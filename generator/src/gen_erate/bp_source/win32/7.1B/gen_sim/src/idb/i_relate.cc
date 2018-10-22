/*========================================================================
 *
 * File:      $RCSfile: i_relate.cc,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:36 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#include <u_trace.hh>
#include <u_error.hh>
#include <u_cursor.hh>
#include <u_env.hh>

#include <iostream.h>
#include <fstream.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

#include <i_relate.hh>
#include <i_var.hh>

#include <i_obj.hh>
#include <i_attr.hh>
#include <i_rel.hh>

#include <i_oinst.hh>
#include <i_ainst.hh>
#include <i_rop.hh>
#include <i_idaref.hh>
#include <i_roip.hh>
#include <i_ir_rop.hh>
#include <i_c_rop.hh>

#include <gs_ui.hh>

extern mc_dbms_database* GS_gen_sim_db_ptr;

static t_long ticks_per_second = 0;




t_boolean
I_relate::relate_object_instance (I_Object_Instance* p_start_oinst_ptr,
    const Description& p_end_obj_key_letter_str, const Description& p_Rnum_str,
    const Description& p_rel_direction_str)

{
    //  Set the index for the ROP bit map to -1 in order to be able to
    //    to detect if one has been found yet.
    //
    t_int found_rop_offset = -1;


    if (! p_start_oinst_ptr)
    {
	LOG_ERROR ((L_log_string,
	    "GS_select::find_rop_ptr ():  p_oinst_ptr == 0."));
	return FALSE;
    }


    I_Object* start_obj_ptr = p_start_oinst_ptr->get_Object_R2001_ptr ();
    if (! start_obj_ptr)
    {
	LOG_ERROR ((L_log_string,
	    "GS_select::find_rop_ptr ():  start_obj_ptr == 0."));
	return FALSE;
    }


    mc_dbms_List <I_Related_Object_Pair*>* id_rop_coll_ptr
	= start_obj_ptr->get_Related_Object_Pair_R2005_coll_ptr ();
    if (! id_rop_coll_ptr)
    {
	LOG_ERROR ((L_log_string,
	    "GS_select::find_rop_ptr ():  id_rop_coll_ptr == 0."));
	return FALSE;
    }


    t_int current_rop_index = -1;
    I_Related_Object_Pair* id_rop_ptr = 0;
    FOR_ALL_ELEMENTS
	(id_rop_ptr,
	I_Related_Object_Pair,
	id_rop_coll_ptr,
	rop_cursor)
    {
	current_rop_index++;


	I_Object* ref_obj_ptr = id_rop_ptr->get_Object_R2006_ptr ();
	if (! ref_obj_ptr)
	{
	    LOG_ERROR ((L_log_string,
		"GS_select::find_rop_ptr ():  ref_obj_ptr == 0."));
	    return FALSE;
	}


	if (p_end_obj_key_letter_str == ref_obj_ptr->get_key_letter ())
	{
	    I_Relationship* id_rel_ptr
		= id_rop_ptr->get_Relationship_R2003_ptr ();
	    if (! id_rel_ptr)
	    {
		LOG_ERROR ((L_log_string,
		    "GS_select::find_rop_ptr ():  id_rel_ptr == 0."));
		return FALSE;
	    }

	    if (p_Rnum_str == id_rel_ptr->get_number ())
	    {
		Description phrase_str (id_rop_ptr->get_OTH_side_phrase ());
		if ((p_rel_direction_str == "")
		    || (p_rel_direction_str == phrase_str))
		{
		    if (found_rop_offset != -1)
		    {
			Description err_msg
				("Found more than one Related Object Pair for the chain link:  ");
			err_msg += start_obj_ptr->get_key_letter ();
			err_msg += "->";
			err_msg += p_end_obj_key_letter_str;
			err_msg += "[";
			err_msg += p_Rnum_str.char_ptr();
			err_msg += "]  -  using the first one found.";
			GS_ui::inform (UI_INFORM__ERROR, err_msg);
			return TRUE;
		    }

		    found_rop_offset = current_rop_index;
		    if (found_rop_offset > 31)
		    {
			//  Unable to store related flag - must always search
			//    for related instances in this case.
			//
			if (! relate_object_instance
			    (p_start_oinst_ptr, id_rop_ptr, ID_SIDE))
			{
			    return FALSE;
			}
		    }
		    else
		    {
			t_uint rop_mask = (0x1 << found_rop_offset);
			t_uint related_flag = p_start_oinst_ptr->get_related_flag ();
			if ((related_flag & rop_mask) == 0)
			{
			    if (! relate_object_instance
				(p_start_oinst_ptr, id_rop_ptr, ID_SIDE))
			    {
				return FALSE;
			    }
			    p_start_oinst_ptr->
				set_related_flag (related_flag | rop_mask);
			}
		    }
		}
	    }
	}
    }


    mc_dbms_List <I_Related_Object_Pair*>* ref_rop_coll_ptr
	= start_obj_ptr->get_Related_Object_Pair_R2006_coll_ptr ();
    if (! ref_rop_coll_ptr)
    {
	LOG_ERROR ((L_log_string,
	    "GS_select::find_rop_ptr ():  ref_rop_coll_ptr == 0."));
	return FALSE;
    }


    I_Related_Object_Pair* ref_rop_ptr = 0;
    FOR_ALL_ELEMENTS
	(ref_rop_ptr,
	I_Related_Object_Pair,
	ref_rop_coll_ptr,
	ref_rop_cursor)
    {
	current_rop_index++;


	I_Object* id_obj_ptr = ref_rop_ptr->get_Object_R2005_ptr ();
	if (! id_obj_ptr)
	{
	    LOG_ERROR ((L_log_string,
		"GS_select::find_rop_ptr ():  id_obj_ptr == 0."));
	    return FALSE;
	}


	if (p_end_obj_key_letter_str == id_obj_ptr->get_key_letter ())
	{
	    I_Relationship* ref_rel_ptr
		= ref_rop_ptr->get_Relationship_R2003_ptr ();
	    if (! ref_rel_ptr)
	    {
		LOG_ERROR ((L_log_string,
		    "GS_select::find_rop_ptr ():  ref_rel_ptr == 0."));
		return FALSE;
	    }


	    if (p_Rnum_str == ref_rel_ptr->get_number ())
	    {
		Description phrase_str (ref_rop_ptr->get_ONE_side_phrase ());
		if ((p_rel_direction_str == "")
		    || (p_rel_direction_str == phrase_str))
		{
		    if (found_rop_offset != -1)
		    {
			Description err_msg
			    ("Found more than one Related Object Pair for the chain link:  ");
			err_msg += start_obj_ptr->get_key_letter ();
			err_msg += "->";
			err_msg += p_end_obj_key_letter_str;
			err_msg += "[";
			err_msg += p_Rnum_str.char_ptr();
			err_msg += "]  -  using the first one found.";
			GS_ui::inform (UI_INFORM__ERROR, err_msg);
			return TRUE;
		    }

		    found_rop_offset = current_rop_index;
		    if (found_rop_offset > 31)
		    {
			//  Unable to store related flag - must always search
			//    for related instances in this case.
			//
			if (! relate_object_instance
			    (p_start_oinst_ptr, ref_rop_ptr, REF_SIDE))
			{
			    return FALSE;
			}
		    }
		    else
		    {
			t_uint rop_mask = (0x1 << found_rop_offset);
			t_uint related_flag = p_start_oinst_ptr->get_related_flag ();
			if ((related_flag & rop_mask) == 0)
			{
			    if (! relate_object_instance
				(p_start_oinst_ptr, ref_rop_ptr, REF_SIDE))
			    {
				return FALSE;
			    }
			    p_start_oinst_ptr->
				set_related_flag (related_flag | rop_mask);
			}
		    }
		}
	    }
	}
    }


    if (found_rop_offset == -1)
    {
	Description err_msg ("Related Object Pair '");
	err_msg += start_obj_ptr->get_key_letter ();
	err_msg += "' and '";
	err_msg += p_end_obj_key_letter_str;
	err_msg += "' is not specified properly - either '";
	err_msg += p_Rnum_str.char_ptr();
	err_msg += "' is not a relationship or the direction is incorrectly specified.";
	GS_ui::inform (UI_INFORM__ERROR, err_msg);
	return FALSE;
    }

    Description object_inst_ref_str = start_obj_ptr->get_key_letter ();
    object_inst_ref_str += "_";
    char buffer [32];
    sprintf (buffer, "%06x",
    p_start_oinst_ptr->get_object_instance_ID ().get_entire_value ());
    object_inst_ref_str += buffer;
    
    return TRUE;
}





t_boolean
I_relate::relate_object_instance (I_Object_Instance* p_oinst_ptr,
    I_Related_Object_Pair* p_rop_ptr, e_start_type p_start_side)

{
    LOG_TRACE (L_D_DATA, L_FUNCTION_BEGIN, (L_log_string,
	"Begin  I_relate::relate_object_instance (p_oinst_ptr=0x%08x, p_rop_ptr=0x%08x, p_start_side=%d)",
	p_oinst_ptr, p_rop_ptr, p_start_side));


    if (! p_oinst_ptr)
    {
	LOG_ERROR ((L_log_string,
	    "End  I_relate::relate_object_instance (FALSE):  p_oinst_ptr == 0."));
	return FALSE;
    }


    if (! p_rop_ptr)
    {
	LOG_ERROR ((L_log_string,
	    "End  I_relate::relate_object_instance (FALSE):  p_rop_ptr == 0."));
	return FALSE;
    }


    I_Object* ne_obj_ptr = p_oinst_ptr->get_Object_R2001_ptr ();
    if (! ne_obj_ptr)
    {
	LOG_ERROR ((L_log_string,
	    "End  I_relate::relate_object_instance (FALSE):  ne_obj_ptr == 0."));
	return FALSE;
    }


    I_Relationship* rop_rel_ptr = p_rop_ptr->get_Relationship_R2003_ptr ();
    if (! rop_rel_ptr)
    {
	LOG_ERROR ((L_log_string,
	    "End  I_relate::relate_object_instance (FALSE):  rop_rel_ptr == 0."));
	return FALSE;
    }


    I_Object* fe_obj_ptr = 0;
    if (p_start_side == ID_SIDE)
    {
	fe_obj_ptr = p_rop_ptr->get_Object_R2006_ptr ();
    }
    else if (p_start_side == REF_SIDE)
    {
	fe_obj_ptr = p_rop_ptr->get_Object_R2005_ptr ();
    }
    if (! fe_obj_ptr)
    {
	LOG_ERROR ((L_log_string,
	    "End  I_relate::relate_object_instance (FALSE):  fe_obj_ptr == 0."));
	return FALSE;
    }


    mc_dbms_List <I_Object_Instance*> intersection_oinst_coll;

    if (p_rop_ptr->get_ID_REF_Rel_Obj_Pair_ptr ())
    {
	I_ID_REF_Rel_Obj_Pair* ir_rop_ptr =
	    p_rop_ptr->get_ID_REF_Rel_Obj_Pair_ptr ();


	mc_dbms_List <I_ID_Attribute_Reference*>* idaref_coll_ptr
	    = ir_rop_ptr->get_ID_Attribute_Reference_R2007_coll_ptr ();
	if (! idaref_coll_ptr)
	{
	    LOG_ERROR ((L_log_string,
		"End  I_relate::relate_object_instance (FALSE):  idaref_coll_ptr == 0."));
	    return FALSE;
	}
	t_boolean first_idaref = TRUE;
	I_ID_Attribute_Reference* idaref_ptr = 0;
	FOR_ALL_ELEMENTS_SAFE
	    (idaref_ptr,
	    I_ID_Attribute_Reference,
	    idaref_coll_ptr,
	    idaref_cursor)
	{
	    I_Attribute* ne_attr_ptr = 0;
	    if (p_start_side == ID_SIDE)
	    {
		ne_attr_ptr = idaref_ptr->get_Attribute_R2008_ptr ();
	    }
	    else if (p_start_side == REF_SIDE)
	    {
		ne_attr_ptr = idaref_ptr->get_Attribute_R2009_ptr ();
	    }
	    if (! ne_attr_ptr)
	    {
		LOG_ERROR ((L_log_string,
		    "End  I_relate::relate_object_instance (FALSE):  ne_attr_ptr == 0."));
		return FALSE;
	    }


	    I_Attribute* fe_attr_ptr = 0;
	    if (p_start_side == ID_SIDE)
	    {
		fe_attr_ptr = idaref_ptr->get_Attribute_R2009_ptr ();
	    }
	    else if (p_start_side == REF_SIDE)
	    {
		fe_attr_ptr = idaref_ptr->get_Attribute_R2008_ptr ();
	    }
	    if (! fe_attr_ptr)
	    {
		LOG_ERROR ((L_log_string,
		    "End  I_relate::relate_object_instance (FALSE):  fe_attr_ptr == 0."));
		return FALSE;
	    }


	    LOG_TRACE (L_D_DATA, L_FUNCTION_BEGIN, (L_log_string,
		"Begin Search for ne_ainst_ptr - rel='%s', ne_obj='%s', ne_attr_ptr=0x%08x ('%s')",
		rop_rel_ptr->get_number ().char_ptr (),
		ne_obj_ptr->get_key_letter ().char_ptr (),
		ne_attr_ptr,
		ne_attr_ptr->get_name ().char_ptr ()));
	    I_Attribute_Instance* ne_ainst_ptr = 0;
	    mc_dbms_List <I_Attribute_Instance*>* ne_ainst_coll_ptr
		= p_oinst_ptr->get_Attribute_Instance_R2002_coll_ptr ();
	    if (! ne_ainst_coll_ptr)
	    {
		LOG_ERROR ((L_log_string,
		    "End  I_relate::relate_object_instance (FALSE):  ne_ainst_coll_ptr == 0."));
		return FALSE;
	    }
	    I_Attribute_Instance* curr_ainst_ptr = 0;
	    FOR_ALL_ELEMENTS_SAFE
		(curr_ainst_ptr,
		I_Attribute_Instance,
		ne_ainst_coll_ptr,
		ne_ainst_cursor)
	    {
		I_Attribute* curr_attr_ptr
		    = curr_ainst_ptr->get_Attribute_R2002_ptr ();
		if (! curr_attr_ptr)
		{
		    LOG_ERROR ((L_log_string,
			"End  I_relate::relate_object_instance (FALSE):  curr_attr_ptr == 0."));
		    return FALSE;
		}
		LOG_TRACE (L_D_DATA, L_FUNCTION_BEGIN,
		    (L_log_string,
		    "Search for ne_ainst_ptr - curr_attr=0x%08x ('%s')",
		    curr_attr_ptr,
		    curr_attr_ptr->get_name ().char_ptr ()));

		if (curr_attr_ptr == ne_attr_ptr)
		{
		    if (ne_ainst_ptr)
		    {
			LOG_ERROR ((L_log_string,
			    "End  I_relate::relate_object_instance (FALSE):  Found more than one referential attribute instance."));
			return FALSE;
		    }
		    ne_ainst_ptr = curr_ainst_ptr;
		}
	    }
	    LOG_TRACE (L_D_DATA, L_FUNCTION_BEGIN, (L_log_string,
		"End Search for ne_ainst_ptr - rel='%s', ne_obj='%s', ne_attr_ptr=0x%08x ('%s')",
		rop_rel_ptr->get_number ().char_ptr (),
		ne_obj_ptr->get_key_letter ().char_ptr (),
		ne_attr_ptr,
		ne_attr_ptr->get_name ().char_ptr ()));
	    if (! ne_ainst_ptr)
	    {
		LOG_ERROR ((L_log_string,
		    "End  I_relate::relate_object_instance (FALSE):  Could not find Near End attribute instance for rel='%s', ne_obj='%s', ne_attr='%s', fe_obj='%s', & fe_attr='%s'.",
		    rop_rel_ptr->get_number ().char_ptr (),
		    ne_obj_ptr->get_key_letter ().char_ptr (),
		    ne_attr_ptr->get_name ().char_ptr (),
		    fe_obj_ptr->get_key_letter ().char_ptr (),
		    fe_attr_ptr->get_name ().char_ptr ()));
		return FALSE;
	    }


	    t_int number_instances_searched = 0;
	    if (first_idaref)
	    {
		//  Find the attibutes which have the same value as the
		//    attribute above - must loop through ALL attribute
		//    instances the first time.
		//
		mc_dbms_List <I_Attribute_Instance*>* fe_ainst_coll_ptr
		    = fe_attr_ptr->get_Attribute_Instance_R2002_coll_ptr ();
		if (! fe_ainst_coll_ptr)
		{
		    LOG_ERROR ((L_log_string,
			"End  I_relate::relate_object_instance (FALSE):  fe_ainst_coll_ptr == 0."));
		    return FALSE;
		}
		I_Attribute_Instance* fe_ainst_ptr = 0;
		FOR_ALL_ELEMENTS_SAFE
		    (fe_ainst_ptr,
		    I_Attribute_Instance,
		    fe_ainst_coll_ptr,
		    fe_ainst_cursor)
		{
		    number_instances_searched++;

		    I_Object_Instance* fe_oinst_ptr
			= fe_ainst_ptr->get_Object_Instance_R2002_ptr ();
		    if (! fe_oinst_ptr)
		    {
			LOG_ERROR ((L_log_string,
			    "End  I_relate::relate_object_instance (FALSE):  fe_oinst_ptr == 0."));
			return FALSE;
		    }

		    if (ne_ainst_ptr->get_core_data_type ()
			!= fe_ainst_ptr->get_core_data_type ())
		    {
			LOG_ERROR ((L_log_string,
			    "End  I_relate::relate_object_instance (FALSE):  Attribute refers to attribute which has a different data item type."));
			return FALSE;
		    }

		    if (*(ne_ainst_ptr->get_var_ptr ())
			== *(fe_ainst_ptr->get_var_ptr ()))
		    {
			intersection_oinst_coll.insert (fe_oinst_ptr);
		    }
		}

		first_idaref = FALSE;
	    }
	    else
	    {
		//  Find the instances matching the current attribute out
		//    of the instances found so far - build a new collection
		//    of these intersection matches.
		//
		mc_dbms_List <I_Object_Instance*>
		    prev_intersection_oinst_coll;
		prev_intersection_oinst_coll = intersection_oinst_coll;
		intersection_oinst_coll.clear ();
		I_Object_Instance* prev_intersection_oinst_ptr = 0;
		t_uint retrieval_position = 10000;
		FOR_ALL_ELEMENTS_SAFE
		    (prev_intersection_oinst_ptr,
		    I_Object_Instance,
		    &prev_intersection_oinst_coll,
		    prev_intersection_oinst_cursor)
		{
		    number_instances_searched++;

		    I_Attribute_Instance* fe_ainst_ptr = 0;
		    mc_dbms_List <I_Attribute_Instance*>* fe_ainst_coll_ptr
			= prev_intersection_oinst_ptr->
			    get_Attribute_Instance_R2002_coll_ptr ();
		    if (! fe_ainst_coll_ptr)
		    {
			LOG_ERROR ((L_log_string,
			    "End  I_relate::relate_object_instance (FALSE):  ainst_coll_ptr == 0."));
			return FALSE;
		    }

		    if (retrieval_position == 10000)
		    {
			//  First time through - must find position of
			//    concerned I_Attribute Instance.
			//
			LOG_TRACE (L_D_DATA, L_FUNCTION_BEGIN,
			    (L_log_string,
			    "Begin Search for fe_ainst_ptr - fe_obj='%s', fe_attr_ptr=0x%08x ('%s')",
			    fe_obj_ptr->get_key_letter ().char_ptr (),
			    fe_attr_ptr,
			    fe_attr_ptr->get_name ().char_ptr ()));
			t_uint i = 0;
			I_Attribute_Instance* curr_ainst_ptr = 0;
			FOR_ALL_ELEMENTS_SAFE
			    (curr_ainst_ptr,
			    I_Attribute_Instance,
			    fe_ainst_coll_ptr,
			    fe_ainst_cursor)
			{
			    I_Attribute* curr_attr_ptr =
				curr_ainst_ptr->get_Attribute_R2002_ptr ();
			    if (! curr_attr_ptr)
			    {
				LOG_ERROR ((L_log_string,
				    "End  I_relate::relate_object_instance (FALSE):  curr_attr_ptr == 0."));
				return FALSE;
			    }
			    LOG_TRACE (L_D_DATA, L_FUNCTION_BEGIN,
				(L_log_string,
				"Search for fe_ainst_ptr - curr_attr=0x%08x ('%s')  -  fe_attr_ptr=0x%08x ('%s')",
				curr_attr_ptr,
				curr_attr_ptr->get_name ().char_ptr (),
				fe_attr_ptr,
				fe_attr_ptr->get_name ().char_ptr ()));

			    if (curr_attr_ptr == fe_attr_ptr)
			    {
				if (retrieval_position != 10000)
				{
				    LOG_ERROR ((L_log_string,
					"End  I_relate::relate_object_instance (FALSE):  Found more than one referential attribute instance."));
				    return FALSE;
				}
				retrieval_position = i;
			    }
			    i++;
			}
			LOG_TRACE (L_D_DATA, L_FUNCTION_BEGIN,
			    (L_log_string,
			    "End Search for fe_ainst_ptr - fe_obj='%s', fe_attr_ptr=0x%08x ('%s')",
			    fe_obj_ptr->get_key_letter ().char_ptr (),
			    fe_attr_ptr,
			    fe_attr_ptr->get_name ().char_ptr ()));
		    }

		    if (retrieval_position >= 10000)
		    {
			LOG_ERROR ((L_log_string,
			    "End  I_relate::relate_object_instance (FALSE):  Could not find Far End attribute instance FIRST TIME THROUGH for rel='%s', ne_obj='%s', ne_attr='%s', fe_obj='%s', & fe_attr='%s'.",
			    rop_rel_ptr->get_number ().char_ptr (),
			    ne_obj_ptr->get_key_letter ().char_ptr (),
			    ne_attr_ptr->get_name ().char_ptr (),
			    fe_obj_ptr->get_key_letter ().char_ptr (),
			    fe_attr_ptr->get_name ().char_ptr ()));
			return FALSE;
		    }

		    fe_ainst_ptr
			= fe_ainst_coll_ptr->retrieve (retrieval_position);

		    if (! fe_ainst_ptr)
		    {
			LOG_ERROR ((L_log_string,
			    "End  I_relate::relate_object_instance (FALSE):  Found Far End but retiveval resulted in 0 for rel='%s', ne_obj='%s', ne_attr='%s', fe_obj='%s', & fe_attr='%s'.",
			    rop_rel_ptr->get_number ().char_ptr (),
			    ne_obj_ptr->get_key_letter ().char_ptr (),
			    ne_attr_ptr->get_name ().char_ptr (),
			    fe_obj_ptr->get_key_letter ().char_ptr (),
			    fe_attr_ptr->get_name ().char_ptr ()));
			return FALSE;
		    }

		    if (ne_ainst_ptr->get_core_data_type ()
			!= fe_ainst_ptr->get_core_data_type ())
		    {
			LOG_ERROR ((L_log_string,
			    "End  I_relate::relate_object_instance (FALSE):  Attribute refers to attribute which has a different data item type."));
			return FALSE;
		    }

		    if (*(ne_ainst_ptr->get_var_ptr ())
			== *(fe_ainst_ptr->get_var_ptr ()))
		    {
			intersection_oinst_coll.insert
			    (prev_intersection_oinst_ptr);
		    }
		}
	    }

	}


	if (p_start_side == ID_SIDE)
	{
	    if (! p_rop_ptr->get_OTH_side_is_conditional ())
	    {
		if (intersection_oinst_coll.cardinality () == 0)
		{
		    Description err_msg ("Relationship '");
			err_msg += rop_rel_ptr->get_number ();
			err_msg += "' is unconditional from object '";
			err_msg += ne_obj_ptr->get_key_letter ();
			err_msg += "' to object '";
			err_msg += fe_obj_ptr->get_key_letter ();
			err_msg += "' yet 0 instances are related.";
			GS_ui::inform (UI_INFORM__ERROR, err_msg);
		}
	    }
	    if (! p_rop_ptr->get_OTH_side_is_many ())
	    {
		if (intersection_oinst_coll.cardinality () > 1)
		{
		    Description err_msg ("Relationship '");
			err_msg += rop_rel_ptr->get_number ();
			err_msg += "' is multiplicity ONE from object '";
			err_msg += ne_obj_ptr->get_key_letter ();
			err_msg += "' to object '";
			err_msg += fe_obj_ptr->get_key_letter ();
			err_msg += "' yet more than ONE instances are related.";
			GS_ui::inform (UI_INFORM__ERROR, err_msg);
		}
	    }
	}
	else if (p_start_side == REF_SIDE)
	{
	    if (! p_rop_ptr->get_ONE_side_is_conditional ())
	    {
		if (intersection_oinst_coll.cardinality () == 0)
		{
		    Description err_msg("Relationship '");
			err_msg += rop_rel_ptr->get_number ();
			err_msg += "' is unconditional from object '";
			err_msg += ne_obj_ptr->get_key_letter ();
			err_msg += "' to object '";
			err_msg += fe_obj_ptr->get_key_letter ();
			err_msg += "' yet 0 instances are related.";
			GS_ui::inform (UI_INFORM__ERROR, err_msg);
		}
	    }
	    if (! p_rop_ptr->get_ONE_side_is_many ())
	    {
		if (intersection_oinst_coll.cardinality () > 1)
		{
		    Description	err_msg("Relationship '");
			err_msg += rop_rel_ptr->get_number ();
			err_msg += "' is multiplicity ONE from object '";
			err_msg += ne_obj_ptr->get_key_letter ();
			err_msg += "' to object '";
			err_msg += fe_obj_ptr->get_key_letter ();
			err_msg += "' yet more than ONE instances are related.";
			GS_ui::inform (UI_INFORM__ERROR, err_msg);
		}
	    }
	}



	//  Now that a coll of instances which are related has been built,
	//    create one instance of I_ROIP to represent each of these
	//    related instance pairs.  NOTE:  First, sift out the related
	//    instances already in the DB.
	//
	mc_dbms_List <I_Related_Object_Instance_Pair*>* roip_coll_ptr
	    = p_rop_ptr->get_Related_Object_Instance_Pair_R2004_coll_ptr ();
	if (! roip_coll_ptr)
	{
	    LOG_ERROR ((L_log_string,
		"End  I_relate::relate_object_instance (FALSE):  roip_coll_ptr == 0."));
	    return FALSE;
	}
	I_Related_Object_Instance_Pair* roip_ptr = 0;
	FOR_ALL_ELEMENTS_SAFE
	    (roip_ptr,
	    I_Related_Object_Instance_Pair,
	    roip_coll_ptr,
	    roip_cursor)
	{
	    if (roip_ptr->get_relationship_ID () != p_rop_ptr->
		    get_Relationship_R2003_ptr ()->get_relationship_ID ())
	    {
		LOG_ERROR ((L_log_string,
		    "End  I_relate::relate_object_instance (FALSE):  ROIP does not have relationship_ID which matches ROIP->ROP->REL's - resetting to match."));
		roip_ptr->set_relationship_ID (p_rop_ptr->
		    get_Relationship_R2003_ptr ()->get_relationship_ID ());
	    }

	    if (roip_ptr->get_R2010_is_conditional ()
		!= p_rop_ptr->get_ONE_side_is_conditional ())
	    {
		LOG_ERROR ((L_log_string,
		    "End  I_relate::relate_object_instance (FALSE):  ROIP does not have ONE_side_is_conditional which matches ROIP->ROP's - resetting to match."));
		roip_ptr->set_R2010_is_conditional
		    (p_rop_ptr->get_ONE_side_is_conditional ());
	    }

	    if (roip_ptr->get_R2010_is_many ()
		!= p_rop_ptr->get_ONE_side_is_many ())
	    {
		LOG_ERROR ((L_log_string,
		    "End  I_relate::relate_object_instance (FALSE):  ROIP does not have ONE_side_is_many which matches ROIP->ROP's - resetting to match."));
		roip_ptr->set_R2010_is_many
		    (p_rop_ptr->get_ONE_side_is_many ());
	    }

	    if (roip_ptr->get_R2010_phrase ()
		!= p_rop_ptr->get_ONE_side_phrase ())
	    {
		LOG_ERROR ((L_log_string,
		    "End  I_relate::relate_object_instance (FALSE):  ROIP does not have ONE_side_phrase which matches ROIP->ROP's - resetting to match."));
		roip_ptr->set_R2010_phrase
		    (p_rop_ptr->get_ONE_side_phrase ());
	    }

	    if (roip_ptr->get_R2011_is_conditional ()
		!= p_rop_ptr->get_OTH_side_is_conditional ())
	    {
		LOG_ERROR ((L_log_string,
		    "End  I_relate::relate_object_instance (FALSE):  ROIP does not have OTH_side_is_conditional which matches ROIP->ROP's - resetting to match."));
		roip_ptr->set_R2011_is_conditional
		    (p_rop_ptr->get_OTH_side_is_conditional ());
	    }

	    if (roip_ptr->get_R2011_is_many ()
		!= p_rop_ptr->get_OTH_side_is_many ())
	    {
		LOG_ERROR ((L_log_string,
		    "End  I_relate::relate_object_instance (FALSE):  ROIP does not have OTH_side_is_many which matches ROIP->ROP's - resetting to match."));
		roip_ptr->set_R2011_is_many
		    (p_rop_ptr->get_OTH_side_is_many ());
	    }

	    if (roip_ptr->get_R2011_phrase ()
		!= p_rop_ptr->get_OTH_side_phrase ())
	    {
		LOG_ERROR ((L_log_string,
		    "End  I_relate::relate_object_instance (FALSE):  ROIP does not have OTH_side_phrase which matches ROIP->ROP's - resetting to match."));
		roip_ptr->set_R2011_phrase
		    (p_rop_ptr->get_OTH_side_phrase ());
	    }

	    if (roip_ptr->get_Rnum_str () != p_rop_ptr->
		    get_Relationship_R2003_ptr ()->get_number ())
	    {
		LOG_ERROR ((L_log_string,
		    "End  I_relate::relate_object_instance (FALSE):  ROIP does not have number which matches ROIP->ROP->REL's - resetting to match."));
		roip_ptr->set_Rnum_str (p_rop_ptr->
		    get_Relationship_R2003_ptr ()->get_number ());
	    }

	    I_Object_Instance* oinst_ptr;
	    if (p_start_side == ID_SIDE)
	    {
		oinst_ptr = roip_ptr->get_Object_Instance_R2010_ptr ();
	    }
	    else if (p_start_side == REF_SIDE)
	    {
		oinst_ptr = roip_ptr->get_Object_Instance_R2011_ptr ();
	    }

	    if (oinst_ptr == p_oinst_ptr)
	    {
		//  Search for this ROIP in the ones about to be added -
		//    if already in DB, then remove it from the
		//    intersection collection of ones to be added.
		//
		I_Object_Instance* intersection_oinst_ptr = 0;
		FOR_ALL_ELEMENTS_SAFE
		    (intersection_oinst_ptr,
		    I_Object_Instance,
		    &intersection_oinst_coll,
		    intersection_oinst_cursor)
		{
		    I_Object_Instance* existing_related_oinst_ptr;
		    if (p_start_side == ID_SIDE)
		    {
			existing_related_oinst_ptr
			    = roip_ptr->get_Object_Instance_R2011_ptr ();
		    }
		    else if (p_start_side == REF_SIDE)
		    {
			existing_related_oinst_ptr
			    = roip_ptr->get_Object_Instance_R2010_ptr ();
		    }

		    if (intersection_oinst_ptr
			== existing_related_oinst_ptr)
		    {
			//  Already exists in DB - remove it from
			//    intersection collection.
			//
			intersection_oinst_coll.remove
			    (intersection_oinst_ptr);
		    }
		}
	    }


	    //  Check the other direction...
	    //
	    if (p_start_side == ID_SIDE)
	    {
		oinst_ptr = roip_ptr->get_Object_Instance_R2011_ptr ();
	    }
	    else if (p_start_side == REF_SIDE)
	    {
		oinst_ptr = roip_ptr->get_Object_Instance_R2010_ptr ();
	    }

	    if (oinst_ptr == p_oinst_ptr)
	    {
		//  Search for this ROIP in the ones about to be added -
		//    if already in DB, then remove it from the
		//    intersection collection of ones to be added.
		//
		I_Object_Instance* intersection_oinst_ptr = 0;
		FOR_ALL_ELEMENTS_SAFE
		    (intersection_oinst_ptr,
		    I_Object_Instance,
		    &intersection_oinst_coll,
		    intersection_oinst_cursor)
		{
		    I_Object_Instance* existing_related_oinst_ptr;
		    if (p_start_side == ID_SIDE)
		    {
			existing_related_oinst_ptr
			    = roip_ptr->get_Object_Instance_R2010_ptr ();
		    }
		    else if (p_start_side == REF_SIDE)
		    {
			existing_related_oinst_ptr
			    = roip_ptr->get_Object_Instance_R2011_ptr ();
		    }

		    if (intersection_oinst_ptr
			== existing_related_oinst_ptr)
		    {
			//  Already exists in DB - remove it from
			//    intersection collection.
			//
			intersection_oinst_coll.remove
			    (intersection_oinst_ptr);
		    }
		}
	    }
	}


	I_Object_Instance* intersection_oinst_ptr = 0;
	FOR_ALL_ELEMENTS_SAFE
	    (intersection_oinst_ptr,
	    I_Object_Instance,
	    &intersection_oinst_coll,
	    intersection_oinst_cursor)
	{
	    I_Related_Object_Instance_Pair* roip_ptr
		= I_Related_Object_Instance_Pair::create(GS_gen_sim_db_ptr);
	    if (! roip_ptr)
	    {
		LOG_ERROR ((L_log_string,
		    "End  I_relate::relate_object_instance (FALSE):  I_ROIP create returned 0."));
		return FALSE;
	    }

	    roip_ptr->relate_R2004 (p_rop_ptr);
	    if (p_start_side == ID_SIDE)
	    {
		roip_ptr->relate_R2010 (p_oinst_ptr);
		roip_ptr->relate_R2011 (intersection_oinst_ptr);
	    }
	    else if (p_start_side == REF_SIDE)
	    {
		roip_ptr->relate_R2010 (intersection_oinst_ptr);
		roip_ptr->relate_R2011 (p_oinst_ptr);
	    }
	    roip_ptr->set_relationship_ID (p_rop_ptr->
		get_Relationship_R2003_ptr ()->get_relationship_ID ());
	    roip_ptr->set_Rnum_str
		(p_rop_ptr->get_Relationship_R2003_ptr ()->get_number ());
	    roip_ptr->set_R2010_is_conditional
		(p_rop_ptr->get_ONE_side_is_conditional ());
	    roip_ptr->set_R2010_is_many
		(p_rop_ptr->get_ONE_side_is_many ());
	    roip_ptr->set_R2010_phrase
		(p_rop_ptr->get_ONE_side_phrase ());
	    roip_ptr->set_R2011_is_conditional
		(p_rop_ptr->get_OTH_side_is_conditional ());
	    roip_ptr->set_R2011_is_many
		(p_rop_ptr->get_OTH_side_is_many ());
	    roip_ptr->set_R2011_phrase
		(p_rop_ptr->get_OTH_side_phrase ());
	}
    }
    else if (p_rop_ptr->get_Chain_Rel_Obj_Pair_ptr ())
    {
	I_Chain_Rel_Obj_Pair* c_rop_ptr =
	    p_rop_ptr->get_Chain_Rel_Obj_Pair_ptr ();

/************************************************************************
	LOG_ERROR ((L_log_string,
	    "End  I_relate::relate_object_instance (FALSE):  I_C_ROP not implemented yet."));
	return FALSE;
************************************************************************/
    }
    else
    {
	LOG_ERROR ((L_log_string,
	    "End  I_relate::relate_object_instance (FALSE):  I_ROP derived class type not recognized."));
	return FALSE;
    }


    return TRUE;
}

void
I_relate::clear_related_flag (I_Object_Instance* p_oinst_ptr)
{
    LOG_TRACE (L_D_DATA, L_FUNCTION_BEGIN, (L_log_string,
	"Begin  I_relate::clear_related_flag (p_oinst_ptr=0x%08x)",
	p_oinst_ptr));

    if (! p_oinst_ptr)
    {
    	LOG_ERROR ((L_log_string,
	        "I_relate::clear_related_flag ():  p_oinst_ptr == 0."));
	    return;
    }


    I_Object* start_obj_ptr = p_oinst_ptr->get_Object_R2001_ptr ();
    if (! start_obj_ptr)
    {
    	LOG_ERROR ((L_log_string,
	        "I_relate::clear_related_flag ():  start_obj_ptr == 0."));
	    return;
    }
    else
    {
        I_Object_Instance* oinst_ptr = 0;
        FOR_ALL_ELEMENTS
	    (oinst_ptr,
	    I_Object_Instance,
	    start_obj_ptr->get_Object_Instance_R2001_coll_ptr (),
	    oinst_cursor)
        {
    	    oinst_ptr->set_related_flag (0);
        }
    }

    I_Related_Object_Instance_Pair* roip_ptr = 0;
    FOR_ALL_ELEMENTS_SAFE
	(roip_ptr,
	I_Related_Object_Instance_Pair,
	p_oinst_ptr->get_Related_Object_Instance_Pair_R2010_coll_ptr (),
	roip_cursor)
    {
        delete roip_ptr;
    }

    FOR_ALL_ELEMENTS_SAFE
	(roip_ptr,
	I_Related_Object_Instance_Pair,
	p_oinst_ptr->get_Related_Object_Instance_Pair_R2011_coll_ptr (),
	roip_cursor2)
    {
        delete roip_ptr;
    }

    mc_dbms_List <I_Related_Object_Pair*>* id_rop_coll_ptr
	= start_obj_ptr->get_Related_Object_Pair_R2005_coll_ptr ();
    if (! id_rop_coll_ptr)
    {
    	LOG_ERROR ((L_log_string,
	        "I_relate::clear_related_flag ():  id_rop_coll_ptr == 0."));
	    return;
    }


    I_Related_Object_Pair* id_rop_ptr = 0;
    FOR_ALL_ELEMENTS
	(id_rop_ptr,
	I_Related_Object_Pair,
	id_rop_coll_ptr,
	rop_cursor)
    {

	    I_Object* ref_obj_ptr = id_rop_ptr->get_Object_R2006_ptr ();
	    if (! ref_obj_ptr)
	    {
	        LOG_ERROR ((L_log_string,
		    "I_relate::clear_related_flag ():  ref_obj_ptr == 0."));
	    }
        else
        {
            I_Object_Instance* oinst_ptr = 0;
            FOR_ALL_ELEMENTS
	        (oinst_ptr,
	        I_Object_Instance,
	        ref_obj_ptr->get_Object_Instance_R2001_coll_ptr (),
	        oinst_cursor)
            {
    	        oinst_ptr->set_related_flag (0);
            }
        }
    }

    mc_dbms_List <I_Related_Object_Pair*>* ref_rop_coll_ptr
	= start_obj_ptr->get_Related_Object_Pair_R2006_coll_ptr ();
    if (! ref_rop_coll_ptr)
    {
	    LOG_ERROR ((L_log_string,
	        "I_relate::clear_related_flag ():  ref_rop_coll_ptr == 0."));
	    return;
    }

    I_Related_Object_Pair* ref_rop_ptr = 0;
    FOR_ALL_ELEMENTS
	(ref_rop_ptr,
	I_Related_Object_Pair,
	ref_rop_coll_ptr,
	ref_rop_cursor)
    {
	    I_Object* id_obj_ptr = ref_rop_ptr->get_Object_R2005_ptr ();
	    if (! id_obj_ptr)
	    {
	        LOG_ERROR ((L_log_string,
		    "I_relate::clear_related_flag ():  id_obj_ptr == 0."));
	    }
        else
        {
            I_Object_Instance* oinst_ptr = 0;
            FOR_ALL_ELEMENTS
	        (oinst_ptr,
	        I_Object_Instance,
	        id_obj_ptr->get_Object_Instance_R2001_coll_ptr (),
	        oinst_cursor)
            {
    	        oinst_ptr->set_related_flag (0);
            }
        }
    }

    LOG_TRACE (L_D_DATA, L_FUNCTION_END, (L_log_string,
	"End    I_relate::clear_related_flag ()" ));
}

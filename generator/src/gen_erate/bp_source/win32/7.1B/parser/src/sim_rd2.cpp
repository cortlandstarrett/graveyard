/*========================================================================
 *
 * File:      $RCSfile: sim_rd2.cpp,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:21 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#include "SIM_SOR.h"

#include <gs_obj.hh>
#include <gs_stack.hh>
#include <gs_ui.hh>
#include <gs_find.hh>                               

#include <i_attr.hh>
#include <i_ainst.hh>
#include <i_idaref.hh>
#include <i_ir_rop.hh>
#include <i_oinst.hh>
#include <i_roip.hh>
#include <i_rel.hh>
#include <i_rop.hh>

#include <d_object.hh>                               
#include <d_ario.hh>
#include <d_rattr.hh>
#include <d_rel.hh>                               
#include <d_smprel.hh>                               
#include <d_cmprel.hh>                               
#include <d_assrel.hh>                               
#include <d_inhrel.hh>                               
#include <u_cursor.hh>                               
#include <u_string.hh>

extern mc_dbms_database* GS_gen_sim_db_ptr;

static I_Object_Instance* find_related_assoc_instance( 
		I_Object_Instance* this_oinst_ptr, I_Object_Instance* other_oinst_ptr, 
		Associative_relationship* other_ooa_rel_ptr );

static int check_object_instance_relationship ( 
	const vchar *p_inst1_name, 
    const vchar *p_inst2_name, 
    const vchar *p_assoc_name, 
    I_Object_Instance* oinst1_ptr,
    I_Object_Instance* oinst2_ptr,
    I_Object_Instance* assoc_oinst_ptr,
    Id& oir1_id,
    t_boolean& is_oir1_many,
    Id& oir2_id,
    t_boolean& is_oir2_many,
    Id& assoc_oir_id,
    t_boolean& is_assoc_oir_many)
{
    I_Related_Object_Instance_Pair* roip_ptr;
    FOR_ALL_ELEMENTS_SAFE
	(roip_ptr,
	I_Related_Object_Instance_Pair,
	oinst1_ptr->get_Related_Object_Instance_Pair_R2010_coll_ptr (),
	roip_cursor_1_2010)
    {
	if (oir1_id == roip_ptr->get_R2010_obj_in_rel_ID ())
	{
	    if (! is_oir2_many)
	    {
		if (oir2_id == roip_ptr->get_R2011_obj_in_rel_ID ())
		{
			Description err_msg ("Instance referenced by '");
			err_msg += p_inst1_name;
			err_msg += "' is already related to instance across specified relationship.";
		    GS_ui::inform (UI_INFORM__ERROR, err_msg);
		    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
			"End #31:  SIM_SOR::interpret_relate_statement ()."));
		    return FALSE;
		}
		else if (assoc_oir_id == roip_ptr->get_R2011_obj_in_rel_ID ())
		{
			Description err_msg ("Instance referenced by '");
			err_msg += p_inst1_name;
			err_msg += "' is already related to associative object instance across specified relationship.";
		    GS_ui::inform (UI_INFORM__ERROR, err_msg);
		    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
			"End #32:  SIM_SOR::interpret_relate_statement ()."));
		    return FALSE;
		}
	    }
	    if (! is_assoc_oir_many)
	    {
		if (oir2_id == roip_ptr->get_R2011_obj_in_rel_ID ())
		{
		    if (oinst2_ptr == roip_ptr->get_Object_Instance_R2011_ptr())
		    {
			Description err_msg ("Instance referenced by '");
			err_msg += p_inst1_name;
			err_msg += "' is already related to instance referenced by '";
			err_msg += p_inst2_name;
			err_msg += "' across specified relationship.";
			GS_ui::inform (UI_INFORM__ERROR, err_msg);
			LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
			    "End #33:  SIM_SOR::interpret_relate_statement ()."));
			return FALSE;
		    }
		}
	    }
	}
    }
    FOR_ALL_ELEMENTS_SAFE
	(roip_ptr,
	I_Related_Object_Instance_Pair,
	oinst1_ptr->get_Related_Object_Instance_Pair_R2011_coll_ptr (),
	roip_cursor_1_2011)
    {
	if (oir1_id == roip_ptr->get_R2011_obj_in_rel_ID ())
	{
	    if (! is_oir2_many)
	    {
		if (oir2_id == roip_ptr->get_R2010_obj_in_rel_ID ())
		{
			Description err_msg ("Instance referenced by '");
			err_msg += p_inst1_name;
			err_msg += "' is already related to instance across specified relationship.";
		    GS_ui::inform (UI_INFORM__ERROR, err_msg);
		    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
			"End #34:  SIM_SOR::interpret_relate_statement ()."));
		    return FALSE;
		}
		else if (assoc_oir_id == roip_ptr->get_R2010_obj_in_rel_ID ())
		{
			Description err_msg ("Instance referenced by '");
			err_msg += p_inst1_name;
			err_msg += "' is already related to associative object instance across specified relationship.";
		    GS_ui::inform (UI_INFORM__ERROR, err_msg);
		    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
			"End #35:  SIM_SOR::interpret_relate_statement ()."));
		    return FALSE;
		}
	    }
	    if (! is_assoc_oir_many)
	    {
		if (oir2_id == roip_ptr->get_R2010_obj_in_rel_ID ())
		{
		    if (oinst2_ptr == roip_ptr->get_Object_Instance_R2010_ptr())
		    {
			    Description err_msg ("Instance referenced by '");
				err_msg += p_inst1_name;
			    err_msg += "' is already related to instance referenced by '";
			    err_msg += p_inst2_name;
				err_msg += "' across specified relationship.";
			GS_ui::inform (UI_INFORM__ERROR, err_msg);
			LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
			    "End #36:  SIM_SOR::interpret_relate_statement ()."));
			return FALSE;
		    }
		}
	    }
	}
    }
    FOR_ALL_ELEMENTS_SAFE
	(roip_ptr,
	I_Related_Object_Instance_Pair,
	oinst2_ptr->get_Related_Object_Instance_Pair_R2010_coll_ptr (),
	roip_cursor_2_2010)
    {
	if (oir2_id == roip_ptr->get_R2010_obj_in_rel_ID ())
	{
	    if (! is_oir1_many)
	    {
		if (oir1_id == roip_ptr->get_R2011_obj_in_rel_ID ())
		{
			Description err_msg ("Instance referenced by '");
			err_msg += p_inst2_name;
			err_msg += "' is already related to instance across specified relationship.";
		    GS_ui::inform (UI_INFORM__ERROR, err_msg);
		    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
			"End #37:  SIM_SOR::interpret_relate_statement ()."));
		    return FALSE;
		}
		else if (assoc_oir_id == roip_ptr->get_R2011_obj_in_rel_ID ())
		{
			Description err_msg ("Instance referenced by '");
			err_msg += p_inst2_name;
			err_msg += "' is already related to associative object instance across specified relationship.";
		    GS_ui::inform (UI_INFORM__ERROR, err_msg);
		    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
			"End #38:  SIM_SOR::interpret_relate_statement ()."));
		    return FALSE;
		}
	    }
	    if (! is_assoc_oir_many)
	    {
		if (oir1_id == roip_ptr->get_R2011_obj_in_rel_ID ())
		{
		    if (oinst1_ptr == roip_ptr->get_Object_Instance_R2011_ptr())
		    {
			    Description err_msg ("Instance referenced by '");
				err_msg += p_inst2_name;
			    err_msg += "' is already related to instance referenced by '";
			    err_msg += p_inst1_name;
				err_msg += "' across specified relationship.";
			GS_ui::inform (UI_INFORM__ERROR, err_msg);
			LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
			    "End #39:  SIM_SOR::interpret_relate_statement ()."));
			return FALSE;
		    }
		}
	    }
	}
    }
    FOR_ALL_ELEMENTS_SAFE
	(roip_ptr,
	I_Related_Object_Instance_Pair,
	oinst2_ptr->get_Related_Object_Instance_Pair_R2011_coll_ptr (),
	roip_cursor_2_2011)
    {
	if (oir2_id == roip_ptr->get_R2011_obj_in_rel_ID ())
	{
	    if (! is_oir1_many)
	    {
		if (oir1_id == roip_ptr->get_R2010_obj_in_rel_ID ())
		{
			Description err_msg ("Instance referenced by '");
			err_msg += p_inst2_name;
			err_msg += "' is already related to instance across specified relationship.";
		    GS_ui::inform (UI_INFORM__ERROR, err_msg);
		    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
			"End #40:  SIM_SOR::interpret_relate_statement ()."));
		    return FALSE;
		}
		else if (assoc_oir_id == roip_ptr->get_R2010_obj_in_rel_ID ())
		{
			Description err_msg ("Instance referenced by '");
			err_msg += p_inst2_name;
			err_msg += "' is already related to associative object instance across specified relationship.";
		    GS_ui::inform (UI_INFORM__ERROR, err_msg);
		    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
			"End #41:  SIM_SOR::interpret_relate_statement ()."));
		    return FALSE;
		}
	    }
	    if (! is_assoc_oir_many)
	    {
		if (oir1_id == roip_ptr->get_R2010_obj_in_rel_ID ())
		{
		    if (oinst1_ptr == roip_ptr->get_Object_Instance_R2010_ptr())
		    {
			    Description err_msg ("Instance referenced by '");
				err_msg += p_inst2_name;
			    err_msg += "' is already related to instance referenced by '";
			    err_msg += p_inst1_name;
				err_msg += "' across specified relationship.";
			GS_ui::inform (UI_INFORM__ERROR, err_msg);
			LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
			    "End #42:  SIM_SOR::interpret_relate_statement ()."));
			return FALSE;
		    }
		}
	    }
	}
    }

    if (assoc_oinst_ptr)
    {
	FOR_ALL_ELEMENTS_SAFE
	    (roip_ptr,
	    I_Related_Object_Instance_Pair,
	    assoc_oinst_ptr->get_Related_Object_Instance_Pair_R2010_coll_ptr (),
	    roip_cursor_assoc_2010)
	{
	    if (assoc_oir_id == roip_ptr->get_R2010_obj_in_rel_ID ())
	    {
		if (oir1_id == roip_ptr->get_R2011_obj_in_rel_ID ())
		{
			Description err_msg ("Instance referenced by '");
			err_msg += p_assoc_name;
			err_msg += "' is already related across specified relationship.";
		    GS_ui::inform (UI_INFORM__ERROR, err_msg);
		    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
			"End #43:  SIM_SOR::interpret_relate_statement ()."));
		    return FALSE;
		}
		else if (oir2_id == roip_ptr->get_R2011_obj_in_rel_ID ())
		{
			Description err_msg ("Instance referenced by '");
			err_msg += p_assoc_name;
			err_msg += "' is already related across specified relationship.";
		    GS_ui::inform (UI_INFORM__ERROR, err_msg);
		    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
			"End #44:  SIM_SOR::interpret_relate_statement ()."));
		    return FALSE;
		}
	    }
	}
	FOR_ALL_ELEMENTS_SAFE
	    (roip_ptr,
	    I_Related_Object_Instance_Pair,
	    assoc_oinst_ptr->get_Related_Object_Instance_Pair_R2011_coll_ptr (),
	    roip_cursor_assoc_2011)
	{
	    if (assoc_oir_id == roip_ptr->get_R2011_obj_in_rel_ID ())
	    {
		if (oir1_id == roip_ptr->get_R2010_obj_in_rel_ID ())
		{
			Description err_msg ("Instance referenced by '");
			err_msg += p_assoc_name;
			err_msg += "' is already related across specified relationship.";
		    GS_ui::inform (UI_INFORM__ERROR, err_msg);
		    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
			"End #45:  SIM_SOR::interpret_relate_statement ()."));
		    return FALSE;
		}
		else if (oir2_id == roip_ptr->get_R2010_obj_in_rel_ID ())
		{
			Description err_msg ("Instance referenced by '");
			err_msg += p_assoc_name;
			err_msg += "' is already related across specified relationship.";
		    GS_ui::inform (UI_INFORM__ERROR, err_msg);
		    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
			"End #46:  SIM_SOR::interpret_relate_statement ()."));
		    return FALSE;
		}
	    }
	}
    }
	return TRUE;
}

void SIM_SOR::interpret_relate_statement( const vchar *p_inst1_name, 
    const vchar *p_inst2_name, 
    const vchar *p_assoc_name, 
    const vchar *p_rel, 
    const vchar *p_phrase )
{
    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_BEGIN, (L_log_string,
	"Begin  SIM_SOR::interpret_relate_statement (p_inst1_name=%s, p_inst2_name=%s, p_rel=%s).",
	p_inst1_name, p_inst2_name, p_rel));

    I_Object_Instance* oinst1_ptr = 0;
	Id obj1_id;
	if ( ! get_inst_var_ptr( p_inst1_name, oinst1_ptr, obj1_id ) )
	{
		return ;
	}

    I_Object_Instance* oinst2_ptr = 0;
	Id obj2_id;
	if ( ! get_inst_var_ptr( p_inst2_name, oinst2_ptr, obj2_id ) )
	{
		return ;
	}

    I_Object_Instance* assoc_oinst_ptr = 0;
    Id assoc_obj_id;
    if (p_assoc_name)
    {
		if ( ! get_inst_var_ptr( p_assoc_name, assoc_oinst_ptr, assoc_obj_id ) )
		{
			return ;
		}
    }

    Relationship* ooa_rel_ptr = 0;
    Id sim_rel_id;
	if (! get_relationship_ptr( p_rel, ooa_rel_ptr, sim_rel_id ) )
	{
		return ;
	}


	do_relate_statement (
	  p_inst1_name, p_inst2_name, p_assoc_name, 
	  oinst1_ptr, obj1_id,
      oinst2_ptr, obj2_id,
      assoc_oinst_ptr, assoc_obj_id,
      ooa_rel_ptr, 0, p_rel, p_phrase );

    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	"End #50:  SIM_SOR::interpret_relate_statement ()."));
    return ;
}



void SIM_SOR::interpret_unrelate_statement( const vchar *p_inst1_name, 
    const vchar *p_inst2_name, 
    const vchar *p_assoc_name, 
    const vchar *p_rel, 
    const vchar *p_phrase )
{
    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_BEGIN, (L_log_string,
	"Begin  SIM_SOR::interpret_unrelate_statement (p_inst1_name=%s, p_inst2_name=%s, p_rel=%s).",
	p_inst1_name, p_inst2_name, p_rel));

    I_Object_Instance* oinst1_ptr = 0;
	Id obj1_id;
	if ( ! get_inst_var_ptr( p_inst1_name, oinst1_ptr, obj1_id ) )
	{
		return ;
	}

    I_Object_Instance* oinst2_ptr = 0;
	Id obj2_id;
	if ( ! get_inst_var_ptr( p_inst2_name, oinst2_ptr, obj2_id ) )
	{
		return ;
	}

    I_Object_Instance* assoc_oinst_ptr = 0;
    Id assoc_obj_id;
    if (p_assoc_name)
    {
		if ( ! get_inst_var_ptr( p_assoc_name, assoc_oinst_ptr, assoc_obj_id ) )
		{
			return ;
		}
    }

    Relationship* ooa_rel_ptr = 0;
    Id sim_rel_id;
	if (! get_relationship_ptr( p_rel, ooa_rel_ptr, sim_rel_id ) )
	{
		return ;
	}


	do_unrelate_statement (oinst1_ptr, obj1_id,
      oinst2_ptr, obj2_id,
      assoc_oinst_ptr, assoc_obj_id,
      ooa_rel_ptr, 0, p_phrase );


    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	"End #14:  SIM_SOR::interpret_unrelate_statment ()."));
    return ;
}




void SIM_SOR::set_rel_phrases
    (I_Related_Object_Instance_Pair* p_roip_ptr, Relationship* p_ooa_rel_ptr)

{
    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_BEGIN, (L_log_string,
	"Begin  SIM_SOR::set_rel_phrases (p_roip_ptr=0x%08x, p_ooa_rel_ptr=0x%08x).",
	p_roip_ptr, p_ooa_rel_ptr));


    if (! p_roip_ptr)
    {
	LOG_ERROR ((L_log_string,
	    "End #1:  SIM_SOR::set_rel_phrases ():  p_roip_ptr == 0."));
	return ;
    }


    if (! p_ooa_rel_ptr)
    {
	LOG_ERROR ((L_log_string,
	    "End #2:  SIM_SOR::set_rel_phrases ():  p_ooa_rel_ptr == 0."));
	return ;
    }


    I_Object_Instance* R2010_oinst_ptr
	= p_roip_ptr->get_Object_Instance_R2010_ptr ();
    if (! R2010_oinst_ptr)
    {
	LOG_ERROR ((L_log_string,
	    "End #3:  SIM_SOR::set_rel_phrases ():  R2010_oinst_ptr == 0."));
	return ;
    }
    I_Object* R2010_obj_ptr = R2010_oinst_ptr->get_Object_R2001_ptr ();
    if (! R2010_obj_ptr)
    {
	LOG_ERROR ((L_log_string,
	    "End #4:  SIM_SOR::set_rel_phrases ():  R2010_obj_ptr == 0."));
	return ;
    }
    Id R2010_obj_id = R2010_obj_ptr->get_object_ID ();

    I_Object_Instance* R2011_oinst_ptr
	= p_roip_ptr->get_Object_Instance_R2011_ptr ();
    if (! R2011_oinst_ptr)
    {
	LOG_ERROR ((L_log_string,
	    "End #5:  SIM_SOR::set_rel_phrases ():  R2011_oinst_ptr == 0."));
	return ;
    }
    I_Object* R2011_obj_ptr = R2011_oinst_ptr->get_Object_R2001_ptr ();
    if (! R2011_obj_ptr)
    {
	LOG_ERROR ((L_log_string,
	    "End #6:  SIM_SOR::set_rel_phrases ():  R2011_obj_ptr == 0."));
	return ;
    }
    Id R2011_obj_id = R2011_obj_ptr->get_object_ID ();


    if (! p_ooa_rel_ptr->get_inheritance_relationship_ptr ())
    {
	Simple_relationship* simple_rel_ptr
	    = p_ooa_rel_ptr->get_simple_relationship_ptr ();
	Composition_relationship* compmc_dbms_rel_ptr
	    = p_ooa_rel_ptr->get_composition_relationship_ptr ();
	Associative_relationship* assoc_rel_ptr
	    = p_ooa_rel_ptr->get_associative_relationship_ptr ();
	Object_in_non_inh_relationship* X_oinir_ptr = 0;
	Object_in_non_inh_relationship* Y_oinir_ptr = 0;
	Object_in_non_inh_relationship* Z_oinir_ptr = 0;
	if (simple_rel_ptr)
	{
	    X_oinir_ptr = simple_rel_ptr->get_nth_obj_in_non_inh_rel (1);
	    Y_oinir_ptr = simple_rel_ptr->get_nth_obj_in_non_inh_rel (2);
	}
	else if (compmc_dbms_rel_ptr)
	{
	    X_oinir_ptr = compmc_dbms_rel_ptr->get_object_as_comp_one_end_ptr ();
	    Y_oinir_ptr = compmc_dbms_rel_ptr->get_object_as_comp_other_end_ptr ();
	}
	else if (assoc_rel_ptr)
	{
	    X_oinir_ptr = assoc_rel_ptr->get_object_as_assoc_one_side_ptr ();
	    Y_oinir_ptr = assoc_rel_ptr->get_object_as_assoc_other_side_ptr ();
	    Z_oinir_ptr = assoc_rel_ptr->get_object_as_associator_ptr ();
	}

	if (! X_oinir_ptr)
	{
	    LOG_ERROR ((L_log_string,
		"End #7:  SIM_SOR::set_rel_phrases ():  X_oinir_ptr == 0."));
	    return ;
	}

	if (! Y_oinir_ptr)
	{
	    LOG_ERROR ((L_log_string,
		"End #8:  SIM_SOR::set_rel_phrases ():  Y_oinir_ptr == 0."));
	    return ;
	}


	t_boolean found = FALSE;
	if (Z_oinir_ptr)
	{
	    //  This is an associative relationship.
	    //
	    if (p_roip_ptr->get_R2010_obj_in_rel_ID ()
		== Z_oinir_ptr->get_id ())
	    {
		if (p_roip_ptr->get_R2011_obj_in_rel_ID ()
		    == X_oinir_ptr->get_id ())
		{
		    p_roip_ptr->
			set_R2010_phrase (Y_oinir_ptr->text_phrase ());
		    p_roip_ptr->
			set_R2011_phrase (X_oinir_ptr->text_phrase ());
		    found = TRUE;
		}
		else if (p_roip_ptr->get_R2011_obj_in_rel_ID ()
		    == Y_oinir_ptr->get_id ())
		{
		    p_roip_ptr->
			set_R2010_phrase (X_oinir_ptr->text_phrase ());
		    p_roip_ptr->
			set_R2011_phrase (Y_oinir_ptr->text_phrase ());
		    found = TRUE;
		}
	    }
	    else if (p_roip_ptr->get_R2011_obj_in_rel_ID ()
		== Z_oinir_ptr->get_id ())
	    {
		if (p_roip_ptr->get_R2010_obj_in_rel_ID ()
		    == X_oinir_ptr->get_id ())
		{
		    p_roip_ptr->
			set_R2010_phrase (X_oinir_ptr->text_phrase ());
		    p_roip_ptr->
			set_R2011_phrase (Y_oinir_ptr->text_phrase ());
		    found = TRUE;
		}
		else if (p_roip_ptr->get_R2010_obj_in_rel_ID ()
		    == Y_oinir_ptr->get_id ())
		{
		    p_roip_ptr->
			set_R2010_phrase (Y_oinir_ptr->text_phrase ());
		    p_roip_ptr->
			set_R2011_phrase (X_oinir_ptr->text_phrase ());
		    found = TRUE;
		}
	    }
	}


	if (! found)
	{
	    if (p_roip_ptr->get_R2010_obj_in_rel_ID ()
		== X_oinir_ptr->get_id ())
	    {
		if (p_roip_ptr->get_R2011_obj_in_rel_ID ()
		    == Y_oinir_ptr->get_id ())
		{
		    p_roip_ptr->
			set_R2010_phrase (X_oinir_ptr->text_phrase ());
		    p_roip_ptr->
			set_R2011_phrase (Y_oinir_ptr->text_phrase ());
		    found = TRUE;
		}
	    }
	    else if (p_roip_ptr->get_R2010_obj_in_rel_ID ()
		== Y_oinir_ptr->get_id ())
	    {
		if (p_roip_ptr->get_R2011_obj_in_rel_ID ()
		    == X_oinir_ptr->get_id ())
		{
		    p_roip_ptr->
			set_R2010_phrase (Y_oinir_ptr->text_phrase ());
		    p_roip_ptr->
			set_R2011_phrase (X_oinir_ptr->text_phrase ());
		    found = TRUE;
		}
	    }
	}


	if (! found)
	{
	    LOG_ERROR ((L_log_string,
		"End #9:  SIM_SOR::set_rel_phrases ():  R2010_obj_id does not match part or form."));
	    return ;
	}
    }


    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	"End #10:  SIM_SOR::set_rel_phrases ()."));
    return ;
}

int SIM_SOR::get_inst_var_ptr( const vchar *p_inst_name,  
							I_Object_Instance*& p_oinst_ptr, Id& p_obj_id )
{
    I_var* var_ptr = GS_stack::find_var_ptr (p_inst_name);
    if (! var_ptr)
    {
       Description err_msg("Unable to find '");
	   err_msg += p_inst_name;
	   err_msg += "' on stack.";
       GS_ui::inform (UI_INFORM__ERROR, err_msg);
       LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #1 :  SIM_SOR::get_inst_var_ptr()."));
       return FALSE;
    }

    I_object_inst_ref_var* inst1_var_ptr
	= var_ptr->get_object_inst_ref_var_ptr ();
    if (! inst1_var_ptr)
    {
	    Description err_msg("Variable '");
		err_msg += p_inst_name;
	    err_msg += "' is not defined or is not an instance reference variable.";
	GS_ui::inform (UI_INFORM__ERROR, err_msg);
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #2:  SIM_SOR::get_inst_var_ptr ()."));
	return FALSE;
    }
    p_oinst_ptr = inst1_var_ptr->get_oinst_ptr ();
    if (! p_oinst_ptr)
    {
	    Description err_msg("Instance reference variable '");
		err_msg += p_inst_name;
	    err_msg += "' is empty in RELATE statement.";
	GS_ui::inform (UI_INFORM__ERROR, err_msg);
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #3:  SIM_SOR::get_inst_var_ptr ()."));
	return FALSE;
    }
    I_Object* obj1_ptr = p_oinst_ptr->get_Object_R2001_ptr ();
    if (! obj1_ptr)
    {
	GS_ui::inform (UI_INFORM__ERROR, GS_string("Internal Error."));
	LOG_ERROR ((L_log_string,
	    "End #4:  SIM_SOR::get_inst_var_ptr ():  obj1_ptr == 0."));
	return FALSE;
    }
    p_obj_id = obj1_ptr->get_object_ID ();

	GS_UI_INFORM_START (UI_INFORM__COMP)
    Description info_msg("rvalue '");
        info_msg += p_inst_name;
		info_msg += "' (";
        info_msg += inst1_var_ptr->get_data_type_str ();
		info_msg += ") = ";
		info_msg += inst1_var_ptr->get_value_str ();
    GS_UI_INFORM_END (UI_INFORM__COMP, info_msg)

	return TRUE;
}

int SIM_SOR::get_relationship_ptr( const vchar *p_rel_num,  
							Relationship*& p_ooa_rel_ptr, Id& p_rel_id )
{
    // we're passed in a "Rn", but find_relationship_by_number
    // just wants the "n"
    const vchar * rel_num = &p_rel_num[1];

    mc_dbms_Collection <Relationship*>* ooa_rel_coll_ptr
	= GS_find::find_relationship_by_number (rel_num);
    if (! ooa_rel_coll_ptr)
    {
	GS_ui::inform (UI_INFORM__ERROR, GS_string("Internal Error."));
	LOG_ERROR ((L_log_string,
	    "End #8:  SIM_SOR::get_relationship_ptr ():  Creation of Relationship collection in find returned 0."));
	return FALSE;
    }
    if (ooa_rel_coll_ptr->cardinality () < 1)
    {
	//  Relationship not found in OOA DB.
	//
	Description err_msg ("Relationship '");
	err_msg += p_rel_num;
	err_msg += "' not found in OOA DB.";
	GS_ui::inform (UI_INFORM__ERROR, err_msg);
	delete ooa_rel_coll_ptr;
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #9:  SIM_SOR::get_relationship_ptr ()."));
	return FALSE;
    }
    if (ooa_rel_coll_ptr->cardinality () > 1)
    {
	    Description err_msg ("More than one relationship with R number '");
		err_msg += p_rel_num;
	    err_msg += "' exists in OOA DB - picking one at random for use in UNRELATE statement.";
		GS_ui::inform (UI_INFORM__ERROR, err_msg);
		delete ooa_rel_coll_ptr;
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
			"End #10:  SIM_SOR::get_relationship_ptr ()."));
		return FALSE;
    }

    p_ooa_rel_ptr = ooa_rel_coll_ptr->pick ();
    delete ooa_rel_coll_ptr;
    if (! p_ooa_rel_ptr)
    {
	GS_ui::inform (UI_INFORM__ERROR, GS_string("Internal Error."));
	LOG_ERROR ((L_log_string,
	    "End #11:  SIM_SOR::get_relationship_ptr ():  Relationship pointer in collection of 1 element is 0."));
	return FALSE;
    }
    p_rel_id = p_ooa_rel_ptr->get_relationship_id ();

	return TRUE;
}

int SIM_SOR::correlate_object_instances ( Relationship* ooa_rel_ptr, 
	const Id& obj1_id, const Id& obj2_id, const Id& assoc_obj_id,
	const vchar *p_phrase,
    Id& oir1_id,
    t_boolean& is_oir1_many,
    Id& oir2_id,
    t_boolean& is_oir2_many,
    Id& assoc_oir_id,
    t_boolean& is_assoc_oir_many,
	int& p_formalizer)
{
	// p_formalizer return value:
	// -1 error
	// 1 oir1
	// 2 oir2
	// 3 assoc_oir

	p_formalizer = -1;

    if (! ooa_rel_ptr->get_inheritance_relationship_ptr ())
    {
	Simple_relationship* simple_rel_ptr
	    = ooa_rel_ptr->get_simple_relationship_ptr ();
	Composition_relationship* compmc_dbms_rel_ptr
	    = ooa_rel_ptr->get_composition_relationship_ptr ();
	Associative_relationship* assoc_rel_ptr
	    = ooa_rel_ptr->get_associative_relationship_ptr ();
	Object_in_non_inh_relationship* X_oinir_ptr = 0;
	Object_in_non_inh_relationship* Y_oinir_ptr = 0;
	Object_in_non_inh_relationship* Z_oinir_ptr = 0;
	if (simple_rel_ptr)
	{
	    X_oinir_ptr = simple_rel_ptr->get_nth_obj_in_non_inh_rel (1);
	    Y_oinir_ptr = simple_rel_ptr->get_nth_obj_in_non_inh_rel (2);
	}
	else if (compmc_dbms_rel_ptr)
	{
	    X_oinir_ptr = compmc_dbms_rel_ptr->get_object_as_comp_one_end_ptr ();
	    Y_oinir_ptr = compmc_dbms_rel_ptr->get_object_as_comp_other_end_ptr ();
	}
	else if (assoc_rel_ptr)
	{
	    X_oinir_ptr = assoc_rel_ptr->get_object_as_assoc_one_side_ptr ();
	    Y_oinir_ptr = assoc_rel_ptr->get_object_as_assoc_other_side_ptr ();
	    Z_oinir_ptr = assoc_rel_ptr->get_object_as_associator_ptr ();
	}

	if (! X_oinir_ptr)
	{
	    GS_ui::inform (UI_INFORM__ERROR, GS_string("Internal Error."));
	    LOG_ERROR ((L_log_string,
		"End #17:  SIM_SOR::correlate_object_instances ():  X_oinir_ptr == 0."));
	    return FALSE;
	}

	if (! Y_oinir_ptr)
	{
	    GS_ui::inform (UI_INFORM__ERROR, GS_string("Internal Error."));
	    LOG_ERROR ((L_log_string,
		"End #18:  SIM_SOR::correlate_object_instances ():  Y_oinir_ptr == 0."));
	    return FALSE;
	}

	if (Z_oinir_ptr)
	{
	    if (assoc_obj_id != Z_oinir_ptr->object_id ())
	    {
		GS_ui::inform (UI_INFORM__ERROR,
		    GS_string("USING instance reference variable does NOT refer to instance of associative object for relationship specified."));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "End #19:  SIM_SOR::correlate_object_instances ()."));
		return FALSE;
	    }
	    assoc_oir_id = Z_oinir_ptr->get_id ();
	    is_assoc_oir_many = (Z_oinir_ptr->multiplicity () == MANY)
		? TRUE : FALSE;
		p_formalizer = 3;
	}

	if (ooa_rel_ptr->is_reflexive ())
	{
	    //  Match oir IDs with the relationship phrase since
	    //    they can not be differentiated based on the object.
	    //
	    if (X_oinir_ptr->object_id () != Y_oinir_ptr->object_id ())
	    {
		GS_ui::inform (UI_INFORM__ERROR, GS_string("Internal Error."));
		LOG_ERROR ((L_log_string,
		    "End #20:  SIM_SOR::correlate_object_instances ():  ooa_rel_ptr->is_reflexive () == TRUE  but  object_id's do not match."));
		return FALSE;
	    }

	    if (obj1_id != X_oinir_ptr->object_id ())
	    {
		GS_ui::inform (UI_INFORM__ERROR,
		    GS_string("First instance reference NOT an object of relationship specified."));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "End #21:  SIM_SOR::correlate_object_instances ()."));
		return FALSE;
	    }

	    if (obj2_id != X_oinir_ptr->object_id ())
	    {
		GS_ui::inform (UI_INFORM__ERROR,
		    GS_string("Second instance reference NOT an object of relationship specified."));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "End #22:  SIM_SOR::correlate_object_instances ()."));
		return FALSE;
	    }

	    if (X_oinir_ptr->text_phrase () == Y_oinir_ptr->text_phrase ())
	    {
		GS_ui::inform (UI_INFORM__ERROR,
		    GS_string("Ambiguous Reflexive Relationship Specification:  Both relationship phrases match for relationship specified."));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "End #23:  SIM_SOR::correlate_object_instances ()."));
		return FALSE;
	    }

            // the relationship phrases in the OOA/SIM database have no ticks
            // p_phrase has ticks, so add the ticks to the OOA data base info
            Description X_phrase ("'");
			X_phrase += X_oinir_ptr->text_phrase ();
			X_phrase += "'";
            Description Y_phrase ("'");
			Y_phrase += Y_oinir_ptr->text_phrase ();
			Y_phrase += "'";

	    if ( X_phrase == p_phrase )
	    {
		//  Relationship phrase matches the X side so the X side
		//    is made to correspond to the 2nd inst ref var.
		//
		oir1_id = Y_oinir_ptr->get_id ();
		is_oir1_many = (Y_oinir_ptr->multiplicity () == MANY)
		    ? TRUE : FALSE;
		if ( Y_oinir_ptr->get_object_as_simp_form_ptr() )
		{
			p_formalizer = 1;
		}
		oir2_id = X_oinir_ptr->get_id ();
		is_oir2_many = (X_oinir_ptr->multiplicity () == MANY)
		    ? TRUE : FALSE;
		if ( X_oinir_ptr->get_object_as_simp_form_ptr() )
		{
			p_formalizer = 2;
		}
	    }
	    else if ( Y_phrase == p_phrase )
	    {
		//  Relationship phrase matches the Y side so the Y side
		//    is made to correspond to the 2nd inst ref var.
		//
		oir1_id = X_oinir_ptr->get_id ();
		is_oir1_many = (X_oinir_ptr->multiplicity () == MANY)
		    ? TRUE : FALSE;
		if ( X_oinir_ptr->get_object_as_simp_form_ptr() )
		{
			p_formalizer = 1;
		}
		oir2_id = Y_oinir_ptr->get_id ();
		is_oir2_many = (Y_oinir_ptr->multiplicity () == MANY)
		    ? TRUE : FALSE;
		if ( Y_oinir_ptr->get_object_as_simp_form_ptr() )
		{
			p_formalizer = 2;
		}
	    }
	    else
	    {
		GS_ui::inform (UI_INFORM__ERROR,
		    GS_string("Relationship Phrase in RELATE statement does NOT match either phrase of relationship specified."));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "End #24:  SIM_SOR::correlate_object_instances ()."));
		return FALSE;
	    }
	}
	else
	{
	    //  Match oir IDs with the instance references since
	    //    they can be differentiated based on the object.
	    //
	    if (obj1_id == X_oinir_ptr->object_id ())
	    {
		if (obj2_id == Y_oinir_ptr->object_id ())
		{
		    oir1_id = X_oinir_ptr->get_id ();
		    is_oir1_many = (X_oinir_ptr->multiplicity () == MANY)
			? TRUE : FALSE;
			if ( X_oinir_ptr->get_object_as_simp_form_ptr() )
			{
				p_formalizer = 1;
			}
		    oir2_id = Y_oinir_ptr->get_id ();
		    is_oir2_many = (Y_oinir_ptr->multiplicity () == MANY)
			? TRUE : FALSE;
			if ( Y_oinir_ptr->get_object_as_simp_form_ptr() )
			{
				p_formalizer = 2;
			}
		}
		else
		{
		    GS_ui::inform (UI_INFORM__ERROR,
			GS_string("Second instance reference NOT an object of relationship specified."));
		    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
			"End #25:  SIM_SOR::correlate_object_instances ()."));
		    return FALSE;
		}
	    }
	    else if (obj1_id == Y_oinir_ptr->object_id ())
	    {
		if (obj2_id == X_oinir_ptr->object_id ())
		{
		    oir1_id = Y_oinir_ptr->get_id ();
		    is_oir1_many = (Y_oinir_ptr->multiplicity () == MANY)
			? TRUE : FALSE;
			if ( Y_oinir_ptr->get_object_as_simp_form_ptr() )
			{
				p_formalizer = 1;
			}
		    oir2_id = X_oinir_ptr->get_id ();
		    is_oir2_many = (X_oinir_ptr->multiplicity () == MANY)
			? TRUE : FALSE;
			if ( X_oinir_ptr->get_object_as_simp_form_ptr() )
			{
				p_formalizer = 2;
			}
		}
		else
		{
		    GS_ui::inform (UI_INFORM__ERROR,
			GS_string("Second instance reference NOT an object of relationship specified."));
		    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
			"End #26:  SIM_SOR::correlate_object_instances ()."));
		    return FALSE;
		}
	    }
	    else
	    {
		GS_ui::inform (UI_INFORM__ERROR,
		    GS_string("First instance reference NOT an object of relationship specified."));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "End #27:  SIM_SOR::correlate_object_instances ()."));
		return FALSE;
	    }
	}
    }
    else
    {
	Inheritance_relationship* inher_rel_ptr
	    = ooa_rel_ptr->get_inheritance_relationship_ptr ();
	Object_as_supertype* supertype_ptr
	    = inher_rel_ptr->get_object_as_supertype_ptr ();
	if (obj1_id == supertype_ptr->object_id ())
	{
		p_formalizer = 2;
	    t_boolean found = FALSE;
	    Object_as_subtype* subtype_ptr;
	    FOR_ALL_ELEMENTS
		(subtype_ptr,
		Object_as_subtype,
		inher_rel_ptr->get_obj_as_subtype_coll_ptr (),
		subtype_cursor)
	    {
		if (obj2_id == subtype_ptr->object_id ())
		{
		    oir1_id = supertype_ptr->get_id ();
		    is_oir1_many = FALSE;
		    oir2_id = subtype_ptr->get_id ();
		    is_oir2_many = FALSE;
		    found = TRUE;
		}
	    }
	    if (! found)
	    {
		GS_ui::inform (UI_INFORM__ERROR,
		    GS_string("Second instance reference variable does not refer to the subtype object of relationship specified."));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "End #28:  SIM_SOR::correlate_object_instances ()."));
		return FALSE;
	    }
	}
	else if (obj2_id == supertype_ptr->object_id ())
	{
		p_formalizer = 1;
	    t_boolean found = FALSE;
	    Object_as_subtype* subtype_ptr;
	    FOR_ALL_ELEMENTS
		(subtype_ptr,
		Object_as_subtype,
		inher_rel_ptr->get_obj_as_subtype_coll_ptr (),
		subtype_cursor)
	    {
		if (obj1_id == subtype_ptr->object_id ())
		{
		    oir1_id = subtype_ptr->get_id ();
		    is_oir1_many = FALSE;
		    oir2_id = supertype_ptr->get_id ();
		    is_oir2_many = FALSE;
		    found = TRUE;
		}
	    }
	    if (! found)
	    {
		GS_ui::inform (UI_INFORM__ERROR,
		    GS_string("First instance reference variable does not refer to the subtype object of relationship specified."));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "End #29:  SIM_SOR::correlate_object_instances ()."));
		return FALSE;
	    }
	}
	else
	{
	    GS_ui::inform (UI_INFORM__ERROR,
		GS_string("Neither instance reference variable refers to the supertype object of relationship specified."));
	    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		"End #30:  SIM_SOR::correlate_object_instances ()."));
	    return FALSE;
	}
    }

	return TRUE;
}

void check_and_delete_roip (I_Related_Object_Instance_Pair* roip_ptr,
  I_Object_Instance* oinst1_ptr,
  I_Object_Instance* oinst2_ptr,
  I_Object_Instance* assoc_oinst_ptr,
  const Id& oir1_id,
  const Id& oir2_id,
  const Id& assoc_oir_id,
  t_boolean is_assoc_oir_many,
  int& num_found)
{
	if (! assoc_oinst_ptr)
	{
		mc_dbms_Collection<I_Related_Object_Instance_Pair*>*
			aroip_coll_ptr
			= I_Related_Object_Instance_Pair::
			find_Related_Object_Instance_Pair_by_rel_inst_ID
			(GS_gen_sim_db_ptr, roip_ptr->get_rel_inst_ID ());
		if (aroip_coll_ptr->cardinality () > 1)
		{
			GS_ui::inform (UI_INFORM__ERROR,
				GS_string("This relationship instance was formalized with an associative object instance but is being UNRELATED without the USING clause.  Deleting relationship instance anyway."));
		}
		I_Related_Object_Instance_Pair* aroip_ptr;
		FOR_ALL_ELEMENTS_SAFE
			(aroip_ptr,
			I_Related_Object_Instance_Pair,
			aroip_coll_ptr,
			aroip_cursor2)
		{
			delete aroip_ptr;
		}
		delete aroip_coll_ptr;
		num_found++;
	}
	else
	{
		t_boolean found_1_2 = FALSE;
		t_boolean found_1_assoc = FALSE;
		t_boolean found_2_assoc = FALSE;
		mc_dbms_Collection<I_Related_Object_Instance_Pair*>*
			aroip_coll_ptr
			= I_Related_Object_Instance_Pair::
			find_Related_Object_Instance_Pair_by_rel_inst_ID
			(GS_gen_sim_db_ptr, roip_ptr->get_rel_inst_ID ());
		I_Related_Object_Instance_Pair* aroip_ptr;
		FOR_ALL_ELEMENTS_SAFE
			(aroip_ptr,
			I_Related_Object_Instance_Pair,
			aroip_coll_ptr,
			aroip_cursor1)
		{
			if (roip_ptr == aroip_ptr)
			{
				found_1_2 = TRUE;
			}
			if ((oinst1_ptr
				== aroip_ptr->get_Object_Instance_R2010_ptr ())
				&&
				(assoc_oinst_ptr
				== aroip_ptr->get_Object_Instance_R2011_ptr ()))
			{
				if (oir1_id
					== aroip_ptr->get_R2010_obj_in_rel_ID ())
				{
					if (assoc_oir_id ==
						aroip_ptr->get_R2011_obj_in_rel_ID ())
					{
						found_1_assoc = TRUE;
					}
				}
			}
			if ((oinst1_ptr
				== aroip_ptr->get_Object_Instance_R2011_ptr ())
				&&
				(assoc_oinst_ptr
				== aroip_ptr->get_Object_Instance_R2010_ptr ()))
			{
				if (oir1_id
					== aroip_ptr->get_R2011_obj_in_rel_ID ())
				{
					if (assoc_oir_id ==
						aroip_ptr->get_R2010_obj_in_rel_ID ())
					{
						found_1_assoc = TRUE;
					}
				}
			}
			if ((oinst2_ptr
				== aroip_ptr->get_Object_Instance_R2010_ptr ())
				&&
				(assoc_oinst_ptr
				== aroip_ptr->get_Object_Instance_R2011_ptr ()))
			{
				if (oir2_id
					== aroip_ptr->get_R2010_obj_in_rel_ID ())
				{
					if (assoc_oir_id ==
						aroip_ptr->get_R2011_obj_in_rel_ID ())
					{
						found_2_assoc = TRUE;
					}
				}
			}
			if ((oinst2_ptr
				== aroip_ptr->get_Object_Instance_R2011_ptr ())
				&&
				(assoc_oinst_ptr
				== aroip_ptr->get_Object_Instance_R2010_ptr ()))
			{
				if (oir2_id
					== aroip_ptr->get_R2011_obj_in_rel_ID ())
				{
					if (assoc_oir_id ==
						aroip_ptr->get_R2010_obj_in_rel_ID ())
					{
						found_2_assoc = TRUE;
					}
				}
			}
		}
		
		if (found_1_2 && found_1_assoc && found_2_assoc)
		{
			FOR_ALL_ELEMENTS_SAFE
				(aroip_ptr,
				I_Related_Object_Instance_Pair,
				aroip_coll_ptr,
				aroip_cursor2)
			{
				delete aroip_ptr;
			}
			num_found++;
		}
		else if (found_1_2 && (! found_1_assoc)
			&& (! found_2_assoc) && (! is_assoc_oir_many || (num_found < 1)))
		{
			GS_ui::inform (UI_INFORM__ERROR,
				GS_string("This relationship instance was formalized without an associative object instance but is being UNRELATED with the USING clause.  Deleting relationship instance anyway."));
			FOR_ALL_ELEMENTS_SAFE
				(aroip_ptr,
				I_Related_Object_Instance_Pair,
				aroip_coll_ptr,
				aroip_cursor3)
			{
				delete aroip_ptr;
			}
			num_found++;
		}
		
		delete aroip_coll_ptr;
  }
}

static void unrelate_obj_inst ( 
  I_Object_Instance* oinst1_ptr,
  I_Object_Instance* oinst2_ptr,
  I_Object_Instance* assoc_oinst_ptr,
  const Id& oir1_id,
  const Id& oir2_id,
  const Id& assoc_oir_id,
  t_boolean is_assoc_oir_many,
  int& num_found)
{
    I_Related_Object_Instance_Pair* roip_ptr;
    FOR_ALL_ELEMENTS_SAFE
	(roip_ptr,
	I_Related_Object_Instance_Pair,
	oinst1_ptr->get_Related_Object_Instance_Pair_R2010_coll_ptr (),
	roip_cursor_1_2010)
    {
      if (oir1_id == roip_ptr->get_R2010_obj_in_rel_ID ())
      {
        if (oinst2_ptr == roip_ptr->get_Object_Instance_R2011_ptr ())
        {
          if (oir2_id == roip_ptr->get_R2011_obj_in_rel_ID ())
          {
            check_and_delete_roip( roip_ptr,
               oinst1_ptr, oinst2_ptr, assoc_oinst_ptr,
               oir1_id, oir2_id, assoc_oir_id, is_assoc_oir_many, num_found);
          }
        }
      }
    }
    FOR_ALL_ELEMENTS_SAFE
	(roip_ptr,
	I_Related_Object_Instance_Pair,
	oinst1_ptr->get_Related_Object_Instance_Pair_R2011_coll_ptr (),
	roip_cursor_1_2011)
    {
      if (oir1_id == roip_ptr->get_R2011_obj_in_rel_ID ())
      {
        if (oinst2_ptr == roip_ptr->get_Object_Instance_R2010_ptr ())
	      {
          if (oir2_id == roip_ptr->get_R2010_obj_in_rel_ID ())
          {
            check_and_delete_roip( roip_ptr,
               oinst1_ptr, oinst2_ptr, assoc_oinst_ptr,
               oir1_id, oir2_id, assoc_oir_id, is_assoc_oir_many, num_found);
          }
        }
      }
    }
    FOR_ALL_ELEMENTS_SAFE
	(roip_ptr,
	I_Related_Object_Instance_Pair,
	oinst2_ptr->get_Related_Object_Instance_Pair_R2010_coll_ptr (),
	roip_cursor_2_2010)
    {
      if (oir2_id == roip_ptr->get_R2010_obj_in_rel_ID ())
      {
	      if (oinst1_ptr == roip_ptr->get_Object_Instance_R2011_ptr ())
	      {
          if (oir1_id == roip_ptr->get_R2011_obj_in_rel_ID ())
          {
            check_and_delete_roip( roip_ptr,
               oinst1_ptr, oinst2_ptr, assoc_oinst_ptr,
               oir1_id, oir2_id, assoc_oir_id, is_assoc_oir_many, num_found);
          }
        }
      }
    }
    FOR_ALL_ELEMENTS_SAFE
	(roip_ptr,
	I_Related_Object_Instance_Pair,
	oinst2_ptr->get_Related_Object_Instance_Pair_R2011_coll_ptr (),
	roip_cursor_2_2011)
    {
      if (oir2_id == roip_ptr->get_R2011_obj_in_rel_ID ())
      {
        if (oinst1_ptr == roip_ptr->get_Object_Instance_R2010_ptr ())
        {
          if (oir1_id == roip_ptr->get_R2010_obj_in_rel_ID ())
          {
            check_and_delete_roip( roip_ptr,
               oinst1_ptr, oinst2_ptr, assoc_oinst_ptr,
               oir1_id, oir2_id, assoc_oir_id, is_assoc_oir_many, num_found);
          }
        }
      }
    }
}

void SIM_SOR::find_other_relationships_formalized ( I_Object* p_obj_ptr, Relationship* p_ooa_rel_ptr,
        mc_dbms_Set<Referential_attribute*>& p_ref_attr_coll )
{
    mc_dbms_Set<Object_in_relationship*> other_rel_coll;

	Object* ooa_obj_ptr = GS_find::find_object_by_id( p_obj_ptr->get_object_ID() );

	// create a list of other relationships that this object formalizes
	// and find the attributes that formalize this relationship
	// vis:   
	//   select many other_rel_coll related by ooa_obj_ptr->R_OIR[R201]->R_RGO[R203] 
	//        where selected.Rel_ID != p_rel;
	//   select many p_ref_attr_coll related by ooa_obj_ptr->R_OIR[R201]->R_RGO[R203]->O_REF[R111]->O_RATTR[R108]
	//        where selected.Rel_ID == p_rel
	//
    mc_dbms_Set< Object_in_relationship *> *object_rels = 
            ooa_obj_ptr->get_obj_in_rel_coll_ptr();
	Object_in_relationship* oir_ptr;
	FOR_ALL_ELEMENTS
	(oir_ptr,
	Object_in_relationship,
	object_rels,
	oir_cursor_1)
	{
		if ( oir_ptr->get_object_referring_ptr() )
		{
			Relationship* ref_rel_ptr
			= oir_ptr->get_relationship_ptr ();
			if (ref_rel_ptr->get_rel_number () != p_ooa_rel_ptr->get_rel_number())
			{
				other_rel_coll.insert( oir_ptr );
			}
			else
			{
				mc_dbms_List< Attr_ref_in_object * > * attr_ref_coll_ptr = 
					oir_ptr->get_object_referring_ptr()->get_attr_ref_in_obj_coll_ptr();
				Attr_ref_in_object* aref_ptr;
				FOR_ALL_ELEMENTS
				(aref_ptr,
				Attr_ref_in_object,
				attr_ref_coll_ptr,
				aref_cursor_1)
				{
					Referential_attribute* ref_attr_ptr = aref_ptr->get_ref_attr_ptr();
					p_ref_attr_coll.insert( ref_attr_ptr );
				}

                delete attr_ref_coll_ptr;
			}
		}
	}
    delete object_rels;

   	// sift through the other relationships to find any referential attributes that
	//  the other relationships and this relationship have in common
	// in other words, remove the ref attrs from the collection that don't formalize
	//  one of the other relationships

	FOR_ALL_ELEMENTS
	(oir_ptr,
	Object_in_relationship,
	&other_rel_coll,
	oir_cursor_2)
	{
		mc_dbms_List< Attr_ref_in_object * > * attr_ref_coll_ptr = 
			oir_ptr->get_object_referring_ptr()->get_attr_ref_in_obj_coll_ptr();
		Attr_ref_in_object* aref_ptr;
		FOR_ALL_ELEMENTS
		(aref_ptr,
		Attr_ref_in_object,
		attr_ref_coll_ptr,
		aref_cursor_1)
		{
			t_boolean found = FALSE;
			Referential_attribute* attr_ptr;
			FOR_ALL_ELEMENTS
			(attr_ptr,
			Referential_attribute,
			&p_ref_attr_coll,
			attr_cursor_2)
			{
				if ( attr_ptr->get_id() == 
					 aref_ptr->get_ref_attr_ptr()->get_id() )
				{
					found = TRUE;
				}
			}
			if ( !found )
			{
				p_ref_attr_coll.remove( aref_ptr->get_ref_attr_ptr() );
			}
		}
        delete attr_ref_coll_ptr;
	}
}

void SIM_SOR::do_unrelate_statement (     I_Object_Instance* oinst1_ptr,
    const Id& obj1_id,
    I_Object_Instance* oinst2_ptr,
	const Id& obj2_id,
    I_Object_Instance* assoc_oinst_ptr,
    const Id& assoc_obj_id,
    Relationship* ooa_rel_ptr,
    Relationship* previous_ooa_rel_ptr,
	const vchar* p_phrase )
{
    //  Correlate the oinst's specified in the UNRELATE statement with the
    //    Object in Relationships from the OOA DB.
    //
    Id oir1_id;
    t_boolean is_oir1_many = FALSE;
    Id oir2_id;
    t_boolean is_oir2_many = FALSE;
    Id assoc_oir_id;
    t_boolean is_assoc_oir_many = FALSE;
    int formalizer;
    if ( ! correlate_object_instances ( ooa_rel_ptr, 
              obj1_id, obj2_id, assoc_obj_id, p_phrase,
              oir1_id, is_oir1_many, oir2_id, is_oir2_many,
              assoc_oir_id, is_assoc_oir_many, formalizer ) )
	{
		return ;
	}

	I_Object* obj_ptr = 0;
	if ( formalizer == 1 )
	{
        obj_ptr = oinst1_ptr->get_Object_R2001_ptr ();
	}
	else if ( formalizer == 2 )
	{
        obj_ptr = oinst2_ptr->get_Object_R2001_ptr ();
	}
	else if ( formalizer == 3 )
	{
        obj_ptr = assoc_oinst_ptr->get_Object_R2001_ptr ();
	}

	if ( obj_ptr )
	{
        mc_dbms_Set<Referential_attribute*> ref_attr_coll;
        find_other_relationships_formalized ( obj_ptr, ooa_rel_ptr, ref_attr_coll );

		// ref_attr_col now contains the referential attributes for 
		// the other relationships that need to be unrelated.
		Referential_attribute* attr_ptr;
		FOR_ALL_ELEMENTS_SAFE
		(attr_ptr,
		Referential_attribute,
		&ref_attr_coll,
		attr_cursor_3)
		{
			Attr_ref_in_object *aref_ptr;
			FOR_ALL_ELEMENTS_SAFE
			(aref_ptr,
			Attr_ref_in_object,
			attr_ptr->get_attr_ref_in_obj_coll_ptr(),
			aref_cursor_1)
			{
                Object_referring *rgo_ptr = 
                    aref_ptr->get_object_referring_ptr ();
                if ( rgo_ptr )
                {
				    Relationship* other_ooa_rel_ptr = 
					    rgo_ptr->get_relationship_ptr();
				    if ( (other_ooa_rel_ptr->get_rel_number() != ooa_rel_ptr->get_rel_number() && previous_ooa_rel_ptr == 0) ||
					     (other_ooa_rel_ptr->get_rel_number() != ooa_rel_ptr->get_rel_number() && previous_ooa_rel_ptr != 0 &&
					      other_ooa_rel_ptr->get_rel_number() != previous_ooa_rel_ptr->get_rel_number()) )
				    {
					    Description other_rnum_str("R");
					    vchar vchar_rnum_str[8];
					    vcharCopyScribed( 
						    vcharScribeFormatLiteral ("%d", other_ooa_rel_ptr->get_rel_number() ),
						    vchar_rnum_str );
					    other_rnum_str += vchar_rnum_str;

					    I_Object_Instance* this_oinst_ptr = 0;
				        Id this_obj_id;
					    I_Object_Instance* other_oinst_ptr = 0;
				        Id other_obj_id;
					    I_Object_Instance* other_assoc_oinst_ptr = 0;
					    Id other_assoc_obj_id;
					    Description phrase_str;

					    if ( formalizer == 1 )
					    {
						    this_oinst_ptr = oinst1_ptr;
						    this_obj_id = obj1_id;
					    }
					    else if ( formalizer == 2 )
					    {
						    this_oinst_ptr = oinst2_ptr;
						    this_obj_id = obj2_id;
					    }
					    else if ( formalizer == 3 )
					    {
						    this_oinst_ptr = assoc_oinst_ptr;
						    this_obj_id = assoc_obj_id;
					    }

					    if ( this_oinst_ptr )
					    {
						    Associative_relationship* assoc_rel_ptr
						        = other_ooa_rel_ptr->get_associative_relationship_ptr ();

						    I_Related_Object_Instance_Pair *roip_ptr;
						    FOR_ALL_ELEMENTS
						    (roip_ptr,
						    I_Related_Object_Instance_Pair,
						    this_oinst_ptr->get_Related_Object_Instance_Pair_R2010_coll_ptr (),
						    sim_roip_cursor1)
						    {
							    if (other_rnum_str == roip_ptr->get_Rnum_str ())
							    {
								    if ( assoc_rel_ptr )
								    {
									    if ( roip_ptr->get_R2011_obj_in_rel_ID() == 
										      assoc_rel_ptr->get_object_as_associator_ptr()->object_id() )
									    {
										    other_assoc_oinst_ptr =
											    roip_ptr->get_Object_Instance_R2011_ptr();
										    other_assoc_obj_id = 
											    other_assoc_oinst_ptr->get_Object_R2001_ptr ()->get_object_ID();
									    }
									    else
									    {
										    phrase_str = roip_ptr->get_R2011_phrase ();
										    other_oinst_ptr =
											    roip_ptr->get_Object_Instance_R2011_ptr();
										    other_obj_id = other_oinst_ptr->get_Object_R2001_ptr ()->get_object_ID();
									    }
								    }
								    else
								    {
									    phrase_str = roip_ptr->get_R2011_phrase ();
									    other_oinst_ptr =
										    roip_ptr->get_Object_Instance_R2011_ptr();
									    other_obj_id = other_oinst_ptr->get_Object_R2001_ptr ()->get_object_ID();
								    }
							    }
						    }

						    do_unrelate_statement (this_oinst_ptr, this_obj_id,
						      other_oinst_ptr, other_obj_id,
						      other_assoc_oinst_ptr, other_assoc_obj_id,
						      other_ooa_rel_ptr, ooa_rel_ptr, phrase_str.char_ptr() );
					    }
				    }
                }
			}
		}
	}

	//  Finally, delete the relationship instances.
    //
    int num_found = 0;
    unrelate_obj_inst( oinst1_ptr, oinst2_ptr, assoc_oinst_ptr,
       oir1_id, oir2_id, assoc_oir_id, is_assoc_oir_many, num_found);

    if (num_found < 1)
    {
	GS_ui::inform (UI_INFORM__ERROR,
	    GS_string("Relationship instance to UNRELATE NOT found."));
    }
    else if (num_found > 1)
    {
	GS_ui::inform (UI_INFORM__ERROR,
	    GS_string("More than one relationship instance found and unrelated."));
    }

}

void SIM_SOR::do_relate_statement (   
	const vchar *p_inst1_name, 
    const vchar *p_inst2_name, 
    const vchar *p_assoc_name, 
    I_Object_Instance* oinst1_ptr,
    const Id& obj1_id,
    I_Object_Instance* oinst2_ptr,
	const Id& obj2_id,
    I_Object_Instance* assoc_oinst_ptr,
    const Id& assoc_obj_id,
    Relationship* ooa_rel_ptr,
    Relationship* previous_ooa_rel_ptr,
	const vchar* p_rel,
	const vchar* p_phrase )
{
    //  Correlate the oinst's specified in the RELATE statement with the
    //    Object in Relationships from the OOA DB.
    //
    Id oir1_id;
    t_boolean is_oir1_many = FALSE;
    Id oir2_id;
    t_boolean is_oir2_many = FALSE;
    Id assoc_oir_id;
    t_boolean is_assoc_oir_many = FALSE;
	int formalizer;
    if ( ! correlate_object_instances ( ooa_rel_ptr, 
              obj1_id, obj2_id, assoc_obj_id, p_phrase,
              oir1_id, is_oir1_many, oir2_id, is_oir2_many,
              assoc_oir_id, is_assoc_oir_many, formalizer ) )
	{
		return ;
	}

    //  Check to see if this relationship instance between the object instances
    //    which are about to be related already exists.
    //
    if (! check_object_instance_relationship (p_inst1_name, p_inst2_name, p_assoc_name,
			oinst1_ptr, oinst2_ptr, assoc_oinst_ptr,
			oir1_id, is_oir1_many, oir2_id, is_oir2_many,
			assoc_oir_id, is_assoc_oir_many) )
	{
		return;
	}


	Id rel_inst_id;
    I_Related_Object_Instance_Pair* roip1_ptr = 0;
    I_Related_Object_Instance_Pair* roip2_ptr = 0;

    if (p_assoc_name != 0)
    {
	//  Create the 2 associative related object pairs - one between the
	//    first object instance and the associative object instance and the
	//    other between the second object instance and the assoc inst.
	//
	roip1_ptr = I_Related_Object_Instance_Pair::create (GS_gen_sim_db_ptr);
	if (! roip1_ptr)
	{
	    GS_ui::inform (UI_INFORM__ERROR, GS_string("Internal Error."));
	    LOG_ERROR ((L_log_string,
		"End #47:  SIM_SOR::interpret_relate_statement ():  Unable to create I_Related_Object_Instance_Pair instance."));
	    return ;
	}
	rel_inst_id = roip1_ptr->get_rel_inst_ID ();
	roip1_ptr->set_relationship_ID (ooa_rel_ptr->get_relationship_id ());
	roip1_ptr->set_Rnum_str (p_rel);
	roip1_ptr->relate_R2010 (oinst1_ptr);
	roip1_ptr->set_R2010_obj_in_rel_ID (oir1_id);
	roip1_ptr->relate_R2011 (assoc_oinst_ptr);
	roip1_ptr->set_R2011_obj_in_rel_ID (assoc_oir_id);
	set_rel_phrases (roip1_ptr, ooa_rel_ptr);

	roip2_ptr = I_Related_Object_Instance_Pair::create (GS_gen_sim_db_ptr);
	if (! roip2_ptr)
	{
	    delete roip1_ptr;
	    GS_ui::inform (UI_INFORM__ERROR, GS_string("Internal Error."));
	    LOG_ERROR ((L_log_string,
		"End #48:  SIM_SOR::interpret_relate_statement ():  Unable to create I_Related_Object_Instance_Pair instance."));
	    return ;
	}
	roip2_ptr->set_rel_inst_ID (rel_inst_id);
	roip2_ptr->set_relationship_ID (ooa_rel_ptr->get_relationship_id ());
	roip2_ptr->set_Rnum_str (p_rel);
	roip2_ptr->relate_R2010 (oinst2_ptr);
	roip2_ptr->set_R2010_obj_in_rel_ID (oir2_id);
	roip2_ptr->relate_R2011 (assoc_oinst_ptr);
	roip2_ptr->set_R2011_obj_in_rel_ID (assoc_oir_id);
	set_rel_phrases (roip2_ptr, ooa_rel_ptr);
    }


    //  Relate named instances.
    //
    I_Related_Object_Instance_Pair* roip_ptr
	     = I_Related_Object_Instance_Pair::create (GS_gen_sim_db_ptr);
    if (! roip_ptr)
    {
	delete roip1_ptr;
	delete roip2_ptr;
	GS_ui::inform (UI_INFORM__ERROR, GS_string("Internal Error."));
	LOG_ERROR ((L_log_string,
	    "End #49:  SIM_SOR::interpret_relate_statement ():  Unable to create I_Related_Object_Instance_Pair instance."));
	return ;
    }
    if (p_assoc_name != 0)
    {
	roip_ptr->set_rel_inst_ID (rel_inst_id);
    }
    roip_ptr->set_relationship_ID (ooa_rel_ptr->get_relationship_id ());
    roip_ptr->set_Rnum_str (p_rel);
    roip_ptr->relate_R2010 (oinst1_ptr);
    roip_ptr->set_R2010_obj_in_rel_ID (oir1_id);
    roip_ptr->relate_R2011 (oinst2_ptr);
    roip_ptr->set_R2011_obj_in_rel_ID (oir2_id);
    set_rel_phrases (roip_ptr, ooa_rel_ptr);

	// Now check if any other relationships can be formalized due to
	// combined referentials.

	I_Object* obj_ptr = 0;
	if ( formalizer == 1 )
	{
        obj_ptr = oinst1_ptr->get_Object_R2001_ptr ();
	}
	else if ( formalizer == 2 )
	{
        obj_ptr = oinst2_ptr->get_Object_R2001_ptr ();
	}
	else if ( formalizer == 3 )
	{
        obj_ptr = assoc_oinst_ptr->get_Object_R2001_ptr ();
	}

	if ( obj_ptr )
	{
        mc_dbms_Set<Referential_attribute*> ref_attr_coll;
		find_other_relationships_formalized ( obj_ptr, ooa_rel_ptr, ref_attr_coll );

		// ref_attr_col now contains the referential attributes for 
		// the other relationships that need to be related if possible.
		Referential_attribute* attr_ptr;
		FOR_ALL_ELEMENTS_SAFE
		(attr_ptr,
		Referential_attribute,
		&ref_attr_coll,
		attr_cursor_3)
		{
			Attr_ref_in_object *aref_ptr;
			FOR_ALL_ELEMENTS_SAFE
			(aref_ptr,
			Attr_ref_in_object,
			attr_ptr->get_attr_ref_in_obj_coll_ptr(),
			aref_cursor_1)
			{
                Object_referring *rgo_ptr = 
                    aref_ptr->get_object_referring_ptr ();
                if ( rgo_ptr )
                {
				    Relationship* other_ooa_rel_ptr = 
					    rgo_ptr->get_relationship_ptr();
				    if ( (other_ooa_rel_ptr->get_rel_number() != ooa_rel_ptr->get_rel_number() && previous_ooa_rel_ptr == 0) ||
					     (other_ooa_rel_ptr->get_rel_number() != ooa_rel_ptr->get_rel_number() && previous_ooa_rel_ptr != 0 &&
					      other_ooa_rel_ptr->get_rel_number() != previous_ooa_rel_ptr->get_rel_number()) )
				    {
					    Description other_rnum_str("R");
					    vchar vchar_rnum_str[8];
					    vcharCopyScribed( 
						    vcharScribeFormatLiteral ("%d", other_ooa_rel_ptr->get_rel_number() ),
						    vchar_rnum_str );
					    other_rnum_str += vchar_rnum_str;

					    Description phrase_str;
					    I_Object_Instance*  other_oinst_ptr = 0;
					    I_Object_Instance*  this_oinst_ptr = 0;
					    Id this_obj_id;
					    if ( formalizer == 1 )
					    {
						    // find the other object instance we should be related to
						    other_oinst_ptr =
							    find_related_instance( oinst1_ptr, other_ooa_rel_ptr, phrase_str );
						    this_oinst_ptr = oinst1_ptr;
						    this_obj_id = obj1_id;
					    }
					    else if ( formalizer == 2 )
					    {
						    // find the other object instance we should be related to
						    other_oinst_ptr =
							    find_related_instance( oinst2_ptr, other_ooa_rel_ptr, phrase_str );
						    this_oinst_ptr = oinst2_ptr;
						    this_obj_id = obj2_id;
					    }
					    else if ( formalizer == 3 )
					    {
						    // find the other object instance we should be related to
						    other_oinst_ptr =
							    find_related_instance( assoc_oinst_ptr, other_ooa_rel_ptr, phrase_str );
						    this_oinst_ptr = assoc_oinst_ptr;
						    this_obj_id = assoc_obj_id;
					    }

					    if ( other_oinst_ptr )
					    {
						    Associative_relationship* assoc_rel_ptr
							    = other_ooa_rel_ptr->get_associative_relationship_ptr ();
						    I_Object_Instance* other_assoc_oinst_ptr = 0;
						    Id other_assoc_obj_id;
						    Description other_assoc_name;
						    if (assoc_rel_ptr)
						    {
							    // find the associative instance to relate the two instances
							    other_assoc_oinst_ptr =
								    find_related_assoc_instance( this_oinst_ptr, other_oinst_ptr, assoc_rel_ptr );

							    if ( other_assoc_oinst_ptr )
							    {
								    other_assoc_name = "<Temporary>";
							    }
						    }
   						    
						    Id other_obj_id = other_oinst_ptr->get_Object_R2001_ptr ()->get_object_ID();
						    vchar * other_assoc_name_ptr = 0;
						    if ( other_assoc_name.length() != 0 )
						    {
							    other_assoc_name_ptr = (vchar*) other_assoc_name.char_ptr(); 
						    }

						    do_relate_statement (
						      p_inst1_name, p_inst2_name, other_assoc_name_ptr, 
						      this_oinst_ptr, this_obj_id,
						      other_oinst_ptr, other_obj_id,
						      other_assoc_oinst_ptr, other_assoc_obj_id,
						      other_ooa_rel_ptr, ooa_rel_ptr, other_rnum_str.char_ptr(), phrase_str.char_ptr() );
					    }
				    }
                }
			}
		}
	}
}

I_Object_Instance* SIM_SOR::find_related_instance( 
		I_Object_Instance* oinst_ptr, Relationship* ooa_rel_ptr, 
		Description& phrase_str )
{
	I_Object_Instance* ret_val = 0;

	// first get the referential attributes that formalize the relationship
	mc_dbms_Set<Attr_ref_in_object*> ref_attr_coll;

	Object_in_relationship* oir_ptr;
	FOR_ALL_ELEMENTS
	(oir_ptr,
	Object_in_relationship,
	ooa_rel_ptr->get_obj_in_rel_coll_ptr (),
	oir_cursor_1)
	{
		if ( oir_ptr->get_object_referring_ptr() )
		{
			mc_dbms_List< Attr_ref_in_object * > * attr_ref_coll_ptr = 
				oir_ptr->get_object_referring_ptr()->get_attr_ref_in_obj_coll_ptr();
			Attr_ref_in_object* aref_ptr;
			FOR_ALL_ELEMENTS
			(aref_ptr,
			Attr_ref_in_object,
			attr_ref_coll_ptr,
			aref_cursor_1)
			{
				//Referential_attribute* ref_attr_ptr = aref_ptr->get_ref_attr_ptr();
				ref_attr_coll.insert( aref_ptr );
			}
            delete attr_ref_coll_ptr;
		}
	}

	FOR_ALL_ELEMENTS
	(oir_ptr,
	Object_in_relationship,
	ooa_rel_ptr->get_obj_in_rel_coll_ptr (),
	oir_cursor_2)
	{
		if ( oir_ptr->get_object_referred_to_ptr() )
		{
		    I_Object* sim_obj_ptr = I_Object::find_Object_by_object_ID
				(GS_gen_sim_db_ptr, 
				 oir_ptr->get_object_referred_to_ptr()->object_id() );

			// sim_obj_ptr may be zero if there are no instances created yet
			if ( sim_obj_ptr )
			{
				mc_dbms_List<I_Object_Instance*> *obj_inst_coll_ptr = 
					sim_obj_ptr->get_Object_Instance_R2001_coll_ptr ();

				if ( obj_inst_coll_ptr )
				{
					I_Object_Instance* related_oinst_ptr;
					FOR_ALL_ELEMENTS
						(related_oinst_ptr,
						I_Object_Instance,
						obj_inst_coll_ptr,
						oinst_cursor)
					{
						t_boolean found = TRUE;
						Attr_ref_in_object* aref_ptr;
						FOR_ALL_ELEMENTS
						(aref_ptr,
						Attr_ref_in_object,
						&ref_attr_coll,
						aref_cursor_2)
						{
                            Referred_to_ident_attr *rtida_ptr = aref_ptr->get_referred_to_ident_attr_ptr();
                            if ( rtida_ptr )
                            {
							    Attribute* part_attr_ptr = 
								    rtida_ptr->get_object_id_attr_ptr()->get_attribute_ptr();
							    I_Attribute_Instance*  part_ainst_ptr = 
								    related_oinst_ptr->find_Attribute_Instance_R2002_by_attribute_ID( part_attr_ptr->get_id() );
							    if ( part_ainst_ptr )
							    {
								    I_Attribute_Instance*  form_ainst_ptr = 
									    oinst_ptr->find_Attribute_Instance_R2002_by_attribute_ID( 
										    aref_ptr->get_ref_attr_ptr()->get_id() );
								    if ( form_ainst_ptr )
								    {
									    if ( !(*(part_ainst_ptr->get_var_ptr()) == *(form_ainst_ptr->get_var_ptr())) )
									    {
										    found = FALSE;
										    break;
									    }
								    }
							    }
                            }
						}

						if ( found )
						{
							return related_oinst_ptr;
						}
					}
				}
			}
		}
	}

	return ret_val;
}

I_Object_Instance* find_related_assoc_instance( 
		I_Object_Instance* this_oinst_ptr, I_Object_Instance* other_oinst_ptr, 
		Associative_relationship* other_ooa_rel_ptr )
{
	I_Object_Instance* ret_val = 0;

	// first get the referential attributes that formalize the relationship
	mc_dbms_List<Attr_ref_in_object*> *ref_attr_coll =
		other_ooa_rel_ptr->get_object_as_associator_ptr()->get_attr_ref_in_obj_coll_ptr();

    I_Object* sim_obj_ptr = I_Object::find_Object_by_object_ID
		(GS_gen_sim_db_ptr, 
			other_ooa_rel_ptr->get_object_as_associator_ptr()->object_id() );

	if ( sim_obj_ptr )
	{
		mc_dbms_List<I_Object_Instance*> *obj_inst_coll_ptr = 
			sim_obj_ptr->get_Object_Instance_R2001_coll_ptr ();

		if ( obj_inst_coll_ptr )
		{
			I_Object_Instance* related_oinst_ptr;
			FOR_ALL_ELEMENTS
				(related_oinst_ptr,
				I_Object_Instance,
				obj_inst_coll_ptr,
				oinst_cursor)
			{
				t_boolean found = TRUE;
				Attr_ref_in_object* aref_ptr;
				FOR_ALL_ELEMENTS
				(aref_ptr,
				Attr_ref_in_object,
				ref_attr_coll,
				aref_cursor_2)
				{
					I_Attribute_Instance*  part_ainst_ptr = 0;

                    Referred_to_ident_attr *rtida_ptr = aref_ptr->get_referred_to_ident_attr_ptr();
                    if (rtida_ptr)
                    {
					    Attribute* part_attr_ptr = 
						    rtida_ptr->get_object_id_attr_ptr()->get_attribute_ptr();
					    if ( part_attr_ptr->containing_object_id() == this_oinst_ptr->get_Object_R2001_ptr()->get_object_ID() )
					    {
						    part_ainst_ptr = 
							    this_oinst_ptr->find_Attribute_Instance_R2002_by_attribute_ID( part_attr_ptr->get_id() );
					    }
					    else if ( part_attr_ptr->containing_object_id() == other_oinst_ptr->get_Object_R2001_ptr()->get_object_ID() )
					    {
						    part_ainst_ptr = 
							    other_oinst_ptr->find_Attribute_Instance_R2002_by_attribute_ID( part_attr_ptr->get_id() );
					    }
                    }
					if ( part_ainst_ptr )
					{
						I_Attribute_Instance*  form_ainst_ptr = 
							related_oinst_ptr->find_Attribute_Instance_R2002_by_attribute_ID( 
								aref_ptr->get_ref_attr_ptr()->get_id() );
						if ( form_ainst_ptr )
						{
							if ( !(*(part_ainst_ptr->get_var_ptr()) == *(form_ainst_ptr->get_var_ptr())) )
							{
								found = FALSE;
								break;
							}
						}
					}
				}

				if ( found )
				{
					return related_oinst_ptr;
				}
			}
		}
	}

    delete ref_attr_coll;
	return ret_val;
}


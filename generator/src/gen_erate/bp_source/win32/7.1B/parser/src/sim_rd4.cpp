/*========================================================================
 *
 * File:      $RCSfile: sim_rd4.cpp,v $
 * Version:   $Revision: 1.10 $
 * Modified:  $Date: 2013/01/10 23:41:20 $
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

#include <i_obj.hh>
#include <i_oinst.hh>
#include <i_roip.hh>
#include <i_relate.hh>
#include <i_var.hh>

#include <u_cursor.hh>    
#include <u_env.hh>       
#include <u_trace.hh>                    

extern mc_dbms_database * GS_gen_sim_db_ptr;


void SIM_SOR::interpret_select_any_from_statement( const vchar * p_obj_kl, 
       const vchar *p_irv, SORAST* p_wc )
{
    I_object_inst_ref_set_var* inst_set_var_ptr
	= create__from_instances_of__no_push
	    (p_obj_kl, p_wc, TRUE);


    if ( inst_set_var_ptr)
    {

      I_object_inst_ref_var* result_inst_var_ptr = 0;
      if (inst_set_var_ptr->cardinality () >= 1)
      {
        inst_set_var_ptr->first();
	result_inst_var_ptr = new I_object_inst_ref_var
	    (inst_set_var_ptr->get_obj_ptr(),
	    inst_set_var_ptr->get_oinst_ptr());
      }
      else
      {
        if ( inst_set_var_ptr->get_obj_ptr() )
        {
	  result_inst_var_ptr = new I_object_inst_ref_var
	      (inst_set_var_ptr->get_obj_ptr(), 0);
        }
        else
        {
          // object doesn't exist in SIM database
          // we need to create it

          I_Object *new_obj_ptr
             = GS_sim_obj::create__I_Object (p_obj_kl);
          if (! new_obj_ptr )
          {
              Description err_msg("Unable to create Object with keyletters '");
              err_msg += p_obj_kl;
			  err_msg += "' in SIM Database.";
			  GS_ui::inform (UI_INFORM__ERROR, err_msg);
          }
          else
          {
            result_inst_var_ptr = new I_object_inst_ref_var
              (new_obj_ptr, 0);
          }
        }
      }
      delete inst_set_var_ptr;


      GS_var_si lvalue_var_si;
      lvalue_var_si.replace_var (result_inst_var_ptr);
      GS_stack::place_result_in_stack_var (p_irv, &lvalue_var_si);
    }
}

void SIM_SOR::interpret_select_many_from_statement( const vchar * p_obj_kl, 
       const vchar *p_irv, SORAST* p_wc )
{
    I_object_inst_ref_set_var* inst_set_var_ptr
	= create__from_instances_of__no_push
	    (p_obj_kl, p_wc, FALSE);


    if ( inst_set_var_ptr)
    {
      if ( !inst_set_var_ptr->get_obj_ptr() )
      {
          // object doesn't exist in SIM database
          // we need to create it

          I_Object *new_obj_ptr
             = GS_sim_obj::create__I_Object (p_obj_kl);
          if (! new_obj_ptr )
          {
              Description err_msg("Unable to create Object with keyletters '");
              err_msg += p_obj_kl;
			  err_msg += "' in SIM Database.";
			  GS_ui::inform (UI_INFORM__ERROR, err_msg);
          }
          else
          {
            // we can do this since we're a friend!
            inst_set_var_ptr->m_obj_ptr = new_obj_ptr;
          }
      }

      GS_var_si lvalue_var_si;
      lvalue_var_si.replace_var (inst_set_var_ptr);
      GS_stack::place_result_in_stack_var
	  (p_irv, &lvalue_var_si);
    }

}

void SIM_SOR::interpret_select_any_related_statement( 
         const vchar *p_irv,
         I_object_inst_ref_set_var* inst_set_var_ptr,
         bool p_any_flag, SORAST* p_wc )
{
    if ( p_wc && inst_set_var_ptr )
    {
      interpret_where_clause (inst_set_var_ptr, p_wc, p_any_flag);
    
    }

    if (inst_set_var_ptr)
    {
      if ( p_any_flag == FALSE && (inst_set_var_ptr->cardinality () > 1))
      {
	GS_ui::inform (UI_INFORM__ERROR, GS_string
	    ("Instance Chain results in more than one instance."));
	return ;
      }


      I_object_inst_ref_var* result_inst_var_ptr = 0;
      if (inst_set_var_ptr->cardinality () >= 1)
      {
        inst_set_var_ptr->first();
	result_inst_var_ptr = new I_object_inst_ref_var
	    (inst_set_var_ptr->get_obj_ptr(),
	    inst_set_var_ptr->get_oinst_ptr());
      }
      else
      {
        // don't worry about creating the I_Object in the
        // SIM database, as interpret_single_link has already done it.

  	result_inst_var_ptr = new I_object_inst_ref_var
	    (inst_set_var_ptr->get_obj_ptr(), 0);
      }
      delete inst_set_var_ptr;

      GS_var_si lvalue_var_si;
      lvalue_var_si.replace_var (result_inst_var_ptr);
      GS_stack::place_result_in_stack_var (p_irv, &lvalue_var_si);
    }
}

void SIM_SOR::interpret_select_many_related_statement( 
         const vchar *p_irv,
         I_object_inst_ref_set_var* inst_set_var_ptr,
         SORAST* p_wc )
{
        if ( p_wc && inst_set_var_ptr )
        {
          interpret_where_clause (inst_set_var_ptr, p_wc, FALSE);
        }

        if ( inst_set_var_ptr)
        {
          GS_var_si lvalue_var_si;
          lvalue_var_si.replace_var (inst_set_var_ptr);
          GS_stack::place_result_in_stack_var
	     (p_irv, &lvalue_var_si);
        }
}

I_object_inst_ref_set_var* SIM_SOR::interpret_chain_start ( const vchar *p_irv )
{
    // p_irv can be either an INST_REF_VAR or an INST_REF_SET_VAR

    I_var* var_ptr = GS_stack::find_var_ptr (p_irv);
    if (! var_ptr)
    {
       Description err_msg("Unable to find '");
	   err_msg += p_irv;
	   err_msg += "' on stack.";
       GS_ui::inform (UI_INFORM__ERROR, err_msg);
       LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #1 :  SIM_SOR::interpret_chain_start()."));
       return 0;
    }

    I_object_inst_ref_set_var* initial_inst_set = 0;

    I_object_inst_ref_set_var* inst_set_var_ptr
	= var_ptr->get_object_inst_ref_set_var_ptr ();
    if (inst_set_var_ptr)
    {
      GS_UI_INFORM_START (UI_INFORM__COMP)
      Description info_msg("rvalue '");
         info_msg += p_irv;
		 info_msg += "' (";
         info_msg += inst_set_var_ptr->get_data_type_str() ;
		 info_msg += ") = " ;
		 info_msg += inst_set_var_ptr->get_value_str();
      GS_UI_INFORM_END (UI_INFORM__COMP, info_msg)

      // Make a temporary copy of the inst_ref_set
      initial_inst_set	
	    = new I_object_inst_ref_set_var (inst_set_var_ptr);
    }
    else
    {
	I_object_inst_ref_var* inst_var_ptr
	    = var_ptr->get_object_inst_ref_var_ptr ();
	if (inst_var_ptr)
	{
      GS_UI_INFORM_START (UI_INFORM__COMP)
      Description info_msg("rvalue '");
         info_msg += p_irv;
		 info_msg += "' (";
         info_msg += inst_var_ptr->get_data_type_str() ;
		 info_msg += ") = " ;
		 info_msg += inst_var_ptr->get_value_str();
      GS_UI_INFORM_END (UI_INFORM__COMP, info_msg)

	    //  Convert the I_object_inst_ref_var to I_object_inst_ref_set_var.
	    //
	    initial_inst_set
		= new I_object_inst_ref_set_var (inst_var_ptr);
	}
	else
	{
	    Description err_msg ("Instance Chain ");
		err_msg += "begins with an undefined/incorrect '";
		err_msg += p_irv;
		err_msg += "'.";
	    GS_ui::inform (UI_INFORM__ERROR, err_msg);
	    return 0;
	}
    }
	
    return initial_inst_set;
}

I_object_inst_ref_set_var* SIM_SOR::interpret_single_link
    (const vchar *p_obj_kl,
     const vchar *p_rel, const vchar *p_rel_direction_str,
     I_object_inst_ref_set_var* p_start_inst_set_var_ptr )

    
{
    I_object_inst_ref_set_var* new_inst_set_var_ptr
	= new I_object_inst_ref_set_var ();
    new_inst_set_var_ptr->
	set_last_resort_key_letters_str (p_obj_kl);
        
        
    p_start_inst_set_var_ptr->first ();
    
    if (! p_start_inst_set_var_ptr->is_empty ())
    {
        do
        {
	    if (p_start_inst_set_var_ptr->cursor ()
		> p_start_inst_set_var_ptr->cardinality ())
	    {
		LOG_ERROR ((L_log_string,
		    "End #1:  SIM_SOR::interpret_single_link (0):  p_start_inst_set_var_ptr->cursor () exceeds the cardinality ()."));
		delete new_inst_set_var_ptr;
		return 0;
	    }

	    if ((p_start_inst_set_var_ptr->cursor () < 1)
		&& (p_start_inst_set_var_ptr->cardinality () >= 1))
	    {
		LOG_ERROR ((L_log_string,
		    "End #2:  SIM_SOR::interpret_single_link (0):  p_start_inst_set_var_ptr->cursor () < 1."));
		delete new_inst_set_var_ptr;
		return 0;
	    }

	    I_Object_Instance* start_oinst_ptr
		= p_start_inst_set_var_ptr->m_oinst_coll.retrieve
		    (p_start_inst_set_var_ptr->cursor () - 1);

	    if (! start_oinst_ptr)
	    {
		LOG_ERROR ((L_log_string,
		    "End #3:  SIM_SOR::interpret_single_link (0):  start_oinst_ptr is 0."));
		delete new_inst_set_var_ptr;
		return 0;
	    }

#ifdef COMMENTED_OUT
            // we're passed in a "Rn", but the relationship instance
            // just has the "n"
            const char * rel_num = &p_rel[1];
    
	    extern t_boolean is_simulator;
	    if (! is_simulator)
	    {
		//  Check to see if this object instance has been related yet.
		//    If not, then search out the related instance before
		//    proceeding.
		//
		if (! I_relate::relate_object_instance (start_oinst_ptr,
		    p_obj_kl, rel_num, p_rel_direction_str))
		{
		    delete new_inst_set_var_ptr;
		    return 0;
		}
	    }
#endif
	    if (! start_oinst_ptr->
		get_Related_Object_Instance_Pair_R2010_coll_ptr ())
	    {
		LOG_ERROR ((L_log_string,
		    "End #5:  SIM_SOR::interpret_single_link (0):  start_oinst_ptr->ROIP_R2010_coll_ptr == 0"));
		return 0;
	    }

	    I_Related_Object_Instance_Pair *roip_ptr;
	    FOR_ALL_ELEMENTS
		(roip_ptr,
		I_Related_Object_Instance_Pair,
		start_oinst_ptr->get_Related_Object_Instance_Pair_R2010_coll_ptr (),
		sim_roip_cursor1)
	    {
		if (roip_ptr->get_Rnum_str () == p_rel)
		{
                    // the relationship phrases in the OOA/SIM database have no ticks
                    // p_rel_direction_str has ticks, so add the ticks to the OOA data base info
            Description roip_phrase ("'");
			roip_phrase += roip_ptr->get_R2011_phrase ();
			roip_phrase += "'";

		    if ( (p_rel_direction_str == 0) || (vcharLength(p_rel_direction_str) == 0)
			|| (roip_phrase == p_rel_direction_str) )
		    {
			//  Have found an ROIP instance in the SIM DB which
			//    corresponds to the relationship - make sure that
			//    the related instance is an instance of the
			//    requested object.
			//
			I_Object_Instance* related_oinst_ptr
			    = roip_ptr->get_Object_Instance_R2011_ptr ();
			if (! related_oinst_ptr)
			{
			    LOG_ERROR ((L_log_string,
				"End #9:  SIM_SOR::interpret_single_link (0):  related_oinst_ptr == 0"));
			    return 0;
			}

			if (! related_oinst_ptr->get_Object_R2001_ptr ())
			{
			    LOG_ERROR ((L_log_string,
				"End #10:  SIM_SOR::interpret_single_link (0):  related_oinst_ptr->get_Object_R2001_ptr () == 0"));
			    return 0;
			}

			if (related_oinst_ptr->get_Object_R2001_ptr ()->get_key_letter() == p_obj_kl)
			{
			    try 
			    {
					new_inst_set_var_ptr->m_obj_ptr =
					    related_oinst_ptr->get_Object_R2001_ptr ();
					new_inst_set_var_ptr->m_oinst_coll.
					    insert_last (related_oinst_ptr);
			    } catch (std::exception& mc_exception) {
					LOG_ERROR ((L_log_string,
					    "SIM_SOR::interpret_single_link ():  Pointer trying to be added to inst_set more than once."));
				}
			}
		    }
		}
	    }


	    if (! start_oinst_ptr->
		get_Related_Object_Instance_Pair_R2011_coll_ptr ())
	    {
		LOG_ERROR ((L_log_string,
		    "End #5:  SIM_SOR::interpret_single_link (0):  start_oinst_ptr->ROIP_R2011_coll_ptr == 0"));
		return 0;
	    }

	    FOR_ALL_ELEMENTS
		(roip_ptr,
		I_Related_Object_Instance_Pair,
		start_oinst_ptr->get_Related_Object_Instance_Pair_R2011_coll_ptr (),
		sim_roip_cursor2)
	    {
		if (roip_ptr->get_Rnum_str () == p_rel)
		{
            // the relationship phrases in the OOA/SIM database have no ticks
            // p_rel_direction_str has ticks, so add the ticks to the OOA data base info
            Description roip_phrase ("'");
			roip_phrase += roip_ptr->get_R2010_phrase ();
			roip_phrase += "'";

		    if ( (p_rel_direction_str == 0) || (vcharLength(p_rel_direction_str) == 0)
			|| (roip_phrase == p_rel_direction_str) )
		    {
			//  Have found an ROIP instance in the SIM DB which
			//    corresponds to the relationship - make sure that
			//    the related instance is an instance of the
			//    requested object.
			//
			I_Object_Instance* related_oinst_ptr
			    = roip_ptr->get_Object_Instance_R2010_ptr ();
			if (! related_oinst_ptr)
			{
			    LOG_ERROR ((L_log_string,
				"End #10:  SIM_SOR::interpret_single_link (0):  related_oinst_ptr == 0"));
			    return 0;
			}

			if (! related_oinst_ptr->get_Object_R2001_ptr ())
			{
			    LOG_ERROR ((L_log_string,
				"End #10:  SIM_SOR::interpret_single_link (0):  related_oinst_ptr->get_Object_R2001_ptr () == 0"));
			    return 0;
			}

			if (related_oinst_ptr->get_Object_R2001_ptr ()->get_key_letter () == p_obj_kl)
			{
			    try {
					new_inst_set_var_ptr->m_obj_ptr =
					    related_oinst_ptr->get_Object_R2001_ptr ();
					new_inst_set_var_ptr->m_oinst_coll.
					    insert_last (related_oinst_ptr);
			    } catch (std::exception& mc_exception) {
					LOG_ERROR ((L_log_string,
				    	"SIM_SOR::interpret_single_link ():  Pointer trying to be added to inst_set more than once."));
			    }
			}
		    }
		}
	    }

	    p_start_inst_set_var_ptr->next ();
        }
	while (! p_start_inst_set_var_ptr->is_done ());
    }


    //  Check to see if any instances have been found.  If not, then
    //    set up the m_obj_ptr for the empty set.
    //
    if (! new_inst_set_var_ptr->m_obj_ptr)
    {
	mc_dbms_Set <I_Object*>* obj_coll_ptr
	    = I_Object::find_Object_by_key_letter (GS_gen_sim_db_ptr, p_obj_kl);

	if (! obj_coll_ptr)
	{
	    LOG_ERROR ((L_log_string,
		"SIM_SOR::interpret_single_link ():  I_Object collection pointer on find is 0."));
	    return 0;
	}

	if (obj_coll_ptr->cardinality () > 1)
	{
		Description warn_msg("More than one object with keyletters '");
		warn_msg += p_obj_kl;
		warn_msg += "' exists in the Database.\n\tSelecting one to use.";
	    GS_ui::inform (UI_INFORM__WARNING, warn_msg);
	}

	if (obj_coll_ptr->cardinality () > 0)
	{
	    new_inst_set_var_ptr->m_obj_ptr = obj_coll_ptr->pick ();
	    delete obj_coll_ptr;
	    if (! new_inst_set_var_ptr->m_obj_ptr)
	    {
		LOG_ERROR ((L_log_string,
		    "SIM_SOR::interpret_single_link ():  I_Object pointer in collection returned from find is 0."));
		return 0;
	    }
	}
	else
	{
	    delete obj_coll_ptr;

            Description obj_key_letter_str ( p_obj_kl );
	    obj_key_letter_str.convert_to_upper_case ();
	    obj_coll_ptr = I_Object::find_Object_by_key_letter
		(GS_gen_sim_db_ptr, obj_key_letter_str.char_ptr ());

	    if (! obj_coll_ptr)
	    {
		LOG_ERROR ((L_log_string,
		    "SIM_SOR::interpret_single_link ():  I_Object collection pointer on find is 0."));
		return 0;
	    }

	    if (obj_coll_ptr->cardinality () > 1)
	    {
			Description warn_msg("More than one object with keyletters '");
			warn_msg += obj_key_letter_str;
			warn_msg += "' exists in the Database.\n\tSelecting one to use.";
			GS_ui::inform (UI_INFORM__WARNING, warn_msg);
	    }

	    if (obj_coll_ptr->cardinality () > 0)
	    {
		new_inst_set_var_ptr->m_obj_ptr = obj_coll_ptr->pick ();
		delete obj_coll_ptr;
		if (! new_inst_set_var_ptr->m_obj_ptr)
		{
		    LOG_ERROR ((L_log_string,
			"SIM_SOR::interpret_single_link ():  I_Object pointer in collection returned from find is 0."));
		    return 0;
		}
	    }
	    else
	    {
		delete obj_coll_ptr;
		extern t_boolean is_simulator;
		if (! is_simulator)
		{
			Description err_msg ("Object with keyletters '");
			err_msg += p_obj_kl;
			err_msg += "' does not exist in the Database.";
		    GS_ui::inform (UI_INFORM__ERROR, err_msg);
		    return 0;
		}
		else
		{
		    new_inst_set_var_ptr->m_obj_ptr
			= GS_sim_obj::create__I_Object
			(p_obj_kl);
		    if (! new_inst_set_var_ptr->m_obj_ptr)
		    {
			    Description err_msg ("Unable to create Object with keyletters '");
			    err_msg += p_obj_kl;
				err_msg += "' in SIM Database.";
				GS_ui::inform (UI_INFORM__ERROR, err_msg);
			return 0;
		    }
		}
	    }
	}
    }


    //  Audit the resulting collection of instance handles
    //
    I_Object_Instance* oinst_ptr = 0;
    FOR_ALL_ELEMENTS
	(oinst_ptr,
	I_Object_Instance,
	&(new_inst_set_var_ptr->m_oinst_coll),
	oinst_cursor)
    {
	I_Object* obj_ptr = oinst_ptr->get_Object_R2001_ptr ();
	if (! obj_ptr)
	{
	    LOG_ERROR ((L_log_string,
		"End #15:  SIM_SOR::interpret_single_link (0):  Pointer from I_OINST to O_OBJ is 0 - audit failed."));
	    delete new_inst_set_var_ptr;
	    return 0;
	}

	if (obj_ptr->get_key_letter () != p_obj_kl)
	{
	    LOG_ERROR ((L_log_string,
		"End #16:  SIM_SOR::interpret_single_link (0):  Select object instance is NOT an instance of I_Object '%s' - audit failed.",
		p_obj_kl));
	    delete new_inst_set_var_ptr;
	    return 0;
	}
    }
    
    
    new_inst_set_var_ptr->m_cursor
	= (new_inst_set_var_ptr->cardinality () >= 1) ? 1 : 0;
    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	"End #17:  SIM_SOR::interpret_single_link (new_inst_set_var_ptr=0x%08x).",
	new_inst_set_var_ptr));
    return new_inst_set_var_ptr;
}


I_object_inst_ref_set_var* SIM_SOR::create__from_instances_of__no_push( const vchar * p_obj_kl, 
       SORAST* p_wc, bool p_any_flag )
{
    mc_dbms_Set <I_Object*>* obj_coll_ptr
	= I_Object::find_Object_by_key_letter (GS_gen_sim_db_ptr, p_obj_kl);
    if (! obj_coll_ptr)
    {
	LOG_ERROR ((L_log_string,
	    "SIM_SOR::create__from_instances_of__no_push ():  Creation of I_Object collection in find returned 0."));
	return 0;
    }


    I_object_inst_ref_set_var* inst_set_var_ptr = 0;
    if (obj_coll_ptr->cardinality () < 1)
    {
	delete obj_coll_ptr;

	inst_set_var_ptr = new I_object_inst_ref_set_var ();
	inst_set_var_ptr->
	    set_last_resort_key_letters_str (p_obj_kl);
    }
    else
    {
	if (obj_coll_ptr->cardinality () > 1)
	{
		Description err_msg("More than one object with key letters '");
		err_msg += p_obj_kl;
		err_msg += "' exists.";
	    GS_ui::inform (UI_INFORM__ERROR, err_msg);
	    return 0;
	}

	I_Object* obj_ptr = obj_coll_ptr->pick ();
	delete obj_coll_ptr;
	if (! obj_ptr)
	{
	    LOG_ERROR ((L_log_string,
		"SIM_SOR::create__from_instances_of ():  I_Object pointer in collection of 1 element is 0."));
	    return 0;
	}

	mc_dbms_List <I_Object_Instance*>* oinst_coll_ptr
	    = obj_ptr->get_Object_Instance_R2001_coll_ptr ();
	if (! oinst_coll_ptr)
	{
	    LOG_ERROR ((L_log_string,
		"SIM_SOR::create__from_instances_of ():  Creation of I_OINST collection returned 0."));
	    return 0;
	}

	inst_set_var_ptr
	    = new I_object_inst_ref_set_var (obj_ptr, oinst_coll_ptr);

        if ( p_wc )
        {
          interpret_where_clause
	    (inst_set_var_ptr, p_wc, p_any_flag);
        }
    }


    return inst_set_var_ptr;
}

void SIM_SOR::interpret_where_clause( I_object_inst_ref_set_var* p_inst_set_var_ptr,
       SORAST* p_wc, bool p_any_flag )
{

    if (! p_inst_set_var_ptr)
    {
	LOG_ERROR ((L_log_string,
	    "SIM_SOR::interpret_where_clause ():  p_inst_set_var_ptr == 0."));
	return;
    }

	t_int num_insts_checked = 0;
	t_int num_insts_passed = 0;

    mc_dbms_List <I_Object_Instance*> all_instance_coll =
        p_inst_set_var_ptr->m_oinst_coll;
    p_inst_set_var_ptr->m_oinst_coll.clear ();


// HACK - add optimized search later

    t_boolean done = FALSE;
    I_Object_Instance* oinst_ptr = 0;
    FOR_ALL_ELEMENTS
	    (oinst_ptr,
	    I_Object_Instance,
	    &(all_instance_coll),
	    oinst_cursor)
    {
      num_insts_checked++;

      //  Temporarily push the current instance onto the stack.
      //
      I_object_inst_ref_var* oinst_var_ptr = new I_object_inst_ref_var
  	(p_inst_set_var_ptr->get_obj_ptr(), oinst_ptr);
      GS_stack::push_var (oinst_var_ptr, "SELECTED");

      oinst_var_ptr = new I_object_inst_ref_var
	(p_inst_set_var_ptr->get_obj_ptr(), oinst_ptr);
      GS_stack::push_var (oinst_var_ptr, "Selected");

      oinst_var_ptr = new I_object_inst_ref_var
	(p_inst_set_var_ptr->get_obj_ptr(), oinst_ptr);
      GS_stack::push_var (oinst_var_ptr, "selected");


      // HACK - I think this works
      GS_var_si cond_var_si;
      SORASTBase *expr_root = p_wc;
      SIM_SOR::expr ( &expr_root, cond_var_si, TRUE );

      t_boolean error_occurred = FALSE;
      if (cond_var_si.get_var_ptr ()->get_core_data_type ()
		!= BOOLEAN_DATATYPE)
      {
	GS_ui::inform (UI_INFORM__ERROR, GS_string
	    ("WHERE expression may only contain a BOOLEAN expression."));
	error_occurred = TRUE;
      }
      else
      {
	if (cond_var_si.get_boolean_var_ptr ()->get_value ())
	{
	    num_insts_passed++;

	    //  Transfer pointer to this instance to the new instance
	    //    set.
	    //
	    try {
			p_inst_set_var_ptr->m_oinst_coll.insert_last (oinst_ptr);
		} catch (std::exception& mc_exception) {
			LOG_ERROR ((L_log_string,
			    "SIM_SOR::interpret_where_clause ():  Pointer trying to be added to inst_set more than once."));
			error_occurred = TRUE;
		}
		
	    if (p_any_flag)
	    {
		done = TRUE;
	    }
	 }
       }


      //  Pop the temporary instance off the stack.
      //
      GS_stack_item* si_3_ptr = GS_stack::pop ();
      I_Object_Instance* oinst3_ptr
	  = si_3_ptr ?
  	   (si_3_ptr->get_object_inst_ref_var_ptr () ?
	    si_3_ptr->get_object_inst_ref_var_ptr ()->get_oinst_ptr() : 0)
  	  : 0;
      delete si_3_ptr;
      GS_stack_item* si_2_ptr = GS_stack::pop ();
      I_Object_Instance* oinst2_ptr
	  = si_2_ptr ?
	   (si_2_ptr->get_object_inst_ref_var_ptr () ?
	    si_2_ptr->get_object_inst_ref_var_ptr ()->get_oinst_ptr() : 0)
	  : 0;
      delete si_2_ptr;
      GS_stack_item* si_1_ptr = GS_stack::pop ();
      I_Object_Instance* oinst1_ptr
	  = si_1_ptr ?
	   (si_1_ptr->get_object_inst_ref_var_ptr () ?
	    si_1_ptr->get_object_inst_ref_var_ptr ()->get_oinst_ptr() : 0)
	  : 0;
      delete si_1_ptr;
      if ((oinst1_ptr != oinst_ptr)
	  ||
  	  (oinst2_ptr != oinst_ptr)
  	  ||
	  (oinst3_ptr != oinst_ptr))
      {
	LOG_ERROR ((L_log_string,
	    "SIM_SOR::interpret_where_clause ():  Something pushed on stack during evaluation of condition."));
	error_occurred = TRUE;
      }
 
      if (error_occurred)
      {
	p_inst_set_var_ptr->m_cursor
	    = (p_inst_set_var_ptr->cardinality () >= 1) ? 1 : 0;
	return;
      }

      if (done)
      {
	break;
      }
    }  // FOR_ALL_ELEMENTS

    p_inst_set_var_ptr->m_cursor
	= (p_inst_set_var_ptr->cardinality () >= 1) ? 1 : 0;

}

/*========================================================================
 *
 * File:      $RCSfile: sim_rd.cpp,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:22 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#include "SIM_SOR.h"

#include "gs_stack.hh"      // GS_var_si, GS_for_si
#include "gs_ui.hh"
#include "gs_find.hh"
#include "gs_obj.hh"

#include "u_cursor.hh"    // FOR_ALL_ELEMENTS
#include "u_string.hh"
#include "u_trace.hh"

#include "d_object.hh"    // Object
#include "i_clock.hh"
#include "i_einst.hh"     // I_SM_Evt_Inst
#include "i_esdi.hh"      // I_SM_Evt_Supp_DI
#include "i_esdii.hh"     // I_SM_Evt_Supp_DI_Inst
#include "i_oinst.hh"     // I_Object_Instance
#include "i_var.hh"

#include "vchar.h"

extern mc_dbms_database*		GS_gen_sim_db_ptr;

void SIM_SOR::init ( bool p_instance_sm, I_Object_Instance *p_orig_inst )
{ 
  C_instance_sm = p_instance_sm;
  C_orig_inst_ptr = p_orig_inst;
 
  // initialize these values just to be sure
  C_return = FALSE;
  C_break = FALSE;
  C_return = FALSE;
}

void SIM_SOR::log_stmt ( SORAST* stmt )
{
  long start = stmt->getOffset();
  size_t len = (size_t) stmt->getSegLength();

  vchar* info_str = new vchar [len+1];
  const vchar* descrip_str = C_descrip.char_ptr() + start;
  vcharCopyBounded ( descrip_str, info_str, len );
  info_str[len] = '\0';

  GS_UI_INFORM (UI_INFORM__STMT, Description(info_str));

  delete [] info_str;
}

void SIM_SOR::log_expr ( SORAST* stmt, GS_var_si & p_expr_val )
{
  long start = stmt->getOffset();
  size_t len = (size_t) stmt->getSegLength();

  vchar* info_str = new vchar [len+1];
  const vchar* descrip_str = C_descrip.char_ptr() + start;
  vcharCopyBounded( descrip_str, info_str, len );
  info_str[len] = '\0';

  GS_UI_INFORM_START (UI_INFORM__COMP)
  Description info_msg("expression '");
  info_msg += info_str;
  info_msg += "' (";
  info_msg += p_expr_val.get_var_ptr()->get_data_type_str();
  info_msg += ") = ";
  info_msg += p_expr_val.get_var_ptr()->get_value_str();
  GS_UI_INFORM_END (UI_INFORM__COMP, info_msg)

  delete [] info_str;

}

void SIM_SOR::interpret_create_event_statement(const vchar *p_var_name, I_SM_Evt_Inst *p_einst_ptr)
{

  GS_var_si* event_inst_var_si_ptr
     = new GS_var_si (p_var_name, 
         EVENT_INST_DATATYPE, USER_DEFINED_USERDATATYPE);
  I_event_inst_var* event_inst_var_ptr
    = event_inst_var_si_ptr->get_event_inst_var_ptr ();

  //  Mark event instance as NOT in the Queue because it is
  //    created but not yet queued.
  //
  p_einst_ptr->set_expiration_time_to_infinity ();

  event_inst_var_ptr->set_einst_id (p_einst_ptr->get_evt_inst_ID());
  GS_stack::place_result_in_stack_var
    (p_var_name, event_inst_var_si_ptr);
  delete event_inst_var_si_ptr;

}

void SIM_SOR::interpret_create_object_statement( const vchar *lvalue_str, const vchar *obj_kl ) 
{
  // This code is copied from the function GS_sim_obj::interpret_stmt__create
  // in the file bp/gen_sim/src/sim/gs_obj1.cc

    mc_dbms_Collection <Object*>* ooa_obj_coll_ptr
	= GS_find::find_object_by_key_letters (obj_kl);
    if (! ooa_obj_coll_ptr)
    {
	LOG_ERROR ((L_log_string,
	    "End #1:  SIM_SOR::interpret_create_object_statement ():  Creation of Object collection in find returned 0."));
	return ;
    }


    if (ooa_obj_coll_ptr->cardinality () < 1)
    {
	//  Object not found in OOA DB.
	//
	Description err_msg("Object with key letters '");
	err_msg += obj_kl;
	err_msg += "' not found in OOA DB.";
	GS_ui::inform (UI_INFORM__ERROR, err_msg);
	delete ooa_obj_coll_ptr;
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #2:  SIM_SOR::interpret_create_object_statement (): Object not found in OOA DB."));
	return ;
    }


    if (ooa_obj_coll_ptr->cardinality () > 1)
    {
	    Description err_msg ("More than one object with keyletters '");
	    err_msg += obj_kl;
		err_msg += "' exists in OOA DB.";
	GS_ui::inform (UI_INFORM__ERROR, err_msg);
	delete ooa_obj_coll_ptr;
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #3:  SIM_SOR::interpret_create_object_statement()."));
	return ;
    }


    Object* ooa_obj_ptr = ooa_obj_coll_ptr->pick ();
    delete ooa_obj_coll_ptr;
    if (! ooa_obj_ptr)
    {
	LOG_ERROR ((L_log_string,
	    "End #4:  SIM_SOR::interpret_create_object_statement ():  Object pointer in collection of 1 element is 0."));
	return ;
    }


    I_Object_Instance* oinst_ptr
	= GS_sim_obj::create__I_Object_Instance (ooa_obj_ptr->get_object_id ());
    if (! oinst_ptr)
    {
	//  Assume error message already printed.
	//
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #5:  SIM_SOR::interpret_create_object_statement()."));
	return ;
    }


    if (vcharLength(lvalue_str) != 0)
    {
	GS_var_si* object_inst_ref_var_si_ptr
	    = new GS_var_si (lvalue_str, 
		OBJECT_INST_REF_DATATYPE, USER_DEFINED_USERDATATYPE);
	I_object_inst_ref_var* object_inst_ref_var_ptr
	    = object_inst_ref_var_si_ptr->get_object_inst_ref_var_ptr ();
	if (! object_inst_ref_var_ptr)
	{
	    GS_ui::inform (UI_INFORM__ERROR,
		GS_string("Internal Error:  Unable to Create Object."));
	    LOG_ERROR ((L_log_string,
		"End #6:  SIM_SOR::interpret_create_object_statement():  Can not find object instance variable on stack."));
	    delete oinst_ptr;
	    return ;
	}
	object_inst_ref_var_ptr->set_oinst_ptr (oinst_ptr);
	GS_stack::place_result_in_stack_var
	    (lvalue_str, object_inst_ref_var_si_ptr);
	delete object_inst_ref_var_si_ptr;
    }


    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	"End #7:  SIM_SOR::interpret_create_object_statement (): Success."));
    return ;
}

void SIM_SOR::interpret_delete_statement( const vchar *p_irv )
{

    I_var* var_ptr = GS_stack::find_var_ptr (p_irv);
    if (! var_ptr)
    {
	   Description err_msg ("Unable to find '");
	   err_msg += p_irv;
	   err_msg += "' on stack.";
       GS_ui::inform (UI_INFORM__ERROR, err_msg);
       LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #1 :  SIM_SOR::interpret_delete_statement()."));
       return ;
    }

  // This code is copied from the function GS_sim_obj::interpret_stmt__delete
  // in the file bp/gen_sim/src/sim/gs_obj1.cc

    if (var_ptr->get_object_inst_ref_var_ptr ()->get_oinst_ptr ())
    {
		GS_UI_INFORM_START (UI_INFORM__COMP)
		Description err_msg("rvalue '");
           err_msg += p_irv;
		   err_msg += "' (";
           err_msg += var_ptr->get_object_inst_ref_var_ptr()->get_data_type_str();
		   err_msg += ") = ";
		   err_msg += var_ptr->get_object_inst_ref_var_ptr()->get_value_str();
        GS_UI_INFORM_END (UI_INFORM__COMP, err_msg)

	if (! GS_sim_obj::delete__I_Object_Instance (var_ptr->
	    get_object_inst_ref_var_ptr ()->get_oinst_ptr ()))
	{
	    //  Error message already printed.
	    //
	    var_ptr->get_object_inst_ref_var_ptr ()->
		set_oinst_ptr (0);
	    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
                "End #2 :  SIM_SOR::interpret_delete_statement()."));
	    return ;
	}

	var_ptr->get_object_inst_ref_var_ptr ()->
	    set_oinst_ptr (0);
    }
    // i2744.6.1 begin
    else
    {
       Description err_msg("Instance Reference Variable '");
       err_msg += p_irv;
       err_msg += "' for Object '";
       err_msg += var_ptr->get_object_inst_ref_var_ptr ()->get_key_letters_str ();
       err_msg += "' has cardinality 0.";
       GS_ui::inform (UI_INFORM__ERROR, err_msg);
       err_msg = "This can be caused by a failed select or if the instance was already deleted.";
       GS_ui::inform (UI_INFORM__ERROR, err_msg);
    }
    // i2744.6.1 end


    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	"End #3:  SIM_SOR::interpret_delete_statement()."));
    return ;

}

bool SIM_SOR::interpret_for_initial( const vchar *irv, const vchar *irsv,
     int p_lineNo )
{
    I_var* var_ptr = GS_stack::find_var_ptr (irsv);
    if (! var_ptr)
    {
	   Description err_msg ("Unable to find '");
	   err_msg += irsv;
	   err_msg += "' on stack.";
       GS_ui::inform (UI_INFORM__ERROR, err_msg);
       LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #1 :  SIM_SOR::interpret_for_initial()."));
       return FALSE;
    }

    I_object_inst_ref_set_var* inst_set_var_ptr =
	var_ptr->get_object_inst_ref_set_var_ptr ();
    if (! inst_set_var_ptr)
    {
	    Description err_msg ("Variable '");
		err_msg += irsv;
		err_msg += "' is not of type inst_ref_set<Object>.";
	GS_ui::inform (UI_INFORM__ERROR, err_msg);
	return FALSE;
    }
    else
    {
		GS_UI_INFORM_START (UI_INFORM__COMP)
        Description err_msg("rvalue '");
           err_msg += irsv;
		   err_msg += "' (";
           err_msg += inst_set_var_ptr->get_data_type_str();
		   err_msg += ") = ";
		   err_msg += inst_set_var_ptr->get_value_str();
        GS_UI_INFORM_END (UI_INFORM__COMP, err_msg)

	//  NOTE that the char num is actually stored on the
	//    stack as the line num due to typing problems.
	//
	I_Clock::add_exec_time__stmt__for_initial ();
	if (! GS_stack::for_begin (irv,
	    irsv, 0,
	    p_lineNo) )
	{
	    //  No instances to iterate through - skip forward
            //    to 'END FOR' statement.
	    //
		GS_UI_INFORM_START (UI_INFORM__COMP)
		Description err_msg ("Object instance reference set '");
		err_msg += irsv;
		err_msg += "' is empty - skipping to statement ";
		err_msg += "following corresponding END FOR.";
	    GS_UI_INFORM_END (UI_INFORM__STMT, err_msg)
            return FALSE;
	}
    }
  return TRUE;
}

bool SIM_SOR::interpret_for_next()
{
  GS_UI_INFORM (UI_INFORM__STMT, (GS_string ("END FOR") + ";"));
  I_Clock::add_exec_time__stmt__for_iteration ();
  if (GS_stack::for_rewind ())
  {
    //  More instances exist to iterate through 
    //
    return TRUE;
  }
  else
  {
    //  NO more instances exist to iterate through -
    //    stack already cleaned up 
    //
    // set break and continue to FALSE to prevent an enclosing
    // iteration statement from also exiting
    C_continue = FALSE;
    C_break = FALSE;

    return FALSE;
  }
}

void SIM_SOR::interpret_for_exit( )
{
  extern GS_stack_item* s_stack [];
  extern t_uint s_stack_offset;

  //  Pop all variables off the stack until non-variable encountered.
  //
  while ((s_stack_offset > 0)
      && (s_stack [s_stack_offset])
      && ((s_stack [s_stack_offset])->get_var_si_ptr ()))
  {
    //  Stack item is a variable - pop & delete.
    //
    delete GS_stack::pop ();
  }
	
	
  //  Delete the for stack item itself.
  //
  if ((s_stack_offset > 0)
      && (s_stack [s_stack_offset])
      && ((s_stack [s_stack_offset])->get_for_si_ptr ()))
  {
    delete GS_stack::pop ();
  }

  // set break and continue to FALSE to prevent an enclosing
  // iteration statement from also exiting
  C_continue = FALSE;
  C_break = FALSE;
}

void SIM_SOR::interpret_generate_evt_statement( I_SM_Evt_Inst* p_einst_ptr )
{
  //  Reset the expiration time to the current time.  This will
  //    cause the event to be placed in the proper place in the
  //    queue based on expire time and based on event to self.
  //
  p_einst_ptr->set_expiration_time (I_Clock::current_time ());
}

void SIM_SOR::interpret_generate_evt_inst_statement_var( const vchar *p_event_var_str )
{
  I_var* var_ptr = GS_stack::find_var_ptr (p_event_var_str);
  if (! var_ptr)
  {
     Description err_msg("Unable to find '");
	 err_msg += p_event_var_str;
	 err_msg += "' on stack.";
     GS_ui::inform (UI_INFORM__ERROR, err_msg);
     LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	  "End #1 :  SIM_SOR::interpret_generate_evt_inst_statement_var()."));
     return ;
  }

  GS_var_si event_inst_var_si;
  event_inst_var_si.replace_var(var_ptr);

  I_event_inst_var* event_inst_var_ptr
    = event_inst_var_si.get_event_inst_var_ptr ();
  if (! event_inst_var_ptr)
  {
	Description err_msg ("Rvalue '");
	err_msg += p_event_var_str;
	err_msg += "' not found or is not of type 'inst<Event>'.";
    GS_ui::inform (UI_INFORM__ERROR, err_msg);
    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	"End #2:  SIM_SOR::interpret_generate_evt_inst_statement_var ()."));
    return ;
  }

  I_SM_Evt_Inst* einst_ptr = event_inst_var_ptr->get_einst_ptr ();
  if (! einst_ptr)
  {
	Description err_msg ("Variable '");
	err_msg += p_event_var_str;
	err_msg += "' is not initialized properly'.";
    GS_ui::inform (UI_INFORM__ERROR, err_msg);
    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	"End #3:  SIM_SOR::interpret_generate_evt_inst_statement_var ()."));
    return ;
  }

  GS_UI_INFORM_START (UI_INFORM__COMP)
  Description err_msg("rvalue '");
  err_msg += p_event_var_str;
  err_msg += "' (";
  err_msg += event_inst_var_ptr->get_data_type_str();
  err_msg += ") = ";
  err_msg += event_inst_var_ptr->get_value_str();
  GS_UI_INFORM_END (UI_INFORM__COMP, err_msg )

  interpret_generate_evt_inst_statement( p_event_var_str, event_inst_var_ptr, einst_ptr );
}

void SIM_SOR::interpret_generate_evt_inst_statement_attr( const vchar* lvalue_str, GS_var_si& event_inst_var_si )
{

  I_event_inst_var* event_inst_var_ptr
    = event_inst_var_si.get_event_inst_var_ptr ();
  if (! event_inst_var_ptr)
  {
	Description err_msg ("Attribute '");
	err_msg += lvalue_str;
	err_msg += "' not found or is not of type 'inst<Event>'.";
    GS_ui::inform (UI_INFORM__ERROR, err_msg);
    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	"End #1:  SIM_SOR::interpret_generate_evt_inst_statement_attr ()."));
    return ;
  }

  I_SM_Evt_Inst* einst_ptr = event_inst_var_ptr->get_einst_ptr ();
  if (! einst_ptr)
  {
	Description err_msg ("Attribute '");
	err_msg += lvalue_str;
	err_msg += "' is not initialized properly'.";
    GS_ui::inform (UI_INFORM__ERROR, err_msg);
    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	"End #2:  SIM_SOR::interpret_generate_evt_inst_statement_attr ()."));
    return ;
  }

  // The (COMP) rvalue has already been logged by interpret_attribute_access()

  interpret_generate_evt_inst_statement( lvalue_str, event_inst_var_ptr, einst_ptr );
}

void SIM_SOR::interpret_generate_evt_inst_statement( const vchar *p_event_var_str,
                                                     I_event_inst_var* event_inst_var_ptr,
                                                     I_SM_Evt_Inst* einst_ptr )
{

  // This code is copied from the function GS_sim_evt::interpret_stmt__generate
  // in the file bp/gen_sim/src/sim/gs_evt.cc

  //  This is a    GENERATE <event_inst_var>;    statement.
  //

  I_SM_Evt_Inst* new_einst_ptr
    = I_SM_Evt_Inst::copy__I_SM_Evt_Inst (einst_ptr);

  //  Reset the expiration time to the current time.  This will
  //    cause the event to be placed in the proper place in the
  //    queue based on expire time and based on event to self.
  //
  new_einst_ptr->set_expiration_time (I_Clock::current_time ());

  LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
    "End #4:  SIM_SOR::interpret_generate_evt_inst_statement (): Success."));

}

void SIM_SOR::interpret_if_begin()
{
    //  We don't use condition result, we save it in the
    //  code that called this function.
    //
    GS_stack::if_begin( FALSE );
}

void SIM_SOR::interpret_if_end()
{
    GS_stack::if_end( );
}

void SIM_SOR::interpret_while_initial( int p_lineNo )
{

  I_Clock::add_exec_time__stmt__while_initial ();

  //  Push an for stack item on the stack.
  //
  GS_stack::push_ctrl (new GS_while_si (Description(""),
     0, p_lineNo));


}

void SIM_SOR::interpret_while_next()
{
  GS_UI_INFORM (UI_INFORM__STMT, (GS_string ("END WHILE") + ";"));
  I_Clock::add_exec_time__stmt__while_iteration ();

  extern GS_stack_item* s_stack [];
  extern t_uint s_stack_offset ;

  //  Pop all variables off the stack until non-variable encountered.
  //
  while ((s_stack_offset > 0)
      && (s_stack [s_stack_offset])
      && ((s_stack [s_stack_offset])->get_var_si_ptr ()))
  {
    //  Stack item is a variable - pop & delete.
    //
    delete GS_stack::pop ();
  }

}

void SIM_SOR::interpret_while_exit( )
{
  extern GS_stack_item* s_stack [];
  extern t_uint s_stack_offset;

  //  Pop all variables off the stack until non-variable encountered.
  //
  while ((s_stack_offset > 0)
      && (s_stack [s_stack_offset])
      && ((s_stack [s_stack_offset])->get_var_si_ptr ()))
  {
    //  Stack item is a variable - pop & delete.
    //
    delete GS_stack::pop ();
  }
	
	
  //  Delete the while stack item itself.
  //
  if ((s_stack_offset > 0)
      && (s_stack [s_stack_offset])
      && ((s_stack [s_stack_offset])->get_while_si_ptr ()))
  {
    delete GS_stack::pop ();
  }

  // set break and continue to FALSE to prevent an enclosing
  // iteration statement from also exiting
  C_continue = FALSE;
  C_break = FALSE;
}

I_Object_Instance* SIM_SOR::interpret_event_spec_inst_ref ( const vchar *p_inst_var_name )
{
  I_var* var_ptr = GS_stack::find_var_ptr (p_inst_var_name);
  if (! var_ptr)
  {
     Description err_msg("Unable to find '");
	 err_msg += p_inst_var_name;
	 err_msg += "' on stack.";
     GS_ui::inform (UI_INFORM__ERROR, err_msg);
     LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	  "End #1 :  SIM_SOR::interpret_event_spec_inst_ref()."));
     return 0;
  }

  I_Object_Instance* dest_oinst_ptr = 0;

  I_object_inst_ref_var* obj_inst_var_ptr
		= var_ptr->get_object_inst_ref_var_ptr ();
  if (obj_inst_var_ptr)
  {
    dest_oinst_ptr = obj_inst_var_ptr->get_oinst_ptr ();
    if (! dest_oinst_ptr)
    {
      Description err_msg("Rvalue '");
	  err_msg += p_inst_var_name;
	  err_msg += "' is EMPTY inst_ref<Object>.";
      GS_ui::inform (UI_INFORM__ERROR, err_msg);
      LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	"End #10:  GS_sim_evt::interpret_event_spec_inst_ref (FALSE)."));
      return 0;
    }
  }

  GS_UI_INFORM_START (UI_INFORM__COMP)
  Description err_msg ("rvalue '");
  err_msg += p_inst_var_name;
  err_msg += "' (";
  err_msg += obj_inst_var_ptr->get_data_type_str();
  err_msg += ") = ";
  err_msg += obj_inst_var_ptr->get_value_str();
  GS_UI_INFORM_END (UI_INFORM__COMP, err_msg)

  return dest_oinst_ptr;
}

I_Object_Instance* SIM_SOR::interpret_event_spec_assigner ( const vchar *p_obj_kl )
{
  I_Object_Instance* dest_oinst_ptr = 0;

  mc_dbms_Collection <Object*>* ooa_obj_coll_ptr
	    = GS_find::find_object_by_key_letters (p_obj_kl);
  if (! ooa_obj_coll_ptr)
  {
    LOG_ERROR ((L_log_string,
	"End #1:  SIM_SOR::interpret_event_spec_assigner (0):  ooa_obj_coll_ptr == 0."));
    return 0;
  }
  else if (ooa_obj_coll_ptr->cardinality () > 1)
  {
    delete ooa_obj_coll_ptr;
	Description err_msg("More than one object with keyletters '");
	err_msg += p_obj_kl;
	err_msg += "' exists in OOA DB.";
    GS_ui::inform (UI_INFORM__WARNING, err_msg);
    LOG_ERROR ((L_log_string,
	"End #2:  SIM_SOR::interpret_event_spec_assigner (0):  duplicate obj keyletters."));
    return 0;
  }
  else
  {
    Object* ooa_obj_ptr = ooa_obj_coll_ptr->pick ();
    delete ooa_obj_coll_ptr;
    if (! ooa_obj_ptr)
    {
	LOG_ERROR ((L_log_string,
	    "End #3:   SIM_SOR::interpret_event_spec_assigner (0):  ooa_obj_ptr ==0."));
	return 0;
    }

    I_Object* sim_obj_ptr = I_Object::find_Object_by_object_ID
        (GS_gen_sim_db_ptr, ooa_obj_ptr->get_object_id ());
    if (! sim_obj_ptr)
    {
      LOG_ERROR ((L_log_string,
	"End #4:  SIM_SOR::interpret_event_spec_assigner (0):  sim_obj_ptr == 0."));
      return 0;
    }

    dest_oinst_ptr = sim_obj_ptr->get_Object_Instance_R2001A_ptr ();
    if (! dest_oinst_ptr)
    {
      GS_ui::inform (UI_INFORM__ERROR,
         GS_string("Unable to find destination Object Instance..."));
      LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	"End #5:  SIM_SOR::interpret_event_spec_assigner (0)."));
      return 0;
    }
  }

  return dest_oinst_ptr;
}

Object* SIM_SOR::interpret_event_spec_creator ( const vchar *p_obj_kl )
{
  Object* ooa_obj_ptr = 0;

  mc_dbms_Collection <Object*>* ooa_obj_coll_ptr
	    = GS_find::find_object_by_key_letters (p_obj_kl);
  if (! ooa_obj_coll_ptr)
  {
    LOG_ERROR ((L_log_string,
	"End #1:  SIM_SOR::interpret_event_spec_creator (0):  ooa_obj_coll_ptr == 0."));
  }
  else if (ooa_obj_coll_ptr->cardinality () > 1)
  {
    delete ooa_obj_coll_ptr;
	Description err_msg("More than one object with keyletters '");
	err_msg += p_obj_kl;
	err_msg += "' exists in OOA DB.";
    GS_ui::inform (UI_INFORM__WARNING, err_msg);
    LOG_ERROR ((L_log_string,
	"End #2:  SIM_SOR::interpret_event_spec_creator (0):  duplicate obj keyletters."));
  }
  else
  {
    ooa_obj_ptr = ooa_obj_coll_ptr->pick ();
    delete ooa_obj_coll_ptr;
    if (! ooa_obj_ptr)
    {
	LOG_ERROR ((L_log_string,
	    "End #3:   SIM_SOR::interpret_event_spec_creator (0):  ooa_obj_ptr ==0."));
    }
  }

  return ooa_obj_ptr;
}

void SIM_SOR::interpret_supp_data ( I_SM_Evt_Inst* p_einst_ptr, 
     const vchar *p_supp_data_name, 
     GS_var_si& p_data_val )
{
  if (p_data_val.get_var_ptr () &&
      p_data_val.get_var_ptr ()->get_core_data_type () == VOID_DATATYPE)
  {
    Description err_msg ("Value of '");
	err_msg += p_supp_data_name;
	err_msg += "' not recognized.";
    GS_ui::inform (UI_INFORM__ERROR, err_msg);
  }
  else
  {
    I_SM_Evt_Supp_DI_Inst* esdii_ptr;
    FOR_ALL_ELEMENTS
        (esdii_ptr,
        I_SM_Evt_Supp_DI_Inst,
	p_einst_ptr->get_SM_Evt_Supp_DI_Inst_R2023_coll_ptr (),
	esdii_cursor)
    {
      if (esdii_ptr->get_SM_Evt_Supp_DI_R2023_ptr ()->get_name () == p_supp_data_name)
      {
        if (p_data_val.get_var_ptr ()->get_core_data_type ()
	    != esdii_ptr->get_core_data_type ())
	{
		Description err_msg("Type of '");
		err_msg += p_supp_data_name;
		err_msg += "' does not match Event Supplemental Data Item Type.";
	  GS_ui::inform (UI_INFORM__ERROR, err_msg);
	}
	else
	{
          esdii_ptr->get_var_ptr ()->reassign
	    (p_data_val.get_var_ptr ());
	}
      }
    }
  }
}

void SIM_SOR::mismatched_range(int looking_for, 
        int upper_token, SORASTBase *found)
{
  if ( found == NULL )
  {
    AST *c_ast = (new AST(TOK_GARBAGE));
    AL_PARSE_ERR2( c_ast, AL_GETMSG(ERR,356,2), looking_for, upper_token )
    delete c_ast;
  }
  else
  {
    AST *c_ast = (AST*)found;
    AL_PARSE_ERR3( c_ast, AL_GETMSG(ERR,357,3), looking_for, upper_token, found->type() )
  }
}

void SIM_SOR::missing_wildcard()
{
  AST *c_ast = (new AST(TOK_GARBAGE));
  AL_PARSE_ERR0( c_ast, AL_GETMSG(ERR,358,0))
  delete c_ast;
}

void SIM_SOR::mismatched_token(int looking_for, SORASTBase *found)
{
  if ( found == NULL )
  {
    AST *c_ast = (new AST(TOK_GARBAGE));
    AL_PARSE_ERR1( c_ast, AL_GETMSG(ERR,359,1), looking_for )
    delete c_ast;
  }
  else
  {
    AST *c_ast = (AST*)found;
    AL_PARSE_ERR2( c_ast, AL_GETMSG(ERR,360,2), looking_for, found->type() )
  }
}

void SIM_SOR::no_viable_alt(char *rulename, SORASTBase *root)
{
  if ( root == NULL )
  {
    AST *c_ast = (new AST(TOK_GARBAGE));
    AL_PARSE_ERR1( c_ast, AL_GETMSG(ERR,361,1), vcharScribeASCII(rulename) )
    delete c_ast;
  }
  else
  {
    AST *c_ast = (AST*)root;
    AL_PARSE_ERR1( c_ast, AL_GETMSG(ERR,362,1), vcharScribeASCII(rulename) )
  }
}


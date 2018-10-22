/*========================================================================
 *
 * File:      $RCSfile: i_var.cc,v $
 * Version:   $Revision: 1.11 $
 * Modified:  $Date: 2013/01/10 23:41:36 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#include <stdlib.h>

#include <u_trace.hh>
#include <u_error.hh>
#include <u_cursor.hh>
#include <u_tspec.hh>

#include <i_var.hh>
#include <i_attr.hh>
#include <i_ainst.hh>
#include <i_oinst.hh>
#include <i_einst.hh>
#include <i_evt.hh>
#include <gs_ui.hh>

extern mc_dbms_database* GS_gen_sim_db_ptr;



mc_dbms_List<I_object_inst_ref_var*> *I_object_inst_ref_var::m_extent_coll = 0;  // i2744.1.3






//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////



I_var::~I_var ()

{
    if (m_reference_count > 0)
    {
	LOG_ERROR ((L_log_string,
	    "I_var::~I_var () - Deleting I_var with m_reference_count > 0."));
    } else {
	    operator delete( this, ""); // Remove from InstanceTracker
    }
}



t_int
I_var::get_reference_count ()

{
    return m_reference_count;
}



void
I_var::increment_reference_count ()

{
    m_reference_count++;
}



t_int
I_var::decrement_reference_count ()

{
    if (m_reference_count < 1)
    {
	LOG_ERROR ((L_log_string,
	    "I_var::decrement_reference_count () - m_reference_count < 1."));
    }
    else
    {
	m_reference_count--;
    }
    return m_reference_count;
}



I_var*
I_var::create_in_transient
    (t_core_data_type p_core_data_type, t_user_data_type p_user_data_type)

{
    I_var* var_ptr = 0;


    switch (p_core_data_type)
    {
    case VOID_DATATYPE:
	var_ptr = new I_void_var ();
	break;

    case ENUMERATION_DATATYPE:
	var_ptr = new I_enumerator_var ();
	break;

    case BOOLEAN_DATATYPE:
	var_ptr = new I_boolean_var ();
	break;

    case INTEGER_DATATYPE:
	var_ptr = new I_integer_var ();
	break;

    case REAL_DATATYPE:
	var_ptr = new I_real_var ();
	break;

    case STRING_DATATYPE:
	var_ptr = new I_string_var ();
	break;

    case UNIQUE_ID_DATATYPE:
	var_ptr = new I_unique_id_var ();
	break;

    case CURRENT_STATE_DATATYPE:
	var_ptr = new I_current_state_var ();
	break;

    case OBJECT_INST_REF_DATATYPE:
	var_ptr = new I_object_inst_ref_var ();
	break;

    case OBJECT_INST_REF_SET_DATATYPE:
	var_ptr = new I_object_inst_ref_set_var ();
	break;

    case EVENT_INST_DATATYPE:
	var_ptr = new I_event_inst_var ();
	break;

    case MAPPING_INST_DATATYPE:
	switch (p_user_data_type)
	{
	case USER_DEFINED_USERDATATYPE:
	    var_ptr = new I_mapping_inst_var ();
	    break;

	case TIMESTAMP_USERDATATYPE:
	    var_ptr = new I_timestamp_var ();
	    break;

	case DATE_USERDATATYPE:
	    var_ptr = new I_date_var ();
	    break;

	default:
	    LOG_ERROR ((L_log_string,
		"I_var::create_in_transient () - Unknown user data type."));
	    break;
	}
	break;

    case MAPPING_INST_REF_DATATYPE:
	switch (p_user_data_type)
	{
	case USER_DEFINED_USERDATATYPE:
	    var_ptr = new I_mapping_inst_ref_var ();
	    break;

	case TIMER_INST_REF_USERDATATYPE:
	    var_ptr = new I_timer_inst_ref_var ();
	    break;

	default:
	    LOG_ERROR ((L_log_string,
		"I_var::create_in_transient () - Unknown user data type."));
	    break;
	}
	break;

    case FRAGMENT_DATATYPE:
	var_ptr = new I_frag_ref_var ();
	break;

    default:
	LOG_ERROR ((L_log_string,
	    "I_var::create_in_transient () - Unknown core data type."));
	break;
    }


    return var_ptr;
}



I_var*
I_var::create_in_persistent (mc_dbms_segment* p_segment_ptr,
    t_core_data_type p_core_data_type, t_user_data_type p_user_data_type)

{
    LOG_TRACE (L_D_DATA, L_FUNCTION_BEGIN, (L_log_string,
	"Begin  I_var::create_in_persistent (p_segment_ptr=0x%08x, p_core_data_type=%d, p_user_data_type=%d).",
	p_segment_ptr, p_core_data_type, p_user_data_type));


    I_var* var_ptr = 0;


    switch (p_core_data_type)
    {
    case VOID_DATATYPE:
	var_ptr
	    = new (p_segment_ptr, I_void_var::get_mc_dbms_typespec ())
	    I_void_var ();
	break;

    case ENUMERATION_DATATYPE:
	var_ptr
	    = new (p_segment_ptr, I_enumerator_var::get_mc_dbms_typespec ())
	    I_enumerator_var ();
	break;

    case BOOLEAN_DATATYPE:
	var_ptr
	    = new (p_segment_ptr, I_boolean_var::get_mc_dbms_typespec ())
	    I_boolean_var ();
	break;

    case INTEGER_DATATYPE:
	var_ptr
	    = new (p_segment_ptr, I_integer_var::get_mc_dbms_typespec ())
	    I_integer_var ();
	break;

    case REAL_DATATYPE:
	var_ptr
	    = new (p_segment_ptr, I_real_var::get_mc_dbms_typespec ())
	    I_real_var ();
	break;

    case STRING_DATATYPE:
	var_ptr
	    = new (p_segment_ptr, I_string_var::get_mc_dbms_typespec ())
	    I_string_var ();
	break;

    case UNIQUE_ID_DATATYPE:
	var_ptr
	    = new (p_segment_ptr, I_unique_id_var::get_mc_dbms_typespec ())
	    I_unique_id_var ();
	break;

    case CURRENT_STATE_DATATYPE:
	var_ptr
	    = new (p_segment_ptr, I_current_state_var::get_mc_dbms_typespec ())
	    I_current_state_var ();
	break;

    case OBJECT_INST_REF_DATATYPE:
	var_ptr
	    = new (p_segment_ptr, I_object_inst_ref_var::get_mc_dbms_typespec ())
	    I_object_inst_ref_var ();
	break;

    case OBJECT_INST_REF_SET_DATATYPE:
	var_ptr
	    = new (p_segment_ptr, I_object_inst_ref_set_var::get_mc_dbms_typespec ())
	    I_object_inst_ref_set_var ();
	break;

    case EVENT_INST_DATATYPE:
	var_ptr
	    = new (p_segment_ptr, I_event_inst_var::get_mc_dbms_typespec ())
	    I_event_inst_var ();
	break;

    case MAPPING_INST_DATATYPE:
	switch (p_user_data_type)
	{
	case USER_DEFINED_USERDATATYPE:
	    var_ptr
		= new (p_segment_ptr, I_mapping_inst_var::get_mc_dbms_typespec ())
		I_mapping_inst_var ();
	    break;

	case TIMESTAMP_USERDATATYPE:
	    var_ptr
		= new (p_segment_ptr, I_timestamp_var::get_mc_dbms_typespec ())
		I_timestamp_var ();
	    break;

	case DATE_USERDATATYPE:
	    var_ptr
		= new (p_segment_ptr, I_date_var::get_mc_dbms_typespec ())
		I_date_var ();
	    break;

	default:
	    LOG_ERROR ((L_log_string,
		"I_var::create_in_persistent () - Unknown user data type."));
	    break;
	}
	break;

    case MAPPING_INST_REF_DATATYPE:
	switch (p_user_data_type)
	{
	case USER_DEFINED_USERDATATYPE:
	    var_ptr
		= new (p_segment_ptr, I_mapping_inst_ref_var::get_mc_dbms_typespec())
		I_mapping_inst_ref_var ();
	    break;

	case TIMER_INST_REF_USERDATATYPE:
	    var_ptr
		= new (p_segment_ptr, I_timer_inst_ref_var::get_mc_dbms_typespec ())
		I_timer_inst_ref_var ();
	    break;

	default:
	    LOG_ERROR ((L_log_string,
		"I_var::create_in_persistent () - Unknown user data type."));
	    break;
	}
	break;

    case FRAGMENT_DATATYPE:
	var_ptr
	    = new (p_segment_ptr, I_frag_ref_var::get_mc_dbms_typespec ())
	    I_frag_ref_var ();
	break;

    default:
	LOG_ERROR ((L_log_string,
	    "I_var::create_in_persistent () - Unknown core data type."));
	break;
    }


    LOG_TRACE (L_D_DATA, L_FUNCTION_END, (L_log_string,
	"I_var::create_in_persistent (var_ptr=0x%08x).",
	var_ptr));
    return var_ptr;
}









//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////


t_boolean
I_void_var::operator== (const I_var& p_var) const

{
    return (((I_var&) p_var).get_void_var_ptr ()) ? TRUE : FALSE;
}


t_boolean
I_void_var::reassign (const I_var* p_var_ptr)

{
    if (((I_var*) p_var_ptr)->get_void_var_ptr ()) 
        return TRUE;
    else
    {
        Description err_msg	("Attempting to assign a ");
        err_msg += p_var_ptr->get_data_type_str();
        err_msg += " variable to a ";
        err_msg += get_data_type_str();
        err_msg += " variable";
	    GS_ui::inform (UI_INFORM__ERROR, err_msg);
        return FALSE;
    }
}


I_var*
I_void_var::clone_to_transient () const

{
    return new I_void_var (*this);
}


I_var*
I_void_var::clone_to_persistent () const

{
    return new (GS_gen_sim_db_ptr, I_void_var::get_mc_dbms_typespec ())
	I_void_var (*this);
}


void
I_void_var::set_void_str ()

{
    m_void_str = "void";
}









//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////


t_boolean
I_enumerator_var::operator== (const I_var& p_var) const

{
    t_boolean rv = FALSE;
    if (((I_var&) p_var).get_enumerator_var_ptr ())
    {
	rv = (get_value () == ((I_var&) p_var).get_enumerator_var_ptr ()->
	    get_value ()) ? TRUE : FALSE;
    }
    return rv;
}


t_boolean
I_enumerator_var::reassign (const I_var* p_var_ptr)

{
    t_boolean rv = FALSE;
    if (((I_var*) p_var_ptr)->get_enumerator_var_ptr ())
    {
	set_value (((I_var*) p_var_ptr)->get_enumerator_var_ptr ()->get_value ());
	rv = TRUE;
    }
    else
    {
        Description err_msg	("Attempting to assign a ");
        err_msg += p_var_ptr->get_data_type_str();
        err_msg += " variable to a ";
        err_msg += get_data_type_str();
        err_msg += " variable";
	    GS_ui::inform (UI_INFORM__ERROR, err_msg);
    }
    return rv;
}


I_var*
I_enumerator_var::clone_to_transient () const

{
    return new I_enumerator_var (*this);
}


I_var*
I_enumerator_var::clone_to_persistent () const

{
    return new (GS_gen_sim_db_ptr, I_enumerator_var::get_mc_dbms_typespec ())
	I_enumerator_var (*this);
}


void
I_enumerator_var::set_value (const Description& p_enumerator)

{
    m_enumerator_str = p_enumerator;
}






//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////


t_boolean
I_boolean_var::operator== (const I_var& p_var) const

{
    t_boolean rv = FALSE;
    if (((I_var&) p_var).get_boolean_var_ptr ())
    {
	rv = (get_value () == ((I_var&) p_var).get_boolean_var_ptr ()->
	    get_value ()) ? TRUE : FALSE;
    }
    return rv;
}


t_boolean
I_boolean_var::reassign (const I_var* p_var_ptr)

{
    t_boolean rv = FALSE;
    if (((I_var*) p_var_ptr)->get_boolean_var_ptr ())
    {
	set_value (((I_var*) p_var_ptr)->get_boolean_var_ptr ()->get_value ());
	rv = TRUE;
    }
    else
    {
        Description err_msg	("Attempting to assign a ");
        err_msg += p_var_ptr->get_data_type_str();
        err_msg += " variable to a ";
        err_msg += get_data_type_str();
        err_msg += " variable";
	    GS_ui::inform (UI_INFORM__ERROR, err_msg);
    }
    return rv;
}


I_var*
I_boolean_var::clone_to_transient () const

{
    return new I_boolean_var (*this);
}


I_var*
I_boolean_var::clone_to_persistent () const

{
    return new (GS_gen_sim_db_ptr, I_boolean_var::get_mc_dbms_typespec ())
	I_boolean_var (*this);
}


void
I_boolean_var::set_value (t_boolean p_boolean)

{
    m_boolean = p_boolean;
    set_boolean_str ();
}


void
I_boolean_var::set_boolean_str ()

{
    m_boolean_str = get_value () ? "TRUE" : "FALSE";
}










//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////


t_boolean
I_integer_var::operator== (const I_var& p_var) const

{
    t_boolean rv = FALSE;
    if (((I_var&) p_var).get_integer_var_ptr ())
    {
	rv = (get_value () == ((I_var&) p_var).get_integer_var_ptr ()->
	    get_value ()) ? TRUE : FALSE;
    }
    else if (((I_var&) p_var).get_real_var_ptr ())
    {
	rv = (get_value () == (t_long) ((I_var&) p_var).
	    get_real_var_ptr ()->get_value ()) ? TRUE : FALSE;
    }
    else if (((I_var&) p_var).get_unique_id_var_ptr ())
    {
	rv = (get_value () == (t_long) ((I_var&) p_var).
	    get_unique_id_var_ptr ()->get_value ()) ? TRUE : FALSE;
    }
    return rv;
}


t_boolean
I_integer_var::reassign (const I_var* p_var_ptr)

{
    t_boolean rv = FALSE;
    if (((I_var*) p_var_ptr)->get_integer_var_ptr ())
    {
	set_value (((I_var*) p_var_ptr)->get_integer_var_ptr ()->get_value ());
	rv = TRUE;
    }
    else if (((I_var*) p_var_ptr)->get_real_var_ptr ())
    {
	set_value
	    ((t_long) ((I_var*) p_var_ptr)->get_real_var_ptr ()->get_value ());
	rv = TRUE;
    }
    else
    {
        Description err_msg	("Attempting to assign a ");
        err_msg += p_var_ptr->get_data_type_str();
        err_msg += " variable to a ";
        err_msg += get_data_type_str();
        err_msg += " variable";
	    GS_ui::inform (UI_INFORM__ERROR, err_msg);
    }
    return rv;
}


I_var*
I_integer_var::clone_to_transient () const

{
    return new I_integer_var (*this);
}


I_var*
I_integer_var::clone_to_persistent () const

{
    return new (GS_gen_sim_db_ptr, I_integer_var::get_mc_dbms_typespec ())
	I_integer_var (*this);
}


void
I_integer_var::set_value (t_long p_integer)

{
    m_integer = p_integer;
    set_integer_str ();
}


void
I_integer_var::set_integer_str ()

{
    char buffer [32];
    sprintf (buffer, "%ld", get_value ());
    m_integer_str = buffer;
}










//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////


t_boolean
I_real_var::operator== (const I_var& p_var) const

{
    t_boolean rv = FALSE;
    if (((I_var&) p_var).get_real_var_ptr ())
    {
	rv = (get_value () == ((I_var&) p_var).get_real_var_ptr ()->
	    get_value ()) ? TRUE : FALSE;
    }
    else if (((I_var&) p_var).get_integer_var_ptr ())
    {
	rv = (get_value () == (t_double) ((I_var&) p_var).
	    get_integer_var_ptr ()->get_value ()) ? TRUE : FALSE;
    }
    return rv;
}


t_boolean
I_real_var::reassign (const I_var* p_var_ptr)

{
    t_boolean rv = FALSE;
    if (((I_var*) p_var_ptr)->get_real_var_ptr ())
    {
	set_value (((I_var*) p_var_ptr)->get_real_var_ptr ()->get_value ());
	rv = TRUE;
    }
    else if (((I_var*) p_var_ptr)->get_integer_var_ptr ())
    {
	set_value ((t_double) ((I_var*) p_var_ptr)->get_integer_var_ptr ()->
	    get_value ());
	rv = TRUE;
    }
    else
    {
        Description err_msg	("Attempting to assign a ");
        err_msg += p_var_ptr->get_data_type_str();
        err_msg += " variable to a ";
        err_msg += get_data_type_str();
        err_msg += " variable";
	    GS_ui::inform (UI_INFORM__ERROR, err_msg);
    }
    return rv;
}


I_var*
I_real_var::clone_to_transient () const

{
    return new I_real_var (*this);
}


I_var*
I_real_var::clone_to_persistent () const

{
    return new (GS_gen_sim_db_ptr, I_real_var::get_mc_dbms_typespec ())
	I_real_var (*this);
}


void
I_real_var::set_value (t_double p_real)

{
    m_real = p_real;
    set_real_str ();
}


void
I_real_var::set_real_str ()

{
    char buffer [32];
    sprintf (buffer, "%lf", get_value ());
    m_real_str = buffer;
}









//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////


t_boolean
I_string_var::operator== (const I_var& p_var) const

{
    t_boolean rv = FALSE;
    if (((I_var&) p_var).get_string_var_ptr ())
    {
	rv = (m_string_str
	    == ((I_string_var*) ((I_var&) p_var).get_string_var_ptr ())->
		m_string_str) ? TRUE : FALSE;
    }
    return rv;
}


t_boolean
I_string_var::reassign (const I_var* p_var_ptr)

{
    t_boolean rv = FALSE;
    if (((I_var*) p_var_ptr)->get_string_var_ptr ())
    {
	set_value (((I_var*) p_var_ptr)->get_string_var_ptr ()->get_value ());
	return TRUE;
    }
    else
    {
        Description err_msg	("Attempting to assign a ");
        err_msg += p_var_ptr->get_data_type_str();
        err_msg += " variable to a ";
        err_msg += get_data_type_str();
        err_msg += " variable";
	    GS_ui::inform (UI_INFORM__ERROR, err_msg);
    }
    return rv;
}


I_var*
I_string_var::clone_to_transient () const

{
    return new I_string_var (*this);
}


I_var*
I_string_var::clone_to_persistent () const

{
    return new (GS_gen_sim_db_ptr, I_string_var::get_mc_dbms_typespec ())
	I_string_var (*this);
}


void
I_string_var::set_value (const Description& p_string_str)

{
    m_string_str = p_string_str;
}


void
I_string_var::append_to_value (const Description& p_string_str)

{
    m_string_str += p_string_str;
}









//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////


t_boolean
I_unique_id_var::operator== (const I_var& p_var) const

{
    t_boolean rv = FALSE;
    if (((I_var&) p_var).get_unique_id_var_ptr ())
    {
	rv = (get_value () == ((I_var&) p_var).
	    get_unique_id_var_ptr ()->get_value ()) ? TRUE : FALSE;
    }
    else if (((I_var&) p_var).get_integer_var_ptr ())
    {
	rv = (get_value () == (t_ulong) ((I_var&) p_var).
	    get_integer_var_ptr ()->get_value ()) ? TRUE : FALSE;
    }
    return rv;
}


t_boolean
I_unique_id_var::reassign (const I_var* p_var_ptr)

{
    t_boolean rv = FALSE;
    if (((I_var*) p_var_ptr)->get_unique_id_var_ptr ())
    {
	set_value (((I_var*) p_var_ptr)->get_unique_id_var_ptr ()->
	    get_value ());
	rv = TRUE;
    }
    else if (((I_var*) p_var_ptr)->get_integer_var_ptr ())
    {
        I_integer_var* integer_var_ptr = 
            ((I_var*) p_var_ptr)->get_integer_var_ptr ();
        if ( integer_var_ptr->get_value() == 0 )
        {
            set_value ( 0 );
            rv = TRUE;
        }
    }
    else
    {
        Description err_msg	("Attempting to assign a ");
        err_msg += p_var_ptr->get_data_type_str();
        err_msg += " variable to a ";
        err_msg += get_data_type_str();
        err_msg += " variable";
	    GS_ui::inform (UI_INFORM__ERROR, err_msg);
    }
    return rv;
}


I_var*
I_unique_id_var::clone_to_transient () const

{
    return new I_unique_id_var (*this);
}


I_var*
I_unique_id_var::clone_to_persistent () const

{
    return new (GS_gen_sim_db_ptr, I_unique_id_var::get_mc_dbms_typespec ())
	I_unique_id_var (*this);
}


void
I_unique_id_var::set_value (t_ulong p_unique_id)

{
    m_unique_id = p_unique_id;
    set_unique_id_str ();
}


void
I_unique_id_var::set_unique_id_str ()

{
    if (get_is_initialized ())
    {
	char buffer [32];
	sprintf (buffer, "%lu", get_value ());
	m_unique_id_str = buffer;
    }
    else
    {
	m_unique_id_str = "un-initialized";
    }
}









//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////


t_boolean
I_current_state_var::operator== (const I_var& p_var) const

{
    t_boolean rv = FALSE;
    if (((I_var&) p_var).get_current_state_var_ptr ())
    {
	rv = (get_value ()
	    == ((I_var&) p_var).get_current_state_var_ptr ()->
	    get_value ()) ? TRUE : FALSE;
    }
    return rv;
}


t_boolean
I_current_state_var::reassign (const I_var* p_var_ptr)

{
    t_boolean rv = FALSE;
    if (((I_var*) p_var_ptr)->get_current_state_var_ptr ())
    {
	set_value  (((I_var*) p_var_ptr)->get_current_state_var_ptr ()->
	    get_value ());
	override_value_str (((I_var*) p_var_ptr)->get_value_str ());
	rv = TRUE;
    }
    else
    {
        Description err_msg	("Attempting to assign a ");
        err_msg += p_var_ptr->get_data_type_str();
        err_msg += " variable to a ";
        err_msg += get_data_type_str();
        err_msg += " variable";
	    GS_ui::inform (UI_INFORM__ERROR, err_msg);
    }
    return rv;
}


I_var*
I_current_state_var::clone_to_transient () const

{
    return new I_current_state_var (*this);
}


I_var*
I_current_state_var::clone_to_persistent () const

{
    return new (GS_gen_sim_db_ptr, I_current_state_var::get_mc_dbms_typespec ())
	I_current_state_var (*this);
}


void
I_current_state_var::set_value (t_uint p_current_state)

{
    m_current_state = p_current_state;
    set_current_state_str ();
}


void
I_current_state_var::set_current_state_str ()

{
    if (get_is_initialized ())
    {
	m_current_state_str = "state name not known";
    }
    else
    {
	m_current_state_str = "un-initialized";
    }
}









//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////


I_object_inst_ref_var::I_object_inst_ref_var
    (const I_object_inst_ref_var* p_object_inst_ref_var_ptr)

{
    m_obj_ptr = p_object_inst_ref_var_ptr->m_obj_ptr;
    m_oinst_ptr = p_object_inst_ref_var_ptr->m_oinst_ptr;
    m_last_resort_key_letters
	= p_object_inst_ref_var_ptr->m_last_resort_key_letters;
    set_object_inst_ref_str ();
    get_extent()->insert( this );    // i2744.2.1
}


I_object_inst_ref_var::I_object_inst_ref_var
    (I_object_inst_ref_set_var* p_inst_set_var_ptr)

{
    m_obj_ptr = p_inst_set_var_ptr->m_obj_ptr;
    m_last_resort_key_letters
	= p_inst_set_var_ptr->m_last_resort_key_letters;

    if (p_inst_set_var_ptr->cursor () > p_inst_set_var_ptr->cardinality ())
    {
	LOG_ERROR ((L_log_string,
	    "I_object_inst_ref_var::I_object_inst_ref_var (I_object_inst_ref_set_var*):  p_inst_set_var_ptr->cursor () exceeds the cardinality ()"));
	m_oinst_ptr = 0;
    }
    else if ((p_inst_set_var_ptr->cursor () < 1)
	&& (p_inst_set_var_ptr->cardinality () >= 1))
    {
	LOG_ERROR ((L_log_string,
	    "I_object_inst_ref_var::I_object_inst_ref_var (I_object_inst_ref_set_var*):  p_inst_set_var_ptr->cursor ()."));
	m_oinst_ptr = 0;
    }
    else
    {
	m_oinst_ptr = p_inst_set_var_ptr->m_oinst_coll.retrieve
	    (p_inst_set_var_ptr->cursor () - 1);
    }

    set_object_inst_ref_str ();
    get_extent()->insert( this );   // i2744.2.1
}


I_object_inst_ref_var::I_object_inst_ref_var
    (I_Object* p_obj_ptr, I_Object_Instance* p_oinst_ptr)

{
    m_obj_ptr = p_obj_ptr;
    m_oinst_ptr = p_oinst_ptr;
    set_object_inst_ref_str ();
    get_extent()->insert( this );   // i2744.2.1
}


Description
I_object_inst_ref_var::get_key_letters_str () const

{
    Description return_str;
    if (m_obj_ptr != 0)
    {
	return_str = m_obj_ptr->get_key_letter ();
    }
    else
    {
	return_str = m_last_resort_key_letters;
    }

    return return_str;
}


t_boolean
I_object_inst_ref_var::is_empty () const

{
    return (m_oinst_ptr == 0) ? TRUE : FALSE;
}    


t_boolean
I_object_inst_ref_var::is_valid_attr_name
    (const Description& p_attr_name_str) const

{
    if (m_obj_ptr == 0)
    {
        LOG_ERROR ((L_log_string,
	    "I_object_inst_ref_var::is_valid_attr_name ():  m_obj_ptr == 0."));
        return FALSE;
    }
    

    Description attr_name_str (p_attr_name_str);
    mc_dbms_Set <I_Attribute*>* attr_coll_ptr
        = m_obj_ptr->find_Attribute_R102_by_name (attr_name_str.char_ptr ());
    if (! attr_coll_ptr)
    {
	LOG_ERROR ((L_log_string,
	    "I_object_inst_ref_var::is_valid_attr_name ():  I_Attribute find return a 0 pointer."));
	return FALSE;
    }

    if (attr_coll_ptr->cardinality () < 1)
    {
	delete attr_coll_ptr;
	attr_name_str.convert_to_upper_case ();
	attr_coll_ptr =
	    m_obj_ptr->find_Attribute_R102_by_name (attr_name_str.char_ptr ());
	if (! attr_coll_ptr)
	{
	    LOG_ERROR ((L_log_string,
		"GS_inst_var::get_value_type ():  I_Attribute find return a 0 pointer."));
	    return FALSE;
	}
	if (attr_coll_ptr->cardinality () < 1)
	{
		Description err_msg("Neither attribute '");
		err_msg += get_key_letters_str (); 
		err_msg	+= ".";
		err_msg += p_attr_name_str;
		err_msg += "'  nor attribute  '";
		err_msg += get_key_letters_str ();
		err_msg += ".";
		err_msg += attr_name_str;
		err_msg += "' is a valid attribute.";
	    GS_ui::inform (UI_INFORM__ERROR, err_msg);
	    delete attr_coll_ptr;
	    return FALSE;
	}
    }

    if (attr_coll_ptr->cardinality () > 1)
    {
	    Description err_msg ("More than one attribute with name '");
        err_msg += get_key_letters_str ();
		err_msg += ".";
		err_msg += p_attr_name_str;
		err_msg += "' exists.";
        GS_ui::inform (UI_INFORM__ERROR, err_msg );
	delete attr_coll_ptr;
        return FALSE;
    }

    delete attr_coll_ptr;
    return TRUE;
}


t_boolean
I_object_inst_ref_var::reassign (const I_var* p_var_ptr)

{
    t_boolean rv = FALSE;

    if (((I_var*) p_var_ptr)->get_object_inst_ref_var_ptr ())
    {
	if (get_key_letters_str () == ((I_var*) p_var_ptr)->
	    get_object_inst_ref_var_ptr ()->get_key_letters_str ())
	{
	    m_oinst_ptr = ((I_var*) p_var_ptr)->get_object_inst_ref_var_ptr ()->
		m_oinst_ptr;
	    rv = TRUE;
	}
	else
	{
		Description err_msg	("Unable to reassign type inst_ref<");
		err_msg += ((I_var*) p_var_ptr)->get_object_inst_ref_var_ptr ()->
		     get_key_letters_str ();
		err_msg += "> to inst_ref<";
		err_msg += get_key_letters_str ();
		err_msg += ">.";
	    GS_ui::inform (UI_INFORM__ERROR, err_msg);
	}
    }

    set_object_inst_ref_str ();
    return rv;
}


I_var*
I_object_inst_ref_var::clone_to_transient () const

{
    return new I_object_inst_ref_var (*this);
}


I_var*
I_object_inst_ref_var::clone_to_persistent () const

{
    return new (GS_gen_sim_db_ptr, I_object_inst_ref_var::get_mc_dbms_typespec ())
	I_object_inst_ref_var (*this);
}

I_Attribute_Instance*
I_object_inst_ref_var::get_attr_inst_ptr (const Description& p_attr_name_str)

{
    if (m_oinst_ptr == 0)
      {
        Description err_msg("Instance Reference Variable for Object '");
        err_msg += get_key_letters_str ();
        err_msg += "' has cardinality 0.";
        GS_ui::inform (UI_INFORM__ERROR, err_msg );
        return 0;
      }

    mc_dbms_List <I_Attribute_Instance*>* ainst_coll_ptr
        = m_oinst_ptr->get_Attribute_Instance_R2002_coll_ptr ();

    // i2744.5.1 deletion

    Description cap_attr_name_str (p_attr_name_str);
    cap_attr_name_str.convert_to_upper_case ();


    for (t_uint i = 0;
        i < ainst_coll_ptr->cardinality ();
        i++)
    {
        I_Attribute_Instance* ainst_ptr = ainst_coll_ptr->retrieve (i);
        if (! ainst_ptr)
        {
            LOG_ERROR ((L_log_string,
		"GS_inst_var::get_attr_inst_ptr ():  I_Attribute_Instance at cursor has 0 pointer."));
            return 0;
        }
        
        I_Attribute* attr_ptr = ainst_ptr->get_Attribute_R2002_ptr ();
        if (! attr_ptr)
        {
            LOG_ERROR ((L_log_string,
		"GS_inst_var::get_attr_inst_ptr ():  An I_Attribute_Instance is NOT related to an I_Attribute."));
            return 0;
        }
        
        if (p_attr_name_str == attr_ptr->get_name ())
        {
            return ainst_ptr;
        }

        if (cap_attr_name_str == attr_ptr->get_name ())
        {
            return ainst_ptr;
        }
    }
    
    
    Description err_msg("Neither attribute '");
	err_msg += get_key_letters_str ();
	err_msg +=  ".";
	err_msg += p_attr_name_str;
	err_msg += "'  nor attribute  '";
	err_msg += get_key_letters_str ();
	err_msg += ".";
	err_msg += cap_attr_name_str;
	err_msg += "' is a valid attribute.";
	GS_ui::inform (UI_INFORM__ERROR, err_msg );
    return 0;
}


I_var*
I_object_inst_ref_var::get_attr_var_ptr (const Description& p_attr_name_str)

{
    I_Attribute_Instance* ainst_ptr = get_attr_inst_ptr( p_attr_name_str );
    if (ainst_ptr != 0)
    {
        return ainst_ptr->get_var_ptr ();
    }
    
    return 0;
}


I_Object_Instance*
I_object_inst_ref_var::get_oinst_ptr ()

{
    return m_oinst_ptr;
}


void
I_object_inst_ref_var::set_oinst_ptr (I_Object_Instance* p_oinst_ptr)

{
    m_oinst_ptr = p_oinst_ptr;

    if ((m_oinst_ptr)
	&&
	(m_oinst_ptr->get_Object_R2001_ptr () != m_obj_ptr))
    {
	if (m_obj_ptr)
	{
	    LOG_ERROR ((L_log_string,
		"I_object_inst_ref_var::set_oinst_ptr () - m_obj_ptr != m_oinst_ptr->get_Object_R2001_ptr."));
	}
	m_obj_ptr = m_oinst_ptr->get_Object_R2001_ptr ();
    }

    set_object_inst_ref_str ();
}


I_Object*
I_object_inst_ref_var::get_obj_ptr ()

{
    return m_obj_ptr;
}


void
I_object_inst_ref_var::set_obj_ptr (I_Object* p_obj_ptr)

{
    m_obj_ptr = p_obj_ptr;

    if ((m_oinst_ptr)
	&&
	(m_oinst_ptr->get_Object_R2001_ptr () != m_obj_ptr))
    {
	LOG_ERROR ((L_log_string,
	    "I_object_inst_ref_var::set_obj_ptr () - m_obj_ptr != m_oinst_ptr->get_Object_R2001_ptr."));
	m_oinst_ptr = 0;
    }

    set_object_inst_ref_str ();
}


t_boolean
I_object_inst_ref_var::operator== (const I_var& p_var) const

{
    t_boolean rv = FALSE;
    if (((I_var&) p_var).get_object_inst_ref_var_ptr ())
    {
	rv = (m_oinst_ptr ==
	    ((I_var&) p_var).get_object_inst_ref_var_ptr ()->m_oinst_ptr)
	    ? TRUE : FALSE;
    }
    return rv;
}


void
I_object_inst_ref_var::set_object_inst_ref_str ()

{
    if (get_is_initialized ())
    {
	if (m_oinst_ptr)
	{
	    if (m_obj_ptr)
	    {
		m_object_inst_ref_str = m_obj_ptr->get_key_letter ();
	    }
	    else
	    {
		m_object_inst_ref_str = m_last_resort_key_letters;
	    }
	    m_object_inst_ref_str += "_";
	    char buffer [32];
	    sprintf (buffer, "%06x",
		m_oinst_ptr->get_object_instance_ID ().get_entire_value ());
	    m_object_inst_ref_str += buffer;
	}
	else
	{
	    m_object_inst_ref_str = "empty instance reference for object ";
	    if (m_obj_ptr)
	    {
		m_object_inst_ref_str += m_obj_ptr->get_key_letter ();
	    }
	    else
	    {
		m_object_inst_ref_str += m_last_resort_key_letters;
	    }
	}
    }
    else
    {
	m_object_inst_ref_str = "un-initialized";
    }
}


// i2744.1.4 begin 
mc_dbms_List<I_object_inst_ref_var*> * 
I_object_inst_ref_var::get_extent()
{
   if ( m_extent_coll == 0 )
   {
      m_extent_coll = new mc_dbms_List<I_object_inst_ref_var*>;
   }
   return m_extent_coll;
}
// i2744.1.4 end





//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////


I_object_inst_ref_set_var::I_object_inst_ref_set_var (bool isRestoring)

{
    m_obj_ptr = 0;
    if ( !isRestoring ) {
	    m_cursor = (cardinality () >= 1) ? 1 : 0;
	    set_object_inst_ref_set_str ();
	}
}


I_object_inst_ref_set_var::I_object_inst_ref_set_var
    (const I_object_inst_ref_set_var& p_object_inst_ref_set_var)

{
    m_obj_ptr = p_object_inst_ref_set_var.m_obj_ptr;
    m_oinst_coll = p_object_inst_ref_set_var.m_oinst_coll;
    m_cursor = (cardinality () >= 1) ? 1 : 0;
    m_last_resort_key_letters
	= p_object_inst_ref_set_var.m_last_resort_key_letters;

    set_object_inst_ref_set_str ();
}


I_object_inst_ref_set_var&
I_object_inst_ref_set_var::operator=
    (const I_object_inst_ref_set_var& p_object_inst_ref_set_var)

{
    m_obj_ptr = p_object_inst_ref_set_var.m_obj_ptr;
    m_oinst_coll = p_object_inst_ref_set_var.m_oinst_coll;
    m_cursor = (cardinality () >= 1) ? 1 : 0;
    m_last_resort_key_letters
	= p_object_inst_ref_set_var.m_last_resort_key_letters;
    set_object_inst_ref_set_str ();
    return *this;
}


t_boolean
I_object_inst_ref_set_var::operator== (const I_var& p_var) const

{
    t_boolean rv = FALSE;
    if (((I_var&) p_var).get_object_inst_ref_set_var_ptr ())
    {
	if (m_obj_ptr == ((I_var&) p_var).
		get_object_inst_ref_set_var_ptr ()->m_obj_ptr)
	{
	    rv = (m_oinst_coll == ((I_var&) p_var).
		get_object_inst_ref_set_var_ptr ()->m_oinst_coll)
		? TRUE : FALSE;
	}
	else
	{
	    Description	err_msg("Attempting to compare object reference set for object '");
		err_msg += get_key_letters_str ();
		err_msg += "' to object reference set for object '";
		err_msg += ((I_var&) p_var).get_object_inst_ref_set_var_ptr ()->
		    get_key_letters_str () ;
		err_msg += "'.";
		GS_ui::inform (UI_INFORM__ERROR, err_msg );
	}
    }
    else
    {
	Description err_msg("Attempting to compare an rvalue which is not an object ");
	err_msg += "instance reference set to object instance reference set.";
	GS_ui::inform (UI_INFORM__ERROR, err_msg);
    }
    return rv;
}


t_boolean
I_object_inst_ref_set_var::reassign (const I_var* p_var_ptr)

{
    t_boolean rv = FALSE;
    if (((I_var*) p_var_ptr)->get_object_inst_ref_set_var_ptr ())
    {
	if (m_obj_ptr == ((I_var*) p_var_ptr)->
	    get_object_inst_ref_set_var_ptr ()->m_obj_ptr)
	{
	    m_oinst_coll = ((I_var*) p_var_ptr)->
		get_object_inst_ref_set_var_ptr ()->m_oinst_coll;
	    rv = TRUE;
	}
	else
	{
	    Description	err_msg("Unable to reassign type inst_ref_set<");
		err_msg += ((I_var*) p_var_ptr)->get_object_inst_ref_set_var_ptr ()->
		     get_key_letters_str ();
		err_msg += "> to inst_ref_set<";
		err_msg += get_key_letters_str ();
		err_msg += ">.";
		GS_ui::inform (UI_INFORM__ERROR, err_msg);
	}
    }
    else
    {
	Description err_msg("Attempting to reassign an rvalue which is not an object ");
	err_msg += "instance reference set to object instance reference set.";
	GS_ui::inform (UI_INFORM__ERROR, err_msg);
    }
    m_cursor = (cardinality () >= 1) ? 1 : 0;
    set_object_inst_ref_set_str ();
    return rv;
}


I_var*
I_object_inst_ref_set_var::clone_to_transient () const

{
    return new I_object_inst_ref_set_var (*this);
}


I_var*
I_object_inst_ref_set_var::clone_to_persistent () const

{
    return new
	(GS_gen_sim_db_ptr, I_object_inst_ref_set_var::get_mc_dbms_typespec ())
	I_object_inst_ref_set_var (*this);
}


I_object_inst_ref_set_var::I_object_inst_ref_set_var
    (I_object_inst_ref_set_var* p_object_inst_ref_set_var_ptr)

{
    m_obj_ptr = p_object_inst_ref_set_var_ptr->m_obj_ptr;
    m_oinst_coll = p_object_inst_ref_set_var_ptr->m_oinst_coll;
    m_cursor = (cardinality () >= 1) ? 1 : 0;
    m_last_resort_key_letters
	= p_object_inst_ref_set_var_ptr->m_last_resort_key_letters;
    set_object_inst_ref_set_str ();
}


I_object_inst_ref_set_var::I_object_inst_ref_set_var
    (I_Object* p_obj_ptr,
    const mc_dbms_List <I_Object_Instance*>* p_oinst_coll_ptr)

{
    if (p_obj_ptr)
    {
	m_obj_ptr = p_obj_ptr;
    }
    else
    {
	m_obj_ptr = 0;
	GS_ui::inform (UI_INFORM__ERROR, GS_string("Internal Error."));
	LOG_ERROR ((L_log_string,
	    "I_object_inst_ref_set_var::I_object_inst_ref_set_var (I_Object*,coll) - p_obj_ptr == 0."));
    }
    if (p_oinst_coll_ptr)
    {
        m_oinst_coll = *p_oinst_coll_ptr;
    }
    else
    {
	GS_ui::inform (UI_INFORM__ERROR, GS_string("Internal Error."));
	LOG_ERROR ((L_log_string,
	    "I_object_inst_ref_set_var::I_object_inst_ref_set_var (I_Object*,coll) - p_oinst_coll_ptr == 0."));
    }
    m_cursor = (cardinality () >= 1) ? 1 : 0;
    set_object_inst_ref_set_str ();
}


I_object_inst_ref_set_var::I_object_inst_ref_set_var
    (const I_object_inst_ref_var* p_object_inst_ref_var_ptr)

{
    if (p_object_inst_ref_var_ptr)
    {
	m_obj_ptr = p_object_inst_ref_var_ptr->m_obj_ptr;
	if (p_object_inst_ref_var_ptr->m_oinst_ptr != 0)
	{
	    m_oinst_coll.insert_last (p_object_inst_ref_var_ptr->m_oinst_ptr);
	}
    }
    else
    {
	GS_ui::inform (UI_INFORM__ERROR, GS_string("Internal Error."));
	LOG_ERROR ((L_log_string,
	    "I_object_inst_ref_set_var::I_object_inst_ref_set_var (I_Object*,coll) - p_object_inst_ref_var_ptr == 0."));
    }
    m_cursor = (cardinality () >= 1) ? 1 : 0;
    m_last_resort_key_letters
	= p_object_inst_ref_var_ptr->m_last_resort_key_letters;
    set_object_inst_ref_set_str ();
}


static void l_remove_duplicates( mc_dbms_List<I_Object_Instance*>& p_inst_coll )
{
   mc_dbms_Set<I_Object_Instance*> inst_set;

   inst_set = p_inst_coll;
   if ( inst_set.cardinality() != p_inst_coll.cardinality() )
   {
       p_inst_coll.clear();
       p_inst_coll = inst_set;
   }
}

I_object_inst_ref_set_var::I_object_inst_ref_set_var
    (const I_object_inst_ref_var* p_object_inst_ref_var1_ptr,
     const I_object_inst_ref_var* p_object_inst_ref_var2_ptr,
     const GS_string& p_binary_op_str)

{
    if (p_object_inst_ref_var1_ptr->is_empty() || 
        p_object_inst_ref_var2_ptr->is_empty() )
    {
    m_obj_ptr = 0;
	Description err_msg("Attempting to operate on empty object reference");
	GS_ui::inform (UI_INFORM__ERROR, err_msg);
    }
    if (p_object_inst_ref_var1_ptr->m_obj_ptr !=
	p_object_inst_ref_var2_ptr->m_obj_ptr)
    {
        m_obj_ptr = 0;
	    Description	err_msg ("Attempting to add object reference for object '");
	    err_msg += p_object_inst_ref_var1_ptr->get_key_letters_str ();
	    err_msg += "' to object reference for object '";
	    err_msg += p_object_inst_ref_var2_ptr->get_key_letters_str ();
	    err_msg += "'.";
	    GS_ui::inform (UI_INFORM__ERROR, err_msg);
    }
    else
    {
	    m_obj_ptr = p_object_inst_ref_var1_ptr->m_obj_ptr;
        if ( p_object_inst_ref_var1_ptr->m_oinst_ptr )
        {
	        m_oinst_coll.insert_last (p_object_inst_ref_var1_ptr->m_oinst_ptr);
        }
        if ( p_object_inst_ref_var2_ptr->m_oinst_ptr )
        {
	        if (p_binary_op_str == "|")
	        {
	            m_oinst_coll |= p_object_inst_ref_var2_ptr->m_oinst_ptr;
                l_remove_duplicates ( m_oinst_coll );
	        }
	        else if (p_binary_op_str == "&")
	        {
	            m_oinst_coll &= p_object_inst_ref_var2_ptr->m_oinst_ptr;
	        }
	        else if (p_binary_op_str == "-")
	        {
	            m_oinst_coll -= p_object_inst_ref_var2_ptr->m_oinst_ptr;
	        }
	        else
	        {
	            GS_ui::inform (UI_INFORM__ERROR,
		        GS_string("Internal Error Creating INST_REF_SET."));
	            LOG_ERROR ((L_log_string,
		        "I_object_inst_ref_set_var::I_object_inst_ref_set_var () - unknown operator."));
	        }
        }
    }
    m_cursor = (cardinality () >= 1) ? 1 : 0;
    m_last_resort_key_letters
	= p_object_inst_ref_var1_ptr->m_last_resort_key_letters;
    set_object_inst_ref_set_str ();
}


I_object_inst_ref_set_var::I_object_inst_ref_set_var
    (const I_object_inst_ref_var*     p_object_inst_ref_var_ptr,
     const I_object_inst_ref_set_var* p_object_inst_ref_set_var_ptr,
     const GS_string& p_binary_op_str)

{
    if (p_object_inst_ref_var_ptr->is_empty())
    {
    m_obj_ptr = 0;
	Description err_msg("Attempting to operate on empty object reference");
	GS_ui::inform (UI_INFORM__ERROR, err_msg);
    }
    else if (p_object_inst_ref_var_ptr->m_obj_ptr !=
	p_object_inst_ref_set_var_ptr->m_obj_ptr)
    {
    m_obj_ptr = 0;
	Description err_msg("Attempting to add object reference for object '");
	err_msg += p_object_inst_ref_var_ptr->get_key_letters_str ();
	err_msg += "' to object reference set for object '";
	err_msg += p_object_inst_ref_set_var_ptr->get_key_letters_str ();
	err_msg += "'.";
	GS_ui::inform (UI_INFORM__ERROR, err_msg);
    }
    else
    {
	m_obj_ptr = p_object_inst_ref_var_ptr->m_obj_ptr;
   	m_oinst_coll.insert_last (p_object_inst_ref_var_ptr->m_oinst_ptr);

    if (p_binary_op_str == "|")
	{
	    m_oinst_coll |= p_object_inst_ref_set_var_ptr->m_oinst_coll;
        l_remove_duplicates ( m_oinst_coll );
	}
	else if (p_binary_op_str == "&")
	{
	    m_oinst_coll &= p_object_inst_ref_set_var_ptr->m_oinst_coll;
	}
	else if (p_binary_op_str == "-")
	{
	    m_oinst_coll -= p_object_inst_ref_set_var_ptr->m_oinst_coll;
	}
	else
	{
	    GS_ui::inform (UI_INFORM__ERROR,
		GS_string("Internal Error Creating INST_REF_SET."));
	    LOG_ERROR ((L_log_string,
		"I_object_inst_ref_set_var::I_object_inst_ref_set_var () - unknown operator."));
	}
    }
    m_cursor = (cardinality () >= 1) ? 1 : 0;
    m_last_resort_key_letters
	= p_object_inst_ref_var_ptr->m_last_resort_key_letters;
    set_object_inst_ref_set_str ();
}


I_object_inst_ref_set_var::I_object_inst_ref_set_var
    (const I_object_inst_ref_set_var* p_object_inst_ref_set_var_ptr,
     const I_object_inst_ref_var*     p_object_inst_ref_var_ptr,
     const GS_string& p_binary_op_str)

{
    if (p_object_inst_ref_var_ptr->is_empty())
    {
    m_obj_ptr = 0;
	Description err_msg("Attempting to operate on empty object reference");
	GS_ui::inform (UI_INFORM__ERROR, err_msg);
    }
    else if (p_object_inst_ref_var_ptr->m_obj_ptr !=
	p_object_inst_ref_set_var_ptr->m_obj_ptr)
    {
    m_obj_ptr = 0;
	Description err_msg("Attempting to add object reference set for object '");
	err_msg += p_object_inst_ref_set_var_ptr->get_key_letters_str ();
	err_msg += "' to object reference for object '";
	err_msg += p_object_inst_ref_var_ptr->get_key_letters_str ();
	err_msg += "'.";
	GS_ui::inform (UI_INFORM__ERROR, err_msg);
    }
    else
    {
	    m_obj_ptr = p_object_inst_ref_var_ptr->m_obj_ptr;
	    m_oinst_coll = p_object_inst_ref_set_var_ptr->m_oinst_coll;
	    if (p_binary_op_str == "|")
	    {
	        m_oinst_coll |= p_object_inst_ref_var_ptr->m_oinst_ptr;
            l_remove_duplicates ( m_oinst_coll );
	    }
	    else if (p_binary_op_str == "&")
	    {
	        m_oinst_coll &= p_object_inst_ref_var_ptr->m_oinst_ptr;
	    }
	    else if (p_binary_op_str == "-")
	    {
	        m_oinst_coll -= p_object_inst_ref_var_ptr->m_oinst_ptr;
	    }
	    else
	    {
	        GS_ui::inform (UI_INFORM__ERROR,
		    GS_string("Internal Error Creating INST_REF_SET."));
	        LOG_ERROR ((L_log_string,
		    "I_object_inst_ref_set_var::I_object_inst_ref_set_var () - unknown operator."));
	    }
    }
    m_cursor = (cardinality () >= 1) ? 1 : 0;
    m_last_resort_key_letters
	= p_object_inst_ref_set_var_ptr->m_last_resort_key_letters;
    set_object_inst_ref_set_str ();
}


I_object_inst_ref_set_var::I_object_inst_ref_set_var
    (const I_object_inst_ref_set_var* p_object_inst_ref_set_var1_ptr,
     const I_object_inst_ref_set_var* p_object_inst_ref_set_var2_ptr,
     const GS_string& p_binary_op_str)

{
    if (p_object_inst_ref_set_var1_ptr->m_obj_ptr !=
	p_object_inst_ref_set_var2_ptr->m_obj_ptr)
    {
    m_obj_ptr = 0;
	Description err_msg("Attempting to add object reference set for object '");
	err_msg += p_object_inst_ref_set_var1_ptr->get_key_letters_str ();
	err_msg += "' to object reference set for object '";
	err_msg += p_object_inst_ref_set_var2_ptr->get_key_letters_str (); 
	err_msg += "'.";
	GS_ui::inform (UI_INFORM__ERROR, err_msg);
    }
    else
    {
	m_obj_ptr = p_object_inst_ref_set_var1_ptr->m_obj_ptr;
	m_oinst_coll  = p_object_inst_ref_set_var1_ptr->m_oinst_coll;
	if (p_binary_op_str == "|")
	{
	    m_oinst_coll |= p_object_inst_ref_set_var2_ptr->m_oinst_coll;
        l_remove_duplicates ( m_oinst_coll );
	}
	else if (p_binary_op_str == "&")
	{
	    m_oinst_coll &= p_object_inst_ref_set_var2_ptr->m_oinst_coll;
	}
	else if (p_binary_op_str == "-")
	{
	    m_oinst_coll -= p_object_inst_ref_set_var2_ptr->m_oinst_coll;
	}
	else
	{
	    GS_ui::inform (UI_INFORM__ERROR,
		GS_string("Internal Error Creating INST_REF_SET."));
	    LOG_ERROR ((L_log_string,
		"I_object_inst_ref_set_var::I_object_inst_ref_set_var () - unknown operator."));
	}
    }
    m_cursor = (cardinality () >= 1) ? 1 : 0;
    m_last_resort_key_letters
	= p_object_inst_ref_set_var1_ptr->m_last_resort_key_letters;
    set_object_inst_ref_set_str ();
}


Description
I_object_inst_ref_set_var::get_key_letters_str () const

{
    Description return_str;
    if (m_obj_ptr != 0)
    {
	return_str = m_obj_ptr->get_key_letter ();
    }
    else
    {
	return_str = m_last_resort_key_letters;
    }

    return return_str;
}


void
I_object_inst_ref_set_var::first ()

{
    m_cursor = 1;
}


void
I_object_inst_ref_set_var::next ()
{
    m_cursor++;
}


t_boolean
I_object_inst_ref_set_var::is_empty () const

{
    return (cardinality () == 0) ? TRUE : FALSE;
}    


t_boolean
I_object_inst_ref_set_var::is_first () const

{
    return (cursor () == 1) ? TRUE : FALSE;
}


t_boolean
I_object_inst_ref_set_var::is_last () const

{
    return (cursor () == cardinality ()) ? TRUE : FALSE;
}


t_boolean
I_object_inst_ref_set_var::is_done () const

{
    return (cursor () > cardinality ()) ? TRUE : FALSE;
}


t_uint
I_object_inst_ref_set_var::cardinality () const

{
    return m_oinst_coll.cardinality ();
}


t_uint
I_object_inst_ref_set_var::cursor () const

{
    return m_cursor;
}


I_Object_Instance*
I_object_inst_ref_set_var::get_oinst_ptr ()

{
    if ((m_cursor >= 1) && (m_cursor <= cardinality ()))
    {
	return m_oinst_coll.retrieve (m_cursor - 1);
    }

    return 0;
}


I_Object*
I_object_inst_ref_set_var::get_obj_ptr ()

{
    return m_obj_ptr;
}


void
I_object_inst_ref_set_var::set_object_inst_ref_set_str ()

{
    if (get_is_initialized ())
    {
	m_object_inst_ref_set_str = "set of ";
	char buffer [32];
	sprintf (buffer, "%d", cardinality ());
	m_object_inst_ref_set_str += buffer;
	m_object_inst_ref_set_str += " instance references for object ";
	if (m_obj_ptr)
	{
	    m_object_inst_ref_set_str += m_obj_ptr->get_key_letter ();
	}
	else
	{
	    m_object_inst_ref_set_str += m_last_resort_key_letters;
	}
    }
    else
    {
	m_object_inst_ref_set_str = "un-initialized";
    }
}








//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////


I_event_inst_var::I_event_inst_var (bool isRestoring)

{
	if ( !isRestoring ) {
	    m_einst_id = Id::Default;
	    set_event_inst_str ();
	}
}


I_event_inst_var::I_event_inst_var (const I_event_inst_var& p_event_inst_var)

{
    m_einst_id = Id::Default;
    set_event_inst_str ();


    if (p_event_inst_var.m_einst_id == Id::Default)
    {
	//  This event instance variable is uninitialized.
	//
	return;
    }


    I_SM_Evt_Inst* einst_ptr
	= ((I_event_inst_var&) p_event_inst_var).get_einst_ptr ();
    if (! einst_ptr)
    {
	//  The event instance must have been deleted.  Error message already
	//    printed.
	//
	return;
    }


    I_SM_Evt_Inst* new_einst_ptr
	= I_SM_Evt_Inst::copy__I_SM_Evt_Inst (einst_ptr);
    if (! new_einst_ptr)
    {
	//  The new event instance could not be created.  Leave this event
	//    instance as uninitialized.
	//
	LOG_ERROR ((L_log_string,
	    "I_event_inst_var::I_event_inst_var (const I_event_inst_var&):  new_einst_ptr == 0."));
	return;
    }


    m_einst_id = new_einst_ptr->get_evt_inst_ID ();
    set_event_inst_str ();
}


I_event_inst_var&
I_event_inst_var::operator= (const I_event_inst_var& p_event_inst_var)

{
    //  Delete the current event instance.
    //
    if (m_einst_id != Id::Default)
    {
	I_SM_Evt_Inst* einst_ptr = get_einst_ptr ();
	if (einst_ptr)
	{
	    I_SM_Evt_Inst::delete__I_SM_Evt_Inst (einst_ptr);
	}
	else
	{
	    LOG_ERROR ((L_log_string,
		"I_event_inst_var::operator= ():  einst_ptr == 0."));
	}
    }


    m_einst_id = Id::Default;
    set_event_inst_str ();


    if (p_event_inst_var.m_einst_id != Id::Default)
    {
	I_SM_Evt_Inst* einst_ptr
	    = ((I_event_inst_var&) p_event_inst_var).get_einst_ptr ();
	if (! einst_ptr)
	{
	    LOG_ERROR ((L_log_string,
		"I_event_inst_var::operator= ():  einst_ptr == 0."));
	    return *this;
	}

	I_SM_Evt_Inst* new_einst_ptr
	    = I_SM_Evt_Inst::copy__I_SM_Evt_Inst (einst_ptr);
	if (! new_einst_ptr)
	{
	    //  The new event instance could not be created.  Create an
	    //    uninitialized event instance in its place.
	    //
	    LOG_ERROR ((L_log_string,
		"I_event_inst_var::operator= ():  new_einst_ptr == 0."));
	    return *this;
	}

	m_einst_id = new_einst_ptr->get_evt_inst_ID ();
	set_event_inst_str ();
    }


    return *this;
}


t_boolean
I_event_inst_var::operator== (const I_var& p_var) const

{
    t_boolean rv = FALSE;
    if (((I_var&)p_var).get_event_inst_var_ptr ())
    {
        // cast away the constness
        I_SM_Evt_Inst* einst_ptr1
	        = ((I_event_inst_var*)this)->get_einst_ptr ();

        // cast away the constness
        I_SM_Evt_Inst* einst_ptr2
	        = ((I_var&)p_var).get_event_inst_var_ptr ()->get_einst_ptr ();

        if ( einst_ptr1 && einst_ptr2 )
        {
            rv = (*einst_ptr1) == (*einst_ptr2);
        }
    }
    return rv;
}


t_boolean
I_event_inst_var::reassign (const I_var* p_var_ptr)

{
    if (! (((I_var*) p_var_ptr)->get_event_inst_var_ptr ()))
    {
        Description err_msg	("Attempting to assign a ");
        err_msg += p_var_ptr->get_data_type_str();
        err_msg += " variable to a ";
        err_msg += get_data_type_str();
        err_msg += " variable";
	    GS_ui::inform (UI_INFORM__ERROR, err_msg);
    	return FALSE;
    }


    //  Delete the current event instance.
    //
    if (m_einst_id != Id::Default)
    {
	I_SM_Evt_Inst* einst_ptr = get_einst_ptr ();
	if (einst_ptr)
	{
	    I_SM_Evt_Inst::delete__I_SM_Evt_Inst (einst_ptr);
	}
	else
	{
	    LOG_ERROR ((L_log_string,
		"I_event_inst_var::reassign ():  einst_ptr == 0."));
	}
    }


    m_einst_id = Id::Default;
    set_event_inst_str ();


    if (((I_var*) p_var_ptr)->get_event_inst_var_ptr ()->m_einst_id
	!= Id::Default)
    {
	I_SM_Evt_Inst* einst_ptr =
	    ((I_var*) p_var_ptr)->get_event_inst_var_ptr ()->get_einst_ptr ();
	if (! einst_ptr)
	{
	    LOG_ERROR ((L_log_string,
		"I_event_inst_var::reassign ():  einst_ptr == 0."));
	    return FALSE;
	}

	I_SM_Evt_Inst* new_einst_ptr
	    = I_SM_Evt_Inst::copy__I_SM_Evt_Inst (einst_ptr);
	if (! new_einst_ptr)
	{
	    //  The new event instance could not be created.  Create an
	    //    uninitialized event instance in its place.
	    //
	    LOG_ERROR ((L_log_string,
		"I_event_inst_var::reassign ():  new_einst_ptr == 0."));
	    return FALSE;
	}

	m_einst_id = new_einst_ptr->get_evt_inst_ID ();
	set_event_inst_str ();
    }


    return TRUE;
}


I_var*
I_event_inst_var::clone_to_transient () const

{
    return new I_event_inst_var (*this);
}


I_var*
I_event_inst_var::clone_to_persistent () const

{
    return new (GS_gen_sim_db_ptr, I_event_inst_var::get_mc_dbms_typespec ())
	I_event_inst_var (*this);
}


I_event_inst_var::~I_event_inst_var ()

{
    LOG_TRACE (L_D_DATA, L_FUNCTION_BEGIN, (L_log_string,
	"Begin  I_event_inst_var::~I_event_inst_var ()."));


    //  Delete the current event instance.
    //
    I_SM_Evt_Inst* einst_ptr = get_einst_ptr ();
    if (einst_ptr)
    {
	I_SM_Evt_Inst::delete__I_SM_Evt_Inst (einst_ptr);
    }

    operator delete( this, ""); // Remove from InstanceTracker

    LOG_TRACE (L_D_DATA, L_FUNCTION_END, (L_log_string,
	"End  I_event_inst_var::~I_event_inst_var ()."));
}


I_SM_Evt_Inst*
I_event_inst_var::get_einst_ptr ()

{
    LOG_TRACE (L_D_DATA, L_FUNCTION_BEGIN, (L_log_string,
	"Begin  I_event_inst_var::get_einst_ptr ()."));


    if (m_einst_id == Id::Default)
    {
	LOG_TRACE (L_D_DATA, L_FUNCTION_END, (L_log_string,
	    "End #1:  I_event_inst_var::get_einst_ptr (einst_ptr=0x0):  m_einst_id == ID::Default"));
	return 0;
    }


    I_SM_Evt_Inst* einst_ptr
	= I_SM_Evt_Inst::find_SM_Evt_Inst_by_evt_inst_ID
	    (GS_gen_sim_db_ptr, m_einst_id);
    if (einst_ptr)
    {
	LOG_TRACE (L_D_DATA, L_FUNCTION_END, (L_log_string,
	    "End #2:  I_event_inst_var::get_einst_ptr (einst_ptr=0x%08x).",
	    einst_ptr));
	return einst_ptr;
    }


    LOG_TRACE (L_D_DATA, L_FUNCTION_END, (L_log_string,
	"End #3:  I_event_inst_var::get_einst_ptr (einst_ptr=0x0):  m_einst_id != Id::Default but is not found...setting it to Id::Default for future efficiency."));
    m_einst_id = Id::Default;
    set_event_inst_str ();
    return 0;
}


void
I_event_inst_var::set_einst_id (const Id& p_einst_id)

{
    //  Delete the current event instance.
    //
    if (m_einst_id != Id::Default)
    {
	I_SM_Evt_Inst* einst_ptr = get_einst_ptr ();
	if (einst_ptr)
	{
	    I_SM_Evt_Inst::delete__I_SM_Evt_Inst (einst_ptr);
	}
	else
	{
	    LOG_ERROR ((L_log_string,
		"I_event_inst_var::set_einst_id ():  einst_ptr == 0."));
	}
    }


    m_einst_id = Id::Default;
    set_event_inst_str ();


    if (p_einst_id != Id::Default)
    {
	I_SM_Evt_Inst* einst_ptr
	    = I_SM_Evt_Inst::find_SM_Evt_Inst_by_evt_inst_ID
		(GS_gen_sim_db_ptr, p_einst_id);
	if (! einst_ptr)
	{
	    LOG_ERROR ((L_log_string,
		"I_event_inst_var::set_einst_id ():  einst_ptr == 0."));
	    return;
	}

	m_einst_id = p_einst_id;
	set_event_inst_str ();
    }
}


void
I_event_inst_var::set_event_inst_str ()

{
    if (get_is_initialized ())
    {
	I_SM_Evt_Inst* einst_ptr = get_einst_ptr ();
	if ((einst_ptr)
	    &&
	    (einst_ptr->get_SM_Evt_R2022_ptr ()))
	{
	    m_event_inst_str = einst_ptr->get_SM_Evt_R2022_ptr ()->get_label ();
	    m_event_inst_str += "_";
	    char buffer [32];
	    sprintf (buffer, "%06x",
		einst_ptr->get_evt_inst_ID ().get_entire_value ());
	    m_event_inst_str += buffer;
	}
	else
	{
	    //  Repair error condition.
	    //
	    m_einst_id = Id::Default;
	    m_event_inst_str = "un-initialized";
	}
    }
    else
    {
	m_event_inst_str = "un-initialized";
    }
}









//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////


I_mapping_inst_var::I_mapping_inst_var (bool isRestoring)

{
	if (!isRestoring) {
	    int* next_tracking_value_ptr = 0;
	    mc_dbms_database_root* root_ptr
		= GS_gen_sim_db_ptr->find_root ("I_mapping_inst_var");
	    if (root_ptr)
	    {
		next_tracking_value_ptr = (int*) root_ptr->get_value ();
	    }
	    else
	    {
		next_tracking_value_ptr
		    = new (GS_gen_sim_db_ptr, int_type) int ((int) 1);
		(*next_tracking_value_ptr) = 1;
		GS_gen_sim_db_ptr->create_root ("I_mapping_inst_var")->
		    set_value (next_tracking_value_ptr);
	    }
	
	    m_tracking_value = (*next_tracking_value_ptr);
	    (*next_tracking_value_ptr)++;
	    set_mapping_inst_str ();
	}
}


t_boolean
I_mapping_inst_var::operator== (const I_var& p_var) const

{
    t_boolean rv = FALSE;
    if (((I_var&) p_var).get_mapping_inst_var_ptr ())
    {
	rv = (m_tracking_value ==
	    ((I_var&) p_var).get_mapping_inst_var_ptr ()->m_tracking_value)
	    ? TRUE : FALSE;
    }
    return rv;
}


t_boolean
I_mapping_inst_var::reassign (const I_var* p_var_ptr)

{
    t_boolean rv = FALSE;
    if (((I_var*) p_var_ptr)->get_mapping_inst_var_ptr ())
    {
	m_tracking_value = ((I_var*) p_var_ptr)->
	    get_mapping_inst_var_ptr ()->m_tracking_value;
	set_mapping_inst_str ();
	rv = TRUE;
    }
    else
    {
        Description err_msg	("Attempting to assign a ");
        err_msg += p_var_ptr->get_data_type_str();
        err_msg += " variable to a ";
        err_msg += get_data_type_str();
        err_msg += " variable";
	    GS_ui::inform (UI_INFORM__ERROR, err_msg);
    }
    return rv;
}


I_var*
I_mapping_inst_var::clone_to_transient () const

{
    return new I_mapping_inst_var (*this);
}


I_var*
I_mapping_inst_var::clone_to_persistent () const

{
    return new (GS_gen_sim_db_ptr, I_mapping_inst_var::get_mc_dbms_typespec ())
	I_mapping_inst_var (*this);
}


t_boolean
I_mapping_inst_var::operator< (const I_mapping_inst_var&) const

{
    return TRUE;
}


t_boolean
I_mapping_inst_var::operator<= (const I_mapping_inst_var&) const

{
    return TRUE;
}


t_boolean	
I_mapping_inst_var::operator>= (const I_mapping_inst_var&) const

{
    return TRUE;
}


t_boolean
I_mapping_inst_var::operator> (const I_mapping_inst_var&) const

{
    return TRUE;
}


void
I_mapping_inst_var::set_mapping_inst_str ()

{
    m_mapping_inst_str = "id_";
    char buffer [32];
    sprintf (buffer, "%06x", m_tracking_value);
    m_mapping_inst_str += buffer;
}









//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////


I_mapping_inst_ref_var::I_mapping_inst_ref_var (bool isRestoring)

{
	if (!isRestoring) {
	    int* next_tracking_value_ptr = 0;
	    mc_dbms_database_root* root_ptr
		= GS_gen_sim_db_ptr->find_root ("I_mapping_inst_ref_var");
	    if (root_ptr)
	    {
		next_tracking_value_ptr = (int*) root_ptr->get_value ();
	    }
	    else
	    {
		next_tracking_value_ptr
		    = new (GS_gen_sim_db_ptr, int_type) int ((int) 1);
		(*next_tracking_value_ptr) = 1;
		GS_gen_sim_db_ptr->create_root ("I_mapping_inst_ref_var")->
		    set_value (next_tracking_value_ptr);
	    }
	
	    m_tracking_value = (*next_tracking_value_ptr);
	    (*next_tracking_value_ptr)++;
	    set_mapping_inst_ref_str ();
	}
}


t_boolean
I_mapping_inst_ref_var::operator== (const I_var& p_var) const

{
    t_boolean rv = FALSE;
    if (((I_var&) p_var).get_mapping_inst_ref_var_ptr ())
    {
	rv = (m_tracking_value ==
	    ((I_var&) p_var).get_mapping_inst_ref_var_ptr ()->m_tracking_value)
	    ? TRUE : FALSE;
    }
    return rv;
}


t_boolean
I_mapping_inst_ref_var::reassign (const I_var* p_var_ptr)

{
    t_boolean rv = FALSE;
    if (((I_var*) p_var_ptr)->get_mapping_inst_ref_var_ptr ())
    {
	m_tracking_value = ((I_var*) p_var_ptr)->
	    get_mapping_inst_ref_var_ptr ()->m_tracking_value;
	set_mapping_inst_ref_str ();
	rv = TRUE;
    }
    else
    {
        Description err_msg	("Attempting to assign a ");
        err_msg += p_var_ptr->get_data_type_str();
        err_msg += " variable to a ";
        err_msg += get_data_type_str();
        err_msg += " variable";
	    GS_ui::inform (UI_INFORM__ERROR, err_msg);
    }
    return rv;
}


I_var*
I_mapping_inst_ref_var::clone_to_transient () const

{
    return new I_mapping_inst_ref_var (*this);
}


I_var*
I_mapping_inst_ref_var::clone_to_persistent () const

{
    return new (GS_gen_sim_db_ptr, I_mapping_inst_ref_var::get_mc_dbms_typespec ())
	I_mapping_inst_ref_var (*this);
}


void
I_mapping_inst_ref_var::set_mapping_inst_ref_str ()

{
    m_mapping_inst_ref_str = "id_";
    char buffer [32];
    sprintf (buffer, "%06x", m_tracking_value);
    m_mapping_inst_ref_str += buffer;
}









//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////


I_date_var::I_date_var (bool isRestoring)

{
	if (!isRestoring) {
	    vdateInit (&m_date);   
    	set_date_str ();
    }
}


I_date_var::I_date_var (const I_date_var& p_var)

{
    I_date_var* dv_ptr = (I_date_var*)&p_var;

    vdateInit (&m_date);   
    // set to a legit value so that vdateCopy works
    dv_ptr->m_date.timeZoneName = m_date.timeZoneName;
    dv_ptr->m_date.object.instance.clas = m_date.object.instance.clas;
    vdateCopy (&(dv_ptr->m_date), &m_date);
    dv_ptr->m_date.timeZoneName = 0;
    dv_ptr->m_date.object.instance.clas = 0;
    set_date_str ();
}


I_date_var&
I_date_var::operator= (const I_date_var& p_var)

{
    I_date_var* dv_ptr = (I_date_var*)&p_var;

    vdateInit (&m_date);   
    // set to a legit value so that vdateCopy works
    dv_ptr->m_date.timeZoneName = m_date.timeZoneName;
    dv_ptr->m_date.object.instance.clas = m_date.object.instance.clas;
    vdateCopy (&(dv_ptr->m_date), &m_date);
    dv_ptr->m_date.timeZoneName = 0;
    dv_ptr->m_date.object.instance.clas = 0;
    set_date_str ();
    return *this;
}


I_date_var::~I_date_var ()

{
	operator delete( this, ""); // Remove from InstanceTracker
}


t_boolean
I_date_var::operator== (const I_var& p_var) const

{
  t_boolean rv = FALSE;
  vdate date1 = m_date;
  vdate date2;

  if (! get_is_initialized ())
    {
      GS_ui::inform (UI_INFORM__ERROR,
                     GS_string("Value of type 'date' is not intialized in == operation"));
    }
  else if (((I_var&) p_var).get_date_var_ptr ())
    {
      if (! (((I_var&) p_var).get_date_var_ptr ()->get_is_initialized ()))
        {
          GS_ui::inform (UI_INFORM__ERROR,
                         GS_string("Value of type 'date' is not intialized in == operation"));
        }
      else
        {
          date2 = ((I_var&) p_var).get_date_var_ptr()->m_date;
          rv = (vdateDifference (&date1, &date2) == 0) ? TRUE : FALSE;
        }
    }
    
  return rv;
}


t_boolean
I_date_var::reassign (const I_var* p_var_ptr)

{
    t_boolean rv = FALSE;
    if (((I_var*) p_var_ptr)->get_date_var_ptr ())
    {
        I_date_var* dv_ptr = 
            ((I_var*) p_var_ptr)->get_date_var_ptr ();

        vdateInit (&m_date);   
        // set to a legit value so that vdateCopy works
        dv_ptr->m_date.timeZoneName = m_date.timeZoneName;
        dv_ptr->m_date.object.instance.clas = m_date.object.instance.clas;
    	vdateCopy (&(dv_ptr->m_date), &m_date);
        dv_ptr->m_date.timeZoneName = 0;
        dv_ptr->m_date.object.instance.clas = 0;

    	set_date_str ();
	    rv = TRUE;
    }
    else
    {
        Description err_msg	("Attempting to assign a ");
        err_msg += p_var_ptr->get_data_type_str();
        err_msg += " variable to a ";
        err_msg += get_data_type_str();
        err_msg += " variable";
	    GS_ui::inform (UI_INFORM__ERROR, err_msg);
    }
    return rv;
}


I_var*
I_date_var::clone_to_transient () const

{
    return new I_date_var (*this);
}


I_var*
I_date_var::clone_to_persistent () const

{
    return new (GS_gen_sim_db_ptr, I_date_var::get_mc_dbms_typespec ())
	I_date_var (*this);
}


t_int
I_date_var::get_second ()

{
    return vdateGetSecond (&m_date);
}


void
I_date_var::set_second (t_int p_second)

{
    int second = abs (p_second) % 60;
    vdateSetSecond (&m_date, second);
    set_date_str ();
}


t_int
I_date_var::get_minute ()

{
    return vdateGetMinute (&m_date);
}


void
I_date_var::set_minute (t_int p_minute)

{
    int minute = abs (p_minute) % 60;
    vdateSetMinute (&m_date, minute);
    set_date_str ();
}


t_int
I_date_var::get_hour ()

{
    return vdateGetHour (&m_date);
}


void
I_date_var::set_hour (t_int p_hour)

{
    int hour = abs (p_hour) % 24;
    vdateSetHour (&m_date, hour);
    set_date_str ();
}


t_int
I_date_var::get_day ()

{
    return vdateGetDay (&m_date) + 1;
}


void
I_date_var::set_day (t_int p_day)

{
    int day = abs (p_day - 1) %
	vdateGetDaysInMonth (vdateGetMonth (&m_date), vdateGetYear (&m_date));
    vdateSetDay (&m_date, day);
    set_date_str ();
}


t_int
I_date_var::get_month ()

{
    return vdateGetMonth (&m_date) + 1;
}


void
I_date_var::set_month (t_int p_month)

{
    int month = abs (p_month - 1) % 12;
    vdateSetMonth (&m_date, month);
    set_date_str ();
}


t_int
I_date_var::get_year ()

{
    return vdateGetYear (&m_date);
}


void
I_date_var::set_year (t_int p_year)

{
    int year = abs (p_year);
    vdateSetYear (&m_date, year);
    set_date_str ();
}


t_boolean
I_date_var::operator< (const I_date_var& p_var) const

{
  t_boolean rv = FALSE;
  vdate date1 = m_date;
  vdate date2;

  if (! get_is_initialized ())
    {
      GS_ui::inform (UI_INFORM__ERROR,
                     GS_string("Value of type 'date' is not intialized in < operation"));
    }
  else if (((I_var&) p_var).get_date_var_ptr ())
    {
      if (! (((I_var&) p_var).get_date_var_ptr ()->get_is_initialized ()))
        {
          GS_ui::inform (UI_INFORM__ERROR,
                         GS_string("Value of type 'date' is not intialized in < operation"));
        }
      else
        {
          date2 = ((I_var&) p_var).get_date_var_ptr()->m_date;
          rv = (vdateDifference (&date1, &date2) < 0) ? TRUE : FALSE;
        }
    }

  return rv;
}


t_boolean
I_date_var::operator<= (const I_date_var& p_var) const

{
  t_boolean rv = FALSE;
  vdate date1 = m_date;
  vdate date2;

  if (! get_is_initialized ())
    {
      GS_ui::inform (UI_INFORM__ERROR,
                     GS_string("Value of type 'date' is not intialized in <= operation"));
    }
  else if (((I_var&) p_var).get_date_var_ptr ())
    {
      if (! (((I_var&) p_var).get_date_var_ptr ()->get_is_initialized ()))
        {
          GS_ui::inform (UI_INFORM__ERROR,
                         GS_string("Value of type 'date' is not intialized in <= operation"));
        }
      else
        {
          date2 = ((I_var&) p_var).get_date_var_ptr()->m_date;
          rv = (vdateDifference (&date1, &date2) <= 0) ? TRUE : FALSE;
        }
    }

  return rv;
}


t_boolean	
I_date_var::operator>= (const I_date_var& p_var) const

{
  t_boolean rv = FALSE;
  vdate date1 = m_date;
  vdate date2;

  if (! get_is_initialized ())
    {
      GS_ui::inform (UI_INFORM__ERROR,
                     GS_string("Value of type 'date' is not intialized in >= operation"));
    }
  else if (((I_var&) p_var).get_date_var_ptr ())
    {
      if (! (((I_var&) p_var).get_date_var_ptr ()->get_is_initialized ()))
        {
          GS_ui::inform (UI_INFORM__ERROR,
                         GS_string("Value of type 'date' is not intialized in >= operation"));
        }
      else
        {
          date2 = ((I_var&) p_var).get_date_var_ptr()->m_date;
          rv = (vdateDifference (&date1, &date2) >= 0) ? TRUE : FALSE;
        }
    }

  return rv;
}


t_boolean
I_date_var::operator> (const I_date_var& p_var) const

{
  t_boolean rv = FALSE;
  vdate date1 = m_date;
  vdate date2;

  if (! get_is_initialized ())
    {
      GS_ui::inform (UI_INFORM__ERROR,
                     GS_string("Value of type 'date' is not intialized in > operation"));
    }
  else if (((I_var&) p_var).get_date_var_ptr ())
    {
      if (! (((I_var&) p_var).get_date_var_ptr ()->get_is_initialized ()))
        {
          GS_ui::inform (UI_INFORM__ERROR,
                         GS_string("Value of type 'date' is not intialized in > operation"));
        }
      else
        {
          date2 = ((I_var&) p_var).get_date_var_ptr()->m_date;
          rv = (vdateDifference (&date1, &date2) > 0) ? TRUE : FALSE;
        }
    }

  return rv;
}


t_boolean
I_date_var::get_is_initialized () const

{
    vdate l_m_date = m_date;
    vdate tmp_date;
    vdateInit (&tmp_date);   
    tmp_date.timeZoneName = 0;

    return (vdateDifference (&l_m_date, &tmp_date) == 0) ? FALSE : TRUE;
}


void
I_date_var::set_to_current_date ()

{
    vdateInit (&m_date);   
    vdateSetCurrent (&m_date);   
    set_date_str ();
}


void
I_date_var::set_to_un_initialized ()

{
    vdateInit (&m_date);   
    set_date_str ();
}


void
I_date_var::set_date_str ()

{
    if (get_is_initialized ())
    {
	vchar buffer [256];
	vcharCopyScribed (vdateScribe (&m_date), buffer);
	m_date_str = buffer;
    }
    else
    {
	m_date_str = "un-initialized";
    }

    // these are pointers to non-persistent memory, that cause
    // problems when the data type is persistent!!!
    m_date.timeZoneName = 0;
    m_date.object.instance.clas = 0;
}









//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////


I_timestamp_var::I_timestamp_var (bool isRestoring)

{
	if (!isRestoring) {
	    m_second = 0;
	    m_microsecond = 0;
	    set_timestamp_str ();
	}
}


I_timestamp_var::I_timestamp_var (const I_timestamp_var& p_timestamp_var)

{
    m_second = p_timestamp_var.m_second;
    m_microsecond = p_timestamp_var.m_microsecond;
    set_timestamp_str ();
}


I_timestamp_var&
I_timestamp_var::operator= (const I_timestamp_var& p_timestamp_var)

{
    m_second = p_timestamp_var.m_second;
    m_microsecond = p_timestamp_var.m_microsecond;
    set_timestamp_str ();
    return *this;
}


I_timestamp_var::~I_timestamp_var ()

{
	operator delete( this, ""); // Remove from InstanceTracker
}


I_timestamp_var::I_timestamp_var (t_ulong p_second, t_ulong p_microsecond)

{
    m_second = p_second + (p_microsecond / 1000000);
    m_microsecond = (p_microsecond % 1000000);
    set_timestamp_str ();
}


void
I_timestamp_var::set_microsecond (t_ulong p_microsecond)

{
    m_microsecond = (p_microsecond % 1000000);
    set_timestamp_str ();
}


void
I_timestamp_var::set_second (t_ulong p_second)

{
    m_second = p_second;
    set_timestamp_str ();
}


void
I_timestamp_var::reset ()

{
    m_second = 0;
    m_microsecond = 0;
    set_timestamp_str ();
}


t_boolean
I_timestamp_var::operator== (const I_var& p_var) const

{
    t_boolean rv = FALSE;
    if (((I_var&)p_var).get_timestamp_var_ptr ())
    {
	rv = ((m_second == ((I_var&)p_var).get_timestamp_var_ptr ()->m_second)
	    &&
	    (m_microsecond == ((I_var&)p_var).
	    get_timestamp_var_ptr ()->m_microsecond)) ? TRUE : FALSE;
    }
    return rv;
}


t_boolean
I_timestamp_var::reassign (const I_var* p_var_ptr)

{
    t_boolean rv = FALSE;
    if (((I_var*) p_var_ptr)->get_timestamp_var_ptr ())
    {
	m_second = ((I_var*) p_var_ptr)->
	    get_timestamp_var_ptr ()->m_second;
	m_microsecond = ((I_var*) p_var_ptr)->
	    get_timestamp_var_ptr ()->m_microsecond;
	set_timestamp_str ();
	rv = TRUE;
    }
    else
    {
        Description err_msg	("Attempting to assign a ");
        err_msg += p_var_ptr->get_data_type_str();
        err_msg += " variable to a ";
        err_msg += get_data_type_str();
        err_msg += " variable";
	    GS_ui::inform (UI_INFORM__ERROR, err_msg);
    }
    return rv;
}


I_var*
I_timestamp_var::clone_to_transient () const

{
    return new I_timestamp_var (*this);
}


I_var*
I_timestamp_var::clone_to_persistent () const

{
    return new (GS_gen_sim_db_ptr, I_timestamp_var::get_mc_dbms_typespec ())
	I_timestamp_var (*this);
}


I_timestamp_var&
I_timestamp_var::operator-= (const I_timestamp_var& p_time)

{
    if (m_microsecond < p_time.m_microsecond)
    {
	m_second -= 1;
	m_microsecond
	    += (1000000 - p_time.m_microsecond);
    }
    else
    {
	m_microsecond -= p_time.m_microsecond;
    }
    m_second -= p_time.m_second;
    if (m_second < 0)
    {
	m_second = 0;
    }
    set_timestamp_str ();
    return *this;
}


I_timestamp_var&
I_timestamp_var::operator+= (t_ulong p_microseconds)

{
    m_second += ((m_microsecond % 1000000) + p_microseconds) / 1000000;
    m_microsecond = ((m_microsecond % 1000000) + p_microseconds) % 1000000;
    set_timestamp_str ();
    return *this;
}


t_boolean
I_timestamp_var::operator< (const I_timestamp_var& p_time) const

{
    t_boolean rv = FALSE;
    if (m_second < p_time.m_second)
    {
	rv = TRUE;
    }
    else if ((m_second == p_time.m_second) &&
	(m_microsecond < p_time.m_microsecond))
    {
	rv = TRUE;
    }
    return rv;
}


t_boolean
I_timestamp_var::operator<= (const I_timestamp_var& p_time) const

{
    t_boolean rv = FALSE;
    if (m_second < p_time.m_second)
    {
	rv = TRUE;
    }
    else if ((m_second == p_time.m_second) &&
	(m_microsecond <= p_time.m_microsecond))
    {
	rv = TRUE;
    }
    return rv;
}


t_boolean
I_timestamp_var::operator>= (const I_timestamp_var& p_time) const

{
    t_boolean rv = FALSE;
    if (m_second > p_time.m_second)
    {
	rv = TRUE;
    }
    else if ((m_second == p_time.m_second) &&
	(m_microsecond >= p_time.m_microsecond))
    {
	rv = TRUE;
    }
    return rv;
}


t_boolean
I_timestamp_var::operator> (const I_timestamp_var& p_time) const

{
    t_boolean rv = FALSE;
    if (m_second > p_time.m_second)
    {
	rv = TRUE;
    }
    else if ((m_second == p_time.m_second) &&
	(m_microsecond > p_time.m_microsecond))
    {
	rv = TRUE;
    }
    return rv;
}


void
I_timestamp_var::set_timestamp_str ()

{
    char buffer [32];

    // Use a string from the heap to do all processing
    // That way there's only one write to the database if
    // this is a persistent instance.
    Description temp_timestamp_str;

    if ((m_second / 3600) > 0)
    {
	sprintf (buffer, "%lu", (m_second / 3600));
	temp_timestamp_str += buffer;
	temp_timestamp_str += "h ";
    }

    if ((m_second / 60) > 0)
    {
	sprintf (buffer, "%lu", ((m_second / 60) % 60));
	temp_timestamp_str += buffer;
	temp_timestamp_str += "m ";
    }

    sprintf (buffer, "%lu", (m_second % 60));
    temp_timestamp_str += buffer;
    temp_timestamp_str += "s ";

    sprintf (buffer, "%06lu", (m_microsecond % 1000000));
    temp_timestamp_str += buffer;
    temp_timestamp_str += "us";

    m_timestamp_str = temp_timestamp_str;
}









//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////


t_boolean
I_timer_inst_ref_var::operator== (const I_var& p_var) const

{
    t_boolean rv = FALSE;
    if (((I_var&)p_var).get_timer_inst_ref_var_ptr ())
    {
	rv = (m_einst_id == ((I_var&)p_var).get_timer_inst_ref_var_ptr ()->
	    m_einst_id) ? TRUE : FALSE;
    }
    return rv;
}


t_boolean
I_timer_inst_ref_var::reassign (const I_var* p_var_ptr)

{
    I_timer_inst_ref_var *tiref_var_ptr = 
        ((I_var*) p_var_ptr)->get_timer_inst_ref_var_ptr ();

    if (! tiref_var_ptr )
    {
        Description err_msg	("Attempting to assign a ");
        err_msg += p_var_ptr->get_data_type_str();
        err_msg += " variable to a ";
        err_msg += get_data_type_str();
        err_msg += " variable";
	    GS_ui::inform (UI_INFORM__ERROR, err_msg);
        return FALSE;
    }


    m_einst_id = Id::Default;
    set_timer_inst_ref_str ();


    if (tiref_var_ptr->m_einst_id != Id::Default)
    {
	I_SM_Evt_Inst* einst_ptr = tiref_var_ptr->get_einst_ptr ();
	if (! einst_ptr)
	{
        // error already output
	    return FALSE;
	}

	m_einst_id = einst_ptr->get_evt_inst_ID ();
	set_timer_inst_ref_str ();
    }


    return TRUE;
}


I_var*
I_timer_inst_ref_var::clone_to_transient () const

{
    return new I_timer_inst_ref_var (*this);
}


I_var*
I_timer_inst_ref_var::clone_to_persistent () const

{
    return new (GS_gen_sim_db_ptr, I_timer_inst_ref_var::get_mc_dbms_typespec ())
	I_timer_inst_ref_var (*this);
}


I_timer_inst_ref_var::~I_timer_inst_ref_var ()

{
    LOG_TRACE (L_D_DATA, L_FUNCTION_BEGIN, (L_log_string,
	"Begin  I_timer_inst_ref_var::~I_timer_inst_ref_var ()."));

    operator delete( this, ""); // Remove from InstanceTracker

    LOG_TRACE (L_D_DATA, L_FUNCTION_END, (L_log_string,
	"End  I_timer_inst_ref_var::~I_timer_inst_ref_var ()."));
}


I_SM_Evt_Inst*
I_timer_inst_ref_var::get_einst_ptr ()

{
    if (m_einst_id == Id::Default)
    {
	return 0;
    }


    I_SM_Evt_Inst* einst_ptr
	= I_SM_Evt_Inst::find_SM_Evt_Inst_by_evt_inst_ID
	    (GS_gen_sim_db_ptr, m_einst_id);
    if (einst_ptr)
    {
	return einst_ptr;
    }


    Description err_msg	("Variable of type inst_ref<Timer> has no event. Did you delete the timer? Did the timer expire?");
    GS_ui::inform (UI_INFORM__ERROR, err_msg);
    m_einst_id = Id::Default;
    set_timer_inst_ref_str ();
    return 0;
}


void
I_timer_inst_ref_var::set_einst_id (const Id& p_einst_id)

{
    m_einst_id = Id::Default;
    set_timer_inst_ref_str ();


    if (p_einst_id != Id::Default)
    {
	I_SM_Evt_Inst* einst_ptr
	    = I_SM_Evt_Inst::find_SM_Evt_Inst_by_evt_inst_ID
		(GS_gen_sim_db_ptr, p_einst_id);
	if (! einst_ptr)
	{
	    LOG_ERROR ((L_log_string,
		"I_timer_inst_ref_var::set_einst_id ():  einst_ptr == 0."));
	    return;
	}

	m_einst_id = p_einst_id;
	set_timer_inst_ref_str ();
    }
}


void
I_timer_inst_ref_var::set_timer_inst_ref_str ()

{
    if (get_is_initialized ())
    {
	I_SM_Evt_Inst* einst_ptr = get_einst_ptr ();
	if ((einst_ptr)
	    &&
	    (einst_ptr->get_SM_Evt_R2022_ptr ()))
	{
	    m_timer_inst_ref_str
		= einst_ptr->get_SM_Evt_R2022_ptr ()->get_label ();
	    m_timer_inst_ref_str += "_";
	    char buffer [32];
	    sprintf (buffer, "%06x",
		einst_ptr->get_evt_inst_ID ().get_entire_value ());
	    m_timer_inst_ref_str += buffer;
	    m_timer_inst_ref_str += " - expiration_timestamp = ";
	    m_timer_inst_ref_str += einst_ptr->
		get_expiration_time ().get_var_ptr ()->get_value_str ();
	}
	else
	{
	    //  Repair error condition.
	    //
	    LOG_ERROR ((L_log_string,
		"I_timer_inst_ref_var::set_timer_inst_ref_str ():  einst_ptr == 0."));
	    m_einst_id = Id::Default;
	    m_timer_inst_ref_str = "un-initialized";
	}
    }
    else
    {
	m_timer_inst_ref_str = "un-initialized";
    }
}









//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////


I_frag_ref_var::I_frag_ref_var (bool isRestoring)

{
	if (!isRestoring) {
	    //  New the string for the fragment attribute in the correct part of
	    //    memory - either in the transient database or in the persistent
	    //    database.
	    //
	    String* attr_name_str_ptr
		= new (mc_dbms_segment::of (this), String_type) String ("body");
	    m_attr_name_str_coll.insert_last (attr_name_str_ptr);
	
	
	    //  New the variable for the fragment attribute in the correct part of
	    //    memory - either in the transient database or in the persistent
	    //    database.
	    //
	    I_var* attr_var_ptr = 0;
	    if (mc_dbms_segment::of (this) == mc_dbms_segment::get_transient_segment ())
	    {
		attr_var_ptr
		    = create_in_transient (STRING_DATATYPE, USER_DEFINED_USERDATATYPE);
	    }
	    else
	    {
		I_var* transient_attr_var_ptr
		    = create_in_transient (STRING_DATATYPE, USER_DEFINED_USERDATATYPE);
		attr_var_ptr = transient_attr_var_ptr->clone_to_persistent ();
		delete transient_attr_var_ptr;
	    }
	    attr_var_ptr->increment_reference_count ();
	    m_attr_var_coll.insert_last (attr_var_ptr);
	}
}


I_frag_ref_var::I_frag_ref_var (const I_frag_ref_var& p_frag_ref_var)

{
    reassign (&p_frag_ref_var);
}


I_frag_ref_var::~I_frag_ref_var ()

{
    clear_attrs ();
    operator delete( this, ""); // Remove from InstanceTracker
}


t_boolean
I_frag_ref_var::operator== (const I_var& p_var) const

{
    return (((I_var&) p_var).get_frag_ref_var_ptr ()) ? TRUE : FALSE;
}


t_boolean
I_frag_ref_var::replace_attr_var_ptr
    (const Description& p_attr_name_str, const I_var* p_var_ptr)
{
    t_int found_ii = -1;
    t_int ii = -1;

    String* attr_name_str_ptr;
    FOR_ALL_ELEMENTS
	(attr_name_str_ptr,
	String,
	&(m_attr_name_str_coll),
	attr_name_str_cursor)
    {
	ii++;
	if (p_attr_name_str == (*attr_name_str_ptr))
	{
	    found_ii = ii;
	}
    }

    if (found_ii == -1)
    {
	Description err_msg("Attribute '");
	err_msg += p_attr_name_str.char_ptr();
	err_msg += "' is not a valid attribute.";
	GS_ui::inform (UI_INFORM__ERROR, err_msg);
	return FALSE;
    }

    if (m_attr_var_coll.cardinality () < (found_ii + 1))
    {
	Description err_msg("Internal Error finding Attribute '");
	err_msg += p_attr_name_str.char_ptr();
	err_msg += "' value.";
	GS_ui::inform (UI_INFORM__ERROR, err_msg);
	LOG_ERROR ((L_log_string,
	    "I_frag_ref_var::replace_attr_var_ptr () - Attribute name found but corresponding variable does not exist."));
	return FALSE;
    }


    I_var* to_be_replaced_var_ptr = m_attr_var_coll.retrieve (found_ii);
    if ((to_be_replaced_var_ptr)
	&&
	(to_be_replaced_var_ptr->decrement_reference_count () < 1))
    {
	delete to_be_replaced_var_ptr;
    }


    if (p_var_ptr)
    {
	((I_var*) p_var_ptr)->increment_reference_count ();
    }
    m_attr_var_coll.replace_at (((I_var*) p_var_ptr), found_ii);


    return TRUE;
}


t_boolean
I_frag_ref_var::reassign (const I_var* p_var_ptr)

{
    t_boolean rv = FALSE;
    if (((I_var*) p_var_ptr)->get_frag_ref_var_ptr ())
    {
	clear_attrs ();

	String* attr_name_str_ptr;
	FOR_ALL_ELEMENTS
	    (attr_name_str_ptr,
	    String,
	    &(((I_var*) p_var_ptr)->get_frag_ref_var_ptr ()->
		m_attr_name_str_coll),
	    attr_name_str_cursor)
	{
	    //  New the string for the fragment attribute in the correct
	    //    part of memory - either in the transient database or
	    //    in the persistent database.
	    //
	    String* new_attr_name_str_ptr = 0;
	    new_attr_name_str_ptr = new (mc_dbms_segment::of (this), String_type)
		String (*attr_name_str_ptr);
	    m_attr_name_str_coll.insert_last (new_attr_name_str_ptr);
	}

	I_var* attr_var_ptr;
	FOR_ALL_ELEMENTS
	    (attr_var_ptr,
	    I_var,
	    &(((I_var*) p_var_ptr)->get_frag_ref_var_ptr ()->
		m_attr_var_coll),
	    attr_var_cursor)
	{
	    //  New the variable for the fragment attribute in the correct
	    //    part of memory - either in the transient database or
	    //    in the persistent database.
	    //
	    I_var* new_attr_var_ptr = 0;
	    if (mc_dbms_segment::of (this) == mc_dbms_segment::get_transient_segment ())
	    {
		new_attr_var_ptr = attr_var_ptr->clone_to_transient ();
	    }
	    else
	    {
		new_attr_var_ptr = attr_var_ptr->clone_to_persistent ();
	    }
	    new_attr_var_ptr->increment_reference_count ();
	    m_attr_var_coll.insert_last (new_attr_var_ptr);
	}

	rv = TRUE;
    }
    else
    {
	GS_ui::inform (UI_INFORM__ERROR,
	    GS_string("Internal Error reassigning frag var."));
	LOG_ERROR ((L_log_string,
	    "I_frag_ref_var::reassign () - reassigned when NOT frag var."));
    }
    return rv;
}


I_var*
I_frag_ref_var::clone_to_transient () const

{
    return new I_frag_ref_var (*this);
}


I_var*
I_frag_ref_var::clone_to_persistent () const

{
    return new (GS_gen_sim_db_ptr, I_frag_ref_var::get_mc_dbms_typespec ())
	I_frag_ref_var (*this);
}


void
I_frag_ref_var::append_to_body (const Description& p_str)

{
    I_var* body_attr_var_ptr = get_attr_var_ptr (lc_body_string);
    if (body_attr_var_ptr)
    {
	I_string_var* body_attr_string_var_ptr
	    = body_attr_var_ptr->get_string_var_ptr ();
	if (body_attr_string_var_ptr)
	{
	    body_attr_string_var_ptr->append_to_value (p_str);
	}
	else
	{
	    GS_ui::inform (UI_INFORM__ERROR,
		GS_string("Internal Error appending to 'body' Attribute of fragment."));
	    LOG_ERROR ((L_log_string,
		"I_frag_ref_var::append_to_body () - body attr found but is not string variable."));
	}
    }
    else
    {
	GS_ui::inform (UI_INFORM__ERROR,
	    GS_string("Internal Error appending to 'body' Attribute of fragment."));
	LOG_ERROR ((L_log_string,
	    "I_frag_ref_var::append_to_body () - body attr not found."));
    }
}


void
I_frag_ref_var::add_attr
    (const Description& p_attr_name_str, I_var* p_var_ptr)

{
    if (p_var_ptr)
    {
	if (p_attr_name_str.length () > 5)
	{
	    if (p_attr_name_str.compare_n ("attr_", 5))
	    {
		//  New the string for the fragment attribute in the correct
		//    part of memory - either in the transient database or
		//    in the persistent database.
		//
        String* attr_name_str_ptr = 0;
    	char attr_name_string[256];
	    vcharExport (vcharScribeASCIIExport(p_attr_name_str.char_ptr()), attr_name_string);

		attr_name_str_ptr = new (mc_dbms_segment::of (this), String_type)
		    String (&attr_name_string[5]);
		m_attr_name_str_coll.insert_last (attr_name_str_ptr);

#ifdef NEEDS_TESTING
9/13/95 - I noticed that the variables are being cloned here.  They
really do not need to be since they are just about to be taken off
the stack and thrown out anyway.  Just use them directly.
		//  New the variable for the fragment attribute in the correct
		//    part of memory - either in the transient database or
		//    in the persistent database.
		//
		I_var* attr_var_ptr = 0;
		if (mc_dbms_segment::of (this)
		    == mc_dbms_segment::get_transient_segment ())
		{
		    attr_var_ptr = p_var_ptr->clone_to_transient ();
		}
		else
		{
		    attr_var_ptr = p_var_ptr->clone_to_persistent ();
		}
		attr_var_ptr->increment_reference_count ();
		m_attr_var_coll.insert_last (attr_var_ptr);
#endif
		p_var_ptr->increment_reference_count ();
		m_attr_var_coll.insert_last (p_var_ptr);
	    }
	}
    }
}


t_boolean
I_frag_ref_var::is_valid_attr_name (const Description& p_attr_name_str) const

{
    String* attr_name_str_ptr;
    FOR_ALL_ELEMENTS
	(attr_name_str_ptr,
	String,
	&(m_attr_name_str_coll),
	attr_name_str_cursor)
    {
	if (p_attr_name_str == (*attr_name_str_ptr))
	{
	    return TRUE;
	}
    }


    Description err_msg("Attribute '");
	err_msg += p_attr_name_str.char_ptr();
	err_msg += "' is not a valid attribute.";
	GS_ui::inform (UI_INFORM__ERROR, err_msg);
    return FALSE;
}


I_var*
I_frag_ref_var::get_attr_var_ptr (const Description& p_attr_name_str)

{
    t_int found_ii = -1;
    t_int ii = -1;

    String* attr_name_str_ptr;
    FOR_ALL_ELEMENTS
	(attr_name_str_ptr,
	String,
	&(m_attr_name_str_coll),
	attr_name_str_cursor)
    {
	ii++;
	if (p_attr_name_str == (*attr_name_str_ptr))
	{
	    found_ii = ii;
	}
    }

    if (found_ii == -1)
    {
	Description err_msg("Attribute '");
	err_msg += p_attr_name_str.char_ptr();
	err_msg += "' is not a valid attribute.";
	GS_ui::inform (UI_INFORM__ERROR, err_msg);
	return 0;
    }

    if (m_attr_var_coll.cardinality () < (found_ii + 1))
    {
	Description err_msg("Internal Error finding Attribute '");
	err_msg += p_attr_name_str.char_ptr();
	err_msg += "' value.";
	GS_ui::inform (UI_INFORM__ERROR, err_msg);
	LOG_ERROR ((L_log_string,
	    "I_frag_ref_var::get_attr_var_ptr () - Attribute name found but corresponding variable does not exist."));
	return 0;
    }

    return m_attr_var_coll.retrieve (found_ii);
}


void
I_frag_ref_var::clear_attrs ( t_boolean p_keep_body_var )

{
    String* attr_name_str_ptr;
    while (attr_name_str_ptr = m_attr_name_str_coll.pick ())
    {
	m_attr_name_str_coll.remove (attr_name_str_ptr);
	delete attr_name_str_ptr;
    }

    I_var* attr_var_ptr;
    while (attr_var_ptr = m_attr_var_coll.pick ())
    {
	m_attr_var_coll.remove (attr_var_ptr);
	if ((attr_var_ptr) && (attr_var_ptr->decrement_reference_count () < 1))
	{
	    delete attr_var_ptr;
	}
    }


    if (p_keep_body_var)
    {
        String* attr_name_str_ptr
	    = new (mc_dbms_segment::of (this), String_type) String("body");
        m_attr_name_str_coll.insert_last (attr_name_str_ptr);


        //  New the variable for the fragment attribute in the correct part of
        //    memory - either in the transient database or in the persistent
        //    database.
        //
        I_var* attr_var_ptr = 0;
        if (mc_dbms_segment::of (this) == mc_dbms_segment::get_transient_segment ())
        {
	    attr_var_ptr = create_in_transient
		(STRING_DATATYPE, USER_DEFINED_USERDATATYPE);
        }
        else
        {
	    I_var* transient_attr_var_ptr = create_in_transient
		(STRING_DATATYPE, USER_DEFINED_USERDATATYPE);
	    attr_var_ptr = transient_attr_var_ptr->clone_to_persistent ();
	    delete transient_attr_var_ptr;
        }
        attr_var_ptr->increment_reference_count ();
        m_attr_var_coll.insert_last (attr_var_ptr);
    }
}


const Description&
I_frag_ref_var::get_value_str () const

{
    LOG_TRACE (L_D_DATA, L_FUNCTION_BEGIN, (L_log_string,
	"I_frag_ref_var::get_value_str ()."));


    //  Check to see if this fragment is embedded in itself.  If it is
    //    just return right away without decending into the fragment
    //    attributes (or you will be in an infinite loop!).
    //
    if (m_fragment_str == "{Fragment Embedded in self}")
    {
	return m_fragment_str;
    }


    //  Mark this fragment as being processed already so that we can
    //    detect if the fragment is embedded in itself.
    //
    ((I_frag_ref_var*) this)->m_fragment_str = "{Fragment Embedded in self}";


    //  Use a local fragment string so that the fragment can stay marked
    //    as being processed already.
    //
    Description l_fragment_str ("{");


    //  Loop through each attribute and print the attribute name, data
    //    type, and value.
    //
    t_int ii = -1;
    String* attr_name_str_ptr;
    FOR_ALL_ELEMENTS
	(attr_name_str_ptr,
	String,
	&(m_attr_name_str_coll),
	attr_name_str_cursor)
    {
	ii++;
	Description attr_str;
	if (ii > 0)
	{
	    attr_str += ", ";
	}
	attr_str += *attr_name_str_ptr;

	if (m_attr_var_coll.cardinality () <= ii)
	{
	    LOG_ERROR ((L_log_string,
		"I_frag_ref_var::get_value_str () - Attribute name found but corresponding variable does not exist."));
	}
	else
	{
	    I_var* attr_var_ptr = m_attr_var_coll.retrieve (ii);
	    attr_str += " (";
	    attr_str += attr_var_ptr->get_data_type_str ().char_ptr ();
	    attr_str += ") = ";
	    attr_str += attr_var_ptr->get_value_str ();
	}

	l_fragment_str += attr_str;
    }

    l_fragment_str += "}";
    ((I_frag_ref_var*) this)->m_fragment_str = l_fragment_str;
    return m_fragment_str;
}

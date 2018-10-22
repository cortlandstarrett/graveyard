/*========================================================================
 *
 * File:      $RCSfile: gs_selct.cc,v $
 * Version:   $Revision: 1.10 $
 * Modified:  $Date: 2013/01/10 23:42:29 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#include <mc_dbms/mc_dbms.hh>

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include <gs_selct.hh>
#include <gs_stack.hh>
#include <gs_expr.hh>
#include <gs_ui.hh>
#include <u_string.hh>
#include <gs_sizes.hh>
#include <gs_ui.hh>
#include <gs_obj.hh>

#include <i_var.hh>
#include <i_obj.hh>
#include <i_attr.hh>
#include <i_rel.hh>
#include <i_oinst.hh>
#include <i_ainst.hh>
#include <i_rop.hh>
#include <i_c_rop.hh>
#include <i_roip.hh>
#include <i_relate.hh>                               
#include <i_clock.hh>                               


#include <u_trace.hh>
#include <u_report.hh>
#include <u_error.hh>
#include <u_cursor.hh>
#include <u_env.hh>

extern mc_dbms_database * GS_gen_sim_db_ptr;




void
GS_select::print_select_stmt_error ()

{
    GS_string error_str;
    error_str  = "'.SELECT' statement on line not specified correctly.\n";
    error_str += "    Correct syntax is:\n";
    error_str += "        .SELECT ONE <inst-ref> RELATED BY <instance-chain>\n";
    error_str += "    OR\n";
    error_str += "        .SELECT ANY <inst-ref> RELATED BY <instance-chain>\n";
    error_str += "    OR\n";
    error_str += "        .SELECT MANY <inst-set-ref> RELATED BY <instance-chain>\n";
    error_str += "    OR\n";
    error_str += "        .SELECT ANY <inst-ref> FROM INSTANCES OF <object>\n";
    error_str += "    OR\n";
    error_str += "        .SELECT MANY <inst-set-ref> FROM INSTANCES OF <object>\n";
    GS_ui::inform (UI_INFORM__ERROR, error_str);
}




t_boolean
GS_select::interpret_stmt__select (const Description& p_stmt_str)

{
//	char *stmt_str_ASCII = 
//		Description::createAsciiFromVchar(p_stmt_str.char_ptr());
	Description stmt_str(p_stmt_str);
//	Description::freeAsciiFromVchar(stmt_str_ASCII);
    t_uint stmt_cursor = 0;

    //  Remove the ';' off end of statement if one exists.
    //
    for (t_uint i = stmt_str.length () - 1;
	((i >= 0) && (vcharIsWhiteSpace (stmt_str.char_at(i))));
	i--)
		/* do nothing*/ ;

    if (stmt_str.char_at(i) == ';')
    {
	stmt_str.truncate(i);
    }


    Description select_str;
    stmt_str.parse_token (stmt_cursor, select_str);
    select_str.convert_to_upper_case ();
    if ((select_str != select_string) && (select_str != dot_select))
    {
        LOG_ERROR ((L_log_string,
	    "GS_select::interpret_stmt__select () called for a statement which is NOT a 'SELECT' statement.  Ignoring line and going on."));
        return FALSE;
    }
    
    
    Description cardinality_str;
    stmt_str.parse_token (stmt_cursor, cardinality_str);
    cardinality_str.convert_to_upper_case ();
    if (! ((cardinality_str == one_string)
	|| (cardinality_str == any_string)
	|| (cardinality_str == many_string)))
    {
        GS_ui::inform (UI_INFORM__ERROR,
	    GS_string("SELECT statement requires specification of ONE, ANY, or MANY."));
        return FALSE;
    }


    Description inst_var_str;
    int beginning_of_inst_var_cursor = stmt_cursor;
    Description from_inst_var_str;
    stmt_str.parse_to_keyword ("FROM", stmt_cursor, from_inst_var_str);
    if (((stmt_cursor + 4) < stmt_str.length ())
	&& (   (stmt_str.char_at(stmt_cursor    ) == 'F')
	    || (stmt_str.char_at(stmt_cursor    ) == 'f'))
	&& (   (stmt_str.char_at(stmt_cursor + 1) == 'R')
	    || (stmt_str.char_at(stmt_cursor + 1) == 'r'))
	&& (   (stmt_str.char_at(stmt_cursor + 2) == 'O')
	    || (stmt_str.char_at(stmt_cursor + 2) == 'o'))
	&& (   (stmt_str.char_at(stmt_cursor + 3) == 'M')
	    || (stmt_str.char_at(stmt_cursor + 3) == 'm')))
    {
	inst_var_str = from_inst_var_str;
    }
    else
    {
	stmt_cursor = beginning_of_inst_var_cursor;
	Description related_inst_var_str;
    stmt_str.parse_to_keyword ("RELATED", stmt_cursor, related_inst_var_str);
	if (((stmt_cursor + 7) < stmt_str.length ())
	    && (   (stmt_str.char_at(stmt_cursor    ) == 'R')
		|| (stmt_str.char_at(stmt_cursor    ) == 'r'))
	    && (   (stmt_str.char_at(stmt_cursor + 1) == 'E')
		|| (stmt_str.char_at(stmt_cursor + 1) == 'e'))
	    && (   (stmt_str.char_at(stmt_cursor + 2) == 'L')
		|| (stmt_str.char_at(stmt_cursor + 2) == 'l'))
	    && (   (stmt_str.char_at(stmt_cursor + 3) == 'A')
		|| (stmt_str.char_at(stmt_cursor + 3) == 'a'))
	    && (   (stmt_str.char_at(stmt_cursor + 4) == 'T')
		|| (stmt_str.char_at(stmt_cursor + 4) == 't'))
	    && (   (stmt_str.char_at(stmt_cursor + 5) == 'E')
		|| (stmt_str.char_at(stmt_cursor + 5) == 'e'))
	    && (   (stmt_str.char_at(stmt_cursor + 6) == 'D')
		|| (stmt_str.char_at(stmt_cursor + 6) == 'd')))
	{
	    inst_var_str = related_inst_var_str;
	}
	else
	{
	    GS_ui::inform (UI_INFORM__ERROR,
		GS_string("SELECT statement requires specification of either RELATED BY or FROM INSTANCES OF."));
	    return FALSE;
	}
    }


    Description lower_case_inst_var_str (inst_var_str);
    lower_case_inst_var_str.convert_to_lower_case ();
    if (lower_case_inst_var_str == self_string)
    {
	    Description err_msg ("Instance '");
		err_msg += inst_var_str;
	    err_msg += "' NOT allowed to be used as result variable in SELECT statement.";
		GS_ui::inform (UI_INFORM__ERROR, err_msg);
	return FALSE;
    }
    Description inst_set_var_str (inst_var_str);


    Description related_or_from_str;
    stmt_str.parse_token (stmt_cursor, related_or_from_str);
    related_or_from_str.convert_to_upper_case ();
    if (related_or_from_str == related_string)
    {
	Description by_str;
    stmt_str.parse_token (stmt_cursor, by_str);
	by_str.convert_to_upper_case ();
	if (by_str != by_string)
	{
	    GS_ui::inform (UI_INFORM__ERROR,
		GS_string("SELECT statement requires specification of either RELATED BY or FROM INSTANCES OF."));
	    return FALSE;
	}
    }
    else if (related_or_from_str == from_string)
    {
	Description instances_str;
    stmt_str.parse_token (stmt_cursor, instances_str);
	instances_str.convert_to_upper_case ();
	if (instances_str != instances_string)
	{
	    GS_ui::inform (UI_INFORM__ERROR,
		GS_string("SELECT statement requires specification of either RELATED BY or FROM INSTANCES OF."));
	    return FALSE;
	}
	Description of_str;
    stmt_str.parse_token (stmt_cursor, of_str);
	of_str.convert_to_upper_case ();
	if (of_str != of_string)
	{
	    GS_ui::inform (UI_INFORM__ERROR,
		GS_string("SELECT statement requires specification of either RELATED BY or FROM INSTANCES OF."));
	    return FALSE;
	}
    }
    else
    {
        GS_ui::inform (UI_INFORM__ERROR,
	    GS_string("SELECT statement requires specification of either RELATED BY or FROM INSTANCES OF."));
        return FALSE;
    }


    Description dummy;
    if ((cardinality_str == one_string) && (related_or_from_str == related_string))
    {
	//  Parsed statement:
	//    SELECT ONE <inst-ref> RELATED BY <inst-chain> WHERE <cond>
	//
	Description inst_chain_str;
    stmt_str.parse_to_keyword ("WHERE", stmt_cursor, inst_chain_str);
	stmt_str.parse_token (stmt_cursor, dummy);
	Description condition_str;
    stmt_str.parse_to_end (stmt_cursor, condition_str);
	return (GS_select::select_one_any__related_by (cardinality_str,
	    inst_var_str, inst_chain_str, condition_str)) ? TRUE : FALSE;
    }
    else if ((cardinality_str == any_string) && (related_or_from_str == related_string))
    {
	//  Parsed statement:
	//    SELECT ANY <inst-ref> RELATED BY <inst-chain> WHERE <cond>
	//
	Description inst_chain_str;
    stmt_str.parse_to_keyword ("WHERE", stmt_cursor, inst_chain_str);
	stmt_str.parse_token (stmt_cursor, dummy);
	Description condition_str;
    stmt_str.parse_to_end (stmt_cursor, condition_str);
	return (GS_select::select_one_any__related_by (cardinality_str,
	    inst_var_str, inst_chain_str, condition_str)) ? TRUE : FALSE;
    }
    else if ((cardinality_str == many_string) && (related_or_from_str == related_string))
    {
	//  Parsed statement:
	//    SELECT MANY <inst-set-ref> RELATED BY <inst-chain> WHERE <cond>
	//
	Description inst_chain_str;
    stmt_str.parse_to_keyword ("WHERE", stmt_cursor, inst_chain_str);
	stmt_str.parse_token (stmt_cursor, dummy);
	Description condition_str;
    stmt_str.parse_to_end (stmt_cursor, condition_str);
	return (GS_select::select_many__related_by
	    (inst_set_var_str, inst_chain_str, condition_str)) ? TRUE : FALSE;
    }
    else if ((cardinality_str == any_string) && (related_or_from_str == from_string))
    {
	//  Parsed statement:
	//    SELECT ANY <inst-ref> FROM INSTANCES OF <object> WHERE <cond>
	//
	Description object_str;
    stmt_str.parse_to_keyword ("WHERE", stmt_cursor, object_str);
	stmt_str.parse_token (stmt_cursor, dummy);
	Description condition_str;
    stmt_str.parse_to_end (stmt_cursor, condition_str);
	return (GS_select::select_any__from_instances_of
	    (inst_set_var_str, object_str, condition_str)) ? TRUE : FALSE;
    }
    else if ((cardinality_str == many_string) && (related_or_from_str == from_string))
    {
	//  Parsed statement:
	//    SELECT MANY <inst-set-ref> FROM INSTANCES OF <object> WHERE <cond>
	//
	Description object_str;
    stmt_str.parse_to_keyword ("WHERE", stmt_cursor, object_str);
	stmt_str.parse_token (stmt_cursor, dummy);
	Description condition_str;
    stmt_str.parse_to_end (stmt_cursor, condition_str);
	return (GS_select::select_many__from_instances_of
	    (inst_set_var_str, object_str, condition_str)) ? TRUE : FALSE;
    }


    print_select_stmt_error ();
    return FALSE;
}




t_boolean
GS_select::select_any__from_instances_of
    (const Description& p_inst_var_name_str,
    const Description& p_obj_key_letter_str, const Description& p_condition_str)

{
    I_object_inst_ref_set_var* inst_set_var_ptr
	= GS_select::create__from_instances_of__no_push
	    (p_obj_key_letter_str, p_condition_str, TRUE);


    if (! inst_set_var_ptr)
    {
	//  Assume error message already printed.
	//
	return FALSE;
    }


    I_object_inst_ref_var* result_inst_var_ptr = 0;
    if (inst_set_var_ptr->cardinality () >= 1)
    {
	result_inst_var_ptr = new I_object_inst_ref_var
	    (inst_set_var_ptr->m_obj_ptr,
	    inst_set_var_ptr->m_oinst_coll.pick ());
    }
    else
    {
	result_inst_var_ptr = new I_object_inst_ref_var
	    (inst_set_var_ptr->m_obj_ptr, 0);
    }
    delete inst_set_var_ptr;


    GS_var_si lvalue_var_si;
    lvalue_var_si.replace_var (result_inst_var_ptr);
    GS_stack::place_result_in_stack_var (p_inst_var_name_str, &lvalue_var_si);


    return TRUE;


#ifdef COMMENTED_OUT
    I_object_inst_ref_var* result_inst_var_ptr = 0;
    I_var* result_var_ptr = GS_stack::find_var_ptr (p_inst_var_name_str);
    if (result_var_ptr)
    {
	result_inst_var_ptr
	    = GS_stack::find_object_inst_ref_var_ptr (p_inst_var_name_str);
	if (result_inst_var_ptr)
	{
	    if (result_inst_var_ptr->get_key_letters_str ()
		!= inst_set_var_ptr->get_key_letters_str ())
	    {
		GS_ui::inform (UI_INFORM__ERROR, GS_string
		    ("Instance Variable '")
		    + p_inst_var_name_str
		    + "' is Defined but refers to an instance of a different object than this SELECT statement.");
	    }
	    else
	    {
		if (inst_set_var_ptr->cardinality () >= 1)
		{
		    result_inst_var_ptr->m_oinst_ptr
			= inst_set_var_ptr->m_oinst_coll.pick ();
		}
		else
		{
		    result_inst_var_ptr->m_oinst_ptr = 0;
		}
	    }
	}
	else
	{
	    GS_ui::inform (UI_INFORM__ERROR, GS_string ("Variable '")
		+ p_inst_var_name_str
		+ "' is Defined but is NOT of type INST_REF.");
	}
    }
    else
    {
	if (inst_set_var_ptr->cardinality () >= 1)
	{
	    result_inst_var_ptr = new I_object_inst_ref_var
		(inst_set_var_ptr->m_obj_ptr,
		inst_set_var_ptr->m_oinst_coll.pick ());
	}
	else
	{
	    result_inst_var_ptr = new I_object_inst_ref_var
		(inst_set_var_ptr->m_obj_ptr, 0);
	}
	GS_stack::push_var (result_inst_var_ptr, p_inst_var_name_str);
    }


    delete inst_set_var_ptr;
#endif
}





t_boolean
GS_select::select_one_any__related_by
    (const Description& p_cardinality_str, const Description& p_inst_var_name_str,
    const Description& p_inst_chain_str, const Description& p_condition_str)

{
    I_object_inst_ref_set_var* inst_set_var_ptr;
    if (p_cardinality_str == one_string)
    {
	inst_set_var_ptr = GS_select::create__related_by__no_push
	    (p_inst_chain_str, p_condition_str, FALSE);
    }
    else
    {
	inst_set_var_ptr = GS_select::create__related_by__no_push
	    (p_inst_chain_str, p_condition_str, TRUE);
    }


    if (! inst_set_var_ptr)
    {
	//  Assume error message already printed.
	//
	return FALSE;
    }


    if ((p_cardinality_str == one_string) && (inst_set_var_ptr->cardinality () > 1))
    {
	    Description err_msg ("Instance Chain '");
		err_msg += p_inst_chain_str;
	    err_msg += "' results in more than one instance.";
	GS_ui::inform (UI_INFORM__ERROR, err_msg);
	return FALSE;
    }


    I_object_inst_ref_var* result_inst_var_ptr = 0;
    if (inst_set_var_ptr->cardinality () >= 1)
    {
	result_inst_var_ptr = new I_object_inst_ref_var
	    (inst_set_var_ptr->m_obj_ptr,
	    inst_set_var_ptr->m_oinst_coll.pick ());
    }
    else
    {
	result_inst_var_ptr = new I_object_inst_ref_var
	    (inst_set_var_ptr->m_obj_ptr, 0);
    }
    delete inst_set_var_ptr;


    GS_var_si lvalue_var_si;
    lvalue_var_si.replace_var (result_inst_var_ptr);
    GS_stack::place_result_in_stack_var (p_inst_var_name_str, &lvalue_var_si);


    return TRUE;


#ifdef COMMENTED_OUT
    I_object_inst_ref_var* result_inst_var_ptr = 0;
    I_var* result_var_ptr = GS_stack::find_var_ptr (p_inst_var_name_str);
    if (result_var_ptr)
    {
	result_inst_var_ptr
	    = GS_stack::find_object_inst_ref_var_ptr (p_inst_var_name_str);
	if (result_inst_var_ptr)
	{
	    if (result_inst_var_ptr->get_key_letters_str ()
		!= inst_set_var_ptr->get_key_letters_str ())
	    {
		GS_ui::inform (UI_INFORM__ERROR, GS_string
		    ("Instance Variable '")
		    + p_inst_var_name_str
		    + "' is Defined but refers to an instance of a different object than this SELECT statement.");
	    }
	    else
	    {
		if (inst_set_var_ptr->cardinality () >= 1)
		{
		    result_inst_var_ptr->m_oinst_ptr
			= inst_set_var_ptr->m_oinst_coll.pick ();
		}
		else
		{
		    result_inst_var_ptr->m_oinst_ptr = 0;
		}
	    }
	}
	else
	{
	    GS_ui::inform (UI_INFORM__ERROR, GS_string ("Variable '")
		+ p_inst_var_name_str
		+ "' is Defined but is NOT of type INST_REF.");
	}
    }
    else
    {
	if (inst_set_var_ptr->cardinality () >= 1)
	{
	    result_inst_var_ptr = new I_object_inst_ref_var
		(inst_set_var_ptr->m_obj_ptr,
		inst_set_var_ptr->m_oinst_coll.pick ());
	}
	else
	{
	    result_inst_var_ptr = new I_object_inst_ref_var
		(inst_set_var_ptr->m_obj_ptr, 0);
	}
	GS_stack::push_var (result_inst_var_ptr, p_inst_var_name_str);
    }


    delete inst_set_var_ptr;
#endif
}





t_boolean
GS_select::select_many__from_instances_of
    (const Description& p_inst_set_var_name_str,
    const Description& p_obj_key_letter_str, const Description& p_condition_str)

{
    I_object_inst_ref_set_var* inst_set_var_ptr
	= create__from_instances_of__no_push
	    (p_obj_key_letter_str, p_condition_str, FALSE);


    if (! inst_set_var_ptr)
    {
	//  Assume error message already printed.
	//
	return FALSE;
    }


    GS_var_si lvalue_var_si;
    lvalue_var_si.replace_var (inst_set_var_ptr);
    GS_stack::place_result_in_stack_var
	(p_inst_set_var_name_str, &lvalue_var_si);


    return TRUE;


#ifdef COMMENTED_OUT
    I_object_inst_ref_set_var* result_inst_set_var_ptr = 0;
    I_var* result_var_ptr = GS_stack::find_var_ptr (p_inst_set_var_name_str);
    if (result_var_ptr)
    {
	result_inst_set_var_ptr
	    = GS_stack::find_object_inst_ref_set_var_ptr (p_inst_set_var_name_str);
	if (result_inst_set_var_ptr)
	{
	    if (result_inst_set_var_ptr->get_key_letters_str ()
		!= inst_set_var_ptr->get_key_letters_str ())
	    {
		GS_ui::inform (UI_INFORM__ERROR, GS_string
		    ("Instance Set Variable '")
		    + p_inst_set_var_name_str
		    + "' is Defined but refers to instance(s) of a different object than this SELECT statement.");
	    }
	    else
	    {
		result_inst_set_var_ptr->m_oinst_coll
		    = inst_set_var_ptr->m_oinst_coll;
		result_inst_set_var_ptr->m_cursor
		    = (result_inst_set_var_ptr->cardinality () >= 1) ? 1 : 0;
		delete inst_set_var_ptr;
		inst_set_var_ptr = result_inst_set_var_ptr;
	    }
	}
	else
	{
	    GS_ui::inform (UI_INFORM__ERROR, GS_string ("Variable '")
		+ p_inst_set_var_name_str
		+ "' is Defined but is NOT of type INST_SET_REF.");
	}
    }
    else
    {
	GS_stack::push_var (inst_set_var_ptr, p_inst_set_var_name_str);
    }


    return inst_set_var_ptr;
#endif
}





t_boolean
GS_select::select_many__related_by (const Description& p_inst_set_var_name_str,
    const Description& p_inst_chain_str, const Description& p_condition_str)

{
    I_object_inst_ref_set_var* inst_set_var_ptr
	= GS_select::create__related_by__no_push
	    (p_inst_chain_str, p_condition_str, FALSE);


    if (! inst_set_var_ptr)
    {
	//  Assume error message already printed.
	//
	return FALSE;
    }


    GS_var_si lvalue_var_si;
    lvalue_var_si.replace_var (inst_set_var_ptr);
    GS_stack::place_result_in_stack_var
	(p_inst_set_var_name_str, &lvalue_var_si);


    return TRUE;


#ifdef COMMENTED_OUT
    I_object_inst_ref_set_var* result_inst_set_var_ptr = 0;
    I_var* result_var_ptr = GS_stack::find_var_ptr (p_inst_set_var_name_str);
    if (result_var_ptr)
    {
	result_inst_set_var_ptr
	    = GS_stack::find_object_inst_ref_set_var_ptr (p_inst_set_var_name_str);
	if (result_inst_set_var_ptr)
	{
	    if (result_inst_set_var_ptr->get_key_letters_str ()
		!= inst_set_var_ptr->get_key_letters_str ())
	    {
		GS_ui::inform (UI_INFORM__ERROR, GS_string
		    ("Instance Set Variable '")
		    + p_inst_set_var_name_str
		    + "' is Defined but refers to instance(s) of a different object than this SELECT statement.");
	    }
	    else
	    {
		result_inst_set_var_ptr->m_oinst_coll
		    = inst_set_var_ptr->m_oinst_coll;
		result_inst_set_var_ptr->m_cursor
		    = (result_inst_set_var_ptr->cardinality () >= 1) ? 1 : 0;
		delete inst_set_var_ptr;
		inst_set_var_ptr = result_inst_set_var_ptr;
	    }
	}
	else
	{
	    GS_ui::inform (UI_INFORM__ERROR, GS_string ("Variable '")
		+ p_inst_set_var_name_str
		+ "' is Defined but is NOT of type INST_SET_REF.");
	}
    }
    else
    {
	GS_stack::push_var (inst_set_var_ptr, p_inst_set_var_name_str);
    }


    return inst_set_var_ptr;
#endif
}





t_boolean
GS_select::is_valid_object (const GS_string& p_obj_key_letter_str)

{
    GS_string obj_key_letter_str (p_obj_key_letter_str);
    mc_dbms_Set <I_Object*>* obj_coll_ptr
        = I_Object::find_Object_by_key_letter (GS_gen_sim_db_ptr,
	    obj_key_letter_str.char_ptr ());

    if (! obj_coll_ptr)
    {
        LOG_ERROR ((L_log_string,
	    "GS_select::is_valid_object ():  I_Object collection pointer on find is 0."));
	return FALSE;
    }

    if (obj_coll_ptr->cardinality () < 1)
    {
	obj_key_letter_str.convert_to_upper_case ();
	delete obj_coll_ptr;
	obj_coll_ptr = I_Object::find_Object_by_key_letter (GS_gen_sim_db_ptr,
		obj_key_letter_str.char_ptr ());

	if (! obj_coll_ptr)
	{
	    LOG_ERROR ((L_log_string,
		"GS_select::is_valid_object ():  I_Object collection pointer on find is 0."));
	    return FALSE;
	}

	if (obj_coll_ptr->cardinality () < 1)
	{
	    delete obj_coll_ptr;
	    return FALSE;
	}
    }

    if (obj_coll_ptr->cardinality () > 1)
    {
        GS_ui::inform (UI_INFORM__ERROR, GS_string
	    ("More than one object with keyletters '")
            + p_obj_key_letter_str + "' exists in the Database.");
	delete obj_coll_ptr;
        return FALSE;
    }

    I_Object* obj_ptr = obj_coll_ptr->pick ();
    delete obj_coll_ptr;
    if (! obj_ptr)
    {
        LOG_ERROR ((L_log_string,
	    "GS_select::is_valid_object ():  I_Object pointer in collection returned from find is 0."));
        return FALSE;
    }
    
    return TRUE;
}    





I_object_inst_ref_set_var*
GS_select::create__from_instances_of__no_push
    (const Description& p_obj_key_letter_str, const Description& p_condition_str,
    t_boolean p_any_flag)

{
    mc_dbms_Set <I_Object*>* obj_coll_ptr
	= I_Object::find_Object_by_key_letter (GS_gen_sim_db_ptr,
	    p_obj_key_letter_str.char_ptr ());
    if (! obj_coll_ptr)
    {
	LOG_ERROR ((L_log_string,
	    "GS_select::create__from_instances_of__no_push ():  Creation of I_Object collection in find returned 0."));
	return 0;
    }


    I_object_inst_ref_set_var* inst_set_var_ptr = 0;
    if (obj_coll_ptr->cardinality () < 1)
    {
	delete obj_coll_ptr;

	inst_set_var_ptr = new I_object_inst_ref_set_var ();
	inst_set_var_ptr->
	    set_last_resort_key_letters_str (p_obj_key_letter_str);
    }
    else
    {
	if (obj_coll_ptr->cardinality () > 1)
	{
	    Description err_msg("More than one object with key letters '");
		err_msg += p_obj_key_letter_str;
		err_msg += "' exists.";
	    GS_ui::inform (UI_INFORM__ERROR, err_msg);
	    return 0;
	}

	I_Object* obj_ptr = obj_coll_ptr->pick ();
	delete obj_coll_ptr;
	if (! obj_ptr)
	{
	    LOG_ERROR ((L_log_string,
		"GS_select::create__from_instances_of ():  I_Object pointer in collection of 1 element is 0."));
	    return 0;
	}

	mc_dbms_List <I_Object_Instance*>* oinst_coll_ptr
	    = obj_ptr->get_Object_Instance_R2001_coll_ptr ();
	if (! oinst_coll_ptr)
	{
	    LOG_ERROR ((L_log_string,
		"GS_select::create__from_instances_of ():  Creation of I_OINST collection returned 0."));
	    return 0;
	}

	inst_set_var_ptr
	    = new I_object_inst_ref_set_var (obj_ptr, oinst_coll_ptr);

	interpret_frag__where_clause
	    (inst_set_var_ptr, p_condition_str, p_any_flag);
    }


    return inst_set_var_ptr;
}




I_object_inst_ref_set_var*
GS_select::create__related_by__no_push
    (const Description& p_inst_chain_str, const Description& p_condition_str,
    t_boolean p_any_flag)

{
	char *inst_chain_str_ASCII = (char *) vcharExportAlloc( 
		vcharScribeASCIIExport(p_inst_chain_str.char_ptr()));
    GS_string inst_chain_str (inst_chain_str_ASCII);
	vcharExportFree( inst_chain_str_ASCII );


    I_object_inst_ref_set_var* intermediate_set_ptr [GS_MAX_NUM_CHAIN_LINKS];
    for (t_uint i = 0;
	(i < GS_MAX_NUM_CHAIN_LINKS);
	i++)
    {
	intermediate_set_ptr [i] = 0;
    }
    
    
    GS_string start_name_str = (inst_chain_str.parse_token ("->"));
    if ((inst_chain_str [inst_chain_str.cursor ()] != '-')
	|| (inst_chain_str [inst_chain_str.cursor () + 1] != '>'))
    {
	GS_ui::inform (UI_INFORM__ERROR, GS_string
	    ("Expected '->' in Instance Chain '")
	    + inst_chain_str + "'.");
	return 0;
    }


    GS_string inst_set_name_str (start_name_str);
    GS_var_si start_var_si;
    GS_expression::interpret_frag__rvalue (inst_set_name_str.char_ptr(), start_var_si);
    I_object_inst_ref_set_var* inst_set_var_ptr
	= start_var_si.get_object_inst_ref_set_var_ptr ();
    if (inst_set_var_ptr)
    {
	intermediate_set_ptr [0]
	    = new I_object_inst_ref_set_var (inst_set_var_ptr);
    }
    else
    {
	I_object_inst_ref_var* inst_var_ptr
	    = start_var_si.get_object_inst_ref_var_ptr ();
	if (inst_var_ptr)
	{
	    //  Convert the I_object_inst_ref_var to I_object_inst_ref_set_var.
	    //
	    intermediate_set_ptr [0]
		= new I_object_inst_ref_set_var (inst_var_ptr);
	}
	else
	{
	    GS_ui::inform (UI_INFORM__ERROR, GS_string ("Instance Chain '")
		+ inst_chain_str + "' begins with an undefined/incorrect '"
		+ start_name_str + "'.");
	    return 0;
	}
    }
	
	
    for (t_uint curr_rel_hop_num = 1;
	inst_chain_str.cursor () < inst_chain_str.length ();
	curr_rel_hop_num++)
    {
	inst_chain_str.consume_white_space ();
	if ((inst_chain_str [inst_chain_str.cursor ()] != '-')
	    || (inst_chain_str [inst_chain_str.cursor () + 1] != '>'))
	{
	    GS_ui::inform (UI_INFORM__ERROR, GS_string
		("Expected '->' in Instance Chain '")
		+ inst_chain_str + "'.");
	    delete intermediate_set_ptr [curr_rel_hop_num - 1];
	    return 0;
	}
	inst_chain_str++;
	inst_chain_str++;
	    
	    
	GS_string int_obj_key_letter_str
	    (inst_chain_str.parse_token ('['));
	if (inst_chain_str.curr_char () != '[')
	{
	    GS_ui::inform (UI_INFORM__ERROR, GS_string
		("Expected '[' in Instance Chain '")
		+ inst_chain_str + "'.");
	    delete intermediate_set_ptr [curr_rel_hop_num - 1];
	    return 0;
	} 
	inst_chain_str++;
	
	
	GS_string int_rel_num_str;
	GS_string int_direction_str;
	GS_string full_rel_num_str (inst_chain_str.parse_token (']',
	    GS_string::GS_IGNORE_WITHIN_TICKS
	    | GS_string::GS_IGNORE_REPEATED_TICKS_WITHIN_TICKS)); 
	if (inst_chain_str.curr_char () != ']')
	{
	    GS_ui::inform (UI_INFORM__ERROR, GS_string
		("Expected ']' in Instance Chain '")
		+ inst_chain_str + "'.");
	    delete intermediate_set_ptr [curr_rel_hop_num - 1];
	    return 0;
	} 
	inst_chain_str++;

	int_rel_num_str = full_rel_num_str.parse_token ('.');
	if (full_rel_num_str.curr_char () == '.')
	{
	    //  Direction string follows.
	    //
	    full_rel_num_str++;
	    int_direction_str = full_rel_num_str.parse_token__ticked_str ();
	}

    
	intermediate_set_ptr [curr_rel_hop_num] = create_single_link
	    (intermediate_set_ptr [curr_rel_hop_num - 1],
	    int_obj_key_letter_str.char_ptr(), 
		int_rel_num_str.char_ptr(), int_direction_str.char_ptr());


	//  Get rid of the prior intermediate result.
	//
	delete intermediate_set_ptr [curr_rel_hop_num - 1];
	
	
	if (intermediate_set_ptr [curr_rel_hop_num] == 0)
	{
	    //  Assume error message printed in single hop create.
	    //
	    return 0;
	}
    }
	

    if (curr_rel_hop_num <= 1)
    {
	GS_ui::inform (UI_INFORM__ERROR, GS_string
	    ("Instance Chain '") + inst_chain_str + "' is incomplete.");
	delete intermediate_set_ptr [0];
	return 0;
    }

	
    GS_select::interpret_frag__where_clause
	(intermediate_set_ptr [curr_rel_hop_num - 1],
	p_condition_str, p_any_flag);


    return intermediate_set_ptr [curr_rel_hop_num - 1];
}





I_object_inst_ref_set_var*
GS_select::create_single_link
    (I_object_inst_ref_set_var* p_start_inst_set_var_ptr,
    const Description& p_end_obj_key_letter_str, Description p_Rnum_str,
    Description p_rel_direction_str)
    
{
    I_object_inst_ref_set_var* new_inst_set_var_ptr
	= new I_object_inst_ref_set_var ();
    new_inst_set_var_ptr->
	set_last_resort_key_letters_str (p_end_obj_key_letter_str);
        
        
    p_start_inst_set_var_ptr->first ();
    
    
    if (! p_start_inst_set_var_ptr->is_empty ())
    {
        do
        {
	    if (p_start_inst_set_var_ptr->cursor ()
		> p_start_inst_set_var_ptr->cardinality ())
	    {
		LOG_ERROR ((L_log_string,
		    "End #1:  GS_select::create_single_link (0):  p_start_inst_set_var_ptr->cursor () exceeds the cardinality ()."));
		delete new_inst_set_var_ptr;
		return 0;
	    }

	    if ((p_start_inst_set_var_ptr->cursor () < 1)
		&& (p_start_inst_set_var_ptr->cardinality () >= 1))
	    {
		LOG_ERROR ((L_log_string,
		    "End #2:  GS_select::create_single_link (0):  p_start_inst_set_var_ptr->cursor () < 1."));
		delete new_inst_set_var_ptr;
		return 0;
	    }

	    I_Object_Instance* start_oinst_ptr
		= p_start_inst_set_var_ptr->m_oinst_coll.retrieve
		    (p_start_inst_set_var_ptr->cursor () - 1);

	    if (! start_oinst_ptr)
	    {
		LOG_ERROR ((L_log_string,
		    "End #3:  GS_select::create_single_link (0):  start_oinst_ptr is 0."));
		delete new_inst_set_var_ptr;
		return 0;
	    }


	    extern t_boolean is_simulator;
	    if (! is_simulator)
	    {
		//  Check to see if this object instance has been related yet.
		//    If not, then search out the related instance before
		//    proceeding.
		//
		if (! I_relate::relate_object_instance (start_oinst_ptr,
		    p_end_obj_key_letter_str, p_Rnum_str, p_rel_direction_str))
		{
		    delete new_inst_set_var_ptr;
		    return 0;
		}
	    }


	    if (! start_oinst_ptr->
		get_Related_Object_Instance_Pair_R2010_coll_ptr ())
	    {
		LOG_ERROR ((L_log_string,
		    "End #5:  GS_select::create_single_link (0):  start_oinst_ptr->ROIP_R2010_coll_ptr == 0"));
		return 0;
	    }

	    I_Related_Object_Instance_Pair *roip_ptr;
	    FOR_ALL_ELEMENTS
		(roip_ptr,
		I_Related_Object_Instance_Pair,
		start_oinst_ptr->get_Related_Object_Instance_Pair_R2010_coll_ptr (),
		sim_roip_cursor1)
	    {
		if (p_Rnum_str == roip_ptr->get_Rnum_str ())
		{
		    Description phrase_str (roip_ptr->get_R2011_phrase ());
		    if ((p_rel_direction_str.length() == 0)
			|| ( phrase_str == p_rel_direction_str))
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
				"End #9:  GS_select::create_single_link (0):  related_oinst_ptr == 0"));
			    return 0;
			}

			if (! related_oinst_ptr->get_Object_R2001_ptr ())
			{
			    LOG_ERROR ((L_log_string,
				"End #10:  GS_select::create_single_link (0):  related_oinst_ptr->get_Object_R2001_ptr () == 0"));
			    return 0;
			}

			if (p_end_obj_key_letter_str == related_oinst_ptr->
			    get_Object_R2001_ptr ()->get_key_letter ())
			{
                t_boolean dup_exists = FALSE;
            	I_Object_Instance *oi_ptr;
	            FOR_ALL_ELEMENTS
		        (oi_ptr,
		        I_Object_Instance,
		        &new_inst_set_var_ptr->m_oinst_coll,
		        oi_cursor)
	            {
                    if ( oi_ptr == related_oinst_ptr )
                    {
                        dup_exists = TRUE;
                        break;
                    }
                }
                if ( dup_exists )
                {
                    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_STEP_LO, (L_log_string,
	    			    "GS_select::create_single_link ():  Pointer trying to be added to inst_set more than once."));
                }
                else
                {
    				new_inst_set_var_ptr->m_obj_ptr =
	    			    related_oinst_ptr->get_Object_R2001_ptr ();
    				new_inst_set_var_ptr->m_oinst_coll.
	    			    insert_last (related_oinst_ptr);
                }
			}
		    }
		}
	    }


	    if (! start_oinst_ptr->
		get_Related_Object_Instance_Pair_R2011_coll_ptr ())
	    {
		LOG_ERROR ((L_log_string,
		    "End #5:  GS_select::create_single_link (0):  start_oinst_ptr->ROIP_R2011_coll_ptr == 0"));
		return 0;
	    }

	    FOR_ALL_ELEMENTS
		(roip_ptr,
		I_Related_Object_Instance_Pair,
		start_oinst_ptr->get_Related_Object_Instance_Pair_R2011_coll_ptr (),
		sim_roip_cursor2)
	    {
		if (p_Rnum_str == roip_ptr->get_Rnum_str ())
		{
		    Description phrase_str (roip_ptr->get_R2010_phrase ());
		    if ((p_rel_direction_str.length() == 0)
			|| (phrase_str == p_rel_direction_str))
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
				"End #10:  GS_select::create_single_link (0):  related_oinst_ptr == 0"));
			    return 0;
			}

			if (! related_oinst_ptr->get_Object_R2001_ptr ())
			{
			    LOG_ERROR ((L_log_string,
				"End #10:  GS_select::create_single_link (0):  related_oinst_ptr->get_Object_R2001_ptr () == 0"));
			    return 0;
			}

			if (p_end_obj_key_letter_str == related_oinst_ptr->
			    get_Object_R2001_ptr ()->get_key_letter ())
			{
                t_boolean dup_exists = FALSE;
            	I_Object_Instance *oi_ptr;
	            FOR_ALL_ELEMENTS
		        (oi_ptr,
		        I_Object_Instance,
		        &new_inst_set_var_ptr->m_oinst_coll,
		        oi_cursor)
	            {
                    if ( oi_ptr == related_oinst_ptr )
                    {
                        dup_exists = TRUE;
                        break;
                    }
                }
                if ( dup_exists )
                {
                    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_STEP_LO, (L_log_string,
	    			    "GS_select::create_single_link ():  Pointer trying to be added to inst_set more than once."));
                }
                else
                {
    				new_inst_set_var_ptr->m_obj_ptr =
	    			    related_oinst_ptr->get_Object_R2001_ptr ();
		    		new_inst_set_var_ptr->m_oinst_coll.
			    	    insert_last (related_oinst_ptr);
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
	Description obj_key_letter_str (p_end_obj_key_letter_str);
	mc_dbms_Set <I_Object*>* obj_coll_ptr
	    = I_Object::find_Object_by_key_letter (GS_gen_sim_db_ptr,
		obj_key_letter_str.char_ptr ());

	if (! obj_coll_ptr)
	{
	    LOG_ERROR ((L_log_string,
		"GS_select::create_single_link ():  I_Object collection pointer on find is 0."));
	    return 0;
	}

	if (obj_coll_ptr->cardinality () > 1)
	{
		Description err_msg ("More than one object with keyletters '");
		err_msg += p_end_obj_key_letter_str;
		err_msg += "' exists in the Database.\n\tSelecting one to use.";
	    GS_ui::inform (UI_INFORM__WARNING, err_msg);
	}

	if (obj_coll_ptr->cardinality () > 0)
	{
	    new_inst_set_var_ptr->m_obj_ptr = obj_coll_ptr->pick ();
	    delete obj_coll_ptr;
	    if (! new_inst_set_var_ptr->m_obj_ptr)
	    {
		LOG_ERROR ((L_log_string,
		    "GS_select::create_single_link ():  I_Object pointer in collection returned from find is 0."));
		return 0;
	    }
	}
	else
	{
	    delete obj_coll_ptr;

	    obj_key_letter_str.convert_to_upper_case ();
	    obj_coll_ptr = I_Object::find_Object_by_key_letter
		(GS_gen_sim_db_ptr, obj_key_letter_str.char_ptr ());

	    if (! obj_coll_ptr)
	    {
		LOG_ERROR ((L_log_string,
		    "GS_select::create_single_link ():  I_Object collection pointer on find is 0."));
		return 0;
	    }

	    if (obj_coll_ptr->cardinality () > 1)
	    {
		    Description err_msg("More than one object with keyletters '");
		    err_msg += obj_key_letter_str;
			err_msg += "' exists in the Database.\n\tSelecting one to use.";
			GS_ui::inform (UI_INFORM__WARNING, err_msg);
	    }

	    if (obj_coll_ptr->cardinality () > 0)
	    {
		new_inst_set_var_ptr->m_obj_ptr = obj_coll_ptr->pick ();
		delete obj_coll_ptr;
		if (! new_inst_set_var_ptr->m_obj_ptr)
		{
		    LOG_ERROR ((L_log_string,
			"GS_select::create_single_link ():  I_Object pointer in collection returned from find is 0."));
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
			err_msg += p_end_obj_key_letter_str;
			err_msg += "' does not exist in the Database.";
		    GS_ui::inform (UI_INFORM__ERROR, err_msg);
		    return 0;
		}
		else
		{
		    new_inst_set_var_ptr->m_obj_ptr
			= GS_sim_obj::create__I_Object
			(p_end_obj_key_letter_str);
		    if (! new_inst_set_var_ptr->m_obj_ptr)
		    {
			 Description err_msg("Unable to create Object with keyletters '");
			    err_msg += p_end_obj_key_letter_str; 
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
		"End #15:  GS_select::create_single_link (0):  Pointer from I_OINST to O_OBJ is 0 - audit failed."));
	    delete new_inst_set_var_ptr;
	    return 0;
	}

	if ( obj_ptr->get_key_letter () != p_end_obj_key_letter_str )
	{
	    LOG_ERROR ((L_log_string,
		"End #16:  GS_select::create_single_link (0):  Select object instance is NOT an instance of I_Object '%s' - audit failed.",
		p_end_obj_key_letter_str.char_ptr ()));
	    delete new_inst_set_var_ptr;
	    return 0;
	}
    }
    
    
    new_inst_set_var_ptr->m_cursor
	= (new_inst_set_var_ptr->cardinality () >= 1) ? 1 : 0;
    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	"End #17:  GS_select::create_single_link (new_inst_set_var_ptr=0x%08x).",
	new_inst_set_var_ptr));
    return new_inst_set_var_ptr;
}





void
GS_select::interpret_frag__where_clause
    (I_object_inst_ref_set_var* p_inst_set_var_ptr,
    const Description& p_condition_str, t_boolean p_any_flag)

{
    Description condition_str (p_condition_str);
	t_uint condition_cursor = 0;

    //  Remove the ';' off end of statement if one exists.
    //
    if (condition_str.length () > 0)
    {
	for (t_uint i = condition_str.length () - 1;
	    ((i >= 0) && (vcharIsWhiteSpace (condition_str.char_at(i))));
	    i--)
		/* do nothing */ ;

	if (condition_str.char_at(i) == ';')
	{
	    condition_str.truncate(i);
	}
    }


    if (! p_inst_set_var_ptr)
    {
	LOG_ERROR ((L_log_string,
	    "GS_select::interpret_frag__where_clause ():  p_inst_set_var_ptr == 0."));
	return;
    }


    if (condition_str.length() == 0)
    {
	//  No condition to interpret - leave collection totally in tact.
	//
	return;
    }

    t_int num_insts_checked = 0;
    t_int num_insts_passed = 0;

    mc_dbms_List <I_Object_Instance*> all_instance_coll;
    all_instance_coll = p_inst_set_var_ptr->m_oinst_coll;
    p_inst_set_var_ptr->m_oinst_coll.clear ();


    //  Determine if the WHERE condition can be optimized by doing a direct
    //    search.
    //
    t_boolean do_direct_search = FALSE;
    Description attr_name_str;
    GS_var_si rvalue_var_si;


    {
	Description expression_str (condition_str);
	t_uint expression_cursor = 0;
	expression_str.consume_white_space (expression_cursor);
	if (expression_str.char_at(expression_cursor) == '(')
	{
	    expression_cursor++;
	}
	Description raw_rvalue1_str;
    expression_str.parse_token__rvalue (expression_cursor, raw_rvalue1_str);
	t_uint raw_rvalue1_cursor = 0;
	Description binary_op_str;
    expression_str.parse_token__binary_op (expression_cursor, binary_op_str);
	if (binary_op_str == equal_equal_string)
	{
	    //  This is a '==' binary operation.
	    //
	    Description raw_rvalue2_str;
        expression_str.parse_token__rvalue (expression_cursor, raw_rvalue2_str);
		t_uint raw_rvalue2_cursor = 0;
	    expression_str.consume_white_space (expression_cursor);
	    if ((expression_cursor >= expression_str.length ())
		||
		(expression_str.char_at(expression_cursor) == ')'))
	    {
		//  This is a simple expression (not compound).
		//
		Description selected1_str;
        raw_rvalue1_str.parse_token ('.', raw_rvalue1_cursor, selected1_str);
		selected1_str.convert_to_upper_case ();
		Description selected2_str;
        raw_rvalue2_str.parse_token ('.', raw_rvalue2_cursor, selected2_str);
		selected2_str.convert_to_upper_case ();
		if ((selected1_str == selected_string)
		    &&
		    (selected2_str != selected_string))
		{
		    //  1st operand involves SELECTED attribute - 2nd does not.
		    //
		    raw_rvalue1_cursor++;
		    raw_rvalue1_str.parse_token (raw_rvalue1_cursor, attr_name_str);
		    GS_expression::interpret_frag__rvalue
			(raw_rvalue2_str, rvalue_var_si);
		    if ((! rvalue_var_si.get_var_ptr ())
			||
			(rvalue_var_si.get_var_ptr ()->get_core_data_type()
			    == VOID_DATATYPE))
		    {
			GS_ui::inform (UI_INFORM__ERROR,
			    GS_string("Second operand has invalid type."));
			p_inst_set_var_ptr->m_cursor
			    = (p_inst_set_var_ptr->cardinality () >= 1) ? 1 : 0;
			return;
		    }
		    do_direct_search = TRUE;
		}
		else if ((selected1_str != selected_string)
		    &&
		    (selected2_str == selected_string))
		{
		    //  2nd operand involves SELECTED attribute - 1st does not.
		    //
		    raw_rvalue2_cursor++;
		    raw_rvalue2_str.parse_token (raw_rvalue2_cursor, attr_name_str);
		    GS_expression::interpret_frag__rvalue
			(raw_rvalue2_str, rvalue_var_si);
		    if ((! rvalue_var_si.get_var_ptr ())
			||
			(rvalue_var_si.get_var_ptr ()->get_core_data_type()
			    == VOID_DATATYPE))
		    {
			GS_ui::inform (UI_INFORM__ERROR,
			    GS_string("First operand has invalid type."));
			p_inst_set_var_ptr->m_cursor
			    = (p_inst_set_var_ptr->cardinality () >= 1) ? 1 : 0;
			return;
		    }
		    do_direct_search = TRUE;
		}
	    }
	}
    }


    if (do_direct_search)
    {
	int attr_retrieval_position = -1;
	I_Object_Instance* oinst_ptr = 0;
	FOR_ALL_ELEMENTS
	    (oinst_ptr,
	    I_Object_Instance,
	    &(all_instance_coll),
	    oinst_cursor)
	{
	    num_insts_checked++;

	    if (attr_retrieval_position < 0)
	    {
		attr_name_str.convert_to_upper_case ();
		int ii = 0;
		I_Attribute_Instance* ainst_ptr = 0;
		FOR_ALL_ELEMENTS_SAFE
		    (ainst_ptr,
		    I_Attribute_Instance,
		    oinst_ptr->get_Attribute_Instance_R2002_coll_ptr (),
		    ainst_cursor)
		{
		    if (attr_name_str
			== ainst_ptr->get_Attribute_R2002_ptr ()->get_name ())
		    {
			attr_retrieval_position = ii;
		    }
		    else
		    {
			ii++;
		    }
		}
	    }
	    if (attr_retrieval_position < 0)
	    {
		GS_ui::inform (UI_INFORM__ERROR,
		    GS_string("Attribute of selected object does not exist."));
		p_inst_set_var_ptr->m_cursor
		    = (p_inst_set_var_ptr->cardinality () >= 1) ? 1 : 0;
		return;
	    }

	    I_Attribute_Instance* ainst_ptr
		= oinst_ptr->get_Attribute_Instance_R2002_coll_ptr ()->
		    retrieve (attr_retrieval_position);

	    if (ainst_ptr->get_core_data_type ()
		!= rvalue_var_si.get_var_ptr ()->get_core_data_type ())
	    {
		if (! (((ainst_ptr->get_core_data_type () == INTEGER_DATATYPE)
		    && (rvalue_var_si.get_var_ptr ()->get_core_data_type ()
		    == REAL_DATATYPE))
		    ||
		    ((ainst_ptr->get_core_data_type () == INTEGER_DATATYPE)
		    && (rvalue_var_si.get_var_ptr ()->get_core_data_type ()
		    == UNIQUE_ID_DATATYPE))
		    ||
		    ((ainst_ptr->get_core_data_type () == REAL_DATATYPE)
		    && (rvalue_var_si.get_var_ptr ()->get_core_data_type ()
		    == INTEGER_DATATYPE))
		    ||
		    ((ainst_ptr->get_core_data_type () == UNIQUE_ID_DATATYPE)
		    && (rvalue_var_si.get_var_ptr ()->get_core_data_type ()
		    == INTEGER_DATATYPE))))
		{
		    GS_ui::inform (UI_INFORM__ERROR,
			GS_string("WHERE operands not compatible == types."));
		    p_inst_set_var_ptr->m_cursor
			= (p_inst_set_var_ptr->cardinality () >= 1) ? 1 : 0;
		    return;
		}
	    }

	    if (*(ainst_ptr->get_var_ptr ())
		== *(rvalue_var_si.get_var_ptr ()))
	    {
		num_insts_passed++;

		//  Transfer pointer to this instance to the new instance
		//    set.
		//
	    p_inst_set_var_ptr->m_oinst_coll.insert_last (oinst_ptr);

		if (p_any_flag)
		{
		    break;
		}
	    }
	}
    }
    else
    {
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
		(p_inst_set_var_ptr->m_obj_ptr, oinst_ptr);
	    GS_stack::push_var (oinst_var_ptr, "SELECTED");
//	    delete oinst_var_ptr;
	    oinst_var_ptr = new I_object_inst_ref_var
		(p_inst_set_var_ptr->m_obj_ptr, oinst_ptr);
	    GS_stack::push_var (oinst_var_ptr, "Selected");
//	    delete oinst_var_ptr;
	    oinst_var_ptr = new I_object_inst_ref_var
		(p_inst_set_var_ptr->m_obj_ptr, oinst_ptr);
	    GS_stack::push_var (oinst_var_ptr, "selected");
//	    delete oinst_var_ptr;


	    GS_var_si cond_var_si;
        Description temp_condition_str (condition_str);
	    GS_expression::interpret_frag__expression
		(temp_condition_str, cond_var_si);


	    t_boolean error_occurred = FALSE;
	    if (cond_var_si.get_var_ptr ()->get_core_data_type ()
		!= BOOLEAN_DATATYPE)
	    {
		    Description err_msg ("WHERE expression -->");
			err_msg += condition_str;
		    err_msg += "<-- may only contain a BOOLEAN expression.";
			GS_ui::inform (UI_INFORM__ERROR, err_msg);
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
		    try 
		    {
				p_inst_set_var_ptr->m_oinst_coll.insert_last (oinst_ptr);
		    } catch (std::exception& mc_exception) {
				LOG_ERROR ((L_log_string,
				    "GS_select::interpret_frag__where_clause ():  Pointer trying to be added to inst_set more than once."));
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
		    "GS_select::interpret_frag__where_clause ():  Something pushed on stack during evaluation of condition."));
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
	}
    }

    p_inst_set_var_ptr->m_cursor
	= (p_inst_set_var_ptr->cardinality () >= 1) ? 1 : 0;

}


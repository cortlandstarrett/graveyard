/*========================================================================
 *
 * File:      $RCSfile: gs_gactn.cc,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:42:42 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#include <mc_dbms/mc_dbms.hh>

#include <stdio.h>
#include <iostream.h>
#include <fstream.h>
#include <ctype.h>

#include <gs_gactn.hh>
#include <u_string.hh>
#include <gs_ui.hh>
#include <gs_stack.hh>
#include <gs_selct.hh>
#include <i_obj.hh>
#include <i_attr.hh>
#include <i_ainst.hh>

#include <u_cursor.hh>
#include <u_trace.hh>
#include <u_error.hh>


extern mc_dbms_database* GS_gen_sim_db_ptr;




t_uint		GS_gen_action::s_actn_inst_num   = 1;
t_uint		GS_gen_action::s_blck_inst_num   = 1;
t_uint		GS_gen_action::s_stmt_inst_num   = 1;
t_uint		GS_gen_action::s_rval_inst_num   = 1;
t_uint		GS_gen_action::s_chain_inst_num  = 1;
t_uint		GS_gen_action::s_param_inst_num  = 1;
t_uint		GS_gen_action::s_var_inst_num    = 1;
GS_string	GS_gen_action::s_script_str      = "";

GS_string	GS_gen_action::al_inst_var_name_str;





void
GS_gen_action::gen_actn_script (GS_action::e_action_home p_action_home,
    GS_var_si* p_inst_var_si_ptr, const GS_string& p_script_file_name_str)

{
    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_BEGIN, (L_log_string,
        "Begin  GS_gen_action::gen_actn_script (p_action_home=%d, p_inst_var_si_ptr=0x%08x, p_script_file_name_str=\"%s\").",
        p_action_home, p_inst_var_si_ptr,
	p_script_file_name_str.char_ptr ()));


    //  Prepare for new script generation.
    //
    s_actn_inst_num    = 1;
    s_blck_inst_num    = 1;
    s_stmt_inst_num    = 1;
    s_rval_inst_num    = 1;
    s_chain_inst_num   = 1;
    s_param_inst_num   = 1;
    s_var_inst_num     = 1;
    s_script_str       = "";


    if (! p_inst_var_si_ptr)
    {
	LOG_ERROR ((L_log_string,
	    "GS_gen_action::gen_actn_script ():  p_inst_var_si_ptr==0."));
	return;
    }

    al_inst_var_name_str = p_inst_var_si_ptr->get_var_name_str ();

    if (! p_inst_var_si_ptr->get_object_inst_ref_var_ptr ())
    {
	GS_ui::inform (UI_INFORM__ERROR, GS_string
	    ("Variable '")
	    + al_inst_var_name_str
	    + "' is not an Object Instance Reference variable.");
	return;
    }


    switch (p_action_home)
    {
    case ASSIGNER_STATE:
	if (p_inst_var_si_ptr->get_object_inst_ref_var_ptr ()->
	    get_key_letters_str () != "SM_ACT")
	{
	    GS_ui::inform (UI_INFORM__ERROR, GS_string
		("Object Instance Reference Variable '")
		+ al_inst_var_name_str
		+ "' does not refer to an object of type SM_ACT.");
	    return;
	}
	break;

    case ATTRIBUTE:
	if (p_inst_var_si_ptr->get_object_inst_ref_var_ptr ()->
	    get_key_letters_str () != "O_ATTR")
	{
	    GS_ui::inform (UI_INFORM__ERROR, GS_string
		("Object Instance Reference Variable '")
		+ al_inst_var_name_str
		+ "' does not refer to an object of type O_ATTR.");
	    return;
	}
	break;

    case BRIDGE:
	if (p_inst_var_si_ptr->get_object_inst_ref_var_ptr ()->
	    get_key_letters_str () != "S_BRG")
	{
	    GS_ui::inform (UI_INFORM__ERROR, GS_string
		("Object Instance Reference Variable '")
		+ al_inst_var_name_str
		+ "' does not refer to an object of type S_BRG.");
	    return;
	}
	break;

    case DATA_TYPE:
	if (p_inst_var_si_ptr->get_object_inst_ref_var_ptr ()->
	    get_key_letters_str () != "S_DT")
	{
	    GS_ui::inform (UI_INFORM__ERROR, GS_string
		("Object Instance Reference Variable '")
		+ al_inst_var_name_str
		+ "' does not refer to an object of type S_DT.");
	    return;
	}
	break;

    case EE_EVENT:
	if (p_inst_var_si_ptr->get_object_inst_ref_var_ptr ()->
	    get_key_letters_str () != "S_EEEVT")
	{
	    GS_ui::inform (UI_INFORM__ERROR, GS_string
		("Object Instance Reference Variable '")
		+ al_inst_var_name_str
		+ "' does not refer to an object of type S_EEEVT.");
	    return;
	}
	break;

    case INSTANCE_STATE:
	if (p_inst_var_si_ptr->get_object_inst_ref_var_ptr ()->
	    get_key_letters_str () != "SM_ACT")
	{
	    GS_ui::inform (UI_INFORM__ERROR, GS_string
		("Object Instance Reference Variable '")
		+ al_inst_var_name_str
		+ "' does not refer to an object of type SM_ACT.");
	    return;
	}
	break;

    case RELATIONSHIP:
	if (p_inst_var_si_ptr->get_object_inst_ref_var_ptr ()->
	    get_key_letters_str () != "R_REL")
	{
	    GS_ui::inform (UI_INFORM__ERROR, GS_string
		("Object Instance Reference Variable '")
		+ al_inst_var_name_str
		+ "' does not refer to an object of type R_REL.");
	    return;
	}
	break;

    case SM_EVENT:
	if (p_inst_var_si_ptr->get_object_inst_ref_var_ptr ()->
	    get_key_letters_str () != "SM_EVT")
	{
	    GS_ui::inform (UI_INFORM__ERROR, GS_string
		("Object Instance Reference Variable '")
		+ al_inst_var_name_str
		+ "' does not refer to an object of type SM_EVT.");
	    return;
	}
	break;

    case TRANSFORMER:
	if (p_inst_var_si_ptr->get_object_inst_ref_var_ptr ()->
	    get_key_letters_str () != "O_TFR")
	{
	    GS_ui::inform (UI_INFORM__ERROR, GS_string
		("Object Instance Reference Variable '")
		+ al_inst_var_name_str
		+ "' does not refer to an object of type O_TFR.");
	    return;
	}
	break;

    default:
	LOG_ERROR ((L_log_string,
	    "GS_gen_action::gen_actn_script ():  p_action_home unknown."));
	return;
    }


    I_var* descrip_str_var_ptr = p_inst_var_si_ptr->
	get_object_inst_ref_var_ptr ()->get_attr_var_ptr ("Descrip");
    if (! descrip_str_var_ptr)
    {
	GS_ui::inform (UI_INFORM__ERROR, GS_string
	    ("Object Instance Reference Variable '")
	    + al_inst_var_name_str
	    + "' does not have an attribute named 'Descrip'.");
	return;
    }
    GS_gen_action gen_action (descrip_str_var_ptr->get_value_str ());
    gen_action.uncomment_action ();


    GS_string actn_frag_name_str (output_script__actn (GS_string
	("begin (")
	+ al_inst_var_name_str + ")"));


    //  Treat the whole action as a statement block.
    //
    GS_string blck_frag_name_str (gen_action.gen_blck_script (BLCK_ACTN,
	p_action_home));


    actn_frag_name_str
	= output_script__actn (GS_string ("append_blck (")
	+ actn_frag_name_str + ", "
	+ blck_frag_name_str + ")");
    actn_frag_name_str
	= output_script__actn (GS_string ("end (")
	+ actn_frag_name_str + ")");


    s_script_str += GS_string ("${") + actn_frag_name_str + ".body}\n";


    ofstream out_file;
    out_file.open (((GS_string&) p_script_file_name_str).char_ptr (), ios::out);
    if (! out_file.good ())
    {
	GS_ui::inform (UI_INFORM__ERROR, GS_string
	    ("Could not open temporary file '")
	    + p_script_file_name_str
	    + "' for writing.");
	return;
    }
    else
    {
	out_file << s_script_str.char_ptr () << flush;
    }


    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
        "End  GS_gen_action::gen_actn_script ()."));
    return;
}





GS_string
GS_gen_action::gen_blck_script (e_blck_type p_blck_type,
    GS_action::e_action_home p_action_home)

{
    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_BEGIN, (L_log_string,
        "Begin  GS_gen_action::gen_blck_script (p_blck_type=%d, p_action_home=%d).",
        p_blck_type, p_action_home));


    GS_string blck_frag_name_str (output_script__blck ("begin ()"));


    if (p_blck_type == BLCK_ACTN)
    {
	GS_stack::push_ctrl (new GS_function_si (0, 0, 0, "", ""));
	if (p_action_home == INSTANCE_STATE)
	{
	    GS_string self_var_frag_name_str (output_script__var (GS_string
		("declare_self_obj_inst_ref (")
		+ al_inst_var_name_str + ")"));
	    I_object_inst_ref_var* inst_var_ptr = new I_object_inst_ref_var ();
	    inst_var_ptr->set_last_resort_key_letters_str ("____SELF____");
	    GS_stack::push_var (inst_var_ptr, "self", self_var_frag_name_str);
	}
    }
    else if (p_blck_type == BLCK_FOR)
    {
	GS_stack::push_ctrl (new GS_for_si ("", "", 0, 0));
    }
    else if (p_blck_type == BLCK_IF)
    {
	GS_stack::push_ctrl (new GS_if_si (0));
    }
    else
    {
	LOG_ERROR ((L_log_string,
	    "GS_gen_action::gen_blck_script ():  p_blck_type unknown."));
    }


    t_boolean done = FALSE;
    while ((! done) && (m_action_str.cursor () < m_action_str.length ()))
    {
	GS_string stmt_frag_name_str;

	m_action_str.consume_white_space ();
	t_uint stmt_begin_char_num = m_action_str.cursor ();
	t_uint ii = m_action_str.cursor ();
	GS_string stmt_keyword_str (m_action_str.parse_token ());
	stmt_keyword_str.convert_to_upper_case ();
	m_action_str.reset_cursor (stmt_begin_char_num);


    
        if (stmt_keyword_str == "SELECT")
        {
	    GS_string select_stmt_str (m_action_str.parse_token (';',
		GS_string::GS_IGNORE_WITHIN_TICKS |
		GS_string::GS_IGNORE_REPEATED_TICKS_WITHIN_TICKS |
		GS_string::GS_IGNORE_WITHIN_QUOTES |
		GS_string::GS_IGNORE_REPEATED_QUOTES_WITHIN_QUOTES)); 
	    if (m_action_str.curr_char () != ';')
	    {
		GS_ui::inform (UI_INFORM__ERROR, GS_string
		    ("Could not find ';' character at end of Statement  --->")
		    + select_stmt_str + "<----");
	    }
	    else
	    {
		m_action_str++;
		GS_UI_INFORM (UI_INFORM__STMT, (GS_string
		    ("Generating Script for Statement --->")
		    + select_stmt_str + "<----"));
		stmt_frag_name_str = gen_stmt_script__select (select_stmt_str);
	    }
        }


        else if (stmt_keyword_str == "FOR")
        {
            GS_string for_stmt_str;      
            GS_string for_blck_str;
            parse_blck__for (for_stmt_str, for_blck_str);
            GS_UI_INFORM (UI_INFORM__STMT, (GS_string
                ("Generating Script for Statement --->")
                + for_stmt_str + "<----"));
            stmt_frag_name_str
		= gen_stmt_script__for (for_stmt_str, for_blck_str);
        }


        else if (stmt_keyword_str == "CREATE")
        {
	    GS_string create_stmt_str (m_action_str.parse_token (';',
		GS_string::GS_IGNORE_WITHIN_TICKS |
		GS_string::GS_IGNORE_REPEATED_TICKS_WITHIN_TICKS |
		GS_string::GS_IGNORE_WITHIN_QUOTES |
		GS_string::GS_IGNORE_REPEATED_QUOTES_WITHIN_QUOTES)); 
	    if (m_action_str.curr_char () != ';')
	    {
		GS_ui::inform (UI_INFORM__ERROR, GS_string
		    ("Could not find ';' character at end of Statement  --->")
		    + create_stmt_str + "<----");
	    }
	    else
	    {
		m_action_str++;
		GS_string create_str (create_stmt_str.parse_token ());
		GS_string create_type_str (create_stmt_str.parse_token ());
		create_stmt_str.reset_cursor ();
		create_type_str.convert_to_upper_case ();
		if (create_type_str == "OBJECT")
		{
		    GS_UI_INFORM (UI_INFORM__STMT, (GS_string
			("Generating Script for Statement --->")
			+ create_stmt_str + "<----"));
		    stmt_frag_name_str
			= gen_stmt_script__create_obj (create_stmt_str);
		}
		else if (create_type_str == "EVENT")
		{
		    GS_UI_INFORM (UI_INFORM__STMT, (GS_string
			("Generating Script for Statement --->")
			+ create_stmt_str + "<----"));
		    stmt_frag_name_str
			= gen_stmt_script__create_evt (create_stmt_str);
		}
	    }
        }
        else if (stmt_keyword_str == "DELETE")
        {
            GS_string delete_stmt_str (m_action_str.parse_token (';',
		GS_string::GS_IGNORE_WITHIN_TICKS |
		GS_string::GS_IGNORE_REPEATED_TICKS_WITHIN_TICKS |
		GS_string::GS_IGNORE_WITHIN_QUOTES |
		GS_string::GS_IGNORE_REPEATED_QUOTES_WITHIN_QUOTES)); 
	    if (m_action_str.curr_char () != ';')
	    {
		GS_ui::inform (UI_INFORM__ERROR, GS_string
		    ("Could not find ';' character at end of Statement  --->")
		    + delete_stmt_str + "<----");
	    }
	    else
	    {
		m_action_str++;
		GS_UI_INFORM (UI_INFORM__STMT, (GS_string
		    ("Generating Script for Statement --->")
		    + delete_stmt_str + "<----"));
		stmt_frag_name_str
		    = gen_stmt_script__delete (delete_stmt_str);
	    }
        }
        else if (stmt_keyword_str == "RELATE")
        {
            GS_string relate_stmt_str (m_action_str.parse_token (';',
		GS_string::GS_IGNORE_WITHIN_TICKS |
		GS_string::GS_IGNORE_REPEATED_TICKS_WITHIN_TICKS |
		GS_string::GS_IGNORE_WITHIN_QUOTES |
		GS_string::GS_IGNORE_REPEATED_QUOTES_WITHIN_QUOTES)); 
	    if (m_action_str.curr_char () != ';')
	    {
		GS_ui::inform (UI_INFORM__ERROR, GS_string
		    ("Could not find ';' character at end of Statement  --->")
		    + relate_stmt_str + "<----");
	    }
	    else
	    {
		m_action_str++;
		GS_UI_INFORM (UI_INFORM__STMT, (GS_string
		    ("Generating Script for Statement --->")
		    + relate_stmt_str + "<----"));
		stmt_frag_name_str = gen_stmt_script__relate (relate_stmt_str);
	    }
        }
        else if (stmt_keyword_str == "UNRELATE")
        {
            GS_string unrelate_stmt_str (m_action_str.parse_token (';',
		GS_string::GS_IGNORE_WITHIN_TICKS |
		GS_string::GS_IGNORE_REPEATED_TICKS_WITHIN_TICKS |
		GS_string::GS_IGNORE_WITHIN_QUOTES |
		GS_string::GS_IGNORE_REPEATED_QUOTES_WITHIN_QUOTES)); 
	    if (m_action_str.curr_char () != ';')
	    {
		GS_ui::inform (UI_INFORM__ERROR, GS_string
		    ("Could not find ';' character at end of Statement  --->")
		    + unrelate_stmt_str + "<----");
	    }
	    else
	    {
		m_action_str++;
		GS_UI_INFORM (UI_INFORM__STMT, (GS_string
		    ("Generating Script for Statement --->")
		    + unrelate_stmt_str + "<----"));
		stmt_frag_name_str
		    = gen_stmt_script__unrelate (unrelate_stmt_str);
	    }
        }
        else if (stmt_keyword_str == "GENERATE")
        {
            GS_string generate_stmt_str = (m_action_str.parse_token (';',
		GS_string::GS_IGNORE_WITHIN_TICKS |
		GS_string::GS_IGNORE_REPEATED_TICKS_WITHIN_TICKS |
		GS_string::GS_IGNORE_WITHIN_QUOTES |
		GS_string::GS_IGNORE_REPEATED_QUOTES_WITHIN_QUOTES)); 
	    if (m_action_str.curr_char () != ';')
	    {
		GS_ui::inform (UI_INFORM__ERROR, GS_string
		    ("Could not find ';' character at end of Statement  --->")
		    + generate_stmt_str + "<----");
	    }
	    else
	    {
		m_action_str++;
		GS_UI_INFORM (UI_INFORM__STMT, (GS_string
		    ("Generating Script for Statement --->")
		    + generate_stmt_str + "<----"));
		stmt_frag_name_str
		    = gen_stmt_script__generate (generate_stmt_str);
	    }
        }
        else if (stmt_keyword_str == "ASSIGN")
        {
            GS_string assign_stmt_str (m_action_str.parse_token (';',
		GS_string::GS_IGNORE_WITHIN_TICKS |
		GS_string::GS_IGNORE_REPEATED_TICKS_WITHIN_TICKS |
		GS_string::GS_IGNORE_WITHIN_QUOTES |
		GS_string::GS_IGNORE_REPEATED_QUOTES_WITHIN_QUOTES)); 
	    if (m_action_str.curr_char () != ';')
	    {
		GS_ui::inform (UI_INFORM__ERROR, GS_string
		    ("Could not find ';' character at end of Statement  --->")
		    + assign_stmt_str + "<----");
	    }
	    else
	    {
		m_action_str++;
		GS_UI_INFORM (UI_INFORM__STMT, (GS_string
		    ("Generating Script for Statement --->")
		    + assign_stmt_str + "<----"));
		stmt_frag_name_str = gen_stmt_script__assign (assign_stmt_str);
	    }
        }
        else if (stmt_keyword_str == "TRANSFORM")
        {
            GS_string transform_stmt_str (m_action_str.parse_token (';',
		GS_string::GS_IGNORE_WITHIN_TICKS |
		GS_string::GS_IGNORE_REPEATED_TICKS_WITHIN_TICKS |
		GS_string::GS_IGNORE_WITHIN_QUOTES |
		GS_string::GS_IGNORE_REPEATED_QUOTES_WITHIN_QUOTES)); 
	    if (m_action_str.curr_char () != ';')
	    {
		GS_ui::inform (UI_INFORM__ERROR, GS_string
		    ("Could not find ';' character at end of Statement  --->")
		    + transform_stmt_str + "<----");
	    }
	    else
	    {
		m_action_str++;
		GS_UI_INFORM (UI_INFORM__STMT, (GS_string
		    ("Generating Script for Statement --->")
		    + transform_stmt_str + "<----"));
		stmt_frag_name_str
		    = gen_stmt_script__transform (transform_stmt_str);
	    }
        }


	else if (((m_action_str [ii  ] == 'I') || (m_action_str [ii  ] == 'i'))
	      && ((m_action_str [ii+1] == 'F') || (m_action_str [ii+1] == 'f')))
	{
            GS_string if_stmt_str;      
            GS_string if_blck_str;
            GS_string else_blck_str;
            parse_blck__if_else (if_stmt_str, if_blck_str, else_blck_str);
            GS_UI_INFORM (UI_INFORM__STMT, (GS_string
                ("Generating Script for Statement --->")
                + if_stmt_str + "<----"));
	    stmt_frag_name_str
		= gen_stmt_script__if (if_stmt_str, if_blck_str);
	    if (else_blck_str != "")
	    {
		blck_frag_name_str
		    = output_script__blck (GS_string ("append_stmt (")
		    + blck_frag_name_str + ", "
		    + stmt_frag_name_str + ")");
		stmt_frag_name_str
		    = gen_stmt_script__else (else_blck_str);
	    }
        }
        else if (stmt_keyword_str == "BRIDGE")
        {
            GS_string bridge_stmt_str (m_action_str.parse_token (';',
		GS_string::GS_IGNORE_WITHIN_TICKS |
		GS_string::GS_IGNORE_REPEATED_TICKS_WITHIN_TICKS |
		GS_string::GS_IGNORE_WITHIN_QUOTES |
		GS_string::GS_IGNORE_REPEATED_QUOTES_WITHIN_QUOTES)); 
	    if (m_action_str.curr_char () != ';')
	    {
		GS_ui::inform (UI_INFORM__ERROR, GS_string
		    ("Could not find ';' character at end of Statement  --->")
		    + bridge_stmt_str + "<----");
	    }
	    else
	    {
		m_action_str++;
		GS_UI_INFORM (UI_INFORM__STMT, (GS_string
		    ("Generating Script for Statement --->")
		    + bridge_stmt_str + "<----"));
		stmt_frag_name_str
		    = gen_stmt_script__bridge (bridge_stmt_str);
	    }
        }
        else if (stmt_keyword_str == "END")
        {
            GS_string end_stmt_str (m_action_str.parse_token (';',
		GS_string::GS_IGNORE_WITHIN_TICKS |
		GS_string::GS_IGNORE_REPEATED_TICKS_WITHIN_TICKS |
		GS_string::GS_IGNORE_WITHIN_QUOTES |
		GS_string::GS_IGNORE_REPEATED_QUOTES_WITHIN_QUOTES)); 
	    if (m_action_str.curr_char () == ';')
	    {
		m_action_str++;
	    }
	    GS_ui::inform (UI_INFORM__ERROR, GS_string
		("Unexpected Statement  --->") + end_stmt_str + "<----");
        }
	else if (stmt_keyword_str == "RETURN")
	{
	    GS_string return_stmt_str (m_action_str.parse_token (';',
		GS_string::GS_IGNORE_WITHIN_TICKS |
		GS_string::GS_IGNORE_REPEATED_TICKS_WITHIN_TICKS |
		GS_string::GS_IGNORE_WITHIN_QUOTES |
		GS_string::GS_IGNORE_REPEATED_QUOTES_WITHIN_QUOTES)); 
	    if (m_action_str.curr_char () != ';')
	    {
		GS_ui::inform (UI_INFORM__ERROR, GS_string
		    ("Could not find ';' character at end of Statement  --->")
		    + return_stmt_str + "<----");
	    }
	    else
	    {
		m_action_str++;
		GS_UI_INFORM (UI_INFORM__STMT, (GS_string
		    ("Generating Script for Statement --->")
		    + return_stmt_str + "<----"));
		stmt_frag_name_str
		    = gen_stmt_script__return (return_stmt_str);
	    }
	}
        else if (stmt_keyword_str == "")
	{
	    //  Do nothing.
	}
        else
        {
            GS_ui::inform (UI_INFORM__ERROR, "Do not recognize statement.");
	    done = TRUE;
        }


	if ( stmt_frag_name_str != "" )
	{
	    blck_frag_name_str = output_script__blck (GS_string ("append_stmt(")
	        + blck_frag_name_str + ", "
	        + stmt_frag_name_str + ")");
	}
	m_action_str.consume_white_space ();
    }


    if (p_blck_type == BLCK_ACTN)
    {
	GS_stack_item* curr_item_ptr = GS_stack::pop ();
	while ((curr_item_ptr) && (! curr_item_ptr->get_function_si_ptr ()))
	{
	    if (curr_item_ptr->get_var_si_ptr ())
	    {
		blck_frag_name_str = output_script__blck (GS_string
		    ("var_out_of_scope (")
		    + blck_frag_name_str + ", "
		    + curr_item_ptr->get_var_si_ptr ()->get_var_frag_name_str ()
		    + ")");
	    }
	    else
	    {
		GS_ui::inform (UI_INFORM__ERROR,
		    "Statement Block not closed before end of action.");
	    }
	    delete curr_item_ptr;
	    curr_item_ptr = GS_stack::pop ();
	}
	if (! curr_item_ptr)
	{
	    LOG_ERROR ((L_log_string,
		"GS_gen_action::gen_blck_script ():  Could not find beginning of action."));
	}
    }
    else if (p_blck_type == BLCK_FOR)
    {
	GS_stack_item* curr_item_ptr = GS_stack::pop ();
	while ((curr_item_ptr) && (! curr_item_ptr->get_for_si_ptr ()))
	{
	    if (curr_item_ptr->get_var_si_ptr ())
	    {
		blck_frag_name_str = output_script__blck (GS_string
		    ("var_out_of_scope (")
		    + blck_frag_name_str + ", "
		    + curr_item_ptr->get_var_si_ptr ()->get_var_frag_name_str ()
		    + ")");
	    }
	    else
	    {
		GS_ui::inform (UI_INFORM__ERROR,
		    "Statement Block not closed before end of FOR EACH statement.");
	    }
	    delete curr_item_ptr;
	    curr_item_ptr = GS_stack::pop ();
	}
	if (! curr_item_ptr)
	{
	    LOG_ERROR ((L_log_string,
		"GS_gen_action::gen_blck_script ():  Could not find beginning of for stmt."));
	}
    }
    else if (p_blck_type == BLCK_IF)
    {
	GS_stack_item* curr_item_ptr = GS_stack::pop ();
	while ((curr_item_ptr) && (! curr_item_ptr->get_if_si_ptr ()))
	{
	    if (curr_item_ptr->get_var_si_ptr ())
	    {
		blck_frag_name_str = output_script__blck (GS_string
		    ("var_out_of_scope (")
		    + blck_frag_name_str + ", "
		    + curr_item_ptr->get_var_si_ptr ()->get_var_frag_name_str ()
		    + ")");
	    }
	    else
	    {
		GS_ui::inform (UI_INFORM__ERROR,
		    "Statement Block not closed before end of IF statement.");
	    }
	    delete curr_item_ptr;
	    curr_item_ptr = GS_stack::pop ();
	}
	if (! curr_item_ptr)
	{
	    LOG_ERROR ((L_log_string,
		"GS_gen_action::gen_blck_script ():  Could not find beginning of if stmt."));
	}
    }


    blck_frag_name_str = output_script__blck (GS_string ("end (")
	+ blck_frag_name_str + ")");


    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
        "End  GS_gen_action::gen_blck_script ()."));
    return blck_frag_name_str;
}





GS_string
GS_gen_action::gen_stmt_script__select (const GS_string& p_stmt_str)

{
    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_BEGIN, (L_log_string,
        "Begin  GS_gen_action::gen_stmt_script__select (p_stmt_str=\"%s\").",
        p_stmt_str.char_ptr ()));


    GS_string stmt_str = p_stmt_str;


    GS_string select_keyword_str (stmt_str.parse_token ());

    GS_string cardinality_str (stmt_str.parse_token ());
    cardinality_str.convert_to_upper_case ();

    GS_string inst_var_name_str (stmt_str.parse_token ());

    GS_string related_or_from_str (stmt_str.parse_token ());
    related_or_from_str.convert_to_upper_case ();


    if (! ((cardinality_str == "ONE")
	|| (cardinality_str == "ANY")
	|| (cardinality_str == "MANY")))
    {
        GS_ui::inform (UI_INFORM__ERROR,
	    "SELECT statement requires specification of ONE, ANY, or MANY.");
        return "";
    }


    if (related_or_from_str == "RELATED")
    {
        GS_string by_keyword_str (stmt_str.parse_token ());
    }
    else if (related_or_from_str == "FROM")
    {
        GS_string instances_keyword_str (stmt_str.parse_token ());
        GS_string of_keyword_str (stmt_str.parse_token ());
    }
    else
    {
        GS_ui::inform (UI_INFORM__ERROR,
	    "SELECT statement requires specification of either RELATED BY or FROM INSTANCES OF.");
        return "";
    }


    GS_string stmt_frag_name_str;
    GS_string is_implicitly_declared ("FALSE");
    GS_string result_var_frag_name_str;
    if (related_or_from_str == "RELATED")
    {
        //  Parsed statement:
        //    SELECT <card> <inst-ref> RELATED BY <inst-chain> WHERE <cond>
        //
        GS_string chain_str (stmt_str.parse_to_keyword ("WHERE"));
        GS_string result_obj_key_letters_str;
        GS_string chain_frag_name_str = gen_chain_script
	    (cardinality_str, chain_str, result_obj_key_letters_str);
        stmt_str.parse_token ();
        GS_string condition_str (stmt_str.parse_to_end ());

	if ((cardinality_str == "ONE") || (cardinality_str == "ANY"))
	{
	    GS_string lower_case_inst_var_name_str (inst_var_name_str);
	    lower_case_inst_var_name_str.convert_to_lower_case ();
	    if (lower_case_inst_var_name_str == "self")
	    {
		GS_ui::inform (UI_INFORM__ERROR, GS_string
		    ("Instance '") + inst_var_name_str
		    + "' NOT allowed to be used as result variable in SELECT statement.");
		return "";
	    }
	    GS_var_si* inst_var_si_ptr
		= GS_stack::find_var_si_ptr (inst_var_name_str);
	    I_object_inst_ref_var* inst_var_ptr = 0;
	    if (inst_var_si_ptr)
	    {
		inst_var_ptr = inst_var_si_ptr->get_object_inst_ref_var_ptr ();
	    }
	    if (inst_var_ptr)
	    {
		result_var_frag_name_str
		    = inst_var_si_ptr->get_var_frag_name_str ();
	    }
	    else
	    {
		result_var_frag_name_str
		    = output_script__var (GS_string ("declare_obj_inst_ref (\"")
		    + inst_var_name_str + "\", \""
		    + result_obj_key_letters_str + "\")");
		inst_var_ptr = new I_object_inst_ref_var ();
		inst_var_ptr->set_last_resort_key_letters_str
		    (result_obj_key_letters_str);
		GS_stack::push_var (inst_var_ptr, inst_var_name_str,
		    result_var_frag_name_str);
		is_implicitly_declared = "TRUE";
	    }
	}
	else
	{
	    GS_var_si* inst_set_var_si_ptr
		= GS_stack::find_var_si_ptr (inst_var_name_str);
	    I_object_inst_ref_set_var* inst_set_var_ptr = 0;
	    if (inst_set_var_si_ptr)
	    {
		inst_set_var_ptr
		    = inst_set_var_si_ptr->get_object_inst_ref_set_var_ptr ();
	    }
	    if (inst_set_var_ptr)
	    {
		result_var_frag_name_str
		    = inst_set_var_si_ptr->get_var_frag_name_str ();
	    }
	    else
	    {
		result_var_frag_name_str = output_script__var (GS_string
		    ("declare_obj_inst_ref_set (\"")
		    + inst_var_name_str + "\", \""
		    + result_obj_key_letters_str + "\")");
		inst_set_var_ptr = new I_object_inst_ref_set_var ();
		inst_set_var_ptr->set_last_resort_key_letters_str
		    (result_obj_key_letters_str);
		GS_stack::push_var (inst_set_var_ptr, inst_var_name_str,
		    result_var_frag_name_str);
		is_implicitly_declared = "TRUE";
	    }
	}
	if (condition_str == "")
	{
	    stmt_frag_name_str
		= output_script__stmt (GS_string ("select_related_by (\"")
		+ cardinality_str + "\", "
		+ result_var_frag_name_str + ", "
		+ is_implicitly_declared + ", "
		+ chain_frag_name_str + ")");
	}
	else
	{
	    e_value_type condition_type = VALUE_DATA;
	    GS_string condition_type_parameter_str;
	    GS_string condition_frag_name_str = gen_expr_script
		(condition_str, condition_type, condition_type_parameter_str);
	    if (condition_type != VALUE_DATA)
	    {
		LOG_ERROR ((L_log_string,
		    "GS_gen_action::gen_stmt_script__select ():  condition_type != VALUE_DATA."));
	    }
	    stmt_frag_name_str
		= output_script__stmt (GS_string ("select_related_by (\"")
		+ cardinality_str + "\", "
		+ result_var_frag_name_str + ", "
		+ is_implicitly_declared + ", "
		+ chain_frag_name_str + ", "
		+ condition_frag_name_str + ")");
	}
    }
    else if (related_or_from_str == "FROM")
    {
        //  Parsed statement:
        //    SELECT <card> <inst-ref> FROM INSTANCES OF <object> WHERE <cond>
        //
        GS_string result_obj_key_letters_str
	    (stmt_str.parse_to_keyword ("WHERE"));
        stmt_str.parse_token ();
        GS_string condition_str (stmt_str.parse_to_end ());

	if ((cardinality_str == "ONE") || (cardinality_str == "ANY"))
	{
	    GS_string lower_case_inst_var_name_str (inst_var_name_str);
	    lower_case_inst_var_name_str.convert_to_lower_case ();
	    if (lower_case_inst_var_name_str == "self")
	    {
		GS_ui::inform (UI_INFORM__ERROR, GS_string
		    ("Instance '") + inst_var_name_str
		    + "' NOT allowed to be used as result variable in SELECT statement.");
		return "";
	    }
	    GS_var_si* inst_var_si_ptr
		= GS_stack::find_var_si_ptr (inst_var_name_str);
	    I_object_inst_ref_var* inst_var_ptr = 0;
	    if (inst_var_si_ptr)
	    {
		inst_var_ptr = inst_var_si_ptr->get_object_inst_ref_var_ptr ();
	    }
	    if (inst_var_ptr)
	    {
		result_var_frag_name_str
		    = inst_var_si_ptr->get_var_frag_name_str ();
	    }
	    else
	    {
		result_var_frag_name_str
		    = output_script__var (GS_string ("declare_obj_inst_ref (\"")
		    + inst_var_name_str + "\", \""
		    + result_obj_key_letters_str + "\")");
		inst_var_ptr = new I_object_inst_ref_var ();
		inst_var_ptr->set_last_resort_key_letters_str
		    (result_obj_key_letters_str);
		GS_stack::push_var (inst_var_ptr, inst_var_name_str,
		    result_var_frag_name_str);
		is_implicitly_declared = "TRUE";
	    }
	}
	else
	{
	    GS_var_si* inst_set_var_si_ptr
		= GS_stack::find_var_si_ptr (inst_var_name_str);
	    I_object_inst_ref_set_var* inst_set_var_ptr = 0;
	    if (inst_set_var_si_ptr)
	    {
		inst_set_var_ptr
		    = inst_set_var_si_ptr->get_object_inst_ref_set_var_ptr ();
	    }
	    if (inst_set_var_ptr)
	    {
		result_var_frag_name_str
		    = inst_set_var_si_ptr->get_var_frag_name_str ();
	    }
	    else
	    {
		result_var_frag_name_str = output_script__var (GS_string
		    ("declare_obj_inst_ref_set (\"")
		    + inst_var_name_str + "\", \""
		    + result_obj_key_letters_str + "\")");
		inst_set_var_ptr = new I_object_inst_ref_set_var ();
		inst_set_var_ptr->set_last_resort_key_letters_str
		    (result_obj_key_letters_str);
		GS_stack::push_var (inst_set_var_ptr, inst_var_name_str,
		    result_var_frag_name_str);
		is_implicitly_declared = "TRUE";
	    }
	}

	if (condition_str == "")
	{
	    stmt_frag_name_str = output_script__stmt (GS_string
		("select_from_instances_of (\"")
		+ cardinality_str + "\", "
		+ result_var_frag_name_str + ", "
		+ is_implicitly_declared + ", \""
		+ result_obj_key_letters_str + "\")");
	}
	else
	{
	    e_value_type condition_type = VALUE_DATA;
	    GS_string condition_type_parameter_str;
	    GS_string condition_frag_name_str = gen_expr_script
		(condition_str, condition_type, condition_type_parameter_str);
	    if (condition_type != VALUE_DATA)
	    {
		LOG_ERROR ((L_log_string,
		    "GS_gen_action::gen_stmt_script__select ():  condition_type != VALUE_DATA."));
	    }
	    stmt_frag_name_str = output_script__stmt (GS_string
		("select_from_instances_of (\"")
		+ cardinality_str + "\", "
		+ result_var_frag_name_str + ", "
		+ is_implicitly_declared + ", \""
		+ result_obj_key_letters_str + "\", "
		+ condition_frag_name_str + ")");
	}
    }


    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
        "End  GS_gen_action::gen_stmt_script__select ()."));
    return stmt_frag_name_str;
}





GS_string
GS_gen_action::gen_stmt_script__for
    (const GS_string& p_stmt_str, const GS_string& p_for_blck_str)

{
    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_BEGIN, (L_log_string,
        "Begin  GS_gen_action::gen_stmt_script__for (p_stmt_str=\"%s\", p_for_blck_str=\"%s\").",
        p_stmt_str.char_ptr (), p_for_blck_str.char_ptr ()));


    GS_string stmt_str = p_stmt_str;
    
    
    GS_string for_keyword_str (stmt_str.parse_token ());
    for_keyword_str.convert_to_upper_case ();
    if (for_keyword_str != "FOR")
    {
	GS_ui::inform (UI_INFORM__ERROR, GS_string
	    ("Expected keyword 'FOR' at beginning of Statement in Statement Block  --->")
	    + p_stmt_str + "<----");
    }
    GS_string each_keyword_str (stmt_str.parse_token ());
    each_keyword_str.convert_to_upper_case ();
    if (each_keyword_str != "EACH")
    {
	GS_ui::inform (UI_INFORM__ERROR, GS_string
	    ("Expected keyword 'EACH' in 'FOR' Statement in Statement Block  --->")
	    + p_stmt_str + "<----");
    }
    GS_string inst_var_name_str (stmt_str.parse_token ());
    GS_string in_keyword_str (stmt_str.parse_token ());
    in_keyword_str.convert_to_upper_case ();
    if (in_keyword_str != "IN")
    {
	GS_ui::inform (UI_INFORM__ERROR, GS_string
	    ("Expected keyword 'IN' in 'FOR' Statement in Statement Block  --->")
	    + p_stmt_str + "<----");
    }


    GS_string inst_set_var_name_str (stmt_str.parse_token ());
    GS_string inst_set_var_frag_name_str;
    GS_var_si* inst_set_var_si_ptr
	= GS_stack::find_var_si_ptr (inst_set_var_name_str);
    I_object_inst_ref_set_var* inst_set_var_ptr = 0;
    if (inst_set_var_si_ptr)
    {
	inst_set_var_ptr
	    = inst_set_var_si_ptr->get_object_inst_ref_set_var_ptr ();
    }
    if (inst_set_var_ptr)
    {
	inst_set_var_frag_name_str
	    = inst_set_var_si_ptr->get_var_frag_name_str ();
    }
    else
    {
	GS_ui::inform (UI_INFORM__ERROR, GS_string
	    ("Instance Set '") + inst_set_var_name_str
	    + "' NOT defined");
	return "";
    }
    
    
    GS_string lower_case_inst_var_name_str (inst_var_name_str);
    lower_case_inst_var_name_str.convert_to_lower_case ();
    if (lower_case_inst_var_name_str == "self")
    {
	GS_ui::inform (UI_INFORM__ERROR, GS_string
	    ("Instance '") + inst_var_name_str
	    + "' NOT allowed to be used as iterator in FOR statement.");
	return "";
    }
    GS_string is_implicitly_declared ("FALSE");
    GS_string inst_var_frag_name_str;
    GS_var_si* inst_var_si_ptr
	= GS_stack::find_var_si_ptr (inst_var_name_str);
    I_object_inst_ref_var* inst_var_ptr = 0;
    if (inst_var_si_ptr)
    {
	inst_var_ptr = inst_var_si_ptr->get_object_inst_ref_var_ptr ();
    }
    if (inst_var_ptr)
    {
	inst_var_frag_name_str
	    = inst_var_si_ptr->get_var_frag_name_str ();
    }
    else
    {
	inst_var_frag_name_str
	    = output_script__var (GS_string ("declare_obj_inst_ref (\"")
	    + inst_var_name_str + "\", \""
	    + inst_set_var_ptr->get_key_letters_str () + "\")");
	inst_var_ptr = new I_object_inst_ref_var ();
	inst_var_ptr->set_last_resort_key_letters_str
	    (inst_set_var_ptr->get_key_letters_str ());
	GS_stack::push_var (inst_var_ptr, inst_var_name_str,
	    inst_var_frag_name_str);
	is_implicitly_declared = "TRUE";
    }


    GS_gen_action for_blck_action (p_for_blck_str);
    GS_string for_blck_frag_name_str
	= for_blck_action.gen_blck_script (BLCK_FOR);
    GS_string for_stmt_frag_name_str
	(output_script__stmt (GS_string ("for (")
        + inst_var_frag_name_str + ", "
	+ is_implicitly_declared + ", "
        + inst_set_var_frag_name_str + ", "
	+ for_blck_frag_name_str + ")"));


    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
        "End  GS_gen_action::gen_stmt_script__for ()."));
    return for_stmt_frag_name_str;
}





GS_string
GS_gen_action::gen_stmt_script__create_obj (const GS_string& p_stmt_str)

{
    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_BEGIN, (L_log_string,
        "Begin  GS_gen_action::gen_stmt_script__create_obj (p_stmt_str=\"%s\").",
        p_stmt_str.char_ptr ()));


    GS_string stmt_str = p_stmt_str;
    
    
    GS_string create_keyword_str (stmt_str.parse_token ());
    create_keyword_str.convert_to_upper_case ();
    if (create_keyword_str != "CREATE")
    {
	GS_ui::inform (UI_INFORM__ERROR, GS_string
	    ("Expected keyword 'CREATE' in Statement --->")
	    + p_stmt_str + "<----");
    }
    GS_string obj_keyword_str (stmt_str.parse_token ());
    obj_keyword_str.convert_to_upper_case ();
    if (obj_keyword_str != "OBJECT")
    {
	GS_ui::inform (UI_INFORM__ERROR, GS_string
	    ("Expected keyword 'OBJECT' in Statement --->")
	    + p_stmt_str + "<----");
    }
    GS_string instance_keyword_str (stmt_str.parse_token ());
    instance_keyword_str.convert_to_upper_case ();
    if (instance_keyword_str != "INSTANCE")
    {
	GS_ui::inform (UI_INFORM__ERROR, GS_string
	    ("Expected keyword 'INSTANCE' in Statement --->")
	    + p_stmt_str + "<----");
    }
    GS_string inst_var_name_str (stmt_str.parse_token ());
    GS_string of_keyword_str (inst_var_name_str);
    of_keyword_str.convert_to_upper_case ();
    if (of_keyword_str == "OF")
    {
	inst_var_name_str = "";
    }
    else
    {
	of_keyword_str = stmt_str.parse_token ();
	of_keyword_str.convert_to_upper_case ();
	if (of_keyword_str != "OF")
	{
	    GS_ui::inform (UI_INFORM__ERROR, GS_string
		("Expected keyword 'OF' in Statement --->")
		+ p_stmt_str + "<----");
	}
    }
    GS_string obj_key_letters_str (stmt_str.parse_token ());


    GS_string frag_name_str;
    if (inst_var_name_str == "")
    {
	frag_name_str = output_script__stmt (GS_string
	    ("create_obj_inst_no_var (\"")
	    + obj_key_letters_str + "\")");
    }
    else
    {
	GS_string lower_case_inst_var_name_str (inst_var_name_str);
	lower_case_inst_var_name_str.convert_to_lower_case ();
	if (lower_case_inst_var_name_str == "self")
	{
	    GS_ui::inform (UI_INFORM__ERROR, GS_string
		("Instance '") + inst_var_name_str
		+ "' NOT allowed to be used in CREATE statement.");
	    return "";
	}

	GS_string is_implicitly_declared ("FALSE");
	GS_string inst_var_frag_name_str;
	GS_var_si* inst_var_si_ptr
	    = GS_stack::find_var_si_ptr (inst_var_name_str);
	I_object_inst_ref_var* inst_var_ptr = 0;
	if (inst_var_si_ptr)
	{
	    inst_var_ptr = inst_var_si_ptr->get_object_inst_ref_var_ptr ();
	}
	if (inst_var_ptr)
	{
	    inst_var_frag_name_str
		= inst_var_si_ptr->get_var_frag_name_str ();
	}
	else
	{
	    inst_var_frag_name_str
		= output_script__var (GS_string ("declare_obj_inst_ref (\"")
		+ inst_var_name_str + "\", \""
		+ obj_key_letters_str + "\")");
	    inst_var_ptr = new I_object_inst_ref_var ();
	    inst_var_ptr->set_last_resort_key_letters_str
		(obj_key_letters_str);
	    GS_stack::push_var (inst_var_ptr, inst_var_name_str,
		inst_var_frag_name_str);
	    is_implicitly_declared = "TRUE";
	}

	frag_name_str = output_script__stmt (GS_string ("create_obj_inst (")
	    + inst_var_frag_name_str + ", "
	    + is_implicitly_declared + ", \""
	    + obj_key_letters_str + "\")");
    }


    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
        "End  GS_gen_action::gen_stmt_script__create_obj ()."));
    return frag_name_str;
}





GS_string
GS_gen_action::gen_stmt_script__delete (const GS_string& p_stmt_str)

{
    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_BEGIN, (L_log_string,
        "Begin  GS_gen_action::gen_stmt_script__delete (p_stmt_str=\"%s\").",
        p_stmt_str.char_ptr ()));


    GS_string stmt_str = p_stmt_str;
    
    
    GS_string delete_keyword_str (stmt_str.parse_token ());
    delete_keyword_str.convert_to_upper_case ();
    if (delete_keyword_str != "DELETE")
    {
	GS_ui::inform (UI_INFORM__ERROR, GS_string
	    ("Expected keyword 'DELETE' in Statement --->")
	    + p_stmt_str + "<----");
    }
    GS_string obj_keyword_str (stmt_str.parse_token ());
    obj_keyword_str.convert_to_upper_case ();
    if (obj_keyword_str != "OBJECT")
    {
	GS_ui::inform (UI_INFORM__ERROR, GS_string
	    ("Expected keyword 'OBJECT' in Statement --->")
	    + p_stmt_str + "<----");
    }
    GS_string instance_keyword_str (stmt_str.parse_token ());
    instance_keyword_str.convert_to_upper_case ();
    if (instance_keyword_str != "INSTANCE")
    {
	GS_ui::inform (UI_INFORM__ERROR, GS_string
	    ("Expected keyword 'INSTANCE' in Statement --->")
	    + p_stmt_str + "<----");
    }


    GS_string inst_var_name_str (stmt_str.parse_token ());
    GS_string lower_case_inst_var_name_str (inst_var_name_str);
    lower_case_inst_var_name_str.convert_to_lower_case ();
    if (lower_case_inst_var_name_str == "self")
    {
	GS_ui::inform (UI_INFORM__ERROR, GS_string
	    ("Instance '") + inst_var_name_str
	    + "' NOT allowed to be used in DELETE statement.");
	return "";
    }


    GS_string inst_var_frag_name_str;
    GS_var_si* inst_var_si_ptr
	= GS_stack::find_var_si_ptr (inst_var_name_str);
    I_object_inst_ref_var* inst_var_ptr = 0;
    if (inst_var_si_ptr)
    {
	inst_var_ptr = inst_var_si_ptr->get_object_inst_ref_var_ptr ();
    }
    if (inst_var_ptr)
    {
	inst_var_frag_name_str
	    = inst_var_si_ptr->get_var_frag_name_str ();
    }
    else
    {
	GS_ui::inform (UI_INFORM__ERROR, GS_string
	    ("Instance '") + inst_var_name_str + "' NOT defined");
	return "";
    }
    
    
    GS_string frag_name_str
	= output_script__stmt (GS_string ("delete_obj_inst (")
        + inst_var_frag_name_str + ")");


    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
        "End  GS_gen_action::gen_stmt_script__delete ()."));
    return frag_name_str;
}





GS_string
GS_gen_action::gen_stmt_script__relate (const GS_string& p_stmt_str)

{
    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_BEGIN, (L_log_string,
        "Begin  GS_gen_action::gen_stmt_script__relate (p_stmt_str=\"%s\").",
        p_stmt_str.char_ptr ()));


    GS_string stmt_str = p_stmt_str;
    
    
    GS_string relate_keyword_str (stmt_str.parse_token ());
    relate_keyword_str.convert_to_upper_case ();
    if (relate_keyword_str != "RELATE")
    {
	GS_ui::inform (UI_INFORM__ERROR, GS_string
	    ("Expected keyword 'RELATE' in Statement --->")
	    + p_stmt_str + "<----");
    }
    GS_string inst_var1_name_str (stmt_str.parse_token ());
    GS_string to_keyword_str (stmt_str.parse_token ());
    to_keyword_str.convert_to_upper_case ();
    if (to_keyword_str != "TO")
    {
	GS_ui::inform (UI_INFORM__ERROR, GS_string
	    ("Expected keyword 'TO' in Statement --->")
	    + p_stmt_str + "<----");
    }
    GS_string inst_var2_name_str (stmt_str.parse_token ());
    GS_string across_keyword_str (stmt_str.parse_token ());
    across_keyword_str.convert_to_upper_case ();
    if (across_keyword_str != "ACROSS")
    {
	GS_ui::inform (UI_INFORM__ERROR, GS_string
	    ("Expected keyword 'ACROSS' in Statement --->")
	    + p_stmt_str + "<----");
    }


    // We must check to see if relationship spec contains an optional phrase.
    // eg - "...across R1.'next';". DES

    GS_string rel_phrase;    // null unless we find one
    t_uint char_num = stmt_str.cursor ();
    GS_string rel_number_str (stmt_str.parse_token ('.'));

    // if '.' was found, then the "stmt_str" cursor is sitting on the '.'
    // and rel_number_str contains the R# string; otherwise the cursor is
    // at the end of "stmt_str", so we must reset it back and then parse
    // out the rel_number_str again.
    if (stmt_str.curr_char () == '.')
    {
	// Relationship phrase present. Go ahead and extract it. At this
	// point, rel_number_str contains the R# string.
	stmt_str.parse_token( '\'' );
	stmt_str++;
	rel_phrase = stmt_str.parse_token( '\'' );
	stmt_str++;   // leave after last tick in case USING clause follows.
    }
    else
    {
        // No relationship phrase present. Reset cursor and get rel number.
        stmt_str.reset_cursor (char_num);
        rel_number_str = stmt_str.parse_token ();
    }

    t_uint rel_number = 0;
    if (sscanf ((&(rel_number_str [1])), "%u", &rel_number) != 1)
    {
	GS_ui::inform (UI_INFORM__ERROR, GS_string
	    ("Relationship Number Malformed - Expected  'R#' where # is a positive integer --->")
	    + rel_number_str + "<----");
	return "";
    }


    stmt_str.consume_white_space ();
    GS_string assoc_inst_var_name_str;
    if (stmt_str.cursor () < stmt_str.length ())
    {
        GS_string using_keyword_str (stmt_str.parse_token ());
	using_keyword_str.convert_to_upper_case ();
	if (using_keyword_str != "USING")
	{
	    GS_ui::inform (UI_INFORM__ERROR, GS_string
		("Expected keyword 'USING' in Statement --->")
		+ p_stmt_str + "<----");
	}
        assoc_inst_var_name_str = stmt_str.parse_token ();
    }


    GS_string lower_case_inst_var1_name_str (inst_var1_name_str);
    lower_case_inst_var1_name_str.convert_to_lower_case ();
    if (lower_case_inst_var1_name_str == "self")
    {
	inst_var1_name_str = lower_case_inst_var1_name_str;
    }
    GS_string inst_var1_frag_name_str;
    GS_var_si* inst_var1_si_ptr
	= GS_stack::find_var_si_ptr (inst_var1_name_str);
    I_object_inst_ref_var* inst_var1_ptr = 0;
    if (inst_var1_si_ptr)
    {
	inst_var1_ptr = inst_var1_si_ptr->get_object_inst_ref_var_ptr ();
    }
    if (inst_var1_ptr)
    {
	inst_var1_frag_name_str
	    = inst_var1_si_ptr->get_var_frag_name_str ();
    }
    else
    {
	GS_ui::inform (UI_INFORM__ERROR, GS_string
	    ("Instance '") + inst_var1_name_str + "' NOT defined");
	return "";
    }


    GS_string lower_case_inst_var2_name_str (inst_var2_name_str);
    lower_case_inst_var2_name_str.convert_to_lower_case ();
    if (lower_case_inst_var2_name_str == "self")
    {
	inst_var2_name_str = lower_case_inst_var2_name_str;
    }
    GS_string inst_var2_frag_name_str;
    GS_var_si* inst_var2_si_ptr
	= GS_stack::find_var_si_ptr (inst_var2_name_str);
    I_object_inst_ref_var* inst_var2_ptr = 0;
    if (inst_var2_si_ptr)
    {
	inst_var2_ptr = inst_var2_si_ptr->get_object_inst_ref_var_ptr ();
    }
    if (inst_var2_ptr)
    {
	inst_var2_frag_name_str
	    = inst_var2_si_ptr->get_var_frag_name_str ();
    }
    else
    {
	GS_ui::inform (UI_INFORM__ERROR, GS_string
	    ("Instance '") + inst_var2_name_str + "' NOT defined");
	return "";
    }
    
    
    GS_string frag_name_str;
    if (assoc_inst_var_name_str == "")
    {
        frag_name_str = output_script__stmt (GS_string ("relate (")
            + inst_var1_frag_name_str + ", "
            + inst_var2_frag_name_str + ", "
            + &(rel_number_str [1]) + ", \""
            + rel_phrase + "\")");
    }
    else
    {
	GS_string lower_case_assoc_inst_var_name_str (assoc_inst_var_name_str);
	lower_case_assoc_inst_var_name_str.convert_to_lower_case ();
	if (lower_case_assoc_inst_var_name_str == "self")
	{
	    assoc_inst_var_name_str = lower_case_assoc_inst_var_name_str;
	}
	GS_string assoc_inst_var_frag_name_str;
	GS_var_si* assoc_inst_var_si_ptr
	    = GS_stack::find_var_si_ptr (assoc_inst_var_name_str);
	I_object_inst_ref_var* assoc_inst_var_ptr = 0;
	if (assoc_inst_var_si_ptr)
	{
	    assoc_inst_var_ptr
		= assoc_inst_var_si_ptr->get_object_inst_ref_var_ptr ();
	}
	if (assoc_inst_var_ptr)
	{
	    assoc_inst_var_frag_name_str
		= assoc_inst_var_si_ptr->get_var_frag_name_str ();
	}
	else
	{
	    GS_ui::inform (UI_INFORM__ERROR, GS_string
		("Instance '") + assoc_inst_var_name_str + "' NOT defined");
	    return "";
	}
	
        frag_name_str
	    = output_script__stmt (GS_string ("relate_using (")
            + inst_var1_frag_name_str + ", "
            + inst_var2_frag_name_str + ", " 
            + &(rel_number_str [1]) + ", "
            + assoc_inst_var_frag_name_str + ", \""
            + rel_phrase + "\")");
    }


    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
        "End  GS_gen_action::gen_stmt_script__relate ()."));
    return frag_name_str;
}





GS_string
GS_gen_action::gen_stmt_script__unrelate (const GS_string& p_stmt_str)

{
    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_BEGIN, (L_log_string,
        "Begin  GS_gen_action::gen_stmt_script__unrelate (p_stmt_str=\"%s\").",
        p_stmt_str.char_ptr ()));


    GS_string stmt_str = p_stmt_str;
    
    
    GS_string unrelate_keyword_str (stmt_str.parse_token ());
    unrelate_keyword_str.convert_to_upper_case ();
    if (unrelate_keyword_str != "UNRELATE")
    {
	GS_ui::inform (UI_INFORM__ERROR, GS_string
	    ("Expected keyword 'UNRELATE' in Statement --->")
	    + p_stmt_str + "<----");
    }
    GS_string inst_var1_name_str (stmt_str.parse_token ());
    GS_string from_keyword_str (stmt_str.parse_token ());
    from_keyword_str.convert_to_upper_case ();
    if (from_keyword_str != "FROM")
    {
	GS_ui::inform (UI_INFORM__ERROR, GS_string
	    ("Expected keyword 'FROM' in Statement --->")
	    + p_stmt_str + "<----");
    }
    GS_string inst_var2_name_str (stmt_str.parse_token ());
    GS_string across_keyword_str (stmt_str.parse_token ());
    across_keyword_str.convert_to_upper_case ();
    if (across_keyword_str != "ACROSS")
    {
	GS_ui::inform (UI_INFORM__ERROR, GS_string
	    ("Expected keyword 'ACROSS' in Statement --->")
	    + p_stmt_str + "<----");
    }

    // We must check to see if relationship spec contains an optional phrase.
    // eg - "...across R1.'next';". DES1

    GS_string rel_phrase;    // null unless we find one
    t_uint char_num = stmt_str.cursor ();
    GS_string rel_number_str (stmt_str.parse_token ('.'));

    // if '.' was found, then the "stmt_str" cursor is sitting on the '.'
    // and rel_number_str contains the R# string; otherwise the cursor is
    // at the end of "stmt_str", so we must reset it back and then parse
    // out the rel_number_str again.
    if (stmt_str.curr_char () == '.')
    {
	// Relationship phrase present. Go ahead and extract it. At this
	// point, rel_number_str contains the R# string.
	stmt_str.parse_token( '\'' );
	stmt_str++;
	rel_phrase = stmt_str.parse_token( '\'' );
	stmt_str++;   // leave after last tick in case USING clause follows.
    }
    else
    {
        // No relationship phrase present. Reset cursor and get rel number.
        stmt_str.reset_cursor (char_num);
        rel_number_str = stmt_str.parse_token ();
    }

    t_uint rel_number = 0;
    if (sscanf ((&(rel_number_str [1])), "%u", &rel_number) != 1)
    {
	GS_ui::inform (UI_INFORM__ERROR, GS_string
	    ("Relationship Number Malformed - Expected  'R#' where # is a positive integer --->")
	    + rel_number_str + "<----");
	return "";
    }


    stmt_str.consume_white_space ();
    GS_string assoc_inst_var_name_str;
    if (stmt_str.cursor () < stmt_str.length ())
    {
        GS_string using_keyword_str (stmt_str.parse_token ());
	using_keyword_str.convert_to_upper_case ();
	if (using_keyword_str != "USING")
	{
	    GS_ui::inform (UI_INFORM__ERROR, GS_string
		("Expected keyword 'USING' in Statement --->")
		+ p_stmt_str + "<----");
	}
        assoc_inst_var_name_str = stmt_str.parse_token ();
    }


    GS_string lower_case_inst_var1_name_str (inst_var1_name_str);
    lower_case_inst_var1_name_str.convert_to_lower_case ();
    if (lower_case_inst_var1_name_str == "self")
    {
	inst_var1_name_str = lower_case_inst_var1_name_str;
    }
    GS_string inst_var1_frag_name_str;
    GS_var_si* inst_var1_si_ptr
	= GS_stack::find_var_si_ptr (inst_var1_name_str);
    I_object_inst_ref_var* inst_var1_ptr = 0;
    if (inst_var1_si_ptr)
    {
	inst_var1_ptr = inst_var1_si_ptr->get_object_inst_ref_var_ptr ();
    }
    if (inst_var1_ptr)
    {
	inst_var1_frag_name_str
	    = inst_var1_si_ptr->get_var_frag_name_str ();
    }
    else
    {
	GS_ui::inform (UI_INFORM__ERROR, GS_string
	    ("Instance '") + inst_var1_name_str + "' NOT defined");
	return "";
    }


    GS_string lower_case_inst_var2_name_str (inst_var2_name_str);
    lower_case_inst_var2_name_str.convert_to_lower_case ();
    if (lower_case_inst_var2_name_str == "self")
    {
	inst_var2_name_str = lower_case_inst_var2_name_str;
    }
    GS_string inst_var2_frag_name_str;
    GS_var_si* inst_var2_si_ptr
	= GS_stack::find_var_si_ptr (inst_var2_name_str);
    I_object_inst_ref_var* inst_var2_ptr = 0;
    if (inst_var2_si_ptr)
    {
	inst_var2_ptr = inst_var2_si_ptr->get_object_inst_ref_var_ptr ();
    }
    if (inst_var2_ptr)
    {
	inst_var2_frag_name_str
	    = inst_var2_si_ptr->get_var_frag_name_str ();
    }
    else
    {
	GS_ui::inform (UI_INFORM__ERROR, GS_string
	    ("Instance '") + inst_var2_name_str + "' NOT defined");
	return "";
    }


    GS_string frag_name_str;
    if (assoc_inst_var_name_str == "")
    {
        frag_name_str = output_script__stmt (GS_string ("unrelate (")
            + inst_var1_frag_name_str + ", "
            + inst_var2_frag_name_str + ", "
            + &(rel_number_str [1]) + ", \""
            + rel_phrase + "\")");
    }
    else
    {
	GS_string lower_case_assoc_inst_var_name_str (assoc_inst_var_name_str);
	lower_case_assoc_inst_var_name_str.convert_to_lower_case ();
	if (lower_case_assoc_inst_var_name_str == "self")
	{
	    assoc_inst_var_name_str = lower_case_assoc_inst_var_name_str;
	}
	GS_string assoc_inst_var_frag_name_str;
	GS_var_si* assoc_inst_var_si_ptr
	    = GS_stack::find_var_si_ptr (assoc_inst_var_name_str);
	I_object_inst_ref_var* assoc_inst_var_ptr = 0;
	if (assoc_inst_var_si_ptr)
	{
	    assoc_inst_var_ptr
		= assoc_inst_var_si_ptr->get_object_inst_ref_var_ptr ();
	}
	if (assoc_inst_var_ptr)
	{
	    assoc_inst_var_frag_name_str
		= assoc_inst_var_si_ptr->get_var_frag_name_str ();
	}
	else
	{
	    GS_ui::inform (UI_INFORM__ERROR, GS_string
		("Instance '") + assoc_inst_var_name_str + "' NOT defined");
	    return "";
	}

        frag_name_str
	    = output_script__stmt (GS_string ("unrelate_using (")
	    + inst_var1_frag_name_str + ", "
            + inst_var2_frag_name_str + ", " 
            + &(rel_number_str [1]) + ", "
            + assoc_inst_var_frag_name_str + ", \""
            + rel_phrase + "\")");
    }


    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
        "End  GS_gen_action::gen_stmt_script__unrelate ()."));
    return frag_name_str;
}





GS_string
GS_gen_action::gen_stmt_script__generate (const GS_string& p_stmt_str)

{
    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_BEGIN, (L_log_string,
        "Begin  GS_gen_action::gen_stmt_script__generate (p_stmt_str=\"%s\").",
        p_stmt_str.char_ptr ()));


    GS_string stmt_str = p_stmt_str;
    
    
    GS_string generate_keyword_str (stmt_str.parse_token ());
    generate_keyword_str.convert_to_upper_case ();
    if (generate_keyword_str != "GENERATE")
    {
	GS_ui::inform (UI_INFORM__ERROR, GS_string
	    ("Expected keyword 'GENERATE' in Statement --->")
	    + p_stmt_str + "<----");
	return "";
    }


    GS_string stmt_frag_name_str;

    GS_string event_label_str (stmt_str.parse_token (':',
	GS_string::GS_IGNORE_WITHIN_TICKS |
	GS_string::GS_IGNORE_REPEATED_TICKS_WITHIN_TICKS |
	GS_string::GS_IGNORE_WITHIN_QUOTES |
	GS_string::GS_IGNORE_REPEATED_QUOTES_WITHIN_QUOTES)); 


    //  If we didn't find the ':', then event_label_str contains the event
    //    instance var.
    //
    if (stmt_str.curr_char () != ':')
    {
        //  This is indeed a "GENERATE <event_inst_rvalue>;" statement.
	//    This rvalue must already exist.
	//
	GS_string rval_str = event_label_str.parse_token__rvalue ();
	e_value_type rval_type = VALUE_DATA;
	GS_string rval_type_parameter_str;
	GS_string rval_frag_name_str
	    = gen_rval_script (rval_str, rval_type, rval_type_parameter_str);

	stmt_frag_name_str =
	    output_script__stmt (GS_string ("generate_evt_inst (")
	    + rval_frag_name_str + ")");

        return stmt_frag_name_str;
    }

    stmt_str++;
    GS_string ticked_event_meaning_str (stmt_str.parse_token ('(',
	GS_string::GS_IGNORE_WITHIN_TICKS |
	GS_string::GS_IGNORE_REPEATED_TICKS_WITHIN_TICKS |
	GS_string::GS_IGNORE_WITHIN_QUOTES |
	GS_string::GS_IGNORE_REPEATED_QUOTES_WITHIN_QUOTES)); 


    if (stmt_str != '(')
    {
	GS_ui::inform (UI_INFORM__ERROR, GS_string
	    ("Could not find '(' character for parameters in Statement --->")
	    + stmt_str + "<----");
	return "";
    }
    GS_string params_str (stmt_str.parse_token__parened_str ());


    GS_string to_keyword_str (stmt_str.parse_token ());
    to_keyword_str.convert_to_upper_case ();
    if (to_keyword_str != "TO")
    {
	GS_ui::inform (UI_INFORM__ERROR, GS_string
	    ("Expected keyword 'TO' in Statement --->")
	    + p_stmt_str + "<----");
	return "";
    }


    GS_string inst_var_name_or_key_letters_str (stmt_str.parse_token ());


    if (stmt_str.cursor () >= stmt_str.length ())
    {
	//  This is all of the statement - determine if it is an external entity
	//    event or an event destine to an object instance.
	//
	mc_dbms_Set <I_Object*>* ee_obj_coll_ptr
	    = I_Object::find_Object_by_key_letter (GS_gen_sim_db_ptr, "S_EE");

	if (! ee_obj_coll_ptr)
	{
	    LOG_ERROR ((L_log_string,
		"GS_gen_action::gen_script__generate ():  ee_obj_coll_ptr == 0."));
	    return "";
	}

	if (ee_obj_coll_ptr->cardinality () < 1)
	{
	    GS_ui::inform (UI_INFORM__ERROR,
		"OOA of OOA Object 'S_EE' NOT found in gen DB.");
	    delete ee_obj_coll_ptr;
	    return "";
	}

	if (ee_obj_coll_ptr->cardinality () > 1)
	{
	    LOG_ERROR ((L_log_string,
		"GS_gen_action::gen_script__generate ():  Object Collection resulted in more than one instance! - continuing with one of the instances."));
	    return "";
	}

	I_Object* ee_obj_ptr = ee_obj_coll_ptr->pick ();
	delete ee_obj_coll_ptr;


	mc_dbms_Set <I_Attribute*>* kl_attr_coll_ptr
	    = ee_obj_ptr->find_Attribute_R102_by_name ("Key_Lett");
	if (! kl_attr_coll_ptr)
	{
	    LOG_ERROR ((L_log_string,
		"GS_gen_action::gen_script__generate ():  I_Attribute find return a 0 pointer."));
	    return "";
	}

	if (kl_attr_coll_ptr->cardinality () < 1)
	{
	    delete kl_attr_coll_ptr;
	    kl_attr_coll_ptr
		= ee_obj_ptr->find_Attribute_R102_by_name ("KEY_LETT");
	    if (! kl_attr_coll_ptr)
	    {
		LOG_ERROR ((L_log_string,
		    "GS_gen_action::gen_script__generate ():  I_Attribute find return a 0 pointer."));
		return "";
	    }
	    if (kl_attr_coll_ptr->cardinality () < 1)
	    {
		GS_ui::inform (UI_INFORM__ERROR,
		    "Attribute 'Key_Lett' of object 'S_EE' Not found in gen DB.");
		delete kl_attr_coll_ptr;
		return "";
	    }
	}

	if (kl_attr_coll_ptr->cardinality () > 1)
	{
	    GS_ui::inform (UI_INFORM__ERROR,
		"More than one Attribute 'Key_Lett' of object 'S_EE' found in gen DB.");
	    delete kl_attr_coll_ptr;
	    return "";
	}

	I_Attribute* kl_attr_ptr = kl_attr_coll_ptr->pick ();
	delete kl_attr_coll_ptr;
	if (! kl_attr_ptr)
	{
	    LOG_ERROR ((L_log_string,
		"GS_gen_action::gen_script__generate ():  I_Attribute pointer in collection is 0."));
	    return "";
	}

	mc_dbms_List <I_Attribute_Instance*>* kl_ainst_coll_ptr
	    = kl_attr_ptr->get_Attribute_Instance_R2002_coll_ptr ();
	if (! kl_ainst_coll_ptr)
	{
	    LOG_ERROR ((L_log_string,
		"End  GS_gen_action::gen_script__generate ():  kl_ainst_coll_ptr == 0."));
	    return "";
	}
	t_boolean is_external_entity_event = FALSE;
	I_Attribute_Instance* kl_ainst_ptr = 0;
	FOR_ALL_ELEMENTS_SAFE
	    (kl_ainst_ptr,
	    I_Attribute_Instance,
	    kl_ainst_coll_ptr,
	    kl_ainst_cursor)
	{
	    if (kl_ainst_ptr->get_var_ptr ())
	    {
		if (inst_var_name_or_key_letters_str
		    == kl_ainst_ptr->get_var_ptr ()->get_value_str ())
		{
		    is_external_entity_event = TRUE;
		}
	    }
	}


	if (is_external_entity_event)
	{
	    GS_string begin_param_frag_name_str
		(output_script__param (GS_string ("begin_evt_ext_entity (\"")
		+ event_label_str + "\")"));
	    GS_string added_params_frag_name_str
		(gen_param_script (begin_param_frag_name_str, params_str));
	    GS_string params_frag_name_str
		(output_script__param (GS_string ("end (")
		+ added_params_frag_name_str + ")"));
	    stmt_frag_name_str
		= output_script__stmt (GS_string ("generate_ext_entity (\"")
		+ event_label_str + "\", " 
		+ params_frag_name_str + ", \""
		+ inst_var_name_or_key_letters_str + "\")");
	}
	else
	{
	    GS_string lower_case_inst_var_name_str
		(inst_var_name_or_key_letters_str);
	    lower_case_inst_var_name_str.convert_to_lower_case ();
	    if (lower_case_inst_var_name_str == "self")
	    {
		inst_var_name_or_key_letters_str = lower_case_inst_var_name_str;
	    }
	    GS_string inst_var_frag_name_str;
	    GS_var_si* inst_var_si_ptr = GS_stack::find_var_si_ptr
		(inst_var_name_or_key_letters_str);
	    I_object_inst_ref_var* inst_var_ptr = 0;
	    if (inst_var_si_ptr)
	    {
		inst_var_ptr = inst_var_si_ptr->get_object_inst_ref_var_ptr ();
	    }
	    if (inst_var_ptr)
	    {
		inst_var_frag_name_str
		    = inst_var_si_ptr->get_var_frag_name_str ();
	    }
	    else
	    {
		GS_ui::inform (UI_INFORM__ERROR, GS_string
		    ("Instance '") + inst_var_name_or_key_letters_str
		    + "' NOT defined");
		return "";
	    }

	    GS_string begin_param_frag_name_str
		(output_script__param (GS_string ("begin_evt_obj_inst (\"")
		+ event_label_str + "\")"));
	    GS_string added_params_frag_name_str
		(gen_param_script (begin_param_frag_name_str, params_str));
	    GS_string params_frag_name_str
		(output_script__param (GS_string ("end (")
		+ added_params_frag_name_str + ")"));
	    stmt_frag_name_str
		= output_script__stmt (GS_string ("generate_obj_inst (\"")
		+ event_label_str + "\", " 
		+ params_frag_name_str + ", "
		+ inst_var_frag_name_str + ")");
	}
    }
    else
    {
	GS_string assigner_keyword_str (stmt_str.parse_token ());
	assigner_keyword_str.convert_to_upper_case ();
	if (assigner_keyword_str == "ASSIGNER")
	{
	    GS_string begin_param_frag_name_str
		(output_script__param (GS_string ("begin_evt_assigner (\"")
		+ event_label_str + "\")"));
	    GS_string added_params_frag_name_str
		(gen_param_script (begin_param_frag_name_str, params_str));
	    GS_string params_frag_name_str
		(output_script__param (GS_string ("end (")
		+ added_params_frag_name_str + ")"));
	    stmt_frag_name_str
		= output_script__stmt (GS_string ("generate_assigner (\"")
		+ event_label_str + "\", " 
		+ params_frag_name_str + ", \""
		+ inst_var_name_or_key_letters_str + "\")");
	}
	else if (assigner_keyword_str == "CREATOR")
	{
	    GS_string begin_param_frag_name_str
		(output_script__param (GS_string ("begin_evt_creation (\"")
		+ event_label_str + "\")"));
	    GS_string added_params_frag_name_str
		(gen_param_script (begin_param_frag_name_str, params_str));
	    GS_string params_frag_name_str
		(output_script__param (GS_string ("end (")
		+ added_params_frag_name_str + ")"));
	    stmt_frag_name_str
		= output_script__stmt (GS_string ("generate_creation (\"")
		+ event_label_str + "\", " 
		+ params_frag_name_str + ", \""
		+ inst_var_name_or_key_letters_str + "\")");
	}
	else
	{
	    GS_ui::inform (UI_INFORM__ERROR, GS_string
		("Expected keyword 'ASSIGNER or CREATOR' in Statement --->")
		+ p_stmt_str + "<----");
	    return "";
	}

    }


    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
        "End  GS_gen_action::gen_stmt_script__generate ()."));
    return stmt_frag_name_str;
}





GS_string
GS_gen_action::gen_stmt_script__create_evt (const GS_string& p_stmt_str)

{
    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_BEGIN, (L_log_string,
        "Begin  GS_gen_action::gen_stmt_script__create_evt (p_stmt_str=\"%s\").",
        p_stmt_str.char_ptr ()));


    GS_string stmt_str = p_stmt_str;
    
    
    GS_string create_keyword_str (stmt_str.parse_token ());
    create_keyword_str.convert_to_upper_case ();
    if (create_keyword_str != "CREATE")
    {
	GS_ui::inform (UI_INFORM__ERROR, GS_string
	    ("Expected keyword 'CREATE' in Statement --->")
	    + p_stmt_str + "<----");
	return "";
    }
    GS_string event_keyword_str (stmt_str.parse_token ());
    event_keyword_str.convert_to_upper_case ();
    if (event_keyword_str != "EVENT")
    {
	GS_ui::inform (UI_INFORM__ERROR, GS_string
	    ("Expected keyword 'EVENT' in Statement --->")
	    + p_stmt_str + "<----");
	return "";
    }
    GS_string instance_keyword_str (stmt_str.parse_token ());
    instance_keyword_str.convert_to_upper_case ();
    if (instance_keyword_str != "INSTANCE")
    {
	GS_ui::inform (UI_INFORM__ERROR, GS_string
	    ("Expected keyword 'INSTANCE' in Statement --->")
	    + p_stmt_str + "<----");
	return "";
    }
//    GS_string event_inst_var_name_str (stmt_str.parse_token ());
GS_string event_inst_var_name_str (stmt_str.parse_to_keyword ("OF"));
    GS_string of_keyword_str (stmt_str.parse_token ());
    of_keyword_str.convert_to_upper_case ();
    if (of_keyword_str != "OF")
    {
	GS_ui::inform (UI_INFORM__ERROR, GS_string
	    ("Expected keyword 'OF' in Statement --->")
	    + p_stmt_str + "<----");
	return "";
    }


    GS_string event_label_str (stmt_str.parse_token (':',
	GS_string::GS_IGNORE_WITHIN_TICKS |
	GS_string::GS_IGNORE_REPEATED_TICKS_WITHIN_TICKS |
	GS_string::GS_IGNORE_WITHIN_QUOTES |
	GS_string::GS_IGNORE_REPEATED_QUOTES_WITHIN_QUOTES)); 
    if (stmt_str.curr_char () != ':')
    {
	GS_ui::inform (UI_INFORM__ERROR, GS_string
	    ("Could not find ':' character between label and meaning in Statement --->")
	    + stmt_str + "<----");
	return "";
    }
    stmt_str++;
    GS_string ticked_event_meaning_str (stmt_str.parse_token ('(',
	GS_string::GS_IGNORE_WITHIN_TICKS |
	GS_string::GS_IGNORE_REPEATED_TICKS_WITHIN_TICKS |
	GS_string::GS_IGNORE_WITHIN_QUOTES |
	GS_string::GS_IGNORE_REPEATED_QUOTES_WITHIN_QUOTES)); 


    if (stmt_str != '(')
    {
	GS_ui::inform (UI_INFORM__ERROR, GS_string
	    ("Could not find '(' character for parameters in Statement --->")
	    + stmt_str + "<----");
	return "";
    }
    GS_string params_str (stmt_str.parse_token__parened_str ());


    GS_string to_keyword_str (stmt_str.parse_token ());
    to_keyword_str.convert_to_upper_case ();
    if (to_keyword_str != "TO")
    {
	GS_ui::inform (UI_INFORM__ERROR, GS_string
	    ("Expected keyword 'TO' in Statement --->")
	    + p_stmt_str + "<----");
	return "";
    }


    GS_string is_implicitly_declared ("FALSE");
    GS_string event_inst_var_frag_name_str;
    GS_var_si* event_inst_var_si_ptr
	= GS_stack::find_var_si_ptr (event_inst_var_name_str);
    I_integer_var* event_inst_var_ptr = 0;
    if (event_inst_var_si_ptr)
    {
	event_inst_var_ptr
	    = event_inst_var_si_ptr->get_integer_var_ptr ();
    }
    if (event_inst_var_ptr)
    {
	event_inst_var_frag_name_str
	    = event_inst_var_si_ptr->get_var_frag_name_str ();
    }
    else
    {
	event_inst_var_frag_name_str
	    = output_script__var (GS_string ("declare_evt_inst_ref (\"")
	    + event_inst_var_name_str + "\")");
	event_inst_var_ptr = new I_integer_var ();
	GS_stack::push_var (event_inst_var_ptr, event_inst_var_name_str,
	    event_inst_var_frag_name_str);
	is_implicitly_declared = "TRUE";
    }


    GS_string obj_inst_var_name_str (stmt_str.parse_token ());
    GS_string lower_case_obj_inst_var_name_str (obj_inst_var_name_str);
    lower_case_obj_inst_var_name_str.convert_to_lower_case ();
    if (lower_case_obj_inst_var_name_str == "self")
    {
	obj_inst_var_name_str = lower_case_obj_inst_var_name_str;
    }
    GS_string obj_inst_var_frag_name_str;
    GS_var_si* obj_inst_var_si_ptr = GS_stack::find_var_si_ptr
	(obj_inst_var_name_str);
    I_object_inst_ref_var* obj_inst_var_ptr = 0;
    if (obj_inst_var_si_ptr)
    {
	obj_inst_var_ptr = obj_inst_var_si_ptr->get_object_inst_ref_var_ptr ();
    }
    if (obj_inst_var_ptr)
    {
	obj_inst_var_frag_name_str
	    = obj_inst_var_si_ptr->get_var_frag_name_str ();
    }
    else
    {
	GS_ui::inform (UI_INFORM__ERROR, GS_string
	    ("Instance '") + obj_inst_var_name_str + "' NOT defined");
	return "";
    }


    GS_string begin_param_frag_name_str
	(output_script__param (GS_string ("begin_evt_obj_inst (\"")
	+ event_label_str + "\")"));
    GS_string added_params_frag_name_str
	(gen_param_script (begin_param_frag_name_str, params_str));
    GS_string params_frag_name_str
	(output_script__param (GS_string ("end (")
	+ added_params_frag_name_str + ")"));
    GS_string stmt_frag_name_str
	(output_script__stmt (GS_string ("create_evt_obj_inst (")
	+ event_inst_var_frag_name_str + ", " 
	+ is_implicitly_declared + ", \"" 
	+ event_label_str + "\", " 
	+ params_frag_name_str + ", "
	+ obj_inst_var_frag_name_str + ")"));


    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
        "End  GS_gen_action::gen_stmt_script__create_evt ()."));
    return stmt_frag_name_str;
}





GS_string
GS_gen_action::gen_stmt_script__assign (const GS_string& p_stmt_str)

{
    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_BEGIN, (L_log_string,
        "Begin  GS_gen_action::gen_stmt_script__assign (p_stmt_str=\"%s\").",
        p_stmt_str.char_ptr ()));


    GS_string stmt_str = p_stmt_str;
    
    
    GS_string assign_keyword_str (stmt_str.parse_token ());
    GS_string lvalue_name_str (stmt_str.parse_token ('=',
	GS_string::GS_IGNORE_WITHIN_TICKS |
	GS_string::GS_IGNORE_REPEATED_TICKS_WITHIN_TICKS |
	GS_string::GS_IGNORE_WITHIN_QUOTES |
	GS_string::GS_IGNORE_REPEATED_QUOTES_WITHIN_QUOTES)); 
    if (stmt_str.curr_char () != '=')
    {
	GS_ui::inform (UI_INFORM__ERROR, GS_string
	    ("Could not find '=' character in Statement  --->")
	    + stmt_str + "<----");
	return "";
    }


    stmt_str++;
    GS_string expr_str (stmt_str.parse_token (';',
          GS_string::GS_IGNORE_WITHIN_TICKS
	| GS_string::GS_IGNORE_REPEATED_TICKS_WITHIN_TICKS
	| GS_string::GS_IGNORE_WITHIN_QUOTES
	| GS_string::GS_IGNORE_REPEATED_QUOTES_WITHIN_QUOTES));


    e_value_type rvalue_type = VALUE_DATA;
    GS_string rvalue_type_parameter_str;
    GS_string expr_frag_name_str
	= gen_expr_script (expr_str, rvalue_type, rvalue_type_parameter_str);
    
    
    GS_string inst_var_name_str (lvalue_name_str.parse_token ('.',
	GS_string::GS_IGNORE_WITHIN_TICKS |
	GS_string::GS_IGNORE_REPEATED_TICKS_WITHIN_TICKS |
	GS_string::GS_IGNORE_WITHIN_QUOTES |
	GS_string::GS_IGNORE_REPEATED_QUOTES_WITHIN_QUOTES)); 
    GS_string frag_name_str;
    if (lvalue_name_str == '.')
    {
        lvalue_name_str++;
        GS_string attr_name_str (lvalue_name_str.parse_token ());

	GS_string lower_case_inst_var_name_str (inst_var_name_str);
	lower_case_inst_var_name_str.convert_to_lower_case ();
	if (lower_case_inst_var_name_str == "self")
	{
	    inst_var_name_str = lower_case_inst_var_name_str;
	}
	GS_string inst_var_frag_name_str;
	GS_var_si* inst_var_si_ptr = GS_stack::find_var_si_ptr
	    (inst_var_name_str);
	I_object_inst_ref_var* inst_var_ptr = 0;
	if (inst_var_si_ptr)
	{
	    inst_var_ptr = inst_var_si_ptr->get_object_inst_ref_var_ptr ();
	}
	if (inst_var_ptr)
	{
	    if (rvalue_type != VALUE_DATA)
	    {
		LOG_ERROR ((L_log_string,
		    "GS_gen_action::gen_stmt_script__assign ():  rvalue_type != VALUE_DATA for reassignment of object attribute."));
	    }
	    inst_var_frag_name_str
		= inst_var_si_ptr->get_var_frag_name_str ();
	}
	else
	{
	    GS_ui::inform (UI_INFORM__ERROR, GS_string
		("Instance '") + inst_var_name_str + "' NOT defined");
	    return "";
	}

        frag_name_str
	    = output_script__stmt (GS_string ("assign_obj_attr (")
            + inst_var_frag_name_str + ", \""
            + attr_name_str + "\", "
            + expr_frag_name_str + ")");
    }
    else
    {
	GS_string is_implicitly_declared ("FALSE");
	GS_string lvalue_frag_name_str;
	GS_var_si* lvalue_var_si_ptr
	    = GS_stack::find_var_si_ptr (lvalue_name_str);

	I_integer_var* lvalue_int_var_ptr = 0;
	I_object_inst_ref_var* lvalue_obj_inst_ref_var_ptr = 0;
	I_object_inst_ref_set_var* lvalue_obj_inst_ref_set_var_ptr = 0;

        //  Need to allow assignment of vars other than integer type -
        //    object_inst_ref and object_inst_ref_set also need to be covered.
        //
	if (lvalue_var_si_ptr)
	{
	    //  lvalue already exists
	    //
	    lvalue_int_var_ptr = lvalue_var_si_ptr->get_integer_var_ptr ();
	    lvalue_obj_inst_ref_var_ptr =
		lvalue_var_si_ptr->get_object_inst_ref_var_ptr ();
	    lvalue_obj_inst_ref_set_var_ptr =
		lvalue_var_si_ptr->get_object_inst_ref_set_var_ptr ();
	    if (lvalue_int_var_ptr)
	    {
		if (rvalue_type != VALUE_DATA)
		{
		    LOG_ERROR ((L_log_string,
			"GS_gen_action::gen_stmt_script__assign ():  rvalue_type != VALUE_DATA for reassignment of stack variable."));
		}
	        lvalue_frag_name_str
		    = lvalue_var_si_ptr->get_var_frag_name_str ();
	    }
	    else if (lvalue_obj_inst_ref_var_ptr)
	    {
		if (rvalue_type != VALUE_OBJ_INST_REF)
		{
		    LOG_ERROR ((L_log_string,
			"GS_gen_action::gen_stmt_script__assign ():  rvalue_type != VALUE_OBJ_INST_REF for reassignment of stack variable."));
		}
	        lvalue_frag_name_str
		    = lvalue_var_si_ptr->get_var_frag_name_str ();
	    }
	    else if (lvalue_obj_inst_ref_set_var_ptr)
	    {
		if (rvalue_type != VALUE_OBJ_INST_REF_SET)
		{
		    LOG_ERROR ((L_log_string,
			"GS_gen_action::gen_stmt_script__assign ():  rvalue_type != VALUE_OBJ_INST_REF_SET for reassignment of stack variable."));
		}
	        lvalue_frag_name_str
		    = lvalue_var_si_ptr->get_var_frag_name_str ();
	    }
	}
	else
	{
	    //  lvalue doesn't exist yet; first time used.
	    // 
	    if (rvalue_type == VALUE_DATA)
	    {
		lvalue_frag_name_str
		    = output_script__var (GS_string ("declare (\"")
		    + lvalue_name_str + "\")");
		lvalue_int_var_ptr = new I_integer_var ();
		GS_stack::push_var (lvalue_int_var_ptr, lvalue_name_str,
		    lvalue_frag_name_str);
	    }
	    else if (rvalue_type == VALUE_OBJ_INST_REF)
	    {
		lvalue_frag_name_str = output_script__var (GS_string
		    ("declare_obj_inst_ref (\"")
		    + lvalue_name_str + "\", \""
		    + rvalue_type_parameter_str + "\")");
		lvalue_obj_inst_ref_var_ptr = new I_object_inst_ref_var ();
		lvalue_obj_inst_ref_var_ptr->set_last_resort_key_letters_str
		    (rvalue_type_parameter_str);
		GS_stack::push_var (lvalue_obj_inst_ref_var_ptr,
		    lvalue_name_str, lvalue_frag_name_str);
	    }
	    else if (rvalue_type == VALUE_OBJ_INST_REF_SET)
	    {
		lvalue_frag_name_str = output_script__var (GS_string
		    ("declare_obj_inst_ref_set (\"")
		    + lvalue_name_str + "\", \""
		    + rvalue_type_parameter_str + "\")");
		lvalue_obj_inst_ref_set_var_ptr = new I_object_inst_ref_set_var ();
		lvalue_obj_inst_ref_set_var_ptr->set_last_resort_key_letters_str
		    (rvalue_type_parameter_str);
		GS_stack::push_var (lvalue_obj_inst_ref_set_var_ptr,
		    lvalue_name_str, lvalue_frag_name_str);
	    }
	    else
	    {
		LOG_ERROR ((L_log_string,
		    "GS_gen_action::gen_stmt_script__assign ():  rvalue_type not recognized - treating it like VALUE_DATA."));
		lvalue_frag_name_str
		    = output_script__var (GS_string ("declare (\"")
		    + lvalue_name_str + "\")");
		lvalue_int_var_ptr = new I_integer_var ();
		GS_stack::push_var (lvalue_int_var_ptr, lvalue_name_str,
		    lvalue_frag_name_str);
	    }
	    is_implicitly_declared = "TRUE";
	}

        frag_name_str
	    = output_script__stmt (GS_string ("assign_transient_var (")
            + lvalue_frag_name_str + ", "
            + is_implicitly_declared + ", "
            + expr_frag_name_str + ")");
    }


    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
        "End  GS_gen_action::gen_stmt_script__assign ()."));
    return frag_name_str;
}





GS_string
GS_gen_action::gen_stmt_script__transform (const GS_string& p_stmt_str)

{
    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_BEGIN, (L_log_string,
        "Begin  GS_gen_action::gen_stmt_script__transform (p_stmt_str=\"%s\").",
        p_stmt_str.char_ptr ()));


    GS_string stmt_str = p_stmt_str;
    
    
    GS_string transform_keyword_str (stmt_str.parse_token ());
    t_uint char_num = stmt_str.cursor ();
    GS_string lvalue_name_str (stmt_str.parse_token ('=',
          GS_string::GS_IGNORE_WITHIN_TICKS
	| GS_string::GS_IGNORE_REPEATED_TICKS_WITHIN_TICKS
	| GS_string::GS_IGNORE_WITHIN_QUOTES
	| GS_string::GS_IGNORE_REPEATED_QUOTES_WITHIN_QUOTES));
    if (stmt_str == '=')
    {
        stmt_str++;
    }
    else
    {
        stmt_str.reset_cursor (char_num);
        lvalue_name_str = "";
    }
    GS_string obj_key_letters_str (stmt_str.parse_token ("::"));
    if (stmt_str.curr_char () != ':')
    {
	GS_ui::inform (UI_INFORM__ERROR, GS_string
	    ("Could not find '::' character in Statement  --->")
	    + stmt_str + "<----");
	return "";
    }
    stmt_str++;
    if (stmt_str.curr_char () != ':')
    {
	GS_ui::inform (UI_INFORM__ERROR, GS_string
	    ("Could not find '::' character in Statement  --->")
	    + stmt_str + "<----");
	return "";
    }
    stmt_str++;
    GS_string method_name_str (stmt_str.parse_token ('(',
	GS_string::GS_IGNORE_WITHIN_TICKS |
	GS_string::GS_IGNORE_REPEATED_TICKS_WITHIN_TICKS |
	GS_string::GS_IGNORE_WITHIN_QUOTES |
	GS_string::GS_IGNORE_REPEATED_QUOTES_WITHIN_QUOTES)); 
    if (stmt_str.curr_char () != '(')
    {
	GS_ui::inform (UI_INFORM__ERROR, GS_string
	    ("Could not find '(' character in Statement  --->")
	    + stmt_str + "<----");
	return "";
    }


    GS_string params_str (stmt_str.parse_token__parened_str ());


    GS_string begin_param_frag_name_str
	= output_script__param (GS_string ("begin_transform (\"")
        + obj_key_letters_str + "\", \""
        + method_name_str + "\")");
    GS_string added_params_frag_name_str
	(gen_param_script (begin_param_frag_name_str, params_str));
    GS_string params_frag_name_str
	(output_script__param (GS_string ("end (")
	+ added_params_frag_name_str + ")"));
    
    
    GS_string frag_name_str;
    if (lvalue_name_str == "")
    {
	frag_name_str
	    = output_script__stmt (GS_string ("transform_void (\"")
            + obj_key_letters_str + "\", \""
            + method_name_str + "\", "
            + params_frag_name_str + ")");
    }
    else
    {
        GS_string transform_frag_name_str
            (output_script__rval (GS_string ("transform (\"")
            + obj_key_letters_str + "\", \""
            + method_name_str + "\", "
            + params_frag_name_str + ")"));
        GS_string inst_var_name_str (lvalue_name_str.parse_token ('.',
	    GS_string::GS_IGNORE_WITHIN_TICKS |
	    GS_string::GS_IGNORE_REPEATED_TICKS_WITHIN_TICKS |
	    GS_string::GS_IGNORE_WITHIN_QUOTES |
	    GS_string::GS_IGNORE_REPEATED_QUOTES_WITHIN_QUOTES)); 
        if (lvalue_name_str == '.')
        {
            lvalue_name_str++;
            GS_string attr_name_str (lvalue_name_str.parse_token ());

	    GS_string lower_case_inst_var_name_str (inst_var_name_str);
	    lower_case_inst_var_name_str.convert_to_lower_case ();
	    if (lower_case_inst_var_name_str == "self")
	    {
		inst_var_name_str = lower_case_inst_var_name_str;
	    }
	    GS_string inst_var_frag_name_str;
	    GS_var_si* inst_var_si_ptr = GS_stack::find_var_si_ptr
		(inst_var_name_str);
	    I_object_inst_ref_var* inst_var_ptr = 0;
	    if (inst_var_si_ptr)
	    {
		inst_var_ptr = inst_var_si_ptr->get_object_inst_ref_var_ptr ();
	    }
	    if (inst_var_ptr)
	    {
		inst_var_frag_name_str
		    = inst_var_si_ptr->get_var_frag_name_str ();
	    }
	    else
	    {
		GS_ui::inform (UI_INFORM__ERROR, GS_string
		    ("Instance '") + inst_var_name_str
		    + "' NOT defined");
		return "";
	    }

	    frag_name_str
		= output_script__stmt (GS_string ("assign_obj_attr (")
                + inst_var_frag_name_str + ", \""
                + attr_name_str + "\", "
                + transform_frag_name_str + ")");
        }
        else
        {
	    GS_string is_implicitly_declared ("FALSE");
	    GS_string lvalue_frag_name_str;
	    GS_var_si* lvalue_var_si_ptr
		= GS_stack::find_var_si_ptr (lvalue_name_str);
	    I_var* lvalue_var_ptr = 0;
	    if (lvalue_var_si_ptr)
	    {
		if (method_name_str == "find_inst")
		{
		    lvalue_var_ptr
			= lvalue_var_si_ptr->get_object_inst_ref_var_ptr ();
		}
		else if (method_name_str == "find_inst_set")
		{
		    lvalue_var_ptr
			= lvalue_var_si_ptr->get_object_inst_ref_set_var_ptr ();
		}
		else
		{
		    lvalue_var_ptr = lvalue_var_si_ptr->get_integer_var_ptr ();
		}
	    }
	    if (lvalue_var_ptr)
	    {
		lvalue_frag_name_str
		    = lvalue_var_si_ptr->get_var_frag_name_str ();
	    }
	    else
	    {
		lvalue_frag_name_str
		    = output_script__var (GS_string ("declare (\"")
		    + lvalue_name_str + "\")");
		if (method_name_str == "find_inst")
		{
		    I_object_inst_ref_var* inst_ref_var_ptr
			= new I_object_inst_ref_var ();
		    inst_ref_var_ptr->set_last_resort_key_letters_str
			("____UNKNOWN____");
		    lvalue_var_ptr = inst_ref_var_ptr;
		}
		else if (method_name_str == "find_inst_set")
		{
		    I_object_inst_ref_set_var* inst_ref_set_var_ptr
			= new I_object_inst_ref_set_var ();
		    inst_ref_set_var_ptr->set_last_resort_key_letters_str
			("____UNKNOWN____");
		    lvalue_var_ptr = inst_ref_set_var_ptr;
		}
		else
		{
		    lvalue_var_ptr = new I_integer_var ();
		}
		GS_stack::push_var (lvalue_var_ptr, lvalue_name_str,
		    lvalue_frag_name_str);
		is_implicitly_declared = "TRUE";
	    }

	    frag_name_str
		= output_script__stmt (GS_string ("assign_transient_var (")
                + lvalue_frag_name_str + ", "
		+ is_implicitly_declared + ", "
                + transform_frag_name_str + ")");
        }
    }


    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
        "End  GS_gen_action::gen_stmt_script__transform ()."));
    return frag_name_str;
}





GS_string
GS_gen_action::gen_stmt_script__if
    (const GS_string& p_stmt_str, const GS_string& p_if_blck_str)

{
    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_BEGIN, (L_log_string,
        "Begin  GS_gen_action::gen_stmt_script__if (p_stmt_str=\"%s\", p_if_blck_str=\"%s\").",
        p_stmt_str.char_ptr (), p_if_blck_str.char_ptr ()));


    GS_string stmt_str = p_stmt_str;
    
    
    GS_string if_keyword_str (stmt_str.parse_token ('(',
	GS_string::GS_IGNORE_WITHIN_TICKS |
	GS_string::GS_IGNORE_REPEATED_TICKS_WITHIN_TICKS |
	GS_string::GS_IGNORE_WITHIN_QUOTES |
	GS_string::GS_IGNORE_REPEATED_QUOTES_WITHIN_QUOTES)); 
    if (stmt_str.curr_char () != '(')
    {
	GS_ui::inform (UI_INFORM__ERROR, GS_string
	    ("Could not find '(' character in Statement  --->")
	    + stmt_str + "<----");
	return "";
    }
    stmt_str++;
    GS_string condition_str (stmt_str.parse_token (')',
	GS_string::GS_IGNORE_WITHIN_TICKS |
	GS_string::GS_IGNORE_REPEATED_TICKS_WITHIN_TICKS |
	GS_string::GS_IGNORE_WITHIN_QUOTES |
	GS_string::GS_IGNORE_REPEATED_QUOTES_WITHIN_QUOTES)); 
    if (stmt_str.curr_char () != ')')
    {
	GS_ui::inform (UI_INFORM__ERROR, GS_string
	    ("Could not find ')' character in Statement  --->")
	    + stmt_str + "<----");
	return "";
    }


    e_value_type condition_type = VALUE_DATA;
    GS_string condition_type_parameter_str;
    GS_string condition_frag_name_str = gen_expr_script
	(condition_str, condition_type, condition_type_parameter_str);
    if (condition_type != VALUE_DATA)
    {
	LOG_ERROR ((L_log_string,
	    "GS_gen_action::gen_stmt_script__select ():  condition_type != VALUE_DATA."));
    }
    GS_gen_action if_blck_action (p_if_blck_str);
    GS_string if_blck_frag_name_str (if_blck_action.gen_blck_script (BLCK_IF));
    GS_string if_stmt_frag_name_str (output_script__stmt (GS_string
	("if (")
	+ condition_frag_name_str + ", "
	+ if_blck_frag_name_str + ")"));
    
    
    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
        "End  GS_gen_action::gen_stmt_script__if ()."));
    return if_stmt_frag_name_str;
}





GS_string
GS_gen_action::gen_stmt_script__else (const GS_string& p_else_blck_str)

{
    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_BEGIN, (L_log_string,
        "Begin  GS_gen_action::gen_stmt_script__else (p_else_blck_str=\"%s\").",
        p_else_blck_str.char_ptr ()));


    GS_gen_action else_blck_action (p_else_blck_str);
    GS_string else_blck_frag_name_str
	(else_blck_action.gen_blck_script (BLCK_IF));
    GS_string else_stmt_frag_name_str = output_script__stmt (GS_string
	("else (")
	+ else_blck_frag_name_str + ")");


    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	"End  GS_gen_action::gen_stmt_script__else ()."));
    return else_stmt_frag_name_str;
}





GS_string
GS_gen_action::gen_stmt_script__bridge (const GS_string& p_stmt_str)

{
    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_BEGIN, (L_log_string,
        "Begin  GS_gen_action::gen_stmt_script__bridge (p_stmt_str=\"%s\").",
        p_stmt_str.char_ptr ()));


    GS_string stmt_str = p_stmt_str;
    
    
    GS_string bridge_keyword_str (stmt_str.parse_token ());
    t_uint char_num = stmt_str.cursor ();
    GS_string lvalue_name_str (stmt_str.parse_token ('=',
          GS_string::GS_IGNORE_WITHIN_TICKS
	| GS_string::GS_IGNORE_REPEATED_TICKS_WITHIN_TICKS
	| GS_string::GS_IGNORE_WITHIN_QUOTES
	| GS_string::GS_IGNORE_REPEATED_QUOTES_WITHIN_QUOTES));
    if (stmt_str == '=')
    {
        stmt_str++;
    }
    else
    {
        stmt_str.reset_cursor (char_num);
        lvalue_name_str = "";
    }
    GS_string ext_entity_key_letters_str (stmt_str.parse_token ("::"));
    if (stmt_str.curr_char () != ':')
    {
	GS_ui::inform (UI_INFORM__ERROR, GS_string
	    ("Could not find '::' character in Statement  --->")
	    + stmt_str + "<----");
	return "";
    }
    stmt_str++;
    if (stmt_str.curr_char () != ':')
    {
	GS_ui::inform (UI_INFORM__ERROR, GS_string
	    ("Could not find '::' character in Statement  --->")
	    + stmt_str + "<----");
	return "";
    }
    stmt_str++;
    GS_string method_name_str (stmt_str.parse_token ('(',
	GS_string::GS_IGNORE_WITHIN_TICKS |
	GS_string::GS_IGNORE_REPEATED_TICKS_WITHIN_TICKS |
	GS_string::GS_IGNORE_WITHIN_QUOTES |
	GS_string::GS_IGNORE_REPEATED_QUOTES_WITHIN_QUOTES)); 
    if (stmt_str.curr_char () != '(')
    {
	GS_ui::inform (UI_INFORM__ERROR, GS_string
	    ("Could not find '(' character in Statement  --->")
	    + stmt_str + "<----");
	return "";
    }


    GS_string params_str (stmt_str.parse_token__parened_str ());


    GS_string begin_param_frag_name_str
	(output_script__param (GS_string ("begin_bridge (\"")
        + ext_entity_key_letters_str + "\", \""
        + method_name_str + "\")"));
    GS_string added_params_frag_name_str
	(gen_param_script (begin_param_frag_name_str, params_str));
    GS_string params_frag_name_str
	(output_script__param (GS_string ("end (")
	+ added_params_frag_name_str + ")"));
    
    
    GS_string frag_name_str;
    if (lvalue_name_str == "")
    {
	frag_name_str
	    = output_script__stmt (GS_string ("bridge_void (\"")
		+ ext_entity_key_letters_str + "\", \""
		+ method_name_str + "\", "
		+ params_frag_name_str + ")");
    }
    else
    {
        GS_string bridge_frag_name_str
            (output_script__rval (GS_string ("bridge (\"")
            + ext_entity_key_letters_str + "\", \""
            + method_name_str + "\", "
            + params_frag_name_str + ")"));
        GS_string inst_var_name_str (lvalue_name_str.parse_token ('.',
	    GS_string::GS_IGNORE_WITHIN_TICKS |
	    GS_string::GS_IGNORE_REPEATED_TICKS_WITHIN_TICKS |
	    GS_string::GS_IGNORE_WITHIN_QUOTES |
	    GS_string::GS_IGNORE_REPEATED_QUOTES_WITHIN_QUOTES)); 
        if (lvalue_name_str == '.')
        {
            lvalue_name_str++;
            GS_string attr_name_str (lvalue_name_str.parse_token ());

	    GS_string lower_case_inst_var_name_str (inst_var_name_str);
	    lower_case_inst_var_name_str.convert_to_lower_case ();
	    if (lower_case_inst_var_name_str == "self")
	    {
		inst_var_name_str = lower_case_inst_var_name_str;
	    }
	    GS_string inst_var_frag_name_str;
	    GS_var_si* inst_var_si_ptr = GS_stack::find_var_si_ptr
		(inst_var_name_str);
	    I_object_inst_ref_var* inst_var_ptr = 0;
	    if (inst_var_si_ptr)
	    {
		inst_var_ptr = inst_var_si_ptr->get_object_inst_ref_var_ptr ();
	    }
	    if (inst_var_ptr)
	    {
		inst_var_frag_name_str
		    = inst_var_si_ptr->get_var_frag_name_str ();
	    }
	    else
	    {
		GS_ui::inform (UI_INFORM__ERROR, GS_string
		    ("Instance '") + inst_var_name_str + "' NOT defined");
		return "";
	    }

            frag_name_str
		= output_script__stmt (GS_string ("assign_obj_attr (")
		    + inst_var_frag_name_str + ", \""
		    + attr_name_str + "\", "
		    + bridge_frag_name_str + ")");
        }
        else
        {
	    GS_string is_implicitly_declared ("FALSE");
	    GS_string lvalue_frag_name_str;
	    GS_var_si* lvalue_var_si_ptr
		= GS_stack::find_var_si_ptr (lvalue_name_str);
	    I_var* lvalue_var_ptr = 0;
	    if (lvalue_var_si_ptr)
	    {
		if (method_name_str == "find_inst")
		{
		    lvalue_var_ptr
			= lvalue_var_si_ptr->get_object_inst_ref_var_ptr ();
		}
		else if (method_name_str == "find_inst_set")
		{
		    lvalue_var_ptr
			= lvalue_var_si_ptr->get_object_inst_ref_set_var_ptr ();
		}
		else
		{
		    lvalue_var_ptr = lvalue_var_si_ptr->get_integer_var_ptr ();
		}
	    }
	    if (lvalue_var_ptr)
	    {
		lvalue_frag_name_str
		    = lvalue_var_si_ptr->get_var_frag_name_str ();
	    }
	    else
	    {
		lvalue_frag_name_str
		    = output_script__var (GS_string ("declare (\"")
		    + lvalue_name_str + "\")");
		if (method_name_str == "find_inst")
		{
		    I_object_inst_ref_var* inst_ref_var_ptr
			= new I_object_inst_ref_var ();
		    inst_ref_var_ptr->set_last_resort_key_letters_str
			("____UNKNOWN____");
		    lvalue_var_ptr = inst_ref_var_ptr;
		}
		else if (method_name_str == "find_inst_set")
		{
		    I_object_inst_ref_set_var* inst_ref_set_var_ptr
			= new I_object_inst_ref_set_var ();
		    inst_ref_set_var_ptr->set_last_resort_key_letters_str
			("____UNKNOWN____");
		    lvalue_var_ptr = inst_ref_set_var_ptr;
		}
		else
		{
		    lvalue_var_ptr = new I_integer_var ();
		}
		GS_stack::push_var (lvalue_var_ptr, lvalue_name_str,
		    lvalue_frag_name_str);
		is_implicitly_declared = "TRUE";
	    }

            frag_name_str
		= output_script__stmt (GS_string ("assign_transient_var (")
		    + lvalue_frag_name_str + ", "
		    + is_implicitly_declared + ", "
		    + bridge_frag_name_str + ")");
        }
    }


    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
        "End  GS_gen_action::gen_stmt_script__bridge ()."));
    return frag_name_str;
}





GS_string
GS_gen_action::gen_stmt_script__return (const GS_string& p_stmt_str)

{
    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_BEGIN, (L_log_string,
        "Begin  GS_gen_action::gen_stmt_script__return (p_stmt_str=\"%s\").",
        p_stmt_str.char_ptr ()));


    GS_string stmt_str = p_stmt_str;
    
    
    GS_string return_keyword_str (stmt_str.parse_token ());


    GS_string expr_str (stmt_str.parse_token (';',
          GS_string::GS_IGNORE_WITHIN_TICKS
	| GS_string::GS_IGNORE_REPEATED_TICKS_WITHIN_TICKS
	| GS_string::GS_IGNORE_WITHIN_QUOTES
	| GS_string::GS_IGNORE_REPEATED_QUOTES_WITHIN_QUOTES));
    e_value_type rvalue_type = VALUE_DATA;
    GS_string rvalue_type_parameter_str;
    GS_string expr_frag_name_str
	= gen_expr_script (expr_str, rvalue_type, rvalue_type_parameter_str);


    GS_string frag_name_str
	= output_script__stmt (GS_string ("return (")
	+ expr_frag_name_str + ")");


    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
        "End  GS_gen_action::gen_stmt_script__return ()."));
    return frag_name_str;
}





void
GS_gen_action::parse_blck__for
    (GS_string& p_for_stmt_str, GS_string& p_for_blck_str)

{
    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_BEGIN, (L_log_string,
        "Begin  GS_gen_action::parse_blck__for (p_for_stmt_str=\"%s\", p_for_blck_str=\"%s\").",
        p_for_stmt_str.char_ptr (), p_for_blck_str.char_ptr ()));


    //  Parse out the  'FOR <inst_var> IN <inst_set_var>'  from the for
    //    block.
    //
    t_uint for_stmt_begin_char_num = m_action_str.cursor ();
    GS_string for_keyword_str (m_action_str.parse_token ());
    for_keyword_str.convert_to_upper_case ();
    if (for_keyword_str != "FOR")
    {
	GS_ui::inform (UI_INFORM__ERROR, GS_string
	    ("Expected keyword 'FOR' at beginning of Statement in Statement Block  --->")
	    + m_action_str + "<----");
    }
    GS_string each_keyword_str (m_action_str.parse_token ());
    each_keyword_str.convert_to_upper_case ();
    if (each_keyword_str != "EACH")
    {
	GS_ui::inform (UI_INFORM__ERROR, GS_string
	    ("Expected keyword 'EACH' in 'FOR' Statement in Statement Block  --->")
	    + m_action_str + "<----");
    }
    GS_string inst_var_name_str (m_action_str.parse_token ());
    GS_string in_keyword_str (m_action_str.parse_token ());
    in_keyword_str.convert_to_upper_case ();
    if (in_keyword_str != "IN")
    {
	GS_ui::inform (UI_INFORM__ERROR, GS_string
	    ("Expected keyword 'IN' in 'FOR' Statement in Statement Block  --->")
	    + m_action_str + "<----");
    }
    GS_string inst_set_var_name_str (m_action_str.parse_token ());
    t_uint for_stmt_end_char_num = m_action_str.cursor ();


    //  Copy the FOR statement string to the argument.
    //
    t_uint length = for_stmt_end_char_num - for_stmt_begin_char_num + 1;
    p_for_stmt_str.reset (length);
    strncpy ((char*) p_for_stmt_str.char_ptr (),
        &((m_action_str.char_ptr ()) [for_stmt_begin_char_num]), length);
    p_for_stmt_str [length] = '\0';

    
    //  Now parse down to the matching  'END FOR;'.  Be careful not to
    //    pay attention to any FOR statement constructs contained within
    //    this FOR statement construct.
    //
    t_uint for_blck_begin_char_num = m_action_str.cursor ();
    t_uint for_blck_end_char_num = for_blck_begin_char_num;
    t_uint for_stmt_nesting_level = 1;
    t_boolean end_of_action = FALSE;
    do
    {
        if (get_next_stmt ())
        {
	    for_blck_end_char_num = m_action_str.cursor () - 1;
            GS_string stmt_keyword1_str = m_action_str.parse_token ();
            stmt_keyword1_str.convert_to_upper_case ();
            
            
            if (stmt_keyword1_str == "FOR")
            {
                for_stmt_nesting_level++;
            }
            else if (stmt_keyword1_str == "END")
            {
		GS_string stmt_keyword2_str (m_action_str.parse_token (';',
		    GS_string::GS_IGNORE_WITHIN_TICKS |
		    GS_string::GS_IGNORE_REPEATED_TICKS_WITHIN_TICKS |
		    GS_string::GS_IGNORE_WITHIN_QUOTES |
		    GS_string::GS_IGNORE_REPEATED_QUOTES_WITHIN_QUOTES)); 
		stmt_keyword2_str.convert_to_upper_case ();
		if (stmt_keyword2_str == "FOR")
		{
		    for_stmt_nesting_level--;
		}
            }
        }
        else
        {
            end_of_action = TRUE;
        }
    } while ( (! end_of_action) && (for_stmt_nesting_level >= 1));


    if (m_action_str.curr_char () == ';')
    {
	m_action_str++;
    }


    if (end_of_action)
    {
	for_blck_end_char_num = m_action_str.cursor ();
    }


    //  Copy the FOR block string to the argument.
    //
    length = for_blck_end_char_num - for_blck_begin_char_num + 1;
    p_for_blck_str.reset (length);
    strncpy ((char*) p_for_blck_str.char_ptr (),
        &((m_action_str.char_ptr ()) [for_blck_begin_char_num]), length);
    p_for_blck_str [length] = '\0';


    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
        "End  GS_gen_action::parse_blck__for ()."));
}





void
GS_gen_action::parse_blck__if_else (GS_string& p_if_stmt_str,
    GS_string& p_if_blck_str, GS_string& p_else_blck_str)

{
    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_BEGIN, (L_log_string,
        "Begin  GS_gen_action::parse_blck__if_else (p_if_stmt_str=\"%s\", p_if_blck_str\"%s\", p_else_blck_str\"%s\").",
        p_if_stmt_str.char_ptr (),
        p_if_blck_str.char_ptr (), p_else_blck_str.char_ptr ()));


    //  Parse out the  'IF (<condition>)'  from the for block.
    //
    t_uint if_stmt_begin_char_num = m_action_str.cursor ();
    GS_string if_keyword_str (m_action_str.parse_token ('('));
    if_keyword_str.convert_to_upper_case ();
    if (if_keyword_str != "IF")
    {
	GS_ui::inform (UI_INFORM__ERROR, GS_string
	    ("Expected keyword 'IF' at beginning of Statement in Statement Block  --->")
	    + m_action_str + "<----");
    }
    m_action_str.consume_white_space ();
    if (m_action_str != '(')
    {
	GS_ui::inform (UI_INFORM__ERROR, GS_string
	    ("Could not find '(' character to end IF condition in Statement Block  --->")
	    + m_action_str + "<----");
	return;
    }
    GS_string condition_str (m_action_str.parse_token__parened_str ());
    t_uint if_stmt_end_char_num = m_action_str.cursor ();


    //  Copy the IF statement string to the argument.
    //
    t_uint length = if_stmt_end_char_num - if_stmt_begin_char_num + 1;
    p_if_stmt_str.reset (length);
    strncpy ((char*) p_if_stmt_str.char_ptr (),
        &((m_action_str.char_ptr ()) [if_stmt_begin_char_num]), length);
    p_if_stmt_str [length] = '\0';

    
    //  Now parse down to the matching  'ELSE'  or  'END IF;'.  Be careful
    //    not to pay attention to any FOR or other IF statement constructs
    //    contained within this IF statement construct.
    //
    t_uint if_blck_begin_char_num = m_action_str.cursor ();
    t_uint if_blck_end_char_num = if_blck_begin_char_num;
    const t_uint NO_ELSE_BLCK = 999999;
    t_uint else_blck_begin_char_num = NO_ELSE_BLCK;
    t_uint else_blck_end_char_num = NO_ELSE_BLCK;
    t_uint if_stmt_nesting_level = 1;
    t_boolean end_of_action = FALSE;
    do
    {
        if (get_next_stmt ())
        {
	    if (else_blck_begin_char_num == NO_ELSE_BLCK)
	    {
		if_blck_end_char_num = m_action_str.cursor () - 1;
	    }
	    else
	    {
		else_blck_end_char_num = m_action_str.cursor () - 1;
	    }
	    t_uint stmt_begin_cursor = m_action_str.cursor ();
            GS_string stmt_keyword1_str = m_action_str.parse_token ();
            stmt_keyword1_str.convert_to_upper_case ();
	    m_action_str.reset_cursor (stmt_begin_cursor);
            GS_string if_stmt_keyword1_str = m_action_str.parse_token ('(');
	    if_stmt_keyword1_str.convert_to_upper_case ();
	    m_action_str.reset_cursor (stmt_begin_cursor + 1);
            
            
            if (if_stmt_keyword1_str == "IF")
            {
                if_stmt_nesting_level++;
            }
            else if (stmt_keyword1_str == "ELSE")
            {
		if (if_stmt_nesting_level < 2)
		{
		    //  Record the character at the end of the block - begin
		    //    tracking the else blck.
		    //
		    stmt_keyword1_str = m_action_str.parse_token ();
		    else_blck_begin_char_num = m_action_str.cursor ();
		    else_blck_end_char_num = else_blck_begin_char_num;
		}
            }
            else if (stmt_keyword1_str == "END")
            {
		stmt_keyword1_str = m_action_str.parse_token ();
		GS_string stmt_keyword2_str (m_action_str.parse_token (';',
		    GS_string::GS_IGNORE_WITHIN_TICKS |
		    GS_string::GS_IGNORE_REPEATED_TICKS_WITHIN_TICKS |
		    GS_string::GS_IGNORE_WITHIN_QUOTES |
		    GS_string::GS_IGNORE_REPEATED_QUOTES_WITHIN_QUOTES)); 
		stmt_keyword2_str.convert_to_upper_case ();
		if (stmt_keyword2_str == "IF")
		{
		    if_stmt_nesting_level--;
		}
            }
        }
        else
        {
            end_of_action = TRUE;
        }
    } while ( (! end_of_action) && (if_stmt_nesting_level >= 1));


    if (m_action_str.curr_char () == ';')
    {
	m_action_str++;
    }


    if (end_of_action)
    {
	if (else_blck_end_char_num == NO_ELSE_BLCK)
	{
	    if_blck_end_char_num = m_action_str.cursor ();
	}
	else
	{
	    else_blck_end_char_num = m_action_str.cursor ();
	}
    }


    //  Copy the IF block string to the argument.
    //
    length = if_blck_end_char_num - if_blck_begin_char_num + 1;
    p_if_blck_str.reset (length);
    strncpy ((char*) p_if_blck_str.char_ptr (),
        &((m_action_str.char_ptr ()) [if_blck_begin_char_num]), length);
    p_if_blck_str [length] = '\0';


    //  Copy the ELSE block string to the argument.
    //
    if (else_blck_end_char_num == NO_ELSE_BLCK)
    {
        p_else_blck_str.reset (0);
        p_else_blck_str [0] = '\0';
    }
    else
    {
        length = else_blck_end_char_num - else_blck_begin_char_num + 1;
        p_else_blck_str.reset (length);
        strncpy ((char*) p_else_blck_str.char_ptr (),
            &((m_action_str.char_ptr ()) [else_blck_begin_char_num]), length);
        p_else_blck_str [length] = '\0';
    }


    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
        "End  GS_gen_action::parse_blck__if_else ()."));
}





GS_string
GS_gen_action::gen_expr_script (const GS_string& p_expr_str,
    e_value_type& p_rvalue_type, GS_string& p_rvalue_type_parameter_str)

{
    p_rvalue_type = VALUE_DATA;
    p_rvalue_type_parameter_str = "";


    GS_string expr_str (p_expr_str);
    expr_str.consume_white_space ();
    if (expr_str.curr_char () == '(')
    {
	//  Remove '(' from beginning of expression - then check for ')' on
	//    end of expression - remove it.
	//
	expr_str [expr_str.cursor ()] = ' ';
	for (t_uint i = expr_str.length () - 1;
	    ((i >= 0) && (isspace (expr_str [i])));
	    i--);
	if (expr_str [i] == ')')
	{
	    expr_str [i] = ' ';
	}
	else
	{
	    GS_ui::inform (UI_INFORM__ERROR,
		"(Sub)Expression begins with '(' but does not end with ')'.");
	    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		"End #0:  GS_expression::interpret_frag__expression (VOID_DATATYPE):  (Sub)Expression begins with '(' but does not end with ')'."));
	    return "";
	}
    }
    expr_str.reset_cursor ();


    //  Try out the first part of the expression and see if it matches any
    //    UNARY operators.
    //
    GS_string unary_operator_str = expr_str.parse_token__unary_op ();
    if (unary_operator_str == "NOT")
    {
        GS_string rval_str = expr_str.parse_token__rvalue ();
	e_value_type rval_type = VALUE_DATA;
	GS_string rval_type_parameter_str;
	GS_string rval_frag_name_str
	    = gen_rval_script (rval_str, rval_type, rval_type_parameter_str);
    
        GS_string unary_op_frag_name_str
            = output_script__rval (GS_string ("unary_op (\"")
            + unary_operator_str + "\", "
            + rval_frag_name_str + ")");
        return unary_op_frag_name_str;
    }
    else if ((unary_operator_str == "EMPTY")
	|| (unary_operator_str == "NOT_EMPTY")
	|| (unary_operator_str == "CARDINALITY"))
    {
	GS_string var_name_str = expr_str.parse_token__rvalue ();
	GS_string var_frag_name_str;
	GS_var_si* inst_var_si_ptr = GS_stack::find_var_si_ptr (var_name_str);
	I_object_inst_ref_var* inst_var_ptr = 0;
	I_object_inst_ref_set_var* inst_set_var_ptr = 0;
	if (inst_var_si_ptr)
	{
	    inst_var_ptr = inst_var_si_ptr->get_object_inst_ref_var_ptr ();
	    inst_set_var_ptr
		= inst_var_si_ptr->get_object_inst_ref_set_var_ptr ();
	}
	if (inst_var_ptr)
	{
	    var_frag_name_str = inst_var_si_ptr->get_var_frag_name_str ();
	}
	else if (inst_set_var_ptr)
	{
	    var_frag_name_str = inst_var_si_ptr->get_var_frag_name_str ();
	}
	else
	{
	    GS_ui::inform (UI_INFORM__ERROR, GS_string
		("Instance (Set) '") + var_name_str + "' NOT defined");
	    return "";
	}
    
	GS_string unary_op_frag_name_str
	    = output_script__rval (GS_string ("unary_op (\"")
	    + unary_operator_str + "\", "
	    + var_frag_name_str + ")");
	return unary_op_frag_name_str;
    }
    else if ((unary_operator_str == "FIRST")
	|| (unary_operator_str == "NOT_FIRST")
	|| (unary_operator_str == "LAST")
	|| (unary_operator_str == "NOT_LAST"))
    {
	GS_string var_name_str = expr_str.parse_token__rvalue ();
	GS_string var_frag_name_str;
	GS_var_si* inst_set_var_si_ptr
	    = GS_stack::find_var_si_ptr (var_name_str);
	I_object_inst_ref_set_var* inst_set_var_ptr = 0;
	if (inst_set_var_si_ptr)
	{
	    inst_set_var_ptr
		= inst_set_var_si_ptr->get_object_inst_ref_set_var_ptr ();
	}
	if (inst_set_var_ptr)
	{
	    var_frag_name_str = inst_set_var_si_ptr->get_var_frag_name_str ();
	}
	else
	{
	    GS_ui::inform (UI_INFORM__ERROR, GS_string
		("Instance Set '") + var_name_str + "' NOT defined");
	    return "";
	}
    
	GS_string unary_op_frag_name_str
	    = output_script__rval (GS_string ("unary_op (\"")
	    + unary_operator_str + "\", "
	    + var_frag_name_str + ")");
	return unary_op_frag_name_str;
    }
    else if (unary_operator_str != "")
    {
	GS_ui::inform (UI_INFORM__ERROR, GS_string
	    ("Do not recoginze unary operator '")
	    + unary_operator_str + "'.");
	return "";
    }


    //  Expression is NOT a UNARY OPERATION - must be either a stand alone
    //    value or a BINARY expression.
    //
    GS_string rval1_str = expr_str.parse_token__rvalue ();
    e_value_type rval1_type = VALUE_DATA;
    GS_string rval1_type_parameter_str;
    GS_string rval1_frag_name_str
	= gen_rval_script (rval1_str, rval1_type, rval1_type_parameter_str);

    expr_str.consume_white_space ();
    if (expr_str.cursor () >= expr_str.length ())
    {
        //  Expression string is made up of only an rval.
        //
	p_rvalue_type = rval1_type;
	p_rvalue_type_parameter_str = rval1_type_parameter_str;
        return rval1_frag_name_str;
    }

    GS_string binary_operator_str = expr_str.parse_token__binary_op ();

    GS_string rval2_str = expr_str.parse_token__rvalue ();
    e_value_type rval2_type = VALUE_DATA;
    GS_string rval2_type_parameter_str;
    GS_string rval2_frag_name_str
	= gen_rval_script (rval2_str, rval2_type, rval2_type_parameter_str);
    
    GS_string binary_op_frag_name_str
        (output_script__rval (GS_string ("binary_op (")
        + rval1_frag_name_str + ", \""
        + binary_operator_str + "\", "
        + rval2_frag_name_str + ")"));
    return binary_op_frag_name_str;
}





GS_string
GS_gen_action::gen_rval_script (const GS_string& p_rval_str,
    e_value_type& p_rval_type, GS_string& p_rval_type_parameter_str)

{
    p_rval_type = VALUE_DATA;
    p_rval_type_parameter_str = "";


    GS_string rval_str (p_rval_str);
    rval_str.consume_white_space ();
    GS_string upper_case_rval_str (rval_str);
    upper_case_rval_str.convert_to_upper_case ();


    //  An rvalue can be one of the following:
    //
    //    [data_var]
    //    [inst_var].<attr>
    //    <ext_entity>.<data_item>
    //    rcvd_evt.<evt_data_item>
    //    <boolean literal>
    //    <integer literal>
    //    <real literal>
    //    <string literal>
    //


    if ((upper_case_rval_str.length () >= (upper_case_rval_str.cursor () + 8))
	&&
	(strncmp (&(upper_case_rval_str
	    [upper_case_rval_str.cursor ()]), "RCVD_EVT", 8) == 0)
	&&
	((isspace (upper_case_rval_str [upper_case_rval_str.cursor () + 8]))
	    ||
	    (upper_case_rval_str [upper_case_rval_str.cursor () + 8] == '.')))
    {
        //  Value is a received event data item access.
        //
        GS_string rcvd_evt_str (rval_str.parse_token ('.',
	    GS_string::GS_IGNORE_WITHIN_TICKS |
	    GS_string::GS_IGNORE_REPEATED_TICKS_WITHIN_TICKS |
	    GS_string::GS_IGNORE_WITHIN_QUOTES |
	    GS_string::GS_IGNORE_REPEATED_QUOTES_WITHIN_QUOTES)); 
	if (rval_str.curr_char () != '.')
	{
	    GS_ui::inform (UI_INFORM__ERROR, GS_string
		("Could not find '.' character in Rvalue  --->")
		+ rval_str + "<----");
	    return "";
	}
        rval_str++;
        GS_string evt_supp_di_name_str (rval_str.parse_to_end ());
        GS_string rval_frag_name_str (output_script__rval (GS_string
	    ("read_rcvd_evt_di (")
	    + al_inst_var_name_str + ", \""
            + evt_supp_di_name_str + "\")"));
        return rval_frag_name_str;
    }


    if ((upper_case_rval_str.length () >= (upper_case_rval_str.cursor () + 5))
	&&
	(strncmp (&(upper_case_rval_str
	    [upper_case_rval_str.cursor ()]), "PARAM", 5) == 0)
	&&
	((isspace (upper_case_rval_str [upper_case_rval_str.cursor () + 5]))
	    ||
	    (upper_case_rval_str [upper_case_rval_str.cursor () + 5] == '.')))
    {
        //  Value is a parameter data item access.
        //
        GS_string param_str (rval_str.parse_token ('.',
	    GS_string::GS_IGNORE_WITHIN_TICKS |
	    GS_string::GS_IGNORE_REPEATED_TICKS_WITHIN_TICKS |
	    GS_string::GS_IGNORE_WITHIN_QUOTES |
	    GS_string::GS_IGNORE_REPEATED_QUOTES_WITHIN_QUOTES)); 
	if (rval_str.curr_char () != '.')
	{
	    GS_ui::inform (UI_INFORM__ERROR, GS_string
		("Could not find '.' character in Rvalue  --->")
		+ rval_str + "<----");
	    return "";
	}
        rval_str++;
        GS_string param_name_str (rval_str.parse_to_end ());
        GS_string rval_frag_name_str (output_script__rval (GS_string
	    ("read_param (")
	    + al_inst_var_name_str + ", \""
            + param_name_str + "\")"));
        return rval_frag_name_str;
    }


    if ((upper_case_rval_str.length () >= (upper_case_rval_str.cursor () + 4))
	&&
	(strncmp (&(upper_case_rval_str
	    [upper_case_rval_str.cursor ()]), "TRUE", 4) == 0)
	&&
	((upper_case_rval_str.length () == (upper_case_rval_str.cursor () + 4))
	||
	((! (isalnum (upper_case_rval_str [upper_case_rval_str.cursor () + 4])))
	&&
	(upper_case_rval_str [upper_case_rval_str.cursor () + 4] != '_'))))
    {
        GS_string rval_frag_name_str
            (output_script__rval ("literal_boolean (\"TRUE\")"));
        return rval_frag_name_str;
    }


    if ((upper_case_rval_str.length () >= (upper_case_rval_str.cursor () + 5))
	&&
	(strncmp (&(upper_case_rval_str
	    [upper_case_rval_str.cursor ()]), "FALSE", 5) == 0)
	&&
	((upper_case_rval_str.length () == (upper_case_rval_str.cursor () + 5))
	||
	((! (isalnum (upper_case_rval_str [upper_case_rval_str.cursor () + 5])))
	&&
	(upper_case_rval_str [upper_case_rval_str.cursor () + 5] != '_'))))
    {
        GS_string rval_frag_name_str
            (output_script__rval ("literal_boolean (\"FALSE\")"));
        return rval_frag_name_str;
    }


    if (rval_str == '"')
    {
        //  rval is a quoted string.
        //
        GS_string rval_frag_name_str 
            (output_script__rval (GS_string ("literal_string (")
            + rval_str + ")"));
        return rval_frag_name_str;
    }


    if ((rval_str == '-') || (rval_str == '.')
        || (isdigit (rval_str.curr_char ())))
    {
        //  rval is a numeric value.
        //
        t_boolean has_dot = FALSE;
        for (t_uint ii = rval_str.cursor ();
            ii < rval_str.length ();
            ii++)
        {
            if (rval_str [ii] == '.')
            {
                has_dot = TRUE;
            }
        }
        
        if (has_dot)
        {
            GS_string rval_frag_name_str 
                (output_script__rval (GS_string ("literal_real (\"")
                + rval_str + "\")"));
            return rval_frag_name_str;
        }

        GS_string rval_frag_name_str 
            (output_script__rval (GS_string ("literal_integer (\"")
            + rval_str + "\")"));
        return rval_frag_name_str;
    }


    GS_string var_name_str (rval_str.parse_token ('.',
	GS_string::GS_IGNORE_WITHIN_TICKS |
	GS_string::GS_IGNORE_REPEATED_TICKS_WITHIN_TICKS |
	GS_string::GS_IGNORE_WITHIN_QUOTES |
	GS_string::GS_IGNORE_REPEATED_QUOTES_WITHIN_QUOTES)); 
    if (rval_str.curr_char () == '.')
    {
        //  var_name_str holds an instance variable.
        //
        rval_str++;
        GS_string attr_name_str (rval_str.parse_token ());

	GS_string lower_case_inst_var_name_str (var_name_str);
	lower_case_inst_var_name_str.convert_to_lower_case ();
	if (lower_case_inst_var_name_str == "self")
	{
	    var_name_str = lower_case_inst_var_name_str;
	}
	GS_string inst_var_frag_name_str;
	GS_var_si* inst_var_si_ptr
	    = GS_stack::find_var_si_ptr (var_name_str);
	I_object_inst_ref_var* inst_var_ptr = 0;
	if (inst_var_si_ptr)
	{
	    inst_var_ptr = inst_var_si_ptr->get_object_inst_ref_var_ptr ();
	}
	if (inst_var_ptr)
	{
	    inst_var_frag_name_str = inst_var_si_ptr->get_var_frag_name_str ();
	}
	else
	{
	    GS_ui::inform (UI_INFORM__ERROR, GS_string
		("Instance '") + var_name_str + "' NOT defined");
	    return "";
	}
	
        GS_string rval_frag_name_str 
            (output_script__rval (GS_string ("read_obj_attr (")
            + inst_var_frag_name_str + ", \""
            + attr_name_str + "\")"));
        return rval_frag_name_str;
    }


    //  var_name_str holds a reference to a transient variable.
    //
    GS_string var_frag_name_str;
    GS_var_si* var_si_ptr = GS_stack::find_var_si_ptr (var_name_str);
    if (var_si_ptr)
    {
	var_frag_name_str = var_si_ptr->get_var_frag_name_str ();

	I_object_inst_ref_var* lvalue_obj_inst_ref_var_ptr =
	    var_si_ptr->get_object_inst_ref_var_ptr ();
	I_object_inst_ref_set_var* lvalue_obj_inst_ref_set_var_ptr =
	    var_si_ptr->get_object_inst_ref_set_var_ptr ();
	if (lvalue_obj_inst_ref_var_ptr)
	{
	    p_rval_type = VALUE_OBJ_INST_REF;
	    p_rval_type_parameter_str =
		lvalue_obj_inst_ref_var_ptr->get_key_letters_str ();
	}
	else if (lvalue_obj_inst_ref_set_var_ptr)
	{
	    p_rval_type = VALUE_OBJ_INST_REF_SET;
	    p_rval_type_parameter_str =
		lvalue_obj_inst_ref_set_var_ptr->get_key_letters_str ();
	}
    }
    else
    {
	GS_ui::inform (UI_INFORM__ERROR, GS_string
	    ("Variable '") + var_name_str + "' NOT defined");
	return "";
    }
    
    GS_string rval_frag_name_str 
        (output_script__rval (GS_string ("read_transient_var (")
        + var_frag_name_str + ")"));
    return rval_frag_name_str;
}





GS_string
GS_gen_action::gen_chain_script (const GS_string& p_cardinality_str,
    const GS_string& p_chain_str, GS_string& p_result_obj_key_letters_str)

{
    GS_string chain_str (p_chain_str);
    
    
    GS_string begin_var_name_str (chain_str.parse_token ("->",
	GS_string::GS_IGNORE_WITHIN_TICKS |
	GS_string::GS_IGNORE_REPEATED_TICKS_WITHIN_TICKS |
	GS_string::GS_IGNORE_WITHIN_QUOTES |
	GS_string::GS_IGNORE_REPEATED_QUOTES_WITHIN_QUOTES)); 
    GS_string lower_case_begin_var_name_str (begin_var_name_str);
    lower_case_begin_var_name_str.convert_to_lower_case ();
    if (lower_case_begin_var_name_str == "self")
    {
	begin_var_name_str = lower_case_begin_var_name_str;
    }

    GS_string begin_var_frag_name_str;
    GS_var_si* var_si_ptr
	= GS_stack::find_var_si_ptr (begin_var_name_str);
    I_object_inst_ref_var* inst_var_ptr = 0;
    I_object_inst_ref_set_var* inst_set_var_ptr = 0;
    if (var_si_ptr)
    {
	inst_var_ptr = var_si_ptr->get_object_inst_ref_var_ptr ();
	inst_set_var_ptr = var_si_ptr->get_object_inst_ref_set_var_ptr ();
    }
    if (inst_var_ptr)
    {
	begin_var_frag_name_str = var_si_ptr->get_var_frag_name_str ();
    }
    else if (inst_set_var_ptr)
    {
	begin_var_frag_name_str = var_si_ptr->get_var_frag_name_str ();
    }
    else
    {
	GS_ui::inform (UI_INFORM__ERROR,
	    "Instance reference at beginning of chain is NOT defined or is not of type  'inst_ref'  or 'inst_ref_set'");
	return "";
    }
    GS_string begin_chain_frag_name_str
        (output_script__chain (GS_string ("begin (\"")
	+ p_cardinality_str + "\", "
        + begin_var_frag_name_str + ")"));

    
    GS_string prev_link_frag_name_str (begin_chain_frag_name_str);
    while (chain_str.cursor () < chain_str.length ())
    {
        if ((chain_str [chain_str.cursor ()] == '-')
            &&
            (chain_str [chain_str.cursor () + 1] == '>'))
        {
            chain_str++;
            chain_str++;
        }
        GS_string link_str (chain_str.parse_token ("->",
	    GS_string::GS_IGNORE_WITHIN_TICKS |
	    GS_string::GS_IGNORE_REPEATED_TICKS_WITHIN_TICKS |
	    GS_string::GS_IGNORE_WITHIN_QUOTES |
	    GS_string::GS_IGNORE_REPEATED_QUOTES_WITHIN_QUOTES)); 
        GS_string obj_key_letters_str (link_str.parse_token ('[',
	    GS_string::GS_IGNORE_WITHIN_TICKS |
	    GS_string::GS_IGNORE_REPEATED_TICKS_WITHIN_TICKS |
	    GS_string::GS_IGNORE_WITHIN_QUOTES |
	    GS_string::GS_IGNORE_REPEATED_QUOTES_WITHIN_QUOTES)); 
	if (link_str.curr_char () != '[')
	{
	    GS_ui::inform (UI_INFORM__ERROR, GS_string
		("Could not find '[' character in Instance Chain Link  --->")
		+ link_str + "<----");
	    return "";
	}
        link_str++;
        GS_string rel_spec_str (link_str.parse_token (']',
	    GS_string::GS_IGNORE_WITHIN_TICKS |
	    GS_string::GS_IGNORE_REPEATED_TICKS_WITHIN_TICKS |
	    GS_string::GS_IGNORE_WITHIN_QUOTES |
	    GS_string::GS_IGNORE_REPEATED_QUOTES_WITHIN_QUOTES)); 
        GS_string rel_number_str (rel_spec_str.parse_token ('.',
	    GS_string::GS_IGNORE_WITHIN_TICKS |
	    GS_string::GS_IGNORE_REPEATED_TICKS_WITHIN_TICKS |
	    GS_string::GS_IGNORE_WITHIN_QUOTES |
	    GS_string::GS_IGNORE_REPEATED_QUOTES_WITHIN_QUOTES)); 
	t_uint rel_number = 0;
	if (sscanf ((&(rel_number_str [1])), "%u", &rel_number) != 1)
	{
	    GS_ui::inform (UI_INFORM__ERROR, GS_string
		("Relationship Number Malformed - Expected  'R#' where # is a positive integer --->")
		+ rel_number_str + "<----");
	    return "";
	}
        GS_string rel_phrase_str;
        if (rel_spec_str.curr_char () == '.')
        {
            rel_spec_str++;
            rel_phrase_str = rel_spec_str.parse_token__ticked_str ();
        }

        GS_string link_frag_name_str
            (output_script__chain (GS_string ("add_link (")
            + prev_link_frag_name_str + ", \""
            + obj_key_letters_str + "\", "
            + &(rel_number_str [1]) + ", \""
            + rel_phrase_str + "\")"));
            
        prev_link_frag_name_str = link_frag_name_str;
	p_result_obj_key_letters_str = obj_key_letters_str;
        
        chain_str.consume_white_space ();
    }


    GS_string chain_frag_name_str
	(output_script__chain (GS_string ("end (")
	+ prev_link_frag_name_str + ")"));
    
    
    return chain_frag_name_str;
}





GS_string
GS_gen_action::gen_param_script
    (const GS_string& p_param_begin_frag_name_str, const GS_string& p_param_str)

{
    GS_string param_str (p_param_str);
    param_str.consume_white_space ();
    
    
    GS_string prev_param_frag_name_str (p_param_begin_frag_name_str);
    while (param_str.cursor () < param_str.length ())
    {
        GS_string param_name_str (param_str.parse_token (':',
	    GS_string::GS_IGNORE_WITHIN_TICKS |
	    GS_string::GS_IGNORE_REPEATED_TICKS_WITHIN_TICKS |
	    GS_string::GS_IGNORE_WITHIN_QUOTES |
	    GS_string::GS_IGNORE_REPEATED_QUOTES_WITHIN_QUOTES)); 
	if (param_str.curr_char () != ':')
	{
	    GS_ui::inform (UI_INFORM__ERROR, GS_string
		("Could not find ':' character in Parameter List  --->")
		+ param_str + "<----");
	    return "";
	}
        param_str++;
        GS_string rval_str = param_str.parse_token__rvalue ();
	e_value_type rval_type = VALUE_DATA;
	GS_string rval_type_parameter_str;
	GS_string rval_frag_name_str
	    = gen_rval_script (rval_str, rval_type, rval_type_parameter_str);

        GS_string param_frag_name_str
            (output_script__param (GS_string ("add (")
            + prev_param_frag_name_str + ", \""
            + param_name_str + "\", "
            + rval_frag_name_str + ")"));
            
        prev_param_frag_name_str = param_frag_name_str;
        
        param_str.consume_white_space ();
	if (param_str.curr_char () == ',')
	{
	    param_str++;
	    param_str.consume_white_space ();
	}
    }
    
    
    return prev_param_frag_name_str;
}





GS_string
GS_gen_action::output_script__actn (const GS_string& p_method_with_param_str)

{
    char actn_frag_name_char_ptr [20];
    sprintf (actn_frag_name_char_ptr, "a%03d", s_actn_inst_num);
    s_actn_inst_num++;


    GS_string scratch_str (".Invoke ");
    scratch_str += actn_frag_name_char_ptr;
    scratch_str += " = actn_";
    scratch_str += p_method_with_param_str;
    scratch_str += "\n";


    s_script_str += scratch_str;


    return actn_frag_name_char_ptr;
}





GS_string
GS_gen_action::output_script__blck (const GS_string& p_method_with_param_str)

{
    char blck_frag_name_char_ptr [20];
    sprintf (blck_frag_name_char_ptr, "b%03d", s_blck_inst_num);
    s_blck_inst_num++;


    GS_string scratch_str (".Invoke ");
    scratch_str += blck_frag_name_char_ptr;
    scratch_str += " = blck_";
    scratch_str += p_method_with_param_str;
    scratch_str += "\n";


    s_script_str += scratch_str;


    return blck_frag_name_char_ptr;
}





GS_string
GS_gen_action::output_script__stmt (const GS_string& p_method_with_param_str)

{
    char stmt_frag_name_char_ptr [20];
    sprintf (stmt_frag_name_char_ptr, "s%03d", s_stmt_inst_num);
    s_stmt_inst_num++;


    GS_string scratch_str (".Invoke ");
    scratch_str += stmt_frag_name_char_ptr;
    scratch_str += " = stmt_";
    scratch_str += p_method_with_param_str;
    scratch_str += "\n";


    s_script_str += scratch_str;


    return stmt_frag_name_char_ptr;
}





GS_string
GS_gen_action::output_script__rval (const GS_string& p_method_with_param_str)

{
    char rval_frag_name_char_ptr [20];
    sprintf (rval_frag_name_char_ptr, "r%03d", s_rval_inst_num);
    s_rval_inst_num++;


    GS_string scratch_str (".Invoke ");
    scratch_str += rval_frag_name_char_ptr;
    scratch_str += " = rval_";
    scratch_str += p_method_with_param_str;
    scratch_str += "\n";


    s_script_str += scratch_str;


    return rval_frag_name_char_ptr;
}





GS_string
GS_gen_action::output_script__chain (const GS_string& p_method_with_param_str)

{
    char chain_frag_name_char_ptr [20];
    sprintf (chain_frag_name_char_ptr, "c%03d", s_chain_inst_num);
    s_chain_inst_num++;


    GS_string scratch_str (".Invoke ");
    scratch_str += chain_frag_name_char_ptr;
    scratch_str += " = chain_";
    scratch_str += p_method_with_param_str;
    scratch_str += "\n";


    s_script_str += scratch_str;


    return chain_frag_name_char_ptr;
}





GS_string
GS_gen_action::output_script__param (const GS_string& p_method_with_param_str)

{
    char params_frag_name_char_ptr [20];
    sprintf (params_frag_name_char_ptr, "p%03d", s_param_inst_num);
    s_param_inst_num++;


    GS_string scratch_str (".Invoke ");
    scratch_str += params_frag_name_char_ptr;
    scratch_str += " = param_";
    scratch_str += p_method_with_param_str;
    scratch_str += "\n";


    s_script_str += scratch_str;


    return params_frag_name_char_ptr;
}





GS_string
GS_gen_action::output_script__var (const GS_string& p_method_with_param_str)

{
    char var_frag_name_char_ptr [20];
    sprintf (var_frag_name_char_ptr, "v%03d", s_var_inst_num);
    s_var_inst_num++;


    GS_string scratch_str (".Invoke ");
    scratch_str += var_frag_name_char_ptr;
    scratch_str += " = var_";
    scratch_str += p_method_with_param_str;
    scratch_str += "\n";


    s_script_str += scratch_str;


    return var_frag_name_char_ptr;
}

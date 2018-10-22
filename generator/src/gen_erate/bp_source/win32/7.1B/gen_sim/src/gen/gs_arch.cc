/*========================================================================
 *
 * File:      $RCSfile: gs_arch.cc,v $
 * Version:   $Revision: 1.12 $
 * Modified:  $Date: 2013/01/10 23:42:42 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#include <vex.h>
#include <vnum.h>

#include <vstdio.h>
#include <vstdlib.h>
#include <iostream.h>
#include <fstream.h>
#include <ctype.h>
#include <vsystypes.h>
#include <vtime.h>

#include <gs_arch.hh>
#include <gs_sub.hh>
#include <gs_expr.hh>
#include <gs_func.hh>
#include <gs_selct.hh>
#include <gs_ui.hh>
#include <gs_stack.hh>
#include <gs_gactn.hh>
#include <gs_crypt.hh>

#include <i_attr.hh>
#include <i_ainst.hh>
#include <i_oinst.hh>
#include <i_relate.hh>

#include <p_swhere.hh>

#include <u_bplic.h>
#include <u_string.hh>
#include <u_trace.hh>
#include <u_report.hh>
#include <u_error.hh>
#include <u_env.hh>

#ifdef WIN32
#include <strstrea.h>
#else
#include <strstream.h>
#endif

#include <mc2020_archetypes.hh>
#include <mc3020_archetypes.hh>

extern "C" {
#include <pt_trans.h>
}

extern bool sourceLicense3020Used;
extern bool binaryLicense3020Used;
extern bool sourceLicense2020Used;
extern bool binaryLicense2020Used;

static Description s_line_str;
static t_uint s_line_cursor;

static void interpret_stmt__create( const Description& );

#define INITIAL_MAX_NUM_ARCH_FILES 128

class open_arch_file_t
{
public:
  static void set_arch_file_open(const GS_string& file_name);

  static t_boolean open_arch_file(const GS_string& file_name);

  static void add_file( istrstream* p_arch_file,
    const GS_string& p_file_name,
    t_boolean p_file_encrypted, char * p_buffer);
    
  static void remove_file(const GS_string& file_name);   // i3159.1.1.1 changed

  static void close_all_arch_files();

  static void rewind_file();

  static t_boolean is_file_open(const GS_string& file_name);

  static istrstream* arch_file()
  { 
    if ( m_current_arch_file != -1)
      return m_open_arch_files[m_current_arch_file].m_arch_file;
    else
      return 0;
  }

  static void goto_eof()
  {
    if ( m_current_arch_file != -1)
    {
      m_open_arch_files[m_current_arch_file].m_arch_file->clear();
      char x;
      while ( ! m_open_arch_files[m_current_arch_file].m_arch_file->eof() )
        *m_open_arch_files[m_current_arch_file].m_arch_file >> x;
    }
  }

  static t_boolean encrypted()
  { 
    if ( m_current_arch_file != -1 )
      return m_open_arch_files[m_current_arch_file].m_file_encrypted;
    else
      return FALSE;
  }

  static void set_script_file(t_boolean p_script_file)
  { 
    if ( m_current_arch_file != -1)
      m_open_arch_files[m_current_arch_file].m_script_file = p_script_file;
  }

  static void set_encrypted(t_boolean p_encrypted)
  { 
    if ( m_current_arch_file != -1)
      m_open_arch_files[m_current_arch_file].m_file_encrypted = p_encrypted;
  }

private:
   static int m_current_arch_file;
   static open_arch_file_t *m_open_arch_files;
   static int m_num_open_arch_files;
   static int m_max_num_open_arch_files;

   istrstream* m_arch_file;
   GS_string m_file_name;
   t_boolean m_file_encrypted;
   t_boolean m_script_file;
   char *m_buffer;
};

open_arch_file_t *open_arch_file_t::m_open_arch_files = 0;
int open_arch_file_t::m_num_open_arch_files = 0;
int open_arch_file_t::m_current_arch_file = -1;
int open_arch_file_t::m_max_num_open_arch_files = INITIAL_MAX_NUM_ARCH_FILES;

Special_Where *G_Special_Where_table = 0;

static const char *default_script_file_name_str = "____actn.arc";

extern t_boolean parser_gen_actn_script (
    GS_action::e_action_home p_action_home,
    GS_var_si* p_inst_var_si_ptr, 
    const GS_string& p_script_file_name_str);


streampos
GS_archetype::get_char_num ()

{
    if (open_arch_file_t::arch_file()->good ())
    {
	return open_arch_file_t::arch_file()->tellg ();
    }

    return 0;
}





t_boolean
GS_archetype::populate_archetype (const GS_string& p_arch_file_name_str,
    long p_number_of_populations, const GS_string& p_gen_file_name_str)

{
    GS_func_def::init ();

    if (! open_arch_file (p_arch_file_name_str))
    {
        return FALSE;
    }


    Description ctrl_stmt_str;
    Description expr_ctrl_stmt_str;
    long curr_population_count = 0;


    ofstream out_file;
    out_file.open ("____file.txt", ios::out);
    if (! out_file.good ())
    {
	GS_ui::inform (UI_INFORM__ERROR,
	    GS_string("Could not open temporary file './____file.txt' for writing."));
	return FALSE;
    }
    

    while (get_next_line ())
    {

	t_boolean is_ctrl_stmt_str = FALSE;
	s_line_str.consume_white_space (s_line_cursor);
	if ((s_line_cursor < s_line_str.length ())
	    && (s_line_str.char_at(s_line_cursor) == '.'))
	{
	    if (((s_line_cursor + 1) < s_line_str.length ())
		&& (s_line_str.char_at(s_line_cursor + 1) != '.'))
	    {
		is_ctrl_stmt_str = TRUE;
	    }
	}


	if (is_ctrl_stmt_str)
	{
	    if (! (((s_line_cursor + 2) < s_line_str.length ())
		&& (s_line_str.char_at(s_line_cursor + 1) == '/')
		&& (s_line_str.char_at(s_line_cursor + 2) == '/')))
	    {
		s_line_str.parse_token (s_line_cursor, ctrl_stmt_str);
		ctrl_stmt_str.convert_to_upper_case ();
		s_line_cursor = 0;
		s_line_str.consume_white_space (s_line_cursor);
		s_line_str.parse_token ('(', s_line_cursor, expr_ctrl_stmt_str);
		expr_ctrl_stmt_str.convert_to_upper_case ();
		s_line_cursor = 0;


	    GS_UI_INFORM_START (UI_INFORM__STMT)
		Description info_msg ("Interpreting --->");
		info_msg += s_line_str;
		info_msg += "<----";
		GS_UI_INFORM_END (UI_INFORM__STMT, info_msg)




		if (ctrl_stmt_str == dot_select)
		{
		    GS_select::interpret_stmt__select (s_line_str);
		}

		else if (ctrl_stmt_str == dot_create)
		{
		    interpret_stmt__create (s_line_str);
		}



		else if (ctrl_stmt_str == dot_for)
		{
            Description for_str;
            s_line_str.parse_token (s_line_cursor, for_str);
		    Description each_str;
            s_line_str.parse_token (s_line_cursor, each_str);
		    each_str.convert_to_upper_case ();
		    if (each_str != each_string)
		    {
			GS_ui::inform (UI_INFORM__ERROR,
			    GS_string("Syntax error in .FOR Statement - missing keyword 'EACH'."));
			for_fast_forward_to_end ();
		    }
		    else
		    {
			Description inst_name_str;
			s_line_str.parse_to_keyword ("IN", s_line_cursor, inst_name_str);
			Description in_str;
            s_line_str.parse_token (s_line_cursor, in_str);
			in_str.convert_to_upper_case ();
			if (in_str != in_string)
			{
			    GS_ui::inform (UI_INFORM__ERROR,
				GS_string("Syntax error in .FOR Statement - missing keyword 'IN'."));
			    for_fast_forward_to_end ();
			}
			else
			{
			    Description inst_set_name_str_vchar;
				s_line_str.parse_token__rvalue (s_line_cursor, inst_set_name_str_vchar);
				char *inst_set_name_str_ASCII = 
					Description::createAsciiFromVchar(inst_set_name_str_vchar.char_ptr());
				GS_string inst_set_name_str(inst_set_name_str_ASCII);
				Description::freeAsciiFromVchar(inst_set_name_str_ASCII);

				GS_var_si inst_set_var_si;
			    GS_expression::interpret_frag__rvalue
					(inst_set_name_str_vchar, inst_set_var_si);
			    I_object_inst_ref_set_var* inst_set_ptr =
				inst_set_var_si.
				    get_object_inst_ref_set_var_ptr ();
			    if (! inst_set_ptr)
			    {
				    Description err_msg ("Instance Set '");
					err_msg += inst_set_name_str.char_ptr();
				    err_msg += "' is undefined.";
				GS_ui::inform (UI_INFORM__ERROR, err_msg);
				for_fast_forward_to_end ();
			    }
			    else
			    {
				if (! GS_stack::for_begin (inst_name_str,
				    inst_set_name_str_vchar, get_char_num (),
				    GS_ui::get_line_num ()))
				{
				    //  No instances to iterate through - skip
				    //    forward to '.END FOR' statement.
				    //
				    GS_UI_INFORM_START (UI_INFORM__STMT)
					Description err_msg ("Object instance reference set '");
					err_msg += inst_set_name_str.char_ptr();
					err_msg += "' is empty - skipping to statement ";
					err_msg += "following corresponding .END FOR.";
				    GS_UI_INFORM_END (UI_INFORM__STMT, err_msg)
				    for_fast_forward_to_end ();
				}
			    }
			}
		    }
		}
		else if (expr_ctrl_stmt_str == dot_while)
		{
		    if (! GS_stack::while_begin (s_line_str,
			get_char_num (), GS_ui::get_line_num ()))
		    {
			//  While condition was false - skip forward to
			//    '.END WHILE' statement.
			//
			while_fast_forward_to_end ();
		    }
		}
		else if (ctrl_stmt_str == dot_break)
		{
		    Description break_str;
            s_line_str.parse_token (s_line_cursor, break_str);
		    Description type_str;
            s_line_str.parse_token (s_line_cursor, type_str);
		    type_str.convert_to_upper_case ();
		    if ((type_str == for_string) || (type_str == for_semi))
		    {
			GS_stack::for_break ();
			for_fast_forward_to_end ();
		    }
		    else if ((type_str == while_string) || (type_str == while_semi))
		    {
			GS_stack::while_break ();
			while_fast_forward_to_end ();
		    }
		    else
		    {
			GS_ui::inform (UI_INFORM__ERROR,
			    GS_string("Syntax error in .BREAK Statement - missing keyword 'FOR' or 'WHILE' - ignoring statement."));
		    }
		}




		else if (ctrl_stmt_str == dot_assign)
		{
		    GS_expression::interpret_stmt__assign (s_line_str);
		}




		else if (expr_ctrl_stmt_str == dot_if)
		{
			// debug code
			//char *line_str_ASCII = Description::createAsciiFromVchar(s_line_str.char_ptr());
			//Description::freeAsciiFromVchar(line_str_ASCII);
			// end debug code

			if (GS_expression::interpret_stmt__if (s_line_str))
		    {
			//  Condition is TRUE - continue interpretation until
			//    the '.ELIF', '.ELSE', or '.END IF' is found.
			//
			GS_stack::if_begin (TRUE);
		    }
		    else
		    {
			//  Condition is FALSE - skip forward until
			//    the '.ELIF', '.ELSE', or '.END IF' is found.
			//
			//  NOTE:  if_fast_forward () leaves the file so that
			//    the next call to get_next_line () will get the
			//    '.ELIF', '.ELSE', or '.END IF'.
			//
			if_fast_forward ();
			GS_stack::if_begin (FALSE);
		    }
		}
		else if (expr_ctrl_stmt_str == dot_elif)
		{
		    if (GS_stack::if_get_condition_result ())
		    {
			//  Immediately previous if statement block was
			//    interpreted - skip forward til '.END IF' found
			//
			if_fast_forward_to_end ();
			GS_stack::if_end ();
		    }
		    else if (GS_stack::if_get_else_encountered ())
		    {
			GS_ui::inform (UI_INFORM__ERROR,
			    GS_string("ELSE  already encountered - move ELIF block before ELSE block - skipping to END IF..."));
			if_fast_forward_to_end ();
			GS_stack::if_end ();
		    }
		    else
		    {
			if (GS_expression::interpret_stmt__elif
			    (s_line_str))
			{
			    //  Condition is TRUE - continue interpretation
			    //    until '.ELIF', '.ELSE', or '.END IF'
			    //    found.
			    //
			    GS_stack::if_set_condition_result (TRUE);
			}
			else
			{
			    //  Condition is FALSE - skip forward until the
			    //    '.ELIF', '.ELSE', or '.END IF' is found
			    //
			    //  NOTE:  if_fast_forward () leaves the file so
			    //    that next call to get_next_line () will
			    //    get the '.ELIF', '.ELSE', or '.END IF'.
			    //
			    GS_stack::if_set_condition_result (FALSE);
			    if_fast_forward ();
			}
		    }
		}
		else if (ctrl_stmt_str == dot_else)
		{
		    Description else_str;
            s_line_str.parse_token (s_line_cursor, else_str);
		    s_line_str.consume_white_space (s_line_cursor);
		    if (s_line_cursor < s_line_str.length ())
		    {
			Description if_str;
            s_line_str.parse_token (s_line_cursor, if_str);
			if_str.convert_to_upper_case ();
			if (if_str == if_string)
			{
			    GS_ui::inform (UI_INFORM__ERROR,
				GS_string("Use  ELIF  rather than  ELSE IF"));
			}
			else
			{
			    GS_ui::inform (UI_INFORM__WARNING,
				GS_string("Characters after  ELSE  ignored."));
			}
		    }

		    if (GS_stack::if_get_condition_result ())
		    {
			//  Immediately previous if statement block was
			//    interpreted - skip forward til '.END IF' is
			//    found.
			//
			if_fast_forward_to_end ();
			GS_stack::if_end ();
		    }
		    else if (GS_stack::if_get_else_encountered ())
		    {
			GS_ui::inform (UI_INFORM__ERROR,
			    GS_string("ELSE  already encountered - can not have 2 ELSE bocks - skipping to END IF..."));
			if_fast_forward_to_end ();
			GS_stack::if_end ();
		    }
		    else
		    {
			GS_stack::if_set_else_encountered (TRUE);
		    }

		    //  No if statement block has been interpretted yet -
		    //    continue interpretation until '.END IF' is found..
		    //    
		}




		else if (ctrl_stmt_str == dot_function)
		{
		    Description function_str;
            s_line_str.parse_token (s_line_cursor, function_str);
		    Description func_name_str_vchar;
            s_line_str.parse_token (s_line_cursor, func_name_str_vchar);
			char *func_name_str_ASCII = 
				Description::createAsciiFromVchar(func_name_str_vchar.char_ptr());
			GS_string func_name_str(func_name_str_ASCII);
			Description::freeAsciiFromVchar(func_name_str_ASCII);
		    if (func_name_str.length() != 0)
		    {
			if (GS_func_def::is_valid_func_name (func_name_str))
			{
			    GS_ui::inform (UI_INFORM__ERROR, GS_string
				("Function '")
				+ func_name_str
				+ "' is already defined.");
			}
			else if (GS_func_def::create_func_def (func_name_str,
			    get_char_num (), GS_ui::get_line_num (),
			    GS_ui::get_name_str ()))
			{
			    t_boolean params_done = FALSE;
			    while ((! params_done) && (get_next_line ()))
			    {
				s_line_str.parse_token (s_line_cursor, ctrl_stmt_str);
				ctrl_stmt_str.convert_to_upper_case ();
				if (ctrl_stmt_str == dot_param)
				{
				    Description param_type_str;
					s_line_str.parse_token (s_line_cursor, param_type_str);
				    param_type_str.convert_to_upper_case ();
				    Description param_name_str_vchar;
					s_line_str.parse_token (s_line_cursor, param_name_str_vchar);
			char *param_name_str_ASCII = 
				Description::createAsciiFromVchar(param_name_str_vchar.char_ptr());
			GS_string param_name_str(param_name_str_ASCII);
			Description::freeAsciiFromVchar(param_name_str_ASCII);
				    if (param_name_str.length() == 0)
				    {
					GS_ui::inform (UI_INFORM__ERROR,
					    GS_string("Parameter name not specified - Statement format is  '.PARAM { INST_REF | INST_REF_SET | FRAG_REF | BOOLEAN | INTEGER | REAL | STRING } <param_name>'."));
				    }
				    else
				    {
					if (param_type_str == inst_ref_string)
					{
					    GS_func_def::add_param_to_func_def
						(func_name_str,
						GS_func_param_def::PARAM_INST_REF,
						param_name_str);
					}
					else if (param_type_str == inst_ref_set_string)
					{
					    GS_func_def::add_param_to_func_def
						(func_name_str,
						GS_func_param_def::PARAM_INST_REF_SET,
						param_name_str);
					}
					else if (param_type_str == frag_ref_string)
					{
					    GS_func_def::add_param_to_func_def
						(func_name_str,
						GS_func_param_def::PARAM_FRAG_REF,
						param_name_str);
					}
					else if (param_type_str == boolean_string)
					{
					    GS_func_def::add_param_to_func_def
						(func_name_str,
						GS_func_param_def::PARAM_BOOLEAN,
						param_name_str);
					}
					else if (param_type_str == integer_string)
					{
					    GS_func_def::add_param_to_func_def
						(func_name_str,
						GS_func_param_def::PARAM_INTEGER,
						param_name_str);
					}
					else if (param_type_str == real_string)
					{
					    GS_func_def::add_param_to_func_def
						(func_name_str,
						GS_func_param_def::PARAM_REAL,
						param_name_str);
					}
					else if (param_type_str == string_string)
					{
					    GS_func_def::add_param_to_func_def
						(func_name_str,
						GS_func_param_def::PARAM_STRING,
						param_name_str);
					}
					else
					{
					    GS_ui::inform (UI_INFORM__ERROR,
						GS_string("Parameter type unknown - Statement format is  '.PARAM { INST_REF | INST_REF_SET | FRAG_REF | BOOLEAN | INTEGER | REAL | STRING } <param_name>'."));
					}
				    }
				}
				else
				{
				    params_done = TRUE;
				}
			    }
			}
		    }
		    else
		    {
			GS_ui::inform (UI_INFORM__ERROR,
			    GS_string("Function name not specified - Statement format is  '.FUNCTION <func_name>'."));
		    }

		    //  Skip over the body of the function.
		    //                    
		    t_boolean found_end = FALSE;
		    s_line_cursor = 0;
		    do
		    {
			Description end_str;
            s_line_str.parse_token (s_line_cursor, end_str);
			end_str.convert_to_upper_case ();
			Description function_str;
            s_line_str.parse_token (s_line_cursor, function_str);
			function_str.convert_to_upper_case ();
			if ((end_str == dot_end)
			    &&
			    ((function_str == function_string)
				|| (function_str == function_semi)))
			{
			    found_end = TRUE;
			}
		    }
		    while ((! found_end) && (get_next_line ()));
		    if (! found_end)
		    {
			GS_ui::inform (UI_INFORM__ERROR,
			    GS_string("END FUNCTION  expected before End Of File."));
		    }
		}
		else if (ctrl_stmt_str == dot_invoke)
		{
		    Description invoke_str;
            s_line_str.parse_token (s_line_cursor, invoke_str);

			Description func_name_str_vchar;
            s_line_str.parse_token ('(', s_line_cursor, func_name_str_vchar);
			char *func_name_str_ASCII = 
				Description::createAsciiFromVchar(func_name_str_vchar.char_ptr());
			GS_string func_name_str(func_name_str_ASCII);
			Description::freeAsciiFromVchar(func_name_str_ASCII);

			GS_string return_frag_name_str
				(func_name_str.parse_token ('=', s_line_cursor));
			t_uint func_name_cursor = 0;
		    if (func_name_str.curr_char() == '=')
		    {
			func_name_str++;
			func_name_str = func_name_str.parse_token ();
		    }
		    if (! GS_func_def::is_valid_func_name (func_name_str))
		    {
			    Description err_msg ("Undefined Function '");
				err_msg += func_name_str.char_ptr();
			    err_msg += "' Invoked.";
				GS_ui::inform (UI_INFORM__ERROR, err_msg);
		    }
		    else
		    {
			if (s_line_str.char_at (s_line_cursor) != '(')
			{
			    GS_ui::inform (UI_INFORM__ERROR,
				GS_string("Syntax of 'INVOKE' command incorrect - correct syntax is:\n\t.INVOKE  <return_frag>  =  <func_name>  (<param>, ...)"));
			}
			else
			{
			    s_line_cursor++;
				t_uint param_set_cursor = 0;
			    Description param_set_str;
                s_line_str.parse_token(')', s_line_cursor, param_set_str, TRUE, TRUE);
//			char *param_set_str_ASCII = 
//				Description::createAsciiFromVchar(param_set_str_vchar.char_ptr());
//			GS_string param_set_str(param_set_str_ASCII);
//			Description::freeAsciiFromVchar(param_set_str_ASCII);
			    if (s_line_str.char_at(s_line_cursor) != ')')
			    {
				GS_ui::inform (UI_INFORM__ERROR,
				    GS_string("Syntax of 'INVOKE' command incorrect - correct syntax is:\n\t.INVOKE  <return_frag>  =  <func_name>  (<param>, ...)"));
			    }
			    else
			    {
				s_line_cursor++;

				t_uint num_formal_params
				    = GS_func_def::get_num_formal_param(func_name_str);
   				GS_var_si *param = 0;
                if ( num_formal_params > 0 )
                {
    				param = new GS_var_si [ num_formal_params ];
                }

                t_boolean too_many_params = FALSE;
				for (t_uint num_params = 0;
				    ((! too_many_params) &&
					(param_set_cursor < param_set_str.length ()));
				    num_params++)
				{
				    if (num_params >= num_formal_params)
				    {
					GS_ui::inform (UI_INFORM__ERROR,
					    GS_string("INVOKE statement has more actual parameters than the called function expects."));
					too_many_params = TRUE;
				    }
				    else
				    {
					Description param_str;
					param_set_str.parse_token (',', param_set_cursor, param_str,
						  TRUE, TRUE);
					if (param_set_str.char_at (param_set_cursor) == ',')
					{
					    param_set_cursor++;
					}

    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_BEGIN, 
	(L_log_string,
	"Debug  Before GS_expression::interpret_frag__rvalue, num_params = %d, addr(param[num_params]) = 0x%x", num_params, &param[num_params]));
					GS_expression::interpret_frag__rvalue
					    (param_str, param [num_params]);
    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_BEGIN, 
	(L_log_string,
	"Debug  After GS_expression::interpret_frag__rvalue, num_params = %d, addr(param[num_params]) = 0x%x", num_params, &param[num_params]));
					if ((! param [num_params].get_var_ptr())
					    ||
					    (param [num_params].get_var_ptr ()->
						get_core_data_type()
						== VOID_DATATYPE))
					{
						Description err_msg ("Unknown actual parameter '");
						err_msg += param_str;
						err_msg += "'.";
					    GS_ui::inform (UI_INFORM__ERROR, err_msg);
					}
				    }
				}
				if (! too_many_params)
				{
				    if (num_params != num_formal_params)
				    {
					GS_ui::inform (UI_INFORM__ERROR,
					    GS_string("INVOKE statement has fewer actual parameters than the called function expects."));
				    }
				    else
				    {
					if (GS_stack::function_begin
					    (get_char_num (),
					    GS_ui::get_line_num (),
					    GS_ui::get_name_str (),
					    return_frag_name_str, func_name_str,
					    param, num_params))
					{
					    if (GS_func_def::is_predefined
						(func_name_str))
					    {
						GS_func_def::exec_predefined
						    (func_name_str);
						streampos return_char_num;
						unsigned int return_line_num;
						GS_string return_arch_file_name_str;
						GS_stack::function_end
						    (&return_char_num,
						    &return_line_num,
						    &return_arch_file_name_str);
					    }
					    else
					    {
						goto_arch_file_line
						    (GS_func_def::get_start_char_num
							(func_name_str),
						    GS_func_def::get_start_line_num
							(func_name_str),
						    GS_func_def::get_arch_file_name_str
							(func_name_str));
					    }
					}
				    }
				}
                if ( param != 0 )
                {
                    delete [] param;
                }
			    }
			}
		    }
		}
		else if (ctrl_stmt_str == dot_param)
		{
		    //  This will be encountered as part of the execution of
		    //    the function rather than the definition of the
		    //    function - just skip it because the info has already
		    //    been processed.
		    //
		}




		else if (ctrl_stmt_str == dot_end)
		{
		    Description end_str;
            s_line_str.parse_token (s_line_cursor, end_str);
		    Description end_type_str;
            s_line_str.parse_token (s_line_cursor, end_type_str);
		    end_type_str.convert_to_upper_case ();
		    if ((end_type_str == for_string) || (end_type_str == for_semi))
		    {
			if (GS_stack::for_rewind ())
			{
			    //  More instances exist to iterate through.
			    //
			    goto_arch_file_line
				(GS_stack::for_get_begin_char_num (),
				 GS_stack::for_get_begin_line_num ());
			}
			else
			{
			    //  NO more instances exist to iterate through -
			    //    do nothing - stack already cleaned up and
			    //    interpreter is already on the correct line.
			    //
			}
		    }
		    else if ((end_type_str == while_string)
			|| (end_type_str == while_semi))
		    {
			if (GS_stack::while_rewind ())
			{
			    //  While condition is still TRUE - iterate again.
			    //
			    goto_arch_file_line
				(GS_stack::while_get_begin_char_num (),
				 GS_stack::while_get_begin_line_num ());
			}
			else
			{
			    //  NO more instances exist to iterate through -
			    //    do nothing - stack already cleaned up and
			    //    interpreter is already on the correct line.
			    //
			}
		    }
		    else if ((end_type_str == if_string) || (end_type_str == if_semi))
		    {
			//  Immediately previous if statement block was
			//    interpreted - finish up.
			//
			GS_stack::if_end ();
		    }
		    else if ((end_type_str == function_string)
			||
			(end_type_str == function_semi))
		    {
			//  This will be encountered as part of the execution of
			//    the function rather than the definition of the
			//    function.
			//
			streampos return_char_num;
			unsigned int return_line_num;
			GS_string return_arch_file_name_str;
			if (GS_stack::function_get_return_frag_ref_var_ptr ())
			{
			    GS_stack::function_end (&return_char_num,
				&return_line_num,
				&return_arch_file_name_str);
			    goto_arch_file_line (return_char_num,
				return_line_num, return_arch_file_name_str);
			}
			else
			{
			    GS_ui::inform (UI_INFORM__ERROR,
				GS_string("END FUNCTION  encountered with no matching  FUNCTION statement."));
			}
		    }
		    else
		    {
			GS_ui::inform (UI_INFORM__ERROR,
			    GS_string("Syntax error in .END Statement - missing keyword 'FOR', 'WHILE', 'IF', or 'FUNCTION'."));
		    }
		}

		
		
		else if (ctrl_stmt_str == dot_include)
		{
		    Description include_str;
            s_line_str.parse_token (s_line_cursor, include_str);
		    s_line_str.consume_white_space (s_line_cursor);
		    Description raw_include_file_name_str_vchar;
			s_line_str.parse_token__quoted_str (s_line_cursor, raw_include_file_name_str_vchar);
		    Description& include_file_name_str_vchar
			= GS_substitution::substitute_string
			    (raw_include_file_name_str_vchar, FALSE);
			char *include_file_name_str_ASCII = 
				Description::createAsciiFromVchar(include_file_name_str_vchar.char_ptr());
			GS_string include_file_name_str(include_file_name_str_ASCII);
			Description::freeAsciiFromVchar(include_file_name_str_ASCII);
		    if (test_open_arch_file (include_file_name_str))
		    {
			GS_stack::include_begin (get_char_num (),
			    GS_ui::get_line_num (), GS_ui::get_name_str (),
			    include_file_name_str);
			goto_arch_file_line (0, 0, include_file_name_str);
		    }
		}
		else if (ctrl_stmt_str == dot_slashes)
		{
		    //  Do not do anything - ignore all text on this line.
		    //
		}
		else if (ctrl_stmt_str == dot_comment)
		{
		    //  Do not do anything - ignore all text on this line.
		    //
		}
		else if (ctrl_stmt_str == dot_log)
		{
		    Description log_str;
            s_line_str.parse_token (s_line_cursor, log_str);
		    Description level_str;
            s_line_str.parse_token (s_line_cursor, level_str);
		    extern t_ui_information_level GS_information_level;
		    if (level_str == stmt_string)
		    {
			GS_information_level = UI_INFORM__STMT;
		    }
		    else if (level_str == comp_string)
		    {
			GS_information_level = UI_INFORM__COMP;
		    }
		    else
		    {
			if (level_str != sys_string)
			{
			    GS_ui::inform (UI_INFORM__WARNING,
				GS_string(".LOG statement expects 2nd argument to be SYS, STMT, or COMP.  Assuming SYS."));
			}
			GS_information_level = UI_INFORM__SYS;
		    }
		}
		else if (ctrl_stmt_str == dot_clear)
		{
		    //  Close the temporary out file - will be reopened  as
		    //    a fresh file later to do the "rewind".
		    //
		    out_file.close ();

		    //  Re-open the temporary file '____file.txt' for the
		    //    next population to occur.
		    //
		    out_file.open ("____file.txt", ios::out);
		    if (! out_file.good ())
		    {
			GS_ui::inform (UI_INFORM__ERROR,
			    GS_string("Could not open temporary file './____file.txt' for writing."));
			return FALSE;
		    }
		}
		else if (ctrl_stmt_str == dot_emit)
		{
		    Description emit_str;
            s_line_str.parse_token (s_line_cursor, emit_str);
		    Description to_str;
            s_line_str.parse_token (s_line_cursor, to_str);
		    to_str.convert_to_upper_case ();
		    Description file_str;
            s_line_str.parse_token (s_line_cursor, file_str);
		    file_str.convert_to_upper_case ();
		    if (to_str != to_string)
		    {
			GS_ui::inform (UI_INFORM__ERROR, GS_string
			    ("Syntax error in '.EMIT TO FILE \"<file-name>\"'")
			    + "Statement - missing keyword 'TO'.");
		    }
		    else if (file_str != file_string)
		    {
			GS_ui::inform (UI_INFORM__ERROR, GS_string
			    ("Syntax error in '.EMIT TO FILE \"<file-name>\"'")
			    + " Statement - missing keyword 'FILE'.");
		    }
		    else
		    {
			//  Get the file name to emit to treat as a string
			//    with substitution variables.
			//
			s_line_str.consume_white_space (s_line_cursor);
			Description in_file_full_path_name_str;
            s_line_str.parse_token__quoted_str (s_line_cursor, in_file_full_path_name_str);
			Description& out_file_full_path_name_str_vchar
			    = GS_substitution::substitute_string
			    (in_file_full_path_name_str, FALSE);
			char *out_file_full_path_name_str_ASCII = 
				Description::createAsciiFromVchar(out_file_full_path_name_str_vchar.char_ptr());
			GS_string out_file_full_path_name_str(out_file_full_path_name_str_ASCII);
			Description::freeAsciiFromVchar(out_file_full_path_name_str_ASCII);


			//  Close the temporary out file - will be reopened  as
			//    a fresh file later to do the "rewind".
			//
			out_file.close ();


			if (((p_number_of_populations == 0)
				||
				(curr_population_count
				    < p_number_of_populations))
			    &&
			    ((p_gen_file_name_str == "")
				||
				(out_file_full_path_name_str
				    == p_gen_file_name_str)))
			{
			    //  Diff the newly created file with the code file
			    //    which was there and replace it if anything has
			    //    changed - otherwise, leave the original file
			    //    alone so the access time is unchanged.
			    //
			    t_boolean did_not_exist_before_this_gen = FALSE; 
			    t_boolean different = FALSE; 
			    ifstream orig_file;
			    ifstream new_file;
			    orig_file.open (out_file_full_path_name_str.char_ptr (),
				ios::nocreate); 
			    if (! orig_file.good ())
			    {
				//  No Action needed - the file does not exist.
				//
				did_not_exist_before_this_gen = TRUE;
			    }
			    else
			    {
				ifstream new_file;
				new_file.open ("____file.txt", ios::nocreate);
				if (! new_file.good ())
				{
				    GS_ui::inform (UI_INFORM__ERROR,
					GS_string("Unable to Open file './____file.txt'."));
				    return FALSE;
				}
				while ((! different)
				    && (! orig_file.eof ()) && (! new_file.eof ()))
				{
				    GS_string orig_line	(GS_ARCHETYPE_FILE_LINE_LENGTH);
				    orig_file.getline((char*)orig_line.char_ptr (),
					GS_ARCHETYPE_FILE_LINE_LENGTH);
				    orig_line.recalc_length ();
				    orig_line.reset_cursor ();
				    GS_string new_line
					(GS_ARCHETYPE_FILE_LINE_LENGTH);
				    new_file.getline ((char*)new_line.char_ptr (),
					GS_ARCHETYPE_FILE_LINE_LENGTH);
				    new_line.recalc_length ();
				    new_line.reset_cursor ();
				    if ((! orig_file.eof ()) && new_file.eof ())
				    {
					//  Orig file reached end but New file
					//    did not reach end - files are
					//    different.
					//
					different = TRUE;
				    }
				    else if
					(orig_file.eof () && (! new_file.eof ()))
				    {
					//  New file reached end but Orig file
					//    did not reach end - files are
					//    different.
					//
					different = TRUE;
				    }
				    else if (orig_line != new_line)
				    {
					different = TRUE;
				    }
				}
				new_file.close ();
			    }
			    orig_file.close ();


			    if (did_not_exist_before_this_gen || different)
			    {
				new_file.open ("____file.txt", ios::nocreate);
				if (! new_file.good ())
				{
				    GS_ui::inform (UI_INFORM__ERROR,
					GS_string("Unable to re-open file './____file.txt'."));
				    return FALSE;
				}

				out_file.open
				    (out_file_full_path_name_str.char_ptr (),
				    ios::out);
				if (! out_file.good ())
				{
				    GS_ui::inform (UI_INFORM__ERROR, GS_string
					("Unable to open file '")
					+ out_file_full_path_name_str
					+ "' for writing.");
				    return FALSE;
				}

			    char copy_line[GS_ARCHETYPE_FILE_LINE_LENGTH+1];
				while (! new_file.eof ())
				{
				    copy_line [0] = '\0';
				    new_file.getline(copy_line,	GS_ARCHETYPE_FILE_LINE_LENGTH);
				    if (! new_file.eof ())
				    {
					out_file << copy_line << endl;
				    }
				    else
				    {
					if (copy_line [0] != '\0')
					{
					    out_file << copy_line << endl;
					}
				    }
				}
				if (did_not_exist_before_this_gen)
				{
				    GS_ui::inform (UI_INFORM__SYS, GS_string
					("File '")
					+ out_file_full_path_name_str
					+ "'  CREATED.");
				}
				else
				{
				    GS_ui::inform (UI_INFORM__SYS, GS_string
					("File '")
					+ out_file_full_path_name_str
					+ "'  REPLACED.");
				}
				out_file.close ();
				new_file.close ();
			    }
			    else
			    {
				GS_ui::inform (UI_INFORM__SYS, GS_string
				    ("File '")
				    + out_file_full_path_name_str
				    + "'  UNCHANGED.");
			    }

			    curr_population_count++;
			}

			//  Re-open the temporary file '____file.txt' for the
			//    next population to occur.
			//
			out_file.open ("____file.txt", ios::out);
			if (! out_file.good ())
			{
			    GS_ui::inform (UI_INFORM__ERROR,
				GS_string("Could not open temporary file './____file.txt' for writing."));
			    return FALSE;
			}
		    }
		}
		else if (ctrl_stmt_str == dot_print)
		{
		    //  Get the message to print and treat as a string
		    //    with substitution variables.
		    //
		    Description print_str;
            s_line_str.parse_token (s_line_cursor, print_str);
		    s_line_str.consume_white_space (s_line_cursor);
		    Description raw_message_str;
			s_line_str.parse_token__quoted_str (s_line_cursor, raw_message_str);
		    Description& out_message_str
			= GS_substitution::substitute_string
			    (raw_message_str, FALSE);

		    GS_ui::inform (UI_INFORM__SYS, out_message_str);
		}
		else if (ctrl_stmt_str == dot_exit)
		{
		    //  Get the exit code.
		    //
		    Description exit_str;
            s_line_str.parse_token (s_line_cursor, exit_str);
		    s_line_str.consume_white_space (s_line_cursor);
		    t_int exit_code = 255;
			t_boolean error_occurred = TRUE;
		    if (s_line_cursor < s_line_str.length ())
		    {
				Description exit_code_str;
                s_line_str.parse_token (s_line_cursor, exit_code_str);
		      vexWITH_HANDLING {
				
				exit_code = vnumParseInt(exit_code_str.char_ptr(), 0);
				error_occurred = FALSE;

				} vexON_EXCEPTION {
				} vexEND_HANDLING;
			if (error_occurred)
			{
			    GS_ui::inform (UI_INFORM__ERROR,
				GS_string("Malformed exit code in .EXIT statement - exiting with exit code = 255."));
			    exit (255);
			}
			    Description err_msg ("Exit with exit code = ");
				err_msg += exit_code_str;
			    err_msg += " as result of .EXIT Statement.";
			GS_ui::inform (UI_INFORM__ERROR, err_msg);
			exit (exit_code);
		    }
		    else
		    {
			GS_ui::inform (UI_INFORM__ERROR,
			    GS_string("Malformed exit code in .EXIT statement - exiting with exit code = 255."));
			exit (255);
		    }
		}




		else if (ctrl_stmt_str == dot_al_xlate)
		{
		    Description al_xlate_str;
            s_line_str.parse_token (s_line_cursor, al_xlate_str);
		    t_boolean error_occurred = FALSE;
		    t_boolean script_only = FALSE;
		    GS_string script_file_name_str;

		    Description type_str;
            s_line_str.parse_token (s_line_cursor, type_str);
		    type_str.convert_to_upper_case ();
		    GS_action::e_action_home action_home = GS_action::NONE;
		    if ((type_str == assigner_sm_string)
			||
			(type_str == assigner_state_string))
		    {
			action_home = GS_action::ASSIGNER_STATE;
		    }
		    else if (type_str == attribute_string)
		    {
			action_home = GS_action::ATTRIBUTE;
		    }
		    else if (type_str == bridge_string)
		    {
			action_home = GS_action::BRIDGE;
		    }
		    else if (type_str == data_type_string)
		    {
			action_home = GS_action::DATA_TYPE;
		    }
		    else if (type_str == ee_event_string)
		    {
			action_home = GS_action::EE_EVENT;
		    }
		    else if ((type_str == instance_sm_string)
			||
			(type_str == instance_state_string))
		    {
			action_home = GS_action::INSTANCE_STATE;
		    }
		    else if (type_str == relationship_string)
		    {
			action_home = GS_action::RELATIONSHIP;
		    }
		    else if (type_str == sm_event_string)
		    {
			action_home = GS_action::SM_EVENT;
		    }
		    else if (type_str == synch_service_string)
		    {
			action_home = GS_action::SYNCH_SERVICE;
		    }
		    else if (type_str == transformer_string)
		    {
			action_home = GS_action::TRANSFORMER;
		    }
		    else
		    {
			GS_ui::inform (UI_INFORM__ERROR,
			    GS_string("Syntax error in .AL_XLATE Statement - missing action home keyword."));
			error_occurred = TRUE;
		    }

		    GS_var_si* inst_var_si_ptr = 0;
		    if (! error_occurred)
		    {
			Description inst_var_name_str;
			s_line_str.parse_to_keyword ("SCRIPT", s_line_cursor, inst_var_name_str);
			inst_var_si_ptr = GS_stack::find_var_si_ptr
			    (inst_var_name_str);
			if (! inst_var_si_ptr)
			{
				Description err_msg ("Unable to find Variable '");
				err_msg += inst_var_name_str;
				err_msg += "' in .AL_XLATE Statement.";
			    GS_ui::inform (UI_INFORM__ERROR, err_msg);
			    error_occurred = TRUE;
			}
		    }

		    if (! error_occurred)
		    {
			if (s_line_cursor < s_line_str.length ())
			{
			    Description script_str;
                s_line_str.parse_token (s_line_cursor, script_str);
			    script_str.convert_to_upper_case ();
			    Description to_str;
                s_line_str.parse_token (s_line_cursor, to_str);
			    to_str.convert_to_upper_case ();
			    Description file_str;
                s_line_str.parse_token (s_line_cursor, file_str);
			    file_str.convert_to_upper_case ();
			    if (script_str != script_string)
			    {
				GS_ui::inform (UI_INFORM__ERROR, GS_string
				    ("Syntax error in '.AL_XLATE <type> <actn-inst-var> SCRIPT TO FILE \"<file-name>\"'")
				    + "Statement - missing keyword 'SCRIPT'.");
				error_occurred = TRUE;
			    }
			    else if (to_str != to_string)
			    {
				GS_ui::inform (UI_INFORM__ERROR, GS_string
				    ("Syntax error in '.AL_XLATE <type> <actn-inst-var> SCRIPT TO FILE \"<file-name>\"'")
				    + "Statement - missing keyword 'TO'.");
				error_occurred = TRUE;
			    }
			    else if (file_str != file_string)
			    {
				GS_ui::inform (UI_INFORM__ERROR, GS_string
				    ("Syntax error in '.AL_XLATE <type> <actn-inst-var> SCRIPT TO FILE \"<file-name>\"'")
				    + " Statement - missing keyword 'FILE'.");
				error_occurred = TRUE;
			    }
			    else
			    {
				//  Get the file name to emit script to -
				//    treat as a string with substitution
				//    variables.
				//
				script_only = TRUE;
				Description raw_script_file_name_str;
				s_line_str.parse_token__quoted_str (s_line_cursor, raw_script_file_name_str);
				Description& script_file_name_str_vchar
				    = GS_substitution::substitute_string
				    (raw_script_file_name_str, FALSE);
				char *script_file_name_str_ASCII = 
					Description::createAsciiFromVchar(script_file_name_str_vchar.char_ptr());
				script_file_name_str = script_file_name_str_ASCII;
				Description::freeAsciiFromVchar(script_file_name_str_ASCII);
			    }
			}
			else
			{
			    script_file_name_str = default_script_file_name_str;

			}
		    }

		    if (! error_occurred)
		    {
			t_boolean parse_script_ok = 
                          parser_gen_actn_script (action_home,
			    inst_var_si_ptr, script_file_name_str);

			if (! script_only)
			{
			    if (parse_script_ok && 
                                  test_open_arch_file (script_file_name_str))
			    {
				GS_stack::include_begin (get_char_num (),
				    GS_ui::get_line_num (), GS_ui::get_name_str (),
				    script_file_name_str);
				goto_arch_file_line (0, 0, script_file_name_str);
				open_arch_file_t::set_script_file(TRUE);
			    }
			}
		    }
		}


		else if (ctrl_stmt_str == dot_special_where)
		{
		    Description special_where_str;
            s_line_str.parse_token (s_line_cursor, special_where_str);

		    Description command_str;
            s_line_str.parse_token (s_line_cursor, command_str);
		    command_str.convert_to_upper_case ();

		    Description where_spec_var_str;
            s_line_str.parse_token (s_line_cursor, where_spec_var_str);
                    GS_var_si* where_spec_si_ptr = 0;

		    s_line_str.consume_white_space (s_line_cursor);
		    if (s_line_cursor < s_line_str.length ())
		    {
                      GS_ui::inform (UI_INFORM__WARNING,
			GS_string("Characters after SPECIAL_WHERE command ignored."));
		    }

		    if ( command_str == add_string )
		    {
                      where_spec_si_ptr = GS_stack::find_var_si_ptr
			    (where_spec_var_str);
		      if (! where_spec_si_ptr)
		      {
			    Description err_msg ("Unable to find Variable '");
				err_msg += where_spec_var_str;
				err_msg += "' in .SPECIAL_WHERE Statement.";
				GS_ui::inform (UI_INFORM__ERROR, err_msg);
		      }
                      else
		      {
		        I_object_inst_ref_var* where_var_ptr =
				where_spec_si_ptr->
				    get_object_inst_ref_var_ptr ();
			if (! where_var_ptr)
			{
			         Description err_msg ("Variable '");
			  err_msg += where_spec_var_str;
				   err_msg += "' is not of type INST_REF";
			  	   err_msg += " in .SPECIAL_WHERE Statement.";
			  GS_ui::inform (UI_INFORM__ERROR, err_msg);
			}
                        else
			{
                          if ( where_var_ptr->cardinality() == 0 )
			  {
				 Description err_msg ("Variable '");
				 err_msg += where_spec_var_str;
				 err_msg += "' has cardinality of zero in .SPECIAL_WHERE Statement.";
			    GS_ui::inform (UI_INFORM__ERROR, err_msg);
			  }
                          else
			  {
                            /*  can't use && between the is_valid_attr_name calls because 
                                the compiler gives the error message:
                                line 1396: sorry, not implemented: temporary of class GS_string
                                with destructor needed in && expression
                            */
                            if ( where_var_ptr->is_valid_attr_name ( ret_val_string ) )
                              if ( where_var_ptr->is_valid_attr_name ( obj_kl_string ) )
                                if ( where_var_ptr->is_valid_attr_name ( where_spec_string ) )
                                  if ( where_var_ptr->is_valid_attr_name ( key_string ) )
    		  	          {
                                    I_var* obj_kl = where_var_ptr->get_attr_var_ptr( obj_kl_string );
                                    I_var* where_spec = where_var_ptr->get_attr_var_ptr( where_spec_string );
                                    I_var* key = where_var_ptr->get_attr_var_ptr( key_string );

                                    t_boolean result = Special_Where::add( G_Special_Where_table,
                                        obj_kl->get_string_var_ptr()->get_value().char_ptr(), 
                                        where_spec->get_string_var_ptr()->get_value().char_ptr(),
                                        key->get_string_var_ptr()->get_value().char_ptr(),
                                        UNKNOWN_DOMAIN);

                                    I_var* ret_val = where_var_ptr->get_attr_var_ptr( ret_val_string );
                                    I_boolean_var *ret_val_attr = ret_val->get_boolean_var_ptr();
                                    ret_val_attr->set_value(result);
         	                  }
                          }
			}
		      }
		    }

		    else if ( command_str == clear_string )
		    {
                      if ( where_spec_var_str == all1_string ||
                           where_spec_var_str == all2_string ||
                           where_spec_var_str == all3_string )
		      {
                        t_boolean result = Special_Where::clear_all(G_Special_Where_table);
		      }
                      else
		      {
                        where_spec_si_ptr = GS_stack::find_var_si_ptr
			      (where_spec_var_str);
		        if (! where_spec_si_ptr)
		        {
			        Description err_msg ("Unable to find Variable '");
					err_msg += where_spec_var_str;
			  		err_msg += "' in .SPECIAL_WHERE Statement.";
					GS_ui::inform (UI_INFORM__ERROR, err_msg);
  		        }
                        else
		        {
			   I_object_inst_ref_var* where_var_ptr =
			        where_spec_si_ptr->
				   get_object_inst_ref_var_ptr ();
			   if (! where_var_ptr)
			   {
				    Description err_msg ("Variable '");
					err_msg += where_spec_var_str;
				    err_msg += "' is not of type INST_REF in .SPECIAL_WHERE Statement.";
			     GS_ui::inform (UI_INFORM__ERROR, err_msg);
			   }
                           else
			   {
                             if ( where_var_ptr->cardinality() == 0 )
	                     {
				       Description err_msg ("Variable '");
					   err_msg += where_spec_var_str;
				      err_msg += "' has cardinality of zero in .SPECIAL_WHERE Statement.";
			       GS_ui::inform (UI_INFORM__ERROR, err_msg);
                             }
                             else
			     {
                               if ( where_var_ptr->is_valid_attr_name ( ret_val_string ) )
                                 if ( where_var_ptr->is_valid_attr_name ( obj_kl_string ) )
                                   if ( where_var_ptr->is_valid_attr_name ( where_spec_string ) )
                                     if ( where_var_ptr->is_valid_attr_name ( key_string ) )
      	  	                     {
                                       I_var* obj_kl = where_var_ptr->get_attr_var_ptr( obj_kl_string );
                                       I_var* where_spec = where_var_ptr->get_attr_var_ptr( where_spec_string );
                                       I_var* key = where_var_ptr->get_attr_var_ptr( key_string );
                                       t_boolean result = Special_Where::clear( G_Special_Where_table, 
                                           obj_kl->get_string_var_ptr()->get_value().char_ptr(), 
                                           where_spec->get_string_var_ptr()->get_value().char_ptr(),
                                           key->get_string_var_ptr()->get_value().char_ptr() );

                                       I_var* ret_val = where_var_ptr->get_attr_var_ptr( ret_val_string );
                                       I_boolean_var *ret_val_attr = ret_val->get_boolean_var_ptr();
                                       ret_val_attr->set_value(result);
			             }
                             }
			   }
		        }
		      }
		    }
		    else if ( command_str == query_string )
		    {
                      where_spec_si_ptr = GS_stack::find_var_si_ptr
			    (where_spec_var_str);
		      if (! where_spec_si_ptr)
		      {
			        Description err_msg ("Unable to find Variable '");
					err_msg += where_spec_var_str;
				err_msg += "' in .SPECIAL_WHERE Statement.";
			GS_ui::inform (UI_INFORM__ERROR, err_msg);
		      }
                      else
		      {
			 I_object_inst_ref_var* where_var_ptr =
				where_spec_si_ptr->
				    get_object_inst_ref_var_ptr ();
			 if (! where_var_ptr)
			 {
				    Description err_msg ("Variable '");
					err_msg += where_spec_var_str;
				    err_msg += "' is not of type INST_REF in .SPECIAL_WHERE Statement.";
			   GS_ui::inform (UI_INFORM__ERROR, err_msg);
			 }
                         else
			 {
                           if ( where_var_ptr->cardinality() == 0 )
			   {
				      Description err_msg ("Variable '");
					  err_msg += where_spec_var_str;
				      err_msg += "' has cardinality of zero in .SPECIAL_WHERE Statement.";
			     GS_ui::inform (UI_INFORM__ERROR, err_msg);
			   }
                           else
			   {
                             if ( where_var_ptr->is_valid_attr_name ( ret_val_string ) )
                               if ( where_var_ptr->is_valid_attr_name ( obj_kl_string ) )
                                 if ( where_var_ptr->is_valid_attr_name ( where_spec_string ) )
                                   if ( where_var_ptr->is_valid_attr_name ( key_string ) )
    			           {
                                     I_var* obj_kl = where_var_ptr->get_attr_var_ptr( obj_kl_string );
                                     I_var* where_spec = where_var_ptr->get_attr_var_ptr( where_spec_string );
                                     I_var* key = where_var_ptr->get_attr_var_ptr( key_string );
                                     t_boolean result = Special_Where::query( G_Special_Where_table,
                                         obj_kl->get_string_var_ptr()->get_value().char_ptr(), 
                                         where_spec->get_string_var_ptr()->get_value().char_ptr(),
                                         key->get_string_var_ptr()->get_value().char_ptr() );

                                     I_var* ret_val = where_var_ptr->get_attr_var_ptr( ret_val_string );
                                     I_boolean_var *ret_val_attr = ret_val->get_boolean_var_ptr();
                                     ret_val_attr->set_value(result);
			           }
                           }
			 }
		      }

		    }
		    else
		    {
				Description err_msg ("Unknown command '");
				err_msg += command_str;
				err_msg += "' in .SPECIAL_WHERE Statement.";
                GS_ui::inform (UI_INFORM__ERROR, err_msg);
		    }
		}


		else if (ctrl_stmt_str == dot_license)
		{
		    //  Get the message to print and treat as a string
		    //    with substitution variables.
		    //
		    Description license_str;
            s_line_str.parse_token (s_line_cursor, license_str);
		    s_line_str.consume_white_space (s_line_cursor);
		    Description feature_str_vchar;
			s_line_str.parse_token__quoted_str (s_line_cursor, feature_str_vchar);
			char *feature_str_ASCII = 
					Description::createAsciiFromVchar(feature_str_vchar.char_ptr());
			GS_string feature_str = feature_str_ASCII;
			Description::freeAsciiFromVchar(feature_str_ASCII);

            t_boolean check_license = TRUE;
            BP_LICENSE_TYPE lic_type = BP_LICENSE_INVALID;
            if (feature_str.char_ptr() == "A1")
              lic_type = BP_LICENSE_MISC1;
            else if (feature_str.char_ptr() == "A2")
              lic_type = BP_LICENSE_MISC2;
            else if (feature_str.char_ptr() == "A3")
              lic_type = BP_LICENSE_MISC3;
            else if (feature_str.char_ptr() == "A4")
              lic_type = BP_LICENSE_MISC4;
            else if (feature_str.char_ptr() == "A5")
              lic_type = BP_LICENSE_MISC5;
            else if (feature_str.char_ptr() == "A6")
              check_license = FALSE;
            else
              {
                fprintf (stderr,
                         "\nSORRY:  Invalid feature code on .LICENSE statement.\n\n");
                exit (255);
                break;
              }
        }
		else
		{
		    GS_ui::inform (UI_INFORM__ERROR,
			GS_string("Do not recognize control statement - if you want the first non-white space character of a literal text line to be a '.' character, use the '..' character sequence as the first two non-white space characters."));
		}
	    }
	}
	else
	{
	    //  This is a literal text line.
	    //
	    Description& out_line
	     = GS_substitution::substitute_string (s_line_str, TRUE);
	    if ((out_line.length () >= 1)
		&& (out_line.char_at(out_line.length () - 1) == '\\'))
	    {
		if ((out_line.length () >= 2)
		    && (out_line.char_at(out_line.length () - 2) == '\\'))
		{
		    if ((out_line.length () >= 3)
			&& (out_line.char_at(out_line.length () - 3) == '\\'))
		    {
			//  The character sequence '\\\' is at the end of the
			//    line which indicates that a single '\'
			//    character should be passed through to the
			//    generated file - along with NO new-line...
			//
			out_line.truncate(out_line.length () - 2);
		    }
		    else
		    {
			//  The character sequence '\\' is at the end of the
			//    line which indicates that a single '\'
			//    character should be passed through to the
			//    generated file - still need to output the
			//    new-line...
			//
			out_line.truncate(out_line.length () - 1);
			out_line.append_char('\n');
		    }
		}
		else
		{
		    //  The character '\' is at the end of the line and it is
		    //    not part of a '\\' or '\\\' sequence - this indicates
		    //    that no newline character should be put at the end
		    //    of this line in the generated file.
		    //
		    out_line.truncate(out_line.length () - 1);
		}
	    }
	    else
	    {
		//  No special handling - output the new-line.
		//
		out_line.append_char('\n');
	    }
	    
	    
	    I_frag_ref_var* func_return_frag_ref_var_ptr
		= GS_stack::function_get_return_frag_ref_var_ptr ();
	    if (func_return_frag_ref_var_ptr)
	    {
		func_return_frag_ref_var_ptr->append_to_body (out_line);
	    }
	    else
	    {
		out_file << out_line.char_ptr () << flush;
	    }
	}

    }


    //  Close the temporary out file.
    //
    out_file.close ();


    // Close all archetype files
    open_arch_file_t::close_all_arch_files();

    return TRUE;
}





void
GS_archetype::for_fast_forward_to_end ()

{
    unsigned int for_statement_nesting_level = 1;
    Description ctrl_stmt1_str;
    Description ctrl_stmt2_str;
    do
    {
        get_next_line ();
        s_line_str.parse_token (s_line_cursor, ctrl_stmt1_str);
	ctrl_stmt1_str.convert_to_upper_case ();
        s_line_str.parse_token (s_line_cursor, ctrl_stmt2_str);
	ctrl_stmt2_str.convert_to_upper_case ();
        
        
        if (ctrl_stmt1_str == dot_for)
        {
            for_statement_nesting_level++;
        }
        else if ((ctrl_stmt1_str == dot_end)
	    && ((ctrl_stmt2_str  == for_string) || (ctrl_stmt2_str  == for_semi)))
        {
            for_statement_nesting_level--;
        }
    }
    while ((! open_arch_file_t::arch_file()->eof ()) &&
        ( ! ((for_statement_nesting_level < 1)
        && (ctrl_stmt1_str == dot_end)
        && ((ctrl_stmt2_str == for_string) || (ctrl_stmt2_str == for_semi)))));
}





void
GS_archetype::while_fast_forward_to_end ()

{
    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_BEGIN, (L_log_string,
	"Begin  GS_archetype::while_fast_forward_to_end ()."));


    Description ctrl_stmt1_str;
    Description ctrl_stmt2_str;
    t_uint while_statement_nesting_level = 1;
    do
    {
	ctrl_stmt1_str = "";
	ctrl_stmt2_str = "";


	if (! get_next_line ())
	{
	    GS_ui::inform (UI_INFORM__ERROR,
		GS_string("Unable to find  -->END WHILE;<--  before End of File."));
	    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		"End  GS_archetype::while_fast_forward_to_end ():  Reached EOF"));
	    return;
	}


	s_line_str.consume_white_space (s_line_cursor);
	t_uint ii = s_line_cursor;
	if ( (s_line_str.char_at(ii  ) == '.')
	 && ((s_line_str.char_at(ii+1) == 'W') || (s_line_str.char_at(ii+1) == 'w'))
	 && ((s_line_str.char_at(ii+2) == 'H') || (s_line_str.char_at(ii+2) == 'h'))
	 && ((s_line_str.char_at(ii+3) == 'I') || (s_line_str.char_at(ii+3) == 'i'))
	 && ((s_line_str.char_at(ii+4) == 'L') || (s_line_str.char_at(ii+4) == 'l'))
	 && ((s_line_str.char_at(ii+5) == 'E') || (s_line_str.char_at(ii+5) == 'e')))
	{
	    s_line_str.parse_token ('(', s_line_cursor, ctrl_stmt1_str);
	    ctrl_stmt1_str.convert_to_upper_case ();
            while_statement_nesting_level++;
	}
	else if
	   ( (s_line_str.char_at(ii  ) == '.')
	 && ((s_line_str.char_at(ii+1) == 'E') || (s_line_str.char_at(ii+1) == 'e'))
	 && ((s_line_str.char_at(ii+2) == 'N') || (s_line_str.char_at(ii+2) == 'n'))
	 && ((s_line_str.char_at(ii+3) == 'D') || (s_line_str.char_at(ii+3) == 'd')))
	{
	    s_line_str.parse_token (s_line_cursor, ctrl_stmt1_str);
	    ctrl_stmt1_str.convert_to_upper_case ();
	    s_line_str.parse_token (s_line_cursor, ctrl_stmt2_str);
	    ctrl_stmt2_str.convert_to_upper_case ();
	    if ((ctrl_stmt2_str == while_string) || (ctrl_stmt2_str == while_semi))
	    {
		while_statement_nesting_level--;
	    }
	    else
	    {
		//  Have reached a different kind of  -->.END<--  statement.
		//
	    }
	}
    } while ((! open_arch_file_t::arch_file()->eof ()) &&
	( ! ((while_statement_nesting_level < 1)
	    && (ctrl_stmt1_str == dot_end)
	    && ((ctrl_stmt2_str == while_string) || (ctrl_stmt2_str == while_semi)))));


    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	"End  GS_archetype::while_fast_forward_to_end ()."));
}





void
GS_archetype::if_fast_forward ()

{
    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_BEGIN, (L_log_string,
	"Begin  GS_archetype::if_fast_forward ()."));


    Description ctrl_stmt1_str;
    Description ctrl_stmt2_str;
    t_uint if_statement_nesting_level = 1;
    streampos prev_line_begin_char_num;
    do
    {
	prev_line_begin_char_num = get_char_num ();


	ctrl_stmt1_str = "";
	ctrl_stmt2_str = "";


	if (! get_next_line ())
	{
	    GS_ui::inform (UI_INFORM__ERROR,
		GS_string("Unable to find  -->END IF;<--  before End of File."));
	    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		"End  GS_archetype::if_fast_forward ():  Reached EOF"));
	    return;
	}


	s_line_str.consume_white_space (s_line_cursor);
	t_uint ii = s_line_cursor;
	if ( (s_line_str.char_at(ii  ) == '.')
	 && ((s_line_str.char_at(ii+1) == 'I') || (s_line_str.char_at(ii+1) == 'i'))
	 && ((s_line_str.char_at(ii+2) == 'F') || (s_line_str.char_at(ii+2) == 'f')))
	{
	    s_line_str.parse_token ('(', s_line_cursor, ctrl_stmt1_str);
	    ctrl_stmt1_str.convert_to_upper_case ();
            if_statement_nesting_level++;
	}
	else if
	   ( (s_line_str.char_at(ii  ) == '.')
	 && ((s_line_str.char_at(ii+1) == 'E') || (s_line_str.char_at(ii+1) == 'e'))
	 && ((s_line_str.char_at(ii+2) == 'L') || (s_line_str.char_at(ii+2) == 'l'))
	 && ((s_line_str.char_at(ii+3) == 'I') || (s_line_str.char_at(ii+3) == 'i'))
	 && ((s_line_str.char_at(ii+4) == 'F') || (s_line_str.char_at(ii+4) == 'f')))
	{
	    s_line_str.parse_token ('(', s_line_cursor, ctrl_stmt1_str);
	    ctrl_stmt1_str.convert_to_upper_case ();
	}
	else if
	   ( (s_line_str.char_at(ii  ) == '.')
	 && ((s_line_str.char_at(ii+1) == 'E') || (s_line_str.char_at(ii+1) == 'e'))
	 && ((s_line_str.char_at(ii+2) == 'L') || (s_line_str.char_at(ii+2) == 'l'))
	 && ((s_line_str.char_at(ii+3) == 'S') || (s_line_str.char_at(ii+3) == 's'))
	 && ((s_line_str.char_at(ii+4) == 'E') || (s_line_str.char_at(ii+4) == 'e')))
	{
	    s_line_str.parse_token (s_line_cursor, ctrl_stmt1_str);
	    ctrl_stmt1_str.convert_to_upper_case ();
	}
	else if
	   ( (s_line_str.char_at(ii  ) == '.')
	 && ((s_line_str.char_at(ii+1) == 'E') || (s_line_str.char_at(ii+1) == 'e'))
	 && ((s_line_str.char_at(ii+2) == 'N') || (s_line_str.char_at(ii+2) == 'n'))
	 && ((s_line_str.char_at(ii+3) == 'D') || (s_line_str.char_at(ii+3) == 'd')))
	{
	    s_line_str.parse_token (s_line_cursor, ctrl_stmt1_str);
	    ctrl_stmt1_str.convert_to_upper_case ();
	    s_line_str.parse_token (s_line_cursor, ctrl_stmt2_str);
	    ctrl_stmt2_str.convert_to_upper_case ();
	    if ((ctrl_stmt2_str == if_string) || (ctrl_stmt2_str == if_semi))
	    {
		if_statement_nesting_level--;
	    }
	    else
	    {
		//  Have reached a different kind of  -->.END<--  statement.
		//
	    }
	}
    } while ((! open_arch_file_t::arch_file()->eof ()) &&
	( ! (((if_statement_nesting_level < 1)
	    && (ctrl_stmt1_str == dot_end)
	    && ((ctrl_stmt2_str == if_string) || (ctrl_stmt2_str == if_semi)))
	||
	    ((if_statement_nesting_level < 2)
		&& ((ctrl_stmt1_str == dot_elif)
		    ||
		    (ctrl_stmt1_str == dot_else))))));


    unsigned int curr_line_num = GS_ui::get_line_num ();
    if (curr_line_num > 1)
    {
        if ((ctrl_stmt1_str == dot_elif)
            ||
	    (ctrl_stmt1_str == dot_else)
            ||
	    ((ctrl_stmt1_str == dot_end)
		&& ((ctrl_stmt2_str == if_string) || (ctrl_stmt2_str == if_semi))))
        {
            goto_arch_file_line (prev_line_begin_char_num, curr_line_num - 1);
        }
    }


    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	"End  GS_archetype::if_fast_forward ()."));
}





void
GS_archetype::if_fast_forward_to_end ()

{
    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_BEGIN, (L_log_string,
	"Begin  GS_archetype::if_fast_forward_to_end ()."));


    Description ctrl_stmt1_str;
    Description ctrl_stmt2_str;
    t_uint if_statement_nesting_level = 1;
    do
    {
	ctrl_stmt1_str = "";
	ctrl_stmt2_str = "";


	if (! get_next_line ())
	{
	    GS_ui::inform (UI_INFORM__ERROR,
		GS_string("Unable to find  -->END IF;<--  before End of File."));
	    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		"End  GS_archetype::if_fast_forward_to_end ():  Reached EOF"));
	    return;
	}


	s_line_str.consume_white_space (s_line_cursor);
	t_uint ii = s_line_cursor;
	if ( (s_line_str.char_at(ii  ) == '.')
	 && ((s_line_str.char_at(ii+1) == 'I') || (s_line_str.char_at(ii+1) == 'i'))
	 && ((s_line_str.char_at(ii+2) == 'F') || (s_line_str.char_at(ii+2) == 'f')))
	{
	    s_line_str.parse_token ('(', s_line_cursor, ctrl_stmt1_str);
	    ctrl_stmt1_str.convert_to_upper_case ();
            if_statement_nesting_level++;
	}
	else if
	   ( (s_line_str.char_at(ii  ) == '.')
	 && ((s_line_str.char_at(ii+1) == 'E') || (s_line_str.char_at(ii+1) == 'e'))
	 && ((s_line_str.char_at(ii+2) == 'N') || (s_line_str.char_at(ii+2) == 'n'))
	 && ((s_line_str.char_at(ii+3) == 'D') || (s_line_str.char_at(ii+3) == 'd')))
	{
	    s_line_str.parse_token (s_line_cursor, ctrl_stmt1_str);
	    ctrl_stmt1_str.convert_to_upper_case ();
	    s_line_str.parse_token (s_line_cursor, ctrl_stmt2_str);
	    ctrl_stmt2_str.convert_to_upper_case ();
	    if ((ctrl_stmt2_str == if_string) || (ctrl_stmt2_str == if_semi))
	    {
		if_statement_nesting_level--;
	    }
	    else
	    {
		//  Have reached a different kind of  -->.END<--  statement.
		//
	    }
	}
    } while ((! open_arch_file_t::arch_file()->eof ()) &&
	( ! ((if_statement_nesting_level < 1)
	    && (ctrl_stmt1_str == dot_end)
	    && ((ctrl_stmt2_str == if_string) || (ctrl_stmt2_str == if_semi)))));


    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	"End  GS_archetype::if_fast_forward_to_end ()."));
}





t_boolean
GS_archetype::test_open_arch_file (const GS_string& p_arch_file_name_str)

{
	/* i1841 (deleted) - this check is pointless, not going to do anymore*/

    return TRUE;
}





t_boolean
GS_archetype::open_arch_file (const GS_string& p_arch_file_name_str)

{
    GS_ui::set_name_str (p_arch_file_name_str);
    GS_ui::reset_line_num ();
    
    if ( open_arch_file_t::is_file_open( p_arch_file_name_str ) )
    {
      open_arch_file_t::set_arch_file_open( p_arch_file_name_str );
      return TRUE;
    }

    if ( open_arch_file_t::open_arch_file( p_arch_file_name_str ) )
    {
      // Rewind the file to start "fresh"
      open_arch_file_t::rewind_file();

      return TRUE;
    }

  return FALSE;
}





t_boolean
GS_archetype::goto_arch_file_line (streampos p_char_num,
    unsigned int p_line_num, const GS_string& p_arch_file_name_str)

{
    if (p_arch_file_name_str != "")
    {
	if (GS_ui::get_name_str () != p_arch_file_name_str)
	{
	    close_arch_file ();
	    GS_ui::set_name_str (p_arch_file_name_str);
	    open_arch_file (GS_ui::get_name_str ());
	}
    } 


    if (open_arch_file_t::arch_file()->eof ())
    {
      open_arch_file_t::rewind_file();
    }


    if ( p_char_num < 0 )
    {
      // invalid file position.  most likely at end of file
      // process the stream so that it is at eof
      open_arch_file_t::goto_eof();
    }
    else
    {
      open_arch_file_t::arch_file()->seekg (p_char_num, ios::beg);
    }

    if ( p_arch_file_name_str == default_script_file_name_str )
    {
      open_arch_file_t::set_script_file(TRUE);
    }

    GS_ui::reset_line_num (p_line_num);
    s_line_str.truncate(0);
    s_line_cursor = 0;
    return TRUE;
    
}






void
GS_archetype::close_arch_file ()

{
    // i3159.1.2 delete
    GS_ui::reset_line_num ();
}

// i3159.2.2  add begin
void 
GS_archetype::script_changed( const GS_string& p_script_file_name )
{
    open_arch_file_t::remove_file(p_script_file_name);
}
// i3159.2.2  add end


t_boolean
GS_archetype::get_next_line ()

{
    if (! open_arch_file_t::arch_file()->eof ())
    {
        //  Lines still can be gotten from the currently open archetype file.
        //
	s_line_str.truncate(0);
	s_line_cursor = 0;

      static char temp_buf[ GS_ARCHETYPE_FILE_LINE_LENGTH + 1 ];
      temp_buf[0] = '\0';
	if ( open_arch_file_t::encrypted() )
	{
           xtumlmc_getline( temp_buf, open_arch_file_t::arch_file(), GS_ARCHETYPE_FILE_LINE_LENGTH );
           //Decrypt_Line( encrypted_buf, temp_buf);
	}
	else
	{
            open_arch_file_t::arch_file()->getline (temp_buf, GS_ARCHETYPE_FILE_LINE_LENGTH);
	}

    static vchar temp_vchar_buf[ GS_ARCHETYPE_FILE_LINE_LENGTH + 1 ];
    vcharCopyFromSystem( temp_buf, temp_vchar_buf );
    s_line_str = temp_vchar_buf;

	if (! open_arch_file_t::arch_file()->eof ())
	{
		s_line_cursor = 0;
	    GS_ui::increment_line_num ();
	    return TRUE;
	}
	else
	{
	    if (s_line_str.char_at(0) != '\0')
	    {
		s_line_cursor = 0;
		GS_ui::increment_line_num ();
		return TRUE;
	    }
	}
    }
    
    //  No more lines can be gotten from the currently open archetype file -
    //    see if we are within any include files - if so, then return from
    //    the include file back to where the file was included from.
    //
    streampos return_char_num;
    unsigned int return_line_num;
    GS_string return_arch_file_name_str;
    GS_string include_arch_file_name_str;
    if (GS_stack::include_end (&return_char_num, &return_line_num,
	&return_arch_file_name_str, &include_arch_file_name_str))
    {
        if (include_arch_file_name_str == GS_ui::get_name_str ())
        {
            if (goto_arch_file_line (return_char_num, return_line_num,
		return_arch_file_name_str))
            {
                //  Now sitting on '.INCLUDE' line - must get line following
                //    this line.
                //
                return get_next_line ();
            }
        }
        else
        {
	    GS_ui::inform (UI_INFORM__ERROR, GS_string
		("GS_archetype::get_next_line ():  Trying to return from include file '")
                + include_arch_file_name_str
		+ "' but we are currently in file '"
		+ GS_ui::get_name_str () + "'");
	    return FALSE;
        }
    }


    //  No more lines to get.
    //
    s_line_str.truncate(0);
    s_line_cursor = 0;
    GS_ui::increment_line_num ();
    return FALSE;
}


t_boolean
open_arch_file_t::open_arch_file(const GS_string& p_arch_file_name_str)
{
	static bool init_arcs = true;
        static bool look_for_binary = false;

	if ( init_arcs ) {
          if ( binaryLicense2020Used ) {
            xtumlmc_init_2020_map();
          } else if ( binaryLicense3020Used ) {
            xtumlmc_init_3020_map();
          }
          init_arcs = false;
          look_for_binary = binaryLicense2020Used || binaryLicense3020Used;
        }

        bool binary_arc_found = false;
	if ( look_for_binary ) {
	  // Look for the file in the encrypted archetypes map.  If found
	  // use that, otherwise, read from the file system.
	  std::string name_no_path = p_arch_file_name_str.char_ptr();
	  std::string::size_type index = name_no_path.find_last_of( "\\/" );
	  if ( (index != std::string::npos) && (index + 1 != std::string::npos) ) {
	    name_no_path = name_no_path.substr( index + 1 );
	  }

	  char name_buff[ 256 ];
	  xtumlmc_crypt( name_buff, name_no_path.c_str(), name_no_path.length() );
	  arch_map_iter = arch_map.find( std::string( name_buff, name_no_path.length() ) );
          binary_arc_found = ( arch_map_iter != arch_map.end() );
        }

	if ( binary_arc_found ) {

          istrstream *str_arch_file;
          if ( binaryLicense2020Used ) {
            str_arch_file = new istrstream (
              xtumlmc_2020_archetypes[ arch_map_iter->second ].content, 
              xtumlmc_2020_archetypes[ arch_map_iter->second ].length );
            // add_file takes care of setting m_current_arch_file
            open_arch_file_t::add_file ( str_arch_file, p_arch_file_name_str, TRUE,
              xtumlmc_2020_archetypes[ arch_map_iter->second ].content );
          } else if ( binaryLicense3020Used ) {
            str_arch_file = new istrstream (
              xtumlmc_3020_archetypes[ arch_map_iter->second ].content, 
              xtumlmc_3020_archetypes[ arch_map_iter->second ].length );
            // add_file takes care of setting m_current_arch_file
            open_arch_file_t::add_file ( str_arch_file, p_arch_file_name_str, TRUE,
              xtumlmc_3020_archetypes[ arch_map_iter->second ].content );
          }

	} else {

	  for ( int i = 0; i < m_num_open_arch_files; ++i )
	  {
	    if ( m_open_arch_files[i].m_file_name == p_arch_file_name_str )
	    {
	      m_current_arch_file = i;
	      return TRUE;
	    }
	  }
	
	  ifstream* arch_file = new ifstream();
	     
	  arch_file->open (GS_ui::get_name_str ().char_ptr (), ios::nocreate);
	  if (! arch_file->good ())
	  {
	    delete arch_file;
	    GS_ui::inform (UI_INFORM__ERROR, GS_string
	      ("Could NOT open File '") + GS_ui::get_name_str () + "'.");
	    return FALSE;
		}
	
	  // get the file size
	  // i3159.4.1 delete
	  // i3159.4.1 add begin
	  arch_file->seekg(0, ios::end);
	  int file_length = arch_file->tellg();
	  arch_file->seekg(0, ios::beg);
	  // i3159.4.1 add end
	
	  // Now read the file into a properly sized buffer (with a little extra space)
	  char *big_buff = new char [ file_length+128 ];   // i3159.4.1 changed
	  memset ( big_buff, 0, file_length+128 );  // i3159.4.1 added
	  // i3159.4.1 delete
	  arch_file->read ( big_buff, file_length+128 );
	  arch_file->close();
	  delete arch_file;
	
	  istrstream *str_arch_file = new istrstream ( big_buff, file_length );
	
	  // add_file takes care of setting m_current_arch_file
	  open_arch_file_t::add_file ( str_arch_file, p_arch_file_name_str, FALSE, big_buff );
	}    

  return TRUE;
}

void
open_arch_file_t::close_all_arch_files ()

{
    for ( int i = 0; i < m_num_open_arch_files; ++i )
    {
      m_open_arch_files[i].m_file_name = "";

      delete m_open_arch_files[i].m_arch_file;
      if ( ! m_open_arch_files[i].m_file_encrypted ) {
        delete [] m_open_arch_files[i].m_buffer;
      }

    }
    m_num_open_arch_files = 0;
    m_current_arch_file = -1; 
}

t_boolean
open_arch_file_t::is_file_open(const GS_string& p_arch_file_name_str)
{
    for ( int i = 0; i < m_num_open_arch_files; ++i )
    {
      if ( m_open_arch_files[i].m_file_name == p_arch_file_name_str )
      {
        return TRUE;
      }
    }

  return FALSE;
}

void
open_arch_file_t::set_arch_file_open(const GS_string& p_arch_file_name_str)
{
  for ( int i = 0; i < m_num_open_arch_files; ++i )
  {
    if ( m_open_arch_files[i].m_file_name == p_arch_file_name_str )
    {
      m_current_arch_file = i; 
      return;
    }
  }

  m_current_arch_file = -1; 

}

void 
open_arch_file_t::add_file( istrstream* p_arch_file,
    const GS_string& p_file_name,
    t_boolean p_file_encrypted, char *p_buffer)
{
  if  ( m_open_arch_files == 0 )
    {
      // First time call, allocate open file array
      m_open_arch_files = new open_arch_file_t[m_max_num_open_arch_files];
    }

  if ( m_num_open_arch_files >= m_max_num_open_arch_files )
    {
      // Array is full, create a new, bigger one, and
      // copy the data to it.
      int new_max = 2 * m_max_num_open_arch_files;
      open_arch_file_t *new_array = new open_arch_file_t[new_max];
      
      for ( int i = 0; i < m_num_open_arch_files; ++i )
        {
          new_array[i] = m_open_arch_files[i];
        }
      
      delete [] m_open_arch_files;
      m_open_arch_files = new_array;
      m_max_num_open_arch_files = new_max;
    }
  
  m_open_arch_files[m_num_open_arch_files].m_file_name = p_file_name;
  m_open_arch_files[m_num_open_arch_files].m_arch_file = p_arch_file;
  m_open_arch_files[m_num_open_arch_files].m_file_encrypted = p_file_encrypted;
  m_open_arch_files[m_num_open_arch_files].m_script_file = FALSE;
  m_open_arch_files[m_num_open_arch_files].m_buffer = p_buffer;
  m_current_arch_file = m_num_open_arch_files; 
  m_num_open_arch_files += 1;

}
    
void 
open_arch_file_t::remove_file(const GS_string& p_file_name)   // i3159.1.1.2 changed
{
  // i3159.1.1.3  add begin
  for ( int i = 0; i < m_num_open_arch_files; ++i )
  {
    if ( (m_open_arch_files[i].m_file_name == p_file_name) &&
         (m_open_arch_files[i].m_script_file) )
    {
  // i3159.1.1.3 add end
  // i3159.1.1.4 delete 
  // i3159.1.1.4 add begin
        delete m_open_arch_files[i].m_arch_file;
        delete [] m_open_arch_files[i].m_buffer;

        // and defragment the array
        int j = i;
        while ( j < m_num_open_arch_files-1 )
        {
          m_open_arch_files[j] = m_open_arch_files[j+1];
          j += 1;
        }

        m_open_arch_files[j].m_arch_file = 0;
        m_open_arch_files[j].m_buffer = 0;
        
        m_num_open_arch_files -= 1;

        // fixup the current arch file pointer (if necessary)
        if ( m_current_arch_file == i )
        {
          m_current_arch_file = -1;
        }
        else if ( m_current_arch_file > i )
        {
          m_current_arch_file -= 1;
        }
        break;
  // i3159.1.1.4 add end
    }
  }
}

void 
open_arch_file_t::rewind_file()
{
  if ( open_arch_file_t::arch_file()->eof() )
  {
    //--------------------------
    // the following was used when arch_file was an ifstream*
    // if we're at the end of file, seekg doesn't work,
    // so we need close and open it again
    //    open_arch_file_t::arch_file()->close();
    //open_arch_file_t::arch_file()->open (
    //    m_open_arch_files[m_current_arch_file].m_file_name.char_ptr(),
    //    ios::nocreate);
    //--------------------------
    open_arch_file_t::arch_file()->clear();
    open_arch_file_t::arch_file()->seekg (0, ios::beg);
  }
  else
  {
    open_arch_file_t::arch_file()->seekg (0, ios::beg);
  }
}


void interpret_stmt__create( const Description &p_line_str )
{
    Description create_str;
    s_line_str.parse_token (s_line_cursor, create_str);
	Description object_str;
    s_line_str.parse_token (s_line_cursor, object_str);
	object_str.convert_to_upper_case ();
	if (object_str != object_string)
	{
	GS_ui::inform (UI_INFORM__ERROR,
		GS_string("Syntax error in .CREATE Statement - missing keyword 'OBJECT'."));
	}
	else
	{
	    Description instance_str;
        s_line_str.parse_token (s_line_cursor, instance_str);
	    instance_str.convert_to_upper_case ();
	    if (instance_str != instance_string)
	    {
	    GS_ui::inform (UI_INFORM__ERROR,
		    GS_string("Syntax error in .CREATE Statement - missing keyword 'INSTANCE'."));
	    }
	    else
	    {
	        Description inst_var_str;
	        s_line_str.parse_to_keyword ("OF", s_line_cursor, inst_var_str);

            Description lower_case_inst_var_str (inst_var_str);
            lower_case_inst_var_str.convert_to_lower_case ();
            if (lower_case_inst_var_str == self_string)
            {
	            Description err_msg ("Syntax error in .CREATE Statement - Instance '");
		        err_msg += inst_var_str;
	            err_msg += "' NOT allowed to be used as result variable in .CREATE statement.";
		        GS_ui::inform (UI_INFORM__ERROR, err_msg);
	            return;
            }

            Description of_str;
            s_line_str.parse_token (s_line_cursor, of_str);
	        of_str.convert_to_upper_case ();
	        if (of_str != of_string)
	        {
		        GS_ui::inform (UI_INFORM__ERROR,
		        GS_string("Syntax error in .CREATE Statement - missing keyword 'OF'."));
	        }
	        else
	        {
		        Description keyletters;
		        s_line_str.parse_token (s_line_cursor, keyletters);

	            keyletters.convert_to_upper_case ();
	            mc_dbms_Set <I_Object*>* obj_coll_ptr
	                = I_Object::find_Object_by_key_letter
		            (GS_gen_sim_db_ptr, keyletters.char_ptr ());


	            if (! obj_coll_ptr)
	            {
	                LOG_ERROR ((L_log_string,
		            "interpret_stmt__create ():  Creation of I_Object collection in find returned 0."));
	                return;
	            }

	            if (obj_coll_ptr->cardinality () < 1)
	            {
	                Description err_msg ("Syntax error in .CREATE Statement - Object '");
		            err_msg += keyletters;
		            err_msg += "' Unknown.";
	                GS_ui::inform (UI_INFORM__ERROR, err_msg);
	                delete obj_coll_ptr;
	                return;
	            }

	            if (obj_coll_ptr->cardinality () > 1)
	            {
	                LOG_ERROR ((L_log_string,
		            "interpret_stmt__create ():  Reference side I_Object Collection resulted in more than one instance! - continuing with one of the instances."));
	            }

	            I_Object* obj_ptr = obj_coll_ptr->pick ();
	            delete obj_coll_ptr;
	            if (! obj_ptr)
	            {
	                Description err_msg ("Syntax error in .CREATE Statement - Object '");
		            err_msg += keyletters;
		            err_msg += "' not a valid object in the DB.";
	                GS_ui::inform (UI_INFORM__ERROR, err_msg);
	                return;
	            }
	            
	            I_Object_Instance* oinst_ptr = 0;
	            if (obj_ptr->get_Object_Instance_R2001_coll_ptr ()->cardinality () < 1)
	            {
	                //  No instances exist yet in the DB for this object type.  Create
	                //    a new segment and place this first instance in that segment.
	                //
	                mc_dbms_segment* oinst_segment_ptr
		            = GS_gen_sim_db_ptr->create_segment ();
	                oinst_ptr = I_Object_Instance::create (oinst_segment_ptr);
	            }
	            else
	            {
	                //  One or more instances already exists in the DB for this
	                //    object type.  New this new instance in the same segment
	                //    as the other instances.
	                //
	                oinst_ptr = I_Object_Instance::create (mc_dbms_segment::of
		            (obj_ptr->get_Object_Instance_R2001_coll_ptr ()->pick ()));
	            }

	            if (! oinst_ptr)
	            {
	                LOG_ERROR ((L_log_string,
		            "interpret_stmt__create ():  Unable to create an instance of 'I_Object_Instance'."));
	                return;
	            }
	            oinst_ptr->relate_R2001 (obj_ptr);

                // Create the attribute instances for the new object instance
	            mc_dbms_List <I_Attribute*>* attr_coll_ptr
	                = obj_ptr->get_Attribute_R102_coll_ptr ();
	            if (! attr_coll_ptr)
	            {
	                LOG_ERROR ((L_log_string,
		            "interpret_stmt__create ():  Collection associated with rel between O_OBJ & O_ATTR returned 0."));
	                return;
	            }

	            unsigned int num_attr = attr_coll_ptr->cardinality ();
	            for (unsigned int num_attr_values = 0;
	                num_attr_values < num_attr;
	                ++num_attr_values)
	            {
		            I_Attribute* attr_ptr
		                = obj_ptr->get_Attribute_R102_coll_ptr ()->
			            retrieve (num_attr_values);
		            if (! attr_ptr)
		            {
		                LOG_ERROR ((L_log_string,
			            "interpret_stmt__create ():  Unable to access instance of 'I_Attribute'."));
		                return;
		            }
		            
		            I_Attribute_Instance* ainst_ptr = 0;
		            Description attr_name = attr_ptr->get_name ();
		            attr_name.convert_to_upper_case ();
		            if (attr_ptr->get_name () != descrip_string)
		            {
		                //  Create this attribute instance in the same segment
		                //    as the rest of the attribute data (since it will
		                //    be needed in close locality when searching).
		                //
		                ainst_ptr = I_Attribute_Instance::create
			            (mc_dbms_segment::of (oinst_ptr),
			            attr_ptr->get_core_data_type (),
			            attr_ptr->get_user_data_type (), UNKNOWN_DOMAIN);
		            }
		            else if (attr_ptr->get_Attribute_Instance_R2002_coll_ptr ()->
		                cardinality () < 1)
		            {
		                //  No description attribute instances exist yet in the DB
		                //    for this description attribute.  Create a new segment
		                //    and place this first description attribute instance
		                //    in that segment.  This is done since descriptions
		                //    are not used for searching and are best stored
		                //    separately from the rest of the data so they do not
		                //    spread the data out.
		                //
		                mc_dbms_segment* descrip_ainst_segment_ptr
			            = GS_gen_sim_db_ptr->create_segment ();
		                ainst_ptr = I_Attribute_Instance::create
			            (descrip_ainst_segment_ptr,
			            attr_ptr->get_core_data_type (),
			            attr_ptr->get_user_data_type (), UNKNOWN_DOMAIN);
		            }
		            else
		            {
		                //  One or more description attribute instances already
		                //    exists in the DB for this description attribute.
		                //    New this new description attribute instance in the
		                //    same segment as the other description attribute
		                //    instances.
		                //
		                ainst_ptr = I_Attribute_Instance::create
			            (mc_dbms_segment::of (attr_ptr->
			                get_Attribute_Instance_R2002_coll_ptr ()->pick ()),
			            attr_ptr->get_core_data_type (),
			            attr_ptr->get_user_data_type (), UNKNOWN_DOMAIN);
		            }
		            if (! ainst_ptr)
		            {
		                LOG_ERROR ((L_log_string,
			            "interpret_stmt__create ():  Unable to create an instance of 'I_Attribute_Instance'."));
		                return;
		            }
		            ainst_ptr->relate_R2002 (oinst_ptr);
		            ainst_ptr->relate_R2002 (attr_ptr);

		            I_var* ainst_var_ptr = ainst_ptr->get_var_ptr ();
		            if (! ainst_var_ptr)
		            {
		                LOG_ERROR ((L_log_string,
			            "interpret_stmt__create ():  ainst_var_ptr == 0."));
		                return;
		            }

		            if (ainst_var_ptr->get_boolean_var_ptr ())
		            {                                                 
			            ainst_var_ptr->get_boolean_var_ptr ()->
			                set_value (FALSE);
                    }
                    else if (ainst_var_ptr->get_integer_var_ptr ())
		            {
			            ainst_var_ptr->get_integer_var_ptr ()->
			                set_value (0);
                    }
                    else if (ainst_var_ptr->get_real_var_ptr ())
		            {
			            ainst_var_ptr->get_real_var_ptr ()->
			                set_value (0.0);
                    }
                    else if (ainst_var_ptr->get_string_var_ptr ())
		            {
			            ainst_var_ptr->get_string_var_ptr ()->
                            set_value (Description::Default);
                    }
                    else if (ainst_var_ptr->get_unique_id_var_ptr ())
		            {
                        unsigned long attr_value_int = 0x80000;   // initial value for unique_id
		                unsigned long domain_code = 15; // GS_domain_code;

                        mc_dbms_Cursor<I_Attribute_Instance*> ainst_loop_cursor (*attr_ptr->get_Attribute_Instance_R2002_coll_ptr ());
                        for (I_Attribute_Instance *ainst_loop_ptr = ainst_loop_cursor.first ();
    	                        ainst_loop_ptr != 0;
	                            ainst_loop_ptr = ainst_loop_cursor.next ())
	                    {
                            if ( ainst_ptr != ainst_loop_ptr )
                            {
                                unsigned long loop_id = 
                                    ainst_loop_ptr->get_var_ptr()->get_unique_id_var_ptr ()->get_value() & 0x0fffffff;
                                unsigned long loop_domain = 
                                    (ainst_loop_ptr->get_var_ptr()->get_unique_id_var_ptr ()->get_value() & 0xf0000000) >> 28;
                                if ( loop_domain == domain_code &&
                                     attr_value_int <= loop_id )
                                {
                                    attr_value_int = loop_id + 1;
                                }
                            }
                        }

		                // or-in domain code
		                attr_value_int |= domain_code << 28;
		                ainst_var_ptr->get_unique_id_var_ptr ()->
			            set_value (attr_value_int);
		            }
		            else
		            {
		                LOG_ERROR ((L_log_string,
			            "interpret_stmt__create ():  I_Attribute data type NOT recognized."));
		                return;
		            }

                }		

                // There's a new instance present, so reset all related flags so
                // that instance relationships will be re-calculated

                I_relate::clear_related_flag( oinst_ptr );

                // Create the inst_ref<Object> variable that holds the new object instance
                I_object_inst_ref_var* result_inst_var_ptr = 
	               new I_object_inst_ref_var (obj_ptr, oinst_ptr);

                GS_var_si lvalue_var_si;
                lvalue_var_si.replace_var (result_inst_var_ptr);
                GS_stack::place_result_in_stack_var (inst_var_str, &lvalue_var_si);

 
            }
        }
    }
}

//
// Formatting information for emacs
//
// Local Variables:
// tab-width:4
// End:
//

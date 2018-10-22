/*========================================================================
 *
 * File:      $RCSfile: gs_sub.cc,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:42:29 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#include <ctype.h>
#include <time.h>

#include <gs_sub.hh>
#include <gs_arch.hh>
#include <gs_expr.hh>
#include <gs_selct.hh>
#include <gs_ui.hh>
#include <gs_stack.hh>
#include <u_string.hh>
#include <u_desc.hh>
#include <u_userid.hh>

#ifdef OLD_FILE_NAMES
#include <L_log_trace.hh>
#include <L_log_error.hh>
#else
#include <u_trace.hh>
#include <u_error.hh>
#endif

extern "C" {
#include <pt_trans.h>
}

void *GS_substitution::translate_parm = 0;

static void built_in_info_substitutions( 
	const Description& var_attr_name_str,
	Description& var_output_str )
{
	if (var_attr_name_str == date_string)
	{
		//  Get the time and then remove the newline
		//    character from the end of the string returned.
		//
		time_t clock = time (0);
		var_output_str = ctime (&clock);
		var_output_str.truncate (var_output_str.length () -1);
	}
	else if (var_attr_name_str
		== interpreter_version_string)
	{
		//  Get the tool version.
		//
		var_output_str = Description ("Version ");
		var_output_str +=
#include <version.str>
			;
	}
	else if (var_attr_name_str
		== interpreter_platform_string)
	{
		//  Get the user id.
		//
		var_output_str = Description ("Platform ");
		var_output_str +=
#include <platform.str>
			;
	}
	else if (var_attr_name_str == user_id_string)
	{
		//  Get the user id.
		//
		var_output_str = get_userid();
	}
	else if (var_attr_name_str == arch_file_name_string)
	{
		//  Get the archetype file name.
		//
		var_output_str = GS_ui::get_name_str ().char_ptr();
	}
	else if (var_attr_name_str == arch_file_line_string)
	{
		//  Get the archetype file line number.
		//
		char tmp_buf [10];
		sprintf (tmp_buf, "%u", GS_ui::get_line_num ());
		var_output_str = tmp_buf;
	}
	else if (var_attr_name_str == unique_num_string)
	{
		static t_uint __s_unique_num = 1;
		char tmp_str[20];
		sprintf (tmp_str, "%d", __s_unique_num);
		var_output_str = tmp_str;
		__s_unique_num++;
	}
	else
	{
		GS_string error_str;
		error_str  = "Undefined system information requested in '${INFO.type}'\n";
		error_str += "    substitution variable - valid requests are DATE,\n";
		error_str += "    USER_ID, ARCH_FILE_NAME, ARCH_FILE_LINE, & UNIQUE_NUM.\n";
		GS_ui::inform (UI_INFORM__ERROR, error_str);
	}
}

static t_boolean get_substitution_format( const Description& in_str, t_uint& in_str_cursor, 
				t_boolean& make_spaces_underbars,
                t_boolean& remove_all_white_space,
                t_boolean& make_words_begin_capital,
                t_boolean& make_all_lower_case,
                t_boolean& make_all_upper_case,
                t_boolean& make_corba_complient,
				t_boolean& translate_string,
				Description& translate_function)
{
	while ((in_str_cursor < in_str.length ()) && 
		(!in_str.compare_first('{', in_str_cursor)))
	{
		if ((in_str.compare_first('t', in_str_cursor)) || 
		    (in_str.compare_first('T', in_str_cursor)))
		{
			translate_string = TRUE;
			in_str_cursor++;
			in_str.parse_token('{', in_str_cursor, translate_function);
			// back up cursor one to the '{'
			in_str_cursor--;
		}
		else if (in_str.compare_first('_', in_str_cursor))
		{
			if (make_spaces_underbars || remove_all_white_space
				|| make_corba_complient)
			{
				GS_string warning_str;                    
				warning_str  = "Can not specify more than one of '_', 'r', or 'o'  in the\n";
				warning_str += "    substitution control:\n";
				warning_str += "        '_' causes conversion of white space to '_' characters\n";
				warning_str += "        'r' causes removal of white space\n";
				warning_str += "        'o' causes removal of non-alpha-numeric characters\n";
				GS_ui::inform (UI_INFORM__ERROR, warning_str);
			}
			
			make_spaces_underbars = TRUE;
		}
		else if ((in_str.compare_first('r', in_str_cursor)) || 
			     (in_str.compare_first('R', in_str_cursor)))
		{
			if (make_spaces_underbars || remove_all_white_space
				|| make_corba_complient)
			{
				GS_string warning_str;                    
				warning_str  = "Can not specify more than one of '_', 'r', or 'o'  in the\n";
				warning_str += "    substitution control:\n";
				warning_str += "        '_' causes conversion of white space to '_' characters\n";
				warning_str += "        'r' causes removal of white space\n";
				warning_str += "        'o' causes removal of non-alpha-numeric characters\n";
				GS_ui::inform (UI_INFORM__ERROR, warning_str);
			}
			
			remove_all_white_space = TRUE;
		}
		else if ((in_str.compare_first('c', in_str_cursor)) 
			  || (in_str.compare_first('C', in_str_cursor)))
		{
			if (make_words_begin_capital || make_all_lower_case
				|| make_all_upper_case || make_corba_complient)
			{
				GS_string warning_str;                    
				warning_str  = "Can not specify more than one of 'c', 'l', 'u', or 'o'  in the\n";
				warning_str += "    substitution control:\n";
				warning_str += "        'c' causes each word to be capitalized\n";
				warning_str += "        'l' causes all letters to be make lower case\n";
				warning_str += "        'u' causes all letters to be make upper case\n";
				warning_str += "        'o' causes removal of non-alpha-numeric characters\n";
				GS_ui::inform (UI_INFORM__ERROR, warning_str);
			}
			
			make_words_begin_capital = TRUE;
		}
		else if ((in_str.compare_first('l', in_str_cursor)) || (in_str.compare_first('L', in_str_cursor)))
		{
			if (make_words_begin_capital || make_all_lower_case
				|| make_all_upper_case || make_corba_complient)
			{
				GS_string warning_str;                    
				warning_str  = "Can not specify more than one of 'c', 'l', 'u', or 'o'  in the\n";
				warning_str += "    substitution control:\n";
				warning_str += "        'c' causes each word to be capitalized\n";
				warning_str += "        'l' causes all letters to be make lower case\n";
				warning_str += "        'u' causes all letters to be make upper case\n";
				warning_str += "        'o' causes each word following the first word to be capitalized\n";
				GS_ui::inform (UI_INFORM__ERROR, warning_str);
			}
			
			make_all_lower_case = TRUE;
		}
		else if ((in_str.compare_first('o', in_str_cursor)) || (in_str.compare_first('O', in_str_cursor)))
		{
			if (make_words_begin_capital || make_all_lower_case
				|| make_all_upper_case || make_corba_complient)
			{
				GS_string warning_str;                    
				warning_str  = "Can not specify more than one of 'c', 'l', 'u', or 'o'  in the\n";
				warning_str += "    substitution control:\n";
				warning_str += "        'c' causes each word to be capitalized\n";
				warning_str += "        'l' causes all letters to be make lower case\n";
				warning_str += "        'u' causes all letters to be make upper case\n";
				warning_str += "        'o' causes each word following the first word to be capitalized\n";
				GS_ui::inform (UI_INFORM__ERROR, warning_str);
			}
			
			make_corba_complient = TRUE;
		}
		else if ((in_str.compare_first('u', in_str_cursor)) || (in_str.compare_first('U', in_str_cursor)))
		{
			if (make_words_begin_capital || make_all_lower_case
				|| make_all_upper_case || make_corba_complient)
			{
				GS_string warning_str;                    
				warning_str  = "Can not specify more than one of 'c', 'l', 'u', or 'o'  in the\n";
				warning_str += "    substitution control:\n";
				warning_str += "        'c' causes each word to be capitalized\n";
				warning_str += "        'l' causes all letters to be make lower case\n";
				warning_str += "        'u' causes all letters to be make upper case\n";
				warning_str += "        'o' causes each word following the first word to be capitalized\n";
				GS_ui::inform (UI_INFORM__ERROR, warning_str);
			}
			
			make_all_upper_case = TRUE;
		}
		else
		{
			Description error_str;
			error_str  = "Unrecognized substitution control character '\n";
			vchar tmp_str[2];
			tmp_str[0] = in_str.char_at (in_str_cursor);
			tmp_str[1] = 0;
			error_str += tmp_str;
			error_str += "' specified - legal characters are:\n";
			error_str += "        '_' causes conversion of white space to '_' characters\n";
			error_str += "        'r' causes removal of white space\n";
			error_str += "        'c' causes each word to be capitalized\n";
			error_str += "        'l' causes all letters to be make lower case\n";
			error_str += "        'u' causes all letters to be make upper case\n";
			error_str += "        'o' causes each word following the first word to be capitalized\n";
			error_str += "                AND removal of white space AND '_' characters\n";
			error_str += "\n";
			error_str += "    OR\n";
			error_str += "        '$' character not used as part of a substitution variable\n";
			error_str += "            If you want a single '$' character in the generated output,\n";
			error_str += "            then use the '$$' character sequence.\n";
			GS_ui::inform (UI_INFORM__ERROR, error_str);
			return FALSE;
		}
		in_str_cursor++;
	}			
	return TRUE;
}

Description&
GS_substitution::substitute_string
(const Description& p_in_str, t_boolean p_is_literal_text_line)

{
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_BEGIN, (L_log_string,
		"Begin  GS_substitution::substitute_string () Entered" ));
	
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_BEGIN, (L_log_string,
		"Begin  GS_substitution::substitute_string ()...p_in_str = %s, p_is_literal_text_line = %d",
		p_in_str.char_ptr(), p_is_literal_text_line ));
	
static const unsigned long temp_buffer_size = 1048576;
static Description out_str(temp_buffer_size);
	
    out_str.truncate(0);

    t_uint in_str_cursor = 0;
	
    //  Pass through any leading white space.
    //
    while ( (in_str_cursor < p_in_str.length ()) &&
            (vcharIsWhiteSpace (p_in_str.char_at (in_str_cursor))) )
    {
        out_str.append_char(p_in_str.char_at (in_str_cursor));
        in_str_cursor++;
    }
    
    
    if (p_is_literal_text_line)
    {
		if ((p_in_str.length () > (in_str_cursor + 1))
			&& ( p_in_str.compare_first('.', in_str_cursor) )
			&& ( p_in_str.compare_first('.', in_str_cursor + 1) ))
		{
			//  The first characters of the line are '..' - this should be
			//    interpreted as a single '.' character.  Skip over the first
			//    '.' character so only the second '.' character is placed in
			//    the substituted string.
			//
			in_str_cursor++;
		}
    }
    
    
    while ((in_str_cursor < p_in_str.length ()) && 
		(!p_in_str.compare_first('\0', in_str_cursor)) )
    {
        if (p_in_str.compare_first('$', in_str_cursor))
        {
            in_str_cursor++;
            if (p_in_str.compare_first('$', in_str_cursor))
            {
                //  The character sequence '$$' indicates that a single '$'
                //    character should be passed through to the output
                //    string.
                //
                static vchar dollar_sign = vcharFromASCII('$');
                out_str.append_char(dollar_sign);
            }
            else
            {
                //  We have encountered a substitution variable.
                //
                t_boolean make_spaces_underbars = FALSE;
                t_boolean remove_all_white_space = FALSE;
                t_boolean make_words_begin_capital = FALSE;
                t_boolean make_all_lower_case = FALSE;
                t_boolean make_all_upper_case = FALSE;
                t_boolean make_corba_complient = FALSE;
				t_boolean translate_string = FALSE;
				Description translation_function;

				// Parse the letters between the '$' and '{'
				t_boolean format_ok = get_substitution_format( 
					p_in_str, in_str_cursor, 
					make_spaces_underbars,
		            remove_all_white_space,
			        make_words_begin_capital,
				    make_all_lower_case,
					make_all_upper_case,
					make_corba_complient,
					translate_string, translation_function);

				if ( !format_ok )
				{
					// Error message already output
                    out_str.truncate(0);
					return out_str;
				}

                if (in_str_cursor >= p_in_str.length ())
                {
                    GS_string error_str;
                    error_str  = "'$' character not used as part of a substitution variable\n";
                    error_str += "    If you want a single '$' character in the generated output,\n";
                    error_str += "    then use the '$$' character sequence.\n";
                    GS_ui::inform (UI_INFORM__ERROR, error_str);
                }
				
				
                //  Skip over the '{' character.
                //    
                in_str_cursor++;

				// var_str contains everything between '{' and '}'

				t_uint var_str_cursor = 0;
				Description var_str;
                p_in_str.parse_token ('}', in_str_cursor, var_str, TRUE );
				if (!p_in_str.compare_first('}', in_str_cursor))
				{
					GS_ui::inform (UI_INFORM__ERROR,
						GS_string("Missing '}' at end of Substitution Variable."));
				}
				
				
				Description var_output_str;
				
				
				Description var_name_str;
                var_str.parse_token ('.', var_str_cursor, var_name_str, TRUE );
				if (var_str.compare_first('.', var_str_cursor))
				{
					// var_name_str started with <inst_ref_var> '.'
					//    or <inst_chain> '.'
					//    or <frag_ref_var> '.'
					Description upper_case_var_name_str (var_name_str);
					upper_case_var_name_str.convert_to_upper_case ();
					
					var_str_cursor++;
					Description var_rest_str;
                    var_str.parse_to_end (var_str_cursor, var_rest_str);
					t_uint var_rest_cursor = 0;
					Description var_attr_name_str;
                    var_rest_str.parse_token (':', var_rest_cursor, var_attr_name_str);
					Description var_keyword_str;
					t_uint var_keyword_cursor = 0;

					// is there a ':' <parse_keyword> at the end?
					if (var_rest_str.compare_first(':', var_rest_cursor))
					{
						var_rest_cursor++;
						var_rest_str.parse_to_end (var_rest_cursor, var_keyword_str);
					}
					
					if (upper_case_var_name_str == info_string)
					{
						var_attr_name_str.convert_to_upper_case ();
						built_in_info_substitutions( var_attr_name_str, 
							var_output_str );
					}
					else if (GS_stack::find_frag_ref_var_ptr (var_name_str))
					{
						// <frag_ref_var> . <attribute>
						I_frag_ref_var* frag_ref_var_ptr
							= GS_stack::find_frag_ref_var_ptr (var_name_str);
						I_var* attr_var_ptr = frag_ref_var_ptr->
							get_attr_var_ptr (var_attr_name_str);
						if (attr_var_ptr)
						{
							var_output_str = attr_var_ptr->get_value_str ();
						}
						else
						{
							Description error_str;
							error_str  = "Fragment Attribute '";
							error_str += var_attr_name_str;
							error_str += "' Undefined.\n\tDid you remove the 'attr_' from this attribute name?";
							GS_ui::inform (UI_INFORM__ERROR, error_str);
						}
					}
					else
					{
						// it's either <inst_ref_var> '.'
						//    or <inst_chain> '.'
						Description inst_var_name_str;
						t_boolean using_chain = FALSE;
						t_boolean error_in_chain = FALSE;
						I_object_inst_ref_var* inst_var_ptr =
							GS_stack::find_object_inst_ref_var_ptr
							(var_name_str);
						if (inst_var_ptr)
						{
							// <inst_ref_var> '.' <attribute>
							inst_var_name_str = var_name_str;
						}
						else
						{
							// treat it as a chain.  If it works,
							// then is was a chain, otherwise it's an error.
							inst_var_name_str = "__SELECTED__";
							using_chain = TRUE;
							if (! GS_select::select_one_any__related_by
								("ONE", inst_var_name_str, var_name_str, ""))
							{
								Description err_msg("Substitution Variable ");
								err_msg += var_name_str;
								err_msg += " not Recognized";
								err_msg += " - tried as last resort to treat as Instance Chain '";
								GS_ui::inform (UI_INFORM__ERROR, err_msg);
								error_in_chain = TRUE;
							}
							else
							{
								//  <inst_chain> '.' <attribute>
								inst_var_ptr =
									GS_stack::find_object_inst_ref_var_ptr
									(inst_var_name_str);
							}
						}
						
						if (! error_in_chain)
						{
							I_var* attr_var_ptr = inst_var_ptr->
								get_attr_var_ptr (var_attr_name_str);
							if (attr_var_ptr)
							{
								var_output_str = attr_var_ptr->get_value_str ();
							}
							else
							{
								Description error_str;
								error_str  = "Object Attribute '";
								error_str += var_attr_name_str;
								error_str += "' Undefined.";
								GS_ui::inform (UI_INFORM__ERROR, error_str);
							}
						}
						
						if (using_chain)
						{
							delete (GS_stack::pop ());
						}
						
						if (var_keyword_str.length() != 0)
						{

							var_keyword_str.append_char(':');
							t_uint var_output_cursor = 0;

							// var_keyword_str contains <keyword>':'
							// search for that in var_output_str
							// ( which should contain the descrip attribute for
							//   the object of concern)
                            Description dummy;
							var_output_str.parse_token (var_keyword_str, var_output_cursor, dummy);
							if ((var_output_cursor + var_keyword_str.length ())
								>= var_output_str.length ())
							{
								var_output_str = "";
							}
							else
							{
								var_output_cursor += var_keyword_str.length ();
								Description tmp_var_output_str;
                                var_output_str.parse_token ('\n', var_output_cursor, tmp_var_output_str);
								var_output_str = tmp_var_output_str;
							}
						}
					}
				}
				else
				{
					I_var* var_ptr = GS_stack::find_var_ptr (var_name_str);
					if (var_ptr)
					{
						var_output_str = var_ptr->get_value_str ();
					}
					else
					{
						Description error_str;
						error_str  = "Variable '";
						error_str += var_name_str;
						error_str += "' Undefined.";
						GS_ui::inform (UI_INFORM__ERROR, error_str);
					}
				}
				
				
				if (translate_string)
				{
                  // Translate the function name to system code characters
                  char *translate_function_system_code =
                    (char *)vcharExportAlloc(
                       vcharScribeSystemExport(
                          translation_function.char_ptr()));

                  // Translate the string to system code characters
                  char *translate_string_system_code =
                    (char *)vcharExportAlloc(
                       vcharScribeSystemExport(
                          var_output_str.char_ptr()));

                  // Invoke the translate function. The answer is returned
                  // in system code characters
                  const char *ans_str_system_code =
                    pt_TranslateString( GS_substitution::translate_parm,
                                        translate_function_system_code,
                                        translate_string_system_code );

                  // Translate the answer from system code characters to
                  // Unicode (vchar)
                  vstr *ans_str_vstr =
                    vstrCloneScribed(vcharScribeSystem(ans_str_system_code));
                  var_output_str = (vchar *)ans_str_vstr;

                  // Free all the strings used in the process
                  vstrDestroy(ans_str_vstr);
                  vcharExportFree(translate_function_system_code);
                  vcharExportFree(translate_string_system_code);
				}

				if (make_words_begin_capital)
				{
					var_output_str.make_words_capital();
				}
				
				if (make_corba_complient)
				{
					var_output_str.make_corba_compliant();
				}
				
				if (make_all_lower_case)
				{
					var_output_str.convert_to_lower_case ();
				}
				
				if (make_all_upper_case)
				{
					var_output_str.convert_to_upper_case ();
				}
				
				if (make_spaces_underbars)
				{
					var_output_str.make_spaces_underbars();
				}
				
				if (remove_all_white_space)
				{
					var_output_str.remove_all_white_space();
				}
				
				out_str += var_output_str;
			}
        }
		else if ((! p_is_literal_text_line) && (p_in_str.compare_first('\\', in_str_cursor)))
		{
			//  Current character is a backslash character in a quoted string.
			//    Check for the '\n' or the '\t' character sequence - if found,
			//    put in a new-line or tab.
			//
			if (p_in_str.compare_first('n', in_str_cursor + 1))
			{
				in_str_cursor++;
				out_str.append_char('\n');
			}
			else if (p_in_str.compare_first('t', in_str_cursor + 1))
			{
				in_str_cursor++;
				out_str.append_char('\t');
			}
			else
			{
				out_str.append_char(p_in_str.char_at (in_str_cursor));
			}
		}
        else
        {
            out_str.append_char(p_in_str.char_at (in_str_cursor));
        }
        
        
        in_str_cursor++;
    }
    
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		"End  GS_substitution::substitute_string ()...out_str = %s",
		out_str.char_ptr() ));
	
    
    return out_str;
}

//
// Formatting information for emacs
//
// Local Variables:
// tab-width:4
// End:
//

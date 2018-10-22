/*========================================================================
 *
 * File:      $RCSfile: gs_func.cc,v $
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
#include <stdlib.h>
#include <iostream.h>
#include <fstream.h>

#include <gs_func.hh>
#include <gs_stack.hh>
#include <gs_ui.hh>

#include <u_trace.hh>
#include <u_error.hh>
#include <u_cmd.hh>
#include <u_env.hh>




static GS_func_def* s_func_def [GS_MAX_NUM_FUNC_DEFS];
static t_uint s_num_func_defs = 0;
static char env_str [2048];
static GS_string last_found_func_name_str;
static GS_func_def* last_found_func_def_ptr = 0;




GS_func_def*
GS_func_def::find_func_def_ptr (const GS_string& p_func_name_str)

{
    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_BEGIN, (L_log_string,
	"Begin  GS_func_def::find_func_def_ptr ():  p_func_name_str = %S",
	vcharScribeASCII(p_func_name_str.char_ptr ()) ));


    //  Do not repeat the search if the last one found is the one which
    //    is being looked for.
    //
    if (last_found_func_name_str == p_func_name_str)
    {
	return last_found_func_def_ptr;
    }


    for (t_uint i = 0;
        (i < s_num_func_defs) && (i < GS_MAX_NUM_FUNC_DEFS);
        i++)
    {
        if (s_func_def [i])
        {
            if (s_func_def [i]->m_func_name_str == p_func_name_str)
            {
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_BEGIN, (L_log_string,
		    "Debug GS_func_def::find_func_def_ptr ()...found 0x%x, i = %d",
		    s_func_def [i], i ));

		last_found_func_name_str = p_func_name_str;
		last_found_func_def_ptr = s_func_def [i];
                return s_func_def [i];
            }
        }
        else
        {
            LOG_ERROR ((L_log_string,
		"GS_func_def::find_func_def_ptr ():  Found a NULL pointer for a valid function definition."));
        }
    }
    
    
    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	"End  GS_func_def::find_func_def_ptr ()...returning 0" ));
    return 0;
}



streampos
GS_func_def::get_start_char_num (const GS_string& p_func_name_str)

{
    GS_func_def* func_def_ptr = find_func_def_ptr (p_func_name_str);

    if (func_def_ptr)
    {
        return func_def_ptr->m_start_char_num;
    }
    
    return 0;
}



void
GS_func_def::set_start_char_num
    (const GS_string& p_func_name_str, streampos p_start_char_num)

{
    GS_func_def* func_def_ptr = find_func_def_ptr (p_func_name_str);

    if (func_def_ptr)
    {
        func_def_ptr->m_start_char_num = p_start_char_num;
    }
}



t_uint
GS_func_def::get_start_line_num (const GS_string& p_func_name_str)

{
    GS_func_def* func_def_ptr = find_func_def_ptr (p_func_name_str);

    if (func_def_ptr)
    {
        return func_def_ptr->m_start_line_num;
    }
    
    return 0;
}



void
GS_func_def::set_start_line_num
    (const GS_string& p_func_name_str, t_uint p_start_line_num)

{
    GS_func_def* func_def_ptr = find_func_def_ptr (p_func_name_str);

    if (func_def_ptr)
    {
        func_def_ptr->m_start_line_num = p_start_line_num;
    }
}




GS_string
GS_func_def::get_arch_file_name_str (const GS_string& p_func_name_str)

{
    GS_func_def* func_def_ptr = find_func_def_ptr (p_func_name_str);

    if (func_def_ptr)
    {
        return func_def_ptr->m_arch_file_name_str;
    }
    
    return "";
}




t_uint
GS_func_def::get_num_formal_param (const GS_string& p_func_name_str)

{
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_BEGIN, (L_log_string,
			"Begin GS_func_def::get_num_formal_param (). p_func_name_str = %S",
			vcharScribeASCII(p_func_name_str.char_ptr()) ));

    GS_func_def* func_def_ptr = find_func_def_ptr (p_func_name_str);

    if (func_def_ptr)
    {
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_BEGIN, (L_log_string,
			"Debug GS_func_def::get_num_formal_param ()...returning %d",
			func_def_ptr->m_num_formal_param ));

        return func_def_ptr->m_num_formal_param;
    }
    
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		"End GS_func_def::get_num_formal_param ()...returning 0" ));

    return 0;
}




GS_string
GS_func_def::get_formal_param_name_str (const GS_string& p_func_name_str,
    t_uint p_formal_param_num)

{
    GS_func_def* func_def_ptr = find_func_def_ptr (p_func_name_str);

    if (func_def_ptr)
    {
        if (p_formal_param_num < func_def_ptr->m_num_formal_param)
        {
            return func_def_ptr->
		m_formal_param [p_formal_param_num].m_formal_param_name_str;
        }
            
        LOG_ERROR ((L_log_string,
	    "GS_func_def::get_formal_param_name_str ():  Requesting information about a formal parameter beyond the number of formal parameters for function '%S'.",
                    vcharScribeASCII(p_func_name_str.char_ptr ()) ));
        return "";
    }
    
    return "";
}





t_boolean
GS_func_def::is_formal_param_inst_ref (const GS_string& p_func_name_str,
    t_uint p_formal_param_num)

{
    GS_func_def* func_def_ptr = find_func_def_ptr (p_func_name_str);

    if (func_def_ptr)
    {
        if (p_formal_param_num < func_def_ptr->m_num_formal_param)
        {
            return (func_def_ptr->
		m_formal_param [p_formal_param_num].m_param_type
                == GS_func_param_def::PARAM_INST_REF) ? TRUE : FALSE;
        }
            
        LOG_ERROR ((L_log_string,
	    "GS_func_def::is_formal_param_inst ():  Requesting information about a formal parameter beyond the number of formal parameters for function '%S'",
                    vcharScribeASCII(p_func_name_str.char_ptr ()) ));
        return FALSE;
    }
    
    GS_ui::inform (UI_INFORM__ERROR,
	GS_string ("Undefined function '") + p_func_name_str + "'.");
    return FALSE;
}





t_boolean
GS_func_def::is_formal_param_inst_ref_set (const GS_string& p_func_name_str,
    t_uint p_formal_param_num)

{
    GS_func_def* func_def_ptr = find_func_def_ptr (p_func_name_str);

    if (func_def_ptr)
    {
        if (p_formal_param_num < func_def_ptr->m_num_formal_param)
        {
            return (func_def_ptr->
		m_formal_param [p_formal_param_num].m_param_type
                == GS_func_param_def::PARAM_INST_REF_SET) ? TRUE : FALSE;
        }
            
        LOG_ERROR ((L_log_string,
	    "GS_func_def::is_formal_param_inst_set ():  Requesting information about a formal parameter beyond the number of formal parameters for function '%S'",
	    vcharScribeASCII(p_func_name_str.char_ptr ()) ));
        return FALSE;
    }
    
    GS_ui::inform (UI_INFORM__ERROR,
	GS_string ("Undefined function '") + p_func_name_str + "'.");
    return FALSE;
}





t_boolean
GS_func_def::is_formal_param_frag_ref (const GS_string& p_func_name_str,
    t_uint p_formal_param_num)

{
    GS_func_def* func_def_ptr = find_func_def_ptr (p_func_name_str);

    if (func_def_ptr)
    {
        if (p_formal_param_num < func_def_ptr->m_num_formal_param)
        {
            return (func_def_ptr->m_formal_param [p_formal_param_num].m_param_type
                == GS_func_param_def::PARAM_FRAG_REF) ? TRUE : FALSE;
        }
            
        LOG_ERROR ((L_log_string,
	    "GS_func_def::is_formal_param_frag ():  Requesting information about a formal parameter beyond the number of formal parameters for function '%S'",
	    vcharScribeASCII(p_func_name_str.char_ptr ()) ));
        return TRUE;
    }
    
    GS_ui::inform (UI_INFORM__ERROR,
	GS_string ("Undefined function '") + p_func_name_str + "'.");
    return TRUE;
}




t_boolean
GS_func_def::is_formal_param_boolean (const GS_string& p_func_name_str,
    t_uint p_formal_param_num)

{
    GS_func_def* func_def_ptr = find_func_def_ptr (p_func_name_str);

    if (func_def_ptr)
    {
        if (p_formal_param_num < func_def_ptr->m_num_formal_param)
        {
            return (func_def_ptr->
		m_formal_param [p_formal_param_num].m_param_type
                == GS_func_param_def::PARAM_BOOLEAN) ? TRUE : FALSE;
        }
            
        LOG_ERROR ((L_log_string,
	    "GS_func_def::is_formal_param_boolean ():  Requesting information about a formal parameter beyond the number of formal parameters for function '%S'",
	    vcharScribeASCII(p_func_name_str.char_ptr ()) ));
        return FALSE;
    }
    
    GS_ui::inform (UI_INFORM__ERROR,
	GS_string ("Undefined function '") + p_func_name_str + "'.");
    return FALSE;
}






t_boolean
GS_func_def::is_formal_param_integer (const GS_string& p_func_name_str,
    t_uint p_formal_param_num)

{
    GS_func_def* func_def_ptr = find_func_def_ptr (p_func_name_str);

    if (func_def_ptr)
    {
        if (p_formal_param_num < func_def_ptr->m_num_formal_param)
        {
            return (func_def_ptr->
		m_formal_param [p_formal_param_num].m_param_type
                == GS_func_param_def::PARAM_INTEGER) ? TRUE : FALSE;
        }
            
        LOG_ERROR ((L_log_string,
	    "GS_func_def::is_formal_param_integer ():  Requesting information about a formal parameter beyond the number of formal parameters for function '%S'",
	    vcharScribeASCII(p_func_name_str.char_ptr ()) ));
        return FALSE;
    }
    
    GS_ui::inform (UI_INFORM__ERROR,
	GS_string ("Undefined function '") + p_func_name_str + "'.");
    return FALSE;
}





t_boolean
GS_func_def::is_formal_param_real (const GS_string& p_func_name_str,
    t_uint p_formal_param_num)

{
    GS_func_def* func_def_ptr = find_func_def_ptr (p_func_name_str);

    if (func_def_ptr)
    {
        if (p_formal_param_num < func_def_ptr->m_num_formal_param)
        {
            return (func_def_ptr->
		m_formal_param [p_formal_param_num].m_param_type
                == GS_func_param_def::PARAM_REAL) ? TRUE : FALSE;
        }
            
        LOG_ERROR ((L_log_string,
	    "GS_func_def::is_formal_param_real ():  Requesting information about a formal parameter beyond the number of formal parameters for function '%S'",
	    vcharScribeASCII(p_func_name_str.char_ptr ()) ));
        return FALSE;
    }
    
    GS_ui::inform (UI_INFORM__ERROR,
	GS_string ("Undefined function '") + p_func_name_str + "'.");
    return FALSE;
}





t_boolean
GS_func_def::is_formal_param_string (const GS_string& p_func_name_str,
    t_uint p_formal_param_num)

{
    GS_func_def* func_def_ptr = find_func_def_ptr (p_func_name_str);

    if (func_def_ptr)
    {
        if (p_formal_param_num < func_def_ptr->m_num_formal_param)
        {
            return (func_def_ptr->
		m_formal_param [p_formal_param_num].m_param_type
                == GS_func_param_def::PARAM_STRING) ? TRUE : FALSE;
        }
            
        LOG_ERROR ((L_log_string,
	    "GS_func_def::is_formal_param_string ():  Requesting information about a formal parameter beyond the number of formal parameters for function '%S'",
	    vcharScribeASCII(p_func_name_str.char_ptr ()) ));
        return FALSE;
    }
    
    GS_ui::inform (UI_INFORM__ERROR,
	GS_string ("Undefined function '") + p_func_name_str + "'.");
    return FALSE;
}



                            
t_boolean
GS_func_def::create_func_def (const GS_string& p_func_name_str,
    streampos p_start_char_num,
    t_uint p_start_line_num,
    const GS_string& p_arch_file_name_str)

{
    if (s_num_func_defs < (GS_MAX_NUM_FUNC_DEFS - 1))
    {
        s_func_def [s_num_func_defs] = new GS_func_def (p_func_name_str,
            p_start_char_num, p_start_line_num, p_arch_file_name_str);
        s_num_func_defs++;
        return TRUE;
    }
    
    
    GS_ui::inform (UI_INFORM__ERROR,
	GS_string ("GS_func_def::create_func_def ():  Maximum number of functions '")
	+ p_func_name_str + "' already defined.");
    return FALSE;
}




void
GS_func_def::add_param_to_func_def (const GS_string& p_func_name_str,
    GS_func_param_def::e_param_type p_param_type,
    const GS_string& p_formal_param_name_str)
                            
{
    GS_func_def* func_def_ptr = find_func_def_ptr (p_func_name_str);

    if (func_def_ptr)
    {
        if (func_def_ptr->m_num_formal_param
	    <
	    (GS_MAX_NUM_PARAMS_PER_FUNC_DEF - 1))
        {
            func_def_ptr->m_formal_param [func_def_ptr->m_num_formal_param].
		m_param_type = p_param_type;
            func_def_ptr->m_formal_param [func_def_ptr->m_num_formal_param].
		m_formal_param_name_str = p_formal_param_name_str;
            func_def_ptr->m_num_formal_param++;
            return;
        }
            
        GS_ui::inform (UI_INFORM__ERROR,
	    GS_string ("GS_func_def::add_param_to_func_def ():  Maximum number of parameters already defined for function '")
	    + p_func_name_str + "'.");
        return;
    }
    
    
    LOG_ERROR ((L_log_string,
	"GS_func_def::add_param_to_func_def ():  Function '%S' Undefined",
	vcharScribeASCII(p_func_name_str.char_ptr ()) ));
    return;
}




GS_func_def::GS_func_def (const GS_string& p_func_name_str,
    streampos p_start_char_num,
    t_uint p_start_line_num,
    const GS_string& p_arch_file_name_str)

{
    m_func_name_str = p_func_name_str;
    m_num_formal_param = 0;
    m_start_char_num = p_start_char_num;
    m_start_line_num = p_start_line_num;
    m_arch_file_name_str = p_arch_file_name_str;
    m_is_predefined = FALSE;
}




GS_func_def::~GS_func_def ()

{
}




GS_func_param_def::GS_func_param_def ()

{
    m_param_type = PARAM_UNASSIGNED;
    m_formal_param_name_str = "";
}




GS_func_param_def::~GS_func_param_def ()

{
}




void
GS_func_def::init ()

{
    s_num_func_defs = 0;


    s_func_def [s_num_func_defs] = new GS_func_def ("GET_ENV_VAR", 0, 0, "");
    s_func_def [s_num_func_defs]->m_is_predefined = TRUE;
    s_func_def [s_num_func_defs]->m_num_formal_param = 0;
    s_func_def [s_num_func_defs]->m_formal_param
	[s_func_def [s_num_func_defs]->m_num_formal_param].
	m_param_type = GS_func_param_def::PARAM_STRING;
    s_func_def [s_num_func_defs]->m_formal_param
	[s_func_def [s_num_func_defs]->m_num_formal_param].
	m_formal_param_name_str = "env_var_name";
    s_func_def [s_num_func_defs]->m_num_formal_param++;
    s_num_func_defs++;


    s_func_def [s_num_func_defs] = new GS_func_def ("PUT_ENV_VAR", 0, 0, "");
    s_func_def [s_num_func_defs]->m_is_predefined = TRUE;
    s_func_def [s_num_func_defs]->m_num_formal_param = 0;
    s_func_def [s_num_func_defs]->m_formal_param
	[s_func_def [s_num_func_defs]->m_num_formal_param].
	m_param_type = GS_func_param_def::PARAM_STRING;
    s_func_def [s_num_func_defs]->m_formal_param
	[s_func_def [s_num_func_defs]->m_num_formal_param].
	m_formal_param_name_str = "env_var_name";
    s_func_def [s_num_func_defs]->m_num_formal_param++;
    s_func_def [s_num_func_defs]->m_formal_param
	[s_func_def [s_num_func_defs]->m_num_formal_param].
	m_param_type = GS_func_param_def::PARAM_STRING;
    s_func_def [s_num_func_defs]->m_formal_param
	[s_func_def [s_num_func_defs]->m_num_formal_param].
	m_formal_param_name_str = "env_var_value";
    s_func_def [s_num_func_defs]->m_num_formal_param++;
    s_num_func_defs++;


    s_func_def [s_num_func_defs] = new GS_func_def ("SHELL_COMMAND", 0, 0, "");
    s_func_def [s_num_func_defs]->m_is_predefined = TRUE;
    s_func_def [s_num_func_defs]->m_num_formal_param = 0;
    s_func_def [s_num_func_defs]->m_formal_param
	[s_func_def [s_num_func_defs]->m_num_formal_param].
	m_param_type = GS_func_param_def::PARAM_STRING;
    s_func_def [s_num_func_defs]->m_formal_param
	[s_func_def [s_num_func_defs]->m_num_formal_param].
	m_formal_param_name_str = "command";
    s_func_def [s_num_func_defs]->m_num_formal_param++;
    s_num_func_defs++;


    s_func_def [s_num_func_defs] = new GS_func_def ("FILE_READ", 0, 0, "");
    s_func_def [s_num_func_defs]->m_is_predefined = TRUE;
    s_func_def [s_num_func_defs]->m_num_formal_param = 0;
    s_func_def [s_num_func_defs]->m_formal_param
	[s_func_def [s_num_func_defs]->m_num_formal_param].
	m_param_type = GS_func_param_def::PARAM_STRING;
    s_func_def [s_num_func_defs]->m_formal_param
	[s_func_def [s_num_func_defs]->m_num_formal_param].
	m_formal_param_name_str = "filename";
    s_func_def [s_num_func_defs]->m_num_formal_param++;
    s_num_func_defs++;


    s_func_def [s_num_func_defs] = new GS_func_def ("FILE_WRITE", 0, 0, "");
    s_func_def [s_num_func_defs]->m_is_predefined = TRUE;
    s_func_def [s_num_func_defs]->m_num_formal_param = 0;
    s_func_def [s_num_func_defs]->m_formal_param
	[s_func_def [s_num_func_defs]->m_num_formal_param].
	m_param_type = GS_func_param_def::PARAM_STRING;
    s_func_def [s_num_func_defs]->m_formal_param
	[s_func_def [s_num_func_defs]->m_num_formal_param].
	m_formal_param_name_str = "filename";
    s_func_def [s_num_func_defs]->m_num_formal_param++;
    s_func_def [s_num_func_defs]->m_formal_param
	[s_func_def [s_num_func_defs]->m_num_formal_param].
	m_param_type = GS_func_param_def::PARAM_STRING;
    s_func_def [s_num_func_defs]->m_formal_param
	[s_func_def [s_num_func_defs]->m_num_formal_param].
	m_formal_param_name_str = "contents";
    s_func_def [s_num_func_defs]->m_num_formal_param++;
    s_num_func_defs++;


    s_func_def [s_num_func_defs]
	= new GS_func_def ("STRING_TO_INTEGER", 0, 0, "");
    s_func_def [s_num_func_defs]->m_is_predefined = TRUE;
    s_func_def [s_num_func_defs]->m_num_formal_param = 0;
    s_func_def [s_num_func_defs]->m_formal_param
	[s_func_def [s_num_func_defs]->m_num_formal_param].
	m_param_type = GS_func_param_def::PARAM_STRING;
    s_func_def [s_num_func_defs]->m_formal_param
	[s_func_def [s_num_func_defs]->m_num_formal_param].
	m_formal_param_name_str = "string";
    s_func_def [s_num_func_defs]->m_num_formal_param++;
    s_num_func_defs++;


    s_func_def [s_num_func_defs]
	= new GS_func_def ("STRING_TO_REAL", 0, 0, "");
    s_func_def [s_num_func_defs]->m_is_predefined = TRUE;
    s_func_def [s_num_func_defs]->m_num_formal_param = 0;
    s_func_def [s_num_func_defs]->m_formal_param
	[s_func_def [s_num_func_defs]->m_num_formal_param].
	m_param_type = GS_func_param_def::PARAM_STRING;
    s_func_def [s_num_func_defs]->m_formal_param
	[s_func_def [s_num_func_defs]->m_num_formal_param].
	m_formal_param_name_str = "string";
    s_func_def [s_num_func_defs]->m_num_formal_param++;
    s_num_func_defs++;


    s_func_def [s_num_func_defs]
	= new GS_func_def ("INTEGER_TO_STRING", 0, 0, "");
    s_func_def [s_num_func_defs]->m_is_predefined = TRUE;
    s_func_def [s_num_func_defs]->m_num_formal_param = 0;
    s_func_def [s_num_func_defs]->m_formal_param
	[s_func_def [s_num_func_defs]->m_num_formal_param].
	m_param_type = GS_func_param_def::PARAM_INTEGER;
    s_func_def [s_num_func_defs]->m_formal_param
	[s_func_def [s_num_func_defs]->m_num_formal_param].
	m_formal_param_name_str = "integer";
    s_func_def [s_num_func_defs]->m_num_formal_param++;
    s_num_func_defs++;


    s_func_def [s_num_func_defs]
	= new GS_func_def ("REAL_TO_STRING", 0, 0, "");
    s_func_def [s_num_func_defs]->m_is_predefined = TRUE;
    s_func_def [s_num_func_defs]->m_num_formal_param = 0;
    s_func_def [s_num_func_defs]->m_formal_param
	[s_func_def [s_num_func_defs]->m_num_formal_param].
	m_param_type = GS_func_param_def::PARAM_REAL;
    s_func_def [s_num_func_defs]->m_formal_param
	[s_func_def [s_num_func_defs]->m_num_formal_param].
	m_formal_param_name_str = "real";
    s_func_def [s_num_func_defs]->m_num_formal_param++;
    s_num_func_defs++;


    s_func_def [s_num_func_defs]
	= new GS_func_def ("BOOLEAN_TO_STRING", 0, 0, "");
    s_func_def [s_num_func_defs]->m_is_predefined = TRUE;
    s_func_def [s_num_func_defs]->m_num_formal_param = 0;
    s_func_def [s_num_func_defs]->m_formal_param
	[s_func_def [s_num_func_defs]->m_num_formal_param].
	m_param_type = GS_func_param_def::PARAM_BOOLEAN;
    s_func_def [s_num_func_defs]->m_formal_param
	[s_func_def [s_num_func_defs]->m_num_formal_param].
	m_formal_param_name_str = "boolean";
    s_func_def [s_num_func_defs]->m_num_formal_param++;
    s_num_func_defs++;
}




t_boolean
GS_func_def::exec_predefined (const GS_string& p_func_name_str)

{
    GS_func_def* func_def_ptr = find_func_def_ptr (p_func_name_str);
    if ((func_def_ptr) && (is_predefined (p_func_name_str)))
    {
	//  Function is found OK and it is predefined.
	//
	I_frag_ref_var* return_frag_ref_var_ptr
	    = GS_stack::function_get_return_frag_ref_var_ptr ();
	if (return_frag_ref_var_ptr)
	{
	    if (p_func_name_str == "GET_ENV_VAR")
	    {
		t_boolean success_flag = FALSE;
		Description contents_str;
		I_var* name_str_var_ptr
		    = GS_stack::find_var_ptr ("env_var_name");
		if (name_str_var_ptr)
		{
			char *name_str_ASCII = (char *) vcharExportAlloc( 
				vcharScribeASCIIExport(
					name_str_var_ptr->get_value_str ().char_ptr()));
			contents_str = U_env_var::get_value_str (
				name_str_ASCII );
			vcharExportFree( name_str_ASCII );
			if ( contents_str == "" )
			{
				success_flag = FALSE;
			}
			else
			{
				success_flag = TRUE;
			}
		}
		I_string_var* temp_str_var
		    = new I_string_var (contents_str);
		return_frag_ref_var_ptr->
		    add_attr ("attr_result", temp_str_var);
		//  Do not delete temp_str_var since it has been taken
		//    over in the add_attr function.
		I_boolean_var* temp_bool_var
		    = new I_boolean_var (success_flag);
		return_frag_ref_var_ptr->
		    add_attr ("attr_success", temp_bool_var);
		//  Do not delete temp_bool_var since it has been taken
		//    over in the add_attr function.
	    }
	    else if (p_func_name_str == "PUT_ENV_VAR")
	    {
		t_boolean success_flag = FALSE;
		I_var* name_str_var_ptr
		    = GS_stack::find_var_ptr ("env_var_name");
		if (name_str_var_ptr)
		{
		    Description name_str = name_str_var_ptr->get_value_str ();
		    I_var* value_str_var_ptr
			= GS_stack::find_var_ptr ("env_var_value");
		    if (value_str_var_ptr)
		    {
			Description value_str
			    = value_str_var_ptr->get_value_str ();

			char *name_str_ASCII = (char *) vcharExportAlloc( 
				vcharScribeASCIIExport(name_str.char_ptr()));
			char *value_str_ASCII = (char *) vcharExportAlloc( 
				vcharScribeASCIIExport(value_str.char_ptr()));
			if (U_env_var::put_env_var (name_str_ASCII, value_str_ASCII) )
			{
				LOG_ERROR ((L_log_string, "GS_func_def::exec_predefined(): putenv %s failed.", name_str.char_ptr ()));

				success_flag = FALSE;
			}
			else
			{
				success_flag = TRUE;
			}
			vcharExportFree( name_str_ASCII );
			vcharExportFree( value_str_ASCII );

		    }
		}
		I_boolean_var* temp_bool_var
		    = new I_boolean_var (success_flag);
		return_frag_ref_var_ptr->
		    add_attr ("attr_success", temp_bool_var);
		//  Do not delete temp_bool_var since it has been taken
		//    over in the add_attr function.
	    }
	    else if (p_func_name_str == "SHELL_COMMAND")
	    {
		I_var* command_var_ptr = GS_stack::find_var_ptr ("command");
		if (command_var_ptr)
		{
		    Description command_str = command_var_ptr->get_value_str ();
			char *command_str_ASCII = (char *) vcharExportAlloc( 
				vcharScribeASCIIExport(command_str.char_ptr()));
		    int exit_status	= U_shell_cmd::exec_shell_cmd (command_str_ASCII);
			vcharExportFree( command_str_ASCII );

		    I_integer_var* temp_int_var	= new I_integer_var (exit_status);
		    return_frag_ref_var_ptr->
			add_attr ("attr_result", temp_int_var);
		    //  Do not delete temp_int_var since it has been taken
		    //    over in the add_attr function.
		}
	    }
	    else if (p_func_name_str == "FILE_READ")
	    {
		t_boolean success_flag = FALSE;
		Description contents_str;
		I_var* filename_var_ptr
		    = GS_stack::find_var_ptr ("filename");
		if (filename_var_ptr)
		{
		    Description filename_str = filename_var_ptr->get_value_str ();
		    ifstream read_file;
			char *filename_str_ASCII = (char *) vcharExportAlloc( 
				vcharScribeASCIIExport(filename_str.char_ptr()));
		    read_file.open (filename_str_ASCII, ios::nocreate);
		    if (! read_file.good ())
		    {
				Description err_msg ("Unable to open file '");
				err_msg += filename_str;
			    err_msg += "' for reading.";
				GS_ui::inform (UI_INFORM__ERROR, err_msg);
		    }
		    else
		    {
			char line_str [8092];
            vchar line_vstr [8092];
			while (! read_file.eof ())
			{
			    read_file.getline (line_str, 8092);
			    if (! read_file.eof ())
			    {
                  vcharCopyScribed(vcharScribeSystem(line_str), line_vstr);
                  contents_str += line_vstr;
                  contents_str += "\n";
			    }
			}
			read_file.close ();
			success_flag = TRUE;
		    }
			vcharExportFree( filename_str_ASCII );
		}
		I_string_var* temp_str_var = new I_string_var (contents_str);
		return_frag_ref_var_ptr->
		    add_attr ("attr_result", temp_str_var);
		//  Do not delete temp_str_var since it has been taken
		//    over in the add_attr function.
		I_boolean_var* temp_bool_var = new I_boolean_var (success_flag);
		return_frag_ref_var_ptr->
		    add_attr ("attr_success", temp_bool_var);
		//  Do not delete temp_bool_var since it has been taken
		//    over in the add_attr function.
	    }
	    else if (p_func_name_str == "FILE_WRITE")
	    {
		t_boolean success_flag = FALSE;
		I_var* filename_var_ptr
		    = GS_stack::find_var_ptr ("filename");
		if (filename_var_ptr)
		{
		    Description filename_str = filename_var_ptr->get_value_str ();
		    I_var* contents_var_ptr
			= GS_stack::find_var_ptr ("contents");
		    Description contents_str = contents_var_ptr->get_value_str ();
		    ofstream write_file;
			char *filename_str_ASCII = (char *) vcharExportAlloc( 
				vcharScribeASCIIExport(filename_str.char_ptr()));
		    write_file.open (filename_str_ASCII, ios::out);
		    if (! write_file.good ())
		    {
				Description err_msg ("Unable to open file '");
				err_msg += filename_str;
			    err_msg += "' for writing.";
				GS_ui::inform (UI_INFORM__ERROR, err_msg);
		    }
		    else
		    {
			char *contents_str_system = (char *) vcharExportAlloc( 
				vcharScribeSystemExport(contents_str.char_ptr()));
			write_file << contents_str_system << endl;
			write_file.close ();
			vcharExportFree( contents_str_system );
			success_flag = TRUE;
		    }
			vcharExportFree( filename_str_ASCII );
		}
		I_boolean_var* temp_bool_var = new I_boolean_var (success_flag);
		return_frag_ref_var_ptr->
		    add_attr ("attr_success", temp_bool_var);
		//  Do not delete temp_bool_var since it has been taken
		//    over in the add_attr function.
	    }
	    else if (p_func_name_str == "STRING_TO_INTEGER")
	    {
		I_var* string_var_ptr = GS_stack::find_var_ptr ("string");
		if (string_var_ptr)
		{
		    Description string_str = string_var_ptr->get_value_str ();
		    t_int value_int = 0;
			t_boolean exception_occurred = TRUE;
			vexWITH_HANDLING
			{
				value_int = vnumParseInt(string_str.char_ptr(), 0);
				exception_occurred = FALSE;
			} vexON_EXCEPTION {
				
			} vexEND_HANDLING;
			
			if (exception_occurred)
		    {
			GS_ui::inform (UI_INFORM__ERROR,
			    GS_string("Expected integer value in parameter 'string'."));
		    }
		    I_integer_var* temp_int_var
			= new I_integer_var (value_int);
		    return_frag_ref_var_ptr->
			add_attr ("attr_result", temp_int_var);
		    //  Do not delete temp_int_var since it has been taken
		    //    over in the add_attr function.
		}
	    }
	    else if (p_func_name_str == "STRING_TO_REAL")
	    {
		I_var* string_var_ptr = GS_stack::find_var_ptr ("string");
		if (string_var_ptr)
		{
		    Description string_str = string_var_ptr->get_value_str ();
		    t_double value_real = 0.0;
			t_boolean exception_occurred = TRUE;
			vexWITH_HANDLING
			{
				value_real = vnumParseFloat(string_str.char_ptr(), 0);
				exception_occurred = FALSE;
			} vexON_EXCEPTION {
				
			} vexEND_HANDLING;
			
			if (exception_occurred)
		    {
			GS_ui::inform (UI_INFORM__ERROR,
			    GS_string("Expected real value in parameter 'string'."));
		    }
		    I_real_var* temp_real_var
			= new I_real_var (value_real);
		    return_frag_ref_var_ptr->
			add_attr ("attr_result", temp_real_var);
		    //  Do not delete temp_real_var since it has been taken
		    //    over in the add_attr function.
		}
	    }
	    else if (p_func_name_str == "INTEGER_TO_STRING")
	    {
		I_var* temp_var_ptr = GS_stack::find_var_ptr ("integer");
                I_integer_var* integer_var_ptr = 0;
		if (temp_var_ptr)
		{
                    integer_var_ptr = temp_var_ptr->get_integer_var_ptr();
                }

		if (integer_var_ptr)
		{
		    t_long param_integer = integer_var_ptr->get_value();

                    char int_buf[20];
                    sprintf (int_buf, "%ld", param_integer);

		    I_string_var* temp_string_var
			= new I_string_var (int_buf);
		    return_frag_ref_var_ptr->
			add_attr ("attr_result", temp_string_var);
		    //  Do not delete temp_string_var since it has been taken
		    //    over in the add_attr function.
		}
	    }
	    else if (p_func_name_str == "REAL_TO_STRING")
	    {
		I_var* temp_var_ptr = GS_stack::find_var_ptr ("real");
                I_real_var* real_var_ptr = 0;
		if (temp_var_ptr)
		{
                    real_var_ptr = temp_var_ptr->get_real_var_ptr();
                }

		if (real_var_ptr)
		{
		    t_double param_real = real_var_ptr->get_value();

                    char real_buf[255];
                    sprintf (real_buf, "%lf", param_real);

		    I_string_var* temp_string_var
			= new I_string_var (real_buf);
		    return_frag_ref_var_ptr->
			add_attr ("attr_result", temp_string_var);
		    //  Do not delete temp_string_var since it has been taken
		    //    over in the add_attr function.
		}
	    }
	    else if (p_func_name_str == "BOOLEAN_TO_STRING")
	    {
		I_var* temp_var_ptr = GS_stack::find_var_ptr ("boolean");
                I_boolean_var* boolean_var_ptr = 0;
		if (temp_var_ptr)
		{
                    boolean_var_ptr = temp_var_ptr->get_boolean_var_ptr();
                }

		if (boolean_var_ptr)
		{
		    t_boolean param_boolean = boolean_var_ptr->get_value();

		    I_string_var* temp_string_var;
                    if ( param_boolean )
                    {
                      temp_string_var = new I_string_var ("TRUE");
                    }
                    else
                    {
                      temp_string_var = new I_string_var ("FALSE");
                    }

		    return_frag_ref_var_ptr->
			add_attr ("attr_result", temp_string_var);
		    //  Do not delete temp_string_var since it has been taken
		    //    over in the add_attr function.
		}
	    }
	}
	else
	{
	    LOG_ERROR ((L_log_string,
		"GS_func_def::exec_predefined ():  Function '%S' is not on stack.",
		vcharScribeASCII(p_func_name_str.char_ptr ()) ));
	    GS_ui::inform (UI_INFORM__ERROR,
		GS_string ("Function '") + p_func_name_str + "' is not on stack.");
	    return FALSE;
	}
    }
    else
    {
	LOG_ERROR ((L_log_string,
	    "GS_func_def::exec_predefined ():  Function '%S' is not predefined.",
	    vcharScribeASCII(p_func_name_str.char_ptr ()) ));
	GS_ui::inform (UI_INFORM__ERROR,
	    GS_string ("Function '") + p_func_name_str + "' is not predefined.");
	return FALSE;
    }


    return TRUE;
}

//
// Formatting information for emacs
//
// Local Variables:
// tab-width:4
// End:
//

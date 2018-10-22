/*========================================================================
 *
 * File:      $RCSfile: gs_stack.cc,v $
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
#include <gs_func.hh>
#include <gs_ui.hh>
#include <gs_stack.hh>
#include <gs_expr.hh>
#include <i_clock.hh>

#include <u_trace.hh>
#include <u_error.hh>

#include <i_ainst.hh>
#include <i_attr.hh>
#include <i_relate.hh>

// These two variables are referenced by sim_rd.cc
GS_stack_item* s_stack [GS_STACK_SIZE];
t_uint s_stack_offset = 0;





GS_var_si*
GS_stack::find_var_si_ptr (const Description& p_var_name_str)

{
    //  Begin at the top of the stack and check each item until you reach
    //    the bottom of the stack or until you reach a function on the
    //    stack.
    //
    t_uint tmp_stack_offset = s_stack_offset;
    while ((tmp_stack_offset >= 1)
        && (s_stack [tmp_stack_offset]->get_function_si_ptr() == 0))
    {
        GS_var_si* var_si_ptr = s_stack [tmp_stack_offset]->get_var_si_ptr ();
        if (var_si_ptr)
        {
            if (p_var_name_str == var_si_ptr->get_var_name_str ())
            {
                return var_si_ptr;
            }
        }
        --tmp_stack_offset;
    }
    
    return 0;
}





I_var*
GS_stack::find_var_ptr (const Description& p_name_str)

{
    GS_var_si* var_si_ptr = find_var_si_ptr (p_name_str);
    if (var_si_ptr)
    {
	return var_si_ptr->get_var_ptr ();
    }
    
    return 0;
}




I_enumerator_var*
GS_stack::find_enumerator_var_ptr (const Description& p_name_str)

{
    GS_var_si* var_si_ptr = find_var_si_ptr (p_name_str);
    if (var_si_ptr)
    {
	return var_si_ptr->get_enumerator_var_ptr ();
    }
    
    return 0;
}




I_boolean_var*
GS_stack::find_boolean_var_ptr (const Description& p_name_str)

{
    GS_var_si* var_si_ptr = find_var_si_ptr (p_name_str);
    if (var_si_ptr)
    {
	return var_si_ptr->get_boolean_var_ptr ();
    }
    
    return 0;
}





I_integer_var*
GS_stack::find_integer_var_ptr (const Description& p_name_str)

{
    GS_var_si* var_si_ptr = find_var_si_ptr (p_name_str);
    if (var_si_ptr)
    {
	return var_si_ptr->get_integer_var_ptr ();
    }
    
    return 0;
}





I_real_var*
GS_stack::find_real_var_ptr (const Description& p_name_str)

{
    GS_var_si* var_si_ptr = find_var_si_ptr (p_name_str);
    if (var_si_ptr)
    {
	return var_si_ptr->get_real_var_ptr ();
    }
    
    return 0;
}





I_string_var*
GS_stack::find_string_var_ptr (const Description& p_name_str)

{
    GS_var_si* var_si_ptr = find_var_si_ptr (p_name_str);
    if (var_si_ptr)
    {
	return var_si_ptr->get_string_var_ptr ();
    }
    
    return 0;
}





I_unique_id_var*
GS_stack::find_unique_id_var_ptr (const Description& p_name_str)

{
    GS_var_si* var_si_ptr = find_var_si_ptr (p_name_str);
    if (var_si_ptr)
    {
	return var_si_ptr->get_unique_id_var_ptr ();
    }
    
    return 0;
}





I_current_state_var*
GS_stack::find_current_state_var_ptr (const Description& p_name_str)

{
    GS_var_si* var_si_ptr = find_var_si_ptr (p_name_str);
    if (var_si_ptr)
    {
	return var_si_ptr->get_current_state_var_ptr ();
    }
    
    return 0;
}





I_object_inst_ref_var*
GS_stack::find_object_inst_ref_var_ptr (const Description& p_name_str)

{
    GS_var_si* var_si_ptr = find_var_si_ptr (p_name_str);
    if (var_si_ptr)
    {
	return var_si_ptr->get_object_inst_ref_var_ptr ();
    }
    
    return 0;
}





I_object_inst_ref_set_var*
GS_stack::find_object_inst_ref_set_var_ptr (const Description& p_name_str)

{
    GS_var_si* var_si_ptr = find_var_si_ptr (p_name_str);
    if (var_si_ptr)
    {
	return var_si_ptr->get_object_inst_ref_set_var_ptr ();
    }
    
    return 0;
}





I_event_inst_var*
GS_stack::find_event_inst_var_ptr (const Description& p_name_str)

{
    GS_var_si* var_si_ptr = find_var_si_ptr (p_name_str);
    if (var_si_ptr)
    {
	return var_si_ptr->get_event_inst_var_ptr ();
    }
    
    return 0;
}





I_mapping_inst_var*
GS_stack::find_mapping_inst_var_ptr (const Description& p_name_str)

{
    GS_var_si* var_si_ptr = find_var_si_ptr (p_name_str);
    if (var_si_ptr)
    {
	return var_si_ptr->get_mapping_inst_var_ptr ();
    }
    
    return 0;
}





I_mapping_inst_ref_var*
GS_stack::find_mapping_inst_ref_var_ptr (const Description& p_name_str)

{
    GS_var_si* var_si_ptr = find_var_si_ptr (p_name_str);
    if (var_si_ptr)
    {
	return var_si_ptr->get_mapping_inst_ref_var_ptr ();
    }
    
    return 0;
}





I_date_var*
GS_stack::find_date_var_ptr (const Description& p_name_str)

{
    GS_var_si* var_si_ptr = find_var_si_ptr (p_name_str);
    if (var_si_ptr)
    {
	return var_si_ptr->get_date_var_ptr ();
    }
    
    return 0;
}





I_timestamp_var*
GS_stack::find_timestamp_var_ptr (const Description& p_name_str)

{
    GS_var_si* var_si_ptr = find_var_si_ptr (p_name_str);
    if (var_si_ptr)
    {
	return var_si_ptr->get_timestamp_var_ptr ();
    }
    
    return 0;
}





I_timer_inst_ref_var*
GS_stack::find_timer_inst_ref_var_ptr (const Description& p_name_str)

{
    GS_var_si* var_si_ptr = find_var_si_ptr (p_name_str);
    if (var_si_ptr)
    {
	return var_si_ptr->get_timer_inst_ref_var_ptr ();
    }
    
    return 0;
}





I_frag_ref_var*
GS_stack::find_frag_ref_var_ptr (const Description& p_name_str)

{
    GS_var_si* var_si_ptr = find_var_si_ptr (p_name_str);
    if (var_si_ptr)
    {
	return var_si_ptr->get_frag_ref_var_ptr ();
    }
    
    return 0;
}





void
GS_stack::include_begin (streampos p_return_char_num,
    t_uint p_return_line_num,
    const GS_string& p_return_arch_file_name_str,
    const GS_string& p_include_arch_file_name_str)
    
{
    push_ctrl (new GS_include_si (p_return_char_num, p_return_line_num,
        p_return_arch_file_name_str, p_include_arch_file_name_str));
}





t_boolean
GS_stack::include_end (streampos* p_return_char_num_ptr,
    t_uint* p_return_line_num_ptr,
    GS_string* p_return_arch_file_name_str_ptr,
    GS_string* p_include_arch_file_name_str_ptr)

{
    //  Pop everything off the stack to the include which is on the stack.
    //
    while ((s_stack_offset > 0)
        && (! s_stack [s_stack_offset]->get_include_si_ptr ()))
    {
        GS_stack_item* curr_item_ptr = pop ();
        if (curr_item_ptr)
        {
            if (curr_item_ptr->get_var_si_ptr ())
            {
		delete curr_item_ptr;
            }
            else if (curr_item_ptr->get_function_si_ptr ())
            {
		char buffer [20];
		sprintf (buffer, "%u",
		    curr_item_ptr->get_function_si_ptr ()->m_return_line_num);
                GS_ui::inform (UI_INFORM__ERROR, GS_string
		    ("END FUNCTION  expected before End Of File to end\n")
		    + "\tFUNCTION  statement on line " + buffer + ".");
		delete curr_item_ptr;
            }
            else if (curr_item_ptr->get_for_si_ptr ())
            {
		char buffer [20];
		sprintf (buffer, "%u",
		    curr_item_ptr->get_for_si_ptr ()->m_begin_line_num);
                GS_ui::inform (UI_INFORM__ERROR, GS_string
		    ("END FOR  expected before End Of File to end  FOR\n")
		    + "\tstatement on line " + buffer + ".");
		delete curr_item_ptr;
            }
            else if (curr_item_ptr->get_while_si_ptr ())
            {
		char buffer [20];
		sprintf (buffer, "%u",
		    curr_item_ptr->get_while_si_ptr ()->m_begin_line_num);
                GS_ui::inform (UI_INFORM__ERROR, GS_string
		    ("END WHILE  expected before End Of File to end  WHILE\n")
		    + "\tstatement on line " + buffer + ".");
		delete curr_item_ptr;
            }
            else if (curr_item_ptr->get_if_si_ptr ())
            {
                GS_ui::inform (UI_INFORM__ERROR,
		    GS_string("END IF  expected before End Of File."));
		delete curr_item_ptr;
            }
        }
    }
    
    
    if ((s_stack_offset > 0)
        && (s_stack [s_stack_offset]->get_include_si_ptr ()))
    {
        GS_stack_item* curr_item_ptr = pop ();
        if (curr_item_ptr)
        {
            GS_include_si* incl_si_ptr = curr_item_ptr->get_include_si_ptr ();
            if (incl_si_ptr)
            {
                if (p_return_char_num_ptr)
                {
                    *p_return_char_num_ptr = incl_si_ptr->m_return_char_num;
                }
                if (p_return_line_num_ptr)
                {
                    *p_return_line_num_ptr = incl_si_ptr->m_return_line_num;
                }
                if (p_return_arch_file_name_str_ptr)
                {
                    *p_return_arch_file_name_str_ptr
			= incl_si_ptr->m_return_arch_file_name_str;
                }
                if (p_include_arch_file_name_str_ptr)
                {
                    *p_include_arch_file_name_str_ptr
			= incl_si_ptr->m_include_arch_file_name_str;
                }
                
                delete curr_item_ptr;
                return TRUE;
            }
        }
    }

    return FALSE;
}





t_boolean
GS_stack::function_begin (streampos p_return_char_num,
    t_uint p_return_line_num,
    const GS_string& p_return_arch_file_name_str,
    const GS_string& p_return_frag_name_str,
    const GS_string& p_func_name_str,
    GS_var_si p_param [], t_uint p_num_actual_params)

{
    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_BEGIN,
               (L_log_string,
                "Begin:  GS_stack::function_begin (p_return_char_num=%d, p_return_line_num=%d, p_return_arch_file_name_str=\"%S\", p_return_frag_name_str=\"%S\", p_func_name_str=\"%S\", p_param=0x%08x, p_num_actual_params=%d).",
                p_return_char_num,
                p_return_line_num,
                vcharScribeASCII(p_return_arch_file_name_str.char_ptr ()),
                vcharScribeASCII(p_return_frag_name_str.char_ptr ()),
                vcharScribeASCII(p_func_name_str.char_ptr ()),
                p_param,
                p_num_actual_params));


    //  Create a fragment variable for the return variable.
    //
    I_frag_ref_var* return_frag_ref_var_ptr = 0;
    GS_var_si* return_var_si_ptr
	= GS_stack::find_var_si_ptr (p_return_frag_name_str.char_ptr());
    if (return_var_si_ptr)
    {
	//  Return variable already exists on the stack.  Clear that attributes
	//    which are currently defined, but keep the "body" variable.
	//
	return_frag_ref_var_ptr = return_var_si_ptr->get_frag_ref_var_ptr ();
	if (return_frag_ref_var_ptr)
	{
	    return_frag_ref_var_ptr->clear_attrs ( TRUE );
	}
	else
	{
	    GS_ui::inform (UI_INFORM__ERROR,
		GS_string("Attempting to assign Fragment to Non-Fragment Variable."));
	    return FALSE;
	}
    }
    else
    {
	//  Return variable does not yet exist on stack - create one.
	//
	I_frag_ref_var* tmp_frag_ref_var_ptr = new I_frag_ref_var ();
	GS_var_si* return_var_si_ptr
	    = push_var (tmp_frag_ref_var_ptr, p_return_frag_name_str.char_ptr());
	return_frag_ref_var_ptr = (return_var_si_ptr) ?
	    return_var_si_ptr->get_frag_ref_var_ptr () : 0;
    }
    

    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_BEGIN, (L_log_string,
	"Debug:  GS_stack::function_begin ():  return_frag_ref_var_ptr=0x%08x",
	return_frag_ref_var_ptr));

    
    t_uint num_formal_params
	= GS_func_def::get_num_formal_param (p_func_name_str);


    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_BEGIN, (L_log_string,
	"Debug:  GS_stack::function_begin ():  num_formal_params=%d",
	num_formal_params));


    if (num_formal_params != p_num_actual_params)
    {
	GS_ui::inform (UI_INFORM__ERROR,
	    GS_string("Function invoked with incorrect number of parameters - skipping function interpretation - assuming function return is NULL string."));
	return FALSE;
    }


    //  Create the function on the stack.
    //
    push_ctrl (new GS_function_si (return_frag_ref_var_ptr, p_return_char_num,
	p_return_line_num, p_return_arch_file_name_str, p_func_name_str));
    
    
    //  Create the parameters on the stack.
    //
    for (t_uint i = 0;
	i < p_num_actual_params;
        i++)
    {
        if (i >= num_formal_params)
        {
            GS_ui::inform (UI_INFORM__ERROR,
		GS_string("Function invoked with too many parameters - skipping function interpretation - assuming function return is NULL string."));
            function_end ();
            return FALSE;
        }
        
	if (GS_func_def::is_formal_param_inst_ref (p_func_name_str, i))
        {
	    if (! p_param [i].get_object_inst_ref_var_ptr ())
            {
                GS_ui::inform (UI_INFORM__ERROR, GS_string
		    ("Formal Parameter '")
		    + GS_func_def::get_formal_param_name_str (p_func_name_str,i)
                    + "' expects the actual parameter to be an INST_REF - skipping function interpretation - assuming function return is NULL string.");
                function_end ();
                return FALSE;
            }
	    else
	    {
		push_var (p_param [i].get_object_inst_ref_var_ptr (),
		    GS_func_def::get_formal_param_name_str (p_func_name_str,i).char_ptr());
	    }
        }
        else if (GS_func_def::is_formal_param_inst_ref_set (p_func_name_str, i))
        {
	    if (! p_param [i].get_object_inst_ref_set_var_ptr ())
            {
                GS_ui::inform (UI_INFORM__ERROR, GS_string
		    ("Formal Parameter '")
		    + GS_func_def::get_formal_param_name_str (p_func_name_str,i)
                    + "' expects the actual parameter to be an INST_REF_SET - skipping function interpretation - assuming function return is NULL string.");
                function_end ();
                return FALSE;
            }
	    else
	    {
		push_var (p_param [i].get_object_inst_ref_set_var_ptr (),
		    GS_func_def::get_formal_param_name_str (p_func_name_str,i).char_ptr());
	    }
        }
        else if (GS_func_def::is_formal_param_frag_ref (p_func_name_str, i))
        {
	    if (! p_param [i].get_frag_ref_var_ptr ())
            {
                GS_ui::inform (UI_INFORM__ERROR, GS_string
		    ("Formal Parameter '")
		    + GS_func_def::get_formal_param_name_str (p_func_name_str,i)
                    + "' expects the actual parameter to be a FRAG_REF - skipping function interpretation - assuming function return is NULL string.");
                function_end ();
                return FALSE;
            }
	    else
	    {
		push_var (p_param [i].get_frag_ref_var_ptr (),
		    GS_func_def::get_formal_param_name_str (p_func_name_str,i).char_ptr());
	    }
        }
        else if (GS_func_def::is_formal_param_boolean (p_func_name_str, i))
        {
	    if (! p_param [i].get_boolean_var_ptr ())
	    {
                GS_ui::inform (UI_INFORM__ERROR, GS_string
		    ("Formal Parameter '")
		    + GS_func_def::get_formal_param_name_str (p_func_name_str,i)
                    + "' expects the actual parameter to be a BOOLEAN - skipping function interpretation - assuming function return is NULL string.");
                function_end ();
                return FALSE;
	    }
	    else
	    {
		push_var (p_param [i].get_boolean_var_ptr (),
		    GS_func_def::get_formal_param_name_str (p_func_name_str,i).char_ptr());
	    }
        }
        else if (GS_func_def::is_formal_param_integer (p_func_name_str, i))
        {
	    if (! p_param [i].get_integer_var_ptr ())
	    {
                GS_ui::inform (UI_INFORM__ERROR, GS_string
		    ("Formal Parameter '")
		    + GS_func_def::get_formal_param_name_str (p_func_name_str,i)
                    + "' expects the actual parameter to be an INTEGER - skipping function interpretation - assuming function return is NULL string.");
                function_end ();
                return FALSE;
	    }
	    else
	    {
		push_var (p_param [i].get_integer_var_ptr (),
		    GS_func_def::get_formal_param_name_str (p_func_name_str,i).char_ptr());
	    }
        }
        else if (GS_func_def::is_formal_param_real (p_func_name_str, i))
        {
	    if (! p_param [i].get_real_var_ptr ())
	    {
                GS_ui::inform (UI_INFORM__ERROR, GS_string
		    ("Formal Parameter '")
		    + GS_func_def::get_formal_param_name_str (p_func_name_str,i)
                    + "' expects the actual parameter to be a REAL - skipping function interpretation - assuming function return is NULL string.");
                function_end ();
                return FALSE;
	    }
	    else
	    {
		push_var (p_param [i].get_real_var_ptr (),
		    GS_func_def::get_formal_param_name_str (p_func_name_str,i).char_ptr());
	    }
        }
        else if (GS_func_def::is_formal_param_string (p_func_name_str, i))
        {
	    if (! p_param [i].get_string_var_ptr ())
	    {
                GS_ui::inform (UI_INFORM__ERROR, GS_string
		    ("Formal Parameter '")
		    + GS_func_def::get_formal_param_name_str (p_func_name_str,i)
                    + "' expects the actual parameter to be a STRING - skipping function interpretation - assuming function return is NULL string.");
                function_end ();
                return FALSE;
	    }
	    else
	    {
		push_var (p_param [i].get_string_var_ptr (),
		    GS_func_def::get_formal_param_name_str (p_func_name_str,i).char_ptr());
	    }
        }
    }


    if (i < GS_func_def::get_num_formal_param (p_func_name_str))
    {
        GS_ui::inform (UI_INFORM__ERROR,
	    GS_string("Function invoked with too few parameters - skipping function interpretation - assuming function return is NULL string."));
        function_end ();
        return FALSE;
    }
    
    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	"End:  GS_stack::function_begin ()."));

    
    return TRUE;
}





I_frag_ref_var*
GS_stack::function_get_return_frag_ref_var_ptr ()

{
    //  Begin at the top of the stack and check each item until you reach
    //    the bottom of the stack or until you reach a function on the
    //    stack.
    //
    t_uint tmp_stack_offset = s_stack_offset;
    while ((tmp_stack_offset >= 1)
        && (! s_stack [tmp_stack_offset]->get_function_si_ptr ()))
    {
        tmp_stack_offset--;
    }
    
    
    if (s_stack [tmp_stack_offset])
    {
        GS_function_si* func_si_ptr
	    = s_stack [tmp_stack_offset]->get_function_si_ptr ();
        if (func_si_ptr)
        {
	    if (func_si_ptr->m_return_frag_ref_var_ptr)
	    {
		return func_si_ptr->m_return_frag_ref_var_ptr;
	    }
        }
    }

    return 0;
}





t_boolean
GS_stack::function_end (streampos* p_return_char_num_ptr,
    t_uint* p_return_line_num_ptr,
    GS_string* p_return_arch_file_name_str_ptr)

{
    I_frag_ref_var* return_frag_ref_var_ptr
	= function_get_return_frag_ref_var_ptr ();
    if (! return_frag_ref_var_ptr)
    {
	GS_ui::inform (UI_INFORM__ERROR,
	    GS_string("END FUNCTION  encountered with no matching  FUNCTION."));
        return FALSE;
    }


    //  Pop everything off the stack to the function which is on the stack.
    //
    GS_stack_item* curr_item_ptr = pop ();
    while ((curr_item_ptr)
        && (! curr_item_ptr->get_function_si_ptr ()))
    {
        //  Stack item is potentially a variable.
        //
        if (curr_item_ptr->get_var_si_ptr ())
        {
	    if (curr_item_ptr->get_var_si_ptr ()->get_var_name_str ().
		    length () > 5)
	    {
		if (curr_item_ptr->get_var_si_ptr ()->get_var_name_str ().
			compare_n ("attr_", 5))
		{
		    if ((curr_item_ptr->get_var_si_ptr ()->
			    get_boolean_var_ptr ())
			|| (curr_item_ptr->get_var_si_ptr ()->
			    get_integer_var_ptr ())
			|| (curr_item_ptr->get_var_si_ptr ()->
			    get_real_var_ptr ())
			|| (curr_item_ptr->get_var_si_ptr ()->
			    get_string_var_ptr ())
			|| (curr_item_ptr->get_var_si_ptr ()->
			    get_object_inst_ref_var_ptr ())
			|| (curr_item_ptr->get_var_si_ptr ()->
			    get_object_inst_ref_set_var_ptr ())
			|| (curr_item_ptr->get_var_si_ptr ()->
			    get_frag_ref_var_ptr ()))
		    {
			return_frag_ref_var_ptr->add_attr (curr_item_ptr->
			    get_var_si_ptr ()->get_var_name_str (),
			    curr_item_ptr->get_var_ptr ());
		    }
		}
	    }
        }
	delete curr_item_ptr;
        curr_item_ptr = pop ();
    }
    
    
    GS_function_si* func_si_ptr = curr_item_ptr->get_function_si_ptr ();
    if (func_si_ptr)
    {
        if (p_return_char_num_ptr)
        {
            *p_return_char_num_ptr = func_si_ptr->m_return_char_num;
        }
        if (p_return_line_num_ptr)
        {
            *p_return_line_num_ptr = func_si_ptr->m_return_line_num;
        }
        if (p_return_arch_file_name_str_ptr)
        {
            *p_return_arch_file_name_str_ptr
		= func_si_ptr->m_return_arch_file_name_str;
        }
        
        delete curr_item_ptr;
    }
    else
    {
        LOG_ERROR ((L_log_string,
	    "GS_stack::function_end () - function stack item NOT found."));
        return FALSE;
    }
    
    
    //  Leave the return value on the stack for use in the calling logic.
    //
    return TRUE;
}





t_boolean
GS_stack::mapping_point_begin ()

{
    //  Create the function on the stack.
    //
    push_ctrl (new GS_function_si (0, 0, 0, "", ""));


    return TRUE;
}





t_boolean
GS_stack::mapping_point_end ()

{
    //  Pop everything off the stack to the function which is on the stack.
    //
    GS_stack_item* curr_item_ptr = pop ();
    while ((curr_item_ptr)
        && (! curr_item_ptr->get_function_si_ptr ()))
    {
	delete curr_item_ptr;
        curr_item_ptr = pop ();
    }
    
    
    GS_function_si* func_si_ptr = curr_item_ptr->get_function_si_ptr ();
    if (func_si_ptr)
    {
        delete curr_item_ptr;
    }
    else
    {
        LOG_ERROR ((L_log_string,
	    "GS_stack::mapping_point_end () - function stack item NOT found."));
        return FALSE;
    }
    
    
    return TRUE;
}





t_boolean
GS_stack::for_begin
    (const Description& p_inst_name_str, const Description& p_inst_set_name_str,
    streampos p_begin_char_num, t_uint p_begin_line_num)

{
    I_object_inst_ref_set_var* object_inst_ref_set_var_ptr
	= GS_stack::find_object_inst_ref_set_var_ptr (p_inst_set_name_str.char_ptr());
    if (! object_inst_ref_set_var_ptr)
    {
	    Description err_msg("Instance Set '");
		err_msg += p_inst_set_name_str;
		err_msg += "' is undefined.";
		GS_ui::inform (UI_INFORM__ERROR, err_msg);
		return FALSE;
    }


    if (object_inst_ref_set_var_ptr->is_empty ())
    {
	//  Set up an empty instance variable which would have been
	//    the iterator.
	//
	I_object_inst_ref_var* iterator_inst_var_ptr
	    = new I_object_inst_ref_var
	    (object_inst_ref_set_var_ptr->get_obj_ptr (), 0);
	GS_var_si lvalue_var_si;
	lvalue_var_si.replace_var (iterator_inst_var_ptr);
	GS_stack::place_result_in_stack_var (p_inst_name_str.char_ptr(), &lvalue_var_si);
	return FALSE;
    }


    //  Move cursor of instance set handle to the first instance.
    //
    object_inst_ref_set_var_ptr->first ();


    //  Set up the instance variable with the instance to be iterated over
    //    next.
    //
    I_object_inst_ref_var* iterator_inst_var_ptr = new I_object_inst_ref_var ();
    iterator_inst_var_ptr->
	set_oinst_ptr (object_inst_ref_set_var_ptr->get_oinst_ptr ());
    GS_var_si lvalue_var_si;
    lvalue_var_si.replace_var (iterator_inst_var_ptr);
    GS_stack::place_result_in_stack_var (p_inst_name_str, &lvalue_var_si);


    //  Push an for stack item on the stack.
    //
    push_ctrl (new GS_for_si (p_inst_name_str, p_inst_set_name_str,
	p_begin_char_num, p_begin_line_num));


    return TRUE;
}




Description
GS_stack::for_get_inst_name_str ()

{
    //  Begin at the top of the stack and check each item until you reach
    //    the bottom of the stack or until you reach a control structure
    //    on the stack.
    //
    t_uint tmp_stack_offset = s_stack_offset;
    while ((tmp_stack_offset > 0)
	&& (s_stack [tmp_stack_offset])
	&& (s_stack [tmp_stack_offset]->get_var_si_ptr ()))
    {
	//  Stack item is a variable - look at next in stack.
	//
	tmp_stack_offset--;
    }


    if ((tmp_stack_offset > 0)
	&& (s_stack [tmp_stack_offset])
	&& (s_stack [tmp_stack_offset]->get_for_si_ptr ()))
    {
	return s_stack [tmp_stack_offset]->get_for_si_ptr ()->
	    get_inst_name_str ();
    }


    if ((tmp_stack_offset > 0)
	&& (s_stack [tmp_stack_offset])
	&& (s_stack [tmp_stack_offset]->get_if_si_ptr ()))
    {
	GS_ui::inform (UI_INFORM__ERROR,
	    GS_string("END FOR  encountered with no matching  FOR  within  IF  construct."));
	return "";
    }


    GS_ui::inform (UI_INFORM__ERROR,
	GS_string("END FOR  encountered with no matching  FOR"));
    return "";
}




Description
GS_stack::for_get_inst_set_name_str ()

{
    //  Begin at the top of the stack and check each item until you reach
    //    the bottom of the stack or until you reach a control structure
    //    on the stack.
    //
    t_uint tmp_stack_offset = s_stack_offset;
    while ((tmp_stack_offset > 0)
	&& (s_stack [tmp_stack_offset])
	&& (s_stack [tmp_stack_offset]->get_var_si_ptr ()))
    {
	//  Stack item is a variable - look at next in stack.
	//
	tmp_stack_offset--;
    }


    if ((tmp_stack_offset > 0)
	&& (s_stack [tmp_stack_offset])
	&& (s_stack [tmp_stack_offset]->get_for_si_ptr ()))
    {
	return s_stack [tmp_stack_offset]->get_for_si_ptr ()->
	    get_inst_set_name_str ();
    }


    if ((tmp_stack_offset > 0)
	&& (s_stack [tmp_stack_offset])
	&& (s_stack [tmp_stack_offset]->get_if_si_ptr ()))
    {
	GS_ui::inform (UI_INFORM__ERROR,
	    GS_string("END FOR  encountered with no matching  FOR  within  IF  construct."));
	return "";
    }


    GS_ui::inform (UI_INFORM__ERROR,
	GS_string("END FOR  encountered with no matching  FOR"));
    return "";
}




streampos
GS_stack::for_get_begin_char_num ()

{
    //  Begin at the top of the stack and check each item until you reach
    //    the bottom of the stack or until you reach a control structure
    //    on the stack.
    //
    t_uint tmp_stack_offset = s_stack_offset;
    while ((tmp_stack_offset > 0)
	&& (s_stack [tmp_stack_offset])
	&& (s_stack [tmp_stack_offset]->get_var_si_ptr ()))
    {
	//  Stack item is a variable - look at next in stack.
	//
	tmp_stack_offset--;
    }


    if ((tmp_stack_offset > 0)
	&& (s_stack [tmp_stack_offset])
	&& (s_stack [tmp_stack_offset]->get_for_si_ptr ()))
    {
	return s_stack [tmp_stack_offset]->get_for_si_ptr ()->
	    get_begin_char_num ();
    }


    if ((tmp_stack_offset > 0)
	&& (s_stack [tmp_stack_offset])
	&& (s_stack [tmp_stack_offset]->get_if_si_ptr ()))
    {
	GS_ui::inform (UI_INFORM__ERROR,
	    GS_string("END FOR  encountered with no matching  FOR  within  IF  construct."));
	return 0;
    }


    GS_ui::inform (UI_INFORM__ERROR,
	GS_string("END FOR  encountered with no matching  FOR"));
    return 0;
}




t_uint
GS_stack::for_get_begin_line_num ()

{
    //  Begin at the top of the stack and check each item until you reach
    //    the bottom of the stack or until you reach a control structure
    //    on the stack.
    //
    t_uint tmp_stack_offset = s_stack_offset;
    while ((tmp_stack_offset > 0)
	&& (s_stack [tmp_stack_offset])
	&& (s_stack [tmp_stack_offset]->get_var_si_ptr ()))
    {
	//  Stack item is a variable - look at next in stack.
	//
	tmp_stack_offset--;
    }


    if ((tmp_stack_offset > 0)
	&& (s_stack [tmp_stack_offset])
	&& (s_stack [tmp_stack_offset]->get_for_si_ptr ()))
    {
	return s_stack [tmp_stack_offset]->get_for_si_ptr ()->
	    get_begin_line_num ();
    }


    if ((tmp_stack_offset > 0)
	&& (s_stack [tmp_stack_offset])
	&& (s_stack [tmp_stack_offset]->get_if_si_ptr ()))
    {
	GS_ui::inform (UI_INFORM__ERROR,
	    GS_string("END FOR  encountered with no matching  FOR  within  IF  construct."));
	return 0;
    }


    GS_ui::inform (UI_INFORM__ERROR,
	GS_string("END FOR  encountered with no matching  FOR"));
    return 0;
}




t_boolean
GS_stack::for_rewind ()

{
    Description for_inst_set_name_str (GS_stack::for_get_inst_set_name_str ());
    if (for_inst_set_name_str == "")
    {
	return FALSE;
    }


    I_object_inst_ref_set_var* object_inst_ref_set_var_ptr
	= GS_stack::find_object_inst_ref_set_var_ptr (for_inst_set_name_str);
    if (! object_inst_ref_set_var_ptr)
    {
	LOG_ERROR ((L_log_string,
	    "GS_stack::for_rewind ():  Unable to find set for iteration..."));
	return FALSE;
    }


    if (object_inst_ref_set_var_ptr->is_last ()
	||
	object_inst_ref_set_var_ptr->is_done ())
    {
	//  NO more instances exist to iterate through.
	//

	//  Pop all variables off the stack until non-variable encountered.
	//
	while ((s_stack_offset > 0)
	    && (s_stack [s_stack_offset])
	    && ((s_stack [s_stack_offset])->get_var_si_ptr ()))
	{
	    //  Stack item is a variable - pop & delete.
	    //
	    delete pop ();
	}
	
	
	//  Delete the for stack item itself.
	//
	if ((s_stack_offset > 0)
	    && (s_stack [s_stack_offset])
	    && ((s_stack [s_stack_offset])->get_for_si_ptr ()))
	{
	    delete pop ();
	    return FALSE;
	}


	//  Error message already printed.
	//
	return FALSE;
    }


    //  More instances exist to iterate through.
    //

    
    //  Move to instance set cursor to the next instance.
    //
    object_inst_ref_set_var_ptr->next ();


    //  Clean up the stack of any variables from the previous iteration.
    //
    //  Begin at the top of the stack and check each item until you reach
    //    the bottom of the stack or until you reach a control statement
    //    on the stack.
    //
    while ((s_stack_offset > 0)
	&& (s_stack [s_stack_offset])
	&& ((s_stack [s_stack_offset])->get_var_si_ptr ()))
    {
	//  Stack item is a variable - pop & delete.
	//
	delete pop ();
    }


    //  Restore the instance variable with the instance to be iterated over
    //    next.
    //
    Description iterator_object_inst_ref_var_name_str
	= GS_stack::for_get_inst_name_str ();
    I_object_inst_ref_var* iterator_object_inst_ref_var_ptr = 0;
    I_var* iterator_var_ptr
	= GS_stack::find_var_ptr (iterator_object_inst_ref_var_name_str);
    if (iterator_var_ptr)
    {
	iterator_object_inst_ref_var_ptr
	    = iterator_var_ptr->get_object_inst_ref_var_ptr ();
	if (iterator_object_inst_ref_var_ptr)
	{
	    if (iterator_object_inst_ref_var_ptr->get_key_letters_str ()
		!= object_inst_ref_set_var_ptr->get_key_letters_str ())
	    {
		    Description err_msg("Instance Variable '");
		    err_msg += iterator_object_inst_ref_var_name_str;
		    err_msg += "' is Defined but refers to an instance of a different object than the set in this FOR statement.";
			GS_ui::inform (UI_INFORM__ERROR, err_msg);
			return FALSE;
	    }
	    else
	    {
		if (object_inst_ref_set_var_ptr->cursor ()
		    > object_inst_ref_set_var_ptr->cardinality ())
		{
		    LOG_ERROR ((L_log_string,
			"GS_stack::for_rewind ():  object_inst_ref_set_var_ptr->cursor () exceeds the cardinality ()"));
		    iterator_object_inst_ref_var_ptr->set_oinst_ptr (0);
		}
		else if ((object_inst_ref_set_var_ptr->cursor () < 1)
		    && (object_inst_ref_set_var_ptr->cardinality () >= 1))
		{
		    LOG_ERROR ((L_log_string,
			"GS_stack::for_rewind ():  object_inst_ref_set_var_ptr->cursor () not initialized."));
		    iterator_object_inst_ref_var_ptr->set_oinst_ptr (0);
		}
		else
		{
		    iterator_object_inst_ref_var_ptr->set_oinst_ptr
			(object_inst_ref_set_var_ptr->get_oinst_ptr ());
		}
	    }
	}
	else
	{
		Description err_msg ("Variable '");
		err_msg += iterator_object_inst_ref_var_name_str;
		err_msg += "' is Defined but is NOT of type INST_REF.";
	    GS_ui::inform (UI_INFORM__ERROR, err_msg);
	}
    }
    else
    {
	LOG_ERROR ((L_log_string,
	    "GS_stack::for_rewind ():  iteration variable not found on stack - creating a new one..."));
	push_var (new I_object_inst_ref_var (object_inst_ref_set_var_ptr),
	    iterator_object_inst_ref_var_name_str.char_ptr());
    }


    return TRUE;
}




void
GS_stack::for_break ()

{
    //  Break out of the intermost for statement - may go through some
    //    un-ended if statements but should not go through any un-ended
    //    functions.
    //

    //  Pop variables off the stack to the next control structure stack
    //    item.
    //
    while ((s_stack_offset > 0)
	&& (s_stack [s_stack_offset])
	&& (((s_stack [s_stack_offset])->get_var_si_ptr ())
	    || ((s_stack [s_stack_offset])->get_if_si_ptr ())
	    || ((s_stack [s_stack_offset])->get_while_si_ptr ())))
    {
	//  Stack item is a variable or an if stmt - pop & delete.
	//
	delete pop ();
    }


    //  Delete the for stack item itself.
    //
    if ((s_stack_offset > 0)
	&& (s_stack [s_stack_offset])
	&& ((s_stack [s_stack_offset])->get_for_si_ptr ()))
    {
	delete pop ();
	return;
    }


    GS_ui::inform (UI_INFORM__ERROR,
	GS_string("BREAK FOR  statement used outside  FOR  construct."));
}





GS_while_si::GS_while_si (const Description& p_while_stmt_str,
    streampos p_begin_char_num, t_uint p_begin_line_num)

{
    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_BEGIN, (L_log_string,
	"Begin:  GS_while_si::GS_while_si ()."));


    m_while_stmt_str = p_while_stmt_str;
    m_begin_char_num = p_begin_char_num;
    m_begin_line_num = p_begin_line_num;


    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	"End:  GS_while_si::GS_while_si ()."));
}


GS_while_si::~GS_while_si ()

{
    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_BEGIN, (L_log_string,
	"Begin:  GS_while_si::~GS_while_si ()."));


    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	"End:  GS_while_si::~GS_while_si ()."));
}





t_boolean
GS_stack::while_begin (const Description& p_while_stmt_str,
    streampos p_begin_char_num, t_uint p_begin_line_num)

{
    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_BEGIN, (L_log_string,
	"Begin:  GS_stack::while_begin ()."));


    if (GS_expression::interpret_stmt__while (p_while_stmt_str))
    {
	//  Push a while stack item on the stack.
	//
	push_ctrl (new GS_while_si
	    (p_while_stmt_str, p_begin_char_num, p_begin_line_num));
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #1:  GS_stack::while_begin (TRUE)."));
	return TRUE;
    }


    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	"End #2:  GS_stack::while_begin (FALSE)."));
    return FALSE;
}





streampos
GS_stack::while_get_begin_char_num ()

{
    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_BEGIN, (L_log_string,
	"Begin:  GS_stack::while_get_begin_char_num ()."));


    //  Begin at the top of the stack and check each item until you reach
    //    the bottom of the stack or until you reach a control structure
    //    on the stack.
    //
    t_uint tmp_stack_offset = s_stack_offset;
    while ((tmp_stack_offset > 0)
	&& (s_stack [tmp_stack_offset])
	&& (s_stack [tmp_stack_offset]->get_var_si_ptr ()))
    {
	//  Stack item is a variable - look at next in stack.
	//
	tmp_stack_offset--;
    }


    if ((tmp_stack_offset > 0)
	&& (s_stack [tmp_stack_offset])
	&& (s_stack [tmp_stack_offset]->get_while_si_ptr ()))
    {
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #1:  GS_stack::while_get_begin_char_num (rv=%d).",
	    s_stack [tmp_stack_offset]->get_while_si_ptr ()->
	    get_begin_char_num ()));
	return s_stack [tmp_stack_offset]->get_while_si_ptr ()->
	    get_begin_char_num ();
    }


    if ((tmp_stack_offset > 0)
	&& (s_stack [tmp_stack_offset])
	&& (s_stack [tmp_stack_offset]->get_if_si_ptr ()))
    {
	GS_ui::inform (UI_INFORM__ERROR,
	    GS_string("END WHILE  encountered with no matching  WHILE  within  IF or FOR  construct."));
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #2:  GS_stack::while_get_begin_char_num (rv=0)."));
	return 0;
    }


    GS_ui::inform (UI_INFORM__ERROR,
	GS_string("END WHILE  encountered with no matching  WHILE"));
    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	"End #3:  GS_stack::while_get_begin_char_num (rv=0)."));
    return 0;
}




t_uint
GS_stack::while_get_begin_line_num ()

{
    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_BEGIN, (L_log_string,
	"Begin:  GS_stack::while_get_begin_line_num ()."));


    //  Begin at the top of the stack and check each item until you reach
    //    the bottom of the stack or until you reach a control structure
    //    on the stack.
    //
    t_uint tmp_stack_offset = s_stack_offset;
    while ((tmp_stack_offset > 0)
	&& (s_stack [tmp_stack_offset])
	&& (s_stack [tmp_stack_offset]->get_var_si_ptr ()))
    {
	//  Stack item is a variable - look at next in stack.
	//
	tmp_stack_offset--;
    }


    if ((tmp_stack_offset > 0)
	&& (s_stack [tmp_stack_offset])
	&& (s_stack [tmp_stack_offset]->get_while_si_ptr ()))
    {
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #1:  GS_stack::while_get_begin_line_num (rv=%d).",
	    s_stack [tmp_stack_offset]->get_while_si_ptr ()->
	    get_begin_line_num ()));
	return s_stack [tmp_stack_offset]->get_while_si_ptr ()->
	    get_begin_line_num ();
    }


    if ((tmp_stack_offset > 0)
	&& (s_stack [tmp_stack_offset])
	&& (s_stack [tmp_stack_offset]->get_if_si_ptr ()))
    {
	GS_ui::inform (UI_INFORM__ERROR,
	    GS_string("END WHILE  encountered with no matching  WHILE  within  IF or FOR  construct."));
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #2:  GS_stack::while_get_begin_line_num (rv=0)."));
	return 0;
    }


    GS_ui::inform (UI_INFORM__ERROR,
	GS_string("END WHILE  encountered with no matching  WHILE."));
    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	"End #3:  GS_stack::while_get_begin_line_num (rv=0)."));
    return 0;
}




t_boolean
GS_stack::while_rewind ()

{
    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_BEGIN, (L_log_string,
	"Begin:  GS_stack::while_rewind ()."));


    //  Clean up the stack of any variables from the previous iteration.
    //
    //  Begin at the top of the stack and check each item until you reach
    //    the bottom of the stack or until you reach a control statement
    //    on the stack.
    //
    while ((s_stack_offset > 0)
	&& (s_stack [s_stack_offset])
	&& ((s_stack [s_stack_offset])->get_var_si_ptr ()))
    {
	//  Stack item is a variable - pop & delete.
	//
	delete pop ();
    }


    if (! ((s_stack [s_stack_offset])->get_while_si_ptr ()))
    {
	GS_ui::inform (UI_INFORM__ERROR,
	    GS_string("END WHILE  statement used outside  WHILE  construct   OR  Un-ended IF or FOR statements within WHILE construct."));
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #1:  GS_stack::while_rewind (FALSE):  END WHILE used outside WHILE."));
	return FALSE;
    }


    if (GS_expression::interpret_stmt__while
	(((s_stack [s_stack_offset])->get_while_si_ptr ())->m_while_stmt_str))
    {
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #2:  GS_stack::while_rewind (TRUE):  condition was TRUE."));
	return TRUE;
    }


    //  Delete the GS_while_si on the stack - all done with while statement.
    //
    delete pop ();
    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	"End #3:  GS_stack::while_rewind (FALSE):  condition was FALSE."));
    return FALSE;
}




void
GS_stack::while_break ()

{
    //  Break out of the intermost while statement - may go through some
    //    un-ended if statements but should not go through any un-ended
    //    functions.
    //

    //  Pop variables off the stack to the next control structure stack
    //    item.
    //
    while ((s_stack_offset > 0)
	&& (s_stack [s_stack_offset])
	&& (((s_stack [s_stack_offset])->get_var_si_ptr ())
	    || ((s_stack [s_stack_offset])->get_if_si_ptr ())
	    || ((s_stack [s_stack_offset])->get_for_si_ptr ())))
    {
	//  Stack item is a variable or an if stmt - pop & delete.
	//
	delete pop ();
    }


    //  Delete the while stack item itself.
    //
    if ((s_stack_offset > 0)
	&& (s_stack [s_stack_offset])
	&& ((s_stack [s_stack_offset])->get_while_si_ptr ()))
    {
	delete pop ();
	return;
    }


    GS_ui::inform (UI_INFORM__ERROR,
	GS_string("BREAK WHILE  statement used outside  WHILE  construct."));
}



void
GS_stack::if_begin (t_boolean p_condition_result)

{
    //  Push an if stack item on the stack.
    //
    push_ctrl (new GS_if_si (p_condition_result));
}




t_boolean
GS_stack::if_get_condition_result ()

{
    //  Begin at the top of the stack and check each item until you reach
    //    the bottom of the stack or until you reach a control structure
    //    on the stack.
    //
    t_uint tmp_stack_offset = s_stack_offset;
    while ((tmp_stack_offset > 0)
	&& (s_stack [tmp_stack_offset])
	&& (s_stack [tmp_stack_offset]->get_var_si_ptr ()))
    {
	//  Stack item is a variable - look at next in stack.
	//
	tmp_stack_offset--;
    }


    if ((tmp_stack_offset > 0)
	&& (s_stack [tmp_stack_offset])
	&& (s_stack [tmp_stack_offset]->get_if_si_ptr ()))
    {
	return s_stack [tmp_stack_offset]->get_if_si_ptr ()->
	    get_condition_result ();
    }


    if ((tmp_stack_offset > 0)
	&& (s_stack [tmp_stack_offset])
	&& (s_stack [tmp_stack_offset]->get_for_si_ptr ()))
    {
	char buffer [20];
	sprintf (buffer, "%u",
	    s_stack [tmp_stack_offset]->get_for_si_ptr ()->m_begin_line_num);
	GS_ui::inform (UI_INFORM__ERROR, GS_string
	    ("Incomplete  IF  construct encountered within  FOR\n")
	    + "\tconstruct beginning on line " + buffer + ".");
	return FALSE;
    }


    GS_ui::inform (UI_INFORM__ERROR,
	GS_string("Incomplete  IF  construct encountered."));
    return FALSE;
}




void
GS_stack::if_set_condition_result (t_boolean p_condition_result)

{
    //  Begin at the top of the stack and check each item until you reach
    //    the bottom of the stack or until you reach a control structure
    //    on the stack.
    //
    t_uint tmp_stack_offset = s_stack_offset;
    while ((tmp_stack_offset > 0)
	&& (s_stack [tmp_stack_offset])
	&& (s_stack [tmp_stack_offset]->get_var_si_ptr ()))
    {
	//  Stack item is a variable - look at next in stack.
	//
	tmp_stack_offset--;
    }


    if ((tmp_stack_offset > 0)
	&& (s_stack [tmp_stack_offset])
	&& (s_stack [tmp_stack_offset]->get_if_si_ptr ()))
    {
	s_stack [tmp_stack_offset]->get_if_si_ptr ()->
	    set_condition_result (p_condition_result);
	return;
    }


    if ((tmp_stack_offset > 0)
	&& (s_stack [tmp_stack_offset])
	&& (s_stack [tmp_stack_offset]->get_for_si_ptr ()))
    {
	char buffer [20];
	sprintf (buffer, "%u",
	    s_stack [tmp_stack_offset]->get_for_si_ptr ()->m_begin_line_num);
	GS_ui::inform (UI_INFORM__ERROR, GS_string
	    ("Incomplete  IF  construct encountered within  FOR\n")
	    + "\tconstruct beginning on line " + buffer + ".");
	return;
    }


    GS_ui::inform (UI_INFORM__ERROR,
	GS_string("Incomplete  IF  construct encountered."));
}




t_boolean
GS_stack::if_get_else_encountered ()

{
    //  Begin at the top of the stack and check each item until you reach
    //    the bottom of the stack or until you reach a control structure
    //    on the stack.
    //
    t_uint tmp_stack_offset = s_stack_offset;
    while ((tmp_stack_offset > 0)
	&& (s_stack [tmp_stack_offset])
	&& (s_stack [tmp_stack_offset]->get_var_si_ptr ()))
    {
	//  Stack item is a variable - look at next in stack.
	//
	tmp_stack_offset--;
    }


    if ((tmp_stack_offset > 0)
	&& (s_stack [tmp_stack_offset])
	&& (s_stack [tmp_stack_offset]->get_if_si_ptr ()))
    {
	return s_stack [tmp_stack_offset]->get_if_si_ptr ()->
	    get_else_encountered ();
    }


    if ((tmp_stack_offset > 0)
	&& (s_stack [tmp_stack_offset])
	&& (s_stack [tmp_stack_offset]->get_for_si_ptr ()))
    {
	char buffer [20];
	sprintf (buffer, "%u",
	    s_stack [tmp_stack_offset]->get_for_si_ptr ()->m_begin_line_num);
	GS_ui::inform (UI_INFORM__ERROR, GS_string
	    ("Incomplete  IF  construct encountered within  FOR\n")
	    + "\tconstruct beginning on line " + buffer + ".");
	return FALSE;
    }


    GS_ui::inform (UI_INFORM__ERROR,
	GS_string("Incomplete  IF  construct encountered."));
    return FALSE;
}




void
GS_stack::if_set_else_encountered (t_boolean p_else_encountered)

{
    //  Begin at the top of the stack and check each item until you reach
    //    the bottom of the stack or until you reach a control structure
    //    on the stack.
    //
    t_uint tmp_stack_offset = s_stack_offset;
    while ((tmp_stack_offset > 0)
	&& (s_stack [tmp_stack_offset])
	&& (s_stack [tmp_stack_offset]->get_var_si_ptr ()))
    {
	//  Stack item is a variable - look at next in stack.
	//
	tmp_stack_offset--;
    }


    if ((tmp_stack_offset > 0)
	&& (s_stack [tmp_stack_offset])
	&& (s_stack [tmp_stack_offset]->get_if_si_ptr ()))
    {
	s_stack [tmp_stack_offset]->get_if_si_ptr ()->
	    set_else_encountered (p_else_encountered);
	return;
    }


    if ((tmp_stack_offset > 0)
	&& (s_stack [tmp_stack_offset])
	&& (s_stack [tmp_stack_offset]->get_for_si_ptr ()))
    {
	char buffer [20];
	sprintf (buffer, "%u",
	    s_stack [tmp_stack_offset]->get_for_si_ptr ()->m_begin_line_num);
	GS_ui::inform (UI_INFORM__ERROR, GS_string
	    ("Incomplete  IF  construct encountered within  FOR\n")
	    + "\tconstruct beginning on line " + buffer + ".");
	return;
    }


    GS_ui::inform (UI_INFORM__ERROR,
	GS_string("Incomplete  IF  construct encountered."));
}




void
GS_stack::if_end ()

{
    //  Pop all variables off the stack until non variable encountered.
    //
    while ((s_stack_offset > 0)
	&& (s_stack [s_stack_offset])
	&& ((s_stack [s_stack_offset])->get_var_si_ptr ()))
    {
	//  Stack item is a variable - pop & delete.
	//
	delete pop ();
    }
    
    
    //  Delete the if stack item itself.
    //
    if ((s_stack_offset > 0)
	&& (s_stack [s_stack_offset])
	&& ((s_stack [s_stack_offset])->get_if_si_ptr ()))
    {
	delete pop ();
	return;
    }


    if ((s_stack_offset > 0)
	&& (s_stack [s_stack_offset])
	&& ((s_stack [s_stack_offset])->get_for_si_ptr ()))
    {
	char buffer [20];
	sprintf (buffer, "%u",
	    (s_stack [s_stack_offset])->get_for_si_ptr ()->m_begin_line_num);
	GS_ui::inform (UI_INFORM__ERROR, GS_string
	    ("END IF  encountered with no matching  IF  within  FOR\n")
	    + "\tconstruct beginning on line "
	    + buffer
	    + ".");
	return;
    }


    GS_ui::inform (UI_INFORM__ERROR,
	GS_string("END IF  encountered with no matching  IF"));
}



GS_frag_gen_si::GS_frag_gen_si ()

{
}



GS_frag_gen_si::~GS_frag_gen_si ()

{
}



void
GS_stack::frag_gen_begin ()

{
    //  Push an frag_gen stack item on the stack.
    //
    push_ctrl (new GS_frag_gen_si ());
}




void
GS_stack::frag_gen_end ()

{
    //  Pop everything off the stack to the frag_gen stack item.
    //
    GS_stack_item* curr_item_ptr = pop ();
    while ((curr_item_ptr) && (curr_item_ptr->get_var_si_ptr ()))
    {
        //  Stack item is a variable.
        //
	delete curr_item_ptr;
        curr_item_ptr = pop ();
    }
    
    
    //  Delete the frag_gen stack item itself.
    //
    if (curr_item_ptr)
    {
        if (curr_item_ptr->get_frag_gen_si_ptr ())
        {
            delete curr_item_ptr;
            return;
        }
    }


    delete curr_item_ptr;
    GS_ui::inform (UI_INFORM__ERROR,
	GS_string("A Statement Construct is Un-ended when a .EMIT FRAGMENT is processed - check for a missing .END FOR or .END IF."));
}




#ifdef COMMENTED_OUT

GS_var_si*
GS_stack::push_var (I_var* p_var_ptr, const GS_string& p_var_name_str)

{
    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_BEGIN,
               (L_log_string,
                "Begin:  GS_stack::push_var (p_var_ptr=0x%08x, p_var_name_str=%S).",
                p_var_ptr,
                vcharScribeASCII(p_var_name_str.char_ptr ()) ));


    if (s_stack_offset >= (GS_STACK_SIZE - 1))
    {
        GS_ui::inform (UI_INFORM__ERROR,
	    "Stack Overflow... number of stack items exceeds maximum.");
	LOG_ERROR ((L_log_string,
	    "End #1:  GS_stack::push_var ():  Stack Overflow... number of stack items exceeds maximum."));
	return 0;
    }


    GS_var_si* var_si_ptr = 0;
    if (p_var_ptr->get_frag_ref_var_ptr ())
    {
	//  Push by reference - use same I_var.
	//
	var_si_ptr = new GS_var_si (p_var_ptr, p_var_name_str);
	s_stack_offset++;
	s_stack [s_stack_offset] = var_si_ptr;
    }
    else
    {
	//  Push by value - use clone of the I_var.
	//
	I_var* new_var_ptr = p_var_ptr->clone_to_transient ();
	var_si_ptr = new GS_var_si (new_var_ptr, p_var_name_str);
	s_stack_offset++;
	s_stack [s_stack_offset] = var_si_ptr;
    }


    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	"End #2:  GS_stack::push_var (pushed_item_ptr=0x%08x, new s_stack_offset=%d).",
	var_si_ptr, s_stack_offset));
    return var_si_ptr;
}
#endif





GS_var_si*
GS_stack::push_var (I_var* p_var_ptr,
    const Description& p_var_name_str, const GS_string& p_var_frag_name_str, t_boolean p_pass_by_ref)

{
    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_BEGIN, (L_log_string,
	"Begin:  GS_stack::push_var (p_var_ptr=0x%08x, p_var_name_str=%s, p_var_frag_name_str=%S).",
	p_var_ptr, p_var_name_str.char_ptr (),
	vcharScribeASCII(p_var_frag_name_str.char_ptr ()) ));


    if (s_stack_offset >= (GS_STACK_SIZE - 1))
    {
        GS_ui::inform (UI_INFORM__ERROR,
	    GS_string("Stack Overflow... number of stack items exceeds maximum."));
	LOG_ERROR ((L_log_string,
	    "End #1:  GS_stack::push_var ():  Stack Overflow... number of stack items exceeds maximum."));
	return 0;
    }


    GS_var_si* var_si_ptr = 0;
    if (p_var_ptr->get_frag_ref_var_ptr () || p_pass_by_ref)
    {
	//  Push by reference - use same I_var.
	//
	var_si_ptr
	    = new GS_var_si (p_var_ptr, p_var_name_str, p_var_frag_name_str);
	s_stack_offset++;
	s_stack [s_stack_offset] = var_si_ptr;
    }
    else if (p_var_ptr->get_reference_count () == 0)
    {
	//  Push by value - however, since this variable has ZERO reference
	//    count, just take the variable over.
	//
	var_si_ptr
	    = new GS_var_si (p_var_ptr, p_var_name_str, p_var_frag_name_str);
	s_stack_offset++;
	s_stack [s_stack_offset] = var_si_ptr;
    }
    else
    {
	//  Push by value - use clone of the I_var.
	//
	I_var* new_var_ptr = p_var_ptr->clone_to_transient ();
	var_si_ptr
	    = new GS_var_si (new_var_ptr, p_var_name_str, p_var_frag_name_str);
	s_stack_offset++;
	s_stack [s_stack_offset] = var_si_ptr;
    }


    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	"End #2:  GS_stack::push_var (pushed_item_ptr=0x%08x, new s_stack_offset=%d).",
	var_si_ptr, s_stack_offset));
    return var_si_ptr;
}




#ifdef COMMENTED_OUT

GS_var_si*
GS_stack::push_var (GS_var_si* p_var_si_ptr, const GS_string& p_var_name_str)

{
    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_BEGIN, (L_log_string,
	"Begin:  GS_stack::push_var (p_var_si_ptr=0x%08x, p_var_name_str=%S).",
	p_var_si_ptr,
  vcharScribeASCII(p_var_name_str.char_ptr ()) ));


    if (s_stack_offset >= (GS_STACK_SIZE - 1))
    {
        GS_ui::inform (UI_INFORM__ERROR,
	    "Stack Overflow... number of stack items exceeds maximum.");
	LOG_ERROR ((L_log_string,
	    "End #1:  GS_stack::push_var ():  Stack Overflow... number of stack items exceeds maximum."));
	return 0;
    }


    GS_var_si* var_si_ptr = 0;
    if (p_var_si_ptr->get_var_ptr ()->get_frag_ref_var_ptr ())
    {
	//  Push by reference - use same I_var.
	//
	var_si_ptr
	    = new GS_var_si (p_var_si_ptr->get_var_ptr (), p_var_name_str);
	s_stack_offset++;
	s_stack [s_stack_offset] = var_si_ptr;
    }
    else
    {
	//  Push by value - use clone of the I_var.
	//
	I_var* new_var_ptr
	    = p_var_si_ptr->get_var_ptr ()->clone_to_transient ();
	var_si_ptr = new GS_var_si (new_var_ptr, p_var_name_str);
	s_stack_offset++;
	s_stack [s_stack_offset] = var_si_ptr;
    }


    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	"End #2:  GS_stack::push_var (pushed_item_ptr=0x%08x, new s_stack_offset=%d).",
	var_si_ptr, s_stack_offset));
    return var_si_ptr;
}
#endif





GS_ctrl_si*
GS_stack::push_ctrl (GS_ctrl_si* p_ctrl_si_ptr)

{
    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_BEGIN, (L_log_string,
	"Begin:  GS_stack::push_ctrl (p_ctrl_si_ptr=0x%08x).",
	p_ctrl_si_ptr));


    if (s_stack_offset >= (GS_STACK_SIZE - 1))
    {
        GS_ui::inform (UI_INFORM__ERROR,
	    GS_string("Stack Overflow... number of stack items exceeds maximum."));
        LOG_ERROR ((L_log_string,
	    "End #1:  GS_stack::push_ctrl ():  Stack Overflow... number of stack items exceeds maximum."));
        return 0;
    }
    
    s_stack_offset++;
    s_stack [s_stack_offset] = p_ctrl_si_ptr;


    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	"End #2:  GS_stack::push_ctrl (pushed_item_ptr=0x%08x, new s_stack_offset=%d).",
	p_ctrl_si_ptr, s_stack_offset));
    return p_ctrl_si_ptr;
}





GS_stack_item*
GS_stack::pop ()

{
    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_BEGIN, (L_log_string,
	"Begin:  GS_stack::pop ()."));


    if (s_stack_offset <= 0)
    {
        GS_ui::inform (UI_INFORM__ERROR,
	    GS_string("Stack Underflow... NOT popping item from stack."));
	LOG_ERROR ((L_log_string,
	    "End #1:  GS_stack::pop (rv=0):  Stack Underflow... NOT popping item from stack."));
        return 0;
    }
    
    
    GS_stack_item* popped_item_ptr = s_stack [s_stack_offset];
    s_stack_offset--;
    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	"End #2:  GS_stack::pop (popped_item_ptr=0x%08x, new s_stack_offset=%d).",
	popped_item_ptr, s_stack_offset));
    return popped_item_ptr;
}



void
GS_stack::pop_and_delete_all_stack_items () 

{
    while (s_stack_offset > 0)
    {
	GS_stack_item* popped_item_ptr = s_stack [s_stack_offset];
	delete popped_item_ptr;
	s_stack_offset--;
    }
}





GS_var_si::GS_var_si ():
  m_var_name_str(),
  m_var_frag_name_str()
{
    m_var_ptr = 0;
}





GS_var_si::GS_var_si (I_var* p_var_ptr, const Description& p_var_name_str):
  m_var_frag_name_str()
{
    m_var_name_str = p_var_name_str;
    m_var_ptr = p_var_ptr;
    if (m_var_ptr)
    {
	m_var_ptr->increment_reference_count ();
    }
}





GS_var_si::GS_var_si (I_var* p_var_ptr,
    const Description& p_var_name_str, const GS_string& p_var_frag_name_str)

{
    m_var_name_str = p_var_name_str;
    m_var_frag_name_str = p_var_frag_name_str;
    m_var_ptr = p_var_ptr;
    if (m_var_ptr)
    {
	m_var_ptr->increment_reference_count ();
    }
}





GS_var_si::GS_var_si (const Description& p_var_name_str,
                      t_core_data_type p_core_data_type,
                      t_user_data_type p_user_data_type):
  m_var_frag_name_str()
{
    m_var_name_str = p_var_name_str;
    m_var_ptr = I_var::create_in_transient (p_core_data_type, p_user_data_type);
    if (m_var_ptr)
    {
	m_var_ptr->increment_reference_count ();
    }
}





GS_var_si::~GS_var_si ()

{
    if ((m_var_ptr) && (m_var_ptr->decrement_reference_count () < 1))
    {
	delete m_var_ptr;
    }
}





t_boolean
GS_stack::place_result_in_stack_var
    (const Description& p_lvar_str, GS_var_si* p_var_si_ptr)

{
    if ((! p_var_si_ptr) || (! (p_var_si_ptr->get_var_ptr ())))
    {
		Description err_msg("unable to re-assign lvalue '");
		err_msg += p_lvar_str;
		err_msg += "'";
		GS_ui::inform (UI_INFORM__ERROR, err_msg);
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
			"End #1:  GS_stack::place_result_in_stack_var ():   Variable does not exist."));
		return FALSE;
    }
	
	
    Description lvar_str (p_lvar_str);
	t_uint lvar_cursor = 0;
    Description lvar_name_str;
    lvar_str.parse_token ('.', lvar_cursor, lvar_name_str);

    t_boolean param_update = FALSE;
	
    I_var* var_ptr = find_var_ptr (lvar_name_str);
    if (! var_ptr)
    {
		//  Left-hand variable does not exist on the stack - need to create the
		//    variable and push it...
		//
		if (lvar_str.compare_first('.', lvar_cursor))
		{
            if ( lvar_name_str != "param" )
            {
			    Description err_msg ("lvalue '");
			    err_msg += lvar_name_str;
			    err_msg += "' must exist in order to assign attribute value.";
			    GS_ui::inform (UI_INFORM__ERROR, err_msg);
			    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
			        "End #2:  GS_stack::place_result_in_stack_var ()."));
			    return FALSE;
            }
            else
            {
                param_update = TRUE;
            }
		}
		else
        {
		    GS_var_si* new_var_si_ptr
			    = push_var (p_var_si_ptr->get_var_ptr (), lvar_name_str);
	        GS_UI_INFORM_START (UI_INFORM__COMP)
		    Description err_msg("created lvalue '");
		    err_msg += lvar_str.char_ptr();
		    err_msg += "' (";
		    err_msg += new_var_si_ptr->get_var_ptr ()->get_data_type_str ();
		    err_msg += ") = ";
		    err_msg += new_var_si_ptr->get_var_ptr ()->get_value_str ();
		    GS_UI_INFORM_END (UI_INFORM__COMP, err_msg)
		    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
			    "End #3:  GS_stack::place_result_in_stack_var ():  Pushed new transient variable on stack."));
		    return TRUE;
        }
    }
	
	
    //  Left-hand variable already exists on the stack - need to re-assign
    //    the value.
    //
    if (lvar_str.compare_first('.', lvar_cursor))
    {
		//  Re-assignment of either object instance attribute or a fragment
		//    attribute or a parameter.
		//
		lvar_cursor++;
		Description lvar_attr_name_str;
    		lvar_str.parse_token (lvar_cursor, lvar_attr_name_str);
        if ( param_update )
        {
            var_ptr = find_var_ptr (p_lvar_str);
            if (! var_ptr)
            {
			    Description err_msg ("lvalue '");
			    err_msg += lvar_str;
			    err_msg += "' must exist in order to assign attribute value.";
			    GS_ui::inform (UI_INFORM__ERROR, err_msg);
			    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
			        "End #3.1:  GS_stack::place_result_in_stack_var ()."));
			    return FALSE;
            }

		    if ( ! var_ptr->reassign (p_var_si_ptr->get_var_ptr ()) )
            {
			    LOG_ERROR ((L_log_string,
				    "End #3.2:  GS_stack::place_result_in_stack_var ():   Error in assignment to param by ref - reassign() returned false."));

                // error message already output
                return FALSE;
            }
            else
            {
                GS_UI_INFORM_START (UI_INFORM__COMP)
				Description err_msg("re-assigned lvalue '");
				err_msg += lvar_str.char_ptr();
				err_msg += "' (";
				err_msg += var_ptr->get_data_type_str ();
				err_msg += ") = ";
				err_msg += var_ptr->get_value_str ();
				GS_UI_INFORM_END (UI_INFORM__COMP, err_msg)
				LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
					"End #3.3:  GS_stack::place_result_in_stack_var ():  Reassigned param by ref."));
				return TRUE;
            }
        }
		else if (var_ptr->get_object_inst_ref_var_ptr ())
		{
			//  Re-assignment of object instance attribute.
			//
            I_Attribute_Instance* ainst_ptr = var_ptr->get_object_inst_ref_var_ptr ()->
    		    get_attr_inst_ptr (lvar_attr_name_str);
			if (ainst_ptr)
			{
				I_var* attr_var_ptr = ainst_ptr->get_var_ptr();
                if ( attr_var_ptr )
                {
                    attr_var_ptr->reassign (p_var_si_ptr->get_var_ptr ());
                }

                // If we're in the generator, check for a referential or identifying
                // attribute.  The verifier already manages the related_flag correctly.
		        extern t_boolean is_simulator;
		        if (! is_simulator)
		        {
                    // Check if it's a referential attribute
                    I_Attribute* attr_ptr = ainst_ptr->get_Attribute_R2002_ptr();
                    mc_dbms_List< I_ID_Attribute_Reference * > * ref_coll_ptr = 
                        attr_ptr->get_ID_Attribute_Reference_R2009_coll_ptr();
                    if ( ref_coll_ptr != 0 &&
                         ref_coll_ptr->cardinality() != 0 )
                    {
                        I_Object_Instance* oinst_ptr = 
                            ainst_ptr->get_Object_Instance_R2002_ptr();
                        I_relate::clear_related_flag(oinst_ptr);
                    }
                    else
                    {
                        // Check if it's an identifying attribute
                        mc_dbms_List< I_ID_Attribute_Reference * > * id_coll_ptr = 
                            attr_ptr->get_ID_Attribute_Reference_R2008_coll_ptr();
                        if ( id_coll_ptr != 0 &&
                             id_coll_ptr->cardinality() != 0 )
                        {
                            I_Object_Instance* oinst_ptr = 
                                ainst_ptr->get_Object_Instance_R2002_ptr();
                            I_relate::clear_related_flag(oinst_ptr);
                        }
                    }
                }

                GS_UI_INFORM_START (UI_INFORM__COMP)
				Description err_msg("re-assigned lvalue '");
				err_msg += lvar_str.char_ptr();
				err_msg += "' (";
				err_msg += attr_var_ptr->get_data_type_str ();
				err_msg += ") = ";
				err_msg += attr_var_ptr->get_value_str ();
				GS_UI_INFORM_END (UI_INFORM__COMP, err_msg)
				LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
					"End #4:  GS_stack::place_result_in_stack_var ():  Reassigned I_object_inst_ref_var attribute."));
				return TRUE;
			}
			Description err_msg("Attribute in lvalue '");
			err_msg += lvar_str;
			err_msg += "' does not exist.";
			GS_ui::inform (UI_INFORM__ERROR, err_msg);
			LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
				"End #5:  GS_stack::place_result_in_stack_var ():  Object attribute not found."));
			return FALSE;
		}
		else if (var_ptr->get_frag_ref_var_ptr ())
		{
			//  Re-assignment of fragment attribute.
			//
			I_var* attr_var_ptr = var_ptr->get_frag_ref_var_ptr ()->
				get_attr_var_ptr (lvar_attr_name_str);
			if (attr_var_ptr)
			{
				if (attr_var_ptr->get_frag_ref_var_ptr ())
				{
					//  Need to replace the pointer to the fragment variable
					//    rather than re-assigning the variable.
					//
					var_ptr->get_frag_ref_var_ptr ()->replace_attr_var_ptr
						(lvar_attr_name_str, p_var_si_ptr->get_var_ptr ());
				}
				else
				{
					attr_var_ptr->reassign (p_var_si_ptr->get_var_ptr ());
				}
        	    GS_UI_INFORM_START (UI_INFORM__COMP)
				Description err_msg ("re-assigned lvalue '");
				err_msg += lvar_str.char_ptr();
				err_msg += "' (";
				err_msg += attr_var_ptr->get_data_type_str ();
				err_msg += ") = ";
				err_msg += attr_var_ptr->get_value_str ();
				GS_UI_INFORM_END (UI_INFORM__COMP, err_msg)
				LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
					"End #6:  GS_stack::place_result_in_stack_var ():  Reassigned I_frag_ref_var attribute."));
				return TRUE;
			}
			Description err_msg ("Attribute in lvalue '");
			err_msg += lvar_str;
			err_msg += "' does not exist.";
			GS_ui::inform (UI_INFORM__ERROR, err_msg);
			LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
				"End #7:  GS_stack::place_result_in_stack_var ():  Fragment attribute not found."));
			return FALSE;
		}
		else
		{
			Description err_msg ("unable to re-assign lvalue '");
			err_msg += p_lvar_str;
			err_msg += "'";
			GS_ui::inform (UI_INFORM__ERROR, err_msg);
			LOG_ERROR ((L_log_string,
				"End #8:  GS_stack::place_result_in_stack_var ():   Error in assignment to attribute value - variable is not object instance reference or fragment."));
			return FALSE;
		}
    }
	
	
    //  Re-assignment of transient variable on the stack.
    //
	t_boolean is_fragment = FALSE;
	Description dt_str;
	Description val_str;
    if (var_ptr->get_frag_ref_var_ptr ())
    {
		// Check if the rvalue is a fragment as well
		// This is a common error, where the user forgets to place the
		// attribute name after the fragment.
		if ( p_var_si_ptr->get_frag_ref_var_ptr () )
		{
			is_fragment = TRUE;

			// Get a pointer to the frag ref derived class, that has the
			// correct vtable.
			I_var* rval = p_var_si_ptr->get_frag_ref_var_ptr ();
			dt_str = rval->get_data_type_str ();
			val_str = rval->get_value_str ();

			//  Need to replace the pointer to the fragment variable rather
			//    than re-assigning the variable.
			//
			GS_var_si* var_si_ptr = find_var_si_ptr (lvar_name_str);
			if (var_si_ptr)
			{
				var_si_ptr->replace_var (p_var_si_ptr->get_var_ptr ());
			}
			else
			{
				Description err_msg("unable to re-assign lvalue '");
				err_msg += p_lvar_str;
				err_msg += "'";
				GS_ui::inform (UI_INFORM__ERROR, err_msg);
				LOG_ERROR ((L_log_string,
					"End #9:  GS_stack::place_result_in_stack_var ():   Error in assignment to fragment variable - unable to find var_si_ptr."));
				return FALSE;
			}
		}
		else
		{
			Description err_msg("unable to re-assign lvalue '");
			err_msg += p_lvar_str;
			err_msg += "', rvalue is not of type fragment.";
			GS_ui::inform (UI_INFORM__ERROR, err_msg);
			LOG_ERROR ((L_log_string,
				"End #9:  GS_stack::place_result_in_stack_var ():   Error in assignment to fragment variable - rvalue is not of type fragment."));
			return FALSE;
		}
    }
    else
    {
		if ( ! var_ptr->reassign (p_var_si_ptr->get_var_ptr ()) )
        {
            LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
				"End #9.1:  GS_stack::place_result_in_stack_var ():   reassign() returned false."));

            // error message already output
            return FALSE;
        }
    }
    GS_UI_INFORM_START (UI_INFORM__COMP)
	Description err_msg ("re-assigned lvalue '");
	err_msg += lvar_str.char_ptr(); 
	err_msg += "' (";
	if ( is_fragment )
	{
		err_msg += dt_str;
		err_msg += ") = ";
		err_msg += val_str;
	}
	else
	{
		err_msg += var_ptr->get_data_type_str ();
		err_msg += ") = ";
		err_msg += var_ptr->get_value_str ();
	}
    GS_UI_INFORM_END (UI_INFORM__COMP, err_msg)
    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		"End #10:  GS_stack::place_result_in_stack_var ():  Reassigned transient variable."));
    return TRUE;
}





void
GS_var_si::replace_var (I_var* p_var_ptr)

{
    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_BEGIN, (L_log_string,
	"Begin:  GS_stack::replace_var ()."));


    if (p_var_ptr)
    {
	p_var_ptr->increment_reference_count ();
    }

    if ((m_var_ptr) && (m_var_ptr->decrement_reference_count () < 1))
    {
	delete m_var_ptr;
    }

    m_var_ptr = p_var_ptr;


    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	"End:  GS_stack::replace_var ()."));
}

//
// Formatting information for emacs
//
// Local Variables:
// tab-width:4
// End:
//

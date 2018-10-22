/*========================================================================
 *
 * File:      $RCSfile: gs_stack.hh,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:17 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#ifndef GS_STACK_HH
#define GS_STACK_HH

#include <iostream.h>


#ifdef OLD_FILE_NAMES
#include <U_typedefs.hh>
#include <D_typedefs.hh>
#else
#include <u_typdef.hh>
#include <d_typdef.hh>
#endif


#include <u_string.hh>
#include <i_var.hh>


class GS_stack_item;
class GS_var_si;
class GS_ctrl_si;
class GS_include_si;
class GS_function_si;
class GS_for_si;
class GS_while_si;
class GS_if_si;
class GS_frag_gen_si;

class SIM_SOR;
class GS_gen_action;

class mc_dbms_database;
extern mc_dbms_database* GS_gen_sim_db_ptr;




class GS_stack

{
public:
    static GS_var_si*			find_var_si_ptr
					    (const Description& p_name_str);
    static I_var*			find_var_ptr
					    (const Description& p_name_str);
    static I_void_var*			find_void_var_ptr
					    (const Description& p_name_str);
    static I_enumerator_var*	find_enumerator_var_ptr
					    (const Description& p_name_str);
    static I_boolean_var*		find_boolean_var_ptr
					    (const Description& p_name_str);
    static I_integer_var*		find_integer_var_ptr
					    (const Description& p_name_str);
    static I_real_var*			find_real_var_ptr
					    (const Description& p_name_str);
    static I_string_var*		find_string_var_ptr
					    (const Description& p_name_str);
    static I_unique_id_var*		find_unique_id_var_ptr
					    (const Description& p_name_str);
    static I_current_state_var*		find_current_state_var_ptr
					    (const Description& p_name_str);
    static I_object_inst_ref_var*	find_object_inst_ref_var_ptr
					    (const Description& p_name_str);
    static I_object_inst_ref_set_var*	find_object_inst_ref_set_var_ptr
					    (const Description& p_name_str);
    static I_event_inst_var*		find_event_inst_var_ptr
					    (const Description& p_name_str);
    static I_mapping_inst_var*		find_mapping_inst_var_ptr
					    (const Description& p_name_str);
    static I_mapping_inst_ref_var*	find_mapping_inst_ref_var_ptr
					    (const Description& p_name_str);
    static I_date_var*			find_date_var_ptr
					    (const Description& p_name_str);
    static I_timestamp_var*		find_timestamp_var_ptr
					    (const Description& p_name_str);
    static I_timer_inst_ref_var*	find_timer_inst_ref_var_ptr
					    (const Description& p_name_str);
    static I_frag_ref_var*		find_frag_ref_var_ptr
					    (const Description& p_name_str);

    static void             include_begin (streampos p_return_char_num,
				t_uint p_return_line_num,
                                const GS_string& p_return_arch_file_name_str,
                                const GS_string& p_include_arch_file_name_str);
    static t_boolean        include_end (streampos* p_return_char_num_ptr,
				t_uint* p_return_line_num_ptr,
                                GS_string* p_return_arch_file_name_str_ptr,
                                GS_string* p_include_arch_file_name_str_ptr);

    static t_boolean        function_begin (streampos p_return_char_num,
				t_uint p_return_line_num,
                                const GS_string& p_return_arch_file_name_str,
                                const GS_string& p_return_frag_name_str,
                                const GS_string& p_func_name_str,
                                GS_var_si p_param [],
				t_uint p_num_params);
    static I_frag_ref_var* function_get_return_frag_ref_var_ptr ();

    static t_boolean        function_end (streampos* p_return_char_num_ptr = 0,
                                          t_uint* p_return_line_num_ptr = 0,
                                GS_string* p_return_arch_file_name_str_ptr = 0);

    static t_boolean        mapping_point_begin ();
    static t_boolean        mapping_point_end ();

    static t_boolean        for_begin (const Description& p_inst_name_str,
				const Description& p_inst_set_name_str,
                                streampos p_begin_char_num,
				t_uint p_begin_line_num);
    static Description      for_get_inst_name_str ();
    static Description      for_get_inst_set_name_str ();
    static streampos        for_get_begin_char_num ();
    static t_uint           for_get_begin_line_num ();
    static t_boolean        for_rewind ();
    static void             for_break ();

    static t_boolean        while_begin (const Description& p_while_stmt_str,
				streampos p_begin_char_num,
				t_uint p_begin_line_num);
    static streampos        while_get_begin_char_num ();
    static t_uint           while_get_begin_line_num ();
    static t_boolean        while_rewind ();
    static void             while_break ();

    static void             if_begin (t_boolean p_condition_result);
    static t_boolean        if_get_condition_result ();
    static void             if_set_condition_result
				(t_boolean p_condition_result);
    static t_boolean        if_get_else_encountered ();
    static void             if_set_else_encountered
				(t_boolean p_else_encountered);
    static void             if_end ();

    static void             frag_gen_begin ();
    static void             frag_gen_end ();
    

    static t_boolean	    place_result_in_stack_var
				(const Description& p_lvar_str,
				GS_var_si* p_var_si_ptr);
#ifdef COMMENTED_OUT
    static GS_var_si*       push_var (I_var* p_var_ptr,
                                const GS_string& p_var_name_str);
#endif
    static GS_var_si*       push_var (I_var* p_var_ptr,
                                const Description& p_var_name_str,
                                const GS_string& p_var_frag_name_str
                                    = GS_string__NULL,
                                t_boolean p_pass_by_ref = FALSE);
#ifdef COMMENTED_OUT
    static GS_var_si*       push_var (GS_var_si* p_var_si_ptr,
                                const GS_string& p_var_name_str);
#endif
    static GS_ctrl_si*      push_ctrl (GS_ctrl_si* p_ctrl_stack_item_ptr);
    static GS_stack_item*   pop ();

    static void             pop_and_delete_all_stack_items ();
    
    
private:
};





class GS_stack_item

{
friend GS_stack;

public:
    virtual GS_var_si*			get_var_si_ptr ()
					    { return 0; }
    virtual GS_ctrl_si*			get_ctrl_si_ptr ()
					    { return 0; }
    virtual GS_include_si*		get_include_si_ptr ()
					    { return 0; }
    virtual GS_function_si*		get_function_si_ptr ()
					    { return 0; }
    virtual GS_for_si*			get_for_si_ptr ()
					    { return 0; }
    virtual GS_while_si*		get_while_si_ptr ()
					    { return 0; }
    virtual GS_if_si*			get_if_si_ptr ()
					    { return 0; }
    virtual GS_frag_gen_si*		get_frag_gen_si_ptr ()
					    { return 0; }


    virtual I_var*			get_var_ptr ()
					    { return 0; }
    virtual I_void_var*			get_void_var_ptr ()
					    { return 0; }
    virtual I_enumerator_var*	get_enumerator_var_ptr ()
					    { return 0; }
    virtual I_boolean_var*		get_boolean_var_ptr ()
					    { return 0; }
    virtual I_integer_var*		get_integer_var_ptr ()
					    { return 0; }
    virtual I_real_var*			get_real_var_ptr ()
					    { return 0; }
    virtual I_string_var*		get_string_var_ptr ()
					    { return 0; }
    virtual I_unique_id_var*		get_unique_id_var_ptr ()
					    { return 0; }
    virtual I_current_state_var*	get_current_state_var_ptr ()
					    { return 0; }
    virtual I_object_inst_ref_var*	get_object_inst_ref_var_ptr ()
					    { return 0; }
    virtual I_object_inst_ref_set_var*	get_object_inst_ref_set_var_ptr ()
					    { return 0; }
    virtual I_event_inst_var*		get_event_inst_var_ptr ()
					    { return 0; }
    virtual I_mapping_inst_var*		get_mapping_inst_var_ptr ()
					    { return 0; }
    virtual I_mapping_inst_ref_var*	get_mapping_inst_ref_var_ptr ()
					    { return 0; }
    virtual I_date_var*			get_date_var_ptr ()
					    { return 0; }
    virtual I_timestamp_var*		get_timestamp_var_ptr ()
					    { return 0; }
    virtual I_timer_inst_ref_var*	get_timer_inst_ref_var_ptr ()
					    { return 0; }
    virtual I_frag_ref_var*		get_frag_ref_var_ptr ()
					    { return 0; }

    virtual				~GS_stack_item () {}



protected:
	                                GS_stack_item () {}


private:
};





class GS_var_si : public GS_stack_item

{
friend GS_stack;

public:
    I_var*			get_var_ptr ()
				{
				    return m_var_ptr;
				}
    I_void_var*			get_void_var_ptr ()
				{
				    return (! m_var_ptr) ? 0 : m_var_ptr->
					get_void_var_ptr ();
				}
	I_enumerator_var*	get_enumerator_var_ptr ()
				{
				    return (! m_var_ptr) ? 0 : m_var_ptr->
					get_enumerator_var_ptr ();
				}

    I_boolean_var*		get_boolean_var_ptr ()
				{
				    return (! m_var_ptr) ? 0 : m_var_ptr->
					get_boolean_var_ptr ();
				}
    I_integer_var*		get_integer_var_ptr ()
				{
				    return (! m_var_ptr) ? 0 : m_var_ptr->
					get_integer_var_ptr ();
				}
    I_real_var*			get_real_var_ptr ()
				{
				    return (! m_var_ptr) ? 0 : m_var_ptr->
					get_real_var_ptr ();
				}
    I_string_var*		get_string_var_ptr ()
				{
				    return (! m_var_ptr) ? 0 : m_var_ptr->
					get_string_var_ptr ();
				}
    I_unique_id_var*		get_unique_id_var_ptr ()
				{
				    return (! m_var_ptr) ? 0 : m_var_ptr->
					get_unique_id_var_ptr ();
				}
    I_current_state_var*	get_current_state_var_ptr ()
				{
				    return (! m_var_ptr) ? 0 : m_var_ptr->
					get_current_state_var_ptr ();
				}
    I_object_inst_ref_var*	get_object_inst_ref_var_ptr ()
				{
				    return (! m_var_ptr) ? 0 : m_var_ptr->
					get_object_inst_ref_var_ptr ();
				}
    I_object_inst_ref_set_var*	get_object_inst_ref_set_var_ptr ()
				{
				    return (! m_var_ptr) ? 0 : m_var_ptr->
					get_object_inst_ref_set_var_ptr ();
				}
    I_event_inst_var*		get_event_inst_var_ptr ()
				{
				    return (! m_var_ptr) ? 0 : m_var_ptr->
					get_event_inst_var_ptr ();
				}
    I_mapping_inst_var*		get_mapping_inst_var_ptr ()
				{
				    return (! m_var_ptr) ? 0 : m_var_ptr->
					get_mapping_inst_var_ptr ();
				}
    I_mapping_inst_ref_var*	get_mapping_inst_ref_var_ptr ()
				{
				    return (! m_var_ptr) ? 0 : m_var_ptr->
					get_mapping_inst_ref_var_ptr ();
				}
    I_date_var*			get_date_var_ptr ()
				{
				    return (! m_var_ptr) ? 0 : m_var_ptr->
					get_date_var_ptr ();
				}
    I_timestamp_var*		get_timestamp_var_ptr ()
				{
				    return (! m_var_ptr) ? 0 : m_var_ptr->
					get_timestamp_var_ptr ();
				}
    I_timer_inst_ref_var*	get_timer_inst_ref_var_ptr ()
				{
				    return (! m_var_ptr) ? 0 : m_var_ptr->
					get_timer_inst_ref_var_ptr ();
				}
    I_frag_ref_var*		get_frag_ref_var_ptr ()
				{
				    return (! m_var_ptr) ? 0 : m_var_ptr->
					get_frag_ref_var_ptr ();
				}



    const Description&		get_var_name_str () const
				{
				    return m_var_name_str;
				}
    const GS_string&		get_var_frag_name_str () const
				{
				    return m_var_frag_name_str;
				}
    void			set_var_frag_name_str
				    (const GS_string& p_var_frag_name_str)
				{
				    m_var_frag_name_str = p_var_frag_name_str;
				}
    void			replace_var (I_var* p_var_ptr);

				GS_var_si ();
				GS_var_si (const Description& p_var_name_str,
				    t_core_data_type p_core_data_type,
				    t_user_data_type p_user_data_type);
    virtual			~GS_var_si ();



private:
				GS_var_si (I_var* p_var_ptr,
				    const Description& p_var_name_str);
				GS_var_si (I_var* p_var_ptr,
				    const Description& p_var_name_str,
				    const GS_string& p_var_frag_name_str);
    virtual GS_var_si*		get_var_si_ptr ()
				{
				    return this;
				}

    Description			m_var_name_str;
    GS_string			m_var_frag_name_str;
    I_var*			m_var_ptr;
};





class GS_ctrl_si : public GS_stack_item

{
friend GS_stack;

public:


protected:
			GS_ctrl_si ()
			{
			}
    virtual		~GS_ctrl_si ()
			{
			}


private:
    virtual GS_ctrl_si*	get_ctrl_si_ptr ()
			{
			    return this;
			}
};





class GS_include_si : public GS_ctrl_si

{
friend GS_stack;

public:
    const GS_string&		get_include_arch_file_name_str () const
			{
			    return m_include_arch_file_name_str;
			}

    virtual		~GS_include_si ()
			{
			}

private:
			GS_include_si (streampos p_return_char_num,
			    t_uint p_return_line_num,
			    const GS_string& p_return_arch_file_name_str,
			    const GS_string& p_include_arch_file_name_str)
			{
			    m_return_char_num = p_return_char_num;
			    m_return_line_num = p_return_line_num;
			    m_return_arch_file_name_str
				= p_return_arch_file_name_str;
			    m_include_arch_file_name_str
				= p_include_arch_file_name_str;
			}
    virtual GS_include_si*
			get_include_si_ptr ()
			{
			    return this;
			}
    streampos		m_return_char_num;
    t_uint		m_return_line_num;
    GS_string		m_return_arch_file_name_str;
    GS_string		m_include_arch_file_name_str;
};





class GS_function_si : public GS_ctrl_si

{
friend GS_stack;
friend GS_gen_action;
friend SIM_SOR;

public:
    const GS_string&	get_func_name_str () const
			{
			    return m_func_name_str;
			}
    I_frag_ref_var*     get_return_frag_ref_var_ptr ()
			{
			    return m_return_frag_ref_var_ptr;
			}

    virtual		~GS_function_si ()
			{
			}

private:
    			GS_function_si
			    (I_frag_ref_var* p_return_frag_ref_var_ptr,
			    streampos p_return_char_num,
			    t_uint p_return_line_num,
			    const GS_string& p_return_arch_file_name_str,
			    const GS_string& p_func_name_str)
			{
			    m_return_frag_ref_var_ptr
				= p_return_frag_ref_var_ptr;
			    m_return_char_num = p_return_char_num;
			    m_return_line_num = p_return_line_num;
			    m_return_arch_file_name_str
				= p_return_arch_file_name_str;
			    m_func_name_str = p_func_name_str;
			}
    virtual GS_function_si*
			get_function_si_ptr ()
			{
			    return this;
			}
    I_frag_ref_var*     m_return_frag_ref_var_ptr;
    streampos           m_return_char_num;
    t_uint              m_return_line_num;
    GS_string           m_return_arch_file_name_str;
    GS_string           m_func_name_str;
};





class GS_for_si : public GS_ctrl_si

{
friend GS_stack;
friend GS_gen_action;
friend SIM_SOR;

public:
    const Description&	get_inst_name_str () const
			{
			    return m_inst_name_str;
			}
    const Description&	get_inst_set_name_str () const
			{
			    return m_inst_set_name_str;
			}
    streampos		get_begin_char_num ()
			{
			    return m_begin_char_num;
			}
    t_uint		get_begin_line_num ()
			{
			    return m_begin_line_num;
			}

    virtual		~GS_for_si ()
			{
			}

private:
			GS_for_si (const Description& p_inst_name_str,
			    const Description& p_inst_set_name_str,
			    streampos p_begin_char_num,
			    t_uint p_begin_line_num)
			{
			    m_inst_name_str = p_inst_name_str;
			    m_inst_set_name_str = p_inst_set_name_str;
			    m_begin_char_num = p_begin_char_num;
			    m_begin_line_num = p_begin_line_num;
			}
    
    virtual GS_for_si*	get_for_si_ptr ()
			{
			    return this;
			}
    Description		m_inst_name_str;
    Description		m_inst_set_name_str;
    streampos		m_begin_char_num;
    t_uint		m_begin_line_num;
};





class GS_while_si : public GS_ctrl_si

{
friend GS_stack;
friend GS_gen_action;
friend SIM_SOR;

public:
    streampos		get_begin_char_num ()
			{
			    return m_begin_char_num;
			}
    t_uint		get_begin_line_num ()
			{
			    return m_begin_line_num;
			}

    virtual		~GS_while_si ();

private:
			GS_while_si (const Description& p_while_stmt_str,
			    streampos p_begin_char_num,
			    t_uint p_begin_line_num);
    
    virtual GS_while_si*
			get_while_si_ptr ()
			{
			    return this;
			}
    Description		m_while_stmt_str;
    streampos		m_begin_char_num;
    t_uint		m_begin_line_num;
};





class GS_if_si : public GS_ctrl_si

{
friend GS_stack;
friend GS_gen_action;
friend SIM_SOR;

public:
    t_boolean		get_condition_result ()
			{
			    return m_condition_result;
			}
    void		set_condition_result (t_boolean p_condition_result)
			{
			    m_condition_result = p_condition_result;
			}
    t_boolean		get_else_encountered ()
			{
			    return m_else_encountered;
			}
    void		set_else_encountered (t_boolean p_else_encountered)
			{
			    m_else_encountered = p_else_encountered;
			}

    virtual		~GS_if_si ()
			{
			}

private:
			GS_if_si (t_boolean p_condition_result)
			{
			    m_condition_result = p_condition_result;
			    m_else_encountered = FALSE;
			}
    virtual GS_if_si*	get_if_si_ptr ()
			{
			    return this;
			}
    t_boolean		m_condition_result;
    t_boolean		m_else_encountered;
};





class GS_frag_gen_si : public GS_ctrl_si

{
friend GS_stack;

public:


private:
			GS_frag_gen_si ();
			virtual ~GS_frag_gen_si ();
    virtual GS_frag_gen_si*
			get_frag_gen_si_ptr ()
			{
			    return this;
			}
};




#endif

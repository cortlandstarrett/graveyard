/*========================================================================
 *
 * File:      $RCSfile: gs_func.hh,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:18 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#ifndef GS_FUNC_HH
#define GS_FUNC_HH

#include <iostream.h>

#ifdef OLD_FILE_NAMES
#include <U_typedefs.hh>
#else
#include <u_typdef.hh>
#endif


#include <u_string.hh>
#include <gs_sizes.hh>


class GS_func_def;




class GS_func_param_def

{
friend GS_func_def;


public:
    enum                e_param_type
			{
			    PARAM_UNASSIGNED,
			    PARAM_INST_REF,
			    PARAM_INST_REF_SET,
			    PARAM_FRAG_REF,
			    PARAM_BOOLEAN,
			    PARAM_INTEGER,
			    PARAM_REAL,
			    PARAM_STRING
			};
        

private:
                        GS_func_param_def ();
                        ~GS_func_param_def ();
                        
    e_param_type        m_param_type;
    GS_string           m_formal_param_name_str;
};




class GS_func_def
{
public:
    static void		    init ();

    static t_boolean        is_predefined (const GS_string& p_func_name_str)
				{ GS_func_def* func_def_ptr =
				    find_func_def_ptr (p_func_name_str);
				  return (func_def_ptr)
				    ? func_def_ptr->m_is_predefined : FALSE; }
    static t_boolean	    exec_predefined
				(const GS_string& p_func_name_str);

    static t_boolean	    is_valid_func_name
				(const GS_string& p_func_name_str)
				{ return find_func_def_ptr (p_func_name_str)
				    ? TRUE : FALSE; }
    static streampos        get_start_char_num
				(const GS_string& p_func_name_str);
    static void             set_start_char_num
				(const GS_string& p_func_name_str,
				streampos p_start_char_num);
    static t_uint           get_start_line_num
				(const GS_string& p_func_name_str);
    static void             set_start_line_num
				(const GS_string& p_func_name_str,
				t_uint p_start_line_num);
    static GS_string        get_arch_file_name_str
				(const GS_string& p_func_name_str);

    static t_uint           get_num_formal_param
				(const GS_string& p_func_name_str);
    static GS_string        get_formal_param_name_str
				(const GS_string& p_func_name_str,
				t_uint  p_formal_param_num);
    static t_boolean          is_formal_param_inst_ref
				(const GS_string& p_func_name_str,
				t_uint  p_formal_param_num);
    static t_boolean          is_formal_param_inst_ref_set
				(const GS_string& p_func_name_str,
				t_uint  p_formal_param_num);
    static t_boolean          is_formal_param_frag_ref
				(const GS_string& p_func_name_str,
				t_uint  p_formal_param_num);
    static t_boolean          is_formal_param_boolean
				(const GS_string& p_func_name_str,
				t_uint  p_formal_param_num);
    static t_boolean          is_formal_param_integer
				(const GS_string& p_func_name_str,
				t_uint  p_formal_param_num);
    static t_boolean          is_formal_param_real
				(const GS_string& p_func_name_str,
				t_uint  p_formal_param_num);
    static t_boolean          is_formal_param_string
				(const GS_string& p_func_name_str,
				t_uint  p_formal_param_num);
                            
    static t_boolean          create_func_def (const GS_string& p_func_name_str,
				streampos p_start_char_num,
				t_uint  p_start_line_num,
				const GS_string& p_arch_file_name_str);
    static void               add_param_to_func_def
				(const GS_string& p_func_name_str,
				GS_func_param_def::e_param_type p_param_type,
				const GS_string& p_formal_param_name_str);
    


private:
			    GS_func_def (const GS_string& p_func_name_str,
				streampos p_start_char_num,
				t_uint p_start_line_num,
				const GS_string& p_arch_file_name_str);
			    ~GS_func_def ();
    static GS_func_def*     find_func_def_ptr
				(const GS_string& p_func_name_str);
    
    GS_string               m_func_name_str;
    GS_func_param_def       m_formal_param [GS_MAX_NUM_PARAMS_PER_FUNC_DEF];
    t_uint                  m_num_formal_param;
    streampos               m_start_char_num;
    t_uint                  m_start_line_num;
    GS_string               m_arch_file_name_str;
    t_boolean               m_is_predefined;
};




#endif

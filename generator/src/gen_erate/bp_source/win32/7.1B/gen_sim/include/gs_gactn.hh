/*========================================================================
 *
 * File:      $RCSfile: gs_gactn.hh,v $
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
#ifndef GS_GACTN_HH
#define GS_GACTN_HH

#include <u_typdef.hh>

#include <gs_actn.hh>


class GS_string;
class GS_var_si;




class GS_gen_action : public GS_action

{
public:
    			GS_gen_action (const GS_string& p_action_str)
			    : GS_action (p_action_str) {}
    virtual		~GS_gen_action () {}

    static void		gen_actn_script
			    (e_action_home p_action_home,
			    GS_var_si* p_actn_inst_var_si_ptr,
			    const GS_string& p_script_file_name_str);




private:
    static GS_string	al_inst_var_name_str;

    enum e_blck_type	{
			BLCK_ACTN,
			BLCK_FOR,
			BLCK_IF
			};

    enum e_value_type	{
			VALUE_DATA,
			VALUE_OBJ_INST_REF,
			VALUE_OBJ_INST_REF_SET
			};

    GS_string		gen_blck_script (e_blck_type p_blck_type,
			    GS_action::e_action_home p_action_home = NONE);
    static GS_string	gen_stmt_script__select
			    (const GS_string& p_stmt_str);
    static GS_string	gen_stmt_script__for
			    (const GS_string& p_stmt_str,
			    const GS_string& p_for_blck_str);
    static GS_string	gen_stmt_script__create_obj
			    (const GS_string& p_stmt_str);
    static GS_string	gen_stmt_script__create_evt
			    (const GS_string& p_stmt_str);
    static GS_string	gen_stmt_script__delete
			    (const GS_string& p_stmt_str);
    static GS_string	gen_stmt_script__relate
			    (const GS_string& p_stmt_str);
    static GS_string	gen_stmt_script__unrelate
			    (const GS_string& p_stmt_str);
    static GS_string	gen_stmt_script__generate
			    (const GS_string& p_stmt_str);
    static GS_string	gen_stmt_script__assign
			    (const GS_string& p_stmt_str);
    static GS_string	gen_stmt_script__transform
			    (const GS_string& p_stmt_str);
    static GS_string	gen_stmt_script__if
			    (const GS_string& p_stmt_str,
			    const GS_string& p_if_blck_str);
    static GS_string	gen_stmt_script__else
			    (const GS_string& p_else_blck_str);
    static GS_string	gen_stmt_script__bridge
			    (const GS_string& p_stmt_str);
    static GS_string	gen_stmt_script__return
			    (const GS_string& p_stmt_str);


    void		parse_blck__for
			    (GS_string& p_for_stmt_str,
			    GS_string& p_for_blck_str);
    void		parse_blck__if_else
			    (GS_string& p_if_stmt_str,
			    GS_string& p_if_blck_str,
			    GS_string& p_else_blck_str);


    static GS_string	gen_expr_script
			    (const GS_string& p_expr_str,
			    e_value_type& p_rvalue_type,
			    GS_string& p_rvalue_type_parameter_str);
    static GS_string	gen_rval_script
			    (const GS_string& p_rval_str,
			    e_value_type& p_rvalue_type,
			    GS_string& p_rvalue_type_parameter_str);
    static GS_string	gen_chain_script
			    (const GS_string& p_cardinality_str,
			    const GS_string& p_chain_str,
			    GS_string& p_result_obj_keyletters_str);
    static GS_string	gen_param_script
			    (const GS_string& p_param_begin_comp_name_str,
			    const GS_string& p_param_str);


    static GS_string	output_script__actn
			    (const GS_string& p_actn_script_str);
    static GS_string	output_script__blck
			    (const GS_string& p_blck_script_str);
    static GS_string	output_script__stmt
			    (const GS_string& p_stmt_script_str);
    static GS_string	output_script__rval
			    (const GS_string& p_rval_script_str);
    static GS_string	output_script__chain
			    (const GS_string& p_chain_script_str);
    static GS_string	output_script__param
			    (const GS_string& p_param_script_str);
    static GS_string	output_script__var
			    (const GS_string& p_param_script_str);


    static t_uint	s_actn_inst_num;
    static t_uint	s_blck_inst_num;
    static t_uint	s_stmt_inst_num;
    static t_uint	s_rval_inst_num;
    static t_uint	s_chain_inst_num;
    static t_uint	s_param_inst_num;
    static t_uint	s_var_inst_num;

    static GS_string	s_script_str;
};




#endif

/*========================================================================
 *
 * File:      $RCSfile: gs_selct.hh,v $
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
#include <mc_dbms/mc_dbms.hh>

#ifndef GS_SELCT_HH
#define GS_SELCT_HH


#include <u_typdef.hh>
#include <d_typdef.hh>

#include <gs_stack.hh>


class I_Object_Instance;
class I_Related_Object_Pair;
class GS_string;
class I_object_inst_ref_var;
class I_object_inst_ref_set_var;




class GS_select

{
public:
    static void		print_select_stmt_error
			    ();
    static t_boolean	interpret_stmt__select
			    (const Description& p_stmt_str);
    static t_boolean	select_any__from_instances_of
			    (const Description& p_inst_set_var_name_str,
			     const Description& p_object_name_str,
			     const Description& p_condition_str);
    static t_boolean	select_one_any__related_by
			    (const Description& p_cardinality_str,
			     const Description& p_inst_var_name_str,
			     const Description& p_inst_chain_str,
			     const Description& p_condition_str);
    static t_boolean	select_many__from_instances_of
			    (const Description& p_inst_set_var_name_str,
			     const Description& p_object_name_str,
			     const Description& p_condition_str);
    static t_boolean	select_many__related_by
			    (const Description& p_inst_set_var_name_str,
			     const Description& p_inst_chain_str,
			     const Description& p_condition_str);

    static I_object_inst_ref_set_var*
			create_single_link
			    (I_object_inst_ref_set_var*
				p_start_inst_set_var_ptr,
			     const Description& p_end_obj_key_letter_str,
			     Description p_rel_name_str,
			     Description p_rel_direction_str);

    static void	interpret_frag__where_clause
			    (I_object_inst_ref_set_var* p_inst_set_var_ptr,
			     const Description& p_condition_str,
			     t_boolean p_any_flag);

private:
    static t_boolean	is_valid_object
			    (const GS_string& p_obj_key_letter_str);
    static I_object_inst_ref_set_var*
			create__from_instances_of__no_push
			    (const Description& p_object_name_str,
			     const Description& p_condition_str,
			     t_boolean p_any_flag);
    static I_object_inst_ref_set_var*
			create__related_by__no_push
			    (const Description& p_inst_chain_str,
			     const Description& p_condition_str,
			     t_boolean p_any_flag);
};




#endif

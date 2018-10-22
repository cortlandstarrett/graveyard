/*========================================================================
 *
 * File:      $RCSfile: u_keyword.hh,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:34 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#ifndef U_KEYWORD_HH
#define U_KEYWORD_HH

#include <u_desc.hh>

extern Description dot_select;
extern Description select_string;
extern Description dot_for;
extern Description for_string;
extern Description for_semi;
extern Description each_string;
extern Description in_string;
extern Description dot_while;
extern Description while_string;
extern Description while_semi;
extern Description dot_break;
extern Description dot_assign;
extern Description assign_string;
extern Description dot_if;
extern Description if_string;
extern Description if_semi;
extern Description dot_elif;
extern Description elif_string;
extern Description dot_else;
extern Description dot_function;
extern Description function_string;
extern Description function_semi;
extern Description dot_invoke;
extern Description dot_param;
extern Description dot_end;
extern Description dot_include;
extern Description dot_slashes;
extern Description dot_comment;
extern Description dot_log;
extern Description stmt_string;
extern Description comp_string;
extern Description sys_string;
extern Description dot_clear;
extern Description dot_emit;
extern Description dot_print;
extern Description dot_exit;
extern Description dot_license;
extern Description dot_special_where;
extern Description add_string;
extern Description clear_string;
extern Description query_string;
extern Description all1_string;
extern Description all2_string;
extern Description all3_string;

extern Description inst_ref_string;
extern Description inst_ref_set_string;
extern Description frag_ref_string;
extern Description boolean_string;
extern Description integer_string;
extern Description real_string;
extern Description string_string;

extern Description not_string;
extern Description empty_string;
extern Description not_empty_string;
extern Description first_string;
extern Description not_first_string;
extern Description last_string;
extern Description not_last_string;
extern Description cardinality_string;
extern Description obj_key_letters_string;
extern Description initialized_string;
extern Description not_initialized_string;
extern Description and_string;
extern Description or_string;
extern Description equal_equal_string;
extern Description bang_equal_string;

extern Description dot_al_xlate;
extern Description script_string;
extern Description to_string;
extern Description file_string;
extern Description assigner_sm_string;
extern Description assigner_state_string;
extern Description attribute_string;
extern Description bridge_string;
extern Description data_type_string;
extern Description ee_event_string;
extern Description instance_sm_string;
extern Description instance_state_string;
extern Description relationship_string;
extern Description sm_event_string;
extern Description synch_service_string;
extern Description transformer_string;

extern Description one_string;
extern Description any_string;
extern Description many_string;
extern Description self_string;
extern Description related_string;
extern Description by_string;
extern Description from_string;
extern Description instances_string;
extern Description of_string;
extern Description selected_string;

extern Description lc_void_string;
extern Description lc_enumeration_string;
extern Description lc_boolean_string;
extern Description lc_integer_string;
extern Description lc_real_string;
extern Description lc_string_string;
extern Description lc_unique_id_string;
extern Description lc_state_model_string;
extern Description lc_inst_ref_string;
extern Description lc_inst_ref_set_string;
extern Description lc_inst_event_string;
extern Description lc_inst_mapping_string;
extern Description lc_inst_ref_mapping_string;
extern Description lc_date_string;
extern Description lc_timestamp_string;
extern Description lc_inst_ref_timer_string;
extern Description lc_fragment_string;
extern Description lc_user_defined_string;

extern Description rcvd_evt_string;
extern Description param_string;
extern Description true_string;
extern Description false_string;

extern Description ret_val_string;
extern Description obj_kl_string;
extern Description where_spec_string;
extern Description key_string;

extern Description lc_body_string;

extern Description info_string;
extern Description date_string;
extern Description interpreter_version_string;
extern Description interpreter_platform_string;
extern Description user_id_string;
extern Description arch_file_name_string;
extern Description arch_file_line_string;
extern Description unique_num_string;

extern Description create_string;
extern Description table_string;
extern Description unique_id_string;
extern Description rop_string;
extern Description ref_id_string;
extern Description onec_string;
extern Description m_string;
extern Description mc_string;
extern Description num_one_string;
extern Description phrase_string;
extern Description chain_string;
extern Description through_string;
extern Description ir_string;
extern Description ri_string;
extern Description insert_string;
extern Description values_string;
extern Description descrip_string;
extern Description zero_string;
extern Description dash_dash_string;

extern Description right_paren_semi;

extern Description dot_create;
extern Description object_string;
extern Description instance_string;

extern void keyword_init();

#endif


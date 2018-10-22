/*========================================================================
 *
 * File:      $RCSfile: u_keyword.cc,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:59 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#include <u_keyword.hh>

Description dot_select( ".SELECT");
Description select_string( "SELECT");
Description dot_for( ".FOR");
Description for_string( "FOR");
Description for_semi( "FOR;");
Description each_string( "EACH" );
Description in_string( "IN" );
Description dot_while( ".WHILE");
Description while_string( "WHILE");
Description while_semi( "WHILE;");
Description dot_break( ".BREAK");
Description dot_assign( ".ASSIGN");
Description assign_string( "ASSIGN");
Description dot_if( ".IF");
Description if_string( "IF");
Description if_semi( "IF;");
Description dot_elif( ".ELIF");
Description elif_string( "ELIF");
Description dot_else( ".ELSE");
Description dot_function( ".FUNCTION");
Description function_string( "FUNCTION");
Description function_semi( "FUNCTION;");
Description dot_invoke( ".INVOKE");
Description dot_param( ".PARAM");
Description dot_end( ".END");
Description dot_include( ".INCLUDE");
Description dot_slashes( ".//");
Description dot_comment( ".COMMENT");
Description dot_log( ".LOG");
Description stmt_string( "STMT");
Description comp_string( "COMP");
Description sys_string( "SYS");
Description dot_clear( ".CLEAR");
Description dot_emit( ".EMIT");
Description dot_print( ".PRINT");
Description dot_exit( ".EXIT");
Description dot_license( ".LICENSE");
Description dot_special_where( ".SPECIAL_WHERE");
Description add_string( "ADD");
Description clear_string( "CLEAR");
Description query_string( "QUERY");
Description all1_string( "ALL");
Description all2_string( "All");
Description all3_string( "all");

Description inst_ref_string( "INST_REF");
Description inst_ref_set_string( "INST_REF_SET");
Description frag_ref_string( "FRAG_REF");
Description boolean_string( "BOOLEAN");
Description integer_string( "INTEGER");
Description real_string( "REAL");
Description string_string( "STRING");

Description empty_string( "EMPTY" );
Description not_string( "NOT" );
Description not_empty_string( "NOT_EMPTY" );
Description first_string( "FIRST" );
Description not_first_string( "NOT_FIRST" );
Description last_string( "LAST" );
Description not_last_string( "NOT_LAST" );
Description cardinality_string( "CARDINALITY" );
Description obj_key_letters_string( "OBJ_KEY_LETTERS");
Description initialized_string( "INITIALIZED" );
Description not_initialized_string( "NOT_INITIALIZED" );
Description and_string("AND");
Description or_string("OR");
Description equal_equal_string("==");
Description bang_equal_string("!=");

Description dot_al_xlate( ".AL_XLATE");
Description script_string( "SCRIPT" );
Description to_string( "TO");
Description file_string( "FILE");
Description assigner_sm_string( "ASSIGNER_SM");
Description assigner_state_string( "ASSIGNER_STATE");
Description attribute_string( "ATTRIBUTE");
Description bridge_string( "BRIDGE");
Description data_type_string( "DATA_TYPE");
Description ee_event_string( "EE_EVENT");
Description instance_sm_string( "INSTANCE_SM");
Description instance_state_string( "INSTANCE_STATE");
Description relationship_string( "RELATIONSHIP");
Description sm_event_string( "SM_EVENT");
Description synch_service_string( "SYNCH_SERVICE");
Description transformer_string( "TRANSFORMER");

Description one_string("ONE");
Description any_string("ANY");
Description many_string("MANY");
Description self_string("self");
Description related_string("RELATED");
Description by_string("BY");
Description from_string("FROM");
Description instances_string("INSTANCES");
Description of_string("OF");
Description selected_string("SELECTED");

Description lc_void_string("void");
Description lc_enumeration_string("enumeration");
Description lc_boolean_string("boolean");
Description lc_integer_string("integer");
Description lc_real_string("real");
Description lc_string_string("string");
Description lc_unique_id_string("unique_id");
Description lc_state_model_string("");
Description lc_inst_ref_string("");
Description lc_inst_ref_set_string("");
Description lc_inst_event_string("inst<Event>");
Description lc_inst_mapping_string("inst<Mapping>");
Description lc_inst_ref_mapping_string("");
Description lc_date_string("date");
Description lc_timestamp_string("timestamp");
Description lc_inst_ref_timer_string("inst_ref<Timer>");
Description lc_fragment_string("fragment");
Description lc_user_defined_string("user defined");

Description rcvd_evt_string("RCVD_EVT");
Description param_string("PARAM");
Description true_string("TRUE");
Description false_string("FALSE");

Description ret_val_string("RET_VAL");
Description obj_kl_string("OBJ_KL");
Description where_spec_string("WHERE_SPEC");
Description key_string("KEY");

Description lc_body_string("body");

Description info_string("INFO");
Description date_string("DATE");
Description interpreter_version_string("");
Description interpreter_platform_string("");
Description user_id_string("USER_ID");
Description arch_file_name_string("ARCH_FILE_NAME");
Description arch_file_line_string("ARCH_FILE_LINE");
Description unique_num_string("UNIQUE_NUM");

Description create_string("CREATE");
Description table_string("TABLE");
Description unique_id_string("UNIQUE_ID");
Description rop_string("ROP");
Description ref_id_string("REF_ID");
Description onec_string("1C");
Description m_string("M");
Description mc_string("MC");
Description num_one_string("1");
Description phrase_string("PHRASE");
Description chain_string("CHAIN");
Description through_string("THROUGH");
Description ir_string("IR");
Description ri_string("RI");
Description insert_string("INSERT");
Description values_string("VALUES");
Description descrip_string("DESCRIP");
Description zero_string("0");
Description dash_dash_string("--");
Description right_paren_semi(");");

Description dot_create(".CREATE");
Description object_string("OBJECT");
Description instance_string("INSTANCE");

void keyword_init()
{
    lc_state_model_string = "state<State_Model>";
    lc_inst_ref_string = "inst_ref<Object>";
    lc_inst_ref_set_string = "inst_ref_set<Object>";
    lc_inst_ref_mapping_string = "inst_ref<Mapping>";
    interpreter_version_string = "INTERPRETER_VERSION";
    interpreter_platform_string = "INTERPRETER_PLATFORM";
}

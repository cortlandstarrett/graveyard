/*========================================================================
 *
 * File:      $RCSfile: sim_rd3.cpp,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:21 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#include "SIM_SOR.h"

#include <gs_obj.hh>
#include <gs_stack.hh>
#include <gs_ui.hh>
#include <gs_find.hh>                               
#include <gs_sorsim.hh>

#include <i_oinst.hh>
#include <i_ainst.hh>
#include <i_var.hh>
#include <i_attr.hh>

#include <d_bridge.hh>
#include <d_dattyp.hh>
#include <d_object.hh>                               
#include <d_battr.hh>
#include <d_parm.hh>
#include <d_tfmr.hh>

#include <u_cursor.hh>                               


extern mc_dbms_database* GS_gen_sim_db_ptr;


void SIM_SOR::interpret_op_relational_eq ( GS_var_si &p_rvalue, 
  GS_var_si &operand1, GS_var_si &operand2 )
{
       if ( operand1.get_var_ptr()->get_core_data_type() == BOOLEAN_DATATYPE &&
            operand2.get_var_ptr()->get_core_data_type() == BOOLEAN_DATATYPE )
       {
         p_rvalue.replace_var (new I_boolean_var ((t_boolean)
           (operand1.get_boolean_var_ptr ()->get_value ()
          == operand2.get_boolean_var_ptr ()->get_value ())));
         LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
           "BOOLEAN   ==   BOOLEAN"));
       }
       else if ( operand1.get_var_ptr()->get_core_data_type() == ENUMERATION_DATATYPE &&
            operand2.get_var_ptr()->get_core_data_type() == ENUMERATION_DATATYPE )
       {
         p_rvalue.replace_var (new I_boolean_var ((t_boolean)
           (operand1.get_enumerator_var_ptr ()->get_value ()
          == operand2.get_enumerator_var_ptr ()->get_value ())));
         LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
           "ENUMERATION == ENUMERATION"));
       }
       else if ( operand1.get_var_ptr()->get_core_data_type() == INTEGER_DATATYPE &&
            operand2.get_var_ptr()->get_core_data_type() == INTEGER_DATATYPE )
       {
         p_rvalue.replace_var (new I_boolean_var ((t_boolean)
           (operand1.get_integer_var_ptr ()->get_value ()
          == operand2.get_integer_var_ptr ()->get_value ())));
         LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
           "INTEGER   ==   INTEGER"));
       }
       else if ( operand1.get_var_ptr()->get_core_data_type() == INTEGER_DATATYPE &&
                 operand2.get_var_ptr()->get_core_data_type() == REAL_DATATYPE )
       {
         p_rvalue.replace_var (new I_boolean_var ((t_boolean)
           (operand1.get_integer_var_ptr ()->get_value ()
          == operand2.get_real_var_ptr()->get_value ())));
         LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
           "INTEGER   ==   REAL"));
       }
       else if ( operand1.get_var_ptr()->get_core_data_type() == REAL_DATATYPE &&
                 operand2.get_var_ptr()->get_core_data_type() == INTEGER_DATATYPE )
       {
         p_rvalue.replace_var (new I_boolean_var ((t_boolean)
           (operand1.get_real_var_ptr ()->get_value ()
          == operand2.get_integer_var_ptr()->get_value ())));
         LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
           "REAL      ==   INTEGER"));
       }
       else if ( operand1.get_var_ptr()->get_core_data_type() == REAL_DATATYPE &&
                 operand2.get_var_ptr()->get_core_data_type() == REAL_DATATYPE )
       {
         p_rvalue.replace_var (new I_boolean_var ((t_boolean)
           (operand1.get_real_var_ptr ()->get_value ()
          == operand2.get_real_var_ptr()->get_value ())));
         LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
           "REAL      ==   REAL"));
       }
       else if ( operand1.get_var_ptr()->get_core_data_type() == UNIQUE_ID_DATATYPE &&
                 operand2.get_var_ptr()->get_core_data_type() == UNIQUE_ID_DATATYPE )
       {
         p_rvalue.replace_var (new I_boolean_var ((t_boolean)
           (operand1.get_unique_id_var_ptr ()->get_value ()
          == operand2.get_unique_id_var_ptr()->get_value ())));
         LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
           "UNIQUE_ID   ==   UNIQUE_ID"));
       }
       else if ( operand1.get_var_ptr()->get_core_data_type() == UNIQUE_ID_DATATYPE &&
                 operand2.get_var_ptr()->get_core_data_type() == INTEGER_DATATYPE )
       {
         p_rvalue.replace_var (new I_boolean_var ((t_boolean)
           (operand1.get_unique_id_var_ptr ()->get_value ()
          == operand2.get_integer_var_ptr()->get_value ())));
         LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
           "UNIQUE_ID   ==   INTEGER"));
       }
       else if ( operand1.get_var_ptr()->get_core_data_type() == INTEGER_DATATYPE &&
                 operand2.get_var_ptr()->get_core_data_type() == UNIQUE_ID_DATATYPE )
       {
         p_rvalue.replace_var (new I_boolean_var ((t_boolean)
           (operand1.get_integer_var_ptr ()->get_value ()
          == operand2.get_unique_id_var_ptr()->get_value ())));
         LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
           "INTEGER   ==   UNIQUE_ID"));
       }
       else if ( operand1.get_var_ptr()->get_core_data_type() == STRING_DATATYPE &&
                 operand2.get_var_ptr()->get_core_data_type() == STRING_DATATYPE )
       {
         p_rvalue.replace_var (new I_boolean_var ((t_boolean)
           (operand1.get_string_var_ptr ()->get_value ()
          == operand2.get_string_var_ptr()->get_value ())));
         LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
           "STRING   ==   STRING"));
       }
       else if ( operand1.get_var_ptr()->get_core_data_type() == OBJECT_INST_REF_DATATYPE &&
                 operand2.get_var_ptr()->get_core_data_type() == OBJECT_INST_REF_DATATYPE )
       {
         p_rvalue.replace_var (new I_boolean_var ((t_boolean) 
           ((*(operand1.get_var_ptr ()))
           == (*(operand2.get_var_ptr ())))));
         LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
           "OBJECT_INST_REF   ==   OBJECT_INST_REF"));
       }
       else if ( operand1.get_var_ptr()->get_core_data_type() == OBJECT_INST_REF_SET_DATATYPE &&
                 operand2.get_var_ptr()->get_core_data_type() == OBJECT_INST_REF_SET_DATATYPE )
       {
         p_rvalue.replace_var (new I_boolean_var ((t_boolean) 
           ((*(operand1.get_var_ptr ()))
           == (*(operand2.get_var_ptr ())))));
         LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
           "OBJECT_INST_REF_SET   ==   OBJECT_INST_REF_SET"));
       }
       else if ( operand1.get_var_ptr()->get_core_data_type() == EVENT_INST_DATATYPE &&
                 operand2.get_var_ptr()->get_core_data_type() == EVENT_INST_DATATYPE )
       {
         p_rvalue.replace_var (new I_boolean_var ((t_boolean) 
           ((*(operand1.get_var_ptr ()))
           == (*(operand2.get_var_ptr ())))));
         LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
           "EVENT_INST_DATATYPE   ==   EVENT_INST_DATATYPE"));
       }
       else if ( operand1.get_var_ptr()->get_core_data_type() == MAPPING_INST_DATATYPE )
       {
         if ( operand1.get_var_ptr()->get_user_data_type() == USER_DEFINED_USERDATATYPE &&
              operand2.get_var_ptr()->get_user_data_type() == USER_DEFINED_USERDATATYPE )
         {
           p_rvalue.replace_var (new I_boolean_var ((t_boolean)
             ((*(operand1.get_var_ptr ()))
             == (*(operand2.get_var_ptr ())))));
           LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
             "USER_DEFINED   ==   USER_DEFINED"));
         }
         else if ( operand1.get_var_ptr()->get_user_data_type() == DATE_USERDATATYPE &&
                   operand2.get_var_ptr()->get_user_data_type() == DATE_USERDATATYPE )
         {
           p_rvalue.replace_var (new I_boolean_var ((t_boolean)
             ((*(operand1.get_var_ptr ()))
             == (*(operand2.get_var_ptr ())))));
           LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
             "DATE   ==   DATE"));
         }
         else if ( operand1.get_var_ptr()->get_user_data_type() == TIMESTAMP_USERDATATYPE &&
                   operand2.get_var_ptr()->get_user_data_type() == TIMESTAMP_USERDATATYPE )
         {
           p_rvalue.replace_var (new I_boolean_var ((t_boolean)
             ((*(operand1.get_var_ptr ()))
             == (*(operand2.get_var_ptr ())))));
           LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
             "TIMESTAMP   ==   TIMESTAMP"));
         }
         else
         {
           GS_ui::inform (UI_INFORM__ERROR, GS_string("????   ==   ????"));
           LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		  "MAP_INST ????   ==   MAP_INST ????"));
           // HACK! - invalid expression
         }
       }
       else if ( operand1.get_var_ptr()->get_core_data_type() == MAPPING_INST_REF_DATATYPE )
       {
         if ( operand1.get_var_ptr()->get_user_data_type() == USER_DEFINED_USERDATATYPE &&
              operand2.get_var_ptr()->get_user_data_type() == USER_DEFINED_USERDATATYPE )
         {
           p_rvalue.replace_var (new I_boolean_var ((t_boolean)
             ((*(operand1.get_var_ptr ()))
             == (*(operand2.get_var_ptr ())))));
           LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
             "USER_DEFINED_REF   ==   USER_DEFINED_REF"));
         }
         else if ( operand1.get_var_ptr()->get_user_data_type() == TIMER_INST_REF_USERDATATYPE &&
                   operand2.get_var_ptr()->get_user_data_type() == TIMER_INST_REF_USERDATATYPE )
         {
           p_rvalue.replace_var (new I_boolean_var ((t_boolean)
             ((*(operand1.get_var_ptr ()))
             == (*(operand2.get_var_ptr ())))));
           LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
             "TIMER_INST_REF   ==   TIMER_INST_REF"));
         }
         else
         {
           GS_ui::inform (UI_INFORM__ERROR, GS_string("????   ==   ????"));
           LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		  "MAP_INST_REF ????   ==   MAP_INST_REF ????"));
           // HACK! - invalid expression
         }
       }
       else
       {
         GS_ui::inform (UI_INFORM__ERROR, GS_string("????   ==   ????"));
         LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		"????   ==   ????"));
         // HACK! - invalid expression
       }
}

void SIM_SOR::interpret_op_relational_ne ( GS_var_si &p_rvalue, 
  GS_var_si &operand1, GS_var_si &operand2 )
{
       if ( operand1.get_var_ptr()->get_core_data_type() == BOOLEAN_DATATYPE &&
            operand2.get_var_ptr()->get_core_data_type() == BOOLEAN_DATATYPE )
       {
         p_rvalue.replace_var (new I_boolean_var ((t_boolean)
           (operand1.get_boolean_var_ptr ()->get_value ()
          != operand2.get_boolean_var_ptr ()->get_value ())));
         LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
           "BOOLEAN   !=   BOOLEAN"));
       }
       else if ( operand1.get_var_ptr()->get_core_data_type() == ENUMERATION_DATATYPE &&
            operand2.get_var_ptr()->get_core_data_type() == ENUMERATION_DATATYPE )
       {
         p_rvalue.replace_var (new I_boolean_var ((t_boolean)
           (operand1.get_enumerator_var_ptr ()->get_value ()
          != operand2.get_enumerator_var_ptr ()->get_value ())));
         LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
           "ENUMERATION != ENUMERATION"));
       }
       else if ( operand1.get_var_ptr()->get_core_data_type() == INTEGER_DATATYPE &&
            operand2.get_var_ptr()->get_core_data_type() == INTEGER_DATATYPE )
       {
         p_rvalue.replace_var (new I_boolean_var ((t_boolean)
           (operand1.get_integer_var_ptr ()->get_value ()
          != operand2.get_integer_var_ptr ()->get_value ())));
         LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
           "INTEGER   !=   INTEGER"));
       }
       else if ( operand1.get_var_ptr()->get_core_data_type() == INTEGER_DATATYPE &&
                 operand2.get_var_ptr()->get_core_data_type() == REAL_DATATYPE )
       {
         p_rvalue.replace_var (new I_boolean_var ((t_boolean)
           (operand1.get_integer_var_ptr ()->get_value ()
          != operand2.get_real_var_ptr()->get_value ())));
         LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
           "INTEGER   !=   REAL"));
       }
       else if ( operand1.get_var_ptr()->get_core_data_type() == REAL_DATATYPE &&
                 operand2.get_var_ptr()->get_core_data_type() == INTEGER_DATATYPE )
       {
         p_rvalue.replace_var (new I_boolean_var ((t_boolean)
           (operand1.get_real_var_ptr ()->get_value ()
          != operand2.get_integer_var_ptr()->get_value ())));
         LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
           "REAL      !=   INTEGER"));
       }
       else if ( operand1.get_var_ptr()->get_core_data_type() == REAL_DATATYPE &&
                 operand2.get_var_ptr()->get_core_data_type() == REAL_DATATYPE )
       {
         p_rvalue.replace_var (new I_boolean_var ((t_boolean)
           (operand1.get_real_var_ptr ()->get_value ()
          != operand2.get_real_var_ptr()->get_value ())));
         LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
           "REAL      !=   REAL"));
       }
       else if ( operand1.get_var_ptr()->get_core_data_type() == UNIQUE_ID_DATATYPE &&
                 operand2.get_var_ptr()->get_core_data_type() == UNIQUE_ID_DATATYPE )
       {
         p_rvalue.replace_var (new I_boolean_var ((t_boolean)
           (operand1.get_unique_id_var_ptr ()->get_value ()
          != operand2.get_unique_id_var_ptr()->get_value ())));
         LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
           "UNIQUE_ID   !=   UNIQUE_ID"));
       }
       else if ( operand1.get_var_ptr()->get_core_data_type() == UNIQUE_ID_DATATYPE &&
                 operand2.get_var_ptr()->get_core_data_type() == INTEGER_DATATYPE )
       {
         p_rvalue.replace_var (new I_boolean_var ((t_boolean)
           (operand1.get_unique_id_var_ptr ()->get_value ()
          != operand2.get_integer_var_ptr()->get_value ())));
         LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
           "UNIQUE_ID   !=   INTEGER"));
       }
       else if ( operand1.get_var_ptr()->get_core_data_type() == INTEGER_DATATYPE &&
                 operand2.get_var_ptr()->get_core_data_type() == UNIQUE_ID_DATATYPE )
       {
         p_rvalue.replace_var (new I_boolean_var ((t_boolean)
           (operand1.get_integer_var_ptr ()->get_value ()
          != operand2.get_unique_id_var_ptr()->get_value ())));
         LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
           "INTEGER   !=   UNIQUE_ID"));
       }
       else if ( operand1.get_var_ptr()->get_core_data_type() == STRING_DATATYPE &&
                 operand2.get_var_ptr()->get_core_data_type() == STRING_DATATYPE )
       {
         p_rvalue.replace_var (new I_boolean_var ((t_boolean)
           (operand1.get_string_var_ptr ()->get_value ()
          != operand2.get_string_var_ptr()->get_value ())));
         LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
           "STRING   !=   STRING"));
       }
       else if ( operand1.get_var_ptr()->get_core_data_type() == OBJECT_INST_REF_DATATYPE &&
                 operand2.get_var_ptr()->get_core_data_type() == OBJECT_INST_REF_DATATYPE )
       {
         p_rvalue.replace_var (new I_boolean_var ((t_boolean) 
           (! ((*(operand1.get_var_ptr ()))
           == (*(operand2.get_var_ptr ()))))));
         LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
           "OBJECT_INST_REF   !=   OBJECT_INST_REF"));
       }
       else if ( operand1.get_var_ptr()->get_core_data_type() == OBJECT_INST_REF_SET_DATATYPE &&
                 operand2.get_var_ptr()->get_core_data_type() == OBJECT_INST_REF_SET_DATATYPE )
       {
         p_rvalue.replace_var (new I_boolean_var ((t_boolean) 
           (! ((*(operand1.get_var_ptr ()))
           == (*(operand2.get_var_ptr ()))))));
         LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
           "OBJECT_INST_REF_SET   !=   OBJECT_INST_REF_SET"));
       }
       else if ( operand1.get_var_ptr()->get_core_data_type() == EVENT_INST_DATATYPE &&
                 operand2.get_var_ptr()->get_core_data_type() == EVENT_INST_DATATYPE )
       {
         p_rvalue.replace_var (new I_boolean_var ((t_boolean) 
           (! ((*(operand1.get_var_ptr ()))
           == (*(operand2.get_var_ptr ()))))));
         LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
           "EVENT_INST_DATATYPE   !=   EVENT_INST_DATATYPE"));
       }
       else if ( operand1.get_var_ptr()->get_core_data_type() == MAPPING_INST_DATATYPE )
       {
         if ( operand1.get_var_ptr()->get_user_data_type() == USER_DEFINED_USERDATATYPE &&
              operand2.get_var_ptr()->get_user_data_type() == USER_DEFINED_USERDATATYPE )
         {
           p_rvalue.replace_var (new I_boolean_var ((t_boolean)
             (!((*(operand1.get_var_ptr ()))
             == (*(operand2.get_var_ptr ()))))));
           LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
             "USER_DEFINED   !=   USER_DEFINED"));
         }
         else if ( operand1.get_var_ptr()->get_user_data_type() == DATE_USERDATATYPE &&
                   operand2.get_var_ptr()->get_user_data_type() == DATE_USERDATATYPE )
         {
           p_rvalue.replace_var (new I_boolean_var ((t_boolean)
             (!((*(operand1.get_var_ptr ()))
             == (*(operand2.get_var_ptr ()))))));
           LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
             "DATE   !=   DATE"));
         }
         else if ( operand1.get_var_ptr()->get_user_data_type() == TIMESTAMP_USERDATATYPE &&
                   operand2.get_var_ptr()->get_user_data_type() == TIMESTAMP_USERDATATYPE )
         {
           p_rvalue.replace_var (new I_boolean_var ((t_boolean)
             (!((*(operand1.get_var_ptr ()))
             == (*(operand2.get_var_ptr ()))))));
           LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
             "TIMESTAMP   !=   TIMESTAMP"));
         }
         else
         {
           GS_ui::inform (UI_INFORM__ERROR, GS_string("????   !=   ????"));
           LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		  "MAP_INST ????   !=   MAP_INST ????"));
           // HACK! - invalid expression
         }
       }
       else if ( operand1.get_var_ptr()->get_core_data_type() == MAPPING_INST_REF_DATATYPE )
       {
         if ( operand1.get_var_ptr()->get_user_data_type() == USER_DEFINED_USERDATATYPE &&
              operand2.get_var_ptr()->get_user_data_type() == USER_DEFINED_USERDATATYPE )
         {
           p_rvalue.replace_var (new I_boolean_var ((t_boolean)
             (!((*(operand1.get_var_ptr ()))
             == (*(operand2.get_var_ptr ()))))));
           LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
             "USER_DEFINED_REF   !=   USER_DEFINED_REF"));
         }
         else if ( operand1.get_var_ptr()->get_user_data_type() == TIMER_INST_REF_USERDATATYPE &&
                   operand2.get_var_ptr()->get_user_data_type() == TIMER_INST_REF_USERDATATYPE )
         {
           p_rvalue.replace_var (new I_boolean_var ((t_boolean)
             (!((*(operand1.get_var_ptr ()))
             == (*(operand2.get_var_ptr ()))))));
           LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
             "TIMER_INST_REF   !=   TIMER_INST_REF"));
         }
         else
         {
           GS_ui::inform (UI_INFORM__ERROR, GS_string("????   !=   ????"));
           LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		  "MAP_INST_REF ????   !=   MAP_INST_REF ????"));
           // HACK! - invalid expression
         }
       }
       else
       {
         GS_ui::inform (UI_INFORM__ERROR, GS_string("????   !=   ????"));
         LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		"????   !=   ????"));
         // HACK! - invalid expression
       }
}

void SIM_SOR::interpret_op_relational_lt ( GS_var_si &p_rvalue, 
  GS_var_si &operand1, GS_var_si &operand2 )
{
       if ( operand1.get_var_ptr()->get_core_data_type() == INTEGER_DATATYPE &&
            operand2.get_var_ptr()->get_core_data_type() == INTEGER_DATATYPE )
       {
         p_rvalue.replace_var (new I_boolean_var ((t_boolean)
           (operand1.get_integer_var_ptr ()->get_value ()
          < operand2.get_integer_var_ptr ()->get_value ())));
         LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
           "INTEGER   <   INTEGER"));
       }
       else if ( operand1.get_var_ptr()->get_core_data_type() == INTEGER_DATATYPE &&
                 operand2.get_var_ptr()->get_core_data_type() == REAL_DATATYPE )
       {
         p_rvalue.replace_var (new I_boolean_var ((t_boolean)
           (operand1.get_integer_var_ptr ()->get_value ()
          < operand2.get_real_var_ptr()->get_value ())));
         LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
           "INTEGER   <   REAL"));
       }
       else if ( operand1.get_var_ptr()->get_core_data_type() == REAL_DATATYPE &&
                 operand2.get_var_ptr()->get_core_data_type() == INTEGER_DATATYPE )
       {
         p_rvalue.replace_var (new I_boolean_var ((t_boolean)
           (operand1.get_real_var_ptr ()->get_value ()
          < operand2.get_integer_var_ptr()->get_value ())));
         LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
           "REAL      <   INTEGER"));
       }
       else if ( operand1.get_var_ptr()->get_core_data_type() == REAL_DATATYPE &&
                 operand2.get_var_ptr()->get_core_data_type() == REAL_DATATYPE )
       {
         p_rvalue.replace_var (new I_boolean_var ((t_boolean)
           (operand1.get_real_var_ptr ()->get_value ()
          < operand2.get_real_var_ptr()->get_value ())));
         LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
           "REAL      <   REAL"));
       }
       else if ( operand1.get_var_ptr()->get_core_data_type() == STRING_DATATYPE &&
                 operand2.get_var_ptr()->get_core_data_type() == STRING_DATATYPE )
       {
         p_rvalue.replace_var (new I_boolean_var ((t_boolean)
           (operand1.get_string_var_ptr ()->get_value ().compare (
              operand2.get_string_var_ptr()->get_value ()) < 0)));
         LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
           "STRING   <   STRING"));
       }
       else if ( operand1.get_var_ptr()->get_core_data_type() == MAPPING_INST_DATATYPE )
       {
         if ( operand1.get_var_ptr()->get_user_data_type() == USER_DEFINED_USERDATATYPE &&
              operand2.get_var_ptr()->get_user_data_type() == USER_DEFINED_USERDATATYPE )
         {
           p_rvalue.replace_var (new I_boolean_var ((t_boolean)
             ((*(operand1.get_mapping_inst_var_ptr ()))
             < (*(operand2.get_mapping_inst_var_ptr ())))));
           LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
             "USER_DEFINED   <   USER_DEFINED"));
         }
         else if ( operand1.get_var_ptr()->get_user_data_type() == DATE_USERDATATYPE &&
                   operand2.get_var_ptr()->get_user_data_type() == DATE_USERDATATYPE )
         {
           p_rvalue.replace_var (new I_boolean_var ((t_boolean)
             ((*(operand1.get_date_var_ptr ()))
             < (*(operand2.get_date_var_ptr ())))));
           LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
             "DATE   <   DATE"));
         }
         else if ( operand1.get_var_ptr()->get_user_data_type() == TIMESTAMP_USERDATATYPE &&
                   operand2.get_var_ptr()->get_user_data_type() == TIMESTAMP_USERDATATYPE )
         {
           p_rvalue.replace_var (new I_boolean_var ((t_boolean)
             ((*(operand1.get_timestamp_var_ptr ()))
             < (*(operand2.get_timestamp_var_ptr ())))));
           LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
             "TIMESTAMP   <   TIMESTAMP"));
         }
         else
         {
           GS_ui::inform (UI_INFORM__ERROR, GS_string("????   <   ????"));
           LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		  "MAP_INST ????   <   MAP_INST ????"));
           // HACK! - invalid expression
         }
       }
       else
       {
         GS_ui::inform (UI_INFORM__ERROR, GS_string("????   <   ????"));
         LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		"????   <   ????"));
         // HACK! - invalid expression
       }
}

void SIM_SOR::interpret_op_relational_le ( GS_var_si &p_rvalue, 
  GS_var_si &operand1, GS_var_si &operand2 )
{
       if ( operand1.get_var_ptr()->get_core_data_type() == INTEGER_DATATYPE &&
            operand2.get_var_ptr()->get_core_data_type() == INTEGER_DATATYPE )
       {
         p_rvalue.replace_var (new I_boolean_var ((t_boolean)
           (operand1.get_integer_var_ptr ()->get_value ()
          <= operand2.get_integer_var_ptr ()->get_value ())));
         LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
           "INTEGER   <=   INTEGER"));
       }
       else if ( operand1.get_var_ptr()->get_core_data_type() == INTEGER_DATATYPE &&
                 operand2.get_var_ptr()->get_core_data_type() == REAL_DATATYPE )
       {
         p_rvalue.replace_var (new I_boolean_var ((t_boolean)
           (operand1.get_integer_var_ptr ()->get_value ()
          <= operand2.get_real_var_ptr()->get_value ())));
         LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
           "INTEGER   <=   REAL"));
       }
       else if ( operand1.get_var_ptr()->get_core_data_type() == REAL_DATATYPE &&
                 operand2.get_var_ptr()->get_core_data_type() == INTEGER_DATATYPE )
       {
         p_rvalue.replace_var (new I_boolean_var ((t_boolean)
           (operand1.get_real_var_ptr ()->get_value ()
          <= operand2.get_integer_var_ptr()->get_value ())));
         LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
           "REAL      <=   INTEGER"));
       }
       else if ( operand1.get_var_ptr()->get_core_data_type() == REAL_DATATYPE &&
                 operand2.get_var_ptr()->get_core_data_type() == REAL_DATATYPE )
       {
         p_rvalue.replace_var (new I_boolean_var ((t_boolean)
           (operand1.get_real_var_ptr ()->get_value ()
          <= operand2.get_real_var_ptr()->get_value ())));
         LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
           "REAL      <=   REAL"));
       }
       else if ( operand1.get_var_ptr()->get_core_data_type() == STRING_DATATYPE &&
                 operand2.get_var_ptr()->get_core_data_type() == STRING_DATATYPE )
       {
         p_rvalue.replace_var (new I_boolean_var ((t_boolean)
           (operand1.get_string_var_ptr ()->get_value ().compare (
              operand2.get_string_var_ptr()->get_value ()) <= 0)));
         LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
           "STRING   <=   STRING"));
       }
       else if ( operand1.get_var_ptr()->get_core_data_type() == MAPPING_INST_DATATYPE )
       {
         if ( operand1.get_var_ptr()->get_user_data_type() == USER_DEFINED_USERDATATYPE &&
              operand2.get_var_ptr()->get_user_data_type() == USER_DEFINED_USERDATATYPE )
         {
           p_rvalue.replace_var (new I_boolean_var ((t_boolean)
             ((*(operand1.get_mapping_inst_var_ptr ()))
             <= (*(operand2.get_mapping_inst_var_ptr ())))));
           LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
             "USER_DEFINED   <=   USER_DEFINED"));
         }
         else if ( operand1.get_var_ptr()->get_user_data_type() == DATE_USERDATATYPE &&
                   operand2.get_var_ptr()->get_user_data_type() == DATE_USERDATATYPE )
         {
           p_rvalue.replace_var (new I_boolean_var ((t_boolean)
             ((*(operand1.get_date_var_ptr ()))
             <= (*(operand2.get_date_var_ptr ())))));
           LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
             "DATE   <=   DATE"));
         }
         else if ( operand1.get_var_ptr()->get_user_data_type() == TIMESTAMP_USERDATATYPE &&
                   operand2.get_var_ptr()->get_user_data_type() == TIMESTAMP_USERDATATYPE )
         {
           p_rvalue.replace_var (new I_boolean_var ((t_boolean)
             ((*(operand1.get_timestamp_var_ptr ()))
             <= (*(operand2.get_timestamp_var_ptr ())))));
           LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
             "TIMESTAMP   <=   TIMESTAMP"));
         }
         else
         {
           GS_ui::inform (UI_INFORM__ERROR, GS_string("????   <=   ????"));
           LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		  "MAP_INST ????   <=   MAP_INST ????"));
           // HACK! - invalid expression
         }
       }
       else
       {
         GS_ui::inform (UI_INFORM__ERROR, GS_string("????   <=   ????"));
         LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		"????   <=   ????"));
         // HACK! - invalid expression
       }
}

void SIM_SOR::interpret_op_relational_gt ( GS_var_si &p_rvalue, 
  GS_var_si &operand1, GS_var_si &operand2 )
{
       if ( operand1.get_var_ptr()->get_core_data_type() == INTEGER_DATATYPE &&
            operand2.get_var_ptr()->get_core_data_type() == INTEGER_DATATYPE )
       {
         p_rvalue.replace_var (new I_boolean_var ((t_boolean)
           (operand1.get_integer_var_ptr ()->get_value ()
          > operand2.get_integer_var_ptr ()->get_value ())));
         LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
           "INTEGER   >   INTEGER"));
       }
       else if ( operand1.get_var_ptr()->get_core_data_type() == INTEGER_DATATYPE &&
                 operand2.get_var_ptr()->get_core_data_type() == REAL_DATATYPE )
       {
         p_rvalue.replace_var (new I_boolean_var ((t_boolean)
           (operand1.get_integer_var_ptr ()->get_value ()
          > operand2.get_real_var_ptr()->get_value ())));
         LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
           "INTEGER   >   REAL"));
       }
       else if ( operand1.get_var_ptr()->get_core_data_type() == REAL_DATATYPE &&
                 operand2.get_var_ptr()->get_core_data_type() == INTEGER_DATATYPE )
       {
         p_rvalue.replace_var (new I_boolean_var ((t_boolean)
           (operand1.get_real_var_ptr ()->get_value ()
          > operand2.get_integer_var_ptr()->get_value ())));
         LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
           "REAL      >   INTEGER"));
       }
       else if ( operand1.get_var_ptr()->get_core_data_type() == REAL_DATATYPE &&
                 operand2.get_var_ptr()->get_core_data_type() == REAL_DATATYPE )
       {
         p_rvalue.replace_var (new I_boolean_var ((t_boolean)
           (operand1.get_real_var_ptr ()->get_value ()
          > operand2.get_real_var_ptr()->get_value ())));
         LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
           "REAL      >   REAL"));
       }
       else if ( operand1.get_var_ptr()->get_core_data_type() == STRING_DATATYPE &&
                 operand2.get_var_ptr()->get_core_data_type() == STRING_DATATYPE )
       {
         p_rvalue.replace_var (new I_boolean_var ((t_boolean)
           (operand1.get_string_var_ptr ()->get_value ().compare (
              operand2.get_string_var_ptr()->get_value ()) > 0)));
         LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
           "STRING   >   STRING"));
       }
       else if ( operand1.get_var_ptr()->get_core_data_type() == MAPPING_INST_DATATYPE )
       {
         if ( operand1.get_var_ptr()->get_user_data_type() == USER_DEFINED_USERDATATYPE &&
              operand2.get_var_ptr()->get_user_data_type() == USER_DEFINED_USERDATATYPE )
         {
           p_rvalue.replace_var (new I_boolean_var ((t_boolean)
             ((*(operand1.get_mapping_inst_var_ptr ()))
             > (*(operand2.get_mapping_inst_var_ptr ())))));
           LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
             "USER_DEFINED   >   USER_DEFINED"));
         }
         else if ( operand1.get_var_ptr()->get_user_data_type() == DATE_USERDATATYPE &&
                   operand2.get_var_ptr()->get_user_data_type() == DATE_USERDATATYPE )
         {
           p_rvalue.replace_var (new I_boolean_var ((t_boolean)
             ((*(operand1.get_date_var_ptr ()))
             > (*(operand2.get_date_var_ptr ())))));
           LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
             "DATE   >   DATE"));
         }
         else if ( operand1.get_var_ptr()->get_user_data_type() == TIMESTAMP_USERDATATYPE &&
                   operand2.get_var_ptr()->get_user_data_type() == TIMESTAMP_USERDATATYPE )
         {
           p_rvalue.replace_var (new I_boolean_var ((t_boolean)
             ((*(operand1.get_timestamp_var_ptr ()))
             > (*(operand2.get_timestamp_var_ptr ())))));
           LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
             "TIMESTAMP   >   TIMESTAMP"));
         }
         else
         {
           GS_ui::inform (UI_INFORM__ERROR, GS_string("????   >   ????"));
           LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		  "MAP_INST ????   >   MAP_INST ????"));
           // HACK! - invalid expression
         }
       }
       else
       {
         GS_ui::inform (UI_INFORM__ERROR, GS_string("????   >   ????"));
         LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		"????   >   ????"));
         // HACK! - invalid expression
       }
}

void SIM_SOR::interpret_op_relational_ge ( GS_var_si &p_rvalue, 
  GS_var_si &operand1, GS_var_si &operand2 )
{
       if ( operand1.get_var_ptr()->get_core_data_type() == INTEGER_DATATYPE &&
            operand2.get_var_ptr()->get_core_data_type() == INTEGER_DATATYPE )
       {
         p_rvalue.replace_var (new I_boolean_var ((t_boolean)
           (operand1.get_integer_var_ptr ()->get_value ()
          >= operand2.get_integer_var_ptr ()->get_value ())));
         LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
           "INTEGER   >=   INTEGER"));
       }
       else if ( operand1.get_var_ptr()->get_core_data_type() == INTEGER_DATATYPE &&
                 operand2.get_var_ptr()->get_core_data_type() == REAL_DATATYPE )
       {
         p_rvalue.replace_var (new I_boolean_var ((t_boolean)
           (operand1.get_integer_var_ptr ()->get_value ()
          >= operand2.get_real_var_ptr()->get_value ())));
         LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
           "INTEGER   >=   REAL"));
       }
       else if ( operand1.get_var_ptr()->get_core_data_type() == REAL_DATATYPE &&
                 operand2.get_var_ptr()->get_core_data_type() == INTEGER_DATATYPE )
       {
         p_rvalue.replace_var (new I_boolean_var ((t_boolean)
           (operand1.get_real_var_ptr ()->get_value ()
          >= operand2.get_integer_var_ptr()->get_value ())));
         LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
           "REAL      >=   INTEGER"));
       }
       else if ( operand1.get_var_ptr()->get_core_data_type() == REAL_DATATYPE &&
                 operand2.get_var_ptr()->get_core_data_type() == REAL_DATATYPE )
       {
         p_rvalue.replace_var (new I_boolean_var ((t_boolean)
           (operand1.get_real_var_ptr ()->get_value ()
          >= operand2.get_real_var_ptr()->get_value ())));
         LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
           "REAL      >=   REAL"));
       }
       else if ( operand1.get_var_ptr()->get_core_data_type() == STRING_DATATYPE &&
                 operand2.get_var_ptr()->get_core_data_type() == STRING_DATATYPE )
       {
         p_rvalue.replace_var (new I_boolean_var ((t_boolean)
           (operand1.get_string_var_ptr ()->get_value ().compare (
              operand2.get_string_var_ptr()->get_value ()) >= 0)));
         LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
           "STRING   >=   STRING"));
       }
       else if ( operand1.get_var_ptr()->get_core_data_type() == MAPPING_INST_DATATYPE )
       {
         if ( operand1.get_var_ptr()->get_user_data_type() == USER_DEFINED_USERDATATYPE &&
              operand2.get_var_ptr()->get_user_data_type() == USER_DEFINED_USERDATATYPE )
         {
           p_rvalue.replace_var (new I_boolean_var ((t_boolean)
             ((*(operand1.get_mapping_inst_var_ptr ()))
             >= (*(operand2.get_mapping_inst_var_ptr ())))));
           LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
             "USER_DEFINED   >=   USER_DEFINED"));
         }
         else if ( operand1.get_var_ptr()->get_user_data_type() == DATE_USERDATATYPE &&
                   operand2.get_var_ptr()->get_user_data_type() == DATE_USERDATATYPE )
         {
           p_rvalue.replace_var (new I_boolean_var ((t_boolean)
             ((*(operand1.get_date_var_ptr ()))
             >= (*(operand2.get_date_var_ptr ())))));
           LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
             "DATE   >=   DATE"));
         }
         else if ( operand1.get_var_ptr()->get_user_data_type() == TIMESTAMP_USERDATATYPE &&
                   operand2.get_var_ptr()->get_user_data_type() == TIMESTAMP_USERDATATYPE )
         {
           p_rvalue.replace_var (new I_boolean_var ((t_boolean)
             ((*(operand1.get_timestamp_var_ptr ()))
             >= (*(operand2.get_timestamp_var_ptr ())))));
           LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
             "TIMESTAMP   >=   TIMESTAMP"));
         }
         else
         {
           GS_ui::inform (UI_INFORM__ERROR, GS_string("????   >=   ????"));
           LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		  "MAP_INST ????   >=   MAP_INST ????"));
           // HACK! - invalid expression
         }
       }
       else
       {
         GS_ui::inform (UI_INFORM__ERROR, GS_string("????   >=   ????"));
         LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		"????   >=   ????"));
         // HACK! - invalid expression
       }
}

void SIM_SOR::interpret_op_addition_plus ( GS_var_si &p_rvalue, 
    GS_var_si &operand1, GS_var_si &operand2 )
{
       if ( operand1.get_var_ptr()->get_core_data_type() == INTEGER_DATATYPE &&
            operand2.get_var_ptr()->get_core_data_type() == INTEGER_DATATYPE )
       {
         p_rvalue.replace_var (new I_integer_var ((t_long)
           (operand1.get_integer_var_ptr ()->get_value ()
          + operand2.get_integer_var_ptr ()->get_value ())));
         LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
           "INTEGER   +   INTEGER"));
       }
       else if ( operand1.get_var_ptr()->get_core_data_type() == INTEGER_DATATYPE &&
                 operand2.get_var_ptr()->get_core_data_type() == REAL_DATATYPE )
       {
         p_rvalue.replace_var (new I_real_var ((t_double)
           (operand1.get_integer_var_ptr ()->get_value ()
          + operand2.get_real_var_ptr()->get_value ())));
         LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
           "INTEGER   +   REAL"));
       }
       else if ( operand1.get_var_ptr()->get_core_data_type() == REAL_DATATYPE &&
                 operand2.get_var_ptr()->get_core_data_type() == INTEGER_DATATYPE )
       {
         p_rvalue.replace_var (new I_real_var ((t_double)
           (operand1.get_real_var_ptr ()->get_value ()
          + operand2.get_integer_var_ptr()->get_value ())));
         LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
           "REAL      +   INTEGER"));
       }
       else if ( operand1.get_var_ptr()->get_core_data_type() == REAL_DATATYPE &&
                 operand2.get_var_ptr()->get_core_data_type() == REAL_DATATYPE )
       {
         p_rvalue.replace_var (new I_real_var ((t_double)
           (operand1.get_real_var_ptr ()->get_value ()
          + operand2.get_real_var_ptr()->get_value ())));
         LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
           "REAL      +   REAL"));
       }
       else if ( operand1.get_var_ptr()->get_core_data_type() == STRING_DATATYPE &&
                 operand2.get_var_ptr()->get_core_data_type() == STRING_DATATYPE )
       {
		 Description tmp_str (operand1.get_string_var_ptr ()->get_value ());
		 tmp_str += operand2.get_string_var_ptr ()->get_value ();
         p_rvalue.replace_var (new I_string_var ( tmp_str ));
         LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
           "STRING   +   STRING"));
       }
       else
       {
         GS_ui::inform (UI_INFORM__ERROR, GS_string("????   +   ????"));
         LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		"????   +   ????"));
         // HACK! - invalid expression
       }
}

void SIM_SOR::interpret_op_addition_minus ( GS_var_si &p_rvalue, 
    GS_var_si &operand1, GS_var_si &operand2 )
{
       if ( operand1.get_var_ptr()->get_core_data_type() == INTEGER_DATATYPE &&
            operand2.get_var_ptr()->get_core_data_type() == INTEGER_DATATYPE )
       {
         p_rvalue.replace_var (new I_integer_var ((t_long)
           (operand1.get_integer_var_ptr ()->get_value ()
          - operand2.get_integer_var_ptr ()->get_value ())));
         LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
           "INTEGER   -   INTEGER"));
       }
       else if ( operand1.get_var_ptr()->get_core_data_type() == INTEGER_DATATYPE &&
                 operand2.get_var_ptr()->get_core_data_type() == REAL_DATATYPE )
       {
         p_rvalue.replace_var (new I_real_var ((t_double)
           (operand1.get_integer_var_ptr ()->get_value ()
          - operand2.get_real_var_ptr()->get_value ())));
         LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
           "INTEGER   -   REAL"));
       }
       else if ( operand1.get_var_ptr()->get_core_data_type() == REAL_DATATYPE &&
                 operand2.get_var_ptr()->get_core_data_type() == INTEGER_DATATYPE )
       {
         p_rvalue.replace_var (new I_real_var ((t_double)
           (operand1.get_real_var_ptr ()->get_value ()
          - operand2.get_integer_var_ptr()->get_value ())));
         LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
           "REAL      -   INTEGER"));
       }
       else if ( operand1.get_var_ptr()->get_core_data_type() == REAL_DATATYPE &&
                 operand2.get_var_ptr()->get_core_data_type() == REAL_DATATYPE )
       {
         p_rvalue.replace_var (new I_real_var ((t_double)
           (operand1.get_real_var_ptr ()->get_value ()
          - operand2.get_real_var_ptr()->get_value ())));
         LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
           "REAL      -   REAL"));
       }
       // The '-' operations between OBJ_INST_REF and OBJ_INST_REF_SET
       // are only implemented for the archetype language.  We won't
       // implement them in the simulator.  (pending approval)
       else
       {
         GS_ui::inform (UI_INFORM__ERROR, GS_string("????   -   ????"));
         LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		"????   -   ????"));
         // HACK! - invalid expression
       }
}

void SIM_SOR::interpret_op_multiplication_times ( GS_var_si &p_rvalue, 
    GS_var_si &operand1, GS_var_si &operand2 )
{
       if ( operand1.get_var_ptr()->get_core_data_type() == INTEGER_DATATYPE &&
            operand2.get_var_ptr()->get_core_data_type() == INTEGER_DATATYPE )
       {
         p_rvalue.replace_var (new I_integer_var ((t_long)
           (operand1.get_integer_var_ptr ()->get_value ()
          * operand2.get_integer_var_ptr ()->get_value ())));
         LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
           "INTEGER   *   INTEGER"));
       }
       else if ( operand1.get_var_ptr()->get_core_data_type() == INTEGER_DATATYPE &&
                 operand2.get_var_ptr()->get_core_data_type() == REAL_DATATYPE )
       {
         p_rvalue.replace_var (new I_real_var ((t_double)
           (operand1.get_integer_var_ptr ()->get_value ()
          * operand2.get_real_var_ptr()->get_value ())));
         LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
           "INTEGER   *   REAL"));
       }
       else if ( operand1.get_var_ptr()->get_core_data_type() == REAL_DATATYPE &&
                 operand2.get_var_ptr()->get_core_data_type() == INTEGER_DATATYPE )
       {
         p_rvalue.replace_var (new I_real_var ((t_double)
           (operand1.get_real_var_ptr ()->get_value ()
          * operand2.get_integer_var_ptr()->get_value ())));
         LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
           "REAL      *   INTEGER"));
       }
       else if ( operand1.get_var_ptr()->get_core_data_type() == REAL_DATATYPE &&
                 operand2.get_var_ptr()->get_core_data_type() == REAL_DATATYPE )
       {
         p_rvalue.replace_var (new I_real_var ((t_double)
           (operand1.get_real_var_ptr ()->get_value ()
          * operand2.get_real_var_ptr()->get_value ())));
         LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
           "REAL      *   REAL"));
       }
       else
       {
         GS_ui::inform (UI_INFORM__ERROR, GS_string("????   *   ????"));
         LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		"????   *   ????"));
         // HACK! - invalid expression
       }
}

void SIM_SOR::interpret_op_multiplication_div ( GS_var_si &p_rvalue, 
    GS_var_si &operand1, GS_var_si &operand2 )
{
       if ( operand1.get_var_ptr()->get_core_data_type() == INTEGER_DATATYPE &&
            operand2.get_var_ptr()->get_core_data_type() == INTEGER_DATATYPE )
       {
         if ( operand2.get_integer_var_ptr ()->get_value () != 0 )
         {
           p_rvalue.replace_var (new I_integer_var ((t_long)
             (operand1.get_integer_var_ptr ()->get_value ()
            / operand2.get_integer_var_ptr ()->get_value ())));
           LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
             "INTEGER   /   INTEGER"));
         }
         else
         {
           p_rvalue.replace_var (new I_integer_var ((t_long) 0));
           GS_ui::inform (UI_INFORM__ERROR, GS_string("INTEGER  /  INTEGER=0"));
           LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "INTEGER   /   INTEGER=0"));
           // HACK! - invalid expression
         }
       }
       else if ( operand1.get_var_ptr()->get_core_data_type() == INTEGER_DATATYPE &&
                 operand2.get_var_ptr()->get_core_data_type() == REAL_DATATYPE )
       {
         if ( operand2.get_real_var_ptr ()->get_value () != 0.0 )
         {
           p_rvalue.replace_var (new I_real_var ((t_double)
             (operand1.get_integer_var_ptr ()->get_value ()
            / operand2.get_real_var_ptr()->get_value ())));
           LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
             "INTEGER   /   REAL"));
         }
         else
         {
           p_rvalue.replace_var (new I_real_var ((t_double) 0.0));
           GS_ui::inform (UI_INFORM__ERROR, GS_string("INTEGER  /  REAL=0.0"));
           LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "INTEGER   /   REAL=0.0"));
           // HACK! - invalid expression
         }
       }
       else if ( operand1.get_var_ptr()->get_core_data_type() == REAL_DATATYPE &&
                 operand2.get_var_ptr()->get_core_data_type() == INTEGER_DATATYPE )
       {
         if ( operand2.get_integer_var_ptr ()->get_value () != 0 )
         {
           p_rvalue.replace_var (new I_real_var ((t_double)
             (operand1.get_real_var_ptr ()->get_value ()
            / operand2.get_integer_var_ptr()->get_value ())));
           LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
             "REAL      /   INTEGER"));
         }
         else
         {
           p_rvalue.replace_var (new I_real_var ((t_double) 0.0));
           GS_ui::inform (UI_INFORM__ERROR, GS_string("REAL  /  INTEGER=0"));
           LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "REAL   /   INTEGER=0"));
           // HACK! - invalid expression
         }
       }
       else if ( operand1.get_var_ptr()->get_core_data_type() == REAL_DATATYPE &&
                 operand2.get_var_ptr()->get_core_data_type() == REAL_DATATYPE )
       {
         if ( operand2.get_real_var_ptr ()->get_value () != 0.0 )
         {
           p_rvalue.replace_var (new I_real_var ((t_double)
             (operand1.get_real_var_ptr ()->get_value ()
            / operand2.get_real_var_ptr()->get_value ())));
           LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
             "REAL      /   REAL"));
         }
         else
         {
           p_rvalue.replace_var (new I_real_var ((t_double) 0.0));
           GS_ui::inform (UI_INFORM__ERROR, GS_string("REAL  /  REAL=0.0"));
           LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "REAL   /   REAL=0.0"));
           // HACK! - invalid expression
         }
       }
       else
       {
         GS_ui::inform (UI_INFORM__ERROR, GS_string("????   /   ????"));
         LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		"????   /   ????"));
         // HACK! - invalid expression
       }
}

void SIM_SOR::interpret_op_multiplication_mod ( GS_var_si &p_rvalue, 
    GS_var_si &operand1, GS_var_si &operand2 )
{
       if ( operand1.get_var_ptr()->get_core_data_type() == INTEGER_DATATYPE &&
            operand2.get_var_ptr()->get_core_data_type() == INTEGER_DATATYPE )
       {
         if ( operand2.get_integer_var_ptr ()->get_value () != 0 )
         {
           p_rvalue.replace_var (new I_integer_var ((t_long)
             (operand1.get_integer_var_ptr ()->get_value ()
            % operand2.get_integer_var_ptr ()->get_value ())));
           LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
             "INTEGER   %   INTEGER"));
         }
         else
         {
           p_rvalue.replace_var (new I_integer_var ((t_long) 0));
           GS_ui::inform (UI_INFORM__ERROR, GS_string("INTEGER  %  INTEGER=0"));
           LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "INTEGER   %   INTEGER=0"));
           // HACK! - invalid expression
         }
       }
       else
       {
         GS_ui::inform (UI_INFORM__ERROR, GS_string("????   %   ????"));
         LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		"????   %   ????"));
         // HACK! - invalid expression
       }
}

void SIM_SOR::interpret_op_cardinality ( GS_var_si &p_rvalue, 
    const vchar *local_var )
{
        I_var* var_ptr = GS_stack::find_var_ptr (local_var);
        if (! var_ptr)
        {
	     Description err_msg ("Unable to find '");
		 err_msg += local_var;
		 err_msg += "' on stack.";
          GS_ui::inform (UI_INFORM__ERROR, err_msg);
          LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #1:  SIM_SOR::term (VOID_DATATYPE)."));
        }
        else
        {
	  if (var_ptr->get_object_inst_ref_var_ptr ())
	  {
			GS_UI_INFORM_START (UI_INFORM__COMP)
            Description err_msg ("rvalue '");
			err_msg += local_var;
			err_msg += "' (";
            err_msg += var_ptr->get_object_inst_ref_var_ptr()->get_data_type_str();
			err_msg += ") = ";
			err_msg += var_ptr->get_object_inst_ref_var_ptr()->get_value_str();
            GS_UI_INFORM_END (UI_INFORM__COMP, err_msg);

	    p_rvalue.replace_var (new I_integer_var ((t_long) (
               var_ptr->get_object_inst_ref_var_ptr ()->
                 cardinality ())));
            LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	      "End #2:  SIM_SOR::term (OBJECT_INST_REF_DATATYPE)."));
          }
	  else if (var_ptr->get_object_inst_ref_set_var_ptr ())
          {
			GS_UI_INFORM_START (UI_INFORM__COMP)
            Description err_msg ("rvalue '");
			err_msg += local_var;
			err_msg += "' (";
            err_msg += var_ptr->get_object_inst_ref_set_var_ptr()->get_data_type_str();
			err_msg += ") = ";
			err_msg += var_ptr->get_object_inst_ref_set_var_ptr()->get_value_str();
            GS_UI_INFORM_END (UI_INFORM__COMP, err_msg);

            p_rvalue.replace_var (new I_integer_var ((t_long) (
               var_ptr->get_object_inst_ref_set_var_ptr ()->
		    cardinality ())));
            LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	      "End #3:  SIM_SOR::term (OBJECT_INST_REF_SET_DATATYPE)."));
          }
          else
          {
            GS_ui::inform (UI_INFORM__ERROR,
	      GS_string("CARDINALITY operator expects INST_REF or INST_REF_SET rvalue."));
            LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	      "End #4:  SIM_SOR::term():  CARDINALITY operator expects INST_REF or INST_REF_SET rvalue."));
            // HACK - invalid expression
          }
        }
}

void SIM_SOR::interpret_op_empty ( GS_var_si &p_rvalue, 
    const vchar *local_var )
{
        I_var* var_ptr = GS_stack::find_var_ptr (local_var);
        if (! var_ptr)
        {
	     Description err_msg ("Unable to find '");
		 err_msg += local_var;
		 err_msg += "' on stack.";
          GS_ui::inform (UI_INFORM__ERROR, err_msg);
          LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #5:  SIM_SOR::term (VOID_DATATYPE)."));
        }
        else
        {
	  if (var_ptr->get_object_inst_ref_var_ptr ())
	  {
			GS_UI_INFORM_START (UI_INFORM__COMP)
            Description err_msg ("rvalue '");
			err_msg += local_var;
			err_msg += "' (";
            err_msg += var_ptr->get_object_inst_ref_var_ptr()->get_data_type_str();
			err_msg += ") = ";
			err_msg += var_ptr->get_object_inst_ref_var_ptr()->get_value_str();
            GS_UI_INFORM_END (UI_INFORM__COMP, err_msg);

	    if (var_ptr->get_object_inst_ref_var_ptr ()->is_empty())
	    {
              p_rvalue.replace_var (new I_boolean_var ((t_boolean) TRUE));
            }
            else
            {
              p_rvalue.replace_var (new I_boolean_var ((t_boolean) FALSE));
            }
            LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
              "End #6:  SIM_SOR::term (OBJECT_INST_REF_DATATYPE)."));
          }
	  else if (var_ptr->get_object_inst_ref_set_var_ptr ())
          {
			GS_UI_INFORM_START (UI_INFORM__COMP)
            Description err_msg ("rvalue '");
			err_msg += local_var;
			err_msg += "' (";
            err_msg += var_ptr->get_object_inst_ref_set_var_ptr()->get_data_type_str();
			err_msg += ") = ";
			err_msg += var_ptr->get_object_inst_ref_set_var_ptr()->get_value_str();
            GS_UI_INFORM_END (UI_INFORM__COMP, err_msg);

            if (var_ptr->get_object_inst_ref_set_var_ptr ()-> is_empty())
	    {
              p_rvalue.replace_var (new I_boolean_var ((t_boolean) TRUE));
            }
            else
            {
              p_rvalue.replace_var (new I_boolean_var ((t_boolean) FALSE));
            }
            LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	      "End #7:  SIM_SOR::term (OBJECT_INST_REF_SET_DATATYPE)."));
          }
          else
          {
            GS_ui::inform (UI_INFORM__ERROR,
	      GS_string("EMPTY operator expects INST_REF or INST_REF_SET rvalue."));
            LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	      "End #8:  SIM_SOR::term():  EMPTY operator expects INST_REF or INST_REF_SET rvalue."));
            // HACK - invalid expression
          }
        }
}

void SIM_SOR::interpret_op_not_empty ( GS_var_si &p_rvalue, 
    const vchar *local_var )
{
        I_var* var_ptr = GS_stack::find_var_ptr (local_var);
        if (! var_ptr)
        {
	     Description err_msg ("Unable to find '");
		 err_msg += local_var;
		 err_msg += "' on stack.";
          GS_ui::inform (UI_INFORM__ERROR, err_msg);
          LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #9:  SIM_SOR::term (VOID_DATATYPE)."));
        }
        else
        {
	  if (var_ptr->get_object_inst_ref_var_ptr ())
	  {
			GS_UI_INFORM_START (UI_INFORM__COMP)
            Description err_msg ("rvalue '");
			err_msg += local_var;
			err_msg += "' (";
            err_msg += var_ptr->get_object_inst_ref_var_ptr()->get_data_type_str();
			err_msg += ") = ";
			err_msg += var_ptr->get_object_inst_ref_var_ptr()->get_value_str();
            GS_UI_INFORM_END (UI_INFORM__COMP, err_msg);

	    if (var_ptr->get_object_inst_ref_var_ptr ()->is_empty())
	    {
              p_rvalue.replace_var (new I_boolean_var ((t_boolean) FALSE));
            }
            else
            {
              p_rvalue.replace_var (new I_boolean_var ((t_boolean) TRUE));
            }
            LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
              "End #10:  SIM_SOR::term (OBJECT_INST_REF_DATATYPE)."));
          }
	  else if (var_ptr->get_object_inst_ref_set_var_ptr ())
          {
			GS_UI_INFORM_START (UI_INFORM__COMP)
            Description err_msg ("rvalue '");
			err_msg += local_var;
			err_msg += "' (";
            err_msg += var_ptr->get_object_inst_ref_set_var_ptr()->get_data_type_str();
			err_msg += ") = ";
			err_msg += var_ptr->get_object_inst_ref_set_var_ptr()->get_value_str();
            GS_UI_INFORM_END (UI_INFORM__COMP, err_msg);

            if (var_ptr->get_object_inst_ref_set_var_ptr ()-> is_empty())
	    {
              p_rvalue.replace_var (new I_boolean_var ((t_boolean) FALSE));
            }
            else
            {
              p_rvalue.replace_var (new I_boolean_var ((t_boolean) TRUE));
            }
            LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	      "End #11:  SIM_SOR::term (OBJECT_INST_REF_SET_DATATYPE)."));
          }
          else
          {
            GS_ui::inform (UI_INFORM__ERROR,
	      GS_string("NOT_EMPTY operator expects INST_REF or INST_REF_SET rvalue."));
            LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	      "End #8:  SIM_SOR::term():  NOT_EMPTY operator expects INST_REF or INST_REF_SET rvalue."));
            // HACK - invalid expression
          }
        }
}

void SIM_SOR::interpret_attribute_access ( bool p_is_rval, GS_var_si &p_rvalue, 
   const vchar *irv, const vchar *p_attr_name, vchar *& lvalue_str )
{
      if ( p_is_rval )
      {
        I_object_inst_ref_var* object_inst_ref_var_ptr
	    = GS_stack::find_object_inst_ref_var_ptr (irv);
        if (object_inst_ref_var_ptr)
        {
          // if I try to put these two conditions in an &&, the compiler barfs 
          // with the error message:
          //  sorry, not implemented: temporary of class GS_string  with destructor needed in && expression
          if ( object_inst_ref_var_ptr->is_valid_attr_name (p_attr_name) )
          {
            if ( object_inst_ref_var_ptr->get_attr_var_ptr (p_attr_name) ) 
            {
                // Is this a derived attribute?
                I_Attribute_Instance* ainst_ptr = object_inst_ref_var_ptr->get_attr_inst_ptr(p_attr_name);
	            if (!ainst_ptr)
	            {
		            GS_UI_INFORM_START (UI_INFORM__ERROR)
	                Description err_msg ("Error: inst_ref<Object> variable '");
	                err_msg += irv;
		            err_msg += "' is missing attribute '";
                    err_msg += p_attr_name;
                    err_msg += "'.";
	                GS_UI_INFORM_END (UI_INFORM__ERROR, err_msg);
	               LOG_ERROR ((L_log_string,
	                "End #2:  SIM_SOR::interpret_attribute_access ():  Variable missing attribute instance."));
                   return;
                }

                I_Attribute* sim_attr_ptr = ainst_ptr->get_Attribute_R2002_ptr ();
                if (sim_attr_ptr == 0) 
                {
 	               GS_ui::inform (UI_INFORM__ERROR, GS_string("Internal Error: Assigner instance has no associated attribute."));
	               LOG_ERROR ((L_log_string,
	                "End #3:  SIM_SOR::interpret_attribute_access ():  Assigner instance has no associated attribute."));
                    return;
                }

                if ( !sim_attr_ptr->get_is_referential_attr() )
                {
                    Attribute*  ooa_attr_ptr
                        = GS_find::find_attribute_by_id (sim_attr_ptr->get_attribute_ID ());
                    Base_attribute* base_attr_ptr = ooa_attr_ptr->get_base_attribute_ptr();
                    if ( base_attr_ptr->get_derived_base_attribute_ptr() &&
                         base_attr_ptr->get_parse_on_apply() )
                    {
                        t_boolean ok_to_interpret = TRUE;
                        if ( base_attr_ptr->get_last_parse_result() == D_execution_spec::AL_NOT_PARSED )
                        {
                            ok_to_interpret = FALSE;
		                    GS_UI_INFORM_START (UI_INFORM__ERROR)
	                        Description err_msg ("Action Specification for Derived Attribute '");
	                        err_msg += object_inst_ref_var_ptr->get_key_letters_str();
		                    err_msg += ".";
		                    err_msg += p_attr_name;
	                        err_msg += "' has not been parsed.  Default value returned";
	                        GS_UI_INFORM_END (UI_INFORM__ERROR, err_msg);
                        }
                        else if ( base_attr_ptr->get_last_parse_result() != D_execution_spec::AL_PARSE_SUCCESSFUL )
                        {
                            ok_to_interpret = FALSE;
		                    GS_UI_INFORM_START (UI_INFORM__ERROR)
	                        Description err_msg ("Action Specification for Derived Attribute '");
	                        err_msg += object_inst_ref_var_ptr->get_key_letters_str();
		                    err_msg += ".";
		                    err_msg += p_attr_name;
	                        err_msg += "' has parse errors.  Default value returned";
	                        GS_UI_INFORM_END (UI_INFORM__ERROR, err_msg);
                        }
                        else if ( base_attr_ptr->relocatable_desc_resolved() == FALSE )
                        {
                            ok_to_interpret = FALSE;
		                    GS_UI_INFORM_START (UI_INFORM__ERROR)
	                        Description err_msg ("Action Specification for Derived Attribute '");
	                        err_msg += object_inst_ref_var_ptr->get_key_letters_str();
		                    err_msg += ".";
		                    err_msg += p_attr_name;
	                        err_msg += "' has unresolved symbols.  Default value returned";
	                        GS_UI_INFORM_END (UI_INFORM__ERROR, err_msg);
                        }

                        if (ok_to_interpret)
                        {
		                    GS_UI_INFORM_START (UI_INFORM__STMT)
	                        Description err_msg ("Derived Attribute '");
	                        err_msg += object_inst_ref_var_ptr->get_key_letters_str();
		                    err_msg += ".";
		                    err_msg += p_attr_name;
		                    err_msg += "' Invocation Begin.";
	                    GS_UI_INFORM_END (UI_INFORM__STMT, err_msg);
	                    GS_stack::mapping_point_begin ();

							// use the PCCTS parser
                            // i2718.5 begin
                            D_execution_spec::t_desc_state save_state = 
                                base_attr_ptr->get_desc_state ();
                            base_attr_ptr->set_desc_state (D_execution_spec::DESC_USE_RELOCATABLE);
                            // i2718.5 end
                            parser_interpret_attribute_logic (
                                object_inst_ref_var_ptr->get_oinst_ptr(), base_attr_ptr, 
			                    base_attr_ptr->action_specification (), p_rvalue );
                            base_attr_ptr->set_desc_state (save_state);   // i2718.5 added

	                    GS_stack::mapping_point_end ();

		                    GS_UI_INFORM_START (UI_INFORM__STMT)
	                        Description err_msg2 ("Derived Attribute '");
	                        err_msg2 += object_inst_ref_var_ptr->get_key_letters_str();
		                    err_msg2 += ".";
		                    err_msg2 += p_attr_name;
		                    err_msg2 += "' Invocation End.";
	                        GS_UI_INFORM_END (UI_INFORM__STMT, err_msg2);
                        }
                    }
                }

                p_rvalue.replace_var
                    (object_inst_ref_var_ptr->get_attr_var_ptr (p_attr_name));

                GS_UI_INFORM_START (UI_INFORM__COMP)
		        Description err_msg ("rvalue '");
				err_msg += irv;
				err_msg += ".";
				err_msg += p_attr_name;
				err_msg += "' (";
				err_msg += p_rvalue.get_var_ptr ()->get_data_type_str();
				err_msg += ") = ";
				err_msg += p_rvalue.get_var_ptr ()->get_value_str();
				GS_UI_INFORM_END (UI_INFORM__COMP, err_msg);
              LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
                 "End #1:  SIM_SOR::interpret_attribute_access ()."));
            }
            else
            {
              GS_ui::inform (UI_INFORM__ERROR,
		      GS_string("This can be caused by a failed select or accessing attributes of a deleted instance."));  // i2744.6.2 change
              LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
                 "End #2:  SIM_SOR::interpret_attribute_access (VOID_DATATYPE):  get_attr_var_ptr returned 0."));
            }
          }
          else
          {
            GS_ui::inform (UI_INFORM__ERROR,
		    GS_string("Attribute Not a valid attribute of object."));
            LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
               "End #3:  SIM_SOR::interpret_attribute_access (VOID_DATATYPE):  Attribute not a valid attribute of fragment."));
          }
        }
      }

      // The 2 is for the '.' and ending '\0'.
      // The calling routine must delete the string.
      int tlen = vcharLength(irv) + vcharLength(p_attr_name) + 2; 
      lvalue_str = new vchar [ tlen ];
      vcharCopy ( irv, lvalue_str );
      vcharAppendFromLiteral( lvalue_str, "." );
      vcharAppend( lvalue_str, p_attr_name );
}

void SIM_SOR::interpret_enumerator_literal ( GS_var_si &p_rvalue, 
   const vchar *p_enum_dt, const vchar *p_enumerator )
{
    mc_dbms_Bag <D_enum_data_type*>* edt_coll_ptr
	= GS_find::find_enum_data_type_by_name (p_enum_dt);
    if (! edt_coll_ptr)
    {
	GS_ui::inform (UI_INFORM__ERROR, GS_string("Internal Error."));
	LOG_ERROR ((L_log_string,
	    "End #6:  SIM_SOR::interpret_enumerator_literal ():  Creation of Enum Data Type collection in find returned 0."));
	return ;
    }

    if (edt_coll_ptr->cardinality () > 1)
    {
	    Description err_msg ("More than enumeration data type with name '");
		err_msg += p_enum_dt;
	    err_msg += "' exists in OOA DB";
	GS_ui::inform (UI_INFORM__WARNING, err_msg);
	delete edt_coll_ptr;
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #8:  SIM_SOR::interpret_enumerator_literal ()."));
	return ;
    }


    D_enum_data_type* edt_ptr = edt_coll_ptr->pick ();
    delete edt_coll_ptr;
    if (! edt_ptr)
    {
	GS_ui::inform (UI_INFORM__ERROR, GS_string("Internal Error."));
	LOG_ERROR ((L_log_string,
	    "End #9:  SIM_SOR::interpret_enumerator_literal ():  Object pointer in collection of 1 element is 0."));
	return ;
    }

	Description enum_value( p_enum_dt );
	enum_value += "::";
	enum_value += p_enumerator;

	p_rvalue.replace_var(new I_enumerator_var( enum_value ));


}

void SIM_SOR::interpret_param_data_access ( bool p_is_rval, GS_var_si &p_rvalue, 
   const vchar *p_param_name, vchar *& p_lvalue_str )
{
  if ( p_is_rval )
  {
     // pretend it's a local variable called param.<data name>
     // the parser automatically converts param to all lowercase
     vchar *var_name_str;
     int tlen = strlen("param.") + vcharLength(p_param_name) + 1; 
     var_name_str = new vchar [ tlen ];
     vcharCopyFromLiteral( "param.", var_name_str );
     vcharAppend( var_name_str, p_param_name );
     I_var* var_ptr = GS_stack::find_var_ptr (var_name_str);
     if (! var_ptr)
     {
	     Description err_msg ("Unable to find '");
		 err_msg += var_name_str;
		 err_msg += "' on stack.";
          GS_ui::inform (UI_INFORM__ERROR, err_msg);
       LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
         "End #1:  SIM_SOR::interpret_param_data_access (VOID_DATATYPE)."));
     }
     else
     {
       p_rvalue.replace_var (var_ptr);
		GS_UI_INFORM_START (UI_INFORM__COMP)
       Description err_msg ("rvalue '");
		err_msg += var_name_str;
		err_msg += "' (";
        err_msg += p_rvalue.get_var_ptr ()->get_data_type_str();
		err_msg += ") = ";
		err_msg += p_rvalue.get_var_ptr ()->get_value_str();
        GS_UI_INFORM_END (UI_INFORM__COMP, err_msg);
       LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
           "End #2:  SIM_SOR::interpret_param_data_access ()."));
     }
     delete [] var_name_str;
  }

  // The 7 is for the 'param.' and ending '\0'.
  // The calling routine must delete the string.
  int tlen = vcharLength(p_param_name) + 7; 
  p_lvalue_str = new vchar [ tlen ];
  vcharCopyFromLiteral( "param.", p_lvalue_str );
  vcharAppend( p_lvalue_str, p_param_name );
}


void SIM_SOR::interpret_event_data_access ( GS_var_si &p_rvalue, 
   const vchar *p_supp_data )
{
  // pretend it's a local variable called RCVD_EVT.<data name>
  // the sim engine automatically uses all uppercase
  vchar *var_name_str;
  int tlen = strlen("RCVD_EVT.") + vcharLength(p_supp_data) + 1; 
  var_name_str = new vchar [ tlen ];
  vcharCopyFromLiteral( "RCVD_EVT.", var_name_str );
  vcharAppend( var_name_str, p_supp_data );
  I_var* var_ptr = GS_stack::find_var_ptr (var_name_str);
  if (! var_ptr)
  {
	     Description err_msg ("Unable to find '");
		 err_msg += var_name_str;
		 err_msg += "' on stack.";
          GS_ui::inform (UI_INFORM__ERROR, err_msg);
    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
      "End #1:  SIM_SOR::interpret_event_data_access (VOID_DATATYPE)."));
  }
  else
  {
    p_rvalue.replace_var (var_ptr);
		GS_UI_INFORM_START (UI_INFORM__COMP)
       Description err_msg ("rvalue '");
		err_msg += var_name_str;
		err_msg += "' (";
        err_msg += p_rvalue.get_var_ptr ()->get_data_type_str();
		err_msg += ") = ";
		err_msg += p_rvalue.get_var_ptr ()->get_value_str();
        GS_UI_INFORM_END (UI_INFORM__COMP, err_msg);
    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
        "End #2:  SIM_SOR::interpret_event_data_access ()."));
  }
  delete [] var_name_str;
}

void SIM_SOR::interpret_bridge_expr( const vchar *p_eekl, const vchar *p_func, 
           int num_params, Description p_param_name[], GS_var_si p_param_value[],
           bool p_param_readonly[], GS_var_si &p_rvalue )
{
    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_BEGIN, (L_log_string,
	"Begin  SIM_SOR::interpret_bridge_expr ()." ));

    t_boolean simulator_supported = FALSE;

    Description ee_kl_str (p_eekl);
    ee_kl_str.convert_to_upper_case ();

    Description func_name_str (p_func);
    func_name_str.convert_to_upper_case ();

    if (ee_kl_str == "TIM")
    {
	if (func_name_str == "CURRENT_DATE")
	{
		GS_UI_INFORM_START (UI_INFORM__COMP)
		Description err_msg ("Using Built-in Implementation for:  \"");
		err_msg += p_eekl;
		err_msg += "::";
		err_msg += p_func;
		err_msg += ";\"";
	    GS_UI_INFORM_END (UI_INFORM__COMP, err_msg);
	    interpret__time__current_date (p_rvalue);
	    simulator_supported = TRUE;
	}
	else if (func_name_str == "CREATE_DATE")
	{
		GS_UI_INFORM_START (UI_INFORM__COMP)
		Description err_msg ("Using Built-in Implementation for:  \"");
		err_msg += p_eekl;
		err_msg += "::";
		err_msg += p_func;
		err_msg += ";\"";
	    GS_UI_INFORM_END (UI_INFORM__COMP, err_msg);
	    interpret__time__create_date (num_params, p_param_name, p_param_value, p_rvalue);
	    simulator_supported = TRUE;
	}
	else if (func_name_str == "GET_SECOND")
	{
		GS_UI_INFORM_START (UI_INFORM__COMP)
		Description err_msg ("Using Built-in Implementation for:  \"");
		err_msg += p_eekl;
		err_msg += "::";
		err_msg += p_func;
		err_msg += ";\"";
	    GS_UI_INFORM_END (UI_INFORM__COMP, err_msg);
	    interpret__time__get_second (num_params, p_param_name, p_param_value, p_rvalue);
	    simulator_supported = TRUE;
	}
	else if (func_name_str == "GET_MINUTE")
	{
		GS_UI_INFORM_START (UI_INFORM__COMP)
		Description err_msg ("Using Built-in Implementation for:  \"");
		err_msg += p_eekl;
		err_msg += "::";
		err_msg += p_func;
		err_msg += ";\"";
	    GS_UI_INFORM_END (UI_INFORM__COMP, err_msg);
	    interpret__time__get_minute (num_params, p_param_name, p_param_value, p_rvalue);
	    simulator_supported = TRUE;
	}
	else if (func_name_str == "GET_HOUR")
	{
		GS_UI_INFORM_START (UI_INFORM__COMP)
		Description err_msg ("Using Built-in Implementation for:  \"");
		err_msg += p_eekl;
		err_msg += "::";
		err_msg += p_func;
		err_msg += ";\"";
	    GS_UI_INFORM_END (UI_INFORM__COMP, err_msg);
	    interpret__time__get_hour (num_params, p_param_name, p_param_value, p_rvalue);
	    simulator_supported = TRUE;
	}
	else if (func_name_str == "GET_DAY")
	{
		GS_UI_INFORM_START (UI_INFORM__COMP)
		Description err_msg ("Using Built-in Implementation for:  \"");
		err_msg += p_eekl;
		err_msg += "::";
		err_msg += p_func;
		err_msg += ";\"";
	    GS_UI_INFORM_END (UI_INFORM__COMP, err_msg);
	    interpret__time__get_day (num_params, p_param_name, p_param_value, p_rvalue);
	    simulator_supported = TRUE;
	}
	else if (func_name_str == "GET_MONTH")
	{
		GS_UI_INFORM_START (UI_INFORM__COMP)
		Description err_msg ("Using Built-in Implementation for:  \"");
		err_msg += p_eekl;
		err_msg += "::";
		err_msg += p_func;
		err_msg += ";\"";
	    GS_UI_INFORM_END (UI_INFORM__COMP, err_msg);
	    interpret__time__get_month (num_params, p_param_name, p_param_value, p_rvalue);
	    simulator_supported = TRUE;
	}
	else if (func_name_str == "GET_YEAR")
	{
		GS_UI_INFORM_START (UI_INFORM__COMP)
		Description err_msg ("Using Built-in Implementation for:  \"");
		err_msg += p_eekl;
		err_msg += "::";
		err_msg += p_func;
		err_msg += ";\"";
	    GS_UI_INFORM_END (UI_INFORM__COMP, err_msg);
	    interpret__time__get_year (num_params, p_param_name, p_param_value, p_rvalue);
	    simulator_supported = TRUE;
	}

	else if (func_name_str == "CURRENT_CLOCK")
	{
		GS_UI_INFORM_START (UI_INFORM__COMP)
		Description err_msg ("Using Built-in Implementation for:  \"");
		err_msg += p_eekl;
		err_msg += "::";
		err_msg += p_func;
		err_msg += ";\"";
	    GS_UI_INFORM_END (UI_INFORM__COMP, err_msg);
	    interpret__time__current_clock (p_rvalue);
	    simulator_supported = TRUE;
	}

	else if (func_name_str == "TIMER_START")
	{
		GS_UI_INFORM_START (UI_INFORM__COMP)
		Description err_msg ("Using Built-in Implementation for:  \"");
		err_msg += p_eekl;
		err_msg += "::";
		err_msg += p_func;
		err_msg += ";\"";
	    GS_UI_INFORM_END (UI_INFORM__COMP, err_msg);
	    interpret__time__timer_start (num_params, p_param_name, p_param_value, p_rvalue);
	    simulator_supported = TRUE;
	}
	else if (func_name_str == "TIMER_START_RECURRING")
	{
		GS_UI_INFORM_START (UI_INFORM__COMP)
		Description err_msg ("Using Built-in Implementation for:  \"");
		err_msg += p_eekl;
		err_msg += "::";
		err_msg += p_func;
		err_msg += ";\"";
	    GS_UI_INFORM_END (UI_INFORM__COMP, err_msg);
	    interpret__time__timer_start_recurring (num_params, p_param_name, p_param_value, p_rvalue);
	    simulator_supported = TRUE;
	}
	else if (func_name_str == "TIMER_REMAINING_TIME")
	{
		GS_UI_INFORM_START (UI_INFORM__COMP)
		Description err_msg ("Using Built-in Implementation for:  \"");
		err_msg += p_eekl;
		err_msg += "::";
		err_msg += p_func;
		err_msg += ";\"";
	    GS_UI_INFORM_END (UI_INFORM__COMP, err_msg);
	    interpret__time__timer_remaining_time (num_params, p_param_name, p_param_value, p_rvalue);
	    simulator_supported = TRUE;
	}
	else if (func_name_str == "TIMER_RESET_TIME")
	{
		GS_UI_INFORM_START (UI_INFORM__COMP)
		Description err_msg ("Using Built-in Implementation for:  \"");
		err_msg += p_eekl;
		err_msg += "::";
		err_msg += p_func;
		err_msg += ";\"";
	    GS_UI_INFORM_END (UI_INFORM__COMP, err_msg);
	    interpret__time__timer_reset_time (num_params, p_param_name, p_param_value, p_rvalue);
	    simulator_supported = TRUE;
	}
	else if (func_name_str == "TIMER_ADD_TIME")
	{
		GS_UI_INFORM_START (UI_INFORM__COMP)
		Description err_msg ("Using Built-in Implementation for:  \"");
		err_msg += p_eekl;
		err_msg += "::";
		err_msg += p_func;
		err_msg += ";\"";
	    GS_UI_INFORM_END (UI_INFORM__COMP, err_msg);
	    interpret__time__timer_add_time (num_params, p_param_name, p_param_value, p_rvalue);
	    simulator_supported = TRUE;
	}
	else if (func_name_str == "TIMER_CANCEL")
	{
		GS_UI_INFORM_START (UI_INFORM__COMP)
		Description err_msg ("Using Built-in Implementation for:  \"");
		err_msg += p_eekl;
		err_msg += "::";
		err_msg += p_func;
		err_msg += ";\"";
	    GS_UI_INFORM_END (UI_INFORM__COMP, err_msg);
	    interpret__time__timer_cancel (num_params, p_param_name, p_param_value, p_rvalue);
	    simulator_supported = TRUE;
	}
    }
    else if (ee_kl_str == "OS")
    {
	if (func_name_str == "PUT_ENV_VAR")
	{
		GS_UI_INFORM_START (UI_INFORM__COMP)
		Description err_msg ("Using Built-in Implementation for:  \"");
		err_msg += p_eekl;
		err_msg += "::";
		err_msg += p_func;
		err_msg += ";\"";
	    GS_UI_INFORM_END (UI_INFORM__COMP, err_msg);
	    interpret__mc_dbms__put_env_var (num_params, p_param_name, p_param_value);
	    simulator_supported = TRUE;
	}
	else if (func_name_str == "GET_ENV_VAR")
	{
		GS_UI_INFORM_START (UI_INFORM__COMP)
		Description err_msg ("Using Built-in Implementation for:  \"");
		err_msg += p_eekl;
		err_msg += "::";
		err_msg += p_func;
		err_msg += ";\"";
	    GS_UI_INFORM_END (UI_INFORM__COMP, err_msg);
	    interpret__mc_dbms__get_env_var (num_params, p_param_name, p_param_value, p_rvalue);
	    simulator_supported = TRUE;
	}
	else if (func_name_str == "SHELL_COMMAND")
	{
		GS_UI_INFORM_START (UI_INFORM__COMP)
		Description err_msg ("Using Built-in Implementation for:  \"");
		err_msg += p_eekl;
		err_msg += "::";
		err_msg += p_func;
		err_msg += ";\"";
	    GS_UI_INFORM_END (UI_INFORM__COMP, err_msg);
	    interpret__mc_dbms__shell_command (num_params, p_param_name, p_param_value, p_rvalue);
	    simulator_supported = TRUE;
	}
	else if (func_name_str == "FILE_READ")
	{
		GS_UI_INFORM_START (UI_INFORM__COMP)
		Description err_msg ("Using Built-in Implementation for:  \"");
		err_msg += p_eekl;
		err_msg += "::";
		err_msg += p_func;
		err_msg += ";\"";
	    GS_UI_INFORM_END (UI_INFORM__COMP, err_msg);
	    interpret__mc_dbms__file_read (num_params, p_param_name, p_param_value, p_rvalue);
	    simulator_supported = TRUE;
	}
	else if (func_name_str == "FILE_WRITE")
	{
		GS_UI_INFORM_START (UI_INFORM__COMP)
		Description err_msg ("Using Built-in Implementation for:  \"");
		err_msg += p_eekl;
		err_msg += "::";
		err_msg += p_func;
		err_msg += ";\"";
	    GS_UI_INFORM_END (UI_INFORM__COMP, err_msg);
	    interpret__mc_dbms__file_write (num_params, p_param_name, p_param_value, p_rvalue);
	    simulator_supported = TRUE;
	}
	else if (func_name_str == "STRING_TO_INTEGER")
	{
		GS_UI_INFORM_START (UI_INFORM__COMP)
		Description err_msg ("Using Built-in Implementation for:  \"");
		err_msg += p_eekl;
		err_msg += "::";
		err_msg += p_func;
		err_msg += ";\"";
	    GS_UI_INFORM_END (UI_INFORM__COMP, err_msg);
	    interpret__mc_dbms__string_to_integer (num_params, p_param_name, p_param_value, p_rvalue);
	    simulator_supported = TRUE;
	}
	else if (func_name_str == "STRING_TO_REAL")
	{
		GS_UI_INFORM_START (UI_INFORM__COMP)
		Description err_msg ("Using Built-in Implementation for:  \"");
		err_msg += p_eekl;
		err_msg += "::";
		err_msg += p_func;
		err_msg += ";\"";
	    GS_UI_INFORM_END (UI_INFORM__COMP, err_msg);
	    interpret__mc_dbms__string_to_real (num_params, p_param_name, p_param_value, p_rvalue);
	    simulator_supported = TRUE;
	}
	else if (func_name_str == "INTEGER_TO_STRING")
	{
		GS_UI_INFORM_START (UI_INFORM__COMP)
		Description err_msg ("Using Built-in Implementation for:  \"");
		err_msg += p_eekl;
		err_msg += "::";
		err_msg += p_func;
		err_msg += ";\"";
	    GS_UI_INFORM_END (UI_INFORM__COMP, err_msg);
	    interpret__mc_dbms__integer_to_string (num_params, p_param_name, p_param_value, p_rvalue);
	    simulator_supported = TRUE;
	}
	else if (func_name_str == "REAL_TO_STRING")
	{
		GS_UI_INFORM_START (UI_INFORM__COMP)
		Description err_msg ("Using Built-in Implementation for:  \"");
		err_msg += p_eekl;
		err_msg += "::";
		err_msg += p_func;
		err_msg += ";\"";
	    GS_UI_INFORM_END (UI_INFORM__COMP, err_msg);
	    interpret__mc_dbms__real_to_string (num_params, p_param_name, p_param_value, p_rvalue);
	    simulator_supported = TRUE;
	}
	else if (func_name_str == "BOOLEAN_TO_STRING")
	{
		GS_UI_INFORM_START (UI_INFORM__COMP)
		Description err_msg ("Using Built-in Implementation for:  \"");
		err_msg += p_eekl;
		err_msg += "::";
		err_msg += p_func;
		err_msg += ";\"";
	    GS_UI_INFORM_END (UI_INFORM__COMP, err_msg);
	    interpret__mc_dbms__boolean_to_string (num_params, p_param_name, p_param_value, p_rvalue);
	    simulator_supported = TRUE;
	}
    }


    if (! simulator_supported)
    {
	interpret_bridge_descrip (p_eekl, p_func, 
             num_params, p_param_name, p_param_value, p_param_readonly, p_rvalue);
    }


    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	"End #7:  SIM_SOR::interpret_bridge_expr (TRUE)."));

}


void SIM_SOR::interpret_bridge_descrip( const vchar *p_eekl, 
           const vchar *p_func, 
           int num_params, Description p_param_name[], GS_var_si p_param_value[],
           bool p_param_readonly[], GS_var_si &p_rvalue )
{
    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_BEGIN, (L_log_string,
	"Begin  SIM_SOR::interpret_bridge_descrip ()." ));


    mc_dbms_Bag <D_external_entity*>* ooa_ee_coll_ptr
	= GS_find::find_external_entity_by_key_letters
	(p_eekl);
    if (! ooa_ee_coll_ptr)
    {
	GS_ui::inform (UI_INFORM__ERROR, GS_string("Internal Error"));
	LOG_ERROR ((L_log_string,
	    "End #6:  SIM_SOR::interpret_bridge_descrip (FALSE):  Creation of External Entity collection in find returned 0."));
	return ;
    }

    if (ooa_ee_coll_ptr->cardinality () > 1)
    {
	    Description err_msg ("More than one object with keyletters '");
		err_msg += p_eekl;
	    err_msg += "' exists in OOA DB";
	GS_ui::inform (UI_INFORM__ERROR, err_msg);
	delete ooa_ee_coll_ptr;
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #8:  SIM_SOR::interpret_bridge_descrip (FALSE)."));
	return ;
    }


    D_external_entity* ooa_ee_ptr = ooa_ee_coll_ptr->pick ();
    delete ooa_ee_coll_ptr;
    if (! ooa_ee_ptr)
    {
	GS_ui::inform (UI_INFORM__ERROR, GS_string("Internal Error"));
	LOG_ERROR ((L_log_string,
	    "End #9:  SIM_SOR::interpret_bridge_descrip (FALSE):  External Entity pointer in collection of 1 element is 0."));
	return ;
    }


    D_bridge* ooa_bridge_ptr
	= ooa_ee_ptr->find_bridge_by_name (p_func);
    if (! ooa_bridge_ptr)
    {
	//  Bridge not found in OOA DB.
	//
	    Description err_msg ("Bridge '");
	    err_msg += p_eekl;
		err_msg += "::";
		err_msg += p_func;
	    err_msg += "' not found in OOA DB.";
	GS_ui::inform (UI_INFORM__ERROR, err_msg);
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #10:  SIM_SOR::interpret_bridge_descrip (FALSE)."));
	return ;
    }


	D_core_data_type* core_data_type_ptr = ooa_bridge_ptr->get_return_core_data_type_ptr ();
	D_enum_data_type* enum_data_type_ptr = ooa_bridge_ptr->get_return_enum_data_type_ptr ();
	t_core_data_type return_core_data_type;
	if ( enum_data_type_ptr )
	{
		return_core_data_type = ENUMERATION_DATATYPE;
	}
	else if ( core_data_type_ptr )
	{
		return_core_data_type = (t_core_data_type)
			core_data_type_ptr->get_core_data_type_type ();
	}
    else
    {
	GS_ui::inform (UI_INFORM__ERROR, GS_string("Internal Error"));
	LOG_ERROR ((L_log_string,
	    "End #11:  SIM_SOR::interpret_bridge_descrip (FALSE):  Unable to get return type of bridge."));
	return ;
    }


    D_user_data_type* return_user_data_type_ptr
	= ooa_bridge_ptr->get_return_user_data_type_ptr ();

    t_user_data_type return_user_data_type = USER_DEFINED_USERDATATYPE;
    if (return_user_data_type_ptr)
    {
      return_user_data_type = (t_user_data_type) return_user_data_type_ptr->
        get_general_service_mapping ();
    }


    //  Get the bridge description and determine if it should be simulated
    //    or not.
    //
    t_boolean interpret = TRUE;
    if ( ooa_bridge_ptr->get_last_parse_result() == D_execution_spec::AL_NOT_PARSED )
    {
        interpret = FALSE;
		GS_UI_INFORM_START (UI_INFORM__ERROR)
	    Description err_msg ("Action Specification for Bridge '");
	    err_msg += p_eekl;
		err_msg += "::";
		err_msg += p_func;
	    err_msg += "' has not been parsed.  Default value returned";
	    GS_UI_INFORM_END (UI_INFORM__ERROR, err_msg);
    }
    else if ( ooa_bridge_ptr->get_last_parse_result() != D_execution_spec::AL_PARSE_SUCCESSFUL )
    {
        interpret = FALSE;
		GS_UI_INFORM_START (UI_INFORM__ERROR)
	    Description err_msg ("Action Specification for Bridge '");
	    err_msg += p_eekl;
		err_msg += "::";
		err_msg += p_func;
	    err_msg += "' has parse errors.  Default value returned";
	    GS_UI_INFORM_END (UI_INFORM__ERROR, err_msg);
    }
    else if ( ooa_bridge_ptr->relocatable_desc_resolved() == FALSE )
    {
        interpret = FALSE;
		GS_UI_INFORM_START (UI_INFORM__ERROR)
	    Description err_msg ("Action Specification for Bridge '");
	    err_msg += p_eekl;
		err_msg += "::";
		err_msg += p_func;
	    err_msg += "' has unresolved symbols.  Default value returned";
	    GS_UI_INFORM_END (UI_INFORM__ERROR, err_msg);
    }

    if (interpret)
    {
		GS_UI_INFORM_START (UI_INFORM__STMT)
	    Description err_msg ("Bridge Method '");
	    err_msg += p_eekl;
		err_msg += "::";
		err_msg += p_func;
		err_msg += "' Invocation Begin.";
	GS_UI_INFORM_END (UI_INFORM__STMT, err_msg);
	GS_stack::mapping_point_begin ();

	for (int ii = 0;
	    ii < num_params;
	    ii++)
	{
	    GS_stack::push_var
		(p_param_value [ii].get_var_ptr (), p_param_name [ii], 
          GS_string__NULL, ! p_param_readonly[ii] );
	}

        // use the PCCTS parser
        // i2718.1 begin
        D_execution_spec::t_desc_state save_state = 
            ooa_bridge_ptr->get_desc_state ();
        ooa_bridge_ptr->set_desc_state (D_execution_spec::DESC_USE_RELOCATABLE);
        // i2718.1 end
        parser_interpret_bridge_logic (ooa_bridge_ptr, 
			ooa_bridge_ptr->action_specification (), p_rvalue );
        ooa_bridge_ptr->set_desc_state (save_state);    // i2718.1 added


    GS_stack::mapping_point_end ();
		GS_UI_INFORM_START (UI_INFORM__STMT)
	    Description err_msg2 ("Bridge Method '");
	    err_msg2 += p_eekl;
		err_msg2 += "::";
		err_msg2 += p_func;
		err_msg2 += "' Invocation End.";
	GS_UI_INFORM_END (UI_INFORM__STMT, err_msg2);
    }
    else
    {
	p_rvalue.replace_var (I_var::create_in_transient
	    (return_core_data_type,return_user_data_type));
    }

    if ( return_core_data_type != VOID_DATATYPE )
    {
      if ( p_rvalue.get_var_ptr () )
      {
        if (! ((return_core_data_type
      	      == p_rvalue.get_var_ptr ()->get_core_data_type ())
         	&&
        	(return_user_data_type
        	    == p_rvalue.get_var_ptr ()->get_user_data_type ())))
        {
          Description err_msg ("Bridge '");
		  err_msg += p_eekl;
		  err_msg += "::";
		  err_msg += p_func;
          err_msg += "' returned value with incorrect type.";
          GS_ui::inform (UI_INFORM__ERROR, err_msg);
          LOG_TRACE(L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
              "End #13:  SIM_SOR::interpret_bridge_descrip (FALSE)."));
          return ;
        }
      }
      else
      {
        p_rvalue.replace_var (new I_void_var () );
          Description err_msg ("Bridge '");
		  err_msg += p_eekl;
		  err_msg += "::";
		  err_msg += p_func;
          err_msg += "' did not return a value.";
          GS_ui::inform (UI_INFORM__ERROR, err_msg);
        LOG_TRACE(L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
            "End #14:  SIM_SOR::interpret_bridge_descrip (FALSE)."));
        return ;
      }
    }

    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	"End #7:  SIM_SOR::interpret_bridge_descrip (TRUE)."));

}

void SIM_SOR::interpret_transform_expr( const vchar *p_kl, const vchar *p_func, 
           int num_params, Description p_param_name[], GS_var_si p_param_value[],
           bool p_param_readonly[], GS_var_si &p_rvalue )
{
    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_BEGIN, (L_log_string,
	"Begin  SIM_SOR::interpret_transform_expr (p_kl=%s, p_func=%s).",
	p_kl, p_func));

    mc_dbms_Bag <Object*>* ooa_obj_coll_ptr
	= GS_find::find_object_by_key_letters (p_kl);
    if (! ooa_obj_coll_ptr)
    {
	GS_ui::inform (UI_INFORM__ERROR, GS_string("Internal Error."));
	LOG_ERROR ((L_log_string,
	    "End #6:  SIM_SOR::interpret_transform_expr ():  Creation of Object collection in find returned 0."));
	return ;
    }

    if (ooa_obj_coll_ptr->cardinality () > 1)
    {
	    Description err_msg ("More than one object with keyletters '");
		err_msg += p_kl;
	    err_msg += "' exists in OOA DB";
	GS_ui::inform (UI_INFORM__WARNING, err_msg);
	delete ooa_obj_coll_ptr;
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #8:  SIM_SOR::interpret_transform_expr ()."));
	return ;
    }


    Object* ooa_obj_ptr = ooa_obj_coll_ptr->pick ();
    delete ooa_obj_coll_ptr;
    if (! ooa_obj_ptr)
    {
	GS_ui::inform (UI_INFORM__ERROR, GS_string("Internal Error."));
	LOG_ERROR ((L_log_string,
	    "End #9:  SIM_SOR::interpret_transform_expr ():  Object pointer in collection of 1 element is 0."));
	return ;
    }


    D_transformer* ooa_xform_ptr
	= ooa_obj_ptr->find_transformer_by_name (p_func);

	D_core_data_type* core_data_type_ptr = ooa_xform_ptr->get_return_core_data_type_ptr ();
	D_enum_data_type* enum_data_type_ptr = ooa_xform_ptr->get_return_enum_data_type_ptr ();
	t_core_data_type return_core_data_type;
	if ( enum_data_type_ptr )
	{
		return_core_data_type = ENUMERATION_DATATYPE;
	}
	else if ( core_data_type_ptr )
	{
		return_core_data_type = (t_core_data_type)
			core_data_type_ptr->get_core_data_type_type ();
	}
    else
    {
	GS_ui::inform (UI_INFORM__ERROR, GS_string("Internal Error"));
	LOG_ERROR ((L_log_string,
	    "End #11:  SIM_SOR::interpret_transform_expr (FALSE):  Unable to get return type of transform."));
	return ;
    }

    D_user_data_type* return_user_data_type_ptr
	= ooa_xform_ptr->get_return_user_data_type_ptr ();

    t_user_data_type return_user_data_type = USER_DEFINED_USERDATATYPE;
    if (return_user_data_type_ptr)
    {
      return_user_data_type = (t_user_data_type) return_user_data_type_ptr->
	    get_general_service_mapping ();
    }

    //  Get the transformer description and determine if it should be simulated
    //    or not.
    //
    t_boolean interpret = TRUE;
    if ( ooa_xform_ptr->get_last_parse_result() == D_execution_spec::AL_NOT_PARSED )
    {
        interpret = FALSE;
		GS_UI_INFORM_START (UI_INFORM__ERROR)
	    Description err_msg ("Action Specification for Transformer '");
	    err_msg += p_kl;
		err_msg += "::";
		err_msg += p_func;
	    err_msg += "' has not been parsed.  Default value returned";
	    GS_UI_INFORM_END (UI_INFORM__ERROR, err_msg);
    }
    else if ( ooa_xform_ptr->get_last_parse_result() != D_execution_spec::AL_PARSE_SUCCESSFUL )
    {
        interpret = FALSE;
		GS_UI_INFORM_START (UI_INFORM__ERROR)
	    Description err_msg ("Action Specification for Transformer '");
	    err_msg += p_kl;
		err_msg += "::";
		err_msg += p_func;
	    err_msg += "' has parse errors.  Default value returned";
	    GS_UI_INFORM_END (UI_INFORM__ERROR, err_msg);
    }
    else if ( ooa_xform_ptr->relocatable_desc_resolved() == FALSE )
    {
        interpret = FALSE;
		GS_UI_INFORM_START (UI_INFORM__ERROR)
	    Description err_msg ("Action Specification for Transformer '");
	    err_msg += p_kl;
		err_msg += "::";
		err_msg += p_func;
	    err_msg += "' has unresolved symbols.  Default value returned";
	    GS_UI_INFORM_END (UI_INFORM__ERROR, err_msg);
    }

    if (interpret)
    {
		GS_UI_INFORM_START (UI_INFORM__STMT)
	    Description err_msg ("Transformer Method '");
	    err_msg += p_kl;
		err_msg += "::";
		err_msg += p_func;
		err_msg += "' Invocation Begin.";
	GS_UI_INFORM_END (UI_INFORM__STMT, err_msg);
	GS_stack::mapping_point_begin ();

	for (int ii = 0;
	    ii < num_params;
	    ii++)
	{
	    GS_stack::push_var
		(p_param_value[ii].get_var_ptr (), p_param_name[ii], 
          GS_string__NULL, ! p_param_readonly[ii] );
	}

        // use the PCCTS parser
        // i2718.4 begin
        D_execution_spec::t_desc_state save_state = 
            ooa_xform_ptr->get_desc_state ();
        ooa_xform_ptr->set_desc_state (D_execution_spec::DESC_USE_RELOCATABLE);
        // i2718.4 end
        parser_interpret_transformer_logic (ooa_xform_ptr, 
			ooa_xform_ptr->action_specification (), p_rvalue );
        ooa_xform_ptr->set_desc_state (save_state);   // i2718.4 added

	GS_stack::mapping_point_end ();
		GS_UI_INFORM_START (UI_INFORM__STMT)
	    Description err_msg2 ("Transformer Method '");
	    err_msg2 += p_kl;
		err_msg2 += "::";
		err_msg2 += p_func;
		err_msg2 += "' Invocation End.";
	GS_UI_INFORM_END (UI_INFORM__STMT, err_msg2);
    }
    else
    {
	p_rvalue.replace_var (I_var::create_in_transient
	    (return_core_data_type, return_user_data_type));
    }

    if ( return_core_data_type != VOID_DATATYPE )
    {
      if ( p_rvalue.get_var_ptr () )
      {
        if (! ((return_core_data_type
                == p_rvalue.get_var_ptr ()->get_core_data_type ())
             &&
               (return_user_data_type
                == p_rvalue.get_var_ptr ()->get_user_data_type ())))
        {
          Description err_msg ("Transformer '");
		  err_msg += p_kl;
		  err_msg += "::";
		  err_msg += p_func;
          err_msg += "' returned value with incorrect type.";
          GS_ui::inform (UI_INFORM__ERROR, err_msg);
          LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	          "End #13:  SIM_SOR::interpret_transform_expr ()."));
          return ;
        }
      }
      else
      {
        p_rvalue.replace_var (new I_void_var () );
          Description err_msg ("Transformer '");
		  err_msg += p_kl;
		  err_msg += "::";
		  err_msg += p_func;
          err_msg += "' did not return a value.";
          GS_ui::inform (UI_INFORM__ERROR, err_msg);
        LOG_TRACE(L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
            "End #14:  SIM_SOR::interpret_transform_expr ()."));
        return ;
      }
    }


    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	"End #15:  SIM_SOR::interpret_transform_expr ()."));
    return ;
}

void SIM_SOR::interpret_ib_transform_expr( const vchar *p_irv, const vchar *p_func, 
           int num_params, Description p_param_name[], GS_var_si p_param_value[],
           bool p_param_readonly[], GS_var_si &p_rvalue )
{
    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_BEGIN, (L_log_string,
	"Begin  SIM_SOR::interpret_ib_transform_expr (p_kl=%s, p_func=%s).",
	p_irv, p_func));

    I_object_inst_ref_var* object_inst_ref_var_ptr
      = GS_stack::find_object_inst_ref_var_ptr (p_irv);
	if (!object_inst_ref_var_ptr)
	{
		GS_UI_INFORM_START (UI_INFORM__ERROR)
	    Description err_msg ("Error: inst_ref<Object> variable '");
	    err_msg += p_irv;
		err_msg += "' does not exist.";
	    GS_UI_INFORM_END (UI_INFORM__ERROR, err_msg);
	   LOG_ERROR ((L_log_string,
	    "End #1:  SIM_SOR::interpret_ib_transform_expr ():  Variable does not exist."));
       return;
    }

    I_Object_Instance* oinst_ptr = object_inst_ref_var_ptr->get_oinst_ptr();
	if (!oinst_ptr)
	{
		GS_UI_INFORM_START (UI_INFORM__ERROR)
	    Description err_msg ("Error: inst_ref<Object> variable '");
	    err_msg += p_irv;
		err_msg += "' is an null reference.";
	    GS_UI_INFORM_END (UI_INFORM__ERROR, err_msg);
	   LOG_ERROR ((L_log_string,
	    "End #2:  SIM_SOR::interpret_ib_transform_expr ():  Variable is a null reference."));
       return;
    }

    I_Object* sim_dest_obj_ptr = oinst_ptr->get_Object_R2001_ptr ();
    if (sim_dest_obj_ptr == 0)   // it's an assigner instance, error
    {
 	   GS_ui::inform (UI_INFORM__ERROR, GS_string("Internal Error: variable points to assigner instance."));
	   LOG_ERROR ((L_log_string,
	    "End #3:  SIM_SOR::interpret_ib_transform_expr ():  Variable points to an assigner instance."));
        return;
    }

    Object*  ooa_obj_ptr
        = GS_find::find_object_by_id (sim_dest_obj_ptr->get_object_ID ());

    D_transformer* ooa_xform_ptr
	= ooa_obj_ptr->find_transformer_by_name (p_func);

	D_core_data_type* core_data_type_ptr = ooa_xform_ptr->get_return_core_data_type_ptr ();
	D_enum_data_type* enum_data_type_ptr = ooa_xform_ptr->get_return_enum_data_type_ptr ();
	t_core_data_type return_core_data_type;
	if ( enum_data_type_ptr )
	{
		return_core_data_type = ENUMERATION_DATATYPE;
	}
	else if ( core_data_type_ptr )
	{
		return_core_data_type = (t_core_data_type)
			core_data_type_ptr->get_core_data_type_type ();
	}
    else
    {
	GS_ui::inform (UI_INFORM__ERROR, GS_string("Internal Error"));
	LOG_ERROR ((L_log_string,
	    "End #11:  SIM_SOR::interpret_ib_transform_expr (FALSE):  Unable to get return type of transform."));
	return ;
    }

    D_user_data_type* return_user_data_type_ptr
	= ooa_xform_ptr->get_return_user_data_type_ptr ();

    t_user_data_type return_user_data_type = USER_DEFINED_USERDATATYPE;
    if (return_user_data_type_ptr)
    {
      return_user_data_type = (t_user_data_type) return_user_data_type_ptr->
	    get_general_service_mapping ();
    }

    //  Get the transformer description and determine if it should be simulated
    //    or not.
    //
    t_boolean interpret = TRUE;
    if ( ooa_xform_ptr->get_last_parse_result() == D_execution_spec::AL_NOT_PARSED )
    {
        interpret = FALSE;
		GS_UI_INFORM_START (UI_INFORM__ERROR)
	    Description err_msg ("Action Specification for Transformer '");
	    err_msg += ooa_obj_ptr->object_key_letters();
		err_msg += "::";
		err_msg += p_func;
	    err_msg += "' has not been parsed.  Default value returned";
	    GS_UI_INFORM_END (UI_INFORM__ERROR, err_msg);
    }
    else if ( ooa_xform_ptr->get_last_parse_result() != D_execution_spec::AL_PARSE_SUCCESSFUL )
    {
        interpret = FALSE;
		GS_UI_INFORM_START (UI_INFORM__ERROR)
	    Description err_msg ("Action Specification for Transformer '");
	    err_msg += ooa_obj_ptr->object_key_letters();
		err_msg += "::";
		err_msg += p_func;
	    err_msg += "' has parse errors.  Default value returned";
	    GS_UI_INFORM_END (UI_INFORM__ERROR, err_msg);
    }
    else if ( ooa_xform_ptr->relocatable_desc_resolved() == FALSE )
    {
        interpret = FALSE;
		GS_UI_INFORM_START (UI_INFORM__ERROR)
	    Description err_msg ("Action Specification for Transformer '");
	    err_msg += ooa_obj_ptr->object_key_letters();
		err_msg += "::";
		err_msg += p_func;
	    err_msg += "' has unresolved symbols.  Default value returned";
	    GS_UI_INFORM_END (UI_INFORM__ERROR, err_msg);
    }

    if (interpret)
    {
		GS_UI_INFORM_START (UI_INFORM__STMT)
	    Description err_msg ("Transformer Method '");
	    err_msg += ooa_obj_ptr->object_key_letters();
		err_msg += "::";
		err_msg += p_func;
		err_msg += "' Invocation Begin.";
        GS_UI_INFORM_END (UI_INFORM__STMT, err_msg);

	    GS_stack::mapping_point_begin ();

	    I_object_inst_ref_var* self_inst_ptr = new I_object_inst_ref_var
	        (sim_dest_obj_ptr, oinst_ptr);
	    if (! self_inst_ptr)
	    {
            GS_stack::mapping_point_end ();
	        LOG_ERROR ((L_log_string,
		    "End #4:  SIM_SOR::interpret_ib_transform_expr ():  creation of I_object_inst_ref_var failed."));
	        return;
	    }
	    GS_stack::push_var (self_inst_ptr, "SELF");
	    self_inst_ptr = new I_object_inst_ref_var (sim_dest_obj_ptr, oinst_ptr);
	    if (! self_inst_ptr)
	    {
            GS_stack::mapping_point_end ();
	        LOG_ERROR ((L_log_string,
		    "End #5:  SIM_SOR::interpret_ib_transform_expr ():  creation of I_object_inst_ref_var failed."));
	        return;
	    }
	    GS_stack::push_var (self_inst_ptr, "Self");
	    self_inst_ptr = new I_object_inst_ref_var (sim_dest_obj_ptr, oinst_ptr);
	    if (! self_inst_ptr)
	    {
            GS_stack::mapping_point_end ();
	        LOG_ERROR ((L_log_string,
		    "End #6:  SIM_SOR::interpret_ib_transform_expr ():  creation of I_object_inst_ref_var failed."));
	        return;
	    }
	    GS_stack::push_var (self_inst_ptr, "self");

        for (int ii = 0;
	        ii < num_params;
	        ii++)
	    {
	        GS_stack::push_var
		    (p_param_value[ii].get_var_ptr (), p_param_name[ii], 
               GS_string__NULL, ! p_param_readonly[ii] );
	    }

        // use the PCCTS parser
        // i2718.3 begin
        D_execution_spec::t_desc_state save_state = 
            ooa_xform_ptr->get_desc_state ();
        ooa_xform_ptr->set_desc_state (D_execution_spec::DESC_USE_RELOCATABLE);
        // i2718.3 end 
        parser_interpret_ib_transformer_logic (oinst_ptr, ooa_xform_ptr, 
			ooa_xform_ptr->action_specification (), p_rvalue );
        ooa_xform_ptr->set_desc_state (save_state);    // i2718.3 added

        GS_stack::mapping_point_end ();

		GS_UI_INFORM_START (UI_INFORM__STMT)
	    Description err_msg2 ("Transformer Method '");
	    err_msg2 += ooa_obj_ptr->object_key_letters();
		err_msg2 += "::";
		err_msg2 += p_func;
		err_msg2 += "' Invocation End.";
	    GS_UI_INFORM_END (UI_INFORM__STMT, err_msg2);
    }
    else
    {

	p_rvalue.replace_var (I_var::create_in_transient
	    (return_core_data_type, return_user_data_type));
    }

    if ( return_core_data_type != VOID_DATATYPE )
    {
      if ( p_rvalue.get_var_ptr () )
      {
        if (! ((return_core_data_type
                == p_rvalue.get_var_ptr ()->get_core_data_type ())
             &&
               (return_user_data_type
                == p_rvalue.get_var_ptr ()->get_user_data_type ())))
        {
          Description err_msg ("Transformer '");
		  err_msg += ooa_obj_ptr->object_key_letters();
		  err_msg += "::";
		  err_msg += p_func;
          err_msg += "' returned value with incorrect type.";
          GS_ui::inform (UI_INFORM__ERROR, err_msg);
          LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	          "End #13:  SIM_SOR::interpret_ib_transform_expr ()."));
          return ;
        }
      }
      else
      {
        p_rvalue.replace_var (new I_void_var () );
          Description err_msg ("Transformer '");
		  err_msg += ooa_obj_ptr->object_key_letters();
		  err_msg += "::";
		  err_msg += p_func;
          err_msg += "' did not return a value.";
          GS_ui::inform (UI_INFORM__ERROR, err_msg);
        LOG_TRACE(L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
            "End #14:  SIM_SOR::interpret_ib_transform_expr ()."));
        return ;
      }
    }


    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	"End #15:  SIM_SOR::interpret_ib_transform_expr ()."));
    return ;
}


void SIM_SOR::interpret_synch_service_descrip( const vchar *p_func, 
           int num_params, Description p_param_name[], GS_var_si p_param_value[],
           bool p_param_readonly[], GS_var_si &p_rvalue )
{
    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_BEGIN, (L_log_string,
	"Begin  SIM_SOR::interpret_synch_service_descrip ()." ));


    mc_dbms_Bag <D_synchronous_service*>* ooa_ss_coll_ptr
	= GS_find::find_synch_service_by_name(p_func);
    if (! ooa_ss_coll_ptr)
    {
	GS_ui::inform (UI_INFORM__ERROR, GS_string("Internal Error"));
	LOG_ERROR ((L_log_string,
	    "End #6:  SIM_SOR::interpret_synch_service_descrip (FALSE):  Creation of External Entity collection in find returned 0."));
	return ;
    }

    if (ooa_ss_coll_ptr->cardinality () > 1)
    {
	    Description err_msg ("More than one synchronous service with name '");
		err_msg += p_func;
	    err_msg += "' exists in OOA DB";
	GS_ui::inform (UI_INFORM__ERROR, err_msg);
	delete ooa_ss_coll_ptr;
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #8:  SIM_SOR::interpret_synch_service_descrip (FALSE)."));
	return ;
    }

    if (ooa_ss_coll_ptr->cardinality () == 0)
    {
	//  Service not found in OOA DB.
	//
	    Description err_msg ("Synchronous Service '");
		err_msg += p_func;
	    err_msg += "' not found in OOA DB.";
	GS_ui::inform (UI_INFORM__ERROR, err_msg);
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #9:  SIM_SOR::interpret_synch_service_descrip (FALSE)."));
	delete ooa_ss_coll_ptr;
	return ;
    }


    D_synchronous_service* ooa_synch_service_ptr = ooa_ss_coll_ptr->pick ();
    delete ooa_ss_coll_ptr;
    if (! ooa_synch_service_ptr)
    {
	GS_ui::inform (UI_INFORM__ERROR, GS_string("Internal Error"));
	LOG_ERROR ((L_log_string,
	    "End #10:  SIM_SOR::interpret_synch_service_descrip (FALSE):  Synchronous Service pointer in collection of 1 element is 0."));
	return ;
    }


	D_core_data_type* core_data_type_ptr = ooa_synch_service_ptr->get_return_core_data_type_ptr ();
	D_enum_data_type* enum_data_type_ptr = ooa_synch_service_ptr->get_return_enum_data_type_ptr ();
	t_core_data_type return_core_data_type;
	if ( enum_data_type_ptr )
	{
		return_core_data_type = ENUMERATION_DATATYPE;
	}
	else if ( core_data_type_ptr )
	{
		return_core_data_type = (t_core_data_type)
			core_data_type_ptr->get_core_data_type_type ();
	}
    else
    {
	GS_ui::inform (UI_INFORM__ERROR, GS_string("Internal Error"));
	LOG_ERROR ((L_log_string,
	    "End #11:  SIM_SOR::interpret_synch_service_descrip (FALSE):  Unable to get return type of synch service."));
	return ;
    }

    D_user_data_type* return_user_data_type_ptr
	= ooa_synch_service_ptr->get_return_user_data_type_ptr ();

    t_user_data_type return_user_data_type = USER_DEFINED_USERDATATYPE;
    if (return_user_data_type_ptr)
    {
      return_user_data_type = (t_user_data_type) return_user_data_type_ptr->
        get_general_service_mapping ();
    }


    //  Get the bridge description and determine if it should be simulated
    //    or not.
    //
    t_boolean interpret = TRUE;
    if ( ooa_synch_service_ptr->get_last_parse_result() == D_execution_spec::AL_NOT_PARSED )
    {
        interpret = FALSE;
		GS_UI_INFORM_START (UI_INFORM__ERROR)
	    Description err_msg ("Action Specification for Synchronous Service '");
        err_msg += p_func;
	    err_msg += "' has not been parsed.  Default value returned";
	    GS_UI_INFORM_END (UI_INFORM__ERROR, err_msg);
    }
    else if ( ooa_synch_service_ptr->get_last_parse_result() != D_execution_spec::AL_PARSE_SUCCESSFUL )
    {
        interpret = FALSE;
		GS_UI_INFORM_START (UI_INFORM__ERROR)
	    Description err_msg ("Action Specification for Synchronous Service '");
		err_msg += p_func;
	    err_msg += "' has parse errors.  Default value returned";
	    GS_UI_INFORM_END (UI_INFORM__ERROR, err_msg);
    }
    else if ( ooa_synch_service_ptr->relocatable_desc_resolved() == FALSE )
    {
        interpret = FALSE;
		GS_UI_INFORM_START (UI_INFORM__ERROR)
	    Description err_msg ("Action Specification for Synchronous Service '");
		err_msg += p_func;
	    err_msg += "' has unresolved symbols.  Default value returned";
	    GS_UI_INFORM_END (UI_INFORM__ERROR, err_msg);
    }



    if (interpret)
    {
		GS_UI_INFORM_START (UI_INFORM__STMT)
	    Description err_msg ("Synchronous Service '");
		err_msg += p_func;
		err_msg += "' Invocation Begin.";
	GS_UI_INFORM_END (UI_INFORM__STMT, err_msg);
	GS_stack::mapping_point_begin ();

	for (int ii = 0;
	    ii < num_params;
	    ii++)
	{
	    GS_stack::push_var
		(p_param_value [ii].get_var_ptr (), p_param_name [ii], 
          GS_string__NULL, ! p_param_readonly[ii] );
	}

        // use the PCCTS parser
        // i2718.2 begin
        D_execution_spec::t_desc_state save_state = 
            ooa_synch_service_ptr->get_desc_state ();
        ooa_synch_service_ptr->set_desc_state (D_execution_spec::DESC_USE_RELOCATABLE);
        // i2718.2 end
        parser_interpret_synch_service_logic (ooa_synch_service_ptr, 
			ooa_synch_service_ptr->action_specification (), p_rvalue );
        ooa_synch_service_ptr->set_desc_state (save_state);   // i2718.2 added

	GS_stack::mapping_point_end ();
		GS_UI_INFORM_START (UI_INFORM__STMT)
	    Description err_msg2 ("Synchronous Service '");
		err_msg2 += p_func;
		err_msg2 += "' Invocation End.";
	GS_UI_INFORM_END (UI_INFORM__STMT, err_msg2);
    }
    else
    {

	p_rvalue.replace_var (I_var::create_in_transient
	    (return_core_data_type, return_user_data_type));
    }

    if ( return_core_data_type != VOID_DATATYPE )
    {
      if ( p_rvalue.get_var_ptr () )
      {
        if (! ((return_core_data_type
      	      == p_rvalue.get_var_ptr ()->get_core_data_type ())
         	&&
        	(return_user_data_type
        	    == p_rvalue.get_var_ptr ()->get_user_data_type ())))
        {
          Description err_msg ("Synchronous Service '");
		  err_msg += p_func;
          err_msg += "' returned value with incorrect type.";
          GS_ui::inform (UI_INFORM__ERROR, err_msg);
          LOG_TRACE(L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
              "End #13:  SIM_SOR::interpret_synch_service_descrip (FALSE)."));
          return ;
        }
      }
      else
      {
        p_rvalue.replace_var (new I_void_var () );
          Description err_msg ("Synchronous Service '");
		  err_msg += p_func;
          err_msg += "' did not return a value.";
          GS_ui::inform (UI_INFORM__ERROR, err_msg);
        LOG_TRACE(L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
            "End #14:  SIM_SOR::interpret_synch_service_descrip (FALSE)."));
        return ;
      }
    }

    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	"End #7:  SIM_SOR::interpret_synch_service_descrip (TRUE)."));

}

bool SIM_SOR::interpret_bridge_param ( const vchar *p_din, 
   Description& p_param_name,  GS_var_si &param_value )
{
   p_param_name = Description ("param.");
   p_param_name += p_din;
   if (param_value.get_void_var_ptr () ||
	   param_value.get_var_ptr() == 0)
   {
 	Description err_msg ("Value of Bridge Parameter '");
	err_msg += p_din;
	err_msg += "' not recoginzed.";
     GS_ui::inform (UI_INFORM__ERROR, err_msg);
     LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	"End #1:  SIM_SOR::interpret_bridge_param (FALSE)."));
     return FALSE;
   }

   return TRUE;
}

bool SIM_SOR::interpret_transform_param ( const vchar *p_din, 
   Description& p_param_name,  GS_var_si &param_value )
{
   p_param_name = Description ("param.");
   p_param_name += p_din;
   if (param_value.get_void_var_ptr () ||
	   param_value.get_var_ptr() == 0)
   {
 	Description err_msg ("Value of Transformer Parameter '");
	err_msg += p_din;
	err_msg += "' not recoginzed.";
     GS_ui::inform (UI_INFORM__ERROR, err_msg);
     LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	"End #1:  SIM_SOR::interpret_transform_param (FALSE)."));
     return FALSE;
   }

   return TRUE;
}

bool SIM_SOR::interpret_synch_service_param ( const vchar *p_din, 
   Description& p_param_name,  GS_var_si &param_value )
{
   p_param_name = Description ("param.");
   p_param_name += p_din;
   if (param_value.get_void_var_ptr () ||
	   param_value.get_var_ptr() == 0)
   {
 	Description err_msg ("Value of Synchronous Service Parameter '");
	err_msg += p_din;
	err_msg += "' not recoginzed.";
     GS_ui::inform (UI_INFORM__ERROR, err_msg);
     LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	"End #1:  SIM_SOR::interpret_synch_service_param (FALSE)."));
     return FALSE;
   }

   return TRUE;
}


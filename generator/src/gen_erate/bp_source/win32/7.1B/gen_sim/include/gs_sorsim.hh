/*========================================================================
 *
 * File:      $RCSfile: gs_sorsim.hh,v $
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
#ifndef GS_SORSIM_HH
#define GS_SORSIM_HH


class D_action;
class D_bridge;
class D_synchronous_service;
class D_transformer;
class Base_attribute;
class Description;
class GS_var_si;
class I_Object_Instance;
class I_Object_Instance;
class I_SM_Evt_Inst;

void parser_interpret_action_logic
    (I_Object_Instance* p_oinst_ptr,
     I_SM_Evt_Inst* p_einst_ptr,
     D_action* p_D_action_ptr,
     const Description& p_action_str);

void parser_interpret_bridge_logic
    (D_bridge* p_bridge_ptr,
     const Description& p_action_str,
     GS_var_si& p_return_var_si);

void parser_interpret_transformer_logic
    (D_transformer* p_transformer_ptr,
     const Description& p_action_str,
     GS_var_si& p_return_var_si);

void parser_interpret_ib_transformer_logic
    (I_Object_Instance* p_oinst_ptr,
	 D_transformer* p_transformer_ptr,
     const Description& p_action_str,
     GS_var_si& p_return_var_si);

void parser_interpret_synch_service_logic
    (D_synchronous_service* p_synch_service_ptr,
     const Description& p_action_str,
     GS_var_si& p_return_var_si);

void parser_interpret_attribute_logic
    (I_Object_Instance* p_oinst_ptr,
	 Base_attribute* p_attr_ptr,
     const Description& p_action_str,
     GS_var_si& p_return_var_si);



#endif

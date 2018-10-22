/*========================================================================
 *
 * File:      $RCSfile: schema_gen.cc,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:36 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#include  <i_c_rop.hh>
#include  <i_rop.hh>
#include  <i_var.hh>
#include  <i_ainst.hh>
#include  <i_oinst.hh>
#include  <i_idaref.hh>
#include  <i_ir_rop.hh>
#include  <i_rel.hh>
#include  <i_obj.hh>
#include  <i_attr.hh>
#include  <i_einst.hh>
#include  <i_clock.hh>
#include  <i_esdii.hh>
#include  <i_evt.hh>
#include  <i_roip.hh>
#include  <i_esdi.hh>
#include <mc_dbms/mc_dbms.hh>

mc_dbms_typespec* I_Chain_Rel_Obj_Pair::get_mc_dbms_typespec()
{
	static mc_dbms_typespec type("I_Chain_Rel_Obj_Pair",sizeof(I_Chain_Rel_Obj_Pair));
	return &type;
}


mc_dbms_typespec* I_Related_Object_Pair::get_mc_dbms_typespec()
{
	static mc_dbms_typespec type("I_Related_Object_Pair",sizeof(I_Related_Object_Pair));
	return &type;
}
mc_dbms_typespec* I_frag_ref_var::get_mc_dbms_typespec()
{
	static mc_dbms_typespec type("I_frag_ref_var",sizeof(I_frag_ref_var));
	return &type;
}

mc_dbms_typespec* I_timer_inst_ref_var::get_mc_dbms_typespec()
{
	static mc_dbms_typespec type("I_timer_inst_ref_var",sizeof(I_timer_inst_ref_var));
	return &type;
}

mc_dbms_typespec* I_mapping_inst_ref_var::get_mc_dbms_typespec()
{
	static mc_dbms_typespec type("I_mapping_inst_ref_var",sizeof(I_mapping_inst_ref_var));
	return &type;
}

mc_dbms_typespec* I_date_var::get_mc_dbms_typespec()
{
	static mc_dbms_typespec type("I_date_var",sizeof(I_date_var));
	return &type;
}

mc_dbms_typespec* I_timestamp_var::get_mc_dbms_typespec()
{
	static mc_dbms_typespec type("I_timestamp_var",sizeof(I_timestamp_var));
	return &type;
}

mc_dbms_typespec* I_mapping_inst_var::get_mc_dbms_typespec()
{
	static mc_dbms_typespec type("I_mapping_inst_var",sizeof(I_mapping_inst_var));
	return &type;
}

mc_dbms_typespec* I_event_inst_var::get_mc_dbms_typespec()
{
	static mc_dbms_typespec type("I_event_inst_var",sizeof(I_event_inst_var));
	return &type;
}

mc_dbms_typespec* I_object_inst_ref_set_var::get_mc_dbms_typespec()
{
	static mc_dbms_typespec type("I_object_inst_ref_set_var",sizeof(I_object_inst_ref_set_var));
	return &type;
}

mc_dbms_typespec* I_object_inst_ref_var::get_mc_dbms_typespec()
{
	static mc_dbms_typespec type("I_object_inst_ref_var",sizeof(I_object_inst_ref_var));
	return &type;
}

mc_dbms_typespec* I_current_state_var::get_mc_dbms_typespec()
{
	static mc_dbms_typespec type("I_current_state_var",sizeof(I_current_state_var));
	return &type;
}

mc_dbms_typespec* I_unique_id_var::get_mc_dbms_typespec()
{
	static mc_dbms_typespec type("I_unique_id_var",sizeof(I_unique_id_var));
	return &type;
}

mc_dbms_typespec* I_string_var::get_mc_dbms_typespec()
{
	static mc_dbms_typespec type("I_string_var",sizeof(I_string_var));
	return &type;
}

mc_dbms_typespec* I_real_var::get_mc_dbms_typespec()
{
	static mc_dbms_typespec type("I_real_var",sizeof(I_real_var));
	return &type;
}

mc_dbms_typespec* I_integer_var::get_mc_dbms_typespec()
{
	static mc_dbms_typespec type("I_integer_var",sizeof(I_integer_var));
	return &type;
}

mc_dbms_typespec* I_boolean_var::get_mc_dbms_typespec()
{
	static mc_dbms_typespec type("I_boolean_var",sizeof(I_boolean_var));
	return &type;
}

mc_dbms_typespec* I_enumerator_var::get_mc_dbms_typespec()
{
	static mc_dbms_typespec type("I_enumerator_var",sizeof(I_enumerator_var));
	return &type;
}

mc_dbms_typespec* I_void_var::get_mc_dbms_typespec()
{
	static mc_dbms_typespec type("I_void_var",sizeof(I_void_var));
	return &type;
}

mc_dbms_typespec* I_Attribute_Instance::get_mc_dbms_typespec()
{
	static mc_dbms_typespec type("I_Attribute_Instance",sizeof(I_Attribute_Instance));
	return &type;
}

mc_dbms_typespec* I_Object_Instance::get_mc_dbms_typespec()
{
	static mc_dbms_typespec type("I_Object_Instance",sizeof(I_Object_Instance));
	return &type;
}

mc_dbms_typespec* I_ID_Attribute_Reference::get_mc_dbms_typespec()
{
	static mc_dbms_typespec type("I_ID_Attribute_Reference",sizeof(I_ID_Attribute_Reference));
	return &type;
}

mc_dbms_typespec* I_ID_REF_Rel_Obj_Pair::get_mc_dbms_typespec()
{
	static mc_dbms_typespec type("I_ID_REF_Rel_Obj_Pair",sizeof(I_ID_REF_Rel_Obj_Pair));
	return &type;
}

mc_dbms_typespec* I_Relationship::get_mc_dbms_typespec()
{
	static mc_dbms_typespec type("I_Relationship",sizeof(I_Relationship));
	return &type;
}

mc_dbms_typespec* I_Object::get_mc_dbms_typespec()
{
	static mc_dbms_typespec type("I_Object",sizeof(I_Object));
	return &type;
}

mc_dbms_typespec* I_Attribute::get_mc_dbms_typespec()
{
	static mc_dbms_typespec type("I_Attribute",sizeof(I_Attribute));
	return &type;
}

mc_dbms_typespec* I_SM_Evt_Inst::get_mc_dbms_typespec()
{
	static mc_dbms_typespec type("I_SM_Evt_Inst",sizeof(I_SM_Evt_Inst));
	return &type;
}

mc_dbms_typespec* I_Clock::get_mc_dbms_typespec()
{
	static mc_dbms_typespec type("I_Clock",sizeof(I_Clock));
	return &type;
}

mc_dbms_typespec* I_SM_Evt_Supp_DI_Inst::get_mc_dbms_typespec()
{
	static mc_dbms_typespec type("I_SM_Evt_Supp_DI_Inst",sizeof(I_SM_Evt_Supp_DI_Inst));
	return &type;
}

mc_dbms_typespec* I_SM_Evt::get_mc_dbms_typespec()
{
	static mc_dbms_typespec type("I_SM_Evt",sizeof(I_SM_Evt));
	return &type;
}

mc_dbms_typespec* I_Related_Object_Instance_Pair::get_mc_dbms_typespec()
{
	static mc_dbms_typespec type("I_Related_Object_Instance_Pair",sizeof(I_Related_Object_Instance_Pair));
	return &type;
}

mc_dbms_typespec* I_SM_Evt_Supp_DI::get_mc_dbms_typespec()
{
	static mc_dbms_typespec type("I_SM_Evt_Supp_DI",sizeof(I_SM_Evt_Supp_DI));
	return &type;
}


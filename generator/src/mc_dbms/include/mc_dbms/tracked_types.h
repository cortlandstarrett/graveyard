/*========================================================================
 *
 * File:      $RCSfile: tracked_types.h,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:52 $
 *
 * (c) Copyright 2005-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#ifndef _included_tracked_types_
#define _included_tracked_types_ 1

enum TrackedType 
{
	tt_UnitializedTypeID = -1,

	/* We'll start with "1" making 0 (or smaller) an invalid value.  One reason 
	 * for this is that we want to be able to tell the difference between 
	 * something that has not been initialized vs something that may be a real 
	 * type identifier.
	 */
	tt_char = 1,
	tt_uchar,
	tt_ushort,
	tt_ulong,
	tt_mc_dbms_collection,
	tt_mc_dbms_Array,
	tt_mc_dbms_Bag,
	tt_mc_dbms_List,
	tt_mc_dbms_Set,
	tt_mc_dbms_Dictionary,
	tt_mc_dbms_cursor,

	tt_I_frag_ref_var,
	tt_I_timer_inst_ref_var,
	tt_I_mapping_inst_ref_var,
	tt_I_date_var,
	tt_I_timestamp_var,
	tt_I_mapping_inst_var,
	tt_I_event_inst_var,
	tt_I_object_inst_ref_var,
	tt_I_object_inst_ref_set_var,
	tt_I_current_state_var,
	tt_I_unique_id_var,
	tt_I_string_var,
	tt_I_real_var,
	tt_I_integer_var,
	tt_I_boolean_var,
	tt_I_enumerator_var,
	tt_I_void_var,
	
	tt_I_Chain_Rel_Obj_Pair,
	tt_I_Related_Object_Pair,
	tt_I_Attribute_Instance,
	tt_I_Object_Instance,
	tt_I_ID_Attribute_Reference,
	tt_I_ID_REF_Rel_Obj_Pair,
	tt_I_Relationship,
	tt_I_Object,
	tt_I_Attribute,
	tt_I_SM_Evt_Inst,
	tt_I_Clock,
	tt_I_SM_Evt_Supp_DI_Inst,
	tt_I_SM_Evt,
	tt_I_Related_Object_Instance_Pair,
	tt_Id_assigner,
	tt_String,
	tt_I_SM_Evt_Supp_DI

};


#endif // _included_tracked_types_

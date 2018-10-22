/*========================================================================
 *
 * File:      $RCSfile: d_typdef.hh,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:09 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */

#ifndef D_OOA_TYPEDEFS_HH
#define D_OOA_TYPEDEFS_HH

//
// FILE: D_typedefs.hh	AUTHOR: David E. Solomon	CREATION DATE: 9/11/92
//
// CONTENTS:
//
//		This file creates typedef's for the OOA domain.
//
// REMARKS:
//
//		These constants and typedefs should encompass the entire OOA data
//		domain or are needed across several classes; anything specific to a
//		particular class should NOT reside here but be encapsulated within
//		that class.
//

//
//
//  NOTE:  PLEASE PLEASE PLEASE do not change the number assigned to a
//    particular model type - if you do, it will not cause any functional
//    problems but will be a hassle for people to relearn what number belongs
//    to what type.
//

enum t_model_type
{
    NO_TYPE		= 0,

    DD_TYPE		= 1,
    SRM_TYPE		= 2,
    SCM_TYPE		= 3,
    SAM_TYPE		= 4,

    IM_TYPE		= 5,
    OCM_TYPE		= 6,
    OAM_TYPE		= 7,

    ISM_TYPE		= 8,
    ISTT_TYPE		= 9,
    ASM_TYPE		= 10,
    ASTT_TYPE		= 11,
    ISPT_TYPE		= 12,
    ASPT_TYPE		= 13,

    PM_TYPE		= 14,

    GREATEST_MODEL_TYPE	= 15
};


// e_class_type enumerates all the types of classes/objects that we define.
// We use the term "class" because this concept of identifying the
// type of "generic" object we are dealing with is independent of
// OOA objects; thus the switch in terminology. Furthermore, these can
// be used in any context where we need to distinguish any object/
// class type from another, but for now they are only used for
// Id's (hence the "short-sided" list; we will add the others later
// when we have time...ie - bucket-1 code/philosophy).
//
//
//  NOTE:  PLEASE PLEASE PLEASE do not change the number assigned to a
//    particular ID type - if you do, it will not cause any functional
//    problems but will be a hassle for people to relearn what number belongs
//    to what type.
//

enum t_class_type
{
  NO_CLASS_TYPE       = 0,
  DOMAIN_TYPE				=  1,

  DD_SRM_SCM_SAM_TYPE			= 10,
	SUBSYSTEM_TYPE			= 11,
	EXTERNAL_ENTITY_TYPE		= 12,
	EXT_ENTITY_EVENT_TYPE		= 13,
	EXT_ENTITY_DATA_ITEM_TYPE	= 14,
	EXT_ENTITY_EVENT_DATA_ITEM_TYPE	= 15,
	DATA_TYPE_TYPE			= 16,
	BRIDGE_TYPE			= 17,
	BRIDGE_PARM_TYPE		= 18,
	SYNCH_SERVICE_TYPE      = 19,
	SYNCH_SERVICE_PARM_TYPE  = 32,
	ENUMERATOR_TYPE     = 33,

  IM_OCM_OAM_TYPE			= 20,
	OBJECT_TYPE			= 21,
	ATTRIBUTE_TYPE			= 22,
	IMPORTED_OBJECT_TYPE		= 23,
	RELATIONSHIP_TYPE		= 24,
	OBJ_IN_REL_TYPE			= 25,
	ATTR_REF_IN_OBJECT_TYPE		= 26,
	EXT_ENTITY_IN_MODEL_TYPE	= 27,
	COMMUNICATION_PATH_TYPE		= 28,
	ACCESS_PATH_TYPE		= 29,
	TRANSFORMER_TYPE		= 30,
	TRANSFORMER_PARM_TYPE		= 31,
//	SYNCH_SERVICE_PARM_TYPE  = 32,   this value is used above!
//	ENUMERATOR_TYPE     = 33,        this value is used above!

  SM_SPT_PM_TYPE			= 40,
	STATE_TYPE			= 41,
	TRANSITION_TYPE			= 42,
	EVENT_TYPE			= 43,
	ACTION_TYPE			= 44,
	EVENT_DATA_ITEM_TYPE		= 45,
	SUPPLEMENTAL_DATA_TYPE		= 46,
	DERIVED_COMMUNICATION_PATH_TYPE	= 47,
	DERIVED_ACCESS_PATH_TYPE	= 48,

  INSTANCE_TYPE			= 100,
	OBJECT_INST_TYPE		= 101,
	ATTRIBUTE_INST_TYPE		= 102,
	RELATIONSHIP_INST_TYPE		= 103,
	RELATED_OBJECT_INST_PAIR_TYPE	= 104,
	EVENT_INST_TYPE			= 105,
	EVENT_DATA_ITEM_INST_TYPE	= 106,

	GRAPHICAL_ELEMENT_TYPE  = 1004,
  AUTOCONNECTORS			= 1005,

  GREATEST_ID_TYPE			= 1006
};



enum t_conditionality { UNCONDITIONAL, CONDITIONAL };

enum t_multiplicity { ONE, MANY };

enum t_workspace_type { LATEST_WS_TYPE, BROWSE_WS_TYPE, EDIT_WS_TYPE };


//  IMPORTANT: The t_core_data_type values must start with VOID being 0 and
//    be incremented by 1. If new types are added, don't forget to change
//    NUM_CORE_DATA_TYPES also.
//
//  IMPORTANT:  The values of these can NEVER NEVER NEVER change because it
//    will mess import of prior exported DB's up completely!!
//

const int NUM_CORE_DATA_TYPES = 13;

enum t_core_data_type
{
	VOID_DATATYPE			= 0,
	BOOLEAN_DATATYPE		= 1,
	INTEGER_DATATYPE		= 2,
	REAL_DATATYPE			= 3,
	STRING_DATATYPE			= 4,
	UNIQUE_ID_DATATYPE		= 5,
	CURRENT_STATE_DATATYPE		= 6,
	SAME_AS_BASE_DATATYPE		= 7,
	OBJECT_INST_REF_DATATYPE	= 8,
	OBJECT_INST_REF_SET_DATATYPE	= 9,
	EVENT_INST_DATATYPE		= 10,
	MAPPING_INST_DATATYPE		= 11,
	MAPPING_INST_REF_DATATYPE	= 12,


	//  The following core data types are not considered as part of the
	//    NUM_CORE_DATA_TYPES - they are considered only for purposes of
	//    the translator - NUM_CORE_DATA_TYPES is used by the action
	//    language parser inside the OOA tool to lookup legal operations...
	//
	FRAGMENT_DATATYPE 	 = 32,
	UNKNOWN_DATATYPE	 	 = 33,
    QMARK_DATATYPE       = 34,
    BRIDGE_OR_TRANSFORMER_INST_DATATYPE = 35,
    ENUMERATION_DATATYPE = 36,
	ENUMERATOR_DATATYPE = 37
};





//  IMPORTANT:  The t_user_data_type values must start with the
//    USER_DEFINED_USERDATATYPE - it indicates that the type is NOT predefined
//    by our tool.  Also, if new types are added, don't forget to change
//    NUM_USER_DATA_TYPES.
//
//  IMPORTANT:  The values of these can NEVER NEVER NEVER change because it
//    will mess import of prior exported DB's up completely!!
//

const int NUM_USER_DATA_TYPES = 5;

enum t_user_data_type
{
	USER_DEFINED_USERDATATYPE	= 0,
	DATE_USERDATATYPE		= 1,
	TIMESTAMP_USERDATATYPE		= 2,
	TIMER_INST_REF_USERDATATYPE	= 3,
	OLD_AND_OUT_OUT_USE___PROMPT_INST_REF_USERDATATYPE	= 4
};

// The following enum is used to determine which display mode
// model diagrams will be shown in.

enum e_diagram_display_mode
{
  DISPLAY_MODE_SM = 0,      // Shlaer-Mellor
  DISPLAY_MODE_UML          // UML
};

enum e_export_user_data_type { 
   EXPORT_ALL_UDT,
   EXPORT_NO_UDT,
   EXPORT_SOME_UDT
};


#define CANVAS_FONT_SIZE 12
#define CANVAS_FONT_SIZE_STRING "size:12"


#endif

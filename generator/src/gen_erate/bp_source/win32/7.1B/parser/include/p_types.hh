/*========================================================================
 *
 * File:      $RCSfile: p_types.hh,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:30 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#ifndef P_TYPES_HH
#define P_TYPES_HH

//---------------------------------------------------------------------
// Turn printing on or off.
//---------------------------------------------------------------------
#ifdef UI
#define UI_printf( a1 ) printf( a1 )
#define UI_printf1( a1, a2 ) printf( a1, a2 )
#define UI_printf2( a1, a2, a3 ) printf( a1, a2, a3 )
#define UI_printf3( a1, a2, a3, a4 ) printf( a1, a2, a3, a4 )
#else
#define UI_printf( a1 )
#define UI_printf1( a1, a2 )
#define UI_printf2( a1, a2, a3 )
#define UI_printf3( a1, a2, a3, a4 )
#endif

//---------------------------------------------------------------------
// symbol table constants
//---------------------------------------------------------------------
#define HashTableSize     8000  // number of symbols allowed in table
#define StringTableSize  64000  // bytes of string space in symbol table
#define GLOBAL               0

#ifndef __GNUC__
  #ifndef WIN32
typedef int bool;
  #endif
#endif
typedef void * voidPtr;
typedef void * persObjPtr;

enum Name_Space_e
{
  SYMBOL_ENTRY_INST_REF,
  SYMBOL_ENTRY_NON_INST_REF
};

//--------------------------------------------------------------------
// token types needed for symbol table
//--------------------------------------------------------------------

enum Reloc_Type_e
{
  // The following are hardcoded in a_gfinds.cc:
  OBJECT_KEY_LETTERS_FIELD = 1,
  RELATIONSHIP_NUMBER_FIELD = 2,
  EVENT_LABEL_FIELD = 3,
  SM_EVENT_DATA_ITEM_NAME_FIELD = 4,
  EE_EVENT_DATA_ITEM_NAME_FIELD = 5,
  EXTERNAL_ENTITY_KL_FIELD = 6,
  EVENT_MEANING_FIELD = 7,
  EVENT_MEANING_TICKED_FIELD = 8,
  ATTRIBUTE_FIELD = 9,
  RELATIONSHIP_PHRASE_FIELD = 10,
  TRANSFORMER_FIELD = 11,
  TRANSFORMER_PARM_FIELD = 12,
  BRIDGE_FIELD = 13,
  BRIDGE_PARM_FIELD = 14,
  // Not used: EXTERNAL_ENTITY_NAME_FIELD = 15
  SYNCH_SVC_FIELD = 16,
  SYNCH_SVC_PARM_FIELD = 17,
  ENUMERATION_FIELD = 18,
  ENUMERATOR_FIELD = 19,
  // Following are for the new parser's use
  UNKNOWN_RELOC_TYPE = 0,
  RELOC_IGNORE_DATA = 20,
  RELOC_NOT_YET_ADDED = 21
};

enum s_attrib_e
{
  SA_READWRITE,  // normal read/write symbol
  SA_READONLY,   // read-only in this scope
  SA_INVALID     // invalid in this scope
};

// Used for return value of get_right_obj_card (for ONE and MANY) and
// also for card paramater passed in by select
enum Obj_Card_e
{
  CARD_UNKNOWN,  // Undefined cardinality 
  CARD_ONE,      // Select ONE or cardinality of ONE
  CARD_ANY,      // Select ANY
  CARD_MANY      // Select MANY or cardinality of MANY
};

enum Assign_Val_e
{
  ASSIGN_LVAL,      // indicates variable is being written to
  ASSIGN_RVAL       // indicates variable is being read from
};

#endif

/*========================================================================
 *
 * File:      $RCSfile: p_ckudb.cc,v $
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
#include "p_ckudb.hh"
#include "myAST.h"

  //------------------------------------------------------------
  // Query functions
  //------------------------------------------------------------

// Determine if object keyletters is a valid object
bool P_checkUserDB::is_valid_obj_kl( AST *kl )
{
  return TRUE;
}

// Determine if object keyletters is a valid object
int P_checkUserDB::get_obj_kl_card( AST *kl )
{
  // Let's make sure the object key_letters exists.
  
//  Smart_ptr< mc_dbms_Collection< Object * > > object_coll =
 //   AL_Generic_finds::find_object_by_key_letters( m_current_domain_ptr,
 //                                                kl->getText() );
  
//  int card = object_coll->cardinality();
  
  return 1;
}

// Determine if transformer is valid for this object
bool P_checkUserDB::is_valid_transformer( AST *transformer,
                                          AST *obj_obj )
{
  return TRUE;
}

// Determine if event label is valid for this object
bool P_checkUserDB::is_valid_obj_event_label( AST *label,
                                             AST *obj_obj )
{
  return FALSE;
}

// Determine if there's an EE for the given keyletters
bool P_checkUserDB::is_valid_ee_kl( AST *kl )
{
  return FALSE;
}

// Determine if event label is valid for this object
bool P_checkUserDB::is_valid_ee_event_label( AST *label,
                                             AST *ee )
{
  return FALSE;
}

// Get the data type of the transformer data item
void P_checkUserDB::get_transformer_param_type( AST *data_item )
{
      data_item->setDatatype( UNKNOWN_DATATYPE );
}

// Get the data type of the bridge data item
void P_checkUserDB::get_bridge_param_type( AST *data_item )
{
      data_item->setDatatype( UNKNOWN_DATATYPE );
}

// Get the cardinality (Obj_Card_e) for the right object
Obj_Card_e P_checkUserDB::get_right_obj_card( AST *rel,
                                             AST *obj_left,
                                             AST *obj_right )
{
  return( CARD_ONE );
}

// Get the data type of the transformer return value
t_core_data_type P_checkUserDB::get_transformer_return_type( AST *data_item )
{
  return UNKNOWN_DATATYPE;
}

// Get the data type of the bridge return value
t_core_data_type P_checkUserDB::get_bridge_return_type( AST *data_item )
{
  return UNKNOWN_DATATYPE;
}

// Determine if attribute is referential
bool P_checkUserDB::is_referential_attr( AST *attr )
{
  return FALSE;
}

// Determine if attribute is an identifier
bool P_checkUserDB::is_identifier( AST *attr )
{
  return FALSE;
}

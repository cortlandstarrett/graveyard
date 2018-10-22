/*========================================================================
 *
 * File:      $RCSfile: p_ckbase.cc,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:22 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#include "p_ckbase.hh"
#include "myAST.h"

//------------------------------------------------------------
// Basic Interface Functions:
//------------------------------------------------------------

// Validate the object keyletters.
void P_checkBase::validate_obj_kl( AST *kl )
{
  kl->dumpNode("validate_obj_kl: ");
}

// Validate object attribute
int P_checkBase::validate_obj_attribute( AST *attr,
                                          AST *obj_obj,
                                          Assign_Val_e isLval,
										  const vchar* attribute_write_valid)
{
  attr->dumpNode("validate_obj_attribute: ");
  return 0;
}

// Validate the event label
void P_checkBase::validate_obj_event_label( AST *label,
                                            AST *to_obj  )
{
  label->dumpNode("validate_obj_event_label: ");
}

// Validate the event meaning
void P_checkBase::validate_sm_event_meaning( AST *meaning,
                                             AST *event )
{
  meaning->dumpNode("validate_sm_event_meaning: ");
}

// Validate the event meaning
void P_checkBase::validate_ee_event_meaning( AST *meaning,
                                             AST *event )
{
  meaning->dumpNode("validate_ee_event_meaning: ");
}

// Validate event data item name
void P_checkBase::validate_rcvd_evt_data_item_name( AST *name,
                                                    AST *event )
{
  name->dumpNode("validate_rcvd_evt_data_item_name: ");
}

// Validate state model event data items
void P_checkBase::validate_sm_event_data_items( AST *event,
                                                AST *data_items )
{
  if ( data_items != NULL )
    data_items->dumpNode("validate_sm_event_data_items: ");
}

// Validate external entity event data items
void P_checkBase::validate_ee_event_data_items( AST *event,
                                                AST *data_items )
{
  if ( data_items != NULL )
    data_items->dumpNode("validate_ee_event_data_items: ");
}

// Validate bridge data items
void P_checkBase::validate_bridge_data_items( AST *bridge,
                                              AST *data_items )
{
  if ( data_items != NULL )
    data_items->dumpNode("validate_bridge_data_items: ");
}

// Validate bridge data item
void P_checkBase::validate_bridge_data_item( AST *data_item,
                                             AST *bridge,
                                             Assign_Val_e isLval )
{
  if ( data_item != NULL )
    data_item->dumpNode("validate_bridge_data_item: ");
}

// Validate synch_svc data items
void P_checkBase::validate_synch_svc_data_items( AST *synch_svc,
                                                 AST *data_items )
{
  if ( data_items != NULL )
    data_items->dumpNode("validate_synch_svc_data_items: ");
}

// Validate synch_svc data item
void P_checkBase::validate_synch_svc_data_item( AST *data_item,
                                                AST *synch_svc,
                                                Assign_Val_e isLval )
{
  if ( data_item != NULL )
    data_item->dumpNode("validate_synch_svc_data_item: ");
}

// Validate transformer data items
void P_checkBase::validate_transformer_data_items( AST *transformer,
                                                   AST *data_items )
{
  if ( data_items != NULL )
    data_items->dumpNode("validate_transformer_data_items: ");
}

// Validate transformer data item
void P_checkBase::validate_transformer_data_item( AST *data_item,
                                                  AST *transformer,
                                                  Assign_Val_e isLval )
{
  if ( data_item != NULL )
    data_item->dumpNode("validate_transformer_data_item: ");
}

// Validate the relationship that ties together two objects. 
void P_checkBase::validate_rel_id( AST *id,
                                   AST *from,
                                   AST *to,
                                   AST *rel_phrase,
                                   Obj_Card_e card_expected,
                                   bool &manyFound )
{
  id->dumpNode("validate_rel_id: ");
}

// Validate the objects and relationship for a relate/unrelate.
void P_checkBase::validate_relate( AST *id,
                                   AST *from,
                                   AST *to,
                                   AST *rel_phrase )
{
  id->dumpNode("validate_relate: ");
}

// Validate the associative relationship that ties together three objects. 
void P_checkBase::validate_assoc_relate( AST *id,
                                         AST *from,
                                         AST *to,
                                         AST *assoc,
                                         AST *rel_phrase )
{
  id->dumpNode("validate_assoc_relate: ");
}

// Validate the external entity key letters
void P_checkBase::validate_ee_kl( AST *kl )
{
  kl->dumpNode("validate_ee_kl: ");
}

// Validate the external entity event data item name
void P_checkBase::validate_ee_event_data_item_name( AST *name,
                                                    AST *ee_event )
{
  name->dumpNode("validate_ee_event_data_item_name: ");
}

// Validate the bridge name
void P_checkBase::validate_bridge( AST *bridge,
                                   AST *ee )
{
  bridge->dumpNode("validate_bridge: ");
}

// Validate the synch_svc name
void P_checkBase::validate_synch_svc( AST *synch_svc )
{
  synch_svc->dumpNode("validate_synch_svc: ");
}

// Validate the transformer name
void P_checkBase::validate_transformer( AST *transformer,
                                        AST *obj,
                                        bool isInstanceBased )
{
  transformer->dumpNode("validate_transformer: ");
}

// Validate that object has an assigner state model
void P_checkBase::validate_obj_is_assigner( AST *kl )
{
  kl->dumpNode("validate_obj_is_assigner: ");
}

// Validate that object has a creation state
void  P_checkBase::validate_obj_has_creation_state( AST *kl )
{
  kl->dumpNode("validate_obj_has_creation_state: ");
}

// Validate that the event label can be received by the external entity
void P_checkBase::validate_ee_event_label( AST *label,
                                           AST *ee )
{
  label->dumpNode("validate_ee_event_label: ");
}

// Validate the event label for an assigner
void P_checkBase::validate_assigner_event_label( AST *label,
                                                 AST *to_obj )
{
  label->dumpNode("validate_assigner_event_label: ");
}

// Validate the creation event label
void P_checkBase::validate_creator_event_label( AST *label,
                                                AST *to_obj )
{
  label->dumpNode("validate_creator_event_label: ");
}

// Validate the enumerator for an enumeration
void P_checkBase::validate_enumerator( AST *enumeration,
                                   AST *enumerator)
{
  enumeration->dumpNode("validate_enumerator: ");
}

  //------------------------------------------------------------
  // Query functions
  //------------------------------------------------------------

// Determine if object keyletters is a valid object
bool P_checkBase::is_valid_obj_kl( AST *kl )
{
  return TRUE;
}

// Determine if transformer is valid for this object
bool P_checkBase::is_valid_transformer( AST *transformer,
                                        AST *obj_obj,
                                        bool isInstanceBased )
{
  return TRUE;
}

// Determine if event label is valid for this object
bool P_checkBase::is_valid_obj_event_label( AST *label,
                                            AST *obj_obj )
{
  return FALSE;
}

// Determine if there's an EE for the given keyletters
bool P_checkBase::is_valid_ee_kl( AST *kl )
{
  return FALSE;
}

// Determine if bridge is valid for this external entity
bool P_checkBase::is_valid_ee_bridge( AST *bridge,
                                      AST *ee_obj )
{
  return TRUE;
}

// Determine if event label is valid for this object
bool P_checkBase::is_valid_ee_event_label( AST *label,
                                           AST *ee )
{
  return FALSE;
}

// Get the data type of the bridge return value
t_core_data_type P_checkBase::get_bridge_return_type( AST *data_item )
{
  return UNKNOWN_DATATYPE;
}

// Get the data type of the synch_svc return value
t_core_data_type P_checkBase::get_synch_svc_return_type( AST *data_item )
{
  return UNKNOWN_DATATYPE;
}

// Get the data type of the transformer return value
t_core_data_type P_checkBase::get_transformer_return_type( AST *data_item )
{
  return UNKNOWN_DATATYPE;
}

// Get the cardinality (Obj_Card_e) for the right object
Obj_Card_e P_checkBase::get_right_obj_card( AST *rel,
                                            AST *obj_left,
                                            AST *obj_right )
{
  return( CARD_ONE );
}

// Determine if attribute is referential
bool P_checkBase::is_referential_attr( AST *attr )
{
  return FALSE;
}

// Determine if attribute is an identifier
bool P_checkBase::is_identifier( AST *attr )
{
  return FALSE;
}

// Get cardinality of object with given object keyletters
int P_checkBase:: get_obj_kl_card( AST *kl )
{
  return 1;
}

persObjPtr P_checkBase::get_enum_data_type_ptr( AST *p_enum )
{
  return 0;
}

void P_checkBase::verify_return_type( t_core_data_type p_dt, 
					  persObjPtr p_return_type_reqd,
					  AST *p_e, const vchar* p_descr )
{
}

void P_checkBase::verify_return_void( persObjPtr p_return_type_reqd,
					  AST *p_e, const vchar* p_descr )
{
}


/*========================================================================
 *
 * File:      $RCSfile: p_check.cc,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:20 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#include "p_check.hh"

#include "myAST.h"
#include "p_ckbase.hh"
#include "d_typdef.hh"
#include "p_error.hh"
#include "vchar.h"

  //------------------------------------------------------------
  // Internal function:
  //------------------------------------------------------------

bool P_check::check_ast( AST *ast,
                         int tok_should_be,
                         int line_no )
{
  bool ans = TRUE;
  if (ast != NULL)
    {
      int tok_was = ast->getType();
      if (tok_was != tok_should_be)
        {
          AL_PARSE_ERR4( ast, AL_GETMSG(ERR,350,4),
                         line_no, vcharScribeASCII( __FILE__ ),
                         tok_was, tok_should_be )
          ans = FALSE;
        }
    }
  else
    ans = FALSE;
  return ans;
}

bool P_check::check_ast( AST *ast,
                         int tok_should_be1,
                         int tok_should_be2,
                         int line_no )
{
  bool ans = TRUE;
  if (ast != NULL)
    {
      int tok_was = ast->getType();
      if ( (tok_was != tok_should_be1) &&
           (tok_was != tok_should_be2) )
        {
          AL_PARSE_ERR5( ast, AL_GETMSG(ERR,351,5),
                         line_no, vcharScribeASCII( __FILE__ ),
                         tok_was, tok_should_be1,
                         tok_should_be2 )
          ans = FALSE;
        }
    }
  else
    ans = FALSE;
  return ans;
}

//------------------------------------------------------------
// Basic Interface Functions:
//------------------------------------------------------------

// Validate the object keyletters.
void P_check::validate_obj_kl( AST *kl )
{
  CHECK_AST(kl, TOK_KL_OBJECT)

  kl->setObjPtr( RESET_OBJPTR );
  kl->markReloc( OBJECT_KEY_LETTERS_FIELD );

  ck->validate_obj_kl( kl );

  END_CHECK;
}

// Validate object attribute
int P_check::validate_obj_attribute ( AST *attribute,
                                       AST *obj_obj,
                                       Assign_Val_e isLval,
									   const vchar* attribute_write_valid)
{
  int ret_val = 0;

  CHECK_AST(attribute, TOK_OBJ_ATTR);
  attribute->setObjPtr( RESET_OBJPTR );
  attribute->markReloc( ATTRIBUTE_FIELD );
  attribute->setDatatype( UNKNOWN_DATATYPE );

  CHECK_AST_OBJ(obj_obj, TOK_INST_REF_VAR);
  ret_val = ck->validate_obj_attribute( attribute, obj_obj, isLval, attribute_write_valid );

  END_CHECK;

  return ret_val;
}

// Validate the event label
void P_check::validate_obj_event_label( AST *label,
                                        AST *to_obj )
{ 
  CHECK_AST(label, TOK_EVENT_LABEL);
  label->setObjPtr( RESET_OBJPTR );
  label->markReloc( EVENT_LABEL_FIELD );

  CHECK_AST_OBJ(to_obj, TOK_INST_REF_VAR);
  ck->validate_obj_event_label( label, to_obj );

  END_CHECK;
}

// Validate the state model event meaning
void P_check::validate_sm_event_meaning( AST *p_meaning,
                                         AST *p_event )
{
  const vchar *l_meaning  = p_meaning->getVcharText();
  const vchar &first_char = *l_meaning;
  vchar tic = vcharFromASCII('\'');

  CHECK_AST(p_meaning, TOK_PHRASE);
  p_meaning->setObjPtr( RESET_OBJPTR );

  if ( first_char == tic )
    p_meaning->markReloc(EVENT_MEANING_TICKED_FIELD);
  else
    p_meaning->markReloc(EVENT_MEANING_FIELD);

  CHECK_AST_OBJ(p_event, TOK_EVENT_LABEL);
  ck->validate_sm_event_meaning( p_meaning, p_event );

  END_CHECK;
}

// Validate the external entity event meaning
void P_check::validate_ee_event_meaning( AST *p_meaning,
                                         AST *p_event )
{
  const vchar *l_meaning = p_meaning->getVcharText();
  const vchar &first_char = *l_meaning;
  vchar tic = vcharFromASCII('\'');

  CHECK_AST(p_meaning, TOK_PHRASE);
  p_meaning->setObjPtr( RESET_OBJPTR );

  if ( first_char == tic )
    p_meaning->markReloc(EVENT_MEANING_TICKED_FIELD);
  else
    p_meaning->markReloc(EVENT_MEANING_FIELD);

  CHECK_AST_OBJ(p_event, TOK_EVENT_LABEL);
  ck->validate_ee_event_meaning( p_meaning, p_event );

  END_CHECK;
}

// Validate event data item name
void P_check::validate_rcvd_evt_data_item_name( AST *name,
                                                AST *event)
{
  CHECK_AST(name, TOK_SUPP_DATA_NAME);
  name->setObjPtr( RESET_OBJPTR );
  name->markReloc(SM_EVENT_DATA_ITEM_NAME_FIELD);
  
  CHECK_AST_OBJ(event, TOK_RCVD_EVT);
  ck->validate_rcvd_evt_data_item_name( name, event );
  
  END_CHECK;
}

// Validate state model event data items
void P_check::validate_sm_event_data_items( AST *event,
                                            AST *data_items)
{
  CHECK_AST_OBJ(event, TOK_EVENT_LABEL);

  if ( data_items != NULL )
    {
      AST * data_item_cursor = data_items;
      while ( data_item_cursor != NULL )
        {
          data_item_cursor->markReloc( SM_EVENT_DATA_ITEM_NAME_FIELD );
          data_item_cursor = (AST *) data_item_cursor->right();
        }
    }

  // data_items is checked in the called validate function
  ck->validate_sm_event_data_items( event, data_items );

  END_CHECK;
}

// Validate external entity event data items
void P_check::validate_ee_event_data_items( AST *event,
                                            AST *data_items)
{
  CHECK_AST_OBJ(event, TOK_EVENT_LABEL);

  if ( data_items != NULL )
    {
      AST * data_item_cursor = data_items;
      while ( data_item_cursor != NULL )
        {
          data_item_cursor->markReloc( EE_EVENT_DATA_ITEM_NAME_FIELD );
          data_item_cursor = (AST *) data_item_cursor->right();
        }
    }
  
  // data_items is checked in the called validate function
  ck->validate_ee_event_data_items( event, data_items );

  END_CHECK;
}

// Validate bridge event data items
void P_check::validate_bridge_data_items( AST *bridge,
                                          AST *data_items)
{
  CHECK_AST_OBJ(bridge, TOK_FUNCTION_NAME);

  if ( data_items != NULL )
    {
      AST * data_item_cursor = data_items;
      while ( data_item_cursor != NULL )
        {
          data_item_cursor->markReloc( BRIDGE_PARM_FIELD );
          data_item_cursor = (AST *) data_item_cursor->right();
        }
    }

  // data_items is checked in the called validate function
  ck->validate_bridge_data_items( bridge, data_items );

  END_CHECK;
}

// Validate bridge data item
void P_check::validate_bridge_data_item( AST *data_item,
                                         AST *bridge,
                                         Assign_Val_e isLval )
{
  CHECK_AST(data_item, TOK_DATA_ITEM_NAME);
  CHECK_AST_OBJ(bridge, TOK_BRIDGE_PARAM);

  data_item->setObjPtr( RESET_OBJPTR );
  data_item->markReloc(BRIDGE_PARM_FIELD);

  // data_item is checked in the called validate function
  ck->validate_bridge_data_item( data_item, bridge, isLval );

  END_CHECK;
}

// Validate synch_svc data items
void P_check::validate_synch_svc_data_items( AST *synch_svc,
                                             AST *data_items)
{
  CHECK_AST_OBJ(synch_svc, TOK_FUNCTION_NAME);

  if ( data_items != NULL )
    {
      AST * data_item_cursor = data_items;
      while ( data_item_cursor != NULL )
        {
          data_item_cursor->markReloc( SYNCH_SVC_PARM_FIELD );
          data_item_cursor = (AST *) data_item_cursor->right();
        }
    }

  // data_items is checked in the called validate function
  ck->validate_synch_svc_data_items( synch_svc, data_items );

  END_CHECK;
}

// Validate synch_svc data item
void P_check::validate_synch_svc_data_item( AST *data_item,
                                            AST *synch_svc,
                                            Assign_Val_e isLval )
{
  CHECK_AST(data_item, TOK_DATA_ITEM_NAME);
  CHECK_AST_OBJ(synch_svc, TOK_SYNCH_SVC_PARAM);

  data_item->setObjPtr( RESET_OBJPTR );
  data_item->markReloc(SYNCH_SVC_PARM_FIELD);

  // data_item is checked in the called validate function
  ck->validate_synch_svc_data_item( data_item, synch_svc, isLval );

  END_CHECK;
}

// Validate transformer data items
void P_check::validate_transformer_data_items( AST *transformer,
                                               AST *data_items)
{
  CHECK_AST_OBJ(transformer, TOK_FUNCTION_NAME);

  if ( data_items != NULL )
    {
      AST * data_item_cursor = data_items;
      while ( data_item_cursor != NULL )
        {
          data_item_cursor->markReloc( TRANSFORMER_PARM_FIELD );
          data_item_cursor = (AST *) data_item_cursor->right();
        }
    }

  // data_items is checked in the called validate function
  ck->validate_transformer_data_items( transformer, data_items );

  END_CHECK;
}

// Validate transformer data item
void P_check::validate_transformer_data_item( AST *data_item,
                                              AST *transformer,
                                              Assign_Val_e isLval )
{
  CHECK_AST(data_item, TOK_DATA_ITEM_NAME);
  CHECK_AST_OBJ(transformer, TOK_TRANSFORMER_PARAM);

  data_item->setObjPtr( RESET_OBJPTR );
  data_item->markReloc(TRANSFORMER_PARM_FIELD);

  // data_item is checked in the called validate function
  ck->validate_transformer_data_item( data_item, transformer, isLval );

  END_CHECK;
}

// Validate the relationship that ties together two objects. 
void P_check::validate_rel_id( AST *id,
                               AST *from_obj,
                               AST *to_obj,
                               AST *rel_phrase,
                               Obj_Card_e card_expected,
                               bool &manyFound )
{
  CHECK_AST(id, TOK_RELID);
  id->setObjPtr( RESET_OBJPTR );
  id->markReloc(RELATIONSHIP_NUMBER_FIELD);

  if ( rel_phrase != NULL )
    {
      CHECK_AST(rel_phrase, TOK_PHRASE);
      rel_phrase->setObjPtr( RESET_OBJPTR );
      rel_phrase->markReloc(RELATIONSHIP_PHRASE_FIELD);
    }
  
  CHECK_AST_OBJ_ALT(from_obj, TOK_INST_REF_VAR, TOK_KL_OBJECT);
  CHECK_AST_OBJ(to_obj, TOK_KL_OBJECT);

  ck->validate_rel_id( id, from_obj, to_obj, rel_phrase, card_expected, manyFound );
  
  END_CHECK;
}

// Validate the relationship that ties together two objects. 
void P_check::validate_relate ( AST *id,
                                AST *from_obj,
                                AST *to_obj,
                                AST *rel_phrase )
{
  CHECK_AST(id, TOK_RELID);
  id->setObjPtr( RESET_OBJPTR );
  id->markReloc(RELATIONSHIP_NUMBER_FIELD);

  if ( rel_phrase != NULL )
    {
      CHECK_AST(rel_phrase, TOK_PHRASE);
      rel_phrase->setObjPtr( RESET_OBJPTR );
      rel_phrase->markReloc(RELATIONSHIP_PHRASE_FIELD);
    }
  
  CHECK_AST_OBJ(from_obj, TOK_INST_REF_VAR);
  CHECK_AST_OBJ(to_obj, TOK_INST_REF_VAR);

  ck->validate_relate( id, from_obj, to_obj, rel_phrase );
  
  END_CHECK;
}

// Validate the associative relationship that ties together three objects. 
void P_check::validate_assoc_relate( AST *id,
                                     AST *from,
                                     AST *to,
                                     AST *assoc,
                                     AST *rel_phrase )
{
  CHECK_AST(id, TOK_RELID);
  id->setObjPtr( RESET_OBJPTR );
  id->markReloc( RELATIONSHIP_NUMBER_FIELD );

  if ( rel_phrase != NULL )
    {
      CHECK_AST(rel_phrase, TOK_PHRASE);
      rel_phrase->setObjPtr( RESET_OBJPTR );
      rel_phrase->markReloc(RELATIONSHIP_PHRASE_FIELD);
    }
  
  CHECK_AST_OBJ(from, TOK_INST_REF_VAR);
  CHECK_AST_OBJ(to, TOK_INST_REF_VAR);
  CHECK_AST_OBJ(assoc, TOK_INST_REF_VAR);

  ck->validate_assoc_relate( id, from, to, assoc, rel_phrase );
  
  END_CHECK;
}

// Validate the external entity key letters
void P_check::validate_ee_kl (AST *kl)
{
  CHECK_AST(kl, TOK_KL_EXTERNAL_ENTITY);
  
  kl->setObjPtr( RESET_OBJPTR );
  kl->markReloc(EXTERNAL_ENTITY_KL_FIELD);
  
  ck->validate_ee_kl( kl );
  
  END_CHECK;
}

// Validate the bridge name
void P_check::validate_bridge( AST *bridge,
                               AST *ee)
{
  CHECK_AST(bridge, TOK_FUNCTION_NAME);
  bridge->setObjPtr( RESET_OBJPTR );
  bridge->markReloc(BRIDGE_FIELD);
  
  CHECK_AST_OBJ(ee, TOK_KL_EXTERNAL_ENTITY);
  ck->validate_bridge( bridge, ee );
  
  END_CHECK;
}

// Validate the synch_svc name
void P_check::validate_synch_svc( AST *synch_svc )
{
  CHECK_AST(synch_svc, TOK_FUNCTION_NAME);
  synch_svc->setObjPtr( RESET_OBJPTR );
  synch_svc->markReloc(SYNCH_SVC_FIELD);

  ck->validate_synch_svc( synch_svc );
  
  END_CHECK;
}

// Validate the transformer name
void P_check::validate_transformer( AST *transformer,
                                    AST *obj_obj,
                                    bool isInstanceBased )
{
  CHECK_AST(transformer, TOK_FUNCTION_NAME);
  transformer->setObjPtr( RESET_OBJPTR );
  transformer->markReloc(TRANSFORMER_FIELD);
  CHECK_AST_OBJ_ALT(obj_obj, TOK_KL_OBJECT, TOK_INST_REF_VAR);

  ck->validate_transformer( transformer, obj_obj, isInstanceBased );
  
  END_CHECK;
}

// Validate that object has an assigner state model
void P_check::validate_obj_is_assigner( AST *kl )
{
  CHECK_AST_OBJ( kl, TOK_KL_OBJECT_ASSIGNER );

  // Probably want to return assigner SM somehow
  ck->validate_obj_is_assigner( kl );

  END_CHECK;
}

// Validate that object has a creation state
void P_check::validate_obj_has_creation_state( AST *kl )
{
  CHECK_AST_OBJ( kl, TOK_KL_OBJECT_CREATOR );

  ck->validate_obj_has_creation_state( kl );

  END_CHECK;
}

// Validate that the event label can be recieved by the external entity
void P_check::validate_ee_event_label( AST *label,
                                       AST *ee )
{
  CHECK_AST(label, TOK_EVENT_LABEL);
  label->setObjPtr( RESET_OBJPTR );
  label->markReloc(EVENT_LABEL_FIELD);
  CHECK_AST_OBJ(ee, TOK_KL_EXTERNAL_ENTITY);

  ck->validate_ee_event_label( label, ee );
  
  END_CHECK;
}

// Validate the event label for an assigner
void P_check::validate_assigner_event_label( AST *label,
                                             AST *to_obj )
{
  CHECK_AST( label, TOK_EVENT_LABEL );
  label->setObjPtr( RESET_OBJPTR );
  label->markReloc( EVENT_LABEL_FIELD );
  CHECK_AST_OBJ( to_obj, TOK_KL_OBJECT_ASSIGNER );

  ck->validate_assigner_event_label( label, to_obj );
  
  END_CHECK;
}

// Validate the event label for a creation event
void P_check::validate_creator_event_label( AST *label,
                                            AST *to_obj )
{
  CHECK_AST(label, TOK_EVENT_LABEL);
  label->setObjPtr( RESET_OBJPTR );
  label->markReloc(EVENT_LABEL_FIELD);
  CHECK_AST_OBJ(to_obj, TOK_KL_OBJECT_CREATOR);

  ck->validate_creator_event_label( label, to_obj );
  
  END_CHECK;
}

// Validate the enumerator for an enumeration
void P_check::validate_enumerator( AST *enumeration,
                                   AST *enumerator)
{
  CHECK_AST(enumeration, TOK_ENUMERATION);
  enumeration->setObjPtr( RESET_OBJPTR );
  enumeration->markReloc(ENUMERATOR_FIELD);
  CHECK_AST(enumerator, TOK_ENUMERATOR);
  enumerator->setObjPtr( RESET_OBJPTR );
  enumerator->markReloc(ENUMERATION_FIELD);

  ck->validate_enumerator( enumeration, enumerator );
  
  END_CHECK;
}

  //------------------------------------------------------------
  // Query functions
  //------------------------------------------------------------

// Determine if object keyletters is a valid object
bool P_check::is_valid_obj_kl( AST *kl )
{
  bool answer = FALSE;
  
  CHECK_AST_ALT(kl, TOK_KL_OBJECT, TOK_ID);

  kl->setObjPtr(RESET_OBJPTR);
  kl->markReloc(OBJECT_KEY_LETTERS_FIELD);

  answer = ck->is_valid_obj_kl( kl );
  
  END_CHECK;
  return answer;
}

// Determine if transformer is valid for this object
bool P_check::is_valid_transformer( AST *transformer,
                                    AST *obj_obj,
                                    bool isInstanceBased )
{
  bool answer = FALSE;

  CHECK_AST(transformer, TOK_FUNCTION_NAME);
  transformer->setObjPtr( RESET_OBJPTR );
  transformer->markReloc(TRANSFORMER_FIELD);

  CHECK_AST_OBJ_ALT(obj_obj, TOK_KL_OBJECT, TOK_INST_REF_VAR);
  answer = ck->is_valid_transformer( transformer, obj_obj, isInstanceBased );
  
  END_CHECK;
  return answer;
}

// Determine if keyletters is a valid external entity
bool P_check::is_valid_ee_kl( AST *kl )
{
  bool answer = FALSE;
  
  CHECK_AST(kl, TOK_KL_EXTERNAL_ENTITY);
  kl->setObjPtr( RESET_OBJPTR );
  kl->markReloc(EXTERNAL_ENTITY_KL_FIELD);
  
  answer = ck->is_valid_ee_kl( kl );
  
  END_CHECK;
  return answer;
}

// Determine if bridge is valid for this external entity
bool P_check::is_valid_ee_bridge( AST *bridge,
                                  AST *ee_kl )
{
  bool answer = FALSE;
  
  CHECK_AST_OBJ(ee_kl, TOK_KL_EXTERNAL_ENTITY);
  CHECK_AST(bridge, TOK_FUNCTION_NAME);
  bridge->setObjPtr( RESET_OBJPTR );
  bridge->markReloc(BRIDGE_FIELD);
  
  answer = ck->is_valid_ee_bridge( bridge, ee_kl );
  
  END_CHECK;
  return answer;
}

// Get the cardinality (Obj_Card_e) for the right object
Obj_Card_e P_check::get_right_obj_card( AST *rel,
                                        AST *obj_left,
                                        AST *obj_right )
{ 
  Obj_Card_e card = CARD_UNKNOWN;

  rel->dumpNode ("p_check - get_right_obj_card: ");
  obj_left->dumpNode ("p_check - get_right_obj_card: ");
  obj_right->dumpNode ("p_check - get_right_obj_card: ");

  CHECK_AST_OBJ(rel, TOK_RELID);
  CHECK_AST_OBJ_ALT(obj_left, TOK_INST_REF_VAR, TOK_KL_OBJECT);
  CHECK_AST_OBJ(obj_right,TOK_KL_OBJECT);
  
  card = ck->get_right_obj_card( rel, obj_left, obj_right );
  
  END_CHECK;
  return card;
}

// Get the return data type of the bridge
t_core_data_type P_check::get_bridge_return_type( AST *bridge )
{
  t_core_data_type datatype = UNKNOWN_DATATYPE;

  CHECK_AST_OBJ(bridge, TOK_FUNCTION_NAME);

  datatype = ck->get_bridge_return_type(bridge);

  END_CHECK;
  return datatype;
}

// Get the return data type of the synch_svc
t_core_data_type P_check::get_synch_svc_return_type( AST *synch_svc )
{
  t_core_data_type datatype = UNKNOWN_DATATYPE;
  
  CHECK_AST_OBJ(synch_svc, TOK_FUNCTION_NAME);

  datatype = ck->get_synch_svc_return_type(synch_svc);

  END_CHECK;
  return datatype;
}

// Get the return data type of the transformer
t_core_data_type P_check::get_transformer_return_type( AST *transform )
{
  t_core_data_type datatype = UNKNOWN_DATATYPE;
  
  CHECK_AST_OBJ(transform, TOK_FUNCTION_NAME);

  datatype = ck->get_transformer_return_type(transform);

  END_CHECK;
  return datatype;
}

// Determine if attribute is referential
bool P_check::is_referential_attr( AST *attr )
{
  bool answer = FALSE;

  CHECK_AST_OBJ(attr, TOK_OBJ_ATTR);

  answer = ck->is_referential_attr(attr);

  END_CHECK;
  return answer;
}

// Determine if attribute is an identifier
bool P_check::is_identifier( AST *attr )
{
  bool answer = FALSE;
  
  CHECK_AST_OBJ(attr, TOK_OBJ_ATTR);

  answer = ck->is_identifier(attr);

  END_CHECK;
  return answer;
}

// Determine if attribute is an identifier
persObjPtr P_check::get_enum_data_type_ptr( AST *p_enum )
{
  persObjPtr answer = 0;

  answer = ck->get_enum_data_type_ptr(p_enum);

  return answer;
}

void P_check::verify_return_type( t_core_data_type p_dt,
								  persObjPtr p_return_type_reqd,
								  AST *p_e, const vchar* p_descr )
{
	ck->verify_return_type( p_dt, p_return_type_reqd, p_e, p_descr );
}

void P_check::verify_return_void( persObjPtr p_return_type_reqd,
								  AST *p_e, const vchar* p_descr )
{
	ck->verify_return_void( p_return_type_reqd, p_e, p_descr );
}

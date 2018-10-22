/*========================================================================
 *
 * File:      $RCSfile: p_ckbase.hh,v $
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
#ifndef P_CKBASE_HH
#define P_CKBASE_HH

#include "p_types.hh"
#include "p_msgs.hh"
#include "d_typdef.hh"
#include <vchar.h>

class AST;
class P_error;

class P_checkBase
{
public:
  // Constructor
  P_checkBase(P_error *p_er):
    er(p_er)
    {}

  // Destructor
  virtual ~P_checkBase()
    {}

  //------------------------------------------------------------
  // Basic Interface Functions:
  //------------------------------------------------------------

  // Validate the object keyletters.
  virtual void validate_obj_kl( AST *kl );
  // The parameter kl is the string containing the key letters.
  // It returns a pointer (of type O_OBJ*).

  // Validate object attribute
  virtual int validate_obj_attribute( AST *attr,
                              AST *obj_obj,
                              Assign_Val_e isLval,
							  const vchar* valid_attribute_write);
  // Parameter attr is an AST containing the string with the
  // name of the object attribute.  The parameter obj_obj is a
  // pointer to the object which should have the attribute in it.
  // Parameter isLval indicates whether the attribute is being
  // assigned to or not.
  // Parameter valid_attribute_write is the attribute that 
  // can be written in the process spec for a derived attribute
  // Returns TRUE if the attribute written is the derived attribute
  // for the derived attribute.  FALSE otherwise.

  // Validate the event label
  virtual void validate_obj_event_label( AST *label,
                                         AST *to_obj );
  // Parameter label is an AST containing a string of event
  // label (which is defined in
  // OOA as the keyletters followed by the event number).  Parameter
  // to_obj is an AST containing the destination object (of type O_OBJ)
  // and the text given for the local variable of that object type.
  // Returns a pointer to the event (of type SM_EVT).

  // Validate the event label for an assigner
  virtual void validate_assigner_event_label( AST *label,
                                              AST *to_obj );
  // Parameter label is an AST containing a string of event label
  // (which is defined in
  // Parameter label is an AST containing the string with the event
  // label.  Parameter to_obj is an AST containing a valid object
  // pointer (of type ???) to the assigner object and the kl text.
  // Returns a pointer to the event (of type SM_EVT) in the label AST.
  
  // Validate the event label as a creation event
  virtual void validate_creator_event_label( AST *label,
                                             AST *to_obj );
  // Parameter label is an AST containing a string of
  // event label (which is defined in
  // OOA as the keyletters followed by the event number).  Parameter
  // to_obj is an AST containing the destination object (of type O_OBJ)
  // and the kl text.
  // Returns a pointer to the event (of type SM_EVT) in the label AST.

  // Validate the event meaning for a state model (not an EE)
  virtual void validate_sm_event_meaning( AST *meaning,
                                 AST *event);
  // Parameter meaning is an AST containing the unquoted
  // phrase associated with an
  // event, called the event meaning.  Parameter event is the event
  // (of type SM_EVT) with which the meaning should be checked.
  // The parameter event is returned.

  // Validate the event meaning for and external entity
  virtual void validate_ee_event_meaning( AST *meaning,
                                 AST *event);
  // Parameter meaning is an AST containing the unquoted
  // phrase associated with an external entity event
  // event, called the event meaning.  Parameter event is the event
  // (of type S_EEEVT) with which the meaning should be checked.
  // The parameter event is returned.

  // Validate event data item name by a pointer to the event
  virtual void validate_rcvd_evt_data_item_name( AST *name,
                                                AST *event);
  // The parameter name is an AST containing the string with the event
  // data item name.  The parameter event is a pointer to the
  // event (of type SM_EVT).
  // This returns a pointer to the data item object (of time SM_EVTDI)
  // in the AST.

  // Validate state model event data items
  virtual void validate_sm_event_data_items( AST *event,
                                             AST *data_items);
  // The parameter event is an AST with a pointer to the
  // event (of type SM_EVT) and the text of the event label.
  // The parameter data_items is an AST tree containing all of the data
  // item names in a sibling structure (traverse with data_items->right()).
  // All of the data item name ASTs will be given an objPtr and a dataType.

  // Validate external entity event data items
  virtual void validate_ee_event_data_items( AST *event,
                                             AST *data_items);
  // The parameter event is an AST with a pointer to the external entity
  // event (of type S_EEEVT) and the text of the event label.
  // The parameter data_items is an AST tree containing all of the data
  // item names in a sibling structure (traverse with data_items->right()).
  // All of the data item name ASTs will be given an objPtr and a dataType.

  // Validate bridge data items
  virtual void validate_bridge_data_items( AST *bridge,
                                           AST *data_items);
  // The parameter bridge is an AST with a pointer to the bridge object.
  // The parameter data_items is an AST tree containing all of the data
  // item names in a sibling structure (traverse with data_items->right()).
  // All of the data item name ASTs will be given an objPtr and a dataType.

  // Validate bridge data item
  virtual void validate_bridge_data_item( AST *data_item,
                                          AST *bridge,
                                          Assign_Val_e isLval );
  // The parameter data_item is an AST for the data item to be validated.
  // The parameter bridge is an AST with a pointer to the bridge object.

  // Validate synch_svc data data items
  virtual void validate_synch_svc_data_items( AST *synch_svc,
                                              AST *data_items);
  // The parameter synch_svc is an AST with a pointer to the synch_svc object.
  // The parameter data_items is an AST tree containing all of the data
  // item names in a sibling structure (traverse with data_items->right()).
  // All of the data item name ASTs will be given an objPtr and a dataType.

  // Validate synch_svc data item
  virtual void validate_synch_svc_data_item( AST *data_item,
                                             AST *synch_svc,
                                             Assign_Val_e isLval );
  // The parameter data_item is an AST for the data item to be validated.
  // The parameter synch_svc is an AST with a pointer to the
  // synch_svc object.

  // Validate transformer data data items
  virtual void validate_transformer_data_items( AST *transformer,
                                                AST *data_items);
  // The parameter transformer is an AST with a pointer to the transformer object.
  // The parameter data_items is an AST tree containing all of the data
  // item names in a sibling structure (traverse with data_items->right()).
  // All of the data item name ASTs will be given an objPtr and a dataType.

  // Validate transformer data item
  virtual void validate_transformer_data_item( AST *data_item,
                                               AST *transformer,
                                               Assign_Val_e isLval );
  // The parameter data_item is an AST for the data item to be validated.
  // The parameter transformer is an AST with a pointer to the
  // transformer object.

  // Validate the relationship that ties together two objects. 
  virtual void validate_rel_id( AST *id,
                                AST *from_obj,
                                AST *to_obj, 
                                AST *rel_phrase,
                                Obj_Card_e card_expected,
                                bool &manyFound );
  // The parameter id is an AST holding the string  which is the 
  // relationship number - without the leading "r".
  // The parameter from_obj is an AST with a pointer (of type O_OBJ *)
  // to the first object and a pointer to the text of either the instance
  // variable or the object keyletters.  The parameter to_obj is an AST with
  // a pointer (of type O_OBJ *) to the second object and a pointer to the
  // text of object keyletters.  The parameter rel_phrase is an AST with
  // a pointer to the relationship phrase found in the parse.  Returns a
  // pointer to the relationship (of type R_REL).

  // Validate the objects and relationship for a RELATE/UNRELATE statement 
  virtual void validate_relate( AST *id,
                                AST *from_obj,
                                AST *to_obj,
                                AST *rel_phrase );
  // The parameter id is an AST holding the string  which is the 
  // relationship number - without the leading "r".
  // The parameter from_obj is an AST with a pointer (of type O_OBJ *)
  // to the first object and a pointer to the text of either the instance
  // variable or the object keyletters.  The parameter to_obj is an AST with
  // a pointer (of type O_OBJ *) to the second object and a pointer to the
  // text of object keyletters.  The parameter rel_phrase is an AST with
  // a pointer to the relationship phrase found in the parse.  Returns a
  // pointer to the relationship (of type R_REL).

  // Validate the associative relationship that ties together three objects. 
  virtual void validate_assoc_relate( AST *id,
                                      AST *from,
                                      AST *to,
                                      AST *assoc,
                                      AST *rel_phrase );
  // The parameter id is an AST holding the string  which is the 
  // relationship number - without the leading "r".
  // The parameter from is an AST with a pointer (of type O_OBJ *)
  // to the first object.  The parameter to is an AST with a pointer (of
  // type O_OBJ *) to the second object.
  // The parameter assoc is an AST with a pointer (of type O_OBJ *) 
  // to the associative object.
  // Returns a pointer to the relationship (of type R_REL) in the id AST.
  // The parameter assoc_obj is a pointer to the associative object.
  // The parameter rel_phrase is an AST with
  // a pointer to the relationship phrase found in the parse.  Returns a
  // pointer to the relationship (of type R_REL).

  // Validate the external entity key letters
  virtual void validate_ee_kl (AST *kl);
  // The parameter kl is an AST containing the string with the key
  // leeters.
  // Returns pointer to the external entity (of type S_EE).

  // Validate the external entity event data item name
  virtual void validate_ee_event_data_item_name( AST *name,
                                                 AST *ee_event);
  // The parameter name is an AST containing the string with the event
  // data item name.  The parameter ee_event is an AST with a pointer to the
  // event (of type S_EEEVT) and the text of the event label.
  // This returns a pointer to the data item object (of time S_EEEDI) in the AST.

  // Validate the bridge name
  virtual void validate_bridge( AST *bridge,
                                AST *ee);
  // The parameter bridge is an AST containing the string with the
  // bridge name.  The parameter ee is an AST with pointer to the enternal
  // entity object (of type S_EE) and the EE keyletters.
  // Returns a pointer to the bridge object (of type S_BRG).

  // Validate the synch_svc name
  virtual void validate_synch_svc( AST *synch_svc );
  // The parameter synch_svc is an AST containing the string with the
  // synch_svc name.
  // Returns a pointer to the synch_svc object (of type S_SSVC) in the AST.

  // Validate the transformer name
  virtual void validate_transformer( AST *transformer,
                                     AST *obj_obj,
                                     bool isInstanceBased );
  // The parameter transformer is an AST containing the string with the
  // transformer name.  The parameter obj is an AST with a pointer to the
  // object (of type O_OBJ) which owns the transformer.
  // If isInstanceBased is TRUE, the transformer must be instance-based;
  // otherwise, it must not be instance-based.
  // Returns a pointer to the transformer object (of type O_TFR).

  // Validate that object has an assigner state model
  virtual void validate_obj_is_assigner( AST *kl );
  // Parameter kl is an AST containing and objPtr of the object
  // to be validated.
  // Returns a pointer to the object (of type O_OBJ) in the AST.

  // Validate that object has a creation state
  virtual void validate_obj_has_creation_state( AST *kl );
  // Parameter kl is an AST containing and objPtr of the object
  // to be validated.
  // Returns a pointer to the object (of type O_OBJ) in the AST.

  // Validate that the event label can be received by the external entity
  virtual void validate_ee_event_label( AST *label,
                                        AST *ee );
  // Parameter label is an AST containing the name of the
  // event label.
  // Parameter ee is an AST containing a pointer to the object (of type
  // S_EE), the external entity to be validated.
  // Returns a pointer to the object (of type S_EEEVT) in the AST.


  // Validate enumerator
  virtual void validate_enumerator( AST *enumeration,
                            AST *enumerator );
  // The parameter enumeration is an AST for the enumeration to be validated.
  // The parameter enumerator is an AST for the enumerator (value
  // defined by enumeration) to be validated.

  //------------------------------------------------------------
  // Query functions
  //------------------------------------------------------------
  
  // Determine if object keyletters is a valid object
  virtual bool is_valid_obj_kl( AST *kl );
  // Parameter kl is an AST containing the string with the object
  // keyletters.
  // Returns TRUE if keyletters are valid; otherwise FALSE;
  
  // Determine if transformer is valid for this object
  virtual bool is_valid_transformer( AST *transformer,
                                     AST *obj_obj,
                                     bool isInstanceBased );
  // Parameter transformer is an AST containing the string with the
  // transformer name.  Parameter obj_obj is a pointer to the
  // object (of type O_OBJ) which possibly contains the transformer.
  // If isInstanceBased is TRUE, the transformer must be instance-based;
  // otherwise, it must not be instance-based.
  // Returns TRUE if transformer is valid; otherwise FALSE
  
  // Determine if event label is valid for this object
  virtual bool is_valid_obj_event_label( AST *label,
                                         AST *obj_obj );
  // Parameter label is an AST containing the string with the label
  // text.  Parameter obj_obj is a pointer to the object (of type O_OBJ)
  // to verify the event label for.
  // Returns TRUE if the event is valid; otherwise FALSE

  // Determine if keyletters is a valid external entity
  virtual bool is_valid_ee_kl( AST *kl );
  // Parameter kl is an AST containing the string with the ee
  // keyletters.
  // Returns TRUE if keyletters are valid; otherwise FALSE;

  // Determine if bridge is valid for this external entity
  virtual bool is_valid_ee_bridge( AST *bridge,
                                   AST *ee_obj );
  // Parameter label is an AST containing the string with the bridge
  // name.  Parameter ee_obj is a pointer to the ee (of type S_EE)
  // to verify the bridge name for.
  // Returns TRUE if the bridge is valid; otherwise FALSE
  
  // Determine if event label is valid for this external entity
  virtual bool is_valid_ee_event_label( AST *label,
                                        AST *ee_obj );
  // Parameter label is an AST containing the string with the label
  // text.  Parameter ee_obj is a pointer to the ee (of type S_EE)
  // to verify the event label for.
  // Returns TRUE if the event is valid; otherwise FALSE

  // Get the data type of the bridge data item
  virtual t_core_data_type get_bridge_return_type( AST *bridge );
  // Parameter bridge is a pointer to a Bridge (S_BRG), which is 
  // used to find its return type.

  // Get the data type of the synch_svc data item
  virtual t_core_data_type get_synch_svc_return_type( AST *ss );
  // Parameter ss is a pointer to a synchronous service (S_SSYN), which is 
  // used to find its return type.

  // Get the data type of the transformer data item
  virtual t_core_data_type get_transformer_return_type( AST *obj );
  // Parameter data_item is a pointer to an Object (O_OBJ), which is 
  // used to find its return type.
  
  // Get the cardinality (Obj_Card_e) for the right object
  virtual Obj_Card_e get_right_obj_card( AST *rel,
                                        AST *obj_left,
                                        AST *obj_right);
  // Parameter rel is a pointer to a Relationship object (R_REL).
  // Parameter obj_left is a pointer to the object on the left side
  // of the relationship, and obj_right is a pointer to an object
  // on the right side of the relationship.  The function will return
  // a value from Obj_Card_e, either CARD_ONE or CARD_MANY, based on
  // whether the relationship is X to ONE or X to MANY.
  
  // Determine if attribute is referential
  virtual bool is_referential_attr( AST *attr );
  // Parameter attr is a pointer to an Attribute (O_ATTR).
  // Returns TRUE if the Attribute is referential; otherwise FALSE;

  // Determine if attribute is an identifier
  virtual bool is_identifier( AST *attr );
  // Parameter attr is a pointer to an Attribute (O_ATTR).
  // Returns TRUE if the Attribute is an identifier; otherwise FALSE;

  // Get cardinality of object with given object keyletters
  virtual int get_obj_kl_card( AST *kl );
  // Parameter kl is an AST containing the string with the object
  // keyletters.  kl->objPtr is assigned the pointer to the object
  // with the keyletters in kl->getText() if the cardinality == 1;
  // Returns the number of objects in this domain with the given
  // object keyletters.
  
  virtual persObjPtr get_enum_data_type_ptr(  AST* p_enum );

  virtual void verify_return_type( t_core_data_type p_dt, 
					  persObjPtr p_return_type_reqd,
					  AST *p_e, const vchar* p_descr );

  virtual void verify_return_void( persObjPtr p_return_type_reqd,
					  AST *p_e, const vchar* p_descr );


protected:
  P_error *er;
};

#endif

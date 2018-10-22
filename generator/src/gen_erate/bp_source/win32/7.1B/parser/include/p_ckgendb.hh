/*========================================================================
 *
 * File:      $RCSfile: p_ckgendb.hh,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:31 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#include <mc_dbms/mc_dbms.hh>

#ifndef P_CKGENDB_HH
#define P_CKGENDB_HH

#include "d_typdef.hh"   // t_core_data_type
#include "p_types.hh"
#include "p_ckbase.hh"
#include "vchar.h"


class AST;
class P_error;

class I_Object_Instance;
class I_Attribute_Instance;
class I_object_inst_ref_set_var;

class P_checkGenDB : public P_checkBase
{
public:
  // Constructor
  P_checkGenDB(P_error *p_er, bool p_dumpflag, unsigned int p_domain_code):
    P_checkBase(p_er),
    dumpflag(p_dumpflag),
    m_domain_code(p_domain_code)
    {}

  // Destructor
  virtual ~P_checkGenDB()
    {}


  //------------------------------------------------------------
  // Basic Interface Functions:
  //------------------------------------------------------------

  // Validate the object keyletters.
  void validate_obj_kl( AST *kl );
  // The parameter kl is the string containing the key letters.
  // It returns a pointer (of type O_OBJ*).

  // Validate object attribute
  int validate_obj_attribute( AST *attr,
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
  void validate_obj_event_label( AST *label,
                                 AST *to_obj );
  // Parameter label is an AST containing a string of event
  // label (which is defined in
  // OOA as the keyletters followed by the event number).  Parameter
  // to_obj is an AST containing the destination object (of type O_OBJ)
  // and the text given for the local variable of that object type.
  // Returns a pointer to the event (of type SM_EVT).

  // Validate the event label for an assigner
  void validate_assigner_event_label( AST *label,
                                      AST *to_obj );
  // Parameter label is an AST containing a string of event label
  // (which is defined in
  // Parameter label is an AST containing the string with the event
  // label.  Parameter to_obj is an AST containing a valid object
  // pointer (of type ???) to the assigner object and the kl text.
  // Returns a pointer to the event (of type SM_EVT) in the label AST.
  
  // Validate the event label as a creation event
  void validate_creator_event_label( AST *label,
                                     AST *to_obj );
  // Parameter label is an AST containing a string of
  // event label (which is defined in
  // OOA as the keyletters followed by the event number).  Parameter
  // to_obj is an AST containing the destination object (of type O_OBJ)
  // and the kl text.
  // Returns a pointer to the event (of type SM_EVT) in the label AST.

  // Validate the event meaning for a state model (not an EE)
  void validate_sm_event_meaning( AST *meaning,
                                 AST *event);
  // Parameter meaning is an AST containing the unquoted
  // phrase associated with an
  // event, called the event meaning.  Parameter event is the event
  // (of type SM_EVT) with which the meaning should be checked.
  // The parameter event is returned.

  // Validate event data item name by a pointer to the event
  void validate_rcvd_evt_data_item_name( AST *name,
                                        AST *event);
  // The parameter name is an AST containing the string with the event
  // data item name.  The parameter event is a pointer to the
  // event (of type SM_EVT).
  // This returns a pointer to the data item object (of time SM_EVTDI)
  // in the AST.

  // Validate state model event data items
  void validate_sm_event_data_items( AST *event,
                                    AST *data_items);
  // The parameter event is an AST with a pointer to the
  // event (of type SM_EVT) and the text of the event label.
  // The parameter data_items is an AST tree containing all of the data
  // item names in a sibling structure (traverse with data_items->right()).
  // All of the data item name ASTs will be given an objPtr and a dataType.

  // Validate external entity event data items
  void validate_ee_event_data_items( AST *event,
                                    AST *data_items);
  // The parameter event is an AST with a pointer to the external entity
  // event (of type S_EEEVT) and the text of the event label.
  // The parameter data_items is an AST tree containing all of the data
  // item names in a sibling structure (traverse with data_items->right()).
  // All of the data item name ASTs will be given an objPtr and a dataType.

  // Validate bridge data item
  void validate_bridge_data_item( AST *data_item,
                                  AST *bridge,
                                  Assign_Val_e isLval );
  // The parameter data_item is an AST for the data item to be validated.
  // The parameter bridge is an AST with a pointer to the bridge object.

  // Validate external entity event data items
  void validate_bridge_data_items( AST *bridge,
                                  AST *data_items);
  // The parameter bridge is an AST with a pointer to the bridge object.
  // The parameter data_items is an AST tree containing all of the data
  // item names in a sibling structure (traverse with data_items->right()).
  // All of the data item name ASTs will be given an objPtr and a dataType.

  // Validate synch_svc data data items
  void validate_synch_svc_data_items( AST *synch_svc,
                                              AST *data_items);
  // The parameter synch_svc is an AST with a pointer to the synch_svc object.
  // The parameter data_items is an AST tree containing all of the data
  // item names in a sibling structure (traverse with data_items->right()).
  // All of the data item name ASTs will be given an objPtr and a dataType.

  // Validate synch_svc data item
  void validate_synch_svc_data_item( AST *data_item,
                                     AST *synch_svc,
                                     Assign_Val_e isLval );
  // The parameter data_item is an AST for the data item to be validated.
  // The parameter synch_svc is an AST with a pointer to the
  // synch_svc object.

  // Validate transformer data item
  void validate_transformer_data_item( AST *data_item,
                                       AST *transformer,
                                       Assign_Val_e isLval );
  // The parameter data_item is an AST for the data item to be validated.
  // The parameter transformer is an AST with a pointer to the
  // transformer object.

  // Validate transformer data items
  void validate_transformer_data_items( AST *transformer,
                                       AST *data_items);
  // The parameter transformer is an AST with a pointer to the transformer object.
  // The parameter data_items is an AST tree containing all of the data
  // item names in a sibling structure (traverse with data_items->right()).
  // All of the data item name ASTs will be given an objPtr and a dataType.

  // Validate the relationship that ties together two objects. 
  void validate_rel_id( AST *id,
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
  // a pointer to the relationship phrase found in the parse. 
  // Returns a pointer to the relationship (of type R_REL).

  // Validate the objects and relationship for a RELATE/UNRELATE statement 
  void validate_relate( AST *id,
                       AST *from_obj,
                       AST *to_obj,
                       AST *rel_phrase);
  // The parameter id is an AST holding the string  which is the 
  // relationship number - without the leading "r".
  // The parameter from_obj is an AST with a pointer (of type O_OBJ *)
  // to the first object and a pointer to the text of either the instance
  // variable or the object keyletters.  The parameter to_obj is an AST with
  // a pointer (of type O_OBJ *) to the second object and a pointer to the
  // text of object keyletters. The parameter rel_phrase is an AST with
  // a pointer to the relationship phrase found in the parse.
  // Returns a pointer to the relationship (of type R_REL).

  // Validate the associative relationship that ties together three objects. 
  void validate_assoc_relate( AST *id,
                             AST *from,
                             AST *to,
                             AST *assoc,
                             AST *rel_phrase);
  // The parameter id is an AST holding the string  which is the 
  // relationship number - with the leading "R".
  // The parameter from is an AST with a pointer (of type O_OBJ *)
  // to the first object.  The parameter to is an AST with a pointer (of
  // type O_OBJ *) to the second object.
  // The parameter assoc is an AST with a pointer (of type O_OBJ *) 
  // to the associative object.
  // Returns a pointer to the relationship (of type R_REL) in the id AST.
  // Returns a pointer to R_Rel (Relationship).

  // Validate the relationship phrase
  void validate_rel_phrase (AST *rel_phrase,
                            AST *rel,
                            AST *kl);
  // The parameter rel_phrase is the unquoted phrase associated with
  // a relationship.  The parameter rel is an AST with a pointer to an
  // instance of R_REL and text of the relationship number.
  // The parameter kl is an AST with a pointer to an O_OBJ and the
  // text of its keyletters.
  // Returns a pointer to an object of type Object_As_xxx, one of the
  // OOA of OOA objects in the Relationship domain numbered 206, 207,
  // 209, or 210 in the AST.

  // Validate the relationship phrase
  void validate_rel_phrase_irv( AST *rel_phrase,
                                AST *rel,
                                AST *irv);
  // The parameter rel_phrase is the unquoted phrase associated with
  // a relationship.  The parameter rel is an AST with a pointer to an
  // instance of R_REL and text of the relationship number.
  // The parameter irv is an AST with a pointer to an O_OBJ and the
  // text of its instance reference variable name.
  // Returns a pointer to an object of type Object_As_xxx, one of the
  // OOA of OOA objects in the Relationship domain numbered 206, 207,
  // 209, or 210 in the AST.

  // Validate the external entity key letters
  void validate_ee_kl (AST *kl);
  // The parameter kl is an AST containing the string with the key
  // leeters.
  // Returns pointer to the external entity (of type S_EE).

  // Validate the event meaning for and external entity
  void validate_ee_event_meaning( AST *meaning,
                                 AST *event);
  // Parameter meaning is an AST containing the unquoted
  // phrase associated with an external entity event
  // event, called the event meaning.  Parameter event is the event
  // (of type S_EEEVT) with which the meaning should be checked.
  // The parameter event is returned.

  // Validate the bridge name
  void validate_bridge( AST *bridge,
                        AST *ee);
  // The parameter bridge is an AST containing the string with the
  // bridge name.  The parameter ee is an AST with pointer to the enternal
  // entity object (of type S_EE) and the EE keyletters.
  // Returns a pointer to the bridge object (of type S_BRG).

  // Validate the synch_svc name
  void validate_synch_svc( AST *synch_svc );
  // The parameter synch_svc is an AST containing the string with the
  // synch_svc name.
  // Returns a pointer to the synch_svc object (of type S_SYNC) in the AST.

  // Validate the transformer name
  void validate_transformer( AST *transformer,
                             AST *obj_obj,
                             bool isInstanceBased );
  // The parameter transformer is an AST containing the string with the
  // transformer name.  The parameter obj is an AST with a pointer to the
  // object (of type O_OBJ) which owns the transformer.
  // If isInstanceBased is TRUE, the transformer must be instance-based;
  // otherwise, it must not be instance-based.
  // Returns a pointer to the transformer object (of type O_TFR).

  // Validate that object has an assigner state model
  void validate_obj_is_assigner( AST *kl );
  // Parameter kl is an AST containing and objPtr of the object
  // to be validated.
  // Returns a pointer to the object (of type O_OBJ) in the AST.

  // Validate that object has a creation state
  void validate_obj_has_creation_state( AST *kl );
  // Parameter kl is an AST containing and objPtr of the object
  // to be validated.
  // Returns a pointer to the object (of type O_OBJ) in the AST.

  // Validate that the event label can be received by the external entity
  void validate_ee_event_label( AST *label,
                                AST *ee );
  // Parameter label is an AST containing the name of the
  // event label.
  // Parameter ee is an AST containing a pointer to the object (of type
  // S_EE), the external entity to be validated.
  // Returns a pointer to the object (of type S_EEEVT) in the AST.

  // Validate enumerator
  void validate_enumerator( AST *enumeration,
                            AST *enumerator );
  // The parameter enumeration is an AST for the enumeration to be validated.
  // The parameter enumerator is an AST for the enumerator (value
  // defined by enumeration) to be validated.


  //------------------------------------------------------------
  // Query functions
  //------------------------------------------------------------
  
  // Determine if object keyletters is a valid object
  bool is_valid_obj_kl( AST *kl );
  // Parameter kl is an AST containing the string with the object
  // keyletters.
  // Returns TRUE if keyletters are valid; otherwise FALSE;
  
  // Determine if transformer is valid for this object
  bool is_valid_transformer( AST *transformer,
                             AST *obj_obj,
                             bool isInstanceBased );
  // Parameter transformer is an AST containing the string with the
  // transformer name.  Parameter obj_obj is a pointer to the
  // object (of type O_OBJ) which possibly contains the transformer.
  // If isInstanceBased is TRUE, the transformer must be instance-based;
  // otherwise, it must not be instance-based.
  // Returns TRUE if transformer is valid; otherwise FALSE
  
  // Determine if event label is valid for this object
  bool is_valid_obj_event_label( AST *label,
                                 AST *obj_obj );
  // Parameter label is an AST containing the string with the label
  // text.  Parameter obj_obj is a pointer to the object (of type O_OBJ)
  // to verify the event label for.
  // Returns TRUE if the event is valid; otherwise FALSE

  // Determine if keyletters is a valid external entity
  bool is_valid_ee_kl( AST *kl );
  // Parameter kl is an AST containing the string with the ee
  // keyletters.
  // Returns TRUE if keyletters are valid; otherwise FALSE;

  // Determine if bridge is valid for this external entity
  bool is_valid_ee_bridge( AST *bridge,
                           AST *ee_obj );
  // Parameter label is an AST containing the string with the bridge
  // name.  Parameter ee_obj is a pointer to the ee (of type S_EE)
  // to verify the bridge name for.
  // Returns TRUE if the bridge is valid; otherwise FALSE
  
  // Determine if event label is valid for this external entity
  bool is_valid_ee_event_label( AST *label,
                                AST *ee_obj );
  // Parameter label is an AST containing the string with the label
  // text.  Parameter obj_obj is a pointer to the ee (of type S_EE)
  // to verify the event label for.
  // Returns TRUE if the event is valid; otherwise FALSE
  
  // Get the data type of the transformer data item
  void get_transformer_param_type( AST *data_item );
  // Parameter data_item is an AST containing the Transformer Parameter
  // (O_TPARM), which is used to find its associated data type.
  // The data type of the AST is set based on the value found in 
  // the Data Type (S_DT) object associated with the Transformer Parameter.
  
  // Get the data type of the bridge data item
  void get_bridge_param_type( AST *data_item );
  // Parameter data_item is an AST containing the Bridge Parameter
  // (S_BPARM), which is used to find its associated data type.
  // The data type of the AST is set based on the value found in 
  // the Data Type (S_DT) object associated with the Bridge Parameter.
  
  // Get the cardinality (Obj_Card_e) for the right object
  Obj_Card_e get_right_obj_card( AST *rel,
                                AST *obj_left,
                                AST *obj_right);
  // Parameter rel is a pointer to a Relationship object (R_REL).
  // Parameter obj_left is a pointer to the object on the left side
  // of the relationship, and obj_right is a pointer to an object
  // on the right side of the relationship.  The function will return
  // a value from Obj_Card_e, either CARD_ONE or CARD_MANY, based on
  // whether the relationship is X to ONE or X to MANY.
  
  // Get the data type of the transformer data item
  t_core_data_type get_transformer_return_type( AST *obj );
  // Parameter data_item is a pointer to an Object (O_OBJ), which is 
  // used to find its return type.

  // Get the data type of the bridge data item
  t_core_data_type get_bridge_return_type( AST *ee );
  // Parameter data_item is a pointer to a Bridge (S_BRG), which is 
  // used to find its return type.

  // Get the data type of the synch_svc data item
  virtual t_core_data_type get_synch_svc_return_type( AST *ss );
  // Parameter ss is a pointer to a synchronous service (S_SYNC), which is 
  // used to find its return type.

  // Determine if attribute is referential
  bool is_referential_attr( AST *attr );
  // Parameter attr is a pointer to an Attribute (O_ATTR).
  // Returns TRUE if the Attribute is referential; otherwise FALSE;

  // Determine if attribute is an identifier
  bool is_identifier( AST *attr );
  // Parameter attr is a pointer to an Attribute (O_ATTR).
  // Returns TRUE if the Attribute is an identifier; otherwise FALSE;



  I_Attribute_Instance* get_attribute_instance_by_name ( char *kl, 
     char *attr_name, const vchar *attr_value, bool &mult_found );
  // Find an attribute instance for the object with keyletters kl, the attribute
  // name attr_name, with that attribute having the value attr_value.  Return
  // the instance matching.  If none found, return zero.  If more than one found,
  // return the first one found, and set mult_found to true.

  static I_Attribute_Instance* find_Attribute_Instance_R2002_by_name( I_Object_Instance *oi_ptr,
    const vchar * attr_name, int &num_found );
  // Return a pointer to an I_Attribute_Instance related by I_Object_Instance oi_ptr
  // where the attribute has the name attr_name. The number of attributes that match
  // attr_name is returned in num_found. The first attribute instance that matches
  // is returned by the function.

  t_core_data_type find_core_data_type( I_Object_Instance *p_attr, const char *rel_id );
  // Return the core data type for an object instance p_attr that is related to the S_DT
  // object via the relationship rel_id.
  // If the core datatype is not found, UNKNOWN_DATATYPE is returned.

  persObjPtr find_enum_data_type( I_Object_Instance *p_attr, const char *rel_id );
  // Return the enum data type for an object instance p_attr that is related to the S_DT
  // object via the relationship rel_id.
  // If the enum datatype is not found, zero is returned.

  Obj_Card_e get_mult_attr ( I_object_inst_ref_set_var *obj_as );
  // Return the cardinality enum value for the "MULT" attribute of obj_as.
  // The inst_ref_set contains one object instance that is one of the "Object As ..."
  // objects (206, 207, 209, 210, 211, 213, 214).

  persObjPtr get_enum_data_type_ptr(  AST* p_enum );
  void find_event_for_event_label( const vchar* p_event_label,
                                      I_object_inst_ref_set_var *p_ism,
                                      bool& p_found_here,
                                      mc_dbms_Bag< I_Object_Instance * > *&p_event_coll);


private:
  
  // Domain code of the action spec being translated
  unsigned int m_domain_code;

  bool dumpflag;
  // True if the AST passing in to validate functions should be printed
  // out as a debugging aid.  

};

#endif

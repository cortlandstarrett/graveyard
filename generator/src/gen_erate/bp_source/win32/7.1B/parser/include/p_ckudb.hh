/*========================================================================
 *
 * File:      $RCSfile: p_ckudb.hh,v $
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
#ifndef P_CKOSDB_HH
#define P_CKOSDB_HH

#include "p_types.hh"
#include "p_ckbase.hh"

class AST;
class P_error;

class P_checkUserDB : public P_checkBase
{
public:
  // Constructor
  P_checkUserDB(P_error *p_er):
    P_checkBase(p_er)
    {}

  // Destructor
  virtual ~P_checkUserDB()
    {}

  //------------------------------------------------------------
  // Query functions
  //------------------------------------------------------------
  
  // Determine if object keyletters is a valid object
  bool is_valid_obj_kl( AST *kl );
  // Parameter kl is an AST containing the string with the object
  // keyletters.
  // Returns TRUE if keyletters are valid; otherwise FALSE;
  
  // Get cardinality of object with given object keyletters
  int get_obj_kl_card( AST *kl );
  // Parameter kl is an AST containing the string with the object
  // keyletters.  kl->objPtr is assigned the pointer to the object
  // with the keyletters in kl->getText() if the cardinality == 1;
  // Returns the number of objects in this domain with the given
  // object keyletters.
  
  // Determine if transformer is valid for this object
  bool is_valid_transformer( AST *transformer,
                            AST *obj_obj );
  // Parameter transformer is an AST containing the string with the
  // transformer name.  Parameter obj_obj is a pointer to the
  // object (of type O_OBJ) which possibly contains the transformer.
  // Returns TRUE if transformer is valid; otherwise FALSE
  
  // Determine if event label is valid for this object
  bool is_valid_obj_event_label( AST *label,
                                 AST *obj_obj,
                                 bool PE_indicated );
  // Parameter label is an AST containing the string with the label
  // text.  Parameter obj_obj is a pointer to the object (of type O_OBJ)
  // to verify the event label for.
  // Returns TRUE if the event is valid; otherwise FALSE

  // Determine if keyletters is a valid external entity
  bool is_valid_ee_kl( AST *kl );
  // Parameter kl is an AST containing the string with the ee
  // keyletters.
  // Returns TRUE if keyletters are valid; otherwise FALSE;
  
  // Determine if event label is valid for this external entity
  bool is_valid_ee_event_label( AST *label,
                                AST *ee_obj,
                                bool PE_indicated );
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

  // Determine if attribute is referential
  bool is_referential_attr( AST *attr );
  // Parameter attr is a pointer to an Attribute (O_ATTR).
  // Returns TRUE if the Attribute is referential; otherwise FALSE;

  // Determine if attribute is an identifier
  bool is_identifier( AST *attr );
  // Parameter attr is a pointer to an Attribute (O_ATTR).
  // Returns TRUE if the Attribute is an identifier; otherwise FALSE;

};

#endif

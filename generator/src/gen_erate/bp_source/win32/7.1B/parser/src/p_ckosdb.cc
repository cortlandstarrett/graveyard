/*========================================================================
 *
 * File:      $RCSfile: p_ckosdb.cc,v $
 * Version:   $Revision: 1.10 $
 * Modified:  $Date: 2013/01/10 23:41:21 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#include <mc_dbms/mc_dbms.hh>


#include "p_ckosdb.hh"
#include "myAST.h"
#include "p_error.hh"
#include "vstr.h"
#include "p_check.hh"     // RESET_OBJPTR

// BridgePoint includes

#include "u_smtptr.hh"
#include "d_object.hh"
#include "a_gfinds.hh"
#include "u_desc.hh"
#include "u_cursor.hh"      // For FIRST_ELEMENT/NEXT_ELEMENT
#include "d_dattyp.hh"      // For D_core_data_type
#include "d_sm_pm.hh"       // For D_sm_spt_pm
#include "d_smevt.hh"       // For D_sm_event
#include "d_action.hh"      // For D_action
#include "d_suppdi.hh"      // For D_supplemental_data_item
#include "d_suppdt.hh"      // For D_supplemental_data
#include "d_smedi.hh"       // For D_sm_event_data_item
#include "d_rel.hh"
#include "d_assrel.hh"
#include "d_typdef.hh"      // For t_multiplicity
#include "d_moorhm.hh"      // For D_moore_action_home
#include "d_smsta.hh"       // For D_sm_state
#include "a_bush.hh"        // For AL_Bush, AL_Bush_statement
#include "d_bridge.hh"      // For D_bridge
#include "d_entity.hh"      // For D_external_entity
#include "d_tfmr.hh"        // For D_transformer
#include "d_parm.hh"        // For D_bridge_parm
#include "d_levt.hh"        // For D_local_event
#include "d_nlevt.hh"       // For D_non_local_event
#include "d_pevt.hh"        // For D_polymorphic_event
#include "d_inhrel.hh"
#include "u_keyword.hh"     // For self_string
#include <d_battr.hh>

#define AL_OBJECT_REFERENCE object_key_letters().char_ptr()

//------------------------------------------------------------
// Basic Interface Functions:
//------------------------------------------------------------


//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
//
// Function: validate_obj_kl
// Description: Validate the object keyletters in the dbms_config database
//              
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
void P_checkOSDB::validate_obj_kl( AST *kl )
{
  // Let's make sure the object key_letters exists.
  Smart_ptr< mc_dbms_Bag< Object * > > object_coll =
    AL_Generic_finds::find_object_by_key_letters( m_current_domain_ptr,
                                                  kl->getVcharText() );
  int card = object_coll->cardinality();

  // Generate this error if the keyletters can't be found
  if ( card == 0 )
    {
      AL_PARSE_ERR1( kl, AL_GETMSG(ERR,123,1), kl->getVcharText() )
      return;
    }
  
  // Generate this error if there's more than one object with keyletters kl
  else if ( card > 1 )
    {
      AL_PARSE_ERR1( kl, AL_GETMSG(ERR,023,1), kl->getVcharText() )
      return;
    }

  Object *obj_ptr = object_coll->pick();

  kl->setObjPtr( (persObjPtr) obj_ptr );
  kl->set_Id( obj_ptr->get_id() );
}


//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
//
// Function: validate_obj_attribute
// Description: Validate object attribute in the dbms_config database
//              
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
int P_checkOSDB::validate_obj_attribute( AST *attr,
                                               AST *obj_obj,
                                               Assign_Val_e isLval,
				                               const vchar* attribute_write_valid)
{

  if ( isLval == ASSIGN_LVAL )
    {
      vstr *cs = vstrCloneScribed(vcharScribeASCIIShared("current_state"));
      if (vcharCompare( attr->getVcharText(), cs ) == 0)
        {
          // Generate this error if the attr is current_state and an lval
          AL_PARSE_ERR0( attr, AL_GETMSG(ERR,129,0) )
          return FALSE;
        }
      vstrDestroy(cs);
    }

  // Get the attribute with the name in attr AST
  Attribute *attribute_ptr = find_attribute( attr->getVcharText(),
                                             (Object *) obj_obj->getObjPtr() );
  
  // Put the attribute pointer in the attr AST
  attr->setObjPtr( (persObjPtr) attribute_ptr );

  Object *object_ptr = (Object *) obj_obj->getObjPtr();

  if ( attribute_ptr == 0 )
    {
      // Generate this error if the obj_obj does not contain the attr
      AL_PARSE_ERR3( attr, AL_GETMSG(ERR,127,3),
                    object_ptr->get_object_name_char_ptr(),
                    obj_obj->getVcharText(), attr->getVcharText() )
      return FALSE;
    }
  
  if ( attribute_ptr->get_core_data_type_ptr() == NULL )
    {
	  if ( attribute_ptr->get_enum_data_type_ptr() == NULL )
	  {
		  // Generate this error if (somehow?) you can't determine the datatype
		  // of the attribute
		  AL_PARSE_ERR1( attr, AL_GETMSG(ERR,121,1), attr->getVcharText() )
		  return FALSE;
	  }
	  else
	  {
		  // Set the datatype of the attribute in the AST tree
		  attr->setDatatype( ENUMERATION_DATATYPE );
	  }
    }
  else
  {
    // Set the datatype of the attribute in the AST tree
    attr->setDatatype( (t_core_data_type) attribute_ptr->
        get_core_data_type_ptr()->get_core_data_type_type() );
  }

  if ( isLval == ASSIGN_LVAL )
    {
      if ( attribute_ptr->get_referential_attribute_ptr() != NULL )
        {
          AL_PARSE_ERR1( attr, AL_GETMSG(ERR,122,1), attr->getVcharText() );
          return FALSE;
        }
      if ( (attr->getDatatype() == UNIQUE_ID_DATATYPE) && attribute_ptr->
          is_an_identifier() )
        {
          AL_PARSE_ERR1( attr, AL_GETMSG(ERR,273,1), attr->getVcharText() );
          return FALSE;
        }
      if ( attribute_ptr->get_base_attribute_ptr() != NULL )
        {
          Base_attribute* base_attr_ptr = attribute_ptr->get_base_attribute_ptr();
          if ( base_attr_ptr->get_derived_base_attribute_ptr() != NULL )
          {
			  if ( attribute_write_valid == 0 || vcharLength(attribute_write_valid) == 0 )
			  {
                  if ( base_attr_ptr->get_parse_on_apply() )
                  {
    	              AL_PARSE_ERR1( attr, AL_GETMSG(ERR,130,1), attr->getVcharText() );
                      return FALSE;
                  }
                  // else parse on apply not set, so let them treat it like a 
                  // normal attribute
			  }
              else
			  {
			      if (vcharCompareBase( obj_obj->getVcharText(), self_string.char_ptr() ) != 0)
				  {
		              AL_PARSE_ERR1( attr, AL_GETMSG(ERR,130,1), attr->getVcharText() );
		              return FALSE;
				  }
				  else if (vcharCompare( attr->getVcharText(), attribute_write_valid ) != 0)
				  {
		              AL_PARSE_ERR1( attr, AL_GETMSG(ERR,130,1), attr->getVcharText() );
		              return FALSE;
				  }
				  else
				  {
				     attr->set_Id( attribute_ptr->get_id() );
				     return TRUE;
				  }
			  }
          }
        }
    }

  if ( isLval == ASSIGN_RVAL )
  {
      if ( attribute_ptr->get_base_attribute_ptr() != NULL )
        {
          Base_attribute* base_attr_ptr = attribute_ptr->get_base_attribute_ptr();
          if ( base_attr_ptr->get_derived_base_attribute_ptr() != NULL )
          {
			  if ( attribute_write_valid != 0 && vcharLength(attribute_write_valid) != 0 )
			  {
			      if (vcharCompareBase( obj_obj->getVcharText(), self_string.char_ptr() ) == 0 &&
				      vcharCompare( attr->getVcharText(), attribute_write_valid ) == 0)
				  {
                      // reading the derived attribute in it's own description causes
                      // an infinite loop in Verifier.  
    	              AL_PARSE_ERR1( attr, AL_GETMSG(ERR,252,1), attr->getVcharText() );
                      return FALSE;
				  }
			  }
          }
        }
  }
 
  // ReadOnly is for use when passing parameters by reference.
  t_boolean isReadOnly = FALSE;
  if ( attribute_ptr->get_referential_attribute_ptr() != NULL )
    {
      isReadOnly = TRUE;
    }
  else if ( (attr->getDatatype() == UNIQUE_ID_DATATYPE) && attribute_ptr->
      is_an_identifier() )
    {
      isReadOnly = TRUE;
    }
  else if ( attribute_ptr->get_base_attribute_ptr() != NULL )
    {
      Base_attribute* base_attr_ptr = attribute_ptr->get_base_attribute_ptr();
      if ( base_attr_ptr->get_derived_base_attribute_ptr() != NULL )
      {
		  if ( attribute_write_valid == 0 || vcharLength(attribute_write_valid) == 0 )
		  {
              if ( base_attr_ptr->get_parse_on_apply() )
              {
                  isReadOnly = TRUE;
              }
              // else parse on apply not set, so let them treat it like a 
              // normal attribute
		  }
          else
		  {
			  if (vcharCompareBase( obj_obj->getVcharText(), self_string.char_ptr() ) != 0)
			  {
                  isReadOnly = TRUE;
			  }
			  else if (vcharCompare( attr->getVcharText(), attribute_write_valid ) != 0)
			  {
                  isReadOnly = TRUE;
			  }
              else
              {
                  // in theory, we could pass the derived attribute as a parameter
                  // in practice, the baggage to figure out if the passed in parameter
                  // is a derived attribute, and to set the proper flags if the 
                  // derived attirbute is written in the called function is too much
                  // junk.
                  // The user can pass a local variable to the function, and then
                  // assign that value to the derived attribute, if they really need to.
                  isReadOnly = TRUE;
              }
		  }
      }
    }

  obj_obj->setReadOnly ( isReadOnly );
  attr->set_Id( attribute_ptr->get_id() );

  return FALSE;
}


//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
//
// Function: validate_obj_event_label
// Description: Validate the event label in the dbms_config database
//              
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
void P_checkOSDB::validate_obj_event_label( AST *label,
                                            AST *to_obj )
{
  Object *to_object_ptr = (Object *) to_obj->getObjPtr();
  D_sm_spt_pm *event_to_sm_spt_pm_ptr = to_object_ptr->
    get_instance_sm_spt_pm_ptr();

  if ( event_to_sm_spt_pm_ptr == NULL )
    {
      // Generate this if there is no instance state model associated with label
      AL_PARSE_ERR2( label, AL_GETMSG(ERR,125,2),
                    to_object_ptr->get_object_name_char_ptr(),
                    label->getVcharText() )
      return;
    }
  
  bool found_here = FALSE;
  mc_dbms_Bag< D_sm_event * > *sm_event_coll = 0;

  find_all_events ( label->getVcharText(),
             event_to_sm_spt_pm_ptr, found_here, sm_event_coll );
  if ( sm_event_coll->cardinality() == 0 )
    {
      // If the to object is self, 
      if ( to_obj->getType() == TOK_SELF )
        {
          // If no events with this label are found for this state
          //  model (or for an EE--see below), generate this error message:
          AL_PARSE_ERR1( label, AL_GETMSG(ERR,068,1), label->getVcharText() )
          delete sm_event_coll;
          return;
        }
      else
        {
          // Generate this error if the event can't be found for this object
          // Instead of to_obj->getVcharText(), use the actual object name from
          //  database
          AL_PARSE_ERR2( label, AL_GETMSG(ERR,061,2), label->getVcharText(),
                        to_object_ptr->get_object_name_char_ptr() )
          delete sm_event_coll;
          return;
        }
    }
    else if ( sm_event_coll->cardinality() > 1 )
    {
      // If multiple events with the same label are found for this object,
      // generate this error message:
      AL_PARSE_ERR1( label, AL_GETMSG(ERR,020,1), label->getVcharText() )
      delete sm_event_coll;
      return;
    }
  
    D_sm_event *event_ptr = sm_event_coll->pick();

  // Put the event pointer and Id into the attr AST
  label->setObjPtr( (persObjPtr) event_ptr );
  label->set_Id( event_ptr->get_id() );

  delete sm_event_coll;
  return;
}


//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
//
// Function: validate_sm_event_meaning
// Description: Validate the event meaning in the dbms_config database
//              
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
void P_checkOSDB::validate_sm_event_meaning( AST *meaning,
                                             AST *event)
{
  // Check event meaning for state model event only
  D_sm_event * event_ptr = (D_sm_event *) event->getObjPtr();

  const vchar *ast_meaning = meaning->getVcharText();
  const vchar first_char = *ast_meaning;
  const vchar tic = vcharFromASCII('\'');
  size_t len;
  if ( first_char == tic )
    {
      // Tick mark in meaning string in AST
      len = vcharLength(ast_meaning) - 2;  // remove first/last tick count

      Description db_meaning = event_ptr->get_event_meaning();

      const vchar *past_tick = ast_meaning + 1;
      if ( vcharCompareBounded ( db_meaning.char_ptr(), past_tick, len ) != 0 ||
          ( len != vcharLength(db_meaning.char_ptr()) ) )
        {
          // if the meaning doesn't match the label, generate this error
          AL_PARSE_ERR2( meaning, AL_GETMSG(ERR,069,2),
                         meaning->getVcharText(), event->getVcharText() )
          return;
        }
    }
  else
    {
      if ( event_ptr->get_event_meaning() != meaning->getVcharText() )
        {
          // if the meaning doesn't match the label, generate this error
          AL_PARSE_ERR2( meaning, AL_GETMSG(ERR,069,2),
                         meaning->getVcharText(), event->getVcharText() )
          return;
        }
    }
  
  // Put the event Id into the meaning AST for use by the bush create code
  meaning->set_Id( event_ptr->get_id() );
  
  return;
}


//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
//
// Function: validate_ee_event_meaning
// Description: Validate the event meaning in the dbms_config database
//              
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// Validate the external entity event meaning
void P_checkOSDB::validate_ee_event_meaning( AST *meaning,
                                             AST *event)
{
  // Check event meaning for state model event only
  D_external_entity_event * event_ptr =
    (D_external_entity_event *) event->getObjPtr();

  const vchar *ast_meaning = meaning->getVcharText();
  const vchar first_char = *ast_meaning;
  const vchar tic = vcharFromASCII('\'');
  size_t len;
  if ( first_char == tic )
    {
      // Tick mark in meaning string in AST
      len = vcharLength (ast_meaning) - 2;  // remove first/last tick count

      Description db_meaning = event_ptr->get_event_meaning();

      const vchar *past_tick = ast_meaning + 1;
      if ( vcharCompareBounded ( db_meaning.char_ptr(), past_tick, len ) != 0 ||
          ( len != vcharLength(db_meaning.char_ptr()) ) )
        {
          // if the meaning doesn't match the label, generate this error
          AL_PARSE_ERR2( meaning, AL_GETMSG(ERR,069,2),
                         meaning->getVcharText(), event->getVcharText() )
          return;
        }
    }
  else
    {
      if ( event_ptr->get_event_meaning() != meaning->getVcharText() )
        {
          // if the meaning doesn't match the label, generate this error
          AL_PARSE_ERR2( meaning, AL_GETMSG(ERR,069,2),
                         meaning->getVcharText(), event->getVcharText() )
          return;
        }
    }

  // Put the event Id into the meaning AST for use by the bush create code
  meaning->set_Id( event_ptr->get_id() );

  return;
}


//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
//
// Function: validate_rcvd_evt_data_item_name
// Description: Validate event data item name in the dbms_config database
//              
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
void P_checkOSDB::validate_rcvd_evt_data_item_name( AST *name,
                                                    AST *event)
{
  D_sm_event* event_ptr = (D_sm_event *)event->getObjPtr();
  const vchar *cname = name->getVcharText();
  
  //Get the pointer to the event data item with the given name
  D_sm_event_data_item *event_data_item_ptr = 0;
  FIRST_ELEMENT( event_data_item_ptr,
                 D_sm_event_data_item,
                 event_ptr->get_sm_event_data_item_coll_ptr(),
                 cursor );

  while( event_data_item_ptr )
  {
    if ( event_data_item_ptr->get_event_data_name() == cname )
    {
      break;
    }
    else
    {
      NEXT_ELEMENT( event_data_item_ptr, cursor );
    }
  }

  if ( event_data_item_ptr == NULL )
    {
      // Generate this error if the given data item is not associated
      //  with the event
      AL_PARSE_ERR1( name, AL_GETMSG(ERR,152,1), name->getVcharText() );
      return;
    }

  // Now set the objPtr, Id, and the dataType in the AST to the supp data item
  name->setObjPtr( event_data_item_ptr );
  name->set_Id( event_data_item_ptr->get_id() );

  t_core_data_type datatype = UNKNOWN_DATATYPE;
  D_core_data_type *core_dt = event_data_item_ptr->get_core_data_type_ptr();
  if ( core_dt != 0 )
  {
    datatype = (t_core_data_type)core_dt->get_core_data_type_type();
  }
  else   // enum_data_type
  {
    datatype = ENUMERATION_DATATYPE;
  }
  name->setDatatype( datatype );

  return;
}

bool P_checkOSDB::verify_datatype (D_dd_srm_scm_sam* p_dd_ptr,
	   const Id &p_data_type_id, 
       AST* p_ast,
       t_core_data_type &p_db_datatype) 
{
	// Returns TRUE if there is a type mismatch

  D_data_type * dt_ptr = p_dd_ptr->find_data_type_by_id(p_data_type_id);

  p_db_datatype = UNKNOWN_DATATYPE;
  if ( dt_ptr != 0 )
  {
	  if ( dt_ptr->get_enum_data_type_ptr() )
	  {
		  p_db_datatype = ENUMERATION_DATATYPE;
		  persObjPtr ast_datatype = 
			  get_enum_data_type_ptr( p_ast );
		  return dt_ptr != ast_datatype;
	  }
	  else
	  {
		  p_db_datatype = (t_core_data_type) dt_ptr->get_core_data_type_ptr()->
			get_core_data_type_type();
		  return p_db_datatype != p_ast->getDatatype();
	  }
  }
  else
  {
	return TRUE;
  }
}

//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
//
// Function: validate_sm_event_data_items
// Description: Validate the event data items in the dbms_config database
//              
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
void P_checkOSDB::validate_sm_event_data_items( AST *event,
                                                AST *data_items)
{
  // Get the event pointer
  D_sm_event *event_ptr = (D_sm_event *) event->getObjPtr();

  //TODO: Since R522 is no longer used, this needs to be rewritten to validate
  //        across R532. (Bugzilla issue 3467)
}


//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
//
// Function: validate_rel_id
// Description: Validate the relationship in the dbms_config database
//              
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// Validate the relationship that ties together two objects. 
void P_checkOSDB::validate_rel_id( AST *id,
                                   AST *from,
                                   AST *to,
                                   AST *rel_phrase,
                                   Obj_Card_e card_expected,
                                   bool &manyFound )
{
  const vchar *vc_rel_num = id->getVcharText();
  // Strip leading [Rr] from relationship id
  const char *rel_num = id->getAsciiText();
  const char R = 'R';
  const char r = 'r';
  
  if ( (rel_num[0] == R) || (rel_num[0] == r) )
    {
      ++rel_num;
      ++vc_rel_num;
    }

  Smart_ptr< mc_dbms_Bag< Relationship * > > rel_coll =
    AL_Generic_finds::find_relationship_by_number( m_current_domain_ptr,
                                                   rel_num );

  int card = rel_coll->cardinality();
  
  if ( card == 0 )
    {
      // Generate this error if the relationship does not exist
      AL_PARSE_ERR1( id, AL_GETMSG(ERR,173,1), vc_rel_num )
      return;
    }
  else if ( card > 1 )
    {
      // Generate this error if there's more than one relationship with the number
      AL_PARSE_ERR1( id, AL_GETMSG(ERR,024,1), vc_rel_num )
      return;
    }

  Relationship * rel_ptr = rel_coll->pick();
  Id rel_id = rel_ptr->get_relationship_id();
  t_multiplicity mult;
  
  if ( ! is_valid_relation( id, rel_phrase, (Object *)from->getObjPtr(), rel_ptr,
                           (Object *)to->getObjPtr(), mult ) )
    {
      return;
    }
  
  switch( card_expected )
    {
    case CARD_UNKNOWN:
    case CARD_ONE:
      if ( mult != ONE )
        AL_PARSE_ERR0( id, AL_GETMSG(ERR,171,0) );
      break;
    case CARD_MANY:
    case CARD_ANY:
      if ( mult == MANY )
        manyFound = TRUE;
      break;
    }

  id->setObjPtr( (persObjPtr) rel_ptr );
  id->set_Id( rel_ptr->get_relationship_id() );

  return;
}


//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
//
// Function: validate_relate
// Description: Validate the relate statement in the dbms_config database
//              
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// Validate the objects and relationship for a relate/unrelate.
void P_checkOSDB::validate_relate( AST *id,
                                   AST *from,
                                   AST *to,
                                   AST *rel_phrase )
{
  const vchar *vc_rel_num = id->getVcharText();
  // Strip leading [Rr] from relationship id
  const char *rel_num = id->getAsciiText();
  const char R = 'R';
  const char r = 'r';
  
  if ( (rel_num[0] == R) || (rel_num[0] == r) )
    {
      ++rel_num;
      ++vc_rel_num;
    }

  Smart_ptr< mc_dbms_Bag< Relationship * > > rel_coll =
    AL_Generic_finds::find_relationship_by_number( m_current_domain_ptr,
                                                   rel_num );

  int card = rel_coll->cardinality();

  if ( card == 1 )
    {
      Relationship * rel_ptr = rel_coll->pick();

      // If associative relationship then need "USING ref" clause.
      if ( rel_ptr->get_associative_relationship_ptr() )
        {
          // Generate this if the objects have an associative relationship
          //  and need USING clause
          AL_PARSE_ERR1( id, AL_GETMSG(ERR,176,1), vc_rel_num )
          return;
        }
    }
  if ( card == 0 )
    {
      // Generate this error if the relationship does not exist
      AL_PARSE_ERR1( id, AL_GETMSG(ERR,173,1), vc_rel_num )
      return;
    }
  if ( card > 1 )
    {
      // Generate this error if there's more than one relationship with the number
      AL_PARSE_ERR1( id, AL_GETMSG(ERR,024,1), vc_rel_num )
      return;
    }

  Relationship * rel_ptr = rel_coll->pick();
  Id rel_id = rel_ptr->get_relationship_id();
  t_multiplicity mult;
  
  if ( ! is_valid_relation( id, rel_phrase, (Object *)from->getObjPtr(), rel_ptr,
                           (Object *)to->getObjPtr(), mult ) )
    {
      return;
    }
  
  id->setObjPtr( (persObjPtr) rel_ptr );
  id->set_Id( rel_ptr->get_relationship_id() );

  return;
}


//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
//
// Function: validate_assoc_relate
// Description: Validate the assoc relationship in the dbms_config database
//              
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// Validate the associative relationship that ties together three objects. 
void P_checkOSDB::validate_assoc_relate( AST *id,
                                         AST *from,
                                         AST *to,
                                         AST *assoc,
                                         AST *rel_phrase )
{
  const vchar *vc_rel_num = id->getVcharText();
  // Strip leading [Rr] from relationship id
  const char *rel_num = id->getAsciiText();
  const char R = 'R';
  const char r = 'r';
  
  if ( (rel_num[0] == R) || (rel_num[0] == r) )
    {
      ++rel_num;
      ++vc_rel_num;
    }

  Smart_ptr< mc_dbms_Bag< Relationship * > > rel_coll =
    AL_Generic_finds::find_relationship_by_number( m_current_domain_ptr,
                                                   rel_num );
  int card = rel_coll->cardinality();
  if ( card == 0 )
    {
      // Generate this error if the relationship does not exist
      AL_PARSE_ERR1( id, AL_GETMSG(ERR,173,1), vc_rel_num )
      return;
    }
  if ( card > 1 )
    {
      // Generate this error if there's more than one relationship with the number
      AL_PARSE_ERR1( id, AL_GETMSG(ERR,024,1), vc_rel_num )
      return;
    }

  Relationship * rel_ptr = rel_coll->pick();
  Id rel_id = rel_ptr->get_relationship_id();
  t_multiplicity mult;
  
  if ( ! is_valid_relation( id, rel_phrase, (Object *)from->getObjPtr(), rel_ptr,
                           (Object *)to->getObjPtr(), mult ) )
    {
      return;
    }

  // We know that the relationship is associative and has been validated
  // Validate the associative part

  Object * p_left_object_ptr = (Object *) from->getObjPtr();
  Object * p_right_object_ptr = (Object *) to->getObjPtr();
  Object * p_ass_object_ptr = (Object *) assoc->getObjPtr();

  Relationship * p_rel_ptr = rel_coll->pick();

  if ( ! is_valid_assoc_relationship( id, from, to, assoc, p_rel_ptr,
         p_left_object_ptr, p_ass_object_ptr, p_right_object_ptr ) )
    {
      return;
    }

  id->setObjPtr( (persObjPtr) rel_ptr );
  id->set_Id( rel_ptr->get_relationship_id() );

  return;
}



//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
//
// Function: validate_ee_kl
// Description: Validate the ee keyletters in the dbms_config database
//              
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// Validate the external entity key letters
void P_checkOSDB::validate_ee_kl (AST *kl)
{
  mc_dbms_List< D_external_entity * > ee_coll;
  
  // Get the first EE in the collection of all EEs
  D_external_entity * ee_ptr;
  FIRST_ELEMENT( ee_ptr,
                D_external_entity,
                m_current_domain_ptr->get_current_dd_srm_scm_sam_ptr()->
                get_external_entity_coll_ptr(),
                c1 );
  
  // Check all EEs for a match
  while ( ee_ptr )
    {
      if ( ee_ptr->external_entity_key_letters() == kl->getVcharText() )
	{
          ee_coll.insert( ee_ptr );
	}
      NEXT_ELEMENT( ee_ptr, c1 );
    }

  int card = ee_coll.cardinality();
  
  if ( card == 0 )
    {
      // If there is no EE with the keyletters, generate this error
      AL_PARSE_ERR1( kl, AL_GETMSG(ERR,100,1), kl->getVcharText() )
      return;
    }
  else if ( card > 1 )
    {
      // If there's more than one EE with keyletters kl, generate this error
      AL_PARSE_ERR1( kl, AL_GETMSG(ERR,021,1), kl->getVcharText() )
      return;
    }

  ee_ptr = ee_coll.pick();

  kl->setObjPtr( (persObjPtr) ee_ptr );
  kl->set_Id( ee_ptr->get_id() );

  return;
}


//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
//
// Function: validate_ee_event_data_items
// Description: Validate the ee event data items in the dbms_config database
//              
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// Validate the external entity event data item name
void P_checkOSDB::validate_ee_event_data_items( AST *event,
                                               AST *data_items)
{
  // Get the event pointer and use it to get the supplemental data pointer
  D_external_entity_event *event_ptr = (D_external_entity_event *) event->getObjPtr();

  mc_dbms_Set< D_external_entity_event_data * > *ee_event_data_coll =
    event_ptr->get_external_entity_event_data_coll_ptr();

  int card = ee_event_data_coll->cardinality();

  // If there are no data items, make sure the data item collection is empty
  if ( data_items == NULL )
    {
      if ( card != 0 )
        {
          // Generate this error if some data items are missing
          // Should probably make a new error message listing the data items
          //  that are missing. HACK! - PMB
          AL_PARSE_ERR1( event, AL_GETMSG(ERR,071,1), event->getVcharText() )
          return;
        }
    }
  else
    {
      // If there are more data items in the database then were found in
      //  the parse, raise an error.
      if ( card > data_items->nsiblings() )
        {
          AL_PARSE_ERR1( data_items, AL_GETMSG(ERR,071,1), event->getVcharText() )
          return;
        }

      D_external_entity_event_data *ee_event_data_ptr = NULL;
      D_external_entity_event_data_item *ee_edi_ptr = NULL;
      FIRST_ELEMENT( ee_event_data_ptr,
                    D_external_entity_event_data,
                    ee_event_data_coll,
                    cursor );

      bool found = FALSE;
      AST * data_item_cursor;
      
      // Loop through the supplemental data items from the database
      while( ee_event_data_ptr != NULL)
        {
          // Initialize parse data item cursor to point to head of AST
          data_item_cursor = data_items;
          found = FALSE;

          // The the EE event data item for this event data
          ee_edi_ptr =
            ee_event_data_ptr->get_external_entity_event_data_item_ptr();
      
          // Loop through the data items from the parse and
          // compare them to the one from the database
          while ( data_item_cursor != NULL )
            {
              if ( ee_event_data_ptr->get_external_entity_event_data_item_ptr()->
                  name() == data_item_cursor->getVcharText() )
                {
                  found = TRUE;
                  t_core_data_type db_datatype;
                  if ( verify_datatype ( 
					  ee_event_data_ptr->
                          get_external_entity_event_data_item_ptr()->
						  get_dd_srm_scm_sam_ptr (),
					  ee_event_data_ptr->
                          get_external_entity_event_data_item_ptr()->get_data_type_id(),
					  data_item_cursor->child(), db_datatype) )
                    {
                      AL_PARSE_ERR1( data_item_cursor, AL_GETMSG(ERR,281,1),
                                    data_item_cursor->getVcharText() );
                      return;
                    }
                  data_item_cursor->setDatatype( db_datatype );
                  data_item_cursor->setObjPtr( (persObjPtr) ee_event_data_ptr->
                              get_external_entity_event_data_item_ptr() );
                  data_item_cursor->set_Id( ee_event_data_ptr->
                              get_external_entity_event_data_item_ptr()->get_id() );
                  break;
                }
              data_item_cursor = (AST *) data_item_cursor->right();
            }

          // If the data item was not found in the parameter list, report an error
          if ( ! found )
            {
              // Generate this error if some data items are missing
              // Should probably make a new error message listing the data item
              //  that was missing. HACK! - PMB
              AL_PARSE_ERR1( data_items, AL_GETMSG(ERR,071,1), event->getVcharText() )
              return;
            }
          NEXT_ELEMENT( ee_event_data_ptr, cursor );
        }
      
      // If execution gets here, all the data items from the database
      // were found in the parse data items.

      // If there are more data items in the parse then were found in the
      // database, that means there were redundant or extra data items in the
      // supplemental data item list found by the parse.  Generate an error.
      if ( card < data_items->nsiblings() )
        {
          // Initialize the cursor to the head of the data item AST
          data_item_cursor = data_items;
          
          // Loop through the supplemental data items from the parse
          while( data_item_cursor != NULL )
            {

              // Get the first supp data item from the database
              ee_event_data_ptr = NULL;
              FIRST_ELEMENT( ee_event_data_ptr,
                            D_external_entity_event_data,
                            ee_event_data_coll,
                            cursor );

              // Loop through all the items to find a match
              found = FALSE;
              while( ee_event_data_ptr )
                {
                  if ( ee_event_data_ptr->get_external_entity_event_data_item_ptr()->
                      name() == data_item_cursor->getVcharText() )
                    {
                      found = TRUE;
                      break;
                    }
                  NEXT_ELEMENT( ee_event_data_ptr, cursor );
                }
              // If the supp data item wasn't found in the dbms_config database,
              //  raise an error stating that it isn't associated with the event
              if ( ! found )
                {
                  // Generate this error if the given data item is not associated with the event
                  AL_PARSE_ERR2( data_item_cursor, AL_GETMSG(ERR,074,2),
                                data_item_cursor->getVcharText(), event->getVcharText() )
                  return;
                }
              
              data_item_cursor = (AST *) data_item_cursor->right();
            }
          
          // If it gets out of the while loop without returning, there must be
          // a redundant data item, so report the error
          AL_PARSE_ERR1( data_items, AL_GETMSG(ERR,072,1), event->getVcharText() )
          return;
        }
    }
}


//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
//
// Function: validate_bridge
// Description: Insures that the bridge exists in the dbms_config database.
//              Checks
//              
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
void P_checkOSDB::validate_bridge( AST *bridge,
                                   AST *ee)
{
  D_external_entity *ee_ptr = (D_external_entity *) ee->getObjPtr();
  
  D_bridge *bridge_ptr;
  bool found = FALSE;
  FIRST_ELEMENT( bridge_ptr, D_bridge, ee_ptr->get_ro_bridge_coll_ptr(), c );
  while ( bridge_ptr && ! found )
    {
       if ( bridge_ptr->get_name() == bridge->getVcharText() )
          found = TRUE;
       else
	  {
	     NEXT_ELEMENT( bridge_ptr, c );
	  }
    }

  if ( bridge_ptr == NULL )
    {
      // Generate this if the bridge does not exist for this EE
      AL_PARSE_ERR2( bridge, AL_GETMSG(ERR,226,2), bridge->getVcharText(), ee->getVcharText() );
      return;
    }
  
  bridge->setObjPtr( (persObjPtr) bridge_ptr );
  bridge->set_Id( bridge_ptr->get_id() );

  // Get the core data type of the bridge
  Id bridge_return_type_id = bridge_ptr->get_return_type_id();
  D_data_type * bridge_data_type_ptr = 
    AL_Generic_finds::find_data_type_by_id( m_current_domain_ptr,
       bridge_return_type_id );
  if ( bridge_data_type_ptr->get_enum_data_type_ptr() != 0 )
  {
	  bridge->setDatatype( ENUMERATION_DATATYPE );
  }
  else
  {
	D_core_data_type * bridge_core_data_type_ptr =
	    AL_Generic_finds::find_core_data_type_by_id( m_current_domain_ptr,
		   bridge_return_type_id );
	if ( bridge_core_data_type_ptr == 0 )
    {
      // Generate this if the bridge has not been assigned a return type
      AL_PARSE_ERR2( bridge, AL_GETMSG(ERR,220,2), bridge->getVcharText(), ee->getVcharText() )
      return;
    }

	// Set the data type for the bridge AST
    bridge->setDatatype( (t_core_data_type) bridge_core_data_type_ptr->
                        get_core_data_type_type() );
  }
}


//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
//
// Function: validate_bridge_data_items
// Description: Validate the bridge data items in the dbms_config database
//              
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// Validate the bridge data items
void P_checkOSDB::validate_bridge_data_items( AST *bridge,
                                              AST *data_items)
{
  // Get the event pointer and use it to get the supplemental data pointer
  D_bridge *bridge_ptr = (D_bridge *) bridge->getObjPtr();
  mc_dbms_List< D_bridge_parm * > * bridge_parm_coll =
    bridge_ptr->get_parameter_coll_ptr();

  // Get the number of data items from the database
  int card = bridge_parm_coll->cardinality();

  // If there are no data items, make sure the data item collection is empty
  if ( data_items == NULL )
    {
      if ( card != 0 )
        {
          // Generate this error if some data items are missing
          // Should probably make a new error message listing the data items
          //  that are missing. HACK! - PMB
          AL_PARSE_ERR2( bridge, AL_GETMSG(ERR,221,2),
                         bridge->getVcharText(),
                         bridge_ptr->get_external_entity_ptr()->
                         external_entity_name().char_ptr())
          return;
        }
      return;
    }
  else
    {
      // If there are more data items in the database then were found in
      //  the parse, raise an error.
      if ( card > data_items->nsiblings() )
        {
          AL_PARSE_ERR2( data_items, AL_GETMSG(ERR,221,2),
                         bridge_ptr->get_name().char_ptr(),
                         bridge_ptr->get_external_entity_ptr()->
                         external_entity_name().char_ptr() )
          return;
        }

      D_bridge_parm *bridge_parm_ptr = NULL;
      FIRST_ELEMENT( bridge_parm_ptr,
                    D_bridge_parm,
                    bridge_parm_coll,
                    cursor );

      bool found = FALSE;
      AST * data_item_cursor;
      
      // Loop through the supplemental data items from the database
      while( bridge_parm_ptr != NULL )
        {
          // Initialize parse data item cursor to point to head of AST
          data_item_cursor = data_items;
          found = FALSE;

          // Loop through the data items from the parse and
          // compare them to the one from the database
          while ( data_item_cursor != NULL )
            {
              if ( bridge_parm_ptr->get_name() == data_item_cursor->getVcharText() )
                {
                  found = TRUE;
                  t_core_data_type db_datatype;
                  if ( verify_datatype ( bridge_parm_ptr->get_dd_srm_scm_sam_ptr (),
					  bridge_parm_ptr->get_data_type_id(),
					  data_item_cursor->child(), db_datatype) )
                    {
                      AL_PARSE_ERR1( data_item_cursor, AL_GETMSG(ERR,278,1),
                                    data_item_cursor->getVcharText() );
                      return;
                    }

                  if ( bridge_parm_ptr->is_by_reference() &&
                       data_item_cursor->child()->isReadOnly() )
                  {
                      AL_PARSE_ERR1( data_item_cursor, AL_GETMSG(ERR,251,1),
                                    data_item_cursor->getVcharText() );
                      return;
                  }

                  data_item_cursor->setDatatype( db_datatype );
                  data_item_cursor->setObjPtr( (persObjPtr) bridge_parm_ptr );
                  data_item_cursor->set_Id( bridge_parm_ptr->get_id() );
                  break;
                }
              data_item_cursor = (AST *) data_item_cursor->right();
            }

          // If the data item was not found in the parameter list, report an error
          if ( ! found )
            {
              // Generate this error if some data items are missing
              // Should probably make a new error message listing the data item
              //  that was missing. HACK! - PMB
              AL_PARSE_ERR2( data_items, AL_GETMSG(ERR,221,2),
                             bridge_ptr->get_name().char_ptr(),
                             bridge_ptr->get_external_entity_ptr()->
                             external_entity_name().char_ptr() )
              return;
            }
          NEXT_ELEMENT( bridge_parm_ptr, cursor );
        }
      
      // If execution gets here, all the data items from the database
      // were found in the parse data items.

      // If there are more data items in the parse then were found in the
      // database, that means there were redundant or extra data items in the
      // supplemental data item list found by the parse.  Generate an error.
      if ( card < data_items->nsiblings() )
        {
          // Initialize the cursor to the head of the data item AST
          data_item_cursor = data_items;
          
          // Loop through the supplemental data items from the parse
          while( data_item_cursor != NULL )
            {

              // Get the first supp data item from the database
              bridge_parm_ptr = NULL;
              FIRST_ELEMENT( bridge_parm_ptr,
                            D_bridge_parm,
                            bridge_parm_coll,
                            cursor );

              // Loop through all the items to find a match
              found = FALSE;
              while( bridge_parm_ptr )
                {
                  if ( bridge_parm_ptr->get_name() == data_item_cursor->getVcharText() )
                    {
                      found = TRUE;
                      break;
                    }
                  NEXT_ELEMENT( bridge_parm_ptr, cursor );
                }
              // If the supp data item wasn't found in the dbms_config database,
              //  raise an error stating that it isn't associated with the bridge
              if ( ! found )
                {
                  // Generate this error if the given data item is not associated
                  //  with the bridge
                  AL_PARSE_ERR2( data_item_cursor, AL_GETMSG(ERR,228,2),
                     data_item_cursor->getVcharText(), bridge_ptr->get_name().char_ptr() )
                  return;
                }
              
              data_item_cursor = (AST *) data_item_cursor->right();
            }
          
          // If it gets out of the while loop without returning, there must be
          // a redundant data item, so report the error
          AL_PARSE_ERR2( data_items, AL_GETMSG(ERR,239,2),
                 bridge_ptr->get_name().char_ptr(),
                 bridge_ptr->get_external_entity_ptr()->
                 external_entity_name().char_ptr() )
          return;
        }
    }
}


//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
//
// Function: validate_bridge_data_items
// Description: Validate the bridge data items in the dbms_config database
//              
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
void P_checkOSDB::validate_bridge_data_item( AST *data_item,
                                             AST *bridge,
                                             Assign_Val_e isLval )
{
  // Get the event pointer and use it to get the supplemental data pointer
  D_bridge *bridge_ptr = (D_bridge *) bridge->getObjPtr();
  mc_dbms_List< D_bridge_parm * > * bridge_parm_coll =
    bridge_ptr->get_parameter_coll_ptr();

  D_bridge_parm *bridge_parm_ptr = NULL;
  FIRST_ELEMENT( bridge_parm_ptr,
                D_bridge_parm,
                bridge_parm_coll,
                cursor );
  
  bool found = FALSE;
  // Loop through the supplemental data items from the database
  while( bridge_parm_ptr )
    {
      if ( bridge_parm_ptr->get_name() == data_item->getVcharText() )
        {
          found = TRUE;
          break;
        }
      NEXT_ELEMENT( bridge_parm_ptr, cursor );
    }

  if ( ! found )
    {
      AL_PARSE_ERR2( data_item, AL_GETMSG(ERR,228,2),
                    data_item->getVcharText(),
                    bridge_ptr->get_name().char_ptr() );
      return;
    }

  if ( isLval == ASSIGN_LVAL &&
       ! bridge_parm_ptr->is_by_reference() )
  {
      AL_PARSE_ERR1( data_item, AL_GETMSG(ERR,250,1),
                    data_item->getVcharText() );
      return;
  }

  data_item->setObjPtr( (persObjPtr) bridge_parm_ptr );
  data_item->set_Id( bridge_parm_ptr->get_id() );
  data_item->setDatatype( (t_core_data_type) bridge_parm_ptr->
                         get_core_data_type_type() );
  if ( bridge_parm_ptr->is_by_reference() )
  {
      // Yes, this is the one to change!
      bridge->setReadOnly( FALSE );
  }
  return;
}



//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
//
// Function: validate_synch_svc
// Description: Validate the synchronous service in the dbms_config database
//              
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// Validate the synchronous service
void P_checkOSDB::validate_synch_svc (AST *ss)
{
  mc_dbms_List< D_synchronous_service * > ss_coll;
  
  // Get the first SS in the collection of all SSs
  D_synchronous_service *ss_ptr;
  FIRST_ELEMENT( ss_ptr,
                 D_synchronous_service,
                 m_current_domain_ptr->get_current_dd_srm_scm_sam_ptr()->
                 get_synch_service_coll_ptr(),
                 c1 );
  
  // Check all SSs for a match
  while ( ss_ptr )
    {
      if ( ss_ptr->get_name() == ss->getVcharText() )
        {
          ss_coll.insert( ss_ptr );
        }
      NEXT_ELEMENT( ss_ptr, c1 );
    }

  int card = ss_coll.cardinality();
  
  if ( card == 0 )
    {
      // If there is no SS with the name, generate this error
      AL_PARSE_ERR1( ss, AL_GETMSG(ERR,247,1), ss->getVcharText() )
      return;
    }
  else if ( card > 1 )
    {
      // If there's more than one SS with name ss, generate this error
      AL_PARSE_ERR1( ss, AL_GETMSG(ERR,248,1), ss->getVcharText() )
      return;
    }

  ss_ptr = ss_coll.pick();

  ss->setObjPtr( (persObjPtr) ss_ptr );
  ss->set_Id( ss_ptr->get_id() );

  return;
}


//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
//
// Function: validate_synch_svc_data_items
// Description: Validate the synchronous service data items in the dbms_config
//              database
//
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// Validate the synchronous service data items
void P_checkOSDB::validate_synch_svc_data_items( AST *synch_svc,
                                                 AST *data_items)
{

  // Get the synch_svc pointer and use it to get the supplemental data pointer
  D_synchronous_service *synch_svc_ptr =
    (D_synchronous_service *) synch_svc->getObjPtr();
  mc_dbms_List< D_synchronous_service_parm * > *synch_svc_parm_coll =
    synch_svc_ptr->get_parameter_coll_ptr();

  // Get the number of data items from the database
  int card = synch_svc_parm_coll->cardinality();

  // If there are no data items, make sure the data item collection is empty
  if ( data_items == NULL )
    {
      if ( card != 0 )
        {
          // Generate this error if some data items are missing
          // Should probably make a new error message listing the data items
          //  that are missing. HACK! - PMB
          AL_PARSE_ERR1( synch_svc, AL_GETMSG(ERR,201,1),
                         synch_svc_ptr->get_name().char_ptr() )
          return;
        }
      return;
    }
  else
    {
      // If there are more data items in the database then were found in
      //  the parse, raise an error.
      if ( card > data_items->nsiblings() )
        {
          AL_PARSE_ERR1( data_items, AL_GETMSG(ERR,201,1),
                         synch_svc_ptr->get_name().char_ptr() )
          return;
        }

      D_synchronous_service_parm *synch_svc_parm_ptr = NULL;
      FIRST_ELEMENT( synch_svc_parm_ptr,
                    D_synchronous_service_parm,
                    synch_svc_parm_coll,
                    cursor );

      bool found = FALSE;
      AST * data_item_cursor;
      

      // Loop through the supplemental data items from the database
      while( synch_svc_parm_ptr != NULL )
        {
          // Initialize parse data item cursor to point to head of AST
          data_item_cursor = data_items;
          found = FALSE;

          // Loop through the data items from the parse and
          // compare them to the one from the database
          while ( data_item_cursor != NULL )
            {
              if ( synch_svc_parm_ptr->get_name() == data_item_cursor->getVcharText() )
                {
                  found = TRUE;
                  t_core_data_type db_datatype;
                  if ( verify_datatype ( synch_svc_parm_ptr->get_dd_srm_scm_sam_ptr (),
					  synch_svc_parm_ptr->get_data_type_id(),
					  data_item_cursor->child(), db_datatype) )
                    {
                      AL_PARSE_ERR1( data_item_cursor, AL_GETMSG(ERR,278,1),
                                     data_item_cursor->getVcharText() );
                      return;
                    }

                  if ( synch_svc_parm_ptr->is_by_reference() &&
                       data_item_cursor->child()->isReadOnly() )
                  {
                      AL_PARSE_ERR1( data_item_cursor, AL_GETMSG(ERR,251,1),
                                    data_item_cursor->getVcharText() );
                      return;
                  }

                  data_item_cursor->setDatatype( db_datatype );
                  data_item_cursor->setObjPtr( (persObjPtr) synch_svc_parm_ptr );
                  data_item_cursor->set_Id( synch_svc_parm_ptr->get_id() );
                  break;
                }
              data_item_cursor = (AST *) data_item_cursor->right();
            }

          // If the data item was not found in the parameter list, report an error
          if ( ! found )
            {
              // Generate this error if some data items are missing
              // Should probably make a new error message listing the data item
              //  that was missing. HACK! - PMB
              AL_PARSE_ERR1( data_items, AL_GETMSG(ERR,201,1),
                             synch_svc_ptr->get_name().char_ptr() )
              return;
            }
          NEXT_ELEMENT( synch_svc_parm_ptr, cursor );
        }
      
      // If execution gets here, all the data items from the database
      // were found in the parse data items.

      // If there are more data items in the parse then were found in the
      // database, that means there were redundant or extra data items in the
      // supplemental data item list found by the parse.  Generate an error.
      if ( card < data_items->nsiblings() )
        {
          // Initialize the cursor to the head of the data item AST
          data_item_cursor = data_items;
          
          // Loop through the supplemental data items from the parse
          while( data_item_cursor != NULL )
            {

              // Get the first supp data item from the database
              synch_svc_parm_ptr = NULL;
              FIRST_ELEMENT( synch_svc_parm_ptr,
                            D_synchronous_service_parm,
                            synch_svc_parm_coll,
                            cursor );

              // Loop through all the items to find a match
              found = FALSE;
              while( synch_svc_parm_ptr )
                {
                  if ( synch_svc_parm_ptr->get_name() == data_item_cursor->getVcharText() )
                    {
                      found = TRUE;
                      break;
                    }
                  NEXT_ELEMENT( synch_svc_parm_ptr, cursor );
                }
              // If the supp data item wasn't found in the dbms_config database,
              //  raise an error stating that it isn't associated with the synchronous service
              if ( ! found )
                {
                  // Generate this error if the given data item is not associated
                  //  with the synchronous service
                  AL_PARSE_ERR2( data_item_cursor, AL_GETMSG(ERR,200,2),
                     data_item_cursor->getVcharText(), synch_svc_ptr->get_name().char_ptr() )
                  return;
                }
              
              data_item_cursor = (AST *) data_item_cursor->right();
            }
          
          // If it gets out of the while loop without returning, there must be
          // a redundant data item, so report the error
          AL_PARSE_ERR1( data_items, AL_GETMSG(ERR,202,1),
                         synch_svc_ptr->get_name().char_ptr() )
          return;
        }
    }
}


//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
//
// Function: validate_synch_svc_data_item
// Description: Validate the synchronous service data item in the dbms_config
//              database
//
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// Validate the synchronous service data item
void P_checkOSDB::validate_synch_svc_data_item( AST *data_item,
                                                AST *synch_svc,
                                                Assign_Val_e isLval)
{

  // Get the synchronous service pointer and use it to get the supplemental data pointer
  D_synchronous_service *synch_svc_ptr =
    (D_synchronous_service *) synch_svc->getObjPtr();
  mc_dbms_List< D_synchronous_service_parm * > *synch_svc_parm_coll =
    synch_svc_ptr->get_parameter_coll_ptr();


  D_synchronous_service_parm *synch_svc_parm_ptr = NULL;
  FIRST_ELEMENT( synch_svc_parm_ptr,
                D_synchronous_service_parm,
                synch_svc_parm_coll,
                cursor );
  
  bool found = FALSE;
  // Loop through the supplemental data items from the database
  while( synch_svc_parm_ptr )
    {
      if ( synch_svc_parm_ptr->get_name() == data_item->getVcharText() )
        {
          found = TRUE;
          break;
        }
      NEXT_ELEMENT( synch_svc_parm_ptr, cursor );
    }

  if ( ! found )
    {
      AL_PARSE_ERR2( data_item, AL_GETMSG(ERR,203,2),
                     data_item->getVcharText(),
                     synch_svc_ptr->get_name().char_ptr() );
      return;
    }

  if ( isLval == ASSIGN_LVAL &&
       ! synch_svc_parm_ptr->is_by_reference() )
  {
      AL_PARSE_ERR1( data_item, AL_GETMSG(ERR,250,1),
                    data_item->getVcharText() );
      return;
  }

  data_item->setObjPtr( (persObjPtr) synch_svc_parm_ptr );
  data_item->set_Id( synch_svc_parm_ptr->get_id() );
  data_item->setDatatype( (t_core_data_type) synch_svc_parm_ptr->
                         get_core_data_type_type() );
  if ( synch_svc_parm_ptr->is_by_reference() )
  {
      // Yes, this is the one to change!
      synch_svc->setReadOnly( FALSE );
  }
  return;
}

//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
//
// Function: validate_transformer
// Description: Validate the transformer in the dbms_config database
//              
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// Validate the transformer name
void P_checkOSDB::validate_transformer( AST *transformer,
                                        AST *obj,
                                        bool isInstanceBased )
{
  D_transformer *transformer_ptr = ((Object *)obj->getObjPtr())->
    find_transformer_by_name( transformer->getVcharText() );
  
  if ( ! transformer_ptr )
    {
      // Generate this if the transformer does not exist for this object
      AL_PARSE_ERR2( transformer, AL_GETMSG(ERR,227,2), transformer->getVcharText(),
                    obj->getVcharText() )
      return;
    }
  
  Id return_type_id = transformer_ptr->get_return_type_id();
  D_data_type * data_type_ptr = 
    AL_Generic_finds::find_data_type_by_id( m_current_domain_ptr,
       return_type_id );
  if ( data_type_ptr->get_enum_data_type_ptr() != 0 )
  {
	  transformer->setDatatype( ENUMERATION_DATATYPE );
  }
  else
  {
	  D_core_data_type * trans_core_data_type_ptr =
		AL_Generic_finds::find_core_data_type_by_id( m_current_domain_ptr,
		   return_type_id );
  
	  if ( trans_core_data_type_ptr == 0 )
		{
		  // Generate this if the transformer has not been assigned a return type
		  AL_PARSE_ERR2( transformer, AL_GETMSG(ERR,230,2), transformer->getVcharText(),
						 obj->getVcharText() )
		  return;
		}
  
	  transformer->setDatatype( (t_core_data_type) trans_core_data_type_ptr->
							   get_core_data_type_type() );
  }

  if ( isInstanceBased )
    {
      // AL usage dictates an instance-based transformer be used
      if ( ! transformer_ptr->is_instance_based() )
        {
          // Transformer must be instance-based but is not invoked as such
          AL_PARSE_ERR2( transformer,
                         AL_GETMSG(ERR,244,2),
                         transformer->getVcharText(),
                         transformer->getVcharText() )
          return;
        }
    }
  else
    {
      // AL usage dictates a non-instance-based transformer be used
      if ( transformer_ptr->is_instance_based() )
        {
          // Transformer must not be instance-based but is invoked as such
          AL_PARSE_ERR2( transformer,
                         AL_GETMSG(ERR,243,2),
                         transformer->getVcharText(),
                         transformer->getVcharText() )
          return;
        }
    }

  transformer->setObjPtr( (persObjPtr) transformer_ptr );
  transformer->set_Id( transformer_ptr->get_id() );
}



//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
//
// Function: validate_transformer_data_items
// Description: Validate the transformer data items in the dbms_config
//              database
//
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// Validate the transformer data items
void P_checkOSDB::validate_transformer_data_items( AST *transformer,
                                                   AST *data_items)
{

  // Get the transformer pointer and use it to get the supplemental data pointer
  D_transformer *transformer_ptr = (D_transformer *) transformer->getObjPtr();
  mc_dbms_List< D_transformer_parm * > *transformer_parm_coll =
    transformer_ptr->get_parameter_coll_ptr();

  // Get the number of data items from the database
  int card = transformer_parm_coll->cardinality();

  // If there are no data items, make sure the data item collection is empty
  if ( data_items == NULL )
    {
      if ( card != 0 )
        {
          // Generate this error if some data items are missing
          // Should probably make a new error message listing the data items
          //  that are missing. HACK! - PMB
          AL_PARSE_ERR2( transformer, AL_GETMSG(ERR,234,2),
                         transformer_ptr->get_name().char_ptr(),
                         transformer_ptr->get_object_ptr()->
                         get_object_name().char_ptr())
          return;
        }
      return;
    }
  else
    {
      // If there are more data items in the database then were found in
      //  the parse, raise an error.
      if ( card > data_items->nsiblings() )
        {
          AL_PARSE_ERR2( data_items, AL_GETMSG(ERR,234,2),
                         transformer_ptr->get_name().char_ptr(),
                         transformer_ptr->get_object_ptr()->
                         get_object_name().char_ptr())
          return;
        }

      D_transformer_parm *transformer_parm_ptr = NULL;
      FIRST_ELEMENT( transformer_parm_ptr,
                    D_transformer_parm,
                    transformer_parm_coll,
                    cursor );

      bool found = FALSE;
      AST * data_item_cursor;
      
      // Loop through the supplemental data items from the database
      while( transformer_parm_ptr != NULL )
        {
          // Initialize parse data item cursor to point to head of AST
          data_item_cursor = data_items;
          found = FALSE;

          // Loop through the data items from the parse and
          // compare them to the one from the database
          while ( data_item_cursor != NULL )
            {
              if ( transformer_parm_ptr->get_name() == data_item_cursor->getVcharText() )
                {
                  found = TRUE;
                  t_core_data_type db_datatype;
                  if ( verify_datatype ( transformer_ptr->get_dd_srm_scm_sam_ptr (),
					  transformer_parm_ptr->get_data_type_id(),
					  data_item_cursor->child(), db_datatype) )
                    {
                      AL_PARSE_ERR1( data_item_cursor, AL_GETMSG(ERR,278,1),
                                     data_item_cursor->getVcharText() );
                      return;
                    }

                  if ( transformer_parm_ptr->is_by_reference() &&
                       data_item_cursor->child()->isReadOnly() )
                  {
                      AL_PARSE_ERR1( data_item_cursor, AL_GETMSG(ERR,251,1),
                                    data_item_cursor->getVcharText() );
                      return;
                  }

                  data_item_cursor->setDatatype( db_datatype );
                  data_item_cursor->setObjPtr( (persObjPtr) transformer_parm_ptr );
                  data_item_cursor->set_Id( transformer_parm_ptr->get_id() );
                  break;
                }
              data_item_cursor = (AST *) data_item_cursor->right();
            }

          // If the data item was not found in the parameter list, report an error
          if ( ! found )
            {
              // Generate this error if some data items are missing
              // Should probably make a new error message listing the data item
              //  that was missing. HACK! - PMB
              AL_PARSE_ERR2( data_items, AL_GETMSG(ERR,234,2),
                             transformer_ptr->get_name().char_ptr(),
                             transformer_ptr->get_object_ptr()->
                             get_object_name().char_ptr())
              return;
            }
          NEXT_ELEMENT( transformer_parm_ptr, cursor );
        }
      
      // If execution gets here, all the data items from the database
      // were found in the parse data items.

      // If there are more data items in the parse then were found in the
      // database, that means there were redundant or extra data items in the
      // supplemental data item list found by the parse.  Generate an error.
      if ( card < data_items->nsiblings() )
        {
          // Initialize the cursor to the head of the data item AST
          data_item_cursor = data_items;
          
          // Loop through the supplemental data items from the parse
          while( data_item_cursor != NULL )
            {

              // Get the first supp data item from the database
              transformer_parm_ptr = NULL;
              FIRST_ELEMENT( transformer_parm_ptr,
                            D_transformer_parm,
                            transformer_parm_coll,
                            cursor );

              // Loop through all the items to find a match
              found = FALSE;
              while( transformer_parm_ptr )
                {
                  if ( transformer_parm_ptr->get_name() == data_item_cursor->getVcharText() )
                    {
                      found = TRUE;
                      break;
                    }
                  NEXT_ELEMENT( transformer_parm_ptr, cursor );
                }
              // If the supp data item wasn't found in the dbms_config database,
              //  raise an error stating that it isn't associated with the transformer
              if ( ! found )
                {
                  // Generate this error if the given data item is not associated
                  //  with the transformer
                  AL_PARSE_ERR2( data_item_cursor, AL_GETMSG(ERR,228,2),
                     data_item_cursor->getVcharText(), transformer_ptr->get_name().char_ptr() )
                  return;
                }
              
              data_item_cursor = (AST *) data_item_cursor->right();
            }
          
          // If it gets out of the while loop without returning, there must be
          // a redundant data item, so report the error
          AL_PARSE_ERR2( data_items, AL_GETMSG(ERR,240,2),
                         transformer_ptr->get_name().char_ptr(),
                         transformer_ptr->get_object_ptr()->
                         get_object_name().char_ptr() )
          return;
        }
    }
}


//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
//
// Function: validate_transformer_data_item
// Description: Validate the transformer data item in the dbms_config
//              database
//
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// Validate the transformer data item
void P_checkOSDB::validate_transformer_data_item( AST *data_item,
                                                  AST *transformer,
                                                  Assign_Val_e isLval)
{

  // Get the transformer pointer and use it to get the supplemental data pointer
  D_transformer *transformer_ptr = (D_transformer *) transformer->getObjPtr();
  mc_dbms_List< D_transformer_parm * > *transformer_parm_coll =
    transformer_ptr->get_parameter_coll_ptr();


  D_transformer_parm *transformer_parm_ptr = NULL;
  FIRST_ELEMENT( transformer_parm_ptr,
                D_transformer_parm,
                transformer_parm_coll,
                cursor );
  
  bool found = FALSE;
  // Loop through the supplemental data items from the database
  while( transformer_parm_ptr )
    {
      if ( transformer_parm_ptr->get_name() == data_item->getVcharText() )
        {
          found = TRUE;
          break;
        }
      NEXT_ELEMENT( transformer_parm_ptr, cursor );
    }

  if ( ! found )
    {
      AL_PARSE_ERR2( data_item, AL_GETMSG(ERR,229,2),
                     data_item->getVcharText(),
                     transformer_ptr->get_name().char_ptr() );
      return;
    }

  if ( isLval == ASSIGN_LVAL &&
       ! transformer_parm_ptr->is_by_reference() )
  {
      AL_PARSE_ERR1( data_item, AL_GETMSG(ERR,250,1),
                    data_item->getVcharText() );
      return;
  }

  data_item->setObjPtr( (persObjPtr) transformer_parm_ptr );
  data_item->set_Id( transformer_parm_ptr->get_id() );
  data_item->setDatatype( (t_core_data_type) transformer_parm_ptr->
                         get_core_data_type_type() );
  if ( transformer_parm_ptr->is_by_reference() )
  {
      // yes, this is really the one to change!
      transformer->setReadOnly( FALSE );
  }

  return;
}


//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
//
// Function: validate_obj_is_assigner
// Description: Validate the assigner in the dbms_config database
//              
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// Validate that object has an assigner state model
void P_checkOSDB::validate_obj_is_assigner( AST *kl )
{
  // All the checking here is actually done in validate_assigner_event_label
}



//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
//
// Function: validate_obj_has_creation_state
// Description: Validate that the object in the dbms_config database has a
//              creation state.
//              
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// Validate that object has a creation state
void  P_checkOSDB::validate_obj_has_creation_state( AST *kl )
{
  // All the necessary code is in validate_creator_event_label
}



//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
//
// Function: validate_ee_event_label
// Description: Validate the ee event label in the dbms_config database
//              
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// Validate that the event label can be received by the external entity
void P_checkOSDB::validate_ee_event_label( AST *label,
                                           AST *ee )
{
  void * ee_or_sm_event_ptr = 0;
  
  Smart_ptr< mc_dbms_Bag< D_external_entity_event * > > ee_event_coll =
    AL_Generic_finds::find_external_entity_event_by_label(
       m_current_domain_ptr, label->getVcharText() );

  int card = ee_event_coll->cardinality();
  if ( card == 0 )
    {
      // If event can't be found for this ee, generate this error message
      AL_PARSE_ERR2( label, AL_GETMSG(ERR,062,2), label->getVcharText(), ee->getVcharText())
      return;
    }
  else if ( card > 1 )
    {
      // If multiple events with the same label are found for this EE,
      // generate this error message
      AL_PARSE_ERR1( label, AL_GETMSG(ERR,020,1), label->getVcharText() )
      return;
    }

  label->setObjPtr( (persObjPtr) ee_event_coll->pick() );
  label->set_Id( (ee_event_coll->pick())->get_id() );

  return;
}


//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
//
// Function: validate_assigner_event_label
// Description: Validate the assigner event label in the dbms_config
//              database
//
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// Validate the event label for an assigner
void P_checkOSDB::validate_assigner_event_label( AST *label,
                                                 AST *to_obj )
{
  Object *object_ptr = (Object *) to_obj->getObjPtr();
  Id object_id = object_ptr->get_id();

  D_sm_spt_pm * object_sm_spt_pm_ptr = object_ptr->get_assigner_sm_spt_pm_ptr();

  if ( object_sm_spt_pm_ptr == 0 )
    {
      // Generate this if to_obj->objPtr does not have an assigner state model
      AL_PARSE_ERR1( to_obj, AL_GETMSG(ERR,151,1), to_obj->getVcharText() )
      return;
    }

  bool found_event_ptr = FALSE;
  D_sm_event * event_ptr;
  FIRST_ELEMENT( event_ptr,
                D_sm_event,
                object_sm_spt_pm_ptr->get_sm_event_coll_ptr(),
                c1 );

  while ( event_ptr && !found_event_ptr )
    {
      if ( event_ptr->get_derived_event_label() == label->getVcharText() )
        {
          found_event_ptr = TRUE;
        }
      else
        {
          NEXT_ELEMENT( event_ptr, c1 );
        }
    }

  if ( event_ptr == NULL )
    {
      AL_PARSE_ERR2( label, AL_GETMSG(ERR,065,2), label->getVcharText(), to_obj->getVcharText() );
      return;
    }

  D_sm_spt_pm * event_sm_spt_pm_ptr = event_ptr->get_sm_spt_pm_ptr();

  if ( event_sm_spt_pm_ptr->get_id() != object_sm_spt_pm_ptr->get_id() )
    {
      // If the given event does not exist for this assigner, generate
      // this error message
      AL_PARSE_ERR2( label, AL_GETMSG(ERR,065,2), label->getVcharText(), to_obj->getVcharText() )
      return;
    }

  // Put the attribute pointer in the attr AST
  label->setObjPtr( (persObjPtr) event_ptr );
  label->set_Id( event_ptr->get_id() );

  return;
}


//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
//
// Function: validate_creator_event_label
// Description: Validate the creator event label in the dbms_config database
//              
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// Validate the creation event label
void P_checkOSDB::validate_creator_event_label( AST *label,
                                                AST *to_obj )
{
  Object * object_ptr = (Object *) to_obj->getObjPtr();

  // Get the instance state model
  D_sm_spt_pm * object_sm_spt_pm_ptr = object_ptr->get_instance_sm_spt_pm_ptr();
  if ( object_sm_spt_pm_ptr == 0 )
    {
      // Generate this if there is no instance state model to send creation event to
      AL_PARSE_ERR1( to_obj, AL_GETMSG(ERR,126,1), to_obj->getVcharText() );
      return;
    }

  D_sm_event * event_ptr;

  FIRST_ELEMENT( event_ptr,
                D_sm_event,
                object_sm_spt_pm_ptr->get_sm_event_coll_ptr (),
                cursor );
  
  // Check all events for a match
  while ( event_ptr )
    {
      if ( event_ptr->get_derived_event_label() == label->getVcharText() )
	{
          break;
	}
      NEXT_ELEMENT( event_ptr, cursor );
    }

  if ( event_ptr == 0 )
    {
      AL_PARSE_ERR1( label, AL_GETMSG(ERR,068,1), label->getVcharText() )
      return;
    }

  // Make sure this is a creation transition.
  if ( ! event_ptr->is_local_event() )
    {
      // If the given event is not a creation event for this object, generate
      // this error message
      AL_PARSE_ERR2( label, AL_GETMSG(ERR,066,2), label->getVcharText(), to_obj->getVcharText() );
      return;
    }
  else
    {
      D_local_event* local_event_ptr = event_ptr->get_sem_event_ptr()->get_local_event_ptr();
      if ( local_event_ptr->get_creation_transition_ptr() == 0 )
      {
          // If the given event is not a creation event for this object, generate
          // this error message
          AL_PARSE_ERR2( label, AL_GETMSG(ERR,066,2), label->getVcharText(), to_obj->getVcharText() );
          return;
      }
    }

  label->setObjPtr( (persObjPtr) event_ptr );
  label->set_Id( event_ptr->get_id() );
}


// Validate the enumerator for an enumeration
void P_checkOSDB::validate_enumerator( AST *enumeration,
                                   AST *enumerator)
{
  mc_dbms_List< D_enum_data_type * > edt_coll;
  
  // Get the first DT in the collection of all DTs
  D_data_type *dt_ptr;
  FIRST_ELEMENT( dt_ptr,
                 D_data_type,
                 m_current_domain_ptr->get_current_dd_srm_scm_sam_ptr()->
                 get_data_type_coll_ptr(),
                 c1 );
  
  // Check all DTs for a match
  while ( dt_ptr )
    {
      if ( dt_ptr->get_enum_data_type_ptr() != 0 &&
		   dt_ptr->name() == enumeration->getVcharText() )
        {
          edt_coll.insert( dt_ptr->get_enum_data_type_ptr() );
        }
      NEXT_ELEMENT( dt_ptr, c1 );
    }

  int card = edt_coll.cardinality();
  
  if ( card == 0 )
    {
      // If there is no EDT with the name, generate this error
      AL_PARSE_ERR1( enumeration, AL_GETMSG(ERR,290,1), enumeration->getVcharText() )
      return;
    }
  else if ( card > 1 )
    {
      // If there's more than one EDT with name enumeration, generate this error
      AL_PARSE_ERR1( enumeration, AL_GETMSG(ERR,291,1), enumeration->getVcharText() )
      return;
    }

  D_enum_data_type* edt_ptr = edt_coll.pick();

  enumeration->setObjPtr( (persObjPtr) edt_ptr );
  enumeration->set_Id( edt_ptr->get_id() );
  enumeration->setDatatype( ENUMERATION_DATATYPE );

  // Now validate that enumerator is part of enumeration
  mc_dbms_List< D_enumerator * > enum_coll;
  
  // Get the first Enum in the EDT
  D_enumerator *enum_ptr;
  FIRST_ELEMENT( enum_ptr,
                 D_enumerator,
                 edt_ptr->get_enumerator_coll_ptr(),
                 c2 );
  
  // Check all enums for a match
  while ( enum_ptr )
    {
      if ( enum_ptr->name() == enumerator->getVcharText() )
        {
          enum_coll.insert( enum_ptr );
        }
      NEXT_ELEMENT( enum_ptr, c2 );
    }

  card = enum_coll.cardinality();
  
  if ( card == 0 )
    {
      // If there is no enum with the name, generate this error
      AL_PARSE_ERR2( enumeration, AL_GETMSG(ERR,292,2), enumerator->getVcharText(), enumeration->getVcharText() )
      return;
    }
  else if ( card > 1 )
    {
      // If there's more than one enum with name enumerator, generate this error
      AL_PARSE_ERR2( enumeration, AL_GETMSG(ERR,293,2), enumerator->getVcharText(), enumeration->getVcharText() )
      return;
    }

  enum_ptr = enum_coll.pick();

  enumerator->setObjPtr( (persObjPtr) enum_ptr );
  enumerator->set_Id( enum_ptr->get_id() );
  enumerator->setDatatype( ENUMERATOR_DATATYPE );

}


  //------------------------------------------------------------
  // Query functions
  //------------------------------------------------------------


//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
//
// Function: is_valid_obj_kl
// Description: Verify existance of the object keyletters in the
//              dbms_config database
//
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// Determine if object keyletters is a valid object
bool P_checkOSDB::is_valid_obj_kl( AST *kl )
{
  Smart_ptr< mc_dbms_Bag< Object * > > object_coll =
    AL_Generic_finds::find_object_by_key_letters( m_current_domain_ptr,
                                                  kl->getVcharText() );
  
  int card = object_coll->cardinality();
  
  if ( card == 1 )
    {
      kl->setObjPtr( (persObjPtr) object_coll->pick() );
      kl->set_Id( object_coll->pick()->get_id() );
      return TRUE;
    }
  else
    return FALSE;
}


//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
//
// Function: is_valid_transformer
// Description: Check the transformer in the dbms_config database and set
//              the transformer AST objPtr to the transformer object.
//              
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// Determine if transformer is valid for this object
bool P_checkOSDB::is_valid_transformer( AST *transformer,
                                        AST *obj_obj,
                                        bool isInstanceBased )
{
  D_transformer *transformer_ptr = ((Object *)obj_obj->getObjPtr())->
    find_transformer_by_name( transformer->getVcharText() );
  
  if ( ! transformer_ptr )
    {
      return FALSE;
    }
  
  transformer->setObjPtr( (persObjPtr) transformer_ptr );
  transformer->set_Id( transformer_ptr->get_id() );

  if ( ! isInstanceBased )
    {
      if ( transformer_ptr->is_instance_based() )
        return FALSE;
    }
  else
    {
      if ( ! transformer_ptr->is_instance_based() )
        return FALSE;
    }
      
  return TRUE;
}


//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
//
// Function: get_transformer_return_type
// Description: Get the transformer's return type from the dbms_config
//              database
//
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// Get the data type of the transformer data item
t_core_data_type P_checkOSDB::get_transformer_return_type( AST *transformer )
{
  D_transformer *transformer_ptr = (D_transformer *) transformer->getObjPtr();
  
  Id return_type_id = transformer_ptr->get_return_type_id();
  D_data_type * data_type_ptr = 
    AL_Generic_finds::find_data_type_by_id( m_current_domain_ptr,
       return_type_id );
  if ( data_type_ptr->get_enum_data_type_ptr() != 0 )
  {
	  return ENUMERATION_DATATYPE;
  }
  else
  {
	  D_core_data_type *trans_core_data_type_ptr =
		AL_Generic_finds::find_core_data_type_by_id( m_current_domain_ptr,
		   return_type_id );
  
	  if ( trans_core_data_type_ptr == 0 )
		{
		  return UNKNOWN_DATATYPE;
		}
  
	  return( (t_core_data_type) trans_core_data_type_ptr->
			 get_core_data_type_type() );
  }
}


//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
//
// Function: get_synch_svc_return_type
// Description: Get the synchronous service's return type from the dbms_config
//              database
//
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// Get the data type of the synchronous service data item
t_core_data_type P_checkOSDB::get_synch_svc_return_type( AST *synch_svc )
{
  D_synchronous_service *synch_svc_ptr =
    (D_synchronous_service *) synch_svc->getObjPtr();
  
  Id return_type_id = synch_svc_ptr->get_return_type_id();
  D_data_type * data_type_ptr = 
    AL_Generic_finds::find_data_type_by_id( m_current_domain_ptr,
       return_type_id );
  if ( data_type_ptr->get_enum_data_type_ptr() != 0 )
  {
	  return ENUMERATION_DATATYPE;
  }
  else
  {
	  D_core_data_type *synch_svc_core_data_type_ptr =
		AL_Generic_finds::find_core_data_type_by_id( m_current_domain_ptr,
		   return_type_id );
  
	  if ( synch_svc_core_data_type_ptr == 0 )
		{
		  return UNKNOWN_DATATYPE;
		}
  
	  return( (t_core_data_type) synch_svc_core_data_type_ptr->
			 get_core_data_type_type() );
  }
}


//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
//
// Function: get bridge return type
// Description: Validate the bridge's return type from the dbms_config
//              database
//
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// Get the data type of the bridge data item
t_core_data_type P_checkOSDB::get_bridge_return_type( AST *ee )
{
  D_bridge *bridge_ptr = (D_bridge *) ee->getObjPtr();
  
  Id return_type_id = bridge_ptr->get_return_type_id();
  D_data_type * data_type_ptr = 
    AL_Generic_finds::find_data_type_by_id( m_current_domain_ptr,
       return_type_id );
  if ( data_type_ptr->get_enum_data_type_ptr() != 0 )
  {
	  return ENUMERATION_DATATYPE;
  }
  else
  {
	  D_core_data_type *bridge_core_data_type_ptr =
		AL_Generic_finds::find_core_data_type_by_id( m_current_domain_ptr,
		   return_type_id );
  
	  if ( bridge_core_data_type_ptr == 0 )
		{
		  return UNKNOWN_DATATYPE;
		}

	  return( (t_core_data_type) bridge_core_data_type_ptr->
			 get_core_data_type_type() );
  }
}


//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
//
// Function: is_valid_ee_kl
// Description: Verify the ee keyletters in the dbms_config database
//              
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// Determine if there's an EE for the given keyletters
bool P_checkOSDB::is_valid_ee_kl( AST *kl )
{
  mc_dbms_List< D_external_entity * > ee_coll;
  
  // Get the first EE in the collection of all EEs
  D_external_entity * ee_ptr;
  FIRST_ELEMENT( ee_ptr,
                D_external_entity,
                m_current_domain_ptr->get_current_dd_srm_scm_sam_ptr()->
                get_external_entity_coll_ptr(),
                c1 );
  
  // Check all EEs for a match
  while ( ee_ptr )
    {
      if ( ee_ptr->external_entity_key_letters() == kl->getVcharText() )
	{
          ee_coll.insert( ee_ptr );
	}
      NEXT_ELEMENT( ee_ptr, c1 );
    }

  int card = ee_coll.cardinality();
  
  if ( card != 1 )
    {
      return FALSE;
    }

  ee_ptr = ee_coll.pick();
  kl->setObjPtr( (persObjPtr) ee_ptr );
  kl->set_Id( ee_ptr->get_id() );
  return TRUE;
}


//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
//
// Function: is_valid_ee_bridge
// Description: Check the bridge in the dbms_config database and set
//              the bridge AST objPtr to the bridge object.
//              
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// Determine if bridge is valid for this ee
bool P_checkOSDB::is_valid_ee_bridge( AST *bridge,
                                      AST *ee )
{
  D_external_entity *ee_ptr = (D_external_entity *) ee->getObjPtr();
  
  D_bridge *bridge_ptr;
  bool found = FALSE;
  FIRST_ELEMENT( bridge_ptr, D_bridge, ee_ptr->get_ro_bridge_coll_ptr(), c );
  while ( bridge_ptr && ! found )
    {
       if ( bridge_ptr->get_name() == bridge->getVcharText() )
          found = TRUE;
       else
	  {
	     NEXT_ELEMENT( bridge_ptr, c );
	  }
    }

  if ( ! bridge_ptr )
    {
      return FALSE;
    }
  
  bridge->setObjPtr( (persObjPtr) bridge_ptr );
  bridge->set_Id( bridge_ptr->get_id() );
  return TRUE;
}


//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
//
// Function: is_referential_attr
// Description: Verify that the attribute is referential in the dbms_config
//              database
//
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// Determine if attribute is referential
bool P_checkOSDB::is_referential_attr( AST *attr )
{
  if ( ((Attribute *)attr->getObjPtr())->get_referential_attribute_ptr() == NULL )
    return FALSE;
  else
    return TRUE;
}


//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// Helper functions extracted from old parser code (render, etc.)
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *


//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
//
// Function: 
// Description: 
//              
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Attribute *P_checkOSDB::find_attribute( const vchar * p_attr,
                                        Object * p_object_ptr )
{
bool found = FALSE;
Attribute * attr_ptr;

FIRST_ELEMENT( attr_ptr, Attribute, p_object_ptr->get_attr_coll_ptr(), c );

while ( attr_ptr && ! found )
  {
    if ( attr_ptr->get_attr_name() == p_attr )
      {
        found = TRUE;
      }
    else
      {
        NEXT_ELEMENT( attr_ptr, c );
      }
  }

return( attr_ptr );
}


//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
//
// Function: 
// Description: 
//              
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
void P_checkOSDB::find_all_events ( const vchar *p_evt_label,
                                      D_sm_spt_pm *event_to_sm_spt_pm_ptr,
                                      bool& p_found_here,
                                      mc_dbms_Bag< D_sm_event * > *&p_event_coll)
{

  if ( p_event_coll == 0 )
  {
    p_event_coll =
	    & mc_dbms_Bag< D_sm_event * >::create(
        	mc_dbms_database::get_transient_database() );
  }

  if ( event_to_sm_spt_pm_ptr != 0 )
  {
      D_sm_event * event_ptr = NULL;

      FIRST_ELEMENT( event_ptr,
                    D_sm_event,
                    event_to_sm_spt_pm_ptr->get_sm_event_coll_ptr(),
                    c1 );
  
      while ( event_ptr )
        {
          if ( event_ptr->get_derived_event_label() == p_evt_label )
            {
              p_event_coll->insert(event_ptr);
              p_found_here = TRUE;
            }

          NEXT_ELEMENT( event_ptr, c1 );
        }
  }

  if ( !p_found_here && event_to_sm_spt_pm_ptr != 0 )
  {
    Object* object_ptr = event_to_sm_spt_pm_ptr->get_object_ptr();

    // Check if Object is Object_as_subtype  (it better be!)
    mc_dbms_Set< Object_in_relationship *> *object_rels = 
            object_ptr->get_obj_in_rel_coll_ptr();
	if (object_rels->cardinality () > 0)
	{
		Object_in_relationship * obj_in_rel_ptr;
		FOR_ALL_ELEMENTS
			(obj_in_rel_ptr,
			Object_in_relationship,
			object_rels,
			obj_in_rel_cursor)
		{
			if (obj_in_rel_ptr->get_object_as_subtype_ptr () != 0)
			{
				if (obj_in_rel_ptr->get_relationship_ptr ()->
					get_inheritance_relationship_ptr () != 0)
				{
					if (obj_in_rel_ptr->get_relationship_ptr ()->
						get_inheritance_relationship_ptr ()->
						get_object_as_supertype_ptr() != 0)
					{
		                Object_as_supertype * supertype_obj_ptr = 
			                obj_in_rel_ptr->get_relationship_ptr ()->
						        get_inheritance_relationship_ptr ()->
						        get_object_as_supertype_ptr();

                        Object * referred_to_obj_ptr = supertype_obj_ptr->get_related_object_ptr();

                        D_sm_spt_pm *supertype_sm_spt_pm_ptr = 0;
                        if (referred_to_obj_ptr)
                        {
                            supertype_sm_spt_pm_ptr =
                              referred_to_obj_ptr->get_instance_sm_spt_pm_ptr();
                        }

                        vchar label_no_splat[32];
                        vcharCopy ( p_evt_label, label_no_splat );

                        vchar splat = vcharFromASCII( '*' );
                        int label_len = vcharLength( p_evt_label );
                        if ( p_evt_label[label_len - 1] == splat )
                        {
                            label_no_splat[label_len - 1] = 0;
                        }

                        bool l_found_here = FALSE;
                        find_all_events( label_no_splat, 
                            supertype_sm_spt_pm_ptr, l_found_here, p_event_coll);

                        if ( l_found_here )
                        {
                            D_sm_event * found_event_ptr;
		                    FOR_ALL_ELEMENTS_SAFE
			                    (found_event_ptr,
			                    D_sm_event,
			                    p_event_coll,
			                    evt_cursor)
		                    {
                                if ( ! found_event_ptr->get_polymorphic_event_ptr() )
                                {
                                    // Event in supertype, but it's not polymorphic
                                    p_event_coll->remove(found_event_ptr);
                                }
                            }
                        }
					}
				}
			}
		}
    }
    delete object_rels;
  }
}



//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
//
// Function: 
// Description: 
//              
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
bool P_checkOSDB::is_valid_relation( AST *id, 
                                     AST *rel_phrase,
                                     Object * p_left_object_ptr,
                                     Relationship * p_rel_ptr,
                                     Object * p_right_object_ptr,
                                     t_multiplicity & p_right_object_mult )
{

  // Check the rel_phrase AST for a phrase, and if it has one, set
  //  p_dest_rel_phrase and p_dest_rel_phrase_exists.
  const vchar *p_dest_rel_phrase = NULL;
  bool p_dest_rel_phrase_exists = FALSE;
  if ( rel_phrase != NULL )
    {
      p_dest_rel_phrase_exists = TRUE;
      p_dest_rel_phrase = rel_phrase->getVcharText();
    }


  // We have to confirm that the specified relationship exists between the
  // left and right object. We also have to get the multiplicity of the right
  // object so that the cardinality of the relationship chain can be determined
  // to make sure matches the SELECT ONE/ANY/MANY.
  
  bool left_object_found = FALSE;
  bool right_object_found = FALSE;
  Object_in_relationship * oir_ptr = 0;
  Object_in_relationship * left_oir_ptr = 0;
  Object_in_relationship * right_oir_ptr = 0;
  Object_in_non_inh_relationship * left_oinir_ptr = 0;
  Object_in_non_inh_relationship * right_oinir_ptr = 0;
  Object_as_subtype * left_oasub_ptr = 0;
  Object_as_subtype * right_oasub_ptr = 0;

  Object_in_non_inh_relationship * dest_rel_oir_ptr;
  Id dest_rel_oir_id;

  FIRST_ELEMENT( oir_ptr,
                Object_in_relationship,
                p_rel_ptr->get_obj_in_rel_coll_ptr(),
                cursor );
  
  while ( ( ! left_object_found || ! right_object_found ) && oir_ptr )
    {
      // We must get two distinct object-in-relationship's if we have a
      // relationship to self.
      
      if ( oir_ptr->object_id() ==
          p_left_object_ptr->get_object_id() )
	{
          if ( ! left_object_found )
            {
              left_object_found = TRUE;
              left_oinir_ptr = oir_ptr->get_object_in_non_inh_relationship_ptr();
              left_oir_ptr = oir_ptr;
              left_oasub_ptr = oir_ptr->get_object_as_subtype_ptr();
            }
	}
      
      if ( oir_ptr->object_id() ==
          p_right_object_ptr->get_object_id() )
	{
          if ( left_oir_ptr == 0
              ||
              oir_ptr->get_id() != left_oir_ptr->get_id() )
            {
              right_object_found = TRUE;
              right_oinir_ptr = oir_ptr->get_object_in_non_inh_relationship_ptr();
              right_oir_ptr = oir_ptr;
              right_oasub_ptr = oir_ptr->get_object_as_subtype_ptr();
            }
	}
      
      NEXT_ELEMENT( oir_ptr, cursor );
    }

  bool valid = FALSE;
  if (left_object_found && right_object_found)
    valid = TRUE;
  
  if ( ! valid )
    {
      // Generate this if the relationship does not exist between from and to.
      AL_PARSE_ERR3( id, AL_GETMSG(ERR,186,3), p_rel_ptr->get_rel_number(),
                     p_left_object_ptr->AL_OBJECT_REFERENCE,
                     p_right_object_ptr->AL_OBJECT_REFERENCE )
      return( FALSE );
    }
  if (left_oasub_ptr && right_oasub_ptr)
    {
      // Generate this if the relationship is between subtypes.
      AL_PARSE_ERR3( id, AL_GETMSG(ERR,190,3),
                     p_left_object_ptr->AL_OBJECT_REFERENCE,
                     p_right_object_ptr->AL_OBJECT_REFERENCE,
                     p_rel_ptr->get_rel_number() )
      return( FALSE );
    }
  

  // We currently don't allow relationship phrase for inheritance relationships.
  
  if ( p_rel_ptr->get_inheritance_relationship_ptr() && p_dest_rel_phrase_exists )
    {
      AL_PARSE_ERR0( id, AL_GETMSG(ERR,170,0) )
      return( FALSE );
    }
  
  // Verify if reflexive relationship, then correctly specified. A reflexive
  // relationship must have the destination relationship phrase. However,
  // a non-reflexive relationship may have a relationship phrase; if one
  // is present, then it had better be right! We must also save the oir
  // associated with the relationship phrase (if exists) as a bush relocatable.
  
  if ( p_rel_ptr->is_reflexive() )
    {
      if ( p_dest_rel_phrase_exists )
	{
          // We could have an associative relationship to self, but are
          // navigating via the associative object. In this case the relationship
          // phrase is still needed, but remember, it is stored with either
          // Object_as_assoc_one_side or Object_as_assoc_other_side, not
          // Object_as_associator.
          
          // If the left and right objects are the same, then we have either
          // a simple reflexive relationship or a reflexive associative
          // relationship whereby we are NOT navigating via the
          // associative object (we are going from the same associated object
          // across the relationship to the same associated object skipping the
          // associative object).
          
          if ( p_left_object_ptr->get_id() == p_right_object_ptr->get_id() )
            {
              // The dest_rel_phrase is associated with the right object. For a
              // reflexive relationship, we must make sure that the right_oinir
              // is associated with the dest_rel_phrase. If it is currently with
              // the left, then we will switch the left and right oinir.
              
              // Get rid of ticks for comparison.
              
              Description dest_rel_phrase;
              dest_rel_phrase += & p_dest_rel_phrase[ 1 ];
              dest_rel_phrase.truncate( dest_rel_phrase.length() - 1 );
              
              if ( left_oinir_ptr->text_phrase() == dest_rel_phrase )
                {
                  // Save oir ptr and id for relocatable dest_rel_phrase, but
                  // first switch the two oir's.
                  Object_in_non_inh_relationship * tmp_oinir_ptr = left_oinir_ptr;
                  left_oinir_ptr = right_oinir_ptr;
                  right_oinir_ptr = tmp_oinir_ptr;

                  dest_rel_oir_ptr = right_oinir_ptr;
                }
              else if ( right_oinir_ptr->text_phrase() == dest_rel_phrase )
                {
                  // Save oir ptr and id for relocatable dest_rel_phrase
                  dest_rel_oir_ptr = right_oinir_ptr;
                }
              else
                {
                  AL_PARSE_ERR3( id, AL_GETMSG(ERR,181,3),
                                 p_right_object_ptr->AL_OBJECT_REFERENCE,
                                 p_rel_ptr->get_rel_number(),
                                 p_dest_rel_phrase )
                  return( FALSE );
                }
            }
          else	// Reflexive associative relationship via associative object.
            {
              // We are navigating via the associative object, which means we are
              // either at the associated object and going thru the associative
              // object or we are at the associative object going thru the
              // associated object. In either case, simply make sure the
              // relationship phrase match either one of the associated objects.
              // Remember we must save the oir affiliated with the phrase;
              // additionally we need to save the left and right oirs so the
              // multiplicity can be determined later.
              
              Associative_relationship * ass_rel_ptr =
                p_rel_ptr->get_associative_relationship_ptr();
              
              if ( ass_rel_ptr == 0 )
                {
                  LOG_ERROR( ( L_log_string,
                              "AL_Render::valid_relation()...relationship R%d not associative!",
                              p_rel_ptr->get_rel_number() ) );
                  return( FALSE );
                }
              
              // Get rid of ticks for comparison.
              
              Description dest_rel_phrase;
              dest_rel_phrase += & p_dest_rel_phrase[ 1 ];
              dest_rel_phrase.truncate( dest_rel_phrase.length() - 1 );
              
              Object_as_associator * rel_associator_ptr =
                ass_rel_ptr->get_object_as_associator_ptr();
              Object_as_assoc_one_side * rel_one_end_ptr =
                ass_rel_ptr->get_object_as_assoc_one_side_ptr();
              Object_as_assoc_other_side * rel_other_end_ptr =
                ass_rel_ptr->get_object_as_assoc_other_side_ptr();
              
              if ( rel_associator_ptr
                  &&
                  left_oir_ptr->get_object_as_associator_ptr()
                  &&
                  rel_associator_ptr->get_id() ==
                  left_oir_ptr->get_object_as_associator_ptr()->get_id() )
                {
                  // The left object is the associative object and the right is
                  // one of the associators. The destination phrase should match
                  // one of the associators.
                  
                  if ( rel_one_end_ptr->text_phrase() == dest_rel_phrase )
                    {
                      // Save oir ptr and id for relocatable dest_rel_phrase.
                      dest_rel_oir_ptr = rel_one_end_ptr;

                      right_oinir_ptr = rel_one_end_ptr;
                    }
                  else if ( rel_other_end_ptr->text_phrase() == dest_rel_phrase )
                    {
                      // Save oir ptr and id for relocatable dest_rel_phrase.
                      dest_rel_oir_ptr = rel_other_end_ptr;

                      right_oinir_ptr = rel_other_end_ptr;
                    }
                  else
                    {
                      AL_PARSE_ERR3( id, AL_GETMSG(ERR,181,3),
                                     p_right_object_ptr->AL_OBJECT_REFERENCE,
                                     p_rel_ptr->get_rel_number(),
                                     p_dest_rel_phrase )
                      return( FALSE );
                    }
                }
              else
                {
                  // The left object is one of the associators and the right
                  // object is the associative object. Even though the right
                  // object is the associative object, the destination phrase
                  // must match with one of the associators, and we must
                  // store the destination phrase of the matching associator.
                  // However, the left_oinir_ptr should be OPPOSITE the phrase.
                  
                  if ( rel_one_end_ptr->text_phrase() == dest_rel_phrase )
                    {
                      // Save oir ptr and id for relocatable dest_rel_phrase.
                      dest_rel_oir_ptr = rel_one_end_ptr;
                      
                      left_oinir_ptr = rel_other_end_ptr;
                    }
                  else if ( rel_other_end_ptr->text_phrase() == dest_rel_phrase )
                    {
                      // Save oir ptr and id for relocatable dest_rel_phrase.
                      dest_rel_oir_ptr = rel_other_end_ptr;

                      left_oinir_ptr = rel_one_end_ptr;
                    }
                  else
                    {
                      AL_PARSE_ERR3( id, AL_GETMSG(ERR,181,3),
                                     p_right_object_ptr->AL_OBJECT_REFERENCE,
                                     p_rel_ptr->get_rel_number(),
                                     p_dest_rel_phrase )
                      return( FALSE );
                    }
                }
            }
	}
      else
	{
          // Error: We have a reflexive relationship, but no relationship phrase!
          AL_PARSE_ERR3( id, AL_GETMSG(ERR,185,3),
                         p_rel_ptr->get_rel_number(),
                         p_left_object_ptr->AL_OBJECT_REFERENCE,
                         p_right_object_ptr->AL_OBJECT_REFERENCE )
          return( FALSE );
	}
    }
  else	// Not a reflexive relationship
    {
      if ( p_dest_rel_phrase_exists )
	{
          // We don't have a reflexive relationship, but, since they entered
          // a destination relationship phrase then it must be correct.
          // Also, the phrase is associated with the right object.
          
          Description dest_rel_phrase;
          dest_rel_phrase += & p_dest_rel_phrase[ 1 ];
          dest_rel_phrase.truncate( dest_rel_phrase.length() - 1 );
              
          if ( right_oinir_ptr->text_phrase() == dest_rel_phrase )
            {
              // Save oir ptr and id for relocatable dest_rel_phrase
              dest_rel_oir_ptr = right_oinir_ptr;
            }
          else
            {
              AL_PARSE_ERR3( id, AL_GETMSG(ERR,182,3),
                             p_right_object_ptr->AL_OBJECT_REFERENCE,
                             p_rel_ptr->get_rel_number(),
                             p_dest_rel_phrase )
              return( FALSE );
            }
	}
    }
  
  p_right_object_mult = get_right_object_multiplicity( left_oinir_ptr,
                                                      p_rel_ptr, right_oinir_ptr );

  if ( rel_phrase != NULL )
    {
      rel_phrase->setObjPtr( (persObjPtr) dest_rel_oir_ptr );
      rel_phrase->set_Id( dest_rel_oir_ptr->get_id() );
    }

  return( valid );
}


//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
//
// Function: is_valid_assoc_relationship
// Description: validate associative relationship in database
//              
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
bool P_checkOSDB::is_valid_assoc_relationship( AST *id,
                                               AST *from,
                                               AST *to,
                                               AST *assoc,
                                               Relationship * p_rel_ptr,
                                               Object * p_left_object_ptr,
                                               Object * p_ass_object_ptr,
                                               Object * p_right_object_ptr )
{
  const vchar *vc_rel_num = id->getVcharText();
  // Strip leading [Rr] from relationship id
  const vchar *rel_num = id->getVcharText();
  const vchar R = vcharFromASCII('R');
  const vchar r = vcharFromASCII('r');
  
  if ( (rel_num[0] == R) || (rel_num[0] == r) )
    {
      ++rel_num;
      ++vc_rel_num;
    }

  Associative_relationship * ass_rel_ptr =
    p_rel_ptr->get_associative_relationship_ptr();
  
  if ( ! ass_rel_ptr )
    {
      // Generate this if the relationship is not associative
      AL_PARSE_ERR1( id, AL_GETMSG(ERR,184,1), vc_rel_num );
      return( FALSE );
    }

  // Make sure the left and right objects are the associators and the
  // associative one is indeed associative. Remember that an object
  // can have an associative relationship with itself.
  
  t_boolean left_object_found = FALSE;
  t_boolean right_object_found = FALSE;
  t_boolean ass_object_found = FALSE;
  Object_in_non_inh_relationship * left_oinir_ptr = 0;
  Object_in_non_inh_relationship * right_oinir_ptr = 0;
  Object_in_non_inh_relationship * ass_oinir_ptr = 0;
  Object_in_relationship * oir_ptr;
  
  FIRST_ELEMENT( oir_ptr,
                Object_in_relationship,
                p_rel_ptr->get_obj_in_rel_coll_ptr(),
                cursor );
  
  while ( ( ! left_object_found || ! right_object_found  || ! ass_object_found )
         && oir_ptr )
    {
      if ( oir_ptr->object_id() ==
          p_left_object_ptr->get_object_id() )
	{
          if ( ! left_object_found )
            {
              left_object_found = TRUE;
              left_oinir_ptr = oir_ptr->get_object_in_non_inh_relationship_ptr();
            }
	}
      
      if ( oir_ptr->object_id() ==
          p_right_object_ptr->get_object_id() )
	{
          right_object_found = TRUE;
          right_oinir_ptr = oir_ptr->get_object_in_non_inh_relationship_ptr();
	}
      
      if ( oir_ptr->object_id() ==
          p_ass_object_ptr->get_object_id() )
	{
          ass_object_found = TRUE;
          ass_oinir_ptr = oir_ptr->get_object_in_non_inh_relationship_ptr();
	}
      
      NEXT_ELEMENT( oir_ptr, cursor );
    }
  
  
  // Make sure that all three objects were found in the relationship.
  
  if ( ! ass_object_found )
    {
      // Generate this if the assoc_obj is not an associative object between
      //  from_obj and to_obj
      AL_PARSE_ERR4( id, AL_GETMSG(ERR,179,4),
                     assoc->getVcharText(),
                     from->getVcharText(),
                     to->getVcharText(),
                     vc_rel_num )
      return( FALSE );
    }
  
  if ( ! left_object_found )
    {
      AL_PARSE_ERR2( id, AL_GETMSG(ERR,180,2),
                     from->getVcharText(), vc_rel_num )
      return( FALSE );
    }
  
  if ( ! right_object_found )
    {
      AL_PARSE_ERR2( id, AL_GETMSG(ERR,180,2),
                     to->getVcharText(), vc_rel_num )
      return( FALSE );
    }
  
  
  // Make sure each object is at its correct position in relationship. First check
  // associative object, then associated objects.
  
  Object_as_assoc_one_side * rel_one_side_ptr =
    ass_rel_ptr->get_object_as_assoc_one_side_ptr();
  Object_as_assoc_other_side * rel_other_side_ptr =
    ass_rel_ptr->get_object_as_assoc_other_side_ptr();
  Object_as_associator * rel_associator_ptr =
    ass_rel_ptr->get_object_as_associator_ptr();
  
  if ( ass_oinir_ptr->get_object_as_associator_ptr() != rel_associator_ptr )
    {
      AL_PARSE_ERR4( id, AL_GETMSG(ERR,179,4),
                     assoc->getVcharText(),
                     from->getVcharText(),
                     to->getVcharText(),
                     vc_rel_num )
      return( FALSE );
    }
  
  // Make sure the left and right objects are indeed the one and other associated
  // objects.
  
  if ( ! left_oinir_ptr->get_object_as_assoc_one_side_ptr() &&
      ! left_oinir_ptr->get_object_as_assoc_other_side_ptr() )
    {
      AL_PARSE_ERR2( id, AL_GETMSG(ERR,183,2),
                     from->getVcharText(), vc_rel_num )
      return( FALSE );
    }
  
  if ( left_oinir_ptr->get_object_as_assoc_one_side_ptr() &&
      left_oinir_ptr->get_object_as_assoc_one_side_ptr() != rel_one_side_ptr )
    {
      AL_PARSE_ERR2( id, AL_GETMSG(ERR,183,2),
                     from->getVcharText(), vc_rel_num )
      return( FALSE );
    }
  else if ( left_oinir_ptr->get_object_as_assoc_other_side_ptr() &&
           left_oinir_ptr->get_object_as_assoc_other_side_ptr() !=
           rel_other_side_ptr )
    {
      AL_PARSE_ERR2( id, AL_GETMSG(ERR,183,2),
                     from->getVcharText(), vc_rel_num )
      return( FALSE );
    }
  
  if ( ! right_oinir_ptr->get_object_as_assoc_one_side_ptr() &&
      ! right_oinir_ptr->get_object_as_assoc_other_side_ptr() )
    {
      AL_PARSE_ERR2( id, AL_GETMSG(ERR,183,2),
                     to->getVcharText(), vc_rel_num )
      return( FALSE );
    }
  
  if ( right_oinir_ptr->get_object_as_assoc_one_side_ptr() &&
      right_oinir_ptr->get_object_as_assoc_one_side_ptr() != rel_one_side_ptr )
    {
      AL_PARSE_ERR2( id, AL_GETMSG(ERR,183,2),
                     to->getVcharText(), vc_rel_num )
      return( FALSE );
    }
  else if ( right_oinir_ptr->get_object_as_assoc_other_side_ptr() &&
           right_oinir_ptr->get_object_as_assoc_other_side_ptr() !=
           rel_other_side_ptr )
    {
      AL_PARSE_ERR2( id, AL_GETMSG(ERR,183,2),
                     to->getVcharText(), vc_rel_num )
      return( FALSE );
    }

  return TRUE;
}


//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
//
// Function: 
// Description: 
//              
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
t_multiplicity P_checkOSDB::get_right_object_multiplicity(
   Object_in_non_inh_relationship * p_left_oinir_ptr,
   Relationship * p_rel_ptr,
   Object_in_non_inh_relationship * p_right_oinir_ptr )
{
  t_multiplicity result_mult;
  t_multiplicity associator_mult;
  
  // We also have to get the multiplicity of the right
  // object so that the cardinality of the relationship chain can be determined
  // to make sure matches the SELECT ONE/ANY/MANY.
  
  if ( p_rel_ptr->get_simple_relationship_ptr() )
    {
      result_mult = p_right_oinir_ptr->multiplicity();
    }
  else if ( p_rel_ptr->get_inheritance_relationship_ptr() )
    {
      result_mult = ONE;
    }
  else if ( p_rel_ptr->get_composition_relationship_ptr() )
    {
      result_mult = p_right_oinir_ptr->multiplicity();
    }
  else if ( p_rel_ptr->get_associative_relationship_ptr() )
    {
      if ( p_left_oinir_ptr->get_object_as_associator_ptr() )
	{
          // Real simply, if the left object is the associative object,
          // then we should ALWAYS use ONE multiplicity because we can
          // only navigate to ONE and only ONE of the associators.
          
          result_mult = ONE;
	}
      else if ( p_left_oinir_ptr->get_object_as_assoc_one_side_ptr() )
	{
          if ( p_right_oinir_ptr->get_object_as_assoc_other_side_ptr() )
            {
              result_mult = p_right_oinir_ptr->multiplicity();
            }
          else if ( p_right_oinir_ptr->get_object_as_associator_ptr() )
            {
              associator_mult =
                p_right_oinir_ptr->get_object_as_associator_ptr()->
                  multiplicity();
              
              if ( associator_mult == ONE &&
                  p_rel_ptr->get_associative_relationship_ptr()->
                  get_object_as_assoc_other_side_ptr()->multiplicity() == ONE )
                {
                  result_mult = ONE;
                }
              else
                {
                  result_mult = MANY;
                }
            }
          else
            {
              result_mult = ONE;
            }
	}
      else if ( p_left_oinir_ptr->get_object_as_assoc_other_side_ptr() )
	{
          if ( p_right_oinir_ptr->get_object_as_assoc_one_side_ptr() )
            {
              result_mult = p_right_oinir_ptr->multiplicity();
            }
          else if ( p_right_oinir_ptr->get_object_as_associator_ptr() )
            {
              associator_mult =
                p_right_oinir_ptr->get_object_as_associator_ptr()->
                  multiplicity();
              
              if ( associator_mult == ONE &&
                  p_rel_ptr->get_associative_relationship_ptr()->
                  get_object_as_assoc_one_side_ptr()->multiplicity() == ONE )
                {
                  result_mult = ONE;
                }
              else
                {
                  result_mult = MANY;
                }
            }
          else
            {
              result_mult = ONE;
            }
	}
      else
	{
          result_mult = ONE;
	}
    }
  else
    {
      result_mult = ONE;
    }

  return( result_mult );
}



// The following functions are not used for MB parsing.  They're here only
// because they're used in p_ckgendb.


//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
//
// Function: is_valid_obj_event_label
// Description: Verify the event label in the dbms_config database
//              
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// Determine if event label is valid for this object
bool P_checkOSDB::is_valid_obj_event_label( AST *label,
                                            AST *obj_obj )
{
  return FALSE;
}


//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
//
// Function: is_valid_ee_event_label
// Description: Verify the ee event label in the dbms_config database
//              
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// Determine if event label is valid for this object
bool P_checkOSDB::is_valid_ee_event_label( AST *label,
                                           AST *ee )
{
  return FALSE;
}


//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
//
// Function: get_right_obj_card
// Description: Get the cardinality (multiplicity) of the right object via
//              the given relationship from the dbms_config database
//              
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// Get the cardinality (Obj_Card_e) for the right object
Obj_Card_e P_checkOSDB::get_right_obj_card( AST *rel,
                                            AST *obj_left,
                                            AST *obj_right )
{
  // Is this used anywhere?
  return( CARD_ONE );
}


//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
//
// Function: is_identifier
// Description: Verify that the attribute is an identifier in the
//              dbms_config database
//
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// Determine if attribute is an identifier
bool P_checkOSDB::is_identifier( AST *attr )
{
  if ( !((Attribute *)attr->getObjPtr())->is_an_identifier() )
    return FALSE;
  else
    return TRUE;
}

persObjPtr P_checkOSDB::get_enum_data_type_ptr(  AST* p_enum )
{
  persObjPtr ret_val = 0;
  if ( p_enum->getObjPtr() == RESET_OBJPTR )
  {
	  return ret_val;
  }

  switch ( p_enum->getType() )
  {
    case TOK_ENUMERATION:
    case TOK_LOCAL_VAR:
	  ret_val = (D_enum_data_type*) p_enum->getObjPtr();
	  break;

    case TOK_BRIDGE_PARAM:
	case TOK_SYNCH_SVC_PARAM:
    case TOK_TRANSFORMER_PARAM:
	{
		D_parameter *parm_ptr = (D_parameter*) p_enum->child()->getObjPtr();
	    if ( parm_ptr && parm_ptr != RESET_OBJPTR )
		{
			ret_val = parm_ptr->get_enum_data_type_ptr();
		}
	}
	  break;

    case TOK_BRIDGE_EXPR:
		{
		D_bridge *brg_ptr = (D_bridge*) p_enum->child()->sibling()->getObjPtr();
	    if ( brg_ptr && brg_ptr != RESET_OBJPTR )
		{
			ret_val = brg_ptr->get_return_type()->get_enum_data_type_ptr();
		}
		}
		break;
    case TOK_TRANSFORMER_EXPR:
    case TOK_TRANSFORMER_IB_EXPR:
		{
		D_transformer *tfmr_ptr = (D_transformer*) p_enum->child()->sibling()->getObjPtr();
	    if ( tfmr_ptr && tfmr_ptr != RESET_OBJPTR )
		{
			ret_val = tfmr_ptr->get_return_type()->get_enum_data_type_ptr();
		}
		}
		break;
	case TOK_SYNCH_SVC_EXPR:
		{
		D_synchronous_service *ss_ptr = (D_synchronous_service*) p_enum->child()->getObjPtr();
	    if ( ss_ptr && ss_ptr != RESET_OBJPTR )
		{
			ret_val = ss_ptr->get_return_type()->get_enum_data_type_ptr();
		}
		}
		break;

    case TOK_INST_REF_VAR:
	{
		Attribute* attr_ptr = (Attribute*) p_enum->child()->getObjPtr();
	    if ( attr_ptr && attr_ptr != RESET_OBJPTR )
		{
			ret_val = attr_ptr->get_enum_data_type_ptr();
		}
	}
	  break;

    case TOK_EXPRESSION:
		ret_val = get_enum_data_type_ptr(p_enum->child());
      break;

    case TOK_RCVD_EVT:
	{
		D_sm_event_data_item *event_data_item_ptr = 
			(D_sm_event_data_item*) p_enum->sibling()->getObjPtr();
	    if ( event_data_item_ptr && event_data_item_ptr != RESET_OBJPTR )
		{
			ret_val = event_data_item_ptr->get_enum_data_type_ptr();
		}
	}
	  break;
  }
  return ret_val;
}

void P_checkOSDB::verify_return_type( t_core_data_type p_dt,
								  persObjPtr p_return_type_reqd,
								  AST *p_e, const vchar* p_descr )
{
		D_core_data_type* cdt_ptr = ((D_data_type*)p_return_type_reqd)->get_core_data_type_ptr();
		if ( cdt_ptr && cdt_ptr->get_core_data_type_type() == VOID_DATATYPE )
		{
			if ( p_e )
			AL_PARSE_ERR1(p_e, AL_GETMSG(ERR, 238, 1),
			p_descr)
		}
		else
		{
			if ( ! p_e )
			{
				AL_PARSE_ERR1(p_e, AL_GETMSG(ERR, 236, 1),
				p_descr);
			}
			else if ( p_dt == ENUMERATION_DATATYPE )
			{
				if ( get_enum_data_type_ptr(p_e) != p_return_type_reqd )
				{
					AL_PARSE_ERR1(p_e, AL_GETMSG(ERR, 237, 1),
					p_descr);
				}
			}
			else if ( cdt_ptr == 0 || p_dt != cdt_ptr->get_core_data_type_type() )
			{
				AL_PARSE_ERR1(p_e, AL_GETMSG(ERR, 237, 1),
				p_descr);
			}
		}
}


void P_checkOSDB::verify_return_void( persObjPtr p_return_type_reqd,
								  AST *p_e, const vchar* p_descr )
{
		if ( p_return_type_reqd != 0 )
		{
			D_core_data_type* cdt_ptr = ((D_data_type*)p_return_type_reqd)->get_core_data_type_ptr();
			if ( cdt_ptr == 0 )
			{
				if ( ((D_data_type*)p_return_type_reqd)->get_enum_data_type_ptr() )
				{
					AL_PARSE_ERR1(p_e, AL_GETMSG(ERR, 236, 1), p_descr)
				}
			}
			else if ( cdt_ptr->get_core_data_type_type() != VOID_DATATYPE )
			{
				AL_PARSE_ERR1(p_e, AL_GETMSG(ERR, 236, 1), p_descr)
			}
		}
}

/*========================================================================
 *
 * File:      $RCSfile: p_ckgendb.cc,v $
 * Version:   $Revision: 1.10 $
 * Modified:  $Date: 2013/01/10 23:41:23 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#include "p_ckgendb.hh"
#include "myAST.h"
#include "p_error.hh"
#include "p_check.hh"     // RESET_OBJPTR

// BridgePoint includes

#include "gs_ui.hh"
#include "gs_selct.hh"

#include "d_typdef.hh"

#include "i_var.hh"

#include "i_obj.hh"
#include "i_oinst.hh"
#include "i_attr.hh"
#include "i_ainst.hh"

#include "u_error.hh"
#include "u_smtptr.hh"
#include "u_trace.hh"
#include "u_cursor.hh"

#include "vchar.h"

extern mc_dbms_database * GS_gen_sim_db_ptr;

//------------------------------------------------------------
// Basic Interface Functions:
//------------------------------------------------------------

// Validate the object keyletters.
void P_checkGenDB::validate_obj_kl( AST *kl )
{
  if (dumpflag)
    kl->dumpNode("validate_obj_kl: ");

  // make sure it has an illegal value in case of error.
  // we call this function from other functions in this 
  // file, so we need to do this.
  kl->setObjPtr(0);     
  
  // Let's make sure the object key_letters exists.

  // select many results from instances of O_OBJ where selected.Key_Lett == kl->getVcharText()
  
  bool mult_found = FALSE;
  I_Attribute_Instance* result = get_attribute_instance_by_name( 
      "O_OBJ", "KEY_LETT", kl->getVcharText(), mult_found );


  // Generate this error if the keyletters can't be found
  if ( result == 0 )
  {
    AL_PARSE_ERR1( kl, AL_GETMSG(ERR,123,1), kl->getVcharText() )
  }
  // Generate this error if there's more than one object with keyletters kl
  else if ( mult_found )
  {
    AL_PARSE_ERR1( kl, AL_GETMSG(ERR,023,1), kl->getVcharText() )
  }
  else
  {
    I_Object_Instance *obj_inst = result->get_Object_Instance_R2002_ptr();
    kl->setObjPtr(obj_inst);
  }

}

// Validate object attribute
int P_checkGenDB::validate_obj_attribute( AST *attr,
                                         AST *obj_obj,
                                         Assign_Val_e isLval,
										 const vchar* attribute_write_valid)
{
  int ret_val = 0;

  if (dumpflag)
    attr->dumpNode("validate_obj_attribute: ");

  // select many attrs related by obj_obj->O_ATTR[R102] 
  // for each oi in attrs
  //   if oi.Name == attr->getVcharText()
  //     found it
  //   end if
  // end for

  I_Object_Instance* p_obj_inst = (I_Object_Instance *) obj_obj->getObjPtr();
  I_Object* p_obj = p_obj_inst->get_Object_R2001_ptr();

  mc_dbms_List<I_Object_Instance*> inst_coll;
  inst_coll.insert_last(p_obj_inst);
  I_object_inst_ref_set_var* inst_set_var_ptr = 
    new I_object_inst_ref_set_var (p_obj, &inst_coll);

  I_object_inst_ref_set_var* attrs =
    GS_select::create_single_link( inst_set_var_ptr, "O_ATTR", "R102", "");

  I_Object_Instance * attr_ptr;
  FIRST_ELEMENT( attr_ptr,
                 I_Object_Instance, 
                 &(attrs->m_oinst_coll),
                 attr_cursor );

  int num_found = 0;
  while ( attr_ptr )
  {
    I_Attribute_Instance *nm = 
      find_Attribute_Instance_R2002_by_name( 
		attr_ptr, Description("NAME").char_ptr(), num_found );

    if (num_found > 0)
    {
      I_var* nm_ptr = nm->get_var_ptr ();
      if ( nm_ptr )
        if ( nm_ptr->get_string_var_ptr() )
          if ( vcharCompare (nm_ptr->get_string_var_ptr()->get_value().char_ptr(), 
                       attr->getVcharText()) == 0 )
          {
            // Put the attribute pointer in the attr AST
            attr->setObjPtr( attr_ptr );
            break;
          }
    }
    NEXT_ELEMENT( attr_ptr, attr_cursor );
  }

  delete attrs;
  delete inst_set_var_ptr;

  if ( attr_ptr == 0 )
  {
      // Generate this error if the obj_obj does not contain the attr
      AL_PARSE_ERR2( attr, AL_GETMSG(ERR,124,2), obj_obj->getVcharText(), attr->getVcharText() )
  }
  else
  {
    t_core_data_type dt = find_core_data_type ( attr_ptr, "R114" );
    if ( dt == UNKNOWN_DATATYPE )
    {
      // Generate this error if (somehow?) you can't determine the datatype of the attribute
      AL_PARSE_ERR1( attr, AL_GETMSG(ERR,121,1), attr->getVcharText() )
    }

    // Set the datatype of the attribute in the AST tree
    attr->setDatatype( dt );

    if ( isLval == ASSIGN_LVAL )
    {
      if ( is_referential_attr(attr) )
      {
        AL_PARSE_ERR1( attr, AL_GETMSG(ERR,122,1), attr->getVcharText() )
      }
      else if ( (dt == UNIQUE_ID_DATATYPE) && is_identifier(attr) )
      {
        AL_PARSE_ERR1( attr, AL_GETMSG(ERR,273,1), attr->getVcharText() )
      }
      else 
      {
		  // select one battr related by attr->O_BATTR[R106]
		  // select one dbattr related by attr->O_DBATTR[R107]
		  // if ( cardinality(dbase_attr) != 0 )
		  //   check for write to valid attribute
          mc_dbms_List<I_Object_Instance*> inst_coll;
          inst_coll.insert_last(attr_ptr);
          I_Object* p_obj = attr_ptr->get_Object_R2001_ptr();
          I_object_inst_ref_set_var* attr_coll = 
            new I_object_inst_ref_set_var (p_obj, &inst_coll);

          I_object_inst_ref_set_var* battr =
            GS_select::create_single_link( attr_coll, "O_BATTR", "R106", "");

          I_object_inst_ref_set_var* dbattr =
            GS_select::create_single_link( battr, "O_DBATTR", "R107", "");

		  delete attr_coll;

          if ( dbattr->cardinality() != 0 )
          {
			  if ( attribute_write_valid == 0 || vcharLength(attribute_write_valid) == 0 )
			  {
                  dbattr->first();
                  I_Attribute_Instance *suc_pars = find_Attribute_Instance_R2002_by_name( 
		              dbattr->get_oinst_ptr(), Description("SUC_PARS").char_ptr(), num_found );
                  if ( num_found > 0 )
                  {
                    I_var* n_ptr = suc_pars->get_var_ptr ();
                    if ( n_ptr )
                      if ( n_ptr->get_integer_var_ptr() )
                        if ( n_ptr->get_integer_var_ptr()->get_value() > 0 )
                        {
            	            AL_PARSE_ERR1( attr, AL_GETMSG(ERR,130,1), attr->getVcharText() );
                            ret_val = FALSE;
                        }
                        else
                        {
                            // parse_on_apply not set, treat it like an ordinary attribute
                            ret_val = TRUE;
                        }
                  }
                  else
                  {
    	              AL_PARSE_ERR1( attr, AL_GETMSG(ERR,130,1), attr->getVcharText() );
                      ret_val = FALSE;
                  }
			  }
              else
			  {
			      if (vcharCompareBase( obj_obj->getVcharText(), self_string.char_ptr() ) != 0)
				  {
		              AL_PARSE_ERR1( attr, AL_GETMSG(ERR,130,1), attr->getVcharText() );
		              ret_val = FALSE;
				  }
				  else if (vcharCompare( attr->getVcharText(), attribute_write_valid ) != 0)
				  {
		              AL_PARSE_ERR1( attr, AL_GETMSG(ERR,130,1), attr->getVcharText() );
		              ret_val = FALSE;
				  }
				  else
				  {
				      ret_val = TRUE;
				  }
			  }
          }

		  delete dbattr;
		  delete battr;
      }
    }
    else
    {
      // if this is a referential, follow back to actual
      // data type
      if ( is_referential_attr(attr) )
      {
        // select one rattr related by attr->O_RATTR[R106]
        // while ( cardinality(rattr) != 0 )
        //   select one battr related by rattr->O_BATTR[R113]
        //   select one attr2 related by battr->O_ATTR[R106]
        //   select one rattr related by attr2->O_RATTR[R106]
        // end while

        mc_dbms_List<I_Object_Instance*> inst_coll;
        inst_coll.insert_last(attr_ptr);
        I_Object* p_obj = attr_ptr->get_Object_R2001_ptr();
        I_object_inst_ref_set_var* attr_coll = 
          new I_object_inst_ref_set_var (p_obj, &inst_coll);

        I_object_inst_ref_set_var* rattr =
          GS_select::create_single_link( attr_coll, "O_RATTR", "R106", "");

        delete attr_coll;

        I_object_inst_ref_set_var* battr = 0;
        I_object_inst_ref_set_var* attr2 = 0;
        while ( rattr->cardinality() != 0 )
        {
          if ( battr != 0 )
          {
            delete battr;
          }
          battr =
            GS_select::create_single_link( rattr, "O_BATTR", "R113", "");

          if ( attr2 != 0 )
          {
            delete attr2;
          }
          attr2 =
            GS_select::create_single_link( battr, "O_ATTR", "R106", "");

          delete rattr;
          rattr =
            GS_select::create_single_link( attr2, "O_RATTR", "R106", "");
        }

        delete rattr;
        delete battr;

        attr2->first();
        attr_ptr = attr2->get_oinst_ptr();
        dt = find_core_data_type ( attr_ptr, "R114" );
        attr->setDatatype( dt );

        delete attr2;
      }
    }
  }

  return ret_val;
}


// Validate the event label
void P_checkGenDB::validate_obj_event_label( AST *label,
                                             AST *to_obj )
{
  if (dumpflag)
    label->dumpNode("validate_obj_event_label: ");

  // select one ism related by to_obj->SM_ISM[R518]
  // if ( cardinality(ism) == 0 )
  //    error -- no state model
  // else
  //   select one sm related by ism->SM_SM[R517]
  //   select many events related by sm->SM_EVT[R502]
  //   for each evt in events
  //     if (evt.Drv_Lbl == label->getVcharText() )
  //        found_it 
  //        break;
  //     end if
  //   end for
  // end if

  I_Object_Instance *to_object_ptr = (I_Object_Instance *) to_obj->getObjPtr();
  mc_dbms_List<I_Object_Instance*> inst_coll;
  inst_coll.insert_last(to_object_ptr);
  I_Object* p_obj = to_object_ptr->get_Object_R2001_ptr();
  I_object_inst_ref_set_var* inst_set_var_ptr = 
    new I_object_inst_ref_set_var (p_obj, &inst_coll);

  I_object_inst_ref_set_var* ism =
    GS_select::create_single_link( inst_set_var_ptr, "SM_ISM", "R518", "");

  if ( ism->cardinality() == 0 )
  {
    AL_PARSE_ERR2( label, AL_GETMSG(ERR,125,2), to_obj->getVcharText(), label->getVcharText() )
  }
  else
  {
    bool found_here = FALSE;
    mc_dbms_Bag< I_Object_Instance * > *sm_event_coll = 0;
    find_event_for_event_label( label->getVcharText(), ism, found_here,
                                      sm_event_coll);

    if ( sm_event_coll->cardinality() == 0 )
    {
      AL_PARSE_ERR2( label, AL_GETMSG(ERR,061,2), label->getVcharText(),
                    to_obj->getVcharText() )
    }
    else
    {
      label->setObjPtr(sm_event_coll->pick());
    }
  }

  delete ism;
  delete inst_set_var_ptr;

}


// Validate the event meaning
void P_checkGenDB::validate_sm_event_meaning( AST *meaning,
                                            AST *event)
{
  if (dumpflag)
    meaning->dumpNode("validate_sm_event_meaning: ");

  I_Object_Instance* p_event = (I_Object_Instance*) event->getObjPtr();
  int num_found = 0;
  I_Attribute_Instance *mning = 
    find_Attribute_Instance_R2002_by_name( p_event, Description("MNING").char_ptr(), num_found );

  if (num_found > 0)
  {
    I_var* attr_val_ptr = mning->get_var_ptr ();
    if ( attr_val_ptr )
    {
      if ( attr_val_ptr->get_string_var_ptr() )
      {
        // event meanings in the gen DB have no ticks, event meanings
        // in the AST might or might not, so check and add the ticks
        // back if needed before comparing

        Description evt_mning;
        if ( meaning->getRelocType() == EVENT_MEANING_TICKED_FIELD )
	{
          evt_mning = Description("'");
		  evt_mning += attr_val_ptr->get_string_var_ptr()->get_value();
		  evt_mning += "'";
        }
        else if ( meaning->getRelocType() == EVENT_MEANING_FIELD )
	{
          evt_mning = attr_val_ptr->get_string_var_ptr()->get_value();
        }

        if ( evt_mning == meaning->getVcharText() )
	{
          meaning->setObjPtr(p_event);
	}
        else
        {
          // if the meaning doesn't match the label, generate this error
          AL_PARSE_ERR2( meaning, AL_GETMSG(ERR,069,2), meaning->getVcharText(), event->getVcharText() )
        }
      }
    }
  }
}


// Validate the external entity event meaning
void P_checkGenDB::validate_ee_event_meaning( AST *meaning,
                                            AST *event)
{
  if (dumpflag)
    meaning->dumpNode("validate_ee_event_meaning: ");

  I_Object_Instance* p_event = (I_Object_Instance*) event->getObjPtr();
  int num_found = 0;
  I_Attribute_Instance *mning = 
    find_Attribute_Instance_R2002_by_name( p_event, Description("MNING").char_ptr(), num_found );

  if (num_found > 0)
  {
    I_var* attr_val_ptr = mning->get_var_ptr ();
    if ( attr_val_ptr )
    {
      if ( attr_val_ptr->get_string_var_ptr() )
      {
        // event meanings in the gen DB have no ticks, event meanings
        // in the AST might or might not, so check and add the ticks
        // back if needed before comparing

        Description evt_mning;
        if ( meaning->getRelocType() == EVENT_MEANING_TICKED_FIELD )
	{
          evt_mning = Description("'");
		  evt_mning += attr_val_ptr->get_string_var_ptr()->get_value();
		  evt_mning += "'";
        }
        else if ( meaning->getRelocType() == EVENT_MEANING_FIELD )
	{
          evt_mning = attr_val_ptr->get_string_var_ptr()->get_value();
        }

        if ( evt_mning == meaning->getVcharText() )
	{
          meaning->setObjPtr(p_event);
	}
        else
        {
          // if the meaning doesn't match the label, generate this error
          AL_PARSE_ERR2( meaning, AL_GETMSG(ERR,069,2), meaning->getVcharText(), event->getVcharText() )
        }
      }
    }
  }
}


// Validate event data item name
void P_checkGenDB::validate_rcvd_evt_data_item_name( AST *name,
                                                   AST *event)
{
  if (dumpflag)
    name->dumpNode("validate_rcvd_evt_data_item_name: ");

  // convert event pointer to an sevt instance
  // if not_empty sevt
  //   select one evt related by sevt->SM_EVT[R525]
  //   select one nlevt related by sevt->SM_NLEVT[R526]
  //   if not_empty nlevt
  //     select one pevt related by nlevt->SM_PEVT[R527]
  //     if ( empty pevt )
  //        error 157
  //     else
  //       select one evt related by pevt->SM_EVT[R525]
  //     end if
  //   end if
  // end if
  // select many edis related by evt->SM_EVTDI[R532]  
  // for each edi in edis
  //  if edi.Name == name->getVcharText()
  //    break;
  //  end if;
  // end for;

  I_Object_Instance *event_ptr = (I_Object_Instance *) event->getObjPtr();

  mc_dbms_List<I_Object_Instance*> inst_coll;
  inst_coll.insert_last(event_ptr);
  I_Object* p_obj = event_ptr->get_Object_R2001_ptr();

  I_object_inst_ref_set_var* inst_set_var_ptr = 
    new I_object_inst_ref_set_var (p_obj, &inst_coll);

  I_object_inst_ref_set_var* evt = 0;

  I_object_inst_ref_set_var* sevt =
        GS_select::create_single_link( inst_set_var_ptr, "SM_SEVT", "R525", "");

  if ( sevt->cardinality() != 0 )
  {
    evt = GS_select::create_single_link( sevt, "SM_EVT", "R525", "");
    I_object_inst_ref_set_var* nlevt =
        GS_select::create_single_link( sevt, "SM_NLEVT", "R526", "");
    if ( nlevt->cardinality() != 0 )
      {
          I_object_inst_ref_set_var* pevt =
              GS_select::create_single_link( nlevt, "SM_PEVT", "R527", "");
          if ( pevt->cardinality() == 0 )
          {
              AL_PARSE_ERR1( name, AL_GETMSG(ERR,157,1), name->getVcharText() )
          }
          else
          {  
              evt =
                  GS_select::create_single_link( pevt, "SM_EVT", "R525", "");
          }
          delete pevt;
      }
    delete nlevt;
  }


  if (evt != 0 && evt->cardinality() != 0) {
    I_object_inst_ref_set_var* edis =
      GS_select::create_single_link( evt, "SM_EVTDI", "R532", "");

    I_Object_Instance * edi_ptr;
    FIRST_ELEMENT( edi_ptr,
                   I_Object_Instance, 
                   &(edis->m_oinst_coll),
                   evt_cursor );

    int num_found = 0;
    while ( edi_ptr )
    {
      I_Attribute_Instance *nm = 
        find_Attribute_Instance_R2002_by_name( edi_ptr, Description("NAME").char_ptr(), num_found );

      if (num_found > 0)
      {
        I_var* attr_val_ptr = nm->get_var_ptr ();
        if ( attr_val_ptr )
          if ( attr_val_ptr->get_string_var_ptr() )
            if ( vcharCompare (attr_val_ptr->get_string_var_ptr()->get_value().char_ptr(), 
                         name->getVcharText()) == 0 )
            {
              break;
            }
      }

      NEXT_ELEMENT( edi_ptr, evt_cursor );
    }

    if ( edi_ptr == NULL )
    {
      // Generate this error if the given data item is not associated with the event
      AL_PARSE_ERR1( name, AL_GETMSG(ERR,152,1), name->getVcharText() )
    }
    else
    {
      t_core_data_type dt = find_core_data_type ( edi_ptr, "R524" );

      name->setObjPtr(edi_ptr);
      name->setDatatype( dt );
    }

    delete edis;
  }
  delete evt;
  delete sevt;
  delete inst_set_var_ptr;
}


// Validate event data item name
void P_checkGenDB::validate_sm_event_data_items( AST *event,
                                               AST *data_items)
{
  if (data_items)
    if (dumpflag)
      data_items->dumpNode("validate_sm_event_data_items: ");


  // select many edis related by event->SM_EVTDI[R532]  
  // if (edis->cardinality > 0 and data_items != 0)
  //   for each edi in edis
  //     save edi and datatype
  //   end for
  // end if

  I_Object_Instance *event_ptr = (I_Object_Instance *) event->getObjPtr();

  mc_dbms_List<I_Object_Instance*> inst_coll;
  inst_coll.insert_last(event_ptr);
  I_Object* p_obj = event_ptr->get_Object_R2001_ptr();
  I_object_inst_ref_set_var* inst_set_var_ptr = 
    new I_object_inst_ref_set_var (p_obj, &inst_coll);

  I_object_inst_ref_set_var* edis =
    GS_select::create_single_link( inst_set_var_ptr, "SM_EVTDI", "R532", "");

  if ( data_items == NULL )
  {  
    if ( edis->cardinality() != 0 )
    {
      // Generate this error if some data items are missing
      AL_PARSE_ERR1( event, AL_GETMSG(ERR,073,1), event->getVcharText() )
    }
  }
  else
  {

    // If there are more data items in the database then were found in
    //  the parse, raise an error.
    if ( edis->cardinality() > data_items->nsiblings() )
    {
      AL_PARSE_ERR1( data_items, AL_GETMSG(ERR,073,1), event->getVcharText() )
    }
    else
    {

      I_Object_Instance * edi_ptr;
      FIRST_ELEMENT( edi_ptr,
                     I_Object_Instance, 
                     &(edis->m_oinst_coll),
                     evt_cursor );
  
      int num_found = 0;
  
      while ( edi_ptr )
      {
        I_Attribute_Instance *nm = 
          find_Attribute_Instance_R2002_by_name( edi_ptr, Description("NAME").char_ptr(), num_found );

        if (num_found > 0)
        {
          I_var* attr_val_ptr = nm->get_var_ptr ();
          if ( attr_val_ptr )
            if ( attr_val_ptr->get_string_var_ptr() )
            {
              AST *data_items_cursor = data_items;
              while ( data_items_cursor != NULL )
              {
                if (vcharCompare (attr_val_ptr->get_string_var_ptr()->get_value().char_ptr(), 
                            data_items_cursor->getVcharText()) == 0 )
                {
                  t_core_data_type dt = find_core_data_type ( edi_ptr, "R524" );
                  data_items_cursor->setObjPtr(edi_ptr);
                  data_items_cursor->setDatatype( dt );
                  break;
                }

                data_items_cursor = (AST *)data_items_cursor->right();
              }
            }
        }
        NEXT_ELEMENT( edi_ptr, evt_cursor );
      }
    }
  }

  delete edis;
  delete inst_set_var_ptr;
  
}


// Validate the relationship that ties together two objects. 
void P_checkGenDB::validate_rel_id( AST *id,
                                    AST *from,
                                    AST *to,
                                    AST *rel_phrase,
                                    Obj_Card_e card_expected,
                                    bool &manyFound )
{
  if (dumpflag)
    id->dumpNode("validate_rel_id: ");

  // Not going to do any real validation since 
  // the action language is already parsed by Model Builder
  // Just get the appropriate R_REL

  // Set to TRUE so that there's no error checking in parser.
  manyFound = TRUE;

  // If we wanted to waste CPU time and actually return the
  // correct value, here's what we'd do:
  //Obj_Card_e card = get_right_obj_card(id, from, to);
  //if ( card == CARD_MANY )
  //{
  //  manyFound = TRUE;
  //}

  // select many rels from instances of R_REL
  // for each rel in rels 
  //   if ( rel.Numb == atoi(id->getVcharText()) )
  //     save info
  //     break
  //   end if
  // end for

  
  mc_dbms_Set<I_Object*>* rel_objs = 
       I_Object::find_Object_by_key_letter( GS_gen_sim_db_ptr, "R_REL" );
  if ( rel_objs->cardinality() < 1 )
  {
    // Generate this error if the relationship does not exist
    // AL_PARSE_ERR1( id, AL_GETMSG(ERR,173,1), id->getVcharText() )
  }
  else
  {
    I_Object* rel_obj = rel_objs->pick();

	// Strip leading [Rr] from relationship id
	const vchar *rel_num_text = id->getVcharText();
	const vchar R = vcharFromASCII('R');
	const vchar r = vcharFromASCII('r');
  
	if ( (rel_num_text[0] == R) || (rel_num_text[0] == r) )
    {
      ++rel_num_text;
    }
	
    t_int rel_num = -1;
	
    vexWITH_HANDLING {
		rel_num = vnumParseInt(rel_num_text, 0);
	} vexON_EXCEPTION {
	} vexEND_HANDLING;

    int num_found = 0;
    I_Object_Instance* rel_ptr;
    FIRST_ELEMENT( rel_ptr,
                   I_Object_Instance,
                   rel_obj->get_Object_Instance_R2001_coll_ptr(),
                   cursor );
      
    while( rel_ptr )
    {
      I_Attribute_Instance *numb = 
        find_Attribute_Instance_R2002_by_name( rel_ptr, Description("NUMB").char_ptr(), num_found );

      if (num_found > 0)
      {
        I_var* n_ptr = numb->get_var_ptr ();
        if ( n_ptr )
          if ( n_ptr->get_integer_var_ptr() )
            if ( n_ptr->get_integer_var_ptr()->get_value() ==  rel_num )
            {
              break;
            }
      }

      NEXT_ELEMENT( rel_ptr, cursor );
    }

    if ( rel_ptr == NULL )
    {
      // Generate this error if the relationship does not exist
      // AL_PARSE_ERR1( id, AL_GETMSG(ERR,173,1), id->getVcharText() )
    }
    else
    {
      id->setObjPtr(rel_ptr);
    }
  }

  delete rel_objs;
}

// Validate the objects and relationship for a relate/unrelate.
void P_checkGenDB::validate_relate( AST *id,
                                    AST *from,
                                    AST *to,
                                    AST *rel_phrase)
{
  if (dumpflag)
    id->dumpNode("validate_relate: ");

  // Do all the regular relationship validation
  bool multFound = FALSE;
  Obj_Card_e card = CARD_UNKNOWN;
  validate_rel_id (id, from, to, rel_phrase, card, multFound );

}

// Validate the associative relationship that ties together three objects. 
void P_checkGenDB::validate_assoc_relate( AST *id,
                                          AST *from,
                                          AST *to,
                                          AST *assoc,
                                          AST *rel_phrase)
{
  if (dumpflag)
    id->dumpNode("validate_assoc_relate: ");
  
  // Validate the relationship
  bool multFound = FALSE;
  Obj_Card_e card = CARD_UNKNOWN;
  validate_rel_id (id, from, to, rel_phrase, card, multFound );

}

// Validate the relationship phrase
void P_checkGenDB::validate_rel_phrase( AST *rel_phrase,
                                        AST *rel,
                                        AST *kl)
{
  if (dumpflag)
    rel_phrase->dumpNode("validate_rel_phrase: ");

  // select any simp related by rel->R_SIMP[R206]
  // if ( cardinality(simp) != 0 )
  //   select one part related by simp->R_PART[R207]
  //   if ( part.Txt_Phrs == rel_phrase->getVcharText() )
  //     found it
  //   else
  //     select one form related by simp->R_FORM[R208]
  //     if ( form.Txt_Phrs == rel_phrase->getVcharText() )
  //       found it
  //     end if
  //   end if
  // else
  //   select any assoc related by rel->R_ASSOC[R206]
  //   if ( cardinality(assoc) != 0 )
  //     select one aone related by assoc->R_AONE[R209]
  //     if ( aone.Txt_Phrs == rel_phrase->getVcharText() )
  //       found it
  //     else
  //       select one aoth related by assoc->R_AOTH[R210]
  //       if ( aoth.Txt_Phrs == rel_phrase->getVcharText() )
  //         found it
  //       end if
  //     end if
  //   end if
  // end if
  // 

  int num_found = 0;

  I_Object_Instance *rel_ptr = (I_Object_Instance *) rel->getObjPtr();
  mc_dbms_List<I_Object_Instance*> inst_coll;
  inst_coll.insert_last(rel_ptr);
  I_Object* p_obj = rel_ptr->get_Object_R2001_ptr();
  I_object_inst_ref_set_var* inst_set_var_ptr = 
    new I_object_inst_ref_set_var (p_obj, &inst_coll);

  I_object_inst_ref_set_var* simp =
    GS_select::create_single_link( inst_set_var_ptr, "R_SIMP", "R206", "");

  if ( simp->cardinality() != 0 )
  {
    I_object_inst_ref_set_var* part =
      GS_select::create_single_link( simp, "R_PART", "R207", "");

    if ( part->cardinality() != 0 )
    {
      part->first();
      I_Attribute_Instance *txt_phrs = 
        find_Attribute_Instance_R2002_by_name( part->get_oinst_ptr(), Description("TXT_PHRS").char_ptr(), num_found );
      I_var* attr_val_ptr = txt_phrs->get_var_ptr ();
      if ( attr_val_ptr )
        if ( attr_val_ptr->get_string_var_ptr() )
        {
          if (vcharCompare (attr_val_ptr->get_string_var_ptr()->get_value().char_ptr(), 
                      rel_phrase->getVcharText()) == 0 )
          {
            rel_phrase->setObjPtr(part->get_oinst_ptr());
          }
        }
    }
    else
    {
      I_object_inst_ref_set_var* form =
        GS_select::create_single_link( simp, "R_FORM", "R208", "");

      if ( form->cardinality() != 0 )
      {
        form->first();
        I_Attribute_Instance *txt_phrs = 
          find_Attribute_Instance_R2002_by_name( form->get_oinst_ptr(), Description("TXT_PHRS").char_ptr(), num_found );
        I_var* attr_val_ptr = txt_phrs->get_var_ptr ();
        if ( attr_val_ptr )
          if ( attr_val_ptr->get_string_var_ptr() )
          {
            if (vcharCompare (attr_val_ptr->get_string_var_ptr()->get_value().char_ptr(), 
                        rel_phrase->getVcharText()) == 0 )
            {
              rel_phrase->setObjPtr(form->get_oinst_ptr());
            }
          }
      }
      delete form;
    }
    delete part;
  }  
  else
  {
    I_object_inst_ref_set_var* assoc =
      GS_select::create_single_link( inst_set_var_ptr, "R_ASSOC", "R206", "");

    if ( assoc->cardinality() != 0 )
    {
      I_object_inst_ref_set_var* aone =
        GS_select::create_single_link( assoc, "R_AONE", "R209", "");

      if ( aone->cardinality() != 0 )
      {
        aone->first();
        I_Attribute_Instance *txt_phrs = 
          find_Attribute_Instance_R2002_by_name( aone->get_oinst_ptr(), Description("TXT_PHRS").char_ptr(), num_found );
        I_var* attr_val_ptr = txt_phrs->get_var_ptr ();
        if ( attr_val_ptr )
          if ( attr_val_ptr->get_string_var_ptr() )
          {
            if (vcharCompare (attr_val_ptr->get_string_var_ptr()->get_value().char_ptr(), 
                        rel_phrase->getVcharText()) == 0 )
            {
              rel_phrase->setObjPtr(aone->get_oinst_ptr());
            }
          }
      }
      else
      {
        I_object_inst_ref_set_var* aoth =
          GS_select::create_single_link( assoc, "R_AOTH", "R210", "");

        if ( aoth->cardinality() != 0 )
        {
          aoth->first();
          I_Attribute_Instance *txt_phrs = 
            find_Attribute_Instance_R2002_by_name( aoth->get_oinst_ptr(), Description("TXT_PHRS").char_ptr(), num_found );
          I_var* attr_val_ptr = txt_phrs->get_var_ptr ();
          if ( attr_val_ptr )
            if ( attr_val_ptr->get_string_var_ptr() )
            {
              if (vcharCompare (attr_val_ptr->get_string_var_ptr()->get_value().char_ptr(), 
                          rel_phrase->getVcharText()) == 0 )
              {
                rel_phrase->setObjPtr(aoth->get_oinst_ptr());
              }
            }
        }
        delete aoth;
      }
      delete aone;
    }
    delete assoc;
  }
  delete simp;
  delete inst_set_var_ptr;
}

// Validate the relationship phrase using inst_ref_var
void P_checkGenDB::validate_rel_phrase_irv( AST *rel_phrase,
                                            AST *rel,
                                            AST *irv)
{
  if (dumpflag)
    rel_phrase->dumpNode("validate_rel_phrase_irv: ");

  // since validate_rel_phrase doesn't need the key letters,
  // just use it.
  validate_rel_phrase(rel_phrase, rel, 0);
}


// Validate the external entity key letters
void P_checkGenDB::validate_ee_kl (AST *kl)
{
  if (dumpflag)
    kl->dumpNode("validate_ee_kl: ");
  kl->setObjPtr(0);     // make sure it has an illegal value in case of error.
  
  // select many results from instances of S_EE where selected.Key_Lett == kl->getVcharText()
  
  bool mult_found = FALSE;
  I_Attribute_Instance* result = get_attribute_instance_by_name( 
      "S_EE", "KEY_LETT", kl->getVcharText(), mult_found );

  // Generate this error if the keyletters can't be found
  if ( result == 0 )
  {
    AL_PARSE_ERR1( kl, AL_GETMSG(ERR,100,1), kl->getVcharText() )
  }

  // Generate this error if there's more than one external entity with keyletters kl
  else if ( mult_found )
  {
    AL_PARSE_ERR1( kl, AL_GETMSG(ERR,021,1), kl->getVcharText() )
  }
  else
  {
    I_Object_Instance *obj_inst = result->get_Object_Instance_R2002_ptr();
    kl->setObjPtr(obj_inst);
  }

}

// Validate the external entity event data item name
void P_checkGenDB::validate_ee_event_data_items( AST *event,
                                               AST *data_items)
{
  if (data_items)
    if (dumpflag)
      data_items->dumpNode("validate_ee_event_data_items: ");

  // select many eeedts related by event->S_EEEDT[R13]
  // select many eeedis related by eeedts->S_EEEDI[R13]  
  // if (eeedis->cardinality > 0 and data_items != 0)
  //   for each eeedi in eeedis
  //     save eeedi and datatype
  //   end for
  // end if

  I_Object_Instance *event_ptr = (I_Object_Instance *) event->getObjPtr();

  mc_dbms_List<I_Object_Instance*> inst_coll;
  inst_coll.insert_last(event_ptr);
  I_Object* p_obj = event_ptr->get_Object_R2001_ptr();
  I_object_inst_ref_set_var* inst_set_var_ptr = 
    new I_object_inst_ref_set_var (p_obj, &inst_coll);

  I_object_inst_ref_set_var* eeedts =
    GS_select::create_single_link( inst_set_var_ptr, "S_EEEDT", "R13", "");
  
  I_object_inst_ref_set_var* eeedis =
    GS_select::create_single_link( eeedts, "S_EEEDI", "R13", "");

  if ( data_items == NULL )
  {  
    if ( eeedis->cardinality() != 0 )
    {
      // Generate this error if some data items are missing
      AL_PARSE_ERR1( event, AL_GETMSG(ERR,073,1), event->getVcharText() )
    }
  }
  else
  {
    // If there are more data items in the database then were found in
    //  the parse, raise an error.
    if ( eeedis->cardinality() > data_items->nsiblings() )
    {
      AL_PARSE_ERR1( data_items, AL_GETMSG(ERR,073,1), event->getVcharText() )
    }
    else
    {
      I_Object_Instance * eeedi_ptr;
      FIRST_ELEMENT( eeedi_ptr,
                     I_Object_Instance, 
                     &(eeedis->m_oinst_coll),
                     di_cursor );
  
      int num_found = 0;
      while ( eeedi_ptr )
      {
        I_Attribute_Instance *nm = 
          find_Attribute_Instance_R2002_by_name( eeedi_ptr, Description("NAME").char_ptr(), num_found );

        if (num_found > 0)
        {
          I_var* attr_val_ptr = nm->get_var_ptr ();
          if ( attr_val_ptr )
            if ( attr_val_ptr->get_string_var_ptr() )
	    {
              AST *data_items_cursor = data_items;
              while ( data_items_cursor != NULL )
              {
                if (vcharCompare (attr_val_ptr->get_string_var_ptr()->get_value().char_ptr(), 
                            data_items_cursor->getVcharText()) == 0 )
                {
                  t_core_data_type dt = find_core_data_type ( eeedi_ptr, "R16" );
                  data_items_cursor->setObjPtr(eeedi_ptr);
                  data_items_cursor->setDatatype( dt );
                  break;
                }

                data_items_cursor = (AST *)data_items_cursor->right();
              }
            }
        }
        NEXT_ELEMENT( eeedi_ptr, di_cursor );
      }
    }
  }
  delete eeedis;
  delete eeedts;
  delete inst_set_var_ptr;

}

// Validate the bridge name
void P_checkGenDB::validate_bridge( AST *bridge,
                                     AST *ee)
{
  if (dumpflag)
    bridge->dumpNode("validate_bridge: ");

  // select many brgs related by ee->S_BRG[R19];
  // for each brg in brgs
  //   if brg.Name == bridge->getVcharText()
  //     save info
  //     break
  //   end if
  // end for
  I_Object_Instance* p_ee = (I_Object_Instance*) ee->getObjPtr();
  I_Object* p_obj = p_ee->get_Object_R2001_ptr();

  mc_dbms_List<I_Object_Instance*> inst_coll;
  inst_coll.insert_last(p_ee);
  I_object_inst_ref_set_var* inst_set_var_ptr = 
    new I_object_inst_ref_set_var (p_obj, &inst_coll);

  I_object_inst_ref_set_var* brgs =
    GS_select::create_single_link( inst_set_var_ptr, "S_BRG", "R19", "");

  int num_found = 0;
  I_Object_Instance* brg_ptr;
  FIRST_ELEMENT( brg_ptr,
                 I_Object_Instance,
                 &(brgs->m_oinst_coll),
                 cursor );
      
  while( brg_ptr )
  {
    I_Attribute_Instance *name = 
      find_Attribute_Instance_R2002_by_name( brg_ptr, Description("NAME").char_ptr(), num_found );

    if (num_found > 0)
    {
      I_var* n_ptr = name->get_var_ptr ();
      if ( n_ptr )
        if ( n_ptr->get_string_var_ptr() )
          if ( vcharCompare (n_ptr->get_string_var_ptr()->get_value().char_ptr(), 
                       bridge->getVcharText()) == 0 )
          {
            break;
          }
    }

    NEXT_ELEMENT( brg_ptr, cursor );
  }

  if ( brg_ptr == NULL )
  {
    // Generate this if the bridge does not exist for this EE
    AL_PARSE_ERR2( bridge, AL_GETMSG(ERR,226,2), bridge->getVcharText(), ee->getVcharText() )
  }
  else
  {
    t_core_data_type dt = find_core_data_type ( brg_ptr, "R20" );

    bridge->setObjPtr(brg_ptr);

    if ( dt == UNKNOWN_DATATYPE )
    {
      // Generate this if the bridge has not been assigned a return type
      AL_PARSE_ERR2( bridge, AL_GETMSG(ERR,220,2), bridge->getVcharText(), ee->getVcharText() )
    }
    else
    {
      bridge->setDatatype( dt );
    }
  }

  delete brgs;
  delete inst_set_var_ptr;
}

// Validate the bridge parameter name
void P_checkGenDB::validate_bridge_data_item( AST *data_item,
                                  AST *bridge,
                                  Assign_Val_e isLval )
{
  if (data_item)
    if (dumpflag)
      data_item->dumpNode("validate_bridge_data_item: ");

  // select many bparms related by bridge->S_BPARM[R21]
  // for each bparm in bparms
  //   if bparm.Name == data_item.name
  //     save bparm and datatype
  //     break
  //   end if
  // end for

    I_Object_Instance *bridge_ptr = (I_Object_Instance *) bridge->getObjPtr();
    
    mc_dbms_List<I_Object_Instance*> inst_coll;
    inst_coll.insert_last(bridge_ptr);
    I_Object* p_obj = bridge_ptr->get_Object_R2001_ptr();
    I_object_inst_ref_set_var* inst_set_var_ptr = 
        new I_object_inst_ref_set_var (p_obj, &inst_coll);
    
    I_object_inst_ref_set_var* bparms =
        GS_select::create_single_link( inst_set_var_ptr, "S_BPARM", "R21", "");
    
    I_Object_Instance * bparm_ptr;
    FIRST_ELEMENT( bparm_ptr,
        I_Object_Instance, 
        &(bparms->m_oinst_coll),
        evt_cursor );
    
    int num_found = 0;
    
    while ( bparm_ptr )
    {
        I_Attribute_Instance *nm = 
            find_Attribute_Instance_R2002_by_name( bparm_ptr, Description("NAME").char_ptr(), num_found );
        
        if (num_found > 0)
        {
            I_var* attr_val_ptr = nm->get_var_ptr ();
            if ( attr_val_ptr )
            {
                if ( attr_val_ptr->get_string_var_ptr() )
                {
                    if (vcharCompare (attr_val_ptr->get_string_var_ptr()->get_value().char_ptr(), 
                        data_item->getVcharText()) == 0 )
                    {
                        t_core_data_type dt = find_core_data_type ( bparm_ptr, "R22" );
                        data_item->setObjPtr(bparm_ptr);
                        data_item->setDatatype( dt );
                        break;
                    }
                }
            }
        }
        NEXT_ELEMENT( bparm_ptr, evt_cursor );
    }

    delete bparms;
    delete inst_set_var_ptr;
}

// Validate all bridge parameters
void P_checkGenDB::validate_bridge_data_items( AST *bridge,
                                             AST *data_items)
{
  if (data_items)
    if (dumpflag)
      data_items->dumpNode("validate_bridge_data_items: ");

  // select many bparms related by bridge->S_BPARM[R21]
  // if (bparms->cardinality > 0 and data_items != 0)
  //   for each bparm in bparms
  //     save bparm and datatype
  //   end for
  // end if

  I_Object_Instance *bridge_ptr = (I_Object_Instance *) bridge->getObjPtr();

  mc_dbms_List<I_Object_Instance*> inst_coll;
  inst_coll.insert_last(bridge_ptr);
  I_Object* p_obj = bridge_ptr->get_Object_R2001_ptr();
  I_object_inst_ref_set_var* inst_set_var_ptr = 
    new I_object_inst_ref_set_var (p_obj, &inst_coll);

  I_object_inst_ref_set_var* bparms =
    GS_select::create_single_link( inst_set_var_ptr, "S_BPARM", "R21", "");
  
  if ( data_items == NULL )
  {  
    if ( bparms->cardinality() != 0 )
    {
      // Generate this error if some data items are missing
      // HACK- get the EE name for the error message
      AL_PARSE_ERR2( bridge, AL_GETMSG(ERR,221,2), bridge->getVcharText(), vcharScribeASCIIShared("???") )
    }
  }
  else
  {
    // If there are more data items in the database then were found in
    //  the parse, raise an error.
    if ( bparms->cardinality() > data_items->nsiblings() )
    {
      AL_PARSE_ERR1( data_items, AL_GETMSG(ERR,222,1), bridge->getVcharText() )
    }
    else
    {

      I_Object_Instance * bparm_ptr;
      FIRST_ELEMENT( bparm_ptr,
                     I_Object_Instance, 
                     &(bparms->m_oinst_coll),
                     evt_cursor );
  
      int num_found = 0;

      while ( bparm_ptr )
      {
        I_Attribute_Instance *nm = 
          find_Attribute_Instance_R2002_by_name( bparm_ptr, Description("NAME").char_ptr(), num_found );

        if (num_found > 0)
        {
          I_var* attr_val_ptr = nm->get_var_ptr ();
          if ( attr_val_ptr )
            if ( attr_val_ptr->get_string_var_ptr() )
	    {
              AST *data_items_cursor = data_items;
              while ( data_items_cursor != NULL )
	      {
                if (vcharCompare (attr_val_ptr->get_string_var_ptr()->get_value().char_ptr(), 
                            data_items_cursor->getVcharText()) == 0 )
                {
                  t_core_data_type dt = find_core_data_type ( bparm_ptr, "R22" );
                  data_items_cursor->setObjPtr(bparm_ptr);
                  data_items_cursor->setDatatype( dt );
                  break;
                }

                data_items_cursor = (AST *)data_items_cursor->right();
              }
            }
        }
        NEXT_ELEMENT( bparm_ptr, evt_cursor );
      }
    }
  }
  delete bparms;
  delete inst_set_var_ptr;

}

// Validate the synch service name
void P_checkGenDB::validate_synch_svc( AST *ss)
{
  if (dumpflag)
    ss->dumpNode("validate_synch_svc: ");

  ss->setObjPtr(0);     
  
  // select many results from instances of S_SYNC where selected.NAME == ss->getVcharText()
  
  bool mult_found = FALSE;
  I_Attribute_Instance* result = get_attribute_instance_by_name( 
      "S_SYNC", "NAME", ss->getVcharText(), mult_found );


  // Generate this error if the ss can't be found
  if ( result == 0 )
  {
      AL_PARSE_ERR1( ss, AL_GETMSG(ERR,247,1), ss->getVcharText() )
  }
  // Generate this error if there's more than one object with keyletters kl
  else if ( mult_found )
  {
      AL_PARSE_ERR1( ss, AL_GETMSG(ERR,248,1), ss->getVcharText() )
  }
  else
  {
    I_Object_Instance *obj_inst = result->get_Object_Instance_R2002_ptr();
    ss->setObjPtr(obj_inst);
  }

}

// Validate all bridge parameters
void P_checkGenDB::validate_synch_svc_data_items( AST *synch_svc,
                                             AST *data_items)
{
  if (data_items)
    if (dumpflag)
      data_items->dumpNode("validate_synch_svc_data_items: ");

  // select many sparms related by synch_svc->S_SPARM[R24]
  // if (sparms->cardinality > 0 and data_items != 0)
  //   for each sparm in sparms
  //     save sparm and datatype
  //   end for
  // end if

  I_Object_Instance *ss_ptr = (I_Object_Instance *) synch_svc->getObjPtr();

  mc_dbms_List<I_Object_Instance*> inst_coll;
  inst_coll.insert_last(ss_ptr);
  I_Object* p_obj = ss_ptr->get_Object_R2001_ptr();
  I_object_inst_ref_set_var* inst_set_var_ptr = 
    new I_object_inst_ref_set_var (p_obj, &inst_coll);

  I_object_inst_ref_set_var* sparms =
    GS_select::create_single_link( inst_set_var_ptr, "S_SPARM", "R24", "");
  
  if ( data_items == NULL )
  {  
    if ( sparms->cardinality() != 0 )
    {
      // Generate this error if there are extra data items
      AL_PARSE_ERR1( synch_svc, AL_GETMSG(ERR,201,1),
                         synch_svc->getVcharText() )
    }
  }
  else
  {
    // If there are more data items in the database then were found in
    //  the parse, raise an error.
    if ( sparms->cardinality() > data_items->nsiblings() )
    {
      AL_PARSE_ERR1( data_items, AL_GETMSG(ERR,201,1), synch_svc->getVcharText() )
    }
    else
    {

      I_Object_Instance * sparm_ptr;
      FIRST_ELEMENT( sparm_ptr,
                     I_Object_Instance, 
                     &(sparms->m_oinst_coll),
                     evt_cursor );
  
      int num_found = 0;

      while ( sparm_ptr )
      {
        I_Attribute_Instance *nm = 
          find_Attribute_Instance_R2002_by_name( sparm_ptr, Description("NAME").char_ptr(), num_found );

        if (num_found > 0)
        {
          I_var* attr_val_ptr = nm->get_var_ptr ();
          if ( attr_val_ptr )
            if ( attr_val_ptr->get_string_var_ptr() )
	    {
              AST *data_items_cursor = data_items;
              while ( data_items_cursor != NULL )
	      {
                if (vcharCompare (attr_val_ptr->get_string_var_ptr()->get_value().char_ptr(), 
                            data_items_cursor->getVcharText()) == 0 )
                {
                  t_core_data_type dt = find_core_data_type ( sparm_ptr, "R26" );
                  data_items_cursor->setObjPtr(sparm_ptr);
                  data_items_cursor->setDatatype( dt );
                  break;
                }

                data_items_cursor = (AST *)data_items_cursor->right();
              }
            }
        }
        NEXT_ELEMENT( sparm_ptr, evt_cursor );
      }
    }
  }
  delete sparms;
  delete inst_set_var_ptr;

}

// Validate the synch service parameter name
void P_checkGenDB::validate_synch_svc_data_item( AST *data_item,
                                  AST *synch_svc,
                                  Assign_Val_e isLval )
{
  if (data_item)
    if (dumpflag)
      data_item->dumpNode("validate_bridge_data_item: ");

  // select many sparms related by synch_service->S_SPARM[R24]
  // for each sparm in sparms
  //   if sparm.Name == data_item.name
  //     save sparm and datatype
  //     break
  //   end if
  // end for

    I_Object_Instance *ss_ptr = (I_Object_Instance *) synch_svc->getObjPtr();
    
    mc_dbms_List<I_Object_Instance*> inst_coll;
    inst_coll.insert_last(ss_ptr);
    I_Object* p_obj = ss_ptr->get_Object_R2001_ptr();
    I_object_inst_ref_set_var* inst_set_var_ptr = 
        new I_object_inst_ref_set_var (p_obj, &inst_coll);
    
    I_object_inst_ref_set_var* sparms =
        GS_select::create_single_link( inst_set_var_ptr, "S_SPARM", "R24", "");
    
    I_Object_Instance * sparm_ptr;
    FIRST_ELEMENT( sparm_ptr,
        I_Object_Instance, 
        &(sparms->m_oinst_coll),
        evt_cursor );
    
    int num_found = 0;
    
    while ( sparm_ptr )
    {
        I_Attribute_Instance *nm = 
            find_Attribute_Instance_R2002_by_name( sparm_ptr, Description("NAME").char_ptr(), num_found );
        
        if (num_found > 0)
        {
            I_var* attr_val_ptr = nm->get_var_ptr ();
            if ( attr_val_ptr )
            {
                if ( attr_val_ptr->get_string_var_ptr() )
                {
                    if (vcharCompare (attr_val_ptr->get_string_var_ptr()->get_value().char_ptr(), 
                        data_item->getVcharText()) == 0 )
                    {
                        t_core_data_type dt = find_core_data_type ( sparm_ptr, "R26" );
                        data_item->setObjPtr(sparm_ptr);
                        data_item->setDatatype( dt );
                        break;
                    }
                }
            }
        }
        NEXT_ELEMENT( sparm_ptr, evt_cursor );
    }

    delete sparms;
    delete inst_set_var_ptr;
}

// Validate the transformer name
void P_checkGenDB::validate_transformer( AST *transformer,
                                         AST *obj,
                                         bool isInstanceBased )
{
  if (dumpflag)
    transformer->dumpNode("validate_transformer: ");

  // select many trfs related by obj->O_TFR[R115];
  // for each trf in trfs
  //   if trf.Name == transformer->getVcharText()
  //     save info
  //     break
  //   end if
  // end for
  I_Object_Instance* p_obj_inst = (I_Object_Instance*) obj->getObjPtr();
  I_Object* p_obj = p_obj_inst->get_Object_R2001_ptr();

  mc_dbms_List<I_Object_Instance*> inst_coll;
  inst_coll.insert_last(p_obj_inst);
  I_object_inst_ref_set_var* inst_set_var_ptr = 
    new I_object_inst_ref_set_var (p_obj, &inst_coll);

  I_object_inst_ref_set_var* trfs =
    GS_select::create_single_link( inst_set_var_ptr, "O_TFR", "R115", "");

  int num_found = 0;
  I_Object_Instance* trf_ptr;
  FIRST_ELEMENT( trf_ptr,
                 I_Object_Instance,
                 &(trfs->m_oinst_coll),
                 cursor );
      
  while( trf_ptr )
  {
    I_Attribute_Instance *name = 
      find_Attribute_Instance_R2002_by_name( trf_ptr, Description("NAME").char_ptr(), num_found );

    if (num_found > 0)
    {
      I_var* n_ptr = name->get_var_ptr ();
      if ( n_ptr )
        if ( n_ptr->get_string_var_ptr() )
          if ( vcharCompare (n_ptr->get_string_var_ptr()->get_value().char_ptr(), 
                       transformer->getVcharText()) == 0 )
          {
            break;
          }
    }

    NEXT_ELEMENT( trf_ptr, cursor );
  }

  if ( trf_ptr == NULL )
  {
    // Generate this if the transformer does not exist for this object
    // AL_PARSE_ERR2( transformer, AL_GETMSG(ERR,227,2), transformer->getVcharText(), obj->getVcharText() )
  }
  else
  {
    t_core_data_type dt = find_core_data_type ( trf_ptr, "R116" );

    transformer->setObjPtr(trf_ptr);

    if ( dt == UNKNOWN_DATATYPE )
    {
      // Generate this if the transformer has not been assigned a return type
      AL_PARSE_ERR2( transformer, AL_GETMSG(ERR,230,2), transformer->getVcharText(), obj->getVcharText() )
    }
    else
    {
      transformer->setDatatype( dt );
    }
  }

  delete trfs;
  delete inst_set_var_ptr;

}

// Validate the transformer parameter name
void P_checkGenDB::validate_transformer_data_item( AST *data_item,
                                             AST *transformer,
                                       Assign_Val_e isLval)
{
  if (data_item)
    if (dumpflag)
      data_item->dumpNode("validate_transformer_data_item: ");

  // select many tparms related by transformer->O_TPARM[R117]
  // for each tparm in tparms
  //   if (tparm.Name == data_item )
  //     save tparm and datatype
  //     break
  //   end if
  // end for

  I_Object_Instance *transformer_ptr = (I_Object_Instance *) transformer->getObjPtr();

  mc_dbms_List<I_Object_Instance*> inst_coll;
  inst_coll.insert_last(transformer_ptr);
  I_Object* p_obj = transformer_ptr->get_Object_R2001_ptr();
  I_object_inst_ref_set_var* inst_set_var_ptr = 
    new I_object_inst_ref_set_var (p_obj, &inst_coll);

  I_object_inst_ref_set_var* tparms =
    GS_select::create_single_link( inst_set_var_ptr, "O_TPARM", "R117", "");
  

      I_Object_Instance * tparm_ptr;
      FIRST_ELEMENT( tparm_ptr,
                     I_Object_Instance, 
                     &(tparms->m_oinst_coll),
                     evt_cursor );
  
      int num_found = 0;
      while ( tparm_ptr )
      {
        I_Attribute_Instance *nm = 
          find_Attribute_Instance_R2002_by_name( tparm_ptr, Description("NAME").char_ptr(), num_found );

        if (num_found > 0)
        {
          I_var* attr_val_ptr = nm->get_var_ptr ();
          if ( attr_val_ptr )
            if ( attr_val_ptr->get_string_var_ptr() )
            {
                if (vcharCompare (attr_val_ptr->get_string_var_ptr()->get_value().char_ptr(), 
                            data_item->getVcharText()) == 0 )
                {
                  t_core_data_type dt = find_core_data_type ( tparm_ptr, "R118" );
                  data_item->setObjPtr(tparm_ptr);
                  data_item->setDatatype( dt );
                  break;
                }

            }
        }
        NEXT_ELEMENT( tparm_ptr, evt_cursor );
      }

  delete tparms;
  delete inst_set_var_ptr;

}

// Validate all the transformer parameter names
void P_checkGenDB::validate_transformer_data_items( AST *transformer,
                                             AST *data_items)
{
  if (data_items)
    if (dumpflag)
      data_items->dumpNode("validate_transformer_data_items: ");

  // select many tparms related by transformer->O_TPARM[R117]
  // if (tparms->cardinality > 0 and data_items != 0)
  //   for each tparm in tparms
  //     save tparm and datatype
  //   end for
  // end if

  I_Object_Instance *transformer_ptr = (I_Object_Instance *) transformer->getObjPtr();

  mc_dbms_List<I_Object_Instance*> inst_coll;
  inst_coll.insert_last(transformer_ptr);
  I_Object* p_obj = transformer_ptr->get_Object_R2001_ptr();
  I_object_inst_ref_set_var* inst_set_var_ptr = 
    new I_object_inst_ref_set_var (p_obj, &inst_coll);

  I_object_inst_ref_set_var* tparms =
    GS_select::create_single_link( inst_set_var_ptr, "O_TPARM", "R117", "");
  
  if ( data_items == NULL )
  {  
    if ( tparms->cardinality() != 0 )
    {
      // Generate this error if some data items are missing
      // HACK- get the OBJ name for the error message
      AL_PARSE_ERR2( transformer, AL_GETMSG(ERR,234,2), transformer->getVcharText(), "???" )
    }
  }
  else
  {
    // If there are more data items in the database then were found in
    //  the parse, raise an error.
    if ( tparms->cardinality() > data_items->nsiblings() )
    {
      AL_PARSE_ERR1( data_items, AL_GETMSG(ERR,231,1), transformer->getVcharText() )
    }
    else
    {

      I_Object_Instance * tparm_ptr;
      FIRST_ELEMENT( tparm_ptr,
                     I_Object_Instance, 
                     &(tparms->m_oinst_coll),
                     evt_cursor );
  
      int num_found = 0;
      while ( tparm_ptr )
      {
        I_Attribute_Instance *nm = 
          find_Attribute_Instance_R2002_by_name( tparm_ptr, Description("NAME").char_ptr(), num_found );

        if (num_found > 0)
        {
          I_var* attr_val_ptr = nm->get_var_ptr ();
          if ( attr_val_ptr )
            if ( attr_val_ptr->get_string_var_ptr() )
            {
              AST *data_items_cursor = data_items;
              while ( data_items_cursor != NULL )
              {
                if (vcharCompare (attr_val_ptr->get_string_var_ptr()->get_value().char_ptr(), 
                            data_items_cursor->getVcharText()) == 0 )
                {
                  t_core_data_type dt = find_core_data_type ( tparm_ptr, "R118" );
                  data_items_cursor->setObjPtr(tparm_ptr);
                  data_items_cursor->setDatatype( dt );
                  break;
                }

                data_items_cursor = (AST *)data_items_cursor->right();
	      }
            }
        }
        NEXT_ELEMENT( tparm_ptr, evt_cursor );
      }
    }
  }
  delete tparms;
  delete inst_set_var_ptr;

}

// Validate that object has an assigner state model
void P_checkGenDB::validate_obj_is_assigner( AST *kl )
{
  if (dumpflag)
    kl->dumpNode("validate_obj_is_assigner: ");

  kl->setObjPtr(0);
  validate_obj_kl(kl);
  if ( kl->getObjPtr() == 0 )
    return;

  // select one a_sm related by obj->SM_ASM[R519]
  // if ( cardinality(a_sm) == 0 )
  //    error -- no assigner state model
  // end if

  I_Object_Instance *object_ptr = (I_Object_Instance *) kl->getObjPtr();
  mc_dbms_List<I_Object_Instance*> inst_coll;
  inst_coll.insert_last(object_ptr);
  I_Object* p_obj = object_ptr->get_Object_R2001_ptr();
  I_object_inst_ref_set_var* inst_set_var_ptr = 
    new I_object_inst_ref_set_var (p_obj, &inst_coll);

  I_object_inst_ref_set_var* a_sm =
    GS_select::create_single_link( inst_set_var_ptr, "SM_ASM", "R519", "");

  if ( a_sm->cardinality() == 0 )
  {
    // Generate this if kl->objPtr does not have an assigner state model
    AL_PARSE_ERR1( kl, AL_GETMSG(ERR,151,1), kl->getVcharText() )
  }

  delete a_sm;
  delete inst_set_var_ptr;
}

// Validate that object has a creation state
void  P_checkGenDB::validate_obj_has_creation_state( AST *kl )
{
  if (dumpflag)
    kl->dumpNode("validate_obj_has_creation_state: ");
}

// Validate that the event label can be received by the external entity
void P_checkGenDB::validate_ee_event_label( AST *label,
                                            AST *ee )
{
  if (dumpflag)
    label->dumpNode("validate_ee_event_label: ");
 
  // select many events related by ee->S_EEEVT[R10]
  // for each evt in events
  //   if (evt.Drv_Lbl == label->getVcharText() )
  //      found_it 
  //      break;
  //   end if
  // end for

  I_Object_Instance *ee_ptr = (I_Object_Instance *) ee->getObjPtr();
  mc_dbms_List<I_Object_Instance*> inst_coll;
  inst_coll.insert_last(ee_ptr);
  I_Object* p_obj = ee_ptr->get_Object_R2001_ptr();
  I_object_inst_ref_set_var* inst_set_var_ptr = 
    new I_object_inst_ref_set_var (p_obj, &inst_coll);

  I_object_inst_ref_set_var* events =
    GS_select::create_single_link( inst_set_var_ptr, "S_EEEVT", "R10", "");

  I_Object_Instance * evt_ptr;
  FIRST_ELEMENT( evt_ptr,
                 I_Object_Instance, 
                 &(events->m_oinst_coll),
                 evt_cursor );

  int num_found = 0;
  while ( evt_ptr )
  {
    I_Attribute_Instance *drv_lbl = 
      find_Attribute_Instance_R2002_by_name( evt_ptr, Description("DRV_LBL").char_ptr(), num_found );

    if (num_found > 0)
    {
      I_var* el_ptr = drv_lbl->get_var_ptr ();
      if ( el_ptr )
        if ( el_ptr->get_string_var_ptr() )
          if ( vcharCompare (el_ptr->get_string_var_ptr()->get_value().char_ptr(), 
                       label->getVcharText()) == 0 )
          {
            label->setObjPtr(evt_ptr);
            break;
          }
    }

    NEXT_ELEMENT( evt_ptr, evt_cursor );
  }

  if ( evt_ptr == 0 )
  {
    // If event can't be found for this ee, generate this error message
    AL_PARSE_ERR2( label, AL_GETMSG(ERR,062,2), label->getVcharText(), ee->getVcharText())
  }

  delete events;
  delete inst_set_var_ptr;

}

// Validate the event label for an assigner
void P_checkGenDB::validate_assigner_event_label( AST *label,
                                                  AST *to_obj )
{
  if (dumpflag)
    label->dumpNode("validate_assigner_event_label: ");

  // warning: asm is a keyword!

  // select one sm_asm related by to_obj->SM_ASM[R519]
  // if ( cardinality(sm_asm) == 0 )
  //    error -- no assigner state model
  // else
  //   select one sm related by sm_asm->SM_SM[R517]
  //   select many events related by sm->SM_EVT[R502]
  //   for each evt in events
  //     if (evt.Drv_Lbl == label->getVcharText() )
  //        found_it 
  //        break;
  //     end if
  //   end for
  // end if

  I_Object_Instance *to_object_ptr = (I_Object_Instance *) to_obj->getObjPtr();
  mc_dbms_List<I_Object_Instance*> inst_coll;
  inst_coll.insert_last(to_object_ptr);
  I_Object* p_obj = to_object_ptr->get_Object_R2001_ptr();
  I_object_inst_ref_set_var* inst_set_var_ptr = 
    new I_object_inst_ref_set_var (p_obj, &inst_coll);

  I_object_inst_ref_set_var* sm_asm =
    GS_select::create_single_link( inst_set_var_ptr, "SM_ASM", "R519", "");

  if ( sm_asm->cardinality() == 0 )
  {
    AL_PARSE_ERR1( label, AL_GETMSG(ERR,151,1), to_obj->getVcharText() )
  }
  else
  {
    I_object_inst_ref_set_var* sm =
      GS_select::create_single_link( sm_asm, "SM_SM", "R517", "");

    I_object_inst_ref_set_var* events =
      GS_select::create_single_link( sm, "SM_EVT", "R502", "");

    if ( events->cardinality() == 0 )
    {
      AL_PARSE_ERR2( label, AL_GETMSG(ERR,065,2), label->getVcharText(),
                    to_obj->getVcharText() )
    }
    else
    {
      I_Object_Instance * evt_ptr;
      FIRST_ELEMENT( evt_ptr,
                     I_Object_Instance, 
                     &(events->m_oinst_coll),
                     evt_cursor );

      int num_found = 0;
      while ( evt_ptr )
      {
        I_Attribute_Instance *drv_lbl = 
          find_Attribute_Instance_R2002_by_name( evt_ptr, Description("DRV_LBL").char_ptr(), num_found );

        if (num_found > 0)
        {
          I_var* el_ptr = drv_lbl->get_var_ptr ();
          if ( el_ptr )
            if ( el_ptr->get_string_var_ptr() )
              if ( vcharCompare (el_ptr->get_string_var_ptr()->get_value().char_ptr(), 
                           label->getVcharText()) == 0 )
              {
                label->setObjPtr(evt_ptr);
                break;
	      }
        }

        NEXT_ELEMENT( evt_ptr, evt_cursor );
      }

      if ( evt_ptr == 0 )
      {
        // If the given event does not exist for this assigner, generate
        // this error message
        AL_PARSE_ERR2( label, AL_GETMSG(ERR,065,2), label->getVcharText(), to_obj->getVcharText() )
      }
    }
    delete events;
    delete sm;
  }

  delete sm_asm;
  delete inst_set_var_ptr;

}

// Validate the creation event label
void P_checkGenDB::validate_creator_event_label( AST *label,
                                                 AST *to_obj )
{
  if (dumpflag)
    label->dumpNode("validate_creator_event_label: ");

  // The generator doesn't need to verify that this is a creation
  // event, since the model builder would have done that already.
  // So we just validate the event normally.
  validate_obj_event_label(label, to_obj);
}

// Validate the enumerator for an enumeration
void P_checkGenDB::validate_enumerator( AST *enumeration,
                                   AST *enumerator)
{
  if (dumpflag)
    enumeration->dumpNode("validate_enumerator: ");

  // select one result from instances of S_DT where selected.Name == enumeration->getVcharText()
  // select one edt related by result->S_EDT[R17]
  
  bool mult_found = FALSE;
  I_Attribute_Instance* result = get_attribute_instance_by_name( 
      "S_DT", "NAME", enumeration->getVcharText(), mult_found );

  // Generate this error if the datatype can't be found
  if ( result == 0 )
  {
    AL_PARSE_ERR1( enumeration, AL_GETMSG(ERR,290,1), enumeration->getVcharText() )
  }
  // Generate this error if there's more than one datatype with the same name 
  else if ( mult_found )
  {
    AL_PARSE_ERR1( enumeration, AL_GETMSG(ERR,291,1), enumeration->getVcharText() )
  }
  else
  {
    I_Object_Instance *obj_inst = result->get_Object_Instance_R2002_ptr();

	  mc_dbms_List<I_Object_Instance*> inst_coll;
	  inst_coll.insert_last(obj_inst);
	  I_Object* p_obj = obj_inst->get_Object_R2001_ptr();
	  I_object_inst_ref_set_var* inst_set_var_ptr = 
		new I_object_inst_ref_set_var (p_obj, &inst_coll);

	I_object_inst_ref_set_var* edt =
		GS_select::create_single_link( inst_set_var_ptr, "S_EDT", "R17", "");

	if ( edt->cardinality() != 1 )
	{
        AL_PARSE_ERR1( enumeration, AL_GETMSG(ERR,291,1), enumeration->getVcharText() )
	}
	else
	{
        edt->first();
		enumeration->setObjPtr(edt->get_oinst_ptr());
        enumeration->setDatatype( ENUMERATION_DATATYPE );

		// select many result2 related by edt->S_ENUM[R27] where selected.name == enumerator->getVcharText()
		I_object_inst_ref_set_var* result2 =
			GS_select::create_single_link( edt, "S_ENUM", "R27", "");
	
		Description wc( "selected.name == \"" );
		wc += enumerator->getVcharText();
		wc += "\"";

		GS_select::interpret_frag__where_clause( result2, wc, FALSE );

		  // Generate this error if the enumerator can't be found
		  if ( result2->cardinality() == 0 )
		  {
			AL_PARSE_ERR2( enumeration, AL_GETMSG(ERR,292,2), enumeration->getVcharText(), enumerator->getVcharText() )
		  }
		  // Generate this error if there's more than one enumerator with the same name
		  else if ( result2->cardinality() > 1 )
		  {
			AL_PARSE_ERR2( enumeration, AL_GETMSG(ERR,293,2), enumeration->getVcharText(), enumerator->getVcharText() )
		  }
		  else
		  {
	        result2->first();
			I_Object_Instance *obj_inst = result2->get_oinst_ptr();
			enumerator->setObjPtr(obj_inst);
			enumerator->setDatatype( ENUMERATOR_DATATYPE );
		  }

		delete result2;
	}

	delete edt;
	delete inst_set_var_ptr;
  }
}

  //------------------------------------------------------------
  // Query functions
  //------------------------------------------------------------

// Determine if object keyletters is a valid object
bool P_checkGenDB::is_valid_obj_kl( AST *kl )
{
  if (dumpflag)
    kl->dumpNode("is_valid_obj_kl: ");

  // select many results from instances of O_OBJ where selected.Key_Lett == kl->getVcharText()
  
  bool mult_found = FALSE;
  I_Attribute_Instance* result = get_attribute_instance_by_name( 
      "O_OBJ", "KEY_LETT", kl->getVcharText(), mult_found );

  if ( result == 0 )
    return FALSE;
  else if ( mult_found )
    return FALSE;
  else
  {
    I_Object_Instance *obj_inst = result->get_Object_Instance_R2002_ptr();
    kl->setObjPtr( obj_inst );
    return TRUE;
  }

}

// Determine if transformer is valid for this object
bool P_checkGenDB::is_valid_transformer( AST *transformer,
                                         AST *obj_obj,
                                         bool isInstanceBased )
{
  if (dumpflag)
    transformer->dumpNode("is_valid_transformer: ");

  // select many trfs related by obj->O_TFR[R115];
  // for each trf in trfs
  //   if trf.Name == transformer->getVcharText()
  //     break
  //   end if
  // end for

  I_Object_Instance* p_obj_inst = (I_Object_Instance*) obj_obj->getObjPtr();
  I_Object* p_obj = p_obj_inst->get_Object_R2001_ptr();

  mc_dbms_List<I_Object_Instance*> inst_coll;
  inst_coll.insert_last(p_obj_inst);
  I_object_inst_ref_set_var* inst_set_var_ptr = 
    new I_object_inst_ref_set_var (p_obj, &inst_coll);

  I_object_inst_ref_set_var* trfs =
    GS_select::create_single_link( inst_set_var_ptr, "O_TFR", "R115", "");

  int num_found = 0;
  bool ret_val = FALSE;
  I_Object_Instance* trf_ptr;
  FIRST_ELEMENT( trf_ptr,
                 I_Object_Instance,
                 &(trfs->m_oinst_coll),
                 cursor );
      
  while( trf_ptr )
  {
    I_Attribute_Instance *name = 
      find_Attribute_Instance_R2002_by_name( trf_ptr, Description("NAME").char_ptr(), num_found );

    if (num_found > 0)
    {
      I_var* n_ptr = name->get_var_ptr ();
      if ( n_ptr )
        if ( n_ptr->get_string_var_ptr() )
          if ( vcharCompare (n_ptr->get_string_var_ptr()->get_value().char_ptr(), 
                       transformer->getVcharText()) == 0 )
          {
            transformer->setObjPtr(trf_ptr);
            ret_val = TRUE;
            break;
          }
    }

    NEXT_ELEMENT( trf_ptr, cursor );
  }

  delete trfs;
  delete inst_set_var_ptr;

  return ret_val;
}

// Determine if event label is valid for this object
bool P_checkGenDB::is_valid_obj_event_label( AST *label,
                                             AST *obj_obj )
{
  if (dumpflag)
    label->dumpNode("is_valid_obj_event_label: ");

  bool ret_val = FALSE;

  // select one ism related by to_obj->SM_ISM[R518]
  // if ( cardinality(ism) != 0 )
  //   select one sm related by ism->SM_SM[R517]
  //   select many events related by sm->SM_EVT[R502]
  //   for each evt in events
  //     if (evt.Drv_Lbl == label->getVcharText() )
  //        found_it 
  //        break;
  //     end if
  //   end for
  // end if

  I_Object_Instance *to_object_ptr = (I_Object_Instance *) obj_obj->getObjPtr();
  mc_dbms_List<I_Object_Instance*> inst_coll;
  inst_coll.insert_last(to_object_ptr);
  I_Object* p_obj = to_object_ptr->get_Object_R2001_ptr();
  I_object_inst_ref_set_var* inst_set_var_ptr = 
    new I_object_inst_ref_set_var (p_obj, &inst_coll);

  I_object_inst_ref_set_var* ism =
    GS_select::create_single_link( inst_set_var_ptr, "SM_ISM", "R518", "");

  if ( ism->cardinality() != 0 )
  {
    I_object_inst_ref_set_var* sm =
      GS_select::create_single_link( ism, "SM_SM", "R517", "");

    I_object_inst_ref_set_var* events =
      GS_select::create_single_link( sm, "SM_EVT", "R502", "");

    if ( events->cardinality() != 0 )
    {
      I_Object_Instance * evt_ptr;
      FIRST_ELEMENT( evt_ptr,
                     I_Object_Instance, 
                     &(events->m_oinst_coll),
                     evt_cursor );

      int num_found = 0;
      while ( evt_ptr )
      {
        I_Attribute_Instance *drv_lbl = 
          find_Attribute_Instance_R2002_by_name( evt_ptr, Description("DRV_LBL").char_ptr(), num_found );

        if (num_found > 0)
        {
          I_var* el_ptr = drv_lbl->get_var_ptr ();
          if ( el_ptr )
            if ( el_ptr->get_string_var_ptr() )
              if ( vcharCompare (el_ptr->get_string_var_ptr()->get_value().char_ptr(), 
                           label->getVcharText()) == 0 )
              {
                ret_val = TRUE;
                break;
	      }
        }

        NEXT_ELEMENT( evt_ptr, evt_cursor );
      }
    }
    delete events;
    delete sm;
  }

  delete ism;
  delete inst_set_var_ptr;

  return ret_val;
}

// Determine if there's an EE for the given keyletters
bool P_checkGenDB::is_valid_ee_kl( AST *kl )
{
  // select many results from instances of S_EE where selected.Key_Lett == kl->getVcharText()
  
  bool mult_found = FALSE;
  I_Attribute_Instance* result = get_attribute_instance_by_name
    ( "S_EE", "KEY_LETT", kl->getVcharText(), mult_found );

  if ( result == 0 )
    return FALSE;
  else if ( mult_found )
    return FALSE;
  else
  {
    I_Object_Instance *ee_inst = result->get_Object_Instance_R2002_ptr();
    kl->setObjPtr( ee_inst );
    return TRUE;
  }

}


// Determine if the bridge is valid for the ee
bool P_checkGenDB::is_valid_ee_bridge( AST *bridge,
                                       AST *ee)
{
  bool ret_val = TRUE;
  if (dumpflag)
    bridge->dumpNode("is_valid_ee_bridge: ");

  // select many brgs related by ee->S_BRG[R19];
  // for each brg in brgs
  //   if brg.Name == bridge->getVcharText()
  //     save info
  //     break
  //   end if
  // end for
  I_Object_Instance* p_ee = (I_Object_Instance*) ee->getObjPtr();
  I_Object* p_obj = p_ee->get_Object_R2001_ptr();

  mc_dbms_List<I_Object_Instance*> inst_coll;
  inst_coll.insert_last(p_ee);
  I_object_inst_ref_set_var* inst_set_var_ptr = 
    new I_object_inst_ref_set_var (p_obj, &inst_coll);

  I_object_inst_ref_set_var* brgs =
    GS_select::create_single_link( inst_set_var_ptr, "S_BRG", "R19", "");

  int num_found = 0;
  I_Object_Instance* brg_ptr;
  FIRST_ELEMENT( brg_ptr,
                 I_Object_Instance,
                 &(brgs->m_oinst_coll),
                 cursor );
      
  while( brg_ptr )
  {
    I_Attribute_Instance *name = 
      find_Attribute_Instance_R2002_by_name( brg_ptr, Description("NAME").char_ptr(), num_found );

    if (num_found > 0)
    {
      I_var* n_ptr = name->get_var_ptr ();
      if ( n_ptr )
        if ( n_ptr->get_string_var_ptr() )
          if ( vcharCompare (n_ptr->get_string_var_ptr()->get_value().char_ptr(), 
                       bridge->getVcharText()) == 0 )
          {
            break;
          }
    }

    NEXT_ELEMENT( brg_ptr, cursor );
  }

  if ( brg_ptr )
    {
      t_core_data_type dt = find_core_data_type ( brg_ptr, "R20" );
      
      bridge->setObjPtr(brg_ptr);
      
      if ( dt == UNKNOWN_DATATYPE )
        {
          ret_val = FALSE;
        }
      else
        {
          bridge->setDatatype( dt );
        }
    }
  else
    ret_val = FALSE;
  
  delete brgs;
  delete inst_set_var_ptr;

  return ret_val;
}

// Determine if event label is valid for this object
bool P_checkGenDB::is_valid_ee_event_label( AST *label,
                                            AST *ee )
{
  if (dumpflag)
    label->dumpNode("is_valid_ee_event_label: ");

  bool ret_val = FALSE;
 
  // select many events related by ee->S_EEEVT[R10]
  // for each evt in events
  //   if (evt.Drv_Lbl == label->getVcharText() )
  //      found_it 
  //      break;
  //   end if
  // end for

  I_Object_Instance *ee_ptr = (I_Object_Instance *) ee->getObjPtr();
  mc_dbms_List<I_Object_Instance*> inst_coll;
  inst_coll.insert_last(ee_ptr);
  I_Object* p_obj = ee_ptr->get_Object_R2001_ptr();
  I_object_inst_ref_set_var* inst_set_var_ptr = 
    new I_object_inst_ref_set_var (p_obj, &inst_coll);

  I_object_inst_ref_set_var* events =
    GS_select::create_single_link( inst_set_var_ptr, "S_EEEVT", "R10", "");

  I_Object_Instance * evt_ptr;
  FIRST_ELEMENT( evt_ptr,
                 I_Object_Instance, 
                 &(events->m_oinst_coll),
                 evt_cursor );

  int num_found = 0;
  while ( evt_ptr )
  {
    I_Attribute_Instance *drv_lbl = 
      find_Attribute_Instance_R2002_by_name( evt_ptr, Description("DRV_LBL").char_ptr(), num_found );

    if (num_found > 0)
    {
      I_var* el_ptr = drv_lbl->get_var_ptr ();
      if ( el_ptr )
        if ( el_ptr->get_string_var_ptr() )
          if ( vcharCompare (el_ptr->get_string_var_ptr()->get_value().char_ptr(), 
                       label->getVcharText()) == 0 )
          {
            ret_val = TRUE;
            break;
          }
    }

    NEXT_ELEMENT( evt_ptr, evt_cursor );
  }

  delete events;
  delete inst_set_var_ptr;

  return ret_val;
}

// Get the data type of the transformer data item
void P_checkGenDB::get_transformer_param_type( AST *data_item )
{
  I_Object_Instance* tparm_ptr = (I_Object_Instance*)data_item->getObjPtr();
  t_core_data_type dt = find_core_data_type ( tparm_ptr, "R118" );
  data_item->setDatatype( dt );
}

// Get the data type of the bridge data item
void P_checkGenDB::get_bridge_param_type( AST *data_item )
{
  I_Object_Instance* bparm_ptr = (I_Object_Instance*)data_item->getObjPtr();
  t_core_data_type dt = find_core_data_type ( bparm_ptr, "R22" );
  data_item->setDatatype( dt );
}


// Get the cardinality (Obj_Card_e) for the right object
Obj_Card_e P_checkGenDB::get_right_obj_card( AST *rel,
                                             AST *obj_left,
                                             AST *obj_right )
{
  if (dumpflag)
    rel->dumpNode("get_right_obj_card: ");

  Obj_Card_e ret_val = CARD_UNKNOWN;
  
  // select many oirs related by rel->R_OIR[R201]
  // for each oir in oirs
  //   if ( oir.Obj_ID == obj_right.Obj_ID )
  //     select one rto related by oir->R_RTO[R203]
  //     if ( rto->cardinality() != 0 )
  //       select one part related by rto->R_PART[R204]
  //       if ( part->cardinality() != 0 )
  //         return part.Mult ? CARD_ONE : CARD_MANY ;
  //       else
  //         select one aone related by rto->R_AONE[R204]
  //         if ( aone->cardinality() != 0 )
  //           return aone.Mult ? CARD_ONE : CARD_MANY ;
  //         else
  //           select one aoth related by rto->R_AOTH[R204]
  //           if ( aoth->cardinality() != 0 )
  //             return aoth.Mult ? CARD_ONE : CARD_MANY ;
  //           else
  //             select one super related by rto->R_SUPER[R204]
  //             if ( super->cardinality() != 0 )
  //               return super.Mult ? CARD_ONE : CARD_MANY ;
  //             end if
  //           end if
  //         end if
  //       end if
  //     else
  //       select one rgo related by oir->R_RGO[R203]
  //       if ( rgo->cardinality() != 0 )
  //         select one form related by rgo->R_FORM[R205]
  //         if ( form->cardinality() != 0 )
  //           return form.Mult ? CARD_ONE : CARD_MANY ;
  //         else
  //           select one assr related by rgo->R_ASSR[R205]
  //           if ( assr->cardinality() != 0 )
  //             return assr.Mult ? CARD_ONE : CARD_MANY ;
  //           else
  //             select one sub related by rgo->R_SUB[R205]
  //             if ( sub->cardinality() != 0 )
  //               return sub.Mult ? CARD_ONE : CARD_MANY ;
  //             end if
  //           end if
  //         end if
  //       end if
  //     end if
  //   end if
  // end for

  int num_found = 0;
  I_Object_Instance* right_obj_ptr = (I_Object_Instance *) obj_right->getObjPtr();
  I_Attribute_Instance *right_obj_id = 
      find_Attribute_Instance_R2002_by_name( 
         right_obj_ptr, Description("OBJ_ID").char_ptr(), num_found );
  if ( num_found == 0 )
    return ret_val;

  I_var* r_oi_ptr = right_obj_id->get_var_ptr();
  t_ulong right_obj_id_value = r_oi_ptr->get_unique_id_var_ptr()->get_value();

  I_Object_Instance *rel_ptr = (I_Object_Instance *) rel->getObjPtr();
  mc_dbms_List<I_Object_Instance*> inst_coll;
  inst_coll.insert_last(rel_ptr);
  I_Object* p_obj = rel_ptr->get_Object_R2001_ptr();
  I_object_inst_ref_set_var* inst_set_var_ptr = 
    new I_object_inst_ref_set_var (p_obj, &inst_coll);

  I_object_inst_ref_set_var* oirs =
    GS_select::create_single_link( inst_set_var_ptr, "R_OIR", "R201", "");


  I_Object_Instance * oir_ptr;
  FIRST_ELEMENT( oir_ptr,
                 I_Object_Instance, 
                 &(oirs->m_oinst_coll),
                 oir_cursor );

  bool exit_loop = FALSE;
  while ( oir_ptr && !exit_loop )
  {
    I_Attribute_Instance *oir_obj_id = 
      find_Attribute_Instance_R2002_by_name( oir_ptr, Description("OBJ_ID").char_ptr(), num_found );

    if (num_found > 0)
    {
      I_var* el_ptr = oir_obj_id->get_var_ptr ();
      if ( el_ptr )
        if ( el_ptr->get_unique_id_var_ptr() )
          if ( el_ptr->get_unique_id_var_ptr()->get_value() == right_obj_id_value ) 
          {
            mc_dbms_List<I_Object_Instance*> oir_inst_coll;
            oir_inst_coll.insert_last(oir_ptr);
            I_object_inst_ref_set_var* oir_inst_ptr = 
              new I_object_inst_ref_set_var (oir_ptr->get_Object_R2001_ptr(), &inst_coll);

            I_object_inst_ref_set_var* rto =
              GS_select::create_single_link( oir_inst_ptr, "R_RTO", "R204", "");

            if ( rto->cardinality() != 0 )
	    {
              I_object_inst_ref_set_var* part =
                GS_select::create_single_link( rto, "R_PART", "R204", "");
              if ( part->cardinality() != 0 )
	      {
                ret_val = get_mult_attr ( part );
                exit_loop = TRUE;
              }
              else
              {
                I_object_inst_ref_set_var* aone =
                  GS_select::create_single_link( rto, "R_AONE", "R204", "");
                if ( aone->cardinality() != 0 )
	        {
                  ret_val = get_mult_attr ( aone );
                  exit_loop = TRUE;
                }
                else
                {
                  I_object_inst_ref_set_var* aoth =
                    GS_select::create_single_link( rto, "R_AOTH", "R204", "");
                  if ( aoth->cardinality() != 0 )
	          {
                    ret_val = get_mult_attr ( aoth );
                    exit_loop = TRUE;
                  }
                  else
                  {
                    I_object_inst_ref_set_var* sup =
                      GS_select::create_single_link( rto, "R_SUPER", "R204", "");
                    if ( sup->cardinality() != 0 )
	            {
                      ret_val = get_mult_attr ( sup );
                      exit_loop = TRUE;
                    }
                    delete sup;
                  }
                  delete aoth;
		}
                delete aone;
	      }
              delete part;
	    }
            else
	    {
              I_object_inst_ref_set_var* rgo =
                GS_select::create_single_link( oir_inst_ptr, "R_RGO", "R203", "");

              if ( rgo->cardinality() != 0 )
	      {
                I_object_inst_ref_set_var* form =
                  GS_select::create_single_link( rgo, "R_FORM", "R205", "");
                if ( form->cardinality() != 0 )
	        {
                  ret_val = get_mult_attr ( form );
                  exit_loop = TRUE;
                }
                else
                {
                  I_object_inst_ref_set_var* assr =
                    GS_select::create_single_link( rgo, "R_ASSR", "R205", "");
                  if ( assr->cardinality() != 0 )
	          {
                    ret_val = get_mult_attr ( assr );
                    exit_loop = TRUE;
                  }
                  else
                  {
                    I_object_inst_ref_set_var* sub =
                      GS_select::create_single_link( rgo, "R_SUB", "R205", "");
                    if ( sub->cardinality() != 0 )
	            {
                      ret_val = get_mult_attr ( sub );
                      exit_loop = TRUE;
                    }
                    delete sub;
                  }
                  delete assr;
		}
                delete form;
              }
              delete rgo;
	    }
            delete rto;
          }
    }

    NEXT_ELEMENT( oir_ptr, oir_cursor );
  }

  delete oirs;
  delete inst_set_var_ptr;

  return ret_val;

}

// Get the data type of the transformer return value
t_core_data_type P_checkGenDB::get_transformer_return_type( AST *trfr )
{
  I_Object_Instance* trfr_ptr = (I_Object_Instance*)trfr->getObjPtr();
  t_core_data_type dt = find_core_data_type ( trfr_ptr, "R116" );
  return dt;
}

// Get the data type of the bridge return value
t_core_data_type P_checkGenDB::get_bridge_return_type( AST *bridge )
{
  if (dumpflag)
    bridge->dumpNode("get_bridge_return_type: ");

  I_Object_Instance* br_ptr = (I_Object_Instance*)bridge->getObjPtr();
  t_core_data_type dt = find_core_data_type ( br_ptr, "R20" );
  return dt;
}

// Get the data type of the synch service return value
t_core_data_type P_checkGenDB::get_synch_svc_return_type( AST *synch_svc )
{
  if (dumpflag)
    synch_svc->dumpNode("get_synch_svc_return_type: ");

  I_Object_Instance* br_ptr = (I_Object_Instance*)synch_svc->getObjPtr();
  t_core_data_type dt = find_core_data_type ( br_ptr, "R25" );
  return dt;
}

// Determine if attribute is referential
bool P_checkGenDB::is_referential_attr( AST *attr )
{
  if (dumpflag)
    attr->dumpNode("is_referential_attr: ");

  if ( attr->getObjPtr() == 0 )
    return FALSE;

  //  validate_obj_attribute (attr, obj_obj, isLval )

  // select one rattr related by attr->O_RATTR[R106]
  // if ( cardinality(rattr) == 0 )
  //   return false
  // else
  //   return true
  // end if

  I_Object_Instance *attr_ptr = (I_Object_Instance *) attr->getObjPtr();
  mc_dbms_List<I_Object_Instance*> inst_coll;
  inst_coll.insert_last(attr_ptr);
  I_Object* p_obj = attr_ptr->get_Object_R2001_ptr();
  I_object_inst_ref_set_var* inst_set_var_ptr = 
    new I_object_inst_ref_set_var (p_obj, &inst_coll);

  I_object_inst_ref_set_var* rattr =
    GS_select::create_single_link( inst_set_var_ptr, "O_RATTR", "R106", "");

  bool ret_val = FALSE;
  if ( rattr->cardinality() != 0 )
  {
    ret_val = TRUE;
  }

  delete rattr;
  delete inst_set_var_ptr;
  return ret_val;
}

// Determine if attribute is an identifier
bool P_checkGenDB::is_identifier( AST *attr )
{
  if (dumpflag)
    attr->dumpNode("is_identifier: ");

  // select one oida related by attr->O_OIDA[R105]
  // if ( cardinality(oida) == 0 )
  //   return false
  // else
  //   return true
  // end if

  I_Object_Instance *attr_ptr = (I_Object_Instance *) attr->getObjPtr();
  mc_dbms_List<I_Object_Instance*> inst_coll;
  inst_coll.insert_last(attr_ptr);
  I_Object* p_obj = attr_ptr->get_Object_R2001_ptr();
  I_object_inst_ref_set_var* inst_set_var_ptr = 
    new I_object_inst_ref_set_var (p_obj, &inst_coll);

  I_object_inst_ref_set_var* oida =
    GS_select::create_single_link( inst_set_var_ptr, "O_OIDA", "R105", "");

  bool ret_val = FALSE;
  if ( oida->cardinality() != 0 )
  {
    ret_val = TRUE;
  }

  delete oida;
  delete inst_set_var_ptr;
  return ret_val;
}




// Helper functions

I_Attribute_Instance* 
  P_checkGenDB::find_Attribute_Instance_R2002_by_name( I_Object_Instance *oi_ptr,
    const vchar * attr_name, int &num_found )
{
  I_Attribute_Instance * ptr;
  FIRST_ELEMENT( ptr,
                 I_Attribute_Instance, 
                 oi_ptr->get_Attribute_Instance_R2002_coll_ptr(),
                 cursor );
      
  num_found = 0;
  I_Attribute_Instance *ret_val = 0;

  while ( ptr )
  {
    I_Attribute* attr_ptr = ptr->get_Attribute_R2002_ptr();
    if ( vcharCompare (attr_ptr->get_name().char_ptr(), attr_name) == 0 )
    {
      num_found += 1;
      if ( num_found == 1 )
      {
        ret_val = ptr;
      }
    }
    NEXT_ELEMENT( ptr, cursor );
  }
  return ret_val;
}

I_Attribute_Instance* P_checkGenDB::get_attribute_instance_by_name ( char *kl, 
     char *attr_name, const vchar *attr_value, bool &mult_found )
{
  // Let's make sure the object key_letters exists.
  
  GS_string obj_name_str (kl);
  obj_name_str.convert_to_upper_case ();
  mc_dbms_Set <I_Object*>* obj_coll_ptr
    = I_Object::find_Object_by_key_letter
        (GS_gen_sim_db_ptr, obj_name_str.char_ptr() );

  if (! obj_coll_ptr)
  {
    LOG_ERROR ((L_log_string,
      "P_checkGenDB::validate_obj_kl ():  Creation of I_Object collection returned 0."));
    return 0;
  }

  if (obj_coll_ptr->cardinality () < 1)
  {
    GS_ui::inform (UI_INFORM__ERROR, GS_string ("Object '") + kl + "' Unknown." );
    delete obj_coll_ptr;
    return 0;
  }

  I_Object* obj_ptr = obj_coll_ptr->pick ();
  delete obj_coll_ptr;

  mc_dbms_Set <I_Attribute*>* attr_coll_ptr
    = obj_ptr->find_Attribute_R102_by_name ( attr_name );

  if (! attr_coll_ptr)
  {
    LOG_ERROR ((L_log_string,
      "P_checkGenDB::validate_obj_kl ():  Creation of I_Attribute collection returned 0."));
    return 0;
  }

  if (attr_coll_ptr->cardinality () < 1)
  {
    GS_ui::inform (UI_INFORM__ERROR, GS_string ("Attribute '") + kl + "." + attr_name + "' Unknown.");
    delete attr_coll_ptr;
    return 0;
  }

  I_Attribute* attr_ptr = attr_coll_ptr->pick ();
  delete attr_coll_ptr;

  I_Attribute_Instance * ptr;
  FIRST_ELEMENT( ptr,
                 I_Attribute_Instance, 
                 attr_ptr->get_Attribute_Instance_R2002_coll_ptr(),
                 cursor );
      
  int num_found = 0;
  I_Attribute_Instance *ret_val = 0;

  while ( ptr )
  {
    if ( m_domain_code == UNKNOWN_DOMAIN ||
         ptr->get_attribute_ID().get_domain_id() == m_domain_code )
    {
    I_var* ainst_var_ptr = ptr->get_var_ptr ();
    if (ainst_var_ptr)
      if (ainst_var_ptr->get_string_var_ptr() )
      {
        if ( vcharCompare (ainst_var_ptr->get_string_var_ptr()->get_value().char_ptr(), attr_value) == 0 )
        {
          num_found += 1;
          if ( num_found == 1 )
          {
            ret_val = ptr;
          }
        }
      }
    }
    NEXT_ELEMENT( ptr, cursor );
  }

  if ( num_found > 1)
    mult_found = TRUE;
  else
    mult_found = FALSE;

  return ret_val;
}

persObjPtr P_checkGenDB::find_enum_data_type( I_Object_Instance *p_attr, const char * rel_id )
{
  // ret_val = <null_ptr>         // i2779.1.1  new
  // select one dt related by p_attr->S_DT[<rel_id>]
  // select one edt related by dt->S_EDT[R17]
  // if (cardinality(edt) != 0 )
  //   ret_val = edt;             // i2779.1.1 changed
/* i2779.1.1 begin */
  // else
  //   if ( <rel_id> == "R114" )
  //     select one rattr related by p_attr->O_RATTR[R106]
  //     if ( cardinality(rattr) != 0 )
  //       select one battr related by rattr->O_BATTR[R113]
  //       select one attr2 related by battr->O_ATTR[R106]
  //       if ( not_empty attr2 )
  //         ret_val = find_enum_data_type( attr2, <rel_id> )
  //       end if
  //     end if
  //   end if
/* i2779.1.1 end */
  // end if
  // return ret_val              // i2779.1.1  new

  persObjPtr ret_val = 0;

  I_Object* p_obj = p_attr->get_Object_R2001_ptr();

  mc_dbms_List<I_Object_Instance*> inst_coll;
  inst_coll.insert_last(p_attr);
  I_object_inst_ref_set_var* inst_set_var_ptr = 
    new I_object_inst_ref_set_var (p_obj, &inst_coll);

  I_object_inst_ref_set_var* dt =
    GS_select::create_single_link( inst_set_var_ptr, "S_DT", rel_id, "");
  I_object_inst_ref_set_var* edt =
    GS_select::create_single_link( dt, "S_EDT", "R17", "");
  if ( edt->cardinality() != 0 )
  {
	  edt->first();
	  ret_val = edt->get_oinst_ptr();
  }
/* i2779.1.2 begin */
  else
  {
    if ( strcmp ( rel_id, "R114" ) == 0 )
    {
      // Only O_ATTR's can be supertypes of O_RATTR's

      I_object_inst_ref_set_var* rattr =
        GS_select::create_single_link( inst_set_var_ptr, "O_RATTR", "R106", "");
      if ( rattr->cardinality() != 0 )
      {
        // this is a referential attribute, find it's base type
        I_object_inst_ref_set_var* battr =
          GS_select::create_single_link( rattr, "O_BATTR", "R113", "");

        I_object_inst_ref_set_var* attr2 =
          GS_select::create_single_link( battr, "O_ATTR", "R106", "");

        if ( attr2->cardinality() != 0 )
        {
          attr2->first();
          I_Object_Instance * attr2_ptr = attr2->get_oinst_ptr();
          ret_val = find_enum_data_type ( attr2_ptr, "R114" );
        }

        delete attr2;
        delete battr;
      }
      delete rattr;
    }
  }
/* i2779.1.2 end */

  delete edt;
  delete dt;
  delete inst_set_var_ptr;

  return ret_val;
}

t_core_data_type P_checkGenDB::find_core_data_type( I_Object_Instance *p_attr, const char * rel_id )
{
  // select one dt related by p_attr->S_DT[<rel_id>]
  // select one udt related by dt->S_UDT[R17]
  // if (cardinality(udt) == 0 )
  //   select one cdt related by dt->S_CDT[R17]
  // else
  //   select one cdt related by udt->S_CDT[R18]
  //   if ( cardinality(udt) == 0 )
  //     select one edt related by dt->S_EDT[R17]
  //     if (cardinality(edt) != 0 )
  //        return ENUMERATION_DATATYPE
  //     else
  //        return UNKNOWN_DATATYPE
  // return cdt.Core_Typ

  t_core_data_type ret_val = UNKNOWN_DATATYPE;

  I_Object* p_obj = p_attr->get_Object_R2001_ptr();

  mc_dbms_List<I_Object_Instance*> inst_coll;
  inst_coll.insert_last(p_attr);
  I_object_inst_ref_set_var* inst_set_var_ptr = 
    new I_object_inst_ref_set_var (p_obj, &inst_coll);

  I_object_inst_ref_set_var* dt =
    GS_select::create_single_link( inst_set_var_ptr, "S_DT", rel_id, "");

  I_object_inst_ref_set_var* udt =
    GS_select::create_single_link( dt, "S_UDT", "R17", "");

  I_object_inst_ref_set_var* cdt;
  if ( udt->cardinality() == 0 )
  {
	cdt =
	  GS_select::create_single_link( dt, "S_CDT", "R17", "");
    if ( cdt->cardinality() == 0 )
    {
      I_object_inst_ref_set_var* edt =
        GS_select::create_single_link( dt, "S_EDT", "R17", "");
      if ( edt->cardinality() != 0 )
      {
	      ret_val = ENUMERATION_DATATYPE;
      }
      delete edt;
    }
  }
  else
  {
	cdt = 
	  GS_select::create_single_link( udt, "S_CDT", "R18", "");
  }

  if ( ret_val == UNKNOWN_DATATYPE )
  {
	  cdt->first();
	  I_Object_Instance* the_cdt = cdt->get_oinst_ptr();

	  int num_found = 0;
	  I_Attribute_Instance *core_type = 
		  find_Attribute_Instance_R2002_by_name( the_cdt, Description("CORE_TYP").char_ptr(), num_found );

	  if (num_found > 0)
	  {
		I_var* ct_ptr = core_type->get_var_ptr ();
		if ( ct_ptr )
		  if ( ct_ptr->get_integer_var_ptr() )
			ret_val = (t_core_data_type)(ct_ptr->get_integer_var_ptr()->get_value());
	  }
  }
  delete cdt;
  delete udt;
  delete dt;
  delete inst_set_var_ptr;
  return ret_val;
}

Obj_Card_e P_checkGenDB::get_mult_attr ( I_object_inst_ref_set_var *obj_as )
{
  Obj_Card_e ret_val = CARD_ONE;

  obj_as->first();
  int num_found = 0;
  I_Attribute_Instance *attr_ptr = 
    find_Attribute_Instance_R2002_by_name( obj_as->get_oinst_ptr(), Description("MULT").char_ptr(), num_found );

  if (num_found > 0)
  {
    I_var* m_ptr = attr_ptr->get_var_ptr ();
    if ( m_ptr )
      if ( m_ptr->get_integer_var_ptr() )
        if ( m_ptr->get_integer_var_ptr()->get_value() == 1 )
        {
          ret_val = CARD_MANY;
        }
        else
        {
          ret_val = CARD_ONE;
        }
  }
  return ret_val;
}

persObjPtr P_checkGenDB::get_enum_data_type_ptr(  AST* p_enum )
{
  persObjPtr ret_val = 0;
  if ( p_enum->getObjPtr() == RESET_OBJPTR )
  {
	  return ret_val;
  }

  switch ( p_enum->getType() )
  {
    case TOK_EXPRESSION:
		ret_val = get_enum_data_type_ptr(p_enum->child());
      break;

    case TOK_ENUMERATION:
    case TOK_LOCAL_VAR:
	  ret_val = p_enum->getObjPtr();
	  break;

    case TOK_BRIDGE_PARAM:
	  if ( p_enum->child()->getObjPtr() == RESET_OBJPTR )
	  {
		return ret_val;
	  }
      ret_val = find_enum_data_type( (I_Object_Instance *)p_enum->child()->getObjPtr(), "R22" );
	  break;

	case TOK_SYNCH_SVC_PARAM:
	  if ( p_enum->child()->getObjPtr() == RESET_OBJPTR )
	  {
		return ret_val;
	  }
      ret_val = find_enum_data_type( (I_Object_Instance *)p_enum->child()->getObjPtr(), "R26" );
	  break;

    case TOK_TRANSFORMER_PARAM:
	  if ( p_enum->child()->getObjPtr() == RESET_OBJPTR )
	  {
		return ret_val;
	  }
      ret_val = find_enum_data_type( (I_Object_Instance *)p_enum->child()->getObjPtr(), "R118" );
	  break;

    case TOK_BRIDGE_EXPR:
	  if ( p_enum->child()->sibling()->getObjPtr() == RESET_OBJPTR )
	  {
		return ret_val;
	  }
      ret_val = find_enum_data_type( (I_Object_Instance *)p_enum->child()->sibling()->getObjPtr(), "R20" );
      break;

    case TOK_TRANSFORMER_EXPR:
    case TOK_TRANSFORMER_IB_EXPR:
	  if ( p_enum->child()->sibling()->getObjPtr() == RESET_OBJPTR )
	  {
		return ret_val;
	  }
      ret_val = find_enum_data_type( (I_Object_Instance *)p_enum->child()->sibling()->getObjPtr(), "R116" );
	  break;

	case TOK_SYNCH_SVC_EXPR:
	  if ( p_enum->child()->getObjPtr() == RESET_OBJPTR )
	  {
		return ret_val;
	  }
      ret_val = find_enum_data_type( (I_Object_Instance *)p_enum->child()->getObjPtr(), "R25" );
	  break;

    case TOK_INST_REF_VAR:
	  if ( p_enum->child()->getObjPtr() == RESET_OBJPTR )
	  {
		return ret_val;
	  }
      ret_val = find_enum_data_type( (I_Object_Instance *)p_enum->child()->getObjPtr(), "R114" );
	  break;

    case TOK_RCVD_EVT:
	  if ( p_enum->sibling()->getObjPtr() == RESET_OBJPTR )
	  {
		return ret_val;
	  }
      ret_val = find_enum_data_type( (I_Object_Instance *)p_enum->sibling()->getObjPtr(), "R524" );
	  break;
  }
  return ret_val;
}

// Validate the event label
void P_checkGenDB::find_event_for_event_label( const vchar* p_event_label,
                                      I_object_inst_ref_set_var *p_ism,
                                      bool& p_found_here,
                                      mc_dbms_Bag< I_Object_Instance * > *&p_event_coll)
{
  if ( p_event_coll == 0 )
  {
    p_event_coll =
	    & mc_dbms_Bag< I_Object_Instance * >::create(
        	mc_dbms_database::get_transient_database() );
  }

  //   select one sm related by p_ism->SM_SM[R517]
  //   select many events related by sm->SM_EVT[R502]
  //   for each evt in events
  //     if (evt.Drv_Lbl == label->getVcharText() )
  //        p_event_coll = p_event_coll + evt 
  //     end if
  //   end for
  // end if

  if ( p_ism->cardinality() != 0 )
  {
    I_object_inst_ref_set_var* sm =
      GS_select::create_single_link( p_ism, "SM_SM", "R517", "");

    I_object_inst_ref_set_var* events =
      GS_select::create_single_link( sm, "SM_EVT", "R502", "");

      I_Object_Instance * evt_ptr;
      FIRST_ELEMENT( evt_ptr,
                     I_Object_Instance, 
                     &(events->m_oinst_coll),
                     evt_cursor );

      int num_found = 0;
      while ( evt_ptr )
      {
        I_Attribute_Instance *drv_lbl = 
          find_Attribute_Instance_R2002_by_name( evt_ptr, Description("DRV_LBL").char_ptr(), num_found );

        if (num_found > 0)
        {
          I_var* el_ptr = drv_lbl->get_var_ptr ();
          if ( el_ptr )
            if ( el_ptr->get_string_var_ptr() )
              if ( vcharCompare (el_ptr->get_string_var_ptr()->get_value().char_ptr(), 
                           p_event_label) == 0 )
              {
                  p_event_coll->insert(evt_ptr);
                  p_found_here = TRUE;
              }
        }

        NEXT_ELEMENT( evt_ptr, evt_cursor );
      }

      if ( !p_found_here && p_ism->cardinality() != 0 )
      {
          // Check if Object is Object_as_subtype  (it better be!)
          // select one obj related by p_ism->O_OBJ[R518]
          // select many oirs related by obj->R_OIR[R201]
          // for each oir in oirs 
          //   select one rgo related by oir->R_RGO[R203]
          //   if ( not_empty rgo )
          //      select one subtype related by rgo->R_SUB[R205]
          //      if ( not_empty subtype )
          //        select one rel related by oir->R_REL[R201]
          //        select one inhrel related by rel->R_SUBSUP[R206]
          //        if ( not_empty inhrel )
          //          select one supertype related by inhrel->R_SUPER[R212]
          //          if ( not_empty supertype )
          //            select one rto related by supertype->R_RTO[R204]
          //            select one super_oir related by rto->R_OIR[R203]
          //            select one super_obj related by super_oir->O_OBJ[R201]
          //            select one super_ism related by super_obj->SM_ISM[R518]
          //            l_found_here = FALSE
          //            label_no_splat = // p_event_label with splat removed
          //            find_event_for_event_label( label_no_splat, super_ism, l_found_here, p_event_coll )
          //            if ( l_found_here )
          //               for all found_evt_ptr in p_event_coll
          //                 select one poly_evt related by found_evt_ptr->SM_PEVT[R525]
          //                 if ( empty poly_evt )
          //                     p_event_coll = p_event_coll - found_evt_ptr
          //                 end if
          //               end for
          //            end if
          //          end if
          //        end if
          //      end if
          //   end if
          // end for

        I_object_inst_ref_set_var* obj =
          GS_select::create_single_link( p_ism, "O_OBJ", "R518", "");

        I_object_inst_ref_set_var* oirs =
          GS_select::create_single_link( obj, "R_OIR", "R201", "");

        I_Object_Instance * oir;
        FIRST_ELEMENT( oir,
                       I_Object_Instance, 
                       &(oirs->m_oinst_coll),
                       oirs_cursor );

          while ( oir )
          {
            I_Object* oir_obj_ptr = oir->get_Object_R2001_ptr();
            mc_dbms_List<I_Object_Instance*> oir_inst_coll;
            oir_inst_coll.insert_last(oir);
            I_object_inst_ref_set_var* oir_inst_set_var_ptr = 
                new I_object_inst_ref_set_var (oir_obj_ptr, &oir_inst_coll);
            I_object_inst_ref_set_var* rgo =
              GS_select::create_single_link( oir_inst_set_var_ptr, "R_RGO", "R203", "");
            if ( rgo->cardinality() != 0 )
            {
                I_object_inst_ref_set_var* subtype =
                  GS_select::create_single_link( rgo, "R_SUB", "R205", "");
                if ( subtype->cardinality() != 0 )
                {
                    I_object_inst_ref_set_var* rel =
                      GS_select::create_single_link( oir_inst_set_var_ptr, "R_REL", "R201", "");

                    I_object_inst_ref_set_var* inhrel =
                      GS_select::create_single_link( rel, "R_SUBSUP", "R206", "");
                    if ( inhrel->cardinality() != 0 )
                    {
                        I_object_inst_ref_set_var* supertype =
                          GS_select::create_single_link( inhrel, "R_SUPER", "R212", "");
                        if ( supertype->cardinality() != 0 )
                        {
                            I_object_inst_ref_set_var* rto =
                              GS_select::create_single_link( supertype, "R_RTO", "R204", "");
                            I_object_inst_ref_set_var* super_oir =
                              GS_select::create_single_link( rto, "R_OIR", "R203", "");
                            I_object_inst_ref_set_var* super_obj =
                              GS_select::create_single_link( super_oir, "O_OBJ", "R201", "");
                            I_object_inst_ref_set_var* super_ism =
                              GS_select::create_single_link( super_obj, "SM_ISM", "R518", "");
                            bool l_found_here = FALSE;

                            vchar label_no_splat[32];
                            vcharCopy ( p_event_label, label_no_splat );

                            vchar splat = vcharFromASCII( '*' );
                            int label_len = vcharLength( p_event_label );
                            if ( p_event_label[label_len - 1] == splat )
                            {
                                label_no_splat[label_len - 1] = 0;
                            }

                            find_event_for_event_label ( label_no_splat, super_ism, l_found_here, p_event_coll );
                            if ( l_found_here )
                            {
                                  I_Object_Instance * found_evt_ptr;
                                  FIRST_ELEMENT( found_evt_ptr,
                                                 I_Object_Instance, 
                                                 p_event_coll,
                                                 found_evt_cursor );

                                  while ( found_evt_ptr )
                                  {
                                    I_Object* evt_obj_ptr = found_evt_ptr->get_Object_R2001_ptr();
                                    mc_dbms_List<I_Object_Instance*> evt_inst_coll;
                                    evt_inst_coll.insert_last(found_evt_ptr);
                                    I_object_inst_ref_set_var* evt_inst_set_var_ptr = 
                                        new I_object_inst_ref_set_var (evt_obj_ptr, &evt_inst_coll);
                                    I_object_inst_ref_set_var* poly_evt_ptr =
                                      GS_select::create_single_link( evt_inst_set_var_ptr, "SM_PEVT", "R525", "");

                                    if ( poly_evt_ptr->cardinality() == 0 )
                                    {
                                        // Event in supertype, but it's not polymorphic
                                        p_event_coll->remove(found_evt_ptr);
                                    }

                                    NEXT_ELEMENT( found_evt_ptr, found_evt_cursor );

                                    delete poly_evt_ptr;
                                    delete evt_inst_set_var_ptr;
                                  }
                            }
                            delete super_ism;
                            delete super_obj;
                            delete super_oir;
                            delete rto;
                        }
                        delete supertype;

                    }
                    delete inhrel;
                    delete rel;
                }
                delete subtype;
            }
            delete rgo;
            delete oir_inst_set_var_ptr;
            NEXT_ELEMENT( oir, oirs_cursor );
          }
      }
      delete events;
      delete sm;
    }

}


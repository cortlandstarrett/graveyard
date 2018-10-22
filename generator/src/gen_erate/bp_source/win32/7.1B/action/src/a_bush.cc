/*========================================================================
 *
 * File:      $RCSfile: a_bush.cc,v $
 * Version:   $Revision: 1.11 $
 * Modified:  $Date: 2013/01/10 23:42:36 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#include <mc_dbms/mc_dbms.hh>


#include "a_bush.hh"
#include "a_gfinds.hh"
#include "a_stmtyp.hh"

#include <u_trace.hh>

#include <u_util.hh>
#include <u_tspec.hh>
#include <u_cursor.hh>

#include "d_dattyp.hh"
#include "d_invoct.hh"
#include "d_sm_pm.hh"
#include "d_smedi.hh"
#include "d_smevt.hh"
#include "d_entity.hh"
#include "d_object.hh"
#include <d_battr.hh>
#include "d_rel.hh"
#include "d_sevt.hh"
#include "d_seme.hh"
#include "d_tfmr.hh"
#include "d_bridge.hh"
#include "d_parm.hh"
#include "d_action.hh"
#include "d_acthom.hh"
#include "d_moorhm.hh"
#include "d_smsta.hh"
#include "d_suppdt.hh"
#include <d_usrprp.hh>


// Includes for the PCCTS parser
#include "myToken.h"
#include "myAST.h"
#include "myPanic.h"
#include "myTokenBuffer.h"
#include "DLGLexer.h"
#include "P.h"
#include "p_ckosdb.hh"


// The following global symbols are needed to interface with the parser.

const Description AL_Bush_relocatable::UNRESOLVED_SYMBOL = "#####";
const Description AL_Bush_relocatable::LEADING_DELIMITER = "${#@!:";

// The get_spec_type() functions are implemented here to avoid 
// having to #include all the parser .h files in these class's
// .h files

int D_action::get_spec_type ()
{
   if ( get_sm_spt_pm_ptr()->get_sm_spt_pm_type() == D_sm_spt_pm::ASSIGNER_SM )
   {
       return P::AL_SPEC_ASSIGNER_E;
   }
   else
   {
       return P::AL_SPEC_STATE_ACTION_E;
   }
}

int D_bridge::get_spec_type ()
{
    return P::AL_SPEC_BRIDGE_E;
}

int D_synchronous_service::get_spec_type ()
{
    return P::AL_SPEC_SYNSVC_E;
}

int D_transformer::get_spec_type ()
{
    if ( is_instance_based() )
    {
      return P::AL_SPEC_IB_TRANSFORMER_E;
    }
    else
    {
      return P::AL_SPEC_TRANSFORMER_E;
    }
}

int Base_attribute::get_spec_type ()
{
    return P::AL_SPEC_ATTRIBUTE_E;
}

AL_Bush_action *
AL_Bush_action::create( D_execution_spec *p_D_action_ptr, const vchar *p_action_desc,
                       Description &p_err_msg, long int &p_bad_line_num,
                       long int &p_err_start, long int &p_err_end )
{
  char *action_desc_ASCII = Description::createAsciiFromVchar(p_action_desc);

  LOG_TRACE( L_AL, L_FUNCTION_BEGIN, ( L_log_string,
                                       "Begin AL_Bush_action::create()...p_D_action_ptr = 0x%x, p_action_desc = %s",
                                       p_D_action_ptr, p_action_desc ));
  
  // Before parsing we must remove/clear this action with regard to any access
  // or communication path it is currently associated with before parsing again;
  // we want to clear it now because this new parse makes previous path data
  // null-and-void.
  
  p_D_action_ptr->remove_action_from_derived_paths();
  
  // Also, regardless of this current new parse, the old bush action is no
  // longer valid or needed; delete it accordingly.
  
  AL_Bush_action * old_bush_action_ptr = p_D_action_ptr->get_AL_Action_ptr();
  delete old_bush_action_ptr;
  
  
  // Now create the empty bush action and set the global pointer to it so
  // that it can be added-to by the parse code.
  
  AL_Bush_action * new_bush_action_ptr =
    new( mc_dbms_segment::of( p_D_action_ptr ), 
         AL_Bush_action::get_mc_dbms_typespec() )
    AL_Bush_action();
  
  new_bush_action_ptr->set_D_execution_spec_ptr( p_D_action_ptr );
  
  p_err_msg = "";
  p_bad_line_num = 1;
  
  p_err_start = 0;
  p_err_end = 0;  
  
  LOG_TRACE( L_AL, L_FUNCTION_BEGIN, ( L_log_string,
     "calling PCCTS parser...parseable input = %s", p_action_desc ));
  
  P_error error;
  P_error *er = &error;
  P_checkOSDB ck(er);

  ck.set_current_D_action_ptr( p_D_action_ptr->get_action_ptr() );
  ck.set_current_domain_ptr( p_D_action_ptr->get_domain_ptr() );
  ck.set_bush_action_ptr( new_bush_action_ptr );
  
  //-------------------------------------------------------------------
  // Initialize the scanner and parser.
  //-------------------------------------------------------------------
  char *spec_descr = "unknown";
  Object *self = 0;
  P::al_spec_type spec_type = P::AL_SPEC_NONE_E;
  e_diagram_display_mode dm = User_properties::diagram_display_mode ();
  Description attribute_name;   // local storage for attribute_write_valid to point to
  vchar* attribute_write_valid = 0;

  switch ( p_D_action_ptr->get_spec_type() )
  {
  case P::AL_SPEC_STATE_ACTION_E:
    // Resolve the pointer to self
    self = p_D_action_ptr->get_action_ptr()->get_sm_spt_pm_ptr()->get_object_ptr();
    spec_descr = "state";
    spec_type = P::AL_SPEC_STATE_ACTION_E;
    break;

  case P::AL_SPEC_ASSIGNER_E:
    spec_descr = "assigner state";
    spec_type = P::AL_SPEC_ASSIGNER_E;
    break;

  case P::AL_SPEC_IB_ASSIGNER_E:
    spec_descr = "instance-based assigner state";
    spec_type = P::AL_SPEC_IB_ASSIGNER_E;
    break;

  case P::AL_SPEC_BRIDGE_E:
    spec_descr = "bridge";
    spec_type = P::AL_SPEC_BRIDGE_E;
    break;

  case P::AL_SPEC_TRANSFORMER_E:
    spec_type = P::AL_SPEC_TRANSFORMER_E;
    if ( dm == DISPLAY_MODE_SM )
    {
      spec_descr = "transformer";
    }
    else
    {
      spec_descr = "class operation";
    }
    break;

  case P::AL_SPEC_IB_TRANSFORMER_E:
    // get self pointer
    self = p_D_action_ptr->get_transformer_ptr()->get_object_ptr();
    spec_type = P::AL_SPEC_IB_TRANSFORMER_E;
    if ( dm == DISPLAY_MODE_SM )
    {
      spec_descr = "instance-based transformer";
    }
    else
    {
      spec_descr = "operation";
    }
    break;

  case P::AL_SPEC_SYNSVC_E:
    if ( dm == DISPLAY_MODE_SM )
    {
      spec_descr = "synchronous service";
    }
    else
    {
      spec_descr = "function";
    }
    
    spec_type = P::AL_SPEC_SYNSVC_E;
    break;

  case P::AL_SPEC_ATTRIBUTE_E:
    // get self pointer
	Attribute* attr_ptr = p_D_action_ptr->get_attribute_ptr();
    self = attr_ptr->get_object_ptr();
	// get attribute name
    attribute_name = attr_ptr->get_attr_name();
    attribute_write_valid = (vchar*)attribute_name.char_ptr();
    spec_descr = "attribute";
    spec_type = P::AL_SPEC_ATTRIBUTE_E;
    break;
  }
  
  // Get a pointer to any event impinging on this state
  D_sm_event *p_sm_event = NULL;

  if ( spec_type == P::AL_SPEC_STATE_ACTION_E ||
       spec_type == P::AL_SPEC_ASSIGNER_E ||
       spec_type == P::AL_SPEC_IB_ASSIGNER_E )
  {

      // Get the state event matrix entry set associated with this state
      mc_dbms_Set<D_state_event_matrix_entry*>* p_sm_seme_coll =
        p_D_action_ptr->get_action_ptr()->
        get_action_home_ptr()->
        get_moore_action_home_ptr()->
        get_sm_state_ptr()->
        get_state_event_matrix_entry_coll_ptr();

      if ( p_sm_seme_coll != NULL )
        {
          // Get any SM_SEME from the collection and get its associated event,
          // since they all must have the same event supp data.
          // This gets put in the parser's symbol table to be used
          // for checking rcvd_evt data accesses.
          if ( p_sm_seme_coll->cardinality() > 0 )
            {
              p_sm_event = p_sm_seme_coll->pick()->
                get_sm_event_ptr();
            }
        }
  }

  P *parser = NULL;
  const vchar* saveBuffer = AST::getVcharBuffer();

  try {
    // Using a char buffer instead of a file
    ColToken::accumulated_offset = 0;   // HACK: should be done elsewhere
    DLGStringInput in(action_desc_ASCII);
    DLGLexer lexer(&in, 2000);      // what is 2000? max token length
    MyTokenBuffer pipe(&lexer,1);
    ANTLRToken aToken( (ANTLRTokenType)0 );
    lexer.setToken(&aToken);
  
    parser = new P(&pipe);
    parser->init(er, &ck, self, p_sm_event, NULL, p_D_action_ptr);
    parser->initReloc();
    parser->setBufferAddr(action_desc_ASCII,
                          p_action_desc);
    
    //-------------------------------------------------------------------
    // Fire up the parser by initializing and invoking first rule.
    //-------------------------------------------------------------------
    ASTBase *root = NULL;            // Define root of abstract syntax tree.
    int parser_rc;
    
    parser->al_spec( &root,
                     &parser_rc,
                     spec_type,     // al_spec_type p_type
                     spec_descr,    // char *p_descr
                     p_D_action_ptr->get_return_type(),     // t_core_data_type p_return_type_reqd
					 attribute_write_valid
                     );
  }
  catch ( char *msg )
    {
      er->severe_error( msg );
      p_err_msg = er->get_error_messages();
      er->get_first_error_location( p_bad_line_num, p_err_start, p_err_end );

      delete parser;
      Description::freeAsciiFromVchar( action_desc_ASCII );

      // Don't forget to delete the partial action bush that was built and
      // set the AL_Action bush pointer to 0.
      
      delete new_bush_action_ptr;
      new_bush_action_ptr = 0;
      
      p_D_action_ptr->set_AL_Action_ptr( 0 );


      LOG_TRACE( L_AL, L_FUNCTION_END, ( L_log_string,
         "End AL_Bush_action::create()...try #2 threw an exception",
         new_bush_action_ptr ) );

      return( new_bush_action_ptr );
    }
  

  create_bushes(parser, er, p_action_desc, action_desc_ASCII, new_bush_action_ptr);

  // Note: error can get generated in the fragment of code
  // preceding this test.  Do not change the test on the if statement!
  if ( er->error_count() )
    {
      p_err_msg = er->get_error_messages();
      er->get_first_error_location( p_bad_line_num, p_err_start, p_err_end );
      
      // Don't forget to delete the partial action bush that was built and
      // set the AL_Action bush pointer to 0.
      
      delete new_bush_action_ptr;
      new_bush_action_ptr = 0;
      
      p_D_action_ptr->set_AL_Action_ptr( 0 );
    }

  // delete the instances created for the parser
  delete parser;
  AST::setVcharBuffer(saveBuffer);
  Description::freeAsciiFromVchar( action_desc_ASCII );


  LOG_TRACE( L_AL, L_FUNCTION_END, ( L_log_string,
                                     "End AL_Bush_action::create()...new_bush_action_ptr = 0x%x",
                                     new_bush_action_ptr ) );

  return( new_bush_action_ptr );
  
}


void AL_Bush_action::create_bushes(P* parser, P_error* er, const vchar *p_action_desc,
                                   const char *action_desc_ASCII,
                                   AL_Bush_action * new_bush_action_ptr)
{
  t_boolean dumpflag = parser->dumpflag;
  if ( ! er->error_count() )
    {
      AL_Bush_statement *current_stmt_ptr;
      
      long int c_last_offset = 0;  // Offset of the last bush
      long int c_buf_lng = ::strlen(action_desc_ASCII);
      if (dumpflag)
        printf("Input p_action_desc:\n%s\n", action_desc_ASCII);
      long int c_next_offset = 0;
      long int c_lit_lng;
      enum {MAX_MC_DBMS_STRING_LNG = 4000};
      vchar lit_buf[MAX_MC_DBMS_STRING_LNG+10];  // give a little room
      char lit_buf_ascii[MAX_MC_DBMS_STRING_LNG+10];  // give a little room
      vchar ASC_NUL = vcharFromASCII('\0');

      int c_reloc_lng;             // Length of a relocatable
      t_boolean order_error = FALSE;
      AST *look = parser->ttr->getItemHead();
      
      while (look && (! order_error))
        {
          c_next_offset = look->getOffset();
          c_lit_lng = c_next_offset - c_last_offset;
          
          // If it's 0, we have two relocatables next to each other.
          while ( c_lit_lng )
            {
              if ( c_lit_lng < 0 )
                {
                  order_error = TRUE;
                  break;
                }
              else
                {
                  if ( c_lit_lng > MAX_MC_DBMS_STRING_LNG )
                    c_lit_lng = MAX_MC_DBMS_STRING_LNG;
                  if (dumpflag)
                    {
                      ::strncpy( &lit_buf_ascii[0],
                                 action_desc_ASCII + c_last_offset,
                                 (size_t)c_lit_lng);
                      lit_buf_ascii[c_lit_lng] = '\0';
                      printf("->creating AL_Bush_literal:\n    c_lit_lng: %d\n    c_next_offset: %d\n    c_last_offset: %d\n    c_buf_lng: %d\n    string:'%s'\n", c_lit_lng, c_next_offset, c_last_offset, c_buf_lng, &lit_buf_ascii[0]);
                    }

                  vchar *ep = vcharCopyBounded(p_action_desc + c_last_offset,
                                               &lit_buf[0],
                                               (size_t)c_lit_lng);
                  *ep = ASC_NUL;
                  current_stmt_ptr = AL_Bush_statement::create( new_bush_action_ptr );
                  AL_Bush_literal *literal_ptr = 
                    AL_Bush_literal::create( lit_buf, current_stmt_ptr );
                    current_stmt_ptr->get_component_coll_ptr()->insert( literal_ptr );
                  c_last_offset += c_lit_lng;
                  c_lit_lng = c_next_offset - c_last_offset;
                }
            }
          if (! order_error)
            {
              current_stmt_ptr = 0;
              c_reloc_lng = look->getTokenLength();
              Id id = look->get_Id();
              if (dumpflag)
                {
                  printf("->creating AL_Bush_relocatable:\n    c_reloc_lng: %d, c_last_offset: %d, c_buf_lng: %d\n    string:'%s'\n", c_reloc_lng, c_last_offset, c_buf_lng, look->getAsciiText());
                  
                  printf("  look stuff:\n    getText(): %s\n    getRelocType(): %d\n    getObjPtr(): 0X%x\n    id: %d\n",
                         look->getAsciiText(),
                         look->getRelocType(),
                         look->getObjPtr(),
                         id.get_entire_value());
                }
              Reloc_Type_e type = look->getRelocType();
              switch(type)
                {
                case EVENT_LABEL_FIELD:
                  current_stmt_ptr =
                    AL_Bush_statement::create( new_bush_action_ptr );
                  new_bush_action_ptr->derive_comm_path(look);
                  break;
                case ATTRIBUTE_FIELD:
                  current_stmt_ptr =
                    AL_Bush_statement::create( new_bush_action_ptr );
                  new_bush_action_ptr->derive_access_path(look);
                  break;
                case OBJECT_KEY_LETTERS_FIELD:
                case RELATIONSHIP_NUMBER_FIELD:
                case SM_EVENT_DATA_ITEM_NAME_FIELD:
                case EE_EVENT_DATA_ITEM_NAME_FIELD:
                case EXTERNAL_ENTITY_KL_FIELD:
                case EVENT_MEANING_FIELD:
                case EVENT_MEANING_TICKED_FIELD:
                case RELATIONSHIP_PHRASE_FIELD:
                case TRANSFORMER_FIELD:
                case TRANSFORMER_PARM_FIELD:
                case BRIDGE_FIELD:
                case BRIDGE_PARM_FIELD:
                case SYNCH_SVC_FIELD:
                case SYNCH_SVC_PARM_FIELD:
				case ENUMERATOR_FIELD:
				case ENUMERATION_FIELD:
                  current_stmt_ptr =
                    AL_Bush_statement::create( new_bush_action_ptr );
                  break;
                case RELOC_IGNORE_DATA:
                  if (dumpflag)
                  {
                  printf("Ignore Data Reloc\n");
                  }
                  break;
                case UNKNOWN_RELOC_TYPE:
                case RELOC_NOT_YET_ADDED:
                  printf("Invalid Reloc Type in AST\n");
                  break;
                }
              if (current_stmt_ptr)
                {
                  AL_Bush_relocatable *reloc_ptr = 
                    AL_Bush_relocatable::create( look->getVcharText(),
                                                 id,
                                                 look->getRelocType(),
                                                 current_stmt_ptr );
                  current_stmt_ptr->get_component_coll_ptr()->insert( reloc_ptr );
                }
              c_last_offset += c_reloc_lng;
              look = look->getItemNext();
            }
          else
            break;
        }
      if ( (!order_error) && (c_buf_lng) )
        {
          c_next_offset = c_buf_lng;
          c_lit_lng = c_next_offset - c_last_offset;
          
          // This is for the last literal.
          // If it's 0, there is nothing left in the buffer to handle
          if ( c_lit_lng < 0 )
            order_error = TRUE;
          else
            while ( c_lit_lng )
              {
                if ( c_lit_lng > MAX_MC_DBMS_STRING_LNG )
                  c_lit_lng = MAX_MC_DBMS_STRING_LNG;
                vchar *ep = vcharCopyBounded( p_action_desc + c_last_offset,
                                              &lit_buf[0],
                                              (size_t)c_lit_lng);
                *ep = '\0';
                if (dumpflag)
                  printf("->creating AL_Bush_literal:\n    c_lit_lng: %d, c_next_offset: %d, c_last_offset: %d, c_buf_lng: %d\n", c_lit_lng, c_next_offset, c_last_offset, c_buf_lng);
                current_stmt_ptr =
                  AL_Bush_statement::create( new_bush_action_ptr );
                AL_Bush_literal *literal_ptr = 
                  AL_Bush_literal::create( lit_buf, current_stmt_ptr );
                current_stmt_ptr->get_component_coll_ptr()->
                  insert( literal_ptr );
                c_last_offset += c_lit_lng;
                c_lit_lng = c_next_offset - c_last_offset;
              }
        }
      if (!order_error)
        {
          // Reset persistent pointers to 0.
          
          new_bush_action_ptr->clear_persistent_ptrs();
        }

      else
        {
          AL_PARSE_ERR3( look,
                         AL_GETMSG(ERR,352,3),
                         look->getVcharText(),
                         c_next_offset,
                         c_last_offset )
        }
    }
}

AL_Bush_action::AL_Bush_action()
{

LOG_TRACE( L_AL, L_FUNCTION_BEGIN, ( L_log_string,
	"Begin AL_Bush_action::AL_Bush_action()" ));

// IMPORTANT: We will NOT automatically set the pointer to D_action. We
// will let the caller of the function do that (if desired). This is because
// we do NOT want to unconditionally connect to D_action (thus overwriting
// the current AL_Bush_action pointer).

    DELETE_IN_PROGRESS_INIT()

LOG_TRACE( L_AL, L_FUNCTION_END, ( L_log_string,
	"End AL_Bush_action::AL_Bush_action()" ));

}


AL_Bush_action::~AL_Bush_action()
{

LOG_TRACE( L_AL, L_FUNCTION_BEGIN, ( L_log_string,
	"Begin AL_Bush_action::~AL_Bush_action()" ));

// IMPORTANT: Because the statement destructor does NOT delete its component
// collection (due to duplicate complications), we will delete the components
// here.

AL_Bush_statement * statement_ptr;

FOR_ALL_ELEMENTS_SAFE( statement_ptr,
				  AL_Bush_statement,
				  get_statement_coll_ptr(),
				  c1 )
{
	delete statement_ptr;
}

AL_Bush_statement_component * component_ptr;

FOR_ALL_ELEMENTS_SAFE( component_ptr,
				  AL_Bush_statement_component,
				  get_component_coll_ptr(),
				  c2 )
{
	delete component_ptr;
}

LOG_TRACE( L_AL, L_FUNCTION_END, ( L_log_string,
	"End AL_Bush_action::~AL_Bush_action()" ));

}


Description
AL_Bush_action::render( t_boolean p_encode_reloc ) const
{

LOG_TRACE( L_AL, L_FUNCTION_BEGIN, ( L_log_string,
	"Begin AL_Bush_action::render()... p_encode_reloc = %d",
	p_encode_reloc ));

Description action_string;
AL_Bush_statement * statement_ptr;

FOR_ALL_ELEMENTS( statement_ptr,
				  AL_Bush_statement,
				  get_statement_coll_ptr(),
				  c1 )
{
	action_string += statement_ptr->render( p_encode_reloc );
}

LOG_TRACE( L_AL, L_FUNCTION_END, ( L_log_string,
	"End AL_Bush_action::render()...action_string ->%s<-",
	action_string.char_ptr() ));

return( action_string );

}

void 
AL_Bush_action::mark_referenced_datatypes(D_dd_srm_scm_sam* p_dd_ptr)
{

LOG_TRACE( L_AL, L_FUNCTION_BEGIN, ( L_log_string,
	"Begin AL_Bush_action::mark_referenced_datatypes()"));

AL_Bush_statement * statement_ptr;

FOR_ALL_ELEMENTS( statement_ptr,
				  AL_Bush_statement,
				  get_statement_coll_ptr(),
				  c1 )
{
	statement_ptr->mark_referenced_datatypes( p_dd_ptr );
}

LOG_TRACE( L_AL, L_FUNCTION_END, ( L_log_string,
	"End AL_Bush_action::mark_referenced_datatypes()"));

}


void
AL_Bush_action::derive_comm_path( AST* event_label )
{
  
  LOG_TRACE( L_AL, L_FUNCTION_BEGIN, ( L_log_string,
                                      "Begin AL_Bush_action::derive_comm_path()" ));
  
  Id evt_id = event_label->get_Id();
  switch( event_label->sibling()->getType() )
    {
    case TOK_INST_REF_VAR:
      {
        // If the inst_ref is self, we don't need to add the com path
        if ( strcmp(event_label->sibling()->getAsciiText(), "self") == 0 )
          break;
        else if ( strcmp(event_label->sibling()->getAsciiText(), "Self") == 0 )
          break;
        else if ( strcmp(event_label->sibling()->getAsciiText(), "SELF") == 0 )
          break;
        // If it's not self, add it the same way as for a creator
      }
    
    case TOK_KL_OBJECT_CREATOR:
      {
        Id sm_spt_pm_id = ( (Object *) event_label->sibling()->getObjPtr() )->
          get_instance_sm_spt_pm_id();
        get_D_execution_spec_ptr()->add_derived_communication_path( evt_id, sm_spt_pm_id );
        break;
      }

    case TOK_KL_OBJECT_ASSIGNER:
      {
        Id sm_spt_pm_id = ( (Object *) event_label->sibling()->getObjPtr() )->
          get_assigner_sm_spt_pm_id();
        get_D_execution_spec_ptr()->add_derived_communication_path( evt_id, sm_spt_pm_id );
        break;
      }
      
    case TOK_KL_EXTERNAL_ENTITY:
      {
        Id ee_id = event_label->sibling()->get_Id();
        get_D_execution_spec_ptr()->add_derived_communication_path( evt_id, ee_id );
        break;
      }      
      
    default:
      break;
    }
  
  LOG_TRACE( L_AL, L_FUNCTION_END, ( L_log_string,
                                    "End AL_Bush_action::derive_comm_path()" ));
  
}


void
AL_Bush_action::derive_access_path( AST* attribute )
{

	LOG_TRACE( L_AL, L_FUNCTION_BEGIN, ( L_log_string,
		"Begin AL_Bush_action::derive_access_path()" ));

	Id data_id = attribute->get_Id();
   Id dest_id = ( (Attribute *) attribute->getObjPtr() )->containing_object_id();
	get_D_execution_spec_ptr()->add_derived_access_path( data_id, dest_id );

	LOG_TRACE( L_AL, L_FUNCTION_END, ( L_log_string,
		"End AL_Bush_action::derive_access_path()" ));

}


t_boolean
AL_Bush_action::resolved() const
{

LOG_TRACE( L_AL, L_FUNCTION_BEGIN, ( L_log_string,
	"Begin AL_Bush_action::resolved()" ));

t_boolean is_resolved = TRUE;		// until proven otherwise
AL_Bush_statement * statement_ptr;

FIRST_ELEMENT( statement_ptr,
			   AL_Bush_statement,
			   get_statement_coll_ptr(),
			   c1 );

while( is_resolved && statement_ptr )
{
	AL_Bush_statement_component * component_ptr;

	FIRST_ELEMENT( component_ptr,
				   AL_Bush_statement_component,
				   statement_ptr->get_component_coll_ptr(),
				   c2 );

	while ( is_resolved && component_ptr )
	{
		if ( ! component_ptr->resolved() )
		{
			is_resolved = FALSE;
		}
		else
		{
			NEXT_ELEMENT( component_ptr, c2 );
		}
	}

	NEXT_ELEMENT( statement_ptr, c1 );
}

LOG_TRACE( L_AL, L_FUNCTION_END, ( L_log_string,
	"End AL_Bush_action::resolved()...is_resolved = %d", is_resolved ));

return( is_resolved );

}

void
AL_Bush_action::clear_persistent_ptrs()
{

LOG_TRACE( L_AL, L_FUNCTION_BEGIN, ( L_log_string,
	"Begin AL_Bush_action::clear_persistent_ptrs()" ));

AL_Bush_statement * statement_ptr;

FOR_ALL_ELEMENTS( statement_ptr,
			   AL_Bush_statement,
			   get_statement_coll_ptr(),
			   c1 )
{
	AL_Bush_statement_component * component_ptr;

	FOR_ALL_ELEMENTS( component_ptr,
					  AL_Bush_statement_component,
					  statement_ptr->get_component_coll_ptr(),
					  c2 )
	{
		component_ptr->clear_persistent_ptrs();
	}
}

LOG_TRACE( L_AL, L_FUNCTION_END, ( L_log_string,
	"End AL_Bush_action::clear_persistent_ptrs()" ));

}


AL_Bush_statement *
AL_Bush_statement::create( AL_Bush_action * p_action_ptr )
{

LOG_TRACE( L_AL, L_FUNCTION_BEGIN, ( L_log_string,
	"Begin AL_Bush_statement::create()...p_action_ptr = 0x%x", p_action_ptr ));

AL_Bush_statement * statement_ptr;

statement_ptr = new( mc_dbms_segment::of( p_action_ptr ),
	AL_Bush_statement::get_mc_dbms_typespec() )
	AL_Bush_statement( p_action_ptr );

LOG_TRACE( L_AL, L_FUNCTION_END, ( L_log_string,
	"End AL_Bush_statement::create()" ));

return( statement_ptr );

}


AL_Bush_statement::AL_Bush_statement( AL_Bush_action * p_action_ptr )
	:
	m_type( DONT_CARE )
{

LOG_TRACE( L_AL, L_FUNCTION_BEGIN, ( L_log_string,
	"Begin AL_Bush_statement::AL_Bush_statement()...p_action_ptr = 0x%x",
	p_action_ptr ));

m_action_ptr.relate( p_action_ptr, this );

    DELETE_IN_PROGRESS_INIT()

LOG_TRACE( L_AL, L_FUNCTION_END, ( L_log_string,
	"End AL_Bush_statement::AL_Bush_statement()" ));

}


AL_Bush_statement::~AL_Bush_statement()
{

LOG_TRACE( L_AL, L_HI_FUNCTION_BEGIN, ( L_log_string,
	"Begin AL_Bush_statement::~AL_Bush_statement()" ));

// IMPORTANT: We will not delete the contained components here (due to
// duplicates). Note that the components are deleted in the AL_Bush_action
// destructor. Also note that there is no need to remove from the collection
// because the collection and its contained pointers are deleted automatically
// by the system at the termination of this destructor.

LOG_TRACE( L_AL, L_HI_FUNCTION_END, ( L_log_string,
	"End AL_Bush_statement::~AL_Bush_statement()" ));

}


Description
AL_Bush_statement::render( t_boolean p_encode_reloc ) const
{

LOG_TRACE( L_AL, L_HI_FUNCTION_BEGIN, ( L_log_string,
	"Begin AL_Bush_statement::render()...p_encode_reloc = %d",
	p_encode_reloc ) );

Description statement;
AL_Bush_statement_component * component_ptr;

FOR_ALL_ELEMENTS( component_ptr,
				  AL_Bush_statement_component,
				  get_component_coll_ptr(),
				  c1 )
{
	statement += component_ptr->render( p_encode_reloc );
}

LOG_TRACE( L_AL, L_HI_FUNCTION_END, ( L_log_string,
	"End AL_Bush_statement::render()...result = %s", statement.char_ptr() ));

return( statement );

}

void
AL_Bush_statement::mark_referenced_datatypes(D_dd_srm_scm_sam* p_dd_ptr)
{

LOG_TRACE( L_AL, L_HI_FUNCTION_BEGIN, ( L_log_string,
	"Begin AL_Bush_statement::mark_referenced_datatypes()") );

AL_Bush_statement_component * component_ptr;

FOR_ALL_ELEMENTS( component_ptr,
				  AL_Bush_statement_component,
				  get_component_coll_ptr(),
				  c1 )
{
	component_ptr->mark_referenced_datatypes( p_dd_ptr );
}

LOG_TRACE( L_AL, L_HI_FUNCTION_END, ( L_log_string,
	"End AL_Bush_statement::mark_referenced_datatypes()" ));

}


AL_Bush_statement_component::AL_Bush_statement_component()
{

LOG_TRACE( L_AL, L_HI_FUNCTION_BEGIN, ( L_log_string,
	"Begin AL_Bush_statement_component::AL_Bush_statement_component()" ));

LOG_TRACE( L_AL, L_HI_FUNCTION_END, ( L_log_string,
	"End AL_Bush_statement_component::AL_Bush_statement_component()" ));

}


AL_Bush_statement_component::~AL_Bush_statement_component()
{

LOG_TRACE( L_AL, L_HI_FUNCTION_BEGIN, ( L_log_string,
	"Begin AL_Bush_statement_component::~AL_Bush_statement_component()...this = 0x%x", this ));

LOG_TRACE( L_AL, L_HI_FUNCTION_END, ( L_log_string,
	"End AL_Bush_statement_component::~AL_Bush_statement_component()" ));

}


AL_Bush_literal *
AL_Bush_literal::create( const vchar* p_string,
	const AL_Bush_statement * p_stmt_ptr )
{

LOG_TRACE( L_AL, L_HI_FUNCTION_BEGIN, ( L_log_string,
	"Begin AL_Bush_literal::create()" ));

AL_Bush_literal * literal_ptr;

literal_ptr = new( mc_dbms_segment::of( p_stmt_ptr ),
	AL_Bush_literal::get_mc_dbms_typespec() )
	AL_Bush_literal( p_string );

literal_ptr->set_action_ptr( p_stmt_ptr->get_action_ptr() );

LOG_TRACE( L_AL, L_HI_FUNCTION_END, ( L_log_string,
	"End AL_Bush_literal::create()" ));

return( literal_ptr );

}


AL_Bush_literal::AL_Bush_literal( const vchar * p_string )
	:
	AL_Bush_statement_component(),
	m_string( p_string )
{

LOG_TRACE( L_AL, L_HI_FUNCTION_BEGIN, ( L_log_string,
	"Begin/End AL_Bush_literal::AL_Bush_literal()" ));

    DELETE_IN_PROGRESS_INIT()

}


AL_Bush_literal::~AL_Bush_literal()
{

LOG_TRACE( L_AL, L_HI_FUNCTION_BEGIN, ( L_log_string,
	"Begin/End AL_Bush_literal::~AL_Bush_literal()" ));

}



AL_Bush_relocatable *
AL_Bush_relocatable::create( const vchar * p_orig_reloc,
                             const Id & p_object_id,
                             int p_field_id,
                             AL_Bush_statement * p_stmt_ptr )
{

LOG_TRACE( L_AL, L_FUNCTION_BEGIN, ( L_log_string,
	"Begin AL_Bush_relocatable::create()...orig_reloc = %s, object_id.class_type = %d, object_id.value = %d, field_id = %d",
	p_orig_reloc, p_object_id.get_class_type(), p_object_id.get_entire_value(), p_field_id ));

AL_Bush_relocatable * reloc_ptr;

reloc_ptr = new( mc_dbms_segment::of( p_stmt_ptr ),
                 AL_Bush_relocatable::get_mc_dbms_typespec() )
  AL_Bush_relocatable( p_orig_reloc, p_object_id, p_field_id );

reloc_ptr->set_action_ptr( p_stmt_ptr->get_action_ptr() );

LOG_TRACE( L_AL, L_FUNCTION_END, ( L_log_string,
	"End AL_Bush_relocatable::create()" ));

return( reloc_ptr );

}


AL_Bush_relocatable::AL_Bush_relocatable( const vchar * p_orig_reloc,
	const Id & p_object_id, int p_field_id )
	:
	AL_Bush_statement_component(),
	m_orig_relocatable( p_orig_reloc ),
	m_object_id( p_object_id ),
	m_field_id( p_field_id )
{

LOG_TRACE( L_AL, L_FUNCTION_BEGIN, ( L_log_string,
	"Begin AL_Bush_relocatable::AL_Bush_relocatable()" ));

// IMPORTANT: We will build the encoded relocatable here
// since the encoded relocatable is
// basically constant. There is no need to cause the overhead of building
// it on the fly everytime rendered.
//
// The relocatable is "encrypted" as indicated by the following example:
//     Select any dog from instances of DG;  // DG is relocatable
// After encryption:
//     Select any dog from instances of ${#@!:23:5128733:2:DG};
// where
//     23 is an example of the class type of id
//     5128733 is an example of the id value
//     2 is example of the field id (eg - use event label instead
//        of event meaning)
//     DG is original relocatable string value (this field not used and
//        may be null/empty)

vchar reloc_buf[ 256 ];

vcharCopyScribed( 
	vcharScribeFormatLiteral("%s%d:%lu:%d:%s}", 
	  LEADING_DELIMITER.char_ptr(),
	  m_object_id.get_class_type(), m_object_id.get_entire_value(),
	  m_field_id,
      m_orig_relocatable.char_ptr() ),
	reloc_buf );

    m_encoded_reloc = reloc_buf;

    DELETE_IN_PROGRESS_INIT()

LOG_TRACE( L_AL, L_FUNCTION_BEGIN, ( L_log_string,
	"End AL_Bush_relocatable::AL_Bush_relocatable()...encoded_reloc = %s",
	m_encoded_reloc.char_ptr() ));

}


AL_Bush_relocatable::~AL_Bush_relocatable()
{


LOG_TRACE( L_AL, L_HI_FUNCTION_BEGIN, ( L_log_string,
	"Begin AL_Bush_relocatable::~AL_Bush_relocatable()...encoded_reloc = %s",
	m_encoded_reloc.char_ptr() ));


LOG_TRACE( L_AL, L_HI_FUNCTION_BEGIN, ( L_log_string,
	"End AL_Bush_relocatable::~AL_Bush_relocatable()" ));

}


Description
AL_Bush_relocatable::render( t_boolean p_encode_reloc ) const
{

LOG_TRACE( L_AL, L_HI_FUNCTION_BEGIN, ( L_log_string,
	"Begin AL_Bush_relocatable::render()...p_encode_reloc = %d",
	p_encode_reloc ));

if ( p_encode_reloc )
{
	if ( Invocation::get_debug_ASL() )
	{
		// IMPORTANT: Need to write code to insert mapped string at end
		// of encoded relocatable. Will be done in future when we add
		// debug option.
		LOG_TRACE( L_AL, L_HI_FUNCTION_BEGIN, ( L_log_string,
			"End AL_Bush_relocatable::render()...using encoded form, debug = ON, result = ->%s<-",
			get_encoded_reloc().char_ptr() ));

		return( get_encoded_reloc() );
	}
	else
	{
		LOG_TRACE( L_AL, L_HI_FUNCTION_BEGIN, ( L_log_string,
			"End AL_Bush_relocatable::render()...using encoded form, debug = OFF, result = ->%s<-",
			get_encoded_reloc().char_ptr() ));

		return( get_encoded_reloc() );
	}
}
else
{
  Description orig_string = get_orig_relocatable();
  Description return_string;

  get_mapped_string( get_domain_ptr(),
                     get_object_id().get_class_type(),
                     get_object_id().get_entire_value(),
                     get_field_id(),
                     orig_string.char_ptr(),
                     return_string );

	LOG_TRACE( L_AL, L_HI_FUNCTION_BEGIN, ( L_log_string,
			"End AL_Bush_relocatable::render()...using mapped form, result = ->%s<-",
		return_string.char_ptr() ));

	return( return_string );

}

}

void
AL_Bush_relocatable::mark_referenced_datatypes(D_dd_srm_scm_sam* p_dd_ptr) const
{

LOG_TRACE( L_AL, L_HI_FUNCTION_BEGIN, ( L_log_string,
	"Begin AL_Bush_relocatable::mark_referenced_datatypes()") );

switch ( get_field_id() )
{
    case OBJECT_KEY_LETTERS_FIELD:
    case RELATIONSHIP_NUMBER_FIELD:
    case EVENT_LABEL_FIELD:
    case EXTERNAL_ENTITY_KL_FIELD:
    case EVENT_MEANING_FIELD:
    case EVENT_MEANING_TICKED_FIELD:
    case RELATIONSHIP_PHRASE_FIELD:
        // no data type associated
      break;

    case ATTRIBUTE_FIELD:
      {
        Attribute * attr_ptr =
          AL_Generic_finds::find_attribute_by_id( p_dd_ptr->get_domain_ptr(),
                                                  m_object_id );
        if ( attr_ptr )
        {
            D_data_type * ret_type =
                p_dd_ptr->
                    find_data_type_by_id( attr_ptr->get_data_type_id () );

            if ( ret_type != 0 )
            {
                ret_type->set_referenced(TRUE);
            }
        }
      }
      break;

    case SM_EVENT_DATA_ITEM_NAME_FIELD:
      {
        D_sm_event_data_item * edi_ptr =
          AL_Generic_finds::find_sm_event_data_item_by_id( p_dd_ptr->get_domain_ptr(),
                                                  m_object_id );
        if ( edi_ptr )
        {
            D_data_type * ret_type =
                p_dd_ptr->
                    find_data_type_by_id( edi_ptr->get_data_type_id () );

            if ( ret_type != 0 )
            {
                ret_type->set_referenced(TRUE);
            }
        }
      }
      break;

    case EE_EVENT_DATA_ITEM_NAME_FIELD:
      {
        D_external_entity_event_data_item * edi_ptr =
          AL_Generic_finds::find_external_entity_event_data_item_by_id( p_dd_ptr->get_domain_ptr(),
                                                  m_object_id );
        if ( edi_ptr )
        {
            D_data_type * ret_type =
                p_dd_ptr->
                    find_data_type_by_id( edi_ptr->get_data_type_id () );

            if ( ret_type != 0 )
            {
                ret_type->set_referenced(TRUE);
            }
        }
      }
      break;

    case TRANSFORMER_FIELD:
      {
        D_transformer * trans_ptr =
          AL_Generic_finds::find_transformer_by_id( p_dd_ptr->get_domain_ptr(),
                                                  m_object_id );
        if ( trans_ptr )
        {
            D_data_type * ret_type =
                p_dd_ptr->
                    find_data_type_by_id( trans_ptr->get_return_type_id () );

            if ( ret_type != 0 )
            {
                ret_type->set_referenced(TRUE);
            }
        }
      }
      break;

    case TRANSFORMER_PARM_FIELD:
      {
        D_transformer_parm * parm_ptr =
          AL_Generic_finds::find_transformer_parm_by_id( p_dd_ptr->get_domain_ptr(),
                                                  m_object_id );
        if ( parm_ptr )
        {
            D_data_type * ret_type =
                p_dd_ptr->
                    find_data_type_by_id( parm_ptr->get_data_type_id () );

            if ( ret_type != 0 )
            {
                ret_type->set_referenced(TRUE);
            }
        }
      }
      break;

    case BRIDGE_FIELD:
      {
        D_bridge * bridge_ptr =
          AL_Generic_finds::find_bridge_by_id( p_dd_ptr->get_domain_ptr(),
                                                  m_object_id );
        if ( bridge_ptr )
        {
            D_data_type * ret_type =
                p_dd_ptr->
                    find_data_type_by_id( bridge_ptr->get_return_type_id () );

            if ( ret_type != 0 )
            {
                ret_type->set_referenced(TRUE);
            }
        }
      }
      break;

    case BRIDGE_PARM_FIELD:
      {
        D_bridge_parm * parm_ptr =
          AL_Generic_finds::find_bridge_parm_by_id( p_dd_ptr->get_domain_ptr(),
                                                  m_object_id );
        if ( parm_ptr )
        {
            D_data_type * ret_type =
                p_dd_ptr->
                    find_data_type_by_id( parm_ptr->get_data_type_id () );

            if ( ret_type != 0 )
            {
                ret_type->set_referenced(TRUE);
            }
        }
      }
      break;

    case SYNCH_SVC_FIELD:
      {
        D_synchronous_service * ss_ptr =
          p_dd_ptr->find_synch_service_by_id( m_object_id );

        if ( ss_ptr )
        {
            D_data_type * ret_type =
                p_dd_ptr->
                    find_data_type_by_id( ss_ptr->get_return_type_id () );

            if ( ret_type != 0 )
            {
                ret_type->set_referenced(TRUE);
            }
        }
      }
      break;

    case SYNCH_SVC_PARM_FIELD:
      {
        D_synchronous_service_parm * parm_ptr =
          AL_Generic_finds::find_synch_service_parm_by_id( p_dd_ptr->get_domain_ptr(),
                                                  m_object_id );
        if ( parm_ptr )
        {
            D_data_type * ret_type =
                p_dd_ptr->
                    find_data_type_by_id( parm_ptr->get_data_type_id () );

            if ( ret_type != 0 )
            {
                ret_type->set_referenced(TRUE);
            }
        }
      }
      break;

	case ENUMERATOR_FIELD:   // the data type will include all values
      {
        D_data_type * dt_ptr =
          p_dd_ptr->find_data_type_by_id( m_object_id );

        if ( dt_ptr != 0 )
        {
            dt_ptr->set_referenced(TRUE);
        }
      }
      break;

    case UNKNOWN_RELOC_TYPE:
    case RELOC_IGNORE_DATA:
    case RELOC_NOT_YET_ADDED:
      break;
}

LOG_TRACE( L_AL, L_HI_FUNCTION_END, ( L_log_string,
	"End AL_Bush_relocatable::mark_referenced_datatypes()" ));

}


t_boolean
AL_Bush_relocatable::get_mapped_string( Domain * p_domain_ptr,
                                        int p_id_class_type,
                                        unsigned long p_id_entire_value,
                                        int p_field_id,
                                        const vchar *p_orig_string,
                                        Description & p_mapped_string
                                        )
{

Description domain_name = p_domain_ptr->get_domain_name_char_ptr();
  
LOG_TRACE( L_AL, L_HI_FUNCTION_BEGIN, ( L_log_string,
	"Begin AL_Bush_relocatable::get_mapped_string()...p_domain = %s, p_id_class_type = %d, p_id_entire_value = %lu, p_field_id = %d, ",
	domain_name.char_ptr(), p_id_class_type,
	p_id_entire_value, p_field_id ));

t_boolean mapped = FALSE;

if ( p_orig_string && vcharLength(p_orig_string) != 0 )
  p_mapped_string = p_orig_string;
else
  p_mapped_string = UNRESOLVED_SYMBOL;

Domain * domain_ptr = p_domain_ptr;

if ( domain_ptr == 0 )
{
	LOG_ERROR( ( L_log_string,
		"AL_Bush_relocatable::get_mapped_string()...domain_ptr == 0!" ));

	return( mapped );
}

if ( p_id_entire_value == 0
			||
	 p_id_class_type == Id::NO_CLASS_TYPE )
{

	return( mapped );
}

Id generic_object_id;
generic_object_id.set_class_type( p_id_class_type );
generic_object_id.set_entire_value( ( unsigned int ) p_id_entire_value );

vchar ASC_TICK[2];
ASC_TICK[0] = vcharFromASCII('\'');
ASC_TICK[1] = vcharFromASCII('\0');

switch( (t_class_type)p_id_class_type )
{
case NO_CLASS_TYPE:
  break;
  
case DOMAIN_TYPE:
  break;

case DD_SRM_SCM_SAM_TYPE:
  break;

case SUBSYSTEM_TYPE:
  break;

case EXTERNAL_ENTITY_TYPE:
  {
    D_external_entity * ee_ptr =
      AL_Generic_finds::find_external_entity_by_id(domain_ptr,
                                                   generic_object_id );
    if ( ee_ptr )
      {
//      if ( p_field_id == AL_Generic_finds::EXTERNAL_ENTITY_NAME_FIELD )
//        {
//          p_mapped_string = ee_ptr->external_entity_name();
//          mapped = TRUE;
//        }
//      else
          if ( p_field_id == AL_Generic_finds::EXTERNAL_ENTITY_KL_FIELD )
          {
            p_mapped_string = ee_ptr->external_entity_key_letters();
            mapped = TRUE;
          }
      }
  }
break;

case EXT_ENTITY_EVENT_TYPE:
  {
    D_external_entity_event * event_ptr =
      AL_Generic_finds::find_external_entity_event_by_id(domain_ptr,
                                                         generic_object_id );
    if ( event_ptr )
      {
        if ( p_field_id == AL_Generic_finds::EVENT_LABEL_FIELD )
          {
            p_mapped_string = event_ptr->get_derived_event_label();
            mapped = TRUE;
          }
        else if ( p_field_id == AL_Generic_finds::EVENT_MEANING_FIELD )
          {
            p_mapped_string = event_ptr->get_event_meaning();
            mapped = TRUE;
          }
        else 	// must be a 'ticked' meaning
          {
            // HACK: check the ticks here
            p_mapped_string.reset(event_ptr->get_event_meaning().length()+2);
            p_mapped_string += ASC_TICK;
            p_mapped_string += event_ptr->get_event_meaning(); 
            p_mapped_string += ASC_TICK;
            mapped = TRUE;
          }
      }
  }
break;

case EXT_ENTITY_DATA_ITEM_TYPE:
  break;

case EXT_ENTITY_EVENT_DATA_ITEM_TYPE:
  {
    D_external_entity_event_data_item * data_item_ptr =
      AL_Generic_finds::find_external_entity_event_data_item_by_id(domain_ptr,
                                                                   generic_object_id );
    if ( data_item_ptr )
      {
        p_mapped_string = data_item_ptr->name();
        mapped = TRUE;
      }
  }
break;

case DATA_TYPE_TYPE:
{
    D_data_type * ptr =
      AL_Generic_finds::find_data_type_by_id( domain_ptr, generic_object_id);
    if ( ptr )
      {
		if ( ptr->get_enum_data_type_ptr() )
		{
			p_mapped_string = ptr->name();
			mapped = TRUE;
		}
      }
  }
break;

case ENUMERATOR_TYPE:
  {
    D_enumerator * ptr =
      AL_Generic_finds::find_enumerator_by_id( domain_ptr, generic_object_id);
    if ( ptr )
      {
        p_mapped_string = ptr->name();
        mapped = TRUE;
      }
  }
break;

case BRIDGE_TYPE:
  {
    D_bridge * ptr =
      AL_Generic_finds::find_bridge_by_id( domain_ptr, generic_object_id);
    if ( ptr )
      {
        p_mapped_string = ptr->get_name();
        mapped = TRUE;
      }
  }
break;

case BRIDGE_PARM_TYPE:
  {
    D_bridge_parm * ptr =
      AL_Generic_finds::find_bridge_parm_by_id( domain_ptr,
                                                generic_object_id );
    if ( ptr )
      {
        p_mapped_string = ptr->get_name();
        mapped = TRUE;
      }
  }
break;

case SYNCH_SERVICE_TYPE:
  {
    D_synchronous_service * ptr =
      AL_Generic_finds::find_synch_service_by_id( domain_ptr,
                                                  generic_object_id);
    if ( ptr )
      {
        p_mapped_string = ptr->get_name();
        mapped = TRUE;
      }
  }
break;

case SYNCH_SERVICE_PARM_TYPE:
  {
    D_synchronous_service_parm * ptr =
      AL_Generic_finds::find_synch_service_parm_by_id( domain_ptr,
                                                       generic_object_id );
    if ( ptr )
      {
        p_mapped_string = ptr->get_name();
        mapped = TRUE;
      }
  }
break;

case IM_OCM_OAM_TYPE:
  break;

case OBJECT_TYPE:
  {
    Object * object_ptr =
      AL_Generic_finds::find_object_by_id( domain_ptr, generic_object_id);
    if ( object_ptr )
      {
        p_mapped_string = object_ptr->object_key_letters();
        mapped = TRUE;
      }
  }
break;

case ATTRIBUTE_TYPE:
  {
    Attribute * attr_ptr =
      AL_Generic_finds::find_attribute_by_id( domain_ptr,
                                              generic_object_id );
    if ( attr_ptr )
      {
        p_mapped_string = attr_ptr->get_attr_name();
        mapped = TRUE;
      }
  }
break;

case IMPORTED_OBJECT_TYPE:
  break;

case RELATIONSHIP_TYPE:
  {
    Relationship * rel_ptr =
      AL_Generic_finds::find_relationship_by_id(domain_ptr,
                                                generic_object_id );
    if ( rel_ptr )
      {
        int num;
        vchar num_char[ 17 ];
        num_char[ 0 ] = vcharFromASCII('R');

        num = rel_ptr->get_rel_number();
        vcharCopyScribed(vcharScribeFormatLiteral("%d", num ),
                         &num_char[1] );
        p_mapped_string = num_char;
        mapped = TRUE;
      }
  }
break;

case OBJ_IN_REL_TYPE:
  {
    Object_in_relationship * oir_ptr =
      AL_Generic_finds::find_object_in_relationship_by_id(domain_ptr,
                                                          generic_object_id );
    if ( oir_ptr )
      {
        if ( p_field_id == AL_Generic_finds::RELATIONSHIP_PHRASE_FIELD )
          {
            Object_in_non_inh_relationship * oinir_ptr =
              oir_ptr->get_object_in_non_inh_relationship_ptr();
            if ( oinir_ptr == 0 )
              {
                LOG_ERROR( ( L_log_string,
                             "AL_Bush_relocatable::get_mapped_string()...oinir_ptr == 0; generic_object_id.class_value = %d", generic_object_id.get_entire_value() ) );
              }
            else
              {
                p_mapped_string.reset(oinir_ptr->text_phrase().length()+2);
                p_mapped_string += ASC_TICK;
                p_mapped_string += oinir_ptr->text_phrase(); 
                p_mapped_string += ASC_TICK;
                mapped = TRUE;
              }
          }
      }
  }
break;

case ATTR_REF_IN_OBJECT_TYPE:
  break;

case EXT_ENTITY_IN_MODEL_TYPE:
  break;

case COMMUNICATION_PATH_TYPE:
  break;

case ACCESS_PATH_TYPE:
  break;

case TRANSFORMER_TYPE:
  {
    D_transformer * ptr =
      AL_Generic_finds::find_transformer_by_id( domain_ptr,
                                                generic_object_id );
    if ( ptr )
      {
        p_mapped_string = ptr->get_name();
        mapped = TRUE;
      }
  }
break;

case TRANSFORMER_PARM_TYPE:
  {
    D_transformer_parm * ptr =
      AL_Generic_finds::find_transformer_parm_by_id( domain_ptr,
                                                     generic_object_id );
    if ( ptr )
      {
        p_mapped_string = ptr->get_name();
        mapped = TRUE;
      }
  }
break;

case SM_SPT_PM_TYPE:
  break;

case STATE_TYPE:
  break;

case TRANSITION_TYPE:
  break;

case EVENT_TYPE:
  {
    D_sm_event * event_ptr =
      AL_Generic_finds::find_sm_event_by_id(domain_ptr, generic_object_id );
    if ( event_ptr )
      {
        if ( p_field_id == AL_Generic_finds::EVENT_LABEL_FIELD )
          {
            p_mapped_string = event_ptr->get_derived_event_label();
            if ( event_ptr->is_polymorphic_event() )
              {
                p_mapped_string += "*";
              }
            mapped = TRUE;
          }
        else if ( p_field_id == AL_Generic_finds::EVENT_MEANING_FIELD )
          {
            p_mapped_string = event_ptr->get_event_meaning();
            mapped = TRUE;
          }
        else 	// must be a 'ticked' meaning
          {
            p_mapped_string.reset(event_ptr->get_event_meaning().length()+2);
            p_mapped_string += ASC_TICK;
            p_mapped_string += event_ptr->get_event_meaning(); 
            p_mapped_string += ASC_TICK;
            mapped = TRUE;
          }
      }
  }
break;

case ACTION_TYPE:
  break;

case EVENT_DATA_ITEM_TYPE:
  {
    D_sm_event_data_item * data_item_ptr =
      AL_Generic_finds::find_sm_event_data_item_by_id(domain_ptr,
                                                      generic_object_id );
    if ( data_item_ptr )
      {
        p_mapped_string = data_item_ptr->get_event_data_name();
        mapped = TRUE;
      }
  }
break;

case SUPPLEMENTAL_DATA_TYPE:
  break;

case DERIVED_COMMUNICATION_PATH_TYPE:
  break;
  
case DERIVED_ACCESS_PATH_TYPE:
  break;

case INSTANCE_TYPE:
  break;

case OBJECT_INST_TYPE:
  break;

case ATTRIBUTE_INST_TYPE:
  break;

case RELATIONSHIP_INST_TYPE:
  break;

case RELATED_OBJECT_INST_PAIR_TYPE:
  break;

case EVENT_INST_TYPE:
  break;

case EVENT_DATA_ITEM_INST_TYPE:
  break;

case GRAPHICAL_ELEMENT_TYPE:
  break;

case AUTOCONNECTORS:
  break;

case GREATEST_ID_TYPE:
  break;
}

LOG_TRACE( L_AL, L_HI_FUNCTION_END, ( L_log_string,
	"End AL_Bush_relocatable::get_mapped_string()...p_mapped_string = %s",
	p_mapped_string.char_ptr() ));

return( mapped );

}


t_boolean
AL_Bush_relocatable::resolved() const
{

LOG_TRACE( L_AL, L_FUNCTION_BEGIN, ( L_log_string,
	"Begin AL_Bush_relocatable::resolved()" ));

Description mapped_string;
t_boolean is_resolved = 
  get_mapped_string( get_domain_ptr(),
                     get_object_id().get_class_type(),
                     get_object_id().get_entire_value(),
                     get_field_id(),
                     NULL,
                     mapped_string );

LOG_TRACE( L_AL, L_FUNCTION_BEGIN, ( L_log_string,
	"End AL_Bush_relocatable::resolved()...is_resolved = %d",
	is_resolved ));

return( is_resolved );

}



DELETE_DOWN_START_SUBTYPE( AL_Bush_action )

  delete_mc_dbms_relationship_1_1_body(AL_Bush_action,m_D_execution_spec_ptr,D_execution_spec,m_AL_Action_ptr)
  delete_mc_dbms_relationship_m_1_body(AL_Bush_action,m_statement_coll,AL_Bush_statement,m_action_ptr)
  delete_mc_dbms_relationship_m_1_body(AL_Bush_action,m_component_coll,AL_Bush_statement_component,m_action_ptr)

DELETE_DOWN_END_SUBTYPE( AL_Bush_action )


DELETE_DOWN_START_SUBTYPE( AL_Bush_statement )

  delete_mc_dbms_relationship_1_m_body(AL_Bush_statement,m_action_ptr,AL_Bush_action,m_statement_coll)
  delete_mc_dbms_relationship_m_m_body(AL_Bush_statement,m_component_coll,AL_Bush_statement_component,m_statement_coll)

DELETE_DOWN_END_SUBTYPE( AL_Bush_statement )


DELETE_DOWN_START_SUPERTYPE( AL_Bush_statement_component )

  delete_mc_dbms_relationship_1_m_body(AL_Bush_statement_component,m_action_ptr,AL_Bush_action,m_component_coll)
  delete_mc_dbms_relationship_m_m_body(AL_Bush_statement_component,m_statement_coll,AL_Bush_statement,m_component_coll)

DELETE_DOWN_END_SUPERTYPE( AL_Bush_statement_component )


DELETE_DOWN_START_SUBTYPE( AL_Bush_literal )

  delete_mc_dbms_relationship_supertype_body( AL_Bush_statement_component )

DELETE_DOWN_END_SUBTYPE( AL_Bush_literal )


DELETE_DOWN_START_SUBTYPE( AL_Bush_relocatable )

  delete_mc_dbms_relationship_supertype_body( AL_Bush_statement_component )

DELETE_DOWN_END_SUBTYPE( AL_Bush_relocatable )



mc_dbms_relationship_1_1_body(AL_Bush_action,m_D_execution_spec_ptr,D_execution_spec,m_AL_Action_ptr);
mc_dbms_relationship_m_1_body(AL_Bush_action,m_statement_coll,AL_Bush_statement,m_action_ptr);
mc_dbms_relationship_m_1_body(AL_Bush_action,m_component_coll,AL_Bush_statement_component,m_action_ptr);
mc_dbms_relationship_1_m_body(AL_Bush_statement,m_action_ptr,AL_Bush_action,m_statement_coll);
mc_dbms_relationship_m_m_body(AL_Bush_statement,m_component_coll,AL_Bush_statement_component,m_statement_coll);
mc_dbms_relationship_1_m_body(AL_Bush_statement_component,m_action_ptr,AL_Bush_action,m_component_coll);
mc_dbms_relationship_m_m_body(AL_Bush_statement_component,m_statement_coll,AL_Bush_statement,m_component_coll);

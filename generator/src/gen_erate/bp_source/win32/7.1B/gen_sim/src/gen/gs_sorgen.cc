/*========================================================================
 *
 * File:      $RCSfile: gs_sorgen.cc,v $
 * Version:   $Revision: 1.11 $
 * Modified:  $Date: 2013/01/10 23:42:43 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 * Interface to PCCTS parser and back end
 *
 * This is the function that bridges between the .AL_XLATE
 * command and the PCCTS parser and back end for code generation
 */

#include "vstdio.h"

#include "myToken.h"
#include "myAST.h"
#include "myPanic.h"
#include "myTokenBuffer.h"
#include "DLGLexer.h"
#include "P.h"
#include "GEN_SOR.h"
#include "p_ckgendb.hh"

#include <gs_ui.hh>
#include <gs_actn.hh>
#include <gs_arch.hh>   // i3159.3.1 added
#include <gs_stack.hh>
#include <gs_selct.hh>
#include <i_oinst.hh>
#include <i_ainst.hh>
#include <i_var.hh>

#include <u_string.hh>
#include <u_error.hh>
#include <u_trace.hh>

static I_Object_Instance* get_self_ptr_action( GS_var_si* p_inst_var_si_ptr );
static I_Object_Instance* get_self_ptr_ib_trans( GS_var_si* p_inst_var_si_ptr );
static I_Object_Instance* get_self_ptr_attribute( GS_var_si* p_inst_var_si_ptr );
static I_Object_Instance* get_evt_ptr( GS_var_si* p_inst_var_si_ptr );
static I_Object_Instance* get_descrip_owner_ptr( GS_var_si* p_inst_var_si_ptr );
static t_core_data_type get_return_data_type( GS_var_si* p_inst_var_si_ptr, P_checkGenDB& p_ck);
static I_Object_Instance* find_attribute_from_dbattr( GS_var_si* p_inst_var_si_ptr );
static unsigned int get_action_domain_code( GS_var_si* p_inst_var_si_ptr );

t_boolean parser_gen_actn_script(
    GS_action::e_action_home p_action_home,
    GS_var_si* p_inst_var_si_ptr,
    const GS_string& p_script_file_name_str)

{

  LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_BEGIN,
             (L_log_string,
              "Begin  parser_gen_actn_script (p_action_home=%d, p_inst_var_si_ptr=0x%08x, p_script_file_name_str=\"%S\").",
              p_action_home,
              p_inst_var_si_ptr,
              vcharScribeASCII(p_script_file_name_str.char_ptr ()) ));

  if (! p_inst_var_si_ptr)
  {
      LOG_ERROR ((L_log_string,
          "parser_gen_actn_script ():  p_inst_var_si_ptr==0."));
      return FALSE;
  }
       
  Description al_inst_var_name_str = p_inst_var_si_ptr->get_var_name_str ();
  char *al_inst_var_name_str_ASCII = Description::createAsciiFromVchar(al_inst_var_name_str.char_ptr());
 
  if (! p_inst_var_si_ptr->get_object_inst_ref_var_ptr ())
  {
      Description err_msg ("Variable '");
      err_msg += al_inst_var_name_str;
      err_msg += "' is not an Object Instance Reference variable.";
      GS_ui::inform (UI_INFORM__ERROR, err_msg);
      Description::freeAsciiFromVchar( al_inst_var_name_str_ASCII );
      return FALSE;
  }


    switch (p_action_home)
    {
    case GS_action::INSTANCE_STATE:
    case GS_action::ASSIGNER_STATE:
	if (p_inst_var_si_ptr->get_object_inst_ref_var_ptr ()->
	    get_key_letters_str () != "SM_ACT")
	{
		Description err_msg ("Object Instance Reference Variable '");
		err_msg += al_inst_var_name_str;
		err_msg += "' does not refer to an object of type SM_ACT.";
	    GS_ui::inform (UI_INFORM__ERROR, err_msg);
        Description::freeAsciiFromVchar( al_inst_var_name_str_ASCII );
	    return FALSE;
	}
	break;

    case GS_action::BRIDGE:
	if (p_inst_var_si_ptr->get_object_inst_ref_var_ptr ()->
	    get_key_letters_str () != "S_BRG")
	{
		Description err_msg ("Object Instance Reference Variable '");
		err_msg += al_inst_var_name_str;
		err_msg += "' does not refer to an object of type S_BRG.";
	    GS_ui::inform (UI_INFORM__ERROR, err_msg);
        Description::freeAsciiFromVchar( al_inst_var_name_str_ASCII );
	    return FALSE;
	}
	break;

    case GS_action::TRANSFORMER:
	if (p_inst_var_si_ptr->get_object_inst_ref_var_ptr ()->
	    get_key_letters_str () != "O_TFR")
	{
		Description err_msg ("Object Instance Reference Variable '");
		err_msg += al_inst_var_name_str;
		err_msg += "' does not refer to an object of type O_TFR.";
	    GS_ui::inform (UI_INFORM__ERROR, err_msg);
        Description::freeAsciiFromVchar( al_inst_var_name_str_ASCII );
	    return FALSE;
	}
	break;

    case GS_action::SYNCH_SERVICE:
	if (p_inst_var_si_ptr->get_object_inst_ref_var_ptr ()->
	    get_key_letters_str () != "S_SYNC")
	{
		Description err_msg ("Object Instance Reference Variable '");
		err_msg += al_inst_var_name_str;
		err_msg += "' does not refer to an object of type S_SYNC.";
	    GS_ui::inform (UI_INFORM__ERROR, err_msg);
        Description::freeAsciiFromVchar( al_inst_var_name_str_ASCII );
	    return FALSE;
	}
	break;

    case GS_action::ATTRIBUTE:
	if (p_inst_var_si_ptr->get_object_inst_ref_var_ptr ()->
	    get_key_letters_str () != "O_DBATTR")
	{
		Description err_msg ("Object Instance Reference Variable '");
		err_msg += al_inst_var_name_str;
		err_msg += "' does not refer to an object of type O_DBATTR.";
	    GS_ui::inform (UI_INFORM__ERROR, err_msg);
        Description::freeAsciiFromVchar( al_inst_var_name_str_ASCII );
	    return FALSE;
	}
	break;

    case GS_action::DATA_TYPE:
    case GS_action::EE_EVENT:
    case GS_action::RELATIONSHIP:
    case GS_action::SM_EVENT:
    	LOG_ERROR ((L_log_string,
	        "GS_gen_action::gen_actn_script ():  Unsupported p_action_home."));
        Description::freeAsciiFromVchar( al_inst_var_name_str_ASCII );
	    return FALSE;

    default:
    	LOG_ERROR ((L_log_string,
	        "GS_gen_action::gen_actn_script ():  p_action_home unknown."));
        Description::freeAsciiFromVchar( al_inst_var_name_str_ASCII );
	    return FALSE;
    }



  I_var* descrip_str_var_ptr = p_inst_var_si_ptr->
      get_object_inst_ref_var_ptr ()->get_attr_var_ptr ("Action_Semantics");
  if (! descrip_str_var_ptr)
  {
      Description err_msg ("Object Instance Reference Variable '");
      err_msg += al_inst_var_name_str;
      err_msg += "' does not have an attribute named 'Action_Semantics'.";
      GS_ui::inform (UI_INFORM__ERROR, err_msg);
      Description::freeAsciiFromVchar( al_inst_var_name_str_ASCII );
      return FALSE;
  }

  Description descrip_str (descrip_str_var_ptr->get_value_str());
  char *descrip_str_ASCII = Description::createAsciiFromVchar(descrip_str.char_ptr());
  Description write_attribute_valid;

  P::al_spec_type spec_type = P::AL_SPEC_STATE_ACTION_E;
  char* described_name = "action";
  switch (p_action_home)
  {
    case GS_action::ATTRIBUTE:
	{
       spec_type = P::AL_SPEC_ATTRIBUTE_E;
       described_name = "derived attribute";

	   I_var* attr_name_var_ptr = 0;
       I_Object_Instance* attr_val = find_attribute_from_dbattr ( p_inst_var_si_ptr );

       int num_found = 0;
       I_Attribute_Instance *attr_name = 
          P_checkGenDB::find_Attribute_Instance_R2002_by_name( attr_val, Description("NAME").char_ptr(), num_found );

       if (num_found > 0)
       {
          attr_name_var_ptr = attr_name->get_var_ptr ();
       }

       if (! attr_name_var_ptr)
       {
          Description err_msg ("Object Instance Reference Variable '");
          err_msg += al_inst_var_name_str;
          err_msg += "' does not have an attribute named 'Name'.";
          GS_ui::inform (UI_INFORM__ERROR, err_msg);
          Description::freeAsciiFromVchar( al_inst_var_name_str_ASCII );
          return FALSE;
       }
       if ( attr_name_var_ptr->get_string_var_ptr() == 0 )
       {
          Description err_msg ("Object Instance Reference Variable '");
          err_msg += al_inst_var_name_str;
          err_msg += "' attribute 'Name' is not of type 'String'.";
          GS_ui::inform (UI_INFORM__ERROR, err_msg);
          Description::freeAsciiFromVchar( al_inst_var_name_str_ASCII );
          return FALSE;
       }

       write_attribute_valid = attr_name_var_ptr->get_string_var_ptr()->get_value();
	}
	break;

    case GS_action::ASSIGNER_STATE:
       spec_type = P::AL_SPEC_ASSIGNER_E;
       described_name = "assigner";
	break;

    case GS_action::BRIDGE:
       spec_type = P::AL_SPEC_BRIDGE_E;
       described_name = "bridge";
	break;

    case GS_action::TRANSFORMER:
      {
       spec_type = P::AL_SPEC_TRANSFORMER_E;
       described_name = "transformer";
       I_var* instance_based_var_ptr = p_inst_var_si_ptr->
         get_object_inst_ref_var_ptr ()->get_attr_var_ptr ("Instance_Based");
       if (! instance_based_var_ptr)
       {
          Description err_msg ("Object Instance Reference Variable '");
          err_msg += al_inst_var_name_str;
          err_msg += "' does not have an attribute named 'Instance_Based'.";
          GS_ui::inform (UI_INFORM__ERROR, err_msg);
          Description::freeAsciiFromVchar( al_inst_var_name_str_ASCII );
          return FALSE;
       }
       if ( instance_based_var_ptr->get_integer_var_ptr() == 0 )
       {
          Description err_msg ("Object Instance Reference Variable '");
          err_msg += al_inst_var_name_str;
          err_msg += "' attribute 'Instance_Based' is not of type 'Integer'.";
          GS_ui::inform (UI_INFORM__ERROR, err_msg);
          Description::freeAsciiFromVchar( al_inst_var_name_str_ASCII );
          return FALSE;
       }

       if ( instance_based_var_ptr->get_integer_var_ptr()->get_value() != 0 )
       {
           spec_type = P::AL_SPEC_IB_TRANSFORMER_E;
           described_name = "instance-based transformer";
       }
      }
	break;

    case GS_action::SYNCH_SERVICE:
       spec_type = P::AL_SPEC_SYNSVC_E;
       described_name = "synchronous service";
	break;
 }

  I_Object_Instance* self_ptr = 0;
  Description self_obj_kl ( "" );
  if ( p_action_home == GS_action::INSTANCE_STATE )
  { 
    self_ptr = get_self_ptr_action( p_inst_var_si_ptr );
  }
  else if ( spec_type == P::AL_SPEC_IB_TRANSFORMER_E )
  { 
    self_ptr = get_self_ptr_ib_trans( p_inst_var_si_ptr );
  }
  else if ( spec_type == P::AL_SPEC_ATTRIBUTE_E )
  { 
    self_ptr = get_self_ptr_attribute( p_inst_var_si_ptr );
  }

  I_Object_Instance* rcvd_evt_ptr = 0;
  if ( p_action_home == GS_action::INSTANCE_STATE ||
       p_action_home == GS_action::ASSIGNER_STATE )
  { 
    rcvd_evt_ptr = get_evt_ptr( p_inst_var_si_ptr );
  }

  I_Object_Instance* descrip_owner_ptr = 0;
  if ( p_action_home == GS_action::BRIDGE ||
       p_action_home == GS_action::TRANSFORMER ||
       p_action_home == GS_action::SYNCH_SERVICE )
  { 
    descrip_owner_ptr = get_descrip_owner_ptr( p_inst_var_si_ptr );
  }

  unsigned int action_domain_code = 
      get_action_domain_code( p_inst_var_si_ptr );

  const vchar* saveBuffer = AST::getVcharBuffer();
  int error_count = 0;
  bool runbe = TRUE;
  try {
    //-------------------------------------------------------------------
    // Declare and allocate front end.
    //-------------------------------------------------------------------
    ColToken::accumulated_offset = 0;
    DLGStringInput in(descrip_str_ASCII);
    DLGLexer lexer(&in,2000);
    MyTokenBuffer pipe(&lexer,1);
    ANTLRToken aToken( (ANTLRTokenType)0 );
    lexer.setToken(&aToken);
    P parser(&pipe);

    P_error er;
    P_checkGenDB ck(&er, FALSE, action_domain_code);

    if ( self_ptr )
    {
      int num_found = 0;
      I_Attribute_Instance* obj_kl_attr = 
        ck.find_Attribute_Instance_R2002_by_name(
          self_ptr, Description("KEY_LETT").char_ptr(), num_found );
  	  if ( obj_kl_attr && (num_found == 1) )
      {
        I_var* ainst_var_ptr = obj_kl_attr->get_var_ptr ();
        if (ainst_var_ptr)
          if (ainst_var_ptr->get_string_var_ptr() )
          {
            self_obj_kl = ainst_var_ptr->get_string_var_ptr()->get_value();
          }
      }
    }

    t_core_data_type ret_type = VOID_DATATYPE;
    if ( p_action_home == GS_action::BRIDGE ||
       p_action_home == GS_action::TRANSFORMER ||
       p_action_home == GS_action::SYNCH_SERVICE ||
       p_action_home == GS_action::ATTRIBUTE )
    {
        ret_type = get_return_data_type( p_inst_var_si_ptr, ck );
    }

    //-------------------------------------------------------------------
    // Initialize the scanner and parser.
    //-------------------------------------------------------------------
    parser.init(&er, &ck, self_ptr, rcvd_evt_ptr, 0, descrip_owner_ptr);
    parser.initReloc();
    parser.setBufferAddr(descrip_str_ASCII,
                          descrip_str.char_ptr());

    //-------------------------------------------------------------------
    // Fire up the parser by initializing and invoking first rule.
    //-------------------------------------------------------------------
    ASTBase *root = NULL;            // Define root of abstract syntax tree.
    int parser_rc;
    bool traceflag = FALSE;
    bool dumpflag = FALSE;

    switch (p_action_home)
    {
    case GS_action::INSTANCE_STATE:
    case GS_action::ASSIGNER_STATE:
    case GS_action::BRIDGE:
    case GS_action::TRANSFORMER:
    case GS_action::SYNCH_SERVICE:
        parser.al_spec( &root,
                       &parser_rc,
                       spec_type, described_name, 0, 0 );   // front end
        break;

    case GS_action::ATTRIBUTE:
		if ( write_attribute_valid.length() == 0 )
		{
			parser.al_spec( &root,
			           &parser_rc,
                       spec_type, described_name, 0, 0 );   // front end
		}
		else
		{
			parser.al_spec( &root,
			           &parser_rc,
                       spec_type, described_name, 0, write_attribute_valid.char_ptr() );   // front end
		}
        break;


    default:
        runbe = FALSE;
        break;
    }

    error_count = er.error_count();
    traceflag = parser.trace;
    dumpflag = parser.dumpflag;
    runbe = parser.sor;
    if ( parser.severe_error )
      runbe = FALSE;

    if ( error_count > 0 )
      {
	    char *msg = Description::createAsciiFromVchar(er.get_error_messages());
		GS_ui::inform (UI_INFORM__ERROR, GS_string(msg));
	    Description::freeAsciiFromVchar(msg);
      }

    if ( ( error_count == 0 ) || runbe )
    {
      error_count = 0;
      SORASTBase *ro_root = root;
      GS_archetype::script_changed( p_script_file_name_str );  // i3159.3.2 added
      ofstream out_file;
      out_file.open ( p_script_file_name_str.char_ptr(), ios::out);
      if (! out_file.good ())
      {
        GS_ui::inform (UI_INFORM__ERROR, GS_string
                       ("Could not open temporary file '")
                       + p_script_file_name_str
                       + "' for writing.");
        return FALSE;
      }

      //-------------------------------------------------------------------
      // Initialize the generator backend
      //-------------------------------------------------------------------
      GEN_SOR be(&parser, out_file);
      be.init( (self_ptr != 0), 
               al_inst_var_name_str_ASCII, self_obj_kl.char_ptr()  );
      er.no_error();

      switch (p_action_home)
      {
      case GS_action::INSTANCE_STATE:
      case GS_action::ASSIGNER_STATE:
          be.statement(&ro_root, traceflag, dumpflag, 0);
          break;

      case GS_action::BRIDGE:
          be.statement(&ro_root, traceflag, dumpflag, 1);
          break;

      case GS_action::TRANSFORMER:
          if ( spec_type == P::AL_SPEC_IB_TRANSFORMER_E )
          {
            be.statement(&ro_root, traceflag, dumpflag, 4);
          }
          else
          {
            be.statement(&ro_root, traceflag, dumpflag, 2);
          }
          break;

      case GS_action::SYNCH_SERVICE:
          be.statement(&ro_root, traceflag, dumpflag, 3);
          break;

      case GS_action::ATTRIBUTE:
          be.statement(&ro_root, traceflag, dumpflag, 5);
          break;
      }
      out_file.close();
      error_count = er.error_count();
      if ( error_count > 0 )
      {
        char *msg = Description::createAsciiFromVchar(er.get_error_messages());
		GS_ui::inform (UI_INFORM__ERROR, GS_string(msg));
        Description::freeAsciiFromVchar(msg);
      }
    }
  }
  catch ( char *msg )
  {
	GS_ui::inform (UI_INFORM__ERROR, GS_string(msg));
	
	Description::freeAsciiFromVchar( descrip_str_ASCII );
    Description::freeAsciiFromVchar( al_inst_var_name_str_ASCII );
    return FALSE;
  }

  AST::setVcharBuffer(saveBuffer);

  Description::freeAsciiFromVchar( descrip_str_ASCII );
  Description::freeAsciiFromVchar( al_inst_var_name_str_ASCII );

  
  LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
      "End  parser_gen_actn_script ()."));

  return ( (error_count == 0) || runbe);

}

static I_Object_Instance* get_self_ptr_action( GS_var_si* p_inst_var_si_ptr )
{

  // select one sm related by action->SM_SM[R515]
  // select one ism related by sm->SM_ISM[R517]
  // select one obj related by ism->O_OBJ[R518]

  I_object_inst_ref_var* action_inst_ref = 
     p_inst_var_si_ptr->get_object_inst_ref_var_ptr();
  I_Object_Instance* p_action = action_inst_ref->get_oinst_ptr();

  mc_dbms_List<I_Object_Instance*> inst_coll;
  inst_coll.insert_last(p_action);
  I_Object* p_obj = p_action->get_Object_R2001_ptr();
  I_object_inst_ref_set_var* inst_set_var_ptr = 
    new I_object_inst_ref_set_var (p_obj, &inst_coll);

  I_object_inst_ref_set_var* sm =
    GS_select::create_single_link( inst_set_var_ptr, "SM_SM", "R515", "");

  I_object_inst_ref_set_var* ism =
    GS_select::create_single_link( sm, "SM_ISM", "R517", "");

  I_object_inst_ref_set_var* obj =
    GS_select::create_single_link( ism, "O_OBJ", "R518", "");

  obj->first();
  I_Object_Instance* ret_val = obj->get_oinst_ptr();

  delete obj;
  delete ism;
  delete sm;
  delete inst_set_var_ptr;
  return ret_val;

}

static I_Object_Instance* get_self_ptr_ib_trans( GS_var_si* p_inst_var_si_ptr )
{

  // select one obj related by trans->O_OBJ[R115]

  I_object_inst_ref_var* trans_inst_ref = 
     p_inst_var_si_ptr->get_object_inst_ref_var_ptr();
  I_Object_Instance* p_trans = trans_inst_ref->get_oinst_ptr();

  mc_dbms_List<I_Object_Instance*> inst_coll;
  inst_coll.insert_last(p_trans);
  I_Object* p_obj = p_trans->get_Object_R2001_ptr();
  I_object_inst_ref_set_var* inst_set_var_ptr = 
    new I_object_inst_ref_set_var (p_obj, &inst_coll);

  I_object_inst_ref_set_var* obj =
    GS_select::create_single_link( inst_set_var_ptr, "O_OBJ", "R115", "");

  obj->first();
  I_Object_Instance* ret_val = obj->get_oinst_ptr();

  delete obj;
  delete inst_set_var_ptr;
  return ret_val;

}

static I_Object_Instance* get_self_ptr_attribute( GS_var_si* p_inst_var_si_ptr )
{

  I_Object_Instance* attr_inst = 
	  find_attribute_from_dbattr( p_inst_var_si_ptr );

  // select one obj related by attr->O_OBJ[R102]

  mc_dbms_List<I_Object_Instance*> inst_coll;
  inst_coll.insert_last(attr_inst);
  I_Object* p_obj = attr_inst->get_Object_R2001_ptr();
  I_object_inst_ref_set_var* inst_set_var_ptr = 
    new I_object_inst_ref_set_var (p_obj, &inst_coll);

  I_object_inst_ref_set_var* obj =
    GS_select::create_single_link( inst_set_var_ptr, "O_OBJ", "R102", "");

  obj->first();
  I_Object_Instance* ret_val = obj->get_oinst_ptr();

  delete obj;
  delete inst_set_var_ptr;
  return ret_val;

}

static I_Object_Instance* find_attribute_from_dbattr( GS_var_si* p_inst_var_si_ptr )
{

  // select one battr related by db_attribute->O_BATTR[R107]
  // select one attr related by battr->O_ATTR[R106]

  I_object_inst_ref_var* attr_inst_ref = 
     p_inst_var_si_ptr->get_object_inst_ref_var_ptr();
  I_Object_Instance* p_attr = attr_inst_ref->get_oinst_ptr();

  mc_dbms_List<I_Object_Instance*> inst_coll;
  inst_coll.insert_last(p_attr);
  I_Object* p_obj = p_attr->get_Object_R2001_ptr();
  I_object_inst_ref_set_var* inst_set_var_ptr = 
    new I_object_inst_ref_set_var (p_obj, &inst_coll);

  I_object_inst_ref_set_var* battr =
     GS_select::create_single_link( inst_set_var_ptr, "O_BATTR", "R107", "");
  I_object_inst_ref_set_var* attr = 
     GS_select::create_single_link( battr, "O_ATTR", "R106", "");

  attr->first();
  I_Object_Instance* ret_val = attr->get_oinst_ptr();

  delete attr;
  delete battr;
  delete inst_set_var_ptr;
  return ret_val;

}

static I_Object_Instance* get_evt_ptr( GS_var_si* p_inst_var_si_ptr )
{
  // select one ah related by action->SM_AH[R514]
  // select one moah related by ah->SM_MOAH[R513]
  // if ( moah->cardinality() == 0 )
  //   .// Look for an action on transition
  //   select one tah related by ah->SM_TAH[R513]
  //   .// R530 has multiplicity 1, not many. However, we use many here
  //   .// for orthagaonality with the SM_MOAH case.  Since the C++ code
  //   .// always uses instance sets, even for cardinality 1 relationships 
  //   .// we can do this. 
  //   select many transitions related by tah->SM_TXN[R530]
  // else
  //   select one sm_state related by moah->SM_STATE[R511]
  //   select many transitions related by sm_state->SM_TXN[R506]
  // end if
  // if (transitions->cardinality() != 0)
  //   select many ns_txns related by transitions->SM_NSTXN[R507]
  //   select many sm_semes related by ns_txns->SM_SEME[R504]
  //   select any sm_sevt related by sm_semes->SM_SEVT[R503]
  //   select one evt related by sm_sevt->SM_EVT[R525] 
  //   if ( evt->cardinality() != 0 )
  //     ret_val = evt;
  //   else
  //      .// Look for a creation transition
  //      select many tmp_txns related by transitions->SM_CRTXN[R507]
  //      select any tmp_sm_lmevt related by cr_txns->SM_LEVT[R509]
  //      select any tmp_sm_sevt related by sm_lmevt->SM_SEVT[R526]
  //      select one tmp_evt related by sm_sevt->SM_EVT[R525] 
  //      ret_val = tmp_evt;
  //   end if
  // end if
  //

  I_Object_Instance* ret_val = 0;

  I_object_inst_ref_var* action_inst_ref = 
     p_inst_var_si_ptr->get_object_inst_ref_var_ptr();
  I_Object_Instance* p_action = action_inst_ref->get_oinst_ptr();

  mc_dbms_List<I_Object_Instance*> inst_coll;
  inst_coll.insert_last(p_action);
  I_Object* p_obj = p_action->get_Object_R2001_ptr();
  I_object_inst_ref_set_var* inst_set_var_ptr = 
    new I_object_inst_ref_set_var (p_obj, &inst_coll);

  I_object_inst_ref_set_var* ah =
    GS_select::create_single_link( inst_set_var_ptr, "SM_AH", "R514", "");
  I_object_inst_ref_set_var* moah =
    GS_select::create_single_link( ah, "SM_MOAH", "R513", "");
  I_object_inst_ref_set_var* sm_state = 0;
  I_object_inst_ref_set_var* sm_tah = 0;
  I_object_inst_ref_set_var* txns = 0;
  if (moah->cardinality() == 0 )
  {
  	// Look for an action on transition
    sm_tah = GS_select::create_single_link( ah, "SM_TAH", "R513", "");
    txns = GS_select::create_single_link( sm_tah, "SM_TXN", "R530", "");
  }
  else 
  {
    sm_state = GS_select::create_single_link( moah, "SM_STATE", "R511", "");
    txns = GS_select::create_single_link( sm_state, "SM_TXN", "R506", "");
  }
    
  if (txns != 0 && txns->cardinality() > 0) 
  {
	I_object_inst_ref_set_var* ns_txns =
		GS_select::create_single_link( txns, "SM_NSTXN", "R507", "");
	
	I_object_inst_ref_set_var* sm_semes =
	    GS_select::create_single_link( ns_txns, "SM_SEME", "R504", "");
	
	I_object_inst_ref_set_var* sm_sevt =
	    GS_select::create_single_link( sm_semes, "SM_SEVT", "R503", "");
	
	I_object_inst_ref_set_var* evt =
	    GS_select::create_single_link( sm_sevt, "SM_EVT", "R525", "");
	
	
	if ( evt->cardinality() > 0 )
	{  
      evt->first();
	  ret_val = evt->get_oinst_ptr();
	} else {
	  // Look for a creation transition
	  I_object_inst_ref_set_var* tmp_cr_txns =
	        GS_select::create_single_link( txns, "SM_CRTXN", "R507", "");
	  I_object_inst_ref_set_var* tmp_sm_lmevt =
	        GS_select::create_single_link( tmp_cr_txns, "SM_LEVT", "R509", "");
	  I_object_inst_ref_set_var* tmp_sm_sevt =
	        GS_select::create_single_link( tmp_sm_lmevt, "SM_SEVT", "R526", "");
	  I_object_inst_ref_set_var* tmp_evt =
	        GS_select::create_single_link( tmp_sm_sevt, "SM_EVT", "R525", "");
			
	  if ( tmp_evt->cardinality() > 0 ) {
	    tmp_evt->first();
	    ret_val = tmp_evt->get_oinst_ptr();
	  }
		  
	  delete tmp_evt;
	  delete tmp_sm_sevt;
	  delete tmp_sm_lmevt;
	  delete tmp_cr_txns;
	}
	
    delete evt;
	delete sm_sevt;
	delete sm_semes;
	delete ns_txns;

    delete txns;
    delete sm_state;  // This may be null, but it is safe to delete a null pointer
	delete sm_tah;  // This may be null, but it is safe to delete a null pointer
  }
  
  delete moah;
  delete ah;
  delete inst_set_var_ptr;

  return ret_val;
}

I_Object_Instance* get_descrip_owner_ptr( GS_var_si* p_inst_var_si_ptr )
{
  I_Object_Instance* ret_val = 0;

  I_object_inst_ref_var* descrip_owner_inst_ref = 
     p_inst_var_si_ptr->get_object_inst_ref_var_ptr();

  ret_val = descrip_owner_inst_ref->get_oinst_ptr();

  return ret_val;
}

t_core_data_type get_return_data_type( GS_var_si* p_inst_var_si_ptr, P_checkGenDB& p_ck )
{

  // select one dt related by transformer->S_DT[R116]
    // or
  // select one dt related by bridge->S_DT[R20]
    // or
  // select one dt related by synch_service->S_DT[R25]
    // or
  // select one battr related by db_attribute->O_BATTR[R107]
  // select one attr related by battr->O_ATTR[R106]
  // select one dt related by attr->S_DT[R114]

  // select one coredt related by dt->S_CDT[R17]
  // if cardinality coredt == 0
  //    select one userdt related by dt->S_UDT[R17]
  //    select one coredt related by userdt->S_CDT[R18]
  // endif
  // return coredt.Core_Typ

  t_core_data_type ret_val = VOID_DATATYPE;

  I_object_inst_ref_var* descrip_owner_inst_ref = 
     p_inst_var_si_ptr->get_object_inst_ref_var_ptr();
  I_Object_Instance* p_descrip_owner = descrip_owner_inst_ref->get_oinst_ptr();

  mc_dbms_List<I_Object_Instance*> inst_coll;
  inst_coll.insert_last(p_descrip_owner);
  I_Object* p_obj = p_descrip_owner->get_Object_R2001_ptr();
  I_object_inst_ref_set_var* inst_set_var_ptr = 
    new I_object_inst_ref_set_var (p_obj, &inst_coll);

  I_object_inst_ref_set_var* dt = 0;
  if ( p_inst_var_si_ptr->get_object_inst_ref_var_ptr ()->
	    get_key_letters_str () == "S_BRG" )
  {
      dt = GS_select::create_single_link( inst_set_var_ptr, "S_DT", "R20", "");
  }
  else if ( p_inst_var_si_ptr->get_object_inst_ref_var_ptr ()->
	    get_key_letters_str () == "O_TFR" )
  {
      dt = GS_select::create_single_link( inst_set_var_ptr, "S_DT", "R116", "");
  }
  else if ( p_inst_var_si_ptr->get_object_inst_ref_var_ptr ()->
	    get_key_letters_str () == "S_SYNC" )
  {
      dt = GS_select::create_single_link( inst_set_var_ptr, "S_DT", "R25", "");
  }
  else if ( p_inst_var_si_ptr->get_object_inst_ref_var_ptr ()->
	    get_key_letters_str () == "O_DBATTR" )
  {
	  I_object_inst_ref_set_var* battr =
	      GS_select::create_single_link( inst_set_var_ptr, "O_BATTR", "R107", "");
      I_object_inst_ref_set_var* attr = 
		  GS_select::create_single_link( battr, "O_ATTR", "R106", "");
      dt = GS_select::create_single_link( attr, "S_DT", "R114", "");
	  delete attr;
	  delete battr;
  }

  if ( dt != 0 )
  {
      I_object_inst_ref_set_var* coredt =
        GS_select::create_single_link( dt, "S_CDT", "R17", "");
      if (coredt->cardinality() == 0 )
      {
        I_object_inst_ref_set_var* userdt =
          GS_select::create_single_link( dt, "S_UDT", "R17", "");

        delete coredt;
        coredt =
          GS_select::create_single_link( userdt, "S_CDT", "R18", "");

        delete userdt;
      }

      if ( coredt->cardinality() > 0 )
      {  
          coredt->first();
          I_Object_Instance* coredt_val = coredt->get_oinst_ptr();

          int num_found = 0;
          I_Attribute_Instance *core_type = 
              p_ck.find_Attribute_Instance_R2002_by_name( coredt_val, Description("CORE_TYP").char_ptr(), num_found );

          if (num_found > 0)
          {
            I_var* ct_ptr = core_type->get_var_ptr ();
            if ( ct_ptr )
              if ( ct_ptr->get_integer_var_ptr() )
                ret_val = (t_core_data_type)(ct_ptr->get_integer_var_ptr()->get_value());
          }

      }

      delete coredt;
	  delete dt;
  }
  delete inst_set_var_ptr;

  return ret_val;
}

unsigned int get_action_domain_code( GS_var_si* p_inst_var_si_ptr )
{
  I_object_inst_ref_var* action_inst_ref = 
     p_inst_var_si_ptr->get_object_inst_ref_var_ptr();
  I_Object_Instance* p_action_inst = action_inst_ref->get_oinst_ptr();

  I_Attribute_Instance * ainst_ptr =
       p_action_inst->get_Attribute_Instance_R2002_coll_ptr()->pick();

  unsigned int ret_val = 0;
  if ( ainst_ptr )
  {
      ret_val = ainst_ptr->get_attribute_ID().get_domain_id();
  }
  return ret_val;
  
}

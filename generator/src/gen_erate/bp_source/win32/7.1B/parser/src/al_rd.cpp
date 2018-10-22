/*========================================================================
 *
 * File:      $RCSfile: al_rd.cpp,v $
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
#include "tokens.h"
#include "ASTBase.h"
#include "AParser.h"
#include "P.h"
#include "DLexerBase.h"

void P::init( P_error *p_er,
              P_checkBase *p_ck,
              persObjPtr p_self,
              persObjPtr p_rcvd_evt,
              persObjPtr p_selected,
              persObjPtr p_param )
{
  // set er data member first so that the parser can report any
  // illegal characters found during initialization
  er = p_er;
  AST::init();
  ANTLRParser::init();
  pck = new P_check(p_er, p_ck);
  st = new BPSymbol_Table(p_er, pck,
                          p_self, p_rcvd_evt,
                          p_selected, p_param);
  trace = FALSE;
  dumpflag = FALSE;
  sor = FALSE;
  severe_error = FALSE;
  ttr = NULL;
  ttqm = NULL;
  relocflag = FALSE;
  wspecflag = FALSE;
  return_valid = FALSE;
  return_found = FALSE;
  self_valid = TRUE;
  in_where = FALSE;
  return_type_reqd = 0;
  param_valid = FALSE;
  spec_descr = "";
  spec_type = AL_SPEC_BRIDGE_E;
  ascii_buffer = NULL;
  orig_buffer = NULL;
}

void P::parse_action(ASTBase **_root,int *_retsignal )
{
  zzRULE;
  int _signal=NoSignal;
  *_retsignal = NoSignal;
  loop_clause_nest_level = 0;
  *_root = new AST(TOK_STATEMENTS);

  tracein("action");

  while ( 1 )
    {
      statement( _root, &_signal );
      _signal = NoSignal;
      if ( LA(1) == Eof ) break;
    }

  ASTBase::tmake( NULL, (*_root)->bottom(), (new AST(Eof)) , NULL);
  if ( dumpflag && (*_root) )
    {
		((AST *)(*_root))->dumpTree("\nAST tree", ascii_buffer);
		printf("--------------------------------------------------\n");
		if (relocflag)
        {
          printf("Relocatable ASTs:\n");
          AST *look = ttr->getItemHead();
          while (look)
            {
              look->dumpNode("  ");
              look = look->getItemNext();
            }
          printf("--------------------------------------------------\n");
        }
    }

  traceout("action");
  return;
}


void P::setBufferAddr(const char *p_ascii_buffer,
                      const vchar *p_vchar_buffer)
{
  ascii_buffer = p_ascii_buffer;
  orig_buffer = p_vchar_buffer;
  AST::setVcharBuffer(p_vchar_buffer);
}

void P::initReloc()
{
  ttr = new P_treeThread;
  relocflag = TRUE;
}

void P::initWSpec(bool p_trace, bool p_dump)
  {
    ttqm = new P_treeThread;
    wspecflag = TRUE;
    in_where = TRUE;
    if (p_trace)
      trace = TRUE;
    if (p_dump)
      dumpflag = TRUE;
  }

P::~P()
{
  AST::cleanup();
  delete pck;
  delete st;
  delete ttr; 
  delete ttqm;
}

const ANTLRChar *P::_get_token( const ANTLRTokenType token )
{
  return _token_tbl[token];
}

const ANTLRChar *P::tokenName(ANTLRTokenType t)
{
  return _token_tbl[t];
}

bool P::accum_datatype( AST* e1, AST* e2,
					    t_core_data_type &t1,
                        t_core_data_type t2,
                        bool &mismatch )
{
  // Function returns TRUE if the types are incompatible
  bool retv = FALSE;   // mismatch on this invocation
  if ( ! mismatch )
    {
	  if ( t1 == ENUMERATION_DATATYPE && t2 != QMARK_DATATYPE ||
	       t2 == ENUMERATION_DATATYPE && t1 != QMARK_DATATYPE )
	  {
		  if ( pck->get_enum_data_type_ptr(e1) != pck->get_enum_data_type_ptr(e2) )
		  {
			  retv = TRUE;
		  }
	  }
	  if ( ! retv )
	  {
		  if ( t2 == QMARK_DATATYPE )
			t2 = t1;
		  if ( t1 == QMARK_DATATYPE )
			t1 = t2;
		  retv = ( t1 != t2 );   // true if mismatch
	  }
      if ( retv )            // if mismatch
        {
          switch( t1 )
            {
            case QMARK_DATATYPE:
              retv = FALSE;
              t1 = t2;                 // use second datatype
              break;
            case UNKNOWN_DATATYPE:
              t1 = t2;                 // use second datatype
              break;
            case REAL_DATATYPE:
              switch( t2 )
                {
                case INTEGER_DATATYPE:
                  retv = FALSE;
                  // return datatype of t1 ( REAL_DATATYPE )
                  break;
                default:
                  break;
                }
            case INTEGER_DATATYPE:
              switch( t2 )
                {
                case REAL_DATATYPE:
                  retv = FALSE;
                  t1 = REAL_DATATYPE;  // return datatype
                  break;
                default:
                  break;
                }
            default:
              ; // mismatch - use first datatype as expression datatype
            }
        }     // if mismatch
      mismatch = retv;
  }    // if ! mismatch
  return retv;
}

bool P::enum_oper_check( AST* op )
{
	// Function returns TRUE if the operation
	// cannot be performed on an enumerator
    if ( op->getType() == TOK_DOUBLEEQUAL ||
         op->getType() == TOK_NOTEQUAL )
	{
  	    return FALSE;
	}
	else
	{
		return TRUE;
	}
}


void P::tracein(const char *r)
{
  if( trace )
    fprintf(stderr, "enter rule \"%s\"\n", r);
}

void P::traceout(const char *r)
{
  if( trace )
    fprintf(stderr, "exit rule \"%s\"\n", r);
}

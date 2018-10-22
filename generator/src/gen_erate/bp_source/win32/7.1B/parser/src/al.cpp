/*========================================================================
 *
 * File:      $RCSfile: al.cpp,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:23 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
/*
 * A n t l r  T r a n s l a t i o n  H e a d e r
 *
 * Terence Parr, Will Cohen, and Hank Dietz: 1989-1999
 * Purdue University Electrical Engineering
 * With AHPCRC, University of Minnesota
 * ANTLR Version 1.33MR20
 *
 *   /opt/PCCTS/v1.33_mr20/bin_sol2/antlr -CC -gt -gs -k 2 -prc on -o /tmp/parser_gen/ al.g
 *
 */

#define ANTLR_VERSION	13320
#include "pcctscfg.h"
#include "pccts_stdio.h"
#include "tokens.h"

#include "p_types.hh"
#include "myAST.h"
#include "p_symtbl.hh"
#include "p_msgs.hh"
#include "p_error.hh"
#include "p_check.hh"
#include "p_ckbase.hh"
#include "p_tthred.hh"
#include "d_typdef.hh"
#include "u_desc.hh"
#include <stdio.h>
#define EXCEPTION_HANDLING
#define NUM_SIGNALS 3
#include "ASTBase.h"

#include "AParser.h"
#include "P.h"
#include "DLexerBase.h"
#include "ATokPtr.h"
#ifndef PURIFY
#define PURIFY(r,s) memset((char *) &(r),'\0',(s));
#endif

#include "sym.hh"

void P::
zzdflthandlers( int _signal, int *_retsignal )
{
	switch ( _signal ) {
	case NoSignal: break;  /* MR7 */
	default :
		tracein("default exception handler");
		*_retsignal = _signal;
		traceout("default exception handler");
		_signal=NoSignal;  /* MR7 */
		break;  /* MR7 */
	}
}


void
P::statement(ASTBase **_root,int *_retsignal)
{
	zzRULE;
	int _sva=1;
	ASTBase *_ast = NULL, *_sibling = NULL, *_tail = NULL;
	ANTLRTokenPtr _t12=NULL;
	AST *_ast12=NULL;
	ANTLRTokenPtr stmt=NULL, ustmt=NULL;
	AST *stmt_ast=NULL, *ustmt_ast=NULL;
	int _signal=NoSignal;
	*_retsignal = NoSignal;
	loop_clause_nest_level = 0;
	er->no_stmt_error();
	{
		AST *_ast21=NULL;
		for (;;) {
			if ( !((LA(1)==TOK_ACROSS || LA(1)==TOK_ANY || LA(1)==TOK_ASSIGNER || LA(1)==TOK_ASSIGN || 
LA(1)==TOK_BREAKTOKEN || LA(1)==TOK_BY || LA(1)==TOK_CLASS || LA(1)==TOK_CONTINUE || LA(1)==TOK_CONTROL || 
LA(1)==TOK_CREATE || LA(1)==TOK_CREATOR || LA(1)==TOK_DELETE || LA(1)==TOK_EACH || LA(1)==TOK_END || 
LA(1)==TOK_EVENT || LA(1)==TOK_FOR || LA(1)==TOK_FROM || LA(1)==TOK_GENERATE || LA(1)==TOK_IN || 
LA(1)==TOK_INSTANCES || LA(1)==TOK_INSTANCE || LA(1)==TOK_MANY || LA(1)==TOK_OBJECT || LA(1)==TOK_OF || 
LA(1)==TOK_ONE || LA(1)==TOK_RELATED || LA(1)==TOK_RELATE || LA(1)==TOK_SELECT || LA(1)==TOK_STOP || 
LA(1)==TOK_TO || LA(1)==TOK_WHERE || LA(1)==TOK_UNRELATE || LA(1)==TOK_USING || LA(1)==TOK_BRIDGE || 
LA(1)==TOK_CARDINALITY || LA(1)==TOK_EMPTY || LA(1)==TOK_FALSETOKEN || LA(1)==TOK_NOT || LA(1)==TOK_NOTEMPTY || 
LA(1)==TOK_TRANSFORM || LA(1)==TOK_TRUETOKEN || LA(1)==TOK_PARAM || LA(1)==TOK_RCVD_EVT || LA(1)==TOK_SELECTED || 
LA(1)==TOK_SELF || LA(1)==TOK_ELIF || LA(1)==TOK_ELSE || LA(1)==TOK_IF || LA(1)==TOK_RETURN || 
LA(1)==TOK_WHILE || LA(1)==TOK_DEBUG || LA(1)==TOK_DOUBLECOLON || LA(1)==TOK_SEMI || LA(1)==TOK_GENERAL_NAME || 
LA(1)==TOK_GARBAGE || LA(1)==TOK_BAD_ID || LA(1)==TOK_BAD_NAME || LA(1)==TOK_ID || LA(1)==TOK_RELID)
)) break;
			if ( (LA(1)==TOK_ACROSS || LA(1)==TOK_ANY || LA(1)==TOK_ASSIGNER || LA(1)==TOK_ASSIGN || 
LA(1)==TOK_BREAKTOKEN || LA(1)==TOK_BY || LA(1)==TOK_CLASS || LA(1)==TOK_CONTINUE || LA(1)==TOK_CONTROL || 
LA(1)==TOK_CREATE || LA(1)==TOK_CREATOR || LA(1)==TOK_DELETE || LA(1)==TOK_EACH || LA(1)==TOK_END || 
LA(1)==TOK_EVENT || LA(1)==TOK_FOR || LA(1)==TOK_FROM || LA(1)==TOK_GENERATE || LA(1)==TOK_IN || 
LA(1)==TOK_INSTANCES || LA(1)==TOK_INSTANCE || LA(1)==TOK_MANY || LA(1)==TOK_OBJECT || LA(1)==TOK_OF || 
LA(1)==TOK_ONE || LA(1)==TOK_RELATED || LA(1)==TOK_RELATE || LA(1)==TOK_SELECT || LA(1)==TOK_STOP || 
LA(1)==TOK_TO || LA(1)==TOK_WHERE || LA(1)==TOK_UNRELATE || LA(1)==TOK_USING || LA(1)==TOK_BRIDGE || 
LA(1)==TOK_CARDINALITY || LA(1)==TOK_EMPTY || LA(1)==TOK_FALSETOKEN || LA(1)==TOK_NOT || LA(1)==TOK_NOTEMPTY || 
LA(1)==TOK_TRANSFORM || LA(1)==TOK_TRUETOKEN || LA(1)==TOK_PARAM || LA(1)==TOK_RCVD_EVT || LA(1)==TOK_SELECTED || 
LA(1)==TOK_SELF || LA(1)==TOK_IF || LA(1)==TOK_RETURN || LA(1)==TOK_WHILE || LA(1)==TOK_DEBUG || 
LA(1)==TOK_DOUBLECOLON || LA(1)==TOK_SEMI || LA(1)==TOK_GENERAL_NAME || LA(1)==TOK_GARBAGE || LA(1)==TOK_BAD_ID || 
LA(1)==TOK_BAD_NAME || LA(1)==TOK_ID || LA(1)==TOK_RELID) && (LA(2)==Eof || 
LA(2)==TOK_ACROSS || LA(2)==TOK_ANY || LA(2)==TOK_ASSIGNER || LA(2)==TOK_ASSIGN || LA(2)==TOK_BREAKTOKEN || 
LA(2)==TOK_BY || LA(2)==TOK_CLASS || LA(2)==TOK_CONTINUE || LA(2)==TOK_CONTROL || LA(2)==TOK_CREATE || 
LA(2)==TOK_CREATOR || LA(2)==TOK_DELETE || LA(2)==TOK_EACH || LA(2)==TOK_END || LA(2)==TOK_EVENT || 
LA(2)==TOK_FOR || LA(2)==TOK_FROM || LA(2)==TOK_GENERATE || LA(2)==TOK_IN || LA(2)==TOK_INSTANCES || 
LA(2)==TOK_INSTANCE || LA(2)==TOK_MANY || LA(2)==TOK_OBJECT || LA(2)==TOK_OF || LA(2)==TOK_ONE || 
LA(2)==TOK_RELATED || LA(2)==TOK_RELATE || LA(2)==TOK_SELECT || LA(2)==TOK_STOP || LA(2)==TOK_TO || 
LA(2)==TOK_WHERE || LA(2)==TOK_UNRELATE || LA(2)==TOK_USING || LA(2)==TOK_BRIDGE || LA(2)==TOK_CARDINALITY || 
LA(2)==TOK_EMPTY || LA(2)==TOK_FALSETOKEN || LA(2)==TOK_NOT || LA(2)==TOK_NOTEMPTY || LA(2)==TOK_TRANSFORM || 
LA(2)==TOK_TRUETOKEN || LA(2)==TOK_PARAM || LA(2)==TOK_RCVD_EVT || LA(2)==TOK_SELECTED || LA(2)==TOK_SELF || 
LA(2)==TOK_AND || LA(2)==TOK_ELIF || LA(2)==TOK_ELSE || LA(2)==TOK_IF || LA(2)==TOK_OR || 
LA(2)==TOK_RETURN || LA(2)==TOK_WHILE || LA(2)==TOK_DEBUG || LA(2)==TOK_ON || LA(2)==TOK_OFF || 
LA(2)==TOK_TRACE || LA(2)==TOK_STAT || LA(2)==TOK_DUMP || LA(2)==TOK_SOR || LA(2)==TOK_DOT || 
LA(2)==TOK_DOUBLECOLON || LA(2)==TOK_EQUAL || LA(2)==TOK_LPAREN || LA(2)==TOK_MINUS || LA(2)==TOK_PLUS || 
LA(2)==TOK_SEMI || LA(2)==TOK_QMARK || LA(2)==TOK_QUOTE || LA(2)==TOK_FRACTION || LA(2)==TOK_GENERAL_NAME || 
LA(2)==TOK_GARBAGE || LA(2)==TOK_BAD_ID || LA(2)==TOK_BAD_NAME || LA(2)==TOK_ID || LA(2)==TOK_RELID || 
LA(2)==TOK_NUMBER) && !( LA(1)==TOK_END && ( LA(2)==TOK_FOR || LA(2)==TOK_IF || LA(2)==TOK_WHILE)) ) {
				_ast = NULL;
				valid_statement(&_ast,&_signal); if (_signal) goto _handler;
				_ast21 = (AST *)_ast;
				stmt_ast = _ast21;
				if ( !guessing ) {
				ASTBase::tmake( NULL, (*_root)->bottom(), stmt_ast , NULL);
				}
			}
			else {
				if ( (LA(1)==TOK_END || LA(1)==TOK_ELIF || LA(1)==TOK_ELSE) && (
LA(2)==Eof || LA(2)==TOK_ACROSS || LA(2)==TOK_ANY || LA(2)==TOK_ASSIGNER || LA(2)==TOK_ASSIGN || 
LA(2)==TOK_BREAKTOKEN || LA(2)==TOK_BY || LA(2)==TOK_CLASS || LA(2)==TOK_CONTINUE || LA(2)==TOK_CONTROL || 
LA(2)==TOK_CREATE || LA(2)==TOK_CREATOR || LA(2)==TOK_DELETE || LA(2)==TOK_EACH || LA(2)==TOK_END || 
LA(2)==TOK_EVENT || LA(2)==TOK_FOR || LA(2)==TOK_FROM || LA(2)==TOK_GENERATE || LA(2)==TOK_IN || 
LA(2)==TOK_INSTANCES || LA(2)==TOK_INSTANCE || LA(2)==TOK_MANY || LA(2)==TOK_OBJECT || LA(2)==TOK_OF || 
LA(2)==TOK_ONE || LA(2)==TOK_RELATED || LA(2)==TOK_RELATE || LA(2)==TOK_SELECT || LA(2)==TOK_STOP || 
LA(2)==TOK_TO || LA(2)==TOK_WHERE || LA(2)==TOK_UNRELATE || LA(2)==TOK_USING || LA(2)==TOK_BRIDGE || 
LA(2)==TOK_CARDINALITY || LA(2)==TOK_EMPTY || LA(2)==TOK_FALSETOKEN || LA(2)==TOK_NOT || LA(2)==TOK_NOTEMPTY || 
LA(2)==TOK_TRANSFORM || LA(2)==TOK_TRUETOKEN || LA(2)==TOK_PARAM || LA(2)==TOK_RCVD_EVT || LA(2)==TOK_SELECTED || 
LA(2)==TOK_SELF || LA(2)==TOK_ELIF || LA(2)==TOK_ELSE || LA(2)==TOK_IF || LA(2)==TOK_RETURN || 
LA(2)==TOK_WHILE || LA(2)==TOK_DEBUG || LA(2)==TOK_DOUBLECOLON || LA(2)==TOK_LPAREN || LA(2)==TOK_MINUS || 
LA(2)==TOK_PLUS || LA(2)==TOK_SEMI || LA(2)==TOK_QMARK || LA(2)==TOK_QUOTE || LA(2)==TOK_FRACTION || 
LA(2)==TOK_GENERAL_NAME || LA(2)==TOK_GARBAGE || LA(2)==TOK_BAD_ID || LA(2)==TOK_BAD_NAME || LA(2)==TOK_ID || 
LA(2)==TOK_RELID || LA(2)==TOK_NUMBER) ) {
					_ast = NULL;
					unmatched_statement(&_ast,&_signal); if (_signal) goto _handler;
					_ast21 = (AST *)_ast;
					ustmt_ast = _ast21;
					if ( !guessing ) {
					ASTBase::tmake( NULL, (*_root)->bottom(), ustmt_ast , NULL);
					}
				}
				else break; /* MR6 code for exiting loop "for sure" */
			}
		}
	}
	zzmatch_wsig(Eof, _handler);	
	if ( !guessing ) {
	 _t12 = (ANTLRTokenPtr)LT(1);
}
 labase++;
	 consume();
	return;
fail:
	if ( guessing ) zzGUESS_FAIL;
	syn(zzBadTok, "state actions", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd1, 0x1);
	return;
	/* exception handlers */
_handler:
	switch ( _signal ) {
	case NoSignal: break;  /* MR7 */
	default :
		tracein("statement exception handler");
		AST *c_ast = (new AST(LT(1)));
		// Prevent an endless loop here:
		if ( set_el(LA(1), TOK_RESYNCH_set) )
		{
			AL_PARSE_ERR1( c_ast, AL_GETMSG(ERR,300,1),
			c_ast->getVcharText() )
			labase++;
			consume();
		}
		else
		{
			if (LA(1) == TOK_MISSING_ASTSL )
			{
				// Missing trailing asterisk-slash on a comment
				AL_PARSE_ERR0( c_ast, AL_GETMSG(ERR,321,0) )
			}
			else
			{
				AL_PARSE_ERR1( c_ast, AL_GETMSG(ERR,300,1),
				c_ast->getVcharText() )
			}
			consumeUntil(TOK_RESYNCH_set);
			*_retsignal=NoSignal;
		}
		delete c_ast;
		traceout("statement exception handler");
		_signal=NoSignal;  /* MR7 */
		break;  /* MR7 */
	}
	return;
}

void
P::al_spec(ASTBase **_root,int *_retsignal, al_spec_type p_type, char *p_descr, void* p_return_type_reqd, const vchar* p_attribute_write_valid )
{
	zzRULE;
	int _sva=1;
	ASTBase *_ast = NULL, *_sibling = NULL, *_tail = NULL;
	ANTLRTokenPtr _t11=NULL;
	AST *_ast11=NULL;
	ANTLRTokenPtr e=NULL;
	AST *e_ast=NULL;
	int _signal=NoSignal;
	*_retsignal = NoSignal;
	
	spec_type =  p_type;
	spec_descr =  p_descr;
	return_type_reqd =  p_return_type_reqd;
	switch (spec_type)
	{
		case AL_SPEC_NONE_E:
		// should never get here
		// invoke an error and exit parser
		return;
		break;
		case AL_SPEC_STATE_ACTION_E:
		return_valid = FALSE;
		param_valid = FALSE;
		self_valid = TRUE;
		attribute_write_valid = 0;
		break;
		case AL_SPEC_ASSIGNER_E:
		return_valid = FALSE;
		param_valid = FALSE;
		self_valid = FALSE;
		attribute_write_valid = 0;
		break;
		case AL_SPEC_IB_ASSIGNER_E:
		return_valid = FALSE;
		param_valid = FALSE;
		self_valid = TRUE;
		attribute_write_valid = 0;
		break;
		case AL_SPEC_BRIDGE_E:
		return_valid = TRUE;
		param_valid = TRUE;
		self_valid = FALSE;
		attribute_write_valid = 0;
		break;
		case AL_SPEC_TRANSFORMER_E:
		return_valid = TRUE;
		param_valid = TRUE;
		self_valid = FALSE;
		attribute_write_valid = 0;
		break;
		case AL_SPEC_IB_TRANSFORMER_E:
		return_valid = TRUE;
		param_valid = TRUE;
		self_valid = TRUE;
		attribute_write_valid = 0;
		break;
		case AL_SPEC_SYNSVC_E:
		return_valid = TRUE;
		param_valid = TRUE;
		self_valid = FALSE;
		attribute_write_valid = 0;
		break;
		case AL_SPEC_ATTRIBUTE_E:
		return_valid = FALSE;
		param_valid = FALSE;
		self_valid = TRUE;
		attribute_write_valid = (vchar*)p_attribute_write_valid;
		break;
	}
	// Parse the AL with the parse_action function (not a rule)
	return_found = FALSE;
	attribute_write_found = FALSE;
	loop_clause_nest_level = 0;
	parse_action( &((*_root)), &_signal );
	zzmatch_wsig(Eof, _handler);	
	if ( !guessing ) {
	 _t11 = (ANTLRTokenPtr)LT(1);
}
 labase++;
	if ( !guessing ) {
	
	_ast11 = new AST(_t11);
	_ast11->subchild(_root, &_sibling, &_tail);
	}
	
	if ( !guessing ) {
		e = _t11;
	e_ast = _ast11;
	}
	
	if ( !guessing ) {
	if ( ! return_found && ! attribute_write_valid )
	{
		pck->verify_return_void( return_type_reqd, e_ast, spec_descr.char_ptr());
	}
	if ( attribute_write_valid && ! attribute_write_found )
	{
		AL_PARSE_ERR1( e_ast, AL_GETMSG(ERR,249,1), attribute_write_valid )
	}
	}
 consume();
	return;
fail:
	if ( guessing ) zzGUESS_FAIL;
	syn(zzBadTok, "AL specification", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd1, 0x2);
_handler:
	zzdflthandlers(_signal,_retsignal);
	return;
}

void
P::valid_statement(ASTBase **_root,int *_retsignal)
{
	zzRULE;
	int _sva=1;
	ASTBase *_ast = NULL, *_sibling = NULL, *_tail = NULL;
	ANTLRTokenPtr _t12=NULL;
	AST *_ast12=NULL;
	ANTLRTokenPtr iibt=NULL, ssvc=NULL, iasn=NULL, ibt=NULL, asgn=NULL, ctrl=NULL, brk=NULL, brdg=NULL, cont=NULL, crob=NULL, crte=NULL, del=NULL, fors=NULL, gen=NULL, ifst=NULL, rel=NULL, rtrn=NULL, sel=NULL, tran=NULL, whil=NULL, urel=NULL, dbug=NULL, emty=NULL, semi=NULL;
	AST *iibt_ast=NULL, *ssvc_ast=NULL, *iasn_ast=NULL, *ibt_ast=NULL, *asgn_ast=NULL, *ctrl_ast=NULL, *brk_ast=NULL, *brdg_ast=NULL, *cont_ast=NULL, *crob_ast=NULL, *crte_ast=NULL, *del_ast=NULL, *fors_ast=NULL, *gen_ast=NULL, *ifst_ast=NULL, *rel_ast=NULL, *rtrn_ast=NULL, *sel_ast=NULL, *tran_ast=NULL, *whil_ast=NULL, *urel_ast=NULL, *dbug_ast=NULL, *emty_ast=NULL, *semi_ast=NULL;
	int _signal=NoSignal;
	*_retsignal = NoSignal;
	AST *c_ast = NULL;
	er->no_stmt_error();
	bool adjust_seglength = TRUE;
	{
		AST *_ast21=NULL,*_ast22=NULL;
		zzGUESS_BLOCK
		zzGUESS
		if ( !zzrv && (LA(1)==TOK_ACROSS || LA(1)==TOK_ANY || LA(1)==TOK_ASSIGNER || 
LA(1)==TOK_ASSIGN || LA(1)==TOK_BREAKTOKEN || LA(1)==TOK_BY || LA(1)==TOK_CLASS || LA(1)==TOK_CONTINUE || 
LA(1)==TOK_CONTROL || LA(1)==TOK_CREATE || LA(1)==TOK_CREATOR || LA(1)==TOK_DELETE || LA(1)==TOK_EACH || 
LA(1)==TOK_END || LA(1)==TOK_EVENT || LA(1)==TOK_FOR || LA(1)==TOK_FROM || LA(1)==TOK_GENERATE || 
LA(1)==TOK_IN || LA(1)==TOK_INSTANCES || LA(1)==TOK_INSTANCE || LA(1)==TOK_MANY || LA(1)==TOK_OBJECT || 
LA(1)==TOK_OF || LA(1)==TOK_ONE || LA(1)==TOK_RELATED || LA(1)==TOK_RELATE || LA(1)==TOK_SELECT || 
LA(1)==TOK_STOP || LA(1)==TOK_TO || LA(1)==TOK_WHERE || LA(1)==TOK_UNRELATE || LA(1)==TOK_USING || 
LA(1)==TOK_SELECTED || LA(1)==TOK_SELF || LA(1)==TOK_GARBAGE || LA(1)==TOK_BAD_ID || LA(1)==TOK_BAD_NAME || 
LA(1)==TOK_ID || LA(1)==TOK_RELID) && (LA(2)==TOK_DOT) ) {
			{
				AST *_ast31=NULL;
				_ast = NULL;
				implicit_ib_transform_statement(&_ast,&_signal); if (_signal) goto _handler;
				if (!guessing) {    /* MR10 */
					if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
					_ast31 = (AST *)_ast;
					ASTBase::link(_root, &_sibling, &_tail);
				};    /* MR10 */
			}
			zzGUESS_DONE
			_ast = NULL;
			implicit_ib_transform_statement(&_ast,&_signal); if (_signal) goto _handler;
			if (!guessing) {    /* MR10 */
				if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
				_ast22 = (AST *)_ast;
				ASTBase::link(_root, &_sibling, &_tail);
			};    /* MR10 */
			iibt_ast = _ast22;
		}
		else {
			if ( !zzrv ) zzGUESS_DONE;
			zzGUESS
			if ( !zzrv && (LA(1)==TOK_DOUBLECOLON)
 ) {
				{
					AST *_ast31=NULL;
					_ast = NULL;
					synch_svc_statement(&_ast,&_signal); if (_signal) goto _handler;
					if (!guessing) {    /* MR10 */
						if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
						_ast31 = (AST *)_ast;
						ASTBase::link(_root, &_sibling, &_tail);
					};    /* MR10 */
				}
				zzGUESS_DONE
				_ast = NULL;
				synch_svc_statement(&_ast,&_signal); if (_signal) goto _handler;
				if (!guessing) {    /* MR10 */
					if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
					_ast22 = (AST *)_ast;
					ASTBase::link(_root, &_sibling, &_tail);
				};    /* MR10 */
				ssvc_ast = _ast22;
			}
			else {
				if ( !zzrv ) zzGUESS_DONE;
				if ( (LA(1)==TOK_ACROSS || LA(1)==TOK_ANY || LA(1)==TOK_ASSIGNER || LA(1)==TOK_ASSIGN || 
LA(1)==TOK_BREAKTOKEN || LA(1)==TOK_BY || LA(1)==TOK_CLASS || LA(1)==TOK_CONTINUE || LA(1)==TOK_CONTROL || 
LA(1)==TOK_CREATE || LA(1)==TOK_CREATOR || LA(1)==TOK_DELETE || LA(1)==TOK_EACH || LA(1)==TOK_END || 
LA(1)==TOK_EVENT || LA(1)==TOK_FOR || LA(1)==TOK_FROM || LA(1)==TOK_GENERATE || LA(1)==TOK_IN || 
LA(1)==TOK_INSTANCES || LA(1)==TOK_INSTANCE || LA(1)==TOK_MANY || LA(1)==TOK_OBJECT || LA(1)==TOK_OF || 
LA(1)==TOK_ONE || LA(1)==TOK_RELATED || LA(1)==TOK_RELATE || LA(1)==TOK_SELECT || LA(1)==TOK_STOP || 
LA(1)==TOK_TO || LA(1)==TOK_WHERE || LA(1)==TOK_UNRELATE || LA(1)==TOK_USING || LA(1)==TOK_PARAM || 
LA(1)==TOK_RCVD_EVT || LA(1)==TOK_SELECTED || LA(1)==TOK_SELF || LA(1)==TOK_GARBAGE || LA(1)==TOK_BAD_ID || 
LA(1)==TOK_BAD_NAME || LA(1)==TOK_ID || LA(1)==TOK_RELID) && (LA(2)==TOK_DOT || 
LA(2)==TOK_EQUAL) ) {
					_ast = NULL;
					implicit_assignment_statement(&_ast,&_signal); if (_signal) goto _handler;
					if (!guessing) {    /* MR10 */
						if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
						_ast21 = (AST *)_ast;
						ASTBase::link(_root, &_sibling, &_tail);
					};    /* MR10 */
					iasn_ast = _ast21;
				}
				else {
					if ( !zzrv ) zzGUESS_DONE;
					if ( (LA(1)==TOK_ACROSS || LA(1)==TOK_ANY || LA(1)==TOK_ASSIGNER || LA(1)==TOK_ASSIGN || 
LA(1)==TOK_BREAKTOKEN || LA(1)==TOK_BY || LA(1)==TOK_CLASS || LA(1)==TOK_CONTINUE || LA(1)==TOK_CONTROL || 
LA(1)==TOK_CREATE || LA(1)==TOK_CREATOR || LA(1)==TOK_DELETE || LA(1)==TOK_EACH || LA(1)==TOK_END || 
LA(1)==TOK_EVENT || LA(1)==TOK_FOR || LA(1)==TOK_FROM || LA(1)==TOK_GENERATE || LA(1)==TOK_IN || 
LA(1)==TOK_INSTANCES || LA(1)==TOK_INSTANCE || LA(1)==TOK_MANY || LA(1)==TOK_OBJECT || LA(1)==TOK_OF || 
LA(1)==TOK_ONE || LA(1)==TOK_RELATED || LA(1)==TOK_RELATE || LA(1)==TOK_SELECT || LA(1)==TOK_STOP || 
LA(1)==TOK_TO || LA(1)==TOK_WHERE || LA(1)==TOK_UNRELATE || LA(1)==TOK_USING || LA(1)==TOK_BRIDGE || 
LA(1)==TOK_CARDINALITY || LA(1)==TOK_EMPTY || LA(1)==TOK_FALSETOKEN || LA(1)==TOK_NOT || LA(1)==TOK_NOTEMPTY || 
LA(1)==TOK_TRANSFORM || LA(1)==TOK_TRUETOKEN || LA(1)==TOK_PARAM || LA(1)==TOK_RCVD_EVT || LA(1)==TOK_SELECTED || 
LA(1)==TOK_SELF || LA(1)==TOK_GENERAL_NAME || LA(1)==TOK_GARBAGE || LA(1)==TOK_BAD_ID || LA(1)==TOK_BAD_NAME || 
LA(1)==TOK_ID || LA(1)==TOK_RELID) && (LA(2)==TOK_DOUBLECOLON) ) {
						_ast = NULL;
						implicit_bridge_or_transform_statement(&_ast,&_signal); if (_signal) goto _handler;
						if (!guessing) {    /* MR10 */
							if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
							_ast21 = (AST *)_ast;
							ASTBase::link(_root, &_sibling, &_tail);
						};    /* MR10 */
						ibt_ast = _ast21;
					}
					else {
						if ( !zzrv ) zzGUESS_DONE;
						if ( (LA(1)==TOK_ASSIGN) && 
(LA(2)==TOK_ACROSS || LA(2)==TOK_ANY || LA(2)==TOK_ASSIGNER || LA(2)==TOK_ASSIGN || 
LA(2)==TOK_BREAKTOKEN || LA(2)==TOK_BY || LA(2)==TOK_CLASS || LA(2)==TOK_CONTINUE || LA(2)==TOK_CONTROL || 
LA(2)==TOK_CREATE || LA(2)==TOK_CREATOR || LA(2)==TOK_DELETE || LA(2)==TOK_EACH || LA(2)==TOK_END || 
LA(2)==TOK_EVENT || LA(2)==TOK_FOR || LA(2)==TOK_FROM || LA(2)==TOK_GENERATE || LA(2)==TOK_IN || 
LA(2)==TOK_INSTANCES || LA(2)==TOK_INSTANCE || LA(2)==TOK_MANY || LA(2)==TOK_OBJECT || LA(2)==TOK_OF || 
LA(2)==TOK_ONE || LA(2)==TOK_RELATED || LA(2)==TOK_RELATE || LA(2)==TOK_SELECT || LA(2)==TOK_STOP || 
LA(2)==TOK_TO || LA(2)==TOK_WHERE || LA(2)==TOK_UNRELATE || LA(2)==TOK_USING || LA(2)==TOK_PARAM || 
LA(2)==TOK_RCVD_EVT || LA(2)==TOK_SELECTED || LA(2)==TOK_SELF || LA(2)==TOK_GARBAGE || LA(2)==TOK_BAD_ID || 
LA(2)==TOK_BAD_NAME || LA(2)==TOK_ID || LA(2)==TOK_RELID) ) {
							_ast = NULL;
							assignment_statement(&_ast,&_signal); if (_signal) goto _handler;
							if (!guessing) {    /* MR10 */
								if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
								_ast21 = (AST *)_ast;
								ASTBase::link(_root, &_sibling, &_tail);
							};    /* MR10 */
							asgn_ast = _ast21;
						}
						else {
							if ( !zzrv ) zzGUESS_DONE;
							if ( (LA(1)==TOK_CONTROL) && (
LA(2)==TOK_STOP) ) {
								_ast = NULL;
								control_statement(&_ast,&_signal); if (_signal) goto _handler;
								if (!guessing) {    /* MR10 */
									if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
									_ast21 = (AST *)_ast;
									ASTBase::link(_root, &_sibling, &_tail);
								};    /* MR10 */
								ctrl_ast = _ast21;
							}
							else {
								if ( !zzrv ) zzGUESS_DONE;
								if ( (LA(1)==TOK_BREAKTOKEN) && (LA(2)==TOK_SEMI) ) {
									_ast = NULL;
									break_statement(&_ast,&_signal); if (_signal) goto _handler;
									if (!guessing) {    /* MR10 */
										if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
										_ast21 = (AST *)_ast;
										ASTBase::link(_root, &_sibling, &_tail);
									};    /* MR10 */
									brk_ast = _ast21;
									if ( !guessing ) {
									if ( ! loop_clause_nest_level )
									AL_PARSE_ERR0( brk_ast, AL_GETMSG(ERR,009,0) )
									}
								}
								else {
									if ( !zzrv ) zzGUESS_DONE;
									if ( (LA(1)==TOK_BRIDGE) && 
(LA(2)==TOK_ACROSS || LA(2)==TOK_ANY || LA(2)==TOK_ASSIGNER || LA(2)==TOK_ASSIGN || 
LA(2)==TOK_BREAKTOKEN || LA(2)==TOK_BY || LA(2)==TOK_CLASS || LA(2)==TOK_CONTINUE || LA(2)==TOK_CONTROL || 
LA(2)==TOK_CREATE || LA(2)==TOK_CREATOR || LA(2)==TOK_DELETE || LA(2)==TOK_EACH || LA(2)==TOK_END || 
LA(2)==TOK_EVENT || LA(2)==TOK_FOR || LA(2)==TOK_FROM || LA(2)==TOK_GENERATE || LA(2)==TOK_IN || 
LA(2)==TOK_INSTANCES || LA(2)==TOK_INSTANCE || LA(2)==TOK_MANY || LA(2)==TOK_OBJECT || LA(2)==TOK_OF || 
LA(2)==TOK_ONE || LA(2)==TOK_RELATED || LA(2)==TOK_RELATE || LA(2)==TOK_SELECT || LA(2)==TOK_STOP || 
LA(2)==TOK_TO || LA(2)==TOK_WHERE || LA(2)==TOK_UNRELATE || LA(2)==TOK_USING || LA(2)==TOK_BRIDGE || 
LA(2)==TOK_CARDINALITY || LA(2)==TOK_EMPTY || LA(2)==TOK_FALSETOKEN || LA(2)==TOK_NOT || LA(2)==TOK_NOTEMPTY || 
LA(2)==TOK_TRANSFORM || LA(2)==TOK_TRUETOKEN || LA(2)==TOK_PARAM || LA(2)==TOK_RCVD_EVT || LA(2)==TOK_SELECTED || 
LA(2)==TOK_SELF || LA(2)==TOK_GENERAL_NAME || LA(2)==TOK_GARBAGE || LA(2)==TOK_BAD_ID || LA(2)==TOK_BAD_NAME || 
LA(2)==TOK_ID || LA(2)==TOK_RELID) ) {
										_ast = NULL;
										bridge_statement(&_ast,&_signal); if (_signal) goto _handler;
										if (!guessing) {    /* MR10 */
											if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
											_ast21 = (AST *)_ast;
											ASTBase::link(_root, &_sibling, &_tail);
										};    /* MR10 */
										brdg_ast = _ast21;
									}
									else {
										if ( !zzrv ) zzGUESS_DONE;
										if ( (LA(1)==TOK_CONTINUE) && (LA(2)==TOK_SEMI) ) {
											_ast = NULL;
											continue_statement(&_ast,&_signal); if (_signal) goto _handler;
											if (!guessing) {    /* MR10 */
												if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
												_ast21 = (AST *)_ast;
												ASTBase::link(_root, &_sibling, &_tail);
											};    /* MR10 */
											cont_ast = _ast21;
											if ( !guessing ) {
											if ( ! loop_clause_nest_level )
											AL_PARSE_ERR0( cont_ast, AL_GETMSG(ERR,010,0) )
											}
										}
										else {
											if ( !zzrv ) zzGUESS_DONE;
											if ( (
LA(1)==TOK_CREATE) && (LA(2)==TOK_OBJECT) ) {
												_ast = NULL;
												create_object_statement(&_ast,&_signal); if (_signal) goto _handler;
												if (!guessing) {    /* MR10 */
													if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
													_ast21 = (AST *)_ast;
													ASTBase::link(_root, &_sibling, &_tail);
												};    /* MR10 */
												crob_ast = _ast21;
											}
											else {
												if ( !zzrv ) zzGUESS_DONE;
												if ( (LA(1)==TOK_CREATE) && (
LA(2)==TOK_EVENT) ) {
													_ast = NULL;
													create_event_statement(&_ast,&_signal); if (_signal) goto _handler;
													if (!guessing) {    /* MR10 */
														if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
														_ast21 = (AST *)_ast;
														ASTBase::link(_root, &_sibling, &_tail);
													};    /* MR10 */
													crte_ast = _ast21;
												}
												else {
													if ( !zzrv ) zzGUESS_DONE;
													if ( (LA(1)==TOK_DELETE) && (LA(2)==TOK_OBJECT) ) {
														_ast = NULL;
														delete_statement(&_ast,&_signal); if (_signal) goto _handler;
														if (!guessing) {    /* MR10 */
															if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
															_ast21 = (AST *)_ast;
															ASTBase::link(_root, &_sibling, &_tail);
														};    /* MR10 */
														del_ast = _ast21;
													}
													else {
														if ( !zzrv ) zzGUESS_DONE;
														if ( (LA(1)==TOK_FOR) && 
(LA(2)==TOK_EACH) ) {
															_ast = NULL;
															for_statement(&_ast,&_signal); if (_signal) goto _handler;
															if (!guessing) {    /* MR10 */
																if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
																_ast21 = (AST *)_ast;
																ASTBase::link(_root, &_sibling, &_tail);
															};    /* MR10 */
															fors_ast = _ast21;
															if ( !guessing ) {
															adjust_seglength = FALSE;
															}
														}
														else {
															if ( !zzrv ) zzGUESS_DONE;
															if ( (LA(1)==TOK_GENERATE) && (LA(2)==TOK_ACROSS || 
LA(2)==TOK_ANY || LA(2)==TOK_ASSIGNER || LA(2)==TOK_ASSIGN || LA(2)==TOK_BREAKTOKEN || LA(2)==TOK_BY || 
LA(2)==TOK_CLASS || LA(2)==TOK_CONTINUE || LA(2)==TOK_CONTROL || LA(2)==TOK_CREATE || LA(2)==TOK_CREATOR || 
LA(2)==TOK_DELETE || LA(2)==TOK_EACH || LA(2)==TOK_END || LA(2)==TOK_EVENT || LA(2)==TOK_FOR || 
LA(2)==TOK_FROM || LA(2)==TOK_GENERATE || LA(2)==TOK_IN || LA(2)==TOK_INSTANCES || LA(2)==TOK_INSTANCE || 
LA(2)==TOK_MANY || LA(2)==TOK_OBJECT || LA(2)==TOK_OF || LA(2)==TOK_ONE || LA(2)==TOK_RELATED || 
LA(2)==TOK_RELATE || LA(2)==TOK_SELECT || LA(2)==TOK_STOP || LA(2)==TOK_TO || LA(2)==TOK_WHERE || 
LA(2)==TOK_UNRELATE || LA(2)==TOK_USING || LA(2)==TOK_BRIDGE || LA(2)==TOK_CARDINALITY || LA(2)==TOK_EMPTY || 
LA(2)==TOK_FALSETOKEN || LA(2)==TOK_NOT || LA(2)==TOK_NOTEMPTY || LA(2)==TOK_TRANSFORM || LA(2)==TOK_TRUETOKEN || 
LA(2)==TOK_PARAM || LA(2)==TOK_RCVD_EVT || LA(2)==TOK_SELECTED || LA(2)==TOK_SELF || LA(2)==TOK_GENERAL_NAME || 
LA(2)==TOK_GARBAGE || LA(2)==TOK_BAD_ID || LA(2)==TOK_BAD_NAME || LA(2)==TOK_ID || LA(2)==TOK_RELID) ) {
																_ast = NULL;
																generate_statement(&_ast,&_signal); if (_signal) goto _handler;
																if (!guessing) {    /* MR10 */
																	if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
																	_ast21 = (AST *)_ast;
																	ASTBase::link(_root, &_sibling, &_tail);
																};    /* MR10 */
																gen_ast = _ast21;
															}
															else {
																if ( !zzrv ) zzGUESS_DONE;
																if ( (
LA(1)==TOK_IF) ) {
																	_ast = NULL;
																	if_statement(&_ast,&_signal); if (_signal) goto _handler;
																	if (!guessing) {    /* MR10 */
																		if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
																		_ast21 = (AST *)_ast;
																		ASTBase::link(_root, &_sibling, &_tail);
																	};    /* MR10 */
																	ifst_ast = _ast21;
																	if ( !guessing ) {
																	adjust_seglength = FALSE;
																	}
																}
																else {
																	if ( !zzrv ) zzGUESS_DONE;
																	if ( (LA(1)==TOK_RELATE) && (LA(2)==TOK_ACROSS || 
LA(2)==TOK_ANY || LA(2)==TOK_ASSIGNER || LA(2)==TOK_ASSIGN || LA(2)==TOK_BREAKTOKEN || LA(2)==TOK_BY || 
LA(2)==TOK_CLASS || LA(2)==TOK_CONTINUE || LA(2)==TOK_CONTROL || LA(2)==TOK_CREATE || LA(2)==TOK_CREATOR || 
LA(2)==TOK_DELETE || LA(2)==TOK_EACH || LA(2)==TOK_END || LA(2)==TOK_EVENT || LA(2)==TOK_FOR || 
LA(2)==TOK_FROM || LA(2)==TOK_GENERATE || LA(2)==TOK_IN || LA(2)==TOK_INSTANCES || LA(2)==TOK_INSTANCE || 
LA(2)==TOK_MANY || LA(2)==TOK_OBJECT || LA(2)==TOK_OF || LA(2)==TOK_ONE || LA(2)==TOK_RELATED || 
LA(2)==TOK_RELATE || LA(2)==TOK_SELECT || LA(2)==TOK_STOP || LA(2)==TOK_TO || LA(2)==TOK_WHERE || 
LA(2)==TOK_UNRELATE || LA(2)==TOK_USING || LA(2)==TOK_SELECTED || LA(2)==TOK_SELF || LA(2)==TOK_GARBAGE || 
LA(2)==TOK_BAD_ID || LA(2)==TOK_BAD_NAME || LA(2)==TOK_ID || LA(2)==TOK_RELID) ) {
																		_ast = NULL;
																		relate_statement(&_ast,&_signal); if (_signal) goto _handler;
																		if (!guessing) {    /* MR10 */
																			if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
																			_ast21 = (AST *)_ast;
																			ASTBase::link(_root, &_sibling, &_tail);
																		};    /* MR10 */
																		rel_ast = _ast21;
																	}
																	else {
																		if ( !zzrv ) zzGUESS_DONE;
																		if ( (LA(1)==TOK_RETURN)
 ) {
																			_ast = NULL;
																			return_statement(&_ast,&_signal); if (_signal) goto _handler;
																			if (!guessing) {    /* MR10 */
																				if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
																				_ast21 = (AST *)_ast;
																				ASTBase::link(_root, &_sibling, &_tail);
																			};    /* MR10 */
																			rtrn_ast = _ast21;
																		}
																		else {
																			if ( !zzrv ) zzGUESS_DONE;
																			if ( (LA(1)==TOK_SELECT) && (LA(2)==TOK_ANY || LA(2)==TOK_MANY || 
LA(2)==TOK_ONE) ) {
																				_ast = NULL;
																				select_statement(&_ast,&_signal); if (_signal) goto _handler;
																				if (!guessing) {    /* MR10 */
																					if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
																					_ast21 = (AST *)_ast;
																					ASTBase::link(_root, &_sibling, &_tail);
																				};    /* MR10 */
																				sel_ast = _ast21;
																			}
																			else {
																				if ( !zzrv ) zzGUESS_DONE;
																				if ( (LA(1)==TOK_TRANSFORM) && (LA(2)==TOK_ACROSS || LA(2)==TOK_ANY || 
LA(2)==TOK_ASSIGNER || LA(2)==TOK_ASSIGN || LA(2)==TOK_BREAKTOKEN || LA(2)==TOK_BY || LA(2)==TOK_CLASS || 
LA(2)==TOK_CONTINUE || LA(2)==TOK_CONTROL || LA(2)==TOK_CREATE || LA(2)==TOK_CREATOR || LA(2)==TOK_DELETE || 
LA(2)==TOK_EACH || LA(2)==TOK_END || LA(2)==TOK_EVENT || LA(2)==TOK_FOR || LA(2)==TOK_FROM || 
LA(2)==TOK_GENERATE || LA(2)==TOK_IN || LA(2)==TOK_INSTANCES || LA(2)==TOK_INSTANCE || LA(2)==TOK_MANY || 
LA(2)==TOK_OBJECT || LA(2)==TOK_OF || LA(2)==TOK_ONE || LA(2)==TOK_RELATED || LA(2)==TOK_RELATE || 
LA(2)==TOK_SELECT || LA(2)==TOK_STOP || LA(2)==TOK_TO || LA(2)==TOK_WHERE || LA(2)==TOK_UNRELATE || 
LA(2)==TOK_USING || LA(2)==TOK_BRIDGE || LA(2)==TOK_CARDINALITY || LA(2)==TOK_EMPTY || LA(2)==TOK_FALSETOKEN || 
LA(2)==TOK_NOT || LA(2)==TOK_NOTEMPTY || LA(2)==TOK_TRANSFORM || LA(2)==TOK_TRUETOKEN || LA(2)==TOK_PARAM || 
LA(2)==TOK_RCVD_EVT || LA(2)==TOK_SELECTED || LA(2)==TOK_SELF || LA(2)==TOK_GENERAL_NAME || LA(2)==TOK_GARBAGE || 
LA(2)==TOK_BAD_ID || LA(2)==TOK_BAD_NAME || LA(2)==TOK_ID || LA(2)==TOK_RELID) ) {
																					_ast = NULL;
																					transform_statement(&_ast,&_signal); if (_signal) goto _handler;
																					if (!guessing) {    /* MR10 */
																						if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
																						_ast21 = (AST *)_ast;
																						ASTBase::link(_root, &_sibling, &_tail);
																					};    /* MR10 */
																					tran_ast = _ast21;
																				}
																				else {
																					if ( !zzrv ) zzGUESS_DONE;
																					if ( (LA(1)==TOK_WHILE)
 ) {
																						_ast = NULL;
																						while_statement(&_ast,&_signal); if (_signal) goto _handler;
																						if (!guessing) {    /* MR10 */
																							if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
																							_ast21 = (AST *)_ast;
																							ASTBase::link(_root, &_sibling, &_tail);
																						};    /* MR10 */
																						whil_ast = _ast21;
																						if ( !guessing ) {
																						adjust_seglength = FALSE;
																						}
																					}
																					else {
																						if ( !zzrv ) zzGUESS_DONE;
																						if ( (LA(1)==TOK_UNRELATE) && (LA(2)==TOK_ACROSS || LA(2)==TOK_ANY || 
LA(2)==TOK_ASSIGNER || LA(2)==TOK_ASSIGN || LA(2)==TOK_BREAKTOKEN || LA(2)==TOK_BY || LA(2)==TOK_CLASS || 
LA(2)==TOK_CONTINUE || LA(2)==TOK_CONTROL || LA(2)==TOK_CREATE || LA(2)==TOK_CREATOR || LA(2)==TOK_DELETE || 
LA(2)==TOK_EACH || LA(2)==TOK_END || LA(2)==TOK_EVENT || LA(2)==TOK_FOR || LA(2)==TOK_FROM || 
LA(2)==TOK_GENERATE || LA(2)==TOK_IN || LA(2)==TOK_INSTANCES || LA(2)==TOK_INSTANCE || LA(2)==TOK_MANY || 
LA(2)==TOK_OBJECT || LA(2)==TOK_OF || LA(2)==TOK_ONE || LA(2)==TOK_RELATED || LA(2)==TOK_RELATE || 
LA(2)==TOK_SELECT || LA(2)==TOK_STOP || LA(2)==TOK_TO || LA(2)==TOK_WHERE || LA(2)==TOK_UNRELATE || 
LA(2)==TOK_USING || LA(2)==TOK_SELECTED || LA(2)==TOK_SELF || LA(2)==TOK_GARBAGE || LA(2)==TOK_BAD_ID || 
LA(2)==TOK_BAD_NAME || LA(2)==TOK_ID || LA(2)==TOK_RELID) ) {
																							_ast = NULL;
																							unrelate_statement(&_ast,&_signal); if (_signal) goto _handler;
																							if (!guessing) {    /* MR10 */
																								if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
																								_ast21 = (AST *)_ast;
																								ASTBase::link(_root, &_sibling, &_tail);
																							};    /* MR10 */
																							urel_ast = _ast21;
																						}
																						else {
																							if ( !zzrv ) zzGUESS_DONE;
																							if ( (LA(1)==TOK_DEBUG) ) {
																								_ast = NULL;
																								debug_statement(&_ast,&_signal); if (_signal) goto _handler;
																								if (!guessing) {    /* MR10 */
																									if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
																									_ast21 = (AST *)_ast;
																									ASTBase::link(_root, &_sibling, &_tail);
																								};    /* MR10 */
																								dbug_ast = _ast21;
																							}
																							else {
																								if ( !zzrv ) zzGUESS_DONE;
																								if ( (
LA(1)==TOK_SEMI) ) {
																									_ast = NULL;
																									empty_statement(&_ast,&_signal); if (_signal) goto _handler;
																									if (!guessing) {    /* MR10 */
																										if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
																										_ast21 = (AST *)_ast;
																										ASTBase::link(_root, &_sibling, &_tail);
																									};    /* MR10 */
																									emty_ast = _ast21;
																								}
																								else {
																									if ( guessing ) goto fail;
																									if (_sva) _signal=NoViableAlt;
																									else _signal=NoSemViableAlt;
																									goto _handler;  /* MR7 */
																								}
																							}
																						}
																					}
																				}
																			}
																		}
																	}
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	zzmatch_wsig(TOK_SEMI, _handler);	
	if ( !guessing ) {
	 _t12 = (ANTLRTokenPtr)LT(1);
}
 labase++;
	 
	if ( !guessing ) {
		semi = _t12;
	}
	
	if ( !guessing ) {
	AST *stmt;
	c_ast = (new AST( semi));
	long int semi_offset = c_ast->getOffset();
	delete c_ast;
	stmt = (AST *)*_root;
	if ( stmt )
	{
		long int stmt_offset = stmt->getOffset();
		if ( stmt_offset == -1 )
		stmt->setOffset(semi_offset);
		if (adjust_seglength)
		stmt->setSegLength(semi_offset + 1 - stmt_offset);
	}
	if ( dumpflag && (*_root) )
	{
		printf("--------------------------------------------------\n");
		((AST *)(*_root))->dumpTree("\nAST tree", ascii_buffer);
	}
	}
 consume();
	return;
fail:
	if ( guessing ) zzGUESS_FAIL;
	syn(zzBadTok, "action statement", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd1, 0x4);
_handler:
	zzdflthandlers(_signal,_retsignal);
	return;
}

void
P::if_clause_statement(ASTBase **_root,int *_retsignal)
{
	zzRULE;
	int _sva=1;
	ASTBase *_ast = NULL, *_sibling = NULL, *_tail = NULL;
;
	int _signal=NoSignal;
	*_retsignal = NoSignal;
	er->no_stmt_error();
	{
		AST *_ast21=NULL;
		if ( (LA(1)==TOK_ACROSS || LA(1)==TOK_ANY || LA(1)==TOK_ASSIGNER || 
LA(1)==TOK_ASSIGN || LA(1)==TOK_BREAKTOKEN || LA(1)==TOK_BY || LA(1)==TOK_CLASS || LA(1)==TOK_CONTINUE || 
LA(1)==TOK_CONTROL || LA(1)==TOK_CREATE || LA(1)==TOK_CREATOR || LA(1)==TOK_DELETE || LA(1)==TOK_EACH || 
LA(1)==TOK_END || LA(1)==TOK_EVENT || LA(1)==TOK_FOR || LA(1)==TOK_FROM || LA(1)==TOK_GENERATE || 
LA(1)==TOK_IN || LA(1)==TOK_INSTANCES || LA(1)==TOK_INSTANCE || LA(1)==TOK_MANY || LA(1)==TOK_OBJECT || 
LA(1)==TOK_OF || LA(1)==TOK_ONE || LA(1)==TOK_RELATED || LA(1)==TOK_RELATE || LA(1)==TOK_SELECT || 
LA(1)==TOK_STOP || LA(1)==TOK_TO || LA(1)==TOK_WHERE || LA(1)==TOK_UNRELATE || LA(1)==TOK_USING || 
LA(1)==TOK_BRIDGE || LA(1)==TOK_CARDINALITY || LA(1)==TOK_EMPTY || LA(1)==TOK_FALSETOKEN || LA(1)==TOK_NOT || 
LA(1)==TOK_NOTEMPTY || LA(1)==TOK_TRANSFORM || LA(1)==TOK_TRUETOKEN || LA(1)==TOK_PARAM || LA(1)==TOK_RCVD_EVT || 
LA(1)==TOK_SELECTED || LA(1)==TOK_SELF || LA(1)==TOK_IF || LA(1)==TOK_RETURN || LA(1)==TOK_WHILE || 
LA(1)==TOK_DEBUG || LA(1)==TOK_DOUBLECOLON || LA(1)==TOK_SEMI || LA(1)==TOK_GENERAL_NAME || LA(1)==TOK_GARBAGE || 
LA(1)==TOK_BAD_ID || LA(1)==TOK_BAD_NAME || LA(1)==TOK_ID || LA(1)==TOK_RELID) && (
LA(2)==Eof || LA(2)==TOK_ACROSS || LA(2)==TOK_ANY || LA(2)==TOK_ASSIGNER || LA(2)==TOK_ASSIGN || 
LA(2)==TOK_BREAKTOKEN || LA(2)==TOK_BY || LA(2)==TOK_CLASS || LA(2)==TOK_CONTINUE || LA(2)==TOK_CONTROL || 
LA(2)==TOK_CREATE || LA(2)==TOK_CREATOR || LA(2)==TOK_DELETE || LA(2)==TOK_EACH || LA(2)==TOK_END || 
LA(2)==TOK_EVENT || LA(2)==TOK_FOR || LA(2)==TOK_FROM || LA(2)==TOK_GENERATE || LA(2)==TOK_IN || 
LA(2)==TOK_INSTANCES || LA(2)==TOK_INSTANCE || LA(2)==TOK_MANY || LA(2)==TOK_OBJECT || LA(2)==TOK_OF || 
LA(2)==TOK_ONE || LA(2)==TOK_RELATED || LA(2)==TOK_RELATE || LA(2)==TOK_SELECT || LA(2)==TOK_STOP || 
LA(2)==TOK_TO || LA(2)==TOK_WHERE || LA(2)==TOK_UNRELATE || LA(2)==TOK_USING || LA(2)==TOK_BRIDGE || 
LA(2)==TOK_CARDINALITY || LA(2)==TOK_EMPTY || LA(2)==TOK_FALSETOKEN || LA(2)==TOK_NOT || LA(2)==TOK_NOTEMPTY || 
LA(2)==TOK_TRANSFORM || LA(2)==TOK_TRUETOKEN || LA(2)==TOK_PARAM || LA(2)==TOK_RCVD_EVT || LA(2)==TOK_SELECTED || 
LA(2)==TOK_SELF || LA(2)==TOK_AND || LA(2)==TOK_ELIF || LA(2)==TOK_ELSE || LA(2)==TOK_IF || 
LA(2)==TOK_OR || LA(2)==TOK_RETURN || LA(2)==TOK_WHILE || LA(2)==TOK_DEBUG || LA(2)==TOK_ON || 
LA(2)==TOK_OFF || LA(2)==TOK_TRACE || LA(2)==TOK_STAT || LA(2)==TOK_DUMP || LA(2)==TOK_SOR || 
LA(2)==TOK_DOT || LA(2)==TOK_DOUBLECOLON || LA(2)==TOK_EQUAL || LA(2)==TOK_LPAREN || LA(2)==TOK_MINUS || 
LA(2)==TOK_PLUS || LA(2)==TOK_SEMI || LA(2)==TOK_QMARK || LA(2)==TOK_QUOTE || LA(2)==TOK_FRACTION || 
LA(2)==TOK_GENERAL_NAME || LA(2)==TOK_GARBAGE || LA(2)==TOK_BAD_ID || LA(2)==TOK_BAD_NAME || LA(2)==TOK_ID || 
LA(2)==TOK_RELID || LA(2)==TOK_NUMBER) && !( LA(1)==TOK_END && ( LA(2)==TOK_FOR || LA(2)==TOK_WHILE)) ) {
			_ast = NULL;
			valid_statement(&_ast,&_signal); if (_signal) goto _handler;
			if (!guessing) {    /* MR10 */
				if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
				_ast21 = (AST *)_ast;
				ASTBase::link(_root, &_sibling, &_tail);
			};    /* MR10 */
		}
		else {
			if ( (LA(1)==TOK_END) && (LA(2)==TOK_FOR || 
LA(2)==TOK_WHILE) ) {
				_ast = NULL;
				unmatched_end_in_if_clause(&_ast,&_signal); if (_signal) goto _handler;
				if (!guessing) {    /* MR10 */
					if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
					_ast21 = (AST *)_ast;
					ASTBase::link(_root, &_sibling, &_tail);
				};    /* MR10 */
			}
			else {
				if ( guessing ) goto fail;
				if (_sva) _signal=NoViableAlt;
				else _signal=NoSemViableAlt;
				goto _handler;  /* MR7 */
			}
		}
	}
	return;
fail:
	if ( guessing ) zzGUESS_FAIL;
	syn(zzBadTok, "valid statement in if clause", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd1, 0x8);
_handler:
	zzdflthandlers(_signal,_retsignal);
	return;
}

void
P::for_clause_statement(ASTBase **_root,int *_retsignal)
{
	zzRULE;
	int _sva=1;
	ASTBase *_ast = NULL, *_sibling = NULL, *_tail = NULL;
;
	int _signal=NoSignal;
	*_retsignal = NoSignal;
	er->no_stmt_error();
	{
		AST *_ast21=NULL;
		if ( (LA(1)==TOK_ACROSS || LA(1)==TOK_ANY || LA(1)==TOK_ASSIGNER || LA(1)==TOK_ASSIGN || 
LA(1)==TOK_BREAKTOKEN || LA(1)==TOK_BY || LA(1)==TOK_CLASS || LA(1)==TOK_CONTINUE || LA(1)==TOK_CONTROL || 
LA(1)==TOK_CREATE || LA(1)==TOK_CREATOR || LA(1)==TOK_DELETE || LA(1)==TOK_EACH || LA(1)==TOK_END || 
LA(1)==TOK_EVENT || LA(1)==TOK_FOR || LA(1)==TOK_FROM || LA(1)==TOK_GENERATE || LA(1)==TOK_IN || 
LA(1)==TOK_INSTANCES || LA(1)==TOK_INSTANCE || LA(1)==TOK_MANY || LA(1)==TOK_OBJECT || LA(1)==TOK_OF || 
LA(1)==TOK_ONE || LA(1)==TOK_RELATED || LA(1)==TOK_RELATE || LA(1)==TOK_SELECT || LA(1)==TOK_STOP || 
LA(1)==TOK_TO || LA(1)==TOK_WHERE || LA(1)==TOK_UNRELATE || LA(1)==TOK_USING || LA(1)==TOK_BRIDGE || 
LA(1)==TOK_CARDINALITY || LA(1)==TOK_EMPTY || LA(1)==TOK_FALSETOKEN || LA(1)==TOK_NOT || LA(1)==TOK_NOTEMPTY || 
LA(1)==TOK_TRANSFORM || LA(1)==TOK_TRUETOKEN || LA(1)==TOK_PARAM || LA(1)==TOK_RCVD_EVT || LA(1)==TOK_SELECTED || 
LA(1)==TOK_SELF || LA(1)==TOK_IF || LA(1)==TOK_RETURN || LA(1)==TOK_WHILE || LA(1)==TOK_DEBUG || 
LA(1)==TOK_DOUBLECOLON || LA(1)==TOK_SEMI || LA(1)==TOK_GENERAL_NAME || LA(1)==TOK_GARBAGE || LA(1)==TOK_BAD_ID || 
LA(1)==TOK_BAD_NAME || LA(1)==TOK_ID || LA(1)==TOK_RELID) && (LA(2)==Eof || 
LA(2)==TOK_ACROSS || LA(2)==TOK_ANY || LA(2)==TOK_ASSIGNER || LA(2)==TOK_ASSIGN || LA(2)==TOK_BREAKTOKEN || 
LA(2)==TOK_BY || LA(2)==TOK_CLASS || LA(2)==TOK_CONTINUE || LA(2)==TOK_CONTROL || LA(2)==TOK_CREATE || 
LA(2)==TOK_CREATOR || LA(2)==TOK_DELETE || LA(2)==TOK_EACH || LA(2)==TOK_END || LA(2)==TOK_EVENT || 
LA(2)==TOK_FOR || LA(2)==TOK_FROM || LA(2)==TOK_GENERATE || LA(2)==TOK_IN || LA(2)==TOK_INSTANCES || 
LA(2)==TOK_INSTANCE || LA(2)==TOK_MANY || LA(2)==TOK_OBJECT || LA(2)==TOK_OF || LA(2)==TOK_ONE || 
LA(2)==TOK_RELATED || LA(2)==TOK_RELATE || LA(2)==TOK_SELECT || LA(2)==TOK_STOP || LA(2)==TOK_TO || 
LA(2)==TOK_WHERE || LA(2)==TOK_UNRELATE || LA(2)==TOK_USING || LA(2)==TOK_BRIDGE || LA(2)==TOK_CARDINALITY || 
LA(2)==TOK_EMPTY || LA(2)==TOK_FALSETOKEN || LA(2)==TOK_NOT || LA(2)==TOK_NOTEMPTY || LA(2)==TOK_TRANSFORM || 
LA(2)==TOK_TRUETOKEN || LA(2)==TOK_PARAM || LA(2)==TOK_RCVD_EVT || LA(2)==TOK_SELECTED || LA(2)==TOK_SELF || 
LA(2)==TOK_AND || LA(2)==TOK_ELIF || LA(2)==TOK_ELSE || LA(2)==TOK_IF || LA(2)==TOK_OR || 
LA(2)==TOK_RETURN || LA(2)==TOK_WHILE || LA(2)==TOK_DEBUG || LA(2)==TOK_ON || LA(2)==TOK_OFF || 
LA(2)==TOK_TRACE || LA(2)==TOK_STAT || LA(2)==TOK_DUMP || LA(2)==TOK_SOR || LA(2)==TOK_DOT || 
LA(2)==TOK_DOUBLECOLON || LA(2)==TOK_EQUAL || LA(2)==TOK_LPAREN || LA(2)==TOK_MINUS || LA(2)==TOK_PLUS || 
LA(2)==TOK_SEMI || LA(2)==TOK_QMARK || LA(2)==TOK_QUOTE || LA(2)==TOK_FRACTION || LA(2)==TOK_GENERAL_NAME || 
LA(2)==TOK_GARBAGE || LA(2)==TOK_BAD_ID || LA(2)==TOK_BAD_NAME || LA(2)==TOK_ID || LA(2)==TOK_RELID || 
LA(2)==TOK_NUMBER) && !( LA(1)==TOK_END && ( LA(2)==TOK_IF || LA(2)==TOK_WHILE)) ) {
			_ast = NULL;
			valid_statement(&_ast,&_signal); if (_signal) goto _handler;
			if (!guessing) {    /* MR10 */
				if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
				_ast21 = (AST *)_ast;
				ASTBase::link(_root, &_sibling, &_tail);
			};    /* MR10 */
		}
		else {
			if ( (LA(1)==TOK_END) && (LA(2)==TOK_IF || LA(2)==TOK_WHILE) ) {
				_ast = NULL;
				unmatched_end_in_for_clause(&_ast,&_signal); if (_signal) goto _handler;
				if (!guessing) {    /* MR10 */
					if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
					_ast21 = (AST *)_ast;
					ASTBase::link(_root, &_sibling, &_tail);
				};    /* MR10 */
			}
			else {
				if ( guessing ) goto fail;
				if (_sva) _signal=NoViableAlt;
				else _signal=NoSemViableAlt;
				goto _handler;  /* MR7 */
			}
		}
	}
	return;
fail:
	if ( guessing ) zzGUESS_FAIL;
	syn(zzBadTok, "valid statement in for each clause", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd1, 0x10);
_handler:
	zzdflthandlers(_signal,_retsignal);
	return;
}

void
P::while_clause_statement(ASTBase **_root,int *_retsignal)
{
	zzRULE;
	int _sva=1;
	ASTBase *_ast = NULL, *_sibling = NULL, *_tail = NULL;
;
	int _signal=NoSignal;
	*_retsignal = NoSignal;
	er->no_stmt_error();
	{
		AST *_ast21=NULL;
		if ( (
LA(1)==TOK_ACROSS || LA(1)==TOK_ANY || LA(1)==TOK_ASSIGNER || LA(1)==TOK_ASSIGN || LA(1)==TOK_BREAKTOKEN || 
LA(1)==TOK_BY || LA(1)==TOK_CLASS || LA(1)==TOK_CONTINUE || LA(1)==TOK_CONTROL || LA(1)==TOK_CREATE || 
LA(1)==TOK_CREATOR || LA(1)==TOK_DELETE || LA(1)==TOK_EACH || LA(1)==TOK_END || LA(1)==TOK_EVENT || 
LA(1)==TOK_FOR || LA(1)==TOK_FROM || LA(1)==TOK_GENERATE || LA(1)==TOK_IN || LA(1)==TOK_INSTANCES || 
LA(1)==TOK_INSTANCE || LA(1)==TOK_MANY || LA(1)==TOK_OBJECT || LA(1)==TOK_OF || LA(1)==TOK_ONE || 
LA(1)==TOK_RELATED || LA(1)==TOK_RELATE || LA(1)==TOK_SELECT || LA(1)==TOK_STOP || LA(1)==TOK_TO || 
LA(1)==TOK_WHERE || LA(1)==TOK_UNRELATE || LA(1)==TOK_USING || LA(1)==TOK_BRIDGE || LA(1)==TOK_CARDINALITY || 
LA(1)==TOK_EMPTY || LA(1)==TOK_FALSETOKEN || LA(1)==TOK_NOT || LA(1)==TOK_NOTEMPTY || LA(1)==TOK_TRANSFORM || 
LA(1)==TOK_TRUETOKEN || LA(1)==TOK_PARAM || LA(1)==TOK_RCVD_EVT || LA(1)==TOK_SELECTED || LA(1)==TOK_SELF || 
LA(1)==TOK_IF || LA(1)==TOK_RETURN || LA(1)==TOK_WHILE || LA(1)==TOK_DEBUG || LA(1)==TOK_DOUBLECOLON || 
LA(1)==TOK_SEMI || LA(1)==TOK_GENERAL_NAME || LA(1)==TOK_GARBAGE || LA(1)==TOK_BAD_ID || LA(1)==TOK_BAD_NAME || 
LA(1)==TOK_ID || LA(1)==TOK_RELID) && (LA(2)==Eof || LA(2)==TOK_ACROSS || 
LA(2)==TOK_ANY || LA(2)==TOK_ASSIGNER || LA(2)==TOK_ASSIGN || LA(2)==TOK_BREAKTOKEN || LA(2)==TOK_BY || 
LA(2)==TOK_CLASS || LA(2)==TOK_CONTINUE || LA(2)==TOK_CONTROL || LA(2)==TOK_CREATE || LA(2)==TOK_CREATOR || 
LA(2)==TOK_DELETE || LA(2)==TOK_EACH || LA(2)==TOK_END || LA(2)==TOK_EVENT || LA(2)==TOK_FOR || 
LA(2)==TOK_FROM || LA(2)==TOK_GENERATE || LA(2)==TOK_IN || LA(2)==TOK_INSTANCES || LA(2)==TOK_INSTANCE || 
LA(2)==TOK_MANY || LA(2)==TOK_OBJECT || LA(2)==TOK_OF || LA(2)==TOK_ONE || LA(2)==TOK_RELATED || 
LA(2)==TOK_RELATE || LA(2)==TOK_SELECT || LA(2)==TOK_STOP || LA(2)==TOK_TO || LA(2)==TOK_WHERE || 
LA(2)==TOK_UNRELATE || LA(2)==TOK_USING || LA(2)==TOK_BRIDGE || LA(2)==TOK_CARDINALITY || LA(2)==TOK_EMPTY || 
LA(2)==TOK_FALSETOKEN || LA(2)==TOK_NOT || LA(2)==TOK_NOTEMPTY || LA(2)==TOK_TRANSFORM || LA(2)==TOK_TRUETOKEN || 
LA(2)==TOK_PARAM || LA(2)==TOK_RCVD_EVT || LA(2)==TOK_SELECTED || LA(2)==TOK_SELF || LA(2)==TOK_AND || 
LA(2)==TOK_ELIF || LA(2)==TOK_ELSE || LA(2)==TOK_IF || LA(2)==TOK_OR || LA(2)==TOK_RETURN || 
LA(2)==TOK_WHILE || LA(2)==TOK_DEBUG || LA(2)==TOK_ON || LA(2)==TOK_OFF || LA(2)==TOK_TRACE || 
LA(2)==TOK_STAT || LA(2)==TOK_DUMP || LA(2)==TOK_SOR || LA(2)==TOK_DOT || LA(2)==TOK_DOUBLECOLON || 
LA(2)==TOK_EQUAL || LA(2)==TOK_LPAREN || LA(2)==TOK_MINUS || LA(2)==TOK_PLUS || LA(2)==TOK_SEMI || 
LA(2)==TOK_QMARK || LA(2)==TOK_QUOTE || LA(2)==TOK_FRACTION || LA(2)==TOK_GENERAL_NAME || LA(2)==TOK_GARBAGE || 
LA(2)==TOK_BAD_ID || LA(2)==TOK_BAD_NAME || LA(2)==TOK_ID || LA(2)==TOK_RELID || LA(2)==TOK_NUMBER) && !( LA(1)==TOK_END && ( LA(2)==TOK_FOR || LA(2)==TOK_IF)) ) {
			_ast = NULL;
			valid_statement(&_ast,&_signal); if (_signal) goto _handler;
			if (!guessing) {    /* MR10 */
				if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
				_ast21 = (AST *)_ast;
				ASTBase::link(_root, &_sibling, &_tail);
			};    /* MR10 */
		}
		else {
			if ( (
LA(1)==TOK_END) && (LA(2)==TOK_FOR || LA(2)==TOK_IF) ) {
				_ast = NULL;
				unmatched_end_in_while_clause(&_ast,&_signal); if (_signal) goto _handler;
				if (!guessing) {    /* MR10 */
					if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
					_ast21 = (AST *)_ast;
					ASTBase::link(_root, &_sibling, &_tail);
				};    /* MR10 */
			}
			else {
				if ( guessing ) goto fail;
				if (_sva) _signal=NoViableAlt;
				else _signal=NoSemViableAlt;
				goto _handler;  /* MR7 */
			}
		}
	}
	return;
fail:
	if ( guessing ) zzGUESS_FAIL;
	syn(zzBadTok, "valid statement in while clause", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd1, 0x20);
_handler:
	zzdflthandlers(_signal,_retsignal);
	return;
}

void
P::unmatched_statement(ASTBase **_root,int *_retsignal)
{
	zzRULE;
	int _sva=1;
	ASTBase *_ast = NULL, *_sibling = NULL, *_tail = NULL;
;
	ANTLRTokenPtr uels=NULL, ueli=NULL, uend=NULL;
	AST *uels_ast=NULL, *ueli_ast=NULL, *uend_ast=NULL;
	int _signal=NoSignal;
	*_retsignal = NoSignal;
	er->no_stmt_error();
	{
		AST *_ast21=NULL;
		if ( (LA(1)==TOK_ELSE)
 ) {
			_ast = NULL;
			unmatched_else_statement(&_ast,&_signal); if (_signal) goto _handler;
			if (!guessing) {    /* MR10 */
				if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
				_ast21 = (AST *)_ast;
				ASTBase::link(_root, &_sibling, &_tail);
			};    /* MR10 */
			uels_ast = _ast21;
		}
		else {
			if ( (LA(1)==TOK_ELIF) ) {
				_ast = NULL;
				unmatched_elif_statement(&_ast,&_signal); if (_signal) goto _handler;
				if (!guessing) {    /* MR10 */
					if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
					_ast21 = (AST *)_ast;
					ASTBase::link(_root, &_sibling, &_tail);
				};    /* MR10 */
				ueli_ast = _ast21;
			}
			else {
				if ( (LA(1)==TOK_END) ) {
					_ast = NULL;
					unmatched_end_statement(&_ast,&_signal); if (_signal) goto _handler;
					if (!guessing) {    /* MR10 */
						if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
						_ast21 = (AST *)_ast;
						ASTBase::link(_root, &_sibling, &_tail);
					};    /* MR10 */
					uend_ast = _ast21;
				}
				else {
					if ( guessing ) goto fail;
					if (_sva) _signal=NoViableAlt;
					else _signal=NoSemViableAlt;
					goto _handler;  /* MR7 */
				}
			}
		}
	}
	return;
fail:
	if ( guessing ) zzGUESS_FAIL;
	syn(zzBadTok, "invalid statement", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd1, 0x40);
_handler:
	zzdflthandlers(_signal,_retsignal);
	return;
}

void
P::assignment_statement(ASTBase **_root,int *_retsignal)
{
	zzRULE;
	int _sva=1;
	ASTBase *_ast = NULL, *_sibling = NULL, *_tail = NULL;
	ANTLRTokenPtr _t11=NULL;
	AST *_ast11=NULL,*_ast12=NULL;
	ANTLRTokenPtr ta=NULL, ae=NULL;
	AST *ta_ast=NULL, *ae_ast=NULL;
	int _signal=NoSignal;
	*_retsignal = NoSignal;
	t_core_data_type t1;
	AST *c_ast = NULL;
	zzmatch_wsig(TOK_ASSIGN, _handler);	
	if ( !guessing ) {
	 _t11 = (ANTLRTokenPtr)LT(1);
}
 labase++;
	
	if ( !guessing ) {
		ta = _t11;
	}
	 consume();
	_ast = NULL;
	if ( !guessing ) {
		 t1  = assignment_expr(&_ast,&_signal); if (_signal) goto _handler;
		_ast12 = (AST *)_ast;
		ae_ast = _ast12;
	} else {
		assignment_expr(&_ast,&_signal);
	}
	if ( !guessing ) {
	
	c_ast = (new AST( ta, TOK_STMT_ASSIGN));
	(*_root) = ASTBase::tmake( c_ast, ae_ast , NULL);
	}
	return;
fail:
	if ( guessing ) zzGUESS_FAIL;
	syn(zzBadTok, "assignment statement", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd1, 0x80);
_handler:
	zzdflthandlers(_signal,_retsignal);
	return;
}

void
P::break_statement(ASTBase **_root,int *_retsignal)
{
	zzRULE;
	int _sva=1;
	ASTBase *_ast = NULL, *_sibling = NULL, *_tail = NULL;
	ANTLRTokenPtr _t11=NULL;
	AST *_ast11=NULL;
	ANTLRTokenPtr brk=NULL;
	AST *brk_ast=NULL;
	int _signal=NoSignal;
	*_retsignal = NoSignal;
	zzmatch_wsig(TOK_BREAKTOKEN, _handler);	
	if ( !guessing ) {
	 _t11 = (ANTLRTokenPtr)LT(1);
}
 labase++;
	if ( !guessing ) {
	
	_ast11 = new AST(_t11);
	_ast11->subchild(_root, &_sibling, &_tail);
	}
	
	if ( !guessing ) {
		brk = _t11;
	brk_ast = _ast11;
	}
	
	if ( !guessing ) {
	brk_ast->setType(TOK_STMT_BREAK);
	}
 consume();
	return;
fail:
	if ( guessing ) zzGUESS_FAIL;
	syn(zzBadTok, "break statement", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd2, 0x1);
_handler:
	zzdflthandlers(_signal,_retsignal);
	return;
}

void
P::bridge_statement(ASTBase **_root,int *_retsignal)
{
	zzRULE;
	int _sva=1;
	ASTBase *_ast = NULL, *_sibling = NULL, *_tail = NULL;
	ANTLRTokenPtr _t11=NULL;
	AST *_ast11=NULL,*_ast13=NULL;
	ANTLRTokenPtr tb=NULL, lv=NULL, aa=NULL, br=NULL;
	AST *tb_ast=NULL, *lv_ast=NULL, *aa_ast=NULL, *br_ast=NULL;
	int _signal=NoSignal;
	*_retsignal = NoSignal;
	t_core_data_type t1;
	t_core_data_type t2;
	bool requiresReturnValue = FALSE;
	AST *c_ast;
	AST *b_ast;
	zzmatch_wsig(TOK_BRIDGE, _handler);	
	if ( !guessing ) {
	 _t11 = (ANTLRTokenPtr)LT(1);
}
 labase++;
	
	if ( !guessing ) {
		tb = _t11;
	}
	 consume();
	{
		ANTLRTokenPtr _t22=NULL;
		AST *_ast22=NULL;
		if ( (
LA(1)==TOK_ACROSS || LA(1)==TOK_ANY || LA(1)==TOK_ASSIGNER || LA(1)==TOK_ASSIGN || LA(1)==TOK_BREAKTOKEN || 
LA(1)==TOK_BY || LA(1)==TOK_CLASS || LA(1)==TOK_CONTINUE || LA(1)==TOK_CONTROL || LA(1)==TOK_CREATE || 
LA(1)==TOK_CREATOR || LA(1)==TOK_DELETE || LA(1)==TOK_EACH || LA(1)==TOK_END || LA(1)==TOK_EVENT || 
LA(1)==TOK_FOR || LA(1)==TOK_FROM || LA(1)==TOK_GENERATE || LA(1)==TOK_IN || LA(1)==TOK_INSTANCES || 
LA(1)==TOK_INSTANCE || LA(1)==TOK_MANY || LA(1)==TOK_OBJECT || LA(1)==TOK_OF || LA(1)==TOK_ONE || 
LA(1)==TOK_RELATED || LA(1)==TOK_RELATE || LA(1)==TOK_SELECT || LA(1)==TOK_STOP || LA(1)==TOK_TO || 
LA(1)==TOK_WHERE || LA(1)==TOK_UNRELATE || LA(1)==TOK_USING || LA(1)==TOK_SELECTED || LA(1)==TOK_SELF || 
LA(1)==TOK_GARBAGE || LA(1)==TOK_BAD_ID || LA(1)==TOK_BAD_NAME || LA(1)==TOK_ID || LA(1)==TOK_RELID) && 
(LA(2)==TOK_DOT || LA(2)==TOK_EQUAL) ) {
			{
				AST *_ast31=NULL;
				if ( (LA(1)==TOK_ACROSS || LA(1)==TOK_ANY || 
LA(1)==TOK_ASSIGNER || LA(1)==TOK_ASSIGN || LA(1)==TOK_BREAKTOKEN || LA(1)==TOK_BY || LA(1)==TOK_CLASS || 
LA(1)==TOK_CONTINUE || LA(1)==TOK_CONTROL || LA(1)==TOK_CREATE || LA(1)==TOK_CREATOR || LA(1)==TOK_DELETE || 
LA(1)==TOK_EACH || LA(1)==TOK_END || LA(1)==TOK_EVENT || LA(1)==TOK_FOR || LA(1)==TOK_FROM || 
LA(1)==TOK_GENERATE || LA(1)==TOK_IN || LA(1)==TOK_INSTANCES || LA(1)==TOK_INSTANCE || LA(1)==TOK_MANY || 
LA(1)==TOK_OBJECT || LA(1)==TOK_OF || LA(1)==TOK_ONE || LA(1)==TOK_RELATED || LA(1)==TOK_RELATE || 
LA(1)==TOK_SELECT || LA(1)==TOK_STOP || LA(1)==TOK_TO || LA(1)==TOK_WHERE || LA(1)==TOK_UNRELATE || 
LA(1)==TOK_USING || LA(1)==TOK_SELECTED || LA(1)==TOK_SELF || LA(1)==TOK_GARBAGE || LA(1)==TOK_BAD_ID || 
LA(1)==TOK_BAD_NAME || LA(1)==TOK_ID || LA(1)==TOK_RELID) && (LA(2)==TOK_EQUAL) ) {
					_ast = NULL;
					local_variable(&_ast,&_signal, ASSIGN_LVAL ); if (_signal) goto _handler;
					_ast31 = (AST *)_ast;
					lv_ast = _ast31;
				}
				else {
					if ( (
LA(1)==TOK_ACROSS || LA(1)==TOK_ANY || LA(1)==TOK_ASSIGNER || LA(1)==TOK_ASSIGN || LA(1)==TOK_BREAKTOKEN || 
LA(1)==TOK_BY || LA(1)==TOK_CLASS || LA(1)==TOK_CONTINUE || LA(1)==TOK_CONTROL || LA(1)==TOK_CREATE || 
LA(1)==TOK_CREATOR || LA(1)==TOK_DELETE || LA(1)==TOK_EACH || LA(1)==TOK_END || LA(1)==TOK_EVENT || 
LA(1)==TOK_FOR || LA(1)==TOK_FROM || LA(1)==TOK_GENERATE || LA(1)==TOK_IN || LA(1)==TOK_INSTANCES || 
LA(1)==TOK_INSTANCE || LA(1)==TOK_MANY || LA(1)==TOK_OBJECT || LA(1)==TOK_OF || LA(1)==TOK_ONE || 
LA(1)==TOK_RELATED || LA(1)==TOK_RELATE || LA(1)==TOK_SELECT || LA(1)==TOK_STOP || LA(1)==TOK_TO || 
LA(1)==TOK_WHERE || LA(1)==TOK_UNRELATE || LA(1)==TOK_USING || LA(1)==TOK_SELECTED || LA(1)==TOK_SELF || 
LA(1)==TOK_GARBAGE || LA(1)==TOK_BAD_ID || LA(1)==TOK_BAD_NAME || LA(1)==TOK_ID || LA(1)==TOK_RELID) && 
(LA(2)==TOK_DOT) ) {
						_ast = NULL;
						if ( !guessing ) {
							 t1  = attribute_access(&_ast,&_signal, ASSIGN_LVAL ); if (_signal) goto _handler;
							_ast31 = (AST *)_ast;
							aa_ast = _ast31;
						} else {
							attribute_access(&_ast,&_signal, ASSIGN_LVAL );
						}
					}
					else {
						if ( guessing ) goto fail;
						if (_sva) _signal=NoViableAlt;
						else _signal=NoSemViableAlt;
						goto _handler;  /* MR7 */
					}
				}
			}
			zzmatch_wsig(TOK_EQUAL, _handler);			
			if ( !guessing ) {
			 _t22 = (ANTLRTokenPtr)LT(1);
}
 labase++;
			
			if ( !guessing ) {
			requiresReturnValue = TRUE;
			}
 consume();
		}
	}
	_ast = NULL;
	if ( !guessing ) {
		 t2  = bridge_invocation(&_ast,&_signal, requiresReturnValue ); if (_signal) goto _handler;
		_ast13 = (AST *)_ast;
		br_ast = _ast13;
	} else {
		bridge_invocation(&_ast,&_signal, requiresReturnValue );
	}
	if ( !guessing ) {
	if ( lv_ast )
	{
		c_ast = (new AST( tb, TOK_STMT_ASSIGN));
		st->newadd( lv_ast, t2, br_ast );
		b_ast = (new AST(TOK_EXPRESSION, br_ast));  // sets datatype and offset
		b_ast->setSegLength(br_ast->getSegLength());
		(*_root) = ASTBase::tmake( c_ast, lv_ast, ASTBase::tmake( b_ast, br_ast, NULL) , NULL);
	}
	else if (aa_ast)
	{
		bool mismatch = FALSE;
		if ( accum_datatype( aa_ast, br_ast, t1, t2, mismatch ) )
		AL_PARSE_ERR0( aa_ast, AL_GETMSG(ERR,274,0) )
		c_ast = (new AST( tb, TOK_STMT_ASSIGN));
		b_ast = (new AST(TOK_EXPRESSION, br_ast));  // sets datatype and offset
		b_ast->setSegLength(br_ast->getSegLength());
		(*_root) = ASTBase::tmake( c_ast, aa_ast, ASTBase::tmake( b_ast, br_ast, NULL) , NULL);
	}
	else
	{
		c_ast = (new AST( tb, TOK_STMT_BRIDGE));
		(*_root) = ASTBase::tmake( c_ast, br_ast , NULL);
	}
	}
	return;
fail:
	if ( guessing ) zzGUESS_FAIL;
	syn(zzBadTok, "bridge statement", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd2, 0x2);
_handler:
	zzdflthandlers(_signal,_retsignal);
	return;
}

void
P::control_statement(ASTBase **_root,int *_retsignal)
{
	zzRULE;
	int _sva=1;
	ASTBase *_ast = NULL, *_sibling = NULL, *_tail = NULL;
	ANTLRTokenPtr _t11=NULL,_t12=NULL;
	AST *_ast11=NULL,*_ast12=NULL;
	ANTLRTokenPtr ctrl=NULL;
	AST *ctrl_ast=NULL;
	int _signal=NoSignal;
	*_retsignal = NoSignal;
	zzmatch_wsig(TOK_CONTROL, _handler);	
	if ( !guessing ) {
	 _t11 = (ANTLRTokenPtr)LT(1);
}
 labase++;
	if ( !guessing ) {
	
	_ast11 = new AST(_t11);
	_ast11->subroot(_root, &_sibling, &_tail);
	}
	
	if ( !guessing ) {
		ctrl = _t11;
	ctrl_ast = _ast11;
	}
	
	if ( !guessing ) {
	ctrl_ast->setType(TOK_STMT_CONTROL);
	}
 consume();
	zzmatch_wsig(TOK_STOP, _handler);	
	if ( !guessing ) {
	 _t12 = (ANTLRTokenPtr)LT(1);
}
 labase++;
	if ( !guessing ) {
	
	_ast12 = new AST(_t12);
	_ast12->subchild(_root, &_sibling, &_tail);
	}
	 consume();
	return;
fail:
	if ( guessing ) zzGUESS_FAIL;
	syn(zzBadTok, "control statement", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd2, 0x4);
_handler:
	zzdflthandlers(_signal,_retsignal);
	return;
}

void
P::continue_statement(ASTBase **_root,int *_retsignal)
{
	zzRULE;
	int _sva=1;
	ASTBase *_ast = NULL, *_sibling = NULL, *_tail = NULL;
	ANTLRTokenPtr _t11=NULL;
	AST *_ast11=NULL;
	ANTLRTokenPtr cont=NULL;
	AST *cont_ast=NULL;
	int _signal=NoSignal;
	*_retsignal = NoSignal;
	zzmatch_wsig(TOK_CONTINUE, _handler);	
	if ( !guessing ) {
	 _t11 = (ANTLRTokenPtr)LT(1);
}
 labase++;
	if ( !guessing ) {
	
	_ast11 = new AST(_t11);
	_ast11->subchild(_root, &_sibling, &_tail);
	}
	
	if ( !guessing ) {
		cont = _t11;
	cont_ast = _ast11;
	}
	
	if ( !guessing ) {
	cont_ast->setType(TOK_STMT_CONTINUE);
	}
 consume();
	return;
fail:
	if ( guessing ) zzGUESS_FAIL;
	syn(zzBadTok, "continue statement", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd2, 0x8);
_handler:
	zzdflthandlers(_signal,_retsignal);
	return;
}

void
P::create_event_statement(ASTBase **_root,int *_retsignal)
{
	zzRULE;
	int _sva=1;
	ASTBase *_ast = NULL, *_sibling = NULL, *_tail = NULL;
	ANTLRTokenPtr _t11=NULL,_t12=NULL,_t13=NULL,_t15=NULL;
	AST *_ast11=NULL,*_ast12=NULL,*_ast13=NULL,*_ast14=NULL,*_ast15=NULL,*_ast16=NULL;
	ANTLRTokenPtr cr=NULL, eirv=NULL, es=NULL;
	AST *cr_ast=NULL, *eirv_ast=NULL, *es_ast=NULL;
	int _signal=NoSignal;
	*_retsignal = NoSignal;
	AST *c_ast;
	zzmatch_wsig(TOK_CREATE, _handler);	
	if ( !guessing ) {
	 _t11 = (ANTLRTokenPtr)LT(1);
}
 labase++;
	
	if ( !guessing ) {
		cr = _t11;
	}
	 consume();
	zzmatch_wsig(TOK_EVENT, _handler);	
	if ( !guessing ) {
	 _t12 = (ANTLRTokenPtr)LT(1);
}
 labase++;
	 consume();
	zzmatch_wsig(TOK_INSTANCE, _handler);	
	if ( !guessing ) {
	 _t13 = (ANTLRTokenPtr)LT(1);
}
 labase++;
	 consume();
	_ast = NULL;
	local_variable(&_ast,&_signal, ASSIGN_LVAL ); if (_signal) goto _handler;
	_ast14 = (AST *)_ast;
	eirv_ast = _ast14;
	zzmatch_wsig(TOK_OF, _handler);	
	if ( !guessing ) {
	 _t15 = (ANTLRTokenPtr)LT(1);
}
 labase++;
	 consume();
	_ast = NULL;
	event_spec(&_ast,&_signal); if (_signal) goto _handler;
	_ast16 = (AST *)_ast;
	es_ast = _ast16;
	if ( !guessing ) {
	eirv_ast->setType(TOK_EVENT_REF_VAR);
	st->newadd( eirv_ast, EVENT_INST_DATATYPE, es_ast );
	c_ast = (new AST( cr, TOK_STMT_CREATE_EVENT));
	(*_root) = ASTBase::tmake( c_ast, eirv_ast, es_ast , NULL);
	}
	return;
fail:
	if ( guessing ) zzGUESS_FAIL;
	syn(zzBadTok, "create event instance statement", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd2, 0x10);
_handler:
	zzdflthandlers(_signal,_retsignal);
	return;
}

void
P::create_object_statement(ASTBase **_root,int *_retsignal)
{
	zzRULE;
	int _sva=1;
	ASTBase *_ast = NULL, *_sibling = NULL, *_tail = NULL;
	ANTLRTokenPtr _t11=NULL,_t12=NULL,_t13=NULL,_t15=NULL;
	AST *_ast11=NULL,*_ast12=NULL,*_ast13=NULL,*_ast15=NULL,*_ast16=NULL;
	ANTLRTokenPtr cr=NULL, lv=NULL, kl=NULL;
	AST *cr_ast=NULL, *lv_ast=NULL, *kl_ast=NULL;
	int _signal=NoSignal;
	*_retsignal = NoSignal;
	AST *c_ast;
	zzmatch_wsig(TOK_CREATE, _handler);	
	if ( !guessing ) {
	 _t11 = (ANTLRTokenPtr)LT(1);
}
 labase++;
	
	if ( !guessing ) {
		cr = _t11;
	}
	 consume();
	zzmatch_wsig(TOK_OBJECT, _handler);	
	if ( !guessing ) {
	 _t12 = (ANTLRTokenPtr)LT(1);
}
 labase++;
	 consume();
	zzmatch_wsig(TOK_INSTANCE, _handler);	
	if ( !guessing ) {
	 _t13 = (ANTLRTokenPtr)LT(1);
}
 labase++;
	 consume();
	{
		AST *_ast22=NULL;
		zzGUESS_BLOCK
		zzGUESS
		if ( !zzrv && (LA(1)==TOK_ACROSS || LA(1)==TOK_ANY || LA(1)==TOK_ASSIGNER || 
LA(1)==TOK_ASSIGN || LA(1)==TOK_BREAKTOKEN || LA(1)==TOK_BY || LA(1)==TOK_CLASS || LA(1)==TOK_CONTINUE || 
LA(1)==TOK_CONTROL || LA(1)==TOK_CREATE || LA(1)==TOK_CREATOR || LA(1)==TOK_DELETE || LA(1)==TOK_EACH || 
LA(1)==TOK_END || LA(1)==TOK_EVENT || LA(1)==TOK_FOR || LA(1)==TOK_FROM || LA(1)==TOK_GENERATE || 
LA(1)==TOK_IN || LA(1)==TOK_INSTANCES || LA(1)==TOK_INSTANCE || LA(1)==TOK_MANY || LA(1)==TOK_OBJECT || 
LA(1)==TOK_OF || LA(1)==TOK_ONE || LA(1)==TOK_RELATED || LA(1)==TOK_RELATE || LA(1)==TOK_SELECT || 
LA(1)==TOK_STOP || LA(1)==TOK_TO || LA(1)==TOK_WHERE || LA(1)==TOK_UNRELATE || LA(1)==TOK_USING || 
LA(1)==TOK_SELECTED || LA(1)==TOK_SELF || LA(1)==TOK_GARBAGE || LA(1)==TOK_BAD_ID || LA(1)==TOK_BAD_NAME || 
LA(1)==TOK_ID || LA(1)==TOK_RELID) && (LA(2)==TOK_OF) ) {
			{
				ANTLRTokenPtr _t32=NULL;
				AST *_ast31=NULL,*_ast32=NULL;
				_ast = NULL;
				local_variable(&_ast,&_signal, ASSIGN_LVAL ); if (_signal) goto _handler;
				_ast31 = (AST *)_ast;
				zzmatch_wsig(TOK_OF, _handler);				
				if ( !guessing ) {
				 _t32 = (ANTLRTokenPtr)LT(1);
}
 labase++;
				 consume();
			}
			zzGUESS_DONE
			_ast = NULL;
			local_variable(&_ast,&_signal, ASSIGN_LVAL ); if (_signal) goto _handler;
			_ast22 = (AST *)_ast;
			lv_ast = _ast22;
		}
		else if ( !zzrv ) zzGUESS_DONE;
	}
	zzmatch_wsig(TOK_OF, _handler);	
	if ( !guessing ) {
	 _t15 = (ANTLRTokenPtr)LT(1);
}
 labase++;
	 consume();
	_ast = NULL;
	object_keyletters(&_ast,&_signal); if (_signal) goto _handler;
	_ast16 = (AST *)_ast;
	kl_ast = _ast16;
	if ( !guessing ) {
	if ( lv_ast )
	{
		lv_ast->setType(TOK_INST_REF_VAR);
		st->newadd( lv_ast, OBJECT_INST_REF_DATATYPE, kl_ast );
	}
	c_ast = (new AST( cr, TOK_STMT_CREATE_OBJECT));
	(*_root) = ASTBase::tmake( c_ast, kl_ast, lv_ast , NULL);
	}
	return;
fail:
	if ( guessing ) zzGUESS_FAIL;
	syn(zzBadTok, "create object instance statement", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd2, 0x20);
_handler:
	zzdflthandlers(_signal,_retsignal);
	return;
}

void
P::debug_statement(ASTBase **_root,int *_retsignal)
{
	zzRULE;
	int _sva=1;
	ASTBase *_ast = NULL, *_sibling = NULL, *_tail = NULL;
	ANTLRTokenPtr _t11=NULL;
	AST *_ast11=NULL;
	int _signal=NoSignal;
	*_retsignal = NoSignal;
	zzmatch_wsig(TOK_DEBUG, _handler);	
	if ( !guessing ) {
	 _t11 = (ANTLRTokenPtr)LT(1);
}
 labase++;
	 consume();
	{
;
		if ( (LA(1)==TOK_ON || 
LA(1)==TOK_OFF || LA(1)==TOK_TRACE || LA(1)==TOK_STAT || LA(1)==TOK_DUMP || LA(1)==TOK_SOR)
 ) {
			{
				AST *_ast31=NULL;
				int zzcnt=1;
				do {
					_ast = NULL;
					debug_operand(&_ast,&_signal); if (_signal) goto _handler;
					_ast31 = (AST *)_ast;
				} while ( (LA(1)==TOK_ON || LA(1)==TOK_OFF || LA(1)==TOK_TRACE || LA(1)==TOK_STAT || 
LA(1)==TOK_DUMP || LA(1)==TOK_SOR) );
			}
		}
		else {
			if ( (LA(1)==TOK_SEMI) ) {
				if ( !guessing ) {
				trace = TRUE;
				dumpflag = TRUE;
				}
			}
			else {
				if ( guessing ) goto fail;
				if (_sva) _signal=NoViableAlt;
				else _signal=NoSemViableAlt;
				goto _handler;  /* MR7 */
			}
		}
	}
	return;
fail:
	if ( guessing ) zzGUESS_FAIL;
	syn(zzBadTok, "debug statement", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd2, 0x40);
_handler:
	zzdflthandlers(_signal,_retsignal);
	return;
}

void
P::delete_statement(ASTBase **_root,int *_retsignal)
{
	zzRULE;
	int _sva=1;
	ASTBase *_ast = NULL, *_sibling = NULL, *_tail = NULL;
	ANTLRTokenPtr _t11=NULL,_t12=NULL,_t13=NULL;
	AST *_ast11=NULL,*_ast12=NULL,*_ast13=NULL,*_ast14=NULL;
	ANTLRTokenPtr td=NULL, irv=NULL;
	AST *td_ast=NULL, *irv_ast=NULL;
	int _signal=NoSignal;
	*_retsignal = NoSignal;
	Sym *s_ref = NULL;
	AST *c_ast;
	zzmatch_wsig(TOK_DELETE, _handler);	
	if ( !guessing ) {
	 _t11 = (ANTLRTokenPtr)LT(1);
}
 labase++;
	
	if ( !guessing ) {
		td = _t11;
	}
	 consume();
	zzmatch_wsig(TOK_OBJECT, _handler);	
	if ( !guessing ) {
	 _t12 = (ANTLRTokenPtr)LT(1);
}
 labase++;
	 consume();
	zzmatch_wsig(TOK_INSTANCE, _handler);	
	if ( !guessing ) {
	 _t13 = (ANTLRTokenPtr)LT(1);
}
 labase++;
	 consume();
	_ast = NULL;
	inst_ref_var(&_ast,&_signal); if (_signal) goto _handler;
	_ast14 = (AST *)_ast;
	irv_ast = _ast14;
	if ( !guessing ) {
	
	if ( irv_ast )
	{
		// This goes along with error 41 in the inst_ref_var subrule
		if ( ! ( st->is_inst_ref_var( irv_ast->getVcharText(), &s_ref ) ) )
		AL_PARSE_ERR1( irv_ast, AL_GETMSG(ERR,120,1), irv_ast->getVcharText() )
		c_ast = (new AST( td, TOK_STMT_DELETE));
		(*_root) = ASTBase::tmake( c_ast, irv_ast , NULL);
	}
	}
	return;
fail:
	if ( guessing ) zzGUESS_FAIL;
	syn(zzBadTok, "delete object instance statement", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd2, 0x80);
_handler:
	zzdflthandlers(_signal,_retsignal);
	return;
}

void
P::empty_statement(ASTBase **_root,int *_retsignal)
{
	zzRULE;
	int _sva=1;
	ASTBase *_ast = NULL, *_sibling = NULL, *_tail = NULL;
;
	int _signal=NoSignal;
	*_retsignal = NoSignal;
	(*_root) = (new AST(TOK_STMT_EMPTY));
	return;
fail:
	if ( guessing ) zzGUESS_FAIL;
	syn(zzBadTok, "empty statement", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd3, 0x1);
_handler:
	zzdflthandlers(_signal,_retsignal);
	return;
}

void
P::for_statement(ASTBase **_root,int *_retsignal)
{
	zzRULE;
	int _sva=1;
	ASTBase *_ast = NULL, *_sibling = NULL, *_tail = NULL;
	ANTLRTokenPtr _t11=NULL,_t12=NULL,_t14=NULL;
	AST *_ast11=NULL,*_ast12=NULL,*_ast13=NULL,*_ast14=NULL,*_ast15=NULL;
	ANTLRTokenPtr f=NULL, irv=NULL, irsv=NULL, stmt=NULL;
	AST *f_ast=NULL, *irv_ast=NULL, *irsv_ast=NULL, *stmt_ast=NULL;
	int _signal=NoSignal;
	*_retsignal = NoSignal;
	AST *fa;
	AST *pa1;
	AST *pa2;
	AST *t_ast;
	Sym *s_ref;
	zzmatch_wsig(TOK_FOR, _handler);	
	if ( !guessing ) {
	 _t11 = (ANTLRTokenPtr)LT(1);
}
 labase++;
	
	if ( !guessing ) {
		f = _t11;
	}
	 consume();
	zzmatch_wsig(TOK_EACH, _handler);	
	if ( !guessing ) {
	 _t12 = (ANTLRTokenPtr)LT(1);
}
 labase++;
	 consume();
	_ast = NULL;
	local_variable(&_ast,&_signal, ASSIGN_LVAL ); if (_signal) goto _handler;
	_ast13 = (AST *)_ast;
	irv_ast = _ast13;
	zzmatch_wsig(TOK_IN, _handler);	
	if ( !guessing ) {
	 _t14 = (ANTLRTokenPtr)LT(1);
}
 labase++;
	 consume();
	_ast = NULL;
	inst_ref_set_var(&_ast,&_signal); if (_signal) goto _handler;
	_ast15 = (AST *)_ast;
	irsv_ast = _ast15;
	if ( !guessing ) {
	irv_ast->setType(TOK_INST_REF_VAR);
	if ( st->is_inst_ref_set_var( irsv_ast->getVcharText(), &s_ref ) )
	st->newadd( irv_ast, OBJECT_INST_REF_DATATYPE, irsv_ast );
	st = st->push();
	fa = (new AST( f, TOK_STMT_FOR));
	fa->setSegLength(irsv_ast->getOffset() +
	irsv_ast->getSegLength() -
	fa->getOffset());
	pa1 = (new AST(TOK_CONTEXT_PUSH));
	pa1->setObjPtr( st );
	(*_root) = ASTBase::tmake( fa, irv_ast, irsv_ast, ASTBase::tmake( (new AST(TOK_CLAUSE_FOR)), pa1, NULL) , NULL);
	loop_clause_nest_level++;
	}
	{
		AST *_ast21=NULL;
		while ( (
LA(1)==TOK_ACROSS || LA(1)==TOK_ANY || LA(1)==TOK_ASSIGNER || LA(1)==TOK_ASSIGN || LA(1)==TOK_BREAKTOKEN || 
LA(1)==TOK_BY || LA(1)==TOK_CLASS || LA(1)==TOK_CONTINUE || LA(1)==TOK_CONTROL || LA(1)==TOK_CREATE || 
LA(1)==TOK_CREATOR || LA(1)==TOK_DELETE || LA(1)==TOK_EACH || LA(1)==TOK_END || LA(1)==TOK_EVENT || 
LA(1)==TOK_FOR || LA(1)==TOK_FROM || LA(1)==TOK_GENERATE || LA(1)==TOK_IN || LA(1)==TOK_INSTANCES || 
LA(1)==TOK_INSTANCE || LA(1)==TOK_MANY || LA(1)==TOK_OBJECT || LA(1)==TOK_OF || LA(1)==TOK_ONE || 
LA(1)==TOK_RELATED || LA(1)==TOK_RELATE || LA(1)==TOK_SELECT || LA(1)==TOK_STOP || LA(1)==TOK_TO || 
LA(1)==TOK_WHERE || LA(1)==TOK_UNRELATE || LA(1)==TOK_USING || LA(1)==TOK_BRIDGE || LA(1)==TOK_CARDINALITY || 
LA(1)==TOK_EMPTY || LA(1)==TOK_FALSETOKEN || LA(1)==TOK_NOT || LA(1)==TOK_NOTEMPTY || LA(1)==TOK_TRANSFORM || 
LA(1)==TOK_TRUETOKEN || LA(1)==TOK_PARAM || LA(1)==TOK_RCVD_EVT || LA(1)==TOK_SELECTED || LA(1)==TOK_SELF || 
LA(1)==TOK_IF || LA(1)==TOK_RETURN || LA(1)==TOK_WHILE || LA(1)==TOK_DEBUG || LA(1)==TOK_DOUBLECOLON || 
LA(1)==TOK_SEMI || LA(1)==TOK_GENERAL_NAME || LA(1)==TOK_GARBAGE || LA(1)==TOK_BAD_ID || LA(1)==TOK_BAD_NAME || 
LA(1)==TOK_ID || LA(1)==TOK_RELID) && (LA(2)==Eof || LA(2)==TOK_ACROSS || 
LA(2)==TOK_ANY || LA(2)==TOK_ASSIGNER || LA(2)==TOK_ASSIGN || LA(2)==TOK_BREAKTOKEN || LA(2)==TOK_BY || 
LA(2)==TOK_CLASS || LA(2)==TOK_CONTINUE || LA(2)==TOK_CONTROL || LA(2)==TOK_CREATE || LA(2)==TOK_CREATOR || 
LA(2)==TOK_DELETE || LA(2)==TOK_EACH || LA(2)==TOK_END || LA(2)==TOK_EVENT || LA(2)==TOK_FOR || 
LA(2)==TOK_FROM || LA(2)==TOK_GENERATE || LA(2)==TOK_IN || LA(2)==TOK_INSTANCES || LA(2)==TOK_INSTANCE || 
LA(2)==TOK_MANY || LA(2)==TOK_OBJECT || LA(2)==TOK_OF || LA(2)==TOK_ONE || LA(2)==TOK_RELATED || 
LA(2)==TOK_RELATE || LA(2)==TOK_SELECT || LA(2)==TOK_STOP || LA(2)==TOK_TO || LA(2)==TOK_WHERE || 
LA(2)==TOK_UNRELATE || LA(2)==TOK_USING || LA(2)==TOK_BRIDGE || LA(2)==TOK_CARDINALITY || LA(2)==TOK_EMPTY || 
LA(2)==TOK_FALSETOKEN || LA(2)==TOK_NOT || LA(2)==TOK_NOTEMPTY || LA(2)==TOK_TRANSFORM || LA(2)==TOK_TRUETOKEN || 
LA(2)==TOK_PARAM || LA(2)==TOK_RCVD_EVT || LA(2)==TOK_SELECTED || LA(2)==TOK_SELF || LA(2)==TOK_AND || 
LA(2)==TOK_ELIF || LA(2)==TOK_ELSE || LA(2)==TOK_IF || LA(2)==TOK_OR || LA(2)==TOK_RETURN || 
LA(2)==TOK_WHILE || LA(2)==TOK_DEBUG || LA(2)==TOK_ON || LA(2)==TOK_OFF || LA(2)==TOK_TRACE || 
LA(2)==TOK_STAT || LA(2)==TOK_DUMP || LA(2)==TOK_SOR || LA(2)==TOK_DOT || LA(2)==TOK_DOUBLECOLON || 
LA(2)==TOK_EQUAL || LA(2)==TOK_LPAREN || LA(2)==TOK_MINUS || LA(2)==TOK_PLUS || LA(2)==TOK_SEMI || 
LA(2)==TOK_QMARK || LA(2)==TOK_QUOTE || LA(2)==TOK_FRACTION || LA(2)==TOK_GENERAL_NAME || LA(2)==TOK_GARBAGE || 
LA(2)==TOK_BAD_ID || LA(2)==TOK_BAD_NAME || LA(2)==TOK_ID || LA(2)==TOK_RELID || LA(2)==TOK_NUMBER) && !( LA(1)==TOK_END && LA(2)==TOK_FOR) ) {
			_ast = NULL;
			for_clause_statement(&_ast,&_signal); if (_signal) goto _handler;
			_ast21 = (AST *)_ast;
			stmt_ast = _ast21;
			if ( !guessing ) {
			ASTBase::tmake( NULL, pa1->bottom(), stmt_ast , NULL);
			}
		}
	}
	if ( !guessing ) {
	loop_clause_nest_level--;
	st = st->pop();
	pa2 = (new AST(TOK_CONTEXT_POP));
	pa2->setObjPtr( st );
	ASTBase::tmake( NULL, pa1->bottom(), pa2 , NULL);
	}
	{
		ANTLRTokenPtr _t21=NULL,_t22=NULL;
		AST *_ast21=NULL,*_ast22=NULL;
		if ( (
LA(1)==TOK_END) ) {
			zzmatch_wsig(TOK_END, _handler);			
			if ( !guessing ) {
			 _t21 = (ANTLRTokenPtr)LT(1);
}
 labase++;
			 consume();
			zzmatch_wsig(TOK_FOR, _handler);			
			if ( !guessing ) {
			 _t22 = (ANTLRTokenPtr)LT(1);
}
 labase++;
			 consume();
		}
		else {
			if ( (LA(1)==Eof) ) {
				zzmatch_wsig(Eof, _handler);				
				if ( !guessing ) {
				 _t21 = (ANTLRTokenPtr)LT(1);
}
 labase++;
				
				if ( !guessing ) {
				AL_PARSE_ERR0( fa, AL_GETMSG(ERR,011,0) )
				}
 consume();
			}
			else {
				if ( guessing ) goto fail;
				if (_sva) _signal=NoViableAlt;
				else _signal=NoSemViableAlt;
				goto _handler;  /* MR7 */
			}
		}
	}
	return;
fail:
	if ( guessing ) zzGUESS_FAIL;
	syn(zzBadTok, "for statement", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd3, 0x2);
_handler:
	zzdflthandlers(_signal,_retsignal);
	return;
}

void
P::generate_statement(ASTBase **_root,int *_retsignal)
{
	zzRULE;
	int _sva=1;
	ASTBase *_ast = NULL, *_sibling = NULL, *_tail = NULL;
	ANTLRTokenPtr _t11=NULL;
	AST *_ast11=NULL;
	ANTLRTokenPtr ge=NULL, es=NULL, ev=NULL, aa=NULL;
	AST *ge_ast=NULL, *es_ast=NULL, *ev_ast=NULL, *aa_ast=NULL;
	int _signal=NoSignal;
	*_retsignal = NoSignal;
	Sym *s_ref = NULL;
	t_core_data_type t1;
	zzmatch_wsig(TOK_GENERATE, _handler);	
	if ( !guessing ) {
	 _t11 = (ANTLRTokenPtr)LT(1);
}
 labase++;
	
	if ( !guessing ) {
		ge = _t11;
	}
	 consume();
	{
		AST *_ast21=NULL;
		if ( (LA(1)==TOK_ACROSS || 
LA(1)==TOK_ANY || LA(1)==TOK_ASSIGNER || LA(1)==TOK_ASSIGN || LA(1)==TOK_BREAKTOKEN || LA(1)==TOK_BY || 
LA(1)==TOK_CLASS || LA(1)==TOK_CONTINUE || LA(1)==TOK_CONTROL || LA(1)==TOK_CREATE || LA(1)==TOK_CREATOR || 
LA(1)==TOK_DELETE || LA(1)==TOK_EACH || LA(1)==TOK_END || LA(1)==TOK_EVENT || LA(1)==TOK_FOR || 
LA(1)==TOK_FROM || LA(1)==TOK_GENERATE || LA(1)==TOK_IN || LA(1)==TOK_INSTANCES || LA(1)==TOK_INSTANCE || 
LA(1)==TOK_MANY || LA(1)==TOK_OBJECT || LA(1)==TOK_OF || LA(1)==TOK_ONE || LA(1)==TOK_RELATED || 
LA(1)==TOK_RELATE || LA(1)==TOK_SELECT || LA(1)==TOK_STOP || LA(1)==TOK_TO || LA(1)==TOK_WHERE || 
LA(1)==TOK_UNRELATE || LA(1)==TOK_USING || LA(1)==TOK_BRIDGE || LA(1)==TOK_CARDINALITY || LA(1)==TOK_EMPTY || 
LA(1)==TOK_FALSETOKEN || LA(1)==TOK_NOT || LA(1)==TOK_NOTEMPTY || LA(1)==TOK_TRANSFORM || LA(1)==TOK_TRUETOKEN || 
LA(1)==TOK_PARAM || LA(1)==TOK_RCVD_EVT || LA(1)==TOK_SELECTED || LA(1)==TOK_SELF || LA(1)==TOK_GENERAL_NAME || 
LA(1)==TOK_GARBAGE || LA(1)==TOK_BAD_ID || LA(1)==TOK_BAD_NAME || LA(1)==TOK_ID || LA(1)==TOK_RELID) && 
(LA(2)==TOK_TO || LA(2)==TOK_COLON || LA(2)==TOK_LPAREN || LA(2)==TOK_TIMES) ) {
			_ast = NULL;
			event_spec(&_ast,&_signal); if (_signal) goto _handler;
			_ast21 = (AST *)_ast;
			es_ast = _ast21;
			if ( !guessing ) {
			(*_root) = ASTBase::tmake( (new AST( ge, TOK_STMT_GENERATE)), es_ast , NULL);
			}
		}
		else {
			if ( (
LA(1)==TOK_ACROSS || LA(1)==TOK_ANY || LA(1)==TOK_ASSIGNER || LA(1)==TOK_ASSIGN || LA(1)==TOK_BREAKTOKEN || 
LA(1)==TOK_BY || LA(1)==TOK_CLASS || LA(1)==TOK_CONTINUE || LA(1)==TOK_CONTROL || LA(1)==TOK_CREATE || 
LA(1)==TOK_CREATOR || LA(1)==TOK_DELETE || LA(1)==TOK_EACH || LA(1)==TOK_END || LA(1)==TOK_EVENT || 
LA(1)==TOK_FOR || LA(1)==TOK_FROM || LA(1)==TOK_GENERATE || LA(1)==TOK_IN || LA(1)==TOK_INSTANCES || 
LA(1)==TOK_INSTANCE || LA(1)==TOK_MANY || LA(1)==TOK_OBJECT || LA(1)==TOK_OF || LA(1)==TOK_ONE || 
LA(1)==TOK_RELATED || LA(1)==TOK_RELATE || LA(1)==TOK_SELECT || LA(1)==TOK_STOP || LA(1)==TOK_TO || 
LA(1)==TOK_WHERE || LA(1)==TOK_UNRELATE || LA(1)==TOK_USING || LA(1)==TOK_SELECTED || LA(1)==TOK_SELF || 
LA(1)==TOK_GARBAGE || LA(1)==TOK_BAD_ID || LA(1)==TOK_BAD_NAME || LA(1)==TOK_ID || LA(1)==TOK_RELID) && 
(LA(2)==TOK_SEMI) ) {
				_ast = NULL;
				local_variable(&_ast,&_signal, ASSIGN_RVAL ); if (_signal) goto _handler;
				_ast21 = (AST *)_ast;
				ev_ast = _ast21;
				if ( !guessing ) {
				ev_ast->setType(TOK_EVENT_REF_VAR);
				if ( ! (st->is_var_this_type_defined( ev_ast->getVcharText(),
				EVENT_INST_DATATYPE, &s_ref ) ) )
				AL_PARSE_ERR1( ev_ast, AL_GETMSG(ERR,044,1), ev_ast->getVcharText() )
				(*_root) = ASTBase::tmake( (new AST( ge, TOK_STMT_GENERATE)), ev_ast , NULL);
				}
			}
			else {
				if ( (LA(1)==TOK_ACROSS || LA(1)==TOK_ANY || LA(1)==TOK_ASSIGNER || 
LA(1)==TOK_ASSIGN || LA(1)==TOK_BREAKTOKEN || LA(1)==TOK_BY || LA(1)==TOK_CLASS || LA(1)==TOK_CONTINUE || 
LA(1)==TOK_CONTROL || LA(1)==TOK_CREATE || LA(1)==TOK_CREATOR || LA(1)==TOK_DELETE || LA(1)==TOK_EACH || 
LA(1)==TOK_END || LA(1)==TOK_EVENT || LA(1)==TOK_FOR || LA(1)==TOK_FROM || LA(1)==TOK_GENERATE || 
LA(1)==TOK_IN || LA(1)==TOK_INSTANCES || LA(1)==TOK_INSTANCE || LA(1)==TOK_MANY || LA(1)==TOK_OBJECT || 
LA(1)==TOK_OF || LA(1)==TOK_ONE || LA(1)==TOK_RELATED || LA(1)==TOK_RELATE || LA(1)==TOK_SELECT || 
LA(1)==TOK_STOP || LA(1)==TOK_TO || LA(1)==TOK_WHERE || LA(1)==TOK_UNRELATE || LA(1)==TOK_USING || 
LA(1)==TOK_SELECTED || LA(1)==TOK_SELF || LA(1)==TOK_GARBAGE || LA(1)==TOK_BAD_ID || LA(1)==TOK_BAD_NAME || 
LA(1)==TOK_ID || LA(1)==TOK_RELID) && (LA(2)==TOK_DOT) ) {
					_ast = NULL;
					if ( !guessing ) {
						 t1  = attribute_access(&_ast,&_signal, ASSIGN_RVAL ); if (_signal) goto _handler;
						_ast21 = (AST *)_ast;
						aa_ast = _ast21;
					} else {
						attribute_access(&_ast,&_signal, ASSIGN_RVAL );
					}
					if ( !guessing ) {
					if ( t1 != EVENT_INST_DATATYPE)
					AL_PARSE_ERR1( aa_ast, AL_GETMSG(ERR,283,1), aa_ast->getVcharText() )
					(*_root) = ASTBase::tmake( (new AST( ge, TOK_STMT_GENERATE)), aa_ast , NULL);
					}
				}
				else {
					if ( guessing ) goto fail;
					if (_sva) _signal=NoViableAlt;
					else _signal=NoSemViableAlt;
					goto _handler;  /* MR7 */
				}
			}
		}
	}
	return;
fail:
	if ( guessing ) zzGUESS_FAIL;
	syn(zzBadTok, "generate event statement", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd3, 0x4);
_handler:
	zzdflthandlers(_signal,_retsignal);
	return;
}

void
P::if_statement(ASTBase **_root,int *_retsignal)
{
	zzRULE;
	int _sva=1;
	ASTBase *_ast = NULL, *_sibling = NULL, *_tail = NULL;
	ANTLRTokenPtr _t11=NULL;
	AST *_ast11=NULL,*_ast12=NULL;
	ANTLRTokenPtr ifs=NULL, e1=NULL, stmt1=NULL, elf=NULL, e2=NULL, stmt2=NULL, el=NULL, stmt3=NULL;
	AST *ifs_ast=NULL, *e1_ast=NULL, *stmt1_ast=NULL, *elf_ast=NULL, *e2_ast=NULL, *stmt2_ast=NULL, *el_ast=NULL, *stmt3_ast=NULL;
	int _signal=NoSignal;
	*_retsignal = NoSignal;
	t_core_data_type t1;
	AST *ifa = NULL;
	AST *eia = NULL;
	AST *ela = NULL;
	AST *pa1;
	AST *pa2;
	ASTBase *ia1;
	zzmatch_wsig(TOK_IF, _handler);	
	if ( !guessing ) {
	 _t11 = (ANTLRTokenPtr)LT(1);
}
 labase++;
	
	if ( !guessing ) {
		ifs = _t11;
	}
	 consume();
	_ast = NULL;
	if ( !guessing ) {
		 t1  = expr(&_ast,&_signal); if (_signal) goto _handler;
		_ast12 = (AST *)_ast;
		e1_ast = _ast12;
	} else {
		expr(&_ast,&_signal);
	}
	if ( !guessing ) {
	st = st->push();
	ifa = (new AST( ifs, TOK_STMT_IF));
	ifa->setSegLength(e1_ast->getOffset() +
	e1_ast->getSegLength() -
	ifa->getOffset());
	pa1 = (new AST(TOK_CONTEXT_PUSH));
	pa1->setObjPtr( st );
	ia1 = (new AST(TOK_CLAUSE_IF));
	(*_root) = ASTBase::tmake( ifa, ASTBase::tmake( ia1, e1_ast, pa1 , NULL) , NULL);
	if ( t1 != BOOLEAN_DATATYPE )
	AL_PARSE_ERR0( ifa, AL_GETMSG(ERR,014,0) )
	}
	{
		AST *_ast21=NULL;
		while ( (LA(1)==TOK_ACROSS || 
LA(1)==TOK_ANY || LA(1)==TOK_ASSIGNER || LA(1)==TOK_ASSIGN || LA(1)==TOK_BREAKTOKEN || LA(1)==TOK_BY || 
LA(1)==TOK_CLASS || LA(1)==TOK_CONTINUE || LA(1)==TOK_CONTROL || LA(1)==TOK_CREATE || LA(1)==TOK_CREATOR || 
LA(1)==TOK_DELETE || LA(1)==TOK_EACH || LA(1)==TOK_END || LA(1)==TOK_EVENT || LA(1)==TOK_FOR || 
LA(1)==TOK_FROM || LA(1)==TOK_GENERATE || LA(1)==TOK_IN || LA(1)==TOK_INSTANCES || LA(1)==TOK_INSTANCE || 
LA(1)==TOK_MANY || LA(1)==TOK_OBJECT || LA(1)==TOK_OF || LA(1)==TOK_ONE || LA(1)==TOK_RELATED || 
LA(1)==TOK_RELATE || LA(1)==TOK_SELECT || LA(1)==TOK_STOP || LA(1)==TOK_TO || LA(1)==TOK_WHERE || 
LA(1)==TOK_UNRELATE || LA(1)==TOK_USING || LA(1)==TOK_BRIDGE || LA(1)==TOK_CARDINALITY || LA(1)==TOK_EMPTY || 
LA(1)==TOK_FALSETOKEN || LA(1)==TOK_NOT || LA(1)==TOK_NOTEMPTY || LA(1)==TOK_TRANSFORM || LA(1)==TOK_TRUETOKEN || 
LA(1)==TOK_PARAM || LA(1)==TOK_RCVD_EVT || LA(1)==TOK_SELECTED || LA(1)==TOK_SELF || LA(1)==TOK_IF || 
LA(1)==TOK_RETURN || LA(1)==TOK_WHILE || LA(1)==TOK_DEBUG || LA(1)==TOK_DOUBLECOLON || LA(1)==TOK_SEMI || 
LA(1)==TOK_GENERAL_NAME || LA(1)==TOK_GARBAGE || LA(1)==TOK_BAD_ID || LA(1)==TOK_BAD_NAME || LA(1)==TOK_ID || 
LA(1)==TOK_RELID) && (LA(2)==Eof || LA(2)==TOK_ACROSS || LA(2)==TOK_ANY || 
LA(2)==TOK_ASSIGNER || LA(2)==TOK_ASSIGN || LA(2)==TOK_BREAKTOKEN || LA(2)==TOK_BY || LA(2)==TOK_CLASS || 
LA(2)==TOK_CONTINUE || LA(2)==TOK_CONTROL || LA(2)==TOK_CREATE || LA(2)==TOK_CREATOR || LA(2)==TOK_DELETE || 
LA(2)==TOK_EACH || LA(2)==TOK_END || LA(2)==TOK_EVENT || LA(2)==TOK_FOR || LA(2)==TOK_FROM || 
LA(2)==TOK_GENERATE || LA(2)==TOK_IN || LA(2)==TOK_INSTANCES || LA(2)==TOK_INSTANCE || LA(2)==TOK_MANY || 
LA(2)==TOK_OBJECT || LA(2)==TOK_OF || LA(2)==TOK_ONE || LA(2)==TOK_RELATED || LA(2)==TOK_RELATE || 
LA(2)==TOK_SELECT || LA(2)==TOK_STOP || LA(2)==TOK_TO || LA(2)==TOK_WHERE || LA(2)==TOK_UNRELATE || 
LA(2)==TOK_USING || LA(2)==TOK_BRIDGE || LA(2)==TOK_CARDINALITY || LA(2)==TOK_EMPTY || LA(2)==TOK_FALSETOKEN || 
LA(2)==TOK_NOT || LA(2)==TOK_NOTEMPTY || LA(2)==TOK_TRANSFORM || LA(2)==TOK_TRUETOKEN || LA(2)==TOK_PARAM || 
LA(2)==TOK_RCVD_EVT || LA(2)==TOK_SELECTED || LA(2)==TOK_SELF || LA(2)==TOK_AND || LA(2)==TOK_ELIF || 
LA(2)==TOK_ELSE || LA(2)==TOK_IF || LA(2)==TOK_OR || LA(2)==TOK_RETURN || LA(2)==TOK_WHILE || 
LA(2)==TOK_DEBUG || LA(2)==TOK_ON || LA(2)==TOK_OFF || LA(2)==TOK_TRACE || LA(2)==TOK_STAT || 
LA(2)==TOK_DUMP || LA(2)==TOK_SOR || LA(2)==TOK_DOT || LA(2)==TOK_DOUBLECOLON || LA(2)==TOK_EQUAL || 
LA(2)==TOK_LPAREN || LA(2)==TOK_MINUS || LA(2)==TOK_PLUS || LA(2)==TOK_SEMI || LA(2)==TOK_QMARK || 
LA(2)==TOK_QUOTE || LA(2)==TOK_FRACTION || LA(2)==TOK_GENERAL_NAME || LA(2)==TOK_GARBAGE || LA(2)==TOK_BAD_ID || 
LA(2)==TOK_BAD_NAME || LA(2)==TOK_ID || LA(2)==TOK_RELID || LA(2)==TOK_NUMBER) && !( LA(1)==TOK_END && LA(2)==TOK_IF) ) {
			_ast = NULL;
			if_clause_statement(&_ast,&_signal); if (_signal) goto _handler;
			_ast21 = (AST *)_ast;
			stmt1_ast = _ast21;
			if ( !guessing ) {
			ASTBase::tmake( NULL, pa1->bottom(), stmt1_ast , NULL);
			}
		}
	}
	if ( !guessing ) {
	st = st->pop();
	pa2 = (new AST(TOK_CONTEXT_POP));
	pa2->setObjPtr( st );
	ASTBase::tmake( NULL, pa1->bottom(), pa2 , NULL);
	}
	{
;
		if ( (LA(1)==TOK_ELIF)
 ) {
			{
				ANTLRTokenPtr _t31=NULL;
				AST *_ast31=NULL,*_ast32=NULL;
				int zzcnt=1;
				do {
					zzmatch_wsig(TOK_ELIF, _handler);					
					if ( !guessing ) {
					 _t31 = (ANTLRTokenPtr)LT(1);
}
 labase++;
					
					if ( !guessing ) {
										elf = _t31;
					}
					 consume();
					_ast = NULL;
					if ( !guessing ) {
						 t1  = expr(&_ast,&_signal); if (_signal) goto _handler;
						_ast32 = (AST *)_ast;
						e2_ast = _ast32;
					} else {
						expr(&_ast,&_signal);
					}
					if ( !guessing ) {
					st = st->push();
					eia = (new AST( elf, TOK_CLAUSE_ELIF));
					eia->setSegLength(e2_ast->getOffset() +
					e2_ast->getSegLength() -
					eia->getOffset());
					pa1 = (new AST(TOK_CONTEXT_PUSH));
					pa1->setObjPtr( st );
					ASTBase::tmake( NULL, ia1->tail(), ASTBase::tmake( eia, e2_ast, pa1 , NULL) , NULL);
					if ( t1 != BOOLEAN_DATATYPE )
					AL_PARSE_ERR0( eia, AL_GETMSG(ERR,015,0) )
					}
					{
						AST *_ast41=NULL;
						while ( (LA(1)==TOK_ACROSS || LA(1)==TOK_ANY || LA(1)==TOK_ASSIGNER || LA(1)==TOK_ASSIGN || 
LA(1)==TOK_BREAKTOKEN || LA(1)==TOK_BY || LA(1)==TOK_CLASS || LA(1)==TOK_CONTINUE || LA(1)==TOK_CONTROL || 
LA(1)==TOK_CREATE || LA(1)==TOK_CREATOR || LA(1)==TOK_DELETE || LA(1)==TOK_EACH || LA(1)==TOK_END || 
LA(1)==TOK_EVENT || LA(1)==TOK_FOR || LA(1)==TOK_FROM || LA(1)==TOK_GENERATE || LA(1)==TOK_IN || 
LA(1)==TOK_INSTANCES || LA(1)==TOK_INSTANCE || LA(1)==TOK_MANY || LA(1)==TOK_OBJECT || LA(1)==TOK_OF || 
LA(1)==TOK_ONE || LA(1)==TOK_RELATED || LA(1)==TOK_RELATE || LA(1)==TOK_SELECT || LA(1)==TOK_STOP || 
LA(1)==TOK_TO || LA(1)==TOK_WHERE || LA(1)==TOK_UNRELATE || LA(1)==TOK_USING || LA(1)==TOK_BRIDGE || 
LA(1)==TOK_CARDINALITY || LA(1)==TOK_EMPTY || LA(1)==TOK_FALSETOKEN || LA(1)==TOK_NOT || LA(1)==TOK_NOTEMPTY || 
LA(1)==TOK_TRANSFORM || LA(1)==TOK_TRUETOKEN || LA(1)==TOK_PARAM || LA(1)==TOK_RCVD_EVT || LA(1)==TOK_SELECTED || 
LA(1)==TOK_SELF || LA(1)==TOK_IF || LA(1)==TOK_RETURN || LA(1)==TOK_WHILE || LA(1)==TOK_DEBUG || 
LA(1)==TOK_DOUBLECOLON || LA(1)==TOK_SEMI || LA(1)==TOK_GENERAL_NAME || LA(1)==TOK_GARBAGE || LA(1)==TOK_BAD_ID || 
LA(1)==TOK_BAD_NAME || LA(1)==TOK_ID || LA(1)==TOK_RELID) && (LA(2)==Eof || 
LA(2)==TOK_ACROSS || LA(2)==TOK_ANY || LA(2)==TOK_ASSIGNER || LA(2)==TOK_ASSIGN || LA(2)==TOK_BREAKTOKEN || 
LA(2)==TOK_BY || LA(2)==TOK_CLASS || LA(2)==TOK_CONTINUE || LA(2)==TOK_CONTROL || LA(2)==TOK_CREATE || 
LA(2)==TOK_CREATOR || LA(2)==TOK_DELETE || LA(2)==TOK_EACH || LA(2)==TOK_END || LA(2)==TOK_EVENT || 
LA(2)==TOK_FOR || LA(2)==TOK_FROM || LA(2)==TOK_GENERATE || LA(2)==TOK_IN || LA(2)==TOK_INSTANCES || 
LA(2)==TOK_INSTANCE || LA(2)==TOK_MANY || LA(2)==TOK_OBJECT || LA(2)==TOK_OF || LA(2)==TOK_ONE || 
LA(2)==TOK_RELATED || LA(2)==TOK_RELATE || LA(2)==TOK_SELECT || LA(2)==TOK_STOP || LA(2)==TOK_TO || 
LA(2)==TOK_WHERE || LA(2)==TOK_UNRELATE || LA(2)==TOK_USING || LA(2)==TOK_BRIDGE || LA(2)==TOK_CARDINALITY || 
LA(2)==TOK_EMPTY || LA(2)==TOK_FALSETOKEN || LA(2)==TOK_NOT || LA(2)==TOK_NOTEMPTY || LA(2)==TOK_TRANSFORM || 
LA(2)==TOK_TRUETOKEN || LA(2)==TOK_PARAM || LA(2)==TOK_RCVD_EVT || LA(2)==TOK_SELECTED || LA(2)==TOK_SELF || 
LA(2)==TOK_AND || LA(2)==TOK_ELIF || LA(2)==TOK_ELSE || LA(2)==TOK_IF || LA(2)==TOK_OR || 
LA(2)==TOK_RETURN || LA(2)==TOK_WHILE || LA(2)==TOK_DEBUG || LA(2)==TOK_ON || LA(2)==TOK_OFF || 
LA(2)==TOK_TRACE || LA(2)==TOK_STAT || LA(2)==TOK_DUMP || LA(2)==TOK_SOR || LA(2)==TOK_DOT || 
LA(2)==TOK_DOUBLECOLON || LA(2)==TOK_EQUAL || LA(2)==TOK_LPAREN || LA(2)==TOK_MINUS || LA(2)==TOK_PLUS || 
LA(2)==TOK_SEMI || LA(2)==TOK_QMARK || LA(2)==TOK_QUOTE || LA(2)==TOK_FRACTION || LA(2)==TOK_GENERAL_NAME || 
LA(2)==TOK_GARBAGE || LA(2)==TOK_BAD_ID || LA(2)==TOK_BAD_NAME || LA(2)==TOK_ID || LA(2)==TOK_RELID || 
LA(2)==TOK_NUMBER) && !( LA(1)==TOK_END && LA(2)==TOK_IF) ) {
							_ast = NULL;
							if_clause_statement(&_ast,&_signal); if (_signal) goto _handler;
							_ast41 = (AST *)_ast;
							stmt2_ast = _ast41;
							if ( !guessing ) {
							ASTBase::tmake( NULL, pa1->bottom(), stmt2_ast , NULL);
							}
						}
					}
					if ( !guessing ) {
					st = st->pop();
					pa2 = (new AST(TOK_CONTEXT_POP));
					pa2->setObjPtr( st );
					ASTBase::tmake( NULL, pa1->bottom(), pa2 , NULL);
					}
				} while ( (LA(1)==TOK_ELIF) );
			}
		}
	}
	{
		ANTLRTokenPtr _t21=NULL;
		AST *_ast21=NULL;
		if ( (LA(1)==TOK_ELSE) ) {
			zzmatch_wsig(TOK_ELSE, _handler);			
			if ( !guessing ) {
			 _t21 = (ANTLRTokenPtr)LT(1);
}
 labase++;
			
			if ( !guessing ) {
						el = _t21;
			}
			
			if ( !guessing ) {
			st = st->push();
			pa1 = (new AST(TOK_CONTEXT_PUSH));
			pa1->setObjPtr( st );
			ela = (new AST( el, TOK_CLAUSE_ELSE));
			ela->setSegLength(strlen(ela->getAsciiText()));
			ASTBase::tmake( NULL, ia1->tail(), ASTBase::tmake( ela, pa1 , NULL) , NULL);
			}
 consume();
			{
				AST *_ast31=NULL;
				while ( (
LA(1)==TOK_ACROSS || LA(1)==TOK_ANY || LA(1)==TOK_ASSIGNER || LA(1)==TOK_ASSIGN || LA(1)==TOK_BREAKTOKEN || 
LA(1)==TOK_BY || LA(1)==TOK_CLASS || LA(1)==TOK_CONTINUE || LA(1)==TOK_CONTROL || LA(1)==TOK_CREATE || 
LA(1)==TOK_CREATOR || LA(1)==TOK_DELETE || LA(1)==TOK_EACH || LA(1)==TOK_END || LA(1)==TOK_EVENT || 
LA(1)==TOK_FOR || LA(1)==TOK_FROM || LA(1)==TOK_GENERATE || LA(1)==TOK_IN || LA(1)==TOK_INSTANCES || 
LA(1)==TOK_INSTANCE || LA(1)==TOK_MANY || LA(1)==TOK_OBJECT || LA(1)==TOK_OF || LA(1)==TOK_ONE || 
LA(1)==TOK_RELATED || LA(1)==TOK_RELATE || LA(1)==TOK_SELECT || LA(1)==TOK_STOP || LA(1)==TOK_TO || 
LA(1)==TOK_WHERE || LA(1)==TOK_UNRELATE || LA(1)==TOK_USING || LA(1)==TOK_BRIDGE || LA(1)==TOK_CARDINALITY || 
LA(1)==TOK_EMPTY || LA(1)==TOK_FALSETOKEN || LA(1)==TOK_NOT || LA(1)==TOK_NOTEMPTY || LA(1)==TOK_TRANSFORM || 
LA(1)==TOK_TRUETOKEN || LA(1)==TOK_PARAM || LA(1)==TOK_RCVD_EVT || LA(1)==TOK_SELECTED || LA(1)==TOK_SELF || 
LA(1)==TOK_IF || LA(1)==TOK_RETURN || LA(1)==TOK_WHILE || LA(1)==TOK_DEBUG || LA(1)==TOK_DOUBLECOLON || 
LA(1)==TOK_SEMI || LA(1)==TOK_GENERAL_NAME || LA(1)==TOK_GARBAGE || LA(1)==TOK_BAD_ID || LA(1)==TOK_BAD_NAME || 
LA(1)==TOK_ID || LA(1)==TOK_RELID) && (LA(2)==Eof || LA(2)==TOK_ACROSS || 
LA(2)==TOK_ANY || LA(2)==TOK_ASSIGNER || LA(2)==TOK_ASSIGN || LA(2)==TOK_BREAKTOKEN || LA(2)==TOK_BY || 
LA(2)==TOK_CLASS || LA(2)==TOK_CONTINUE || LA(2)==TOK_CONTROL || LA(2)==TOK_CREATE || LA(2)==TOK_CREATOR || 
LA(2)==TOK_DELETE || LA(2)==TOK_EACH || LA(2)==TOK_END || LA(2)==TOK_EVENT || LA(2)==TOK_FOR || 
LA(2)==TOK_FROM || LA(2)==TOK_GENERATE || LA(2)==TOK_IN || LA(2)==TOK_INSTANCES || LA(2)==TOK_INSTANCE || 
LA(2)==TOK_MANY || LA(2)==TOK_OBJECT || LA(2)==TOK_OF || LA(2)==TOK_ONE || LA(2)==TOK_RELATED || 
LA(2)==TOK_RELATE || LA(2)==TOK_SELECT || LA(2)==TOK_STOP || LA(2)==TOK_TO || LA(2)==TOK_WHERE || 
LA(2)==TOK_UNRELATE || LA(2)==TOK_USING || LA(2)==TOK_BRIDGE || LA(2)==TOK_CARDINALITY || LA(2)==TOK_EMPTY || 
LA(2)==TOK_FALSETOKEN || LA(2)==TOK_NOT || LA(2)==TOK_NOTEMPTY || LA(2)==TOK_TRANSFORM || LA(2)==TOK_TRUETOKEN || 
LA(2)==TOK_PARAM || LA(2)==TOK_RCVD_EVT || LA(2)==TOK_SELECTED || LA(2)==TOK_SELF || LA(2)==TOK_AND || 
LA(2)==TOK_ELIF || LA(2)==TOK_ELSE || LA(2)==TOK_IF || LA(2)==TOK_OR || LA(2)==TOK_RETURN || 
LA(2)==TOK_WHILE || LA(2)==TOK_DEBUG || LA(2)==TOK_ON || LA(2)==TOK_OFF || LA(2)==TOK_TRACE || 
LA(2)==TOK_STAT || LA(2)==TOK_DUMP || LA(2)==TOK_SOR || LA(2)==TOK_DOT || LA(2)==TOK_DOUBLECOLON || 
LA(2)==TOK_EQUAL || LA(2)==TOK_LPAREN || LA(2)==TOK_MINUS || LA(2)==TOK_PLUS || LA(2)==TOK_SEMI || 
LA(2)==TOK_QMARK || LA(2)==TOK_QUOTE || LA(2)==TOK_FRACTION || LA(2)==TOK_GENERAL_NAME || LA(2)==TOK_GARBAGE || 
LA(2)==TOK_BAD_ID || LA(2)==TOK_BAD_NAME || LA(2)==TOK_ID || LA(2)==TOK_RELID || LA(2)==TOK_NUMBER) && !( LA(1)==TOK_END && LA(2)==TOK_IF) ) {
					_ast = NULL;
					if_clause_statement(&_ast,&_signal); if (_signal) goto _handler;
					_ast31 = (AST *)_ast;
					stmt3_ast = _ast31;
					if ( !guessing ) {
					ASTBase::tmake( NULL, pa1->bottom(), stmt3_ast , NULL);
					}
				}
			}
			if ( !guessing ) {
			st = st->pop();
			pa2 = (new AST(TOK_CONTEXT_POP));
			pa2->setObjPtr( st );
			ASTBase::tmake( NULL, pa1->bottom(), pa2 , NULL);
			}
		}
	}
	{
		ANTLRTokenPtr _t21=NULL,_t22=NULL;
		AST *_ast21=NULL,*_ast22=NULL;
		if ( (
LA(1)==TOK_END) ) {
			zzmatch_wsig(TOK_END, _handler);			
			if ( !guessing ) {
			 _t21 = (ANTLRTokenPtr)LT(1);
}
 labase++;
			 consume();
			zzmatch_wsig(TOK_IF, _handler);			
			if ( !guessing ) {
			 _t22 = (ANTLRTokenPtr)LT(1);
}
 labase++;
			 consume();
		}
		else {
			if ( (LA(1)==Eof) ) {
				zzmatch_wsig(Eof, _handler);				
				if ( !guessing ) {
				 _t21 = (ANTLRTokenPtr)LT(1);
}
 labase++;
				
				if ( !guessing ) {
				AL_PARSE_ERR0( ifa, AL_GETMSG(ERR,004,0) )
				}
 consume();
			}
			else {
				if ( guessing ) goto fail;
				if (_sva) _signal=NoViableAlt;
				else _signal=NoSemViableAlt;
				goto _handler;  /* MR7 */
			}
		}
	}
	return;
fail:
	if ( guessing ) zzGUESS_FAIL;
	syn(zzBadTok, "if statement", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd3, 0x8);
_handler:
	zzdflthandlers(_signal,_retsignal);
	return;
}

void
P::implicit_assignment_statement(ASTBase **_root,int *_retsignal)
{
	zzRULE;
	int _sva=1;
	ASTBase *_ast = NULL, *_sibling = NULL, *_tail = NULL;
	AST *_ast11=NULL;
	ANTLRTokenPtr ae=NULL;
	AST *ae_ast=NULL;
	int _signal=NoSignal;
	*_retsignal = NoSignal;
	t_core_data_type t1;
	AST *c_ast = NULL;
	_ast = NULL;
	if ( !guessing ) {
		 t1  = assignment_expr(&_ast,&_signal); if (_signal) goto _handler;
		_ast11 = (AST *)_ast;
		ae_ast = _ast11;
	} else {
		assignment_expr(&_ast,&_signal);
	}
	if ( !guessing ) {
	
	c_ast = (new AST(TOK_STMT_ASSIGN, ae_ast));  // sets datatype and offset
	(*_root) = ASTBase::tmake( c_ast, ae_ast , NULL);
	}
	return;
fail:
	if ( guessing ) zzGUESS_FAIL;
	syn(zzBadTok, "assignment statement", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd3, 0x10);
_handler:
	zzdflthandlers(_signal,_retsignal);
	return;
}

void
P::implicit_bridge_or_transform_statement(ASTBase **_root,int *_retsignal)
{
	zzRULE;
	int _sva=1;
	ASTBase *_ast = NULL, *_sibling = NULL, *_tail = NULL;
	AST *_ast11=NULL;
	ANTLRTokenPtr bt=NULL;
	AST *bt_ast=NULL;
	int _signal=NoSignal;
	*_retsignal = NoSignal;
	ANTLRTokenType OorEE;
	t_core_data_type t;
	AST *s_ast;
	_ast = NULL;
	if ( !guessing ) {
		{ struct _rv40 _trv; _trv = bridge_or_transform_invocation(&_ast,&_signal, FALSE ); if (_signal) goto _handler;
		_ast11 = (AST *)_ast;
		t = _trv.t; OorEE  = _trv.OorEE; }
		bt_ast = _ast11;
	} else {
		bridge_or_transform_invocation(&_ast,&_signal, FALSE );
	}
	if ( !guessing ) {
	if ( OorEE == TOK_KL_OBJECT )
	s_ast = (new AST(TOK_STMT_TRANSFORM, bt_ast));  // set datatype and offset
	else   // ( OorEE == TOK_KL_EXTERNAL_ENTITY )
	s_ast = (new AST(TOK_STMT_BRIDGE, bt_ast));  // set datatype and offset
	(*_root) = ASTBase::tmake( s_ast, bt_ast , NULL);
	}
	return;
fail:
	if ( guessing ) zzGUESS_FAIL;
	syn(zzBadTok, "implicit bridge or transform statement", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd3, 0x20);
_handler:
	zzdflthandlers(_signal,_retsignal);
	return;
}

void
P::implicit_ib_transform_statement(ASTBase **_root,int *_retsignal)
{
	zzRULE;
	int _sva=1;
	ASTBase *_ast = NULL, *_sibling = NULL, *_tail = NULL;
	AST *_ast11=NULL;
	ANTLRTokenPtr tr=NULL;
	AST *tr_ast=NULL;
	int _signal=NoSignal;
	*_retsignal = NoSignal;
	t_core_data_type t;
	AST *s_ast;
	_ast = NULL;
	if ( !guessing ) {
		 t  = transform_ib_invocation(&_ast,&_signal, FALSE ); if (_signal) goto _handler;
		_ast11 = (AST *)_ast;
		tr_ast = _ast11;
	} else {
		transform_ib_invocation(&_ast,&_signal, FALSE );
	}
	if ( !guessing ) {
	
	s_ast = (new AST(TOK_STMT_TRANSFORM, tr_ast));  // set datatype and offset
	(*_root) = ASTBase::tmake( s_ast, tr_ast , NULL);
	}
	return;
fail:
	if ( guessing ) zzGUESS_FAIL;
	syn(zzBadTok, "implicit ib transform statement", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd3, 0x40);
_handler:
	zzdflthandlers(_signal,_retsignal);
	return;
}

void
P::relate_statement(ASTBase **_root,int *_retsignal)
{
	zzRULE;
	int _sva=1;
	ASTBase *_ast = NULL, *_sibling = NULL, *_tail = NULL;
	ANTLRTokenPtr _t11=NULL,_t13=NULL,_t15=NULL;
	AST *_ast11=NULL,*_ast12=NULL,*_ast13=NULL,*_ast14=NULL,*_ast15=NULL,*_ast16=NULL;
	ANTLRTokenPtr tr=NULL, ir1=NULL, ir2=NULL, rel=NULL, ph=NULL, airv=NULL;
	AST *tr_ast=NULL, *ir1_ast=NULL, *ir2_ast=NULL, *rel_ast=NULL, *ph_ast=NULL, *airv_ast=NULL;
	int _signal=NoSignal;
	*_retsignal = NoSignal;
	AST *t_ast;
	zzmatch_wsig(TOK_RELATE, _handler);	
	if ( !guessing ) {
	 _t11 = (ANTLRTokenPtr)LT(1);
}
 labase++;
	
	if ( !guessing ) {
		tr = _t11;
	}
	 consume();
	_ast = NULL;
	inst_ref_var(&_ast,&_signal); if (_signal) goto _handler;
	_ast12 = (AST *)_ast;
	ir1_ast = _ast12;
	zzmatch_wsig(TOK_TO, _handler);	
	if ( !guessing ) {
	 _t13 = (ANTLRTokenPtr)LT(1);
}
 labase++;
	 consume();
	_ast = NULL;
	inst_ref_var(&_ast,&_signal); if (_signal) goto _handler;
	_ast14 = (AST *)_ast;
	ir2_ast = _ast14;
	zzmatch_wsig(TOK_ACROSS, _handler);	
	if ( !guessing ) {
	 _t15 = (ANTLRTokenPtr)LT(1);
}
 labase++;
	 consume();
	_ast = NULL;
	relationship(&_ast,&_signal); if (_signal) goto _handler;
	_ast16 = (AST *)_ast;
	rel_ast = _ast16;
	{
		ANTLRTokenPtr _t21=NULL;
		AST *_ast21=NULL,*_ast22=NULL;
		if ( (LA(1)==TOK_DOT)
 ) {
			zzmatch_wsig(TOK_DOT, _handler);			
			if ( !guessing ) {
			 _t21 = (ANTLRTokenPtr)LT(1);
}
 labase++;
			 consume();
			_ast = NULL;
			phrase(&_ast,&_signal); if (_signal) goto _handler;
			_ast22 = (AST *)_ast;
			ph_ast = _ast22;
			if ( !guessing ) {
			ttr->add( ph_ast );
			}
		}
	}
	{
		ANTLRTokenPtr _t21=NULL;
		AST *_ast21=NULL,*_ast22=NULL;
		if ( (LA(1)==TOK_USING) ) {
			zzmatch_wsig(TOK_USING, _handler);			
			if ( !guessing ) {
			 _t21 = (ANTLRTokenPtr)LT(1);
}
 labase++;
			 consume();
			_ast = NULL;
			assoc_obj_inst_ref_var(&_ast,&_signal); if (_signal) goto _handler;
			_ast22 = (AST *)_ast;
			airv_ast = _ast22;
		}
	}
	if ( !guessing ) {
	if (!airv_ast)
	pck->validate_relate( rel_ast, ir1_ast, ir2_ast, ph_ast );
	else
	pck->validate_assoc_relate( rel_ast, ir1_ast, ir2_ast, airv_ast, ph_ast );
	t_ast = (new AST( tr, TOK_STMT_RELATE));
	if ( ph_ast )
	(*_root) = ASTBase::tmake( t_ast, ir1_ast, ir2_ast, rel_ast, ph_ast, airv_ast , NULL);
	else
	(*_root) = ASTBase::tmake( t_ast, ir1_ast, ir2_ast, rel_ast, airv_ast , NULL);
	}
	return;
fail:
	if ( guessing ) zzGUESS_FAIL;
	syn(zzBadTok, "relate statement", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd3, 0x80);
_handler:
	zzdflthandlers(_signal,_retsignal);
	return;
}

void
P::return_statement(ASTBase **_root,int *_retsignal)
{
	zzRULE;
	int _sva=1;
	ASTBase *_ast = NULL, *_sibling = NULL, *_tail = NULL;
	ANTLRTokenPtr _t11=NULL;
	AST *_ast11=NULL;
	ANTLRTokenPtr t=NULL, e=NULL;
	AST *t_ast=NULL, *e_ast=NULL;
	int _signal=NoSignal;
	*_retsignal = NoSignal;
	t_core_data_type dt;
	zzmatch_wsig(TOK_RETURN, _handler);	
	if ( !guessing ) {
	 _t11 = (ANTLRTokenPtr)LT(1);
}
 labase++;
	if ( !guessing ) {
	
	_ast11 = new AST(_t11);
	_ast11->subroot(_root, &_sibling, &_tail);
	}
	
	if ( !guessing ) {
		t = _t11;
	t_ast = _ast11;
	}
	
	if ( !guessing ) {
	t_ast->setType(TOK_STMT_RETURN);
	}
 consume();
	{
		AST *_ast21=NULL;
		if ( (LA(1)==TOK_ACROSS || LA(1)==TOK_ANY || 
LA(1)==TOK_ASSIGNER || LA(1)==TOK_ASSIGN || LA(1)==TOK_BREAKTOKEN || LA(1)==TOK_BY || LA(1)==TOK_CLASS || 
LA(1)==TOK_CONTINUE || LA(1)==TOK_CONTROL || LA(1)==TOK_CREATE || LA(1)==TOK_CREATOR || LA(1)==TOK_DELETE || 
LA(1)==TOK_EACH || LA(1)==TOK_END || LA(1)==TOK_EVENT || LA(1)==TOK_FOR || LA(1)==TOK_FROM || 
LA(1)==TOK_GENERATE || LA(1)==TOK_IN || LA(1)==TOK_INSTANCES || LA(1)==TOK_INSTANCE || LA(1)==TOK_MANY || 
LA(1)==TOK_OBJECT || LA(1)==TOK_OF || LA(1)==TOK_ONE || LA(1)==TOK_RELATED || LA(1)==TOK_RELATE || 
LA(1)==TOK_SELECT || LA(1)==TOK_STOP || LA(1)==TOK_TO || LA(1)==TOK_WHERE || LA(1)==TOK_UNRELATE || 
LA(1)==TOK_USING || LA(1)==TOK_BRIDGE || LA(1)==TOK_CARDINALITY || LA(1)==TOK_EMPTY || LA(1)==TOK_FALSETOKEN || 
LA(1)==TOK_NOT || LA(1)==TOK_NOTEMPTY || LA(1)==TOK_TRANSFORM || LA(1)==TOK_TRUETOKEN || LA(1)==TOK_PARAM || 
LA(1)==TOK_RCVD_EVT || LA(1)==TOK_SELECTED || LA(1)==TOK_SELF || LA(1)==TOK_DOUBLECOLON || LA(1)==TOK_LPAREN || 
LA(1)==TOK_MINUS || LA(1)==TOK_PLUS || LA(1)==TOK_QMARK || LA(1)==TOK_QUOTE || LA(1)==TOK_FRACTION || 
LA(1)==TOK_GENERAL_NAME || LA(1)==TOK_GARBAGE || LA(1)==TOK_BAD_ID || LA(1)==TOK_BAD_NAME || LA(1)==TOK_ID || 
LA(1)==TOK_RELID || LA(1)==TOK_NUMBER) ) {
			_ast = NULL;
			if ( !guessing ) {
				 dt  = expr(&_ast,&_signal); if (_signal) goto _handler;
				if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
				_ast21 = (AST *)_ast;
				ASTBase::link(_root, &_sibling, &_tail);
				e_ast = _ast21;
			} else {
				expr(&_ast,&_signal);
			}
		}
	}
	if ( !guessing ) {
	if (return_valid)
	{
		return_found = TRUE;
		pck->verify_return_type( dt, return_type_reqd, e_ast, spec_descr.char_ptr() );
	}
	else
	AL_PARSE_ERR1(e_ast, AL_GETMSG(ERR, 300, 1), t_ast->getVcharText())
	}
	return;
fail:
	if ( guessing ) zzGUESS_FAIL;
	syn(zzBadTok, "return statement", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd4, 0x1);
_handler:
	zzdflthandlers(_signal,_retsignal);
	return;
}

void
P::select_statement(ASTBase **_root,int *_retsignal)
{
	zzRULE;
	int _sva=1;
	ASTBase *_ast = NULL, *_sibling = NULL, *_tail = NULL;
	ANTLRTokenPtr _t11=NULL;
	AST *_ast11=NULL;
	ANTLRTokenPtr s1=NULL, irv1=NULL, os1=NULL, irv2=NULL, os2=NULL, irsv=NULL, os3=NULL;
	AST *s1_ast=NULL, *irv1_ast=NULL, *os1_ast=NULL, *irv2_ast=NULL, *os2_ast=NULL, *irsv_ast=NULL, *os3_ast=NULL;
	int _signal=NoSignal;
	*_retsignal = NoSignal;
	Sym *s_ref;
	persObjPtr obj;
	// An error message if the variable is already used as an
	// instance reference variable of a different object.  MSG:
	// "Cannot use previously defined variable for this select statement"
	zzmatch_wsig(TOK_SELECT, _handler);	
	if ( !guessing ) {
	 _t11 = (ANTLRTokenPtr)LT(1);
}
 labase++;
	
	if ( !guessing ) {
		s1 = _t11;
	}
	 consume();
	{
		ANTLRTokenPtr _t21=NULL;
		AST *_ast21=NULL,*_ast22=NULL,*_ast23=NULL;
		if ( (LA(1)==TOK_ONE) ) {
			zzmatch_wsig(TOK_ONE, _handler);			
			if ( !guessing ) {
			 _t21 = (ANTLRTokenPtr)LT(1);
}
 labase++;
			 consume();
			_ast = NULL;
			local_variable(&_ast,&_signal, ASSIGN_LVAL ); if (_signal) goto _handler;
			_ast22 = (AST *)_ast;
			irv1_ast = _ast22;
			_ast = NULL;
			if ( !guessing ) {
				 obj  = object_spec(&_ast,&_signal, CARD_ONE ); if (_signal) goto _handler;
				_ast23 = (AST *)_ast;
				os1_ast = _ast23;
			} else {
				object_spec(&_ast,&_signal, CARD_ONE );
			}
			if ( !guessing ) {
			irv1_ast->setType(TOK_INST_REF_VAR);
			s_ref = st->newadd( irv1_ast, OBJECT_INST_REF_DATATYPE, obj );
			// Error messages generated by newadd():
			//   Variable --> %s <-- already exists as a different type
			// Check to make sure no right objects have multiplicity of many
			(*_root) = ASTBase::tmake( (new AST( s1, TOK_STMT_SELECT_ONE)), irv1_ast, os1_ast , NULL);
			}
		}
		else {
			if ( (
LA(1)==TOK_ANY) ) {
				zzmatch_wsig(TOK_ANY, _handler);				
				if ( !guessing ) {
				 _t21 = (ANTLRTokenPtr)LT(1);
}
 labase++;
				 consume();
				_ast = NULL;
				local_variable(&_ast,&_signal, ASSIGN_LVAL ); if (_signal) goto _handler;
				_ast22 = (AST *)_ast;
				irv2_ast = _ast22;
				_ast = NULL;
				if ( !guessing ) {
					 obj  = object_spec(&_ast,&_signal, CARD_ANY ); if (_signal) goto _handler;
					_ast23 = (AST *)_ast;
					os2_ast = _ast23;
				} else {
					object_spec(&_ast,&_signal, CARD_ANY );
				}
				if ( !guessing ) {
				irv2_ast->setType(TOK_INST_REF_VAR);
				s_ref = st->newadd( irv2_ast, OBJECT_INST_REF_DATATYPE, obj );
				(*_root) = ASTBase::tmake( (new AST( s1, TOK_STMT_SELECT_ANY)), irv2_ast, os2_ast , NULL);
				}
			}
			else {
				if ( (LA(1)==TOK_MANY) ) {
					zzmatch_wsig(TOK_MANY, _handler);					
					if ( !guessing ) {
					 _t21 = (ANTLRTokenPtr)LT(1);
}
 labase++;
					 consume();
					_ast = NULL;
					local_variable(&_ast,&_signal, ASSIGN_LVAL ); if (_signal) goto _handler;
					_ast22 = (AST *)_ast;
					irsv_ast = _ast22;
					_ast = NULL;
					if ( !guessing ) {
						 obj  = object_spec(&_ast,&_signal, CARD_MANY ); if (_signal) goto _handler;
						_ast23 = (AST *)_ast;
						os3_ast = _ast23;
					} else {
						object_spec(&_ast,&_signal, CARD_MANY );
					}
					if ( !guessing ) {
					irsv_ast->setType(TOK_INST_REF_SET_VAR);
					s_ref = st->newadd( irsv_ast, OBJECT_INST_REF_SET_DATATYPE, obj );
					(*_root) = ASTBase::tmake( (new AST( s1, TOK_STMT_SELECT_MANY)), irsv_ast, os3_ast , NULL);
					}
				}
				else {
					if ( guessing ) goto fail;
					if (_sva) _signal=NoViableAlt;
					else _signal=NoSemViableAlt;
					goto _handler;  /* MR7 */
				}
			}
		}
	}
	return;
fail:
	if ( guessing ) zzGUESS_FAIL;
	syn(zzBadTok, "select statement", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd4, 0x2);
_handler:
	zzdflthandlers(_signal,_retsignal);
	return;
}

void
P::synch_svc_statement(ASTBase **_root,int *_retsignal)
{
	zzRULE;
	int _sva=1;
	ASTBase *_ast = NULL, *_sibling = NULL, *_tail = NULL;
	ANTLRTokenPtr _t11=NULL;
	AST *_ast11=NULL,*_ast12=NULL;
	ANTLRTokenPtr ss=NULL;
	AST *ss_ast=NULL;
	int _signal=NoSignal;
	*_retsignal = NoSignal;
	t_core_data_type t;
	AST *s_ast;
	zzmatch_wsig(TOK_DOUBLECOLON, _handler);	
	if ( !guessing ) {
	 _t11 = (ANTLRTokenPtr)LT(1);
}
 labase++;
	 consume();
	_ast = NULL;
	if ( !guessing ) {
		 t  = synch_svc_invocation(&_ast,&_signal, FALSE ); if (_signal) goto _handler;
		_ast12 = (AST *)_ast;
		ss_ast = _ast12;
	} else {
		synch_svc_invocation(&_ast,&_signal, FALSE );
	}
	if ( !guessing ) {
	
	s_ast = (new AST(TOK_STMT_SYNCH_SVC, ss_ast));  // set datatype and offset
	(*_root) = ASTBase::tmake( s_ast, ss_ast , NULL);
	}
	return;
fail:
	if ( guessing ) zzGUESS_FAIL;
	syn(zzBadTok, "synchronous service statement", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd4, 0x4);
_handler:
	zzdflthandlers(_signal,_retsignal);
	return;
}

void
P::transform_statement(ASTBase **_root,int *_retsignal)
{
	zzRULE;
	int _sva=1;
	ASTBase *_ast = NULL, *_sibling = NULL, *_tail = NULL;
	ANTLRTokenPtr _t11=NULL;
	AST *_ast11=NULL;
	ANTLRTokenPtr tt=NULL, aa=NULL, lv=NULL, tr1=NULL, tr2=NULL;
	AST *tt_ast=NULL, *aa_ast=NULL, *lv_ast=NULL, *tr1_ast=NULL, *tr2_ast=NULL;
	int _signal=NoSignal;
	*_retsignal = NoSignal;
	t_core_data_type t1;
	t_core_data_type t2;
	bool requiresReturnValue = FALSE;
	AST *s_ast;
	AST *t_ast;
	AST *tr_ast;
	zzmatch_wsig(TOK_TRANSFORM, _handler);	
	if ( !guessing ) {
	 _t11 = (ANTLRTokenPtr)LT(1);
}
 labase++;
	
	if ( !guessing ) {
		tt = _t11;
	}
	 consume();
	{
		ANTLRTokenPtr _t22=NULL,_t23=NULL;
		AST *_ast21=NULL,*_ast22=NULL,*_ast23=NULL;
		zzGUESS_BLOCK
		zzGUESS
		if ( !zzrv && (LA(1)==TOK_ACROSS || 
LA(1)==TOK_ANY || LA(1)==TOK_ASSIGNER || LA(1)==TOK_ASSIGN || LA(1)==TOK_BREAKTOKEN || LA(1)==TOK_BY || 
LA(1)==TOK_CLASS || LA(1)==TOK_CONTINUE || LA(1)==TOK_CONTROL || LA(1)==TOK_CREATE || LA(1)==TOK_CREATOR || 
LA(1)==TOK_DELETE || LA(1)==TOK_EACH || LA(1)==TOK_END || LA(1)==TOK_EVENT || LA(1)==TOK_FOR || 
LA(1)==TOK_FROM || LA(1)==TOK_GENERATE || LA(1)==TOK_IN || LA(1)==TOK_INSTANCES || LA(1)==TOK_INSTANCE || 
LA(1)==TOK_MANY || LA(1)==TOK_OBJECT || LA(1)==TOK_OF || LA(1)==TOK_ONE || LA(1)==TOK_RELATED || 
LA(1)==TOK_RELATE || LA(1)==TOK_SELECT || LA(1)==TOK_STOP || LA(1)==TOK_TO || LA(1)==TOK_WHERE || 
LA(1)==TOK_UNRELATE || LA(1)==TOK_USING || LA(1)==TOK_SELECTED || LA(1)==TOK_SELF || LA(1)==TOK_GARBAGE || 
LA(1)==TOK_BAD_ID || LA(1)==TOK_BAD_NAME || LA(1)==TOK_ID || LA(1)==TOK_RELID) && (
LA(2)==TOK_DOT) ) {
			{
				ANTLRTokenPtr _t32=NULL;
				AST *_ast31=NULL,*_ast32=NULL;
				_ast = NULL;
				if ( !guessing ) {
					 t1  = attribute_access(&_ast,&_signal, ASSIGN_LVAL ); if (_signal) goto _handler;
					_ast31 = (AST *)_ast;
				} else {
					attribute_access(&_ast,&_signal, ASSIGN_LVAL );
				}
				zzmatch_wsig(TOK_EQUAL, _handler);				
				if ( !guessing ) {
				 _t32 = (ANTLRTokenPtr)LT(1);
}
 labase++;
				 consume();
			}
			zzGUESS_DONE
			_ast = NULL;
			if ( !guessing ) {
				 t1  = attribute_access(&_ast,&_signal, ASSIGN_LVAL ); if (_signal) goto _handler;
				_ast22 = (AST *)_ast;
				aa_ast = _ast22;
			} else {
				attribute_access(&_ast,&_signal, ASSIGN_LVAL );
			}
			zzmatch_wsig(TOK_EQUAL, _handler);			
			if ( !guessing ) {
			 _t23 = (ANTLRTokenPtr)LT(1);
}
 labase++;
			
			if ( !guessing ) {
			requiresReturnValue = TRUE;
			}
 consume();
		}
		else {
			if ( !zzrv ) zzGUESS_DONE;
			if ( (LA(1)==TOK_ACROSS || LA(1)==TOK_ANY || LA(1)==TOK_ASSIGNER || LA(1)==TOK_ASSIGN || 
LA(1)==TOK_BREAKTOKEN || LA(1)==TOK_BY || LA(1)==TOK_CLASS || LA(1)==TOK_CONTINUE || LA(1)==TOK_CONTROL || 
LA(1)==TOK_CREATE || LA(1)==TOK_CREATOR || LA(1)==TOK_DELETE || LA(1)==TOK_EACH || LA(1)==TOK_END || 
LA(1)==TOK_EVENT || LA(1)==TOK_FOR || LA(1)==TOK_FROM || LA(1)==TOK_GENERATE || LA(1)==TOK_IN || 
LA(1)==TOK_INSTANCES || LA(1)==TOK_INSTANCE || LA(1)==TOK_MANY || LA(1)==TOK_OBJECT || LA(1)==TOK_OF || 
LA(1)==TOK_ONE || LA(1)==TOK_RELATED || LA(1)==TOK_RELATE || LA(1)==TOK_SELECT || LA(1)==TOK_STOP || 
LA(1)==TOK_TO || LA(1)==TOK_WHERE || LA(1)==TOK_UNRELATE || LA(1)==TOK_USING || LA(1)==TOK_SELECTED || 
LA(1)==TOK_SELF || LA(1)==TOK_GARBAGE || LA(1)==TOK_BAD_ID || LA(1)==TOK_BAD_NAME || LA(1)==TOK_ID || 
LA(1)==TOK_RELID) && (LA(2)==TOK_EQUAL) ) {
				_ast = NULL;
				local_variable(&_ast,&_signal, ASSIGN_LVAL ); if (_signal) goto _handler;
				_ast21 = (AST *)_ast;
				lv_ast = _ast21;
				zzmatch_wsig(TOK_EQUAL, _handler);				
				if ( !guessing ) {
				 _t22 = (ANTLRTokenPtr)LT(1);
}
 labase++;
				
				if ( !guessing ) {
				requiresReturnValue = TRUE;
				}
 consume();
			}
			else if ( !zzrv ) zzGUESS_DONE;
		}
	}
	{
		AST *_ast21=NULL,*_ast22=NULL;
		zzGUESS_BLOCK
		zzGUESS
		if ( !zzrv && (LA(1)==TOK_ACROSS || LA(1)==TOK_ANY || 
LA(1)==TOK_ASSIGNER || LA(1)==TOK_ASSIGN || LA(1)==TOK_BREAKTOKEN || LA(1)==TOK_BY || LA(1)==TOK_CLASS || 
LA(1)==TOK_CONTINUE || LA(1)==TOK_CONTROL || LA(1)==TOK_CREATE || LA(1)==TOK_CREATOR || LA(1)==TOK_DELETE || 
LA(1)==TOK_EACH || LA(1)==TOK_END || LA(1)==TOK_EVENT || LA(1)==TOK_FOR || LA(1)==TOK_FROM || 
LA(1)==TOK_GENERATE || LA(1)==TOK_IN || LA(1)==TOK_INSTANCES || LA(1)==TOK_INSTANCE || LA(1)==TOK_MANY || 
LA(1)==TOK_OBJECT || LA(1)==TOK_OF || LA(1)==TOK_ONE || LA(1)==TOK_RELATED || LA(1)==TOK_RELATE || 
LA(1)==TOK_SELECT || LA(1)==TOK_STOP || LA(1)==TOK_TO || LA(1)==TOK_WHERE || LA(1)==TOK_UNRELATE || 
LA(1)==TOK_USING || LA(1)==TOK_SELECTED || LA(1)==TOK_SELF || LA(1)==TOK_GARBAGE || LA(1)==TOK_BAD_ID || 
LA(1)==TOK_BAD_NAME || LA(1)==TOK_ID || LA(1)==TOK_RELID) && (LA(2)==TOK_DOT) ) {
			{
				AST *_ast31=NULL;
				_ast = NULL;
				if ( !guessing ) {
					 t2  = transform_ib_invocation(&_ast,&_signal, requiresReturnValue ); if (_signal) goto _handler;
					_ast31 = (AST *)_ast;
				} else {
					transform_ib_invocation(&_ast,&_signal, requiresReturnValue );
				}
			}
			zzGUESS_DONE
			_ast = NULL;
			if ( !guessing ) {
				 t2  = transform_ib_invocation(&_ast,&_signal, requiresReturnValue ); if (_signal) goto _handler;
				_ast22 = (AST *)_ast;
				tr1_ast = _ast22;
			} else {
				transform_ib_invocation(&_ast,&_signal, requiresReturnValue );
			}
			if ( !guessing ) {
			tr_ast = tr1_ast;
			}
		}
		else {
			if ( !zzrv ) zzGUESS_DONE;
			if ( (
LA(1)==TOK_ACROSS || LA(1)==TOK_ANY || LA(1)==TOK_ASSIGNER || LA(1)==TOK_ASSIGN || LA(1)==TOK_BREAKTOKEN || 
LA(1)==TOK_BY || LA(1)==TOK_CLASS || LA(1)==TOK_CONTINUE || LA(1)==TOK_CONTROL || LA(1)==TOK_CREATE || 
LA(1)==TOK_CREATOR || LA(1)==TOK_DELETE || LA(1)==TOK_EACH || LA(1)==TOK_END || LA(1)==TOK_EVENT || 
LA(1)==TOK_FOR || LA(1)==TOK_FROM || LA(1)==TOK_GENERATE || LA(1)==TOK_IN || LA(1)==TOK_INSTANCES || 
LA(1)==TOK_INSTANCE || LA(1)==TOK_MANY || LA(1)==TOK_OBJECT || LA(1)==TOK_OF || LA(1)==TOK_ONE || 
LA(1)==TOK_RELATED || LA(1)==TOK_RELATE || LA(1)==TOK_SELECT || LA(1)==TOK_STOP || LA(1)==TOK_TO || 
LA(1)==TOK_WHERE || LA(1)==TOK_UNRELATE || LA(1)==TOK_USING || LA(1)==TOK_BRIDGE || LA(1)==TOK_CARDINALITY || 
LA(1)==TOK_EMPTY || LA(1)==TOK_FALSETOKEN || LA(1)==TOK_NOT || LA(1)==TOK_NOTEMPTY || LA(1)==TOK_TRANSFORM || 
LA(1)==TOK_TRUETOKEN || LA(1)==TOK_PARAM || LA(1)==TOK_RCVD_EVT || LA(1)==TOK_SELECTED || LA(1)==TOK_SELF || 
LA(1)==TOK_GENERAL_NAME || LA(1)==TOK_GARBAGE || LA(1)==TOK_BAD_ID || LA(1)==TOK_BAD_NAME || LA(1)==TOK_ID || 
LA(1)==TOK_RELID) && (LA(2)==TOK_DOUBLECOLON) ) {
				_ast = NULL;
				if ( !guessing ) {
					 t2  = transform_invocation(&_ast,&_signal, requiresReturnValue ); if (_signal) goto _handler;
					_ast21 = (AST *)_ast;
					tr2_ast = _ast21;
				} else {
					transform_invocation(&_ast,&_signal, requiresReturnValue );
				}
				if ( !guessing ) {
				tr_ast = tr2_ast;
				}
			}
			else {
				if ( guessing ) goto fail;
				if (_sva) _signal=NoViableAlt;
				else _signal=NoSemViableAlt;
				goto _handler;  /* MR7 */
			}
		}
	}
	if ( !guessing ) {
	if ( lv_ast )
	{
		st->newadd( lv_ast, t2, tr_ast );
		s_ast = (new AST( tt, TOK_STMT_ASSIGN));
		t_ast = (new AST(TOK_EXPRESSION, tr_ast));  // sets datatype and offset
		t_ast->setSegLength(tr_ast->getSegLength());
		(*_root) = ASTBase::tmake( s_ast, lv_ast, ASTBase::tmake( t_ast, tr_ast, NULL) , NULL);
	}
	else if (aa_ast)
	{
		bool mismatch = FALSE;
		if ( accum_datatype( aa_ast, tr_ast, t1, t2, mismatch ) )
		AL_PARSE_ERR0( aa_ast, AL_GETMSG(ERR,274,0) )
		s_ast = (new AST( tt, TOK_STMT_ASSIGN));
		t_ast = (new AST(TOK_EXPRESSION, tr_ast));  // sets datatype and offset
		t_ast->setSegLength(tr_ast->getSegLength());
		(*_root) = ASTBase::tmake( s_ast, aa_ast, ASTBase::tmake( t_ast, tr_ast, NULL) , NULL);
	}
	else
	{
		s_ast = (new AST( tt, TOK_STMT_TRANSFORM));
		(*_root) = ASTBase::tmake( s_ast, tr_ast , NULL);
	}
	}
	return;
fail:
	if ( guessing ) zzGUESS_FAIL;
	syn(zzBadTok, "transform statement", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd4, 0x8);
_handler:
	zzdflthandlers(_signal,_retsignal);
	return;
}

void
P::unrelate_statement(ASTBase **_root,int *_retsignal)
{
	zzRULE;
	int _sva=1;
	ASTBase *_ast = NULL, *_sibling = NULL, *_tail = NULL;
	ANTLRTokenPtr _t11=NULL,_t13=NULL,_t15=NULL;
	AST *_ast11=NULL,*_ast12=NULL,*_ast13=NULL,*_ast14=NULL,*_ast15=NULL,*_ast16=NULL;
	ANTLRTokenPtr tu=NULL, ir1=NULL, ir2=NULL, rel=NULL, ph=NULL, airv=NULL;
	AST *tu_ast=NULL, *ir1_ast=NULL, *ir2_ast=NULL, *rel_ast=NULL, *ph_ast=NULL, *airv_ast=NULL;
	int _signal=NoSignal;
	*_retsignal = NoSignal;
	AST *t_ast;
	zzmatch_wsig(TOK_UNRELATE, _handler);	
	if ( !guessing ) {
	 _t11 = (ANTLRTokenPtr)LT(1);
}
 labase++;
	
	if ( !guessing ) {
		tu = _t11;
	}
	 consume();
	_ast = NULL;
	inst_ref_var(&_ast,&_signal); if (_signal) goto _handler;
	_ast12 = (AST *)_ast;
	ir1_ast = _ast12;
	zzmatch_wsig(TOK_FROM, _handler);	
	if ( !guessing ) {
	 _t13 = (ANTLRTokenPtr)LT(1);
}
 labase++;
	 consume();
	_ast = NULL;
	inst_ref_var(&_ast,&_signal); if (_signal) goto _handler;
	_ast14 = (AST *)_ast;
	ir2_ast = _ast14;
	zzmatch_wsig(TOK_ACROSS, _handler);	
	if ( !guessing ) {
	 _t15 = (ANTLRTokenPtr)LT(1);
}
 labase++;
	 consume();
	_ast = NULL;
	relationship(&_ast,&_signal); if (_signal) goto _handler;
	_ast16 = (AST *)_ast;
	rel_ast = _ast16;
	{
		ANTLRTokenPtr _t21=NULL;
		AST *_ast21=NULL,*_ast22=NULL;
		if ( (LA(1)==TOK_DOT) ) {
			zzmatch_wsig(TOK_DOT, _handler);			
			if ( !guessing ) {
			 _t21 = (ANTLRTokenPtr)LT(1);
}
 labase++;
			 consume();
			_ast = NULL;
			phrase(&_ast,&_signal); if (_signal) goto _handler;
			_ast22 = (AST *)_ast;
			ph_ast = _ast22;
			if ( !guessing ) {
			ttr->add( ph_ast );
			}
		}
	}
	{
		ANTLRTokenPtr _t21=NULL;
		AST *_ast21=NULL,*_ast22=NULL;
		if ( (
LA(1)==TOK_USING) ) {
			zzmatch_wsig(TOK_USING, _handler);			
			if ( !guessing ) {
			 _t21 = (ANTLRTokenPtr)LT(1);
}
 labase++;
			 consume();
			_ast = NULL;
			assoc_obj_inst_ref_var(&_ast,&_signal); if (_signal) goto _handler;
			_ast22 = (AST *)_ast;
			airv_ast = _ast22;
		}
	}
	if ( !guessing ) {
	if (!airv_ast)
	pck->validate_relate( rel_ast, ir1_ast, ir2_ast, ph_ast );
	else
	pck->validate_assoc_relate( rel_ast, ir1_ast, ir2_ast, airv_ast, ph_ast );
	t_ast = (new AST( tu, TOK_STMT_UNRELATE));
	if ( ph_ast )
	(*_root) = ASTBase::tmake( t_ast, ir1_ast, ir2_ast, rel_ast, ph_ast, airv_ast , NULL);
	else
	(*_root) = ASTBase::tmake( t_ast, ir1_ast, ir2_ast, rel_ast, airv_ast , NULL);
	}
	return;
fail:
	if ( guessing ) zzGUESS_FAIL;
	syn(zzBadTok, "unrelate statement", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd4, 0x10);
_handler:
	zzdflthandlers(_signal,_retsignal);
	return;
}

void
P::while_statement(ASTBase **_root,int *_retsignal)
{
	zzRULE;
	int _sva=1;
	ASTBase *_ast = NULL, *_sibling = NULL, *_tail = NULL;
	ANTLRTokenPtr _t11=NULL;
	AST *_ast11=NULL,*_ast12=NULL;
	ANTLRTokenPtr w=NULL, e=NULL, stmt=NULL;
	AST *w_ast=NULL, *e_ast=NULL, *stmt_ast=NULL;
	int _signal=NoSignal;
	*_retsignal = NoSignal;
	t_core_data_type t;
	AST *wa = NULL;
	AST *pa1;
	AST *pa2;
	zzmatch_wsig(TOK_WHILE, _handler);	
	if ( !guessing ) {
	 _t11 = (ANTLRTokenPtr)LT(1);
}
 labase++;
	
	if ( !guessing ) {
		w = _t11;
	}
	 consume();
	_ast = NULL;
	if ( !guessing ) {
		 t  = expr(&_ast,&_signal); if (_signal) goto _handler;
		_ast12 = (AST *)_ast;
		e_ast = _ast12;
	} else {
		expr(&_ast,&_signal);
	}
	if ( !guessing ) {
	st = st->push();
	wa = (new AST( w, TOK_STMT_WHILE));
	wa->setSegLength(e_ast->getOffset() +
	e_ast->getSegLength() -
	wa->getOffset());
	pa1 = (new AST(TOK_CONTEXT_PUSH));
	pa1->setObjPtr( st );
	(*_root) = ASTBase::tmake( wa, e_ast, ASTBase::tmake( (new AST(TOK_CLAUSE_WHILE)), pa1, NULL) , NULL);
	if ( t != BOOLEAN_DATATYPE )
	AL_PARSE_ERR0( wa, AL_GETMSG(ERR,016,0) )
	loop_clause_nest_level++;
	}
	{
		AST *_ast21=NULL;
		while ( (LA(1)==TOK_ACROSS || LA(1)==TOK_ANY || LA(1)==TOK_ASSIGNER || 
LA(1)==TOK_ASSIGN || LA(1)==TOK_BREAKTOKEN || LA(1)==TOK_BY || LA(1)==TOK_CLASS || LA(1)==TOK_CONTINUE || 
LA(1)==TOK_CONTROL || LA(1)==TOK_CREATE || LA(1)==TOK_CREATOR || LA(1)==TOK_DELETE || LA(1)==TOK_EACH || 
LA(1)==TOK_END || LA(1)==TOK_EVENT || LA(1)==TOK_FOR || LA(1)==TOK_FROM || LA(1)==TOK_GENERATE || 
LA(1)==TOK_IN || LA(1)==TOK_INSTANCES || LA(1)==TOK_INSTANCE || LA(1)==TOK_MANY || LA(1)==TOK_OBJECT || 
LA(1)==TOK_OF || LA(1)==TOK_ONE || LA(1)==TOK_RELATED || LA(1)==TOK_RELATE || LA(1)==TOK_SELECT || 
LA(1)==TOK_STOP || LA(1)==TOK_TO || LA(1)==TOK_WHERE || LA(1)==TOK_UNRELATE || LA(1)==TOK_USING || 
LA(1)==TOK_BRIDGE || LA(1)==TOK_CARDINALITY || LA(1)==TOK_EMPTY || LA(1)==TOK_FALSETOKEN || LA(1)==TOK_NOT || 
LA(1)==TOK_NOTEMPTY || LA(1)==TOK_TRANSFORM || LA(1)==TOK_TRUETOKEN || LA(1)==TOK_PARAM || LA(1)==TOK_RCVD_EVT || 
LA(1)==TOK_SELECTED || LA(1)==TOK_SELF || LA(1)==TOK_IF || LA(1)==TOK_RETURN || LA(1)==TOK_WHILE || 
LA(1)==TOK_DEBUG || LA(1)==TOK_DOUBLECOLON || LA(1)==TOK_SEMI || LA(1)==TOK_GENERAL_NAME || LA(1)==TOK_GARBAGE || 
LA(1)==TOK_BAD_ID || LA(1)==TOK_BAD_NAME || LA(1)==TOK_ID || LA(1)==TOK_RELID) && (
LA(2)==Eof || LA(2)==TOK_ACROSS || LA(2)==TOK_ANY || LA(2)==TOK_ASSIGNER || LA(2)==TOK_ASSIGN || 
LA(2)==TOK_BREAKTOKEN || LA(2)==TOK_BY || LA(2)==TOK_CLASS || LA(2)==TOK_CONTINUE || LA(2)==TOK_CONTROL || 
LA(2)==TOK_CREATE || LA(2)==TOK_CREATOR || LA(2)==TOK_DELETE || LA(2)==TOK_EACH || LA(2)==TOK_END || 
LA(2)==TOK_EVENT || LA(2)==TOK_FOR || LA(2)==TOK_FROM || LA(2)==TOK_GENERATE || LA(2)==TOK_IN || 
LA(2)==TOK_INSTANCES || LA(2)==TOK_INSTANCE || LA(2)==TOK_MANY || LA(2)==TOK_OBJECT || LA(2)==TOK_OF || 
LA(2)==TOK_ONE || LA(2)==TOK_RELATED || LA(2)==TOK_RELATE || LA(2)==TOK_SELECT || LA(2)==TOK_STOP || 
LA(2)==TOK_TO || LA(2)==TOK_WHERE || LA(2)==TOK_UNRELATE || LA(2)==TOK_USING || LA(2)==TOK_BRIDGE || 
LA(2)==TOK_CARDINALITY || LA(2)==TOK_EMPTY || LA(2)==TOK_FALSETOKEN || LA(2)==TOK_NOT || LA(2)==TOK_NOTEMPTY || 
LA(2)==TOK_TRANSFORM || LA(2)==TOK_TRUETOKEN || LA(2)==TOK_PARAM || LA(2)==TOK_RCVD_EVT || LA(2)==TOK_SELECTED || 
LA(2)==TOK_SELF || LA(2)==TOK_AND || LA(2)==TOK_ELIF || LA(2)==TOK_ELSE || LA(2)==TOK_IF || 
LA(2)==TOK_OR || LA(2)==TOK_RETURN || LA(2)==TOK_WHILE || LA(2)==TOK_DEBUG || LA(2)==TOK_ON || 
LA(2)==TOK_OFF || LA(2)==TOK_TRACE || LA(2)==TOK_STAT || LA(2)==TOK_DUMP || LA(2)==TOK_SOR || 
LA(2)==TOK_DOT || LA(2)==TOK_DOUBLECOLON || LA(2)==TOK_EQUAL || LA(2)==TOK_LPAREN || LA(2)==TOK_MINUS || 
LA(2)==TOK_PLUS || LA(2)==TOK_SEMI || LA(2)==TOK_QMARK || LA(2)==TOK_QUOTE || LA(2)==TOK_FRACTION || 
LA(2)==TOK_GENERAL_NAME || LA(2)==TOK_GARBAGE || LA(2)==TOK_BAD_ID || LA(2)==TOK_BAD_NAME || LA(2)==TOK_ID || 
LA(2)==TOK_RELID || LA(2)==TOK_NUMBER) && !( LA(1)==TOK_END && LA(2)==TOK_WHILE) ) {
			_ast = NULL;
			while_clause_statement(&_ast,&_signal); if (_signal) goto _handler;
			_ast21 = (AST *)_ast;
			stmt_ast = _ast21;
			if ( !guessing ) {
			ASTBase::tmake( NULL, pa1->bottom(), stmt_ast , NULL);
			}
		}
	}
	if ( !guessing ) {
	loop_clause_nest_level--;
	st = st->pop();
	pa2 = (new AST(TOK_CONTEXT_POP));
	pa2->setObjPtr( st );
	ASTBase::tmake( NULL, pa1->bottom(), pa2 , NULL);
	}
	{
		ANTLRTokenPtr _t21=NULL,_t22=NULL;
		AST *_ast21=NULL,*_ast22=NULL;
		if ( (LA(1)==TOK_END) ) {
			zzmatch_wsig(TOK_END, _handler);			
			if ( !guessing ) {
			 _t21 = (ANTLRTokenPtr)LT(1);
}
 labase++;
			 consume();
			zzmatch_wsig(TOK_WHILE, _handler);			
			if ( !guessing ) {
			 _t22 = (ANTLRTokenPtr)LT(1);
}
 labase++;
			 consume();
		}
		else {
			if ( (LA(1)==Eof)
 ) {
				zzmatch_wsig(Eof, _handler);				
				if ( !guessing ) {
				 _t21 = (ANTLRTokenPtr)LT(1);
}
 labase++;
				
				if ( !guessing ) {
				AL_PARSE_ERR0( wa, AL_GETMSG(ERR,008,0) )
				}
 consume();
			}
			else {
				if ( guessing ) goto fail;
				if (_sva) _signal=NoViableAlt;
				else _signal=NoSemViableAlt;
				goto _handler;  /* MR7 */
			}
		}
	}
	return;
fail:
	if ( guessing ) zzGUESS_FAIL;
	syn(zzBadTok, "while statement", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd4, 0x20);
_handler:
	zzdflthandlers(_signal,_retsignal);
	return;
}

void
P::unmatched_else_statement(ASTBase **_root,int *_retsignal)
{
	zzRULE;
	int _sva=1;
	ASTBase *_ast = NULL, *_sibling = NULL, *_tail = NULL;
	ANTLRTokenPtr _t11=NULL;
	AST *_ast11=NULL;
	ANTLRTokenPtr e=NULL;
	AST *e_ast=NULL;
	int _signal=NoSignal;
	*_retsignal = NoSignal;
	AST *a = NULL;
	zzmatch_wsig(TOK_ELSE, _handler);	
	if ( !guessing ) {
	 _t11 = (ANTLRTokenPtr)LT(1);
}
 labase++;
	
	if ( !guessing ) {
		e = _t11;
	}
	
	if ( !guessing ) {
	a = (new AST( e));
	AL_PARSE_ERR0( a, AL_GETMSG(ERR,002,0) )
	delete a;
	}
 consume();
	return;
fail:
	if ( guessing ) zzGUESS_FAIL;
	syn(zzBadTok, "unmatched else statement", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd4, 0x40);
_handler:
	zzdflthandlers(_signal,_retsignal);
	return;
}

void
P::unmatched_elif_statement(ASTBase **_root,int *_retsignal)
{
	zzRULE;
	int _sva=1;
	ASTBase *_ast = NULL, *_sibling = NULL, *_tail = NULL;
	ANTLRTokenPtr _t11=NULL;
	AST *_ast11=NULL,*_ast12=NULL;
	ANTLRTokenPtr e=NULL;
	AST *e_ast=NULL;
	int _signal=NoSignal;
	*_retsignal = NoSignal;
	t_core_data_type t;
	AST *a = NULL;
	zzmatch_wsig(TOK_ELIF, _handler);	
	if ( !guessing ) {
	 _t11 = (ANTLRTokenPtr)LT(1);
}
 labase++;
	
	if ( !guessing ) {
		e = _t11;
	}
	 consume();
	_ast = NULL;
	if ( !guessing ) {
		 t  = expr(&_ast,&_signal); if (_signal) goto _handler;
		_ast12 = (AST *)_ast;
	} else {
		expr(&_ast,&_signal);
	}
	if ( !guessing ) {
	a = (new AST( e));
	AL_PARSE_ERR0( a, AL_GETMSG(ERR,007,0) )
	delete a;
	}
	return;
fail:
	if ( guessing ) zzGUESS_FAIL;
	syn(zzBadTok, "unmatched elif statement", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd4, 0x80);
_handler:
	zzdflthandlers(_signal,_retsignal);
	return;
}

void
P::unmatched_end_statement(ASTBase **_root,int *_retsignal)
{
	zzRULE;
	int _sva=1;
	ASTBase *_ast = NULL, *_sibling = NULL, *_tail = NULL;
;
	ANTLRTokenPtr e=NULL;
	AST *e_ast=NULL;
	int _signal=NoSignal;
	*_retsignal = NoSignal;
	AST *a = NULL;
	{
		ANTLRTokenPtr _t21=NULL;
		AST *_ast21=NULL;
		zzmatch_wsig(TOK_END, _handler);		
		if ( !guessing ) {
		 _t21 = (ANTLRTokenPtr)LT(1);
}
 labase++;
		
		if ( !guessing ) {
				e = _t21;
		}
		 consume();
		{
			ANTLRTokenPtr _t31=NULL;
			AST *_ast31=NULL;
			if ( (LA(1)==TOK_FOR) ) {
				zzmatch_wsig(TOK_FOR, _handler);				
				if ( !guessing ) {
				 _t31 = (ANTLRTokenPtr)LT(1);
}
 labase++;
				 consume();
			}
			else {
				if ( (LA(1)==TOK_IF) ) {
					zzmatch_wsig(TOK_IF, _handler);					
					if ( !guessing ) {
					 _t31 = (ANTLRTokenPtr)LT(1);
}
 labase++;
					 consume();
				}
				else {
					if ( (
LA(1)==TOK_WHILE) ) {
						zzmatch_wsig(TOK_WHILE, _handler);						
						if ( !guessing ) {
						 _t31 = (ANTLRTokenPtr)LT(1);
}
 labase++;
						 consume();
					}
					else {
						if ( guessing ) goto fail;
						if (_sva) _signal=NoViableAlt;
						else _signal=NoSemViableAlt;
						goto _handler;  /* MR7 */
					}
				}
			}
		}
	}
	if ( !guessing ) {
	a = (new AST( e));
	AL_PARSE_ERR0( a, AL_GETMSG(ERR,001,0) )
	delete a;
	}
	return;
fail:
	if ( guessing ) zzGUESS_FAIL;
	syn(zzBadTok, "unmatched end statement", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd5, 0x1);
_handler:
	zzdflthandlers(_signal,_retsignal);
	return;
}

void
P::unmatched_end_in_for_clause(ASTBase **_root,int *_retsignal)
{
	zzRULE;
	int _sva=1;
	ASTBase *_ast = NULL, *_sibling = NULL, *_tail = NULL;
;
	ANTLRTokenPtr e=NULL;
	AST *e_ast=NULL;
	int _signal=NoSignal;
	*_retsignal = NoSignal;
	AST *a = NULL;
	{
		ANTLRTokenPtr _t21=NULL;
		AST *_ast21=NULL;
		zzmatch_wsig(TOK_END, _handler);		
		if ( !guessing ) {
		 _t21 = (ANTLRTokenPtr)LT(1);
}
 labase++;
		
		if ( !guessing ) {
				e = _t21;
		}
		 consume();
		{
			ANTLRTokenPtr _t31=NULL;
			AST *_ast31=NULL;
			if ( (LA(1)==TOK_IF) ) {
				zzmatch_wsig(TOK_IF, _handler);				
				if ( !guessing ) {
				 _t31 = (ANTLRTokenPtr)LT(1);
}
 labase++;
				 consume();
			}
			else {
				if ( (LA(1)==TOK_WHILE)
 ) {
					zzmatch_wsig(TOK_WHILE, _handler);					
					if ( !guessing ) {
					 _t31 = (ANTLRTokenPtr)LT(1);
}
 labase++;
					 consume();
				}
				else {
					if ( guessing ) goto fail;
					if (_sva) _signal=NoViableAlt;
					else _signal=NoSemViableAlt;
					goto _handler;  /* MR7 */
				}
			}
		}
	}
	if ( !guessing ) {
	a = (new AST( e));
	AL_PARSE_ERR0( a, AL_GETMSG(ERR,003,0) )
	delete a;
	}
	return;
fail:
	if ( guessing ) zzGUESS_FAIL;
	syn(zzBadTok, "unmatched end statement in for clause", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd5, 0x2);
_handler:
	zzdflthandlers(_signal,_retsignal);
	return;
}

void
P::unmatched_end_in_if_clause(ASTBase **_root,int *_retsignal)
{
	zzRULE;
	int _sva=1;
	ASTBase *_ast = NULL, *_sibling = NULL, *_tail = NULL;
;
	ANTLRTokenPtr e=NULL;
	AST *e_ast=NULL;
	int _signal=NoSignal;
	*_retsignal = NoSignal;
	AST *a = NULL;
	{
		ANTLRTokenPtr _t21=NULL;
		AST *_ast21=NULL;
		zzmatch_wsig(TOK_END, _handler);		
		if ( !guessing ) {
		 _t21 = (ANTLRTokenPtr)LT(1);
}
 labase++;
		
		if ( !guessing ) {
				e = _t21;
		}
		 consume();
		{
			ANTLRTokenPtr _t31=NULL;
			AST *_ast31=NULL;
			if ( (LA(1)==TOK_FOR) ) {
				zzmatch_wsig(TOK_FOR, _handler);				
				if ( !guessing ) {
				 _t31 = (ANTLRTokenPtr)LT(1);
}
 labase++;
				 consume();
			}
			else {
				if ( (LA(1)==TOK_WHILE) ) {
					zzmatch_wsig(TOK_WHILE, _handler);					
					if ( !guessing ) {
					 _t31 = (ANTLRTokenPtr)LT(1);
}
 labase++;
					 consume();
				}
				else {
					if ( guessing ) goto fail;
					if (_sva) _signal=NoViableAlt;
					else _signal=NoSemViableAlt;
					goto _handler;  /* MR7 */
				}
			}
		}
	}
	if ( !guessing ) {
	a = (new AST( e));
	AL_PARSE_ERR0( a, AL_GETMSG(ERR,004,0) )
	delete a;
	}
	return;
fail:
	if ( guessing ) zzGUESS_FAIL;
	syn(zzBadTok, "unmatched end statement in if clause", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd5, 0x4);
_handler:
	zzdflthandlers(_signal,_retsignal);
	return;
}

void
P::unmatched_end_in_while_clause(ASTBase **_root,int *_retsignal)
{
	zzRULE;
	int _sva=1;
	ASTBase *_ast = NULL, *_sibling = NULL, *_tail = NULL;
;
	ANTLRTokenPtr e=NULL;
	AST *e_ast=NULL;
	int _signal=NoSignal;
	*_retsignal = NoSignal;
	AST *a = NULL;
	{
		ANTLRTokenPtr _t21=NULL;
		AST *_ast21=NULL;
		zzmatch_wsig(TOK_END, _handler);		
		if ( !guessing ) {
		 _t21 = (ANTLRTokenPtr)LT(1);
}
 labase++;
		
		if ( !guessing ) {
				e = _t21;
		}
		 consume();
		{
			ANTLRTokenPtr _t31=NULL;
			AST *_ast31=NULL;
			if ( (
LA(1)==TOK_FOR) ) {
				zzmatch_wsig(TOK_FOR, _handler);				
				if ( !guessing ) {
				 _t31 = (ANTLRTokenPtr)LT(1);
}
 labase++;
				 consume();
			}
			else {
				if ( (LA(1)==TOK_IF) ) {
					zzmatch_wsig(TOK_IF, _handler);					
					if ( !guessing ) {
					 _t31 = (ANTLRTokenPtr)LT(1);
}
 labase++;
					 consume();
				}
				else {
					if ( guessing ) goto fail;
					if (_sva) _signal=NoViableAlt;
					else _signal=NoSemViableAlt;
					goto _handler;  /* MR7 */
				}
			}
		}
	}
	if ( !guessing ) {
	a = (new AST( e));
	AL_PARSE_ERR0( a, AL_GETMSG(ERR,008,0) )
	delete a;
	}
	return;
fail:
	if ( guessing ) zzGUESS_FAIL;
	syn(zzBadTok, "unmatched end statement in while clause", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd5, 0x8);
_handler:
	zzdflthandlers(_signal,_retsignal);
	return;
}

 t_core_data_type  
P::assignment_expr(ASTBase **_root,int *_retsignal)
{
	 t_core_data_type  	 _retv;
	zzRULE;
	int _sva=1;
	ASTBase *_ast = NULL, *_sibling = NULL, *_tail = NULL;
	ANTLRTokenPtr _t12=NULL,_t13=NULL;
	AST *_ast11=NULL,*_ast12=NULL,*_ast13=NULL,*_ast14=NULL;
	ANTLRTokenPtr lv=NULL, ex1=NULL, aa=NULL, ex2=NULL, eda=NULL, ex3=NULL, pda=NULL, ex4=NULL;
	AST *lv_ast=NULL, *ex1_ast=NULL, *aa_ast=NULL, *ex2_ast=NULL, *eda_ast=NULL, *ex3_ast=NULL, *pda_ast=NULL, *ex4_ast=NULL;
	int _signal=NoSignal;
	PURIFY(_retv,sizeof( t_core_data_type  	))
	*_retsignal = NoSignal;
	zzGUESS_BLOCK
	t_core_data_type t1;
	t_core_data_type t2;
	zzGUESS
	if ( !zzrv && (LA(1)==TOK_ACROSS || 
LA(1)==TOK_ANY || LA(1)==TOK_ASSIGNER || LA(1)==TOK_ASSIGN || LA(1)==TOK_BREAKTOKEN || LA(1)==TOK_BY || 
LA(1)==TOK_CLASS || LA(1)==TOK_CONTINUE || LA(1)==TOK_CONTROL || LA(1)==TOK_CREATE || LA(1)==TOK_CREATOR || 
LA(1)==TOK_DELETE || LA(1)==TOK_EACH || LA(1)==TOK_END || LA(1)==TOK_EVENT || LA(1)==TOK_FOR || 
LA(1)==TOK_FROM || LA(1)==TOK_GENERATE || LA(1)==TOK_IN || LA(1)==TOK_INSTANCES || LA(1)==TOK_INSTANCE || 
LA(1)==TOK_MANY || LA(1)==TOK_OBJECT || LA(1)==TOK_OF || LA(1)==TOK_ONE || LA(1)==TOK_RELATED || 
LA(1)==TOK_RELATE || LA(1)==TOK_SELECT || LA(1)==TOK_STOP || LA(1)==TOK_TO || LA(1)==TOK_WHERE || 
LA(1)==TOK_UNRELATE || LA(1)==TOK_USING || LA(1)==TOK_SELECTED || LA(1)==TOK_SELF || LA(1)==TOK_GARBAGE || 
LA(1)==TOK_BAD_ID || LA(1)==TOK_BAD_NAME || LA(1)==TOK_ID || LA(1)==TOK_RELID) && (
LA(2)==TOK_EQUAL) ) {
		{
			ANTLRTokenPtr _t22=NULL;
			AST *_ast21=NULL,*_ast22=NULL;
			_ast = NULL;
			local_variable(&_ast,&_signal, ASSIGN_LVAL ); if (_signal) goto _handler;
			_ast21 = (AST *)_ast;
			zzmatch_wsig(TOK_EQUAL, _handler);			
			if ( !guessing ) {
			 _t22 = (ANTLRTokenPtr)LT(1);
}
 labase++;
			 consume();
		}
		zzGUESS_DONE
		_ast = NULL;
		local_variable(&_ast,&_signal, ASSIGN_LVAL ); if (_signal) goto _handler;
		_ast12 = (AST *)_ast;
		lv_ast = _ast12;
		zzmatch_wsig(TOK_EQUAL, _handler);		
		if ( !guessing ) {
		 _t13 = (ANTLRTokenPtr)LT(1);
}
 labase++;
		 consume();
		_ast = NULL;
		if ( !guessing ) {
			 _retv  = expr(&_ast,&_signal); if (_signal) goto _handler;
			_ast14 = (AST *)_ast;
			ex1_ast = _ast14;
		} else {
			expr(&_ast,&_signal);
		}
		if ( !guessing ) {
		// newadd() checks that datatypes are compatible
		st->newadd( lv_ast, _retv, ex1_ast );
		lv_ast->setDatatype(_retv);
		(*_root) = ASTBase::tmake( NULL, lv_ast, ex1_ast , NULL);
		}
	}
	else {
		if ( !zzrv ) zzGUESS_DONE;
		zzGUESS
		if ( !zzrv && (LA(1)==TOK_ACROSS || LA(1)==TOK_ANY || LA(1)==TOK_ASSIGNER || LA(1)==TOK_ASSIGN || 
LA(1)==TOK_BREAKTOKEN || LA(1)==TOK_BY || LA(1)==TOK_CLASS || LA(1)==TOK_CONTINUE || LA(1)==TOK_CONTROL || 
LA(1)==TOK_CREATE || LA(1)==TOK_CREATOR || LA(1)==TOK_DELETE || LA(1)==TOK_EACH || LA(1)==TOK_END || 
LA(1)==TOK_EVENT || LA(1)==TOK_FOR || LA(1)==TOK_FROM || LA(1)==TOK_GENERATE || LA(1)==TOK_IN || 
LA(1)==TOK_INSTANCES || LA(1)==TOK_INSTANCE || LA(1)==TOK_MANY || LA(1)==TOK_OBJECT || LA(1)==TOK_OF || 
LA(1)==TOK_ONE || LA(1)==TOK_RELATED || LA(1)==TOK_RELATE || LA(1)==TOK_SELECT || LA(1)==TOK_STOP || 
LA(1)==TOK_TO || LA(1)==TOK_WHERE || LA(1)==TOK_UNRELATE || LA(1)==TOK_USING || LA(1)==TOK_SELECTED || 
LA(1)==TOK_SELF || LA(1)==TOK_GARBAGE || LA(1)==TOK_BAD_ID || LA(1)==TOK_BAD_NAME || LA(1)==TOK_ID || 
LA(1)==TOK_RELID) && (LA(2)==TOK_DOT) ) {
			{
				ANTLRTokenPtr _t22=NULL;
				AST *_ast21=NULL,*_ast22=NULL;
				_ast = NULL;
				if ( !guessing ) {
					 t1  = attribute_access(&_ast,&_signal, ASSIGN_LVAL ); if (_signal) goto _handler;
					_ast21 = (AST *)_ast;
				} else {
					attribute_access(&_ast,&_signal, ASSIGN_LVAL );
				}
				zzmatch_wsig(TOK_EQUAL, _handler);				
				if ( !guessing ) {
				 _t22 = (ANTLRTokenPtr)LT(1);
}
 labase++;
				 consume();
			}
			zzGUESS_DONE
			_ast = NULL;
			if ( !guessing ) {
				 t1  = attribute_access(&_ast,&_signal, ASSIGN_LVAL ); if (_signal) goto _handler;
				_ast12 = (AST *)_ast;
				aa_ast = _ast12;
			} else {
				attribute_access(&_ast,&_signal, ASSIGN_LVAL );
			}
			zzmatch_wsig(TOK_EQUAL, _handler);			
			if ( !guessing ) {
			 _t13 = (ANTLRTokenPtr)LT(1);
}
 labase++;
			 consume();
			_ast = NULL;
			if ( !guessing ) {
				 t2  = expr(&_ast,&_signal); if (_signal) goto _handler;
				_ast14 = (AST *)_ast;
				ex2_ast = _ast14;
			} else {
				expr(&_ast,&_signal);
			}
			if ( !guessing ) {
			(*_root) = ASTBase::tmake( NULL, aa_ast, ex2_ast , NULL);
			bool mismatch = FALSE;
			if ( accum_datatype( aa_ast, ex2_ast, t1, t2, mismatch ) )
			AL_PARSE_ERR0( aa_ast, AL_GETMSG(ERR,274,0) )
			_retv = t1;
			}
		}
		else {
			if ( !zzrv ) zzGUESS_DONE;
			if ( (LA(1)==TOK_RCVD_EVT) ) {
				_ast = NULL;
				if ( !guessing ) {
					 t1  = event_data_access(&_ast,&_signal, ASSIGN_LVAL ); if (_signal) goto _handler;
					_ast11 = (AST *)_ast;
					eda_ast = _ast11;
				} else {
					event_data_access(&_ast,&_signal, ASSIGN_LVAL );
				}
				zzmatch_wsig(TOK_EQUAL, _handler);				
				if ( !guessing ) {
				 _t12 = (ANTLRTokenPtr)LT(1);
}
 labase++;
				 consume();
				_ast = NULL;
				if ( !guessing ) {
					 _retv  = expr(&_ast,&_signal); if (_signal) goto _handler;
					_ast13 = (AST *)_ast;
					ex3_ast = _ast13;
				} else {
					expr(&_ast,&_signal);
				}
				if ( !guessing ) {
				eda_ast->setDatatype(t1);
				(*_root) = ASTBase::tmake( NULL, eda_ast , NULL);
				}
			}
			else {
				if ( !zzrv ) zzGUESS_DONE;
				if ( (
LA(1)==TOK_PARAM) ) {
					_ast = NULL;
					if ( !guessing ) {
						 t1  = param_data_access(&_ast,&_signal, ASSIGN_LVAL ); if (_signal) goto _handler;
						_ast11 = (AST *)_ast;
						pda_ast = _ast11;
					} else {
						param_data_access(&_ast,&_signal, ASSIGN_LVAL );
					}
					zzmatch_wsig(TOK_EQUAL, _handler);					
					if ( !guessing ) {
					 _t12 = (ANTLRTokenPtr)LT(1);
}
 labase++;
					 consume();
					_ast = NULL;
					if ( !guessing ) {
						 t2  = expr(&_ast,&_signal); if (_signal) goto _handler;
						_ast13 = (AST *)_ast;
						ex4_ast = _ast13;
					} else {
						expr(&_ast,&_signal);
					}
					if ( !guessing ) {
					(*_root) = ASTBase::tmake( NULL, pda_ast, ex4_ast , NULL);
					bool mismatch = FALSE;
					if ( accum_datatype( pda_ast, ex4_ast, t1, t2, mismatch ) )
					AL_PARSE_ERR0( pda_ast, AL_GETMSG(ERR,274,0) )
					_retv = t1;
					}
				}
				else {
					if ( guessing ) goto fail;
					if (_sva) _signal=NoViableAlt;
					else _signal=NoSemViableAlt;
					goto _handler;  /* MR7 */
				}
			}
		}
	}
	return _retv;
fail:
	if ( guessing ) zzGUESS_FAIL;
	syn(zzBadTok, "assignment expression", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd5, 0x10);
	return _retv;
_handler:
	zzdflthandlers(_signal,_retsignal);
	return _retv;
}

 t_core_data_type  
P::attribute_access(ASTBase **_root,int *_retsignal, Assign_Val_e isLval )
{
	 t_core_data_type  	 _retv;
	zzRULE;
	int _sva=1;
	ASTBase *_ast = NULL, *_sibling = NULL, *_tail = NULL;
	ANTLRTokenPtr _t12=NULL;
	AST *_ast11=NULL,*_ast12=NULL,*_ast13=NULL;
	ANTLRTokenPtr ir=NULL, attr=NULL;
	AST *ir_ast=NULL, *attr_ast=NULL;
	int _signal=NoSignal;
	PURIFY(_retv,sizeof( t_core_data_type  	))
	*_retsignal = NoSignal;
	_ast = NULL;
	inst_ref_var(&_ast,&_signal); if (_signal) goto _handler;
	_ast11 = (AST *)_ast;
	ir_ast = _ast11;
	zzmatch_wsig(TOK_DOT, _handler);	
	if ( !guessing ) {
	 _t12 = (ANTLRTokenPtr)LT(1);
}
 labase++;
	 consume();
	_ast = NULL;
	attribute(&_ast,&_signal); if (_signal) goto _handler;
	_ast13 = (AST *)_ast;
	attr_ast = _ast13;
	if ( !guessing ) {
	t_boolean derived_attribute_written = 
	pck->validate_obj_attribute( attr_ast, ir_ast, isLval, attribute_write_valid );
	if (attribute_write_valid && derived_attribute_written)
	{
		attribute_write_found = TRUE;
	}
	_retv = attr_ast->getDatatype();
	ir_ast->setDatatype(_retv);
	ir_ast->setSegLength(attr_ast->getOffset() +
	attr_ast->getSegLength() -
	ir_ast->getOffset());
	(*_root) = ASTBase::tmake( ir_ast, attr_ast , NULL);
	}
	return _retv;
fail:
	if ( guessing ) zzGUESS_FAIL;
	syn(zzBadTok, "object attribute access", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd5, 0x20);
	return _retv;
_handler:
	zzdflthandlers(_signal,_retsignal);
	return _retv;
}

 t_core_data_type  
P::bridge_invocation(ASTBase **_root,int *_retsignal, bool requiresReturnValue )
{
	 t_core_data_type  	 _retv;
	zzRULE;
	int _sva=1;
	ASTBase *_ast = NULL, *_sibling = NULL, *_tail = NULL;
	ANTLRTokenPtr _t12=NULL,_t14=NULL,_t16=NULL;
	AST *_ast11=NULL,*_ast12=NULL,*_ast13=NULL,*_ast14=NULL,*_ast16=NULL;
	ANTLRTokenPtr kl=NULL, bf=NULL, fp=NULL, rp=NULL;
	AST *kl_ast=NULL, *bf_ast=NULL, *fp_ast=NULL, *rp_ast=NULL;
	int _signal=NoSignal;
	PURIFY(_retv,sizeof( t_core_data_type  	))
	*_retsignal = NoSignal;
	AST *top_ast = NULL;
	AST *b_ast;
	_ast = NULL;
	ee_keyletters(&_ast,&_signal); if (_signal) goto _handler;
	_ast11 = (AST *)_ast;
	kl_ast = _ast11;
	zzmatch_wsig(TOK_DOUBLECOLON, _handler);	
	if ( !guessing ) {
	 _t12 = (ANTLRTokenPtr)LT(1);
}
 labase++;
	 consume();
	_ast = NULL;
	if ( !guessing ) {
		 _retv  = bridge_function(&_ast,&_signal, kl_ast ); if (_signal) goto _handler;
		_ast13 = (AST *)_ast;
		bf_ast = _ast13;
	} else {
		bridge_function(&_ast,&_signal, kl_ast );
	}
	if ( !guessing ) {
	top_ast = (new AST(TOK_BRIDGE_EXPR, kl_ast));  // sets offset
	top_ast->setDatatype(_retv);
	(*_root) = ASTBase::tmake( top_ast, kl_ast, bf_ast, NULL);
	if ( requiresReturnValue && (_retv == VOID_DATATYPE) )
	AL_PARSE_ERR2( kl_ast, AL_GETMSG(ERR,223,2),
	kl_ast->getVcharText(), bf_ast->getVcharText())
	if ( !requiresReturnValue && (_retv != VOID_DATATYPE) )
	AL_PARSE_ERR2( kl_ast, AL_GETMSG(ERR,225,2),
	kl_ast->getVcharText(), bf_ast->getVcharText())
	}
	zzmatch_wsig(TOK_LPAREN, _handler);	
	if ( !guessing ) {
	 _t14 = (ANTLRTokenPtr)LT(1);
}
 labase++;
	 consume();
	{
		AST *_ast21=NULL;
		if ( (LA(1)==TOK_ACROSS || LA(1)==TOK_ANY || LA(1)==TOK_ASSIGNER || 
LA(1)==TOK_ASSIGN || LA(1)==TOK_BREAKTOKEN || LA(1)==TOK_BY || LA(1)==TOK_CLASS || LA(1)==TOK_CONTINUE || 
LA(1)==TOK_CONTROL || LA(1)==TOK_CREATE || LA(1)==TOK_CREATOR || LA(1)==TOK_DELETE || LA(1)==TOK_EACH || 
LA(1)==TOK_END || LA(1)==TOK_EVENT || LA(1)==TOK_FOR || LA(1)==TOK_FROM || LA(1)==TOK_GENERATE || 
LA(1)==TOK_IN || LA(1)==TOK_INSTANCES || LA(1)==TOK_INSTANCE || LA(1)==TOK_MANY || LA(1)==TOK_OBJECT || 
LA(1)==TOK_OF || LA(1)==TOK_ONE || LA(1)==TOK_RELATED || LA(1)==TOK_RELATE || LA(1)==TOK_SELECT || 
LA(1)==TOK_STOP || LA(1)==TOK_TO || LA(1)==TOK_WHERE || LA(1)==TOK_UNRELATE || LA(1)==TOK_USING || 
LA(1)==TOK_BRIDGE || LA(1)==TOK_CARDINALITY || LA(1)==TOK_EMPTY || LA(1)==TOK_FALSETOKEN || LA(1)==TOK_NOT || 
LA(1)==TOK_NOTEMPTY || LA(1)==TOK_TRANSFORM || LA(1)==TOK_TRUETOKEN || LA(1)==TOK_PARAM || LA(1)==TOK_RCVD_EVT || 
LA(1)==TOK_SELECTED || LA(1)==TOK_SELF || LA(1)==TOK_GENERAL_NAME || LA(1)==TOK_GARBAGE || LA(1)==TOK_BAD_ID || 
LA(1)==TOK_BAD_NAME || LA(1)==TOK_ID || LA(1)==TOK_RELID) ) {
			_ast = NULL;
			function_parameters(&_ast,&_signal); if (_signal) goto _handler;
			_ast21 = (AST *)_ast;
			fp_ast = _ast21;
			if ( !guessing ) {
			ASTBase::tmake( NULL, (*_root)->bottom(), fp_ast, NULL);
			}
		}
	}
	zzmatch_wsig(TOK_RPAREN, _handler);	
	if ( !guessing ) {
	 _t16 = (ANTLRTokenPtr)LT(1);
}
 labase++;
	
	if ( !guessing ) {
		rp = _t16;
	}
	
	if ( !guessing ) {
	// Validate data items here
	pck->validate_bridge_data_items( bf_ast, fp_ast );
	b_ast = (new AST( rp));
	top_ast->setSegLength(b_ast->getOffset() +
	1 -
	top_ast->getOffset());
	delete b_ast;
	}
 consume();
	return _retv;
fail:
	if ( guessing ) zzGUESS_FAIL;
	syn(zzBadTok, "bridge invocation", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd5, 0x40);
	return _retv;
_handler:
	zzdflthandlers(_signal,_retsignal);
	return _retv;
}

P::_rv40
P::bridge_or_transform_invocation(ASTBase **_root,int *_retsignal, bool requiresReturnValue )
{
	struct _rv40 _retv;
	zzRULE;
	int _sva=1;
	ASTBase *_ast = NULL, *_sibling = NULL, *_tail = NULL;
	ANTLRTokenPtr _t12=NULL,_t14=NULL,_t16=NULL;
	AST *_ast11=NULL,*_ast12=NULL,*_ast13=NULL,*_ast14=NULL,*_ast16=NULL;
	ANTLRTokenPtr kl=NULL, mn=NULL, fp=NULL, rp=NULL;
	AST *kl_ast=NULL, *mn_ast=NULL, *fp_ast=NULL, *rp_ast=NULL;
	int _signal=NoSignal;
	PURIFY(_retv,sizeof(struct _rv40))
	*_retsignal = NoSignal;
	AST *top_ast;
	AST *b_ast;
	_ast = NULL;
	obj_or_ee_keyletters(&_ast,&_signal); if (_signal) goto _handler;
	_ast11 = (AST *)_ast;
	kl_ast = _ast11;
	zzmatch_wsig(TOK_DOUBLECOLON, _handler);	
	if ( !guessing ) {
	 _t12 = (ANTLRTokenPtr)LT(1);
}
 labase++;
	 consume();
	_ast = NULL;
	function_name(&_ast,&_signal); if (_signal) goto _handler;
	_ast13 = (AST *)_ast;
	mn_ast = _ast13;
	if ( !guessing ) {
	top_ast = (new AST(TOK_STMT_UNKNOWN, kl_ast));  // sets offset
	(*_root) = ASTBase::tmake(top_ast, kl_ast, mn_ast, NULL);
	kl_ast->setType(TOK_KL_OBJECT);
	if ( pck->is_valid_obj_kl( kl_ast ) &&
	pck->is_valid_transformer( mn_ast, kl_ast, FALSE ) )
	{
		_retv.OorEE = TOK_KL_OBJECT;
		top_ast->setType(TOK_TRANSFORMER_EXPR);
		_retv.t = pck->get_transformer_return_type( mn_ast );
		if ( requiresReturnValue && (_retv.t == VOID_DATATYPE) )
		AL_PARSE_ERR2( kl_ast, AL_GETMSG(ERR,232,2),
		kl_ast->getVcharText(), mn_ast->getVcharText())
		if ( !requiresReturnValue && (_retv.t != VOID_DATATYPE) )
		AL_PARSE_ERR2( kl_ast, AL_GETMSG(ERR,235,2),
		kl_ast->getVcharText(), mn_ast->getVcharText())
	}
	else
	{
		_retv.OorEE = TOK_KL_EXTERNAL_ENTITY;
		top_ast->setType(TOK_BRIDGE_EXPR);
		kl_ast->setType(TOK_KL_EXTERNAL_ENTITY);
		if ( pck->is_valid_ee_kl( kl_ast ) &&
		pck->is_valid_ee_bridge( mn_ast, kl_ast ) )
		{
			pck->validate_ee_kl( kl_ast );
			pck->validate_bridge( mn_ast, kl_ast );
			_retv.t = pck->get_bridge_return_type( mn_ast );
			if ( requiresReturnValue && (_retv.t == VOID_DATATYPE) )
			AL_PARSE_ERR2( kl_ast, AL_GETMSG(ERR,223,2),
			kl_ast->getVcharText(), mn_ast->getVcharText())
			if ( !requiresReturnValue && (_retv.t != VOID_DATATYPE) )
			AL_PARSE_ERR2( kl_ast, AL_GETMSG(ERR,225,2),
			kl_ast->getVcharText(), mn_ast->getVcharText())
		}
		else
		AL_PARSE_ERR2( kl_ast, AL_GETMSG(ERR,103,2),
		kl_ast->getVcharText(), mn_ast->getVcharText())
	}
	top_ast->setDatatype(_retv.t);
	}
	zzmatch_wsig(TOK_LPAREN, _handler);	
	if ( !guessing ) {
	 _t14 = (ANTLRTokenPtr)LT(1);
}
 labase++;
	 consume();
	{
		AST *_ast21=NULL;
		if ( (LA(1)==TOK_ACROSS || 
LA(1)==TOK_ANY || LA(1)==TOK_ASSIGNER || LA(1)==TOK_ASSIGN || LA(1)==TOK_BREAKTOKEN || LA(1)==TOK_BY || 
LA(1)==TOK_CLASS || LA(1)==TOK_CONTINUE || LA(1)==TOK_CONTROL || LA(1)==TOK_CREATE || LA(1)==TOK_CREATOR || 
LA(1)==TOK_DELETE || LA(1)==TOK_EACH || LA(1)==TOK_END || LA(1)==TOK_EVENT || LA(1)==TOK_FOR || 
LA(1)==TOK_FROM || LA(1)==TOK_GENERATE || LA(1)==TOK_IN || LA(1)==TOK_INSTANCES || LA(1)==TOK_INSTANCE || 
LA(1)==TOK_MANY || LA(1)==TOK_OBJECT || LA(1)==TOK_OF || LA(1)==TOK_ONE || LA(1)==TOK_RELATED || 
LA(1)==TOK_RELATE || LA(1)==TOK_SELECT || LA(1)==TOK_STOP || LA(1)==TOK_TO || LA(1)==TOK_WHERE || 
LA(1)==TOK_UNRELATE || LA(1)==TOK_USING || LA(1)==TOK_BRIDGE || LA(1)==TOK_CARDINALITY || LA(1)==TOK_EMPTY || 
LA(1)==TOK_FALSETOKEN || LA(1)==TOK_NOT || LA(1)==TOK_NOTEMPTY || LA(1)==TOK_TRANSFORM || LA(1)==TOK_TRUETOKEN || 
LA(1)==TOK_PARAM || LA(1)==TOK_RCVD_EVT || LA(1)==TOK_SELECTED || LA(1)==TOK_SELF || LA(1)==TOK_GENERAL_NAME || 
LA(1)==TOK_GARBAGE || LA(1)==TOK_BAD_ID || LA(1)==TOK_BAD_NAME || LA(1)==TOK_ID || LA(1)==TOK_RELID)
 ) {
			_ast = NULL;
			function_parameters(&_ast,&_signal); if (_signal) goto _handler;
			_ast21 = (AST *)_ast;
			fp_ast = _ast21;
			if ( !guessing ) {
			ASTBase::tmake( NULL, (*_root)->bottom(), fp_ast, NULL);
			}
		}
	}
	zzmatch_wsig(TOK_RPAREN, _handler);	
	if ( !guessing ) {
	 _t16 = (ANTLRTokenPtr)LT(1);
}
 labase++;
	
	if ( !guessing ) {
		rp = _t16;
	}
	
	if ( !guessing ) {
	// Validate data items here
	if ( _retv.OorEE == TOK_KL_OBJECT )
	pck->validate_transformer_data_items( mn_ast, fp_ast );
	else   // ( $OorEE == TOK_KL_EXTERNAL_ENTITY )
	pck->validate_bridge_data_items( mn_ast, fp_ast );
	b_ast = (new AST( rp));
	top_ast->setSegLength(b_ast->getOffset() +
	1 -
	top_ast->getOffset());
	delete b_ast;
	}
 consume();
	return _retv;
fail:
	if ( guessing ) zzGUESS_FAIL;
	syn(zzBadTok, "bridge or transformer invocation", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd5, 0x80);
	return _retv;
_handler:
	zzdflthandlers(_signal,_retsignal);
	return _retv;
}

  t_core_data_type   
P::bridge_expr(ASTBase **_root,int *_retsignal)
{
	  t_core_data_type   	 _retv;
	zzRULE;
	int _sva=1;
	ASTBase *_ast = NULL, *_sibling = NULL, *_tail = NULL;
	ANTLRTokenPtr _t11=NULL;
	AST *_ast11=NULL,*_ast12=NULL;
	ANTLRTokenPtr tb=NULL, br=NULL;
	AST *tb_ast=NULL, *br_ast=NULL;
	int _signal=NoSignal;
	PURIFY(_retv,sizeof(  t_core_data_type   	))
	*_retsignal = NoSignal;
	ANTLRTokenType OorEE;
	AST *t_ast;
	zzmatch_wsig(TOK_BRIDGE, _handler);	
	if ( !guessing ) {
	 _t11 = (ANTLRTokenPtr)LT(1);
}
 labase++;
	 
	if ( !guessing ) {
		tb = _t11;
	}
	 consume();
	_ast = NULL;
	if ( !guessing ) {
		 _retv  = bridge_invocation(&_ast,&_signal, TRUE ); if (_signal) goto _handler;
		if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
		_ast12 = (AST *)_ast;
		ASTBase::link(_root, &_sibling, &_tail);
		br_ast = _ast12;
	} else {
		bridge_invocation(&_ast,&_signal, TRUE );
	}
	if ( !guessing ) {
	t_ast = (new AST( tb));
	br_ast->setSegLength(br_ast->getOffset() +
	br_ast->getSegLength() -
	t_ast->getOffset());
	br_ast->setOffset(t_ast->getOffset());
	delete t_ast;
	}
	return _retv;
fail:
	if ( guessing ) zzGUESS_FAIL;
	syn(zzBadTok, "bridge expression", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd6, 0x1);
	return _retv;
_handler:
	zzdflthandlers(_signal,_retsignal);
	return _retv;
}

  t_core_data_type   
P::bridge_or_transform_expr(ASTBase **_root,int *_retsignal)
{
	  t_core_data_type   	 _retv;
	zzRULE;
	int _sva=1;
	ASTBase *_ast = NULL, *_sibling = NULL, *_tail = NULL;
	AST *_ast11=NULL;
	ANTLRTokenPtr bt=NULL;
	AST *bt_ast=NULL;
	int _signal=NoSignal;
	PURIFY(_retv,sizeof(  t_core_data_type   	))
	*_retsignal = NoSignal;
	ANTLRTokenType OorEE;
	_ast = NULL;
	if ( !guessing ) {
		{ struct _rv40 _trv; _trv = bridge_or_transform_invocation(&_ast,&_signal, TRUE ); if (_signal) goto _handler;
		if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
		_ast11 = (AST *)_ast;
		ASTBase::link(_root, &_sibling, &_tail);
		_retv = _trv.t; OorEE  = _trv.OorEE; }
		bt_ast = _ast11;
	} else {
		bridge_or_transform_invocation(&_ast,&_signal, TRUE );
	}
	return _retv;
fail:
	if ( guessing ) zzGUESS_FAIL;
	syn(zzBadTok, "bridge or transform invocation", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd6, 0x2);
	return _retv;
_handler:
	zzdflthandlers(_signal,_retsignal);
	return _retv;
}

 t_core_data_type  
P::enumerator_access(ASTBase **_root,int *_retsignal)
{
	 t_core_data_type  	 _retv;
	zzRULE;
	int _sva=1;
	ASTBase *_ast = NULL, *_sibling = NULL, *_tail = NULL;
	ANTLRTokenPtr _t12=NULL;
	AST *_ast11=NULL,*_ast12=NULL,*_ast13=NULL;
	ANTLRTokenPtr enumdt=NULL, enumtr=NULL;
	AST *enumdt_ast=NULL, *enumtr_ast=NULL;
	int _signal=NoSignal;
	PURIFY(_retv,sizeof( t_core_data_type  	))
	*_retsignal = NoSignal;
	_ast = NULL;
	enum_data_type(&_ast,&_signal); if (_signal) goto _handler;
	if (!guessing) {    /* MR10 */
		if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
		_ast11 = (AST *)_ast;
		ASTBase::link(_root, &_sibling, &_tail);
	};    /* MR10 */
	enumdt_ast = _ast11;
	zzmatch_wsig(TOK_DOUBLECOLON, _handler);	
	if ( !guessing ) {
	 _t12 = (ANTLRTokenPtr)LT(1);
}
 labase++;
	  consume();
	_ast = NULL;
	enumerator(&_ast,&_signal); if (_signal) goto _handler;
	if (!guessing) {    /* MR10 */
		if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
		_ast13 = (AST *)_ast;
		ASTBase::link(_root, &_sibling, &_tail);
	};    /* MR10 */
	enumtr_ast = _ast13;
	if ( !guessing ) {
	pck->validate_enumerator( enumdt_ast, enumtr_ast );
	_retv = enumdt_ast->getDatatype();
	}
	return _retv;
fail:
	if ( guessing ) zzGUESS_FAIL;
	syn(zzBadTok, "enumerator access", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd6, 0x4);
	return _retv;
_handler:
	zzdflthandlers(_signal,_retsignal);
	return _retv;
}

void
P::debug_operand(ASTBase **_root,int *_retsignal)
{
	zzRULE;
	int _sva=1;
	ASTBase *_ast = NULL, *_sibling = NULL, *_tail = NULL;
	ANTLRTokenPtr _t11=NULL;
	AST *_ast11=NULL;
	int _signal=NoSignal;
	*_retsignal = NoSignal;
	if ( (LA(1)==TOK_TRACE) ) {
		{
			ANTLRTokenPtr _t21=NULL;
			AST *_ast21=NULL;
			zzmatch_wsig(TOK_TRACE, _handler);			
			if ( !guessing ) {
			 _t21 = (ANTLRTokenPtr)LT(1);
}
 labase++;
			 consume();
			{
				ANTLRTokenPtr _t31=NULL;
				AST *_ast31=NULL;
				if ( (LA(1)==TOK_OFF) ) {
					zzmatch_wsig(TOK_OFF, _handler);					
					if ( !guessing ) {
					 _t31 = (ANTLRTokenPtr)LT(1);
}
 labase++;
					
					if ( !guessing ) {
					trace = FALSE;
					}
 consume();
				}
				else {
					if ( (
LA(1)==TOK_ON) ) {
						zzmatch_wsig(TOK_ON, _handler);						
						if ( !guessing ) {
						 _t31 = (ANTLRTokenPtr)LT(1);
}
 labase++;
						
						if ( !guessing ) {
						trace = TRUE;
						}
 consume();
					}
					else {
						if ( guessing ) goto fail;
						if (_sva) _signal=NoViableAlt;
						else _signal=NoSemViableAlt;
						goto _handler;  /* MR7 */
					}
				}
			}
		}
	}
	else {
		if ( (LA(1)==TOK_DUMP) ) {
			{
				ANTLRTokenPtr _t21=NULL;
				AST *_ast21=NULL;
				zzmatch_wsig(TOK_DUMP, _handler);				
				if ( !guessing ) {
				 _t21 = (ANTLRTokenPtr)LT(1);
}
 labase++;
				 consume();
				{
					ANTLRTokenPtr _t31=NULL;
					AST *_ast31=NULL;
					if ( (LA(1)==TOK_OFF)
 ) {
						zzmatch_wsig(TOK_OFF, _handler);						
						if ( !guessing ) {
						 _t31 = (ANTLRTokenPtr)LT(1);
}
 labase++;
						
						if ( !guessing ) {
						dumpflag = FALSE;
						}
 consume();
					}
					else {
						if ( (LA(1)==TOK_ON) ) {
							zzmatch_wsig(TOK_ON, _handler);							
							if ( !guessing ) {
							 _t31 = (ANTLRTokenPtr)LT(1);
}
 labase++;
							
							if ( !guessing ) {
							dumpflag = TRUE;
							}
 consume();
						}
						else {
							if ( guessing ) goto fail;
							if (_sva) _signal=NoViableAlt;
							else _signal=NoSemViableAlt;
							goto _handler;  /* MR7 */
						}
					}
				}
			}
		}
		else {
			if ( (LA(1)==TOK_SOR) ) {
				{
					ANTLRTokenPtr _t21=NULL;
					AST *_ast21=NULL;
					zzmatch_wsig(TOK_SOR, _handler);					
					if ( !guessing ) {
					 _t21 = (ANTLRTokenPtr)LT(1);
}
 labase++;
					 consume();
					{
						ANTLRTokenPtr _t31=NULL;
						AST *_ast31=NULL;
						if ( (
LA(1)==TOK_OFF) ) {
							zzmatch_wsig(TOK_OFF, _handler);							
							if ( !guessing ) {
							 _t31 = (ANTLRTokenPtr)LT(1);
}
 labase++;
							
							if ( !guessing ) {
							sor = FALSE;
							}
 consume();
						}
						else {
							if ( (LA(1)==TOK_ON) ) {
								zzmatch_wsig(TOK_ON, _handler);								
								if ( !guessing ) {
								 _t31 = (ANTLRTokenPtr)LT(1);
}
 labase++;
								
								if ( !guessing ) {
								sor = TRUE;
								}
 consume();
							}
							else {
								if ( guessing ) goto fail;
								if (_sva) _signal=NoViableAlt;
								else _signal=NoSemViableAlt;
								goto _handler;  /* MR7 */
							}
						}
					}
				}
			}
			else {
				if ( (LA(1)==TOK_ON)
 ) {
					zzmatch_wsig(TOK_ON, _handler);					
					if ( !guessing ) {
					 _t11 = (ANTLRTokenPtr)LT(1);
}
 labase++;
					
					if ( !guessing ) {
					trace = TRUE;  dumpflag = TRUE;
					}
 consume();
				}
				else {
					if ( (LA(1)==TOK_OFF) ) {
						zzmatch_wsig(TOK_OFF, _handler);						
						if ( !guessing ) {
						 _t11 = (ANTLRTokenPtr)LT(1);
}
 labase++;
						
						if ( !guessing ) {
						trace = FALSE; dumpflag = FALSE;
						}
 consume();
					}
					else {
						if ( (LA(1)==TOK_STAT) ) {
							zzmatch_wsig(TOK_STAT, _handler);							
							if ( !guessing ) {
							 _t11 = (ANTLRTokenPtr)LT(1);
}
 labase++;
							
							if ( !guessing ) {
							st->stat();
							}
 consume();
						}
						else {
							if ( guessing ) goto fail;
							if (_sva) _signal=NoViableAlt;
							else _signal=NoSemViableAlt;
							goto _handler;  /* MR7 */
						}
					}
				}
			}
		}
	}
	return;
fail:
	if ( guessing ) zzGUESS_FAIL;
	syn(zzBadTok, "debug operand", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd6, 0x8);
_handler:
	zzdflthandlers(_signal,_retsignal);
	return;
}

 t_core_data_type  
P::event_data_access(ASTBase **_root,int *_retsignal, Assign_Val_e isLval )
{
	 t_core_data_type  	 _retv;
	zzRULE;
	int _sva=1;
	ASTBase *_ast = NULL, *_sibling = NULL, *_tail = NULL;
	ANTLRTokenPtr _t11=NULL,_t12=NULL;
	AST *_ast11=NULL,*_ast12=NULL,*_ast13=NULL;
	ANTLRTokenPtr re=NULL, sdi=NULL;
	AST *re_ast=NULL, *sdi_ast=NULL;
	int _signal=NoSignal;
	PURIFY(_retv,sizeof( t_core_data_type  	))
	*_retsignal = NoSignal;
	Sym *s_ref = NULL;
	zzmatch_wsig(TOK_RCVD_EVT, _handler);	
	if ( !guessing ) {
	 _t11 = (ANTLRTokenPtr)LT(1);
}
 labase++;
	if ( !guessing ) {
	
	_ast11 = new AST(_t11);
	_ast11->subchild(_root, &_sibling, &_tail);
	}
	
	if ( !guessing ) {
		re = _t11;
	re_ast = _ast11;
	}
	
	if ( !guessing ) {
	if ( isLval == ASSIGN_LVAL )
	AL_PARSE_ERR0( re_ast, AL_GETMSG(ERR,075,0) )
	}
 consume();
	zzmatch_wsig(TOK_DOT, _handler);	
	if ( !guessing ) {
	 _t12 = (ANTLRTokenPtr)LT(1);
}
 labase++;
	  consume();
	_ast = NULL;
	supp_data_item(&_ast,&_signal); if (_signal) goto _handler;
	if (!guessing) {    /* MR10 */
		if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
		_ast13 = (AST *)_ast;
		ASTBase::link(_root, &_sibling, &_tail);
	};    /* MR10 */
	sdi_ast = _ast13;
	if ( !guessing ) {
	// We have made an entry in the symbol table for a readonly
	// local variable named "rcvd_evt".  It is an EVENT_INST_REF
	// for the event (any one) which transitions to this state.
	// Set the seglength of re to include the sdi
	re_ast->setSegLength(sdi_ast->getOffset() +
	sdi_ast->getSegLength() -
	re_ast->getOffset());
	// Validate the supplemental data item for this state
	if ( st->is_var_this_type_defined( re_ast->getVcharText(),
	EVENT_INST_DATATYPE, &s_ref ) )
	{
		// rcvd_evt's objPtr is set to the value of an SM_EVT
		// object that transitions to this state by the init() function.
		re_ast->setObjPtr( s_ref->objPtr );
		pck->validate_rcvd_evt_data_item_name( sdi_ast, re_ast );
		_retv = sdi_ast->getDatatype();
		re_ast->setDatatype(_retv);
	}
	else
	{
	_retv = UNKNOWN_DATATYPE;
	AL_PARSE_ERR1( re_ast, AL_GETMSG(ERR, 300, 1), re_ast->getVcharText() )
}
	}
	return _retv;
fail:
	if ( guessing ) zzGUESS_FAIL;
	syn(zzBadTok, "event data access", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd6, 0x10);
	return _retv;
_handler:
	zzdflthandlers(_signal,_retsignal);
	return _retv;
}

void
P::event_spec(ASTBase **_root,int *_retsignal)
{
	zzRULE;
	int _sva=1;
	ASTBase *_ast = NULL, *_sibling = NULL, *_tail = NULL;
	ANTLRTokenPtr _t15=NULL;
	AST *_ast11=NULL,*_ast15=NULL;
	ANTLRTokenPtr l=NULL, t=NULL, m=NULL, s=NULL, kla=NULL, klc=NULL, irvee=NULL;
	AST *l_ast=NULL, *t_ast=NULL, *m_ast=NULL, *s_ast=NULL, *kla_ast=NULL, *klc_ast=NULL, *irvee_ast=NULL;
	int _signal=NoSignal;
	*_retsignal = NoSignal;
	Sym *s_ref = NULL;
	AST *event_and_label = NULL;
	AST *target = NULL;
	AST *tt_ast = NULL;
	persObjPtr sm_objPtr;
	bool PE_indicated = FALSE;
	_ast = NULL;
	event_label(&_ast,&_signal); if (_signal) goto _handler;
	_ast11 = (AST *)_ast;
	l_ast = _ast11;
	{
		ANTLRTokenPtr _t21=NULL;
		AST *_ast21=NULL;
		if ( (
LA(1)==TOK_TIMES) ) {
			zzmatch_wsig(TOK_TIMES, _handler);			
			if ( !guessing ) {
			 _t21 = (ANTLRTokenPtr)LT(1);
}
 labase++;
			
			if ( !guessing ) {
						t = _t21;
			}
			
			if ( !guessing ) {
			PE_indicated = TRUE;
			tt_ast = (new AST( t));
			tt_ast->markReloc( RELOC_IGNORE_DATA );
			ttr->add( tt_ast );
			}
 consume();
		}
	}
	{
		ANTLRTokenPtr _t21=NULL;
		AST *_ast21=NULL,*_ast22=NULL;
		if ( (LA(1)==TOK_COLON) ) {
			zzmatch_wsig(TOK_COLON, _handler);			
			if ( !guessing ) {
			 _t21 = (ANTLRTokenPtr)LT(1);
}
 labase++;
			 consume();
			_ast = NULL;
			event_meaning(&_ast,&_signal); if (_signal) goto _handler;
			_ast22 = (AST *)_ast;
			m_ast = _ast22;
		}
	}
	{
		ANTLRTokenPtr _t21=NULL,_t23=NULL;
		AST *_ast21=NULL,*_ast23=NULL;
		if ( (LA(1)==TOK_LPAREN)
 ) {
			zzmatch_wsig(TOK_LPAREN, _handler);			
			if ( !guessing ) {
			 _t21 = (ANTLRTokenPtr)LT(1);
}
 labase++;
			 consume();
			{
				AST *_ast31=NULL;
				if ( (LA(1)==TOK_ACROSS || LA(1)==TOK_ANY || LA(1)==TOK_ASSIGNER || LA(1)==TOK_ASSIGN || 
LA(1)==TOK_BREAKTOKEN || LA(1)==TOK_BY || LA(1)==TOK_CLASS || LA(1)==TOK_CONTINUE || LA(1)==TOK_CONTROL || 
LA(1)==TOK_CREATE || LA(1)==TOK_CREATOR || LA(1)==TOK_DELETE || LA(1)==TOK_EACH || LA(1)==TOK_END || 
LA(1)==TOK_EVENT || LA(1)==TOK_FOR || LA(1)==TOK_FROM || LA(1)==TOK_GENERATE || LA(1)==TOK_IN || 
LA(1)==TOK_INSTANCES || LA(1)==TOK_INSTANCE || LA(1)==TOK_MANY || LA(1)==TOK_OBJECT || LA(1)==TOK_OF || 
LA(1)==TOK_ONE || LA(1)==TOK_RELATED || LA(1)==TOK_RELATE || LA(1)==TOK_SELECT || LA(1)==TOK_STOP || 
LA(1)==TOK_TO || LA(1)==TOK_WHERE || LA(1)==TOK_UNRELATE || LA(1)==TOK_USING || LA(1)==TOK_BRIDGE || 
LA(1)==TOK_CARDINALITY || LA(1)==TOK_EMPTY || LA(1)==TOK_FALSETOKEN || LA(1)==TOK_NOT || LA(1)==TOK_NOTEMPTY || 
LA(1)==TOK_TRANSFORM || LA(1)==TOK_TRUETOKEN || LA(1)==TOK_PARAM || LA(1)==TOK_RCVD_EVT || LA(1)==TOK_SELECTED || 
LA(1)==TOK_SELF || LA(1)==TOK_GENERAL_NAME || LA(1)==TOK_GARBAGE || LA(1)==TOK_BAD_ID || LA(1)==TOK_BAD_NAME || 
LA(1)==TOK_ID || LA(1)==TOK_RELID) ) {
					_ast = NULL;
					supp_data(&_ast,&_signal); if (_signal) goto _handler;
					_ast31 = (AST *)_ast;
					s_ast = _ast31;
				}
			}
			zzmatch_wsig(TOK_RPAREN, _handler);			
			if ( !guessing ) {
			 _t23 = (ANTLRTokenPtr)LT(1);
}
 labase++;
			 consume();
		}
	}
	zzmatch_wsig(TOK_TO, _handler);	
	if ( !guessing ) {
	 _t15 = (ANTLRTokenPtr)LT(1);
}
 labase++;
	 consume();
	{
;
		if ( (LA(1)==TOK_ACROSS || LA(1)==TOK_ANY || 
LA(1)==TOK_ASSIGNER || LA(1)==TOK_ASSIGN || LA(1)==TOK_BREAKTOKEN || LA(1)==TOK_BY || LA(1)==TOK_CLASS || 
LA(1)==TOK_CONTINUE || LA(1)==TOK_CONTROL || LA(1)==TOK_CREATE || LA(1)==TOK_CREATOR || LA(1)==TOK_DELETE || 
LA(1)==TOK_EACH || LA(1)==TOK_END || LA(1)==TOK_EVENT || LA(1)==TOK_FOR || LA(1)==TOK_FROM || 
LA(1)==TOK_GENERATE || LA(1)==TOK_IN || LA(1)==TOK_INSTANCES || LA(1)==TOK_INSTANCE || LA(1)==TOK_MANY || 
LA(1)==TOK_OBJECT || LA(1)==TOK_OF || LA(1)==TOK_ONE || LA(1)==TOK_RELATED || LA(1)==TOK_RELATE || 
LA(1)==TOK_SELECT || LA(1)==TOK_STOP || LA(1)==TOK_TO || LA(1)==TOK_WHERE || LA(1)==TOK_UNRELATE || 
LA(1)==TOK_USING || LA(1)==TOK_BRIDGE || LA(1)==TOK_CARDINALITY || LA(1)==TOK_EMPTY || LA(1)==TOK_FALSETOKEN || 
LA(1)==TOK_NOT || LA(1)==TOK_NOTEMPTY || LA(1)==TOK_TRANSFORM || LA(1)==TOK_TRUETOKEN || LA(1)==TOK_PARAM || 
LA(1)==TOK_RCVD_EVT || LA(1)==TOK_SELECTED || LA(1)==TOK_SELF || LA(1)==TOK_GENERAL_NAME || LA(1)==TOK_GARBAGE || 
LA(1)==TOK_BAD_ID || LA(1)==TOK_BAD_NAME || LA(1)==TOK_ID || LA(1)==TOK_RELID) && (
LA(2)==TOK_ASSIGNER || LA(2)==TOK_CLASS || LA(2)==TOK_CREATOR) ) {
			{
				ANTLRTokenPtr _t32=NULL;
				AST *_ast31=NULL,*_ast32=NULL;
				zzGUESS_BLOCK
				zzGUESS
				if ( !zzrv && (LA(1)==TOK_ACROSS || LA(1)==TOK_ANY || 
LA(1)==TOK_ASSIGNER || LA(1)==TOK_ASSIGN || LA(1)==TOK_BREAKTOKEN || LA(1)==TOK_BY || LA(1)==TOK_CLASS || 
LA(1)==TOK_CONTINUE || LA(1)==TOK_CONTROL || LA(1)==TOK_CREATE || LA(1)==TOK_CREATOR || LA(1)==TOK_DELETE || 
LA(1)==TOK_EACH || LA(1)==TOK_END || LA(1)==TOK_EVENT || LA(1)==TOK_FOR || LA(1)==TOK_FROM || 
LA(1)==TOK_GENERATE || LA(1)==TOK_IN || LA(1)==TOK_INSTANCES || LA(1)==TOK_INSTANCE || LA(1)==TOK_MANY || 
LA(1)==TOK_OBJECT || LA(1)==TOK_OF || LA(1)==TOK_ONE || LA(1)==TOK_RELATED || LA(1)==TOK_RELATE || 
LA(1)==TOK_SELECT || LA(1)==TOK_STOP || LA(1)==TOK_TO || LA(1)==TOK_WHERE || LA(1)==TOK_UNRELATE || 
LA(1)==TOK_USING || LA(1)==TOK_BRIDGE || LA(1)==TOK_CARDINALITY || LA(1)==TOK_EMPTY || LA(1)==TOK_FALSETOKEN || 
LA(1)==TOK_NOT || LA(1)==TOK_NOTEMPTY || LA(1)==TOK_TRANSFORM || LA(1)==TOK_TRUETOKEN || LA(1)==TOK_PARAM || 
LA(1)==TOK_RCVD_EVT || LA(1)==TOK_SELECTED || LA(1)==TOK_SELF || LA(1)==TOK_GENERAL_NAME || LA(1)==TOK_GARBAGE || 
LA(1)==TOK_BAD_ID || LA(1)==TOK_BAD_NAME || LA(1)==TOK_ID || LA(1)==TOK_RELID) && (
LA(2)==TOK_ASSIGNER || LA(2)==TOK_CLASS) ) {
					{
						AST *_ast41=NULL;
						_ast = NULL;
						object_keyletters(&_ast,&_signal); if (_signal) goto _handler;
						_ast41 = (AST *)_ast;
						{
							ANTLRTokenPtr _t51=NULL;
							AST *_ast51=NULL;
							if ( (LA(1)==TOK_ASSIGNER) ) {
								zzmatch_wsig(TOK_ASSIGNER, _handler);								
								if ( !guessing ) {
								 _t51 = (ANTLRTokenPtr)LT(1);
}
 labase++;
								 consume();
							}
							else {
								if ( (LA(1)==TOK_CLASS)
 ) {
									zzmatch_wsig(TOK_CLASS, _handler);									
									if ( !guessing ) {
									 _t51 = (ANTLRTokenPtr)LT(1);
}
 labase++;
									 consume();
								}
								else {
									if ( guessing ) goto fail;
									if (_sva) _signal=NoViableAlt;
									else _signal=NoSemViableAlt;
									goto _handler;  /* MR7 */
								}
							}
						}
					}
					zzGUESS_DONE
					_ast = NULL;
					object_keyletters(&_ast,&_signal); if (_signal) goto _handler;
					_ast32 = (AST *)_ast;
					kla_ast = _ast32;
					{
						ANTLRTokenPtr _t41=NULL;
						AST *_ast41=NULL;
						if ( (LA(1)==TOK_ASSIGNER) ) {
							zzmatch_wsig(TOK_ASSIGNER, _handler);							
							if ( !guessing ) {
							 _t41 = (ANTLRTokenPtr)LT(1);
}
 labase++;
							 consume();
						}
						else {
							if ( (LA(1)==TOK_CLASS) ) {
								zzmatch_wsig(TOK_CLASS, _handler);								
								if ( !guessing ) {
								 _t41 = (ANTLRTokenPtr)LT(1);
}
 labase++;
								 consume();
							}
							else {
								if ( guessing ) goto fail;
								if (_sva) _signal=NoViableAlt;
								else _signal=NoSemViableAlt;
								goto _handler;  /* MR7 */
							}
						}
					}
					if ( !guessing ) {
					
					kla_ast->setType(TOK_KL_OBJECT_ASSIGNER);
					pck->validate_obj_is_assigner(kla_ast);
					pck->validate_assigner_event_label( l_ast, kla_ast );
					if (m_ast)
					pck->validate_sm_event_meaning( m_ast, l_ast );
					pck->validate_sm_event_data_items( l_ast, s_ast );
					if ( PE_indicated )
					AL_PARSE_ERR0( t_ast, AL_GETMSG(ERR,077,0) )
					target = kla_ast;
					}
				}
				else {
					if ( !zzrv ) zzGUESS_DONE;
					if ( (
LA(1)==TOK_ACROSS || LA(1)==TOK_ANY || LA(1)==TOK_ASSIGNER || LA(1)==TOK_ASSIGN || LA(1)==TOK_BREAKTOKEN || 
LA(1)==TOK_BY || LA(1)==TOK_CLASS || LA(1)==TOK_CONTINUE || LA(1)==TOK_CONTROL || LA(1)==TOK_CREATE || 
LA(1)==TOK_CREATOR || LA(1)==TOK_DELETE || LA(1)==TOK_EACH || LA(1)==TOK_END || LA(1)==TOK_EVENT || 
LA(1)==TOK_FOR || LA(1)==TOK_FROM || LA(1)==TOK_GENERATE || LA(1)==TOK_IN || LA(1)==TOK_INSTANCES || 
LA(1)==TOK_INSTANCE || LA(1)==TOK_MANY || LA(1)==TOK_OBJECT || LA(1)==TOK_OF || LA(1)==TOK_ONE || 
LA(1)==TOK_RELATED || LA(1)==TOK_RELATE || LA(1)==TOK_SELECT || LA(1)==TOK_STOP || LA(1)==TOK_TO || 
LA(1)==TOK_WHERE || LA(1)==TOK_UNRELATE || LA(1)==TOK_USING || LA(1)==TOK_BRIDGE || LA(1)==TOK_CARDINALITY || 
LA(1)==TOK_EMPTY || LA(1)==TOK_FALSETOKEN || LA(1)==TOK_NOT || LA(1)==TOK_NOTEMPTY || LA(1)==TOK_TRANSFORM || 
LA(1)==TOK_TRUETOKEN || LA(1)==TOK_PARAM || LA(1)==TOK_RCVD_EVT || LA(1)==TOK_SELECTED || LA(1)==TOK_SELF || 
LA(1)==TOK_GENERAL_NAME || LA(1)==TOK_GARBAGE || LA(1)==TOK_BAD_ID || LA(1)==TOK_BAD_NAME || LA(1)==TOK_ID || 
LA(1)==TOK_RELID) && (LA(2)==TOK_CREATOR) ) {
						_ast = NULL;
						object_keyletters(&_ast,&_signal); if (_signal) goto _handler;
						_ast31 = (AST *)_ast;
						klc_ast = _ast31;
						zzmatch_wsig(TOK_CREATOR, _handler);						
						if ( !guessing ) {
						 _t32 = (ANTLRTokenPtr)LT(1);
}
 labase++;
						
						if ( !guessing ) {
						
						klc_ast->setType(TOK_KL_OBJECT_CREATOR);
						pck->validate_obj_has_creation_state( klc_ast );
						pck->validate_creator_event_label( l_ast, klc_ast );
						if (m_ast)
						pck->validate_sm_event_meaning( m_ast, l_ast );
						pck->validate_sm_event_data_items( l_ast, s_ast );
						if ( PE_indicated )
						AL_PARSE_ERR0( t_ast, AL_GETMSG(ERR,077,0) )
						target = klc_ast;
						}
 consume();
					}
					else {
						if ( guessing ) goto fail;
						if (_sva) _signal=NoViableAlt;
						else _signal=NoSemViableAlt;
						goto _handler;  /* MR7 */
					}
				}
			}
		}
		else {
			if ( (LA(1)==TOK_ACROSS || LA(1)==TOK_ANY || 
LA(1)==TOK_ASSIGNER || LA(1)==TOK_ASSIGN || LA(1)==TOK_BREAKTOKEN || LA(1)==TOK_BY || LA(1)==TOK_CLASS || 
LA(1)==TOK_CONTINUE || LA(1)==TOK_CONTROL || LA(1)==TOK_CREATE || LA(1)==TOK_CREATOR || LA(1)==TOK_DELETE || 
LA(1)==TOK_EACH || LA(1)==TOK_END || LA(1)==TOK_EVENT || LA(1)==TOK_FOR || LA(1)==TOK_FROM || 
LA(1)==TOK_GENERATE || LA(1)==TOK_IN || LA(1)==TOK_INSTANCES || LA(1)==TOK_INSTANCE || LA(1)==TOK_MANY || 
LA(1)==TOK_OBJECT || LA(1)==TOK_OF || LA(1)==TOK_ONE || LA(1)==TOK_RELATED || LA(1)==TOK_RELATE || 
LA(1)==TOK_SELECT || LA(1)==TOK_STOP || LA(1)==TOK_TO || LA(1)==TOK_WHERE || LA(1)==TOK_UNRELATE || 
LA(1)==TOK_USING || LA(1)==TOK_BRIDGE || LA(1)==TOK_CARDINALITY || LA(1)==TOK_EMPTY || LA(1)==TOK_FALSETOKEN || 
LA(1)==TOK_NOT || LA(1)==TOK_NOTEMPTY || LA(1)==TOK_TRANSFORM || LA(1)==TOK_TRUETOKEN || LA(1)==TOK_SELECTED || 
LA(1)==TOK_SELF || LA(1)==TOK_GENERAL_NAME || LA(1)==TOK_GARBAGE || LA(1)==TOK_BAD_ID || LA(1)==TOK_BAD_NAME || 
LA(1)==TOK_ID || LA(1)==TOK_RELID) && (LA(2)==TOK_SEMI) ) {
				{
					AST *_ast31=NULL;
					_ast = NULL;
					inst_ref_var_or_ee_keyletters(&_ast,&_signal); if (_signal) goto _handler;
					_ast31 = (AST *)_ast;
					irvee_ast = _ast31;
					if ( !guessing ) {
					target = irvee_ast;
					if ( PE_indicated )
					AL_PARSE_ERR0( t_ast, AL_GETMSG(ERR,077,0) )
					}
				}
				if ( !guessing ) {
				if ( st->is_inst_ref_var( target->getVcharText(), &s_ref ) )
				{
					target->setType(TOK_INST_REF_VAR);
					target->setObjPtr( s_ref->objPtr );
					pck->validate_obj_event_label( l_ast, target );
					if (m_ast)
					pck->validate_sm_event_meaning( m_ast, l_ast );
					pck->validate_sm_event_data_items( l_ast, s_ast );
				}
				else
				{
					target->setType( TOK_KL_EXTERNAL_ENTITY );
					ttr->add( target );
					if ( pck->is_valid_ee_kl( target ) )
					{
						pck->validate_ee_event_label( l_ast, target );
						if (m_ast)
						pck->validate_ee_event_meaning( m_ast, l_ast );
						pck->validate_ee_event_data_items( l_ast, s_ast );
						if ( PE_indicated )
						AL_PARSE_ERR0( t_ast, AL_GETMSG(ERR,077,0) )
					}
					else
					AL_PARSE_ERR1( target, AL_GETMSG(ERR,043,1), target->getVcharText() )
				}
				}
			}
			else {
				if ( guessing ) goto fail;
				if (_sva) _signal=NoViableAlt;
				else _signal=NoSemViableAlt;
				goto _handler;  /* MR7 */
			}
		}
	}
	if ( !guessing ) {
	if (PE_indicated)
	event_and_label = (AST*) ASTBase::tmake( l_ast, tt_ast , m_ast , NULL);
	else   
	event_and_label = (AST*) ASTBase::tmake( l_ast, m_ast , NULL);
	(*_root) = ASTBase::tmake( NULL, event_and_label, target, s_ast , NULL);
	((AST *)(*_root))->setObjPtr( l_ast->getObjPtr() );
	}
	return;
fail:
	if ( guessing ) zzGUESS_FAIL;
	syn(zzBadTok, "event specification", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd6, 0x20);
_handler:
	zzdflthandlers(_signal,_retsignal);
	return;
}

void
P::function_parameters(ASTBase **_root,int *_retsignal)
{
	zzRULE;
	int _sva=1;
	ASTBase *_ast = NULL, *_sibling = NULL, *_tail = NULL;
	ANTLRTokenPtr _t12=NULL;
	AST *_ast11=NULL,*_ast12=NULL,*_ast13=NULL;
	ANTLRTokenPtr di1=NULL, e1=NULL, di2=NULL, e2=NULL;
	AST *di1_ast=NULL, *e1_ast=NULL, *di2_ast=NULL, *e2_ast=NULL;
	int _signal=NoSignal;
	*_retsignal = NoSignal;
	t_core_data_type dt;
	_ast = NULL;
	data_item(&_ast,&_signal); if (_signal) goto _handler;
	_ast11 = (AST *)_ast;
	di1_ast = _ast11;
	zzmatch_wsig(TOK_COLON, _handler);	
	if ( !guessing ) {
	 _t12 = (ANTLRTokenPtr)LT(1);
}
 labase++;
	 consume();
	_ast = NULL;
	if ( !guessing ) {
		 dt  = expr(&_ast,&_signal); if (_signal) goto _handler;
		_ast13 = (AST *)_ast;
		e1_ast = _ast13;
	} else {
		expr(&_ast,&_signal);
	}
	if ( !guessing ) {
	(*_root) = ASTBase::tmake( di1_ast, e1_ast , NULL);
	}
	{
		ANTLRTokenPtr _t21=NULL,_t23=NULL;
		AST *_ast21=NULL,*_ast22=NULL,*_ast23=NULL,*_ast24=NULL;
		while ( (LA(1)==TOK_COMMA)
 ) {
			zzmatch_wsig(TOK_COMMA, _handler);			
			if ( !guessing ) {
			 _t21 = (ANTLRTokenPtr)LT(1);
}
 labase++;
			 consume();
			_ast = NULL;
			data_item(&_ast,&_signal); if (_signal) goto _handler;
			_ast22 = (AST *)_ast;
			di2_ast = _ast22;
			zzmatch_wsig(TOK_COLON, _handler);			
			if ( !guessing ) {
			 _t23 = (ANTLRTokenPtr)LT(1);
}
 labase++;
			 consume();
			_ast = NULL;
			if ( !guessing ) {
				 dt  = expr(&_ast,&_signal); if (_signal) goto _handler;
				_ast24 = (AST *)_ast;
				e2_ast = _ast24;
			} else {
				expr(&_ast,&_signal);
			}
			if ( !guessing ) {
			ASTBase::tmake( NULL, (*_root)->tail(), ASTBase::tmake( di2_ast, e2_ast , NULL) , NULL);
			}
		}
	}
	return;
fail:
	if ( guessing ) zzGUESS_FAIL;
	syn(zzBadTok, "function parameters", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd6, 0x40);
_handler:
	zzdflthandlers(_signal,_retsignal);
	return;
}

void
P::inst_ref_var_or_ee_keyletters(ASTBase **_root,int *_retsignal)
{
	zzRULE;
	int _sva=1;
	ASTBase *_ast = NULL, *_sibling = NULL, *_tail = NULL;
;
	int _signal=NoSignal;
	*_retsignal = NoSignal;
	{
		ANTLRTokenPtr _t21=NULL;
		AST *_ast21=NULL;
		if ( (LA(1)==TOK_ACROSS || LA(1)==TOK_ANY || LA(1)==TOK_ASSIGNER || LA(1)==TOK_ASSIGN || 
LA(1)==TOK_BREAKTOKEN || LA(1)==TOK_BY || LA(1)==TOK_CLASS || LA(1)==TOK_CONTINUE || LA(1)==TOK_CONTROL || 
LA(1)==TOK_CREATE || LA(1)==TOK_CREATOR || LA(1)==TOK_DELETE || LA(1)==TOK_EACH || LA(1)==TOK_END || 
LA(1)==TOK_EVENT || LA(1)==TOK_FOR || LA(1)==TOK_FROM || LA(1)==TOK_GENERATE || LA(1)==TOK_IN || 
LA(1)==TOK_INSTANCES || LA(1)==TOK_INSTANCE || LA(1)==TOK_MANY || LA(1)==TOK_OBJECT || LA(1)==TOK_OF || 
LA(1)==TOK_ONE || LA(1)==TOK_RELATED || LA(1)==TOK_RELATE || LA(1)==TOK_SELECT || LA(1)==TOK_STOP || 
LA(1)==TOK_TO || LA(1)==TOK_WHERE || LA(1)==TOK_UNRELATE || LA(1)==TOK_USING || LA(1)==TOK_SELECTED || 
LA(1)==TOK_SELF || LA(1)==TOK_GARBAGE || LA(1)==TOK_BAD_ID || LA(1)==TOK_BAD_NAME || LA(1)==TOK_ID || 
LA(1)==TOK_RELID) ) {
			_ast = NULL;
			local_variable(&_ast,&_signal, ASSIGN_RVAL ); if (_signal) goto _handler;
			if (!guessing) {    /* MR10 */
				if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
				_ast21 = (AST *)_ast;
				ASTBase::link(_root, &_sibling, &_tail);
			};    /* MR10 */
		}
		else {
			if ( (LA(1)==TOK_GENERAL_NAME) ) {
				zzmatch_wsig(TOK_GENERAL_NAME, _handler);				
				if ( !guessing ) {
				 _t21 = (ANTLRTokenPtr)LT(1);
}
 labase++;
				if ( !guessing ) {
				
				_ast21 = new AST(_t21);
				_ast21->subchild(_root, &_sibling, &_tail);
				}
				 consume();
			}
			else {
				if ( (LA(1)==TOK_BRIDGE || 
LA(1)==TOK_CARDINALITY || LA(1)==TOK_EMPTY || LA(1)==TOK_FALSETOKEN || LA(1)==TOK_NOT || LA(1)==TOK_NOTEMPTY || 
LA(1)==TOK_TRANSFORM || LA(1)==TOK_TRUETOKEN) ) {
					_ast = NULL;
					kw_as_id2(&_ast,&_signal); if (_signal) goto _handler;
					if (!guessing) {    /* MR10 */
						if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
						_ast21 = (AST *)_ast;
						ASTBase::link(_root, &_sibling, &_tail);
					};    /* MR10 */
				}
				else {
					if ( guessing ) goto fail;
					if (_sva) _signal=NoViableAlt;
					else _signal=NoSemViableAlt;
					goto _handler;  /* MR7 */
				}
			}
		}
	}
	return;
fail:
	if ( guessing ) zzGUESS_FAIL;
	syn(zzBadTok, "instance reference variable or ee keyletters", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd6, 0x80);
_handler:
	zzdflthandlers(_signal,_retsignal);
	return;
}

void
P::instance_chain(ASTBase **_root,int *_retsignal, Obj_Card_e card )
{
	zzRULE;
	int _sva=1;
	ASTBase *_ast = NULL, *_sibling = NULL, *_tail = NULL;
	AST *_ast11=NULL;
	ANTLRTokenPtr lv=NULL, kl=NULL, rel=NULL, drp=NULL;
	AST *lv_ast=NULL, *kl_ast=NULL, *rel_ast=NULL, *drp_ast=NULL;
	int _signal=NoSignal;
	*_retsignal = NoSignal;
	AST *top_ast;
	AST *left_obj;
	bool manyFound = FALSE;
	bool irs_var = FALSE;
	Sym *s_ref;
	ANTLRTokenType save_type;
	_ast = NULL;
	local_variable(&_ast,&_signal, ASSIGN_RVAL ); if (_signal) goto _handler;
	_ast11 = (AST *)_ast;
	lv_ast = _ast11;
	if ( !guessing ) {
	top_ast = (new AST(TOK_INST_REF));
	left_obj = lv_ast;
	(*_root) = ASTBase::tmake( NULL, top_ast, lv_ast , NULL);
	if ( st->is_inst_ref_var( lv_ast->getVcharText(), &s_ref ) )
	{
		lv_ast->setType(TOK_INST_REF_VAR);
		lv_ast->setObjPtr( s_ref->objPtr );
	}
	else if ( st->is_inst_ref_set_var( lv_ast->getVcharText(), &s_ref ) )
	{
		irs_var = TRUE;  // remember it's an inst_ref_set_var
		lv_ast->setType(TOK_INST_REF_SET_VAR);
		lv_ast->setObjPtr( s_ref->objPtr );
		if ( card == CARD_ONE )
		AL_PARSE_ERR1( lv_ast, AL_GETMSG(ERR,188,1), lv_ast->getVcharText() )
	}
	else
	AL_PARSE_ERR1( lv_ast, AL_GETMSG(ERR,041,1), lv_ast->getVcharText() )
	top_ast->setObjPtr( lv_ast->getObjPtr() );
	}
	{
		ANTLRTokenPtr _t21=NULL,_t23=NULL,_t26=NULL;
		AST *_ast21=NULL,*_ast22=NULL,*_ast23=NULL,*_ast24=NULL,*_ast26=NULL;
		int zzcnt=1;
		do {
			zzmatch_wsig(TOK_ARROW, _handler);			
			if ( !guessing ) {
			 _t21 = (ANTLRTokenPtr)LT(1);
}
 labase++;
			 consume();
			_ast = NULL;
			object_keyletters(&_ast,&_signal); if (_signal) goto _handler;
			_ast22 = (AST *)_ast;
			kl_ast = _ast22;
			zzmatch_wsig(TOK_LSQBR, _handler);			
			if ( !guessing ) {
			 _t23 = (ANTLRTokenPtr)LT(1);
}
 labase++;
			 consume();
			_ast = NULL;
			relationship(&_ast,&_signal); if (_signal) goto _handler;
			_ast24 = (AST *)_ast;
			rel_ast = _ast24;
			if ( !guessing ) {
			drp_ast = 0;   // clear it out for the next link in the chain I1034
			}
			{
				ANTLRTokenPtr _t31=NULL;
				AST *_ast31=NULL,*_ast32=NULL;
				if ( (LA(1)==TOK_DOT) ) {
					zzmatch_wsig(TOK_DOT, _handler);					
					if ( !guessing ) {
					 _t31 = (ANTLRTokenPtr)LT(1);
}
 labase++;
					 consume();
					_ast = NULL;
					phrase(&_ast,&_signal); if (_signal) goto _handler;
					_ast32 = (AST *)_ast;
					drp_ast = _ast32;
					if ( !guessing ) {
					ttr->add( drp_ast );
					}
				}
			}
			zzmatch_wsig(TOK_RSQBR, _handler);			
			if ( !guessing ) {
			 _t26 = (ANTLRTokenPtr)LT(1);
}
 labase++;
			
			if ( !guessing ) {
			save_type = left_obj->getType();  // save type to restore later
			left_obj->setType(TOK_KL_OBJECT);
			pck->validate_rel_id (rel_ast, left_obj, kl_ast, drp_ast, card, manyFound);
			left_obj->setType(save_type);     // restore the type
			left_obj = kl_ast;
			ASTBase::tmake( NULL, (*_root)->tail(), ASTBase::tmake( kl_ast, rel_ast, drp_ast, NULL) , NULL);
			top_ast->setObjPtr( kl_ast->getObjPtr() );
			top_ast->setVcharText( kl_ast->getVcharText() );
			}
 consume();
		} while ( (
LA(1)==TOK_ARROW) );
	}
	if ( !guessing ) {
	if ( ( !manyFound ) && ( !irs_var ) )
	{
		if ( card == CARD_ANY )
		AL_PARSE_ERR0( rel_ast, AL_GETMSG(ERR,177,0) )
		if ( card == CARD_MANY )
		AL_PARSE_ERR0( rel_ast, AL_GETMSG(ERR,178,0) )
	}
	}
	return;
fail:
	if ( guessing ) zzGUESS_FAIL;
	syn(zzBadTok, "instance reference", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd7, 0x1);
_handler:
	zzdflthandlers(_signal,_retsignal);
	return;
}

 persObjPtr  
P::object_spec(ASTBase **_root,int *_retsignal, Obj_Card_e card )
{
	 persObjPtr  	 _retv;
	zzRULE;
	int _sva=1;
	ASTBase *_ast = NULL, *_sibling = NULL, *_tail = NULL;
;
	ANTLRTokenPtr r=NULL, ic=NULL, f=NULL, kl=NULL, wt=NULL, ex=NULL;
	AST *r_ast=NULL, *ic_ast=NULL, *f_ast=NULL, *kl_ast=NULL, *wt_ast=NULL, *ex_ast=NULL;
	int _signal=NoSignal;
	PURIFY(_retv,sizeof( persObjPtr  	))
	*_retsignal = NoSignal;
	
	t_core_data_type t1;
	AST * w_ast;
	AST * rel_ast = NULL;
	Sym * s_ref1 = NULL;
	Sym * s_ref2 = NULL;
	Sym * s_ref3 = NULL;
	{
		ANTLRTokenPtr _t21=NULL,_t22=NULL,_t23=NULL;
		AST *_ast21=NULL,*_ast22=NULL,*_ast23=NULL,*_ast24=NULL;
		if ( (LA(1)==TOK_RELATED) ) {
			zzmatch_wsig(TOK_RELATED, _handler);			
			if ( !guessing ) {
			 _t21 = (ANTLRTokenPtr)LT(1);
}
 labase++;
			
			if ( !guessing ) {
						r = _t21;
			}
			 consume();
			zzmatch_wsig(TOK_BY, _handler);			
			if ( !guessing ) {
			 _t22 = (ANTLRTokenPtr)LT(1);
}
 labase++;
			 consume();
			_ast = NULL;
			instance_chain(&_ast,&_signal, card ); if (_signal) goto _handler;
			_ast23 = (AST *)_ast;
			ic_ast = _ast23;
			if ( !guessing ) {
			_retv = ic_ast->getObjPtr();
			rel_ast = (new AST( r, TOK_RELATED));
			(*_root) = ASTBase::tmake( rel_ast, ic_ast , NULL);
			}
		}
		else {
			if ( (LA(1)==TOK_FROM)
 ) {
				zzmatch_wsig(TOK_FROM, _handler);				
				if ( !guessing ) {
				 _t21 = (ANTLRTokenPtr)LT(1);
}
 labase++;
				
				if ( !guessing ) {
								f = _t21;
				}
				 consume();
				zzmatch_wsig(TOK_INSTANCES, _handler);				
				if ( !guessing ) {
				 _t22 = (ANTLRTokenPtr)LT(1);
}
 labase++;
				 consume();
				zzmatch_wsig(TOK_OF, _handler);				
				if ( !guessing ) {
				 _t23 = (ANTLRTokenPtr)LT(1);
}
 labase++;
				 consume();
				_ast = NULL;
				object_keyletters(&_ast,&_signal); if (_signal) goto _handler;
				_ast24 = (AST *)_ast;
				kl_ast = _ast24;
				if ( !guessing ) {
				AST * from_ast;
				_retv = kl_ast->getObjPtr();
				from_ast = (new AST( f, TOK_FROM));
				(*_root) = ASTBase::tmake( from_ast, kl_ast , NULL);
				if ( card == CARD_ONE )
				AL_PARSE_ERR0( from_ast, AL_GETMSG(ERR,189,0) )
				}
			}
			else {
				if ( guessing ) goto fail;
				if (_sva) _signal=NoViableAlt;
				else _signal=NoSemViableAlt;
				goto _handler;  /* MR7 */
			}
		}
	}
	{
		ANTLRTokenPtr _t21=NULL;
		AST *_ast21=NULL,*_ast22=NULL;
		if ( (LA(1)==TOK_WHERE) ) {
			zzmatch_wsig(TOK_WHERE, _handler);			
			if ( !guessing ) {
			 _t21 = (ANTLRTokenPtr)LT(1);
}
 labase++;
			
			if ( !guessing ) {
						wt = _t21;
			}
			
			if ( !guessing ) {
			
			w_ast = (new AST(TOK_SELECTED));
			w_ast->setAsciiText("selected");
			s_ref1 = st->newadd( w_ast, OBJECT_INST_REF_DATATYPE, _retv );
			w_ast->setAsciiText("Selected");
			s_ref2 = st->newadd( w_ast, OBJECT_INST_REF_DATATYPE, _retv );
			w_ast->setAsciiText("SELECTED");
			s_ref3 = st->newadd( w_ast, OBJECT_INST_REF_DATATYPE, _retv );
			delete w_ast;
			in_where=TRUE;
			selected_found = FALSE;
			}
 consume();
			_ast = NULL;
			if ( !guessing ) {
				 t1  = expr(&_ast,&_signal); if (_signal) goto _handler;
				_ast22 = (AST *)_ast;
				ex_ast = _ast22;
			} else {
				expr(&_ast,&_signal);
			}
			if ( !guessing ) {
			
			st->remove( s_ref1 );
			s_ref1 = NULL;
			st->remove( s_ref2 );
			s_ref2 = NULL;
			st->remove( s_ref3 );
			s_ref3 = NULL;
			w_ast = (new AST( wt));
			ASTBase::tmake( NULL, (*_root)->tail(), w_ast, ex_ast , NULL);
			if ( rel_ast )   // select related by ...
			rel_ast->setType(TOK_RELATED_WHERE);
			if ( t1 != BOOLEAN_DATATYPE )
			AL_PARSE_ERR0( w_ast, AL_GETMSG(ERR,017,0) )
			if ( ! selected_found )
			AL_PARSE_ERR0( ex_ast, AL_GETMSG(ERR,155,0) )
			in_where=FALSE;
			}
		}
	}
	return _retv;
fail:
	if ( guessing ) zzGUESS_FAIL;
	
	if ( s_ref1 ) st->remove( s_ref1 );
	if ( s_ref2 ) st->remove( s_ref2 );
	if ( s_ref3 ) st->remove( s_ref3 );
	syn(zzBadTok, "object specification", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd7, 0x2);
	return _retv;
_handler:
	zzdflthandlers(_signal,_retsignal);
	return _retv;
}

 t_core_data_type  
P::param_data_access(ASTBase **_root,int *_retsignal, Assign_Val_e isLval )
{
	 t_core_data_type  	 _retv;
	zzRULE;
	int _sva=1;
	ASTBase *_ast = NULL, *_sibling = NULL, *_tail = NULL;
	ANTLRTokenPtr _t11=NULL,_t12=NULL;
	AST *_ast11=NULL,*_ast12=NULL,*_ast13=NULL;
	ANTLRTokenPtr pd=NULL, din=NULL;
	AST *pd_ast=NULL, *din_ast=NULL;
	int _signal=NoSignal;
	PURIFY(_retv,sizeof( t_core_data_type  	))
	*_retsignal = NoSignal;
	Sym *s_ref = NULL;
	zzmatch_wsig(TOK_PARAM, _handler);	
	if ( !guessing ) {
	 _t11 = (ANTLRTokenPtr)LT(1);
}
 labase++;
	if ( !guessing ) {
	
	_ast11 = new AST(_t11);
	_ast11->subroot(_root, &_sibling, &_tail);
	}
	
	if ( !guessing ) {
		pd = _t11;
	pd_ast = _ast11;
	}
	 consume();
	zzmatch_wsig(TOK_DOT, _handler);	
	if ( !guessing ) {
	 _t12 = (ANTLRTokenPtr)LT(1);
}
 labase++;
	  consume();
	_ast = NULL;
	data_item(&_ast,&_signal); if (_signal) goto _handler;
	if (!guessing) {    /* MR10 */
		if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
		_ast13 = (AST *)_ast;
		ASTBase::link(_root, &_sibling, &_tail);
	};    /* MR10 */
	din_ast = _ast13;
	if ( !guessing ) {
	// Set the seglength to include the data item
	pd_ast->setSegLength(din_ast->getOffset() +
	din_ast->getSegLength() -
	pd_ast->getOffset());
	// Validate that param.xx is valid
	if (!param_valid)
	AL_PARSE_ERR1( pd_ast, AL_GETMSG(ERR, 300, 1), pd_ast->getVcharText() )
	else
	{
		// Validate the supplemental data item for this state
		st->is_var_this_type_defined( pd_ast->getVcharText(),
		BRIDGE_OR_TRANSFORMER_INST_DATATYPE,
		&s_ref );
		// objPtr is set to the value of an BRIDGE or TRANSFORMER instance
		pd_ast->setObjPtr( s_ref->objPtr );
		switch (spec_type)
		{
			case AL_SPEC_BRIDGE_E:
			pd_ast->setType(TOK_BRIDGE_PARAM);
			pck->validate_bridge_data_item( din_ast, pd_ast, isLval );
			break;
			case AL_SPEC_TRANSFORMER_E:
			case AL_SPEC_IB_TRANSFORMER_E:
			pd_ast->setType(TOK_TRANSFORMER_PARAM);
			pck->validate_transformer_data_item( din_ast, pd_ast, isLval );
			break;
			case AL_SPEC_SYNSVC_E:
			pd_ast->setType(TOK_SYNCH_SVC_PARAM);
			pck->validate_synch_svc_data_item( din_ast, pd_ast, isLval );
			break;
			default:
			break;
		}
		_retv = din_ast->getDatatype();
	}
	}
	return _retv;
fail:
	if ( guessing ) zzGUESS_FAIL;
	syn(zzBadTok, "bridge or transformer parameter data access", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd7, 0x4);
	return _retv;
_handler:
	zzdflthandlers(_signal,_retsignal);
	return _retv;
}

void
P::supp_data(ASTBase **_root,int *_retsignal)
{
	zzRULE;
	int _sva=1;
	ASTBase *_ast = NULL, *_sibling = NULL, *_tail = NULL;
	ANTLRTokenPtr _t12=NULL;
	AST *_ast11=NULL,*_ast12=NULL,*_ast13=NULL;
	ANTLRTokenPtr s1=NULL, e1=NULL, s2=NULL, e2=NULL;
	AST *s1_ast=NULL, *e1_ast=NULL, *s2_ast=NULL, *e2_ast=NULL;
	int _signal=NoSignal;
	*_retsignal = NoSignal;
	t_core_data_type dt;
	_ast = NULL;
	supp_data_item(&_ast,&_signal); if (_signal) goto _handler;
	_ast11 = (AST *)_ast;
	s1_ast = _ast11;
	zzmatch_wsig(TOK_COLON, _handler);	
	if ( !guessing ) {
	 _t12 = (ANTLRTokenPtr)LT(1);
}
 labase++;
	 consume();
	_ast = NULL;
	if ( !guessing ) {
		 dt  = expr(&_ast,&_signal); if (_signal) goto _handler;
		_ast13 = (AST *)_ast;
		e1_ast = _ast13;
	} else {
		expr(&_ast,&_signal);
	}
	if ( !guessing ) {
	(*_root) = ASTBase::tmake( s1_ast, e1_ast , NULL);
	}
	{
		ANTLRTokenPtr _t21=NULL,_t23=NULL;
		AST *_ast21=NULL,*_ast22=NULL,*_ast23=NULL,*_ast24=NULL;
		while ( (LA(1)==TOK_COMMA) ) {
			zzmatch_wsig(TOK_COMMA, _handler);			
			if ( !guessing ) {
			 _t21 = (ANTLRTokenPtr)LT(1);
}
 labase++;
			 consume();
			_ast = NULL;
			supp_data_item(&_ast,&_signal); if (_signal) goto _handler;
			_ast22 = (AST *)_ast;
			s2_ast = _ast22;
			zzmatch_wsig(TOK_COLON, _handler);			
			if ( !guessing ) {
			 _t23 = (ANTLRTokenPtr)LT(1);
}
 labase++;
			 consume();
			_ast = NULL;
			if ( !guessing ) {
				 dt  = expr(&_ast,&_signal); if (_signal) goto _handler;
				_ast24 = (AST *)_ast;
				e2_ast = _ast24;
			} else {
				expr(&_ast,&_signal);
			}
			if ( !guessing ) {
			ASTBase::tmake( NULL, (*_root)->tail(), ASTBase::tmake( s2_ast, e2_ast , NULL) , NULL);
			}
		}
	}
	return;
fail:
	if ( guessing ) zzGUESS_FAIL;
	syn(zzBadTok, "event supplemental data", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd7, 0x8);
_handler:
	zzdflthandlers(_signal,_retsignal);
	return;
}

 t_core_data_type  
P::synch_svc_invocation(ASTBase **_root,int *_retsignal, bool requiresReturnValue )
{
	 t_core_data_type  	 _retv;
	zzRULE;
	int _sva=1;
	ASTBase *_ast = NULL, *_sibling = NULL, *_tail = NULL;
	ANTLRTokenPtr _t12=NULL,_t14=NULL;
	AST *_ast11=NULL,*_ast12=NULL,*_ast14=NULL;
	ANTLRTokenPtr ss=NULL, fp=NULL, rp=NULL;
	AST *ss_ast=NULL, *fp_ast=NULL, *rp_ast=NULL;
	int _signal=NoSignal;
	PURIFY(_retv,sizeof( t_core_data_type  	))
	*_retsignal = NoSignal;
	AST *top_ast;
	AST *b_ast;
	_ast = NULL;
	if ( !guessing ) {
		 _retv  = synch_svc_function(&_ast,&_signal); if (_signal) goto _handler;
		_ast11 = (AST *)_ast;
		ss_ast = _ast11;
	} else {
		synch_svc_function(&_ast,&_signal);
	}
	if ( !guessing ) {
	top_ast = (new AST(TOK_SYNCH_SVC_EXPR, ss_ast));
	top_ast->setDatatype(_retv);
	(*_root) = ASTBase::tmake( top_ast, ss_ast, NULL);
	if ( requiresReturnValue && (_retv == VOID_DATATYPE) )
	AL_PARSE_ERR1( ss_ast, AL_GETMSG(ERR,245,1),
	ss_ast->getVcharText() )
	if ( !requiresReturnValue && (_retv != VOID_DATATYPE) )
	AL_PARSE_ERR1( ss_ast, AL_GETMSG(ERR,246,1),
	ss_ast->getVcharText() )
	}
	zzmatch_wsig(TOK_LPAREN, _handler);	
	if ( !guessing ) {
	 _t12 = (ANTLRTokenPtr)LT(1);
}
 labase++;
	 consume();
	{
		AST *_ast21=NULL;
		if ( (
LA(1)==TOK_ACROSS || LA(1)==TOK_ANY || LA(1)==TOK_ASSIGNER || LA(1)==TOK_ASSIGN || LA(1)==TOK_BREAKTOKEN || 
LA(1)==TOK_BY || LA(1)==TOK_CLASS || LA(1)==TOK_CONTINUE || LA(1)==TOK_CONTROL || LA(1)==TOK_CREATE || 
LA(1)==TOK_CREATOR || LA(1)==TOK_DELETE || LA(1)==TOK_EACH || LA(1)==TOK_END || LA(1)==TOK_EVENT || 
LA(1)==TOK_FOR || LA(1)==TOK_FROM || LA(1)==TOK_GENERATE || LA(1)==TOK_IN || LA(1)==TOK_INSTANCES || 
LA(1)==TOK_INSTANCE || LA(1)==TOK_MANY || LA(1)==TOK_OBJECT || LA(1)==TOK_OF || LA(1)==TOK_ONE || 
LA(1)==TOK_RELATED || LA(1)==TOK_RELATE || LA(1)==TOK_SELECT || LA(1)==TOK_STOP || LA(1)==TOK_TO || 
LA(1)==TOK_WHERE || LA(1)==TOK_UNRELATE || LA(1)==TOK_USING || LA(1)==TOK_BRIDGE || LA(1)==TOK_CARDINALITY || 
LA(1)==TOK_EMPTY || LA(1)==TOK_FALSETOKEN || LA(1)==TOK_NOT || LA(1)==TOK_NOTEMPTY || LA(1)==TOK_TRANSFORM || 
LA(1)==TOK_TRUETOKEN || LA(1)==TOK_PARAM || LA(1)==TOK_RCVD_EVT || LA(1)==TOK_SELECTED || LA(1)==TOK_SELF || 
LA(1)==TOK_GENERAL_NAME || LA(1)==TOK_GARBAGE || LA(1)==TOK_BAD_ID || LA(1)==TOK_BAD_NAME || LA(1)==TOK_ID || 
LA(1)==TOK_RELID) ) {
			_ast = NULL;
			function_parameters(&_ast,&_signal); if (_signal) goto _handler;
			_ast21 = (AST *)_ast;
			fp_ast = _ast21;
			if ( !guessing ) {
			ASTBase::tmake( NULL, (*_root)->bottom(), fp_ast , NULL);
			}
		}
	}
	zzmatch_wsig(TOK_RPAREN, _handler);	
	if ( !guessing ) {
	 _t14 = (ANTLRTokenPtr)LT(1);
}
 labase++;
	
	if ( !guessing ) {
		rp = _t14;
	}
	
	if ( !guessing ) {
	// Set the seglength to include up to right paren
	b_ast = (new AST( rp));
	top_ast->setSegLength(b_ast->getOffset() +
	1 -
	top_ast->getOffset());
	// Validate data items here
	pck->validate_synch_svc_data_items( ss_ast, fp_ast );
	delete b_ast;
	}
 consume();
	return _retv;
fail:
	if ( guessing ) zzGUESS_FAIL;
	syn(zzBadTok, "synchronous service", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd7, 0x10);
	return _retv;
_handler:
	zzdflthandlers(_signal,_retsignal);
	return _retv;
}

 t_core_data_type  
P::transform_ib_invocation(ASTBase **_root,int *_retsignal, bool requiresReturnValue )
{
	 t_core_data_type  	 _retv;
	zzRULE;
	int _sva=1;
	ASTBase *_ast = NULL, *_sibling = NULL, *_tail = NULL;
	ANTLRTokenPtr _t12=NULL,_t14=NULL,_t16=NULL;
	AST *_ast11=NULL,*_ast12=NULL,*_ast13=NULL,*_ast14=NULL,*_ast16=NULL;
	ANTLRTokenPtr ir=NULL, tn=NULL, fp=NULL, rp=NULL;
	AST *ir_ast=NULL, *tn_ast=NULL, *fp_ast=NULL, *rp_ast=NULL;
	int _signal=NoSignal;
	PURIFY(_retv,sizeof( t_core_data_type  	))
	*_retsignal = NoSignal;
	AST *top_ast;
	AST *b_ast;
	_ast = NULL;
	inst_ref_var(&_ast,&_signal); if (_signal) goto _handler;
	_ast11 = (AST *)_ast;
	ir_ast = _ast11;
	zzmatch_wsig(TOK_DOT, _handler);	
	if ( !guessing ) {
	 _t12 = (ANTLRTokenPtr)LT(1);
}
 labase++;
	 consume();
	_ast = NULL;
	if ( !guessing ) {
		 _retv  = transformer_function(&_ast,&_signal, ir_ast, TRUE ); if (_signal) goto _handler;
		_ast13 = (AST *)_ast;
		tn_ast = _ast13;
	} else {
		transformer_function(&_ast,&_signal, ir_ast, TRUE );
	}
	if ( !guessing ) {
	top_ast = (new AST(TOK_TRANSFORMER_IB_EXPR, ir_ast));
	top_ast->setDatatype(_retv);
	(*_root) = ASTBase::tmake( top_ast, ir_ast, tn_ast, NULL);
	if ( requiresReturnValue && (_retv == VOID_DATATYPE) )
	AL_PARSE_ERR2( ir_ast, AL_GETMSG(ERR,241,2),
	ir_ast->getVcharText(), tn_ast->getVcharText())
	if ( !requiresReturnValue && (_retv != VOID_DATATYPE) )
	AL_PARSE_ERR2( ir_ast, AL_GETMSG(ERR,242,2),
	ir_ast->getVcharText(), tn_ast->getVcharText())
	}
	zzmatch_wsig(TOK_LPAREN, _handler);	
	if ( !guessing ) {
	 _t14 = (ANTLRTokenPtr)LT(1);
}
 labase++;
	 consume();
	{
		AST *_ast21=NULL;
		if ( (LA(1)==TOK_ACROSS || LA(1)==TOK_ANY || LA(1)==TOK_ASSIGNER || 
LA(1)==TOK_ASSIGN || LA(1)==TOK_BREAKTOKEN || LA(1)==TOK_BY || LA(1)==TOK_CLASS || LA(1)==TOK_CONTINUE || 
LA(1)==TOK_CONTROL || LA(1)==TOK_CREATE || LA(1)==TOK_CREATOR || LA(1)==TOK_DELETE || LA(1)==TOK_EACH || 
LA(1)==TOK_END || LA(1)==TOK_EVENT || LA(1)==TOK_FOR || LA(1)==TOK_FROM || LA(1)==TOK_GENERATE || 
LA(1)==TOK_IN || LA(1)==TOK_INSTANCES || LA(1)==TOK_INSTANCE || LA(1)==TOK_MANY || LA(1)==TOK_OBJECT || 
LA(1)==TOK_OF || LA(1)==TOK_ONE || LA(1)==TOK_RELATED || LA(1)==TOK_RELATE || LA(1)==TOK_SELECT || 
LA(1)==TOK_STOP || LA(1)==TOK_TO || LA(1)==TOK_WHERE || LA(1)==TOK_UNRELATE || LA(1)==TOK_USING || 
LA(1)==TOK_BRIDGE || LA(1)==TOK_CARDINALITY || LA(1)==TOK_EMPTY || LA(1)==TOK_FALSETOKEN || LA(1)==TOK_NOT || 
LA(1)==TOK_NOTEMPTY || LA(1)==TOK_TRANSFORM || LA(1)==TOK_TRUETOKEN || LA(1)==TOK_PARAM || LA(1)==TOK_RCVD_EVT || 
LA(1)==TOK_SELECTED || LA(1)==TOK_SELF || LA(1)==TOK_GENERAL_NAME || LA(1)==TOK_GARBAGE || LA(1)==TOK_BAD_ID || 
LA(1)==TOK_BAD_NAME || LA(1)==TOK_ID || LA(1)==TOK_RELID) ) {
			_ast = NULL;
			function_parameters(&_ast,&_signal); if (_signal) goto _handler;
			_ast21 = (AST *)_ast;
			fp_ast = _ast21;
			if ( !guessing ) {
			ASTBase::tmake( NULL, (*_root)->bottom(), fp_ast , NULL);
			}
		}
	}
	zzmatch_wsig(TOK_RPAREN, _handler);	
	if ( !guessing ) {
	 _t16 = (ANTLRTokenPtr)LT(1);
}
 labase++;
	
	if ( !guessing ) {
		rp = _t16;
	}
	
	if ( !guessing ) {
	// Set the seglength to include up to right paren
	b_ast = (new AST( rp));
	top_ast->setSegLength(b_ast->getOffset() +
	1 -
	top_ast->getOffset());
	// Validate data items here
	pck->validate_transformer_data_items( tn_ast, fp_ast );
	delete b_ast;
	}
 consume();
	return _retv;
fail:
	if ( guessing ) zzGUESS_FAIL;
	syn(zzBadTok, "instance-based transformer", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd7, 0x20);
	return _retv;
_handler:
	zzdflthandlers(_signal,_retsignal);
	return _retv;
}

  t_core_data_type   
P::transform_expr(ASTBase **_root,int *_retsignal)
{
	  t_core_data_type   	 _retv;
	zzRULE;
	int _sva=1;
	ASTBase *_ast = NULL, *_sibling = NULL, *_tail = NULL;
	ANTLRTokenPtr _t11=NULL;
	AST *_ast11=NULL,*_ast12=NULL;
	ANTLRTokenPtr tt=NULL, tr=NULL;
	AST *tt_ast=NULL, *tr_ast=NULL;
	int _signal=NoSignal;
	PURIFY(_retv,sizeof(  t_core_data_type   	))
	*_retsignal = NoSignal;
	ANTLRTokenType OorEE;
	AST *t_ast;
	zzmatch_wsig(TOK_TRANSFORM, _handler);	
	if ( !guessing ) {
	 _t11 = (ANTLRTokenPtr)LT(1);
}
 labase++;
	 
	if ( !guessing ) {
		tt = _t11;
	}
	 consume();
	_ast = NULL;
	if ( !guessing ) {
		 _retv  = transform_invocation(&_ast,&_signal, TRUE ); if (_signal) goto _handler;
		if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
		_ast12 = (AST *)_ast;
		ASTBase::link(_root, &_sibling, &_tail);
		tr_ast = _ast12;
	} else {
		transform_invocation(&_ast,&_signal, TRUE );
	}
	if ( !guessing ) {
	t_ast = (new AST( tt));
	tr_ast->setSegLength(tr_ast->getOffset() +
	tr_ast->getSegLength() -
	t_ast->getOffset());
	tr_ast->setOffset(t_ast->getOffset());
	delete t_ast;
	}
	return _retv;
fail:
	if ( guessing ) zzGUESS_FAIL;
	syn(zzBadTok, "transformer expression", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd7, 0x40);
	return _retv;
_handler:
	zzdflthandlers(_signal,_retsignal);
	return _retv;
}

 t_core_data_type  
P::transform_invocation(ASTBase **_root,int *_retsignal, bool requiresReturnValue )
{
	 t_core_data_type  	 _retv;
	zzRULE;
	int _sva=1;
	ASTBase *_ast = NULL, *_sibling = NULL, *_tail = NULL;
	ANTLRTokenPtr _t12=NULL,_t14=NULL,_t16=NULL;
	AST *_ast11=NULL,*_ast12=NULL,*_ast13=NULL,*_ast14=NULL,*_ast16=NULL;
	ANTLRTokenPtr kl=NULL, tn=NULL, fp=NULL, rp=NULL;
	AST *kl_ast=NULL, *tn_ast=NULL, *fp_ast=NULL, *rp_ast=NULL;
	int _signal=NoSignal;
	PURIFY(_retv,sizeof( t_core_data_type  	))
	*_retsignal = NoSignal;
	AST *top_ast;
	AST *b_ast;
	_ast = NULL;
	object_keyletters(&_ast,&_signal); if (_signal) goto _handler;
	_ast11 = (AST *)_ast;
	kl_ast = _ast11;
	zzmatch_wsig(TOK_DOUBLECOLON, _handler);	
	if ( !guessing ) {
	 _t12 = (ANTLRTokenPtr)LT(1);
}
 labase++;
	 consume();
	_ast = NULL;
	if ( !guessing ) {
		 _retv  = transformer_function(&_ast,&_signal, kl_ast, FALSE ); if (_signal) goto _handler;
		_ast13 = (AST *)_ast;
		tn_ast = _ast13;
	} else {
		transformer_function(&_ast,&_signal, kl_ast, FALSE );
	}
	if ( !guessing ) {
	top_ast = (new AST(TOK_TRANSFORMER_EXPR, kl_ast));
	top_ast->setDatatype(_retv);
	(*_root) = ASTBase::tmake( top_ast, kl_ast, tn_ast, NULL);
	if ( requiresReturnValue && (_retv == VOID_DATATYPE) )
	AL_PARSE_ERR2( kl_ast, AL_GETMSG(ERR,232,2),
	kl_ast->getVcharText(), tn_ast->getVcharText())
	if ( !requiresReturnValue && (_retv != VOID_DATATYPE) )
	AL_PARSE_ERR2( kl_ast, AL_GETMSG(ERR,235,2),
	kl_ast->getVcharText(), tn_ast->getVcharText())
	}
	zzmatch_wsig(TOK_LPAREN, _handler);	
	if ( !guessing ) {
	 _t14 = (ANTLRTokenPtr)LT(1);
}
 labase++;
	 consume();
	{
		AST *_ast21=NULL;
		if ( (LA(1)==TOK_ACROSS || 
LA(1)==TOK_ANY || LA(1)==TOK_ASSIGNER || LA(1)==TOK_ASSIGN || LA(1)==TOK_BREAKTOKEN || LA(1)==TOK_BY || 
LA(1)==TOK_CLASS || LA(1)==TOK_CONTINUE || LA(1)==TOK_CONTROL || LA(1)==TOK_CREATE || LA(1)==TOK_CREATOR || 
LA(1)==TOK_DELETE || LA(1)==TOK_EACH || LA(1)==TOK_END || LA(1)==TOK_EVENT || LA(1)==TOK_FOR || 
LA(1)==TOK_FROM || LA(1)==TOK_GENERATE || LA(1)==TOK_IN || LA(1)==TOK_INSTANCES || LA(1)==TOK_INSTANCE || 
LA(1)==TOK_MANY || LA(1)==TOK_OBJECT || LA(1)==TOK_OF || LA(1)==TOK_ONE || LA(1)==TOK_RELATED || 
LA(1)==TOK_RELATE || LA(1)==TOK_SELECT || LA(1)==TOK_STOP || LA(1)==TOK_TO || LA(1)==TOK_WHERE || 
LA(1)==TOK_UNRELATE || LA(1)==TOK_USING || LA(1)==TOK_BRIDGE || LA(1)==TOK_CARDINALITY || LA(1)==TOK_EMPTY || 
LA(1)==TOK_FALSETOKEN || LA(1)==TOK_NOT || LA(1)==TOK_NOTEMPTY || LA(1)==TOK_TRANSFORM || LA(1)==TOK_TRUETOKEN || 
LA(1)==TOK_PARAM || LA(1)==TOK_RCVD_EVT || LA(1)==TOK_SELECTED || LA(1)==TOK_SELF || LA(1)==TOK_GENERAL_NAME || 
LA(1)==TOK_GARBAGE || LA(1)==TOK_BAD_ID || LA(1)==TOK_BAD_NAME || LA(1)==TOK_ID || LA(1)==TOK_RELID)
 ) {
			_ast = NULL;
			function_parameters(&_ast,&_signal); if (_signal) goto _handler;
			_ast21 = (AST *)_ast;
			fp_ast = _ast21;
			if ( !guessing ) {
			ASTBase::tmake( NULL, (*_root)->bottom(), fp_ast , NULL);
			}
		}
	}
	zzmatch_wsig(TOK_RPAREN, _handler);	
	if ( !guessing ) {
	 _t16 = (ANTLRTokenPtr)LT(1);
}
 labase++;
	
	if ( !guessing ) {
		rp = _t16;
	}
	
	if ( !guessing ) {
	// Set the seglength to include up to right paren
	b_ast = (new AST( rp));
	top_ast->setSegLength(b_ast->getOffset() +
	1 -
	top_ast->getOffset());
	// Validate data items here
	pck->validate_transformer_data_items( tn_ast, fp_ast );
	delete b_ast;
	}
 consume();
	return _retv;
fail:
	if ( guessing ) zzGUESS_FAIL;
	syn(zzBadTok, "transform invocation", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd7, 0x80);
	return _retv;
_handler:
	zzdflthandlers(_signal,_retsignal);
	return _retv;
}

void
P::where_spec(ASTBase **_root,int *_retsignal)
{
	zzRULE;
	int _sva=1;
	ASTBase *_ast = NULL, *_sibling = NULL, *_tail = NULL;
	AST *_ast11=NULL;
	ANTLRTokenPtr e=NULL;
	AST *e_ast=NULL;
	int _signal=NoSignal;
	*_retsignal = NoSignal;
	t_core_data_type t;
	_ast = NULL;
	if ( !guessing ) {
		 t  = expr(&_ast,&_signal); if (_signal) goto _handler;
		if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
		_ast11 = (AST *)_ast;
		ASTBase::link(_root, &_sibling, &_tail);
		e_ast = _ast11;
	} else {
		expr(&_ast,&_signal);
	}
	if ( !guessing ) {
	if ( t != BOOLEAN_DATATYPE )
	AL_PARSE_ERR0( e_ast, AL_GETMSG(ERR,018,0) )
	if ( dumpflag && (*_root) )
	{
		((AST *)(*_root))->dumpTree("\nwhere_spec AST tree", ascii_buffer);
		printf("--------------------------------------------------\n");
		printf("QMark ASTs:\n");
		AST *look = ttqm->getItemHead();
		while (look)
		{
			look->dumpNode("  ");
			look = look->getItemNext();
		}
		printf("--------------------------------------------------\n");
	}
	}
	return;
fail:
	if ( guessing ) zzGUESS_FAIL;
	syn(zzBadTok, "where specification", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd8, 0x1);
_handler:
	zzdflthandlers(_signal,_retsignal);
	return;
}

void
P::assoc_obj_inst_ref_var(ASTBase **_root,int *_retsignal)
{
	zzRULE;
	int _sva=1;
	ASTBase *_ast = NULL, *_sibling = NULL, *_tail = NULL;
	AST *_ast11=NULL;
	int _signal=NoSignal;
	*_retsignal = NoSignal;
	_ast = NULL;
	inst_ref_var(&_ast,&_signal); if (_signal) goto _handler;
	if (!guessing) {    /* MR10 */
		if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
		_ast11 = (AST *)_ast;
		ASTBase::link(_root, &_sibling, &_tail);
	};    /* MR10 */
	return;
fail:
	if ( guessing ) zzGUESS_FAIL;
	syn(zzBadTok, "associative object instance reference variable", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd8, 0x2);
_handler:
	zzdflthandlers(_signal,_retsignal);
	return;
}

void
P::attribute(ASTBase **_root,int *_retsignal)
{
	zzRULE;
	int _sva=1;
	ASTBase *_ast = NULL, *_sibling = NULL, *_tail = NULL;
	AST *_ast11=NULL;
	ANTLRTokenPtr attr=NULL;
	AST *attr_ast=NULL;
	int _signal=NoSignal;
	*_retsignal = NoSignal;
	_ast = NULL;
	general_name(&_ast,&_signal); if (_signal) goto _handler;
	if (!guessing) {    /* MR10 */
		if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
		_ast11 = (AST *)_ast;
		ASTBase::link(_root, &_sibling, &_tail);
	};    /* MR10 */
	attr_ast = _ast11;
	if ( !guessing ) {
	attr_ast->setType(TOK_OBJ_ATTR);
	ttr->add( attr_ast );
	}
	return;
fail:
	if ( guessing ) zzGUESS_FAIL;
	syn(zzBadTok, "object attribute", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd8, 0x4);
_handler:
	zzdflthandlers(_signal,_retsignal);
	return;
}

 t_core_data_type  
P::bridge_function(ASTBase **_root,int *_retsignal, AST *ee_kl )
{
	 t_core_data_type  	 _retv;
	zzRULE;
	int _sva=1;
	ASTBase *_ast = NULL, *_sibling = NULL, *_tail = NULL;
	AST *_ast11=NULL;
	ANTLRTokenPtr bf=NULL;
	AST *bf_ast=NULL;
	int _signal=NoSignal;
	PURIFY(_retv,sizeof( t_core_data_type  	))
	*_retsignal = NoSignal;
	_ast = NULL;
	function_name(&_ast,&_signal); if (_signal) goto _handler;
	if (!guessing) {    /* MR10 */
		if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
		_ast11 = (AST *)_ast;
		ASTBase::link(_root, &_sibling, &_tail);
	};    /* MR10 */
	bf_ast = _ast11;
	if ( !guessing ) {
	pck->validate_bridge( bf_ast, ee_kl );
	_retv = pck->get_bridge_return_type( bf_ast );
	}
	return _retv;
fail:
	if ( guessing ) zzGUESS_FAIL;
	syn(zzBadTok, "bridge function", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd8, 0x8);
	return _retv;
_handler:
	zzdflthandlers(_signal,_retsignal);
	return _retv;
}

void
P::data_item(ASTBase **_root,int *_retsignal)
{
	zzRULE;
	int _sva=1;
	ASTBase *_ast = NULL, *_sibling = NULL, *_tail = NULL;
	AST *_ast11=NULL;
	ANTLRTokenPtr n=NULL;
	AST *n_ast=NULL;
	int _signal=NoSignal;
	*_retsignal = NoSignal;
	_ast = NULL;
	data_item_name(&_ast,&_signal); if (_signal) goto _handler;
	if (!guessing) {    /* MR10 */
		if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
		_ast11 = (AST *)_ast;
		ASTBase::link(_root, &_sibling, &_tail);
	};    /* MR10 */
	n_ast = _ast11;
	if ( !guessing ) {
	n_ast->setType(TOK_DATA_ITEM_NAME);
	ttr->add( n_ast );
	}
	return;
fail:
	if ( guessing ) zzGUESS_FAIL;
	syn(zzBadTok, "data item", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd8, 0x10);
_handler:
	zzdflthandlers(_signal,_retsignal);
	return;
}

void
P::data_item_name(ASTBase **_root,int *_retsignal)
{
	zzRULE;
	int _sva=1;
	ASTBase *_ast = NULL, *_sibling = NULL, *_tail = NULL;
	AST *_ast11=NULL;
	int _signal=NoSignal;
	*_retsignal = NoSignal;
	_ast = NULL;
	general_name(&_ast,&_signal); if (_signal) goto _handler;
	if (!guessing) {    /* MR10 */
		if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
		_ast11 = (AST *)_ast;
		ASTBase::link(_root, &_sibling, &_tail);
	};    /* MR10 */
	return;
fail:
	if ( guessing ) zzGUESS_FAIL;
	syn(zzBadTok, "data item name", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd8, 0x20);
_handler:
	zzdflthandlers(_signal,_retsignal);
	return;
}

void
P::enum_data_type(ASTBase **_root,int *_retsignal)
{
	zzRULE;
	int _sva=1;
	ASTBase *_ast = NULL, *_sibling = NULL, *_tail = NULL;
	AST *_ast11=NULL;
	ANTLRTokenPtr n=NULL;
	AST *n_ast=NULL;
	int _signal=NoSignal;
	*_retsignal = NoSignal;
	_ast = NULL;
	general_name(&_ast,&_signal); if (_signal) goto _handler;
	if (!guessing) {    /* MR10 */
		if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
		_ast11 = (AST *)_ast;
		ASTBase::link(_root, &_sibling, &_tail);
	};    /* MR10 */
	n_ast = _ast11;
	if ( !guessing ) {
	n_ast->setType(TOK_ENUMERATION); ttr->add( n_ast );
	}
	return;
fail:
	if ( guessing ) zzGUESS_FAIL;
	syn(zzBadTok, "enumeration data type", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd8, 0x40);
_handler:
	zzdflthandlers(_signal,_retsignal);
	return;
}

void
P::enumerator(ASTBase **_root,int *_retsignal)
{
	zzRULE;
	int _sva=1;
	ASTBase *_ast = NULL, *_sibling = NULL, *_tail = NULL;
	AST *_ast11=NULL;
	ANTLRTokenPtr n=NULL;
	AST *n_ast=NULL;
	int _signal=NoSignal;
	*_retsignal = NoSignal;
	_ast = NULL;
	general_name(&_ast,&_signal); if (_signal) goto _handler;
	if (!guessing) {    /* MR10 */
		if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
		_ast11 = (AST *)_ast;
		ASTBase::link(_root, &_sibling, &_tail);
	};    /* MR10 */
	n_ast = _ast11;
	if ( !guessing ) {
	n_ast->setType(TOK_ENUMERATOR); ttr->add( n_ast );
	}
	return;
fail:
	if ( guessing ) zzGUESS_FAIL;
	syn(zzBadTok, "enumerator", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd8, 0x80);
_handler:
	zzdflthandlers(_signal,_retsignal);
	return;
}

void
P::keyletters(ASTBase **_root,int *_retsignal)
{
	zzRULE;
	int _sva=1;
	ASTBase *_ast = NULL, *_sibling = NULL, *_tail = NULL;
	AST *_ast11=NULL;
	ANTLRTokenPtr kl=NULL;
	AST *kl_ast=NULL;
	int _signal=NoSignal;
	*_retsignal = NoSignal;
	_ast = NULL;
	general_name(&_ast,&_signal); if (_signal) goto _handler;
	if (!guessing) {    /* MR10 */
		if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
		_ast11 = (AST *)_ast;
		ASTBase::link(_root, &_sibling, &_tail);
	};    /* MR10 */
	kl_ast = _ast11;
	if ( !guessing ) {
	ttr->add( kl_ast );
	}
	return;
fail:
	if ( guessing ) zzGUESS_FAIL;
	syn(zzBadTok, "keyletters", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd9, 0x1);
_handler:
	zzdflthandlers(_signal,_retsignal);
	return;
}

void
P::ee_keyletters(ASTBase **_root,int *_retsignal)
{
	zzRULE;
	int _sva=1;
	ASTBase *_ast = NULL, *_sibling = NULL, *_tail = NULL;
	AST *_ast11=NULL;
	ANTLRTokenPtr eekl=NULL;
	AST *eekl_ast=NULL;
	int _signal=NoSignal;
	*_retsignal = NoSignal;
	_ast = NULL;
	keyletters(&_ast,&_signal); if (_signal) goto _handler;
	if (!guessing) {    /* MR10 */
		if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
		_ast11 = (AST *)_ast;
		ASTBase::link(_root, &_sibling, &_tail);
	};    /* MR10 */
	eekl_ast = _ast11;
	if ( !guessing ) {
	eekl_ast->setType(TOK_KL_EXTERNAL_ENTITY);
	pck->validate_ee_kl( eekl_ast );
	}
	return;
fail:
	if ( guessing ) zzGUESS_FAIL;
	syn(zzBadTok, "external entity keyletters", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd9, 0x2);
_handler:
	zzdflthandlers(_signal,_retsignal);
	return;
}

void
P::event_label(ASTBase **_root,int *_retsignal)
{
	zzRULE;
	int _sva=1;
	ASTBase *_ast = NULL, *_sibling = NULL, *_tail = NULL;
	AST *_ast11=NULL;
	ANTLRTokenPtr el=NULL;
	AST *el_ast=NULL;
	int _signal=NoSignal;
	*_retsignal = NoSignal;
	_ast = NULL;
	general_name(&_ast,&_signal); if (_signal) goto _handler;
	if (!guessing) {    /* MR10 */
		if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
		_ast11 = (AST *)_ast;
		ASTBase::link(_root, &_sibling, &_tail);
	};    /* MR10 */
	el_ast = _ast11;
	if ( !guessing ) {
	el_ast->setType(TOK_EVENT_LABEL);
	ttr->add( el_ast );
	}
	return;
fail:
	if ( guessing ) zzGUESS_FAIL;
	syn(zzBadTok, "event label", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd9, 0x4);
_handler:
	zzdflthandlers(_signal,_retsignal);
	return;
}

void
P::event_meaning(ASTBase **_root,int *_retsignal)
{
	zzRULE;
	int _sva=1;
	ASTBase *_ast = NULL, *_sibling = NULL, *_tail = NULL;
;
	ANTLRTokenPtr em1=NULL, em2=NULL;
	AST *em1_ast=NULL, *em2_ast=NULL;
	int _signal=NoSignal;
	*_retsignal = NoSignal;
	AST *em = NULL;
	{
		AST *_ast21=NULL;
		if ( (LA(1)==TOK_BADPHRASE_EOF || LA(1)==TOK_PHRASE || LA(1)==TOK_BADPHRASE_NL) ) {
			_ast = NULL;
			phrase(&_ast,&_signal); if (_signal) goto _handler;
			if (!guessing) {    /* MR10 */
				if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
				_ast21 = (AST *)_ast;
				ASTBase::link(_root, &_sibling, &_tail);
			};    /* MR10 */
			em1_ast = _ast21;
			if ( !guessing ) {
			em = em1_ast;
			}
		}
		else {
			if ( (
LA(1)==TOK_ACROSS || LA(1)==TOK_ANY || LA(1)==TOK_ASSIGNER || LA(1)==TOK_ASSIGN || LA(1)==TOK_BREAKTOKEN || 
LA(1)==TOK_BY || LA(1)==TOK_CLASS || LA(1)==TOK_CONTINUE || LA(1)==TOK_CONTROL || LA(1)==TOK_CREATE || 
LA(1)==TOK_CREATOR || LA(1)==TOK_DELETE || LA(1)==TOK_EACH || LA(1)==TOK_END || LA(1)==TOK_EVENT || 
LA(1)==TOK_FOR || LA(1)==TOK_FROM || LA(1)==TOK_GENERATE || LA(1)==TOK_IN || LA(1)==TOK_INSTANCES || 
LA(1)==TOK_INSTANCE || LA(1)==TOK_MANY || LA(1)==TOK_OBJECT || LA(1)==TOK_OF || LA(1)==TOK_ONE || 
LA(1)==TOK_RELATED || LA(1)==TOK_RELATE || LA(1)==TOK_SELECT || LA(1)==TOK_STOP || LA(1)==TOK_TO || 
LA(1)==TOK_WHERE || LA(1)==TOK_UNRELATE || LA(1)==TOK_USING || LA(1)==TOK_BRIDGE || LA(1)==TOK_CARDINALITY || 
LA(1)==TOK_EMPTY || LA(1)==TOK_FALSETOKEN || LA(1)==TOK_NOT || LA(1)==TOK_NOTEMPTY || LA(1)==TOK_TRANSFORM || 
LA(1)==TOK_TRUETOKEN || LA(1)==TOK_PARAM || LA(1)==TOK_RCVD_EVT || LA(1)==TOK_SELECTED || LA(1)==TOK_SELF || 
LA(1)==TOK_GENERAL_NAME || LA(1)==TOK_GARBAGE || LA(1)==TOK_BAD_ID || LA(1)==TOK_BAD_NAME || LA(1)==TOK_ID || 
LA(1)==TOK_RELID) ) {
				_ast = NULL;
				general_name(&_ast,&_signal); if (_signal) goto _handler;
				if (!guessing) {    /* MR10 */
					if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
					_ast21 = (AST *)_ast;
					ASTBase::link(_root, &_sibling, &_tail);
				};    /* MR10 */
				em2_ast = _ast21;
				if ( !guessing ) {
				em = em2_ast;
				}
			}
			else {
				if ( guessing ) goto fail;
				if (_sva) _signal=NoViableAlt;
				else _signal=NoSemViableAlt;
				goto _handler;  /* MR7 */
			}
		}
	}
	if ( !guessing ) {
	ttr->add( em );
	em->setType(TOK_PHRASE);
	}
	return;
fail:
	if ( guessing ) zzGUESS_FAIL;
	syn(zzBadTok, "event meaning", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd9, 0x8);
_handler:
	zzdflthandlers(_signal,_retsignal);
	return;
}

void
P::general_name(ASTBase **_root,int *_retsignal)
{
	zzRULE;
	int _sva=1;
	ASTBase *_ast = NULL, *_sibling = NULL, *_tail = NULL;
;
	ANTLRTokenPtr gn1=NULL, gn2=NULL, gn3=NULL, gn4=NULL, gn5=NULL, gn8=NULL, gn9=NULL, gna=NULL;
	AST *gn1_ast=NULL, *gn2_ast=NULL, *gn3_ast=NULL, *gn4_ast=NULL, *gn5_ast=NULL, *gn8_ast=NULL, *gn9_ast=NULL, *gna_ast=NULL;
	int _signal=NoSignal;
	*_retsignal = NoSignal;
	AST *gn = NULL;
	{
		ANTLRTokenPtr _t21=NULL;
		AST *_ast21=NULL;
		if ( (LA(1)==TOK_ID || LA(1)==TOK_RELID) ) {
			_ast = NULL;
			limited_name(&_ast,&_signal); if (_signal) goto _handler;
			if (!guessing) {    /* MR10 */
				if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
				_ast21 = (AST *)_ast;
				ASTBase::link(_root, &_sibling, &_tail);
			};    /* MR10 */
			gn1_ast = _ast21;
			if ( !guessing ) {
			gn = gn1_ast;
			}
		}
		else {
			if ( (
LA(1)==TOK_GENERAL_NAME) ) {
				zzmatch_wsig(TOK_GENERAL_NAME, _handler);				
				if ( !guessing ) {
				 _t21 = (ANTLRTokenPtr)LT(1);
}
 labase++;
				if ( !guessing ) {
				
				_ast21 = new AST(_t21);
				_ast21->subchild(_root, &_sibling, &_tail);
				}
				
				if ( !guessing ) {
								gn2 = _t21;
				gn2_ast = _ast21;
				}
				
				if ( !guessing ) {
				gn = gn2_ast;
				gn->setSegLength(strlen(gn->getAsciiText()));
				}
 consume();
			}
			else {
				if ( (LA(1)==TOK_ACROSS || LA(1)==TOK_ANY || LA(1)==TOK_ASSIGNER || 
LA(1)==TOK_ASSIGN || LA(1)==TOK_BREAKTOKEN || LA(1)==TOK_BY || LA(1)==TOK_CLASS || LA(1)==TOK_CONTINUE || 
LA(1)==TOK_CONTROL || LA(1)==TOK_CREATE || LA(1)==TOK_CREATOR || LA(1)==TOK_DELETE || LA(1)==TOK_EACH || 
LA(1)==TOK_END || LA(1)==TOK_EVENT || LA(1)==TOK_FOR || LA(1)==TOK_FROM || LA(1)==TOK_GENERATE || 
LA(1)==TOK_IN || LA(1)==TOK_INSTANCES || LA(1)==TOK_INSTANCE || LA(1)==TOK_MANY || LA(1)==TOK_OBJECT || 
LA(1)==TOK_OF || LA(1)==TOK_ONE || LA(1)==TOK_RELATED || LA(1)==TOK_RELATE || LA(1)==TOK_SELECT || 
LA(1)==TOK_STOP || LA(1)==TOK_TO || LA(1)==TOK_WHERE || LA(1)==TOK_UNRELATE || LA(1)==TOK_USING)
 ) {
					_ast = NULL;
					kw_as_id1(&_ast,&_signal); if (_signal) goto _handler;
					if (!guessing) {    /* MR10 */
						if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
						_ast21 = (AST *)_ast;
						ASTBase::link(_root, &_sibling, &_tail);
					};    /* MR10 */
					gn3_ast = _ast21;
					if ( !guessing ) {
					gn = gn3_ast;
					}
				}
				else {
					if ( (LA(1)==TOK_BRIDGE || LA(1)==TOK_CARDINALITY || LA(1)==TOK_EMPTY || LA(1)==TOK_FALSETOKEN || 
LA(1)==TOK_NOT || LA(1)==TOK_NOTEMPTY || LA(1)==TOK_TRANSFORM || LA(1)==TOK_TRUETOKEN) ) {
						_ast = NULL;
						kw_as_id2(&_ast,&_signal); if (_signal) goto _handler;
						if (!guessing) {    /* MR10 */
							if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
							_ast21 = (AST *)_ast;
							ASTBase::link(_root, &_sibling, &_tail);
						};    /* MR10 */
						gn4_ast = _ast21;
						if ( !guessing ) {
						gn = gn4_ast;
						}
					}
					else {
						if ( (
LA(1)==TOK_PARAM || LA(1)==TOK_RCVD_EVT || LA(1)==TOK_SELECTED || LA(1)==TOK_SELF) ) {
							_ast = NULL;
							kw_as_id3(&_ast,&_signal); if (_signal) goto _handler;
							if (!guessing) {    /* MR10 */
								if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
								_ast21 = (AST *)_ast;
								ASTBase::link(_root, &_sibling, &_tail);
							};    /* MR10 */
							gn5_ast = _ast21;
							if ( !guessing ) {
							gn = gn5_ast;
							AL_PARSE_ERR1( gn, AL_GETMSG(ERR,265,1), gn->getVcharText() )
							}
						}
						else {
							if ( (
LA(1)==TOK_GARBAGE) ) {
								zzmatch_wsig(TOK_GARBAGE, _handler);								
								if ( !guessing ) {
								 _t21 = (ANTLRTokenPtr)LT(1);
}
 labase++;
								if ( !guessing ) {
								
								_ast21 = new AST(_t21);
								_ast21->subchild(_root, &_sibling, &_tail);
								}
								
								if ( !guessing ) {
																gn8 = _t21;
								gn8_ast = _ast21;
								}
								
								if ( !guessing ) {
								gn = gn8_ast;
								gn->setSegLength(strlen(gn->getAsciiText()));
								AL_PARSE_ERR1( gn, AL_GETMSG(ERR, 300, 1), gn->getVcharText() )
								}
 consume();
							}
							else {
								if ( (LA(1)==TOK_BAD_ID) ) {
									zzmatch_wsig(TOK_BAD_ID, _handler);									
									if ( !guessing ) {
									 _t21 = (ANTLRTokenPtr)LT(1);
}
 labase++;
									if ( !guessing ) {
									
									_ast21 = new AST(_t21);
									_ast21->subchild(_root, &_sibling, &_tail);
									}
									
									if ( !guessing ) {
																		gn9 = _t21;
									gn9_ast = _ast21;
									}
									
									if ( !guessing ) {
									gn = gn9_ast;
									gn->setSegLength(strlen(gn->getAsciiText()));
									AL_PARSE_ERR1( gn, AL_GETMSG(ERR, 300, 1), gn->getVcharText() )
									}
 consume();
								}
								else {
									if ( (LA(1)==TOK_BAD_NAME)
 ) {
										zzmatch_wsig(TOK_BAD_NAME, _handler);										
										if ( !guessing ) {
										 _t21 = (ANTLRTokenPtr)LT(1);
}
 labase++;
										if ( !guessing ) {
										
										_ast21 = new AST(_t21);
										_ast21->subchild(_root, &_sibling, &_tail);
										}
										
										if ( !guessing ) {
																				gna = _t21;
										gna_ast = _ast21;
										}
										
										if ( !guessing ) {
										gn = gna_ast;
										gn->setSegLength(strlen(gn->getAsciiText()));
										AL_PARSE_ERR1( gn, AL_GETMSG(ERR, 300, 1), gn->getVcharText() )
										}
 consume();
									}
									else {
										if ( guessing ) goto fail;
										if (_sva) _signal=NoViableAlt;
										else _signal=NoSemViableAlt;
										goto _handler;  /* MR7 */
									}
								}
							}
						}
					}
				}
			}
		}
	}
	if ( !guessing ) {
	gn->setType(TOK_ID);
	}
	return;
fail:
	if ( guessing ) zzGUESS_FAIL;
	syn(zzBadTok, "general name", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd9, 0x10);
_handler:
	zzdflthandlers(_signal,_retsignal);
	return;
}

void
P::svc_general_name(ASTBase **_root,int *_retsignal)
{
	zzRULE;
	int _sva=1;
	ASTBase *_ast = NULL, *_sibling = NULL, *_tail = NULL;
;
	ANTLRTokenPtr gn1=NULL, gn2=NULL, gn3=NULL, gn4=NULL, gn5=NULL, gn7=NULL, gn8=NULL, gn9=NULL, gna=NULL;
	AST *gn1_ast=NULL, *gn2_ast=NULL, *gn3_ast=NULL, *gn4_ast=NULL, *gn5_ast=NULL, *gn7_ast=NULL, *gn8_ast=NULL, *gn9_ast=NULL, *gna_ast=NULL;
	int _signal=NoSignal;
	*_retsignal = NoSignal;
	AST *gn = NULL;
	{
		ANTLRTokenPtr _t21=NULL;
		AST *_ast21=NULL;
		if ( (LA(1)==TOK_ID || LA(1)==TOK_RELID) ) {
			_ast = NULL;
			limited_name(&_ast,&_signal); if (_signal) goto _handler;
			if (!guessing) {    /* MR10 */
				if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
				_ast21 = (AST *)_ast;
				ASTBase::link(_root, &_sibling, &_tail);
			};    /* MR10 */
			gn1_ast = _ast21;
			if ( !guessing ) {
			gn = gn1_ast;
			}
		}
		else {
			if ( (LA(1)==TOK_GENERAL_NAME)
 ) {
				zzmatch_wsig(TOK_GENERAL_NAME, _handler);				
				if ( !guessing ) {
				 _t21 = (ANTLRTokenPtr)LT(1);
}
 labase++;
				if ( !guessing ) {
				
				_ast21 = new AST(_t21);
				_ast21->subchild(_root, &_sibling, &_tail);
				}
				
				if ( !guessing ) {
								gn2 = _t21;
				gn2_ast = _ast21;
				}
				
				if ( !guessing ) {
				gn = gn2_ast;
				gn->setSegLength(strlen(gn->getAsciiText()));
				}
 consume();
			}
			else {
				if ( (LA(1)==TOK_ACROSS || LA(1)==TOK_ANY || LA(1)==TOK_ASSIGNER || LA(1)==TOK_ASSIGN || 
LA(1)==TOK_BREAKTOKEN || LA(1)==TOK_BY || LA(1)==TOK_CLASS || LA(1)==TOK_CONTINUE || LA(1)==TOK_CONTROL || 
LA(1)==TOK_CREATE || LA(1)==TOK_CREATOR || LA(1)==TOK_DELETE || LA(1)==TOK_EACH || LA(1)==TOK_END || 
LA(1)==TOK_EVENT || LA(1)==TOK_FOR || LA(1)==TOK_FROM || LA(1)==TOK_GENERATE || LA(1)==TOK_IN || 
LA(1)==TOK_INSTANCES || LA(1)==TOK_INSTANCE || LA(1)==TOK_MANY || LA(1)==TOK_OBJECT || LA(1)==TOK_OF || 
LA(1)==TOK_ONE || LA(1)==TOK_RELATED || LA(1)==TOK_RELATE || LA(1)==TOK_SELECT || LA(1)==TOK_STOP || 
LA(1)==TOK_TO || LA(1)==TOK_WHERE || LA(1)==TOK_UNRELATE || LA(1)==TOK_USING) ) {
					_ast = NULL;
					kw_as_id1(&_ast,&_signal); if (_signal) goto _handler;
					if (!guessing) {    /* MR10 */
						if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
						_ast21 = (AST *)_ast;
						ASTBase::link(_root, &_sibling, &_tail);
					};    /* MR10 */
					gn3_ast = _ast21;
					if ( !guessing ) {
					gn = gn3_ast;
					}
				}
				else {
					if ( (
LA(1)==TOK_BRIDGE || LA(1)==TOK_CARDINALITY || LA(1)==TOK_EMPTY || LA(1)==TOK_FALSETOKEN || LA(1)==TOK_NOT || 
LA(1)==TOK_NOTEMPTY || LA(1)==TOK_TRANSFORM || LA(1)==TOK_TRUETOKEN) ) {
						_ast = NULL;
						kw_as_id2(&_ast,&_signal); if (_signal) goto _handler;
						if (!guessing) {    /* MR10 */
							if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
							_ast21 = (AST *)_ast;
							ASTBase::link(_root, &_sibling, &_tail);
						};    /* MR10 */
						gn4_ast = _ast21;
						if ( !guessing ) {
						gn = gn4_ast;
						}
					}
					else {
						if ( (LA(1)==TOK_PARAM || 
LA(1)==TOK_RCVD_EVT || LA(1)==TOK_SELECTED || LA(1)==TOK_SELF) ) {
							_ast = NULL;
							kw_as_id3(&_ast,&_signal); if (_signal) goto _handler;
							if (!guessing) {    /* MR10 */
								if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
								_ast21 = (AST *)_ast;
								ASTBase::link(_root, &_sibling, &_tail);
							};    /* MR10 */
							gn5_ast = _ast21;
							if ( !guessing ) {
							gn = gn5_ast;
							AL_PARSE_ERR1( gn, AL_GETMSG(ERR,265,1), gn->getVcharText() )
							}
						}
						else {
							if ( (LA(1)==TOK_AND || 
LA(1)==TOK_ELIF || LA(1)==TOK_ELSE || LA(1)==TOK_IF || LA(1)==TOK_OR || LA(1)==TOK_RETURN || 
LA(1)==TOK_WHILE) ) {
								_ast = NULL;
								kw_as_id4(&_ast,&_signal); if (_signal) goto _handler;
								if (!guessing) {    /* MR10 */
									if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
									_ast21 = (AST *)_ast;
									ASTBase::link(_root, &_sibling, &_tail);
								};    /* MR10 */
								gn7_ast = _ast21;
								if ( !guessing ) {
								gn = gn7_ast;
								}
							}
							else {
								if ( (LA(1)==TOK_GARBAGE) ) {
									zzmatch_wsig(TOK_GARBAGE, _handler);									
									if ( !guessing ) {
									 _t21 = (ANTLRTokenPtr)LT(1);
}
 labase++;
									if ( !guessing ) {
									
									_ast21 = new AST(_t21);
									_ast21->subchild(_root, &_sibling, &_tail);
									}
									
									if ( !guessing ) {
																		gn8 = _t21;
									gn8_ast = _ast21;
									}
									
									if ( !guessing ) {
									gn = gn8_ast;
									gn->setSegLength(strlen(gn->getAsciiText()));
									AL_PARSE_ERR1( gn, AL_GETMSG(ERR, 300, 1), gn->getVcharText() )
									}
 consume();
								}
								else {
									if ( (LA(1)==TOK_BAD_ID)
 ) {
										zzmatch_wsig(TOK_BAD_ID, _handler);										
										if ( !guessing ) {
										 _t21 = (ANTLRTokenPtr)LT(1);
}
 labase++;
										if ( !guessing ) {
										
										_ast21 = new AST(_t21);
										_ast21->subchild(_root, &_sibling, &_tail);
										}
										
										if ( !guessing ) {
																				gn9 = _t21;
										gn9_ast = _ast21;
										}
										
										if ( !guessing ) {
										gn = gn9_ast;
										gn->setSegLength(strlen(gn->getAsciiText()));
										AL_PARSE_ERR1( gn, AL_GETMSG(ERR, 300, 1), gn->getVcharText() )
										}
 consume();
									}
									else {
										if ( (LA(1)==TOK_BAD_NAME) ) {
											zzmatch_wsig(TOK_BAD_NAME, _handler);											
											if ( !guessing ) {
											 _t21 = (ANTLRTokenPtr)LT(1);
}
 labase++;
											if ( !guessing ) {
											
											_ast21 = new AST(_t21);
											_ast21->subchild(_root, &_sibling, &_tail);
											}
											
											if ( !guessing ) {
																						gna = _t21;
											gna_ast = _ast21;
											}
											
											if ( !guessing ) {
											gn = gna_ast;
											gn->setSegLength(strlen(gn->getAsciiText()));
											AL_PARSE_ERR1( gn, AL_GETMSG(ERR, 300, 1), gn->getVcharText() )
											}
 consume();
										}
										else {
											if ( guessing ) goto fail;
											if (_sva) _signal=NoViableAlt;
											else _signal=NoSemViableAlt;
											goto _handler;  /* MR7 */
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	if ( !guessing ) {
	gn->setType(TOK_ID);
	}
	return;
fail:
	if ( guessing ) zzGUESS_FAIL;
	syn(zzBadTok, "service general name", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd9, 0x20);
_handler:
	zzdflthandlers(_signal,_retsignal);
	return;
}

void
P::limited_name(ASTBase **_root,int *_retsignal)
{
	zzRULE;
	int _sva=1;
	ASTBase *_ast = NULL, *_sibling = NULL, *_tail = NULL;
	ANTLRTokenPtr _t11=NULL;
	AST *_ast11=NULL;
	ANTLRTokenPtr i1=NULL, i2=NULL;
	AST *i1_ast=NULL, *i2_ast=NULL;
	int _signal=NoSignal;
	*_retsignal = NoSignal;
	if ( (LA(1)==TOK_ID) ) {
		zzmatch_wsig(TOK_ID, _handler);		
		if ( !guessing ) {
		 _t11 = (ANTLRTokenPtr)LT(1);
}
 labase++;
		if ( !guessing ) {
		
		_ast11 = new AST(_t11);
		_ast11->subchild(_root, &_sibling, &_tail);
		}
		
		if ( !guessing ) {
				i1 = _t11;
		i1_ast = _ast11;
		}
		
		if ( !guessing ) {
		i1_ast->setSegLength(strlen(i1_ast->getAsciiText()));
		}
 consume();
	}
	else {
		if ( (
LA(1)==TOK_RELID) ) {
			zzmatch_wsig(TOK_RELID, _handler);			
			if ( !guessing ) {
			 _t11 = (ANTLRTokenPtr)LT(1);
}
 labase++;
			if ( !guessing ) {
			
			_ast11 = new AST(_t11);
			_ast11->subchild(_root, &_sibling, &_tail);
			}
			
			if ( !guessing ) {
						i2 = _t11;
			i2_ast = _ast11;
			}
			
			if ( !guessing ) {
			i2_ast->setType(TOK_ID);
			i2_ast->setSegLength(strlen(i2_ast->getAsciiText()));
			}
 consume();
		}
		else {
			if ( guessing ) goto fail;
			if (_sva) _signal=NoViableAlt;
			else _signal=NoSemViableAlt;
			goto _handler;  /* MR7 */
		}
	}
	return;
fail:
	if ( guessing ) zzGUESS_FAIL;
	syn(zzBadTok, "limited name", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd9, 0x40);
_handler:
	zzdflthandlers(_signal,_retsignal);
	return;
}

void
P::inst_ref_set_var(ASTBase **_root,int *_retsignal)
{
	zzRULE;
	int _sva=1;
	ASTBase *_ast = NULL, *_sibling = NULL, *_tail = NULL;
	AST *_ast11=NULL;
	ANTLRTokenPtr irsv=NULL;
	AST *irsv_ast=NULL;
	int _signal=NoSignal;
	*_retsignal = NoSignal;
	Sym *s_ref;
	_ast = NULL;
	local_variable(&_ast,&_signal, ASSIGN_RVAL ); if (_signal) goto _handler;
	if (!guessing) {    /* MR10 */
		if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
		_ast11 = (AST *)_ast;
		ASTBase::link(_root, &_sibling, &_tail);
	};    /* MR10 */
	irsv_ast = _ast11;
	if ( !guessing ) {
	irsv_ast->setType(TOK_INST_REF_SET_VAR);
	if ( st->is_inst_ref_set_var( irsv_ast->getVcharText(), &s_ref ) )
	irsv_ast->setObjPtr( s_ref->objPtr );
	else
	AL_PARSE_ERR1( irsv_ast, AL_GETMSG(ERR,041,1), irsv_ast->getVcharText() )
	}
	return;
fail:
	if ( guessing ) zzGUESS_FAIL;
	syn(zzBadTok, "instance reference set variable", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd9, 0x80);
_handler:
	zzdflthandlers(_signal,_retsignal);
	return;
}

void
P::inst_ref_var(ASTBase **_root,int *_retsignal)
{
	zzRULE;
	int _sva=1;
	ASTBase *_ast = NULL, *_sibling = NULL, *_tail = NULL;
	AST *_ast11=NULL;
	ANTLRTokenPtr lv=NULL;
	AST *lv_ast=NULL;
	int _signal=NoSignal;
	*_retsignal = NoSignal;
	Sym *s_ref;
	_ast = NULL;
	local_variable(&_ast,&_signal, ASSIGN_RVAL ); if (_signal) goto _handler;
	if (!guessing) {    /* MR10 */
		if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
		_ast11 = (AST *)_ast;
		ASTBase::link(_root, &_sibling, &_tail);
	};    /* MR10 */
	lv_ast = _ast11;
	if ( !guessing ) {
	lv_ast->setType(TOK_INST_REF_VAR);
	if ( st->is_inst_ref_var( lv_ast->getVcharText(), &s_ref ) )
	lv_ast->setObjPtr( s_ref->objPtr );
	else
	AL_PARSE_ERR1( lv_ast, AL_GETMSG(ERR,041,1), lv_ast->getVcharText() )
	}
	return;
fail:
	if ( guessing ) zzGUESS_FAIL;
	syn(zzBadTok, "instance reference variable", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd10, 0x1);
_handler:
	zzdflthandlers(_signal,_retsignal);
	return;
}

void
P::kw_as_id1(ASTBase **_root,int *_retsignal)
{
	zzRULE;
	int _sva=1;
	ASTBase *_ast = NULL, *_sibling = NULL, *_tail = NULL;
	ANTLRTokenPtr _t11=NULL;
	AST *_ast11=NULL;
	ANTLRTokenPtr x=NULL;
	AST *x_ast=NULL;
	int _signal=NoSignal;
	*_retsignal = NoSignal;
	zzsetmatch_wsig(err1, _handler);	
	if ( !guessing ) {
	 _t11 = (ANTLRTokenPtr)LT(1);
}
 labase++;
	if ( !guessing ) {
	
	_ast11 = new AST(_t11);
	_ast11->subchild(_root, &_sibling, &_tail);
	}
	
	if ( !guessing ) {
		x = _t11;
	x_ast = _ast11;
	}
	
	if ( !guessing ) {
	x_ast->setType(TOK_ID);
	x_ast->setSegLength(strlen(x_ast->getAsciiText()));
	}
 consume();
	return;
fail:
	if ( guessing ) zzGUESS_FAIL;
	syn(zzBadTok, "keyword as identifier", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd10, 0x2);
_handler:
	zzdflthandlers(_signal,_retsignal);
	return;
}

void
P::kw_as_id2(ASTBase **_root,int *_retsignal)
{
	zzRULE;
	int _sva=1;
	ASTBase *_ast = NULL, *_sibling = NULL, *_tail = NULL;
	ANTLRTokenPtr _t11=NULL;
	AST *_ast11=NULL;
	ANTLRTokenPtr x=NULL;
	AST *x_ast=NULL;
	int _signal=NoSignal;
	*_retsignal = NoSignal;
	zzsetmatch_wsig(err2, _handler);	
	if ( !guessing ) {
	 _t11 = (ANTLRTokenPtr)LT(1);
}
 labase++;
	if ( !guessing ) {
	
	_ast11 = new AST(_t11);
	_ast11->subchild(_root, &_sibling, &_tail);
	}
	
	if ( !guessing ) {
		x = _t11;
	x_ast = _ast11;
	}
	
	if ( !guessing ) {
	x_ast->setType(TOK_ID);
	x_ast->setSegLength(strlen(x_ast->getAsciiText()));
	}
 consume();
	return;
fail:
	if ( guessing ) zzGUESS_FAIL;
	syn(zzBadTok, "keyword as identifier", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd10, 0x4);
_handler:
	zzdflthandlers(_signal,_retsignal);
	return;
}

void
P::kw_as_id3(ASTBase **_root,int *_retsignal)
{
	zzRULE;
	int _sva=1;
	ASTBase *_ast = NULL, *_sibling = NULL, *_tail = NULL;
	ANTLRTokenPtr _t11=NULL;
	AST *_ast11=NULL;
	ANTLRTokenPtr x=NULL;
	AST *x_ast=NULL;
	int _signal=NoSignal;
	*_retsignal = NoSignal;
	zzsetmatch_wsig(err3, _handler);	
	if ( !guessing ) {
	 _t11 = (ANTLRTokenPtr)LT(1);
}
 labase++;
	if ( !guessing ) {
	
	_ast11 = new AST(_t11);
	_ast11->subchild(_root, &_sibling, &_tail);
	}
	
	if ( !guessing ) {
		x = _t11;
	x_ast = _ast11;
	}
	
	if ( !guessing ) {
	x_ast->setType(TOK_ID);
	x_ast->setSegLength(strlen(x_ast->getAsciiText()));
	}
 consume();
	return;
fail:
	if ( guessing ) zzGUESS_FAIL;
	syn(zzBadTok, "keyword as identifier", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd10, 0x8);
_handler:
	zzdflthandlers(_signal,_retsignal);
	return;
}

void
P::kw_as_id4(ASTBase **_root,int *_retsignal)
{
	zzRULE;
	int _sva=1;
	ASTBase *_ast = NULL, *_sibling = NULL, *_tail = NULL;
	ANTLRTokenPtr _t11=NULL;
	AST *_ast11=NULL;
	ANTLRTokenPtr x=NULL;
	AST *x_ast=NULL;
	int _signal=NoSignal;
	*_retsignal = NoSignal;
	zzsetmatch_wsig(err4, _handler);	
	if ( !guessing ) {
	 _t11 = (ANTLRTokenPtr)LT(1);
}
 labase++;
	if ( !guessing ) {
	
	_ast11 = new AST(_t11);
	_ast11->subchild(_root, &_sibling, &_tail);
	}
	
	if ( !guessing ) {
		x = _t11;
	x_ast = _ast11;
	}
	
	if ( !guessing ) {
	x_ast->setType(TOK_ID);
	x_ast->setSegLength(strlen(x_ast->getAsciiText()));
	}
 consume();
	return;
fail:
	if ( guessing ) zzGUESS_FAIL;
	syn(zzBadTok, "keyword as identifier", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd10, 0x10);
_handler:
	zzdflthandlers(_signal,_retsignal);
	return;
}

void
P::local_variable(ASTBase **_root,int *_retsignal, Assign_Val_e isLval )
{
	zzRULE;
	int _sva=1;
	ASTBase *_ast = NULL, *_sibling = NULL, *_tail = NULL;
;
	ANTLRTokenPtr lv1=NULL, lv2=NULL, lv3=NULL, lv4=NULL, lv5=NULL, lv6=NULL, lv7=NULL;
	AST *lv1_ast=NULL, *lv2_ast=NULL, *lv3_ast=NULL, *lv4_ast=NULL, *lv5_ast=NULL, *lv6_ast=NULL, *lv7_ast=NULL;
	int _signal=NoSignal;
	*_retsignal = NoSignal;
	Sym * s_ref;
	AST *lv = NULL;
	{
		ANTLRTokenPtr _t21=NULL;
		AST *_ast21=NULL;
		if ( (LA(1)==TOK_ID || LA(1)==TOK_RELID) ) {
			_ast = NULL;
			limited_name(&_ast,&_signal); if (_signal) goto _handler;
			if (!guessing) {    /* MR10 */
				if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
				_ast21 = (AST *)_ast;
				ASTBase::link(_root, &_sibling, &_tail);
			};    /* MR10 */
			lv1_ast = _ast21;
			if ( !guessing ) {
			lv = lv1_ast;
			}
		}
		else {
			if ( (
LA(1)==TOK_ACROSS || LA(1)==TOK_ANY || LA(1)==TOK_ASSIGNER || LA(1)==TOK_ASSIGN || LA(1)==TOK_BREAKTOKEN || 
LA(1)==TOK_BY || LA(1)==TOK_CLASS || LA(1)==TOK_CONTINUE || LA(1)==TOK_CONTROL || LA(1)==TOK_CREATE || 
LA(1)==TOK_CREATOR || LA(1)==TOK_DELETE || LA(1)==TOK_EACH || LA(1)==TOK_END || LA(1)==TOK_EVENT || 
LA(1)==TOK_FOR || LA(1)==TOK_FROM || LA(1)==TOK_GENERATE || LA(1)==TOK_IN || LA(1)==TOK_INSTANCES || 
LA(1)==TOK_INSTANCE || LA(1)==TOK_MANY || LA(1)==TOK_OBJECT || LA(1)==TOK_OF || LA(1)==TOK_ONE || 
LA(1)==TOK_RELATED || LA(1)==TOK_RELATE || LA(1)==TOK_SELECT || LA(1)==TOK_STOP || LA(1)==TOK_TO || 
LA(1)==TOK_WHERE || LA(1)==TOK_UNRELATE || LA(1)==TOK_USING) ) {
				_ast = NULL;
				kw_as_id1(&_ast,&_signal); if (_signal) goto _handler;
				if (!guessing) {    /* MR10 */
					if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
					_ast21 = (AST *)_ast;
					ASTBase::link(_root, &_sibling, &_tail);
				};    /* MR10 */
				lv2_ast = _ast21;
				if ( !guessing ) {
				lv = lv2_ast;
				}
			}
			else {
				if ( (LA(1)==TOK_SELECTED)
 ) {
					zzmatch_wsig(TOK_SELECTED, _handler);					
					if ( !guessing ) {
					 _t21 = (ANTLRTokenPtr)LT(1);
}
 labase++;
					if ( !guessing ) {
					
					_ast21 = new AST(_t21);
					_ast21->subchild(_root, &_sibling, &_tail);
					}
					
					if ( !guessing ) {
										lv3 = _t21;
					lv3_ast = _ast21;
					}
					
					if ( !guessing ) {
					lv = lv3_ast;
					lv->setSegLength(strlen(lv->getAsciiText()));
					if ( ! in_where )
					AL_PARSE_ERR0( lv, AL_GETMSG(ERR,154,0) )
					selected_found = TRUE;
					}
 consume();
				}
				else {
					if ( (LA(1)==TOK_SELF) ) {
						zzmatch_wsig(TOK_SELF, _handler);						
						if ( !guessing ) {
						 _t21 = (ANTLRTokenPtr)LT(1);
}
 labase++;
						if ( !guessing ) {
						
						_ast21 = new AST(_t21);
						_ast21->subchild(_root, &_sibling, &_tail);
						}
						
						if ( !guessing ) {
												lv4 = _t21;
						lv4_ast = _ast21;
						}
						
						if ( !guessing ) {
						lv = lv4_ast;
						lv->setSegLength(strlen(lv->getAsciiText()));
						if (! self_valid)
						{
							if ( ! ( st->is_inst_ref_var( lv->getVcharText(), &s_ref) ) )
							{
								AL_PARSE_ERR1( lv, AL_GETMSG(ERR,156,1), spec_descr.char_ptr() )
							}
						}
						else if ( isLval == ASSIGN_LVAL )
						AL_PARSE_ERR0( lv, AL_GETMSG(ERR,284,0) )
						}
 consume();
					}
					else {
						if ( (LA(1)==TOK_GARBAGE) ) {
							zzmatch_wsig(TOK_GARBAGE, _handler);							
							if ( !guessing ) {
							 _t21 = (ANTLRTokenPtr)LT(1);
}
 labase++;
							if ( !guessing ) {
							
							_ast21 = new AST(_t21);
							_ast21->subchild(_root, &_sibling, &_tail);
							}
							
							if ( !guessing ) {
														lv5 = _t21;
							lv5_ast = _ast21;
							}
							
							if ( !guessing ) {
							lv = lv5_ast;
							lv->setSegLength(strlen(lv->getAsciiText()));
							AL_PARSE_ERR1( lv, AL_GETMSG(ERR, 300, 1), lv->getVcharText() )
							}
 consume();
						}
						else {
							if ( (
LA(1)==TOK_BAD_ID) ) {
								zzmatch_wsig(TOK_BAD_ID, _handler);								
								if ( !guessing ) {
								 _t21 = (ANTLRTokenPtr)LT(1);
}
 labase++;
								if ( !guessing ) {
								
								_ast21 = new AST(_t21);
								_ast21->subchild(_root, &_sibling, &_tail);
								}
								
								if ( !guessing ) {
																lv6 = _t21;
								lv6_ast = _ast21;
								}
								
								if ( !guessing ) {
								lv = lv6_ast;
								lv->setSegLength(strlen(lv->getAsciiText()));
								AL_PARSE_ERR1( lv, AL_GETMSG(ERR, 300, 1), lv->getVcharText() )
								}
 consume();
							}
							else {
								if ( (LA(1)==TOK_BAD_NAME) ) {
									zzmatch_wsig(TOK_BAD_NAME, _handler);									
									if ( !guessing ) {
									 _t21 = (ANTLRTokenPtr)LT(1);
}
 labase++;
									if ( !guessing ) {
									
									_ast21 = new AST(_t21);
									_ast21->subchild(_root, &_sibling, &_tail);
									}
									
									if ( !guessing ) {
																		lv7 = _t21;
									lv7_ast = _ast21;
									}
									
									if ( !guessing ) {
									lv = lv7_ast;
									lv->setSegLength(strlen(lv->getAsciiText()));
									AL_PARSE_ERR1( lv, AL_GETMSG(ERR, 300, 1), lv->getVcharText() )
									}
 consume();
								}
								else {
									if ( guessing ) goto fail;
									if (_sva) _signal=NoViableAlt;
									else _signal=NoSemViableAlt;
									goto _handler;  /* MR7 */
								}
							}
						}
					}
				}
			}
		}
	}
	if ( !guessing ) {
	lv->setType(TOK_LOCAL_VAR);
	}
	return;
fail:
	if ( guessing ) zzGUESS_FAIL;
	syn(zzBadTok, "local variable", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd10, 0x20);
_handler:
	zzdflthandlers(_signal,_retsignal);
	return;
}

void
P::function_name(ASTBase **_root,int *_retsignal)
{
	zzRULE;
	int _sva=1;
	ASTBase *_ast = NULL, *_sibling = NULL, *_tail = NULL;
	AST *_ast11=NULL;
	ANTLRTokenPtr fn=NULL;
	AST *fn_ast=NULL;
	int _signal=NoSignal;
	*_retsignal = NoSignal;
	_ast = NULL;
	general_name(&_ast,&_signal); if (_signal) goto _handler;
	if (!guessing) {    /* MR10 */
		if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
		_ast11 = (AST *)_ast;
		ASTBase::link(_root, &_sibling, &_tail);
	};    /* MR10 */
	fn_ast = _ast11;
	if ( !guessing ) {
	fn_ast->setType(TOK_FUNCTION_NAME);
	ttr->add( fn_ast );
	}
	return;
fail:
	if ( guessing ) zzGUESS_FAIL;
	syn(zzBadTok, "function name", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd10, 0x40);
_handler:
	zzdflthandlers(_signal,_retsignal);
	return;
}

void
P::svc_function_name(ASTBase **_root,int *_retsignal)
{
	zzRULE;
	int _sva=1;
	ASTBase *_ast = NULL, *_sibling = NULL, *_tail = NULL;
	AST *_ast11=NULL;
	ANTLRTokenPtr fn=NULL;
	AST *fn_ast=NULL;
	int _signal=NoSignal;
	*_retsignal = NoSignal;
	_ast = NULL;
	svc_general_name(&_ast,&_signal); if (_signal) goto _handler;
	if (!guessing) {    /* MR10 */
		if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
		_ast11 = (AST *)_ast;
		ASTBase::link(_root, &_sibling, &_tail);
	};    /* MR10 */
	fn_ast = _ast11;
	if ( !guessing ) {
	fn_ast->setType(TOK_FUNCTION_NAME);
	ttr->add( fn_ast );
	}
	return;
fail:
	if ( guessing ) zzGUESS_FAIL;
	syn(zzBadTok, "service function name", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd10, 0x80);
_handler:
	zzdflthandlers(_signal,_retsignal);
	return;
}

void
P::obj_or_ee_keyletters(ASTBase **_root,int *_retsignal)
{
	zzRULE;
	int _sva=1;
	ASTBase *_ast = NULL, *_sibling = NULL, *_tail = NULL;
	AST *_ast11=NULL;
	int _signal=NoSignal;
	*_retsignal = NoSignal;
	_ast = NULL;
	keyletters(&_ast,&_signal); if (_signal) goto _handler;
	if (!guessing) {    /* MR10 */
		if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
		_ast11 = (AST *)_ast;
		ASTBase::link(_root, &_sibling, &_tail);
	};    /* MR10 */
	return;
fail:
	if ( guessing ) zzGUESS_FAIL;
	syn(zzBadTok, "object or external entity keyletters", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd11, 0x1);
_handler:
	zzdflthandlers(_signal,_retsignal);
	return;
}

void
P::object_keyletters(ASTBase **_root,int *_retsignal)
{
	zzRULE;
	int _sva=1;
	ASTBase *_ast = NULL, *_sibling = NULL, *_tail = NULL;
	AST *_ast11=NULL;
	ANTLRTokenPtr kl=NULL;
	AST *kl_ast=NULL;
	int _signal=NoSignal;
	*_retsignal = NoSignal;
	_ast = NULL;
	keyletters(&_ast,&_signal); if (_signal) goto _handler;
	if (!guessing) {    /* MR10 */
		if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
		_ast11 = (AST *)_ast;
		ASTBase::link(_root, &_sibling, &_tail);
	};    /* MR10 */
	kl_ast = _ast11;
	if ( !guessing ) {
	kl_ast->setType(TOK_KL_OBJECT);
	pck->validate_obj_kl( kl_ast );
	// This generates errors "more than one object..." and "Object with
	//  keyletters $s does not exist".  All other object kl errors
	//  should be removed from p_msglst.hh
	}
	return;
fail:
	if ( guessing ) zzGUESS_FAIL;
	syn(zzBadTok, "object keyletters", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd11, 0x2);
_handler:
	zzdflthandlers(_signal,_retsignal);
	return;
}

void
P::phrase(ASTBase **_root,int *_retsignal)
{
	zzRULE;
	int _sva=1;
	ASTBase *_ast = NULL, *_sibling = NULL, *_tail = NULL;
;
	ANTLRTokenPtr s1=NULL, s2=NULL, s3=NULL;
	AST *s1_ast=NULL, *s2_ast=NULL, *s3_ast=NULL;
	int _signal=NoSignal;
	*_retsignal = NoSignal;
	AST *s_ast = NULL;
	{
		ANTLRTokenPtr _t21=NULL;
		AST *_ast21=NULL;
		if ( (LA(1)==TOK_PHRASE)
 ) {
			zzmatch_wsig(TOK_PHRASE, _handler);			
			if ( !guessing ) {
			 _t21 = (ANTLRTokenPtr)LT(1);
}
 labase++;
			if ( !guessing ) {
			
			_ast21 = new AST(_t21);
			_ast21->subchild(_root, &_sibling, &_tail);
			}
			
			if ( !guessing ) {
						s1 = _t21;
			s1_ast = _ast21;
			}
			
			if ( !guessing ) {
			s_ast = s1_ast;
			s1_ast->setSegLength(strlen(s1_ast->getAsciiText()) + 2);  // adjust for ticks
			}
 consume();
		}
		else {
			if ( (LA(1)==TOK_BADPHRASE_NL) ) {
				zzmatch_wsig(TOK_BADPHRASE_NL, _handler);				
				if ( !guessing ) {
				 _t21 = (ANTLRTokenPtr)LT(1);
}
 labase++;
				if ( !guessing ) {
				
				_ast21 = new AST(_t21);
				_ast21->subchild(_root, &_sibling, &_tail);
				}
				
				if ( !guessing ) {
								s2 = _t21;
				s2_ast = _ast21;
				}
				
				if ( !guessing ) {
				s_ast = s2_ast;
				s2_ast->setSegLength(strlen(s2_ast->getAsciiText()) + 1);  // adjust for single tick
				s2_ast->setLine( s2_ast->getLine() - 1 );  // correct line number
				AL_PARSE_ERR0( s2_ast, AL_GETMSG(ERR,315,0) )
				}
 consume();
			}
			else {
				if ( (LA(1)==TOK_BADPHRASE_EOF) ) {
					zzmatch_wsig(TOK_BADPHRASE_EOF, _handler);					
					if ( !guessing ) {
					 _t21 = (ANTLRTokenPtr)LT(1);
}
 labase++;
					if ( !guessing ) {
					
					_ast21 = new AST(_t21);
					_ast21->subchild(_root, &_sibling, &_tail);
					}
					
					if ( !guessing ) {
										s3 = _t21;
					s3_ast = _ast21;
					}
					
					if ( !guessing ) {
					s_ast = s3_ast;
					s3_ast->setSegLength(strlen(s3_ast->getAsciiText()) + 1);  // adjust for single tick
					AL_PARSE_ERR0( s3_ast, AL_GETMSG(ERR,315,0) )
					}
 consume();
				}
				else {
					if ( guessing ) goto fail;
					if (_sva) _signal=NoViableAlt;
					else _signal=NoSemViableAlt;
					goto _handler;  /* MR7 */
				}
			}
		}
	}
	if ( !guessing ) {
	s_ast->setType(TOK_PHRASE);
	}
	return;
fail:
	if ( guessing ) zzGUESS_FAIL;
	syn(zzBadTok, "phrase", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd11, 0x4);
_handler:
	zzdflthandlers(_signal,_retsignal);
	return;
}

void
P::relationship(ASTBase **_root,int *_retsignal)
{
	zzRULE;
	int _sva=1;
	ASTBase *_ast = NULL, *_sibling = NULL, *_tail = NULL;
	ANTLRTokenPtr _t11=NULL;
	AST *_ast11=NULL;
	ANTLRTokenPtr rn=NULL;
	AST *rn_ast=NULL;
	int _signal=NoSignal;
	*_retsignal = NoSignal;
	zzmatch_wsig(TOK_RELID, _handler);	
	if ( !guessing ) {
	 _t11 = (ANTLRTokenPtr)LT(1);
}
 labase++;
	if ( !guessing ) {
	
	_ast11 = new AST(_t11);
	_ast11->subchild(_root, &_sibling, &_tail);
	}
	
	if ( !guessing ) {
		rn = _t11;
	rn_ast = _ast11;
	}
	
	if ( !guessing ) {
	ttr->add( rn_ast );
	rn_ast->setSegLength(strlen(rn_ast->getAsciiText()));
	}
 consume();
	return;
fail:
	if ( guessing ) zzGUESS_FAIL;
	syn(zzBadTok, "relationship id", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd11, 0x8);
_handler:
	zzdflthandlers(_signal,_retsignal);
	return;
}

void
P::supp_data_item(ASTBase **_root,int *_retsignal)
{
	zzRULE;
	int _sva=1;
	ASTBase *_ast = NULL, *_sibling = NULL, *_tail = NULL;
	AST *_ast11=NULL;
	ANTLRTokenPtr nm=NULL;
	AST *nm_ast=NULL;
	int _signal=NoSignal;
	*_retsignal = NoSignal;
	_ast = NULL;
	data_item_name(&_ast,&_signal); if (_signal) goto _handler;
	if (!guessing) {    /* MR10 */
		if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
		_ast11 = (AST *)_ast;
		ASTBase::link(_root, &_sibling, &_tail);
	};    /* MR10 */
	nm_ast = _ast11;
	if ( !guessing ) {
	nm_ast->setType(TOK_SUPP_DATA_NAME);
	ttr->add( nm_ast );
	}
	return;
fail:
	if ( guessing ) zzGUESS_FAIL;
	syn(zzBadTok, "event supplemental data name", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd11, 0x10);
_handler:
	zzdflthandlers(_signal,_retsignal);
	return;
}

 t_core_data_type  
P::synch_svc_function(ASTBase **_root,int *_retsignal)
{
	 t_core_data_type  	 _retv;
	zzRULE;
	int _sva=1;
	ASTBase *_ast = NULL, *_sibling = NULL, *_tail = NULL;
	AST *_ast11=NULL;
	ANTLRTokenPtr nm=NULL;
	AST *nm_ast=NULL;
	int _signal=NoSignal;
	PURIFY(_retv,sizeof( t_core_data_type  	))
	*_retsignal = NoSignal;
	_ast = NULL;
	svc_function_name(&_ast,&_signal); if (_signal) goto _handler;
	if (!guessing) {    /* MR10 */
		if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
		_ast11 = (AST *)_ast;
		ASTBase::link(_root, &_sibling, &_tail);
	};    /* MR10 */
	nm_ast = _ast11;
	if ( !guessing ) {
	pck->validate_synch_svc( nm_ast );
	_retv = pck->get_synch_svc_return_type( nm_ast );
	}
	return _retv;
fail:
	if ( guessing ) zzGUESS_FAIL;
	syn(zzBadTok, "synchronous service function", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd11, 0x20);
	return _retv;
_handler:
	zzdflthandlers(_signal,_retsignal);
	return _retv;
}

 t_core_data_type  
P::transformer_function(ASTBase **_root,int *_retsignal, AST *obj_kl_or_inst_ref_var, bool isInstanceBased )
{
	 t_core_data_type  	 _retv;
	zzRULE;
	int _sva=1;
	ASTBase *_ast = NULL, *_sibling = NULL, *_tail = NULL;
	AST *_ast11=NULL;
	ANTLRTokenPtr nm=NULL;
	AST *nm_ast=NULL;
	int _signal=NoSignal;
	PURIFY(_retv,sizeof( t_core_data_type  	))
	*_retsignal = NoSignal;
	_ast = NULL;
	function_name(&_ast,&_signal); if (_signal) goto _handler;
	if (!guessing) {    /* MR10 */
		if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
		_ast11 = (AST *)_ast;
		ASTBase::link(_root, &_sibling, &_tail);
	};    /* MR10 */
	nm_ast = _ast11;
	if ( !guessing ) {
	pck->validate_transformer( nm_ast,  obj_kl_or_inst_ref_var,
	isInstanceBased );
	_retv = pck->get_transformer_return_type( nm_ast );
	}
	return _retv;
fail:
	if ( guessing ) zzGUESS_FAIL;
	syn(zzBadTok, "transformer function", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd11, 0x40);
	return _retv;
_handler:
	zzdflthandlers(_signal,_retsignal);
	return _retv;
}

 t_core_data_type  
P::expr(ASTBase **_root,int *_retsignal)
{
	 t_core_data_type  	 _retv;
	zzRULE;
	int _sva=1;
	ASTBase *_ast = NULL, *_sibling = NULL, *_tail = NULL;
	AST *_ast11=NULL;
	ANTLRTokenPtr e=NULL;
	AST *e_ast=NULL;
	int _signal=NoSignal;
	PURIFY(_retv,sizeof( t_core_data_type  	))
	*_retsignal = NoSignal;
	AST *c_ast;
	_ast = NULL;
	if ( !guessing ) {
		 _retv  = sub_expr(&_ast,&_signal); if (_signal) goto _handler;
		_ast11 = (AST *)_ast;
		e_ast = _ast11;
	} else {
		sub_expr(&_ast,&_signal);
	}
	if ( !guessing ) {
	c_ast = (new AST(TOK_EXPRESSION, e_ast));  // sets datatype and offset
	c_ast->setSegLength(e_ast->getSegLength());
	c_ast->setObjPtr(e_ast->getObjPtr());
	c_ast->setReadOnly(e_ast->isReadOnly());
	(*_root) = ASTBase::tmake( c_ast, e_ast , NULL);
	}
	return _retv;
fail:
	if ( guessing ) zzGUESS_FAIL;
	syn(zzBadTok, "expression", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd11, 0x80);
	return _retv;
_handler:
	zzdflthandlers(_signal,_retsignal);
	return _retv;
}

 t_core_data_type  
P::sub_expr(ASTBase **_root,int *_retsignal)
{
	 t_core_data_type  	 _retv;
	zzRULE;
	int _sva=1;
	ASTBase *_ast = NULL, *_sibling = NULL, *_tail = NULL;
	AST *_ast11=NULL;
	ANTLRTokenPtr c1=NULL, o=NULL, c2=NULL;
	AST *c1_ast=NULL, *o_ast=NULL, *c2_ast=NULL;
	int _signal=NoSignal;
	PURIFY(_retv,sizeof( t_core_data_type  	))
	*_retsignal = NoSignal;
	t_core_data_type t1, t2;
	_ast = NULL;
	if ( !guessing ) {
		 t1  = conjunction(&_ast,&_signal); if (_signal) goto _handler;
		if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
		_ast11 = (AST *)_ast;
		ASTBase::link(_root, &_sibling, &_tail);
		c1_ast = _ast11;
	} else {
		conjunction(&_ast,&_signal);
	}
	if ( !guessing ) {
	_retv = t1;
	}
	{
		ANTLRTokenPtr _t21=NULL;
		AST *_ast21=NULL,*_ast22=NULL;
		while ( (
LA(1)==TOK_OR) ) {
			zzmatch_wsig(TOK_OR, _handler);			
			if ( !guessing ) {
			 _t21 = (ANTLRTokenPtr)LT(1);
}
 labase++;
			if ( !guessing ) {
			
			_ast21 = new AST(_t21);
			_ast21->subroot(_root, &_sibling, &_tail);
			}
			
			if ( !guessing ) {
						o = _t21;
			o_ast = _ast21;
			}
			 consume();
			_ast = NULL;
			if ( !guessing ) {
				 t2  = conjunction(&_ast,&_signal); if (_signal) goto _handler;
				if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
				_ast22 = (AST *)_ast;
				ASTBase::link(_root, &_sibling, &_tail);
				c2_ast = _ast22;
			} else {
				conjunction(&_ast,&_signal);
			}
			if ( !guessing ) {
			_retv = BOOLEAN_DATATYPE;
			o_ast->setDatatype(_retv);
			o_ast->setObjPtr(c2_ast->getObjPtr());
			o_ast->setOffset(c1_ast->getOffset());
			o_ast->setSegLength(c2_ast->getOffset() -
			c1_ast->getOffset() +
			c2_ast->getSegLength());
			if ( t1 != _retv ) AL_PARSE_ERR0( c1_ast, AL_GETMSG(ERR,317,0) )
			if ( t2 != _retv ) AL_PARSE_ERR0( c2_ast, AL_GETMSG(ERR,317,0) )
			}
		}
	}
	return _retv;
fail:
	if ( guessing ) zzGUESS_FAIL;
	syn(zzBadTok, "sub_expression", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd12, 0x1);
	return _retv;
_handler:
	zzdflthandlers(_signal,_retsignal);
	return _retv;
}

 t_core_data_type  
P::conjunction(ASTBase **_root,int *_retsignal)
{
	 t_core_data_type  	 _retv;
	zzRULE;
	int _sva=1;
	ASTBase *_ast = NULL, *_sibling = NULL, *_tail = NULL;
	AST *_ast11=NULL;
	ANTLRTokenPtr e1=NULL, a=NULL, e2=NULL;
	AST *e1_ast=NULL, *a_ast=NULL, *e2_ast=NULL;
	int _signal=NoSignal;
	PURIFY(_retv,sizeof( t_core_data_type  	))
	*_retsignal = NoSignal;
	t_core_data_type t1, t2;
	_ast = NULL;
	if ( !guessing ) {
		 t1  = relational_expr(&_ast,&_signal); if (_signal) goto _handler;
		if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
		_ast11 = (AST *)_ast;
		ASTBase::link(_root, &_sibling, &_tail);
		e1_ast = _ast11;
	} else {
		relational_expr(&_ast,&_signal);
	}
	if ( !guessing ) {
	_retv = t1;
	}
	{
		ANTLRTokenPtr _t21=NULL;
		AST *_ast21=NULL,*_ast22=NULL;
		while ( (LA(1)==TOK_AND) ) {
			zzmatch_wsig(TOK_AND, _handler);			
			if ( !guessing ) {
			 _t21 = (ANTLRTokenPtr)LT(1);
}
 labase++;
			if ( !guessing ) {
			
			_ast21 = new AST(_t21);
			_ast21->subroot(_root, &_sibling, &_tail);
			}
			
			if ( !guessing ) {
						a = _t21;
			a_ast = _ast21;
			}
			 consume();
			_ast = NULL;
			if ( !guessing ) {
				 t2  = relational_expr(&_ast,&_signal); if (_signal) goto _handler;
				if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
				_ast22 = (AST *)_ast;
				ASTBase::link(_root, &_sibling, &_tail);
				e2_ast = _ast22;
			} else {
				relational_expr(&_ast,&_signal);
			}
			if ( !guessing ) {
			_retv = BOOLEAN_DATATYPE;
			a_ast->setDatatype(_retv);
			a_ast->setObjPtr(e2_ast->getObjPtr());
			a_ast->setOffset(e1_ast->getOffset());
			a_ast->setSegLength(e2_ast->getOffset() -
			e1_ast->getOffset() +
			e2_ast->getSegLength());
			if ( t1 != _retv ) AL_PARSE_ERR0( e1_ast, AL_GETMSG(ERR,317,0) )
			if ( t2 != _retv ) AL_PARSE_ERR0( e2_ast, AL_GETMSG(ERR,317,0) )
			}
		}
	}
	return _retv;
fail:
	if ( guessing ) zzGUESS_FAIL;
	syn(zzBadTok, "expression", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd12, 0x2);
	return _retv;
_handler:
	zzdflthandlers(_signal,_retsignal);
	return _retv;
}

 t_core_data_type  
P::relational_expr(ASTBase **_root,int *_retsignal)
{
	 t_core_data_type  	 _retv;
	zzRULE;
	int _sva=1;
	ASTBase *_ast = NULL, *_sibling = NULL, *_tail = NULL;
	AST *_ast11=NULL;
	ANTLRTokenPtr a1=NULL, op=NULL, a2=NULL;
	AST *a1_ast=NULL, *op_ast=NULL, *a2_ast=NULL;
	int _signal=NoSignal;
	PURIFY(_retv,sizeof( t_core_data_type  	))
	*_retsignal = NoSignal;
	t_core_data_type t1, t2;
	bool mismatch = FALSE;
	_ast = NULL;
	if ( !guessing ) {
		 t1  = addition(&_ast,&_signal); if (_signal) goto _handler;
		if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
		_ast11 = (AST *)_ast;
		ASTBase::link(_root, &_sibling, &_tail);
		a1_ast = _ast11;
	} else {
		addition(&_ast,&_signal);
	}
	if ( !guessing ) {
	_retv = t1;
	}
	{
		ANTLRTokenPtr _t21=NULL;
		AST *_ast21=NULL,*_ast22=NULL;
		if ( (LA(1)==TOK_DOUBLEEQUAL || 
LA(1)==TOK_GE || LA(1)==TOK_GT || LA(1)==TOK_LE || LA(1)==TOK_LESSTHAN || LA(1)==TOK_NOTEQUAL)
 ) {
			zzsetmatch_wsig(TOK_COMPARISON_OPERATOR_set, _handler);			
			if ( !guessing ) {
			 _t21 = (ANTLRTokenPtr)LT(1);
}
 labase++;
			if ( !guessing ) {
			
			_ast21 = new AST(_t21);
			_ast21->subroot(_root, &_sibling, &_tail);
			}
			
			if ( !guessing ) {
						op = _t21;
			op_ast = _ast21;
			}
			 consume();
			_ast = NULL;
			if ( !guessing ) {
				 t2  = addition(&_ast,&_signal); if (_signal) goto _handler;
				if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
				_ast22 = (AST *)_ast;
				ASTBase::link(_root, &_sibling, &_tail);
				a2_ast = _ast22;
			} else {
				addition(&_ast,&_signal);
			}
			if ( !guessing ) {
			_retv = BOOLEAN_DATATYPE;
			op_ast->setDatatype(_retv);
			op_ast->setObjPtr(a2_ast->getObjPtr());
			op_ast->setOffset(a1_ast->getOffset());
			op_ast->setSegLength(a2_ast->getOffset() -
			a1_ast->getOffset() +
			a2_ast->getSegLength());
			if ( accum_datatype( a1_ast, a2_ast, t1, t2, mismatch ) )
			{
				AL_PARSE_ERR0( op_ast, AL_GETMSG(ERR,318,0) );
			}
			else if ( t1 == ENUMERATION_DATATYPE )
			{
				if ( enum_oper_check ( op_ast ) )
				{
					AL_PARSE_ERR0( op_ast, AL_GETMSG(ERR,294,0) );
				}
			}
			else if ( t1 == STRING_DATATYPE )
			{
				if ( a1_ast->getType() == TOK_STRING && a2_ast->getType() == TOK_STRING )
				{
					// fixup the AST's Offset
					op_ast->setOffset( op_ast->getOffset() - 1 );
				}
				else if ( a1_ast->getType() != TOK_STRING && a2_ast->getType() == TOK_STRING )
				{
				// fixup the AST's segLength
				op_ast->setSegLength( op_ast->getSegLength() - 1 );
			}
			else if ( a1_ast->getType() == TOK_STRING && a2_ast->getType() != TOK_STRING )
			{
				// fixup the AST's Offset
				op_ast->setOffset( op_ast->getOffset() - 1 );
				// fixup the AST's segLength
				op_ast->setSegLength( op_ast->getSegLength() + 1 );
			}
		}
			}
		}
	}
	return _retv;
fail:
	if ( guessing ) zzGUESS_FAIL;
	syn(zzBadTok, "expression", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd12, 0x4);
	return _retv;
_handler:
	zzdflthandlers(_signal,_retsignal);
	return _retv;
}

 t_core_data_type  
P::addition(ASTBase **_root,int *_retsignal)
{
	 t_core_data_type  	 _retv;
	zzRULE;
	int _sva=1;
	ASTBase *_ast = NULL, *_sibling = NULL, *_tail = NULL;
	AST *_ast11=NULL;
	ANTLRTokenPtr m1=NULL, op=NULL, m2=NULL;
	AST *m1_ast=NULL, *op_ast=NULL, *m2_ast=NULL;
	int _signal=NoSignal;
	PURIFY(_retv,sizeof( t_core_data_type  	))
	*_retsignal = NoSignal;
	t_core_data_type t1, t2;
	bool mismatch = FALSE;
	_ast = NULL;
	if ( !guessing ) {
		 t1  = multiplication(&_ast,&_signal); if (_signal) goto _handler;
		if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
		_ast11 = (AST *)_ast;
		ASTBase::link(_root, &_sibling, &_tail);
		m1_ast = _ast11;
	} else {
		multiplication(&_ast,&_signal);
	}
	if ( !guessing ) {
	_retv = t1;
	m1_ast->setDatatype(t1);
	}
	{
		ANTLRTokenPtr _t21=NULL;
		AST *_ast21=NULL,*_ast22=NULL;
		while ( (LA(1)==TOK_MINUS || LA(1)==TOK_PLUS) ) {
			zzsetmatch_wsig(TOK_PLUS_OR_MINUS_set, _handler);			
			if ( !guessing ) {
			 _t21 = (ANTLRTokenPtr)LT(1);
}
 labase++;
			if ( !guessing ) {
			
			_ast21 = new AST(_t21);
			_ast21->subroot(_root, &_sibling, &_tail);
			}
			
			if ( !guessing ) {
						op = _t21;
			op_ast = _ast21;
			}
			 consume();
			_ast = NULL;
			if ( !guessing ) {
				 t2  = multiplication(&_ast,&_signal); if (_signal) goto _handler;
				if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
				_ast22 = (AST *)_ast;
				ASTBase::link(_root, &_sibling, &_tail);
				m2_ast = _ast22;
			} else {
				multiplication(&_ast,&_signal);
			}
			if ( !guessing ) {
			// Set the offset and seglength to include both terms
			op_ast->setOffset(m1_ast->getOffset());
			op_ast->setSegLength(m2_ast->getOffset() -
			m1_ast->getOffset() +
			m2_ast->getSegLength());
			if ( ! mismatch )
			{
				if ( accum_datatype( m1_ast, m2_ast, t1, t2, mismatch ) )
				{
					AL_PARSE_ERR0( op_ast, AL_GETMSG(ERR,319,0) )
				}
				else
				{
					switch ( t1 )
					{
						case INTEGER_DATATYPE:
						case REAL_DATATYPE:
						break;
						case STRING_DATATYPE:
						if ( op_ast->getType() != TOK_PLUS )
						{
							mismatch = TRUE;
							AL_PARSE_ERR0( op_ast, AL_GETMSG(ERR,320,0) )
						}
						else
						{
							if ( m1_ast->getType() == TOK_STRING && m2_ast->getType() == TOK_STRING )
							{
								// fixup the AST's Offset
								op_ast->setOffset( op_ast->getOffset() - 1 );
							}
							else if ( m1_ast->getType() != TOK_STRING && m2_ast->getType() == TOK_STRING )
							{
							// fixup the AST's segLength
							op_ast->setSegLength( op_ast->getSegLength() - 1 );
						}
						else if ( m1_ast->getType() == TOK_STRING && m2_ast->getType() != TOK_STRING )
						{
							// fixup the AST's Offset
							op_ast->setOffset( op_ast->getOffset() - 1 );
							// fixup the AST's segLength
							op_ast->setSegLength( op_ast->getSegLength() + 1 );
						}
					}
					break;
					default:
					mismatch = TRUE;
					AL_PARSE_ERR0( op_ast, AL_GETMSG(ERR,319,0) )
				}
			}
		}                 
		_retv = t1;
		op_ast->setDatatype(_retv);
		op_ast->setObjPtr(m2_ast->getObjPtr());
			}
		}
	}
	return _retv;
fail:
	if ( guessing ) zzGUESS_FAIL;
	syn(zzBadTok, "expression", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd12, 0x8);
	return _retv;
_handler:
	zzdflthandlers(_signal,_retsignal);
	return _retv;
}

 t_core_data_type  
P::multiplication(ASTBase **_root,int *_retsignal)
{
	 t_core_data_type  	 _retv;
	zzRULE;
	int _sva=1;
	ASTBase *_ast = NULL, *_sibling = NULL, *_tail = NULL;
	AST *_ast11=NULL,*_ast12=NULL;
	ANTLRTokenPtr bn=NULL, e1=NULL, op=NULL, e2=NULL;
	AST *bn_ast=NULL, *e1_ast=NULL, *op_ast=NULL, *e2_ast=NULL;
	int _signal=NoSignal;
	PURIFY(_retv,sizeof( t_core_data_type  	))
	*_retsignal = NoSignal;
	zzGUESS_BLOCK
	t_core_data_type t1, t2;
	bool mismatch = FALSE;
	zzGUESS
	if ( !zzrv && (LA(1)==TOK_NOT) && 
(LA(2)==TOK_ACROSS || LA(2)==TOK_ANY || LA(2)==TOK_ASSIGNER || LA(2)==TOK_ASSIGN || 
LA(2)==TOK_BREAKTOKEN || LA(2)==TOK_BY || LA(2)==TOK_CLASS || LA(2)==TOK_CONTINUE || LA(2)==TOK_CONTROL || 
LA(2)==TOK_CREATE || LA(2)==TOK_CREATOR || LA(2)==TOK_DELETE || LA(2)==TOK_EACH || LA(2)==TOK_END || 
LA(2)==TOK_EVENT || LA(2)==TOK_FOR || LA(2)==TOK_FROM || LA(2)==TOK_GENERATE || LA(2)==TOK_IN || 
LA(2)==TOK_INSTANCES || LA(2)==TOK_INSTANCE || LA(2)==TOK_MANY || LA(2)==TOK_OBJECT || LA(2)==TOK_OF || 
LA(2)==TOK_ONE || LA(2)==TOK_RELATED || LA(2)==TOK_RELATE || LA(2)==TOK_SELECT || LA(2)==TOK_STOP || 
LA(2)==TOK_TO || LA(2)==TOK_WHERE || LA(2)==TOK_UNRELATE || LA(2)==TOK_USING || LA(2)==TOK_BRIDGE || 
LA(2)==TOK_CARDINALITY || LA(2)==TOK_EMPTY || LA(2)==TOK_FALSETOKEN || LA(2)==TOK_NOT || LA(2)==TOK_NOTEMPTY || 
LA(2)==TOK_TRANSFORM || LA(2)==TOK_TRUETOKEN || LA(2)==TOK_PARAM || LA(2)==TOK_RCVD_EVT || LA(2)==TOK_SELECTED || 
LA(2)==TOK_SELF || LA(2)==TOK_DOUBLECOLON || LA(2)==TOK_LPAREN || LA(2)==TOK_QMARK || LA(2)==TOK_QUOTE || 
LA(2)==TOK_FRACTION || LA(2)==TOK_GENERAL_NAME || LA(2)==TOK_GARBAGE || LA(2)==TOK_BAD_ID || LA(2)==TOK_BAD_NAME || 
LA(2)==TOK_ID || LA(2)==TOK_RELID || LA(2)==TOK_NUMBER) ) {
		{
			AST *_ast21=NULL;
			_ast = NULL;
			if ( !guessing ) {
				 _retv  = boolean_negation(&_ast,&_signal); if (_signal) goto _handler;
				if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
				_ast21 = (AST *)_ast;
				ASTBase::link(_root, &_sibling, &_tail);
			} else {
				boolean_negation(&_ast,&_signal);
			}
		}
		zzGUESS_DONE
		_ast = NULL;
		if ( !guessing ) {
			 _retv  = boolean_negation(&_ast,&_signal); if (_signal) goto _handler;
			if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
			_ast12 = (AST *)_ast;
			ASTBase::link(_root, &_sibling, &_tail);
			bn_ast = _ast12;
		} else {
			boolean_negation(&_ast,&_signal);
		}
	}
	else {
		if ( !zzrv ) zzGUESS_DONE;
		if ( (LA(1)==TOK_ACROSS || LA(1)==TOK_ANY || 
LA(1)==TOK_ASSIGNER || LA(1)==TOK_ASSIGN || LA(1)==TOK_BREAKTOKEN || LA(1)==TOK_BY || LA(1)==TOK_CLASS || 
LA(1)==TOK_CONTINUE || LA(1)==TOK_CONTROL || LA(1)==TOK_CREATE || LA(1)==TOK_CREATOR || LA(1)==TOK_DELETE || 
LA(1)==TOK_EACH || LA(1)==TOK_END || LA(1)==TOK_EVENT || LA(1)==TOK_FOR || LA(1)==TOK_FROM || 
LA(1)==TOK_GENERATE || LA(1)==TOK_IN || LA(1)==TOK_INSTANCES || LA(1)==TOK_INSTANCE || LA(1)==TOK_MANY || 
LA(1)==TOK_OBJECT || LA(1)==TOK_OF || LA(1)==TOK_ONE || LA(1)==TOK_RELATED || LA(1)==TOK_RELATE || 
LA(1)==TOK_SELECT || LA(1)==TOK_STOP || LA(1)==TOK_TO || LA(1)==TOK_WHERE || LA(1)==TOK_UNRELATE || 
LA(1)==TOK_USING || LA(1)==TOK_BRIDGE || LA(1)==TOK_CARDINALITY || LA(1)==TOK_EMPTY || LA(1)==TOK_FALSETOKEN || 
LA(1)==TOK_NOT || LA(1)==TOK_NOTEMPTY || LA(1)==TOK_TRANSFORM || LA(1)==TOK_TRUETOKEN || LA(1)==TOK_PARAM || 
LA(1)==TOK_RCVD_EVT || LA(1)==TOK_SELECTED || LA(1)==TOK_SELF || LA(1)==TOK_DOUBLECOLON || LA(1)==TOK_LPAREN || 
LA(1)==TOK_MINUS || LA(1)==TOK_PLUS || LA(1)==TOK_QMARK || LA(1)==TOK_QUOTE || LA(1)==TOK_FRACTION || 
LA(1)==TOK_GENERAL_NAME || LA(1)==TOK_GARBAGE || LA(1)==TOK_BAD_ID || LA(1)==TOK_BAD_NAME || LA(1)==TOK_ID || 
LA(1)==TOK_RELID || LA(1)==TOK_NUMBER) && (LA(2)==Eof || LA(2)==TOK_BADSTRING_EOF || 
LA(2)==TOK_STRING || LA(2)==TOK_BADSTRING_NL || LA(2)==TOK_ACROSS || LA(2)==TOK_ANY || LA(2)==TOK_ASSIGNER || 
LA(2)==TOK_ASSIGN || LA(2)==TOK_BREAKTOKEN || LA(2)==TOK_BY || LA(2)==TOK_CLASS || LA(2)==TOK_CONTINUE || 
LA(2)==TOK_CONTROL || LA(2)==TOK_CREATE || LA(2)==TOK_CREATOR || LA(2)==TOK_DELETE || LA(2)==TOK_EACH || 
LA(2)==TOK_END || LA(2)==TOK_EVENT || LA(2)==TOK_FOR || LA(2)==TOK_FROM || LA(2)==TOK_GENERATE || 
LA(2)==TOK_IN || LA(2)==TOK_INSTANCES || LA(2)==TOK_INSTANCE || LA(2)==TOK_MANY || LA(2)==TOK_OBJECT || 
LA(2)==TOK_OF || LA(2)==TOK_ONE || LA(2)==TOK_RELATED || LA(2)==TOK_RELATE || LA(2)==TOK_SELECT || 
LA(2)==TOK_STOP || LA(2)==TOK_TO || LA(2)==TOK_WHERE || LA(2)==TOK_UNRELATE || LA(2)==TOK_USING || 
LA(2)==TOK_BRIDGE || LA(2)==TOK_CARDINALITY || LA(2)==TOK_EMPTY || LA(2)==TOK_FALSETOKEN || LA(2)==TOK_NOT || 
LA(2)==TOK_NOTEMPTY || LA(2)==TOK_TRANSFORM || LA(2)==TOK_TRUETOKEN || LA(2)==TOK_PARAM || LA(2)==TOK_RCVD_EVT || 
LA(2)==TOK_SELECTED || LA(2)==TOK_SELF || LA(2)==TOK_AND || LA(2)==TOK_ELIF || LA(2)==TOK_ELSE || 
LA(2)==TOK_IF || LA(2)==TOK_OR || LA(2)==TOK_RETURN || LA(2)==TOK_WHILE || LA(2)==TOK_DEBUG || 
LA(2)==TOK_COMMA || LA(2)==TOK_DIV || LA(2)==TOK_DOT || LA(2)==TOK_DOUBLECOLON || LA(2)==TOK_DOUBLEEQUAL || 
LA(2)==TOK_GE || LA(2)==TOK_GT || LA(2)==TOK_LE || LA(2)==TOK_LESSTHAN || LA(2)==TOK_LPAREN || 
LA(2)==TOK_MINUS || LA(2)==TOK_MOD || LA(2)==TOK_NOTEQUAL || LA(2)==TOK_PLUS || LA(2)==TOK_RPAREN || 
LA(2)==TOK_SEMI || LA(2)==TOK_TIMES || LA(2)==TOK_QMARK || LA(2)==TOK_QUOTE || LA(2)==TOK_FRACTION || 
LA(2)==TOK_GENERAL_NAME || LA(2)==TOK_GARBAGE || LA(2)==TOK_BAD_ID || LA(2)==TOK_BAD_NAME || LA(2)==TOK_ID || 
LA(2)==TOK_RELID || LA(2)==TOK_NUMBER) ) {
			_ast = NULL;
			if ( !guessing ) {
				 t1  = sign_expr(&_ast,&_signal); if (_signal) goto _handler;
				if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
				_ast11 = (AST *)_ast;
				ASTBase::link(_root, &_sibling, &_tail);
				e1_ast = _ast11;
			} else {
				sign_expr(&_ast,&_signal);
			}
			if ( !guessing ) {
			_retv = t1;
			}
			{
				ANTLRTokenPtr _t21=NULL;
				AST *_ast21=NULL,*_ast22=NULL;
				while ( (LA(1)==TOK_DIV || LA(1)==TOK_MOD || LA(1)==TOK_TIMES)
 ) {
					zzsetmatch_wsig(TOK_MULT_OP_set, _handler);					
					if ( !guessing ) {
					 _t21 = (ANTLRTokenPtr)LT(1);
}
 labase++;
					if ( !guessing ) {
					
					_ast21 = new AST(_t21);
					_ast21->subroot(_root, &_sibling, &_tail);
					}
					
					if ( !guessing ) {
										op = _t21;
					op_ast = _ast21;
					}
					 consume();
					_ast = NULL;
					if ( !guessing ) {
						 t2  = sign_expr(&_ast,&_signal); if (_signal) goto _handler;
						if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
						_ast22 = (AST *)_ast;
						ASTBase::link(_root, &_sibling, &_tail);
						e2_ast = _ast22;
					} else {
						sign_expr(&_ast,&_signal);
					}
					if ( !guessing ) {
					// Set the offset and seglength to include both terms
					op_ast->setOffset(e1_ast->getOffset());
					op_ast->setSegLength(e2_ast->getOffset() -
					e1_ast->getOffset() +
					e2_ast->getSegLength());
					if ( ! mismatch )
					{
						if ( accum_datatype( e1_ast, e2_ast, t1, t2, mismatch ) )
						{
							AL_PARSE_ERR0( op_ast, AL_GETMSG(ERR,319,0) )
						}
						else
						{
							switch ( t1 )
							{
								case INTEGER_DATATYPE:
								case REAL_DATATYPE:
								break;
								default:
								AL_PARSE_ERR0( op_ast, AL_GETMSG(ERR,319,0) )
							}
						}
					}
					_retv = t1;
					op_ast->setDatatype(_retv);
					}
				}
			}
		}
		else {
			if ( guessing ) goto fail;
			if (_sva) _signal=NoViableAlt;
			else _signal=NoSemViableAlt;
			goto _handler;  /* MR7 */
		}
	}
	return _retv;
fail:
	if ( guessing ) zzGUESS_FAIL;
	syn(zzBadTok, "expression", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd12, 0x10);
	return _retv;
_handler:
	zzdflthandlers(_signal,_retsignal);
	return _retv;
}

 t_core_data_type  
P::sign_expr(ASTBase **_root,int *_retsignal)
{
	 t_core_data_type  	 _retv;
	zzRULE;
	int _sva=1;
	ASTBase *_ast = NULL, *_sibling = NULL, *_tail = NULL;
	AST *_ast12=NULL;
	ANTLRTokenPtr op1=NULL, op2=NULL, t=NULL;
	AST *op1_ast=NULL, *op2_ast=NULL, *t_ast=NULL;
	int _signal=NoSignal;
	PURIFY(_retv,sizeof( t_core_data_type  	))
	*_retsignal = NoSignal;
	t_core_data_type t1, t2;
	bool mismatch = FALSE;
	AST *op = NULL;
	{
		ANTLRTokenPtr _t21=NULL;
		AST *_ast21=NULL;
		if ( (LA(1)==TOK_PLUS) ) {
			zzmatch_wsig(TOK_PLUS, _handler);			
			if ( !guessing ) {
			 _t21 = (ANTLRTokenPtr)LT(1);
}
 labase++;
			
			if ( !guessing ) {
						op1 = _t21;
			}
			
			if ( !guessing ) {
			op = (new AST( op1, TOK_UNARY_PLUS));
			}
 consume();
		}
		else {
			if ( (LA(1)==TOK_MINUS) ) {
				zzmatch_wsig(TOK_MINUS, _handler);				
				if ( !guessing ) {
				 _t21 = (ANTLRTokenPtr)LT(1);
}
 labase++;
				
				if ( !guessing ) {
								op2 = _t21;
				}
				
				if ( !guessing ) {
				op = (new AST( op2, TOK_UNARY_MINUS));
				}
 consume();
			}
		}
	}
	_ast = NULL;
	if ( !guessing ) {
		 t1  = term(&_ast,&_signal); if (_signal) goto _handler;
		_ast12 = (AST *)_ast;
		t_ast = _ast12;
	} else {
		term(&_ast,&_signal);
	}
	if ( !guessing ) {
	_retv = t1;
	if ( op )
	{ // Set the seglength to include both term and operator
		op->setSegLength(t_ast->getOffset() +
		t_ast->getSegLength() -
		op->getOffset());
		t2 = INTEGER_DATATYPE;
		if ( accum_datatype( t_ast, t_ast, t2, t1, mismatch ) )
		{
			AL_PARSE_ERR0( op, AL_GETMSG(ERR,312,0) )
		}
		_retv = t2;                    // return accum datatype
		op->setDatatype(_retv);
		op->setObjPtr(t_ast->getObjPtr());
		if ( ( t_ast->getOffset() - op->getOffset() ) == 1 )
		{
			switch (t_ast->getType())
			{
				case TOK_NUMBER:
				case TOK_FRACTION:
				{
					// combine sign with number
					size_t l_num = strlen(t_ast->getAsciiText());
					vchar *s = new vchar[l_num + 2];
					vchar *endpt;
					vcharCopyBounded(op->getVcharText(), s, 1);
					endpt = vcharCopyBounded(t_ast->getVcharText(), s+1, l_num+1);
					*endpt = '\0';
					op->setVcharText( s );
					op->setSegLength(l_num + 1);
					op->setType(t_ast->getType());
					(*_root) = op;
					delete t_ast;
					delete [] s;
				}
				break;
				default:
				(*_root) = ASTBase::tmake(op, t_ast, NULL);
				break;
			}
		}
		else  // separation between sign and number
		(*_root) = ASTBase::tmake(op, t_ast, NULL);
	}
	else
	(*_root) = t_ast;
	}
	return _retv;
fail:
	if ( guessing ) zzGUESS_FAIL;
	syn(zzBadTok, "expression", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd12, 0x20);
	return _retv;
_handler:
	zzdflthandlers(_signal,_retsignal);
	return _retv;
}

 t_core_data_type  
P::boolean_negation(ASTBase **_root,int *_retsignal)
{
	 t_core_data_type  	 _retv;
	zzRULE;
	int _sva=1;
	ASTBase *_ast = NULL, *_sibling = NULL, *_tail = NULL;
	ANTLRTokenPtr _t11=NULL;
	AST *_ast11=NULL,*_ast12=NULL;
	ANTLRTokenPtr op=NULL, t=NULL;
	AST *op_ast=NULL, *t_ast=NULL;
	int _signal=NoSignal;
	PURIFY(_retv,sizeof( t_core_data_type  	))
	*_retsignal = NoSignal;
	t_core_data_type t1;
	zzmatch_wsig(TOK_NOT, _handler);	
	if ( !guessing ) {
	 _t11 = (ANTLRTokenPtr)LT(1);
}
 labase++;
	if ( !guessing ) {
	
	_ast11 = new AST(_t11);
	_ast11->subroot(_root, &_sibling, &_tail);
	}
	
	if ( !guessing ) {
		op = _t11;
	op_ast = _ast11;
	}
	 consume();
	_ast = NULL;
	if ( !guessing ) {
		 t1  = term(&_ast,&_signal); if (_signal) goto _handler;
		if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
		_ast12 = (AST *)_ast;
		ASTBase::link(_root, &_sibling, &_tail);
		t_ast = _ast12;
	} else {
		term(&_ast,&_signal);
	}
	if ( !guessing ) {
	// Set the seglength to include both terms
	op_ast->setSegLength(t_ast->getOffset() -
	op_ast->getOffset() +
	t_ast->getSegLength());
	if ( t1 != BOOLEAN_DATATYPE )
	{
		AL_PARSE_ERR0( op_ast, AL_GETMSG(ERR,312,0) )
	}
	_retv = BOOLEAN_DATATYPE;
	op_ast->setDatatype(_retv);
	op_ast->setObjPtr(t_ast->getObjPtr());
	}
	return _retv;
fail:
	if ( guessing ) zzGUESS_FAIL;
	syn(zzBadTok, "expression", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd12, 0x40);
	return _retv;
_handler:
	zzdflthandlers(_signal,_retsignal);
	return _retv;
}

 t_core_data_type  
P::term(ASTBase **_root,int *_retsignal)
{
	 t_core_data_type  	 _retv;
	zzRULE;
	int _sva=1;
	ASTBase *_ast = NULL, *_sibling = NULL, *_tail = NULL;
	ANTLRTokenPtr _t11=NULL,_t13=NULL;
	AST *_ast11=NULL,*_ast12=NULL,*_ast13=NULL;
	ANTLRTokenPtr op1=NULL, op2=NULL, op3=NULL, idx=NULL, lp=NULL, ae=NULL, e=NULL, rp=NULL;
	AST *op1_ast=NULL, *op2_ast=NULL, *op3_ast=NULL, *idx_ast=NULL, *lp_ast=NULL, *ae_ast=NULL, *e_ast=NULL, *rp_ast=NULL;
	int _signal=NoSignal;
	PURIFY(_retv,sizeof( t_core_data_type  	))
	*_retsignal = NoSignal;
	t_core_data_type t1;
	Sym *s_ref;
	AST *op = NULL;
	AST *p_ast;
	if ( (
LA(1)==TOK_CARDINALITY || LA(1)==TOK_EMPTY || LA(1)==TOK_NOTEMPTY) && (LA(2)==TOK_ACROSS || 
LA(2)==TOK_ANY || LA(2)==TOK_ASSIGNER || LA(2)==TOK_ASSIGN || LA(2)==TOK_BREAKTOKEN || LA(2)==TOK_BY || 
LA(2)==TOK_CLASS || LA(2)==TOK_CONTINUE || LA(2)==TOK_CONTROL || LA(2)==TOK_CREATE || LA(2)==TOK_CREATOR || 
LA(2)==TOK_DELETE || LA(2)==TOK_EACH || LA(2)==TOK_END || LA(2)==TOK_EVENT || LA(2)==TOK_FOR || 
LA(2)==TOK_FROM || LA(2)==TOK_GENERATE || LA(2)==TOK_IN || LA(2)==TOK_INSTANCES || LA(2)==TOK_INSTANCE || 
LA(2)==TOK_MANY || LA(2)==TOK_OBJECT || LA(2)==TOK_OF || LA(2)==TOK_ONE || LA(2)==TOK_RELATED || 
LA(2)==TOK_RELATE || LA(2)==TOK_SELECT || LA(2)==TOK_STOP || LA(2)==TOK_TO || LA(2)==TOK_WHERE || 
LA(2)==TOK_UNRELATE || LA(2)==TOK_USING || LA(2)==TOK_SELECTED || LA(2)==TOK_SELF || LA(2)==TOK_GARBAGE || 
LA(2)==TOK_BAD_ID || LA(2)==TOK_BAD_NAME || LA(2)==TOK_ID || LA(2)==TOK_RELID) ) {
		{
			ANTLRTokenPtr _t21=NULL;
			AST *_ast21=NULL;
			if ( (LA(1)==TOK_CARDINALITY)
 ) {
				zzmatch_wsig(TOK_CARDINALITY, _handler);				
				if ( !guessing ) {
				 _t21 = (ANTLRTokenPtr)LT(1);
}
 labase++;
				if ( !guessing ) {
				
				_ast21 = new AST(_t21);
				_ast21->subroot(_root, &_sibling, &_tail);
				}
				
				if ( !guessing ) {
								op1 = _t21;
				op1_ast = _ast21;
				}
				
				if ( !guessing ) {
				_retv = INTEGER_DATATYPE;
				op = op1_ast;
				op->setDatatype(_retv);
				}
 consume();
			}
			else {
				if ( (LA(1)==TOK_EMPTY) ) {
					zzmatch_wsig(TOK_EMPTY, _handler);					
					if ( !guessing ) {
					 _t21 = (ANTLRTokenPtr)LT(1);
}
 labase++;
					if ( !guessing ) {
					
					_ast21 = new AST(_t21);
					_ast21->subroot(_root, &_sibling, &_tail);
					}
					
					if ( !guessing ) {
										op2 = _t21;
					op2_ast = _ast21;
					}
					
					if ( !guessing ) {
					_retv = BOOLEAN_DATATYPE;
					op = op2_ast;
					op->setDatatype(_retv);
					}
 consume();
				}
				else {
					if ( (LA(1)==TOK_NOTEMPTY) ) {
						zzmatch_wsig(TOK_NOTEMPTY, _handler);						
						if ( !guessing ) {
						 _t21 = (ANTLRTokenPtr)LT(1);
}
 labase++;
						if ( !guessing ) {
						
						_ast21 = new AST(_t21);
						_ast21->subroot(_root, &_sibling, &_tail);
						}
						
						if ( !guessing ) {
												op3 = _t21;
						op3_ast = _ast21;
						}
						
						if ( !guessing ) {
						_retv = BOOLEAN_DATATYPE;
						op = op3_ast;
						op->setDatatype(_retv);
						}
 consume();
					}
					else {
						if ( guessing ) goto fail;
						if (_sva) _signal=NoViableAlt;
						else _signal=NoSemViableAlt;
						goto _handler;  /* MR7 */
					}
				}
			}
		}
		_ast = NULL;
		local_variable(&_ast,&_signal, ASSIGN_RVAL ); if (_signal) goto _handler;
		if (!guessing) {    /* MR10 */
			if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
			_ast12 = (AST *)_ast;
			ASTBase::link(_root, &_sibling, &_tail);
		};    /* MR10 */
		idx_ast = _ast12;
		if ( !guessing ) {
		// Set the seglength to include both terms
		op->setSegLength(idx_ast->getOffset() -
		op->getOffset() +
		idx_ast->getSegLength());
		if ( st->is_var_this_type_defined( idx_ast->getVcharText(),
		OBJECT_INST_REF_DATATYPE,
		&s_ref ) )
		{
			idx_ast->setDatatype(OBJECT_INST_REF_DATATYPE);   // inst_ref variable
			idx_ast->setObjPtr( s_ref->objPtr );
		}
		else if ( st->is_var_this_type_defined( idx_ast->getVcharText(),
		OBJECT_INST_REF_SET_DATATYPE,
		&s_ref ) )
		{
			idx_ast->setDatatype(OBJECT_INST_REF_SET_DATATYPE);   // inst_ref_set
			idx_ast->setObjPtr( s_ref->objPtr );
		}
		else
		{
			idx_ast->setDatatype(UNKNOWN_DATATYPE);
			AL_PARSE_ERR1( idx_ast, AL_GETMSG(ERR, 044, 1), idx_ast->getVcharText() )
		}
		op->setObjPtr(idx_ast->getObjPtr());
		}
	}
	else {
		if ( (
LA(1)==TOK_ACROSS || LA(1)==TOK_ANY || LA(1)==TOK_ASSIGNER || LA(1)==TOK_ASSIGN || LA(1)==TOK_BREAKTOKEN || 
LA(1)==TOK_BY || LA(1)==TOK_CLASS || LA(1)==TOK_CONTINUE || LA(1)==TOK_CONTROL || LA(1)==TOK_CREATE || 
LA(1)==TOK_CREATOR || LA(1)==TOK_DELETE || LA(1)==TOK_EACH || LA(1)==TOK_END || LA(1)==TOK_EVENT || 
LA(1)==TOK_FOR || LA(1)==TOK_FROM || LA(1)==TOK_GENERATE || LA(1)==TOK_IN || LA(1)==TOK_INSTANCES || 
LA(1)==TOK_INSTANCE || LA(1)==TOK_MANY || LA(1)==TOK_OBJECT || LA(1)==TOK_OF || LA(1)==TOK_ONE || 
LA(1)==TOK_RELATED || LA(1)==TOK_RELATE || LA(1)==TOK_SELECT || LA(1)==TOK_STOP || LA(1)==TOK_TO || 
LA(1)==TOK_WHERE || LA(1)==TOK_UNRELATE || LA(1)==TOK_USING || LA(1)==TOK_BRIDGE || LA(1)==TOK_CARDINALITY || 
LA(1)==TOK_EMPTY || LA(1)==TOK_FALSETOKEN || LA(1)==TOK_NOT || LA(1)==TOK_NOTEMPTY || LA(1)==TOK_TRANSFORM || 
LA(1)==TOK_TRUETOKEN || LA(1)==TOK_PARAM || LA(1)==TOK_RCVD_EVT || LA(1)==TOK_SELECTED || LA(1)==TOK_SELF || 
LA(1)==TOK_DOUBLECOLON || LA(1)==TOK_QMARK || LA(1)==TOK_QUOTE || LA(1)==TOK_FRACTION || LA(1)==TOK_GENERAL_NAME || 
LA(1)==TOK_GARBAGE || LA(1)==TOK_BAD_ID || LA(1)==TOK_BAD_NAME || LA(1)==TOK_ID || LA(1)==TOK_RELID || 
LA(1)==TOK_NUMBER) && (LA(2)==Eof || LA(2)==TOK_BADSTRING_EOF || LA(2)==TOK_STRING || 
LA(2)==TOK_BADSTRING_NL || LA(2)==TOK_ACROSS || LA(2)==TOK_ANY || LA(2)==TOK_ASSIGNER || LA(2)==TOK_ASSIGN || 
LA(2)==TOK_BREAKTOKEN || LA(2)==TOK_BY || LA(2)==TOK_CLASS || LA(2)==TOK_CONTINUE || LA(2)==TOK_CONTROL || 
LA(2)==TOK_CREATE || LA(2)==TOK_CREATOR || LA(2)==TOK_DELETE || LA(2)==TOK_EACH || LA(2)==TOK_END || 
LA(2)==TOK_EVENT || LA(2)==TOK_FOR || LA(2)==TOK_FROM || LA(2)==TOK_GENERATE || LA(2)==TOK_IN || 
LA(2)==TOK_INSTANCES || LA(2)==TOK_INSTANCE || LA(2)==TOK_MANY || LA(2)==TOK_OBJECT || LA(2)==TOK_OF || 
LA(2)==TOK_ONE || LA(2)==TOK_RELATED || LA(2)==TOK_RELATE || LA(2)==TOK_SELECT || LA(2)==TOK_STOP || 
LA(2)==TOK_TO || LA(2)==TOK_WHERE || LA(2)==TOK_UNRELATE || LA(2)==TOK_USING || LA(2)==TOK_BRIDGE || 
LA(2)==TOK_CARDINALITY || LA(2)==TOK_EMPTY || LA(2)==TOK_FALSETOKEN || LA(2)==TOK_NOT || LA(2)==TOK_NOTEMPTY || 
LA(2)==TOK_TRANSFORM || LA(2)==TOK_TRUETOKEN || LA(2)==TOK_PARAM || LA(2)==TOK_RCVD_EVT || LA(2)==TOK_SELECTED || 
LA(2)==TOK_SELF || LA(2)==TOK_AND || LA(2)==TOK_ELIF || LA(2)==TOK_ELSE || LA(2)==TOK_IF || 
LA(2)==TOK_OR || LA(2)==TOK_RETURN || LA(2)==TOK_WHILE || LA(2)==TOK_DEBUG || LA(2)==TOK_COMMA || 
LA(2)==TOK_DIV || LA(2)==TOK_DOT || LA(2)==TOK_DOUBLECOLON || LA(2)==TOK_DOUBLEEQUAL || LA(2)==TOK_GE || 
LA(2)==TOK_GT || LA(2)==TOK_LE || LA(2)==TOK_LESSTHAN || LA(2)==TOK_MINUS || LA(2)==TOK_MOD || 
LA(2)==TOK_NOTEQUAL || LA(2)==TOK_PLUS || LA(2)==TOK_RPAREN || LA(2)==TOK_SEMI || LA(2)==TOK_TIMES || 
LA(2)==TOK_GENERAL_NAME || LA(2)==TOK_GARBAGE || LA(2)==TOK_BAD_ID || LA(2)==TOK_BAD_NAME || LA(2)==TOK_ID || 
LA(2)==TOK_RELID) ) {
			_ast = NULL;
			if ( !guessing ) {
				 _retv  = rval(&_ast,&_signal); if (_signal) goto _handler;
				if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
				_ast11 = (AST *)_ast;
				ASTBase::link(_root, &_sibling, &_tail);
			} else {
				rval(&_ast,&_signal);
			}
		}
		else {
			if ( (LA(1)==TOK_LPAREN) ) {
				zzmatch_wsig(TOK_LPAREN, _handler);				
				if ( !guessing ) {
				 _t11 = (ANTLRTokenPtr)LT(1);
}
 labase++;
				if ( !guessing ) {
				
				_ast11 = new AST(_t11);
				_ast11->subroot(_root, &_sibling, &_tail);
				}
				
				if ( !guessing ) {
								lp = _t11;
				lp_ast = _ast11;
				}
				 consume();
				{
					AST *_ast21=NULL,*_ast22=NULL;
					zzGUESS_BLOCK
					zzGUESS
					if ( !zzrv && (LA(1)==TOK_ACROSS || LA(1)==TOK_ANY || 
LA(1)==TOK_ASSIGNER || LA(1)==TOK_ASSIGN || LA(1)==TOK_BREAKTOKEN || LA(1)==TOK_BY || LA(1)==TOK_CLASS || 
LA(1)==TOK_CONTINUE || LA(1)==TOK_CONTROL || LA(1)==TOK_CREATE || LA(1)==TOK_CREATOR || LA(1)==TOK_DELETE || 
LA(1)==TOK_EACH || LA(1)==TOK_END || LA(1)==TOK_EVENT || LA(1)==TOK_FOR || LA(1)==TOK_FROM || 
LA(1)==TOK_GENERATE || LA(1)==TOK_IN || LA(1)==TOK_INSTANCES || LA(1)==TOK_INSTANCE || LA(1)==TOK_MANY || 
LA(1)==TOK_OBJECT || LA(1)==TOK_OF || LA(1)==TOK_ONE || LA(1)==TOK_RELATED || LA(1)==TOK_RELATE || 
LA(1)==TOK_SELECT || LA(1)==TOK_STOP || LA(1)==TOK_TO || LA(1)==TOK_WHERE || LA(1)==TOK_UNRELATE || 
LA(1)==TOK_USING || LA(1)==TOK_PARAM || LA(1)==TOK_RCVD_EVT || LA(1)==TOK_SELECTED || LA(1)==TOK_SELF || 
LA(1)==TOK_GARBAGE || LA(1)==TOK_BAD_ID || LA(1)==TOK_BAD_NAME || LA(1)==TOK_ID || LA(1)==TOK_RELID) && 
(LA(2)==TOK_DOT || LA(2)==TOK_EQUAL) ) {
						{
							AST *_ast31=NULL;
							_ast = NULL;
							if ( !guessing ) {
								 t1  = assignment_expr(&_ast,&_signal); if (_signal) goto _handler;
								if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
								_ast31 = (AST *)_ast;
								ASTBase::link(_root, &_sibling, &_tail);
							} else {
								assignment_expr(&_ast,&_signal);
							}
						}
						zzGUESS_DONE
						_ast = NULL;
						if ( !guessing ) {
							 t1  = assignment_expr(&_ast,&_signal); if (_signal) goto _handler;
							if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
							_ast22 = (AST *)_ast;
							ASTBase::link(_root, &_sibling, &_tail);
							ae_ast = _ast22;
						} else {
							assignment_expr(&_ast,&_signal);
						}
						if ( !guessing ) {
						AL_PARSE_ERR0( ae_ast, AL_GETMSG(ERR, 314, 0) )
						}
					}
					else {
						if ( !zzrv ) zzGUESS_DONE;
						if ( (LA(1)==TOK_ACROSS || LA(1)==TOK_ANY || 
LA(1)==TOK_ASSIGNER || LA(1)==TOK_ASSIGN || LA(1)==TOK_BREAKTOKEN || LA(1)==TOK_BY || LA(1)==TOK_CLASS || 
LA(1)==TOK_CONTINUE || LA(1)==TOK_CONTROL || LA(1)==TOK_CREATE || LA(1)==TOK_CREATOR || LA(1)==TOK_DELETE || 
LA(1)==TOK_EACH || LA(1)==TOK_END || LA(1)==TOK_EVENT || LA(1)==TOK_FOR || LA(1)==TOK_FROM || 
LA(1)==TOK_GENERATE || LA(1)==TOK_IN || LA(1)==TOK_INSTANCES || LA(1)==TOK_INSTANCE || LA(1)==TOK_MANY || 
LA(1)==TOK_OBJECT || LA(1)==TOK_OF || LA(1)==TOK_ONE || LA(1)==TOK_RELATED || LA(1)==TOK_RELATE || 
LA(1)==TOK_SELECT || LA(1)==TOK_STOP || LA(1)==TOK_TO || LA(1)==TOK_WHERE || LA(1)==TOK_UNRELATE || 
LA(1)==TOK_USING || LA(1)==TOK_BRIDGE || LA(1)==TOK_CARDINALITY || LA(1)==TOK_EMPTY || LA(1)==TOK_FALSETOKEN || 
LA(1)==TOK_NOT || LA(1)==TOK_NOTEMPTY || LA(1)==TOK_TRANSFORM || LA(1)==TOK_TRUETOKEN || LA(1)==TOK_PARAM || 
LA(1)==TOK_RCVD_EVT || LA(1)==TOK_SELECTED || LA(1)==TOK_SELF || LA(1)==TOK_DOUBLECOLON || LA(1)==TOK_LPAREN || 
LA(1)==TOK_MINUS || LA(1)==TOK_PLUS || LA(1)==TOK_QMARK || LA(1)==TOK_QUOTE || LA(1)==TOK_FRACTION || 
LA(1)==TOK_GENERAL_NAME || LA(1)==TOK_GARBAGE || LA(1)==TOK_BAD_ID || LA(1)==TOK_BAD_NAME || LA(1)==TOK_ID || 
LA(1)==TOK_RELID || LA(1)==TOK_NUMBER) && (LA(2)==TOK_BADSTRING_EOF || LA(2)==TOK_STRING || 
LA(2)==TOK_BADSTRING_NL || LA(2)==TOK_ACROSS || LA(2)==TOK_ANY || LA(2)==TOK_ASSIGNER || LA(2)==TOK_ASSIGN || 
LA(2)==TOK_BREAKTOKEN || LA(2)==TOK_BY || LA(2)==TOK_CLASS || LA(2)==TOK_CONTINUE || LA(2)==TOK_CONTROL || 
LA(2)==TOK_CREATE || LA(2)==TOK_CREATOR || LA(2)==TOK_DELETE || LA(2)==TOK_EACH || LA(2)==TOK_END || 
LA(2)==TOK_EVENT || LA(2)==TOK_FOR || LA(2)==TOK_FROM || LA(2)==TOK_GENERATE || LA(2)==TOK_IN || 
LA(2)==TOK_INSTANCES || LA(2)==TOK_INSTANCE || LA(2)==TOK_MANY || LA(2)==TOK_OBJECT || LA(2)==TOK_OF || 
LA(2)==TOK_ONE || LA(2)==TOK_RELATED || LA(2)==TOK_RELATE || LA(2)==TOK_SELECT || LA(2)==TOK_STOP || 
LA(2)==TOK_TO || LA(2)==TOK_WHERE || LA(2)==TOK_UNRELATE || LA(2)==TOK_USING || LA(2)==TOK_BRIDGE || 
LA(2)==TOK_CARDINALITY || LA(2)==TOK_EMPTY || LA(2)==TOK_FALSETOKEN || LA(2)==TOK_NOT || LA(2)==TOK_NOTEMPTY || 
LA(2)==TOK_TRANSFORM || LA(2)==TOK_TRUETOKEN || LA(2)==TOK_PARAM || LA(2)==TOK_RCVD_EVT || LA(2)==TOK_SELECTED || 
LA(2)==TOK_SELF || LA(2)==TOK_AND || LA(2)==TOK_ELIF || LA(2)==TOK_ELSE || LA(2)==TOK_IF || 
LA(2)==TOK_OR || LA(2)==TOK_RETURN || LA(2)==TOK_WHILE || LA(2)==TOK_DIV || LA(2)==TOK_DOT || 
LA(2)==TOK_DOUBLECOLON || LA(2)==TOK_DOUBLEEQUAL || LA(2)==TOK_GE || LA(2)==TOK_GT || LA(2)==TOK_LE || 
LA(2)==TOK_LESSTHAN || LA(2)==TOK_LPAREN || LA(2)==TOK_MINUS || LA(2)==TOK_MOD || LA(2)==TOK_NOTEQUAL || 
LA(2)==TOK_PLUS || LA(2)==TOK_RPAREN || LA(2)==TOK_TIMES || LA(2)==TOK_QMARK || LA(2)==TOK_QUOTE || 
LA(2)==TOK_FRACTION || LA(2)==TOK_GENERAL_NAME || LA(2)==TOK_GARBAGE || LA(2)==TOK_BAD_ID || LA(2)==TOK_BAD_NAME || 
LA(2)==TOK_ID || LA(2)==TOK_RELID || LA(2)==TOK_NUMBER) ) {
							_ast = NULL;
							if ( !guessing ) {
								 _retv  = expr(&_ast,&_signal); if (_signal) goto _handler;
								if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
								_ast21 = (AST *)_ast;
								ASTBase::link(_root, &_sibling, &_tail);
								e_ast = _ast21;
							} else {
								expr(&_ast,&_signal);
							}
							if ( !guessing ) {
							lp_ast->setObjPtr(e_ast->getObjPtr());
							}
						}
						else {
							if ( guessing ) goto fail;
							if (_sva) _signal=NoViableAlt;
							else _signal=NoSemViableAlt;
							goto _handler;  /* MR7 */
						}
					}
				}
				zzmatch_wsig(TOK_RPAREN, _handler);				
				if ( !guessing ) {
				 _t13 = (ANTLRTokenPtr)LT(1);
}
 labase++;
				 
				if ( !guessing ) {
								rp = _t13;
				}
				
				if ( !guessing ) {
				lp_ast->setType(TOK_PAREN_EXPR);
				lp_ast->setDatatype(_retv);
				p_ast = (new AST( rp));
				lp_ast->setSegLength(p_ast->getOffset() +
				1 -
				lp_ast->getOffset());
				delete p_ast;
				}
 consume();
			}
			else {
				if ( guessing ) goto fail;
				if (_sva) _signal=NoViableAlt;
				else _signal=NoSemViableAlt;
				goto _handler;  /* MR7 */
			}
		}
	}
	return _retv;
fail:
	if ( guessing ) zzGUESS_FAIL;
	syn(zzBadTok, "expression", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd12, 0x80);
	return _retv;
_handler:
	zzdflthandlers(_signal,_retsignal);
	return _retv;
}

  t_core_data_type   
P::rval(ASTBase **_root,int *_retsignal)
{
	  t_core_data_type   	 _retv;
	zzRULE;
	int _sva=1;
	ASTBase *_ast = NULL, *_sibling = NULL, *_tail = NULL;
	ANTLRTokenPtr _t11=NULL,_t12=NULL;
	AST *_ast11=NULL,*_ast12=NULL,*_ast13=NULL;
	ANTLRTokenPtr q=NULL;
	AST *q_ast=NULL;
	int _signal=NoSignal;
	PURIFY(_retv,sizeof(  t_core_data_type   	))
	*_retsignal = NoSignal;
	zzGUESS_BLOCK
	zzGUESS
	if ( !zzrv && (LA(1)==TOK_DOUBLECOLON) ) {
		{
			ANTLRTokenPtr _t21=NULL;
			AST *_ast21=NULL;
			zzmatch_wsig(TOK_DOUBLECOLON, _handler);			
			if ( !guessing ) {
			 _t21 = (ANTLRTokenPtr)LT(1);
}
 labase++;
			if ( !guessing ) {
			
			_ast21 = new AST(_t21);
			_ast21->subchild(_root, &_sibling, &_tail);
			}
			 consume();
		}
		zzGUESS_DONE
		zzmatch_wsig(TOK_DOUBLECOLON, _handler);		
		if ( !guessing ) {
		 _t12 = (ANTLRTokenPtr)LT(1);
}
 labase++;
		  consume();
		_ast = NULL;
		if ( !guessing ) {
			 _retv  = synch_svc_invocation(&_ast,&_signal, TRUE ); if (_signal) goto _handler;
			if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
			_ast13 = (AST *)_ast;
			ASTBase::link(_root, &_sibling, &_tail);
		} else {
			synch_svc_invocation(&_ast,&_signal, TRUE );
		}
	}
	else {
		if ( !zzrv ) zzGUESS_DONE;
		zzGUESS
		if ( !zzrv && (
LA(1)==TOK_ACROSS || LA(1)==TOK_ANY || LA(1)==TOK_ASSIGNER || LA(1)==TOK_ASSIGN || LA(1)==TOK_BREAKTOKEN || 
LA(1)==TOK_BY || LA(1)==TOK_CLASS || LA(1)==TOK_CONTINUE || LA(1)==TOK_CONTROL || LA(1)==TOK_CREATE || 
LA(1)==TOK_CREATOR || LA(1)==TOK_DELETE || LA(1)==TOK_EACH || LA(1)==TOK_END || LA(1)==TOK_EVENT || 
LA(1)==TOK_FOR || LA(1)==TOK_FROM || LA(1)==TOK_GENERATE || LA(1)==TOK_IN || LA(1)==TOK_INSTANCES || 
LA(1)==TOK_INSTANCE || LA(1)==TOK_MANY || LA(1)==TOK_OBJECT || LA(1)==TOK_OF || LA(1)==TOK_ONE || 
LA(1)==TOK_RELATED || LA(1)==TOK_RELATE || LA(1)==TOK_SELECT || LA(1)==TOK_STOP || LA(1)==TOK_TO || 
LA(1)==TOK_WHERE || LA(1)==TOK_UNRELATE || LA(1)==TOK_USING || LA(1)==TOK_SELECTED || LA(1)==TOK_SELF || 
LA(1)==TOK_GARBAGE || LA(1)==TOK_BAD_ID || LA(1)==TOK_BAD_NAME || LA(1)==TOK_ID || LA(1)==TOK_RELID) && 
(LA(2)==TOK_DOT) ) {
			{
				AST *_ast21=NULL;
				_ast = NULL;
				if ( !guessing ) {
					 _retv  = transform_ib_invocation(&_ast,&_signal, TRUE ); if (_signal) goto _handler;
					if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
					_ast21 = (AST *)_ast;
					ASTBase::link(_root, &_sibling, &_tail);
				} else {
					transform_ib_invocation(&_ast,&_signal, TRUE );
				}
			}
			zzGUESS_DONE
			_ast = NULL;
			if ( !guessing ) {
				 _retv  = transform_ib_invocation(&_ast,&_signal, TRUE ); if (_signal) goto _handler;
				if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
				_ast12 = (AST *)_ast;
				ASTBase::link(_root, &_sibling, &_tail);
			} else {
				transform_ib_invocation(&_ast,&_signal, TRUE );
			}
		}
		else {
			if ( !zzrv ) zzGUESS_DONE;
			zzGUESS
			if ( !zzrv && (LA(1)==TOK_ACROSS || LA(1)==TOK_ANY || LA(1)==TOK_ASSIGNER || 
LA(1)==TOK_ASSIGN || LA(1)==TOK_BREAKTOKEN || LA(1)==TOK_BY || LA(1)==TOK_CLASS || LA(1)==TOK_CONTINUE || 
LA(1)==TOK_CONTROL || LA(1)==TOK_CREATE || LA(1)==TOK_CREATOR || LA(1)==TOK_DELETE || LA(1)==TOK_EACH || 
LA(1)==TOK_END || LA(1)==TOK_EVENT || LA(1)==TOK_FOR || LA(1)==TOK_FROM || LA(1)==TOK_GENERATE || 
LA(1)==TOK_IN || LA(1)==TOK_INSTANCES || LA(1)==TOK_INSTANCE || LA(1)==TOK_MANY || LA(1)==TOK_OBJECT || 
LA(1)==TOK_OF || LA(1)==TOK_ONE || LA(1)==TOK_RELATED || LA(1)==TOK_RELATE || LA(1)==TOK_SELECT || 
LA(1)==TOK_STOP || LA(1)==TOK_TO || LA(1)==TOK_WHERE || LA(1)==TOK_UNRELATE || LA(1)==TOK_USING || 
LA(1)==TOK_BRIDGE || LA(1)==TOK_CARDINALITY || LA(1)==TOK_EMPTY || LA(1)==TOK_FALSETOKEN || LA(1)==TOK_NOT || 
LA(1)==TOK_NOTEMPTY || LA(1)==TOK_TRANSFORM || LA(1)==TOK_TRUETOKEN || LA(1)==TOK_PARAM || LA(1)==TOK_RCVD_EVT || 
LA(1)==TOK_SELECTED || LA(1)==TOK_SELF || LA(1)==TOK_GENERAL_NAME || LA(1)==TOK_GARBAGE || LA(1)==TOK_BAD_ID || 
LA(1)==TOK_BAD_NAME || LA(1)==TOK_ID || LA(1)==TOK_RELID) && (LA(2)==TOK_DOUBLECOLON) ) {
				{
					AST *_ast21=NULL;
					_ast = NULL;
					if ( !guessing ) {
						 _retv  = bridge_or_transform_expr(&_ast,&_signal); if (_signal) goto _handler;
						if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
						_ast21 = (AST *)_ast;
						ASTBase::link(_root, &_sibling, &_tail);
					} else {
						bridge_or_transform_expr(&_ast,&_signal);
					}
				}
				zzGUESS_DONE
				_ast = NULL;
				if ( !guessing ) {
					 _retv  = bridge_or_transform_expr(&_ast,&_signal); if (_signal) goto _handler;
					if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
					_ast12 = (AST *)_ast;
					ASTBase::link(_root, &_sibling, &_tail);
				} else {
					bridge_or_transform_expr(&_ast,&_signal);
				}
			}
			else {
				if ( !zzrv ) zzGUESS_DONE;
				zzGUESS
				if ( !zzrv && (
LA(1)==TOK_ACROSS || LA(1)==TOK_ANY || LA(1)==TOK_ASSIGNER || LA(1)==TOK_ASSIGN || LA(1)==TOK_BREAKTOKEN || 
LA(1)==TOK_BY || LA(1)==TOK_CLASS || LA(1)==TOK_CONTINUE || LA(1)==TOK_CONTROL || LA(1)==TOK_CREATE || 
LA(1)==TOK_CREATOR || LA(1)==TOK_DELETE || LA(1)==TOK_EACH || LA(1)==TOK_END || LA(1)==TOK_EVENT || 
LA(1)==TOK_FOR || LA(1)==TOK_FROM || LA(1)==TOK_GENERATE || LA(1)==TOK_IN || LA(1)==TOK_INSTANCES || 
LA(1)==TOK_INSTANCE || LA(1)==TOK_MANY || LA(1)==TOK_OBJECT || LA(1)==TOK_OF || LA(1)==TOK_ONE || 
LA(1)==TOK_RELATED || LA(1)==TOK_RELATE || LA(1)==TOK_SELECT || LA(1)==TOK_STOP || LA(1)==TOK_TO || 
LA(1)==TOK_WHERE || LA(1)==TOK_UNRELATE || LA(1)==TOK_USING || LA(1)==TOK_BRIDGE || LA(1)==TOK_CARDINALITY || 
LA(1)==TOK_EMPTY || LA(1)==TOK_FALSETOKEN || LA(1)==TOK_NOT || LA(1)==TOK_NOTEMPTY || LA(1)==TOK_TRANSFORM || 
LA(1)==TOK_TRUETOKEN || LA(1)==TOK_PARAM || LA(1)==TOK_RCVD_EVT || LA(1)==TOK_SELECTED || LA(1)==TOK_SELF || 
LA(1)==TOK_GENERAL_NAME || LA(1)==TOK_GARBAGE || LA(1)==TOK_BAD_ID || LA(1)==TOK_BAD_NAME || LA(1)==TOK_ID || 
LA(1)==TOK_RELID) && (LA(2)==TOK_DOUBLECOLON) ) {
					{
						AST *_ast21=NULL;
						_ast = NULL;
						if ( !guessing ) {
							 _retv  = enumerator_access(&_ast,&_signal); if (_signal) goto _handler;
							if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
							_ast21 = (AST *)_ast;
							ASTBase::link(_root, &_sibling, &_tail);
						} else {
							enumerator_access(&_ast,&_signal);
						}
					}
					zzGUESS_DONE
					_ast = NULL;
					if ( !guessing ) {
						 _retv  = enumerator_access(&_ast,&_signal); if (_signal) goto _handler;
						if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
						_ast12 = (AST *)_ast;
						ASTBase::link(_root, &_sibling, &_tail);
					} else {
						enumerator_access(&_ast,&_signal);
					}
				}
				else {
					if ( !zzrv ) zzGUESS_DONE;
					if ( (LA(1)==TOK_ACROSS || LA(1)==TOK_ANY || 
LA(1)==TOK_ASSIGNER || LA(1)==TOK_ASSIGN || LA(1)==TOK_BREAKTOKEN || LA(1)==TOK_BY || LA(1)==TOK_CLASS || 
LA(1)==TOK_CONTINUE || LA(1)==TOK_CONTROL || LA(1)==TOK_CREATE || LA(1)==TOK_CREATOR || LA(1)==TOK_DELETE || 
LA(1)==TOK_EACH || LA(1)==TOK_END || LA(1)==TOK_EVENT || LA(1)==TOK_FOR || LA(1)==TOK_FROM || 
LA(1)==TOK_GENERATE || LA(1)==TOK_IN || LA(1)==TOK_INSTANCES || LA(1)==TOK_INSTANCE || LA(1)==TOK_MANY || 
LA(1)==TOK_OBJECT || LA(1)==TOK_OF || LA(1)==TOK_ONE || LA(1)==TOK_RELATED || LA(1)==TOK_RELATE || 
LA(1)==TOK_SELECT || LA(1)==TOK_STOP || LA(1)==TOK_TO || LA(1)==TOK_WHERE || LA(1)==TOK_UNRELATE || 
LA(1)==TOK_USING || LA(1)==TOK_SELECTED || LA(1)==TOK_SELF || LA(1)==TOK_GARBAGE || LA(1)==TOK_BAD_ID || 
LA(1)==TOK_BAD_NAME || LA(1)==TOK_ID || LA(1)==TOK_RELID) && (LA(2)==TOK_DOT) ) {
						_ast = NULL;
						if ( !guessing ) {
							 _retv  = attribute_access(&_ast,&_signal, ASSIGN_RVAL ); if (_signal) goto _handler;
							if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
							_ast11 = (AST *)_ast;
							ASTBase::link(_root, &_sibling, &_tail);
						} else {
							attribute_access(&_ast,&_signal, ASSIGN_RVAL );
						}
					}
					else {
						if ( !zzrv ) zzGUESS_DONE;
						if ( (
LA(1)==TOK_FALSETOKEN || LA(1)==TOK_TRUETOKEN || LA(1)==TOK_QUOTE || LA(1)==TOK_FRACTION || LA(1)==TOK_NUMBER) && 
(LA(2)==Eof || LA(2)==TOK_BADSTRING_EOF || LA(2)==TOK_STRING || LA(2)==TOK_BADSTRING_NL || 
LA(2)==TOK_ACROSS || LA(2)==TOK_ANY || LA(2)==TOK_ASSIGNER || LA(2)==TOK_ASSIGN || LA(2)==TOK_BREAKTOKEN || 
LA(2)==TOK_BY || LA(2)==TOK_CLASS || LA(2)==TOK_CONTINUE || LA(2)==TOK_CONTROL || LA(2)==TOK_CREATE || 
LA(2)==TOK_CREATOR || LA(2)==TOK_DELETE || LA(2)==TOK_EACH || LA(2)==TOK_END || LA(2)==TOK_EVENT || 
LA(2)==TOK_FOR || LA(2)==TOK_FROM || LA(2)==TOK_GENERATE || LA(2)==TOK_IN || LA(2)==TOK_INSTANCES || 
LA(2)==TOK_INSTANCE || LA(2)==TOK_MANY || LA(2)==TOK_OBJECT || LA(2)==TOK_OF || LA(2)==TOK_ONE || 
LA(2)==TOK_RELATED || LA(2)==TOK_RELATE || LA(2)==TOK_SELECT || LA(2)==TOK_STOP || LA(2)==TOK_TO || 
LA(2)==TOK_WHERE || LA(2)==TOK_UNRELATE || LA(2)==TOK_USING || LA(2)==TOK_BRIDGE || LA(2)==TOK_CARDINALITY || 
LA(2)==TOK_EMPTY || LA(2)==TOK_FALSETOKEN || LA(2)==TOK_NOT || LA(2)==TOK_NOTEMPTY || LA(2)==TOK_TRANSFORM || 
LA(2)==TOK_TRUETOKEN || LA(2)==TOK_PARAM || LA(2)==TOK_RCVD_EVT || LA(2)==TOK_SELECTED || LA(2)==TOK_SELF || 
LA(2)==TOK_AND || LA(2)==TOK_ELIF || LA(2)==TOK_ELSE || LA(2)==TOK_IF || LA(2)==TOK_OR || 
LA(2)==TOK_RETURN || LA(2)==TOK_WHILE || LA(2)==TOK_DEBUG || LA(2)==TOK_COMMA || LA(2)==TOK_DIV || 
LA(2)==TOK_DOUBLECOLON || LA(2)==TOK_DOUBLEEQUAL || LA(2)==TOK_GE || LA(2)==TOK_GT || LA(2)==TOK_LE || 
LA(2)==TOK_LESSTHAN || LA(2)==TOK_MINUS || LA(2)==TOK_MOD || LA(2)==TOK_NOTEQUAL || LA(2)==TOK_PLUS || 
LA(2)==TOK_RPAREN || LA(2)==TOK_SEMI || LA(2)==TOK_TIMES || LA(2)==TOK_GENERAL_NAME || LA(2)==TOK_GARBAGE || 
LA(2)==TOK_BAD_ID || LA(2)==TOK_BAD_NAME || LA(2)==TOK_ID || LA(2)==TOK_RELID) ) {
							_ast = NULL;
							if ( !guessing ) {
								 _retv  = constant_value(&_ast,&_signal); if (_signal) goto _handler;
								if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
								_ast11 = (AST *)_ast;
								ASTBase::link(_root, &_sibling, &_tail);
							} else {
								constant_value(&_ast,&_signal);
							}
						}
						else {
							if ( !zzrv ) zzGUESS_DONE;
							if ( (LA(1)==TOK_ACROSS || 
LA(1)==TOK_ANY || LA(1)==TOK_ASSIGNER || LA(1)==TOK_ASSIGN || LA(1)==TOK_BREAKTOKEN || LA(1)==TOK_BY || 
LA(1)==TOK_CLASS || LA(1)==TOK_CONTINUE || LA(1)==TOK_CONTROL || LA(1)==TOK_CREATE || LA(1)==TOK_CREATOR || 
LA(1)==TOK_DELETE || LA(1)==TOK_EACH || LA(1)==TOK_END || LA(1)==TOK_EVENT || LA(1)==TOK_FOR || 
LA(1)==TOK_FROM || LA(1)==TOK_GENERATE || LA(1)==TOK_IN || LA(1)==TOK_INSTANCES || LA(1)==TOK_INSTANCE || 
LA(1)==TOK_MANY || LA(1)==TOK_OBJECT || LA(1)==TOK_OF || LA(1)==TOK_ONE || LA(1)==TOK_RELATED || 
LA(1)==TOK_RELATE || LA(1)==TOK_SELECT || LA(1)==TOK_STOP || LA(1)==TOK_TO || LA(1)==TOK_WHERE || 
LA(1)==TOK_UNRELATE || LA(1)==TOK_USING || LA(1)==TOK_SELECTED || LA(1)==TOK_SELF || LA(1)==TOK_GARBAGE || 
LA(1)==TOK_BAD_ID || LA(1)==TOK_BAD_NAME || LA(1)==TOK_ID || LA(1)==TOK_RELID) && (
LA(2)==Eof || LA(2)==TOK_ACROSS || LA(2)==TOK_ANY || LA(2)==TOK_ASSIGNER || LA(2)==TOK_ASSIGN || 
LA(2)==TOK_BREAKTOKEN || LA(2)==TOK_BY || LA(2)==TOK_CLASS || LA(2)==TOK_CONTINUE || LA(2)==TOK_CONTROL || 
LA(2)==TOK_CREATE || LA(2)==TOK_CREATOR || LA(2)==TOK_DELETE || LA(2)==TOK_EACH || LA(2)==TOK_END || 
LA(2)==TOK_EVENT || LA(2)==TOK_FOR || LA(2)==TOK_FROM || LA(2)==TOK_GENERATE || LA(2)==TOK_IN || 
LA(2)==TOK_INSTANCES || LA(2)==TOK_INSTANCE || LA(2)==TOK_MANY || LA(2)==TOK_OBJECT || LA(2)==TOK_OF || 
LA(2)==TOK_ONE || LA(2)==TOK_RELATED || LA(2)==TOK_RELATE || LA(2)==TOK_SELECT || LA(2)==TOK_STOP || 
LA(2)==TOK_TO || LA(2)==TOK_WHERE || LA(2)==TOK_UNRELATE || LA(2)==TOK_USING || LA(2)==TOK_BRIDGE || 
LA(2)==TOK_CARDINALITY || LA(2)==TOK_EMPTY || LA(2)==TOK_FALSETOKEN || LA(2)==TOK_NOT || LA(2)==TOK_NOTEMPTY || 
LA(2)==TOK_TRANSFORM || LA(2)==TOK_TRUETOKEN || LA(2)==TOK_PARAM || LA(2)==TOK_RCVD_EVT || LA(2)==TOK_SELECTED || 
LA(2)==TOK_SELF || LA(2)==TOK_AND || LA(2)==TOK_ELIF || LA(2)==TOK_ELSE || LA(2)==TOK_IF || 
LA(2)==TOK_OR || LA(2)==TOK_RETURN || LA(2)==TOK_WHILE || LA(2)==TOK_DEBUG || LA(2)==TOK_COMMA || 
LA(2)==TOK_DIV || LA(2)==TOK_DOUBLECOLON || LA(2)==TOK_DOUBLEEQUAL || LA(2)==TOK_GE || LA(2)==TOK_GT || 
LA(2)==TOK_LE || LA(2)==TOK_LESSTHAN || LA(2)==TOK_MINUS || LA(2)==TOK_MOD || LA(2)==TOK_NOTEQUAL || 
LA(2)==TOK_PLUS || LA(2)==TOK_RPAREN || LA(2)==TOK_SEMI || LA(2)==TOK_TIMES || LA(2)==TOK_GENERAL_NAME || 
LA(2)==TOK_GARBAGE || LA(2)==TOK_BAD_ID || LA(2)==TOK_BAD_NAME || LA(2)==TOK_ID || LA(2)==TOK_RELID) ) {
								_ast = NULL;
								if ( !guessing ) {
									 _retv  = variable(&_ast,&_signal); if (_signal) goto _handler;
									if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
									_ast11 = (AST *)_ast;
									ASTBase::link(_root, &_sibling, &_tail);
								} else {
									variable(&_ast,&_signal);
								}
							}
							else {
								if ( !zzrv ) zzGUESS_DONE;
								if ( (
LA(1)==TOK_RCVD_EVT) && (LA(2)==TOK_DOT) ) {
									_ast = NULL;
									if ( !guessing ) {
										 _retv  = event_data_access(&_ast,&_signal, ASSIGN_RVAL ); if (_signal) goto _handler;
										if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
										_ast11 = (AST *)_ast;
										ASTBase::link(_root, &_sibling, &_tail);
									} else {
										event_data_access(&_ast,&_signal, ASSIGN_RVAL );
									}
								}
								else {
									if ( !zzrv ) zzGUESS_DONE;
									if ( (LA(1)==TOK_BRIDGE) && (
LA(2)==TOK_ACROSS || LA(2)==TOK_ANY || LA(2)==TOK_ASSIGNER || LA(2)==TOK_ASSIGN || LA(2)==TOK_BREAKTOKEN || 
LA(2)==TOK_BY || LA(2)==TOK_CLASS || LA(2)==TOK_CONTINUE || LA(2)==TOK_CONTROL || LA(2)==TOK_CREATE || 
LA(2)==TOK_CREATOR || LA(2)==TOK_DELETE || LA(2)==TOK_EACH || LA(2)==TOK_END || LA(2)==TOK_EVENT || 
LA(2)==TOK_FOR || LA(2)==TOK_FROM || LA(2)==TOK_GENERATE || LA(2)==TOK_IN || LA(2)==TOK_INSTANCES || 
LA(2)==TOK_INSTANCE || LA(2)==TOK_MANY || LA(2)==TOK_OBJECT || LA(2)==TOK_OF || LA(2)==TOK_ONE || 
LA(2)==TOK_RELATED || LA(2)==TOK_RELATE || LA(2)==TOK_SELECT || LA(2)==TOK_STOP || LA(2)==TOK_TO || 
LA(2)==TOK_WHERE || LA(2)==TOK_UNRELATE || LA(2)==TOK_USING || LA(2)==TOK_BRIDGE || LA(2)==TOK_CARDINALITY || 
LA(2)==TOK_EMPTY || LA(2)==TOK_FALSETOKEN || LA(2)==TOK_NOT || LA(2)==TOK_NOTEMPTY || LA(2)==TOK_TRANSFORM || 
LA(2)==TOK_TRUETOKEN || LA(2)==TOK_PARAM || LA(2)==TOK_RCVD_EVT || LA(2)==TOK_SELECTED || LA(2)==TOK_SELF || 
LA(2)==TOK_GENERAL_NAME || LA(2)==TOK_GARBAGE || LA(2)==TOK_BAD_ID || LA(2)==TOK_BAD_NAME || LA(2)==TOK_ID || 
LA(2)==TOK_RELID) ) {
										_ast = NULL;
										if ( !guessing ) {
											 _retv  = bridge_expr(&_ast,&_signal); if (_signal) goto _handler;
											if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
											_ast11 = (AST *)_ast;
											ASTBase::link(_root, &_sibling, &_tail);
										} else {
											bridge_expr(&_ast,&_signal);
										}
									}
									else {
										if ( !zzrv ) zzGUESS_DONE;
										if ( (LA(1)==TOK_TRANSFORM) && (LA(2)==TOK_ACROSS || LA(2)==TOK_ANY || 
LA(2)==TOK_ASSIGNER || LA(2)==TOK_ASSIGN || LA(2)==TOK_BREAKTOKEN || LA(2)==TOK_BY || LA(2)==TOK_CLASS || 
LA(2)==TOK_CONTINUE || LA(2)==TOK_CONTROL || LA(2)==TOK_CREATE || LA(2)==TOK_CREATOR || LA(2)==TOK_DELETE || 
LA(2)==TOK_EACH || LA(2)==TOK_END || LA(2)==TOK_EVENT || LA(2)==TOK_FOR || LA(2)==TOK_FROM || 
LA(2)==TOK_GENERATE || LA(2)==TOK_IN || LA(2)==TOK_INSTANCES || LA(2)==TOK_INSTANCE || LA(2)==TOK_MANY || 
LA(2)==TOK_OBJECT || LA(2)==TOK_OF || LA(2)==TOK_ONE || LA(2)==TOK_RELATED || LA(2)==TOK_RELATE || 
LA(2)==TOK_SELECT || LA(2)==TOK_STOP || LA(2)==TOK_TO || LA(2)==TOK_WHERE || LA(2)==TOK_UNRELATE || 
LA(2)==TOK_USING || LA(2)==TOK_BRIDGE || LA(2)==TOK_CARDINALITY || LA(2)==TOK_EMPTY || LA(2)==TOK_FALSETOKEN || 
LA(2)==TOK_NOT || LA(2)==TOK_NOTEMPTY || LA(2)==TOK_TRANSFORM || LA(2)==TOK_TRUETOKEN || LA(2)==TOK_PARAM || 
LA(2)==TOK_RCVD_EVT || LA(2)==TOK_SELECTED || LA(2)==TOK_SELF || LA(2)==TOK_GENERAL_NAME || LA(2)==TOK_GARBAGE || 
LA(2)==TOK_BAD_ID || LA(2)==TOK_BAD_NAME || LA(2)==TOK_ID || LA(2)==TOK_RELID) ) {
											_ast = NULL;
											if ( !guessing ) {
												 _retv  = transform_expr(&_ast,&_signal); if (_signal) goto _handler;
												if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
												_ast11 = (AST *)_ast;
												ASTBase::link(_root, &_sibling, &_tail);
											} else {
												transform_expr(&_ast,&_signal);
											}
										}
										else {
											if ( !zzrv ) zzGUESS_DONE;
											if ( (LA(1)==TOK_PARAM) && 
(LA(2)==TOK_DOT) ) {
												_ast = NULL;
												if ( !guessing ) {
													 _retv  = param_data_access(&_ast,&_signal, ASSIGN_RVAL ); if (_signal) goto _handler;
													if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
													_ast11 = (AST *)_ast;
													ASTBase::link(_root, &_sibling, &_tail);
												} else {
													param_data_access(&_ast,&_signal, ASSIGN_RVAL );
												}
											}
											else {
												if ( !zzrv ) zzGUESS_DONE;
												if ( (LA(1)==TOK_QMARK) ) {
													zzmatch_wsig(TOK_QMARK, _handler);													
													if ( !guessing ) {
													 _t11 = (ANTLRTokenPtr)LT(1);
}
 labase++;
													if ( !guessing ) {
													
													_ast11 = new AST(_t11);
													_ast11->subchild(_root, &_sibling, &_tail);
													}
													
													if ( !guessing ) {
																										q = _t11;
													q_ast = _ast11;
													}
													
													if ( !guessing ) {
													_retv = QMARK_DATATYPE;
													q_ast->setSegLength(strlen(q_ast->getAsciiText()));
													ttqm->add( q_ast );
													if ( ! wspecflag )
													AL_PARSE_ERR1( q_ast, AL_GETMSG(ERR, 300, 1), q_ast->getVcharText() )
													}
 consume();
												}
												else {
													if ( guessing ) goto fail;
													if (_sva) _signal=NoViableAlt;
													else _signal=NoSemViableAlt;
													goto _handler;  /* MR7 */
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	return _retv;
fail:
	if ( guessing ) zzGUESS_FAIL;
	syn(zzBadTok, "expression", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd13, 0x1);
	return _retv;
_handler:
	zzdflthandlers(_signal,_retsignal);
	return _retv;
}

  t_core_data_type   
P::variable(ASTBase **_root,int *_retsignal)
{
	  t_core_data_type   	 _retv;
	zzRULE;
	int _sva=1;
	ASTBase *_ast = NULL, *_sibling = NULL, *_tail = NULL;
	AST *_ast11=NULL;
	ANTLRTokenPtr idx=NULL;
	AST *idx_ast=NULL;
	int _signal=NoSignal;
	PURIFY(_retv,sizeof(  t_core_data_type   	))
	*_retsignal = NoSignal;
	Sym *s = NULL;
	_ast = NULL;
	local_variable(&_ast,&_signal, ASSIGN_RVAL ); if (_signal) goto _handler;
	if (!guessing) {    /* MR10 */
		if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
		_ast11 = (AST *)_ast;
		ASTBase::link(_root, &_sibling, &_tail);
	};    /* MR10 */
	idx_ast = _ast11;
	if ( !guessing ) {
	if ( st->is_var_this_space_defined( idx_ast->getVcharText(),
	SYMBOL_ENTRY_NON_INST_REF, &s ) )
	{
		_retv = (t_core_data_type)s->datatype;
		idx_ast->setDatatype(_retv);
		idx_ast->setObjPtr(s->objPtr);
		idx_ast->setReadOnly(FALSE);
	}
	else if ( st->is_var_this_space_defined( idx_ast->getVcharText(),
	SYMBOL_ENTRY_INST_REF, &s ) )
	{
		_retv = (t_core_data_type)s->datatype;
		idx_ast->setDatatype(_retv);
		idx_ast->setObjPtr(s->objPtr);
		idx_ast->setReadOnly(FALSE);
	}
	else
	{
		_retv = UNKNOWN_DATATYPE;
		idx_ast->setDatatype(_retv);
		AL_PARSE_ERR1( idx_ast, AL_GETMSG( ERR, 044, 1), idx_ast->getVcharText() )
	}
	}
	return _retv;
fail:
	if ( guessing ) zzGUESS_FAIL;
	syn(zzBadTok, "local variable", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd13, 0x2);
	return _retv;
_handler:
	zzdflthandlers(_signal,_retsignal);
	return _retv;
}

 t_core_data_type  
P::constant_value(ASTBase **_root,int *_retsignal)
{
	 t_core_data_type  	 _retv;
	zzRULE;
	int _sva=1;
	ASTBase *_ast = NULL, *_sibling = NULL, *_tail = NULL;
	AST *_ast11=NULL;
	ANTLRTokenPtr op1=NULL, op2=NULL, op4=NULL, op5=NULL, op3=NULL;
	AST *op1_ast=NULL, *op2_ast=NULL, *op4_ast=NULL, *op5_ast=NULL, *op3_ast=NULL;
	int _signal=NoSignal;
	PURIFY(_retv,sizeof( t_core_data_type  	))
	*_retsignal = NoSignal;
	AST *t;
	if ( (LA(1)==TOK_FALSETOKEN || 
LA(1)==TOK_TRUETOKEN || LA(1)==TOK_FRACTION || LA(1)==TOK_NUMBER) ) {
		{
			ANTLRTokenPtr _t21=NULL;
			AST *_ast21=NULL;
			if ( (LA(1)==TOK_FRACTION)
 ) {
				zzmatch_wsig(TOK_FRACTION, _handler);				
				if ( !guessing ) {
				 _t21 = (ANTLRTokenPtr)LT(1);
}
 labase++;
				if ( !guessing ) {
				
				_ast21 = new AST(_t21);
				_ast21->subchild(_root, &_sibling, &_tail);
				}
				
				if ( !guessing ) {
								op1 = _t21;
				op1_ast = _ast21;
				}
				
				if ( !guessing ) {
				_retv = REAL_DATATYPE;    t = op1_ast;
				}
 consume();
			}
			else {
				if ( (LA(1)==TOK_NUMBER) ) {
					zzmatch_wsig(TOK_NUMBER, _handler);					
					if ( !guessing ) {
					 _t21 = (ANTLRTokenPtr)LT(1);
}
 labase++;
					if ( !guessing ) {
					
					_ast21 = new AST(_t21);
					_ast21->subchild(_root, &_sibling, &_tail);
					}
					
					if ( !guessing ) {
										op2 = _t21;
					op2_ast = _ast21;
					}
					
					if ( !guessing ) {
					_retv = INTEGER_DATATYPE; t = op2_ast;
					}
 consume();
				}
				else {
					if ( (LA(1)==TOK_TRUETOKEN) ) {
						zzmatch_wsig(TOK_TRUETOKEN, _handler);						
						if ( !guessing ) {
						 _t21 = (ANTLRTokenPtr)LT(1);
}
 labase++;
						if ( !guessing ) {
						
						_ast21 = new AST(_t21);
						_ast21->subchild(_root, &_sibling, &_tail);
						}
						
						if ( !guessing ) {
												op4 = _t21;
						op4_ast = _ast21;
						}
						
						if ( !guessing ) {
						_retv = BOOLEAN_DATATYPE; t = op4_ast;
						}
 consume();
					}
					else {
						if ( (
LA(1)==TOK_FALSETOKEN) ) {
							zzmatch_wsig(TOK_FALSETOKEN, _handler);							
							if ( !guessing ) {
							 _t21 = (ANTLRTokenPtr)LT(1);
}
 labase++;
							if ( !guessing ) {
							
							_ast21 = new AST(_t21);
							_ast21->subchild(_root, &_sibling, &_tail);
							}
							
							if ( !guessing ) {
														op5 = _t21;
							op5_ast = _ast21;
							}
							
							if ( !guessing ) {
							_retv = BOOLEAN_DATATYPE; t = op5_ast;
							}
 consume();
						}
						else {
							if ( guessing ) goto fail;
							if (_sva) _signal=NoViableAlt;
							else _signal=NoSemViableAlt;
							goto _handler;  /* MR7 */
						}
					}
				}
			}
		}
		if ( !guessing ) {
		t->setDatatype(_retv);
		t->setSegLength(strlen(t->getAsciiText()));
		}
	}
	else {
		if ( (LA(1)==TOK_QUOTE) ) {
			_ast = NULL;
			quoted_string(&_ast,&_signal); if (_signal) goto _handler;
			if (!guessing) {    /* MR10 */
				if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
				_ast11 = (AST *)_ast;
				ASTBase::link(_root, &_sibling, &_tail);
			};    /* MR10 */
			op3_ast = _ast11;
			if ( !guessing ) {
			_retv = STRING_DATATYPE;
			op3_ast->setDatatype(_retv);
			}
		}
		else {
			if ( guessing ) goto fail;
			if (_sva) _signal=NoViableAlt;
			else _signal=NoSemViableAlt;
			goto _handler;  /* MR7 */
		}
	}
	return _retv;
fail:
	if ( guessing ) zzGUESS_FAIL;
	syn(zzBadTok, "constant", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd13, 0x4);
	return _retv;
_handler:
	zzdflthandlers(_signal,_retsignal);
	return _retv;
}

void
P::quoted_string(ASTBase **_root,int *_retsignal)
{
	zzRULE;
	int _sva=1;
	ASTBase *_ast = NULL, *_sibling = NULL, *_tail = NULL;
	ANTLRTokenPtr _t11=NULL;
	AST *_ast11=NULL;
	ANTLRTokenPtr tq=NULL, s1=NULL, s2=NULL, s3=NULL;
	AST *tq_ast=NULL, *s1_ast=NULL, *s2_ast=NULL, *s3_ast=NULL;
	int _signal=NoSignal;
	*_retsignal = NoSignal;
	AST *t_ast;
	AST *s_ast;
	int increment = 2;
	zzmatch_wsig(TOK_QUOTE, _handler);	
	if ( !guessing ) {
	 _t11 = (ANTLRTokenPtr)LT(1);
}
 labase++;
	 
	if ( !guessing ) {
		tq = _t11;
	}
	
	if ( !guessing ) {
	t_ast = (new AST( tq));
	}
 consume();
	{
		ANTLRTokenPtr _t21=NULL;
		AST *_ast21=NULL;
		if ( (LA(1)==TOK_STRING)
 ) {
			zzmatch_wsig(TOK_STRING, _handler);			
			if ( !guessing ) {
			 _t21 = (ANTLRTokenPtr)LT(1);
}
 labase++;
			if ( !guessing ) {
			
			_ast21 = new AST(_t21);
			_ast21->subchild(_root, &_sibling, &_tail);
			}
			
			if ( !guessing ) {
						s1 = _t21;
			s1_ast = _ast21;
			}
			
			if ( !guessing ) {
			s_ast = s1_ast;
			s_ast->setSegLength( strlen(s_ast->getAsciiText()) + increment );
			// s_ast->setOffset( t_ast->getOffset());
			}
 consume();
		}
		else {
			if ( (LA(1)==TOK_BADSTRING_NL) ) {
				zzmatch_wsig(TOK_BADSTRING_NL, _handler);				
				if ( !guessing ) {
				 _t21 = (ANTLRTokenPtr)LT(1);
}
 labase++;
				if ( !guessing ) {
				
				_ast21 = new AST(_t21);
				_ast21->subchild(_root, &_sibling, &_tail);
				}
				
				if ( !guessing ) {
								s2 = _t21;
				s2_ast = _ast21;
				}
				
				if ( !guessing ) {
				s_ast = s2_ast;
				increment = 1;  // add one for a single quote
				s2_ast->setType(TOK_STRING);
				s2_ast->setLine( s2_ast->getLine() - 1 );  // correct line number
				s_ast->setSegLength( strlen(s_ast->getAsciiText()) + increment );
				s_ast->setOffset( t_ast->getOffset() );
				AL_PARSE_ERR0( s2_ast, AL_GETMSG(ERR,316,0) )
				}
 consume();
			}
			else {
				if ( (LA(1)==TOK_BADSTRING_EOF) ) {
					zzmatch_wsig(TOK_BADSTRING_EOF, _handler);					
					if ( !guessing ) {
					 _t21 = (ANTLRTokenPtr)LT(1);
}
 labase++;
					if ( !guessing ) {
					
					_ast21 = new AST(_t21);
					_ast21->subchild(_root, &_sibling, &_tail);
					}
					
					if ( !guessing ) {
										s3 = _t21;
					s3_ast = _ast21;
					}
					
					if ( !guessing ) {
					s_ast = s3_ast;
					increment = 1;  // add one for a single quote
					s3_ast->setType(TOK_STRING);
					s_ast->setSegLength( strlen(s_ast->getAsciiText()) + increment );
					s_ast->setOffset( t_ast->getOffset() );
					AL_PARSE_ERR0( s3_ast, AL_GETMSG(ERR,316,0) )
					}
 consume();
				}
				else {
					if ( guessing ) goto fail;
					if (_sva) _signal=NoViableAlt;
					else _signal=NoSemViableAlt;
					goto _handler;  /* MR7 */
				}
			}
		}
	}
	if ( !guessing ) {
	
	delete t_ast;
	}
	return;
fail:
	if ( guessing ) zzGUESS_FAIL;
	syn(zzBadTok, "quoted string", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd13, 0x8);
_handler:
	zzdflthandlers(_signal,_retsignal);
	return;
}

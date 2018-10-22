/*
 * A n t l r  T r a n s l a t i o n  H e a d e r
 *
 * Terence Parr, Will Cohen, and Hank Dietz: 1989-1999
 * Purdue University Electrical Engineering
 * With AHPCRC, University of Minnesota
 * ANTLR Version 1.33MR21
 *
 *   /opt/PCCTS/v1.33_mr21_pre/bin_sol2/antlr -CC -gt -gs -k 2 -prc on -mrhoist on -gd calcex2.g
 *
 */

#define ANTLR_VERSION	13321
#include "pcctscfg.h"
#include "pccts_stdio.h"
#include "tokens.h"

#include "p_symtbl.hh"
#include "ASTBase.h"

#ifndef zzTRACE_RULES
#define zzTRACE_RULES
#endif  zzTRACE_RULES
#include "AParser.h"
#include "P.h"
#include "DLexerBase.h"
#include "ATokPtr.h"
#ifndef PURIFY
#define PURIFY(r,s) memset((char *) &(r),'\0',(s));
#endif

#include "myToken.h"
#include "myAST.h"
#include "mathAST.h"
#include "myPanic.h"
#include "myTokenBuffer.h"
#include "DLGLexer.h"

int main() {
	
	DLGFileInput		in(stdin);
	DLGLexer			lexer(&in,2000);
	MyTokenBuffer	pipe(&lexer,1);
	ANTLRToken		aToken( (ANTLRTokenType)0 );
	P				parser(&pipe);
	ASTBase *		root;
	AST *			rootCopy;
	
	root=(ASTBase *)0;
	
	lexer.setToken(&aToken);
	AST::clearList();		// remove statically constructed ASTs
	AST::clearCounter();
	parser.init();
	parser.statement(&root);
	rootCopy=(AST *) root;
	
	if (rootCopy != 0) {
		////     rootCopy->preorder();
		////     rootCopy->dumpTree();
		rootCopy->destroy();
	};
	////   AST::dumpList();
	
	AST::destroyList();
	
	fclose(stdin);
	fclose(stdout);
	return 0;
}

void
P::statement(ASTBase **_root)
{
	zzRULE;
	ASTBase *_ast = NULL, *_sibling = NULL, *_tail = NULL;
	ANTLRTokenPtr _t12=NULL;
	AST *_ast12=NULL;
	ANTLRTokenPtr e=NULL;
	AST *e_ast=NULL;
	zzTRACEIN("statement");
	{
		ANTLRTokenPtr _t22=NULL;
		AST *_ast21=NULL,*_ast22=NULL;
		while ( (LA(1)==Number || LA(1)==10) ) {
			_ast = NULL;
			expr1(&_ast);
			if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
			_ast21 = (AST *)_ast;
			ASTBase::link(_root, &_sibling, &_tail);
			e_ast = _ast21;
			
			printf("\n-----------------------------\n"
			"Result=%f\n",e_ast->eval());
			e_ast->dumpTree();
			zzmatch(NL); _t22 = (ANTLRTokenPtr)LT(1); labase++;
			
			_ast22 = new AST(_t22);
			_ast22->subchild(_root, &_sibling, &_tail);
			 consume();
		}
	}
	zzmatch(Eof); _t12 = (ANTLRTokenPtr)LT(1); labase++;
	
	_ast12 = new AST(_t12);
	_ast12->subchild(_root, &_sibling, &_tail);
	 consume();
	zzTRACEOUT("statement");
	return;
fail:
	syn(zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd1, 0x1);
	zzTRACEOUT("statement");
}

void
P::expr1(ASTBase **_root)
{
	zzRULE;
	ASTBase *_ast = NULL, *_sibling = NULL, *_tail = NULL;
	AST *_ast11=NULL;
	ANTLRTokenPtr a=NULL, b=NULL, c=NULL;
	AST *a_ast=NULL, *b_ast=NULL, *c_ast=NULL;
	zzTRACEIN("expr1");
	_ast = NULL;
	expr2(&_ast);
	_ast11 = (AST *)_ast;
	a_ast = _ast11;
	(*_root)=a_ast;
	{
		ANTLRTokenPtr _t21=NULL;
		AST *_ast21=NULL,*_ast22=NULL;
		for (;;) {
			if ( !((LA(1)==6 || 
LA(1)==7))) break;
			if ( (LA(1)==6) ) {
				zzmatch(6); _t21 = (ANTLRTokenPtr)LT(1); labase++;
				 consume();
				_ast = NULL;
				expr2(&_ast);
				_ast22 = (AST *)_ast;
				b_ast = _ast22;
				(*_root)=ASTBase::tmake(new Add,(*_root),b_ast, NULL);
			}
			else {
				if ( (LA(1)==7)
 ) {
					zzmatch(7); _t21 = (ANTLRTokenPtr)LT(1); labase++;
					 consume();
					_ast = NULL;
					expr2(&_ast);
					_ast22 = (AST *)_ast;
					c_ast = _ast22;
					(*_root)=ASTBase::tmake(new Sub,(*_root),c_ast, NULL);
				}
				else break; /* MR6 code for exiting loop "for sure" */
			}
		}
	}
	zzTRACEOUT("expr1");
	return;
fail:
	syn(zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd1, 0x2);
	zzTRACEOUT("expr1");
}

void
P::expr2(ASTBase **_root)
{
	zzRULE;
	ASTBase *_ast = NULL, *_sibling = NULL, *_tail = NULL;
	AST *_ast11=NULL;
	ANTLRTokenPtr a=NULL, b=NULL, c=NULL;
	AST *a_ast=NULL, *b_ast=NULL, *c_ast=NULL;
	zzTRACEIN("expr2");
	_ast = NULL;
	expr3(&_ast);
	_ast11 = (AST *)_ast;
	a_ast = _ast11;
	(*_root)=a_ast;
	{
		ANTLRTokenPtr _t21=NULL;
		AST *_ast21=NULL,*_ast22=NULL;
		for (;;) {
			if ( !((LA(1)==8 || LA(1)==9))) break;
			if ( (LA(1)==8)
 ) {
				zzmatch(8); _t21 = (ANTLRTokenPtr)LT(1); labase++;
				 consume();
				_ast = NULL;
				expr3(&_ast);
				_ast22 = (AST *)_ast;
				b_ast = _ast22;
				(*_root)=ASTBase::tmake(new Mul,(*_root),b_ast, NULL);
			}
			else {
				if ( (LA(1)==9) ) {
					zzmatch(9); _t21 = (ANTLRTokenPtr)LT(1); labase++;
					 consume();
					_ast = NULL;
					expr3(&_ast);
					_ast22 = (AST *)_ast;
					c_ast = _ast22;
					(*_root)=ASTBase::tmake(new Div,(*_root),c_ast, NULL);
				}
				else break; /* MR6 code for exiting loop "for sure" */
			}
		}
	}
	zzTRACEOUT("expr2");
	return;
fail:
	syn(zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd1, 0x4);
	zzTRACEOUT("expr2");
}

void
P::expr3(ASTBase **_root)
{
	zzRULE;
	ASTBase *_ast = NULL, *_sibling = NULL, *_tail = NULL;
	ANTLRTokenPtr _t11=NULL,_t13=NULL;
	AST *_ast11=NULL,*_ast12=NULL,*_ast13=NULL;
	ANTLRTokenPtr n=NULL;
	AST *n_ast=NULL;
	zzTRACEIN("expr3");
	if ( (LA(1)==Number) ) {
		zzmatch(Number); _t11 = (ANTLRTokenPtr)LT(1); labase++;
		
		_ast11 = new AST(_t11);
		_ast11->subchild(_root, &_sibling, &_tail);
		
		n = _t11;
		n_ast = _ast11;
 consume();
	}
	else {
		if ( (
LA(1)==10) ) {
			zzmatch(10); _t11 = (ANTLRTokenPtr)LT(1); labase++;
			  consume();
			_ast = NULL;
			expr1(&_ast);
			if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
			_ast12 = (AST *)_ast;
			ASTBase::link(_root, &_sibling, &_tail);
			zzmatch(11); _t13 = (ANTLRTokenPtr)LT(1); labase++;
			  consume();
		}
		else {FAIL(1,err1,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
	}
	zzTRACEOUT("expr3");
	return;
fail:
	syn(zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd1, 0x8);
	zzTRACEOUT("expr3");
}

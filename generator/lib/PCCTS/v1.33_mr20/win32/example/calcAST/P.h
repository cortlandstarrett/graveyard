/*
 * P: P a r s e r  H e a d e r 
 *
 * Generated from: calcex2.g
 *
 * Terence Parr, Russell Quong, Will Cohen, and Hank Dietz: 1989-1999
 * Parr Research Corporation
 * with Purdue University Electrical Engineering
 * with AHPCRC, University of Minnesota
 * ANTLR Version 1.33MR21
 */

#ifndef P_h
#define P_h

#ifndef ANTLR_VERSION
#define ANTLR_VERSION 13321
#endif

class ASTBase;
#ifndef zzTRACE_RULES
#define zzTRACE_RULES
#endif  zzTRACE_RULES
#include "AParser.h"


#include "p_symtbl.hh"
class P : public ANTLRParser {
public:
	static  const ANTLRChar *tokenName(int tk);
protected:
	static  const ANTLRChar *_token_tbl[];
	enum { SET_SIZE = 12 };
private:

public:
virtual void syn(
ANTLRAbstractToken *	tok,
ANTLRChar *		egroup,
SetWordType *		eset,
ANTLRTokenType		etok,
int			k);
protected:
	static SetWordType err1[4];
	static SetWordType setwd1[12];
private:
	void zzdflthandlers( int _signal, int *_retsignal );

public:
	P(ANTLRTokenBuffer *input);
	void statement(ASTBase **_root);
	void expr1(ASTBase **_root);
	void expr2(ASTBase **_root);
	void expr3(ASTBase **_root);
};

#endif /* P_h */


/* parser.dlg -- DLG Description of scanner
 *
 * Generated from: calcex2.g
 *
 * Terence Parr, Will Cohen, and Hank Dietz: 1989-1999
 * Purdue University Electrical Engineering
 * With AHPCRC, University of Minnesota
 * ANTLR Version 1.33MR21
 */

#define ANTLR_VERSION	13321
#include "tokens.h"
#include "AToken.h"
#include "ASTBase.h"

#include "p_symtbl.hh"
/*
 * D L G tables
 *
 * Generated from: parser.dlg
 *
 * 1989-1999 by  Will Cohen, Terence Parr, and Hank Dietz
 * Purdue University Electrical Engineering
 * DLG Version 1.33MR21
 */

#include "pcctscfg.h"
#include "pccts_stdio.h"

#include "AParser.h"
#include "DLexerBase.h"
#include "DLGLexer.h"

ANTLRTokenType DLGLexer::act1()
{ 
		return Eof;
	}


ANTLRTokenType DLGLexer::act2()
{ 
		double	d;
		char *	endptr;
		d=strtod(_lextext,&endptr);
		if (*endptr != 0) {
			return InvalidNumber;
		};
		return Number;
	}


ANTLRTokenType DLGLexer::act3()
{ 
		skip();
		if (*_lextext=='\t') {
			_endcol=((_endcol-1) & ~7) + 8;
			// DLG will add 1 more because it
			//   assumes \t is a printing character
			// See wstabadjust.cpp for ws strings
		};
		return WS;
	}


ANTLRTokenType DLGLexer::act4()
{ 
		newline();set_endcol(0);  
		return NL;
	}


ANTLRTokenType DLGLexer::act5()
{ 
		return (ANTLRTokenType)6;
	}


ANTLRTokenType DLGLexer::act6()
{ 
		return (ANTLRTokenType)7;
	}


ANTLRTokenType DLGLexer::act7()
{ 
		return (ANTLRTokenType)8;
	}


ANTLRTokenType DLGLexer::act8()
{ 
		return (ANTLRTokenType)9;
	}


ANTLRTokenType DLGLexer::act9()
{ 
		return (ANTLRTokenType)10;
	}


ANTLRTokenType DLGLexer::act10()
{ 
		return (ANTLRTokenType)11;
	}

 unsigned char DLGLexer::shift0[257] = {
  0, 12, 12, 12, 12, 12, 12, 12, 12, 12, 
  6, 7, 12, 12, 12, 12, 12, 12, 12, 12, 
  12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 
  12, 12, 12, 6, 12, 12, 12, 12, 12, 12, 
  12, 10, 11, 8, 4, 12, 5, 2, 9, 1, 
  1, 1, 1, 1, 1, 1, 1, 1, 1, 12, 
  12, 12, 12, 12, 12, 12, 12, 12, 12, 3, 
  3, 3, 12, 12, 12, 12, 12, 3, 12, 12, 
  12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 
  12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 
  12, 3, 3, 3, 12, 12, 12, 12, 12, 3, 
  12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 
  12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 
  12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 
  12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 
  12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 
  12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 
  12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 
  12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 
  12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 
  12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 
  12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 
  12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 
  12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 
  12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 
  12, 12, 12, 12, 12, 12, 12
};


const int DLGLexer::MAX_MODE=1;
const int DLGLexer::DfaStates=15;
const int DLGLexer::START=0;

DLGLexer::DfaState DLGLexer::st0[13] = {
  1, 2, 2, 15, 3, 4, 5, 6, 7, 8, 
  9, 10, 15
};

DLGLexer::DfaState DLGLexer::st1[13] = {
  15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 
  15, 15, 15
};

DLGLexer::DfaState DLGLexer::st2[13] = {
  15, 2, 2, 11, 15, 15, 15, 15, 15, 15, 
  15, 15, 15
};

DLGLexer::DfaState DLGLexer::st3[13] = {
  15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 
  15, 15, 15
};

DLGLexer::DfaState DLGLexer::st4[13] = {
  15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 
  15, 15, 15
};

DLGLexer::DfaState DLGLexer::st5[13] = {
  15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 
  15, 15, 15
};

DLGLexer::DfaState DLGLexer::st6[13] = {
  15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 
  15, 15, 15
};

DLGLexer::DfaState DLGLexer::st7[13] = {
  15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 
  15, 15, 15
};

DLGLexer::DfaState DLGLexer::st8[13] = {
  15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 
  15, 15, 15
};

DLGLexer::DfaState DLGLexer::st9[13] = {
  15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 
  15, 15, 15
};

DLGLexer::DfaState DLGLexer::st10[13] = {
  15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 
  15, 15, 15
};

DLGLexer::DfaState DLGLexer::st11[13] = {
  15, 12, 15, 15, 13, 15, 15, 15, 15, 15, 
  15, 15, 15
};

DLGLexer::DfaState DLGLexer::st12[13] = {
  15, 12, 15, 15, 15, 15, 15, 15, 15, 15, 
  15, 15, 15
};

DLGLexer::DfaState DLGLexer::st13[13] = {
  15, 15, 15, 15, 15, 14, 15, 15, 15, 15, 
  15, 15, 15
};

DLGLexer::DfaState DLGLexer::st14[13] = {
  15, 12, 15, 15, 15, 15, 15, 15, 15, 15, 
  15, 15, 15
};


DLGLexer::DfaState *DLGLexer::dfa[15] = {
	st0,
	st1,
	st2,
	st3,
	st4,
	st5,
	st6,
	st7,
	st8,
	st9,
	st10,
	st11,
	st12,
	st13,
	st14
};


DLGLexer::DfaState DLGLexer::accepts[16] = {
  0, 1, 2, 5, 6, 3, 4, 7, 8, 9, 
  10, 0, 2, 0, 0, 0
};

PtrDLGLexerMemberFunc DLGLexer::actions[11] = {
	&DLGLexer::erraction,
	&DLGLexer::act1,
	&DLGLexer::act2,
	&DLGLexer::act3,
	&DLGLexer::act4,
	&DLGLexer::act5,
	&DLGLexer::act6,
	&DLGLexer::act7,
	&DLGLexer::act8,
	&DLGLexer::act9,
	&DLGLexer::act10
};

DLGLexer::DfaState DLGLexer::dfa_base[] = {
	0
};

 unsigned char *DLGLexer::b_class_no[] = {
	shift0
};

DLGChar DLGLexer::alternatives[DLGLexer::DfaStates+1] = {
	1,
	0,
	1,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	1,
	1,
	1,
	1,
/* must have 0 for zzalternatives[DfaStates] */
	0
};

#include "DLexer.cpp"

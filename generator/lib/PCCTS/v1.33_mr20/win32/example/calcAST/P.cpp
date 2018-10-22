/*
 * P: P a r s e r  S u p p o r t
 *
 * Generated from: calcex2.g
 *
 * Terence Parr, Russell Quong, Will Cohen, and Hank Dietz: 1989-1999
 * Parr Research Corporation
 * with Purdue University Electrical Engineering
 * with AHPCRC, University of Minnesota
 * ANTLR Version 1.33MR21
 */

#define ANTLR_VERSION	13321
#include "pcctscfg.h"
#include "pccts_stdio.h"
#define ANTLR_SUPPORT_CODE
#include "tokens.h"
#include "P.h"

const ANTLRChar *P::tokenName(int tok)   { return _token_tbl[tok]; }

const ANTLRChar *P::_token_tbl[]={
	/* 00 */	"Invalid",
	/* 01 */	"Eof",
	/* 02 */	"InvalidNumber",
	/* 03 */	"Number",
	/* 04 */	"WS",
	/* 05 */	"NL",
	/* 06 */	"\\+",
	/* 07 */	"\\-",
	/* 08 */	"\\*",
	/* 09 */	"\\/",
	/* 10 */	"\\(",
	/* 11 */	"\\)"
};

P::P(ANTLRTokenBuffer *input) : ANTLRParser(input,2,0,0,4)
{
	token_tbl = _token_tbl;
	traceOptionValueDefault=1;		// MR10 turn trace ON
}

SetWordType P::err1[4] = {0x8,0x4,0x0,0x0};
SetWordType P::setwd1[12] = {0x0,0x1,0x0,0x0,0x0,0xe,0xc,
	0xc,0x8,0x8,0x0,0xe};

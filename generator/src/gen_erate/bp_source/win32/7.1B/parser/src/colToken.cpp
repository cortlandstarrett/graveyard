/*========================================================================
 *
 * File:      $RCSfile: colToken.cpp,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:20 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
/*  This file should be accompanied by DISCLAIMER.TXT stating disclaimers */

#include "noleakTok.h"
#include "colToken.h"
#include "string.h"
#include <stdio.h>
#include "P.h"

long int ColToken::accumulated_offset = 0;

void ColToken::init() {
  pText=0;
  byte_offset = 0;
}

ColToken::ColToken() {
  init();
  setLine(0);
}

ColToken::~ColToken() {
   delete [] pText;
   pText=0;
}

ColToken::ColToken(ANTLRTokenType tokenTypeNew) {
   init();
   setType(tokenTypeNew);
   setLine(0);
}

ColToken::ColToken(ANTLRTokenType 	tokenTypeNew,
		   ANTLRChar *		textNew,   
		   int			lineNew) {
   init();
   setType(tokenTypeNew);
   setLine(lineNew);
   setText(textNew);
}         

ColToken::ColToken(const ColToken & from) :
	NoLeakToken(from) 
{
   init();
   col=from.col;
   byte_offset=from.byte_offset;
   setText(from.pText);
};	

//  create new copy of text - not just another reference to existing text

ColToken & ColToken::operator = (const ColToken & from) {

   this->NoLeakToken::operator = (from);

   if (this != &from) {
     col=from.col;
     byte_offset=from.byte_offset;
     setText(from.pText);
   };
   return *this;
}      

//  create new copy of text - not just another reference to existing text

void ColToken::setText(const ANTLRChar *s) {

   if (pText != 0) {
      delete [] pText;
      pText=0;
   };
   if (s != 0) {
     pText=new char [strlen(s)+1];
     if (pText == 0) panic ("ColToken::setText strdup failed");
     strcpy(pText,s);
   };
}

ANTLRAbstractToken * ColToken::makeToken(ANTLRTokenType		tokenType,
					 ANTLRChar *		text,
					 int			line) {
   return new ColToken(tokenType,text,line);
}

void ColToken::dumpNode(const char * s) {

   char * theText;

   if (s != 0) {printf("%s ",s);};
   if (getType() == Eof) {
     printf("TokenType \"EOF\" Token # %d\n",serial);
   } else {
     if (pText == 0) {
        theText="";
     } else if (strcmp(pText,"\n") == 0) {
	theText="NL";
     } else {
	theText=pText;
     };	
     printf("TokenType (%s) Text (%s) Token # %d  Line=%d  Col=%d\n",
		P::tokenName(getType()),
		theText,
		serial,		
		getLine(),
		col);
   };
}

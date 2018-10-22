/*========================================================================
 *
 * File:      $RCSfile: myTokenBuffer.cpp,v $
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
/*  This file should be accompanied by DISCLAIMER.TXT stating disclaimers */

#include "myToken.h"
#include "myTokenBuffer.h"
#include "DLexerBase.h"

MyTokenBuffer::MyTokenBuffer(ANTLRTokenStream * in,
			     int		kx,
			     int		chksz) :
   ANTLRTokenBuffer(in,kx,chksz) {

   ( (DLGLexerBase *)input )->trackColumns();
}

ANTLRAbstractToken * MyTokenBuffer::getANTLRToken() {

   ANTLRToken *		myToken;
   int current_accumulated_offset = ColToken::accumulated_offset;
   myToken=(ANTLRToken *)ANTLRTokenBuffer::getANTLRToken();
   myToken->col=( (DLGLexerBase *)input ) ->begcol();

   if ( myToken->getType() == TOK_BADPHRASE_NL ||
        myToken->getType() == TOK_BADPHRASE_EOF )
   {
       // yes, this is a horrible way to do things, but changing the
       //  parser grammar would be even riskier at this time (6.0 beta)

       // The resynch() logic has parsed ahead to the next semicolon, so
       // the accumulated_offset is way wrong.  We need to use the value we 
       // saved at the beginning of this function.

       int save_ao = ColToken::accumulated_offset;
       ColToken::accumulated_offset = current_accumulated_offset;
       myToken->setByteOffset();    // Set byte offset after setting up column.
       ColToken::accumulated_offset = save_ao;
   }
   else
   {
       myToken->setByteOffset();    // Set byte offset after setting up column.
   }
   return myToken;
}

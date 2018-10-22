/*========================================================================
 *
 * File:      $RCSfile: myTokenBuffer.h,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:31 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#ifndef MYTOKENBUFFER_H
#define MYTOKENBUFFER_H

/*  This file should be accompanied by DISCLAIMER.TXT stating disclaimers */

#include "tokens.h"
#include "ATokenBuffer.h"

struct MyTokenBuffer : ANTLRTokenBuffer {
   
   /* constructor */		MyTokenBuffer(
					ANTLRTokenStream *in,
					int k=1,
					int chksz=200);
   virtual /* destructor */	~MyTokenBuffer() {};
   virtual ANTLRAbstractToken *	getANTLRToken();
   void panic ( const char *msg )
      { throw msg; }

}; 

#endif

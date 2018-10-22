/*========================================================================
 *
 * File:      $RCSfile: myPanic.cpp,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:21 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
/*  This file should be accompanied by DISCLAIMER.TXT stating disclaimers */

#include <stdio.h>
#include <stdlib.h>

void myPanic(const char * s) {
   printf ("\nPanic: %s\n",s);
   exit(1);
};

/*========================================================================
 *
 * File:      $RCSfile: dbdump.h,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:53 $
 *
 * (c) Copyright 2005-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#ifndef INCLUDED_DBDMP
#define INCLUDED_DBDMP

// This is from Galaxy it used to hold strings.
class Description;

void dump_data(char* fileName = 0, const Description& des = "");

#endif

/*========================================================================
 *
 * File:      $RCSfile: u_init.cc,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:58 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#include <mc_dbms/mc_dbms.hh>

#include "u_typdef.hh"


#include "u_string.hh"
#include "u_tspec.hh"



//
// FUNCTION: DBU_init
//
// PURPOSE:
//
//		Calls any DBU class initialization functions.
//
// REMARKS:
//
//		None.
//

void
DBU_init()
{

Ordered_string::init();

}

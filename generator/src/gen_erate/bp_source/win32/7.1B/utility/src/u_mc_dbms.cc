/*========================================================================
 *
 * File:      $RCSfile: u_mc_dbms.cc,v $
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

#include <u_mc_dbms.hh>


int MCDBMSInit::_initialized = 0;
int MCDBMSInit::_ok_to_initialize = 0;


void MCDBMSInit::start_initialization(const char *app_name)
{
   _ok_to_initialize = 1;

  if ( !_initialized && _ok_to_initialize )
  {
	  _initialized = 1;
  }
}

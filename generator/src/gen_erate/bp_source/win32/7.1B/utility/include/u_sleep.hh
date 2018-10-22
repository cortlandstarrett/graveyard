/*========================================================================
 *
 * File:      $RCSfile: u_sleep.hh,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:34 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#ifndef U_SLEEP_HH
#define U_SLEEP_HH

#ifdef WIN32
#include <windows.h>
#define sleep(n) Sleep(n*1000)
#else
  // sleep() is defined in <unistd.h>
#endif

#endif

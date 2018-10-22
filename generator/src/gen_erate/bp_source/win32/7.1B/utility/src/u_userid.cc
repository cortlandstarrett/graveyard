/*========================================================================
 *
 * File:      $RCSfile: u_userid.cc,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:59 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
// This file is only needed by Windows NT/95

#ifdef WIN32

#include <windows.h>
#include <u_userid.hh>

#define L_cuserid 32

const char *get_userid()
{
  static char userid[L_cuserid + 1];
  char *userid_ptr = &userid[0];

  strcpy ( userid_ptr, "UNKNOWN_USER" );

  DWORD bufferSize = L_cuserid;
  DWORD result = WNetGetUser( 0, userid, &bufferSize );
  if ( result != NO_ERROR )
	{
      strcpy ( userid_ptr, "UNKNOWN_USER" );
	}

  return userid_ptr;
}

#else

#include <vstdio.h>
#include <vstring.h>

#ifdef L_cuserid
#undef L_cuserid
#endif
#define L_cuserid 32

const char *get_userid()
{
	static char userid[L_cuserid + 1];
    char *userid_ptr = &userid[0];

	strcpy ( userid_ptr, "UNKNOWN_USER" );

    // This form is required on HP-UX because cuserid(0) returns 0!
    cuserid (userid_ptr);

	return userid_ptr;
}


#endif

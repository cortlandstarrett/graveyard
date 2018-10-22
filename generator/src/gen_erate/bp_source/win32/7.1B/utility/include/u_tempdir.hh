/*========================================================================
 *
 * File:      $RCSfile: u_tempdir.hh,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:33 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#ifndef U_TEMPDIR_HH
#define U_TEMPDIR_HH

#ifdef WIN32

#include <windows.h>

const char * U_get_temp_dir()
{ 
    DWORD pathSize;
	static char pathBuffer[MAX_PATH];
	pathSize = GetTempPath(sizeof(pathBuffer), pathBuffer);
	if ( pathSize < sizeof(pathBuffer) )
	  pathBuffer[pathSize] = 0;
	else
	  pathBuffer[0] = 0;
	
	return pathBuffer;
}

#else

const char * U_get_temp_dir()
{ 
	return "/tmp/";
}

#endif

#endif

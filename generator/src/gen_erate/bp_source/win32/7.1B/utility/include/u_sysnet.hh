/*========================================================================
 *
 * File:      $RCSfile: u_sysnet.hh,v $
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
#ifndef U_SYSNET_HH
#define U_SYSNET_HH

#ifdef WIN32
  #include <windows.h>

// gethostname returns zero (FALSE) on success
// GetComputerName returns a non-zero on success

// we need to name this function something different
// so it won't collide with the winsock declaration.

static inline int my_gethostname(char *name, int namelen)
{
   DWORD var_yy = namelen;
   return !GetComputerName(name, &var_yy);
}

  #include <process.h>
  #define getpid _getpid

#else 

#ifndef HPUX
extern "C"
{
    int gethostname (char*, int);
}
#endif

#define my_gethostname(xx,yy) gethostname(xx,yy)

#endif

#endif

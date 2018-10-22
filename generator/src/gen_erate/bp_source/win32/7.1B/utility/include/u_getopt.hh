/*========================================================================
 *
 * File:      $RCSfile: u_getopt.hh,v $
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
#ifndef U_GETOPT_HH
#define U_GETOPT_HH

#ifdef WIN32

int getopt( int argc, char * const *argv, const char *optstring );
extern char*	optarg;
extern int		optind;
extern int		opterr;
extern int    optopt;

#else

// Under sol2, the function getopt() is defined in stdlib.h

#endif

#endif

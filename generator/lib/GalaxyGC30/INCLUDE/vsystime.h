/* $Id: vsystime.h,v 1.4 1994/09/28 03:15:22 abstine Exp $ */

#ifndef vsystimeINCLUDED
#define vsystimeINCLUDED 1

/*
	+---------------------------------------------------------------+
	|								|
	|	     vsystime.h - Visix sys/time & sys/times Header	|
	|	     ========================================		|
	|								|
	+---------------------------------------------------------------+
	|								|
	| (c) Copyright 1991, Visix Software, Inc., All rights reserved.|
	|								|
	+---------------------------------------------------------------+
	|								|
	|			   DESCRIPTION				|
	|			   ===========				|
	|								|
	|	This file is intended to replace sys/time.h and		|
	|	sys/times.h with the "Right Thing".  To use this file,	|
	|	replace any instances of #include <sys/time.h> or	|
	|	#include <sys/times.h> with				|
	|	#include vsystimeHEADER.				|
	|								|
	|	This file is meant to conform to the POSIX standard	|
	|	specification for sys/times.h.				|
	|								|
	+---------------------------------------------------------------+
*/


/*
 * Include any other files this header depends upon
 */

#ifndef   vportINCLUDED
#include <vport.h>
#endif


/*
 * Include the system version of sys/time.h, if its not too bad
 */

vportBEGIN_CPLUSPLUS_HEADER_PROTECTION

#if ( ! vportBAD_SYS_TIME_HDR )
#include <sys/time.h>
#endif

#if ( ! vportBAD_SYS_TIMES_HDR )
#include <sys/times.h>
#endif


/*
 * Fix up anything wrong with the system version
 */

#if (vportNEED_BSD_SYS_TIME_HDR)
#include <bsd/sys/time.h>
#endif

#if (vportTIMEVAL_IN_SOCKET_HDR)
#include <socket.h>
#endif

vportEND_CPLUSPLUS_HEADER_PROTECTION


vportBEGIN_CPLUSPLUS_EXTERN_C

#if (vportNEED_TIMEZONE_STRUCT)
struct timezone {
        int     tz_minuteswest; /* minutes west of Greenwich */
        int     tz_dsttime;     /* type of dst correction */
      };
#endif

#if (vportNEED_GETTIMEOFDAY_PROTO)
int	 gettimeofday( struct timeval *, struct timezone * );
#endif

vportEND_CPLUSPLUS_EXTERN_C


#endif /* vsystimeINCLUDED */


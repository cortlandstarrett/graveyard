/* $Id: vsystypes.h,v 1.4 1994/11/28 20:54:40 chad Exp $ */

#ifndef vsystypesINCLUDED
#define vsystypesINCLUDED 1

/*
	+---------------------------------------------------------------+
	|								|
	|	     vsystypes.h - Visix Sys/Types Header		|
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
	|	This file is intended to replace sys/types.h with	|
	|	the "Right Thing".  To use this file, replace any	|
	|	instances of #include <sys/types.h> with		|
	|	#include <vsystypes.h>.					|
	|								|
	|	This file is meant to conform to the POSIX standard	|
	|	specification for sys/types.h.				|
	|								|
	+---------------------------------------------------------------+
*/


/*
 * Include any other files this header depends upon
 */

#ifndef  vportINCLUDED		/* for v*HEADER */
#include <vport.h>
#endif

#ifndef  vstddefINCLUDED	/* real home of size_t, ptrdiff_t */
#include vstddefHEADER
#endif


/*
 * Include the system version of sys/types.h, if its not too bad
 */

vportBEGIN_CPLUSPLUS_HEADER_PROTECTION

#if ( ! vportBAD_SYS_TYPES_HDR )
#include <sys/types.h>
#else
#if ( ! vportBAD_BSD_SYS_TYPES_HDR )
#include <bsd/sys/types.h>
#else
#if ( ! vportBAD_TYPES_HDR )
#include <types.h>
#endif
#endif
#endif

#if ( vportNEED_TYPES_HDR )
#if ( ! vportBAD_TYPES_HDR )
#include <types.h>
#endif
#endif

vportEND_CPLUSPLUS_HEADER_PROTECTION


/*
 * Fix up anything that may have been wrong
 */

vportBEGIN_CPLUSPLUS_EXTERN_C

#ifndef NBBY
#define NBBY 8
#endif

#if (vportNEED_USHORT_TYPE)
typedef unsigned short ushort;
#endif

#if (vportNEED_CADDR_T_TYPE)
typedef char *caddr_t;
#endif

#if (vportNEED_SSIZE_T_TYPE)
typedef long ssize_t;
#endif

#if (vportNEED_PID_T_TYPE)
typedef int pid_t;
#endif

#if (vportNEED_MODE_T_TYPE)
typedef unsigned short mode_t;
#endif

#if (vportNEED_UID_T_TYPE)
typedef int uid_t;
#endif

#if (vportNEED_GID_T_TYPE)
typedef int gid_t;
#endif

#if (vportNEED_BZERO_PROTO)
void bzero(char *, int);
#endif

vportEND_CPLUSPLUS_EXTERN_C


#endif /* #ifndef vsystypesINCLUDED */


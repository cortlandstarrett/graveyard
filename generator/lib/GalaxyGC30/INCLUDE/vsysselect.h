/* $Id: vsysselect.h,v 1.8 1997/09/02 15:31:32 gregt Exp $ */

#ifndef	vsysselectINCLUDED
#define vsysselectINCLUDED 1

/*
	+---------------------------------------------------------------+
	|								|
	|	     vsysselect.h - Visix Sys/Select Header		|
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
	|	This file is intended to replace sys/select.h with	|
	|	the "Right Thing".  To use this file, replace any	|
	|	instances of #include <sys/select.h> with		|
	|	#include <vsysselect.h>.				|
	|								|
	|	This file is meant to conform to the BSD43 standard	|
	|	specification for sys/select.h.				|
	|								|
	+---------------------------------------------------------------+
*/


/*
 * Include any other files this header depends upon
 */

#ifndef  vportINCLUDED		/* for v*HEADER */
#include <vport.h>
#endif

#ifndef  vsystimeINCLUDED
#include vsystimeHEADER
#endif

#ifndef  vsystypesINCLUDED	/* for struct timeval */
#include vsystypesHEADER
#endif

#ifndef  vulimitINCLUDED
#include vulimitHEADER
#endif

#ifndef  vlibcINCLUDED		/* some systems have a generic libc.h */
#include vlibcHEADER
#endif


/*
 * Include the system version of sys/select.h, if its not too bad
 */

vportBEGIN_CPLUSPLUS_HEADER_PROTECTION

#if (vportNEED_BSTRING_HDR)	/* for bzero() */
#include <bstring.h>
#endif

#if (vportOS_UNIX_AIX)	/* for bzero() */
#include <strings.h>
#endif

#if ( ! vportBAD_SYS_SELECT_HDR )
#include <sys/select.h>
#endif

vportEND_CPLUSPLUS_HEADER_PROTECTION


/*
 * Fix up anything that may have been wrong
 */

vportBEGIN_CPLUSPLUS_EXTERN_C

#if (vportNEED_SELECT_PROTO)
int	 select( int, vportFD_SET_CAST, vportFD_SET_CAST, vportFD_SET_CAST, struct timeval * );
#endif

#if (vportNEED_GETDTABLESIZE_PROTO)
int	 getdtablesize( void );
#endif

#if (vportBAD_GETDTABLESIZE)
#ifdef NOFILE
#define getdtablesize()			NOFILE
#else
#if (!vportBAD_ULIMIT)
#define getdtablesize()			ulimit(4,0)
#else
#if (!vportBAD_SYSCONF)
#define getdtablesize()			sysconf(_SC_OPEN_MAX)
#else
#define getdtablesize()			(64)
#endif
#endif
#endif
#endif

vportEND_CPLUSPLUS_EXTERN_C


#endif /* vsysselectINCLUDED */


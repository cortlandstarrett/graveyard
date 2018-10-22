/* $Id: vtime.h,v 1.10 1993/09/05 23:36:56 chad Exp $ */

#ifndef vtimeINCLUDED
#define vtimeINCLUDED 1

/*
	+---------------------------------------------------------------+
	|								|
	|	     vtime.h - Visix Time Header			|
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
	|	This file is intended to replace time.h with		|
	|	the "Right Thing" as defined by ANSI C.			|
	|								|
	+---------------------------------------------------------------+
*/


/*
 * Include any files this header depends upon
 */

#ifndef vportINCLUDED
#include <vport.h>
#endif


/*
 * Include the system version of time.h, if its not too bad
 */

vportBEGIN_CPLUSPLUS_HEADER_PROTECTION

#if (! vportBAD_TIME_HDR)
#include <time.h>
#endif

vportEND_CPLUSPLUS_HEADER_PROTECTION


/*
 * Fix up any problems there may have been in the included system time.h
 */



/*
 * some non-ANSI systems don't define time_t in time.h,
 * but in sys/types.h instead.
 */
#ifndef  vsystypesINCLUDED
#include vsystypesHEADER
#endif


vportBEGIN_CPLUSPLUS_EXTERN_C

#if (vportNEED_MKTIME_PROTO)
time_t mktime( struct tm * );
#endif

#if (vportNEED_STRFTIME_PROTO)
size_t strftime( char *, size_t, const char *, const struct tm * );
#endif

#if (vportNEED_STRPTIME_PROTO)
char *strptime(char *, char *, struct tm *);
#endif

#if (vportNEED_TIME_PROTO)
time_t time( time_t *tod );
#endif

#if (vportNEED_CLOCKS_PER_SEC)
#define CLOCKS_PER_SEC 1000000
#endif

#if (vportNEED_CLOCK_PROTO)
clock_t clock( void );
#endif

vportEND_CPLUSPLUS_EXTERN_C


/*
 * * * * * * * * * * * * * * * * Miscellaneous * * * * * * * * * * * * * * * *
 */

/*
 * Formatting information for emacs in c-mode
 *
 * Local Variables:
 * c-indent-level:4
 * c-continued-statement-offset:2
 * c-brace-offset:-2
 * c-brace-imaginary-offset:0
 * c-argdecl-indent:4
 * c-label-offset:-2
 * End:
 */


#endif /* vtimeINCLUDED */


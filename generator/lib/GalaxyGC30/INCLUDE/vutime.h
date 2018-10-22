/* $Id: vutime.h,v 1.6 1993/09/05 23:36:56 chad Exp $ */

#ifndef vutimeINCLUDED
#define vutimeINCLUDED 1


/*
	+---------------------------------------------------------------+
	|								|
	|	     vutime.h - Visix Utime Header			|
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
	|	This file is intended to replace utime.h with		|
	|	the "Right Thing", as defined by POSIX.			|
	|								|
	+---------------------------------------------------------------+
*/


/*
 * Include any other files this header depends upon
 */

#ifndef vportINCLUDED
#include <vport.h>
#endif


/*
 * Include the system version of utime.h, if its not too bad
 */

vportBEGIN_CPLUSPLUS_HEADER_PROTECTION

#if ( ! vportBAD_UTIME_HDR )
#include <utime.h>
#else
#if ( ! vportBAD_SYS_UTIME_HDR )
#include <sys/utime.h>
#endif
#endif

vportEND_CPLUSPLUS_HEADER_PROTECTION


/*
 * Fix up anything that may have been wrong
 */


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

#endif /* vutimeINCLUDED */


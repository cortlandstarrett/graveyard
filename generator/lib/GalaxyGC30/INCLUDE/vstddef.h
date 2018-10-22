/* $Id: vstddef.h,v 1.9 1996/05/14 12:48:00 chad Exp $ */

#ifndef vstddefINCLUDED
#define vstddefINCLUDED 1

/*
	+---------------------------------------------------------------+
	|								|
	|	     vstddef.h - Visix Stddef Header			|
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
	|	This file is intended to supplant stddef.h with		|
	|	the "Right Thing" as defined bby ANSI C.		|
	|								|
	+---------------------------------------------------------------+
*/


/*
 * Include any other files this header depends upon
 */

#ifndef  vportINCLUDED
#include <vport.h>		/* for vport* */
#endif

/*
 * Include the system version of stddef.h, if its not too bad
 */

vportBEGIN_CPLUSPLUS_HEADER_PROTECTION

#if ( ! vportBAD_STDDEF_HDR )
#include <stddef.h>
#endif

vportEND_CPLUSPLUS_HEADER_PROTECTION


/*
 * Fix up anything that may have been wrong
 */

#ifndef NULL			/* ANSI defines NULL in several places	*/
#define NULL	0
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C

#if (vportBAD_SIZE_T)
#define size_t			unsigned long
#endif

#if (vportNEED_SIZE_T_TYPE)
typedef unsigned long	size_t;
#endif

#ifndef offsetof
#define offsetof(type,id)	(size_t) (((char *) &(((type *) NULL)->id)) - ((char *) NULL) )
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


#endif /* vstddefINCLUDED */


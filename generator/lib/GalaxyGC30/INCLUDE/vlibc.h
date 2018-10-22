/* $Id: vlibc.h,v 1.2 1993/09/05 23:36:56 chad Exp $ */

#ifndef vlibcINCLUDED
#define vlibcINCLUDED 1

/*
	+---------------------------------------------------------------+
	|								|
	|	     vlibc.h - Visix Libc Header			|
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
	|	This file is intended to replace libc.h with		|
	|	the "Right Thing".					|
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
 * Include the system version of libc.h, if its not too bad
 */

vportBEGIN_CPLUSPLUS_HEADER_PROTECTION

#if ( ! vportBAD_LIBC_HDR )
#include <libc.h>
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


#endif /* vlibcINCLUDED */


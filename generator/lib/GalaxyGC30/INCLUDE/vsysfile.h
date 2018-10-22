/* $Id: vsysfile.h,v 1.2 1993/09/05 23:34:28 chad Exp $ */

#ifndef vsysfileINCLUDED
#define vsysfileINCLUDED 1


/*
	+---------------------------------------------------------------+
	|								|
	|	     vsysfile.h - Visix Sys/File Header			|
	|	     ========================================		|
	|								|
	+---------------------------------------------------------------+
	|								|
	| (c) Copyright 1990, Visix Software, Inc., All rights reserved.|
	|								|
	+---------------------------------------------------------------+
	|								|
	|			   DESCRIPTION				|
	|			   ===========				|
	|								|
	|	This file is intended to replace sys/file.h with	|
	|	the "Right Thing".  To use this file, replace any	|
	|	instances of #include <sys/file.h> with			|
	|	#include <vsys/vfile.h>.				|
	|								|
	|	There is no real standard for this file to conform to.	|
	|	It is provided for compatibility with Old Unix		|
	|	programs.  It's use is highly discouraged.		|
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
 * Include the system version of sys/file.h, if its not too bad.
 */

vportBEGIN_CPLUSPLUS_HEADER_PROTECTION

#if ( ! vportBAD_SYS_FILE_HDR )
#include <sys/file.h>
#endif

vportEND_CPLUSPLUS_HEADER_PROTECTION


/*
 * Now fix up any failings in the included system header
 */


#endif /* vsysfileINCLUDED */


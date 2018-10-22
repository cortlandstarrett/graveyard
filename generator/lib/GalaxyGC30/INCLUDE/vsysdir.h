/* $Id: vsysdir.h,v 1.2 1993/09/05 23:34:28 chad Exp $ */

#ifndef vsysdirINCLUDED
#define vsysdirINCLUDED 1

/*
	+---------------------------------------------------------------+
	|								|
	|	     vsysdir.h - Visix Sys/Dir Header			|
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
	|	This file is intended to replace sys/dir.h with		|
	|	the "Right Thing".  To use this file, replace any	|
	|	instances of #include <sys/dir.h> with			|
	|	#include <vsys/vdir.h>.					|
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
 * Include the system version of sys/dir.h, if its not too bad.
 */

vportBEGIN_CPLUSPLUS_HEADER_PROTECTION

#if ( ! vportBAD_SYS_DIR_HDR )
#include <sys/dir.h>
#endif

vportEND_CPLUSPLUS_HEADER_PROTECTION


/*
 * Now fix up any failings in the included system header
 */

#ifndef  vdirentINCLUDED
#include vdirentHEADER
#endif


#endif /* vsysdirINCLUDED */


/* $Id: vsysparam.h,v 1.4 1994/11/16 23:37:01 chad Exp $ */

#ifndef vsysparamINCLUDED
#define vsysparamINCLUDED 1

/*
	+---------------------------------------------------------------+
	|								|
	|	     vsysparam.h - Visix Sys/param Header		|
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
	|	instances of #include <sys/param.h> with		|
	|	#include <vsysparam.h>.				|
	|								|
	|	This file is meant to conform to the POSIX standard	|
	|	specification for sys/param.h.				|
	|								|
	+---------------------------------------------------------------+
*/


/*
 * Include any other files this header depends upon
 */

#ifndef  vportINCLUDED
#include <vport.h>
#endif

#ifndef  vsystypesINCLUDED
#include vsystypesHEADER
#endif


/*
 * Include the system version of sys/param.h, if its not too bad
 */

vportBEGIN_CPLUSPLUS_HEADER_PROTECTION

#if ( ! vportBAD_SYS_PARAM_HDR )
#include <sys/param.h>
#endif

vportEND_CPLUSPLUS_HEADER_PROTECTION


/*
 * Fix up anything that may have been wrong
 */

/*
 * If you're looking for MAXHOSTNAMELEN, it lives in vnetdb.h, not here.
 */


#endif /* #ifndef vsysparamINCLUDED */


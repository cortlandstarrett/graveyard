/* $Id: vstd.h,v 1.10 1996/05/20 23:25:32 robert Exp $ */

#ifndef vstdINCLUDED
#define vstdINCLUDED 1

/*
 *	+---------------------------------------------------------------+
 *	|								|
 *	|			vstd.h					|
 *	|								|
 *	+---------------------------------------------------------------+
 *	|								|
 *	|	Standard include file for Galaxy global definitions     |
 *	|								|
 *	+---------------------------------------------------------------+
 */


/*
 * This file is the one place where Galaxy defines identifiers that
 * don't comply with the vmodule prefix convention that all the rest
 * of Galaxy adheres to.  It is a place to declare things that should have
 * been built into C in  the first place.
 */

/*

	Some notes on convention - 

	Any identifier exported in the global namespace that doesn't
have a leading underscore is provided for client use.  However you
should not know and cannot depend upon its implementation.  In
particular, you should not use and cannot depend on a structure having
the field names that it has at any one time, regardless of whether
those field names start with an underscore.  You can't even depend on
the fact that it is a structure; it may be changed to a union, a basic
type, or even an array.

	Any identifier that does have a leading underscore is private
and does not exist.  Never use them. 

*/


/*
 * Include any other files this header depends upon
 */

#ifndef  vportINCLUDED
#include <vport.h>
#endif


#ifndef vMAX
#define vMAX(A,B)	(((A) > (B)) ? (A) : (B))
#endif

#ifndef vMIN
#define vMIN(A,B)	(((A) < (B)) ? (A) : (B))
#endif


/*
 * Some basic types
 */

vportBEGIN_CPLUSPLUS_EXTERN_C

#if (vportBAD_BOOL || !vportCPLUSPLUS_SOURCE)
typedef unsigned char	  vbool;
#else
typedef bool		  vbool;
#endif

typedef unsigned char	  vbyte;

typedef signed char	  vbyteSigned;
    
vportEND_CPLUSPLUS_EXTERN_C


#if (vportCPLUSPLUS_SOURCE)

class vsuppress		{};
#define vsuppressDONT_INIT	((vsuppress *) 0)

#endif /* (vportCPLUSPLUS_SOURCE) */


#ifdef  vportNULL_HEADER
#undef  vstdHEADER
#define vstdHEADER vportNULL_HEADER
#endif

#endif /* vstdINCLUDED */
 

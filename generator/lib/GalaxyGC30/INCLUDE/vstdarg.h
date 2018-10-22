/* $Id: vstdarg.h,v 1.10 1994/02/03 06:56:57 chad Exp $ */

#ifndef vstdargINCLUDED
#define vstdargINCLUDED 1

/*
	+---------------------------------------------------------------+
	|								|
	|	     vstdarg.h - Visix Stdarg Header			|
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
	|	This file is intended to replace stdarg.h with		|
	|	the "Right Thing", as defined by ANSI C.		|
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
 * Include the system version of stdarg.h, if its not too bad
 */

vportBEGIN_CPLUSPLUS_HEADER_PROTECTION

#if ( ! vportBAD_STDARG_HDR )
#include <stdarg.h>
#endif

vportEND_CPLUSPLUS_HEADER_PROTECTION


/*
 * Fix up anything that may have been wrong
 */

#if (vportNEED_VA_LIST_TYPE || vportBAD_STDARG_HDR)
typedef void *va_list;
#endif

#define _vstdargRoundedSize(TYPE)  \
  (((sizeof (TYPE) + sizeof (int) - 1) / sizeof (int)) * sizeof (int))

#if (vportBAD_VA_START)
#undef  va_start
#endif
#ifndef va_start
#define va_start(LIST, ARG)	\
  LIST = (char *)&(ARG) + _vstdargRoundedSize(ARG)
#endif

#if (vportBAD_VA_ARG)
#undef  va_arg
#endif
#ifndef va_arg
#define va_arg(LIST, TYPE)						\
  (LIST = ((char *)(LIST) + _vstdargRoundedSize(TYPE)),			\
   *((TYPE *)(void *)((char *)(LIST) - _vstdargRoundedSize(TYPE))))
#endif

#if (vportBAD_VA_END)
#undef  va_end
#endif
#ifndef va_end
#define va_end(LIST) (void)0
#endif


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


#endif /* #ifndef vstdargINCLUDED */


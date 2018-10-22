/* $Id: vctype.h,v 1.8 1994/09/12 21:10:44 chad Exp $ */

#ifndef vctypeINCLUDED
#define vctypeINCLUDED 1


/*
 * Include any other files this header depends upon
 */

#ifndef  vportINCLUDED
#include <vport.h>
#endif


/*
 * Include the system version of ctype.h, if its not too bad
 */

vportBEGIN_CPLUSPLUS_HEADER_PROTECTION

#if ( ! vportBAD_CTYPE_HDR )
#include <ctype.h>
#endif

vportEND_CPLUSPLUS_HEADER_PROTECTION


/*
 * Fix up anything that may have been wrong
 */

vportBEGIN_CPLUSPLUS_EXTERN_C

#ifndef isascii
#define isascii(__c) ((__c)<=0177)
#endif

#if (vportNEED_TOLOWER_PROTO)
int	tolower( int /*char*/ );
#endif

#if (vportNEED_TOUPPER_PROTO)
int	toupper( int /*char*/ );
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

#endif /* vctypeINCLUDED */


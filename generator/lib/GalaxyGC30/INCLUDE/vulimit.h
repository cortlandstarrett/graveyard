/* $Id: vulimit.h,v 1.1 1992/06/18 20:15:07 chad Exp $ */

#ifndef vulimitINCLUDED
#define vulimitINCLUDED 1


/*
 * Include any other files this header depends upon
 */

#ifndef vportINCLUDED
#include <vport.h>
#endif


/*
 * Include the system version of ulimit.h, if its not too bad
 */

vportBEGIN_CPLUSPLUS_HEADER_PROTECTION

#if ( ! vportBAD_ULIMIT_HDR )
#include <ulimit.h>
#endif

vportEND_CPLUSPLUS_HEADER_PROTECTION


vportBEGIN_CPLUSPLUS_EXTERN_C


/*
 * Fix up anything that may have been wrong
 */

#if (vportNEED_ULIMIT_PROTO)
long	 ulimit( int, ... );
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

#endif /* vulimitINCLUDED */


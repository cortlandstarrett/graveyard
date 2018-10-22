/* $Id: vio.h,v 1.2 1993/06/18 15:45:54 sean Exp $ */

#ifndef vioINCLUDED
#define vioINCLUDED 1

/*
 * Include any other files this header depends upon
 */

#ifndef vportINCLUDED
#include <vport.h>
#endif

/*
 * Include the system version of io.h, if its not too bad
 */

vportBEGIN_CPLUSPLUS_HEADER_PROTECTION

#if (!vportNEED_UNIX_FILESYSTEM)
#if ( ! vportBAD_IO_HDR )
#include <io.h>
#endif
#endif

/*
 * Fix up anything that may have been wrong
 */

vportEND_CPLUSPLUS_HEADER_PROTECTION


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

#endif /* vioINCLUDED */


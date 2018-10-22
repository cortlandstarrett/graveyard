/* $Id: vx11xlib.h,v 1.3 1996/06/22 21:32:25 chad Exp $ */

#ifndef vx11xlibINCLUDED
#define vx11xlibINCLUDED 1

/*
	+---------------------------------------------------------------+
	|								|
	|	     vx11xlib.h - Visix X11/Xlib Header			|
	|	     ========================================		|
	|								|
	+---------------------------------------------------------------+
	|								|
	| (c) Copyright 1993, Visix Software, Inc., All rights reserved.|
	|								|
	+---------------------------------------------------------------+
	|								|
	|			   DESCRIPTION				|
	|			   ===========				|
	|								|
	|	This file is intended to replace X11/Xlib.h with	|
	|	the "Right Thing", as defined by the X Consortium.	|
	|								|
	+---------------------------------------------------------------+
*/


/*
 * Include any files this header depends upon
 */

#ifndef   vportINCLUDED
#include <vport.h>
#endif

/*
 * Include the system versions of X11/Xlib.h, if its not too bad
 */

vportBEGIN_CPLUSPLUS_HEADER_PROTECTION

#if (vportWIN_X11)

/*
 * protect Xlib.h from our C++ keyword MACROs
 */

#if (!defined(__cplusplus) && !vportDONT_MACRO_CPLUSPLUS_KEYWORDS)
#undef class
#undef new
#endif

#if ( ! vportBAD_X11_XLIB_HDR )
#include <X11/Xlib.h>
#endif

#ifdef XlibSpecificationRelease
#undef  vportWIN_X11_VERSION
#define vportWIN_X11_VERSION (0x11000000+0x10000*(XlibSpecificationRelease))
#endif

#endif /* if (vportWIN_X11) */

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

#endif /* vx11xlibINCLUDED */


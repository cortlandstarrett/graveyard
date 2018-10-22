/* $Id: vmswhdrs.h,v 1.13 1997/11/12 17:23:49 jim Exp $ */

#ifndef vmswhdrsINCLUDED
#define vmswhdrsINCLUDED 1

/*
	+---------------------------------------------------------------+
	|								|
	|	     vmswhdrs.h - Visix MS Windows Headers Header	|
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
	|	This file is intended to replace windows.h with		|
	|	the "Right Thing", as defined by Microsoft.		|
	|								|
	+---------------------------------------------------------------+
*/


/*
 * Include any files this header depends upon
 */

#ifndef vportINCLUDED
#include <vport.h>
#endif


/*
 * Include the system headers if they're not too bad
 */

vportBEGIN_CPLUSPLUS_HEADER_PROTECTION

#if (vportOS_WINDOWS)

#define INCLUDE_COMMDLG_H		TRUE
#define INCLUDE_CUSTCNTL_H		TRUE
#define INCLUDE_DDEML_H			TRUE
#define INCLUDE_DDE_H			TRUE
#define INCLUDE_DRIVINIT_H		TRUE
#define INCLUDE_LZEXPAND_H		TRUE
#define INCLUDE_MMSYSTEM_H		TRUE
#define INCLUDE_OLE_H			TRUE
#define INCLUDE_PENWIN_H		TRUE
#define INCLUDE_PENWOEM_H		TRUE
#define INCLUDE_PRINT_H			TRUE
#define INCLUDE_SHELLAPI_H		TRUE
#define INCLUDE_STRESS_H		TRUE
#define INCLUDE_VER_H			TRUE

#ifndef STRICT
#define STRICT				TRUE
#endif

#ifndef OEMRESOURCE
/* this is necessary in order to use native system bitmaps */
#define OEMRESOURCE 1
#endif

#if ( ! vportBAD_WINDOWS_HDR )
#include <windows.h>
#endif

#if ( ! vportBAD_WINDOWSX_HDR )
#include <windowsx.h>
#endif

#ifndef APIENTRY
#define APIENTRY			PASCAL
#endif

#ifndef MK_FP
#define MK_FP(__s,__o) (((unsigned short)(__s)):>((void __near *)(__o)))
#endif

#if (vportOS_WIN32S)
#define AllocAlias16(_ptr)              (_ptr)
#endif

#if (vportCPLUSPLUS_SOURCE)
/* These are method names in G/C++, and the preprocessor is not smart
   enough to distinguish them from the Windows API functions, which 
   are macros in Win32.
*/
#ifndef vportDONT_UNDEF_FINDRESOURCE
#undef FindResource
#endif
#ifndef vportDONT_UNDEF_ISMAXIMIZED
#undef IsMaximized
#endif
#ifndef vportDONT_UNDEF_GETCHARWIDTH
#undef GetCharWidth
#endif
#ifndef vportDONT_UNDEF_APPENDMENU
#undef AppendMenu
#endif
#ifndef vportDONT_UNDEF_GETOBJECT
#undef GetObject
#endif
#ifndef vportDONT_UNDEF_YIELD
#undef Yield
#endif
#ifndef vportDONT_UNDEF_COPYFILE
#undef CopyFile
#endif
#endif /* if (vportCPLUSPLUS_SOURCE) */

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

#endif /* vmswhdrsINCLUDED */


/* $Id: vsys.h,v 1.32 1996/12/12 16:45:52 david Exp $ */

#ifndef vsysINCLUDED
#define vsysINCLUDED 1

/************************************************************
 *
 *	Header file for process-level system-specific info and routines.
 *
 *	Copyright (c) Visix Software 1992-1994
 *	All rights reserved
 *
 ************************************************************/


/*
 * Include any headers that this include file depends upon.
 */

/* Galaxy headers */

#ifndef   vportINCLUDED		/* for v*HEADER */
# include <vport.h>
#endif

#ifndef   vstdINCLUDE           /* for vbool */
# include vstdHEADER
#endif

/* Window system headers */

#if (vportOS_WINDOWS)

#ifndef  vmswhdrsINCLUDED	/* for all MS Windows headers */
#include vmswhdrsHEADER
#endif

#if (vportWIN_X11)
#include <X11/Intrnsc.h>
#endif

#endif

#if (vportOS_OS2)

#ifndef  vos2INCLUDED		/* for all OS/2 headers */
#include vos2HEADER
#endif

#endif

#if (vportOS_MAC)

#include <QuickDraw.h>

#endif

#if (vportVMS_OS)

#ifndef vvmstypesINCLUDED
#include <vvmstypes.h>
#endif

#endif

vportBEGIN_CPLUSPLUS_EXTERN_C



/* ----------------------------------------------------------------------------
 * private types
 * ------------------------------------------------------------------------- */

#if (vportOS_WINDOWS)

typedef struct vsysMSWMessageData vsysMSWMessageData;

struct vsysMSWMessageData {
  HWND   wnd;
  UINT   message;
  WPARAM param1;
  LPARAM param2;
};

#endif



/* ----------------------------------------------------------------------------
 * private internal declarations
 * ------------------------------------------------------------------------- */

#if (vportOS_WINDOWS)
extern vportLINK HPALETTE       _vcolorsysMSWPalette;
extern vportLINK HINSTANCE	_vsysMSWInstance;
extern vportLINK HINSTANCE	_vsysMSWPreviousInstance;
extern vportLINK int		_vsysMSWCmdShow;
extern vportLINK HICON		_vsysMSWIcon;
extern vportLINK DWORD		_vsysMSWVersion;
extern vportLINK DWORD		_vsysMSWWinNT;
#if (vportWIN_X11)
extern vportLINK Widget		_vsysMSWTopLevelWidget;
#endif
#endif

#if (vportOS_MAC)
extern vportLINK unsigned long		_vsysMacSIZE;
extern vportLINK short			_vsysMacProcessResRef;
#endif



/* ----------------------------------------------------------------------------
 * function prototypes
 * ------------------------------------------------------------------------- */

vportLINK void vsysStartup( void );



/* ----------------------------------------------------------------------------
 * platform specific prototypes
 * ------------------------------------------------------------------------- */

#if (vportOS_WINDOWS)
	  HINSTANCE 		 vsysGetMSWInstance( void );
	  HINSTANCE 		 vsysGetMSWPreviousInstance( void );
	  int       		 vsysGetMSWCmdShow( void );
vportLINK HWND	       vsysGetMSWTaskWindow( void );
vportLINK void         vsysHideMSWTaskWindow( void );
vportLINK void         vsysShowMSWTaskWindow( void );
vportLINK void         vsysRegisterMSWTaskWindowChild( HWND );
vportLINK void         vsysUnregisterMSWTaskWindowChild( HWND );
vportLINK void         vsysSetMSWTaskWindowTitle( const char * );
	  HICON			 vsysGetMSWIcon( void );
vportLINK void         vsysSetMSWIcon( HICON icon );
	  int			 vsysIsMSWWin32s();
	  int			 vsysIsMSWWinNT();
	  BYTE			 vsysGetMSWMajorVersion();
	  int			 vsysIsMSWWin32s();
	  int			 vsysIsMSWWin32Windows();
	  int			 vsysIsMSWWin31();
vportLINK void         _setupMSWPrinter();
vportLINK int          vsysGetMSWRegistryValue( HKEY, char *, char *,
							  char *, int );
#if (vportWIN_X11)
vportLINK void	       vsysMSWXtInitialize( int argc, char *argv[] );
#endif
#endif

#if (vportOS_OS2)
HAB			vsysGetPMAnchorBlock( void );
vbool			vsysExistsPMAnchorBlock( void );
HMQ			vsysGetPMMsgQueue( void );
vbool			vsysExistsPMMsgQueue( void );
#endif

#if (vportOS_MAC)

unsigned long *vsysGetMacSIZE(
    void
    );

vportLINK void vsysSetMacFrontClicks(
    int 			on
    );

vportLINK void vsysSetMacMoreMasters(
    int				moremasters
    );

vportLINK void vsysSetMacStackKBytes(
    int				kbytes
    );

#endif

#if (vportOLE)

int vportLINK vsysOleInitialize(
    void
    );

void vportLINK vsysOleUninitialize(
    void
    );

#endif


/* ----------------------------------------------------------------------------
 * MACROs
 * ------------------------------------------------------------------------- */

#if (vportOS_WINDOWS)
#define vsysGetMSWInstance()	        (_vsysMSWInstance)
#define vsysGetMSWPreviousInstance()    (_vsysMSWPreviousInstance)
#define vsysGetMSWCmdShow()             (_vsysMSWCmdShow)
#define vsysGetMSWIcon()                (_vsysMSWIcon)
#define vsysGetMSWMajorVersion()	((BYTE)_vsysMSWVersion)

#if (vportOS_WIN32S)
#define vsysIsMSWWinNT()                   (_vsysMSWWinNT)
#define vsysIsMSWWin32s() \
    ((!vsysIsMSWWinNT()) && (vsysGetMSWMajorVersion() < 4))
#define vsysIsMSWWin32Windows() \
    ((!vsysIsMSWWinNT()) && (vsysGetMSWMajorVersion() >= 4))
#define vsysIsMSWWin31()		(vsysIsMSWWin32s())
#else
#define vsysIsMSWWinNT()                (vFALSE)
#define vsysIsMSWWin32s()               (vFALSE)
#define vsysIsMSWWin32Windows()         (vFALSE)
#define vsysIsMSWWin31()		(vTRUE)
#endif
#endif

#if (vportOS_MAC)
#define vsysGetMacSIZE()	  	(_vsysMacSIZE)
#define vsysGetMacResRef()	  	(_vsysMacProcessResRef)
#endif



/* ----------------------------------------------------------------------------
 * Mark system-dependent words
 * ------------------------------------------------------------------------- */

/*
 * mark any words that would choke on MS Windows
 */

#if (!vportOS_WINDOWS && !vportOS_OS2)
#if (!vportDONT_MACRO_MS_WINDOWS_RESERVED_WORDS)
#define ATOM		error{symbol ATOM is an MS-Windows reserved word}
#define BOOL		error{symbol BOOL is an MS-Windows reserved word}
#define BYTE		error{symbol BYTE is an MS-Windows reserved word}
#define CHAR		error{symbol CHAR is an MS-Windows reserved word}
#define DWORD		error{symbol DWORD is an MS-Windows reserved word}
#define FIXED		error{symbol FIXED is an MS-Windows reserved word}
#define HANDLE		error{symbol HANDLE is an MS-Windows reserved word}
#define HIWORD		error{symbol HIWORD is an MS-Windows reserved word}
#define LONG		error{symbol LONG is an MS-Windows reserved word}
#define LOWORD		error{symbol LOWORD is an MS-Windows reserved word}
#define LPARAM		error{symbol LPARAM is an MS-Windows reserved word}
#define RECTL		error{symbol RECTL is an MS-Windows reserved word}
#define RGB		error{symbol RGB is an MS-Windows reserved word}
#define TEXT		error{symbol TEXT is an MS-Windows reserved word}
#define UINT		error{symbol UINT is an MS-Windows reserved word}
#define WORD		error{symbol WORD is an MS-Windows reserved word}
#define WPARAM		error{symbol WPARAM is an MS-Windows reserved word}
#endif
#endif

/*
 * mark any words that would choke on PM
 */

#if (!vportOS_OS2)
#if (!vportDONT_MACRO_OS2_RESERVED_WORDS)
#define CELL		error{symbol CELL is an OS/2 reserved word}
#define CLASS		error{symbol CLASS is an OS/2 reserved word}
#define COLOR		error{symbol COLOR is an OS/2 reserved word}
#define PID		error{symbol PID is an OS/2 reserved word}
#endif
#endif

vportEND_CPLUSPLUS_EXTERN_C

#ifdef  vportNULL_HEADER
#undef  vsysHEADER
#define vsysHEADER vportNULL_HEADER
#endif

#endif /* #ifndef vsysINCLUDED */


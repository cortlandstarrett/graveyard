/* $Id: veventsys.h,v 1.15 1997/08/19 21:53:15 jim Exp $ */

/************************************************************

    veventsys.h

    C Interface file for the Event Manager System-Dependent interface

    (c) Copyright Visix Software Inc.
    All rights reserved

************************************************************/

#ifndef veventsysINCLUDED
#define veventsysINCLUDED 1

#ifndef  vportINCLUDED
#include <vport.h>		/* for v*HEADER */
#endif

#ifndef  vtimestampINCLUDED
#include vtimestampHEADER
#endif

#ifndef  veventINCLUDED
#include veventHEADER
#endif

#ifndef  vevent2INCLUDED
#include vevent2HEADER
#endif

#ifndef  vevent2sysINCLUDED
#include vevent2sysHEADER
#endif

/* System-Dependent headers */

#if (vportWIN_X11)
#ifndef  vx11xlibINCLUDED
#include vx11xlibHEADER
#endif
#endif

#if (vportOS_WIN32S)
#ifndef  vmswhdrsINCLUDED
#include vmswhdrsHEADER
#endif
#endif

#if (vportOS_OS2)
#ifndef  vos2INCLUDED
#include vos2HEADER
#endif
#endif

#if (vportOS_MAC)
#ifndef  vconditionINCLUDED
#include vconditionHEADER
#endif
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C


/*
 * * * * * * * * * * PUBLIC TYPE DEFINITIONS * * * * * * * * * *
 */

#if (vportWIN_X11)

typedef void (*veventsysXHandlerProc)(
    XEvent                         *event
    );
    
#endif

#if (vportOS_WIN32S)

typedef void (*veventsysMSWHandlerProc)(
    MSG                            *message
    );

typedef int (*veventsysOleAccelProc)(
    void                           *window,
    MSG                            *message
    );
#endif

#if (vportOS_OS2)

typedef void (*veventsysPMHandlerProc)(
    QMSG                           *message
    );
    
#endif

#if (vportOS_MAC)

typedef void (*veventsysMacHandlerProc)(
    EventRecord                    *event
    );
        
#endif

#if (vportEVENTS_USE_VMS_EF)

typedef struct veventEF veventEF;

typedef void (veventEFNoteProc)(veventEF *efEvent);

struct veventEF {
    int		                 EF;
    void			*data;
    veventEFNoteProc		*notify;
    veventEF			*next;
};

typedef struct veventEFIterator veventEFIterator;

struct veventEFIterator {
    veventEF		*efEvent;
};

extern vportLINK veventEF				 _veventEFListHead;

#endif


/*
 * * * * * * * * * * PRIVATE GLOBAL VARIABLES * * * * * * * * * *
 */


/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */

int veventIsDoneProcessing(
    void
    );

void veventProcessQuit(
    void
    );

void veventBeginQuit(
    int system
    );

void veventEndQuit(
    void
    );

int veventIsQuitCancelled(
    void
    );

int veventIsSystemQuit(
    void
    );

#if (vportWIN_X11)

void veventsysSetXHandlerProc(
    veventsysXHandlerProc           proc
    );

veventsysXHandlerProc veventsysGetXHandlerProc(
    void
    );

#endif /* vportWIN_X11 */

#if (vportOS_WIN32S)

void veventsysSetMSWHandlerProc(
    veventsysMSWHandlerProc   proc
    );

veventsysMSWHandlerProc veventsysGetMSWHandlerProc(
    void
    );

void veventsysMSWQueueFlushProc(
    void
    );

int veventsysMSWModalDialogBoxHook(
    HWND                           hDlg,
    UINT                           msg,
    WPARAM                         wParam,
    LPARAM                         lParam
    );

void veventsysFlushMSWEventQueue(
    int				 triggered,
    int				 priority
    );

HACCEL veventsysGetMSWAccelTable(
    void
    );   

HWND veventsysGetMSWAccelWindow(
    void
    );   

void veventsysSetMSWAccelTable(
    HACCEL hAccel
    );

void veventsysSetMSWAccelWindow(
    HWND hWnd
    );

void veventsysSetOleAccelProc(
    veventsysOleAccelProc proc
    );

veventsysOleAccelProc veventsysGetOleAccelProc(
    void
    );

void veventsysSetActiveWindow(
    void  *window
    );

void *veventsysGetActiveWindow(
    void
    );
#endif /* vportOS_WIN32S */

#if (vportOS_OS2)

void veventsysSetPMHandlerProc(
    veventsysPMHandlerProc          proc
    );

veventsysPMHandlerProc veventsysGetPMHandlerProc(
    void
    );

void _veventPMCancelWaitProc(
    void
    );

#endif /* vportOS_OS2 */

#if (vportOS_MAC)

void veventsysSetMacHandlerProc(
    veventsysMacHandlerProc         proc
    );

veventsysMacHandlerProc veventsysGetMacHandlerProc(
    void
    );

void veventsysRunMacEventLoop(
    void
    );

vbool veventsysIsInitialized(
	void
	);

#endif /* vportOS_MAC */

#if (vportEVENTS_USE_VMS_EF)

veventEF *veventRegisterEF(
    int                             efn
    );

void veventUnregisterEF(
    veventEF                       *EF
    );

unsigned int veventReserveEF(
    int                            *start_efn, 
    int                            *efn
    );

unsigned int veventFreeEF(
    int                            *efn
    );

unsigned int veventGetEF(
    int                            *efn
    );

int veventGetEFEventFlag(
    veventEF                       *EF
    );

veventEFNoteProc *veventGetEFNotify(
    veventEF                       *EF
    );

void veventSetEFNotify(
    veventEF                       *EF, 
    veventEFNoteProc               *noteProc
    );

void *veventGetEFData(
    veventEF                       *EF
    );

void veventSetEFData(
    veventEF                       *EF,
    const void                     *data
    );

void veventInitEFIterator(
    veventEFIterator               *iterator
    );

int veventNextEFIterator(
    veventEFIterator               *iterator
    );

veventEF *veventGetEFIteratorEF(
    veventEFIterator               *iterator
    );

void veventDestroyEFIterator(
    veventEFIterator               *iterator
    );

veventEF *_veventFindEF(
    int                             ef
    );

#endif


/*
 * * * * * * * * * * PRIVATE PROTOYPES * * * * * * * * * *
 */

#if (vportOS_WIN32S)

int _vevent2bcsysMSWModalDialogBoxHook(
    HWND                           hDlg,
    UINT                           msg,
    WPARAM                         wParam,
    LPARAM                         lParam
    );

void _vevent2bcsysFlushMSWEventQueue(
    int				 triggered,
    int				 priority
    );

#endif

/*
 * * * * * * * * * * PRIVATE CONSTANT DEFINITIONS * * * * * * * * * *
 */


/*
 * * * * * * * * * * PRIVATE VARIABLE DECLARATIONS * * * * * * * * * *
 */

#if (vportWIN_X11)
extern vportLINK veventsysXHandlerProc        _veventsysXHandlerProc;
#endif

#if (vportOS_WIN32S)
extern vportLINK veventsysMSWHandlerProc      _vevent2bcsysMSWHandlerProc;
extern vportLINK HACCEL                       _vevent2bcsysMSWAccelTable;
extern vportLINK HWND                         _vevent2bcsysMSWAccelWindow;
extern vportLINK veventsysOleAccelProc        _vevent2bcsysOleAccelProc;
extern vportLINK void                        *_vevent2bcsysActiveWindow;
#endif

#if (vportOS_OS2)
extern vportLINK veventsysPMHandlerProc       _veventsysPMHandlerProc;
#endif

/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * *
 */

#define veventIsDoneProcessing() \
        (vevent2LoopGetCurrent()->stops >= vevent2LoopGetCurrent()->depth)
#define veventProcessQuit() \
        (_vevent2bcBlockingQuit = vTRUE, \
	 veventProcess(), \
	 _vevent2bcBlockingQuit = vFALSE)
#define veventBeginQuit(system) \
        (_vevent2bcQuitting = vTRUE, _vevent2bcSystemQuit = system)
#define veventEndQuit() \
        (_vevent2bcQuitting = vFALSE, _vevent2bcSystemQuit = vFALSE)
#define veventIsQuitCancelled() \
        (!_vevent2bcQuitting)

#if (vportWIN_X11)
#define veventsysSetXHandlerProc(p) \
        vevent2sysXSetHandlerProc(p)
#define veventsysGetXHandlerProc() \
        vevent2sysXGetHandlerProc()
#endif

#if (vportOS_WIN32S)
#define veventsysMSWModalDialogBoxHook(d, m, w, l) \
        _vevent2bcsysMSWModalDialogBoxHook(d, m, w, l)
#define veventsysFlushMSWEventQueue(t, p) \
        _vevent2bcsysFlushMSWEventQueue(t, p)
#define veventsysGetMSWAccelTable() \
        (_vevent2bcsysMSWAccelTable)
#define veventsysGetMSWAccelWindow() \
        (_vevent2bcsysMSWAccelWindow)
#define veventsysSetMSWAccelTable(t) \
        (_vevent2bcsysMSWAccelTable = (t))
#define veventsysSetMSWAccelWindow(w) \
        (_vevent2bcsysMSWAccelWindow = (w))
#define veventsysSetOleAccelProc(p) \
        (_vevent2bcsysOleAccelProc = (p))
#define veventsysGetOleAccelProc() \
        (_vevent2bcsysOleAccelProc)
#define veventsysSetActiveWindow(w) \
        (_vevent2bcsysActiveWindow = (w))
#define veventsysGetActiveWindow(w) \
        (_vevent2bcsysActiveWindow)
#endif

#if (vportOS_OS2)
#define veventsysSetPMHandlerProc(p) \
        vevent2sysOS2SystemHandlerSetHandlerProc \
	(vevent2sysOS2SystemHandlerGetCurrent(), (p))
#define veventsysGetPMHandlerProc() \
        vevent2sysOS2SystemHandlerGetHandlerProc \
	(vevent2sysOS2SystemHandlerGetCurrent())
#endif

vportEND_CPLUSPLUS_EXTERN_C

#endif /* #ifndef veventsysINCLUDED */


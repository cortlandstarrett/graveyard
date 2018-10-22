/* $Id: vevent2sys.h,v 1.43 1997/10/01 22:59:52 robert Exp $ */

#ifndef vevent2sysINCLUDED
#define vevent2sysINCLUDED 1

#ifndef  vportINCLUDED      /* for v*HEADER */
#include <vport.h>
#endif

#ifndef  vevent2INCLUDED
#include vevent2HEADER
#endif

#ifndef  vsysselectINCLUDED
#include vsysselectHEADER
#endif

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
#include <events.h>

#ifndef  vconditionINCLUDED
#include vconditionHEADER
#endif
#endif


vportBEGIN_CPLUSPLUS_EXTERN_C


/*
 * * * * * * * * * * * * * PUBLIC TYPES * * * * * * * * * * * * * *
 */

#if (vportOS_UNIX)

typedef struct vevent2sysUnixSystemHandler     vevent2sysUnixSystemHandler;

typedef struct vevent2sysUnixSystemHandlerClass
               vevent2sysUnixSystemHandlerClass;

typedef struct vevent2sysUnixDriver            vevent2sysUnixDriver;

typedef struct vevent2sysUnixDriverClass       vevent2sysUnixDriverClass;

typedef _veventFDSelectNoteProc                vevent2sysUnixSelectNotifyProc;

#endif

#if (vportWIN_X11)
typedef void (vevent2sysXHandlerProc)(XEvent *pEvent);
#endif

#if (vportOS_WIN32S)

typedef struct vevent2sysWin32SystemHandler    vevent2sysWin32SystemHandler;

typedef struct vevent2sysWin32SystemHandlerClass
               vevent2sysWin32SystemHandlerClass;

typedef struct vevent2sysWin32Driver           vevent2sysWin32Driver;

typedef struct vevent2sysWin32DriverClass      vevent2sysWin32DriverClass;

typedef void (vevent2sysWin32HandlerProc)(MSG *pEvent);

#endif

#if (vportOS_OS2)

typedef struct vevent2sysOS2SystemHandler      vevent2sysOS2SystemHandler;

typedef struct vevent2sysOS2SystemHandlerClass vevent2sysOS2SystemHandlerClass;

typedef struct vevent2sysOS2Driver             vevent2sysOS2Driver;

typedef struct vevent2sysOS2DriverClass        vevent2sysOS2DriverClass;

typedef void (vevent2sysOS2HandlerProc)(QMSG *pEvent);

#endif

#if (vportOS_MAC)

typedef struct vevent2sysMacSystemHandler      vevent2sysMacSystemHandler;

typedef struct vevent2sysMacSystemHandlerClass vevent2sysMacSystemHandlerClass;

typedef struct vevent2sysMacDriver             vevent2sysMacDriver;

typedef struct vevent2sysMacDriverClass        vevent2sysMacDriverClass;

typedef void (vevent2sysMacHandlerProc)(EventRecord *pEvent);
    
#endif


/*
 * * * * * * * * * * * * * PUBLIC CONSTANTS * * * * * * * * * * * * * * *
 */


/*
 * * * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * * *
 */

#if (vportOS_UNIX)

/* class vevent2sysUnixSystemHandler */

vevent2sysUnixSystemHandlerClass *vevent2sysUnixSystemHandlerClassGetDefault
    (void                                 );

vevent2SystemEventHandlerClass
                          *vevent2sysUnixSystemHandlerClassAsSystemHandlerClass
    (vevent2sysUnixSystemHandlerClass    *pClass);

vbool                            vevent2sysUnixSystemHandlerClassValidate
    (vevent2sysUnixSystemHandlerClass    *pClass);

void                             vevent2sysUnixSystemHandlerClassAssert
    (vevent2sysUnixSystemHandlerClass    *pClass);

void                             vevent2sysUnixSystemHandlerClassHandledAssert
    (vevent2sysUnixSystemHandlerClass    *pClass,
     vdebugAssertionHandler               handler,
     void                                *pData);

vevent2sysUnixSystemHandler     *vevent2sysUnixSystemHandlerGetCurrent
    (void                                 );

vevent2sysUnixSystemHandler     *vevent2sysUnixSystemHandlerOfLoop
    (vevent2Loop                         *pLoop);

vevent2sysUnixSystemHandler     *vevent2sysUnixSystemHandlerCreate
    (void                                 );

vevent2sysUnixSystemHandler     *vevent2sysUnixSystemHandlerCreateOfClass
    (vevent2sysUnixSystemHandlerClass    *pClass);

void                             vevent2sysUnixSystemHandlerRelease
    (vevent2sysUnixSystemHandler         *pSystemHandler);

void                             vevent2sysUnixSystemHandlerSetSelectNotifyData
    (vevent2sysUnixSystemHandler         *pSystemHandler,
     int                                  fd,
     const void                          *pData);

void                            *vevent2sysUnixSystemHandlerGetSelectNotifyData
    (vevent2sysUnixSystemHandler         *pSystemHandler,
     int                                  fd);

void                             vevent2sysUnixSystemHandlerSetSelectReadNotify
    (vevent2sysUnixSystemHandler         *pSystemHandler,
     int                                  fd,
     vevent2sysUnixSelectNotifyProc      *pNoteProc);

vevent2sysUnixSelectNotifyProc  *vevent2sysUnixSystemHandlerGetSelectReadNotify
    (vevent2sysUnixSystemHandler         *pSystemHandler,
     int                                  fd);

void                            vevent2sysUnixSystemHandlerSetSelectWriteNotify
    (vevent2sysUnixSystemHandler          *pSystemHandler,
     int                                  fd,
     vevent2sysUnixSelectNotifyProc      *pNoteProc);

vevent2sysUnixSelectNotifyProc *vevent2sysUnixSystemHandlerGetSelectWriteNotify
    (vevent2sysUnixSystemHandler         *pSystemHandler,
     int                                  fd);

void                           vevent2sysUnixSystemHandlerSetSelectExceptNotify
    (vevent2sysUnixSystemHandler         *pSystemHandler,
     int                                  fd,
     vevent2sysUnixSelectNotifyProc      *pNoteProc);

vevent2sysUnixSelectNotifyProc*vevent2sysUnixSystemHandlerGetSelectExceptNotify
    (vevent2sysUnixSystemHandler         *pSystemHandler,
     int                                  fd);

vevent2SystemEventHandler          *vevent2sysUnixSystemHandlerAsSystemHandler
    (vevent2sysUnixSystemHandler         *pSystemHandler);

vevent2sysUnixSystemHandlerClass   *vevent2sysUnixSystemHandlerGetClass
    (vevent2sysUnixSystemHandler         *pSystemHandler);

vbool                               vevent2sysUnixSystemHandlerValidate
    (vevent2sysUnixSystemHandler         *pSystemHandler);

void                                vevent2sysUnixSystemHandlerAssert
    (vevent2sysUnixSystemHandler         *pSystemHandler);

void                                vevent2sysUnixSystemHandlerHandledAssert
    (vevent2sysUnixSystemHandler         *pSystemHandler,
     vdebugAssertionHandler               handler,
     void                                *pData);

/* class vevent2sysUnixDriver */

vevent2sysUnixDriverClass          *vevent2sysUnixDriverClassGetDefault
    (void                                 );

vevent2DriverClass                 *vevent2sysUnixDriverClassAsDriverClass
    (vevent2sysUnixDriverClass           *pClass);

vbool                               vevent2sysUnixDriverClassValidate
    (vevent2sysUnixDriverClass           *pClass);

void                                vevent2sysUnixDriverClassAssert
    (vevent2sysUnixDriverClass           *pClass);

void                                vevent2sysUnixDriverClassHandledAssert
    (vevent2sysUnixDriverClass           *pClass,
     vdebugAssertionHandler               handler,
     void                                *pData);

vevent2sysUnixDriver               *vevent2sysUnixDriverGetCurrent
    (void                                 );

vevent2sysUnixDriver               *vevent2sysUnixDriverOfLoop
    (vevent2Loop                         *pLoop);

vevent2sysUnixDriver               *vevent2sysUnixDriverCreate
    (void                                 );

vevent2sysUnixDriver               *vevent2sysUnixDriverCreateOfClass
    (vevent2sysUnixDriverClass           *pClass);

void                                vevent2sysUnixDriverRelease
    (vevent2sysUnixDriver                *pDriver);

void                                vevent2sysUnixDriverSetXHandlerProc
    (vevent2sysUnixDriver                *pDriver,
     vevent2sysXHandlerProc              *pHandlerProc);

vevent2sysXHandlerProc             *vevent2sysUnixDriverGetXHandlerProc
    (vevent2sysUnixDriver                *pDriver);

void                                vevent2sysUnixDriverSetSystemHandler
    (vevent2sysUnixDriver                *pDriver,
     vevent2sysUnixSystemHandler         *pHandler);

vevent2sysUnixSystemHandler        *vevent2sysUnixDriverGetSystemHandler
    (vevent2sysUnixDriver                *pDriver);

vevent2Driver                      *vevent2sysUnixDriverAsDriver
    (vevent2sysUnixDriver                *pDriver);

vevent2sysUnixDriverClass          *vevent2sysUnixDriverGetClass
    (vevent2sysUnixDriver                *pDriver);

vbool                               vevent2sysUnixDriverValidate
    (vevent2sysUnixDriver                *pDriver);

void                                vevent2sysUnixDriverAssert
    (vevent2sysUnixDriver                *pDriver);

void                                vevent2sysUnixDriverHandledAssert
    (vevent2sysUnixDriver                *pDriver,
     vdebugAssertionHandler               handler,
     void                                *pData);

#endif /* #if (vportOS_UNIX) */

#if (vportWIN_X11)

vportLINK void                    vevent2sysXSetHandlerProc
    (vevent2sysXHandlerProc              *pProc);

vportLINK vevent2sysXHandlerProc *vevent2sysXGetHandlerProc
    (void                                 );

#endif

#if (vportOS_WIN32S)

/* class vevent2sysWin32SystemHandler */

vevent2sysWin32SystemHandlerClass  *vevent2sysWin32SystemHandlerClassGetDefault
    (void                                 );

vevent2SystemEventHandlerClass
                         *vevent2sysWin32SystemHandlerClassAsSystemHandlerClass
    (vevent2sysWin32SystemHandlerClass   *pClass);

vbool                               vevent2sysWin32SystemHandlerClassValidate
    (vevent2sysWin32SystemHandlerClass   *pClass);

void                                vevent2sysWin32SystemHandlerClassAssert
    (vevent2sysWin32SystemHandlerClass   *pClass);

void                             vevent2sysWin32SystemHandlerClassHandledAssert
    (vevent2sysWin32SystemHandlerClass   *pClass,
     vdebugAssertionHandler               handler,
     void                                *pData);

vevent2sysWin32SystemHandler       *vevent2sysWin32SystemHandlerGetCurrent
    (void                                 );

vevent2sysWin32SystemHandler       *vevent2sysWin32SystemHandlerCreate
    (void                                 );

vevent2sysWin32SystemHandler       *vevent2sysWin32SystemHandlerCreateOfClass
    (vevent2sysWin32SystemHandlerClass   *pClass);

void                                vevent2sysWin32SystemHandlerRelease
    (vevent2sysWin32SystemHandler        *pSystemHandler);

vevent2SystemEventHandler          *vevent2sysWin32SystemHandlerAsSystemHandler
    (vevent2sysWin32SystemHandler        *pSystemHandler);

vevent2sysWin32SystemHandlerClass  *vevent2sysWin32SystemHandlerGetClass
    (vevent2sysWin32SystemHandler        *pSystemHandler);

vbool                               vevent2sysWin32SystemHandlerValidate
    (vevent2sysWin32SystemHandler        *pSystemHandler);

void                                vevent2sysWin32SystemHandlerAssert
    (vevent2sysWin32SystemHandler        *pSystemHandler);

void                                vevent2sysWin32SystemHandlerHandledAssert
    (vevent2sysWin32SystemHandler        *pSystemHandler,
     vdebugAssertionHandler               handler,
     void                                *pData);

/* class vevent2sysWin32Driver */

vevent2sysWin32DriverClass         *vevent2sysWin32DriverClassGetDefault
    (void                                 );

vevent2DriverClass                 *vevent2sysWin32DriverClassAsDriverClass
    (vevent2sysWin32DriverClass          *pClass);

vbool                               vevent2sysWin32DriverClassValidate
    (vevent2sysWin32DriverClass          *pClass);

void                                vevent2sysWin32DriverClassAssert
    (vevent2sysWin32DriverClass          *pClass);

void                                vevent2sysWin32DriverClassHandledAssert
    (vevent2sysWin32DriverClass          *pClass,
     vdebugAssertionHandler               handler,
     void                                *pData);

vevent2sysWin32Driver              *vevent2sysWin32DriverGetCurrent
    (void                                 );

vevent2sysWin32Driver              *vevent2sysWin32DriverCreate
    (void                                 );

vevent2sysWin32Driver              *vevent2sysWin32DriverCreateOfClass
    (vevent2sysWin32DriverClass          *pClass);

void                                vevent2sysWin32DriverRelease
    (vevent2sysWin32Driver               *pDriver);

void                                vevent2sysWin32DriverSetHandlerProc
    (vevent2sysWin32Driver               *pDriver,
     vevent2sysWin32HandlerProc          *pHandlerProc);

vevent2sysWin32HandlerProc         *vevent2sysWin32DriverGetHandlerProc
    (vevent2sysWin32Driver               *pDriver);

vevent2Driver                      *vevent2sysWin32DriverAsDriver
    (vevent2sysWin32Driver               *pDriver);

vevent2sysWin32DriverClass         *vevent2sysWin32DriverGetClass
    (vevent2sysWin32Driver               *pDriver);

vbool                               vevent2sysWin32DriverValidate
    (vevent2sysWin32Driver               *pDriver);

void                                vevent2sysWin32DriverAssert
    (vevent2sysWin32Driver               *pDriver);

void                                vevent2sysWin32DriverHandledAssert
    (vevent2sysWin32Driver               *pDriver,
     vdebugAssertionHandler               handler,
     void                                *pData);

#endif /* #if (vportOS_WIN32S) */

#if (vportOS_OS2)

/* class vevent2sysOS2SystemHandler */

vevent2sysOS2SystemHandlerClass     *vevent2sysOS2SystemHandlerClassGetDefault
    (void                                 );

vevent2SystemEventHandlerClass
                           *vevent2sysOS2SystemHandlerClassAsSystemHandlerClass
    (vevent2sysOS2SystemHandlerClass     *pClass);

vbool                             vevent2sysOS2SystemHandlerClassValidate
    (vevent2sysOS2SystemHandlerClass     *pClass);

void                              vevent2sysOS2SystemHandlerClassAssert
    (vevent2sysOS2SystemHandlerClass     *pClass);

void                              vevent2sysOS2SystemHandlerClassHandledAssert
    (vevent2sysOS2SystemHandlerClass     *pClass,
     vdebugAssertionHandler               handler,
     void                                *pData);

vevent2sysOS2SystemHandler      *vevent2sysOS2SystemHandlerGetCurrent
    (void                                 );

vevent2sysOS2SystemHandler      *vevent2sysOS2SystemHandlerCreate
    (void                                 );

vevent2sysOS2SystemHandler      *vevent2sysOS2SystemHandlerCreateOfClass
    (vevent2sysOS2SystemHandlerClass     *pClass);

void                             vevent2sysOS2SystemHandlerRelease
    (vevent2sysOS2SystemHandler          *pSystemHandler);

void                                vevent2sysOS2SystemHandlerSetHandlerProc
    (vevent2sysOS2SystemHandler          *pSystemHandler,
     vevent2sysOS2HandlerProc            *pHandlerProc);

vevent2sysOS2HandlerProc           *vevent2sysOS2SystemHandlerGetHandlerProc
    (vevent2sysOS2SystemHandler          *pSystemHandler);

vevent2SystemEventHandler          *vevent2sysOS2SystemHandlerAsSystemHandler
    (vevent2sysOS2SystemHandler          *pSystemHandler);

vevent2sysOS2SystemHandlerClass    *vevent2sysOS2SystemHandlerGetClass
    (vevent2sysOS2SystemHandler          *pSystemHandler);

vbool                               vevent2sysOS2SystemHandlerValidate
    (vevent2sysOS2SystemHandler          *pSystemHandler);

void                                vevent2sysOS2SystemHandlerAssert
    (vevent2sysOS2SystemHandler          *pSystemHandler);

void                                vevent2sysOS2SystemHandlerHandledAssert
    (vevent2sysOS2SystemHandler          *pSystemHandler,
     vdebugAssertionHandler               handler,
     void                                *pData);

/* class vevent2sysOS2Driver */

vevent2sysOS2DriverClass           *vevent2sysOS2DriverClassGetDefault
    (void                                 );

vevent2DriverClass                 *vevent2sysOS2DriverClassAsDriverClass
    (vevent2sysOS2DriverClass            *pClass);

vbool                               vevent2sysOS2DriverClassValidate
    (vevent2sysOS2DriverClass            *pClass);

void                                vevent2sysOS2DriverClassAssert
    (vevent2sysOS2DriverClass            *pClass);

void                                vevent2sysOS2DriverClassHandledAssert
    (vevent2sysOS2DriverClass            *pClass,
     vdebugAssertionHandler               handler,
     void                                *pData);

vevent2sysOS2Driver                *vevent2sysOS2DriverGetCurrent
    (void                                 );

vevent2sysOS2Driver                *vevent2sysOS2DriverCreate
    (void                                 );

vevent2sysOS2Driver                *vevent2sysOS2DriverCreateOfClass
    (vevent2sysOS2DriverClass            *pClass);

void                                vevent2sysOS2DriverRelease
    (vevent2sysOS2Driver                 *pDriver);

vevent2Driver                      *vevent2sysOS2DriverAsDriver
    (vevent2sysOS2Driver                 *pDriver);

vevent2sysOS2DriverClass           *vevent2sysOS2DriverGetClass
    (vevent2sysOS2Driver                 *pDriver);

vbool                               vevent2sysOS2DriverValidate
    (vevent2sysOS2Driver                 *pDriver);

void                                vevent2sysOS2DriverAssert
    (vevent2sysOS2Driver                 *pDriver);

void                                vevent2sysOS2DriverHandledAssert
    (vevent2sysOS2Driver                 *pDriver,
     vdebugAssertionHandler               handler,
     void                                *pData);

#endif /* #if (vportOS_OS2) */

#if (vportOS_MAC)

/* class vevent2sysMacSystemHandler */

vevent2sysMacSystemHandlerClass    *vevent2sysMacSystemHandlerClassGetDefault
    (void                                 );

vevent2SystemEventHandlerClass
                           *vevent2sysMacSystemHandlerClassAsSystemHandlerClass
    (vevent2sysMacSystemHandlerClass     *pClass);

vbool                               vevent2sysMacSystemHandlerClassValidate
    (vevent2sysMacSystemHandlerClass     *pClass);

void                                vevent2sysMacSystemHandlerClassAssert
    (vevent2sysMacSystemHandlerClass     *pClass);

void                               vevent2sysMacSystemHandlerClassHandledAssert
    (vevent2sysMacSystemHandlerClass     *pClass,
     vdebugAssertionHandler               handler,
     void                                *pData);

vevent2sysMacSystemHandler         *vevent2sysMacSystemHandlerGetCurrent
    (void                                 );

vevent2sysMacSystemHandler         *vevent2sysMacSystemHandlerCreate
    (void                                 );

vevent2sysMacSystemHandler         *vevent2sysMacSystemHandlerCreateOfClass
    (vevent2sysMacSystemHandlerClass     *pClass);

void                                vevent2sysMacSystemHandlerRelease
    (vevent2sysMacSystemHandler          *pSystemHandler);

vevent2SystemEventHandler          *vevent2sysMacSystemHandlerAsSystemHandler
    (vevent2sysMacSystemHandler          *pSystemHandler);

vevent2sysMacSystemHandlerClass    *vevent2sysMacSystemHandlerGetClass
    (vevent2sysMacSystemHandler          *pSystemHandler);

vbool                               vevent2sysMacSystemHandlerValidate
    (vevent2sysMacSystemHandler          *pSystemHandler);

void                                vevent2sysMacSystemHandlerAssert
    (vevent2sysMacSystemHandler          *pSystemHandler);

void                                vevent2sysMacSystemHandlerHandledAssert
    (vevent2sysMacSystemHandler          *pSystemHandler,
     vdebugAssertionHandler               handler,
     void                                *pData);

/* class vevent2sysMacDriver */

vevent2sysMacDriverClass           *vevent2sysMacDriverClassGetDefault
    (void                                 );

vevent2DriverClass                 *vevent2sysMacDriverClassAsDriverClass
    (vevent2sysMacDriverClass            *pClass);

vbool                               vevent2sysMacDriverClassValidate
    (vevent2sysMacDriverClass            *pClass);

void                                vevent2sysMacDriverClassAssert
    (vevent2sysMacDriverClass            *pClass);

void                                vevent2sysMacDriverClassHandledAssert
    (vevent2sysMacDriverClass            *pClass,
     vdebugAssertionHandler               handler,
     void                                *pData);

vevent2sysMacDriver                *vevent2sysMacDriverGetCurrent
    (void                                 );

vevent2sysMacDriver                *vevent2sysMacDriverCreate
    (void                                 );

vevent2sysMacDriver                *vevent2sysMacDriverCreateOfClass
    (vevent2sysMacDriverClass            *pClass);

void                                vevent2sysMacDriverRelease
    (vevent2sysMacDriver                 *pDriver);

void                                vevent2sysMacDriverSetHandlerProc
    (vevent2sysMacDriver                 *pDriver,
     vevent2sysMacHandlerProc            *pHandlerProc);

vevent2sysMacHandlerProc           *vevent2sysMacDriverGetHandlerProc
    (vevent2sysMacDriver                 *pDriver);

vevent2Driver                      *vevent2sysMacDriverAsDriver
    (vevent2sysMacDriver                 *pDriver);

vevent2sysMacDriverClass           *vevent2sysMacDriverGetClass
    (vevent2sysMacDriver                 *pDriver);

vbool                               vevent2sysMacDriverValidate
    (vevent2sysMacDriver                 *pDriver);

void                                vevent2sysMacDriverAssert
    (vevent2sysMacDriver                 *pDriver);

void                                vevent2sysMacDriverHandledAssert
    (vevent2sysMacDriver                 *pDriver,
     vdebugAssertionHandler               handler,
     void                                *pData);

#endif /* #if (vportOS_MAC) */


/*
 * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * *
 */

#if (vportOS_UNIX)

typedef veventFD _vevent2sysUnixFD;

struct vevent2sysUnixSystemHandler
{
    vevent2SystemEventHandler             super;
    _vevent2sysUnixFD                    *pFD;
    int                                   FDMaxPlusOne;
    fd_set                                readFDs;
    fd_set                                writeFDs;
    fd_set                                exceptFDs;
    volatile int                          piped;
#if (vdebugDEBUG)
    int                                   signature;
#endif
};

#define vevent2sysUnixSystemHandlerCLASS(CLASS, HANDLER)                    \
    vevent2SystemEventHandlerCLASS(CLASS, HANDLER);                         \
    vclassMETHOD(vevent2sysUnixSystemHandlerSET_SELECT_NOTIFY_DATA,         \
                 (HANDLER *pHandler, int fd, const void *pData));           \
    vclassMETHOD_RET(vevent2sysUnixSystemHandlerGET_SELECT_NOTIFY_DATA,     \
                     void *, (HANDLER *pHandler, int fd));                  \
    vclassMETHOD(vevent2sysUnixSystemHandlerSET_SELECT_READ_NOTIFY,         \
                 (HANDLER *pHandler, int fd,                                \
                  vevent2sysUnixSelectNotifyProc *p));                      \
    vclassMETHOD_RET(vevent2sysUnixSystemHandlerGET_SELECT_READ_NOTIFY,     \
                     vevent2sysUnixSelectNotifyProc *,                      \
                     (HANDLER *pHandler, int fd));                          \
    vclassMETHOD(vevent2sysUnixSystemHandlerSET_SELECT_WRITE_NOTIFY,        \
                 (HANDLER *pHandler, int fd,                                \
                  vevent2sysUnixSelectNotifyProc *p));                      \
    vclassMETHOD_RET(vevent2sysUnixSystemHandlerGET_SELECT_WRITE_NOTIFY,    \
                     vevent2sysUnixSelectNotifyProc *,                      \
                     (HANDLER *pHandler, int fd));                          \
    vclassMETHOD(vevent2sysUnixSystemHandlerSET_SELECT_EXCEPT_NOTIFY,       \
                 (HANDLER *pHandler, int fd,                                \
                  vevent2sysUnixSelectNotifyProc *p));                      \
    vclassMETHOD_RET(vevent2sysUnixSystemHandlerGET_SELECT_EXCEPT_NOTIFY,   \
                     vevent2sysUnixSelectNotifyProc *,                      \
                     (HANDLER *pHandler, int fd))

struct vevent2sysUnixSystemHandlerClass
{
    vevent2sysUnixSystemHandlerCLASS(vevent2sysUnixSystemHandlerClass,
                                     vevent2sysUnixSystemHandler);
};

struct vevent2sysUnixDriver
{
    vevent2Driver                         super;
    vevent2sysUnixSystemHandler          *pSystemHandler;
    vevent2sysXHandlerProc               *pXHandlerProc;
    int                                   pipe0;
    int                                   pipe1;
#if (vdebugDEBUG)
    int                                   signature;
#endif
};

#define vevent2sysUnixDriverCLASS(CLASS, DRIVER)                            \
    vevent2DriverCLASS(CLASS, DRIVER);                                      \
    vclassMETHOD(vevent2sysUnixDriverSET_X_HANDLER_PROC,                    \
                 (DRIVER *pDriver, vevent2sysXHandlerProc p));              \
    vclassMETHOD_RET(vevent2sysUnixDriverGET_X_HANDLER_PROC,                \
                     vevent2sysXHandlerProc *, (DRIVER *pDriver))

struct vevent2sysUnixDriverClass
{
    vevent2sysUnixDriverCLASS(vevent2sysUnixDriverClass, vevent2sysUnixDriver);
};

#endif /* #if (vportOS_UNIX) */

#if (vportOS_WIN32S)

struct vevent2sysWin32SystemHandler
{
    vevent2SystemEventHandler             super;
#if (vdebugDEBUG)
    int                                   signature;
#endif
};

#define vevent2sysWin32SystemHandlerCLASS(CLASS, HANDLER) \
    vevent2SystemEventHandlerCLASS(CLASS, HANDLER)

struct vevent2sysWin32SystemHandlerClass
{
    vevent2sysWin32SystemHandlerCLASS(vevent2sysWin32SystemHandlerClass,
                                      vevent2sysWin32SystemHandler);
};

struct vevent2sysWin32Driver
{
    vevent2Driver                         super;
    vevent2sysWin32SystemHandler         *pSystemHandler;
    vevent2sysWin32HandlerProc           *pHandlerProc;
    DWORD                                 threadID;
#if (vdebugDEBUG)
    int                                   signature;
#endif
};

#define vevent2sysWin32DriverCLASS(CLASS, DRIVER) \
    vevent2DriverCLASS(CLASS, DRIVER)

struct vevent2sysWin32DriverClass
{
    vevent2sysWin32DriverCLASS(vevent2sysWin32DriverClass,
                               vevent2sysWin32Driver);
};

#endif /* #if (vportOS_WIN32S) */

#if (vportOS_OS2)

struct vevent2sysOS2SystemHandler
{
    vevent2SystemEventHandler             super;
    vevent2sysOS2HandlerProc             *pHandlerProc;
#if (vdebugDEBUG)
    int                                   signature;
#endif
};

#define vevent2sysOS2SystemHandlerCLASS(CLASS, HANDLER) \
    vevent2SystemEventHandlerCLASS(CLASS, HANDLER)

struct vevent2sysOS2SystemHandlerClass
{
    vevent2sysOS2SystemHandlerCLASS(vevent2sysOS2SystemHandlerClass,
                                      vevent2sysOS2SystemHandler);
};

struct vevent2sysOS2Driver
{
    vevent2Driver                         super;
    vevent2sysOS2SystemHandler           *pSystemHandler;
    HMQ                                   hMsgQueue;
#if (vdebugDEBUG)
    int                                   signature;
#endif
};

#define vevent2sysOS2DriverCLASS(CLASS, DRIVER) \
    vevent2DriverCLASS(CLASS, DRIVER)

struct vevent2sysOS2DriverClass
{
    vevent2sysOS2DriverCLASS(vevent2sysOS2DriverClass, vevent2sysOS2Driver);
};

#endif /* #if (vportOS_OS2) */

#if (vportOS_MAC)

struct vevent2sysMacSystemHandler
{
    vevent2SystemEventHandler             super;
#if (vdebugDEBUG)
    int                                   signature;
#endif
};

#define vevent2sysMacSystemHandlerCLASS(CLASS, HANDLER) \
    vevent2SystemEventHandlerCLASS(CLASS, HANDLER)

struct vevent2sysMacSystemHandlerClass
{
    vevent2sysMacSystemHandlerCLASS(vevent2sysMacSystemHandlerClass,
                                      vevent2sysMacSystemHandler);
};

struct vevent2sysMacDriver
{
    vevent2Driver                         super;
    vevent2sysMacSystemHandler           *pSystemHandler;
    vevent2sysMacHandlerProc             *pMacHandlerProc;
    vmutex                               pWaitEventMutex;
    vcondition                           pWaitEventCondition;
#if (vdebugDEBUG)
    int                                   signature;
#endif
};

#define vevent2sysMacDriverCLASS(CLASS, DRIVER) \
    vevent2DriverCLASS(CLASS, DRIVER); \
    vclassMETHOD(vevent2sysMacDriverSET_MAC_HANDLER_PROC, \
                 (DRIVER *pDriver, vevent2sysMacHandlerProc *p)); \
    vclassMETHOD_RET(vevent2sysMacDriverGET_MAC_HANDLER_PROC, \
                     vevent2sysMacHandlerProc *, (DRIVER *pDriver));

struct vevent2sysMacDriverClass
{
    vevent2sysMacDriverCLASS(vevent2sysMacDriverClass, vevent2sysMacDriver);
};

#endif /* #if (vportOS_MAC) */


/*
 * * * * * * * * * * PRIVATE exported variables * * * * * * * * * *
 */

#if (vportWIN_X11)
extern vportLINK vevent2sysXHandlerProc    *_vevent2sysXHandlerProc;
#endif


/*
 * * * * * * * * * * PRIVATE exported prototypes * * * * * * * * * *
 */

#if (vportOS_UNIX)

void                             _vevent2sysUnixSystemHandlerClassHandledAssert
    (vevent2sysUnixSystemHandlerClass    *pClass,
     vdebugAssertionHandler               handler,
     void                                *pData,
     const char                          *tag,
     const char                          *file,
     int                                  line);

void                                _vevent2sysUnixSystemHandlerHandledAssert
    (vevent2sysUnixSystemHandler         *pHandler,
     vdebugAssertionHandler               handler,
     void                                *pData,
     const char                          *tag,
     const char                          *file,
     int                                  line);

void                                _vevent2sysUnixDriverClassHandledAssert
    (vevent2sysUnixDriverClass           *pClass,
     vdebugAssertionHandler               handler,
     void                                *pData,
     const char                          *tag,
     const char                          *file,
     int                                  line);

void                                _vevent2sysUnixDriverHandledAssert
    (vevent2sysUnixDriver                *pDriver,
     vdebugAssertionHandler               handler,
     void                                *pData,
     const char                          *tag,
     const char                          *file,
     int                                  line);

#endif /* #if (vportOS_UNIX) */

#if (vportOS_WIN32S)

void                            _vevent2sysWin32SystemHandlerClassHandledAssert
    (vevent2sysWin32SystemHandlerClass   *pClass,
     vdebugAssertionHandler               handler,
     void                                *pData,
     const char                          *tag,
     const char                          *file,
     int                                  line);

void                                _vevent2sysWin32SystemHandlerHandledAssert
    (vevent2sysWin32SystemHandler        *pHandler,
     vdebugAssertionHandler               handler,
     void                                *pData,
     const char                          *tag,
     const char                          *file,
     int                                  line);

void                                _vevent2sysWin32DriverClassHandledAssert
    (vevent2sysWin32DriverClass          *pClass,
     vdebugAssertionHandler               handler,
     void                                *pData,
     const char                          *tag,
     const char                          *file,
     int                                  line);

void                                _vevent2sysWin32DriverHandledAssert
    (vevent2sysWin32Driver               *pDriver,
     vdebugAssertionHandler               handler,
     void                                *pData,
     const char                          *tag,
     const char                          *file,
     int                                  line);

#endif /* #if (vportOS_WIN32S) */

#if (vportOS_OS2)

void                              _vevent2sysOS2SystemHandlerClassHandledAssert
    (vevent2sysOS2SystemHandlerClass     *pClass,
     vdebugAssertionHandler               handler,
     void                                *pData,
     const char                          *tag,
     const char                          *file,
     int                                  line);

void                                _vevent2sysOS2SystemHandlerHandledAssert
    (vevent2sysOS2SystemHandler          *pSystemHandler,
     vdebugAssertionHandler               handler,
     void                                *pData,
     const char                          *tag,
     const char                          *file,
     int                                  line);

void                                _vevent2sysOS2DriverClassHandledAssert
    (vevent2sysOS2DriverClass            *pClass,
     vdebugAssertionHandler               handler,
     void                                *pData,
     const char                          *tag,
     const char                          *file,
     int                                  line);

void                                _vevent2sysOS2DriverHandledAssert
    (vevent2sysOS2Driver                 *pDriver,
     vdebugAssertionHandler               handler,
     void                                *pData,
     const char                          *tag,
     const char                          *file,
     int                                  line);

#endif /* #if (vportOS_OS2) */

#if (vportOS_MAC)

void                              _vevent2sysMacSystemHandlerClassHandledAssert
    (vevent2sysMacSystemHandlerClass     *pClass,
     vdebugAssertionHandler               handler,
     void                                *pData,
     const char                          *tag,
     const char                          *file,
     int                                  line);

void                                _vevent2sysMacSystemHandlerHandledAssert
    (vevent2sysMacSystemHandler          *pSystemHandler,
     vdebugAssertionHandler               handler,
     void                                *pData,
     const char                          *tag,
     const char                          *file,
     int                                  line);

void                                _vevent2sysMacDriverClassHandledAssert
    (vevent2sysMacDriverClass            *pClass,
     vdebugAssertionHandler               handler,
     void                                *pData,
     const char                          *tag,
     const char                          *file,
     int                                  line);

void                                _vevent2sysMacDriverHandledAssert
    (vevent2sysMacDriver                 *pDriver,
     vdebugAssertionHandler               handler,
     void                                *pData,
     const char                          *tag,
     const char                          *file,
     int                                  line);

#endif /* #if (vportOS_MAC) */


/*
 * * * * * * * * * * PRIVATE function macro definitions * * * * * * * * * *
 */

vportBEGIN_MUST_BE_MACRO

#if (vportOS_UNIX)

#define vevent2sysUnixSystemHandlerClassHandledAssert(l, h, d) \
    _vevent2sysUnixSystemHandlerClassHandledAssert(l, h, d, vdebugTAG, \
                                                   __FILE__, __LINE__)

#define vevent2sysUnixSystemHandlerHandledAssert(l, h, d) \
    _vevent2sysUnixSystemHandlerHandledAssert(l, h, d, vdebugTAG, \
                                              __FILE__, __LINE__)

#define vevent2sysUnixDriverClassHandledAssert(l, h, d) \
    _vevent2sysUnixDriverClassHandledAssert(l, h, d, vdebugTAG, \
                                            __FILE__, __LINE__)

#define vevent2sysUnixDriverHandledAssert(l, h, d) \
    _vevent2sysUnixDriverHandledAssert(l, h, d, vdebugTAG, __FILE__, __LINE__)

#if (vdebugDEBUG)

#define vevent2sysUnixSystemHandlerClassAssert(l) \
    vevent2sysUnixSystemHandlerClassHandledAssert((l), NULL, NULL)

#define vevent2sysUnixSystemHandlerAssert(l) \
    vevent2sysUnixSystemHandlerHandledAssert((l), NULL, NULL)

#define vevent2sysUnixDriverClassAssert(l) \
    vevent2sysUnixDriverClassHandledAssert((l), NULL, NULL)

#define vevent2sysUnixDriverAssert(l) \
    vevent2sysUnixDriverHandledAssert((l), NULL, NULL)

#else /* #if (vdebugDEBUG) */

#define vevent2sysUnixSystemHandlerClassAssert(l) \
    ((void)0)

#define vevent2sysUnixSystemHandlerAssert(l) \
    ((void)0)

#define vevent2sysUnixDriverClassAssert(l) \
    ((void)0)

#define vevent2sysUnixDriverAssert(l) \
    ((void)0)

#endif

/* class vevent2sysUnixDriver */

#define vevent2sysUnixDriverAsDriver(l) \
    vportBASE_OBJECT(l, super)

#define vevent2sysUnixDriverGetClass(l) \
    ((vevent2sysUnixDriverClass *) \
     vevent2DriverGetClass(vevent2sysUnixDriverAsDriver(l)))

#define vevent2sysUnixDriverClassAsDriverClass(c) \
    (vevent2sysUnixDriverClassAssert(c), (vevent2DriverClass *)(c))

#define vevent2sysUnixDriverGetCurrent() \
    ((vevent2sysUnixDriver *)vevent2LoopGetDriver(vevent2LoopGetCurrent()))

#define vevent2sysUnixDriverOfLoop(l) \
    ((vevent2sysUnixDriver *)vevent2LoopGetDriver(l))

#define vevent2sysUnixDriverCreateOfClass(c) \
    ((vevent2sysUnixDriver *) \
     vevent2DriverCreateOfClass(vevent2sysUnixDriverClassAsDriverClass(c)))

#define vevent2sysUnixDriverCreate() \
    vevent2sysUnixDriverCreateOfClass(vevent2sysUnixDriverClassGetDefault())

#define vevent2sysUnixDriverInitOfClass(l,c) \
    vevent2DriverInitOfClass(vevent2sysUnixDriverAsDriver(l), \
                  vevent2sysUnixDriverClassAsDriverClass(c))

#define vevent2sysUnixDriverInit(l) \
    vevent2sysUnixDriverInitOfClass(l, vevent2sysUnixDriverClassGetDefault())

#define vevent2sysUnixDriverRelease(l) \
    vevent2DriverRelease(vevent2sysUnixDriverAsDriver(l))

#define vevent2sysUnixDriverSetSystemHandler(d, h) \
    (vevent2sysUnixDriverAssert(d), vevent2SystemEventHandlerAssert(h), \
     (d)->pSystemHandler = (h))

#define vevent2sysUnixDriverGetSystemHandler(d) \
    (vevent2sysUnixDriverAssert(d), (d)->pSystemHandler)

/* class vevent2sysUnixSystemHandler */

#define vevent2sysUnixSystemHandlerAsSystemHandler(l) \
    vportBASE_OBJECT(l, super)

#define vevent2sysUnixSystemHandlerGetClass(l) \
    ((vevent2sysUnixSystemHandlerClass *)vevent2SystemEventHandlerGetClass \
     (vevent2sysUnixSystemHandlerAsSystemHandler(l)))

#define vevent2sysUnixSystemHandlerClassAsSystemHandlerClass(c) \
    (vevent2sysUnixSystemHandlerClassAssert(c), \
     (vevent2SystemEventHandlerClass *)(c))

#define vevent2sysUnixSystemHandlerGetCurrent() \
    vevent2sysUnixDriverGetSystemHandler(vevent2sysUnixDriverGetCurrent())

#define vevent2sysUnixSystemHandlerOfLoop(l) \
    vevent2sysUnixDriverGetSystemHandler(vevent2sysUnixDriverOfLoop(l))

#define vevent2sysUnixSystemHandlerCreateOfClass(c) \
    ((vevent2sysUnixSystemHandler *)vevent2SystemEventHandlerCreateOfClass \
     (vevent2sysUnixSystemHandlerClassAsSystemHandlerClass(c)))

#define vevent2sysUnixSystemHandlerCreate() \
    vevent2sysUnixSystemHandlerCreateOfClass \
    (vevent2sysUnixSystemHandlerClassGetDefault())

#define vevent2sysUnixSystemHandlerInitOfClass(l,c) \
    vevent2SystemEventHandlerInitOfClass \
    (vevent2sysUnixSystemHandlerAsSystemHandler(l), \
     vevent2sysUnixSystemHandlerClassAsSystemHandlerClass(c))

#define vevent2sysUnixSystemHandlerInit(l) \
    vevent2sysUnixSystemHandlerInitOfClass \
    (l, vevent2sysUnixSystemHandlerClassGetDefault())

#define vevent2sysUnixSystemHandlerRelease(l) \
    vevent2SystemEventHandlerRelease \
    (vevent2sysUnixSystemHandlerAsSystemHandler(l))

#endif /* #if (vportOS_UNIX) */

#if (vportWIN_X11)

#define vevent2sysXSetHandlerProc(p) \
    (void)(_vevent2sysXHandlerProc = (p))

#define vevent2sysXGetHandlerProc() \
    (_vevent2sysXHandlerProc)

#endif

#if (vportOS_WIN32S)

#define vevent2sysWin32SystemHandlerClassHandledAssert(l, h, d) \
    _vevent2sysWin32SystemHandlerClassHandledAssert(l, h, d, vdebugTAG, \
                                                    __FILE__, __LINE__)

#define vevent2sysWin32SystemHandlerHandledAssert(l, h, d) \
    _vevent2sysWin32SystemHandlerHandledAssert(l, h, d, vdebugTAG, \
                                               __FILE__, __LINE__)

#define vevent2sysWin32DriverClassHandledAssert(l, h, d) \
    _vevent2sysWin32DriverClassHandledAssert(l, h, d, vdebugTAG, \
                                           __FILE__, __LINE__)

#define vevent2sysWin32DriverHandledAssert(l, h, d) \
    _vevent2sysWin32DriverHandledAssert(l, h, d, vdebugTAG, __FILE__, __LINE__)

#if (vdebugDEBUG)

#define vevent2sysWin32SystemHandlerClassAssert(l) \
    vevent2sysWin32SystemHandlerClassHandledAssert((l), NULL, NULL)

#define vevent2sysWin32SystemHandlerAssert(l) \
    vevent2sysWin32SystemHandlerHandledAssert((l), NULL, NULL)

#define vevent2sysWin32DriverClassAssert(l) \
    vevent2sysWin32DriverClassHandledAssert((l), NULL, NULL)

#define vevent2sysWin32DriverAssert(l) \
    vevent2sysWin32DriverHandledAssert((l), NULL, NULL)

#else /* #if (vdebugDEBUG) */

#define vevent2sysWin32SystemHandlerClassAssert(l) \
    ((void)0)

#define vevent2sysWin32SystemHandlerAssert(l) \
    ((void)0)

#define vevent2sysWin32DriverClassAssert(l) \
    ((void)0)

#define vevent2sysWin32DriverAssert(l) \
    ((void)0)

#endif

/* class vevent2sysWin32Driver */

#define vevent2sysWin32DriverAsDriver(l) \
    vportBASE_OBJECT(l, super)

#define vevent2sysWin32DriverGetClass(l) \
    ((vevent2sysWin32DriverClass *) \
     vevent2DriverGetClass(vevent2sysWin32DriverAsDriver(l)))

#define vevent2sysWin32DriverClassAsDriverClass(c) \
    (vevent2sysWin32DriverClassAssert(c), (vevent2DriverClass *)(c))

#define vevent2sysWin32DriverGetCurrent() \
    ((vevent2sysWin32Driver *)vevent2LoopGetDriver(vevent2LoopGetCurrent()))

#define vevent2sysWin32DriverOfLoop(l) \
    ((vevent2sysWin32Driver *)vevent2LoopGetDriver(l))

#define vevent2sysWin32DriverCreateOfClass(c) \
    ((vevent2sysWin32Driver *) \
     vevent2DriverCreateOfClass(vevent2sysWin32DriverClassAsDriverClass(c)))

#define vevent2sysWin32DriverCreate() \
    vevent2sysWin32DriverCreateOfClass(vevent2sysWin32DriverClassGetDefault())

#define vevent2sysWin32DriverInitOfClass(l,c) \
    vevent2DriverInitOfClass(vevent2sysWin32DriverAsDriver(l), \
                             vevent2sysWin32DriverClassAsDriverClass(c))

#define vevent2sysWin32DriverInit(l) \
    vevent2sysWin32DriverInitOfClass(l, vevent2sysWin32DriverClassGetDefault())

#define vevent2sysWin32DriverRelease(l) \
    vevent2DriverRelease(vevent2sysWin32DriverAsDriver(l))

#define vevent2sysWin32DriverSetSystemHandler(d, h) \
    (vevent2sysWin32DriverAssert(d), vevent2SystemEventHandlerAssert(h), \
     (d)->pSystemHandler = (h))

#define vevent2sysWin32DriverGetSystemHandler(d) \
    (vevent2sysWin32DriverAssert(d), (d)->pSystemHandler)

/* class vevent2sysWin32SystemHandler */

#define vevent2sysWin32SystemHandlerAsSystemHandler(l) \
    vportBASE_OBJECT(l, super)

#define vevent2sysWin32SystemHandlerGetClass(l) \
    ((vevent2sysWin32SystemHandlerClass *)vevent2SystemEventHandlerGetClass \
     (vevent2sysWin32SystemHandlerAsSystemHandler(l)))

#define vevent2sysWin32SystemHandlerClassAsSystemHandlerClass(c) \
    (vevent2sysWin32SystemHandlerClassAssert(c), \
     (vevent2SystemEventHandlerClass *)(c))

#define vevent2sysWin32SystemHandlerGetCurrent() \
    vevent2sysWin32DriverGetSystemHandler(vevent2sysWin32DriverGetCurrent())

#define vevent2sysWin32SystemHandlerOfLoop(l) \
    vevent2sysWin32DriverGetSystemHandler(vevent2sysWin32DriverOfLoop(l))

#define vevent2sysWin32SystemHandlerCreateOfClass(c) \
    ((vevent2sysWin32SystemHandler *)vevent2SystemEventHandlerCreateOfClass \
     (vevent2sysWin32SystemHandlerClassAsSystemHandlerClass(c)))

#define vevent2sysWin32SystemHandlerCreate() \
    vevent2sysWin32SystemHandlerCreateOfClass \
    (vevent2sysWin32SystemHandlerClassGetDefault())

#define vevent2sysWin32SystemHandlerInitOfClass(l,c) \
    vevent2SystemEventHandlerInitOfClass \
    (vevent2sysWin32SystemHandlerAsSystemHandler(l), \
     vevent2sysWin32SystemHandlerClassAsSystemHandlerClass(c))

#define vevent2sysWin32SystemHandlerInit(l) \
    vevent2sysWin32SystemHandlerInitOfClass \
    (l, vevent2sysWin32SystemHandlerClassGetDefault())

#define vevent2sysWin32SystemHandlerRelease(l) \
    vevent2SystemEventHandlerRelease \
    (vevent2sysWin32SystemHandlerAsSystemHandler(l))

#endif /* #if (vportOS_WIN32S) */

#if (vportOS_OS2)

#define vevent2sysOS2SystemHandlerClassHandledAssert(l, h, d) \
    _vevent2sysOS2SystemHandlerClassHandledAssert(l, h, d, vdebugTAG, \
                                                  __FILE__, __LINE__)

#define vevent2sysOS2SystemHandlerHandledAssert(l, h, d) \
    _vevent2sysOS2SystemHandlerHandledAssert(l, h, d, vdebugTAG, \
                                             __FILE__, __LINE__)

#define vevent2sysOS2DriverClassHandledAssert(l, h, d) \
    _vevent2sysOS2DriverClassHandledAssert(l, h, d, vdebugTAG, \
                                          __FILE__, __LINE__)

#define vevent2sysOS2DriverHandledAssert(l, h, d) \
    _vevent2sysOS2DriverHandledAssert(l, h, d, vdebugTAG, __FILE__, __LINE__)

#if (vdebugDEBUG)

#define vevent2sysOS2SystemHandlerClassAssert(l) \
    vevent2sysOS2SystemHandlerClassHandledAssert((l), NULL, NULL)

#define vevent2sysOS2SystemHandlerAssert(l) \
    vevent2sysOS2SystemHandlerHandledAssert((l), NULL, NULL)

#define vevent2sysOS2DriverClassAssert(l) \
    vevent2sysOS2DriverClassHandledAssert((l), NULL, NULL)

#define vevent2sysOS2DriverAssert(l) \
    vevent2sysOS2DriverHandledAssert((l), NULL, NULL)

#else /* #if (vdebugDEBUG) */

#define vevent2sysOS2SystemHandlerClassAssert(l) \
    ((void)0)

#define vevent2sysOS2SystemHandlerAssert(l) \
    ((void)0)

#define vevent2sysOS2DriverClassAssert(l) \
    ((void)0)

#define vevent2sysOS2DriverAssert(l) \
    ((void)0)

#endif

/* class vevent2sysOS2Driver */

#define vevent2sysOS2DriverAsDriver(l) \
    vportBASE_OBJECT(l, super)

#define vevent2sysOS2DriverGetClass(l) \
    ((vevent2sysOS2DriverClass *) \
     vevent2DriverGetClass(vevent2sysOS2DriverAsDriver(l)))

#define vevent2sysOS2DriverClassAsDriverClass(c) \
    (vevent2sysOS2DriverClassAssert(c), (vevent2DriverClass *)(c))

#define vevent2sysOS2DriverGetCurrent() \
    ((vevent2sysOS2Driver *)vevent2LoopGetDriver(vevent2LoopGetCurrent()))

#define vevent2sysOS2DriverOfLoop(l) \
    ((vevent2sysOS2Driver *)vevent2LoopGetDriver(l))

#define vevent2sysOS2DriverCreateOfClass(c) \
    ((vevent2sysOS2Driver *) \
     vevent2DriverCreateOfClass(vevent2sysOS2DriverClassAsDriverClass(c)))

#define vevent2sysOS2DriverCreate() \
    vevent2sysOS2DriverCreateOfClass(vevent2sysOS2DriverClassGetDefault())

#define vevent2sysOS2DriverInitOfClass(l,c) \
    vevent2DriverInitOfClass(vevent2sysOS2DriverAsDriver(l), \
                             vevent2sysOS2DriverClassAsDriverClass(c))

#define vevent2sysOS2DriverInit(l) \
    vevent2sysOS2DriverInitOfClass(l, vevent2sysOS2DriverClassGetDefault())

#define vevent2sysOS2DriverRelease(l) \
    vevent2DriverRelease(vevent2sysOS2DriverAsDriver(l))

#define vevent2sysOS2DriverSetSystemHandler(d, h) \
    (vevent2sysOS2DriverAssert(d), vevent2SystemEventHandlerAssert(h), \
     (d)->pSystemHandler = (h))

#define vevent2sysOS2DriverGetSystemHandler(d) \
    (vevent2sysOS2DriverAssert(d), (d)->pSystemHandler)

/* class vevent2sysOS2SystemHandler */

#define vevent2sysOS2SystemHandlerAsSystemHandler(l) \
    vportBASE_OBJECT(l, super)

#define vevent2sysOS2SystemHandlerGetClass(l) \
    ((vevent2sysOS2SystemHandlerClass *)vevent2SystemEventHandlerGetClass \
     (vevent2sysOS2SystemHandlerAsSystemHandler(l)))

#define vevent2sysOS2SystemHandlerClassAsSystemHandlerClass(c) \
    (vevent2sysOS2SystemHandlerClassAssert(c), \
     (vevent2SystemEventHandlerClass *)(c))

#define vevent2sysOS2SystemHandlerGetCurrent() \
    vevent2sysOS2DriverGetSystemHandler(vevent2sysOS2DriverGetCurrent())

#define vevent2sysOS2SystemHandlerOfLoop(l) \
    vevent2sysOS2DriverGetSystemHandler(vevent2sysOS2DriverOfLoop(l))

#define vevent2sysOS2SystemHandlerCreateOfClass(c) \
    ((vevent2sysOS2SystemHandler *)vevent2SystemEventHandlerCreateOfClass \
     (vevent2sysOS2SystemHandlerClassAsSystemHandlerClass(c)))

#define vevent2sysOS2SystemHandlerCreate() \
    vevent2sysOS2SystemHandlerCreateOfClass \
    (vevent2sysOS2SystemHandlerClassGetDefault())

#define vevent2sysOS2SystemHandlerInitOfClass(l,c) \
    (vevent2SystemEventHandlerInitOfClass \
     (vevent2sysOS2SystemHandlerAsSystemHandler(l), \
      vevent2sysOS2SystemHandlerClassAsSystemHandlerClass(c)))

#define vevent2sysOS2SystemHandlerInit(l) \
    vevent2sysOS2SystemHandlerInitOfClass \
        (l, vevent2sysOS2SystemHandlerClassGetDefault())

#define vevent2sysOS2SystemHandlerRelease(l) \
    vevent2SystemEventHandlerRelease \
    (vevent2sysOS2SystemHandlerAsSystemHandler(l))

#endif

#if (vportOS_MAC)

#define vevent2sysMacSystemHandlerClassHandledAssert(l, h, d) \
    _vevent2sysMacSystemHandlerClassHandledAssert(l, h, d, vdebugTAG, \
                                                  __FILE__, __LINE__)

#define vevent2sysMacSystemHandlerHandledAssert(l, h, d) \
    _vevent2sysMacSystemHandlerHandledAssert(l, h, d, vdebugTAG, \
                                             __FILE__, __LINE__)

#define vevent2sysMacDriverClassHandledAssert(l, h, d) \
    _vevent2sysMacDriverClassHandledAssert(l, h, d, vdebugTAG, \
                                           __FILE__, __LINE__)

#define vevent2sysMacDriverHandledAssert(l, h, d) \
    _vevent2sysMacDriverHandledAssert(l, h, d, vdebugTAG, __FILE__, __LINE__)

#if (vdebugDEBUG)

#define vevent2sysMacSystemHandlerClassAssert(l) \
    vevent2sysMacSystemHandlerClassHandledAssert((l), NULL, NULL)

#define vevent2sysMacSystemHandlerAssert(l) \
    vevent2sysMacSystemHandlerHandledAssert((l), NULL, NULL)

#define vevent2sysMacDriverClassAssert(l) \
    vevent2sysMacDriverClassHandledAssert((l), NULL, NULL)

#define vevent2sysMacDriverAssert(l) \
    vevent2sysMacDriverHandledAssert((l), NULL, NULL)

#else /* #if (vdebugDEBUG) */

#define vevent2sysMacSystemHandlerClassAssert(l) \
    ((void)0)

#define vevent2sysMacSystemHandlerAssert(l) \
    ((void)0)

#define vevent2sysMacDriverClassAssert(l) \
    ((void)0)

#define vevent2sysMacDriverAssert(l) \
    ((void)0)

#endif

/* class vevent2sysMacDriver */

#define vevent2sysMacDriverAsDriver(l) \
    vportBASE_OBJECT(l, super)

#define vevent2sysMacDriverGetClass(l) \
    ((vevent2sysMacDriverClass *) \
     vevent2DriverGetClass(vevent2sysMacDriverAsDriver(l)))

#define vevent2sysMacDriverClassAsDriverClass(c) \
    (vevent2sysMacDriverClassAssert(c), (vevent2DriverClass *)(c))

#define vevent2sysMacDriverGetCurrent() \
    ((vevent2sysMacDriver *)vevent2LoopGetDriver(vevent2LoopGetCurrent()))

#define vevent2sysMacDriverOfLoop(l) \
    ((vevent2sysMacDriver *)vevent2LoopGetDriver(l))

#define vevent2sysMacDriverCreateOfClass(c) \
    ((vevent2sysMacDriver *) \
     vevent2DriverCreateOfClass(vevent2sysMacDriverClassAsDriverClass(c)))

#define vevent2sysMacDriverCreate() \
    vevent2sysMacDriverCreateOfClass(vevent2sysMacDriverClassGetDefault())

#define vevent2sysMacDriverInitOfClass(l,c) \
    vevent2DriverInitOfClass(vevent2sysMacDriverAsDriver(l), \
                             vevent2sysMacDriverClassAsDriverClass(c))

#define vevent2sysMacDriverInit(l) \
    vevent2sysMacDriverInitOfClass(l, vevent2sysMacDriverClassGetDefault())

#define vevent2sysMacDriverRelease(l) \
    vevent2DriverRelease(vevent2sysMacDriverAsDriver(l))

#define vevent2sysMacDriverSetSystemHandler(d, h) \
    (vevent2sysMacDriverAssert(d), vevent2SystemEventHandlerAssert(h), \
     (d)->pSystemHandler = (h))

#define vevent2sysMacDriverGetSystemHandler(d) \
    (vevent2sysMacDriverAssert(d), (d)->pSystemHandler)

/* class vevent2sysMacSystemHandler */

#define vevent2sysMacSystemHandlerAsSystemHandler(l) \
    vportBASE_OBJECT(l, super)

#define vevent2sysMacSystemHandlerGetClass(l) \
    ((vevent2sysMacSystemHandlerClass *)vevent2SystemEventHandlerGetClass \
     (vevent2sysMacSystemHandlerAsSystemHandler(l)))

#define vevent2sysMacSystemHandlerClassAsSystemHandlerClass(c) \
    (vevent2sysMacSystemHandlerClassAssert(c), \
     (vevent2SystemEventHandlerClass *)(c))

#define vevent2sysMacSystemHandlerGetCurrent() \
    vevent2sysMacDriverGetSystemHandler(vevent2sysMacDriverGetCurrent())

#define vevent2sysMacSystemHandlerOfLoop(l) \
    vevent2sysMacDriverGetSystemHandler(vevent2sysMacDriverOfLoop(l))

#define vevent2sysMacSystemHandlerCreateOfClass(c) \
    ((vevent2sysMacSystemHandler *) \
     vevent2SystemEventHandlerCreateOfClass \
     (vevent2sysMacSystemHandlerClassAsSystemHandlerClass(c)))

#define vevent2sysMacSystemHandlerCreate() \
    vevent2sysMacSystemHandlerCreateOfClass \
    (vevent2sysMacSystemHandlerClassGetDefault())

#define vevent2sysMacSystemHandlerInitOfClass(l,c) \
    vevent2SystemEventHandlerInitOfClass \
    (vevent2sysMacSystemHandlerAsSystemHandler(l), \
     vevent2sysMacSystemHandlerClassAsSystemHandlerClass(c))

#define vevent2sysMacSystemHandlerInit(l) \
    vevent2sysMacSystemHandlerInitOfClass \
    (l, vevent2sysMacSystemHandlerClassGetDefault())

#define vevent2sysMacSystemHandlerRelease(l) \
    vevent2SystemEventHandlerRelease \
    (vevent2sysMacSystemHandlerAsSystemHandler(l))

#endif /* #if (vportOS_MAC) */

vportEND_MUST_BE_MACRO

/*
 * * * * * * * * * * PRIVATE function message definitions * * * * * * * * * *
 */

#if (vportOS_UNIX)

/* class vevent2sysUnixSystemHandler */

#define vevent2sysUnixSystemHandlerSetSelectNotifyData(l, fd, d) \
    vclassSend(vevent2sysUnixSystemHandlerGetClass(l), \
               vevent2sysUnixSystemHandlerSET_SELECT_NOTIFY_DATA, (l, fd, d))

#define vevent2sysUnixSystemHandlerGetSelectNotifyData(l, fd) \
    vclassSend(vevent2sysUnixSystemHandlerGetClass(l), \
               vevent2sysUnixSystemHandlerGET_SELECT_NOTIFY_DATA, (l, fd))

#define vevent2sysUnixSystemHandlerSetSelectReadNotify(l, fd, n) \
    vclassSend(vevent2sysUnixSystemHandlerGetClass(l), \
               vevent2sysUnixSystemHandlerSET_SELECT_READ_NOTIFY, (l, fd, n))

#define vevent2sysUnixSystemHandlerGetSelectReadNotify(l, fd) \
    vclassSend(vevent2sysUnixSystemHandlerGetClass(l), \
               vevent2sysUnixSystemHandlerGET_SELECT_READ_NOTIFY, (l, fd))

#define vevent2sysUnixSystemHandlerSetSelectWriteNotify(l, fd, n) \
    vclassSend(vevent2sysUnixSystemHandlerGetClass(l), \
               vevent2sysUnixSystemHandlerSET_SELECT_WRITE_NOTIFY, (l, fd, n))

#define vevent2sysUnixSystemHandlerGetSelectWriteNotify(l, fd) \
    vclassSend(vevent2sysUnixSystemHandlerGetClass(l), \
               vevent2sysUnixSystemHandlerGET_SELECT_WRITE_NOTIFY, (l, fd))

#define vevent2sysUnixSystemHandlerSetSelectExceptNotify(l, fd, n) \
    vclassSend(vevent2sysUnixSystemHandlerGetClass(l), \
               vevent2sysUnixSystemHandlerSET_SELECT_EXCEPT_NOTIFY, (l, fd, n))

#define vevent2sysUnixSystemHandlerGetSelectExceptNotify(l, fd) \
    vclassSend(vevent2sysUnixSystemHandlerGetClass(l), \
               vevent2sysUnixSystemHandlerGET_SELECT_EXCEPT_NOTIFY, (l, fd))

/* class vevent2sysUnixDriver */

#define vevent2sysUnixDriverAddSystemHandler(l, h) \
    vevent2DriverAddSystemEventHandler(vevent2sysUnixDriverAsDriver(l), h)

#define vevent2sysUnixDriverRemoveSystemHandler(l, h) \
    vevent2DriverRemoveSystemEventHandler(vevent2sysUnixDriverAsDriver(l), h)

#define vevent2sysUnixDriverAddPreBlocker(l, p) \
    vevent2DriverAddPreBlocker(vevent2sysUnixDriverAsDriver(l), p)

#define vevent2sysUnixDriverRemovePreBlocker(l, p) \
    vevent2DriverRemovePreBlocker(vevent2sysUnixDriverAsDriver(l), p)

#define vevent2sysUnixDriverPreBlock(l, s, n) \
    vevent2DriverPreBlock(vevent2sysUnixDriverAsDriver(l), s, n)

#define vevent2sysUnixDriverBlock(l, s, n) \
    vevent2DriverBlock(vevent2sysUnixDriverAsDriver(l), s, n)

#define vevent2sysUnixDriverHandleSystemEvents(l) \
    vevent2DriverHandleSystemEvents(vevent2sysUnixDriverAsDriver(l))

#define vevent2sysUnixDriverGoNative(l) \
    vevent2DriverGoNative(vevent2sysUnixDriverAsDriver(l))

#define vevent2sysUnixDriverSetXHandlerProc(l, h) \
    vclassSend(vevent2sysUnixDriverGetClass(l), \
               vevent2sysUnixDriverSET_X_HANDLER_PROC, (l, h))

#define vevent2sysUnixDriverGetXHandlerProc(l) \
    vclassSend(vevent2sysUnixDriverGetClass(l), \
               vevent2sysUnixDriverGET_X_HANDLER_PROC, (l))

#endif /* #if (vportOS_UNIX) */

#if (vportOS_WIN32S)

/* class vevent2sysWin32Driver */

#define vevent2sysWin32DriverPreBlock(l, s, n) \
    vevent2DriverPreBlock(vevent2sysWin32DriverAsDriver(l), s, n)

#define vevent2sysWin32DriverBlock(l, s, n) \
    vevent2DriverBlock(vevent2sysWin32DriverAsDriver(l), s, n)

#define vevent2sysWin32DriverHandleSystemEvents(l) \
    vevent2DriverHandleSystemEvents(vevent2sysWin32DriverAsDriver(l))

#define vevent2sysWin32DriverGoNative(l) \
    vevent2DriverGoNative(vevent2sysWin32DriverAsDriver(l))

#define vevent2sysWin32DriverAddSystemHandler(l, h) \
    vevent2DriverAddSystemEventHandler(vevent2sysWin32DriverAsDriver(l), h)

#define vevent2sysWin32DriverRemoveSystemHandler(l, h) \
    vevent2DriverRemoveSystemEventHandler(vevent2sysWin32DriverAsDriver(l), h)

#define vevent2sysWin32DriverAddPreBlocker(l, p) \
    vevent2DriverAddPreBlocker(vevent2sysWin32DriverAsDriver(l), p)

#define vevent2sysWin32DriverRemovePreBlocker(l, p) \
    vevent2DriverRemovePreBlocker(vevent2sysWin32DriverAsDriver(l), p)

#endif /* #if (vportOS_WIN32S) */

#if (vportOS_OS2)

/* class vevent2sysOS2Driver */

#define vevent2sysOS2DriverPreBlock(l, s, n) \
    vevent2DriverPreBlock(vevent2sysOS2DriverAsDriver(l), s, n)

#define vevent2sysOS2DriverBlock(l, s, n) \
    vevent2DriverBlock(vevent2sysOS2DriverAsDriver(l), s, n)

#define vevent2sysOS2DriverHandleSystemEvents(l) \
    vevent2DriverHandleSystemEvents(vevent2sysOS2DriverAsDriver(l))

#define vevent2sysOS2DriverGoNative(l) \
    vevent2DriverGoNative(vevent2sysOS2DriverAsDriver(l))

#define vevent2sysOS2DriverAddSystemHandler(l, h) \
    vevent2DriverAddSystemEventHandler(vevent2sysOS2DriverAsDriver(l), h)

#define vevent2sysOS2DriverRemoveSystemHandler(l, h) \
    vevent2DriverRemoveSystemEventHandler(vevent2sysOS2DriverAsDriver(l), h)

#define vevent2sysOS2DriverAddPreBlocker(l, p) \
    vevent2DriverAddPreBlocker(vevent2sysOS2DriverAsDriver(l), p)

#define vevent2sysOS2DriverRemovePreBlocker(l, p) \
    vevent2DriverRemovePreBlocker(vevent2sysOS2DriverAsDriver(l), p)

#endif /* #if (vportOS_OS2) */

#if (vportOS_MAC)

/* class vevent2sysMacDriver */

#define vevent2sysMacDriverPreBlock(l, s, n) \
    vevent2DriverPreBlock(vevent2sysMacDriverAsDriver(l), s, n)

#define vevent2sysMacDriverBlock(l, s, n) \
    vevent2DriverBlock(vevent2sysMacDriverAsDriver(l), s, n)

#define vevent2sysMacDriverHandleSystemEvents(l) \
    vevent2DriverHandleSystemEvents(vevent2sysMacDriverAsDriver(l))

#define vevent2sysMacDriverGoNative(l) \
    vevent2DriverGoNative(vevent2sysMacDriverAsDriver(l))

#define vevent2sysMacDriverAddSystemHandler(l, h) \
    vevent2DriverAddSystemEventHandler(vevent2sysMacDriverAsDriver(l), h)

#define vevent2sysMacDriverRemoveSystemHandler(l, h) \
    vevent2DriverRemoveSystemEventHandler(vevent2sysMacDriverAsDriver(l), h)

#define vevent2sysMacDriverAddPreBlocker(l, p) \
    vevent2DriverAddPreBlocker(vevent2sysMacDriverAsDriver(l), p)

#define vevent2sysMacDriverRemovePreBlocker(l, p) \
    vevent2DriverRemovePreBlocker(vevent2sysMacDriverAsDriver(l), p)

#define vevent2sysMacDriverSetHandlerProc(l, h) \
    vclassSend(vevent2sysMacDriverGetClass(l), \
               vevent2sysMacDriverSET_MAC_HANDLER_PROC, (l, h))

#define vevent2sysMacDriverGetHandlerProc(l) \
    vclassSend(vevent2sysMacDriverGetClass(l), \
               vevent2sysMacDriverGET_MAC_HANDLER_PROC, (l))

#endif /* #if (vportOS_MAC) */

vportEND_CPLUSPLUS_EXTERN_C

#endif /* #ifndef vevent2sysINCLUDED */


/*
 * Local Variables:
 * c-argdecl-indent:4
 * c-brace-imaginary-offset:0
 * c-brace-offset:-4
 * c-continued-brace-offset:0
 * c-continued-statement-offset:4
 * c-extra-brace-offset:0
 * c-file-offsets:((block-open . -))
 * c-file-style:"BSD"
 * c-indent-level:4
 * c-label-offset:-4
 * indent-tabs-mode:nil
 * tab-width:4
 * End:
 */


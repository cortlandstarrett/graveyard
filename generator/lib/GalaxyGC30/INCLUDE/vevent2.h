/* $Id: vevent2.h,v 1.83 1997/10/21 18:05:34 robert Exp $ */

#ifndef  vportINCLUDED      /* for v*HEADER */
#include <vport.h>
#endif

#ifndef  veventINCLUDED      /* for v*HEADER */
#include veventHEADER
#endif


#ifndef vevent2INCLUDED
#define vevent2INCLUDED 1

#ifndef  vportINCLUDED      /* for v*HEADER */
#include <vport.h>
#endif

#ifndef  vstdioINCLUDED
#include vstdioHEADER
#endif

#ifndef  vmutexINCLUDED
#include vmutexHEADER
#endif

#ifndef  vdictINCLUDED
#include vdictHEADER
#endif

#ifndef  vloadableINCLUDED
#include vloadableHEADER
#endif

#ifndef  vtimestampINCLUDED
#include vtimestampHEADER
#endif

#ifndef  vkeyINCLUDED
#include vkeyHEADER
#endif

#ifndef  vpointINCLUDED
#include vpointHEADER
#endif

#ifndef  vpqINCLUDED
#include vpqHEADER
#endif

#ifndef  viteratorINCLUDED
#include viteratorHEADER
#endif

/*

Java Class Names

Iterator/EventIterator
Loadable/Event
Loadable/Event/WindowEvent
Loadable/Event/WindowEvent/ConfigureEvent
Loadable/Event/WindowEvent/ConfigureEvent/WindowCloseEvent
Loadable/Event/WindowEvent/ConfigureEvent/WindowIconifyEvent
Loadable/Event/WindowEvent/ConfigureEvent/WindowMaximizeEvent
Loadable/Event/WindowEvent/ConfigureEvent/WindowOpenEvent
Loadable/Event/WindowEvent/ConfigureEvent/WindowPinEvent
Loadable/Event/WindowEvent/ConfigureEvent/WindowUniconifyEvent
Loadable/Event/WindowEvent/ConfigureEvent/WindowUnmaximizeEvent
Loadable/Event/WindowEvent/ConfigureEvent/WindowUnpinEvent
Loadable/Event/WindowEvent/FocusEvent
Loadable/Event/WindowEvent/FocusEvent/AcquireEvent
Loadable/Event/WindowEvent/FocusEvent/LoseEvent
Loadable/Event/WindowEvent/PointerEvent
Loadable/Event/WindowEvent/PointerEvent/ButtonEvent
Loadable/Event/WindowEvent/PointerEvent/ButtonEvent/ButtonDownEvent
Loadable/Event/WindowEvent/PointerEvent/ButtonEvent/ButtonUpEvent
Loadable/Event/WindowEvent/PointerEvent/EnterEvent
Loadable/Event/WindowEvent/PointerEvent/KeyEvent
Loadable/Event/WindowEvent/PointerEvent/KeyEvent/KeyDownEvent
Loadable/Event/WindowEvent/PointerEvent/KeyEvent/KeyUpEvent
Loadable/Event/WindowEvent/PointerEvent/LeaveEvent
Loadable/Event/WindowEvent/PointerEvent/MotionEvent
Loadable/Event/WindowEvent/StateEvent
Loadable/Event/WindowEvent/UpdateEvent
Loadable/Handler
Loadable/Handler/Loop
LoopDriver
PreBlocker
Quitter
SystemEventHandler

*/

vportBEGIN_CPLUSPLUS_EXTERN_C


/*
 * * * * * * * * * * * * * PUBLIC TYPES * * * * * * * * * * * * * *
 */

#if 0
/* defined in vevent.h */

typedef vbyte                                   vevent2Priority;
typedef unsigned int                            vevent2Type;
typedef vbyte                                   vevent2Button;

typedef vevent                                  vevent2;
typedef veventWindowEvent                       vevent2WindowEvent;
typedef veventWindowConfigureEvent              vevent2WindowConfigureEvent;
typedef veventWindowFocusEvent                  vevent2FocusEvent;
typedef veventWindowFocusAcquireEvent           vevent2FocusAcquireEvent;
typedef veventWindowFocusLoseEvent              vevent2FocusLoseEvent;
typedef veventWindowPointerEvent                vevent2PointerEvent;
typedef veventWindowPointerButtonEvent          vevent2ButtonEvent;
typedef veventWindowPointerButtonDownEvent      vevent2ButtonDownEvent;
typedef veventWindowPointerButtonUpEvent        vevent2ButtonUpEvent;
typedef veventWindowPointerEnterEvent           vevent2PointerEnterEvent;
typedef veventWindowKeyEvent                    vevent2KeyEvent;
typedef veventWindowKeyDownEvent                vevent2KeyDownEvent;
typedef veventWindowKeyUpEvent                  vevent2KeyUpEvent;
typedef veventWindowPointerLeaveEvent           vevent2PointerLeaveEvent;
typedef veventWindowPointerDragEvent            vevent2MotionEvent;
typedef veventWindowStateEvent                  vevent2WindowStateEvent;
typedef veventWindowUpdateEvent                 vevent2WindowUpdateEvent;

typedef struct vevent2Handler                   vevent2Handler;
typedef struct vevent2Loop                      vevent2Loop;
typedef struct vevent2Driver                    vevent2Driver;
typedef struct vevent2PreBlocker                vevent2PreBlocker;
typedef struct vevent2Quitter                   vevent2Quitter;
typedef struct vevent2SystemEventHandler        vevent2SystemEventHandler;

typedef struct vevent2Class                     vevent2Class;
typedef struct vevent2WindowEventClass          vevent2WindowEventClass;
typedef struct vevent2WindowConfigureEventClass
               vevent2WindowConfigureEventClass;
typedef struct vevent2FocusEventClass           vevent2FocusEventClass;
typedef struct vevent2FocusAcquireEventClass    vevent2FocusAcquireEventClass;
typedef struct vevent2FocusLoseEventClass       vevent2FocusLoseEventClass;
typedef struct vevent2PointerEventClass         vevent2PointerEventClass;
typedef struct vevent2ButtonEventClass          vevent2ButtonEventClass;
typedef struct vevent2ButtonDownEventClass      vevent2ButtonDownEventClass;
typedef struct vevent2ButtonUpEventClass        vevent2ButtonUpEventClass;
typedef struct vevent2PointerEnterEventClass    vevent2PointerEnterEventClass;
typedef struct vevent2KeyEventClass             vevent2KeyEventClass;
typedef struct vevent2KeyDownEventClass         vevent2KeyDownEventClass;
typedef struct vevent2KeyUpEventClass           vevent2KeyUpEventClass;
typedef struct vevent2PointerLeaveEventClass    vevent2PointerLeaveEventClass;
typedef struct vevent2MotionEventClass          vevent2MotionEventClass;
typedef struct vevent2WindowStateEventClass     vevent2WindowStateEventClass;
typedef struct vevent2WindowUpdateEventClass    vevent2WindowUpdateEventClass;
typedef struct vevent2HandlerClass              vevent2HandlerClass;
typedef struct vevent2LoopClass                 vevent2LoopClass;
typedef struct vevent2DriverClass               vevent2DriverClass;
typedef struct vevent2PreBlockerClass           vevent2PreBlockerClass;
typedef struct vevent2QuitterClass              vevent2QuitterClass;
typedef struct vevent2SystemEventHandlerClass   vevent2SystemEventHandlerClass;

typedef struct vevent2Iterator                  vevent2Iterator;
typedef struct vevent2IteratorClass             vevent2IteratorClass;

typedef int (_vevent2HandlerProc)(vevent2 *pEvent);

typedef void    (vevent2WaitProc)(long secs, unsigned long nanosecs);

#if (vportCPLUSPLUS_SOURCE)
#define _vevent2STRUCT              
class vportCLASS_LINK vwindow;
#else
#define _vevent2STRUCT struct
struct vwindow;
#endif

#endif /* defined in vevent.h */


/*
 * * * * * * * * * * * * * PUBLIC CONSTANTS * * * * * * * * * * * * * * *
 */

/* a higher priority event will take precedence over a lower priority
 * event iff both should have already been dispatched */

enum {
    vevent2PRIORITY_MIN         = 0x08,             /* later events */
    vevent2PRIORITY_LOW         = 0x30,             /* window updates */
    vevent2PRIORITY_SYSTEM      = 0x7c,             /* system events */
    vevent2PRIORITY_DEFAULT     = 0x7f,             /* most events */
    vevent2PRIORITY_HIGH        = 0xbf,             /* in a hurry */
    vevent2PRIORITY_MAX         = 0xf0              /* don't go no higher */
};

/*
 * vevent2Type
 * The odd ordering of the low number types is required for vevent bc
 */

enum {
    vevent2TYPE_UNKNOWN = 0,
    vevent2TYPE_BUTTON_DOWN = 1,
    vevent2TYPE_BUTTON_UP = 2,
    vevent2TYPE_POINTER_DETAIL = 3,
    vevent2TYPE_POINTER_DRAG = 4,
    vevent2TYPE_WINDOW_CONFIGURED = 5,
    vevent2TYPE_FOCUS_ACQUIRED = 6,
    vevent2TYPE_FOCUS_LOST = 7,
    vevent2TYPE_KEY_DOWN = 8,
    vevent2TYPE_KEY_UP = 9,
    vevent2TYPE_POINTER_ENTERED = 10,
    vevent2TYPE_POINTER_LEFT = 11,
    vevent2TYPE_WINDOW_STATE = 12,
    vevent2TYPE_WINDOW_UPDATE_REQUESTED = 13,
    vevent2TYPE_POINTER_MOVED = 14,
    _vevent2TYPE_NUM_BC_TYPES = 15,
    vevent2TYPE_WINDOW_CLOSED,
    vevent2TYPE_WINDOW_ICONIFIED,
    vevent2TYPE_WINDOW_MAXIMIZED,
    vevent2TYPE_WINDOW_OPENED,
    vevent2TYPE_WINDOW_PINNED,
    vevent2TYPE_WINDOW_UNICONIFIED,
    vevent2TYPE_WINDOW_UNMAXIMIZED,
    vevent2TYPE_WINDOW_UNPINNED,
    vevent2TYPE_NEXT_GALAXY_TYPE,
    vevent2TYPE_NEXT_VISIX_TYPE = 64,
    vevent2TYPE_NEXT_REGISTERED_TYPE = 256,
    vevent2TYPE_NEXT_3RD_PARTY_LIBRARY_TYPE = 512,
    vevent2TYPE_NEXT_APPLICATION_TYPE = 1024
};

enum {
    vevent2BUTTON_LEFT,
    vevent2BUTTON_MIDDLE,
    vevent2BUTTON_RIGHT
};


/*
 * * * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * * *
 */

void                                 vevent2Startup
    (void                                 );

vevent2Class                        *vevent2GetDefaultClass
    (void                                 );

vevent2WindowEventClass             *vevent2GetDefaultWindowEventClass
    (void                                 );

vevent2WindowConfigureEventClass    *vevent2GetDefaultWindowConfigureEventClass
    (void                                 );

vevent2FocusEventClass              *vevent2GetDefaultFocusEventClass
    (void                                 );

vevent2FocusAcquireEventClass       *vevent2GetDefaultFocusAcquireEventClass
    (void                                 );

vevent2FocusLoseEventClass          *vevent2GetDefaultFocusLoseEventClass
    (void                                 );

vevent2PointerEventClass            *vevent2GetDefaultPointerEventClass
    (void                                 );

vevent2ButtonEventClass             *vevent2GetDefaultButtonEventClass
    (void                                 );

vevent2ButtonDownEventClass         *vevent2GetDefaultButtonDownEventClass
    (void                                 );

vevent2ButtonUpEventClass           *vevent2GetDefaultButtonUpEventClass
    (void                                 );

vevent2PointerEnterEventClass       *vevent2GetDefaultPointerEnterEventClass
    (void                                 );

vevent2KeyEventClass                *vevent2GetDefaultKeyEventClass
    (void                                 );

vevent2KeyDownEventClass            *vevent2GetDefaultKeyDownEventClass
    (void                                 );

vevent2KeyUpEventClass              *vevent2GetDefaultKeyUpEventClass
    (void                                 );

vevent2PointerLeaveEventClass       *vevent2GetDefaultPointerLeaveEventClass
    (void                                 );

vevent2MotionEventClass             *vevent2GetDefaultMotionEventClass
    (void                                 );

vevent2WindowStateEventClass        *vevent2GetDefaultWindowStateEventClass
    (void                                 );

vevent2WindowUpdateEventClass       *vevent2GetDefaultWindowUpdateEventClass
    (void                                 );

vevent2HandlerClass                 *vevent2GetDefaultHandlerClass
    (void                                 );

vevent2LoopClass                    *vevent2GetDefaultLoopClass
    (void                                 );

vevent2DriverClass                  *vevent2GetDefaultDriverClass
    (void                                 );

vevent2PreBlockerClass              *vevent2GetDefaultPreBlockerClass
    (void                                 );

vevent2QuitterClass                 *vevent2GetDefaultQuitterClass
    (void                                 );

vevent2SystemEventHandlerClass      *vevent2GetDefaultSystemEventHandlerClass
    (void                                 );

vevent2Loop                         *vevent2GetDefaultLoop
    (void                                 );

vevent2Loop                         *vevent2GetCurrentLoop
    (void                                 );

void                                 vevent2DestroyInstanceLater
    (vinstance                           *pInstance);

/* class vevent2 */

vevent2Class                        *vevent2ClassGetDefault
    (void                                 );

vloadableClass                      *vevent2ClassAsLoadableClass
    (vevent2Class                        *pClass);

vinstanceClass                      *vevent2ClassAsInstanceClass
    (vevent2Class                        *pClass);

vbool                                vevent2ClassValidate
    (vevent2Class                        *pClass);

void                                 vevent2ClassAssert
    (vevent2Class                        *pClass);

void                                 vevent2ClassHandledAssert
    (vevent2Class                        *pClass,
     vdebugAssertionHandler               handler,
     void                                *pData);

vevent2                             *vevent2Create
    (void                                 );

vevent2                             *vevent2CreateOfClass
    (vevent2Class                        *pClass);

void                                 vevent2Share
    (vevent2                             *pEvent);

void                                 vevent2Release
    (vevent2                             *pEvent);

vbool                                vevent2IsShared
    (vevent2                             *pEvent);

void                                 vevent2Dump
    (vevent2                             *pEvent,
     FILE                                *fp);

void                                 vevent2SetTime
    (vevent2                             *pEvent,
     vtimestamp                           time);

vtimestamp                           vevent2GetTime
    (vevent2                             *pEvent);

void                                 vevent2SetType
    (vevent2                             *pEvent,
     vevent2Type                          type);

vevent2Type                          vevent2GetType
    (vevent2                             *pEvent);

void                                 vevent2SetBinding
    (vevent2                             *pEvent,
     const vname                         *binding);

const vname                         *vevent2GetBinding
    (vevent2                             *pEvent);

void                                 vevent2SetData
    (vevent2                             *pEvent,
     const void                          *pData);

void                                *vevent2GetData
    (vevent2                             *pEvent);

void                                 vevent2SetPriority
    (vevent2                             *pEvent,
     vbyte                                priority);

vbyte                                vevent2GetPriority
    (vevent2                             *pEvent);

void                                 vevent2SetHandler
    (vevent2                             *pEvent,
     vevent2Handler                      *pHandler);

vevent2Handler                      *vevent2GetHandler
    (vevent2                             *pEvent);

void                                 vevent2SetLoop
    (vevent2                             *pEvent,
     vevent2Loop                         *pLoop);

vevent2Loop                         *vevent2GetLoop
    (vevent2                             *pEvent);

void                                 vevent2Post
    (vevent2                             *pEvent);

void                                 vevent2PostAtInterrupt
    (vevent2                             *pEvent);

void                                 vevent2NotifyQueued
    (vevent2                             *pEvent,
     vevent2Loop                         *pLoop);

vloadable                           *vevent2AsLoadable
    (vevent2                             *pEvent);

vinstance                           *vevent2AsInstance
    (vevent2                             *pEvent);

vevent2Class                        *vevent2GetClass
    (vevent2                             *pEvent);

vbool                                vevent2Validate
    (vevent2                             *pEvent);

void                                 vevent2Assert
    (vevent2                             *pEvent);

void                                 vevent2HandledAssert
    (vevent2                             *pEvent,
     vdebugAssertionHandler               handler,
     void                                *pData);

/* class vevent2WindowEvent */

vevent2WindowEventClass             *vevent2WindowEventClassGetDefault
    (void                                 );

vevent2Class                        *vevent2WindowEventClassAsEventClass
    (vevent2WindowEventClass             *pClass);

vloadableClass                      *vevent2WindowEventClassAsLoadableClass
    (vevent2WindowEventClass             *pClass);

vinstanceClass                      *vevent2WindowEventClassAsInstanceClass
    (vevent2WindowEventClass             *pClass);

vbool                                vevent2WindowEventClassValidate
    (vevent2WindowEventClass             *pClass);

void                                 vevent2WindowEventClassAssert
    (vevent2WindowEventClass             *pClass);

void                                 vevent2WindowEventClassHandledAssert
    (vevent2WindowEventClass             *pClass,
     vdebugAssertionHandler               handler,
     void                                *pData);

vevent2WindowEvent                  *vevent2WindowEventCreate
    (void                                 );

vevent2WindowEvent                  *vevent2WindowEventCreateOfClass
    (vevent2WindowEventClass             *pClass);

void                                 vevent2WindowEventSetWindow
    (vevent2WindowEvent                  *pEvent,
     _vevent2STRUCT vwindow              *pWindow);

_vevent2STRUCT vwindow              *vevent2WindowEventGetWindow
    (vevent2WindowEvent                  *pEvent);

vevent2                             *vevent2WindowEventAsEvent
    (vevent2WindowEvent                  *pEvent);

vloadable                           *vevent2WindowEventAsLoadable
    (vevent2WindowEvent                  *pEvent);

vinstance                           *vevent2WindowEventAsInstance
    (vevent2WindowEvent                  *pEvent);

vevent2WindowEventClass             *vevent2WindowEventGetClass
    (vevent2WindowEvent                  *pEvent);

vbool                                vevent2WindowEventValidate
    (vevent2WindowEvent                  *pEvent);

void                                 vevent2WindowEventAssert
    (vevent2WindowEvent                  *pEvent);

void                                 vevent2WindowEventHandledAssert
    (vevent2WindowEvent                  *pEvent,
     vdebugAssertionHandler               handler,
     void                                *pData);

/* class vevent2WindowConfigureEvent */

vevent2WindowConfigureEventClass    *vevent2WindowConfigureEventClassGetDefault
    (void                                 );

vevent2WindowEventClass     *vevent2WindowConfigureEventClassAsWindowEventClass
    (vevent2WindowConfigureEventClass    *pClass);

vevent2Class                      *vevent2WindowConfigureEventClassAsEventClass
    (vevent2WindowConfigureEventClass    *pClass);

vloadableClass                 *vevent2WindowConfigureEventClassAsLoadableClass
    (vevent2WindowConfigureEventClass    *pClass);

vinstanceClass                 *vevent2WindowConfigureEventClassAsInstanceClass
    (vevent2WindowConfigureEventClass    *pClass);

vbool                                vevent2WindowConfigureEventClassValidate
    (vevent2WindowConfigureEventClass    *pClass);

void                                 vevent2WindowConfigureEventClassAssert
    (vevent2WindowConfigureEventClass    *pClass);

void                              vevent2WindowConfigureEventClassHandledAssert
    (vevent2WindowConfigureEventClass    *pClass,
     vdebugAssertionHandler               handler,
     void                                *pData);

vevent2WindowConfigureEvent         *vevent2WindowConfigureEventCreate
    (void                                 );

vevent2WindowConfigureEvent         *vevent2WindowConfigureEventCreateOfClass
    (vevent2WindowConfigureEventClass    *pClass);

void                                 vevent2WindowConfigureEventSetRect
    (vevent2WindowConfigureEvent         *pEvent,
     const vrect                         *pRect);

const vrect                         *vevent2WindowConfigureEventGetRect
    (vevent2WindowConfigureEvent         *pEvent);

void                                 vevent2WindowConfigureEventSetAbove
    (vevent2WindowConfigureEvent         *pEvent,
     _vevent2STRUCT vwindow              *pAbove);

_vevent2STRUCT vwindow              *vevent2WindowConfigureEventGetAbove
    (vevent2WindowConfigureEvent         *pEvent);

vevent2WindowEvent                  *vevent2WindowConfigureEventAsWindowEvent
    (vevent2WindowConfigureEvent         *pEvent);

vevent2                             *vevent2WindowConfigureEventAsEvent
    (vevent2WindowConfigureEvent         *pEvent);

vloadable                           *vevent2WindowConfigureEventAsLoadable
    (vevent2WindowConfigureEvent         *pEvent);

vinstance                           *vevent2WindowConfigureEventAsInstance
    (vevent2WindowConfigureEvent         *pEvent);

vevent2WindowConfigureEventClass    *vevent2WindowConfigureEventGetClass
    (vevent2WindowConfigureEvent         *pEvent);

vbool                                vevent2WindowConfigureEventValidate
    (vevent2WindowConfigureEvent         *pEvent);

void                                 vevent2WindowConfigureEventAssert
    (vevent2WindowConfigureEvent         *pEvent);

void                                 vevent2WindowConfigureEventHandledAssert
    (vevent2WindowConfigureEvent         *pEvent,
     vdebugAssertionHandler               handler,
     void                                *pData);

/* class vevent2FocusEvent */

vevent2FocusEventClass              *vevent2FocusEventClassGetDefault
    (void                                 );

vevent2WindowEventClass             *vevent2FocusEventClassAsWindowEventClass
    (vevent2FocusEventClass              *pClass);

vevent2Class                        *vevent2FocusEventClassAsEventClass
    (vevent2FocusEventClass              *pClass);

vloadableClass                      *vevent2FocusEventClassAsLoadableClass
    (vevent2FocusEventClass              *pClass);

vinstanceClass                      *vevent2FocusEventClassAsInstanceClass
    (vevent2FocusEventClass              *pClass);

vbool                                vevent2FocusEventClassValidate
    (vevent2FocusEventClass              *pClass);

void                                 vevent2FocusEventClassAssert
    (vevent2FocusEventClass              *pClass);

void                                 vevent2FocusEventClassHandledAssert
    (vevent2FocusEventClass              *pClass,
     vdebugAssertionHandler               handler,
     void                                *pData);

vevent2FocusEvent                   *vevent2FocusEventCreate
    (void                                 );

vevent2FocusEvent                   *vevent2FocusEventCreateOfClass
    (vevent2FocusEventClass              *pClass);

vevent2WindowEvent                  *vevent2FocusEventAsWindowEvent
    (vevent2FocusEvent                   *pEvent);

vevent2                             *vevent2FocusEventAsEvent
    (vevent2FocusEvent                   *pEvent);

vloadable                           *vevent2FocusEventAsLoadable
    (vevent2FocusEvent                   *pEvent);

vinstance                           *vevent2FocusEventAsInstance
    (vevent2FocusEvent                   *pEvent);

vevent2FocusEventClass              *vevent2FocusEventGetClass
    (vevent2FocusEvent                   *pEvent);

vbool                                vevent2FocusEventValidate
    (vevent2FocusEvent                   *pEvent);

void                                 vevent2FocusEventAssert
    (vevent2FocusEvent                   *pEvent);

void                                 vevent2FocusEventHandledAssert
    (vevent2FocusEvent                   *pEvent,
     vdebugAssertionHandler               handler,
     void                                *pData);

/* class vevent2FocusAcquireEvent */

vevent2FocusAcquireEventClass       *vevent2FocusAcquireEventClassGetDefault
    (void                                 );

vevent2FocusEventClass          *vevent2FocusAcquireEventClassAsFocusEventClass
    (vevent2FocusAcquireEventClass       *pClass);

vevent2WindowEventClass        *vevent2FocusAcquireEventClassAsWindowEventClass
    (vevent2FocusAcquireEventClass       *pClass);

vevent2Class                        *vevent2FocusAcquireEventClassAsEventClass
    (vevent2FocusAcquireEventClass       *pClass);

vloadableClass                    *vevent2FocusAcquireEventClassAsLoadableClass
    (vevent2FocusAcquireEventClass       *pClass);

vinstanceClass                    *vevent2FocusAcquireEventClassAsInstanceClass
    (vevent2FocusAcquireEventClass       *pClass);

vbool                                vevent2FocusAcquireEventClassValidate
    (vevent2FocusAcquireEventClass       *pClass);

void                                 vevent2FocusAcquireEventClassAssert
    (vevent2FocusAcquireEventClass       *pClass);

void                                 vevent2FocusAcquireEventClassHandledAssert
    (vevent2FocusAcquireEventClass       *pClass,
     vdebugAssertionHandler               handler,
     void                                *pData);

vevent2FocusAcquireEvent            *vevent2FocusAcquireEventCreate
    (void                                 );

vevent2FocusAcquireEvent            *vevent2FocusAcquireEventCreateOfClass
    (vevent2FocusAcquireEventClass       *pClass);

vevent2FocusEvent                   *vevent2FocusAcquireEventAsFocusEvent
    (vevent2FocusAcquireEvent            *pEvent);

vevent2WindowEvent                  *vevent2FocusAcquireEventAsWindowEvent
    (vevent2FocusAcquireEvent            *pEvent);

vevent2                             *vevent2FocusAcquireEventAsEvent
    (vevent2FocusAcquireEvent            *pEvent);

vloadable                           *vevent2FocusAcquireEventAsLoadable
    (vevent2FocusAcquireEvent            *pEvent);

vinstance                           *vevent2FocusAcquireEventAsInstance
    (vevent2FocusAcquireEvent            *pEvent);

vevent2FocusAcquireEventClass       *vevent2FocusAcquireEventGetClass
    (vevent2FocusAcquireEvent            *pEvent);

vbool                                vevent2FocusAcquireEventValidate
    (vevent2FocusAcquireEvent            *pEvent);

void                                 vevent2FocusAcquireEventAssert
    (vevent2FocusAcquireEvent            *pEvent);

void                                 vevent2FocusAcquireEventHandledAssert
    (vevent2FocusAcquireEvent            *pEvent,
     vdebugAssertionHandler               handler,
     void                                *pData);

/* class vevent2FocusLoseEvent */

vevent2FocusLoseEventClass          *vevent2FocusLoseEventClassGetDefault
    (void                                 );

vevent2FocusEventClass             *vevent2FocusLoseEventClassAsFocusEventClass
    (vevent2FocusLoseEventClass          *pClass);

vevent2WindowEventClass           *vevent2FocusLoseEventClassAsWindowEventClass
    (vevent2FocusLoseEventClass          *pClass);

vevent2Class                        *vevent2FocusLoseEventClassAsEventClass
    (vevent2FocusLoseEventClass          *pClass);

vloadableClass                      *vevent2FocusLoseEventClassAsLoadableClass
    (vevent2FocusLoseEventClass          *pClass);

vinstanceClass                      *vevent2FocusLoseEventClassAsInstanceClass
    (vevent2FocusLoseEventClass          *pClass);

vbool                                vevent2FocusLoseEventClassValidate
    (vevent2FocusLoseEventClass          *pClass);

void                                 vevent2FocusLoseEventClassAssert
    (vevent2FocusLoseEventClass          *pClass);

void                                 vevent2FocusLoseEventClassHandledAssert
    (vevent2FocusLoseEventClass          *pClass,
     vdebugAssertionHandler               handler,
     void                                *pData);

vevent2FocusLoseEvent               *vevent2FocusLoseEventCreate
    (void                                 );

vevent2FocusLoseEvent               *vevent2FocusLoseEventCreateOfClass
    (vevent2FocusLoseEventClass          *pClass);

vevent2FocusEvent                   *vevent2FocusLoseEventAsFocusEvent
    (vevent2FocusLoseEvent               *pEvent);

vevent2WindowEvent                  *vevent2FocusLoseEventAsWindowEvent
    (vevent2FocusLoseEvent               *pEvent);

vevent2                             *vevent2FocusLoseEventAsEvent
    (vevent2FocusLoseEvent               *pEvent);

vloadable                           *vevent2FocusLoseEventAsLoadable
    (vevent2FocusLoseEvent               *pEvent);

vinstance                           *vevent2FocusLoseEventAsInstance
    (vevent2FocusLoseEvent               *pEvent);

vevent2FocusLoseEventClass          *vevent2FocusLoseEventGetClass
    (vevent2FocusLoseEvent               *pEvent);

vbool                                vevent2FocusLoseEventValidate
    (vevent2FocusLoseEvent               *pEvent);

void                                 vevent2FocusLoseEventAssert
    (vevent2FocusLoseEvent               *pEvent);

void                                 vevent2FocusLoseEventHandledAssert
    (vevent2FocusLoseEvent               *pEvent,
     vdebugAssertionHandler               handler,
     void                                *pData);

/* class vevent2PointerEvent */

vevent2PointerEventClass            *vevent2PointerEventClassGetDefault
    (void                                 );

vevent2WindowEventClass             *vevent2PointerEventClassAsWindowEventClass
    (vevent2PointerEventClass            *pClass);

vevent2Class                        *vevent2PointerEventClassAsEventClass
    (vevent2PointerEventClass            *pClass);

vloadableClass                      *vevent2PointerEventClassAsLoadableClass
    (vevent2PointerEventClass            *pClass);

vinstanceClass                      *vevent2PointerEventClassAsInstanceClass
    (vevent2PointerEventClass            *pClass);

vbool                                vevent2PointerEventClassValidate
    (vevent2PointerEventClass            *pClass);

void                                 vevent2PointerEventClassAssert
    (vevent2PointerEventClass            *pClass);

void                                 vevent2PointerEventClassHandledAssert
    (vevent2PointerEventClass            *pClass,
     vdebugAssertionHandler               handler,
     void                                *pData);

vevent2PointerEvent                 *vevent2PointerEventCreate
    (void                                 );

vevent2PointerEvent                 *vevent2PointerEventCreateOfClass
    (vevent2PointerEventClass            *pClass);

void                                 vevent2PointerEventSetPoint
    (vevent2PointerEvent                 *pEvent,
     const vpoint                        *point);

const vpoint                        *vevent2PointerEventGetPoint
    (vevent2PointerEvent                 *pEvent);

void                                 vevent2PointerEventSetX
    (vevent2PointerEvent                 *pEvent,
     int                                  x);

int                                  vevent2PointerEventGetX
    (vevent2PointerEvent                 *pEvent);

void                                 vevent2PointerEventSetY
    (vevent2PointerEvent                 *pEvent,
     int                                  y);

int                                  vevent2PointerEventGetY
    (vevent2PointerEvent                 *pEvent);

void                                 vevent2PointerEventSetClickCount
    (vevent2PointerEvent                 *pEvent,
     vbyte                                clickCount);

vbyte                                vevent2PointerEventGetClickCount
    (vevent2PointerEvent                 *pEvent);

void                                 vevent2PointerEventSetModifiers
    (vevent2PointerEvent                 *pEvent,
     vkeyModifiers                        modifiers);

vkeyModifiers                        vevent2PointerEventGetModifiers
    (vevent2PointerEvent                 *pEvent);

vevent2WindowEvent                  *vevent2PointerEventAsWindowEvent
    (vevent2PointerEvent                 *pEvent);

vevent2                             *vevent2PointerEventAsEvent
    (vevent2PointerEvent                 *pEvent);

vloadable                           *vevent2PointerEventAsLoadable
    (vevent2PointerEvent                 *pEvent);

vinstance                           *vevent2PointerEventAsInstance
    (vevent2PointerEvent                 *pEvent);

vevent2PointerEventClass            *vevent2PointerEventGetClass
    (vevent2PointerEvent                 *pEvent);

vbool                                vevent2PointerEventValidate
    (vevent2PointerEvent                 *pEvent);

void                                 vevent2PointerEventAssert
    (vevent2PointerEvent                 *pEvent);

void                                 vevent2PointerEventHandledAssert
    (vevent2PointerEvent                 *pEvent,
     vdebugAssertionHandler               handler,
     void                                *pData);

/* class vevent2ButtonEvent */

vevent2ButtonEventClass             *vevent2ButtonEventClassGetDefault
    (void                                 );

vevent2PointerEventClass            *vevent2ButtonEventClassAsPointerEventClass
    (vevent2ButtonEventClass             *pClass);

vevent2Class                        *vevent2ButtonEventClassAsEventClass
    (vevent2ButtonEventClass             *pClass);

vloadableClass                      *vevent2ButtonEventClassAsLoadableClass
    (vevent2ButtonEventClass             *pClass);

vinstanceClass                      *vevent2ButtonEventClassAsInstanceClass
    (vevent2ButtonEventClass             *pClass);

vbool                                vevent2ButtonEventClassValidate
    (vevent2ButtonEventClass             *pClass);

void                                 vevent2ButtonEventClassAssert
    (vevent2ButtonEventClass             *pClass);

void                                 vevent2ButtonEventClassHandledAssert
    (vevent2ButtonEventClass             *pClass,
     vdebugAssertionHandler               handler,
     void                                *pData);

vevent2ButtonEvent                  *vevent2ButtonEventCreate
    (void                                 );

vevent2ButtonEvent                  *vevent2ButtonEventCreateOfClass
    (vevent2ButtonEventClass             *pClass);

void                                 vevent2ButtonEventSetButton
    (vevent2ButtonEvent                  *pEvent,
     vevent2Button                        button);

vevent2Button                        vevent2ButtonEventGetButton
    (vevent2ButtonEvent                  *pEvent);

vevent2PointerEvent                  *vevent2ButtonEventAsPointerEvent
    (vevent2ButtonEvent                  *pEvent);

vevent2WindowEvent                  *vevent2ButtonEventAsWindowEvent
    (vevent2ButtonEvent                  *pEvent);

vevent2                             *vevent2ButtonEventAsEvent
    (vevent2ButtonEvent                  *pEvent);

vloadable                           *vevent2ButtonEventAsLoadable
    (vevent2ButtonEvent                  *pEvent);

vinstance                           *vevent2ButtonEventAsInstance
    (vevent2ButtonEvent                  *pEvent);

vevent2ButtonEventClass             *vevent2ButtonEventGetClass
    (vevent2ButtonEvent                  *pEvent);

vbool                                vevent2ButtonEventValidate
    (vevent2ButtonEvent                  *pEvent);

void                                 vevent2ButtonEventAssert
    (vevent2ButtonEvent                  *pEvent);

void                                 vevent2ButtonEventHandledAssert
    (vevent2ButtonEvent                  *pEvent,
     vdebugAssertionHandler               handler,
     void                                *pData);

/* class vevent2ButtonDownEvent */

vevent2ButtonDownEventClass         *vevent2ButtonDownEventClassGetDefault
    (void                                 );

vevent2ButtonEventClass          *vevent2ButtonDownEventClassAsButtonEventClass
    (vevent2ButtonDownEventClass         *pClass);

vevent2Class                        *vevent2ButtonDownEventClassAsEventClass
    (vevent2ButtonDownEventClass         *pClass);

vloadableClass                      *vevent2ButtonDownEventClassAsLoadableClass
    (vevent2ButtonDownEventClass         *pClass);

vinstanceClass                      *vevent2ButtonDownEventClassAsInstanceClass
    (vevent2ButtonDownEventClass         *pClass);

vbool                                vevent2ButtonDownEventClassValidate
    (vevent2ButtonDownEventClass         *pClass);

void                                 vevent2ButtonDownEventClassAssert
    (vevent2ButtonDownEventClass         *pClass);

void                                 vevent2ButtonDownEventClassHandledAssert
    (vevent2ButtonDownEventClass         *pClass,
     vdebugAssertionHandler               handler,
     void                                *pData);

vevent2ButtonDownEvent              *vevent2ButtonDownEventCreate
    (void                                 );

vevent2ButtonDownEvent              *vevent2ButtonDownEventCreateOfClass
    (vevent2ButtonDownEventClass         *pClass);

vevent2ButtonEvent                  *vevent2ButtonDownEventAsButtonEvent
    (vevent2ButtonDownEvent              *pEvent);

vevent2WindowEvent                  *vevent2ButtonDownEventAsWindowEvent
    (vevent2ButtonDownEvent              *pEvent);

vevent2                             *vevent2ButtonDownEventAsEvent
    (vevent2ButtonDownEvent              *pEvent);

vloadable                           *vevent2ButtonDownEventAsLoadable
    (vevent2ButtonDownEvent              *pEvent);

vinstance                           *vevent2ButtonDownEventAsInstance
    (vevent2ButtonDownEvent              *pEvent);

vevent2ButtonDownEventClass         *vevent2ButtonDownEventGetClass
    (vevent2ButtonDownEvent              *pEvent);

vbool                                vevent2ButtonDownEventValidate
    (vevent2ButtonDownEvent              *pEvent);

void                                 vevent2ButtonDownEventAssert
    (vevent2ButtonDownEvent              *pEvent);

void                                 vevent2ButtonDownEventHandledAssert
    (vevent2ButtonDownEvent              *pEvent,
     vdebugAssertionHandler               handler,
     void                                *pData);

/* class vevent2ButtonUpEvent */

vevent2ButtonUpEventClass           *vevent2ButtonUpEventClassGetDefault
    (void                                 );

vevent2ButtonEventClass            *vevent2ButtonUpEventClassAsButtonEventClass
    (vevent2ButtonUpEventClass           *pClass);

vevent2Class                        *vevent2ButtonUpEventClassAsEventClass
    (vevent2ButtonUpEventClass           *pClass);

vloadableClass                      *vevent2ButtonUpEventClassAsLoadableClass
    (vevent2ButtonUpEventClass           *pClass);

vinstanceClass                      *vevent2ButtonUpEventClassAsInstanceClass
    (vevent2ButtonUpEventClass           *pClass);

vbool                                vevent2ButtonUpEventClassValidate
    (vevent2ButtonUpEventClass           *pClass);

void                                 vevent2ButtonUpEventClassAssert
    (vevent2ButtonUpEventClass           *pClass);

void                                 vevent2ButtonUpEventClassHandledAssert
    (vevent2ButtonUpEventClass           *pClass,
     vdebugAssertionHandler               handler,
     void                                *pData);

vevent2ButtonUpEvent                *vevent2ButtonUpEventCreate
    (void                                 );

vevent2ButtonUpEvent                *vevent2ButtonUpEventCreateOfClass
    (vevent2ButtonUpEventClass           *pClass);

vevent2ButtonEvent                  *vevent2ButtonUpEventAsButtonEvent
    (vevent2ButtonUpEvent                *pEvent);

vevent2WindowEvent                  *vevent2ButtonUpEventAsWindowEvent
    (vevent2ButtonUpEvent                *pEvent);

vevent2                             *vevent2ButtonUpEventAsEvent
    (vevent2ButtonUpEvent                *pEvent);

vloadable                           *vevent2ButtonUpEventAsLoadable
    (vevent2ButtonUpEvent                *pEvent);

vinstance                           *vevent2ButtonUpEventAsInstance
    (vevent2ButtonUpEvent                *pEvent);

vevent2ButtonUpEventClass           *vevent2ButtonUpEventGetClass
    (vevent2ButtonUpEvent                *pEvent);

vbool                                vevent2ButtonUpEventValidate
    (vevent2ButtonUpEvent                *pEvent);

void                                 vevent2ButtonUpEventAssert
    (vevent2ButtonUpEvent                *pEvent);

void                                 vevent2ButtonUpEventHandledAssert
    (vevent2ButtonUpEvent                *pEvent,
     vdebugAssertionHandler               handler,
     void                                *pData);

/* class vevent2PointerEnterEvent */

vevent2PointerEnterEventClass       *vevent2PointerEnterEventClassGetDefault
    (void                                 );

vevent2PointerEventClass      *vevent2PointerEnterEventClassAsPointerEventClass
    (vevent2PointerEnterEventClass       *pClass);

vevent2Class                        *vevent2PointerEnterEventClassAsEventClass
    (vevent2PointerEnterEventClass       *pClass);

vloadableClass                    *vevent2PointerEnterEventClassAsLoadableClass
    (vevent2PointerEnterEventClass       *pClass);

vinstanceClass                    *vevent2PointerEnterEventClassAsInstanceClass
    (vevent2PointerEnterEventClass       *pClass);

vbool                                vevent2PointerEnterEventClassValidate
    (vevent2PointerEnterEventClass       *pClass);

void                                 vevent2PointerEnterEventClassAssert
    (vevent2PointerEnterEventClass       *pClass);

void                                 vevent2PointerEnterEventClassHandledAssert
    (vevent2PointerEnterEventClass       *pClass,
     vdebugAssertionHandler               handler,
     void                                *pData);

vevent2PointerEnterEvent            *vevent2PointerEnterEventCreate
    (void                                 );

vevent2PointerEnterEvent            *vevent2PointerEnterEventCreateOfClass
    (vevent2PointerEnterEventClass       *pClass);

vevent2PointerEvent                 *vevent2PointerEnterEventAsPointerEvent
    (vevent2PointerEnterEvent            *pEvent);

vevent2WindowEvent                  *vevent2PointerEnterEventAsWindowEvent
    (vevent2PointerEnterEvent            *pEvent);

vevent2                             *vevent2PointerEnterEventAsEvent
    (vevent2PointerEnterEvent            *pEvent);

vloadable                           *vevent2PointerEnterEventAsLoadable
    (vevent2PointerEnterEvent            *pEvent);

vinstance                           *vevent2PointerEnterEventAsInstance
    (vevent2PointerEnterEvent            *pEvent);

vevent2PointerEnterEventClass       *vevent2PointerEnterEventGetClass
    (vevent2PointerEnterEvent            *pEvent);

vbool                                vevent2PointerEnterEventValidate
    (vevent2PointerEnterEvent            *pEvent);

void                                 vevent2PointerEnterEventAssert
    (vevent2PointerEnterEvent            *pEvent);

void                                 vevent2PointerEnterEventHandledAssert
    (vevent2PointerEnterEvent            *pEvent,
     vdebugAssertionHandler               handler,
     void                                *pData);

/* class vevent2KeyEvent */

vevent2KeyEventClass                *vevent2KeyEventClassGetDefault
    (void                                 );

vevent2PointerEventClass            *vevent2KeyEventClassAsPointerEventClass
    (vevent2KeyEventClass                *pClass);

vevent2WindowEventClass             *vevent2KeyEventClassAsWindowEventClass
    (vevent2KeyEventClass                *pClass);

vevent2Class                        *vevent2KeyEventClassAsEventClass
    (vevent2KeyEventClass                *pClass);

vloadableClass                      *vevent2KeyEventClassAsLoadableClass
    (vevent2KeyEventClass                *pClass);

vinstanceClass                      *vevent2KeyEventClassAsInstanceClass
    (vevent2KeyEventClass                *pClass);

vbool                                vevent2KeyEventClassValidate
    (vevent2KeyEventClass                *pClass);

void                                 vevent2KeyEventClassAssert
    (vevent2KeyEventClass                *pClass);

void                                 vevent2KeyEventClassHandledAssert
    (vevent2KeyEventClass                *pClass,
     vdebugAssertionHandler               handler,
     void                                *pData);

vevent2KeyEvent                     *vevent2KeyEventCreate
    (void                                 );

vevent2KeyEvent                     *vevent2KeyEventCreateOfClass
    (vevent2KeyEventClass                *pClass);

void                                 vevent2KeyEventSetKey
    (vevent2KeyEvent                     *pEvent,
     vkey                                 k);

vkey                                 vevent2KeyEventGetKey
    (vevent2KeyEvent                     *pEvent);

void                                 vevent2KeyEventSetKeyStroke
    (vevent2KeyEvent                     *pEvent,
     vkeyStroke                           keyStroke);

vkeyStroke                           vevent2KeyEventGetKeyStroke
    (vevent2KeyEvent                     *pEvent);

void                                 vevent2KeyEventSetKeyCode
    (vevent2KeyEvent                     *pEvent,
     unsigned int                         keyCode);

unsigned int                         vevent2KeyEventGetKeyCode
    (vevent2KeyEvent                     *pEvent);

void                                 vevent2KeyEventSetKeyChar
    (vevent2KeyEvent                     *pEvent,
     unsigned int                         keyChar);

unsigned int                         vevent2KeyEventGetKeyChar
    (vevent2KeyEvent                     *pEvent);

vevent2PointerEvent                 *vevent2KeyEventAsPointerEvent
    (vevent2KeyEvent                     *pEvent);

vevent2WindowEvent                  *vevent2KeyEventAsWindowEvent
    (vevent2KeyEvent                     *pEvent);

vevent2                             *vevent2KeyEventAsEvent
    (vevent2KeyEvent                     *pEvent);

vloadable                           *vevent2KeyEventAsLoadable
    (vevent2KeyEvent                     *pEvent);

vinstance                           *vevent2KeyEventAsInstance
    (vevent2KeyEvent                     *pEvent);

vevent2KeyEventClass                *vevent2KeyEventGetClass
    (vevent2KeyEvent                     *pEvent);

vbool                                vevent2KeyEventValidate
    (vevent2KeyEvent                     *pEvent);

void                                 vevent2KeyEventAssert
    (vevent2KeyEvent                     *pEvent);

void                                 vevent2KeyEventHandledAssert
    (vevent2KeyEvent                     *pEvent,
     vdebugAssertionHandler               handler,
     void                                *pData);

/* class vevent2KeyDownEvent */

vevent2KeyDownEventClass            *vevent2KeyDownEventClassGetDefault
    (void                                 );

vevent2KeyEventClass                *vevent2KeyDownEventClassAsKeyEventClass
    (vevent2KeyDownEventClass            *pClass);

vevent2Class                        *vevent2KeyDownEventClassAsEventClass
    (vevent2KeyDownEventClass            *pClass);

vloadableClass                      *vevent2KeyDownEventClassAsLoadableClass
    (vevent2KeyDownEventClass            *pClass);

vinstanceClass                      *vevent2KeyDownEventClassAsInstanceClass
    (vevent2KeyDownEventClass            *pClass);

vbool                                vevent2KeyDownEventClassValidate
    (vevent2KeyDownEventClass            *pClass);

void                                 vevent2KeyDownEventClassAssert
    (vevent2KeyDownEventClass            *pClass);

void                                 vevent2KeyDownEventClassHandledAssert
    (vevent2KeyDownEventClass            *pClass,
     vdebugAssertionHandler               handler,
     void                                *pData);

vevent2KeyDownEvent                 *vevent2KeyDownEventCreate
    (void                                 );

vevent2KeyDownEvent                 *vevent2KeyDownEventCreateOfClass
    (vevent2KeyDownEventClass            *pClass);

vevent2KeyEvent                     *vevent2KeyDownEventAsKeyEvent
    (vevent2KeyDownEvent                 *pEvent);

vevent2WindowEvent                  *vevent2KeyDownEventAsWindowEvent
    (vevent2KeyDownEvent                 *pEvent);

vevent2                             *vevent2KeyDownEventAsEvent
    (vevent2KeyDownEvent                 *pEvent);

vloadable                           *vevent2KeyDownEventAsLoadable
    (vevent2KeyDownEvent                 *pEvent);

vinstance                           *vevent2KeyDownEventAsInstance
    (vevent2KeyDownEvent                 *pEvent);

vevent2KeyDownEventClass            *vevent2KeyDownEventGetClass
    (vevent2KeyDownEvent                 *pEvent);

vbool                                vevent2KeyDownEventValidate
    (vevent2KeyDownEvent                 *pEvent);

void                                 vevent2KeyDownEventAssert
    (vevent2KeyDownEvent                 *pEvent);

void                                 vevent2KeyDownEventHandledAssert
    (vevent2KeyDownEvent                 *pEvent,
     vdebugAssertionHandler               handler,
     void                                *pData);

/* class vevent2KeyUpEvent */

vevent2KeyUpEventClass              *vevent2KeyUpEventClassGetDefault
    (void                                 );

vevent2KeyEventClass                *vevent2KeyUpEventClassAsKeyEventClass
    (vevent2KeyUpEventClass              *pClass);

vevent2Class                        *vevent2KeyUpEventClassAsEventClass
    (vevent2KeyUpEventClass              *pClass);

vloadableClass                      *vevent2KeyUpEventClassAsLoadableClass
    (vevent2KeyUpEventClass              *pClass);

vinstanceClass                      *vevent2KeyUpEventClassAsInstanceClass
    (vevent2KeyUpEventClass              *pClass);

vbool                                vevent2KeyUpEventClassValidate
    (vevent2KeyUpEventClass              *pClass);

void                                 vevent2KeyUpEventClassAssert
    (vevent2KeyUpEventClass              *pClass);

void                                 vevent2KeyUpEventClassHandledAssert
    (vevent2KeyUpEventClass              *pClass,
     vdebugAssertionHandler               handler,
     void                                *pData);

vevent2KeyUpEvent                   *vevent2KeyUpEventCreate
    (void                                 );

vevent2KeyUpEvent                   *vevent2KeyUpEventCreateOfClass
    (vevent2KeyUpEventClass              *pClass);

vevent2KeyEvent                     *vevent2KeyUpEventAsKeyEvent
    (vevent2KeyUpEvent                   *pEvent);

vevent2WindowEvent                  *vevent2KeyUpEventAsWindowEvent
    (vevent2KeyUpEvent                   *pEvent);

vevent2                             *vevent2KeyUpEventAsEvent
    (vevent2KeyUpEvent                   *pEvent);

vloadable                           *vevent2KeyUpEventAsLoadable
    (vevent2KeyUpEvent                   *pEvent);

vinstance                           *vevent2KeyUpEventAsInstance
    (vevent2KeyUpEvent                   *pEvent);

vevent2KeyUpEventClass              *vevent2KeyUpEventGetClass
    (vevent2KeyUpEvent                   *pEvent);

vbool                                vevent2KeyUpEventValidate
    (vevent2KeyUpEvent                   *pEvent);

void                                 vevent2KeyUpEventAssert
    (vevent2KeyUpEvent                   *pEvent);

void                                 vevent2KeyUpEventHandledAssert
    (vevent2KeyUpEvent                   *pEvent,
     vdebugAssertionHandler               handler,
     void                                *pData);

/* class vevent2PointerLeaveEvent */

vevent2PointerLeaveEventClass       *vevent2PointerLeaveEventClassGetDefault
    (void                                 );

vevent2PointerEventClass      *vevent2PointerLeaveEventClassAsPointerEventClass
    (vevent2PointerLeaveEventClass       *pClass);

vevent2Class                        *vevent2PointerLeaveEventClassAsEventClass
    (vevent2PointerLeaveEventClass       *pClass);

vloadableClass                    *vevent2PointerLeaveEventClassAsLoadableClass
    (vevent2PointerLeaveEventClass       *pClass);

vinstanceClass                    *vevent2PointerLeaveEventClassAsInstanceClass
    (vevent2PointerLeaveEventClass       *pClass);

vbool                                vevent2PointerLeaveEventClassValidate
    (vevent2PointerLeaveEventClass       *pClass);

void                                 vevent2PointerLeaveEventClassAssert
    (vevent2PointerLeaveEventClass       *pClass);

void                                 vevent2PointerLeaveEventClassHandledAssert
    (vevent2PointerLeaveEventClass       *pClass,
     vdebugAssertionHandler               handler,
     void                                *pData);

vevent2PointerLeaveEvent            *vevent2PointerLeaveEventCreate
    (void                                 );

vevent2PointerLeaveEvent            *vevent2PointerLeaveEventCreateOfClass
    (vevent2PointerLeaveEventClass       *pClass);

vevent2PointerEvent                 *vevent2PointerLeaveEventAsPointerEvent
    (vevent2PointerLeaveEvent            *pEvent);

vevent2WindowEvent                  *vevent2PointerLeaveEventAsWindowEvent
    (vevent2PointerLeaveEvent            *pEvent);

vevent2                             *vevent2PointerLeaveEventAsEvent
    (vevent2PointerLeaveEvent            *pEvent);

vloadable                           *vevent2PointerLeaveEventAsLoadable
    (vevent2PointerLeaveEvent            *pEvent);

vinstance                           *vevent2PointerLeaveEventAsInstance
    (vevent2PointerLeaveEvent            *pEvent);

vevent2PointerLeaveEventClass       *vevent2PointerLeaveEventGetClass
    (vevent2PointerLeaveEvent            *pEvent);

vbool                                vevent2PointerLeaveEventValidate
    (vevent2PointerLeaveEvent            *pEvent);

void                                 vevent2PointerLeaveEventAssert
    (vevent2PointerLeaveEvent            *pEvent);

void                                 vevent2PointerLeaveEventHandledAssert
    (vevent2PointerLeaveEvent            *pEvent,
     vdebugAssertionHandler               handler,
     void                                *pData);

/* class vevent2MotionEvent */

vevent2MotionEventClass             *vevent2MotionEventClassGetDefault
    (void                                 );

vevent2PointerEventClass            *vevent2MotionEventClassAsPointerEventClass
    (vevent2MotionEventClass             *pClass);

vevent2Class                        *vevent2MotionEventClassAsEventClass
    (vevent2MotionEventClass             *pClass);

vloadableClass                      *vevent2MotionEventClassAsLoadableClass
    (vevent2MotionEventClass             *pClass);

vinstanceClass                      *vevent2MotionEventClassAsInstanceClass
    (vevent2MotionEventClass             *pClass);

vbool                                vevent2MotionEventClassValidate
    (vevent2MotionEventClass             *pClass);

void                                 vevent2MotionEventClassAssert
    (vevent2MotionEventClass             *pClass);

void                                 vevent2MotionEventClassHandledAssert
    (vevent2MotionEventClass             *pClass,
     vdebugAssertionHandler               handler,
     void                                *pData);

vevent2MotionEvent                  *vevent2MotionEventCreate
    (void                                 );

vevent2MotionEvent                  *vevent2MotionEventCreateOfClass
    (vevent2MotionEventClass             *pClass);

vevent2PointerEvent                  *vevent2MotionEventAsPointerEvent
    (vevent2MotionEvent                  *pEvent);

vevent2WindowEvent                  *vevent2MotionEventAsWindowEvent
    (vevent2MotionEvent                  *pEvent);

vevent2                             *vevent2MotionEventAsEvent
    (vevent2MotionEvent                  *pEvent);

vloadable                           *vevent2MotionEventAsLoadable
    (vevent2MotionEvent                  *pEvent);

vinstance                           *vevent2MotionEventAsInstance
    (vevent2MotionEvent                  *pEvent);

vevent2MotionEventClass             *vevent2MotionEventGetClass
    (vevent2MotionEvent                  *pEvent);

vbool                                vevent2MotionEventValidate
    (vevent2MotionEvent                  *pEvent);

void                                 vevent2MotionEventAssert
    (vevent2MotionEvent                  *pEvent);

void                                 vevent2MotionEventHandledAssert
    (vevent2MotionEvent                  *pEvent,
     vdebugAssertionHandler               handler,
     void                                *pData);

/* class vevent2WindowStateEvent */

vevent2WindowStateEventClass        *vevent2WindowStateEventClassGetDefault
    (void                                 );

vevent2WindowEventClass         *vevent2WindowStateEventClassAsWindowEventClass
    (vevent2WindowStateEventClass        *pClass);

vevent2Class                        *vevent2WindowStateEventClassAsEventClass
    (vevent2WindowStateEventClass        *pClass);

vloadableClass                     *vevent2WindowStateEventClassAsLoadableClass
    (vevent2WindowStateEventClass        *pClass);

vinstanceClass                     *vevent2WindowStateEventClassAsInstanceClass
    (vevent2WindowStateEventClass        *pClass);

vbool                                vevent2WindowStateEventClassValidate
    (vevent2WindowStateEventClass        *pClass);

void                                 vevent2WindowStateEventClassAssert
    (vevent2WindowStateEventClass        *pClass);

void                                 vevent2WindowStateEventClassHandledAssert
    (vevent2WindowStateEventClass        *pClass,
     vdebugAssertionHandler               handler,
     void                                *pData);

vevent2WindowStateEvent             *vevent2WindowStateEventCreate
    (void                                 );

vevent2WindowStateEvent             *vevent2WindowStateEventCreateOfClass
    (vevent2WindowStateEventClass        *pClass);

vevent2WindowEvent                  *vevent2WindowStateEventAsWindowEvent
    (vevent2WindowStateEvent             *pEvent);

vevent2                             *vevent2WindowStateEventAsEvent
    (vevent2WindowStateEvent             *pEvent);

vloadable                           *vevent2WindowStateEventAsLoadable
    (vevent2WindowStateEvent             *pEvent);

vinstance                           *vevent2WindowStateEventAsInstance
    (vevent2WindowStateEvent             *pEvent);

vevent2WindowStateEventClass        *vevent2WindowStateEventGetClass
    (vevent2WindowStateEvent             *pEvent);

vbool                                vevent2WindowStateEventValidate
    (vevent2WindowStateEvent             *pEvent);

void                                 vevent2WindowStateEventAssert
    (vevent2WindowStateEvent             *pEvent);

void                                 vevent2WindowStateEventHandledAssert
    (vevent2WindowStateEvent             *pEvent,
     vdebugAssertionHandler               handler,
     void                                *pData);

/* class vevent2WindowUpdateEvent */

vevent2WindowUpdateEventClass       *vevent2WindowUpdateEventClassGetDefault
    (void                                 );

vevent2WindowEventClass        *vevent2WindowUpdateEventClassAsWindowEventClass
    (vevent2WindowUpdateEventClass       *pClass);

vevent2Class                        *vevent2WindowUpdateEventClassAsEventClass
    (vevent2WindowUpdateEventClass       *pClass);

vloadableClass                    *vevent2WindowUpdateEventClassAsLoadableClass
    (vevent2WindowUpdateEventClass       *pClass);

vinstanceClass                    *vevent2WindowUpdateEventClassAsInstanceClass
    (vevent2WindowUpdateEventClass       *pClass);

vbool                                vevent2WindowUpdateEventClassValidate
    (vevent2WindowUpdateEventClass       *pClass);

void                                 vevent2WindowUpdateEventClassAssert
    (vevent2WindowUpdateEventClass       *pClass);

void                                 vevent2WindowUpdateEventClassHandledAssert
    (vevent2WindowUpdateEventClass       *pClass,
     vdebugAssertionHandler               handler,
     void                                *pData);

vevent2WindowUpdateEvent            *vevent2WindowUpdateEventCreate
    (void                                 );

vevent2WindowUpdateEvent            *vevent2WindowUpdateEventCreateOfClass
    (vevent2WindowUpdateEventClass       *pClass);

vevent2WindowEvent                  *vevent2WindowUpdateEventAsWindowEvent
    (vevent2WindowUpdateEvent            *pEvent);

vevent2                             *vevent2WindowUpdateEventAsEvent
    (vevent2WindowUpdateEvent            *pEvent);

vloadable                           *vevent2WindowUpdateEventAsLoadable
    (vevent2WindowUpdateEvent            *pEvent);

vinstance                           *vevent2WindowUpdateEventAsInstance
    (vevent2WindowUpdateEvent            *pEvent);

vevent2WindowUpdateEventClass       *vevent2WindowUpdateEventGetClass
    (vevent2WindowUpdateEvent            *pEvent);

vbool                                vevent2WindowUpdateEventValidate
    (vevent2WindowUpdateEvent            *pEvent);

void                                 vevent2WindowUpdateEventAssert
    (vevent2WindowUpdateEvent            *pEvent);

void                                 vevent2WindowUpdateEventHandledAssert
    (vevent2WindowUpdateEvent            *pEvent,
     vdebugAssertionHandler               handler,
     void                                *pData);

/* class vevent2Handler */

vevent2HandlerClass                 *vevent2HandlerClassGetDefault
    (void                                 );

vloadableClass                      *vevent2HandlerClassAsLoadableClass
    (vevent2HandlerClass                 *pClass);

vinstanceClass                      *vevent2HandlerClassAsInstanceClass
    (vevent2HandlerClass                 *pClass);

vbool                                vevent2HandlerClassValidate
    (vevent2HandlerClass                 *pClass);

void                                 vevent2HandlerClassAssert
    (vevent2HandlerClass                 *pClass);

void                                 vevent2HandlerClassHandledAssert
    (vevent2HandlerClass                 *pClass,
     vdebugAssertionHandler               handler,
     void                                *pData);

vevent2Handler                      *vevent2HandlerCreate
    (void                                 );

vevent2Handler                      *vevent2HandlerCreateOfClass
    (vevent2HandlerClass                 *pClass);

void                                 vevent2HandlerInit
    (vevent2Handler                      *pHandler);

void                                 vevent2HandlerInitOfClass
    (vevent2Handler                      *pHandler,
     vevent2HandlerClass                 *pClass);

void                                 vevent2HandlerCopy
    (vevent2Handler                      *pSource,
     vevent2Handler                      *pDest);

void                                 vevent2HandlerShare
    (vevent2Handler                      *pHandler);

void                                 vevent2HandlerRelease
    (vevent2Handler                      *pHandler);

vbool                                vevent2HandlerIsShared
    (vevent2Handler                      *pHandler);

vbool                                vevent2HandlerHandleEvent
    (vevent2Handler                      *pHandler,
     vevent2                             *pEvent);

vloadable                           *vevent2HandlerAsLoadable
    (vevent2Handler                      *pHandler);

vinstance                           *vevent2HandlerAsInstance
    (vevent2Handler                      *pHandler);

vevent2HandlerClass                 *vevent2HandlerGetClass
    (vevent2Handler                      *pHandler);

vbool                                vevent2HandlerValidate
    (vevent2Handler                      *pHandler);

void                                 vevent2HandlerAssert
    (vevent2Handler                      *pHandler);

void                                 vevent2HandlerHandledAssert
    (vevent2Handler                      *pHandler,
     vdebugAssertionHandler               assertionHandler,
     void                                *pData);

/* class vevent2Loop */

vevent2LoopClass                    *vevent2LoopClassGetDefault
    (void                                 );

vevent2HandlerClass                 *vevent2LoopClassAsHandlerClass
    (vevent2LoopClass                    *pClass);

vbool                                vevent2LoopClassValidate
    (vevent2LoopClass                    *pClass);

void                                 vevent2LoopClassAssert
    (vevent2LoopClass                    *pClass);

void                                 vevent2LoopClassHandledAssert
    (vevent2LoopClass                    *pClass,
     vdebugAssertionHandler               handler,
     void                                *pData);

vevent2Loop                         *vevent2LoopGetDefault
    (void                                 );

void                                 vevent2LoopSetCurrent
    (vevent2Loop                         *pLoop);

vevent2Loop                         *vevent2LoopGetCurrent
    (void                                 );

vevent2Loop                         *vevent2LoopCreate
    (void                                 );

vevent2Loop                         *vevent2LoopCreateOfClass
    (vevent2LoopClass                    *pClass);

void                                 vevent2LoopInit
    (vevent2Loop                         *pLoop);

void                                 vevent2LoopInitOfClass
    (vevent2Loop                         *pLoop,
     vevent2LoopClass                    *pClass);

void                                 vevent2LoopRelease
    (vevent2Loop                         *pLoop);

void                                 vevent2LoopSetHandler
    (vevent2Loop                         *pLoop,
     vevent2Handler                      *pHandler);

vevent2Handler                      *vevent2LoopGetHandler
    (vevent2Loop                         *pLoop);

void                                 vevent2LoopSetDriver
    (vevent2Loop                         *pLoop,
     vevent2Driver                       *pDriver);

vevent2Driver                       *vevent2LoopGetDriver
    (vevent2Loop                         *pLoop);

void                                 vevent2LoopSetWaitProc
    (vevent2Loop                         *pLoop,
     vevent2WaitProc                     *pWaitProc);

vevent2WaitProc                     *vevent2LoopGetWaitProc
    (vevent2Loop                         *pLoop);

void                                 vevent2LoopAddQuitter
    (vevent2Loop                         *pLoop,
     vevent2Quitter                      *pQuitter);

void                                 vevent2LoopRemoveQuitter
    (vevent2Loop                         *pLoop,
     vevent2Quitter                      *pQuitter);

void                                 vevent2LoopPost
    (vevent2Loop                         *pLoop,
     vevent2                             *pEvent);

void                                 vevent2LoopPostLater
    (vevent2Loop                         *pLoop,
     vevent2                             *pEvent);

void                                 vevent2LoopGoNative
    (vevent2Loop                         *pLoop);

void                                 vevent2LoopRun
    (vevent2Loop                         *pLoop);

void                                 vevent2LoopStop
    (vevent2Loop                         *pLoop);

vbool                                vevent2LoopQuit
    (vevent2Loop                         *pLoop);

void                                 vevent2LoopForceQuit
    (vevent2Loop                         *pLoop);

void                                 vevent2LoopFlush
    (vevent2Loop                         *pLoop,
     unsigned long                       *sec,
     unsigned long                       *nsec);

void                                 vevent2LoopBlock
    (vevent2Loop                         *pLoop,
     unsigned long                        sec,
     unsigned long                        nsec);

void                                 vevent2LoopUnblock
    (vevent2Loop                         *pLoop);

vbool                                vevent2LoopPreBlock
    (vevent2Loop                         *pLoop,
     unsigned long                       *sec,
     unsigned long                       *nsec);

void                                 vevent2LoopAddPreBlocker
    (vevent2Loop                         *pLoop,
     vevent2PreBlocker                   *pPreBlocker);

void                                 vevent2LoopRemovePreBlocker
    (vevent2Loop                         *pLoop,
     vevent2PreBlocker                   *pPreBlocker);

void                                 vevent2LoopAddSystemEventHandler
    (vevent2Loop                         *pLoop,
     vevent2SystemEventHandler           *pHandler);

void                                 vevent2LoopRemoveSystemEventHandler
    (vevent2Loop                         *pLoop,
     vevent2SystemEventHandler           *pHandler);

void                                 vevent2LoopFlushSystemEvents
    (vevent2Loop                         *pLoop);

void                                 vevent2LoopPreQueueEvent
    (vevent2Loop                         *pLoop,
     vevent2                             *pEvent);

void                                 vevent2LoopRemovePreQueuedEvent
    (vevent2Loop                         *pLoop,
     vevent2                             *pEvent);

void                                 vevent2LoopRemoveEvent
    (vevent2Loop                         *pLoop,
     vevent2                             *pEvent);

vevent2                             *vevent2LoopNext
    (vevent2Loop                         *pLoop,
     unsigned long                       *pSeconds,
     unsigned long                       *pNanoseconds);

vevent2                             *vevent2LoopPeek
    (vevent2Loop                        *pLoop);

vevent2Handler                      *vevent2LoopAsHandler
    (vevent2Loop                         *pLoop);

vevent2LoopClass                    *vevent2LoopGetClass
    (vevent2Loop                         *pLoop);

vbool                                vevent2LoopValidate
    (vevent2Loop                         *pLoop);

void                                 vevent2LoopAssert
    (vevent2Loop                         *pLoop);

void                                 vevent2LoopHandledAssert
    (vevent2Loop                         *pLoop,
     vdebugAssertionHandler               handler,
     void                                *pData);

void                                 vevent2LoopAssertNonQueued
    (vevent2Loop                         *pLoop,
     vevent2                             *pEvent);

/* class vevent2Driver */

vevent2DriverClass                  *vevent2DriverClassGetDefault
    (void                                 );

vinstanceClass                      *vevent2DriverClassAsInstanceClass
    (vevent2DriverClass                  *pClass);

vbool                                vevent2DriverClassValidate
    (vevent2DriverClass                  *pClass);

void                                 vevent2DriverClassAssert
    (vevent2DriverClass                  *pClass);

void                                 vevent2DriverClassHandledAssert
    (vevent2DriverClass                  *pClass,
     vdebugAssertionHandler               handler,
     void                                *pData);

vevent2Driver                       *vevent2DriverCreate
    (void                                 );

vevent2Driver                       *vevent2DriverCreateOfClass
    (vevent2DriverClass                  *pClass);

void                                 vevent2DriverInit
    (vevent2Driver                       *pDriver);

void                                 vevent2DriverInitOfClass
    (vevent2Driver                       *pDriver,
     vevent2DriverClass                  *pClass);

void                                 vevent2DriverShare
    (vevent2Driver                       *pDriver);

void                                 vevent2DriverRelease
    (vevent2Driver                       *pDriver);

vbool                                vevent2DriverIsShared
    (vevent2Driver                       *pDriver);

void                                 vevent2DriverSetWaitProc
    (vevent2Driver                       *pDriver,
     vevent2WaitProc                     *pWaitProc);

vevent2WaitProc                     *vevent2DriverGetWaitProc
    (vevent2Driver                       *pDriver);

void                                 vevent2DriverAddSystemEventHandler
    (vevent2Driver                       *pDriver,
     vevent2SystemEventHandler           *pHandler);

void                                 vevent2DriverRemoveSystemEventHandler
    (vevent2Driver                       *pDriver,
     vevent2SystemEventHandler           *pHandler);

void                                 vevent2DriverAddPreBlocker
    (vevent2Driver                       *pDriver,
     vevent2PreBlocker                   *pPreBlocker);

void                                 vevent2DriverRemovePreBlocker
    (vevent2Driver                       *pDriver,
     vevent2PreBlocker                   *pPreBlocker);

vbool                                vevent2DriverPreBlock
    (vevent2Driver                       *pDriver,
     unsigned long                       *sec,
     unsigned long                       *nsec);

void                                 vevent2DriverBlock
    (vevent2Driver                       *pDriver,
     unsigned long                        sec,
     unsigned long                        nsec);

void                                 vevent2DriverUnblock
    (vevent2Driver                       *pDriver);

void                                 vevent2DriverHandleSystemEvents
    (vevent2Driver                       *pDriver);

void                                 vevent2DriverGoNative
    (vevent2Driver                       *pDriver);

vinstance                           *vevent2DriverAsInstance
    (vevent2Driver                       *pDriver);

vevent2DriverClass                  *vevent2DriverGetClass
    (vevent2Driver                       *pDriver);

vbool                                vevent2DriverValidate
    (vevent2Driver                       *pDriver);

void                                 vevent2DriverAssert
    (vevent2Driver                       *pDriver);

void                                 vevent2DriverHandledAssert
    (vevent2Driver                       *pDriver,
     vdebugAssertionHandler               handler,
     void                                *pData);

/* class vevent2PreBlocker */

vevent2PreBlockerClass              *vevent2PreBlockerClassGetDefault
    (void                                 );

vinstanceClass                      *vevent2PreBlockerClassAsInstanceClass
    (vevent2PreBlockerClass              *pClass);

vbool                                vevent2PreBlockerClassValidate
    (vevent2PreBlockerClass              *pClass);

void                                 vevent2PreBlockerClassAssert
    (vevent2PreBlockerClass              *pClass);

void                                 vevent2PreBlockerClassHandledAssert
    (vevent2PreBlockerClass              *pClass,
     vdebugAssertionHandler               handler,
     void                                *pData);

vevent2PreBlocker                   *vevent2PreBlockerCreate
    (void                                 );

vevent2PreBlocker                   *vevent2PreBlockerCreateOfClass
    (vevent2PreBlockerClass              *pClass);

void                                 vevent2PreBlockerInit
    (vevent2PreBlocker                   *pPreBlocker);

void                                 vevent2PreBlockerInitOfClass
    (vevent2PreBlocker                   *pPreBlocker,
     vevent2PreBlockerClass              *pClass);

void                                 vevent2PreBlockerShare
    (vevent2PreBlocker                   *pPreBlocker);

void                                 vevent2PreBlockerRelease
    (vevent2PreBlocker                   *pPreBlocker);

vbool                                vevent2PreBlockerIsShared
    (vevent2PreBlocker                   *pPreBlocker);

vbool                                vevent2PreBlockerPreBlock
    (vevent2PreBlocker                   *PreBlocker,
     unsigned long                       *pSec,
     unsigned long                       *pNSec);

vinstance                           *vevent2PreBlockerAsInstance
    (vevent2PreBlocker                   *PreBlocker);

vevent2PreBlockerClass              *vevent2PreBlockerGetClass
    (vevent2PreBlocker                   *PreBlocker);

vbool                                vevent2PreBlockerValidate
    (vevent2PreBlocker                   *PreBlocker);

void                                 vevent2PreBlockerAssert
    (vevent2PreBlocker                   *PreBlocker);

void                                 vevent2PreBlockerHandledAssert
    (vevent2PreBlocker                   *PreBlocker,
     vdebugAssertionHandler               handler,
     void                                *pData);

/* class vevent2Quitter     */

vevent2QuitterClass                 *vevent2QuitterClassGetDefault
    (void                                 );

vinstanceClass                      *vevent2QuitterClassAsInstanceClass
    (vevent2QuitterClass                 *pClass);

vbool                                vevent2QuitterClassValidate
    (vevent2QuitterClass                 *pClass);

void                                 vevent2QuitterClassAssert
    (vevent2QuitterClass                 *pClass);

void                                 vevent2QuitterClassHandledAssert
    (vevent2QuitterClass                 *pClass,
     vdebugAssertionHandler               handler,
     void                                *pData);

vevent2Quitter                      *vevent2QuitterCreate
    (void                                 );

vevent2Quitter                      *vevent2QuitterCreateOfClass
    (vevent2QuitterClass                 *pClass);

void                                 vevent2QuitterInit
    (vevent2Quitter                      *pQuitter);

void                                 vevent2QuitterInitOfClass
    (vevent2Quitter                      *pQuitter,
     vevent2QuitterClass                 *pClass);

void                                 vevent2QuitterShare
    (vevent2Quitter                      *pQuitter);

void                                 vevent2QuitterRelease
    (vevent2Quitter                      *pQuitter);

vbool                                vevent2QuitterIsShared
    (vevent2Quitter                      *pQuitter);

vbool                                vevent2QuitterQuit
    (vevent2Quitter                      *pQuitter);

void                                 vevent2QuitterForceQuit
    (vevent2Quitter                      *pQuitter);

vinstance                           *vevent2QuitterAsInstance
    (vevent2Quitter                      *pQuitter);

vevent2QuitterClass                 *vevent2QuitterGetClass
    (vevent2Quitter                      *pQuitter);

vbool                                vevent2QuitterValidate
    (vevent2Quitter                      *pQuitter);

void                                 vevent2QuitterAssert
    (vevent2Quitter                      *pQuitter);

void                                 vevent2QuitterHandledAssert
    (vevent2Quitter                      *pQuitter,
     vdebugAssertionHandler               handler,
     void                                *pData);

/* class vevent2SystemEventHandler */

vevent2SystemEventHandlerClass      *vevent2SystemEventHandlerClassGetDefault
    (void                                 );

vinstanceClass                  *vevent2SystemEventHandlerClassAsInstanceClass
    (vevent2SystemEventHandlerClass      *pClass);

vbool                                vevent2SystemEventHandlerClassValidate
    (vevent2SystemEventHandlerClass      *pClass);

void                                 vevent2SystemEventHandlerClassAssert
    (vevent2SystemEventHandlerClass      *pClass);

void                                 vevent2SystemEventHandlerClassHandledAssert
    (vevent2SystemEventHandlerClass      *pClass,
     vdebugAssertionHandler               handler,
     void                                *pData);

vevent2SystemEventHandler           *vevent2SystemEventHandlerCreate
    (void                                 );

vevent2SystemEventHandler           *vevent2SystemEventHandlerCreateOfClass
    (vevent2SystemEventHandlerClass      *pClass);

void                                 vevent2SystemEventHandlerInit
    (vevent2SystemEventHandler           *pHandler);

void                                 vevent2SystemEventHandlerInitOfClass
    (vevent2SystemEventHandler           *pHandler,
     vevent2SystemEventHandlerClass      *pClass);

void                                 vevent2SystemEventHandlerShare
    (vevent2SystemEventHandler           *pHandler);

void                                 vevent2SystemEventHandlerRelease
    (vevent2SystemEventHandler           *pHandler);

vbool                                vevent2SystemEventHandlerIsShared
    (vevent2SystemEventHandler           *pHandler);

void                                 vevent2SystemEventHandlerFlush
    (vevent2SystemEventHandler           *pHandler);

vinstance                           *vevent2SystemEventHandlerAsInstance
    (vevent2SystemEventHandler           *pHandler);

vevent2SystemEventHandlerClass      *vevent2SystemEventHandlerGetClass
    (vevent2SystemEventHandler           *pHandler);

vbool                                vevent2SystemEventHandlerValidate
    (vevent2SystemEventHandler           *pHandler);

void                                 vevent2SystemEventHandlerAssert
    (vevent2SystemEventHandler           *pHandler);

void                                 vevent2SystemEventHandlerHandledAssert
    (vevent2SystemEventHandler           *pHandler,
     vdebugAssertionHandler               handler,
     void                                *pData);


/*
 * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * *
 */

struct vevent2Iterator
{
    viterator                     super;
#if (vdebugDEBUG)
    int                           signature;
#endif
};

#define vevent2IteratorCLASS(CLASS, ITERATOR) \
    viteratorCLASS(CLASS, ITERATOR)

struct vevent2IteratorClass
{
    vevent2IteratorCLASS(vevent2IteratorClass, vevent2Iterator);
};

#define vevent2CLASS(CLASS, EVENT) \
    vloadableCLASS(CLASS, EVENT); \
    vclassVARIABLE(vevent2TYPE, vevent2Type); \
    vclassMETHOD(vevent2SET_HANDLER, \
                 (EVENT *pEvent, vevent2Handler *pHandler)); \
    vclassMETHOD(vevent2SET_LOOP, (EVENT *pEvent, vevent2Loop *pLoop)); \
    vclassMETHOD(vevent2NOTIFY_QUEUED, (EVENT *pEvent, vevent2Loop *pLoop))

struct vevent2Class
{
    vevent2CLASS(vevent2Class, vevent2);
};

#define vevent2WindowEventCLASS(CLASS, EVENT) \
    vevent2CLASS(CLASS, EVENT)

struct vevent2WindowEventClass
{
    vevent2WindowEventCLASS(vevent2WindowEventClass, vevent2WindowEvent);
};

#define vevent2WindowConfigureEventCLASS(CLASS, EVENT) \
    vevent2WindowEventCLASS(CLASS, EVENT)

struct vevent2WindowConfigureEventClass
{
    vevent2WindowConfigureEventCLASS(vevent2WindowConfigureEventClass,
                                     vevent2WindowConfigureEvent);
};

#define vevent2FocusEventCLASS(CLASS, EVENT) \
    vevent2WindowEventCLASS(CLASS, EVENT)

struct vevent2FocusEventClass
{
    vevent2FocusEventCLASS(vevent2FocusEventClass, vevent2FocusEvent);
};

#define vevent2FocusAcquireEventCLASS(CLASS, EVENT) \
    vevent2FocusEventCLASS(CLASS, EVENT)

struct vevent2FocusAcquireEventClass
{
    vevent2FocusAcquireEventCLASS(vevent2FocusAcquireEventClass,
                                  vevent2FocusAcquireEvent);
};

#define vevent2FocusLoseEventCLASS(CLASS, EVENT) \
    vevent2FocusEventCLASS(CLASS, EVENT)

struct vevent2FocusLoseEventClass
{
    vevent2FocusLoseEventCLASS(vevent2FocusLoseEventClass,
                               vevent2FocusLoseEvent);
};

#define vevent2PointerEventCLASS(CLASS, EVENT) \
    vevent2WindowEventCLASS(CLASS, EVENT)

struct vevent2PointerEventClass
{
    vevent2PointerEventCLASS(vevent2PointerEventClass, vevent2PointerEvent);
};

#define vevent2ButtonEventCLASS(CLASS, EVENT) \
    vevent2PointerEventCLASS(CLASS, EVENT)

struct vevent2ButtonEventClass
{
    vevent2ButtonEventCLASS(vevent2ButtonEventClass, vevent2ButtonEvent);
};

#define vevent2ButtonDownEventCLASS(CLASS, EVENT) \
    vevent2ButtonEventCLASS(CLASS, EVENT)

struct vevent2ButtonDownEventClass
{
    vevent2ButtonDownEventCLASS(vevent2ButtonDownEventClass,
                                vevent2ButtonDownEvent);
};

#define vevent2ButtonUpEventCLASS(CLASS, EVENT) \
    vevent2ButtonEventCLASS(CLASS, EVENT)

struct vevent2ButtonUpEventClass
{
    vevent2ButtonUpEventCLASS(vevent2ButtonUpEventClass, vevent2ButtonUpEvent);
};

#define vevent2PointerEnterEventCLASS(CLASS, EVENT) \
    vevent2PointerEventCLASS(CLASS, EVENT)

struct vevent2PointerEnterEventClass
{
    vevent2PointerEnterEventCLASS(vevent2PointerEnterEventClass,
                                  vevent2PointerEnterEvent);
};

#define vevent2KeyEventCLASS(CLASS, EVENT) \
    vevent2PointerEventCLASS(CLASS, EVENT)

struct vevent2KeyEventClass
{
    vevent2KeyEventCLASS(vevent2KeyEventClass, vevent2KeyEvent);
};

#define vevent2KeyDownEventCLASS(CLASS, EVENT) \
    vevent2KeyEventCLASS(CLASS, EVENT)

struct vevent2KeyDownEventClass
{
    vevent2KeyDownEventCLASS(vevent2KeyDownEventClass, vevent2KeyDownEvent);
};

#define vevent2KeyUpEventCLASS(CLASS, EVENT) \
    vevent2KeyEventCLASS(CLASS, EVENT)

struct vevent2KeyUpEventClass
{
    vevent2KeyUpEventCLASS(vevent2KeyUpEventClass, vevent2KeyUpEvent);
};

#define vevent2PointerLeaveEventCLASS(CLASS, EVENT) \
    vevent2PointerEventCLASS(CLASS, EVENT)

struct vevent2PointerLeaveEventClass
{
    vevent2PointerLeaveEventCLASS(vevent2PointerLeaveEventClass,
                                  vevent2PointerLeaveEvent);
};

#define vevent2MotionEventCLASS(CLASS, EVENT) \
    vevent2PointerEventCLASS(CLASS, EVENT)

struct vevent2MotionEventClass
{
    vevent2MotionEventCLASS(vevent2MotionEventClass, vevent2MotionEvent);
};

#define vevent2WindowStateEventCLASS(CLASS, EVENT) \
    vevent2WindowEventCLASS(CLASS, EVENT)

struct vevent2WindowStateEventClass
{
    vevent2WindowStateEventCLASS(vevent2WindowStateEventClass,
                                 vevent2WindowStateEvent);
};

#define vevent2WindowUpdateEventCLASS(CLASS, EVENT) \
    vevent2WindowEventCLASS(CLASS, EVENT)

struct vevent2WindowUpdateEventClass
{
    vevent2WindowUpdateEventCLASS(vevent2WindowUpdateEventClass,
                                  vevent2WindowUpdateEvent);
};

struct vevent2Handler
{
    vloadable                     super;
    short                         shareCount;
#if (vdebugDEBUG)
    int                           signature;
#endif
};

#define vevent2HandlerCLASS(CLASS, HANDLER) \
    vloadableCLASS(CLASS, HANDLER); \
    vclassMETHOD_RET(vevent2HandlerHANDLE_EVENT, vbool, \
                     (HANDLER *h, vevent2 *e))

struct vevent2HandlerClass
{
    vevent2HandlerCLASS(vevent2HandlerClass, vevent2Handler);
};

struct vevent2Loop
{
    vevent2Handler                super;
    vevent2Handler               *pHandler;
    volatile vbool                scanPreQueued;
    vevent2Driver                *pDriver;
    vpq                           now;
    vpq                           future;
    vpq                         **ppLater;
    vevent2                     **ppPreQueued;
    vevent2                     **ppPreQueuedEnd;
    vevent2                     **ppPreQueuedMax;
    vevent2Quitter               *pQuitter;
    vevent2                      *quitEvent;
    vbyte                         stops;
    vbyte                         depth; 
    vbyte                         nLaterSlots;
    vbool                         scanLaterQueues;
    vmutex                        mutex;
#if (vdebugDEBUG)
    int                           signature;
#endif
};

#define vevent2LoopCLASS(CLASS, LOOP) \
    vevent2HandlerCLASS(CLASS, LOOP); \
    vclassMETHOD    (vevent2LoopRUN, (LOOP *pLoop)); \
    vclassMETHOD    (vevent2LoopSTOP, (LOOP *pLoop)); \
    vclassMETHOD_RET(vevent2LoopQUIT, vbool, (LOOP *pLoop)); \
    vclassMETHOD    (vevent2LoopFORCE_QUIT, (LOOP *pLoop)); \
    vclassMETHOD_RET(vevent2LoopPRE_BLOCK, vbool, \
                     (LOOP *pLoop, unsigned long *sec, unsigned long *nsec)); \
    vclassMETHOD(vevent2LoopFLUSH, \
                 (LOOP *pLoop, unsigned long *sec, unsigned long *nsec)); \
    vclassMETHOD(vevent2LoopBLOCK, \
                 (LOOP *pLoop, unsigned long sec, unsigned long nsec)); \
    vclassMETHOD(vevent2LoopUNBLOCK, \
                 (LOOP *pLoop)); \
    vclassMETHOD(vevent2LoopFLUSH_SYSTEM_EVENTS, \
                 (LOOP *pLoop)); \
    vclassMETHOD(vevent2LoopGO_NATIVE, \
                 (LOOP *pLoop)); \
    vclassMETHOD(vevent2LoopADD_SYSTEM_EVENT_HANDLER, \
                 (LOOP *pLoop, vevent2SystemEventHandler *pHandler)); \
    vclassMETHOD(vevent2LoopREMOVE_SYSTEM_EVENT_HANDLER, \
                 (LOOP *pLoop, vevent2SystemEventHandler *pHandler)); \
    vclassMETHOD(vevent2LoopADD_PRE_BLOCKER, \
                 (LOOP *pLoop, vevent2PreBlocker *pPreBlocker)); \
    vclassMETHOD(vevent2LoopREMOVE_PRE_BLOCKER, \
                 (LOOP *pLoop, vevent2PreBlocker *pPreBlocker)); \
    vclassMETHOD(vevent2LoopADD_QUITTER, \
                 (LOOP *pLoop, vevent2Quitter *pQuitter)); \
    vclassMETHOD(vevent2LoopREMOVE_QUITTER, \
                 (LOOP *pLoop, vevent2Quitter *pQuitter)); \
    vclassMETHOD_RET(vevent2LoopNEXT, vevent2 *, \
                     (LOOP *pLoop, unsigned long*pSec, unsigned long *pNSec));\
    vclassMETHOD_RET(vevent2LoopPEEK, vevent2 *, \
                     (LOOP *pLoop)); \
    vclassMETHOD(vevent2LoopPRE_QUEUE_EVENT, \
                 (LOOP *pLoop, vevent2 *pEvent)); \
    vclassMETHOD(vevent2LoopREMOVE_PRE_QUEUED_EVENT, \
                 (LOOP *pLoop, vevent2 *pEvent)); \
    vclassMETHOD(vevent2LoopREMOVE_EVENT, \
                 (LOOP *pLoop, vevent2 *pEvent))

struct vevent2LoopClass
{
    vevent2LoopCLASS(vevent2LoopClass, vevent2Loop);
};

struct vevent2Driver
{
    vinstance                     super;
    vevent2WaitProc              *pWaitProc;
    short                         shareCount;
    vevent2SystemEventHandler   **ppSystemHandler;
    int                           nSystemHandlers;
    vevent2PreBlocker           **ppPreBlocker;
    int                           nPreBlockers;
#if (vdebugDEBUG)
    int                           signature;
#endif
};

#define vevent2DriverCLASS(CLASS, DRIVER)                                   \
    vinstanceCLASS(CLASS, DRIVER);                                          \
    vclassMETHOD(vevent2DriverADD_SYSTEM_EVENT_HANDLER,                     \
                 (DRIVER *pDriver, vevent2SystemEventHandler *pHandler));   \
    vclassMETHOD(vevent2DriverREMOVE_SYSTEM_EVENT_HANDLER,                  \
                 (DRIVER *pDriver, vevent2SystemEventHandler *pHandler));   \
    vclassMETHOD(vevent2DriverADD_PRE_BLOCKER,                              \
                 (DRIVER *pDriver, vevent2PreBlocker *pPreBlocker));        \
    vclassMETHOD(vevent2DriverREMOVE_PRE_BLOCKER,                           \
                 (DRIVER *pDriver, vevent2PreBlocker *pPreBlocker));        \
    vclassMETHOD_RET(vevent2DriverPRE_BLOCK, vbool,                         \
                     (DRIVER *pDriver,                                      \
                      unsigned long *sec, unsigned long *nsec));            \
    vclassMETHOD(vevent2DriverBLOCK,                                        \
                 (DRIVER *pDriver, unsigned long sec, unsigned long nsec)); \
    vclassMETHOD(vevent2DriverUNBLOCK,                                      \
                 (DRIVER *pDriver));                                        \
    vclassMETHOD(vevent2DriverHANDLE_SYSTEM_EVENTS,                         \
                 (DRIVER *pDriver));                                        \
    vclassMETHOD(vevent2DriverGO_NATIVE,                                    \
                 (DRIVER *pDriver))

struct vevent2DriverClass
{
    vevent2DriverCLASS(vevent2DriverClass, vevent2Driver);
};

struct vevent2PreBlocker
{
    vinstance                     super;
    vevent2PreBlocker            *pNext;
    short                         shareCount;
#if (vdebugDEBUG)
    int                           signature;
#endif
};

#define vevent2PreBlockerCLASS(CLASS, PRE_BLOCKER) \
    vinstanceCLASS(CLASS, PRE_BLOCKER); \
    vclassMETHOD_RET(vevent2PreBlockerPRE_BLOCK, vbool, \
                     (PRE_BLOCKER *p, \
                      unsigned long *pSec, unsigned long *pNSec))

struct vevent2PreBlockerClass
{
    vevent2PreBlockerCLASS(vevent2PreBlockerClass, vevent2PreBlocker);
};

struct vevent2Quitter
{
    vinstance                     super;
    vevent2Quitter               *pNext;
    short                         shareCount;
#if (vdebugDEBUG)
    int                           signature;
#endif
};

#define vevent2QuitterCLASS(CLASS, QUITTER) \
    vinstanceCLASS(CLASS, QUITTER); \
    vclassMETHOD_RET(vevent2QuitterQUIT, vbool, (QUITTER *pQuitter)); \
    vclassMETHOD    (vevent2QuitterFORCE_QUIT, (QUITTER *pQuitter))

struct vevent2QuitterClass
{
    vevent2QuitterCLASS(vevent2QuitterClass, vevent2Quitter);
};

struct vevent2SystemEventHandler
{
    vinstance                     super;
    vevent2SystemEventHandler    *pNext;
    short                         shareCount;
#if (vdebugDEBUG)
    int                           signature;
#endif
};

#define vevent2SystemEventHandlerCLASS(CLASS, HANDLER) \
    vinstanceCLASS(CLASS, HANDLER); \
    vclassMETHOD(vevent2SystemEventHandlerFLUSH, (HANDLER *h))

struct vevent2SystemEventHandlerClass
{
    vevent2SystemEventHandlerCLASS(vevent2SystemEventHandlerClass,
                                   vevent2SystemEventHandler);
};


/*
 * * * * * * * * * * PRIVATE exported constants * * * * * * * * * *
 */

enum {
    _vevent2SYNC     = 0x1,
    _vevent2BCNEWBIE = 0x2
};


/*
 * * * * * * * * * * PRIVATE exported variables * * * * * * * * * *
 */

extern vportLINK vbool                _vevent2ManagerInitializing;


/*
 * * * * * * * * * * PRIVATE exported prototypes * * * * * * * * * *
 */

int									 _vevent2HandleTarget
    (vevent2                             *event);

vevent2Handler                      *_vevent2GetTargetHandler
    (void);

void                                 _vevent2ClassHandledAssert
    (vevent2Class                        *pClass,
     vdebugAssertionHandler               handler,
     void                                *pData,
     const char                          *tag,
     const char                          *file,
     int                                  line);

void                                 _vevent2HandledAssert
    (vevent2                             *pEvent,
     vdebugAssertionHandler               handler,
     void                                *pData,
     const char                          *tag,
     const char                          *file,
     int                                  line);

void                                 _vevent2WindowEventClassHandledAssert
    (vevent2WindowEventClass             *pClass,
     vdebugAssertionHandler               handler,
     void                                *pData,
     const char                          *tag,
     const char                          *file,
     int                                  line);

void                                 _vevent2WindowEventHandledAssert
    (vevent2WindowEvent                  *pEvent,
     vdebugAssertionHandler               handler,
     void                                *pData,
     const char                          *tag,
     const char                          *file,
     int                                  line);

void                             _vevent2WindowConfigureEventClassHandledAssert
    (vevent2WindowConfigureEventClass    *pClass,
     vdebugAssertionHandler               handler,
     void                                *pData,
     const char                          *tag,
     const char                          *file,
     int                                  line);

void                                 _vevent2WindowConfigureEventHandledAssert
    (vevent2WindowConfigureEvent         *pEvent,
     vdebugAssertionHandler               handler,
     void                                *pData,
     const char                          *tag,
     const char                          *file,
     int                                  line);

void                                 _vevent2FocusEventClassHandledAssert
    (vevent2FocusEventClass              *pClass,
     vdebugAssertionHandler               handler,
     void                                *pData,
     const char                          *tag,
     const char                          *file,
     int                                  line);

void                                 _vevent2FocusEventHandledAssert
    (vevent2FocusEvent                   *pEvent,
     vdebugAssertionHandler               handler,
     void                                *pData,
     const char                          *tag,
     const char                          *file,
     int                                  line);

void                                _vevent2FocusAcquireEventClassHandledAssert
    (vevent2FocusAcquireEventClass       *pClass,
     vdebugAssertionHandler               handler,
     void                                *pData,
     const char                          *tag,
     const char                          *file,
     int                                  line);

void                                 _vevent2FocusAcquireEventHandledAssert
    (vevent2FocusAcquireEvent            *pEvent,
     vdebugAssertionHandler               handler,
     void                                *pData,
     const char                          *tag,
     const char                          *file,
     int                                  line);

void                                 _vevent2FocusLoseEventClassHandledAssert
    (vevent2FocusLoseEventClass          *pClass,
     vdebugAssertionHandler               handler,
     void                                *pData,
     const char                          *tag,
     const char                          *file,
     int                                  line);

void                                 _vevent2FocusLoseEventHandledAssert
    (vevent2FocusLoseEvent               *pEvent,
     vdebugAssertionHandler               handler,
     void                                *pData,
     const char                          *tag,
     const char                          *file,
     int                                  line);

void                                 _vevent2KeyEventClassHandledAssert
    (vevent2KeyEventClass                *pClass,
     vdebugAssertionHandler               handler,
     void                                *pData,
     const char                          *tag,
     const char                          *file,
     int                                  line);

void                                 _vevent2KeyEventHandledAssert
    (vevent2KeyEvent                     *pEvent,
     vdebugAssertionHandler               handler,
     void                                *pData,
     const char                          *tag,
     const char                          *file,
     int                                  line);

void                                 _vevent2KeyDownEventClassHandledAssert
    (vevent2KeyDownEventClass            *pClass,
     vdebugAssertionHandler               handler,
     void                                *pData,
     const char                          *tag,
     const char                          *file,
     int                                  line);

void                                 _vevent2KeyDownEventHandledAssert
    (vevent2KeyDownEvent                 *pEvent,
     vdebugAssertionHandler               handler,
     void                                *pData,
     const char                          *tag,
     const char                          *file,
     int                                  line);

void                                 _vevent2KeyUpEventClassHandledAssert
    (vevent2KeyUpEventClass              *pClass,
     vdebugAssertionHandler               handler,
     void                                *pData,
     const char                          *tag,
     const char                          *file,
     int                                  line);

void                                 _vevent2KeyUpEventHandledAssert
    (vevent2KeyUpEvent                   *pEvent,
     vdebugAssertionHandler               handler,
     void                                *pData,
     const char                          *tag,
     const char                          *file,
     int                                  line);

void                                 _vevent2PointerEventClassHandledAssert
    (vevent2PointerEventClass            *pClass,
     vdebugAssertionHandler               handler,
     void                                *pData,
     const char                          *tag,
     const char                          *file,
     int                                  line);

void                                 _vevent2PointerEventHandledAssert
    (vevent2PointerEvent                 *pEvent,
     vdebugAssertionHandler               handler,
     void                                *pData,
     const char                          *tag,
     const char                          *file,
     int                                  line);

void                                 _vevent2ButtonEventClassHandledAssert
    (vevent2ButtonEventClass             *pClass,
     vdebugAssertionHandler               handler,
     void                                *pData,
     const char                          *tag,
     const char                          *file,
     int                                  line);

void                                 _vevent2ButtonEventHandledAssert
    (vevent2ButtonEvent                  *pEvent,
     vdebugAssertionHandler               handler,
     void                                *pData,
     const char                          *tag,
     const char                          *file,
     int                                  line);

void                                 _vevent2ButtonDownEventClassHandledAssert
    (vevent2ButtonDownEventClass         *pClass,
     vdebugAssertionHandler               handler,
     void                                *pData,
     const char                          *tag,
     const char                          *file,
     int                                  line);

void                                 _vevent2ButtonDownEventHandledAssert
    (vevent2ButtonDownEvent              *pEvent,
     vdebugAssertionHandler               handler,
     void                                *pData,
     const char                          *tag,
     const char                          *file,
     int                                  line);

void                                 _vevent2ButtonUpEventClassHandledAssert
    (vevent2ButtonUpEventClass           *pClass,
     vdebugAssertionHandler               handler,
     void                                *pData,
     const char                          *tag,
     const char                          *file,
     int                                  line);

void                                 _vevent2ButtonUpEventHandledAssert
    (vevent2ButtonUpEvent                *pEvent,
     vdebugAssertionHandler               handler,
     void                                *pData,
     const char                          *tag,
     const char                          *file,
     int                                  line);

void                                _vevent2PointerEnterEventClassHandledAssert
    (vevent2PointerEnterEventClass       *pClass,
     vdebugAssertionHandler               handler,
     void                                *pData,
     const char                          *tag,
     const char                          *file,
     int                                  line);

void                                 _vevent2PointerEnterEventHandledAssert
    (vevent2PointerEnterEvent            *pEvent,
     vdebugAssertionHandler               handler,
     void                                *pData,
     const char                          *tag,
     const char                          *file,
     int                                  line);

void                                _vevent2PointerLeaveEventClassHandledAssert
    (vevent2PointerLeaveEventClass       *pClass,
     vdebugAssertionHandler               handler,
     void                                *pData,
     const char                          *tag,
     const char                          *file,
     int                                  line);

void                                 _vevent2PointerLeaveEventHandledAssert
    (vevent2PointerLeaveEvent            *pEvent,
     vdebugAssertionHandler               handler,
     void                                *pData,
     const char                          *tag,
     const char                          *file,
     int                                  line);

void                               _vevent2MotionEventClassHandledAssert
    (vevent2MotionEventClass             *pClass,
     vdebugAssertionHandler               handler,
     void                                *pData,
     const char                          *tag,
     const char                          *file,
     int                                  line);

void                                 _vevent2MotionEventHandledAssert
    (vevent2MotionEvent                  *pEvent,
     vdebugAssertionHandler               handler,
     void                                *pData,
     const char                          *tag,
     const char                          *file,
     int                                  line);

void                                 _vevent2WindowStateEventClassHandledAssert
    (vevent2WindowStateEventClass        *pClass,
     vdebugAssertionHandler               handler,
     void                                *pData,
     const char                          *tag,
     const char                          *file,
     int                                  line);

void                                 _vevent2WindowStateEventHandledAssert
    (vevent2WindowStateEvent             *pEvent,
     vdebugAssertionHandler               handler,
     void                                *pData,
     const char                          *tag,
     const char                          *file,
     int                                  line);

void                                _vevent2WindowUpdateEventClassHandledAssert
    (vevent2WindowUpdateEventClass       *pClass,
     vdebugAssertionHandler               handler,
     void                                *pData,
     const char                          *tag,
     const char                          *file,
     int                                  line);

void                                 _vevent2WindowUpdateEventHandledAssert
    (vevent2WindowUpdateEvent            *pEvent,
     vdebugAssertionHandler               handler,
     void                                *pData,
     const char                          *tag,
     const char                          *file,
     int                                  line);

void                                 _vevent2HandlerClassHandledAssert
    (vevent2HandlerClass                 *pClass,
     vdebugAssertionHandler               handler,
     void                                *pData,
     const char                          *tag,
     const char                          *file,
     int                                  line);

void                                 _vevent2HandlerHandledAssert
    (vevent2Handler                      *pHandler,
     vdebugAssertionHandler               assertionHandler,
     void                                *pData,
     const char                          *tag,
     const char                          *file,
     int                                  line);

void                                 _vevent2LoopClassHandledAssert
    (vevent2LoopClass                    *pClass,
     vdebugAssertionHandler               handler,
     void                                *pData,
     const char                          *tag,
     const char                          *file,
     int                                  line);

void                                 _vevent2LoopHandledAssert
    (vevent2Loop                         *pLoop,
     vdebugAssertionHandler               handler,
     void                                *pData,
     const char                          *tag,
     const char                          *file,
     int                                  line);

void                                 _vevent2DriverClassHandledAssert
    (vevent2DriverClass                  *pClass,
     vdebugAssertionHandler               handler,
     void                                *pData,
     const char                          *tag,
     const char                          *file,
     int                                  line);

void                                 _vevent2DriverHandledAssert
    (vevent2Driver                       *pDriver,
     vdebugAssertionHandler               handler,
     void                                *pData,
     const char                          *tag,
     const char                          *file,
     int                                  line);

void                                 _vevent2PreBlockerClassHandledAssert
    (vevent2PreBlockerClass              *pClass,
     vdebugAssertionHandler               handler,
     void                                *pData,
     const char                          *tag,
     const char                          *file,
     int                                  line);

void                                 _vevent2PreBlockerHandledAssert
    (vevent2PreBlocker                   *pPreBlocker,
     vdebugAssertionHandler               handler,
     void                                *pData,
     const char                          *tag,
     const char                          *file,
     int                                  line);

void                                 _vevent2QuitterClassHandledAssert
    (vevent2QuitterClass                 *pClass,
     vdebugAssertionHandler               handler,
     void                                *pData,
     const char                          *tag,
     const char                          *file,
     int                                  line);

void                                 _vevent2QuitterHandledAssert
    (vevent2Quitter                      *pHandler,
     vdebugAssertionHandler               assertionHandler,
     void                                *pData,
     const char                          *tag,
     const char                          *file,
     int                                  line);

void                               _vevent2SystemEventHandlerClassHandledAssert
    (vevent2SystemEventHandlerClass      *pClass,
     vdebugAssertionHandler               handler,
     void                                *pData,
     const char                          *tag,
     const char                          *file,
     int                                  line);

void                                 _vevent2SystemEventHandlerHandledAssert
    (vevent2SystemEventHandler           *pHandler,
     vdebugAssertionHandler               assertionHandler,
     void                                *pData,
     const char                          *tag,
     const char                          *file,
     int                                  line);

/*
 * * * * * * * * * * PRIVATE function macro definitions * * * * * * * * * *
 */

#define vevent2GetDefaultClass() \
        vevent2ClassGetDefault()

#define vevent2GetDefaultWindowEventClass() \
        vevent2WindowEventClassGetDefault()

#define vevent2GetDefaultWindowConfigureEventClass() \
        vevent2WindowConfigureEventClassGetDefault()

#define vevent2GetDefaultFocusEventClass() \
        vevent2FocusEventClassGetDefault()

#define vevent2GetDefaultFocusAcquireEventClass() \
        vevent2FocusAcquireEventClassGetDefault()

#define vevent2GetDefaultFocusLoseEventClass() \
        vevent2FocusLoseEventClassGetDefault()

#define vevent2GetDefaultPointerEventClass() \
        vevent2PointerEventClassGetDefault()

#define vevent2GetDefaultButtonEventClass() \
        vevent2ButtonEventClassGetDefault()

#define vevent2GetDefaultButtonDownEventClass() \
        vevent2ButtonDownEventClassGetDefault()

#define vevent2GetDefaultButtonUpEventClass() \
        vevent2ButtonUpEventClassGetDefault()

#define vevent2GetDefaultPointerEnterEventClass() \
        vevent2PointerEnterEventClassGetDefault()

#define vevent2GetDefaultKeyEventClass() \
        vevent2KeyEventClassGetDefault()

#define vevent2GetDefaultKeyDownEventClass() \
        vevent2KeyDownEventClassGetDefault()

#define vevent2GetDefaultKeyUpEventClass() \
        vevent2KeyUpEventClassGetDefault()

#define vevent2GetDefaultPointerLeaveEventClass() \
        vevent2PointerLeaveEventClassGetDefault()

#define vevent2GetDefaultMotionEventClass() \
        vevent2MotionEventClassGetDefault()

#define vevent2GetDefaultWindowStateEventClass() \
        vevent2WindowStateEventClassGetDefault()

#define vevent2GetDefaultWindowUpdateEventClass() \
        vevent2WindowUpdateEventClassGetDefault()

#define vevent2GetDefaultHandlerClass() \
        vevent2HandlerClassGetDefault()

#define vevent2GetDefaultLoopClass() \
        vevent2LoopClassGetDefault()

#define vevent2GetDefaultDriverClass() \
        vevent2DriverClassGetDefault()

#define vevent2GetDefaultPreBlockerClass() \
        vevent2PreBlockerClassGetDefault()

#define vevent2GetDefaultQuitterClass() \
        vevent2QuitterClassGetDefault()

#define vevent2GetDefaultSystemEventHandlerClass() \
        vevent2SystemEventHandlerClassGetDefault()

#define vevent2GetDefaultLoop() \
        vevent2LoopGetDefault()

#define vevent2GetCurrentLoop() \
        vevent2LoopGetCurrent()

/* Asserts */

#define vevent2ClassHandledAssert(c, h, d) \
        _vevent2ClassHandledAssert(c, h, d, vdebugTAG, __FILE__, __LINE__)

#define vevent2HandledAssert(e, h, d) \
        _vevent2HandledAssert(e, h, d, vdebugTAG, __FILE__, __LINE__)

#define vevent2WindowEventClassHandledAssert(c, h, d) \
        _vevent2WindowEventClassHandledAssert(c, h, d, vdebugTAG, \
                                              __FILE__, __LINE__)

#define vevent2WindowEventHandledAssert(e, h, d) \
        _vevent2WindowEventHandledAssert(e, h, d, vdebugTAG, \
                                         __FILE__, __LINE__)

#define vevent2WindowConfigureEventClassHandledAssert(c, h, d) \
        _vevent2WindowConfigureEventClassHandledAssert(c, h, d, vdebugTAG, \
                                                       __FILE__, __LINE__)

#define vevent2WindowConfigureEventHandledAssert(e, h, d) \
        _vevent2WindowConfigureEventHandledAssert(e, h, d, vdebugTAG, \
                                                  __FILE__, __LINE__)

#define vevent2FocusEventClassHandledAssert(c, h, d) \
        _vevent2FocusEventClassHandledAssert(c, h, d, vdebugTAG, \
                                             __FILE__, __LINE__)

#define vevent2FocusEventHandledAssert(e, h, d) \
        _vevent2FocusEventHandledAssert(e, h, d, vdebugTAG, \
                                        __FILE__, __LINE__)

#define vevent2FocusAcquireEventClassHandledAssert(c, h, d) \
        _vevent2FocusAcquireEventClassHandledAssert(c, h, d, vdebugTAG, \
                                                    __FILE__, __LINE__)

#define vevent2FocusAcquireEventHandledAssert(e, h, d) \
        _vevent2FocusAcquireEventHandledAssert(e, h, d, vdebugTAG, \
                                               __FILE__, __LINE__)

#define vevent2FocusLoseEventClassHandledAssert(c, h, d) \
        _vevent2FocusLoseEventClassHandledAssert(c, h, d, vdebugTAG, \
                                                 __FILE__, __LINE__)

#define vevent2FocusLoseEventHandledAssert(e, h, d) \
        _vevent2FocusLoseEventHandledAssert(e, h, d, vdebugTAG, \
                                            __FILE__, __LINE__)

#define vevent2KeyEventClassHandledAssert(c, h, d) \
        _vevent2KeyEventClassHandledAssert(c, h, d, vdebugTAG, \
                                           __FILE__, __LINE__)

#define vevent2KeyEventHandledAssert(e, h, d) \
        _vevent2KeyEventHandledAssert(e, h, d, vdebugTAG, \
                                      __FILE__, __LINE__)

#define vevent2KeyDownEventClassHandledAssert(c, h, d) \
        _vevent2KeyDownEventClassHandledAssert(c, h, d, vdebugTAG, \
                                               __FILE__, __LINE__)

#define vevent2KeyDownEventHandledAssert(e, h, d) \
        _vevent2KeyDownEventHandledAssert(e, h, d, vdebugTAG, \
                                          __FILE__, __LINE__)

#define vevent2KeyUpEventClassHandledAssert(c, h, d) \
        _vevent2KeyUpEventClassHandledAssert(c, h, d, vdebugTAG, \
                                             __FILE__, __LINE__)

#define vevent2KeyUpEventHandledAssert(e, h, d) \
        _vevent2KeyUpEventHandledAssert(e, h, d, vdebugTAG, \
                                        __FILE__, __LINE__)

#define vevent2PointerEventClassHandledAssert(c, h, d) \
        _vevent2PointerEventClassHandledAssert(c, h, d, vdebugTAG, \
                                               __FILE__, __LINE__)

#define vevent2PointerEventHandledAssert(e, h, d) \
        _vevent2PointerEventHandledAssert(e, h, d, vdebugTAG, \
                                          __FILE__, __LINE__)

#define vevent2ButtonEventClassHandledAssert(c, h, d) \
        _vevent2ButtonEventClassHandledAssert(c, h, d, vdebugTAG, \
                                              __FILE__, __LINE__)

#define vevent2ButtonEventHandledAssert(e, h, d) \
        _vevent2ButtonEventHandledAssert(e, h, d, vdebugTAG, \
                                         __FILE__, __LINE__)

#define vevent2ButtonDownEventClassHandledAssert(c, h, d) \
        _vevent2ButtonDownEventClassHandledAssert(c, h, d, vdebugTAG, \
                                                  __FILE__, __LINE__)

#define vevent2ButtonDownEventHandledAssert(e, h, d) \
        _vevent2ButtonDownEventHandledAssert(e, h, d, vdebugTAG, \
                                             __FILE__, __LINE__)

#define vevent2ButtonUpEventClassHandledAssert(c, h, d) \
        _vevent2ButtonUpEventClassHandledAssert(c, h, d, vdebugTAG, \
                                                __FILE__, __LINE__)

#define vevent2ButtonUpEventHandledAssert(e, h, d) \
        _vevent2ButtonUpEventHandledAssert(e, h, d, vdebugTAG, \
                                           __FILE__, __LINE__)

#define vevent2PointerEnterEventClassHandledAssert(c, h, d) \
        _vevent2PointerEnterEventClassHandledAssert(c, h, d, vdebugTAG, \
                                                    __FILE__, __LINE__)

#define vevent2PointerEnterEventHandledAssert(e, h, d) \
        _vevent2PointerEnterEventHandledAssert(e, h, d, vdebugTAG, \
                                               __FILE__, __LINE__)

#define vevent2PointerLeaveEventClassHandledAssert(c, h, d) \
        _vevent2PointerLeaveEventClassHandledAssert(c, h, d, vdebugTAG, \
                                                    __FILE__, __LINE__)

#define vevent2PointerLeaveEventHandledAssert(e, h, d) \
        _vevent2PointerLeaveEventHandledAssert(e, h, d, vdebugTAG, \
                                               __FILE__, __LINE__)

#define vevent2MotionEventClassHandledAssert(c, h, d) \
        _vevent2MotionEventClassHandledAssert(c, h, d, vdebugTAG, \
                                              __FILE__, __LINE__)

#define vevent2MotionEventHandledAssert(e, h, d) \
        _vevent2MotionEventHandledAssert(e, h, d, vdebugTAG, \
                                         __FILE__, __LINE__)

#define vevent2WindowStateEventClassHandledAssert(c, h, d) \
        _vevent2WindowStateEventClassHandledAssert(c, h, d, vdebugTAG, \
                                                   __FILE__, __LINE__)

#define vevent2WindowStateEventHandledAssert(e, h, d) \
        _vevent2WindowStateEventHandledAssert(e, h, d, vdebugTAG, \
                                              __FILE__, __LINE__)

#define vevent2WindowUpdateEventClassHandledAssert(c, h, d) \
        _vevent2WindowUpdateEventClassHandledAssert(c, h, d, vdebugTAG, \
                                                    __FILE__, __LINE__)

#define vevent2WindowUpdateEventHandledAssert(e, h, d) \
        _vevent2WindowUpdateEventHandledAssert(e, h, d, vdebugTAG, \
                                               __FILE__, __LINE__)

#define vevent2HandlerClassHandledAssert(c, h, d) \
        _vevent2HandlerClassHandledAssert(c, h, d, vdebugTAG, \
                                          __FILE__, __LINE__)

#define vevent2HandlerHandledAssert(eh, h, d) \
        _vevent2HandlerHandledAssert(eh, h, d, vdebugTAG, __FILE__, __LINE__)

#define vevent2LoopClassHandledAssert(l, h, d) \
        _vevent2LoopClassHandledAssert(l, h, d, vdebugTAG, __FILE__, __LINE__)

#define vevent2LoopHandledAssert(l, h, d) \
        _vevent2LoopHandledAssert(l, h, d, vdebugTAG, __FILE__, __LINE__)

#define vevent2DriverClassHandledAssert(q, h, d) \
        _vevent2DriverClassHandledAssert(q, h, d, vdebugTAG, __FILE__, __LINE__)

#define vevent2DriverHandledAssert(q, h, d) \
        _vevent2DriverHandledAssert(q, h, d, vdebugTAG, __FILE__, __LINE__)

#define vevent2PreBlockerClassHandledAssert(c, h, d) \
        _vevent2PreBlockerClassHandledAssert(c, h, d, vdebugTAG, \
                                             __FILE__, __LINE__)

#define vevent2PreBlockerHandledAssert(eh, h, d) \
        _vevent2PreBlockerHandledAssert(eh, h, d, vdebugTAG, \
                                        __FILE__, __LINE__)

#define vevent2QuitterClassHandledAssert(c, h, d) \
        _vevent2QuitterClassHandledAssert(c, h, d, vdebugTAG, \
                                         __FILE__, __LINE__)

#define vevent2QuitterHandledAssert(eh, h, d) \
        _vevent2QuitterHandledAssert(eh, h, d, vdebugTAG, __FILE__, __LINE__)

#define vevent2SystemEventHandlerClassHandledAssert(c, h, d) \
        _vevent2SystemEventHandlerClassHandledAssert(c, h, d, vdebugTAG, \
                                                     __FILE__, __LINE__)

#define vevent2SystemEventHandlerHandledAssert(seh, h, d) \
        _vevent2SystemEventHandlerHandledAssert(seh, h, d, vdebugTAG, \
                                                __FILE__, __LINE__)

#if (vdebugDEBUG)

#define vevent2ClassAssert(c) \
        vevent2ClassHandledAssert((c), NULL, NULL)

#define vevent2Assert(e) \
        vevent2HandledAssert((e), NULL, NULL)

#define vevent2WindowEventClassAssert(c) \
        vevent2WindowEventClassHandledAssert((c), NULL, NULL)

#define vevent2WindowEventAssert(e) \
        vevent2WindowEventHandledAssert((e), NULL, NULL)

#define vevent2WindowConfigureEventClassAssert(c) \
        vevent2WindowConfigureEventClassHandledAssert((c), NULL, NULL)

#define vevent2WindowConfigureEventAssert(e) \
        vevent2WindowConfigureEventHandledAssert((e), NULL, NULL)

#define vevent2FocusEventClassAssert(c) \
        vevent2FocusEventClassHandledAssert((c), NULL, NULL)

#define vevent2FocusEventAssert(e) \
        vevent2FocusEventHandledAssert((e), NULL, NULL)

#define vevent2FocusAcquireEventClassAssert(c) \
        vevent2FocusAcquireEventClassHandledAssert((c), NULL, NULL)

#define vevent2FocusAcquireEventAssert(e) \
        vevent2FocusAcquireEventHandledAssert((e), NULL, NULL)

#define vevent2FocusLoseEventClassAssert(c) \
        vevent2FocusLoseEventClassHandledAssert((c), NULL, NULL)

#define vevent2FocusLoseEventAssert(e) \
        vevent2FocusLoseEventHandledAssert((e), NULL, NULL)

#define vevent2KeyEventClassAssert(c) \
        vevent2KeyEventClassHandledAssert((c), NULL, NULL)

#define vevent2KeyEventAssert(e) \
        vevent2KeyEventHandledAssert((e), NULL, NULL)

#define vevent2KeyDownEventClassAssert(c) \
        vevent2KeyDownEventClassHandledAssert((c), NULL, NULL)

#define vevent2KeyDownEventAssert(e) \
        vevent2KeyDownEventHandledAssert((e), NULL, NULL)

#define vevent2KeyUpEventClassAssert(c) \
        vevent2KeyUpEventClassHandledAssert((c), NULL, NULL)

#define vevent2KeyUpEventAssert(e) \
        vevent2KeyUpEventHandledAssert((e), NULL, NULL)

#define vevent2PointerEventClassAssert(c) \
        vevent2PointerEventClassHandledAssert((c), NULL, NULL)

#define vevent2PointerEventAssert(e) \
        vevent2PointerEventHandledAssert((e), NULL, NULL)

#define vevent2ButtonEventClassAssert(c) \
        vevent2ButtonEventClassHandledAssert((c), NULL, NULL)

#define vevent2ButtonEventAssert(e) \
        vevent2ButtonEventHandledAssert((e), NULL, NULL)

#define vevent2ButtonDownEventClassAssert(c) \
        vevent2ButtonDownEventClassHandledAssert((c), NULL, NULL)

#define vevent2ButtonDownEventAssert(e) \
        vevent2ButtonDownEventHandledAssert((e), NULL, NULL)

#define vevent2ButtonUpEventClassAssert(c) \
        vevent2ButtonUpEventClassHandledAssert((c), NULL, NULL)

#define vevent2ButtonUpEventAssert(e) \
        vevent2ButtonUpEventHandledAssert((e), NULL, NULL)

#define vevent2PointerEnterEventClassAssert(c) \
        vevent2PointerEnterEventClassHandledAssert((c), NULL, NULL)

#define vevent2PointerEnterEventAssert(e) \
        vevent2PointerEnterEventHandledAssert((e), NULL, NULL)

#define vevent2PointerLeaveEventClassAssert(c) \
        vevent2PointerLeaveEventClassHandledAssert((c), NULL, NULL)

#define vevent2PointerLeaveEventAssert(e) \
        vevent2PointerLeaveEventHandledAssert((e), NULL, NULL)

#define vevent2MotionEventClassAssert(c) \
        vevent2MotionEventClassHandledAssert((c), NULL, NULL)

#define vevent2MotionEventAssert(e) \
        vevent2MotionEventHandledAssert((e), NULL, NULL)

#define vevent2WindowStateEventClassAssert(c) \
        vevent2WindowStateEventClassHandledAssert((c), NULL, NULL)

#define vevent2WindowStateEventAssert(e) \
        vevent2WindowStateEventHandledAssert((e), NULL, NULL)

#define vevent2WindowUpdateEventClassAssert(c) \
        vevent2WindowUpdateEventClassHandledAssert((c), NULL, NULL)

#define vevent2WindowUpdateEventAssert(e) \
        vevent2WindowUpdateEventHandledAssert((e), NULL, NULL)

#define vevent2HandlerClassAssert(h) \
        vevent2HandlerClassHandledAssert((h), NULL, NULL)

#define vevent2HandlerAssert(h) \
        vevent2HandlerHandledAssert((h), NULL, NULL)

#define vevent2LoopClassAssert(l) \
        vevent2LoopClassHandledAssert((l), NULL, NULL)

#define vevent2LoopAssert(l) \
        vevent2LoopHandledAssert((l), NULL, NULL)

#define vevent2DriverClassAssert(q) \
        vevent2DriverClassHandledAssert((q), NULL, NULL)

#define vevent2DriverAssert(q) \
        vevent2DriverHandledAssert((q), NULL, NULL)

#define vevent2PreBlockerClassAssert(h) \
        vevent2PreBlockerClassHandledAssert((h), NULL, NULL)

#define vevent2PreBlockerAssert(h) \
        vevent2PreBlockerHandledAssert((h), NULL, NULL)

#define vevent2QuitterClassAssert(h) \
        vevent2QuitterClassHandledAssert((h), NULL, NULL)

#define vevent2QuitterAssert(h) \
        vevent2QuitterHandledAssert((h), NULL, NULL)

#define vevent2SystemEventHandlerClassAssert(h) \
        vevent2SystemEventHandlerClassHandledAssert((h), NULL, NULL)

#define vevent2SystemEventHandlerAssert(h) \
        vevent2SystemEventHandlerHandledAssert((h), NULL, NULL)

#else /* #if (vdebugDEBUG) */

#define vevent2ClassAssert(e) \
        ((void)0)

#define vevent2Assert(e) \
        ((void)0)

#define vevent2WindowEventClassAssert(e) \
        ((void)0)

#define vevent2WindowEventAssert(e) \
        ((void)0)

#define vevent2WindowConfigureEventClassAssert(e) \
        ((void)0)

#define vevent2WindowConfigureEventAssert(e) \
        ((void)0)

#define vevent2FocusEventClassAssert(e) \
        ((void)0)

#define vevent2FocusEventAssert(e) \
        ((void)0)

#define vevent2FocusAcquireEventClassAssert(e) \
        ((void)0)

#define vevent2FocusAcquireEventAssert(e) \
        ((void)0)

#define vevent2FocusLoseEventClassAssert(e) \
        ((void)0)

#define vevent2FocusLoseEventAssert(e) \
        ((void)0)

#define vevent2KeyEventClassAssert(e) \
        ((void)0)

#define vevent2KeyEventAssert(e) \
        ((void)0)

#define vevent2KeyDownEventClassAssert(e) \
        ((void)0)

#define vevent2KeyDownEventAssert(e) \
        ((void)0)

#define vevent2KeyUpEventClassAssert(e) \
        ((void)0)

#define vevent2KeyUpEventAssert(e) \
        ((void)0)

#define vevent2PointerEventClassAssert(e) \
        ((void)0)

#define vevent2PointerEventAssert(e) \
        ((void)0)

#define vevent2ButtonEventClassAssert(e) \
        ((void)0)

#define vevent2ButtonEventAssert(e) \
        ((void)0)

#define vevent2ButtonDownEventClassAssert(e) \
        ((void)0)

#define vevent2ButtonDownEventAssert(e) \
        ((void)0)

#define vevent2ButtonUpEventClassAssert(e) \
        ((void)0)

#define vevent2ButtonUpEventAssert(e) \
        ((void)0)

#define vevent2PointerEnterEventClassAssert(e) \
        ((void)0)

#define vevent2PointerEnterEventAssert(e) \
        ((void)0)

#define vevent2PointerLeaveEventClassAssert(e) \
        ((void)0)

#define vevent2PointerLeaveEventAssert(e) \
        ((void)0)

#define vevent2MotionEventClassAssert(e) \
        ((void)0)

#define vevent2MotionEventAssert(e) \
        ((void)0)

#define vevent2WindowStateEventClassAssert(e) \
        ((void)0)

#define vevent2WindowStateEventAssert(e) \
        ((void)0)

#define vevent2WindowUpdateEventClassAssert(e) \
        ((void)0)

#define vevent2WindowUpdateEventAssert(e) \
        ((void)0)

#define vevent2HandlerClassAssert(h) \
        ((void)0)

#define vevent2HandlerAssert(h) \
        ((void)0)

#define vevent2LoopClassAssert(l) \
        ((void)0)

#define vevent2LoopAssert(l) \
        ((void)0)

#define vevent2DriverClassAssert(q) \
        ((void)0)

#define vevent2DriverAssert(q) \
        ((void)0)

#define vevent2PreBlockerClassAssert(h) \
        ((void)0)

#define vevent2PreBlockerAssert(h) \
        ((void)0)

#define vevent2QuitterClassAssert(h) \
        ((void)0)

#define vevent2QuitterAssert(h) \
        ((void)0)

#define vevent2SystemEventHandlerClassAssert(h) \
        ((void)0)

#define vevent2SystemEventHandlerAssert(h) \
        ((void)0)

#endif

/* Up-casts */

#define vevent2AsLoadable(e) \
        vportBASE_OBJECT(e, super)

#define vevent2AsInstance(e) \
        vloadableGetInstance(vevent2AsLoadable(e))

#define vevent2ClassAsLoadableClass(c) \
        (vevent2ClassAssert(c), (vloadableClass *)(c))

#define vevent2ClassAsInstanceClass(c) \
        (vevent2ClassAssert(c), (vinstanceClass *)(c))

#define vevent2WindowEventAsEvent(e) \
        vportBASE_OBJECT(e, super)

#define vevent2WindowEventAsLoadable(e) \
        vevent2AsLoadable(vevent2WindowEventAsEvent(e))

#define vevent2WindowEventAsInstance(e) \
        vloadableGetInstance(vevent2WindowEventAsLoadable(e))

#define vevent2WindowEventClassAsEventClass(c) \
        (vevent2WindowEventClassAssert(c), (vevent2Class *)(c))

#define vevent2WindowEventClassAsLoadableClass(c) \
        (vevent2WindowEventClassAssert(c), (vloadableClass *)(c))

#define vevent2WindowEventClassAsInstanceClass(c) \
        (vevent2WindowEventClassAssert(c), (vinstanceClass *)(c))

#define vevent2WindowConfigureEventAsWindowEvent(e) \
        vportBASE_OBJECT(e, super)

#define vevent2WindowConfigureEventAsEvent(e) \
        vevent2WindowEventAsEvent(vevent2WindowConfigureEventAsWindowEvent(e))

#define vevent2WindowConfigureEventAsLoadable(e) \
        vevent2AsLoadable(vevent2WindowConfigureEventAsEvent(e))

#define vevent2WindowConfigureEventAsInstance(e) \
        vloadableGetInstance(vevent2WindowConfigureEventAsLoadable(e))

#define vevent2WindowConfigureEventClassAsWindowEventClass(c) \
        (vevent2WindowConfigureEventClassAssert(c), \
         (vevent2WindowEventClass *)(c))

#define vevent2WindowConfigureEventClassAsLoadableClass(c) \
        (vevent2WindowConfigureEventClassAssert(c), (vloadableClass *)(c))

#define vevent2WindowConfigureEventClassAsInstanceClass(c) \
        (vevent2WindowConfigureEventClassAssert(c), (vinstanceClass *)(c))

#define vevent2FocusEventAsWindowEvent(e) \
        vportBASE_OBJECT(e, super)

#define vevent2FocusEventAsEvent(e) \
        vevent2WindowEventAsEvent(vevent2FocusEventAsWindowEvent(e))

#define vevent2FocusEventAsLoadable(e) \
        vevent2AsLoadable(vevent2FocusEventAsEvent(e))

#define vevent2FocusEventAsInstance(e) \
        vloadableGetInstance(vevent2FocusEventAsLoadable(e))

#define vevent2FocusEventClassAsWindowEventClass(c) \
        (vevent2FocusEventClassAssert(c),(vevent2WindowEventClass *)(c))

#define vevent2FocusEventClassAsLoadableClass(c) \
        (vevent2FocusEventClassAssert(c), (vloadableClass *)(c))

#define vevent2FocusEventClassAsInstanceClass(c) \
        (vevent2FocusEventClassAssert(c), (vinstanceClass *)(c))

#define vevent2FocusLoseEventAsFocusEvent(e) \
        vportBASE_OBJECT(e, super)

#define vevent2FocusLoseEventAsWindowEvent(e) \
        vevent2FocusEventAsWindowEvent(vevent2FocusLoseEventAsFocusEvent(e))

#define vevent2FocusLoseEventAsEvent(e) \
        vevent2WindowEventAsEvent(vevent2FocusLoseEventAsWindowEvent(e))

#define vevent2FocusLoseEventAsLoadable(e) \
        vevent2AsLoadable(vevent2FocusLoseEventAsEvent(e))

#define vevent2FocusLoseEventAsInstance(e) \
        vloadableGetInstance(vevent2FocusLoseEventAsLoadable(e))

#define vevent2FocusLoseEventClassAsFocusEventClass(c) \
        (vevent2FocusLoseEventClassAssert(c), (vevent2FocusEventClass *)(c))

#define vevent2FocusLoseEventClassAsWindowEventClass(c) \
        (vevent2FocusLoseEventClassAssert(c), (vevent2WindowEventClass *)(c))

#define vevent2FocusLoseEventClassAsLoadableClass(c) \
        (vevent2FocusLoseEventClassAssert(c), (vloadableClass *)(c))

#define vevent2FocusLoseEventClassAsInstanceClass(c) \
        (vevent2FocusLoseEventClassAssert(c), (vinstanceClass *)(c))

#define vevent2PointerEventAsWindowEvent(e) \
        vportBASE_OBJECT(e, super)

#define vevent2PointerEventAsEvent(e) \
        vevent2WindowEventAsEvent(vevent2PointerEventAsWindowEvent(e))

#define vevent2PointerEventAsLoadable(e) \
        vevent2AsLoadable(vevent2PointerEventAsEvent(e))

#define vevent2PointerEventAsInstance(e) \
        vloadableGetInstance(vevent2PointerEventAsLoadable(e))

#define vevent2PointerEventClassAsWindowEventClass(c) \
        (vevent2PointerEventClassAssert(c), (vevent2WindowEventClass *)(c))

#define vevent2PointerEventClassAsLoadableClass(c) \
        (vevent2PointerEventClassAssert(c), (vloadableClass *)(c))

#define vevent2PointerEventClassAsInstanceClass(c) \
        (vevent2PointerEventClassAssert(c), (vinstanceClass *)(c))

#define vevent2ButtonEventAsPointerEvent(e) \
        vportBASE_OBJECT(e, super)

#define vevent2ButtonEventAsWindowEvent(e) \
        vevent2PointerEventAsWindowEvent(vevent2ButtonEventAsPointerEvent(e))

#define vevent2ButtonEventAsEvent(e) \
        vevent2WindowEventAsEvent(vevent2ButtonEventAsWindowEvent(e))

#define vevent2ButtonEventAsLoadable(e) \
        vevent2AsLoadable(vevent2ButtonEventAsEvent(e))

#define vevent2ButtonEventAsInstance(e) \
        vloadableGetInstance(vevent2ButtonEventAsLoadable(e))

#define vevent2ButtonEventClassAsPointerEventClass(c) \
        (vevent2ButtonEventClassAssert(c), (vevent2PointerEventClass *)(c))

#define vevent2ButtonEventClassAsLoadableClass(c) \
        (vevent2ButtonEventClassAssert(c), (vloadableClass *)(c))

#define vevent2ButtonEventClassAsInstanceClass(c) \
        (vevent2ButtonEventClassAssert(c), (vinstanceClass *)(c))

#define vevent2ButtonDownEventAsButtonEvent(e) \
        vportBASE_OBJECT(e, super)

#define vevent2ButtonDownEventAsWindowEvent(e) \
        vevent2ButtonEventAsWindowEvent(vevent2ButtonDownEventAsButtonEvent(e))

#define vevent2ButtonDownEventAsEvent(e) \
        vevent2WindowEventAsEvent(vevent2ButtonDownEventAsWindowEvent(e))

#define vevent2ButtonDownEventAsLoadable(e) \
        vevent2AsLoadable(vevent2ButtonDownEventAsEvent(e))

#define vevent2ButtonDownEventAsInstance(e) \
        vloadableGetInstance(vevent2ButtonDownEventAsLoadable(e))

#define vevent2ButtonDownEventClassAsButtonEventClass(c) \
        (vevent2ButtonDownEventClassAssert(c), (vevent2ButtonEventClass *)(c))

#define vevent2ButtonDownEventClassAsLoadableClass(c) \
        (vevent2ButtonDownEventClassAssert(c), (vloadableClass *)(c))

#define vevent2ButtonDownEventClassAsInstanceClass(c) \
        (vevent2ButtonDownEventClassAssert(c), (vinstanceClass *)(c))

#define vevent2ButtonUpEventAsButtonEvent(e) \
        vportBASE_OBJECT(e, super)

#define vevent2ButtonUpEventAsWindowEvent(e) \
        vevent2ButtonEventAsWindowEvent(vevent2ButtonUpEventAsButtonEvent(e))

#define vevent2ButtonUpEventAsEvent(e) \
        vevent2WindowEventAsEvent(vevent2ButtonUpEventAsWindowEvent(e))

#define vevent2ButtonUpEventAsLoadable(e) \
        vevent2AsLoadable(vevent2ButtonUpEventAsEvent(e))

#define vevent2ButtonUpEventAsInstance(e) \
        vloadableGetInstance(vevent2ButtonUpEventAsLoadable(e))

#define vevent2ButtonUpEventClassAsButtonEventClass(c) \
        (vevent2ButtonUpEventClassAssert(c), (vevent2ButtonEventClass *)(c))

#define vevent2ButtonUpEventClassAsLoadableClass(c) \
        (vevent2ButtonUpEventClassAssert(c), (vloadableClass *)(c))

#define vevent2ButtonUpEventClassAsInstanceClass(c) \
        (vevent2ButtonUpEventClassAssert(c), (vinstanceClass *)(c))

#define vevent2PointerEnterEventAsPointerEvent(e) \
        vportBASE_OBJECT(e, super)

#define vevent2PointerEnterEventAsWindowEvent(e) \
        vevent2PointerEventAsWindowEvent \
            (vevent2PointerEnterEventAsPointerEvent(e))

#define vevent2PointerEnterEventAsEvent(e) \
        vevent2WindowEventAsEvent(vevent2PointerEnterEventAsWindowEvent(e))

#define vevent2PointerEnterEventAsLoadable(e) \
        vevent2AsLoadable(vevent2PointerEnterEventAsEvent(e))

#define vevent2PointerEnterEventAsInstance(e) \
        vloadableGetInstance(vevent2PointerEnterEventAsLoadable(e))

#define vevent2PointerEnterEventClassAsPointerEventClass(c) \
        (vevent2PointerEnterEventClassAssert(c),(vevent2PointerEventClass*)(c))

#define vevent2PointerEnterEventClassAsLoadableClass(c) \
        (vevent2PointerEnterEventClassAssert(c), (vloadableClass *)(c))

#define vevent2PointerEnterEventClassAsInstanceClass(c) \
        (vevent2PointerEnterEventClassAssert(c), (vinstanceClass *)(c))

#define vevent2KeyEventAsPointerEvent(e) \
        vportBASE_OBJECT(e, super)

#define vevent2KeyEventAsWindowEvent(e) \
        vevent2PointerEventAsWindowEvent(vevent2KeyEventAsPointerEvent(e))

#define vevent2KeyEventAsLoadable(e) \
        vevent2WindowEventAsLoadable(vevent2KeyEventAsWindowEvent(e))

#define vevent2KeyEventAsInstance(e) \
        vloadableGetInstance(vevent2KeyEventAsLoadable(e))

#define vevent2KeyEventClassAsPointerEventClass(c) \
        (vevent2KeyEventClassAssert(c), (vevent2PointerEventClass *)(c))

#define vevent2KeyEventClassAsWindowEventClass(c) \
        (vevent2KeyEventClassAssert(c), (vevent2WindowEventClass *)(c))

#define vevent2KeyEventClassAsLoadableClass(c) \
        (vevent2KeyEventClassAssert(c), (vloadableClass *)(c))

#define vevent2KeyEventClassAsInstanceClass(c) \
        (vevent2KeyEventClassAssert(c), (vinstanceClass *)(c))

#define vevent2KeyDownEventAsKeyEvent(e) \
        vportBASE_OBJECT(e, super)

#define vevent2KeyDownEventAsWindowEvent(e) \
        vevent2KeyEventAsWindowEvent(vevent2KeyDownEventAsKeyEvent(e))

#define vevent2KeyDownEventAsEvent(e) \
        vevent2WindowEventAsEvent(vevent2KeyDownEventAsWindowEvent(e))

#define vevent2KeyDownEventAsLoadable(e) \
        vevent2AsLoadable(vevent2KeyDownEventAsEvent(e))

#define vevent2KeyDownEventAsInstance(e) \
        vloadableGetInstance(vevent2KeyDownEventAsLoadable(e))

#define vevent2KeyDownEventClassAsKeyEventClass(c) \
        (vevent2KeyDownEventClassAssert(c), (vevent2KeyEventClass *)(c))

#define vevent2KeyDownEventClassAsLoadableClass(c) \
        (vevent2KeyDownEventClassAssert(c), (vloadableClass *)(c))

#define vevent2KeyDownEventClassAsInstanceClass(c) \
        (vevent2KeyDownEventClassAssert(c), (vinstanceClass *)(c))

#define vevent2KeyUpEventAsKeyEvent(e) \
        vportBASE_OBJECT(e, super)

#define vevent2KeyUpEventAsWindowEvent(e) \
        vevent2KeyEventAsWindowEvent(vevent2KeyUpEventAsKeyEvent(e))

#define vevent2KeyUpEventAsEvent(e) \
        vevent2WindowEventAsEvent(vevent2KeyUpEventAsWindowEvent(e))

#define vevent2KeyUpEventAsLoadable(e) \
        vevent2AsLoadable(vevent2KeyUpEventAsEvent(e))

#define vevent2KeyUpEventAsInstance(e) \
        vloadableGetInstance(vevent2KeyUpEventAsLoadable(e))

#define vevent2KeyUpEventClassAsKeyEventClass(c) \
        (vevent2KeyUpEventClassAssert(c), (vevent2KeyEventClass *)(c))

#define vevent2KeyUpEventClassAsLoadableClass(c) \
        (vevent2KeyUpEventClassAssert(c), (vloadableClass *)(c))

#define vevent2KeyUpEventClassAsInstanceClass(c) \
        (vevent2KeyUpEventClassAssert(c), (vinstanceClass *)(c))

#define vevent2PointerLeaveEventAsPointerEvent(e) \
        vportBASE_OBJECT(e, super)

#define vevent2PointerLeaveEventAsWindowEvent(e) \
        vevent2PointerEventAsWindowEvent \
            (vevent2PointerLeaveEventAsPointerEvent(e))

#define vevent2PointerLeaveEventAsEvent(e) \
        vevent2WindowEventAsEvent(vevent2PointerLeaveEventAsWindowEvent(e))

#define vevent2PointerLeaveEventAsLoadable(e) \
        vevent2AsLoadable(vevent2PointerLeaveEventAsEvent(e))

#define vevent2PointerLeaveEventAsInstance(e) \
        vloadableGetInstance(vevent2PointerLeaveEventAsLoadable(e))

#define vevent2PointerLeaveEventClassAsPointerEventClass(c) \
        (vevent2PointerLeaveEventClassAssert(c),(vevent2PointerEventClass*)(c))

#define vevent2PointerLeaveEventClassAsLoadableClass(c) \
        (vevent2PointerLeaveEventClassAssert(c), (vloadableClass *)(c))

#define vevent2PointerLeaveEventClassAsInstanceClass(c) \
        (vevent2PointerLeaveEventClassAssert(c), (vinstanceClass *)(c))

#define vevent2MotionEventAsPointerEvent(e) \
        vportBASE_OBJECT(e, super)

#define vevent2MotionEventAsWindowEvent(e) \
        vevent2PointerEventAsWindowEvent \
            (vevent2MotionEventAsPointerEvent(e))

#define vevent2MotionEventAsEvent(e) \
        vevent2WindowEventAsEvent(vevent2MotionEventAsWindowEvent(e))

#define vevent2MotionEventAsLoadable(e) \
        vevent2AsLoadable(vevent2MotionEventAsEvent(e))

#define vevent2MotionEventAsInstance(e) \
        vloadableGetInstance(vevent2MotionEventAsLoadable(e))

#define vevent2MotionEventClassAsPointerEventClass(c) \
        (vevent2MotionEventClassAssert(c),(vevent2PointerEventClass*)(c))

#define vevent2MotionEventClassAsLoadableClass(c) \
        (vevent2MotionEventClassAssert(c), (vloadableClass *)(c))

#define vevent2MotionEventClassAsInstanceClass(c) \
        (vevent2MotionEventClassAssert(c), (vinstanceClass *)(c))

#define vevent2WindowStateEventAsWindowEvent(e) \
        vportBASE_OBJECT(e, super)

#define vevent2WindowStateEventAsEvent(e) \
        vevent2WindowEventAsEvent(vevent2WindowStateEventAsWindowEvent(e))

#define vevent2WindowStateEventAsLoadable(e) \
        vevent2AsLoadable(vevent2WindowStateEventAsEvent(e))

#define vevent2WindowStateEventAsInstance(e) \
        vloadableGetInstance(vevent2WindowStateEventAsLoadable(e))

#define vevent2WindowStateEventClassAsWindowEventClass(c) \
        (vevent2WindowStateEventClassAssert(c), (vevent2WindowEventClass *)(c))

#define vevent2WindowStateEventClassAsLoadableClass(c) \
        (vevent2WindowStateEventClassAssert(c), (vloadableClass *)(c))

#define vevent2WindowStateEventClassAsInstanceClass(c) \
        (vevent2WindowStateEventClassAssert(c), (vinstanceClass *)(c))

#define vevent2WindowUpdateEventAsWindowEvent(e) \
        vportBASE_OBJECT(e, super)

#define vevent2WindowUpdateEventAsEvent(e) \
        vevent2WindowEventAsEvent(vevent2WindowUpdateEventAsWindowEvent(e))

#define vevent2WindowUpdateEventAsLoadable(e) \
        vevent2AsLoadable(vevent2WindowUpdateEventAsEvent(e))

#define vevent2WindowUpdateEventAsInstance(e) \
        vloadableGetInstance(vevent2WindowUpdateEventAsLoadable(e))

#define vevent2WindowUpdateEventClassAsWindowEventClass(c) \
        (vevent2WindowUpdateEventClassAssert(c), (vevent2WindowEventClass*)(c))

#define vevent2WindowUpdateEventClassAsLoadableClass(c) \
        (vevent2WindowUpdateEventClassAssert(c), (vloadableClass *)(c))

#define vevent2WindowUpdateEventClassAsInstanceClass(c) \
        (vevent2WindowUpdateEventClassAssert(c), (vinstanceClass *)(c))

#define vevent2HandlerAsLoadable(h) \
        vportBASE_OBJECT(h, super)

#define vevent2HandlerAsInstance(h) \
        vloadableGetInstance(vevent2HandlerAsLoadable(h))

#define vevent2HandlerClassAsLoadableClass(c) \
        (vevent2HandlerClassAssert(c), (vloadableClass *)(c))

#define vevent2LoopAsHandler(l) \
        vportBASE_OBJECT(l, super)

#define vevent2LoopClassAsHandlerClass(c) \
        (vevent2LoopClassAssert(c), (vevent2HandlerClass *)(c))

#define vevent2DriverAsInstance(d) \
        vportBASE_OBJECT(d, super)

#define vevent2DriverClassAsInstanceClass(c) \
        (vevent2DriverClassAssert(c), (vinstanceClass *)(c))

#define vevent2PreBlockerAsInstance(p) \
        vportBASE_OBJECT(p, super)

#define vevent2PreBlockerClassAsInstanceClass(c) \
        (vevent2PreBlockerClassAssert(c), (vinstanceClass *)(c))

#define vevent2QuitterAsInstance(q) \
        vportBASE_OBJECT(q, super)

#define vevent2QuitterClassAsInstanceClass(c) \
        (vevent2QuitterClassAssert(c), (vinstanceClass *)(c))

#define vevent2SystemEventHandlerAsInstance(h) \
        vportBASE_OBJECT(h, super)

#define vevent2SystemEventHandlerClassAsInstanceClass(c) \
        (vevent2SystemEventHandlerClassAssert(c), (vinstanceClass *)(c))

/* class vevent2 */

#define vevent2GetClass(e) \
        ((vevent2Class *) vloadableGetClass(vevent2AsLoadable(e)))

#define vevent2CreateOfClass(c) \
        ((vevent2 *) vinstanceCreateOfClass(vevent2ClassAsInstanceClass(c)))

#define vevent2Create() \
        vevent2CreateOfClass(vevent2ClassGetDefault())

#define vevent2Share(e) \
        (vevent2Assert(e), (e)->shareCount++)

#define vevent2Release(e) \
        (vevent2Assert(e), (e)->shareCount > 0 ? --(e)->shareCount : \
         (vloadableDestroy(vevent2AsLoadable(e)), 0))

#define vevent2IsShared(e) \
        (vevent2Assert(e), (e)->shareCount > 0)

#define vevent2Dump(e, fp) \
        vloadableDump(vevent2AsLoadable(e), fp)

#define vevent2SetTime(e, t) \
        (vevent2Assert(e), vtimestampAssert(t), (e)->time = (t))

#define vevent2GetTime(e) \
        (vevent2Assert(e), (e)->time)

#define vevent2SetType(e, t) \
        (vevent2Assert(e), (e)->type = (t))

#define vevent2GetType(e) \
        (vevent2Assert(e), (e)->type)

#define vevent2SetBinding(e, b) \
        (vevent2Assert(e), (e)->pBinding = (b))

#define vevent2GetBinding(e) \
        (vevent2Assert(e), (e)->pBinding)

#define vevent2SetData(e, d) \
        (vevent2Assert(e), (e)->pData = (void *) (d))

#define vevent2GetData(e) \
        (vevent2Assert(e), (e)->pData)

#define vevent2SetPriority(e, p) \
        (vevent2Assert(e), (e)->priority = (p))

#define vevent2GetPriority(e) \
        (vevent2Assert(e), (e)->priority)

#define vevent2GetHandler(e) \
        (vevent2Assert(e), (e)->pHandler)

#define vevent2GetLoop(e) \
        (vevent2Assert(e), (e)->pLoop)

#define vevent2Post(e) \
        vevent2HandlerHandleEvent(vevent2LoopAsHandler\
                                  (vevent2LoopGetCurrent()), (e))

#define vevent2PostAtInterrupt(e) \
        ((e)->triggered = (e)->pLoop->scanPreQueued = vTRUE, \
         vevent2LoopUnblock((e)->pLoop))

/* class vevent2WindowEvent */

#define vevent2WindowEventGetClass(e) \
        ((vevent2WindowEventClass *) \
         vloadableGetClass(vevent2WindowEventAsLoadable(e)))

#define vevent2WindowEventCreateOfClass(c) \
        ((vevent2WindowEvent *) \
         vinstanceCreateOfClass(vevent2WindowEventClassAsInstanceClass(c)))

#define vevent2WindowEventCreate() \
        vevent2WindowEventCreateOfClass(vevent2WindowEventClassGetDefault())

#define vevent2WindowEventSetWindow(e, w) \
        (vevent2WindowEventAssert(e), (e)->pWindow = (w))

#define vevent2WindowEventGetWindow(e) \
        (vevent2WindowEventAssert(e), (e)->pWindow)

/* class vevent2WindowConfigureEvent */

#define vevent2WindowConfigureEventGetClass(e) \
        ((vevent2WindowConfigureEventClass *) \
         vloadableGetClass(vevent2WindowConfigureEventAsLoadable(e)))

#define vevent2WindowConfigureEventCreateOfClass(c) \
        ((vevent2WindowConfigureEvent *) \
         vinstanceCreateOfClass \
         (vevent2WindowConfigureEventClassAsInstanceClass(c)))

#define vevent2WindowConfigureEventCreate() \
        vevent2WindowConfigureEventCreateOfClass \
          (vevent2WindowConfigureEventClassGetDefault())

#define vevent2WindowConfigureEventSetRect(e, r) \
        (vevent2WindowConfigureEventAssert(e), (e)->rect = *(r))

#define vevent2WindowConfigureEventGetRect(e) \
        (vevent2WindowConfigureEventAssert(e), &(e)->rect)

#define vevent2WindowConfigureEventSetAbove(e, w) \
        (vevent2WindowConfigureEventAssert(e), (e)->pAbove = (w))

#define vevent2WindowConfigureEventGetAbove(e) \
        (vevent2WindowConfigureEventAssert(e), (e)->pAbove)

/* class vevent2FocusEvent */

#define vevent2FocusEventGetClass(e) \
        ((vevent2FocusEventClass *) \
         vloadableGetClass(vevent2FocusEventAsLoadable(e)))

#define vevent2FocusEventCreateOfClass(c) \
        ((vevent2FocusEvent *) \
         vinstanceCreateOfClass \
         (vevent2FocusEventClassAsInstanceClass(c)))

#define vevent2FocusEventCreate() \
        vevent2FocusEventCreateOfClass \
          (vevent2FocusEventClassGetDefault())

/* class vevent2FocusAcquireEvent */

#define vevent2FocusAcquireEventAsFocusEvent(e) \
        vportBASE_OBJECT(e, super)

#define vevent2FocusAcquireEventAsWindowEvent(e) \
        vevent2FocusEventAsWindowEvent(vevent2FocusAcquireEventAsFocusEvent(e))

#define vevent2FocusAcquireEventAsEvent(e) \
        vevent2WindowEventAsEvent(vevent2FocusAcquireEventAsWindowEvent(e))

#define vevent2FocusAcquireEventAsLoadable(e) \
        vevent2AsLoadable(vevent2FocusAcquireEventAsEvent(e))

#define vevent2FocusAcquireEventAsInstance(e) \
        vloadableGetInstance(vevent2FocusAcquireEventAsLoadable(e))

#define vevent2FocusAcquireEventGetClass(e) \
        ((vevent2FocusAcquireEventClass *) \
         vloadableGetClass(vevent2FocusAcquireEventAsLoadable(e)))

#define vevent2FocusAcquireEventClassAsFocusEventClass(c) \
        (vevent2FocusAcquireEventClassAssert(c),(vevent2FocusEventClass *)(c))

#define vevent2FocusAcquireEventClassAsWindowEventClass(c) \
        (vevent2FocusAcquireEventClassAssert(c),(vevent2WindowEventClass *)(c))

#define vevent2FocusAcquireEventClassAsLoadableClass(c) \
        (vevent2FocusAcquireEventClassAssert(c), (vloadableClass *)(c))

#define vevent2FocusAcquireEventClassAsInstanceClass(c) \
        (vevent2FocusAcquireEventClassAssert(c), (vinstanceClass *)(c))

#define vevent2FocusAcquireEventCreateOfClass(c) \
        ((vevent2FocusAcquireEvent *) \
         vinstanceCreateOfClass \
         (vevent2FocusAcquireEventClassAsInstanceClass(c)))

#define vevent2FocusAcquireEventCreate() \
        vevent2FocusAcquireEventCreateOfClass \
          (vevent2FocusAcquireEventClassGetDefault())

/* class vevent2FocusLoseEvent */

#define vevent2FocusLoseEventGetClass(e) \
        ((vevent2FocusLoseEventClass *) \
         vloadableGetClass(vevent2FocusLoseEventAsLoadable(e)))

#define vevent2FocusLoseEventCreateOfClass(c) \
        ((vevent2FocusLoseEvent *) \
         vinstanceCreateOfClass \
         (vevent2FocusLoseEventClassAsInstanceClass(c)))

#define vevent2FocusLoseEventCreate() \
        vevent2FocusLoseEventCreateOfClass \
          (vevent2FocusLoseEventClassGetDefault())

/* class vevent2PointerEvent */

#define vevent2PointerEventGetClass(e) \
        ((vevent2PointerEventClass *) \
         vloadableGetClass(vevent2PointerEventAsLoadable(e)))

#define vevent2PointerEventCreateOfClass(c) \
        ((vevent2PointerEvent *) \
         vinstanceCreateOfClass \
         (vevent2PointerEventClassAsInstanceClass(c)))

#define vevent2PointerEventCreate() \
        vevent2PointerEventCreateOfClass \
          (vevent2PointerEventClassGetDefault())

#define vevent2PointerEventSetPoint(e, p) \
        (vevent2PointerEventAssert(e), (e)->point = *(p))

#define vevent2PointerEventGetPoint(e) \
        (vevent2PointerEventAssert(e), &(e)->point)

#define vevent2PointerEventSetX(e, _x) \
        (vevent2PointerEventAssert(e), (e)->point.x = (_x))

#define vevent2PointerEventGetX(e) \
        (vevent2PointerEventAssert(e), (e)->point.x)

#define vevent2PointerEventSetY(e, _y) \
        (vevent2PointerEventAssert(e), (e)->point.y = (_y))

#define vevent2PointerEventGetY(e) \
        (vevent2PointerEventAssert(e), (e)->point.y)

#define vevent2PointerEventSetClickCount(e, c) \
        (vevent2PointerEventAssert(e), (e)->clicks = (c))

#define vevent2PointerEventGetClickCount(e) \
        (vevent2PointerEventAssert(e), (e)->clicks)

#define vevent2PointerEventSetModifiers(e, m) \
        (vevent2PointerEventAssert(e), (e)->modifiers = (m))

#define vevent2PointerEventGetModifiers(e) \
        (vevent2PointerEventAssert(e), (e)->modifiers)

/* class vevent2ButtonEvent */

#define vevent2ButtonEventGetClass(e) \
        ((vevent2ButtonEventClass *) \
         vloadableGetClass(vevent2ButtonEventAsLoadable(e)))

#define vevent2ButtonEventCreateOfClass(c) \
        ((vevent2ButtonEvent *) \
         vinstanceCreateOfClass \
         (vevent2ButtonEventClassAsInstanceClass(c)))

#define vevent2ButtonEventCreate() \
        vevent2ButtonEventCreateOfClass \
          (vevent2ButtonEventClassGetDefault())

#define vevent2ButtonEventSetButton(e, b) \
        (vevent2ButtonEventAssert(e), (e)->button = (b))

#define vevent2ButtonEventGetButton(e) \
        (vevent2ButtonEventAssert(e), (e)->button)

/* class vevent2ButtonDownEvent */

#define vevent2ButtonDownEventGetClass(e) \
        ((vevent2ButtonDownEventClass *) \
         vloadableGetClass(vevent2ButtonDownEventAsLoadable(e)))

#define vevent2ButtonDownEventCreateOfClass(c) \
        ((vevent2ButtonDownEvent *) \
         vinstanceCreateOfClass \
         (vevent2ButtonDownEventClassAsInstanceClass(c)))

#define vevent2ButtonDownEventCreate() \
        vevent2ButtonDownEventCreateOfClass \
          (vevent2ButtonDownEventClassGetDefault())

/* class vevent2ButtonUpEvent */

#define vevent2ButtonUpEventGetClass(e) \
        ((vevent2ButtonUpEventClass *) \
         vloadableGetClass(vevent2ButtonUpEventAsLoadable(e)))

#define vevent2ButtonUpEventCreateOfClass(c) \
        ((vevent2ButtonUpEvent *) \
         vinstanceCreateOfClass \
         (vevent2ButtonUpEventClassAsInstanceClass(c)))

#define vevent2ButtonUpEventCreate() \
        vevent2ButtonUpEventCreateOfClass \
          (vevent2ButtonUpEventClassGetDefault())

/* class vevent2PointerEnterEvent */

#define vevent2PointerEnterEventGetClass(e) \
        ((vevent2PointerEnterEventClass *) \
         vloadableGetClass(vevent2PointerEnterEventAsLoadable(e)))

#define vevent2PointerEnterEventCreateOfClass(c) \
        ((vevent2PointerEnterEvent *) \
         vinstanceCreateOfClass \
         (vevent2PointerEnterEventClassAsInstanceClass(c)))

#define vevent2PointerEnterEventCreate() \
        vevent2PointerEnterEventCreateOfClass \
          (vevent2PointerEnterEventClassGetDefault())

/* class vevent2KeyEvent */

#define vevent2KeyEventGetClass(e) \
        ((vevent2KeyEventClass *) \
         vloadableGetClass(vevent2KeyEventAsLoadable(e)))

#define vevent2KeyEventCreateOfClass(c) \
        ((vevent2KeyEvent *) \
         vinstanceCreateOfClass(vevent2KeyEventClassAsInstanceClass(c)))

#define vevent2KeyEventCreate() \
        vevent2KeyEventCreateOfClass(vevent2KeyEventClassGetDefault())

#define vevent2KeyEventSetKey(e, k) \
        ((e)->key = (k))

#define vevent2KeyEventGetKey(e) \
        ((e)->key)

#define vevent2KeyEventSetKeyStroke(e, ks) \
        (((e)->key = vkeyGetStrokeKey(ks)), \
         (vevent2KeyEventAsPointerEvent(e)->modifiers \
          = vkeyGetStrokeModifiers(ks)))

#define vevent2KeyEventGetKeyStroke(e) \
        (vkeyComputeStroke((e)->key, \
                           vevent2KeyEventAsPointerEvent(e)->modifiers));

#define vevent2KeyEventSetKeyCode(e, kc) \
        ((e)->keycode = (kc))

#define vevent2KeyEventGetKeyCode(e) \
        ((e)->keycode)

#define vevent2KeyEventSetKeyChar(e, kc) \
        ((e)->keychar = (kc))

#define vevent2KeyEventGetKeyChar(e) \
        ((e)->keychar)

/* class vevent2KeyDownEvent */

#define vevent2KeyDownEventGetClass(e) \
        ((vevent2KeyDownEventClass *) \
         vloadableGetClass(vevent2KeyDownEventAsLoadable(e)))

#define vevent2KeyDownEventCreateOfClass(c) \
        ((vevent2KeyDownEvent *) \
         vinstanceCreateOfClass \
         (vevent2KeyDownEventClassAsInstanceClass(c)))

#define vevent2KeyDownEventCreate() \
        vevent2KeyDownEventCreateOfClass \
          (vevent2KeyDownEventClassGetDefault())

/* class vevent2KeyUpEvent */

#define vevent2KeyUpEventGetClass(e) \
        ((vevent2KeyUpEventClass *) \
         vloadableGetClass(vevent2KeyUpEventAsLoadable(e)))

#define vevent2KeyUpEventCreateOfClass(c) \
        ((vevent2KeyUpEvent *) \
         vinstanceCreateOfClass \
         (vevent2KeyUpEventClassAsInstanceClass(c)))

#define vevent2KeyUpEventCreate() \
        vevent2KeyUpEventCreateOfClass \
          (vevent2KeyUpEventClassGetDefault())

/* class vevent2PointerLeaveEvent */

#define vevent2PointerLeaveEventGetClass(e) \
        ((vevent2PointerLeaveEventClass *) \
         vloadableGetClass(vevent2PointerLeaveEventAsLoadable(e)))

#define vevent2PointerLeaveEventCreateOfClass(c) \
        ((vevent2PointerLeaveEvent *) \
         vinstanceCreateOfClass \
         (vevent2PointerLeaveEventClassAsInstanceClass(c)))

#define vevent2PointerLeaveEventCreate() \
        vevent2PointerLeaveEventCreateOfClass \
          (vevent2PointerLeaveEventClassGetDefault())

/* class vevent2MotionEvent */

#define vevent2MotionEventGetClass(e) \
        ((vevent2MotionEventClass *) \
         vloadableGetClass(vevent2MotionEventAsLoadable(e)))

#define vevent2MotionEventCreateOfClass(c) \
        ((vevent2MotionEvent *) \
         vinstanceCreateOfClass \
         (vevent2MotionEventClassAsInstanceClass(c)))

#define vevent2MotionEventCreate() \
        vevent2MotionEventCreateOfClass \
          (vevent2MotionEventClassGetDefault())

/* class vevent2WindowStateEvent */

#define vevent2WindowStateEventGetClass(e) \
        ((vevent2WindowStateEventClass *) \
         vloadableGetClass(vevent2WindowStateEventAsLoadable(e)))

#define vevent2WindowStateEventCreateOfClass(c) \
        ((vevent2WindowStateEvent *) \
         vinstanceCreateOfClass \
         (vevent2WindowStateEventClassAsInstanceClass(c)))

#define vevent2WindowStateEventCreate() \
        vevent2WindowStateEventCreateOfClass \
          (vevent2WindowStateEventClassGetDefault())

/* class vevent2WindowUpdateEvent */

#define vevent2WindowUpdateEventGetClass(e) \
        ((vevent2WindowUpdateEventClass *) \
         vloadableGetClass(vevent2WindowUpdateEventAsLoadable(e)))

#define vevent2WindowUpdateEventCreateOfClass(c) \
        ((vevent2WindowUpdateEvent *) \
         vinstanceCreateOfClass \
         (vevent2WindowUpdateEventClassAsInstanceClass(c)))

#define vevent2WindowUpdateEventCreate() \
        vevent2WindowUpdateEventCreateOfClass \
          (vevent2WindowUpdateEventClassGetDefault())

/* class vevent2Handler */

#define vevent2HandlerGetClass(h) \
        ((vevent2HandlerClass *) \
         vloadableGetClass(vevent2HandlerAsLoadable(h)))

#define vevent2HandlerCreateOfClass(c) \
        ((vevent2Handler *) \
         vloadableCreateOfClass(vevent2HandlerClassAsLoadableClass(c)))

#define vevent2HandlerCreate() \
        vevent2HandlerCreateOfClass(vevent2HandlerClassGetDefault())

#define vevent2HandlerInitOfClass(h,c) \
        vloadableInitOfClass(vevent2HandlerAsLoadable(h), \
                             vevent2HandlerClassAsLoadableClass(c))

#define vevent2HandlerInit(h) \
        vevent2HandlerInitOfClass(h, vevent2HandlerClassGetDefault())

#define vevent2HandlerShare(h) \
        (vevent2HandlerAssert(h), (h)->shareCount++)

#define vevent2HandlerRelease(h) \
        (vevent2HandlerAssert(h), (h)->shareCount > 0 ? --(h)->shareCount : \
         (vloadableDestroy(vevent2HandlerAsLoadable(h)), 0))

#define vevent2HandlerIsShared(h) \
        (vevent2HandlerAssert(h), (h)->shareCount > 0)

/* class vevent2Loop */

#define vevent2LoopGetClass(l) \
        ((vevent2LoopClass *) \
         vevent2HandlerGetClass(vevent2LoopAsHandler(l)))

#define vevent2LoopCreateOfClass(c) \
        ((vevent2Loop *) \
         vevent2HandlerCreateOfClass(vevent2LoopClassAsHandlerClass(c)))

#define vevent2LoopCreate() \
        vevent2LoopCreateOfClass(vevent2LoopClassGetDefault())

#define vevent2LoopInitOfClass(l,c) \
        vevent2HandlerInitOfClass(vevent2LoopAsHandler(l), \
                                  vevent2LoopClassAsHandlerClass(c))

#define vevent2LoopInit(l) \
        vevent2LoopInitOfClass(l, vevent2LoopClassGetDefault())

#define vevent2LoopRelease(l) \
        vevent2HandlerRelease(vevent2LoopAsHandler(l))

#define vevent2LoopSetHandler(l, q) \
        (vevent2LoopAssert(l), vevent2HandlerAssert(q), vevent2HandlerRelease((l)->pHandler), vevent2HandlerShare(q), (l)->pHandler = (q))

#define vevent2LoopGetHandler(l) \
        (vevent2LoopAssert(l), (l)->pHandler)

#define vevent2LoopSetDriver(l, d) \
        (vevent2LoopAssert(l), vevent2DriverAssert(d), (l)->pDriver = (d))

#define vevent2LoopGetDriver(l) \
        (vevent2LoopAssert(l), (l)->pDriver)

#define vevent2LoopSetWaitProc(l, p) \
        (vevent2LoopAssert(l), vevent2LoopGetDriver(l)->pWaitProc = (p))

#define vevent2LoopGetWaitProc(l) \
        (vevent2LoopAssert(l), vevent2LoopGetDriver(l)->pWaitProc)

#define vevent2LoopPost(l, e) \
        vevent2HandlerHandleEvent(vevent2LoopAsHandler(l), e)

/* class vevent2Driver */

#define vevent2DriverGetClass(d) \
        ((vevent2DriverClass *) \
         vinstanceGetClass(vevent2DriverAsInstance(d)))

#define vevent2DriverCreateOfClass(c) \
        ((vevent2Driver *) \
         vinstanceCreateOfClass(vevent2DriverClassAsInstanceClass(c)))

#define vevent2DriverCreate() \
        vevent2DriverCreateOfClass(vevent2DriverClassGetDefault())

#define vevent2DriverInitOfClass(d,c) \
        vinstanceInitOfClass(vevent2DriverAsInstance(d), \
                             vevent2DriverClassAsInstanceClass(c))

#define vevent2DriverInit(d) \
        vevent2DriverInitOfClass(d, vevent2DriverClassGetDefault())

#define vevent2DriverShare(d) \
        (vevent2DriverAssert(d), (d)->shareCount++)

#define vevent2DriverRelease(d) \
        (vevent2DriverAssert(d), (d)->shareCount > 0 ? --(d)->shareCount : \
         (vinstanceDestroy(vevent2DriverAsInstance(d)), 0))

#define vevent2DriverIsShared(d) \
        (vevent2DriverAssert(d), (d)->shareCount > 0)

#define vevent2DriverSetWaitProc(d, p) \
        (vevent2DriverAssert(d), (d)->pWaitProc = (p))

#define vevent2DriverGetWaitProc(d) \
        (vevent2DriverAssert(d), (d)->pWaitProc)

/* class vevent2PreBlocker */

#define vevent2PreBlockerGetClass(p) \
        ((vevent2PreBlockerClass *) \
         vinstanceGetClass(vevent2PreBlockerAsInstance(p)))

#define vevent2PreBlockerCreateOfClass(c) \
        ((vevent2PreBlocker *) \
         vinstanceCreateOfClass(vevent2PreBlockerClassAsInstanceClass(c)))

#define vevent2PreBlockerCreate() \
        vevent2PreBlockerCreateOfClass(vevent2PreBlockerClassGetDefault())

#define vevent2PreBlockerInitOfClass(p,c) \
        vinstanceInitOfClass(vevent2PreBlockerAsInstance(p), \
                             vevent2PreBlockerClassAsInstanceClass(c))

#define vevent2PreBlockerInit(p) \
        vevent2PreBlockerInitOfClass(p, vevent2PreBlockerClassGetDefault())

#define vevent2PreBlockerShare(p) \
        (vevent2PreBlockerAssert(p), (p)->shareCount++)

#define vevent2PreBlockerRelease(p) \
        (vevent2PreBlockerAssert(p), (p)->shareCount > 0 ? --(p)->shareCount :\
         (vinstanceDestroy(vevent2PreBlockerAsInstance(p)), 0))

#define vevent2PreBlockerIsShared(p) \
        (vevent2PreBlockerAssert(p), (p)->shareCount > 0)

/* class vevent2Quitter */

#define vevent2QuitterGetClass(q) \
        ((vevent2QuitterClass *) \
         vinstanceGetClass(vevent2QuitterAsInstance(q)))

#define vevent2QuitterCreateOfClass(c) \
        ((vevent2Quitter *) \
         vinstanceCreateOfClass(vevent2QuitterClassAsInstanceClass(c)))

#define vevent2QuitterCreate() \
        vevent2QuitterCreateOfClass(vevent2PreBlockerClassGetDefault())

#define vevent2QuitterInitOfClass(q,c) \
        vinstanceInitOfClass(vevent2QuitterAsInstance(q), \
                             vevent2QuitterClassAsInstanceClass(c))

#define vevent2QuitterInit(q) \
        vevent2QuitterInitOfClass(q, vevent2PreBlockerClassGetDefault())

#define vevent2QuitterShare(q) \
        (vevent2QuitterAssert(q), (q)->shareCount++)

#define vevent2QuitterRelease(q) \
        (vevent2QuitterAssert(q), (q)->shareCount > 0 ? --(q)->shareCount : \
         (vinstanceDestroy(vevent2QuitterAsInstance(q)), 0))

#define vevent2QuitterIsShared(q) \
        (vevent2QuitterAssert(q), (q)->shareCount > 0)

/* class vevent2SystemEventHandler */

#define vevent2SystemEventHandlerGetClass(h) \
        ((vevent2SystemEventHandlerClass *) \
         vinstanceGetClass(vevent2SystemEventHandlerAsInstance(h)))

#define vevent2SystemEventHandlerCreateOfClass(c) \
        ((vevent2SystemEventHandler *) vinstanceCreateOfClass \
         (vevent2SystemEventHandlerClassAsInstanceClass(c)))

#define vevent2SystemEventHandlerCreate() \
        vevent2SystemEventHandlerCreateOfClass \
        (vevent2SystemEventHandlerClassGetDefault())

#define vevent2SystemEventHandlerInitOfClass(h,c) \
        vinstanceInitOfClass(vevent2SystemEventHandlerAsInstance(h), \
                             vevent2SystemEventHandlerClassAsInstanceClass(c))

#define vevent2SystemEventHandlerInit(h) \
        vevent2SystemEventHandlerInitOfClass \
        (h, vevent2SystemEventHandlerClassGetDefault())

#define vevent2SystemEventHandlerShare(q) \
        (vevent2SystemEventHandlerAssert(q), (q)->shareCount++)

#define vevent2SystemEventHandlerRelease(q) \
        (vevent2SystemEventHandlerAssert(q), \
         (q)->shareCount > 0 ? --(q)->shareCount : \
         (vinstanceDestroy(vevent2SystemEventHandlerAsInstance(q)), 0))

#define vevent2SystemEventHandlerIsShared(q) \
        (vevent2SystemEventHandlerAssert(q), (q)->shareCount > 0)

/* misc */

#define _vevent2ManagerInitializing()       (_vevent2ManagerInitializing)


/*
 * * * * * * * * * * PRIVATE function message definitions * * * * * * * * * *
 */

/* class vevent2 */

#define vevent2SetHandler(e, h) \
    vclassSend(vevent2GetClass(e), vevent2SET_HANDLER, (e, h))

#define vevent2SetLoop(e, q) \
    vclassSend(vevent2GetClass(e), vevent2SET_LOOP, (e, q))

#define vevent2NotifyQueued(e, q) \
    vclassSend(vevent2GetClass(e), vevent2NOTIFY_QUEUED, (e, q))

/* class vevent2Handler */

#define vevent2HandlerHandleEvent(h, e) \
    vclassSend(vevent2HandlerGetClass(h), vevent2HandlerHANDLE_EVENT, (h, e))

/* class vevent2Loop */

#define vevent2LoopRun(l) \
    vclassSend(vevent2LoopGetClass(l), vevent2LoopRUN, (l))

#define vevent2LoopStop(l) \
    vclassSend(vevent2LoopGetClass(l), vevent2LoopSTOP, (l))

#define vevent2LoopQuit(l) \
    vclassSend(vevent2LoopGetClass(l), vevent2LoopQUIT, (l))

#define vevent2LoopForceQuit(l) \
    vclassSend(vevent2LoopGetClass(l), vevent2LoopFORCE_QUIT, (l))

#define vevent2LoopPreBlock(l, s, n) \
    vclassSend(vevent2LoopGetClass(l), vevent2LoopPRE_BLOCK, (l, s, n))

#define vevent2LoopFlush(l, s, n) \
    vclassSend(vevent2LoopGetClass(l), vevent2LoopFLUSH, (l, s, n))

#define vevent2LoopBlock(l, s, n) \
    vclassSend(vevent2LoopGetClass(l), vevent2LoopBLOCK, (l, s, n))

#define vevent2LoopUnblock(l) \
    vclassSend(vevent2LoopGetClass(l), vevent2LoopUNBLOCK, (l))

#define vevent2LoopFlushSystemEvents(l) \
    vclassSend(vevent2LoopGetClass(l), vevent2LoopFLUSH_SYSTEM_EVENTS, (l))

#define vevent2LoopGoNative(l) \
    vclassSend(vevent2LoopGetClass(l), vevent2LoopGO_NATIVE, (l))

#define vevent2LoopAddSystemEventHandler(l, h) \
    vclassSend(vevent2LoopGetClass(l), \
               vevent2LoopADD_SYSTEM_EVENT_HANDLER, (l, h))

#define vevent2LoopRemoveSystemEventHandler(l, h) \
    vclassSend(vevent2LoopGetClass(l), \
               vevent2LoopREMOVE_SYSTEM_EVENT_HANDLER, (l, h))

#define vevent2LoopAddPreBlocker(l, p) \
    vclassSend(vevent2LoopGetClass(l), vevent2LoopADD_PRE_BLOCKER, (l, p))

#define vevent2LoopRemovePreBlocker(l, p) \
    vclassSend(vevent2LoopGetClass(l), vevent2LoopREMOVE_PRE_BLOCKER, (l, p))

#define vevent2LoopAddQuitter(l, q) \
    vclassSend(vevent2LoopGetClass(l), vevent2LoopADD_QUITTER, (l, q))

#define vevent2LoopRemoveQuitter(l, q) \
    vclassSend(vevent2LoopGetClass(l), vevent2LoopADD_QUITTER, (l, q))

#define vevent2LoopNext(q, s, n) \
    vclassSend(vevent2LoopGetClass(q), vevent2LoopNEXT, (q, s, n))

#define vevent2LoopPeek(q) \
    vclassSend(vevent2LoopGetClass(q), vevent2LoopPEEK, (q))

#define vevent2LoopPreQueueEvent(q, e) \
    vclassSend(vevent2LoopGetClass(q), vevent2LoopPRE_QUEUE_EVENT, (q, e))

#define vevent2LoopRemovePreQueuedEvent(q, e) \
    vclassSend(vevent2LoopGetClass(q), \
               vevent2LoopREMOVE_PRE_QUEUED_EVENT, (q, e))

#define vevent2LoopRemoveEvent(q, e) \
    vclassSend(vevent2LoopGetClass(q), \
               vevent2LoopREMOVE_EVENT, (q, e))

/* class vevent2Driver */

#define vevent2DriverAddSystemEventHandler(l, h) \
    vclassSend(vevent2DriverGetClass(l), \
               vevent2DriverADD_SYSTEM_EVENT_HANDLER, (l, h))

#define vevent2DriverRemoveSystemEventHandler(l, h) \
    vclassSend(vevent2DriverGetClass(l), \
               vevent2DriverREMOVE_SYSTEM_EVENT_HANDLER, (l, h))

#define vevent2DriverAddPreBlocker(l, p) \
    vclassSend(vevent2DriverGetClass(l), vevent2DriverADD_PRE_BLOCKER, (l, p))

#define vevent2DriverRemovePreBlocker(l, p) \
    vclassSend(vevent2DriverGetClass(l), \
               vevent2DriverREMOVE_PRE_BLOCKER, (l, p))

#define vevent2DriverPreBlock(l, s, n) \
    vclassSend(vevent2DriverGetClass(l), vevent2DriverPRE_BLOCK, (l, s, n))

#define vevent2DriverBlock(l, s, n) \
    vclassSend(vevent2DriverGetClass(l), vevent2DriverBLOCK, (l, s, n))

#define vevent2DriverUnblock(l) \
    vclassSend(vevent2DriverGetClass(l), vevent2DriverUNBLOCK, (l))

#define vevent2DriverHandleSystemEvents(l) \
    vclassSend(vevent2DriverGetClass(l), \
               vevent2DriverHANDLE_SYSTEM_EVENTS, (l))

#define vevent2DriverGoNative(l) \
    vclassSend(vevent2DriverGetClass(l), vevent2DriverGO_NATIVE, (l))

/* class vevent2PreBlocker */

#define vevent2PreBlockerPreBlock(p, s, n) \
    vclassSend(vevent2PreBlockerGetClass(p), \
               vevent2PreBlockerPRE_BLOCK, (p, s, n))

/* class vevent2Quitter */

#define vevent2QuitterQuit(q) \
    vclassSend(vevent2QuitterGetClass(q), vevent2QuitterQUIT, (q))

#define vevent2QuitterForceQuit(q) \
    vclassSend(vevent2QuitterGetClass(q), vevent2QuitterFORCE_QUIT, (q))

/* class vevent2SystemEventHandler */

#define vevent2SystemEventHandlerFlush(h) \
    vclassSend(vevent2SystemEventHandlerGetClass(h), \
               vevent2SystemEventHandlerFLUSH, (h))


vportEND_CPLUSPLUS_EXTERN_C

#endif /* #ifndef vevent2INCLUDED */


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


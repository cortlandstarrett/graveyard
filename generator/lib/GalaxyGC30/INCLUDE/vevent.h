/* $Id: vevent.h,v 1.93 1997/10/21 19:42:51 robert Exp $ */

#ifndef veventINCLUDED
#define veventINCLUDED 1

/* vevent Backward Compatability header file - builds old vevent
   interface on top of new vevent2 interface. */

#ifndef  vportINCLUDED      /* for v*HEADER */
#include <vport.h>
#endif

#ifndef  vstdioINCLUDED
#include vstdioHEADER
#endif

#ifndef  vdebugINCLUDED
#include vdebugHEADER
#endif

#ifndef  vnameINCLUDED
#include vnameHEADER
#endif

#ifndef  vtimestampINCLUDED
#include vtimestampHEADER
#endif

#ifndef  vkeyINCLUDED
#include vkeyHEADER
#endif

#ifndef  vrectINCLUDED
#include vrectHEADER
#endif

#ifndef  vpointINCLUDED
#include vpointHEADER
#endif

#ifndef  vloadableINCLUDED
#include vloadableHEADER
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * * * * * * * * * * * * * PUBLIC TYPES * * * * * * * * * * * * * *
 */

typedef struct vevent                             /* vevent2 */
               vevent;

typedef        vevent
               veventClientEvent;

typedef struct veventWindowEvent                  /* vevent2WindowEvent */
               veventWindowEvent;
typedef struct veventWindowUpdateEvent            /* vevent2WindowUpdateEvent */
               veventWindowUpdateEvent;
typedef struct veventWindowFocusEvent             /* vevent2FocusEvent */
               veventWindowFocusEvent;
typedef struct veventWindowFocusAcquireEvent      /* vevent2FocusAcquireEvent */
               veventWindowFocusAcquireEvent;
typedef struct veventWindowFocusLoseEvent         /* vevent2FocusLoseEvent */
               veventWindowFocusLoseEvent;
typedef struct veventWindowConfigureEvent     /* vevent2WindowConfigureEvent */
               veventWindowConfigureEvent;
typedef struct veventWindowKeyEvent               /* vevent2KeyEvent */
               veventWindowKeyEvent;
typedef struct veventWindowKeyDownEvent           /* vevent2KeyDownEvent */
               veventWindowKeyDownEvent;
typedef struct veventWindowKeyUpEvent             /* vevent2KeyUpEvent */
               veventWindowKeyUpEvent;
typedef struct veventWindowPointerEvent           /* vevent2PointerEvent */
               veventWindowPointerEvent;
typedef struct veventWindowPointerDragEvent       /* vevent2MotionEvent */
               veventWindowPointerDragEvent;
typedef        veventWindowPointerDragEvent       /* vevent2MotionEvent */
               veventWindowPointerDetailEvent;
typedef struct veventWindowPointerEnterEvent      /* vevent2PointerEnterEvent */
               veventWindowPointerEnterEvent;
typedef struct veventWindowPointerLeaveEvent      /* vevent2PointerLeaveEvent */
               veventWindowPointerLeaveEvent;
typedef        veventWindowPointerDragEvent       /* vevent2MotionEvent */
               veventWindowPointerMotionEvent;
typedef struct veventWindowPointerButtonEvent     /* vevent2ButtonEvent */
               veventWindowPointerButtonEvent;
typedef struct veventWindowPointerButtonDownEvent /* vevent2ButtonDownEvent */
               veventWindowPointerButtonDownEvent;
typedef struct veventWindowPointerButtonUpEvent   /* vevent2ButtonUpEvent */
               veventWindowPointerButtonUpEvent;
typedef struct veventWindowStateEvent             /* vevent2WindowStateEvent */
               veventWindowStateEvent;

typedef struct veventHandler veventHandler;

typedef vbool (*veventQuitProc)(void);

typedef int (*veventDispatcherProc)(vevent *e, const veventHandler *h);

typedef int (*veventHandlerProc)(vevent *e);

typedef void (*veventPreBlockHandlerProc)(void);

typedef void (*veventClientQueueFlushProc)(void);

typedef void (*veventClientWaitProc)(long secs, unsigned long nsecs);

typedef void (*veventClientWaitIndefinitelyProc)(void);

typedef void (*veventCancelWaitProc)(void);

typedef int veventType;

typedef int veventPriority;

typedef void (*veventTranslatorProc)(FILE *fp, int flags);

#if (vportOS_UNIX)

typedef struct veventFD veventFD;

typedef struct veventFDIterator veventFDIterator;

typedef void (veventFDNoteProc)(veventFD *fdEvent);

typedef void (_veventFDSelectNoteProc)(int fd);

#endif

#if (vportCPLUSPLUS_SOURCE)
#define _veventSTRUCT              
class vportCLASS_LINK vwindow;
#else
#define _veventSTRUCT struct
struct vwindow;
#endif

/*
 * * * * * * * * * * * * * PUBLIC CONSTANTS * * * * * * * * * * * * * *
 */

#define veventCLIENT                /* 0*/ vevent2TYPE_UNKNOWN
#define veventBUTTON_DOWN           /* 1*/ vevent2TYPE_BUTTON_DOWN
#define veventPOINTER_BUTTON_DOWN   /* 1*/ vevent2TYPE_BUTTON_DOWN
#define veventBUTTON_UP             /* 2*/ vevent2TYPE_BUTTON_UP
#define veventPOINTER_BUTTON_UP     /* 2*/ vevent2TYPE_BUTTON_UP
#define veventPOINTER_DETAIL        /* 3*/ vevent2TYPE_POINTER_DETAIL
#define veventPOINTER_DRAG          /* 4*/ vevent2TYPE_POINTER_DRAG
#define veventWINDOW_CONFIGURE      /* 5*/ vevent2TYPE_WINDOW_CONFIGURED
#define veventFOCUS_ACQUIRE         /* 6*/ vevent2TYPE_FOCUS_ACQUIRED
#define veventWINDOW_FOCUS_ACQUIRE  /* 6*/ vevent2TYPE_FOCUS_ACQUIRED
#define veventFOCUS_LOSE            /* 7*/ vevent2TYPE_FOCUS_LOST
#define veventWINDOW_FOCUS_LOSE     /* 7*/ vevent2TYPE_FOCUS_LOST
#define veventKEY_DOWN              /* 8*/ vevent2TYPE_KEY_DOWN
#define veventWINDOW_KEY_DOWN       /* 8*/ vevent2TYPE_KEY_DOWN
#define veventKEY_UP                /* 9*/ vevent2TYPE_KEY_UP
#define veventWINDOW_KEY_UP         /* 9*/ vevent2TYPE_KEY_UP
#define veventPOINTER_ENTER         /*10*/ vevent2TYPE_POINTER_ENTERED
#define veventWINDOW_POINTER_ENTER  /*10*/ vevent2TYPE_POINTER_ENTERED
#define veventPOINTER_LEAVE         /*11*/ vevent2TYPE_POINTER_LEFT
#define veventWINDOW_POINTER_LEAVE  /*11*/ vevent2TYPE_POINTER_LEFT
#define veventWINDOW_STATE          /*12*/ vevent2TYPE_WINDOW_STATE
#define veventWINDOW_UPDATE         /*13*/ vevent2TYPE_WINDOW_UPDATE_REQUESTED
#define veventPOINTER_MOTION        /*14*/ vevent2TYPE_POINTER_MOVED
#define _veventNUM_HANDLER_TYPES    /*15*/ _vevent2TYPE_NUM_BC_TYPES

#define veventWINDOW_STATE_OPEN            vevent2TYPE_WINDOW_OPENED
#define veventWINDOW_STATE_CLOSE           vevent2TYPE_WINDOW_CLOSED
#define veventWINDOW_STATE_MAXIMIZE        vevent2TYPE_WINDOW_MAXIMIZED
#define veventWINDOW_STATE_UNMAXIMIZE      vevent2TYPE_WINDOW_UNMAXIMIZED
#define veventWINDOW_STATE_ICONIFY         vevent2TYPE_WINDOW_ICONIFIED
#define veventWINDOW_STATE_UNICONIFY       vevent2TYPE_WINDOW_UNICONIFIED
#define veventWINDOW_STATE_PIN             vevent2TYPE_WINDOW_PINNED
#define veventWINDOW_STATE_UNPIN           vevent2TYPE_WINDOW_UNPINNED

enum {
    veventWINDOW_CONFIGURE_MOVE         = 0x01,
    veventWINDOW_CONFIGURE_SIZE         = 0x02,
    veventWINDOW_CONFIGURE_STACK        = 0x04
};

enum {
    veventPRIORITY_MIN                  = 0x00,
    veventPRIORITY_LOW                  = 0x3f,
    veventLOW_PRIORITY                  = veventPRIORITY_LOW,
    veventPRIORITY_DEFAULT              = 0x7f,
    veventDEFAULT_PRIORITY              = veventPRIORITY_DEFAULT,
    veventPRIORITY_HIGH                 = 0xbf,
    veventHIGH_PRIORITY                 = veventPRIORITY_HIGH,
    veventPRIORITY_MAX                  = 0xfe
};

enum {
    veventSTREAM_READ_AVAIL     = 0x1,
    veventSTREAM_WRITE_AVAIL        = 0x2,
    veventSTREAM_EXCEPTION_AVAIL    = 0x4,
    _veventMONITOR_STREAM_READ      = 0x8,
    _veventMONITOR_STREAM_WRITE     = 0x10,
    _veventMONITOR_STREAM_EXCEPTION = 0x20
};

/*
 * * * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * * *
 */

void veventStartup(
    void
    );

void veventQuit(
    void
    );

void veventAddQuitProc(
    veventQuitProc proc
    );

void veventProcess(
    void
    );

void veventFlushProcessing(
    void
    );

void veventStopProcessing(
    void
    );

void veventCancelQuit(
    void
    );

int veventDispatch(
    vevent *event, 
    const veventHandler *target
    );

int veventHandle(
    vevent *event
    );

int veventHandleOwned(
    vevent *event
    );

void veventPost(
    vevent *event
    );

void _veventPostLater(
    vevent *event
    );

void veventPostAtInterrupt(
    vevent *event
    );

void veventPostFuture(
    vevent *event, 
    unsigned long seconds,
    unsigned long nanoseconds
    );

void veventPostFutureAtInterrupt(
    vevent *event, 
    unsigned long seconds,
    unsigned long nanoseconds
    );

void veventPostAtEventTime(
    vevent *event
    );

void veventPostAtEventTimeAtInterrupt(
    vevent *event
    );

vbool veventUnpost(
    vevent *event
    );

void veventDump(
    vevent *event, 
    FILE *stream
    );

vbool veventValidate(
    const vevent *event
    );

void veventAssert(
    const vevent *event
    );

void veventHandledAssert(
    const vevent *event,
    vdebugAssertionHandler handler,
    void *data
    );

void veventReference(
    vevent *event
    );

void veventUnreference(
    vevent *event
    );

int veventIsReferenced(
    vevent *event
    );

void veventDestroy(
    vevent *event
    );

void _veventSetPostTimeType(
    int type
    );


/* ----------------------------------------------------------------------------
 * dispatcher function prototypes
 * ------------------------------------------------------------------------- */

void veventSetDispatcher(
    veventDispatcherProc dispatcher
    );

veventDispatcherProc veventGetDispatcher(
    void
    );

/* deprecated */
veventDispatcherProc veventRegisterDispatcher(
    veventDispatcherProc dispatcher
    );


/* ----------------------------------------------------------------------------
 * handler function prototypes
 * ------------------------------------------------------------------------- */

veventHandler *veventCreateHandler(
    void
    );

void veventInitHandler(
    veventHandler *handler
    );

void veventCopyHandler(
    const veventHandler *from, 
    veventHandler *to
    );

void veventCopyInitHandler(
    const veventHandler *from, 
    veventHandler *to
    );

veventHandler *veventCloneHandler(
    veventHandler *handler
    );

void veventDestroyHandler(
    veventHandler *handler
    );

/* deprecated */
const veventHandler *veventRegisterHandler(
    const veventHandler *newHandler
    );

void veventSetHandler(
    const veventHandler *handler
    );

const veventHandler *veventGetHandler(
    void
    );

veventHandlerProc veventGetHandlerProc(
    veventHandler *handler, 
    int type
    );

void veventSetHandlerProc(
    veventHandler *handler,
    int type,
    veventHandlerProc handlerProc
    );


/* ----------------------------------------------------------------------------
 * event loop hook function prototypes
 * ------------------------------------------------------------------------- */

veventPreBlockHandlerProc veventGetPreBlockHandlerProc(
    void
    );

void veventSetPreBlockHandlerProc(
    veventPreBlockHandlerProc proc
    );

veventClientQueueFlushProc veventGetClientQueueFlushProc(
    void
    );

void veventSetClientQueueFlushProc(
    veventClientQueueFlushProc proc
    );

veventClientWaitProc veventGetClientWaitProc(
    void
    );

void veventSetClientWaitProc(
    veventClientWaitProc proc
    );

veventClientWaitIndefinitelyProc veventGetClientWaitIndefinitelyProc(
    void
    );

void veventSetClientWaitIndefinitelyProc(
    veventClientWaitIndefinitelyProc proc
    );

veventCancelWaitProc veventGetCancelWaitProc(
    void
    );

void veventSetCancelWaitProc(
    veventCancelWaitProc proc
    );


/* ----------------------------------------------------------------------------
 * file descriptor translator function prototypes
 * ------------------------------------------------------------------------- */

#if (vportOS_UNIX)

veventFD         *veventRegisterFD         (int               fd);
void              veventUnregisterFD       (veventFD         *file);
int               veventGetFDFileDescriptor(veventFD         *file);

veventFDNoteProc *veventGetFDReadNotify    (veventFD         *file);
void              veventSetFDReadNotify    (veventFD         *file,
                                            veventFDNoteProc *noteProc);
veventFDNoteProc *veventGetFDWriteNotify   (veventFD         *file);
void              veventSetFDWriteNotify   (veventFD         *file,
                                            veventFDNoteProc *noteProc);
veventFDNoteProc *veventGetFDExceptNotify  (veventFD         *file);
void              veventSetFDExceptNotify  (veventFD         *file,
                                            veventFDNoteProc *noteProc);

void             *veventGetFDData          (veventFD *file);
void              veventSetFDData          (veventFD *file, const void *data);

void              veventInitFDIterator     (veventFDIterator *iterator);
int               veventNextFDIterator     (veventFDIterator *iterator);
veventFD         *veventGetFDIteratorFD    (veventFDIterator *iterator);
void              veventDestroyFDIterator  (veventFDIterator *iterator);

#endif


/* ----------------------------------------------------------------------------
 * event interface function prototypes
 * ------------------------------------------------------------------------- */

veventType veventGetType(
    vevent *event
    );

void veventSetType(
    vevent *event, 
    veventType type
    );

vtimestamp veventGetTime(
    vevent *event
    );

void veventSetTime(
    vevent *event, 
    vtimestamp time
    );

veventPriority veventGetPriority(
    vevent *event
    );

void veventSetPriority(
    vevent *event,
    veventPriority priority
    );

const vname *veventGetBinding(
    vevent *event
    );

void veventSetBinding(
    vevent *event, 
    const vname *binding
    );

veventHandlerProc veventGetTarget(
    vevent *event
    );

void veventSetTarget(
    vevent *event, 
    veventHandlerProc target
    );

const void *veventGetData(
    vevent *event
    );

void veventSetData(
    vevent *event, 
    const void *data
    );

int _veventGetFlags(
    vevent *event
    );

void _veventSetFlags(
    vevent *event, 
    int flags
    );

int veventGetX(
    vevent *event
    );

int veventGetY(
    vevent *event
    );

void veventSetX(
    vevent *event,
    int     x
    );

void veventSetY(
    vevent *event,
    int     y
    );

vbool veventIsSynchronizationRequested(
    vevent *event
    );

void veventSetSynchronizationRequested(
    vevent *event,
    int     requested
    );

void veventSetSyncFlagOn(
    vevent *event
    );

void veventSetSyncFlagOff(
    vevent *event
    );

vbool _veventIsEnqueued(
    vevent *event
    );

void _veventSetEnqueuedFlagOn(
    vevent *event
    );

void _veventSetEnqueuedFlagOff(
    vevent *event
    );

void _veventSetSubLoopFlagOn(
    vevent *event
    );

void _veventSetSubLoopFlagOff(
    vevent *event
    );

/* deprecated Event/Application Interfaces */
vevent          *veventCreateApplication(void);
int              veventGetApplicationType(vevent *event);
const void      *veventGetApplicationData(vevent *event);
void             veventSetApplicationType(vevent *event, int type);
void             veventSetApplicationData(vevent *event, void *data);
 
/* Event/Client Interfaces */
vevent          *veventCreateClient(void);
int              veventGetClientType(vevent *event);
const void      *veventGetClientData(vevent *event);
void             veventSetClientType(vevent *event, int type);
void             veventSetClientData(vevent *event, void *data);
 
/* Event/Window Interfaces */
_veventSTRUCT vwindow   *veventGetWindow(vevent *event);
void             veventSetWindow(vevent *event,
                                 _veventSTRUCT vwindow *window);

/* Event/Window/Configure Interfaces */
vevent          *veventCreateWindowConfigure(void);
vbool            veventIsMove(vevent *event);
vbool            veventIsSize(vevent *event);
vbool            veventIsStack(vevent *event);
int              veventGetConfigureX(vevent *event);
int              veventGetConfigureY(vevent *event);
int              veventGetConfigureWidth(vevent *event);
int              veventGetConfigureHeight(vevent *event);
int              veventGetConfigureFlags(vevent *event);
void             veventSetConfigureX(vevent *event, int x);
void             veventSetConfigureY(vevent *event, int y);
void             veventSetConfigureWidth(vevent *event, int width);
void             veventSetConfigureHeight(vevent *event, int height);
void             veventSetConfigureFlags(vevent *event, int flags);

/* Event/Window/Focus/Acquire Interfaces */
vevent          *veventCreateFocusAcquire(void);

/* Event/Window/Focus/Lose Interfaces */
vevent          *veventCreateFocusLose(void);

/* Event/Window/Key Interfaces */
vkey             veventGetKey(vevent *event);
void             veventSetKey(vevent *event, vkey key);
vkeyStroke       veventGetKeyStroke(vevent *event);
void             veventSetKeyStroke(vevent *event, vkeyStroke keyStroke);
vchar            veventGetKeyChar(vevent *event);
void             veventSetKeyChar(vevent *event,
                                  unsigned int /*vchar*/ keyChar);
unsigned int     veventGetKeyCode(vevent *event);
void             veventSetKeyCode(vevent *event, unsigned int keyCode);
int              veventGetKeyX(vevent *event);
int              veventGetKeyY(vevent *event);
void             veventSetKeyX(vevent *event, int x);
void             veventSetKeyY(vevent *event, int y);
vbool            veventIsKeyModifierOn(vevent *event,
                                       vkeyModifiers modifier);
void             veventSetKeyModifierOn(vevent *event,
                                        vkeyModifiers modifier);
void             veventSetKeyModifierOff(vevent *event,
                                         vkeyModifiers modifier);
vkeyModifiers    veventGetKeyModifiers(vevent *event);
void             veventSetKeyModifiers(vevent *event,
                                       vkeyModifiers modifiers);

/* Event/Window/Key/Down Interfaces */
vevent          *veventCreateKeyDown(void);

/* Event/Window/Key/Up Interfaces */
vevent          *veventCreateKeyUp(void);

/* Event/Window/Pointer Interfaces */
int              veventGetPointerX(vevent *event);
int              veventGetPointerY(vevent *event);
void             veventSetPointerX(vevent *event, int x);
void             veventSetPointerY(vevent *event, int y);
vbool            veventIsPointerModifierOn(vevent *event,
                                           vkeyModifiers modifier);
void             veventSetPointerModifierOn(vevent *event,
                                            vkeyModifiers modifier);
void             veventSetPointerModifierOff(vevent *event,
                                             vkeyModifiers modifier);
vkeyModifiers    veventGetPointerModifiers(vevent *event);
void             veventSetPointerModifiers(vevent *event,
                                           vkeyModifiers modifiers);
vbyte            veventGetPointerButtonCount(vevent *event);
void             veventSetPointerButtonCount(vevent *event,
                                             int /*vbyte*/ count);
vbyte            veventGetPointerClickCount(vevent *event);
void             veventSetPointerClickCount(vevent *event,
                                            int /*vbyte*/ count);

/* Event/Window/Pointer/Button Interfaces */
int              veventGetPointerButton(vevent *event);
void             veventSetPointerButton(vevent *event, int button);

/* Event/Window/Pointer/Button/Down Interfaces */
vevent          *veventCreateButtonDown(void);

/* Event/Window/Pointer/Button/Up Interfaces */
vevent          *veventCreateButtonUp(void);

/* Event/Window/Pointer/Drag Interfaces */
vevent          *veventCreatePointerDrag(void);

/* Event/Window/Pointer/Detail Interfaces */
vevent          *veventCreatePointerDetail(void);

/* Event/Window/Pointer/Motion Interfaces */
vevent          *veventCreatePointerMotion(void);

/* Event/Window/Pointer/Enter Interfaces */
vevent          *veventCreatePointerEnter(void);

/* Event/Window/Pointer/Leave Interfaces */
vevent          *veventCreatePointerLeave(void);

/* Event/Window/State Interfaces */
vevent          *veventCreateWindowState(void);
vbool            veventIsOpen(vevent *event);
vbool            veventIsClose(vevent *event);
vbool            veventIsIconify(vevent *event);
vbool            veventIsUniconify(vevent *event);
vbool            veventIsMaximize(vevent *event);
vbool            veventIsUnmaximize(vevent *event);
vbool            veventIsPin(vevent *event);
vbool            veventIsUnpin(vevent *event);
int              veventGetWindowStateType(vevent *event);
void             veventSetWindowStateType(vevent *event, int type);

/* Event/Window/Update Interfaces */
vevent          *veventCreateWindowUpdate(void);

/* Misc Window System Interfaces */
unsigned long    veventGetDoubleClickInterval(void);
void             veventSetDoubleClickInterval(unsigned long interval);



/* ----------------------------------------------------------------------------
 * deprecated function prototypes
 * ------------------------------------------------------------------------- */

vevent              *_veventCreate(void);
vevent              *veventClone(vevent *event);

void                 veventRegisterStreamTranslator(FILE *file,
                                              veventTranslatorProc translator);
void                 veventUnregisterStreamTranslator(FILE *file);
veventTranslatorProc veventGetStreamTranslator(FILE *file);
void                 veventSetStreamTranslator(FILE *file,
                                              veventTranslatorProc translator);

vbool                veventGetMonitorStreamRead(FILE *file);
void                 veventSetMonitorStreamRead(FILE *file,
                                                int /*vbool*/ value);
void                 veventSetMonitorStreamReadOn(FILE *file);
void                 veventSetMonitorStreamReadOff(FILE *file);
vbool                veventGetMonitorStreamWrite(FILE *file);
void                 veventSetMonitorStreamWrite(FILE *file,
                                                 int /*vbool*/ value);
void                 veventSetMonitorStreamWriteOn(FILE *file);
void                 veventSetMonitorStreamWriteOff(FILE *file);
vbool                veventGetMonitorStreamException(FILE *file);
void                 veventSetMonitorStreamException(FILE *file,
                                                     int /*vbool*/ value);
void                 veventSetMonitorStreamExceptionOn(FILE *file);
void                 veventSetMonitorStreamExceptionOff(FILE *file);

/*
 * * * * * * * * * * PRIVATE exported types * * * * * * * * * *
 */

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

struct vevent /* vevent2 */
{
    vloadable                     super;
    volatile vbyte                triggered;
    vbyte                         flags;
    vbyte                         priority;
    vevent2Type                   type;
    short                         shareCount;
    const vname                  *pBinding;
    vtimestamp                    time;
    vevent2Handler               *pHandler;
    void                         *pData;
    vevent2Loop                  *pLoop;
    _vevent2HandlerProc          *pTarget;
    vevent2Handler               *pTempHandler;
#if (vdebugDEBUG)
    int                           signature;
#endif
};

struct veventWindowEvent /* vevent2WindowEvent */
{
    vevent2                       super;
    _vevent2STRUCT vwindow       *pWindow;
#if (vdebugDEBUG)
    int                           signature;
#endif
};

struct veventWindowConfigureEvent /* vevent2WindowConfigureEvent */
{
    vevent2WindowEvent            super;
    _vevent2STRUCT vwindow       *pAbove;
    vrect                         rect;
#if (vdebugDEBUG)
    int                           signature;
#endif
};

struct veventWindowFocusEvent /* vevent2FocusEvent */
{
    vevent2WindowEvent            super;
#if (vdebugDEBUG)
    int                           signature;
#endif
};

struct veventWindowFocusAcquireEvent /* vevent2FocusAcquireEvent */
{
    vevent2FocusEvent             super;
#if (vdebugDEBUG)
    int                           signature;
#endif
};

struct veventWindowFocusLoseEvent /* vevent2FocusLoseEvent */
{
    vevent2FocusEvent             super;
#if (vdebugDEBUG)
    int                           signature;
#endif
};

struct veventWindowPointerEvent /* vevent2PointerEvent */
{
    vevent2WindowEvent            super;
    vpoint                        point;
    vkeyModifiers                 modifiers;
    vbyte                         clicks;
#if (vdebugDEBUG)
    int                           signature;
#endif
};

struct veventWindowPointerButtonEvent /* vevent2ButtonEvent */
{
    vevent2PointerEvent           super;
    vevent2Button                 button;
#if (vdebugDEBUG)
    int                           signature;
#endif
};

struct veventWindowPointerButtonDownEvent /* vevent2ButtonDownEvent */
{
    vevent2ButtonEvent            super;
#if (vdebugDEBUG)
    int                           signature;
#endif
};

struct veventWindowPointerButtonUpEvent /* vevent2ButtonUpEvent */
{
    vevent2ButtonEvent            super;
#if (vdebugDEBUG)
    int                           signature;
#endif
};

struct veventWindowPointerEnterEvent /* vevent2PointerEnterEvent */
{
    vevent2PointerEvent           super;
#if (vdebugDEBUG)
    int                           signature;
#endif
};

struct veventWindowKeyEvent /* vevent2KeyEvent */
{
    vevent2PointerEvent           super;
    unsigned int                  hwkey; /*???*/
    unsigned int                  keycode;
    vkey                          key;
    vchar                         keychar;
    vbool                         autorepeat;
#if (vdebugDEBUG)
    int                           signature;
#endif
};

struct veventWindowKeyDownEvent /* vevent2KeyDownEvent */
{
    vevent2KeyEvent               super;
#if (vdebugDEBUG)
    int                           signature;
#endif
};

struct veventWindowKeyUpEvent /* vevent2KeyUpEvent */
{
    vevent2KeyEvent               super;
#if (vdebugDEBUG)
    int                           signature;
#endif
};

struct veventWindowPointerLeaveEvent /* vevent2PointerLeaveEvent */
{
    vevent2PointerEvent           super;
#if (vdebugDEBUG)
    int                           signature;
#endif
};

struct veventWindowPointerDragEvent /* vevent2MotionEvent */
{
    vevent2PointerEvent           super;
#if (vdebugDEBUG)
    int                           signature;
#endif
};

struct veventWindowStateEvent /* vevent2WindowStateEvent */
{
    vevent2WindowEvent            super;
#if (vdebugDEBUG)
    int                           signature;
#endif
};

struct veventWindowUpdateEvent /* vevent2WindowUpdateEvent */
{
    vevent2WindowEvent            super;
#if (vdebugDEBUG)
    int                           signature;
#endif
};

vportALIAS(veventClientEvent, vevent)


vportEND_CPLUSPLUS_EXTERN_C

#ifndef  vevent2INCLUDED
#include vevent2HEADER
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C

typedef vevent2Iterator veventPostedIterator;

typedef vevent2Loop _veventLoop;

typedef veventHandlerProc _veventHandlerProcArray[_veventNUM_HANDLER_TYPES];

struct veventHandler
{
    vevent2Handler           super;
    vevent2Handler          *pDelegate;
    _veventHandlerProcArray  a;
    /* vbyte                 flags; */
};

typedef struct veventHandlerClass veventHandlerClass;

#define veventHandlerCLASS(CLASS, HANDLER)\
    vevent2HandlerCLASS(CLASS, HANDLER)

struct veventHandlerClass
{
    veventHandlerCLASS(veventHandlerClass, veventHandler);
};

#if (vportOS_UNIX)

struct veventFD
{
    veventFD                   *pNext;
    int                         fd;
    _veventFDSelectNoteProc    *pRead;
    _veventFDSelectNoteProc    *pWrite;
    _veventFDSelectNoteProc    *pExcept;
    void                       *pData;
};

struct veventFDIterator {
    int index;
    int count;
};

#endif

/*
 * * * * * * * * * * PRIVATE exported variables * * * * * * * * * *
 */

extern vportLINK unsigned long    _vevent2bcDoubleClickNanoseconds;
extern vportLINK int              _vevent2bcBlockingQuit;
extern vportLINK int              _vevent2bcQuitting;
extern vportLINK int              _vevent2bcSystemQuit;


/*
 * * * * * * * * * * PRIVATE exported prototypes * * * * * * * * * *
 */

void     veventInitPostedIterator    (veventPostedIterator *iterator);
int      veventNextPostedIterator    (veventPostedIterator *iterator);
vevent  *veventGetPostedIteratorEvent(veventPostedIterator *iterator);
void     veventDestroyPostedIterator (veventPostedIterator *iterator);

_veventLoop *_veventCreateLoop   (void);
void         _veventDestroyLoop  (_veventLoop *loop);
void         _veventInitLoop     (_veventLoop *loop);
void         _veventRunLoop      (_veventLoop *loop, int waitForNowQueue);
void         _veventFlushLoop    (_veventLoop *loop, int waitForNowQueue);
void         _veventStopLoop     (_veventLoop *loop);
int          _veventIsLoopStopped(_veventLoop *loop);

void                 _vevent2bcStartup         (void);
vevent              *_vevent2bcSetBC           (vevent2 *p, veventType type);
const veventHandler *_vevent2bcRegisterHandler (const veventHandler *pHandler);
void                 _vevent2bcSetHandler      (const veventHandler *pHandler);
veventHandler       *_vevent2bcGetHandler      (void);

veventHandlerClass  *_vevent2bcHandlerClassGetDefault(void);
int                  _vevent2bcHandle                (vevent           *event);
int                  _vevent2bcHandleOwned           (vevent           *event);

veventDispatcherProc _vevent2bcGetDispatcher         (void);
veventDispatcherProc _vevent2bcRegisterDispatcher    (veventDispatcherProc p);

void                  vevent2bcCancelQuit            (void);

void                 _vevent2bcReference             (vevent2          *event);
void                 _vevent2bcPostDenewbize         (vevent2          *event);

void                 _vevent2bcAddQuitProc           (veventQuitProc    proc);

vevent2Class		*_vevent2bcGetDefaultClientEventClass(void);

#if (vportOS_UNIX)

veventFD            *_vevent2bcRegisterFD(int fd);
void                 _vevent2bcUnregisterFD(veventFD *file);
int                  _vevent2bcGetFDCount(void);
veventFD            *_vevent2bcGetFDAt(int index);

veventFDNoteProc    *_vevent2bcGetFDReadNotify       (veventFD         *file);
void                 _vevent2bcSetFDReadNotify       (veventFD         *file,
                                                      veventFDNoteProc *p);
veventFDNoteProc    *_vevent2bcGetFDWriteNotify      (veventFD         *file);
void                 _vevent2bcSetFDWriteNotify      (veventFD         *file,
                                                      veventFDNoteProc *p);
veventFDNoteProc    *_vevent2bcGetFDExceptNotify     (veventFD         *file);
void                 _vevent2bcSetFDExceptNotify     (veventFD         *file,
                                                      veventFDNoteProc *p);

void                *_vevent2bcGetFDData             (veventFD         *file);
void                 _vevent2bcSetFDData             (veventFD         *file,
                                                      const void       *data);

#endif

/*
 * * * * * * * * * * PRIVATE function macro definitions * * * * * * * * * *
 */

#define _veventAsInstance(e) \
        vevent2AsInstance(_veventAsEvent2(e))
#define _veventAsEvent2(e) \
        (vevent2Assert((vevent2 *)(e)), (vevent2 *)(e))
#define _veventAsWindowEvent(e) \
        (vevent2WindowEventAssert((vevent2WindowEvent *)(e)), \
         (vevent2WindowEvent *)(e))
#define _veventAsWindowConfigureEvent(e) \
        (vevent2WindowConfigureEventAssert \
         ((vevent2WindowConfigureEvent *)(e)), \
         (vevent2WindowConfigureEvent *)(e))
#define _veventAsFocusAcquireEvent(e) \
        (vevent2FocusAcquireEventAssert \
         ((vevent2FocusAcquireEvent *)(e)), \
         (vevent2FocusAcquireEvent *)(e))
#define _veventAsFocusLoseEvent(e) \
        (vevent2FocusLoseEventAssert \
         ((vevent2FocusLoseEvent *)(e)), \
         (vevent2FocusLoseEvent *)(e))
#define _veventAsPointerEvent(e) \
        (vevent2PointerEventAssert((vevent2PointerEvent *)(e)), \
         (vevent2PointerEvent *)(e))
#define _veventAsKeyEvent(e) \
        (vevent2KeyEventAssert((vevent2KeyEvent *)(e)), \
         (vevent2KeyEvent *)(e))
#define _veventAsKeyDownEvent(e) \
        (vevent2KeyDownEventAssert((vevent2KeyDownEvent *)(e)), \
         (vevent2KeyDownEvent *)(e))
#define _veventAsKeyUpEvent(e) \
        (vevent2KeyUpEventAssert((vevent2KeyUpEvent *)(e)), \
         (vevent2KeyUpEvent *)(e))
#define _veventAsButtonEvent(e) \
        (vevent2ButtonEventAssert((vevent2ButtonEvent *)(e)), \
         (vevent2ButtonEvent *)(e))
#define _veventAsButtonDownEvent(e) \
        (vevent2ButtonDownEventAssert((vevent2ButtonDownEvent *)(e)), \
         (vevent2ButtonDownEvent *)(e))
#define _veventAsButtonUpEvent(e) \
        (vevent2ButtonUpEventAssert((vevent2ButtonUpEvent *)(e)), \
         (vevent2ButtonUpEvent *)(e))
#define _veventAsPointerEnterEvent(e) \
        (vevent2PointerEnterEventAssert((vevent2PointerEnterEvent *)(e)), \
         (vevent2PointerEnterEvent *)(e))
#define _veventAsPointerLeaveEvent(e) \
        (vevent2PointerLeaveEventAssert((vevent2PointerLeaveEvent *)(e)), \
         (vevent2PointerLeaveEvent *)(e))
#define _veventAsWindowStateEvent(e) \
        (vevent2WindowStateEventAssert((vevent2WindowStateEvent *)(e)), \
         (vevent2WindowStateEvent *)(e))
#define _veventAsWindowUpdateEvent(e) \
        (vevent2WindowUpdateEventAssert((vevent2WindowUpdateEvent *)(e)), \
         (vevent2WindowUpdateEvent *)(e))
#define _veventHandlerAsHandler2(h) \
        vportBASE_OBJECT(h, super)

#define _vevent2Gripe(old, new) \
        vdebugMWarn((vportQUOTE(old)" deprecated by "vportQUOTE(new)"\n"))

#define veventStartup() \
        _vevent2bcStartup()
#define veventQuit() \
        vevent2LoopQuit(vevent2LoopGetCurrent())
#define veventAddQuitProc(p) \
        _vevent2bcAddQuitProc(p)
#define _veventCreateLoop() \
        (vevent2HandlerShare(vevent2LoopAsHandler(vevent2LoopGetCurrent())), \
         vevent2LoopGetCurrent())
#define _veventDestroyLoop(l) \
        vevent2LoopRelease(l)
#define _veventInitLoop(l) \
        vevent2LoopInit(l)
#define _veventRunLoop(l, w) \
        vevent2LoopRun(l)
#define _veventFlushLoop(l, w) \
        {unsigned long sec, nsec; vevent2LoopFlush(l, &sec, &nsec);}
#define _veventStopLoop(l) \
        vevent2LoopStop(l)
#define veventProcess() \
        vevent2LoopRun(vevent2LoopGetCurrent())
#define veventFlushProcessing() \
        _veventFlushLoop(vevent2LoopGetCurrent(), TRUE)
#define veventStopProcessing() \
        vevent2LoopStop(vevent2LoopGetCurrent())
#define veventCancelQuit() \
        vevent2bcCancelQuit()
#define veventGetDispatcher() \
        _vevent2bcGetDispatcher()
#define veventDispatch(e, h) \
        (veventGetDispatcher()(e, h))
#define veventHandle(e) \
        _vevent2bcHandle(e)
#define veventHandleOwned(e) \
        _vevent2bcHandleOwned(e)
#define veventPost(e) \
        (vevent2SetTime(_veventAsEvent2(e), vtimestampGetRecent()), \
         _vevent2bcPostDenewbize(_veventAsEvent2(e)))
#define _veventPostLater(e) \
        (_veventAsEvent2(e)->flags &= ~_vevent2BCNEWBIE, \
         vevent2LoopPostLater(vevent2LoopGetCurrent(), _veventAsEvent2(e)))
#define veventPostAtInterrupt(e) \
        vevent2PostAtInterrupt(e)
#define veventPostFuture(e, s, ns) \
        (vevent2SetTime(_veventAsEvent2(e), \
                        vtimestampAdd(vtimestampGetRecent(), s, ns)), \
         _vevent2bcPostDenewbize(_veventAsEvent2(e)))
#define veventPostFutureAtInterrupt(e, s, ns) \
        vevent2PostAtInterrupt(e)
#define veventPostAtEventTime(e) \
        _vevent2bcPostDenewbize(_veventAsEvent2(e))
#define veventPostAtEventTimeAtInterrupt(e) \
        vevent2PostAtInterrupt(e)
#define veventUnpost(e) \
        (vevent2LoopRemoveEvent(vevent2LoopGetCurrent(), _veventAsEvent2(e)), \
         vTRUE)
#define veventDump(e,fp) \
        vevent2Dump(_veventAsEvent2(e),fp)
#define veventValidate(e) \
        vevent2Validate(_veventAsEvent2(e))
#define veventAssert(e) \
        vevent2Assert(_veventAsEvent2(e))
#define veventHandledAssert(e, h, d) \
        vevent2HandledAssert(_veventAsEvent2(e), h, d)
#define veventReference(e) \
        _vevent2bcReference(_veventAsEvent2(e))
#define veventUnreference(e) \
        (_veventAsEvent2(e)->flags &= ~_vevent2BCNEWBIE, \
         vevent2Release(_veventAsEvent2(e)))
#define veventIsReferenced(e) \
        vevent2IsShared(_veventAsEvent2(e))
#define veventDestroy(e) \
        veventUnreference(e)
#define veventRegisterDispatcher(d) \
        _vevent2bcRegisterDispatcher(d)
#define veventSetDispatcher(d) \
        ((void)_vevent2bcRegisterDispatcher(d))
#define veventCreateHandler() \
        (vevent2Startup(), (veventHandler *) \
         vevent2HandlerCreateOfClass((vevent2HandlerClass *) \
                                     _vevent2bcHandlerClassGetDefault()))
#define veventInitHandler(h) \
        (vevent2Startup(), \
         vloadableInitOfClass \
         (vevent2HandlerAsLoadable(_veventHandlerAsHandler2(h)), \
          _vevent2bcHandlerClassGetDefault()))
#define veventCopyHandler(f, t) \
        vloadableCopy \
        ((vloadable *) vevent2HandlerAsLoadable(_veventHandlerAsHandler2(f)), \
         vevent2HandlerAsLoadable(_veventHandlerAsHandler2(t)))
#define veventCopyInitHandler(f, t) \
        vloadableCopyInit \
        ((vloadable *) vevent2HandlerAsLoadable(_veventHandlerAsHandler2(f)), \
         vevent2HandlerAsLoadable(_veventHandlerAsHandler2(t)))
#define veventCloneHandler(h) \
        ((veventHandler *) \
         vloadableClone(vevent2HandlerAsLoadable(_veventHandlerAsHandler2(h)))
#define veventDestroyHandler(h) \
        vevent2HandlerRelease(_veventHandlerAsHandler2(h))
#define veventRegisterHandler(h) \
        _vevent2bcRegisterHandler(h)
#define veventSetHandler(h) \
        _vevent2bcSetHandler(h)
#define veventGetHandler() \
        _vevent2bcGetHandler()
#define veventGetHandlerProc(h,t) \
        ((h)->a[t])
#define veventSetHandlerProc(h,t,p) \
        ((h)->a[t] = (p))
#define veventGetClientWaitProc() \
        vevent2LoopGetWaitProc(vevent2LoopGetCurrent())
#define veventSetClientWaitProc(p) \
        vevent2LoopSetWaitProc(vevent2LoopGetCurrent(), p)
#define veventGetClientWaitIndefinitelyProc() \
        NULL
#define veventSetClientWaitIndefinitelyProc(p)
#if (vportOS_UNIX)
/*
 * Compilers for 64-bit architectures may throw a warning for casting
 * from a pointer to an int, so we cast to a long first.
 */
#define veventGetFDFileDescriptor(fd) \
        ((int)(long)(fd))
#define veventGetFDReadNotify(fd) \
        _vevent2bcGetFDReadNotify(fd)
#define veventSetFDReadNotify(fd, n) \
        _vevent2bcSetFDReadNotify(fd, n)
#define veventGetFDWriteNotify(fd) \
        _vevent2bcGetFDWriteNotify(fd)
#define veventSetFDWriteNotify(fd, n) \
        _vevent2bcSetFDWriteNotify(fd, n)
#define veventGetFDExceptNotify(fd) \
        _vevent2bcGetFDExceptNotify(fd)
#define veventSetFDExceptNotify(fd, n) \
        _vevent2bcSetFDExceptNotify(fd, n)
#define veventGetFDData(fd) \
        _vevent2bcGetFDData(fd)
#define veventSetFDData(fd, d) \
        _vevent2bcSetFDData(fd, d)
#define veventRegisterFD(fd) \
        _vevent2bcRegisterFD(fd)
#define veventUnregisterFD(fd) \
        _vevent2bcUnregisterFD(fd)

#define veventInitFDIterator(i) \
       if (1) {(i)->index = -1; (i)->count = _vevent2bcGetFDCount(); } \
       else ((void) 0)
#define veventNextFDIterator(i)	  (++(i)->index < (i)->count)
#define veventGetFDIteratorFD(i)  ((veventFD *) _vevent2bcGetFDAt((i)->index))
#define veventDestroyFDIterator(i)	((void)0)

#endif
#define veventGetType(e) \
        (((e)->type < _vevent2TYPE_NUM_BC_TYPES) ? (int) (e)->type : \
         (((e)->type > vevent2TYPE_WINDOW_UNPINNED) ? veventCLIENT : \
          (((e)->type >= vevent2TYPE_WINDOW_CLOSED) ? veventWINDOW_STATE : \
           veventCLIENT)))
#define veventSetType(e, t) \
        (vdebugAssert((t) < _veventNUM_HANDLER_TYPES), \
         (e)->type = (unsigned int) (t))
#define veventGetPriority(e) \
        ((veventPriority)vevent2GetPriority(_veventAsEvent2(e)))
#define veventSetPriority(e, p) \
        vevent2SetPriority(_veventAsEvent2(e),(vevent2Priority)p)
#define veventGetBinding(e) \
        vevent2GetBinding(_veventAsEvent2(e))
#define veventSetBinding(e, b) \
        vevent2SetBinding(_veventAsEvent2(e), b)
#define veventGetTarget(e) \
        ((e)->pTarget)
#define veventSetTarget(e, t) \
        ((e)->pTarget = (t))
#define veventGetX(e) \
        vevent2PointerEventGetX(_veventAsPointerEvent(e))
#define veventGetY(e) \
        vevent2PointerEventGetY(_veventAsPointerEvent(e))
#define veventSetX(e, x) \
        vevent2PointerEventSetX(_veventAsPointerEvent(e), x)
#define veventSetY(e, y) \
        vevent2PointerEventSetY(_veventAsPointerEvent(e), y)
#define veventIsSynchronizationRequested(e) \
        (_veventAsEvent2(e)->flags & _vevent2SYNC)
#define veventSetSyncFlagOn(e) \
        (_veventAsEvent2(e)->flags |= _vevent2SYNC)
#define veventSetSyncFlagOff(e) \
        (_veventAsEvent2(e)->flags &= ~_vevent2SYNC)
#define veventSetSynchronizationRequested(e, s) \
        ((s) ? veventSetSyncFlagOn(e) : veventSetSyncFlagOff(e))
#define veventCreateClient() \
        _vevent2bcSetBC(vevent2CreateOfClass( \
            _vevent2bcGetDefaultClientEventClass()), veventCLIENT)
#define veventGetClientType(e) \
        ((vevent2GetType(e) < vevent2TYPE_NEXT_APPLICATION_TYPE) \
         ? 0 : (int) vevent2GetType(e) - vevent2TYPE_NEXT_APPLICATION_TYPE)
#define veventSetClientType(e, t) \
        (vevent2SetType(e, (vevent2Type)(t+vevent2TYPE_NEXT_APPLICATION_TYPE)))
#define veventGetClientData(e) \
        veventGetData(e)
#define veventSetClientData(e, d) \
        veventSetData(e, d)
#define veventCreateApplication() \
        veventCreateClient()
#define veventGetApplicationType(e) \
        veventGetClientType(e)
#define veventGetApplicationData(e) \
        veventGetClientData(e)
#define veventSetApplicationType(e, t) \
        veventSetClientType(e, t)
#define veventSetApplicationData(e, t) \
        veventSetClientData(e, t)
#define veventGetWindow(e) \
        (_veventAsWindowEvent(e)->pWindow)
#define veventSetWindow(e, w) \
        (_veventAsWindowEvent(e)->pWindow = (w))
#define veventCreateWindowConfigure() \
        _vevent2bcSetBC(vevent2WindowConfigureEventAsEvent \
                        (vevent2WindowConfigureEventCreate()), \
                        veventWINDOW_CONFIGURE)
#define veventIsMove(e) \
        (vinstanceIsKindOf(_veventAsInstance(e), \
                           vevent2WindowConfigureEventClassGetDefault()))
#define veventIsSize(e) \
        (vinstanceIsKindOf(_veventAsInstance(e), \
                           vevent2WindowConfigureEventClassGetDefault()))
#define veventIsStack(e) \
        (vinstanceIsKindOf(_veventAsInstance(e), \
                           vevent2WindowConfigureEventClassGetDefault()) && \
         _veventAsWindowConfigureEvent(e)->pAbove != NULL)
#define veventGetConfigureX(e) \
        (_veventAsWindowConfigureEvent(e)->rect.x)
#define veventGetConfigureY(e) \
        (_veventAsWindowConfigureEvent(e)->rect.y)
#define veventGetConfigureWidth(e) \
        (_veventAsWindowConfigureEvent(e)->rect.w)
#define veventGetConfigureHeight(e) \
        (_veventAsWindowConfigureEvent(e)->rect.h)
#define veventGetConfigureFlags(e) \
        ((veventIsStack(e) ? veventWINDOW_CONFIGURE_STACK : 0) | \
         veventWINDOW_CONFIGURE_MOVE | veventWINDOW_CONFIGURE_SIZE)
#define veventSetConfigureX(e, _x) \
        (_veventAsWindowConfigureEvent(e)->rect.x = (_x))
#define veventSetConfigureY(e, _y) \
        (_veventAsWindowConfigureEvent(e)->rect.y = (_y))
#define veventSetConfigureWidth(e, _w) \
        (_veventAsWindowConfigureEvent(e)->rect.w = (_w))
#define veventSetConfigureHeight(e, _h) \
        (_veventAsWindowConfigureEvent(e)->rect.h = (_h))
#define veventSetConfigureFlags(e, f)
#define veventCreateFocusAcquire() \
        _vevent2bcSetBC(vevent2FocusAcquireEventAsEvent \
                        (vevent2FocusAcquireEventCreate()), \
                        veventFOCUS_ACQUIRE)
#define veventCreateFocusLose() \
        _vevent2bcSetBC(vevent2FocusLoseEventAsEvent \
                        (vevent2FocusLoseEventCreate()), \
                        veventFOCUS_LOSE)
#define veventGetPointerX(e) \
        veventGetX(e)
#define veventGetPointerY(e) \
        veventGetY(e)
#define veventSetPointerX(e, x) \
        veventSetX(e, x)
#define veventSetPointerY(e, y) \
        veventSetY(e, y)
#define veventIsPointerModifierOn(e, m) \
        (_veventAsPointerEvent(e)->modifiers & (m))
#define veventSetPointerModifierOn(e, m) \
        (_veventAsPointerEvent(e)->modifiers |= (m))
#define veventSetPointerModifierOff(e, m) \
        (_veventAsPointerEvent(e)->modifiers &= ~(m))
#define veventGetPointerModifiers(e) \
        (_veventAsPointerEvent(e)->modifiers)
#define veventSetPointerModifiers(e, m) \
        (_veventAsPointerEvent(e)->modifiers = (m))
#define veventGetPointerClickCount(e) \
        (_veventAsPointerEvent(e)->clicks)
#define veventSetPointerClickCount(e, c) \
        (_veventAsPointerEvent(e)->clicks = (c))
#define veventGetPointerButton(e) \
        (_veventAsButtonEvent(e)->button)
#define veventSetPointerButton(e, b) \
        (_veventAsButtonEvent(e)->button = (vevent2Button) (b))
#define veventGetKey(e) \
        (_veventAsKeyEvent(e)->key)
#define veventSetKey(e, k) \
        (_veventAsKeyEvent(e)->key = (k))
#define veventGetKeyStroke(e) \
        (vkeyComputeStroke(_veventAsKeyEvent(e)->key, \
                           veventGetPointerModifiers(e)))
#define veventSetKeyStroke(e, s) \
        (_veventAsKeyEvent(e)->key = vkeyGetStrokeKey(s), \
         veventSetPointerModifiers(e, vkeyGetStrokeModifiers(s)))
#define veventGetKeyChar(e) \
        (_veventAsKeyEvent(e)->keychar)
#define veventSetKeyChar(e, c) \
        (_veventAsKeyEvent(e)->keychar = (c))
#define veventGetKeyCode(e) \
        (_veventAsKeyEvent(e)->keycode)
#define veventSetKeyCode(e, kc) \
        (_veventAsKeyEvent(e)->keycode = (kc))
#define veventGetKeyX(e) \
        veventGetX(e)
#define veventGetKeyY(e) \
        veventGetY(e)
#define veventSetKeyX(e, x) \
        veventSetX(e, x)
#define veventSetKeyY(e, y) \
        veventSetY(e, y)
#define veventSetKeyModifierOn(e, m) \
        (veventSetPointerModifierOn(e, m))
#define veventSetKeyModifierOff(e, m) \
        (veventSetPointerModifierOff(e, m))
#define veventGetKeyModifiers(e) \
        (veventGetPointerModifiers(e))
#define veventIsKeyModifierOn(e, m) \
        (veventIsPointerModifierOn(e, m))
#define veventSetKeyModifiers(e, m) \
        (veventSetPointerModifiers(e,m))
#define veventCreateKeyDown() \
        _vevent2bcSetBC(vevent2KeyDownEventAsEvent \
                        (vevent2KeyDownEventCreate()), veventKEY_DOWN)
#define veventCreateKeyUp() \
        _vevent2bcSetBC(vevent2KeyUpEventAsEvent(vevent2KeyUpEventCreate()), \
                        veventKEY_UP)
#define veventCreateButtonDown() \
        _vevent2bcSetBC(vevent2ButtonDownEventAsEvent \
                        (vevent2ButtonDownEventCreate()), veventBUTTON_DOWN)
#define veventCreateButtonUp() \
        _vevent2bcSetBC(vevent2ButtonUpEventAsEvent \
                        (vevent2ButtonUpEventCreate()), veventBUTTON_UP)
#define veventCreatePointerDrag() \
        _vevent2bcSetBC(vevent2MotionEventAsEvent \
                        (vevent2MotionEventCreate()), veventPOINTER_DRAG)
#define veventCreatePointerDetail() \
        _vevent2bcSetBC(vevent2MotionEventAsEvent \
                        (vevent2MotionEventCreate()), \
                        veventPOINTER_DETAIL)
#define veventCreatePointerMotion() \
        _vevent2bcSetBC(vevent2MotionEventAsEvent \
                        (vevent2MotionEventCreate()), \
                        veventPOINTER_MOTION)
#define veventCreatePointerEnter() \
        _vevent2bcSetBC(vevent2PointerEnterEventAsEvent \
                        (vevent2PointerEnterEventCreate()), \
                        veventPOINTER_ENTER)
#define veventCreatePointerLeave() \
        _vevent2bcSetBC(vevent2PointerLeaveEventAsEvent \
                        (vevent2PointerLeaveEventCreate()), \
                        veventPOINTER_LEAVE)
#define veventCreateWindowState() \
        _vevent2bcSetBC(vevent2WindowStateEventAsEvent \
                        (vevent2WindowStateEventCreate()), \
                        veventWINDOW_STATE)
#define veventIsOpen(e) \
        (vevent2GetType(e) == vevent2TYPE_WINDOW_OPENED)
#define veventIsClose(e) \
        (vevent2GetType(e) == vevent2TYPE_WINDOW_CLOSED)
#define veventIsIconify(e) \
        (vevent2GetType(e) == vevent2TYPE_WINDOW_ICONIFIED)
#define veventIsUniconify(e) \
        (vevent2GetType(e) == vevent2TYPE_WINDOW_UNICONIFIED)
#define veventIsMaximize(e) \
        (vevent2GetType(e) == vevent2TYPE_WINDOW_MAXIMIZED)
#define veventIsUnmaximize(e) \
        (vevent2GetType(e) == vevent2TYPE_WINDOW_UNMAXIMIZED)
#define veventIsPin(e) \
        (vevent2GetType(e) == vevent2TYPE_WINDOW_PINNED)
#define veventIsUnpin(e) \
        (vevent2GetType(e) == vevent2TYPE_WINDOW_UNPINNED)
#define veventGetWindowStateType(e) \
        vevent2GetType(e)
#define veventSetWindowStateType(e, t) \
        vevent2SetType(e, (vevent2Type)(t))
#define veventCreateWindowUpdate() \
        _vevent2bcSetBC(vevent2WindowUpdateEventAsEvent \
                        (vevent2WindowUpdateEventCreate()), \
                        veventWINDOW_UPDATE)
#define veventGetDoubleClickInterval() \
        _vevent2bcDoubleClickNanoseconds
#define veventSetDoubleClickInterval(i) \
        (_vevent2bcDoubleClickNanoseconds = (i))


/*
 * * * * * * * * * * PRIVATE function message definitions * * * * * * * * * *
 */

vportEND_CPLUSPLUS_EXTERN_C

#endif /* #ifndef veventINCLUDED */


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


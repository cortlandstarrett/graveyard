/* $Id: vdrag.h,v 1.35 1997/10/20 22:26:23 bill Exp $ */

/*
 * vdrag.h
 *
 * Drag Manager Header File
 *
 * Copyright (C) 1996 Visix Software, Inc.
 * All rights reserved
 */

#ifndef vdragINCLUDED
#define vdragINCLUDED 1

#ifndef  vportINCLUDED
#include <vport.h>
#endif

#ifndef vrectINCLUDED
#include vrectHEADER
#endif

#ifndef vdictINCLUDED
#include vdictHEADER
#endif

#ifndef  vmutexINCLUDED
#include vmutexHEADER
#endif

#ifndef veventINCLUDED
#include veventHEADER
#endif

#ifndef vclassINCLUDED
#include vclassHEADER
#endif

#ifndef vclipboardINCLUDED
#include vclipboardHEADER
#endif

#ifndef vinstanceINCLUDED
#include vinstanceHEADER
#endif

#ifndef vimageINCLUDED
#include vimageHEADER
#endif

#ifndef vscrapINCLUDED
#include vscrapHEADER
#endif

#ifndef vcursorINCLUDED
#include vcursorHEADER
#endif

#ifndef vwindowINCLUDED
#include vwindowHEADER
#endif

#ifndef  vdropsiteINCLUDED
#include vdropsiteHEADER
#endif


vportBEGIN_CPLUSPLUS_EXTERN_C


/*
 * PUBLIC TYPE DECLARATION
 */

#if (!_vdragDefined)
typedef struct vdrag vdrag;
typedef struct vdragEngine vdragEngine;
#define _vdragDefined 1
#endif

typedef struct vdragClass vdragClass;

typedef struct vdragEngineClass vdragEngineClass;

typedef vdragEngine	vdragInternalEngine;

typedef struct vdragDropsiteIterator vdragDropsiteIterator;
typedef struct vdragDropsiteIteratorClass vdragDropsiteIteratorClass;

typedef void (*vdragActionProc)(vdrag *drag, int actionFlag, vevent *event);
typedef void (*vdragFeedbackProc)(vdrag *drag, int dropAction,
                                  vevent *event, vrect *drawRect);

/*
 * Deprecated Types
 */

typedef void (*vdragDrawProc)(vdrag *drag, vrect *drawRect);
typedef void (*vdragNotifyProc)(vdrag *drag, vwindow *from, vwindow *to,
                                vevent *event);
typedef int (*vdragDetailProc)(vdrag *drag, vwindow *from, vwindow *to,
                               vevent *event);

/*
 * PUBLIC CONSTANT DECLARATION
 */

enum {
  vdragDROP_ACTION_NONE             = 0x00000000,
  vdragDROP_ACTION_MOVE             = 0x00000001,
  vdragDROP_ACTION_COPY             = 0x00000002,
  vdragDROP_ACTION_LINK             = 0x00000004,
  vdragDROP_ACTION_ABORT            = 0x00000008
};

enum {
  vdragACTION_NONE,                  
  vdragACTION_START,
  vdragACTION_DROP,                  
  vdragACTION_CHANGE_DRAG_STATE,
  vdragACTION_ABORT
};

/*
 * PUBLIC FUNCTION DECLARATION
 */

void vdragStartup(
    void
    );

/*
 * Drag Class Functions
 */

vdragClass *vdragGetDefaultClass(
    void
    );

vdrag *vdragCreateOfClass(
    vdragClass          *drag
    );

vdrag *vdragCreate(
    void 
    );

vinstance *vdragGetInstance(
    vdrag               *drag
    );

vdragClass *vdragGetClass(
    vdrag               *drag
    );

void vdragInitOfClass(
    vdrag               *drag,
    vdragClass          *clas
    );

void vdragInit(
    vdrag               *drag
    );

/*
 * Function Interface to Drag Methods
 */

void vdragDestroy(
    vdrag               *drag
    );

void vdragSetActionNotify(
    vdrag               *drag,
    vdragActionProc      notify
    );

void vdragSetData(
    vdrag               *drag,
    const void          *data
    );

void vdragSetEngine(
    vdrag               *drag,
    vdragEngine         *engine
    );

void vdragSetFeedbackNotify(
    vdrag               *drag,
    vdragFeedbackProc    notify
    );

void vdragSetMaxSize( 
    vdrag               *drag,
    int                  width,
    int                  height 
    );

void vdragSetNativeFeedback(
    vdrag               *drag,
    vbool                flag                    
    );

void vdragSetOffset(
    vdrag               *drag,
    int                  x,
    int                  y
    );

void vdragSetScrap(
    vdrag               *drag,
    vscrap              *scrap
    );

void vdragSetValidDropActions(
    vdrag               *drag,
    unsigned long        actionFlags
    );

void vdragSetUserUndraw(
    vdrag               *drag,
    vbool                flag
    );

void vdragNotifyAction(
    vdrag               *drag,
    int                  dragAction,
    vevent              *event
    );

void vdragNotifyFeedback(
    vdrag               *drag,
    int                  dragAction,
    vevent              *event,
    vrect               *drawRect
    );

void vdragNotifyFeedbackWith(
    vdrag               *drag,
    int                  dragAction,
    vevent              *event,
    vrect               *drawRect,
    vdrawcontext        *context
    );

/*
 * Drag Convenience Functions
 */

void vdragDestroyLater(
    vdrag               *drag
    );

void vdragStart( 
    vdrag               *drag,
    vevent              *event 
    );

void vdragStop(
    vdrag               *drag
    );

vdragEngine *vdragGetEngine(
    vdrag               *drag
    );

int vdragGetMaxWidth(
    vdrag               *drag
    );

int vdragGetMaxHeight(
    vdrag               *drag
    );

int vdragGetOffsetX(
    vdrag               *drag
    );

int vdragGetOffsetY(
    vdrag               *drag
    );

void *vdragGetData(
    vdrag               *drag
    );

unsigned long vdragGetValidDropActions(
    vdrag               *drag
    );

const vrect *vdragGetLastRect(
    vdrag               *drag
    );

int vdragGetLastFeedback(
    vdrag               *drag
    );

vbool vdragGetNativeFeedback(
    vdrag               *drag
    );

vbool vdragHasUserUndraw(
    vdrag               *drag
    );

void vdragSetFeedbackCursor(
    vdrag               *drag,
    vwindow             *to,
    vcursor             *cursor
    );

/*
 * Drag Engine Class Functions
 */

vdragEngine *vdragCreateInternalEngine(
    void
    );

vdragEngine *vdragCreateEngineOfClass(
    vdragEngineClass    *clas
    );

vdragEngine *vdragGetInternalEngine(
    void
    );

vdragEngineClass *vdragGetDefaultInternalEngineClass(
    void
    );

vdragEngineClass *vdragGetDefaultEngineClass(
    void
    ); 

vdragEngineClass *vdragGetEngineClass(
    vdragEngine         *engine
    );

void vdragInitEngine(
    vdragEngine         *engine
    );

void vdragInitEngineOfClass(
    vdragEngine         *engine,
    vdragEngineClass    *clas
    );

void vdragDestroyEngine(
    vdragEngine         *engine
    );

vinstance *vdragGetEngineInstance(
    vdragEngine         *engine
    );

void vdragAbortEngineDrag(
    vdragEngine         *engine
    );

void vdragCleanUpEngineDrag(
    vdragEngine         *engine
    );

void vdragConvertEngineDragScrap(
    vdragEngine         *engine,
    vdrag               *drag,
    vscrap              *scrap
    );

vbool vdragEngineDragIntersectsDropsite(
    vdragEngine         *engine,
    vdropsite           *dropsite,
    vevent              *event
    );

vdict *vdragGetEngineDragEncodings(
    vdragEngine         *engine,
    vdrag               *drag
    );

vdrag *vdragGetEngineCurrentDrag(
    vdragEngine         *engine
    );

vdropsite *vdragGetEngineCurrentDropsite(
    vdragEngine         *engine
    );

void vdragLockEngine(
    vdragEngine         *engine
    );

void vdragUnlockEngine(
    vdragEngine         *engine
    );

void vdragLockEngineWithHandling(
    vdragEngine         *engine
    );

void vdragUnlockEngineWithHandling(
    vdragEngine         *engine
    );

int vdragProcessEngineDrag(
    vdragEngine         *engine,
    vdrag               *drag,
    vevent              *event
    );

void vdragRegisterEngineDropsite(
    vdragEngine         *engine,
    vdropsite           *dropsite
    );

void vdragUnregisterEngineDropsite(
    vdragEngine         *engine,
    vdropsite           *dropsite
    );

void vdragSetEngineClipboardEngine(
    vdragEngine         *engine,
    vclipboardEngine    *clipboardEngine
    );

void vdragSetUpEngineDrag(
    vdragEngine         *engine,
    vdrag               *drag,
    vevent              *event
    );

/*
 * Engine Dropsite Iterator Class Functions
 */

vdragDropsiteIteratorClass *vdragGetDefaultDropsiteIteratorClass(
    void
    );

void vdragInitEngineDropsiteIterator(
    vdragEngine           *engine,
    vwindow               *window,
    vdragDropsiteIterator *iterator
    );
    
void vdragDestroyDropsiteIterator(
    vdragDropsiteIterator *iterator
    );

vbool vdragNextDropsiteIterator(
    vdragDropsiteIterator *iterator
    );

vdropsite *vdragGetDropsiteIteratorDropsite(
    vdragDropsiteIterator *iterator
    );

/*
 * Deprecated Drag Functions
 */

void vdragSetNotify( 
    vdrag               *drag,
    vdragNotifyProc      notify
    );

void vdragSetDetail( 
    vdrag               *drag,
    vdragDetailProc      notify
    );

vdragDetailProc vdragGetDetail(
    vdrag               *drag
    );

vdragNotifyProc vdragGetNotify(
    vdrag               *drag
    );

void vdragSetDrawProc(
    vdrag               *drag,
    vdragDrawProc        draw
    );

vdragDrawProc vdragGetDrawProc(
    vdrag               *drag
    );


/*
 * CLASS DECLARATION
 */

#define vdragCLASS(SUPER, DRAG)                                               \
    vinstanceCLASS(SUPER, DRAG);                                              \
    vclassMETHOD(vdragSET_ENGINE, (DRAG *drag, vdragEngine *engine));         \
    vclassMETHOD(vdragSET_VALID_DROP_ACTIONS,                                 \
                 (DRAG *drag, unsigned long actionFlags));                    \
    vclassMETHOD(vdragSET_USER_UNDRAW,                                        \
                 (DRAG *drag, vbool flag));                                   \
    vclassMETHOD(vdragSET_ACTION_NOTIFY,                                      \
                 (DRAG *drag, vdragActionProc notify));                       \
    vclassMETHOD(vdragSET_FEEDBACK_NOTIFY,                                    \
                 (DRAG *drag, vdragFeedbackProc notify));                     \
    vclassMETHOD(vdragSET_DATA, (DRAG *drag, const void *data));              \
    vclassMETHOD(vdragSET_SCRAP, (DRAG *drag, vscrap *scrap));                \
    vclassMETHOD(vdragSET_MAX_SIZE, (DRAG *drag, int w, int h));              \
    vclassMETHOD(vdragSET_OFFSET, (DRAG *drag, int x, int y));                \
    vclassMETHOD(vdragSET_NATIVE_FEEDBACK, (DRAG *drag, vbool flag));         \
    vclassMETHOD(vdragNOTIFY_ACTION,                                          \
                 (DRAG *drag, int dragAction, vevent *event));                \
    vclassMETHOD(vdragNOTIFY_FEEDBACK,                                        \
                 (DRAG *drag, int dropAction, vevent *event,vrect *drawRect));\
    vclassMETHOD(vdragNOTIFY_FEEDBACK_WITH,                                   \
                 (DRAG *drag, int dropAction, vevent *event,                  \
                  vrect *drawRect, vdrawcontext *context))


#define vdragEngineCLASS(SUPER, ENGINE)                                       \
    vinstanceCLASS(SUPER, ENGINE);                                            \
    vclassMETHOD(vdragSET_ENGINE_CLIPBOARD_ENGINE,                            \
                 (ENGINE *engine, vclipboardEngine *clipboardEngine));        \
    vclassMETHOD(vdragREGISTER_ENGINE_DROPSITE,                               \
                 (ENGINE *engine, vdropsite *site));                          \
    vclassMETHOD(vdragUNREGISTER_ENGINE_DROPSITE,                             \
                 (ENGINE *engine, vdropsite *site));                          \
    vclassMETHOD(vdragSETUP_ENGINE_DRAG,                                      \
                 (ENGINE *engine, vdrag *drag, vevent *event));               \
    vclassMETHOD_RET(vdragPROCESS_ENGINE_DRAG, int,                           \
                 (ENGINE *engine, vdrag *drag, vevent *event));               \
    vclassMETHOD_RET(vdragENGINE_DRAG_INTERSECTS_DROPSITE, vbool,             \
                     (ENGINE *engine, vdropsite *dropsite, vevent *event));   \
    vclassMETHOD(vdragCLEANUP_ENGINE_DRAG,                                    \
                 (ENGINE *engine));                                           \
    vclassMETHOD(vdragABORT_ENGINE_DRAG,                                      \
                 (ENGINE *engine));                                           \
    vclassMETHOD_RET(vdragGET_ENGINE_DRAG_ENCODINGS, vdict *,                 \
                     (ENGINE *engine, vdrag *drag));                          \
    vclassMETHOD(vdragCONVERT_ENGINE_DRAG_SCRAP,                              \
                 (ENGINE *engine, vdrag *drag, vscrap *scrap))
    
/*
 * PRIVATE TYPE DECLARATIONS 
 */

struct vdrag {
  vinstance super;
  vdragEngine *engine;
  unsigned long validDropActions;
  const void *data;
  unsigned int offsetX, offsetY;
  unsigned int maxW, maxH;
  vdragActionProc actionNotify;
  vdragFeedbackProc feedbackNotify;
  vdragDrawProc drawProc;
  vdragDetailProc detailProc;
  vdragNotifyProc notifyProc;
  vscrap *scrap;
  unsigned int flags;
  vrect lastRect;
  int lastFeedback;
  vwindow *fromWindow;
  vwindow *lastToWindow;
};

struct vdragClass {
  vdragCLASS(vdragClass, vdrag);
};

typedef struct _vdragDropsiteInfo _vdragDropsiteInfo;

struct vdragEngine {
  vinstance super;
  vclipboardEngine *clipboardEngine;
  _vdragDropsiteInfo *dropsites;
  vdrag *currentDrag;
  vdropsite *currentDropsite;
  vbool dragRejected;
  vimage *root;
  vimage *offScreen;
  vimage *drawScreen;
  int dropResult;
  veventHandlerProc appDragHandler;
  veventHandlerProc appButtonDownHandler;
  veventHandlerProc appButtonUpHandler;
  veventHandlerProc appDetailHandler;
  veventHandlerProc appKeyUpHandler;
  veventHandlerProc appKeyDownHandler;
  _veventLoop *loop;
  vevent *stopEvent;
  vmutex mutex;
};

struct vdragEngineClass {
  vdragEngineCLASS(vdragEngineClass, vdragEngine);
};

vportALIAS(vdragInternalEngine, vdragEngine)

struct vdragDropsiteIterator {
  viterator super;
  vdragEngine *engine;
  vwindow *window;
  vdictIterator iter;
  vdropsite **scan;
  vdropsite **stop;
};

struct vdragDropsiteIteratorClass {
  viteratorCLASS(vdragDropsiteIteratorClass, vdragDropsiteIterator);
};

/*
 * PRIVATE CONSTANT DECLARATION
 */

/*
 * FUNCTIONS IMPLEMENTED AS MACROS
 */

#define vdragGetInstance(d)                                                   \
  (vportBASE_OBJECT(d, super))

#define vdragGetClass(d)                                                      \
  ((vdragClass *) vinstanceGetClass(vdragGetInstance((d))))

#define vdragInitOfClass(d, cls)                                              \
    vinstanceInitOfClass(vdragGetInstance(d), (vinstanceClass*)(cls))

#define vdragCreateOfClass(cls)                                               \
    ((vdrag *) vinstanceCreateOfClass((vinstanceClass*)(cls)))

#define vdragInit(d)                                                          \
    vdragInitOfClass(d, vdragGetDefaultClass())

#define vdragCreate()                                                         \
    vdragCreateOfClass(vdragGetDefaultClass())

#define vdragDestroy(d)                                                       \
    vinstanceDestroy(vdragGetInstance(d))

#define vdragGetEngineInstance(e)                                             \
     (vportBASE_OBJECT(e, super))

#define vdragGetEngineClass(e)                                                \
     ((vdragEngineClass *)vinstanceGetClass(vdragGetEngineInstance((e))))

#define vdragInitEngineOfClass(e, c)                                          \
     vinstanceInitOfClass(vdragGetEngineInstance((e)), (vinstanceClass *)(c))

#define vdragCreateEngineOfClass(c)                                           \
     ((vdragEngine *)vinstanceCreateOfClass((vinstanceClass *)(c)))

#define vdragInitEngine(e)                                                    \
     vdragInitEngineOfClass(e, vdragGetDefaultEngineClass())

#define vdragCreateInternalEngine()                                           \
     vdragCreateEngineOfClass(vdragGetDefaultInternalEngineClass())

#define vdragDestroyEngine(e)                                                 \
     vinstanceDestroy(vdragGetEngineInstance((e)))

#define vdragLockEngineWithHandling(e)                                        \
     vmutexLockWithHandling(&((e)->mutex));
    
#define vdragUnlockEngineWithHandling(e)                                      \
     vmutexUnlockWithHandling(&((e)->mutex));
    
#define vdragLockEngine(e)                                                    \
     vmutexLock(&((e)->mutex));

#define vdragUnlockEngine(e)                                                  \
     vmutexUnlock(&((e)->mutex));

#define vdragGetDetail(d)  ((d)->detailProc)

#define vdragGetNotify(d)  ((d)->notifyProc)

#define vdragGetDrawProc(d) ((d)->drawProc)

#define vdragGetValidDropActions(d) ((d)->validDropActions)

#define vdragGetLastRect(d) ((const vrect*)&((d)->lastRect))

#define vdragGetLastFeedback(d) ((d)->lastFeedback)

#define vdragGetEngineCurrentDrag(e) ((e)->currentDrag)

#define vdragGetEngineCurrentDropsite(e) ((e)->currentDropsite)

#define vdragGetEngine(d) ((d)->engine)

#define vdragGetOffsetX(d) ((d)->offsetX)

#define vdragGetOffsetY(d) ((d)->offsetY)

#define vdragGetMaxHeight(d) ((d)->maxH)

#define vdragGetMaxWidth(d) ((d)->maxW)

#define vdragGetData(d) ((void *) (d)->data)

#define _vdragGetDropsiteIteratorIterator(i) vportBASE_OBJECT(i, super)

#define vdragGetDropsiteIteratorDropsite(i) (*((i)->scan))

#define vdragNextDropsiteIterator(i)                                          \
    viteratorNext(_vdragGetDropsiteIteratorIterator(i))

#define vdragDestroyDropsiteIterator(i)                                       \
    viteratorDestroy(_vdragGetDropsiteIteratorIterator(i))

/*
 * FUNCTIONS IMPLEMENTED AS METHODS
 */

#define vdragSetEngine(d,e)                                                   \
     vclassSend(vdragGetClass((d)),                                           \
                vdragSET_ENGINE, ((d),(e)))

#define vdragSetValidDropActions(d,f)                                         \
     vclassSend(vdragGetClass((d)),                                           \
                vdragSET_VALID_DROP_ACTIONS, ((d),(f)))

#define vdragSetUserUndraw(d,f)                                               \
     vclassSend(vdragGetClass((d)),                                           \
                vdragSET_USER_UNDRAW, ((d),(f)))

#define vdragSetActionNotify(d, n)                                            \
     vclassSend(vdragGetClass((d)),                                           \
                vdragSET_ACTION_NOTIFY, ((d),(n)))

#define vdragSetFeedbackNotify(d, n)                                          \
     vclassSend(vdragGetClass((d)),                                           \
                vdragSET_FEEDBACK_NOTIFY, ((d),(n)))

#define vdragSetData(d, v)                                                    \
     vclassSend(vdragGetClass((d)),                                           \
                vdragSET_DATA, ((d), (v)))

#define vdragSetScrap(d, s)                                                   \
     vclassSend(vdragGetClass((d)),                                           \
                vdragSET_SCRAP, ((d), (s)))

#define vdragSetMaxSize(d, w, h)                                              \
     vclassSend(vdragGetClass((d)),                                           \
                vdragSET_MAX_SIZE, ((d), (w), (h)))

#define vdragSetOffset(d, x, y)                                               \
     vclassSend(vdragGetClass((d)),                                           \
                vdragSET_OFFSET, ((d), (x), (y)));

#define vdragSetNativeFeedback(d, f)                                          \
     vclassSend(vdragGetClass((d)),                                           \
                vdragSET_NATIVE_FEEDBACK, ((d), (f)))

#define vdragNotifyAction(d, a, e)                                            \
     vclassSend(vdragGetClass((d)),                                           \
                vdragNOTIFY_ACTION, ((d), (a), (e)))

#define vdragNotifyFeedback(d, a, e, r)                                       \
     vclassSend(vdragGetClass((d)),                                           \
                vdragNOTIFY_FEEDBACK, ((d), (a), (e), (r)))

#define vdragNotifyFeedbackWith(d, a, e, r, c)                                \
     vclassSend(vdragGetClass((d)),                                           \
                vdragNOTIFY_FEEDBACK_WITH, ((d), (a), (e), (r), (c)))

#define vdragSetEngineClipboardEngine(e,c)                                    \
     vclassSend(vdragGetEngineClass((e)),                                     \
                vdragSET_ENGINE_CLIPBOARD_ENGINE, ((e),(c)))

#define vdragRegisterEngineDropsite(e,s)                                      \
     vclassSend(vdragGetEngineClass((e)),                                     \
                vdragREGISTER_ENGINE_DROPSITE, ((e),(s)))

#define vdragUnregisterEngineDropsite(e,s)                                    \
     vclassSend(vdragGetEngineClass((e)),                                     \
                vdragUNREGISTER_ENGINE_DROPSITE, ((e),(s)))

#define vdragSetUpEngineDrag(e,d,v)                                           \
     vclassSend(vdragGetEngineClass((e)),                                     \
                vdragSETUP_ENGINE_DRAG, ((e),(d),(v)))

#define vdragProcessEngineDrag(e,d,v)                                         \
     vclassSend(vdragGetEngineClass((e)),                                     \
                vdragPROCESS_ENGINE_DRAG, ((e),(d),(v)))

#define vdragEngineDragIntersectsDropsite(e,s,v)                              \
     vclassSend(vdragGetEngineClass((e)),                                     \
                vdragENGINE_DRAG_INTERSECTS_DROPSITE, ((e),(s),(v)))

#define vdragCleanUpEngineDrag(e)                                             \
     vclassSend(vdragGetEngineClass((e)),                                     \
                vdragCLEANUP_ENGINE_DRAG, ((e)))

#define vdragAbortEngineDrag(e)                                               \
     vclassSend(vdragGetEngineClass((e)),                                     \
                vdragABORT_ENGINE_DRAG, ((e)))

#define vdragGetEngineDragEncodings(e,d)                                      \
     vclassSend(vdragGetEngineClass((e)),                                     \
                vdragGET_ENGINE_DRAG_ENCODINGS, ((e),(d)))

#define vdragConvertEngineDragScrap(e,d,s)                                    \
     vclassSend(vdragGetEngineClass((e)),                                     \
                vdragCONVERT_ENGINE_DRAG_SCRAP, ((e),(d),(s)))

vportEND_CPLUSPLUS_EXTERN_C

#endif

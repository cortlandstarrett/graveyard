/* $Id: vwindow.h,v 1.149 1997/10/20 23:10:20 david Exp $ */

/************************************************************

    vwindow.h

    C Interface file for the Window Manager

    (c) Copyright Visix Software Inc.
    All rights reserved

************************************************************/

#ifndef vwindowINCLUDED
#define vwindowINCLUDED

#ifndef  vportINCLUDED
#include <vport.h>
#endif

#ifndef  vstdioINCLUDED
#include vstdioHEADER
#endif

#ifndef  vexINCLUDED
#include vexHEADER
#endif

#ifndef  vscribeINCLUDED
#include vscribeHEADER
#endif

#ifndef  vcharINCLUDED
#include vcharHEADER
#endif

#ifndef  vkeyINCLUDED
#include vkeyHEADER
#endif

#ifndef  vnameINCLUDED
#include vnameHEADER
#endif

#ifndef  vdictINCLUDED
#include vdictHEADER
#endif

#ifndef  vrectINCLUDED
#include vrectHEADER
#endif

#ifndef  vresourceINCLUDED
#include vresourceHEADER
#endif

#ifndef  vcolorINCLUDED
#include vcolorHEADER
#endif

#ifndef  vfontINCLUDED
#include vfontHEADER
#endif

#ifndef  vimageINCLUDED
#include vimageHEADER
#endif

#ifndef  vdrawINCLUDED
#include vdrawHEADER
#endif

#ifndef  vdrawcontextINCLUDED
#include vdrawcontextHEADER
#endif

#ifndef  vcursorINCLUDED
#include vcursorHEADER
#endif

#ifndef  vclassINCLUDED
#include vclassHEADER
#endif

#ifndef  vobjectINCLUDED
#include vobjectHEADER
#endif

#ifndef  vcommandINCLUDED
#include vcommandHEADER
#endif

#ifndef  vevent2INCLUDED
#include vevent2HEADER
#endif

#ifndef  veventINCLUDED
#include veventHEADER
#endif

#ifndef  vprintINCLUDED
#include vprintHEADER
#endif

#ifndef  vmutexINCLUDED
#include vmutexHEADER
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * * * * * * * * * * PUBLIC CONSTANT DEFINITIONS * * * * * * * * * *
 */

/*
 * windows
 */

enum {
    vwindowID_ATTRIBUTE_DATA        = vobjectNEXT_ID_ATTRIBUTE,
    vwindowID_ATTRIBUTE_TITLE,
    vwindowID_ATTRIBUTE_CURSOR,
    vwindowID_ATTRIBUTE_BLOCK_CURSOR,
    vwindowID_ATTRIBUTE_ICON,
    vwindowID_ATTRIBUTE_FONT,
    vwindowID_ATTRIBUTE_FOREGROUND,
    vwindowID_ATTRIBUTE_FOREGROUND_HILITE,
    vwindowID_ATTRIBUTE_BACKGROUND,
    vwindowID_ATTRIBUTE_BACKGROUND_HILITE,
    vwindowID_ATTRIBUTE_COLOR,
    vwindowID_ATTRIBUTE_LINE_WIDTH,
    vwindowID_ATTRIBUTE_RECT,
    vwindowID_ATTRIBUTE_MIN_SIZE,
    vwindowID_ATTRIBUTE_MAX_SIZE,
    vwindowNEXT_ID_ATTRIBUTE
};

enum {
    vwindowSELECT_CLOSE             = vobjectNEXT_SELECT,
    vwindowSELECT_PRINT,
    vwindowSELECT_HELP_MODE,
    vwindowSELECT_ABANDON,
    vwindowNEXT_SELECT
};

enum {
    vwindowSTYLE_BACKGROUND         = 0x0001,
    vwindowSTYLE_BORDER             = 0x0002,
    vwindowSTYLE_MOVABLE            = 0x0004,
    vwindowSTYLE_RESIZABLE          = 0x0008,
    vwindowSTYLE_ICONIFIABLE        = 0x0010,
    vwindowSTYLE_MAXIMIZABLE        = 0x0020,
    vwindowSTYLE_PINNABLE           = 0x0040,
    vwindowSTYLE_MAIN               = 0x0080,
    vwindowSTYLE_DOCUMENT           = 0x0100,
    vwindowSTYLE_CONFIRM            = 0x0200,
    vwindowSTYLE_UNCLOSABLE         = 0x0400,
    vwindowSTYLE_PALETTE            = 0x0800,
    vwindowSTYLE_SUBWINDOW          = 0x1000
};

enum {
    vwindowINVAL_OPAQUE             = 0x0001,
    vwindowINVAL_IMMEDIATE          = 0x0002,
    vwindowINVAL_UPDATE             = 0x0004,
    vwindowINVAL_DISABLE            = 0x0008,
    vwindowINVAL_NO_UPDATE          = 0x0010 
};

/*
 * deprecated windows
 */

enum {
    vwindowSTYLE_GLOBAL             = vwindowSTYLE_MAIN,
    vwindowSTYLE_CHILD              = vwindowSTYLE_DOCUMENT
};

/*
 * * * * * * * * * * PUBLIC TYPE DEFINITIONS * * * * * * * * * *
 */

typedef struct vwindow              vwindow;
typedef struct vwindowIterator      vwindowIterator;
typedef struct vwindowFollowerIterator vwindowFollowerIterator;
typedef struct vwindowClass         vwindowClass;

typedef vexArgException             vwindowNotOpenException;
typedef vexArgException             vwindowGrabException;

typedef vimage			    vwindowImage;
typedef vimage			    vwindowBufferImage;

typedef void (*vwindowNoteProc)(
    vwindow                        *window,
    vevent                         *event
    );

#ifndef  _vapplicationDEFINED_VAPPLICATION
typedef struct vapplication	 vapplication;
#define  _vapplicationDEFINED_VAPPLICATION (1)	/** circular dependency  **/
#endif

/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */

void vwindowStartup(void);


/*
 * windows
 */

void vwindowReadDefaultPrefs(
    void
    );

void vwindowReadPrefs(
    void
    );

void vwindowMapPrefs(
    void
    );

vwindowClass *vwindowGetDefaultClass(
    void
    );

vwindow *vwindowGetRoot(
    void
    );

vwindow *vwindowGetGrabInputWindow(
    void
    );

vwindow *vwindowGetPointerWindow(
    void
    );

vwindow *vwindowGetFocusWindow(
    void
    );

void vwindowGetResolution(
    double                         *x,
    double                         *y
    );

int vwindowIsMonochrome(
    void
    );

int vwindowGetFontDeviceID(
    void
    );

void vwindowInitIterator(
    vwindowIterator                *iterator
    );

int vwindowNextIterator(
    vwindowIterator                *iterator
    );

void vwindowDestroyIterator(
    vwindowIterator                *iterator
    );

vwindow *vwindowGetIteratorWindow(
    vwindowIterator                *iterator
    );

vwindow *vwindowCreateOfClass(
    vwindowClass                   *clas
    );

vwindow *vwindowCreate(
    void
    );

vwindow *vwindowClone( 
    vwindow                        *window
    );

void vwindowInitOfClass(
    vwindow                        *window,
    vwindowClass                   *clas
    );

void vwindowInit(
    vwindow                        *window
    );

void vwindowDestroy(
    vwindow                        *window
    );

void vwindowDestroyLater(
    vwindow                        *window
    );

void vwindowCopy(
    vwindow                        *window,
    vwindow                        *target
    );

void vwindowCopyInit(
    vwindow                        *window,
    vwindow                        *target
    );

vwindow *vwindowLoad(
    vresource                       resource
    );

void vwindowLoadInit(
    vwindow                        *window,
    vresource                       resource
    );

void vwindowStore(
    vwindow                        *window,
    vresource                       resource
    );

void vwindowSetAttribute(
    vwindow                        *window,
    const vname                    *attr,
    const void                     *value
    );

void vwindowSetAllAttributes(
    vwindow                        *window,
    vdict                          *attr2value
    );

const void *vwindowGetAttribute(
    vwindow                        *window,
    const vname                    *attr
    );

void vwindowGetAllAttributes(
    vwindow                        *window,
    vdict                          *attr2value
    );

void vwindowGetContextAttributes(
    vwindow                        *window,
    vdict                          *attr2value
    );

void vwindowChangedParentAttribute(
    vwindow                        *window,
    const vname                    *attr,
    vdict                          *context
    );

void vwindowChangedAttribute(
    vwindow                        *window,
    const vname                    *attr,
    vdict                          *context
    );

void vwindowChangedChildAttribute(
    vwindow                        *window,
    const vname                    *attr,
    vdict                          *context
    );

void vwindowChangedAttributeNone(
    vwindow                        *window,
    const vname                    *attr
    );

void vwindowChangedAttributeValue(
    vwindow                        *window,
    const vname                    *attr,
    const void                     *oldValue,
    const void                     *value
    );

void vwindowUpdateAttribute(
    vwindow                        *window,
    const vname                    *attr
    );

void vwindowUpdateAllAttributes(
    vwindow                        *window
    );

const void *vwindowAssociateAttribute(
    vwindow                        *window,
    const vname                    *attr,
    const vname                    *tag
    );

void vwindowAssociateAllAttributes(
    vwindow                        *window,
    const vname                    *tag,
    vdict                          *attr2value
    );

void vwindowPropagateChange(
    vwindow                        *window,
    const vname                    *attr,
    const vname                    *tag,
    const void                     *value
    );

void vwindowPropagateChangeDict(
    vwindow                        *window,
    const vname                    *attr,
    vdict                          *tag2value
    );

void vwindowPropagateChangeDictFromParent(
    vwindow                        *window,
    const vname                    *attr,
    vdict                          *tag2value
    );

void vwindowHelp(
    vwindow                        *window
    );

void vwindowDump(
    vwindow                        *window,
    FILE                           *stream
    );

void vwindowOpen(
    vwindow                        *window
    );

void vwindowClose(
    vwindow                        *window
    );

void vwindowIconify(
    vwindow                        *window
    );

void vwindowUniconify(
    vwindow                        *window
    );

void vwindowMaximize(
    vwindow                        *window
    );

void vwindowUnmaximize(
    vwindow                        *window
    );

void vwindowBlock(
    vwindow                        *window
    );

void vwindowUnblock(
    vwindow                        *window
    );

void vwindowPin(
    vwindow                        *window
    );

void vwindowUnpin(
    vwindow                        *window
    );

void vwindowLower(
    vwindow                        *window
    );

void vwindowRaise(
    vwindow                        *window
    );

void vwindowInvalRect(
    vwindow                        *window,
    const vrect                    *rect,
    int                             flags
    );

void vwindowInval(
    vwindow                        *window,
    int                             flags
    );

void vwindowScrollRect(
    vwindow                        *window,
    const vrect                    *rect,
    int                             dx,
    int                             dy,
    int                             flags
    );

void vwindowNotify(
    vwindow                        *window,
    vevent                         *event
    );

void vwindowMove(
    vwindow                        *window,
    int                             x,
    int                             y
    );

void vwindowResize(
    vwindow                        *window,
    int                             w,
    int                             h
    );

void vwindowPlaceRect(
    vwindow                        *window,
    const vrect                    *base,
    int                             modex,
    int                             modey
    );

void vwindowPlace(
    vwindow                        *window,
    vwindow                        *base,
    int                             modex,
    int                             modey
    );

void vwindowDraw(
    vwindow                        *window
    );

void vwindowDrawWith(
    vwindow                        *window,
    vdrawcontext                   *context
    );

void vwindowDrawDevice(
    vwindow                        *window
    );

vdrawcontext *vwindowCreateDrawcontext(
    vwindow                        *window
    );

void vwindowUpdateDevice(
    vwindow                        *window
    );

vimageClass *vwindowGetDefaultBufferImageClass(
    void
    );

vwindowBufferImage *vwindowCreateBufferImage(
    int                             w,
    int                             h
    );

vimageClass *vwindowGetDefaultImageClass(
    void
    );

vwindowImage *vwindowToImage(
    vwindow                        *window
    );

int vwindowHandleConfigure(
    vwindow                        *window,
    vevent                         *event
    );

int vwindowHandleState(
    vwindow                        *window,
    vevent                         *event
    );

int vwindowHandleUpdate(
    vwindow                        *window,
    vevent                         *event
    );

int vwindowHandleEnter(
    vwindow                        *window,
    vevent                         *event
    );

int vwindowHandleLeave(
    vwindow                        *window,
    vevent                         *event
    );

int vwindowHandleButtonDown(
    vwindow                        *window,
    vevent                         *event
    );

int vwindowHandleButtonUp(
    vwindow                        *window,
    vevent                         *event
    );

int vwindowHandleDrag(
    vwindow                        *window,
    vevent                         *event
    );

int vwindowHandleDetail(
    vwindow                        *window,
    vevent                         *event
    );

int vwindowHandleMotion(
    vwindow                        *window,
    vevent                         *event
    );

int vwindowHandleAcquire(
    vwindow                        *window,
    vevent                         *event
    );

int vwindowHandleLose(
    vwindow                        *window,
    vevent                         *event
    );

int vwindowHandleKeyDown(
    vwindow                        *window,
    vevent                         *event
    );

int vwindowHandleKeyUp(
    vwindow                        *window,
    vevent                         *event
    );

void vwindowGrabInput(
    vwindow                        *window
    );

void vwindowReleaseInput(
    vwindow                        *window
    );

void vwindowGrabScreen(
    void
    );

void vwindowReleaseScreen(
    void
    );

void vwindowWarpPointer(
    vwindow                        *window,
    int                             x,
    int                             y
    );

void vwindowWarpFocus(
    vwindow                        *window
    );

void vwindowGetPointer(
    vwindow                        *window,
    int                            *x,
    int                            *y
    );

void vwindowAddCursorRect(
    vwindow                        *window,
    vcursor                        *cursor,
    const vrect                    *rect
    );

void vwindowRemoveCursorRect(
    vwindow                        *window,
    vcursor                        *cursor,
    const vrect                    *rect
    );

void vwindowChangeCursorRect(
    vwindow                        *window,
    vcursor                        *cursor,
    const vrect                    *oldRect,
    const vrect                    *newRect
    );

void vwindowSetTag(
    vwindow                        *window,
    const vname                    *tag
    );

void vwindowSetNotify(
    vwindow                        *window,
    vwindowNoteProc	            noteProc
    );

void vwindowSetData(
    vwindow                        *window,
    const void                     *data
    );

void vwindowSetTitle(
    vwindow                        *window,
    const vchar                    *title
    );

void vwindowSetTitleScribed(
    vwindow                        *window,
    vscribe                        *scribe
    );

void vwindowSetCursor(
    vwindow                        *window,
    vcursor                        *cursor
    );

void vwindowSetCursorOwned(
    vwindow                        *window,
    vcursor                        *cursor
    );

void vwindowSetIcon(
    vwindow                        *window,
    vimage                         *icon
    );

void vwindowSetIconOwned(
    vwindow                        *window,
    vimage                         *icon
    );

void vwindowSetFont(
    vwindow                        *window,
    vfont                          *font
    );

void vwindowSetForeground(
    vwindow                        *window,
    vcolor                         *foreground
    );

void vwindowSetBackground(
    vwindow                        *window,
    vcolor                         *background
    );

void vwindowSetSpace(
    vwindow                        *window,
    vcommandSpace                  *space
    );

void vwindowSetSpaceOwned(
    vwindow                        *window,
    vcommandSpace                  *space
    );

void vwindowSetStyle(
    vwindow                        *window,
    int                             flags
    );

void vwindowAddStyle(
    vwindow                        *window,
    int                             flags
    );

void vwindowRemoveStyle(
    vwindow                        *window,
    int                             flags
    );

void vwindowSetPopup(
    vwindow                        *window,
    int                             flag
    );

void vwindowSetBackStore(
    vwindow                        *window,
    int                             flag
    );

void vwindowSetModal(
    vwindow                        *window,
    int                             flag
    );

void vwindowSetFocusable(
    vwindow                        *window,
    int                             flag
    );

void vwindowSetMotion(
    vwindow                        *window,
    int                             flag
    );

void vwindowSetRect(
    vwindow                        *window,
    const vrect                    *rect
    );

void vwindowSetMinSize(
    vwindow                        *window,
    int                             w,
    int                             h
    );

void vwindowSetMaxSize(
    vwindow                        *window,
    int                             w,
    int                             h
    );

void vwindowSetLeader(
    vwindow                        *window,
    vwindow                        *leader
    );

void vwindowSetApplication(
    vwindow                        *window,
    vapplication                   *application
    );

void vwindowSetHelpMode(
    vwindow                        *window,
    vbool			    onOff
    );

void vwindowSetOverrideCursor(
    vwindow                        *window,
    vcursor                        *cursor
    );

vobjectAttributed *vwindowGetObject(
    vwindow                        *window
    );

vwindowClass *vwindowGetClass(
    vwindow                        *window
    );

const vname *vwindowGetTag(
    vwindow                        *window
    );

vwindowNoteProc vwindowGetNotify(
    vwindow                        *window
    );

const void *vwindowGetData(
    vwindow                        *window
    );

const vchar *vwindowGetTitle(
    vwindow                        *window
    );

vcursor *vwindowGetCursor(
    vwindow                        *window
    );

vimage *vwindowGetIcon(
    vwindow                        *window
    );

vfont *vwindowGetFont(
    vwindow                        *window
    );

vcolor *vwindowGetForeground(
    vwindow                        *window
    );

vcolor *vwindowGetBackground(
    vwindow                        *window
    );

vcommandSpace *vwindowGetSpace(
    vwindow                        *window
    );

int vwindowGetStyle(
    vwindow                        *window
    );

vcursor *vwindowGetOverrideCursor(
    vwindow			   *window
    );

int vwindowIsPopup(
    vwindow                        *window
    );

int vwindowUsesBackStore(
    vwindow                        *window
    );

int vwindowIsModal(
    vwindow                        *window
    );

int vwindowIsFocusable(
    vwindow                        *window
    );

int vwindowUsesMotion(
    vwindow                        *window
    );

int vwindowIsOpen(
    vwindow                        *window
    );

int vwindowIsIconified(
    vwindow                        *window
    );

int vwindowIsMaximized(
    vwindow                        *window
    );

int vwindowIsBlocked(
    vwindow                        *window
    );

int vwindowIsPinned(
    vwindow                        *window
    );

int vwindowIsVisible(
    vwindow                        *window
    );

vbool vwindowIsInHelpMode(
    vwindow                        *window
    );

const vrect *vwindowGetRect(
    vwindow                        *window
    );

int vwindowGetX(
    vwindow                        *window
    );

int vwindowGetY(
    vwindow                        *window
    );

int vwindowGetW(
    vwindow                        *window
    );

int vwindowGetH(
    vwindow                        *window
    );

int vwindowGetMinW(
    vwindow                        *window
    );

int vwindowGetMinH(
    vwindow                        *window
    );

int vwindowGetMaxW(
    vwindow                        *window
    );

int vwindowGetMaxH(
    vwindow                        *window
    );

int vwindowHasKeyMap(
    vwindow                        *window
    );

int vwindowHasKeyDispatch(
    vwindow                        *window
    );

vdict *vwindowGetKeyMap(
    vwindow                        *window
    );

vdict *vwindowGetKeyDispatch(
    vwindow                        *window
    );

const vname *vwindowLoadKeyMap(
    vwindow                        *window,
    vkeyStroke                      key
    );

const void *vwindowLoadKeyDispatch(
    vwindow                        *window,
    vkeyStroke                      key
    );

vwindow *vwindowGetLeader(
    vwindow                        *window
    );

vapplication *vwindowGetApplication(
    vwindow                        *window
    );

void vwindowInitFollowerIterator(
    vwindowFollowerIterator        *iterator,
    vwindow                        *window
    );

int vwindowNextFollowerIterator(
    vwindowFollowerIterator        *iterator
    );

void vwindowDestroyFollowerIterator(
    vwindowFollowerIterator        *iterator
    );

vwindow *vwindowGetFollowerIteratorWindow(
    vwindowFollowerIterator        *iterator
    );

vcursor *vwindowDetermineCursor(
    vwindow                        *window
    );

vcursor *vwindowDetermineBlockCursor(
    vwindow                        *window
    );

vimage *vwindowDetermineIcon(
    vwindow                        *window
    );

vfont *vwindowDetermineFont(
    vwindow                        *window
    );

vcolor *vwindowDetermineForeground(
    vwindow                        *window
    );

vcolor *vwindowDetermineBackground(
    vwindow                        *window
    );

vcolor *vwindowDetermineColor(
    vwindow                        *window,
    int                             id
    );

void vwindowDetermineColorScheme(
    vwindow                        *window,
    unsigned long                   flags,
    vcolorScheme                   *scheme
    );

void vwindowDetermineColorSchemeFrom(
    vwindow                        *window,
    vcolorScheme                   *known,
    unsigned long                   flags,
    vcolorScheme                   *scheme
    );

void vwindowDetermineFrameSize(
    vwindow                        *window,
    int				   *top,
    int				   *left,
    int				   *bottom,
    int				   *right
    );

int vwindowComplementColors(
    vcolor                       ***colors,
    int                             groupCount,
    int                             colorCount
    );

int vwindowDetermineLineWidth(
    vwindow                        *window
    );

void vwindowTransformPoint(
    vwindow                        *window,
    vwindow                        *target,
    int                             x,
    int                             y,
    int                            *rx,
    int                            *ry
    );

void vwindowTransformRect(
    vwindow                        *window,
    vwindow                        *target,
    const vrect                    *rect,
    vrect                          *rrect
    );

void vwindowTransformEvent(
    vwindow                        *window,
    vwindow                        *target,
    vevent                         *event
    );

void vwindowFlushRequests(
    void
    );

void vwindowSyncEvents(
    void
    );

void vwindowBeep(
    void
    );

const vexClass *vwindowGetNotOpenExceptionClass(
    void
    );

const vexClass *vwindowGetGrabExceptionClass(
    void
    );

vwindowNotOpenException *vwindowGetNotOpenException(
    void
    );

vwindowGrabException *vwindowGetGrabException(
    void
    );

vbool vwindowDisplayHelp(
    vwindow                       *window,
    vhelprequest		  *request
    );

void vwindowLock(
    void
    );

void vwindowUnlock(
    void
    );

void vwindowLockWithHandling(
    void
    );

void vwindowUnlockWithHandling(
    void
    );

void vwindowPostEvent(
    vwindow                       *window,
    vevent                        *event
    );

void vwindowPostEventUnsafe(
    vwindow                       *window,
    vevent                        *event
    );

/*
 * deprecated windows
 */

void vwindowDetermineColors(
    vwindow                        *window,
    int                            *ids,
    int                             count,
    vcolor                        **colors
    );

void vwindowDetermineColorsFrom(
    vwindow                        *window,
    long                            flags,
    vcolor                        **known,
    int                            *ids,
    int                             count,
    vcolor                        **colors
    );

/*
 * * * * * * * * * * PRIVATE CONSTANT DEFINITIONS * * * * * * * * * *
 */

enum {
    _vwindowPOPUP                   = 0x0001,
    _vwindowBACK_STORE              = 0x0002,
    _vwindowMODAL                   = 0x0004,
    _vwindowFOCUSABLE               = 0x0008,
    _vwindowOPEN	            = 0x0010,
    _vwindowICONIFIED               = 0x0020,
    _vwindowMAXIMIZED               = 0x0040,
    _vwindowBLOCKED                 = 0x0080,
    _vwindowPINNED                  = 0x0100,
    _vwindowMOTION                  = 0x0200,
    _vwindowOWN_TITLE               = 0x0400,
    _vwindowOWN_CURSOR              = 0x0800,
    _vwindowOWN_ICON                = 0x1000,
    _vwindowOWN_SPACE               = 0x2000,
    _vwindowHELP_MODE		    = 0x4000
};

/*
 * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * *
 */

typedef struct _vwindowExtra        _vwindowExtra;
typedef struct _vwindowInfo         _vwindowInfo;

struct vwindow {
    vobjectAttributed               object;
    vwindowNoteProc	            noteProc;
    const void		           *data;
    const vchar                    *title;
    _vwindowExtra                  *extra;
    short                           style;
    unsigned short	            flags;
    vrect		            rect;
    vrect                           saveRect;
    short                           minW, minH;
    short                           maxW, maxH;
    vwindow                        *leader;
    vapplication                   *application;
    vcursor			   *oldCursor;
    _vwindowInfo                   *info;
    vevent2Loop			   *pLoop;
    vmutex		            mutex;
};

struct vwindowIterator {
    vwindow                       **scan;
};

struct vwindowFollowerIterator {
    vwindow                       **scan, **stop;
};

#define vwindowCLASS(SUPER, WINDOW, NOTIFY)                                   \
    vobjectATTRIBUTED_CLASS(SUPER, WINDOW);                                   \
    vclassVARIABLE(vwindowCURSOR, vcursor*);                                  \
    vclassVARIABLE(vwindowICON, vimage*);                                     \
    vclassVARIABLE(vwindowFONT, vfont*);                                      \
    vclassVARIABLE(vwindowFOREGROUND, vcolor*);                               \
    vclassVARIABLE(vwindowFOREGROUND_HILITE, vcolor*);                        \
    vclassVARIABLE(vwindowBACKGROUND, vcolor*);                               \
    vclassVARIABLE(vwindowBACKGROUND_HILITE, vcolor*);                        \
    vclassMETHOD(vwindowOPEN, (WINDOW *window));                              \
    vclassMETHOD(vwindowCLOSE, (WINDOW *window));                             \
    vclassMETHOD(vwindowICONIFY, (WINDOW *window));                           \
    vclassMETHOD(vwindowUNICONIFY, (WINDOW *window));                         \
    vclassMETHOD(vwindowMAXIMIZE, (WINDOW *window));                          \
    vclassMETHOD(vwindowUNMAXIMIZE, (WINDOW *window));                        \
    vclassMETHOD(vwindowBLOCK, (WINDOW *window));                             \
    vclassMETHOD(vwindowUNBLOCK, (WINDOW *window));                           \
    vclassMETHOD(vwindowPIN, (WINDOW *window));                               \
    vclassMETHOD(vwindowUNPIN, (WINDOW *window));                             \
    vclassMETHOD(vwindowLOWER, (WINDOW *window));                             \
    vclassMETHOD(vwindowRAISE, (WINDOW *window));                             \
    vclassMETHOD(vwindowINVAL_RECT,                                           \
		 (WINDOW *window, const vrect *rect, int flags));             \
    vclassMETHOD(vwindowSCROLL_RECT,                                          \
		 (WINDOW *window, const vrect *rect, int dx, int dy,          \
		  int flags));                                                \
    vclassMETHOD(vwindowNOTIFY, (WINDOW *window, vevent *event));             \
    vclassMETHOD(vwindowOBSERVE_WINDOW, (WINDOW *window, vevent *event));     \
    vclassMETHOD(vwindowPLACE_RECT,					      \
		 (WINDOW *window, const vrect *base, int modex, int modey));  \
    vclassMETHOD(vwindowPLACE,  					      \
		 (WINDOW *window, vwindow *base, int modex, int modey));      \
    vclassMETHOD(vwindowDRAW, (WINDOW *window));                              \
    vclassMETHOD(vwindowDRAW_WITH, (WINDOW *window, vdrawcontext *context));  \
    vclassMETHOD(vwindowDRAW_DEVICE, (WINDOW *window, int flags));            \
    vclassMETHOD_RET(vwindowCREATE_DRAWCONTEXT, vdrawcontext *,               \
		     (WINDOW *window));                                       \
    vclassMETHOD_RET(vwindowHANDLE_CONFIGURE, int,                            \
		     (WINDOW *window, vevent *event));                        \
    vclassMETHOD_RET(vwindowHANDLE_STATE, int,                                \
		     (WINDOW *window, vevent *event));                        \
    vclassMETHOD_RET(vwindowHANDLE_UPDATE, int,                               \
		     (WINDOW *window, vevent *event));                        \
    vclassMETHOD_RET(vwindowHANDLE_ENTER, int,                                \
		     (WINDOW *window, vevent *event));                        \
    vclassMETHOD_RET(vwindowHANDLE_LEAVE, int,                                \
		     (WINDOW *window, vevent *event));                        \
    vclassMETHOD_RET(vwindowHANDLE_BUTTON_DOWN, int,                          \
		     (WINDOW *window, vevent *event));                        \
    vclassMETHOD_RET(vwindowHANDLE_BUTTON_UP, int,                            \
		     (WINDOW *window, vevent *event));                        \
    vclassMETHOD_RET(vwindowHANDLE_DRAG, int,                                 \
		     (WINDOW *window, vevent *event));                        \
    vclassMETHOD_RET(vwindowHANDLE_DETAIL, int,                               \
		     (WINDOW *window, vevent *event));                        \
    vclassMETHOD_RET(vwindowHANDLE_MOTION, int,                               \
		     (WINDOW *window, vevent *event));                        \
    vclassMETHOD_RET(vwindowHANDLE_ACQUIRE, int,                              \
		     (WINDOW *window, vevent *event));                        \
    vclassMETHOD_RET(vwindowHANDLE_LOSE, int,                                 \
		     (WINDOW *window, vevent *event));                        \
    vclassMETHOD_RET(vwindowHANDLE_KEY_DOWN, int,                             \
		     (WINDOW *window, vevent *event));                        \
    vclassMETHOD_RET(vwindowHANDLE_KEY_UP, int,                               \
		     (WINDOW *window, vevent *event));                        \
    vclassMETHOD(vwindowSET_NOTIFY, (WINDOW *window, NOTIFY noteProc));       \
    vclassMETHOD(vwindowSET_DATA, (WINDOW *window, const void *data));        \
    vclassMETHOD(vwindowSET_TITLE_SCRIBED, (WINDOW *window, vscribe *scribe));\
    vclassMETHOD(vwindowSET_CURSOR, (WINDOW *window, vcursor *cursor));       \
    vclassMETHOD(vwindowSET_CURSOR_OWNED, (WINDOW *window, vcursor *cursor)); \
    vclassMETHOD(vwindowSET_ICON, (WINDOW *window, vimage *icon));            \
    vclassMETHOD(vwindowSET_ICON_OWNED, (WINDOW *window, vimage *icon));      \
    vclassMETHOD(vwindowSET_FONT, (WINDOW *window, vfont *font));             \
    vclassMETHOD(vwindowSET_FOREGROUND, (WINDOW *window, vcolor *foreground));\
    vclassMETHOD(vwindowSET_BACKGROUND, (WINDOW *window, vcolor *background));\
    vclassMETHOD(vwindowSET_SPACE, (WINDOW *window, vcommandSpace *space));   \
    vclassMETHOD(vwindowSET_SPACE_OWNED,                                      \
		 (WINDOW *window, vcommandSpace *space));                     \
    vclassMETHOD(vwindowSET_STYLE, (WINDOW *window, int flags));              \
    vclassMETHOD(vwindowSET_POPUP, (WINDOW *window, int flag));               \
    vclassMETHOD(vwindowSET_BACK_STORE, (WINDOW *window, int flag));          \
    vclassMETHOD(vwindowSET_MODAL, (WINDOW *window, int flag));               \
    vclassMETHOD(vwindowSET_FOCUSABLE, (WINDOW *window, int flag));           \
    vclassMETHOD(vwindowSET_MOTION, (WINDOW *window, int flag));              \
    vclassMETHOD(vwindowSET_RECT, (WINDOW *window, const vrect *rect));       \
    vclassMETHOD(vwindowSET_MIN_SIZE, (WINDOW *window, int w, int h));        \
    vclassMETHOD(vwindowSET_MAX_SIZE, (WINDOW *window, int w, int h));        \
    vclassMETHOD(vwindowSET_LEADER, (WINDOW *window, vwindow *leader));       \
    vclassMETHOD(vwindowSET_HELP_MODE, (WINDOW *window, vbool onOff));	      \
    vclassMETHOD(vwindowSET_APPLICATION,                                      \
		 (WINDOW *window, vapplication *application));                \
    vclassMETHOD(vwindowDETERMINE_COLOR_SCHEME_FROM,                          \
		 (WINDOW *window, vcolorScheme *known, unsigned long flags,   \
		  vcolorScheme *scheme));                                     \
    vclassMETHOD(vwindowDETERMINE_FRAME_SIZE,                                 \
		 (WINDOW *window, int *top, int *left, int *bottom,           \
		  int *right))

struct vwindowClass {
    vwindowCLASS(vwindowClass, vwindow, vwindowNoteProc);
};


vportALIAS(vwindowImage, vimage)

vportALIAS(vwindowBufferImage, vimage)

vportALIAS(vprintInteractive, vprint)

/*
 * * * * * * * * * * PRIVATE VARIABLE DECLARATIONS * * * * * * * * * *
 */

extern vportLINK vwindow                     *_vwindowGrabInputWindow;
extern vportLINK const vexClass               _vwindowNotOpenExceptionClass;
extern vportLINK const vexClass               _vwindowGrabExceptionClass;
extern vportLINK vmutex                       _vwindowMutex;


/*
 * * * * * * * * * * PRIVATE FUNCTION DECLARATIONS * * * * * * * * * *
 */

void _vwindowSetupWindowImage(vwindowImage *image, vwindow *window);

void _vwindowDrawUpdateDevice(vwindow *window, int flags);
vobjectPartialChildIteratorClass *_vwindowGetPartialChildIteratorClass(void);

void _vwindowSetClassFont(
    vobjectAttributedClass *clas,
    vfont *font
    );

/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * *
 */

/*
 * windows
 */

#define vwindowGetGrabInputWindow() (_vwindowGrabInputWindow) 

#define vwindowGetIteratorWindow(i) (*(i)->scan)

#define vwindowGetObject(w)         vportBASE_OBJECT(w, object)

#define vwindowCreateOfClass(c) \
    ((vwindow*)vobjectCreateOfClass((vobjectClass*)(c)))
#define vwindowCreate() \
    vwindowCreateOfClass(vwindowGetDefaultClass())
#define vwindowClone(w)           ((vwindow*)vobjectClone(vwindowGetObject(w)))
#define vwindowInitOfClass(w, c) \
    vobjectInitOfClass(vwindowGetObject(w), (vobjectClass*)(c))
#define vwindowInit(w) \
    vwindowInitOfClass(w, vwindowGetDefaultClass())
#define vwindowCopyInit(w, t) \
    vobjectCopyInit(vwindowGetObject(w), vwindowGetObject(t))
#define vwindowLoad(r)            ((vwindow*)vobjectLoad(r))
#define vwindowLoadInit(w, r)       vobjectLoadInit(vwindowGetObject(w), r)

#define vwindowChangedAttributeNone(w, n) \
    vobjectChangedAttributeNone(vwindowGetObject(w), n)
#define vwindowChangedAttributeValue(w, n, o, v) \
    vobjectChangedAttributeValue(vwindowGetObject(w), n, o, v)
#define vwindowAssociateAttribute(w, a, n) \
    vobjectAssociateAttribute(vwindowGetObject(w), a, n)
#define vwindowAssociateAllAttributes(w, n, d) \
    vobjectAssociateAllAttributes(vwindowGetObject(w), n, d)
#define vwindowPropagateChange(w, a, n, v) \
    vobjectPropagateChange(vwindowGetObject(w), a, n, v)
#define vwindowPropagateChangeDictFromParent(w, a, d) \
    vobjectPropagateChangeDictFromParent(vwindowGetObject(w), a, d)

#define vwindowSetTitle(w, s)       vwindowSetTitleScribed(w, vcharScribe(s))

#define vwindowGetClass(w) \
    ((vwindowClass*)vobjectGetAttributedClass(vwindowGetObject(w)))
#define vwindowGetTag(w)            vobjectGetTag(vwindowGetObject(w))
#define vwindowGetNotify(w)	  ((w)->noteProc)
#define vwindowGetData(w)	  ((w)->data)
#define vwindowGetTitle(w)	  ((w)->title)
#define vwindowGetStyle(w)        ((w)->style)
#define vwindowIsPopup(w)	 (((w)->flags&_vwindowPOPUP)     !=0)
#define vwindowUsesBackStore(w)  (((w)->flags&_vwindowBACK_STORE)!=0)
#define vwindowIsModal(w)	 (((w)->flags&_vwindowMODAL)     !=0)
#define vwindowIsFocusable(w)	 (((w)->flags&_vwindowFOCUSABLE) !=0)
#define vwindowUsesMotion(w)	 (((w)->flags&_vwindowMOTION)    !=0)
#define vwindowIsOpen(w)	 (((w)->flags&_vwindowOPEN)      !=0)
#define vwindowIsIconified(w)	 (((w)->flags&_vwindowICONIFIED) !=0)
#define vwindowIsMaximized(w)	 (((w)->flags&_vwindowMAXIMIZED) !=0)
#define vwindowIsBlocked(w)	 (((w)->flags&_vwindowBLOCKED)   !=0)
#define vwindowIsPinned(w)	 (((w)->flags&_vwindowPINNED)    !=0)
#define vwindowIsInHelpMode(w) \
    ((((w)->flags&_vwindowHELP_MODE) !=0)?vTRUE:vFALSE)
#define vwindowIsVisible(w) \
    (((w)->flags&(_vwindowOPEN|_vwindowICONIFIED))==_vwindowOPEN)
#define vwindowGetRect(w)	 ((const vrect*)&(w)->rect)
#define vwindowGetX(w)  	  ((w)->rect.x)
#define vwindowGetY(w)		  ((w)->rect.y)
#define vwindowGetW(p)		  ((p)->rect.w)
#define vwindowGetH(w)		  ((w)->rect.h)
#define vwindowGetMinW(w)	  ((w)->minW)
#define vwindowGetMinH(w)	  ((w)->minH)
#define vwindowGetMaxW(w)	  ((w)->maxW)
#define vwindowGetMaxH(w)	  ((w)->maxH)
#define vwindowGetLeader(w)	  ((w)->leader)
#define vwindowGetApplication(w)  ((w)->application)

#define vwindowDrawDevice(w) \
    _vwindowDrawUpdateDevice(w, 0)
#define vwindowUpdateDevice(w) \
    _vwindowDrawUpdateDevice(w, vdrawDEVICE_VIEW_CLIP)

#define vwindowNextFollowerIterator(i)     (--(i)->scan>=(i)->stop)
#define vwindowDestroyFollowerIterator(i)
#define vwindowGetFollowerIteratorWindow(i) (*(i)->scan)

#define vwindowDetermineForeground(w) \
    vwindowDetermineColor(w, vcolorID_FOREGROUND)
#define vwindowDetermineBackground(w) \
    vwindowDetermineColor(w, vcolorID_BACKGROUND)

#define vwindowGetNotOpenExceptionClass() (&_vwindowNotOpenExceptionClass)
#define vwindowGetGrabExceptionClass()    (&_vwindowGrabExceptionClass)
#define vwindowGetNotOpenException() \
    ((vwindowNotOpenException*) \
         vexGetExceptionOfClass(&_vwindowNotOpenExceptionClass))
#define vwindowGetGrabException() \
    ((vwindowGrabException*) \
         vexGetExceptionOfClass(&_vwindowGrabExceptionClass))
#define vwindowLock() vmutexLock(&_vwindowMutex)
#define vwindowUnlock() vmutexUnlock(&_vwindowMutex)
#define vwindowLockWithHandling() vmutexLockWithHandling(&_vwindowMutex)
#define vwindowUnlockWithHandling() vmutexUnlockWithHandling(&_vwindowMutex)
      
/*
 * deprecated windows
 */

#define vwindowDetermineColors(w, i, n, c) \
    vwindowDetermineColorsFrom(w, 0L, (vcolor**)NULL, i, n, c)

/*
 * * * * * * * * * * PRIVATE FUNCTION MESSAGE DEFINITIONS * * * * * * * * * *
 */

#define vwindowCopy(w, t) \
    vclassSend(vwindowGetClass(w), vobjectCOPY, (w, t))
#define vwindowStore(w, r) \
    vclassSend(vwindowGetClass(w), vobjectSTORE, (w, r))
#define vwindowSetAttribute(w, a, v) \
    vclassSend(vwindowGetClass(w), vobjectSET_ATTRIBUTE, (w, a, v))
#define vwindowSetAllAttributes(w, d) \
    vclassSend(vwindowGetClass(w), vobjectSET_ALL_ATTRIBUTES, (w, d))
#define vwindowGetAttribute(w, a) \
    vclassSend(vwindowGetClass(w), vobjectGET_ATTRIBUTE, (w, a))
#define vwindowGetAllAttributes(w, d) \
    vclassSend(vwindowGetClass(w), vobjectGET_ALL_ATTRIBUTES, (w, d))
#define vwindowGetContextAttributes(w, d) \
    vclassSend(vwindowGetClass(w), vobjectGET_CONTEXT_ATTRIBUTES, (w, d))
#define vwindowChangedParentAttribute(w, a, d) \
    vclassSend(vwindowGetClass(w), vobjectCHANGED_PARENT_ATTRIBUTE, (w, a, d))
#define vwindowChangedAttribute(w, a, d) \
    vclassSend(vwindowGetClass(w), vobjectCHANGED_ATTRIBUTE, (w, a, d))
#define vwindowChangedChildAttribute(w, a, d) \
    vclassSend(vwindowGetClass(w), vobjectCHANGED_CHILD_ATTRIBUTE, (w, a, d))
#define vwindowUpdateAttribute(w, a) \
    vclassSend(vwindowGetClass(w), vobjectUPDATE_ATTRIBUTE, (w, a))
#define vwindowUpdateAllAttributes(w) \
    vclassSend(vwindowGetClass(w), vobjectUPDATE_ALL_ATTRIBUTES, (w))
#define vwindowPropagateChangeDict(w, a, d) \
    vclassSend(vwindowGetClass(w), vobjectPROPAGATE_CHANGE_DICT, (w, a, d))
#define vwindowHelp(w) \
    vclassSend(vwindowGetClass(w), vobjectHELP, (w))
#define vwindowDisplayHelp(w, r) \
    vclassSend(vwindowGetClass(w), vobjectDISPLAY_HELP, (w, r))
#define vwindowDump(w, s) \
    vclassSend(vwindowGetClass(w), vobjectDUMP, (w, s))

#define vwindowOpen(w) \
    vclassSend(vwindowGetClass(w), vwindowOPEN, (w))
#define vwindowClose(w) \
    vclassSend(vwindowGetClass(w), vwindowCLOSE, (w))
#define vwindowCreateDrawcontext(w)                                            \
    vclassSend(vwindowGetClass(w), vwindowCREATE_DRAWCONTEXT, (w))
#define vwindowDrawWith(w,c)                                                   \
    vclassSend(vwindowGetClass(w), vwindowDRAW_WITH, (w,c))
#define vwindowIconify(w) \
    vclassSend(vwindowGetClass(w), vwindowICONIFY, (w))
#define vwindowUniconify(w) \
    vclassSend(vwindowGetClass(w), vwindowUNICONIFY, (w))
#define vwindowMaximize(w) \
    vclassSend(vwindowGetClass(w), vwindowMAXIMIZE, (w))
#define vwindowUnmaximize(w) \
    vclassSend(vwindowGetClass(w), vwindowUNMAXIMIZE, (w))
#define vwindowBlock(w) \
    vclassSend(vwindowGetClass(w), vwindowBLOCK, (w))
#define vwindowUnblock(w) \
    vclassSend(vwindowGetClass(w), vwindowUNBLOCK, (w))
#define vwindowPin(w) \
    vclassSend(vwindowGetClass(w), vwindowPIN, (w))
#define vwindowUnpin(w) \
    vclassSend(vwindowGetClass(w), vwindowUNPIN, (w))
#define vwindowLower(w) \
    vclassSend(vwindowGetClass(w), vwindowLOWER, (w))
#define vwindowRaise(w) \
    vclassSend(vwindowGetClass(w), vwindowRAISE, (w))
#define vwindowInvalRect(w, r, f) \
    vclassSend(vwindowGetClass(w), vwindowINVAL_RECT, (w, r, f))
#define vwindowScrollRect(w, r, dx, dy, f) \
    vclassSend(vwindowGetClass(w), vwindowSCROLL_RECT, (w, r, dx, dy, f))
#define vwindowNotify(w, e) \
    vclassSend(vwindowGetClass(w), vwindowNOTIFY, (w, e))
#define vwindowPlaceRect(w, b, mx, my) \
    vclassSend(vwindowGetClass(w), vwindowPLACE_RECT, (w, b, mx, my))
#define vwindowPlace(w, b, mx, my) \
    vclassSend(vwindowGetClass(w), vwindowPLACE, (w, b, mx, my))
#define vwindowDraw(w) \
    vclassSend(vwindowGetClass(w), vwindowDRAW, (w))
#define _vwindowDrawUpdateDevice(w, f) \
    vclassSend(vwindowGetClass(w), vwindowDRAW_DEVICE, (w, f))
#define vwindowHandleConfigure(w, e) \
    vclassSend(vwindowGetClass(w), vwindowHANDLE_CONFIGURE, (w, e))
#define vwindowHandleState(w, e) \
    vclassSend(vwindowGetClass(w), vwindowHANDLE_STATE, (w, e))
#define vwindowHandleUpdate(w, e) \
    vclassSend(vwindowGetClass(w), vwindowHANDLE_UPDATE, (w, e))
#define vwindowHandleEnter(w, e) \
    vclassSend(vwindowGetClass(w), vwindowHANDLE_ENTER, (w, e))
#define vwindowHandleLeave(w, e) \
    vclassSend(vwindowGetClass(w), vwindowHANDLE_LEAVE, (w, e))
#define vwindowHandleButtonDown(w, e) \
    vclassSend(vwindowGetClass(w), vwindowHANDLE_BUTTON_DOWN, (w, e))
#define vwindowHandleButtonUp(w, e) \
    vclassSend(vwindowGetClass(w), vwindowHANDLE_BUTTON_UP, (w, e))
#define vwindowHandleDrag(w, e) \
    vclassSend(vwindowGetClass(w), vwindowHANDLE_DRAG, (w, e))
#define vwindowHandleDetail(w, e) \
    vclassSend(vwindowGetClass(w), vwindowHANDLE_DETAIL, (w, e))
#define vwindowHandleMotion(w, e) \
    vclassSend(vwindowGetClass(w), vwindowHANDLE_MOTION, (w, e))
#define vwindowHandleAcquire(w, e) \
    vclassSend(vwindowGetClass(w), vwindowHANDLE_ACQUIRE, (w, e))
#define vwindowHandleLose(w, e) \
    vclassSend(vwindowGetClass(w), vwindowHANDLE_LOSE, (w, e))
#define vwindowHandleKeyDown(w, e) \
    vclassSend(vwindowGetClass(w), vwindowHANDLE_KEY_DOWN, (w, e))
#define vwindowHandleKeyUp(w, e) \
    vclassSend(vwindowGetClass(w), vwindowHANDLE_KEY_UP, (w, e))
#define vwindowSetTag(w, t) \
    vclassSend(vwindowGetClass(w), vobjectSET_TAG, (w, t))
#define vwindowSetNotify(w, f) \
    vclassSend(vwindowGetClass(w), vwindowSET_NOTIFY, (w, f))
#define vwindowSetData(w, p) \
    vclassSend(vwindowGetClass(w), vwindowSET_DATA, (w, p))
#define vwindowSetTitleScribed(w, s) \
    vclassSend(vwindowGetClass(w), vwindowSET_TITLE_SCRIBED, (w, s))
#define vwindowSetCursor(w, c) \
    vclassSend(vwindowGetClass(w), vwindowSET_CURSOR, (w, c))
#define vwindowSetCursorOwned(w, c) \
    vclassSend(vwindowGetClass(w), vwindowSET_CURSOR_OWNED, (w, c))
#define vwindowSetIcon(w, i) \
    vclassSend(vwindowGetClass(w), vwindowSET_ICON, (w, i))
#define vwindowSetIconOwned(w, i) \
    vclassSend(vwindowGetClass(w), vwindowSET_ICON_OWNED, (w, i))
#define vwindowSetFont(w, f) \
    vclassSend(vwindowGetClass(w), vwindowSET_FONT, (w, f))
#define vwindowSetForeground(w, c) \
    vclassSend(vwindowGetClass(w), vwindowSET_FOREGROUND, (w, c))
#define vwindowSetBackground(w, c) \
    vclassSend(vwindowGetClass(w), vwindowSET_BACKGROUND, (w, c))
#define vwindowSetSpace(w, s) \
    vclassSend(vwindowGetClass(w), vwindowSET_SPACE, (w, s))
#define vwindowSetSpaceOwned(w, s) \
    vclassSend(vwindowGetClass(w), vwindowSET_SPACE_OWNED, (w, s))
#define vwindowSetStyle(w, f) \
    vclassSend(vwindowGetClass(w), vwindowSET_STYLE, (w, f))
#define vwindowSetPopup(w, f) \
    vclassSend(vwindowGetClass(w), vwindowSET_POPUP, (w, f))
#define vwindowSetBackStore(w, f) \
    vclassSend(vwindowGetClass(w), vwindowSET_BACK_STORE, (w, f))
#define vwindowSetModal(w, f) \
    vclassSend(vwindowGetClass(w), vwindowSET_MODAL, (w, f))
#define vwindowSetFocusable(w, f) \
    vclassSend(vwindowGetClass(w), vwindowSET_FOCUSABLE, (w, f))
#define vwindowSetMotion(w, f) \
    vclassSend(vwindowGetClass(w), vwindowSET_MOTION, (w, f))
#define vwindowSetRect(w, r) \
    vclassSend(vwindowGetClass(w), vwindowSET_RECT, (w, r))
#define vwindowSetMinSize(w, x, y) \
    vclassSend(vwindowGetClass(w), vwindowSET_MIN_SIZE, (w, x, y))
#define vwindowSetMaxSize(w, x, y) \
    vclassSend(vwindowGetClass(w), vwindowSET_MAX_SIZE, (w, x, y))
#define vwindowSetLeader(w, l) \
    vclassSend(vwindowGetClass(w), vwindowSET_LEADER, (w, l))
#define vwindowSetApplication(w, a) \
    vclassSend(vwindowGetClass(w), vwindowSET_APPLICATION, (w, a))
#define vwindowSetHelpMode(w, b) \
    vclassSend(vwindowGetClass(w), vwindowSET_HELP_MODE, (w, b))
#define vwindowDetermineColorSchemeFrom(w, k, f, s) \
    vclassSend(vwindowGetClass(w), vwindowDETERMINE_COLOR_SCHEME_FROM, \
	       (w, k, f, s))
#define vwindowDetermineFrameSize(w, t, l, b, r) \
    vclassSend(vwindowGetClass(w), vwindowDETERMINE_FRAME_SIZE, (w,t,l,b,r))

vportEND_CPLUSPLUS_EXTERN_C

#endif /* #ifndef vwindowINCLUDED */


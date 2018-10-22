/* $Id: vapplication.h,v 1.53 1997/09/30 19:16:15 robert Exp $ */

/************************************************************

    vapplication.h

    C Interface file for the Application Manager

    (c) Copyright Visix Software Inc.
    All rights reserved

************************************************************/

#ifndef vapplicationINCLUDED
#define vapplicationINCLUDED

#ifndef  vportINCLUDED
#include <vport.h>
#endif

#ifndef  vstdioINCLUDED
#include vstdioHEADER
#endif

#ifndef  vclientINCLUDED
#include vclientHEADER
#endif

#ifndef  vpoolINCLUDED
#include vpoolHEADER
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

#ifndef  vfixedINCLUDED
#include vfixedHEADER
#endif

#ifndef  vrectINCLUDED
#include vrectHEADER
#endif

#ifndef  vpointINCLUDED
#include vpointHEADER
#endif

#ifndef  vmatrixINCLUDED
#include vmatrixHEADER
#endif

#ifndef  vtransformINCLUDED
#include vtransformHEADER
#endif

#ifndef  vfsINCLUDED
#include vfsHEADER
#endif

#ifndef  vresourceINCLUDED
#include vresourceHEADER
#endif

#ifndef  vpixmapINCLUDED
#include vpixmapHEADER
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

#ifndef  veventINCLUDED
#include veventHEADER
#endif

#ifndef  vwindowINCLUDED
#include vwindowHEADER
#endif

#ifndef  vresolverINCLUDED
#include <vresolver.h>
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * * * * * * * * * * PUBLIC CONSTANT DEFINITIONS * * * * * * * * * *
 */

enum {
    vapplicationID_ATTRIBUTE_DATA   = vobjectNEXT_ID_ATTRIBUTE,
    vapplicationID_ATTRIBUTE_TITLE,
    vapplicationID_ATTRIBUTE_NAME,
    vapplicationID_ATTRIBUTE_CURSOR,
    vapplicationID_ATTRIBUTE_BLOCK_CURSOR,
    vapplicationID_ATTRIBUTE_ICON,
    vapplicationID_ATTRIBUTE_FONT,
    vapplicationID_ATTRIBUTE_LINE_WIDTH,
    vapplicationID_ATTRIBUTE_COLOR,
    vapplicationNEXT_ID_ATTRIBUTE   = 
	vapplicationID_ATTRIBUTE_COLOR+vcolorID_MAX
};

enum {
    vapplicationSELECT_STOP_PROCESS = vobjectNEXT_SELECT,
    vapplicationNEXT_SELECT
};

enum {
    vapplicationPREF_DEFAULT_SYSTEM = 0,
    vapplicationPREF_DEFAULT_WINDOW,
    vapplicationPREF_DEFAULT_APPLICATION,
    vapplicationPREF_SYSTEM,
    vapplicationPREF_APPLICATION,
    vapplicationPREF_ENVIRONMENT,
    vapplicationPREF_WINDOW,
    vapplicationPREF_ARGS
};

/*
 * * * * * * * * * * PUBLIC TYPE DEFINITIONS * * * * * * * * * *
 */

#ifndef  _vapplicationDEFINED_VAPPLICATION
typedef struct vapplication	 vapplication;
#define  _vapplicationDEFINED_VAPPLICATION (1)	/** circular dependency  **/
#endif

typedef struct vapplicationClass    vapplicationClass;
typedef struct vapplicationWindowIterator vapplicationWindowIterator;

typedef void (*vapplicationNoteProc)(
    vapplication                   *application,
    vevent                         *event
    );

typedef unsigned long (*vapplicationDependColorFunc)(
    vapplication                   *application,
    unsigned long                   flags
    );

typedef vcolor *(*vapplicationDeriveColorFunc)(
    vapplication                   *application,
    vcolorScheme                   *known,
    int                             id
    );

/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */

void vapplicationStartup(void);


/*
 * applications
 */

void vapplicationReadPrefs(
    vapplication                   *application,
    int                             id
    );

void vapplicationSetCurrent(
    vapplication                   *application
    );

vapplicationClass *vapplicationGetDefaultClass(
    void
    );

vapplication *vapplicationGetRoot(
    void
    );

vapplication *vapplicationGetCurrent(
    void
    );

vapplication *vapplicationCreateOfClass(
    vapplicationClass              *clas
    );

vapplication *vapplicationCreate(
    void
    );

vapplication *vapplicationClone(
    vapplication                   *application
    );

void vapplicationInitOfClass(
    vapplication                   *application,
    vapplicationClass              *clas
    );

void vapplicationInit(
    vapplication                   *application
    );

void vapplicationDestroy(
    vapplication                   *application
    );

void vapplicationCopy(
    vapplication                   *application,
    vapplication                   *target
    );

void vapplicationCopyInit(
    vapplication                   *application,
    vapplication                   *target
    );

vapplication *vapplicationLoad(
    vresource                       resource
    );

void vapplicationLoadInit(
    vapplication                   *application,
    vresource                       resource
    );

void vapplicationStore(
    vapplication                   *application,
    vresource                       resource
    );

void vapplicationSetAttribute(
    vapplication                   *application,
    const vname                    *attr,
    void                           *value
    );

void vapplicationSetAllAttributes(
    vapplication                   *application,
    vdict                          *attr2value
    );

const void *vapplicationGetAttribute(
    vapplication                   *application,
    const vname                    *attr
    );

void vapplicationGetAllAttributes(
    vapplication                   *application,
    vdict                          *attr2value
    );

void vapplicationGetContextAttributes(
    vapplication                   *application,
    vdict                          *attr2value
    );

void vapplicationChangedParentAttribute(
    vapplication                   *application,
    const vname                    *attr,
    vdict                          *context
    );

void vapplicationChangedAttribute(
    vapplication                   *application,
    const vname                    *attr,
    vdict                          *context
    );

void vapplicationChangedChildAttribute(
    vapplication                   *application,
    const vname                    *attr,
    vdict                          *context
    );

void vapplicationChangedAttributeNone(
    vapplication                   *application,
    const vname                    *attr
    );

void vapplicationChangedAttributeValue(
    vapplication                   *application,
    const vname                    *attr,
    const void                     *oldValue,
    const void                     *value
    );

void vapplicationUpdateAttribute(
    vapplication                   *application,
    const vname                    *attr
    );

void vapplicationUpdateAllAttributes(
    vapplication                   *application
    );

const void *vapplicationAssociateAttribute(
    vapplication                   *application,
    const vname                    *attr,
    const vname                    *tag
    );

void vapplicationAssociateAllAttributes(
    vapplication                   *application,
    const vname                    *tag,
    vdict                          *attr2value
    );

void vapplicationPropagateChange(
    vapplication                   *application,
    const vname                    *attr,
    const vname                    *tag,
    const void                     *value
    );

void vapplicationPropagateChangeDict(
    vapplication                   *application,
    const vname                    *attr,
    vdict                          *tag2value
    );

void vapplicationPropagateChangeDictFromParent(
    vapplication                   *application,
    const vname                    *attr,
    vdict                          *tag2value
    );

void vapplicationHelp(
    vapplication                   *application
    );

void vapplicationDump(
    vapplication                   *application,
    FILE                           *stream
    );

void vapplicationNotify(
    vapplication                   *application,
    vevent                         *event
    );

void vapplicationSetTag(
    vapplication                   *application,
    const vname                    *tag
    );

void vapplicationSetNotify(
    vapplication                   *application,
    vapplicationNoteProc            noteProc
    );

void vapplicationSetData(
    vapplication                   *application,
    const void                     *data
    );

void vapplicationSetTitle(
    vapplication                   *application,
    const vchar                    *title
    );

void vapplicationSetTitleScribed(
    vapplication                   *application,
    vscribe                        *scribe
    );

void vapplicationSetName(
    vapplication                   *application,
    const vchar                    *name
    );

void vapplicationSetNameScribed(
    vapplication                   *application,
    vscribe                        *scribe
    );

void vapplicationSetCursor(
    vapplication                   *application,
    vcursor                        *cursor
    );

void vapplicationSetCursorOwned(
    vapplication                   *application,
    vcursor                        *cursor
    );

void vapplicationSetBlockCursor(
    vapplication                   *application,
    vcursor                        *cursor
    );

void vapplicationSetBlockCursorOwned(
    vapplication                   *application,
    vcursor                        *cursor
    );

void vapplicationSetIcon(
    vapplication                   *application,
    vimage                         *icon
    );

void vapplicationSetIconOwned(
    vapplication                   *application,
    vimage                         *icon
    );

void vapplicationSetFont(
    vapplication                   *application,
    vfont                          *font
    );

void vapplicationSetColor(
    vapplication                   *application,
    int                             id,
    vcolor                         *color
    );

void vapplicationSetDependColor(
    vapplication                   *application,
    vapplicationDependColorFunc     dependColorFunc
    );

void vapplicationSetDeriveColor(
    vapplication                   *application,
    vapplicationDeriveColorFunc     deriveColorFunc
    );

void vapplicationSetLineWidth(
    vapplication                   *application,
    int                             lineWidth
    );

void vapplicationSetSpace(
    vapplication                   *application,
    vcommandSpace                  *space
    );

void vapplicationSetSpaceOwned(
    vapplication                   *application,
    vcommandSpace                  *space
    );

void vapplicationSetResources(
    vapplication                   *application,
    vresource                       resource
    );

void vapplicationSetPreferences(
    vapplication                   *application,
    vresource                       resource
    );

void vapplicationSetGlobalWindow(
    vapplication                   *application,
    vwindow                        *window
    );

void vapplicationSetDragWindow(
    vapplication                   *application,
    vwindow                        *window
    );

void vapplicationSetKeyWindow(
    vapplication                   *application,
    vwindow                        *window
    );

vobjectAttributed *vapplicationGetObject(
    vapplication                   *application
    );

vapplicationClass *vapplicationGetClass(
    vapplication                   *application
    );

const vname *vapplicationGetTag(
    vapplication                   *application
    );

veventHandler *vapplicationGetHandler(
    vapplication                   *application
    );

vapplicationNoteProc vapplicationGetNotify(
    vapplication                   *application
    );

const void *vapplicationGetData(
    vapplication                   *application
    );

const vname *vapplicationGetTitle(
    vapplication                   *application
    );

const vname *vapplicationGetName(
    vapplication                   *application
    );

vcursor *vapplicationGetCursor(
    vapplication                   *application
    );

vcursor *vapplicationGetBlockCursor(
    vapplication                   *application
    );

vimage *vapplicationGetIcon(
    vapplication                   *application
    );

vfont *vapplicationGetFont(
    vapplication                   *application
    );

vcolor *vapplicationGetColor(
    vapplication                   *application,
    int                             id
    );

vapplicationDependColorFunc vapplicationGetDependColor(
    vapplication                   *application
    );

vapplicationDeriveColorFunc vapplicationGetDeriveColor(
    vapplication                   *application
    );

int vapplicationGetLineWidth(
    vapplication                   *application
    );

vcommandSpace *vapplicationGetSpace(
    vapplication                   *application
    );

vresource vapplicationGetResources(
    vapplication                   *application
    );

vresource vapplicationGetPreferences(
    vapplication                   *application
    );

vresource vapplicationGetSystemResources(
    vapplication                   *application
    );

vresource vapplicationGetSystemPreferences(
    vapplication                   *application
    );

vdict *vapplicationGetButtonMap(
    vapplication                   *application
    );

vdict *vapplicationGetKeyMap(
    vapplication                   *application
    );

vdict *vapplicationGetKeyDispatch(
    vapplication                   *application
    );

const vname *vapplicationLoadButtonMap(
    vapplication                   *application,
    vkeyModifiers                   modifiers
    );

const vname *vapplicationLoadKeyMap(
    vapplication                   *application,
    vkeyStroke                      key
    );

vwindow *vapplicationLoadKeyDispatch(
    vapplication                   *application,
    vkeyStroke                      key
    );

vwindow *vapplicationGetGlobalWindow(
    vapplication                   *application
    );

vwindow *vapplicationGetDragWindow(
    vapplication                   *application
    );

vwindow *vapplicationGetKeyWindow(
    vapplication                   *application
    );

vcursor *vapplicationDetermineCursor(
    vapplication                   *application
    );

vcursor *vapplicationDetermineBlockCursor(
    vapplication                   *application
    );

vimage *vapplicationDetermineIcon(
    vapplication                   *application
    );

vfont *vapplicationDetermineFont(
    vapplication                   *application
    );

vcolor *vapplicationDetermineColor(
    vapplication                   *application,
    int                             id
    );

void vapplicationDetermineColorScheme(
    vapplication                   *application,
    unsigned long                   flags,
    vcolorScheme                   *scheme
    );

void vapplicationDetermineColorSchemeFrom(
    vapplication                   *application,
    vcolorScheme                   *known,
    unsigned long                   flags,
    vcolorScheme                   *scheme
    );

int vapplicationDetermineLineWidth(
    vapplication                   *application
    );

void vapplicationInitWindowIterator(
    vapplicationWindowIterator     *iterator,
    vapplication                   *application
    );

int vapplicationNextWindowIterator(
    vapplicationWindowIterator     *iterator
    );

void vapplicationDestroyWindowIterator(
    vapplicationWindowIterator     *iterator
    );

vwindow *vapplicationGetWindowIteratorWindow(
    vapplicationWindowIterator     *iterator
    );

void vapplicationSetResolver(
    vapplication		   *application,
    vresolver			   *resolver
    );
    
vresolver *vapplicationGetResolver(
    vapplication		   *application
    );

/*
 * deprecated applications
 */

void vapplicationDetermineColors(
    vapplication                   *application,
    int                            *ids,
    int                             count,
    vcolor                        **colors
    );

void vapplicationDetermineColorsFrom(
    vapplication                   *application,
    long                            flags,
    vcolor                        **known,
    int                            *ids,
    int                             count,
    vcolor                        **colors
    );

void vapplicationReadPlatformSpecificPrefs(
    void
    );

/*
 * * * * * * * * * * PRIVATE CONSTANT DEFINITIONS * * * * * * * * * *
 */

enum {
    _vapplicationOWN_CURSOR         = 0x0001,
    _vapplicationOWN_BLOCK_CURSOR   = 0x0002,
    _vapplicationOWN_ICON           = 0x0004,
    _vapplicationOWN_SPACE          = 0x0008
};

/*
 * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * *
 */

struct vapplication {
    vobjectAttributed               object;
    veventHandler                   handler;
    vapplicationNoteProc            noteProc;
    const void		           *data;
    const vname                    *title;
    const vname                    *name;
    vcursor		           *cursor;
    vcursor		           *blockCursor;
    vimage                         *icon;
    vfont                          *font;
    vcolorScheme                    colors;
    vapplicationDependColorFunc     dependColorFunc;
    vapplicationDeriveColorFunc     deriveColorFunc;
    int                             lineWidth;
    vcommandSpace                  *space;
    unsigned int                    flags;
    vdict                           buttonMap;
    vdict                           keyMap;
    vdict                           keyDispatch;
    vwindow                        *globalWindow;
    vwindow                        *dragWindow;
    vwindow                        *keyWindow;
    vclient                        *client;
    vresolver			   *resolver;
};

struct vapplicationWindowIterator {
    vapplication                   *application;
    vwindowIterator                 window;
};

#define vapplicationCLASS(SUPER, APPLICATION, NOTIFY)                         \
    vobjectATTRIBUTED_CLASS(SUPER, APPLICATION);                              \
    vclassVARIABLE(vapplicationCURSOR, vcursor*);                             \
    vclassVARIABLE(vapplicationBLOCK_CURSOR, vcursor*);                       \
    vclassVARIABLE(vapplicationICON, vimage*);                                \
    vclassVARIABLE(vapplicationFONT, vfont*);                                 \
    vclassVARIABLE_ARRAY(vapplicationCOLORS, vcolor*, vdrawCOLOR_MAX);        \
    vclassVARIABLE(vapplicationLINE_WIDTH, int);                              \
    vclassVARIABLE(vapplicationRESOURCES, vresource);                         \
    vclassVARIABLE(vapplicationPREFERENCES, vresource);                       \
    vclassMETHOD(vapplicationNOTIFY,                                          \
		 (APPLICATION *application, vevent *event));                  \
    vclassMETHOD(vapplicationOBSERVE_APPLICATION,                             \
		 (APPLICATION *application, vevent *event));                  \
    vclassMETHOD(vapplicationSET_NOTIFY,                                      \
		 (APPLICATION *application, NOTIFY noteProc));                \
    vclassMETHOD(vapplicationSET_DATA,                                        \
		 (APPLICATION *application, const void *data));               \
    vclassMETHOD(vapplicationSET_TITLE_SCRIBED,                               \
		 (APPLICATION *application, vscribe *scribe));                \
    vclassMETHOD(vapplicationSET_NAME_SCRIBED,                                \
		 (APPLICATION *application, vscribe *scribe));                \
    vclassMETHOD(vapplicationSET_CURSOR,                                      \
		 (APPLICATION *application, vcursor *cursor));                \
    vclassMETHOD(vapplicationSET_CURSOR_OWNED,                                \
		 (APPLICATION *application, vcursor *cursor));                \
    vclassMETHOD(vapplicationSET_BLOCK_CURSOR,                                \
		 (APPLICATION *application, vcursor *cursor));                \
    vclassMETHOD(vapplicationSET_BLOCK_CURSOR_OWNED,                          \
		 (APPLICATION *application, vcursor *cursor));                \
    vclassMETHOD(vapplicationSET_ICON,                                        \
		 (APPLICATION *application, vimage *icon));                   \
    vclassMETHOD(vapplicationSET_ICON_OWNED,                                  \
		 (APPLICATION *application, vimage *icon));                   \
    vclassMETHOD(vapplicationSET_FONT,                                        \
		 (APPLICATION *application, vfont *font));                    \
    vclassMETHOD(vapplicationSET_COLOR,                                       \
		 (APPLICATION *application, int id, vcolor *color));          \
    vclassMETHOD(vapplicationSET_DEPEND_COLOR,                                \
		 (APPLICATION *application,                                   \
		  vapplicationDependColorFunc dependColorFunc));              \
    vclassMETHOD(vapplicationSET_DERIVE_COLOR,                                \
		 (APPLICATION *application,                                   \
		  vapplicationDeriveColorFunc deriveColorFunc));              \
    vclassMETHOD(vapplicationSET_LINE_WIDTH,                                  \
		 (APPLICATION *application, int lineWidth));                  \
    vclassMETHOD(vapplicationSET_SPACE,                                       \
		 (APPLICATION *application, vcommandSpace *space));           \
    vclassMETHOD(vapplicationSET_SPACE_OWNED,                                 \
		 (APPLICATION *application, vcommandSpace *space));           \
    vclassMETHOD(vapplicationSET_RESOURCES,                                   \
		 (APPLICATION *application, vresource resource));             \
    vclassMETHOD(vapplicationSET_PREFERENCES,                                 \
		 (APPLICATION *application, vresource resource));             \
    vclassMETHOD(vapplicationSET_GLOBAL_WINDOW,                               \
		 (APPLICATION *application, vwindow *window));                \
    vclassMETHOD(vapplicationSET_DRAG_WINDOW,                                 \
		 (APPLICATION *application, vwindow *window));                \
    vclassMETHOD(vapplicationSET_KEY_WINDOW,                                  \
		 (APPLICATION *application, vwindow *window));                \
    vclassMETHOD(vapplicationDETERMINE_COLOR_SCHEME_FROM,                     \
		 (APPLICATION *application, vcolorScheme *known,              \
		  unsigned long flags, vcolorScheme *scheme))

struct vapplicationClass {
    vapplicationCLASS(vapplicationClass, vapplication, vapplicationNoteProc);
};

/*
 * * * * * * * * * * PRIVATE FUNCTION DECLARATIONS * * * * * * * * * *
 */

vobjectPartialChildIteratorClass *_vapplicationGetPartialChildIteratorClass(
								void);

void _vapplicationTranslateKeyModifiers(vkeyModifiers *modifiers);


/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * *
 */

/*
 * applications
 */

#define vapplicationGetObject(a)    vportBASE_OBJECT(a, object)

#define vapplicationCreateOfClass(c) \
    ((vapplication*)vobjectCreateOfClass((vobjectClass*)(c)))
#define vapplicationCreate() \
    vapplicationCreateOfClass(vapplicationGetDefaultClass())
#define vapplicationClone(a) \
    ((vapplication*)vobjectClone(vapplicationGetObject(a)))
#define vapplicationInitOfClass(a, c) \
    vobjectInitOfClass(vapplicationGetObject(a), (vobjectClass*)(c))
#define vapplicationInit(a) \
    vapplicationInitOfClass(a, vapplicationGetDefaultClass())
#define vapplicationCopyInit(a, t) \
    vobjectCopyInit(vapplicationGetObject(a), vapplicationGetObject(t))
#define vapplicationLoad(r)       ((vapplication*)vobjectLoad(r))
#define vapplicationLoadInit(a, r) \
    vobjectLoadInit(vapplicationGetObject(a), r)
#define vapplicationDestroy(a) \
    vobjectDestroy(vapplicationGetObject(a))

#define vapplicationChangedAttributeNone(a, n) \
    vobjectChangedAttributeNone(vapplicationGetObject(a), n)
#define vapplicationChangedAttributeValue(a, n, o, v) \
    vobjectChangedAttributeValue(vapplicationGetObject(a), n, o, v)
#define vapplicationAssociateAttribute(a, t, n) \
    vobjectAssociateAttribute(vapplicationGetObject(a), t, n)
#define vapplicationAssociateAllAttributes(a, n, d) \
    vobjectAssociateAllAttributes(vapplicationGetObject(a), n, d)
#define vapplicationPropagateChange(a, t, n, v) \
    vobjectPropagateChange(vapplicationGetObject(a), t, n, v)
#define vapplicationPropagateChangeDictFromParent(a, t, d) \
    vobjectPropagateChangeDictFromParent(vapplicationGetObject(a), t, d)

#define vapplicationSetTitle(a, s)  \
    vapplicationSetTitleScribed(a, vcharScribe(s))
#define vapplicationSetName(a, s)  \
    vapplicationSetNameScribed(a, vcharScribe(s))

#define vapplicationGetClass(a) \
    ((vapplicationClass*)vobjectGetAttributedClass(vapplicationGetObject(a)))
#define vapplicationGetTag(a) \
    vobjectGetTag(vapplicationGetObject(a))
#define vapplicationGetHandler(a)     (&(a)->handler)
#define vapplicationGetNotify(a)       ((a)->noteProc)
#define vapplicationGetData(a)	       ((a)->data)
#define vapplicationGetTitle(a)	       ((a)->title)
#define vapplicationGetName(a)	       ((a)->name)
#define vapplicationGetCursor(a)       ((a)->cursor)
#define vapplicationGetBlockCursor(a)  ((a)->blockCursor)
#define vapplicationGetIcon(a)	       ((a)->icon)
#define vapplicationGetFont(a)	       ((a)->font)
#define vapplicationGetColor(a, i)       vcolorGetScheme(&(a)->colors, i)
#define vapplicationGetDependColor(a)  ((a)->dependColorFunc)
#define vapplicationGetDeriveColor(a)  ((a)->deriveColorFunc)
#define vapplicationGetLineWidth(a)    ((a)->lineWidth)
#define vapplicationGetSpace(a)        ((a)->space)
#define vapplicationGetSystemResources(a) \
    vclassGet(vapplicationGetClass(a), vapplicationRESOURCES)
#define vapplicationGetSystemPreferences(a) \
    vclassGet(vapplicationGetClass(a), vapplicationPREFERENCES)
#define vapplicationGetButtonMap(a)   (&(a)->buttonMap)
#define vapplicationGetKeyMap(a)      (&(a)->keyMap)
#define vapplicationGetKeyDispatch(a) (&(a)->keyDispatch)
#define vapplicationLoadButtonMap(a, m) \
    ((const vname*)vdictLoad(&(a)->buttonMap, vkeyInternModifiers(m)))
#define vapplicationLoadKeyDispatch(a, k) \
    ((vwindow*)vdictLoad(&(a)->keyDispatch, vkeyInternStroke(k)))
#define vapplicationGetGlobalWindow(a) ((a)->globalWindow)
#define vapplicationGetDragWindow(a)   ((a)->dragWindow)
#define vapplicationGetKeyWindow(a)    ((a)->keyWindow)
#define vapplicationGetResolver(a)     ((a)->resolver)

#define vapplicationDestroyWindowIterator(i) \
    vwindowDestroyIterator(&(i)->window)
#define vapplicationGetWindowIteratorWindow(i) \
    vwindowGetIteratorWindow(&(i)->window)

/*
 * deprecated applications
 */

#define vapplicationDetermineColors(a, i, n, c) \
    vapplicationDetermineColorsFrom(a, 0L, (vcolor**)NULL, i, n, c)
#define vapplicationReadPlatformSpecificPrefs() \
    vprefReadPlatformSpecificPrefs()

/*
 * * * * * * * * * * PRIVATE FUNCTION MESSAGE DEFINITIONS * * * * * * * * * *
 */

#define vapplicationCopy(a, t) \
    vclassSend(vapplicationGetClass(a), vobjectCOPY, (a, t))
#define vapplicationStore(a, r) \
    vclassSend(vapplicationGetClass(a), vobjectSTORE, (a, r))
#define vapplicationSetAttribute(a, t, v) \
    vclassSend(vapplicationGetClass(a), vobjectSET_ATTRIBUTE, (a, t, v))
#define vapplicationSetAllAttributes(a, d) \
    vclassSend(vapplicationGetClass(a), vobjectSET_ALL_ATTRIBUTES, (a, d))
#define vapplicationGetAttribute(a, t) \
    vclassSend(vapplicationGetClass(a), vobjectGET_ATTRIBUTE, (a, t))
#define vapplicationGetAllAttributes(a, d) \
    vclassSend(vapplicationGetClass(a), vobjectGET_ALL_ATTRIBUTES, (a, d))
#define vapplicationGetContextAttributes(a, d) \
    vclassSend(vapplicationGetClass(a), vobjectGET_CONTEXT_ATTRIBUTES, (a, d))
#define vapplicationChangedParentAttribute(a, t, d) \
    vclassSend(vapplicationGetClass(a), vobjectCHANGED_PARENT_ATTRIBUTE, \
	       (a, t, d))
#define vapplicationChangedAttribute(a, t, d) \
    vclassSend(vapplicationGetClass(a), vobjectCHANGED_ATTRIBUTE, (a, t, d))
#define vapplicationChangedChildAttribute(a, t, d) \
    vclassSend(vapplicationGetClass(a), vobjectCHANGED_CHILD_ATTRIBUTE, \
	       (a, t, d))
#define vapplicationUpdateAttribute(a, t) \
    vclassSend(vapplicationGetClass(a), vobjectUPDATE_ATTRIBUTE, (a, t))
#define vapplicationUpdateAllAttributes(a) \
    vclassSend(vapplicationGetClass(a), vobjectUPDATE_ALL_ATTRIBUTES, (a))
#define vapplicationPropagateChangeDict(a, t, d) \
    vclassSend(vapplicationGetClass(a), vobjectPROPAGATE_CHANGE_DICT, \
	       (a, t, d))
#define vapplicationHelp(a) \
    vclassSend(vapplicationGetClass(a), vobjectHELP, (a))
#define vapplicationDump(a, s) \
    vclassSend(vapplicationGetClass(a), vobjectDUMP, (a, s))
#define vapplicationSetTag(a, t) \
    vclassSend(vapplicationGetClass(a), vobjectSET_TAG, (a, t))

#define vapplicationNotify(a, e) \
    vclassSend(vapplicationGetClass(a), vapplicationNOTIFY, (a, e))
#define vapplicationSetNotify(a, f) \
    vclassSend(vapplicationGetClass(a), vapplicationSET_NOTIFY, (a, f))
#define vapplicationSetData(a, p) \
    vclassSend(vapplicationGetClass(a), vapplicationSET_DATA, (a, p))
#define vapplicationSetTitleScribed(a, s) \
    vclassSend(vapplicationGetClass(a), vapplicationSET_TITLE_SCRIBED, (a, s))
#define vapplicationSetNameScribed(a, s) \
    vclassSend(vapplicationGetClass(a), vapplicationSET_NAME_SCRIBED, (a, s))
#define vapplicationSetCursor(a, c) \
    vclassSend(vapplicationGetClass(a), vapplicationSET_CURSOR, (a, c))
#define vapplicationSetCursorOwned(a, c) \
    vclassSend(vapplicationGetClass(a), vapplicationSET_CURSOR_OWNED, (a, c))
#define vapplicationSetBlockCursor(a, c) \
    vclassSend(vapplicationGetClass(a), vapplicationSET_BLOCK_CURSOR, (a, c))
#define vapplicationSetBlockCursorOwned(a, c) \
    vclassSend(vapplicationGetClass(a), vapplicationSET_BLOCK_CURSOR_OWNED, \
	       (a, c))
#define vapplicationSetIcon(a, i) \
    vclassSend(vapplicationGetClass(a), vapplicationSET_ICON, (a, i))
#define vapplicationSetIconOwned(a, i) \
    vclassSend(vapplicationGetClass(a), vapplicationSET_ICON_OWNED, (a, i))
#define vapplicationSetFont(a, f) \
    vclassSend(vapplicationGetClass(a), vapplicationSET_FONT, (a, f))
#define vapplicationSetColor(a, n, c) \
    vclassSend(vapplicationGetClass(a), vapplicationSET_COLOR, (a, n, c))
#define vapplicationSetDependColor(a, f) \
    vclassSend(vapplicationGetClass(a), vapplicationSET_DEPEND_COLOR, (a, f))
#define vapplicationSetDeriveColor(a, f) \
    vclassSend(vapplicationGetClass(a), vapplicationSET_DERIVE_COLOR, (a, f))
#define vapplicationSetLineWidth(a, w) \
    vclassSend(vapplicationGetClass(a), vapplicationSET_LINE_WIDTH, (a, w))
#define vapplicationSetSpace(a, s) \
    vclassSend(vapplicationGetClass(a), vapplicationSET_SPACE, (a, s))
#define vapplicationSetSpaceOwned(a, s) \
    vclassSend(vapplicationGetClass(a), vapplicationSET_SPACE_OWNED, (a, s))
#define vapplicationSetResources(a, r) \
    vclassSend(vapplicationGetClass(a), vapplicationSET_RESOURCES, (a, r))
#define vapplicationSetPreferences(a, r) \
    vclassSend(vapplicationGetClass(a), vapplicationSET_PREFERENCES, (a, r))
#define vapplicationSetGlobalWindow(a, w) \
    vclassSend(vapplicationGetClass(a), vapplicationSET_GLOBAL_WINDOW, (a, w))
#define vapplicationSetDragWindow(a, w) \
    vclassSend(vapplicationGetClass(a), vapplicationSET_DRAG_WINDOW, (a, w))
#define vapplicationSetKeyWindow(a, w) \
    vclassSend(vapplicationGetClass(a), vapplicationSET_KEY_WINDOW, (a, w))
#define vapplicationDetermineColorSchemeFrom(a, k, f, s) \
    vclassSend(vapplicationGetClass(a), \
	       vapplicationDETERMINE_COLOR_SCHEME_FROM, (a, k, f, s))

vportEND_CPLUSPLUS_EXTERN_C

#endif /* #ifndef vapplicationINCLUDED */


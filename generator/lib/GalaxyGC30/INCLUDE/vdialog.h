/* $Id: vdialog.h,v 1.120 1997/11/14 01:20:01 bill Exp $ */

/************************************************************

    vdialog.h

    C Interface file for the Dialog Manager

    (c) Copyright Visix Software Inc.
    All rights reserved

************************************************************/

#ifndef vdialogINCLUDED
#define vdialogINCLUDED

#ifndef  vportINCLUDED
#include <vport.h>
#endif

#ifndef  vdebugINCLUDED
#include vdebugHEADER
#endif

#ifndef  vmemINCLUDED
#include vmemHEADER
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

#ifndef  veventINCLUDED
#include veventHEADER
#endif

#ifndef  vwindowINCLUDED
#include vwindowHEADER
#endif

#ifndef  vlafINCLUDED
#include vlafHEADER
#endif

#ifndef  vspringINCLUDED
#include vspringHEADER
#endif

#ifndef  vmenuINCLUDED
#include vmenuHEADER
#endif

#ifndef  vdropsiteINCLUDED
#include vdropsiteHEADER
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * * * * * * * * * * PUBLIC CONSTANT DEFINITIONS * * * * * * * * * *
 */

/*
 * dialogs
 */

enum {
    vdialogID_ATTRIBUTE_MENU        = vwindowNEXT_ID_ATTRIBUTE,
    vdialogID_ATTRIBUTE_FOCUS,
    vdialogID_ATTRIBUTE_CONFIRM,
    vdialogID_ATTRIBUTE_ABANDON,
    vdialogID_ATTRIBUTE_DEFAULT_FOCUS,
    vdialogID_ATTRIBUTE_SOLUTION,
    vdialogNEXT_ID_ATTRIBUTE
};

enum {
    vdialogSELECT_MOVE_FOCUS        = vwindowNEXT_SELECT,
    vdialogSELECT_MENU,
    vdialogSELECT_REROUTE,
    vdialogSELECT_LIVE_HELP,
    vdialogNEXT_SELECT
};

/*
 * dialog items
 */

enum {
    vdialogITEM_ID_ATTRIBUTE_DATA   = vobjectNEXT_ID_ATTRIBUTE,
    vdialogITEM_ID_ATTRIBUTE_TITLE,
    vdialogITEM_ID_ATTRIBUTE_CURSOR,
    vdialogITEM_ID_ATTRIBUTE_MENU,
    vdialogITEM_ID_ATTRIBUTE_DROPSITE,
    vdialogITEM_ID_ATTRIBUTE_FONT,
    vdialogITEM_ID_ATTRIBUTE_FOREGROUND,
    vdialogITEM_ID_ATTRIBUTE_FOREGROUND_HILITE,
    vdialogITEM_ID_ATTRIBUTE_BACKGROUND,
    vdialogITEM_ID_ATTRIBUTE_BACKGROUND_HILITE,
    vdialogITEM_ID_ATTRIBUTE_COLOR,
    vdialogITEM_ID_ATTRIBUTE_LINE_WIDTH,
    vdialogITEM_ID_ATTRIBUTE_IMAGE,
    vdialogITEM_ID_ATTRIBUTE_MNEMONIC,
    vdialogITEM_ID_ATTRIBUTE_SHOWN,
    vdialogITEM_ID_ATTRIBUTE_STATE,
    vdialogITEM_ID_ATTRIBUTE_BORDER,
    vdialogITEM_ID_ATTRIBUTE_IMAGE_MASK,
    vdialogITEM_ID_ATTRIBUTE_RECT,
    vdialogITEM_ID_ATTRIBUTE_BOUNDS,
    vdialogITEM_ID_ATTRIBUTE_MIN_SIZE,
    vdialogITEM_ID_ATTRIBUTE_FIELD,
    vdialogITEM_NEXT_ID_ATTRIBUTE
};

enum {
    vdialogITEM_SELECT_SELECT       = vobjectNEXT_SELECT,
    vdialogITEM_SELECT_MOVE_FOCUS,
    vdialogITEM_SELECT_MENU,
    vdialogITEM_SELECT_MENU_BAR,
    vdialogITEM_SELECT_ACCELERATOR,
    vdialogITEM_SELECT_BEGIN,
    vdialogITEM_SELECT_END,
    vdialogITEM_SELECT_LEFT,
    vdialogITEM_SELECT_RIGHT,
    vdialogITEM_SELECT_UP,
    vdialogITEM_SELECT_DOWN,
    vdialogITEM_SELECT_PAGE_LEFT,
    vdialogITEM_SELECT_PAGE_RIGHT,
    vdialogITEM_SELECT_PAGE_UP,
    vdialogITEM_SELECT_PAGE_DOWN,
    vdialogITEM_SELECT_INSERT,
    vdialogITEM_SELECT_DELETE,
    vdialogITEM_SELECT_UNDO,
    vdialogITEM_SELECT_CUT,
    vdialogITEM_SELECT_COPY,
    vdialogITEM_SELECT_PASTE,
    vdialogITEM_SELECT_CLEAR,
    vdialogITEM_SELECT_PRINT,
    vdialogITEM_SELECT_FIND,
    vdialogITEM_SELECT_MNEMONIC,
    vdialogITEM_NEXT_SELECT
};

/*
 * dialog item lists
 */

enum {
    vdialogITEM_LIST_ID_ATTRIBUTE_FOCUS = vobjectNEXT_ID_ATTRIBUTE,
    vdialogITEM_LIST_ID_ATTRIBUTE_CONFIRM,
    vdialogITEM_LIST_ID_ATTRIBUTE_ABANDON,
    vdialogITEM_LIST_ID_ATTRIBUTE_DEFAULT_FOCUS,
    vdialogITEM_LIST_ID_ATTRIBUTE_CURRENT_CONFIRM,
    vdialogITEM_LIST_ID_ATTRIBUTE_SOLUTION,
    vdialogITEM_LIST_NEXT_ID_ATTRIBUTE
};

enum {
    vdialogITEM_LIST_OWNER_STATE_FUNCS		= 0x0001,
    vdialogITEM_LIST_OWNER_DRAW_FUNCS		= 0x0002,
    vdialogITEM_LIST_OWNER_TRANSFORM_FUNCS	= 0x0004
};

/*
 * * * * * * * * * * PUBLIC TYPE DEFINITIONS * * * * * * * * * *
 */

/*
 * dialogs
 */

typedef struct vdialog              vdialog;
typedef struct vdialogClass         vdialogClass;

typedef vcommand                    vdialogFocusCommand;
typedef vcommandClass               vdialogFocusCommandClass;

typedef void (*vdialogNoteProc)(
    vdialog                        *dialog,
    vevent                         *event
    );

typedef int (*vdialogHookFunc)(
    vdialog                        *dialog,
    vevent                         *event
    );

/*
 * dialog items
 */

typedef struct vdialogItem          vdialogItem;
typedef struct vdialogItemClass     vdialogItemClass;

typedef vdialogItem                 vdialogLabelItem;
typedef vdialogItemClass            vdialogLabelItemClass;

typedef vdialogItem                 vdialogLineItem;
typedef vdialogItemClass            vdialogLineItemClass;

typedef vdialogItem                 vdialogBoxItem;
typedef vdialogItemClass            vdialogBoxItemClass;

typedef void (*vdialogItemNoteProc)(
    vdialogItem                    *item,
    vevent                         *event
    );

/*
 * dialog item lists
 */

typedef struct vdialogItemList           vdialogItemList;
typedef struct vdialogItemListClass      vdialogItemListClass;
typedef struct vdialogItemListOwnerFuncs vdialogItemListOwnerFuncs;

struct vdialogItemListOwnerFuncs {
    unsigned int flags;
    vdialog *(*DetermineDialog)(vobjectAttributed *owner);
    vcursor *(*DetermineCursor)(vobjectAttributed *owner);
    vfont   *(*DetermineFont)(vobjectAttributed *owner);
    void     (*DetermineColorsFrom)
	         (vobjectAttributed *owner, long flags, vcolor **known, 
		  int *ids, int count, vcolor **colors);
    int      (*DetermineLineWidth)(vobjectAttributed *owner);
    void     (*DetermineBounds)(vobjectAttributed *owner, vrect *bounds);
    void     (*DetermineContent)(vobjectAttributed *owner, vrect *content);
    vdict   *(*GetKeyMap)(vobjectAttributed *owner);
    vdict   *(*GetKeyDispatch)(vobjectAttributed *owner);
    int      (*DetermineShown)(vobjectAttributed *owner);
    int      (*DetermineEnabled)(vobjectAttributed *owner);
    void     (*DetermineColorSchemeFrom)
	         (vobjectAttributed *owner, vcolorScheme *known, 
		  unsigned long flags, vcolorScheme *scheme);
    void     (*DrawDevice)(vobjectAttributed *owner);
    void     (*TransformPoint)(vobjectAttributed *owner, int x, int y,
			       int *rx, int *ry);
    void     (*TransformRect)(vobjectAttributed *owner, const vrect *rect,
			      vrect *rrect);
};

/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */

void vdialogStartup(void);


/*
 * dialogs
 */

vdialogClass *vdialogGetDefaultClass(
    void
    );

vdialog *vdialogCreateOfClass(
    vdialogClass                   *clas
    );

vdialog *vdialogCreate(
    void
    );

vdialog *vdialogClone(
    vdialog                        *dialog
    );

void vdialogInitOfClass(
    vdialog                        *dialog,
    vdialogClass                   *clas
    );

void vdialogInit(
    vdialog                        *dialog
    );

void vdialogDestroy(
    vdialog                        *dialog
    );

void vdialogCopy(
    vdialog                        *dialog,
    vdialog                        *target
    );

void vdialogCopyInit(
    vdialog                        *dialog,
    vdialog                        *target
    );

vdialog *vdialogLoad(
    vresource                       resource
    );

void vdialogLoadInit(
    vdialog                        *dialog,
    vresource                       resource
    );

void vdialogStore(
    vdialog                        *dialog,
    vresource                       resource
    );

vbool vdialogDisplayHelp(
    vdialog                        *dialog,
    vhelprequest		   *request
    );

void vdialogOpen(
    vdialog                        *dialog
    );

void vdialogClose(
    vdialog                        *dialog
    );

void vdialogNotify(
    vdialog                        *dialog,
    vevent                         *event
    );

void vdialogMove(
    vdialog                        *dialog,
    int                             x,
    int                             y
    );

void vdialogResize(
    vdialog                        *dialog,
    int                             w,
    int                             h
    );

void vdialogPlace(
    vdialog                        *dialog,
    vdialog                        *base,
    int                             modeX,
    int                             modeY
    );

void vdialogPlaceWindow(
    vdialog                        *dialog,
    vwindow			   *base,
    int                             modeX,
    int                             modeY
    );

void vdialogAppendItem(
    vdialog                        *dialog,
    vdialogItem                    *item
    );

vdialogItem *vdialogRemoveItem(
    vdialog                        *dialog,
    vdialogItem                    *item
    );

void vdialogSetItemIndex(
    vdialog                        *dialog,
    vdialogItem                    *item,
    int                             index
    );

void vdialogArrange(
    vdialog                        *dialog,
    const vrect                    *rect
    );

void vdialogCalcMinSize(
    vdialog                        *dialog,
    int                            *w,
    int                            *h
    );

void vdialogSetNotify(
    vdialog                        *dialog,
    vdialogNoteProc	            noteProc
    );

void vdialogSetData(
    vdialog                        *dialog,
    const void                     *data
    );

void vdialogSetTitle(
    vdialog                        *dialog,
    const vchar                    *title
    );

void vdialogSetTitleScribed(
    vdialog                        *dialog,
    vscribe                        *scribe
    );

void vdialogSetIcon(
    vdialog                        *dialog,
    vimage                         *icon
    );

void vdialogSetMaxSize(
    vdialog                        *dialog,
    int                             w,
    int                             h
    );

void vdialogSetMenu(
    vdialog                        *dialog,
    vmenu                          *menu
    );

void vdialogSetCloseHook(
    vdialog                        *dialog,
    vdialogHookFunc                 closeHook
    );

void vdialogSetRetainFocusOnDeactivate(
    vdialog                        *dialog,
    int				    retain
    );

void vdialogSetFocus(
    vdialog                        *dialog,
    vdialogItem                    *item
    );

vbool vdialogTestSetFocus(
    vdialog                        *dialog,
    vdialogItem                    *item,
    vevent			   *event
    );

void vdialogSetConfirm(
    vdialog                        *dialog,
    vdialogItem                    *item
    );

void vdialogSetAbandon(
    vdialog                        *dialog,
    vdialogItem                    *item
    );

void vdialogSetDefFocus(
    vdialog                        *dialog,
    vdialogItem                    *item
    );

void vdialogSetDrag(
    vdialog                        *dialog,
    vdialogItem                    *item
    );

void vdialogSetSolution(
    vdialog                        *dialog,
    vspringSolution                *solution
    );

vobjectAttributed *vdialogGetObject(
    vdialog                        *dialog
    );

vwindow *vdialogGetWindow(
    vdialog                        *dialog
    );

vdialogClass *vdialogGetClass(
    vdialog                        *dialog
    );

vdialogNoteProc vdialogGetNotify(
    vdialog                        *dialog
    );

const void *vdialogGetData(
    vdialog                        *dialog
    );

const vchar *vdialogGetTitle(
    vdialog                        *dialog
    );

vimage *vdialogGetIcon(
    vdialog                        *dialog
    );

int vdialogIsOpen(
    vdialog                        *dialog
    );

int vdialogGetMaxW(
    vdialog                        *dialog
    );

int vdialogGetMaxH(
    vdialog                        *dialog
    );

vmenu *vdialogGetMenu(
    vdialog                        *dialog
    );

vdialogHookFunc vdialogGetCloseHook(
    vdialog                        *dialog
    );

vdialogItemList *vdialogGetItemList(
    vdialog                        *dialog
    );

vbool vdialogGetRetainFocusOnDeactivate(
    vdialog                        *dialog
    );

vdialogItem *vdialogGetFocus(
    vdialog                        *dialog
    );

vdialogItem *vdialogGetConfirm(
    vdialog                        *dialog
    );

vdialogItem *vdialogGetAbandon(
    vdialog                        *dialog
    );

vdialogItem *vdialogGetDefFocus(
    vdialog                        *dialog
    );

vdialogItem *vdialogGetDrag(
    vdialog                        *dialog
    );

vspringSolution *vdialogGetSolution(
    vdialog                        *dialog
    );

int vdialogGetItemCount(
    vdialog                        *dialog
    );

vdialogItem *vdialogGetItemAt(
    vdialog                        *dialog,
    int                             index
    );

int vdialogGetItemIndex(
    vdialog                        *dialog,
    vdialogItem                    *item
    );

vdialogItem *vdialogFindItem(
    vdialog                        *dialog,
    const vname                    *tag
    );

vdialogFocusCommandClass *vdialogGetDefaultFocusCommandClass(
    void
    );

vdialogFocusCommand *vdialogCreateFocusCommand(
    void
    );

void vdialogInitFocusCommand(
    vdialogFocusCommand            *command
    );

/*
 * dialog items
 */

vdialogItemClass *vdialogGetDefaultItemClass(
    void
    );

vdialogLabelItemClass *vdialogGetLabelItemClass(
    void
    );

vdialogLineItemClass *vdialogGetLineItemClass(
    void
    );

vdialogBoxItemClass *vdialogGetBoxItemClass(
    void
    );

vdialogItem *vdialogCreateItemOfClass(
    vdialogItemClass               *clas
    );

vdialogItem *vdialogCreateItem(
    void
    );

vdialogLabelItem *vdialogCreateLabelItem(
    void
    );

vdialogLineItem *vdialogCreateLineItem(
    void
    );

vdialogBoxItem *vdialogCreateBoxItem(
    void
    );

vdialogItem *vdialogCloneItem(
    vdialogItem                    *item
    );

void vdialogInitItemOfClass(
    vdialogItem                    *item,
    vdialogItemClass               *clas
    );

void vdialogInitItem(
    vdialogItem                    *item
    );

void vdialogInitLabelItem(
    vdialogLabelItem               *item
    );

void vdialogInitLineItem(
    vdialogLineItem                *item
    );

void vdialogInitBoxItem(
    vdialogBoxItem                 *item
    );

void vdialogDestroyItem(
    vdialogItem                    *item
    );

void vdialogDestroyItemLater(
    vdialogItem                    *item
    );

void vdialogCopyItem(
    vdialogItem                    *item,
    vdialogItem                    *target
    );

void vdialogCopyInitItem(
    vdialogItem                    *item,
    vdialogItem                    *target
    );

vdialogItem *vdialogLoadItem(
    vresource                       resource
    );

void vdialogLoadInitItem(
    vdialogItem                    *item,
    vresource                       resource
    );

void vdialogStoreItem(
    vdialogItem                    *item,
    vresource                       resource
    );

void vdialogSetItemAttribute(
    vdialogItem                    *item,
    const vname                    *attr,
    const void                     *value
    );

void vdialogSetAllItemAttributes(
    vdialogItem                    *item,
    vdict                          *attr2value
    );

const void *vdialogGetItemAttribute(
    vdialogItem                    *item,
    const vname                    *attr
    );

void vdialogGetAllItemAttributes(
    vdialogItem                    *item,
    vdict                          *attr2value
    );

void vdialogGetItemContextAttributes(
    vdialogItem                    *item,
    vdict                          *attr2value
    );

void vdialogChangedItemParentAttribute(
    vdialogItem                    *item,
    const vname                    *attr,
    vdict                          *context
    );

void vdialogChangedItemAttribute(
    vdialogItem                    *item,
    const vname                    *attr,
    vdict                          *context
    );

void vdialogChangedItemChildAttribute(
    vdialogItem                    *item,
    const vname                    *attr,
    vdict                          *context
    );

void vdialogChangedItemAttributeNone(
    vdialogItem                    *item,
    const vname                    *attr
    );

void vdialogChangedItemAttributeValue(
    vdialogItem                    *item,
    const vname                    *attr,
    const void                     *oldValue,
    const void                     *value
    );

void vdialogUpdateItemAttribute(
    vdialogItem                    *item,
    const vname                    *attr
    );

void vdialogUpdateAllItemAttributes(
    vdialogItem                    *item
    );

const void *vdialogAssociateItemAttribute(
    vdialogItem                    *item,
    const vname                    *attr,
    const vname                    *tag
    );

void vdialogAssociateAllItemAttributes(
    vdialogItem                    *item,
    const vname                    *tag,
    vdict                          *attr2value
    );

void vdialogPropagateItemChange(
    vdialogItem                    *item,
    const vname                    *attr,
    const vname                    *tag,
    const void                     *value
    );

void vdialogPropagateItemChangeDict(
    vdialogItem                    *item,
    const vname                    *attr,
    vdict                          *tag2value
    );

void vdialogPropagateItemChangeDictFromParent(
    vdialogItem                    *item,
    const vname                    *attr,
    vdict                          *tag2value
    );

void vdialogHelpItem(
    vdialogItem                    *item
    );

vbool vdialogDisplayItemHelp(
    vdialogItem                    *item,
    vhelprequest		   *request
    );

void vdialogDumpItem(
    vdialogItem                    *item,
    FILE                           *stream
    );

void vdialogOpenItem(
    vdialogItem                    *item
    );

void vdialogCloseItem(
    vdialogItem                    *item
    );

void vdialogShowItem(
    vdialogItem                    *item
    );

void vdialogHideItem(
    vdialogItem                    *item
    );

void vdialogEnableItem(
    vdialogItem                    *item
    );

void vdialogDisableItem(
    vdialogItem                    *item
    );

void vdialogFocusItem(
    vdialogItem                    *item
    );

void vdialogUnfocusItem(
    vdialogItem                    *item
    );

vbool vdialogTestFocusItem(
    vdialogItem                    *item,
    vevent			   *event
    );

vbool vdialogTestUnfocusItem(
    vdialogItem                    *item,
    vevent			   *event
    );

vbool vdialogTestFocusItemInDialog(
    vdialogItem                    *item,
    vevent			   *event
    );

void vdialogConfirmItem(
    vdialogItem                    *item
    );

void vdialogUnconfirmItem(
    vdialogItem                    *item
    );

void vdialogActivateItem(
    vdialogItem                    *item
    );

void vdialogDeactivateItem(
    vdialogItem                    *item
    );

void vdialogInvalItemRect(
    vdialogItem                    *item,
    const vrect                    *rect,
    int                             flags
    );		      

void vdialogInvalItem(
    vdialogItem                    *item,
    int                             flags
    );		      

void vdialogScrollItemRect(
    vdialogItem                    *item,
    const vrect                    *rect,
    int                             dx,
    int                             dy,
    int                             flags
    );		      

void vdialogNotifyItem(
    vdialogItem                    *item,
    vevent                         *event
    );

void vdialogGetItemMinSize(
    vdialogItem                    *item,
    int                            *w,
    int                            *h
    );

void vdialogGetItemNaturalSize(
    vdialogItem                    *item,
    int                            *w,
    int                            *h
    );

void vdialogGetItemDecorationSizes(
    vdialogItem                   *item,
    int                           *top,
    int                           *left,
    int                           *bottom,
    int                           *right
    );

int vdialogGetItemNaturalSeparation(
    vdialogItem                    *item,
    vdialogItem			   *to,
    unsigned int		    which
    );

void vdialogConstrainItemSize(
    vdialogItem                    *item,
    int                            *w,
    int                            *h
    );

void vdialogDrawItem(
    vdialogItem                    *item
    );

void vdialogDrawItemWith(
    vdialogItem                    *item,
    vdrawcontext                   *context
    );

void vdialogDrawItemBackgroundWith(
    vdialogItem                    *item,
    vdrawcontext                   *context
    );

void vdialogDrawItemBorderWith(
    vdialogItem                    *item,
    vdrawcontext                   *context
    );

void vdialogDrawItemImageWith(
    vdialogItem                    *item,
    vdrawcontext                   *context
    );

void vdialogDrawItemTitleWith(
    vdialogItem                    *item,
    vdrawcontext                   *context
    );

void vdialogDrawItemContentWith(
    vdialogItem                    *item,
    vdrawcontext                   *context
    );

void vdialogDrawItemFocus(
    vdialogItem                    *item
    );

void vdialogDrawItemFocusWith(
    vdialogItem                    *item,
    vdrawcontext                   *context
    );

void vdialogOutlineConfirmItem(
    vdialogItem                    *item
    );

void vdialogOutlineConfirmItemWith(
    vdialogItem                    *item,
    vdrawcontext                   *context
    );

void vdialogOutlineAbandonItem(
    vdialogItem                    *item
    );

void vdialogOutlineAbandonItemWith(
    vdialogItem                    *item,
    vdrawcontext                   *context
    );

void vdialogItemDrawDevice(
    vdialogItem                    *item
    );

vdrawcontext  *vdialogCreateItemDrawcontext(
    vdialogItem                    *item
    );

void vdialogSetItemDraw(
    vdialogItem                    *item
    );

void vdialogSetItemPenAttributes(
    vdialogItem                    *item,
    vdrawpen                       *pen
    );

int vdialogHandleItemButtonDown(
    vdialogItem                    *item,
    vevent                         *event
    );

int vdialogHandleItemButtonUp(
    vdialogItem                    *item,
    vevent                         *event
    );

int vdialogHandleItemDrag(
    vdialogItem                    *item,
    vevent                         *event
    );

int vdialogHandleItemDetail(
    vdialogItem                    *item,
    vevent                         *event
    );

int vdialogHandleItemMotion(
    vdialogItem                    *item,
    vevent                         *event
    );

int vdialogHandleItemKeyDown(
    vdialogItem                    *item,
    vevent                         *event
    );

int vdialogHandleItemKeyUp(
    vdialogItem                    *item,
    vevent                         *event
    );

void vdialogSetItemTag(
    vdialogItem                    *item,
    const vname                    *tag
    );

void vdialogSetItemNotify(
    vdialogItem                    *item,
    vdialogItemNoteProc	            noteProc
    );

void vdialogSetItemData(
    vdialogItem                    *item,
    const void                     *data
    );

void vdialogSetItemTitle(
    vdialogItem                    *item,
    const vchar                    *title
    );

void vdialogSetItemTitleScribed(
    vdialogItem                    *item,
    vscribe                        *scribe
    );

void vdialogSetItemCursor(
    vdialogItem                    *item,
    vcursor                        *cursor
    );

void vdialogSetItemCursorOwned(
    vdialogItem                    *item,
    vcursor                        *cursor
    );

void vdialogSetItemMenu(
    vdialogItem                    *item,
    vmenu                          *menu
    );

void vdialogSetItemDropsite(
    vdialogItem                    *item,
    vdropsite                      *dropsite
    );

void vdialogSetItemFont(
    vdialogItem                    *item,
    vfont                          *font
    );

void vdialogSetItemForeground(
    vdialogItem                    *item,
    vcolor                         *foreground
    );

void vdialogSetItemBackground(
    vdialogItem                    *item,
    vcolor                         *background
    );

void vdialogSetItemImage(
    vdialogItem                    *item,
    vimage                         *image
    );

void vdialogSetItemImageOwned(
    vdialogItem                    *item,
    vimage                         *image
    );

void vdialogSetItemSpace(
    vdialogItem                    *item,
    vcommandSpace                  *space
    );

void vdialogSetItemSpaceOwned(
    vdialogItem                    *item,
    vcommandSpace                  *space
    );

void vdialogSetItemItemList(
    vdialogItem                    *item,
    vdialogItemList                *itemList
    );

void vdialogSetItemMnemonic(
    vdialogItem                    *item,
    int                             mnemonic
    );

void vdialogSetItemFocusable(
    vdialogItem                    *item,
    int                             flag
    );

void vdialogSetItemClickFocusable(
    vdialogItem                    *item,
    int                             flag
    );

void vdialogSetItemText(
    vdialogItem                    *item,
    int                             flag
    );

void vdialogSetItemBorder(
    vdialogItem                    *item,
    int                             flag
    );

void vdialogSetItemImageMask(
    vdialogItem                    *item,
    int                             flag
    );

void vdialogSetItemRect(
    vdialogItem                    *item,
    const vrect                    *rect
    );

void vdialogSetItemField(
    vdialogItem                    *item,
    vobservable                    *field
);

void vdialogSetItemObserving(
   vdialogItem                     *item,
   vbool                            onOff
);

void vdialogSetItemDefersHelp(
   vdialogItem                     *item,
   int                              onOff
);

vobservable *vdialogGetItemField(
    vdialogItem                    *item
);

vobjectAttributed *vdialogGetItemObject(
    vdialogItem                    *item
    );

vloadable *vdialogGetItemLoadable(
    vdialogItem			   *item
    );

vdialogItemClass *vdialogGetItemClass(
    vdialogItem                    *item
    );

const vname *vdialogGetItemTag(
    vdialogItem                    *item
    );

vdialogItemNoteProc vdialogGetItemNotify(
    vdialogItem                    *item
    );

const void *vdialogGetItemData(
    vdialogItem                    *item
    );

const vchar *vdialogGetItemTitle(
    vdialogItem                    *item
    );

vcursor *vdialogGetItemCursor(
    vdialogItem                    *item
    );

vmenu *vdialogGetItemMenu(
    vdialogItem                    *item
    );

vdropsite *vdialogGetItemDropsite(
    vdialogItem                    *item
    );

vfont *vdialogGetItemFont(
    vdialogItem                    *item
    );

vcolor *vdialogGetItemForeground(
    vdialogItem                    *item
    );

vcolor *vdialogGetItemBackground(
    vdialogItem                    *item
    );

vimage *vdialogGetItemImage(
    vdialogItem                    *item
    );

vcommandSpace *vdialogGetItemSpace(
    vdialogItem                    *item
    );

vdialogItemList *vdialogGetItemItemList(
    vdialogItem                    *item
    );

int vdialogGetItemMnemonic(
    vdialogItem                    *item
    );

int vdialogItemIsShown(
    vdialogItem                    *item
    );

int vdialogItemIsEnabled(
    vdialogItem                    *item
    );

int vdialogItemIsFocusable(
    vdialogItem                    *item
    );

int vdialogItemIsClickFocusable(
    vdialogItem                    *item
    );

int vdialogItemIsText(
    vdialogItem                    *item
    );

vbool vdialogItemIsObserving(
    vdialogItem                    *item
);

vbool vdialogItemIsValid(
    vdialogItem                    *item
    );

int vdialogItemHasBorder(
    vdialogItem                    *item
    );

int vdialogItemIsImageMask(
    vdialogItem                    *item
    );

int vdialogItemIsOpen(
    vdialogItem                    *item
    );

int vdialogItemIsFocused(
    vdialogItem                    *item
    );

int vdialogItemIsConfirmed(
    vdialogItem                    *item
    );

int vdialogItemIsActivated(
    vdialogItem                    *item
    );

int vdialogItemIsVisible(
    vdialogItem                    *item
    );

int vdialogItemFocusIsVisible(
    vdialogItem                    *item
    );

int vdialogItemCanFocus(
    vdialogItem                    *item
    );

int vdialogItemIsFocusConfirmable(
    vdialogItem                    *item
    );

int vdialogItemDefersHelp(
    vdialogItem                    *item
    );

const vrect *vdialogGetItemRect(
    vdialogItem                    *item
    );

int vdialogGetItemX(
    vdialogItem                    *item
    );

int vdialogGetItemY(
    vdialogItem                    *item
    );

int vdialogGetItemW(
    vdialogItem                    *item
    );

int vdialogGetItemH(
    vdialogItem                    *item
    );

int vdialogItemContainsPoint(
    vdialogItem                    *item,
    int                             x,
    int                             y
    );

int vdialogItemHasKeyMap(
    vdialogItem                    *item
    );

int vdialogItemHasKeyDispatch(
    vdialogItem                    *item
    );

vdict *vdialogGetItemKeyMap(
    vdialogItem                    *item
    );

vdict *vdialogGetItemKeyDispatch(
    vdialogItem                    *item
    );

const vname *vdialogLoadItemKeyMap(
    vdialogItem                    *item,
    vkeyStroke                      key
    );

const void *vdialogLoadItemKeyDispatch(
    vdialogItem                    *item,
    vkeyStroke                      key
    );

vdialog *vdialogDetermineItemDialog(
    vdialogItem                    *item
    );

vwindow *vdialogDetermineItemWindow(
    vdialogItem                    *item
    );

vcursor *vdialogDetermineItemCursor(
    vdialogItem                    *item
    );

vfont *vdialogDetermineItemFont(
    vdialogItem                    *item
    );

vcolor *vdialogDetermineItemForeground(
    vdialogItem                    *item
    );

vcolor *vdialogDetermineItemBackground(
    vdialogItem                    *item
    );

vcolor *vdialogDetermineItemColor(
    vdialogItem                    *item,
    int                             id
    );

void vdialogDetermineItemColorScheme(
    vdialogItem                    *item,
    unsigned long                   flags,
    vcolorScheme                   *scheme
    );

void vdialogDetermineItemColorSchemeState(
    vdialogItem                    *item,
    unsigned long                   flags,
    vcolorScheme                   *scheme
    );

void vdialogDetermineItemColorSchemeFrom(
    vdialogItem                    *item,
    vcolorScheme                   *known,
    unsigned long                   flags,
    vcolorScheme                   *scheme
    );

vimage *vdialogDetermineItemImage(
    vdialogItem                    *item
    );

int vdialogDetermineItemLineWidth(
    vdialogItem                    *item
    );

int vdialogDetermineItemShown(
    vdialogItem                    *item
    );

int vdialogDetermineItemEnabled(
    vdialogItem                    *item
    );

/*
 * dialog item lists
 */

vdialogItemListClass *vdialogGetDefaultItemListClass(
    void
    );

vdialogItemList *vdialogCreateItemListOfClass(
    vdialogItemListClass           *clas
    );

vdialogItemList *vdialogCreateItemList(
    void
    );

vdialogItemList *vdialogCloneItemList(
    vdialogItemList                *itemList
    );

void vdialogInitItemListOfClass(
    vdialogItemList                *itemList, 
    vdialogItemListClass           *clas
    );

void vdialogInitItemList(
    vdialogItemList                *itemList
    );

void vdialogDestroyItemList(
    vdialogItemList                *itemList
    );

void vdialogCopyItemList(
    vdialogItemList                *itemList,
    vdialogItemList                *targetList
    );

void vdialogCopyInitItemList(
    vdialogItemList                *itemList,
    vdialogItemList                *targetList
    );

vdialogItemList *vdialogLoadItemList(
    vresource                       resource
    );

void vdialogLoadInitItemList(
    vdialogItemList                *itemList,
    vresource                       resource
    );

void vdialogStoreItemList(
    vdialogItemList                *itemList,
    vresource                       resource
    );

vbool vdialogDisplayItemListHelp(
    vdialogItemList                *itemList,
    vhelprequest		   *request
    );

void vdialogPropagateItemListChangeDictFromParent(
    vdialogItemList                *itemList,
    const vname                    *attr,
    vdict                          *tag2value
    );

void vdialogChangedItemListParentAttribute(
    vdialogItemList                *itemList,
    const vname                    *attr,
    vdict                          *context
    );

void vdialogChangedItemListAttribute(
    vdialogItemList                *itemList,
    const vname                    *attr,
    vdict                          *context
    );

void vdialogChangedItemListChildAttribute(
    vdialogItemList                *itemList,
    const vname                    *attr,
    vdict                          *context
    );

void vdialogUpdateItemListAttribute(
    vdialogItemList                *itemList,
    const vname                    *attr
    );

void vdialogUpdateAllItemListAttributes(
    vdialogItemList                *itemList
    );

void vdialogAppendItemListItem(
    vdialogItemList                *itemList,
    vdialogItem                    *item
    );

void vdialogInsertItemListItem(
    vdialogItemList                *itemList,
    vdialogItem                    *item,
    int                             index
    );

vdialogItem *vdialogRemoveItemListIndex(
    vdialogItemList                *itemList,
    int                             index
    );

vdialogItem *vdialogRemoveItemListItem(
    vdialogItemList                *itemList,
    vdialogItem                    *item
    );

void vdialogSetItemListIndexIndex(
    vdialogItemList                *itemList,
    int                             itemIndex,
    int                             index
    );

void vdialogSetItemListItemIndex(
    vdialogItemList                *itemList,
    vdialogItem                    *item,
    int                             index
    );

vdialogItem *vdialogReplaceItemListItemAt(
    vdialogItemList                *itemList,
    int                             index,
    vdialogItem                    *item
    );

void vdialogOpenItemList(
    vdialogItemList                *itemList
    );

void vdialogCloseItemList(
    vdialogItemList                *itemList
    );

void vdialogFocusItemList(
    vdialogItemList                *itemList
    );

void vdialogUnfocusItemList(
    vdialogItemList                *itemList
    );

vbool vdialogTestFocusItemList(
    vdialogItemList                *itemList,
    vevent                         *event
    );

vbool vdialogTestUnfocusItemList(
    vdialogItemList                *itemList,
    vevent                         *event
    );

void vdialogConfirmItemList(
    vdialogItemList                *itemList
    );

void vdialogUnconfirmItemList(
    vdialogItemList                *itemList
    );

void vdialogActivateItemList(
    vdialogItemList                *itemList
    );

void vdialogDeactivateItemList(
    vdialogItemList                *itemList
    );

void vdialogDrawItemList(
    vdialogItemList                *itemList
    );

void vdialogDrawItemListWith(
    vdialogItemList                *itemList,
    vdrawcontext                   *context
    );

int vdialogHandleItemListButtonDown(
    vdialogItemList                *itemList,
    vevent                         *event
    );

int vdialogHandleItemListMotion(
    vdialogItemList                *itemList,
    vevent                         *event
    );

void vdialogMoveItemListFocus(
    vdialogItemList                *itemList,
    int                             direct,
    int                             text
    );

int vdialogTestMoveItemListFocus(
    vdialogItemList                *itemList,
    int                             direct,
    int                             text,
    int				    wrap,
    vevent			   *event
    );

void vdialogArrangeItemList(
    vdialogItemList                *itemList,
    const vrect                    *rect
    );

void vdialogCalcItemListMinSize(
    vdialogItemList                *itemList,
    int                            *w,
    int                            *h
    );

void vdialogSetItemListFocusIndex(
    vdialogItemList                *itemList,
    int                             index
    );

void vdialogSetItemListFocus(
    vdialogItemList                *itemList,
    vdialogItem                    *focus
    );

vbool vdialogTestSetItemListFocusIndex(
    vdialogItemList                *itemList,
    int                             index,
    vevent			   *event
    );

vbool vdialogTestSetItemListFocus(
    vdialogItemList                *itemList,
    vdialogItem                    *focus,
    vevent			   *event
    );

void vdialogSetItemListConfirm(
    vdialogItemList                *itemList,
    vdialogItem                    *confirm
    );

void vdialogSetItemListAbandon(
    vdialogItemList                *itemList,
    vdialogItem                    *abandon
    );

void vdialogSetItemListDefFocus(
    vdialogItemList                *itemList,
    vdialogItem                    *defFocus
    );

void vdialogSetItemListDrag(
    vdialogItemList                *itemList,
    vdialogItem                    *drag
    );

void vdialogSetItemListSolution(
    vdialogItemList                *itemList,
    vspringSolution                *solution
    );

void vdialogSetItemListOwner(
    vdialogItemList                *itemList,
    vobjectAttributed              *owner,
    vdialogItemListOwnerFuncs      *ownerFuncs
    );

vobjectList *vdialogGetItemListObjectList(
    vdialogItemList                *itemList
    );

vdialogItemListClass *vdialogGetItemListClass(
    vdialogItemList                *itemList
    );

int vdialogGetItemListItemCount(
    vdialogItemList                *itemList
    );

vdialogItem *vdialogGetItemListItemAt(
    vdialogItemList                *itemList,
    int                             index
    );

int vdialogGetItemListItemIndex(
    vdialogItemList                *itemList,
    vdialogItem                    *item
    );

int vdialogFindItemListItemIndex(
    vdialogItemList                *itemList,
    const vname                    *tag
    );

vdialogItem *vdialogFindItemListItem(
    vdialogItemList                *itemList,
    const vname                    *tag
    );

vdialogItem *vdialogRelocateItemListItem(
    vdialogItemList                *itemList,
    vdialogItem                    *item,
    vdialogItemList                *target
    );

int vdialogItemListFocusIsForward(
    vdialogItemList                *itemList
    );

int vdialogItemListFocusIsReverse(
    vdialogItemList                *itemList
    );

int vdialogItemListFocusIsText(
    vdialogItemList                *itemList
    );

int vdialogItemListFocusHasWrapped(
    vdialogItemList                *itemList
    );

int vdialogItemListIsOpen(
    vdialogItemList                *itemList
    );

int vdialogItemListIsFocused(
    vdialogItemList                *itemList
    );

int vdialogItemListIsConfirmed(
    vdialogItemList                *itemList
    );

int vdialogItemListIsActivated(
    vdialogItemList                *itemList
    );

int vdialogGetItemListFocusIndex(
    vdialogItemList                *itemList
    );

vdialogItem *vdialogGetItemListFocus(
    vdialogItemList                *itemList
    );

vdialogItem *vdialogGetItemListConfirm(
    vdialogItemList                *itemList
    );

vdialogItem *vdialogGetItemListAbandon(
    vdialogItemList                *itemList
    );

vdialogItem *vdialogGetItemListDefFocus(
    vdialogItemList                *itemList
    );

vdialogItem *vdialogGetItemListCurrentConfirm(
    vdialogItemList                *itemList
    );

vdialogItem *vdialogGetItemListDrag(
    vdialogItemList                *itemList
    );

vspringSolution *vdialogGetItemListSolution(
    vdialogItemList                *itemList
    );

vobjectAttributed *vdialogGetItemListOwner(
    vdialogItemList                *itemList
    );

vdialogItemListOwnerFuncs *vdialogGetItemListOwnerFuncs(
    vdialogItemList                *itemList
    );

vdialog *vdialogDetermineItemListDialog(
    vdialogItemList                *itemList
    );

vwindow *vdialogDetermineItemListWindow(
    vdialogItemList                *itemList
    );

vcursor *vdialogDetermineItemListCursor(
    vdialogItemList                *itemList
    );

vfont *vdialogDetermineItemListFont(
    vdialogItemList                *itemList
    );

int vdialogDetermineItemListLineWidth(
    vdialogItemList                *itemList
    );

void vdialogDetermineItemListBounds(
    vdialogItemList                *itemList,
    vrect                          *bounds
    );

void vdialogDetermineItemListContent(
    vdialogItemList                *itemList,
    vrect                          *content
    );

vdict *vdialogGetItemListKeyMap(
    vdialogItemList                *itemList
    );

vdict *vdialogGetItemListKeyDispatch(
    vdialogItemList                *itemList
    );

int vdialogDetermineItemListShown(
    vdialogItemList                *itemList
    );

int vdialogDetermineItemListEnabled(
    vdialogItemList                *itemList
    );

void vdialogDetermineItemListColorSchemeFrom(
    vdialogItemList                *itemList,
    vcolorScheme                   *known,
    unsigned long                   flags,
    vcolorScheme                   *scheme
    );

void vdialogItemListDrawDevice(
    vdialogItemList                *itemList
    );

vdrawcontext  *vdialogCreateItemListDrawcontext(
    vdialogItemList                *itemList
    );

void vdialogTransformItemListPoint(
    vdialogItemList                *itemList,
    int                             x,
    int                             y,
    int                            *rx,
    int                            *ry
    );

void vdialogTransformItemListRect(
    vdialogItemList                *itemList,
    const vrect                    *rect,
    vrect                          *rrect
    );

void vdialogTransformItemListRectClip(
    vdialogItemList                *itemList,
    const vrect                    *rect,
    vrect                          *rrect
    );

void vdialogTransformItemListEvent(
    vdialogItemList                *itemList,
    vevent                         *event
    );


/*
 * deprecated dialogs
 */

void vdialogDeleteItem(
    vdialog                        *dialog,
    vdialogItem                    *item
    );

/*
 * deprecated dialog items
 */

void vdialogDetermineItemColors(
    vdialogItem                    *item,
    int                            *ids,
    int                             count,
    vcolor                        **colors
    );

void vdialogDetermineItemColorsFrom(
    vdialogItem                    *item,
    long                            flags,
    vcolor                        **known,
    int                            *ids,
    int                             count,
    vcolor                        **colors
    );

/*
 * deprecated dialog item lists
 */

void vdialogDeleteItemListIndex(
    vdialogItemList                *itemList,
    int                             index
    );

void vdialogDeleteItemListItem(
    vdialogItemList                *itemList,
    vdialogItem                    *item
    );

void vdialogSetItemListItemAt(
    vdialogItemList                *itemList,
    int                             index,
    vdialogItem                    *item
    );

void vdialogDetermineItemListColorsFrom(
    vdialogItemList                *itemList,
    long                            flags,
    vcolor                        **known,
    int                            *ids,
    int                             count,
    vcolor                        **colors
    );

/*
 * * * * * * * * * * PRIVATE CONSTANT DEFINITIONS * * * * * * * * * *
 */

/*
 * dialogs
 */

enum {
    _vdialogCHANGED_SOLUTION       = 0x0001,
    _vdialogCHANGED_SIZE           = 0x0002,
    _vdialogRETAIN_FOCUS_ON_DEACTIVATE
                                   = 0x0004
};

/*
 * dialog items
 */

enum {
    _vdialogITEM_SHOWN	            = 0x0001,
    _vdialogITEM_ENABLED            = 0x0002,
    _vdialogITEM_FOCUSABLE          = 0x0004,
    _vdialogITEM_TEXT               = 0x0008,
    _vdialogITEM_OPEN               = 0x0010,
    _vdialogITEM_FOCUSED            = 0x0020,
    _vdialogITEM_OWN_TITLE          = 0x0040,
    _vdialogITEM_BORDER             = 0x0080,
    _vdialogITEM_IMAGE_MASK         = 0x0100,
    _vdialogITEM_CLICK_FOCUSABLE    = 0x0200,
    _vdialogITEM_ACTIVATED          = 0x0400,
    _vdialogITEM_OWN_CURSOR         = 0x0800,
    _vdialogITEM_OWN_IMAGE          = 0x1000,
    _vdialogITEM_OWN_SPACE          = 0x2000,
    _vdialogITEM_CONFIRMED          = 0x4000,
    _vdialogITEM_DEFERS_HELP        = 0x8000,
    _vdialogITEM_CAN_FOCUS          = 
	_vdialogITEM_ENABLED|_vdialogITEM_FOCUSABLE
};

/*
 * dialog item lists
 */

enum {
    _vdialogITEM_LIST_FOCUS_FORWARD = 0x0001,
    _vdialogITEM_LIST_FOCUS_REVERSE = 0x0002,
    _vdialogITEM_LIST_FOCUS_TEXT    = 0x0004,
    _vdialogITEM_LIST_FOCUS_WRAP    = 0x0008,
    _vdialogITEM_LIST_FOCUSED       = 0x0010,
    _vdialogITEM_LIST_OPEN          = 0x0020,
    _vdialogITEM_LIST_ACTIVATED     = 0x0040,
    _vdialogITEM_LIST_CONFIRMED     = 0x0080,
    _vdialogITEM_LIST_IN_CLOSE      = 0x0100
};

/*
 * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * *
 */

/*
 * dialog item lists
 */

struct vdialogItemList {
    vobjectList                     list;
    unsigned short                  flags;
    short			    focus;
    short			    confirm;
    short			    abandon;
    short			    defFocus;
    vdialogItem                    *drag;
    vspringSolution                *solution;
    vobjectAttributed              *owner;
    vdialogItemListOwnerFuncs      *ownerFuncs;
};

#define vdialogITEM_LIST_CLASS(SUPER, LIST, ITEM)                             \
    vobjectLIST_CLASS(SUPER, LIST, ITEM);                                     \
    vclassMETHOD(vdialogOPEN_ITEM_LIST, (LIST *itemList));                    \
    vclassMETHOD(vdialogCLOSE_ITEM_LIST, (LIST *itemList));                   \
    vclassMETHOD(vdialogFOCUS_ITEM_LIST, (LIST *itemList));                   \
    vclassMETHOD(vdialogUNFOCUS_ITEM_LIST, (LIST *itemList));                 \
    vclassMETHOD_RET(vdialogTEST_FOCUS_ITEM_LIST, vbool,                      \
		     (LIST *itemList, vevent *event));                        \
    vclassMETHOD_RET(vdialogTEST_UNFOCUS_ITEM_LIST, vbool,                    \
		     (LIST *itemList, vevent *event));                        \
    vclassMETHOD(vdialogCONFIRM_ITEM_LIST, (LIST *itemList));                 \
    vclassMETHOD(vdialogUNCONFIRM_ITEM_LIST, (LIST *itemList));               \
    vclassMETHOD(vdialogACTIVATE_ITEM_LIST, (LIST *itemList));                \
    vclassMETHOD(vdialogDEACTIVATE_ITEM_LIST, (LIST *itemList));              \
    vclassMETHOD(vdialogDRAW_ITEM_LIST, (LIST *itemList));                    \
    vclassMETHOD(vdialogDRAW_ITEM_LIST_WITH,                                  \
		 (LIST *itemList, vdrawcontext *context));                    \
    vclassMETHOD_RET(vdialogHANDLE_ITEM_LIST_BUTTON_DOWN, int,                \
		     (LIST *itemList, vevent *event));                        \
    vclassMETHOD_RET(vdialogHANDLE_ITEM_LIST_MOTION, int,                     \
		     (LIST *itemList, vevent *event));                        \
    vclassMETHOD_RET(vdialogTEST_MOVE_ITEM_LIST_FOCUS, int,                   \
		     (LIST *itemList, int direct, int text, int wrap,         \
		      vevent *event));                                        \
    vclassMETHOD(vdialogMOVE_ITEM_LIST_FOCUS,                                 \
		 (LIST *itemList, int direct, int text));                     \
    vclassMETHOD(vdialogARRANGE_ITEM_LIST,                                    \
		 (LIST *itemList, const vrect *rect));                        \
    vclassMETHOD(vdialogCALC_ITEM_LIST_MIN_SIZE,                              \
		 (LIST *itemList, int *w, int *h));                           \
    vclassMETHOD(vdialogSET_ITEM_LIST_FOCUS_INDEX,                            \
		 (LIST *itemList, int index));                                \
    vclassMETHOD_RET(vdialogTEST_SET_ITEM_LIST_FOCUS_INDEX, vbool,            \
		 (LIST *itemList, int index, vevent *event));                 \
    vclassMETHOD(vdialogSET_ITEM_LIST_CONFIRM,                                \
		 (LIST *itemList, ITEM *confirm));                            \
    vclassMETHOD(vdialogSET_ITEM_LIST_ABANDON,                                \
		 (LIST *itemList, ITEM *abandon));                            \
    vclassMETHOD(vdialogSET_ITEM_LIST_DEF_FOCUS,                              \
		 (LIST *itemList, ITEM *defFocus));                           \
    vclassMETHOD(vdialogSET_ITEM_LIST_DRAG, (LIST *itemList, ITEM *drag));    \
    vclassMETHOD(vdialogSET_ITEM_LIST_SOLUTION,                               \
		 (LIST *itemList, vspringSolution *solution));                \
    vclassMETHOD(vdialogSET_ITEM_LIST_OWNER,                                  \
		 (LIST *itemList, vobjectAttributed *owner,                   \
		  vdialogItemListOwnerFuncs *ownerFuncs));                    \
    vclassMETHOD_RET(vdialogDETERMINE_ITEM_LIST_DIALOG, vdialog *,            \
		     (LIST *itemList));                                       \
    vclassMETHOD_RET(vdialogDETERMINE_ITEM_LIST_CURSOR, vcursor *,            \
		     (LIST *itemList));                                       \
    vclassMETHOD_RET(vdialogDETERMINE_ITEM_LIST_FONT, vfont *,                \
		     (LIST *itemList));                                       \
    vclassMETHOD_RET(vdialogDETERMINE_ITEM_LIST_LINE_WIDTH, int,              \
		     (LIST *itemList));                                       \
    vclassMETHOD(vdialogDETERMINE_ITEM_LIST_BOUNDS,                           \
		 (LIST *itemList, vrect *bounds));                            \
    vclassMETHOD(vdialogDETERMINE_ITEM_LIST_CONTENT,                          \
		 (LIST *itemList, vrect *content));                           \
    vclassMETHOD_RET(vdialogGET_ITEM_LIST_KEY_MAP, vdict *,                   \
		     (LIST *itemList));                                       \
    vclassMETHOD_RET(vdialogGET_ITEM_LIST_KEY_DISPATCH, vdict *,              \
		     (LIST *itemList));                                       \
    vclassMETHOD_RET(vdialogDETERMINE_ITEM_LIST_SHOWN, int,                   \
		     (LIST *itemList));                                       \
    vclassMETHOD_RET(vdialogDETERMINE_ITEM_LIST_ENABLED, int,                 \
		     (LIST *itemList));                                       \
    vclassMETHOD(vdialogITEM_LIST_DRAW_DEVICE, (LIST *itemList));             \
    vclassMETHOD_RET(vdialogCREATE_ITEM_LIST_DRAWCONTEXT, vdrawcontext *,     \
		     (LIST *itemList));                                       \
    vclassMETHOD(vdialogTRANSFORM_ITEM_LIST_POINT,                            \
		 (LIST *itemList, int x, int y, int *rx, int *ry));           \
    vclassMETHOD(vdialogTRANSFORM_ITEM_LIST_RECT,                             \
		 (LIST *itemList, const vrect *rect, vrect *rrect));          \
    vclassMETHOD(vdialogDETERMINE_ITEM_LIST_COLOR_SCHEME_FROM,                \
		 (LIST *itemList, vcolorScheme *known, unsigned long flags,   \
		  vcolorScheme *scheme))


struct vdialogItemListClass {
    vdialogITEM_LIST_CLASS(vdialogItemListClass, vdialogItemList, vdialogItem);
};

vportALIAS(vdialogDialogItemList, vdialogItemList)

/*
 * dialogs
 */

struct vdialog {
    vwindow                         window;
    vmenu                          *menu;
    vdialogHookFunc                 closeHook;
    unsigned short                  flags;
    vdialogItemList	           *itemList;
    vevent                         *updateSizeEvent;
};

#define vdialogCLASS(SUPER, DIALOG, NOTIFY, ITEM, LIST)                       \
    vwindowCLASS(SUPER, DIALOG, NOTIFY);                                      \
    vclassMETHOD_RET(vdialogCREATE_ITEM_LIST, LIST *, (DIALOG *dialog));      \
    vclassMETHOD(vdialogAPPEND_ITEM, (DIALOG *dialog, ITEM *item));           \
    vclassMETHOD(vdialogDELETE_ITEM, (DIALOG *dialog, ITEM *item));           \
    vclassMETHOD_RET(vdialogREMOVE_ITEM, ITEM *,			      \
		     (DIALOG *dialog, ITEM *item));		              \
    vclassMETHOD(vdialogSET_ITEM_INDEX,                                       \
		 (DIALOG *dialog, ITEM *item, int index));                    \
    vclassMETHOD(vdialogARRANGE, (DIALOG *dialog, const vrect *rect));        \
    vclassMETHOD(vdialogCALC_MIN_SIZE, (DIALOG *dialog, int *w, int *h));     \
    vclassMETHOD_RET(vdialogHOOK_CLOSE, int,                                  \
		     (DIALOG *dialog, vevent *event));                        \
    vclassMETHOD(vdialogSET_MENU, (DIALOG *dialog, vmenu *menu));             \
    vclassMETHOD(vdialogSET_CLOSE_HOOK,                                       \
		 (DIALOG *dialog, vdialogHookFunc closeHook));                \
    vclassMETHOD(vdialogSET_FOCUS, (DIALOG *dialog, ITEM *focus));            \
    vclassMETHOD_RET(vdialogTEST_SET_FOCUS, vbool,                            \
		     (DIALOG *dialog, ITEM *focus, vevent *event));           \
    vclassMETHOD(vdialogSET_CONFIRM, (DIALOG *dialog, ITEM *confirm));        \
    vclassMETHOD(vdialogSET_ABANDON, (DIALOG *dialog, ITEM *abandon));        \
    vclassMETHOD(vdialogSET_DEF_FOCUS, (DIALOG *dialog, ITEM *defFocus));     \
    vclassMETHOD(vdialogSET_DRAG, (DIALOG *dialog, ITEM *drag));              \
    vclassMETHOD(vdialogSET_SOLUTION,                                         \
		 (DIALOG *dialog, vspringSolution *solution))

struct vdialogClass {
    vdialogCLASS(vdialogClass, vdialog, vdialogNoteProc, vdialogItem,
		 vdialogItemList);
};

/*
 * dialog items
 */

typedef struct _vdialogItemExtra    _vdialogItemExtra;

struct vdialogItem {
    vobjectAttributed               object;
    vdialogItemNoteProc		    noteProc;
    const void			   *data;
    const vchar                    *title;
    _vdialogItemExtra              *extra;
    vdialogItemList                *parentItemList;
    vchar	                    mnemonic;
    unsigned short		    flags;
    vrect			    rect;
};

#define vdialogITEM_CLASS(SUPER, ITEM, NOTIFY)                                \
    vobjectATTRIBUTED_CLASS(SUPER, ITEM);                                     \
    vclassVARIABLE(vdialogITEM_CURSOR, vcursor*);                             \
    vclassVARIABLE(vdialogITEM_FONT, vfont*);                                 \
    vclassVARIABLE(vdialogITEM_FOREGROUND, vcolor*);                          \
    vclassVARIABLE(vdialogITEM_FOREGROUND_HILITE, vcolor*);                   \
    vclassVARIABLE(vdialogITEM_BACKGROUND, vcolor*);                          \
    vclassVARIABLE(vdialogITEM_BACKGROUND_HILITE, vcolor*);                   \
    vclassVARIABLE(vdialogITEM_IMAGE, vimage*);                               \
    vclassVARIABLE(vdialogITEM_WIDTH, short);                                 \
    vclassVARIABLE(vdialogITEM_HEIGHT, short);                                \
    vclassVARIABLE(vdialogITEM_FOCUS_EXTRA, short);                           \
    vclassVARIABLE(vdialogITEM_CONFIRM_EXTRA, short);                         \
    vclassMETHOD(vdialogOPEN_ITEM, (ITEM *item));                             \
    vclassMETHOD(vdialogCLOSE_ITEM, (ITEM *item));                            \
    vclassMETHOD(vdialogSHOW_ITEM, (ITEM *item));                             \
    vclassMETHOD(vdialogHIDE_ITEM, (ITEM *item));                             \
    vclassMETHOD(vdialogENABLE_ITEM, (ITEM *item));                           \
    vclassMETHOD(vdialogDISABLE_ITEM, (ITEM *item));                          \
    vclassMETHOD_RET(vdialogITEM_IS_VALID, vbool, (ITEM *item));              \
    vclassMETHOD(vdialogFOCUS_ITEM, (ITEM *item));                            \
    vclassMETHOD(vdialogUNFOCUS_ITEM, (ITEM *item));                          \
    vclassMETHOD_RET(vdialogTEST_FOCUS_ITEM, vbool,                           \
		     (ITEM *item, vevent *event));                            \
    vclassMETHOD_RET(vdialogTEST_UNFOCUS_ITEM, vbool,                         \
		     (ITEM *item, vevent *event));                            \
    vclassMETHOD(vdialogCONFIRM_ITEM, (ITEM *item));                          \
    vclassMETHOD(vdialogUNCONFIRM_ITEM, (ITEM *item));                        \
    vclassMETHOD(vdialogACTIVATE_ITEM, (ITEM *item));                         \
    vclassMETHOD(vdialogDEACTIVATE_ITEM, (ITEM *item));                       \
    vclassMETHOD(vdialogINVAL_ITEM_RECT,                                      \
		 (ITEM *item, const vrect *rect, int flags));                 \
    vclassMETHOD(vdialogSCROLL_ITEM_RECT,                                     \
		 (ITEM *item, const vrect *rect, int dx, int dy, int flags)); \
    vclassMETHOD(vdialogNOTIFY_ITEM, (ITEM *item, vevent *event));            \
    vclassMETHOD(vdialogOBSERVE_DIALOG_ITEM, (ITEM *item, vevent *event));    \
    vclassMETHOD(vdialogGET_ITEM_MIN_SIZE, (ITEM *item, int *w, int *h));     \
    vclassMETHOD(vdialogGET_ITEM_NATURAL_SIZE, (ITEM *item, int *w, int *h)); \
    vclassMETHOD(vdialogGET_ITEM_DECORATION_SIZES, (ITEM *item, int *top,     \
						    int *left, int *bottom,   \
						    int *right));             \
    vclassMETHOD_RET(vdialogGET_ITEM_NATURAL_SEPARATION, int,		      \
		     (ITEM *item, vdialogItem *to, unsigned int which ));     \
    vclassMETHOD(vdialogCONSTRAIN_ITEM_SIZE, (ITEM *item, int *w, int *h));   \
    vclassMETHOD(vdialogDRAW_ITEM, (ITEM *item));                             \
    vclassMETHOD(vdialogDRAW_ITEM_WITH, (ITEM *item, vdrawcontext *context)); \
    vclassMETHOD(vdialogDRAW_ITEM_BACKGROUND_WITH,                            \
		 (ITEM *item, vdrawcontext *context));                        \
    vclassMETHOD(vdialogDRAW_ITEM_BORDER_WITH,                                \
		 (ITEM *item, vdrawcontext *context));                        \
    vclassMETHOD(vdialogDRAW_ITEM_IMAGE_WITH,                                 \
		 (ITEM *item, vdrawcontext *context));                        \
    vclassMETHOD(vdialogDRAW_ITEM_TITLE_WITH,                                 \
		 (ITEM *item, vdrawcontext *context));                        \
    vclassMETHOD(vdialogDRAW_ITEM_CONTENT_WITH,                               \
		 (ITEM *item, vdrawcontext *context));                        \
    vclassMETHOD(vdialogDRAW_ITEM_FOCUS, (ITEM *item));                       \
    vclassMETHOD(vdialogDRAW_ITEM_FOCUS_WITH, (ITEM *item,                    \
					       vdrawcontext *context));       \
    vclassMETHOD(vdialogOUTLINE_CONFIRM_ITEM, (ITEM *item));                  \
    vclassMETHOD(vdialogOUTLINE_CONFIRM_ITEM_WITH, (ITEM *item,               \
						    vdrawcontext *context));  \
    vclassMETHOD(vdialogOUTLINE_ABANDON_ITEM, (ITEM *item));                  \
    vclassMETHOD(vdialogOUTLINE_ABANDON_ITEM_WITH, (ITEM *item,               \
						    vdrawcontext *context));  \
    vclassMETHOD(vdialogITEM_DRAW_DEVICE, (ITEM *item));                      \
    vclassMETHOD_RET(vdialogCREATE_ITEM_DRAWCONTEXT, vdrawcontext *,          \
		     (ITEM *item));                                           \
    vclassMETHOD(vdialogSET_ITEM_DRAW, (ITEM *item));                         \
    vclassMETHOD(vdialogSET_ITEM_PEN_ATTRIBUTES, (ITEM *item, vdrawpen *pen));\
    vclassMETHOD_RET(vdialogHANDLE_ITEM_BUTTON_DOWN, int,                     \
		     (ITEM *item, vevent *event));                            \
    vclassMETHOD_RET(vdialogHANDLE_ITEM_BUTTON_UP, int,                       \
		     (ITEM *item, vevent *event));                            \
    vclassMETHOD_RET(vdialogHANDLE_ITEM_DRAG, int,                            \
		     (ITEM *item, vevent *event));                            \
    vclassMETHOD_RET(vdialogHANDLE_ITEM_DETAIL, int,                          \
		     (ITEM *item, vevent *event));                            \
    vclassMETHOD_RET(vdialogHANDLE_ITEM_MOTION, int,                          \
		     (ITEM *item, vevent *event));                            \
    vclassMETHOD_RET(vdialogHANDLE_ITEM_KEY_DOWN, int,                        \
		     (ITEM *item, vevent *event));                            \
    vclassMETHOD_RET(vdialogHANDLE_ITEM_KEY_UP, int,                          \
		     (ITEM *item, vevent *event));                            \
    vclassMETHOD(vdialogSET_ITEM_NOTIFY, (ITEM *item, NOTIFY noteProc));      \
    vclassMETHOD(vdialogSET_ITEM_DATA, (ITEM *item, const void *data));       \
    vclassMETHOD(vdialogSET_ITEM_TITLE_SCRIBED,                               \
		 (ITEM *item, vscribe *scribe));                              \
    vclassMETHOD(vdialogSET_ITEM_CURSOR, (ITEM *item, vcursor *cursor));      \
    vclassMETHOD(vdialogSET_ITEM_CURSOR_OWNED, (ITEM *item, vcursor *cursor)); \
    vclassMETHOD(vdialogSET_ITEM_MENU, (ITEM *item, vmenu *menu));            \
    vclassMETHOD(vdialogSET_ITEM_DROPSITE, (ITEM *item, vdropsite *dropsite));\
    vclassMETHOD(vdialogSET_ITEM_FONT, (ITEM *item, vfont *font));            \
    vclassMETHOD(vdialogSET_ITEM_FOREGROUND,                                  \
		 (ITEM *item, vcolor *foreground));                           \
    vclassMETHOD(vdialogSET_ITEM_BACKGROUND,                                  \
		 (ITEM *item, vcolor *background));                           \
    vclassMETHOD(vdialogSET_ITEM_IMAGE, (ITEM *item, vimage *image));         \
    vclassMETHOD(vdialogSET_ITEM_IMAGE_OWNED, (ITEM *item, vimage *image));   \
    vclassMETHOD(vdialogSET_ITEM_SPACE, (ITEM *item, vcommandSpace *space));  \
    vclassMETHOD(vdialogSET_ITEM_SPACE_OWNED,                                 \
		 (ITEM *item, vcommandSpace *space));                         \
    vclassMETHOD(vdialogSET_ITEM_ITEM_LIST,                                   \
		 (ITEM *item, vdialogItemList *itemList));                    \
    vclassMETHOD(vdialogSET_ITEM_MNEMONIC, (ITEM *item, int mnemonic));       \
    vclassMETHOD(vdialogSET_ITEM_FOCUSABLE, (ITEM *item, int flag));          \
    vclassMETHOD(vdialogSET_ITEM_CLICK_FOCUSABLE, (ITEM *item, int flag));    \
    vclassMETHOD(vdialogSET_ITEM_TEXT, (ITEM *item, int flag));               \
    vclassMETHOD(vdialogSET_ITEM_BORDER, (ITEM *item, int flag));             \
    vclassMETHOD(vdialogSET_ITEM_IMAGE_MASK, (ITEM *item, int flag));         \
    vclassMETHOD(vdialogSET_ITEM_RECT, (ITEM *item, const vrect *rect));      \
    vclassMETHOD(vdialogSET_ITEM_FIELD, (ITEM *item, vobservable *field));    \
    vclassMETHOD(vdialogSET_ITEM_OBSERVING, (ITEM *item, vbool onOff));       \
    vclassMETHOD(vdialogSET_ITEM_DEFERS_HELP, (ITEM *item, int onOff));   \
    vclassMETHOD_RET(vdialogITEM_IS_FOCUS_CONFIRMABLE, int, (ITEM *item));    \
    vclassMETHOD(vdialogDETERMINE_ITEM_COLOR_SCHEME_FROM,                     \
		 (ITEM *item, vcolorScheme *known, unsigned long flags,       \
		  vcolorScheme *scheme))

struct vdialogItemClass {
    vdialogITEM_CLASS(vdialogItemClass, vdialogItem, vdialogItemNoteProc);
};

vportALIAS(vdialogLabelItem,	vdialogItem)
vportALIAS(vdialogLineItem,	vdialogItem)
vportALIAS(vdialogBoxItem,	vdialogItem)

typedef vspringArrangerClass	vdialogItemListArrangerClass;

/*
 * * * * * * * * * * PRIVATE FUNCTION PROTOTYPES * * * * * * * * * *
 */

vcursor *_vdialogGetItemDefaultCursor(vdialogItem *item);
short    _vdialogGetItemFocusExtra(vdialogItem *item);
short    _vdialogGetItemConfirmExtra(vdialogItem *item);

void	 _vdialogSetItemListOwnerNoFuncs(vdialogItemList *itemList,
					 vobjectAttributed *owner);
vdialogItemListArrangerClass *_vdialogGetDefaultItemListArrangerClass(void);

vobjectPartialChildIteratorClass *_vdialogGetPartialChildIteratorClass(void);
vobjectPartialChildIteratorClass *_vdialogGetItemPartialChildIteratorClass(
									void);

vbool _vdialogSetItemListFocusRecursively(
    vdialogItemList                *itemList,
    vdialogItem                    *focus
    );

void _vdialogSetItemClassFont(
    vobjectAttributedClass *clas,
    vfont *font
    );

/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * *
 */

/*
 * dialog items
 */

#define vdialogGetItemObject(i)     vportBASE_OBJECT((i), object)
#define vdialogGetItemLoadable(i) \
    vobjectGetLoadable(vdialogGetItemObject(i))

#define vdialogCreateItemOfClass(c) \
    ((vdialogItem*)vobjectCreateOfClass((vobjectClass*)(c)))
#define vdialogCreateItem() \
    vdialogCreateItemOfClass(vdialogGetDefaultItemClass())
#define vdialogCreateLabelItem() \
    vdialogCreateItemOfClass(vdialogGetLabelItemClass())
#define vdialogCreateLineItem() \
    vdialogCreateItemOfClass(vdialogGetLineItemClass())
#define vdialogCreateBoxItem() \
    vdialogCreateItemOfClass(vdialogGetBoxItemClass())
#define vdialogCloneItem(i) \
    ((vdialogItem*)vobjectClone(vdialogGetItemObject(i)))
#define vdialogInitItemOfClass(i, c) \
    vobjectInitOfClass(vdialogGetItemObject(i), (vobjectClass*)(c))
#define vdialogInitItem(i) \
    vdialogInitItemOfClass(i, vdialogGetDefaultItemClass())
#define vdialogInitLabelItem(i) \
    vdialogInitItemOfClass(i, vdialogGetLabelItemClass())
#define vdialogInitLineItem(i) \
    vdialogInitItemOfClass(i, vdialogGetLineItemClass())
#define vdialogInitBoxItem(i) \
    vdialogInitItemOfClass(i, vdialogGetBoxItemClass())
#define vdialogDestroyItemLater(i) \
    vobjectDestroyLater(vdialogGetItemObject(i))
#define vdialogCopyInitItem(i, t) \
    vobjectCopyInit(vdialogGetItemObject(i), vdialogGetItemObject(t))
#define vdialogCopyItem(i, t) \
    vobjectCopy(vdialogGetItemObject(i), vdialogGetItemObject(t))
#define vdialogStoreItem(i, r) \
    vobjectStore(vdialogGetItemObject(i), r)
#define vdialogLoadItem(r)        ((vdialogItem*)vobjectLoad(r))
#define vdialogLoadInitItem(i, r)   vobjectLoadInit(vdialogGetItemObject(i), r)
#define vdialogDestroyItem(i) \
    vobjectDestroy(vdialogGetItemObject(i))
#define vdialogDisplayItemHelp(i, r) \
    vobjectDisplayHelp(vdialogGetItemObject(i), r)


#define vdialogSetItemAttribute(i, a, v) \
    vobjectSetAttribute(vdialogGetItemObject(i), a, v)
#define vdialogSetAllItemAttributes(i, d) \
    vobjectSetAllAttributes(vdialogGetItemObject(i), d)
#define vdialogGetItemAttribute(i, a) \
    vobjectGetAttribute(vdialogGetItemObject(i), a)
#define vdialogGetAllItemAttributes(i, d) \
    vobjectGetAllAttributes(vdialogGetItemObject(i), d)
#define vdialogGetItemContextAttributes(i, d) \
    vobjectGetContextAttributes(vdialogGetItemObject(i), d)
#define vdialogChangedItemParentAttribute(i, a, d) \
    vobjectChangedParentAttribute(vdialogGetItemObject(i), a, d)
#define vdialogChangedItemAttribute(i, a, d) \
    vobjectChangedAttribute(vdialogGetItemObject(i), a, d)
#define vdialogChangedItemChildAttribute(i, a, d) \
    vobjectChangedChildAttribute(vdialogGetItemObject(i), a, d)
#define vdialogUpdateItemAttribute(i, a) \
    vobjectUpdateAttribute(vdialogGetItemObject(i), a)
#define vdialogUpdateAllItemAttributes(i) \
    vobjectUpdateAllAttributes(vdialogGetItemObject(i))
#define vdialogPropagateItemChangeDict(i, a, d) \
    vobjectPropagateChangeDict(vdialogGetItemObject(i), a, d)
#define vdialogHelpItem(i) \
    vobjectHelp(vdialogGetItemObject(i))
#define vdialogDumpItem(i, s) \
    vobjectDump(vdialogGetItemObject(i), s)

#define vdialogChangedItemAttributeNone(i, n) \
    vobjectChangedAttributeNone(vdialogGetItemObject(i), n)
#define vdialogChangedItemAttributeValue(i, n, o, v) \
    vobjectChangedAttributeValue(vdialogGetItemObject(i), n, o, v)
#define vdialogAssociateItemAttribute(i, a, n) \
    vobjectAssociateAttribute(vdialogGetItemObject(i), a, n)
#define vdialogAssociateAllItemAttributes(i, n, d) \
    vobjectAssociateAllAttributes(vdialogGetItemObject(i), n, d)
#define vdialogPropagateItemChange(i, a, n, v) \
    vobjectPropagateChange(vdialogGetItemObject(i), a, n, v)
#define vdialogPropagateItemChangeDictFromParent(i, a, d) \
    vobjectPropagateChangeDictFromParent(vdialogGetItemObject(i), a, d)

#define vdialogSetItemTitle(i, s) \
    vdialogSetItemTitleScribed(i, vcharScribe(s))

#define vdialogGetItemClass(i) \
    ((vdialogItemClass*)vobjectGetAttributedClass(vdialogGetItemObject(i)))
#define vdialogGetItemTag(i)         vobjectGetTag(vdialogGetItemObject(i))
#define vdialogGetItemNotify(i)	   ((i)->noteProc)
#define vdialogGetItemData(i)	   ((i)->data)
#define vdialogGetItemTitle(i)	   ((i)->title)
#define vdialogGetItemItemList(i)  ((i)->parentItemList)
#define vdialogGetItemMnemonic(i)  ((i)->mnemonic)
#define vdialogItemIsShown(i)     (((i)->flags&_vdialogITEM_SHOWN)     !=0)
#define vdialogItemIsEnabled(i)	  (((i)->flags&_vdialogITEM_ENABLED)   !=0)
#define vdialogItemIsFocusable(i) (((i)->flags&_vdialogITEM_FOCUSABLE) !=0)
#define vdialogItemIsClickFocusable(i) \
    (((i)->flags&_vdialogITEM_CLICK_FOCUSABLE)!=0)
#define vdialogItemIsText(i)	  (((i)->flags&_vdialogITEM_TEXT)      !=0)
#define vdialogItemHasBorder(i)	  (((i)->flags&_vdialogITEM_BORDER)    !=0)
#define vdialogItemIsImageMask(i) (((i)->flags&_vdialogITEM_IMAGE_MASK)!=0)
#define vdialogItemIsOpen(i)	  (((i)->flags&_vdialogITEM_OPEN)      !=0)
#define vdialogItemIsFocused(i)	  (((i)->flags&_vdialogITEM_FOCUSED)   !=0)
#define vdialogItemIsConfirmed(i) (((i)->flags&_vdialogITEM_CONFIRMED) !=0)
#define vdialogItemIsActivated(i) (((i)->flags&_vdialogITEM_ACTIVATED) !=0)
#define vdialogItemDefersHelp(i) \
    (((i)->flags&_vdialogITEM_DEFERS_HELP) !=0)
#define vdialogItemCanFocus(i) \
    (((i)->flags&_vdialogITEM_CAN_FOCUS)==_vdialogITEM_CAN_FOCUS)
#define vdialogGetItemRect(i)	   ((const vrect*)&(i)->rect)
#define vdialogGetItemX(i)         ((i)->rect.x)
#define vdialogGetItemY(i)	   ((i)->rect.y)
#define vdialogGetItemW(i)	   ((i)->rect.w)
#define vdialogGetItemH(i)	   ((i)->rect.h)
#define vdialogItemContainsPoint(i, x, y) vrectContainsPoint(&(i)->rect, x, y)

#define vdialogDetermineItemForeground(i) \
    vdialogDetermineItemColor(i, vdrawCOLOR_FOREGROUND)
#define vdialogDetermineItemBackground(i) \
    vdialogDetermineItemColor(i, vdrawCOLOR_BACKGROUND)

/*
 * dialog item lists
 */

#define vdialogGetItemListObjectList(l) vportBASE_OBJECT((l), list)

#define vdialogCreateItemListOfClass(c) \
    ((vdialogItemList*)vobjectCreateListOfClass((vobjectListClass*)(c)))
#define vdialogCreateItemList() \
    vdialogCreateItemListOfClass(vdialogGetDefaultItemListClass())
#define vdialogCloneItemList(l) \
    ((vdialogItemList*)vobjectCloneList(vdialogGetItemListObjectList(l)))
#define vdialogInitItemListOfClass(l, c) \
    vobjectInitListOfClass(vdialogGetItemListObjectList(l), \
			   (vobjectListClass*)(c))
#define vdialogInitItemList(l) \
    vdialogInitItemListOfClass(l, vdialogGetDefaultItemListClass())
#define vdialogDestroyItemList(l) \
    vobjectDestroyList(vdialogGetItemListObjectList(l))
#define vdialogCopyItemList(l, t) \
    vobjectCopyList(vdialogGetItemListObjectList(l), \
		    vdialogGetItemListObjectList(t))
#define vdialogStoreItemList(l, r) \
    vobjectStoreList(vdialogGetItemListObjectList(l), r)

#define vdialogDisplayItemListHelp(l, r) \
    vobjectDisplayHelp(vobjectGetListObject(vdialogGetItemListObjectList(l)), r)
#define vdialogChangedItemListParentAttribute(l, a, d) \
    vobjectChangedListParentAttribute(vdialogGetItemListObjectList(l), a, d)
#define vdialogChangedItemListAttribute(l, a, d) \
    vobjectChangedListAttribute(vdialogGetItemListObjectList(l), a, d)
#define vdialogChangedItemListChildAttribute(l, a, d) \
    vobjectChangedListChildAttribute(vdialogGetItemListObjectList(l), a, d)
#define vdialogUpdateItemListAttribute(l, a) \
    vobjectUpdateListAttribute(vdialogGetItemListObjectList(l), a)
#define vdialogUpdateAllItemListAttributes(l) \
    vobjectUpdateAllListAttributes(vdialogGetItemListObjectList(l))
#define vdialogAppendItemListItem(l, i) \
    vobjectAppendList(vdialogGetItemListObjectList(l), vdialogGetItemObject(i))
#define vdialogRemoveItemListIndex(l, i) \
    vobjectRemoveListIndex(vdialogGetItemListObjectList(l), i)
#define vdialogDeleteItemListIndex(l, i) \
    ((void) vdialogRemoveItemListIndex(l, i))
#define vdialogSetItemListIndexIndex(l, ii, i) \
    vobjectSetListIndexIndex(vdialogGetItemListObjectList(l), ii, i)
#define vdialogReplaceItemListItemAt(l, n, i) \
    vobjectReplaceListAt(vdialogGetItemListObjectList(l), n, \
			 vdialogGetItemObject(i))
#define vdialogSetItemListItemAt(l, n, i) \
    ((void) vdialogReplaceItemListItemAt(l, n, i))
#define vdialogPropagateItemListChangeDictFromParent(l, a, d) \
    vobjectPropagateListChangeDictFromParent(vdialogGetItemListObjectList(l), \
					     a, d)
#define vdialogInsertItemListItem(l, i, n) \
    vobjectInsertList(vdialogGetItemListObjectList(l), \
		      vdialogGetItemObject(i), n)
#define vdialogRemoveItemListItem(l, i) \
    vobjectRemoveList(vdialogGetItemListObjectList(l), vdialogGetItemObject(i))
#define vdialogDeleteItemListItem(l, i) \
    vobjectDeleteList(vdialogGetItemListObjectList(l), vdialogGetItemObject(i))
#define vdialogSetItemListItemIndex(l, i, n) \
    vobjectSetListIndex(vdialogGetItemListObjectList(l), \
			vdialogGetItemObject(i), n)

#define vdialogGetItemListClass(l) \
    ((vdialogItemListClass*) \
         vobjectGetListClass(vdialogGetItemListObjectList(l)))
#define vdialogGetItemListItemCount(l) \
    vobjectGetListCount(vdialogGetItemListObjectList(l))
#define vdialogGetItemListItemAt(l, n) \
    ((vdialogItem*)vobjectGetListAt(vdialogGetItemListObjectList(l), n))
#define vdialogGetItemListItemIndex(l, i) \
    vobjectGetListIndex(vdialogGetItemListObjectList(l), \
			vdialogGetItemObject(i))
#define vdialogFindItemListItemIndex(l, t) \
    vobjectFindListIndex(vdialogGetItemListObjectList(l), t)
#define vdialogFindItemListItem(l, t) \
    ((vdialogItem*)vobjectFindList(vdialogGetItemListObjectList(l), t))
#define vdialogRelocateItemListItem(l, i, t) \
    ((vdialogItem*)vobjectRelocateList \
         (vdialogGetItemListObjectList(l), vdialogGetItemObject(i), \
	  vdialogGetItemListObjectList(t)))
#define vdialogItemListFocusIsForward(l) \
    (((l)->flags&_vdialogITEM_LIST_FOCUS_FORWARD)!=0)
#define vdialogItemListFocusIsReverse(l) \
    (((l)->flags&_vdialogITEM_LIST_FOCUS_REVERSE)!=0)
#define vdialogItemListFocusIsText(l) \
    (((l)->flags&_vdialogITEM_LIST_FOCUS_TEXT)!=0)
#define vdialogItemListFocusHasWrapped(l) \
    (((l)->flags&_vdialogITEM_LIST_FOCUS_WRAP)!=0)
#define vdialogItemListIsOpen(l) \
    (((l)->flags&_vdialogITEM_LIST_OPEN)!=0)
#define vdialogItemListIsFocused(l) \
    (((l)->flags&_vdialogITEM_LIST_FOCUSED)!=0)
#define vdialogItemListIsConfirmed(l) \
    (((l)->flags&_vdialogITEM_LIST_CONFIRMED)!=0)
#define vdialogItemListIsActivated(l) \
    (((l)->flags&_vdialogITEM_LIST_ACTIVATED)!=0)
#define vdialogGetItemListFocusIndex(l) ((l)->focus)
#define vdialogGetItemListDrag(l)       ((l)->drag)
#define vdialogGetItemListSolution(l)   ((l)->solution)
#define vdialogGetItemListOwner(l)      ((l)->owner)
#define vdialogGetItemListOwnerFuncs(l) ((l)->ownerFuncs)

#define vdialogDetermineItemListWindow(l) \
    vdialogGetWindow(vdialogDetermineItemListDialog(l))

#define _vdialogSetItemListOwnerNoFuncs(i, o) \
    vdialogSetItemListOwner(i, o, NULL)

/*
 * dialogs
 */

#define vdialogGetWindow(d)         vportBASE_OBJECT((d), window)
#define vdialogGetObject(d)         vwindowGetObject(vdialogGetWindow(d))

#define vdialogCreateOfClass(c) \
    ((vdialog*)vwindowCreateOfClass((vwindowClass*)(c)))
#define vdialogCreate() \
    vdialogCreateOfClass(vdialogGetDefaultClass())
#define vdialogClone(d)           ((vdialog*)vwindowClone((vwindow*)(d)))
#define vdialogInitOfClass(d, c) \
    vwindowInitOfClass(vdialogGetWindow(d), (vwindowClass*)(c))
#define vdialogInit(d) \
    vdialogInitOfClass(d, vdialogGetDefaultClass())
#define vdialogCopyInit(d, t) \
    vwindowCopyInit(vdialogGetWindow(d), vdialogGetWindow(t))
#define vdialogCopy(d, t) \
    vwindowCopy(vdialogGetWindow(d), vdialogGetWindow(t))
#define vdialogStore(d, r) \
    vwindowStore(vdialogGetWindow(d), r)
#define vdialogLoad(r)            ((vdialog*)vwindowLoad(r))
#define vdialogLoadInit(d, r)       vwindowLoadInit(vdialogGetWindow(d), r)
#define vdialogDestroy(d) \
    vwindowDestroy(vdialogGetWindow(d))

#define vdialogMove(d, x, y)        vwindowMove(vdialogGetWindow(d), x, y)
#define vdialogResize(d, w, h)      vwindowResize(vdialogGetWindow(d), w, h)

#define vdialogSetTitle(d, s)       vwindowSetTitle(vdialogGetWindow(d), s)

#define vdialogGetClass(d) \
    ((vdialogClass*)vwindowGetClass(vdialogGetWindow(d)))

#define vdialogGetNotify(d) \
    ((vdialogNoteProc)vwindowGetNotify(vdialogGetWindow(d)))
#define vdialogSetNotify(d, n) \
    vwindowSetNotify((vwindow *)(d), (vwindowNoteProc)(n))

#define vdialogPlaceWindow(d, b, mx, my) \
    vwindowPlace(vdialogGetWindow(d), b, mx, my)
#define vdialogPlace(d, b, mx, my) \
    vwindowPlace(vdialogGetWindow(d), (vwindow *)(b), mx, my)

#define vdialogGetData(d)           vwindowGetData(vdialogGetWindow(d))
#define vdialogGetTitle(d)          vwindowGetTitle(vdialogGetWindow(d))
#define vdialogGetIcon(d)           vwindowGetIcon(vdialogGetWindow(d))
#define vdialogIsOpen(d)            vwindowIsOpen(vdialogGetWindow(d))
#define vdialogGetMaxW(d)           vwindowGetMaxW(vdialogGetWindow(d))
#define vdialogGetMaxH(d)           vwindowGetMaxH(vdialogGetWindow(d))
#define vdialogDisplayHelp(d, r)    vwindowDisplayHelp(vdialogGetWindow(d), r)
#define vdialogOpen(d)		    vwindowOpen(vdialogGetWindow(d))
#define vdialogClose(d)		    vwindowClose(vdialogGetWindow(d))
#define vdialogNotify(d, e)	    vwindowNotify(vdialogGetWindow(d), e)
#define vdialogSetData(d, p)	    vwindowSetData(vdialogGetWindow(d), p)
#define vdialogSetTitleScribed(d, s) \
    vwindowSetTitleScribed(vdialogGetWindow(d), s)
#define vdialogSetIcon(d, i)	    vwindowSetIcon(vdialogGetWindow(d), i)
#define vdialogSetMaxSize(d, x, y)  vwindowSetMaxSize(vdialogGetWindow(d), x, y)
#define vdialogGetMenu(d)	  ((d)->menu)
#define vdialogGetCloseHook(d)	  ((d)->closeHook)
#define vdialogGetItemList(d)    ((d)->itemList)
#define vdialogSetRetainFocusOnDeactivate(d, r) \
    if (r) (d)->flags |= _vdialogRETAIN_FOCUS_ON_DEACTIVATE; \
    else (d)->flags &= ~_vdialogRETAIN_FOCUS_ON_DEACTIVATE
#define vdialogGetRetainFocusOnDeactivate(d) \
    (((d)->flags&_vdialogRETAIN_FOCUS_ON_DEACTIVATE) != 0)
#define vdialogGetFocus(d)          vdialogGetItemListFocus((d)->itemList)
#define vdialogGetConfirm(d)        vdialogGetItemListConfirm((d)->itemList)
#define vdialogGetAbandon(d)        vdialogGetItemListAbandon((d)->itemList)
#define vdialogGetDefFocus(d)       vdialogGetItemListDefFocus((d)->itemList)
#define vdialogGetDrag(d)           vdialogGetItemListDrag((d)->itemList)
#define vdialogGetSolution(d)       vdialogGetItemListSolution((d)->itemList)
#define vdialogGetItemCount(d)      vdialogGetItemListItemCount((d)->itemList)
#define vdialogGetItemAt(d, i)      vdialogGetItemListItemAt((d)->itemList, i)
#define vdialogGetItemIndex(d, i) \
    vdialogGetItemListItemIndex((d)->itemList, i)
#define vdialogFindItem(d, t)       vdialogFindItemListItem((d)->itemList, t)

#define vdialogCreateFocusCommand() \
    vcommandCreateOfClass(vdialogGetDefaultFocusCommandClass())
#define vdialogInitFocusCommand(c) \
    vcommandInitOfClass(c, vdialogGetDefaultFocusCommandClass())

/*
 * deprecated dialog items
 */

#define vdialogDetermineItemColors(i, d, n, c) \
    vdialogDetermineItemColorsFrom(i, 0L, (vcolor**)NULL, d, n, c)

/*
 * deprecated dialog item lists
 */

#define vdialogDetermineItemListColorsFrom(l, f, k, i, n, c) \
    ((*(l)->ownerFuncs->DetermineColorsFrom)((l)->owner, f, k, i, n, c))

/*
 * * * * * * * * * * PRIVATE FUNCTION MESSAGE DEFINITIONS * * * * * * * * * *
 */

/*
 * dialogs
 */

#define vdialogAppendItem(d, i) \
    vclassSend(vdialogGetClass(d), vdialogAPPEND_ITEM, (d, i))
#define vdialogRemoveItem(d, i) \
    vclassSend(vdialogGetClass(d), vdialogREMOVE_ITEM, (d, i))
#define vdialogDeleteItem(d, i) \
    ((void) vdialogRemoveItem(d, i))
#define vdialogSetItemIndex(d, i, n) \
    vclassSend(vdialogGetClass(d), vdialogSET_ITEM_INDEX, (d, i, n))
#define vdialogArrange(d, r) \
    vclassSend(vdialogGetClass(d), vdialogARRANGE, (d, r))
#define vdialogCalcMinSize(d, w, h) \
    vclassSend(vdialogGetClass(d), vdialogCALC_MIN_SIZE, (d, w, h))
#define vdialogSetMenu(d, m) \
    vclassSend(vdialogGetClass(d), vdialogSET_MENU, (d, m))
#define vdialogSetCloseHook(d, f) \
    vclassSend(vdialogGetClass(d), vdialogSET_CLOSE_HOOK, (d, f))
#define vdialogSetFocus(d, i) \
    vclassSend(vdialogGetClass(d), vdialogSET_FOCUS, (d, i))
#define vdialogTestSetFocus(d, i, e) \
    vclassSend(vdialogGetClass(d), vdialogTEST_SET_FOCUS, (d, i, e))
#define vdialogSetConfirm(d, i) \
    vclassSend(vdialogGetClass(d), vdialogSET_CONFIRM, (d, i))
#define vdialogSetAbandon(d, i) \
    vclassSend(vdialogGetClass(d), vdialogSET_ABANDON, (d, i))
#define vdialogSetDefFocus(d, i) \
    vclassSend(vdialogGetClass(d), vdialogSET_DEF_FOCUS, (d, i))
#define vdialogSetDrag(d, i) \
    vclassSend(vdialogGetClass(d), vdialogSET_DRAG, (d, i))
#define vdialogSetSolution(d, s) \
    vclassSend(vdialogGetClass(d), vdialogSET_SOLUTION, (d, s))

/*
 * dialog items
 */

#define vdialogOpenItem(i) \
    vclassSend(vdialogGetItemClass(i), vdialogOPEN_ITEM, (i))
#define vdialogCloseItem(i) \
    vclassSend(vdialogGetItemClass(i), vdialogCLOSE_ITEM, (i))
#define vdialogShowItem(i) \
    vclassSend(vdialogGetItemClass(i), vdialogSHOW_ITEM, (i))
#define vdialogHideItem(i) \
    vclassSend(vdialogGetItemClass(i), vdialogHIDE_ITEM, (i))
#define vdialogEnableItem(i) \
    vclassSend(vdialogGetItemClass(i), vdialogENABLE_ITEM, (i))
#define vdialogDisableItem(i) \
    vclassSend(vdialogGetItemClass(i), vdialogDISABLE_ITEM, (i))
#define vdialogFocusItem(i) \
    vclassSend(vdialogGetItemClass(i), vdialogFOCUS_ITEM, (i))
#define vdialogUnfocusItem(i) \
    vclassSend(vdialogGetItemClass(i), vdialogUNFOCUS_ITEM, (i))
#define vdialogTestFocusItem(i, e) \
    vclassSend(vdialogGetItemClass(i), vdialogTEST_FOCUS_ITEM, (i, e))
#define vdialogTestUnfocusItem(i, e) \
    vclassSend(vdialogGetItemClass(i), vdialogTEST_UNFOCUS_ITEM, (i, e))
#define vdialogItemIsValid(i) \
    vclassSend(vdialogGetItemClass(i), vdialogITEM_IS_VALID, (i))
#define vdialogConfirmItem(i) \
    vclassSend(vdialogGetItemClass(i), vdialogCONFIRM_ITEM, (i))
#define vdialogUnconfirmItem(i) \
    vclassSend(vdialogGetItemClass(i), vdialogUNCONFIRM_ITEM, (i))
#define vdialogActivateItem(i) \
    vclassSend(vdialogGetItemClass(i), vdialogACTIVATE_ITEM, (i))
#define vdialogDeactivateItem(i) \
    vclassSend(vdialogGetItemClass(i), vdialogDEACTIVATE_ITEM, (i))
#define vdialogInvalItemRect(i, r, f) \
    vclassSend(vdialogGetItemClass(i), vdialogINVAL_ITEM_RECT, (i, r, f))
#define vdialogScrollItemRect(i, r, x, y, f) \
    vclassSend(vdialogGetItemClass(i), vdialogSCROLL_ITEM_RECT, \
	       (i, r, x, y, f))
#define vdialogNotifyItem(i, e) \
    vclassSend(vdialogGetItemClass(i), vdialogNOTIFY_ITEM, (i, e))
#define vdialogGetItemMinSize(i, w, h) \
    vclassSend(vdialogGetItemClass(i), vdialogGET_ITEM_MIN_SIZE, (i, w, h))

#define vdialogGetItemDecorationSizes(i,t,l,b,r) \
    vclassSend(vdialogGetItemClass(i), \
	       vdialogGET_ITEM_DECORATION_SIZES, (i, t, l, b, r))

#define vdialogGetItemNaturalSize(i, w, h) \
    vclassSend(vdialogGetItemClass(i), vdialogGET_ITEM_NATURAL_SIZE, (i, w, h))
#define vdialogGetItemNaturalSeparation(i, i2, w) \
    vclassSend(vdialogGetItemClass(i), vdialogGET_ITEM_NATURAL_SEPARATION, \
	       (i, i2, w))
#define vdialogConstrainItemSize(i, w, h) \
    vclassSend(vdialogGetItemClass(i), vdialogCONSTRAIN_ITEM_SIZE, (i, w, h))
#define vdialogDrawItem(i) \
    vclassSend(vdialogGetItemClass(i), vdialogDRAW_ITEM, (i))
#define vdialogDrawItemWith(i,c) \
    vclassSend(vdialogGetItemClass(i), vdialogDRAW_ITEM_WITH, (i,c))
#define vdialogDrawItemBackgroundWith(i,c) \
    vclassSend(vdialogGetItemClass(i), vdialogDRAW_ITEM_BACKGROUND_WITH, (i,c))
#define vdialogDrawItemBorderWith(i,c) \
    vclassSend(vdialogGetItemClass(i), vdialogDRAW_ITEM_BORDER_WITH, (i,c))
#define vdialogDrawItemImageWith(i,c) \
    vclassSend(vdialogGetItemClass(i), vdialogDRAW_ITEM_IMAGE_WITH, (i,c))
#define vdialogDrawItemTitleWith(i,c) \
    vclassSend(vdialogGetItemClass(i), vdialogDRAW_ITEM_TITLE_WITH, (i,c))
#define vdialogDrawItemContentWith(i,c) \
    vclassSend(vdialogGetItemClass(i), vdialogDRAW_ITEM_CONTENT_WITH, (i,c))
#define vdialogDrawItemFocus(i) \
    vclassSend(vdialogGetItemClass(i), vdialogDRAW_ITEM_FOCUS, (i))
#define vdialogDrawItemFocusWith(i,c) \
    vclassSend(vdialogGetItemClass(i), vdialogDRAW_ITEM_FOCUS_WITH, (i,c))
#define vdialogOutlineConfirmItem(i) \
    vclassSend(vdialogGetItemClass(i), vdialogOUTLINE_CONFIRM_ITEM, (i))
#define vdialogOutlineConfirmItemWith(i,c) \
    vclassSend(vdialogGetItemClass(i), vdialogOUTLINE_CONFIRM_ITEM_WITH, (i,c))
#define vdialogOutlineAbandonItem(i) \
    vclassSend(vdialogGetItemClass(i), vdialogOUTLINE_ABANDON_ITEM, (i))
#define vdialogOutlineAbandonItemWith(i,c) \
    vclassSend(vdialogGetItemClass(i), vdialogOUTLINE_ABANDON_ITEM_WITH, (i,c))
#define vdialogItemDrawDevice(i) \
    vclassSend(vdialogGetItemClass(i), vdialogITEM_DRAW_DEVICE, (i))
#define vdialogCreateItemDrawcontext(i) \
    vclassSend(vdialogGetItemClass(i), vdialogCREATE_ITEM_DRAWCONTEXT, (i))
#define vdialogSetItemDraw(i) \
    vclassSend(vdialogGetItemClass(i), vdialogSET_ITEM_DRAW, (i))
#define vdialogSetItemPenAttributes(i,p) \
    vclassSend(vdialogGetItemClass(i), vdialogSET_ITEM_PEN_ATTRIBUTES, (i,p))
#define vdialogHandleItemButtonDown(i, e) \
    vclassSend(vdialogGetItemClass(i), vdialogHANDLE_ITEM_BUTTON_DOWN, (i, e))
#define vdialogHandleItemButtonUp(i, e) \
    vclassSend(vdialogGetItemClass(i), vdialogHANDLE_ITEM_BUTTON_UP, (i, e))
#define vdialogHandleItemDrag(i, e) \
    vclassSend(vdialogGetItemClass(i), vdialogHANDLE_ITEM_DRAG, (i, e))
#define vdialogHandleItemDetail(i, e) \
    vclassSend(vdialogGetItemClass(i), vdialogHANDLE_ITEM_DETAIL, (i, e))
#define vdialogHandleItemMotion(i, e) \
    vclassSend(vdialogGetItemClass(i), vdialogHANDLE_ITEM_MOTION, (i, e))
#define vdialogHandleItemKeyDown(i, e) \
    vclassSend(vdialogGetItemClass(i), vdialogHANDLE_ITEM_KEY_DOWN, (i, e))
#define vdialogHandleItemKeyUp(i, e) \
    vclassSend(vdialogGetItemClass(i), vdialogHANDLE_ITEM_KEY_UP, (i, e))
#define vdialogSetItemTag(i, t) \
    vclassSend(vdialogGetItemClass(i), vobjectSET_TAG, (i, t))
#define vdialogSetItemNotify(i, n) \
    vclassSend(vdialogGetItemClass(i), vdialogSET_ITEM_NOTIFY, (i, n))
#define vdialogSetItemData(i, d) \
    vclassSend(vdialogGetItemClass(i), vdialogSET_ITEM_DATA, (i, d))
#define vdialogSetItemObserving(i, b) \
    vclassSend(vdialogGetItemClass(i), vdialogSET_ITEM_OBSERVING, (i, b))
#define vdialogSetItemDefersHelp(i, b) \
    vclassSend(vdialogGetItemClass(i), vdialogSET_ITEM_DEFERS_HELP, (i, b))
#define vdialogSetItemTitleScribed(i, s) \
    vclassSend(vdialogGetItemClass(i), vdialogSET_ITEM_TITLE_SCRIBED, (i, s))
#define vdialogSetItemCursor(i, c) \
    vclassSend(vdialogGetItemClass(i), vdialogSET_ITEM_CURSOR, (i, c))
#define vdialogSetItemCursorOwned(i, c) \
    vclassSend(vdialogGetItemClass(i), vdialogSET_ITEM_CURSOR_OWNED, (i, c))
#define vdialogSetItemMenu(i, m) \
    vclassSend(vdialogGetItemClass(i), vdialogSET_ITEM_MENU, (i, m))
#define vdialogSetItemDropsite(i, d) \
    vclassSend(vdialogGetItemClass(i), vdialogSET_ITEM_DROPSITE, (i, d))
#define vdialogSetItemFont(i, f) \
    vclassSend(vdialogGetItemClass(i), vdialogSET_ITEM_FONT, (i, f))
#define vdialogSetItemForeground(i, c) \
    vclassSend(vdialogGetItemClass(i), vdialogSET_ITEM_FOREGROUND, (i, c))
#define vdialogSetItemBackground(i, c) \
    vclassSend(vdialogGetItemClass(i), vdialogSET_ITEM_BACKGROUND, (i, c))
#define vdialogSetItemImage(i, c) \
    vclassSend(vdialogGetItemClass(i), vdialogSET_ITEM_IMAGE, (i, c))
#define vdialogSetItemImageOwned(i, c) \
    vclassSend(vdialogGetItemClass(i), vdialogSET_ITEM_IMAGE_OWNED, (i, c))
#define vdialogSetItemSpace(i, s) \
    vclassSend(vdialogGetItemClass(i), vdialogSET_ITEM_SPACE, (i, s))
#define vdialogSetItemSpaceOwned(i, s) \
    vclassSend(vdialogGetItemClass(i), vdialogSET_ITEM_SPACE_OWNED, (i, s))
#define vdialogSetItemItemList(i, l) \
    vclassSend(vdialogGetItemClass(i), vdialogSET_ITEM_ITEM_LIST, (i, l))
#define vdialogSetItemMnemonic(i, k) \
    vclassSend(vdialogGetItemClass(i), vdialogSET_ITEM_MNEMONIC, (i, k))
#define vdialogSetItemFocusable(i, f) \
    vclassSend(vdialogGetItemClass(i), vdialogSET_ITEM_FOCUSABLE, (i, f))
#define vdialogSetItemClickFocusable(i, f) \
    vclassSend(vdialogGetItemClass(i), vdialogSET_ITEM_CLICK_FOCUSABLE, (i, f))
#define vdialogSetItemText(i, f) \
    vclassSend(vdialogGetItemClass(i), vdialogSET_ITEM_TEXT, (i, f))
#define vdialogSetItemBorder(i, f) \
    vclassSend(vdialogGetItemClass(i), vdialogSET_ITEM_BORDER, (i, f))
#define vdialogSetItemImageMask(i, f) \
    vclassSend(vdialogGetItemClass(i), vdialogSET_ITEM_IMAGE_MASK, (i, f))
#define vdialogSetItemRect(i, r) \
    vclassSend(vdialogGetItemClass(i), vdialogSET_ITEM_RECT, (i, r))
#define vdialogSetItemField(i, f) \
    vclassSend(vdialogGetItemClass(i), vdialogSET_ITEM_FIELD, (i, f))
#define vdialogItemIsFocusConfirmable(i) \
    vclassSend(vdialogGetItemClass(i), vdialogITEM_IS_FOCUS_CONFIRMABLE, (i))
#define vdialogDetermineItemColorSchemeFrom(i, k, f, s) \
    vclassSend(vdialogGetItemClass(i), \
	       vdialogDETERMINE_ITEM_COLOR_SCHEME_FROM, (i, k, f, s))
#define _vdialogGetItemDefaultCursor(i) \
    vclassGet(vdialogGetItemClass(item), vdialogITEM_CURSOR)
#define _vdialogGetItemFocusExtra(i) \
    vclassGet(vdialogGetItemClass(item), vdialogITEM_FOCUS_EXTRA)
#define _vdialogGetItemConfirmExtra(i) \
    vclassGet(vdialogGetItemClass(item), vdialogITEM_CONFIRM_EXTRA)

/*
 * dialog item lists
 */

#define vdialogOpenItemList(l) \
    vclassSend(vdialogGetItemListClass(l), vdialogOPEN_ITEM_LIST, (l))
#define vdialogCloseItemList(l) \
    vclassSend(vdialogGetItemListClass(l), vdialogCLOSE_ITEM_LIST, (l))
#define vdialogFocusItemList(l) \
    vclassSend(vdialogGetItemListClass(l), vdialogFOCUS_ITEM_LIST, (l))
#define vdialogUnfocusItemList(l) \
    vclassSend(vdialogGetItemListClass(l), vdialogUNFOCUS_ITEM_LIST, (l))
#define vdialogTestFocusItemList(l, e) \
    vclassSend(vdialogGetItemListClass(l), vdialogTEST_FOCUS_ITEM_LIST, (l, e))
#define vdialogTestUnfocusItemList(l, e) \
    vclassSend(vdialogGetItemListClass(l), vdialogTEST_UNFOCUS_ITEM_LIST, \
	       (l, e))
#define vdialogConfirmItemList(l) \
    vclassSend(vdialogGetItemListClass(l), vdialogCONFIRM_ITEM_LIST, (l))
#define vdialogUnconfirmItemList(l) \
    vclassSend(vdialogGetItemListClass(l), vdialogUNCONFIRM_ITEM_LIST, (l))
#define vdialogActivateItemList(l) \
    vclassSend(vdialogGetItemListClass(l), vdialogACTIVATE_ITEM_LIST, (l))
#define vdialogDeactivateItemList(l) \
    vclassSend(vdialogGetItemListClass(l), vdialogDEACTIVATE_ITEM_LIST, (l))
#define vdialogDrawItemList(l) \
    vclassSend(vdialogGetItemListClass(l), vdialogDRAW_ITEM_LIST, (l))
#define vdialogDrawItemListWith(l,c) \
    vclassSend(vdialogGetItemListClass(l), vdialogDRAW_ITEM_LIST_WITH, (l,c))
#define vdialogHandleItemListButtonDown(l, e) \
    vclassSend(vdialogGetItemListClass(l), \
	       vdialogHANDLE_ITEM_LIST_BUTTON_DOWN, (l, e))
#define vdialogHandleItemListMotion(l, e) \
    vclassSend(vdialogGetItemListClass(l), \
	       vdialogHANDLE_ITEM_LIST_MOTION, (l, e))
#define vdialogMoveItemListFocus(l, d, t) \
    vclassSend(vdialogGetItemListClass(l), vdialogMOVE_ITEM_LIST_FOCUS, \
	       (l, d, t))
#define vdialogTestMoveItemListFocus(l, d, t, w, e) \
    vclassSend(vdialogGetItemListClass(l), vdialogTEST_MOVE_ITEM_LIST_FOCUS, \
	       (l, d, t, w, e))
#define vdialogArrangeItemList(l, r) \
    vclassSend(vdialogGetItemListClass(l), vdialogARRANGE_ITEM_LIST, (l, r))
#define vdialogCalcItemListMinSize(l, w, h) \
    vclassSend(vdialogGetItemListClass(l), vdialogCALC_ITEM_LIST_MIN_SIZE, \
	       (l, w, h))
#define vdialogSetItemListFocusIndex(l, n) \
    vclassSend(vdialogGetItemListClass(l), vdialogSET_ITEM_LIST_FOCUS_INDEX, \
	       (l, n))
#define vdialogTestSetItemListFocusIndex(l, n, e) \
    vclassSend(vdialogGetItemListClass(l), \
	       vdialogTEST_SET_ITEM_LIST_FOCUS_INDEX, \
	       (l, n, e))
#define vdialogSetItemListConfirm(l, i) \
    vclassSend(vdialogGetItemListClass(l), vdialogSET_ITEM_LIST_CONFIRM, \
	       (l, i))
#define vdialogSetItemListAbandon(l, i) \
    vclassSend(vdialogGetItemListClass(l), vdialogSET_ITEM_LIST_ABANDON, \
	       (l, i))
#define vdialogSetItemListDefFocus(l, i) \
    vclassSend(vdialogGetItemListClass(l), vdialogSET_ITEM_LIST_DEF_FOCUS, \
	       (l, i))
#define vdialogSetItemListDrag(l, i) \
    vclassSend(vdialogGetItemListClass(l), vdialogSET_ITEM_LIST_DRAG, (l, i))
#define vdialogSetItemListSolution(l, s) \
    vclassSend(vdialogGetItemListClass(l), vdialogSET_ITEM_LIST_SOLUTION, \
	       (l, s))
#define vdialogSetItemListOwner(l, o, f) \
    vclassSend(vdialogGetItemListClass(l), vdialogSET_ITEM_LIST_OWNER, \
	       (l, o, f))

#define vdialogDetermineItemListDialog(l) \
    vclassSend(vdialogGetItemListClass(l), \
	       vdialogDETERMINE_ITEM_LIST_DIALOG, (l))
#define vdialogDetermineItemListCursor(l) \
    vclassSend(vdialogGetItemListClass(l), \
	       vdialogDETERMINE_ITEM_LIST_CURSOR, (l))
#define vdialogDetermineItemListFont(l) \
    vclassSend(vdialogGetItemListClass(l), \
	       vdialogDETERMINE_ITEM_LIST_FONT, (l))
#define vdialogDetermineItemListLineWidth(l) \
    vclassSend(vdialogGetItemListClass(l), \
	       vdialogDETERMINE_ITEM_LIST_LINE_WIDTH, (l))
#define vdialogDetermineItemListBounds(l, r) \
    vclassSend(vdialogGetItemListClass(l), \
	       vdialogDETERMINE_ITEM_LIST_BOUNDS, (l, r))
#define vdialogDetermineItemListContent(l, r) \
    vclassSend(vdialogGetItemListClass(l), \
	       vdialogDETERMINE_ITEM_LIST_CONTENT, (l, r))
#define vdialogGetItemListKeyMap(l) \
    vclassSend(vdialogGetItemListClass(l), \
	       vdialogGET_ITEM_LIST_KEY_MAP, (l))
#define vdialogGetItemListKeyDispatch(l) \
    vclassSend(vdialogGetItemListClass(l), \
	       vdialogGET_ITEM_LIST_KEY_DISPATCH, (l))
#define vdialogDetermineItemListShown(l) \
    vclassSend(vdialogGetItemListClass(l), \
	       vdialogDETERMINE_ITEM_LIST_SHOWN, (l))
#define vdialogDetermineItemListEnabled(l) \
    vclassSend(vdialogGetItemListClass(l), \
	       vdialogDETERMINE_ITEM_LIST_ENABLED, (l))
#define vdialogItemListDrawDevice(l) \
    vclassSend(vdialogGetItemListClass(l), \
	       vdialogITEM_LIST_DRAW_DEVICE, (l))
#define vdialogCreateItemListDrawcontext(l) \
    vclassSend(vdialogGetItemListClass(l), \
	       vdialogCREATE_ITEM_LIST_DRAWCONTEXT, (l))
#define vdialogTransformItemListPoint(l, x, y, rx, ry) \
    vclassSend(vdialogGetItemListClass(l), \
	       vdialogTRANSFORM_ITEM_LIST_POINT, (l, x, y, rx, ry))
#define vdialogTransformItemListRect(l, r, rr) \
    vclassSend(vdialogGetItemListClass(l), \
	       vdialogTRANSFORM_ITEM_LIST_RECT, (l, r, rr))
#define vdialogDetermineItemListColorSchemeFrom(l, k, f, s) \
    vclassSend(vdialogGetItemListClass(l), \
	       vdialogDETERMINE_ITEM_LIST_COLOR_SCHEME_FROM, (l, k, f, s))


vportEND_CPLUSPLUS_EXTERN_C

#endif /* #ifndef vdialogINCLUDED */


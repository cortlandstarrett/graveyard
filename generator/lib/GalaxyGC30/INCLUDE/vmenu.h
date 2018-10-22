/* $Id: vmenu.h,v 1.102 1997/09/30 20:52:21 alexey Exp $ */

/************************************************************

    vmenu.h

    C Interface file for the Menu Manager

    (c) Copyright Visix Software Inc.
    All rights reserved

************************************************************/

#ifndef vmenuINCLUDED
#define vmenuINCLUDED

#ifndef  vportINCLUDED
#include <vport.h>
#endif

#ifndef  vstdioINCLUDED
#include vstdioHEADER
#endif

#ifndef  vdebugINCLUDED
#include vdebugHEADER
#endif

#ifndef  vmemINCLUDED
#include vmemHEADER
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

#ifndef  veventINCLUDED
#include veventHEADER
#endif

#ifndef  vwindowINCLUDED
#include vwindowHEADER
#endif

#ifndef  vlafINCLUDED
#include vlafHEADER
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * * * * * * * * * * PUBLIC CONSTANT DEFINITIONS * * * * * * * * * *
 */

/*
 * menus
 */

enum {
    vmenuID_ATTRIBUTE_MNEMONIC      = vwindowNEXT_ID_ATTRIBUTE,
    vmenuID_ATTRIBUTE_DEFAULT,
    vmenuID_ATTRIBUTE_SELECTION,
    vmenuID_ATTRIBUTE_STATE,
    vmenuID_ATTRIBUTE_SIZE,
    vmenuNEXT_ID_ATTRIBUTE
};

enum { 
    vmenuSELECT_CONFIRM             = vwindowNEXT_SELECT,
    vmenuSELECT_ABANDON,
    vmenuSELECT_BEGIN,
    vmenuSELECT_END,
    vmenuSELECT_LEFT,
    vmenuSELECT_RIGHT,
    vmenuSELECT_UP,
    vmenuSELECT_DOWN,
    vmenuNEXT_SELECT
};

/*
 * menu items
 */

enum {
    vmenuITEM_ID_ATTRIBUTE_DATA     = vobjectNEXT_ID_ATTRIBUTE,
    vmenuITEM_ID_ATTRIBUTE_TITLE,
    vmenuITEM_ID_ATTRIBUTE_FONT,
    vmenuITEM_ID_ATTRIBUTE_FOREGROUND,
    vmenuITEM_ID_ATTRIBUTE_FOREGROUND_HILITE,
    vmenuITEM_ID_ATTRIBUTE_COLOR,
    vmenuITEM_ID_ATTRIBUTE_LINE_WIDTH,
    vmenuITEM_ID_ATTRIBUTE_KEY,
    vmenuITEM_ID_ATTRIBUTE_ACCELERATOR,
    vmenuITEM_ID_ATTRIBUTE_MNEMONIC,
    vmenuITEM_ID_ATTRIBUTE_STATE,
    vmenuITEM_ID_ATTRIBUTE_EXCLUSIVE,
    vmenuITEM_ID_ATTRIBUTE_TOGGLE,
    vmenuITEM_ID_ATTRIBUTE_FIELD,
    vmenuITEM_NEXT_ID_ATTRIBUTE
};

#ifdef vlafMAC

enum {
    vmenuMAC_CHECK_DOWN_STROKE      = 2,
    vmenuMAC_CHECK_UP_STROKE        = 7,
    vmenuMAC_CHECK_THICKNESS        = 2,
    vmenuMAC_EXTRA	            = 6,
    vmenuMAC_ARROW_WIDTH            = 5,
    vmenuMAC_ARROW_MIDDLE_HEIGHT    = 1,
    vmenuMAC_ARROW_HEIGHT           = 
	vmenuMAC_ARROW_WIDTH*2+vmenuMAC_ARROW_MIDDLE_HEIGHT,
    vmenuMAC_ARROW_RIGHT	    = 2,
    vmenuMAC_SUB_MENU_INSET	    = 6
};

#endif

#ifdef vlafMOTIF

enum {
    vmenuMOTIF_TOGGLE_SIZE          = 10
};

#endif

/*
 * * * * * * * * * * PUBLIC TYPE DEFINITIONS * * * * * * * * * *
 */

/*
 * menus
 */

typedef struct vmenu                vmenu;
typedef struct vmenuClass           vmenuClass;
typedef struct vmenuMetrics         vmenuMetrics;

typedef void (*vmenuNoteProc)(
    vmenu                          *menu,
    vevent                         *event
    );

typedef void (*vmenuParentNoteProc)(
    const void                     *parent,
    vevent                         *event
    );

struct vmenuMetrics {
    unsigned short                  flags;
    short                           left, right, below, above;
    short                           leftItem, rightItem, belowItem, aboveItem;
};

/*
 * menu items
 */

typedef struct vmenuItem            vmenuItem;
typedef struct vmenuItemClass       vmenuItemClass;
typedef struct vmenuItemMetrics     vmenuItemMetrics;

typedef vmenuItem                   vmenuSeparatorItem;
typedef vmenuItemClass              vmenuSeparatorItemClass;

typedef vmenuItem                   vmenuToggleItem;
typedef vmenuItemClass              vmenuToggleItemClass;

typedef vmenuItem                   vmenuPushPinItem;
typedef vmenuItemClass              vmenuPushPinItemClass;

typedef vmenuItem                   vmenuSubMenuItem;
typedef vmenuItemClass              vmenuSubMenuItemClass;

typedef void (*vmenuItemNoteProc)(
    vmenuItem                      *item,
    vevent                         *event
    );

struct vmenuItemMetrics {
    unsigned short                  flags;
    short                           width, height;
    short                           left, right;
};

/*
 * menu item lists
 */

typedef struct vmenuItemList        vmenuItemList;
typedef struct vmenuItemListClass   vmenuItemListClass;

/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */

void vmenuStartup(void);


/*
 * menus
 */

vmenuClass *vmenuGetDefaultClass(
    void
    );

vmenu *vmenuCreateOfClass(
    vmenuClass                     *clas
    );

vmenu *vmenuCreate(
    void
    );

vmenu *vmenuClone(
    vmenu                          *menu
    );

void vmenuInitOfClass(
    vmenu                          *menu,
    vmenuClass                     *clas
    );

void vmenuInit(
    vmenu                          *menu
    );

void vmenuDestroy(
    vmenu                          *menu
    );

void vmenuCopy(
    vmenu                          *menu,
    vmenu                          *target
    );

void vmenuCopyInit(
    vmenu                          *menu,
    vmenu                          *target
    );

vmenu *vmenuLoad(
    vresource                       resource
    );

void vmenuLoadInit(
    vmenu                          *menu,
    vresource                       resource
    );

void vmenuStore(
    vmenu                          *menu,
    vresource                       resource
    );

void vmenuOpen(
    vmenu                          *menu
    );

void vmenuClose(
    vmenu                          *menu
    );

void vmenuDump(
    vmenu                          *menu,
    FILE                           *stream
    );

void vmenuMove(
    vmenu                          *menu,
    int                             x,
    int                             y
    );

void vmenuEnable(
    vmenu                          *menu
    );

void vmenuDisable(
    vmenu                          *menu
    );

void vmenuChangedContents(
    vmenu                          *menu
    );

void vmenuChangedState(
    vmenu                          *menu
    );

void vmenuChangedSize(
    vmenu                          *menu
    );

void vmenuAppendItem(
    vmenu                          *menu,
    vmenuItem                      *item
    );

vmenuItem *vmenuRemoveItem(
    vmenu                          *menu,
    vmenuItem                      *item
    );

void vmenuSetItemIndex(
    vmenu                          *menu,
    vmenuItem                      *item,
    int                             index
    );

void vmenuPlaceRect(
    vmenu                          *menu,
    const vrect                    *rect,
    int                             modex,
    int                             modey
    );

void vmenuPlaceDefault(
    vmenu                          *menu,
    int                             x,
    int                             y
    );

void vmenuPlaceEvent(
    vmenu                          *menu,
    vevent                         *event
    );

void vmenuPlaceBelow(
    vmenu                          *menu,
    vwindow                        *window,
    const vrect                    *rect
    );

void vmenuPlaceRight(
    vmenu                          *menu,
    vwindow                        *window,
    const vrect                    *rect
    );

void vmenuPlaceLeft(
    vmenu                          *menu,
    vwindow                        *window,
    const vrect                    *rect
    );

int vmenuPopup(
    vmenu                          *menu,
    vevent                         *event
    );

int vmenuConfirm(
    vmenu                          *menu,
    vevent                         *event
    );

int vmenuAbandon(
    vmenu                          *menu,
    vevent                         *event
    );

int vmenuAccelerate(
    vmenu                          *menu,
    vevent                         *event
    );

void vmenuCalcMetrics(
    vmenu                          *menu,
    vmenuMetrics                   *metrics
    );

void vmenuCalcInsets(
    vmenu                          *menu,
    int				   *top,
    int				   *left,
    int				   *bottom,
    int				   *right
    );

void vmenuCalcInsetsForItems(
    vmenu                          *menu,
    int				   *top,
    int				   *left,
    int				   *bottom,
    int				   *right
    );

void vmenuArrange(
    vmenu                          *menu,
    const vmenuMetrics             *metrics
    );

void vmenuRecalc(
    vmenu                          *menu
    );

void vmenuSetNotify(
    vmenu                          *menu,
    vmenuNoteProc	            noteProc
    );

void vmenuSetData(
    vmenu                          *menu,
    const void                     *data
    );

void vmenuSetTitle(
    vmenu                          *menu,
    const vchar                    *title
    );

void vmenuSetTitleScribed(
    vmenu                          *menu,
    vscribe                        *scribe
    );

void vmenuSetLeader(
    vmenu                          *menu,
    vwindow                        *leader
    );

void vmenuSetMnemonic(
    vmenu                          *menu,
    int                             mnemonic
    );

void vmenuSetDefault(
    vmenu                          *menu,
    vmenuItem                      *item
    );

void vmenuSetSelection(
    vmenu                          *menu,
    vmenuItem                      *item
    );

void vmenuSetParent(
    vmenu                          *menu,
    const void                     *parent
    );

void vmenuSetParentNotify(
    vmenu                          *menu,
    vmenuParentNoteProc             noteProc
    );

void vmenuSetParentNotifyEarly(
    vmenu                          *menu,
    int                             flag
    );

void vmenuSetParentDragNotify(
    vmenu                          *menu,
    vmenuParentNoteProc             noteProc
    );

void vmenuSetParentDragRects(
    vmenu                          *menu,
    const vrect                    *rects,
    int                             count
    );

void vmenuSetParentStickRect(
    vmenu                          *menu,
    const vrect                    *rect
    );

vobjectAttributed *vmenuGetObject(
    vmenu                          *menu
    );

vwindow *vmenuGetWindow(
    vmenu                          *menu
    );

vmenuClass *vmenuGetClass(
    vmenu                          *menu
    );

vmenuNoteProc vmenuGetNotify(
    vmenu                          *menu
    );

const void *vmenuGetData(
    vmenu                          *menu
    );

const vchar *vmenuGetTitle(
    vmenu                          *menu
    );

int vmenuIsOpen(
    vmenu                          *menu
    );

int vmenuIsEnabled(
    vmenu                          *menu
    );

int vmenuContentsHaveChanged(
    vmenu                          *menu
    );

int vmenuStateHasChanged(
    vmenu                          *menu
    );

int vmenuSizeHasChanged(
    vmenu                          *menu
    );

vwindow *vmenuGetLeader(
    vmenu                          *menu
    );

int vmenuGetMnemonic(
    vmenu                          *menu
    );

vmenuItemList *vmenuGetItemList(
    vmenu                          *menu
    );

vmenuItem *vmenuGetDefault(
    vmenu                          *menu
    );

int vmenuGetItemCount(
    vmenu                          *menu
    );

vmenuItem *vmenuGetItemAt(
    vmenu                          *menu,
    int                             index
    );

int vmenuGetItemIndex(
    vmenu                          *menu,
    vmenuItem                      *item
    );

vmenuItem *vmenuFindItem(
    vmenu                          *menu,
    const vname                    *tag
    );

vmenuItem *vmenuFindAcceleratorItem(
    vmenu                          *menu,
    vkeyStroke                      accelerator
    );

vmenuItem *vmenuFindMnemonicItem(
    vmenu                          *menu,
    int                             mnemonic
    );

vmenuItem *vmenuGetSelection(
    vmenu                          *menu
    );

const void *vmenuGetParent(
    vmenu                          *menu
    );

vmenuParentNoteProc vmenuGetParentNotify(
    vmenu                          *menu
    );

int vmenuParentNotifyIsEarly(
    vmenu                          *menu
    );

vmenuParentNoteProc vmenuGetParentDragNotify(
    vmenu                          *menu
    );

const vrect *vmenuGetParentDragRects(
    vmenu                          *menu
    );

int vmenuGetParentDragRectCount(
    vmenu                          *menu
    );

const vrect *vmenuGetParentStickRect(
    vmenu                          *menu
    );

void vmenuMapAccelerators(
    vmenu                          *menu,
    const void                     *value,
    vdict                          *dict
    );

int vmenuIsOpenNative(
    vmenu                          *menu
    );

/*
 * menu items
 */
	
vmenuItemClass *vmenuGetDefaultItemClass(
    void
    );

vmenuSeparatorItemClass *vmenuGetSeparatorItemClass(
    void
    );

vmenuToggleItemClass *vmenuGetToggleItemClass(
    void
    );

vmenuPushPinItemClass *vmenuGetPushPinItemClass(
    void
    );

vmenuSubMenuItemClass *vmenuGetSubMenuItemClass(
    void
    );

vmenuItem *vmenuCreateItemOfClass(
    vmenuItemClass                 *clas
    );

vmenuItem *vmenuCreateItem(
    void
    );

vmenuSeparatorItem *vmenuCreateSeparatorItem(
    void
    );

vmenuToggleItem *vmenuCreateToggleItem(
    void
    );

vmenuPushPinItem *vmenuCreatePushPinItem(
    void
    );

vmenuSubMenuItem *vmenuCreateSubMenuItem(
    void
    );

vmenuItem *vmenuCloneItem(
    vmenuItem                      *item
    );

void vmenuInitItemOfClass(
    vmenuItem                      *item,
    vmenuItemClass                 *clas
    );

void vmenuInitItem(
    vmenuItem                      *item
    );

void vmenuInitSeparatorItem(
    vmenuSeparatorItem             *item
    );

void vmenuInitToggleItem(
    vmenuToggleItem                *item
    );

void vmenuInitPushPinItem(
    vmenuPushPinItem               *item
    );

void vmenuInitSubMenuItem(
    vmenuSubMenuItem               *item
    );

void vmenuDestroyItem(
    vmenuItem                      *item
    );

void vmenuDestroyItemLater(
    vmenuItem                      *item
    );

void vmenuCopyItem(
    vmenuItem                      *item,
    vmenuItem                      *target
    );

void vmenuCopyInitItem(
    vmenuItem                      *item,
    vmenuItem                      *target
    );

vmenuItem *vmenuLoadItem(
    vresource                       resource
    );

void vmenuLoadInitItem(
    vmenuItem                      *item,
    vresource                       resource
    );

void vmenuStoreItem(
    vmenuItem                      *item,
    vresource                       resource
    );

void vmenuSetItemAttribute(
    vmenuItem                      *item,
    const vname                    *attr,
    const void                     *value
    );

void vmenuSetAllItemAttributes(
    vmenuItem                      *item,
    vdict                          *attr2value
    );

const void *vmenuGetItemAttribute(
    vmenuItem                      *item,
    const vname                    *attr
    );

void vmenuGetAllItemAttributes(
    vmenuItem                      *item,
    vdict                          *attr2value
    );

void vmenuGetItemContextAttributes(
    vmenuItem                      *item,
    vdict                          *attr2value
    );

void vmenuChangedItemParentAttribute(
    vmenuItem                      *item,
    const vname                    *attr,
    vdict                          *context
    );

void vmenuChangedItemAttribute(
    vmenuItem                      *item,
    const vname                    *attr,
    vdict                          *context
    );

void vmenuChangedItemChildAttribute(
    vmenuItem                      *item,
    const vname                    *attr,
    vdict                          *context
    );

void vmenuChangedItemAttributeNone(
    vmenuItem                      *item,
    const vname                    *attr
    );

void vmenuChangedItemAttributeValue(
    vmenuItem                      *item,
    const vname                    *attr,
    const void                     *oldValue,
    const void                     *value
    );

void vmenuUpdateItemAttribute(
    vmenuItem                      *item,
    const vname                    *attr
    );

void vmenuUpdateAllItemAttributes(
    vmenuItem                      *item
    );

const void *vmenuAssociateItemAttribute(
    vmenuItem                      *item,
    const vname                    *attr,
    const vname                    *tag
    );

void vmenuAssociateAllItemAttributes(
    vmenuItem                      *item,
    const vname                    *tag,
    vdict                          *attr2value
    );

void vmenuPropagateItemChange(
    vmenuItem                      *item,
    const vname                    *attr,
    const vname                    *tag,
    const void                     *value
    );

void vmenuPropagateItemChangeDict(
    vmenuItem                      *item,
    const vname                    *attr,
    vdict                          *tag2value
    );

void vmenuPropagateItemChangeDictFromParent(
    vmenuItem                      *item,
    const vname                    *attr,
    vdict                          *tag2value
    );

void vmenuHelpItem(
    vmenuItem                      *item
    );

void vmenuDumpItem(
    vmenuItem                      *item,
    FILE                           *stream
    );

void vmenuEnableItem(
    vmenuItem                      *item
    );

void vmenuDisableItem(
    vmenuItem                      *item
    );

void vmenuNotifyItem(
    vmenuItem                      *item,
    vevent                         *event
    );

void vmenuInvalItemRect(
    vmenuItem                      *item,
    const vrect                    *rect,
    int                             flags
    );

void vmenuInvalItem(
    vmenuItem                      *item,
    int                             flags
    );

void vmenuScrollItemRect(
    vmenuItem                      *item,
    const vrect                    *rect,
    int                             dx,
    int                             dy,
    int                             flags
    );		      

void vmenuDrawItem(
    vmenuItem                      *item,
    const vrect                    *bounds,
    const vrect                    *content
    );

void vmenuDrawItemWith(
    vmenuItem                      *item,
    const vrect                    *bounds,
    const vrect                    *content,
    vdrawcontext                   *context
    );

void vmenuHiliteItem(
    vmenuItem                      *item,
    const vrect                    *bounds,
    const vrect                    *content
    );

void vmenuHiliteItemWith(
    vmenuItem                      *item,
    const vrect                    *bounds,
    const vrect                    *content,
    vdrawcontext                   *context
    );

void vmenuUnhiliteItem(
    vmenuItem                      *item,
    const vrect                    *bounds,
    const vrect                    *content
    );

void vmenuUnhiliteItemWith(
    vmenuItem                      *item,
    const vrect                    *bounds,
    const vrect                    *content,
    vdrawcontext                   *context
    );

void vmenuHiliteDefaultItem(
    vmenuItem                      *item,
    const vrect                    *bounds,
    const vrect                    *content
    );

void vmenuHiliteDefaultItemWith(
    vmenuItem                      *item,
    const vrect                    *bounds,
    const vrect                    *content,
    vdrawcontext                   *context
    );

int vmenuPopupItem(
    vmenuItem                      *item,
    vevent                         *event
    );

void vmenuSetItemDraw(
    vmenuItem                      *item
    );

void vmenuSetItemPenAttributes(
    vmenuItem                      *item,
    vdrawpen                       *pen
    );

void vmenuCalcItemMetrics(
    vmenuItem                      *item,
    vmenuItemMetrics               *metrics
    );

void vmenuCalcItemInsets(
    vmenuItem                      *item,
    int				   *top,
    int				   *left,
    int				   *bottom,
    int				   *right
    );

void vmenuGetItemMinSize(
    vmenuItem                      *item,
    int				   *width,
    int				   *height
    );

void vmenuSetItemTag(
    vmenuItem                      *item,
    const vname                    *tag
    );

void vmenuSetItemNotify(
    vmenuItem                      *item,
    vmenuItemNoteProc               noteProc
    );

void vmenuSetItemData(
    vmenuItem                      *item,
    const void                     *data
    );

void vmenuSetItemTitle(
    vmenuItem                      *item,
    const vchar                    *title
    );

void vmenuSetItemTitleScribed(
    vmenuItem                      *item,
    vscribe                        *scribe
    );

void vmenuSetItemFont(
    vmenuItem                      *item,
    vfont                          *font
    );

void vmenuSetItemForeground(
    vmenuItem                      *item,
    vcolor                         *foreground
    );

void vmenuSetItemSubMenu(
    vmenuItem                      *item,
    vmenu                          *subMenu
    );

void vmenuSetItemItemList(
    vmenuItem                      *item,
    vmenuItemList                  *itemList
    );

void vmenuSetItemAccelerator(
    vmenuItem                      *item,
    vkeyStroke                      accelerator
    );

void vmenuSetItemMnemonic(
    vmenuItem                      *item,
    int                             mnemonic
    );

void vmenuSetItemExclusive(
    vmenuItem                      *item,
    int                             flag
    );

void vmenuSetItemOn(
    vmenuItem                      *item,
    int                             flag
    );

void vmenuSetItemDefersHelp(
    vmenuItem                      *item,
    int                             flag
    );

void vmenuSetItemField(
    vmenuItem                      *item,
    vobservable                    *field
    );

void vmenuSetItemObserving(
    vmenuItem                      *item,
    vbool                           onOff
    );

vobjectAttributed *vmenuGetItemObject(
    vmenuItem                      *item
    );

vmenuItemClass *vmenuGetItemClass(
    vmenuItem                      *item
    );

const vname *vmenuGetItemTag(
    vmenuItem                      *item
    );

vmenuItemNoteProc vmenuGetItemNotify(
    vmenuItem                      *item
    );

const void *vmenuGetItemData(
    vmenuItem                      *item
    );

const vchar *vmenuGetItemTitle(
    vmenuItem                      *item
    );

vfont *vmenuGetItemFont(
    vmenuItem                      *item
    );

vcolor *vmenuGetItemForeground(
    vmenuItem                      *item
    );

vmenu *vmenuGetItemSubMenu(
    vmenuItem                      *item
    );

vmenuItemList *vmenuGetItemItemList(
    vmenuItem                      *item
    );

vkeyStroke vmenuGetItemAccelerator(
    vmenuItem                      *item
    );

int vmenuGetItemMnemonic(
    vmenuItem                      *item
    );

vobservable *vmenuGetItemField(
    vmenuItem                      *item
    );

int vmenuItemIsEnabled(
    vmenuItem                      *item
    );

int vmenuItemIsExclusive(
    vmenuItem                      *item
    );

int vmenuItemIsOn(
    vmenuItem                      *item
    );

int vmenuItemIsToggle(
    vmenuItem                      *item
    );

vbool vmenuItemIsObserving(
    vmenuItem                      *item
    );

int vmenuItemDefersHelp(
    vmenuItem                      *item
    );

int vmenuItemCanHilite(
    vmenuItem                      *item
    );

vmenu *vmenuDetermineItemMenu(
    vmenuItem                      *item
    );

vwindow *vmenuDetermineItemWindow(
    vmenuItem                      *item
    );

vfont *vmenuDetermineItemFont(
    vmenuItem                      *item
    );

vcolor *vmenuDetermineItemForeground(
    vmenuItem                      *item
    );

vcolor *vmenuDetermineItemBackground(
    vmenuItem                      *item
    );

vcolor *vmenuDetermineItemColor(
    vmenuItem                      *item,
    int                             id
    );

void vmenuDetermineItemColorScheme(
    vmenuItem                      *item,
    unsigned long                   flags,
    vcolorScheme                   *scheme
    );

void vmenuDetermineItemColorSchemeState(
    vmenuItem                      *item,
    unsigned long                   flags,
    vcolorScheme                   *scheme
    );

void vmenuDetermineItemColorSchemeFrom(
    vmenuItem                      *item,
    vcolorScheme                   *known,
    unsigned long                   flags,
    vcolorScheme                   *scheme
    );

int vmenuDetermineItemLineWidth(
    vmenuItem                      *item
    );

int vmenuDetermineItemEnabled(
    vmenuItem                      *item
    );

int vmenuNeedNativeDrawItem(
    vmenuItem                      *item
	);

int vmenuItemIsNativeDraw(
    vmenuItem                      *item
	);

/*
 * menu item lists
 */

vmenuItemListClass *vmenuGetDefaultItemListClass(
    void
    );

vmenuItemList *vmenuCreateItemListOfClass(
    vmenuItemListClass             *clas
    );

vmenuItemList *vmenuCreateItemList(
    void
    );

vmenuItemList *vmenuCloneItemList(
    vmenuItemList                  *itemList
    );

void vmenuInitItemListOfClass(
    vmenuItemList                  *itemList, 
    vmenuItemListClass             *clas
    );

void vmenuInitItemList(
    vmenuItemList                  *itemList
    );

void vmenuDestroyItemList(
    vmenuItemList                  *itemList
    );

void vmenuCopyItemList(
    vmenuItemList                  *itemList,
    vmenuItemList                  *targetList
    );

void vmenuCopyInitItemList(
    vmenuItemList                  *itemList,
    vmenuItemList                  *targetList
    );

vmenuItemList *vmenuLoadItemList(
    vresource                       resource
    );

void vmenuLoadInitItemList(
    vmenuItemList                  *itemList,
    vresource                       resource
    );

void vmenuStoreItemList(
    vmenuItemList                  *itemList,
    vresource                       resource
    );

void vmenuPropagateItemListChangeDictFromParent(
    vmenuItemList                  *itemList,
    const vname                    *attr,
    vdict                          *tag2value
    );

void vmenuChangedItemListParentAttribute(
    vmenuItemList                  *itemList,
    const vname                    *attr,
    vdict                          *context
    );

void vmenuChangedItemListAttribute(
    vmenuItemList                  *itemList,
    const vname                    *attr,
    vdict                          *context
    );

void vmenuChangedItemListChildAttribute(
    vmenuItemList                  *itemList,
    const vname                    *attr,
    vdict                          *context
    );

void vmenuUpdateItemListAttribute(
    vmenuItemList                  *itemList,
    const vname                    *attr
    );

void vmenuUpdateAllItemListAttributes(
    vmenuItemList                  *itemList
    );

void vmenuAppendItemListItem(
    vmenuItemList                  *itemList,
    vmenuItem                      *item
    );

void vmenuInsertItemListItem(
    vmenuItemList                  *itemList,
    vmenuItem                      *item,
    int                             index
    );

vmenuItem *vmenuRemoveItemListIndex(
    vmenuItemList                  *itemList,
    int                             index
    );

vmenuItem *vmenuRemoveItemListItem(
    vmenuItemList                  *itemList,
    vmenuItem                      *item
    );

void vmenuSetItemListIndexIndex(
    vmenuItemList                  *itemList,
    int                             itemIndex,
    int                             index
    );

void vmenuSetItemListItemIndex(
    vmenuItemList                  *itemList,
    vmenuItem                      *item,
    int                             index
    );

vmenuItem *vmenuReplaceItemListItemAt(
    vmenuItemList                  *itemList,
    int                             index,
    vmenuItem                      *item
    );

void vmenuOpenItemList(
    vmenuItemList                  *itemList
    );

void vmenuCloseItemList(
    vmenuItemList                  *itemList
    );

void vmenuDrawItemList(
    vmenuItemList                  *itemList
    );

void vmenuDrawItemListWith(
    vmenuItemList                  *itemList,
    vdrawcontext                   *context
    );

void vmenuHiliteItemListIndex(
    vmenuItemList                  *itemList,
    int                             index,
    int                             direct
    );

void vmenuHiliteItemListIndexWith(
    vmenuItemList                  *itemList,
    int                             index,
    int                             direct,
    vdrawcontext                   *context
    );

void vmenuHiliteItemListItem(
    vmenuItemList                  *itemList,
    vmenuItem                      *item
    );

void vmenuHiliteItemListItemWith(
    vmenuItemList                  *itemList,
    vmenuItem                      *item,
    vdrawcontext                   *context
    );

void vmenuHiliteItemListDefault(
    vmenuItemList                  *itemList
    );

void vmenuHiliteItemListDefaultWith(
    vmenuItemList                  *itemList,
    vdrawcontext                   *context
    );

void vmenuHiliteItemListOffset(
    vmenuItemList                  *itemList,
    int                             offset
    );

void vmenuHiliteItemListOffsetWith(
    vmenuItemList                  *itemList,
    int                             offset,
    vdrawcontext                   *context
    );

void vmenuHiliteItemListPoint(
    vmenuItemList                  *itemList,
    vevent                         *event
    );

void vmenuHiliteItemListPointWith(
    vmenuItemList                  *itemList,
    vevent                         *event,
    vdrawcontext                   *context
    );

vmenuItem *vmenuGetItemListPointItem(
    vmenuItemList                  *itemList,
    vevent                         *event
    );

void vmenuUnhiliteItemList(
    vmenuItemList                  *itemList
    );

void vmenuUnhiliteItemListWith(
    vmenuItemList                  *itemList,
    vdrawcontext                   *context
    );

int vmenuPopupItemList(
    vmenuItemList                  *itemList,
    vevent                         *event
    );

void vmenuArrangeItemList(
    vmenuItemList                  *itemList,
    const vmenuMetrics             *metrics
    );

void vmenuCalcItemListIndex(
    vmenuItemList                  *itemList,
    int                             index,
    vrect                          *bounds,
    vrect                          *content
    );

void vmenuCalcItemListItem(
    vmenuItemList                  *itemList,
    vmenuItem                      *item,
    vrect                          *bounds,
    vrect                          *content
    );

void vmenuSetItemListDefault(
    vmenuItemList                  *itemList,
    vmenuItem                      *defItem
    );

void vmenuSetItemListHilite(
    vmenuItemList                  *itemList,
    vmenuItem                      *item
    );

void vmenuSetItemListOwner(
    vmenuItemList                  *itemList,
    vobjectAttributed              *owner
    );

vobjectList *vmenuGetItemListObjectList(
    vmenuItemList                  *itemList
    );

vmenuItemListClass *vmenuGetItemListClass(
    vmenuItemList                  *itemList
    );

int vmenuGetItemListItemCount(
    vmenuItemList                  *itemList
    );

vmenuItem *vmenuGetItemListItemAt(
    vmenuItemList                  *itemList,
    int                             index
    );

int vmenuGetItemListItemIndex(
    vmenuItemList                  *itemList,
    vmenuItem                      *item
    );

int vmenuFindItemListItemIndex(
    vmenuItemList                  *itemList,
    const vname                    *tag
    );

vmenuItem *vmenuFindItemListItem(
    vmenuItemList                  *itemList,
    const vname                    *tag
    );

vmenuItem *vmenuRelocateItemListItem(
    vmenuItemList                  *itemList,
    vmenuItem                      *item,
    vmenuItemList                  *target
    );

vmenuItem *vmenuGetItemListDefault(
    vmenuItemList                  *itemList
    );

vmenuItem *vmenuGetItemListHilite(
    vmenuItemList                  *itemList
    );

vobjectAttributed *vmenuGetItemListOwner(
    vmenuItemList                  *itemList
    );

const vrect *vmenuGetItemListBounds(
    vmenuItemList                  *itemList
    );

vmenu *vmenuDetermineItemListMenu(
    vmenuItemList                  *itemList
    );

vwindow *vmenuDetermineItemListWindow(
    vmenuItemList                  *itemList
    );

vcursor *vmenuDetermineItemListCursor(
    vmenuItemList                  *itemList
    );

vfont *vmenuDetermineItemListFont(
    vmenuItemList                  *itemList
    );

void vmenuDetermineItemListColorSchemeFrom(
    vmenuItemList                  *itemList,
    vcolorScheme                   *known,
    unsigned long                   flags,
    vcolorScheme                   *scheme
    );

int vmenuDetermineItemListLineWidth(
    vmenuItemList                  *itemList
    );

/*
 * deprecated menus
 */

void vmenuDeleteItem(
    vmenu                          *menu,
    vmenuItem                      *item
    );

/*
 * deprecated menu items
 */
	
void vmenuDetermineItemColors(
    vmenuItem                      *item,
    int                            *ids,
    int                             count,
    vcolor                        **colors
    );

void vmenuDetermineItemColorsFrom(
    vmenuItem                      *item,
    long                            flags,
    vcolor                        **known,
    int                            *ids,
    int                             count,
    vcolor                        **colors
    );

void vmenuUnderlineMnemonic(
    const vchar                    *title,
    int                             mnemonic
    );

/*
 * deprecated menu item lists
 */
	
void vmenuDeleteItemListIndex(
    vmenuItemList                  *itemList,
    int                             index
    );

void vmenuDeleteItemListItem(
    vmenuItemList                  *itemList,
    vmenuItem                      *item
    );

void vmenuSetItemListItemAt(
    vmenuItemList                  *itemList,
    int                             index,
    vmenuItem                      *item
    );

void vmenuDetermineItemListColorsFrom(
    vmenuItemList                  *itemList,
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
 * menus
 */
	
enum {
    _vmenuENABLED                   = 0x0001,
    _vmenuCHANGED_CONTENTS          = 0x0002,
    _vmenuCHANGED_STATE             = 0x0004,
    _vmenuCHANGED_SIZE              = 0x0008,
    _vmenuPARENT_NOTIFY_EARLY       = 0x0010,
    _vmenuINHERIT_EVENT             = 0x0020,
    _vmenuSTICK_UP_ENABLED          = 0x0040,
    _vmenuHILITE_ENABLED            = 0x0080,
    _vmenuPINNED                    = 0x0100,
    _vmenuHAS_PIN                   = 0x0200,
    _vmenuHAS_MOTION                = 0x0400,
#if (vportWIN_MAC)
    _vmenuMAC_NATIVE		    = 0x0800,
#endif
   _vmenuCONFIRM_DEFAULT            = 0x1000
};

/*
 * menu items
 */
	
enum {
    _vmenuITEM_ENABLED	            = 0x0001,
    _vmenuITEM_EXCLUSIVE            = 0x0002,
    _vmenuITEM_ON		    = 0x0004,
    _vmenuITEM_TOGGLE               = 0x0008,
    _vmenuITEM_OWN_TITLE            = 0x0010,
    _vmenuITEM_NATIVE_DRAW          = 0x0020,
    _vmenuITEM_MENUBREAK            = 0x0040,
    _vmenuITEM_DEFERS_HELP          = 0x0080
};

/*
 * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * *
 */

/*
 * menu item lists
 */
	
typedef struct _vmenuItemListExtra  _vmenuItemListExtra;

struct vmenuItemList {
    vobjectList                     list;
    short                           defItem, hilite;
    vobjectAttributed              *owner;
    _vmenuItemListExtra            *extra;
};

#define vmenuITEM_LIST_CLASS(SUPER, LIST, ITEM)                               \
    vobjectLIST_CLASS(SUPER, LIST, ITEM);                                     \
    vclassMETHOD(vmenuOPEN_ITEM_LIST, (LIST *itemList));                      \
    vclassMETHOD(vmenuCLOSE_ITEM_LIST, (LIST *itemList));                     \
    vclassMETHOD(vmenuDRAW_ITEM_LIST, (LIST *itemList));                      \
    vclassMETHOD(vmenuDRAW_ITEM_LIST_WITH,                                    \
		 (LIST *itemList, vdrawcontext *context));                    \
    vclassMETHOD(vmenuHILITE_ITEM_LIST_INDEX,                                 \
		 (LIST *itemList, int index, int direct));                    \
    vclassMETHOD(vmenuHILITE_ITEM_LIST_INDEX_WITH,                            \
		 (LIST *itemList, int index, int direct,                      \
		  vdrawcontext *context));                                    \
    vclassMETHOD(vmenuHILITE_ITEM_LIST_POINT,                                 \
		 (LIST *itemList, vevent *event));                            \
    vclassMETHOD(vmenuHILITE_ITEM_LIST_POINT_WITH,                            \
		 (LIST *itemList, vevent *event, vdrawcontext *context));     \
    vclassMETHOD_RET(vmenuGET_ITEM_LIST_POINT_ITEM, vmenuItem *,  	      \
		 (LIST *itemList, vevent *event));                            \
    vclassMETHOD_RET(vmenuPOPUP_ITEM_LIST, int,                               \
		     (LIST *itemList, vevent *event));                        \
    vclassMETHOD(vmenuARRANGE_ITEM_LIST,                                      \
		 (LIST *itemList, const vmenuMetrics *metrics));              \
    vclassMETHOD(vmenuCALC_ITEM_LIST_INDEX,                                   \
		 (LIST *itemList, int index, vrect *bounds, vrect *content)); \
    vclassMETHOD(vmenuSET_ITEM_LIST_DEFAULT, (LIST *itemList, ITEM *item));   \
    vclassMETHOD(vmenuSET_ITEM_LIST_HILITE, (LIST *itemList, ITEM *item));    \
    vclassMETHOD(vmenuSET_ITEM_LIST_OWNER, (LIST *itemList,		      \
					    vobjectAttributed *owner))

struct vmenuItemListClass {
    vmenuITEM_LIST_CLASS(vmenuItemListClass, vmenuItemList, vmenuItem);
};

/*
 * menus
 */

typedef struct _vmenuExtra          _vmenuExtra;

#if (vportWIN_MS_WINDOWS)
    typedef struct _vmenuInfo  _vmenuInfo;
#endif

struct vmenu {
    vwindow                         window;
    vchar	                    mnemonic;
    unsigned short     	            flags;
    vmenuItemList                  *itemList;
    vmenuItem                      *selection;
    vobject			   *parent;
    _vmenuExtra                    *extra;
    vevent                         *lastClick;
#if (vportWIN_MAC)
    const void			   *sysData;
#endif
#if (vportWIN_MS_WINDOWS)
    _vmenuInfo     		   *info;
#endif

};

#define vmenuCLASS(SUPER, MENU, NOTIFY, ITEM, LIST)                           \
    vwindowCLASS(SUPER, MENU, NOTIFY);                                        \
    vclassMETHOD_RET(vmenuCREATE_ITEM_LIST, LIST *, (MENU *menu));            \
    vclassMETHOD(vmenuENABLE, (MENU *menu));                                  \
    vclassMETHOD(vmenuDISABLE, (MENU *menu));                                 \
    vclassMETHOD(vmenuCHANGED_CONTENTS, (MENU *menu));                        \
    vclassMETHOD(vmenuCHANGED_STATE, (MENU *menu));                           \
    vclassMETHOD(vmenuCHANGED_SIZE, (MENU *menu));                            \
    vclassMETHOD(vmenuAPPEND_ITEM, (MENU *menu, ITEM *item));                 \
    vclassMETHOD_RET(vmenuREMOVE_ITEM, ITEM *, (MENU *menu, ITEM *item));     \
    vclassMETHOD(vmenuDELETE_ITEM, (MENU *menu, ITEM *item));                 \
    vclassMETHOD(vmenuSET_ITEM_INDEX, (MENU *menu, ITEM *item, int index));   \
    vclassMETHOD(vmenuCALC_METRICS, (MENU *menu, vmenuMetrics *metrics));     \
    vclassMETHOD(vmenuCALC_INSETS,				      \
		 (MENU *menu, int *top, int *left, int *bottom, int *right)); \
    vclassMETHOD(vmenuCALC_INSETS_FOR_ITEMS,				      \
		 (MENU *menu, int *top, int *left, int *bottom, int *right)); \
    vclassMETHOD(vmenuARRANGE, (MENU *menu, const vmenuMetrics *metrics));    \
    vclassMETHOD(vmenuSET_MNEMONIC, (MENU *menu, int mnemonic));              \
    vclassMETHOD(vmenuSET_DEFAULT, (MENU *menu, ITEM *defItem));              \
    vclassMETHOD(vmenuSET_SELECTION, (MENU *menu, ITEM *selection));          \
    vclassMETHOD(vmenuSET_PARENT, (MENU *menu, const void *parent));          \
    vclassMETHOD(vmenuSET_PARENT_NOTIFY,                                      \
		 (MENU *menu, vmenuParentNoteProc noteProc));                 \
    vclassMETHOD(vmenuSET_PARENT_NOTIFY_EARLY, (MENU *menu, int flag));       \
    vclassMETHOD(vmenuSET_PARENT_DRAG_NOTIFY,                                 \
		 (MENU *menu, vmenuParentNoteProc dragNoteProc));             \
    vclassMETHOD(vmenuSET_PARENT_DRAG_RECTS,                                  \
		 (MENU *menu, const vrect *rects, int count));                \
    vclassMETHOD(vmenuSET_PARENT_STICK_RECT, (MENU *menu, const vrect *rect))

struct vmenuClass {
    vmenuCLASS(vmenuClass, vmenu, vmenuNoteProc, vmenuItem, vmenuItemList);
};

/*
 * menu items
 */
	
typedef struct _vmenuItemExtra      _vmenuItemExtra;

struct vmenuItem {
    vobjectAttributed               object;
    vmenuItemNoteProc               noteProc;
    const void		           *data;
    const vchar                    *title;
    _vmenuItemExtra                *extra;
    vmenuItemList                  *itemList;
    vkeyStroke                      accelerator;
    vchar                           mnemonic;
    unsigned short                  flags;
};

#define vmenuITEM_CLASS(SUPER, ITEM, NOTIFY)                                  \
    vobjectATTRIBUTED_CLASS(SUPER, ITEM);                                     \
    vclassVARIABLE(vmenuITEM_FONT, vfont*);                                   \
    vclassVARIABLE(vmenuITEM_FOREGROUND, vcolor*);                            \
    vclassVARIABLE(vmenuITEM_FOREGROUND_HILITE, vcolor*);                     \
    vclassMETHOD(vmenuENABLE_ITEM, (ITEM *item));                             \
    vclassMETHOD(vmenuDISABLE_ITEM, (ITEM *item));                            \
    vclassMETHOD(vmenuNOTIFY_ITEM, (ITEM *item, vevent *event));              \
    vclassMETHOD(vmenuOBSERVE_MENU_ITEM, (ITEM *item, vevent *event));        \
    vclassMETHOD(vmenuDRAW_ITEM,                                              \
		 (ITEM *item, const vrect *bounds, const vrect *content));    \
    vclassMETHOD(vmenuDRAW_ITEM_WITH,                                         \
		 (ITEM *item, const vrect *bounds,                            \
		  const vrect *content, vdrawcontext *context));              \
    vclassMETHOD(vmenuHILITE_ITEM,                                            \
		 (ITEM *item, const vrect *bounds, const vrect *content));    \
    vclassMETHOD(vmenuHILITE_ITEM_WITH,                                       \
		 (ITEM *item, const vrect *bounds, const vrect *content,      \
		  vdrawcontext *context));                                    \
    vclassMETHOD(vmenuUNHILITE_ITEM,                                          \
		 (ITEM *item, const vrect *bounds, const vrect *content));    \
    vclassMETHOD(vmenuUNHILITE_ITEM_WITH,                                     \
		 (ITEM *item, const vrect *bounds, const vrect *content,      \
		  vdrawcontext *context));                                    \
    vclassMETHOD(vmenuHILITE_DEFAULT_ITEM,                                    \
		 (ITEM *item, const vrect *bounds, const vrect *content));    \
    vclassMETHOD(vmenuHILITE_DEFAULT_ITEM_WITH,                               \
		 (ITEM *item, const vrect *bounds, const vrect *content,      \
		  vdrawcontext *context));                                    \
    vclassMETHOD(vmenuSET_ITEM_DRAW, (ITEM *item));                           \
    vclassMETHOD(vmenuSET_ITEM_PEN_ATTRIBUTES, (ITEM *item, vdrawpen *pen));  \
    vclassMETHOD(vmenuCALC_ITEM_METRICS,                                      \
		 (ITEM *item, vmenuItemMetrics *metrics));                    \
    vclassMETHOD(vmenuCALC_ITEM_INSETS,                                       \
		 (ITEM *item, int *top, int *left, int *bottom, int *right)); \
    vclassMETHOD(vmenuGET_ITEM_MIN_SIZE,                                      \
		 (ITEM *item, int *width, int *height));		      \
    vclassMETHOD(vmenuSET_ITEM_NOTIFY, (ITEM *item, NOTIFY noteProc));        \
    vclassMETHOD(vmenuSET_ITEM_DATA, (ITEM *item, const void *data));         \
    vclassMETHOD(vmenuSET_ITEM_TITLE_SCRIBED, (ITEM *item, vscribe *scribe)); \
    vclassMETHOD(vmenuSET_ITEM_FONT, (ITEM *item, vfont *font));              \
    vclassMETHOD(vmenuSET_ITEM_FOREGROUND, (ITEM *item, vcolor *foreground)); \
    vclassMETHOD(vmenuSET_ITEM_SUB_MENU, (ITEM *item, vmenu *subMenu));       \
    vclassMETHOD(vmenuSET_ITEM_ITEM_LIST,                                     \
		 (ITEM *item, vmenuItemList *itemList));                      \
    vclassMETHOD(vmenuSET_ITEM_ACCELERATOR,                                   \
		 (ITEM *item, vkeyStroke accelerator));                       \
    vclassMETHOD(vmenuSET_ITEM_MNEMONIC, (ITEM *item, int mnemonic));         \
    vclassMETHOD(vmenuSET_ITEM_EXCLUSIVE, (ITEM *item, int flag));            \
    vclassMETHOD(vmenuSET_ITEM_ON, (ITEM *item, int flag));                   \
    vclassMETHOD(vmenuSET_ITEM_FIELD, (ITEM *item, vobservable *field));      \
    vclassMETHOD(vmenuSET_ITEM_OBSERVING, (ITEM *item, vbool onOff));         \
    vclassMETHOD(vmenuSET_ITEM_DEFERS_HELP, (ITEM *item, int flag));          \
    vclassMETHOD(vmenuDETERMINE_ITEM_COLOR_SCHEME_FROM,                       \
		 (ITEM *item, vcolorScheme *known, unsigned long flags,       \
		  vcolorScheme *scheme));                                     \
    vclassMETHOD_RET(vmenuNEED_NATIVE_DRAW_ITEM, int, (ITEM *item))

struct vmenuItemClass {
    vmenuITEM_CLASS(vmenuItemClass, vmenuItem, vmenuItemNoteProc);
};

vportALIAS(vmenuSeparatorItem,	vmenuItem)
vportALIAS(vmenuToggleItem,	vmenuItem)
vportALIAS(vmenuPushPinItem,	vmenuItem)
vportALIAS(vmenuSubMenuItem,	vmenuItem)

/*
 * * * * * * * * * * PRIVATE FUNCTION PROTOTYPES * * * * * * * * * *
 */

int _vmenuPopdown(vmenu *menu, vevent *event, int confirm);

vobjectPartialChildIteratorClass *_vmenuGetPartialChildIteratorClass(void);
vobjectPartialChildIteratorClass *_vmenuGetItemPartialChildIteratorClass(void);

#if (vportWIN_MS_WINDOWS)
void _vmenuSetItemBreak(vmenuItem *item, int flag);
int  _vmenuItemIsBreak(vmenuItem *item);
#endif
void _vmenuSetItemNativeDraw(vmenuItem *item, int flag);

/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * *
 */

#define vmenuGetItemObject(i)       vportBASE_OBJECT(i, object)

#define vmenuGetItemListObjectList(l) vportBASE_OBJECT(l, list)

#define vmenuGetWindow(m)           vportBASE_OBJECT(m, window)
#define vmenuGetObject(m)           vwindowGetObject(vmenuGetWindow(m))

#if (vportWIN_MS_WINDOWS)
#define vmenuIsOpenNative(m)  ((m)->info != NULL)
#else
#define vmenuIsOpenNative(m)  (vFALSE)
#endif

/*
 * menu items
 */

#define vmenuCreateItemOfClass(c) \
    ((vmenuItem*)vobjectCreateOfClass((vobjectClass*)(c)))
#define vmenuCreateItem() \
    vmenuCreateItemOfClass(vmenuGetDefaultItemClass())
#define vmenuCreateSeparatorItem() \
    vmenuCreateItemOfClass(vmenuGetSeparatorItemClass())
#define vmenuCreateToggleItem() \
    vmenuCreateItemOfClass(vmenuGetToggleItemClass())
#define vmenuCreatePushPinItem() \
    vmenuCreateItemOfClass(vmenuGetPushPinItemClass())
#define vmenuCreateSubMenuItem() \
    vmenuCreateItemOfClass(vmenuGetSubMenuItemClass())
#define vmenuCloneItem(i) \
    ((vmenuItem*)vobjectClone(vmenuGetItemObject(i)))
#define vmenuInitItemOfClass(i, c) \
    vobjectInitOfClass(vmenuGetItemObject(i), (vobjectClass*)(c))
#define vmenuInitItem(i) \
    vmenuInitItemOfClass(i, vmenuGetDefaultItemClass())
#define vmenuInitSeparatorItem(i) \
    vmenuInitItemOfClass(i, vmenuGetSeparatorItemClass())
#define vmenuInitToggleItem(i) \
    vmenuInitItemOfClass(i, vmenuGetToggleItemClass())
#define vmenuInitPushPinItem(i) \
    vmenuInitItemOfClass(i, vmenuGetPushPinItemClass())
#define vmenuInitSubMenuItem(i) \
    vmenuInitItemOfClass(i, vmenuGetSubMenuItemClass())
#define vmenuDestroyItemLater(i)  vobjectDestroyLater(vmenuGetItemObject(i))
#define vmenuCopyInitItem(i, t) \
    vobjectCopyInit(vmenuGetItemObject(i), vmenuGetItemObject(t))
#define vmenuCopyItem(i, t) \
    vobjectCopy(vmenuGetItemObject(i), vmenuGetItemObject(t))
#define vmenuStoreItem(i, r) \
    vobjectStore(vmenuGetItemObject(i), r)
#define vmenuLoadItem(r)        ((vmenuItem*)vobjectLoad(r))
#define vmenuLoadInitItem(i, r)   vobjectLoadInit(vmenuGetItemObject(i), r)
#define vmenuDestroyItem(i) \
    vobjectDestroy(vmenuGetItemObject(i))

#define vmenuSetItemAttribute(i, a, v) \
    vobjectSetAttribute(vmenuGetItemObject(i), a, v)
#define vmenuSetAllItemAttributes(i, d) \
    vobjectSetAllAttributes(vmenuGetItemObject(i), d)
#define vmenuGetItemAttribute(i, a) \
    vobjectGetAttribute(vmenuGetItemObject(i), a)
#define vmenuGetAllItemAttributes(i, d) \
    vobjectGetAllAttributes(vmenuGetItemObject(i), d)
#define vmenuGetItemContextAttributes(i, d) \
    vobjectGetContextAttributes(vmenuGetItemObject(i), d)
#define vmenuChangedItemParentAttribute(i, a, d) \
    vobjectChangedParentAttribute(vmenuGetItemObject(i), a, d)
#define vmenuChangedItemAttribute(i, a, d) \
    vobjectChangedAttribute(vmenuGetItemObject(i), a, d)
#define vmenuChangedItemChildAttribute(i, a, d) \
    vobjectChangedChildAttribute(vmenuGetItemObject(i), a, d)
#define vmenuUpdateItemAttribute(i, a) \
    vobjectUpdateAttribute(vmenuGetItemObject(i), a)
#define vmenuUpdateAllItemAttributes(i) \
    vobjectUpdateAllAttributes(vmenuGetItemObject(i))
#define vmenuPropagateItemChangeDict(i, a, d) \
    vobjectPropagateChangeDict(vmenuGetItemObject(i), a, d)
#define vmenuHelpItem(i) \
    vobjectHelp(vmenuGetItemObject(i))
#define vmenuDumpItem(i, s) \
    vobjectDump(vmenuGetItemObject(i), s)

#define vmenuChangedItemAttributeNone(i, n) \
    vobjectChangedAttributeNone(vmenuGetItemObject(i), n)
#define vmenuChangedItemAttributeValue(i, n, o, v) \
    vobjectChangedAttributeValue(vmenuGetItemObject(i), n, o, v)
#define vmenuAssociateItemAttribute(i, a, n) \
    vobjectAssociateAttribute(vmenuGetItemObject(i), a, n)
#define vmenuAssociateAllItemAttributes(i, n, d) \
    vobjectAssociateAllAttributes(vmenuGetItemObject(i), n, d)
#define vmenuPropagateItemChange(i, a, n, v) \
    vobjectPropagateChange(vmenuGetItemObject(i), a, n, v)
#define vmenuPropagateItemChangeDictFromParent(i, a, d) \
    vobjectPropagateChangeDictFromParent(vmenuGetItemObject(i), a, d)

#define vmenuSetItemTitle(i, s)     vmenuSetItemTitleScribed(i, vcharScribe(s))

#define vmenuGetItemClass(i) \
    ((vmenuItemClass*)vobjectGetAttributedClass(vmenuGetItemObject(i)))
#define vmenuGetItemTag(i)           vobjectGetTag(vmenuGetItemObject(i))
#define vmenuGetItemNotify(i)      ((i)->noteProc)
#define vmenuGetItemData(i)        ((i)->data)
#define vmenuGetItemTitle(i)       ((i)->title)
#define vmenuGetItemItemList(i)    ((i)->itemList)
#define vmenuGetItemAccelerator(i) ((i)->accelerator)
#define vmenuGetItemMnemonic(i)    ((i)->mnemonic)
#define vmenuItemIsEnabled(i)     (((i)->flags&_vmenuITEM_ENABLED)    !=0)
#define vmenuItemIsExclusive(i)   (((i)->flags&_vmenuITEM_EXCLUSIVE)  !=0)
#define vmenuItemIsOn(i)          (((i)->flags&_vmenuITEM_ON)         !=0)
#define vmenuItemIsToggle(i)      (((i)->flags&_vmenuITEM_TOGGLE)     !=0)
#define vmenuItemDefersHelp(i)    (((i)->flags&_vmenuITEM_DEFERS_HELP)!=0)

#define vmenuDetermineItemForeground(i) \
    vmenuDetermineItemColor(i, vdrawCOLOR_FOREGROUND)
#define vmenuDetermineItemBackground(i) \
    vmenuDetermineItemColor(i, vdrawCOLOR_BACKGROUND)

#if (vportWIN_MS_WINDOWS)
#define _vmenuItemIsBreak(i)  (((i)->flags&_vmenuITEM_MENUBREAK) !=0)
#endif

#define vmenuItemIsNativeDraw(i)  (((i)->flags & _vmenuITEM_NATIVE_DRAW) != 0)

/*
 * menu item lists
 */

#define vmenuCreateItemListOfClass(c) \
    ((vmenuItemList*)vobjectCreateListOfClass((vobjectListClass*)(c)))
#define vmenuCreateItemList() \
    vmenuCreateItemListOfClass(vmenuGetDefaultItemListClass())
#define vmenuCloneItemList(l) \
    ((vmenuItemList*)vobjectCloneList(vmenuGetItemListObjectList(l)))
#define vmenuInitItemListOfClass(l, c) \
    vobjectInitListOfClass(vmenuGetItemListObjectList(l), \
			   (vobjectListClass*)(c))
#define vmenuInitItemList(l) \
    vmenuInitItemListOfClass(l, vmenuGetDefaultItemListClass())
#define vmenuDestroyItemList(l) \
    vobjectDestroyList(vmenuGetItemListObjectList(l))
#define vmenuCopyItemList(l, t) \
    vobjectCopyList(vmenuGetItemListObjectList(l), \
		    vmenuGetItemListObjectList(t))
#define vmenuStoreItemList(l, r) \
    vobjectStoreList(vmenuGetItemListObjectList(l), r)

#define vmenuGetItemListClass(l) \
    ((vmenuItemListClass*)vobjectGetListClass(vmenuGetItemListObjectList(l)))
#define vmenuGetItemListItemCount(l) \
    vobjectGetListCount(vmenuGetItemListObjectList(l))
#define vmenuGetItemListItemAt(l, n) \
    ((vmenuItem*)vobjectGetListAt(vmenuGetItemListObjectList(l), n))
#define vmenuGetItemListItemIndex(l, i) \
    vobjectGetListIndex(vmenuGetItemListObjectList(l), vmenuGetItemObject(i))

#define vmenuChangedItemListParentAttribute(l, a, d) \
    vobjectChangedListParentAttribute(vmenuGetItemListObjectList(l), a, d)
#define vmenuChangedItemListAttribute(l, a, d) \
    vobjectChangedListAttribute(vmenuGetItemListObjectList(l), a, d)
#define vmenuChangedItemListChildAttribute(l, a, d) \
    vobjectChangedListChildAttribute(vmenuGetItemListObjectList(l), a, d)
#define vmenuUpdateItemListAttribute(l, a) \
    vobjectUpdateListAttribute(vmenuGetItemListObjectList(l), a)
#define vmenuUpdateAllItemListAttributes(l) \
    vobjectUpdateAllListAttributes(vmenuGetItemListObjectList(l))
#define vmenuAppendItemListItem(l, i) \
    vobjectAppendList(vmenuGetItemListObjectList(l), vmenuGetItemObject(i))
#define vmenuRemoveItemListIndex(l, i) \
    ((vmenuItem*)vobjectRemoveListIndex(vmenuGetItemListObjectList(l), i))
#define vmenuDeleteItemListIndex(l, i) \
    ((void) vmenuRemoveItemListIndex(l, i))
#define vmenuSetItemListIndexIndex(l, ii, i) \
    vobjectSetListIndexIndex(vmenuGetItemListObjectList(l), ii, i)
#define vmenuReplaceItemListItemAt(l, n, i) \
    vobjectReplaceListAt(vmenuGetItemListObjectList(l), n, \
			 vmenuGetItemObject(i))
#define vmenuSetItemListItemAt(l, n, i) \
    ((void) vmenuReplaceItemListItemAt(l, n, i))

#define vmenuPropagateItemListChangeDictFromParent(l, a, d) \
    vobjectPropagateListChangeDictFromParent(vmenuGetItemListObjectList(l), \
					     a, d)
#define vmenuInsertItemListItem(l, i, n) \
    vobjectInsertList(vmenuGetItemListObjectList(l), vmenuGetItemObject(i), n)
#define vmenuRemoveItemListItem(l, i) \
    ((vmenuItem*)vobjectRemoveList(vmenuGetItemListObjectList(l), vmenuGetItemObject(i)))
#define vmenuDeleteItemListItem(l, i) \
    vobjectDeleteList(vmenuGetItemListObjectList(l), vmenuGetItemObject(i))
#define vmenuSetItemListItemIndex(l, i, n) \
    vobjectSetListIndex(vmenuGetItemListObjectList(l), \
			vmenuGetItemObject(i), n)
#define vmenuHiliteItemListItem(l, i) \
    vmenuHiliteItemListIndex(l, vmenuGetItemListItemIndex(l, i), 1)
#define vmenuHiliteItemListItemWith(l, i, c) \
    vmenuHiliteItemListIndexWith(l, vmenuGetItemListItemIndex(l, i), 1, c)
#define vmenuUnhiliteItemList(l)    vmenuHiliteItemListIndex(l, -1, 0)
#define vmenuUnhiliteItemListWith(l,c) vmenuHiliteItemListIndexWith(l, -1, 0, c)
#define vmenuCalcItemListItem(l, i, b, c) \
    vmenuCalcItemListIndex(l, vmenuGetItemListItemIndex(l, i), b, c)

#define vmenuFindItemListItemIndex(l, t) \
    vobjectFindListIndex(vmenuGetItemListObjectList(l), t)
#define vmenuFindItemListItem(l, t) \
    ((vmenuItem*)vobjectFindList(vmenuGetItemListObjectList(l), t))
#define vmenuRelocateItemListItem(l, i, t) \
    ((vmenuItem*)vobjectRelocateList(vmenuGetItemListObjectList(l), \
				     vmenuGetItemObject(i), \
				     vmenuGetItemListObjectList(t)))
#define vmenuGetItemListOwner(l)  ((l)->owner)

#define vmenuDetermineItemListMenu(l) ((vmenu*)(l)->owner)
#define vmenuDetermineItemListWindow(l) \
    vmenuGetWindow(vmenuDetermineItemListMenu(l))
#define vmenuDetermineItemListCursor(l) \
    vwindowDetermineCursor(vmenuGetWindow((vmenu*)(l)->owner))
#define vmenuDetermineItemListFont(l) \
    vwindowDetermineFont(vmenuGetWindow((vmenu*)(l)->owner))
#define vmenuDetermineItemListColorSchemeFrom(l, k, f, s) \
    vwindowDetermineColorSchemeFrom(vmenuGetWindow((vmenu*)(l)->owner), k, \
				    f, s)
#define vmenuDetermineItemListLineWidth(l) \
    vwindowDetermineLineWidth(vmenuGetWindow((vmenu*)(l)->owner))

/*
 * menus
 */

#define vmenuCreateOfClass(c) \
    ((vmenu*)vwindowCreateOfClass((vwindowClass*)(c)))
#define vmenuCreate()               vmenuCreateOfClass(vmenuGetDefaultClass())
#define vmenuClone(m)             ((vmenu*)vwindowClone(vmenuGetWindow(m)))
#define vmenuInitOfClass(m, c) \
    vwindowInitOfClass(vmenuGetWindow(m), (vwindowClass*)(c))
#define vmenuInit(m)                vmenuInitOfClass(m, vmenuGetDefaultClass())
#define vmenuCopyInit(m, t) \
    vwindowCopyInit(vmenuGetWindow(m), vmenuGetWindow(t))
#define vmenuCopy(m, t) \
    vwindowCopy(vmenuGetWindow(m), vmenuGetWindow(t))
#define vmenuStore(m, r) \
    vwindowStore(vmenuGetWindow(m), r)
#define vmenuLoad(r)                ((vmenu*)vwindowLoad(r))
#define vmenuLoadInit(m, r)         vwindowLoadInit(vmenuGetWindow(m), r)
#define vmenuDestroy(m) \
    vwindowDestroy(vmenuGetWindow(m))

#define vmenuDump(m, s) \
    vwindowDump(vmenuGetWindow(m), s)
#define vmenuOpen(m) \
    vwindowOpen(vmenuGetWindow(m))
#define vmenuClose(m) \
    vwindowClose(vmenuGetWindow(m))
#define vmenuSetData(m, p) \
    vwindowSetData(vmenuGetWindow(m), p)
#define vmenuSetTitleScribed(m, s) \
    vwindowSetTitleScribed(vmenuGetWindow(m), s)
#define vmenuSetLeader(m, w) \
    vwindowSetLeader(vmenuGetWindow(m), w)

#define vmenuMove(m, x, y)          vwindowMove(vmenuGetWindow(m), x, y)

#define vmenuSetTitle(m, s)         vwindowSetTitle(vmenuGetWindow(m), s)

#define vmenuGetClass(m) \
    ((vmenuClass*)vwindowGetClass(vmenuGetWindow(m)))

#define vmenuGetNotify(m) \
    ((vmenuNoteProc)vwindowGetNotify(vmenuGetWindow(m)))
#define vmenuSetNotify(m, n) \
    vwindowSetNotify((vwindow *)(m), (vwindowNoteProc)(n))

#define vmenuGetData(m)                vwindowGetData(vmenuGetWindow(m))
#define vmenuGetTitle(m)               vwindowGetTitle(vmenuGetWindow(m))
#define vmenuIsOpen(m)                 vwindowIsOpen(vmenuGetWindow(m))
#define vmenuIsEnabled(m)           (((m)->flags&_vmenuENABLED)!=0)
#define vmenuContentsHaveChanged(m) (((m)->flags&_vmenuCHANGED_CONTENTS)!=0)
#define vmenuStateHasChanged(m)     (((m)->flags&_vmenuCHANGED_STATE)!=0)
#define vmenuSizeHasChanged(m)      (((m)->flags&_vmenuCHANGED_SIZE) !=0)
#define vmenuGetLeader(m)              vwindowGetLeader(vmenuGetWindow(m))
#define vmenuPlaceRect(m, r, mx, my)   vwindowPlaceRect(vmenuGetWindow(m), \
							r, mx, my)
#define vmenuGetParent(m)           ((void *) (m)->parent)

#define vmenuGetMnemonic(m)          ((m)->mnemonic)
#define vmenuGetItemList(m)         ((m)->itemList)
#define vmenuGetDefault(m)             vmenuGetItemListDefault((m)->itemList)
#define vmenuGetItemCount(m) \
    vmenuGetItemListItemCount((m)->itemList)
#define vmenuGetItemAt(m, i) \
    vmenuGetItemListItemAt((m)->itemList, i)
#define vmenuGetItemIndex(m, i) \
    vmenuGetItemListItemIndex((m)->itemList, i)
#define vmenuFindItem(m, t)            vmenuFindItemListItem((m)->itemList, t)
#define vmenuGetSelection(m)         ((m)->selection)
#define vmenuParentNotifyIsEarly(m) (((m)->flags&_vmenuPARENT_NOTIFY_EARLY)!=0)

#define vmenuConfirm(m, e)          _vmenuPopdown(m, e, TRUE)
#define vmenuAbandon(m, e)          _vmenuPopdown(m, e, FALSE)

/*
 * deprecated menu items
 */
	
#define vmenuDetermineItemColors(i, d, n, c) \
    vmenuDetermineItemColorsFrom(i, 0L, (vcolor**)NULL, d, n, c)
#define vmenuUnderlineMnemonic(t, m) \
    vlafUnderlineMnemonic(t, m)

/*
 * deprecated menu item lists
 */
	
#define vmenuDetermineItemListColorsFrom(l, f, k, i, n, c) \
    vwindowDetermineColorsFrom(vmenuGetWindow((vmenu*)(l)->owner), \
			       f, k, i, n, c)

/*
 * * * * * * * * * * PRIVATE FUNCTION MESSAGE DEFINITIONS * * * * * * * * * *
 */

/*
 * menus
 */

#define vmenuEnable(m) \
    vclassSend(vmenuGetClass(m), vmenuENABLE, (m))
#define vmenuDisable(m) \
    vclassSend(vmenuGetClass(m), vmenuDISABLE, (m))
#define vmenuChangedContents(m) \
    vclassSend(vmenuGetClass(m), vmenuCHANGED_CONTENTS, (m))
#define vmenuChangedState(m) \
    vclassSend(vmenuGetClass(m), vmenuCHANGED_STATE, (m))
#define vmenuChangedSize(m) \
    vclassSend(vmenuGetClass(m), vmenuCHANGED_SIZE, (m))
#define vmenuAppendItem(m, i) \
    vclassSend(vmenuGetClass(m), vmenuAPPEND_ITEM, (m, i))
#define vmenuRemoveItem(m, i) \
    vclassSend(vmenuGetClass(m), vmenuREMOVE_ITEM, (m, i))
#define vmenuDeleteItem(m, i) \
    ((void) vmenuRemoveItem(m, i))
#define vmenuSetItemIndex(m, i, n) \
    vclassSend(vmenuGetClass(m), vmenuSET_ITEM_INDEX, (m, i, n))
#define vmenuCalcMetrics(m, t) \
    vclassSend(vmenuGetClass(m), vmenuCALC_METRICS, (m, t))
#define vmenuCalcInsets(m, t, l, b, r) \
    vclassSend(vmenuGetClass(m), vmenuCALC_INSETS, (m, t, l, b, r))
#define vmenuCalcInsetsForItems(m, t, l, b, r) \
    vclassSend(vmenuGetClass(m), vmenuCALC_INSETS_FOR_ITEMS, (m, t, l, b, r))
#define vmenuArrange(m, t) \
    vclassSend(vmenuGetClass(m), vmenuARRANGE, (m, t))
#define vmenuSetMnemonic(m, k) \
    vclassSend(vmenuGetClass(m), vmenuSET_MNEMONIC, (m, k))
#define vmenuSetDefault(m, i) \
    vclassSend(vmenuGetClass(m), vmenuSET_DEFAULT, (m, i))
#define vmenuSetSelection(m, i) \
    vclassSend(vmenuGetClass(m), vmenuSET_SELECTION, (m, i))
#define vmenuSetParent(m, p) \
    vclassSend(vmenuGetClass(m), vmenuSET_PARENT, (m, p))
#define vmenuSetParentNotify(m, f) \
    vclassSend(vmenuGetClass(m), vmenuSET_PARENT_NOTIFY, (m, f))
#define vmenuSetParentNotifyEarly(m, f) \
    vclassSend(vmenuGetClass(m), vmenuSET_PARENT_NOTIFY_EARLY, (m, f))
#define vmenuSetParentDragNotify(m, f) \
    vclassSend(vmenuGetClass(m), vmenuSET_PARENT_DRAG_NOTIFY, (m, f))
#define vmenuSetParentDragRects(m, r, n) \
    vclassSend(vmenuGetClass(m), vmenuSET_PARENT_DRAG_RECTS, (m, r, n))
#define vmenuSetParentStickRect(m, r) \
    vclassSend(vmenuGetClass(m), vmenuSET_PARENT_STICK_RECT, (m, r))

/*
 * menu items
 */

#define vmenuEnableItem(i) \
    vclassSend(vmenuGetItemClass(i), vmenuENABLE_ITEM, (i))
#define vmenuDisableItem(i) \
    vclassSend(vmenuGetItemClass(i), vmenuDISABLE_ITEM, (i))
#define vmenuNotifyItem(i, e) \
    vclassSend(vmenuGetItemClass(i), vmenuNOTIFY_ITEM, (i, e))
#define vmenuDrawItem(i, r, t) \
    vclassSend(vmenuGetItemClass(i), vmenuDRAW_ITEM, (i, r, t))
#define vmenuDrawItemWith(i, r, t, c) \
    vclassSend(vmenuGetItemClass(i), vmenuDRAW_ITEM_WITH, (i, r, t, c))
#define vmenuHiliteItemWith(i, r, t, c) \
    vclassSend(vmenuGetItemClass(i), vmenuHILITE_ITEM_WITH, (i, r, t, c))
#define vmenuUnhiliteItemWith(i, r, t, c) \
    vclassSend(vmenuGetItemClass(i), vmenuUNHILITE_ITEM_WITH, (i, r, t, c))
#define vmenuHiliteDefaultItemWith(i, r, t, c) \
    vclassSend(vmenuGetItemClass(i), vmenuHILITE_DEFAULT_ITEM_WITH, (i, r, t, c))
#define vmenuHiliteItem(i, r, t) \
    vclassSend(vmenuGetItemClass(i), vmenuHILITE_ITEM, (i, r, t))
#define vmenuUnhiliteItem(i, r, t) \
    vclassSend(vmenuGetItemClass(i), vmenuUNHILITE_ITEM, (i, r, t))
#define vmenuHiliteDefaultItem(i, r, t) \
    vclassSend(vmenuGetItemClass(i), vmenuHILITE_DEFAULT_ITEM, (i, r, t))
#define vmenuSetItemDraw(i) \
    vclassSend(vmenuGetItemClass(i), vmenuSET_ITEM_DRAW, (i))
#define vmenuSetItemPenAttributes(i,p) \
    vclassSend(vmenuGetItemClass(i), vmenuSET_ITEM_PEN_ATTRIBUTES, (i,p))
#define vmenuCalcItemMetrics(i, m) \
    vclassSend(vmenuGetItemClass(i), vmenuCALC_ITEM_METRICS, (i, m))
#define vmenuCalcItemInsets(i, t, l, b, r) \
    vclassSend(vmenuGetItemClass(i), vmenuCALC_ITEM_INSETS, (i, t, l, b, r))
#define vmenuGetItemMinSize(i, w, h) \
    vclassSend(vmenuGetItemClass(i), vmenuGET_ITEM_MIN_SIZE, (i, w, h))
#define vmenuSetItemTag(i, t) \
    vclassSend(vmenuGetItemClass(i), vobjectSET_TAG, (i, t))
#define vmenuSetItemNotify(i, f) \
    vclassSend(vmenuGetItemClass(i), vmenuSET_ITEM_NOTIFY, (i, f))
#define vmenuSetItemData(i, p) \
    vclassSend(vmenuGetItemClass(i), vmenuSET_ITEM_DATA, (i, p))
#define vmenuSetItemObserving(i, b) \
    vclassSend(vmenuGetItemClass(i), vmenuSET_ITEM_OBSERVING, (i, b))
#define vmenuSetItemTitleScribed(i, s) \
    vclassSend(vmenuGetItemClass(i), vmenuSET_ITEM_TITLE_SCRIBED, (i, s))
#define vmenuSetItemFont(i, f) \
    vclassSend(vmenuGetItemClass(i), vmenuSET_ITEM_FONT, (i, f))
#define vmenuSetItemForeground(i, c) \
    vclassSend(vmenuGetItemClass(i), vmenuSET_ITEM_FOREGROUND, (i, c))
#define vmenuSetItemSubMenu(i, m) \
    vclassSend(vmenuGetItemClass(i), vmenuSET_ITEM_SUB_MENU, (i, m))
#define vmenuSetItemItemList(i, l) \
    vclassSend(vmenuGetItemClass(i), vmenuSET_ITEM_ITEM_LIST, (i, l))
#define vmenuSetItemAccelerator(i, k) \
    vclassSend(vmenuGetItemClass(i), vmenuSET_ITEM_ACCELERATOR, (i, k))
#define vmenuSetItemMnemonic(i, k) \
    vclassSend(vmenuGetItemClass(i), vmenuSET_ITEM_MNEMONIC, (i, k))
#define vmenuSetItemExclusive(i, f) \
    vclassSend(vmenuGetItemClass(i), vmenuSET_ITEM_EXCLUSIVE, (i, f))
#define vmenuSetItemField(i, f) \
    vclassSend(vmenuGetItemClass(i), vmenuSET_ITEM_FIELD, (i, f))
#define vmenuSetItemOn(i, f) \
    vclassSend(vmenuGetItemClass(i), vmenuSET_ITEM_ON, (i, f))
#define vmenuSetItemDefersHelp(i, f) \
    vclassSend(vmenuGetItemClass(i), vmenuSET_ITEM_DEFERS_HELP, (i, f))
#define vmenuDetermineItemColorSchemeFrom(i, k, f, s) \
    vclassSend(vmenuGetItemClass(i), vmenuDETERMINE_ITEM_COLOR_SCHEME_FROM, \
	       (i, k, f, s))
#define vmenuNeedNativeDrawItem(i) \
    vclassSend(vmenuGetItemClass(i), vmenuNEED_NATIVE_DRAW_ITEM, (i))

/*
 * menu item lists
 */

#define vmenuOpenItemList(l) \
    vclassSend(vmenuGetItemListClass(l), vmenuOPEN_ITEM_LIST, (l))
#define vmenuCloseItemList(l) \
    vclassSend(vmenuGetItemListClass(l), vmenuCLOSE_ITEM_LIST, (l))
#define vmenuDrawItemList(l) \
    vclassSend(vmenuGetItemListClass(l), vmenuDRAW_ITEM_LIST, (l))
#define vmenuDrawItemListWith(l,c) \
    vclassSend(vmenuGetItemListClass(l), vmenuDRAW_ITEM_LIST_WITH, (l,c))
#define vmenuHiliteItemListIndex(l, i, d) \
    vclassSend(vmenuGetItemListClass(l), vmenuHILITE_ITEM_LIST_INDEX, \
	       (l, i, d))
#define vmenuHiliteItemListIndexWith(l, i, d, c) \
    vclassSend(vmenuGetItemListClass(l), vmenuHILITE_ITEM_LIST_INDEX_WITH, \
	       (l, i, d, c))
#define vmenuHiliteItemListPoint(l, e) \
    vclassSend(vmenuGetItemListClass(l), vmenuHILITE_ITEM_LIST_POINT, (l, e))
#define vmenuHiliteItemListPointWith(l, e, c) \
    vclassSend(vmenuGetItemListClass(l), vmenuHILITE_ITEM_LIST_POINT_WITH, \
	       (l, e, c))
#define vmenuGetItemListPointItem(l, e) \
    vclassSend(vmenuGetItemListClass(l), vmenuGET_ITEM_LIST_POINT_ITEM, (l, e))
#define vmenuPopupItemList(l, e) \
    vclassSend(vmenuGetItemListClass(l), vmenuPOPUP_ITEM_LIST, (l, e))
#define vmenuArrangeItemList(l, m) \
    vclassSend(vmenuGetItemListClass(l), vmenuARRANGE_ITEM_LIST, (l, m))
#define vmenuCalcItemListIndex(l, i, b, c) \
    vclassSend(vmenuGetItemListClass(l), vmenuCALC_ITEM_LIST_INDEX, \
	       (l, i, b, c))
#define vmenuSetItemListDefault(l, i) \
    vclassSend(vmenuGetItemListClass(l), vmenuSET_ITEM_LIST_DEFAULT, (l, i))
#define vmenuSetItemListHilite(l, i) \
    vclassSend(vmenuGetItemListClass(l), vmenuSET_ITEM_LIST_HILITE, (l, i))
#define vmenuSetItemListOwner(l, o) \
    vclassSend(vmenuGetItemListClass(l), vmenuSET_ITEM_LIST_OWNER, (l, o))

vportEND_CPLUSPLUS_EXTERN_C

#endif /* #ifndef vmenuINCLUDED */


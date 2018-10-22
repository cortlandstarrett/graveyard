/* $Id: vcontain.h,v 1.53 1997/07/02 22:00:47 gray Exp $ */

/************************************************************

    vcontain.h

    C Interface file for the Container Manager

    (c) Copyright Visix Software Inc.
    All rights reserved

************************************************************/

#ifndef vcontainINCLUDED
#define vcontainerINCLUDED
#define vcontainINCLUDED

#ifndef  vportINCLUDED
#include <vport.h>
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

#ifndef  vlafINCLUDED
#include vlafHEADER
#endif

#ifndef  vspringINCLUDED
#include vspringHEADER
#endif

#ifndef  vmenuINCLUDED
#include vmenuHEADER
#endif

#ifndef  vdialogINCLUDED
#include vdialogHEADER
#endif

#ifndef  vsliderINCLUDED
#include vsliderHEADER
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * * * * * * * * * * PUBLIC CONSTANT DEFINITIONS * * * * * * * * * *
 */

enum {
    vcontainerID_ATTRIBUTE_CONTENT  = vdialogITEM_NEXT_ID_ATTRIBUTE,
    vcontainerID_ATTRIBUTE_FLAT,
    vcontainerID_ATTRIBUTE_SCROLL_X,
    vcontainerID_ATTRIBUTE_SCROLL_Y,
    vcontainerID_ATTRIBUTE_FOCUS,
    vcontainerID_ATTRIBUTE_DEFAULT_FOCUS,
    vcontainerID_ATTRIBUTE_SOLUTION,
    vcontainerID_ATTRIBUTE_SELECTION,
    vcontainerNEXT_ID_ATTRIBUTE
};
    
enum {
    vcontainerNEXT_SELECT           = vdialogITEM_NEXT_SELECT
};

/*
 * * * * * * * * * * PUBLIC TYPE DEFINITIONS * * * * * * * * * *
 */

typedef struct vcontainer           vcontainer;
typedef struct vcontainerClass      vcontainerClass;
 
typedef vcontainer                  vcontainerGroup;
typedef vcontainerClass             vcontainerGroupClass;
typedef vcontainer                  vcontainerExclusiveGroup;
typedef vcontainerClass             vcontainerExclusiveGroupClass;
 
typedef void (*vcontainerNoteProc)(
    vcontainer                     *container,
    vevent                         *event
    );

/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */

void vcontainerStartup(void);


vcontainerClass *vcontainerGetDefaultClass(
    void
    );

vcontainerGroupClass *vcontainerGetGroupClass(
    void
    );

vcontainerExclusiveGroupClass *vcontainerGetExclusiveGroupClass(
    void
    );

vcontainer *vcontainerCreateOfClass(
    vcontainerClass                *clas
    );

vcontainer *vcontainerCreate(
    void
    );

vcontainerGroup *vcontainerCreateGroup(
    void
    );

vcontainerExclusiveGroup *vcontainerCreateExclusiveGroup(
    void
    );

vcontainer *vcontainerClone(
    vcontainer                     *container
    );

void vcontainerInitOfClass(
    vcontainer                     *container,
    vcontainerClass                *clas
    );

void vcontainerInit(
    vcontainer                     *container
    );

void vcontainerInitGroup(
    vcontainerGroup                *container
    );

void vcontainerInitExclusiveGroup(
    vcontainerExclusiveGroup       *container
    );

void vcontainerDestroy(
    vcontainer                     *container
    );

void vcontainerCopy(
    vcontainer                     *container,
    vcontainer                     *target
    );

void vcontainerCopyInit(
    vcontainer                     *container,
    vcontainer                     *target
    );

vcontainer *vcontainerLoad(
    vresource                       resource
    );

void vcontainerLoadInit(
    vcontainer                     *container,
    vresource                       resource
    );

void vcontainerStore(
    vcontainer                     *container,
    vresource                       resource
    );

void vcontainerEnable(
    vcontainer                     *container
    );

void vcontainerDisable(
    vcontainer                     *container
    );

void vcontainerAppendItem(
    vcontainer                     *container,
    vdialogItem                    *item
    );

vdialogItem *vcontainerRemoveItem(
    vcontainer                     *container,
    vdialogItem                    *item
    );

void vcontainerSetItemIndex(
    vcontainer                     *container,
    vdialogItem                    *item,
    int                             index
    );

void vcontainerArrange(
    vcontainer                     *container,
    const vrect                    *rect
    );

void vcontainerCalcMinSize(
    vcontainer                     *container,
    int                            *w,
    int                            *h
    );

void vcontainerCalcContent(
    vcontainer                     *container,
    vrect                          *content
    );

void vcontainerGetBorderDecorationSizes(
    vcontainer                     *container,
    int                            *top,
    int                            *left,
    int                            *bottom,
    int                            *right
    );

void vcontainerGetTitleDecorationSizes(
    vcontainer                     *container,
    int                            *top,
    int                            *left,
    int                            *bottom,
    int                            *right
    );

void vcontainerGetScrollBarDecorationSizes(
    vcontainer                     *container,
    int                            *top,
    int                            *left,
    int                            *bottom,
    int                            *right
    );

void vcontainerSetNotify(
    vcontainer                     *container,
    vcontainerNoteProc              noteProc
    );

void vcontainerSetData(
    vcontainer                     *container,
    const void                     *data
    );

void vcontainerSetTitle(
    vcontainer                     *container,
    const vchar                    *title
    );

void vcontainerSetTitleScribed(
    vcontainer                     *container,
    vscribe                        *title
    );

void vcontainerSetBorder(
    vcontainer                     *container,
    int                             flag
    );

void vcontainerSetBounds(
    vcontainer                     *container,
    const vrect                    *bounds
    );

void vcontainerSetFlat(
    vcontainer                     *container,
    int                             flag
    );

void vcontainerSetScrollX(
    vcontainer                     *container,
    int                             flag
    );

void vcontainerSetScrollY(
    vcontainer                     *container,
    int                             flag
    );

void vcontainerSetFocus(
    vcontainer                     *container,
    vdialogItem                    *focus
    );

vbool vcontainerTestSetFocus(
    vcontainer                     *container,
    vdialogItem                    *focus,
    vevent			   *event
    );

void vcontainerSetDefFocus(
    vcontainer                     *container,
    vdialogItem                    *defFocus
    );

void vcontainerSetSolution(
    vcontainer                     *container,
    vspringSolution                *solution
    );

void vcontainerSetSelection(
    vcontainer                     *container,
    vdialogItem                    *selection
    );

vobjectAttributed *vcontainerGetObject(
    vcontainer                     *container
    );

vdialogItem *vcontainerGetItem(
    vcontainer                     *container
    );

vcontainerClass *vcontainerGetClass(
    vcontainer                     *container
    );

vcontainerNoteProc vcontainerGetNotify(
    vcontainer                     *container
    );

const void *vcontainerGetData(
    vcontainer                     *container
    );

const vchar *vcontainerGetTitle(
    vcontainer                     *container
    );

int vcontainerIsEnabled(
    vcontainer                     *container
    );

int vcontainerHasBorder(
    vcontainer                     *container
    );

const vrect *vcontainerGetContent(
    vcontainer                     *container
    );

const vrect *vcontainerGetBounds(
    vcontainer                     *container
    );

int vcontainerIsFlat(
    vcontainer                     *container
    );

int vcontainerHasScrollX(
    vcontainer                     *container
    );

int vcontainerHasScrollY(
    vcontainer                     *container
    );

vdialogItemList *vcontainerGetItemList(
    vcontainer                     *container
    );

vdialogItem *vcontainerGetFocus(
    vcontainer                     *container
    );

vdialogItem *vcontainerGetDefFocus(
    vcontainer                     *container
    );

vspringSolution *vcontainerGetSolution(
    vcontainer                     *container
    );

int vcontainerGetItemCount(
    vcontainer                     *container
    );

vdialogItem *vcontainerGetItemAt(
    vcontainer                     *container,
    int                             index
    );

int vcontainerGetItemIndex(
    vcontainer                     *container,
    vdialogItem                    *item
    );

vdialogItem *vcontainerFindItem(
    vcontainer                     *container,
    const vname                    *tag
    );

vdialogItem *vcontainerGetSelection(
    vcontainer                     *container
    );

/*
 * deprecated containers
 */

void vcontainerDeleteItem(
    vcontainer                     *container,
    vdialogItem                    *item
    );

/*
 * * * * * * * * * * PRIVATE CONSTANT DEFINITIONS * * * * * * * * * *
 */

enum {
    _vcontainerFLAT                 = 0x0001,
    _vcontainerSCROLL_X             = 0x0004,
    _vcontainerSCROLL_Y             = 0x0008,
    _vcontainerCHANGED_SOLUTION     = 0x0010,
    _vcontainerCHANGED_SIZE         = 0x0020
};

/*
 * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * *
 */

vportALIAS(vcontainerItemList, vdialogItemList)


struct vcontainer {
    vdialogItem                     item;
    vrect                           content, bounds;
    unsigned short                  flags;
    vdialogItemList	           *itemList;
    vdialogItem                    *selection;
    vcontrol                       *scrollX, *scrollY;
    short                           minW, minH;
};

#define vcontainerCLASS(SUPER, CONTAINER, NOTIFY)                             \
    vdialogITEM_CLASS(SUPER, CONTAINER, NOTIFY);                              \
    vclassMETHOD_RET(vcontainerCREATE_ITEM_LIST, vdialogItemList *,	      \
		     (CONTAINER *container));				      \
    vclassMETHOD_RET(vcontainerCREATE_SCROLL_BAR, vsliderScrollBar *,	      \
		     (CONTAINER *container));				      \
    vclassMETHOD(vcontainerAPPEND_ITEM,                                       \
		 (CONTAINER *container, vdialogItem *item));                  \
    vclassMETHOD_RET(vcontainerREMOVE_ITEM, vdialogItem *,                    \
		 (CONTAINER *container, vdialogItem *item));                  \
    vclassMETHOD(vcontainerDELETE_ITEM,                                       \
		 (CONTAINER *container, vdialogItem *item));                  \
    vclassMETHOD(vcontainerSET_ITEM_INDEX,                                    \
		 (CONTAINER *container, vdialogItem *item, int index));       \
    vclassMETHOD(vcontainerARRANGE,                                           \
		 (CONTAINER *container, const vrect *rect));                  \
    vclassMETHOD(vcontainerCALC_MIN_SIZE,                                     \
		 (CONTAINER *container, int *w, int *h));                     \
    vclassMETHOD(vcontainerGET_BORDER_DECORATION_SIZES,                       \
		 (CONTAINER *container, int *top, int *left,                  \
		  int *bottom, int *right));                                  \
    vclassMETHOD(vcontainerGET_TITLE_DECORATION_SIZES,                        \
		 (CONTAINER *container, int *top, int *left,                  \
		  int *bottom, int *right));                                  \
    vclassMETHOD(vcontainerGET_SCROLLBAR_DECORATION_SIZES,                    \
		 (CONTAINER *container, int *top, int *left,                  \
		  int *bottom, int *right));                                  \
    vclassMETHOD(vcontainerSET_BOUNDS,                                        \
		 (CONTAINER *container, const vrect *bounds));                \
    vclassMETHOD(vcontainerSET_FLAT, (CONTAINER *container, int flag));       \
    vclassMETHOD(vcontainerSET_SCROLL_X, (CONTAINER *container, int flag));   \
    vclassMETHOD(vcontainerSET_SCROLL_Y, (CONTAINER *container, int flag));   \
    vclassMETHOD(vcontainerSET_FOCUS,                                         \
		 (CONTAINER *container, vdialogItem *focus));                 \
    vclassMETHOD_RET(vcontainerTEST_SET_FOCUS, vbool,                         \
		 (CONTAINER *container, vdialogItem *focus, vevent *event));  \
    vclassMETHOD(vcontainerSET_DEF_FOCUS,                                     \
		 (CONTAINER *container, vdialogItem *defFocus));              \
    vclassMETHOD(vcontainerSET_SOLUTION,                                      \
		 (CONTAINER *container, vspringSolution *solution));          \
    vclassMETHOD(vcontainerSET_SELECTION,                                     \
		 (CONTAINER *container, vdialogItem *selection))

struct vcontainerClass {
    vcontainerCLASS(vcontainerClass, vcontainer, vcontainerNoteProc);
};

vportALIAS(vcontainerGroup,		vcontainer)
vportALIAS(vcontainerExclusiveGroup,	vcontainerGroup)

/*
 * * * * * * * * * * PRIVATE FUNCTION PROTOTYPES * * * * * * * * * *
 */

vobjectPartialChildIteratorClass *_vcontainerGetPartialChildIteratorClass(
									void);


/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * *
 */

#define vcontainerGetItem(c)        vportBASE_OBJECT(c, item)
#define vcontainerGetObject(c)      vdialogGetItemObject(vcontainerGetItem(c))

#define vcontainerCreateOfClass(c) \
    ((vcontainer*)vdialogCreateItemOfClass((vdialogItemClass*)(c)))
#define vcontainerCreate() \
    vcontainerCreateOfClass(vcontainerGetDefaultClass())
#define vcontainerCreateGroup() \
    vcontainerCreateOfClass(vcontainerGetGroupClass())
#define vcontainerCreateExclusiveGroup() \
    vcontainerCreateOfClass(vcontainerGetExclusiveGroupClass())
#define vcontainerClone(c) \
    ((vcontainer*)vdialogCloneItem(vcontainerGetItem(c)))
#define vcontainerInitOfClass(c, cl) \
    vdialogInitItemOfClass(vcontainerGetItem(c), (vdialogItemClass*)(cl))
#define vcontainerInit(c) \
    vcontainerInitOfClass(c, vcontainerGetDefaultClass())
#define vcontainerInitGroup(c) \
    vcontainerInitOfClass(c, vcontainerGetGroupClass())
#define vcontainerInitExclusiveGroup(c) \
    vcontainerInitOfClass(c, vcontainerGetExclusiveGroupClass())
#define vcontainerCopyInit(c, t) \
    vdialogCopyInitItem(vcontainerGetItem(c), vcontainerGetItem(t))
#define vcontainerLoad(r)         ((vcontainer*)vdialogLoadItem(r))
#define vcontainerLoadInit(c, r) \
    vdialogLoadInitItem(vcontainerGetItem(c), r)
#define vcontainerDestroy(c) \
    vdialogDestroyItem(vcontainerGetItem(c))

#define vcontainerSetTitle(c, s) \
    vdialogSetItemTitle(vcontainerGetItem(c), s)

#define vcontainerGetClass(c) \
    ((vcontainerClass*)vdialogGetItemClass(vcontainerGetItem(c)))

#define vcontainerGetNotify(c) \
    ((vcontainerNoteProc)vdialogGetItemNotify(vcontainerGetItem(c)))
#define vcontainerSetNotify(c, n) \
    vdialogSetItemNotify((vdialogItem *)(c), (vdialogItemNoteProc)(n))

#define vcontainerGetData(c)        vdialogGetItemData(vcontainerGetItem(c))
#define vcontainerGetTitle(c)       vdialogGetItemTitle(vcontainerGetItem(c))
#define vcontainerIsEnabled(c)      vdialogItemIsEnabled(vcontainerGetItem(c))
#define vcontainerHasBorder(c)      vdialogItemHasBorder(vcontainerGetItem(c))
#define vcontainerGetContent(c)   ((const vrect*)&(c)->content)
#define vcontainerGetBounds(c)    ((const vrect*)&(c)->bounds)
#define vcontainerIsFlat(c)      (((c)->flags&_vcontainerFLAT)!=0)
#define vcontainerHasScrollX(c)  (((c)->flags&_vcontainerSCROLL_X)!=0)
#define vcontainerHasScrollY(c)  (((c)->flags&_vcontainerSCROLL_Y)!=0)
#define vcontainerGetItemList(c) ((c)->itemList)
#define vcontainerGetFocus(c)       vdialogGetItemListFocus((c)->itemList)
#define vcontainerGetDefFocus(c)    vdialogGetItemListDefFocus((c)->itemList)
#define vcontainerGetSolution(c)    vdialogGetItemListSolution((c)->itemList)
#define vcontainerGetItemCount(c)   vdialogGetItemListItemCount((c)->itemList)
#define vcontainerGetItemAt(c, i)   vdialogGetItemListItemAt((c)->itemList, i)
#define vcontainerGetItemIndex(c, i) \
    vdialogGetItemListItemIndex((c)->itemList, i)
#define vcontainerFindItem(c, t)    vdialogFindItemListItem((c)->itemList, t)
#define vcontainerGetSelection(c) ((c)->selection)

/*
 * * * * * * * * * * PRIVATE FUNCTION MESSAGE DEFINITIONS * * * * * * * * * *
 */

#define vcontainerCopy(c, t) \
    vclassSend(vcontainerGetClass(c), vobjectCOPY, (c, t))
#define vcontainerStore(c, r) \
    vclassSend(vcontainerGetClass(c), vobjectSTORE, (c, r))
#define vcontainerEnable(c) \
    vclassSend(vcontainerGetClass(c), vdialogENABLE_ITEM, (c))
#define vcontainerDisable(c) \
    vclassSend(vcontainerGetClass(c), vdialogDISABLE_ITEM, (c))
#define vcontainerAppendItem(c, i) \
    vclassSend(vcontainerGetClass(c), vcontainerAPPEND_ITEM, (c, i))
#define vcontainerRemoveItem(c, i) \
    vclassSend(vcontainerGetClass(c), vcontainerREMOVE_ITEM, (c, i))
#define vcontainerDeleteItem(c, i) \
    ((void) vcontainerRemoveItem(c, i))
#define vcontainerSetItemIndex(c, i, n) \
    vclassSend(vcontainerGetClass(c), vcontainerSET_ITEM_INDEX, (c, i, n))
#define vcontainerArrange(c, r) \
    vclassSend(vcontainerGetClass(c), vcontainerARRANGE, (c, r))
#define vcontainerCalcMinSize(c, w, h) \
    vclassSend(vcontainerGetClass(c), vcontainerCALC_MIN_SIZE, (c, w, h))
#define vcontainerGetBorderDecorationSizes(c,t,l,b,r) \
    vclassSend(vcontainerGetClass(c), vcontainerGET_BORDER_DECORATION_SIZES, \
	       (c, t, l, b, r))
#define vcontainerGetTitleDecorationSizes(c,t,l,b,r) \
    vclassSend(vcontainerGetClass(c), vcontainerGET_TITLE_DECORATION_SIZES,\
	       (c, t, l, b, r))
#define vcontainerGetScrollBarDecorationSizes(c,t,l,b,r) \
    vclassSend(vcontainerGetClass(c),  \
	       vcontainerGET_SCROLLBAR_DECORATION_SIZES, (c, t, l, b, r))
#define vcontainerSetData(c, d) \
    vclassSend(vcontainerGetClass(c), vdialogSET_ITEM_DATA, (c, d))
#define vcontainerSetTitleScribed(c, s) \
    vclassSend(vcontainerGetClass(c), vdialogSET_ITEM_TITLE_SCRIBED, (c, s))
#define vcontainerSetBorder(c, f) \
    vclassSend(vcontainerGetClass(c), vdialogSET_ITEM_BORDER, (c, f))
#define vcontainerSetBounds(c, r) \
    vclassSend(vcontainerGetClass(c), vcontainerSET_BOUNDS, (c, r))
#define vcontainerSetFlat(c, f) \
    vclassSend(vcontainerGetClass(c), vcontainerSET_FLAT, (c, f))
#define vcontainerSetScrollX(c, f) \
    vclassSend(vcontainerGetClass(c), vcontainerSET_SCROLL_X, (c, f))
#define vcontainerSetScrollY(c, f) \
    vclassSend(vcontainerGetClass(c), vcontainerSET_SCROLL_Y, (c, f))
#define vcontainerSetFocus(c, i) \
    vclassSend(vcontainerGetClass(c), vcontainerSET_FOCUS, (c, i))
#define vcontainerTestSetFocus(c, i, e) \
    vclassSend(vcontainerGetClass(c), vcontainerTEST_SET_FOCUS, (c, i, e))
#define vcontainerSetDefFocus(c, i) \
    vclassSend(vcontainerGetClass(c), vcontainerSET_DEF_FOCUS, (c, i))
#define vcontainerSetSolution(c, s) \
    vclassSend(vcontainerGetClass(c), vcontainerSET_SOLUTION, (c, s))
#define vcontainerSetSelection(c, i) \
    vclassSend(vcontainerGetClass(c), vcontainerSET_SELECTION, (c, i))

vportEND_CPLUSPLUS_EXTERN_C

#endif /* #ifndef vcontainINCLUDED */


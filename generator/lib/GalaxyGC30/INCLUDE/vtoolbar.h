/* $Id: vtoolbar.h,v 1.32 1997/10/20 22:51:54 bill Exp $ */

/*--------------------------------------------------------------------------
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
                                                                           * 
    vtoolbar.h                                                             * 
                                                                           * 
    C Interface file for Toolbars                                          * 
                                                                           * 
    Copyright (c) 1997 Visix Software Inc.                                 * 
    All rights reserved                                                    * 
                                                                           * 
  -------------------------------------------------------------------------*/

#ifndef vtoolbarINCLUDED
#define vtoolbarINCLUDED

#ifndef  vportINCLUDED
#include <vport.h>
#endif

#ifndef vcontainerINCLUDED
#include vcontainerHEADER
#endif

#ifndef vdockerINCLUDED
#include vdockerHEADER
#endif

#ifndef vformINCLUDED
#include vformHEADER
#endif

#ifndef vtoolbarRearrangerINCLUDED
#include vtoolbarRearrangerHEADER
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C

/*-------------------------------------------------------------------------
 * * * PUBLIC CONSTANT DEFINITIONS  * * * * * * * * * * * * * * * * * * * *
  ------------------------------------------------------------------------*/

/* Attributes */
enum {
    vtoolbarID_ATTRIBUTE_VERTICAL = vcontainerNEXT_ID_ATTRIBUTE,
    vtoolbarID_ATTRIBUTE_WRAP,
    vtoolbarID_ATTRIBUTE_REARRANGEABLE,
    vtoolbarNEXT_ID_ATTRIBUTE
};


/* Pre-interned strings */
#define vtoolbar_Wrap		(_vtoolbarPredefs[_vtoolbar_Wrap])
#define vtoolbar_Rearrangeable  (_vtoolbarPredefs[_vtoolbar_Rearrangeable])
#define vtoolbar_RearrangeCopy	(_vtoolbarPredefs[_vtoolbar_RearrangeCopy])
#define vtoolbar_RearrangeMove  (_vtoolbarPredefs[_vtoolbar_RearrangeMove])
#define vtoolbar_RearrangeNone  (_vtoolbarPredefs[_vtoolbar_RearrangeNone])

/* Toolbar insertion index hints */
enum {
    vtoolbarINSERTION_HINT_NONE = 0,
    vtoolbarINSERTION_HINT_ROW_END,
    vtoolbarINSERTION_HINT_PAST_ROW_END
};
    

/*-------------------------------------------------------------------------
 * * * PUBLIC TYPE DEFINITIONS  * * * * * * * * * * * * * * * * * * * * * *
  ------------------------------------------------------------------------*/

typedef struct vtoolbar 		vtoolbar;
typedef struct vtoolbarClass 		vtoolbarClass;
typedef struct vtoolbarRowInfo          vtoolbarRowInfo;
typedef vinstanceClass 			vtoolbarRowInfoClass;
typedef vsequence			vtoolbarRowInfoSequence;
typedef vsequenceClass			vtoolbarRowInfoSequenceClass;

typedef void (*vtoolbarNoteProc)(
    vtoolbar                     *toolbar,
    vevent                       *event
    );

/*-------------------------------------------------------------------------
 * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * * * * * * * * * * * * *
  ------------------------------------------------------------------------*/

/* Class and object management */
void vtoolbarStartup( 
    void 
    );

vtoolbarClass *vtoolbarGetDefaultClass(
    void
    );

vtoolbarClass *vtoolbarGetClass(
    vtoolbar 		*toolbar
    );

vtoolbar *vtoolbarCreateOfClass(
    vtoolbarClass 	*clas
    );

vtoolbar *vtoolbarCreate(
     void
     );

vtoolbar *vtoolbarClone(
    vtoolbar		*toolbar
    );

void vtoolbarInitOfClass(
    vtoolbar		*toolbar,
    vtoolbarClass	*clas
    );

void vtoolbarInit(
    vtoolbar		*toolbar
    );

void vtoolbarDestroy(
    vtoolbar		*toolbar
    );

void vtoolbarCopy(
    vtoolbar		*toolbar,
    vtoolbar		*target
    );

void vtoolbarCopyInit(
    vtoolbar		*toolbar,
    vtoolbar		*target
    );

vtoolbar *vtoolbarLoad(
    vresource 		res
    );

void vtoolbarLoadInit(
    vtoolbar		*toolbar,
    vresource 		 res
    );

void vtoolbarStore(
    vtoolbar		*toolbar,
    vresource 		 res
    );

/* Inheritance accessors */

vform *vtoolbarGetForm(
    vtoolbar 		*toolbar
    );

vcontainer *vtoolbarGetContainer(
    vtoolbar 		*toolbar
    );

vdialogItem *vtoolbarGetItem(
    vtoolbar 		*toolbar
    );

vobjectAttributed *vtoolbarGetObject(
    vtoolbar 		*toolbar
    );

vobservable *vtoolbarGetObservable(
    vtoolbar 		*toolbar
    );

/* Superclass API equivalents */

void vtoolbarEnable(
    vtoolbar		*toolbar
    );

void vtoolbarDisable(
    vtoolbar		*toolbar
    );

int vtoolbarIsEnabled(
    vtoolbar		*toolbar
    );

void vtoolbarShow(
    vtoolbar		*toolbar
    );

void vtoolbarHide(
    vtoolbar		*toolbar
    );

int vtoolbarIsShown(
    vtoolbar		*toolbar
    );

void vtoolbarSetBorder(
    vtoolbar		*toolbar,
    int			flag
    );

int vtoolbarHasBorder(
    vtoolbar		*toolbar
    );

void vtoolbarSetData(
    vtoolbar		*toolbar,
    const void          *data
    );

const void *vtoolbarGetData(
    vtoolbar		*toolbar
    );

void vtoolbarSetNotify(
    vtoolbar		*toolbar,
    vtoolbarNoteProc	 noteProc
    );

vtoolbarNoteProc vtoolbarGetNotify(
    vtoolbar		*toolbar
    );

void vtoolbarSetTitle(
    vtoolbar		*toolbar,
    const vchar		*title
    );

void vtoolbarSetTitleScribed(
    vtoolbar		*toolbar,
    vscribe		*title
    );

const vchar *vtoolbarGetTitle(
    vtoolbar		*toolbar
    );

void vtoolbarSetBounds(
    vtoolbar		*toolbar,
    const vrect		*bounds
    );

const vrect *vtoolbarGetBounds(
    vtoolbar		*toolbar
    );

const vrect *vtoolbarGetContent(
    vtoolbar 		*toolbar
    );

void vtoolbarArrange(
    vtoolbar 		*toolbar,
    const vrect		*rect
    );

void vtoolbarConstrainSize(
    vtoolbar 		*toolbar,
    int 		*w,
    int 		*h
    );

void vtoolbarCalcMinSize(
    vtoolbar 		*toolbar,
    int			*w,
    int			*h
    );

void vtoolbarAddField(
    vtoolbar            *toolbar,
    vfield              *field
    );

vfield *vtoolbarFindFieldLinkedToItem(
    vtoolbar            *toolbar,
    const vname         *itemTag
    );

vbool vtoolbarHasField(
    vtoolbar            *toolbar,
    vfield              *field
    );

void vtoolbarLinkField(
    vtoolbar            *toolbar,
    const vname         *tag,
    vfield              *field
    );

vbool vtoolbarIsItemLinked(
    vtoolbar            *toolbar,
    const vname         *tag
    );

void vtoolbarRelinkFields(
    vtoolbar            *toolbar
    );

void vtoolbarRemoveField(
    vtoolbar            *toolbar,
    vfield              *field
    );

void vtoolbarUnlinkField(
    vtoolbar            *toolbar,
    const vname         *tag
    );


/* Itemlist management */

vdialogItemList *vtoolbarGetItemList(
    vtoolbar		*toolbar
    );

void vtoolbarAppendItem(
    vtoolbar		*toolbar,
    vdialogItem		*item
    );

vdialogItem *vtoolbarRemoveItem(
    vtoolbar		*toolbar,
    vdialogItem		*item
    );

int vtoolbarGetItemCount(
    vtoolbar 		*toolbar
    );

int vtoolbarGetItemIndex(
    vtoolbar 		*toolbar,
    vdialogItem 	*item
    );

void vtoolbarSetItemIndex(
    vtoolbar 		*toolbar,
    vdialogItem 	*item,
    int			 index
    );

vdialogItem *vtoolbarGetItemAt(
    vtoolbar 		*toolbar,
    int 		 index
    );

vdialogItem *vtoolbarFindItem(
    vtoolbar		*toolbar,
    const vname		*tag
    );

void vtoolbarInsertItem(
    vtoolbar		*toolbar,
    vdialogItem 	*item,
    int 		 index
    );

/* Docker management */

vdocker *vtoolbarGetDocker(
    vtoolbar		*toolbar
    );

void vtoolbarSetFloating(
    vtoolbar		*toolbar,
    vbool		 floating
    );

vbool vtoolbarIsFloating(
    vtoolbar		*toolbar
    );

void vtoolbarSetLocked(
    vtoolbar		*toolbar,
    vbool		 locked
    );

vbool vtoolbarIsLocked(
    vtoolbar		*toolbar
    );

/* Functionality introduced in toolbar class */

void vtoolbarSetVertical(
    vtoolbar 		*toolbar,
    vbool 		 vertical
    );

vbool vtoolbarIsVertical(
    vtoolbar 		*toolbar
    );

void vtoolbarSetWrap(
    vtoolbar		*toolbar,
    vbool		 wrap
    );

vbool vtoolbarHasWrap(
    vtoolbar		*toolbar
    );

void vtoolbarSetRearrangeable(
    vtoolbar		*toolbar,
    vbool		 rearrange
    );

vbool vtoolbarIsRearrangeable(
    vtoolbar		*toolbar
    );

void vtoolbarSetRearranger(
    vtoolbar		*toolbar,
    vtoolbarRearranger	*rearranger
    );

vtoolbarRearranger *vtoolbarGetRearranger(
    vtoolbar		*toolbar
    );

vtoolbarRearranger *vtoolbarCreateToolbarRearranger(
    vtoolbar			*toolbar
    );

int vtoolbarDetermineInsertionIndex(
    vtoolbar			*targetItem,
    const vrect			*dragRect,
    unsigned short		*placementHint
    );


/* * * * * * * Toolbar Row Info * * * * * * * * * * * * * * * * * * * * * */

vtoolbarRowInfoSequence *vtoolbarMakeRowInfoSequence(
    vtoolbar		*toolbar
    );

vinstance *vtoolbarGetRowInfoInstance(
    vtoolbarRowInfo	*rowInfo
    );

vtoolbarRowInfoClass *vtoolbarGetDefaultRowInfoClass(
    void
    );

vtoolbarRowInfo *vtoolbarCreateRowInfoOfClass(
    vtoolbarRowInfoClass *clas
    );

vtoolbarRowInfo *vtoolbarCreateRowInfo(
    void
    );

void vtoolbarInitRowInfoOfClass(
    vtoolbarRowInfo	 *rowInfo,
    vtoolbarRowInfoClass *clas
    );

void vtoolbarInitRowInfo(
    vtoolbarRowInfo	*rowInfo
    );

void vtoolbarDestroyRowInfo(
    vtoolbarRowInfo	*rowInfo
    );

const vrect *vtoolbarGetRowInfoRect(
    vtoolbarRowInfo	*rowInfo
    );

int vtoolbarGetRowInfoSeparatorWidth(
    vtoolbarRowInfo	*rowInfo
    );

int vtoolbarGetRowInfoStartIndex(
    vtoolbarRowInfo	*rowInfo
    );

int vtoolbarGetRowInfoEndIndex(
    vtoolbarRowInfo	*rowInfo
    );

void vtoolbarSetRowInfoRect(
    vtoolbarRowInfo	*rowInfo,
    const vrect		*rect
    );

void vtoolbarSetRowInfoSeparatorWidth(
    vtoolbarRowInfo	*rowInfo,
    int			 width
    );

void vtoolbarSetRowInfoStartIndex(
    vtoolbarRowInfo	*rowInfo,
    int			 startIndex
    );

void vtoolbarSetRowInfoEndIndex(
    vtoolbarRowInfo	*rowInfo,
    int			 endIndex
    );

/*-------------------------------------------------------------------------
 * * * PRIVATE CONSTANT DEFINITIONS * * * * * * * * * * * * * * * * * * * *
  ------------------------------------------------------------------------*/

/*
 * Global toolbar strings
 */

enum {
    _vtoolbar_Wrap,
    _vtoolbar_Rearrangeable,
    _vtoolbar_RearrangeCopy,
    _vtoolbar_RearrangeMove,
    _vtoolbar_RearrangeNone,
    _vtoolbar_Count
};

enum {
    _vtoolbarFlagVERTICAL	 = 0x0001,
    _vtoolbarFlagWRAP		 = 0x0002,
    _vtoolbarFlagREARRANGEABLE	 = 0x0004,
    _vtoolbarFlagUPDATE_LOCK	 = 0x0008,
    _vtoolbarFlagDRAG_FINISHING	 = 0x0010,
    _vtoolbarFlagSWITCHING_VERT	 = 0x0020,
    _vtoolbarFlagSEG_CACHE_VALID = 0x0040
};


/*-------------------------------------------------------------------------
 * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * * * * * * * * * * * * * *
  ------------------------------------------------------------------------*/

struct vtoolbar {
    vform		 form;
    int			 flags;
    vtoolbarRearranger	*rearranger;
    vtoolbarRowInfoSequence *segCache;
    vtoolbarRowInfoSequence *rowCache;
};

#define vtoolbarCLASS(SUPER, TOOLBAR, NOTIFY)                                \
  vformCLASS(SUPER, TOOLBAR, NOTIFY);                                        \
  vclassMETHOD(vtoolbarSET_VERTICAL, (TOOLBAR *toolbar, vbool vertical));    \
  vclassMETHOD(vtoolbarSET_WRAP, (TOOLBAR *toolbar, vbool wrap));            \
  vclassMETHOD(vtoolbarSET_REARRANGEABLE,                                    \
               (TOOLBAR *toolbar, vbool rearrange));                         \
  vclassMETHOD(vtoolbarSET_REARRANGER, (TOOLBAR *toolbar,                    \
                                        vtoolbarRearranger *rearranger));    \
  vclassMETHOD(vtoolbarINSERT_ITEM,                                          \
                   (TOOLBAR *toolbar, vdialogItem *item, int index));        \
  vclassMETHOD_RET(vtoolbarCREATE_TOOLBAR_REARRANGER,                        \
                   vtoolbarRearranger*, (TOOLBAR *toolbar))
                    

struct vtoolbarClass {
  vtoolbarCLASS( vtoolbarClass, vtoolbar, vtoolbarNoteProc );
};


/* vtoolbarRowInfo */

struct vtoolbarRowInfo {
    vinstance		instance;
    int			startIndex;
    int			endIndex;
    vrect		rect;
    int			sepWidth;
};



/*-------------------------------------------------------------------------
 * * * PRIVATE GLOBAL VARIABLES * * * * * * * * * * * * * * * * * * * * * *
  ------------------------------------------------------------------------*/

extern vportLINK const vchar 		*_vtoolbarPredefs[];


/*-------------------------------------------------------------------------
 * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * * * * * * * * *
  ------------------------------------------------------------------------*/

/* Class and object management */

#define vtoolbarGetClass(t)  \
  ((vtoolbarClass*)vdialogGetItemClass(vtoolbarGetItem(t)))
#define vtoolbarCreateOfClass(c) \
  ((vtoolbar*)vdialogCreateItemOfClass((vdialogItemClass*)(c)))
#define vtoolbarCreate() vtoolbarCreateOfClass(vtoolbarGetDefaultClass())
#define vtoolbarClone(t) ((vtoolbar*)vformClone(vtoolbarGetForm(t)))
#define vtoolbarInitOfClass(t, c)  \
  vformInitOfClass(vtoolbarGetForm(t), (vformClass*)(c))
#define vtoolbarInit(t) vtoolbarInitOfClass(t, vtoolbarGetDefaultClass())
#define vtoolbarDestroy(t) vformDestroy(vtoolbarGetForm(t))
#define vtoolbarCopy(s, t) \
  vformCopy(vtoolbarGetForm(s), vtoolbarGetForm(t))
#define vtoolbarCopyInit(s, t) \
  vformCopyInit(vtoolbarGetForm(s), vtoolbarGetForm(t))
#define vtoolbarLoad(r) ((vtoolbar*)vformLoad(r))
#define vtoolbarLoadInit(t, r) \
  ((vtoolbar*)vformLoadInit(vtoolbarGetForm(t), r))
#define vtoolbarStore(t, r) vformStore(vtoolbarGetForm(t), r);

/* Inheritance accessors */

#define vtoolbarGetForm(t) vportBASE_OBJECT(t, form)
#define vtoolbarGetContainer(t) vformGetContainer(vtoolbarGetForm(t))
#define vtoolbarGetItem(t) vformGetItem(vtoolbarGetForm(t))
#define vtoolbarGetObject(t) vformGetObject(vtoolbarGetForm(t))
#define vtoolbarGetObservable(t) vformGetObservable(vtoolbarGetForm(t))

/* Superclass API equivalents */

#define vtoolbarEnable(t) vformEnable(vtoolbarGetForm(t))
#define vtoolbarDisable(t) vformDisable(vtoolbarGetForm(t))
#define vtoolbarIsEnabled(t) vformIsEnabled(vtoolbarGetForm(t))
#define vtoolbarShow(t) vdialogShowItem(vtoolbarGetItem(t))
#define vtoolbarHide(t) vdialogHideItem(vtoolbarGetItem(t))
#define vtoolbarIsShown(t) vdialogItemIsShown(vtoolbarGetItem(t))
#define vtoolbarSetBorder(t, r) vformSetBorder(vtoolbarGetForm(t), r)
#define vtoolbarHasBorder(t) vformHasBorder(vtoolbarGetForm(t))
#define vtoolbarSetData(t, d) vformSetData(vtoolbarGetForm(t), d)
#define vtoolbarGetData(t) vformGetData(vtoolbarGetForm(t))
#define vtoolbarSetNotify(t, n) vformSetNotify(vtoolbarGetForm(t), n)
#define vtoolbarGetNotify(t) vformGetNotify(vtoolbarGetForm(t))
#define vtoolbarSetTitle(t, s) vformSetTitle(vtoolbarGetForm(t), s)
#define vtoolbarSetTitleScribed(t, s) \
  vformSetTitleScribed(vtoolbarGetForm(t), s)
#define vtoolbarGetTitle(t) vformGetTitle(vtoolbarGetForm(t))
#define vtoolbarSetBounds(t, r) vformSetBounds(vtoolbarGetForm(t), r)
#define vtoolbarGetBounds(t) vformGetBounds(vtoolbarGetForm(t))
#define vtoolbarGetContent(t) vformGetContent(vtoolbarGetForm(t))
#define vtoolbarArrange(t, r) vformArrange(vtoolbarGetForm(t), r)
#define vtoolbarConstrainSize(t, w, h) \
  vdialogConstrainItemSize(vtoolbarGetItem(t), w, h)
#define vtoolbarCalcMinSize(t, w, h) vformCalcMinSize(vtoolbarGetForm(t), w, h)
#define vtoolbarAddField(t, f)     vformAddField(vtoolbarGetForm(t), f)
#define vtoolbarHasField(t, f)     vformHasField(vtoolbarGetForm(t), f)
#define vtoolbarLinkField(t, n, f) vformLinkField(vtoolbarGetForm(t), n, f)
#define vtoolbarIsItemLinked(t, n) vformIsItemLinked(vtoolbarGetForm(t), n)
#define vtoolbarRelinkFields(t)    vformRelinkFields(vtoolbarGetForm(t))
#define vtoolbarRemoveField(t, f)  vformRemoveField(vtoolbarGetForm(t), f)
#define vtoolbarUnlinkField(t, n)  vformUnlinkField(vtoolbarGetForm(t), n)
#define vtoolbarFindFieldLinkedToItem(t, i) \
    vformFindFieldLinkedToItem(vtoolbarGetForm(t), i)

/* Itemlist management */

#define vtoolbarGetItemList(t) vformGetItemList(vtoolbarGetForm(t))
#define vtoolbarAppendItem(t,d) vformAppendItem(vtoolbarGetForm(t), d)
#define vtoolbarRemoveItem(t,d) \
  vcontainerRemoveItem(vtoolbarGetContainer(t), d)
#define vtoolbarGetItemCount(t) vformGetItemCount(vtoolbarGetForm(t))
#define vtoolbarGetItemIndex(t, d) \
  vformGetItemIndex(vtoolbarGetForm(t), d) 
#define vtoolbarSetItemIndex(t, d, i) \
  vformSetItemIndex(vtoolbarGetForm(t), d, i)
#define vtoolbarGetItemAt(t,i) vformGetItemAt(vtoolbarGetForm(t),i)
#define vtoolbarFindItem(t, n) vformFindItem(vtoolbarGetForm(t), n)
#define vtoolbarInsertItem(t, d, i) \
  vclassSend(vtoolbarGetClass(t), vtoolbarINSERT_ITEM, (t, d, i))

/* New toolbar methods */

#define vtoolbarSetVertical(t, b) \
  vclassSend(vtoolbarGetClass(t), vtoolbarSET_VERTICAL, (t, b))
#define vtoolbarSetWrap(t, b) \
  vclassSend(vtoolbarGetClass(t), vtoolbarSET_WRAP, (t, b))
#define vtoolbarSetRearrangeable(t, b) \
  vclassSend(vtoolbarGetClass(t), vtoolbarSET_REARRANGEABLE, (t, b))
#define vtoolbarSetRearranger(t, r) \
  vclassSend(vtoolbarGetClass(t), vtoolbarSET_REARRANGER, (t, r))
#define vtoolbarCreateToolbarRearranger(t) \
  vclassSend(vtoolbarGetClass(t), vtoolbarCREATE_TOOLBAR_REARRANGER, (t))

#define vtoolbarIsVertical(t) \
  ((vbool)(((t)->flags & _vtoolbarFlagVERTICAL)!=0))
#define vtoolbarHasWrap(t) (((t)->flags & _vtoolbarFlagWRAP) != 0)
#define vtoolbarIsRearrangeable(t) \
  (((t)->flags & _vtoolbarFlagREARRANGEABLE) != 0)
#define vtoolbarGetRearranger(t)    ((t)->rearranger)

/* Row info functionality */
#define vtoolbarGetRowInfoInstance(r) vportBASE_OBJECT(r, instance)
#define vtoolbarCreateRowInfoOfClass(c) \
  ((vtoolbarRowInfo*)vinstanceCreateOfClass((vinstanceClass*)(c)))
#define vtoolbarCreateRowInfo() \
  ((vtoolbarRowInfo*)vtoolbarCreateRowInfoOfClass( \
    vtoolbarGetDefaultRowInfoClass()))
#define vtoolbarInitRowInfo(r) \
  vtoolbarInitRowInfoOfClass(r, vtoolbarGetRowInfoClass())
#define vtoolbarDestroyRowInfo(r) \
  vinstanceDestroy(vtoolbarGetRowInfoInstance(r))
#define vtoolbarGetRowInfoRect(r)              ((const vrect*) &((r)->rect))
#define vtoolbarGetRowInfoSeparatorWidth(r)    ((r)->sepWidth)
#define vtoolbarGetRowInfoStartIndex(r)        ((r)->startIndex)
#define vtoolbarGetRowInfoEndIndex(r)          ((r)->endIndex)
#define vtoolbarSetRowInfoRect(r, s)           ((r)->rect = *(s))
#define vtoolbarSetRowInfoSeparatorWidth(r, w) ((r)->sepWidth = (w))
#define vtoolbarSetRowInfoStartIndex(r, s)     ((r)->startIndex = (s))
#define vtoolbarSetRowInfoEndIndex(r, e)       ((r)->endIndex = (e))

vportEND_CPLUSPLUS_EXTERN_C

#endif /* vtoolbarINCLUDED */


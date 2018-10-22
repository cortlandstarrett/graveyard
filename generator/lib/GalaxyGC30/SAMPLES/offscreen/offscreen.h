/* $Id: offscreen.h,v 1.1 1997/10/24 19:36:01 bill Exp $ */

#ifndef OffscreenDialogINCLUDED
#define OffscreenDialogINCLUDED

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

#ifndef  vdialogINCLUDED
#include vdialogHEADER
#endif

#ifndef  vdialogItemINCLUDED
#include vdialogItemHEADER
#endif

#ifndef  vmutexINCLUDED
#include vHEADER
#endif

#ifdef vportWIN_MS_WINDOWS
#define OffscreenDialogUSE_OFFSCREEN
#endif

/*
 * * * * * * * * * * PUBLIC CONSTANT DEFINITIONS * * * * * * * * * *
 */

/*
 * dialogs
 */

enum {
    OffscreenDialogNEXT_ID_ATTRIBUTE        = vdialogNEXT_ID_ATTRIBUTE
};

enum {
    OffscreenDialogNEXT_SELECT      = vdialogNEXT_SELECT
};

/*
 * * * * * * * * * * PUBLIC TYPE DEFINITIONS * * * * * * * * * *
 */

/*
 * dialogs
 */

#ifdef OffscreenDialogUSE_OFFSCREEN
typedef struct OffscreenDialog              OffscreenDialog;
typedef struct OffscreenDialogClass         OffscreenDialogClass;
#else
typedef vdialog		  OffscreenDialog;
typedef vdialogClass	  OffscreenDialogClass;
#endif

/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */

void OffscreenDialogStartup(void);


/*
 * dialogs
 */

OffscreenDialogClass *OffscreenDialogGetDefaultClass(
    void
    );

OffscreenDialog *OffscreenDialogCreateOfClass(
    OffscreenDialogClass                   *clas
    );

OffscreenDialog *OffscreenDialogCreate(
    void
    );

OffscreenDialog *OffscreenDialogClone(
    OffscreenDialog                        *dialog
    );

void OffscreenDialogInitOfClass(
    OffscreenDialog                        *dialog,
    OffscreenDialogClass                   *clas
    );

void OffscreenDialogInit(
    OffscreenDialog                        *dialog
    );

void OffscreenDialogDestroy(
    OffscreenDialog                        *dialog
    );

void OffscreenDialogCopy(
    OffscreenDialog                        *dialog,
    OffscreenDialog                        *target
    );

void OffscreenDialogCopyInit(
    OffscreenDialog                        *dialog,
    OffscreenDialog                        *target
    );

OffscreenDialog *OffscreenDialogLoad(
    vresource                       resource
    );

void OffscreenDialogLoadInit(
    OffscreenDialog                        *dialog,
    vresource                       resource
    );

void OffscreenDialogStore(
    OffscreenDialog                        *dialog,
    vresource                       resource
    );

vbool OffscreenDialogDisplayHelp(
    OffscreenDialog                        *dialog,
    vhelprequest		   *request
    );

void OffscreenDialogOpen(
    OffscreenDialog                        *dialog
    );

void OffscreenDialogClose(
    OffscreenDialog                        *dialog
    );

void OffscreenDialogNotify(
    OffscreenDialog                        *dialog,
    vevent                         *event
    );

void OffscreenDialogMove(
    OffscreenDialog                        *dialog,
    int                             x,
    int                             y
    );

void OffscreenDialogResize(
    OffscreenDialog                        *dialog,
    int                             w,
    int                             h
    );

void OffscreenDialogPlace(
    OffscreenDialog                        *dialog,
    OffscreenDialog                        *base,
    int                             modeX,
    int                             modeY
    );

void OffscreenDialogPlaceWindow(
    OffscreenDialog                        *dialog,
    vwindow			   *base,
    int                             modeX,
    int                             modeY
    );

void OffscreenDialogAppendItem(
    OffscreenDialog                *dialog,
    vdialogItem                    *item
    );

vdialogItem *OffscreenDialogRemoveItem(
    OffscreenDialog                        *dialog,
    vdialogItem                    *item
    );

void OffscreenDialogSetItemIndex(
    OffscreenDialog                        *dialog,
    vdialogItem                    *item,
    int                             index
    );

void OffscreenDialogArrange(
    OffscreenDialog                        *dialog,
    const vrect                    *rect
    );

void OffscreenDialogCalcMinSize(
    OffscreenDialog                        *dialog,
    int                            *w,
    int                            *h
    );

void OffscreenDialogSetNotify(
    OffscreenDialog                        *dialog,
    vdialogNoteProc	            noteProc
    );

void OffscreenDialogSetData(
    OffscreenDialog                        *dialog,
    const void                     *data
    );

void OffscreenDialogSetTitle(
    OffscreenDialog                        *dialog,
    const vchar                    *title
    );

void OffscreenDialogSetTitleScribed(
    OffscreenDialog                        *dialog,
    vscribe                        *scribe
    );

void OffscreenDialogSetIcon(
    OffscreenDialog                        *dialog,
    vimage                         *icon
    );

void OffscreenDialogSetMaxSize(
    OffscreenDialog                        *dialog,
    int                             w,
    int                             h
    );

void OffscreenDialogSetMenu(
    OffscreenDialog                        *dialog,
    vmenu                          *menu
    );

void OffscreenDialogSetCloseHook(
    OffscreenDialog                        *dialog,
    vdialogHookFunc                 closeHook
    );

void OffscreenDialogSetFocus(
    OffscreenDialog                        *dialog,
    vdialogItem                    *item
    );

vbool OffscreenDialogTestSetFocus(
    OffscreenDialog                        *dialog,
    vdialogItem                    *item,
    vevent			   *event
    );

void OffscreenDialogSetConfirm(
    OffscreenDialog                        *dialog,
    vdialogItem                    *item
    );

void OffscreenDialogSetAbandon(
    OffscreenDialog                        *dialog,
    vdialogItem                    *item
    );

void OffscreenDialogSetDefFocus(
    OffscreenDialog                        *dialog,
    vdialogItem                    *item
    );

void OffscreenDialogSetDrag(
    OffscreenDialog                        *dialog,
    vdialogItem                    *item
    );

void OffscreenDialogSetSolution(
    OffscreenDialog                        *dialog,
    vspringSolution                *solution
    );

vobjectAttributed *OffscreenDialogGetObject(
    OffscreenDialog                        *dialog
    );

vwindow *OffscreenDialogGetWindow(
    OffscreenDialog                        *dialog
    );

OffscreenDialogClass *OffscreenDialogGetClass(
    OffscreenDialog                        *dialog
    );

const void *OffscreenDialogGetData(
    OffscreenDialog                        *dialog
    );

const vchar *OffscreenDialogGetTitle(
    OffscreenDialog                        *dialog
    );

vimage *OffscreenDialogGetIcon(
    OffscreenDialog                        *dialog
    );

int OffscreenDialogIsOpen(
    OffscreenDialog                        *dialog
    );

int OffscreenDialogGetMaxW(
    OffscreenDialog                        *dialog
    );

int OffscreenDialogGetMaxH(
    OffscreenDialog                        *dialog
    );

vmenu *OffscreenDialogGetMenu(
    OffscreenDialog                        *dialog
    );

vdialogHookFunc OffscreenDialogGetCloseHook(
    OffscreenDialog                        *dialog
    );

vdialogItemList *OffscreenDialogGetItemList(
    OffscreenDialog                        *dialog
    );

vdialogItem *OffscreenDialogGetFocus(
    OffscreenDialog                        *dialog
    );

vdialogItem *OffscreenDialogGetConfirm(
    OffscreenDialog                        *dialog
    );

vdialogItem *OffscreenDialogGetAbandon(
    OffscreenDialog                        *dialog
    );

vdialogItem *OffscreenDialogGetDefFocus(
    OffscreenDialog                        *dialog
    );

vdialogItem *OffscreenDialogGetDrag(
    OffscreenDialog                        *dialog
    );

vspringSolution *OffscreenDialogGetSolution(
    OffscreenDialog                        *dialog
    );

int OffscreenDialogGetItemCount(
    OffscreenDialog                        *dialog
    );

vdialogItem *OffscreenDialogGetItemAt(
    OffscreenDialog                        *dialog,
    int                             index
    );

int OffscreenDialogGetItemIndex(
    OffscreenDialog                        *dialog,
    vdialogItem                    *item
    );

vdialogItem *OffscreenDialogFindItem(
    OffscreenDialog                        *dialog,
    const vname                    *tag
    );

void OffscreenDialogLock(
    void
    );

void OffscreenDialogUnlock(
    void
    );

void OffscreenDialogLockWithHandling(
    void
    );

void OffscreenDialogUnockWithHandling(
    void
    );

/*
 * * * * * * * * * * PRIVATE CONSTANT DEFINITIONS * * * * * * * * * *
 */


/*
 * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * *
 */

/*
 * dialogs
 */

#ifdef OffscreenDialogUSE_OFFSCREEN

struct OffscreenDialog {
    vdialog                         dialog;
    vbool                           resized;
};

#define OffscreenDialogCLASS(SUPER, DIALOG, NOTIFY, ITEM, LIST)               \
    vdialogCLASS(SUPER, DIALOG, NOTIFY, ITEM, LIST);                          \
    vclassVARIABLE(OffscreenDialogIMAGE, vimage*)

struct OffscreenDialogClass {
    OffscreenDialogCLASS(OffscreenDialogClass, OffscreenDialog,  
                         vdialogNoteProc, vdialogItem, vdialogItemList);
};

#endif /* OffscreenDialogUSE_OFFSCREEN */


/*
 * * * * * * * * * * PRIVATE VARIABLE DECLARATIONS  * * * * * * * * * * * *
 */

extern vportLINK vmutex                       _offscreenDialogMutex;

/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * *
 */

#ifdef OffscreenDialogUSE_OFFSCREEN

#define OffscreenDialogGetDialog(d)  vportBASE_OBJECT((d), dialog)
#define OffscreenDialogGetWindow(d) \
   vdialogGetWindow(OffscreenDialogGetDialog(d))
#define OffscreenDialogGetObject(d) \
   vwindowGetObject(OffscreenDialogGetWindow(d))

#define OffscreenDialogCreateOfClass(c) \
    ((OffscreenDialog*)vdialogCreateOfClass((vdialogClass*)(c)))
#define OffscreenDialogCreate() \
    OffscreenDialogCreateOfClass(OffscreenDialogGetDefaultClass())
#define OffscreenDialogClone(d) \
   ((OffscreenDialog*)vdialogClone((vdialog*)(d)))
#define OffscreenDialogInitOfClass(d, c) \
    vdialogInitOfClass(OffscreenDialogGetDialog(d), (vdialogClass*)(c))
#define OffscreenDialogInit(d) \
    OffscreenDialogInitOfClass(d, OffscreenDialogGetDefaultClass())
#define OffscreenDialogCopyInit(d, t) \
    vdialogCopyInit(OffscreenDialogGetDialog(d), OffscreenDialogGetDialog(t))
#define OffscreenDialogCopy(d, t) \
    vdialogCopy(OffscreenDialogGetDialog(d), OffscreenDialogGetDialog(t))
#define OffscreenDialogStore(d, r) \
    vdialogStore(OffscreenDialogGetDialog(d), r)
#define OffscreenDialogLoad(r)            ((OffscreenDialog*)vdialogLoad(r))
#define OffscreenDialogLoadInit(d, r)   \
    vdialogLoadInit(OffscreenDialogGetDialog(d), r)
#define OffscreenDialogDestroy(d) \
    vdialogDestroy(OffscreenDialogGetDialog(d))

#define OffscreenDialogMove(d, x, y)  \
    vwindowMove(OffscreenDialogGetWindow(d), x, y)
#define OffscreenDialogResize(d, w, h) \
    vwindowResize(OffscreenDialogGetWindow(d), w, h)
#define OffscreenDialogSetTitle(d, s) \
    vwindowSetTitle(OffscreenDialogGetWindow(d), s)

#define OffscreenDialogGetClass(d) \
    ((OffscreenDialogClass*)vwindowGetClass(OffscreenDialogGetWindow(d)))

#define OffscreenDialogGetNotify(d) \
    ((vdialogNoteProc)vwindowGetNotify(OffscreenDialogGetWindow(d)))

#define OffscreenDialogSetNotify(d, n) \
    vwindowSetNotify((vwindow *)(d), (vwindowNoteProc)(n))

#define OffscreenDialogPlaceWindow(d, b, mx, my) \
    vwindowPlace(OffscreenDialogGetWindow(d), b, mx, my)
#define OffscreenDialogPlace(d, b, mx, my) \
    vwindowPlace(OffscreenDialogGetWindow(d), (vwindow *)(b), mx, my)

#define OffscreenDialogGetData(d)  vwindowGetData(OffscreenDialogGetWindow(d))
#define OffscreenDialogGetTitle(d) vwindowGetTitle(OffscreenDialogGetWindow(d))
#define OffscreenDialogGetIcon(d)  vwindowGetIcon(OffscreenDialogGetWindow(d))
#define OffscreenDialogIsOpen(d)   vwindowIsOpen(OffscreenDialogGetWindow(d))
#define OffscreenDialogGetMaxW(d)  vwindowGetMaxW(OffscreenDialogGetWindow(d))
#define OffscreenDialogGetMaxH(d)  vwindowGetMaxH(OffscreenDialogGetWindow(d))
#define OffscreenDialogDisplayHelp(d, r)  vwindowDisplayHelp(OffscreenDialogGetWindow(d), r)
#define OffscreenDialogOpen(d)	vwindowOpen(OffscreenDialogGetWindow(d))
#define OffscreenDialogClose(d)	vwindowClose(OffscreenDialogGetWindow(d))
#define OffscreenDialogNotify(d, e) vwindowNotify(OffscreenDialogGetWindow(d), e)
#define OffscreenDialogSetData(d, p)  vwindowSetData(OffscreenDialogGetWindow(d), p)
#define OffscreenDialogSetTitleScribed(d, s) \
    vwindowSetTitleScribed(OffscreenDialogGetWindow(d), s)
#define OffscreenDialogSetIcon(d, i)	    vwindowSetIcon(OffscreenDialogGetWindow(d), i)
#define OffscreenDialogSetMaxSize(d, x, y)  vwindowSetMaxSize(OffscreenDialogGetWindow(d), x, y)
#define OffscreenDialogGetMenu(d)	\
    vdialogGetMenu(OffscreenDialogGetDialog(d))
#define OffscreenDialogGetCloseHook(d)	\
    vdialogGetCloseHook(OffscreenDialogGetDialog(d))
#define OffscreenDialogGetItemList(d)    \
    vdialogGetItemList(OffscreenDialogGetDialog(d))
#define OffscreenDialogGetFocus(d)    \
    vdialogGetItemListFocus(OffscreenDialogGetItemList(d))
#define OffscreenDialogGetConfirm(d)  \
    vdialogGetItemListConfirm(OffscreenDialogGetItemList(d))
#define OffscreenDialogGetAbandon(d)  \
    vdialogGetItemListAbandon(OffscreenDialogGetItemList(d))
#define OffscreenDialogGetDefFocus(d) \
    vdialogGetItemListDefFocus(OffscreenDialogGetItemList(d))
#define OffscreenDialogGetDrag(d)  \
    vdialogGetItemListDrag(OffscreenDialogGetItemList(d))
#define OffscreenDialogGetSolution(d) \
    vdialogGetItemListSolution(OffscreenDialogGetItemList(d))
#define OffscreenDialogGetItemCount(d) \
    vdialogGetItemListItemCount(OffscreenDialogGetItemList(d))
#define OffscreenDialogGetItemAt(d, i) \
    vdialogGetItemListItemAt(OffscreenDialogGetItemList(d), i)
#define OffscreenDialogGetItemIndex(d, i) \
    vdialogGetItemListItemIndex(OffscreenDialogGetItemList(d), i)
#define OffscreenDialogFindItem(d, t)  \
    vdialogFindItemList(OffscreenDialogGetItemList(d), t)

#else /* OffscreenDialogUSE_OFFSCREEN */

#define OffscreenDialogCreateOfClass(c)  vdialogCreateOfClass(c)
#define OffscreenDialogCreate() vdialogCreate()
#define OffscreenDialogClone(d)  vdialogClone(d)
#define OffscreenDialogInitOfClass(d,c) vdialogInitOfClass(d,c)
#define OffscreenDialogInit(d)  vdialogInit(d)
#define OffscreenDialogDestroy(d)  vdialogDestroy(d)
#define OffscreenDialogCopy(d,t) vdialogCopy(d,t)
#define OffscreenDialogCopyInit(d,t) vdialogCopyInit(d,t)
#define OffscreenDialogLoad(r)  vdialogLoad(r)
#define OffscreenDialogLoadInit(d,r) vdialogLoadInit(d,r)
#define OffscreenDialogStore(d,r) vdialogStore(d,r)
#define OffscreenDialogDisplayHelp(d,r) vdialogDisplayHelp(d,r)
#define OffscreenDialogOpen(d)  vdialogOpen(d)
#define OffscreenDialogClose(d)  vdialogClose(d)
#define OffscreenDialogNotify(d,e) vdialogNotify(d,e)
#define OffscreenDialogMove(d,x,y) vdialogMove(d,x,y)
#define OffscreenDialogResize(d,w,h) vdialogResize(d,w,h)
#define OffscreenDialogPlace(d,b,x,y) vdialogPlace(d,b,x,y)
#define OffscreenDialogPlaceWindow(d,b,x,y) vdialogPlaceWindow(d,b,x,y)
#define OffscreenDialogAppendItem(d,i) vdialogAppendItem(d,i)
#define OffscreenDialogRemoveItem(d,i) vdialogRemoveItem(d,i)
#define OffscreenDialogSetItemIndex(d,i,n) DialogSetItemIndex(d,i,n)
#define OffscreenDialogArrange(d,r) vdialogArrange(d,r)
#define OffscreenDialogCalcMinSize(d,w,h) vdialogCalcMinSize(d,w,h)
#define OffscreenDialogSetNotify(d,n) vdialogSetNotify(d,n)
#define OffscreenDialogSetData(d,p) vdialogSetData(d,p)
#define OffscreenDialogSetTitle(d,t) vdialogSetTitle(d,t)
#define OffscreenDialogSetTitleScribed(d,s) vdialogSetTitleScribed(d,s)
#define OffscreenDialogSetIcon(d,i) vdialogSetIcon(d,i)
#define OffscreenDialogSetMaxSize(d,w,h) vdialogSetMaxSize(d,w,h)
#define OffscreenDialogSetMenu(d,m) vdialogSetMenu(d,m)
#define OffscreenDialogSetCloseHook(d,c) vdialogSetCloseHook(d,c)
#define OffscreenDialogSetFocus(d,i) vdialogSetFocus(d,i)
#define OffscreenDialogTestSetFocus(d,i,e) vdialogTestSetFocus(d,i,e)
#define OffscreenDialogSetConfirm(d,i) vdialogSetConfirm(d,i)
#define OffscreenDialogSetAbandon(d,i) vdialogSetAbandon(d,i)
#define OffscreenDialogSetDefFocus(d,i) vdialogSetDefFocus(d,i)
#define OffscreenDialogSetDrag(d,i) vdialogSetDrag(d,i)
#define OffscreenDialogSetSolution(d,s) vdialogSetSolution(d,s)
#define OffscreenDialogGetObject(d)  vdialogGetObject(d)
#define OffscreenDialogGetWindow(d)  vdialogGetWindow(d)
#define OffscreenDialogGetClass(d)  vdialogGetClass(d)
#define OffscreenDialogGetData(d)  vdialogGetData(d)
#define OffscreenDialogGetTitle(d)  vdialogGetTitle(d)
#define OffscreenDialogGetIcon(d)  vdialogGetIcon(d)
#define OffscreenDialogIsOpen(d)  vdialogIsOpen(d)
#define OffscreenDialogGetMaxW(d)  vdialogGetMaxW(d)
#define OffscreenDialogGetMaxH(d)  vdialogGetMaxH(d)
#define OffscreenDialogGetMenu(d)  vdialogGetMenu(d)
#define OffscreenDialogGetCloseHook(d)  vdialogGetCloseHook(d)
#define OffscreenDialogGetItemList(d)  vdialogGetItemList(d)
#define OffscreenDialogGetFocus(d)  vdialogGetFocus(d)
#define OffscreenDialogGetConfirm(d)  vdialogGetConfirm(d)
#define OffscreenDialogGetAbandon(d)  vdialogGetAbandon(d)
#define OffscreenDialogGetDefFocus(d)  vdialogGetDefFocus(d)
#define OffscreenDialogGetDrag(d)  vdialogGetDrag(d)
#define OffscreenDialogGetSolution(d)  vdialogGetSolution(d)
#define OffscreenDialogGetItemCount(d)  vdialogGetItemCount(d)
#define OffscreenDialogGetItemAt(d,i)  vdialogGetItemAt(d,i)
#define OffscreenDialogGetItemIndex(d,i) vdialogGetItemIndex(d,i)
#define OffscreenDialogFindItem(d, t) vdialogFindItem(d, t)

#endif /* OffscreenDialogUSE_OFFSCREEN */

#define OffscreenDialogLock() vmutexLock(&_offscreenDialogMutex)
#define OffscreenDialogUnlock() vmutexUnlock(&_offscreenDialogMutex)
#define OffscreenDialogLockWithHandling() \
   vmutexLockWithHandling(&_offscreenDialogMutex)
#define OffscreenDialogUnlockWithHandling() \
   vmutexUnlockWithHandling(&_offscreenDialogMutex)

/*
 * * * * * * * * * * PRIVATE FUNCTION MESSAGE DEFINITIONS * * * * * * * * * *
 */


#endif /* #ifndef vdialogINCLUDED */



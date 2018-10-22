/* $Id: vmenubar.h,v 1.54 1997/07/09 22:18:28 alex Exp $ */

/************************************************************

    vmenubar.h

    C Interface file for Menu Bar items

    (c) Copyright Visix Software Inc.
    All rights reserved

************************************************************/

#ifndef vmenubarINCLUDED
#define vmenubarINCLUDED

#ifndef  vportINCLUDED
#include <vport.h>
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

vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * * * * * * * * * * PUBLIC CONSTANT DEFINITIONS * * * * * * * * * *
 */

enum {
    vmenubarNEXT_ID_ATTRIBUTE       = vdialogITEM_NEXT_ID_ATTRIBUTE
};

enum {
    vmenubarNEXT_SELECT             = vdialogITEM_NEXT_SELECT
};

/*
 * * * * * * * * * * PUBLIC TYPE DEFINITIONS * * * * * * * * * *
 */

typedef struct vmenubar             vmenubar;
typedef struct vmenubarClass        vmenubarClass;
 
typedef void (*vmenubarNoteProc)(
    vmenubar                       *menubar,
    vevent                         *event
    );

/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */

void vmenubarStartup(void);


vmenubarClass *vmenubarGetDefaultClass(
    void
    );

vmenubar *vmenubarCreateOfClass(
    vmenubarClass                  *clas
    );

vmenubar *vmenubarCreate(
    void
    );

vmenubar *vmenubarClone(
    vmenubar                       *menubar
    );

void vmenubarInitOfClass(
    vmenubar                       *menubar,
    vmenubarClass                  *clas
    );

void vmenubarInit(
    vmenubar                       *menubar
    );

void vmenubarDestroy(
    vmenubar                       *menubar
    );

void vmenubarCopy(
    vmenubar                       *menubar,
    vmenubar                       *target
    );

void vmenubarCopyInit(
    vmenubar                       *menubar,
    vmenubar                       *target
    );

vmenubar *vmenubarLoad(
    vresource                       resource
    );

void vmenubarLoadInit(
    vmenubar                       *menubar,
    vresource                       resource
    );

void vmenubarStore(
    vmenubar                       *menubar,
    vresource                       resource
    );

void vmenubarChangedMenu(
    vmenubar                       *menubar
    );

void vmenubarAppendMenu(
    vmenubar                       *menubar,
    vmenu                          *menu
    );

vmenu *vmenubarRemoveMenu(
    vmenubar                       *menubar,
    vmenu                          *menu
    );

void vmenubarSetMenuIndex(
    vmenubar                       *menubar,
    vmenu                          *menu,
    int                             index
    );

void vmenubarRecalc(
    vmenubar                       *menubar
    );

void vmenubarHilite(
    vmenubar                       *menubar
    );

void vmenubarUnhilite(
    vmenubar                       *menubar
    );

void vmenubarSetNotify(
    vmenubar                       *menubar,
    vmenubarNoteProc	            noteProc
    );

void vmenubarSetData(
    vmenubar                       *menubar,
    const void                     *data
    );

void vmenubarSetHelp(
    vmenubar                       *menubar,
    int                             flag
    );

void vmenubarSetLocal(
    vmenubar                       *menubar,
    int                             flag
    );

vobjectAttributed *vmenubarGetObject(
    vmenubar                       *menubar
    );

vdialogItem *vmenubarGetItem(
    vmenubar                       *menubar
    );

vmenubarClass *vmenubarGetClass(
    vmenubar                       *menubar
    );

vmenubarNoteProc vmenubarGetNotify(
    vmenubar                       *menubar
    );

const void *vmenubarGetData(
    vmenubar                       *menubar
    );

int vmenubarMenuHasHelp(
    vmenubar                       *menubar
    );

int vmenubarIsLocal(
    vmenubar                       *menubar
    );

int vmenubarMenuHasChanged(
    vmenubar                       *menubar
    );

int vmenubarGetMenuCount(
    vmenubar                       *menubar
    );

vmenu *vmenubarGetMenuAt(
    vmenubar                       *menubar,
    int                             index
    );

int vmenubarGetMenuIndex(
    vmenubar                       *menubar,
    vmenu                          *menu
    );

vmenu *vmenubarFindMenu(
    vmenubar                       *menubar,
    const vname                    *tag
    );

void vmenubarSetPreferNative(
    vmenubar                       *menubar,
    int                             flag
    );

int vmenubarPrefersNative(
    vmenubar                       *menubar
    );

int vmenubarNeedNativeDraw(
    vmenubar                       *menubar
    );

int vmenubarIsNativeDraw(
    vmenubar                       *menubar
    );

int vmenubarIsOpenNative(
    vmenubar                       *menubar
    );

/*
 * deprecated menubars
 */

void vmenubarDeleteMenu(
    vmenubar                       *menubar,
    vmenu                          *menu
    );

/*
 * * * * * * * * * * PRIVATE CONSTANT DEFINITIONS * * * * * * * * * *
 */

enum {
    _vmenubarHELP                   = 0x0001,
    _vmenubarLOCAL                  = 0x0002,
    _vmenubarCHANGED_MENU           = 0x0004,
    _vmenubarHILITED                = 0x0008,
    _vmenubarSELECTED               = 0x0010,
    _vmenubarCLOSED                 = 0x0020,
    _vmenubarNATIVE		    = 0x0040,
    _vmenubarFORCED_LOCAL	    = 0x0080,
    _vmenubarGHOST	    	    = 0x0100,
    _vmenubarGHOST_DISABLE	    = 0x0200,
    _vmenubarICONIFIED              = 0x0400,
    _vmenubarICONIFIED_DISABLE	    = 0x0800,
    _vmenubarOPEN_NATIVE            = 0x1000,
    _vmenubarNATIVE_DRAW            = 0x2000,
    _vmenubarHANDLE_MOTION          = 0x4000
}; 


/*
 * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * *
 */

#if (vportWIN_MS_WINDOWS)
typedef struct _vmenubarInfo  _vmenubarInfo;
#endif

struct vmenubar {
    vdialogItem                     item;
    vobjectList                    *list;
    short                          *edges;
    short                          *stop;
    unsigned short                  flags;
    short                           left, right, below, above, height;
    short                           hilite;
    short			    barLeft, barRight;
    vrect                           hiliteRect;

#if (vportWIN_MAC)
    const void			   *sysData;
#endif
#if (vportWIN_MS_WINDOWS)
    _vmenubarInfo                  *info;
#endif
};

#define vmenubarCLASS(SUPER, MENUBAR, NOTIFY)                                 \
    vdialogITEM_CLASS(SUPER, MENUBAR, NOTIFY);                                \
    vclassMETHOD(vmenubarCHANGED_MENU, (MENUBAR *menubar));                   \
    vclassMETHOD(vmenubarAPPEND_MENU, (MENUBAR *menubar, vmenu *menu));       \
    vclassMETHOD_RET(vmenubarREMOVE_MENU, vmenu *,			      \
		     (MENUBAR *menubar, vmenu *menu));                        \
    vclassMETHOD(vmenubarDELETE_MENU, (MENUBAR *menubar, vmenu *menu));       \
    vclassMETHOD(vmenubarSET_MENU_INDEX,                                      \
		 (MENUBAR *menubar, vmenu *menu, int index));                 \
    vclassMETHOD(vmenubarRECALC, (MENUBAR *menubar));                         \
    vclassMETHOD(vmenubarHILITE, (MENUBAR *menubar));                         \
    vclassMETHOD(vmenubarUNHILITE, (MENUBAR *menubar));                       \
    vclassMETHOD(vmenubarSET_HELP, (MENUBAR *menubar, int flag));             \
    vclassMETHOD(vmenubarSET_LOCAL, (MENUBAR *menubar, int flag));            \
    vclassMETHOD_RET(vmenubarNEED_NATIVE_DRAW, int, (MENUBAR *menubar))  

struct vmenubarClass {
    vmenubarCLASS(vmenubarClass, vmenubar, vmenubarNoteProc);
};

/*
 * * * * * * * * * * PRIVATE FUNCTION PROTOTYPES * * * * * * * * * *
 */

vobjectPartialChildIteratorClass *_vmenubarGetPartialChildIteratorClass(void);
void _vmenubarSetNativeDraw(vmenubar *menubar, int flag);

/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * *
 */

#define vmenubarGetItem(m)          vportBASE_OBJECT(m, item)
#define vmenubarGetObject(m)        vdialogGetItemObject(vmenubarGetItem(m))

#define vmenubarCreateOfClass(c) \
    ((vmenubar*)vdialogCreateItemOfClass((vdialogItemClass*)(c)))
#define vmenubarCreate() \
    vmenubarCreateOfClass(vmenubarGetDefaultClass())
#define vmenubarClone(m) \
    ((vmenubar*)vdialogCloneItem(vmenubarGetItem(m)))
#define vmenubarInitOfClass(m, c) \
    vdialogInitItemOfClass(vmenubarGetItem(m), (vdialogItemClass*)(c))
#define vmenubarInit(m) \
    vmenubarInitOfClass(m, vmenubarGetDefaultClass())
#define vmenubarCopyInit(m, t) \
    vdialogCopyInitItem(vmenubarGetItem(m), vmenubarGetItem(t))
#define vmenubarLoad(r)           ((vmenubar*)vdialogLoadItem(r))
#define vmenubarLoadInit(m, r)      vdialogLoadInitItem(vmenubarGetItem(m), r)
#define vmenubarDestroy(m) \
    vdialogDestroyItem(vmenubarGetItem(m))

#define vmenubarGetClass(m) \
    ((vmenubarClass*)vdialogGetItemClass(vmenubarGetItem(m)))

#define vmenubarGetNotify(m) \
    ((vmenubarNoteProc)vdialogGetItemNotify(vmenubarGetItem(m)))
#define vmenubarSetNotify(m, n) \
    vdialogSetItemNotify((vdialogItem *)(m), (vdialogItemNoteProc)(n))

#define vmenubarGetData(m)          vdialogGetItemData(vmenubarGetItem(m))
#define vmenubarMenuHasHelp(m)   (((m)->flags&_vmenubarHELP)!=0)

#if (vportWIN_MAC)
#define vmenubarIsLocal(m) /* asymmetric !!! */ \
    (((m)->flags&(_vmenubarLOCAL|_vmenubarFORCED_LOCAL))!=0)
#else
#define vmenubarIsLocal(m)       (((m)->flags&_vmenubarLOCAL)!=0)
#endif

#define vmenubarMenuHasChanged(m) (((m)->flags&_vmenubarCHANGED_MENU)!=0)
#define vmenubarGetMenuCount(m)     vobjectGetListCount((m)->list)
#define vmenubarGetMenuAt(m, n)   ((vmenu*)vobjectGetListAt((m)->list, n))
#define vmenubarGetMenuIndex(m, i) \
    vobjectGetListIndex((m)->list, vwindowGetObject(vmenuGetWindow(i)))
#define vmenubarFindMenu(m, t)    ((vmenu*)vobjectFindList((m)->list, t))

#define vmenubarIsNativeDraw(m)  (((m)->flags & _vmenubarNATIVE_DRAW) != 0)
#define vmenubarIsOpenNative(m)    (((m)->flags & _vmenubarOPEN_NATIVE) != 0)
#define vmenubarPrefersNative(m)   (((m)->flags & _vmenubarNATIVE) != 0)

/*
 * * * * * * * * * * PRIVATE FUNCTION MESSAGE DEFINITIONS * * * * * * * * * *
 */

#define vmenubarCopy(m, t) \
    vclassSend(vmenubarGetClass(m), vobjectCOPY, (m, t))
#define vmenubarStore(m, r) \
    vclassSend(vmenubarGetClass(m), vobjectSTORE, (m, r))
#define vmenubarChangedMenu(m) \
    vclassSend(vmenubarGetClass(m), vmenubarCHANGED_MENU, (m))
#define vmenubarAppendMenu(m, i) \
    vclassSend(vmenubarGetClass(m), vmenubarAPPEND_MENU, (m, i))
#define vmenubarRemoveMenu(m, i) \
    vclassSend(vmenubarGetClass(m), vmenubarREMOVE_MENU, (m, i))
#define vmenubarDeleteMenu(m, i) \
    ((void) vmenubarRemoveMenu(m, i))
#define vmenubarSetMenuIndex(m, i, n) \
    vclassSend(vmenubarGetClass(m), vmenubarSET_MENU_INDEX, (m, i, n))
#define vmenubarRecalc(m) \
    vclassSend(vmenubarGetClass(m), vmenubarRECALC, (m))
#define vmenubarHilite(m) \
    vclassSend(vmenubarGetClass(m), vmenubarHILITE, (m))
#define vmenubarUnhilite(m) \
    vclassSend(vmenubarGetClass(m), vmenubarUNHILITE, (m))
#define vmenubarSetData(m, p) \
    vclassSend(vmenubarGetClass(m), vdialogSET_ITEM_DATA, (m, p))
#define vmenubarSetHelp(m, f) \
    vclassSend(vmenubarGetClass(m), vmenubarSET_HELP, (m, f))
#define vmenubarSetLocal(m, f) \
    vclassSend(vmenubarGetClass(m), vmenubarSET_LOCAL, (m, f))
#define vmenubarNeedNativeDraw(m) \
    vclassSend(vmenubarGetClass(m), vmenubarNEED_NATIVE_DRAW, (m))

vportEND_CPLUSPLUS_EXTERN_C

#endif /* #ifndef vmenubarINCLUDED */


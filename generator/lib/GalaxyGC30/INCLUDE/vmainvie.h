/* $Id: vmainvie.h,v 1.21 1995/06/07 18:47:40 robert Exp $ */

/************************************************************

    vmainview.h
    C Interface to main view items

    Copyright Visix Software  1991
    All rights reserved

************************************************************/

#ifndef vmainviewINCLUDED
#define vmainviewINCLUDED 1

#ifndef  vportINCLUDED
#include <vport.h>
#endif

#ifndef  vfsINCLUDED
#include vfsHEADER
#endif

#ifndef  vresourceINCLUDED
#include vresourceHEADER
#endif

#ifndef  vwindowINCLUDED
#include vwindowHEADER
#endif

#ifndef  viconviewINCLUDED
#include viconviewHEADER
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C
  
/*
 * * * * * * * * * * PUBLIC CONSTANT DEFINITIONS * * * * * * * * * *
 */
  
/* Values for the domain object type, for an icon's objects */
  
enum {
  vmainviewICON_VIEW,
  vmainviewNAME_VIEW,
  vmainviewNEXT_VIEW
};

/*
 * * * * * * * * * * PUBLIC TYPE DEFINITIONS * * * * * * * * * *
 */

typedef struct vmainview                vmainview;
typedef struct vmainviewClass           vmainviewClass;
typedef struct vmainviewIterator        vmainviewIterator;

/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */

void vmainviewStartup(void);


/* Main View Class Functions */

vmainviewClass *vmainviewGetDefaultClass(void);

/* Initialization and allocation */

vmainview *vmainviewCreate(void);

vmainview *vmainviewCreateOfClass(
    vmainviewClass	*clas
    );
    
vmainview *vmainviewClone(
    vmainview	    	*mainview
    );

void vmainviewCopy(
    vmainview    	*mainview,
    vmainview	    	*targetItem
    );

void vmainviewCopyInit(
    vmainview    	*mainview,
    vmainview	    	*targetItem
    );

void vmainviewInit(
    vmainview	    	*mainview
    );

void vmainviewInitOfClass(
    vmainview		*mainview,
    vmainviewClass	*clas
    );

void vmainviewDestroy(
    vmainview	    	*mainview
    );

void vmainviewDestroyLater(
    vmainview	    	*mainview
    );

vmainview *vmainviewLoad(
    vresource		resource
    );

void vmainviewLoadInit(
    vmainview		*mainview,
    vresource		resource
    );

void vmainviewStore(
    vmainview		*mainview,
    vresource		resource
    );

/* Main view operations */	

void vmainviewCleanup(
    vmainview		*mainview
    );

void vmainviewTile(
    vmainview		*mainview
    );

void vmainviewCascade(
    vmainview		*mainview
    );

vwindow *vmainviewGetActiveWindow(
    vmainview *mainview
    );

void vmainviewSetActiveWindow(
     vmainview		*mainview,
     vwindow		*window
    );

int
vmainviewHasWindow(
     vmainview		*mainview,
     vwindow		*window
    );

void vmainviewInitIterator(
    vmainviewIterator   *iterator,
    vmainview           *mainview
    );

int vmainviewNextIterator(
    vmainviewIterator   *iterator
    );

void vmainviewDestroyIterator(
    vmainviewIterator   *iterator
    );

vwindow *vmainviewGetIteratorWindow(
    vmainviewIterator   *iterator
    );


void vmainviewSetNameView(
    vmainview           *mainview
    );

void vmainviewSetIconView(
    vmainview           *mainview
    );

void *vmainviewGetData(
    vmainview           *mainview
    );

void vmainviewSetData(
    vmainview           *mainview,
    void                *data
    );

void vmainviewOpen(
    vmainview           *mainview
    );

void vmainviewClose(
    vmainview           *mainview
    );


/* Main View attribute access */

vmainviewClass *vmainviewGetClass(
    vmainview		*mainview
    );

void vmainviewAddWindow(
    vmainview		*mainview,
    vwindow     	*window
    );

void vmainviewRemoveWindow(
     vmainview		*mainview,
     vwindow            *window
    );

void vmainviewSetWindowTitle(
    vmainview		*mainview,
    vwindow     	*window,
    vchar               *title
    );

void vmainviewSetWindowTitleScribed(
    vmainview		*mainview,
    vwindow     	*window,
    vscribe             *title
    );

vdialogItem *vmainviewGetItem(
    vmainview           *mainview
    );

int vmainviewGetView(
    vmainview           *mainview
    );

void vmainviewSetView(
    vmainview           *mainview,
    int                  view
    );

void vmainviewSetWindowNameViewImage(
    vmainview           *mainview,
    vwindow             *window,
    vimage              *image
    );

void vmainviewSetWindowIconViewImage(
    vmainview           *mainview,
    vwindow             *window,
    vimage              *image
    );

void _vmainviewSetWindowViewImage(
    vmainview           *mainview,
    vwindow             *window,
    viconviewView       *view,
    vimage              *image
    );

/*
 * * * * * * * * * * PRIVATE CONSTANT DEFINITIONS * * * * * * * * * *
 */

enum {
  _vmainviewNATIVE                = 0x01
};

/*
 * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * *
 */

typedef struct _vmainviewIconInfo     _vmainviewIconInfo;
typedef struct _vmainviewInfo         _vmainviewInfo;

typedef struct _vmainviewIconData {
  vwindow                       *window;
  vchar                         *title;
  _vmainviewIconInfo            *info;
  unsigned short                 flags;
} _vmainviewIconData;

struct vmainview {
  viconview                     iconview;
  int                           viewType;
  _vmainviewInfo               *info;
  unsigned short                flags;
};

/* vmainviewIterator */

struct vmainviewIterator {
    viconviewIterator		iviterator;
    vwindow			*window;
};


/*
 * Main View Class Definition
 */

#define vmainviewCLASS(SUPER, ITEM, NOTIFY, DOMAIN, ICON, WINDOW)            \
  viconviewCLASS(SUPER, ITEM, NOTIFY, DOMAIN, ICON);                         \
  vclassMETHOD(vmainviewADD_WINDOW,        (ITEM *, WINDOW *));              \
  vclassMETHOD(vmainviewREMOVE_WINDOW,     (ITEM *, WINDOW *));              \
  vclassMETHOD(vmainviewSET_WINDOW_TITLE_SCRIBED,  (ITEM *, WINDOW *,        \
                                                    vscribe *));             \
  vclassMETHOD(vmainviewSET_WINDOW_TITLE,          (ITEM *, WINDOW *,        \
                                                    vchar *));               \
  vclassMETHOD(vmainviewSET_VIEW,          (ITEM *, int));                   \
  vclassMETHOD(vmainviewTILE,              (ITEM *));                        \
  vclassMETHOD(vmainviewCASCADE,           (ITEM *));                        \
  vclassMETHOD_RET(vmainviewGET_ACTIVE_WINDOW, vwindow *, (ITEM *));         \
  vclassMETHOD(vmainviewSET_ACTIVE_WINDOW, (ITEM *, WINDOW *))

struct vmainviewClass {
  vmainviewCLASS(vmainviewClass, 
		 vmainview, 
		 vdialogItemNoteProc,
		 vdomain, 
		 viconviewIcon,
		 vwindow);
};

/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * *
 */

#define vmainviewGetBase(c)	vportBASE_OBJECT(c, iconview)

#define vmainviewCreateOfClass(c) \
  ((vmainview *) vdomainviewCreateOfClass((vdomainviewClass *)(c)))
#define vmainviewCreate() \
    vmainviewCreateOfClass(vmainviewGetDefaultClass())
#define vmainviewClone(m) \
  ((vmainview *) vdialogCloneItem(viconviewGetItem(vmainviewGetBase(m))))
#define vmainviewInitOfClass(m, c) \
  vdialogInitItemOfClass((vdialogItem *)(m), (vdialogItemClass *)(c))
	
#define vmainviewInit(m) \
  vmainviewInitOfClass((m), vmainviewGetDefaultClass())
#define vmainviewDestroy(m) \
  vobjectDestroy(vdialogGetItemObject(viconviewGetItem(vmainviewGetBase(m))))
#define vmainviewDestroyLater(m) \
  vobjectDestroyLater(vdialogGetItemObject(viconviewGetItem(vmainviewGetBase(m))))
#define vmainviewCopyInit(c,t) \
  vdialogCopyInitItem(viconviewGetItem(vmainviewGetBase(c)), \
		      viconviewGetItem(vmainviewGetBase(t)))
#define vmainviewLoad(r) \
  ((vmainview*)vdialogLoadItem(r))
#define vmainviewLoadInit(c, r) \
  vdialogLoadInitItem(viconviewGetItem(vmainviewGetBase(c)), r)

#define vmainviewGetData(m) \
  vdialogGetItemData(viconviewGetItem(vmainviewGetBase(m)))

#define vmainviewSetWindowNameViewImage(m, d, i) \
  _vmainviewSetWindowViewImage(m, d, viconviewGetNameView(), i)
#define vmainviewSetWindowIconViewImage(m, d, i) \
  _vmainviewSetWindowViewImage(m, d, viconviewGetIconView(), i)

#define vmainviewGetView(m)    ((m)->viewType)

/* 
 * deprecated 
 */
#define vmainviewSetNameView(m) \
  vmainviewSetView(m, vmainviewNAME_VIEW)
#define vmainviewSetIconView(m) \
  vmainviewSetView(m, vmainviewICON_VIEW)

#if 0
#define vmainviewSetWindowTitle(m, d, c) \
  vmainviewSetWindowTitleScribed(m, d, vcharScribe(c))
#endif

#define vmainviewGetItem(m) viconviewGetItem(vmainviewGetBase(m))
#define vmainviewGetClass(m) \
  ((vmainviewClass *) vobjectGetClass((vobject *)(m)))

#define vmainviewDestroyIterator(i) \
  viconviewDestroyIterator(&((i)->iviterator))
#define vmainviewGetIteratorWindow(i)	((i)->window)


/*
 * * * * * * * * * * PRIVATE FUNCTION MESSAGE DEFINITIONS * * * * * * * * * *
 */

#define vmainviewStore(m, t) \
  vclassSend(vmainviewGetClass(m), vobjectSTORE, (m, t))
#define vmainviewCopy(m, t) \
  vclassSend(vmainviewGetClass(m), vobjectCOPY, (m, t))

#define vmainviewOpen(m) \
  vclassSend(vmainviewGetClass(m), vdialogOPEN_ITEM, (m))
#define vmainviewClose(m) \
  vclassSend(vmainviewGetClass(m), vdialogCLOSE_ITEM, (m))
#define vmainviewSetData(m, x) \
  vclassSend(vmainviewGetClass(m), vdialogSET_ITEM_DATA, (m, x))

#define vmainviewSetView(m, v) \
  vclassSend(vmainviewGetClass(m), vmainviewSET_VIEW, (m, v))

#define vmainviewGetActiveWindow(m) \
  vclassSend(vmainviewGetClass(m), vmainviewGET_ACTIVE_WINDOW, (m))

#define vmainviewSetActiveWindow(m, d) \
  vclassSend(vmainviewGetClass(m), vmainviewSET_ACTIVE_WINDOW, (m, d))

#define vmainviewCleanup(m) \
  vclassSend(vmainviewGetClass(m), viconviewCLEANUP, (m))

#define vmainviewTile(m) \
  vclassSend(vmainviewGetClass(m), vmainviewTILE, (m))
#define vmainviewCascade(m) \
  vclassSend(vmainviewGetClass(m), vmainviewCASCADE, (m))

#define vmainviewAddWindow(m, d) \
  vclassSend(vmainviewGetClass(m), vmainviewADD_WINDOW, (m, d))
#define vmainviewRemoveWindow(m, d) \
  vclassSend(vmainviewGetClass(m), vmainviewREMOVE_WINDOW, (m, d))
#define vmainviewSetWindowTitleScribed(m, d, sc) \
  vclassSend(vmainviewGetClass(m), vmainviewSET_WINDOW_TITLE_SCRIBED, \
	     (m, d, sc))

/*
 * deprecated
 */

#define vmainviewSetWindowTitle(m, d, t) \
  vclassSend(vmainviewGetClass(m), vmainviewSET_WINDOW_TITLE, \
	     (m, d, t))

/*
 * * * * * * * * * MAIN VIEW GLOBAL VARIABLES * * * * * * * * * *
 */

vportEND_CPLUSPLUS_EXTERN_C

#endif /* vmainviewINCLUDED */





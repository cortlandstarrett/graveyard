/* $Id: vstatusbar.h,v 1.18 1997/10/21 23:53:09 paulm Exp $ */

/************************************************************

    vstatusbar.h

    C Interface file for the Statusbar Manager

    (c) Copyright Visix Software Inc.
    All rights reserved

************************************************************/

#ifndef vstatusbarINCLUDED
#define vstatusbarINCLUDED 1

#ifndef  vportINCLUDED
#include <vport.h>
#endif

#ifndef  vcontainerINCLUDED
#include vcontainerHEADER
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * * * * * * * * * * PUBLIC CONSTANT DEFINITIONS * * * * * * * * * *
 */

/*
 *  Item Addition Policy Per Add
 */

typedef enum vstatusbarAdderType{
  vstatusbarFIXED_LEFT,
  vstatusbarNATURAL_LEFT,
  vstatusbarFIXED_RIGHT,
  vstatusbarNATURAL_RIGHT,
  vstatusbarVARIABLE
} vstatusbarAdderType;


/*
 * * * * * * * * * * PUBLIC TYPE DEFINITIONS * * * * * * * * * *
 */

typedef struct vstatusbar           vstatusbar;
typedef struct vstatusbarClass      vstatusbarClass;

typedef struct vstatusbarItem       vstatusbarItem;
typedef struct vstatusbarItemClass  vstatusbarItemClass;

typedef void (*vstatusbarNoteProc)(
    vstatusbar                     *statusbar,
    vevent                          *event
    );

typedef void (*vstatusbarItemNoteProc)(
    vstatusbarItem                  *statusbarItem,
    vevent                          *event
    );


/*
 * * * * * * * * * * PUBLIC MACRO DEFINITIONS * * * * * * * * * *
 */
#define	vstatusbar_vstatusbarDefaultItem _vstatusbar_vstatusbarDefaultItemTag


/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */

void vstatusbarStartup(void);


vstatusbarClass *vstatusbarGetDefaultClass(
    void
    );

vstatusbar *vstatusbarCreateOfClass(
    vstatusbarClass                *clas
    );

vstatusbar *vstatusbarCreate(
    void
    );

vstatusbar *vstatusbarClone(
    vstatusbar                     *statusbar
    );

void vstatusbarInitOfClass(
    vstatusbar                     *statusbar,
    vstatusbarClass                *clas
    );

void vstatusbarInit(
    vstatusbar                     *statusbar
    );

void vstatusbarDestroy(
    vstatusbar                     *statusbar
    );

void vstatusbarCopy(
    vstatusbar                     *statusbar,
    vstatusbar                     *target
    );

void vstatusbarCopyInit(
    vstatusbar                     *statusbar,
    vstatusbar                     *target
    );

vstatusbar *vstatusbarLoad(
    vresource                       resource
    );

void vstatusbarLoadInit(
    vstatusbar                     *statusbar,
    vresource                       resource
    );

void vstatusbarStore(
    vstatusbar                     *statusbar,
    vresource                       resource
    );

vcontainer *vstatusbarGetContainer(
    vstatusbar                     *statusbar
    );

vdialogItem *vstatusbarGetItem(
    vstatusbar                     *statusbar
    );

void vstatusbarAddItem(
    vstatusbar                     *statusbar,
    vdialogItem                     *item,
    vstatusbarAdderType             adder
    );

void vstatusbarDeleteItem(
    vstatusbar                     *statusbar,
    vdialogItem                     *item
    );

void vstatusbarSetFullBorders(
    vstatusbar                     *statusbar,
    vbool			    onOff
    );

vbool vstatusbarHasFullBorders(
    vstatusbar                     *statusbar
    );

void vstatusbarSetNotify(
    vstatusbar                     *statusbar,
    vstatusbarNoteProc              noteProc
    );

void vstatusbarSetData(
    vstatusbar                     *statusbar,
    const void                      *data
    );

vobjectAttributed *vstatusbarGetObject(
    vstatusbar                     *statusbar
    );

vstatusbarClass *vstatusbarGetClass(
    vstatusbar                     *statusbar
    );

vstatusbarNoteProc vstatusbarGetNotify(
    vstatusbar                     *statusbar
    );

const void *vstatusbarGetData(
    vstatusbar                     *statusbar
    );

void vstatusbarDrawBorder(
    vstatusbar                     *statusbar
    );

void vstatusbarSetDefaultItemText(
    vstatusbar                     *statusbar,
    const vchar                    *string    
    );

void vstatusbarSetDefaultItemTextScribed(
    vstatusbar                     *statusbar,
    vscribe			   *scribe
    );

const vchar *vstatusbarGetDefaultItemText(
    vstatusbar                     *statusbar
    );

void vstatusbarSetStatusbarText(
    vdialogItem                    *item,
    const vchar                    *string
    );

void vstatusbarSetStatusbarTextScribed(
    vdialogItem                    *item,
    vscribe                        *scribe
    );

void vstatusbarSetObserveStatusHelp(
    vstatusbar                     *statusbar,
    vbool                           onOff
    );

vbool vstatusbarIsObservingStatusHelp(
    vstatusbar                     *statusbar
    );
/* 
---------------------------------------------------------
        For statusbarItems
---------------------------------------------------------
*/

vstatusbarItemClass *vstatusbarGetDefaultItemClass(
    void
    );

vstatusbarItemClass *vstatusbarGetItemClass(
    vstatusbarItem                  *statusbarItem
    );

vstatusbarItem *vstatusbarCreateItem(
    void
    );

vstatusbarItem *vstatusbarCreateItemOfClass(
    vstatusbarItemClass                *clas
    );

vstatusbarItem *vstatusbarCloneItem(
    vstatusbarItem               *statusbarItem
    );

void vstatusbarCopyItem(
    vstatusbarItem                     *statusbarItem,
    vstatusbarItem                     *target
    );

void vstatusbarCopyInitItem(
    vstatusbarItem                     *statusbarItem,
    vstatusbarItem                     *target
    );

vstatusbarItem *vstatusbarLoadItem(
    vresource                       resource
    );

void vstatusbarLoadInitItem(
    vstatusbarItem                     *statusbarItem,
    vresource                           resource
    );

void vstatusbarStoreItem(
    vstatusbarItem                     *statusbarItem,
    vresource                           resource
    );
    

void vstatusbarDestroyItem(
    vstatusbarItem               *statusbarItem
    );

void vstatusbarInitItem(
    vstatusbarItem               *statusbarItem
    );

void vstatusbarInitItemOfClass(
    vstatusbarItem                     *statusbarItem,
    vstatusbarItemClass                *clas
    );

vdialogLabelItem *vstatusbarGetItemLabelItem(
    vstatusbarItem               *statusbarItem
    );

vdialogItem *vstatusbarGetItemItem(
    vstatusbarItem               *statusbarItem
    );

const vchar *vstatusbarGetItemText(
    vstatusbarItem               *statusbarItem
    );

int vstatusbarGetItemTextWidth(
    vstatusbarItem               *statusbarItem
    );

vstatusbarItemNoteProc vstatusbarGetItemNotify(
    vstatusbarItem                     *statusbarItem
    );

void vstatusbarSetItemNotify(
    vstatusbarItem                     *statusbarItem,
    vstatusbarItemNoteProc              noteProc
    );

void vstatusbarSetItemText(
    vstatusbarItem               *statusbarItem,
    const vchar                  *text
    );

void vstatusbarSetItemTextScribed(
    vstatusbarItem               *statusbarItem,
    vscribe                      *scribe
    );

void vstatusbarSetItemTextWidth(
    vstatusbarItem               *statusbarItem,
    int                          numberofchars
    );



/*
 * * * * * * * * * * PRIVATE CONSTANT DEFINITIONS * * * * * * * * * *
 */


enum {
    _vstatusbarFULL_BORDERS                = 0x0001,
    _vstatusbarOBSERVE_STATUS_HELP         = 0x0002
};


/*
 * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * *
 */

struct vstatusbar {
  vcontainer                        container;
  unsigned short                    flags;
  vdialogItem	                   *default_item;

};

struct vstatusbarItem {
  vdialogLabelItem                  label;
  int                               maxchars;

};

#define vstatusbarCLASS(SUPER, STATUSBAR, NOTIFY) \
     vcontainerCLASS(SUPER, STATUSBAR, NOTIFY); \
     vclassVARIABLE(vstatusbarDEFAULT_ITEM_CLASS, vstatusbarItemClass *); \
     vclassMETHOD(vstatusbarADD_ITEM,\
       (STATUSBAR *statusbar, vdialogItem *item, vstatusbarAdderType adder));\
     vclassMETHOD(vstatusbarSET_FULL_BORDERS, \
		  (STATUSBAR *statusbar, vbool onOff));\
     vclassMETHOD(vstatusbarSET_OBSERVE_STATUS_HELP, \
		  (STATUSBAR *statusbar, vbool onOff));\
     vclassMETHOD(vstatusbarSET_DEFAULT_ITEM_TEXT_SCRIBED, \
		  (STATUSBAR *statusbar, vscribe *scribe))



struct vstatusbarClass {
  vstatusbarCLASS(vstatusbarClass, vstatusbar, vstatusbarNoteProc);
};

#define vstatusbarITEM_CLASS(SUPER, STATUSBARITEM, NOTIFY) \
     vdialogITEM_CLASS(SUPER, STATUSBARITEM, NOTIFY); \
     vclassMETHOD(vstatusbarSET_ITEM_TEXT_WIDTH,\
       (STATUSBARITEM *statusbarItem, int numberofchars))


struct vstatusbarItemClass {
  vstatusbarITEM_CLASS(vstatusbarItemClass, vstatusbarItem, vstatusbarItemNoteProc);
};




/*
 * * * * * * * * * * PRIVATE FUNCTION PROTOTYPES * * * * * * * * * *
 */



/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * *
 */

#define vstatusbarGetContainer(s)   vportBASE_OBJECT((s), container) 

#define vstatusbarGetItem(s) vcontainerGetItem(vstatusbarGetContainer(s))

#define vstatusbarGetObject(s)      vcontainerGetObject(vstatusbarGetContainer(s))

#define vstatusbarCreateOfClass(s) \
    ((vstatusbar*)vcontainerCreateOfClass((vcontainerClass*)(s)))

#define vstatusbarCreate() \
    vstatusbarCreateOfClass(vstatusbarGetDefaultClass())

#define vstatusbarClone(s) \
    ((vstatusbar*)vcontainerClone(vstatusbarGetContainer(s)))

#define vstatusbarInitOfClass(s, cl) \
    vcontainerInitOfClass(vstatusbarGetContainer(s), (vcontainerClass*)(cl))

#define vstatusbarInit(s) \
    vstatusbarInitOfClass(s, vstatusbarGetDefaultClass())

#define vstatusbarCopy(s, t) \
    vcontainerCopy(vstatusbarGetContainer(s), vstatusbarGetContainer(t))

#define vstatusbarCopyInit(s, t) \
    vcontainerCopyInit(vstatusbarGetContainer(s), vstatusbarGetContainer(t))

#define vstatusbarLoad(r)         ((vstatusbar*)vcontainerLoad(r))

#define vstatusbarLoadInit(s, r) \
    vcontainerLoadInit(vstatusbarGetContainer(s), r)

#define vstatusbarStore(s, r) vcontainerStore(vstatusbarGetContainer(s), r)

#define vstatusbarDestroy(s) \
    vcontainerDestroy(vstatusbarGetContainer(s))

#define vstatusbarGetClass(s) \
    ((vstatusbarClass*)vcontainerGetClass(vstatusbarGetContainer(s)))

#define vstatusbarGetNotify(s) \
    ((vstatusbarNoteProc)vcontainerGetNotify(vstatusbarGetContainer(s)))

#define vstatusbarSetNotify(s, n) \
    vcontainerSetNotify((vcontainer *)(s), (vcontainerNoteProc)(n))

#define vstatusbarGetData(s) vcontainerGetData(vstatusbarGetContainer(s))

#define vstatusbarSetData(s, d) vcontainerSetData((vcontainer *)s, d)

#define vstatusbarSetStatusbarText(i, c) \
    vstatusbarSetStatusbarTextScribed (i, vcharScribe(c))

#define vstatusbarHasFullBorders(s) \
    ((vbool)(((s)->flags&_vstatusbarFULL_BORDERS) ? vTRUE : vFALSE))

#define vstatusbarIsObservingStatusHelp(s) \
    ((vbool)(((s)->flags&_vstatusbarOBSERVE_STATUS_HELP) ? vTRUE : vFALSE))
/* 
---------------------------------------------------------
        For statusbarItems
---------------------------------------------------------
*/

#define vstatusbarCreateItemOfClass(si) \
    ((vstatusbarItem*)vdialogCreateItemOfClass((vdialogLabelItemClass*)(si)))

#define vstatusbarCreateItem() \
    vstatusbarCreateItemOfClass(vstatusbarGetDefaultItemClass())

#define vstatusbarCloneItem(si) \
    ((vstatusbarItem*)vdialogItemClone(vstatusbarGetItemItem(si)))

#define vstatusbarInitItemOfClass(si, cl) \
    vdialogInitItemOfClass(vstatusbarGetItemItem(si), (vlabelItemClass*)(cl))

#define vstatusbarInitItem(si) \
    vdialogInitItemOfClass(si, vstatusbarGetDefaultItemClass())

#define vstatusbarCopyItem(si, t) \
    vdialogCopyItem(vstatusbarGetItemItem(si), vstatusbarGetItemItem(t))

#define vstatusbarCopyInitItem(si, t) \
    vdialogCopyInitItem(vstatusbarGetItemItem(si), vstatusbarGetItemItem(t))

#define vstatusbarLoadItem(r)((vstatusbarItem*)vdialogLoadItem(r))

#define vstatusbarLoadInitItem(si, r) \
    vdialogLoadInitItem(vstatusbarGetItemItem(si), r)

#define vstatusbarStoreItem(si, r) \
    vdialogStoreItem(vstatusbarGetItemItem(si), r)

#define vstatusbarDestroyItem(si) \
    vdialogDestroyItem(vstatusbarGetItemItem(si))

#define vstatusbarGetItemLabelItem(si) vportBASE_OBJECT((si), label)

#define vstatusbarGetItemClass(si) \
    ((vstatusbarItemClass *)vdialogGetItemClass(vstatusbarGetItemItem(si)))

#define vstatusbarGetItemNotify(si) \
    ((vdialogItemNoteProc)vdialogGetItemNotify(vstatusbarGetItemItem(si)))

#define vstatusbarSetItemNotify(si, n) \
    vdialogSetItemNotify((vdialogItem *)(si), (vdialogItemNoteProc)(n))

#define vstatusbarGetItemItem(si) vstatusbarGetItemLabelItem(si)

#define vstatusbarGetItemText(si) \
     vdialogGetItemTitle(vstatusbarGetItemItem(si))

#define vstatusbarGetItemTextWidth(si)	(si)->maxchars

#define vstatusbarSetItemTextScribed(si, s) \
    vdialogSetItemTitleScribed(vstatusbarGetItemItem(si), s)

#define vstatusbarSetItemText(si, t) \
     vstatusbarSetItemTextScribed(si, vcharScribe(t))

#define vstatusbarSetDefaultItemText(s, c) \
    vstatusbarSetDefaultItemTextScribed (s, vcharScribe(c))

#define vstatusbarGetDefaultItemText(s) \
    vdialogGetItemTitle((s)->default_item)



/*
 * * * * * * * * * * PRIVATE FUNCTION MESSAGE DEFINITIONS * * * * * * * * * *
 */

#define vstatusbarAddItem(s, t, i) \
    vclassSend(vstatusbarGetClass(s), vstatusbarADD_ITEM, (s, t, i))

#define vstatusbarDeleteItem(s, t) \
    vcontainerDeleteItem(vstatusbarGetContainer(s), t)

#define vstatusbarSetObserveStatusHelp(s, b) \
    vclassSend(vstatusbarGetClass(s), \
	       vstatusbarSET_OBSERVE_STATUS_HELP, (s, b))

#define vstatusbarSetFullBorders(s, b) \
    vclassSend(vstatusbarGetClass(s), vstatusbarSET_FULL_BORDERS, (s, b))

#define vstatusbarSetDefaultItemTextScribed(s, t) \
    vclassSend(vstatusbarGetClass(s), \
	       vstatusbarSET_DEFAULT_ITEM_TEXT_SCRIBED, (s, t))

#define vstatusbarSetItemTextWidth(si, n) \
    vclassSend(vstatusbarGetItemClass(si), vstatusbarSET_ITEM_TEXT_WIDTH, \
	       (si, n))



vportEND_CPLUSPLUS_EXTERN_C


#endif /* #ifndef vstatusbarINCLUDED */


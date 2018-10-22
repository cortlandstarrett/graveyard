/* $Id: vbutton.h,v 1.58 1997/11/14 19:03:50 bill Exp $ */

/************************************************************

    vbutton.h

    C Interface file for the Button Manager

    (c) Copyright Visix Software Inc.
    All rights reserved

************************************************************/

#ifndef vbuttonINCLUDED
#define vbuttonINCLUDED

#ifndef  vportINCLUDED		/* for v*HEADER */
#include <vport.h>
#endif

#ifndef  vexINCLUDED
#include vexHEADER
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

#ifndef  vcontrolINCLUDED
#include vcontrolHEADER
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

/*
 * buttons
 */

enum {
    vbuttonNEXT_ID_ATTRIBUTE        = vcontrolNEXT_ID_ATTRIBUTE
};

enum {
    vbuttonNEXT_SELECT              = vcontrolNEXT_SELECT
};

enum {
    vbuttonOFF		 = 0,
    vbuttonON		 = 1,
    vbuttonINDETERMINATE = -1
};


/*
 * deprecated buttons
 */

#ifdef vlafOPEN_LOOK

enum {
    vbuttonOPEN_LOOK_MENU_FROB	    = vlafOPEN_LOOK_BUTTON_MENU_FROB,
    vbuttonOPEN_LOOK_HILITED	    = vlafOPEN_LOOK_BUTTON_HILITED,
    vbuttonOPEN_LOOK_FILL_2D	    = vlafOPEN_LOOK_BUTTON_FILL_2D,
    vbuttonOPEN_LOOK_ENABLED	    = vlafOPEN_LOOK_BUTTON_ENABLED
};

#endif

/*
 * * * * * * * * * * PUBLIC TYPE DEFINITIONS * * * * * * * * * *
 */

/*
 * buttons
 */

typedef struct vbutton              vbutton;
typedef struct vbuttonClass         vbuttonClass;
 
typedef void (*vbuttonNoteProc)(
    vbutton                        *button,
    vevent                         *event
    );

/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */

void vbuttonStartup(void);


/*
 * buttons
 */

vbuttonClass *vbuttonGetDefaultClass(
    void
    );

vbutton *vbuttonCreateOfClass(
    vbuttonClass                   *clas
    );

vbutton *vbuttonCreate(
    void
    );

vbutton *vbuttonClone(
    vbutton                        *button
    );

void vbuttonInitOfClass(
    vbutton                        *button,
    vbuttonClass                   *clas
    );

void vbuttonInit(
    vbutton                        *button
    );

void vbuttonDestroy(
    vbutton                        *button
    );

void vbuttonCopy(
    vbutton                        *button,
    vbutton                        *target
    );

void vbuttonCopyInit(
    vbutton                        *button,
    vbutton                        *target
    );

vbutton *vbuttonLoad(
    vresource                       resource
    );

void vbuttonLoadInit(
    vbutton                        *button,
    vresource                       resource
    );

void vbuttonStore(
    vbutton                        *button,
    vresource                       resource
    );

void vbuttonShow(
    vbutton                        *button
    );

void vbuttonHide(
    vbutton                        *button
    );

void vbuttonEnable(
    vbutton                        *button
    );

void vbuttonDisable(
    vbutton                        *button
    );

void vbuttonDrawBorderWith(
    vbutton                        *button,
    vdrawcontext                   *context
    );

void vbuttonDrawBackgroundWith(
    vbutton                        *button,
    vdrawcontext                   *context
    );

void vbuttonDrawImageWith(
    vbutton                        *button,
    vdrawcontext                   *context
    );
    
void vbuttonDrawTitleWith(
    vbutton                        *button,
    vdrawcontext                   *context
    );
    
void vbuttonDrawMenuFrobWith(
    vbutton                        *button,
    vdrawcontext                   *context
    );
    
void vbuttonDrawContent(  /* Deprecated. Use DrawContentWith. */
    vbutton                        *button
    );

void vbuttonDrawContentWith(
    vbutton                        *button,
    vdrawcontext                   *context
    );

void vbuttonHilite(
    vbutton                        *button
    );

void vbuttonHiliteWith(
    vbutton                        *button,
    vdrawcontext                   *context
    );

void vbuttonUnhilite(
    vbutton                        *button
    );

void vbuttonUnhiliteWith(
    vbutton                        *button,
    vdrawcontext                   *context
    );

void vbuttonSetNotify(
    vbutton                        *button,
    vbuttonNoteProc                 noteProc
    );

void vbuttonSetData(
    vbutton                        *button,
    const void                     *data
    );

void vbuttonSetTitle(
    vbutton                        *button,
    const vchar                    *title
    );

void vbuttonSetTitleScribed(
    vbutton                        *button,
    vscribe                        *title
    );

void vbuttonSetMenu(
    vbutton                        *button,
    vmenu                          *menu
    );

vobjectAttributed *vbuttonGetObject(
    vbutton                        *button
    );

vdialogItem *vbuttonGetItem(
    vbutton                        *button
    );

vcontrol *vbuttonGetControl(
    vbutton                        *button
    );

vbuttonClass *vbuttonGetClass(
    vbutton                        *button
    );

vbuttonNoteProc vbuttonGetNotify(
    vbutton                        *button
    );

const void *vbuttonGetData(
    vbutton                        *button
    );

const vchar *vbuttonGetTitle(
    vbutton                        *button
    );

vmenu *vbuttonGetMenu(
    vbutton                        *button
    );

int vbuttonIsShown(
    vbutton                        *button
    );

int vbuttonIsEnabled(
    vbutton                        *button
    );

int vbuttonIsHilited(
    vbutton                        *button
    );

void vbuttonBlink(
    vbutton                        *button
    );

int vbuttonIsToggle(
    vbutton                        *button
    );

void vbuttonSetToggle(
    vbutton                        *button,
    int                             isToggle
    );

void vbuttonSetMax(
    vbutton                        *button,
    int                             max
    );

void vbuttonSetMin(
    vbutton                        *button,
    int                             min
    );

void vbuttonSetValue(
    vbutton                        *button,
    int                             value
    );

int vbuttonSetValueValid(
    vbutton                        *button,
    int                             value
    );

int vbuttonGetMax(
    vbutton                        *button
    );

int vbuttonGetMin(
    vbutton                        *button
    );

int vbuttonGetValue(
    vbutton                        *button
    );

void vbuttonSetImageDisabling(
    vbutton                        *button,
    vbool                           onOff
    );

vbool vbuttonHasImageDisabling(
    vbutton                        *button
    );

/*
 * deprecated buttons
 */

#ifdef vlafOPEN_LOOK

void vbuttonDrawOpenLookImage(
    const vrect			   *rect,
    int                             flags,
    vcolor                         *topShadow,
    vcolor                         *botShadow,
    vcolor                         *background,
    vcolor			   *debossColor
    );

#endif

/*
 * * * * * * * * * * PRIVATE CONSTANT DEFINITIONS * * * * * * * * * *
 */

/*
 * buttons
 */

enum {
    _vbuttonSHOWING_DEFAULT         = 0x0002,
    _vbuttonALT_STYLE	            = 0x0004,
    _vbuttonMULTI_LINE		    = 0x0008,
    _vbuttonDRAW_DISABLED_IMAGE	    = 0x0010,
    _vbuttonBUTTON_UP		    = 0x0020
};

/*
 * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * *
 */

/*
 * buttons
 */

struct vbutton {
    vcontrol                        control;
    unsigned short                  flags;

#if (vportWIN_MAC && defined(vlafMAC))
    const void			    *sysData;
    vimage			    *sysGrayed;
#endif

};

#define vbuttonHILITE           vcontrolHILITE
#define vbuttonHILITE_WITH      vcontrolHILITE_WITH
#define vbuttonUNHILITE         vcontrolUNHILITE
#define vbuttonUNHILITE_WITH    vcontrolUNHILITE_WITH

#define vbuttonCLASS(SUPER, BUTTON, NOTIFY)                                   \
    vcontrolCLASS(SUPER, BUTTON, NOTIFY);                                     \
    vclassMETHOD(vbuttonDRAW_MENU_FROB_WITH,                                  \
                 (BUTTON *button, vdrawcontext *context));                    \
    vclassMETHOD(vbuttonDRAW_CONTENT, (BUTTON *button));                      \
    vclassMETHOD(vbuttonDETERMINE_COLOR_SCHEME,                               \
                 (BUTTON *button, vcolorScheme *retScheme))

struct vbuttonClass {
    vbuttonCLASS(vbuttonClass, vbutton, vbuttonNoteProc);
};

/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * *
 */

/*
 * buttons
 */

#define vbuttonGetControl(b)        vportBASE_OBJECT(b, control)
#define vbuttonGetItem(b)           vcontrolGetItem(vbuttonGetControl(b))
#define vbuttonGetObject(b)         vdialogGetItemObject(vbuttonGetItem(b))

#define vbuttonCreateOfClass(c) \
    ((vbutton*)vdialogCreateItemOfClass((vdialogItemClass*)(c)))
#define vbuttonCreate() \
    vbuttonCreateOfClass(vbuttonGetDefaultClass())
#define vbuttonClone(b) \
    ((vbutton*)vdialogCloneItem(vbuttonGetItem(b)))
#define vbuttonInitOfClass(b, c) \
    vdialogInitItemOfClass(vbuttonGetItem(b), (vdialogItemClass*)(c))
#define vbuttonInit(b) \
    vbuttonInitOfClass(b, vbuttonGetDefaultClass())
#define vbuttonCopyInit(b, t) \
    vdialogCopyInitItem(vbuttonGetItem(b), vbuttonGetItem(t))
#define vbuttonLoad(r)            ((vbutton*)vdialogLoadItem(r))
#define vbuttonLoadInit(b, r)       vdialogLoadInitItem(vbuttonGetItem(b), r)
#define vbuttonDestroy(b) \
    vdialogDestroyItem(vbuttonGetItem(b))

#define vbuttonSetTitle(b, s)       vdialogSetItemTitle(vbuttonGetItem(b), s)

#define vbuttonGetClass(b) \
    ((vbuttonClass*)vdialogGetItemClass(vbuttonGetItem(b)))

#define vbuttonGetNotify(b) \
    ((vbuttonNoteProc)vdialogGetItemNotify(vbuttonGetItem(b)))
#define vbuttonSetNotify(b, n) \
    vdialogSetItemNotify((vdialogItem *)(b), (vdialogItemNoteProc)(n))

#define vbuttonHilite(b)         vcontrolHilite(vbuttonGetControl(b))
#define vbuttonHiliteWith(b,c)   vcontrolHiliteWith(vbuttonGetControl(b), c)
#define vbuttonUnhilite(b)       vcontrolUnhilite(vbuttonGetControl(b))
#define vbuttonUnhiliteWith(b,c) vcontrolUnhiliteWith(vbuttonGetControl(b), c)

#define vbuttonGetData(b)           vdialogGetItemData(vbuttonGetItem(b))
#define vbuttonGetTitle(b)          vdialogGetItemTitle(vbuttonGetItem(b))
#define vbuttonGetMenu(b)           vdialogGetItemMenu(vbuttonGetItem(b))
#define vbuttonIsShown(b)           vdialogItemIsShown(vbuttonGetItem(b))
#define vbuttonIsEnabled(b)         vdialogItemIsEnabled(vbuttonGetItem(b))
#define vbuttonIsHilited(b)         vcontrolIsHilited(vbuttonGetControl(b))

#define vbuttonSetMax(b, m)    vcontrolSetMax(vbuttonGetControl(b), m)
#define vbuttonSetMin(b, m)    vcontrolSetMin(vbuttonGetControl(b), m)
#define vbuttonSetValue(b, v)  vcontrolSetValue(vbuttonGetControl(b), v)
#define vbuttonSetValueValid(b, v) \
  vcontrolSetValueValid(vbuttonGetControl(b), v)
#define vbuttonGetMax(b)       vcontrolGetMax(vbuttonGetControl(b))
#define vbuttonGetMin(b)       vcontrolGetMin(vbuttonGetControl(b))
#define vbuttonGetValue(b)     vcontrolGetValue(vbuttonGetControl(b))

#define vbuttonIsToggle(b) (vbuttonGetMin(b)<=0 && vbuttonGetMax(b)>0)
#define vbuttonHasImageDisabling(b)  \
  (((b)->flags&_vbuttonDRAW_DISABLED_IMAGE)!=0)

#define _vbuttonIsAlternateStyle(b)  (((b)->flags&_vbuttonALT_STYLE)!=0)
/*
 * deprecated buttons
 */

/* backwards compatibility with first 3.0 release */
#define _vbuttonSetDrawDisabledImage(b,d) vbuttonSetImageDisabling(b, d)
#define _vbuttonDrawsDisabledImage(b) vbuttonHasImageDisabling(b)

#ifdef vlafOPEN_LOOK
#define vbuttonDrawOpenLookImage(r, f, t, b, k, d) \
    vlafDrawOpenLookButtonImage(r, f, t, b, k, d)
#endif

/*
 * * * * * * * * * * PRIVATE FUNCTION MESSAGE DEFINITIONS * * * * * * * * * *
 */

/*
 * buttons
 */

#define vbuttonCopy(b, t) \
    vclassSend(vbuttonGetClass(b), vobjectCOPY, (b, t))
#define vbuttonStore(b, r) \
    vclassSend(vbuttonGetClass(b), vobjectSTORE, (b, r))
#define vbuttonShow(b) \
    vclassSend(vbuttonGetClass(b), vdialogSHOW_ITEM, (b))
#define vbuttonHide(b) \
    vclassSend(vbuttonGetClass(b), vdialogHIDE_ITEM, (b))
#define vbuttonEnable(b) \
    vclassSend(vbuttonGetClass(b), vdialogENABLE_ITEM, (b))
#define vbuttonDisable(b) \
    vclassSend(vbuttonGetClass(b), vdialogDISABLE_ITEM, (b))
#define vbuttonDrawBorderWith(b,c) \
    vdialogDrawItemBorderWith(vbuttonGetItem(b), c)
#define vbuttonDrawBackgroundWith(b,c) \
    vdialogDrawItemBackgroundWith(vbuttonGetItem(b), c)
#define vbuttonDrawImageWith(b,c) \
    vdialogDrawItemImageWith(vbuttonGetItem(b), c)
#define vbuttonDrawTitleWith(b,c) \
    vdialogDrawItemTitleWith(vbuttonGetItem(b), c)
#define vbuttonDrawContentWith(b,c) \
    vdialogDrawItemContentWith(vbuttonGetItem(b), c)
#define vbuttonDrawMenuFrobWith(b,c) \
    vclassSend(vbuttonGetClass(b), vbuttonDRAW_MENU_FROB_WITH, (b,c))
#define vbuttonDrawContent(b) \
    vclassSend(vbuttonGetClass(b), vbuttonDRAW_CONTENT, (b))
#define vbuttonSetData(b, d) \
    vclassSend(vbuttonGetClass(b), vdialogSET_ITEM_DATA, (b, d))
#define vbuttonSetTitleScribed(b, s) \
    vclassSend(vbuttonGetClass(b), vdialogSET_ITEM_TITLE_SCRIBED, (b, s))
#define vbuttonSetMenu(b, m) \
    vclassSend(vbuttonGetClass(b), vdialogSET_ITEM_MENU, (b, m))

vportEND_CPLUSPLUS_EXTERN_C

#endif /* #ifndef vbuttonINCLUDED */


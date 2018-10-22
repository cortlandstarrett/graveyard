/* $Id: vcontrol.h,v 1.58 1997/11/14 21:44:59 bill Exp $ */

/************************************************************

    vcontrol.h

    C Interface file for the Control Manager

    (c) Copyright Visix Software Inc.
    All rights reserved

************************************************************/

#ifndef vcontrolINCLUDED
#define vcontrolINCLUDED

#ifndef  vportINCLUDED		/* for v*HEADER */
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

vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * * * * * * * * * * PUBLIC CONSTANT DEFINITIONS * * * * * * * * * *
 */

/*
 * controls
 */

enum {
    vcontrolPART_HOLD               = 0x0001,
    vcontrolPART_SELECT             = 0x0002,
    vcontrolPART_UNHILITE_SAME      = 0x0004,
    vcontrolPART_HOLD_IMMEDIATE     = 0x0008
};

enum {
    vcontrolID_ATTRIBUTE_VERTICAL   = vdialogITEM_NEXT_ID_ATTRIBUTE,
    vcontrolID_ATTRIBUTE_EXCLUSIVE,
    vcontrolID_ATTRIBUTE_TOGGLE,
    vcontrolID_ATTRIBUTE_VALUE,
    vcontrolID_ATTRIBUTE_MIN,
    vcontrolID_ATTRIBUTE_MAX,
    vcontrolID_ATTRIBUTE_VIEW,
    vcontrolID_ATTRIBUTE_INCREMENT,
    vcontrolID_ATTRIBUTE_PAGE,
    vcontrolID_ATTRIBUTE_SELECTION,
    vcontrolNEXT_ID_ATTRIBUTE
};
    
enum {
    vcontrolNEXT_SELECT             = vdialogITEM_NEXT_SELECT
};

/*
 * deprecated controls
 */

#ifdef vlafWINDOWS

enum {
    vcontrolWINDOWS_TOGGLE_SIZE     = 16
};

#endif

#ifdef vlafWIN95

enum {
    vcontrolWIN95_TOGGLE_SIZE     = 13
};

#endif

#ifdef vlafMOTIF

enum {
    vcontrolMOTIF_TOGGLE_SIZE       = 16
};

#endif

#ifdef vlafCUA

enum {
    vcontrolCUA_TOGGLE_SIZE         = 14
};

#endif

#ifdef vlafCUA96

enum {
    vcontrolCUA96_TOGGLE_SIZE         = 14
};

#endif


/*
 * * * * * * * * * * PUBLIC TYPE DEFINITIONS * * * * * * * * * *
 */

/*
 * controls
 */

typedef struct vcontrol             vcontrol;
typedef struct vcontrolClass        vcontrolClass;
typedef struct vcontrolPart         vcontrolPart;
typedef struct vcontrolPartWith     vcontrolPartWith;

typedef vcontrol                    vcontrolToggle;
typedef vcontrolClass               vcontrolToggleClass;

typedef vcontrol                    vcontrolOptionMenu;
typedef vcontrolClass               vcontrolOptionMenuClass;

typedef void (*vcontrolNoteProc)(
    vcontrol                       *control,
    vevent                         *event
    );

struct vcontrolPart {
    unsigned int                    flags;
    int                           (*Hit)(vcontrol *control, vevent *event);
    void                          (*Hilite)(vcontrol *control);
    void                          (*Unhilite)(vcontrol *control);
    int                           (*Track)(vcontrol *control, vevent *event);
    int                           (*Select)(vcontrol *control);
};

struct vcontrolPartWith {
    unsigned int           flags;
    int             (*Hit)(vcontrol *control, vevent *event);
    void     (*HiliteWith)(vcontrol *control, vdrawcontext *context);
    void   (*UnhiliteWith)(vcontrol *control, vdrawcontext *context);
    int       (*TrackWith)(vcontrol *control, vevent *event,
                           vdrawcontext *context);
    int      (*SelectWith)(vcontrol *control, vdrawcontext *context);
};

/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */

void vcontrolStartup(void);


/*
 * controls
 */

vcontrolClass *vcontrolGetDefaultClass(
    void
    );

vcontrolToggleClass *vcontrolGetToggleClass(
    void
    );

vcontrolOptionMenuClass *vcontrolGetOptionMenuClass(
    void
    );

vcontrol *vcontrolCreateOfClass(
    vcontrolClass                  *clas
    );

vcontrol *vcontrolCreate(
    void
    );

vcontrolToggle *vcontrolCreateToggle(
    void
    );

vcontrolOptionMenu *vcontrolCreateOptionMenu(
    void
    );

vcontrol *vcontrolClone(
    vcontrol                       *control
    );

void vcontrolInitOfClass(
    vcontrol                       *control,
    vcontrolClass                  *clas
    );

void vcontrolInit(
    vcontrol                       *control
    );

void vcontrolInitToggle(
    vcontrolToggle                 *control
    );

void vcontrolInitOptionMenu(
    vcontrolOptionMenu             *control
    );

void vcontrolDestroy(
    vcontrol                       *control
    );

void vcontrolCopy(
    vcontrol                       *control,
    vcontrol                       *target
    );

void vcontrolCopyInit(
    vcontrol                       *control,
    vcontrol                       *target
    );

vcontrol *vcontrolLoad(
    vresource                       resource
    );

void vcontrolLoadInit(
    vcontrol                       *control,
    vresource                       resource
    );

void vcontrolStore(
    vcontrol                       *control,
    vresource                       resource
    );

void vcontrolShow(
    vcontrol                       *control
    );

void vcontrolHide(
    vcontrol                       *control
    );

void vcontrolEnable(
    vcontrol                       *control
    );

void vcontrolDisable(
    vcontrol                       *control
    );

void vcontrolRecalc(
    vcontrol                       *control
    );

void vcontrolRecalcValue(
    vcontrol                       *control
    );

void vcontrolTest(
    vcontrol                       *control,
    vevent                         *event
    );

int vcontrolHit(
    vcontrol                       *control,
    vevent                         *event
    );

int vcontrolTrack(
    vcontrol                       *control,
    vevent                         *event
    );

int vcontrolTrackWith(
    vcontrol                       *control,
    vevent                         *event,
    vdrawcontext                   *context
    );

int vcontrolSelect(
    vcontrol                       *control,
    vevent                         *event
    );

int vcontrolSelectWith(
    vcontrol                       *control,
    vevent                         *event,
    vdrawcontext                   *context
    );

void vcontrolHilite(
    vcontrol                       *control
    );

void vcontrolHiliteWith(
    vcontrol                       *control,
    vdrawcontext                   *context
    );

void vcontrolUnhilite(
    vcontrol                       *control
    );

void vcontrolUnhiliteWith(
    vcontrol                       *control,
    vdrawcontext                   *context
    );

void vcontrolSetNotify(
    vcontrol                       *control,
    vcontrolNoteProc                noteProc
    );

void vcontrolSetData(
    vcontrol                       *control,
    const void                     *data
    );

void vcontrolSetTitle(
    vcontrol                       *control,
    const vchar                    *title
    );

void vcontrolSetTitleScribed(
    vcontrol                       *control,
    vscribe                        *title
    );

void vcontrolSetMenu(
    vcontrol                       *control,
    vmenu                          *menu
    );

void vcontrolSetVertical(
    vcontrol                       *control,
    int  		            flag
    );

void vcontrolSetExclusive(
    vcontrol                       *control,
    int  		            flag
    );

void vcontrolSetAlternateStyle(
    vcontrol                       *control,
    int  		            flag
    );

void vcontrolSetValue(
    vcontrol                       *control,
    int  		            value
    );

int vcontrolSetValueValid(
    vcontrol                       *control,
    int  		            value
    );

void vcontrolSetValueInverted(
    vcontrol                       *control,
    int  		            value
    );

void vcontrolSetMin(
    vcontrol                       *control,
    int  		            min
    );

void vcontrolSetMax(
    vcontrol                       *control,
    int  		            max
    );

void vcontrolSetView(
    vcontrol                       *control,
    int  		            view
    );

void vcontrolSetIncrement(
    vcontrol                       *control,
    int  		            increment
    );

void vcontrolSetPage(
    vcontrol                       *control,
    int  		            page
    );

void vcontrolSetIndicator(
    vcontrol                       *control,
    const vrect                    *rect
    );

void vcontrolSetPart(
    vcontrol                       *control,
    const vcontrolPart             *part
    );

void vcontrolSetPartWith(
    vcontrol                       *control,
    const vcontrolPartWith         *part
    );

vobjectAttributed *vcontrolGetObject(
    vcontrol                       *control
    );

vdialogItem *vcontrolGetItem(
    vcontrol                       *control
    );

vcontrolClass *vcontrolGetClass(
    vcontrol                       *control
    );

vcontrolNoteProc vcontrolGetNotify(
    vcontrol                       *control
    );

const void *vcontrolGetData(
    vcontrol                       *control
    );

const vchar *vcontrolGetTitle(
    vcontrol                       *control
    );

vmenu *vcontrolGetMenu(
    vcontrol                       *control
    );

int vcontrolIsShown(
    vcontrol                       *control
    );

int vcontrolIsEnabled(
    vcontrol                       *control
    );

int vcontrolIsVertical(
    vcontrol                       *control
    );

int vcontrolIsExclusive(
    vcontrol                       *control
    );

int vcontrolIsPinned(
    vcontrol                       *control
    );

int vcontrolIsAlternateStyle(
    vcontrol                       *control
    );

int vcontrolIsHilited(
    vcontrol                       *control
    );

int vcontrolGetValue(
    vcontrol                       *control
    );

int vcontrolGetValueInverted(
    vcontrol                       *control
    );

int vcontrolGetMin(
    vcontrol                       *control
    );

int vcontrolGetMax(
    vcontrol                       *control
    );

int vcontrolGetView(
    vcontrol                       *control
    );

int vcontrolGetIncrement(
    vcontrol                       *control
    );

int vcontrolGetPage(
    vcontrol                       *control
    );

const vrect *vcontrolGetIndicator(
    vcontrol                       *control
    );

const vcontrolPart *vcontrolGetPart(
    vcontrol                       *control
    );

const vcontrolPartWith *vcontrolGetPartWith(
    vcontrol                       *control
    );

/*
 * deprecated controls
 */

void vcontrolBoxHiliteFill(
    const vrect                    *rect,
    vcolor                         *interior,
    vcolor                         *top,
    vcolor                         *bottom
    );

void vcontrolDiamondHiliteFill(
    const vrect                    *rect,
    vcolor                         *interior,
    vcolor                         *top,
    vcolor                         *bottom
    );

/*
 * * * * * * * * * * PRIVATE CONSTANT DEFINITIONS * * * * * * * * * *
 */

/*
 * controls
 */

enum {
    _vcontrolVERTICAL               = 0x0001,
    _vcontrolEXCLUSIVE              = 0x0002,
    _vcontrolPINNED                 = 0x0004,
    _vcontrolALTERNATE_STYLE        = 0x0008,
    _vcontrolHILITED                = 0x0010,
    _vcontrolMULTI_LINE             = 0x0020
};

/*
 * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * *
 */

/*
 * controls
 */

struct vcontrol {
    vdialogItem                     item;
    int                             value, min, max;
    short                           view, increment, page;
    unsigned short                  flags;
    vrect                           indicator;
    const vcontrolPart             *part;
    const vcontrolPartWith         *partWith;

#if (vportWIN_MAC && defined(vlafMAC))
    const void			    *sysData;
#endif

};

#define vcontrolCLASS(SUPER, CONTROL, NOTIFY)                                 \
    vdialogITEM_CLASS(SUPER, CONTROL, NOTIFY);                                \
    vclassMETHOD(vcontrolRECALC, (CONTROL *control));                         \
    vclassMETHOD(vcontrolRECALC_VALUE, (CONTROL *control));                   \
    vclassMETHOD(vcontrolTEST, (CONTROL *control, vevent *event));            \
    vclassMETHOD_RET(vcontrolHIT, int, (CONTROL *control, vevent *event));    \
    vclassMETHOD_RET(vcontrolTRACK, int, (CONTROL *control, vevent *event));  \
    vclassMETHOD_RET(vcontrolTRACK_WITH, int,                                 \
                     (CONTROL *control, vevent *event, vdrawcontext *ctx));   \
    vclassMETHOD_RET(vcontrolSELECT, int, (CONTROL *control, vevent *event)); \
    vclassMETHOD_RET(vcontrolSELECT_WITH, int,                                \
                     (CONTROL *control, vevent *event, vdrawcontext *ctx));   \
    vclassMETHOD(vcontrolHILITE, (CONTROL *control));                         \
    vclassMETHOD(vcontrolHILITE_WITH,					      \
		 (CONTROL *control, vdrawcontext *context));                  \
    vclassMETHOD(vcontrolUNHILITE, (CONTROL *control));                       \
    vclassMETHOD(vcontrolUNHILITE_WITH,					      \
		 (CONTROL *control, vdrawcontext *context));                  \
    vclassMETHOD(vcontrolSET_VERTICAL, (CONTROL *control, int flag));         \
    vclassMETHOD(vcontrolSET_EXCLUSIVE, (CONTROL *control, int flag));        \
    vclassMETHOD(vcontrolSET_ALTERNATE_STYLE, (CONTROL *control, int flag));  \
    vclassMETHOD(vcontrolSET_VALUE, (CONTROL *control, int value));           \
    vclassMETHOD(vcontrolSET_MIN, (CONTROL *control, int min));               \
    vclassMETHOD(vcontrolSET_MAX, (CONTROL *control, int max));               \
    vclassMETHOD(vcontrolSET_VIEW, (CONTROL *control, int view));             \
    vclassMETHOD(vcontrolSET_INCREMENT, (CONTROL *control, int increment));   \
    vclassMETHOD(vcontrolSET_PAGE, (CONTROL *control, int page));             \
    vclassMETHOD(vcontrolSET_INDICATOR,                                       \
		 (CONTROL *control, const vrect *indicator));                 \
    vclassMETHOD(vcontrolSET_PART,                                            \
		 (CONTROL *control, const vcontrolPart *part));               \
    vclassMETHOD(vcontrolSET_PART_WITH,                                       \
		 (CONTROL *control, const vcontrolPartWith *part))

struct vcontrolClass {
    vcontrolCLASS(vcontrolClass, vcontrol, vcontrolNoteProc);
};

vportALIAS(vcontrolToggle,	vcontrol)
vportALIAS(vcontrolOptionMenu,	vcontrol)

/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * *
 */

/*
 * controls
 */

#define vcontrolGetItem(c)          vportBASE_OBJECT(c, item)
#define vcontrolGetObject(c)        vdialogGetItemObject(vcontrolGetItem(c))

#define vcontrolCreateOfClass(c) \
    ((vcontrol*)vdialogCreateItemOfClass((vdialogItemClass*)(c)))
#define vcontrolCreate() \
    vcontrolCreateOfClass(vcontrolGetDefaultClass())
#define vcontrolCreateToggle() \
    vcontrolCreateOfClass(vcontrolGetToggleClass())
#define vcontrolCreateOptionMenu() \
    vcontrolCreateOfClass(vcontrolGetOptionMenuClass())
#define vcontrolClone(c) \
    ((vcontrol*)vdialogCloneItem(vcontrolGetItem(c)))
#define vcontrolInitOfClass(i, c) \
    vdialogInitItemOfClass(vcontrolGetItem(i), (vdialogItemClass*)(c))
#define vcontrolInit(c) \
    vcontrolInitOfClass(c, vcontrolGetDefaultClass())
#define vcontrolInitToggle(c) \
    vcontrolInitOfClass(c, vcontrolGetToggleClass())
#define vcontrolInitOptionMenu(c) \
    vcontrolInitOfClass(c, vcontrolGetOptionMenuClass())
#define vcontrolCopyInit(c, t) \
    vdialogCopyInitItem(vcontrolGetItem(c), vcontrolGetItem(t))
#define vcontrolLoad(r)             ((vcontrol*)vdialogLoadItem(r))
#define vcontrolLoadInit(c, r)      vdialogLoadInitItem(vcontrolGetItem(c), r)
#define vcontrolDestroy(c) \
    vdialogDestroyItem(vcontrolGetItem(c))

#define vcontrolSetTitle(c, s)      vdialogSetItemTitle(vcontrolGetItem(c), s)

#define vcontrolGetClass(c) \
    ((vcontrolClass*)vdialogGetItemClass(vcontrolGetItem(c)))

#define vcontrolGetNotify(c) \
    ((vcontrolNoteProc)vdialogGetItemNotify(vcontrolGetItem(c)))
#define vcontrolSetNotify(c, n) \
    vdialogSetItemNotify((vdialogItem *)(c), (vdialogItemNoteProc)(n))

#define vcontrolGetData(c)             vdialogGetItemData(vcontrolGetItem(c))
#define vcontrolGetTitle(c)            vdialogGetItemTitle(vcontrolGetItem(c))
#define vcontrolGetMenu(c)             vdialogGetItemMenu(vcontrolGetItem(c))
#define vcontrolIsShown(c)             vdialogItemIsShown(vcontrolGetItem(c))
#define vcontrolIsEnabled(c)           vdialogItemIsEnabled(vcontrolGetItem(c))
#define vcontrolIsVertical(c)       (((c)->flags&_vcontrolVERTICAL)!=0)
#define vcontrolIsExclusive(c)      (((c)->flags&_vcontrolEXCLUSIVE)!=0)
#define vcontrolIsPinned(c)         (((c)->flags&_vcontrolPINNED)!=0)
#define vcontrolIsAlternateStyle(c) (((c)->flags&_vcontrolALTERNATE_STYLE)!=0)
#define vcontrolIsHilited(c)        (((c)->flags&_vcontrolHILITED)!=0)
#define vcontrolGetValue(c)          ((c)->value)
#define vcontrolGetMin(c)            ((c)->min)
#define vcontrolGetMax(c)            ((c)->max)
#define vcontrolGetView(c)           ((c)->view)
#define vcontrolGetIncrement(c)      ((c)->increment)
#define vcontrolGetPage(c)           ((c)->page)
#define vcontrolGetIndicator(c)      ((const vrect*)&(c)->indicator)
#define vcontrolGetPart(c)           ((c)->part)
#define vcontrolGetPartWith(c)       ((c)->partWith)

/*
 * deprecated controls
 */

#define vcontrolBoxHiliteFill(r, i, t, b)     vlafBoxHiliteFill(r, i, t, b)
#define vcontrolDiamondHiliteFill(r, i, t, b) vlafDiamondHiliteFill(r, i, t, b)

/*
 * * * * * * * * * * PRIVATE FUNCTION MESSAGE DEFINITIONS * * * * * * * * * *
 */

/*
 * controls
 */

#define vcontrolCopy(c, t) \
    vclassSend(vcontrolGetClass(c), vobjectCOPY, (c, t))
#define vcontrolStore(c, r) \
    vclassSend(vcontrolGetClass(c), vobjectSTORE, (c, r))
#define vcontrolShow(c) \
    vclassSend(vcontrolGetClass(c), vdialogSHOW_ITEM, (c))
#define vcontrolHide(c) \
    vclassSend(vcontrolGetClass(c), vdialogHIDE_ITEM, (c))
#define vcontrolEnable(c) \
    vclassSend(vcontrolGetClass(c), vdialogENABLE_ITEM, (c))
#define vcontrolDisable(c) \
    vclassSend(vcontrolGetClass(c), vdialogDISABLE_ITEM, (c))
#define vcontrolRecalc(c) \
    vclassSend(vcontrolGetClass(c), vcontrolRECALC, (c))
#define vcontrolRecalcValue(c) \
    vclassSend(vcontrolGetClass(c), vcontrolRECALC_VALUE, (c))
#define vcontrolTest(c, e) \
    vclassSend(vcontrolGetClass(c), vcontrolTEST, (c, e))
#define vcontrolHit(c, e) \
    vclassSend(vcontrolGetClass(c), vcontrolHIT, (c, e))
#define vcontrolTrack(c, e) \
    vclassSend(vcontrolGetClass(c), vcontrolTRACK, (c, e))
#define vcontrolTrackWith(c, e, d) \
    vclassSend(vcontrolGetClass(c), vcontrolTRACK_WITH, (c, e, d))
#define vcontrolSelect(c, e) \
    vclassSend(vcontrolGetClass(c), vcontrolSELECT, (c, e))
#define vcontrolSelectWith(c, e, d) \
    vclassSend(vcontrolGetClass(c), vcontrolSELECT_WITH, (c, e, d))
#define vcontrolHilite(c) \
    vclassSend(vcontrolGetClass(c), vcontrolHILITE, (c))
#define vcontrolHiliteWith(c, x) \
    vclassSend(vcontrolGetClass(c), vcontrolHILITE_WITH, (c, x))
#define vcontrolUnhilite(c) \
    vclassSend(vcontrolGetClass(c), vcontrolUNHILITE, (c))
#define vcontrolUnhiliteWith(c, x) \
    vclassSend(vcontrolGetClass(c), vcontrolUNHILITE_WITH, (c, x))
#define vcontrolSetData(c, d) \
    vclassSend(vcontrolGetClass(c), vdialogSET_ITEM_DATA, (c, d))
#define vcontrolSetTitleScribed(c, s) \
    vclassSend(vcontrolGetClass(c), vdialogSET_ITEM_TITLE_SCRIBED, (c, s))
#define vcontrolSetMenu(c, m) \
    vclassSend(vcontrolGetClass(c), vdialogSET_ITEM_MENU, (c, m))
#define vcontrolSetVertical(c, f) \
    vclassSend(vcontrolGetClass(c), vcontrolSET_VERTICAL, (c, f))
#define vcontrolSetExclusive(c, f) \
    vclassSend(vcontrolGetClass(c), vcontrolSET_EXCLUSIVE, (c, f))
#define vcontrolSetAlternateStyle(c, f) \
    vclassSend(vcontrolGetClass(c), vcontrolSET_ALTERNATE_STYLE, (c, f))
#define vcontrolSetValue(c, n) \
    vclassSend(vcontrolGetClass(c), vcontrolSET_VALUE, (c, n))
#define vcontrolSetMin(c, n) \
    vclassSend(vcontrolGetClass(c), vcontrolSET_MIN, (c, n))
#define vcontrolSetMax(c, n) \
    vclassSend(vcontrolGetClass(c), vcontrolSET_MAX, (c, n))
#define vcontrolSetView(c, n) \
    vclassSend(vcontrolGetClass(c), vcontrolSET_VIEW, (c, n))
#define vcontrolSetIncrement(c, n) \
    vclassSend(vcontrolGetClass(c), vcontrolSET_INCREMENT, (c, n))
#define vcontrolSetPage(c, n) \
    vclassSend(vcontrolGetClass(c), vcontrolSET_PAGE, (c, n))
#define vcontrolSetIndicator(c, r) \
    vclassSend(vcontrolGetClass(c), vcontrolSET_INDICATOR, (c, r))
#define vcontrolSetPart(c, p) \
    vclassSend(vcontrolGetClass(c), vcontrolSET_PART, (c, p))
#define vcontrolSetPartWith(c, p) \
    vclassSend(vcontrolGetClass(c), vcontrolSET_PART_WITH, (c, p))

vportEND_CPLUSPLUS_EXTERN_C

#endif /* #ifndef vcontrolINCLUDED */


/* $Id: vslider.h,v 1.25 1994/08/26 22:33:22 robert Exp $ */

/************************************************************

    vslider.h

    C Interface file for sliding controls

    (c) Copyright Visix Software Inc.
    All rights reserved

************************************************************/

#ifndef vsliderINCLUDED
#define vsliderINCLUDED

#ifndef  vportINCLUDED
#include <vport.h>
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

#ifndef  vcontrolINCLUDED
#include vcontrolHEADER
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * * * * * * * * * * PUBLIC CONSTANT DEFINITIONS * * * * * * * * * *
 */

enum {
    vsliderNEXT_ID_ATTRIBUTE        = vcontrolNEXT_ID_ATTRIBUTE
};

enum {
    vsliderNEXT_SELECT              = vcontrolNEXT_SELECT
};

/*
 * * * * * * * * * * PUBLIC TYPE DEFINITIONS * * * * * * * * * *
 */

/*
 * sliders
 */

typedef struct vsliderClass         vsliderClass;

typedef vcontrol                    vslider;

typedef vslider                     vsliderScrollBar;
typedef vsliderClass                vsliderScrollBarClass;

typedef void (*vsliderNoteProc)(
    vslider                        *slider,
    vevent                         *event
    );

/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */

void vsliderStartup(void);


/*
 * sliders
 */

vsliderClass *vsliderGetDefaultClass(
    void
    );

vsliderScrollBarClass *vsliderGetScrollBarClass(
    void
    );

vslider *vsliderCreateOfClass(
    vsliderClass                   *clas
    );

vslider *vsliderCreate(
    void
    );

vsliderScrollBar *vsliderCreateScrollBar(
    void
    );

void vsliderInitOfClass(
    vslider                        *slider,
    vsliderClass                   *clas
    );

void vsliderInit(
    vslider                        *slider
    );

void vsliderInitScrollBar(
    vsliderScrollBar               *slider
    );

void vsliderCalcContent(
    vslider                        *slider,
    vrect                          *content
    );

int vsliderCalcThumb(
    vslider                        *slider,
    int                             thin,
    int                             thick
    );

void vsliderSetValueScroll(
    vslider                        *slider,
    int                             value
    );

vsliderClass *vsliderGetClass(
    vslider                        *slider
    );

/*
 * deprecated sliders
 */

void vsliderArrowHiliteFillLeft(
    const vrect                    *bounds,
    vcolor                         *interior,
    vcolor                         *top,
    vcolor                         *bottom
    );

void vsliderArrowHiliteFillRight(
    const vrect                    *bounds,
    vcolor                         *interior,
    vcolor                         *top,
    vcolor                         *bottom
    );

void vsliderArrowHiliteFillDown(
    const vrect                    *bounds,
    vcolor                         *interior,
    vcolor                         *top,
    vcolor                         *bottom
    );

void vsliderArrowHiliteFillUp(
    const vrect                    *bounds,
    vcolor                         *interior,
    vcolor                         *top,
    vcolor                         *bottom
    );

/*
 * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * *
 */

/*
 * sliders
 */

#define vsliderCLASS(SUPER, SLIDER, NOTIFY)                                   \
    vcontrolCLASS(SUPER, SLIDER, NOTIFY);                                     \
    vclassMETHOD(vsliderCALC_CONTENT, (SLIDER *slider, vrect *content));      \
    vclassMETHOD_RET(vsliderCALC_THUMB, int,                                  \
		     (SLIDER *slider, int thin, int thick));                  \
    vclassMETHOD(vsliderSET_VALUE_SCROLL, (SLIDER *slider, int value))

struct vsliderClass {
    vsliderCLASS(vsliderClass, vslider, vsliderNoteProc);
};

vportALIAS(vslider, 		vcontrol)
vportALIAS(vsliderScrollBar,	vslider)

/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * *
 */

/*
 * sliders
 */

#define vsliderCreateOfClass(c) \
    ((vslider *) vcontrolCreateOfClass((vcontrolClass*)(c)))
#define vsliderCreate() \
    vsliderCreateOfClass(vsliderGetDefaultClass())
#define vsliderCreateScrollBar() \
    ((vsliderScrollBar *) vsliderCreateOfClass(vsliderGetScrollBarClass()))
#define vsliderInitOfClass(s, c) \
    vcontrolInitOfClass(s, (vcontrolClass*)(c))
#define vsliderInit(s) \
    vsliderInitOfClass(s, vsliderGetDefaultClass())
#define vsliderInitScrollBar(s) \
    vsliderInitOfClass(s, vsliderGetScrollBarClass())

#define vsliderGetClass(s)        ((vsliderClass*)vcontrolGetClass(s))

/*
 * deprecated sliders
 */

#define vsliderArrowHiliteFillLeft(r, i, t, b) \
    vlafArrowHiliteFillX((r)->x, (r)->y+(r)->h/2, (r)->w, (r)->h/2, i, t, b)
#define vsliderArrowHiliteFillRight(r, i, t, b) \
    vlafArrowHiliteFillX((r)->x+(r)->w, (r)->y+(r)->h/2, -(r)->w, -(r)->h/2, \
			 i, b, t)
#define vsliderArrowHiliteFillDown(r, i, t, b) \
    vlafArrowHiliteFillY((r)->x+(r)->w/2, (r)->y, (r)->h, (r)->w/2, i, b, t)
#define vsliderArrowHiliteFillUp(r, i, t, b) \
    vlafArrowHiliteFillY((r)->x+(r)->w/2, (r)->y+(r)->h, -(r)->h, -(r)->w/2, \
			 i, t, b)

/*
 * * * * * * * * * * PRIVATE FUNCTION MESSAGE DEFINITIONS * * * * * * * * * *
 */

/*
 * sliders
 */

#define vsliderCalcContent(s, r) \
    vclassSend((vsliderClass*)vcontrolGetClass(s), vsliderCALC_CONTENT, \
	       (s, r))
#define vsliderCalcThumb(s, n, k) \
    vclassSend((vsliderClass*)vcontrolGetClass(s), vsliderCALC_THUMB, \
	       (s, n, k))
#define vsliderSetValueScroll(s, v) \
    vclassSend((vsliderClass*)vcontrolGetClass(s), vsliderSET_VALUE_SCROLL, \
	       (s, v))

vportEND_CPLUSPLUS_EXTERN_C

#endif /* #ifndef vsliderINCLUDED */


/* $Id: vstrchsr.h,v 1.4 1997/08/13 16:33:39 robert Exp $ */

/************************************************************

    vstrchsr.h
    C Interface to the Str Chsrer

    (c) Copyright Visix Software  1991
    All rights reserved

************************************************************/

#ifndef vstrchsrINCLUDED
#define vstrchsrINCLUDED 1

#ifndef  vportINCLUDED		/* for v*HEADER */
#include <vport.h>
#endif

#ifndef  vdialogINCLUDED
#include vdialogHEADER
#endif

#ifndef  vconfirmINCLUDED
#include vconfirmHEADER
#endif

#ifndef  vtextitemINCLUDED
#include vtextitemHEADER
#endif
  


vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * * * * * * * * * * PUBLIC CONSTANT DEFINITIONS * * * * * * * * * *
 */

/*
 * * * * * * * * * * PUBLIC TYPE DEFINITIONS * * * * * * * * * *
 */

typedef struct vstrchsr		vstrchsr;
typedef struct vstrchsrClass	vstrchsrClass;

typedef int (*vstrchsrApplyProc) (
    vstrchsr			*chooser,
    const vchar                 *string
    );

/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */

void vstrchsrStartup(void);

vstrchsrClass *vstrchsrGetDefaultClass(void);

void vstrchsrClose(
    vstrchsr		*chooser
    );

vstrchsr *vstrchsrCreate(void);

vstrchsr *vstrchsrCreateOfClass(
    vstrchsrClass		*clas
    );

void vstrchsrDestroy(
    vstrchsr		*chooser
    );

vstrchsrApplyProc vstrchsrGetApply(
    vstrchsr		*chooser
    );

vstrchsrClass *vstrchsrGetClass(
    vstrchsr		*chooser
    );

vconfirm *vstrchsrGetConfirm(
    vstrchsr		*chooser
    );

const void *vstrchsrGetData(
    vstrchsr		*chooser
    );

vdialog *vstrchsrGetDialog(
    vstrchsr		*chooser
    );

void vstrchsrGetText(
    vstrchsr		*chooser,
    vchar               *text,
    long                 length
    );

vstr *vstrchsrGetTextAsString(
    vstrchsr		*chooser
    );

vscribe *vstrchsrGetTextScribed(
    vstrchsr            *chooser
    );

void vstrchsrOpen(
    vstrchsr		*chooser
    );

const vname *vstrchsrProcess(
    vstrchsr            *chooser
    );

void vstrchsrSetApply(
    vstrchsr		*chooser,
    vstrchsrApplyProc	 applyProc
    );

void vstrchsrSetData(
    vstrchsr		*chooser,
    const void		*data
    );

void vstrchsrSetText(
    vstrchsr		*chooser,
    const vchar         *text
    );

void vstrchsrSetTextScribed(
    vstrchsr		*chooser,
    vscribe             *scribe
    );

/* Other Routines */



/*
 * * * * * * * * * * PRIVATE CONSTANT DEFINITIONS * * * * * * * * * *
 */

enum {
  _vstrchsrFLAGS_IS_PROCESSED = 1
};

/*
 * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * *
 */

struct vstrchsr {
  vconfirm	       confirm;

  short                flags;
  vstrchsrApplyProc    applyProc;

  vtextitem           *textitem;
};

/*
 * Str Chsrer Class definition
 */

#define vstrchsrCLASS(SUPER, CONFIRM, NOTIFY, APPLY) \
    vconfirmCLASS(SUPER, CONFIRM, NOTIFY); \
    vclassMETHOD(vstrchsrSET_APPLY, \
                 (CONFIRM *chooser, APPLY applyProc)); \
    vclassMETHOD(vstrchsrSET_TEXT, \
		 (CONFIRM *chooser, const vchar *text)); \
    vclassMETHOD(vstrchsrSET_TEXT_SCRIBED, \
		 (CONFIRM *chooser, vscribe *scribe)); \
    vclassMETHOD_RET(vstrchsrHOOK_APPLY, int, \
		     (CONFIRM *chooser, const vchar *string)); \
    vclassMETHOD_RET(vstrchsrPROCESS, const vname *, \
                 (CONFIRM *chooser))

struct vstrchsrClass {
    vstrchsrCLASS(vstrchsrClass, vstrchsr,
		  vconfirmHookProc, vstrchsrApplyProc);
};

/*
 * * * * * * * * * * PRIVATE FUNCTION PROTOTYPES * * * * * * * * * *
 */

/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * *
 */

#define vstrchsrGetConfirm(h)     vportBASE_OBJECT((h), confirm)
#define vstrchsrGetDialog(h)	  vconfirmGetDialog(vstrchsrGetConfirm(h))

#define vstrchsrClose(c) \
    vclassSend(vstrchsrGetClass(c), vwindowCLOSE, (c))
#define vstrchsrCreateOfClass(c) \
    ((vstrchsr *)vconfirmCreateOfClass((vconfirmClass*)(c)))
#define vstrchsrCreate() \
    vstrchsrCreateOfClass(vstrchsrGetDefaultClass())
#define vstrchsrDestroy(h) \
    vconfirmDestroy(vstrchsrGetConfirm(h))
#define vstrchsrGetApply(h) \
    ((h)->applyProc)
#define vstrchsrGetClass(h) \
    ((vstrchsrClass *) vconfirmGetClass(vstrchsrGetConfirm(h)))
#define vstrchsrGetData(h) \
    vconfirmGetData(vstrchsrGetConfirm(h))
#define vstrchsrGetText(h, t, l) \
    vtextitemGetText((h)->textitem, t, l)
#define vstrchsrGetTextScribed(h) \
    vtextitemGetTextScribed((h)->textitem)
#define vstrchsrGetTextAsString(h) \
    vtextitemGetTextAsString((h)->textitem)
#define vstrchsrOpen(h)	\
    vclassSend(vstrchsrGetClass(h), vwindowOPEN, (h))
#define vstrchsrProcess(h)	\
    vclassSend(vstrchsrGetClass(h), vstrchsrPROCESS, (h))
#define vstrchsrSetApply(h, p) \
    vclassSend(vstrchsrGetClass(h), vstrchsrSET_APPLY, (h, p))
#define vstrchsrSetData(h, d) \
    vclassSend(vstrchsrGetClass(h), vwindowSET_DATA, (h, d))
#define vstrchsrSetText(h, t) \
    vclassSend(vstrchsrGetClass(h), vstrchsrSET_TEXT, (h, t))
#define vstrchsrSetTextScribed(h, t) \
    vclassSend(vstrchsrGetClass(h), vstrchsrSET_TEXT_SCRIBED, (h, t))

vportEND_CPLUSPLUS_EXTERN_C


#endif /* #ifndef vstrchsrINCLUDED */


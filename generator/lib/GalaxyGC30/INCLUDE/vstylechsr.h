/* $Id: vstylechsr.h,v 1.17 1997/08/13 16:33:39 robert Exp $ */

/************************************************************

    vstylechsr.h
    C Interface to the Style Chsrer

    (c) Copyright Visix Software  1991
    All rights reserved

************************************************************/

#ifndef vstylechsrINCLUDED
#define vstylechsrINCLUDED 1

#ifndef  vportINCLUDED		/* for v*HEADER */
#include <vport.h>
#endif

#ifndef  vdialogINCLUDED
#include vdialogHEADER
#endif

#ifndef  vtextitemINCLUDED
#include vtextitemHEADER
#endif

#ifndef  vconfirmINCLUDED
#include vconfirmHEADER
#endif
  
#ifndef  vlistviewINCLUDED
#include vlistitemHEADER
#endif
  
#ifndef  vfontchsrINCLUDED
#include vfontchsrHEADER
#endif
  
#ifndef  vcolorchsrINCLUDED
#include vcolorchsrHEADER
#endif


vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * * * * * * * * * * PUBLIC CONSTANT DEFINITIONS * * * * * * * * * *
 */

/*
 * * * * * * * * * * PUBLIC TYPE DEFINITIONS * * * * * * * * * *
 */

typedef struct vstylechsr		vstylechsr;
typedef struct vstylechsrClass		vstylechsrClass;

typedef int (*vstylechsrApplyFunc) (
    vstylechsr			*styleChooser,
    vtextStyle			*style
    );

/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */

void vstylechsrStartup(void);


/* Style Chooser Class Functions */

vstylechsrClass *vstylechsrGetDefaultClass(void);

/* Initialization and allocation */

vstylechsr *vstylechsrCreate(void);

vstylechsr *vstylechsrCreateOfClass(
    vstylechsrClass		*clas
    );

void vstylechsrDestroy(
    vstylechsr		*styleChooser
    );

void vstylechsrOpen(
    vstylechsr		*chooser
    );

void vstylechsrClose(
    vstylechsr		*chooser
    );

/* Style Chooser attributes modification */

void vstylechsrSetApply(
    vstylechsr		*styleChooser,
    vstylechsrApplyFunc	 applyFunc
    );

void vstylechsrSetData(
    vstylechsr		*styleChooser,
    const void		*data
    );

void vstylechsrSetStyle(
    vstylechsr		*styleChooser,
    vtextStyle		*style
    );

/* Style Chooser attributes access */

vstylechsrClass *vstylechsrGetClass(
    vstylechsr		*styleChooser
    );

vstylechsrApplyFunc vstylechsrGetApply(
    vstylechsr		*styleChooser
    );

const void *vstylechsrGetData(
    vstylechsr		*styleChooser
    );

vtextStyle *vstylechsrGetStyle(
    vstylechsr		*styleChooser
    );

/* Other Routines */

vdialog *vstylechsrGetDialog(
    vstylechsr		*styleChooser
    );


/*
 * * * * * * * * * * PRIVATE CONSTANT DEFINITIONS * * * * * * * * * *
 */

/*
 * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * *
 */

struct vstylechsr {
    vconfirm		confirm;
    vbutton		*setFont;
    vbutton		*setColor;
    vbutton		*setBackgroundColor;
    vcontrol		*bold;
    vcontrol		*italic;
    vcontrol		*underline;
    vcontrol		*hidden;
    vcontrol		*strikethru;
    vcontrol		*font;
    vcontrol		*color;
    vcontrol		*backgroundColor;
    vtextitem		*styleDisplay;
    
    vtextStyle		*style;
    vstylechsrApplyFunc	apply;
    vfontchsr		*fontChooser;
    vcolorchsr		*colorChooser;

    vfont		*chosenFont;
    vcolor		*chosenColor;
    vcolor		*chosenBackgroundColor;
    int			colorChoice;      
};

/*
 * Style Chsrer Class definition
 */

#define vstylechsrCLASS(SUPER, CONFIRM, NOTIFY)				   \
    vconfirmCLASS(SUPER, CONFIRM, NOTIFY);				   \
    vclassMETHOD(vstylechsrSET_STYLE, (CONFIRM *styleChooser,		   \
				       vtextStyle *style));		   \
    vclassMETHOD_RET(vstylechsrHOOK_APPLY_STYLE, int,			   \
		     (CONFIRM *styleChooser, vtextStyle *style))

struct vstylechsrClass {
    vstylechsrCLASS(vstylechsrClass, vstylechsr, vconfirmHookProc);
};

/*
 * * * * * * * * * * PRIVATE FUNCTION PROTOTYPES * * * * * * * * * *
 */

/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * *
 */

#define _vstylechsrGetConfirm(f)   vportBASE_OBJECT((f), confirm)

#define vstylechsrCreateOfClass(c)	\
	((vstylechsr *) vconfirmCreateOfClass((vconfirmClass *) (c)))

#define vstylechsrGetClass(f)      \
	((vstylechsrClass *) vconfirmGetClass(_vstylechsrGetConfirm(f)))
#define vstylechsrGetData(f)	   vconfirmGetData(_vstylechsrGetConfirm(f))
#define vstylechsrGetStyle(f)	   ((f)->style)
#define vstylechsrDestroy(f)	   vconfirmDestroy(_vstylechsrGetConfirm(f))
#define vstylechsrGetDialog(f)	   \
	vconfirmGetDialog(_vstylechsrGetConfirm(f))
#define vstylechsrGetApply(f)	   ((f)->apply)

/*
 * * * * * * * * * * PRIVATE FUNCTION MESSAGE DEFINITIONS * * * * * * * * * *
 */

#define vstylechsrSetData(f,d)	\
    vclassSend(vstylechsrGetClass(f), vwindowSET_DATA, (f, d))

#define vstylechsrSetStyle(f,d)	\
    vclassSend(vstylechsrGetClass(f), vstylechsrSET_STYLE, (f, d))

#define vstylechsrOpen(c)	\
    vclassSend(vstylechsrGetClass(c), vwindowOPEN, (c))

#define vstylechsrClose(c)	\
    vclassSend(vstylechsrGetClass(c), vwindowCLOSE, (c))
/*
 * * * * * * * * * STYLE CHOOSER GLOBAL VARIABLES * * * * * * * * * *
 */


vportEND_CPLUSPLUS_EXTERN_C


#endif /* #ifndef vstylechsrINCLUDED */


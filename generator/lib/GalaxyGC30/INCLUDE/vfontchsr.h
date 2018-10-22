/* $Id: vfontchsr.h,v 1.44 1997/08/13 16:33:39 robert Exp $ */

/************************************************************

    vfontchsr.h
    C Interface to the Font Chsrer

    (c) Copyright Visix Software  1991
    All rights reserved

************************************************************/

#ifndef vfontchsrINCLUDED
#define vfontchsrINCLUDED 1

#ifndef  vportINCLUDED
#include <vport.h>		/* for v*HEADER */
#endif

#ifndef  vdialogINCLUDED
#include vdialogHEADER
#endif

#ifndef  vtextitemINCLUDED
#include vtextitemHEADER
#endif

#ifndef  vlistINCLUDED
#include vlistHEADER
#endif

#ifndef  vconfirmINCLUDED
#include vconfirmHEADER
#endif
  
#ifndef  vlistitemINCLUDED
#include vlistitemHEADER
#endif


vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * * * * * * * * * * PUBLIC CONSTANT DEFINITIONS * * * * * * * * * *
 */

enum {
  vfontchsrFILTER_OPTION_NONE               = 0,
  vfontchsrFILTER_OPTION_FAMILY             = 0x01,
  vfontchsrFILTER_OPTION_FACE               = 0x02,
  vfontchsrFILTER_OPTION_FONT               = 0x04,
  vfontchsrFILTER_OPTION_ADD_CUSTOM_FONTS   = 0x08,
  vfontchsrFILTER_OPTION_ADD_EXPLICIT_FONTS = 0x10
};


#define vfontchsrDEFAULT_FILTER_OPTIONS \
     (vfontchsrFILTER_OPTION_FONT             | \
      vfontchsrFILTER_OPTION_ADD_CUSTOM_FONTS | \
      vfontchsrFILTER_OPTION_ADD_EXPLICIT_FONTS)


/*
 * * * * * * * * * * PUBLIC TYPE DEFINITIONS * * * * * * * * * *
 */

typedef struct vfontchsr		vfontchsr;
typedef struct vfontchsrClass		vfontchsrClass;
 
typedef int (*vfontchsrApplyFunc) (
    vfontchsr			*fontChooser,
    vfont			*font
    );

/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */

void vfontchsrStartup(void);


/* Font Chooser Class Functions */

vfontchsrClass *vfontchsrGetDefaultClass(void);

/* Initialization and allocation */

vfontchsr *vfontchsrCreate(void);

vfontchsr *vfontchsrCreateOfClass(
    vfontchsrClass	*clas
    );

void vfontchsrDestroy(
    vfontchsr		*fontChooser
    );

void vfontchsrOpen(
    vfontchsr		*fontChooser
    );

void vfontchsrClose(
    vfontchsr		*fontChooser
    );

const vname *vfontchsrProcess(
    vfontchsr		*fontChooser
    );

void vfontchsrSetLeader(
     vfontchsr		*fontChooser,
     vwindow            *leader
     );

void vfontchsrPlace(
    vfontchsr		*fontChooser,
    vdialog		*base,
    int			 modeX,
    int			 modeY
    );

/* Font Chooser attributes modification */

void vfontchsrSetApply(
    vfontchsr		*fontChooser,
    vfontchsrApplyFunc	 applyFunc
    );

void vfontchsrSetData(
    vfontchsr		*fontChooser,
    void		*data
    );

void vfontchsrSetFont(
    vfontchsr		*fontChooser,
    vfont		*currentFont
    );

void vfontchsrSetShowUpright(
    vfontchsr		*fontChooser,
    int			showUpright
    );

void vfontchsrSetFilterOptions(
    vfontchsr		*fontChooser,
    unsigned		 options
    );

void vfontchsrRescan(
    vfontchsr		*fontChooser
    );


/* Font Chooser attributes access */

vfontchsrClass *vfontchsrGetClass(
    vfontchsr		*fontChooser
    );

vfontchsrApplyFunc vfontchsrGetApply(
    vfontchsr		*fontChooser
    );

void *vfontchsrGetData(
    vfontchsr		*fontChooser
    );

vfont *vfontchsrGetFont(
    vfontchsr		*fontChooser
    );

int vfontchsrGetShowUpright(
    vfontchsr		*fontChooser
    );

unsigned vfontchsrGetFilterOptions(
    vfontchsr		*fontChooser
    );

/* Other Routines */

vconfirm *vfontchsrGetConfirm(
    vfontchsr		*fontChooser
    );

vdialog *vfontchsrGetDialog(
    vfontchsr		*fontChooser
    );


/*
 * * * * * * * * * * PRIVATE CONSTANT DEFINITIONS * * * * * * * * * *
 */

/*
 * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * *
 */

struct vfontchsr {
    vconfirm		confirm;
    vlistitem		*familyList;
    vlistitem		*faceList;
    vlistitem		*sizeList;
    vtextitem		*sizeEntry;
    vdialogItem		*fontDisplay;
    int		 	currFamily;
    int		 	currFace;
    int	       	 	currSize;
    vfont		*font;
    vfontFace		*face;
    vfontFamily		*family;
    double		size;
    vfontchsrApplyFunc	apply;
    const vname		*choiceTag;
    unsigned		filterOptions;
    unsigned		showUpright:1;
    unsigned		isBlocking:1;
    unsigned		filterDirty:1;
    unsigned		ignoreNotify:1;
};

/*
 * Font Chsr Class definition
 */

#define vfontchsrCLASS(SUPER, CONFIRM, NOTIFY)				   \
    vconfirmCLASS(SUPER, CONFIRM, NOTIFY);				   \
    vclassMETHOD(vfontchsrSET_FONT, (CONFIRM *fontChooser, vfont *font));  \
    vclassMETHOD(vfontchsrSET_SHOW_UPRIGHT, (CONFIRM *fontChooser,	   \
					     int showUpright));		   \
    vclassMETHOD_RET(vfontchsrHOOK_APPLY_FONT, int,			   \
		     (CONFIRM *fontChooser, vfont *font));		   \
    vclassMETHOD_RET(vfontchsrFILTER, vbool,(CONFIRM *fontChooser,	   \
					     vfont *font));                \
    vclassMETHOD_RET(vfontchsrFILTER_FAMILY, vbool, (CONFIRM *fontChooser, \
					     vfontFamily *family));        \
    vclassMETHOD_RET(vfontchsrFILTER_FACE, vbool, (CONFIRM *fontChooser,   \
                                             vfontFace *face));            \
    vclassMETHOD(vfontchsrSET_FILTER_OPTIONS, (CONFIRM *fontChooser,       \
					       unsigned options));         \
    vclassMETHOD(vfontchsrFILTER_RESCAN, (CONFIRM *fontChooser))

struct vfontchsrClass {
    vfontchsrCLASS(vfontchsrClass, vfontchsr, vconfirmHookProc);
};


/*
 * * * * * * * * * * PRIVATE FUNCTION PROTOTYPES * * * * * * * * * *
 */

/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * *
 */

#define vfontchsrGetConfirm(f)	   vportBASE_OBJECT((f), confirm)

#define vfontchsrCreateOfClass(c)	\
	((vfontchsr *) vconfirmCreateOfClass((vconfirmClass *) (c)))

#define vfontchsrGetClass(f)	((vfontchsrClass*) vconfirmGetClass \
				 (vfontchsrGetConfirm(f)))

#define vfontchsrGetData(f)	   vconfirmGetData(vfontchsrGetConfirm(f))
#define vfontchsrGetShowUpright(f) ((f)->showUpright)
#define vfontchsrGetFilterOptions(f)  ((f)->filterOptions)
#define vfontchsrGetFont(f)	   ((f)->font)
#define vfontchsrDestroy(f)	   vconfirmDestroy(vfontchsrGetConfirm(f))
#define vfontchsrGetDialog(f)	   vconfirmGetDialog(vfontchsrGetConfirm(f))

#define vfontchsrGetApply(f) 	   ((f)->apply)

#define vfontchsrSetLeader(f, w)    \
  vwindowSetLeader(vdialogGetWindow(vfontchsrGetDialog(f)), \
		   (w) ? (w) : vwindowGetRoot())

#define vfontchsrPlace(f,w,x,y) \
  vdialogPlaceWindow(vfontchsrGetDialog(f), \
	       (w) ? vdialogGetWindow(w) : vwindowGetRoot(), x, y)

/*
 * * * * * * * * * * PRIVATE FUNCTION MESSAGE DEFINITIONS * * * * * * * * * *
 */

#define vfontchsrSetData(f,d)	\
	vclassSend(vfontchsrGetClass(f), vwindowSET_DATA, (f, d))

#define vfontchsrSetFont(f,d)	\
	vclassSend(vfontchsrGetClass(f), vfontchsrSET_FONT, (f, d))

#define vfontchsrSetShowUpright(f,d)	\
	vclassSend(vfontchsrGetClass(f), vfontchsrSET_SHOW_UPRIGHT, (f, d))

#define vfontchsrSetFilterOptions(f,o) \
        vclassSend(vfontchsrGetClass(f), vfontchsrSET_FILTER_OPTIONS, (f,o))

#define vfontchsrOpen(c)	\
	vclassSend(vfontchsrGetClass(c), vwindowOPEN, (c))

#define vfontchsrClose(c)	\
	vclassSend(vfontchsrGetClass(c), vwindowCLOSE, (c))

#define vfontchsrRescan(c)      \
        vclassSend(vfontchsrGetClass(c), vfontchsrFILTER_RESCAN, (c))

/*
 * * * * * * * * * FONT CHOOSER GLOBAL VARIABLES * * * * * * * * * *
 */


vportEND_CPLUSPLUS_EXTERN_C


#endif /* vfontchsrINCLUDED */


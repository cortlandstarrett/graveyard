/* $Id: vcolorchsr.h,v 1.21 1997/10/02 21:25:37 robert Exp $ */

/************************************************************

    vcolorchsr.h
    C Interface file for the color chooser

    (c) Copyright Visix Software Inc.
    All rights reserved

************************************************************/

#ifndef vcolorchsrINCLUDED
#define vcolorchsrINCLUDED 1

#ifndef  vportINCLUDED
#include <vport.h>		/* for v*HEADER */
#endif

#ifndef  vtextitemINCLUDED
#include vtextitemHEADER
#endif

#ifndef  vlistitemINCLUDED
#include vlistitemHEADER
#endif

#ifndef  vcontainerINCLUDED
#include vcontainerHEADER
#endif

#ifndef  vcontrolINCLUDED
#include vcontrolHEADER
#endif

#ifndef  vconfirmINCLUDED
#include vconfirmHEADER
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * * * * * * * * * CONSTANTS AND MACRO DEFINITIONS * * * * * * * * * *
 */

enum{
  _vcolorchsrTOLERANCE_PANEL_FLAG	= 1
};

enum{
  vcolorchsrHLS		= 1,
  vcolorchsrRGB,
  vcolorchsrCMY,
  vcolorchsrGRAY,
  vcolorchsrNAME
};

enum{
  vcolorchsrSORT_BY_NAME	= 1,
  vcolorchsrSORT_BY_HUE		
};

enum{
  vcolorchsrSELECT_WHEEL		= vdialogNEXT_SELECT,
  vcolorchsrSELECT_TOLERANCES		,
  vcolorchsrSELECT_NAMES		,
  vcolorchsrSELECT_REFORM	     	,
  vcolorchsrSELECT_LG_DITHER		,
  vcolorchsrSELECT_SM_DITHER		,
  vcolorchsrSELECT_SOLID		,
  vcolorchsrSELECT_PRECISE_LG_DITHER	,
  vcolorchsrSELECT_PRECISE_SM_DITHER	,
  vcolorchsrSELECT_PRECISE_SOLID     	,
  vcolorchsrSELECT_RG_PLANE		,
  vcolorchsrSELECT_RB_PLANE		,
  vcolorchsrSELECT_BG_PLANE		,
  vcolorchsrSELECT_SORT_NAME		,
  vcolorchsrSELECT_SORT_HUE		,
  vcolorchsrSELECT_ADD_COLOR		
};

enum {
  vcolorchsrRG_PLANE		= 1,
  vcolorchsrRB_PLANE,
  vcolorchsrBG_PLANE,

  vcolorchsrCM_PLANE		= vcolorchsrRG_PLANE,
  vcolorchsrCY_PLANE		= vcolorchsrRB_PLANE,
  vcolorchsrMY_PLANE		= vcolorchsrBG_PLANE
};

enum {
  vcolorchsrWHEEL_PANEL		= 1,
  vcolorchsrTOLERANCES_PANEL,
  vcolorchsrNAMED_COLORS_PANEL
};


/*
 * * * * * * * * * TYPE AND STRUCTURE DEFINITIONS * * * * * * * * * *
 */

typedef struct vcolorchsr	 vcolorchsr;
typedef struct vcolorchsrClass	 vcolorchsrClass;

typedef void (*vcolorchsrApplyFunc)( vcolorchsr *chooser, vcolor *color );

/*
 * * * * * * * * * * FUNCTION PROTOTYPES * * * * * * * * * *
 */

void vcolorchsrStartup(void);


vcolorchsrClass *vcolorchsrGetDefaultClass(
    void
    );

vcolorchsr *vcolorchsrCreateOfClass( 
    vcolorchsrClass		*clas
    );

vcolorchsr *vcolorchsrCreate(
    void
    );

void vcolorchsrDestroy( 
    vcolorchsr			*chooser
    );

void vcolorchsrOpen(
    vcolorchsr			*chooser
    );

const vname *vcolorchsrProcess(
    vcolorchsr			*chooser
    );

void vcolorchsrClose(
    vcolorchsr			*chooser
    );

/* Color Chooser attribute modification */

void vcolorchsrSetApply(
    vcolorchsr			*chooser,
    vcolorchsrApplyFunc		 applyFunc
    );

void vcolorchsrSetData( 
    vcolorchsr			*chooser,
    void			*data
    );

void vcolorchsrSetColor( 
    vcolorchsr			*chooser,
    vcolor			*color
    );

void vcolorchsrSetColorSpec( 
    vcolorchsr			*chooser,
    vcolorSpec			*color
    );

void vcolorchsrSetMethod( 
    vcolorchsr			*chooser,
    int			 	 method
    );

void vcolorchsrSetPanel(
    vcolorchsr			*chooser,
    int				 whichPanel
    );

void vcolorchsrSetNamedSortType(
    vcolorchsr			*chooser,
    int				 whichSort
    );

void vcolorchsrSetPlane(
    vcolorchsr			*chooser,
    int				 whichPlane
    );

void vcolorchsrSetSavedSpecAt(
    vcolorchsr		    	*chooser,
    int				 index,
    vcolorSpec			*spec
    );

void vcolorchsrSetTolerancePanel(
    vcolorchsr		    	*chooser,
    int				 value
    );

void vcolorchsrSetTitle(
    vcolorchsr			*chooser,
    const vchar			*title
    );

void vcolorchsrSetTitleScribed(
    vcolorchsr			*chooser,
    vscribe			*title
    );

void vcolorchsrSetLeader(
    vcolorchsr			*chooser,
    vwindow			*leader
    );

void vcolorchsrPlace(
   vcolorchsr			*chooser,
   vdialog			*base,
   int				 modeX,
   int				 modeY
   );

void vcolorchsrSetPreferNative(
    vcolorchsr			*chooser,
    int			 	doNative
    );

void vcolorchsrSetOverridePreferNative(
    vcolorchsr			*chooser,
    int			 	doNative
    );

/* Color Chooser attribute access */

vcolorchsrClass *vcolorchsrGetClass(
    vcolorchsr			*chooser 
    );

vcolor *vcolorchsrGetColor( 
    vcolorchsr			*chooser
    );

vcolorSpec *vcolorchsrGetColorSpec(
    vcolorchsr			*chooser
    );

void *vcolorchsrGetData(
    vcolorchsr			*chooser 
    );

int vcolorchsrGetMethod( 
    vcolorchsr			*chooser
    );

vcolorchsrApplyFunc vcolorchsrGetApply(
    vcolorchsr			*chooser
    );

int vcolorchsrHasTolerancePanel(
    vcolorchsr		    	*chooser
    );

int vcolorchsrGetSavedSpecCount(
    vcolorchsr		    	*chooser
    );

vcolorSpec *vcolorchsrGetSavedSpecAt(
    vcolorchsr		    	*chooser,
    int				 index
    );

int vcolorchsrGetPanel(
    vcolorchsr			*chooser
    );

int vcolorchsrGetPlane(
    vcolorchsr			*chooser
    );

int vcolorchsrGetNamedSortType(
    vcolorchsr			*chooser
    );

int vcolorchsrPrefersNative(
    vcolorchsr			*chooser
    );

/* Other Routines */

void vcolorchsrSetReformRGB_CMY(
    vcolorchsr			*chooser,
    int				 value
    );

vbool vcolorchsrGetReformRGB_CMY(
    vcolorchsr			*chooser
    );

vconfirm *vcolorchsrGetConfirm(
    vcolorchsr			*chooser
    );

vdialog *vcolorchsrGetDialog(
    vcolorchsr	   		*chooser
    );


/*
 * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * *
 */

struct vcolorchsr{
  vconfirm		 confirm;
  unsigned short	 flags;
  vdialogItem	   	*choiceUser;
  vdialogItem	     	*wheelUser;
  vtextitem	     	*text1;
  vtextitem	     	*text2;
  vtextitem	       	*text3;
  vdialogItem	 	*nameStat1;
  vdialogItem	     	*nameStat2;
  vdialogItem	     	*nameStat3;
  vcontrol	   	*user1;
  vcontrol	     	*user2;
  vcontrol	     	*user3;
  vdialogItem	     	*label1;
  vdialogItem	   	*label2;
  vdialogItem	   	*label3;
  vdialogItem		*mostUsed;
  vcontrol		*optionMenu;
  int			 method;
  vcolorSpec		*origColor;
  vcolorSpec		*editColor;
  vcolorSpec		*currColor;
  vcolorSpec	        *hsPalette;
  vimage		*img1;
  vimage		*img2;
  vimage		*img3;
  vimage		*hsOffscreen;
  vimage	      	*cubeImage;
  vbool			 reform;
  vcolorchsrApplyFunc	 applyProc;
  vcontainer		*container;
  vcontainer		*tolerancePanel;
  vcontainer		*wheelPanel;
  vcontainer		*namePanel;
  vcontainer		*currPanel;
  int			 whichPlane;
  vlistitem		*nameList;
  vtextitem		*deltaText1;
  vtextitem		*deltaText2;
  vtextitem		*deltaText3;
  vdialogItem		*deltaLabel1;
  vdialogItem		*deltaLabel2;
  vdialogItem		*deltaLabel3;
  vcontrol		*deltaSlider1;
  vcontrol		*deltaSlider2;
  vcontrol		*deltaSlider3;
  vcontrol		*deltaBtn;
  vcontrol		*distanceBtn;
  vtextitem		*distText;
  vcontrol		*distSlider;
  vdialogItem		*distLabel;
  vcontrol		*ditherArea;
  int			 colorSort;
  vmenuItem		*tolerPanelItem;
  vmenuItem		*tolerSubMenuItem;

  vbool			 doSys;
  vbool			 doSysOverride;
  vbool			 isBlocking;
  const void		*sysData;
  const vname		*choiceTag;
};

/*
 * Color Chooser Class definition
 */

#define vcolorchsrCLASS(SUPER, CHOOSER, HOOK)				\
    vconfirmCLASS(SUPER, CHOOSER, HOOK);				\
    vclassMETHOD_RET(vcolorchsrHOOK_APPLY_COLOR, vbool,			\
		     (CHOOSER *chooser, vcolor *color));		\
    vclassMETHOD(vcolorchsrAPPLY_COLOR,					\
		 (CHOOSER *chooser, vcolor *color))

struct vcolorchsrClass {
    vcolorchsrCLASS( vcolorchsrClass, vcolorchsr, vconfirmHookProc );
};


typedef vdialogItem		vcolorchsrWheelItem;

/*
 * * * * * * * * * * PRIVATE FUNCTION PROTOTYPES * * * * * * * * * *
 */

/*
 * * * * * * * * * FUNCTIONS IMPLEMENTED AS MACROS * * * * * * * *
 */

#define vcolorchsrGetBase( c )	vportBASE_OBJECT( c, confirm )

#define vcolorchsrCreateOfClass( c )	\
  ( (vcolorchsr *) vconfirmCreateOfClass( (vconfirmClass *) (c) ) )
#define vcolorchsrGetClass( c ) \
  ( (vcolorchsrClass *) vconfirmGetClass( (vconfirm *) (c) ) )
#define vcolorchsrCreate() \
  vcolorchsrCreateOfClass( vcolorchsrGetDefaultClass() )
#define vcolorchsrDestroy( c ) \
  vconfirmDestroy(vcolorchsrGetBase(c))

#define vcolorchsrGetMethod( c )	( (c)->method )
#define vcolorchsrGetData( c )	\
  ( vconfirmGetData( vcolorchsrGetBase(c) ) )
#define vcolorchsrGetDialog( c ) \
  ( vconfirmGetDialog( vcolorchsrGetBase(c) ) )
#define vcolorchsrGetConfirm( c )	( vcolorchsrGetBase(c) )
#define vcolorchsrGetApply( c ) 	( (c)->applyProc )

#define vcolorchsrGetPlane( c )		( (c)->whichPlane )
#define vcolorchsrGetNamedSortType( c )	( (c)->colorSort )
#define vcolorchsrGetSavedSpecCount( c )( 16 )

#define vcolorchsrHasTolerancePanel( c )\
  (((c)->flags & _vcolorchsrTOLERANCE_PANEL_FLAG) != 0)

#define vcolorchsrGetReformRGB_CMY(c)	((c)->reform)

#define vcolorchsrSetPreferNative(c,b)		((c)->doSys = ((b) != 0))
#define vcolorchsrPrefersNative(c)		((c)->doSys || (c)->doSysOverride)
#define vcolorchsrSetOverridePreferNative(c,b)	((c)->doSysOverride = ((b) != 0))

#define vcolorchsrSetTitle( c,t ) \
  vcolorchsrSetTitleScribed((c), (t) ? vcharScribe(t) : NULL)

#define vcolorchsrPlace(c, b, mx, my) \
  vdialogPlace(vcolorchsrGetDialog(c), b, mx, my)

/*
 * * * * * * * * * FUNCTION DEFINED AS MESSAGES * * * * * * * * * *
 */

#define vcolorchsrSetData( c, d ) \
  vclassSend( vcolorchsrGetClass( c ), vwindowSET_DATA, (c, d) )
#define vcolorchsrOpen( c ) \
  vclassSend( vcolorchsrGetClass( c ), vwindowOPEN, (c) )
#define vcolorchsrClose( c ) \
  vclassSend( vcolorchsrGetClass( c ), vwindowCLOSE, (c) )

#define vcolorchsrSetTitleScribed( c,t ) \
  vclassSend( vcolorchsrGetClass( c ), vwindowSET_TITLE_SCRIBED, (c,t))
#define vcolorchsrSetLeader( c, d ) \
  vclassSend( vcolorchsrGetClass( c ), vwindowSET_LEADER, (c, d) )


vportEND_CPLUSPLUS_EXTERN_C

#endif /* vcolorchsrINCLUDED */

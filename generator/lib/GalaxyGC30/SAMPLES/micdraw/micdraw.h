/* $Id: micdraw.h,v 1.21 1997/10/23 21:39:43 gregt Exp $ */

/************************************************************

    microdraw.c
    C Implementation file for the Microdraw


    (c) Copyright Visix Software Inc.
    All rights reserved

************************************************************/
 
/*----------------------------------------------------------------------------
 * The following Sample Code is provided for your reference purposes in
 * connection with your use of the Galaxy Application Environment (TM) software
 * product which you have licensed from Visix Software, Inc. ("Visix").
 * The Sample code is provided to you without any warranty of any kind
 * whatsoever and you agree to be responsible for the use and/or incorporation
 * of the Sample Code into any software product you develop. You agree to fully
 * and completely indemnify and hold Visix harmless from any and all loss,
 * claim, liability or damages with respect to your use of the Sample Code.
 *
 * Subject to the foregoing, you are permitted to copy, modify, and
 * distribute the Sample Code for any purpose and without fee,
 * provided that (i) a copyright notice in the form of "Copyright
 * 1992, 1993, 1994 Visix Software Inc., 11440 Commerce Park Drive,
 * Reston, VA 22091. All Rights Reserved" appears in all copies, (ii)
 * both the copyright notice and this permission notice appear in
 * supporting documentation and (iii) you are a valid licensee of
 * Galaxy Application Environment.
 ---------------------------------------------------------------------------*/

#ifndef _vmicrodrawINCLUDED
#define _vmicrodrawINCLUDED

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

#ifndef  vscribeINCLUDED
#include vscribeHEADER
#endif

#ifndef  vcharINCLUDED
#include vcharHEADER
#endif

#ifndef  vstrINCLUDED
#include vstrHEADER
#endif

#ifndef  vnameINCLUDED
#include vnameHEADER
#endif

#ifndef  vdictINCLUDED
#include vdictHEADER
#endif

#ifndef  vfsINCLUDED
#include vfsHEADER
#endif

#ifndef  vresourceINCLUDED
#include vresourceHEADER
#endif

#ifndef  vclassINCLUDED
#include vclassHEADER
#endif

#ifndef  vcommandINCLUDED
#include vcommandHEADER
#endif

#ifndef  vundoINCLUDED
#include vundoHEADER
#endif

#ifndef  vcolorINCLUDED
#include vcolorHEADER
#endif

#ifndef  vimageINCLUDED
#include vimageHEADER
#endif

#ifndef  vtextINCLUDED
#include vtextHEADER
#endif

#ifndef  vdomainINCLUDED
#include vdomainHEADER
#endif

#ifndef  vdrawcontextINCLUDED
#include vdrawcontextHEADER
#endif

#ifndef  vcursorINCLUDED
#include vcursorHEADER
#endif

#ifndef  vwindowINCLUDED
#include vwindowHEADER
#endif

#ifndef  vmenuINCLUDED
#include vmenuHEADER
#endif

#ifndef  vapplicationINCLUDED
#include vapplicationHEADER
#endif

#ifndef  vdialogINCLUDED
#include vdialogHEADER
#endif

#ifndef  vmenubarINCLUDED
#include vmenubarHEADER
#endif

#ifndef  vtextviewINCLUDED
#include vtextviewHEADER
#endif

#ifndef  vpaletteINCLUDED
#include vpaletteHEADER
#endif

#ifndef  vdomainviewINCLUDED
#include vdomainviewHEADER
#endif

#ifndef  vnoticeINCLUDED
#include vnoticeHEADER
#endif

#ifndef  vcolorchsrINCLUDED
#include vcolorchsrHEADER
#endif

#ifndef  vfilechsrINCLUDED
#include vfilechsrHEADER
#endif

#ifndef  vstylechsrINCLUDED
#include vstylechsrHEADER
#endif

#ifndef mdrawUSE_DAS
#define mdrawUSE_DAS	1
#endif

#if mdrawUSE_DAS

#ifndef  vserviceINCLUDED
#include vserviceHEADER
#endif

#ifndef  vsessionINCLUDED
#include vsessionHEADER
#endif

#endif /* mdrawUSE_DAS */


/*
 * * * * * * * * * CONSTANTS AND MACRO DEFINITIONS * * * * * * * * * *
 */

/* Tool Types */

enum {
     vmdrawARROW_TOOL	        = 1,
     vmdrawTEXT_TOOL		= 2,
     vmdrawLINE_TOOL		= 3,
     vmdrawRECT_TOOL	        = 4,
     vmdrawRRECT_TOOL	        = 5,
     vmdrawOVAL_TOOL		= 6,
     vmdrawPOLYGON_TOOL		= 7,	/* Not Implemented */
     vmdrawARC_TOOL		= 8,	/* Not Implemented */
     vmdrawFREEHAND_TOOL	= 9,	/* Not Implemented */
     vmdrawNUM_TOOLS		= 9
};


/* View Menu Settings */

enum {
     vmdrawVIEW_GRID_LINES	= 0x0001,
     vmdrawSHOW_LAYERING	= 0x0002
};

/* Domain Manager Object Types */

enum {
     vmdrawTEXT_OBJECT	        = 2,
     vmdrawLINE_OBJECT	        = 3,
     vmdrawRECT_OBJECT	        = 4,
     vmdrawRRECT_OBJECT	        = 5,
     vmdrawOVAL_OBJECT	        = 6,
     vmdrawFILL_RECT_OBJECT	= 7,
     vmdrawFILL_RRECT_OBJECT	= 8,
     vmdrawFILL_OVAL_OBJECT	= 9
};

/* Value for 'flag' field in document structure */

enum {
    vmdrawDOC_READ_ONLY		= 0x0001,
    vmdrawDOC_SELECTION		= 0x0002,
    vmdrawDOC_SNAP_TO_GRID	= 0x0004
};

/* Values for 'arrow' field in vmdrawPen structure */

enum {
    vmdrawNO_ARROWS             = 0,
    vmdrawSTART_ARROW           = 0x0001,
    vmdrawEND_ARROW             = 0x0002
};

/* Values for "corner" field in vmdrawDocument & vmdrawObjectData structure */

enum {
    vmdrawCORNER_LOWER_LEFT	= 0,
    vmdrawCORNER_UPPER_LEFT	= 1,
    vmdrawCORNER_LOWER_RIGHT	= 2,
    vmdrawCORNER_UPPER_RIGHT	= 3
    };

/* Returns values for vmdrawSaveDocument */

enum {
    vmdrawDID_SAVE_AS		= 0,
    vmdrawSAVED			= 1,
    vmdrawWAS_READ_ONLY		= 2
    };

/*
 * Application Commands
 */

enum {
    comNEW_DOCUMENT		= vapplicationNEXT_SELECT,
    comOPEN_REQUEST,
    comABOUT_MICRO_DRAW,
    comINFORMATION,
    comQUIT,
    comCONNECT
};

/*
 * Values for 'option' field in Preference data
 */

enum {
    vmdrawPREF_BACKUP                    = 0x0001,
    vmdrawPREF_AUTO_STROKE               = 0x0002,
    vmdrawPREF_AUTO_TIME                 = 0x0004
};

/*
 * Document Commands
 */

enum {
    comCLOSE_WINDOW	= vdialogNEXT_SELECT,
    comREVERT,
    comSAVE,
    comSHOW_VERTICAL_SCROLL_BAR,
    comSHOW_HORIZONTAL_SCROLL_BAR,
    comMOVE,
    comALIGN,
    comDISTRIBUTE,
    comDRAG,
    comSELECTION,
    comSNAP_TO_GRID,
    comGRID_LINES,
    comSET_GRID,
    comDRAWING_SIZE,
    comAUTO_SCROLLING,
    comSHOW_LAYERING,
    comORIGIN_AT_TOP_LEFT,
    comROTATE,
    comFLIP,
    comZOOM_IN,
    comZOOM_OUT,
    comGROUP,
    comUNGROUP,
    comPEN,
    comPATTERN,
    comSET_TARGET_OBJECT,
    comOFFSCREEN_DRAWING,
    comSAVE_TEMPLATE,
    comDUMP_OBJECTS,
    comPOSITION,
    comVIRTUAL_BOUNDS,
    comSET_STYLE,
    comAPPLY_STYLE,
    comAPPLY_JUSTIFICATION,
    comAPPLY_CASE,
    /*  ---  mdrawUSE_DAS  ---  */
    comDISCONNECT, /* not used */
    comREGISTER,
    comUNREGISTER,
    /*  ---  mdrawUSE_DAS  ---  */
    comMAX_DOC_SELECTOR
};

/*
 * Array values in the global string resource array
 */

enum {
    vmdrawMSG_UNTITLED		= 0,
    vmdrawMSG_SAVE_CHANGES,
    vmdrawMSG_ALREADY_EXISTS,
    vmdrawMSG_SAVE_DOCUMENT,
    vmdrawMSG_CANT_SAVE_CHANGES,
    vmdrawMSG_OPEN_FILE,
    vmdrawMSG_READ_ERROR
    };

/*
 * Pre-defined names
 */

enum {
    _vmdraw_Option,
    _vmdraw_As,
    _vmdraw_Front,
    _vmdraw_Back,
    _vmdraw_Forward,
    _vmdraw_Backward,
    _vmdraw_Target,
    _vmdraw_Vertical,
    _vmdraw_Horizontal,
    _vmdraw_Grid,  
    _vmdraw_Limit,
    _vmdraw_Two,
    _vmdraw_None,
    _vmdraw_Normal,
    _vmdraw_Auto,
    _vmdraw_External,
    _vmdraw_Enclose,
    _vmdraw_Single,
    _vmdraw_Live,
    _vmdraw_Objects,
    _vmdraw_All,
    _vmdraw_In,
    _vmdraw_Count
};

#define vmdraw_Option       	(_vmdrawPredefs[_vmdraw_Option])
#define vmdraw_As       	(_vmdrawPredefs[_vmdraw_As])
#define vmdraw_Front       	(_vmdrawPredefs[_vmdraw_Front])
#define vmdraw_Back       	(_vmdrawPredefs[_vmdraw_Back])
#define vmdraw_Forward      	(_vmdrawPredefs[_vmdraw_Forward])
#define vmdraw_Backward       	(_vmdrawPredefs[_vmdraw_Backward])
#define vmdraw_Target       	(_vmdrawPredefs[_vmdraw_Target])
#define vmdraw_Vertical       	(_vmdrawPredefs[_vmdraw_Vertical])
#define vmdraw_Horizontal      	(_vmdrawPredefs[_vmdraw_Horizontal])
#define vmdraw_Grid       	(_vmdrawPredefs[_vmdraw_Grid])
#define vmdraw_Limit       	(_vmdrawPredefs[_vmdraw_Limit])
#define vmdraw_Two       	(_vmdrawPredefs[_vmdraw_Two])
#define vmdraw_None       	(_vmdrawPredefs[_vmdraw_None])
#define vmdraw_Normal       	(_vmdrawPredefs[_vmdraw_Normal])
#define vmdraw_Auto       	(_vmdrawPredefs[_vmdraw_Auto])
#define vmdraw_External       	(_vmdrawPredefs[_vmdraw_External])
#define vmdraw_Enclose       	(_vmdrawPredefs[_vmdraw_Enclose])
#define vmdraw_Single       	(_vmdrawPredefs[_vmdraw_Single])
#define vmdraw_Live       	(_vmdrawPredefs[_vmdraw_Live])
#define vmdraw_Objects       	(_vmdrawPredefs[_vmdraw_Objects])
#define vmdraw_All       	(_vmdrawPredefs[_vmdraw_All])
#define vmdraw_In       	(_vmdrawPredefs[_vmdraw_In])

#define vmdrawJOINT_SIZE	2
#define vmdrawMAX_DOCUMENTS	20
#define vmdrawWINDOW_SPACING	5
#define vmdrawMAX_PENPAT_SIZE   6

/*
 * * * * * * * * * TYPE AND STRUCTURE DEFINITIONS * * * * * * * * * *
 */

typedef struct vmdrawPen		vmdrawPen;

struct vmdrawPen {
    short               pat[vmdrawMAX_PENPAT_SIZE];
    vbyte	        size;
    vbyte		arrows;
    vbyte		thickness;
    vcolor		*color;
};


typedef struct vmdrawPattern		vmdrawPattern;

struct vmdrawPattern {
    vimage		*image;
    vbool		transparent;
};


typedef struct vmdrawDocument		vmdrawDocument;
typedef struct vmdrawDocumentClass	vmdrawDocumentClass;

struct vmdrawDocument {
    vdialog			dialog;
    struct vmdrawDocument     	*next;
    vchar			*name;
    vresource			fileSpec;
    vbyteSigned			newIndex;
    vbyte			flags;
    vundoLog			*undoLog;
    vdomainObject		*targetObject;

    short			currentTool;
    short			viewSettings;
    int				documentWidth;
    int				documentHeight;
    short			alignOption;

    vdomainObject		*resizeObject;
    short			corner;
    short			clickedOnStart;
    int				lockedCell;

    float			scale;
    vmatrix			matrix;

    vdomainview			*domainView;
    vpalette			*palette;
    vdialogItem			*scaleItem;
    vmenubar			*menuBar;
    vmenu			*windowMenu;

    vtextview			*floatTextView;
    vtextview			*editTextView;
    vdomainObject		*editingObject;

    vdict			*standardState;
    vcommandSpace		*space;

#if (mdrawUSE_DAS)
    unsigned int		 idNext;
    vsession			*session;
    vservice			*service;
    vdomainObserver		*observerSessionDomain;
    vtextObserver		*observerSessionText;
    vdict			*dictObjectMap;
#endif
};

#define vmdrawDocumentCLASS(SUPER, DIALOG)	                             \
    vdialogCLASS(SUPER, DIALOG, vdialogNoteProc, vdialogItem,		     \
		 vdialogItemList); \
    vclassMETHOD(vmdrawDocumentNO_OP, (DIALOG *))

struct vmdrawDocumentClass {
    vmdrawDocumentCLASS(vmdrawDocumentClass, vmdrawDocument);
};


typedef struct vmdrawObjectData {
    vtext		*text;
    vmdrawPen		pen;
    vmdrawPattern	pattern;
    short		startCorner;	
    short		layerNumber;
#if (mdrawUSE_DAS)
    unsigned int	id;
#endif
} vmdrawObjectData;

/*
 * Preference Information
 */

typedef struct vmdrawPreferenceData {
    short	    numAutoActions;  /* Number of actions between saves */
    short	    numAutoMinutes;  /* Number of minutes between saves */
    unsigned long   options;
    short	    maxUndos;	     /* Levels of Undo		        */
} vmdrawPreferenceData;
    
typedef struct vmdrawTemplatePreferenceData {
    vrect		newDocumentRect;
    vdomainGrid		grid;
    float		scale;
    short		viewSettings;
    short		alignOption;
    int			documentWidth;
    int			documentHeight;
} vmdrawTemplatePreferenceData;


/*
 * * * * * * * * * FUNCTION PROTOTYPES * * * * * * * * * *
 */

    
/* microdraw.c */

vnotice *vmdrawAlert(
    vdialog		*dialog,
    vchar		*message
    );

vnotice *vmdrawConfirmation(
    vdialog		*dialog,
    vchar		*message,
    vnoticeHookProc	okHook,
    vnoticeHookProc	noHook
    );

const vname *vmdrawModalConfirmation(
    vdialog	*dialog,
    vchar	*message
    );

void vmdrawCenterWindow(
    vwindow		*window
    );

void vmdrawReplaceStrings(
    vstr 		**strPtr, 
    vscribe 		*s1, 
    vscribe 		*s2
    );

void vmdrawOpenColorChooser(void);

void vmdrawOpenStyleChooser(void);

vdialog *vmdrawLoadDialog(
    const vname 	*tag
    );

vcommandSpace *vmdrawLoadSpace(
    const vname 	*tag
    );

void vmdrawSetDrawingSize(
    vmdrawDocument 	*data
    );

void vmdrawSetGrid(
    vmdrawDocument 	*data
    );

void vmdrawSetTargetDocument(
    vmdrawDocument	*data
    );

vbool vmdrawCloseAllDocuments();

void vmdrawStartup(void);

void vmdrawShutdown(void);

vbool vmdrawCloseAllDocuments(void);

/* canvas.c */

vdomain *vmdrawCreateDomain(void);

void vmdrawCanvasStartup(void);

/* document.c */

vmdrawDocument *vmdrawNewDocument(void);

void vmdrawOpenDocument(
    vfsPath		*path
    );

void vmdrawDestroyDocument(
    vmdrawDocument	*data
    );

void vmdrawOpenDocument(
    vfsPath		*path
    );

vbool vmdrawSaveDocument(
    vmdrawDocument	*data,
    vdict		*context
    );

vbool vmdrawIsDocumentValid(
    vmdrawDocument	*data
    );

void vmdrawChangeDocumentState(
    vmdrawDocument      *data,
    const vname		*name,
    const vname		*value
    );

void vmdrawCreatePositionWindow(void);

void vmdrawBuildWindowMenus(void);

void vmdrawDocumentStartup(void);

void vmdrawDocumentShutdown(void);

/* object.c */

vmdrawObjectData *vmdrawCreateObjectData(
    vdomain		*domain,
    vdomainObject	*object
    );

#if (mdrawUSE_DAS)
vdomainObject *vmdrawAddObject(
    vmdrawDocument	*data,
    vrect		*baseRect,
    int		         type,
    unsigned int	 id
    );
#else
vdomainObject *vmdrawAddObject(
    vmdrawDocument	*data,
    vrect		*baseRect,
    int		         type
    );
#endif /* mdrawUSE_DAS */

void vmdrawDrawObjectWith(
    vdomainview		*domainView,
    vdomainObject	*object,
    vdrawcontext	*context
    );

void vmdrawSelectObjectJointsWith(
    vdomainview		*domainView,
    vdomainObject	*object,
    vdrawcontext	*context
    );

vbool vmdrawRectIntersect(
    vdomain		*domain,
    vdomainObject	*object,
    vrect		*r
    );

void vmdrawRecalcLayering(
    vmdrawDocument	*data
    );

/* pen.c */

void vmdrawCreatePenWindow(void);

void vmdrawUsePen(
    vmdrawPen		*pen
    );

vmdrawPen *vmdrawLoadPens(
    vresource		resource,
    int			*penCount
    );

void vmdrawLoadPen(
    vresource           resource,
    vmdrawPen           *pen
    );

void vmdrawSavePens(
    vresource		resource,
    vmdrawPen		*pens,
    int			count
    );

void vmdrawStorePen(
    vresource		resource,
    vmdrawPen		*pen
    );

void vmdrawCopyPen(
    vmdrawPen		*pattern,
    vmdrawPen		*target
    );

void vmdrawDestroyPen(
    vmdrawPen		*pen
    );

void vmdrawSetPen(
    vmdrawPen		*pen,
    float		scale,
    vdrawcontext	*context
    );

void vmdrawPushPopPen(
    vbool                push, 
    vdrawcontext	*context
    );

void vmdrawDrawLine(
    int          x,
    int          y,
    int          tox,
    int          toy,
    int          arrows,
    vdrawcontext *context
    );

void vmdrawPenStartup(void);

/* pattern.c */

void vmdrawCreatePatternWindow(void);

vmdrawPattern *vmdrawLoadPatterns(
    vresource		resource,
    int			*patternCount
    );

void vmdrawLoadPattern(
    vresource           resource,
    vmdrawPattern       *pattern
    );

void vmdrawSavePatterns(
    vresource		resource,
    vmdrawPattern	*patterns,
    int			count
    );

void vmdrawStorePattern(
    vresource		resource,
    vmdrawPattern	*pattern
    );

void vmdrawCopyPattern(
    vmdrawPattern	*pattern,
    vmdrawPattern	*target
    );

void vmdrawCopyInitPattern(
    vmdrawPattern	*pattern,
    vmdrawPattern	*target
    );

void vmdrawDestroyPattern(
    vmdrawPattern	*pattern
    );

void vmdrawPatternFillRect(
    vmdrawPattern	*pattern,
    const vrect		*r,
    vdrawcontext	*context
    );

vimage *vmdrawCreatePatternImage(void);

void vmdrawPatternStartup(void);

/* preferences.c */

void vmdrawLoadTemplate(
    vresource				res,
    vmdrawTemplatePreferenceData	*prefs
    );

void vmdrawStoreTemplate(
    vresource				res,
    vmdrawTemplatePreferenceData	*prefs
    );

void vmdrawPreferencesStartup(void);

void vmdrawPreferencesShutdown(void);

/* text.c */

void vmdrawCreateTextObject(
    vmdrawObjectData	*objectData
    );

vtextview *vmdrawCreateFloatTextView(void);

void vmdrawPositionEditTextView(
    vmdrawDocument 	        *data,
    vdomainObject               *object
    );

void vmdrawEnableEditing(
    vmdrawDocument 	        *data,
    vdomainObject               *object
    );

void vmdrawDisableEditing(
    vmdrawDocument 	        *data,
    vbool			adjustPalette
    );

int vmdrawApplyStyle(
    vstylechsr   *styleChsrer, 
    vtextStyle   *newStyle
    );

void vmdrawApplyJustification(
    const vname		*name
    );

void vmdrawTextStartup(void);

#if (mdrawUSE_DAS)
void  mdrawOpenServiceChooser(void);
void mdrawUnregisterDocument(vmdrawDocument *document);
void mdrawRegisterDocument(vmdrawDocument *document);
#endif /* mdrawUSE_DAS */

#if (mdrawUSE_DAS)
int  vmdrawDocumentIsConsumer(
	vmdrawDocument *document
	);
#define  vmdrawDocumentIsConsumer(_doc)			\
    (((_doc)->service == NULL) && ((_doc)->session != NULL))
#endif /* mdrawUSE_DAS */


#if (mdrawUSE_DAS)
void vmdrawInvalObjects(vmdrawDocument *, vdomainObjectSet *);
#else
#define  vmdrawInvalObjects(doc, set)				  \
    vdomainviewInvalObjects((doc)->domainView, set, 0);

#endif /* mdrawUSE_DAS */


/*
 * * * * * * * * * FUNCTIONS IMPLEMENTED AS MACROS * * * * * * * *
 */

#define vmdrawDestroyDocument(d)	vwindowDestroyLater((vwindow *) (d))

/*
 * Global Variables
 */

extern vmdrawDocument		    *vmdrawDocumentList;
extern vmdrawDocument		    *vmdrawTargetDocument;
extern const vchar 		   *_vmdrawPredefs[];
extern vresource		     vmdrawResFile;
extern vresource		     vmdrawUserPrefFile;
extern vdialog			    *vmdrawPenWindow;
extern vdialog			    *vmdrawPatternWindow;
extern vdialog			    *vmdrawPositionWindow;
extern vfilechsr		    *vmdrawOpenWindow;
extern vfilechsr		    *vmdrawSaveWindow;
extern vcolorchsr                   *vmdrawColorChooser;
extern vstylechsr		    *vmdrawStyleChooser;
extern vdialog			    *wrtDialog;
extern vmdrawPen                    *vmdrawPens;
extern vmdrawPen                     vmdrawCurrentPen;
extern int			     vmdrawPenCount;
extern vmdrawPattern                *vmdrawPatterns;
extern vmdrawPattern                 vmdrawCurrentPattern;
extern int			     vmdrawPatternCount;
extern vcolor			    *vmdrawLockedColor;
extern vresource	             vmdrawMessages;
extern vpoint			     vmdrawCurrentPosition;
extern vdialogItem		    *vmdrawPositionItem;
extern vcolorPalette		    *vmdrawPalette;
extern vcolor                       *vmdrawEdgeColor;
extern vdomainviewEventClass	    *vmdrawDefaultEventClass;
extern vcursor			    *vmdrawGoodDropCursor;
extern vcursor			    *vmdrawBadDropCursor;

extern vmdrawPreferenceData          vmdrawPreferences;
extern vmdrawTemplatePreferenceData  vmdrawTemplatePreferences;

#endif

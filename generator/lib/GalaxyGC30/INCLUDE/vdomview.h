/* $Id: vdomview.h,v 1.90 1997/10/17 22:34:05 gregt Exp $ */

/************************************************************

    domainview.h
    C Interface file for Domain Views

    (c) Copyright Visix Software Inc.
    All rights reserved

************************************************************/

#ifndef  vdomainviewINCLUDED
#define  vdomainviewINCLUDED 1

#ifndef  vportINCLUDED		/* for v*HEADER */
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

#ifndef  vkeyINCLUDED
#include vkeyHEADER
#endif

#ifndef  veventINCLUDED
#include veventHEADER
#endif

#ifndef  vresourceINCLUDED
#include vresourceHEADER
#endif

#ifndef  vclassINCLUDED
#include vclassHEADER
#endif

#ifndef  vloadableINCLUDED
#include vloadableHEADER
#endif

#ifndef  vobjectINCLUDED
#include vobjectHEADER
#endif

#ifndef  vundoINCLUDED
#include vundoHEADER
#endif

#ifndef  vimageINCLUDED
#include vimageHEADER
#endif

#ifndef  vdomainINCLUDED
#include vdomainHEADER
#endif

#ifndef  vdialogINCLUDED
#include vdialogHEADER
#endif

#ifndef  vcontrolINCLUDED
#include vcontrolHEADER
#endif

#ifndef  vsliderINCLUDED
#include vsliderHEADER
#endif

#ifndef  vdomainviewINCLUDED
#include vdomainviewHEADER
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C


/*
 * * * * * * * * * * PUBLIC CONSTANT DEFINITIONS * * * * * * * * * *
 */

enum {
    vdomainviewID_ATTRIBUTE_MATRIX	= vdialogITEM_NEXT_ID_ATTRIBUTE,
    vdomainviewID_ATTRIBUTE_DRAG_SNAP_MODE,
    vdomainviewNEXT_ID_ATTRIBUTE
};

/* Domain view command selector values */

enum {
    vdomainviewSELECT_MOVE_FOCUS        = vdialogITEM_NEXT_SELECT,
    vdomainviewSELECT_SELECT_ALL,
    vdomainviewSELECT_DUPLICATE,
    vdomainviewSELECT_DISPLAY_SELECTION,
    vdomainviewSELECT_OBJECT,
    vdomainviewSELECT_MOVE,
    vdomainviewSELECT_ALIGN,
    vdomainviewSELECT_DISTRIBUTE,
    vdomainviewNEXT_SELECT
};

/* Values for DRAG_OUTLINE attribute */

enum {
    vdomainviewOUTLINE_ALL		= 1,
    vdomainviewOUTLINE_TWO		= 2,
    vdomainviewOUTLINE_LIMITRECT	= 3,
    vdomainviewOUTLINE_NONE     	= 4
};

/* Values for DRAG_METHOD attribute */

enum {
    vdomainviewDRAG_AUTOSCROLL	= 0,
    vdomainviewDRAG_NORMAL	= 1,
    vdomainviewEXTERNAL_DRAG	= 2
};

/*
 * Values for TRACK_MODE attribute
 */

enum {
    vdomainviewTRACK_NONE		= 0x00,
    vdomainviewTRACK_SELECT		= 0x01,
    vdomainviewTRACK_DRAG 		= 0x02
};

/*
 * Values for 'direction' paramter to vdomainviewTranslatePoint()
 */

enum {
    vdomainviewTO_DIALOG		= 0,	/* deprecated */
    vdomainviewTO_DOMAIN		= 1,	/* deprecated */
    vdomainviewDOMAIN_TO_DIALOG		= 0,
    vdomainviewDIALOG_TO_DOMAIN		= 1,
    vdomainviewDOMAIN_TO_USER		= 2,
    vdomainviewUSER_TO_DOMAIN		= 3
};

/* Values for 'state' field for Track Event */

enum {
    vdomainviewTRACK_START		= 1,
    vdomainviewTRACK_MOVE_DRAW		= 2,
    vdomainviewTRACK_MOVE_UNDRAW	= 3,
    vdomainviewTRACK_END		= 4,
    vdomainviewTRACK_UPDATE		= 5
};

/* Values for DRAG_SNAP_MODE attribute */

enum {
    vdomainviewSNAP_OFF			= 0,
    vdomainviewSNAP_NO_ALIGN		= 1,
    vdomainviewSNAP_ALIGN_ONE		= 2,
    vdomainviewSNAP_ALIGN_LIMIT		= 3
};

#define vdomainview_Option          (_vdomainviewPredefs[_vdomainview_Option])
#define vdomainview_Top             (_vdomainviewPredefs[_vdomainview_Top])
#define vdomainview_ScrollIncrement (_vdomainviewPredefs[_vdomainview_ScrollIncrement])
#define vdomainview_ScrollBarMargin (_vdomainviewPredefs[_vdomainview_ScrollBarMargin])
#define vdomainview_TrackMode       (_vdomainviewPredefs[_vdomainview_TrackMode])
#define vdomainview_Front           (_vdomainviewPredefs[_vdomainview_Front])
#define vdomainview_Back            (_vdomainviewPredefs[_vdomainview_Back])
#define vdomainview_Forward         (_vdomainviewPredefs[_vdomainview_Forward])
#define vdomainview_Backward        (_vdomainviewPredefs[_vdomainview_Backward])
#define vdomainview_Vertical        (_vdomainviewPredefs[_vdomainview_Vertical])
#define vdomainview_Horizontal      (_vdomainviewPredefs[_vdomainview_Horizontal])
#define vdomainview_Matrix	    (_vdomainviewPredefs[_vdomainview_Matrix])
#define vdomainview_DragSnapMode    (_vdomainviewPredefs[_vdomainview_DragSnapMode])


/*
 * * * * * * * * * * PUBLIC TYPE DEFINITIONS * * * * * * * * * *
 */

typedef struct vdomainview		vdomainview;
typedef struct vdomainviewClass		vdomainviewClass;
typedef vdomainObserver			vdomainviewDomainObserver;
typedef struct vdomainviewEventClass	vdomainviewEventClass;
typedef vsliderScrollBar		vdomainviewScrollBar;
typedef vsliderScrollBarClass		vdomainviewScrollBarClass;

typedef void (*vdomainviewDrawObjectProc)(
    vdomainview 		*domainView,
    vdomainObject 		*object
    );

typedef void (*vdomainviewDrawObjectWithProc)(
    vdomainview 		*domainView,
    vdomainObject 		*object,
    vdrawcontext		*context
    );

typedef void (*vdomainviewDrawSelectionProc)(
    vdomainview 		*domainView,
    vdomainObject 		*object
    );

typedef void (*vdomainviewDrawSelectionWithProc)(
    vdomainview 		*domainView,
    vdomainObject 		*object,
    vdrawcontext		*context
    );

typedef void (*vdomainviewUndoNoteProc)(
    vdomainview 		*domainView,
    vundoAction			*action
    );

/*
 * Domain View Events
 */

typedef struct vdomainviewDblClickEvent {
    vevent			*event;
    vdomainObject		*dblClickObject;
    vpoint			position;
    vpointLong			longPosition;
} vdomainviewDblClickEvent;

typedef struct vdomainviewMoveEvent {
    vevent			*event;
    vdomainObjectSet		*movingObjects;
    vpoint			position;
    vpointLong			longPosition;
    vbool			positionIsAbsolute;
} vdomainviewMoveEvent;

typedef struct vdomainviewSelectEvent {
    vevent                      *event;
    vdomainObject               *object;
    vbool                       selected;
} vdomainviewSelectEvent;

typedef struct vdomainviewSelectAllEvent {
    vbool			beforeSelecting;
    vbool			selected;
    int				numSelected;
} vdomainviewSelectAllEvent;

typedef struct vdomainviewButtonUpEvent {
    vevent			*event;
    vpoint			position;
    vpointLong			longPosition;
} vdomainviewButtonUpEvent;

typedef struct vdomainviewButtonDownEvent {
    vevent			*event;
    vdomainObject		*clickedOnObject;
    vpoint			position;
    vpointLong			longPosition;
} vdomainviewButtonDownEvent;

typedef struct vdomainviewResizeEvent {
    vevent			*event;
    vrect			oldBounds;
    vrectLong			oldLongBounds;
} vdomainviewResizeEvent;

typedef struct vdomainviewScrollEvent {
    vevent			*event;
    vpoint			oldScrollPosition;
    vpointLong			longOldScrollPosition;
    vpointLong			oldScrollTranslation;
} vdomainviewScrollEvent;

typedef struct vdomainviewTrackEvent {
    vevent			*event;
    short			state;
    short			pad;  /** DEC's c89 compiler needs this */
    vpoint			originalPosition;
    vpoint			currentPosition;
    vpointLong			longOriginalPosition;
    vpointLong			longCurrentPosition;
    
    vdomainObjectSet		*dragObjects;
    vdialog			*overDialog;
    vpoint			overDialogPosition;

    vdrawcontext		*context;
} vdomainviewTrackEvent;

typedef struct vdomainviewKeyEvent {
    vevent			*event;
    vkeyStroke			keystroke;
    vchar			ch;
} vdomainviewKeyEvent;

typedef struct vdomainviewResizeObjectEvent {
    vevent			*event;
    vdomainObjectSet     	*resizedObjects;
    vbool			before;
} vdomainviewResizeObjectEvent;


/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */

void vdomainviewStartup(void);

/* Domain Class Functions */

vdomainviewClass *vdomainviewGetDefaultClass(void);

vdomainObserverClass *vdomainviewGetDefaultObserverClass(void);

vdomainviewEventClass *vdomainviewGetDefaultEventClass(void);

vdomainviewScrollBarClass *vdomainviewGetDefaultScrollBarClass(void);

/* Initialization and allocation */

vdomainview *vdomainviewCreate(void);

vdomainview *vdomainviewCreateOfClass(
    vdomainviewClass	*clas
    );
    
vdomainview *vdomainviewClone(
    vdomainview	    	*domainView
    );

void vdomainviewCopy(
    vdomainview	    	*domainView,
    vdomainview	    	*targetDomain
    );

void vdomainviewCopyInit(
    vdomainview	    	*domainView,
    vdomainview	    	*targetDomain
    );

void vdomainviewInit(
    vdomainview	    	*domainView
    );

void vdomainviewInitOfClass(
    vdomainview		*domainView,
    vdomainviewClass	*clas
    );

void vdomainviewDestroy(
    vdomainview	    	*domainView
    );

vdomainview *vdomainviewLoad(
    vresource           resource
    );

void vdomainviewLoadInit(
    vdomainview         *domainView,
    vresource           resource
    );

void vdomainviewStore(
    vdomainview         *domainView,
    vresource           resource
    );

/* Domain Operations */

void vdomainviewDraw(
    vdomainview		*domainView
    );

void vdomainviewScroll(
    vdomainview		*domainView,
    int 		xPos,
    int 		yPos,
    int 		positioning
    );

void vdomainviewSetScrollTranslation(
    vdomainview		*domainView,
    int			xPos,
    int			yPos,
    int			positioning
    );

void vdomainviewScrollToObject(
    vdomainview		*domainView,
    vdomainObject	*object,
    int 	 	minimumLeft,
    int 		minimumTop,
    int 		minimumRight,
    int 		minimumBottom,
    int 		doScroll,
    short		*scrollX,
    short		*scrollY
    );

void vdomainviewInval(
    vdomainview		*domainView
    );
    
void vdomainviewInvalRect(
    vdomainview		*domainView,
    vrect		*r,
    int			flags
    );

vbool vdomainviewIsObjectInView(
    vdomainview		*domainView,
    vdomainObject	*object
    );

vpoint *vdomainviewGetScrollOffset(
    vdomainview		*domainView
    );

vpointLong *vdomainviewGetScrollOffsetLong(
    vdomainview		*domainView
    );

vpointLong *vdomainviewGetScrollTranslation(
    vdomainview		*domainView
    );

vrect *vdomainviewGetViewArea(
    vdomainview		*domainView
    );

vrectLong *vdomainviewGetViewAreaLong(
    vdomainview		*domainView
    );

vrectLong *vdomainviewGetViewableArea(
    vdomainview		*domainView
    );

vrect *vdomainviewGetDomainRect(
    vdomainview		*domainView
    );

void vdomainviewInvalObjects(
    vdomainview		*domainView,
    vdomainObjectSet	*objectSet,
    int			flags
    );

short vdomainviewSelectedObjects(
    vdomainview		*domainView
    );

void vdomainviewTranslatePoint(
    vdomainview		*domainView,
    vpoint		*pt,
    int			direction
    );

void vdomainviewTranslatePointLong(
    vdomainview		*domainView,
    vpointLong		*pt,
    int			direction
    );

void vdomainviewTranslateRect(
    vdomainview		*domainView,
    vrect		*r,
    int			direction
    );

void vdomainviewTranslateRectLong(
    vdomainview		*domainView,
    vrectLong		*r,
    int			direction
    );

/* Domain View attribute modification */

void vdomainviewSetData(
    vdomainview		*domainView,
    void		*data
    );

void vdomainviewSetDomain(
    vdomainview	    	*domainView,
    vdomain		*domain
    );

void vdomainviewSetSelection(
    vdomainview		*domainView,
    vdomainSelection	selection
    );
    
void vdomainviewSetObserver(
    vdomainview			*domainView,
    vdomainObserverClass	*observerClass
    );
    
void vdomainviewSetEventClass(
    vdomainview		*domainView,
    vdomainviewEventClass	*eventClass
    );
    
void vdomainviewSetDrawObjectProc(
    vdomainview			*domainView,
    vdomainviewDrawObjectProc	drawProc
    );

void vdomainviewSetDrawObjectWithProc(
    vdomainview				*domainView,
    vdomainviewDrawObjectWithProc	 drawWithProc
    );

void vdomainviewSetDrawSelectionProc(
    vdomainview			 *domainView,
    vdomainviewDrawSelectionProc drawProc
    );

void vdomainviewSetDrawSelectionWithProc(
    vdomainview				 *domainView,
    vdomainviewDrawSelectionWithProc	 drawWithProc
    );

void vdomainviewSetUndoNotify(
    vdomainview			 *domainView,
    vdomainviewUndoNoteProc 	 undoNotifyProc
    );

void vdomainviewSetMatrix(
    vdomainview		*domainView,
    const vmatrix	*matrix
    );

void vdomainviewSetHorzBar( 
    vdomainview		*domainView,
    int 		hasBar
    );
    
void vdomainviewSetVertBar( 
    vdomainview		*domainView,
    int 		hasBar
    );
    
void vdomainviewSetHorzLocked(
    vdomainview		*domainView,
    int 		scrollable
    );
    
void vdomainviewSetVertLocked(
    vdomainview		*domainView,
    int 		scrollable
    );
    
void vdomainviewSetGrabbingHand( 
    vdomainview		*domainView,
    int 		grabWithHand
    );
    
void vdomainviewSetAutoScroll(
    vdomainview		*domainView,
    int 		autoScroll
    );

void vdomainviewSetSelectEnclosed(
    vdomainview		*domainView,
    int 		enclosed
    );

void vdomainviewSetSingleSelection(
    vdomainview		*domainView,
    int 		singleSelect
    );

void vdomainviewSetLiveSelection(
    vdomainview		*domainView,
    int 		liveSelection
    );

void vdomainviewSetTrackMode(
    vdomainview		*domainView,
    int 		trackMode
    );

void vdomainviewSetSelectAllEvents(
    vdomainview		*domainView,
    int 		selectAllEvents
    );

void vdomainviewSetDragOutline(
    vdomainview		*domainView,
    int 		dragOutline
    );

void vdomainviewSetDragProhibited(
    vdomainview		*domainView,
    int 		dragProhibited
    );

void vdomainviewSetDragSnapMode(
    vdomainview		*domainView,
    int 		dragSnapMode
    );

void vdomainviewSetOffscreenDrawing(
    vdomainview		*domainView,
    int 		useOffscreenDrawing
    );
    
void vdomainviewSetDragMethod(
    vdomainview		*domainView,
    int 		dragMethod
    );

void vdomainviewSetDragThreshold(
    vdomainview		*domainView,
    int 		dragThreshold
    );
    
void vdomainviewSetScrollBarMargin(
    vdomainview		*domainView,
    int 		scrollBarMargin
    );

void vdomainviewSetScrollIncrement(
    vdomainview		*domainView,
    int 		scrollIncrement
    );
    
/* Domain View attribute access */

vdomainviewClass *vdomainviewGetClass(
    vdomainview		*domainView
    );

void *vdomainviewGetData(
    vdomainview		*domainView
    );

vdomain *vdomainviewGetDomain(
    vdomainview	    	*domainView
    );

vdomainSelection vdomainviewGetSelection(
    vdomainview		*domainView
    );
    
vdomainObserverClass *vdomainviewGetObserver(
    vdomainview			*domainView
    );
    
vdomainviewEventClass *vdomainviewGetEventClass( 
    vdomainview		*domainView
    );

vdomainviewDrawObjectProc vdomainviewGetDrawObjectProc(
    vdomainview		*domainView
    );

vdomainviewDrawObjectWithProc vdomainviewGetDrawObjectWithProc(
    vdomainview		*domainView
    );

vdomainviewDrawSelectionProc vdomainviewGetDrawSelectionProc(
    vdomainview		*domainView
    );

vdomainviewDrawSelectionWithProc vdomainviewGetDrawSelectionWithProc(
    vdomainview		*domainView
    );

vdomainviewUndoNoteProc vdomainviewGetUndoNotify(
    vdomainview		*domainView
    );

const vmatrix *vdomainviewGetMatrix(
    vdomainview		*domainView
    );

vbool vdomainviewHasHorzBar( 
    vdomainview		*domainView
    );
    
vbool vdomainviewHasVertBar( 
    vdomainview		*domainView
    );
   
vcontrol *vdomainviewGetHorzScrollbar(
    vdomainview		*domainView 
    );

vcontrol *vdomainviewGetVertScrollbar(
    vdomainview		*domainView
    );
   
vbool vdomainviewIsHorzLocked(
    vdomainview		*domainView
    );

vbool vdomainviewIsVertLocked(
    vdomainview		*domainView
  );
 
vbool vdomainviewHasGrabbingHand(
    vdomainview		*domainView
    );
    
vbool vdomainviewIsAutoScroll(
    vdomainview		*domainView
    );

vbool vdomainviewIsSelectEnclosed(
    vdomainview		*domainView
    );

vbool vdomainviewIsSingleSelection(
    vdomainview		*domainView
    );

vbool vdomainviewIsLiveSelection(
    vdomainview		*domainView
    );

vbyte vdomainviewGetTrackMode(
    vdomainview		*domainView
    );

vbyte vdomainviewGetDragSnapMode(
    vdomainview		*domainView
    );

vbool vdomainviewHasSelectAllEvents(
    vdomainview		*domainView
    );

vbyte vdomainviewGetDragOutline(
    vdomainview		*domainView
    );

vbool vdomainviewIsDragProhibited(
    vdomainview		*domainView
    );

vbool vdomainviewIsOffscreenDrawing(
    vdomainview		*domainView
    );

vbyte vdomainviewGetDragMethod(
    vdomainview		*domainView
    );

short vdomainviewGetDragThreshold(
    vdomainview		*domainView
    );

short vdomainviewGetScrollBarMargin(
    vdomainview		*domainView
    );

short vdomainviewGetScrollIncrement(
    vdomainview		*domainView
    );

/* Other Routines */

vdialogItem *vdomainviewGetItem(
    vdomainview		*domainView
    );

vobject *vdomainviewGetObject(
    vdomainview		*domainView
    );

vloadable *vdomainviewGetLoadable(
    vdomainview		*domainView
    );

vdomainObserver *vdomainviewObserver(
    vdomainview			*domainView
    );
    
void vdomainviewNotifyUndo(
    vdomainview		*domainView,
    vscribe		*actionName
    );

/* Deprecated Routines */

vdomainObserverClass *vdomainviewGetObserverClass(vdomainview *domainView);
void  vdomainviewSetObserverClass(vdomainview *domainView, 
				  vdomainObserverClass *clas);
void vdomainviewSetDragSnapToGrid(vdomainview *domainView, int snapToGrid);
vbool vdomainviewIsDragSnapToGrid(vdomainview *domainView);
#if !(vportBAD_CC_SCOPING)
short vdomainviewGetScrollbarMargin(vdomainview *domainView);
void  vdomainviewSetScrollbarMargin(vdomainview *domainView,
				    int scrollBarMargin);
#endif


/*
 * * * * * * * * * * PRIVATE CONSTANT DEFINITIONS * * * * * * * * * *
 */

/* Values for 'attributes' field in the vdomainview structure */

enum {
    _vdomainviewAUTO_SCROLL		=  0x0001,
    _vdomainviewSELECT_ENCLOSED		=  0x0002,
    _vdomainviewSINGLE_SELECTION	=  0x0004,
    _vdomainviewLIVE_SELECTION		=  0x0008,
    _vdomainviewSELECTALL_EVENTS	=  0x0010,
    _vdomainviewDRAG_PROHIBITED		=  0x0020,
    _vdomainviewDRAG_SNAPTOGRID		=  0x0040,	/* backward compat */
    _vdomainviewALIGN_TO_GRID		=  0x0080,
    _vdomainviewHORZ_LOCKED		=  0x0200,
    _vdomainviewVERT_LOCKED		=  0x0400,
    _vdomainviewGRABBING_HAND		=  0x0800,
    _vdomainviewTRACKING		=  0x1000,
    _vdomainviewOFFSCREEN_DRAWING   	=  0x2000,
    _vdomainviewHAS_HORZ_BAR		=  0x4000,
    _vdomainviewHAS_VERT_BAR		=  0x8000,
    _vdomainviewSCROLLBAR_MARGIN_SET	= 0x10000,
    _vdomainviewOLD_OBSERVER_CLASS	= 0x20000
};

/*
 * Global text view strings
 */

enum {
    _vdomainview_Option,
    _vdomainview_Top,
    _vdomainview_ScrollIncrement,
    _vdomainview_ScrollBarMargin,
    _vdomainview_TrackMode,
    _vdomainview_Forward,
    _vdomainview_Backward,
    _vdomainview_Front,
    _vdomainview_Back,
    _vdomainview_Vertical,
    _vdomainview_Horizontal,
    _vdomainview_Matrix,
    _vdomainview_DragSnapMode,
    _vdomainview_Count
};


/*
 * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * *
 */

typedef struct _vdomainviewTrackData	_vdomainviewTrackData;

typedef struct _vdomainviewShortInfo {
    vrect		 	viewRect;
    vpoint		 	translation;
} _vdomainviewShortInfo;

typedef struct _vdomainviewLongInfo {
    vrectLong		viewRect;
    vpointLong		translation;
} _vdomainviewLongInfo;

struct vdomainview {
    vdialogItem		 	item;
    vdomain			*domain;

    union {
	_vdomainviewShortInfo	info;
	_vdomainviewLongInfo	longInfo;
    } u;

    vrect			viewDialogRect;
    vmatrix			matrix;
    const vmatrix		*userMatrix;
    vbool			translationDirty;
    vrectLong			viewableArea;
    vpointLong			translation;

    vcontrol			*hBar;
    vcontrol			*vBar;
    vdialogItem			*focusItem;
    vdomainviewEventClass	*eventClass;
    vimage  	    	    	*offscreenBuffer;

    unsigned long	 	attributes;
    vbyte		 	dragOutline;
    vbyte			dragMethod;
    vbyte			trackMode;
    vbyte			dragSnapMode;
    vbyte			longDomain;
    short		 	scrollBarMargin;
    short		 	scrollIncrement;
    short			dragThreshold;
    double			lineWidthX, lineWidthY;

    vdomainSelection		selection;
    vdomainObserver       	*observer;
    vdomainObserverClass  	*observerClass;

    vdomainviewDrawObjectProc	 drawProc;
    vdomainviewDrawObjectWithProc drawWithProc;
    vdomainviewDrawSelectionProc selectionProc;
    vdomainviewDrawSelectionWithProc selectionWithProc;
    vdomainviewUndoNoteProc	 undoNotifyProc;

    vdomainObjectSet		*visibleObjects;
    _vdomainviewTrackData	*trackData;
    vevent			*scrollEvent;
};

/*
 * Domain View Class
 */

#define vdomainviewCLASS(SUPER, ITEM, NOTIFY, DOMAIN)			      \
    vdialogITEM_CLASS(SUPER, ITEM, NOTIFY);				      \
    vclassVARIABLE(vdomainviewBORDER_INSET,  short);			      \
    vclassMETHOD_RET(vdomainviewCREATE_SCROLL_BAR, vsliderScrollBar *,	      \
		     (ITEM *domainView));				      \
    vclassMETHOD(vdomainviewSET_HORZ_BAR,  (ITEM *domainView, int hasBar));   \
    vclassMETHOD(vdomainviewSET_VERT_BAR,  (ITEM *domainView, int hasBar));   \
    vclassMETHOD(vdomainviewBACKGROUND,    (ITEM *domainView));	    	      \
    vclassMETHOD(vdomainviewDRAW_CONTENT_BACKGROUND_WITH,		      \
					   (ITEM *domainView,		      \
					    vdrawcontext *context));	      \
    vclassMETHOD(vdomainviewDRAW_MARQUEE,  (ITEM *domainView, vrect *rect));  \
    vclassMETHOD(vdomainviewDRAW_MARQUEE_WITH,				      \
					   (ITEM *domainView, vrect *rect,    \
					    vdrawcontext *context));	      \
    vclassMETHOD(vdomainviewDRAW_MARQUEE_LONG,				      \
					   (ITEM *domainView,		      \
					    vrectLong *rect));		      \
    vclassMETHOD(vdomainviewDRAW_MARQUEE_LONG_WITH,			      \
					   (ITEM *domainView,		      \
					    vrectLong *rect,		      \
					    vdrawcontext *context));	      \
    vclassMETHOD(vdomainviewDRAG_OUTLINE,  (ITEM *domainView, vrect *rects,   \
					    int numRects, vrect *limitRect,   \
					    vpoint *pinAmount));	      \
    vclassMETHOD(vdomainviewDRAG_OUTLINE_WITH,				      \
					   (ITEM *domainView, vrect *rects,   \
					    int numRects, vrect *limitRect,   \
					    vpoint *pinAmount,		      \
					    vdrawcontext *context));	      \
    vclassMETHOD(vdomainviewDRAG_OUTLINE_LONG,				      \
		                           (ITEM *domainView,		      \
					    vrectLong *rects,  int numRects,  \
					    vrectLong *limitRect,	      \
					    vpoint *pinAmount));	      \
    vclassMETHOD(vdomainviewDRAG_OUTLINE_LONG_WITH,			      \
		                           (ITEM *domainView,		      \
					    vrectLong *rects,  int numRects,  \
					    vrectLong *limitRect,	      \
					    vpoint *pinAmount,		      \
					    vdrawcontext *context));	      \
    vclassMETHOD(vdomainviewSET_DOMAIN,	   (ITEM *domainView,DOMAIN *domain));\
    vclassMETHOD(vdomainviewSCROLL,	   (ITEM *domainView, int xPos,       \
					    int yPos, int positioning));      \
    vclassMETHOD(vdomainviewSET_SCROLL_TRANSLATION,			      \
					   (ITEM *domainView, int xPos,	      \
					    int yPos, int positioning));      \
    vclassMETHOD(vdomainviewDRAW_BORDER,   (ITEM *domainView,		      \
					    const vrect *border));	      \
    vclassMETHOD(vdomainviewDRAW_OBJECTS,  (ITEM *domainView));		      \
    vclassMETHOD(vdomainviewDRAW_OBJECTS_WITH,				      \
					   (ITEM *domainView,		      \
					    vdrawcontext *context));	      \
    vclassMETHOD(vdomainviewDRAW_OBJECT,				      \
		 (ITEM *domainView, vdomainObject *object));		      \
    vclassMETHOD(vdomainviewDRAW_OBJECT_WITH,				      \
		 (ITEM *domainView, vdomainObject *object,		      \
		  vdrawcontext *context));				      \
    vclassMETHOD(vdomainviewDRAW_SELECTION,				      \
		 (ITEM *domainView, vdomainObject *object));		      \
    vclassMETHOD(vdomainviewDRAW_SELECTION_WITH,			      \
		 (ITEM *domainView, vdomainObject *object,		      \
		  vdrawcontext *context));				      \
    vclassMETHOD_RET(vdomainviewHANDLE_SCROLL_EVENT, vbool,		      \
		     (ITEM *domainView, vdomainviewScrollEvent *event));      \
    vclassMETHOD_RET(vdomainviewHANDLE_TRACK_EVENT, vbool,		      \
		     (ITEM *domainView, vdomainviewTrackEvent *event));	      \
    vclassMETHOD_RET(vdomainviewHANDLE_BUTTON_UP_EVENT, vbool,		      \
		     (ITEM *domainView, vdomainviewButtonUpEvent *event));    \
    vclassMETHOD_RET(vdomainviewHANDLE_BUTTON_DOWN_EVENT, vbool,	      \
		     (ITEM *domainView, vdomainviewButtonDownEvent *event));  \
    vclassMETHOD_RET(vdomainviewHANDLE_DBL_CLICK_EVENT, vbool,		      \
		     (ITEM *domainView, vdomainviewDblClickEvent *event));    \
    vclassMETHOD_RET(vdomainviewHANDLE_KEY_EVENT, vbool,		      \
		     (ITEM *domainView, vdomainviewKeyEvent *event));	      \
    vclassMETHOD_RET(vdomainviewHANDLE_MOVE_EVENT, vbool,		      \
		     (ITEM *domainView, vdomainviewMoveEvent *event));	      \
    vclassMETHOD_RET(vdomainviewHANDLE_RESIZEOBJECT_EVENT, vbool,	      \
		     (ITEM *domainView, vdomainviewResizeObjectEvent *event));\
    vclassMETHOD_RET(vdomainviewHANDLE_SELECT_EVENT, vbool,		      \
		     (ITEM *domainView, vdomainviewSelectEvent *event));      \
    vclassMETHOD_RET(vdomainviewHANDLE_RESIZE_EVENT, vbool,		      \
		     (ITEM *domainView, vdomainviewResizeEvent *event));      \
    vclassMETHOD_RET(vdomainviewHANDLE_SELECTALL_EVENT, vbool,		      \
		     (ITEM *domainView, vdomainviewSelectAllEvent *event))    \

struct vdomainviewClass {
    vdomainviewCLASS(vdomainviewClass, vdomainview, vdialogItemNoteProc,
		     vdomain);
};

vportALIAS(vdomainviewDomainObserver, vdomainObserver)
vportALIAS(vdomainviewScrollBar, vsliderScrollBar)

/*
 * Domain View Event Class
 */

#define vdomainviewEventCLASS(SUPER, DOMAINVIEW)			      \
    vclassROOT(SUPER);               			   		      \
    vclassMETHOD_RET(vdomainviewDBL_CLICK_EVENT, vbool,			      \
	     (DOMAINVIEW *domainView, vdomainviewDblClickEvent *event));      \
    vclassMETHOD_RET(vdomainviewMOVE_EVENT, vbool,			      \
	     (DOMAINVIEW *domainView, vdomainviewMoveEvent *event));   	      \
    vclassMETHOD_RET(vdomainviewBUTTON_DOWN_EVENT, vbool,		      \
	     (DOMAINVIEW *domainView, vdomainviewButtonDownEvent *event));    \
    vclassMETHOD_RET(vdomainviewBUTTON_UP_EVENT, vbool,			      \
	     (DOMAINVIEW *domainView, vdomainviewButtonUpEvent *event));      \
    vclassMETHOD_RET(vdomainviewSELECT_EVENT, vbool,			      \
	     (DOMAINVIEW *domainView, vdomainviewSelectEvent *event)); 	      \
    vclassMETHOD_RET(vdomainviewSELECTALL_EVENT, vbool,			      \
	     (DOMAINVIEW *domainView, vdomainviewSelectAllEvent *event));     \
    vclassMETHOD_RET(vdomainviewRESIZE_EVENT, vbool,			      \
	     (DOMAINVIEW *domainView, vdomainviewResizeEvent *event));	      \
    vclassMETHOD_RET(vdomainviewSCROLL_EVENT, vbool,			      \
	     (DOMAINVIEW *domainView, vdomainviewScrollEvent *event));	      \
    vclassMETHOD_RET(vdomainviewTRACK_EVENT, vbool,			      \
	     (DOMAINVIEW *domainView, vdomainviewTrackEvent *event)); 	      \
    vclassMETHOD_RET(vdomainviewKEY_EVENT, vbool,			      \
	     (DOMAINVIEW *domainView, vdomainviewKeyEvent *event));	      \
    vclassMETHOD_RET(vdomainviewRESIZEOBJECT_EVENT, vbool,		      \
	     (DOMAINVIEW *domainView, vdomainviewResizeObjectEvent *event))
    			
struct vdomainviewEventClass {
    vdomainviewEventCLASS(vdomainviewEventClass, vdomainview);
};


/*
 * * * * * * * * * * * * PRIVATE GLOBAL VARIABLES * * * * * * * * * * * * *
 */

extern vportLINK const vchar 		*_vdomainviewPredefs[];


/*
 * * * * * * * * * * * * PRIVATE FUNCTION PROTOTYPES * * * * * * * * * * * * *
 */

void _vdomainviewSendDrawObject(
    vdomainview			*domainView,
    vdomainObject		*object
    );

void _vdomainviewSendDrawObjectWith(
    vdomainview			*domainView,
    vdomainObject		*object,
    vdrawcontext		*context
    );

void _vdomainviewSendDrawSelection(
    vdomainview			*domainView,
    vdomainObject		*object
    );

void _vdomainviewSendDrawSelectionWith(
    vdomainview			*domainView,
    vdomainObject		*object,
    vdrawcontext		*context
    );

vbool _vdomainviewSendScrollEvent(
    vdomainview			*domainView,
    vdomainviewScrollEvent	*event
    );

vbool _vdomainviewSendTrackEvent(
    vdomainview			*domainView,
    vdomainviewTrackEvent	*event
    );

vbool _vdomainviewSendButtonUpEvent(
    vdomainview			*domainView,
    vdomainviewButtonUpEvent	*event
    );

vbool _vdomainviewSendButtonDownEvent(
    vdomainview			*domainView,
    vdomainviewButtonDownEvent	*event
    );

vbool _vdomainviewSendDoubleClickEvent(
    vdomainview			*domainView,
    vdomainviewDblClickEvent	*event
    );

vbool _vdomainviewSendKeyEvent(
    vdomainview			*domainView,
    vdomainviewKeyEvent		*event
    );

vbool _vdomainviewSendMoveEvent(
    vdomainview			*domainView,
    vdomainviewMoveEvent	*event
    );

vbool _vdomainviewSendResizeObjectEvent(
    vdomainview				*domainView,
    vdomainviewResizeObjectEvent	*event
    );

vbool _vdomainviewSendSelectEvent(
    vdomainview			*domainView,
    vdomainviewSelectEvent	*event
    );

vbool _vdomainviewSendResizeEvent(
    vdomainview			*domainView,
    vdomainviewResizeEvent	*event
    );

vbool _vdomainviewSendSelectAllEvent(
    vdomainview			*domainView,
    vdomainviewSelectAllEvent	*event
    );

/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * *
 */

#define vdomainviewGetItem(d)		vportBASE_OBJECT(d, item)
#define vdomainviewGetObject(d)		\
	vdialogGetItemObject(vdomainviewGetItem(d))
#define vdomainviewGetLoadable(d)	\
	vdialogGetItemLoadable(vdomainviewGetItem(d))
 
#define vdomainviewCreateOfClass(c)	\
	((vdomainview *) vdialogCreateItemOfClass((vdialogItemClass *) (c)))
#define vdomainviewCreate()	       \
        vdomainviewCreateOfClass(vdomainviewGetDefaultClass())
#define vdomainviewInitOfClass(e,c)	\
	vdialogInitItemOfClass(vdomainviewGetItem(e), (vdialogItemClass *) (c))
#define vdomainviewInit(e)		\
	vdomainviewInitOfClass(e, vdomainviewGetDefaultClass())
#define vdomainviewDestroy(d)		\
	vdialogDestroyItem(vdomainviewGetItem(d))
#define vdomainviewClone(d)		\
	((vdomainview *) vloadableCloneOfSubclass(vdomainviewGetLoadable(d),  \
			      (vloadableClass *) vdomainviewGetDefaultClass()))
#define vdomainviewCopyInit(c,t)	\
	vloadableCopyInitOfSubclass(vdomainviewGetLoadable(c),		      \
				    vdomainviewGetLoadable(t),		      \
			       (vloadableClass *) vdomainviewGetDefaultClass())
#define vdomainviewCopy(c,t)	\
	vdialogCopyItem(vdomainviewGetItem(c), vdomainviewGetItem(t))
#define vdomainviewLoad(r)		\
	((vdomainview *) vloadableLoadOfSubclass(r,			      \
			      (vloadableClass *) vdomainviewGetDefaultClass()))
#define vdomainviewLoadInit(c,r)	\
	vloadableLoadInitOfSubclass(vdomainviewGetLoadable(c), r,	      \
			       (vloadableClass *) vdomainviewGetDefaultClass())
#define vdomainviewStore(d, r)	vdialogStoreItem(vdomainviewGetItem(d), (r))
#define vdomainviewSetData(v, d)	\
	vdialogSetItemData(vdomainviewGetItem(v), d)
#define vdomainviewDraw(d)		\
	vdialogDrawItem(vdomainviewGetItem(d))
#define vdomainviewGetViewArea(d)	(&(d)->u.info.viewRect)
#define vdomainviewGetViewAreaLong(d)	(&(d)->u.longInfo.viewRect)
#define vdomainviewGetViewableArea(d)	(&(d)->viewableArea)
#define vdomainviewGetDomainRect(d)	(&(d)->viewDialogRect)

#define vdomainviewSelectedObjects(d)	(vdomainSelectedObjects((d)->domain, \
								(d)->selection))

#define vdomainviewGetClass(d)	      ((vdomainviewClass*)vdialogGetItemClass \
					 (vdomainviewGetItem(d)))
#define vdomainviewGetData(d)         vdialogGetItemData(vdomainviewGetItem(d))
#define vdomainviewSetSelection(d,s)		((d)->selection = (s))
#define vdomainviewGetEventClass(d)		((d)->eventClass)
#define vdomainviewSetEventClass(d,e)		((d)->eventClass = (e))
#define vdomainviewGetDrawObjectProc(d)		((d)->drawProc)
#define vdomainviewGetDrawObjectWithProc(d)		((d)->drawWithProc)
#define vdomainviewGetDrawSelectionProc(d)	((d)->selectionProc)
#define vdomainviewGetDrawSelectionWithProc(d)	((d)->selectionWithProc)
#define vdomainviewSetDrawObjectProc(d,p)	((d)->drawProc = (p))
#define vdomainviewSetDrawObjectWithProc(d,p)	((d)->drawWithProc = (p))
#define vdomainviewSetDrawSelectionWithProc(d,p) ((d)->selectionWithProc = (p))
#define vdomainviewGetDomain(d)			((d)->domain)
#define vdomainviewGetSelection(d)		((d)->selection)
#define vdomainviewHasHorzBar(d)		\
		(((d)->attributes & _vdomainviewHAS_HORZ_BAR) != 0)
#define vdomainviewHasVertBar(d)		\
		(((d)->attributes & _vdomainviewHAS_VERT_BAR) != 0)
#define vdomainviewGetHorzScrollbar(d)		((d)->hBar)
#define vdomainviewGetVertScrollbar(d)		((d)->vBar)
#define vdomainviewGetDragOutline(d)		((d)->dragOutline)
#define vdomainviewSetDragOutline(d,o)		((d)->dragOutline = (o))
#define vdomainviewGetDragMethod(d)		((d)->dragMethod)
#define vdomainviewSetDragMethod(d,m)		((d)->dragMethod = (m))
#define vdomainviewGetDragSnapMode(d)		((d)->dragSnapMode)
#define vdomainviewGetScrollBarMargin(d)	((d)->scrollBarMargin)
#define vdomainviewGetScrollIncrement(d)	((d)->scrollIncrement)
#define vdomainviewSetScrollIncrement(d,s)	((d)->scrollIncrement = (s))
#define vdomainviewGetDragThreshold(d)		((d)->dragThreshold)
#define vdomainviewSetDragThreshold(d,s)	((d)->dragThreshold = (s))
#define vdomainviewGetTrackMode(d)		((d)->trackMode)
#define vdomainviewSetTrackMode(d,m)		((d)->trackMode = (m)) 
#define vdomainviewGetUndoNotify(d)   		((d)->undoNotifyProc)
#define vdomainviewSetUndoNotify(d,p)   	((d)->undoNotifyProc = (p))
#define vdomainviewGetMatrix(d)			((d)->userMatrix)
#define vdomainviewObserver(d)			((d)->observer)
#define vdomainviewGetObserverClass(d)		((d)->observerClass)
#define vdomainviewGetObserver(d)		((d)->observerClass)
#define vdomainviewSetObserver(d, c)		((d)->observerClass = (c))
#define vdomainviewSetObserverClass(d, c)	       \
    ((d)->attributes |= _vdomainviewOLD_OBSERVER_CLASS, \
     (d)->observerClass = (c))

#define vdomainviewIsOffscreenDrawing(d)   	    	    	     	\
	    	(((d)->attributes & _vdomainviewOFFSCREEN_DRAWING) != 0)

#define vdomainviewIsAutoScroll(d)					\
		(((d)->attributes & _vdomainviewAUTO_SCROLL) != 0)
#define vdomainviewSetAutoScroll(d,a)   (a ? 			\
		((d)->attributes |= _vdomainviewAUTO_SCROLL) : 	\
		((d)->attributes &= ~_vdomainviewAUTO_SCROLL))

#define vdomainviewIsSelectEnclosed(d)					\
		(((d)->attributes & _vdomainviewSELECT_ENCLOSED) != 0)
#define vdomainviewSetSelectEnclosed(d,e)   (e ? 			\
		((d)->attributes |= _vdomainviewSELECT_ENCLOSED) :  	\
		((d)->attributes &= ~_vdomainviewSELECT_ENCLOSED))

#define vdomainviewIsSingleSelection(d)					\
		(((d)->attributes & _vdomainviewSINGLE_SELECTION) != 0)
#define vdomainviewSetSingleSelection(d,s)   (s ? 			\
		((d)->attributes |= _vdomainviewSINGLE_SELECTION) :  	\
		((d)->attributes &= ~_vdomainviewSINGLE_SELECTION))

#define vdomainviewIsLiveSelection(d)					\
		(((d)->attributes & _vdomainviewLIVE_SELECTION) != 0)
#define vdomainviewSetLiveSelection(d,l)   (l ? 			\
		((d)->attributes |= _vdomainviewLIVE_SELECTION) :  	\
		((d)->attributes &= ~_vdomainviewLIVE_SELECTION))

#define vdomainviewHasSelectAllEvents(d)				\
		(((d)->attributes & _vdomainviewSELECTALL_EVENTS) != 0)
#define vdomainviewSetSelectAllEvents(d,s)   (s ? 			\
		((d)->attributes |= _vdomainviewSELECTALL_EVENTS) :  	\
		((d)->attributes &= ~_vdomainviewSELECTALL_EVENTS))

#define vdomainviewIsDragProhibited(d)					\
		(((d)->attributes & _vdomainviewDRAG_PROHIBITED) != 0)
#define vdomainviewSetDragProhibited(d,p)   (p ? 			\
		((d)->attributes |= _vdomainviewDRAG_PROHIBITED) :  	\
		((d)->attributes &= ~_vdomainviewDRAG_PROHIBITED))

#define vdomainviewHasGrabbingHand(d)					\
		(((d)->attributes & _vdomainviewGRABBING_HAND) != 0)
#define vdomainviewSetGrabbingHand(d,s)   (s ? 			\
		((d)->attributes |= _vdomainviewGRABBING_HAND) :  	\
		((d)->attributes &= ~_vdomainviewGRABBING_HAND))

#define vdomainviewIsHorzLocked(d)				     \
		(((d)->attributes & _vdomainviewHORZ_LOCKED) != 0)
#define vdomainviewSetHorzLocked(d,s)   (s ? 			\
		((d)->attributes |= _vdomainviewHORZ_LOCKED) :  	\
		((d)->attributes &= ~_vdomainviewHORZ_LOCKED)) 
		
#define vdomainviewIsVertLocked(d)				      \
		(((d)->attributes & _vdomainviewVERT_LOCKED) != 0)
#define vdomainviewSetVertLocked(d,s)   (s ? 			\
		((d)->attributes |= _vdomainviewVERT_LOCKED) :  	\
		((d)->attributes &= ~_vdomainviewVERT_LOCKED))

#define vdomainviewGetScrollOffset(d)		(&(d)->u.info.translation)
#define vdomainviewGetScrollOffsetLong(d)	(&(d)->u.longInfo.translation)
#define vdomainviewGetScrollTranslation(d)	(&(d)->translation)

/* Backward compatibility macros */

#define vdomainviewSetScrollbarMargin(a,b)  vdomainviewSetScrollBarMargin(a,b)
#define vdomainviewGetScrollbarMargin(a)    vdomainviewGetScrollBarMargin(a)
#define vdomainviewSetDragSnapToGrid(d,s)				      \
	vdomainviewSetDragSnapMode(d,					      \
			((s) ? vdomainviewSNAP_NO_ALIGN : vdomainviewSNAP_OFF))
#define vdomainviewIsDragSnapToGrid(d)					      \
	(vdomainviewGetDragSnapMode(d) == vdomainviewSNAP_NO_ALIGN)


/*
 * * * * * * * * * * PRIVATE FUNCTION MESSAGE DEFINITIONS * * * * * * * * * *
 */

#define vdomainviewSetHorzBar(d,b) vclassSend(vdomainviewGetClass(d), \
					      vdomainviewSET_HORZ_BAR, (d,b))
#define vdomainviewSetVertBar(d,b) vclassSend(vdomainviewGetClass(d), \
					      vdomainviewSET_VERT_BAR, (d,b))
#define vdomainviewScroll(d,x,y,p) vclassSend(vdomainviewGetClass(d), \
					      vdomainviewSCROLL, (d,x,y,p))
#define vdomainviewSetScrollTranslation(d,x,y,p)	\
				   vclassSend(vdomainviewGetClass(d), \
					    vdomainviewSET_SCROLL_TRANSLATION,\
					      (d,x,y,p))
#define vdomainviewSetDomain(v,d)  vclassSend(vdomainviewGetClass(v), \
					      vdomainviewSET_DOMAIN, (v,d))
#define _vdomainviewSendDrawObject(v, o) \
				   vclassSend(vdomainviewGetClass(v), \
					      vdomainviewDRAW_OBJECT, (v,o))
#define _vdomainviewSendDrawObjectWith(v, o, c) \
				   vclassSend(vdomainviewGetClass(v), \
					      vdomainviewDRAW_OBJECT_WITH, \
					      (v,o,c))
#define _vdomainviewSendDrawSelection(v, o) \
				   vclassSend(vdomainviewGetClass(v), \
					      vdomainviewDRAW_SELECTION, (v,o))
#define _vdomainviewSendDrawSelectionWith(v, o, c) \
				   vclassSend(vdomainviewGetClass(v), \
					      vdomainviewDRAW_SELECTION_WITH, \
					      (v,o,c))


#define _vdomainviewSendScrollEvent(d, e)				      \
	vclassSend(vdomainviewGetClass(d),				      \
		   vdomainviewHANDLE_SCROLL_EVENT, (d, e))
#define _vdomainviewSendTrackEvent(d, e)				      \
	vclassSend(vdomainviewGetClass(d),				      \
		   vdomainviewHANDLE_TRACK_EVENT, (d, e))
#define _vdomainviewSendButtonUpEvent(d, e)				      \
	vclassSend(vdomainviewGetClass(d),				      \
		   vdomainviewHANDLE_BUTTON_UP_EVENT, (d, e))
#define _vdomainviewSendButtonDownEvent(d, e)				      \
	vclassSend(vdomainviewGetClass(d),				      \
		   vdomainviewHANDLE_BUTTON_DOWN_EVENT, (d, e))
#define _vdomainviewSendDoubleClickEvent(d, e)				      \
	vclassSend(vdomainviewGetClass(d),				      \
		   vdomainviewHANDLE_DBL_CLICK_EVENT, (d, e))
#define _vdomainviewSendKeyEvent(d, e)					      \
	vclassSend(vdomainviewGetClass(d),				      \
		   vdomainviewHANDLE_KEY_EVENT, (d, e))
#define _vdomainviewSendMoveEvent(d, e)					      \
	vclassSend(vdomainviewGetClass(d),				      \
		   vdomainviewHANDLE_MOVE_EVENT, (d, e))
#define _vdomainviewSendResizeObjectEvent(d, e)				      \
	vclassSend(vdomainviewGetClass(d),				      \
		   vdomainviewHANDLE_RESIZEOBJECT_EVENT, (d, e))
#define _vdomainviewSendSelectEvent(d, e)				      \
	vclassSend(vdomainviewGetClass(d),				      \
		   vdomainviewHANDLE_SELECT_EVENT, (d, e))
#define _vdomainviewSendResizeEvent(d, e)				      \
	vclassSend(vdomainviewGetClass(d),				      \
		   vdomainviewHANDLE_RESIZE_EVENT, (d, e))
#define _vdomainviewSendSelectAllEvent(d, e)				      \
	vclassSend(vdomainviewGetClass(d),				      \
		   vdomainviewHANDLE_SELECTALL_EVENT, (d, e))


vportEND_CPLUSPLUS_EXTERN_C

/*
 * Formatting information for emacs in c-mode
 *
 * Local Variables:
 * c-indent-level:4
 * c-continued-statement-offset:4
 * End:
 */

#endif /* #ifndef vdomainviewINCLUDED */

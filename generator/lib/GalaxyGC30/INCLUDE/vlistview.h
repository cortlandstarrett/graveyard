/* $Id: vlistview.h,v 1.107 1997/09/30 19:11:57 robert Exp $ */

/************************************************************

    vlistview.h
    C Interface to the List Manager, listview objects

    (c) Copyright Visix Software
    All rights reserved

************************************************************/

#ifndef vlistviewINCLUDED
#define vlistviewINCLUDED 1

#ifndef  vportINCLUDED
#include <vport.h>
#endif

#ifndef  vstdINCLUDED
#include vstdHEADER
#endif

#ifndef vdebugINCLUDED
#include vdebugHEADER
#endif

#ifndef  vclassINCLUDED
#include vclassHEADER
#endif

#ifndef  vsliderINCLUDED
#include vsliderHEADER
#endif

#ifndef vcolorINCLUDED
#include vcolorHEADER
#endif

#ifndef  vdialogINCLUDED
#include vdialogHEADER
#endif

#ifndef  veventINCLUDED
#include veventHEADER
#endif

#ifndef  vlistINCLUDED
#include vlistHEADER
#endif

#ifndef  vlistsizeINCLUDED
#include vlistsizeHEADER
#endif

#ifndef  vobjectINCLUDED
#include vobjectHEADER
#endif

#ifndef  vrectINCLUDED
#include vrectHEADER
#endif

#ifndef  vresourceINCLUDED
#include vresourceHEADER
#endif


vportBEGIN_CPLUSPLUS_EXTERN_C


/*
 * * * * * * * * * * PUBLIC CONSTANT DEFINITIONS * * * * * * * * * *
 */

/* directions for vlistviewMoveFocus */
enum {
    vlistviewLEFT	= 0,
    vlistviewUP		= 1,
    vlistviewRIGHT	= 2,
    vlistviewDOWN	= 3
};


/* all-inclusive row/column IDs for vlistviewSetRowHeight/ColumnWidth */
#define vlistviewALL_ROWS    vlistsizeALL_ROWS
#define vlistviewALL_COLUMNS vlistsizeALL_COLUMNS


/* state parameter to selection notify function */
enum {
    vlistviewSELECTION_WILL_CHANGE = 1,
    vlistviewSELECTION_IS_CHANGING,
    vlistviewSELECTION_HAS_CHANGED
};

/* command selector values */
enum {
    vlistviewSELECT_EXTEND_RIGHT = vdialogITEM_NEXT_SELECT,
    vlistviewSELECT_EXTEND_LEFT,
    vlistviewSELECT_EXTEND_UP,
    vlistviewSELECT_EXTEND_DOWN,
    vlistviewSELECT_TRIGGER_ACTION,
    vlistviewNEXT_SELECT
};

/* types for vlistviewSetRearrange() */
enum {
    vlistviewNO_REARRANGE = -1,
    vlistviewROW_REARRANGE = 1,
    vlistviewCOLUMN_REARRANGE
};

/* don't care value from vlistviewDetermineCellSize() */
enum {
    vlistviewDONT_CARE = -1
};

/* Modes for vlistviewSetUpdateMode */
enum {
    vlistviewSCROLL,
    vlistviewINVAL,
    vlistviewDO_NOTHING
};

/* magic cookie for vlistviewDrawCellFocus */
enum {
    vlistviewEMPTY_LIST = -1
};


/*
 * * * * * * * * * * PUBLIC TYPE DEFINITIONS * * * * * * * * * *
 */

typedef struct vlistview	vlistview;
typedef struct vlistviewClass	vlistviewClass;
typedef vlistObserver		vlistviewListObserver;

typedef void (*vlistviewDrawCellProc) (
    vlistview  *listview, 
    int 	row, 
    int 	column,
    int 	selected, 
    vrect      *rect);

typedef void (*vlistviewSelectNoteProc) (
    vlistview  *listview,
    int state
    );

typedef void (*vlistviewSelectionFilterProc) (
    vlistview *listview,
    vlistSelection *selection
    );

typedef void (*vlistviewNoteProc) (
    vlistview *listview,
    vevent *event
    );


/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */


void vlistviewStartup (
     void
     );


vlistviewClass	*vlistviewGetDefaultClass (
    void
    );


vlistview *vlistviewCreateOfClass (
    vlistviewClass	*clas
    );

vlistview *vlistviewCreate (
    void
    );

vlistview *vlistviewClone (
    vlistview	*listview
    );

void vlistviewInit (
    vlistview	*listview
    );

void vlistviewInitOfClass (
    vlistview		*listview,
    vlistviewClass	*clas
    );

void vlistviewDestroy (
    vlistview	*listview
    );

void vlistviewCopy (
    vlistview	*listview,
    vlistview	*target
    );

void vlistviewCopyInit (
    vlistview	*listview,
    vlistview	*target
    );

vlistObserverClass *vlistviewGetDefaultObserverClass (
    void
    );


vlistview *vlistviewLoad (
    vresource 	 resource
    );
    
void vlistviewLoadInit (
    vlistview 	*listview,
    vresource    resource
    );

void vlistviewStore (
    vlistview 	*listview,
    vresource    resource
    );

void vlistviewSetNotify (
    vlistview 	*listview,
    vlistviewNoteProc  noteProc
    );

vlistviewNoteProc vlistviewGetNotify (
    vlistview   *listview
    );

void vlistviewNotify (
    vlistview	*listview,
    vevent	*event
    );

void vlistviewSetSelectNotify (
    vlistview   *listview,
    vlistviewSelectNoteProc noteProc
    );

vlistviewSelectNoteProc vlistviewGetSelectNotify (
    vlistview   *listview
    );

void vlistviewNotifySelect (
    vlistview	*listview,
    int		 state
    );

void vlistviewNotifyScroll (
    vlistview	*listview,
    int		 horzDistance,
    int	         vertDistance
    );

void vlistviewSetData (
    vlistview   *listview,
    void	*data
    );

const void *vlistviewGetData (
    vlistview	*listview
    );

void vlistviewSetList (
    vlistview	*listview,
    vlist	*list
    );

void vlistviewSetListOwned (
    vlistview	*listview,
    vlist	*list
    );

vlist *vlistviewGetList (
    vlistview	*listview
    );

vdialogItem *vlistviewGetItem (
    vlistview	*listview
    );

vlistviewClass *vlistviewGetClass (
    vlistview	*listview
    );


void vlistviewSetObserverClass (
    vlistview	*listview,
    vlistObserverClass *observerClass
    );

vlistObserverClass *vlistviewGetObserverClass (
    vlistview	*listview
    );

/* sizes */

vlistsize *vlistviewGetSizes (
    vlistview	*listview
    );

void vlistviewSetSizes (
    vlistview	*listview,
    vlistsize	*size
    );

void vlistviewSetRowHeight (
    vlistview	*listview,
    int		 row,
    int		 height
    );

int vlistviewGetRowHeight (
    vlistview	*listview,
    int		 row
    );

void vlistviewSetColumnWidth (
    vlistview	*listview,
    int		 column,
    int		 width
    );

int vlistviewGetColumnWidth (
    vlistview	*listview,
    int		 column
    );

void vlistviewGetCellRect (
    vlistview	*listview,
    int		 row,
    int		 column,
    vrect	*rect
    );

void vlistviewDetermineCellSize (
    vlistview	*listview,
    int 	 row,
    int		 column,
    int		*width,
    int		*height
    );

void vlistviewSetUpdateMode (
    vlistview	*listview,
    int		 mode /* vlistviewSCROLL, vlistviewINVAL, vlistviewDO_NOTHING */
    );

int vlistviewGetUpdateMode (
    vlistview	*listview
    );

/* scrolling */

void vlistviewScroll (
    vlistview	*listview,
    int		 deltaRows,
    int		 deltaColumns
    );

void vlistviewScrollToCell (
    vlistview	*listview,
    int		 row,
    int		 column
    );

void vlistviewScrollToCellWithOffset (
    vlistview	*listview,
    int		 row,
    int		 column,
    int		 xoffset,
    int		 yoffset
    );

void vlistviewScrollSelectionIntoView (
    vlistview	*listview
    );

void vlistviewScrollFocusIntoView (
    vlistview	*listview
    );


void vlistviewScrollRelative (
    vlistview	*listview,
    int		 hdelta,
    int		 vdelta
    );

void vlistviewScrollAbsolute (
    vlistview	*listview,
    int		 xoffset,
    int		 yoffset
    );


/* drawing */

void vlistviewGetDrawingOffsets (
    vlistview	*listview,
    int		*xoffset,
    int		*yoffset
    );

void vlistviewGetVisibleRange (
    vlistview	*listview,
    int		*row,
    int		*column,
    int		*rows,
    int		*columns
    );

void vlistviewGetContentNaturalSize (
    vlistview	*listview,
    int		*w,
    int		*h
    );

void vlistviewGetDecorationSizes (
    vlistview	*listview,
    int		*top,
    int		*left,
    int		*bottom,
    int		*right
    );

void vlistviewDraw (
    vlistview	*listview
    );

void vlistviewDrawWith (
    vlistview	*listview,
    vdrawcontext *context
    );

void vlistviewDrawCell (
    vlistview	*listview,
    int		 row,
    int		 column
    );

void vlistviewDrawCellBackground (
    vlistview	*listview,
    int		 row,
    int		 column,
    int		 selected,
    vrect	*rect
    );

void vlistviewDrawCellBackgroundWith (
    vlistview	*listview,
    int		 row,
    int		 column,
    int		 selected,
    vrect	*rect,
    vdrawcontext *context
    );

void vlistviewDrawCellGrid (
    vlistview	*listview,
    int		 row,
    int		 column,
    vrect	*rect
    );
    
void vlistviewDrawCellGridWith (
    vlistview	*listview,
    int		 row,
    int		 column,
    vrect	*rect,
    vdrawcontext *context
    );
    
void vlistviewDrawCellContents (
    vlistview	*listview,
    int		 row,
    int		 column,
    int		 selected,
    vrect	*rect
    );

void vlistviewDrawCellContentsWith (
    vlistview	*listview,
    int		 row,
    int		 column,
    int		 selected,
    vrect	*rect,
    vdrawcontext *context
    );

void vlistviewDrawCellSelection (
    vlistview	*listview,
    int		 row,
    int		 column,
    vrect	*rect
    );

void vlistviewDrawCellSelectionWith (
    vlistview	*listview,
    int		 row,
    int		 column,
    vrect	*rect,
    vdrawcontext *context
    );

/* this may be passed vlistviewEMPTY_LIST for row & column */
void vlistviewDrawCellFocus (
    vlistview   *listview,
    int		 row,
    int		 column,
    vrect	*rect
    );

void vlistviewDrawCellFocusWith (
    vlistview   *listview,
    int		 row,
    int		 column,
    vrect	*rect,
    vdrawcontext *context
    );

void vlistviewDrawMoveCursor (
    vlistview	*listview,
    int		 oldindex,
    int		 newindex
    );

void vlistviewSetCellContentProc (
    vlistview	*listview,
    vlistviewDrawCellProc  proc
    );

vlistviewDrawCellProc vlistviewGetCellContentProc (
    vlistview	*listview
    );

vlistviewDrawCellProc vlistviewGetDefaultCellContentProc (
    vlistview	*listview
    );

void vlistviewDrawFocus (
    vlistview	*listview
    );
    
void vlistviewDrawFocusWith (
    vlistview	*listview,
    vdrawcontext *context
    );
    
void vlistviewInval (
    vlistview	*listview
    );

void vlistviewInvalCell (
    vlistview	*listview,
    int		 row,
    int		 column
    );

void vlistviewInvalRow (
    vlistview	*listview,
    int		 row
    );

void vlistviewInvalColumn (
    vlistview	*listview,
    int		 column
    );

void vlistviewRedrawSelectionDifference (
    vlistview	*listview,
    vlistSelection	*selection,
    vlistSelection	*anotherSelection
    );

void vlistviewInvalSelection (
    vlistview	*listview,
    vlistSelection	*selection
    );

void vlistviewRedrawSelection (
    vlistview	*listview,
    vlistSelection	*selection,
    vlistSelection  	*selectedCells
    );

void vlistviewClip (
    vlistview	*listview
    );

void vlistviewClipContext (
    vlistview	*listview,
    vdrawcontext *context
    );

const vrect *vlistviewGetRect (
    vlistview	*listview
    );

const vrect *vlistviewGetListRect (
    vlistview	*listview
    );

void vlistviewSetScrollBarMargin (
    vlistview	*listview,
    int		 margin
    );

int vlistviewGetScrollBarMargin (
    vlistview	*listview
    );

void vlistviewSetSelection (
    vlistview	*listview,
    vlistSelection	*selection
    );

vlistSelection *vlistviewGetSelection (
    vlistview	*listview
    );

vlistSelection *vlistviewGetVolatileSelection (
    vlistview	*listview
    );

int vlistviewGetTopRow (
    vlistview	*listview
    );

int vlistviewGetBottomRow (
    vlistview	*listview
    );

int vlistviewGetLeftColumn (
    vlistview	*listview
    );

int vlistviewGetRightColumn (
    vlistview	*listview
    );

/* event */

void vlistviewSetFocus (
    vlistview	*listview,
    int		 row,
    int		 column
    );

void vlistviewGetFocus (
    vlistview	*listview,
    int		*row,
    int		*column
    );

void vlistviewMoveFocus (
    vlistview	*listview,
    int		 direction /* vlistviewLEFT/UP/RIGHT/DOWN */
    );

void vlistviewTraverseVector (
    vlistview	*listview,
    int		 rowDelta,
    int		 columnDelta
    );

void vlistviewMapPointToCell (
    vlistview	*listview,
    vpoint	*point,
    int		*row,
    int		*column
    );

int vlistviewGetLastPointerClickCount (
    vlistview	*listview
    );
    
void vlistviewGetLastPointerPosition (
    vlistview	*listview,
    int		*lastX,
    int		*lastY
    );

void vlistviewFilterSelection (
    vlistview	*listview,
    vlistSelection	*selection
    );

void vlistviewSetSelectionFilter (
    vlistview	*listview,
    vlistviewSelectionFilterProc	proc
    );

vlistviewSelectionFilterProc vlistviewGetSelectionFilter (
    vlistview	*listview
    );



/* list attribute modification/access */

void vlistviewSetBorder (
    vlistview	*listview,
    int		 hasBorder
    );

void vlistviewSetAutoScroll (
    vlistview	*listview,
    int		 isAutoScroll
    );

void vlistviewSetRearrange (
    vlistview	*listview,
    int		 type /* vlistviewNO_REARRANGE/ROW_REARRANGE/COLUMN_REARRANGE */
    );
    
int vlistviewGetRearrange (
    vlistview	*listview
    );

void vlistviewSetRowRearrange (
    vlistview	*listview,
    int		 isRowRearrange
    );

void vlistviewSetColumnRearrange (
    vlistview	*listview,
    int		 isColumnRearrange
    );


void vlistviewSetHorzBar (
    vlistview	*listview,
    int		 onOff
    );

void vlistviewSetVertBar (
    vlistview	*listview,
    int		 onOff
    );

vsliderScrollBar *vlistviewGetHorzScrollbar (
    vlistview	*listview
    );

vsliderScrollBar *vlistviewGetVertScrollbar (
    vlistview	*listview
    );

void vlistviewSetTraversalWrap (
    vlistview	*listview,
    int		 onOff
    );

void vlistviewSetGrabbingHand (
    vlistview	*listview,
    int		 onOff
    );

void vlistviewSetSelectionSense (
    vlistview	*listview,
    int		 onOff
    );

void vlistviewSetUseKeyboardSelection (
    vlistview	*listview,
    int		 onOff
    );

void vlistviewSetUseKeyboardTraversal (
    vlistview	*listview,
    int		 onOff
    );

void vlistviewSetDrawingSelection (
    vlistview	*listview,
    int		 onOff
    );

void vlistviewSetHorzGrid (
    vlistview	*listview,
    int		 onOff
    );

void vlistviewSetVertGrid (
    vlistview 	*listview,
    int		 onOff
    );

int vlistviewHasBorder (
    vlistview	*listview
    );

int vlistviewHasAutoScroll (
    vlistview	*listview
    );

int vlistviewHasHorzBar (
    vlistview	*listview
    );

int vlistviewHasVertBar (
    vlistview	*listview
    );

int vlistviewHasTraversalWrap (
    vlistview	*listview
    );

int vlistviewHasGrabbingHand (
    vlistview	*listview
    );

int vlistviewHasSelectionSense (
    vlistview	*listview
    );

int vlistviewHasUseKeyboardSelection (
    vlistview	*listview
    );

int vlistviewHasDrawingSelection (
    vlistview	*listview
    );

int vlistviewHasUseKeyboardTraversal (
    vlistview	*listview
    );

int vlistviewHasHorzGrid (
    vlistview	*listview
    );

int vlistviewHasVertGrid (
    vlistview 	*listview
    );

int vlistviewHasRearrange (
    vlistview	*listview
    );

int vlistviewHasRowRearrange (
    vlistview	*listview
    );
    
int vlistviewHasColumnRearrange (
    vlistview	*listview
    );

int vlistviewIsRearranging (
    vlistview	*listview
    );

int vlistviewGetRearrangingFrom (
    vlistview	*listview
    );

int vlistviewGetRearrangingTo (
    vlistview	*listview
    );

int vlistviewGetRearrangingType (
    vlistview	*listview
    );


/*
 * deprecated functions
 */

void vlistviewGetRearrangement (
    vlistview	*listview,
    int		*from,
    int		*to,
    int		*type
    );

void vlistviewDrawBorder (
    vlistview	*listview,
    vrect	*rect
    );

void vlistviewDrawBorderWith (
    vlistview    *listview,
    vrect        *rect,
    vdrawcontext *context
    );


/*
 * * * * * * * * * * PRIVATE CONSTANT DEFINITIONS * * * * * * * * * *
 */

enum {
    _vlistviewAUTO_SCROLL		= 0x00000001,
    _vlistviewUNUSED_2			= 0x00000002,
    _vlistviewTRAVERSAL_WRAP		= 0x00000004,
    _vlistviewSELECTION_SENSE		= 0x00000008,
    _vlistviewUSE_KEYBOARD_SELECTION	= 0x00000010,
    _vlistviewBORDER			= 0x00000020,
    _vlistviewGRABBING_HAND		= 0x00000040,
    _vlistviewDRAWING_SELECTION		= 0x00000080,
    _vlistviewHAS_ROW_REARRANGE		= 0x00000100,
    _vlistviewHAS_COLUMN_REARRANGE	= 0x00000200,
    _vlistviewUSE_KEYBOARD_TRAVERSAL	= 0x00000400,
    _vlistviewHAS_HORZ_BAR		= 0x00000800,
    _vlistviewHAS_VERT_BAR		= 0x00001000,
    _vlistviewHAS_HORZ_SPLITTER		= 0x00002000,
    _vlistviewHAS_VERT_SPLITTER		= 0x00004000,
    _vlistviewSCROLLBAR_MARGIN_SET	= 0x00008000,
    _vlistviewHORZ_GRID			= 0x00010000,
    _vlistviewVERT_GRID			= 0x00020000
};


/*
 * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * *
 */

/* !!! 2/12/96 scotth: Warning! _vlistviewCopy assumes that the last 7    */
/*     slots of the vlistview struct are the selections, scroll bars, and */
/*     observer. Appending anything to the end of the vlistview struct    */
/*     will break _vlistviewCopy! Add any new stuff after the slots for   */
/*     xtranslate and ytranslate, it's safe there.                        */

struct vlistview {
    vdialogItem		item;
    int			top, left, bottom, right;
    short		xoffset, yoffset;
    short		updateMode;
    vrect		cellArea;
    
    int			focusRow, focusColumn;
    int			attributes;
    int			flags;
    int			arrangeFrom, arrangeTo, arrangeType;

    vlistviewDrawCellProc   cellContentProc;
    vlistviewSelectNoteProc selectNoteProc;
    vlistviewSelectionFilterProc selectionFilter;

    vbool		hasFocus;
    
    int			hScrollValue; /* scrolling w/o bars */
    int			vScrollValue;
    int			lastScrollX, lastScrollY;
    short		notifyNest;
    int			rowAnchor, columnAnchor;
    short		scrollBarMargin;
    int			lastRow, lastColumn;

    vlistsize          *sizes;

    int			xtranslate, ytranslate;
    
    vlistObserverClass *observerClass;
    int			observerNest;
    vlistObserver      *observer;

    vbool		ownedListData;
    vlist	       *listData;

    vsliderScrollBar   *hscroll;
    vsliderScrollBar   *vscroll;
    vlistSelection     *selection, 	    *transientSelection,
    		       *previousSelection;
};



#define vlistviewCLASS(SUPER, ITEM, NOTIFY) 				      \
vdialogITEM_CLASS(SUPER, ITEM, NOTIFY); 				      \
vclassVARIABLE(vlistviewSELECTION_INSET, short); 			      \
vclassVARIABLE(vlistviewCELL_CONTENT_INDENT, short); 			      \
vclassVARIABLE(vlistviewBORDER_INSET, short); 				      \
vclassMETHOD_RET (vlistviewCREATE_SCROLL_BAR, vsliderScrollBar *,	      \
		  (ITEM *listview));					      \
vclassMETHOD_RET (vlistviewGET_DEFAULT_CONTENT_PROC,			      \
		  vlistviewDrawCellProc, (ITEM *listview)); 		      \
vclassMETHOD (vlistviewSCROLL_ABSOLUTE, (ITEM *listview, int xpos, int ypos));\
vclassMETHOD (vlistviewNOTIFY_SCROLL, (ITEM *listview, int horzDistance,      \
				       int vertDistance)); 		      \
vclassMETHOD (vlistviewDRAW_CELL_BACKGROUND, (ITEM *listview, int row, 	      \
					      int column, int selected,       \
					      vrect *rect)); 		      \
vclassMETHOD (vlistviewDRAW_CELL_BACKGROUND_WITH, (ITEM *listview, int row,   \
					      int column, int selected,       \
					      vrect *rect,                    \
					      vdrawcontext *context));	      \
vclassMETHOD (vlistviewDRAW_CELL_GRID, (ITEM *listview, int row, 	      \
					int column, vrect *rect)); 	      \
vclassMETHOD (vlistviewDRAW_CELL_GRID_WITH, (ITEM *listview, int row, 	      \
					int column, vrect *rect,              \
					vdrawcontext *context)); 	      \
vclassMETHOD (vlistviewDRAW_CELL_CONTENTS, (ITEM *listview, int row, 	      \
					    int column, int selected, 	      \
					    vrect *rect)); 		      \
vclassMETHOD (vlistviewDRAW_CELL_CONTENTS_WITH, (ITEM *listview, int row,     \
					    int column, int selected, 	      \
					    vrect *rect,                      \
					    vdrawcontext *context)); 	      \
vclassMETHOD (vlistviewDRAW_CELL_SELECTION, (ITEM *listview, int row, 	      \
					     int column, 		      \
					     vrect *rect)); 		      \
vclassMETHOD (vlistviewDRAW_CELL_SELECTION_WITH, (ITEM *listview, int row,    \
					     int column, 		      \
					     vrect *rect,                     \
                                             vdrawcontext *context));         \
vclassMETHOD (vlistviewDRAW_CELL_FOCUS, (ITEM *listview, int row, 	      \
					     int column, 		      \
					     vrect *rect)); 		      \
vclassMETHOD (vlistviewDRAW_CELL_FOCUS_WITH, (ITEM *listview, int row, 	      \
					     int column, 		      \
					     vrect *rect,                     \
                                             vdrawcontext *context));         \
vclassMETHOD (vlistviewDRAW_MOVE_CURSOR, (ITEM *listview, int oldIndex,       \
					  int newIndex)); 		      \
vclassMETHOD (vlistviewDETERMINE_CELL_SIZE, (ITEM *listview, int row, 	      \
					     int column, int *width, 	      \
					     int *height));  		      \
vclassMETHOD (vlistviewTRAVERSE_VECTOR, (ITEM *listview, int rowDelta, 	      \
					 int columnDelta)); 		      \
vclassMETHOD (vlistviewSET_FOCUS, (ITEM *listview, int row, int column));     \
vclassMETHOD (vlistviewNOTIFY_SELECT, (ITEM *listview, int type)); 	      \
vclassMETHOD (vlistviewFILTER_SELECTION, (ITEM *listview,		      \
					  vlistSelection *selection)); 	      \
vclassMETHOD (vlistviewINVAL_SELECTION, (ITEM *listview,		      \
					 vlistSelection *selection));  	      \
vclassMETHOD (vlistviewREDRAW_SELECTION, (ITEM *listview,		      \
					  vlistSelection *selection,	      \
					  vlistSelection *selectedCells));    \
vclassMETHOD (vlistviewSET_HORZ_BAR, (ITEM *listview, int onOff)); 	      \
vclassMETHOD (vlistviewSET_VERT_BAR, (ITEM *listview, int onOff)); 	      \
vclassMETHOD (vlistviewSET_LIST, (ITEM *listview, vlist *list)); 	      \
vclassMETHOD (vlistviewSET_LIST_OWNED, (ITEM *listview, vlist *list)); 	      \
vclassMETHOD (vlistviewSET_SELECTION, (ITEM *listview, 			      \
				       vlistSelection *selection)); 	      \
vclassMETHOD (vlistviewSET_SELECT_NOTIFY, (ITEM *listview, 		      \
					   vlistviewSelectNoteProc proc));    \
vclassMETHOD (vlistviewSET_ROW_HEIGHT, (ITEM *listview, int row, int height));\
vclassMETHOD (vlistviewSET_COLUMN_WIDTH, (ITEM *listview, int column, 	      \
					  int width)); 			      \
vclassMETHOD (vlistviewSET_SCROLL_BAR_MARGIN, (ITEM *listview, int margin));  \
vclassMETHOD (vlistviewSET_CELL_CONTENT_PROC, (ITEM *listview, 		      \
					       vlistviewDrawCellProc proc));  \
vclassMETHOD (vlistviewSET_SELECTION_FILTER, (ITEM *listview, 		      \
					      vlistviewSelectionFilterProc    \
					      proc)); 			      \
vclassMETHOD (vlistviewSET_AUTO_SCROLL, (ITEM *listview, int onOff)); 	      \
vclassMETHOD (vlistviewSET_TRAVERSAL_WRAP, (ITEM *listview, int onOff));      \
vclassMETHOD (vlistviewSET_GRABBING_HAND, (ITEM *listview, int onOff));       \
				      				              \
vclassMETHOD (vlistviewSET_USE_KEYBOARD_SELECTION, (ITEM *listview, 	      \
						    int onOff));	      \
vclassMETHOD (vlistviewSET_USE_KEYBOARD_TRAVERSAL, (ITEM *listview, 	      \
						    int onOff)); 	      \
vclassMETHOD (vlistviewSET_DRAWING_SELECTION, (ITEM *listview, int onOff));   \
vclassMETHOD (vlistviewSET_SELECTION_SENSE, (ITEM *listview, int onOff));     \
vclassMETHOD (vlistviewSET_REARRANGE, (ITEM *listview, int type)); 	      \
vclassMETHOD (vlistviewGET_CONTENT_NATURAL_SIZE, (ITEM *listview, 	      \
						  int *w, int *h)); 	      \
vclassMETHOD (vlistviewSET_HORZ_GRID, (ITEM *listview, int onOff)); 	      \
vclassMETHOD (vlistviewSET_VERT_GRID, (ITEM *listview, int onOff)); 	      \
vclassMETHOD (vlistviewSET_SIZES, (ITEM *listview, vlistsize *size)); 	      \
vclassMETHOD (vlistviewSET_UPDATE_MODE, (ITEM *listview, int mode));          \
/* deprecated methods */                                                      \
vclassMETHOD (vlistviewDRAW_BORDER, (ITEM *listview, vrect *rect));           \
vclassMETHOD (vlistviewDRAW_BORDER_WITH, (ITEM *listview, vrect *rect,        \
                                          vdrawcontext *context));            \
vclassMETHOD (vlistviewGET_DECORATION_SIZES, (ITEM *listivew,                 \
                                              int *top, int *left,            \
                                              int *bottom, int *right))



struct vlistviewClass {
    vlistviewCLASS (vlistviewClass, vlistview, vlistviewNoteProc);
};


/*
 * * * * * * * * * * PRIVATE VARIABLE DECLARATIONS * * * * * * * * * *
 */

#if (vdebugTEST_UI)
extern vportLINK vbool _vlistviewKbdEvent;
#endif


/*
 * * * * * * * * * * PRIVATE FUNCTION PROTOTYPES * * * * * * * * * *
 */


void _vlistviewSetRowColumnHeight (vlistview*, int, int, int);
int _vlistviewGetRowColumnHeight (vlistview*, int, int);
short _vlistviewGetLastPointerX (vlistview *listview);
short _vlistviewGetLastPointerY (vlistview *listview);

short _vlistviewGetDefaultSelectionInset(vlistview *listview);
short _vlistviewGetDefaultBorderInset(vlistview *listview);
short _vlistviewGetDefaultCellContentIndent(vlistview *listview);

void _vlistviewSetSelectOnlyIfInside (vlistview *listview, int onOff);
int _vlistviewGetSelectOnlyIfInside (vlistview *listview);
void _vlistviewSetAutoBar (vlistview *listview, int onOff);
int _vlistviewGetAutoBar (vlistview *listview);

vobjectPartialChildIteratorClass *_vlistviewGetPartialChildIteratorClass(void);

vsliderScrollBar *_vlistviewSendCreateScrollBar(vlistview *listview);

/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * *
 */

#define _vlistviewARE_REARRANGING		0x00000008

#define vlistviewGetItem(l)	(vportBASE_OBJECT((l), item))
#define vlistviewGetClass(l)	((vlistviewClass*)vdialogGetItemClass \
				 ((vdialogItem *)(l)))

#define vlistviewCreateOfClass(c) \
	((vlistview*) vdialogCreateItemOfClass((vdialogItemClass*)(c)))
#define vlistviewCreate()  vlistviewCreateOfClass(vlistviewGetDefaultClass())

#define vlistviewClone(l)	((vlistview*)vdialogCloneItem((vdialogItem*) \
							      (l)))
#define vlistviewInitOfClass(l,c)	\
	vdialogInitItemOfClass(vlistviewGetItem(l), (vdialogItemClass*)(c))
#define vlistviewInit(l)	vlistviewInitOfClass(l, \
						     vlistviewGetDefaultClass())
#define vlistviewDestroy(l)	vdialogDestroyItem(vlistviewGetItem(l))

#define vlistviewCopy(l,t)	vclassSend(vlistviewGetClass(l), \
					   vobjectCOPY, (l,t))
#define vlistviewCopyInit(l,t)	vdialogCopyInitItem(vlistviewGetItem(l), \
						    vlistviewGetItem(t))
#define vlistviewLoad(r)	((vlistview*)vdialogLoadItem(r))
#define vlistviewLoadInit(l,r)	vdialogLoadInitItem(vlistviewGetItem(l), r)
#define vlistviewStore(l,r)	vclassSend(vlistviewGetClass(l), \
					   vobjectSTORE, (l,r))

#define vlistviewSetNotify(l,p)	vdialogSetItemNotify(vlistviewGetItem(l),\
						     (vdialogItemNoteProc)p)
#define vlistviewGetNotify(l)	((vlistviewNoteProc)vdialogGetItemNotify \
				 (vlistviewGetItem(l)))
#define vlistviewNotify(l,e)	vdialogNotifyItem(vlistviewGetItem(l),e)

#define vlistviewGetSelectNotify(l)	(l)->selectNoteProc
#define vlistviewSetData(l,d)	vdialogSetItemData(vlistviewGetItem(l),d)
#define vlistviewGetData(l)	vdialogGetItemData(vlistviewGetItem(l))

#define vlistviewGetList(l)	(l)->listData
#define vlistviewSetObserverClass(l,c) ((l)->observerClass = (c))
#define vlistviewGetObserverClass(l) ((l)->observerClass)

#define vlistviewScrollFocusIntoView(l) vlistviewScrollToCell(l, \
							     (l)->focusRow, \
							     (l)->focusColumn)

#define vlistviewDraw(l)	vdialogDrawItem(vlistviewGetItem(l))
#define vlistviewDrawWith(l,c)	vdialogDrawItemWith(vlistviewGetItem(l),c)
#define vlistviewGetCellContentProc(l)	    ((l)->cellContentProc)
#define vlistviewGetSizes(l)		    ((l)->sizes)

#define vlistviewDrawFocus(l)	vdialogDrawItemFocus(vlistviewGetItem(l))
#define vlistviewDrawFocusWith(l,c)                                           \
       vdialogDrawItemFocusWith(vlistviewGetItem(l),c)
#define vlistviewInval(l)	\
vdialogInvalItemRect(vlistviewGetItem((l)),&((l)->cellArea),vwindowINVAL_OPAQUE)
#define vlistviewClip(l)	vdrawRectsClip(&(l)->cellArea, 1)
#define vlistviewClipContext(l,c)                                              \
  vdrawcontextClipRectangles(c,&(l)->cellArea, 1)
#define vlistviewGetRect(l)	vdialogGetItemRect(vlistviewGetItem(l))
#define vlistviewGetListRect(l) (&((l)->cellArea))
#define vlistviewGetScrollBarMargin(l)	(l)->scrollBarMargin
#define vlistviewGetSelection(l) (l)->selection
#define vlistviewGetVolatileSelection(l) (l)->previousSelection
#define vlistviewGetTopRow(l)	(l)->top
#define vlistviewGetBottomRow(l) (l)->bottom
#define vlistviewGetLeftColumn(l) (l)->left
#define vlistviewGetRightColumn(l) (l)->right
#define vlistviewGetFocus(l,r,c)  { *(r) = (l)->focusRow; \
				    *(c) = (l)->focusColumn; }
#define vlistviewGetDrawingOffsets(l,x,y) { *(x) = (l)->xoffset; \
					    *(y) = (l)->yoffset; }
#define vlistviewGetLastPointerPosition(l,x,y) \
    { *(x) = _vlistviewGetLastPointerX((l));   \
      *(y) = _vlistviewGetLastPointerY((l)); } 

#define vlistviewSetBorder(l,a)	vdialogSetItemBorder(vlistviewGetItem(l), a)


#define vlistviewHasBorder(l)	vdialogItemHasBorder(vlistviewGetItem(l))

#define vlistviewHasAutoScroll(l)	\
		(((l)->attributes & _vlistviewAUTO_SCROLL) != 0)
#define vlistviewHasGrabbingHand(l)	\
		(((l)->attributes & _vlistviewGRABBING_HAND) != 0)
#define vlistviewHasHorzBar(l)	((l)->hscroll != NULL)
#define vlistviewHasVertBar(l)	((l)->vscroll != NULL)
#define vlistviewHasSelectionSense(l)	\
		(((l)->attributes & _vlistviewSELECTION_SENSE) != 0)
#define vlistviewHasUseKeyboardSelection(l)   \
		(((l)->attributes & _vlistviewUSE_KEYBOARD_SELECTION) != 0)
#define vlistviewHasDrawingSelection(l)   \
		(((l)->attributes & _vlistviewDRAWING_SELECTION) != 0)
#define vlistviewHasTraversalWrap(l)   \
		(((l)->attributes & _vlistviewTRAVERSAL_WRAP) != 0)
#define vlistviewHasUseKeyboardTraversal(l)	\
		(((l)->attributes & _vlistviewUSE_KEYBOARD_TRAVERSAL) != 0)
#define vlistviewHasRearrange(l)	\
		(((l)->attributes &     \
	   (_vlistviewHAS_ROW_REARRANGE | _vlistviewHAS_COLUMN_REARRANGE)) != 0)
#define vlistviewHasRowRearrange(l) \
		(((l)->attributes & _vlistviewHAS_ROW_REARRANGE) != 0)
#define vlistviewHasColumnRearrange(l) \
		(((l)->attributes & _vlistviewHAS_COLUMN_REARRANGE) != 0)

#define vlistviewIsRearranging(l)	\
		(vlistviewHasRearrange(l) \
		 && ((l)->flags & _vlistviewARE_REARRANGING))


#define vlistviewGetSelectionFilter(l)    ((l)->selectionFilter)

#define vlistviewGetRearrangingFrom(l)	  ((l)->arrangeFrom)
#define vlistviewGetRearrangingTo(l)	  ((l)->arrangeTo)
#define vlistviewGetRearrangingType(l)	  ((l)->arrangeType)

#define vlistviewGetRearrangement(l,f,t,y) { \
					     *(f) = (l)->arrangeFrom; \
					     *(t) = (l)->arrangeTo; \
					     *(y) = (l)->arrangeType; }

#define vlistviewHasHorzGrid(l) (((l)->attributes & _vlistviewHORZ_GRID) != 0)
#define vlistviewHasVertGrid(l) (((l)->attributes & _vlistviewVERT_GRID) != 0)

#define vlistviewGetHorzScrollbar(l)	((l)->hscroll)
#define vlistviewGetVertScrollbar(l)	((l)->vscroll)

#define vlistviewGetUpdateMode(l)	((l)->updateMode)


/*
 * * * * * * * * * * PRIVATE FUNCTION MESSAGE DEFINITIONS * * * * * * * * * *
 */

#define vlistviewGetDefaultCellContentProc(l) \
	vclassSend(vlistviewGetClass(l), vlistviewGET_DEFAULT_CONTENT_PROC, (l))

#define vlistviewNotifyScroll(l,h,v) \
	vclassSend(vlistviewGetClass(l), vlistviewNOTIFY_SCROLL, (l,h,v))

#define vlistviewDrawCellBackground(l,r,c,s,rt) \
	vclassSend(vlistviewGetClass(l), vlistviewDRAW_CELL_BACKGROUND, \
		   (l,r,c,s,rt))

#define vlistviewDrawCellBackgroundWith(l,r,c,s,rt,x) \
	vclassSend(vlistviewGetClass(l), vlistviewDRAW_CELL_BACKGROUND_WITH, \
		   (l,r,c,s,rt,x))

#define vlistviewDrawCellGrid(l,r,c,rt) \
	vclassSend(vlistviewGetClass(l), vlistviewDRAW_CELL_GRID, (l,r,c,rt))

#define vlistviewDrawCellGridWith(l,r,c,rt,x) \
	vclassSend(vlistviewGetClass(l), vlistviewDRAW_CELL_GRID_WITH, \
		   (l,r,c,rt,x))

#define vlistviewDrawCellSelection(l,r,c,rt) \
	vclassSend(vlistviewGetClass(l), vlistviewDRAW_CELL_SELECTION, \
		   (l,r,c,rt))

#define vlistviewDrawCellSelectionWith(l,r,c,rt, x) \
	vclassSend(vlistviewGetClass(l), vlistviewDRAW_CELL_SELECTION_WITH, \
		   (l,r,c,rt,x))

#define vlistviewDrawCellFocus(l,r,c,rt) \
	vclassSend(vlistviewGetClass(l), vlistviewDRAW_CELL_FOCUS, \
		   (l,r,c,rt))

#define vlistviewDrawCellFocusWith(l,r,c,rt,x) \
	vclassSend(vlistviewGetClass(l), vlistviewDRAW_CELL_FOCUS_WITH, \
		   (l,r,c,rt,x))

#define vlistviewTraverseVector(l,rd,cd) \
	vclassSend(vlistviewGetClass(l), vlistviewTRAVERSE_VECTOR, (l,rd,cd))

#define vlistviewSetFocus(l,r,c) \
	vclassSend(vlistviewGetClass(l), vlistviewSET_FOCUS, (l, r, c))

#define vlistviewNotifySelect(l,s) \
	vclassSend(vlistviewGetClass(l), vlistviewNOTIFY_SELECT, (l,s))

#define vlistviewDrawMoveCursor(l,oi,ni) \
	vclassSend(vlistviewGetClass(l), vlistviewDRAW_MOVE_CURSOR, (l,oi,ni))

#define vlistviewSetHorzBar(l,oo) \
	vclassSend(vlistviewGetClass(l), vlistviewSET_HORZ_BAR, (l,oo))

#define vlistviewSetVertBar(l,oo) \
	vclassSend(vlistviewGetClass(l), vlistviewSET_VERT_BAR, (l,oo))

#define vlistviewSetList(l,z) \
	vclassSend(vlistviewGetClass(l), vlistviewSET_LIST, (l,z))

#define vlistviewSetListOwned(l,z) \
	vclassSend(vlistviewGetClass(l), vlistviewSET_LIST_OWNED, (l,z))

#define vlistviewScrollAbsolute(l,x,y) \
	vclassSend(vlistviewGetClass(l), vlistviewSCROLL_ABSOLUTE, (l,x,y))

#define vlistviewInvalSelection(l,s) \
	vclassSend(vlistviewGetClass(l), vlistviewINVAL_SELECTION, (l, s))

#define vlistviewRedrawSelection(l,s,ss) \
	vclassSend(vlistviewGetClass(l), vlistviewREDRAW_SELECTION, (l, s, ss))

#define vlistviewSetSelection(l,s) \
	vclassSend(vlistviewGetClass(l), vlistviewSET_SELECTION, (l, s))

#define vlistviewSetSelectNotify(l,n) \
	vclassSend(vlistviewGetClass(l), vlistviewSET_SELECT_NOTIFY, (l,n))

#define vlistviewDrawCellContents(l,r,c,s,t) \
	vclassSend(vlistviewGetClass(l), vlistviewDRAW_CELL_CONTENTS, \
		   (l,r,c,s,t))

#define vlistviewDrawCellContentsWith(l,r,c,s,t,x) \
	vclassSend(vlistviewGetClass(l), vlistviewDRAW_CELL_CONTENTS_WITH, \
		   (l,r,c,s,t,x))

#define vlistviewSetRowHeight(l,r,h) \
	vclassSend(vlistviewGetClass(l), vlistviewSET_ROW_HEIGHT, (l,r,h))

#define vlistviewSetColumnWidth(l,c,w) \
	vclassSend(vlistviewGetClass(l), vlistviewSET_COLUMN_WIDTH, (l,c,w))

#define vlistviewSetScrollBarMargin(l,m) \
	vclassSend(vlistviewGetClass(l), vlistviewSET_SCROLL_BAR_MARGIN, (l,m))

#define vlistviewSetCellContentProc(l,p) \
	vclassSend(vlistviewGetClass(l), vlistviewSET_CELL_CONTENT_PROC, (l,p))

#define vlistviewSetSelectionFilter(l,f) \
	vclassSend(vlistviewGetClass(l), vlistviewSET_SELECTION_FILTER, (l,f))

#define vlistviewSetAutoScroll(l,o) \
	vclassSend(vlistviewGetClass(l), vlistviewSET_AUTO_SCROLL, (l,o))

#define vlistviewSetTraversalWrap(l,o) \
	vclassSend(vlistviewGetClass(l), vlistviewSET_TRAVERSAL_WRAP, (l,o))

#define vlistviewSetGrabbingHand(l,o) \
	vclassSend(vlistviewGetClass(l), vlistviewSET_GRABBING_HAND, (l,o))

#define vlistviewSetSelectionSense(l,o) \
	vclassSend(vlistviewGetClass(l), vlistviewSET_SELECTION_SENSE, (l,o))

#define vlistviewSetUseKeyboardSelection(l,o) \
	vclassSend(vlistviewGetClass(l), vlistviewSET_USE_KEYBOARD_SELECTION, \
		   (l,o))

#define vlistviewSetUseKeyboardTraversal(l,o) \
	vclassSend(vlistviewGetClass(l), vlistviewSET_USE_KEYBOARD_TRAVERSAL, \
		   (l,o))

#define vlistviewSetDrawingSelection(l,o) \
	vclassSend(vlistviewGetClass(l), vlistviewSET_DRAWING_SELECTION, (l,o))

#define vlistviewSetRearrange(l,t) \
	vclassSend(vlistviewGetClass(l), vlistviewSET_REARRANGE, (l,t))

#define vlistviewGetContentNaturalSize(l,w,h) \
	vclassSend(vlistviewGetClass(l), vlistviewGET_CONTENT_NATURAL_SIZE, \
		   (l,w,h))

#define vlistviewSetHorzGrid(l,o) \
	vclassSend(vlistviewGetClass(l), vlistviewSET_HORZ_GRID, (l,o))

#define vlistviewSetVertGrid(l,o) \
	vclassSend(vlistviewGetClass(l), vlistviewSET_VERT_GRID, (l,o))

#define vlistviewDetermineCellSize(l,r,c,w,h) \
	vclassSend(vlistviewGetClass(l), vlistviewDETERMINE_CELL_SIZE, \
		   (l,r,c,w,h))

#define vlistviewFilterSelection(l,s) \
	vclassSend(vlistviewGetClass(l), vlistviewFILTER_SELECTION, (l,s))

#define vlistviewSetSizes(l,s) \
	vclassSend(vlistviewGetClass(l), vlistviewSET_SIZES, (l,s))

#define vlistviewSetUpdateMode(l,m) \
	vclassSend(vlistviewGetClass(l), vlistviewSET_UPDATE_MODE, (l,m))

#define _vlistviewSendCreateScrollBar(l) \
	vclassSend(vlistviewGetClass(l), vlistviewCREATE_SCROLL_BAR, (l))

#define _vlistviewGetDefaultSelectionInset(l) \
	vclassGet(vlistviewGetClass(l), vlistviewSELECTION_INSET)

#define _vlistviewGetDefaultBorderInset(l) \
	vclassGet(vlistviewGetClass(l), vlistviewBORDER_INSET)

#define _vlistviewGetDefaultCellContentIndent(l) \
	vclassGet(vlistviewGetClass(l), vlistviewCELL_CONTENT_INDENT)

/* deprecated */

#define vlistviewDrawBorder(l,rt) \
	vclassSend(vlistviewGetClass(l), vlistviewDRAW_BORDER, (l,rt))

#define vlistviewDrawBorderWith(l,rt,c) \
	vclassSend(vlistviewGetClass(l), vlistviewDRAW_BORDER_WITH, (l,rt,c))

#define vlistviewGetDecorationSizes(l,t,L,b,r) \
	vclassSend(vlistviewGetClass(l), vlistviewGET_DECORATION_SIZES, \
                   (l,t,L,b,r))


vportEND_CPLUSPLUS_EXTERN_C


#endif

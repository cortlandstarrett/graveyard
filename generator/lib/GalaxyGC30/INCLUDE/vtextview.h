/* $Id: vtextview.h,v 1.160 1997/09/30 19:10:34 robert Exp $ */

/************************************************************
  
  vtextview.h
  C Interface to the Text Manager
  
  (c) Copyright Visix Software  1991
  All rights reserved
  
  ************************************************************/

#ifndef vtextviewINCLUDED
#define vtextviewINCLUDED 1

#ifndef  vportINCLUDED		/* for v*HEADER */
#include <vport.h>
#endif

#ifndef  vstdINCLUDED		/* for vbool */
#include vstdHEADER
#endif

#ifndef  vstrINCLUDED
#include vstrHEADER
#endif

#ifndef  vrectINCLUDED
#include vrectHEADER
#endif

#ifndef  vtextINCLUDED
#include vtextHEADER
#endif

#ifndef  vdrawINCLUDED
#include vdrawHEADER
#endif

#ifndef  vclassINCLUDED
#include vclassHEADER
#endif

#ifndef  vclientINCLUDED
#include vclientHEADER
#endif

#ifndef  vdialogINCLUDED
#include vdialogHEADER
#endif

#ifndef  vtimerINCLUDED
#include vtimerHEADER
#endif

#ifndef  vresourceINCLUDED
#include vresourceHEADER
#endif

#ifndef  vsliderINCLUDED
#include vsliderHEADER
#endif

#ifndef  vclipboardINCLUDED
#include vclipboardHEADER
#endif

#ifndef  vundoINCLUDED
#include vundoHEADER
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * * * * * * * * * * PUBLIC CONSTANT DEFINITIONS * * * * * * * * * *
 */

/* Text view command selector values */

enum {
    vtextviewSELECT_MOVE_FOCUS        = vdialogITEM_NEXT_SELECT,
    vtextviewSELECT_NEXT_WORD,
    vtextviewSELECT_PREVIOUS_WORD,
    vtextviewSELECT_START_OF_LINE,
    vtextviewSELECT_END_OF_LINE,
    vtextviewSELECT_TOP_OF_VIEW,
    vtextviewSELECT_BOTTOM_OF_VIEW,
    vtextviewSELECT_SELECT_RANGE,
    vtextviewSELECT_GOTO_LINE,
    vtextviewSELECT_APPLY_STYLE,
    vtextviewSELECT_APPLY_RULER,
    vtextviewSELECT_SELECT_ALL,
    vtextviewSELECT_TRANSPOSE,
    vtextviewSELECT_DISPLAY_SELECTION,
    vtextviewSELECT_DELETE_LINE,
    vtextviewSELECT_DELETE_TO_EOLN,
    vtextviewSELECT_DELETE_CHAR,
    vtextviewSELECT_NEW_LINE,
    vtextviewSELECT_LINE_UP,
    vtextviewSELECT_LINE_DOWN,
    vtextviewSELECT_BACKSPACE,
    vtextviewSELECT_RECTANGULAR,
    vtextviewSELECT_OVERSTRIKE,
    vtextviewSELECT_AUTO_INDENT,
    vtextviewSELECT_SHIFT,
    vtextviewSELECT_UPPER_CASE,
    vtextviewSELECT_LOWER_CASE,
    vtextviewSELECT_CAPITALIZE,
    vtextviewSELECT_TOGGLE_CASE,
    vtextviewSELECT_SHOW_INVISIBLES,
    vtextviewSELECT_SHOW_KEYCODE,
    vtextviewSELECT_SHOW_HIDDEN_TEXT,
    vtextviewSELECT_SORT_LINES,
    vtextviewSELECT_RETURN,
    vtextviewSELECT_TAB,
    vtextviewSELECT_SPACE,
    vtextviewSELECT_DRAG_DROP_EDIT,
    vtextviewSELECT_DUPLICATE,
    vtextviewSELECT_SELECT_BLOCK,
    vtextviewSELECT_EXTEND_SELECT,
    vtextviewSELECT_ADD_MODE,
    vtextviewNEXT_SELECT
};

/* Values for 'active' parameter to vtextviewActivate() */

enum {
    vtextviewDEACTIVATE		= 0x0001,
    vtextviewACTIVATE		= 0x0002,
    vtextviewSILENT_ACTIVATE	= 0x0004
};

/* Values for 'hiliteTo' parameter to vtextviewSetHiliteTo() */

enum {
    vtextviewDEFAULT_HILITE_TO		= 0,
    vtextviewTO_END_OF_LINE		= 1,
    vtextviewTO_END_OF_SCREEN		= 2
};

/* Values for 'scrollTo' parameter to vtextviewSetScrollTo() */

enum {
    vtextviewSCROLL_TO_CENTER	= 0,
    vtextviewSCROLL_TO_TOP	= 1,
    vtextviewSCROLL_TO_BOTTOM	= 2
};

/* Values for 'hiliteStyle' parameter to vtextviewSetHiliteStyle() */

enum {
    vtextviewDEFAULT_HILITE	= 0,
    vtextviewINVERT_HILITE	= 1,
    vtextviewLINE_HILITE	= 2,
    vtextviewBOX_HILITE		= 3,
    vtextviewNO_HILITE		= 4,
    vtextviewDOT_LINE_HILITE	= 5
};

/* values for modes of drawing the hilite */
enum {
   vtextviewDRAW_HILITE_DEFAULT      = 0,
   vtextviewDRAW_HILITE_REPAINT      = 1,
   vtextviewDRAW_HILITE_INVERT       = 2
};

/* Values for 'options' parameter to vtextviewScrollToStart() */

enum {
    _vtextviewSTS_SET_ONLY	= 0x0001,
    vtextviewSTS_ALWAYS 	= 0x0002,
    vtextviewSTS_HORIZONTAL	= 0x0008,
    vtextviewSTS_VERTICAL	= 0x0010
};

/* Values for 'state' parameter to vtextviewHiliteCaret() */

enum {
    vtextviewCLEAR_CARET		= 0,
    vtextviewHILITE_CARET		= 1,
    vtextviewREDRAW_CARET		= 2,
    vtextviewHILITE_CARET_IN_HILITE	= 3
};

/* Values for 'direction' parameter to vtextviewMoveCursor() */

enum {
    vtextviewLEFT		= 0,
    vtextviewUP			= 1,
    vtextviewRIGHT		= 2,
    vtextviewDOWN		= 3
};

/* Value for message parameter to Notify function */

enum {
    vtextviewVSCROLL_NOTIFY	= 1,
    vtextviewHSCROLL_NOTIFY	= 2,
    vtextviewACCEPT_NOTIFY	= 3,
    vtextviewUPDATE_NOTIFY	= 4,
    vtextviewSELECT_NOTIFY	= 5,
    vtextviewBUTTON_UP_NOTIFY	= 6,
    vtextviewBUTTON_DOWN_NOTIFY	= 7,
    vtextviewNEXT_NOTIFY
};

/* Values for sense parameter to vtextviewPerformQuickTranferText */

enum {
    vtextviewQUICK_TRANSFER_IN	= 1,
    vtextviewQUICK_TRANSFER_OUT	= 2
};

#define vtextview_Append          (_vtextviewPredefs[_vtextview_Append])
#define vtextview_Amount          (_vtextviewPredefs[_vtextview_Amount])
#define vtextview_AmountArray     (_vtextviewPredefs[_vtextview_AmountArray])
#define vtextview_Direction       (_vtextviewPredefs[_vtextview_Direction])
#define vtextview_Left            (_vtextviewPredefs[_vtextview_Left])
#define vtextview_Right           (_vtextviewPredefs[_vtextview_Right])
#define vtextview_LeftMargin      (_vtextviewPredefs[_vtextview_LeftMargin])
#define vtextview_TopMargin       (_vtextviewPredefs[_vtextview_TopMargin])
#define vtextview_ScrollTo	  (_vtextviewPredefs[_vtextview_ScrollTo])
#define vtextview_UnfocusHilite	  (_vtextviewPredefs[_vtextview_UnfocusHilite])
#define vtextview_FocusHilite	  (_vtextviewPredefs[_vtextview_FocusHilite])
#define vtextview_HiliteTo	  (_vtextviewPredefs[_vtextview_HiliteTo])
#define vtextview_ScrollBarMargin (_vtextviewPredefs[_vtextview_ScrollBarMargin])
#define vtextview_Linenumber	  (_vtextviewPredefs[_vtextview_Linenumber])
#define vtextview_Words	  	  (_vtextviewPredefs[_vtextview_Words])
#define vtextview_Lines		  (_vtextviewPredefs[_vtextview_Lines])
#define vtextview_DragDropEdit	  (_vtextviewPredefs[_vtextview_DragDropEdit])
#define vtextview_AutoInsert	  (_vtextviewPredefs[_vtextview_AutoInsert])
#define vtextview_AddMode	  (_vtextviewPredefs[_vtextview_AddMode])

/*
 * * * * * * * * * * PUBLIC TYPE DEFINITIONS * * * * * * * * * *
 */

typedef struct vtextview          vtextview;
typedef struct vtextviewClass     vtextviewClass;
typedef vtextObserver		  vtextviewTextObserver;

typedef void (*vtextviewNoteProc)(
    vtextview 		*textView,
    vevent 		*event,
    int 		message
    );

typedef void (*vtextviewUndoNoteProc)(
    vtextview 		*textView,
    vundoAction 	*action
    );

/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */

void vtextviewStartup(void);


/* Text View Class Functions */

vtextviewClass *vtextviewGetDefaultClass(void);

vtextObserverClass *vtextviewGetDefaultObserverClass(void);

/* Initialization and allocation */

vtextview *vtextviewCreate(void);

vtextview *vtextviewCreateOfClass(
    vtextviewClass	*clas
    );

vtextview *vtextviewClone(
    vtextview	    	*textView
    );

void vtextviewCopy(
    vtextview	    	*textView,
    vtextview	    	*targetView
    );

void vtextviewCopyInit(
    vtextview	    	*textView,
    vtextview	    	*targetView
    );

void vtextviewInit(
    vtextview	    	*textView
    );

void vtextviewInitOfClass(
    vtextview		*textView,
    vtextviewClass	*clas
    );

void vtextviewDestroy(
    vtextview	    	*textView
    );

vtextview *vtextviewLoad(
    vresource		resource
    );

void vtextviewLoadInit(
    vtextview		*textView,
    vresource		resource
    );

void vtextviewStore(
    vtextview		*textView,
    vresource		resource
    );

/* Text display and scrolling */

void vtextviewDraw(
    vtextview	    	*textView
    );

vbool vtextviewScroll(
    vtextview	    	*textView,
    long	    	scrollToLineNum,
    int		    	scrollToHPos
    );

void vtextviewPageScroll(
    vtextview           *textView,
    int                direction
    );

void vtextviewScrollToStart(
    vtextview	    	*textView,
    int 	    	options
    );

void vtextviewMoveCursor(
    vtextview		*textView,
    int 		direction
    );

void vtextviewMoveCursorToEnd(
    vtextview		*textview,
    int 		direction
    );

vrect *vtextviewClip(
    vtextview	    	*textView
    );


/* Text attribute modification */

void vtextviewSetNotify(
    vtextview           *textView,
    vtextviewNoteProc   noteProc
    );

void vtextviewSetUndoNotify(
    vtextview			 *textView,
    vtextviewUndoNoteProc 	 undoNotifyProc
    );

void vtextviewSetData(
    vtextview	    	*textView,
    void	    	*data
    );

void vtextviewSetTextData(
    vtextview	    	*textView,
    vtext	    	*editRec
    );

void vtextviewSetTextDataOwned(
    vtextview	    	*textView,
    vtext	    	*editRec
    );

void vtextviewSetSelection(
    vtextview		*textView,
    vtextSelection	*selection
    );

void vtextviewSetSelectionOwned(
    vtextview		*textView,
    vtextSelection	*selection
    );

void vtextviewSetObserver(
    vtextview		*textView,
    vtextObserverClass	*observerClass
    );

void vtextviewSetLeftMargin(
    vtextview	    	*textView,
    int 	    	leftMargin
    );

void vtextviewSetTopMargin(
    vtextview	    	*textView,
    int 	    	topMargin
    );

void vtextviewSetGrabbingHand(
    vtextview	    	*textView,
    int 	    	hasGrabbingHand
    );

void vtextviewSetDragDropEdit(
    vtextview	    	*textView,
    int 	    	dragDropEdit
    );

void vtextviewSetAddMode(
    vtextview	    	*textView,
    int 	    	onOff
    );

void vtextviewSetAutoScroll(
    vtextview	    	*textView,
    int 	    	autoScrollOn
    );

void vtextviewSetAutoInsert(
    vtextview	    	*textView,
    int 	    	autoInsert
    );

void vtextviewSetBlink(
    vtextview	    	*textView,
    unsigned long	 seconds,
    unsigned long	 nanoseconds
    );

void vtextviewSetHorzBar(
    vtextview		*textView,
    int 		hasHorzBar
    );

void vtextviewSetVertBar(
    vtextview		*textView,
    int 		hasVertBar
    );

void vtextviewSetHorzLocked(
    vtextview	    	*textView,
    int 	    	horzLocked
    );

void vtextviewSetVertLocked(
    vtextview	    	*textView,
    int 	    	vertLocked
    );

void vtextviewSetHorzLockedOverride(
    vtextview	    	*textView,
    int 	    	horzLocked
    );

void vtextviewSetVertLockedOverride(
    vtextview	    	*textView,
    int 	    	vertLocked
    );

void vtextviewSetHiliteTo(
    vtextview	    	*textView,
    int 	    	hiliteTo
    );

void vtextviewSetScrollTo(
    vtextview	    	*textView,
    int 	    	scrollTo
    );

void vtextviewSetDrawHiliteStyle(
    vtextview	    	*textView,
    int			drawHiliteStyle
    );

void vtextviewSetHiliteStyle(
    vtextview	    	*textView,
    int 	    	hiliteStyle
    );

void vtextviewSetUnhiliteStyle(
    vtextview	    	*textView,
    int 	    	unhiliteStyle
    );

void vtextviewSetScrollBarMargin(
    vtextview		*textView,
    int			margin
    );

void vtextviewSetOffscreenDrawing(
    vtextview		*textView,
    int 		useOffscreenDrawing
    );

/* Text View attribute access */

vtextviewClass *vtextviewGetClass(
    vtextview	    	*textView
    );

vtextviewNoteProc vtextviewGetNotify(
    vtextview           *textView
    );

vtextviewUndoNoteProc vtextviewGetUndoNotify(
    vtextview		*textView
    );

void *vtextviewGetData(
    vtextview	    	*textView
    );

vtext *vtextviewGetTextData(
    vtextview	   	*textView
    );

vtextSelection *vtextviewGetSelection(
    vtextview	    	*textView
    );

vtextObserverClass *vtextviewGetObserver(
    vtextview	    	*textView
    );

short vtextviewGetLeftMargin(
    vtextview	    	*textView
    );

short vtextviewGetTopMargin(
    vtextview	    	*textView
    );

vbool vtextviewHasGrabbingHand(
    vtextview	    	*textView
    );

vbool vtextviewHasDragDropEdit(
    vtextview	    	*textView
    );

vbool vtextviewHasAddMode(
    vtextview	    	*textView
    );

vbool vtextviewIsAutoScroll(
    vtextview	    	*textView
    );

vbool vtextviewIsAutoInsert(
    vtextview	    	*textView
    );

unsigned long vtextviewGetBlinkSeconds(
    vtextview	    	*textView
    );

unsigned long vtextviewGetBlinkNanoseconds(
    vtextview	    	*textView
    );

vbool vtextviewHasHorzBar(
    vtextview		*textView
    );

vbool vtextviewHasVertBar(
    vtextview		*textView
    );

vcontrol *vtextviewGetHorzScrollbar(
    vtextview		*textView
    );

vcontrol *vtextviewGetVertScrollbar(
    vtextview		*textView
    );

vbool vtextviewIsHorzLocked(
    vtextview	    	*textView
    );

vbool vtextviewIsVertLocked(
    vtextview	    	*textView
    );

vbool vtextviewIsHorzLockedOverride(
    vtextview	    	*textView
    );

vbool vtextviewIsVertLockedOverride(
    vtextview	    	*textView
    );

vbyte vtextviewGetHiliteTo(
    vtextview	    	*textView
    );

vbyte vtextviewGetScrollTo(
    vtextview	    	*textView
    );

vbyte vtextviewGetDrawHiliteStyle(
    vtextview	    	*textView
    );

vbyte vtextviewGetHiliteStyle(
    vtextview	    	*textView
    );

vbyte vtextviewGetUnhiliteStyle(
    vtextview	    	*textView
    );

short vtextviewGetScrollBarMargin(
    vtextview	   	*textView
    );

vbool vtextviewIsOffscreenDrawing(
    vtextview		*textView
    );


/* Text view operations */

void vtextviewActivate(
    vtextview	    	*textView,
    int 	    	active
    );

vbool vtextviewIsActive(
    vtextview	    	*textView
    );

void vtextviewHiliteCaret(
    vtextview	    	*textView,
    int		    	state
    );

void vtextviewSetCaret(
    vtextview	    	*textView
    );

void vtextviewUpdateControls(
    vtextview	    	*textView
    );

void vtextviewInval(
    vtextview	    	*textView
    );

void vtextviewCursorTrack(
    vtextview	    	*textView
    );

/* Accessing the text view object */

long vtextviewSelStart(
    vtextview	    	*textView
    );

long vtextviewSelEnd(
    vtextview	    	*textView
    );

long vtextviewGetTopLineNum(
    vtextview	    	*textView
    );

void vtextviewSetTopLineNum(
    vtextview	    	*textView,
    long	    	topLineNum
    );

short vtextviewGetHPosition(
    vtextview	    	*textView
    );

void vtextviewSetHPosition(
    vtextview	    	*textView,
    int 	    	hPosition
    );

vrect *vtextviewGetRect(
    vtextview	    	*textView
    );

vrect *vtextviewGetTextRect(
    vtextview	    	*textView
    );

short vtextviewLines(
    vtextview	    	*textView
    );

short vtextviewLineInScreen(
    vtextview	    	*textView
    );

long vtextviewWindowLine(
    vtextview	    	*textView
    );

/* Other */

void vtextviewCalcBoundingRect(
    vtextview		*textView,
    long		startLine,
    long		endLine,
    vrect               *boundingRect
    );

void vtextviewMapPointToPosition(
    vtextview		*textView,
    vpoint		*pt,
    long		*pos,
    long		*lineNum
    );

long vtextviewGetPositionAtPoint(
    vtextview		*textView,
    vpoint		*pt
    );

long vtextviewGetLineAtPoint(
    vtextview		*textView,
    vpoint		*pt
    );

void vtextviewPerformCutText(
    vtextview	    	*textView
    );

void vtextviewPerformCopyText(
    vtextview	    	*textView
    );

void vtextviewPerformPasteText(
    vtextview	    	*textView
    );

void vtextviewPerformClearText(
    vtextview	    	*textView
    );

void vtextviewPerformDuplicateText(
    vtextview	    	*textView
    );

void vtextviewPerformQuickTransferText(
    vtextview	    	*textView,
    int			sense,
    vpoint		*point
    );

vclipboard *vtextviewGetClipboard(void);

void vtextviewNotify(
    vtextview		*textView,
    vevent		*event,
    int			message
    );

void vtextviewNotifyUndo(
    vtextview		*textView,
    vscribe		*actionName
    );

vtextObserver *vtextviewObserver(
    vtextview	    	*textView
    );

vdialogItem *vtextviewGetItem(
    vtextview		*textView
    );


/*
 * * * * * * * * * * PRIVATE CONSTANT DEFINITIONS * * * * * * * * * *
 */

/* Values for 'attributes' in an vtextview */

enum {
    _vtextviewAUTO_SCROLL		= 0x00000001,
    _vtextviewHORZ_LOCKED		= 0x00000002,
    _vtextviewVERT_LOCKED		= 0x00000004,
    _vtextviewDRAG_DROP_EDIT		= 0x00000008,
    _vtextviewGRABBING_HAND		= 0x00000040,
    _vtextviewHAS_HORZ_BAR		= 0x00000080,
    _vtextviewHAS_VERT_BAR		= 0x00000100,
    _vtextviewAUTO_INSERT		= 0x00000200,
    _vtextviewOFFSCREEN_DRAWING		= 0x00001000,
    _vtextviewTRACKING			= 0x00002000,
    _vtextviewSCROLLBAR_MARGIN_SET	= 0x00004000,
    _vtextviewOLD_OBSERVER_CLASS	= 0x00008000,
    _vtextviewHAS_FOCUS_HILITE		= 0x00010000,
    _vtextviewHAS_DIFF_SELECTION	= 0x00020000,
    _vtextviewPREVIOUS_LINE_CARET	= 0x00040000,
    _vtextviewCURSOR_ADDED		= 0x00080000,
    _vtextviewHORZ_LOCKED_OVERRIDE	= 0x00100000,
    _vtextviewVERT_LOCKED_OVERRIDE	= 0x00200000,
    _vtextviewADD_MODE			= 0x00400000,
    _vtextviewIN_EDITING_MODE		= 0x00800000
};

/* Text view preferences */

enum {
    _vtextviewPREF_DRAG_DROP_EDIT          = 0,
    _vtextviewPREF_AUTO_INSERT_SPACES      = 1,
    _vtextviewPREF_HILITE_STYLE            = 2,
    _vtextviewPREF_UNHILITE_STYLE          = 3,
    _vtextviewPREF_HILITE_TO               = 4
};

/*
 * Global text view strings
 */

enum {
    _vtextview_Append,
    _vtextview_Amount,
    _vtextview_AmountArray,
    _vtextview_Direction,
    _vtextview_Left,
    _vtextview_Right,
    _vtextview_Select,
    _vtextview_LeftMargin,
    _vtextview_TopMargin,
    _vtextview_ScrollTo,
    _vtextview_UnfocusHilite,
    _vtextview_FocusHilite,
    _vtextview_HiliteTo,
    _vtextview_ScrollBarMargin,
    _vtextview_Linenumber,
    _vtextview_Words,
    _vtextview_Lines,
    _vtextview_DragDropEdit,
    _vtextview_AutoInsert,
    _vtextview_AddMode,
    _vtextview_Count
};


/*
 * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * *
 */

/*
 * _vtextviewScreenCache
 *
 * This information is generated for every visible line in the current view
 */

typedef struct _vtextviewScreenCache {
    vtextLineMetricRec  metrics;
    int			linenumber;
} _vtextviewScreenCache;


typedef struct _vtextviewInput _vtextviewInput;


struct vtextview {

    vdialogItem 	item;
    vrect		viewRect;
    int			hPosition;
    long		topLineNum;	/* Line # of top line in view        */
    short		leftMargin;	/* Left margin within a viewRect     */
    short		topMargin;	/* Top margin within a viewRect	     */

    vtextObserverClass  *observerClass;
    vtextviewNoteProc	noteProc;
    vtextviewUndoNoteProc undoNotifyProc;

    vimage  	    		 *offscreenBuffer;
    _vtextviewScreenCache 	 *screenCache;
    short			 cacheLineCount;

    vrect	caretRect;	/* X,Y position of cursor in the Window      */
    short	cursorX;	/* Kept for doing up/down cursoring tracking */
    vrect	cursorRect;

    vbyte		scrollTo;

    vbyte		focusHiliteStyle;
    vbyte		unfocusHiliteStyle;
    vbyte		drawHiliteStyle;
    vbyte		hiliteTo;

    unsigned int	attributes;

    vbool		ownedSelection;
    vbool		ownedTextData;
    vtextSelection     	*selection;
    vtext		*textData;
    vtextObserver       *observer;

    vsliderScrollBar	*hBar;
    vsliderScrollBar	*vBar;

    _vtextviewInput	*input;
    vtextSelection     	*previousSelection;

    vbyteSigned		scrollBarMargin;

    vbyte		activeLevel;     /* nested activate/deactivates */
    vbyte		caretState;
    vbyte		caretBehavior;   
};

/*
 * Text View Class Definition
 */

#define vtextviewCLASS(SUPER, ITEM, NOTIFY)				     \
    vdialogITEM_CLASS(SUPER, ITEM, NOTIFY);				     \
    vclassVARIABLE(vtextviewBORDER_INSET,  short);			     \
    vclassVARIABLE(vtextviewCURSOR,        vcursor*);                        \
    vclassMETHOD_RET(vtextviewCREATE_SCROLL_BAR, vsliderScrollBar *,	     \
		     (ITEM *textview));					     \
    vclassMETHOD(vtextviewDRAW_CARET_WITH,                                   \
		 (ITEM *textview, vrect *caret, vdrawcontext *context));     \
    vclassMETHOD(vtextviewDRAW_BACKGROUND_WITH,                              \
		 (ITEM *textview, vrect *area, vdrawcontext *context));      \
    vclassMETHOD(vtextviewDRAW_HILITE_WITH,                                  \
		 (ITEM *textview, vrect *r, 	                             \
		  int hilitestyle, vdrawcontext *context));		     \
    vclassMETHOD(vtextviewDRAW_LINE_WITH,  (ITEM *textview, 		     \
					    vtextLineMetricRec *lineInfo,    \
					    vdrawcontext *context));         \
    vclassMETHOD(vtextviewDRAW_RUN_EXTRA_WITH,(ITEM *textview, 		     \
					    vtextLineMetricRec *lineInfo,    \
					    vchar *text, int length,         \
					    vtextStyle *style,               \
					    vrect *rect, int selectionOn,    \
					    vdrawcontext *context));         \
    vclassMETHOD(vtextviewDRAW_RUN_WITH,   (ITEM *textview, vchar *text,     \
					    int length, vtextStyle *style,   \
					    vdrawcontext *context));         \
    vclassMETHOD(vtextviewDRAW_CARET,      (ITEM *textview, vrect *caret));  \
    vclassMETHOD(vtextviewDRAW_BACKGROUND, (ITEM *textview, vrect *area));   \
    vclassMETHOD(vtextviewDRAW_HILITE,	   (ITEM *textview, vrect *r, 	     \
					    int hilitestyle));		     \
    vclassMETHOD(vtextviewDRAW_LINE,	   (ITEM *textview, 		     \
					    vtextLineMetricRec *lineInfo));  \
    vclassMETHOD(vtextviewDRAW_RUN,	   (ITEM *textview, vchar *text,     \
					    int length, vtextStyle *style)); \
    vclassMETHOD(vtextviewUSE_STYLE,	   (ITEM *textview,		     \
					    vtextStyle *style));	     \
    vclassMETHOD(vtextviewACTIVATE,        (ITEM *textview, int activate));  \
    vclassMETHOD(vtextviewHILITE_CARET,    (ITEM *textview, int state));     \
    vclassMETHOD(vtextviewSET_CARET,       (ITEM *textview));		     \
    vclassMETHOD(vtextviewUPDATE_CONTROLS, (ITEM *textview));		     \
    vclassMETHOD_RET(vtextviewSCROLL,vbool,(ITEM *textview, long lineNumber, \
					    int hPosition));    	     \
    vclassMETHOD(vtextviewSCROLL_TO_START, (ITEM *textview, int options));   \
    vclassMETHOD(vtextviewMOVE_CURSOR,	   (ITEM *textview, int direction)); \
    vclassMETHOD(vtextviewMOVE_CURSOR_TO_END,(ITEM *textview, int direction));\
    vclassMETHOD(vtextviewSET_TEXT_DATA,   (ITEM *textview, vtext *text));   \
    vclassMETHOD(vtextviewSET_TEXT_DATA_OWNED,				     \
					   (ITEM *textview, vtext *text));   \
    vclassMETHOD(vtextviewCALC_CURSOR_RECT,(ITEM *textview, vrect *rect));   \
    vclassMETHOD(vtextviewNOTIFY,          (ITEM *textview, vevent *event,   \
					    int message));		     \
    vclassMETHOD(vtextviewPERFORM_CUT_TEXT,				     \
		 (ITEM *textview));					     \
    vclassMETHOD(vtextviewPERFORM_COPY_TEXT,				     \
		 (ITEM *textview));					     \
    vclassMETHOD(vtextviewPERFORM_PASTE_TEXT,				     \
		 (ITEM *textview));					     \
    vclassMETHOD(vtextviewPERFORM_CLEAR_TEXT,				     \
		 (ITEM *textview));					     \
    vclassMETHOD(vtextviewPERFORM_DUPLICATE_TEXT,			     \
		 (ITEM *textview));					     \
    vclassMETHOD(vtextviewPERFORM_QUICK_TRANSFER_TEXT,			     \
		 (ITEM *textview, int sense, vpoint *point));		     \
    vclassMETHOD(vtextviewOBSERVE_ACTION,  (ITEM *textview,		     \
					    vundoAction *action));	     \
    /* deprecated methods */                                                 \
    vclassMETHOD(vtextviewDRAW_BORDER,     (ITEM *textview, vrect *border)); \
    vclassMETHOD(vtextviewDRAW_BORDER_WITH,                                  \
		 (ITEM *textview, vrect *border, vdrawcontext *context))


struct vtextviewClass {
    vtextviewCLASS(struct vtextviewClass, vtextview, vtextviewNoteProc);
};

vportALIAS(vtextviewTextObserver, vtextObserver)

/*
 * * * * * * * * * * PRIVATE FUNCTION PROTOTYPES * * * * * * * * * *
 */

void vtextviewSetObserverClass(vtextview *textView, vtextObserverClass *clas);
vtextObserverClass *vtextviewGetObserverClass(vtextview *textView);

void _vtextviewSendObserveAction(vtextview *textView, vundoAction *action);

vsliderScrollBar *_vtextviewSendCreateScrollBar(vtextview *textView);

vobjectPartialChildIteratorClass *_vtextviewGetPartialChildIteratorClass(void);

/*
 * * * * * * * * * TEXT MANAGER GLOBAL VARIABLES * * * * * * * * * *
 */

extern vportLINK const vchar 		*_vtextviewPredefs[];
extern vportLINK const vexClass		_vtextviewNoTextDataExceptionClass; 

/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * *
 */

#define vtextviewGetItem(e)		vportBASE_OBJECT(e, item)

#define vtextviewCreateOfClass(c)	\
	((vtextview *) vdialogCreateItemOfClass((vdialogItemClass *) (c)))
#define vtextviewCreate()	       \
        vtextviewCreateOfClass(vtextviewGetDefaultClass())

#define vtextviewClone(v)		\
	((vtextview *) vdialogCloneItem((vdialogItem *) (v)))

#define vtextviewInitOfClass(e,c)	\
	vdialogInitItemOfClass((vdialogItem  *) (e), (vdialogItemClass *) (c))
#define vtextviewInit(e)	vtextviewInitOfClass(e, \
					   vtextviewGetDefaultClass());
#define vtextviewCopyInit(v,t)  vdialogCopyInitItem(vtextviewGetItem(v), \
						    vtextviewGetItem(t))
#define vtextviewLoad(v)        ((vtextview*)vdialogLoadItem(v))
#define vtextviewLoadInit(v,r)  vdialogLoadInitItem(vtextviewGetItem(v), r)
#define vtextviewDestroy(v)	vdialogDestroyItem(vtextviewGetItem(v))

#define vtextviewSetLeftMargin(e,m)	((e)->leftMargin = (m))
#define vtextviewSetTopMargin(e,m)	((e)->topMargin = (m))
#define vtextviewSetScrollTo(e,s)	((e)->scrollTo = (s))

#define vtextviewGetData(e)      	vdialogGetItemData(vtextviewGetItem(e))
#define vtextviewGetClass(e)		((vtextviewClass*)vdialogGetItemClass \
					 ((vdialogItem *) (e)))
#define vtextviewGetNotify(e)  	   ((e)->noteProc)

#define vtextviewGetTextData(e)		((e)->textData)
#define vtextviewGetSelection(e)	((e)->selection)
#define vtextviewGetLeftMargin(e)	((e)->leftMargin)
#define vtextviewGetTopMargin(e)	((e)->topMargin)

#define vtextviewGetScrollTo(e)		((e)->scrollTo & 0xF)

#define vtextviewGetDrawHiliteStyle(e)	((e)->drawHiliteStyle & 0xF)
#define vtextviewGetHiliteStyle(e)	((e)->focusHiliteStyle & 0xF)
#define vtextviewGetUnhiliteStyle(e)	((e)->unfocusHiliteStyle & 0xF)

#define vtextviewGetHiliteTo(e)		((e)->hiliteTo & 0xF)

#define _vtextviewGetActualDrawHiliteStyle(e) \
(((e)->drawHiliteStyle >> 4) & 0xF)

#define _vtextviewGetActualHiliteStyle(e) \
(((e)->focusHiliteStyle >> 4) & 0xF)

#define _vtextviewGetActualUnhiliteStyle(e) \
(((e)->unfocusHiliteStyle >> 4) & 0xF)

#define _vtextviewGetActualHiliteTo(e)	(((e)->hiliteTo >> 4) & 0xF)

#define vtextviewGetScrollBarMargin(e)	((e)->scrollBarMargin)

#define vtextviewObserver(e)			((e)->observer)
#define vtextviewGetObserverClass(e)		((e)->observerClass)
#define vtextviewGetObserver(e)			((e)->observerClass)
#define vtextviewSetObserver(e, c)		((e)->observerClass = (c))
#define vtextviewSetObserverClass(e, c)	       \
    ((e)->attributes |= _vtextviewOLD_OBSERVER_CLASS, \
     (e)->observerClass = (c))

#define vtextviewSelStart(e)		vtextSelectionStart((e)->selection)
#define vtextviewSelEnd(e)		vtextSelectionEnd((e)->selection)
#define vtextviewGetTopLineNum(e)	((e)->topLineNum)
#define vtextviewGetHPosition(e)	((e)->hPosition)
#define vtextviewIsActive(e)		((e)->activeLevel > 0)

#define vtextviewInval(e)	 vdialogInvalItemRect(vtextviewGetItem(e), \
				 vtextviewGetRect(e), vwindowINVAL_OPAQUE)

#define vtextviewIsOffscreenDrawing(d)  \
	    	(((d)->attributes & _vtextviewOFFSCREEN_DRAWING) != 0)

#define vtextviewHasHorzBar(d)		((d)->hBar != NULL)
#define vtextviewHasVertBar(d)		((d)->vBar != NULL)
#define vtextviewGetHorzScrollbar(d)	((d)->hBar)
#define vtextviewGetVertScrollbar(d)	((d)->vBar)

#define vtextviewGetUndoNotify(e)   	((e)->undoNotifyProc)
#define vtextviewSetUndoNotify(e,p)   	((e)->undoNotifyProc = (p))

#define vtextviewSetAutoScroll(e,a)	(a ? 			\
		((e)->attributes |=  _vtextviewAUTO_SCROLL) :  	\
		((e)->attributes &= ~_vtextviewAUTO_SCROLL))
#define vtextviewSetAutoInsert(e,a)	(a ? 			\
		((e)->attributes |=  _vtextviewAUTO_INSERT) :  	\
		((e)->attributes &= ~_vtextviewAUTO_INSERT))
#define vtextviewSetHorzLocked(e,a)	(a ? 			\
		((e)->attributes |=  _vtextviewHORZ_LOCKED) :  	\
		((e)->attributes &= ~_vtextviewHORZ_LOCKED))
#define vtextviewSetVertLocked(e,a)	(a ? 			\
		((e)->attributes |=  _vtextviewVERT_LOCKED) :  	\
		((e)->attributes &= ~_vtextviewVERT_LOCKED))
#define vtextviewSetHorzLockedOverride(e,a)	(a ? 		\
		((e)->attributes |=  _vtextviewHORZ_LOCKED_OVERRIDE) : 	\
		((e)->attributes &= ~_vtextviewHORZ_LOCKED_OVERRIDE))
#define vtextviewSetVertLockedOverride(e,a)	(a ? 			\
		((e)->attributes |=  _vtextviewVERT_LOCKED_OVERRIDE) : 	\
		((e)->attributes &= ~_vtextviewVERT_LOCKED_OVERRIDE))
#define vtextviewSetGrabbingHand(e,a)	(a ? 			\
		((e)->attributes |=  _vtextviewGRABBING_HAND) : \
		((e)->attributes &= ~_vtextviewGRABBING_HAND))
#define vtextviewSetDragDropEdit(e,a)	(a ? 			 \
		((e)->attributes |=  _vtextviewDRAG_DROP_EDIT) : \
		((e)->attributes &= ~_vtextviewDRAG_DROP_EDIT))
#define vtextviewSetAddMode(e,a)	(a ? 			 \
		((e)->attributes |=  _vtextviewADD_MODE) : \
		((e)->attributes &= ~_vtextviewADD_MODE))

#define vtextviewIsAutoScroll(e)	\
		(((e)->attributes & _vtextviewAUTO_SCROLL) != 0)
#define vtextviewIsAutoInsert(e)	\
		(((e)->attributes & _vtextviewAUTO_INSERT) != 0)
#define vtextviewIsHorzLocked(e)	\
		(((e)->attributes & _vtextviewHORZ_LOCKED) != 0)
#define vtextviewIsVertLocked(e)	\
		(((e)->attributes & _vtextviewVERT_LOCKED) != 0)
#define vtextviewIsHorzLockedOverride(e)\
		(((e)->attributes & _vtextviewHORZ_LOCKED_OVERRIDE) != 0)
#define vtextviewIsVertLockedOverride(e)	\
		(((e)->attributes & _vtextviewVERT_LOCKED_OVERRIDE) != 0)
#define vtextviewHasGrabbingHand(e)	\
		(((e)->attributes & _vtextviewGRABBING_HAND) != 0)
#define vtextviewHasDragDropEdit(e)	\
		(((e)->attributes & _vtextviewDRAG_DROP_EDIT) != 0)
#define vtextviewHasAddMode(e)	\
		(((e)->attributes & _vtextviewADD_MODE) != 0)

/*
 * * * * * * * * * * PRIVATE FUNCTION MESSAGE DEFINITIONS * * * * * * * * * *
 */

#define vtextviewCopy(v,t)	 vclassSend(vtextviewGetClass(v), \
					    vobjectCOPY, (v, t))
#define vtextviewStore(v,r)      vclassSend(vtextviewGetClass(v), \
					    vobjectSTORE, (v, r))
#define vtextviewDraw(v)	 vclassSend(vtextviewGetClass(v), \
					    vdialogDRAW_ITEM, (v))
#define vtextviewActivate(v,d)	 vclassSend(vtextviewGetClass(v), \
					    vtextviewACTIVATE, (v,d))
#define vtextviewHiliteCaret(v,d) vclassSend(vtextviewGetClass(v),\
					    vtextviewHILITE_CARET, (v,d))
#define vtextviewSetCaret(v)	 vclassSend(vtextviewGetClass(v), \
					    vtextviewSET_CARET, (v))
#define vtextviewUpdateControls(v) vclassSend(vtextviewGetClass(v), \
					    vtextviewUPDATE_CONTROLS, (v))
#define vtextviewNotify(v,e,m)	 vclassSend(vtextviewGetClass(v), \
					    vtextviewNOTIFY, (v,e,m))
#define vtextviewSetTextData(v,t) vclassSend(vtextviewGetClass(v), \
					    vtextviewSET_TEXT_DATA, (v,t))
#define vtextviewSetTextDataOwned(v,t) vclassSend(vtextviewGetClass(v), \
					    vtextviewSET_TEXT_DATA_OWNED, (v,t))
#define vtextviewScroll(v,l,h)	 vclassSend(vtextviewGetClass(v), \
					    vtextviewSCROLL, (v,l,h))
#define vtextviewScrollToStart(v,d)   vclassSend(vtextviewGetClass(v), \
					    vtextviewSCROLL_TO_START, (v,d))
#define vtextviewMoveCursor(v,d)      vclassSend(vtextviewGetClass(v), \
					    vtextviewMOVE_CURSOR, (v,d))
#define vtextviewMoveCursorToEnd(v,d) vclassSend(vtextviewGetClass(v), \
					    vtextviewMOVE_CURSOR_TO_END, (v,d))
#define vtextviewSetData(e, d)	      vclassSend(vtextviewGetClass(e), \
					    vdialogSET_ITEM_DATA, (e,d))
#define vtextviewSetNotify(e,n)   ((e)->noteProc = (n))

#define vtextviewPerformCutText(v)       vclassSend(vtextviewGetClass(v), \
					      vtextviewPERFORM_CUT_TEXT, (v))
#define vtextviewPerformCopyText(v)      vclassSend(vtextviewGetClass(v), \
					      vtextviewPERFORM_COPY_TEXT, (v))
#define vtextviewPerformPasteText(v)     vclassSend(vtextviewGetClass(v), \
					      vtextviewPERFORM_PASTE_TEXT, (v))
#define vtextviewPerformClearText(v)     vclassSend(vtextviewGetClass(v), \
					      vtextviewPERFORM_CLEAR_TEXT, (v))
#define vtextviewPerformDuplicateText(v) vclassSend(vtextviewGetClass(v), \
					  vtextviewPERFORM_DUPLICATE_TEXT, (v))
#define vtextviewPerformQuickTransferText(v, s, p) 			\
   vclassSend(vtextviewGetClass(v), 					\
	      vtextviewPERFORM_QUICK_TRANSFER_TEXT, (v, s, p))

#define _vtextviewSendCreateScrollBar(v) vclassSend(vtextviewGetClass(v), \
					    vtextviewCREATE_SCROLL_BAR, (v))
#define _vtextviewSendObserveAction(v,a) vclassSend(vtextviewGetClass(v), \
					    vtextviewOBSERVE_ACTION, (v,a))


vportEND_CPLUSPLUS_EXTERN_C


#endif /* #ifndef vtextviewINCLUDED */


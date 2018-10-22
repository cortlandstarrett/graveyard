/* $Id: xincell.h,v 1.5 1994/05/06 05:47:28 abstine Exp $
 *
 * Copyright 1992-1993 Visix Software Inc., 11440 Commerce Park Drive, 
 * Reston, VA  22091. All Rights Reserved.
 */

/* xincell.h -- Interface to a class that does in-cell editing
 *		   in a list view.
 */

#ifndef listincellINCLUDED
#define listincellINCLUDED 1


#ifndef vclassINCLUDED
#include vclassHEADER
#endif

#ifndef vlistviewINCLUDED
#include vlistviewHEADER
#endif

#ifndef vtextitemINCLUDED
#include vtextitemHEADER
#endif

/* --------------- Private and public constants --------------- */


/* private flags to govern the behavior of the in-cell editing thing */
enum {
    _xincellAUTO_ROW_RESIZE    = 0x0001,
    _xincellAUTO_COLUMN_RESIZE = 0x0002,
    _xincellIS_EDITING         = 0x0004,
    _xincellCAN_EDIT           = 0x0008,

    _xincellTEXT_CAN_GROW      = 0x0010
};


/* currently no cell is designated the editing one. */
enum {
    xincellNO_CELL	= -1
};


/* --------------- Class and object setup --------------- */


typedef struct xincell {
    vlistview		 listv; /* we're subclassing vlistview -- this
				    * _must_ come first. */
    vcolor     		*hiliteColor;
    vdialogItemList	*itemList;
    vpoint		 lastMousePoint;
    int			 edRow, edColumn;
    int			 flags;

    vtextitemClass	*textitemClass;
    vtextitem		*textitem;
    vcolor		*textEditColor;
} xincell;


/* describe the new class methods, and include the ones from the superclass. */
/* SUPER is the class we're currently defining
 * ITEM is the dialog-item type that each function in our module takes for
 * a first parameter.
 * NOTIFY is the notification procedure type.
 */
#define xincellCLASS(SUPER, ITEM, NOTIFY)  \
vlistviewCLASS(SUPER, ITEM, NOTIFY); \
vclassMETHOD (xincellDETERMINE_EDITING_RECT, (ITEM *incell, vrect *rect)); \
vclassMETHOD (xincellCANCEL_EDITING, (ITEM *incell)); \
vclassMETHOD (xincellACCEPT_EDITING, (ITEM *incell)); \
vclassMETHOD (xincellDRAW_EDITING_HILITE, (ITEM *incell)); \
vclassMETHOD (xincellCALCULATE_AUTO_RESIZE, (ITEM *incell)); \
vclassMETHOD (xincellSET_EDITING_CELL, (ITEM *incell, int row, int column)); \
vclassMETHOD_RET (xincellGET_EDITING_VALUE, void *, (ITEM *incell)); \
vclassMETHOD (xincellSET_EDITING_VALUE, (ITEM *incell, void *value))


/* this forward reference is necessary to keep the compiler happy when
 * expanding the above macro. */
typedef struct xincellClass	xincellClass;

struct xincellClass {
    xincellCLASS (xincellClass, xincell, vlistviewNoteProc);
};


/* --------------- Module prototypes --------------- */


/* Object functions */
xincellClass *xincellGetDefaultClass (void);
xincellClass *xincellGetClass (xincell *incell);

xincell *xincellCreateOfClass (xincellClass *clas);
xincell *xincellCreate (void);
void xincellDestroy (xincell *incell);

void xincellInit (xincell *incell);
void xincellLoadInit (xincell *incell);

/* superclass accessor functions */
vlistview *xincellGetListview (xincell *incell);
vdialogItem *xincellGetItem (xincell *incell);
vdialogItemList *xincellGetItemList (xincell *incell);


/* incell-editing specific functions */
void xincellSetEditing (xincell *incell, int onOff);
int xincellIsEditing (xincell *incell);

void xincellSetEditingCell (xincell *incell, int row, int column);
void xincellGetEditingCell (xincell *incell, int *row, int *column);
void xincellGetEditingCellRow (xincell *incell);
void xincellGetEditingCellColumn (xincell *incell);

void xincellSetCanEdit (xincell *incell, int onOff);
int xincellGetCanEdit (xincell *incell);

void xincellCancelEditing (xincell *incell);
void xincellAcceptEditing (xincell *incell);

void xincellSetAutoRowResize (xincell *incell, int onOff);
int xincellGetAutoRowResize (xincell *incell);

void xincellSetAutoColumnResize (xincell *incell, int onOff);
int xincellGetAutoColumnResize (xincell *incell);

void xincellDetermineEditingRect (xincell *incell, vrect *rect);
vrect *xincellGetEditingRect (xincell *incell);
void xincellDrawEditingHilite (xincell *incell);
void xincellCalculateAutoResize (xincell *incell);

void xincellSetHiliteColor (xincell *incell, vcolor *hiliteColor);
vcolor *xincellGetHiliteColor (xincell *incell);

void *xincellGetEditingValue (xincell *incell);
void xincellSetEditingValue (xincell, void *value);


/* Text-specific calls -- may go away when this module is generalized */
vtextitem *xincellGetTextitem (xincell *incell);

void xincellSetTextitemClass (xincell *incell, vtextitemClass *clas);
vtextitemClass xincellGetTextitemClass (xincell *incell);

void xincellSetTextCanGrow (xincell *incell, int onOff);
int xincellGetTextCanGrow (xincell *incell);

void xincellSetTextEditColor (xincell *incell, vcolor *color);
vcolor *xincellGetTextEditColor (xincell *incell);


/* --------------- functions defined as #define defines --------------- */

/* typically, "Set" functions are real functions or methods.
 * "Get" functions are typically struct references.  The actual
 * implementation of these are considered "owned" by the module, and
 * are subject to change. (i.e. a "Get" function that was a macro
 * might need to do more processing in the future and get changed to
 * real function or a method.
 */
/* important for xincellSend */
#define xincellGetClass(i)	((xincellClass*)vdialogGetItemClass \
				 ((vdialogItem *)(i)))

/* shorthand for sending messages */
#define xincellSend(m,s,a)	vclassSend(xincellGetClass(m),s,a)
#define xincellSendSuper(m,s,a) \
				vclassSendSuper(xincellGetClass(m),s,a)

/* foobarCreate is typically built with foobarCreateOfClass */
#define xincellCreateOfClass(c) \
	((xincell*) vdialogCreateItemOfClass((vdialogItemClass*)(c)))
#define xincellCreate()  xincellCreateOfClass(xincellGetDefaultClass())

/* superclass accessor functions -- these are convenience "functions".
 * Most can actually be done with casts, but I don't like doing lots
 * of casts, so I use these a lot. */
#define xincellGetListview(i) &((i)->listv)
#define xincellGetItem(i)     vlistviewGetItem(xincellGetListview((i)))
#define xincellGetItemList(i) (i)->itemList

/* access attributes stored in flags */
#define xincellIsEditing(i) (((i)->flags & _xincellIS_EDITING) != 0)
#define xincellGetCanEdit(i) (((i)->flags & _xincellCAN_EDIT) != 0)
#define xincellGetAutoRowResize(i) (((i)->flags  \
				     & _xincellAUTO_ROW_RESIZE != 0))
#define xincellGetAutoColumnResize(i) (((i)->flags  \
					& _xincellAUTO_COLUMN_RESIZE != 0))

/* more attribute accessing */
#define xincellGetHiliteColor(i)  ((i)->hiliteColor)

/* cell-editing specific accessors */
#define xincellGetEditingCell(i,r,c) { *(r) = (i)->edRow; \
				       *(c) = (i)->edColumn; }
#define xincellGetEditingCellRow(i)	(i)->edRow
#define xincellGetEditingCellColumn(i)	(i)->edColumn


/* text specific stuff -- may go away or mutate when this module 
 * is more generalized. */

#define xincellGetTextitem(i)	((i)->textitem)
#define xincellGetTextitemClass(i) ((i)->textitemClass)
#define xincellGetTextCanGrow(i) (((i)->flags  \
				   & _xincellTEXT_CAN_GROW != 0))
#define xincellGetTextEditColor(i) ((i)->textEditColor);



/* --------------- functions defined as messages --------------- */

#define xincellDetermineEditingRect(i,rt) \
	xincellSend (i, xincellDETERMINE_EDITING_RECT, (i,rt))
#define xincellCancelEditing(i) \
	xincellSend (i, xincellCANCEL_EDITING, (i))
#define xincellAcceptEditing(i) \
	xincellSend (i, xincellACCEPT_EDITING, (i))
#define xincellDrawEditingHilite(i) \
	xincellSend (i, xincellDRAW_EDITING_HILITE, (i))
#define xincellCalculateAutoResize(i) \
	xincellSend (i, xincellCALCULATE_AUTO_RESIZE, (i))
#define xincellSetEditingCell(i,r,c) \
	xincellSend (i, xincellSET_EDITING_CELL, (i,r,c))
#define xincellGetEditingValue(i) \
	xincellSend (i, xincellGET_EDITING_VALUE, (i))
#define xincellSetEditingValue(i,v) \
	xincellSend (i, xincellSET_EDITING_VALUE, (i,v))


#endif /* listincellINCLUDED */



/*
 * Formatting information for emacs in c-mode
 *
 * Local Variables:
 * c-indent-level:4
 * c-continued-statement-offset:0
 * c-brace-offset:0
 * c-brace-imaginary-offset:0
 * c-argdecl-indent:0
 * c-label-offset:0
 * End:
 */




/* $Id: incell.c,v 1.14 1997/09/25 22:26:33 dimitri Exp $
 *
 * The following Sample Code is provided for your reference purposes in
 * connection with your use of the Galaxy Application Environment (TM) software
 * product which you have licensed from Visix Software, Inc. ("Visix").
 * The Sample code is provided to you without any warranty of any kind
 * whatsoever and you agree to be responsible for the use and/or incorporation
 * of the Sample Code into any software product you develop. You agree to fully
 * and completely indemnify and hold Visix harmless from any and all loss,
 * claim, liability or damages with respect to your use of the Sample Code.  
 *
 * Subject to the foregoing, you are permitted to copy, modify, and distribute
 * the Sample Code for any purpose and without fee, provided that (i) a
 * copyright notice in the in the form of "Copyright 1993 Visix Software Inc.,
 * 11440 Commerce Park Drive, Reston, VA  22091. All Rights Reserved" appears
 * in all copies, (ii) both the copyright notice and this permission notice
 * appear in supporting documentation and (iii) you are a valid licensee of
 * Galaxy Application Environment.
 */

/* incell.c -- Implementation for a class that does in-cell editing
 *		in a list view.
 */

/* This file demonstrates these concepts:
 *     Use of dialog item lists (although the dwi samples does a better job)
 *     Sophisticated subclassing
 *     Event handling
 */

#define vdebugTAG "xincell" /* label memory we may leak */

#ifndef vportINCLUDED
#include <vport.h>
#endif

#ifndef vdebugINCLUDED
#include vdebugHEADER
#endif

#ifndef vnameINCLUDED
#include vnameHEADER
#endif

#ifndef vstrINCLUDED
#include vstrHEADER
#endif

#ifndef vrectINCLUDED
#include vrectHEADER
#endif

#ifndef vclientINCLUDED
#include vclientHEADER
#endif

#ifndef vdrawINCLUDED
#include vdrawHEADER
#endif

#ifndef veventINCLUDED
#include veventHEADER
#endif

#ifndef vclassINCLUDED
#include vclassHEADER
#endif

#ifndef vdialogINCLUDED
#include vdialogHEADER
#endif

#ifndef vtextitemINCLUDED
#include vtextitemHEADER
#endif

#ifndef vlistviewINCLUDED
#include vlistviewHEADER
#endif


#include "xincell.h"



/* --------------- Useful symbols and macros --------------- */


/* I haven't written the code yet to attach a command space to this list 
 * subclass.   This will go away when this module is completed. */
#define COMMANDS 0

/* I haven't written the code yet to draw the text and cell-editing hiliting
 * in different colors.  This will go away when this module is completed. */
#define COLORS 0


/* how far the mouse can move and still consider it a "click-to-edit-cell" */
#define xincellSLOP 5


/* turn a boolean into a literal string */
#define strTrueFalse(i)  ((i) ? "True" : "False")




/* --------------- Module global types and variables --------------- */


/* type for per-client globals. */

typedef struct xincellGlobals {
    xincellClass	*defaultClass;
#if (COMMANDS)
    vcommandSpace	 defaultSpace;
    vdict		 defaultCommandDict;
#endif
} xincellGlobals;


/* master pointer to our per-client globals.  This is essentially a "handle"
 * to the globals which will be set correctly by the client/application 
 * manager before we are called. */

static void **master = NULL;




/* --------------- Handy utility functions --------------- */



/* _xincellTextitemSelectAll -- Selects the entire contents of the given
 *			textitem.
 *
 *  -> textitem	-- the textitem to select all in
 *
 * The text manager should provide a function to do this in textitems.
 */
static void _xincellTextitemSelectAll (vtextitem *textitem)
{
    vtext	*text;
    size_t	 len;

    text = vtextitemGetTextData (textitem);
    len = vtextLength (text);
    vtextSelectRange (text, vtextviewGetSelection(vtextitemGetView(textitem)),
		      0, len);
} /* _xincellTextitemSelectAll */




/* --------------- Event handling method overrides --------------- */


/* _xincellHandleItemButtonDown -- Handle a button-down event in the incell
 *			thing.
 *			override of vdialogHANDLE_ITEM_BUTTON_DOWN.
 *			This is overridden so that we can snarf the event
 *			before the listview gets it.  If we are currently
 *			in cell editing mode, pass the event to the textitem.
 *			otherwise send it to the listview.
 *
 *  -> incell	-- the incell-editing thing
 *  -> event	-- the button down event that happened
 * <-		-- TRUE if we handled it, FALSE otherwise
 */
static int _xincellHandleItemButtonDown (xincell *incell, vevent *event)
{
    int ret = TRUE;
    
    if (xincellIsEditing(incell)) {
	/* we have been editing... */
	if (vrectContainsPoint 
	    (vdialogGetItemRect(vtextitemGetItem(incell->textitem)),
	     veventGetPointerX(event), veventGetPointerY(event))) {

	    vdialogSetItemListDrag (incell->itemList,
				    vtextitemGetItem(incell->textitem));
	    ret = vclassSend (incell->textitemClass,
			      vdialogHANDLE_ITEM_BUTTON_DOWN,
			      (incell->textitem, event));
	    
	} else if (veventGetBinding(event) != vname_Grab) {

	    /* clicked outside of thingie - leave edit mode */
	    xincellAcceptEditing (incell); /* will do xincellSetEditing(FALSE); */

	}
    }
    
    if (!xincellIsEditing(incell)) {

	incell->lastMousePoint.x = veventGetPointerX (event);
	incell->lastMousePoint.y = veventGetPointerY (event);
	
	ret = vclassSendSuper (((xincellGlobals*)*master)->defaultClass, 
			       vdialogHANDLE_ITEM_BUTTON_DOWN, (incell, event));
    }	

    return (ret);
	
} /* _xincellHandleItemButtonDown */




/* _xincellHandleItemButtonUp -- Handle a button-up event in the incell
 *			thing.
 *			override of vdialogHANDLE_ITEM_BUTTON_DOWN.
 *			This is overridden so that we can snarf the event
 *			before the listview gets it.  If we are currently
 *			in cell editing mode, pass the event to the textitem.
 *			If we are not editing, but the mouse up is within
 *			_xincellSLOP pixels, enter editing mode.  Otherwise
 *			send it to the listview.
 *
 *  -> incell	-- the incell-editing thing
 *  -> event	-- the button up event that happened
 * <-		-- TRUE if we handled it, FALSE otherwise
 */
static int _xincellHandleItemButtonUp (xincell *incell, vevent *event)
{
    int ret;
    
    if (xincellIsEditing(incell)) {
	/* send to textitem */
	ret = vclassSend (incell->textitemClass,
			  vdialogHANDLE_ITEM_BUTTON_UP,
			  (incell->textitem, event));

    } else {

	/* send to listview. this will generate a selection change notifiy */

	ret = vclassSendSuper (((xincellGlobals*)*master)->defaultClass, 
			       vdialogHANDLE_ITEM_BUTTON_UP, (incell, event));
	
	if (   (incell->lastMousePoint.x > veventGetPointerX (event) - xincellSLOP)
	    && (incell->lastMousePoint.x < veventGetPointerX (event) + xincellSLOP)
	    && (incell->lastMousePoint.y > veventGetPointerY (event) - xincellSLOP)
	    && (incell->lastMousePoint.y < veventGetPointerY (event) + xincellSLOP)
	    ) {

	    /* start editing */
	    vlistviewMapPointToCell (xincellGetListview(incell),
				     &incell->lastMousePoint,
				     &incell->edRow, &incell->edColumn);
	    xincellSetEditingCell (incell, incell->edRow, incell->edColumn);
	}
    }
    
    return (ret);
    
} /* _xincellHandleItemButtonUp */




/* _xincellHandleItemDrag -- Handle a button-drag event in the incell
 *			thing -- dispatch it to the listview or the dialog
 *			item as appropriate.
 *			override of vdialogHANDLE_ITEM_DRAG.
 *			This is overridden so that we can snarf the event
 *			before the listview gets it.  If we are currently
 *			in cell editing mode, send it to the textitem,
 *			otherwise send it to the listview.
 *
 *  -> incell	-- the incell-editing thing
 *  -> event	-- the button drag event that happened
 * <-		-- TRUE if we handled it, FALSE otherwise
 */
static int _xincellHandleItemDrag (xincell *incell, vevent *event)
{
    int ret;
    
    if (xincellIsEditing(incell)) {

	/* send to textitem */
	ret = vclassSend (incell->textitemClass,
			  vdialogHANDLE_ITEM_DRAG,
			  (incell->textitem, event));
    } else {

	ret = vclassSendSuper (((xincellGlobals*)*master)->defaultClass, 
			       vdialogHANDLE_ITEM_DRAG, (incell, event));
    }
    
    return (ret);
    
} /* _xincellHandleItemDrag */




/* _xincellHandleItemKeyDown -- Handle a key-down event in the incell
 *			thing -- dispatch it to the list or dialog item
 *			as appropriate.
 *			override of vdialogHANDLE_ITEM_KEY_DOWN.
 *			This is overridden so that we can snarf the event
 *			before the listview gets it.  If we are currently
 *			in cell editing mode, pass the event to the textitem,
 *			otherwise send it to the listview.
 *		Future enhancement: Need to have some way of designating
 *		keys as "accept" and "cancel" -- perhaps put something into
 *		the command spaces of the xincell or vtextitem?
 *
 *  -> incell	-- the incell-editing thing
 *  -> event	-- the keydown event that happened
 * <-		-- TRUE if we handled it, FALSE otherwise
 */
static int _xincellHandleItemKeyDown (xincell *incell, vevent *event)
{
    int ret;
    
    if (xincellIsEditing(incell)) {

	/* send to textitem */
	ret = vclassSend (incell->textitemClass,
			  vdialogHANDLE_ITEM_KEY_DOWN,
			  (incell->textitem, event));
    } else {

	/* send to listview */
	ret = vclassSendSuper (((xincellGlobals*)*master)->defaultClass, 
			       vdialogHANDLE_ITEM_KEY_DOWN, (incell, event));
    }
    
    return (ret);
    
} /* _xincellHandleItemKeyDown */




/* _xincellHandleItemKeyUp -- Handle a key-up event in the incell thing.
 *			dispatch it to the list or dialog item as appropriate.
 *			override of vdialogHANDLE_ITEM_KEY_UP.
 *			You've read this about 4 or 5 times already.
 *
 *  -> incell	-- the incell-editing thing
 *  -> event	-- the keyup event that happened
 * <-  		-- TRUE if we handled it, FALSE otherwise
 */
static int _xincellHandleItemKeyUp (xincell *incell, vevent *event)
{
    int ret;
    
    if (xincellIsEditing(incell)) {

	/* send to textitem */
	ret = vclassSend (incell->textitemClass,
			  vdialogHANDLE_ITEM_KEY_UP,
			  (incell->textitem, event));
    } else {

	/* send to listview */
	ret = vclassSendSuper (((xincellGlobals*)*master)->defaultClass,
			       vdialogHANDLE_ITEM_KEY_UP, (incell, event));
    }
    
    return (ret);
    
} /* _xincellHandleItemKeyUp */




/* --------------- Dialog item method overrides --------------- */


/* _xincellFocusItem -- acquire focus for our incell things.
 *			override of vdialogFOCUS_ITEM.
 *			This is overriden so that we can give focus to
 *			the proper dialog item: the textitem or the list.
 *			if we're editing, we want the textitem to be focused
 *			so that it will draw the blinking insertion point.
 *			otherwise, just go ahead and let the listview get focus.
 *
 *  -> incell	-- the incell-editing thing that got focus
 */
static void _xincellFocusItem (xincell *incell)
{
    if (xincellIsEditing(incell)) {

	vdialogFocusItemList (incell->itemList);

    } else {

	vclassSendSuper (((xincellGlobals*)*master)->defaultClass, 
			 vdialogFOCUS_ITEM, (incell));
    }
} /* _xincellFocusItem */




/* _xincellUnfocusItem -- lose focus of our incell thingie.
 *			override of vdialogUNFOCUS_ITEM.
 *			This is overridden so that we can remove focus from
 *			the proper dialog item.  If we're editing, we want
 *			to shut off the textitem's blinking insertion point,
 *			otherwise remove the focus from the listview.
 *
 *  -> incell	-- the incell-editing thing that lost focus
 */
static void _xincellUnfocusItem (xincell *incell)
{
    if (xincellIsEditing(incell)) {

	vdialogUnfocusItemList (incell->itemList);

    } else {

	vclassSendSuper (((xincellGlobals*)*master)->defaultClass, 
			 vdialogUNFOCUS_ITEM, (incell));
    }
} /* _xincellUnfocusItem */




/* dialog item list functions -- since we're handling our own dialog item
 * 			list, we need to provide these functions.  Since
 *			we're not doing anything fancy with this item list,
 *			just use the vdialog versions.
 *			(cargo culted from vre.)
 */

static vdialog *determineDialog (vobject *owner)
{
    return (vdialogDetermineItemDialog (xincellGetItem((xincell*)owner)));
} /* determineDialog */


static vcursor *determineCursor (vobject *owner)
{
    return (vdialogDetermineItemCursor (xincellGetItem((xincell*)owner)));
} /* determineCursor */


static vfont *determineFont (vobject *owner)
{
    return (vdialogDetermineItemFont (xincellGetItem((xincell*)owner)));
} /* determineFont */


static void determineColorsFrom (vobject *owner, long flags, vcolor **known,
				 int *ids, int count, vcolor **colors)
{
    vdialogDetermineItemColorsFrom (xincellGetItem((xincell*)owner),
				    flags, known, ids, count, colors);
} /* determineColorsFrom */


static int determineLineWidth (vobject *owner)
{
    return (vdialogDetermineItemLineWidth (xincellGetItem ((xincell*)owner)));
} /* determineLineWidth */


static void determineBounds (vobject *owner, register vrect *rect)
{
    vdialogDetermineItemListBounds (vdialogGetItemItemList 
				    ((vdialogItem*)owner), rect);
} /* determineBounds */


static void determineContent (vobject *owner, vrect *rect)
{
    vdialogDetermineItemListContent (vdialogGetItemItemList 
				     ((vdialogItem*)owner), rect);
} /* determineContent */


static vdict *determineKeyMap (vobject *owner)
{
    return (vdialogGetItemKeyMap (xincellGetItem((xincell*)owner)));
} /* determineKeyMap */


static vdict *determineKeyDispatch (vobject *owner)
{
    return (vdialogGetItemKeyDispatch (xincellGetItem((xincell*)owner)));
} /* determineKeyDispatch */


/* our table for the owner functions for our dialog item list */
static vdialogItemListOwnerFuncs ownerFuncs = {
    0,
    determineDialog,
    determineCursor,
    determineFont,
    determineColorsFrom,
    determineLineWidth,
    determineBounds,
    determineContent,
    determineKeyMap,
    determineKeyDispatch
};





/* _xincellOpenItem -- The list is being added to the dialog's item list.
 *			override of vdialogOPEN_ITEM.
 *			This is overridden so that we can associate a custom
 *			item list with the incell-editing thing.  We also
 *			attach the textitem to this dialog item list,
 *			open the item the text manager can set up its necessary
 *			internal state, and finally hide the item until it's
 *			necessary to show it during editing.
 *
 *  -> incell	-- the incell-editing thing that's being opened.
 */
static void _xincellOpenItem (xincell *incell)
{
    /* open the listview */
    vclassSendSuper (((xincellGlobals*)*master)->defaultClass,
		     vdialogOPEN_ITEM, (incell));

    /* make a new item list and make it owned by the xincell */
    incell->itemList = vdialogCreateItemList ();
    vdialogSetItemListOwner (incell->itemList,
			     vdialogGetItemObject(xincellGetItem(incell)),
			     &ownerFuncs);

    /* attach the textitem to this new itemlist */
    vdialogAppendItemListItem (incell->itemList,
			       vtextitemGetItem(incell->textitem));

    vdialogOpenItem (vtextitemGetItem(incell->textitem));
    vdialogHideItem (vtextitemGetItem(incell->textitem));

} /* _xincellOpenItem */




/* _xincellCloseItem -- We're being closed.
 *			override of vdialogCLOSE_ITEM.
 *			This is overridden so that we can dispose of our
 *			private item list as the dialog item is being closed.
 *
 *  -> incell 	-- the incell-editing thing that's being closed
 */
static void _xincellCloseItem (xincell *incell)
{
    vdialogCloseItem (vtextitemGetItem(incell->textitem));

    vdialogDeleteItemListItem (incell->itemList,
			       vtextitemGetItem(incell->textitem));

    vdialogDestroyItemList (incell->itemList);

    incell->itemList = NULL;

    vclassSendSuper (((xincellGlobals*)*master)->defaultClass, 
		     vdialogCLOSE_ITEM, (incell));

    
} /* _xincellCloseItem */




/* _xincellDrawItem -- we're being drawn.
 *			override of vdialogDRAW_ITEM.
 *			This is overridden so that we can draw the 
 *			highlight around the cell being edited, as well
 *			as clip to the list's content area before drawing
 *			the text item.  If we don't clip, then the textitem
 *			could be drawn over the scrollbars and other parts
 *			of the dialog.
 *     !!!	Known bug: If the text item straddles the border, it will
 *			get drawn clipped, but it will still blast over the
 *			scrollbars when the user types into it.
 *
 *  -> incell	-- the in-cell editing thing that's being drawn
 */
static void _xincellDrawItem (xincell *incell)
{
    vclassSendSuper (((xincellGlobals*)*master)->defaultClass, 
		     vdialogDRAW_ITEM, (incell));

    if (xincellIsEditing(incell)) {

	/* so the textitem will be clipped to the list's borders if it
	 * should straddle the sides. */
	vdrawGSave ();
	vlistviewClip (xincellGetListview (incell));

	xincellDrawEditingHilite (incell);
	vdialogDrawItem (vtextitemGetItem(incell->textitem));
	vdrawGRestore ();
    }
} /* _xincellDrawItem */




/* --------------- Listview method overrides --------------- */


/* _xincellNotifyScroll -- The listview got scrolled - we need to scroll
 *			the editing fields.
 *			override of vlistviewNOTIFY_SCROLL. 
 *			This is overridden so that we can keep tabs on
 *			where the listview has scrolled, and move the
 *			textitem appropriately.
 *
 *  -> incell		-- the listview being scrolled.
 *  -> horzDistance 	-- how many pixels scrolled horizontally
 *  -> vertDistance	-- how many pixels scrolled vertically
 */
static void _xincellNotifyScroll (xincell *incell, 
				  int horzDistance, int vertDistance)
{
    vclassSendSuper (((xincellGlobals*)*master)->defaultClass, 
		     vlistviewNOTIFY_SCROLL, (incell, 
					      horzDistance, vertDistance));

    if (xincellIsEditing(incell)) {
	vrect	rect;
	xincellDetermineEditingRect (incell, &rect);
	vdialogSetItemRect (vtextitemGetItem(incell->textitem), &rect);
    }
    
} /* _xincellNotifyScroll */




/* _xincellDrawCellBackground -- cell background drawer for listviews.
 *			override of vlistviewDRAW_CELL_BACKGROUND.
 *			This method is overridden so that the cell being
 *			in-place edited will not be drawn.  This reduces
 *			some (not all, unfortunately) flicker during redraws.
 *
 *  -> incell	   -- the incell-editing thing (listview) whose cell is being
 *		      drawn.
 *  -> row, column -- the cell to draw the background for.
 *  -> selected	   -- show it with selected background?
 *  -> rect	   -- the rectangle to draw it in.
 */
static void _xincellDrawCellBackground (xincell *incell, int row, int column,
					int selected, vrect *rect)
{
    if (!xincellIsEditing(incell) 
	|| (row != xincellGetEditingCellRow(incell))
	|| (column != xincellGetEditingCellColumn(incell))) {
	vclassSendSuper (((xincellGlobals*)*master)->defaultClass, 
			 vlistviewDRAW_CELL_BACKGROUND,
			 (incell, row, column, selected, rect));
    }
} /* _xincellDrawCellBackground */




/* _xincellDrawCellSelection -- cell selection highlight drawer for listviews.
 *			override of vlistviewDRAW_CELL_SELECTION.
 *			This method is overridden so that the cell being
 *			in-place edited will not be drawn.  This reduces
 *			some (not all, unfortunately) flicker during redraws.
 *
 *  -> incell	   -- the incell-editing thing (listview) whose cell is being
 *		      drawn.
 *  -> row, column -- the cell to draw the selection hightlighting for.
 *  -> rect	   -- the rectangle to draw it in.
 */
static void _xincellDrawCellSelection (xincell *incell, int row, int column,
				       vrect *rect)
{
    if (!xincellIsEditing(incell) 
	|| (row != xincellGetEditingCellRow(incell))
	|| (column != xincellGetEditingCellColumn(incell))) {
	vclassSendSuper (((xincellGlobals*)*master)->defaultClass, 
			 vlistviewDRAW_CELL_SELECTION,
			 (incell, row, column, rect));
    }
} /* _xincellDrawCellSelection */




/* --------------- xincell implementation --------------- */


/* _xincellDetermineEditingRect -- Figure out the rectangle that will
 *			be used for this editing operation.
 *			implementation of xincellDETERMINE_EDITING_RECT.
 *
 *  -> incell 	   -- the incell-editing thing in question
 *  -> row, column -- the row and column of the cell to edit
 * <-  rect	   -- where to put the return value
 */
static void _xincellDetermineEditingRect (xincell *incell, vrect *rect)
{
    if ((incell->edRow != xincellNO_CELL) 
	&& (incell->edColumn != xincellNO_CELL)) {
	int fudge;

	vlistviewGetCellRect (xincellGetListview(incell),
			      incell->edRow, incell->edColumn, rect);
	fudge = vclassGet (xincellGetClass(incell),
			   vlistviewSELECTION_INSET);
	fudge += vdialogDetermineItemLineWidth (xincellGetItem(incell));
	vrectInset (rect, -fudge, -fudge, rect);

    } else {

	vdebugWarn ("WARNING: _xincellDetermineEditingRect -- bad editing cell"
		    " values.\n");
    }

} /* _xincellDetermineEditingRect */




/* _xincellCancelEditing -- Remove the editing thing and restore the
 *			previous cell's value.
 *			implementation of xincellCANCEL_EDITING.
 *
 *  -> incell
 */
static void _xincellCancelEditing (xincell *incell)
{

    xincellSetEditing (incell, FALSE); /* will empty textitem */

} /* _xincellCancelEditing */




/* _xincellAcceptEditing -- Remove editing thing and set the cell's value
 *			to what was in the editing thing.
 *			implementation of xincellACCEPT_EDITING.
 *
 *  -> incell -- the incell-editing thing that accepts the editing
 */
static void _xincellAcceptEditing (xincell *incell)
{
    if (xincellIsEditing(incell)) {
	xincellSetEditingValue (incell, 
				vtextitemGetTextAsString(incell->textitem));
	xincellSetEditing (incell, FALSE); /* will empty textitem */
    }
} /* _xincellAcceptEditing */




/* _xincellDrawEditingHilite -- Draw the frob around the editing item.
 *			implementation of xincellDRAW_EDITING_HILITE.
 *
 *  -> incell -- the edit thing to draw the frob on.
 */
static void _xincellDrawEditingHilite (xincell *incell)
{

} /* _xincellDrawEditingHilite */




/* _xincellCalculateAutoResize -- Calculate the automatic sizing of
 *			row and/or column depending on the contents of
 *			the editing item.
 *			implementation of xincellCALCULATE_AUTO_RESIZE.
 *
 *  -> incell -- the edit thing to resize the row and/or column for
 */
static void _xincellCalculateAutoResize (xincell *incell)
{
    vdebugWarn ("_xincellCalculateAutoResize under construction.\n");
} /* _xincellCalculateAutoResize */




/* xincellSetEditing -- sets the state of the editing mode.
 *			When editing is turned on, the text item is put
 *			into place.  When it is turned off, the text
 *			item is removed, and editing is cancelled.
 *			This doesn't put the textitem value into the
 *			list -- that is the responsibility of the
 *			function calling this one.
 *
 *  -> incell	-- the editing thingie.
 *  -> onOff	-- TRUE to turn on editing, FALSE to shut it off
 */
void xincellSetEditing (xincell *incell, int onOff)
{
    vrect	rect;
    
    if (onOff && !xincellIsEditing(incell) && xincellGetCanEdit(incell)) {
	vdebugIF ((incell->edRow == xincellNO_CELL)
		  || (incell->edColumn == xincellNO_CELL),
		  vexGenerateArgRange ());

	/* Turn on... */
	/* initialize the text item */
	vtextitemSetText (incell->textitem,
			  xincellGetEditingValue (incell));
	_xincellTextitemSelectAll (incell->textitem);
	xincellDetermineEditingRect (incell, &rect);
	vdialogSetItemRect (vtextitemGetItem(incell->textitem), &rect);
	vdialogShowItem (vtextitemGetItem(incell->textitem));

	/* make sure that the textitem will get drag events */
	vdialogSetItemListDrag (incell->itemList,
				vtextitemGetItem(incell->textitem));

	/* set up focus stuff */

	vdialogSetItemListFocus (vdialogGetItemItemList
				 (xincellGetItem(incell)),
				 xincellGetItem(incell));

	incell->flags |= _xincellIS_EDITING;

	vdialogFocusItemList (incell->itemList);
	vdialogSetItemListFocus (incell->itemList,
				 vtextitemGetItem(incell->textitem));

    } else if (!onOff && xincellIsEditing(incell)) {

	/* ...turn off... */

	incell->flags &= ~_xincellIS_EDITING;

	vdialogHideItem (vtextitemGetItem(incell->textitem));
	vdialogSetItemListFocus (incell->itemList, NULL);

    } else {
	/* ... tune out ... */
    }
} /* xincellSetEditing */



/* xincellSetCanEdit -- turn on the editability of the entire incell thing.
 *			When it is turned off, the text item (if shown)
 *			will be removed and editing cancelled. 
 *			This won't put the textitem value into the list
 *			-- that is the responsibility of the function
 *			calling this one.
 *			xincelLSetEditing() actually does most of the work.
 *
 *  -> incell	-- the incell thingie
 *  -> onOff	-- TRUE if users can edit in-place, FALSE otherwise
 */
void xincellSetCanEdit (xincell *incell, int onOff)
{
    if (onOff) {
	incell->flags |= _xincellCAN_EDIT;
    } else {
	incell->flags &= ~_xincellCAN_EDIT;
	if (xincellIsEditing(incell)) {
	    xincellSetEditing (incell, FALSE);
	}
    }
} /* xincellSetCanEdit */




/* _xincellSetEditingCell -- Set the cell that should have the editing
 *			done for it. This turns on the editing mode.
 *			implementation of xincellSET_EDITING_CELL. 
 *			Override this if you want to prevent some cells
 *			from being in-place-editable.
 *
 *  -> incell      -- the editing thing to set the cell for
 *  -> row, column -- the cell to edit
 */
static void _xincellSetEditingCell (xincell *incell, int row, int column)
{
    vdebugBE (vlist *list = vlistviewGetList(xincellGetListview(incell)));

    vdebugIF ((row > vlistGetRowCount(list))
	      || (column > vlistGetColumnCount(list)),
	      vexGenerateArgRange ());
    
    incell->edRow = row;
    incell->edColumn = column;
    
    xincellSetEditing (incell, TRUE);
    
} /* _xincellSetEditingCell */




/* _xincellGetEditingValue -- returns the value that should be placed into
 *			the dialog item that will be user-editable.
 *			By default, this is a wrapper around vlistGetCellValue
 *			and assumes a list of strings.  If the underlying
 *			list is not strings (say for an icon chooser), or
 *			not directly stored as strings (say for a spreadsheet
 *			where the cell contains a value the the editing is of
 *			the formula), then this is the method to override
 *			to tell xincell what to put in the dialog item.
 *			implementation of xincellGET_EDITING_VALUE.
 *
 *  -> incell	-- the incell thingie being edited
 * <-		-- what to put into the dialog item being edited.
 */
static void *_xincellGetEditingValue (xincell *incell)
{
    vlist	*list = vlistviewGetList (xincellGetListview(incell));
    int		 row, column;

    xincellGetEditingCell (incell, &row, &column);
    
    if ((row != xincellNO_CELL) && (column != xincellNO_CELL)) {

	return ((void*)vlistGetCellValue (list, row, column));

    } else {

	/* ??? generate exception ??? */
	vdebugWarn ("WARNING: _xincellGetEditingValue -- value requested "
		    "for list w/o an editing cell.");
	return (NULL);
    }

} /* _xincellGetEditingValue */




/* _xincellSetEditingValue -- called internally when editing has been
 *			accepted.  This method is responsible for (somehow)
 *			putting the users changes into the list.  By default
 *			it is just a wrapper for vlistSetCellValue.  Other
 *			applications may want to do some pre-processing
 *			before changing the list's value.  (e.g. a spreadsheet
 *			where a value is changed, but the user actually
 *			edited a formula.
 *			One other assumption is that the list is a list of
 *			vstr's, and that we can nuke the previous vstr before
 *			adding this one.
 *			implementation of xincellSET_EDITING_VALUE.
 *
 *  -> incell	-- the incell thingie
 *  -> value	-- what the user has finished editing.  Right now xincell
 *		   sends a vstr of the text item's contents.
 */
static void _xincellSetEditingValue (xincell *incell, void *value)
{
    vlist	*list = vlistviewGetList (xincellGetListview(incell));
    int		 row, column;

    xincellGetEditingCell (incell, &row, &column);

    if ((row != xincellNO_CELL) && (column != xincellNO_CELL)) {

	vstrDestroy ((vstr*)vlistGetCellValue (list, row, column));
	vlistSetCellValue (list, row, column, value);

    } else {

	vdebugWarn ("WARNING: _xincellSetEditingValue -- value being set "
		    " for list w/o an editing cell.");
	/* ??? exception ??? */
    }
} /* _xincellSetEditingValue */


/* --------------- Object method overrides --------------- */



/* _xincellLowInit -- handle intializing code that's shared between
 *			_xincellInit and xincellLoadInit.
 *
 *  -> incell	-- the thingie to init
 */
static void _xincellLowInit (xincell *incell)
{
    /* intialize these to useful sentinel values */
    incell->hiliteColor = NULL;
    incell->itemList = NULL;
    incell->lastMousePoint.x = -1;
    incell->lastMousePoint.y = -1;
    incell->edRow = xincellNO_CELL;
    incell->edColumn = xincellNO_CELL;
    incell->flags = _xincellCAN_EDIT;
    
    incell->textitemClass = vtextitemGetDefaultClass ();
    incell->textitem = vtextitemCreate ();
    incell->textEditColor = NULL;
    
} /* _xincellLowInit */




/* _xincellInit -- Initialize a new incell structure.
 *			An override of vobjectINIT.
 *
 *  -> incell -- the listview to initialize.
 */
static void _xincellInit (xincell *incell)
{
    vclassSendSuper (((xincellGlobals*)*master)->defaultClass, vobjectINIT, 
		     (incell));
    
    _xincellLowInit (incell);
    
} /* _xincellInit */




/* _xincellLoadInit -- Initialize a new incell structure from a resource.
 *			An override of vobjectLOAD_INIT
 *
 *  -> incell   -- the listview to initialize
 *  -> resource -- the resource to get it from.
 */
static void _xincellLoadInit (xincell *incell, vresource resource)
{
    vclassSendSuper (((xincellGlobals*)*master)->defaultClass, 
		     vobjectLOAD_INIT, (incell, resource));
    
    _xincellLowInit (incell);

    /* !!! need to restore the hilite color and text edit color.  
     * !!! also need to restore the auto_row_resize, auto_column_resize,
     * !!! text_can_grow, and can_edit flags once they're implemented.
     * !!! for right now, restoring just the listview is sufficient. 
     */
    
} /* _xincellLoadInit */




/* _xincellStore -- Save an incell structure to a resource.
 *			An override of vobjectSTORE.
 *
 *  -> incell   -- the listview to store
 *  -> resource -- where to store it.
 */
static void _xincellStore (xincell *incell, vresource resource)
{
    vclassSendSuper (((xincellGlobals*)*master)->defaultClass, vobjectSTORE, 
		     (incell, resource));
    
    /* !!! need to store the hilite color and text edit color.  
     * !!! also need to store the auto_row_resize, auto_column_resize,
     * !!! text_can_grow, and can_edit flags once they're implemented.
     * !!! for right now, storing just the listview is sufficient. 
     */
} /* _xincellStore */





/* _xincellDestroy -- Destroy an incell structure and free any extra memory 
 *			consumed by it.
 *			An override of vobjectDESTROY.
 *
 *  -> incell -- the listview to obliterate
 */
static void _xincellDestroy (xincell *incell)
{
#if (COLORS)

    if (incell->hiliteColor) {
	vcolorDestroy (incell->hiliteColor);
    }

    if (incell->textEditColor) {
	vcolorDestroy (incell->textEditColor);
    }

#endif
    
    if (incell->itemList) {
	vdialogDestroyItemList (incell->itemList);
    }
    
    if (incell->textitem) {
	vtextitemDestroy (incell->textitem);
    }
    
    vclassSendSuper (((xincellGlobals*)*master)->defaultClass, vobjectDESTROY, 
		     (incell));
    
} /* _xincellDestroy */




/* _xincellStartup -- setup any cross-client globals.
 */
static void _xincellStartup (void)
{
    /* make sure vlistview is up and running */
    (void) vlistviewGetDefaultClass ();

} /* _xincellStartup */




/* _xincellStartupCline -- allocate global space for this invocation of
 *			the _xincellEditing client.  This also sets up
 * 			the default xincellEditing class.
 */
static void _xincellStartupClient (void)
{
    register xincellClass	*defaultClass;
    register xincellGlobals	*globals;

    /* create the default xincellEditing class */
    globals = *master;
    
    defaultClass = vclassSpawn (vlistviewGetDefaultClass (),
				sizeof (xincellClass));
    
    vclassSetNameScribed (defaultClass,
			  vcharScribeLiteral ("xincell"));
    
    vclassSetObjectSize (defaultClass, sizeof (xincell));
    

    /* ----- object, dialogItem, and listview method overrides ----- */

#if (COMMANDS)
    vclassSet (defaultClass,
	       vobjectSPACE, /* point to our command space */
	       &globals->defaultSpace);
#endif
    vclassSet (defaultClass, /* to initialize our new fields */
	       vobjectINIT,
	       _xincellInit);
    vclassSet (defaultClass, /* to initialzie our new fields from a resource */
	       vobjectLOAD_INIT,
	       _xincellLoadInit);
    vclassSet (defaultClass, /* to clean up extra memory we use. */
	       vobjectDESTROY,
	       _xincellDestroy);
    vclassSet (defaultClass, /* save our attributes in a resource */
	       vobjectSTORE,
	       _xincellStore);
    vclassSet (defaultClass, /* to send the keydown to the list or textitem */
	       vdialogHANDLE_ITEM_KEY_DOWN,
	       _xincellHandleItemKeyDown);
    vclassSet (defaultClass, /* to send the keyup to the list or textitem */
	       vdialogHANDLE_ITEM_KEY_UP,
	       _xincellHandleItemKeyUp);
    vclassSet (defaultClass, /* to send the buttondown to the list or textitem */
	       vdialogHANDLE_ITEM_BUTTON_DOWN,
	       _xincellHandleItemButtonDown);
    vclassSet (defaultClass, /* to send the buttonup to the list or textitem */
	       vdialogHANDLE_ITEM_BUTTON_UP,
	       _xincellHandleItemButtonUp);
    vclassSet (defaultClass, /* to send the buttondrag to the list or textitem */
	       vdialogHANDLE_ITEM_DRAG,
	       _xincellHandleItemDrag);
    vclassSet (defaultClass, /* to give focus to the text item if editing */
	       vdialogFOCUS_ITEM,
	       _xincellFocusItem);
    vclassSet (defaultClass, /* to remove focus to the text item if editing */
	       vdialogUNFOCUS_ITEM,
	       _xincellUnfocusItem);
    vclassSet (defaultClass, /* create our item list and attach the textitem */
	       vdialogOPEN_ITEM,
	       _xincellOpenItem);
    vclassSet (defaultClass, /* remove textitem and destroy our item list */
	       vdialogCLOSE_ITEM,
	       _xincellCloseItem);
    vclassSet (defaultClass, /* draw the text item on top of the list */
	       vdialogDRAW_ITEM,
	       _xincellDrawItem);
    vclassSet (defaultClass, /* scroll the textitem when the list does */
	       vlistviewNOTIFY_SCROLL,
	       _xincellNotifyScroll);
    vclassSet (defaultClass, /* don't draw cell under textitem */
	       vlistviewDRAW_CELL_BACKGROUND,
	       _xincellDrawCellBackground);
    vclassSet (defaultClass, /* don't draw cell under textitem */
	       vlistviewDRAW_CELL_SELECTION,
	       _xincellDrawCellSelection);

    /* ----- xincell method implementations ----- */

    vclassSet (defaultClass, /* calc size textitem should be */
	       xincellDETERMINE_EDITING_RECT,
	       _xincellDetermineEditingRect);
    vclassSet (defaultClass, /* restore previous value to list */
	       xincellCANCEL_EDITING,
	       _xincellCancelEditing);
    vclassSet (defaultClass, /* textitem is OK: put new value into list */
	       xincellACCEPT_EDITING,
	       _xincellAcceptEditing);
    vclassSet (defaultClass, /* draw frob around textitem */
	       xincellDRAW_EDITING_HILITE,
	       _xincellDrawEditingHilite);
    vclassSet (defaultClass, /* resize row or column to fit value */
	       xincellCALCULATE_AUTO_RESIZE,
	       _xincellCalculateAutoResize);
    vclassSet (defaultClass, /* designate which cell should be edited */
	       xincellSET_EDITING_CELL,
	       _xincellSetEditingCell);
    vclassSet (defaultClass, /* fetch the value to put into textitem. */
	       xincellGET_EDITING_VALUE,
	       _xincellGetEditingValue);
    vclassSet (defaultClass, /* store value from textitem item item list */
	       xincellSET_EDITING_VALUE,
	       _xincellSetEditingValue);

    globals->defaultClass = defaultClass;

} /* _xincellStartupClient */




/* _xincellShutdownClient -- clean up global-variable usage for this
 * 			invocation of the xincellEditing client.
 */
static void _xincellShutdownClient (void)
{
    xincellGlobals *globals;

    globals = *master;
    vclassDestroy (globals->defaultClass);

} /* _xincellShutdownClient */




/* _xincellSetup -- get xincellEditing up and running.
 */
static void _xincellSetup (void)
{
    if (master == NULL) {
	master = vclientRegisterModule();
	_xincellStartup ();
    }

    if (*master == NULL) {
	vclientAllocateModule (master, sizeof(xincellGlobals));
	_xincellStartupClient ();
	vclientRegisterShutdown (_xincellShutdownClient);
    }

} /* _xincellSetup */





/* xincellGetDefaultClass -- returns the defualt xincellEditing class.
 *
 * <-  the default xincellEditng class.
 */
xincellClass *xincellGetDefaultClass (void)
{
    if ((master == NULL) || (*master == NULL)) {
	_xincellSetup();
    }
	
    return ((xincellGlobals*)*master)->defaultClass;

} /* xincellGetDefaultClass */



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


/* $Id: ditem.c,v 1.3 1995/01/19 19:08:31 chad Exp $ */
/* ditem.c -- implementation of dialog-item specific functions
 *            for the minitext example
 * The following Sample Code is provided for your reference purposes in
 * connection with your use of the Galaxy Application Environment (TM) software
 * product which you have licensed from Visix Software, Inc. ("Visix").
 * The Sample code is provided to you without any warranty of any kind
 * whatsoever and you agree to be responsible for the use and/or incorporation
 * of the Sample Code into any software product you develop. You agree to fully
 * and completely indemnify and hold Visix harmless from any and all loss,.
 * claim, liability or damages with respect to your use of the Sample Code.  
 *
 * Subject to the foregoing, you are permitted to copy, modify, and distribute
 * the Sample Code for any purpose and without fee, provided that (i) a
 * copyright notice in the in the form of "Copyright 1994 Visix Software Inc.,
 * 11440 Commerce Park Drive, Reston, VA  22091. All Rights Reserved" appears
 * in all copies, (ii) both the copyright notice and this permission notice
 * appear in supporting documentation and (iii) you are a valid licensee of
 * Galaxy Application Environment.
 *
 * Do not taunt Happy Fun Ball.
 *
 * Stuff that was done to construct this file:
 *
 * step zero:
 *    file did not exist
 * step one:
 *    add stub functions for DrawItem, ButtonDown/Up/Drag, KeyDown
 *        (drawItem draws a thin border for non-focus, thick for focus.)
 *    add stub functions for FocusItem/UnfocusItem to force a redraw
 * step two:
 *    add selectionEnd setting in mouse tracking.
 * step three:
 *    add selection stuff to mouse-event code.
 * step four:
 *    add proper use of colors when drawing
 *    add dialog sizing code (min size, nat size, etc...)
 * step five:
 *    add obeying of select type setting in drawItem
 *    and in event handling
 *    added dialog item notification on keypresses
 * step six:
 *    fix clipping in drawing
 * step seven:
 *    do vame_Adjust stuff in button-down and drag/detail
 *    use color scheme stuff for drawing
 *    do some arg checking
 */

#include <vport.h>


/* only include the header files we need for this particular file
 */

#ifndef  vdialogINCLUDED
#include vdialogHEADER
#endif

#ifndef  veventINCLUDED
#include veventHEADER
#endif

#ifndef  vdrawINCLUDED
#include vdrawHEADER
#endif




/* snarf in the local headers */

#include "mtext.h"
#include "priv.h"




/*
 * ----- Drawing stuff
 */


/* _mtextDrawItem -- draw the minitext
 *
 *  -> text -- the minitext to draw
 *
 * This routine draws the border (if that dialog item attribute is set),
 * clips the drawing area, displays the text, and then draws the 
 * selection point or range selection as appropriate.
 *
 * Lastly, it draws the dialog item focus if necessary (the dialog manager
 * won't do this for us.  The only time it calls the focus drawing method
 * is when the focus state changes.)
 */
void _mtextDrawItem (mtext *text)
{
    vdialogItem *item = mtextGetItem (text);
    int          x, y;
    vbool        focusIsVisible = vdialogItemFocusIsVisible(item);

    vcolorScheme scheme; /* or CommonLisp if you want */


    vdialogDetermineItemColorSchemeState (item,
					  (  vcolorFLAG_SHADOW_TOP
					   | vcolorFLAG_SHADOW_BOTTOM
					   | vcolorFLAG_BACKGROUND
					   | vcolorFLAG_FOREGROUND),
					  &scheme);
    /*
     * draw the border first
     */

    vdrawGSave (); {
	vrect clippy;
	clippy = *vdialogGetItemRect(item);

	vdrawSetColor (vcolorGetSchemeBackground(&scheme));
	vdrawRectsFill (vdialogGetItemRect(item), 1);
	vdrawSetColor (vcolorGetSchemeForeground(&scheme));
	    
	if (vdialogItemHasBorder(item)) {
	    int lineWidth = vdialogDetermineItemLineWidth(item);

	    if (vlaf3D()) {
		vdrawRectsHiliteFillInside (vdialogGetItemRect(item), 1, 
					    (vcolor*)NULL,
					    vcolorGetSchemeShadowBottom(&scheme),
					    vcolorGetSchemeShadowTop(&scheme));
	    } else {
		vdrawRectsStrokeInside (vdialogGetItemRect(item), 1);
	    }

	    /* inset the clipping rect so that text won't draw over the
	     * border we just drew
	     */
	    vrectInset (&clippy, lineWidth, lineWidth, &clippy);
	}

	vdrawRectsClip (&clippy, 1);

	/*
	 * draw the text
	 */

	_mtextGetLineOrigin (text, 0, &x, &y);
	vdrawMoveTo (x, y);
	vdrawSizedShow (mtextGetText(text), mtextGetLength(text));
	
	/*
	 * draw the insertion point or selection
	 */
	
	if (    focusIsVisible
	    && (mtextGetSelectType(text) != mtextNO_SELECTION)) {
	    if (mtextGetSelectionLength(text) > 0) {
		mtextDrawSelectedRange (text, 
					mtextGetAnchor(text),
					mtextGetSelectionEnd(text));
	    } else {
		mtextDrawCaret (text, mtextGetAnchor(text), mtextDRAW);
	    }
	}
	
    } vdrawGRestore ();

    if (focusIsVisible) {
	vdialogDrawItemFocus (item);
    }

} /* _mtextDrawItem */




/* _mtextDrawItemFocus -- draw the focus indication for the item
 *
 *  -> text -- the mtext to draw the focus for.
 *
 * The way text items show focus is to hilite the selected range (or
 * show the insertion point), and draw a box around the textitem (for
 * some look and feels.).  The selection stuff is handled elsewhere (namely
 * invalidating the selected region), so all we do is do the out-of-item
 * drawing.
 */
void _mtextDrawItemFocus (mtext *text)
{
    /* for mootif and the Mac, draw a box around the item */

    /* you can't depend on this getting called automatically at the
     * Necessary Times (say after a vdialogArrange.  your vdailogDRAW_ITEM
     * must call it explicitly
     */

    switch (vlafAppear()) {

#ifdef vlafMOTIF
	case vlafMOTIF: {
	    vrect rect;
	    rect = *vdialogGetItemRect(mtextGetItem(text));
	    
	    vrectInset (&rect,
			- vclassGet (mtextGetClass(text), 
				     vdialogITEM_FOCUS_EXTRA),
			- vclassGet (mtextGetClass(text),
				     vdialogITEM_FOCUS_EXTRA),
			&rect);
	    vdrawRectsStrokeInside (&rect, 1);
	    break;
	}
#endif

#ifdef vlafMAC
	case vlafMAC: {
	    if (TRUE) { /* !!! needs to be some kind of conditional */
		vrect rect;
		rect = *vdialogGetItemRect(mtextGetItem(text));
		
		vrectInset (&rect,
			    - vclassGet (mtextGetClass(text),
					 vdialogITEM_FOCUS_EXTRA),
			    - vclassGet (mtextGetClass(text),
					 vdialogITEM_FOCUS_EXTRA),
			    &rect);
		vdrawRectsStrokeInside (&rect, 1);
	    }
	    break;
	}
#endif
    }

} /* _mtextDrawItemFocus */




/*
 * ----- Sizing stuff
 */


/* _mtextGetItemMinSize -- return the minimum useful size the mtext can
 * 			   be.
 *
 *  -> text   -- the text to determine the minimum size for
 * <-  width  -- the minimum width
 * <-  height -- the minimum height
 *
 * The minimum size is the amount of space the border takes, as well as
 * a 10 pixel pad to show a little text.  The minimum height is the
 * height necessary to show an arbitrary font glyph.
 */
void _mtextGetItemMinSize (mtext *text, int *width, int *height)
{
    vdialogItem *item = mtextGetItem(text);
    vfont       *font = vdialogDetermineItemFont(item);

    /* see if there's a minimum our superclass needs */
    vclassSendSuper (_mtextGlobals->defaultClass, vdialogGET_ITEM_MIN_SIZE,
		     (text, width, height));

    /* !!! these constants really should be parameterized.  Should also
     * !!! take into account the border parameter
     */

    if (width != NULL) {
	*width += (  vdialogDetermineItemLineWidth(item) * 2  /* border */
		   + 10 /* pad */ );
    }
    
    if (height != NULL) {
	*height += (  vdialogDetermineItemLineWidth(item) * 2 /* border */
		    + vfontHeight(font) + vfontDescent(font)
		    + 10 /* pad */ );
    }

} /* _mtextGetItemMinSize */




/* _mtextGetItemNaturalSize -- return the size that the dialog item feels
 * 			       most natural, that just "feels right."
 *
 *  -> text   -- the text to determine the natural size for
 * <-  width  -- the natural width
 * <-  height -- the natural height
 */
void _mtextGetItemNaturalSize (mtext *text, int *width, int *height)
{
    vfont *font = vdialogDetermineItemFont (mtextGetItem(text));

    vclassSendSuper (_mtextGlobals->defaultClass, vdialogGET_ITEM_NATURAL_SIZE,
		     (text, width, height));

    /* natural size is minSize + the width of the string */

    _mtextGetItemMinSize (text, width, height);

    if (width != NULL) {
	*width += vfontSizedStringWidthX (font, text->contents,
					  mtextGetLength(text));
    }

} /* _mtextGetItemNaturalSize */




/* _mtextContstrainItemSize -- given a dialog item size, return a smaller
 *			       version that more closely matches the contents
 *			       being displayed.
 *
 *  -> text   -- the text to constrain the size for 
 * <-> width  -- the initial width.  Change to a smaller value if so desired
 * <-> height -- the initial height.  Change to a smaller value is so desired
 */
void _mtextConstrainItemSize (mtext *text, int *width, int *height)
{
    vclassSendSuper (_mtextGlobals->defaultClass, vdialogCONSTRAIN_ITEM_SIZE,
		     (text, width, height));

    /* doesn't really make sense to constrain a text field.  Things like
     * lists could use constraining to show only integral rows, or to
     * limit the height to an exact multiple of a given row height.
     *
     * This can also be used to enforce a maximum size (beyond this grow
     * no larger)
     */

} /* _mtextConstrainItemSize */




/* _mtextGetItemNaturalSeparation -- return the amount of space a natural
 *      			     strut originating from this item should
 *				      be.
 *
 *  -> text        -- the text to determine the separation for
 *  -> to          -- the dialog item connected to.  can be NULL for connecting
 *		      to the dialog/container border
 *  -> wickedWitch -- a connection constant
 * <-              -- the size this strut should be
 *
 * The conenction constant is one of these:
 *   vspringLEFT_TO_LEFT_SEPARATION     -- left of text to left side of 'to'
 *   vspringLEFT_TO_RIGHT_SEPARATION    -- left of text to right side of 'to'
 *   vspringRIGHT_TO_LEFT_SEPARATION    -- right of text to left side of 'to'
 *   vspringRIGHT_TO_RIGHT_SEPARATION   -- right of text to right side of 'to'
 *   vspringBOTTOM_TO_BOTTOM_SEPARATION -- bottom of text to bot side of 'to'
 *   vspringBOTTOM_TO_TOP_SEPARATION    -- bottom of text to top side of 'to'
 *   vspringTOP_TO_BOTTOM_SEPARATION    -- I think you get the idea
 *   vspringTOP_TO_TOP_SEPARATION       -- of what's going on here.
 *
 * Why is this really useful?  Consider the case of a full-dialog textitem/
 * wordProcessor and the Macintosh look-n-feel.  In most look and feels, 
 * you put a pad between the textitem and the window border (that's just
 * How It's Done).  On the Mac, though, you want the border to snug itself
 * against the dialog border.  The way to accomplish this is to, in vre,
 * put natural struts all around the textitem.  In this method, you'd
 * return something like "5" in all lookNFeels for leftToLeft, RightToRight,
 * BottomToBototm, and TopToTop, but "0" for the Mac look and feel.
 */
int _mtextGetItemNaturalSeparation (mtext *text, vdialogItem *to,
				    unsigned int wickedWitch)
{
    int ret;

    ret = vclassSendSuper (_mtextGlobals->defaultClass, 
			   vdialogGET_ITEM_NATURAL_SEPARATION, 
			   (text, to, wickedWitch));

    return (ret);

} /* _mtextGetItemNaturalSeparation */




/*
 * ----- Event handling stuff
 */


/* _mtextHandleItemButtonDown -- handle a mouse click
 *
 *  -> text  -- the minitext being clicked on
 *  -> event -- the event that diddit
 * <-        -- TRUE if we handled it, FALSE if we didn't
 *
 * This starts a selection change operation
 */
int _mtextHandleItemButtonDown (mtext *text, vevent *event)
{
    int ret;

#if (vdebugDEBUG)
    if (event == NULL) {
	vexGenerate (vexGetArgNullClass(), vexERRNO, 0, vexMESSAGE,
		     "_mtextHandleItemButtonDown -- NULL event", vexNULL);
    }
#endif

    /* first, see if our suerclass can handle it (for things like 
     * vname_Menu
     */
    ret = vclassSendSuper (_mtextGlobals->defaultClass,
			   vdialogHANDLE_ITEM_BUTTON_DOWN, (text, event));

    if (!ret) {
	int loc;
	loc = _mtextMapPointToPosition (text, 
					veventGetPointerX(event),
					veventGetPointerY(event));

	/* having the cursor blink during a drag looks weird */
	if (   (veventGetBinding(event) == vname_Select) 
	    || (mtextGetSelectType(text) == mtextSINGLE_POSITION_ONLY)) {
	    mtextSetAnchor (text, loc);

	    
	} else if (veventGetBinding(event) == vname_Adjust) {
	    mtextSetSelectionEnd (text, loc);
	}

	_mtextStopCaretBlink (text);

	/* !!! bug - if you click and hold, the cursor disappears.  It
	 * !!! should leave the insertion point there until dragging
	 * !!! starts.
	 */

	/* we must return TRUE if we want to get drag/detail and up events. */
	ret = TRUE;
    }

    /* sanity check because we've (potentially) changed internal state */
    mtextSanityCheck (text);

    return (ret);

} /* _mtextHandleItemButtonDown */ 




/* _mtextHandleItemButtonUp -- handle a mouse button release
 *
 *  -> text  -- the minitext that's been clicked upon
 *  -> event -- the event that diddit
 * <-        -- TRUE if we handled it, FALSE if we didn't.
 */
int _mtextHandleItemButtonUp (mtext *text, vevent *event)
{
    int ret = FALSE;

#if (vdebugDEBUG)
    if (event == NULL) {
	vexGenerate (vexGetArgNullClass(), vexERRNO, 0, vexMESSAGE,
		     "_mtextHandleItemButtonUp -- NULL event", vexNULL);
    }
#endif

    ret = vclassSendSuper (_mtextGlobals->defaultClass,
			   vdialogHANDLE_ITEM_BUTTON_UP, (text, event));

    if (!ret) {
	int loc;
	loc = _mtextMapPointToPosition (text, 
					veventGetPointerX(event),
					veventGetPointerY(event));

	if (mtextGetSelectType(text) == mtextSINGLE_POSITION_ONLY) {
	    mtextSetAnchor (text, loc);
	} else {
	    mtextSetSelectionEnd (text, loc);
	}

	_mtextStartCaretBlink (text);

	ret = TRUE;
    }

    /* sanity check because we've changed internal state */
    mtextSanityCheck (text);

    return (ret);
    
} /* _mtextHandleItemButtonUp */ 




/* _mtextHandleItemDrag -- handle mouse drag events.
 *
 *  -> text  -- the minitext that's being dragged around in
 *  -> event -- the event doing the dragging
 * <-        -- TRUE if we handled it, FALSE if we didn't
 */
int _mtextHandleItemDrag (mtext *text, vevent *event)
{
    int ret = FALSE;

#if (vdebugDEBUG)
    if (event == NULL) {
	vexGenerate (vexGetArgNullClass(), vexERRNO, 0, vexMESSAGE,
		     "_mtextHandleItemDrag -- NULL event", vexNULL);
    }
#endif

    ret = vclassSendSuper (_mtextGlobals->defaultClass,
			   vdialogHANDLE_ITEM_DRAG, (text, event));

    if (!ret) {
	int loc;
	loc = _mtextMapPointToPosition (text, 
					veventGetPointerX(event),
					veventGetPointerY(event));

	if (mtextGetSelectType(text) == mtextSINGLE_POSITION_ONLY) {
	    mtextSetAnchor (text, loc);
	} else {
	    mtextSetSelectionEnd (text, loc);
	}

	ret = TRUE;
    }

    /* sanity check because we've changed internal state */
    mtextSanityCheck (text);

    return (ret);
    
} /* _mtextHandleItemDrag */ 




/* _mtextHandleItemDetail -- handle mouse detail events.
 *
 *  -> text  -- the minitext that's being dragged around in
 *  -> event -- the event doing the dragging
 * <-        -- TRUE if we handled it, FALSE if we didn't
 */
int _mtextHandleItemDetail (mtext *text, vevent *event)
{
    int ret = FALSE;

#if (vdebugDEBUG)
    if (event == NULL) {
	vexGenerate (vexGetArgNullClass(), vexERRNO, 0, vexMESSAGE,
		     "_mtextHandleItemButtonDetail -- NULL event", vexNULL);
    }
#endif

    ret = vclassSendSuper (_mtextGlobals->defaultClass,
			   vdialogHANDLE_ITEM_DETAIL, (text, event));

    return (ret);
    
} /* _mtextHandleItemDetail */ 




/* _mtextHandleItemKeyDown -- handle key pressage.
 *
 *  -> text  -- the mtext being typed into
 *  -> event -- the keystroke event
 * <-        -- TRUE if we handled it, FALSE if we didn't
 */
int _mtextHandleItemKeyDown (mtext *text, vevent *event)
{
    int   ret = FALSE;
    vchar character;

#if (vdebugDEBUG)
    if (event == NULL) {
	vexGenerate (vexGetArgNullClass(), vexERRNO, 0, vexMESSAGE,
		     "_mtextHandleItemKeyDown -- NULL event", vexNULL);
    }
#endif

    /* send it on its way first (this will do any command dispatching
     * if appropriate
     */
    ret = vclassSendSuper (_mtextGlobals->defaultClass,
			   vdialogHANDLE_ITEM_KEY_DOWN, (text, event));

    if (!ret) {
	character = veventGetKeyChar (event);

	/* make sure there's a visible/meaningful glyph before putting it
	 * into the text stream.
	 */
	if (character != vcharNULL) {
	    mtextInsertCharacter (text, character);
	} else {
	    vdebugInform ("not inserting\n");
	}
	
	/* notify/dispatch just for grins */
	vdialogNotifyItem (mtextGetItem(text), event);
    }

    /* sanity check because we've changed internal state */
    mtextSanityCheck (text);

    return (ret);
    
} /* _mtextHandleItemKeyDown */ 




/*
 * ----- Keyboard focus stuff
 */


/* _mtextFocusItem -- the minitext has acquired focus
 *
 *  -> text -- the minitext getting focused
 */
void _mtextFocusItem (mtext *text)
{
    /* let the dialog manager munge internal flags, call drawing proces,
     * whatever
     */
    vclassSendSuper (_mtextGlobals->defaultClass, vdialogFOCUS_ITEM, (text));

    /* only draw selection if it makes sense given our current select type
     */
    if (   (mtextGetSelectType(text) != mtextNO_SELECTION)
	&& (vdialogItemIsEnabled(mtextGetItem(text)))) {
	
	if (mtextGetSelectionLength(text) == 0) {
	    mtextDrawCaret (text, mtextGetAnchor(text), mtextDRAW);

	} else {
	    vrect rect;
	    _mtextCalcPositionDifferenceRect (text, mtextGetAnchor(text),
					      mtextGetSelectionEnd(text),
					      &rect);
	    vdialogInvalItemRect (mtextGetItem(text), &rect, 
				  vwindowINVAL_OPAQUE);
	}
	
	_mtextStartCaretBlink (text);
    }

} /* _mtextFocusItem */




/* _mtextUnfocusItem -- the minitext has lost focus
 *
 *  -> text -- the minitext losing focus
 */
void _mtextUnfocusItem (mtext *text)
{
    _mtextStopCaretBlink (text);

    vclassSendSuper (_mtextGlobals->defaultClass, vdialogUNFOCUS_ITEM, (text));

    if (   (mtextGetSelectType(text) != mtextNO_SELECTION)
	&& (vdialogItemIsEnabled(mtextGetItem(text)))) {

	if (mtextGetSelectionLength(text) == 0) {
	    mtextDrawCaret (text, mtextGetAnchor(text), mtextREMOVE);

	} else {
	    vrect rect;
	    _mtextCalcPositionDifferenceRect (text, mtextGetAnchor(text),
					      mtextGetSelectionEnd(text), 
					      &rect);
	    vdialogInvalItemRect (mtextGetItem(text), &rect,
				  vwindowINVAL_OPAQUE);
	}
    }

} /* _mtextUnfocusItem */



/*
 * ----- state stuff
 */


/* _mtextOpenItem -- the dialog item is being opened and available to the
 *		     user.
 *
 *  -> text -- the dialog item getting opened
 */
void _mtextOpenItem (mtext *text)
{
    vclassSendSuper (_mtextGlobals->defaultClass, vdialogOPEN_ITEM, (text));

    /* open any owned items, and itemslists.  Install custom cursor rects,
     * recalc appearence-based attributes, etc...*/

    _mtextAddCursor (text);

} /* _mtextOpenItem */




/* _mtextCloseItem -- the dialog item is getting closed and will be removed
 * 		      from the user's presence
 *
 *  -> text -- the dialog item getting closed
 */
void _mtextCloseItem (mtext *text)
{
    
    /* close any owned items here (like scrollbars), remove custom cursor
     * rects, and close any owned item lists (for those of you doing container-
     * like objects
     */

    _mtextRemoveCursor (text);
    _mtextStopCaretBlink (text);

    vclassSendSuper (_mtextGlobals->defaultClass, vdialogCLOSE_ITEM, (text));

} /* _mtextCloseItem */




/* stuff that tells my editor (GNU emacs) how I like my code formatted */

/* Formatting information for emacs in c-mode
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


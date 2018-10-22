/* $Id: text.c,v 1.3 1995/01/19 19:08:31 chad Exp $ */
/* text.c -- implementation class-specific functions for the minitext example.
 *
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
 *    create and populate the class
 *    implement GetDefaultClass
 *       populate with object-level functions
 *    do client global stuff
 *    commented housekeeping functions
 * step one:
 *    add vclassSets for some dialogItem functions (DrawItem, button and key
 *        stuff, focus & unfocus)
 *    add some utility functions to support bare-bones entry (GetLineOrigin,
 *        mapPointToLine, mapPointToPosition, getPositionLocation
 *    add mtextDrawCaret implementation
 *    add caret blink timer (function to turn on/off, destruction in
 *        client shutdown)
 * step two:
 *    add mtextInsertCharacter implementation
 *    add command stuff (default space dict, command template table, 
 *        initialization, keyTempate struct, keyTemplate table)
 *    moved caret-shown global (for timer) into client globals
 *    add delete forward/backward implementation
 * step three:
 *    add setSelectionEnd and drawSelectedRange implementation
 *    add selectionEnd field test to sanity check
 *    add selection deleting in delFwd, delBckwd, and insertCharacter
 *    do selEnd manupulation in SetAnchor
 *    make invalidations more intelligent
 * step four:
 *    fix color usage in draw selected range
 * step five:
 *    add selectType method
 *    modify setAnchor to obey selectType
 *    add selectType check to sanityCheck
 *    add vclassSetting for attribute overrides
 *    add predef name setup.
 * step six:
 *    add cursor class variable
 *    add utilities to add or remove the cursor
 *    add forgotten vclassSet of changedParentAttribute
 * step seven:
 *    factor drawDevice stuff into a single function.
 *    add argument checking
 *    fix bugs shown by added arg checking (d'oh!!)
 *    add some private names for resource storage
 *    use some color scheme stuff
 */

#include <vport.h>


/* only include the header files we need for this particular file
 */

#ifndef  vclientINCLUDED
#include vclientHEADER
#endif

#ifndef  vtimerINCLUDED
#include vtimerHEADER
#endif

#ifndef  vkeyINCLUDED /* for keystroke storage into keymap dictionaries */
#include vkeyHEADER 
#endif


/* include local headers */
#include "mtext.h"
#include "priv.h"


/*
 * ----- Useful #defines
 */

/* ABS -- absolue value macro
 *
 *  -> x -- the numeric value
 * <-    -- the absoulte value (e.g. the negative of negative numbers
 */
#ifndef ABS
#define ABS(x)	( ( (x) < 0 ) ? -(x) : (x) )
#endif




/*
 * ----- "Modual" globals
 */


/* handle to our vclient-allocated globals.
 */
void **_mtextMaster = NULL;



/* 
 * command space stuff
 */

/* the space of commands that we're defining.  This will be put into the
 * default mtext class's vobjectSPACE class variable
 */
static vcommandSpace _mtextDefaultSpace;


/* the built-in commands that "come for free" to users of this object and
 * get put into the default space.
 */
static const vcommandSelectorTemplate _mtextSelectorTemplates[] = {
    { "BackwardDelete",  mtextSELECT_BACKWARD_DELETE },
    { "ForwardDelete",   mtextSELECT_FORWARD_DELETE  }
};




/*
 * key mapping stuff
 */

/* key map that maps keystrokes to commands.  Right now this is a global-
 * global, which could be a Bad Thing if different look and feels are
 * active in different clients (potentially different key mappage)
 *
 * This will be put into the default metx calss's vobjectKEY_MAP class 
 * variable
 */
static vdict _mtextDefaultKeyMap;


/* key template structure for specifying the key-to-selectorCommandIDs. 
 * The table of these will be walked and stored into the default key map
 */
typedef struct keyTemplate {
    const char *commandName;
    vkeyStroke	stroke;
} keyTemplate;


/* these key bindings could/should be in resources.  The current way keystrokes
 * are represeneted in resoruces (as seemingly random integers) obfuscate more
 * than enlighten IMNSHO, but this restricts client flexibility.  You make
 * the call.  You decide.
 */
static const keyTemplate _mtextKeyTemplates[] = {
    { "BackwardDelete", vkeyComputeStroke (vkeyBACKSPACE, 0) },
    { "ForwardDelete",  vkeyComputeStroke (vkeyDELETE, 0) },
};




/*
 * ID_Attribute stuff
 */


/* this holds the mapping between ID_ATTRIBUTE integer identifiers and
 * the vnames that describe them.  This dictionary is used in two places:
 * inside of the attributedObject manager to determine which attributes to
 * put into commandManager context dictionaries, as well as in our own
 * object.c to map vname attributes to their integer counterparts so we can
 * use the C switch statement to determine what the Right Thing to do is.
 *
 * This variable isn't static (like the rest of these globals) because another
 * source file needs to use this dictionary to make the name->id mappings.
 */
vdict _mtextDefaultIDAttributeDict;


/* the table that maps the ID_attributes with their symbolic names.
 * We only put the ID_attributes that we're adding overAndAbove the standard
 * set in this table.  We get the dialogItem ID_Attributes along for free
 * when we set things up later on.
 */
static const vobjectIDAttributeTemplate _mtextIDAttributeTemplates[] = {
    { "SelectType",	mtextID_ATTRIBUTE_SELECT_TYPE }
};




/*
 * Name predefinitions
 */


/* the table of vnames that we export.  If your item creates some vnames
 * that are useful to clients (for accessing ID attributes say), this 
 * is one way of providing them.  This array has a corresponding "extern"
 * statement in mtext.h, along with #defines that make symbolic mtext_Name
 * type thingies return the proper vname without having to make the client
 * intern things all over the place.
 */
const vname *_mtextPredefs[_mtextPredefCOUNT];


/* table of predefinitions.  Be *very careful* when modifying the name table
 * using this technique.  If you change the ordering (or insert something),
 * you need to change it in two plces:  the ordering of contstants in
 * the _mtextPredefEnum and in the table that follows.
 * The predef value is linked to the literal string only by virtue of the
 * numeric index in the enum and in the array.  With big sets of names, it's
 * very easy to get the name or number in the wrong place.
 */
static const char *_mtextPredefLiterals[_mtextPredefCOUNT] = {
    "SelectType",
    "Contents",
    "Length",
    "AllocLeft",
    "Anchor",
    "SelectionEnd",
};




/*
 * ----- non-public exported utility functions
 */


/* _mtextGetLineOrigin -- return the (x, y) position of where a particular
 *			  line should start drawing
 *
 *  -> text -- the minitext object to do the calculations relative to
 *  -> line -- the line to get the origin for
 * <-  x, y -- the point where the line starts. Pass NULL if you're not
 * 	       interested in a particular element
 */
void _mtextGetLineOrigin (mtext *text, int line, int *x, int *y)
{
    vdialogItem *item;
    const vrect *rect;
    vfont *font;

#if (vdebugDEBUG)
    if (text == NULL) {
	vexGenerate (vexGetArgNullClass(), vexERRNO, 0, vexMESSAGE,
		     "_mtextGetLineOrigin -- NULL text", vexNULL);
    }
    if (line < 0) {
	vexGenerate (vexGetArgClass(), vexERRNO, 0, vexMESSAGE,
		     "_mtextGetLineOrigin -- negative line", vexNULL);
    }
#endif

    item = mtextGetItem(text);
    rect = vdialogGetItemRect (item);
    font = vdialogDetermineItemFont (item);

    if (x != NULL) {
	*x = rect->x + 5;
    }
    
    /* !!! when we do wrapping, this will probably turn into a table lookup.
     * !!! if we do scrolling, an offset will need to be added
     */
    if (y != NULL) {
	*y = rect->y + rect->h - vfontHeight(font) - vfontDescent(font);
    }
    
} /* _mtextGetLineOrigin */




/* _mtextBEYOND_RANGE -- ultra private constant used by _mtextMapPointToLine.
 *                       It returns this when the given point is below every
 *                       line of the minitext.
 */
#define _mtextBEYOND_RANGE -1




/* _mtextMapPointToLine -- given an (x, y) point, return the line that's under
 *                         that point.
 *
 *  -> text -- the minitext used to compute the line under the point
 *  -> x,y  -- the point
 * <-       -- which line lives under that point, or _mtextBEYOND_RANGE if
 *             the point is completely underneath the bottom line
 */
int _mtextMapPointToLine (mtext *text, int x, int y)
{
    vfont *font;
    int originX, originY, ret;

#if (vdebugDEBUG)
    if (text == NULL) {
	vexGenerate (vexGetArgNullClass(), vexERRNO, 0, vexMESSAGE,
		     "_mtextMapPointToLine -- NULL text", vexNULL);
    }
#endif
    
    font = vdialogDetermineItemFont (mtextGetItem(text));
    _mtextGetLineOrigin (text, 0, &originX, &originY);

    ret = (y < (originY - vfontDescent(font))) ? _mtextBEYOND_RANGE : 0;

    return (ret);

} /* _mtextMapPointToLine */




/* _mtextMapPointToPosition -- given a point, return the position that is
 *                             closest to that point. 
 *
 *  -> text -- the minitext used to determine the character position
 *  -> x, y -- the point to text
 * <-       -- the position.  0 is all the way at the beginning,
 *             mtextGetLength() is all the way at the end.
 */
int _mtextMapPointToPosition (mtext *text, int x, int y)
{
    vfont *font;
    int line, loc = 0;

#if (vdebugDEBUG)
    if (text == NULL) {
	vexGenerate (vexGetArgNullClass(), vexERRNO, 0, vexMESSAGE,
		     "_mtextMapPointToPosition -- NULL text", vexNULL);
    }
#endif

    font = vdialogDetermineItemFont (mtextGetItem(text));

    line = _mtextMapPointToLine (text, x, y);

    if (line == _mtextBEYOND_RANGE) {
	/* last character */
	loc = mtextGetLength (text);  /* after the last character */

    } else {
	vchar *scan, *stop;
	int sum, width;
	int originX;

	/* since we're one-line, just scan until we find where x is located */

	_mtextGetLineOrigin (text, line, &originX, NULL);

	if (x <= originX) {
	    /* the <= is necessary for clicking *right* on the character
	     * boundry at the zero position. */
	    loc = 0;

	} else {
	    sum = originX;
	    
	    scan = text->contents;
	    stop = scan + mtextGetLength(text);
	    
	    /* scan until we cross X */
	    while ((scan < stop) && (sum < x)) {
		width = vfontSizedStringWidthX (font, scan, 1);
		sum += width;
		scan++;
		loc++;
	    }
	    
	    if (scan != stop) { /* e.g. we stopped before exhausting chars */
		sum -= (width >> 1);
		if (x < sum) {
		    loc--;
		}
	    } else {
		if (loc != mtextGetLength(text)) {
		    vdebugWarn ("BARF\n");
		}
	    }
	}
    }

    return (loc);
    
} /* _mtextMapPointToPosition */




/* _mtextGetPositionLocation -- return the 'X' location in the line where
 *                              a particular character position is
 *
 *  -> text     -- the minitext to get the character positionf or
 *  -> position -- the character position of interest
 * <-           -- the x coordinate of the location of that position
 */
int _mtextGetPositionLocation (mtext *text, int position)
{
    vfont *font;
    int    x, sum;
    vchar *scan, *stop;

#if (vdebugDEBUG)
    if (text == NULL) {
	vexGenerate (vexGetArgNullClass(), vexERRNO, 0, vexMESSAGE,
		     "_mtextGetPositionLocation -- NULL text", vexNULL);
    }
    if (position < 0) {
	vexGenerate (vexGetArgClass(), vexERRNO, 0,  vexMESSAGE,
		    "_mtextGetPositionLocation -- negative position", vexNULL);
    }
    if (position > mtextGetLength(text)) {
	vexGenerate (vexGetArgClass(), vexERRNO, 0,  vexMESSAGE,
		    "_mtextGetPositionLocation -- position too big", vexNULL);
    }
#endif
    
    font = vdialogDetermineItemFont (mtextGetItem(text));

    _mtextGetLineOrigin (text, 0, &x, NULL);
    scan = text->contents;
    stop = scan + position;
    
    sum = x;
    while (scan < stop) {
	sum += vfontSizedStringWidthX (font, scan, 1);
	scan++;
    }

    return (sum);

} /* _mtextGetPositionLocation */




/* _mtextCalcPositionDifferenceRect -- calculate the rectangle that encloses
 * 				       two character positions.  (this is the
 *				       same as the rectangle to be drawn to
 * 				       indicate a selection between these two
 *				       positions.)
 *
 *  -> text -- the minitext to key the difference off of
 *  -> pos1 -- one end of the character range
 *  -> pos2 -- the other end of the character range
 * <-  rect -- the rectanlge that holds the two.
 *
 * o pos1 and pos2 don't have to be ordered relative to each other.
 * o this function will be limited value when wrapping is done, unless it's
 *   called individually for every line.
 */
void _mtextCalcPositionDifferenceRect (mtext *text, int pos1, int pos2,
				       vrect *rect)
{
    vdialogItem *item;
    vfont       *font;
    int          biggun, littlun;
    int          textX, textY;

#if (vdebugDEBUG)
    if (text == NULL) {
	vexGenerate (vexGetArgNullClass(), vexERRNO, 0, vexMESSAGE,
		     "_mtextCalcPositionDifferenceRect -- NULL text", vexNULL);
    }
    if ((pos1 < 0) || (pos2 < 0)) {
	vexGenerate (vexGetArgClass(), vexERRNO, 0,  vexMESSAGE,
		    "_mtextCalcPositionDifferenceRect -- negative position[s]",
		    vexNULL);
    }
    if (   (mtextGetLength(text) > 0) 
	&& ((pos1 > mtextGetLength(text)) || (pos2 > mtextGetLength(text)))) {
	vexGenerate (vexGetArgClass(), vexERRNO, 0,  vexMESSAGE,
		    "_mtextCalcPositionDifferenceRect -- position[s] too big",
		    vexNULL);
    }
#endif

    item = mtextGetItem(text);
    font = vdialogDetermineItemFont (item);
    
    biggun = vMAX (pos1, pos2);
    littlun = vMIN (pos1, pos2);
    
    _mtextGetLineOrigin (text, 0, NULL, &textY);
    textX = _mtextGetPositionLocation (text, littlun);
    
    rect->x = textX;
    rect->y = textY- vfontDescent(font);
    
    rect->w = _mtextGetPositionLocation(text, biggun) - textX;
    rect->h = vfontHeight(font) + vfontDescent(font);

} /* _mtextCalcPositionDifferenceRect */




/* _mtextAddCursor -- add a vwindow cursor rect over the item. 
 *
 *  -> text -- the minitext to add the cursor rect for
 *
 * there's a bug (b4980) where if the client does a vdialogSetItemCursor,
 * this will not succeeed in only covering the content area.  DialogItem
 * is doing a AddCursorRect over the entire item, covering the scroll bars.
 */
void _mtextAddCursor (mtext *text)
{
    vwindow     *window;
    vdialogItem *item;
    vcursor     *cursor;

#if (vdebugDEBUG)
    if (text == NULL) {
	vexGenerate (vexGetArgNullClass(), vexERRNO, 0, vexMESSAGE,
		     "_mtextAddCursor -- NULL text", vexNULL);
    }
#endif

    item = mtextGetItem (text);

    cursor = vclassGet (mtextGetClass(text), mtextCURSOR);

    /* make sure it's valid that we add the cursor */
    if (   (cursor != NULL)
	&& ((text->flags & _mtextCURSOR_ADDED) == 0)
	&& vdialogItemIsVisible(item)
	&& vdialogItemIsEnabled(item)) {

	window = vdialogDetermineItemWindow (item);

	if (window != NULL) {
	    mtextCalcCursorRect (text, &text->cursorRect);

	    if (!vrectMIsEmpty(&text->cursorRect)) {
		vwindowAddCursorRect (window, cursor, &text->cursorRect);
		text->flags |= _mtextCURSOR_ADDED;
	    }
	}
    }

} /* _mtextAddCursor */




/* _mtextRemoveCursor -- remove a vwindow cursor rect over the item.
 *
 *  -> text -- the minitext to remove the cursor rect for.
 */
void _mtextRemoveCursor (mtext *text)
{
    vwindow     *window;
    vcursor     *cursor;

#if (vdebugDEBUG)
    if (text == NULL) {
	vexGenerate (vexGetArgNullClass(), vexERRNO, 0, vexMESSAGE,
		     "_mtextRemoveCursor -- NULL text", vexNULL);
    }
#endif

    if ((text->flags & _mtextCURSOR_ADDED) != 0) {
	/* this could break if the cursor gets changed in the MeanTime
	 * without the cursor rect being recreated
	 */

	cursor = vclassGet (mtextGetClass(text), mtextCURSOR);

	window = vdialogDetermineItemWindow (mtextGetItem(text));
	vwindowRemoveCursorRect (window, cursor, &text->cursorRect);

	text->flags &= ~_mtextCURSOR_ADDED;
    }

} /* _mtextRemoveCursor */




/* _mtextChangeCursorRect -- the minitext has moved on the screen or changed
 *			     size.  Update the cursor rectangle to match
 *
 *  -> text -- the minitext to change the cursor rect for
 */
void _mtextChangeCursorRect (mtext *text)
{
    vcursor *cursor;
    vwindow *window;
    vrect    rect; /* the new rectangle */
    
#if (vdebugDEBUG)
    if (text == NULL) {
	vexGenerate (vexGetArgNullClass(), vexERRNO, 0, vexMESSAGE,
		     "_mtextChangeCursorRect -- NULL text", vexNULL);
    }
#endif

    if ((text->flags & _mtextCURSOR_ADDED) != 0) {
	cursor = vclassGet (mtextGetClass(text), mtextCURSOR);

	window = vdialogDetermineItemWindow (mtextGetItem(text));

	mtextCalcCursorRect (text, &rect);
	
	vwindowChangeCursorRect (window, cursor, &text->cursorRect, &rect);

	/* replace the old with the new */
	text->cursorRect = rect;
    }

} /* _mtextChangeCursorRect */





/*
 * ----- visual stuff
 */


/* _mtextDrawCaretImmediate -- draw/undraw the insertion point at the indicated
 * 		               character position immediatlely by drawing into
 * 			       the item's draw device.
 *
 *  -> text     -- the minitext to draw the caret for
 *  -> position -- the character position to draw it at
 *  -> state    -- mtextDRAW to draw the caret, mtextREMOVE to erase it.
 */
void _mtextDrawCaretImmediate (mtext *text, int position, int state)
{
    vdialogItem *item;
    vrect        clippy;

#if (vdebugDEBUG)
    if (text == NULL) {
	vexGenerate (vexGetArgNullClass(), vexERRNO, 0, vexMESSAGE,
		     "_mtextDrawCaretImmediate -- NULL text", vexNULL);
    }
    if (position < 0) {
	vexGenerate (vexGetArgClass(), vexERRNO, 0,  vexMESSAGE,
		    "_mtextDrawCaretImmediate -- negative position", vexNULL);
    }
    if ((mtextGetLength(text) > 0) && (position > mtextGetLength(text))) {
	vexGenerate (vexGetArgClass(), vexERRNO, 0,  vexMESSAGE,
		    "_mtextDrawCaretImmediate -- position too big", vexNULL);
    }
    if ((state != mtextDRAW) && (state !=  mtextREMOVE)) {
	vexGenerate (vexGetArgClass(), vexERRNO, 0,  vexMESSAGE,
		    "_mtextDrawCaretImmediate -- bad state value", vexNULL);
    }
#endif

    item = mtextGetItem(text);
    clippy = *vdialogGetItemRect(item);


    if (vdialogItemHasBorder(item)) {
	vrectInset (&clippy,
		    vdialogDetermineItemLineWidth(item),
		    vdialogDetermineItemLineWidth(item),
		    &clippy);
    }

    vdrawGSave (); {
	vdialogItemDrawDevice (mtextGetItem(text));
	vdialogSetItemDraw (mtextGetItem(text));

	vdrawRectsClip (&clippy, 1);
	
	mtextDrawCaret (text, position, state);
    } vdrawGRestore ();
    
} /* _mtextDrawCaretImmediate */




/* _mtextDrawCaret -- draw/undraw the insertion point at the indicated
 * 		      character position.
 *
 *  -> text     -- the minitext to draw the caret for
 *  -> position -- the character position to draw it at
 *  -> state    -- mtextDRAW to draw the caret, mtextREMOVE to erase it.
 */
void _mtextDrawCaret (mtext *text, int position, int state)
{
    vdialogItem *item = mtextGetItem (text);
    vfont       *font = vdialogDetermineItemFont (item);
    int          x, y;

#if (vdebugDEBUG)
    /* note we're not checking for text == NULL.  Since this is a method,
     * we *can't* get here unless text is valid
     */
    if (position < 0) {
	vexGenerate (vexGetArgClass(), vexERRNO, 0,  vexMESSAGE,
		    "_mtextDrawCaret -- negative position", vexNULL);
    }
    if ((mtextGetLength(text) > 0) && (position > mtextGetLength(text))) {
	vexGenerate (vexGetArgClass(), vexERRNO, 0,  vexMESSAGE,
		    "_mtextDrawCaret -- position too big", vexNULL);
    }
    if ((state != mtextDRAW) && (state !=  mtextREMOVE)) {
	vexGenerate (vexGetArgClass(), vexERRNO, 0,  vexMESSAGE,
		    "_mtextDrawCaret -- bad state value", vexNULL);
    }
#endif

    x = _mtextGetPositionLocation (text, position);

    _mtextGetLineOrigin (text, 0, NULL, &y);
    y -= vfontDescent (font);

    vdrawGSave (); {
	if (state == mtextDRAW) {
	    vdrawSetColor (vdialogDetermineItemForeground (item));
	} else if (state == mtextREMOVE) {
	    vdrawSetColor (vdialogDetermineItemBackground (item));
	}

	vdrawSetLineWidth (1);
	
	vdrawMoveTo (x - 1, y);
	vdrawLineTo (x - 1, y + vfontHeight(font) + vfontDescent(font));

	vdrawStroke ();

    } vdrawGRestore ();

} /* _mtextDrawCaret */




/* _mtextDrawSelectedRange -- draw the characters and hiliting to indicate
 * 			      selected characters between two points
 * 
 *  -> text  -- the minitext to draw the selected range for
 *  -> start -- one end of the range
 *  -> end   -- the other end of the range
 *
 * start and end don't need to be ordered relative to each other
 */
void _mtextDrawSelectedRange (mtext *text, int start, int end)
{
    vdialogItem *item = mtextGetItem(text);
    int littlun, biggun;
    int textX, textY;
    vrect rect;

    _mtextCalcPositionDifferenceRect (text, start, end, &rect);

    biggun = vMAX (start, end);
    littlun = vMIN (start, end);

    _mtextGetLineOrigin (text, 0, NULL, &textY);
    textX = _mtextGetPositionLocation (text, littlun);

    vdrawGSave (); {
	vcolorScheme scheme;

	vdialogDetermineItemColorSchemeState (item, 
					      (  vcolorFLAG_BACKGROUND_HILITE
					       | vcolorFLAG_FOREGROUND_HILITE),
					      &scheme);
	vdrawSetColor (vcolorGetSchemeBackgroundHilite(&scheme));
	vdrawRectsFill (&rect, 1);
	vdrawSetColor (vcolorGetSchemeForegroundHilite(&scheme));
	vdrawMoveTo (textX, textY);
	vdrawSizedShow (text->contents + littlun, biggun - littlun);
    } vdrawGRestore ();

} /* _mtextDrawSelectedRange */




/* _mtextCalcCursorRect -- calculate the screen real-estate that a cursor
 * 			   rectangle should cover
 *
 *  -> text -- the minitext to calcuate the rectangle for
 * <-  rect -- the rectangle that it should cover.  Return an empty rectangle
 *	       if having a cursor rect doesn't make sense at this time. 
 */
void _mtextCalcCursorRect (mtext *text, vrect *rect)
{
    vdialog         *dialog;
    vdialogItemList *itemList;
    vdialogItem	    *item = mtextGetItem(text);

#if (vdebugDEBUG)
    if (rect == NULL) {
	vexGenerate (vexGetArgNullClass(), vexERRNO, 0, vexMESSAGE,
		     "_mtextCalcCursorRect -- negative rect.", vexNULL);
    }
#endif

    dialog = vdialogDetermineItemDialog (item);
    itemList = vdialogGetItemItemList (item);

    if ((itemList != NULL) && (dialog != NULL)) {
	*rect = *vdialogGetItemRect(item);

	/* shrinkify the rectangle if we're inside of a containing object */
	if (itemList != vdialogGetItemList (dialog)) {
	    vdialogTransformItemListRectClip (itemList, rect, rect);
	}

    } else {
	rect->x = rect->y = rect->w = rect->h = 0;
    }

} /* _mtextCalcCursorRect */




/*
 * ----- selection stuff
 */


/* _mtextSetAnchor -- set the anchor to a given character position
 *
 *  -> text     -- the minitext to set the anchor for
 *  -> position -- the position to set it to.
 *
 * Setting the anchor collapses the selection.
 *
 * o !!! I'm not too keen of this massaging the incoming position, but it does
 *   !!! simplify the calling code w.r.t. keyboard traversal.  Maybe add
 *   !!! a MoveAnchor entrypoint?
 * o !!! The auto-caret drawing is disturbing [it's an awful lot of work] and
 *   !!! gives some odd visual results when auto-repeat deleting stuff.
 */
void _mtextSetAnchor (mtext *text, int position)
{
    vbool focusIsVisible = vdialogItemFocusIsVisible(mtextGetItem(text));

#if (vdebugDEBUG)
    /* the position value range check wasn't forgotton. */
#endif

    /* erase existing block selection if it exists */
    if (mtextGetSelectionLength(text) > 0) {
	vrect rect;
	_mtextCalcPositionDifferenceRect (text, mtextGetAnchor(text),
					  mtextGetSelectionEnd(text), &rect);
	vdialogInvalItemRect (mtextGetItem(text), &rect, vwindowINVAL_OPAQUE);
    }

    if (position < 0) {
	position = 0;
    }
    
    if (position > mtextGetLength(text)) {
	position = mtextGetLength (text);
    }

    if (mtextGetSelectionEnd(text) != position) {
	/* !!! I don't like going aroynd mtextSetSelectionEnd here, but I
	 * !!! also don't want the invalidation and subsequent redraw. */
	text->selectionEnd = position;
    }

    if (position != text->anchor) {

	if (mtextGetSelectType(text) != mtextNO_SELECTION) {
	    if (focusIsVisible) {
		_mtextDrawCaretImmediate (text, text->anchor, mtextREMOVE);
		_mtextDrawCaretImmediate (text, position, mtextDRAW);
	    }
	}
	
	text->anchor = position;
    }

    if (focusIsVisible) {
	_mtextStartCaretBlink (text);
    }

    mtextSanityCheck (text);

} /* _mtextSetAnchor */




/* _mtextSetSelectionEnd -- set the "endpoint" of the selection.  Everything
 *                          between the anchor and the selection end is
 *                          considered to be selected.  anchor == selectionEnd
 *                          means an insertion point will be shown.
 *
 *  -> text     -- the minitext to change the selection in
 *  -> position -- the character position to put the end of the selection at.
 *
 * (see previous function's comments about pinning the values
 */
void _mtextSetSelectionEnd (mtext *text, int position)
{
#if (vdebugDEBUG)
    /* the position value range check wasn't forgotton. */
#endif

    if (position < 0) {
	position = 0;
    }

    if (position > mtextGetLength(text)) {
	position = mtextGetLength (text);
    }

    if (position != text->selectionEnd) {
	vrect rect;
	_mtextCalcPositionDifferenceRect (text, position, text->selectionEnd,
					  &rect);
	vdialogInvalItemRect (mtextGetItem(text), &rect, vwindowINVAL_OPAQUE);

	text->selectionEnd = position;
    }

} /* _mtextSetSelectionEnd */




/* _mtextSetSelectType -- set the selection methodology that the minitext
 *			  will use
 *
 *  -> text -- the minitext to set the select type for
 *  -> type -- the type of selection
 *
 * The built-in types are mtextNO_SELECTION (can't select anything or
 * put an insertion point in), mtextSINGLE_POSITION_ONLY (no range selection),
 * and mtextRANGE_SELECTION.  Values out of this range are still stored in
 * the instance for potential extension by subclasses.  The extension
 * mechanism (e.g. how it reacts with selection and drawing) hasn't been
 * thought through, so this could be a really half-baked idea.
 */
void _mtextSetSelectType (mtext *text, int type)
{
    vrect rect;

    if (mtextGetSelectType(text) != type) {

	/* figure out where we may need to invalidate */
	_mtextCalcPositionDifferenceRect (text, mtextGetAnchor(text),
					  mtextGetSelectionEnd(text), &rect);

	text->selectType = type;

	/* let folks know we changed */
	vdialogChangedItemAttributeValue (mtextGetItem(text), mtext_SelectType,
					  &text->selectType, &type);

	/* make sure our internal and visible state jives with type.
	 * As an aside, we could have implemented this portion from the
	 * vobjectCHANGED_ATTRIBUTE override.
	 */
	switch (type) {

	    case mtextNO_SELECTION: {
		if (mtextGetSelectionLength(text) == 0) {

		    if (vdialogItemFocusIsVisible(mtextGetItem(text))) {
			_mtextDrawCaretImmediate (text, mtextGetAnchor(text),
						  mtextREMOVE);
		    }

		} else {
		    vdialogInvalItemRect (mtextGetItem(text), &rect,
					  vwindowINVAL_OPAQUE);
		}

		_mtextStopCaretBlink (text);

		break;
	    }

	    case mtextSINGLE_POSITION_ONLY: {
		mtextSetSelectionEnd (text, mtextGetAnchor(text));

		if (vdialogItemFocusIsVisible(mtextGetItem(text))) {
		    _mtextStartCaretBlink (text);
		}

		break;
	    }

	    case mtextRANGE_SELECTION: {
		vdialogInvalItemRect (mtextGetItem(text), &rect,
				      vwindowINVAL_OPAQUE);

		if (vdialogItemFocusIsVisible(mtextGetItem(text))) {
		    _mtextStartCaretBlink (text);
		}

		break;
	    }
	    
	    default: {
		/* means a subclass must have added something */
		break;
	    }
	}
    }

} /* _mtextSetSelectType */




/*
 * ----- editing stuff
 */


/* _mtextInsertCharacter -- insert a single character, nuking any selection
 *                          that might exist.
 *
 *  -> text      -- the minitext to insert in
 *  -> character -- the character to insert
 */
void _mtextInsertCharacter (mtext *text, vchar character)
{
    if (mtextGetSelectionLength(text) > 0) {
	mtextDeleteForward (text);
    }

    if (text->allocLeft == 0) {
	text->allocLeft = _mtextALLOC_AMOUNT;
	text->contents = vmemRealloc (text->contents, sizeof(vchar) 
				      * (text->allocLeft + text->length));
    }

    /* open space for the new character */
    
    if (mtextGetAnchor(text) < text->length) {
	/* only move memory if the anchor isn't in the last position */
	(void) vmemMove (text->contents + mtextGetAnchor(text), 
			 text->contents + mtextGetAnchor(text) + 1,
			 sizeof(vchar) * (text->length 
					  - mtextGetAnchor(text)));
    }

    text->contents[mtextGetAnchor(text)] = character;

    text->length++;
    text->allocLeft--;

    {
	vrect rect;
	/* !!! will need work when wrapping */
	_mtextCalcPositionDifferenceRect (text, mtextGetAnchor(text),
					  mtextGetLength(text), &rect);
	vdialogInvalItemRect (mtextGetItem(text), &rect, vwindowINVAL_OPAQUE);
    }

    mtextSetAnchor (text, mtextGetAnchor(text) + 1);

    vdialogChangedItemAttributeNone (mtextGetItem(text), vname_MinSize);

    mtextSanityCheck (text);

} /* _mtextInsertCharacter */




/* _mtextDeleteForward -- delete the character that follows the anchor
 *
 *  -> text -- the minitext to delete in
 *
 * This nukes any selected range if it exists.
 *
 * Nothing happns if delete forward is performed with the anchor at the
 * very end of the text.
 */
void _mtextDeleteForward (mtext *text)
{
    int length = 1;
    vrect rect;

    _mtextCalcPositionDifferenceRect (text, mtextGetAnchor(text),
				      mtextGetLength(text), &rect);
    
    if (mtextGetSelectionLength(text) > 0) {
	length = mtextGetAnchor(text) - mtextGetSelectionEnd(text);

	length = ABS(length);

	mtextSetAnchor (text, vMIN (mtextGetAnchor(text),
				    mtextGetSelectionEnd(text)));

    }

    if (mtextGetAnchor(text) < mtextGetLength(text)) {
	
	(void) vmemMove (text->contents + mtextGetAnchor(text) + length,
			 text->contents + mtextGetAnchor(text),
			 sizeof(vchar) * (text->length - length
					  - mtextGetAnchor(text)));
	text->length -= length;
	text->allocLeft += length;

	vdialogInvalItemRect (mtextGetItem(text), &rect, vwindowINVAL_OPAQUE);
    }

    vdialogChangedItemAttributeNone (mtextGetItem(text), vname_MinSize);

    mtextSanityCheck (text);

} /* _mtextDeleteForward */




/* _mtextDeleteBackward -- delete the character that precedes the anchor
 *
 *  -> text -- the minitext to delete in
 *
 * This nukes any selected range if it exists.
 *
 * Nothing happns if delete backward is performed with the anchor at the
 * very beginning of the text.
 */
void _mtextDeleteBackward (mtext *text)
{
    vrect rect;

    if (mtextGetSelectionLength(text) > 0) {
	mtextDeleteForward (text);

    } else {
	
	if (mtextGetAnchor(text) > 0) {
	    int oldAnchor = mtextGetAnchor(text);
	    _mtextCalcPositionDifferenceRect (text, mtextGetAnchor(text) - 1,
					      mtextGetLength(text), &rect);
	    
	    /* need to change the anchor before changing length.  Need to
	     * still be able to access that last position to undraw 
	     * the insertion point.
	     */
	    _mtextSetAnchor (text, oldAnchor - 1);

	    (void) vmemMove (text->contents + oldAnchor,
			     text->contents + oldAnchor - 1,
			     sizeof(vchar) * (text->length - oldAnchor));
	    text->length--;
	    text->allocLeft++;

	    vdialogInvalItemRect (mtextGetItem(text), &rect, 
				  vwindowINVAL_OPAQUE);
	}
    }
    
    vdialogChangedItemAttributeNone (mtextGetItem(text), vname_MinSize);

    mtextSanityCheck (text);

} /* _mtextDeleteBackward */




/*
 * ----- Debugging
 */


#if (vdebugDEBUG)

/* _mtextSanityCheck -- asert object invarients.  If a function leaves it in
 *                      an inconsistent state, barf.
 *
 *  -> text -- the minitext to sanitycheck
 *
 * Throws a /Module exception if something goes wrong.
 * This function is only included in vportDEBUG=TRUE builds, so this
 * can be as expensive as is necessary to do proper checking.
 */
void _mtextSanityCheck (mtext *text)
{
    unsigned short usefulFlags;

    if (text->length < 0) {
	vexGenerate (vexGetModuleClass(), vexERRNO, 0, vexMESSAGE,
		     "mtext failed sanity check - negative length", vexNULL);
    }

    if (text->allocLeft < 0) {
	vexGenerate (vexGetModuleClass(), vexERRNO, 0, vexMESSAGE,
		     "mtext failed sanity check - negative allocLeft", 
		     vexNULL);
    }

    if ((text->anchor < 0) || (text->anchor > text->length)) {
	vexGenerate (vexGetModuleClass(), vexERRNO, 0, vexMESSAGE,
		     "mtext failed anchor-position sanity check", vexNULL);
    }

    if ((text->selectionEnd < 0) || (text->selectionEnd > text->length)) {
	vexGenerate (vexGetModuleClass(), vexERRNO, 0, vexMESSAGE,
		     "mtext failed selectionEnd-position sanity check", 
		     vexNULL);
    }

    if (   (mtextGetSelectType(text) == mtextSINGLE_POSITION_ONLY)
	&& (mtextGetAnchor(text) != mtextGetSelectionEnd(text))) {
	vexGenerate (vexGetModuleClass(), vexERRNO, 0, vexMESSAGE,
		     "mtext failed singlePosition select type sanity check",
		     vexNULL);
    }

    usefulFlags = _mtextMODIFYABLE | _mtextCURSOR_ADDED;

    /* if any additional bits are set, someone is mucking with our
     * flags, or else it's uninitialized.
     */

    if ((text->flags & ~usefulFlags) != 0) {
	vexGenerate (vexGetModuleClass(), vexERRNO, 0, vexMESSAGE,
		     "mtext failed flag cleanliness test", vexNULL);
    }

    /* checking of the selectType isn't done because clients may extend
     * the selection model.  Any changes to the selection model, though,
     * must jive with the above invarients, though.
     */

} /* _mtextSanityCheck */

#endif




/*
 * ----- Cursor blinking stuff
 */


/* _mtextCaretTimerNotify -- timer notification that blinks the insertion
 *                           point.  The timer has the minitext pointer hidden
 *                           under its data pointer
 *
 *  -> timer -- the timer performing the notification
 */
static void _mtextCaretTimerNotify (vtimer *timer)
{
    mtext *text = (mtext*)vtimerGetData (timer);

#if (vdebugDEBUG)
    if (text == NULL) {
	/* this is really bad and should never happen */
	vexGenerate (vexGetModuleClass(), vexERRNO, 0, vexMESSAGE,
		     "_mtextCaretTimerNotify -- NULL text in timer data",
		     vexNULL);
    }
#endif

    /* don't blink if lots of stuff gets selected.  Shut down the timer too. */
    if (mtextGetSelectionLength(text) > 0) {
	_mtextStopCaretBlink(text);

    } else {

	if (_mtextGlobals->showCaret) {
	    _mtextDrawCaretImmediate (text, mtextGetAnchor(text), mtextDRAW);
	} else {
	    _mtextDrawCaretImmediate (text, mtextGetAnchor(text), mtextREMOVE);
	}

	_mtextGlobals->showCaret = !_mtextGlobals->showCaret;
    }

} /* _mtextCaretTimerNotify */




/* _mtextStartCaretBlink -- private utility to turn on the insertion point
 *			    blinking for a given minitext.
 *
 *  -> text -- the minitext to start blinking in
 */
void _mtextStartCaretBlink (mtext *text)
{
#if (vdebugDEBUG)
    if (text == NULL) {
	vexGenerate (vexGetArgNullClass(), vexERRNO, 0, vexMESSAGE,
		     "_mtextStartCaretBlink -- NULL text", vexNULL);
    }
#endif

    if (   (mtextGetSelectionLength(text) == 0)
	&& (mtextGetSelectType(text) != mtextNO_SELECTION)
	&& (vdialogItemIsEnabled(mtextGetItem(text)))) {

	if (_mtextGlobals->caretTimer == NULL) {
	    _mtextGlobals->caretTimer = vtimerCreate ();
	    vtimerSetNotify (_mtextGlobals->caretTimer, 
			     _mtextCaretTimerNotify);
	    vtimerSetPeriod (_mtextGlobals->caretTimer,
			     0, vtimestampSECOND / 2);
	    vtimerSetRecurrent (_mtextGlobals->caretTimer);
	}
	
	vtimerSetData (_mtextGlobals->caretTimer, text);

	_mtextGlobals->showCaret = FALSE;

	vtimerStart (_mtextGlobals->caretTimer);

	/* draw the caret immediately so the user doesn't have to wait
	 * to make sure the insertion point's in the correct place
	 */
	_mtextDrawCaretImmediate (text, mtextGetAnchor(text), mtextDRAW);
    }

} /* _mtextStartCaretBlink */




/* _mtextStopCaretBlink -- private utility that turns off the insertion point
 *			   blinking
 *
 *  -> text -- the minitext to stop blinking in.
 *
 * This only stops blinking if called with the same text pointer that
 * _mtextStartCaretBlink was called with.  This way, you can blindly call
 * _mtextStopCaretBlink on any mtext that's being manipulated without
 * disturbing the currently blinking one.  (handy for object destruction)
 */
void _mtextStopCaretBlink (mtext *text)
{
#if (vdebugDEBUG)
    if (text == NULL) {
	vexGenerate (vexGetArgNullClass(), vexERRNO, 0, vexMESSAGE,
		     "_mtextStopCaretBlink -- NULL text", vexNULL);
    }
#endif

    if (_mtextGlobals->caretTimer != NULL) {
	if (text == vtimerGetData(_mtextGlobals->caretTimer)) {

	    _mtextGlobals->showCaret = FALSE;
	    vtimerSetData (_mtextGlobals->caretTimer, NULL);
	    vtimerStop (_mtextGlobals->caretTimer);

	    /* fixes obiwan drawing at anchor-end-of-range */
	    _mtextDrawCaretImmediate (text, mtextGetAnchor(text), mtextREMOVE);
	}
    }

} /* _mtextStopCaretBlink */




/*
 * ----- HouseKeeping
 */


/* _mtextStartupClient -- do any per-client initialization necessary
 *
 * Right now this just involves populating the mtext class.
 */
static void _mtextStartupClient (void)
{
    mtextClass *defaultClass;

    defaultClass = (mtextClass*)vclassSpawn (vdialogGetDefaultItemClass(),
					     sizeof(mtextClass));
    vclassSetNameScribed (defaultClass, vcharScribeLiteral("mtext"));
    vclassSetObjectSize (defaultClass, sizeof(mtext));

    /* stache it away in our globals.  We need to refer to it when doing
     * vclassSendSupers
     */
    _mtextGlobals->defaultClass = defaultClass;



    /* I like to order my vclassSets by where the methods live in the
     * inheritance hierarchy (vobject first, the vdialogItem, followed
     * finally by brand new methods.
     */

    /* also, don't be daunted by the number of methods overridden.  In any
     * given dialog item, you'll only override a subset.  Several are
     * overridden just to give commentary or as a contrived example.
     */

    /*
     * Object Class Variables
     */

    vclassSet (defaultClass,	/* the command space the command mgr can use */
	       vobjectSPACE,
	       &_mtextDefaultSpace);

    vclassSet (defaultClass,	/* the key space the command manager can use */
	       vobjectKEY_MAP,
	       &_mtextDefaultKeyMap);
    
    vclassSet (defaultClass,	/* the name->ID_attribute mapping dictionary */
	       vobjectID_ATTRIBUTE_DICT,
	       &_mtextDefaultIDAttributeDict);


    /*
     * Object Methods
     */

    vclassSet (defaultClass,	/* initialize a static instance */
	       vinstanceINIT,
	       _mtextInit);
    
    vclassSet (defaultClass,	/* destroy an instance */
	       vinstanceDESTROY,
	       _mtextDestroy);
    
    vclassSet (defaultClass,	/* copy the object */
	       vobjectCOPY,
	       _mtextCopy);
    
    vclassSet (defaultClass,	/* initialize an object, then copy into it */
	       vobjectCOPY_INIT,
	       _mtextCopyInit);
    
    vclassSet (defaultClass,	/* load object from a resource template */
	       vobjectLOAD_INIT,
	       _mtextLoadInit);
    
    vclassSet (defaultClass,	/* store the object into a resource */
	       vobjectSTORE,
	       _mtextStore);

    vclassSet (defaultClass,	/* handle a command that's been issued */
	       vobjectISSUE_SELECTOR,
	       _mtextIssueSelector);

    vclassSet (defaultClass,	/* change an attribute's value symbolically */
	       vobjectSET_ID_ATTRIBUTE,
	       _mtextSetIDAttribute);

    vclassSet (defaultClass,	/* get an attribute symbolically */
	       vobjectGET_ID_ATTRIBUTE,
	       _mtextGetIDAttribute);

    vclassSet (defaultClass,	/* an attribute has changed in an instance */
	       vobjectCHANGED_ATTRIBUTE,
	       _mtextChangedAttribute);

    vclassSet (defaultClass,	/* an instance's parent changed an attribute */
	       vobjectCHANGED_PARENT_ATTRIBUTE,
	       _mtextChangedParentAttribute);


    /*
     * DialogItem class variable
     */

    switch (vlafAppear()) {

#ifdef vlafMOTIF
	case vlafMOTIF: {
	    vclassSet (defaultClass,	/* space around item to draw focus */
		       vdialogITEM_FOCUS_EXTRA,
		       3);
	    break;
	}
#endif

#ifdef vlafMAC
	case vlafMAC: {
	    vclassSet (defaultClass,	/* space around item to draw focus */
		       vdialogITEM_FOCUS_EXTRA,
		       3);
	    break;
	}
#endif

    }


    /*
     * DialogItem Methods
     */

    vclassSet (defaultClass,	/* draw the item on screen or on paper */
	       vdialogDRAW_ITEM,
	       _mtextDrawItem);

    vclassSet (defaultClass,	/* draw the "I'm foucused" indicator */
	       vdialogDRAW_ITEM_FOCUS,
	       _mtextDrawItemFocus);

    vclassSet (defaultClass,	/* handle button press */
	       vdialogHANDLE_ITEM_BUTTON_DOWN,
	       _mtextHandleItemButtonDown);

    vclassSet (defaultClass,	/* handle button release */
	       vdialogHANDLE_ITEM_BUTTON_UP,
	       _mtextHandleItemButtonUp);

    vclassSet (defaultClass,	/* handle mouse drag */
	       vdialogHANDLE_ITEM_DRAG,
	       _mtextHandleItemDrag);

    vclassSet (defaultClass,	/* handle mouse detail */
	       vdialogHANDLE_ITEM_DETAIL,
	       _mtextHandleItemDetail);

    vclassSet (defaultClass,	/* handle key press */
	       vdialogHANDLE_ITEM_KEY_DOWN,
	       _mtextHandleItemKeyDown);
    
    vclassSet (defaultClass,	/* handle item gaining focus */
	       vdialogFOCUS_ITEM,
	       _mtextFocusItem);

    vclassSet (defaultClass,	/* handle item losing focus */
	       vdialogUNFOCUS_ITEM,
	       _mtextUnfocusItem);

    vclassSet (defaultClass,	/* handle between-item spacing */
	       vdialogGET_ITEM_NATURAL_SEPARATION,
	       _mtextGetItemNaturalSeparation);

    vclassSet (defaultClass,	/* control item sizing */
	       vdialogCONSTRAIN_ITEM_SIZE,
	       _mtextConstrainItemSize);

    vclassSet (defaultClass,	/* specify most comfortable size */
	       vdialogGET_ITEM_NATURAL_SIZE,
	       _mtextGetItemNaturalSize);

    vclassSet (defaultClass,	/* specify smallest useful size */
	       vdialogGET_ITEM_MIN_SIZE,
	       _mtextGetItemMinSize);

    vclassSet (defaultClass,	/* item is becoming usable */
	       vdialogOPEN_ITEM,
	       _mtextOpenItem);

    vclassSet (defaultClass,	/* item's usability being turned off */
	       vdialogCLOSE_ITEM,
	       _mtextCloseItem);


    /*
     * mtext class variable
     */

    vclassSet (defaultClass,	/* cursor to show over item */
	       mtextCURSOR,
	       vlafGetCursor(vlafCURSOR_TEXT));

    /*
     * mtext methods
     */

    vclassSet (defaultClass,	/* draw the insertion point */
	       mtextDRAW_CARET,
	       _mtextDrawCaret);

    vclassSet (defaultClass,	/* draw a run of selected text */
	       mtextDRAW_SELECTED_RANGE,
	       _mtextDrawSelectedRange);

    vclassSet (defaultClass,	/* calculate the area the cursor will cover */
	       mtextCALC_CURSOR_RECT,
	       _mtextCalcCursorRect);

    vclassSet (defaultClass,	/* set insertion point / selection anchor */
	       mtextSET_ANCHOR,
	       _mtextSetAnchor);
    
    vclassSet (defaultClass,	/* set other end of selection */
	       mtextSET_SELECTION_END,
	       _mtextSetSelectionEnd);

    vclassSet (defaultClass,	/* set kind of selection model to use */
	       mtextSET_SELECT_TYPE,
	       _mtextSetSelectType);

    vclassSet (defaultClass,	/* handle keystrokes or insertions */
	       mtextINSERT_CHARACTER,
	       _mtextInsertCharacter);

    vclassSet (defaultClass,	/* delete range or character after anchor */
	       mtextDELETE_FORWARD,
	       _mtextDeleteForward);

    vclassSet (defaultClass,	/* delete range or character before anchor */
	       mtextDELETE_BACKWARD,
	       _mtextDeleteBackward);

    /*
     * debugging support
     */

#if (vdebugDEBUG)
    vclassSet (defaultClass,	/* make sure internal state is consistent */
	       mtextSANITY_CHECK,
	       _mtextSanityCheck);
#endif


} /* _mtextStartupClient */




/* _mtextShutdownClient -- clean up our memory mess.
 */
static void _mtextShutdownClient (void)
{
    if (_mtextGlobals->caretTimer != NULL) {
	vtimerDestroy (_mtextGlobals->caretTimer);
    }

} /* _mtextShutdownClient */


static void _mtextGlobalShutdown (void)
{

#if (vmemBALANCE)
    vcommandDestroySpace (&_mtextDefaultSpace);
    vdictDestroy (&_mtextDefaultKeyMap);
    vdictDestroy (&_mtextDefaultIDAttributeDict);
#endif

} /* _mtextGlobalShutdown */




/* _mtextStartup -- do any globalglobal setting up
 */
static void _mtextStartup (void)
{
    vdialogItemClass *super;

    /* init thedefault control ID attribute dictionary */

    super = vdialogGetDefaultItemClass ();


    vdictCopyInit (vclassGet(super, vobjectID_ATTRIBUTE_DICT), 
		   &_mtextDefaultIDAttributeDict);

    vdictSetHashSize (&_mtextDefaultIDAttributeDict, 
		      (size_t)mtextNEXT_ID_ATTRIBUTE*2);

    vobjectStoreDictIDAttributeTemplates (&_mtextDefaultIDAttributeDict, 
					  _mtextIDAttributeTemplates,
					  sizeof(_mtextIDAttributeTemplates)/
					  sizeof(vobjectIDAttributeTemplate));

    /* init the item command space */

    {
	vdict *dict;

	vcommandCopyInitSpace (vclassGet(super, vobjectSPACE), 
			       &_mtextDefaultSpace);

	dict = (vcommandCreateDictOfClassSelectorTemplates
		(vobjectGetCommandClass(), _mtextSelectorTemplates,
		 sizeof (_mtextSelectorTemplates) 
		 / sizeof (vcommandSelectorTemplate)));
	
	vcommandAddSpaceDictOwned (&_mtextDefaultSpace, vname_Command, dict);
    }


    /* make the keymap dictionary */
    /* ??? Should this should be moved into the per-class setup */

    vdictInit (&_mtextDefaultKeyMap, vkeyHashStroke);

    {
	const keyTemplate *scan, *stop;

	scan = _mtextKeyTemplates;
	stop = scan + (sizeof(_mtextKeyTemplates) / sizeof(keyTemplate));

	while (scan < stop) {
	    vdictStore (&_mtextDefaultKeyMap, vkeyInternStroke(scan->stroke),
			vnameInternGlobalLiteral(scan->commandName));
	    scan++;
	}
    }


    /* populate our vname predefinitions */
    {
	int i;

	for (i = 0; i < _mtextPredefCOUNT; i++) {
	    _mtextPredefs[i] = (vnameInternGlobalLiteral
				(_mtextPredefLiterals[i]));
	}
    }
    
} /* _mtextStartup */




/* _mtextSetup -- get the manager up and running.
 *
 * Sets up global-global information (registering our master pointer),
 * as well as per-client information (initializing the class and other
 * globals)
 */
static void _mtextSetup (void)
{
    if (_mtextMaster == NULL) {
	_mtextMaster = vclientRegisterModule ();
	_mtextStartup ();
#if (vmemBALANCE)
	vclientRegisterGlobalShutdown (_mtextGlobalShutdown);
#endif
    }

    if (*_mtextMaster == NULL) {
	vclientAllocateModule (_mtextMaster, sizeof(_mtextGlobalsStruct));
	_mtextStartupClient ();
	vclientRegisterShutdown (_mtextShutdownClient);

	/* clean off other globals here */
	_mtextGlobals->caretTimer = NULL;
    }

} /* _mtextSetup */




/* mtextGetDefaultClass -- return the class used by mtext instances.
 *
 * <- -- the mtext default class
 */
mtextClass *mtextGetDefaultClass (void)
{
    _mtextSetup ();
    return (_mtextGlobals->defaultClass);
} /* mtextGetDefaultClass */




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


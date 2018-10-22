/* $Id: grid.c,v 1.6 1995/11/03 20:43:57 scotth Exp $ */
/*
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
 * copyright notice in the form of "Copyright 1993 Visix Software Inc.,
 * 11440 Commerce Park Drive, Reston, VA  22091. All Rights Reserved" appears
 * in all copies, (ii) both the copyright notice and this permission notice
 * appear in supporting documentation and (iii) you are a valid licensee of
 * Galaxy Application Environment.
 */

/****************************************************************************
 * Executable Name: grid
 * Source Files:    grid.c
 * Resource Files:  grid.vr
 *
 * Managers Illustrated:
 *     List Manager
 *
 * Description Of Sample:
 *	This sample provides a subclass of listview that does
 *	synchronized-scrolling between two listviews, as well as the 
 *      drawing of grid lines between rows.
 *
 *	One listview is a content area that will be populated by the
 *	user.  The upper listview has column headings that can span 
 *	multiple columns underneath it.  Clicking in a column heading
 *	will select the appropriate column(s) in the main listview.
 *	Rearranging of rows is active.
 *
 *	The portions of the List Manager used are the vlistviewNOTIFY_SCROLL
 *	method, as well as modifying the cellContent drawing procedure.
 *
 *	Lots of support stuff is also shown.  Note that this program 
 * 	does not use commands, just simple callbacks.  Had this been
 *	a Real Application, commands would have been used.
 *
 *	The user populates the list by typing things into the 4 textfields,
 *	then clicking the "DoIt" button.  Hitting Return is equivalent
 *	to clicking DoIt.
 *
 * History:
 *	14-Jun-1993 -- Took ancient code and formatted/commented.
 *		       Tested with Galaxy 1.2 release.
 *
 ****************************************************************************/


/* resource tags used:
   GridDialog  -- the main dialog iteself, which contains:
       THING1, THING2, SPAM1, SPAM2 -- the 4 textitems.
       LISTVIEW -- the list/table (of subclass mlSyncList)
       LABELS -- a set of column labels (of subclass mlLabelSyncList)
       DO_IT_BUTTON -- take the info from the textfields and put stuff into the
                       list
       QUIT_BUTTON  -- quit the application
*/


/* set up debugging tag that labels this module and memory allocated by this
 * module.  To see a run-time trace of which functions in this module get
 * called, set the vdebugMODULE environment variable to "grid", and set
 * the vdebugLEVEL environment variable to "1000"
 */

#define vdebugTAG	"grid"

/* include the world */
#include <vgalaxy.h>


/*
 * ========== Useful macro
 */

/* this is a shorthand way for using tags in the code. */

#define TAG(s)	vnameInternGlobalLiteral((s))



/*
 * ========== Random #defines
 */

/* how many columns of stuff list has */
#define _gridNUM_COLUMNS 10

/* the width of each of the columns in the list */
static int _gridColumnWidths[] = { 70,  70,  70,  70, 100,
				   60, 120,  50,  70, 100 };



/* the header columns / table columns are related thusly:
 * |           |  |  |  |        |  (headers)
 * +--+--+--+--+--+--+--+--+--+--+
 * |  |  |  |  |  |  |  |  |  |  |  (table columns)
 */
/* how many columns of header information */
#define _gridNUM_HEADER_COLUMNS	5

/* the width of each of the header columns */
static int _gridHeaderColumnWidths[] = { 70 + 70 + 70 + 70, 100, 60, 120,
					  50 + 70 + 100 };

/* how many columns are owned by each header column */
static int _gridOwnedColumns[] = { 4, 1, 1, 1, 3 };

/* !!! should get this from the resource file */
static char *_gridHeaderTitles[] = { "Originals", "UPPER", "lower", 
				     "Num", "Other Stuff" };


/*
 * ========== Dialog Callback
 */

static void _gridHandleDialogNotify(vdialog *dialog, vevent *event)
{
    if (veventIsClose(event)) {
	veventStopProcessing();
    }
}


/*
 * ========== Dialog Item Callbacks
 */


/* _gridDoItButtonCallback -- notify function for the "Do It" button.
 *			      This takes the text from the 4 text fields,
 * 			      mangulates it, and places information into
 *			      the listview.
 *
 *  -> button	-- the do it button.
 *  -> event	-- the event that triggered the button.  We don't really
 *		   care _what_ triggered this notify, just the fact that
 *                 something triggered it.
 */
static void _gridDoItButtonCallback (vbutton *button, vevent *event)
{
    vstr	*string1, *string2, *string3, *string4;
    vtextitem	*thing1,  *thing2,  *spam1,   *spam2;
    vlistview	*listview;
    vlist	*list;
    vdialog	*dialog;
    int		 newRow;
    vstr	*scratchString;

    vdebugTrace ("_gridDoItButtonCallback\n");

    /* get the dialog the button belongs to */
    dialog = vdialogDetermineItemDialog (vbuttonGetItem (button));


    /* get ahold of the 4 textitems */
    thing1 = (vtextitem*) vdialogFindItem (dialog, TAG ("THING1"));
    thing2 = (vtextitem*) vdialogFindItem (dialog, TAG ("THING2"));
    spam1  = (vtextitem*) vdialogFindItem (dialog, TAG ("SPAM1"));
    spam2  = (vtextitem*) vdialogFindItem (dialog, TAG ("SPAM2"));

    /* turn their contents into strings */
    string1 = vtextitemGetTextAsString (thing1);
    string2 = vtextitemGetTextAsString (thing2);
    string3 = vtextitemGetTextAsString (spam1);
    string4 = vtextitemGetTextAsString (spam2);

    /* empty out the textitems for the next hunks of data to be entered */
    vtextitemSetTextScribed (thing1, vcharScribeLiteral (""));
    vtextitemSetTextScribed (thing2, vcharScribeLiteral (""));
    vtextitemSetTextScribed (spam1,  vcharScribeLiteral (""));
    vtextitemSetTextScribed (spam2,  vcharScribeLiteral (""));


    /* now do stuff with the list (table) */

    listview = (vlistview*) vdialogFindItem (dialog, TAG ("LISTVIEW"));
    list = vlistviewGetList (listview);

    /* determine the new row we're appending.  Since list indicies are zero-
     * based, the current row count is the same as the new row to put
     * information into. */
    newRow = vlistGetRowCount (list);

    /* here is where you'd calculate the table's values.  Right now, we're
     * putting the text field contents into the first 4 columns, then doing
     * string concatentations for the other 6.  If you change 
     * _gridNUM_COLUMNS, you'll need to adjust this here as well */
    vlistSetCellValue (list, newRow, 0, string1);
    vlistSetCellValue (list, newRow, 1, string2);
    vlistSetCellValue (list, newRow, 2, string3);
    vlistSetCellValue (list, newRow, 3, string4);

    /* create some additional strings */
    /* column 4 -> string 1 in all caps */
    scratchString = vstrCloneScribed (vcharScribeToUpperCase (string1));
    vlistSetCellValue (list, newRow, 4, scratchString);


    /* column 5 -> string 2 in all lower calse*/
    scratchString = vstrCloneScribed (vcharScribeToLowerCase (string2));
    vlistSetCellValue (list, newRow, 5, scratchString);


    /* column 6 -> a weirdly generated number */
    {
	double	number;
	number = cos (newRow * 2*3.14159 * 0.1);
	scratchString = vstrCloneScribed (vnumScribeFloat (number));
	vlistSetCellValue (list, newRow, 6, scratchString);
    }

    /* column 7, 8 -> weird words with the row number at the end */
    scratchString = vstrCloneScribed (vscribeScribeMulti 
				      (vcharScribeLiteral("bork"),
				       vnumScribeInt(newRow),
				       NULL));
    vlistSetCellValue (list, newRow, 7, scratchString);

    scratchString = vstrCloneScribed (vscribeScribeMulti 
				      (vcharScribeLiteral("hoover"),
				       vnumScribeInt(newRow),
				       NULL));
    vlistSetCellValue (list, newRow, 8, scratchString);


    /* column 9 -> identical to string 4 */
    scratchString = vstrCloneScribed (vcharScribe (string4));
    vlistSetCellValue (list, newRow, 9, scratchString);


    /* set the column widths the first time through. */
    if (newRow == 0) {
	int i;
	for (i = 0; i < _gridNUM_COLUMNS; i++) {
	    vlistviewSetColumnWidth (listview, i, _gridColumnWidths[i]);
	}
    }

    /* lastly, set the keyboard focs back to thing1 */
    vdialogSetFocus (dialog, vtextitemGetItem (thing1));

} /* _gridDoItButtonCallback */




/* _gridQuitButtonCallback -- notify function for the "Quit" button.
 *			      This just stops processing.  Any memory
 *			      we allocated will be cleaned up after the
 *			      call to veventProcess () returns.
 *
 *  -> button	-- the quit button.
 *  -> event	-- the event that triggered the button.  We don't really
 *		   care _what_ triggered this notify, just the fact that
 *                 something triggered it.
 */
static void _gridQuitButtonCallback (vbutton *button, vevent *event)
{
    vdebugTrace ("_gridQuitButtonCallback\n");

    veventStopProcessing ();

} /* _gridQuitButtonCallback */




/*
 * ========== List Manager subclass and customization
 */

/*
 * The column headings are actually another listview that is sync-scrolled
 * with the main table.  To do the sync scrolling, it's necessary to setup
 * a subclass with the name "mlSyncList" which does the scrolling.
 */


/* a rock to hide data under.  This has pointers to the companion listview,
 * as well as a protection variable to prevent scrolling live-lick.
 */
typedef struct _gridScrollRock {
    vlistview	*companion;
    int		 isScrolling;
    int		 lastSelectMode; /* for the label selection stuff */
} _gridScrollRock;



/* _gridListviewNotifyScroll -- This is called whenever listview gets 
 *				scrolled.  We need to scroll our companion
 *				list as well.
 *
 *  -> listview		-- the listview that scrolled
 *  -> horzDistance	-- horizontal pixel delta
 *  -> vertDistance	-- vertical pixel delta
 */
static void _gridListviewNotifyScroll (vlistview *listview,
				       int horzDistance, int vertDistance)
{
    _gridScrollRock	*granite, *otherGranite;

    vdebugTrace ("_gridListviewNotifyScroll\n");

    granite = (_gridScrollRock *) vlistviewGetData (listview);
    otherGranite = (_gridScrollRock *)vlistviewGetData (granite->companion);

    if (!granite->isScrolling && !otherGranite->isScrolling) {
	granite->isScrolling = TRUE;
	vlistviewScrollRelative (granite->companion, horzDistance,
				 vertDistance);
	granite->isScrolling = FALSE;
    }
} /* _gridListviewNotifyScroll */



static vlistviewClass *mlSyncList = NULL;



/* _gridListviewGetItemNaturalSeparation -- return the amount of space a
 *      			             natural strut originating from
 *				             this item should be.
 *
 *  -> listview    -- the listview to determine the separation for
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
 *
 * In this case, if we're the top listview, we separate ourselves by the
 * natural width of the scroll bar from our partner
 */
static int _gridListviewGetItemNaturalSeparation (vlistview *listview,
						  vdialogItem *to,
						  unsigned int wickedWitch)
{
    int ret = 0, width = 0, dummy;

    if (   ( to != NULL) 
	&&  !vlistviewHasVertBar(listview)
	&& ( vclassIsKindOf (vdialogGetItemClass(to), mlSyncList))
	&& ( vlistviewHasVertBar((vlistview*)to))) {

	vcontrol *bar = vlistviewGetVertScrollbar ((vlistview*)to);
	    
	if (vlafLeftScrollBar()) {
	    if (wickedWitch == vspringLEFT_TO_LEFT_SEPARATION) {
		vdialogGetItemNaturalSize (vcontrolGetItem(bar),
					   &width, &dummy);
	    }
	} else {
	    
	    if (wickedWitch == vspringRIGHT_TO_RIGHT_SEPARATION) {
		vdialogGetItemNaturalSize (vcontrolGetItem(bar),
					   &width, &dummy);
	    }
	}
	ret += width + vlistviewGetScrollBarMargin ((vlistview*)to);
    }

    return (ret);
	
} /* _gridListviewGetItemNaturalSeparation */






/* _gridSetupSyncListSubclass -- subclass listview to have the scrolling
 *			         notify procedures scroll a companion
 *				 list.
 *
 * Side effect -- creates a subclass and registers it with the class
 * manager
 */
static void _gridSetupSyncListSubclass (void)
{
    vdebugTrace ("_gridSetupSyncListSubclass\n");

    if (mlSyncList == NULL) {
	/* make a subclass and name it. */
	mlSyncList = vclassReproduce (vlistviewGetDefaultClass());
	vclassSetNameScribed (mlSyncList, vcharScribeLiteral ("mlSyncList"));

	/* change the necessary method. */
	vclassSet (mlSyncList, vlistviewNOTIFY_SCROLL,
		   _gridListviewNotifyScroll);

	/* to get the dialog layout looking good, we need to inset the
	 * the top listview's border to account for the scroll bar of the
	 * bottom listview */
	vclassSet (mlSyncList, vdialogGET_ITEM_NATURAL_SEPARATION,
		   _gridListviewGetItemNaturalSeparation);
	
    }
} /* _gridSetupSyncListSubclass */




/* _gridShutdownSyncListSubclass -- destroy the subclass created in
 *				    _gridSetupSyncListSubclass.
 *
 * Side effect -- destroys the sync list subclass.
 */
static void _gridShutdownSyncListSubclass (void)
{
    vdebugTrace ("_gridShutdownSyncListSubclass\n");

    if (mlSyncList != NULL) {
	vclassDestroy (mlSyncList);
    }

} /* _gridShutdownSyncListSubclass */



/* _gridSelectBelow -- select the columns in the listview that lie below
 * 		       a particular heading cell.
 *
 *  -> list	 -- the list to select in.
 *  -> selection -- the selection to select in.
 *  -> column    -- the column in the header list that is being selected.
 *
 * This is the workhorse of the "click in the header and select the
 * column(s) underneath it" stuff.  Right now the values are hard-coded 
 * in here, but they could be table-driven.
 */
static void _gridSelectBelow (vlist *list, vlistSelection *selection,
			      int column)
{
    vdebugTrace ("_gridSelectBelow\n");

    switch (column) {
	case 0: {
	    vlistSelectColumn (list, selection, 0);
	    vlistSelectColumn (list, selection, 1);
	    vlistSelectColumn (list, selection, 2);
	    vlistSelectColumn (list, selection, 3);
	    break;
	}
	case 1: {
	    vlistSelectColumn (list, selection, 4);
	    break;
	}
	case 2: {
	    vlistSelectColumn (list, selection, 5);
	    break;
	}
	case 3: {
	    vlistSelectColumn (list, selection, 6);
	    break;
	}
	case 4: {
	    vlistSelectColumn (list, selection, 7);
	    vlistSelectColumn (list, selection, 8);
	    vlistSelectColumn (list, selection, 9);
	    break;
	}
	default: {
	    vdebugWarn ("oops! Bad _gridSelectBelow column\n");
	}
    }
} /* _gridSelectBelow */




/* _gridLabelSelectNotify -- notify procedure for the label listview.
 *			     this selects all of the columns underneath
 *			     the selected cell.
 *
 *  -> listview	-- the listview whose selection is changing
 *  -> state	-- one of vlistviewSELECTION_WILL_CHANGE,
 *		   vlistviewSELECTION_IS_CHANGING, or
 *		   vlistviewSELECTION_HAS_CHANGED.
 */
static void _gridLabelSelectNotify (vlistview *listview, int state)
{
    _gridScrollRock	*mica;
    vlist		*thisList;
    vlist		*otherList;
    vlistSelection	*otherSelection;
    int			 row, column;

    vdebugTrace ("_gridLabelSelectNotify\n");

    thisList = vlistviewGetList (listview);

    mica = (_gridScrollRock *)vlistviewGetData (listview);
    otherList = vlistviewGetList (mica->companion);
    otherSelection = vlistviewGetSelection (mica->companion);

    switch (state) {
	case vlistviewSELECTION_WILL_CHANGE: {
	    vlistUnselectAll (otherList, otherSelection);
	    vlistGetSelectedCell (thisList,
				  vlistviewGetVolatileSelection (listview),
				  &row, &column);
	    if ((row != vlistNO_CELLS_SELECTED)
		&& (column != vlistNO_CELLS_SELECTED)) {
		_gridSelectBelow (otherList, otherSelection, column);
	    }
	    break;
	}
	case vlistviewSELECTION_IS_CHANGING: {
	    vlistUnselectAll (otherList, otherSelection);
	    vlistGetSelectedCell (thisList,
				  vlistviewGetVolatileSelection (listview),
				  &row, &column);
	    if ((row != vlistNO_CELLS_SELECTED)
		&& (column != vlistNO_CELLS_SELECTED)) {
		_gridSelectBelow (otherList, otherSelection, column);
	    }
	    break;
	}
	case vlistviewSELECTION_HAS_CHANGED: {
	    /* this is where you'd notify your application that the user
	     * committed to a new selection */
	    break;
	}
    }
    mica->lastSelectMode = state;
} /* _gridLabelSelectNotify */



/* these are color lookup tables to feed to vdialogDetermineItemColors.
 * The user sets the background and foreground colors in vre, and
 * the dialog manager figures out what the shadow and deboss colors
 * should be.
 */
enum {
    colorFOREGROUND = 0,
    colorBACKGROUND,
    colorSHADOW_TOP,
    colorSHADOW_BOTTOM,
    colorFOCUS,
    colorBACKGROUND_DEBOSS,
    colorNUM_COLORS /* must be last */
};

static int	colorIDs[colorNUM_COLORS] = {
    vdrawCOLOR_FOREGROUND, 
    vdrawCOLOR_BACKGROUND, 
    vdrawCOLOR_SHADOW_TOP, 
    vdrawCOLOR_SHADOW_BOTTOM,
    vdrawCOLOR_FOCUS,
    vdrawCOLOR_BACKGROUND_DEBOSS
};




/* _gridLabelCellDrawProc -- draw the cells for the label listview
 *			     this draws them with a rectangular embossed
 *			     outline.  Selected ones are drawn in a
 *			     pseudo-openlookish pushed in thing.
 *
 *  -> listview	   -- the listview being drawn
 *  -> row, column -- the cell being drawn
 *  -> selected    -- FALSE if the cell is unseleced, selected otherwise.
 *  -> rect	   -- the rectangle to draw in
 */
static void _gridLabelCellDrawProc (vlistview *listview, int row, int column,
				    int selected, vrect *rect)
{
    vcolor	*colors [colorNUM_COLORS];
    vchar	*string;
    vrect	 cellRect = *rect;

    vdebugTrace ("_gridlabelCellDrawProc\n");

    vdrawGSave (); {
	/* since we're doing work of drawing the background, we need
	 * to expand the cell to cover the whole area, including the
	 * keyboard traversal cursor area.
	 */
	vrectInset (&cellRect,
		    -vclassGet(vlistviewGetClass(listview),
			       vlistviewSELECTION_INSET),
		    -vclassGet(vlistviewGetClass(listview),
			       vlistviewSELECTION_INSET),
		    &cellRect);

	vdialogDetermineItemColors (vlistviewGetItem (listview),
				    colorIDs, colorNUM_COLORS, colors);
	
	if (selected) {
	    vdrawRectsHiliteFillInside (&cellRect, 1, 
					colors[colorBACKGROUND_DEBOSS],
					colors[colorSHADOW_BOTTOM],
					colors[colorSHADOW_TOP]);
	} else {
	    vdrawRectsHiliteFillInside (&cellRect, 1, NULL,
					colors[colorSHADOW_TOP],
					colors[colorSHADOW_BOTTOM]);
	}
	
	string = (vchar*) vlistGetCellValue (vlistviewGetList(listview),
					     row, column);
	
	if (string != NULL) {
	    vdrawSetColor (colors[colorFOREGROUND]);
	    vdrawRectShowCenter (string, rect);
	}
    } vdrawGRestore ();

} /* _gridLabelCellDrawProc */




/* _gridLabelCellDrawProc -- draw the cells for the table listview
 *			     this draws them with a beveled line underneath.
 *
 *  -> listview	   -- the listview being drawn
 *  -> row, column -- the cell being drawn
 *  -> selected    -- FALSE if the cell is unseleced, selected otherwise.
 *  -> rect	   -- the rectangle to draw in
 */
static void _gridListviewCellDrawProc (vlistview *listview, 
				       int row, int column, int selected,
				       vrect *rect)
{
    vcolor	*prevColor;
    vcolor	*colors[colorNUM_COLORS];
    double	 lineWidth;
    vchar	*string;
    int		 offset;

    vdebugTrace ("_gridListviewCellDrawProc\n");

    /* draw the string first, then the underline */

    string = (vchar*)vlistGetCellValue (vlistviewGetList(listview), 
					row, column);
    if (string!= NULL) {
	rect->x += 5;	/* indent */
	vdrawRectShowCenterY (string, rect);
	rect->x -= 5;   /* outdent */
    }

    /* set up our drawing state */
    vdialogDetermineItemColors (vlistviewGetItem (listview),
				colorIDs, colorNUM_COLORS, colors);

    prevColor = vdrawGetColor ();
    lineWidth = vdrawFGetLineWidth ();

    vdrawFSetLineWidth (lineWidth * 0.50);

    /* the cell we're passed has been inset to compensate for selection
     * highlighting under certain look and feels.  Since we want the
     * beveled line to span across the list, add in this fudge factor
     * to the rectangle we're passed/ */

    offset = vclassGet (vlistviewGetClass(listview),
			vlistviewSELECTION_INSET);

    vdrawSetColor (colors[colorSHADOW_TOP]);
    vdrawMoveTo (rect->x - offset, rect->y+1);
    vdrawLineTo (rect->x + rect->w + offset*2, rect->y+1);
    vdrawStroke();

    vdrawSetColor (colors[colorSHADOW_BOTTOM]);
    vdrawMoveTo (rect->x - offset, rect->y+2);
    vdrawLineTo (rect->x + rect->w + offset*2, rect->y+2);
    vdrawStroke();

    vdrawSetColor (prevColor);
    vdrawFSetLineWidth (lineWidth);
    
} /* _gridListviewCellDrawProc */


/*
 * ========== Setup
 */


/* _gridSetupLabels -- setup the labels listview.
 *
 *  -> listview	-- the listview to setup.
 *
 * Assumptions -- listview doesn't have a list attached and needs one.
 */
static void _gridSetupLabels (vlistview *listview)
{
    vlist	*list;
    int		 i;
    int		 selectionSpacing;

    vdebugTrace ("_gridSetupLabels\n");

    /* make a new list and attach it to the listview */
    list = vlistCreate ();
    vlistviewSetList (listview, list);

    /* put the info into it. */
    vlistSetRowCount (list, 1);
    vlistSetColumnCount (list, _gridNUM_HEADER_COLUMNS);

    /* change the selection mechanism to one-only.
     * This is just for demonstration purposes. */
    vlistSetSelectMethod (list, vlistviewGetSelection (listview),
			  vlistONE_ONLY_SELECTION);

    /* determine the spacing the list manager will put between columns to
     * compensate for selection highlighting and motif focus cursor */
    selectionSpacing = vclassGet (vlistviewGetClass (listview),
				  vlistviewSELECTION_INSET)*2;

    /* set the cell values and column widths */
    for (i = 0; i < _gridNUM_HEADER_COLUMNS; i++) {
	vlistSetCellValue (list, 0, i,
			   vstrCloneScribed(vcharScribeLiteral
					    (_gridHeaderTitles[i])));
	vlistviewSetColumnWidth (listview, i, 
				 _gridHeaderColumnWidths[i]
				 + selectionSpacing
				 * (_gridOwnedColumns[i] -1));
	/* i.e. the width is the width of all of the columns + 
	 * a selectionSpacing for each inter-column gap of the
	 * the owned columns */
    }

    /* and setup a custom cell drawing procedure */
    vlistviewSetCellContentProc (listview, _gridLabelCellDrawProc);

    /* and setup a selection notify procedure.  This will select
     * the columns underneath the heading */
    vlistviewSetSelectNotify (listview, _gridLabelSelectNotify);

} /* _gridSetupLabels */




/* _gridSetupDialog -- attach the callbacks to the different dialog
 * 		       items in the dialog.  Also attach a list to the
 *		       dialog's listview.
 *
 *  -> dialog	-- the dialog to setup
 */
static void _gridSetupDialog (vdialog *dialog)
{
    vbutton	    *doit, *quit;
    vlistview	    *listview;
    vlistview	    *labels;
    vlist	    *list;
    vtextitem	    *textitem;
    _gridScrollRock *listrock, *labelrock;

    vdebugTrace ("_gridSetupDialog\n");

    /* set up the dialog to quit the app when closed */
    vdialogSetNotify(dialog, _gridHandleDialogNotify);

    /* set up the DoIt button */
    doit = (vbutton*) vdialogFindItem (dialog, TAG ("DO_IT_BUTTON"));
    vbuttonSetNotify (doit, _gridDoItButtonCallback);

    /* ditto the Quit button */
    quit = (vbutton*) vdialogFindItem (dialog, TAG ("QUIT_BUTTON"));
    vbuttonSetNotify (quit, _gridQuitButtonCallback);


    /* now get the listview. */
    listview = (vlistview*) vdialogFindItem (dialog, TAG ("LISTVIEW"));

    /* lists (like the other sophisticated galaxy dialog items) use a 
     * split data - view model.  We currently have a view with no data.
     * create a vlist (which has the list data) and associated it with the
     * view.   */
    list = vlistCreate ();
    vlistviewSetList (listview, list);

    /* set up the column count and column widths.  The list is still
     * considered "empty" because there are no rows yet. */
    vlistSetColumnCount (list, _gridNUM_COLUMNS);

    /* also turn on the listview's scrollbars */
    vlistviewSetHorzBar (listview, TRUE);
    vlistviewSetVertBar (listview, TRUE);

    /* Set its drawProc and row rearranging */
    vlistviewSetCellContentProc (listview, _gridListviewCellDrawProc);
    vlistviewSetRowRearrange (listview, TRUE);

    /* Now get the labels */
    labels = (vlistview*) vdialogFindItem (dialog, TAG ("LABELS"));
    _gridSetupLabels (labels);
    
    /* make the rocks and stash the pointers to each other in there. */
    listrock = (_gridScrollRock*) vmemAlloc (sizeof(_gridScrollRock));
    labelrock = (_gridScrollRock*) vmemAlloc (sizeof(_gridScrollRock));
    listrock->companion = labels;
    listrock->isScrolling = FALSE;

    labelrock->companion = listview;
    labelrock->isScrolling = FALSE;

    /* and hide the rocks under the listviews' data pointers */
    vlistviewSetData (listview, listrock);
    vlistviewSetData (labels, labelrock);


    /* we want the first text item to have keyboard focus when we start up
     * under motif or windows. */
    vdialogSetDefFocus (dialog, vdialogFindItem (dialog, TAG ("THING1")));

    /* and we want the "DoIt" button to be the default confirm item */
    vdialogSetConfirm (dialog, vbuttonGetItem (doit));

    /* lastly, restrict each of the 4 textitems to be one-line-only */

    textitem = (vtextitem*) vdialogFindItem (dialog, TAG("THING1"));
    vtextitemSetOneLine (textitem, TRUE);

    textitem = (vtextitem*) vdialogFindItem (dialog, TAG("THING2"));
    vtextitemSetOneLine (textitem, TRUE);

    textitem = (vtextitem*) vdialogFindItem (dialog, TAG("SPAM1"));
    vtextitemSetOneLine (textitem, TRUE);

    textitem = (vtextitem*) vdialogFindItem (dialog, TAG("SPAM2"));
    vtextitemSetOneLine (textitem, TRUE);
    
} /* _gridSetupDialog */




/* _gridShutdownDialog -- free any memory allocated on this dialog's
 *			  behalf.  The main responsibility for this
 *			  function is to clean up any memory allocated
 *			  that was put into the listview's list.
 *
 *  -> dialog	-- the dialog to shut down.
 *
 * Note that the dialog is _not_ destroyed here, but it can be rendered
 * unusable.
 */
static void _gridShutdownDialog (vdialog *dialog)
{
    vlistview	   *listview;
    vlist	   *list;
    int		    row, column;
    vlistIterator   iterator;
    vstr	   *string;
    vlistview	   *labels;

    vdebugTrace ("_gridShutdownDialog\n");

    /* first, close the dialog if it's open */
    if (vdialogIsOpen (dialog)) {
	vdialogClose (dialog);
    }

    /* now we just need to clean up the strings we put into the list */
    
    /* get the list view from the dialog, and the list from the view. */
    listview = (vlistview*) vdialogFindItem (dialog, TAG("LISTVIEW"));
    list = vlistviewGetList (listview);

    /* we use an iterator to go over the entire list.  You can just as
     * easily use nested loops to go over all rows and columns.  */
    vlistInitIterator (&iterator, list);

    /* increment the iterator to point to another cell */
    while (vlistNextIterator (&iterator)) {

	/* get the cell it's pointing to. */
	row = vlistGetIteratorRow (&iterator);
	column = vlistGetIteratorColumn (&iterator);

	/* get the value of the cell */
	string = (vstr*) vlistGetCellValue (list, row, column);

	/* and destroy the string.  Check for NULLness incase we're iterating
	 * over an empty cell. */
	if (string != NULL) {
	    vstrDestroy (string);
	}
    }

    /* clean up after the iterator */
    vlistDestroyIterator (&iterator);


    /* finally, destroy the listview's list */
    vlistDestroy (list);

    /* now destroy the listview's rock */
    vmemFree ((void*)vlistviewGetData (listview));
    

    /* now do the same thing for the label listview */
    labels = (vlistview*) vdialogFindItem (dialog, TAG ("LABELS"));
    list = vlistviewGetList (labels);

    vlistInitIterator (&iterator, list);

    while (vlistNextIterator (&iterator)) {

	row = vlistGetIteratorRow (&iterator);
	column = vlistGetIteratorColumn (&iterator);

	string = (vstr*) vlistGetCellValue (list, row, column);

	if (string != NULL) {
	    vstrDestroy (string);
	}
    }

    vlistDestroyIterator (&iterator);

    vlistDestroy (list);

    vmemFree ((void*)vlistviewGetData (labels));

} /* _gridShutdownDialog */



/*
 * ========== Random Housekeeping
 */



int main (int argc, char *argv[])
{
    vresource	appRes;    /* application resources */
    vresource	dialogRes; /* dialog resource */
    vdialog    *dialog;	   /* dialog instance */

    vstartup (argc, argv);

    /* Setup the list subclass */
    _gridSetupSyncListSubclass ();

    /* find our application's resource dictionary */
    appRes = vapplicationGetResources (vapplicationGetCurrent());

    /* get a reference to the application's dialog */
    dialogRes = vresourceGet (appRes, TAG("GridDialog"));

    /* make an instance of the dialog */
    dialog = vdialogLoad (dialogRes);

    /* now set it up */
    _gridSetupDialog (dialog);

    /* and open it */
    vdialogOpen (dialog);

    /* and let the user play with it. */
    veventProcess ();

    /* now clean up our mess */
    _gridShutdownDialog (dialog);
    vdialogDestroy (dialog);

    /* destroy the list subclass */
    _gridShutdownSyncListSubclass ();

    /* and exit happily */
    exit (EXIT_SUCCESS);
    
    /* oops! exit returned. Something bad must have happened. */
    return (EXIT_FAILURE);

} /* main */
	      


/*
 * ========== Other random nonsense
 */


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

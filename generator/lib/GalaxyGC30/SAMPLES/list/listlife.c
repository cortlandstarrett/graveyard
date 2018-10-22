/* $Id: listlife.c,v 1.6 1993/11/27 23:24:17 chad Exp $
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

/* listlife.c -- C implementation for a list-based life window.
 *
 * vlist is a collection of distinct Galaxy list manager applications,
 * ranging from a simple list to stocks and bondage to life.
 *
 * The various parts of this demo are:
 * vlist.c     -- Chief overlord and starter-up of the other demos.
 * listlife.c  -- Conway's game o' life.   (this file)
 * listapi.c   -- Fiddle with the API and see what does what.
 * listcell.c     -- Do in-cell editing.
 *   xincell.h    -- interface to in-cell editing subclass.
 *   incell.c     -- implementation of in-cell editing subclass.
 */

/* this file demonstrates these concepts:
 *     a brute-force implementation of Conway's game of life
 *     use of vtimers
 *     custom cell drawing procedure
 *     use of vlistview select notify
 *     simple subclassing
 */

#ifndef  vportINCLUDED
#include <vport.h>		/* for v*HEADER */
#endif

#ifndef  vdialogINCLUDED
#include vdialogHEADER
#endif

#ifndef  vlistINCLUDED
#include vlistHEADER
#endif

#ifndef  vlistviewINCLUDED
#include vlistviewHEADER
#endif

#ifndef  vclassINCLUDED
#include vclassHEADER
#endif

#ifndef  vcommandINCLUDED
#include vcommandHEADER
#endif

#ifndef  vdictINCLUDED
#include vdictHEADER
#endif

#ifndef  vpoolINCLUDED
#include vpoolHEADER
#endif

#ifndef  vtimerINCLUDED
#include vtimerHEADER
#endif

#include "listdemo.h"

/* convenience macro */
#define TAG(s)	vnameInternGlobalLiteral ((s))


/* ------------------ module global variables ------------------- */


/* ------------- Life related global variables and constants ---------- */

#define lifeNeighborMask	0x0000007
#define lifeLiveMask		0x0000008

#define lifeCELL_SIZE	4	/* should get from resources??? */
#define lifeNUM_ACROSS	90
#define lifeNUM_DOWN	90


typedef int petriDish[lifeNUM_DOWN+2][lifeNUM_ACROSS+2];
/* the +2 is a border buffer */


/* a place to hide data under for implementing multiple windows.
 * listapi.c has a fuller description. */
typedef struct lifeRock {
    vtimer *timer;
    vlistview *listview;
    int areRemoving;
    petriDish *petri1, *petri2; /* alloc'd dishen */
    petriDish *currentPetri, *otherPetri, *drawPetri; /* pointers to one
						       * of the above */
} lifeRock;

/* the source of lifeRocks */
static vpool *primordialSoup = NULL;

/* keeper-trakcer of our windows */
static windowset *lifeWindowset = NULL;


/* ---------------- Life related stuff --------------- */


/* _lifeDecNeighbors -- decrement the count of the neighbors surrounding
 *			the cell.  This is done upon a cell's death.
 *
 *  -> petri	   -- the petridish holding the dying cell.
 *  -> row, column -- the bacteria meeting its maker
 */
static void _lifeDecNeighbors(petriDish *petri, int row, int column)
{
    int thingie;
    row++; column++;
    (*petri)[row-1][column-1]--;
    (*petri)[row-1][column  ]--;
    (*petri)[row-1][column+1]--;
    (*petri)[row  ][column-1]--;
    (*petri)[row  ][column+1]--;
    (*petri)[row+1][column-1]--;
    (*petri)[row+1][column  ]--;
    (*petri)[row+1][column+1]--;
    
    if ((row == 1) || (row == lifeNUM_DOWN)) {
	thingie = ((row == 1) ? 0 : lifeNUM_DOWN + 1);
	(*petri)[thingie][column-1] = 0;
	(*petri)[thingie][column  ] = 0;
	(*petri)[thingie][column+1] = 0;
    }
    if ((column == 1) || (column == lifeNUM_ACROSS)) {
	thingie = ((column == 1) ? 0 : lifeNUM_ACROSS + 1);
	(*petri)[row-1][thingie] = 0;
	(*petri)[row  ][thingie] = 0;
	(*petri)[row+1][thingie] = 0;
    }
} /* _lifeDecNeighbors */




/* _lifeIncNeighbors -- Increment the count of the cells surrounding the
 *			given cell -This is done upon a cell's birth.
 *
 *  -> petri	   -- the petridish holding the newly born cell.
 *  -> row, column -- the newly created^H^H^H^H^H^H^H evolved cell. :)
 */
#if ORIGINAL_CODE
static void _lifeIncNeighbors(petriDish *petri, int row, int column) 
{
    int thingie;
    row++; column++;
    (*petri)[row-1][column-1]++;
    (*petri)[row-1][column  ]++;
    (*petri)[row-1][column+1]++;
    (*petri)[row  ][column-1]++;
    (*petri)[row  ][column+1]++;
    (*petri)[row+1][column-1]++;
    (*petri)[row+1][column  ]++;
    (*petri)[row+1][column+1]++;

    if ((row == 1) || (row == lifeNUM_DOWN)) {
	thingie = ((row == 1) ? 0 : lifeNUM_DOWN + 1);
	(*petri)[thingie][column-1] = 0;
	(*petri)[thingie][column  ] = 0;
	(*petri)[thingie][column+1] = 0;
    }
    if ((column == 1) || (column == lifeNUM_ACROSS)) {
	thingie = ((column == 1) ? 0 : lifeNUM_ACROSS + 1);
	(*petri)[row-1][thingie] = 0;
	(*petri)[row  ][thingie] = 0;
	(*petri)[row+1][thingie] = 0;
    }
} /* _lifeIncNeighbors */
#else /* inline me baby */
#define _lifeIncNeighbors(petri,row,column) \
{  \
   int thingie; \
   int nurow = row+1; \
   int nucolumn = column+1; \
   (*petri)[nurow-1][nucolumn-1]++; \
   (*petri)[nurow-1][nucolumn  ]++; \
   (*petri)[nurow-1][nucolumn+1]++; \
   (*petri)[nurow  ][nucolumn-1]++; \
   (*petri)[nurow  ][nucolumn+1]++; \
   (*petri)[nurow+1][nucolumn-1]++; \
   (*petri)[nurow+1][nucolumn  ]++; \
   (*petri)[nurow+1][nucolumn+1]++; \
   if ((nurow == 1) || (nurow == lifeNUM_DOWN)) { \
       thingie = ((nurow == 1) ? 0 : lifeNUM_DOWN + 1);  \
       (*petri)[thingie][nucolumn-1] = 0; \
       (*petri)[thingie][nucolumn  ] = 0; \
       (*petri)[thingie][nucolumn+1] = 0; \
   } \
   if ((nucolumn == 1) || (nucolumn == lifeNUM_ACROSS)) { \
       thingie = ((nucolumn == 1) ? 0 : lifeNUM_ACROSS + 1); \
       (*petri)[nurow-1][thingie] = 0; \
       (*petri)[nurow  ][thingie] = 0; \
       (*petri)[nurow+1][thingie] = 0; \
   } \
}
#endif




/* _lifeIsAlive -- does a given cell hold a living, breathing bacterium?
 *
 *  -> petri	   -- the petridish holding the colony in question.
 *  -> row, column -- the bacterium house in question.
 * <-		   -- 0 if dead, nonzero if not.
 */
#if ORIGINAL_CODE
static int _lifeIsAlive (petriDish *petri, int row, int column)
{
    row++; column++;
    return ( (*petri)[row][column] & lifeLiveMask );
} /* _lifeIsAlive */
#else
#define _lifeIsAlive(p,r,c) ((*(p))[(r)+1][(c)+1] & lifeLiveMask)
#endif




/* _lifeCountNeighbors -- how many cells neighbor a given cell?
 *
 *  -> petri	    -- the petridish representing the neighborhood.
 *  -> row, column  -- can you say "neighbors" boys and girls?
 * <-		    -- I knew you could.
 */
#if ORIGINAL_CODE
static int _lifeCountNeighbors (petriDish *petri, int row, int column)
{
    row++; column++;
    return ( (*petri)[row][column] & ~lifeLiveMask );
} /* _lifeCountNeighbors */
#else
#define _lifeCountNeighbors(p,r,c) ((*(p))[(r)+1][(c)+1] & ~lifeLiveMask)
#endif




/* _lifeConceive -- Let There Be Life!!
 *
 *  -> petri	   -- the home of the spawn.
 *  -> row, column -- where to store it.
 */
static void _lifeConceive (petriDish *petri, int row, int column) 
{
    if (!_lifeIsAlive(petri, row, column)) {
	int orig = (*petri)[row+1][column+1];
	_lifeIncNeighbors (petri, row, column);
	(*petri)[row+1][column+1] = orig | lifeLiveMask;
    }
} /* _lifeConceive */




/* _lifeAbort -- Is it murder, or just disinfecting?
 *
 *  -> petri	   -- the home of the bacterium.
 *  -> row, column -- which one to nuke.
 */
static void _lifeAbort (petriDish *petri, int row, int column)
{
    if (_lifeIsAlive(petri, row, column)) {
	int orig = (*petri)[row+1][column+1];
	_lifeDecNeighbors (petri, row, column);
	(*petri)[row+1][column+1] = orig & ~lifeLiveMask;
    }
} /* _lifeAbort */




/* the core thingie.  Use the straightForwardBruteForce algorithm for now */
/* _lifeRunner -- the main core thingie.  This uses the really brain-damaged
 *			brute-force algorithm.  Given more time, I should
 *			incorporate the spiffy algorithms from Micro
 *			Cornucopia (may it rest in peace) or from xlife.
 *
 *  -> timer	-- the timer that triggered this function.
 */
static void _lifeRunner (vtimer *timer)
{
    register int row, column, neighbors, rowStop, columnStop;
    vlist	*list;
    lifeRock	*granite;

    granite = (lifeRock*)vtimerGetData (timer);
    list = vlistviewGetList (granite->listview);

    granite->drawPetri = granite->otherPetri;

    rowStop = vlistGetRowCount (list) - 1;
    columnStop = vlistGetColumnCount (list) - 1;
    
    /* clean off other petri */
    (void)vmemSet (granite->otherPetri, 0, sizeof(petriDish));

    for (row = 0; row <= rowStop; row++) {
	for (column = 0; column <= columnStop; column++) {
	    neighbors = _lifeCountNeighbors (granite->currentPetri, 
					     row, column);
	    if (_lifeIsAlive (granite->currentPetri, row, column)) {
		if ((neighbors != 2) && (neighbors != 3)) {
		    _lifeAbort (granite->otherPetri, row, column);
		    vlistviewDrawCell (granite->listview, row, column);
		} else {
		    _lifeConceive (granite->otherPetri, row, column);
		}
	    } else {
		if (neighbors == 3) {
		    _lifeConceive (granite->otherPetri, row, column);
		    vlistviewDrawCell (granite->listview, row, column);
		} else {
/*		    _lifeAbort (granite->otherPetri, row, column); */
		}
	    }
	}
    }
    {
	petriDish *akk = granite->currentPetri;
	granite->currentPetri = granite->otherPetri;
	granite->otherPetri = akk;
	granite->drawPetri = granite->currentPetri;
    }

} /* _lifeRunner */




/* ---------------- List related stuff ------------- */


/* _lifeCellBackgroundProc -- overrides the default listview cell background
 *			drawing method so that nothing gets drawn for the
 *			background.
 *
 *  -> listview	   -- the listview to draw the cell for.
 *  -> row, column -- the cell to draw.
 *  -> selection   -- izzit selected?
 *  -> rect	   -- screen region to draw into.
 */
static void _lifeCellBackgroundProc (vlistview *listview, int row, int column,
				     int selected, vrect *rect)
{
    /* draw nothing */
} /* _lifeCellBackgroundProc */




/* _lifeCellSelectionProc -- overrides the default listview cell selection
 *			highlighting method so that nothing gets drawn for
 *			the selection highlighting.
 *
 *  -> listview	   -- the listview to draw the selection highlighting for.
 *  -> row, column -- the cell to draw.
 *  -> rect	   -- screen region to draw into.
 */
static void _lifeCellSelectionProc (vlistview *listview, int row, int column,
				    vrect *rect)
{
    /* draw nothing */
} /* _lifeCellSelectionProc */




/* _lifeCellContentProc -- Draw the cell's contents -- black square for a
 *			living, breathing cell, background for dead, deceased,
 *			no long amongst the living cells.
 *
 *  -> listview	   -- the listview to draw the cell for.
 *  -> row, column -- the cell to draw.
 *  -> selection   -- izzit selected?
 *  -> rect	   -- screen region to draw into.
 */
static void _lifeCellContentProc (vlistview *listview, int row, int column,
				  int selected, vrect *rect)
{
    int		 blorf;
    vcolor	*currentColor;
    lifeRock	*nRoll = (lifeRock*)vlistviewGetData (listview);

    if (nRoll->drawPetri == NULL) {
	blorf = _lifeIsAlive (nRoll->currentPetri, row, column);
    } else {
	blorf = _lifeIsAlive (nRoll->drawPetri, row, column);
    }

    currentColor = vdrawGetColor ();

    if (blorf) {
	vdrawSetColor (vdialogDetermineItemForeground
		       (vlistviewGetItem(listview)));
	vdrawRectsFill (rect, 1);
    } else {
	vdrawSetColor (vdialogDetermineItemBackground
		       (vlistviewGetItem(listview)));
	vdrawRectsFill (rect, 1);
    }

    vdrawSetColor (currentColor);

} /* _lifeCellContentProc */




/* _lifeListviewSelectNotify -- notify procedure for the life listview.
 *
 *  -> listview	   -- the listview where the selection is changing
 *  -> state	   -- one of the 3 magic listview selection state values:
 *		      vlistviewSELECTION_WILL_CHANGE,
 *		      vlistviewSELECTION_IS_CHANGING,
 *		      vlistviewSELECTION_HAS_CHANGED
 *
 * This does a "fatbits" style of turning on - off cells in the listview.
 */
static void _lifeListviewSelectNotify (vlistview *listview, int state)
{
    int        row, column;
    vlist     *list = vlistviewGetList (listview);
    lifeRock  *quartz = (lifeRock*)vlistviewGetData (listview);

    vlistGetSelectedCell (list, vlistviewGetVolatileSelection (listview),
			  &row, &column);
    
    if (state == vlistviewSELECTION_WILL_CHANGE) {

	/* get the cell value from the volatile selection (the one that's
	 * currently visible on the screen */
	/* if there is something in the selection, use that as the cell
	 * that was clicked on */
	if (row != vlistNO_CELLS_SELECTED) {
	    quartz->areRemoving = _lifeIsAlive (quartz->currentPetri, 
						row, column);

	    if (quartz->areRemoving) {
		/* removing cells */
		_lifeAbort (quartz->currentPetri, row, column);
	    } else {
		/* adding cells */
		_lifeConceive (quartz->currentPetri, row, column); 
	    }
	    vlistviewDrawCell (listview, row, column);
	}

    } else if ((state == vlistviewSELECTION_IS_CHANGING)
	       || (state == vlistviewSELECTION_HAS_CHANGED)) {

	if (row != vlistNO_CELLS_SELECTED) {

	    if (quartz->areRemoving) {  /* set during SELECTION_WILL_CHANGE */
		_lifeAbort (quartz->currentPetri, row, column);
	    } else {
		_lifeConceive (quartz->currentPetri, row, column);
	    }
	    vlistviewDrawCell (listview, row, column);
	}
    } 
} /* _lifeListviewSelectNotify */




/* _lifeSetupListview -- sets up various attributes of the life listview.
 *
 *  -> listview	  -- bork's listview o' death.
 */
static void _lifeSetupListview (vlistview *listview)
{
    vlist	*list;

    /* create a new vlist and attach it to the view */
    list = vlistCreate ();
    vlistviewSetList (listview, list);

    /* only use ONE_ONLY_SELECTION -- that makes it easy to do "fatbits" 
     * style editing of cells. */
    vlistSetSelectMethod (list, vlistviewGetSelection (listview),
			  vlistONE_ONLY_SELECTION);

    /* attach our selection-change notification */
    vlistviewSetSelectNotify (listview, _lifeListviewSelectNotify);

    /* attach our custom cell-drawing routine */
    vlistviewSetCellContentProc (listview, _lifeCellContentProc);

    /* set the cell sizes */
    vlistviewSetRowHeight (listview, vlistviewALL_ROWS, lifeCELL_SIZE);
    vlistviewSetColumnWidth (listview, vlistviewALL_COLUMNS, lifeCELL_SIZE);

    /* set the size of our petridishen */
    vlistSetRowCount (list, lifeNUM_DOWN);
    vlistSetColumnCount (list, lifeNUM_ACROSS);

    /* turn on the scroll bars */
    vlistviewSetHorzBar (listview, TRUE);
    vlistviewSetVertBar (listview, TRUE);

    /* we don't need no steenkin' keyboard */
    vlistviewSetUseKeyboardSelection (listview, FALSE);
    vlistviewSetUseKeyboardTraversal (listview, FALSE);

} /* _lifeSetupListview */




/* _lifeRegisterLifeListviewClass -- create and register a subclass of
 *			vlistview used in our life dialog.
 */
static vlistviewClass *_lifeGetDefaultListviewClass (void)
{
    static vlistviewClass *defaultClass = NULL;

    if (defaultClass == NULL) {
	defaultClass = vclassReproduce (vlistviewGetDefaultClass());

	vclassSetNameScribed (defaultClass, 
			      vcharScribeLiteral("lifelistview"));

	vclassSet (defaultClass,
		   vlistviewSELECTION_INSET, 
		   0);

	vclassSet (defaultClass,
		   vlistviewDRAW_CELL_BACKGROUND, 
		   _lifeCellBackgroundProc);

	vclassSet (defaultClass,
		   vlistviewDRAW_CELL_SELECTION,
		   _lifeCellSelectionProc);
    }

    return (defaultClass);

} /* _lifeGetDefaultListviewClass */




/* _lifeShutdownDialog -- destroy auxiliary memory consumed by the dialog.
 *
 *  -> dialog -- the dialog to clean up after
 */
static void _lifeShutdownDialog (vdialog *dialog)
{
    lifeRock 		*gibraltar;

    gibraltar = (lifeRock*)vdialogGetData (dialog);
    vtimerStop (gibraltar->timer);
    vtimerDestroy (gibraltar->timer);
    vmemFree (gibraltar->petri1);
    vmemFree (gibraltar->petri2);
    vpoolFree (primordialSoup, gibraltar);
    vlistDestroy (vlistviewGetList ((vlistview*)
				    vdialogFindItem
				    (dialog, TAG("Life Listview"))));
} /* _lifeShutdownDialog */



/* ----------------- Command implementation -------------------*/



/* _lifeIssueCloseCommand -- do the Real Work for this command.
 *			close the life dialog
 *
 *  -> command	  -- the command that is being handled.
 *  -> attr2value -- dictionary of attributes and values.
 * <-		  -- TRUE or FALSE.
 */
static int _lifeIssueCloseCommand (vcommandFunction *command,
				   vdict *attr2value)
{
    vdialog *dialog;
    
    dialog = (vdialog*)vdictLoad (attr2value, vname_Dialog);

    windowsetRemoveDialog (lifeWindowset, dialog);

    _lifeShutdownDialog (dialog);

    vwindowDestroyLater (vdialogGetWindow(dialog));

    return (TRUE);

} /* _lifeIssueCloseCommand */




/* _lifeIssueClearCommand -- do the Real Work for this command.
 *			clear the listview
 *
 *  -> command	  -- the command that is being handled.
 *  -> attr2value -- dictionary of attributes and values.
 * <-		  -- TRUE or FALSE.
 */
static int _lifeIssueClearCommand (vcommandFunction *command,
				   vdict *attr2value)
{
    vdialog *dialog = (vdialog*)vdictLoad (attr2value, vname_Dialog);
    lifeRock *stallone = (lifeRock*)vdialogGetData (dialog);
    vlistview *listview = (vlistview*)vdialogFindItem (dialog,
						       TAG("Life Listview"));

    (void)vmemSet (stallone->petri1, 0, sizeof(petriDish));
    (void)vmemSet (stallone->petri2, 0, sizeof(petriDish));

    vlistviewInval (listview);

    return (TRUE);
} /* _lifeIssueClearCommand */




/* _lifeIssueStartCommand -- do the Real Work for this command.
 *			start the life animation running
 *
 *  -> command	  -- the command that is being handled.
 *  -> attr2value -- dictionary of attributes and values.
 * <-		  -- TRUE or FALSE.
 */
static int _lifeIssueStartCommand (vcommandFunction *command,
				   vdict *attr2value)
{
    vdialog *dialog = (vdialog*)vdictLoad (attr2value, vname_Dialog);
    lifeRock *mica = (lifeRock*)vdialogGetData (dialog);

    vtimerStart (mica->timer);

    return (TRUE);

} /* _lifeIssueStartCommand */




/* _lifeIssueStopCommand -- do the Real Work for this command.
 *			stop the life animation
 *
 *  -> command	  -- the command that is being handled.
 *  -> attr2value -- dictionary of attributes and values.
 * <-		  -- TRUE or FALSE.
 */
static int _lifeIssueStopCommand (vcommandFunction *command,
				  vdict *attr2value)
{
    vdialog *dialog = (vdialog*)vdictLoad (attr2value, vname_Dialog);
    lifeRock *feldspar = (lifeRock*)vdialogGetData (dialog);

    vtimerStop (feldspar->timer);

    return (TRUE);

} /* _lifeIssueStopCommand */




/* _lifeIssueStepCommand -- do the Real Work for this command.
 *			do one life generation
 *
 *  -> command	  -- the command that is being handled.
 *  -> attr2value -- dictionary of attributes and values.
 * <-		  -- TRUE or FALSE.
 */
static int _lifeIssueStepCommand (vcommandFunction *command,
				  vdict *attr2value)
{
    vdialog *dialog = (vdialog*)vdictLoad (attr2value, vname_Dialog);
    lifeRock *aa = (lifeRock*)vdialogGetData (dialog);

    _lifeRunner (aa->timer);

    return (TRUE);

} /* _lifeIssueStepCommand */




/* ----------------- Command Mappings ------------------- */


static vcommandFunctionTemplate lifeCommandDefs[] = {
    { "Close Window", _lifeIssueCloseCommand, NULL },
    { "Close", _lifeIssueCloseCommand, NULL }, 
    { "Clear", _lifeIssueClearCommand, NULL },
    { "xBegin", _lifeIssueStartCommand, NULL },
    { "Halt",  _lifeIssueStopCommand,  NULL },
    { "Step",  _lifeIssueStepCommand,  NULL },
    { NULL }
};





/* ----------------- Misc Support stuff ----------------- */


/* _lifeSetupCommands -- attachs commands for the various menu items
 *			in the life dialog.  It does so by creating a
 *			command space and attaching it to the dialog's
 * 			window.
 *  -> dialog -- the dialog to attach the command space to
 */
void _lifeSetupCommands (vdialog *dialog)
{
    vcommandSpace	*commandSpace;
    vdict		*commandDict;
    vcommandFunction	*functionCommand;
    vcommandFunctionTemplate	*selectScan;

    /* create a dictionary that will store all of our commands */
    commandDict = vdictCreate (vnameHash);
    
    /* create a brand new command space that will hold our dictionary */
    commandSpace = vcommandCreateSpace ();
    
    /* cycle through our lifeCommandDefs[] and create the command
     * bindings.   To add more commands, add to the lifeCommandDefs array
     * up above. */

    for (selectScan = lifeCommandDefs;
	 selectScan->name != NULL;  selectScan++) {

	/* create a new command... */
	functionCommand = vcommandCreateFunctionOfClass (vcommandGetDefaultFunctionClass());

	/* ... set its issuing function if it has one ... */
	if (selectScan->issueFunc) {
	    vcommandSetFunctionIssue (functionCommand, selectScan->issueFunc);
	}

	/* ... and set its query function if it has one ... */
	if (selectScan->queryFunc) {
	    vcommandSetFunctionQuery (functionCommand, selectScan->queryFunc);
	}

	/* ... and store that pupper into our command dictionary. */
	vdictStore (commandDict, TAG(selectScan->name),
		    functionCommand);
    }

    /* now attach our command dictionary to the command space. */
    vcommandAddSpaceDictOwned (commandSpace, vname_Command,
			       commandDict);

    /* and finally, attach this space to the dialog's window. */
    vwindowSetSpaceOwned (vdialogGetWindow(dialog), commandSpace);

} /* _lifeSetupCommands */




/* _lifeShutdown -- shutdown listlife.c, clean up our mess, put away
 *			our toys and go home.
 */
static void _lifeShutdown (void)
{
    windowsetIterator    iterator;
    vdialog 		*dialog;

    windowsetInitIterator (&iterator, lifeWindowset);
    while (windowsetNextIterator (&iterator)) {
	dialog = windowsetGetIteratorDialog (&iterator);
	if (dialog) {
	    _lifeShutdownDialog (dialog);
	    vdialogDestroy (dialog);
	}
    }
    windowsetDestroyIterator (&iterator);

    windowsetDestroyUnbalanced (lifeWindowset);
 
    vpoolDestroy (primordialSoup);

} /* _lifeShutdown */




/* listdemoNewLife -- creates a new window which lets you do a Conway's
 *			Life game.
 *
 *  -> resource -- a resource dictionary containing our resources
 */
void listdemoNewLife (vresource resource)
{
    vresource	dialogRes;
    vdialog    *dialog;
    vlistview  *listview;
    vtimer     *timer;
    lifeRock   *rocky;

    /* make sure we have a pool to get our rocks from.  If primordialSoup
     * is NULL, this is the first time through this, so do other 
     * once-only initialization now */
    if (primordialSoup == NULL) {
	primordialSoup = vpoolCreate (sizeof(lifeRock));

	/* create and register our lifelistview subclass */
	(void) _lifeGetDefaultListviewClass ();
	
	/* create our windowset so we can clean up our mess afterwards */
	lifeWindowset = windowsetCreate ();

	/* get called at the end of time */
	vclientRegisterShutdown (_lifeShutdown);
    }

    rocky = vpoolAlloc (primordialSoup);
    
    /* snarf the resource for the dialog */
    dialogRes = vresourceGet (resource, TAG("Dialog"));
    
    /* create an instance from the resource */
    dialog = vdialogLoad (dialogRes);

    windowsetAddDialog (lifeWindowset, dialog);
    
    /* attach command space */
    _lifeSetupCommands (dialog);

    /* colorize the menubar */
    listdemoColorizeMenubar (dialog, NULL);
    
    /* snarf our listview and set it up */
    listview = (vlistview*)vdialogFindItem (dialog, TAG("Life Listview"));

    _lifeSetupListview (listview);
    
    timer = vtimerCreate ();
    vtimerSetSyncProc (timer, vwindowSyncEvents);
    vtimerSetNotify (timer, _lifeRunner);
    vtimerSetRecurrent (timer);
    vtimerSetPeriod (timer, 0, vtimestampSECOND / 4);

    vtimerSetData (timer, rocky);
    vlistviewSetData (listview, rocky);
    vdialogSetData (dialog, rocky);
    
    rocky->petri1 = (petriDish*)vmemAllocAndClear (sizeof(petriDish));
    rocky->petri2 = (petriDish*)vmemAllocAndClear (sizeof(petriDish));
    
    rocky->currentPetri = rocky->petri1;
    rocky->otherPetri = rocky->petri2;
    
    rocky->drawPetri = NULL;
    rocky->areRemoving = FALSE;

    rocky->timer = timer;
    rocky->listview = listview;
    
    /* ??? center window? */

    /* show that pupper */
    vdialogOpen (dialog);
	
} /* listdemoNewLife */




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

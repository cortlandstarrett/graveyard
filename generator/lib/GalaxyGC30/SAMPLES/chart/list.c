/* $Id: list.c,v 1.8 1995/02/09 16:56:19 ian Exp $ */
/* The legal types make me put this in here.
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
 * copyright notice in the form of "Copyright 1994 Visix Software Inc.,
 * 11440 Commerce Park Drive, Reston, VA  22091. All Rights Reserved" appears
 * in all copies, (ii) both the copyright notice and this permission notice
 * appear in supporting documentation and (iii) you are a valid licensee of
 * Galaxy Application Environment.
 *
 * Do not taunt Happy Fun Ball
 */

/* list.c -- Implementation for an attribute-notification dialog
 *
 * Module:
 *	xdemolist
 *
 * Docs and description are in xlist.h
 *
 * See file chart.c for more comments about this whole project.
 */

#ifndef  vportINCLUDED
#include <vport.h>		/* for v*HEADER */
#endif

#ifndef  vapplicationINCLUDED
#include vapplicationHEADER
#endif

#ifndef  vbuttonINCLDUED
#include vbuttonHEADER
#endif

#ifndef  vcommandINCLUDED
#include vcommandHEADER
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

#ifndef  vnumINCLUDED
#include vnumHEADER
#endif

#ifndef  vresourceINCLUDED
#include vresourceHEADER
#endif

#ifndef  vstrINCLUDED
#include vstrHEADER
#endif

#include "xlist.h"




/* necessary set-up so we can declare the data table */
typedef struct tablething {
    int	  intIndex;
    char *indexName;
    char *valueName;
    int	  val1;
    int   val2;
    int   val3;
    int	  val4;
} tablething;


/* the table of data.  The size of the table can be gotten by the clients
 * by doing a vlistGetRowCount/vlistGetColumnCount.  The clients do need
 * have knowlege of the table's structure so they know what rows/columns
 * to access.
 */
static tablething table[] = {
    { 1,     "Jan 1743", "Hoover",     120,	 60,	95,	 20 },
    { 2,     "Feb 1743", "Greeble",    110,	 50,	40,	 25 },
    { 3,     "Mar 1743", "Bork",	90,	100,	60,	 39 },
    { 4,     "Apr 1743", "Ni",		80,	 80,	45,	 24 },
    { 5,     "May 1743", "Noo",	        70,	 70,	81,	 20 },
    { 6,     "Jun 1743", "Fnord",	60,	 80,	65,	 15 },
    { 7,     "Jul 1743", "Ekky",	50,	 90,	65,	 10 },
    { 8,     "Aug 1743", "Wizzel",	30,	100,	51,	  5 },
    { 9,     "Sep 1743", "Poohbah",     10,	110,	90,	 42 },
    { 10,    "Oct 1743", "Peng",        20,	 90,	84,	 35 },
    { 11,    "Nov 1743", "Womm",        10,	 80,	53,	 20 },
    { 12,    "Dec 1743", "Bork",        30,	 70,	42,	 23 },
    { 13,    "Jan 1744", "Hoover",	20,	 90,	45,	 20 },
    { 14,    "Feb 1744", "Greeble",	10,	 50,	40,	 25 },
    { 15,    "Mar 1744", "Bork",	30,	100,	60,	 39 },
    { 16,    "Apr 1744", "Ni",		40,	 80,	45,	 24 },
    { 17,    "May 1744", "Noo",	        45,	 70,	51,	 20 },
    { 25,     NULL,	  NULL,         -1,	 -1,	-1,	-1  }
};


/* how wide to make each column of the listview */
static int widths[] = 
{     30,    75,          60,		35,	 35,	 35,	 35 };


/* the list holding the data */
static vlist *list = NULL;


/* the dialog to let the user choose from */
static vdialog *dialog = NULL;


/* procedrue to call when the selected subset of the list changes */
xdemolistNoteProc notify = NULL;




/*
 * ----- Support Functions
 */


/* _xdemolistCellContentProc -- cell drawing routine for the listview.
 *				some cells are strings, some are integers.
 *				This handles each in their own special way.
 *
 *  -> listview -- the listview to draw the cell in
 *  -> row	-- the row to draw
 *  -> column	-- the column to draw
 *  -> selected -- TRUE if the cell is selected, FALSE otherwise
 *  -> rect	-- the rect to draw in
 */
static void _xdemolistCellContentProc (vlistview *listview, 
				       int row, int column,
				       int selected, vrect *rect)
{
    vchar *value;
    vchar  buffer[50];

    if ((column == 1) || (column == 2)) {
	value = (vchar*)vlistGetCellValue (list, row, column);
    } else {
	vcharCopyScribed (vnumScribeInt((int)vlistGetCellValue
					(list,row,column)), buffer);
	value = buffer;
    }

    if (value != NULL) {
	vrect newRect = *rect;
	newRect.x += 5;
	newRect.w -= 5;
	vdrawRectShowCenterY (value, &newRect);
    }

} /* _xdemolistCellContentProc */




/* _xdemolistButtonNotify -- Handler for the "Choose Subset" button. 
 *			     It calcs the range of selected values then
 *			     calls the notify.
 *
 *  -> button -- the button that was pressed
 *  -> event  -- the event that diddit
 */
static void _xdemolistButtonNotify (vbutton *button, vevent *event)
{
    int min = INT_MAX, max = INT_MIN;
    vlistview *listview = (vlistview*) vbuttonGetData (button);
    vlistIterator iterator;

    if (notify != NULL) {
	if (vlistCountSelectedCells (list, 
				     vlistviewGetSelection(listview)) == 0) {
	    min = 0;
	    max = vlistGetRowCount (list) - 1;
	} else {
	    vlistInitSelectionIterator (&iterator,
					vlistviewGetSelection(listview));
	    
	    while (vlistNextIterator(&iterator)) {
		min = vMIN (min, vlistGetIteratorRow (&iterator));
		max = vMAX (max, vlistGetIteratorRow (&iterator));
	    }
	    
	    vlistDestroyIterator (&iterator);
	}
	(notify)(min, max);
    }
    
} /* _xdemolistButtonNotify */

/* _xdemolistShutdown -- clean up our mess
 */
static void _xdemolistShutdown (void)
{
    int row, column;
    vstr *value;

    for (row = 0; row < vlistGetRowCount(list); row++) {
	for (column = 1; column < 3; column++) {
	    value = (vstr*)vlistGetCellValue (list, row, column);
	    if (value != NULL) {
		vstrDestroy (value);
	    }
	}
    }
    vlistDestroy (list);

    vdialogDestroy (dialog);

} /* _xdemolistShutdown */




/*
 * ----- Command stuff
 */


/* This is kinda overkill for attaching one and only one command to the
 * dialog's command space.  But what the hey, this code already existed
 * and works.
 */

static int _closeIssue (vcommandFunction *command, vdict *attr2value)
{
    veventStopProcessing ();
    return (TRUE);
} /* _closeIssue */


typedef struct commandDef {
    const char	       *tagName;
    vcommandFunc	issueFunc;
    vcommandFunc	queryFunc;
} commandDef;


static commandDef commandTable[] = {
    { "Close",		       _closeIssue,		NULL },
    { NULL,		       NULL,			NULL }
};


static void _setupCommands (vdialog *dialog)
{
    vcommandFunction	*functionCommand;
    vcommandSpace	*commandSpace;
    vdict		*commandDict;
    commandDef		*commandScan;

    commandDict = vdictCreate (vnameHash);
    commandSpace = vcommandCreateSpace ();

    for (commandScan = commandTable;
	 commandScan->tagName != NULL; commandScan++) {
	
	functionCommand = (vcommandCreateFunctionOfClass 
			   (vcommandGetDefaultFunctionClass()));
	
	if (commandScan->issueFunc) {
	    vcommandSetFunctionIssue (functionCommand, commandScan->issueFunc);
	}

	if (commandScan->queryFunc) {
	    vcommandSetFunctionQuery (functionCommand, commandScan->queryFunc);
	}

	vdictStore (commandDict, 
		    vnameInternGlobalLiteral(commandScan->tagName), 
		    functionCommand);
    }

    vcommandAddSpaceDictOwned (commandSpace, vname_Command, commandDict);
    vwindowSetSpaceOwned (vdialogGetWindow(dialog), commandSpace);
    
} /* _setupCommands */


static const vchar *_xdemolistCellNamer (vlist *list, int row, int column)
{
  static vchar	numBuf[32];
  const vchar	*ret;


  if (column == 1 || column == 2)
    ret = (vchar *) vlistGetCellValue(list, row, column);
  else {
    numBuf[31] = 0;
    vcharCopyScribedBounded(vnumScribeInt((int) vlistGetCellValue(list, row,
	column)), numBuf, 31);
    ret = numBuf;
  }
  return(ret);
}

/*
 * ----- Exported functions
 */


/* xdemolistGetListDialog -- get the dialog that contains the listview
 *			     for our list.
 *
 * <- the dialog containing the list
 */
vdialog *xdemolistGetListDialog (void)
{
    if (dialog == NULL) {
	vresource   appres, dialogres;
	vlistview  *listview;
	tablething *scan;
	vstr	   *str;
	int	    row = 0;

	appres = vapplicationGetResources (vapplicationGetCurrent());
	dialogres = vresourceGet (appres, vnameInternGlobalLiteral("DataList"));
	dialog = vdialogLoad (dialogres);

	_setupCommands (dialog);

	list = vlistCreate ();
	vlistSetCellNamer(list, _xdemolistCellNamer);

	for (scan = table; scan->indexName != NULL; scan++) {
	    
	    vlistSetCellValue (list, row, 0, (void*)scan->intIndex);
	    
	    str = vstrCloneScribed (vcharScribeLiteral(scan->indexName));
	    vlistSetCellValue (list, row, 1, str);
	    
	    str = vstrCloneScribed (vcharScribeLiteral(scan->valueName));
	    vlistSetCellValue (list, row, 2, str);
	    
	    vlistSetCellValue (list, row, 3, (void*)scan->val1);
	    vlistSetCellValue (list, row, 4, (void*)scan->val2);
	    vlistSetCellValue (list, row, 5, (void*)scan->val3);
	    vlistSetCellValue (list, row, 6, (void*)scan->val4);

	    row++;
	}

	listview = (vlistview*)vdialogFindItem (dialog, vnameInternGlobalLiteral
						("listview"));
	vlistviewSetList (listview, list);

	vlistSetExtendRowSelection (list, vlistviewGetSelection(listview),
				    TRUE);
	vlistSetSelectMethod (list, vlistviewGetSelection(listview),
			      vlistRECTANGULAR_SELECTION);

	{
	    int i;
	    for (i = 0; i < 7; i++) {
		vlistviewSetColumnWidth (listview, i, widths[i]);
	    }
	}
	vlistviewSetCellContentProc (listview, _xdemolistCellContentProc);

	/* turn off keyboard selection for simplicity */
	vlistviewSetUseKeyboardSelection (listview, FALSE);

	{
	    vbutton *button;

	    button = (vbutton*)vdialogFindItem(dialog, vnameInternGlobalLiteral
					       ("Choose Subset"));
	    vbuttonSetNotify (button, _xdemolistButtonNotify);
	    vbuttonSetData (button, listview);
	}

	vclientRegisterShutdown (_xdemolistShutdown);

    }

    return (dialog);
} /* xdemolistGetListDialog */




/* xdemolistSetNotify -- set the function that will be caleld when the
 *			 selected range changes.
 *
 *  -> newNotify -- the notification procedure to use
 */
void xdemolistSetNotify (xdemolistNoteProc newNotify)
{
    notify = newNotify;
} /* xdemolistSetNotify */




/* xdemolistGetList -- get the vlist that contains all of the good stuff
 *
 * <-  -- the list with the Good Stuff
 */
vlist *xdemolistGetList (void)
{
    /* start us up if we're not started already */
    if (list == NULL) {
	(void)xdemolistGetListDialog ();
    }

    return (list);

} /* xdemolistGetList */


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

/* $Id: ruler.c,v 1.5 1995/07/26 15:32:18 seanm Exp $ */

/*----------------------------------------------------------------------------
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
 * copyright notice in the form of "Copyright 1992 Visix Software Inc.,
 * 11440 Commerce Park Drive, Reston, VA  22091. All Rights Reserved" appears
 * in all copies, (ii) both the copyright notice and this permission notice
 * appear in supporting documentation and (iii) you are a valid licensee of
 * Galaxy Application Environment.
 ---------------------------------------------------------------------------*/

/****************************************************************************
 * Executable Name: ruler
 * Source Files:    ruler.c, rultag.c
 * Header Files:    rultag.h
 * Resource Files:  ruler.vr
 *
 * Managers Illustrated:
 *     Ruler Standard Item
 *     List Manager
 *     Command Manager 
 *     Resource Manager
 *
 * Description Of Sample:
 *     This sample provides an example of using the ruler to control a 
 *     listview.  The following operations are possible:
 *
 *     select a column from a list
 *     resize a column
 *     remove a column
 *     move a column
 *     
 *     This example always compacts the ruler.  This makes things much
 *     easier to implement.  The ruler items cannot get any bigger.
 *     Something I haven't tracked down yet.
 * 
 *     The demo can be stopped by using the File/Quit menu item.
 *
 *     Hints: to watch rulerNotify messages
 *        setenv vdebugMODULE ruler
 *        setenv vdebugLEVEL  750
 *
 * History:
 *	$Log: ruler.c,v $
 * Revision 1.5  1995/07/26  15:32:18  seanm
 * added compaction for item removal
 *
 * Revision 1.4  1994/08/12  21:49:07  erik
 * changed var name class to clas to avoid C++ problems
 * this sample was crashing when compiled in debug mode -- fixed now
 * this sample leaked when columns were removed
 * this sample caused exception when column was removed (b03716)
 * debug mode problem mentioned above is b04013
 *
 * Revision 1.3  1994/02/28  22:04:39  tom
 * Fixed compile error
 *
 * Revision 1.2  1994/02/28  17:54:12  simone
 * vince beautified comment.s.
 *
 * Revision 1.1  1993/08/29  17:51:07  chad
 * Initial revision
 *
 *	Written for 1.2 release 6/16/93
 * 
 ****************************************************************************/

#define vdebugTAG "ruler"

/* Galaxy headers */
#include <vgalaxy.h>

/* Private headers */
#include "rultag.h"

/* Global variables */

/* Local variables */

#define ROW_COUNT 5

enum {
    comQUIT
};

typedef struct {
    const char *tagStr;
    short       enumValue;
} selCmd;

static selCmd selCmdBindings[] = {
    {"appQUIT",  comQUIT},
    {NULL}
};

/* Function Definitions */
/* 
 * dialogNotify - dialog notify function 
 */
static void dialogNotify (vdialog *dialog, vevent *event);
/* 
 * setSelCmdDict - setup command selector in dictionary 
 */
static void setSelCmdDict(vdict *cmdDict, vcommandSelectorClass *clas);
/* 
 * issueCmds     - command selector issue function 
 */
static int issueCmds(vcommandSelector *command, vdict *context);
/*
 * rulerNotify   - ruler notify function 
 */
static void rulerNotify (vruler *ruler, 
			 vevent *event, 
			 vrulerItem *item, 
			 int message);
/* 
 * setupRulerAndListView - self explanatory
 */
static void setupRulerAndListView (vdialog *dialog);
/*
 * destroyList - self explanatory 
 */
static void destroyList (vdialog *dialog);

/**********
 * main:
 *
 **********/
int main(int argc, char *argv[])
{
  vresource              resource, dialogRes;
  vdialog               *dialog;
  vcommandSpace         *space;
  vdict                 *cmdDict;
  vcommandSelectorClass *defaultSelectorClass = NULL;

  /*
   * Read user preferences from the command line arguments:
   */
  vstartup (argc, argv);
    
  /*
   * Make the custom classes for the demo
   */
  rultagInternNames ();
  /*
   * Pull the dialog out of resource since we have our
   * classes made already
   */
  resource  = vapplicationGetResources( vapplicationGetCurrent() );
  
  dialogRes = vresourceGet(resource, rultag_Dialog);
  dialog    = vdialogLoad (dialogRes);
  /*
   * Do some command stuff 
   */
  cmdDict   = vdictCreate (vnameHash);

  defaultSelectorClass = vclassReproduce(vcommandGetDefaultSelectorClass());
  vclassSet(defaultSelectorClass, vcommandISSUE, issueCmds);

  setSelCmdDict (cmdDict, defaultSelectorClass);

  space     = vcommandCreateSpace ();
  vcommandAddSpaceDictOwned(space, vname_Command, cmdDict);
  vwindowSetSpaceOwned(vdialogGetWindow(dialog), space);

  setupRulerAndListView (dialog);

  vdialogSetNotify (dialog, dialogNotify);
  vdialogOpen (dialog);
  /*
   * Process events until the window is closed:
   */
  veventProcess();

  destroyList (dialog);
  vdialogDestroy (dialog);
    
  exit( EXIT_SUCCESS );
  return EXIT_FAILURE;
}  /**  main()  **/

/* dialogNotify -- notify function for the dialog.
 *                 If we are closing the dialog call veventStopProcessing().
 *
 * -> dialog    -- the dialog.
 * -> event     -- the event that caused us to get here.   
 */
static void dialogNotify (vdialog *dialog, vevent *event)
{
    if (veventGetType(event) == veventWINDOW_STATE && veventIsClose(event))
    {
	fprintf(stderr, "The Window Manager made me do it...\n");
	veventStopProcessing();
    }
}
/* setSelCmdDict -- setup the command dictionary for our command 
 *                  selector class. The file scoped variable selCmdBindings 
 *                  is used to initialize the dictionary.
 *
 * -> cmdDict   -- the command dictionary to put our selector into
 * -> clas      -- our command selector class 
 */
static void setSelCmdDict(vdict *cmdDict, vcommandSelectorClass *clas)
{
    selCmd           *bindPtr;
    vcommandSelector *select;

    for (bindPtr = selCmdBindings; bindPtr->tagStr != NULL; bindPtr++)
    {
	select = vcommandCreateSelectorOfClass(clas);

	vcommandSetSelector(select, bindPtr->enumValue );

	vdictStore(cmdDict, vnameInternGlobalLiteral(bindPtr->tagStr), select);
    }
}
/* issueCmds  -- our command selector issue function
 *
 * -> command -- our command selector
 * -> context -- our command context dictionary (not used)
 * <- returns whether command was handled.
 */
static int issueCmds(vcommandSelector *command, vdict *context)
{
    int      selector = vcommandGetSelector (command);
    int      retValue;

    switch (selector) {
    case comQUIT:
	veventStopProcessing ();
	retValue = TRUE;
	break;
    default:
	retValue = FALSE;
	break;
    }
    return retValue;
}
/* rulerNotify  -- called whenever the ruler is notified. We cheat by 
 *                 calling vrulerCompact to keep the ruler compacted.
 *                 Otherwise on moves we'd have to figure out where we
 *                 moved to.  One nice thing on moves, the rulerItems
 *                 are reordered by the time we get a vrulerITEM_MOVE_END
 *                 message.
 *
 * -> ruler    -- the ruler
 * -> event    -- the event which caused our notify (usually NULL)
 * -> item     -- the rulerItem which received the event
 * -> message  -- the type of notification we are receiving
 */
void rulerNotify (vruler *ruler, vevent *event, vrulerItem *item, int message)
{
    int        index;
    static int movingIndex;
    static int compacting;	/*  vrulerCompact calls RulerNotify      */
                                /*  this eliminates unnecessary calls to */
                                /*  RulerNotify -- this should be on the */
                                /*  ruler data pointer                   */
    vlistview *listview = (vlistview *) vrulerGetData (ruler);
    vlist     *list     = vlistviewGetList (listview);
    int        row;

    vdebugTrace ("rulerNotify Item: %d Message: %d\n",
	item ? vrulerGetItemIndex(item) : -1, message);

    if (compacting)		/*  don't do anything if we got here from */
	return;			/*  vrulerCOMPACT message                 */
    switch (message) {
    case vrulerITEM_SELECT:	/* 1 Item is selected with single click*/
	index = vrulerGetItemIndex (item);
	vlistUnselectAll (list, vlistviewGetSelection (listview));
	vlistSelectColumn (list, vlistviewGetSelection(listview), index);
	break;
    case vrulerITEM_DOUBLE:	/* 2 Item is double-clicked */
	break;
    case vrulerREDRAW_ALL:      /* 3 obsolete */
    case vrulerITEM_WILL_REMOVE: /* 4 item will be removed from ruler */
	index = vrulerGetItemIndex (item);
	if (vlistIsCellSelected (list, vlistviewGetSelection (listview),
				 0, index))
	    vlistUnselectColumn (list, vlistviewGetSelection (listview),
				 index);
	for (row = vlistGetRowCount(list) - 1; row >= 0; row--) {
	    vstr *str;

	    str = (vstr *) vlistGetCellValue (list, row, index);
	    vstrDestroy (str);
	}
	vlistRemoveColumn (list, index);
	compacting = TRUE;	/*  vrulerCompact causes this notify */
	vrulerCompact (ruler);	/*  function to be called */
	compacting = FALSE;
	break;
    case vrulerITEM_REMOVE:	/* 5 Item is removed from ruler */
	compacting = TRUE;	/*  vrulerCompact causes this notify */
	vrulerCompact (ruler);	/*  function to be called */
	compacting = FALSE;
	break;
    case vrulerITEM_MOVE_START:	/* 6 Item is starting a move */
	movingIndex = vrulerGetItemIndex (item);
	break;
    case vrulerITEM_MOVE_END:  {/* 7  Item has completed a move */
	index  = vrulerGetItemIndex (item); /*  ruler changes index for us */
	if (movingIndex != index)
	    vlistMoveColumn (list, movingIndex, index);
	movingIndex = -1;
	compacting  = TRUE;
	vrulerCompact (ruler);
	compacting  = FALSE;
	break;
    }
    case vrulerITEM_RESIZE_START: /* 8 Item is beginning a resize  */
	break;
    case vrulerITEM_RESIZE_END:	{ /* 9 Item has completed a resize */
	int width;

	index = vrulerGetItemIndex (item);
	width = vrulerGetItemWidth (item);
	vlistviewSetColumnWidth (listview, index, 
				 width + vrulerGetSpacing(ruler));
	compacting = TRUE;
	vrulerCompact (ruler);
	compacting = FALSE;
	break;
    }
    case vrulerSCROLL_START:	/* 10  */
	break;
    case vrulerSCROLL_END:	/* 11  */
	break;
    case vrulerRESIZE:		/* 12  The ruler has been resized          */
	break;
    case vrulerITEM_ADD:	/* 13  An Item has been added to the ruler */
	break;
    }
}
/* setupRulerAndListView -- Find the ruler and listview in the dialog.
 *                          Create the list, hook it to the listview.
 *                          Setup the list.  Put strings into the list
 *                          Setup the column widths from the ruler resource.
 * 
 * -> dialog  -- the dialog which has the ruler and listview
 */    
void setupRulerAndListView (vdialog *dialog)
{
    int         i = 0; 
    int         j = 0;
    int         cols;
    vruler     *ruler;
    vrulerItem *item;
    vlistview  *listview;
    vlist      *list;

    ruler    = (vruler *)    vdialogFindItem (dialog, rultag_Ruler);
    listview = (vlistview *) vdialogFindItem (dialog, rultag_ListView);
    list     = vlistCreate ();
    vlistviewSetList (listview, list);
    cols     = vrulerGetItemCount (ruler);

    vlistSetRowCount    (list, ROW_COUNT);
    vlistSetColumnCount (list, cols);

    for (i = 0; i < ROW_COUNT; i++) {
        for (j = 0; j < cols; j++) {
	    vstr       *str;
            str = vstrCloneScribed (vscribeScribeMulti 
                                    (vcharScribeLiteral("("),
                                     vnumScribeInt(i),
                                     vcharScribeLiteral(", "),
                                     vnumScribeInt(j),
                                     vcharScribeLiteral(")"),
                                     NULL));
            vlistSetCellValue (list, i, j, str);
        }
    }
    /* set up the listview columns from the ruler */
    for (j = 0; j < cols ; j++) {
	int width, spacing;

	spacing  = vrulerGetSpacing (ruler);
	item     = vrulerGetItemAt (ruler, j);
	width    = vrulerGetItemWidth (item);
	vlistviewSetColumnWidth (listview, j, width + spacing);
    }
    vrulerSetNotify (ruler, rulerNotify);
    vrulerSetData   (ruler, (void *) listview);
}
/* destroyList -- destroy the list associated with the listview
 *
 * -> dialog -- the dialog where the listview is which has our list.
 */
void destroyList (vdialog *dialog)
{
    int        i, j;
    int        rows, cols;
    vlistview *listview;
    vlist     *list;

    listview = (vlistview *) vdialogFindItem (dialog, rultag_ListView);
    list     = vlistviewGetList (listview);

    rows = vlistGetRowCount    (list);
    cols = vlistGetColumnCount (list);

    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
	    vstr      *str;
	    str = (vstr *) vlistGetCellValue (list, i, j);
	    vstrDestroy (str);
        }
    }

    vlistDestroy (list);
}


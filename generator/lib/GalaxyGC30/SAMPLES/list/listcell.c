/* $Id: listcell.c,v 1.2 1993/11/24 02:12:20 chad Exp $
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

/* listcell.c -- Using the in-cell editing subclass of listview
 *
 * vlist is a collection of distinct Galaxy list manager applications,
 * ranging from a simple list to stocks and bondage to life.
 *
 * The various parts of this demo are:
 * vlist.c     -- Chief overlord and starter-up of the other demos.
 * listlife.c  -- Conway's game o' life.
 * listapi.c   -- Fiddle with the API and see what does what.
 * listcell.c  -- Do in-cell editing. (this file)
 *   xincell.h    -- interface to in-cell editing subclass.
 *   incell.c     -- implementation of in-cell editing subclass.
 */

/* This file demonstrates these concepts:
 *    Simple command setup.
 *    use of the xincell class.
 */


#define vdebugTAG "listDoInCell"

#ifndef vportINCLUDED
#include <vport.h>
#endif

#ifndef vnameINCLUDED
#include vnameHEADER
#endif

#ifndef vcommandINCLUDED
#include vcommandHEADER
#endif

#ifndef vresourceINCLUDED
#include vresourceHEADER
#endif

#ifndef vstrINCLUDED
#include vstrHEADER
#endif

#ifndef vnumINCLUDED
#include vnumHEADER
#endif

#ifndef vlistINCLUDED
#include vlistHEADER
#endif

#ifndef vdialogINCLUDED
#include vdialogHEADER
#endif

#ifndef vlistviewINCLUDED
#include vlistviewHEADER
#endif


#include "listdemo.h"
#include "xincell.h"


/* convenience macro */
#define TAG(s)	vnameInternGlobalLiteral ((s))


/* ------------------ module global variables ------------------- */



static windowset *incellWindowset = NULL;



/* _incellSetupDialog -- stick default values into the in-cell listview.
 *
 *  -> dialog -- the dialog to setup
 */
static void _incellSetupDialog (vdialog *dialog)
{
    xincell	*incell;
    vlistview	*listview;
    vlist	*list;
    vstr	*str;
    int		 i, j;

    incell = (xincell*)vdialogFindItem (dialog, TAG("InCellThing"));
    listview = xincellGetListview (incell);

    vlistviewSetHorzBar (listview, TRUE);
    vlistviewSetVertBar (listview, TRUE);

    list = vlistCreate ();
    vlistviewSetList (listview, list);

    vlistSetRowCount (list, 40);
    vlistSetColumnCount (list, 40);
    
    for (i = 0; i < 40; i++) {
	for (j = 0; j < 40; j++) {
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
    
    vlistviewSetColumnWidth (listview, vlistviewALL_COLUMNS, 60);

} /* _incellSetupDailog */



/* _incellShutdownDialog -- mop-after during dialog destruction
 */
static void _incellShutdownDialog (vdialog *dialog)
{
    xincell *incell;
    vlist *list ;
    vlistIterator iterator;
    vstr *str;

    incell = (xincell*)vdialogFindItem (dialog, TAG("InCellThing"));
    list = vlistviewGetList (xincellGetListview(incell));

    vlistInitIterator (&iterator, list);
    while (vlistNextIterator (&iterator)) {
	str = (vstr*)vlistGetIteratorValue (&iterator);
	if (str != NULL) {
	    vstrDestroy (str);
	}
    }

    vlistDestroyIterator (&iterator);
    vlistDestroy (list);

} /* _incellShutdownDialog */





/* ----------------- Command Implementation ------------------- */




/* _incellCloseIssue -- issue close command - close the window.
 *
 *  -> func	  -- the command being handled.
 *  -> attr2value -- attributes dictionary.
 * <-		  -- TRUE if we handled it,
 *		     FALSE otherwise
 */
static int _incellCloseIssue (vcommandFunction *func, vdict *attr2value)
{
    vdialog *dialog;
    
    dialog = (vdialog*)vdictLoad (attr2value, vname_Dialog);

    windowsetRemoveDialog (incellWindowset, dialog);

    _incellShutdownDialog (dialog);

    vwindowDestroyLater (vdialogGetWindow(dialog));

    return (TRUE);

} /* _incellCloseIssue */




/* _incellAcceptIssue -- issue Accept command - Accept the edited text.
 *
 *  -> func	  -- the command being handled.
 *  -> attr2value -- attributes dictionary.
 * <-		  -- TRUE if we handled it,
 *		     FALSE otherwise
 */
static int _incellAcceptIssue (vcommandFunction *func, vdict *attr2value)
{
    xincell *incell;
    vdialog *dialog;

    dialog = (vdialog*)vdictLoad (attr2value, vname_Dialog);
    incell = (xincell*)vdialogFindItem (dialog, TAG("InCellThing"));

    xincellAcceptEditing (incell);

    return (TRUE);

} /* _incellAcceptIssue */




/* _incellCancelIssue -- issue Cancel command - Cancel the edited text
 *
 *  -> func	  -- the command being handled.
 *  -> attr2value -- attributes dictionary.
 * <-		  -- TRUE if we handled it,
 *		     FALSE otherwise
 */
static int _incellCancelIssue (vcommandFunction *func, vdict *attr2value)
{
    xincell *incell;
    vdialog *dialog;

    dialog = (vdialog*)vdictLoad (attr2value, vname_Dialog);
    incell = (xincell*)vdialogFindItem (dialog, TAG("InCellThing"));

    xincellCancelEditing (incell);

    return (TRUE);

} /* _incellCancelIssue */





/* _incellCanEditIssue -- issue CanEdit command - toggle the can edit state
 *
 *  -> func	  -- the command being handled.
 *  -> attr2value -- attributes dictionary.
 * <-		  -- TRUE if we handled it,
 *		     FALSE otherwise
 */
static int _incellCanEditIssue (vcommandFunction *func, vdict *attr2value)
{
    xincell *incell;
    vdialog *dialog;
    
    dialog = (vdialog*)vdictLoad (attr2value, vname_Dialog);
    incell = (xincell*)vdialogFindItem (dialog, TAG("InCellThing"));
    
    if (xincellIsEditing(incell)) {
	xincellSetEditing (incell, FALSE);
    }
    xincellSetCanEdit (incell, !xincellGetCanEdit(incell));

    return (TRUE);

} /* _incellCanEditIssue */





/* ----------------- Command Mappings ------------------- */

typedef struct selectDef {
    const char	       *tagName;
    vcommandFunc	issueFunc;
    vcommandFunc	queryFunc;
} selectDef;


static vcommandFunctionTemplate incellCommandDefs[] = {
    { "Close Window",	      _incellCloseIssue,   NULL },
    { "Close",		      _incellCloseIssue,   NULL },
    { "Accept Editing",	      _incellAcceptIssue,  NULL },
    { "Cancel Editing",	      _incellCancelIssue,  NULL },
    { "Can Edit",	      _incellCanEditIssue, NULL },
    { "No Auto Resize",	      NULL,	           NULL },
    { "Auto Row Resize",      NULL,	           NULL },
    { "Auto Column Resize",   NULL,	           NULL },
    { "Text Can Grow",	      NULL,	           NULL },
    { NULL,		      NULL,	           NULL }
};




/* _incellSetupCommands -- attachs commands for the various menu items
 *			in the incell dialog.  It does so by creating a
 *			command space and attaching it to the dialog's
 * 			window.
 *  -> dialog -- the dialog to attach the command space to
 */
void _incellSetupCommands (vdialog *dialog)
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

    for (selectScan = incellCommandDefs;
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

} /* _incellSetupCommands */



static void _incellShutdown (void)
{
    windowsetIterator    iterator;
    vdialog 		*dialog;

    windowsetInitIterator (&iterator, incellWindowset);
    while (windowsetNextIterator (&iterator)) {
	dialog = windowsetGetIteratorDialog (&iterator);
	if (dialog) {
	    _incellShutdownDialog (dialog);
	    vdialogDestroy (dialog);
	}
    }
    windowsetDestroyIterator (&iterator);

    windowsetDestroyUnbalanced (incellWindowset);

} /* _incellShutdown */




/* listdemoNewIncell -- creates a new incell-editing window.
 *
 *  -> resource -- a resource dicationary containing our resources
 */
void listdemoNewIncell (vresource resource)
{
    vresource	dialogRes;
    vdialog *dialog;

    if (incellWindowset == NULL) {
	/* this is first-time initialization */
	
	/* create our windowset so we can clean up our mess afterwards */
	incellWindowset = windowsetCreate ();
	
	/* make sure the class is created and registered */
	(void)xincellGetDefaultClass ();

	/* get called at the end of time */
	vclientRegisterShutdown (_incellShutdown);
    }

    /* get the resource for the dialog */
    dialogRes = vresourceGet (resource, TAG("Dialog"));
    
    /* create an instance from the resouce */
    dialog = vdialogLoad (dialogRes);

    windowsetAddDialog (incellWindowset, dialog);
    
    /* attach commands */
    _incellSetupCommands (dialog);
    
    /* colorize the menubar */
    listdemoColorizeMenubar (dialog, NULL);
    
    /* setup other stuff */
    _incellSetupDialog (dialog);
    
    /* show that pupper */
    vdialogOpen (dialog);

} /* listdemoNewIncell */



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

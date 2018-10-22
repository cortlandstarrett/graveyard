/* $Id: thump.c,v 1.2 1995/01/19 19:32:54 chad Exp $ */


/* we include tons of headers because we're doing the minimal-startup thing
 */

#include <vport.h>

#ifndef  vstdlibINCLUDED /* for EXIT_SUCCESS et.al. */
#include vstdlibHEADER
#endif

#ifndef  vdialogINCLUDED
#include vdialogHEADER
#endif

#ifndef  vcontrolINCLUDED
#include vcontrolHEADER
#endif

#ifndef  vmenubarINCLUDED
#include vmenubarHEADER
#endif

#ifndef  vcontainerINCLUDED
#include vcontainerHEADER
#endif

#ifndef  vbuttonINCLUDED
#include vbuttonHEADER
#endif

#ifndef  vapplicationINCLUDED
#include vapplicationHEADER
#endif


#ifndef  xpacemakerINCLUDED
#include "xpacemak.h"
#endif

#ifndef  xstatusINCLUDED
#include "xstatus.h"
#endif

#ifndef  xgroupINCLUDED
#include "xgroup.h"
#endif

#define TAG(s)	vnameInternGlobalLiteral((s))


/*
 * ----- constants and global variables and forward references (oh my!)
 */

/* how big the to make images being constructed
 */
#define IMAGE_SIZE 400

/* the different "in-progress" status types.  Percentage and barbershop-pole
 * are modes for the xstatus object.  statusNONE will be a blocking operation.
 */
enum {
    statusPERCENTAGE,
    statusBARBERSHOP_POLE,
    statusNONE
};

/* one of the above types */
static int g_statusType = statusPERCENTAGE;


/* TRUE if the status dialog should be modal, FALSE if not
 */
static vbool g_modalStatus;



/* the different image calculator functions.  They are chosen by
 * radio buttons in the main window.
 */
static vbyte _groupMultiplyCalc (int x, int y);
static vbyte _groupAddCalc (int x, int y);
static vbyte _groupModCalc (int x, int y);
static vbyte _groupModCalc2 (int x, int y);

static xgroupCalcFunc g_calculatorTable[] = { _groupAddCalc,
					      _groupMultiplyCalc,
					      _groupModCalc,
					      _groupModCalc2 };
/* the current function to use 
 */
static int g_groupIndex = 0;


/* the main window that controls this whole thingie
 */
static vdialog *g_mainDialog;



/* a handy convenience function for converting a command function table
 * into a command space and mashing it into the given dialog
 */
static void _installCommandSpace (vdialog *dialog,
				  vcommandFunctionTemplate *table,
				  int count);

/* a handy macro for calculating the "count" parameter above.
   */
#define _count(table)	(sizeof(table) / sizeof(vcommandFunctionTemplate))




/*
 * ----- group calculation functions
 */


/* _groupMultiplyCalc -- calculator function for an xgroup.
 *			 This one looks like Moire' patters
 *
 *  -> x, y  -- an integer point in the 1st quadrant of the cartesian plane
 * <-	     -- some spiffy return value
 */
static vbyte _groupMultiplyCalc (int x, int y)
{
    return (x * y);
} /* _groupMultiplyCalc */




/* _groupMultiplyCalc -- calculator function for an xgroup.
 *			 This one is diagonal lines
 *
 *  -> x, y  -- an integer point in the 1st quadrant of the cartesian plane
 * <-	     -- some spiffy return value
 */
static vbyte _groupAddCalc (int x, int y)
{
    return (x + y);
} /* _groupAddCalc */




/* _groupMultiplyCalc -- calculator function for an xgroup.
 *			 This one looks like shattered diagonal lines
 *
 *  -> x, y  -- an integer point in the 1st quadrant of the cartesian plane
 * <-	     -- some spiffy return value
 */
static vbyte _groupModCalc (int x, int y)
{
    return (x + ((y == 0) ? y : (x % y)) );
} /* _groupModCalc */




/* _groupMultiplyCalc -- calculator function for an xgroup.
 *			 wide horizontal stripes with the moire
 *			 stretched along one diagonal
 *
 *  -> x, y  -- an integer point in the 1st quadrant of the cartesian plane
 * <-	     -- some spiffy return value
 */
static vbyte _groupModCalc2 (int x, int y)
{
    return (y * x / (((y == 0) ? y : (x % y))*2+1) );
} /* _groupModCalc2 */




/*
 * ----- Random utility functions
 */


/* _imageCloseIssue -- the close  window command for the image display
 * 		       dialog.  It just destroyes itself.
 *
 *  -> command    -- the command being dispatched
 *  -> attr2value -- the context the command is executing in
 * <-		  -- TRUE if we handled the command, false otherwise
 */
static int _imageCloseIssue (vcommandFunction *command, vdict *attr2value)
{
    vwindowDestroyLater ((vwindow*)vdictLoad(attr2value, vname_Dialog));
    return (TRUE);
} /* _imageCloseIssue */



/* the command template for the image display dialog.
 * "Close" is issued when the dialog is closed by the user
 * "Close Window" is issued from a menu item
 */
static vcommandFunctionTemplate imageDialogCommandTable[] = {
    { "Close",		_imageCloseIssue, NULL },
    { "Close Window",	_imageCloseIssue, NULL }
};




/* _pacemakerNotify -- the notify for the group pacemaker.
 *
 *  -> pacemaker -- the pacemaker going "ka-thump, ka-thump"
 *  -> message   -- the message indicating what's going on
 */
static void _pacemakerNotify (xpacemaker *pacemaker, int message)
{
    xstatus *status = (xstatus*)xpacemakerGetData (pacemaker);
    vdialog *dialog = NULL;

    /* the status indicator is hidden in the pacemaker's data pointer
     */
    if (status != NULL) {
	dialog = vdialogDetermineItemDialog (xstatusGetItem(status));
    }

    switch (message) {
	case xpacemakerNOTIFY_FINISHED: { /* we be done */
	    vresource appres, dialogres;
	    vdialogItem *item;
	    vdialog *imageDialog;
	    
	    /* open up the image dialog to display our work */
	    appres = vapplicationGetResources (vapplicationGetCurrent());
	    dialogres = vresourceGet (appres, TAG("Image Dialog"));
	    
	    imageDialog = vdialogLoad (dialogres);
	    
	    item = vdialogFindItem (imageDialog, TAG("Image"));

	    vdialogSetItemImageOwned (item, 
				      vimageClone(xgroupGetImage
						  ((xgroup*)pacemaker)));

	    /* install this space so we can destroy ourselves when we close */
	    _installCommandSpace (imageDialog, imageDialogCommandTable,
				  _count(imageDialogCommandTable));
	    
	    vdialogOpen (imageDialog);

	    /* -= fall through =- */
	}
	case xpacemakerNOTIFY_TERMINATED: { /* we were aborted early */
	    xpacemakerDestroyLater (pacemaker);

	    /* this nukes the dialog containing the status bar, not the image
	     * dialog
	     */
	    if (dialog != NULL) {
		vwindowDestroyLater (vdialogGetWindow(dialog));
	    }
	    break;
	}
	case xpacemakerNOTIFY_WORK_PERFORMED: { /* update status */
	    /* the status can be NULL if we're doing a blocking calculation */
	    if (status != NULL) {
		xgroup *group = (xgroup*)pacemaker;
		int pos = (xgroupGetCurrentY(group) * xgroupGetWidth(group)
			   + xgroupGetCurrentX(group));
		xstatusAdvanceTo (status, pos);
	    }
	    break;
	}
    }

} /* _pacemakerNotify */



/*
 * ----- Stuff for the terminator dialog
 */


/* _terminatorStopIssue -- the user has indicated that they want no more work
 * 			   to be done. (fickle user)
 *
 *  -> command    -- the command being issued
 *  -> attr2value -- the context the command is being issued in
 * <-		  -- TRUE if we handled the command, false otherwise
 */
static int _terminatorStopIssue (vcommandFunction *command, vdict *attr2value)
{
    vdialog *dialog = (vdialog*)vdictLoad (attr2value, vname_Dialog);
    xgroup *group = (xgroup*)vdialogGetData (dialog);

    xpacemakerTerminate (xgroupGetPacemaker(group));

    return (TRUE);

} /* _terminatorStopIssue */


/* the command template for the terminator dialog
 * "Close" is issued from window-system window manager
 * "Stop!" is a pushbutton
 */
static vcommandFunctionTemplate terminatorCommandTable[] = {
    { "Close",	_terminatorStopIssue, NULL },
    { "Stop!",  _terminatorStopIssue, NULL }
};



/* _openTerminatorDialog -- open a dialog showing status and giving the
 * 			    using a button to push to stop the operation.
 *			    Closing the dialog will have the same effect
 *			    as pushing the button (frank)
 *
 *  -> openRelativeTo -- where to put the terminator relative to
 *  -> group          -- the group object that's doing the work
 */
static void _openTerminatorDialog (vdialog *openRelativeTo, xgroup *group)
{
    vresource appres, dialogres;
    vdialog *dialog;
    xstatus *status;

    appres = vapplicationGetResources (vapplicationGetCurrent());
    dialogres = vresourceGet (appres, TAG("Terminator"));

    dialog = vdialogLoad (dialogres);

    /* if we quite while one of these is active, we'll need to stop the
     * pacemaker.  Otherwise our pacemaker notification will try to
     * update a destroyed dialog
     */
    vwindowSetTag (vdialogGetWindow(dialog), TAG("Terminator"));

    _installCommandSpace (dialog, terminatorCommandTable,
			  _count(terminatorCommandTable));
    status = (xstatus*)vdialogFindItem (dialog, TAG("status"));

    /* make the status bar display the Right Thing */
    if (g_statusType == statusPERCENTAGE) {
	xstatusSetMax (status,
		       xgroupGetWidth(group) * xgroupGetHeight(group));
    } else if (g_statusType == statusBARBERSHOP_POLE) {
	xstatusSetBarberPole (status, TRUE);
    }

    /* reflect the user's checkbox choice */
    vwindowSetModal (vdialogGetWindow(dialog), g_modalStatus);

    /* hide the group under the dialog.  Necessary for proper handling of
     * the "Stop!" button
     */
    vdialogSetData (dialog, group);

    /* hide the status object under the group so it can be updated on
     * an xpacemakerNOTIFY_WORK_PERFORMED notification
     */
    xpacemakerSetData (xgroupGetPacemaker(group), status);

    /* and away we go...
     */
    vdialogOpen (dialog);

} /* _openTerminatorDialog */




/*
 * ----- Command implementation
 */


/* _startIssue -- start a calculation
 *
 *  -> command    -- the command being issued
 *  -> attr2value -- the context the command is being issued in
 * <-		  -- TRUE if we handled the command, false otherwise
 */
static int _startIssue (vcommandFunction *command, vdict *attr2value)
{
    /* create and set up the group as per the user's dialog choices */
    xgroup *group = xgroupCreate ();

    xgroupSetCalculator (group, g_calculatorTable[g_groupIndex]);

    xgroupSetSize (group, IMAGE_SIZE, IMAGE_SIZE);
    xpacemakerSetNotify (xgroupGetPacemaker(group), _pacemakerNotify);

    /* do a blocking or non-blocking calculation, as per the user's desires */
    if (g_statusType == statusNONE) {
	xgroupCalculate (group, FALSE); /* block */

    } else {
	vdialog *dialog = (vdialog*)vdictLoad (attr2value, vname_Dialog);
	_openTerminatorDialog (dialog, group);
	xgroupCalculate (group, TRUE);  /* don't block */
    }

    return (TRUE);

} /* _startIssue */




/* _percentageIssue -- the clicking of the "do a percentage status" radio
 *		       button
 *
 *  -> command    -- the command being issued
 *  -> attr2value -- the context the command is being issued in
 * <-		  -- TRUE if we handled the command, false otherwise
 */
static int _percentageIssue (vcommandFunction *command, vdict *attr2value)
{
    g_statusType = statusPERCENTAGE;

    return (TRUE);

} /* _percentageIssue */




/* _barbershopIssue -- the clicking of the "do a barbeshop pole status" radio
 *		       button
 *
 *  -> command    -- the command being issued
 *  -> attr2value -- the context the command is being issued in
 * <-		  -- TRUE if we handled the command, false otherwise
 */
static int _barbershopIssue (vcommandFunction *command, vdict *attr2value)
{
    g_statusType = statusBARBERSHOP_POLE;

    return (TRUE);

} /* _barbershopIssue */




/* _noStatusIssue -- the clicking of the "don't do any status" radio button
 *
 *  -> command    -- the command being issued
 *  -> attr2value -- the context the command is being issued in
 * <-		  -- TRUE if we handled the command, false otherwise
 */
static int _noStatusIssue (vcommandFunction *command, vdict *attr2value)
{
    g_statusType = statusNONE;

    return (TRUE);

} /* _noStatusIssue */




/* _modalStatusIssue -- the clicking of the "make the status window modal"
 *		        toggle
 *
 *  -> command    -- the command being issued
 *  -> attr2value -- the context the command is being issued in
 * <-		  -- TRUE if we handled the command, false otherwise
 */
static int _modalStatusIssue (vcommandFunction *command, vdict *attr2value)
{
    const vname *val = vdictLoad (attr2value, vname_Toggle);

    g_modalStatus = (val == vname_On);

    return (TRUE);

} /* _modalStatusIssue */




/* _modalStatusIssue -- the choice of group calculation has changed.
 *
 *  -> command    -- the command being issued
 *  -> attr2value -- the context the command is being issued in
 * <-		  -- TRUE if we handled the command, false otherwise
 *
 * This is the command that handles commands issued by the container that
 * contains the radio buttosn for choosing the groups.  It translates the
 * radio button into an index into a function table defined at the top
 * of this file.
 */
static int _groupsIssue (vcommandFunction *command, vdict *attr2value)
{
    vcontainer *container = (vcontainer *)vdictLoad (attr2value,
						     vname_Operator);
    vdialogItem *item = (vdialogItem *)vdictLoad (attr2value,
						  vname_Selection);
    g_groupIndex = vcontainerGetItemIndex (container, item);

    return (TRUE);

} /* _groupsIssue */





/*
 * ----- Generic app-level scaffolding
 */


static void _setupDialog (vdialog *dialog)
{
    
} /* _setupDialog */




static void _shutdownDialog (vdialog *dialog)
{
    /* everything but the vdialog destroy */
} /* _shutdownDialog */




static void _generalSetup (void)
{
    (void) vcontrolGetToggleClass ();
    (void) vdialogGetDefaultClass ();
    (void) vdialogGetDefaultItemClass ();
    (void) vmenubarGetDefaultClass ();
    (void) vmenuGetDefaultClass ();
    (void) vmenuGetDefaultItemClass ();
    (void) vcontainerGetDefaultClass ();
    (void) vdialogGetBoxItemClass ();
    (void) vbuttonGetDefaultClass ();

    (void) xstatusGetDefaultClass ();
    
} /* _generalSetup */




static void _generalShutdown (void)
{

} /* _generalShutdown */




/*
 * ----- Generic Scaffolding follows
 */


/* _quitIssue -- the user has indicated that they're bored with us and want
 *		 us to go away (sob)  Pack up our toys and go home.
 *
 *  -> command    -- the command being issued
 *  -> attr2value -- the context the command is being issued in
 * <-		  -- TRUE if we handled the command, false otherwise
 */
static int _quitIssue (vcommandFunction *command, vdict *attr2value)
{
    vwindow *window;
    vapplicationWindowIterator iterator;

    vapplicationInitWindowIterator (&iterator, vapplicationGetCurrent());
    
    while (vapplicationNextWindowIterator (&iterator)) {
	window = vapplicationGetWindowIteratorWindow (&iterator);
	if (window != vdialogGetWindow(g_mainDialog)) {
	    if (vwindowGetTag(window) == TAG("Terminator")) {
		/* we will call vwindowDestroyLater in our pacemaker notify */
		xpacemakerTerminate ((xpacemaker*)vwindowGetData(window));
	    } else {
		vwindowDestroy(vapplicationGetWindowIteratorWindow(&iterator));
	    }
	}
    }
    vapplicationDestroyWindowIterator (&iterator);
    
    veventStopProcessing ();

    return (TRUE);

} /* _quitNotify */



/* this is the table of commands that might be issued by our main 
 * "control-pannel" dialog
 */
static vcommandFunctionTemplate mainWindowCommandTable[] = {
    { "Start",		_startIssue,		NULL },

    { "Percentage",	_percentageIssue,	NULL },
    { "Barbershop Pole",_barbershopIssue,	NULL },
    { "No Status",	_noStatusIssue,		NULL },

    { "Modal Status",	_modalStatusIssue,	NULL },

    { "Groups",		_groupsIssue,		NULL },

    { "Close",		_quitIssue,		NULL },
    { "Quit",		_quitIssue,		NULL },
};




/* _installCommandSpace -- handy utility function for constructing a
 * 			   dialog's command space
 *
 *  -> dialog -- the dialog to put a command space into
 *  -> table  -- the talbe of function commands to mash into the dialog
 *  -> count  -- the number of entries in the table
 */
static void _installCommandSpace (vdialog *dialog,
				  vcommandFunctionTemplate *table,
				  int count)
{
    vdict *dict;
    vcommandSpace *space;
    
    dict = vcommandCreateDictFunctionTemplates (table, count);
    
    space = vcommandCreateSpace ();
    
    vcommandAddSpaceDictOwned (space, vname_Command, dict);
    
    vwindowSetSpaceOwned (vdialogGetWindow(dialog), space);
    
} /* _installCommandSpace */




/* main -- what's this for?
 *
 *  -> argc -- I dunno
 *  -> argv -- better take care of that sneezing
 * <-	    -- Daisy... daisy...
 */
int main (int argc, char *argv[])
{
    vresource appres, dialogres;

    vprefSetArgs (argc, argv);

    _generalSetup ();

    appres = vapplicationGetResources (vapplicationGetCurrent());
    dialogres = vresourceGet (appres, TAG("Dialog"));

    g_mainDialog = vdialogLoad (dialogres);

    _installCommandSpace (g_mainDialog, mainWindowCommandTable, 
			  _count(mainWindowCommandTable));

    _setupDialog (g_mainDialog);

    vdialogOpen (g_mainDialog);

    veventProcess ();

    _shutdownDialog (g_mainDialog);

    vdialogDestroy (g_mainDialog);

    _generalShutdown ();

    exit (EXIT_SUCCESS);
    return (EXIT_FAILURE);

} /* main */





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


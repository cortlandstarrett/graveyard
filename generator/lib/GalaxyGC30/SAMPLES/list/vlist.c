/* $Id: vlist.c,v 1.3 1997/05/05 19:59:46 david Exp $
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

/* vlist.c -- C implementation for a list manager demo application.
 *
 * vlist is a collection of distinct Galaxy list manager applications,
 * ranging from a simple list to life.
 *
 * The various parts of this demo are:
 * vlist.c        -- Chief overlord and starter-up of the other demos.
 *                   (this file)
 * listlife.c     -- Conway's game o' life.
 * listapi.c      -- Fiddle with the API and see what does what.
 * listcell.c     -- Do in-cell editing.
 *   xincell.h    -- interface to in-cell editing subclass.
 *   incell.c     -- implementation of in-cell editing subclass.
 */

/* This file doesn't actually have any List Manager code in it.  This is all
 * driver and support stuff for the rest of the demo
 *
 * This file demonstrates these concepts:
 *     Minimal header inclusion
 *     Minimal program startup
 *     Simple command setup
 *     Manipulating a menubar and its menus
 *     Tracking sets of windows for later iteration
 */


/* Galaxy headers */

#define vdebugTAG "listdemo"

#ifndef vportINCLUDED
#include <vport.h> /* for v*HEADER */
#endif

#ifndef vstdlibINCLUDED
#include vstdlibHEADER
#endif

#ifndef vpoolINCLUDED /* for windowset stuff */
#include vpoolHEADER
#endif

#ifndef vnameINCLUDED
#include vnameHEADER
#endif

#ifndef vdictINCLUDED
#include vdictHEADER
#endif

#ifndef vresourceINCLUDED
#include vresourceHEADER
#endif

#ifndef vcolorINCLUDED /* for menubar colorization */
#include vcolorHEADER
#endif

#ifndef vprefINCLUDED
#include vprefHEADER
#endif

#ifndef vcommandINCLUDED
#include vcommandHEADER
#endif

#ifndef vwindowINCLUDED /* for windowset stuff */
#include vwindowHEADER
#endif

#ifndef vdialogINCLUDED
#include vdialogHEADER
#endif

#ifndef vmenuINCLUDED  /* for menu colorization */
#include vmenuHEADER
#endif

#ifndef vmenubarINCLUDED /* for menubar colorization */
#include vmenubarHEADER
#endif

#ifndef vapplicationINCLUDED
#include vapplicationHEADER
#endif

#ifndef vlistitemINCLUDED /* for minimal startup */
#include vlistitemHEADER
#endif

#ifndef vbuttonINCLUDED /* for minimal startup */
#include vbuttonHEADER
#endif

#ifndef vtextitemINCLUDED /* for minimal startup */
#include vtextitemHEADER
#endif

#ifndef vsliderINCLUDED
#include vsliderHEADER /* for minimal startup */
#endif


/* Private headers */
#include "listdemo.h"



#define TAG(s)	vnameInternGlobalLiteral ((s))



/* ------------------ handy support stuff ------------------- */


/* listdemoColorizeMenubar -- In the Motif look-n-feel, having a colored
 *			      menubar lends some identity to the windows of
 *			      a particular application.  This function colors
 *			      the menubar of the dialog with a color 
 *			      obtained from the resource file.  Colored
 *			      menubars in other look-n-feels are either
 *			      forbidden (Windows & CUA), rarely if ever
 *			      used (Mac), or looks really really stupid
 *			      (OpenLook)
 *
 *  -> dialog     -- the dialog who has a menu to colorize
 *  -> menubarTag -- the Tag name of the menubar.  Passing NULL uses
 *		     the default tag name that vre gives menubars
 *		     (MenuBar)
 *
 * Does nothing if the current look and feel isn't vlafMOTIF.
 * Does nothing if the dialog doesn't have a menubar or if the menubarTag
 *   isn't found.  (this desicison was made to make client use of this
 *   function easier -- just run every dialog through this without having
 *   to care if the dialog has a menubar or not.  This lets menubars
 *   get added or removed during the development cycle and get colorized 
 *   properly.
 */
void listdemoColorizeMenubar (vdialog *dialog, const vname *menubarTag)
{
    /* only link in this code if the library has Motif l'n'f in it */
#ifdef vlafMOTIF
    if (vlafAppear() == vlafMOTIF) {
	vmenubar *menubar;
	static vcolor *menubarColor = NULL;

	/* first-time through, get the color from the resource file */
	if (menubarColor == NULL) {
	    vresource appres, colorres;
	    appres = vapplicationGetResources (vapplicationGetCurrent());
	    colorres = vresourceGet (appres, TAG("Menubar Color"));
	    menubarColor = vcolorLoadIntern (colorres);
	}

	if (menubarTag == NULL) {
	    menubar = (vmenubar*)vdialogFindItem (dialog, TAG("MenuBar"));
	} else {
	    menubar = (vmenubar*)vdialogFindItem (dialog, menubarTag);
	}

	if (menubar != NULL) {
	    int i;
	    vmenu *menu;

	    vdialogSetItemBackground (vmenubarGetItem(menubar), menubarColor);

	    /* colorize each of the menus as well */
	    for (i = 0; i < vmenubarGetMenuCount(menubar); i++) {
		menu = vmenubarGetMenuAt (menubar, i);
		vwindowSetBackground (vmenuGetWindow(menu), menubarColor);
	    }
	}
    }
#endif

} /* listdemoColorizeMenubar */




/* ------------------ windowset stuff ------------------- */


/* one of the more tedious aspects of being a neat and responsible citizen
 * is cleaning up your messes at the end of time.  In a dynamic windowed
 * environment, this is harder because you'd like to just create a window,
 * open it, and never want to worry about it again.
 *
 * This windowset is a way to make this stuff easier.  windowset clients
 * create a windowset and drop windows into it whenever they are created. 
 * When a window is destroyed, it should be removed from the windowset.  At
 * the end of time, the client iterates over the windowset and destroys the
 * winows they allocated.
 *
 * Why not just iterate over all of the windows at the end of time using
 * vwindowInitIterator et.al?  Frequently you want to do extra work
 * before destroying the window, such as freeing lists, destroying images,
 * or other general mayhem.
 * One way to do this is to subclass vdialog and override vinstanceDESTROY.
 * This would probably be the cleanest way to do this, but requires lots
 * of extra work that I'm too lazy to do right now :)
 *
 * To use the windowset stuff, do this
 *    * create the windowset
 *      windowset *set = windowsetCreate ();
 *
 *    * add windows to it
 *      vwindow *window = somehowGetAWindow ();
 *      windowsetAddWindow (set, window);
 *
 *    * remove windows if you destroy them yourself
 *      windowsetRemoveWindow (set, window);
 *      vwindowDestroyWindow (window);
 *
 *    * iterate over your windowset at the end of time destroying stuff.
 *      windowsetIterator iterator;
 *      windowsetInitIterator (&iterator, set);
 *      while (windowsetNextIterator(&iterator)) {
 *          vwindow *window = windowsetGetIteratorWindow (&iterator);
 *          doMyWindowCleanup (window);
 *          vwindowDestroy (window);
 *      }
 *      windowsetDestroyIterator (&iterator);
 *
 *      !warning! don't call windowsetRemoveWindow during iteration.  It will
 *      mess up the iteration.
 *
 *    * Destroy the windowset when done with it
 *      windowsetDestroy (windowset);
 *
 *    * if you've iterated over the windowset destroying everything, use
 *      windowsetDestroyUnbalanced (windowset);  This makes final destruction
 *      a bit cleaner.
 *
 * As a convenience, at the end of time, the list demo does iterate over
 * all windows and destroys them, so if you have a simple window with no
 * special destroy-time actions to perform, just open it and forget it, and
 * it'll be cleaned up.
 */

/* The windowsets are Yet Another Linked-List implementation.
 * The fundamental data type is the _windowsetNode, which is a linked-list
 * node.  A window set is composed of a dummy _windowsetNode that points
 * to the first window, then a linked-list of more _windosetNodes with the
 * actual window pointers inside of them.
 *
 * Why the dummy first node?  It's to make iteration implementation simple.
 * With the dummy first node, windowsetInitIterator can be set to point to
 * the dummy node, and windowsetNextIterator can be implemented as a simple
 * pointer chase.  If the windowset didin't have have the dummy node, 
 * windowsetNextIterator would have to special-case the first time through
 * the loop.
 */




/* where the linked-list nodes come from */
static vpool *windowsetPool = NULL;




/* _windowsetShutdown -- clean up the mess we made.  i.e. destroy our pool
 *                       at the end of time. 
 */
static void _windowsetShutdown (void)
{
    vpoolDestroy (windowsetPool);
} /* _windowsetShutdown */




/* windowsetCreate -- create a new windowset and return a pointer to it. 
 *
 * <- -- the new windowset
 */
windowset *windowsetCreate (void)
{
    windowset *set;

    /* perform first-time initialization */
    if (windowsetPool == NULL) {
	windowsetPool = vpoolCreate (sizeof (_windowsetNode));
	vclientRegisterShutdown (_windowsetShutdown);
    }

    set = vpoolAlloc (windowsetPool);

    /* first link in the chain is a dummy */
    set->window = NULL;
    set->next = NULL;

    return (set);
    
} /* windowsetCreate */




/* windowsetDestroy -- Nuke a windowset and its contents.  This will generate
 *		       vpool leaks if windows weren't removed from the 
 *		       windowset prior to destruction.
 *
 *  -> set -- the windowset to meet its maker
 */
void windowsetDestroy (windowset *set)
{
    vpoolFree (windowsetPool, set);
} /* windowsetDestroy */




/* windowsetDestroyUnbalanced -- Nuke a windowset and its contents.  This
 *				 will not generate any leak reports if there
 *				 are still elements in the windowset.
 *
 *  -> set -- the windoset to meet its maker, unbalanced
 */
void windowsetDestroyUnbalanced (windowset *set)
{
    _windowsetNode *scan, *death;

    /* stuff easier for clients is harder for us :p */

    /* remove all of the nodes from the windoset */
    scan = set->next;

    while (scan != NULL) {
	death = scan;
	scan = scan->next;
	vpoolFree (windowsetPool, death);
    }

    /* meet its maker */
    windowsetDestroy (set);

} /* windowsetDestroyUnbalanced */




/* windosetAddWindow -- add a window to the windowset.
 *
 *  -> set    -- the windowset to add a window to
 *  -> window -- the window to add to the set
 */
void windowsetAddWindow (windowset *set, vwindow *window)
{
    _windowsetNode *thing;

#if (vdebugDEBUG)
    /* see if this window is already in the set.  Warn the client if it's
     * been added twice (or more)
     */
    {
	_windowsetNode *scan;

	scan = set->next;

	while (scan != NULL) {
	    if (window == scan->window) {
		vdebugWarn ("windowsetAddWindow: window added twice to set\n");
		break;
	    }
	    scan = scan->next;
	}
    }
#endif

    /* alloc a node and stick it at the front of the set. (after the dummy
     * node)
     */
    thing = vpoolAlloc (windowsetPool);
    thing->window = window;
    thing->next = set->next;
    set->next = thing;

} /* windowsetAddWindow */




/* windowsetRemoveWindow -- remove a window from the set.
 *
 *  -> set    -- the set to remove the window from
 *  -> window -- the window to remove from the set.
 */
void windowsetRemoveWindow (windowset *set, vwindow *window)
{
    _windowsetNode *scan, *prev;

    scan = set->next;
    prev = set;

    while (scan != NULL) {
	if (window == scan->window) {
	    prev->next = scan->next;
	    vpoolFree (windowsetPool, scan);
	    break;
	}
	scan = scan->next;
	prev = prev->next;
    }

} /* windowsetRemoveWindow */




/* windowsetInitIterator -- initialize a windowset iterator.  An iterator
 *			    is basically a pointer to the windowset node
 *			    under scrutiny.
 *
 *  -> iterator -- the windowset iterator that needs initialization
 *  -> set      -- the windowset to iterate over
 */
void windowsetInitIterator (windowsetIterator *iterator, windowset *set)
{
    iterator->scan = set;
} /* windowsetInitIterator */




/* windowsetNextIterator -- advance the iterator to the next window.
 *
 *  -> iterator -- the windowset iterator being iterated with
 * <-           -- TRUE if there's more to iterate, FALSE otherwise
 */
int windowsetNextIterator (windowsetIterator *iterator)
{
    iterator->scan = iterator->scan->next;

    return (iterator->scan != NULL);

} /* windowsetNextIterator */




/* windowsetDestroyIterator -- free any memory used by the iterator.
 *
 *  -> iterator -- the windowset iterator.
 */
void windowsetDestroyIterator (windowsetIterator *iterator)
{
    /* no-op.  Included for completeness */
} /* windowsetDestroyIterator */




/* ------------------ control panel / main menu code ------------------- */


/* this next batch of functions implement the command handlers for the
 * pushbuttons on the listdemo control panel.
 */




/* _listdemoIssueQuitCommand -- quit from the application
 *
 *  -> command	  -- the command that is being handled.
 *  -> attr2value -- dictionary of attributes and values.
 * <-		  -- TRUE if we handled the command, FALSE otherwise.
 */
static int _listdemoIssueQuitCommand (vcommandFunction *command,
				      vdict *attr2value)
{
    /* tell the event manager that we're all through now */
    veventStopProcessing ();
    
    /* Yes, I handled it, stop looking for others to handle it. */
    return (TRUE);

} /* _listdemoIssueQuitCommand */




/* _listdemoIssueLifeCommand -- open up a life window.
 *
 *  -> command	  -- the command that is being handled.
 *  -> attr2value -- dictionary of attributes and values.
 * <-		  -- TRUE if we handled the command, FALSE otherwise.
 */
static int _listdemoIssueLifeCommand (vcommandFunction *command,
				      vdict *attr2value)
{
    vresource appres, liferes;

    appres = vapplicationGetResources (vapplicationGetCurrent());
    liferes = vresourceGet (appres, TAG("Life Resources"));

    /* create a new life window */
    listdemoNewLife (liferes);
    
    /* Yes, I handled it, stop looking for others to handle it. */
    return (TRUE);

} /* _listdemoIssueLifeCommand */




#if (NOT_YET_IMPLEMENTED)
/* _listdemoIssueStocklistCommand -- open up a stock listing window
 *
 *  -> command	  -- the command that is being handled.
 *  -> attr2value -- dictionary of attributes and values.
 * <-		  -- TRUE if we handled the command, FALSE otherwise.
 */
static int _listdemoIssueStocklistCommand (vcommandFunction *command,
					   vdict *attr2value)
{
    /* Nope, I didn't handle it */
    return (FALSE);

} /* _listdemoIssueStocklistCommand */
#endif




#if (NOT_YET_IMPLEMENTED)
/* _listdemoIssueOutlineCommand -- open up an outlining window
 *
 *  -> command	  -- the command that is being handled.
 *  -> attr2value -- dictionary of attributes and values.
 * <-		  -- TRUE if we handled the command, FALSE otherwise.
 */
static int _listdemoIssueOutlineCommand (vcommandFunction *command,
					 vdict *attr2value)
{
    /* Nope, didn't handle it */
    return (FALSE);

} /* _listdemoIssueOutlineCommand */
#endif




/* _listdemoAboutDialogNotify -- dialog notification that destroys the
 * 				 dialog when it's closed by the native window
 *				 manager.
 *
 *  -> dialog -- the dialog being closed
 *  -> event  -- the event that diddit
 *
 * The about dialog doesn't have a "nuke" pushbutton -- only a listitem
 * with legalese.
 */
static void _listdemoAboutDialogNotify (vdialog *dialog, vevent *event)
{
    if (veventIsClose(event)) {
	vwindowDestroyLater (vdialogGetWindow(dialog));
    }
} /* _listdemoAboutDialogNotify */




/* _listdemoIssueAboutCommand -- do the Real Work for this command.
 *			open up our about box
 *
 *  -> command	  -- the command that is being handled.
 *  -> attr2value -- dictionary of attributes and values.
 * <-		  -- TRUE if we handled the command, FALSE otherwise.
 */
static int _listdemoIssueAboutCommand (vcommandFunction *command,
				       vdict *attr2value)
{
    vresource    appres, dialogres;
    vdialog	*dialog;

    appres = vapplicationGetResources (vapplicationGetCurrent());
    dialogres = vresourceGet (appres, TAG("About Dialog"));

    dialog = vdialogLoad (dialogres);
    
    vdialogSetNotify (dialog, _listdemoAboutDialogNotify);
    vdialogOpen (dialog);

    /* if the window is opened, and the app quit, _listdemoFinalMopup()
     * will destroy the about window(s)
     */

    return (TRUE);

} /* _listdemoIssueAboutCommand */




#if (NOT_YET_IMPLEMENTED)
/* _listdemoIssueSpreadsheetCommand -- do the Real Work for this command.
 *			open up a pseudo psreadsheet window
 *
 *  -> command	  -- the command that is being handled.
 *  -> attr2value -- dictionary of attributes and values.
 * <-		  -- TRUE if we handled the command, FALSE otherwise.
 */
static int _listdemoIssueSpreadsheetCommand (vcommandFunction *command,
					     vdict *attr2value)
{
    /* nope, not handling this one either */
    return (FALSE);

} /* _listdemoIssueSpreadsheetCommand */
#endif




/* _listdemoIssueFiddlerCommand -- do the Real Work for this command.
 *			open up an API fiddler window
 *
 *  -> command	  -- the command that is being handled.
 *  -> attr2value -- dictionary of attributes and values.
 * <-		  -- TRUE if we handled the command, FALSE otherwise.
 */
static int _listdemoIssueFiddlerCommand (vcommandFunction *command,
					 vdict *attr2value)
{
    vresource appres, fiddlerres;

    appres = vapplicationGetResources (vapplicationGetCurrent());
    fiddlerres = vresourceGet (appres, TAG("API Fiddler Resources"));

    /* create a new api window */
    listdemoNewAPI (fiddlerres);
   
    return (TRUE);

} /* _listdemoIssueFiddlerCommand */




/* _listdemoIssueInCellCommand -- do the Real Work for this command.
 *			open up the In-cell editing window.
 *
 *  -> command	  -- the command that is being handled.
 *  -> attr2value -- dictionary of attributes and values.
 * <-		  -- TRUE if we handled the command, FALSE otherwise.
 */
static int _listdemoIssueInCellCommand (vcommandFunction *command,
					 vdict *attr2value)
{
    vresource appres, incellres;

    appres = vapplicationGetResources (vapplicationGetCurrent());
    incellres = vresourceGet (appres, TAG("In-Cell Resources"));

    /* create a new api window */

    listdemoNewIncell (incellres);
    
    return (TRUE);

} /* _listdemoIssueInCellCommand */




/* _listdemoSetupCommands -- attaches commands for the various pushbuttons
 *			in the control panel.  It does so by creating a command
 *			space and attaching it to the dialog's window.
 *
 *  -> dialog	-- the dialog to attach the command sapce to.
 *
 * the lines marked with "*!*" are the lines that different between setting
 * up the different commands.  Some of the other listdemo files use a more
 * succinct way of setting this up.
 */
static void _listdemoSetupCommands (vdialog *dialog)
{
    /* command space for storing mappings between the following functions
     * and the buttons in the control panel.  This space becomes attached
     * to the control panel window */
    vcommandSpace 	*commandSpace = NULL;

    /* command dictionary that actually holds the mappings.  */
    vdict		*commandDict  = NULL;

    vcommandFunction	*functionCommand;
    

    /* create a dictionary that will store all of our commands */
    commandDict = vdictCreate (vnameHash);
    
    /* create a brand new command space that will hold our dictionary */
    commandSpace = vcommandCreateSpace ();
    
    
    
    /* create the quit command... */
    functionCommand = vcommandCreateFunction ();
    
    /* Set the function to be called when this command is issued */
    vcommandSetFunctionIssue (functionCommand, _listdemoIssueQuitCommand);/*!*/
    
    /* ...and store it in the dictionary */
    vdictStore (commandDict, TAG("Quit"),  /*!*/
		functionCommand);
    
    
    /* create the command to quit on window close... */
    functionCommand = vcommandCreateFunction ();
    
    /* Set the function to be called when this command is issued */
    vcommandSetFunctionIssue (functionCommand, _listdemoIssueQuitCommand);/*!*/
    
    /* ...and store it in the dictionary */
    vdictStore (commandDict, TAG("Close"),  /*!*/
		functionCommand);
    
    
    /* create the life command... */
    functionCommand = vcommandCreateFunction ();
    
    /* Set the function to be called when this command is issued */
    vcommandSetFunctionIssue (functionCommand, _listdemoIssueLifeCommand);/*!*/
    
    /* ...and store it in the dictionary */
    vdictStore (commandDict, TAG("Life"), /*!*/
		functionCommand);
    
#if (NOT_YET_IMPLEMENTED)
    /* create the stock list command... */
    functionCommand = vcommandCreateFunction ();
    
    /* Set the function to be called when this command is issued */
    vcommandSetFunctionIssue (functionCommand, 
			      _listdemoIssueStocklistCommand); /*!*/
    
    /* ...and store it in the dictionary */
    vdictStore (commandDict, TAG("Stocklist"), /*!*/
		functionCommand);
#endif
    

#if (NOT_YET_IMPLEMENTED)
    /* create the outline command... */
    functionCommand = vcommandCreateFunction ();
    
    /* Set the function to be called when this command is issued */
    vcommandSetFunctionIssue (functionCommand, 
			      _listdemoIssueOutlineCommand); /*!*/
    
    /* ...and store it in the dictionary */
    vdictStore (commandDict, TAG("CONTROL_PANEL_OUTLINE"), /*!*/
		functionCommand);
#endif
    
    
    /* create the about command... */
    functionCommand = vcommandCreateFunction ();
    
    /* Set the function to be called when this command is issued */
    vcommandSetFunctionIssue (functionCommand, 
			      _listdemoIssueAboutCommand); /*!*/
    
    /* ...and store it in the dictionary */
    vdictStore (commandDict, TAG("About"), /*!*/
		functionCommand);
    

#if (NOT_YET_IMPLEMENTED)
    /* create the spreadsheet command... */
    functionCommand = vcommandCreateFunction ();
    
    /* Set the function to be called when this command is issued */
    vcommandSetFunctionIssue (functionCommand, 
			      _listdemoIssueSpreadsheetCommand); /*!*/
    
    /* ...and store it in the dictionary */
    vdictStore (commandDict, TAG("Spreadsheet"), /*!*/
		functionCommand);
#endif
    
    
    /* create the fiddler command... */
    functionCommand = vcommandCreateFunction ();
    
    /* Set the function to be called when this command is issued */
    vcommandSetFunctionIssue (functionCommand,
			      _listdemoIssueFiddlerCommand); /*!*/
    
    /* ...and store it in the dictionary */
    vdictStore (commandDict, TAG("API Fiddler"), /*!*/
		functionCommand);
    
    

    /* create the in-cell command... */
    functionCommand = vcommandCreateFunction ();
    
    /* Set the function to be called when this command is issued */
    vcommandSetFunctionIssue (functionCommand,
			      _listdemoIssueInCellCommand); /*!*/
    
    /* ...and store it in the dictionary */
    vdictStore (commandDict, TAG("In-Cell Editing"), /*!*/
		functionCommand);
    
    
    
    /* attach our command dictionary */
    vcommandAddSpaceDictOwned (commandSpace, vname_Command, 
			       commandDict);
    
    /* and attach this space to the dialog's window. */
    vwindowSetSpaceOwned (vdialogGetWindow(dialog), commandSpace);
    
} /* _listdemoSetupCommands */




/* _listdemoFetchDialog -- Gets our control panel dialog from the applicatio
 *			resource file, attaches a command space, and does
 *			any necessary random magic.
 *  -> resource -- the resource dictionary that our dialog lives in
 * <-		-- the dialog ready for action
 */
static vdialog *_listdemoFetchDialog (vresource resource)
{
    vresource	 dialogres;
    vdialog	*dialog;
    
    /* get the resource handle for the control panel dialog */
    dialogres = vresourceGet (resource,
			      TAG("Control Panel Dialog"));
    
    /* create an object instance */
    dialog = vdialogLoad (dialogres);
    
    /* attach command space */
    _listdemoSetupCommands (dialog);
    
    return (dialog);
    
} /* _listdemoFetchDialog */




/* _listdemoFinalMopup -- cycles over all undestroyed windows and destroys
 *			  them.  This allows clients to be sloppy with
 * 			  window handling, and not be messy
 *
 * If you look in main, this function is vclientRegisterShutdown'd instead
 * of called at the end of time.  The reason for this is that this code
 * needs to be called *after* all other shutdown procs used in listdemo
 * have been run.  Why do we have to do this?  Imagine this scenario:
 *
 * listlife registers its shutdown proc to iterate over its windows and
 *    destroy the life-related petri dish structures.
 * _listdemoFinalMopup is called after veventProcess, which dutifully destroys
 *    all undestroyed windows, including the life windows
 * listlife's shutdown proc gets called, and crashes trying to destroy windows
 *   already destroyed.
 */
static void _listdemoFinalMopup (void)
{
    vwindowIterator iterator;
    vwindow *window;

    vwindowInitIterator (&iterator);

    while (vwindowNextIterator(&iterator)) {
	window = vwindowGetIteratorWindow (&iterator);
	/* vwindowRoot is in the iteration path.  Don't destroy it */
	if (window != vwindowGetRoot ()) {
	    vdebugWarn ("listdemo info: auto-destroyed window with "
			"tag \"%s\"\n",
			vwindowGetTag(window));
	    vwindowDestroy (window);
	}
    }

    vwindowDestroyIterator (&iterator);

} /* _listdemoFinalMopup */




/* main -- top dog, big cheese, head dude, righteous controller of everything.
 *
 *  -> argc	-- count o' command line arguments
 *  -> argv	-- vector o' strings of the command line arguments
 * <-		-- some kind of status.
 */
int main (int argc, char *argv[])
{
    vresource    appres;
    vdialog	*listdemoDialog;

    /* rather than calling vstartup(), which pulls in everything, including
     * domains, rulerItems, and other stuff we don't use, we do 
     * vprefSetArgs, then startup the class for each fo the dialog items
     * we're going to load from a resource.
     */
    vprefSetArgs (argc, argv);

    /* start up the world (start up the children...) */
    (void)vwindowGetDefaultClass ();
    (void)vlistviewGetDefaultClass ();
    (void)vlistitemGetDefaultClass ();
    (void)vbuttonGetDefaultClass ();
    (void)vmenubarGetDefaultClass ();
    (void)vmenuGetDefaultClass ();
    (void)vmenuGetDefaultItemClass ();
    (void)vtextitemGetDefaultClass ();
    (void)vsliderGetScrollBarClass ();
    (void)vdialogGetDefaultClass ();

    /* !!! remove when colorchooser works right */
    (void) vcontrolGetOptionMenuClass ();
    (void) vcontrolGetToggleClass ();

    /* find our appliaction resources */
    appres = vapplicationGetResources (vapplicationGetCurrent());

    /* get the dialog, and attach a command space to it */
    listdemoDialog = _listdemoFetchDialog (appres);

    /* Center it on the screen */
    vwindowPlace (vdialogGetWindow (listdemoDialog),
		  vwindowGetRoot(), vrectPLACE_CENTER, vrectPLACE_CENTER);

    /* show it */
    vdialogOpen (listdemoDialog);

    /* prep destruction of stray windows that might have been created */
    /* see comment in _listdemoFinalMopup */
    vclientRegisterShutdown (_listdemoFinalMopup);

    /* do the Real Work of the application */
    veventProcess ();
    
    /* NUKE! NUKE! OK! */
    vdialogDestroy (listdemoDialog);

    exit (EXIT_SUCCESS);
    return (EXIT_FAILURE);
    
} /* main bites dog */




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

/* $Id: filechs1.c,v 1.5 1996/08/21 15:43:55 david Exp $
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
 * copyright notice in the in the form of "Copyright 1992 Visix Software Inc.,
 * 11440 Commerce Park Drive, Reston, VA  22091. All Rights Reserved" appears
 * in all copies, (ii) both the copyright notice and this permission notice
 * appear in supporting documentation and (iii) you are a valid licensee of
 * Galaxy Application Environment.
 */

/******************************************************************************
 *
 *       vfilechsr Demo #1
 *
 *       Demonstrates the use of a simple file-only chooser
 *
 *       Modification History:
 *		11-30-93:  updated for galaxy 2.0
 *
 *****************************************************************************/


#ifndef vportINCLUDED		/* for v*HEADER */
#include <vport.h>
#endif

#ifndef  vstdlibINCLUDED	/* for EXIT_SUCCESS */
#include vstdlibHEADER
#endif

#include vdebugHEADER
#include vcharHEADER
#include vnameHEADER
#include vstrHEADER
#include vrectHEADER
#include vfsHEADER
#include vresourceHEADER
#include veventHEADER
#include vapplicationHEADER
#include vmenuHEADER
#include vdialogHEADER
#include vmenubarHEADER
#include vfilechsrHEADER
#include vnoticeHEADER
#include vstartupHEADER


/*
 * Convenience macro for interning global literals
 */

#define TAG(l) vnameInternGlobalLiteral(l)


/*
 * Forward declarations for notification functions.
 */

static int ApplyFileNotify (vfilechsr *fileChooser, vfsPath *path);

void OpenNotify (vmenuItem *item, vevent *event);

void ExitNotify (vmenuItem *item, vevent *event);

void DialogCloseNotify (vdialog *dialog, vevent *event);

/*
 * Global data items
 */

vdialogItem     *label;            /* label                             */
vdialog         *mainDialog;       /* dialog containing label item      */
vfilechsr	*fileChooser = NULL;



/*
 * Function:    main
 *
 * Description: main entry point for our sample application
 *
 * Parameters:  argc - command line argument count
 *              argv - command line arguments
 *
 * Returns:     EXIT_FAILURE if something wrong
 *		EXIT_SUCCESS on normal termination
 *
 */

int main (int argc, char *argv[])
{
    vresource   resources;         /* resource pointer                  */
    vresource   dialogResource;    /* resource for dialog               */

    vmenubar    *menubar;          /* menu bar for dialog               */
    vmenu       *fileMenu;         /* File menu                         */
    vmenuItem   *openItem;         /* Open... menu item                 */
    vmenuItem   *exitItem;         /* Exit menu item                    */

    /*
     * Start up Galaxy and load in the resource file.
     */

    vstartup (argc, argv);
    resources = vapplicationGetResources (vapplicationGetCurrent ());

    /*
     * Locate and load the dialog containing the sample label.
     */

    dialogResource =  vresourceGet (resources, TAG ("TestDialog"));
    mainDialog = vdialogLoad (dialogResource);
    vdialogSetNotify (mainDialog, DialogCloseNotify);

    /*
     * Get label in dialog
     */

    label = vdialogFindItem (mainDialog,  TAG("Label1"));


    /*
     * Get menubar, File menu, setup callbacks for menu items, etc
     */

    menubar = (vmenubar *) vdialogFindItem (mainDialog, TAG("MenuBar"));

    fileMenu = vmenubarFindMenu (menubar, TAG("FileMenu"));
    openItem = vmenuFindItem (fileMenu, TAG("OpenItem"));
    exitItem = vmenuFindItem (fileMenu, TAG ("ExitItem"));

    vmenuSetItemNotify (openItem, OpenNotify);
    vmenuSetItemNotify (exitItem, ExitNotify);

    /*
     * Display the dialog containing the sample label.
     */

    vwindowPlace(vdialogGetWindow(mainDialog), vwindowGetRoot(),
		 vrectPLACE_CENTER, vrectPLACE_CENTER);
    vdialogOpen (mainDialog);

    /*
     * Process events until the window is closed or Exit
     */

    veventProcess ();

    /*
     * Clean up.
     */

    vdialogDestroy(mainDialog);
    if (fileChooser != NULL)
      vfilechsrDestroy(fileChooser);

    /*
     * Return.
     */
    exit (EXIT_SUCCESS);
    return EXIT_FAILURE;	/* should never reach */
}



/*
 * Function:    OpenNotify
 *
 * Description: Notification procedure for the Open menu item 
 *              in the File menu
 *
 * Parameters:  menuitem, the owning menu item
 *              event,    the event associated with notification
 *
 * Returns:     void
 *
 */

void OpenNotify (vmenuItem *item, vevent *event)
{
    /*
     * First time through, create the file chooser, 
     * set up notify proc, make sure user can only select existing 
     * files.
     */

    if (fileChooser == NULL) { 
        /* new chooser */
	fileChooser = vfilechsrCreate ();

	/* set the type; we want a "open" or "get" type */
	vfilechsrSetType (fileChooser, vfilechsrGET);

	/* our apply hook */
	vfilechsrSetApply (fileChooser, ApplyFileNotify);

	/* the chooser is a follower of our main window */
	vfilechsrSetLeader (fileChooser, vdialogGetWindow(mainDialog));

	/* make sure user can only select one item at a time */
	vfilechsrSetSelection (fileChooser, vfilechsrSINGLE);

	/* make sure user can only specify existing files */
	vfilechsrSetOptions (fileChooser, vfilechsrOPTION_FILE_MUST_EXIST);
    }


    /*
     * Open the chooser; if the chooser's not already open, position
     * its window wrt. the main dialog
     */

    if (!vconfirmIsOpen(vfilechsrGetConfirm(fileChooser)))
      vfilechsrPlace(fileChooser,  mainDialog, 
		     vrectPLACE_CENTER, vrectPLACE_CENTER);

    vfilechsrOpen (fileChooser);
}




/*
 * Function:    ApplyFileNotify

 * Description: Notification procedure for filechooser for Apply/OK
 *              Checks the path returned, does something with it,
 *              and let the file chooser close.
 *              Else, do nothing and let filechooser keep going.
 *
 * Parameters:  chooser, the owning file chooser
 *              path, the path choosen by the user (never a directory)
 *
 * Returns:     TRUE    File choosen was ok - go ahead and let the chooser 
 *              	go away if confirm button was selected.
 *      	FALSE   Don't close chooser - file wasn't acceptable
 *
 */
static int ApplyFileNotify (vfilechsr *fileChooser, vfsPath *path)
{
    vfsInfo             info;
    vstr		*volatile pathname;
    int			volatile canClose;

    /*
     * Default is something's wrong. Don't close
     */
    canClose = FALSE;
    pathname = NULL;


    /*
     * Set label in dialog to the full pathname of the user's
     * choice. Typically, you would open the file here with something 
     * like: file = vfsOpenFile (path, vfsOPEN_READ_ONLY).
     */
    vexWITH_HANDLING
      {
	vfsGetFileInfo (path, &info);

	pathname = vfsPathToStr(path);
	vdialogSetItemTitle(label, pathname);
	vstrDestroy(pathname);

	/*
	 * Ok to close file chooser
	 */
	canClose = TRUE;
      }

    /*
     * Something's wrong; probably cannot access the file
     */
    vexON_EXCEPTION
      {
	register vnotice *notice;

	/* make sure we clean this up */
	if (pathname)
	  vstrDestroy(pathname);

	/* tell the user's somethings wrong */
	notice = vnoticeCreate();
	vnoticeSetTextScribed
	  (notice, vcharScribeLiteral("Can't process file..."));
	(void)vnoticeProcess(notice);
	vnoticeDestroy(notice);

	/* we've handled the exception */
	vdebugBE(vexDumpChain(vdebugGetWarningStream()));
      }
    vexEND_HANDLING;

    /*
     * result
     */
    return canClose;
}



/*
 * Function:    ExitNotify
 *
 * Description: Notification procedure for Exit button
 *
 * Parameters:  menuitem, the exit menu item
 *		event, the triggering event for the menuitem
 *
 * Returns:     void
 *
 */
void ExitNotify (vmenuItem *item, vevent *event)
{
    veventStopProcessing ();
}




/*
 * Function:    DialogNotify
 *
 * Description: Notification procedure for main dialog.
 *              Called when it gets a message. Only  pays attention to 
 *		close messages. Everything else is ignored.
 *
 * Parameters:  dialog, our main dialog
 *		event, the triggering event
 *
 * Returns:     void
 *
 */
void DialogCloseNotify (vdialog *dialog, vevent *event)
{
    if (veventIsClose(event))
      veventStopProcessing ();
}

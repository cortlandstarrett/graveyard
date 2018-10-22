/* $Id: app.c,v 1.8 1995/07/12 19:22:45 lis Exp $
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

#ifndef  vportINCLUDED		/* for v*HEADER */
#include <vport.h>
#endif

#ifndef  vstdlibINCLUDED	/* for exit, EXIT_SUCCESS */
#include vstdlibHEADER
#endif

#ifndef  vresourceINCLUDED
#include vresourceHEADER
#endif

#ifndef  vobjectINCLUDED
#include vobjectHEADER
#endif

#ifndef  vwindowINCLUDED
#include vwindowHEADER
#endif

#ifndef  vdialogINCLUDED
#include vdialogHEADER
#endif

#ifndef  vstartupINCLUDED
#include vstartupHEADER
#endif

#ifndef  vapplicationINCLUDED
#include vapplicationHEADER
#endif

#ifndef  vmenubarINCLUDED
#include vmenubarHEADER
#endif

#ifndef  vmenuINCLUDED
#include vmenuHEADER
#endif

#include "splash.h"


/****************************************************************************
 * executable:    appWithSplash
 * .c files:      anApp.c, splash.c
 * header file:   splash.h
 * resource file: appWithSplash.vr
 *
 * managers illustrated: Event Manager
 *
 * This program illustrates how to implement a splash dialog for any
 * Galaxy application. The splash dialog must be opened before we have
 * entered the main event loop, so we must post our own events for it.
 * This program also illustrates how to associate application code with
 * menu items using notify functions.
 *
 * This demo consists of a splash dialog which apperas immediately and
 * stays up until all application initialization is finished. Then, the
 * splash dialog closes and an application dialog appears.
 *
 * To end the demo, choose "Quit" from the File menu of the application
 * dialog.
 *
 ****************************************************************************/



/*******************************************************************/
/*                  Private functions                              */
/*******************************************************************/

/*********
 * quitNotify()
 *
 * The notification function for the Quit menu item.
 * This function is called when the user chooses Quit from our
 * application dialog's File menu.
 *
 **********/
static void quitNotify(vmenuItem *quitItem, vevent *event)
{
    vwindow  *theDialogsWindow;

    theDialogsWindow = vwindowGetLeader(vmenuDetermineItemWindow(quitItem));
    vwindowClose(theDialogsWindow);
    vwindowDestroyLater(theDialogsWindow);

    /* Stop the event loop. control returns to main() */
    veventStopProcessing();
}


/* handleDialog -- the callback function for the main dialog
 *			This stops processing, and we
 *			fall through the other side of the veventProcess ();
 *
 *  -> dialog	-- the dialog that was notified.
 *  -> event	-- the event that triggered it.
 */
static void handleDialog (vdialog *dialog, vevent *event)
{
    if (veventIsClose (event)) {
	vwindowDestroyLater(vdialogGetWindow(dialog));
	veventStopProcessing ();
    }
} /* _sampleHandleDialog */



/*******************************************************************/
/*                  Public functions                              */
/*******************************************************************/

/*********
 * appDialog1Create()
 *
 * Create an application dialog. This is just a trivial dialog set up in
 * the resource file. It doesn't do anything except represent an application
 * window.
 *********/
vdialog *appDialog1Create()
{
    vdialog   *theApp1Dialog;
    vmenubar  *menubarItem;
    vmenu     *fileMenu;
    vmenuItem *QuitMenuItem;

    vresource res =
	vresourceGet(vapplicationGetResources(vapplicationGetCurrent()),
		     vnameInternGlobalLiteral("nameAPP1_DIALOG"));
    theApp1Dialog = vdialogLoad(res);

    /*
     * Hook up a notify function for the Quit menu item to allow the user
     * to cleanly quit out of the application.
     */
    menubarItem = (vmenubar *)vdialogFindItem(theApp1Dialog, 
				vnameInternGlobalLiteral("nameAPP_MENBAR"));
    fileMenu = vmenubarFindMenu(menubarItem,
				vnameInternGlobalLiteral("nameAPP_FILEMENU"));
    QuitMenuItem = vmenuFindItem(fileMenu,
				vnameInternGlobalLiteral("nameFILEMENU_QUIT"));
    vmenuSetItemNotify(QuitMenuItem, quitNotify);

    vdialogSetNotify(theApp1Dialog, handleDialog);

    return(theApp1Dialog);
}



/*********
 * initProc()
 *
 * Application initialization code. We get called from the splash dialog
 * handler. The splash dialog remains up while this initialization is going
 * on. We explicitly close the splash dialog when the initialization is
 * finished.
 **********/
static void initProc (vdialog *splashDialog)
{
    vdialog  *appDialog1;
    int	    i;
    vstr	   *s;

    /*
     * Initialize the application here while the splash dialog is up.
     *
     */

    /*
     * Simulate application startup activity -- 
     * Note - this loop is here because we want the splash dialog
     * to be up long enough for you to see it! Normally, you wouldn't even
     * use a splash dialog if you didn't have long initialization to do,
     * but this is just a demo.
     */
    for (i=0; i<5000; i++)
    {
	/* do useless stuff that takes time */
	s = vstrCreateSized(1000);
	(void)vmemSet(s, 0, 1000*sizeof(vchar));
	vstrDestroy(s);
    }

    appDialog1 = appDialog1Create();
    vdialogOpen(appDialog1);

    if (splashDialog)
    {
	vdialogClose(splashDialog);
	vdialogDestroy(splashDialog);
    }
}



/*********
 * main()
 *
 * Main program for our demo that illustrates use and
 * implementation of a splash dialog. Since this is a demo, the 
 * application that the splash dialog introduces is trivial.
 *
 **********/
int main(int argc, char *argv[])
{
    vdialog  *splashDialog;

    vstartup(argc, argv);

    splashDialog = splashdialogCreate();
    if (splashDialog != NULL)
	splash(splashDialog, initProc);
    else
	initProc(NULL);

    veventProcess();

    exit(EXIT_SUCCESS);
    return EXIT_FAILURE;
}


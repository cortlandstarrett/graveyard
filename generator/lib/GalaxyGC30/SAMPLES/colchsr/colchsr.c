/* $Id: colchsr.c,v 1.4 1996/03/27 17:30:10 stevek Exp $
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
 *       vcolorchsr Demo
 *
 *       Demonstrates the use of a simple color chooser
 *
 *       Modification History:
 *		12-01-93:  updated for galaxy 2.0
 *
 *****************************************************************************/

#ifndef  vportINCLUDED		/* for v*HEADER */
#include <vport.h>
#endif

#ifndef  vstdlibINCLUDED	/* for EXIT_SUCCESS */
#include vstdlibHEADER
#endif

#include vdebugHEADER
#include vcharHEADER
#include vnameHEADER
#include vresourceHEADER
#include veventHEADER
#include vcolorHEADER
#include vapplicationHEADER
#include vmenuHEADER
#include vdialogHEADER
#include vmenubarHEADER
#include vconfirmHEADER
#include vcolorchsrHEADER
#include vstartupHEADER
#include vtestHEADER


/*
 * Convenience macro for interning global literals
 */

#define TAG(l) vnameInternGlobalLiteral(l)


/*
 * Forward declarations for notification functions.
 */

static void ApplyColorNotify (vcolorchsr *colorChooser, vcolor *color);

static void ColorNotify (vmenuItem *item, vevent *event);

static void ExitNotify (vmenuItem *item, vevent *event);

static void DialogNotify(vdialog *dialog, vevent *event);


/*
 * Global data structures
 */

vcolor		*lastColor;	   /* last color selected          */
vdialogItem	*paintchip;	   /* paintchip                    */
vdialog		*mainDialog;   	   /* dialog containing paint chip */
vcolorchsr	*colorChooser=NULL;/* our global color chooser     */




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
    vresource	resources;	   /* resource pointer		   */
    vresource	dialogResource;	   /* resource for dialog   	   */

    vmenubar	*menubar;	   /* menu bar for dialog          */
    vmenu	*filemenu;	   /* File menu                    */
    vmenuItem	*coloritem;	   /* Set Color... menu item       */
    vmenuItem   *exititem;	   /* Exit menu item               */

    /*
     * Start up Galaxy
     */

    vstartup (argc, argv);

    /*
     * Connect to any running testing tools
     */
    vtestStartup();

    /*
     * Load in the resource file
     */
    resources = vapplicationGetResources (vapplicationGetCurrent ());


    /*
     * Locate and load the dialog containing the paint chip.
     */

    dialogResource = vresourceGet(resources, TAG("TestDialog"));
    mainDialog = vdialogLoad (dialogResource);
    vdialogSetNotify(mainDialog, DialogNotify);


    /*
     * Get "paintchip" dialog item in main dialog; initialize our
     * lastColor global
     */

    paintchip = vdialogFindItem (mainDialog, TAG("PaintChip"));
    lastColor = vdialogDetermineItemBackground (paintchip);


    /*
     * Get menubar, File menu, setup notify procs for menu items, etc
     */

    menubar = (vmenubar *) vdialogFindItem (mainDialog, TAG("MenuBar"));

    filemenu = vmenubarFindMenu (menubar, TAG("FileMenu"));

    coloritem = vmenuFindItem (filemenu, TAG("ColorItem"));

    exititem = vmenuFindItem (filemenu, TAG("ExitItem"));

    vmenuSetItemNotify (coloritem, ColorNotify);
    vmenuSetItemNotify (exititem, ExitNotify);


    /*
     * Display the dialog containing the paint chip.
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

    vdialogDestroy (mainDialog);
    if (colorChooser != NULL)
      vcolorchsrDestroy(colorChooser);


    /*
     * Return.
     */
    exit (EXIT_SUCCESS);
    return (EXIT_FAILURE);	/* should never reach */
}




/*
 * Function:	ColorNotify
 *
 * Description:	Notification procedure for the Set Color menu item 
 *		in the File menu
 *
 * Parameters:	menuitem, the affected menuitem
 *		event,    the triggering event for notification
 *
 * Returns:	void
 */
static void ColorNotify (vmenuItem *item, vevent *event)
{
    /*
     * If it's the first time through, create the color chooser,
     * and set up notify proc
     */

    if (colorChooser == NULL) {
        /* new color chooser */
	colorChooser = vcolorchsrCreate ();

	/* our apply hook */
	vcolorchsrSetApply(colorChooser, ApplyColorNotify);

	/* set the initial color to the paintchips's orig background */
	vcolorchsrSetColor(colorChooser, lastColor);

	/* the chooser is a follower of our main window */
	vcolorchsrSetLeader(colorChooser, vdialogGetWindow(mainDialog));

	/* initially position wrt. the main dialog */
      vcolorchsrPlace(colorChooser,  mainDialog, 
		      vrectPLACE_HALF|vrectPLACE_RIGHT, 
		      vrectPLACE_INSET|vrectPLACE_TOP);
    }


    /*
     * Open the color chooser's dialog window
     */

    vcolorchsrOpen(colorChooser);
}




/*
 * Function:	ApplyColorNotify
 *
 * Description:	Notification procedure for colorchooser for Apply/OK
 *		Set the background color of the 'paintchip' to
 *		selected color and update our lastColor global.
 *
 * Parameters:	chooser, the owning color chooser
 *		color,   the color selected by user
 *
 * Returns:	void
 *
 */
static void ApplyColorNotify (vcolorchsr *colorChooser, vcolor *color)
{
    vdialogSetItemBackground(paintchip, color);
    lastColor = color;
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
static void ExitNotify (vmenuItem *item, vevent *event)
{
    veventStopProcessing();
}




/*
 * Function:    DialogNotify
 *
 * Description: Notification procedure for main dialog.
 *              Called when it gets a message. Only  pays attention to 
 *		close messages. Everything else is ignored.
 *
 * Parameters:  dialog, our main dialog
 *		event,  the triggering event
 *
 * Returns:     void
 *
 */
static void DialogNotify (vdialog *dialog, vevent *event)
{
    if (veventIsClose(event))
	veventStopProcessing ();
}

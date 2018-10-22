/* $Id: fontchsr.c,v 1.4 1994/07/16 17:11:37 chad Exp $
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
 *       vfontchsr Demo
 *
 *       Demonstrates the use of a simple font chooser
 *
 *       Modification History:
 *		12-01-93:  updated for galaxy 2.0
 *
 ******************************************************************************/

#ifndef vportINCLUDED		/* for v*HEADER */
#include <vport.h>
#endif

#ifndef  vstdlibINCLUDED	/* for EXIT_SUCCESS */
#include vstdlibHEADER
#endif

#include vdebugHEADER
#include vscribeHEADER
#include vcharHEADER
#include vnameHEADER
#include vresourceHEADER
#include veventHEADER
#include vfontHEADER
#include vapplicationHEADER
#include vmenuHEADER
#include vdialogHEADER
#include vmenubarHEADER
#include vconfirmHEADER
#include vnumHEADER
#include vfontchsrHEADER
#include vstartupHEADER

/*
 * Convenience macro for interning global literals
 */

#define TAG(l) vnameInternGlobalLiteral(l)



/*
 * Forward declarations for notification functions.
 */

static int ApplyFontNotify(vfontchsr *fontChooser, vfont *font);

static void DialogNotify(vdialog *dialog, vevent *event);

static void ExitNotify(vmenuItem *item, vevent *event);

static void ShowNotify(vmenuItem *item, vevent *event);




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

int main (int argc, char **argv)
{
    vresource   resources;         /* resource pointer              */
    vresource   dialogResource;    /* resource for dialogw/label    */

    vdialog     *labelDialog;      /* dialog containing label item  */

    vdialogItem *label;            /* label to set font on          */

    vfontchsr   *chooser;          /* font chooser to create        */

    vmenuItem   *showItem;         /* show item on menu             */

    vmenuItem   *exitItem;         /* exit item on menu             */

    vmenu       *menu;             /* menu containing above item    */

    vmenubar    *menuBar;          /* menu bar for above menu       */

    /*
     * Start up Galaxy and load in the resource file.
     */

    vstartup (argc, argv);
    resources = vapplicationGetResources (vapplicationGetCurrent ());


    /*
     * Locate and load the dialog containing the sample label.
     */

    dialogResource = vresourceGet (resources, TAG("TestDialog"));
    labelDialog = vdialogLoad (dialogResource);
    vdialogSetNotify (labelDialog, DialogNotify);
    label = vdialogFindItem (labelDialog, TAG("Label1"));


    /*
     * Set up the main dialog's menu handling.
     */

    menuBar = (vmenubar *) vdialogFindItem (labelDialog, TAG("MenuBar"));

    menu = vmenubarFindMenu (menuBar, TAG("FileMenu"));

    showItem = vmenuFindItem (menu, TAG("ShowItem"));

    exitItem = vmenuFindItem (menu, TAG("ExitItem"));

    vmenuSetItemNotify (showItem, ShowNotify);
    vmenuSetItemNotify (exitItem, ExitNotify);



    /*
     * Create a font chooser, and set its data pointer to be
     * the label whose font we want to change.  Set the label item's
     * data field to contain the chooser's reference so we can 
     * access the chooser later.
     */

    /* create the chooser */
    chooser = vfontchsrCreate ();
    vmenuSetItemData (showItem, chooser);
    vfontchsrSetData (chooser, label);

    /* chooser's apply hook */
    vfontchsrSetApply (chooser, ApplyFontNotify);

    /* the chooser is a follower of our main dialog */
    vwindowSetLeader(vdialogGetWindow(vfontchsrGetDialog(chooser)),
		     vdialogGetWindow(labelDialog));


    /*
     * Display the main dialog containing the sample label and
     * our font chooser.
     */

    vwindowPlace(vdialogGetWindow(labelDialog), vwindowGetRoot(),
		 vrectPLACE_CENTER, vrectPLACE_CENTER);

    vdialogOpen (labelDialog);

    vwindowPlace(vdialogGetWindow(vfontchsrGetDialog(chooser)),
		 vdialogGetWindow(labelDialog), 
		 vrectPLACE_HALF|vrectPLACE_RIGHT,
		 vrectPLACE_INSET|vrectPLACE_TOP);

    vfontchsrOpen(chooser);



    /*
     * Process events till the window is closed.
     */

    veventProcess ();


    /*
     * Clean up.
     */

    vfontchsrDestroy (chooser);
    vdialogDestroy (labelDialog);


    /*
     * Return.
     */
    exit (EXIT_SUCCESS);
    return (EXIT_FAILURE); /* should never reach */
}




/*
 * Function:    ApplyFontNotify
 *
 * Description: Apply the new font to the label item.
 *
 * Parameters:  chooser, the owning font chooser
 *		font,    the font selected by the user
 *
 * Returns:     void
 */
static int ApplyFontNotify (vfontchsr *fontChooser, vfont *font)
{
    vdialogItem         *label;  /* label to update */
    vfontFace		*face;
    vscribe		*scribe;

    label = (vdialogItem *) vfontchsrGetData (fontChooser);

    /*
     * Create a title like: "Family: Courier, Face: Bold, Size: 12pt"
     */
    face = vfontGetFace(font);

    scribe = vscribeScribeMulti
      (vcharScribeLiteral("Family: "),
       vnameScribeGlobal(vfontGetFamilyName(vfontGetFaceFamily(face))),
       vcharScribeLiteral(", Face: "),
       vnameScribeGlobal(vfontGetFaceName(face)),
       vcharScribeLiteral(", Size: "),
       vnumScribeInt(vfontGetSize(font)),
       vcharScribeLiteral("pt"),
       NULL
       );

    /*
     * Update the item's font and title
     */
    vdialogSetItemFont (label, font);
    vdialogSetItemTitleScribed (label, scribe); /* destroys scribe */

    return (TRUE);
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
    if (veventIsClose (event))
        veventStopProcessing();
}





/*
 * Function:    ShowNotify
 *
 * Description: Show the font chooser dialog.  If it is already open, make
 *		sure that it's visible.
 *
 * Parameters:  menuitem, the menuitem
 *		event,    the event 
 *
 * Returns:     void
 *
 */
void ShowNotify (vmenuItem *item, vevent *event)
{
    vfontchsr   *chooser;

    chooser = (vfontchsr *)vmenuGetItemData(item);

    if (vdialogIsOpen (vfontchsrGetDialog(chooser))) {
        vwindowUniconify(vdialogGetWindow(vfontchsrGetDialog(chooser)));
        vwindowRaise(vdialogGetWindow(vfontchsrGetDialog(chooser)));
    }
    else
      vfontchsrOpen(chooser);
}





/*
 * Function:    ExitNotify
 *
 * Description: Notification procedure for Exit menu item
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


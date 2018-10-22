/*
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
 *
 * tut3c.c
 *
 * Our final 'Hello Galaxy'.
 *
 * We will:
 * -  Create a dialog
 * -  Set the dialog's size
 * -  Attach a notify function
 * -  Create a label item
 * -  Add a title to it
 * -  Set it's position
 * -  Open the dialog
 * -  Enter the event loop
 * -  Destroy the dialog.
 *
 */

#include <vport.h> /* for v*HEADER */

/* ANSI headers */
#include vstdlibHEADER	/* for exit(), EXIT_ codes */

/* Galaxy headers */
#include vrectHEADER
#include vcharHEADER
#include veventHEADER
#include vwindowHEADER
#include vdialogHEADER
#include vstartupHEADER

/* forward references */
static void dialogNoteProc (vdialog *dialog, vevent *event);

int main (int argc, char **argv)

{

  vdialog     *dialog;
  vdialogItem *item;
  vrect        rect;

  /* Initialize Galaxy */
  vstartup (argc, argv);

  /* Create the dialog */
  dialog = vdialogCreate ();

  /* Position it relative to the root window */
  rect.x = 200;
  rect.y = 200;
  rect.w = 300;
  rect.h = 200;
  vwindowSetRect (vdialogGetWindow (dialog), &rect);

  /* Set the notify function */
  vdialogSetNotify (dialog, dialogNoteProc);

  /* Create a dialog item */
  item = vdialogCreateLabelItem ();
  
  /* Add a title to it */
  vdialogSetItemTitleScribed (
    item, 
    vcharScribeLiteral ("Hello Galaxy!")
  );

  /* Position it relative to the dialog */
  rect.x = 120;
  rect.y = 90;
  rect.w = 120;
  rect.h = 15;
  vdialogSetItemRect (item, &rect);

  /* Add the item to the dialog */
  vdialogAppendItem (dialog, item);

  /* Open the dialog */
  vdialogOpen (dialog);

  /* Enter the event loop */
  veventProcess ();

  /* Return the dialog's resources to the system */
  vdialogDestroy (dialog);

  exit (EXIT_SUCCESS);
  return EXIT_FAILURE;

}

/*
 *  dialogNoteProc
 *
 *  The dialog notification procedure gets called whenever any 
 *  major event applies to the dialog as a whole.  We need to
 *  look for the event which tells us that the dialog has
 *  closed.
 *
 */

static void dialogNoteProc (vdialog *dialog, vevent *event)

{

  int et;

  et = veventGetType (event);
  
  if (et == veventWINDOW_STATE && veventIsClose (event))
    veventStopProcessing ();

}

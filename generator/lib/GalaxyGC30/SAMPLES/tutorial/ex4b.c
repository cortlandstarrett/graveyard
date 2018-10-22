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
 * ex4b.c
 *
 * "The Three Buttons Live Together"
 *
 */

#include <vport.h> /* for v*HEADER */

/* ANSI headers */
#include vstdlibHEADER	/* for exit(), EXIT_ codes */

/* Galaxy headers */
#include vrectHEADER
#include vcharHEADER
#include vnameHEADER
#include veventHEADER
#include vwindowHEADER
#include vdialogHEADER
#include vbuttonHEADER
#include vstartupHEADER

/* forward references */
static void shutdownMain (void);
static void dialogNoteProc (vdialog *dialog, vevent *event);
static void buttonNoteProc (vbutton *button, vevent *event);
static void placeButtons (vdialog *dialog);

/* Global names */
static const vname *name_GrowButton   = NULL;
static const vname *name_ShrinkButton = NULL;
static const vname *name_QuitButton   = NULL;

/* Constatns */
#define GROW_AMOUNT          50

int main (int argc, char **argv)

{

  vdialog     *dialog;
  vbutton     *button;

  /* Initialize Galaxy */
  vstartup (argc, argv);

  /*
   * Create and set the dialog up.
   *
   */

  dialog = vdialogCreate ();
  vdialogSetNotify (dialog, dialogNoteProc);

  vdialogMove (dialog, 200, 200);
  vdialogResize (dialog, 100, 100);

  /*
   * Create and initialize the buttons
   *
   */

  /* Create 'grow' button */
  button = vbuttonCreate ();

  /* Add a notify function */
  vbuttonSetNotify (button, buttonNoteProc);
  
  /* Add a title to it */
  vbuttonSetTitleScribed (
    button, 
    vcharScribeLiteral ("Grow")
  );

  /* Add a tag to it */
  name_GrowButton = vnameInternGlobalLiteral ("grow");
  vdialogSetItemTag (vbuttonGetItem (button), name_GrowButton);

  /* Add the item to the dialog */
  vdialogAppendItem (dialog, vbuttonGetItem (button));

  /*
   *  Now the shrink button
   *  It's the same exact method as before
   *
   */

  button = vbuttonCreate ();
  vbuttonSetNotify (button, buttonNoteProc);
  vbuttonSetTitleScribed (
    button, 
    vcharScribeLiteral ("Shrink")
  );

  name_ShrinkButton = vnameInternGlobalLiteral ("shrink");
  vdialogSetItemTag (vbuttonGetItem (button), name_ShrinkButton);
  vdialogAppendItem (dialog, vbuttonGetItem (button));

  /* And again for the quit button */

  button = vbuttonCreate ();
  vbuttonSetNotify (button, buttonNoteProc);
  vbuttonSetTitleScribed (
    button, 
    vcharScribeLiteral ("Quit")
  );

  name_QuitButton = vnameInternGlobalLiteral ("quit");
  vdialogSetItemTag (vbuttonGetItem (button), name_QuitButton);
  vdialogAppendItem (dialog, vbuttonGetItem (button));

  /* Arrange the buttons */
  placeButtons (dialog);

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
 *  shutdownMain
 *
 *  Stop things
 *
 */

static void shutdownMain ()

{

  veventStopProcessing ();

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

  int      et;

  et = veventGetType (event);
  
  if (et == veventWINDOW_STATE &&veventIsClose (event))
    shutdownMain ();
  else if (et == veventWINDOW_CONFIGURE && veventIsSize (event))
    placeButtons (dialog);

}

/*
 *  placeButtons
 *
 *  Arrange the buttons in the dialog rect so that
 *  grow is in top left, quit is centered, and 
 *  shrink is in the botton right.
 *
 */

static void placeButtons (vdialog *dialog)

{

  vbutton *button;

        vrect    buttonRect;
  const vrect   *dialogRect;

  /* get the dialog's rect, we'll use it later */
  dialogRect = vwindowGetRect (vdialogGetWindow (dialog));

  /*
   * Now let's arrange the grow button
   *
   */

  /* Find the buttons */
  button = (vbutton *) 
	vdialogFindItem (dialog, name_GrowButton);

  /* Get a copy of its rect */
  buttonRect = 
	*vdialogGetItemRect (vbuttonGetItem (button));

  /* move the grow button to top left */
  buttonRect.x = 0;
  buttonRect.y = dialogRect->h - buttonRect.h;
  vdialogSetItemRect (vbuttonGetItem (button), &buttonRect);

 /*
  * Now put shrink in the lower right
  *
  */

  button = (vbutton *) 
	vdialogFindItem (dialog, name_ShrinkButton);
  buttonRect = *vdialogGetItemRect (vbuttonGetItem (button));

  buttonRect.x = dialogRect->w - buttonRect.w;
  buttonRect.y = 0;
  vdialogSetItemRect (vbuttonGetItem (button), &buttonRect);

 /*
  * And put quit in the center
  *
  */

  button = (vbutton *) 
	vdialogFindItem (dialog, name_QuitButton);
  buttonRect = *vdialogGetItemRect (vbuttonGetItem (button));

  buttonRect.x = (dialogRect->w - buttonRect.w) / 2;
  buttonRect.y = (dialogRect->h - buttonRect.h) / 2;
  vdialogSetItemRect (vbuttonGetItem (button), &buttonRect);

}

/*
 *  buttonNoteProc
 *
 *  Take the appropriate action for the button we get. This isn't usually
 *  something you want to do since your checking for which button is extra
 *  overhead that separate notify functions avoid, but sometimes it is
 *  appropriate for your program.
 *
 */

static void buttonNoteProc (vbutton *button, vevent *event)

{

  const vname *tag;

  vdialog *dialog;
  vwindow *window;
  vrect    rect;

  tag = vdialogGetItemTag (vbuttonGetItem (button));

  if (tag == name_QuitButton)
    shutdownMain ();
  else if (tag == name_GrowButton) {
    dialog =  vdialogDetermineItemDialog (vbuttonGetItem (button));
    window =  vdialogGetWindow (dialog);
    rect   = *vwindowGetRect (window);

    rect.w += GROW_AMOUNT;
    rect.h += GROW_AMOUNT;
    vwindowSetRect (window, &rect);

    placeButtons (dialog);
  }
  else if (tag == name_ShrinkButton) {
    dialog =  vdialogDetermineItemDialog (vbuttonGetItem (button));
    window =  vdialogGetWindow (dialog);
    rect   = *vwindowGetRect (window);

    rect.w -= GROW_AMOUNT;
    rect.h -= GROW_AMOUNT;
    vwindowSetRect (window, &rect);

    placeButtons (dialog);
  }

}

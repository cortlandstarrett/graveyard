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
 * tut7a.c
 *
 * "The Quit Button Gets Some Class"
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
#include vresourceHEADER
#include vclassHEADER
#include vfontHEADER
#include vdrawHEADER
#include vwindowHEADER
#include vmenuHEADER
#include vapplicationHEADER
#include vdialogHEADER
#include vmenubarHEADER
#include vbuttonHEADER
#include vstartupHEADER

/* forward references */
static void shutdownMain (void);
static void dialogNoteProc (vdialog *dialog, vevent *event);
static void growButtonNoteProc (vbutton *button, vevent *event);
static void shrinkButtonNoteProc (vbutton *button, vevent *event);
static void quitButtonNoteProc (vbutton *button, vevent *event);
static void growMenuItemNoteProc (vmenuItem *item, vevent *event);
static void shrinkMenuItemNoteProc (vmenuItem *item, vevent *event);
static void quitMenuItemNoteProc (vmenuItem *item, vevent *event);
static void myButtonDrawContent (vbutton *button);

/* Constants */
#define GROW_AMOUNT          50

/* Globals */
static vbuttonClass *myButtonClass;

int main (int argc, char **argv)

{

  vdialog      *dialog;
  vbutton      *button;
  vmenubar     *menubar;
  vmenu        *menu;
  vmenuItem    *mItem;
  vresource     resource;

  /* Initialize Galaxy */
  vstartup (argc, argv);

  /*
   *  Create our new button class
   *
   */

  myButtonClass = vclassReproduce (vbuttonGetDefaultClass ());
  vclassSetNameScribed (myButtonClass, vcharScribeLiteral ("boxButton"));
  vclassSet (myButtonClass, vbuttonDRAW_CONTENT, myButtonDrawContent);

  /*
   * Load the dialog from the application
   * resource file.
   *
   */

  resource = vresourceGet (vapplicationGetResources (vapplicationGetCurrent()),
			   vnameInternGlobalLiteral ("ButtonDialog"));
  dialog = vdialogLoad (resource);
  vdialogSetNotify (dialog, dialogNoteProc);

  /*
   * Find the buttons and attach their notifies.
   *
   */

  button = (vbutton *) vdialogFindItem (dialog, 
					vnameInternGlobalLiteral ("grow"));
  vbuttonSetNotify (button, growButtonNoteProc);
  
  button = (vbutton *) vdialogFindItem (dialog, 
					vnameInternGlobalLiteral ("shrink"));
  vbuttonSetNotify (button, shrinkButtonNoteProc);
  
  button = (vbutton *) vdialogFindItem (dialog, 
					vnameInternGlobalLiteral ("quit"));
  vbuttonSetNotify (button, quitButtonNoteProc);

  /*
   *  Find the menuitems and attach their notifies.
   *
   */

  menubar = (vmenubar *) vdialogFindItem (dialog,
					  vnameInternGlobalLiteral ("Menu Bar"));
  menu = vmenubarFindMenu (menubar, vnameInternGlobalLiteral ("FileMenu"));

  mItem = vmenuFindItem (menu, vnameInternGlobalLiteral ("growMenu"));
  vmenuSetItemNotify (mItem, growMenuItemNoteProc);

  mItem = vmenuFindItem (menu, vnameInternGlobalLiteral ("shrinkMenu"));
  vmenuSetItemNotify (mItem, shrinkMenuItemNoteProc);

  mItem = vmenuFindItem (menu,vnameInternGlobalLiteral ("quitMenu"));
  vmenuSetItemNotify (mItem, quitMenuItemNoteProc);

  /* Open the dialog */
  vdialogOpen (dialog);

  /* Enter the event loop */
  veventProcess ();

  /* Return the dialog's resources to the system */
  vdialogDestroy (dialog);

/*  vclassDestroy (myButtonClass); */

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
  
  if (et == veventWINDOW_STATE && veventIsClose (event))
    shutdownMain ();

}

/*
 *  quitButtonNoteProc
 *
 *  Shut things down
 *
 */

static void quitButtonNoteProc (vbutton *button, vevent *event)

{

  shutdownMain ();

}

/*
 *  growButtonNoteProc
 *
 *  Expand the window by GROW_AMOUNT.
 *
 */

static void growButtonNoteProc (vbutton *button, vevent *event)

{

  vdialog *dialog;
  vwindow *window;
  vrect    rect;

  dialog =  vdialogDetermineItemDialog (vbuttonGetItem (button));
  window =  vdialogGetWindow (dialog);
  rect   = *vwindowGetRect (window);

  rect.w += GROW_AMOUNT;
  rect.h += GROW_AMOUNT;
  vwindowSetRect (window, &rect);

}

/*
 *  shrinkButtonNoteProc
 *
 *  Shrink the window by GROW_AMOUNT
 *
 */

static void shrinkButtonNoteProc (vbutton *button, vevent *event)

{

  vdialog *dialog;
  vwindow *window;
  vrect    rect;

  dialog =  vdialogDetermineItemDialog (vbuttonGetItem (button));
  window =  vdialogGetWindow (dialog);
  rect   = *vwindowGetRect (window);

  rect.w -= GROW_AMOUNT;
  rect.h -= GROW_AMOUNT;

  vwindowSetRect (window, &rect);

}

/*
 *  quitMenuItemNoteProc
 *
 *  Shut things down
 *
 */

static void quitMenuItemNoteProc (vmenuItem *item, vevent *event)

{

  shutdownMain ();

}

/*
 *  growMenuItemNoteProc
 *
 *  Expand the window by GROW_AMOUNT.
 *
 */

static void growMenuItemNoteProc (vmenuItem *item, vevent *event)

{

  vwindow *window;
  vrect    rect;

  window = vwindowGetLeader (vmenuDetermineItemWindow (item));
  rect   = *vwindowGetRect (window);

  rect.w += GROW_AMOUNT;
  rect.h += GROW_AMOUNT;
  vwindowSetRect (window, &rect);

}

/*
 *  shrinkMenuItemNoteProc
 *
 *  Shrink the window by GROW_AMOUNT.
 *
 */

static void shrinkMenuItemNoteProc (vmenuItem *item, vevent *event)

{

  vwindow *window;
  vrect    rect;

  window = vwindowGetLeader (vmenuDetermineItemWindow (item));
  rect   = *vwindowGetRect (window);

  rect.w -= GROW_AMOUNT;
  rect.h -= GROW_AMOUNT;
  vwindowSetRect (window, &rect);

}

/*
 *  myButtonDrawContent
 *
 *  
 *
 */

static void myButtonDrawContent (vbutton *button)

{

  vdialogItem *item;
  vfont       *font;
  vrect        rect;
  vrect        rect2;

  vclassSendSuper (myButtonClass, vbuttonDRAW_CONTENT, (button));

  item = vbuttonGetItem (button);

  font = vdialogDetermineItemFont (item);
  vfontStringBounds (font, vbuttonGetTitle (button), &rect);

  rect.w += 6;
  rect.h += 6;

  vrectPlace (&rect, vdialogGetItemRect (item), 
	      vrectPLACE_CENTER, vrectPLACE_CENTER,
	      &rect2);

  vdrawRectsHiliteStroke (&rect2, 1,
      vdialogDetermineItemColor(item, vdrawCOLOR_SHADOW_BOTTOM),
      vdialogDetermineItemColor(item, vdrawCOLOR_SHADOW_TOP));

}

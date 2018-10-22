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
 * tut8a.c
 *
 * "Command Performance"
 *
 * This program demonstrates the use of the command manager. We have 
 * implemented tut7a using commands.
 *
 */

/* Galaxy headers */
#include <vgalaxy.h>

/* Application headers */
#include "command.h"

/* Command selectors */
enum {
  comGROW,
  comQUIT,
  comSHRINK
};

static commandInitializer initialCommands [] = {
  { "grow",             comGROW,              vCOMMAND('g') },
  { "quit",             comQUIT,              vCOMMAND('q') },
  { "shrink",           comSHRINK,            vCOMMAND('s') },
  { NULL }
};

/* forward references */
static void dialogNotify (vdialog *dialog, vevent *event);
static void shutdownMain (void);
static void myButtonDrawContent (vbutton *button);
static int issueFunc (vcommandSelector *command, vdict *context);

/* Constants */
#define GROW_AMOUNT          50

/* Globals */
static vbuttonClass          *myButtonClass;
static vcommandSelectorClass *selectorClass = NULL;
static vcommandSpace         *space         = NULL;


int main (int argc, char **argv)

{

  vdialog      *dialog;
  vdict        *commandDict;
  vdict        *keyDict;
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
  vdialogSetNotify (dialog, dialogNotify);

  /* Create the command space */
  space = vcommandCreateSpace ();

  /* Attach the space to the dialog */
  vwindowSetSpaceOwned (vdialogGetWindow (dialog), space);

  /* Create our selector class */
  selectorClass = vclassReproduce (vobjectGetCommandClass ());
  vclassSet (selectorClass, vcommandISSUE, issueFunc);

  /* Use the command helper function to create our command dictionary */
  commandDict = commandCreateCommandDict (initialCommands, selectorClass);

  /* Add the command dictionary to the space */
  vcommandAddSpaceDictOwned (space, vname_Command, commandDict);

  /* Use the command helper function to create our key dictionary */
  keyDict = commandCreateKeyDict (initialCommands);
  vcommandAddSpaceDictOwned (space, vname_Key, keyDict);

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
 *  dialogNotify
 *
 *  This function handles dialog events.
 *
 */

static void dialogNotify (vdialog *dialog, vevent *event)

{

  int et;

  et = veventGetType (event);
  
  if (et == veventWINDOW_STATE && veventIsClose (event))
    shutdownMain ();

  return;

}

/*
 *  issueFunc
 *
 *  Handle the commands.
 *
 */

static int issueFunc (vcommandSelector *command, vdict *context)

{

  vdialog *dialog;
  vwindow *window;
  int      selector;
  vrect    rect;

  selector = vcommandGetSelector (command);

  dialog = (vdialog *) vdictLoad (context, vname_Dialog);
  window = vdialogGetWindow (dialog);

  switch (selector) {
  case comQUIT:
    shutdownMain ();
    break;
  case comGROW:
    rect   = *vwindowGetRect (window);
    rect.w += GROW_AMOUNT;
    rect.h += GROW_AMOUNT;
    vwindowSetRect (window, &rect);
    break;
  case comSHRINK:
    rect   = *vwindowGetRect (window);
    rect.w -= GROW_AMOUNT;
    rect.h -= GROW_AMOUNT;
    vwindowSetRect (window, &rect);
    break;
  default:
    return FALSE;
  }

  return TRUE;

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

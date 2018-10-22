/* $Id: face.c,v 1.8 1994/07/16 17:11:37 chad Exp $
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
 * copyright notice in the in the form of "Copyright 1992,93 Visix Software
 *  Inc., 11440 Commerce Park Drive, Reston, VA  22091. All Rights Reserved"
 * appears in all copies, (ii) both the copyright notice and this permission
 * notice appear in supporting documentation and (iii) you are a valid
 * licensee of Galaxy Application Environment.
 */

#ifndef  vportINCLUDED		/* for v*HEADER */
#include <vport.h>
#endif

#ifndef  vstdlibINCLUDED	/* for EXIT_SUCCESS */
#include vstdlibHEADER
#endif

#ifndef  vdictINCLUDED
#include vdictHEADER
#endif

#ifndef  veventINCLUDED
#include veventHEADER
#endif

#ifndef  vapplicationINCLUDED
#include vapplicationHEADER
#endif

#ifndef  vcommandINCLUDED
#include vcommandHEADER
#endif

#ifndef  vnameINCLUDED
#include vnameHEADER
#endif

#ifndef  vresourceINCLUDED
#include vresourceHEADER
#endif

#ifndef  vdialogINCLUDED
#include vdialogHEADER
#endif

#ifndef  vstartupINCLUDED
#include vstartupHEADER
#endif

/****************************************************************************
 * executable:    face
 * .c files:      face.c
 * resource file: face.vr
 *
 * managers illustrated: Command Manager
 *                       Drawing Manager
 *                       Class   Manager
 *
 * This program illustrates how to associate application code to user 
 * interface items using selector commands (instead of notify
 * functions). It also illustrates how to do simple subclassing and how
 * to use some of the drawing manager functionality.
 *
 * This demo consists of a single dialog which contains a "Happy Face"
 * dialog item. This face item is a subclass of vdialogItem and knows
 * how to draw itself as a happy face. Different parts of the face can be
 * drawn or erased by picking from the "Face Parts" menu (menu item titles
 * change dynamically depending on whether each face part can be
 * drawn or erased. The menu items use selector commands to map to
 * application code.
 *
 * To end the demo, choose "Quit" from the File menu.
 *
 ****************************************************************************/




/*
 * Integer selectors for each of our commands. These selectors are used
 * to differentiate the commands coming into our IssueCommand() function.
 */
enum {
  FACE,
  EYES,
  NOSE,
  MOUTH,
  QUIT
  };

/*
 * The tags for each of our commands. These are the tags assigned to each
 * corresponding menu item in vre. These tags are associated with command
 * objects in the command dictionary in our application command space set
 * up in main().
 */
static const char *commandNames[] = 
{
  "commandFace",
  "commandEyes",
  "commandNose",
  "commandMouth",
  "commandQuit"
};

/*
 * Pointers to our subclasses of vcommandSelectorClass and vdialogItemClass.
 */
static vcommandSelectorClass  *_defaultSelectorClass = NULL;
static vdialogItemClass       *_defaultFaceItemClass = NULL;

/*
 * All string constants used in this demo.
 */
const vname *name_DrawFace, *name_DrawEyes, *name_DrawNose,
            *name_DrawMouth, *name_EraseFace, *name_EraseEyes,
            *name_EraseNose, *name_EraseMouth;

/*
 * Global variables to indicate current state of each face part (visible
 * or not). This state information could have been kept in the attribute
 * dictionary for the face item itself (instead of using globals), but
 * this approach would have unecessarily complicated this simple demo.
 */
static vbool gFaceIsVisible = FALSE;
static vbool gEyesAreVisible = FALSE;
static vbool gNoseIsVisible = FALSE;
static vbool gMouthIsVisible = FALSE;



/********
 * IssueCommand()
 *
 * The dispatch point for all the commands associated with the Face Parts
 * menu.
 * (This function is an override of the vcommandISSUE method defined
 * originally for the Selector class).
 *********/
static int IssueCommand(vcommandSelector *command, vdict *attr2value)
{
  vmenuItem    *theMenuItem;
  vdialog      *theDialog;
  vdialogItem  *theFaceItem;

  /*
   * Change the corresponding menu item title and global state variable
   * for the selector command issued so that the drawing function for the
   * face item can use the state variable to know how to draw the face.
   * The menu item title will reflect what can be done with each part at
   * all times.
   */
  theMenuItem = (vmenuItem *)vdictLoad(attr2value, vname_Operator);
  theDialog = (vdialog *)vdictLoad(attr2value, vname_Dialog);
  theFaceItem = (vdialogItem *)vdialogFindItem(theDialog,
				       vnameInternGlobalLiteral("FaceArea"));

  switch (vcommandGetSelector(command))
    {
    case FACE:
      if (!gFaceIsVisible)
	{
	  gFaceIsVisible = TRUE;
	  /* the face will be drawn, so now allow erasure. */
	  vmenuSetItemTitle(theMenuItem, name_EraseFace);
	}
      else
	{
	  gFaceIsVisible = FALSE;
	  /* the face will be erased, so now allow drawing. */
	  vmenuSetItemTitle(theMenuItem, name_DrawFace);
	}
      /* force the face item to be redrawn */
      vdialogInvalItem(theFaceItem, vwindowINVAL_IMMEDIATE);
      break;

    case EYES:
      if (!gEyesAreVisible)
	{
	  gEyesAreVisible = TRUE;
	  /* the eyes will be drawn, so now allow drawing. */
	  vmenuSetItemTitle(theMenuItem, name_EraseEyes);
	}
      else
	{
	  gEyesAreVisible = FALSE;
	  /* the eyes will be erased, so now allow drawing. */
	  vmenuSetItemTitle(theMenuItem, name_DrawEyes);
	}
      /* force the face item to be redrawn */
      vdialogInvalItem(theFaceItem, vwindowINVAL_IMMEDIATE);
      break;

    case NOSE:
      if (!gNoseIsVisible)
	{
	  gNoseIsVisible = TRUE;
	  /* the nose will be drawn, so now allow erasure. */
	  vmenuSetItemTitle(theMenuItem, name_EraseNose);
	}
      else
	{
	  gNoseIsVisible = FALSE;
	  /* the nose will be erased, so now allow drawing. */
	  vmenuSetItemTitle(theMenuItem, name_DrawNose);
	}
      /* force the face item to be redrawn */
      vdialogInvalItem(theFaceItem, vwindowINVAL_IMMEDIATE);
      break;

    case MOUTH:
      if (!gMouthIsVisible)
	{
	  gMouthIsVisible = TRUE;
	  /* the mouth will be drawn, so now allow erasure. */
	  vmenuSetItemTitle(theMenuItem, name_EraseMouth);
	}
      else
	{
	  gMouthIsVisible = FALSE;
	  /* the mouth will be erased, so now allow drawing. */
	  vmenuSetItemTitle(theMenuItem, name_DrawMouth);
	}
      /* force the face item to be redrawn */
      vdialogInvalItem(theFaceItem, vwindowINVAL_IMMEDIATE);
      break;

    case QUIT:
      veventStopProcessing();
      break;

    default:
      return vclassSendSuper(_defaultSelectorClass, vcommandISSUE,
			     (command, attr2value));
    }

  return TRUE;
}



/********
 * FaceItemDraw()
 *
 * The drawing procedure for the face item. Uses the drawing manager to
 * do the actual drawing of the face. The global state of which face parts
 * are visible is kept up to date by the IssueCommand() method according to
 * the menu picks of the user.
 * (This function is an override of the  method defined
 * originally for the vdialogItem class.)
 *********/
void FaceItemDraw(vdialogItem *item)
{
  vwindow     *theDialogsWindow;
  vdialog     *theDialog;
  const vrect *rect;
  int          rectX, rectY;


  theDialogsWindow = vdialogDetermineItemWindow(item);
  theDialog = vdialogDetermineItemDialog(item);
  /* 
   * Get the face item bounding box to use to offset drawing coordinates
   * since vdraw treats coordinates with respect to the window origin not
   * the dialog item origin.
   */
  rect = vdialogGetItemRect (item);
  rectX = rect->x;
  rectY = rect->y;

  vdrawGSave();
  vdialogSetFocus(theDialog, item);
  vdrawSetFunction(vdrawFUNC_COPY);

  /*
   * Draw or Erase the face outline.
   */
  if (gFaceIsVisible)
    vdrawSetColor(vwindowDetermineForeground(theDialogsWindow));    
  else
    vdrawSetColor(vwindowDetermineBackground(theDialogsWindow));
  vdrawSetLineWidth(1);
  vdrawRectEllipseStroke(rectX+50, rectY+10, 100, 100);

  /*
   * Draw or Erase the eyes.
   */
  if(gEyesAreVisible)
    vdrawSetColor(vwindowDetermineForeground(theDialogsWindow));
  else
    vdrawSetColor(vwindowDetermineBackground(theDialogsWindow));
  vdrawSetLineWidth(1);
  vdrawRectEllipseFill(rectX+75, rectY+65, 10, 10);
  vdrawRectEllipseFill(rectX+115, rectY+65, 10, 10);

  /*
   * Draw or Erase the nose.
   */
  if(gNoseIsVisible)
      vdrawSetColor(vwindowDetermineForeground(theDialogsWindow));
  else
      vdrawSetColor(vwindowDetermineBackground(theDialogsWindow));
  vdrawSetLineWidth(1);
  vdrawMoveTo(rectX+100, rectY+60);
  vdrawLineTo(rectX+95, rectY+50);
  vdrawLineTo(rectX+105, rectY+50);
  vdrawStroke();

  /*
   * Draw or Erase the mouth.
   */
  if(gMouthIsVisible)
      vdrawSetColor(vwindowDetermineForeground(theDialogsWindow));
  else
      vdrawSetColor(vwindowDetermineBackground(theDialogsWindow));
  vdrawSetLineWidth(2);
  vdrawArc(rectX+100, rectY+50, 30, 200, 340);
  vdrawStroke();

  vdrawGRestore();
}



/* HandleDialog -- the callback function for the main dialog
 *			This stops processing, and we
 *			fall through the other side of the veventProcess ();
 *
 *  -> dialog	-- the dialog that was notified.
 *  -> event	-- the event that triggered it.
 */
static void HandleDialog (vdialog *dialog, vevent *event)
{
    if (veventIsClose (event)) {
	veventStopProcessing ();
    }
} /* HandleDialog */



/********
 * main()
 *
 * The main program.
 * Set up our vcommandSelector subclass and our vdialogItem subclass, then
 * start the demo by entering the event processing loop.
 *********/
int main(int argc, char *argv[])
{
  register int            i;
  vapplication           *application;
  vcommandSpace          *space;
  vdict                  *dict;
  vcommandSelectorClass  *clas;
  vcommandSelector       *command;
  vdialog                *dialog;
  vresource               resources;
  vdialogItemClass       *faceItemClass;

  vstartup(argc, argv);

  /*
   * Subclass the Selector command class to customize it for our own selectors.
   */
  clas = vclassReproduce(vcommandGetDefaultSelectorClass());
  _defaultSelectorClass = clas;

  /*
   * Set the vcommandISSUE message to refer to our own IssueCommand() function
   * that dispatches work based on our own selectors. In other words,
   * override our parent's vcommandIssue() function.
   */
  vclassSet(clas, vcommandISSUE, IssueCommand);

  /*
   * Create a command space and store it in our application.
   */
  application = vapplicationGetCurrent();
  space = vcommandCreateSpace();
  dict = vdictCreate(vnameHash);

  /*
   * Create our four individual Selector commands, set their numerical
   * selector values, and map them to string tags by Storing 
   * each <tag, command> pair in the dict dictionary.
   */
  for (i = FACE; i <= QUIT; i++)
    {
      command = vcommandCreateSelectorOfClass(clas);
      vcommandSetSelector(command, i);
      vdictStore(dict, vnameInternGlobalLiteral(commandNames[i]), 
		 command);
    }

  vcommandAddSpaceDictOwned(space, vname_Command, dict);
  vapplicationSetSpaceOwned(application, space);

  /*
   * Create a subclass of vdialogBoxItem so that we can override it's
   * drawing method to draw the face parts.
   */
  faceItemClass = vclassReproduce(vdialogGetDefaultItemClass());
  _defaultFaceItemClass = faceItemClass;
  vclassSetNameScribed(faceItemClass, vcharScribeLiteral("faceItem"));

  /*
   * Set the vdialogDRAW_ITEM message to refer to our own FaceItemDraw()
   * function that contains code to draw the happy face.
   */
  vclassSet(faceItemClass, vdialogDRAW_ITEM, FaceItemDraw);

  /*
   * Finally, load our dialog from our resource file.
   */
  resources = vapplicationGetResources(application);
  dialog = vdialogLoad(vresourceGet(resources,
				    vnameInternGlobalLiteral("FaceDialog")));
  /*
   * Place our eight Face Parts menu item strings in the global name table
   * so we can use them as non-literals in multiple places later on.
   */
  name_DrawFace = vnameInternGlobalLiteral("Draw Face");
  name_DrawEyes = vnameInternGlobalLiteral("Draw Eyes");
  name_DrawNose = vnameInternGlobalLiteral("Draw Nose");
  name_DrawMouth = vnameInternGlobalLiteral("Draw Mouth");
  name_EraseFace = vnameInternGlobalLiteral("Erase Face");
  name_EraseEyes = vnameInternGlobalLiteral("Erase Eyes");
  name_EraseNose = vnameInternGlobalLiteral("Erase Nose");
  name_EraseMouth = vnameInternGlobalLiteral("Erase Mouth");

  vdialogSetNotify(dialog, HandleDialog);

  vdialogOpen(dialog);

  veventProcess();

  vdialogDestroy(dialog);

  exit(EXIT_SUCCESS);
  return EXIT_FAILURE;

}

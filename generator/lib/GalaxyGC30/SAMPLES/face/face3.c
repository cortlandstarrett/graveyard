/* $Id: face3.c,v 1.4 1996/05/10 23:06:23 david Exp $ */

#include <vport.h>

#include vstdlibHEADER
#include vapplicationHEADER
#include vcommandHEADER
#include vdictHEADER
#include veventHEADER
#include vdialogHEADER
#include vnameHEADER
#include vresourceHEADER
#include vstartupHEADER


/****************************************************************************
 * executable:    face3
 * .c files:      face3.c
 * resource file: face.vr
 *
 * managers illustrated: Command Manager (selector commands)
 *                       Class   Manager (subclassing, adding class vars.)
 *                       Drawing Manager (simple B&W shape outlines and fills)
 *                       Menu    Manager (dynamically changing menuitem titles)
 *
 *
 * This program differs from its predecessor, face2, in that the face
 * subclass adds class variables to hold the needed state information instead
 * of adding and using instance variables (adding named attributes and
 * propagating changes).
 *
 * This program illustrates how to associate application code to user 
 * interface items using selector commands (instead of notify
 * functions). It also illustrates how to do subclassing
 * of vdialogItem to get a subclass that adds new class variables
 * and how to use these new class variables to hold state that applies
 * to all subclass instances.
 * Also, it illustrates how to use some of the drawing manager functionality.
 *
 * This demo consists of a single dialog which contains nine "Happy Face"
 * dialog items. The face object is a subclass of vdialogItem and knows
 * how to draw itself as a happy face. Different parts of the faces can be
 * drawn or erased by picking from the "Face Parts" menu (menu item titles
 * change dynamically depending on whether each face part can be
 * drawn or erased). The menu items use selector commands to map to
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
 * Pointer to our subclass of vcommandSelectorClass.
 */
static vcommandSelectorClass  *_defaultSelectorClass = NULL;


/*
 * String constants used as references for menu item titles
 * ( these are set up in main() ).
 */
const vname *name_DrawFace, *name_DrawEyes, *name_DrawNose,
            *name_DrawMouth, *name_EraseFace, *name_EraseEyes,
            *name_EraseNose, *name_EraseMouth;

/*
 * declarations for our new vdialogItem subclass.
 */
typedef struct vdialogItem  face;   /* Note - no new instance data! */
typedef struct faceClass    faceClass;


/*
 * define the face operations and class variables using the macro convention.
 *
 * In OOP terminology, we are declaring the instance methods and class 
 * variables for a face object. The macro copies down all the inherited
 * ones, then adds any face-specific ones. In our case here, we are just
 * adding four class variables.
 */

#define faceCLASS(SUPER, FACE, NOTIFY)                                     \
    vdialogITEM_CLASS(SUPER, FACE, NOTIFY);                                \
    vclassVARIABLE(faceFaceIsVisible, vbool);  \
    vclassVARIABLE(faceEyesAreVisible, vbool); \
    vclassVARIABLE(faceNoseIsVisible, vbool);  \
    vclassVARIABLE(faceMouthIsVisible, vbool)


/*
 * define the contents of our class structure by calling our class macro.
 */

struct faceClass
{
  faceCLASS(faceClass, face, vdialogItemNoteProc);
};


/*
 * Forward references.
 */
faceClass *faceGetDefaultClass(void);


/*
 * Macro definitions for some functions.
 * Note - for purposes of simplifying this demo, we did not completely fill out
 *        the interface as we would have if our new subclass were going to
 *        be used as a parent class at some point.
 */
#define faceCreateOfClass(c) \
    ((face *)vdialogItemCreateOfClass((vdialogItemClass *)(c)))
#define faceCreate()  faceCreateOfClass(faceGetDefaultClass())

#define faceGetDitem(n)  ((vdialogItem *)(n))
#define faceGetClass(n) ((faceClass *)vdialogGetItemClass((n)))


/*
 * Convenience functions if have a face object and want to check a class
 * variable.
 */
#define faceGetFaceVisible(n) (vclassGet(faceGetClass(n), faceFaceIsVisible))
#define faceGetEyesVisible(n) (vclassGet(faceGetClass(n), faceEyesAreVisible))
#define faceGetNoseVisible(n) (vclassGet(faceGetClass(n), faceNoseIsVisible))
#define faceGetMouthVisible(n) (vclassGet(faceGetClass(n), faceMouthIsVisible))

#define faceSend(i, m, a)   vclassSend(faceGetClass(i), m, a)


/*
 * pointer to our subclass of vdialogItem, face.
 */
static faceClass *_faceDefaultClass = NULL;



/*------------- Methods overridden from vdialogItem -------------------------*/
/*------------- originally defined for vdialog items ------------------------*/

/********
 * FaceItemDraw()
 *
 * The drawing procedure for the face object. Uses the drawing manager to
 * do the actual drawing of the face. The state of which face parts
 * are visible is kept up to date by the IssueCommand() method according to
 * the menu picks of the user.
 * This method is an override of vdialogDRAW_ITEM.
 *********/
void FaceItemDraw(face *faceItem)
{
  vwindow     *theDialogsWindow;
  vdialog     *theDialog;
  const vrect *rect;
  int          rectX, rectY;


  theDialogsWindow = vdialogDetermineItemWindow(faceItem);
  theDialog = vdialogDetermineItemDialog(faceItem);
  /* 
   * Get the face object bounding box to use to offset drawing coordinates
   * since vdraw treats coordinates with respect to the window origin not
   * the dialog item origin.
   */
  rect = vdialogGetItemRect(faceItem);
  rectX = rect->x;
  rectY = rect->y;

  vdrawGSave();
  vdialogSetFocus(theDialog, faceItem);
  vdrawSetFunction(vdrawFUNC_COPY);

  /*
   * Draw or Erase the face outline.
   */
  if (faceGetFaceVisible(faceItem))
    vdrawSetColor(vwindowDetermineForeground(theDialogsWindow));    
  else
    vdrawSetColor(vwindowDetermineBackground(theDialogsWindow));
  vdrawSetLineWidth(1);
  vdrawRectEllipseStroke(rectX+50, rectY+10, 100, 100);

  /*
   * Draw or Erase the eyes.
   */
  if(faceGetEyesVisible(faceItem))
    vdrawSetColor(vwindowDetermineForeground(theDialogsWindow));
  else
    vdrawSetColor(vwindowDetermineBackground(theDialogsWindow));
  vdrawSetLineWidth(1);
  vdrawRectEllipseFill(rectX+75, rectY+65, 10, 10);
  vdrawRectEllipseFill(rectX+115, rectY+65, 10, 10);

  /*
   * Draw or Erase the nose.
   */
  if(faceGetNoseVisible(faceItem))
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
  if(faceGetMouthVisible(faceItem))
      vdrawSetColor(vwindowDetermineForeground(theDialogsWindow));
  else
      vdrawSetColor(vwindowDetermineBackground(theDialogsWindow));
  vdrawSetLineWidth(2);
  vdrawArc(rectX+100, rectY+50, 30, 200, 340);
  vdrawStroke();

  vdrawGRestore();
}


/*----------- Method overridden from vcommandSelector ---------------------*/
/*------------- originally defined for vcommand ---------------------------*/

/********
 * IssueCommand()
 *
 * The dispatch point for all the commands associated with the Face Parts
 * and File menus {all of our application menus}.
 * This method is an override of the vcommandISSUE method defined
 * originally for the Selector class.
 *********/
static int IssueCommand(vcommandSelector *command, vdict *attr2value)
{
  const vchar  *theMenuItemsTitle;
  vmenuItem    *theMenuItem;
  vdialog      *theDialog;
  int           numItems;
  int           i; /* counter */
  vdialogItemList  *listOfItems;
  vbool             visible;
  vdialogItem      *ditem;


#if (vdebugDEBUG)
  vdictDump(attr2value, stdout);
#endif

  /*
   * Change the corresponding menu item title for the selector command 
   * issued and change the corresponding class variable so that the
   * drawing function for the face object, FaceItemDraw(), can
   * use the class variable to know how to draw each face.
   * The menu item title will reflect what can be done with each face part at
   * all times. All nine face objects in our dialog remain
   * visually consistent with each other. That is why we can use class
   * variables to hold the visible/nonvisible state information.
   */
  theMenuItemsTitle = (const vchar *)vdictLoad(attr2value, vname_Title);
  theMenuItem = (vmenuItem *)vdictLoad(attr2value, vname_Operator);
  theDialog = (vdialog *)vdictLoad(attr2value, vname_Dialog);

  listOfItems = vdialogGetItemList(theDialog);
  numItems = vdialogGetItemListItemCount(listOfItems);

  switch (vcommandGetSelector(command))
    {
    case FACE:
      /*
       * Cycle through the dialog items forcing all the face objects to
       * be redrawn since one of their visual attributes is going to change.
       */
      for (i=0; i < numItems; i++)
	{
	  ditem = vdialogGetItemListItemAt(listOfItems, i);
	  if ( vobjectIsKindOf(vdialogGetItemObject(ditem), 
			       faceGetDefaultClass()) )
	    {
	      /* force the face object to be redrawn */
	      vdialogInvalItem(ditem, vwindowINVAL_IMMEDIATE);
	    }
	}
      visible = vclassGet(_faceDefaultClass, faceFaceIsVisible);

      if (visible)
	{
	  /* the face will be erased, so now allow drawing. */
	  vmenuSetItemTitle(theMenuItem, name_DrawFace);
	  vclassSet(_faceDefaultClass, faceFaceIsVisible, FALSE);
	}
      else
	{
	  /* the face will be drawn, so now allow erasure. */
	  vmenuSetItemTitle(theMenuItem, name_EraseFace);
	  vclassSet(_faceDefaultClass, faceFaceIsVisible, TRUE);
	}
      break;

    case EYES:
      /*
       * Cycle through the dialog items forcing all the face objects to
       * be redrawn since one of their visual attributes is going to change.
       */
      for (i=0; i < numItems; i++)
	{
	  ditem = vdialogGetItemListItemAt(listOfItems, i);
	  if ( vobjectIsKindOf(vdialogGetItemObject(ditem),
			       faceGetDefaultClass()) )
	    {
	      /* force the face object to be redrawn */
	      vdialogInvalItem(ditem, vwindowINVAL_IMMEDIATE);
	    }
	}
      visible = vclassGet(_faceDefaultClass, faceEyesAreVisible);

      if (visible)
	{
	  /* the eyes will be erased, so now allow drawing. */
	  vmenuSetItemTitle(theMenuItem, name_DrawEyes);
	  vclassSet(_faceDefaultClass, faceEyesAreVisible, FALSE);
	}
      else
	{
	  /* the eyes will be drawn, so now allow drawing. */
	  vmenuSetItemTitle(theMenuItem, name_EraseEyes);
	  vclassSet(_faceDefaultClass, faceEyesAreVisible, TRUE);
	}
      break;

    case NOSE:
      /*
       * Cycle through the dialog items forcing all the face objects to
       * be redrawn since one of their visual attributes is going to change.
       */
      for (i=0; i < numItems; i++)
	{
	  ditem = vdialogGetItemListItemAt(listOfItems, i);
	  if ( vobjectIsKindOf(vdialogGetItemObject(ditem), 
			       faceGetDefaultClass()) )
	    {
	      /* force the face object to be redrawn */
	      vdialogInvalItem(ditem, vwindowINVAL_IMMEDIATE);
	    }
	}
      visible = vclassGet(_faceDefaultClass, faceNoseIsVisible);

      if (visible)
	{
	  /* the nose will be erased, so now allow drawing. */
	  vmenuSetItemTitle(theMenuItem, name_DrawNose);
	  vclassSet(_faceDefaultClass, faceNoseIsVisible, FALSE);
	}
      else
	{
	  /* the nose will be drawn, so now allow erasure. */
	  vmenuSetItemTitle(theMenuItem, name_EraseNose);
	  vclassSet(_faceDefaultClass, faceNoseIsVisible, TRUE);
	}
      break;

    case MOUTH:
      /*
       * Cycle through the dialog items forcing all the face objects to
       * be redrawn since one of their visual attributes is going to change.
       */
      for (i=0; i < numItems; i++)
	{
	  ditem = vdialogGetItemListItemAt(listOfItems, i);
	  if ( vobjectIsKindOf(vdialogGetItemObject(ditem), 
			       faceGetDefaultClass()) )
	    {
	      /* force the face object to be redrawn */
	      vdialogInvalItem(ditem, vwindowINVAL_IMMEDIATE);
	    }
	}
      visible = vclassGet(_faceDefaultClass, faceMouthIsVisible);

      if (visible)
	{
	  /* the mouth will be erased, so now allow drawing. */
	  vmenuSetItemTitle(theMenuItem, name_DrawMouth);
	  vclassSet(_faceDefaultClass, faceMouthIsVisible, FALSE);
	}
      else
	{
	  /* the mouth will be drawn, so now allow erasure. */
	  vmenuSetItemTitle(theMenuItem, name_EraseMouth);
	  vclassSet(_faceDefaultClass, faceMouthIsVisible, TRUE);
	}
      break;

    case QUIT:
      veventStopProcessing();
      break;

    default:
      return(vclassSendSuper(_defaultSelectorClass, vcommandISSUE,
			     (command, attr2value)));
    }

  return(TRUE);
}



/*--------------------------- Main Program --------------------------------*/

/********
 * _faceSetUp()
 *
 * Do all the set up for our new vdialogItem subclass, face.
 * This function is called from main().
 ********/
static void _faceSetUp(void)
{
  register faceClass *clas;


  /*
   * Create a subclass of vdialogBoxItem so that we can override its
   * drawing method to draw the face parts and so that we can add
   * four class variables to keep track of the visible/non-viible state
   * of all the face object parts.
   */
  clas = vclassSpawn(vdialogGetDefaultItemClass(), sizeof(faceClass));

  _faceDefaultClass = clas;

  /*
   * Tell the class manager what our name is and how big our instances are.
   */
  vclassSetNameScribed(clas, vcharScribeLiteral("faceClass"));
  vclassSetObjectSize(clas, sizeof(face));

  /*
   * Override the vdialogItem method, vdialogDRAW_ITEM, to refer to our
   * own FaceItemDraw() function that contains code to draw a happy face.
   */
  vclassSet(clas, vdialogDRAW_ITEM, FaceItemDraw);

  /* 
   * No new methods specific to face objects. 
   */

  /*
   * Initialize our new class variables.
   */
  vclassSet(clas, faceFaceIsVisible, FALSE);
  vclassSet(clas, faceEyesAreVisible, FALSE);
  vclassSet(clas, faceNoseIsVisible, FALSE);
  vclassSet(clas, faceMouthIsVisible, FALSE);

}


/*********
 * faceGetDefaultClass()
 *
 * a public function. Necessary to allow calling of superclass methods
 * from our face subclass methods and also to allow further subclasses to
 * be built on our face class.
 *********/
faceClass *faceGetDefaultClass(void)
{
  if (_faceDefaultClass == NULL)
    _faceSetUp();

  return(_faceDefaultClass);
}



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
   * Set up our vdialogItem subclass, face.
   */
  _faceSetUp();

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

  vdialogOpen(dialog);

  veventProcess();

  /* Note - dict is an owned dictionary, so we don't need to explicitly
   * free it.
   */

  vdialogDestroy(dialog);

  exit(EXIT_SUCCESS);
  return EXIT_FAILURE;
}


/* $Id: face2.c,v 1.5 1997/11/12 19:50:46 gregt Exp $ */

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
 * executable:    face2
 * .c files:      face2.c
 * resource file: face.vr
 *
 * managers illustrated: Command Manager (selector commands)
 *                       Class   Manager (complex subclassing, propagation)
 *                       Drawing Manager (simple B&W shape outlines and fills)
 *                       Menu    Manager (dynamically changing menuitem titles)
 *
 * This program illustrates how to associate application code to user 
 * interface items using selector commands (instead of notify
 * functions). It also illustrates how to do fairly complex subclassing
 * of vdialogItem to get a subclass which has attributes and methods of 
 * its own above and beyond those of a simple vdialogItem and how to deal
 * with propagating changes in these new attributes to all subclass instances.
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
typedef struct face       face;
typedef struct faceClass  faceClass;


/*
 * define the structure of a face object.
 * In OOP terminology, we are declaring the instance variables for our
 * new subclass, face.
 *
 * ditem  - the dialog item object that the face object is built on. This needs
 *          to come first since face is a subclass of vdialogItem. More
 *          importantly, this ensures that the face's class will be located
 *          in the place where the method dispatch mechanism expects to find
 *          it. This convention also makes it possible to cast a pointer to
 *          a vdialogItem to a pointer to a face assuming that we know the item
 *          is really a face item.
 *
 * faceIsVisible - a boolean attribute. TRUE if the face outline of the face
 *                 object is currently visible. FALSE if not.
 *
 * eyesAreVisible - a boolean attribute. TRUE if the eyes of the face object
 *                  are currently visible. FALSE if not.
 *
 * noseIsVisible - a boolean attribute. TRUE if the nose of the face object is
 *                 currently visible. FALSE if not.
 *
 * mouthIsVisible - a boolean attribute. TRUE if the mouth of the face object
 *                  is currently visible, FALSE if not.
 *
 */

struct face
{
  vdialogItem  ditem;
  vbool        faceIsVisible;
  vbool        eyesAreVisible;
  vbool        noseIsVisible;
  vbool        mouthIsVisible;
};
 

/*
 * define the face operations using the macro convention.
 *
 * In OOP terminology, we are declaring the instance methods for
 * a face object. The macro copies down all the inherited ones, then
 * adds the face-specific ones.
 */

#define faceCLASS(SUPER, FACE, NOTIFY)                                     \
    vdialogITEM_CLASS(SUPER, FACE, NOTIFY);                                \
    vclassMETHOD(faceSET_FACE_VISIBLE, (FACE *face, vbool faceIsVisible)); \
    vclassMETHOD(faceSET_EYES_VISIBLE, (FACE *face, vbool eyesAreVisible));\
    vclassMETHOD(faceSET_NOSE_VISIBLE, (FACE *face, vbool noseIsVisible)); \
    vclassMETHOD(faceSET_MOUTH_VISIBLE,(FACE *face, vbool mouthIsVisible))

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
static void _faceSetFaceIsVisible(face *faceItem, vbool faceIsVisible);
static void _faceSetEyesAreVisible(face *faceItem, vbool eyesAreVisible);
static void _faceSetNoseIsVisible(face *faceItem, vbool noseIsVisible);
static void _faceSetMouthIsVisible(face *faceItem, vbool mouthIsVisible);


/*
 * Macro definitions for some functions.
 */
#define faceCreateOfClass(c) \
    ((face *)vdialogItemCreateOfClass((vdialogItemClass *)(c)))
#define faceCreate()  faceCreateOfClass(faceGetDefaultClass())
#define faceClone(n)  ((face *)vdialogItemClone(&(n)->ditem))
#define faceInitOfClass(n, c) \
    vdialogItemInitOfClass(&(n)->ditem, (vdialogItemClass *)(c))
#define faceInit(n)   faceInitOfClass(n, faceGetDefaultClass())
#define faceCopyInit(n, t) \
    vdialogItemCopyInit(&(n)->ditem, &(t)->ditem)
#define faceLoad(r)  ((face *)vdialogItemLoad(r))
#define faceLoadInit(n, r)  vdialogItemLoadInit(&(n)->ditem, r)


#define faceGetDitem(n)  (&(n)->ditem)
#define faceGetClass(n) ((faceClass *)vdialogItemGetClass(&(n)->ditem))
#define faceGetTag(n)   vdialogItemGetTag(&(n)->ditem)


#define faceFaceIsVisible(n)  ((n)->faceIsVisible)
#define faceEyesAreVisible(n)  ((n)->eyesAreVisible)
#define faceNoseIsVisible(n)  ((n)->noseIsVisible)
#define faceMouthIsVisible(n) ((n)->mouthIsVisible)

#define faceSend(i, m, a)   vclassSend(facegetClass(i), m, a)
#define faceSetFaceIsVisible(n, f)  faceSend(n, faceSET_FACE_VISIBLE, (n, f))
#define faceSetEyesAreVisible(n, e) faceSend(n, faceSET_EYES_VISIBLE, (n, e))
#define faceSetNoseIsVisible(n, x)  faceSend(n, faceSET_NOSE_VISIBLE, (n, x))
#define faceSetMouthIsVisible(n, m) faceSend(n, faceSET_MOUTH_VISIBLE,(n, m))


/*
 * pointer to our subclass of vdialogItem, face.
 */
static faceClass *_faceDefaultClass = NULL;

/*
 * String constants used as references for face's new named attributes.
 */
static const vname *face_FaceVisible, *face_EyesVisible,
                   *face_NoseVisible, *face_MouthVisible;


/*------------- Methods overridden from vdialogItem -------------------------*/
/*--------------- originally defined for vobject ----------------------------*/

/*********
 * _faceInit()
 *
 * Initializes an instance of a face object.
 * This method is an override of vobjectINIT.
 **********/
static void _faceInit(face *faceItem)
{
  /*
   * Initialize all inherited data members
   */
  vclassSendSuper(_faceDefaultClass, vobjectINIT, (faceItem));

  /*
   * Initialize face item data members.
   */
  faceItem->faceIsVisible = FALSE;
  faceItem->eyesAreVisible = FALSE;
  faceItem->noseIsVisible = FALSE;
  faceItem->mouthIsVisible = FALSE;
}


/*********
 * _faceCopyInit()
 * 
 * Initializes a face object from an existing face object.
 * This method is an override of vobjectCOPY_INIT.
 **********/
static void _faceCopyInit(face *faceItem, face *target)
{
  /* 
   * Initialize all inherited instance variables.
   */
  vclassSendSuper(_faceDefaultClass, vobjectCOPY_INIT, (faceItem, target));

  /*
   * Initialize face object instance variables.
   */
  target->faceIsVisible = faceItem->faceIsVisible;
  target->eyesAreVisible = faceItem->eyesAreVisible;
  target->noseIsVisible = faceItem->noseIsVisible;
  target->mouthIsVisible = faceItem->mouthIsVisible;

}


/*********
 * _faceLoadInit()
 *
 * Initializes a face object from a resource.
 * This method is an override of vobjectLOAD_INIT.
 *********/
static void _faceLoadInit(face *faceItem, vresource resource)
{
  /*
   * Load the face object as if it were a vdialogItem (which it really is
   * in the resource file).
   */
  vclassSendSuper(_faceDefaultClass,vobjectLOAD_INIT,(faceItem, resource));

  /*
   * Initialize face object instance variables.
   */
  faceItem->faceIsVisible = FALSE;
  faceItem->eyesAreVisible = FALSE;
  faceItem->noseIsVisible = FALSE;
  faceItem->mouthIsVisible = FALSE;
}



/*------------- Methods overridden from vdialogItem -------------------------*/
/*---------- originally defined for attributed objects ----------------------*/

/********
 * _faceSetAttribute()
 *
 * If the given attribute is a named attribute for face objects, set
 * this attribute to the given value for the given face object.
 * This method is an override of vobjectSET_ATTRIBUTE.
 *********/
static void  _faceSetAttribute(face *faceItem, const vname *attr,
			       const void *value)
{
  /*
   * Set the attribute in our parent first (will only matter if the attr
   * is named for our parent).
   */
  vclassSendSuper(_faceDefaultClass, vobjectSET_ATTRIBUTE, 
		  (faceItem, attr, value));

  /*
   * Change any of our attributes that match the given attr name.
   */
  if (attr==face_FaceVisible)
    _faceSetFaceIsVisible(faceItem, (value == vname_On) ? TRUE : FALSE );
  else if (attr==face_EyesVisible)
    _faceSetEyesAreVisible(faceItem, (value == vname_On) ? TRUE : FALSE );
  else if (attr==face_NoseVisible)
    _faceSetNoseIsVisible(faceItem, (value == vname_On) ? TRUE : FALSE );
  else if (attr==face_MouthVisible)
    _faceSetMouthIsVisible(faceItem, (value == vname_On) ? TRUE : FALSE );
  
}


/********
 * _faceSetAllAttributes()
 *
 * If any of the attributes in the given dictionary is a named attribute
 * for face objects, set this attribute to the given value for the given
 * face object.
 * This method is an override of vobjectSET_ALL_ATTRIBUTES.
 *********/
static void _faceSetAllAttributes(face *faceItem, vdict *attr2value)
{
  const void *value;

  /*
   * Set the attributes in our parent first (will only matter for each given
   * attr that is named for our parent).
   */
  vclassSendSuper(_faceDefaultClass, vobjectSET_ALL_ATTRIBUTES,
		  (faceItem, attr2value));

  /*
   * Change any of our attributes that match given attr names.
   */
  if ((value = vdictLoad(attr2value, face_FaceVisible)) != NULL)
    _faceSetFaceIsVisible(faceItem, (value == vname_On) ? TRUE:FALSE );
  if ((value = vdictLoad(attr2value, face_EyesVisible)) != NULL)
    _faceSetEyesAreVisible(faceItem, (value == vname_On) ? TRUE:FALSE );
  if ((value = vdictLoad(attr2value, face_NoseVisible)) != NULL)
    _faceSetNoseIsVisible(faceItem, (value == vname_On) ? TRUE:FALSE );
  if ((value = vdictLoad(attr2value, face_MouthVisible)) != NULL)
    _faceSetMouthIsVisible(faceItem, (value == vname_On) ? TRUE:FALSE );

}


/********
 * _faceGetAttribute()
 *
 * If the given attribute is a named attribute for face objects, return
 * this attribute's value for the given face object.
 * This method is an override of vobjectGET_ATTRIBUTE.
 *********/
static const void *_faceGetAttribute(face *faceItem, const vname *attr)
{

  /*
   * Return the appropriate value if its one of our named attrs.
   */
  if (attr==face_FaceVisible)
    return ( faceFaceIsVisible(faceItem) ? vname_On : vname_Off );
  if (attr==face_EyesVisible)
    return ( faceEyesAreVisible(faceItem) ? vname_On : vname_Off );
  if (attr==face_NoseVisible)
    return ( faceNoseIsVisible(faceItem) ? vname_On : vname_Off );
  if (attr==face_MouthVisible)
    return ( faceMouthIsVisible(faceItem) ? vname_On : vname_Off );

  /*
   * If we get to this point, the given attr was not one of our specific
   * named attributes. So, it must be an inherited named attribute. 
   * So, check our inherited attributes for it.
   */
  return (vclassSendSuper(_faceDefaultClass, vobjectGET_ATTRIBUTE,
			  (faceItem, attr)) );
}


/********
 * _faceGetAllAttributes()
 *
 * If any of the attributes in the given dictionary is a named attribute
 * for face objects, put this attribute/value pair for the given face object
 * into the given dictionary, attr2value, to be returned.
 * This method is an override of vobjectGET_ALL_ATTRIBUTES.
 *********/
static void _faceGetAllAttributes(face *faceItem, vdict *attr2value)
{
  /*
   * Enter our inherited named attributes into the given dict first.
   */
  vclassSendSuper(_faceDefaultClass, vobjectGET_ALL_ATTRIBUTES,
		  (faceItem, attr2value));

  /*
   * Enter our own specific named attributes into the given dict now.
   */
  vdictStore(attr2value, face_FaceVisible, 
	     (faceFaceIsVisible(faceItem) ? vname_On : vname_Off) );
  vdictStore(attr2value, face_EyesVisible, 
	     (faceEyesAreVisible(faceItem) ? vname_On : vname_Off) );
  vdictStore(attr2value, face_NoseVisible, 
	     (faceNoseIsVisible(faceItem) ? vname_On : vname_Off) );
  vdictStore(attr2value, face_EyesVisible, 
	     (faceMouthIsVisible(faceItem) ? vname_On : vname_Off) );
}


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


  theDialogsWindow = vdialogDetermineItemWindow(faceGetDitem(faceItem));
  theDialog = vdialogDetermineItemDialog(faceGetDitem(faceItem));
  /* 
   * Get the face object bounding box to use to offset drawing coordinates
   * since vdraw treats coordinates with respect to the window origin not
   * the dialog item origin.
   */
  rect = vdialogGetItemRect(faceGetDitem(faceItem));
  rectX = rect->x;
  rectY = rect->y;

  vdrawGSave();
  vdialogSetFocus(theDialog, faceGetDitem(faceItem) );
  vdrawSetFunction(vdrawFUNC_COPY);

  /*
   * Draw or Erase the face outline.
   */
  if (faceFaceIsVisible(faceItem))
    vdrawSetColor(vwindowDetermineForeground(theDialogsWindow));    
  else
    vdrawSetColor(vwindowDetermineBackground(theDialogsWindow));
  vdrawSetLineWidth(1);
  vdrawRectEllipseStroke(rectX+50, rectY+10, 100, 100);

  /*
   * Draw or Erase the eyes.
   */
  if(faceEyesAreVisible(faceItem))
    vdrawSetColor(vwindowDetermineForeground(theDialogsWindow));
  else
    vdrawSetColor(vwindowDetermineBackground(theDialogsWindow));
  vdrawSetLineWidth(1);
  vdrawRectEllipseFill(rectX+75, rectY+65, 10, 10);
  vdrawRectEllipseFill(rectX+115, rectY+65, 10, 10);

  /*
   * Draw or Erase the nose.
   */
  if(faceNoseIsVisible(faceItem))
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
  if(faceMouthIsVisible(faceItem))
      vdrawSetColor(vwindowDetermineForeground(theDialogsWindow));
  else
      vdrawSetColor(vwindowDetermineBackground(theDialogsWindow));
  vdrawSetLineWidth(2);
  vdrawArc(rectX+100, rectY+50, 30, 200, 340);
  vdrawStroke();

  vdrawGRestore();
}



/*------------- Methods specific to face objects ---------------------------*/

/********
 * _faceSetFaceIsVisible()
 *********/
static void _faceSetFaceIsVisible(face *faceItem, vbool faceIsVisible)
{
  faceItem->faceIsVisible = faceIsVisible;
}


/********
 * _faceSetEyesAreVisible()
 *********/
static void _faceSetEyesAreVisible(face *faceItem, vbool eyesAreVisible)
{
  faceItem->eyesAreVisible = eyesAreVisible;
}


/********
 * _faceSetNoseIsVisible()
 *********/
static void _faceSetNoseIsVisible(face *faceItem, vbool noseIsVisible)
{
  faceItem->noseIsVisible = noseIsVisible;
}


/********
 * _faceSetMouthIsVisible()
 *********/
static void _faceSetMouthIsVisible(face *faceItem, vbool mouthIsVisible)
{
  faceItem->mouthIsVisible = mouthIsVisible;
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
  face             *anItem;
  vdict            *objectTagDict;
  vbool             visible;
  vdialogItem      *ditem;


#if (vdebugDEBUG)
  vdictDump(attr2value, stdout);
#endif

  /*
   * Change the corresponding menu item title for the selector command 
   * issued and change the corresponding instance variable for each face
   * object so that the drawing function for the face object, FaceItemDraw(),
   * can use the instance variable {named attribute} to know
   * how to draw each face.
   * The menu item title will reflect what can be done with each face part at
   * all times. Currently, all nine face objects in our dialog remain
   * visually consistent with each other, however, we could easily make
   * them visually independent using the exact same propagation mechanism
   * since each face object keeps its own individual state (via instance
   * variables).
   */
  theMenuItemsTitle = (const vchar *)vdictLoad(attr2value, vname_Title);
  theMenuItem = (vmenuItem *)vdictLoad(attr2value, vname_Operator);
  theDialog = (vdialog *)vdictLoad(attr2value, vname_Dialog);

  listOfItems = vdialogGetItemList(theDialog);
  numItems = vdialogGetItemListItemCount(listOfItems);
  objectTagDict = vdictCreate(vnameHash);

  switch (vcommandGetSelector(command))
    {
    case FACE:
      /*
       * Build up the needed dictionary parameter, toggling the face attr
       * value for each face object.
       */
      for (i=0; i < numItems; i++)
	{
	  ditem = vdialogGetItemListItemAt(listOfItems, i);
	  if ( vobjectIsKindOf(vdialogGetItemObject(ditem), 
			       faceGetDefaultClass()) )
	    {
	      anItem = (face *)ditem;
	      visible = faceFaceIsVisible(anItem);
	      vdictStore(objectTagDict, 
			 vdialogGetItemTag(faceGetDitem(anItem)),
			 visible ? vname_Off : vname_On );
	      /* force the face object to be redrawn */
	      vdialogInvalItem(faceGetDitem(anItem), vwindowINVAL_IMMEDIATE);
	    }
	}
#if (vdebugDEBUG)
      vdictDump(objectTagDict, stdout);
#endif

      if (visible)
	{
	  /* the face will be erased, so now allow drawing. */
	  vmenuSetItemTitle(theMenuItem, name_DrawFace);
	}
      else
	{
	  /* the face will be drawn, so now allow erasure. */
	  vmenuSetItemTitle(theMenuItem, name_EraseFace);
	}
      /* Let all face objects know of the attribute change */
      vdialogPropagateItemListChangeDictFromParent(listOfItems,
						   face_FaceVisible,
						   objectTagDict);
      break;

    case EYES:
      /*
       * Build up the needed dictionary parameter, toggling the eyes attr
       * value for each face object.
       */
      for (i=0; i < numItems; i++)
	{
	  ditem = vdialogGetItemListItemAt(listOfItems, i);
	  if ( vobjectIsKindOf(vdialogGetItemObject(ditem),
			       faceGetDefaultClass()) )
	    {
	      anItem = (face *)ditem;
	      visible = faceEyesAreVisible(anItem);
	      vdictStore(objectTagDict, 
			 vdialogGetItemTag(faceGetDitem(anItem)),
			 visible ? vname_Off : vname_On );
	      /* force the face object to be redrawn */
	      vdialogInvalItem(faceGetDitem(anItem), vwindowINVAL_IMMEDIATE);
	    }
	}
#if (vdebugDEBUG)
      vdictDump(objectTagDict, stdout);
#endif

      if (visible)
	{
	  /* the eyes will be erased, so now allow drawing. */
	  vmenuSetItemTitle(theMenuItem, name_DrawEyes);
	}
      else
	{
	  /* the eyes will be drawn, so now allow drawing. */
	  vmenuSetItemTitle(theMenuItem, name_EraseEyes);
	}
      /* Let all face objects know of the attribute change */
      vdialogPropagateItemListChangeDictFromParent(listOfItems,
						   face_EyesVisible,
						   objectTagDict);

      break;

    case NOSE:
      /*
       * Build up the needed dictionary parameter, toggling the nose attr
       * value for each face object.
       */
      for (i=0; i < numItems; i++)
	{
	  ditem = vdialogGetItemListItemAt(listOfItems, i);
	  if ( vobjectIsKindOf(vdialogGetItemObject(ditem), 
			       faceGetDefaultClass()) )
	    {
	      anItem = (face *)ditem;
	      visible = faceNoseIsVisible(anItem);
	      vdictStore(objectTagDict, 
			 vdialogGetItemTag(faceGetDitem(anItem)),
			 visible ? vname_Off : vname_On );
	      /* force the face object to be redrawn */
	      vdialogInvalItem(faceGetDitem(anItem), vwindowINVAL_IMMEDIATE);
	    }
	}
#if (vdebugDEBUG)
      vdictDump(objectTagDict, stdout);
#endif

      if (visible)
	{
	  /* the nose will be erased, so now allow drawing. */
	  vmenuSetItemTitle(theMenuItem, name_DrawNose);
	}
      else
	{
	  /* the nose will be drawn, so now allow erasure. */
	  vmenuSetItemTitle(theMenuItem, name_EraseNose);
	}
      /* Let all face objects know of the attribute change */
      vdialogPropagateItemListChangeDictFromParent(listOfItems,
						   face_NoseVisible,
						   objectTagDict);
      break;

    case MOUTH:
      /*
       * Build up the needed dictionary parameter, toggling the mouth attr
       * value for each face object.
       */
      for (i=0; i < numItems; i++)
	{
	  ditem = vdialogGetItemListItemAt(listOfItems, i);
	  if ( vobjectIsKindOf(vdialogGetItemObject(ditem), 
			       faceGetDefaultClass()) )
	    {
	      anItem = (face *)ditem;
	      visible = faceMouthIsVisible(anItem);
	      vdictStore(objectTagDict, 
			 vdialogGetItemTag(faceGetDitem(anItem)),
			 visible ? vname_Off : vname_On );
	      /* force the face object to be redrawn */
	      vdialogInvalItem(faceGetDitem(anItem), vwindowINVAL_IMMEDIATE);
	    }
	}
#if (vdebugDEBUG)
      vdictDump(objectTagDict, stdout);
#endif

      if (visible)
	{
	  /* the mouth will be erased, so now allow drawing. */
	  vmenuSetItemTitle(theMenuItem, name_DrawMouth);
	}
      else
	{
	  /* the mouth will be drawn, so now allow erasure. */
	  vmenuSetItemTitle(theMenuItem, name_EraseMouth);
	}
      /* Let all face objects know of the attribute change */
      vdialogPropagateItemListChangeDictFromParent(listOfItems,
						   face_MouthVisible,
						   objectTagDict);
      break;

    case QUIT:
      veventStopProcessing();
      break;

    default:
      return(vclassSendSuper(_defaultSelectorClass, vcommandISSUE,
			     (command, attr2value)));
    }

  vdictDestroy(objectTagDict);

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
   * methods and instance variables {used also as named attributes} to
   * allow each face object to keep track of its own visual state.
   */
  clas = vclassSpawn(vdialogGetDefaultItemClass(), sizeof(faceClass));

  _faceDefaultClass = clas;

  /*
   * Tell the class manager what our name is and how big our instances are.
   */
  vclassSetNameScribed(clas, vcharScribeLiteral("faceClass"));
  vclassSetObjectSize(clas, sizeof(face));

  /*
   * Override some vdialogItem methods that were originally defined in vobject.
   * We must override these initialization methods to ensure that instances
   * of our subclass will always be initialized properly (since we added
   * instance variables).
   */
  vclassSet(clas, vobjectINIT, _faceInit);
  vclassSet(clas, vobjectCOPY_INIT, _faceCopyInit);
  vclassSet(clas, vobjectLOAD_INIT, _faceLoadInit);

  /*
   * Override some vdialogItem methods that were originally defined for
   * attributed objects. We need to override these methods because our
   * face object has defined some new named attributes.
   */
  vclassSet(clas, vobjectSET_ATTRIBUTE, _faceSetAttribute);
  vclassSet(clas, vobjectSET_ALL_ATTRIBUTES, _faceSetAllAttributes);
  vclassSet(clas, vobjectGET_ATTRIBUTE, _faceGetAttribute);
  vclassSet(clas, vobjectGET_ALL_ATTRIBUTES, _faceGetAllAttributes);

  /*
   * Override the vdialogItem method, vdialogDRAW_ITEM, to refer to our
   * own FaceItemDraw() function that contains code to draw the happy face.
   */
  vclassSet(clas, vdialogDRAW_ITEM, FaceItemDraw);

  /*
   * Define some methods particular to face objects.
   */
  vclassSet(clas, faceSET_FACE_VISIBLE, _faceSetFaceIsVisible);
  vclassSet(clas, faceSET_EYES_VISIBLE, _faceSetEyesAreVisible);
  vclassSet(clas, faceSET_NOSE_VISIBLE, _faceSetNoseIsVisible);
  vclassSet(clas, faceSET_MOUTH_VISIBLE, _faceSetMouthIsVisible);

  /*
   * Make vnames for our new named attributes.
   */
  face_FaceVisible = vnameInternGlobalLiteral("FaceVisible");
  face_EyesVisible = vnameInternGlobalLiteral("EyesVisible");
  face_NoseVisible = vnameInternGlobalLiteral("NoseVisble");
  face_MouthVisible = vnameInternGlobalLiteral("MouthVisble");
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


static void _dialogNotify(vdialog *dialog, vevent *event)
{
  if (veventGetType(event) == veventWINDOW_STATE && veventIsClose(event))
    veventStopProcessing();
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
  vdialogSetNotify(dialog, _dialogNotify);

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

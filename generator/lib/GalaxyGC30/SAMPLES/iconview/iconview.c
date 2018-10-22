/* $Id: iconview.c,v 1.8 1995/06/06 20:58:04 gregt Exp $ */
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
 */


/****************************************************************************
 * Executable Name:    iconview
 * Source Files:       iconview.c
 * Header Files:
 * Resource Files:     iconview.vr
 *
 * Managers Illustrated:
 *		Domain Manager, Class Manager
 * 	standard item illustrated: viconview
 *
 * Description Of Sample:
 *
 * This program illustrates how to add a popup menu to viconview icons.
 * 
 * The demo consists of a single dialog containing a standard viconview
 * that was created with vre. All the icons within the iconview were added
 * in vre also. When the user presses the menu mouse button on any icon
 * within the viconview, a popup menu appears. The user can make a selection
 * from the menu, but there is no functionality behind the menu items as yet.
 * To "Clean Up" the icon view, pick Clean Up from the View menu.
 *
 * To accomplish this task, the standard viconview is subclassed to override
 * its vdialogHANDLE_ITEM_BUTTON_DOWN method.
 *
 * To end the demo, choose "Quit" from the File menu, or quit from the
 * window manager menu.
 *
 * History:
 * $Log: iconview.c,v $
 * Revision 1.8  1995/06/06  20:58:04  gregt
 * added a new viconviewView just for yuks (and testing purposes)
 *
 * Revision 1.7  1994/12/15  21:22:16  david
 * Fixed typo that was messing up laf CUA menus.
 *
 * Revision 1.6  1994/11/30  17:23:55  david
 * Merged 1.4.1.1 into here
 *
 *
 * Revision 1.5  1994/11/30  16:59:43  gregt
 * fixed some menu leaks
 *
 * Revision 1.4.1.1  1994/11/30  17:05:16  david
 * Made menus behave CUA-like on laf CUA
 *
 * Revision 1.4  1994/02/28  17:38:48  simone
 * vince beautified comments.
 *
 * Revision 1.3  1993/12/17  03:31:19  chad
 * fixed missing include of vport to get v*HEADER defs
 *
 * Written for 1.2 release   02/02/93
 *****************************************************************************/

#include <vport.h>		/* for v*HEADER */

#ifndef  vstdlibINCLUDED
#include vstdlibHEADER
#endif


#ifndef  veventINCLUDED
#include veventHEADER
#endif

#ifndef  vclassINCLUDED
#include vclassHEADER
#endif

#ifndef  vstartupINCLUDED
#include vstartupHEADER
#endif

#ifndef  vtextINCLUDED
#include vtextHEADER
#endif

#ifndef  vtextviewINCLUDED
#include vtextviewHEADER
#endif

#ifndef  vapplicationINCLUDED
#include vapplicationHEADER
#endif

#ifndef  vdialogINCLUDED
#include vdialogHEADER
#endif

#ifndef  vmenuINCLUDED
#include vmenuHEADER
#endif

#ifndef  vmenubarINCLUDED
#include vmenubarHEADER
#endif

#ifndef  vtextitemINCLUDED
#include vtextitemHEADER
#endif

#ifndef  vdomainitemINCLUDED
#include vdomainitemHEADER
#endif

#ifndef  viconviewINCLUDED
#include viconviewHEADER
#endif

#ifndef  vstdioINCLUDED
#include vstdioHEADER
#endif

#ifndef  vtimestampINCLUDED
#include vtimestampHEADER
#endif

/* forward declarations */

static void demoDialogNotify(
    vdialog	*dialog,
    vevent	*event
    );

static int _specialIconViewHandleButtonDown(
    viconview	*theIconView,
    vevent	*event
    );

static void _moonViewGeometryCalc(
    viconview			*iconView,
    viconviewView		*view,
    viconviewIcon		*icon,
    vpoint			*position,
    vrect			*imageRect,
    vrect			*nameRect
    );

#ifdef vlafCUA
static int _specialIconViewHandleButtonUp(viconview *theIconView,
					  vevent *event);
static int _specialIconViewHandleDetail(viconview *theIconView,
					    vevent *event);
static int _specialIconViewHandleDrag(viconview *theIconView,
					    vevent *event);
#endif

static void viewByIconMenuItemNoteProc(vmenuItem *item, vevent *event);
static void viewByNameMenuItemNoteProc(vmenuItem *item, vevent *event);
static void viewByMoonMenuItemNoteProc(vmenuItem *item, vevent *event);
static void cleanupMenuItemNoteProc(vmenuItem *item, vevent *event);
static void shutdownMenuItemNoteProc(vmenuItem *item, vevent *event);
static void shutdownMain(void);


/* globals */

static viconviewClass *_specialIconViewClass = NULL;
viconview *globalIconView;
viconviewView *globalMoonView;

#ifdef vlafCUA
int pointX, pointY;
int nomenu;
vtimestamp pointT;
#endif


/**********
 * main:
 *
 **********/
int main
  (int                           argc,
   char                         *argv[])
{
  vdialog          *demoDialog;
  vresource         appRes, resource, menuResource, moonViewResource;
  viconview        *theIconView = NULL;
  viconviewIterator iterator;
  viconviewClass   *specialIconView;

  vmenubar         *menubar;
  vmenu            *fileMenu, *viewMenu, *popupMenu;
  vmenu            *menu;
  vmenuItem        *menuItem;
 
  vstartup(argc, argv);
 

  /*
   * subclass viconview to supply our own button down handler 
   */
  specialIconView = vclassReproduce(viconviewGetDefaultClass());
  _specialIconViewClass = specialIconView;

  vclassSetNameScribed(specialIconView, 
		       vcharScribeLiteral("specialIconView"));

  vclassSet(specialIconView, 
	    vdialogHANDLE_ITEM_BUTTON_DOWN,
	    _specialIconViewHandleButtonDown);
#ifdef vlafCUA
  if (vlafAppear() == vlafCUA)
    {
      /* CUA menus pop up on the button-up stroke */
      vclassSet(specialIconView,
		vdialogHANDLE_ITEM_BUTTON_UP,
		_specialIconViewHandleButtonUp);
      /* Detail and drag events that move the pointer too far will inhibit
	 a CUA menu from popping up */
      vclassSet(specialIconView,
		vdialogHANDLE_ITEM_DETAIL,
		_specialIconViewHandleDetail);
      vclassSet(specialIconView,
		vdialogHANDLE_ITEM_DRAG,
		_specialIconViewHandleDrag);
    }
#endif

  appRes = vapplicationGetResources(vapplicationGetCurrent());

  resource = vresourceGet(appRes, vnameInternGlobalLiteral("Dialog"));

  menuResource=vresourceGet(appRes,
			    vnameInternGlobalLiteral("ICON_POPUP"));

  /* setup the moon view before loading the dialog containing the iconview */
  moonViewResource=vresourceGet(appRes,
				vnameInternGlobalLiteral("Moon View"));
  globalMoonView = viconviewLoadView(moonViewResource);
  viconviewSetViewGeometryProc(globalMoonView, _moonViewGeometryCalc);

  popupMenu = vmenuLoad(menuResource);
  demoDialog = vdialogLoad(resource);

  /*
   * Attach Notify functions to the dialog and its menu items.
   */
  vdialogSetNotify(demoDialog, demoDialogNotify);

  menubar = (vmenubar *)vdialogFindItem(demoDialog,
					vnameInternGlobalLiteral("MenuBar"));
  fileMenu = vmenubarFindMenu(menubar,
			      vnameInternGlobalLiteral("FileMenu"));
  viewMenu = vmenubarFindMenu(menubar,
			      vnameInternGlobalLiteral("ViewMenu"));
  menuItem = vmenuFindItem(fileMenu,
			   vnameInternGlobalLiteral("FILE_QUIT"));
  vmenuSetItemNotify(menuItem, shutdownMenuItemNoteProc);

  /*
   * synthetic commands would work really well for this viewBy stuff,
   * but that's not what this sample is demonstrating.
   */

  menuItem = vmenuFindItem(viewMenu,
			   vnameInternGlobalLiteral("VIEW_byIcon"));
  vmenuSetItemNotify(menuItem, viewByIconMenuItemNoteProc);

  menuItem = vmenuFindItem(viewMenu,
			   vnameInternGlobalLiteral("VIEW_byName"));
  vmenuSetItemNotify(menuItem, viewByNameMenuItemNoteProc);

  menuItem = vmenuFindItem(viewMenu,
			   vnameInternGlobalLiteral("VIEW_byMoon"));
  vmenuSetItemNotify(menuItem, viewByMoonMenuItemNoteProc);

  menuItem = vmenuFindItem(viewMenu,
			   vnameInternGlobalLiteral("VIEW_CLEANUP"));
  vmenuSetItemNotify(menuItem, cleanupMenuItemNoteProc);

  /*
   * Get the icon view from the dialog. Note - within vre, the iconview's
   * Class tag was specified to be "specialIconView".
   */
  theIconView = (viconview *)vdialogFindItem(demoDialog, 
				 vnameInternGlobalLiteral("ICON_VIEW"));
  globalIconView = theIconView;

  /* 
   * Attach a menu to each icon in the icon view.
   */
  viconviewInitIterator(&iterator, theIconView);
  while (viconviewNextIterator(&iterator))
    {
      menu = vmenuClone(popupMenu);
      viconviewSetIconData(viconviewGetIteratorIcon(&iterator), menu);
    }
  viconviewDestroyIterator(&iterator);

  vdialogOpen(demoDialog);
 
  /*
   * Process events until the user ends the demo.
   */
 
  veventProcess();

  /*
   * Do memory cleanup.
   */
  /* destroy all the little menu clones */
  viconviewInitIterator(&iterator, theIconView);
  while (viconviewNextIterator(&iterator))
    {
      vmenuDestroy((vmenu *)viconviewGetIconData(viconviewGetIteratorIcon(&iterator)));
    }
  viconviewDestroyIterator(&iterator);
  vdialogDestroy(demoDialog);
  viconviewDestroyView(globalMoonView);
  vmenuDestroy(popupMenu);

  exit( EXIT_SUCCESS );
  return EXIT_FAILURE;
}  /**  main()  **/



/*********
 * _specialIconViewHandleButtonDown()
 *
 * This function is an override of the vdialogHANDLE_ITEM_BUTTON_DOWN method.
 * It is called to handle every button down event which occurs in our
 * specialIconView.
 **********/
static int _specialIconViewHandleButtonDown(viconview *theIconView, vevent *event)
{
  vdomain           *theDomain;
  vdomainview       *theDomainView;
  vdialogItem       *theDialogItem;
  vdialog           *theDialog;
  vmenu             *menu;
  vdomainObjectSet  *theClickedDomainObject = NULL;
  viconviewIcon     *theClickedIcon;

  vpoint   pt;
  vpoint   domainPoint, iconPoint, displayPoint;
  int      x, y;
  int      result = FALSE;  /* default - event not handled */


  pt.x = veventGetPointerX(event);
  pt.y = veventGetPointerY(event);

  theDialogItem = viconviewGetItem(theIconView);
  theDialog = vdialogDetermineItemDialog(theDialogItem);
  theDomain = viconviewGetDomain(theIconView);
  theDomainView = viconviewGetDomainView(theIconView);

  /*
   * translate the point to domain coordinates.
   */
  domainPoint = pt;
  vdomainviewTranslatePoint(theDomainView, &domainPoint,
			    vdomainviewDIALOG_TO_DOMAIN);

  /*
   * do the hit detection.
   */
  theClickedDomainObject = 
    vdomainObjectsAtPoint(theDomain,
			  &domainPoint,
			  vdomainviewGetSelection(theDomainView),
			  TRUE,
			  vdomainALL,
			  NULL);
  if (vdomainGetObjectSetCount(theClickedDomainObject) >= 1)
    {
      theClickedIcon = 
	viconviewIconFromObject(theClickedDomainObject->objects[0]);
      if (veventGetBinding(event) == vname_Menu)
	{
	  /*
	   * The event is a menubutton event, so we will handle it.
	   * (The user pressed the menu mouse button.)
	   */
	  result = TRUE;

#ifdef vlafCUA
	  if (vlafAppear() == vlafCUA)
	    {
	      /*
	       * For CUA, don't pop up a menu on button down, but record
	       * the cursor position and timestamp for later.
	       */
	      pointX = veventGetPointerX(event);
	      pointY = veventGetPointerY(event);
	      pointT = veventGetTime(event);
	      nomenu = FALSE;
	    }
	  else
	    {
#endif
	      /*
	       * Derive the coordinate at which we want the menu to pop up.
	       * Translate the domain view point to display coordinates.
	       */
	      iconPoint = viconviewGetIconPosition(theClickedIcon);
	      vdomainviewTranslatePoint(theDomainView,
					&iconPoint,
					vdomainviewDOMAIN_TO_DIALOG);
	      vwindowTransformPoint(vdialogGetWindow(theDialog),
				    vwindowGetRoot(),
				    iconPoint.x, iconPoint.y, 
				    &x, &y );
	      vpointSet(x, y, &displayPoint);
	      /*
	       * Open the menu.
	       */
	      menu = viconviewGetIconData(theClickedIcon);
	      vmenuPlaceDefault(menu, displayPoint.x + 20, displayPoint.y);
	      vmenuPopup(menu, event);
#ifdef vlafCUA
	    }
#endif
	}
      else
	{
	  /*
	   * The event is something other than a menubutton event, so
	   * pass it on up to our superclass to handle it.
	   */
	  result = vclassSendSuper(_specialIconViewClass,
				   vdialogHANDLE_ITEM_BUTTON_DOWN, 
				   (theIconView, event));
	}
    }
  else
    {
      /*
       * The button down event did not occur over one of the iconview icons,
       * so we will not handle it here. Pass the event on up to our superclass.
       */
      result = vclassSendSuper(_specialIconViewClass,
			       vdialogHANDLE_ITEM_BUTTON_DOWN, 
			       (theIconView, event));
    }

  vdomainDestroyObjectSet(theClickedDomainObject);

  return(result);
}

#ifdef vlafCUA
/*********
 * _specialIconViewHandleButtonUp()
 *
 * This function is an override of the vdialogHANDLE_ITEM_BUTTON_UP method.
 * It is called to handle every button up event which occurs in our
 * specialIconView.
 *
 * Note that this function is only used with lafCUA.  It isn't attached to
 * the iconview class for motif, openlook, windows, or mac lafs.
 *
 **********/

static int _specialIconViewHandleButtonUp(viconview *theIconView, vevent *event)
{
  vdomain           *theDomain;
  vdomainview       *theDomainView;
  vdialogItem       *theDialogItem;
  vdialog           *theDialog;
  vmenu             *menu;
  vdomainObjectSet  *theClickedDomainObject = NULL;
  viconviewIcon     *theClickedIcon;

  vpoint   pt;
  vpoint   domainPoint, iconPoint, displayPoint;
  int      x, y;
  int      result = FALSE;  /* default - event not handled */

  pt.x = veventGetPointerX(event);
  pt.y = veventGetPointerY(event);

  theDialogItem = viconviewGetItem(theIconView);
  theDialog = vdialogDetermineItemDialog(theDialogItem);
  theDomain = viconviewGetDomain(theIconView);
  theDomainView = viconviewGetDomainView(theIconView);

  /*
   * translate the point to domain coordinates.
   */
  domainPoint = pt;
  vdomainviewTranslatePoint(theDomainView, &domainPoint, vdomainviewTO_DOMAIN);

  /*
   * do the hit detection.
   */
  theClickedDomainObject = 
    vdomainObjectsAtPoint(theDomain,
			  &domainPoint,
			  vdomainviewGetSelection(theDomainView),
			  TRUE,
			  vdomainALL,
			  NULL);
  if (vdomainGetObjectSetCount(theClickedDomainObject) >= 1)
    {
      /*
       * If an icon was button-up'ed on, check for a few things:
       * 1) The menu button was the one released
       * 2) The x & y delta between the up-coordinate and the
       *    down-coordinate is small.  (+/- 2 on both axes here)
       * 3) The nomenu flag isn't set (set by cursor motion beyond a given
       *    distance
       * 4) Less than 1/2 second has elapsed between button down and button
       *    up events.
       * If all these check out, pop up the menu.
       */
      long diffSec;
      unsigned long diffNano;

      vtimestampDiffer(veventGetTime(event), pointT, &diffSec, &diffNano);
      theClickedIcon = 
	viconviewIconFromObject(theClickedDomainObject->objects[0]);
      if ((veventGetBinding(event) == vname_Menu) &&
	  (abs(pointX - veventGetPointerX(event)) < 3) &&
	  (abs(pointY - veventGetPointerY(event)) < 3) &&
	  (nomenu == FALSE) &&
	  (diffSec < 4) /* to prevent overflow on the next line */ &&
	  ((diffSec * vtimestampSECOND + diffNano) <
					veventGetDoubleClickInterval()))
	{
	  /*
	   * The event is a menubutton event, so we will handle it.
	   * (The user pressed the menu mouse button.)
	   */
	  result = TRUE;

	  /*
	   * Derive the coordinate at which we want the menu to pop up.
	   * Translate the domain view point to display coordinates.
	   */
	  iconPoint = viconviewGetIconPosition(theClickedIcon);
	  vdomainviewTranslatePoint(theDomainView,
				    &iconPoint,
				    vdomainviewTO_DIALOG);
	  vwindowTransformPoint(vdialogGetWindow(theDialog),
				vwindowGetRoot(),
				iconPoint.x, iconPoint.y, 
				&x, &y );
	  vpointSet(x, y, &displayPoint);
	  /*
	   * Open the menu.
	   */
	  menu = viconviewGetIconData(theClickedIcon);
	  vmenuPlaceDefault(menu, displayPoint.x + 20, displayPoint.y);
	  vmenuPopup(menu, event);
	}
      else
	{
	  /*
	   * The event is something other than a menubutton event, so
	   * pass it on up to our superclass to handle it.
	   */
	  result = vclassSendSuper(_specialIconViewClass,
				   vdialogHANDLE_ITEM_BUTTON_UP, 
				   (theIconView, event));
	}
    }
  else
    {
      /*
       * The button up event did not occur over one of the iconview icons,
       * so we will not handle it here. Pass the event on up to our superclass.
       */
      result = vclassSendSuper(_specialIconViewClass,
			       vdialogHANDLE_ITEM_BUTTON_UP, 
			       (theIconView, event));
    }

  vdomainDestroyObjectSet(theClickedDomainObject);

  return(result);
}

/*********
 * _specialIconViewHandleDetail()
 *
 * This function is an override of the vdialogHANDLE_ITEM_DETAIL method.
 *
 * If the pointer has moved too far, set a flag indicating no menu.
 *
 * Note that this function is only used with lafCUA.  It isn't attached to
 * the iconview class for motif, openlook, windows, or mac lafs.
 *
 **********/

static int _specialIconViewHandleDetail(viconview *theIconView, vevent *event)
{
  if (nomenu == FALSE)
    if ((abs(pointX - veventGetPointerX(event)) > 2) ||
	(abs(pointY - veventGetPointerY(event)) > 2))
      nomenu = TRUE;

  return vclassSendSuper(_specialIconViewClass,
			 vdialogHANDLE_ITEM_DETAIL,
			 (theIconView, event));
}

/*********
 * _specialIconViewHandleDrag()
 *
 * This function is an override of the vdialogHANDLE_ITEM_DRAG method.
 *
 * If the pointer has moved too far, set a flag indicating no menu.
 *
 * Note that this function is only used with lafCUA.  It isn't attached to
 * the iconview class for motif, openlook, windows, or mac lafs.
 *
 **********/

static int _specialIconViewHandleDrag(viconview *theIconView, vevent *event)
{
  if (nomenu == FALSE)
    if ((abs(pointX - veventGetPointerX(event)) > 2) ||
	(abs(pointY - veventGetPointerY(event)) > 2))
      nomenu = TRUE;

  return vclassSendSuper(_specialIconViewClass,
			 vdialogHANDLE_ITEM_DRAG,
			 (theIconView, event));
}

#endif /* vlafCUA */

/********
 * shutdownMain()
 *********/
static void shutdownMain()
{

  veventStopProcessing();
}


/********
 * viewByIconMenuItemNoteProc()
 *
 * The Notify function for the View menu "by Icon" item.
 *********/
static void viewByIconMenuItemNoteProc(vmenuItem *item, vevent *event)
{
  viconviewSetView(globalIconView, viconviewGetIconView());
}


/********
 * viewByNameMenuItemNoteProc()
 *
 * The Notify function for the View menu "by Name" item.
 *********/
static void viewByNameMenuItemNoteProc(vmenuItem *item, vevent *event)
{
  viconviewSetView(globalIconView, viconviewGetNameView());
}


/********
 * viewByMoonMenuItemNoteProc()
 *
 * The Notify function for the View menu "by Moon" item.
 *********/
static void viewByMoonMenuItemNoteProc(vmenuItem *item, vevent *event)
{
  viconviewSetView(globalIconView, globalMoonView);
}


/********
 * cleanupMenuItemNoteProc()
 *
 * The Notify function for the View menu "Clean Up" item.
 *********/
static void cleanupMenuItemNoteProc(vmenuItem *item, vevent *event)
{
  viconviewCleanup(globalIconView);
}


/********
 * shutdownMenuItemNoteProc()
 *
 * The Notify function for the File menu "Quit" item.
 *********/
static void shutdownMenuItemNoteProc(vmenuItem *item, vevent *event)
{

  shutdownMain();
}


/**********
 * demoDialogNotify:
 *
 * The Notify function for the dialog itself. This function handles the
 * case when the user ends the demo via the window manger.
 **********/
static void demoDialogNotify
  (vdialog                      *dialog,
   vevent                       *event)
{
 
  if (veventGetType(event) == veventWINDOW_STATE && veventIsClose(event))
    {
      shutdownMain();
    }
 
}  /**  demoDialogNotify()  **/

/**********
 * _moonViewGeometryCalc
 *
 * positions the image and name for an icon when the "Moon View"
 * is active.  this is contrived and silly.  all it does is place
 * the name centered above the image rather than centered below.
 **********/
static void _moonViewGeometryCalc(
  viconview		*iconView,
  viconviewView		*view,
  viconviewIcon		*icon,
  vpoint		*position,
  vrect			*imageRect,
  vrect			*nameRect
  )
{
  int		w, h;
  vimage	*image;
  vfont		*font;
  vrect		sRect;

  image = viconviewDetermineIconImage(icon, view);

  w = vimageGetWidth(image);
  h = vimageGetHeight(image);

  vrectSet(position->x, position->y,
	   w + 2 * viconviewICON_BORDER,
	   h + 2 * viconviewICON_BORDER, imageRect);

  font   = vdialogDetermineItemFont(viconviewGetItem(iconView));

  if (icon->name != NULL) {
    vfontStringBounds(font, icon->name, &sRect);
    w = sRect.w + 4;
  } else
    w = 2;
  vfontBounds(font, &sRect);
  h = sRect.h + 1;

  vrectSet(imageRect->x + (imageRect->w / 2) - (w / 2),
	   imageRect->y + imageRect->h, w, h, nameRect);
}  /**  end  _moonViewGeometryCalc  **/

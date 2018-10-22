/* $Id: tracker.c,v 1.5 1997/10/17 21:52:33 gregt Exp $ */
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

/************************************************************/
/*                                                          */
/*              TRACKER                                     */
/*                                                          */
/* This program is a demonstration of some basic animation  */
/* done using a vtimer to update the positions of some     */
/* domain objects. This program also illustrates how to     */
/* subclass a domain to override some methods. The images   */
/* in this program, except the GIF image of Mars, were      */
/* drawn using the VRE image editor.                        */
/*                                                          */
/* Another possible item of interest is the fact that the   */
/* the backgrounds images take 5-10 seconds to load the     */
/* first time they are brought it but are cached after that,*/
/* allowing for very fast background switching the second   */
/* time around. It would be a good enhancement to do this   */
/* loading at startup (with an appropriate splash) rather   */
/* than when the BACKGROUND button is pressed the first     */
/* time.                                                    */
/*                                                          */
/* As an aside, the VR file is quite large (900K) due to the*/
/* 900x900 GIF file stored as "image2". Replacing this with */
/* a normal vimage would reduce the VR file to about 90K.   */
/*                                                          */
/************************************************************/

/* Galaxy headers */
#include <vport.h>
#include vgalaxyHEADER

#define DOMAIN_SIZE 900
#define TAG(s)  vnameInternGlobalLiteral ((s))

/* Most of the info below rightly belongs in a header file. */

/* forward references */
static void dialogNoteProc (vdialog *dialog, vevent *event);

static void goButtonNoteProc   (vbutton *button, vevent *event);
static void infoButtonNoteProc (vbutton *button, vevent *event);
static void gridButtonNoteProc (vbutton *button, vevent *event);
static void backButtonNoteProc (vbutton *button, vevent *event);
static void quitButtonNoteProc (vbutton *button, vevent *event);

static void ObjectMove   (vtimer *);  /* Updates location of domain objects.*/
static void Adjust_Timer (void);      /* Turns the timer on and off.        */

/* Globals */

int GRID_STATE = 0;  /* These flags are toggled by the buttons on */
int INFO_STATE = 0;  /* the GUI. They control what is displayed   */
int BACK_STATE = 0;  /* in the domain area.                       */
int TIME_STATE = 0;

int X_LIMIT,Y_LIMIT;

vdomainObject *object0; /* Five objects will be created in the domain.*/
vdomainObject *object1;      
vdomainObject *object2;      
vdomainObject *object3;      
vdomainObject *object4;      

vdialog       *dialog;
vdomain       *domain;
vdomainview   *domainView;
vdomainitem   *domainItem;
vresource      resource;
vwindow       *win;

vimage        *background_image_1; /* The background images for */
vimage        *background_image_2; /* the domain.               */

vimage        *top_image_0; /* These are the icons used for the */
vimage        *top_image_1; /* domain objects. They will be read*/
vimage        *top_image_2; /* in from the VR file.             */
vimage        *top_image_3;
vimage        *top_image_4;

/****************
* Domain Stuff  *
****************/

/* Domain procedures that don't require sub-classing. */
void  myDrawObject     (vdomainview* domainView, vdomainObject *object  );
void  myDrawSelection  (vdomainview* DOMAINView, vdomainObject *object  );
vbool myRectIntersect  (vdomain *domain, vdomainObject *object, vrect *r);

/* Domain procedures that do require sub-classing. */
void myDrawBackground (vdomainitem* domainItem);
void myDragOutline    (vdomainitem *domainItem, vrect* rects, int numRects,
                         vrect *limitRect, vpoint *pinAmount);
int  myDomainViewHandleItemButtonDown(vdomainitem* domainItem,vevent* event);
 
vdomainitemClass* mydomainclass;

/************************************************************/
/*                                                          */
/*                 MAIN PROGRAM                             */
/*                                                          */
/************************************************************/
int main (int argc, char *argv[])

 {
 vbutton           *button;
 vdomainObjectSet  *objectSet;
 vrect              bounds;

 /* Initialize Galaxy */
 vstartup (argc, argv);

 /* More Domain sub-class stuff */
 mydomainclass = vclassReproduce(vdomainitemGetDefaultClass());
 vclassSetNameScribed(mydomainclass, vcharScribeLiteral("mydomainitem"));
 /* A "mydomainitem" was created in the VR file. */

 vclassSet(mydomainclass, vdomainviewBACKGROUND,   myDrawBackground);
 vclassSet(mydomainclass, vdomainviewDRAG_OUTLINE, myDragOutline   );
 vclassSet(mydomainclass, vdialogHANDLE_ITEM_BUTTON_DOWN,
                          myDomainViewHandleItemButtonDown);
 /*
  * Load the dialog from the application
  * resource file.
  */
 resource = vresourceGet (vapplicationGetResources (vapplicationGetCurrent()),
			   TAG ("DomainDialog"));
 dialog = vdialogLoad (resource);
 vdialogSetNotify (dialog, dialogNoteProc);

 /*
  * Load the images from the application
  * resource file.
  */
 resource = vresourceGet (vapplicationGetResources (vapplicationGetCurrent()),
			  TAG("image1"));
 background_image_1 = vimageLoad (resource);

 resource = vresourceGet (vapplicationGetResources (vapplicationGetCurrent()),
			  TAG("image2"));
 background_image_2 = vimageLoad (resource);


 resource = vresourceGet (vapplicationGetResources (vapplicationGetCurrent()),
			  TAG("top0"));
 top_image_0 = vimageLoad(resource);

 resource = vresourceGet (vapplicationGetResources (vapplicationGetCurrent()),
			  TAG("top1"));
 top_image_1 = vimageLoad(resource);

 resource = vresourceGet (vapplicationGetResources (vapplicationGetCurrent()),
			  TAG("top2"));
 top_image_2 = vimageLoad(resource);

 resource = vresourceGet (vapplicationGetResources (vapplicationGetCurrent()),
			  TAG("top3"));
 top_image_3 = vimageLoad(resource);

 resource = vresourceGet (vapplicationGetResources (vapplicationGetCurrent()),
			  TAG("top4"));
 top_image_4 = vimageLoad(resource);

 /*
  * Find the buttons and attach their notifies.
  *
  */
 button = (vbutton *) vdialogFindItem (dialog, TAG ("quit"));
 vbuttonSetNotify (button, quitButtonNoteProc);

 button = (vbutton *) vdialogFindItem (dialog, TAG ("back"));
 vbuttonSetNotify (button, backButtonNoteProc);

 button = (vbutton *) vdialogFindItem (dialog, TAG ("info"));
 vbuttonSetNotify (button, infoButtonNoteProc);

 button = (vbutton *) vdialogFindItem (dialog, TAG ("go"));
 vbuttonSetNotify (button, goButtonNoteProc);

 button = (vbutton *) vdialogFindItem (dialog, TAG ("grid"));
 vbuttonSetNotify (button, gridButtonNoteProc);

 /* Set up the domain. */

 domainItem = (vdomainitem*)vdialogFindItem(dialog,TAG("domain"));
 domain     = vdomainitemGetDomain(domainItem);
 domainView = vdomainitemGetView(domainItem);

 vdomainviewSetOffscreenDrawing  (domainView, TRUE);
 vdomainviewSetDrawObjectProc    (domainView, myDrawObject);
 vdomainviewSetDrawSelectionProc (domainView, myDrawSelection);
 vdomainSetRectIntersectFunc     (domain,     myRectIntersect);

 /* Set up objects in the domain.                */
 /* Five objects are hard coded into the domain. */
 /* Each is given its own "type" to identify it. */

 objectSet = vdomainCreateObjectSet(NULL);

 vrectSet                   (110,350,70,50, & bounds);
 object0 = vdomainAddObject (domain);
 vdomainSetObjectBounds     (domain, vdomainObjectToSet (object0), &bounds);
 vdomainAddToObjectSet      (&objectSet, object0);
 vdomainSetObjectType       (domain, vdomainObjectToSet(object0),0);

 vrectSet                   (200,90,65,90, & bounds);
 object1 = vdomainAddObject (domain);
 vdomainSetObjectBounds     (domain, vdomainObjectToSet (object1), &bounds);
 vdomainAddToObjectSet      (&objectSet, object1);
 vdomainSetObjectType       (domain, vdomainObjectToSet(object1),1);

 vrectSet                   (10,450,70,50, & bounds);
 object2 = vdomainAddObject (domain);
 vdomainSetObjectBounds     (domain, vdomainObjectToSet (object2), &bounds);
 vdomainAddToObjectSet      (&objectSet, object2);
 vdomainSetObjectType       (domain, vdomainObjectToSet(object2),2);

 vrectSet                   (100,10,55,80, & bounds);
 object3 = vdomainAddObject (domain);
 vdomainSetObjectBounds     (domain, vdomainObjectToSet (object3), &bounds);
 vdomainAddToObjectSet      (&objectSet, object3);
 vdomainSetObjectType       (domain, vdomainObjectToSet(object3),3);

 vrectSet                   (310,50,55,45, & bounds);
 object4 = vdomainAddObject (domain);
 vdomainSetObjectBounds     (domain, vdomainObjectToSet (object4), &bounds);
 vdomainAddToObjectSet      (&objectSet, object4);
 vdomainSetObjectType       (domain, vdomainObjectToSet(object4),4);

 vdomainShowObjects         (domain, objectSet);
 vdomainDestroyObjectSet    (objectSet);

 /* Center and Open the dialog */
 win = vdialogGetWindow(dialog);
 vwindowPlace(win, vwindowGetRoot(), vrectPLACE_CENTER, vrectPLACE_CENTER);
 vdialogOpen (dialog);

 /* Enter the event loop */
 veventProcess ();

 /* destroy the timer if it still exists */
 if (TIME_STATE == 1)
   Adjust_Timer ();

 /* Return resources to the system */
 vdialogDestroy (dialog);

 vimageDestroy (background_image_1);
 vimageDestroy (background_image_2);
 vimageDestroy (top_image_0);
 vimageDestroy (top_image_1);
 vimageDestroy (top_image_2);
 vimageDestroy (top_image_3);
 vimageDestroy (top_image_4);

 exit (EXIT_SUCCESS);
 return EXIT_FAILURE;
 }

/***************************************************************
 *  QUIT IF DIALOG IS CLOSED
 *
 ***************************************************************/
static void dialogNoteProc (vdialog *dialog, vevent *event)
 {
 int      et;
 et = veventGetType (event);
 if (et == veventWINDOW_STATE && veventIsClose (event))
     veventStopProcessing ();
 }

/***************************************************************
 *  QUIT IF "QUIT" BUTTON IS PRESSED
 *
 ***************************************************************/
static void quitButtonNoteProc (vbutton *button, vevent *event)
 {
 veventStopProcessing ();
 }

/***************************************************************
 *  CHANGE BACKGROUND 
 *
 *  Cycle through the background states.
 *  Trigger a redraw of the domain as well.
 ***************************************************************/

static void backButtonNoteProc (vbutton *button, vevent *event)
 {
 switch (BACK_STATE)
   {
   case 0: BACK_STATE = 1; break;
   case 1: BACK_STATE = 2; break;
   case 2: BACK_STATE = 0; break;
   default:BACK_STATE = 0; break;
   }
 vdialogInvalItem (vdomainitemGetItem(domainItem), vwindowINVAL_OPAQUE);
 }

/***************************************************************
 *  TOGGLE GRID        
 *
 *  Alternate grid states.
 *  Trigger a redraw of the domain as well.
 ***************************************************************/

static void gridButtonNoteProc (vbutton *button, vevent *event)
 {
 GRID_STATE = (GRID_STATE == 1) ?  0 : 1;
 vdialogInvalItem (vdomainitemGetItem(domainItem), vwindowINVAL_OPAQUE);
 }

/***************************************************************
 *  TOGGLE TEXT           
 *
 *  Cycle through the information states.
 *  Trigger a redraw of the domain as well.
 ***************************************************************/

static void infoButtonNoteProc (vbutton *button, vevent *event)
 {
 INFO_STATE = (INFO_STATE == 1) ?  0 : 1;
 vdialogInvalItem (vdomainitemGetItem(domainItem), vwindowINVAL_OPAQUE);
 }

/***************************************************************
 *  TOGGLE MOVEMENT 
 *
 *  Alternate the movement states.
 *  Turn the timer on or off accordingly.
 ***************************************************************/
static void goButtonNoteProc (vbutton *button, vevent *event)
 {
 if (TIME_STATE ==0)
   vbuttonSetTitleScribed (button, vcharScribeLiteral(" S T O P "));
 else
   vbuttonSetTitleScribed (button, vcharScribeLiteral("   G O   "));

 Adjust_Timer ();
 }

/***************************************************************
 *  DRAW OBJECT                                                *
 *                                                             *
 *  Draw a given object on the domain. This is called whenever *
 *  any object needs to be drawn.                              *
 *  The "type" of the object is used to customize the display. *
 ***************************************************************/

void myDrawObject       (vdomainview * domainView, vdomainObject *object) 
 {
 vcolor *saveColor;
 int     TYPE;
 const vrect  *bounds;

 TYPE   = vdomainGetObjectType (domain,object);
 bounds = vdomainGetObjectBounds (vdomainviewGetDomain(domainView), object);

 vdrawGSave();
 vdrawRectsClip(bounds, 1);
 vdrawSetFunction(vdrawFUNC_COPY);
 vdrawSetLineWidth(2);

 vdrawMoveTo(bounds->x+30,bounds->y+30);

 if (BACK_STATE == 2)
   vdrawSetColor(vcolorGetWhite());
 else
   vdrawSetColor(vcolorGetBlack());

 switch (TYPE)
   {
   /* Draw the icon. */
   case 0: vdrawImageCompositeIdent (top_image_0); break;
   case 1: vdrawImageCompositeIdent (top_image_1); break;
   case 2: vdrawImageCompositeIdent (top_image_2); break;
   case 3: vdrawImageCompositeIdent (top_image_3); break;
   case 4: vdrawImageCompositeIdent (top_image_4); break;
   default:vdrawImageCompositeIdent (top_image_0); break;
   }

 if (INFO_STATE)
  {/* Display text data along side the objects.            */

  vdrawMoveTo(bounds->x,bounds->y+15);
  switch (vdomainGetObjectType (domain,object))
   {
   case 0: vdrawScribedShow(vcharScribeLiteral("Vel: 9")); break;
   case 1: vdrawScribedShow(vcharScribeLiteral("Vel: 6")); break;
   case 2: saveColor = vdrawGetColor();
           vdrawFSetRGBColor(0.75,0.0,0.0);
           vdrawScribedShow(vcharScribeLiteral("Vel: 14"));            
           vdrawSetColor(saveColor); 
           break;
   case 3: vdrawScribedShow(vcharScribeLiteral("Vel: 3")); break;
   case 4: vdrawScribedShow(vcharScribeLiteral("Vel: 6")); break;
   default:vdrawScribedShow(vcharScribeLiteral("? ")); break;
   }
  vdrawMoveTo(bounds->x,bounds->y);
  switch (TYPE)
   {
   case 0: vdrawScribedShow(vcharScribeLiteral("Dir: E")); break;
   case 1: vdrawScribedShow(vcharScribeLiteral("Dir: S")); break;
   case 2: vdrawScribedShow(vcharScribeLiteral("Dir: W")); break;
   case 3: vdrawScribedShow(vcharScribeLiteral("Dir: N")); break;
   case 4: vdrawScribedShow(vcharScribeLiteral("Dir: E")); break;
   default:vdrawScribedShow(vcharScribeLiteral(" ")); break;
   }
  vdrawMoveTo(bounds->x+2,bounds->y+bounds->h-15);
  switch (TYPE)
   {
   case 0: vdrawScribedUnderlineShow(vcharScribeLiteral("Zero")); break;
   case 1: vdrawScribedUnderlineShow(vcharScribeLiteral("One ")); break;
   case 2: vdrawScribedUnderlineShow(vcharScribeLiteral("Two ")); break;
   case 3: vdrawScribedUnderlineShow(vcharScribeLiteral("Three"));break;
   case 4: vdrawScribedUnderlineShow(vcharScribeLiteral("Four")); break;
   default:vdrawScribedShow(vcharScribeLiteral("??? ")); break;
   }
  }
 vdrawGRestore();
 }

/***************************************************************
 *  MOVE OBJECTS                                               *
 *                                                             *
 * Called every time that the timer goes off, this procedure   *
 * updates the location of the domain objects.                 *
 ***************************************************************/

static void ObjectMove (vtimer *timer)
 {
 vrect bounds;
 vrect *dv_rect; /* Domain view rectangle. */

 /* Set the view limits for wrap-around. */
 dv_rect = vdomainviewGetViewArea (domainView);   
 X_LIMIT  = dv_rect->x+dv_rect->w+80;
 Y_LIMIT  = dv_rect->y+dv_rect->h+80;

 /* Objects are allowed to go up to 80 points off the domain to allow for
    smooth transtitions (rather than blinking out at the border).      */

 /* Move the objects */

 vdomainMoveObjects(domain, vdomainObjectToSet (object0), 9, 0, vdomainRELATIVE);
 vdomainMoveObjects(domain, vdomainObjectToSet (object1), 0,-6, vdomainRELATIVE);
 vdomainMoveObjects(domain, vdomainObjectToSet (object2),-14,0, vdomainRELATIVE);
 vdomainMoveObjects(domain, vdomainObjectToSet (object3), 0, 3, vdomainRELATIVE);
 vdomainMoveObjects(domain, vdomainObjectToSet (object4),-6, 0, vdomainRELATIVE);

 /* Wrap around */

 bounds = *vdomainGetObjectBounds (vdomainviewGetDomain(domainView), object0);
 if (bounds.x > X_LIMIT)
   {
   bounds.x =  -80;
   vdomainSetObjectBounds (domain, vdomainObjectToSet (object0), &bounds);
   }

 bounds = *vdomainGetObjectBounds (vdomainviewGetDomain(domainView), object1);
 if (bounds.y < -80)
   {
   bounds.y = Y_LIMIT;
   vdomainSetObjectBounds (domain, vdomainObjectToSet (object1), &bounds);
   }

 bounds = *vdomainGetObjectBounds (vdomainviewGetDomain(domainView), object2);
 if (bounds.x < -80)
   {
   bounds.x = X_LIMIT;
   vdomainSetObjectBounds (domain, vdomainObjectToSet (object2), &bounds);
   }

 bounds = *vdomainGetObjectBounds (vdomainviewGetDomain(domainView), object3);
 if (bounds.y > Y_LIMIT)
   {
   bounds.y =  -80;
   vdomainSetObjectBounds (domain, vdomainObjectToSet (object3), &bounds);
   }

 bounds = *vdomainGetObjectBounds (vdomainviewGetDomain(domainView), object4);
 if (bounds.x < -80)
   {
   bounds.x = X_LIMIT;
   vdomainSetObjectBounds (domain, vdomainObjectToSet (object4), &bounds);
   }
 }

/***************************************************************
 * TIMER                                                       *
 *                                                             *
 * Creates and starts a recurrent time to trigger animation.   *
 * "ObjectMove" is called each time the TIMER goes off.              *
 ***************************************************************/

static void Adjust_Timer ()
 {
 static  vtimer   *timer;

 if (TIME_STATE == 0)
   { /* Move the objects every 0.4 seconds. */
   timer =  vtimerCreate();
   vtimerSetRecurrent (timer);
   vtimerSetPeriod    (timer, 0,  40000000);
   vtimerSetSyncProc  (timer, vwindowSyncEvents);
   vtimerSetNotify    (timer, ObjectMove);
   vtimerStart        (timer);
   TIME_STATE  = 1;
   }
 else
   {
   vtimerStop    (timer);
   vtimerDestroy (timer);
   TIME_STATE  = 0;
   }
 }

/***************************************************************
 * DRAW BACKGROUND                                             *
 *                                                             *
 * Draw the background image and grid line depending on the    *
 * current value of the BACK_STATE and GRID_STATE flags.       * 
 ***************************************************************/

void myDrawBackground(vdomainitem* domainItem)
 {
 int     i;

 vdrawGSave();
 vdrawSetLineWidth(0);

 vdrawMoveTo( 0, 0); /* Set the background image. */
 if (BACK_STATE == 1) vdrawImageCompositeIdent( background_image_1 );
 else if (BACK_STATE == 2) vdrawImageCompositeIdent( background_image_2 );
 else
   {
   vcolor	*save = vdrawGetColor();

   vdrawSetColor(vdrawGetComplement());
   vdrawRectsFill(vdomainviewGetViewArea(vdomainitemGetView(domainItem)), 1);
   vdrawSetColor(save);
   }

 vdrawSetFunction(vdrawFUNC_COPY);
 vdrawNewPath();

 if (GRID_STATE) /* Draw the grid. */
   {
   /* Draw the grid in black if the current image is #2.*/
   if (BACK_STATE == 2)
     vdrawSetColor(vcolorGetBlack());
   else
     vdrawSetColor(vcolorGetWhite());

   for (i=0; i<= DOMAIN_SIZE; i = i+50)
     {
     vdrawMoveTo(  0, i );
     vdrawLineTo(DOMAIN_SIZE, i );
     vdrawMoveTo( i ,  0);
     vdrawLineTo( i ,DOMAIN_SIZE);
     }
   vdrawStroke();
   }

 vdrawGRestore();
 }

/***************************************************************
 * OBJECT INTERSECTION (for selection)                         *
 *                                                             *
 *   This is provided so that an object cannot be selected     * 
 * unless the icon part is selected (ie. the text part of an   *
 * object doesn't count).                                      *
 *                                                             *
 ***************************************************************/

vbool myRectIntersect  (vdomain *domain, vdomainObject *object, vrect *r) 
 {
 const vrect  *bounds;

 bounds = vdomainGetObjectBounds (domain, object);

 if ( (r->x > bounds->x+30       ) &&
      (r->x < bounds->x+bounds->w) &&
      (r->y > bounds->y+30       ) &&
      (r->y < bounds->y+bounds->h) )
   return TRUE;

 /* This kludge allows for group selections and initial positioning.*/
 if ( (r->w >1) || (r->h >1))
   return TRUE;

  return FALSE;
 }



/* The following stubs could be flushed out if the user desires to
   further alter the default behavior of the domain item. */

/***************************************************************
 * HANDLE BUTTON DOWN EVENT                                    *
 *                                                             *
 *                                                             *
 ***************************************************************/
 
int myDomainViewHandleItemButtonDown(vdomainitem* domainItem, vevent* event)
 {
 vclassSendSuper(mydomainclass, vdialogHANDLE_ITEM_BUTTON_DOWN,
                (domainItem, event));
 /* Add Code Here */
 return TRUE;
 }

/***************************************************************
 * DRAW DRAG OUTLINE                                           *
 *                                                             *
 *                                                             *
 ***************************************************************/
 
void myDragOutline(vdomainitem *domainItem, vrect* rects, int numRects,
                    vrect *limitRect, vpoint *pinAmount)
 {
 vclassSendSuper(mydomainclass, vdomainviewDRAG_OUTLINE,
                (domainItem, rects, numRects, limitRect, pinAmount));
 /* Add Code Here */
 }

/***************************************************************
 *  DRAW SELCTION                                              *
 *                                                             *
 *                                                             *
 ***************************************************************/

void myDrawSelection  (vdomainview* domainView, vdomainObject *object)
 {
 /* Add Code Here */
 }

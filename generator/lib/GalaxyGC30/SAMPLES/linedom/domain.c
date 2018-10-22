/******************************************************************************
*               (c) Copyright 1991,92,93 Visix Software, Inc.              
*                           All rights reserved.                           
* The following Sample Code is provided for your reference purposes in     
* connection with your use of the Galaxy Application Environment (TM)      
* software product which you have licensed from Visix Software, Inc.       
* ("Visix"). The Sample code is provided to you without any warranty of any
* kind and you agree to be responsible for the use and/or incorporation    
* of the Sample Code into any software product you develop. You agree to   
* fully and completely indemnify and hold Visix harmless from any and all  
* loss, claim, liability or damages with respect to your use of the Sample 
* Code.                                                                    
*                                                                          
* Subject to the foregoing, you are permitted to copy, modify, and         
* distribute the Sample Code for any purpose, and without fee, provided    
* that (i) a copyright notice in the in the form of "Copyright 1992 Visix  
* Software Inc., 11440 Commerce Park Drive, Reston, VA  22091. All Rights  
* Reserved" appears in all copies, (ii) both the copyright notice and this 
* permission notice appear in all supporting documentation and (iii) you   
* are a valid licensee of The Galaxy Application Environment.              
*                                                                          
******************************************************************************
*	$Header: /visix/vsx/arch/src/vsamples/c/linedom/RCS/domain.c,v 1.7 1997/11/12 21:46:37 gregt Exp $
*
*       domain.c
*
*       This file contains all Galaxy domain related functions.  It
*       contains functions related to both domains and domainviews (since
*       we are always going to work with both together).  More sophisticated
*       programs might want to separate out domain functions from domainview
*       functions.
*
*       (C) Copyright 1992 Visix Software Inc.
*           All Rights Reserved
*
******************************************************************************/

/* Galaxy Includes */
#include <vgalaxy.h>

/* Application Includes */
#include "domain.h"

/*******************************************************************/
/*                  Private variables                              */
/*******************************************************************/

#define POINT_WIDTH   3          /* really half the point width */
#define LINE_WIDTH    1         
        
/*******************************************************************/
/*                  Private functions                              */
/*******************************************************************/

/*
 *  _domainDrawMyObject
 *
 *  The routine that knows how to draw the object types. It does not
 *  call vdrawStroke itself (well, ok, the rectangle drawing does implicitly)
 *  since the caller might want to do some other drawing.
 *
 */

static void _domainDrawMyObject (vdomain *domain, myDomainObject *myObject,
				 int dx, int dy, vdrawcontext *contextOrig)

{
  vdrawcontext	*context = vdrawcontextClone(contextOrig);
  const vrect	*bounds = vdomainGetObjectBounds(domain,
						 myObject->domainObject);
  vrect		 rect;

  vrectSet(bounds->x + dx, bounds->y + dy, bounds->w, bounds->h, &rect);
  vdrawcontextClipRectangles(context, &rect, 1);

  if (myObject->objectType == myDomainObjectLINE) {
    vdrawpenSetLineWidth(vdrawcontextGetPen(context), LINE_WIDTH);
    vdrawcontextSetCurrentPoint(context, myObject->point1.x + dx,
				myObject->point1.y + dy);
    vdrawcontextDrawLineTo(context, myObject->point2.x + dx,
			   myObject->point2.y + dy);
  }
  else {
    vdrawpenSetLineWidth(vdrawcontextGetPen(context), 1);
    vrectSet(myObject->point1.x + dx - POINT_WIDTH,
	     myObject->point1.y + dy - POINT_WIDTH,
	     2 * POINT_WIDTH,
	     2 * POINT_WIDTH, &rect);
    vdrawcontextDrawRectanglesInside(context, &rect, 1);
  }

  vdrawcontextDestroy(context);
}

/*
 *  _domainDrawObjectProc
 *
 *  The draw proc for the domain view.  We'll just pass this on to our low 
 *  level draw procedure.
 *
 */

static void _domainDrawObjectProc (vdomainview *domainview,
				   vdomainObject *object,
				   vdrawcontext *context)

{
  vdomain        *domain = vdomainviewGetDomain (domainview);
  myDomainObject *myObject;

  myObject = vdomainGetObjectData (domain, object);

  _domainDrawMyObject (domain, myObject, 0, 0, context);
}

/*
 *  _domainDrawSelectionProc
 *
 *  This is how we draw a selection.  In our case, we draw a box showing
 *  the bounding rectangle.
 *
 */

static void _domainDrawSelectionProc (vdomainview *domainview,
				      vdomainObject *object,
				      vdrawcontext *context)

{
  int		 saveFunc;
  double	 saveWidth;

  saveFunc = vdrawpenGetDrawingFunction(vdrawcontextGetPen(context));
  saveWidth = vdrawpenGetLineWidth(vdrawcontextGetPen(context));

  vdrawpenSetDrawingFunction(vdrawcontextGetPen(context), vdrawFUNC_INVERT);
  vdrawpenSetLineWidth(vdrawcontextGetPen(context), 1);

  vdrawcontextDrawRectanglesInside(context,
				   vdomainGetObjectBounds(
					      vdomainviewGetDomain(domainview),
					      object),
				   1);

  vdrawpenSetDrawingFunction(vdrawcontextGetPen(context), saveFunc);
  vdrawpenSetLineWidth(vdrawcontextGetPen(context), saveWidth);
}

/*
 *  _domainAdjustBoundsFixedLeft
 *
 *  Figure out the new bounding rectangle for the object keeping point1
 *  fixed.  It's only legal to call this with a line object.
 *
 */

static void _domainAdjustBoundsFixedLeft (vdomain *domain, myDomainObject 
					  *leftObject)

{

  vrect     rect;

  rect = *vdomainGetObjectBounds (domain, leftObject->domainObject);

  leftObject->point2 = leftObject->connection2->point1;
  vpointSetRect (&leftObject->point1, &leftObject->point2, &rect);
  vrectInset (&rect, -LINE_WIDTH, -LINE_WIDTH, &rect);
  vdomainSetObjectBounds (domain,
			  vdomainObjectToSet (leftObject->domainObject),
			  &rect);

}
				  
/*
 *  _domainAdjustBoundsFixedRight
 *
 *  Figure out the new bounding rectangle for the object keeping point2
 *  fixed.  It's only legal to call this with a line object.
 *
 */

static void _domainAdjustBoundsFixedRight (vdomain *domain, myDomainObject 
					  *rightObject)

{

  vrect     rect;

  rect = *vdomainGetObjectBounds (domain, rightObject->domainObject);

  rightObject->point1 = rightObject->connection1->point2;
  vpointSetRect (&rightObject->point1, &rightObject->point2, &rect);
  vrectInset (&rect, -LINE_WIDTH, -LINE_WIDTH, &rect);
  vdomainSetObjectBounds (domain,
			  vdomainObjectToSet (rightObject->domainObject),
			  &rect);

}
				  
/*
 *  _domainMoveObserver
 *
 *  We observer moves and trigger other objects to move based on this. We use
 *  an observer instead of the Move event because it's not a good idea to move
 *  domain objects inside of a domain event handler.  The observer isn't called
 *  until the event handling is complete so it is safe to cause other objects to
 *  move.
 *
 */

static void _domainMoveObserver (vdomainObserver *ob, vdomainObjectSet *objectSet,
				  vpoint *newPosition, int positioning, int before)

{

  vdomain                  *domain;
  vdomainObjectSetIterator  iterator;
  myDomainObject           *myObject;
  myDomainObject           *leftObject;
  myDomainObject           *rightObject;
  vdomainObject            *object;
  vpoint                    diff;
  vrect                     rect;
  if (before)
    return;

  domain = vdomainGetObserverOwner(ob);

  vdomainInitObjectSetIterator (&iterator, objectSet);

  while (vdomainNextObjectSetIterator (&iterator)) {

    object = vdomainGetObjectSetIteratorObject (&iterator);
    myObject = vdomainGetObjectData (domain, object);
    if (myObject->amMoving)
      continue;

    /* we set this so when we move our neighbor it won't try to move us */
    myObject->amMoving = TRUE;

    if (positioning == vdomainABSOLUTE) {
      rect = *vdomainGetObjectBounds (domain, object);
      diff.x  = newPosition->x - rect.x;
      diff.y  = newPosition->y - rect.y;
    }
    else {
      diff = *newPosition;
    }
    vpointMAdd (&myObject->point1, &diff, &myObject->point1);
    vpointMAdd (&myObject->point2, &diff, &myObject->point2);

    /* our move might cause our left neighbor to move */
    leftObject = myObject->connection1;
    if (leftObject != NULL && !leftObject->amMoving) {
      if (leftObject->objectType == myDomainObjectPOINT)
        vdomainMoveObjects (domain, vdomainObjectToSet (leftObject->domainObject), 
			    diff.x, diff.y, vdomainX_RELATIVE | vdomainY_RELATIVE);
      else 
        _domainAdjustBoundsFixedLeft (domain, leftObject);
    }

    /* our move might cause our right neighbor to move */
    rightObject = myObject->connection2;
    if (rightObject != NULL && !rightObject->amMoving) {
      if (rightObject->objectType == myDomainObjectPOINT)
        vdomainMoveObjects (domain, vdomainObjectToSet (rightObject->domainObject), 
			    diff.x, diff.y, vdomainX_RELATIVE | vdomainY_RELATIVE);
      else
        _domainAdjustBoundsFixedRight (domain, rightObject);
    }

    myObject->amMoving = FALSE;

  }

}

/*
 *  _domainTrackHandler
 *
 *  Track the object movement.  Draw "phantom" lines for all connections.  We
 *  don't want to update the actual domain objects during tracking so we draw
 *  directly into the domain shwoing where the connections would go.  This track
 *  handler only tracks domain objects.  You can track mouse movement in the
 *  domain here also (say to show where to create new objects in the domain)
 *  but we don't do that here to avoid complicating the example.  See microdraw
 *  for examples of that kind of tracking.
 *
 */

static vbool _domainTrackHandler (vdomainview *view, vdomainviewTrackEvent *event)

{
  vdrawcontext		   *context = event->context;
  vdomain                  *domain;
  vdomainObject            *object;
  myDomainObject           *myObject;
  myDomainObject           *leftObject;
  myDomainObject           *rightObject;
  vdomainObjectSetIterator  iterator;
  vpoint                    difference;
  vpoint                    point1;
  vpoint                    point2;
  int			    saveFunc;
  double		    saveWidth;

  if (event->state == vdomainviewTRACK_START ||
      event->state == vdomainviewTRACK_END)
    return TRUE;

  if (event->dragObjects == NULL)
    return TRUE;

  domain = vdomainviewGetDomain (view);

  vpointMSub (&event->currentPosition, &event->originalPosition, &difference);

  saveFunc = vdrawpenGetDrawingFunction(vdrawcontextGetPen(context));
  saveWidth = vdrawpenGetLineWidth(vdrawcontextGetPen(context));

  vdrawpenSetDrawingFunction(vdrawcontextGetPen(context), vdrawFUNC_INVERT);
  vdrawpenSetLineWidth(vdrawcontextGetPen(context), 1);

  vdomainInitObjectSetIterator (&iterator, event->dragObjects);

  while (vdomainNextObjectSetIterator (&iterator)) {

    object = vdomainGetObjectSetIteratorObject (&iterator);
    myObject = vdomainGetObjectData (domain, object);

    vpointMSub (&event->currentPosition, &event->originalPosition, &difference);
    vpointMAdd (&myObject->point1, &difference, &point1);
    vpointMAdd (&myObject->point2, &difference, &point2);

    _domainDrawMyObject (domain, myObject, difference.x, difference.y,
			 context);

    if (myObject->connection1 != NULL) {
      leftObject = myObject->connection1;
      if (leftObject->objectType == myDomainObjectPOINT)
        leftObject = leftObject->connection1;
       if (leftObject != NULL) {
         if (leftObject->objectType == myDomainObjectLINE) {
	   vdrawcontextSetCurrentPoint(context, leftObject->point1.x,
				       leftObject->point1.y);
	   vdrawcontextDrawLineTo(context, point1.x, point1.y);
         }
       }
    }

    if (myObject->connection2 != NULL) {
      rightObject = myObject->connection2;
      if (rightObject->objectType == myDomainObjectPOINT)
	rightObject = rightObject->connection2;
      if (rightObject != NULL) {
        if (rightObject->objectType == myDomainObjectLINE) {
	  vdrawcontextSetCurrentPoint(context, point2.x, point2.y);
	  vdrawcontextDrawLineTo(context, rightObject->point2.x,
				 rightObject->point2.y);
        }
      }
    }
      
  }

  vdrawpenSetDrawingFunction(vdrawcontextGetPen(context), saveFunc);
  vdrawpenSetLineWidth(vdrawcontextGetPen(context), saveWidth);

  return TRUE;
}

/*
 *  _domainCreateObject
 *
 *  All our domain object creation filters through here.  It does common
 *  initialization.
 *
 */

static void _domainCreateObject (vdomain *domain, myDomainObject *myObject, 
				 vrect *rect, int layerOption)

{

  vdomainObjectSet *objectSet;
  vdomainObject    *object;
  vrect             newRect;

  /* Create the low level object and get a set */
  object = vdomainAddObject (domain);
  objectSet = vdomainObjectToSet (object);

  /* set up back and forth pointers */
  vdomainSetObjectData (domain, objectSet, myObject);
  myObject->domainObject = object;


  /*
   * Inset the rect to handle line width.
   * This is done so that when the line approaches
   * horizontal or vertical, we will have a large enough
   * bounds rect to draw into (remember, lines have
   * at least a width of 1!)
   */
  vrectInset (rect, -LINE_WIDTH, -LINE_WIDTH, &newRect);

  /* Set the object bounds */
  vdomainSetObjectBounds (domain, objectSet, &newRect);

  /* apply specified layer operation */
  vdomainLayerObjects (domain, objectSet, layerOption);

  /* peek-a-boo */
  vdomainShowObjects (domain, objectSet);

}

/*******************************************************************/
/*                  Public functions                               */
/*******************************************************************/


/*
 *  domainSetupView
 *
 *  Do all the grungy domainview initialization.
 *
 */

void domainSetupView (vdomainview *domainview)

{

  vdomain	        *domain;
  vdomainObserver	*observer;
  vdomainviewEventClass *eventClass;
  vdomainObserverClass  *observerClass;

  /* Define scrolling parameters */
  vdomainviewSetAutoScroll (domainview, TRUE);
  vdomainviewSetHorzBar (domainview, TRUE);
  vdomainviewSetVertBar (domainview, TRUE);

  /* Define selection parameters */
  vdomainviewSetLiveSelection (domainview, TRUE);
  vdomainviewSetSingleSelection (domainview, TRUE);

  /* Use offscreen drawing to reduce flashiness */
  vdomainviewSetOffscreenDrawing (domainview, TRUE);

  /* We'll do our own drawing during tracking so turn off default */
  vdomainviewSetDragOutline (domainview, vdomainviewOUTLINE_NONE);

  /* Create domain and attach to view */
  domain = vdomainCreate ();
  vdomainviewSetDomain (domainview, domain);
  vdomainviewSetSelection (domainview, vdomainCreateSelection(domain));

  /* Set draw object proc */
  vdomainviewSetDrawObjectWithProc (domainview, _domainDrawObjectProc);
  vdomainviewSetDrawSelectionWithProc (domainview, _domainDrawSelectionProc);

  vdomainResize (domain, 800, 800);

  eventClass = vclassReproduce (vdomainviewGetDefaultEventClass ());
  vclassSet (eventClass, vdomainviewTRACK_EVENT, _domainTrackHandler);
  vdomainviewSetEventClass (domainview, eventClass);

  observerClass = vclassReproduce (vdomainGetDefaultObserverClass ());
  vclassSet (observerClass, vdomainObserverMOVE, _domainMoveObserver);

  observer = vdomainCreateObserverOfClass(observerClass);
  vdomainSetObserverData(observer, domain);
  vdomainInstallObserverOwned(domain, observer);

}

/*
 *  domainCleanupView
 *
 *  Clean up all the stuff that doesn't get cleaned up automatically.
 *
 */

void domainCleanupView (vdomainview *view)

{

  vdomain                  *domain;
  myDomainObject           *myObject;
  vdomainObject            *object;
  vdomainObjectSet         *objectSet;
  vdomainObjectSetIterator  iterator;

  domain = vdomainviewGetDomain (view);

  objectSet = vdomainGetObjectSet (domain, 0, vdomainALL, NULL);
  vdomainInitObjectSetIterator (&iterator, objectSet);

  while (vdomainNextObjectSetIterator (&iterator)) {
    object = vdomainGetObjectSetIteratorObject (&iterator);
    myObject = vdomainGetObjectData (domain, object);
    vmemFree (myObject);
  }

  vdomainDestroyObjectSet (objectSet);

  vdomainDestroy (domain);

}

/*
 *  domainCreateMyObject
 *
 *  Create and initialize a myDomainObject.
 *
 */

myDomainObject *domainCreateMyObject ()

{

  myDomainObject *myObject;

  /* Create our high level object */
  myObject = vmemAlloc (sizeof (myDomainObject));
  myObject->connection1 = 
  myObject->connection2 = NULL;
  myObject->amMoving    = FALSE;

  return myObject;

}

/*
 *  domainAddLine
 *
 *  Add a line that isn't connected to anything.
 *
 */

myDomainObject *domainAddLine (vdomain *domain, int x1, int y1, int x2, int y2)

{

  myDomainObject   *myObject;
  vrect             rect;

/*  _domainMakePointsCanonical (&x1, &y1, &x2, &y2); */

  /* Create our high level object */
  myObject = domainCreateMyObject ();
  myObject->objectType = myDomainObjectLINE;

  /* Compute the rectangle */
  vrectSetPoints (x1, y1, x2, y2, &rect);
  vpointSet (x1, y1, &myObject->point1);
  vpointSet (x2, y2, &myObject->point2);

  /* Create and attach the low level domain object */
  _domainCreateObject (domain, myObject, &rect, vdomainLAYER_TOBACK);

  return myObject;

}

/*
 *  domainAddPoint
 *
 *  Add a point that isn't connected to anything.  The point is at the
 *  center of a rectangle around it.
 *
 */

myDomainObject *domainAddPoint (vdomain *domain, int x1, int y1)

{

  myDomainObject   *myObject;
  vrect             rect;

  /* Create our high level object */
  myObject = domainCreateMyObject ();
  myObject->objectType = myDomainObjectPOINT;

  /* Compute the rectangle */
  vrectSetPoints (x1 - POINT_WIDTH, y1 - POINT_WIDTH, 
		  x1 + POINT_WIDTH, y1 + POINT_WIDTH, &rect);
  vpointSet (x1, y1, &myObject->point1);
  vpointSet (x1, y1, &myObject->point2);

  /* Create and attach the low level domain object */
  _domainCreateObject (domain, myObject, &rect, vdomainLAYER_TOFRONT);

  return myObject;

}

/*
 *  domainConnectLine
 *
 *  Add a line that goes from an existing object to the specified position.
 *
 */

myDomainObject *domainConnectLine (vdomain *domain, myDomainObject *leftObject,
			     int x2, int y2)

{

  myDomainObject   *myObject;
  vrect             rect;
  int               x1;
  int               y1;

  /* Set the object bounds */
  rect = *vdomainGetObjectBounds (domain, leftObject->domainObject);
  x1 = leftObject->point2.x;
  y1 = leftObject->point2.y;

  myObject = domainAddLine (domain, x1, y1, x2, y2);
  leftObject->connection2 = (struct _myDomainObject *) myObject;
  myObject->connection1 = (struct _myDomainObject *) leftObject;

  return myObject;

}


/*
 *  domainConnectPoint
 *
 *  Add a point centered at the edge of the existing object.
 *
 */

myDomainObject *domainConnectPoint (vdomain *domain, myDomainObject *leftObject)

{

  myDomainObject   *myObject;
  int               x1 = 0;
  int               y1 = 0;

  /* Set the object bounds */
  x1 = leftObject->point2.x;
  y1 = leftObject->point2.y;

  myObject = domainAddPoint (domain, x1, y1);
  leftObject->connection2 = (struct _myDomainObject *) myObject;
  myObject->connection1 = (struct _myDomainObject *) leftObject;

  return myObject;

}


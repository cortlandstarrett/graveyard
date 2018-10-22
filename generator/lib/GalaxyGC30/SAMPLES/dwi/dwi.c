/* $Id: dwi.c,v 1.14 1997/10/21 18:57:15 gregt Exp $ */

/* The following Sample Code is provided for your reference purposes in
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
 * copyright notice in the form of "Copyright 1994 Visix Software Inc.,
 * 11440 Commerce Park Drive, Reston, VA  22091. All Rights Reserved" appears
 * in all copies, (ii) both the copyright notice and this permission notice
 * appear in supporting documentation and (iii) you are a valid licensee of
 * Galaxy Application Environment.
 *
 * Do not taunt Happy Fun Ball.
 */

/* Executable Name: dwi
 * Source Files:    dwi.c
 * Header Files:    
 * Resource Files:  dwi.vr
 *
 * Managers Illustrated:
 *     Domain, Dialog, Class Manager, and ItemLists ItemLists ItemLists
 *
 * Description Of Sample:
 * 
 * This module implements a subclass of vdomainview that manages dialog
 * items.  You can put dialog items into the domain and let users operate
 * them as if they were sitting in a dialog or a container.  The users
 * can scroll the domain around (along with the dialog items).  Included
 * is a "tryout" mode that you can turn on/off to allow the moving of
 * the dialog items as domain objects.
 *
 * Things this module demonstrates:
 *   -- Subclassing
 *   -- Use of domains and domainviews
 *   -- Use of domain observers
 *   -- Handling a dialog item list and associated owner functions.
 *
 *
 * How to use it:
 *
 * The calls are somewhat patterned after the Galaxy API, except with
 * module prefix of "dwi" ( Domain With Items )
 *
 * for the time being, look at _populateDomain() below
 *
 *
 * History:
 *     Written for 1.2 release, 06/03/93
 *     Bugs fixed and tweaked for 2.0 release.  11/30/93
 *     Overhauled and completed 10/18/94
 */

/* include those parts of Galaxy which we need */
#include <vport.h>

#ifndef  vstdlibINCLUDED
#include vstdlibHEADER
#endif

#ifndef  vdebugINCLUDED
#include vdebugHEADER
#endif

#ifndef  vrectINCLUDED
#include vrectHEADER
#endif

#ifndef  vpointINCLUDED
#include vpointHEADER
#endif

#ifndef  vcharINCLUDED
#include vcharHEADER
#endif

#ifndef  vnameINCLUDED
#include vnameHEADER
#endif

#ifndef  vdictINCLUDED
#include vdictHEADER
#endif

#ifndef  vkeyINCLUDED
#include vkeyHEADER
#endif

#ifndef  veventINCLUDED
#include veventHEADER
#endif

#ifndef  vresourceINCLUDED
#include vresourceHEADER
#endif

#ifndef  vclassINCLUDED
#include vclassHEADER
#endif

#ifndef  vobjectINCLUDED
#include vobjectHEADER
#endif

#ifndef  vcommandINCLUDED
#include vcommandHEADER
#endif

#ifndef  vcolorINCLUDED
#include vcolorHEADER
#endif

#ifndef  vfontINCLUDED
#include vfontHEADER
#endif

#ifndef  vdomainINCLUDED
#include vdomainHEADER
#endif

#ifndef  vdrawINCLUDED
#include vdrawHEADER
#endif

#ifndef  vcursorINCLUDED
#include vcursorHEADER
#endif

#ifndef  vwindowINCLUDED
#include vwindowHEADER
#endif

#ifndef  vapplicationINCLUDED
#include vapplicationHEADER
#endif

#ifndef  vdialogINCLUDED
#include vdialogHEADER
#endif

#ifndef  vcontrolINCLUDED
#include vcontrolHEADER
#endif

#ifndef  vsliderINCLUDED
#include vsliderHEADER
#endif

#ifndef  vbuttonINCLUDED
#include vbuttonHEADER
#endif

#ifndef  vtextitemINCLUDED
#include vtextitemHEADER
#endif

#ifndef  vlistINCLUDED
#include vlistHEADER
#endif

#ifndef  vlistitemINCLUDED
#include vlistitemHEADER
#endif

#ifndef  vdomainviewINCLUDED
#include vdomainviewHEADER
#endif

#ifndef  vstartupINCLUDED
#include vstartupHEADER
#endif

/* vdebugTAG for this module.  It's declared this way to compensate for
 * brain-dead compilers that don't collapse static string tables.
 */
#if (vdebugDEBUG)
static const char _dwiTag[] = "dwi";
#define vdebugTAG _dwiTag
#endif



/*
 * ---------- Handy Macro ----------
 */

/* TAG -- abbreviation for vnameInternGlobaLiteral.  For "Real Live"
 *	  applications, you'd want to intern all of the tags en-masse
 *	  at startup and use cached vname pointers for more speed.
 *
 *  -> s   -- a literal (double quoted) string
 * <-      -- that string interned int the global name table.
 */

#define TAG(s)	vnameInternGlobalLiteral((s))




/*
 * ---------- Data structures and support stuff ----------
 */


/* this is the pointer to our domainview subclass.  The class manager will
 * destroy this for us when the program ends.  See 
 * dwiGetDefaultDomainviewClass() below for the setup of this
 */
static vdomainviewClass *defaultClass = NULL;


/* this is an enumeration for ID numbers for domain objects.  We reserve
 * one of these for domain objects that are really dialog items.  Users
 * of dwi are invited to use the rest of the number space from
 * dwiLAST_DOMAIN_OBJECT_ID onward for their own domain items.
 * 
 * dwiDrawObjectProc() below shows the proper way to draw the items in your
 * own draw proc.
 */
enum {
    dwiDIALOG_ITEM,
    dwiGENERIC_BOX_OBJECT,
    dwiLAST_DOMAIN_OBJECT_ID
};



/* this is the data layout for the domainview subclass object.
 * The instance data for the domainview is at the top of the structure, named
 * "view".  Pieces of data we need for the subclass follow.
 */
typedef struct dwiDomainview {
    vdomainview      view;
    vdialogItemList *itemList; /* the list of dialogitems in the domain */
    vdomainObserver *observer; /* the observer.  see observer stuff below */
    int              tryout;   /* TRUE  => mouse action will trigger the items
				* FALSE => mouse action will move domain objects
				*/
    vrect	     bounds;   /* the bounding box of the domain's scrolled
				* region */
    vbool	     horizPin; /* TRUE => pin domain movement horizontally */
    int		     initalY;  /* Y value to pin to */
} dwiDomainview;


/* these four macros are convenience things to access our extra
 * fields of the subclassed domainview.
 */
#define _itemList(view)	( ((dwiDomainview*)(view))->itemList )

#define _tryout(view)	( ((dwiDomainview*)(view))->tryout )

#define _horizPin(view)	( ((dwiDomainview*)(view))->horizPin )

#define _initialY(view)	( ((dwiDomainview*)(view))->initalY )

#define _observer(view) ( ((dwiDomainview*)(view))->observer )

#define _bounds(view)   ( ((dwiDomainview*)(view))->bounds )





/* dwiGetTopObjectAtPoint -- Domain utility function that returns the upper-
 * 			     most domain object underneath the given point.
 *			     i.e. the top of the stack that's directly under
 *			     the mouse.
 *
 *  -> view	-- the domainview that the point is over
 *  -> point	-- the point in the domain.  This should be in the 
 *		   coordinate system of the domainview (i.e. the X and Y
 *		   that you're given in an event handler.)
 * <-	        -- the topmost domain object under the mouse.
 *		   NULL if there's nothing under the mouse.
 *
 * Note that this code is independent of our subclass and can be used anywhere
 * regular domains and domainviews are used.
 */
static vdomainObject *dwiGetTopObjectAtPoint (vdomainview *view, vpoint *point)
{
    vdomainObjectSet *set;
    vdomainObjectSetIterator iterator;
    vdomainObject *object = NULL;
    vdomain *domain = vdomainviewGetDomain (view);
    vpoint	domPoint;

    domPoint = *point;
    vdomainviewTranslatePoint (view, &domPoint, vdomainviewDIALOG_TO_DOMAIN);

    set = vdomainObjectsAtPoint (domain, &domPoint,
				 vdomainviewGetSelection(view),
				 TRUE,        /* oneObjectOnly */
				 vdomainALL,  /* criteria */
				 NULL);       /* matchFunc */

    if (vdomainGetObjectSetCount(set) > 0) {
	vdomainInitObjectSetIterator (&iterator, set);
	vdomainNextObjectSetIterator (&iterator);

	object = vdomainGetObjectSetIteratorObject (&iterator);

	vdomainDestroyObjectSetIterator (&iterator);
    }
    
    vdomainDestroyObjectSet (set);

    return (object);
    
} /* dwiGetTopObjectAtPoint */




/* dwiEventIsInViewArea -- hit-tests and event against the visible 
 *			   domain view rectangle on the screen.
 *
 *  -> view  -- the domainview to hit-test with
 *  -> event -- the event to test
 * <-	     -- TRUE if the event is in the domain's view area, FALSE udderwise
 */
static vbool dwiEventIsInViewArea (vdomainview *view, vevent *event)
{
    vrect *rect;
    vbool ret;

    rect = vdomainviewGetDomainRect (view);

    ret = vrectMContainsPoint (rect, veventGetPointerX(event),
			       veventGetPointerY(event));
    return (ret);

} /* dwiEventIsInViewArea */




/* _dwiCalculateBounds -- figure out the bounds of the domain expressed in
 *			  the coordinate system of dialog the domain view
 *			  lives in.
 *
 *  -> view -- the view to calculate the bounds for
 *
 * This has the side effect of changing the 'bounds' field of our domainview
 * structure.
 */
static void _dwiCalculateBounds (vdomainview *view)
{
    vrect		*rect = & _bounds(view);
    vrect		 boundsRect;
    const vrectLong	*viewableArea;

    *rect = *vdomainGetBounds (vdomainviewGetDomain(view));

    boundsRect = *vdomainGetBounds (vdomainviewGetDomain(view));
    vdomainviewTranslateRect (view, &boundsRect, vdomainviewDOMAIN_TO_DIALOG);
    viewableArea = vdomainviewGetViewableArea (view);

    rect->x = boundsRect.x - viewableArea->x;
    rect->y = boundsRect.y - viewableArea->y;

} /* _dwiCalculateBounds */




/*
 * ---------- Domain Observer Stuff ----------
 */


/* There is one piece of domain-related housekeeping we have to keep
 * track of.  We need to update dialog item's rectangles in case the
 * user decides to move the domain objects that are associated with the
 * dialog items.  
 * When any objects are moved, the observers are notified, including the
 * observer we set up below.  We cycle over the set of objects that are
 * being moved, and if they are the placeholders for the dialog items 
 * (i.e. they have a type of dwiDIALOG_ITEM), change the dialog item's
 * rectangle appropriately.  If they're not of this type, ignore them.
 *
 * We add the observer when we set the domain to the domainview,
 * and we remove the observer when the domainview is destroyed.
 */


/* this is the class for our domain observer.  The class manager will
 * destroy this for us when the world ends.
 */
static vdomainObserverClass *dwiObserverClass = NULL;



/* dwiObserverMove -- The Observer Notification that is called when 
 *		      domain objects are moved in the domain.  This gives
 *		      us a chance to update any auxilliary information
 *		      (such as our dialog items) in response.
 * 
 *  -> data	   -- a piece of data we told the domain manager to give
 *		      to us whenever our observer is called.  This happens
 *		      to be a pointer to the domainview.
 *		      (see dwiSetDomain below)
 *  -> set	   -- the set of objects that have been moved.
 *  -> newPosition -- the new location where the objects are.  The contents
 *		      of this vary depending on what the next parameter
 *		      is.
 *  -> positioning -- some combination of the following: 
 *		      vdomainX_RELATIVE &/or vdomainY_RELATIVE &/or
 *		      vdomainX_ABSOLUTE &/or vdomainY_ABSOLUTE,
 *		      vdomainRELATIVE or vdomainABSOULTE
 *  -> before -- TRUE for pre-move, FALSE for post-move
 *
 * we're not paying any attention to newPostion and positioning.  We just
 * get the bounding rectangles from the domain objects and set the bounding
 * rectangles of the dialog items appropriately.
 */
static void dwiObserverMove (vdomainObserver *observer, vdomainObjectSet *set, 
			     vpoint *newPosition, int positioning,
			     int before)
{
    vdomainObjectSetIterator iterator;
    vdomainObject *object;
    vdialogItem *item;

    /* only do the "after" case */
    if (!before && (vdomainGetObjectSetCount(set) > 0)) {
	/* cycle over all of the objects */
	vdomainInitObjectSetIterator (&iterator, set);

	while (vdomainNextObjectSetIterator (&iterator)) {
	    object = vdomainGetObjectSetIteratorObject (&iterator);

	    /* make sure that it's one of our dialog-item domain objects */
	    if (vdomainGetObjectType(dummy, object) == dwiDIALOG_ITEM) {

		/* get the vdialogItem and change it's rectangle */
		item = (vdialogItem*)vdomainGetObjectData(dummy, object);
		vdialogSetItemRect (item, 
				    vdomainGetObjectBounds (dummy, object));
	    }
	}
	
	/* clean up after our iterator */
	vdomainDestroyObjectSetIterator (&iterator);
    }
} /* dwiObserverMove */




/* dwiGetObserverClass -- Setup the observer class so that we can keep our
 *			  auxilliary data in sync to actions on the domain.
 *
 * <-  -- our new observer class
 *
 * Right now we're only looking at vdomainObserverMOVE.  If you lateron
 * provide users with a mechanism for resizing the objects, you'll need
 * to override vdomainObserverRESIZE.  Consult the Friendly Manual for
 * different observer notification messages.
 */

static vdomainObserverClass *dwiGetObserverClass (void)
{
    if (dwiObserverClass == NULL) {

	/* the default class is a collection of No-ops for us to change */
	dwiObserverClass = vclassReproduce (vdomainGetDefaultObserverClass());

	/* just look at move operations */
	vclassSet (dwiObserverClass,
		   vdomainObserverMOVE,
		   dwiObserverMove);
    }

    return (dwiObserverClass);

} /* vdomainObserverClass */



/*
 * ---------- DialogItem Owner Functions ----------
 */


/* this is the most arcane and obscure portion of thos entire module,
 * but it's necessary to successfully become a container of dialog items.
 *
 * Dialog item lists are the principal abstraction for insulating
 * dialog items from the different possible layers of containment.
 *
 * This is accomplished by a hierarchy of functions that are called
 * which transform parts of the environment so that the dialog items
 * can "do their thing" oblivious to how deeply they are contained.
 *
 * When you contain other dialog items, you need to uphold your end
 * of this dialog-item, item-list bargain.  We define a table of functions
 * that are called when the values of different parts of the environment
 * are queried by the items.  For the most part, we just forward these
 * to existing functions that determine these values from the dialog
 * that the items live in.  There are two particular owner functions
 * for determining the bounds and content rectangles.  The rectangles
 * need to be adjust to compensate for the location of the "container"
 * (in this case, a domainview), as well as the scrolling state of
 * the "container".
 *
 * The functions which follow are put into an ownerfunc table, which
 * is then used by vdialogSetItemListOwner.
 *
 * The documentation for the ownerfuncs can be found in the
 * vdialog "Data Types" section of the Dialog Manager Chapter in the
 * documentation set.  The location may be different in subsequent
 * versions.  The docs are very sketchy and incomplete when it comes
 * to owner functions, so some of of what you see below might not be
 * the Absolute Best Thing.
 */


/* owner2item -- a convenience macro that turns a vobject pointer into
 *		 a vdialogItem pointer.  Note that the cast is to
 *		 a vdomainview pointer.  We specified that the owner of
 *		 this dialog item list is a vdomainview, hence this 
 *		 cast is a safe one. (see dwiLowInit below)
 *
 *  -> owner	-- the owner of this item list.
 * <-		-- a vdialogItem equivalent to "owner"
 */
#define owner2item(owner) (vdomainviewGetItem((vdomainview*)owner))



/* determineDialog -- given an owner, figure out what dialog it's in.
 *
 *  -> owner -- the owner of the item list
 * <-	     -- the dialog this item list ultimately lives in.
 */
static vdialog *determineDialog (vobjectAttributed *owner)
{
    return (vdialogDetermineItemDialog (owner2item(owner)));
} /* determineDialog */



/* determineCursor -- given an owner, figure the cursor that should be used
 *		      when the mouse pointer is over this area.
 *
 *  -> owner -- the owner of the item list
 * <-        -- the cursor to use.  Just use the cursor that's set for
 *		the owning dialog item.
 */
static vcursor *determineCursor (vobjectAttributed *owner)
{
    return (vdialogDetermineItemCursor (owner2item(owner)));
} /* determineCursor */




/* determineFont -- given an owner, figure out the font to use for text
 *		    drawing.
 *
 *  -> owner -- the owner of the item list
 * <-	     -- the font to use.  Just use the font that'd be used for
 *		text drawing in owner.
 */
static vfont *determineFont (vobjectAttributed *owner)
{
    return (vdialogDetermineItemFont (owner2item(owner)));
} /* determineFont */
    


/* determineColorsFrom -- given an owner, figure out a set of colors
 *			  to use for drawing.
 *
 *  -> owner  -- the owner of the item list
 *  -> flags  -- 
 *  -> known  -- 
 *  -> ids    --
 *  -> count  --
 *  -> colors -- see the documentation for vdialogDetermineItemColorsFrom()
 */
static void determineColorsFrom (vobjectAttributed *owner, long flags, 
				 vcolor **known, int *ids, int count, 
				 vcolor **colors)
{
    vdialogDetermineItemColorsFrom (owner2item(owner),
				    flags, known, ids, count, colors);
} /* determineColorsFrom */



/* determineLineWidth -- given an owner, figoure out the line width to use
 *			 for vdraw path stroking.
 *
 *  -> owner -- the owner of this item list.
 * <-	     -- the line width to use.  Just use the line width that'd be
 *		used for path stroking for the owner.
 */
static int determineLineWidth (vobjectAttributed *owner)
{
    return (vdialogDetermineItemLineWidth(owner2item(owner)));
} /* determineLineWidth */



/* determineBounds -- return the bounding box of the owning object in
 *		      the coordinate system of its window.
 *
 *  -> owner -- the owner of this item list
 * <-  rect  -- the bounding rectangle for the bounds.
 *
 * !!! need sane description of what's going on here. !!! 
 *
 * This has the nice side effect that we don't have to manually offset
 * the dialog items when the domainview scrolls.
 */
static void determineBounds (vobjectAttributed *owner, register vrect *rect)
{
    vdomainview     *view = (vdomainview*)owner;
    vdialogItemList *itemList;

    _dwiCalculateBounds (view);

    *rect = _bounds(view);

    itemList = vdialogGetItemItemList (owner2item(owner));

    if (itemList != NULL) {
	vrect bounds;
	vdialogDetermineItemListBounds (itemList, &bounds);

	/* compensate for our container's scrolling */
	rect->x += bounds.x;
	rect->y += bounds.y;
    }

} /* determineBounds */



/* determineContent -- retun the bounding box of the visible portion of the
 *		       owning object in the coordinate system of its window.
 *
 *  -> owner -- the owner of this item list
 * <-> rect  -- the content rectangle for the bounds.
 *
 * The above call returns the total area of the domain.
 * This call returns the area actually taken up on the screen.
 *
 * !!! need sane description of what's going on here. !!!
 */
static void determineContent (vobjectAttributed *owner, vrect *rect)
{
    vdialogItemList *itemList;
    vdomainview *view = (vdomainview*)owner;

    *rect = *vdomainviewGetDomainRect (view);

    itemList = vdialogGetItemItemList (owner2item(owner));

    if (itemList != NULL) {
	vrect bounds, content;
	vdialogDetermineItemListBounds (itemList, &bounds);
	vdialogDetermineItemListContent (itemList, &content);

	rect->x += bounds.x;
	rect->y += bounds.y;
	vrectIntersect (rect, &content, rect);
    }

} /* determineContent */



/* determineFont -- given an owner, figure out the key map to use.
 *
 *  -> owner -- the owner of the item list
 * <-	     -- the key map to use.  Just use the key map that'd be used for
 *		our owner.
 */
static vdict *determineKeyMap (vobjectAttributed *owner)
{
    return (vdialogGetItemKeyMap (owner2item(owner)));
} /* determineKeyMap */



/* determineKeyDispatch -- given an owner, figure out the key dispath dict
 *			   to use.
 *
 *  -> owner -- the owner of the item list
 * <-	     -- the key map to use.  Just use the key dispatch dict
 *		that'd be used for our owner.
 */
static vdict *determineKeyDispatch (vobjectAttributed *owner)
{
    return (vdialogGetItemKeyDispatch (owner2item(owner)));
} /* determineKeyDispatch */



/* determineShown -- given an owner, figure if it's currently visible
 *
 *  -> owner -- the owner of the item list
 * <-	     -- the visibility state
 *
 * This allows for a container-like object to hide its contents when it
 * gets hidden.
 */
static int determineShown (vobjectAttributed *owner)
{
    return (vdialogDetermineItemShown (owner2item(owner)));
} /* determineShown */



/* determineEnabled -- given an owner, figure if it's currently enabled.
 *
 *  -> owner -- the owner of the item list
 * <-	     -- the enabled sate.
 *
 * This allows for a container-like object to disable its contents when it
 * gets disabled.
 */
static int determineEnabled (vobjectAttributed *owner)
{
    return (vdialogDetermineItemEnabled (owner2item(owner)));
} /* determineEnabled */



/* determineColorSchemeFrom -- given an owner, figure out the color scheme
 *
 *  -> owner  -- the owner of this item list
 *  -> known  -- a set of colors that we know already
 *  -> flags  -- the elements that are set in known
 *  -> scheme -- the color scheme to modify to fill in the unknown slots
 */
static void determineColorSchemeFrom (vobjectAttributed *owner, 
				      vcolorScheme *known, 
				      unsigned long flags, 
				      vcolorScheme *scheme)
{
    vdialogDetermineItemColorSchemeFrom (owner2item(owner),
					 known, flags, scheme);
} /* determineColorSchemeFrom */



/* drawDevice -- the drawing device is being set for an item in the item
 *		 list.  Set up clipping and whatnot to prevent bit overflow
 *
 *  -> owner -- the owner of the item list that's having a member set the
 *		draw device
 */
static void drawDevice(vobjectAttributed *owner)
{
    vdomainview     *view = (vdomainview*)owner;

    vdialogItemDrawDevice (vdomainviewGetItem(view));
    vdrawTranslate (_bounds(view).x, _bounds(view).y);
    vdrawRectsClip (vdomainviewGetViewArea(view), 1);

} /* drawDevice */



/* this structure is a table of the above-defined functions. */
static vdialogItemListOwnerFuncs ownerFuncs = {
    /* we're defining all of them */
    vdialogITEM_LIST_OWNER_STATE_FUNCS | vdialogITEM_LIST_OWNER_DRAW_FUNCS,
    determineDialog,
    determineCursor,
    determineFont,
    determineColorsFrom,
    determineLineWidth,
    determineBounds,
    determineContent,
    determineKeyMap,
    determineKeyDispatch,
    determineShown,
    determineEnabled,
    determineColorSchemeFrom,
    drawDevice
};




/*
 * ---------- Domainview method overrides ----------
 */


/* the functions which follow are the method overrides for our domainview
 * subclass.*/

/* ??? need more info here ??? */



/* dwiLowInit -- shared initialization code between dwiInit and dwiLoadInit.
 *
 *  -> view -- the view to intialize.
 */
static void dwiLowInit (vdomainview *view)
{
    dwiDomainview *nuView = (dwiDomainview*)view;

    nuView->itemList = vdialogCreateItemList ();

    /* mouse clicks will be forwarded to the dialog items if appropriate */
    nuView->tryout = TRUE;

    /* pinning off by default */
    nuView->horizPin = vFALSE;

    /* associte the owner functions defined above with the item list.
     * also set the owner of this item list to be the domainview.
     */
    vdialogSetItemListOwner (nuView->itemList,
			     vdialogGetItemObject(vdomainviewGetItem(view)),
			     &ownerFuncs);

} /* dwiLowInit */




/* dwInit -- initialize our domainview.
 *
 *  -> view -- the domainview to initialize.
 *
 * This is called in response to a vdomainviewInit() or vdomainviewCreate().
 * This code is *never* called if the the domainview is created or intialized
 * from a resource.
*/
static void dwiInit (vdomainview *view)
{
    vclassSendSuper (defaultClass, vobjectINIT, (view));

    dwiLowInit (view);

} /* dwiInit */




/* dwiLoadInit -- intialize our domainview from a resource.
 *
 *  -> view     -- the domainview to intialize
 *  -> resource -- the resource template to use
 *
 * This is called in response to a vdomainviewLoad() or vdomainviewLoadInit()
 * or when a dialog containing one of our domainviews is loaded from a 
 * resource.
 * This code is *never* called if the domainview is created via vdomainCreate()
 * or vdomainviewCreate()
 */
static void dwiLoadInit (vdomainview *view, vresource resource)
{
    vclassSendSuper (defaultClass, vobjectLOAD_INIT, (view, resource));

    dwiLowInit (view);

    /* we don't have any additional things to look for yet */

} /* dwiLoadInit */




/* dwiDestroy -- Clean up any memory we may have consumed.
 *
 *  -> view -- the domainview being destroyed.
 *
 * This function destorys the domain associated with the view!
 * If you're sharing the domain amongst other views, you'll need to
 * change this.
 */
static void dwiDestroy (vdomainview *view)
{
    vdomain *domain = vdomainviewGetDomain(view);

    /* disconnect  our observer */
    vdomainUninstallObserver (domain, _observer(view));

    /* nuke our item list */
    if (_itemList(view) != NULL) {
	/* I think this destroys the dialog items contined inside */
	vdialogDestroyItemList (_itemList(view));
    }

    /* sign our death warrant */
    vclassSendSuper (defaultClass, vobjectDESTROY, (view));

    /* get rid of the domain while we're here. */
    vdomainDestroy (domain);

} /* dwiDestroy */




/* dwiIssueSelector -- handle selector commands issued against the domainview
 *
 *  -> view       -- the domainview having a command issued
 *  -> selector   -- the ID of the command being issued
 *  -> attr2value -- the context this command is issuing in.
 * <-		  -- TRUE if we handled it, FALSE otherwise.
 *
 * Right now we're just sniffing the focus moving so we can move the focus
 * in our owned itemlist.
 */
static int dwiIssueSelector (vdomainview *view, int selector,
			     vdict *attr2value)
{
    int ret = FALSE;

    switch (selector) {
	case vdialogITEM_SELECT_MOVE_FOCUS: {
	    vdialogItem *item;

	    if ((vdomainviewHasHorzBar(view) &&
		 (item = vcontrolGetItem(vdomainviewGetHorzScrollbar(view))) &&
		 vdialogItemIsFocused(item)) ||
		(vdomainviewHasVertBar(view) &&
		 (item = vcontrolGetItem(vdomainviewGetVertScrollbar(view))) &&
		 vdialogItemIsFocused(item)))
		/* one of the scrollbars is focused, let superclass handle
		 * it
		 */
		ret = FALSE;
	    else {
		const int *direction;

		direction = vdictLoad (attr2value, vname_Direction);
		if (direction != NULL) {
		    vdialogMoveItemListFocus (_itemList(view), *direction,
					      vdictLoad(attr2value, vname_Text)
					      != NULL);
		    /* since we're effectively a "flat" container, see if we
		     * need to pop ourselves out
		     */
		    if (vdialogItemListFocusHasWrapped(_itemList(view))) {
			/* let superclass handle it */
			ret = FALSE;
		    } else {
			ret = TRUE;
		    }
		}
	    }
	    break;
	}
    }

    if (!ret) {
	ret = vclassSendSuper (defaultClass, vobjectISSUE_SELECTOR,
			       (view, selector, attr2value));
    }

    return (ret);

} /* dwiIssueSelector */




/* dwiChangedParentAttribute -- propagate our parent's changes to our children
 *
 *  -> view       -- the domainview receiving the notification
 *  -> attr       -- the name of the attribute which has changed
 *  -> context    -- the context this change happened in
 *
 */
static void dwiChangedParentAttribute (vdomainview *view, const vname *attr,
				       vdict *context)
{
    vclassSendSuper (defaultClass, vobjectCHANGED_PARENT_ATTRIBUTE,
		     (view, attr, context));

    if (attr == vname_Bounds) {
	vdialogChangedItemListParentAttribute (_itemList(view), attr, context);
    }

} /* dwiChangedParentAttribute */




/* dwiChangedAttribute -- propagate our attribute changes to our children
 *
 *  -> view       -- the domainview receiving the notification
 *  -> attr       -- the name of the attribute which has changed
 *  -> context    -- the context this change happened in
 *
 */
static void dwiChangedAttribute (vdomainview *view, const vname *attr,
				 vdict *context)
{
    vclassSendSuper (defaultClass, vobjectCHANGED_ATTRIBUTE,
		     (view, attr, context));

    vdialogChangedItemListParentAttribute (_itemList(view), attr, context);

} /* dwiChangedAttribute */




/* dwiSetDomain -- Associate a domain with a domainview.  We're going to
 *		   attach our observer at this time.
 *
 *  -> view   -- the domainview to set the domain for
 *  -> domain -- the domain the view will watch.
 */
static void dwiSetDomain (vdomainview *view, vdomain *domain)
{
    vclassSendSuper (defaultClass, vdomainviewSET_DOMAIN, (view, domain));

    if (domain != NULL) {
	vdomainObserver *observer;

	/* we want to peek at what's going on so we can keep our dialogItems
	 * up to date.
	 */
	observer = vdomainCreateObserverOfClass (dwiGetObserverClass ());
	vdomainSetObserverData (observer, view);
	vdomainInstallObserverOwned (domain, observer);
	_observer(view) = observer;
    }

} /* dwiSetDomain */


/* dwiDragOutlineWith -- Pin domain objects to restrict movement to horizontal
 * only
 *
 *  -> view      -- the domainview to set the domain for
 *  -> rects     -- the array of rectangles to be dragged
 *  -> numRects  -- # of rectangles in array
 *  -> limitRect -- bounding rectangle for rects
 *  -> pinAmount -- amount to pin
 */
static void dwiDragOutlineWith (vdomainview *view, vrect *rects, int numRects,
				vrect *limitRect, vpoint *pinAmount,
				vdrawcontext *context)
{
    /* if we're pinning, set the pinAmount properly */
    if (_horizPin(view))
	pinAmount->y = _initialY(view) - limitRect->y;

    /* call our parent to do the actual drawing */
    vclassSendSuper (defaultClass, vdomainviewDRAG_OUTLINE_WITH,
		     (view, rects, numRects, limitRect, pinAmount, context));
}


/* dwiHandleTrackEvent -- Get inital Y value of objects being dragged so
 *			  we know how much to pin to in our DragOutline
 *			  override.
 *
 *
 *  -> view      -- the domainview which is tracking
 *  -> event     -- the TrackEvent
 */
static vbool dwiHandleTrackEvent(vdomainview *view,
				 vdomainviewTrackEvent *event)
{
    if (event->state == vdomainviewTRACK_START &&
	event->dragObjects != NULL) {
	vrect	limitRect;

	vdomainBoundingRect(vdomainviewGetDomain(view), &limitRect,
			    event->dragObjects);
	_initialY(view) = limitRect.y;
    }

    return vclassSendSuper (defaultClass, vdomainviewHANDLE_TRACK_EVENT,
			    (view, event));
}

/* dwiHandleScrollEvent -- Propagate the bounds change to our itemList
 *
 *
 *  -> view      -- the domainview which scrolled
 *  -> event     -- the ScrollEvent
 */
static vbool dwiHandleScrollEvent(vdomainview *view,
				  vdomainviewScrollEvent *event)
{
    if (vdomainviewGetDomain(view) != NULL) {
	vrect	oldBounds;

	oldBounds = _bounds (view);

	_dwiCalculateBounds (view);

	vdialogChangedItemAttributeValue (vdomainviewGetItem(view),
					  vname_Bounds, &oldBounds,
					  &_bounds(view));
    }

    return vclassSendSuper (defaultClass, vdomainviewHANDLE_SCROLL_EVENT,
			    (view, event));
}

/* dwiHandleResizeEvent -- Propagate the bounds change to our itemList
 *
 *
 *  -> view      -- the domainview whose domain resized
 *  -> event     -- the ScrollEvent
 */
static vbool dwiHandleResizeEvent(vdomainview *view,
				  vdomainviewResizeEvent *event)
{
    if (vdomainviewGetDomain(view) != NULL) {
	vrect	oldBounds;

	oldBounds = _bounds (view);

	_dwiCalculateBounds (view);

	vdialogChangedItemAttributeValue (vdomainviewGetItem(view),
					  vname_Bounds, &oldBounds,
					  &_bounds(view));
    }

    return vclassSendSuper (defaultClass, vdomainviewHANDLE_RESIZE_EVENT,
			    (view, event));
}

/* dwiHandleItemButtonDown -- Handle a button down in the domainview.
 *
 *  -> view  -- the domain view clicked on
 *  -> event -- the button down event.
 * <-	     -- TRUE if it was handled by somebody, FALSE otherwise
 *
 * We look at the item immediately underneath the mouse pointer.
 * If it iss one of our dialog-item place holders, forward the event to that
 * item.
 */
static int dwiHandleItemButtonDown (vdomainview *view, vevent *event)
{
    int ret = FALSE;
    vpoint point;

    /* if _tryout(view) == TRUE, the dialog items are "live"
     * if _tryout(view) == FALSE, mouse actions only manipulate the domain
     *                            objects
     */
    if (_tryout(view) && dwiEventIsInViewArea(view, event)) {
	vdomainObject *object;
	vdialogItem *item;

	/* if a scrollbar has focus, pass focus over to the view */
	if ((vdomainviewHasHorzBar (view) &&
	     (item = vcontrolGetItem (vdomainviewGetHorzScrollbar (view))) &&
	     vdialogItemIsFocused (item)) ||
	    (vdomainviewHasVertBar (view) &&
	     (item = vcontrolGetItem (vdomainviewGetVertScrollbar (view))) &&
	     vdialogItemIsFocused (item))) {
	    vdialogUnfocusItem (item);
	    vdialogFocusItem (vdomainviewGetItem (view));
	}

	/* make sure dwi bounds match bounds after any scrolling */
	_dwiCalculateBounds (view);

	/* get the top item at the mouse point */
	point.x = veventGetPointerX (event);
	point.y = veventGetPointerY (event);

	object = dwiGetTopObjectAtPoint (view, &point);

	/* if we didn't click in empty space */
	if (   (object != NULL)
	    && (vdomainGetObjectType (dummy, object) == dwiDIALOG_ITEM)) {

	    /* offset the coordinates to match domain's scrolling offset */
	    veventSetPointerX (event, point.x - _bounds(view).x);
	    veventSetPointerY (event, point.y - _bounds(view).y);

	    /* let the item list handle the work of figuring out who gets it */
	    ret = vdialogHandleItemListButtonDown (_itemList(view), event);

	    /* leave the event coordinates mangulated in case someone later
	     * needs them like that.
	     */
	}
    }

    /* either we're not in tryout, we didn't click on a dwiDIALOG_ITEM object,
     * or the dialog item didn't handle the event.  Let the domainview have
     * a chance at it.
     */
    if (!ret) {
	ret = vclassSendSuper (defaultClass, vdialogHANDLE_ITEM_BUTTON_DOWN,
			       (view, event));
    }
    
    return (ret);

} /* dwiHandleItemButtonDown */




/* dwiHandleItemDrag -- Handle mouse drag event.
 *
 *  -> view   -- the domainview being dragged over.
 *  -> event  -- the drag event.
 * <-	      -- TRUE if we handled the event, FALSE otherwise
 */
static int dwiHandleItemDrag (vdomainview *view, vevent *event)
{
    int ret = FALSE;
    /* see if one of our dialogItemInADomain is tracking. */
    vdialogItem *item = vdialogGetItemListDrag (_itemList(view));

    if (item != NULL) {
	vpoint point;

	point.x = veventGetPointerX (event);
	point.y = veventGetPointerY (event);

	veventSetPointerX (event, point.x - _bounds(view).x);
	veventSetPointerY (event, point.y - _bounds(view).y);

	/* see if the item wants to handle it. */
	ret = vdialogHandleItemDrag (item, event);
	
	if (!ret) {
	    /* restore the event coordinates */
	    veventSetPointerX (event, point.x);
	    veventSetPointerY (event, point.y);
	}
    }

    /* either there wasn't a tracking item, or it didn't want to handle
     * this.  We've had our fun, let the domainview have a crack at it.
     */
    if (!ret) {
	ret = vclassSendSuper (defaultClass, vdialogHANDLE_ITEM_DRAG,
			       (view, event));
    }
	
    return (ret);

} /* dwiHandleItemDrag */



/* dwiHandleItemButtonUp -- Handle a button up in the domainview
 *
 *  -> view	-- the domainview getting the button up.
 *  -> event	-- the button up event.
 * <-		-- TRUE if we handled the event, FALSE otherwise.
 */
static int dwiHandleItemButtonUp (vdomainview *view, vevent *event)
{
    int ret = FALSE;
    /* see if one of our dialogItemInADomain is tracking. */
    vdialogItem *item = vdialogGetItemListDrag (_itemList(view));

    if (item != NULL) {
	vpoint point;

	point.x = veventGetPointerX (event);
	point.y = veventGetPointerY (event);

	veventSetPointerX (event, point.x - _bounds(view).x);
	veventSetPointerY (event, point.y - _bounds(view).y);

	/* see if the item wants to handle it */
	ret = vdialogHandleItemButtonUp (item, event);

	/* clear out the value so we don't get confused on a subsequent
	 * drag or mouse up event */
	vdialogSetItemListDrag (_itemList(view), NULL);

	if (!ret) {
	    /* restore the event coordinates */
	    veventSetPointerX (event, point.x);
	    veventSetPointerY (event, point.y);
	}
   }

    /* eldnah ot tnaw t'ndid ti ro ,meti gnikcart a t'nsaw ereht rehtie
     * .ti ta kcarc a evah weivniamod eht tel ,nuf ruo dah ev'eW  .siht
     */
    if (!ret) {
	ret = vclassSendSuper (defaultClass, vdialogHANDLE_ITEM_BUTTON_UP,
			       (view, event));
    }

    return (ret);

} /* dwiHandleItemButtonUp */




/* dwiHandleItemKeyDown -- handle a key press in the domainview.
 *
 *  -> view   -- the domainview getting a keystroke
 *  -> event  -- the key event.
 * <-	      -- TRUE if we handled it, FALSE if someone else should
 */
static int dwiHandleItemKeyDown (vdomainview *view, vevent *event)
{
    vdialogItem *item, *viewItem;
    const vname *binding;
    vkeyStroke key;
    int ret = FALSE;


    viewItem = vdomainviewGetItem (view);

    /* try to bind the key to our key map */
    key = veventGetKeyStroke (event);

    binding = vdialogLoadItemKeyMap (viewItem, key);
    if (binding != NULL) {
	veventSetBinding (event, binding);
    }

    /* try to dispatch the event to an item in the key dispatcher */

    item = (vdialogItem*)vdialogLoadItemKeyDispatch (viewItem, key);
    if (   (item != NULL)
	&& vdialogItemIsEnabled(item) 
	&& vdialogHandleItemKeyDown(item, event)) {
	ret = TRUE;
    }

    if (!ret) {
	item = vdialogGetItemListFocus (_itemList(view));
	if (   (item != NULL)
	    && vdialogItemIsEnabled(item)
	    && vdialogHandleItemKeyDown(item, event)) {
	    ret = TRUE;
	} else {
	    ret = vclassSendSuper (defaultClass,
				   vdialogHANDLE_ITEM_KEY_DOWN,
				   (view, event));
	}
    }

    return (ret);

} /* dwiHandleItemKeyDown */




/* dwiFocusItem -- Do what's necessary when a domainview gets focus.
 *
 *  -> view -- the domainview getting keyboard focus.
 */
static void dwiFocusItem (vdomainview *view)
{
    vdialogItem *item;

    /* let the domainview know it is being focused */
    vclassSendSuper (defaultClass, vdialogFOCUS_ITEM, (view));

    /* let our itemlist know it's focused if neither scrollbar is */
    if ((!vdomainviewHasHorzBar(view) ||
	 ((item = vcontrolGetItem(vdomainviewGetHorzScrollbar(view))) &&
	  !vdialogItemIsFocused(item))) &&
	(!vdomainviewHasVertBar(view) ||
	 ((item = vcontrolGetItem(vdomainviewGetVertScrollbar(view))) &&
	  !vdialogItemIsFocused(item))))
	vdialogFocusItemList (_itemList(view));

} /* dwiFocusItem */



/* dwiUnfocusItem -- Do what's necessary when a domainview loses focus.
 *
 *  -> view -- the domainview losing keybored focus.
 */ 
static void dwiUnfocusItem (vdomainview *view)
{
    vdialogItem *item;

    /* let our itemlist know it's unfocused if neither scrollbar was */
    if ((!vdomainviewHasHorzBar(view) ||
	 ((item = vcontrolGetItem(vdomainviewGetHorzScrollbar(view))) &&
	  !vdialogItemIsFocused(item))) &&
	(!vdomainviewHasVertBar(view) ||
	 ((item = vcontrolGetItem(vdomainviewGetVertScrollbar(view))) &&
	  !vdialogItemIsFocused(item))))
	vdialogUnfocusItemList (_itemList(view));

    /* let the domainview know it's lost focus */
    vclassSendSuper (defaultClass, vdialogUNFOCUS_ITEM, (view));

} /* dwiUnfocusItem */

/* dwiActivateItem -- Do what's necessary when a domainview gets activate event.
 *
 *  -> view -- the domainview getting activate event.
 */
static void dwiActivateItem (vdomainview *view)
{
   vclassSendSuper (defaultClass, vdialogACTIVATE_ITEM, (view) );
   vdialogActivateItemList( _itemList(view) );

} /* dwiActivateItem */



/* dwiDeactivateItem -- Do what's necessary when a domainview gets deactivate event.
 *
 *  -> view -- the domainview getting deactivate event.
 */ 
static void dwiDeactivateItem (vdomainview *view)
{
    vclassSendSuper (defaultClass, vdialogDEACTIVATE_ITEM, (view) );
    vdialogDeactivateItemList( _itemList(view));

} /* dwiDeactivateItem */



/* dwiOpenItem -- Do what's necessary when the domainview gets opened
 *		  (i.e. mapped on the screen and ready to accept user
 *		  input.
 *  -> view -- the domainview being opened
 */
static void dwiOpenItem (vdomainview *view)
{
    /* open ourselves */
    vclassSendSuper (defaultClass, vdialogOPEN_ITEM, (view));
    
    /* open the items in our item list.  New items appened later on will be
     * opened as necessary.
     */
    vdialogOpenItemList (_itemList(view));

} /* dwiOpenItem */




/* dwiCloseItem -- Do what's necessarry when the domainview gets closed.
 *		   (i.e. removed from the dialog, an owning container gets
 *		   hidden, the dialog being closed.)
 *
 *  -> view -- the domainview being closed. 
 */
static void dwiCloseItem (vdomainview *view)
{
    /* close our dialog items.
     */
    vdialogCloseItemList (_itemList(view));

    /* our closings ourselves. */
    vclassSendSuper (defaultClass, vdialogCLOSE_ITEM, (view));

} /* dwiCloseItem */




/* dwiGetDefaultDomainviewClass -- Create our subclass and register it
 *				   with the Class Manager so that it is
 *				   accessible when dialogs are loaded.
 *
 *  <-  -- the domainview subclass that can contain dialog items. 
 */
static vdomainviewClass *dwiGetDefaultDomainviewClass (void)
{
    if (defaultClass == NULL) {
	/* make a subclass */
	defaultClass = vclassReproduce (vdomainviewGetDefaultClass());
	
	/* we've added a couple of fields.  Make sure sufficient memeory
	 * is allocated on our behalf.
	 */
	vclassSetObjectSize (defaultClass, sizeof(dwiDomainview));
	vclassSetNameScribed (defaultClass,
			      vcharScribeLiteral("dwiDomainview"));
	
	vclassSet (defaultClass,
		   vobjectINIT,        /* initialize static data */
		   dwiInit);
	
	vclassSet (defaultClass,
		   vobjectLOAD_INIT,   /* load dynamically from a resource */
		   dwiLoadInit);
	
	vclassSet (defaultClass,
		   vobjectDESTROY,     /* clean up our mess */
		   dwiDestroy);

	vclassSet (defaultClass,
		   vobjectISSUE_SELECTOR, /* handle focus stuff */
		   dwiIssueSelector);
	
	vclassSet (defaultClass,
		   vobjectCHANGED_PARENT_ATTRIBUTE, /* propagate things to our itemList */
		   dwiChangedParentAttribute);

	vclassSet (defaultClass,
		   vobjectCHANGED_ATTRIBUTE, /* propagate things to our itemList */
		   dwiChangedAttribute);

	vclassSet (defaultClass,
		   vdialogHANDLE_ITEM_BUTTON_DOWN, /* handle clicks */
		   dwiHandleItemButtonDown);
	
	vclassSet (defaultClass,
		   vdialogHANDLE_ITEM_BUTTON_UP,   /* handle button releases */
		   dwiHandleItemButtonUp);
	
	vclassSet (defaultClass,
		   vdialogHANDLE_ITEM_DRAG,        /* handle mouse drags */
		   dwiHandleItemDrag);
	
	vclassSet (defaultClass,
		   vdialogHANDLE_ITEM_KEY_DOWN,    /* handle keypresses */
		   dwiHandleItemKeyDown);
	
	vclassSet (defaultClass,
		   vdialogFOCUS_ITEM,     /* give the item keyboard focus */
		   dwiFocusItem);
	
	vclassSet (defaultClass,
		   vdialogUNFOCUS_ITEM,   /* snatch away keyboard focus */
		   dwiUnfocusItem);
	
	vclassSet (defaultClass,
		   vdialogACTIVATE_ITEM,  /* handle activate item event */
		   dwiActivateItem );
	
	vclassSet (defaultClass,
		   vdialogDEACTIVATE_ITEM,/* handle deactivate item event */
		   dwiDeactivateItem );
	
	vclassSet (defaultClass,
		   vdialogOPEN_ITEM,      /* open the item in a dialog */
		   dwiOpenItem);
	
	vclassSet (defaultClass,
		   vdialogCLOSE_ITEM,     /* close the item down */
		   dwiCloseItem);
	
	vclassSet (defaultClass,
		   vdomainviewSET_DOMAIN, /* associate a domain to the view */
		   dwiSetDomain);

	vclassSet (defaultClass,
		   vdomainviewDRAG_OUTLINE_WITH, /* do our pinning in here */
		   dwiDragOutlineWith);

	vclassSet (defaultClass,
		   vdomainviewHANDLE_TRACK_EVENT, /* get initial position */
		   dwiHandleTrackEvent);

	vclassSet (defaultClass,
		   vdomainviewHANDLE_SCROLL_EVENT, /* propagate bounds change */
		   dwiHandleScrollEvent);

	vclassSet (defaultClass,
		   vdomainviewHANDLE_RESIZE_EVENT, /* propagate bounds change */
		   dwiHandleResizeEvent);
    }
    
    return (defaultClass);

} /* dwiGetDefaultDomainviewClass */




/* dwiAppendItem -- Utility function for appeneding a dialog item to
 *		    the subclassed domainview's item list.  This does
 *		    *not* add a vdomainObject for you.  This call 
 *		    gives up ownership of the dialog item.
 *
 *  -> view   -- one of our subclassed domainviews
 *  -> item   -- the item to add to our itemlist. 
 */
static void dwiAppendItem (vdomainview *view, vdialogItem *item)
{
    /* add it to the itemlist. */
    vdialogAppendItemListItem (_itemList(view), item);

    /* if the domainview is currently open, open the now so that it
     * can handle events and be drawn */
    if (vdialogItemIsOpen(vdomainviewGetItem(view))) {
	vdialogOpenItem (item);
    }

} /* dwiAppendItem */



/*
 * ---------- Using dwi ----------
 */



/* dwiDrawObjectProc -- a domainview object drawing procedure.
 *
 *  -> view	-- the domainview being drawn in
 *  -> object	-- the domain object to draw
 *
 * This is the form you should use for your draw procs.  Look at the 
 * object type.  If it's dwiDIALOG_ITEM, do a vdialogDrawItem() on
 * the value under the object's data field.  Otherwise, do whatever drawing
 * is appropriate for your application.
 *
 * If you do use your own domain object types, start off with the number
 * dwiLAST_DOMAIN_OBJECT_ID.
 */
static void dwiDrawObjectProc (vdomainview *view, vdomainObject *object,
			       vdrawcontext *context)
{
#if HERE_FOR_COMPLETENESS
    /* vdoamingGetObjectData/Type are currently macros that don't actually
     * use the domain pointer, leading to fun and exciting compiler warnings
     * about "unused variable "domain".  The data type and initialziation are
     * left here so they can be appreciated in their full and complete glory,
     * but are ifdef'd out so we tell the compiler to go stuff itself.
     */
    vdomain *domain = vdomainviewGetDomain (view);
#endif
    int type = vdomainGetObjectType (domain, object);

    if (type == dwiDIALOG_ITEM) {
	vdialogItem *item = (vdialogItem*)vdomainGetObjectData(domain, object);
	vdrawcontext *itemContext;

	itemContext = vdrawcontextClone(context);
	vdialogSetItemPenAttributes(item, vdrawcontextGetPen(itemContext));
	vdialogDrawItemWith(item, itemContext);
	vdrawcontextDestroy(itemContext);
    } else if (type == dwiGENERIC_BOX_OBJECT) {
	vdrawcontextDrawRectanglesInside(context,
					 vdomainGetObjectBounds(domain,object),
					 1);
    }
} /* dwiDrawObjectProc */



static void _sampleButtonNotify (vbutton *button, vevent *event)
{
    vcharDumpF(vdebugGetInfoStream(), "blarf\n");
} /* _sampleButtonNotify */



/* _populateDomain -- This creates and adds dialog items to the 
 * 		      domain and our subclassed domainview.
 *
 *  -> domain -- the domain to add new objects to
 *  -> view   -- the view looking at the domain.
 *
 * The reader's digest version of what to do is this:
 *   -- vdomainAddObject (...)
 *   -- <create or load some dialog item.  Initialize it too.>
 *   -- vdialogSetItemRect (item, someRectangle); (same rect as above)
 *   -- vdomainSetObjectType (..., dwiDIALOG_ITEM)
 *   -- vdomainSetObjectBounds (..., someRectange);
 *   -- dwiAppendItem (view, item);
 *   -- vdomainShowObjects (...)
 */
static void _populateDomain (vdomain *domain, vdomainview *view)
{
    vdomainObject    *object;
    vbutton *button;
    vcontrol *control;
    vrect rect;
    vlistitem *listitem;
    vtextitem *textitem;

    /* give us lots of space to breathe in */
    vdomainResize (domain, 1000, 1000);

    /*
     * add a button
     */

    /* add a new object */
    object = vdomainAddObject (domain);

    /* make a new button */
    button = vbuttonCreate ();
    vbuttonSetTitleScribed (button, vcharScribeLiteral("Fnord"));

    /* set the rectagles */
    vrectSet (50, 100, 80, 30, &rect);
    vdialogSetItemRect (vbuttonGetItem(button), &rect);
    vdomainSetObjectBounds (domain, vdomainObjectToSet(object), &rect);

    /* set the object's state */
    vdomainShowObjects (domain, vdomainObjectToSet(object));
    vdomainSetObjectType (domain, vdomainObjectToSet(object), dwiDIALOG_ITEM);
    vdomainSetObjectData (domain, vdomainObjectToSet(object), button);
    dwiAppendItem (view, vbuttonGetItem(button));



    /*
     * add another button
     */


    object = vdomainAddObject (domain);

    button = vbuttonCreate ();
    vbuttonSetTitleScribed (button, vcharScribeLiteral("Spam"));
    vbuttonSetNotify (button, _sampleButtonNotify);


    vdialogSetItemBackground(vbuttonGetItem(button), vcolorGetWhite());
    vdialogSetItemFont(vbuttonGetItem(button),
		       vfontFindScribed(vcharScribeLiteral("face:italic-12")));


    vrectSet (0, 140, 80, 30, &rect);
    vdialogSetItemRect (vbuttonGetItem(button), &rect);
    vdomainSetObjectBounds (domain, vdomainObjectToSet(object), &rect);

    vdomainShowObjects (domain, vdomainObjectToSet(object));
    vdomainSetObjectType (domain, vdomainObjectToSet(object), dwiDIALOG_ITEM);
    vdomainSetObjectData (domain, vdomainObjectToSet(object), button);
    dwiAppendItem (view, vbuttonGetItem(button));


    /*
     * add a scrollbar
     */


    object = vdomainAddObject (domain);

    control = vsliderCreateScrollBar ();

    vrectSet (100, 200, 100, 16, &rect);
    vdialogSetItemRect (vcontrolGetItem(control), &rect);
    vdomainSetObjectBounds (domain, vdomainObjectToSet(object), &rect);

    vdomainShowObjects (domain, vdomainObjectToSet(object));
    vdomainSetObjectType (domain, vdomainObjectToSet(object), dwiDIALOG_ITEM);
    vdomainSetObjectData (domain, vdomainObjectToSet(object), control);

    vcontrolSetMax (control, 100);
    vcontrolSetMin (control, 0);
    vcontrolSetPage (control, 10);
    vcontrolSetView (control, 30);
    vcontrolSetValue (control, 23);

    dwiAppendItem (view, vcontrolGetItem(control));


    /*
     * add a checkbox
     */


    object = vdomainAddObject (domain);

    control = vcontrolCreateToggle ();

    vcontrolSetAlternateStyle (control, TRUE);

    vcontrolSetTitleScribed (control, vcharScribeLiteral("Spam"));
    vrectSet (150, 250, 100, 16, &rect);
    vdialogSetItemRect (vcontrolGetItem(control), &rect);
    vdomainSetObjectBounds (domain, vdomainObjectToSet(object), &rect);

    vdomainShowObjects (domain, vdomainObjectToSet(object));
    vdomainSetObjectType (domain, vdomainObjectToSet(object), dwiDIALOG_ITEM);
    vdomainSetObjectData (domain, vdomainObjectToSet(object), control);

    vcontrolSetValue (control, 1);

    dwiAppendItem (view, vcontrolGetItem(control));


    /*
     * add a listitem
     */

    object = vdomainAddObject (domain);

    listitem = vlistitemCreate ();
    
    vrectSet (295, 10, 150, 175, &rect);
    vdialogSetItemRect (vlistitemGetItem(listitem), &rect);
    vdomainSetObjectBounds (domain, vdomainObjectToSet(object), &rect);

    vdomainShowObjects (domain, vdomainObjectToSet(object));
    vdomainSetObjectType (domain, vdomainObjectToSet(object), dwiDIALOG_ITEM);
    vdomainSetObjectData (domain, vdomainObjectToSet(object), listitem);

    vlistitemAppendScribed (listitem, vcharScribeLiteral("bork"));
    vlistitemAppendScribed (listitem, vcharScribeLiteral("ni pop"));
    vlistitemAppendScribed (listitem, vcharScribeLiteral("hoover"));
    vlistitemAppendScribed (listitem, vcharScribeLiteral("greeble"));
    vlistitemAppendScribed (listitem, vcharScribeLiteral("fnord"));
    vlistitemAppendScribed (listitem, vcharScribeLiteral("blarf"));
    vlistitemAppendScribed (listitem, vcharScribeLiteral("ekky"));
    vlistitemAppendScribed (listitem, vcharScribeLiteral("wizzel"));
    vlistitemAppendScribed (listitem, vcharScribeLiteral("poohbah"));
    vlistitemAppendScribed (listitem, vcharScribeLiteral("ni peng"));

    vlistitemAppendScribed (listitem, vcharScribeLiteral("bork"));
    vlistitemAppendScribed (listitem, vcharScribeLiteral("ni pop"));
    vlistitemAppendScribed (listitem, vcharScribeLiteral("hoover"));
    vlistitemAppendScribed (listitem, vcharScribeLiteral("greeble"));
    vlistitemAppendScribed (listitem, vcharScribeLiteral("fnord"));
    vlistitemAppendScribed (listitem, vcharScribeLiteral("blarf"));
    vlistitemAppendScribed (listitem, vcharScribeLiteral("ekky"));
    vlistitemAppendScribed (listitem, vcharScribeLiteral("wizzel"));
    vlistitemAppendScribed (listitem, vcharScribeLiteral("poohbah"));
    vlistitemAppendScribed (listitem, vcharScribeLiteral("ni peng"));

    vlistitemSetSelectMethod (listitem, vlistFREE_SELECTION);

    dwiAppendItem (view, vlistitemGetItem(listitem));
    

    /*
     * add a textitem
     */

    object = vdomainAddObject (domain);

    textitem = vtextitemCreate ();
    
    vrectSet (295, 200, 150, 32, &rect);
    vdialogSetItemRect (vtextitemGetItem(textitem), &rect);
    vdomainSetObjectBounds (domain, vdomainObjectToSet(object), &rect);

    vdomainShowObjects (domain, vdomainObjectToSet(object));
    vdomainSetObjectType (domain, vdomainObjectToSet(object), dwiDIALOG_ITEM);
    vdomainSetObjectData (domain, vdomainObjectToSet(object), textitem);

    vtextitemSetTextScribed (textitem, vcharScribeLiteral ("Greeble Bork"));

    dwiAppendItem (view, vtextitemGetItem(textitem));


    /*
     * add some generic domain items
     */
    
    object = vdomainAddObject (domain);

    vrectSet (3, 3, 30, 30, &rect);
    vdomainSetObjectBounds (domain, vdomainObjectToSet(object), &rect);
    vdomainShowObjects (domain, vdomainObjectToSet(object));
    vdomainSetObjectType (domain, vdomainObjectToSet(object), 
			  dwiGENERIC_BOX_OBJECT);

    object = vdomainAddObject (domain);

    vrectSet (33, 33, 30, 30, &rect);
    vdomainSetObjectBounds (domain, vdomainObjectToSet(object), &rect);
    vdomainShowObjects (domain, vdomainObjectToSet(object));
    vdomainSetObjectType (domain, vdomainObjectToSet(object), 
			  dwiGENERIC_BOX_OBJECT); /* any ID will do */

    object = vdomainAddObject (domain);

    vrectSet (63, 63, 35, 35, &rect);
    vdomainSetObjectBounds (domain, vdomainObjectToSet(object), &rect);
    vdomainShowObjects (domain, vdomainObjectToSet(object));
    vdomainSetObjectType (domain, vdomainObjectToSet(object), 
			  dwiGENERIC_BOX_OBJECT); /* any ID will do */



} /* _populateDomain */


/*
 * ---------- Driver program setup ----------
 */


/* _tryoutIssue -- issue function for a checkbox.  This toggles the 
 *		   "tryout" state of the subclassed domainview.
 */
static int _tryoutIssue (vcommandFunction *command, vdict *attr2value)
{
    dwiDomainview *view = (dwiDomainview*)vdictLoad(attr2value, vname_Data);

    view->tryout = (vdictLoad (attr2value, vname_Toggle) == vname_On);

    return (TRUE);
} /* _tryoutIssue */



static int _horizIssue (vcommandFunction *command, vdict *attr2value)
{
    dwiDomainview *view = (dwiDomainview*)vdictLoad(attr2value, vname_Data);

    view->horizPin = (vdictLoad (attr2value, vname_Toggle) == vname_On);

    return (vTRUE);
} /* _horizIssue */



/* _setupDialog -- initialize a dialog for action.
 */
static void _setupDialog (vdialog *dialog)
{
    vdomainview      *view;
    vdomain 	     *domain;
    vdomainSelection  selection;
    vdialogItem	     *item;

    view = (vdomainview*)vdialogFindItem (dialog, TAG("Canvas"));
    domain = vdomainCreate ();
    selection = vdomainCreateSelection (domain);
    vdomainviewSetDomain (view, domain);
    vdomainviewSetSelection (view, selection);

    vdomainviewSetScrollbarMargin (view, 8);
    vdomainviewSetHorzBar (view, TRUE);
    vdomainviewSetVertBar (view, TRUE);

    vdomainviewSetDrawObjectWithProc (view, dwiDrawObjectProc);

    _populateDomain (domain, view);

    item = vdialogFindItem (dialog, TAG("Horizontal pin"));
    vdialogSetItemData (item, view);

    item = vdialogFindItem (dialog, TAG("Try out"));
    vdialogSetItemData (item, view);
    vcontrolSetValue ((vcontrol*)item, 1);
    
} /* _setupDialog */



/* clean up any mess we made with the dialog */
static void _shutdownDialog (vdialog *dialog)
{
    /* everything but the vdialog destroy */
} /* _shutdownDialog */




/* one-time program setup */
static void _generalSetup (void)
{
    (void) dwiGetDefaultDomainviewClass ();

} /* _generalSetup */




/* one-time program shutdown */
static void _generalShutdown (void)
{

} /* _generalShutdown */




/*
 * ----- Generic Scaffolding follows
 */


static int _quitIssue (vcommandFunction *command, vdict *attr2value)
{
    veventStopProcessing ();
    return (TRUE);
} /* _quitNotify */



static int _closeIssue (vcommandFunction *command, vdict *attr2value)
{
    veventStopProcessing ();
    return (TRUE);
} /* _closeIssue */



typedef struct commandDef {
    const char	       *tagName;
    vcommandFunc	issueFunc;
    vcommandFunc	queryFunc;
} commandDef;


static commandDef commandTable[] = {
    { "Close",		       _closeIssue,		NULL },
    { "Quit",		       _quitIssue,		NULL },
    { "Try out",	       _tryoutIssue,		NULL },
    { "Horizontal pin",	       _horizIssue,		NULL },
    { NULL,		       NULL,			NULL }
};



static void _setupCommands (vdialog *dialog)
{
    vcommandFunction	*functionCommand;
    vcommandSpace	*commandSpace;
    vdict		*commandDict;
    commandDef		*commandScan;

    commandDict = vdictCreate (vnameHash);
    commandSpace = vcommandCreateSpace ();

    for (commandScan = commandTable;
	 commandScan->tagName != NULL; commandScan++) {
	
	functionCommand = (vcommandCreateFunctionOfClass 
			   (vcommandGetDefaultFunctionClass()));
	
	if (commandScan->issueFunc) {
	    vcommandSetFunctionIssue (functionCommand, commandScan->issueFunc);
	}

	if (commandScan->queryFunc) {
	    vcommandSetFunctionQuery (functionCommand, commandScan->queryFunc);
	}

	vdictStore (commandDict, TAG(commandScan->tagName), functionCommand);
    }

    vcommandAddSpaceDictOwned (commandSpace, vname_Command, commandDict);
    vwindowSetSpaceOwned (vdialogGetWindow(dialog), commandSpace);
    
} /* _setupCommands */






int main (int argc, char *argv[])
{
    vresource appres, dialogres;
    vdialog  *dialog;

    vstartup (argc, argv);

    _generalSetup ();

    appres = vapplicationGetResources (vapplicationGetCurrent());
    dialogres = vresourceGet (appres, TAG("Dialog"));

    dialog = vdialogLoad (dialogres);

    _setupCommands (dialog);

    _setupDialog (dialog);

    vdialogOpen (dialog);

    veventProcess ();

    _shutdownDialog (dialog);

    vdialogDestroy (dialog);

    _generalShutdown ();

    exit (EXIT_SUCCESS);
    return (EXIT_FAILURE);

} /* main */





/*
 * Formatting information for emacs in c-mode
 *
 * Local Variables:
 * c-indent-level:4
 * c-continued-statement-offset:0
 * c-brace-offset:0
 * c-brace-imaginary-offset:0
 * c-argdecl-indent:0
 * c-label-offset:0
 * End:
 */

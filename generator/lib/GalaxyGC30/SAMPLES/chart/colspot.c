/* $Id: colspot.c,v 1.4 1997/10/09 22:19:08 bill Exp $ */
/* The legal types make me put this in here.
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
 * copyright notice in the form of "Copyright 1994 Visix Software Inc.,
 * 11440 Commerce Park Drive, Reston, VA  22091. All Rights Reserved" appears
 * in all copies, (ii) both the copyright notice and this permission notice
 * appear in supporting documentation and (iii) you are a valid licensee of
 * Galaxy Application Environment.
 *
 * Do not taunt Happy Fun Ball
 */

/* colspot.c -- Implementation of a color-swatch editing thingie
 *
 * Module:
 *	xcolorspot
 *
 * Docs and description are in xcolspot.h
 *
 * See file chart.c for more comments about this whole project.
 */


#define _xcolorspotCLASS_NAME "xcolorspot"


#ifndef  vportINCLUDED
#include <vport.h>		/* for v*HEADER */
#endif

#ifndef  vclassINCLUDED
#include vclassHEADER
#endif

#ifndef  vcolorchsrINCLUDED
#include vcolorchsrHEADER
#endif

#ifndef  vdialogINCLUDED
#include vdialogHEADER
#endif

#ifndef  veventINCLUDED
#include veventHEADER
#endif

#ifndef  vobjectINCLUDED
#include vobjectHEADER
#endif

#include "xcolspot.h"




/*
 * ----- Module private globals
 */


/* this is the class that implements the default behavior for this 
 * module.  It's setup in xcolorspotGetDefaultClass(), and destroyed
 * automagically by the class manager.
 */
static vdialogItemClass *defaultClass = NULL;


/* this is the colorchooser used by all of the color spots when clicked-
 * on to be edited.
 */
static vcolorchsr *colorChooser = NULL;




/*
 * ----- The rest of the stuff 
 */


/* _xcolorspotShutdown -- clean up any mess this module may have made.
 */
static void _xcolorspotShutdown (void)
{
    /* don't need to check for NULLness -- this shutdown function wouldn't've
     * been installed if the color chooser didn't exist/
     */
    vcolorchsrDestroy (colorChooser);
} /* _xcolorspotShutdown */




/* _xcolorspotChooserApply -- notify function for the color chooser.
 *			      the notify of the item is called and the
 *			      backgroundcolor for the item is changed
 *			      (but not in that order.)
 *
 *  -> chooser -- the color chooser that had a color choosed from it
 *  -> color   -- the color that was choosed.
 */
static void _xcolorspotChooserApply (vcolorchsr *chooser, vcolor *color)
{
    vdialogItem *spot = (vdialogItem*)vcolorchsrGetData (chooser);
    vevent *dummy = veventCreateClient();

    vdialogSetItemBackground (spot, color);

    vdialogNotifyItem (spot, dummy);
    veventDestroy(dummy);

} /* _xcolorspotChooserApply */




/* _xcolorspotOpenChooser -- Create/open the chooser when the spot is
 *			     clicked on.  It's placed immediately above the
 *			     dialog that contains the color spot.  (well, only
 *			     the first time.  It's assumed that after that,
 *			     the user has put the color chooser in a more
 *			     convenient spot.
 *
 *  -> spot -- the colorspot that wants a chooser opened for it
 */
static void _xcolorspotOpenChooser (vdialogItem *spot)
{
    if (colorChooser == NULL) {
	colorChooser = vcolorchsrCreate ();
	vwindowPlace (vdialogGetWindow(vcolorchsrGetDialog(colorChooser)),
		      vdialogGetWindow(vdialogDetermineItemDialog(spot)),
		      vrectPLACE_ALIGN | vrectPLACE_LEFT,
		      vrectPLACE_NEAR  | vrectPLACE_TOP);
	vcolorchsrSetApply (colorChooser, _xcolorspotChooserApply);
	vclientRegisterShutdown (_xcolorspotShutdown);
    }

    vcolorchsrSetColor (colorChooser, vdialogDetermineItemBackground(spot));
    vcolorchsrSetData (colorChooser, spot);
    vcolorchsrOpen (colorChooser);

} /* _xcolorspotOpenChooser */




/* _xcolorspotHandleItemButtonDown -- handle a mouse-click in the spot.
 *				      All it does is set the drag for the
 *				      dialog so that we'll get told about
 *				      the button up.  We *don't* want to
 *				      do the work on the button down `cause
 *				      the user might change her/his/its mind.
 *
 *  -> spot  -- the colorspot that's been clicked on
 *  -> event -- the event that did it
 * <-	     -- TRUE if we handled the event, FALSE otherwise.
 */
static int _xcolorspotHandleItemButtonDown (vdialogItem *spot, vevent *event)
{
    vdialogSetDrag (vdialogDetermineItemDialog(spot), spot);
    return (TRUE);
} /* _xcolorspotHandleItemButtonDown */
    
    


/* _xcolorspotHandleItemButtonUp -- open a color chooser if the user clicked
 *				    on one of our spots.
 *
 *  -> spot  -- the colorspot mouse-upped on
 *  -> event -- the event that done did it
 * <-	     -- TRUE if we handled the event FALSE otherwise
 */
static int _xcolorspotHandleItemButtonUp (vdialogItem *spot, vevent *event)
{
    if (vrectContainsPoint (vdialogGetItemRect (spot),
			    veventGetPointerX(event),
			    veventGetPointerY(event))) {
	_xcolorspotOpenChooser (spot);
	return (TRUE);
    } else {
	return (vclassSendSuper (defaultClass, vdialogHANDLE_ITEM_BUTTON_UP,
				 (spot, event)));
    }
} /* _xcolorspotHandleItemButtonUp */




/* _xcolorspotDrawItem -- draw the color spot
 *
 *  -> spot -- on loan from Leader Kibo
 */
static void _xcolorspotDrawItem (vdialogItem *spot)
{
    const vrect *rect = vdialogGetItemRect (spot);
    
    vdrawGSave ();
    
    vdrawSetColor (vdialogDetermineItemBackground(spot));

    vdrawRectsFill (rect, 1);

    vdrawSetColor (vdialogDetermineItemForeground(spot));
    vdrawSetLineWidth (vdialogDetermineItemLineWidth(spot));
    vdrawRectsStrokeInside (rect, 1);

    vdrawGRestore ();

} /* _xcolorspotDrawItem */




/* xcolorspotGetDefaultClass -- Returns the class used to create new instances
 *			        of xcolorspot objects.
 */
vdialogItemClass *xcolorspotGetDefaultClass (void)
{
    if (defaultClass == NULL) {
	defaultClass = vclassReproduce (vdialogGetDefaultItemClass());

	vclassSetNameScribed (defaultClass,
			      vcharScribeLiteral (_xcolorspotCLASS_NAME));

	vclassSet (defaultClass,
		   vdialogDRAW_ITEM,
		   _xcolorspotDrawItem);

	vclassSet (defaultClass,
		   vdialogHANDLE_ITEM_BUTTON_DOWN,
		   _xcolorspotHandleItemButtonDown);

	vclassSet (defaultClass,
		   vdialogHANDLE_ITEM_BUTTON_UP,
		   _xcolorspotHandleItemButtonUp);

    }

    return (defaultClass);

} /* xcolorspotGetDefaultClass */


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

/* status.c -- a status dialog item
 *
 *
 *
 * Gotta have some legalese:
 * The following Sample Code is provided for your reference purposes in
 * connection with your use of the Galaxy Application Environment (TM) software
 * product which you have licensed from Visix Software, Inc. ("Visix").
 * The Sample code is provided to you without any warranty of any kind
 * whatsoever and you agree to be responsible for the use and/or incorporation
 * of the Sample Code into any software product you develop. You agree to fully
 * and completely indemnify and hold Visix harmless from any and all loss,.
 * claim, liability or damages with respect to your use of the Sample Code.  
 *
 * Subject to the foregoing, you are permitted to copy, modify, and distribute
 * the Sample Code for any purpose and without fee, provided that (i) a
 * copyright notice in the in the form of "Copyright 1994 Visix Software Inc.,
 * 11440 Commerce Park Drive, Reston, VA  22091. All Rights Reserved" appears
 * in all copies, (ii) both the copyright notice and this permission notice
 * appear in supporting documentation and (iii) you are a valid licensee of
 * Galaxy Application Environment.
 *
 * Do not taunt Happy Fun Ball.
 */

#include <vport.h>

#ifndef vdialogINCLUDED
#include vdialogHEADER
#endif

#ifndef vimageINCLUDED
#include vimageHEADER
#endif

#include "xstatus.h"


/*
 * ----- Module global variables, constants, and macros
 */

/* the class pointer for our dialog item subclass
 */
static xstatusClass *g_defaultClass;

/* the striped pattern to use when we're in barbershop-pole mode
 */
static vimage *g_stripeImage;


/* this is the width and height of the stripe image.
 */
#define IMAGE_SIZE 16


/* the bits for the stripe pattern.  There is probably an easier way than
 * marching over this table, but hey, it's only done once, and the table
 * looks kinda cool
 */
static int 
g_stripePattern[] = { 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0,
		      1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0,
		      1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1,
		      1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 
		      1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 
		      0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 
		      0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 
		      0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0,
		      0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0,
		      1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0,
		      1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1,
		      1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 
		      1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 
		      0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 
		      0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 
		      0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0 };


#define _xstatusIsBarberPole(s)	((s)->max == xstatusNO_VALUE)

/*
 * ----- Utility functions
 */


/* _xstatusConstructStripeImage -- make the stripe pattern so that it can
 * 				   eventually be drawn
 */
static void _xstatusConstructStripeImage (void)
{
    vpixmapScanner scanner;
    int i, j, *scan = g_stripePattern;

    g_stripeImage = vimageCreateSpecific (IMAGE_SIZE, IMAGE_SIZE, 2);

    vpixmapInitScanner (&scanner, vimageGetMap(g_stripeImage));

    for (i = 0; i < IMAGE_SIZE; i++) {
	for (j = 0; j < IMAGE_SIZE; j++) {
	    vpixmapWriteAt (&scanner, i, j, *scan);
	    scan++;
	}
    }

} /* _xstatusConstructStripeImage */




/* _xstatusCalcDoneRect -- calculate the "this much as been done" portion
 *			   of the status thingie.
 *
 *  -> status  -- the status bar that needs its done area calculated
 * <-          -- the done region to be colored-in
 */
static void _xstatusCalcDoneRect (xstatus *status, vrect *rect)
{
    *rect= *vdialogGetItemRect (xstatusGetItem(status));
   
#if (vdebugDEBUG)
    /* calculating this doesn't make sense for barber-pole mode */
    if (_xstatusIsBarberPole(status)) {
	vexGenerate (vexGetModuleClass(), vexERRNO, 0, vexMESSAGE,
		     "_xstatusCalcDoneRect - trying to calculate when should"
		     " just be doing image-thang.", vexNULL);
    }
#endif

    rect->w = (double)(rect->w) * (  (double)status->value 
				   / (double)status->max);

    /* don't draw over the border - we'll get screen flash if we do */
    if (vdialogItemHasBorder(xstatusGetItem(status))) {
	vrectInset (rect, 1, 1, rect);
    }

} /* _xstatusCalcDoneRect */




/*
 * ----- Method implementation
 */


/* _xstatusLoadInit -- load a status object from a resource template
 *
 *  -> status   -- the status object to initialize
 *  -> resource -- the resource template to use
 */
static void _xstatusLoadInit (xstatus *status, vresource resource)
{
    vclassSendSuper (g_defaultClass, vobjectLOAD_INIT, (status, resource));

    /* initialize to default value (e.g. barbershopPole mode) */
    status->max = xstatusNO_VALUE;
    status->value = xstatusNO_VALUE;
    status->lastUpdate = vtimestampMake (0, 0);

} /* _xstatusLoadInit */




/* _xstatusDrawItem -- draw a status box
 *
 *  -> status -- the status thingie to draw
 *
 * This can draw itself in two ways -- as a percentage of a total done, or
 * as a walking barberPole.  If the max-value is xstatusNO_VALUE, it uses
 * barberPole drawing mode.
 *
 * The percentage-of-a-total should be done when you know the bounds of
 * your calculations (like computing an image), and should be barberPole
 * when you don't know the bonds (like walking a networked file system)
 */
static void _xstatusDrawItem (xstatus *status)
{
    vdialogItem *item = xstatusGetItem (status);
    vrect rect;

    /* we're going to funge the drawing state, so save it so we can restore
     * it later
     */
    vdrawGSave (); {

	/* draw the walking stripes */
	if (_xstatusIsBarberPole(status)) {
	    int fudge; /* how far to offset drawing to get the stripes moving*/

	    vcolorPalette *palette; /* we change the image's palette to match*/
	    vcolorSpec *spec;	    /* that of the dialogItem */

	    vrect source; /* soure rectangle for the drawing operation.  Making
			   * this begger than the image will cause the image
			   * to tile rather that being stretched */

	    /* make the image if need-be */
	    if (g_stripeImage == NULL) {
		_xstatusConstructStripeImage ();
	    }

	    /* set the color palette to the dialogItem's foreground and
	     * background colors
	     */
	    palette = vimageGetPalette (g_stripeImage);

	    spec = vcolorGetPaletteSpecAt (palette, 0);
	    vcolorCopySpec(vcolorGetSpec(vdialogDetermineItemBackground(item)),
			   spec);

	    spec = vcolorGetPaletteSpecAt (palette, 1);
	    vcolorCopySpec(vcolorGetSpec(vdialogDetermineItemForeground(item)),
			   spec);

	    
	    /* get the area on the screen we're going to draw */
	    rect = *vdialogGetItemRect (item);

	    /* inset over the border */
	    vrectInset (&rect, 1, 1, &rect);

	    vdrawGSave (); {
		/* clip to the visible area.  We need to do this because we
		 * shift the rectangle we're drawing into so we can get an
		 * animation effect.  Without the clipping, the area to the
		 * left of the status bar will get junk drawing
		 */
		vdrawRectsClip (&rect,1);

		/* shift the image by the value */
		fudge = status->value % IMAGE_SIZE;
		rect.x -= fudge;
		rect.w += fudge;
		
		/* tell the drawing manager how much space to tile over */
		source = rect;
		source.x = source.y = 0;
		
		/* draw this tiled area onto the screen */
		vdrawRectImage (g_stripeImage, &source, &rect);

		/* clean up our clipping mess so that the border can be drawn*/
	    } vdrawGRestore ();

	} else {
	    /* figure out how much of the done-area needs to be colored */
	    _xstatusCalcDoneRect (status, &rect);
	    
	    /* and draw it */
	    vdrawSetColor (vdialogDetermineItemBackground(item));
	    vdrawRectsFill (&rect, 1);
	}

	/* draw the border if necessary */
	if (vdialogItemHasBorder(item)) {
	    vdrawSetLineWidth (1);
	    vdrawSetColor (vdialogDetermineItemForeground(item));
	    vdrawRectsStrokeInside (vdialogGetItemRect(item), 1);
	}

    } vdrawGRestore ();

} /* _xstatusDrawItem */




/* _xstatusAdvanceTo -- advance the status item to a new value.
 *
 *  -> status -- the status object to advance to
 *  -> value  -- the value it should become
 *
 * If in barber-pople mode, the screen display is updated based on time,
 * rather than value, providing this is called often enough.  This gives
 * the user a real sense of feedback - if the value isn't advanced, the
 * barberpole won't move.
 */
static void _xstatusAdvanceTo (xstatus *status, long value)
{
    if (_xstatusIsBarberPole(status)) {
	long seconds;
	unsigned long nanoseconds;
	vtimestamp now = vtimestampGetNow ();

	/* figure out the time between now and the last update */
	vtimestampDiffer (now, status->lastUpdate, &seconds, &nanoseconds);

	/* only update every 1/10 second */
	if ((seconds > 0) || (nanoseconds > vtimestampSECOND / 10)) {
	    status->value += 2;
	    status->lastUpdate = now;
	    
	    /* opaque invalling is OK because the image will draw over the
	     * entire contents
	     */
	    vdialogInvalItem (xstatusGetItem(status), vwindowINVAL_OPAQUE);
	}

    } else {
	vrect beforeRect, afterRect;
	long oldValue = status->value;

	/* see how big the "done" area is now... */
	_xstatusCalcDoneRect (status, &beforeRect);

	/* if they pass xstatusNO_VALUE (or just call xstatusAdvance), advance
	 * counter by one
	 */
	status->value = (value == xstatusNO_VALUE) ? 1 : value;

	if (value < oldValue) {
	    /* if the value got smaller, we need to erase an area to be
	     * accurate.  In this case, just be lazy and inval the whole thing
	     * and get the erasing
	     */
	    vdialogInvalItem (xstatusGetItem(status), 0);
	} else {
	    /* see if the current "done" area is different than what's 
	     * currently visible.  If they're different, force a redraw, 
	     * otherwise do nothing.  (the user will see no change, so why
	     * waste time doing extra work?)
	     */

	    _xstatusCalcDoneRect (status, &afterRect);

	    if (!vrectMIsEqual(&beforeRect, &afterRect)) {
		/* opaque invalling is OK because the done area is getting
		 * bigger - no need to have anything erased
		 */
		vdialogInvalItem (xstatusGetItem(status), vwindowINVAL_OPAQUE);
	    }
	}
    }

} /* _xstatusAdvanceTo */




/* _xstatusSetMax -- set the maximum value the status thingie covers.
 *		     passing xstatusNO_VALUE means to switch to barber-pole
 *		     mode.
 *
 *  -> status -- the status bar to set the value for
 *  -> max    -- the extent of its range
 *
 * xstatus.h has a macro xstatusSetBarberPole that hides this fact from our
 * user.
 */
static void _xstatusSetMax (xstatus *status, long max)
{
#if (vdebugDEBUG)
    if ((max != xstatusNO_VALUE) && (max <= 0)) {
	vexGenerate (vexGetArgRangeClass(), vexERRNO, 0, vexMESSAGE,
		     "xstatusSetMax -- max needs to be > 0", vexNULL);
    }
#endif

    status->max = max;

    if ((max != xstatusNO_VALUE) && (status->value == xstatusNO_VALUE)) {
	status->value = 0;
    }

    /* we'll need to redraw.  Rather than having the logic to detect the
     * done-area getting smaller or larger, just erase the whole thing and
     * redraw it.  Hopefully the max won't be changed often enough to make
     * it flashy
     */
    vdialogInvalItem (xstatusGetItem(status), 0);

} /* _xstatusSetMax */




/*
 * ----- Housekeeping
 */


/* _xstatusShutdown -- free some global resources at the end of time
 */
static void _xstatusShutdown (void)
{
    if (g_stripeImage != NULL) {
	vimageDestroy (g_stripeImage);
    }

} /* _xstatusShutdown */




/* xstatusGetDefaultClass -- initialize the status class and return it
 *
 * <-  -- the class pointer for the status item
 */
xstatusClass *xstatusGetDefaultClass (void)
{
    if (g_defaultClass == NULL) {
	g_defaultClass = vclassSpawn (vdialogGetDefaultItemClass(),
				      sizeof(xstatusClass));
	vclassSetNameScribed (g_defaultClass, vcharScribeLiteral("xstatus"));
	vclassSetObjectSize (g_defaultClass, sizeof(xstatus));

	vclassSet (g_defaultClass,
		   vobjectLOAD_INIT,
		   _xstatusLoadInit);

	vclassSet (g_defaultClass,
		   vdialogDRAW_ITEM,
		   _xstatusDrawItem);

	vclassSet (g_defaultClass,
		   xstatusADVANCE_TO,
		   _xstatusAdvanceTo);
	
	vclassSet (g_defaultClass,
		   xstatusSET_MAX,
		   _xstatusSetMax);
	
	vclientRegisterGlobalShutdown (_xstatusShutdown);
    }

    return (g_defaultClass);

} /* xstatusGetDefaultClass */



/* Formatting information for emacs in c-mode
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

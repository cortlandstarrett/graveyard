/* $Id: citem.c,v 1.2 1993/11/30 19:42:27 markd Exp $ */
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

/* citem.c -- Implementation for a dialog item that will draw a chartview
 *
 * Module:
 *	gchartitem
 *
 * Descriptions and docs can be found in gcitem.h
 *
 * See file chart.c for more comments about this whole project.
 */


#define _gchartitemCLASS_NAME "gchartitem"


#ifndef   vportINCLUDED
#include <vport.h>		/* for v*HEADER */
#endif

#ifndef   vclassINCLUDED
#include  vclassHEADER
#endif

#ifndef   vdialogINCLUDED
#include  vdialogHEADER
#endif

#ifndef   vobjectINCLUDED
#include  vobjectHEADER
#endif

#ifndef   xcanvasINCLUDED
#include "xcanvas.h"
#endif

#ifndef   gcitemINCLUDED
#include "gcitem.h"
#endif

#ifndef   gcviewINCLUDED
#include "gcview.h"
#endif




/*
 * ----- Module private globals
 */


/* this is the class that implements the default behavior for this 
 * module.  It's setup in gchartitemGetDefaultClass(), and destroyed
 * automagically by the class manager.
 */
static gchartitemClass *defaultClass = NULL;




/*
 * ----- Chartitem method implementation
 */


/* _gchartitemSetChartview -- tell the chartitem to draw the chartview
 *			      inside of itself
 *
 *  -> item -- the chartitem to set a chartview for
 *  -> view -- the chartview to associate with the chartitem.
 */
static void _gchartitemSetChartview (gchartitem *item, gchartview *view)
{
    gdrawable *drawable;
    int i;

    item->chartview = view;

    for (i = 0; i < gchartviewGetDrawableCount(view); i++) {
        drawable = gchartviewGetDrawableAt (view, i);
        gdrawableSetAxisFont (drawable,
                              vdialogDetermineItemFont(gchartitemGetItem
                                                       (item)));
    }
    
} /* _gchartitemSetChartview */




/*
 * ----- xcanvas overrides
 */


/* _gchartitemDrawContent -- draw the guts of the canvas.  In this case, the
 *			     guts are a chartview.
 *
 *  -> item -- the chartitem to draw
 */
static void _gchartitemDrawContent (gchartitem *item)
{
    if (item->chartview != NULL) {
        gchartviewDraw (item->chartview);
    }
} /* _gchartitemDrawContent */




/* _gchartitemSetContentProc -- set the content proc for this canvas.  Since
 *				we're doing the drawing via overridding rather
 *				than a drawproc, setting the draw proc is
 *				a really asinine stupid boneheaded thing to
 *				do.  Soe we'll raise an exception. 
 *
 *  -> item -- the chartitem to set the content proc for
 *  -> proc -- the draw proc to use
 */  
static void _gchartitemSetContentProc (gchartitem *item, 
                                       gchartitemContentProc proc)
{
#if (vdebugDEBUG)
    vexGenerate (vexGetArgClass(),
                 vexMESSAGE, 
                 "Setting content proc for gchartitem is a useless operation.",
                 vexPROC_NAME, "_gchartitemSetContentProc",
                 vexNULL);
                 
#endif
} /* _gchartitemSetContentProc */




/* _gchartitemSetCanvasBounds -- set the bounds of the canvas - i.e. the area
 *				 the chartview will take up.  We need to tell
 *				 the chartview its new rectangle.
 *
 *  -> item   -- the charitem that's getting its bounds set
 *  -> width  -- the new width of the scrollable area
 *  -> height -- the new height of the scrollble area
 */
static void _gchartitemSetCanvasBounds (gchartitem *item, 
                                        int width, int height)
{
    vrect rect;

    vrectSet (0, 0, width, height, &rect);
    gchartviewSetRect (item->chartview, &rect);

    vclassSendSuper (defaultClass, xcanvasSET_CANVAS_BOUNDS,
                     (item, width, height));
    xcanvasInval (gchartitemGetCanvas(item), 0);

} /* _gchartitemSetCanvasBounds */




/*
 * ----- Object-level duties 
 */



/* _gchartitemLowInit -- shared initialiation code beteen the INIT and
 *			 LOAD_INIT overrides
 *
 *  -> item -- the chartiem to initialize
 */
static void _gchartitemLowInit (gchartitem *item)
{
    item->chartview = NULL;
} /* _gchartitemLowInit */




/* _gchartitemInit -- intialize a chart item
 *
 *  -> item -- the chartitem to initialize
 */
static void _gchartitemInit (gchartitem *item)
{
    vclassSendSuper (defaultClass, vobjectINIT, (item));
    _gchartitemLowInit (item);
} /* _gchartitemInit */




/* _gchartitemLoadInit -- initialize a chartitem from a resource template
 *
 *  -> item     -- the item to initialize
 *  -> resource -- the resource template to use
 */
static void _gchartitemLoadInit (gchartitem *item, vresource resource)
{
    vclassSendSuper (defaultClass, vobjectLOAD_INIT, (item, resource));
    _gchartitemLowInit (item);
} /* _gchartitemLoadInit */




/* _gchartitemDestroy -- nuke this pupper to oblivion
 *
 *  -> item -- the pupper to nuke
 */
static void _gchartitemDestroy (gchartitem *item)
{

    vclassSendSuper (defaultClass, vobjectDESTROY, (item));

} /* _gchartitemDestroy */




/*
 * ----- Managerial duties
 */


/* gchartitemGetDefaultClass -- Returns the class used to create new instances
 *			       of gchartitem objects.
 */
gchartitemClass *gchartitemGetDefaultClass (void)
{
    if (defaultClass == NULL) {

        defaultClass = vclassSpawn (xcanvasGetDefaultClass(),
                                    sizeof (gchartitemClass));
        vclassSetNameScribed (defaultClass,
                              vcharScribeLiteral(_gchartitemCLASS_NAME));
        vclassSetObjectSize (defaultClass, sizeof (gchartitem));


        vclassSet (defaultClass,
                   vobjectINIT,
                   _gchartitemInit);
        
        vclassSet (defaultClass,
                   vobjectLOAD_INIT,
                   _gchartitemLoadInit);

        vclassSet (defaultClass,
                   vobjectDESTROY,
                   _gchartitemDestroy);

        vclassSet (defaultClass,
                   xcanvasDRAW_CONTENT,
                   _gchartitemDrawContent);
        
        vclassSet (defaultClass,
                   xcanvasSET_CONTENT_PROC,
                   _gchartitemSetContentProc);

        vclassSet (defaultClass,
                   xcanvasSET_CANVAS_BOUNDS,
                   _gchartitemSetCanvasBounds);

        vclassSet (defaultClass,
                   gchartitemSET_CHARTVIEW,
                   _gchartitemSetChartview);
    }

    return (defaultClass);

}


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

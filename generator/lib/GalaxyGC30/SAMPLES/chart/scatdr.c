/* $Id: scatdr.c,v 1.3 1994/03/05 04:18:06 chad Exp $ */
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

/* scdraw.c -- Implementation of a chart drawable that does scatter charts.
 *
 * Module:
 *	gscatdraw
 *
 * Descriptions and docs can be found in gscdraw.h
 *
 * See file chart.c for more comments about this whole project.
 */


#define _gscatdrawCLASS_NAME "gscatdraw"

/* the default size of the data point splat */
#define _gscatdrawDEFAULT_POINT_SIZE 9


#ifndef   vportINCLUDED
#include <vport.h>		/* for v*HEADER */
#endif

#ifndef   vclassINCLUDED
#include  vclassHEADER
#endif

#ifndef   vcolorINCLUDED
#include  vcolorHEADER
#endif

#ifndef   vdrawINCLUDED
#include  vdrawHEADER
#endif

#ifndef   vobjectINCLUDED
#include  vobjectHEADER
#endif

#ifndef   vpointINCLUDED
#include  vpointHEADER
#endif

#ifndef   vrectINCLUDED
#include  vrectHEADER
#endif

#ifndef   gaccessINCLUDED
#include "gaccess.h"
#endif

#ifndef   gscatdrINCLUDED
#include "gscatdr.h"
#endif

#ifndef   gdrawbleINCLUDED
#include "gdrawble.h"
#endif




/*
 * ----- Module private globals
 */


/* this is the class that implements the default behavior for this 
 * module.  It's setup in gscatdrawGetDefaultClass(), and destroyed
 * automagically by the class manager.
 */
static gscatdrawClass *defaultClass = NULL;




/*
 * ----- Most Important Functions
 */


/* _gscatdrawDraw -- draw the drawable inside of the rectangle set to it
 *		     previously.
 *
 *  -> scat -- the scatter chart to draw
 *
 * !!! sorry, but the code in this pupper is rather unfocused and meandering
 */
static void _gscatdrawDraw (gscatdraw *scat)
{
    vrect arect = *gscatdrawGetRect(scat);
    vrect *rect = &arect;
    vpoint *points, *pointScan;

    int ymin, ymax, xmin, xmax, xrange, yrange, x, y, xspace, yspace;
    int i, val, pointCount, startIndex, stopIndex;
    vrect *labelRects, *rectScan;
    double xfudge, yfudge;
    int width, height;

    /* !!! using the index as for the X-axis is way-bogus.  It really should
     * !!! be using a vector in the accessor.
     */

    gaccessor *accessor = gscatdrawGetAccessorAt (scat, 0);

    vdrawGSave ();

    gscatdrawGetMarginSpace (scat, &xspace, &yspace);
    vrectInset (rect, yspace, xspace, rect);

    gscatdrawGetNaturalAxisSize(scat, &width, &height);

    if (gscatdrawGetDrawX(scat)) {
        gscatdrawDrawXAxis (scat);
        if (gscatdrawGetXPos(scat) == gdrawableBOTTOM_X) {
            rect->y += height;
        }
        rect->h -= height;
    }

    if (gscatdrawGetDrawY(scat)) {
        gscatdrawDrawYAxis(scat);
        if (gscatdrawGetYPos(scat) == gdrawableLEFT_Y) {
            rect->x += width;
        }
        rect->w -= width;
    }

    rect->x += gscatdrawGetLeftMargin (scat);
    rect->y += gscatdrawGetBottomMargin (scat);
    rect->w -= (gscatdrawGetLeftMargin(scat) + gscatdrawGetRightMargin(scat));
    rect->h -= (gscatdrawGetTopMargin(scat) + gscatdrawGetBottomMargin(scat));




    ymin = *((int*)gaccessorGetRangeMin(accessor));
    ymax = *((int*)gaccessorGetRangeMax(accessor));
    
    xmin = INT_MAX;
    xmax = INT_MIN;

    for (i = 0; i < gaccessorGetIndexCount(accessor); i++) {
        val = *((int*)gaccessorGetIndexValue(accessor, i));
        xmin = vMIN (xmin, val);
        xmax = vMAX (xmax, val);
    }

    xrange = xmax - xmin;
    yrange = ymax - ymin;

    gaccessorGetSubset (accessor, &startIndex, &stopIndex);

    if (   (startIndex == gaccessorUNDEFINED)
        || (stopIndex == gaccessorUNDEFINED)) {
        startIndex = 0;
        stopIndex = gaccessorGetIndexCount (accessor);
    }

    pointCount = stopIndex - startIndex;
    pointScan = points = vmemAlloc (sizeof(vpoint) * pointCount);
    rectScan = labelRects = vmemAlloc (sizeof(vrect) * pointCount);

    vdrawTranslate (rect->x, rect->y);

    for (i = startIndex; i < stopIndex; i++) {
        val = *((int*)gaccessorGetValue(accessor, i));
        val -= ymin;
        yfudge = (double)val / (double)yrange;
        y = yfudge * rect->h;
        

        val = *((int*)gaccessorGetIndexValue(accessor, i));
        val -= xmin;
        xfudge = (double)val / (double)xrange;
        x = xfudge * rect->w;

        if (scat->pointColor != NULL) {
            vdrawSetColor (scat->pointColor);
        }
        
        gscatdrawDrawPoint (scat, i, 0, x, y);

        pointScan->x = x;
        pointScan->y = y;
        pointScan++;
    }

    rect->x = 0;
    rect->y = 0;
    if (gscatdrawGetLabelFont(scat) != NULL) {
        gscatdrawPositionLabelRects (scat, points, labelRects,
                                     pointCount, rect);
        
        vdrawSetFont (gscatdrawGetLabelFont(scat));
        for (i = startIndex; i < stopIndex; i++) {
            if (scat->labelColor != NULL) {
                vdrawSetColor (scat->labelColor);
            }
            gscatdrawDrawLabel (scat, i, 0, rectScan);
            rectScan++;
        }
    }

    vmemFree (points);
    vmemFree (labelRects);

    vdrawGRestore ();

} /* _gscatdrawDraw */




/*
 * ----- scatdraw method implementation
 */


/* _gscatdrawSetPointDrawProc -- set the procedure that will draw the
 *				 scatter data points.  If no proc is supplied
 *				 (or NULL passed to this), then circles will
 *				 be drawn. 
 *
 *  -> scat -- the scatterchart to set the point draw proc for
 *  -> proc -- the draw proc to use.
 */
static void _gscatdrawSetPointDrawProc (gscatdraw *scat, 
                                        gscatdrawPointDrawProc proc)
{
    scat->pointDrawProc = proc;
} /* _gscatdrawSetPointDrawProc */




/* _gscatdrawDrawPoint -- draw something at the given point.  By default it
 *			  calls the pointDrawProc
 *
 *  -> scat      -- the scatter-draw that is doing the drawing
 *  -> index     -- the index of the data point being drawn
 *  -> vectorPos -- the position in the vector tuple of the actual hunka data
 *  -> x,y       -- where in the chart to center the drawing
 *
 * Index and VectorPos can be used to make decisions on what to draw if 
 * different data points or vector tuple locations have different images.
 *
 * if no pointdrawproc is supplied, then a circle is drawn.
 */
static void _gscatdrawDrawPoint (gscatdraw *scat, 
                                 int index, int vectorPos, int x, int y)
{
    if (scat->pointDrawProc) {
        (scat->pointDrawProc) (scat, index, vectorPos, x, y);
    } else {
        vdrawGSave ();
        
        vdrawSetLineWidth (0);
        vdrawArcN (x, y, gscatdrawGetPointHeight(scat)/2, 0, 360);
        vdrawStroke();

        vdrawGRestore ();
    }
} /* _gscatdrawDrawPoint */




/* _gscatdrawSetPointColor -- set the color used to draw the points in the
 *			      scatter chart.
 * 
 *  -> scat  -- the scatter chart to set the color for
 *  -> color -- the color to use to draw the points with 
 */
static void _gscatdrawSetPointColor (gscatdraw *scat, vcolor *color)
{
    scat->pointColor = color;
} /* _gscatdrawSetPointColor */




/* _gscatdrawSetLabelColor -- set the color the data point labels will be
 *			      drawn in. 
 *
 *  -> scat  -- the scatter chart to set the label color for
 *  -> color -- the color to draw the labels with
 */
static void _gscatdrawSetLabelColor (gscatdraw *scat, vcolor *color)
{
    scat->labelColor = color;
} /* _gscatdrawSetLabelColor */




/* _gscatdrawSetLabelFont -- set the font to use for drawing the labels for
 *			     the scatter chart
 *
 *  -> scat -- man, caruthers
 *  -> font -- the font of wisdom to use
 */
static void _gscatdrawSetLabelFont (gscatdraw *scat, vfont *font)
{
    scat->labelFont = font;
} /* _gscatdrawSetLabelFont */




/* _gscatdrawDrawLabel -- draw the label for a given index/tuple position. 
 *
 *  -> scat      -- the scatter chart draw thingie to draw the label for
 *  -> index     -- the index of the data point to use
 *  -> vectorPos -- the tuple position of the data point being labeled
 *  -> rect      -- the rectangle to draw it in.  This rect is calculated
 *		    by gscatdrawPositionLabelRects()
 */
static void _gscatdrawDrawLabel (gscatdraw *scat, int index, int vectorPos,
                                 const vrect *rect)
{
    const vchar *string;

    string = gaccessorGetValueName (gscatdrawGetAccessorAt(scat, 0), index);
    if (string != NULL) {
        vdrawRectShowCenterY (string, rect);
    }
} /* _gscatdrawDrawLabel */




/* _gscatdrawPositionLabelRects -- given the location of the data points in
 *				   the scatter graph, figure out where the 
 *				   the labels should be located.
 *
 *  -> scat       -- the scatterdrawthingie to position the rects for
 *  -> points     -- an array of vpoints representing the location of the
 *		     data points in the graph
 *  -> labelRects -- an uninitialized array of vrects that should be filled in
 *  -> count      -- the nubmer of points/labelRects
 *  -> bounds     -- the bounds of the entire chart, so that rects won't be
 *		     sitting outside of the bounds.
 *
 * This uses a simple algorithm -- position things to the right of the point,
 * centered vertically, and skootched over enough so that the chart marker
 * won't obliterate it.  If this rect straddles the bounds, move it to the
 * left of the point.
 *
 * Full-fledged layout so that all points and rects don't overlap is an
 * NP-Complete problem.  If you manage to solve it efficiently, you'll be
 * eternally famous and worshiped.
 */
static void _gscatdrawPositionLabelRects (gscatdraw *scat,
                                          const vpoint *points,
                                          vrect *labelRects, int count,
                                          const vrect *bounds)
{
    int i;
    int height;
    int width;
    int min, max;
    
    if (gscatdrawGetLabelFont(scat) != NULL) {
        gaccessor *accessor = gscatdrawGetAccessorAt(scat,0);
        height = gscatdrawGetPointHeight (scat);
        width = gscatdrawGetPointWidth (scat);
        
        height = vMAX (height, 
                      vfontDescent(scat->labelFont) 
                      + vfontAscent(scat->labelFont));

        gaccessorGetSubset (accessor, &min, &max);
        if (min == gaccessorUNDEFINED) {
            min = 0;
        }

        for (i = 0; i < count; i++) {
            int stringWidth;

            const vchar *string;
            string = gaccessorGetValueName (accessor, min + i);

            vfontStringWidth (scat->labelFont,
                              string, &stringWidth, &max); /* max==dummy */
            
            labelRects->x = points->x + width / 2;
            labelRects->y = points->y - (height / 2);
            labelRects->w = stringWidth;
            labelRects->h = height;
            
            if (!vrectMEncloses(bounds, labelRects)) {
                /* put on other side */
                labelRects->x = points->x - stringWidth - width;
            }
            
            points++;
            labelRects++;
        }
    }
} /* _gscatdrawPositionLabelRects */




/* _gscatdrawSetPointSize -- set the amount of screen real-estate that each
 *			     data point should occupy.
 *
 *  -> scat   -- the scatterdraw thingie to set the point size for
 *  -> width  -- how wide that pupper should be
 *  -> height -- how tall that pupper should be
 */
static void _gscatdrawSetPointSize (gscatdraw *scat, int width, int height)
{
    scat->pointWidth = width;
    scat->pointHeight = height;
} /* _gscatdrawSetPointSize */




/* _gscatdrawCalcLAbelSize -- figure out how big the label should be for
 *			      a particular data thingie.
 *
 *  -> scat      -- the scattergorical chart thingie
 *  -> index     -- the index of the thing to be labeled
 *  -> vectorPos -- the tuple index of the thing to be labeled
 * <-  width     -- how wide it wants to be
 * <-  height    -- how tall it wants to be
 *
 * !!! I think I forgot about this when I was implementing the rest of 
 * !!! this module
 */
static void _gscatdrawCalcLabelSize (gscatdraw *scat, 
                                     int index, int vectorPos,
                                     int *width, int *height)
{
} /* _gscatdrawCalcLabelSize */




/*
 * ----- drawable method overrides
 */


/* _gscatdrawDrawLegend -- draw the chart legend in the designated rectangle
 *
 *  -> scat -- the scatchartthingie to draw the legend for
 *  -> rect -- the rectangle to draw in.
 */
static void _gscatdrawDrawLegend (gscatdraw *scat, const vrect *rect)
{
} /* _gscatdrawDrawLegend */




/* _gscatdrawGetNaturalAxisSize -- returns the natural size for the X and Y
 *				   axis. These values are used by drawable
 *				   containers to set the margins of all of
 *				   its drawables so that they can share / not
 *				   step over other folks axes.
 *
 *  -> scat    -- the scattermongering thing to get the natural axis size for
 * <-  xheight -- the hegiht the X axis wants to be
 * <-  ywidth  -- the width the Y axis wants to be
 *
 * !!! the numbers below were just picked out of thin air
 */
static void _gscatdrawGetNaturalAxisSize (gscatdraw *scat,
                                          int *xheight, int *ywidth)
{
    *xheight = 30;
    *ywidth = 30;
} /* _gscatdrawGetNaturalAxisSize */




/* _gscatdrawAddAccessor -- add an accessor to the scattergram
 *
 *  -> scat     -- the splatter chart thingie
 *  -> accessor -- the accessor to use to draw the graph
 *
 * Each chart can only use one accessor, so generate an exception if the
 * client tries to add more than that.
 */
static void _gscatdrawAddAccessor (gscatdraw *scat, gaccessor *accessor)
{
    if (gscatdrawGetAccessorCount(scat) > 1)  {
#if (vdebugDEBUG)
        vexGenerate (vexGetArgClass(),
                     vexMESSAGE, 
                     "default scatdraw class can only use one accessor.",
                     vexPROC_NAME, "_gscatdrawAddAccessor",
                     vexArgPOSITION, 2, vexNULL);
#endif
    } else {
        vclassSendSuper (defaultClass, gdrawableADD_ACCESSOR,
                         (scat, accessor));
    }
} /* _gscatdrawAddAccessor */




/* _gscatdrawGetLegendNaturalSize -- get the size the legend for this
 *				     scatthing wants to be
 * 
 *  -> scat   -- the scatchartthing to get the legend size for
 * <-  width  -- the width it wants to be
 * <-  height -- the height it wants to be
 *
 * The current values are bogus -- they should really be calculated based
 * on point size, font size, etc...
 */
static void _gscatdrawGetLegendNaturalSize (gscatdraw *scat, 
                                            int *width, int *height)
{
    /* ??? */
    *width = 100;
    *height = 20;
} /* _gscatdrawGetLegendNaturalSize */




/*
 * ----- Object-level duties 
 */


/* _gscatdrawLowInit -- shared initializaiton code between the INIT and 
 *			LOAD_INIT overrides.
 *
 *  -> scat -- the chartscatthing to initialize
 */
static void _gscatdrawLowInit (gscatdraw *scat)
{
    scat->flags = _gscatdrawDIRTY;
    scat->pointCache = NULL;
    scat->labelCache = NULL;
    scat->pointColor = NULL;
    scat->labelColor = NULL;
    scat->labelFont = NULL;
    scat->pointWidth = scat->pointHeight = _gscatdrawDEFAULT_POINT_SIZE;

    scat->pointDrawProc = (gscatdrawPointDrawProc)NULL;
    
} /* _gscatdrawLowInit */




/* gscatdrawInit -- initialize a scatcharthingie.
 *
 *  -> scat -- the thingie to init.
 */
static void _gscatdrawInit (gscatdraw *scat)
{
    vclassSendSuper (defaultClass, vobjectINIT, (scat));
    _gscatdrawLowInit (scat);
} /* _gscatdrawInit */




/* _gscatdrawLoadInit -- initialize a scatcharthtingie based on a resource 
 *			 template
 *
 *  -> scat     -- the scatdrawchartthingie to init
 *  -> resource -- the resource template to use
 */
static void _gscatdrawLoadInit (gscatdraw *scat, vresource resource)
{
    vclassSendSuper (defaultClass, vobjectLOAD_INIT, (scat, resource));
    _gscatdrawLowInit (scat);
} /* _gscatdrawLoadInit */




/* _gscatdrawDestroy -- I'll nuke you, you'll nuke me.  we're a nuclear
 *			family.  With a mish-mash Barney-smash, the dino'll
 *			get his due.  Let's all squick Barney first me then
 *			you.
 *
 *  -> scat -- Barney must die.  Barney must die.  Barney must die.
 */
static void _gscatdrawDestroy (gscatdraw *scat)
{

    vclassSendSuper (defaultClass, vobjectDESTROY, (scat));
} /* _gscatdrawDestroy */





/*
 * ----- Managerial duties
 */


/* gscatdrawDump -- dumps human-readable debugging information to a particular
 *		    stream.
 *
 *  -> scat     -- the scatdraw to dump
 *  -> stream   -- the stream to dump it into
 */
void gscatdrawDump (gscatdraw *scat, FILE *stream)
{
    
#if (vdebugDEBUG)
    
    if (stream == NULL) {
        stream = vdebugGetInfoStream ();
    }
    
    gdrawableDump (gscatdrawGetDrawable(scat), stream);
    fprintf (stream, "    flags %x\n", scat->flags);
    
#endif
    
} /* gscatdrawDump */




/* gscatdrawGetDefaultClass -- Returns the class used to create new instances
 *			       of gscatdraw objects.
 */
gscatdrawClass *gscatdrawGetDefaultClass (void)
{
    if (defaultClass == NULL) {
        
        defaultClass = vclassSpawn (gdrawableGetDefaultClass(),
                                    sizeof (gscatdrawClass));
        vclassSetNameScribed (defaultClass,
                              vcharScribeLiteral(_gscatdrawCLASS_NAME));
        vclassSetObjectSize (defaultClass, sizeof (gscatdraw));
        
        vclassSet (defaultClass,
                   vobjectINIT,
                   _gscatdrawInit);
        
        vclassSet (defaultClass,
                   vobjectLOAD_INIT,
                   _gscatdrawLoadInit);
        
        vclassSet (defaultClass,
                   vobjectDESTROY,
                   _gscatdrawDestroy);
        
        vclassSet (defaultClass,
                   gdrawableDRAW,
                   _gscatdrawDraw);

        vclassSet (defaultClass,
                   gdrawableDRAW_LEGEND,
                   _gscatdrawDrawLegend);
        
        vclassSet (defaultClass,
                   gdrawableGET_NATURAL_AXIS_SIZE,
                   _gscatdrawGetNaturalAxisSize);
        
        vclassSet (defaultClass,
                   gdrawableADD_ACCESSOR,
                   _gscatdrawAddAccessor);
        
        vclassSet (defaultClass,
                   gdrawableGET_LEGEND_NATURAL_SIZE,
                   _gscatdrawGetLegendNaturalSize);

        vclassSet (defaultClass,
                   gscatdrawSET_POINT_COLOR,
                   _gscatdrawSetPointColor);

        vclassSet (defaultClass,
                   gscatdrawSET_LABEL_COLOR,
                   _gscatdrawSetLabelColor);

        vclassSet (defaultClass,
                   gscatdrawSET_LABEL_FONT,
                   _gscatdrawSetLabelFont);

        vclassSet (defaultClass,
                   gscatdrawSET_POINT_DRAW_PROC,
                   _gscatdrawSetPointDrawProc);

        vclassSet (defaultClass,
                   gscatdrawDRAW_POINT,
                   _gscatdrawDrawPoint);

        vclassSet (defaultClass,
                   gscatdrawDRAW_LABEL,
                   _gscatdrawDrawLabel);

        vclassSet (defaultClass,
                   gscatdrawPOSITION_LABEL_RECTS,
                   _gscatdrawPositionLabelRects);

        vclassSet (defaultClass,
                   gscatdrawSET_POINT_SIZE,
                   _gscatdrawSetPointSize);

        vclassSet (defaultClass,
                   gscatdrawCALC_LABEL_SIZE,
                   _gscatdrawCalcLabelSize);
    }
    
    return (defaultClass);
    
} /* gscatdrawGetDefaultClass */


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

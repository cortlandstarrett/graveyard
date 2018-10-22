/* $Id: drawble.c,v 1.5 1995/05/02 21:37:34 abstine Exp $ */
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

/* drawble.c -- Implementation of drawable chart-hunks.
 *
 * Module:
 *	gdrawable
 *
 * Descriptions and docs can be found in gdrawble.h
 *
 * See file chart.c for more comments about this whole project.
 */


#define _gdrawableCLASS_NAME "gdrawable"


#ifndef  vportINCLUDED
#include <vport.h>		/* for v*HEADER */
#endif

#ifndef  vstdlibINCLUDED
#include vstdlibHEADER          /* for abort() */
#endif

#ifndef  vclassINCLUDED
#include vclassHEADER
#endif

#ifndef  vcolorINCLUDED
#include vcolorHEADER
#endif

#ifndef  vdrawINCLUDED
#include vdrawHEADER
#endif

#ifndef  vfontINCLUDED
#include vfontHEADER
#endif

#ifndef  vobjectINCLUDED
#include vobjectHEADER
#endif

#ifndef  vpointINCLUDED
#include vpointHEADER
#endif

#ifndef  vrectINCLUDED
#include vrectHEADER
#endif

#ifndef  gaccessorINCLUDED
#include "gaccess.h"
#endif

#ifndef  gdrawableINCLUDED
#include "gdrawble.h"
#endif




/*
 * ----- Module private globals
 */


/* this is the class that implements the default behavior for this 
 * module.  It's setup in gdrawableGetDefaultClass(), and destroyed
 * automagically by the class manager.
 */
static gdrawableClass *defaultClass = NULL;




/*
 * ----- Drawable method implementation
 */


/* _gdrawableDraw -- draw the drawable inside of the rectangle set to it
 *		     previously.
 *
 *  -> drawable -- the drawable to draw
 */
static void _gdrawableDraw (gdrawable *drawable)
{
    vrect *rect = &drawable->chartRect;

    if ((rect->w > 0) && (rect->h > 0)) {
        vdrawScribedRectShowCenter (vcharScribeLiteral("Spam"), rect);
    }
} /* _gdrawableDraw */




/* _gdrawableDrawXAxis -- draw the X axis for this chart.
 *
 *  -> drawable -- the drawable to draw in
 *
 * This draws a rule line across the top (or bottom), as well as tick
 * marks extending down (or up), depending if the axis is on the 
 * bottom (or top).
 *
 * !!! this is only half-implemnted.  There isn't any label drawing, no way
 * !!! set count intervals (5 short 1 long 5 short 1 long), to do dates
 * !!! or speciy subsets (only draw every 5 ticks) for large data sets.
 */
static void _gdrawableDrawXAxis (gdrawable *drawable)
{
    vpoint      *scan, *soup; /* it is good food */
    vrect        theRealRectBusters;
    vrect       *innerRect = &theRealRectBusters;
    const vrect *biggunRect;
    int	         y, stopY, width, height, xaxispace, yaxispace;
    gaccessor   *accessor;

    biggunRect = gdrawableGetRect (drawable);
    gdrawableCalcUsefulRect (drawable, innerRect);

    soup = gdrawableCalcPointPoints (drawable);

    accessor = gdrawableGetAccessorAt (drawable, 0);

    gdrawableGetNaturalAxisSize (drawable, &height, &width);
    gdrawableGetMarginSpace (drawable, &xaxispace, &yaxispace);
    
    vdrawGSave ();
    
    if (drawable->axisColor != NULL) {
        vdrawSetColor (drawable->axisColor);
    }
    
    vdrawSetLineWidth (1);  /* ??? have an API for this too ??? */

#if (vdebugDEBUG)
        if (drawable->axisFont == NULL) {
            vexGenerate (vexGetModuleClass(),
                         vexMESSAGE, "Need a font to draw axes",
                         vexPROC_NAME, "_gdrawableDrawXAxis", vexNULL);
        }
#endif

    vdrawSetFont (drawable->axisFont);


    /* figger out the size of the tick marks */
    if (gdrawableGetXPos(drawable) == gdrawableBOTTOM_X) {
        y = biggunRect->y + height;
        stopY = y - 5;
    } else {
        y = biggunRect->y + biggunRect->h - height;
        stopY = y + 5;
    }

    /* draw dividing line */
    
    vdrawMoveTo (innerRect->x - yaxispace, y);
    vdrawLineTo (innerRect->x + innerRect->w + yaxispace, y);

    {
        int    startIndex, stopIndex, numIndex, i;
        
        gaccessorGetSubset (accessor, &startIndex, &stopIndex);
        
        if (   (startIndex == gaccessorUNDEFINED)
            || (stopIndex == gaccessorUNDEFINED)) {
            startIndex = 0;
            stopIndex = gaccessorGetIndexCount (accessor);
        }

        numIndex = stopIndex - startIndex;

        scan = soup;

        /* draw tick borks */
        for (i = 0; i < numIndex; i++) {
            vdrawMoveTo (scan->x, y);
            vdrawLineTo (scan->x, stopY);
            scan++;
        }

        vdrawStroke ();

        /* draw strings */
        /* !!! really need some way to indicate only a portion will
         * !!! be drawn
         */

        /* draw labels */

    }
    
    vdrawGRestore ();

    vmemFree (soup);
    
} /* _gdrawableDrawXAxis */




/* _gdrawableDrawYAxis -- draw the Y axis for this chart.
 *
 *  -> drawable -- the drawable to draw in
 *
 * This draws a rule line across the right (or left), depending if the
 * axis is on the left (or right).
 *
 * !!! this is only one-quarter-implemnted.  There isn't any label drawing, 
 * !!! no way set count intervals (5 short 1 long 5 short 1 long), to do dates
 * !!! or speciy subsets (only draw every 5 ticks) for large data sets.
 */
static void _gdrawableDrawYAxis (gdrawable *drawable)
{
    vrect        theRealRectBusters;
    vrect       *innerRect = &theRealRectBusters;
    const vrect *biggunRect;
    int	         x, stopX, width, height, xaxispace, yaxispace;
    gaccessor   *accessor;

    biggunRect = gdrawableGetRect (drawable);
    gdrawableCalcUsefulRect (drawable, innerRect);

    accessor = gdrawableGetAccessorAt (drawable, 0);

    gdrawableGetNaturalAxisSize (drawable, &height, &width);
    gdrawableGetMarginSpace (drawable, &xaxispace, &yaxispace);
    
    vdrawGSave ();
    
    if (drawable->axisColor != NULL) {
        vdrawSetColor (drawable->axisColor);
    }
    
    vdrawSetLineWidth (1);  /* ??? have an API for this too ??? */

    /* figger out the size of the tick marks */
    if (gdrawableGetYPos(drawable) == gdrawableLEFT_Y) {
        x = biggunRect->x + width;
        stopX = x - 5;
    } else {
        x = biggunRect->x + biggunRect->w - width;
        stopX = x + 5;
    }

    /* draw dividing line */
    
    vdrawMoveTo (x, innerRect->y - xaxispace);
    vdrawLineTo (x, innerRect->y + innerRect->h + xaxispace);

    vdrawStroke ();

    vdrawGRestore ();

} /* _gdrawableDrawYAxis */




/* _gdrawableDrawLegend -- draw the chart legend in the designated recangle.
 *
 *  -> drawable -- the drawable to draw the legend for
 *  -> rect	-- the rectangle to draw in. 
 *
 * The size of the rectangle is determined by the thing actually doing the
 * legend.  This thing can ask the drawable what its natural legend size
 * is.
 */
static void _gdrawableDrawLegend (gdrawable *drawable, const vrect *rect)
{
    /* !!! nobody home */
} /* _gdrawableDrawLegend */




/* _gdrawableSetRect -- set the rect for the drawable.  This is the area
 * 			where the drawable will draw the axes and chart
 *			contents.
 *
 *  -> drawable -- the drawable to set the bounds for
 *  -> rect	-- the bounds rect.
 */
static void _gdrawableSetRect (gdrawable *drawable, const vrect *rect)
{
    drawable->chartRect = *rect;
} /* _gdrawableSetRect */




/* _gdrawableCalcUsefulRect -- calculate the area where the chart can use
 *			       to display the data.  This is the drawable's
 *			       rect minus margins, borders, and axis space.
 *
 *  -> drawable -- the drawable to calc useful rects for
 * <-  rect	-- the rectangle with the useful rect
 */
static void _gdrawableCalcUsefulRect (gdrawable *drawable, vrect *rect)
{
    int left, bottom; /* "boo-leans" for axis location */
    *rect = *gdrawableGetRect (drawable);

    bottom = (gdrawableGetXPos(drawable) == gdrawableBOTTOM_X);
    left = (gdrawableGetYPos(drawable) == gdrawableLEFT_Y);

    /* adjust for margins */
    {
        rect->x += gdrawableGetLeftMargin (drawable);
        rect->y += gdrawableGetBottomMargin (drawable);
        rect->w -= (  gdrawableGetLeftMargin(drawable)
                    + gdrawableGetRightMargin(drawable));
        rect->h -= (  gdrawableGetTopMargin(drawable)
                    + gdrawableGetBottomMargin(drawable));
    }

    /* adjust for axis rects */
    {
        int width, height;

        gdrawableGetNaturalAxisSize (drawable, &height, &width);

        if (gdrawableGetDrawX(drawable)) {
            if (bottom) {
                rect->y += height;
            }
            rect->h -= height;
        }

        if (gdrawableGetDrawY(drawable)) {
            if (left) {
                rect->x += width;
            }
            rect->w -= width;
        }
    }

    /* adjust for axis padding */
    {
        int xaxisspace, yaxisspace;

        gdrawableGetMarginSpace (drawable, &xaxisspace, &yaxisspace);
        rect->x += yaxisspace;
        rect->w -= 2 * yaxisspace;
        rect->y += xaxisspace;
        rect->h -= 2 * xaxisspace;
    }
    
} /* _gdrawableCalcUsefulRect */




/* _gdrawableCalcPointPoints -- calculate the locations the points should
 *				be drawn at in the drawable.  No - really!
 *				this can be generalized!  These values are
 *				the same whether they're the inflection points
 *				for a line chart or the tops of a bar chart.
 *				For more sophisticated things, like stacked
 *				bar charts, there probably should be some
 *				customization done by the subclass.
 *
 *  -> drawable -- the drawable to calc the data point points for
 * <-		-- an array large enough to hold one vpoint for each data
 *		   point.  The client *is* responsible for freeing this.
 */
static vpoint *_gdrawableCalcPointPoints (gdrawable *drawable)
{
    vpoint    *pos; /* it's possi-bul, it's possi-bul */
    int        startIndex, stopIndex, numIndex;
    gaccessor *accessor = gdrawableGetAccessorAt (drawable, 0);
    vrect      arect;
    vrect      *rect = &arect;
    double vertMin;

    /* ??? how will clients be able to calc point points for other 
     * ??? accessors?
     */

    /* figure out what elements are going to be plotted */
    gaccessorGetSubset (accessor, &startIndex, &stopIndex);
    
    if (   (startIndex == gaccessorUNDEFINED)
        || (stopIndex == gaccessorUNDEFINED)) {
        startIndex = 0;
        stopIndex = gaccessorGetIndexCount (accessor);
    }
    
    numIndex = stopIndex - startIndex;
    pos = (vpoint*)vmemAlloc (sizeof(vpoint) * numIndex);

    /* get how much space we have to plot them in */
    gdrawableCalcUsefulRect (drawable, rect);

    /* and do the math */

    if (numIndex == 1)
    {
	pos->x = rect->x + (rect->w / 2);
    }
    else
    {
        double vertScale, horzScale;
	double max;
        
	int i;
	vpoint *scan = pos;

            /* first get the vertical fudge-o-factors */
	if (gaccessorGetValueType(accessor) == gaccessorINTEGER)
	{
	    vertMin = *((int*)gaccessorGetRangeMin(accessor));
	    max = *((int*)gaccessorGetRangeMax(accessor));
	}
	else if (gaccessorGetValueType(accessor) == gaccessorDOUBLE)
	{
	    vertMin = *((double*)gaccessorGetRangeMin(accessor));
	    max = *((double*)gaccessorGetRangeMax(accessor));
	}
	else
	{
	    abort(); /* heh heh... breakin' the law, breakin' the law */
	}

	vertScale = (double)rect->h / (max - vertMin);

        /* next get the horizontal fudge-o-factors */
	horzScale = (double)rect->w / (double)(numIndex - 1);

	for (i = 0; i < numIndex; i++)
	{
	    int val = *((int*)gaccessorGetValue (accessor, i + startIndex));
	    
	    scan->x = rect->x + i * horzScale;
	    scan->y = rect->y + (val - vertMin) * vertScale;
	    scan++;
        }
    }
    
    return (pos);

} /* _gdrawableCalcPointPoints */




/* _gdrawableSetXPos -- Set the position of the X axis -- whether it's on
 *			the top or bottom.
 *
 *  -> drawable -- the drawable to set the X axis position for
 *  -> position -- gdrawableTOP_X or gdrawableBOTTOM_X to indicate the
 *		   position to put it at.
 */
static void _gdrawableSetXPos (gdrawable *drawable, int position)
{
#if (vdebugDEBUG)
    if (   (position != gdrawableTOP_X)
        && (position != gdrawableBOTTOM_X)) {
        vexGenerate (vexGetArgClass(),
                     vexMESSAGE,
                     "bad position arg. Please use gdrawableTOP_X"
                     " or gdrawableBOTTOM_X",
                     vexPROC_NAME, "_gdrawableSetXPos",
                     vexArgPOSITION, 2, vexNULL);
    }
#endif

    drawable->flags &= ~_gdrawableX_FLAGS;
    drawable->flags |= position;

} /* _gdrawableSetXPos */




/* _gdrawableSetYPos -- Set the position of the Y axis -- whether it's on
 *			the left or right.
 *
 *  -> drawable -- the drawable to set the Y axis position for
 *  -> position -- gdrawableLEFT_Y or gdrawableRIGHT_Y to indicate the
 *		   position to put it at.
 */
static void _gdrawableSetYPos (gdrawable *drawable, int position)
{
#if (vdebugDEBUG)
    if (   (position != gdrawableLEFT_Y)
        && (position != gdrawableRIGHT_Y)) {
        vexGenerate (vexGetArgClass(),
                     vexMESSAGE,
                     "bad position arg. Please use gdrawableLEFT_Y"
                     " or gdrawableRIGHT_Y",
                     vexPROC_NAME, "_gdrawableSetYPos",
                     vexArgPOSITION, 2, vexNULL);
    }
#endif

    drawable->flags &= ~_gdrawableY_FLAGS;
    drawable->flags |= position;

} /* _gdrawableSetYPos */




/* _gdrawableSetContinuousX -- indicate whether the X axis represents 
 *			       a discrete range (jumps in value, the spaces
 *			       between each jump is uniform) or continuous
 *			       (has a min/max only)
 *
 *  -> drawable -- the drawable to set the continuosity for
 *  -> onOff    -- TRUE if it should be continuous, FALSE for discrete.
 */
static void _gdrawableSetContinuousX (gdrawable *drawable, int onOff)
{
    if (onOff) {
        drawable->flags |= _gdrawableCONTINUOUS_X;
    } else {
        drawable->flags &= ~_gdrawableCONTINUOUS_X;
    }

} /* _gdrawableSetContinuousX */




/* _gdrevebleSetCunteenoouoosY -- indeecete-a vhezeer zee Y exees represents 
 *                                a deescrete-a runge-a (joomps in felooe-a, 
 *			          zee speces betveee iech joomp is uneeffurm)
 *			          oor cunteenoouoos (hes a meen/mex oonly)
 *
 *  -> dreveble-a  -- zee dreveble-a tu set zee cunteenoousity fur
 *  -> oonOffff    -- TROoE iff it shuoold be-a cunteenoouoos, 
 *		      FELSE fur deescrete-a.
 */
static void _gdrawableSetContinuousY (gdrawable *drawable, int onOff)
{
    if (onOff) {
        drawable->flags |= _gdrawableCONTINUOUS_Y;
    } else {
        drawable->flags &= ~_gdrawableCONTINUOUS_Y;
    }

} /* _gdrawableSetContinuousY */




/* _gdrawableSetDrawX -- turns on or off the drawing of the X axis.  If you're
 *			 layering several drawables, each of which share the
 *			 same X axis, turn off the X axis drawing for each of
 *			 them except for one, which will do the drawing.
 *
 *  -> drawable -- the drawable to set the X axis drawing for
 *  -> onOff	-- TRUE if the X axis should be drawn, FALSE otherwise
 */
static void _gdrawableSetDrawX (gdrawable *drawable, int onOff)
{
    if (onOff) {
        drawable->flags |= _gdrawableDRAW_X;
    } else {
        drawable->flags &= ~_gdrawableDRAW_X;
    }
} /* _gdrawableSetDrawX */




/* _gdrevebleSetDrevX -- toorns oon oor ooffff zee dreveeng ooff zee X exees.  
 *			 Iff yuoo're-a leyereeng seferel drevebles, iech ooff
 *			 vheech shere-a zee seme-a X exees, toorn ooffff zee
 *			 X exees dreveeng fur iech ooff zeem ixcept fur 
 *			 oone-a, vheech veell du zee dreveeng.
 *
 *  -> dreveble-a -- zee dreveble-a tu set zee X exees dreveeng fur
 *  -> oonOffff   -- TROoE iff zee X exees shuoold be-a drevn, FELSE 
 *		     oozeerveese-a
 */
static void _gdrawableSetDrawY (gdrawable *drawable, int onOff)
{
    if (onOff) {
        drawable->flags |= _gdrawableDRAW_Y;
    } else {
        drawable->flags &= ~_gdrawableDRAW_Y;
    }
} /* _gdrawableSetDrawY */




/* _gdrawableGetNaturalAxisSize  -- returns the natural size for the X and
 *				    Y axis.  These values are used by drawable
 *				    containers to set the margins of all of
 *				    its drawables so that they can share/not
 *				    step over other folks axes
 *
 *  -> drawable -- the drawable to get the natural axis size for 
 * <-  xheight	-- the height the X axis wants to be
 * <-  ywidth   -- the width the Y axis wants to be
 */
static void _gdrawableGetNaturalAxisSize (gdrawable *drawable,
                                          int *xheight,
                                          int *ywidth)
{
    *xheight = 0;
    *ywidth = 0;
} /* _gdrawableGetNaturalAxisSize */




/* _gdrawableSetDrawableMargins -- set the margins for the drawable.  The
 *				   margins are areas that the drawable is to
 *				   pretend dont exist.  Drawable containers
 *				   manipulate the margins so that axes can
 *				   be shared and not stomped over. 
 *
 *  -> drawable     -- the drawable to set the margins for
 *  -> topMargin    -- the top margin
 *  -> leftMargin   -- the left margin
 *  -> bottomMargin -- existential qualifications of subliminalism
 *  -> rightMargin  -- transient expressionist neo-postmodernism
 *
 * If "gdrawableNO_CHANGE" is passed for any of these, that particular
 * margin is unaffected.
 */
static void _gdrawableSetDrawableMargins (gdrawable *drawable,
                                          int topMargin,    int leftMargin,
                                          int bottomMargin, int rightMargin)
{
    if (topMargin != gdrawableNO_CHANGE) {
        drawable->topMargin = topMargin;
    }

    if (leftMargin != gdrawableNO_CHANGE) {
        drawable->leftMargin = leftMargin;
    }

    if (bottomMargin != gdrawableNO_CHANGE) {
        drawable->bottomMargin = bottomMargin;
    }

    if (rightMargin != gdrawableNO_CHANGE) {
        drawable->rightMargin = rightMargin;
    }
} /* _gdrawableSetDrawableMargins */




/* _gdrawableSetAxisFont -- set the font used to draw the labels on the
 *			    X and Y axis.  Also used to calc the stringbounds
 *			    for axis labels
 *
 *  -> drawable -- the drawable to set the axis font for
 *  -> font	-- font and font! What is font!
 */
static void _gdrawableSetAxisFont (gdrawable *drawable, vfont *font)
{
    drawable->axisFont = font;
} /* _gdrawableSetAxisFont */




/* _gdrawableSetAxisColor -- set the color to be used when drawing the X and
 *			     Y axis.
 *
 *  -> drawable -- the drawable to set the axis color for
 *  -> color	-- the color to use
 */
static void _gdrawableSetAxisColor (gdrawable *drawable, vcolor *color)
{
    drawable->axisColor = color;
} /* _gdrawableSetAxisColor */




/* _gdrawableGetRatio -- return the width/height ratio that this drawable
 *			 maintains.
 *
 *  -> drawable -- the drawable to get the ratio for
 *  -> width    -- the width it wants to be relative to the height
 *  -> height   -- the height it wants to be relative to the width
 *
 * If gdrawableRATIO_DONT_CARE is returned, then the drawable will scale
 * to its rectangle.
 */
static void _gdrawableGetRatio (gdrawable *drawable, int *width, int *height)
{
    *width = gdrawableRATIO_DONT_CARE;
    *height = gdrawableRATIO_DONT_CARE;
} /* _gdrawableGetRatio */




/* _gdrawableSetMarginSpace -- Sets the margin to be used between the border
 *			       the axis and the data points in the chart.
 *
 *  -> drawable   -- the drawable to set the margin space for
 *  -> xaxisSpace -- the space between the X axis and the chart area.  Note
 *		     this is space along the Y axis when doing calculations
 *  -> yaxisSpace -- the space between the Y axis and the chart area.  Note
 *		     this is space along the X axis when doing calculations
 */
static void _gdrawableSetMarginSpace (gdrawable *drawable, 
                                      int xaxisSpace, int yaxisSpace)
{
    drawable->xaxisSpace = xaxisSpace;
    drawable->yaxisSpace = yaxisSpace;
} /* _gdrawableSetMarginSpace */




/* _gdrawableAddAccessor -- add an accessor that this drawable can use to get
 *			    the data to draw with
 *
 *  -> drawable -- the drawable to add the accessor for
 *  -> accessor -- the accessor to add.
 *
 * Generally, accessors added first will be drawn first, hence will be on
 * the "bottom" of the stack
 *
 * Ownership of the accessor does not transfer -- it's the client's 
 * responsibility to destroy at the end of time.
 */
static void _gdrawableAddAccessor (gdrawable *drawable, gaccessor *accessor)
{
    /* this same code exists in chartview.c.  If bugs are found here,
     * make the appropriate change in chartview.c */

    /* should use a smarter memory scheme */

    drawable->accessorCount++;
    drawable->accessors = (gaccessor**)vmemRealloc (drawable->accessors,
                                                    sizeof(gaccessor*)
                                                    * drawable->accessorCount);
    drawable->accessors[drawable->accessorCount-1] = accessor;

} /* _gdrawableAddAccessor */




/* _gdrawableRemoveAccessor -- remove the accessor from the drawwable
 *
 *  -> drawable -- the drawable to remove the accessor from
 *  -> accessor -- the accessor to remove.  An exception will be raised if
 * 		   this accessor isn't currently associated with the 
 *		   drawable.
 */
static void _gdrawableRemoveAccessor (gdrawable *drawable, gaccessor *accessor)
{
    /* this same code exists in chartview.c.  If bugs are found here,
     * make the appropriate change in chartview.c */

    gaccessor **scan, **stop;

    /* find the first accessor */

    scan = drawable->accessors;
    stop = drawable->accessors + drawable->accessorCount;

    drawable->accessorCount--;

    while (scan < stop) {
        if (*scan == accessor) {
            break;
        }
        scan++;
    }

#if (vdebugDEBUG)
    /* not found! */
    if (scan == stop) {
        vexGenerate (vexGetArgClass(),
                     vexMESSAGE,
                     "requested accessor isn't associated with given drawable",
                     vexPROC_NAME, "_gdrawableRemoveAccessor",
                     vexArgPOSITION, 2, vexNULL);
    }
#endif
    
    /* scoot everybody else down */
    while (scan < (stop-1)) {
        *scan = *(scan + 1);
        scan++;
    }
    
} /* _gdrawableRemoveAccessor */




/* _gdrawableGetAccessorAt -- return an accessor at a particular index
 *
 *  -> drawable -- the drawable to get an accessor from
 *  -> at       -- the index to get the accesor from
 *
 * If at is outside of the range of valid accessors, and exception will
 * be barfed.
 */
static gaccessor *_gdrawableGetAccessorAt (gdrawable *drawable, int at)
{
    /* this same code exists in chartview.c.  If bugs are found here,
     * make the appropriate change in chartview.c */

    gaccessor *ret;

#if (vdebugDEBUG)
    if (   (at >= drawable->accessorCount)
        || (at < 0)) {
        vexGenerate (vexGetArgRangeClass(),
                     vexMESSAGE, "'at' argument out of range",
                     vexPROC_NAME, "_gdrawableGetAccessorAt",
                     vexArgPOSITION, 2,
                     vexNULL);
    }
#endif

    ret = drawable->accessors[at];
    return (ret);

} /* _gdrawableGetAccessorAt */




/* _gdrawableGetLegendNaturalSize -- return the natural size that legend
 *				     entries want to be.
 *
 *  -> drawable -- the drawable to get the legend natural size for
 * <-  width    -- how wide they want to be
 * <-  height   -- how tall they want to be.
 *
 * It's expected that the size of the legend will be the size of the title
 * of the chart element, plus any space for indicating color, line dash,
 * cute pictures, whatever. 
*/
static void _gdrawableGetLegendNaturalSize (gdrawable *drawable, 
                                            int *width, int *height)
{
    *width = 0;
    *height = 0;
} /* _gdrawableGetLegendNaturalSize */




/*
 * ----- Object-level duties 
 */


/* _gdrawableLowInit -- shared intialization code between the INIT and 
 *		        LOAD_INIT overrides. 
 *
 *  -> drawable -- the drawable to initialize
 */
static void _gdrawableLowInit (gdrawable *drawable)
{
    vrectSet (0, 0, 0, 0, &drawable->chartRect);
    drawable->flags = (  gdrawableLEFT_Y 
                       | gdrawableBOTTOM_X 
                       | _gdrawableDRAW_X
                       | _gdrawableDRAW_Y);
    drawable->accessors = (gaccessor**) vmemAlloc (sizeof(gaccessor*));
    drawable->accessorCount = 0;
    drawable->topMargin = 0;
    drawable->leftMargin = 0;
    drawable->bottomMargin = 0;
    drawable->rightMargin = 0;
    drawable->xaxisSpace = 0;
    drawable->yaxisSpace = 0;
    drawable->axisColor = NULL;
    drawable->axisFont = NULL;
} /* _gdrawableLowInit */




/* _gdrawableInit -- initialize a drawable object to become a productive
 *		     contributor to society
 *
 *  -> drawable -- the drawable to initialize
 */
static void _gdrawableInit (gdrawable *drawable)
{
    vclassSendSuper (defaultClass, vobjectINIT, (drawable));
    _gdrawableLowInit (drawable);
} /* _gdrawableInit */




/* _gdrawableLoadInit -- initialzie a drawable object based on a resource
 *		         template
 *
 *  -> drawable -- the drawable to initalize
 *  -> resource -- the resource template to use as a guide
 */
static void _gdrawableLoadInit (gdrawable *drawable, vresource resource)
{
    vclassSendSuper (defaultClass, vobjectLOAD_INIT, (drawable, resource));
    _gdrawableLowInit (drawable);
} /* _gdrawableLoadInit */




/* _gdrawableDestroy -- STERILIZE!  STERILIZE!   EXTERMINATE!
 *
 *  -> drawable -- STERILIZE!  EXTERMINATE!
 */
static void _gdrawableDestroy (gdrawable *drawable)
{
    if (drawable->accessors != NULL) {
        vmemFree (drawable->accessors);
    }

    vclassSendSuper (defaultClass, vobjectDESTROY, (drawable));

} /* _gdrawableDestroy */
 



/*
 * ----- Managerial duties
 */


/* gdrawableDump -- dumps human-readable debugging information to a particular
 *		    stream.
 *
 *  -> drawable -- the drawable to dump
 *  -> stream   -- the stream to dump it into
 */
void gdrawableDump (gdrawable *drawable, FILE *stream)
{
#if (vdebugDEBUG)

    if (stream == NULL) {
        stream = vdebugGetInfoStream ();
    }

    fprintf (stream, "drawable: %p (%s)\n", drawable, 
             (gdrawableGetTag(drawable) == NULL) 
             ? "no tag"
             : (char*)gdrawableGetTag(drawable));
    fprintf (stream, "  chartRect: %d %d %d %d\n",
             drawable->chartRect.x,           drawable->chartRect.y,
             drawable->chartRect.w,           drawable->chartRect.h);
    fprintf (stream, "  flags: %x\n", drawable->flags);
    fprintf (stream, "  accessorCount: %d\n", drawable->accessorCount);
    fprintf (stream, "  accessors: %p\n", drawable->accessors);

#endif

} /* gaccessrDump */




/* gdrawableGetDefaultClass -- Returns the class used to create new instances
 *			       of gdrawable objects.
 */
gdrawableClass *gdrawableGetDefaultClass (void)
{
    if (defaultClass == NULL) {

        defaultClass = vclassSpawn (vobjectGetDefaultClass(),
                                    sizeof (gdrawableClass));
        vclassSetNameScribed (defaultClass,
                              vcharScribeLiteral(_gdrawableCLASS_NAME));
        vclassSetObjectSize (defaultClass, sizeof (gdrawable));

        vclassSet (defaultClass,
                   vobjectINIT,
                   _gdrawableInit);
        
        vclassSet (defaultClass,
                   vobjectLOAD_INIT,
                   _gdrawableLoadInit);

        vclassSet (defaultClass,
                   vobjectDESTROY,
                   _gdrawableDestroy);

        vclassSet (defaultClass,
                   gdrawableDRAW,
                   _gdrawableDraw);

        vclassSet (defaultClass,
                   gdrawableDRAW_X_AXIS,
                   _gdrawableDrawXAxis);

        vclassSet (defaultClass,
                   gdrawableDRAW_Y_AXIS,
                   _gdrawableDrawYAxis);

        vclassSet (defaultClass,
                   gdrawableSET_CONTINUOUS_X,
                   _gdrawableSetContinuousX);

        vclassSet (defaultClass,
                   gdrawableSET_CONTINUOUS_Y,
                   _gdrawableSetContinuousY);

        vclassSet (defaultClass,
                   gdrawableDRAW_LEGEND,
                   _gdrawableDrawLegend);

        vclassSet (defaultClass,
                   gdrawableSET_RECT,
                   _gdrawableSetRect);

        vclassSet (defaultClass,
                   gdrawableCALC_USEFUL_RECT,
                   _gdrawableCalcUsefulRect);

        vclassSet (defaultClass,
                   gdrawableCALC_POINT_POINTS,
                   _gdrawableCalcPointPoints);

        vclassSet (defaultClass,
                   gdrawableSET_X_POS,
                   _gdrawableSetXPos);

        vclassSet (defaultClass,
                   gdrawableSET_Y_POS,
                   _gdrawableSetYPos);

        vclassSet (defaultClass,
                   gdrawableSET_DRAW_X,
                   _gdrawableSetDrawX);

        vclassSet (defaultClass,
                   gdrawableSET_DRAW_Y,
                   _gdrawableSetDrawY);
        
        vclassSet (defaultClass,
                   gdrawableSET_DRAWABLE_MARGINS,
                   _gdrawableSetDrawableMargins);

        vclassSet (defaultClass,
                   gdrawableSET_AXIS_FONT,
                   _gdrawableSetAxisFont);

        vclassSet (defaultClass,
                   gdrawableSET_AXIS_COLOR,
                   _gdrawableSetAxisColor);

        vclassSet (defaultClass,
                   gdrawableGET_NATURAL_AXIS_SIZE,
                   _gdrawableGetNaturalAxisSize);

        vclassSet (defaultClass,
                   gdrawableGET_RATIO,
                   _gdrawableGetRatio);

        vclassSet (defaultClass,
                   gdrawableSET_MARGIN_SPACE,
                   _gdrawableSetMarginSpace);

        vclassSet (defaultClass,
                   gdrawableADD_ACCESSOR,
                   _gdrawableAddAccessor);

        vclassSet (defaultClass,
                   gdrawableREMOVE_ACCESSOR,
                   _gdrawableRemoveAccessor);

        vclassSet (defaultClass,
                   gdrawableGET_ACCESSOR_AT,
                   _gdrawableGetAccessorAt);

        vclassSet (defaultClass,
                   gdrawableGET_LEGEND_NATURAL_SIZE,
                   _gdrawableGetLegendNaturalSize);
    }
    
    return (defaultClass);

} /* gdrawableGetDefaultClass */



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

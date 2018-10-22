/* $Id: linedr.c,v 1.3 1994/10/06 20:09:56 markd Exp $ */
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

/* linedr.c -- Implementation of a chart drawable that does line charts.
 *
 * Module:
 *	glinedraw
 *
 * Descriptions and docs can be found in glinedr.h
 *
 * See file chart.c for more comments about this whole project.
 */


#define _glinedrawCLASS_NAME "glinedraw"


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

#ifndef   vrectINCLUDED
#include  vrectHEADER
#endif

#ifndef   gaccessINCLUDED
#include "gaccess.h"
#endif

#ifndef   glinedrINCLUDED
#include "glinedr.h"
#endif

#ifndef   gdrawbleINCLUDED
#include "gdrawble.h"
#endif




/*
 * ----- Module private globals
 */

/* this is the class that implements the default behavior for this 
 * module.  It's setup in glinedrawGetDefaultClass(), and destroyed
 * automagically by the class manager.
 */
static glinedrawClass *defaultClass = NULL;




/*
 * ----- Most Important Functions
 */


/* _glinedrawDraw -- draw the drawable inside of the rectangle set to it
 *		     previously.
 *
 *  -> line -- the line chart to draw
 */
static void _glinedrawDraw (glinedraw *line)
{
    vrect spam;
    vpoint *soup, *scan; /* hey - never underestimate the power of soup */
    int i, numIndex;
    int startIndex, stopIndex;
    gaccessor *accessor = glinedrawGetAccessorAt (line, 0);

    
    gdrawableCalcUsefulRect (glinedrawGetDrawable(line), &spam);
    scan = soup = gdrawableCalcPointPoints (glinedrawGetDrawable(line));
    
    if (glinedrawGetDrawX(line)) {
	glinedrawDrawXAxis (line);
    }
    
    if (glinedrawGetDrawY(line)) {
	glinedrawDrawYAxis(line);
    }
    
    /* figure out what elements are going to be plotted */
    gaccessorGetSubset (accessor, &startIndex, &stopIndex);

    if (   (startIndex == gaccessorUNDEFINED)
	|| (stopIndex == gaccessorUNDEFINED)) {
	startIndex = 0;
	stopIndex = gaccessorGetIndexCount (accessor);
    }
	
    /* don't do any work if there's zero or one points to draw */
    if (stopIndex - startIndex > 1) {

	numIndex = stopIndex - startIndex;
	
	/* set up our drawaing state */
	vdrawGSave ();
	
	if (line->lineColor != NULL) {
	    vdrawSetColor (line->lineColor);
	}
	
	vdrawFSetLineWidth ((double)line->lineWidth);
	
	if (line->flags & _glinedrawHAS_DASH) {
	    vdrawFSetDash (line->dashSize,
			   line->dashPat,
			   line->dashOffset);
	}
	
	/* draw the lines */
	
	for (i = 0; i < numIndex; i++) {
	    if (i == 0) {
		vdrawMoveTo (scan->x, scan->y);
	    } else {
		vdrawLineTo (scan->x, scan->y);
	    }
	    scan++;
	}
	
	vdrawStroke ();
	
	
	/* draw the (optional) thingie on each point */
	if (glinedrawGetPointDrawProc (line)) {
	    scan = soup;
	    for (i = 0; i < numIndex; i++) {
		glinedrawDrawPoint (line, i + startIndex, 0,
				    scan->x, scan->y);
		scan++;
	    }
	}
	
	/* clean up our mess */
	vdrawGRestore ();
    }

    vmemFree (soup);

} /* _glinedrawDraw */




/*
 * ----- linedraw method implementation
 */


/* _glinedrawSetLineColor -- set the color to draw the line with.
 *
 *  -> line  -- the line draw thingie to set the line color for
 *  -> color -- the color to use
 */
static void _glinedrawSetLineColor (glinedraw *line, vcolor *color)
{
    line->lineColor = color;
} /* _glinedrawSetLineColor */




/* _glinedrawSetLineDash -- set the line dash to draw the data line in.
 *			    See vdrawFSetDash for what all of these things
 *			    mean.
 *
 *  -> line   -- the linedraw to set the dash for 
 *  -> size   -- the number of elements in the pat array.  Send a size of zero
 *	         for a solid line. 
 *  -> pat    -- an array of on/off segments for the line
 *  -> offset -- black magic that i don't understand.
 */
static void _glinedrawSetLineDash (glinedraw *line, 
                                   int size, const float *pat, double offset)
{
#if vdebugDEBUG
    if (size < 0) {
        vexGenerate (vexGetArgRangeClass(),
                     vexMESSAGE, "negative size argument.",
                     vexPROC_NAME, "_glinedrawSetLineDash",
                     vexArgPOSITION, 2, vexNULL);
    } else if ((size > 0) && (pat == NULL)) {
        vexGenerate (vexGetArgNullClass(),
                     vexMESSAGE, "NULL pattern buffer",
                     vexPROC_NAME, "_glinedrawSetLineDash",
                     vexArgPOSITION, 3, vexNULL);
    }
#endif
    
    if (line->dashPat != NULL) {
        vmemFree (line->dashPat);
        line->dashPat = NULL;
    }
    
    if (size == 0) {
        /* solid lines */
        line->flags &= ~_glinedrawHAS_DASH;
    } else {
        line->flags |= _glinedrawHAS_DASH;
        line->dashSize = size;
        line->dashPat = vmemAlloc (sizeof(float) * size);
        (void)vmemCopy (pat, line->dashPat, sizeof(float) * size);
        line->dashOffset = offset;
    }
} /* _glinedrawSetLineDash */




/* _glinedrawSetLineWidth -- set the width of the line used to draw the chart
 *
 *  -> line  -- the line chart thing to set the line width for 
 *  -> width -- the width of the line
 *
 * ??? should this take a float instead?
 */
static void _glinedrawSetLineWidth (glinedraw *line, int width)
{
    line->lineWidth = width;
} /* _glinedrawSetLineWidth */




/* _glinedrawSetPointDrawProc -- set the draw proc called for each data point. 
 *				 this allows client to draw cute pictures at
 *				 each point on the graph.
 *
 *  -> line -- the linechart thingie to set the point draw proc for
 *  -> proc -- the linechart draw proc thingie
 */
static void _glinedrawSetPointDrawProc (glinedraw *line, 
                                        glinedrawPointDrawProc proc)
{
    line->pointDrawProc = proc;
} /* _glinedrawSetPointDrawProc */




/* _glinedrawDrawPoint -- draw something at the given point.  By default it
 *			  calls the pointDrawProc
 *
 *  -> line      -- the line thing that is doing the drawing
 *  -> index     -- the index of the data point being drawn
 *  -> vectorPos -- the position in the vector tuple of the actual hunka data
 *  -> x,y       -- where in the chart to center the drawing
 *
 * Index and VectorPos can be used to make decisions on what to draw if 
 * different data points or vector tuple locations have different images.
 */
static void _glinedrawDrawPoint (glinedraw *line, 
                                 int index, int vectorPos, int x, int y)
{
    if (line->pointDrawProc) {
        (line->pointDrawProc) (line, index, vectorPos, x, y);
    }
} /* _glinedrawDrawPoint */




/* _glinedrawSetLineForm -- tell the line draw whether to use point-to-point
 *			    form for drawing the lines or whether to use
 *			    step-form
 *
 *  -> line     -- the linechartthingie to set the lineform for
 *  -> lineform -- glinedrawPOINT_TO_POINT or glinedrawSTEP_FORM
 */
static void _glinedrawSetLineForm (glinedraw *line, int lineForm)
{
#if (vdebugDEBUG)
    if (   (lineForm != glinedrawPOINT_TO_POINT)
        && (lineForm != glinedrawSTEP_FORM)) {
        vexGenerate (vexGetArgClass(),
                     vexMESSAGE,
                     "Bad lineForm give.  Use glinedrawPOINT_TO_POINT or "
                     "glinedrawSTEP_FORM",
                     vexPROC_NAME, "_glinedrawSetLineForm",
                     vexArgPOSITION, 2, vexNULL);
    }
#endif
    line->flags &= ~_glinedrawLINE_FORM;
    line->flags |= lineForm;
    
} /* _glinedrawSetLineForm */




/*
 * ----- drawable method overrides
 */


/* _glinedrawDrawLegend -- draw the chart legend in the designated recangle.
 *
 *  -> line -- the linechartthingie to draw the legend for
 *  -> rect -- the rectangle to draw in. 
 */
static void _glinedrawDrawLegend (glinedraw *line, const vrect *rect)
{
} /* _glinedrawDrawLegend */




/* _glinedrawSetRect -- set the rect for the linecharthing.  This is the area
 * 			where the drawable will draw the axes and chart
 *			contents.
 *
 *  -> line -- the drawable to set the bounds for
 *  -> rect -- the bounds rect.
 */
static void _glinedrawSetRect (glinedraw *line, const vrect *rect)
{
    vclassSendSuper (defaultClass, gdrawableSET_RECT, (line, rect));
} /* _glinedrawSetRect */




/* _glinedrawSetDrawableMargins -- set the margins for the linethign.  The
 *				   margins are areas that the drawable is to
 *				   pretend dont exist.  Drawable containers
 *				   manipulate the margins so that axes can
 *				   be shared and not stomped over. 
 *
 *  -> drawable     -- the drawable to set the margins for
 *  -> topMargin    -- the top margin
 *  -> leftMargin   -- the left margin
 *  -> bottomMargin -- the bottom margin
 *  -> rightMargin  -- 28 guesses on what this might be
 *
 * If "gdrawableNO_CHANGE" is passed for any of these, that particular
 * margin is unaffected.
 */
static void _glinedrawSetDrawableMargins (glinedraw *line,
                                          int topMargin,    int leftMargin,
                                          int bottomMargin, int rightMargin)
{
    /* !!! calc and cache for performance */
    
    vclassSendSuper (defaultClass, gdrawableSET_DRAWABLE_MARGINS,
                     (line, topMargin, leftMargin, bottomMargin, rightMargin));
} /* _glinedrawSetDrawableMargins */




/* _glinedrawGetNaturalAxisSize  -- returns the natural size for the X and
 *				    Y axis.  These values are used by drawable
 *				    containers to set the margins of all of
 *				    its drawables so that they can share/not
 *				    step over other folks axes
 *
 *  -> line    -- the linecharthing to get the natural axis size for 
 * <-  xheight -- the height the X axis wants to be
 * <-  ywidth  -- the width the Y axis wants to be
 *
 * !!! the numbers below were just picked out of the air
 */
static void _glinedrawGetNaturalAxisSize (glinedraw *line,
                                          int *xheight, int *ywidth)
{
    *xheight = 30;
    *ywidth = 30;
} /* _glinedrawGetNaturalAxisSize */




/* _glinedrawAddAccessor -- add an accessor to the linechart.
 *
 *  -> line     -- the line chart thingie
 *  -> accessor -- the accessor to use to draw the graph
 *
 * Each chart can only use one accessor, so generate an exception if the
 * client tries to add more than that.
 */
static void _glinedrawAddAccessor (glinedraw *line, gaccessor *accessor)
{
    if (glinedrawGetAccessorCount(line) > 1)  {
#if (vdebugDEBUG)
        vexGenerate (vexGetArgClass(),
                     vexMESSAGE, 
                     "default linedraw class can only use one accessor.",
                     vexPROC_NAME, "_glinedrawAddAccessor",
                     vexArgPOSITION, 2, vexNULL);
#endif
    } else {
        vclassSendSuper (defaultClass, gdrawableADD_ACCESSOR,
                         (line, accessor));
    }
} /* _glinedrawAddAccessor */




/* _glinedrawGetLegendNaturalSize -- get the size the legend for this linechart
 *				     wants to be
 * 
 *  -> line   -- the linechartthing to get the legend size for
 * <-  width  -- the width it wants to be
 * <-  height -- the height it wants to be
 *
 * The current values are bogus -- they should really be calculated based
 * on font size, line-dash complexity, and the existence of the per-point
 * drawproc.
 */
static void _glinedrawGetLegendNaturalSize (glinedraw *line, 
                                            int *width, int *height)
{
    /* ??? */
    *width = 100;
    *height = 20;
} /* _glinedrawGetLegendNaturalSize */




/*
 * ----- Object-level duties 
 */


/* _glinedrawLowInit -- shared initializaiton code between the INIT and 
 *			LOAD_INIT overrides.
 *
 *  -> line -- the chartlinething to initialize
 */
static void _glinedrawLowInit (glinedraw *line)
{
    line->flags = glinedrawPOINT_TO_POINT;
    line->dashSize = 0;
    line->dashPat = NULL;
    line->dashOffset = 0.0;
    
    line->lineWidth = 0;
    line->lineColor = NULL;
    
    line->pointDrawProc = (glinedrawPointDrawProc)NULL;
    
} /* _glinedrawLowInit */




/* glinedrawInit -- initialize a linecharthingie.
 *
 *  -> line -- the thingie to init.
 */
static void _glinedrawInit (glinedraw *line)
{
    vclassSendSuper (defaultClass, vobjectINIT, (line));
    _glinedrawLowInit (line);
} /* _glinedrawInit */




/* _glinedrawLoadInit -- initialize a linecharthtingie based on a resource 
 *			 template
 *
 *  -> line     -- the linedrawchartthingie to init
 *  -> resource -- the resource template to use
 */
static void _glinedrawLoadInit (glinedraw *line, vresource resource)
{
    vclassSendSuper (defaultClass, vobjectLOAD_INIT, (line, resource));
    _glinedrawLowInit (line);
} /* _glinedrawLoadInit */




/* _glinedrawDestroy -- kill!  kill!  kill!
 *
 *  -> line -- thou shalt not kill!
 */
static void _glinedrawDestroy (glinedraw *line)
{
    if (line->dashPat != NULL) {
        vmemFree (line->dashPat);
    }
    vclassSendSuper (defaultClass, vobjectDESTROY, (line));
} /* _glinedrawDestroy */




/*
 * ----- Managerial duties
 */


/* glinedrawDump -- dumps human-readable debugging information to a particular
 *		    stream.
 *
 *  -> line     -- the linedraw to dump
 *  -> stream   -- the stream to dump it into
 */
void glinedrawDump (glinedraw *line, FILE *stream)
{
    
#if (vdebugDEBUG)
    int i;
    
    if (stream == NULL) {
        stream = vdebugGetInfoStream ();
    }
    
    gdrawableDump (glinedrawGetDrawable(line), stream);
    fprintf (stream, "    flags %x\n", line->flags);
    fprintf (stream, "    dashSize %d\n", line->dashSize);
    fprintf (stream, "    dashPat %p\n", line->dashPat);
    for (i = 0; i < line->dashSize; i++) {
        fprintf (stream, "        %f\n", line->dashPat[i]);
    }
    fprintf (stream, "    dashOffset %f\n", line->dashOffset);
    fprintf (stream, "    lineWidth: %d\n", line->lineWidth);
    fprintf (stream, "    lineColor: %p\n", line->lineColor);
    
#endif
    
} /* glinedrawDump */




/* glinedrawGetDefaultClass -- Returns the class used to create new instances
 *			       of glinedraw objects.
 */
glinedrawClass *glinedrawGetDefaultClass (void)
{
    if (defaultClass == NULL) {
        
        defaultClass = vclassSpawn (gdrawableGetDefaultClass(),
                                    sizeof (glinedrawClass));
        vclassSetNameScribed (defaultClass,
                              vcharScribeLiteral(_glinedrawCLASS_NAME));
        vclassSetObjectSize (defaultClass, sizeof (glinedraw));
        
        vclassSet (defaultClass,
                   vobjectINIT,
                   _glinedrawInit);
        
        vclassSet (defaultClass,
                   vobjectLOAD_INIT,
                   _glinedrawLoadInit);
        
        vclassSet (defaultClass,
                   vobjectDESTROY,
                   _glinedrawDestroy);
        
        
        vclassSet (defaultClass,
                   gdrawableDRAW,
                   _glinedrawDraw);

        vclassSet (defaultClass,
                   gdrawableDRAW_LEGEND,
                   _glinedrawDrawLegend);
        
        vclassSet (defaultClass,
                   gdrawableSET_RECT,
                   _glinedrawSetRect);
        
        vclassSet (defaultClass,
                   gdrawableGET_NATURAL_AXIS_SIZE,
                   _glinedrawGetNaturalAxisSize);
        
        vclassSet (defaultClass,
                   gdrawableSET_DRAWABLE_MARGINS,
                   _glinedrawSetDrawableMargins);
        
        vclassSet (defaultClass,
                   gdrawableADD_ACCESSOR,
                   _glinedrawAddAccessor);
        
        vclassSet (defaultClass,
                   gdrawableGET_LEGEND_NATURAL_SIZE,
                   _glinedrawGetLegendNaturalSize);
        
        
        vclassSet (defaultClass,
                   glinedrawSET_LINE_COLOR,
                   _glinedrawSetLineColor);
        
        vclassSet (defaultClass,
                   glinedrawSET_LINE_DASH,
                   _glinedrawSetLineDash);
        
        vclassSet (defaultClass,
                   glinedrawSET_LINE_WIDTH,
                   _glinedrawSetLineWidth);
        
        vclassSet (defaultClass,
                   glinedrawSET_POINT_DRAW_PROC,
                   _glinedrawSetPointDrawProc);
        
        vclassSet (defaultClass,
                   glinedrawDRAW_POINT,
                   _glinedrawDrawPoint);
        
        vclassSet (defaultClass,
                   glinedrawSET_LINE_FORM,
                   _glinedrawSetLineForm);
    }
    
    return (defaultClass);
    
} /* glinedrawGetDefaultClass */


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

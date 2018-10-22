/* $Id: chart.c,v 1.7 1995/12/15 20:03:21 chad Exp $ */
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

/* Executable Name: chart
 * Source Files:    chart.c, attr.c, colspot.c, list.c
 * Header Files:    xattr.h, xcanvas.h, xcolspot.h, xlist.h
 * Library Source:  access.c, canvas.c, citem.c, cview.c,
 *		    drawble.c, linedraw.c, listacc.c, scatdr.c
 * Library Headers: gaccess.h, gcitem.h, gcview.h, gdrawble.h
 *		    glinedr.h, glistacc.h, gscatdr.h
 * Resource Files:  chart.vr
 *
 * Managers Illustrated:
 *	A whole bunch.  From vdialog to vdraw, vlist to vobject.  It shows
 *	a lot of subclassing and creating new classes.
 *
 * Description Of Sample:
 *	This sample is composed of a sample charting package with a demo
 *	that exercises it.  Charts in the demo include a line chart,
 *	scatter chart, a line chart with 4 lines, and a double-Y chart.
 *
 *	There are two axuilarry dialogs that the user can play with that
 *	affect what subset of the data is being graphed, as well as control
 *	different graph attributes, such as color, line dash, etc.
 *
 *	To run, run "chartdemo".  It adds no new command-line switches
 *	outside of the usual Galaxy ones.  To quit it, close any window
 *	from your window manager.
 *
 *	Spiffy features to try: click on the squares of color to bring up
 *	a color chooser.  When in a scrolling mode, try grabbing-hand
 *	scrolling.
 *
 * Disclaimer:
 *	The chart code is about 1/2 finished, and probably never will be
 *	completed by Visix.  You are free to use it and extend it however
 *	you like.  I beleive that the architecture is very good, its just
 *	that the skeletal parts haven't been fleshed out.
 *
 *	The API to this charting stuff in no way implies that any future
 *	Visix charting packages will use a similar API or architecture.
 *
 * History:
 *	Written for 1.2 release 13-Aug-1993
 */

#include <vgalaxy.h>



#include "gaccess.h"
#include "glistacc.h"

#include "gdrawble.h"
#include "glinedr.h"
#include "gscatdr.h"

#include "gcview.h"
#include "gcitem.h"

#include "xlist.h"
#include "xattr.h"
#include "xcolspot.h"



/*
 * ---- Handy Macro
 */

#define TAG(s)	vnameInternGlobalLiteral((s))




/*
 * ----- Program Global
 */

/* Mapping dictionary between drawables and the chartitem they belong to.
 * Handy for figuring out whom to inval when a drawable's attribute changes.
 */
static vdict *drawToItem = NULL;




/*
 * ----- Utility and support
 */


/* _genericShutdown -- given a dialog, destroy all of the chart-related things
 *	       	       inside of it.  It assumes that there is no sharing
 *		       of drawables amongs chartviews, and no sharing of
 *		       accessors amongst drawables.  (This is the 90's,
 *		       after all.)
 *
 *  -> dialog -- the dialog to shutdown (to clean up the mess for)
 */
static void _genericShutdown (vdialog *dialog)
{
    gchartitem *chartitem;
    gaccessor  *accessor;
    gdrawable  *drawable;
    gchartview *chartview;

    chartitem = (gchartitem*)vdialogFindItem (dialog, TAG("chartitem"));

    chartview = gchartitemGetChartview (chartitem);

    /* cycle over the drawables contained in the chartview */
    while (gchartviewGetDrawableCount(chartview)) {

        drawable = gchartviewGetDrawableAt (chartview, 0);

        /* cycle over the accessors in the drawable */
        while (gdrawableGetAccessorCount(drawable)) {
            accessor = gdrawableGetAccessorAt (drawable, 0);
            gdrawableRemoveAccessor (drawable, accessor);
            gaccessorDestroy (accessor);
        }
        gchartviewRemoveDrawable (chartview, drawable);
        gdrawableDestroy (drawable);
    }

    gchartviewDestroy (chartview);

} /* _genericShutdown */




/*
 * ---- Attribute change notification/handling
 */


/* _invalIntem -- given a drawToItem key, interpret it as a canvas and
 *		  force a redraw
 *
 *  -> key -- a void* that happens to point to a canvas.
 */
static void _invalItem (const void *key)
{
    xcanvas *item;

    item = (xcanvas*) vdictLoad (drawToItem, key);
    xcanvasInval ((xcanvas*)item, 0);
} /* _invalItem */




/* _demolistNotify -- notification function for the demolist.  When the
 *		      range of selected rows change, change the subset that
 *		      the accessors are using.
 *
 *  -> startIndex -- the start index of the selected subset
 *  -> stopIndex  -- the stop index of the selected subset
 */
static void _demolistNotify (int startIndex, int stopIndex)
{
    vdictIterator iterator;

    vdictInitIterator (&iterator, drawToItem);

    while (vdictNextIterator(&iterator)) {
	gdrawable *drawable;
	gaccessor *accessor;

	drawable = (gdrawable*)vdictGetIteratorKey (&iterator);
	accessor = gdrawableGetAccessorAt (drawable, 0);

	/* since accessor subset stuff is non-inclusive on the top end, we
	 * have to bump it up by one to get the results we want */
	gaccessorSetSubset (accessor, startIndex, stopIndex + 1);

	_invalItem (vdictGetIteratorKey (&iterator));
    }

    vdictDestroyIterator (&iterator);

} /* _demolistNotify */




/* _xpointDrawProc -- draw an X centered on (x,y), with each leg of the X
 *		      being 6 pixels long.
 *
 *  -> line      -- the linedraw to draw
 *  -> index     -- the index of the point being drawn
 *  -> vectorPos -- the tuple position of the point being drawn
 *  -> x, y	 -- where the point should be centered at.
 *
 * Note that line isn't used.  This procdure is shared by the scatter
 * point drawing code, which also does an X.
 */
static void _xpointDrawProc (glinedraw *line, int index, int vectorPos,
			     int x, int y)
{
    vdrawGSave ();
    /* linedraw leaves the line dash turned on.  We don't want that here */
    vdrawFSetDash (0, NULL, 0);

    vdrawMoveTo (x-3, y-3);
    vdrawLineTo (x+3, y+3);
    vdrawMoveTo (x+3, y-3);
    vdrawLineTo (x-3, y+3);

    vdrawStroke ();
    vdrawGRestore ();

} /* _xpointDrawProc */




/* _xpointDrawProcScatter -- draw an X for a custom point proc for the
 *		             scatter chart.
 *
 *  -> scat      -- scoo-be-doo-be-doooo-wap-da-beedle-de-be-boe. 
 *  -> index     -- the index of the point being drawn
 *  -> vectorPos -- the tuple position of the point being drawn
 *  -> x, y	 -- where the point should be centered at.
 */
static void _xpointDrawProcScatter (gscatdraw *scat, int index, int vectorPos,
				    int x, int y)
{
    _xpointDrawProc (NULL, index, vectorPos, x, y);
} /* _xpointDrawProcScatter */




/* _opointDrawProc -- draw a circle for a line graph draw proc.
 *
 *  -> line      -- the linedraw to draw
 *  -> index     -- the index of the point being drawn
 *  -> vectorPos -- the tuple position of the point being drawn
 *  -> x, y	 -- where the point should be centered at.
 */
static void _opointDrawProc (glinedraw *line, int index, int vectorPos,
			     int x, int y)
{
    vdrawGSave ();
    /* linedraw leaves the line dash turned on, which looks weird for the
     * point drawing.
     */
    vdrawFSetDash (0, NULL, 0);

    vdrawArcN (x, y, 3, 0, 360);
    vdrawStroke ();

    vdrawGRestore ();
    
} /* _opointDrawProc */




/* _doXPointChange -- attribute notification indicating that the user
 *		      changed their mind on drawing line graph points.
 *
 *  -> data     -- to be interpreted as a line graph
 *  -> attrName -- the xattribute attribute name of what changed
 *  -> value    -- in this case, vname_On or vname_off, indicating the state
 *		   of the toggle.
 *
 * This particualr notification is for linegraphs that have X for their
 * point drawing.
 */
static void _doXPointChange (const void *data, const vname *attrName,
			     const void *value)
{
    glinedrawSetPointDrawProc ((glinedraw*)data,
			       (value == vname_On) 
			       ? _xpointDrawProc 
			       : NULL);
    _invalItem (data);

} /* _doXPointChange */




/* _doOPointChange -- attribute notification indicating that the user
 *		      changed their mind on drawing line graph points.
 *
 *  -> data     -- to be interpreted as a line graph
 *  -> attrName -- the xattribute attribute name of what changed
 *  -> value    -- in this case, vname_On or vname_off, indicating the state
 *		   of the toggle.
 *
 * This particualr notification is for linegraphs that have O for their
 * point drawing.
 */
static void _doOPointChange (const void *data, const vname *attrName,
			     const void *value)
{
    glinedrawSetPointDrawProc ((glinedraw*)data,
			       (value == vname_On) 
			       ? _opointDrawProc 
			       : NULL);
    _invalItem (data);

} /* _doOPointChange */




/* _doXPointChangeScatter -- attribute notification indicating that the user
 *		             changed their mind on drawing scatter graph points.
 *
 *  -> data     -- to be interpreted as a line graph
 *  -> attrName -- the xattribute attribute name of what changed
 *  -> value    -- in this case, vname_On or vname_off, indicating the state
 *		   of the toggle.
 */
static void _doXPointChangeScatter (const void *data, const vname *attrName,
				    const void *value)
{
    gscatdrawSetPointDrawProc ((gscatdraw*)data,
			       (value == vname_On)
			       ? _xpointDrawProcScatter
			       : NULL);
    _invalItem (data);

} /* _doXPointChangeScatter */




/* _doXLineWidthChange -- attribute notification indicating that the user
 *		          changed their mind about the width of the lines in
 *			  the line graphs
 *
 *  -> data     -- to be interpreted as a line graph
 *  -> attrName -- the xattribute attribute name of what changed
 *  -> value    -- in this case, a pointer to an integer representing the new
 *		   line width.
 *
 * This particualr notification is for linegraphs that have X for their
 * point drawing.
 */
static void _doLineWidthChange (const void *data, const vname *attrName, 
				const void *value)
{
    glinedrawSetLineWidth ((glinedraw*)data, *((int*)value));

    _invalItem (data);

} /* _doLineWidthChange */




/* _doDashedLinesStyle1 -- attribute notification indicating that the user
 *		           changed their mind on using dashed lines
 *
 *  -> data     -- to be interpreted as a line graph
 *  -> attrName -- the xattribute attribute name of what changed
 *  -> value    -- in this case, vname_On or vname_off, indicating the state
 *		   of the toggle.
 *
 * This attribute notification was associated with particular linedraws
 * that have 5-on-5-off line dash style.
 */
static void _doDashedLinesStyle1 (const void *data, const vname *attrName,
				  const void *value)
{
    float thing = 5.0; /* 5-on-5-off */

    if (value == vname_On) {
	glinedrawSetLineDash ((glinedraw*)data, 1, &thing, 0.0);

    } else {
	glinedrawSetLineDash ((glinedraw*)data, 0, NULL, 0.0);
    }

    _invalItem (data);

} /* _doDashedLinesStyle1 */




/* _doDashedLinesStyle2 -- attribute notification indicating that the user
 *		           changed their mind on using dashed lines
 *
 *  -> data     -- to be interpreted as a line graph
 *  -> attrName -- the xattribute attribute name of what changed
 *  -> value    -- in this case, vname_On or vname_off, indicating the state
 *		   of the toggle.
 *
 * This attribute notification was associated with particular linedraws
 * that have 20-on-5-off line dash style.
 */
static void _doDashedLinesStyle2 (const void *data, const vname *attrName,
				  const void *value)
{
    float thing[2];

    if (value == vname_On) {
	thing[0] = 20; /* on  */
	thing[1] =  5; /* off */
	glinedrawSetLineDash ((glinedraw*)data, 2, thing, 0.0);

    } else {
	glinedrawSetLineDash ((glinedraw*)data, 0, NULL, 0.0);
    }

    _invalItem (data);

} /* _doDashedLinesStyle2 */




/* _doDashedLinesStyle3 -- attribute notification indicating that the user
 *		           changed their mind on using dashed lines
 *
 *  -> data     -- to be interpreted as a line graph
 *  -> attrName -- the xattribute attribute name of what changed
 *  -> value    -- in this case, vname_On or vname_off, indicating the state
 *		   of the toggle.
 *
 * This attribute notification was associated with particular linedraws
 * that have 10-on-5-off-5-on-5-off line dash style.
 */
static void _doDashedLinesStyle3 (const void *data, const vname *attrName,
				  const void *value)
{
    float thing[4];

    if (value == vname_On) {
	thing[0] = 10; /* on  */
	thing[1] =  5; /* off */
	thing[2] =  5; /* on  */
	thing[3] =  5; /* off */
	glinedrawSetLineDash ((glinedraw*)data, 4, thing, 0.0);

    } else {
	glinedrawSetLineDash ((glinedraw*)data, 0, NULL, 0.0);
    }

    _invalItem (data);

} /* _doDashedLinesStyle3 */




/* _doLineColorChange -- attribute notification indicating that the user
 *		         changed their mind about the color of a line
 *
 *  -> data     -- to be interpreted as a line graph
 *  -> attrName -- the xattribute attribute name of what changed
 *  -> value    -- in this case, a vcolor pointer.
 */
static void _doLineColorChange (const void *data, const vname *attrName, 
				const void *value)
{
    glinedrawSetLineColor ((glinedraw*)data, (vcolor*)value);

    _invalItem (data);

} /* _doLineColorChange */




/* _doScatColorChange -- attribute notification indicating that the user
 *		         changed their mind about the color of the scatter
 *			 chart's label or point color
 *
 *  -> data     -- to be interpreted as a line graph
 *  -> attrName -- the xattribute attribute name of what changed
 *  -> value    -- in this case, a vcolor pointer.
 */
static void _doScatColorChange (const void *data, const vname *attrName,
				const void *value)
{
    if (attrName == xattr_Label_Color) {
	gscatdrawSetLabelColor ((gscatdraw*)data, (vcolor*)value);

    } else if (attrName == xattr_Point_Color) {
	gscatdrawSetPointColor ((gscatdraw*)data, (vcolor*)value);

    }

    _invalItem (data);
} /* _doScatColorChange */




/* _doBigAndScrolling -- attribute notification indicating that the user
 *		         changed their mind about making the chart big
 *			 and scrollable.  This handles both the line charts
 *			 and the scatter chart.
 *
 *  -> data     -- to be interpreted as a line graph
 *  -> attrName -- the xattribute attribute name of what changed
 *  -> value    -- in this case, vname_On or vname_off, indicating the state
 *		   of the toggle.
 */
static void _doBigAndScrolling (const void *data, const vname *attrName,
				const void *value)
{
    gchartitem *chartitem = (gchartitem*)data;

    if (value == vname_On) {
	gchartitemSetHorzBar (chartitem, TRUE);
	gchartitemSetVertBar (chartitem, TRUE);
        gchartitemSetChartSize (chartitem, 1000, 500);
	
    } else if (value == vname_Off) {
	const vrect *rect = vdialogGetItemRect (gchartitemGetItem(chartitem));
	int lineWidth = vdialogDetermineItemLineWidth (gchartitemGetItem
						       (chartitem));
	gchartitemSetHorzBar (chartitem, FALSE);
	gchartitemSetVertBar (chartitem, FALSE);
        gchartitemSetChartSize (chartitem, 
				rect->w - (2 * lineWidth),
				rect->h - (2 * lineWidth));
    }
} /* _doBigAndScrolling */




/* _chartDialogNotify -- notification function for the dialogs.  It resizes
 *			 the chartview inside of the chart item when
 *			 appropriate.
 *
 *  -> dialog -- the dialog that had something done to it
 *  -> event  -- the event that did it.  If it's NULL, resize the items.
 *               (see below)
 *
 * There is a quasi-hack here to get the charts to resize on initial open.
 * This notify doesn't get called on dialog open with the event type
 * that we want.  If the event is NULL, (which can only happen if we the
 * client programemrs pass it), go ahead and resize the chart contained
 * within.
 */
static void _chartDialogNotify (vdialog *dialog, vevent *event)
{
    gchartitem *chartitem;
    chartitem = (gchartitem*) vdialogFindItem (dialog, TAG("chartitem"));

    if (chartitem != NULL) {  /* we really do have something to resize */

	if (!gchartitemHasHorzBar (chartitem)) {
	    /* i.e. since it doesn't have scrollbars, it needs to be resized */

	    if ( (event == NULL) || veventIsSize(event)) {
		const vrect *rect;
		int lineWidth;
		
		{
		    vrect rect;
		    rect = *vwindowGetRect (vdialogGetWindow(dialog));
		    rect.x = rect.y = 0;
		    vdialogArrange (dialog, &rect);
		}
		
		rect = vdialogGetItemRect (gchartitemGetItem(chartitem));
		lineWidth = vdialogDetermineItemLineWidth (gchartitemGetItem
							   (chartitem));
		gchartitemSetChartSize (chartitem, 
					rect->w - (2 * lineWidth),
					rect->h - (2 * lineWidth));
	    }
	}
    }
} /* _chartDialogNotify */




/*
 * ----- Single Line Dialog
 */


/* _setupSingleLineDialog -- Create charts, chartviews, and accessors, as
 *			     well as set up notifies and attribute watching
 *			     appropriate for a single-line chart.
 *
 *  -> dialog -- the dialog to put a single line chart in.
 */
static void _setupSingleLineDialog (vdialog *dialog)
{
    gchartitem *chartitem;

    glistacc   *accessor;
    glinedraw  *linedraw;
    gchartview *chartview;

    chartitem = (gchartitem*)vdialogFindItem (dialog, TAG("chartitem"));

    /* 
     * first create the accessor to the data 
     */
    {
        accessor = glistaccCreate ();
        
        /* tell the accessor where the data is coming from */
        glistaccSetList (accessor, xdemolistGetList());
        
        /* tell the accessor which list column contains the index value */
        glistaccSetIndexIndex (accessor, 0);

        /* our indices are integers */
        glistaccSetIndexType (accessor, gaccessorINTEGER);
        /* our values are integers too */
        glistaccSetValueType (accessor, gaccessorINTEGER);

        /* tell the accessor which column of the list contains the 
         * values.  Treat it as a vector of length 1
         */
        {
            int scratch = 5;
            glistaccSetVectorIndices (accessor, &scratch);
        }
       
        /* get mins and maxs set right */
        gaccessorCalcRanges (glistaccGetAccessor(accessor));
    }

    /*
     * second, create the drawable, and attach the accessor
     */
    {
        linedraw = glinedrawCreate ();

        /* it comes out of the box with axis drawing turned on and the axes
         * in the "normal" places
         */
        glinedrawAddAccessor (linedraw, glistaccGetAccessor(accessor));

        /* add some space between the axis and where the chart starts
         */
        glinedrawSetMarginSpace (linedraw, 5, 5);
    }

    /*
     * thirdly, associate the drawable with the chart view.
     */
    {
        chartview = gchartviewCreate ();

        gchartviewAddDrawable (chartview, glinedrawGetDrawable(linedraw));
    }

    /*
     * lastly, tell the chartitem about the chartview
     */
    {
        gchartitemSetChartview (chartitem, chartview);

        gchartitemSetHorzBar (chartitem, TRUE);
        gchartitemSetVertBar (chartitem, TRUE);

        gchartitemSetChartSize (chartitem, 1000, 500);
    }

    
    /* and finally, register interest in attribute value changes */
    xattributeRegisterInterest (xattr_Line_Width, linedraw,
				_doLineWidthChange);
    xattributeRegisterInterest (xattr_Line_1_Color, linedraw,
				_doLineColorChange);

    xattributeRegisterInterest (xattr_Dashed_Lines, linedraw,
				_doDashedLinesStyle1);

    xattributeRegisterInterest (xattr_Big_and_Scrolling, chartitem,
				_doBigAndScrolling);

    xattributeRegisterInterest (xattr_Point_Images, linedraw,
				_doXPointChange);

    vdialogSetNotify (dialog, _chartDialogNotify);

    vdictStore (drawToItem, linedraw, chartitem);

} /* _setupSingleLineDialog */




/* _shutdownSingleLineDialog -- clean up the mess we created on this
 *				dialog's behalf.
 *
 *  -> dialog -- the dialog to clean up after
 */
static void _shutdownSingleLineDialog (vdialog *dialog)
{
    _genericShutdown (dialog);
} /* _shutdownSingleLineDialog */




/*
 * ----- Multi Line Dialog
 */


/* _setupMultiLineDialog -- Create charts, chartviews, and accessors, as
 *			    well as set up notifies and attribute watching
 *			    appropriate for a 4-line chart.
 *
 *  -> dialog -- the dialog to put a multi line chart in.
 */
static void _setupMultiLineDialog (vdialog *dialog)
{
    gchartitem *chartitem;

    glistacc   *accessor1, *accessor2, *accessor3, *accessor4;
    glinedraw  *linedraw1, *linedraw2, *linedraw3, *linedraw4;
    gchartview *chartview;

    vlist *list = xdemolistGetList ();

    chartitem = (gchartitem*)vdialogFindItem (dialog, TAG("chartitem"));

    /* 
     * first create the accessors to the data 
     */
    {
        accessor1 = glistaccCreate ();
        
        /* tell the accessor where the data is coming from */
        glistaccSetList (accessor1, list);
        
        /* tell the accessor which list column contains the index value */
        glistaccSetIndexIndex (accessor1, 0);

        /* our indices are integers */
        glistaccSetIndexType (accessor1, gaccessorINTEGER);
        /* our values are integers too */
        glistaccSetValueType (accessor1, gaccessorINTEGER);

        /* !!! I hate the API for this */
        /* tell the accessor which column of the list contains the 
         * values.  Treat it as a vector of length 1
         */
        {
            int scratch = 3;
            glistaccSetVectorIndices (accessor1, &scratch);
        }
       
        /* get mins and maxs set right */
        /* !!! this is black magic.  Very bad. Need to come up with best
         * !!! to set this */
        gaccessorCalcRanges (glistaccGetAccessor(accessor1));

        
        /* now for the second accessor */
        accessor2 = glistaccCreate ();
        glistaccSetList (accessor2, list);
        glistaccSetIndexIndex (accessor2, 0);
        glistaccSetIndexType (accessor2, gaccessorINTEGER);
        glistaccSetValueType (accessor2, gaccessorINTEGER);
        {
            int scratch = 4;
            glistaccSetVectorIndices (accessor2, &scratch);
        }
        gaccessorCalcRanges (glistaccGetAccessor (accessor2));

        /* now for the third accessor */
        accessor3 = glistaccCreate ();
        glistaccSetList (accessor3, list);
        glistaccSetIndexIndex (accessor3, 0);
        glistaccSetIndexType (accessor3, gaccessorINTEGER);
        glistaccSetValueType (accessor3, gaccessorINTEGER);
        {
            int scratch = 5;
            glistaccSetVectorIndices (accessor3, &scratch);
        }
        gaccessorCalcRanges (glistaccGetAccessor (accessor3));

        /* now for the fourth accessor */
        accessor4 = glistaccCreate ();
        glistaccSetList (accessor4, list);
        glistaccSetIndexIndex (accessor4, 0);
        glistaccSetIndexType (accessor4, gaccessorINTEGER);
        glistaccSetValueType (accessor4, gaccessorINTEGER);
        {
            int scratch = 6;
            glistaccSetVectorIndices (accessor4, &scratch);
        }
        gaccessorCalcRanges (glistaccGetAccessor (accessor4));
    }

    /*
     * second, create the drawables, and attach the accessors
     */
    {
        linedraw1 = glinedrawCreate ();

        /* it comes out of the box with axis drawing turned on and the axes
         * in the "normal" places
         */
        glinedrawAddAccessor (linedraw1, glistaccGetAccessor(accessor1));

        /* add some space between the axis and where the chart starts
         */
        glinedrawSetMarginSpace (linedraw1, 5, 5);


        /* now for the second one */
        linedraw2 = glinedrawCreate ();
        glinedrawAddAccessor (linedraw2, glistaccGetAccessor(accessor2));
        glinedrawSetDrawX (linedraw2, FALSE);
	glinedrawSetDrawY (linedraw2, FALSE);
        glinedrawSetMarginSpace (linedraw2, 5, 5);

        /* now for the third one */
        linedraw3 = glinedrawCreate ();
        glinedrawAddAccessor (linedraw3, glistaccGetAccessor(accessor3));
        glinedrawSetDrawX (linedraw3, FALSE);
	glinedrawSetDrawY (linedraw3, FALSE);
        glinedrawSetMarginSpace (linedraw3, 5, 5);

        /* now for the fourth one */
        linedraw4 = glinedrawCreate ();
        glinedrawAddAccessor (linedraw4, glistaccGetAccessor(accessor4));
        glinedrawSetDrawX (linedraw4, FALSE);
	glinedrawSetDrawY (linedraw4, FALSE);
        glinedrawSetMarginSpace (linedraw4, 5, 5);
    }

    /*
     * thirdly, associate the drawables with the chart view.
     */
    {
        chartview = gchartviewCreate ();

        gchartviewAddDrawable (chartview, glinedrawGetDrawable(linedraw1));
        gchartviewAddDrawable (chartview, glinedrawGetDrawable(linedraw2));
        gchartviewAddDrawable (chartview, glinedrawGetDrawable(linedraw3));
        gchartviewAddDrawable (chartview, glinedrawGetDrawable(linedraw4));
    }

    /*
     * lastly, tell the chartitem about the chartview
     */
    {
        gchartitemSetChartview (chartitem, chartview);

        gchartitemSetHorzBar (chartitem, TRUE);
        gchartitemSetVertBar (chartitem, TRUE);

        gchartitemSetChartSize (chartitem, 1000, 500);
    }

    /*
     * and finally, register interest in attribute value changes
     */
    xattributeRegisterInterest (xattr_Line_Width, linedraw1,
				_doLineWidthChange);
    xattributeRegisterInterest (xattr_Line_Width, linedraw2,
				_doLineWidthChange);
    xattributeRegisterInterest (xattr_Line_Width, linedraw3,
				_doLineWidthChange);
    xattributeRegisterInterest (xattr_Line_Width, linedraw4,
				_doLineWidthChange);

    xattributeRegisterInterest (xattr_Line_1_Color, linedraw1,
				_doLineColorChange);
    xattributeRegisterInterest (xattr_Line_2_Color, linedraw2,
				_doLineColorChange);
    xattributeRegisterInterest (xattr_Line_3_Color, linedraw3,
				_doLineColorChange);
    xattributeRegisterInterest (xattr_Line_4_Color, linedraw4,
				_doLineColorChange);

    xattributeRegisterInterest (xattr_Big_and_Scrolling, chartitem,
				_doBigAndScrolling);

    xattributeRegisterInterest (xattr_Dashed_Lines, linedraw1,
				_doDashedLinesStyle1);
    xattributeRegisterInterest (xattr_Dashed_Lines, linedraw2,
				_doDashedLinesStyle2);
    xattributeRegisterInterest (xattr_Dashed_Lines, linedraw3,
				_doDashedLinesStyle3);

    xattributeRegisterInterest (xattr_Point_Images, linedraw1,
				_doXPointChange);
    xattributeRegisterInterest (xattr_Point_Images, linedraw2,
				_doOPointChange);
    xattributeRegisterInterest (xattr_Point_Images, linedraw3,
				_doOPointChange);
    xattributeRegisterInterest (xattr_Point_Images, linedraw4,
				_doXPointChange);

    vdialogSetNotify (dialog, _chartDialogNotify);

    vdictStore (drawToItem, linedraw1, chartitem);
    vdictStore (drawToItem, linedraw2, chartitem);
    vdictStore (drawToItem, linedraw3, chartitem);
    vdictStore (drawToItem, linedraw4, chartitem);

} /* _setupMultiLineDialog */




/* _shutdownSingleLineDialog -- clean up the mess we created on this
 *				dialog's behalf.
 *
 *  -> dialog -- the dialog to clean up after
 */
static void _shutdownMultiLineDialog (vdialog *dialog)
{
    _genericShutdown (dialog);
} /* _shutdownMultiLineDialog */



/*
 * ----- Scatter Dialog
 */


/* _setupScatterDialog -- Create charts, chartviews, and accessors, as
 *			  well as set up notifies and attribute watching
 *			  appropriate for a scatter chart.
 *
 *  -> dialog -- the dialog to put a scatter chart in.
 */
static void _setupScatterDialog (vdialog *dialog)
{
    gchartitem *chartitem;

    glistacc *accessor;
    gscatdraw *scatdraw;
    gchartview *chartview;

    vlist *list = xdemolistGetList ();

    chartitem = (gchartitem*)vdialogFindItem (dialog, TAG("chartitem"));

    /* 
     * first create the accessor to the data 
     */
    {
        accessor = glistaccCreate ();
        
        /* tell the accessor where the data is coming from */
        glistaccSetList (accessor, list);
        
        /* tell the accessor which list column contains the index value */
        glistaccSetIndexIndex (accessor, 4);

        /* our indices are integers */
        glistaccSetIndexType (accessor, gaccessorINTEGER);
        /* our values are integers too */
        glistaccSetValueType (accessor, gaccessorINTEGER);
	/* set the name index for the point labels */
	glistaccSetNameIndex (accessor, 2);

        /* tell the accessor which column of the list contains the 
         * values.  Treat it as a vector of length 1
         */
        {
            int scratch = 6;
            glistaccSetVectorIndices (accessor, &scratch);
        }
       
        /* get mins and maxs set right */
        gaccessorCalcRanges (glistaccGetAccessor(accessor));
    }

    /*
     * second, create the drawable, and attach the accessor
     */
    {
        scatdraw = gscatdrawCreate ();

        /* it comes out of the box with axis drawing turned on and the axes
         * in the "normal" places
         */
        gscatdrawAddAccessor (scatdraw, glistaccGetAccessor(accessor));

        /* add some space between the axis and where the chart starts
         */
        gscatdrawSetMarginSpace (scatdraw, 5, 5);

	/* set the font for the labels */
	gscatdrawSetLabelFont (scatdraw, vdialogDetermineItemFont
			       (gchartitemGetItem(chartitem)));

    }

    /*
     * thirdly, associate the drawable with the chart view.
     */
    {
        chartview = gchartviewCreate ();

        gchartviewAddDrawable (chartview, gscatdrawGetDrawable(scatdraw));
    }

    /*
     * lastly, tell the chartitem about the chartview
     */
    {
        gchartitemSetChartview (chartitem, chartview);

        gchartitemSetHorzBar (chartitem, TRUE);
        gchartitemSetVertBar (chartitem, TRUE);

        gchartitemSetChartSize (chartitem, 1000, 500);
    }

    /* 
     * finally, register interest in attribute value changes
     */
    xattributeRegisterInterest (xattr_Point_Color, scatdraw,
			       _doScatColorChange);
    xattributeRegisterInterest (xattr_Label_Color, scatdraw,
			       _doScatColorChange);
    xattributeRegisterInterest (xattr_Custom_Point_Image, scatdraw,
				_doXPointChangeScatter);

    xattributeRegisterInterest (xattr_Big_and_Scrolling_Scatter, chartitem,
				_doBigAndScrolling);

    vdialogSetNotify (dialog, _chartDialogNotify);

    vdictStore (drawToItem, scatdraw, chartitem);

} /* _setupScatterDialog */




/* _shutdownSingleLineDialog -- clean up the mess we created on this
 *				dialog's behalf.
 *
 *  -> dialog -- the dialog to clean up after
 */
static void _shutdownScatterDialog (vdialog *dialog)
{
    _genericShutdown (dialog);
} /* _shutdownScatterDialog */




/*
 * ----- Double-Y Dialog
 */


/* _setupDoubleYDialog -- Create charts, chartviews, and accessors, as
 *			  well as set up notifies and attribute watching
 *			  appropriate for a 4-line double-Y chart.
 *
 *  -> dialog -- the dialog to put a double-Y chart in.
 */
static void _setupDoubleYDialog (vdialog *dialog)
{
    gchartitem *chartitem;

    glistacc   *accessor1, *accessor2;
    glinedraw  *linedraw1, *linedraw2;
    gchartview *chartview;

    vlist *list = xdemolistGetList ();

    chartitem = (gchartitem*)vdialogFindItem (dialog, TAG("chartitem"));

    /* 
     * first create the accessors to the data 
     */
    {
        accessor1 = glistaccCreate ();
        
        /* tell the accessor where the data is coming from */
        glistaccSetList (accessor1, list);
        
        /* tell the accessor which list column contains the index value */
        glistaccSetIndexIndex (accessor1, 0);

        /* our indices are integers */
        glistaccSetIndexType (accessor1, gaccessorINTEGER);
        /* our values are integers too */
        glistaccSetValueType (accessor1, gaccessorINTEGER);

        /* tell the accessor which column of the list contains the 
         * values.  Treat it as a vector of length 1
         */
        {
            int scratch = 5;
            glistaccSetVectorIndices (accessor1, &scratch);
        }
       
        /* get mins and maxs set right */
        /* this is black magic */
        gaccessorCalcRanges (glistaccGetAccessor(accessor1));

        
        /* now for the second accessor */
        accessor2 = glistaccCreate ();
        glistaccSetList (accessor2, list);
        glistaccSetIndexIndex (accessor2, 0);
        glistaccSetIndexType (accessor2, gaccessorINTEGER);
        glistaccSetValueType (accessor2, gaccessorINTEGER);
        {
            int scratch = 4;
            glistaccSetVectorIndices (accessor2, &scratch);
        }
        gaccessorCalcRanges (glistaccGetAccessor (accessor2));

	/* make the second chart look a little nicer */
	{
	    int scratch;
	    scratch = *((int*)glistaccGetRangeMin(accessor2)) / 2;

	    glistaccSetRangeMin (accessor2, &scratch);
	    
	    scratch = *((int*)glistaccGetRangeMax(accessor2)) * 2;
	    glistaccSetRangeMax (accessor2, &scratch);
	}
    }

    /*
     * second, create the drawables, and attach the accessors
     */
    {
        linedraw1 = glinedrawCreate ();

        /* it comes out of the box with axis drawing turned on and the axes
         * in the "normal" places
         */
        glinedrawAddAccessor (linedraw1, glistaccGetAccessor(accessor1));

        /* add some space between the axis and where the chart starts
         */
        glinedrawSetMarginSpace (linedraw1, 5, 5);



        /* now for the second one */
        linedraw2 = glinedrawCreate ();
        glinedrawAddAccessor (linedraw2, glistaccGetAccessor(accessor2));

        /* tell the Y axis which side to draw itself on */
        glinedrawSetYPos (linedraw2, gdrawableRIGHT_Y);

        /* since linedraw1 already is doing the axis drawing, tell linedraw2
         * to not do it.
         */
        glinedrawSetDrawX (linedraw2, FALSE);

        glinedrawSetMarginSpace (linedraw2, 5, 5);
    }

    /*
     * thirdly, associate the drawables with the chart view.
     */
    {
        chartview = gchartviewCreate ();

        gchartviewAddDrawable (chartview, glinedrawGetDrawable(linedraw1));
        gchartviewAddDrawable (chartview, glinedrawGetDrawable(linedraw2));
    }

    /*
     * lastly, tell the chartitem about the chartview
     */
    {
        gchartitemSetChartview (chartitem, chartview);

        gchartitemSetHorzBar (chartitem, TRUE);
        gchartitemSetVertBar (chartitem, TRUE);

        gchartitemSetChartSize (chartitem, 1000, 500);
    }

    /* 
     * finally, register interest in attribute value changes
     */
    xattributeRegisterInterest (xattr_Line_Width, linedraw1,
				_doLineWidthChange);
    xattributeRegisterInterest (xattr_Line_Width, linedraw2,
				_doLineWidthChange);

    xattributeRegisterInterest (xattr_Line_5_Color, linedraw1,
				_doLineColorChange);
    xattributeRegisterInterest (xattr_Line_6_Color, linedraw2,
				_doLineColorChange);
    xattributeRegisterInterest (xattr_Big_and_Scrolling, chartitem,
				_doBigAndScrolling);

    xattributeRegisterInterest (xattr_Dashed_Lines, linedraw1,
				_doDashedLinesStyle1);
    xattributeRegisterInterest (xattr_Dashed_Lines, linedraw2,
				_doDashedLinesStyle3);

    xattributeRegisterInterest (xattr_Point_Images, linedraw1,
				_doXPointChange);
    xattributeRegisterInterest (xattr_Point_Images, linedraw2,
				_doOPointChange);

    vdialogSetNotify (dialog, _chartDialogNotify);

    vdictStore (drawToItem, linedraw1, chartitem);
    vdictStore (drawToItem, linedraw2, chartitem);
    
} /* _setupDoubleYDialog */




/* _shutdownSingleLineDialog -- clean up the mess we created on this
 *				dialog's behalf.
 *
 *  -> dialog -- the dialog to clean up after
 */
static void _shutdownDoubleYDialog (vdialog *dialog)
{
    _genericShutdown (dialog);
} /* _shutdownDoubleYDialog */




/*
 * ----- General stuff 
 */


/* _generalSetup -- start managers and do whatever kind of global setup needs
 *		    to be done.
 */
static void _generalSetup (void)
{
    xcolorspotGetDefaultClass ();
    xcanvasGetDefaultClass ();

    gaccessorGetDefaultClass ();
    glistaccGetDefaultClass ();
    gdrawableGetDefaultClass ();
    glinedrawGetDefaultClass ();
    gscatdrawGetDefaultClass ();
    gchartviewGetDefaultClass ();
    gchartitemGetDefaultClass ();

    xattributeStartup ();

    drawToItem = vdictCreate (vdictHashGeneric);

    xdemolistSetNotify (_demolistNotify);

} /* _generalSetup */




/* _generalShutdown -- clean up after any global memory usage
 */
static void _generalShutdown (void)
{
    vdictDestroy (drawToItem);
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

    vdialog *singleLineDialog;
    vdialog *multiLineDialog;
    vdialog *scatterDialog;
    vdialog *doubleYDialog;

    vdialog *attributeDialog;
    vdialog *listDialog;

    vwindow *rootWindow;
    vwindow *tempWindow;

    vrect    workRect;

    int rootWidth, rootHeight;

    int windowWidth, windowHeight;

    int windowBorderH, windowBorderV;

    int titleBarV;


    /* start up galaxy */
    vstartup (argc, argv);

    /* set up our global needs */
    _generalSetup ();

    /* load the dialogs */
    appres = vapplicationGetResources (vapplicationGetCurrent());

    dialogres = vresourceGet (appres, TAG("SingleLine"));
    singleLineDialog = vdialogLoad (dialogres);

    dialogres = vresourceGet (appres, TAG("MultiLine"));
    multiLineDialog = vdialogLoad (dialogres);

    dialogres = vresourceGet (appres, TAG("Scatter"));
    scatterDialog = vdialogLoad (dialogres);

    dialogres = vresourceGet (appres, TAG("Double-Y"));
    doubleYDialog = vdialogLoad (dialogres);

    /* attach a simple command space to each of them */
    _setupCommands (singleLineDialog);
    _setupCommands (multiLineDialog);
    _setupCommands (scatterDialog);
    _setupCommands (doubleYDialog);

    /* create the charts and add attribute watching */
    _setupSingleLineDialog (singleLineDialog);
    _setupMultiLineDialog (multiLineDialog);
    _setupScatterDialog (scatterDialog);
    _setupDoubleYDialog (doubleYDialog);

    /* get support dialogs */
    attributeDialog = xattributeGetAttributeDialog ();
    listDialog = xdemolistGetListDialog ();

    /* attach a simple command space to each of them */
    _setupCommands (attributeDialog);
    _setupCommands (listDialog);

    /* Modified placement for use on Mac/PC demo machines -skip 06/09/94
     * 
     * The goal is to make this demo "fit" on the smaller screens found
     * on many Macs and PC's.  To do so, we will find the size of the
     * root window (the screen) and re-size the dialogs so that they
     * are large/small enough.  Also, we'll use the root window as a
     * reference for positionning the dialogs.  If all goes well, the
     * resulting layout should be similar no matter what size screen
     * is being used.
     */

    /* place them:
     *                      +--------------------------------------------+ 
     *                      |                                            | 
     *                      |                                            | 
     *                      |                subset-list                 | 
     *                      |                                            | 
     *                      |                                            |
     *                      +--------------------------------------------+ 
     * +--------------------+ +---------------------+ 
     * |                    | |                     | +------------------+
     * |                    | |                     | |                  |
     * |      double-Y      | |       scatter       | |   attributes     |
     * |                    | |                     | |                  |
     * |                    | |                     | |                  |
     * +--------------------+ +---------------------+ |                  |
     * +--------------------+ +---------------------+ |                  |
     * |                    | |                     | |                  |
     * |                    | |                     | |                  |
     * |    single-Line     | |      multi-line     | |                  |
     * |                    | |                     | |                  |
     * |                    | |                     | |                  |
     * +--------------------+ +---------------------+ +------------------+
     */

    /* Try to do dynamic resize */

    /* Get the root window coordinates */
    rootWindow = vwindowGetRoot();
    rootWidth = vwindowGetW(rootWindow);
    rootHeight = vwindowGetH(rootWindow);

    /* Account for the borders/decorations.  We don't really know what the 
       widths and heights for these items are, so leave enough to account
       for most setups.
    */
    windowBorderH = 12; /* faked */
    windowBorderV = 12; /* faked */
    titleBarV = 24; /* faked */

    /* Divide screen by 1/3 vertically and 1/3 horizontally */
    windowWidth = ((rootWidth - windowBorderH * 6) / 3);
    windowHeight = ((rootHeight - (windowBorderV * 6 + titleBarV * 3)) / 3);

    /* Get the window rects and change accordingly */
    tempWindow = vdialogGetWindow(singleLineDialog);
    vrectSet(0, 0, windowWidth, windowHeight, &workRect);
    vwindowSetRect(tempWindow, &workRect);
    vwindowPlace(tempWindow, rootWindow,
		 vrectPLACE_ALIGN | vrectPLACE_LEFT,
		 vrectPLACE_ALIGN | vrectPLACE_BOTTOM);

    tempWindow = vdialogGetWindow(multiLineDialog);
    vrectSet(0, 0, windowWidth, windowHeight, &workRect);
    vwindowSetRect(tempWindow, &workRect);
    vwindowPlace(tempWindow, rootWindow,
		 vrectPLACE_CENTER,
		 vrectPLACE_NEAR | vrectPLACE_BOTTOM);

    tempWindow = vdialogGetWindow(doubleYDialog);
    vrectSet(0, 0, windowWidth, windowHeight, &workRect);
    vwindowSetRect(tempWindow, &workRect);
    vwindowPlace(tempWindow, rootWindow,
		 vrectPLACE_ALIGN | vrectPLACE_LEFT,
		 vrectPLACE_CENTER);

    tempWindow = vdialogGetWindow(scatterDialog);
    vrectSet(0, 0, windowWidth, windowHeight, &workRect);
    vwindowSetRect(tempWindow, &workRect);
    vwindowPlace(tempWindow, rootWindow,
		 vrectPLACE_CENTER,
		 vrectPLACE_CENTER);

    tempWindow = vdialogGetWindow(listDialog);
    vrectSet(0, 0, (windowWidth * 2), windowHeight, &workRect);
    vwindowSetRect(tempWindow, &workRect);
    vwindowPlace(tempWindow, rootWindow,
		 vrectPLACE_ALIGN | vrectPLACE_RIGHT,
		 vrectPLACE_ALIGN | vrectPLACE_TOP);

    tempWindow = vdialogGetWindow(attributeDialog);
    vrectSet(0, 0, windowWidth, (windowHeight * 2), &workRect);
    vwindowSetRect(tempWindow, &workRect);
    vwindowPlace(tempWindow, rootWindow,
		 vrectPLACE_ALIGN | vrectPLACE_RIGHT,
		 vrectPLACE_ALIGN | vrectPLACE_BOTTOM);

    /* propagate default attribute settings */
    xattributeRefreshEverybody ();

    /* open them puppers and force the initial resize */
    vdialogOpen (singleLineDialog);
    _chartDialogNotify (singleLineDialog, NULL);
    vdialogOpen (multiLineDialog);
    _chartDialogNotify (multiLineDialog, NULL);
    vdialogOpen (scatterDialog);
    _chartDialogNotify (scatterDialog, NULL);
    vdialogOpen (doubleYDialog);
    _chartDialogNotify (doubleYDialog, NULL);

    vdialogOpen (attributeDialog);
    vdialogOpen (listDialog);

    /* give control to the event loop */
    veventProcess ();

    /* clean up the mess */
    _shutdownSingleLineDialog (singleLineDialog);
    _shutdownMultiLineDialog (multiLineDialog);
    _shutdownScatterDialog (scatterDialog);
    _shutdownDoubleYDialog (doubleYDialog);

    /* continue cleaning up the mess */
    vdialogDestroy (singleLineDialog);
    vdialogDestroy (multiLineDialog);
    vdialogDestroy (scatterDialog);
    vdialogDestroy (doubleYDialog);

    /* clean up even more mess */
    _generalShutdown ();

    /* time has ended. */
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

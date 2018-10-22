/* $Id: canvas.c,v 1.8 1997/10/23 21:39:43 gregt Exp $ */

/************************************************************

    canvas.c
    C Implementation file for Microdraw

    (c) Copyright Visix Software Inc.
    All rights reserved

************************************************************/

/*----------------------------------------------------------------------------
 * The following Sample Code is provided for your reference purposes in
 * connection with your use of the Galaxy Application Environment (TM) software
 * product which you have licensed from Visix Software, Inc. ("Visix").
 * The Sample code is provided to you without any warranty of any kind
 * whatsoever and you agree to be responsible for the use and/or incorporation
 * of the Sample Code into any software product you develop. You agree to fully
 * and completely indemnify and hold Visix harmless from any and all loss,
 * claim, liability or damages with respect to your use of the Sample Code.
 *
 * Subject to the foregoing, you are permitted to copy, modify, and
 * distribute the Sample Code for any purpose and without fee,
 * provided that (i) a copyright notice in the form of "Copyright
 * 1992, 1993, 1994 Visix Software Inc., 11440 Commerce Park Drive,
 * Reston, VA 22091. All Rights Reserved" appears in all copies, (ii)
 * both the copyright notice and this permission notice appear in
 * supporting documentation and (iii) you are a valid licensee of
 * Galaxy Application Environment.
 ---------------------------------------------------------------------------*/

#include <vport.h>

#ifndef  vmemINCLUDED
#include vmemHEADER
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

#ifndef  veventINCLUDED
#include veventHEADER
#endif

#ifndef  vresourceINCLUDED
#include vresourceHEADER
#endif

#ifndef  vclassINCLUDED
#include vclassHEADER
#endif

#ifndef  vcolorINCLUDED
#include vcolorHEADER
#endif

#ifndef  vtextINCLUDED
#include vtextHEADER
#endif

#ifndef  vdomainINCLUDED
#include vdomainHEADER
#endif

#ifndef  vdrawINCLUDED
#include vdrawHEADER
#endif

#ifndef  vdrawpenINCLUDED
#include vdrawpenHEADER
#endif

#ifndef  vdrawpathINCLUDED
#include vdrawpathHEADER
#endif

#ifndef  vdrawcontextINCLUDED
#include vdrawcontextHEADER
#endif

#ifndef  vdialogINCLUDED
#include vdialogHEADER
#endif

#ifndef  vtextviewINCLUDED
#include vtextviewHEADER
#endif

#ifndef  vpaletteINCLUDED
#include vpaletteHEADER
#endif

#ifndef  vdomainviewINCLUDED
#include vdomainviewHEADER
#endif

#include "micdraw.h"

vdomainviewEventClass		*vmdrawDefaultEventClass;

static vdomainviewClass		*defaultDomainViewClass;
static vdomainClass		*defaultDomainClass;

/*
 * vmdrawCreateDomain
 *
 * Create a domain of our domain subclass
 */
vdomain *vmdrawCreateDomain()
{
    return(vdomainCreateOfClass(defaultDomainClass));
}

/* * * * * * *     Domain View Methods    * * * * * */

/*
 * _vmdrawBackground
 *
 * Draws the background, showing the grid for the document, if the
 * "Show Grid" option is enabled.
 *
 * Also draws the "edge area" of the canvas if it is visible.  the domain
 * is framed by a solid black line, and the "void" area outside the domain
 * is filled with the "edge" color loaded from the resource file.
 */
static void _vmdrawDrawContentBackgroundWith(
    vdomainview		*domainView,
    vdrawcontext	*context
    )
{
    vdrawpen		*pen = vdrawcontextGetPen(context);
    const vrect         *bounds, *viewArea;
    vrect		r;
    register int	x1,x2,y1,y2;
    register int	i, j, sizeX, sizeY;
    int                 xSkew = 0, ySkew = 0;
    vdomainGrid         *grid;
    double		saveWidth;
    int			edgeXBound, edgeYBound; 
    vmdrawDocument	*data;
    vcolor              *color;

    data      = (vmdrawDocument *) vdomainviewGetData(domainView);
    bounds    = vdomainGetBounds(vdomainviewGetDomain(domainView));
    grid      = vdomainGetGrid(vdomainviewGetDomain(domainView));
    saveWidth = vdrawpenGetLineWidth(pen);

    /*
     * Erase to bg color
     */

    color = vdrawpenGetColor(pen);
    vdrawpenSetColor(pen, vdrawpenGetComplementColor(pen));
    vdrawcontextFillRectangles(context, vdomainviewGetViewArea(domainView), 1);
    vdrawpenSetColor(pen, color);

    /*
     * Do we need to draw the grid?
     */

    if ((data->viewSettings & vmdrawVIEW_GRID_LINES) &&
	(grid->xSpacing > 0 && grid->ySpacing > 0)) {

	vdrawpenSetLineWidth(pen, 0);

        x1 = bounds->x - (bounds->x % grid->xSpacing);
        y1 = bounds->y - (bounds->y % grid->ySpacing);
        x2 = bounds->x + bounds->w;
        y2 = bounds->y + bounds->h;

        sizeX        = grid->xSpacing;
        sizeY        = grid->ySpacing;
	
	i 	     = x1;
        ySkew        = ((i / grid->xSpacing) & 1) ? grid->ySkew : 0;

        for (; i < x2; i += sizeX) {

	    j	  = y1;
            xSkew = ((j / grid->ySpacing) & 1) ? grid->xSkew : 0;

            for (; j < y2; j += sizeY) {

		vdrawcontextSetCurrentPoint(context, i + xSkew, j + ySkew);
		vdrawcontextDrawLineToRelative(context, 1, 1);

                xSkew = (xSkew == 0 ? grid->xSkew : 0);
            }   

            ySkew = (ySkew == 0 ? grid->ySkew : 0);
        }   
    }

    /*
     * Now draw the edges of the document
     */

    viewArea = vdomainviewGetViewArea(domainView);
    color    = vdrawpenGetColor(pen);
       
    vdrawpenSetLineWidth(pen, 2);

    /*
     * Now draw the edges of the domain, if they are visible
     */

    edgeXBound = bounds->x + bounds->w;
    edgeYBound = bounds->y + bounds->h;

    if (viewArea->x + viewArea->w > edgeXBound) {
	  
        r    = *viewArea;
        r.w += (r.x - edgeXBound);
        r.x  = edgeXBound;

        vdrawpenSetColor(pen, vmdrawEdgeColor);
	vdrawcontextFillRectangles(context, &r, 1);
        vdrawpenSetColor(pen, color);

        if (viewArea->h > edgeYBound)
            r.h = (edgeYBound - r.y);
	vdrawcontextSetCurrentPoint(context, r.x, r.y);
	vdrawcontextDrawLineTo(context, r.x, r.y + r.h);
    }

    if (viewArea->y + viewArea->h > edgeYBound) {
	
        r     = *viewArea;
        r.h  += (r.y - edgeYBound);
        r.y   = edgeYBound;

        vdrawpenSetColor(pen, vmdrawEdgeColor);
	vdrawcontextFillRectangles(context, &r, 1);
        vdrawpenSetColor(pen, color);

        if (viewArea->w > edgeXBound)
		r.w = (edgeXBound - r.x);
	vdrawcontextSetCurrentPoint(context, r.x, r.y);
	vdrawcontextDrawLineTo(context, r.x + r.w, r.y);
    }

    /*
     * If virtual bounds are on - we need to check the left and bottom
     * sides of the view.  We don't have to otherwise because it wouldn't
     * be possible to scroll that direction	
     */

    if (vdomainGetVirtualBounds(vdomainviewGetDomain(domainView))) {

        if (viewArea->x < bounds->x) {
	  
            r    = *viewArea;
            r.w  = (bounds->x - r.x);

	    vdrawpenSetColor(pen, vmdrawEdgeColor);
	    vdrawcontextFillRectangles(context, &r, 1);
	    vdrawpenSetColor(pen, color);

            if (viewArea->y + viewArea->h > edgeYBound)
                r.h = (edgeYBound - r.y);
	    vdrawcontextSetCurrentPoint(context, r.x + r.w, r.y);
	    vdrawcontextDrawLineTo(context, r.x + r.w, r.y + r.h);
        }

        if (viewArea->y < bounds->y) {
	
            r     = *viewArea;
            r.h   = (bounds->y - r.y);

	    vdrawpenSetColor(pen, vmdrawEdgeColor);
	    vdrawcontextFillRectangles(context, &r, 1);
	    vdrawpenSetColor(pen, color);

            if (viewArea->x + viewArea->w > edgeXBound)
		r.w = (edgeXBound - r.x);
            if (viewArea->x < bounds->x) {
                r.w -= (bounds->x - viewArea->x);
                r.x  = bounds->x;
	    }

	    vdrawcontextSetCurrentPoint(context, r.x, r.y + r.h);
	    vdrawcontextDrawLineTo(context, r.x + r.w, r.y + r.h);
        }
    }

#ifdef vmdrawDEBUG
    
    /*
     * Draw the limit rectangle - in a dashed line     
     */

    {
        float		dottedPath[2] = { 1, 1 };
	vdrawpen	*penClone;

        /* Draw the limit rectangle */

	pen = vdrawcontextGetPen(context);
	penClone = vdrawpenClone(pen);
        vdrawpenSetLineWidth(penClone, 0);
	vdrawpenSetDashPattern(penClone, dottedPath, 2, 0);
	vdrawcontextSetPen(context, penClone);
	vdrawcontextDrawRectangles(context,
			    vdomainLimitRect(vdomainviewGetDomain(domainView)),
				   1);
	vdrawcontextSetPen(context, pen);
	vdrawpenDestroy(penClone);
    }
#endif

    vdrawpenSetLineWidth(pen, saveWidth);
}

/*
 * _vmdrawDragOutline
 *
 * Drag outline drawing routine for document objects
 */ 
static void _vmdrawDragOutlineWith(
    register vdomainview	*domainView,
    register vrect		*rects,
    register int		numRects,
    register vrect		*limitRect,
    vpoint			*pinAmount,
    vdrawcontext		*context
    )
{
    register const vrect *bounds;
    vrect		r;
    vdrawpen		*pen = vdrawcontextGetPen(context);
    double 		saveLineWidth;
    int			saveFunction;
    vbool		pinned = FALSE;
    
    /*
     * Pin objects to stay within the domain bounds if external dragging
     * is off
     */

    if (vdomainviewGetDragMethod(domainView) != vdomainviewEXTERNAL_DRAG) {

    	bounds = vdomainGetBounds(vdomainviewGetDomain(domainView));
    		
    	if (limitRect->x < bounds->x) {
    	    pinAmount->x = bounds->x - limitRect->x;
            pinned = TRUE;
        }
    	else if (limitRect->x + limitRect->w > bounds->x + bounds->w) {
    	    pinAmount->x = (bounds->x + bounds->w) -
    	    			     (limitRect->x + limitRect->w);
            pinned = TRUE;
        }
    	    			     
    	if (limitRect->y < bounds->y) {
    	    pinAmount->y = bounds->y - limitRect->y;
            pinned = TRUE;
        }
    	else if (limitRect->y + limitRect->h > bounds->y + bounds->h) {
    	   pinAmount->y = (bounds->y + bounds->h) -
    	    			     (limitRect->y + limitRect->h);
            pinned = TRUE;
        }
    }

    /*
     * Now draw the outlines.
     */

    saveLineWidth = vdrawpenGetLineWidth(pen);
    saveFunction = vdrawpenGetDrawingFunction(pen);
    vdrawpenSetLineWidth(pen, 0);
    vdrawpenSetDrawingFunction(pen, vdrawFUNC_INVERT);

    while (numRects-- > 0) {
        if (pinned)
	    vrectSet(rects->x + pinAmount->x + vmdrawJOINT_SIZE,
		     rects->y + pinAmount->y + vmdrawJOINT_SIZE,
		     rects->w - (vmdrawJOINT_SIZE << 1),
		     rects->h - (vmdrawJOINT_SIZE << 1), &r);
        else
	    vrectSet(rects->x + vmdrawJOINT_SIZE,
		     rects->y + vmdrawJOINT_SIZE,
		     rects->w - (vmdrawJOINT_SIZE << 1),
		     rects->h - (vmdrawJOINT_SIZE << 1), &r);
	vdrawcontextDrawRectangles(context, &r, 1);
        rects++;
    }

    vdrawpenSetLineWidth(pen, saveLineWidth);
    vdrawpenSetDrawingFunction(pen, saveFunction);
}

/*
 * _vmdrawButtonDownHandler
 *  
 * Handles the vdialogHANDLE_ITEM_BUTTON_DOWN method for the domain view.
 * We need to:
 *   -  Enable editing if we clicked on a text object with the text tool
 *   -  Disable editing othwise.
 *   -  If the current tool is the text tool - create a new text object
 *      and enable editing.
 */
static int _vmdrawButtonDownHandler(
    vdomainview		*domainView,
    vevent		*ev
    )
{
    vmdrawDocument		*data;
    vdomain			*domain;
    vdomainObjectSet		*objectSet;
    vdomainObject		*object, *editObject = NULL;
    vdomainObjectSetIterator	iterator;
    vpoint			pt;
    vrect			r;

    data = (vmdrawDocument *) vdomainviewGetData(domainView);

    /*
     * Disable editing - we won't get here if editing is enabled and the
     * user clicked on the text - the text view gets the button down
     */
     
    vmdrawDisableEditing(data, TRUE);

    if (data->currentTool == vmdrawTEXT_TOOL) {
      
        vdomainSelectAll(vdomainviewGetDomain(domainView), 
			 vdomainviewGetSelection(domainView), FALSE, FALSE);

	pt.x = veventGetPointerX(ev);
	pt.y = veventGetPointerY(ev);

	vdomainviewTranslatePoint(data->domainView, &pt, vdomainviewTO_DOMAIN);

        domain    = vdomainviewGetDomain(data->domainView);
        objectSet = vdomainObjectsAtPoint(domain, &pt, 0, TRUE, 
                                          vdomainALL, NULL);
   
	/*
	 * Iterate over all objects at the clicked position, and see if
	 * any of them are text objects
	 */

        vdomainInitObjectSetIterator(&iterator, objectSet);
        if (vdomainNextObjectSetIterator(&iterator)) {

            object = vdomainGetObjectSetIteratorObject(&iterator);

            if (vdomainGetObjectType(domain, object) == vmdrawTEXT_TOOL)
		editObject = object;

	}

        vdomainDestroyObjectSetIterator(&iterator);
        vdomainDestroyObjectSet(objectSet);

	if (editObject != NULL) {

	    /*
	     * We clicked on a text object - enable editing, and pass
	     * control over to the text view
	     */

       	    vmdrawEnableEditing(data, editObject);

	     vdialogSetItemListDrag
		(vdialogGetItemItemList(vdomainviewGetItem(data->domainView)),
		 vtextviewGetItem(data->editTextView));
	    return(vdialogHandleItemButtonDown
		   (vtextviewGetItem(data->editTextView), ev));
        }

	/*
	 * We didn't click on a text object - create one and enable editing
	 */

        vrectSet(pt.x, pt.y, 120, 20 + (vmdrawJOINT_SIZE * 2), &r);
#if (mdrawUSE_DAS)
	if (vmdrawDocumentIsConsumer(data))
	    object = vmdrawAddObject(data, &r, vmdrawTEXT_TOOL,data->idNext--);
	else
	    object = vmdrawAddObject(data, &r, vmdrawTEXT_TOOL,data->idNext++);
#else
	object = vmdrawAddObject(data, &r, vmdrawTEXT_TOOL);
#endif

	vmdrawEnableEditing(data, object);

        return(FALSE);
    }

    if (data->currentTool == vmdrawARROW_TOOL && data->resizeObject == NULL)
	vdomainviewSetDragSnapToGrid(data->domainView, FALSE);
    else
	vdomainviewSetDragSnapToGrid(data->domainView,
			    (data->flags & vmdrawDOC_SNAP_TO_GRID) != 0);
    /*
     * Do the usual
     */

    return(vclassSendSuper(defaultDomainViewClass,
                           vdialogHANDLE_ITEM_BUTTON_DOWN, (domainView, ev)));
}

/*
 * _vmdrawSetDomainViewRect
 *  
 * Handles the vdialogSET_ITEM_RECT method for the domain view.  We need
 * to reposition the edit text view if we are editing
 */
static void _vmdrawSetDomainViewRect(
    vdomainview		*domainView,
    const vrect		*r
    )
{
    vmdrawDocument *data = (vmdrawDocument *) vdomainviewGetData(domainView);

    vclassSendSuper(defaultDomainViewClass,  
		    vdialogSET_ITEM_RECT, (domainView, r));

    if (data->editingObject != NULL)
	vmdrawPositionEditTextView(data, data->editingObject);
}

/* * * * * * *     Domain View Event Class Methods    * * * * * */

/*
 * _vmdrawDetermineStartingCorner
 *
 * Determine if given two points - return the starting corner for the
 * line they represent.
 */
static int _vmdrawDetermineStartingCorner(vpoint *origPos, vpoint *currentPos)
{
    if (origPos->x < currentPos->x) {

	if (origPos->y < currentPos->y)
	    return(vmdrawCORNER_LOWER_LEFT);
	else
	    return(vmdrawCORNER_UPPER_LEFT);
    }
    else {

	if (origPos->y < currentPos->y)
	    return(vmdrawCORNER_LOWER_RIGHT);
	else
	    return(vmdrawCORNER_UPPER_RIGHT);
    }
}

/*
 * _vmdrawTrackEvent
 *
 * Domain Manager track event handler.  Handles drawing out the currently
 * selected tool and resizing objects.
 */
static vbool _vmdrawTrackEvent(
    register vdomainview		*domainView,
    register vdomainviewTrackEvent	*event
    )
{
    vrect               *dr, baseRect, *r;
    vmdrawDocument      *data;
    vpoint              origPos, currentPos;
    static vpoint       resizePos;
    short               currentTool;
    int                 type, saveFunc;
    vdomain		*domain;
    vdomainObject	*object;
    vmdrawObjectData	*objectData;
    vdrawpath		*path;

    data            = (vmdrawDocument *) vdomainviewGetData(domainView);
    currentPos      = event->currentPosition;
    origPos	    = event->originalPosition;
    domain	    = vdomainviewGetDomain(domainView);
    dr	            = vdomainGetBounds(domain);

    /*
     * If the current tool is the arrow - allow the normal selecting and
     * dragging in the domain view
     */

    if (data->currentTool == vmdrawARROW_TOOL && data->resizeObject == NULL) {
	vdomainviewSetTrackMode(domainView, 
				vdomainviewTRACK_SELECT | vdomainviewTRACK_DRAG);
        return(TRUE);
    }

    switch (event->state) {

    case vdomainviewTRACK_START:

   	/*
	 * Unselect everything before we create an object or resize on object 
	 */

        vdomainSelectAll(vdomainviewGetDomain(domainView), 
			 vdomainviewGetSelection(domainView), FALSE, FALSE);

	/*
	 * If we are resizing on object (data->resizeObject was set in the
	 * button-down domain view event handler) - check which corner it's
	 * in and set the static variable resizePos to the position of the
	 * corner _opposite_ the corner being resized.  We use this as a
	 * basis for determine the start/end corners
	 */

	if (data->resizeObject != NULL) {
            r = vdomainGetObjectBounds(domain, data->resizeObject);
            resizePos.x = r->x;
            resizePos.y = r->y;
        
            if ((data->corner & 1) == 0)
                resizePos.y += r->h;
            if ((data->corner & 2) == 0)
                resizePos.x += r->w;
        }

        break;

    case vdomainviewTRACK_MOVE_UNDRAW:
    case vdomainviewTRACK_UPDATE:
	/*
	 * We don't need to handle undraw and update when resizing - the
	 * domain view is drawn offscreen - and the MOVE_DRAW message 	
	 * change the objects bounds and the object is resized
	 */
	if (data->resizeObject != NULL)
	    break;

    case vdomainviewTRACK_MOVE_DRAW:

        if (data->resizeObject != NULL)
            origPos = resizePos;

        vrectSetPoints(origPos.x, origPos.y, currentPos.x, currentPos.y,
                       &baseRect);
	vrectLimit(&baseRect, dr, &baseRect);

        if (data->resizeObject != NULL) {

            type = vdomainGetObjectType(domain, data->resizeObject);
            
            if (type == vmdrawLINE_OBJECT) {
                
                /* Check for slope change - reset starting corner  */
                
		objectData = (vmdrawObjectData *)	
		    vdomainGetObjectData(domain, data->resizeObject);

		if (data->clickedOnStart)
		    objectData->startCorner = 
			_vmdrawDetermineStartingCorner(&currentPos, &origPos);
		else
		    objectData->startCorner = 
			_vmdrawDetermineStartingCorner(&origPos, &currentPos);
            }

	    /*
	     * Set the object bounds to the new resized rectangle
	     */

            vdomainSetObjectBounds(domain,
				   vdomainObjectToSet(data->resizeObject),
				   &baseRect);
            break;
        }

	/*
	 * We are creating a new object
	 */

	/* 
	 * Erase previous doings or draw new stuff
	 */
	
	vmdrawPushPopPen(TRUE, event->context);
	vmdrawSetPen(&vmdrawCurrentPen, data->scale, event->context);

	saveFunc = 
	    vdrawpenGetDrawingFunction(vdrawcontextGetPen(event->context));
        vdrawpenSetDrawingFunction(vdrawcontextGetPen(event->context),
				   vdrawFUNC_INVERT);

	switch (data->currentTool) {

	case vmdrawLINE_TOOL:
	    vdrawcontextSetCurrentPoint(event->context, origPos.x, origPos.y);
	    vdrawcontextDrawLineTo(event->context, currentPos.x, currentPos.y);
            break;

	case vmdrawRECT_TOOL:
	    vdrawcontextDrawRectangles(event->context, &baseRect, 1);
            break;

	case vmdrawRRECT_TOOL:
	    vdrawcontextDrawRoundRectangles(event->context, &baseRect, 1, 10);
            break;

	case vmdrawOVAL_TOOL:
	    path = vdrawpathCreate();
	    vdrawpathMoveTo(path, baseRect.x, baseRect.y + (baseRect.h >> 1));
	    vdrawpathAppendCurve(path, baseRect.x, baseRect.y + baseRect.h,
				 baseRect.x + baseRect.w,
				 baseRect.y + baseRect.h,
				 baseRect.x + baseRect.w,
				 baseRect.y + (baseRect.h >> 1));
	    vdrawpathAppendCurve(path, baseRect.x + baseRect.w, baseRect.y,
				 baseRect.x, baseRect.y,
				 baseRect.x, baseRect.y + (baseRect.h >> 1));
	    vdrawcontextDrawPath(event->context, path);
	    vdrawpathRelease(path);
            break;
        }

        vdrawpenSetDrawingFunction(vdrawcontextGetPen(event->context),
				   saveFunc);
	vmdrawPushPopPen(FALSE, event->context);

        break;

    case vdomainviewTRACK_END:
	
        if (data->resizeObject != NULL) {

	    /* 
	     * Select the resized object, and notify undo of the resize
	     * operation
	     */

	    vdomainSelectObjects(domain, vdomainviewGetSelection(domainView),
				 vdomainObjectToSet(data->resizeObject));
	    vmdrawInvalObjects(data, vdomainObjectToSet(data->resizeObject));
			    
	    data->resizeObject = NULL;

	    vdomainviewNotifyUndo(domainView, vcharScribeLiteral("Resize"));

            break;
        }

        vrectSetPoints(origPos.x, origPos.y, currentPos.x, currentPos.y,
                       &baseRect);

	vrectLimit(&baseRect, dr, &baseRect);

	/* Don't create objects that have no width or height */

	if (data->currentTool == vmdrawLINE_TOOL) {
            if (baseRect.w == 0 && baseRect.h == 0)
	        break;
        }
	else if (vrectIsEmpty(&baseRect))
            break;
        
        /* Create the object */

        currentTool = data->currentTool;

        switch (currentTool) {
	
        case vmdrawLINE_TOOL:
#if (mdrawUSE_DAS)
	  if (vmdrawDocumentIsConsumer(data))
	    object = vmdrawAddObject(data, &baseRect, vmdrawLINE_TOOL,
				     data->idNext--);
	  else
	    object = vmdrawAddObject(data, &baseRect, vmdrawLINE_TOOL,
				     data->idNext++);
#else
	    object = vmdrawAddObject(data, &baseRect, vmdrawLINE_TOOL);
#endif
	  objectData = (vmdrawObjectData *) 
	    vdomainGetObjectData(domain, object);
	  objectData->startCorner =
	    _vmdrawDetermineStartingCorner(&origPos, &currentPos);
	  
#if (mdrawUSE_DAS)
	  /*
	   * force the update now that the start corner is set
	   * so it goes over the wire.
	   */
	  vmdrawInvalObjects(data, vdomainObjectToSet(object));
#endif
	
	  break;

	case vmdrawRECT_TOOL:
	case vmdrawRRECT_TOOL:
	case vmdrawOVAL_TOOL:
            baseRect.w  += 1;
            baseRect.h  += 1;
#if (mdrawUSE_DAS)
	if (vmdrawDocumentIsConsumer(data))
	    object = vmdrawAddObject(data, &baseRect, currentTool,
				     data->idNext--);
	else
	    object = vmdrawAddObject(data, &baseRect, currentTool,
				     data->idNext++);
#else
            vmdrawAddObject(data, &baseRect, currentTool);
#endif
            break;
	}

	if (data->lockedCell == -1)
            vpaletteSetSelection(data->palette, 
                                 vpaletteFindItem(data->palette, 
				       vnameInternGlobalLiteral("Arrow")));
        break;
    }
    return(TRUE);
}

#define _vmdrawCORNER_SIZE         (vmdrawJOINT_SIZE+vmdrawJOINT_SIZE+1)

/*
 * _vmdrawButtonDownEvent
 *
 * Domain Manager button down event handler.  Handles the text 
 * tool
 */
static vbool _vmdrawButtonDownEvent(
    register vdomainview		*domainView,
    register vdomainviewButtonDownEvent	*event
    )
{
    vrect		        *bounds;
    vpoint		        *hitPt;
    vmdrawDocument 	        *data;
    vdomainObjectSet            *objectSet;
    vdomainObject               *object;
    vdomainObjectSetIterator    iterator;
    vmdrawObjectData		*objectData;
    vdomain                     *domain;
    int                         corner = -1;

    data            = (vmdrawDocument *) vdomainviewGetData(domainView);

    if (data->currentTool == vmdrawARROW_TOOL) {

        /* 
         * Check for button down's in the corner of a selected object.
         * We want to resize the object
         */

        domain    = vdomainviewGetDomain(domainView);
        objectSet = vdomainObjectsAtPoint(domain, &event->position,
                                vdomainviewGetSelection(domainView), TRUE, 
                                vdomainSELECTED, NULL);

        vdomainInitObjectSetIterator(&iterator, objectSet);
        if (vdomainNextObjectSetIterator(&iterator)) {

            object = vdomainGetObjectSetIteratorObject(&iterator);

            bounds = vdomainGetObjectBounds(domain, object);
            hitPt  = &event->position;

	    /*
	     * See what corner the mouse-down was in if any	
	     */

            if ((hitPt->x < bounds->x + _vmdrawCORNER_SIZE) &&
                (hitPt->y < bounds->y + _vmdrawCORNER_SIZE))
                corner = vmdrawCORNER_LOWER_LEFT;
            else if ((hitPt->x > bounds->x + bounds->w - _vmdrawCORNER_SIZE) &&
                     (hitPt->y > bounds->y + bounds->h - _vmdrawCORNER_SIZE))
                corner = vmdrawCORNER_UPPER_RIGHT;
            else if ((hitPt->x > bounds->x + bounds->w - _vmdrawCORNER_SIZE) &&
                     (hitPt->y < bounds->y + _vmdrawCORNER_SIZE))
                corner = vmdrawCORNER_LOWER_RIGHT;
            else if ((hitPt->x < bounds->x + _vmdrawCORNER_SIZE) &&
                     (hitPt->y > bounds->y + bounds->h - _vmdrawCORNER_SIZE))
                corner = vmdrawCORNER_UPPER_LEFT;
            
	    /*
	     * Check to see if the object is a line - can't resize from the
	     * non start/end point corners 
	     */

	    objectData = vdomainGetObjectData(domain, object);

	    if (vdomainGetObjectType(domain, object) == vmdrawLINE_OBJECT) {
		if (corner != objectData->startCorner &&
		    corner != (objectData->startCorner ^ 3))
		    corner = -1;
	    }
	    
            if (corner != -1) {
                data->corner         = corner;
                data->resizeObject   = object;
		data->clickedOnStart = (corner == objectData->startCorner);
                vdomainviewSetTrackMode(domainView, vdomainviewTRACK_NONE);
            }
        }

        vdomainDestroyObjectSetIterator(&iterator);
        vdomainDestroyObjectSet(objectSet);
    }

    return(TRUE);
}

/*
 * _vmdrawButtonUpEvent
 *
 * Domain Manager button up event handler.
 */
static vbool _vmdrawButtonUpEvent(
    register vdomainview		*domainView,
    register vdomainviewButtonUpEvent	*event
    )
{
    vmdrawDocument *data = (vmdrawDocument *) vdomainviewGetData(domainView);

    /*
     * Reset the track mode to norma selecting and dragging	
     */

    if (data->lockedCell == -1)
	vdomainviewSetTrackMode(domainView, 
			    vdomainviewTRACK_SELECT | vdomainviewTRACK_DRAG);
    return(TRUE);
}

/*
 * _vmdrawScrollEvent
 *
 * Domain Manager scroll event handler.  Handles the text tool
 */
static vbool _vmdrawScrollEvent(
    register vdomainview		*domainView,
    register vdomainviewScrollEvent	*event
    )
{
    vmdrawDocument		*data;
    vpoint			pt;
    vrect			r;

    data = (vmdrawDocument *) vdomainviewGetData(domainView);

    if (!vdialogItemIsShown(vtextviewGetItem(data->editTextView)))
        return(TRUE);
    
    pt = *vdomainviewGetScrollOffset(domainView);
    vpointSub(&event->oldScrollPosition, &pt, &pt);

    /* 
     * Move the editing text view if we scroll
     */

    r = *vdialogGetItemRect(vtextviewGetItem(data->editTextView));
    r.x += pt.x;
    r.y += pt.y;
    vdialogSetItemRect(vtextviewGetItem(data->editTextView), &r);
    
    return(TRUE);
}

/* * * * * * * * * Domain Class Methods * * * * * * */

/*
 * _vmdrawLoadInitObject
 *
 * Whenever an object is loaded from a resource, we want to load our
 * own stuff in the objects data structure.
 */
static void _vmdrawLoadInitObject(
    vdomain		*domain,
    vdomainObject 	*object,
    vresource		resource
    )
{
    vmdrawObjectData	*data;
    vresource		res;
    int			dir;

    vclassSendSuper(defaultDomainClass, vdomainLOAD_INIT_OBJECT, 
                    (domain, object, resource));

    /* Load up our own stuff here */

    data = (vmdrawObjectData *)  vdomainGetObjectData(domain, object);

    if (!vresourceTestGetInteger(resource, vname_Direction, &dir))
	dir = vmdrawCORNER_LOWER_LEFT;
    
    data->startCorner = dir;

    /* Load the pen */

    vmdrawLoadPen(vresourceGet(resource, vnameInternGlobalLiteral("Pen")),
		 &data->pen); 

    /* Load the pattern */

    if (vresourceTestGet(resource, vnameInternGlobalLiteral("Pattern"), &res)) {
	vmdrawDestroyPattern(&data->pattern);
        vmdrawLoadPattern(res, &data->pattern); 	
    }

    /* Load the text */

    if (vdomainGetObjectType(domain, object) == vmdrawTEXT_OBJECT) {
        data->text = vtextLoad(vresourceGet
                           (resource, vnameInternGlobalLiteral("ObjText")));
	vtextSetRulerAutoCalc(data->text, vtextGetDefaultRuler(data->text),
			      TRUE);
	vtextCalculate(data->text);
    }
    else
        data->text = NULL;
}

/*
 * _vmdrawStoreObject
 *
 * Whenever an object is stored to a resource, we want to store our
 * own stuff in the objects data structure.
 */
static void _vmdrawStoreObject(
    vdomain		*domain,
    vdomainObject 	*object,
    vresource		resource
    )
{
    vmdrawObjectData	*data;

    vclassSendSuper(defaultDomainClass, vdomainSTORE_OBJECT, 
                    (domain, object, resource));

    /* Store our own stuff here */

    data = (vmdrawObjectData *)  vdomainGetObjectData(domain, object);

    vmdrawStorePen(vresourceCreate(resource,
	      vnameInternGlobalLiteral("Pen"), vresourceDICT), &data->pen);

    vmdrawStorePattern(vresourceCreate(resource,
	      vnameInternGlobalLiteral("Pattern"), vresourceDICT),
		       &data->pattern);

    vresourceSetInteger(resource, vname_Direction, data->startCorner);

    if (data->text != NULL) {
        vtextStore(data->text, vresourceCreate(resource,
              vnameInternGlobalLiteral("ObjText"), vresourceDICT));
    }
}

/* 
 * _vmdrawAddObject
 *
 * Whenever an new object is added to the domain, we want to allocate
 * and set the object data.
 */
static vdomainObject *_vmdrawAddObject(
    vdomain		*domain
    )
{
    vmdrawObjectData	*data;
    vdomainObject	*object;

    object = vclassSendSuper(defaultDomainClass, vdomainADD_OBJECT, (domain));

    data = vmdrawCreateObjectData(domain, object);
    vdomainSetObjectData(domain, vdomainObjectToSet(object), data);
    
    vmdrawRecalcLayering((vmdrawDocument *) vdomainGetData(domain));

    return(object);
}

/*
 * _vmdrawCopyObject
 *
 * All we need to do here is make sure that the 'data' field we set
 * in AddObject does not get written over by the copy
 */
static void _vmdrawCopyObject(
    vdomain		*domain,
    vdomainObject	*object,
    vdomainObject	*target
    )
{	
    vmdrawObjectData	*objectData, *targetData;

    targetData = vdomainGetObjectData(domain, target);
    objectData = vdomainGetObjectData(domain, object);

    vclassSendSuper(defaultDomainClass, vdomainCOPY_OBJECT,
                    (domain, object, target));
    vdomainSetObjectData(domain, vdomainObjectToSet(target), targetData);

    /* Now copy the pen and pattern information */

    vmdrawCopyPen(&objectData->pen, &targetData->pen);
    vmdrawCopyPattern(&objectData->pattern, &targetData->pattern);

    /* Copy the text */

    if (targetData->text != NULL)
	vtextDestroy(targetData->text);
    if (objectData->text != NULL) {
	targetData->text = vtextClone(objectData->text);
	vtextSetData(targetData->text, target);
    }
}

/*
 * _vmdrawCopyInitObject
 */
static void _vmdrawCopyInitObject(
    vdomain		*domain,
    vdomainObject	*object,
    vdomainObject	*target
    )
{	
    vmdrawObjectData	*objectData, *targetData;

    targetData = vmdrawCreateObjectData(domain, target);
    objectData = vdomainGetObjectData(domain, object);

    vclassSendSuper(defaultDomainClass, vdomainCOPY_INIT_OBJECT,
                    (domain, object, target));
    vdomainSetObjectData(domain, vdomainObjectToSet(target), targetData);

    /* Now copy the pen and pattern information */

    vmdrawCopyPen(&objectData->pen, &targetData->pen);
    vmdrawCopyPattern(&objectData->pattern, &targetData->pattern);

    /* Copy the text */

    if (targetData->text != NULL)
	vtextDestroy(targetData->text);
    if (objectData->text != NULL)
	targetData->text = vtextClone(objectData->text);

    targetData->startCorner = objectData->startCorner;
}

/*
 * _vmdrawDestroyObject
 *
 * Free our allocated object data we store a pointer to in the object
 * data field
 */
static void _vmdrawDestroyObject(
    vdomain		*domain,
    vdomainObject	*object
    )
{	
    vmdrawObjectData    *data;

    vclassSendSuper(defaultDomainClass, vdomainDESTROY_OBJECT,
                    (domain, object));
    
    data = vdomainGetObjectData(domain, object);

    vmdrawDestroyPattern(&data->pattern);
    vmdrawDestroyPen(&data->pen);

    if (data->text != NULL)
        vtextDestroy(data->text);

    vmemFree(data);

    vmdrawRecalcLayering((vmdrawDocument *) vdomainGetData(domain));
}

/*
 * _vmdrawRecalcTextObjects
 *
 * We need to recalcuate the text when an text objects bounds changes.
 * This routine scans an object set for text objects, and calls 
 * vtextCalculate for any text objects found.
 */
static void _vmdrawRecalcTextObjects(
    vdomain		*domain, 
    vdomainObjectSet	*objectSet
    )
{
    vdomainObjectSetIterator	iterator;
    vdomainObject		*object;
    vmdrawObjectData		*data;

    vdomainInitObjectSetIterator(&iterator, objectSet);
        
    while (vdomainNextObjectSetIterator(&iterator)) {
            
        object     = vdomainGetObjectSetIteratorObject(&iterator);
        data	   = (vmdrawObjectData *)
			vdomainGetObjectData(domain, object);

    	if (data->text != NULL)
	    vtextCalculate(data->text);
    }
    
    vdomainDestroyObjectSetIterator(&iterator);
}

/*
 * _vmdrawSetObjectBounds
 *
 * Recalc the text for text objects
 */
static void _vmdrawSetObjectBounds(
    vdomain		*domain,
    vdomainObjectSet	*objectSet,
    vrect		*r
    )
{	
    vclassSendSuper(defaultDomainClass, vdomainSET_OBJECT_BOUNDS,
                    (domain, objectSet, r));

    _vmdrawRecalcTextObjects(domain, objectSet);
}

/*
 * _vmdrawResizeObjects
 *
 * Recalc the text for text objects
 */
static void _vmdrawResizeObjects(
    vdomain		*domain,
    vdomainObjectSet	*objectSet,
    int			x,
    int			y
    )
{	
    vclassSendSuper(defaultDomainClass, vdomainRESIZE_OBJECTS,
                    (domain, objectSet, x, y));

    _vmdrawRecalcTextObjects(domain, objectSet);
}

/* * * * * *   STARTUP AND SHUTDOWN * * * * * */

/*
 * vmdrawCanvasStartup
 *
 * Initialize the text classes
 */
void vmdrawCanvasStartup()
{
    /*
     * Setup the domain view class - handles our background and
     * drag outlines drawing procedures
     */

    defaultDomainViewClass = vclassReproduce(vdomainviewGetDefaultClass());
	
    vclassSetNameScribed(defaultDomainViewClass,
                         vcharScribeLiteral("vmdrawDomainView"));

    vclassSet(defaultDomainViewClass,
	      vdomainviewDRAW_CONTENT_BACKGROUND_WITH,
	      _vmdrawDrawContentBackgroundWith);
    vclassSet(defaultDomainViewClass,
	      vdomainviewDRAG_OUTLINE_WITH,	_vmdrawDragOutlineWith);
    vclassSet(defaultDomainViewClass,
              vdialogHANDLE_ITEM_BUTTON_DOWN,   _vmdrawButtonDownHandler);
    vclassSet(defaultDomainViewClass,
	      vdialogSET_ITEM_RECT,		_vmdrawSetDomainViewRect);

    /*
     * Setup the domain class - handles object loading and copying
     */

    defaultDomainClass = vclassReproduce(vdomainGetDefaultClass());
	
    vclassSetNameScribed(defaultDomainClass,
                         vcharScribeLiteral("vmdrawDomain"));

    vclassSet(defaultDomainClass,
	      vdomainLOAD_INIT_OBJECT, 		_vmdrawLoadInitObject);
    vclassSet(defaultDomainClass,
	      vdomainSTORE_OBJECT, 		_vmdrawStoreObject);
    vclassSet(defaultDomainClass,
	      vdomainADD_OBJECT, 		_vmdrawAddObject);
    vclassSet(defaultDomainClass,
	      vdomainCOPY_OBJECT,		_vmdrawCopyObject);
    vclassSet(defaultDomainClass,
	      vdomainCOPY_INIT_OBJECT,		_vmdrawCopyInitObject);
    vclassSet(defaultDomainClass,
	      vdomainDESTROY_OBJECT,		_vmdrawDestroyObject);
    vclassSet(defaultDomainClass,
	      vdomainSET_OBJECT_BOUNDS,		_vmdrawSetObjectBounds);
    vclassSet(defaultDomainClass,
	      vdomainRESIZE_OBJECTS,		_vmdrawResizeObjects);

    /*
     * Setup the domain view event class - we want to handle track and
     * move events
     */

    vmdrawDefaultEventClass = vclassReproduce(vdomainviewGetDefaultEventClass());
	
    vclassSetNameScribed(vmdrawDefaultEventClass,
                         vcharScribeLiteral("vmdrawEvent"));

    vclassSet(vmdrawDefaultEventClass,
	      vdomainviewTRACK_EVENT, 		_vmdrawTrackEvent);
    vclassSet(vmdrawDefaultEventClass, 
	      vdomainviewBUTTON_DOWN_EVENT,	_vmdrawButtonDownEvent);
    vclassSet(vmdrawDefaultEventClass,
	      vdomainviewBUTTON_UP_EVENT,	_vmdrawButtonUpEvent);
    vclassSet(vmdrawDefaultEventClass,
	      vdomainviewSCROLL_EVENT,		_vmdrawScrollEvent);
}


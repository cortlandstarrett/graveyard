/* $Id: object.c,v 1.39 1997/11/13 14:51:22 gregt Exp $ */

/************************************************************

    object.c
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

#ifndef  vstrINCLUDED
#include vstrHEADER
#endif

#ifndef  vcolorINCLUDED
#include vcolorHEADER
#endif

#ifndef  vfontINCLUDED
#include vfontHEADER
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

#ifndef  vdomainviewINCLUDED
#include vdomainviewHEADER
#endif

#include "micdraw.h"

static void _vmdrawDrawLayerInfo(vmdrawDocument *, vdomainObject *,
				 vdrawcontext *context);

/*
 * vmdrawCreateObjectData
 * 
 * Allocate and initialize the object data
 */
vmdrawObjectData *vmdrawCreateObjectData(
    vdomain		*domain,
    vdomainObject	*object
    )
{
    vmdrawObjectData	*data;

    data = (vmdrawObjectData *) vmemAlloc((long) sizeof(vmdrawObjectData));
    data->text      	= NULL;
    data->pattern.image = vmdrawCreatePatternImage();
    data->layerNumber	= 0;
#if (mdrawUSE_DAS)
    data->id		= 0;
#endif

    vmdrawCopyPen(&vmdrawCurrentPen, &data->pen);
    vmdrawCopyPattern(&vmdrawCurrentPattern, &data->pattern);

    return(data);
}

/*
 * vmdrawAddObject
 *
 * Add an object to the draw document
 */
vdomainObject *vmdrawAddObject(
    vmdrawDocument      *data,
    vrect		*baseRect,
    int		         type
#if  (mdrawUSE_DAS)
    , unsigned int	 id
#endif
    )
{
    vdomainObject       *object;
    vdomainObjectSet    *objectSet;
    vdomain             *domain;
    vrect		objectRect;
    vmdrawObjectData	*objectData;

    domain = vdomainviewGetDomain(data->domainView);

    /*
     * Account for extra pixel that highlighting the joint to indicate
     * that the object is selected will use.  The object data holds
     * the actual rectangle of the object, and the domain object
     * bounds holds the rectangle including the extra space for
     * joints.
     */
	
    vrectInset(baseRect, -vmdrawJOINT_SIZE, -vmdrawJOINT_SIZE, &objectRect);

    object     = vdomainAddObject(domain);
    objectSet  = vdomainObjectToSet(object); 
    objectData = vdomainGetObjectData(domain, object);

    vdomainSetObjectBounds(domain, objectSet, &objectRect);
    vdomainSetObjectType(domain, objectSet, type);
    vdomainSetObjectOpaque(domain, objectSet, type >= vmdrawRECT_TOOL &&
		 type <= vmdrawOVAL_TOOL && !objectData->pattern.transparent);
    vdomainSelectObjects(domain, vdomainviewGetSelection(data->domainView),
                         objectSet);

#if  (mdrawUSE_DAS)
    objectData->id = id;
#endif
    vdomainShowObjects(domain, objectSet);

    if (type == vmdrawTEXT_TOOL) {
	vmdrawCreateTextObject(objectData);
	vtextSetData(objectData->text, object);
    }

    vmdrawRecalcLayering(data);

    return(object);
}

/*
 * vmdrawDrawObject
 * 
 * Draw procudure for the domain manager user item for a document
 */
void vmdrawDrawObjectWith(
    vdomainview		*domainView,
    vdomainObject	*object,
    vdrawcontext	*context
    )
{
    vrect		r;
    vmdrawDocument	*data;
    vmdrawObjectData	*objectData;
    vdrawcontext	*ctx;
    vdrawpath		*path;
    vdrawpen		*pen;
    vtextSelection	*selection;
    double		saveLineWidth;

    /*
     * Account for the selection joints 
     */

    vrectInset(vdomainGetObjectBounds(vdomainviewGetDomain(domainView),
				      object),
	       vmdrawJOINT_SIZE, vmdrawJOINT_SIZE, &r);

    data 	= (vmdrawDocument *) vdomainviewGetData(domainView);
    objectData  = (vmdrawObjectData *) vdomainGetObjectData
                        (vdomainviewGetDomain(domainView), object);

    /*
     * Save the current pen state
     */

    vmdrawPushPopPen(TRUE, context);

    /*
     * Draw the pattern for the object
     */

    if (!objectData->pattern.transparent) {

	switch (object->type) {

        case vmdrawRECT_OBJECT:
	case vmdrawTEXT_OBJECT:
	    vmdrawPatternFillRect(&objectData->pattern, &r, context);
	    break;

        case vmdrawOVAL_OBJECT:
        case vmdrawRRECT_OBJECT:
	    ctx = vdrawcontextClone(context);

	    path = vdrawpathCreate();
	    if (object->type == vmdrawRRECT_OBJECT)
		vdrawpathSetRoundRectangles(path, &r, 1, 10);
	    else
		vdrawpathSetEllipses(path, &r, 1);
	    vdrawcontextClipPath(ctx, path);
	    vdrawpathRelease(path);

	    vmdrawPatternFillRect(&objectData->pattern, &r, ctx);
	    vdrawcontextDestroy(ctx);
	    break;
	}
    }

    /*
     * Use the objects pen
     */

    vmdrawSetPen(&objectData->pen, data->scale, context);

    switch (object->type) {

    case vmdrawLINE_OBJECT:
	switch (objectData->startCorner) {
	
        case vmdrawCORNER_LOWER_LEFT:
	    vmdrawDrawLine(r.x, r.y, r.x + r.w, r.y + r.h,
			   objectData->pen.arrows, context);
	    break;

        case vmdrawCORNER_UPPER_LEFT:
	    vmdrawDrawLine(r.x, r.y + r.h, r.x + r.w, r.y,
			   objectData->pen.arrows, context);
	    break;

        case vmdrawCORNER_LOWER_RIGHT:
	    vmdrawDrawLine(r.x + r.w, r.y, r.x, r.y + r.h,
			   objectData->pen.arrows, context);
	    break;

        case vmdrawCORNER_UPPER_RIGHT:
	    vmdrawDrawLine(r.x + r.w, r.y + r.h, r.x, r.y,
			   objectData->pen.arrows, context);
	    break;
        }

	break;

    case vmdrawRECT_OBJECT:
	vdrawcontextDrawRectangles(context, &r, 1);
        break;
        
    case vmdrawRRECT_OBJECT:
	vdrawcontextDrawRoundRectangles(context, &r, 1, 10);
        break;

    case vmdrawOVAL_OBJECT:
	vdrawcontextDrawEllipses(context, &r, 1);
	break;

    case vmdrawTEXT_OBJECT:
   	
	/*
	 * Reset the pen - text objects don't use their pen
	 */

	vmdrawPushPopPen(FALSE, context);
	
	pen = vdrawcontextGetPen(context);
	saveLineWidth = vdrawpenGetLineWidth(pen);
	vdrawpenSetLineWidth(pen, 1);

	/*
	 * Draw a box around the text object if we're editing it - and then
	 * return.  The editing text view handles drawing the text
	 */

	if (object == data->editingObject) {
	    vdrawcontextDrawRectangles(context, &r, 1);
	    vdrawpenSetLineWidth(pen, saveLineWidth);
	    return;
 	}

	/*
	 * If we are resizing an text object - draw a box around the text
	 */

	if (object == data->resizeObject)
	    vdrawcontextDrawRectangles(context, &r, 1);
	
	vdrawpenSetLineWidth(pen, saveLineWidth);

	vrectInset(&r, vmdrawJOINT_SIZE, vmdrawJOINT_SIZE, &r);

	/*
	 * Move our floating text view to the objects location, set the
	 * floating text view to use the objects text, and force the
	 * item to draw itself.
	 */

	vtextviewSetTextData(data->floatTextView, objectData->text);
	vtextviewSetSelection(data->floatTextView, 
			selection = vtextCreateSelection(objectData->text));
	vtextviewSetData(data->floatTextView, objectData);
	vdialogSetItemRect(vtextviewGetItem(data->floatTextView), &r);
	ctx = vdrawcontextClone(context);
	vdialogSetItemPenAttributes(vtextviewGetItem(data->floatTextView),
				    vdrawcontextGetPen(ctx));
	vdialogDrawItemWith(vtextviewGetItem(data->floatTextView), ctx);
	vdrawcontextDestroy(ctx);
	vtextviewSetTextData(data->floatTextView, NULL);
	vtextviewSetSelection(data->floatTextView, NULL);
	vtextDestroySelection(objectData->text, selection);
	break;
    }

    if (data->viewSettings & vmdrawSHOW_LAYERING)
	_vmdrawDrawLayerInfo(data, object, context);

    if (object->type != vmdrawTEXT_OBJECT)
	vmdrawPushPopPen(FALSE, context);
}

/*
 * vmdrawSelectObjectJoints
 *
 * Select all or one of the joints on a object
 */
void vmdrawSelectObjectJointsWith(
    vdomainview		*domainView,
    vdomainObject	*object,
    vdrawcontext	*context
    )
{
    vdrawpen		*pen = vdrawcontextGetPen(context);
    int			x, y, jointSize, type, saveFunc;
    register short	i=0;
    vpoint		joint;
    vrect		jointRect;
    vrect		r;
    vmdrawObjectData	*objectData;

    objectData  = (vmdrawObjectData *) vdomainGetObjectData
                        (vdomainviewGetDomain(domainView), object);
    type	= vdomainGetObjectType(vdomainviewGetDomain(domainView), 
				       object);

    vrectInset(vdomainGetObjectBounds(vdomainviewGetDomain(domainView),
				      object),
	       vmdrawJOINT_SIZE, vmdrawJOINT_SIZE, &r);

    joint.x   = r.x;
    joint.y   = r.y;
    jointSize = (vmdrawJOINT_SIZE << 1) + 1;

    /* Scan all four corners */

    for (i=0; i<4; i++) {
        
        x = joint.x - vmdrawJOINT_SIZE;
        y = joint.y - vmdrawJOINT_SIZE;
        
	/* 
	 * Only draw the joints for line objects that are at the starting
	 * corner or the corner opposite the starting corner
	 */

	if (type != vmdrawLINE_OBJECT    ||
	    i == objectData->startCorner ||
	    i == (objectData->startCorner ^ 3) ) {
	    vrectSet(x, y, jointSize, jointSize, &jointRect);
	    saveFunc = vdrawpenGetDrawingFunction(pen);
	    vdrawpenSetDrawingFunction(pen, vdrawFUNC_INVERT);
	    vdrawcontextFillRectangles(context, &jointRect, 1);
	    vdrawpenSetDrawingFunction(pen, saveFunc);
	}

        switch (i) {
        
        case 0:
            joint.y += (r.h - 1);
            break;

        case 1:
            joint.y -= (r.h - 1);
            joint.x += (r.w - 1);
            break;
        
        case 2:
            joint.y += (r.h - 1);
            break;
        }
    }
}

/*
 * vmdrawRectIntersect
 * 
 * Hit test routine for domain manager base objects
 */	
vbool vmdrawRectIntersect(
    vdomain		*domain,
    vdomainObject	*object,
    vrect		*checkRect
    )
{
    vmdrawObjectData	*data;
    float		m, b, x, y;
    vrect		*bounds, r;

    if (object->type == vmdrawLINE_OBJECT) {

	data = (vmdrawObjectData *) vdomainGetObjectData(domain, object);
	bounds = vdomainGetObjectBounds(domain, object);
	vrectInset(checkRect, -2, -2, &r);	/* Leeway */

	/* Determine the equation for the line */

	if (data->startCorner == vmdrawCORNER_LOWER_LEFT ||
	    data->startCorner == vmdrawCORNER_UPPER_RIGHT) {

	    if (bounds->w != 0.0)
	      m = ((float) bounds->h) / ((float) bounds->w);
	    else
	      m = 999.0;
	    b = bounds->y - (m * bounds->x);
	}

	else {

	    if (bounds->w != 0.0)
	      m = -(((float) bounds->h) / ((float) bounds->w));
	    else
	      m = 999.0;
	    b = (bounds->y + bounds->h) - (m * (float) bounds->x);
	}

	/*
	 * Now plug check each line segment, until one cross the line
	 */

	/* Check left side */

	y = (m * (float) r.x) + b;

	if (y >= r.y && y <= (r.y + r.h))
	    return(TRUE);
	
	/* Check bottom side */

	x = ((float) (r.y - b)) / m;

	if (x >= r.x && x <= (r.x + r.w))
	    return(TRUE);
	    
	/* Check right side */

	y = (m * (float) (r.x + r.h)) + b;

	if (y >= r.y && y <= (r.y + r.h))
	    return(TRUE);
	
	/* Check top side */

	x = ((float) ((r.y + r.h) - b)) / m;

	if (x >= r.x && x <= (r.x + r.w))
	    return(TRUE);
	    
        return(FALSE);
    }
    else if (vdomainIsObjectOpaque(domain, object)) {
        return(TRUE);
    }
    else {
        return(TRUE);
    }
}

/*
 * vmdrawRecalcLayering
 *
 * Go through all objects and reassign the layer number - and if it is
 * different than it's original value, - inval to redraw
 */
void vmdrawRecalcLayering(
    vmdrawDocument	*data
    )
{
    vdomainObject	*scan;
    int			layer = 1;
    vmdrawObjectData	*objectData;
    vdomain		*domain;

    if (data == NULL || (data->viewSettings & vmdrawSHOW_LAYERING) == 0)
        return;

    if ((domain = vdomainviewGetDomain(data->domainView)) == NULL)
	return;

    scan = vdomainTopObject(domain);

    while (scan != NULL) {

	objectData  = (vmdrawObjectData *) vdomainGetObjectData
	    (vdomainviewGetDomain(data->domainView), scan);

	if (objectData->layerNumber != layer)
            vdomainviewInvalObjects(data->domainView,
				    vdomainObjectToSet(scan), 0);

	objectData->layerNumber = layer;

	layer++;
	scan = vdomainNextObjectBehind(scan);
    }
}

/*
 * _vmdrawDrawLayerInfo
 *
 * Draw the layering number information for the object
 */
static void _vmdrawDrawLayerInfo(
    vmdrawDocument	*data,
    vdomainObject	*object,
    vdrawcontext	*context
    )
{
    vdrawpen		*pen = vdrawcontextGetPen(context);
    int			posX, posY, dx, dy;
    double		saveLineWidth;
    vfont		*saveFont;
    vstr                *str;
    vcolor		*saveColor, *eraseColor;
    vmdrawObjectData	*objectData;
    vrect		r;
    const vrect		*bounds;
    static vfont	*_font = NULL;
    static int		h;

    saveFont 	  = vdrawpenGetFont(pen);
    saveLineWidth = vdrawpenGetLineWidth(pen);

    bounds = vdomainGetObjectBounds(vdomainviewGetDomain(data->domainView),
				    object);
    objectData  = (vmdrawObjectData *) vdomainGetObjectData
	(vdomainviewGetDomain(data->domainView), object);

    /*
     * Get the font to draw the layering in 
     */

    if (_font == NULL) {

	_font = vfontFindScribed(vcharScribeLiteral
				("family:helvetica-face:medium-size:10"));
	h = vfontHeight(_font) >> 1;
    }

    vdrawpenSetLineWidth(pen, 0);
    vdrawpenSetFont(pen, _font);
    saveColor  = vdrawpenGetColor(pen);
    eraseColor = vdrawpenGetComplementColor(pen);

    posX = bounds->x + (bounds->w >> 1);
    posY = bounds->y + (bounds->h >> 1) - h;

    str = vstrCloneScribed(vcharScribeFormatLiteral("%d",
						    objectData->layerNumber));
    vfontStringWidth(_font, str, &dx, &dy);
	
    vrectSet(posX - 10, posY - 2, 20, (h << 1) + 4, &r);
	
    /* 
     * Don't draw if object is too small
     */

    if (r.x > bounds->x && 
	r.x + r.w < bounds->x + bounds->w &&
	r.y > bounds->y &&
	r.y + r.h < bounds->y + bounds->h) {

	vdrawpenSetColor(pen, eraseColor);
	vdrawcontextFillRectangles(context, &r, 1);
	vdrawpenSetColor(pen, saveColor);
	vdrawcontextDrawRectangles(context, &r, 1);
	    
	vdrawcontextSetCurrentPoint(context, posX - (dx >> 1), posY);
	vdrawcontextDrawStringScribed(context, vstrScribe(str), NULL);
    } else
	vstrDestroy(str);

    vdrawpenSetLineWidth(pen, saveLineWidth);
    vdrawpenSetFont(pen, saveFont);
}

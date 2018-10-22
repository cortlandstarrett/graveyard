/* $Id: pen.c,v 1.20 1997/10/23 21:39:43 gregt Exp $ */

/************************************************************

    pen.c
    C Source to Microdraw

    (c) Copyright Visix Software  1991-1992
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

#ifndef  vmathINCLUDED
#include vmathHEADER
#endif

#ifndef  vdebugINCLUDED
#include vdebugHEADER
#endif

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

#ifndef  vclientINCLUDED
#include vclientHEADER
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

#ifndef  vnumINCLUDED
#include vnumHEADER
#endif

#ifndef  vclassINCLUDED
#include vclassHEADER
#endif

#ifndef  vinstanceINCLUDED
#include vinstanceHEADER
#endif

#ifndef  vobjectINCLUDED
#include vobjectHEADER
#endif

#ifndef  vcolorINCLUDED
#include vcolorHEADER
#endif

#ifndef  vlistINCLUDED
#include vlistHEADER
#endif

#ifndef  vdomainINCLUDED
#include vdomainHEADER
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

#ifndef  vwindowINCLUDED
#include vwindowHEADER
#endif

#ifndef  vdialogINCLUDED
#include vdialogHEADER
#endif

#ifndef  vcontrolINCLUDED
#include vcontrolHEADER
#endif

#ifndef  vbuttonINCLUDED
#include vbuttonHEADER
#endif

#ifndef  vtextviewINCLUDED
#include vtextviewHEADER
#endif

#ifndef  vtextitemINCLUDED
#include vtextitemHEADER
#endif

#ifndef  vlistviewINCLUDED
#include vlistviewHEADER
#endif

#ifndef  vdomainviewINCLUDED
#include vdomainviewHEADER
#endif

#ifndef  vdragINCLUDED
#include vdragHEADER
#endif

#ifndef  vcolorchsrINCLUDED
#include vcolorchsrHEADER
#endif

#ifndef  vdropsiteINCLUDED
#include vdropsiteHEADER
#endif

#include "micdraw.h"

#if vdebugDEBUG
static const char _vmdrawTag[] = "vmdrawPen";
#define vdebugTAG _vmdrawTag
#endif


#define ABS(x)          	( (x) > 0 ? (x) : ( -(x) ) )

vdialog				*vmdrawPenWindow = NULL;

static vdialogItemClass		*defaultDashClass;
static vdialogItemClass		*defaultPenClass;
static vlistviewClass		*defaultPenListViewClass;
static vlistview                *_penList;
static vdialogItem              *_penItem;
static vdialogItem              *_currentPenItem;
static vdialogItem		*_penBox;
static vdialogItem		*_currentPenBox;
static vcontrol                 *_startArrowItem;
static vcontrol                 *_endArrowItem;
static vtextitem                *_sizeEntry;
static vmdrawPen		 _editingPen;
static vdragClass		*_vmdrawPenListDragClass = NULL;
static vbool		_vmdrawDragging = FALSE;
static vpoint		_vmdrawDragStart;
static int		_vmdrawDragListRow = -1;

       void	 vmdrawEditPen(vmdrawPen *pen);

int vmdrawArrowFlare		= 5;
int vmdrawArrowLength		= 11;
int vmdrawArrowIndent		= 3;

/* * * * * * * * Notification Functions * * * * * * * */

static void _startArrowChkNotify(vcontrol *item, vevent *ev)
{
    _editingPen.arrows ^= vmdrawSTART_ARROW;
    vdialogInvalItem(_penItem, 0);
}

static void _endArrowChkNotify(vcontrol *item, vevent *ev)
{
    _editingPen.arrows ^= vmdrawEND_ARROW;
    vdialogInvalItem(_penItem, 0);
}

static void _penSizeNotify(
    vtextview 		*textView,
    vevent		*event,
    int			message)
{
    int         x;

    if (message == vtextviewACCEPT_NOTIFY) {
        
        x = vtextitemGetTextAsInt(_sizeEntry);
        if (x > 0 && x <= 10) {
            _editingPen.thickness = x;
            vdialogInvalItem(_penItem, 0);
        }       
        else
            vtextitemSetTextScribed(_sizeEntry, 
                                    vnumScribeInt(_editingPen.thickness));
    }
}

static void _penListNotify(
    vlistview 	*listitem,
    int		state
    )
{
    vmdrawPen			*pen;
    int				row, x;
    vdomainview			*domainView;
    vdomainObjectSet		*objectSet;
    vdomainObjectSetIterator	iterator;

    if (state != vlistviewSELECTION_HAS_CHANGED)
	return;
    
    vlistGetSelectedCell(vlistviewGetList(listitem),
			 vlistviewGetSelection(listitem), &row, &x);

    if (row < 0)
	return;

    pen = vmdrawPens + row;

    /*
     * Apply the selected pen to any selected objects
     */

    domainView = vmdrawTargetDocument->domainView;
    objectSet = vdomainGetObjectSet(vdomainviewGetDomain(domainView),
	   vdomainviewGetSelection(domainView), vdomainSELECTED, NULL);

    vdomainInitObjectSetIterator(&iterator, objectSet);
   
    while (vdomainNextObjectSetIterator(&iterator)) {

	vdomainObject		*object;
	vmdrawObjectData	*objectData;

   	object     = vdomainGetObjectSetIteratorObject(&iterator);
	objectData = vdomainGetObjectData(vdomainviewGetDomain(domainView),
					  object);
        vmdrawCopyPen(pen, &objectData->pen);
    }

    vmdrawInvalObjects(vmdrawTargetDocument, objectSet);

    vdomainDestroyObjectSetIterator(&iterator);
    vdomainDestroyObjectSet(objectSet);
}

static void _applyColor(
    vcolorchsr          *chooser,
    vcolor              *color
    )
{
    _editingPen.color = color;
	
    vdialogInvalItem(_penItem, 0);
}

static void _setColor(
    vbutton             *button,
    vevent              *ev
    )
{
    vmdrawOpenColorChooser();

    vcolorchsrSetApply(vmdrawColorChooser, _applyColor);
}

/*
 * _vmdrawCurrentPenBoxDropsiteNoteProc
 * drop   -> the current pen box's dropsite
 * drag   -> the drag interacting with the dropsite
 * event  -> the event, or NULL
 * state  -> the state of the drag over our dropsite
 *       <-  feedback in the form of a vdropFEEDBACK_foo constant
 */
static int _vmdrawCurrentPenBoxDropsiteNoteProc(
    vdropsite				*drop,
    vdrag				*drag,
    vevent				*event,
    int					 state
    )
{
    int					 retVal = vdropFEEDBACK_REJECT;

    if (vclassIsKindOf(vdragGetClass(drag), _vmdrawPenListDragClass)) {
	const void			*dragData;
	vbool				 fromList;

	dragData = vdragGetData(drag);
	fromList = (dragData == (void *) _penList) ? vTRUE : vFALSE;

	switch (state) {

	case vdropSTATE_ENTER:
	case vdropSTATE_DETAIL:
	    if (fromList)
		retVal = vdropFEEDBACK_COPY;
	    break;

	case vdropSTATE_DROP:
	    if (fromList) {
		/* set current pen */
		vmdrawCopyPen(vmdrawPens + _vmdrawDragListRow,
			      &vmdrawCurrentPen);
		vdialogInvalItem(_currentPenItem, 0);
		/* let the drag know the drop was handled */
		vdragSetData(drag, NULL);
	    }
	    break;

	default:
	    vdebugAssert(state == vdropSTATE_LEAVE);
	    break;
	}
    }

    return retVal;
}


/*
 * _vmdrawEditPenBoxDropsiteNoteProc
 * drop   -> the edit pen box's dropsite
 * drag   -> the drag interacting with the dropsite
 * event  -> the event, or NULL
 * state  -> the state of the drag over our dropsite
 *       <-  feedback in the form of a vdropFEEDBACK_foo constant
 */
static int _vmdrawEditPenBoxDropsiteNoteProc(
    vdropsite				*drop,
    vdrag				*drag,
    vevent				*event,
    int					 state
    )
{
    int					 retVal = vdropFEEDBACK_REJECT;

    if (vclassIsKindOf(vdragGetClass(drag), _vmdrawPenListDragClass)) {
	const void			*dragData;
	vbool				 fromList;

	dragData = vdragGetData(drag);
	fromList = (dragData == (void *) _penList) ? vTRUE : vFALSE;

	switch (state) {

	case vdropSTATE_ENTER:
	case vdropSTATE_DETAIL:
	    if (fromList)
		retVal = vdropFEEDBACK_COPY;
	    break;

	case vdropSTATE_DROP:
	    if (fromList) {
		/* set editing pen */
		vmdrawEditPen(vmdrawPens + _vmdrawDragListRow);
		/* let the drag know the drop was handled */
		vdragSetData(drag, NULL);
	    }
	    break;

	default:
	    vdebugAssert(state == vdropSTATE_LEAVE);
	    break;
	}
    }

    return retVal;
}


/*
 * _vmdrawPenListDropsiteNoteProc
 * drop   -> the pen list's dropsite
 * drag   -> the drag interacting with the dropsite
 * event  -> the event, or NULL
 * state  -> the state of the drag over our dropsite
 *       <-  feedback in the form of a vdropFEEDBACK_foo constant
 */
static int _vmdrawPenListDropsiteNoteProc(
    vdropsite				*drop,
    vdrag				*drag,
    vevent				*event,
    int					 state
    )
{
    int					 retVal = vdropFEEDBACK_REJECT_RETRY;
    const void				*dragData = vdragGetData(drag);
    vbool				 fromList, inList;
    const vrect				*listRect;

    fromList = (dragData == (void *) _penList) ? vTRUE : vFALSE;
    listRect = vlistviewGetListRect(_penList);
    inList = (event != NULL &&
	      vrectMContainsPoint(listRect, veventGetPointerX(event),
				  veventGetPointerY(event)));

    if (vclassIsKindOf(vdragGetClass(drag), _vmdrawPenListDragClass)) {
	switch (state) {

	case vdropSTATE_ENTER:
	case vdropSTATE_DETAIL:
	    if (fromList)
		retVal = vdropFEEDBACK_REJECT;
	    else if (inList)
		/* this is a good place for a drop */
		retVal = vdropFEEDBACK_COPY;
	    break;

	case vdropSTATE_DROP:
	    if (!fromList && inList) {
		vmdrawPen		*pen;

		vmdrawPenCount++;
		vmdrawPens = (vmdrawPen *) vmemRealloc(vmdrawPens,
					   sizeof(vmdrawPen) * vmdrawPenCount);

		pen = vmdrawPens + vmdrawPenCount - 1;
		vmdrawCopyPen(&_editingPen, pen);

		vlistSetRowCount(vlistviewGetList(_penList),
				 vmdrawPenCount);
		vlistSetCellValue(vlistviewGetList(_penList),
				  vmdrawPenCount - 1, 0, NULL);
		vlistSelectRow(vlistviewGetList(_penList),
			       vlistviewGetSelection(_penList),
			       vmdrawPenCount - 1);
	    }
	    break;

	default:
	    vdebugAssert(state == vdropSTATE_LEAVE);
	    break;
	}
    } else
	retVal = vdropFEEDBACK_REJECT;

    return retVal;
}


/* * * * * * * * Primary Pen Window Functions * * * * * * * */

/*
 * vmdrawCreatePenWindow
 *
 * Load up and initialize the Pen window
 */
void vmdrawCreatePenWindow()
{
    vbutton             *color;
    vlist		*listData;
    vdropsite		*drop;

    if (vmdrawPenWindow != NULL) {
        if (!vdialogIsOpen(vmdrawPenWindow))
            vdialogOpen(vmdrawPenWindow);
	vwindowRaise((vwindow *) vmdrawPenWindow);
        return;
      }

    vmdrawPenWindow = vmdrawLoadDialog(vnameInternGlobalLiteral("Pens"));

    _penList    = (vlistview *)
        vdialogFindItem(vmdrawPenWindow, vnameInternGlobalLiteral("PenList"));
    _penItem    = 
        vdialogFindItem(vmdrawPenWindow, vnameInternGlobalLiteral("EditPen"));
    _currentPenItem    = 
        vdialogFindItem(vmdrawPenWindow, vnameInternGlobalLiteral("Pen"));
    _penBox = 
        vdialogFindItem(vmdrawPenWindow, vnameInternGlobalLiteral("EditPenBox"));
    _currentPenBox = 
        vdialogFindItem(vmdrawPenWindow, vnameInternGlobalLiteral("PenBox"));
    _startArrowItem  = (vcontrol *)
        vdialogFindItem(vmdrawPenWindow, vnameInternGlobalLiteral("ArrowStart"));
    _endArrowItem  = (vcontrol *)
        vdialogFindItem(vmdrawPenWindow, vnameInternGlobalLiteral("ArrowEnd"));
    _sizeEntry	  = (vtextitem *)
        vdialogFindItem(vmdrawPenWindow, vnameInternGlobalLiteral("Size"));
    color    = (vbutton *)
        vdialogFindItem(vmdrawPenWindow, vnameInternGlobalLiteral("Color"));

    vcontrolSetNotify(_startArrowItem,                   _startArrowChkNotify);
    vcontrolSetNotify(_endArrowItem,                     _endArrowChkNotify);
    vtextviewSetNotify(vtextitemGetView(_sizeEntry),     _penSizeNotify);
    vlistviewSetSelectNotify(_penList, 			 _penListNotify);
    vbuttonSetNotify(color,                              _setColor);

    vdialogInvalItem(_penItem, 0);

    vtextitemSetOneLine(_sizeEntry, TRUE);

    /* install current pen box dropsite */
    drop = vdropsiteCreateInternal();
    vdropsiteSetData(drop, (void *) _currentPenBox);
    vdropsiteSetNotify(drop, _vmdrawCurrentPenBoxDropsiteNoteProc);
    vdialogSetItemDropsite(_currentPenBox, drop);

    /* install edit pen box dropsite */
    drop = vdropsiteCreateInternal();
    vdropsiteSetData(drop, (void *) _penBox);
    vdropsiteSetNotify(drop, _vmdrawEditPenBoxDropsiteNoteProc);
    vdialogSetItemDropsite(_penBox, drop);

    /* install pen list dropsite */
    drop = vdropsiteCreateInternal();
    vdropsiteSetData(drop, (void *) _penList);
    vdropsiteSetNotify(drop, _vmdrawPenListDropsiteNoteProc);
    vdialogSetItemDropsite(vlistviewGetItem(_penList), drop);

    /*
     * Setup the pen list
     */

    vlistviewSetList(_penList, listData = vlistCreate());
    vlistviewSetSelection(_penList, vlistCreateSelection(listData));
    vlistSetSelectMethod(listData, vlistviewGetSelection(_penList),
			 vlistONE_ONLY_SELECTION);
    vlistSetRowCount(listData, vmdrawPenCount);
    vlistSetCellValue(listData, vmdrawPenCount - 1, 0, NULL);

    vmdrawEditPen(&_editingPen);

    vdialogMove(vmdrawPenWindow, 200, 200);

    vdialogOpen(vmdrawPenWindow);
}

/*
 * vmdrawEditPen
 *
 * Copy the pen into the editing pen - and reset all of the editing pen
 * info (arrow checkboxes, size text entry, etc).
 */
void vmdrawEditPen(
    vmdrawPen		*pen
    )
{
    vmdrawCopyPen(pen, &_editingPen);

    vcontrolSetValue(_startArrowItem,
                     (_editingPen.arrows & vmdrawSTART_ARROW) ? 1 : 0);
    vcontrolSetValue(_endArrowItem,
                     (_editingPen.arrows & vmdrawEND_ARROW) ? 1 : 0);

    vtextitemSetTextScribed(_sizeEntry, vnumScribeInt(pen->thickness));

    vdialogInvalItem(_penItem, 0);
}

/*
 * vmdrawLoadPens
 */
vmdrawPen *vmdrawLoadPens(
    vresource		resource,
    int			*penCount
    )
{
    vresource           penres, entryRes;
    int                 count, i = 0;
    vmdrawPen           *scan, *pens;

    if (!vresourceTestGet(resource, vnameInternGlobalLiteral("Pen Set"), &penres))
        return(NULL);

    *penCount = count = vresourceCountComponents(penres);

    scan = pens = (vmdrawPen *) vmemAlloc(sizeof(vmdrawPen) * count);

    while (count-- > 0) {
	  
        entryRes = vresourceGetAt(penres, i);

        vmdrawLoadPen(entryRes, scan);
        i++;
        scan++;
    }
    return(pens);
}

/*
 * vmdrawLoadPen
 * 
 * Load at individual pen
 */
void vmdrawLoadPen(
    vresource           resource,
    vmdrawPen           *pen
    )
{
    vresource           patRes, res;
    int                 i;

    pen->size      = 0;
    pen->thickness = vresourceGetInteger(resource, vname_Width);
    pen->arrows    = vresourceGetInteger(resource, vname_Attribute);
        
    /* Dashes */

    patRes = vresourceGet(resource,
                          vnameInternGlobalLiteral("Pattern"));
    for (i=0; i<vmdrawMAX_PENPAT_SIZE; i++) {
        pen->pat[i] = vresourceGetIntegerAt(patRes, i);
        if (pen->pat[i] != 0)
            pen->size++;
    }
        
    /* Color */

    pen->color = vresourceTestGet(resource, vname_Color, &res) ? 
        vcolorLoadIntern(res) : NULL;
}

void vmdrawSavePens(
    vresource		resource,
    vmdrawPen		*pens,
    int			count
    )
{
    vresource           penres, entryRes;
    int                 i = 0;

    penres = vresourceCreateArray
      (resource, vnameInternGlobalLiteral("Pen Set"), vresourceDICT, count);

    while (count-- > 0) {
	  
        entryRes = vresourceCreateAt(penres, i, vresourceDICT);

        vmdrawStorePen(entryRes, pens);
        i++;
        pens++;
    }
}

/*
 * vmdrawStorePen
 *
 * Store an individual pen
 */
void vmdrawStorePen(
    vresource		resource,
    vmdrawPen		*pen
    )
{
    vresource           patRes;
    int                 i;

    vresourceSetInteger(resource, vname_Width, pen->thickness);
    vresourceSetInteger(resource, vname_Attribute, pen->arrows);

    /* Dashes */

    patRes = vresourceCreateArray
        (resource, vnameInternGlobalLiteral("Pattern"), vresourceINTEGER,
         vmdrawMAX_PENPAT_SIZE);
    for (i=0; i<vmdrawMAX_PENPAT_SIZE; i++)
        vresourceSetIntegerAt(patRes, i, pen->pat[i]);
    
    /* Color */

    if (pen->color == NULL)
        vresourceRemoveIfExists(resource, vname_Color);
    else
        vcolorStoreSpec(vcolorGetSpec(pen->color),
                        vresourceCreate(resource, vname_Color, vresourceDICT));
}

/*
 * vmdrawCopyPen
 */
void vmdrawCopyPen(
    vmdrawPen		*pen,
    vmdrawPen		*target
    )
{
    *target = *pen;
}

/*
 * vmdrawDestroyPen
 */
void vmdrawDestroyPen(
    vmdrawPen		*pen
    )
{
}

/*
 * vmdrawSetPen
 * 
 * Set up the current drawing context to use the given pen
 */
void vmdrawSetPen(
    vmdrawPen		*pen,
    float                scale,
    vdrawcontext	*context
    )
{ 
    vdrawpen	*dpen = vdrawcontextGetPen(context);
    float	dash[vmdrawMAX_PENPAT_SIZE];
    int         i;

    if (pen->thickness == 1) {
        if (scale == 100.0)
            vdrawpenSetLineWidth(dpen, 0);	/* Optimize for normal scale */
        else
            vdrawpenSetLineWidth(dpen, 1);
    }
    else
        vdrawpenSetLineWidth(dpen, pen->thickness);

    /*
     * Set up the dashes
     */

    if (pen->size > 0) {
        
        for (i=0; i<pen->size; i++)
            dash[i] = pen->pat[i];

	vdrawpenSetDashPattern(dpen, dash, pen->size, 0);
    }

    /* Color */

    if (pen->color != NULL)
        vdrawpenSetColor(dpen, pen->color);
}

/*
 * vmdrawPushPopPen
 * 
 * A 1-level stack of pens - used to save the push and pop the pen
 * state.  Can't push more than 1.
 */
void vmdrawPushPopPen(
    vbool                push,
    vdrawcontext	*context
    )
{
    vdrawpen	       *pen = vdrawcontextGetPen(context);
    static size_t      size;
    static float       *pat;
    static double      offset, lineWidth;
    static vcolor      *saveColor;

    if (push) {
	pat = vdrawpenGetDashPattern(pen, &size);
	offset = vdrawpenGetDashOffset(pen);
        lineWidth = vdrawpenGetLineWidth(pen);
        saveColor = vdrawpenGetColor(pen);
    }
    else {
	vdrawpenSetDashPattern(pen, pat, size, offset);
        vdrawpenSetLineWidth(pen, lineWidth);
        vdrawpenSetColor(pen, saveColor);
    }
}

/* * * * * * * * * * * Dialog Item Methods * * * * * * * */

/*
 * _vmdrawPenItemDrawWith
 *
 * Draws the pen items for the current pen and editing pen dialog items
 * Draws the pen by drawing a line in that pen from the left-vertical
 * center to the right vertical center.
 */
static void _vmdrawPenItemDrawWith(
    vdialogItem		*item,
    vdrawcontext	*context
    )
{
    const vrect         *r;
    int                 y;
    vmdrawPen		*pen;

    vclassSendSuper(defaultPenClass, vdialogDRAW_ITEM_WITH, (item, context));

    r = vdialogGetItemRect(item);

    if (item == _currentPenItem)
	pen = &vmdrawCurrentPen;
    else
	pen = &_editingPen;

    vmdrawPushPopPen(TRUE, context);
    vmdrawSetPen(pen, 100, context);
    y =  r->y + (r->h >> 1);
    vmdrawDrawLine(r->x + 5, y, r->x + r->w - 5, y, pen->arrows, context);
    vmdrawPushPopPen(FALSE, context);
}

/*
 * _vmdrawDashItemDraw
 *
 * Draws the dash item - this is not implemented yet.
 */
static void _vmdrawDashItemDraw(
    vdialogItem		*item
    )
{
    const vrect         *r;

    vclassSendSuper(defaultDashClass, vdialogDRAW_ITEM, (item));

    r = vdialogGetItemRect(item);
}

/*
 * _vmdrawDrawPenCellWith
 *
 * Draw a cell in the pen list
 */
static void _vmdrawDrawPenCellWith(
    vlistview		*listItem,
    int			row,
    int			col, 
    int			selected,
    vrect		*r,
    vdrawcontext	*context
    )
{
    int                 y;

    vmdrawPushPopPen(TRUE, context);
    vmdrawSetPen(vmdrawPens + row, 100, context);
    y =  r->y + (r->h >> 1);
    vmdrawDrawLine(r->x + 5, y, r->x + r->w - 5, y, (vmdrawPens + row)->arrows,
		   context);
    vmdrawPushPopPen(FALSE, context);
}

/* * * * * * * * Line/Arrow Drawing * * * * * * * * */

/*
 * vmdrawDrawLine
 * 
 * Draw a line - in the current pen context - and add the appropriate 
 * arrows.
 */
void vmdrawDrawLine(
    int         x,
    int         y,
    int         tox,
    int         toy,
    int         arrows,
    vdrawcontext *context
    )
{
    float	mag;
    int		angle;
    double	lineWidth;
    vdrawpath	*path;

    lineWidth = vdrawpenGetLineWidth(vdrawcontextGetPen(context));

    tox -= x;
    toy -= y;

    vdrawcontextTranslate(context, x, y);
    vdrawcontextSetCurrentPoint(context, 0, 0);
    vdrawcontextDrawLineTo(context, tox, toy);

    /*
     * Compute the angle to rotate the drawing context
     */

    mag   = sqrt((tox * tox) + (toy * toy));
    angle = (int) ((asin(toy/mag) / (2*vmathPI)) * 360);

    if (tox < 0 && toy < 0)
        angle = (180 - angle);
    else if (tox < 0)
	angle = (180 - angle);
    else if (toy < 0)
	angle += 360;

    if (arrows & vmdrawSTART_ARROW) {
	vdrawcontextRotate(context, angle);
	path = vdrawpathCreate();
	vdrawpathMoveTo(path, 0, 0);
	vdrawpathAppendLineToRelative(path, 0, lineWidth  / 2);
	vdrawpathAppendLineToRelative(path, vmdrawArrowLength,
				      vmdrawArrowFlare);
	vdrawpathAppendLineToRelative(path, -vmdrawArrowIndent,
				      -vmdrawArrowFlare);
	vdrawpathAppendLineToRelative(path, 0, -lineWidth);
	vdrawpathAppendLineToRelative(path, vmdrawArrowIndent,
				      -vmdrawArrowFlare);
	vdrawpathAppendLineToRelative(path, -vmdrawArrowLength,
				      vmdrawArrowFlare);
	vdrawpathAppendLineToRelative(path, 0, lineWidth);
	vdrawcontextFillPath(context, path);
	vdrawpathRelease(path);
	vdrawcontextRotate(context, -angle);
    }
    if (arrows & vmdrawEND_ARROW) {
        vdrawcontextSetCurrentPoint(context, tox, toy);
	vdrawcontextTranslate(context, tox, toy);
	vdrawcontextRotate(context, angle);
	path = vdrawpathCreate();
	vdrawpathMoveTo(path, 0, 0);
	vdrawpathAppendLineToRelative(path, 0, lineWidth  / 2);
	vdrawpathAppendLineToRelative(path, -vmdrawArrowLength,
				      vmdrawArrowFlare);
	vdrawpathAppendLineToRelative(path, vmdrawArrowIndent,
				      -vmdrawArrowFlare);
	vdrawpathAppendLineToRelative(path, 0, -lineWidth);
	vdrawpathAppendLineToRelative(path, -vmdrawArrowIndent,
				      -vmdrawArrowFlare);
	vdrawpathAppendLineToRelative(path, vmdrawArrowLength,
				      vmdrawArrowFlare);
	vdrawpathAppendLineToRelative(path, 0, lineWidth);
	vdrawcontextFillPath(context, path);
	vdrawpathRelease(path);
	vdrawcontextRotate(context, -angle);
	vdrawcontextTranslate(context, -tox, -toy);
    }

    vdrawcontextTranslate(context, -x, -y);
}

/* * * * * * *  DRAGGABLE LIST ITEM CLASS METHODS   * * * * * * */


/*
 * _vmdrawNotifyListDragAction
 */
static void _vmdrawNotifyListDragAction(
    vdrag       *drag,
    int		 dragAction,
    vevent      *event
    )
{
    vbool		 fromList = (vdragGetData(drag) == (void *) _penList);
    vbool		 remove;

    remove = (fromList && event != NULL &&
	      (veventGetWindow(event) != vdialogGetWindow(vmdrawPenWindow) ||
	       !vrectContainsPoint(vlistviewGetListRect(_penList),
				   veventGetPointerX(event),
				   veventGetPointerY(event))));

    if (dragAction == vdragACTION_DROP && remove) {
	vmdrawPen	*pen;

	/* if no dropsite handled the drop, it was a remove operation */
	pen = vmdrawPens + _vmdrawDragListRow;
	vmdrawPenCount--;

	(void) vmemMove(pen + 1, pen, 
	       sizeof(vmdrawPen) * (vmdrawPenCount - _vmdrawDragListRow));

	vmdrawPens = (vmdrawPen *) vmemRealloc(vmdrawPens,
					   sizeof(vmdrawPen) * vmdrawPenCount);
    	vlistSetRowCount(vlistviewGetList(_penList), vmdrawPenCount);
	if (vmdrawPenCount > 0)
	    vlistSetCellValue(vlistviewGetList(_penList),
			      vmdrawPenCount - 1, 0, NULL);
    }

    if (dragAction == vdragACTION_DROP ||
	dragAction == vdragACTION_ABORT) {
	vdragDestroyLater(drag);
	if (event != NULL)
	    vdragSetFeedbackCursor(drag, veventGetWindow(event), NULL);
    }
}

/*
 * _vmdrawNotifyListDragFeedbackWith
 *
 * draw the doodad being dragged
 */
static void _vmdrawNotifyListDragFeedbackWith(
    vdrag		*drag,
    int			 dropAction,
    vevent		*event,
    vrect		*drawRect,
    vdrawcontext	*context
    )
{
    vrect		r = *drawRect;
    int			y;
    vbool		fromList = (vdragGetData(drag) == (void *) _penList);
    vmdrawPen		*pen;
    vcursor		*cursor = NULL;

    vmdrawPushPopPen(TRUE, context);
    vdrawpenSetLineWidth(vdrawcontextGetPen(context), 1);
    vdrawcontextDrawRectanglesInside(context, drawRect, 1);

    y =  r.y + (r.h >> 1);

    if (fromList)
	pen = vmdrawPens + _vmdrawDragListRow;
    else
	pen = &_editingPen;

    vmdrawSetPen(pen, 100, context);
    vmdrawDrawLine(r.x + 5, y, r.x + r.w - 5, y, pen->arrows, context);

    vmdrawPushPopPen(FALSE, context);

    /*
     * if the mouse isn't over a dropsite which will accept it, and it's not
     * over the list it came from, then this is a place where the user could
     * drop to _remove_ the pen from the list.
     */
    if (fromList && dropAction == vdragDROP_ACTION_NONE && event != NULL) {
	if (vwindowGetPointerWindow() != vdialogGetWindow(vmdrawPenWindow))
	    cursor = vlafGetCursor(vlafCURSOR_GOOD_DROP);
	else {
	    int				 x = veventGetPointerX(event);
	    int				 y = veventGetPointerY(event);

	    if (veventGetWindow(event) != vdialogGetWindow(vmdrawPenWindow))
		vwindowTransformPoint(veventGetWindow(event),
				      vdialogGetWindow(vmdrawPenWindow),
				      x, y, &x, &y);
	    if (!vrectContainsPoint(vlistviewGetListRect(_penList), x, y))
		cursor = vlafGetCursor(vlafCURSOR_GOOD_DROP);
	}
    }
    if (cursor == NULL) {
	switch (dropAction) {
	case vdragDROP_ACTION_MOVE:
	    cursor = vlafGetCursor(vlafCURSOR_GOOD_DROP);
	    break;
	case vdragDROP_ACTION_COPY:
	    cursor = vlafGetCursor(vlafCURSOR_GOOD_DROP_COPY);
	    break;
	case vdragDROP_ACTION_LINK:
	    cursor = vlafGetCursor(vlafCURSOR_GOOD_DROP_LINK);
	    break;
	default:
	    cursor = vlafGetCursor(vlafCURSOR_BAD_DROP);
	    break;
	}
    }
    vdragSetFeedbackCursor(drag, veventGetWindow(event), cursor);
}

static vdragClass *_vmdrawGetPenListDragClass(
    void
    )
{
    if (_vmdrawPenListDragClass == NULL) {
	vdragClass			*clas;

	clas = vclassReproduce(vdragGetDefaultClass());
	vclassSetNameScribed(clas, vcharScribeLiteral("_vmdrawPenListDrag"));
	vclassSet(clas, vdragNOTIFY_ACTION, _vmdrawNotifyListDragAction);
	vclassSet(clas, vdragNOTIFY_FEEDBACK_WITH,
		  _vmdrawNotifyListDragFeedbackWith);
	_vmdrawPenListDragClass = clas;
    }

    return _vmdrawPenListDragClass;
}


/*
 * _vmdrawHandleListButtonDown
 */
static int _vmdrawHandleListButtonDown(
    vlistview	*view,
    vevent      *event
    )
{
    vpointSet(veventGetPointerX(event), veventGetPointerY(event),
	      &_vmdrawDragStart);

    return (vclassSendSuper(defaultPenListViewClass,
                            vdialogHANDLE_ITEM_BUTTON_DOWN, 
                            (view, event)));
}

/*
 * _vmdrawHandleListDrag
 */
static int _vmdrawHandleListDrag(
    vlistview	*view,
    vevent      *event
    )
{
    vpoint      *pt;
    vdrag       *drag;
    vrect       r;
    int		col;

    if (veventGetBinding(event) == vname_Drag) {

        pt = &_vmdrawDragStart;

        if (ABS(veventGetPointerX(event) - pt->x) > 4 ||
            ABS(veventGetPointerY(event) - pt->y) > 4) {

            drag = vdragCreateOfClass(_vmdrawGetPenListDragClass());
            vdragSetData(drag, view);

            vlistviewMapPointToCell(view, pt, &_vmdrawDragListRow, &col);

            vlistviewGetCellRect(view, _vmdrawDragListRow, col, &r);

            vdragSetMaxSize(drag, r.w, r.h);
	    vdragSetOffset(drag, pt->x - r.x, pt->y - r.y);

            vdragStart(drag, event);
        }
        return(TRUE);
    }

    return(vclassSendSuper(defaultPenListViewClass, vdialogHANDLE_ITEM_DRAG,
                           (view, event)));
}

/*
 * _vmdrawDestroyList
 */
static void _vmdrawDestroyList(
    vlistview		*view
    )
{
    vlist		*list;

    list = vlistviewGetList(view);
    if (list != NULL) {
	vlistviewSetList(view, NULL);
	vlistDestroy(list);
    }

    vclassSendSuper(defaultPenListViewClass, vobjectDESTROY, (view));
}

/*
 * _vmdrawHandlePenButtonDown
 */
int _vmdrawHandlePenButtonDown(
    vdialogItem	*item,
    vevent      *event
    )
{
    const vrect		*r;
    vpoint		*pt;

    _vmdrawDragging = FALSE;
    
    if (item != _currentPenItem) {

	if (veventGetBinding(event) == vname_Adjust)
	    veventSetBinding(event, vname_Drag);
    
	else if (veventGetBinding(event) == vname_Drag) {
    
	    pt = &_vmdrawDragStart;
	    r  = vdialogGetItemRect(item);
    
	    vpointSet(veventGetPointerX(event), veventGetPointerY(event), pt);
    
	    if (vrectContainsPoint(r, pt->x, pt->y)) {
		
		vwindowSyncEvents();
		_vmdrawDragging = TRUE;
		
		return(TRUE);
	    }
	}
    }

    return (vclassSendSuper(defaultPenClass,
                            vdialogHANDLE_ITEM_BUTTON_DOWN, 
                            (item, event)));
}

/*
 * _vmdrawHandlePenDrag
 */
int _vmdrawHandlePenDrag(
    vdialogItem	*item,
    vevent      *event
    )
{
    const vrect		*r;
    vpoint      	*pt;
    vdrag       	*drag;

    if (veventGetBinding(event) == vname_Adjust)
        veventSetBinding(event, vname_Drag);

    else if (_vmdrawDragging) {

        pt = &_vmdrawDragStart;

        if (ABS(veventGetPointerX(event) - pt->x) > 4 ||
            ABS(veventGetPointerY(event) - pt->y) > 4) {

	    _vmdrawDragListRow = -1;

            drag = vdragCreateOfClass(_vmdrawGetPenListDragClass());
            vdragSetData(drag, item);

	    r = vdialogGetItemRect(item);
            vdragSetMaxSize(drag, r->w, r->h);
	    vdragSetOffset(drag, pt->x - r->x, pt->y - r->y);

            vdragStart(drag, event);
        }
        return(TRUE);
    }

    return(vclassSendSuper(defaultPenClass, vdialogHANDLE_ITEM_DRAG,
                           (item, event)));
}

/*
 * _vmdrawHandlePenButtonUp
 */
int _vmdrawHandlePenButtonUp(
    vdialogItem	*item,
    vevent      *event
    )
{
    if (veventGetBinding(event) == vname_Adjust)
        veventSetBinding(event, vname_Drag);

    else if (_vmdrawDragging)
        return(TRUE);

    return (vclassSendSuper(defaultPenClass,
                            vdialogHANDLE_ITEM_BUTTON_UP,
                            (item, event)));
}

/* * * * * *   STARTUP AND SHUTDOWN * * * * * */

/*
 * _vmdrawPenShutdown
 *
 * Cleanup after the Pen window
 */
static void _vmdrawPenShutdown(void)
{
    vclassDestroy(defaultPenClass);
    vclassDestroy(defaultDashClass);
}

/*
 * vmdrawPenStartup
 *
 * One-time setup for the Pen window
 */
void vmdrawPenStartup()
{
    /*
     * Setup the dash dialog item class
     */

    defaultDashClass = vclassReproduce(vdialogGetBoxItemClass());
	
    vclassSetNameScribed(defaultDashClass,
                         vcharScribeLiteral("vmdrawDashItem"));

    vclassSet(defaultDashClass,   vdialogDRAW_ITEM,    _vmdrawDashItemDraw);

    /*
     * Setup the pen dialog item class
     */

    defaultPenClass = vclassReproduce(vdialogGetBoxItemClass());
	
    vclassSetNameScribed(defaultPenClass,
                         vcharScribeLiteral("vmdrawPenItem"));

    vclassSet(defaultPenClass,
	      vdialogDRAW_ITEM_WITH,   		_vmdrawPenItemDrawWith);
    vclassSet(defaultPenClass,
              vdialogHANDLE_ITEM_BUTTON_DOWN,   _vmdrawHandlePenButtonDown);
    vclassSet(defaultPenClass,
              vdialogHANDLE_ITEM_DRAG,          _vmdrawHandlePenDrag);
    vclassSet(defaultPenClass,
              vdialogHANDLE_ITEM_BUTTON_UP,     _vmdrawHandlePenButtonUp);


    /*
     * Create the default draggable list item class & keyitem class
     */

    defaultPenListViewClass = vclassReproduce(vlistviewGetDefaultClass());

    vclassSetNameScribed(defaultPenListViewClass,
                         vcharScribeLiteral("vmdrawPenListView"));

    vclassSet(defaultPenListViewClass,
              vdialogHANDLE_ITEM_BUTTON_DOWN,     _vmdrawHandleListButtonDown);
    vclassSet(defaultPenListViewClass,
              vdialogHANDLE_ITEM_DRAG,            _vmdrawHandleListDrag);
    vclassSet(defaultPenListViewClass,
              vobjectDESTROY,     		  _vmdrawDestroyList);
    vclassSet(defaultPenListViewClass,
	      vlistviewDRAW_CELL_CONTENTS_WITH,   _vmdrawDrawPenCellWith);

    vclientRegisterShutdown(_vmdrawPenShutdown);
}



/* $Id: pattern.c,v 1.21 1997/10/23 21:39:43 gregt Exp $ */

/************************************************************

    pattern.c
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

#ifndef  vclassINCLUDED
#include vclassHEADER
#endif

#ifndef  vobjectINCLUDED
#include vobjectHEADER
#endif

#ifndef  vpixmapINCLUDED
#include vpixmapHEADER
#endif

#ifndef  vcolorINCLUDED
#include vcolorHEADER
#endif

#ifndef  vimageINCLUDED
#include vimageHEADER
#endif

#ifndef  vlistINCLUDED
#include vlistHEADER
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

#ifndef  vdrawcontextINCLUDED
#include vdrawcontextHEADER
#endif

#ifndef  vwindowINCLUDED
#include vwindowHEADER
#endif

#ifndef  vmenuINCLUDED
#include vmenuHEADER
#endif

#ifndef  vdialogINCLUDED
#include vdialogHEADER
#endif

#ifndef  vcontrolINCLUDED
#include vcontrolHEADER
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

#include "micdraw.h"


#if vdebugDEBUG
static const char _vmdrawTag[] = "vmdrawPattern";
#define vdebugTAG _vmdrawTag
#endif

#define vmdrawBOX_SIZE	 7
#define ABS(x)           ( (x) > 0 ? (x) : ( -(x) ) )

vdialog				*vmdrawPatternWindow = NULL;
vcolorPalette			*vmdrawPalette;

static vdialogItemClass		*defaultPatternClass;
static vdialogItemClass		*defaultPatEditClass;
static vlistviewClass		*defaultPatListViewClass;
static vlistview                *_patternList;
static vdialogItem              *_patternItem;
static vdialogItem              *_currentPatternItem;
static vdialogItem              *_patEditItem;
static vdialogItem		*_currentPatternBox;
static vdialogItem		*_patternBox;
static vcontrol			*_colorMenu;
static vmdrawPattern		 _editingPattern;
static int			 _editingIndex = 1;
static vdragClass		*_vmdrawPatListDragClass = NULL;
static vbool		_vmdrawDragging = FALSE;
static vpoint		_vmdrawDragStart;
static int		_vmdrawDragListRow = -1;

       void 	 vmdrawEditPattern(vmdrawPattern *pattern);

/* * * * * * * * Notification Functions * * * * * * * */

static void _patternListNotify(
    vlistview 	*listitem,
    int		state
    )
{
    vmdrawPattern		*pattern;
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

    pattern = vmdrawPatterns + row;

    /*
     * Apply the selected pattern to any selected objects
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
        vmdrawCopyPattern(pattern, &objectData->pattern);
    }
   
    vdomainviewInvalObjects(domainView, objectSet, 0);

    vdomainDestroyObjectSetIterator(&iterator);
    vdomainDestroyObjectSet(objectSet);
}

static void _setColor(
    vmenu		*menu,
    vevent              *ev
    )
{
    if (veventGetType(ev) == veventBUTTON_UP) {

	_editingIndex = vmenuGetItemIndex(menu, vmenuGetSelection(menu));
	
	vdialogInvalItem(_patternItem, 0);

	vcontrolSetValue(_colorMenu, _editingIndex);
    }
}

/*
 * _vmdrawCurrentPatternBoxDropsiteNoteProc
 * drop   -> the current pattern box's dropsite
 * drag   -> the drag interacting with the dropsite
 * event  -> the event, or NULL
 * state  -> the state of the drag over our dropsite
 *       <-  feedback in the form of a vdropFEEDBACK_foo constant
 */
static int _vmdrawCurrentPatternBoxDropsiteNoteProc(
    vdropsite				*drop,
    vdrag				*drag,
    vevent				*event,
    int					 state
    )
{
    int					 retVal = vdropFEEDBACK_REJECT;

    if (vclassIsKindOf(vdragGetClass(drag), _vmdrawPatListDragClass)) {
	const void			*dragData;
	vbool				 fromList;

	dragData = vdragGetData(drag);
	fromList = (dragData == (void *) _patternList) ? vTRUE : vFALSE;

	switch (state) {

	case vdropSTATE_ENTER:
	case vdropSTATE_DETAIL:
	    if (fromList)
		retVal = vdropFEEDBACK_COPY;
	    break;

	case vdropSTATE_DROP:
	    if (fromList) {
		/* set current pattern */
		vmdrawCopyPattern(vmdrawPatterns + _vmdrawDragListRow,
				  &vmdrawCurrentPattern);
		vdialogInvalItem(_currentPatternItem, 0);
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
 * _vmdrawEditPatternBoxDropsiteNoteProc
 * drop   -> the edit pattern box's dropsite
 * drag   -> the drag interacting with the dropsite
 * event  -> the event, or NULL
 * state  -> the state of the drag over our dropsite
 *       <-  feedback in the form of a vdropFEEDBACK_foo constant
 */
static int _vmdrawEditPatternBoxDropsiteNoteProc(
    vdropsite				*drop,
    vdrag				*drag,
    vevent				*event,
    int					 state
    )
{
    int					 retVal = vdropFEEDBACK_REJECT;

    if (vclassIsKindOf(vdragGetClass(drag), _vmdrawPatListDragClass)) {
	const void			*dragData;
	vbool				 fromList;

	dragData = vdragGetData(drag);
	fromList = (dragData == (void *) _patternList) ? vTRUE : vFALSE;

	switch (state) {

	case vdropSTATE_ENTER:
	case vdropSTATE_DETAIL:
	    if (fromList)
		retVal = vdropFEEDBACK_COPY;
	    break;

	case vdropSTATE_DROP:
	    if (fromList) {
		/* set editing pattern */
		vmdrawEditPattern(vmdrawPatterns + _vmdrawDragListRow);
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
 * _vmdrawPatternListDropsiteNoteProc
 * drop   -> the pattern list's dropsite
 * drag   -> the drag interacting with the dropsite
 * event  -> the event, or NULL
 * state  -> the state of the drag over our dropsite
 *       <-  feedback in the form of a vdropFEEDBACK_foo constant
 */
static int _vmdrawPatternListDropsiteNoteProc(
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

    fromList = (dragData == (void *) _patternList) ? vTRUE : vFALSE;
    listRect = vlistviewGetListRect(_patternList);
    inList = (event != NULL &&
	      vrectMContainsPoint(listRect, veventGetPointerX(event),
				  veventGetPointerY(event)));

    if (vclassIsKindOf(vdragGetClass(drag), _vmdrawPatListDragClass)) {
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
		vmdrawPattern		*pattern;

		vmdrawPatternCount++;
		vmdrawPatterns = (vmdrawPattern *) vmemRealloc(vmdrawPatterns,
				   sizeof(vmdrawPattern) * vmdrawPatternCount);

		pattern = vmdrawPatterns + vmdrawPatternCount - 1;
		vmdrawCopyPattern(&_editingPattern, pattern);

		vlistSetRowCount(vlistviewGetList(_patternList),
				 vmdrawPatternCount);
		vlistSetCellValue(vlistviewGetList(_patternList),
				  vmdrawPatternCount - 1, 0, NULL);
		vlistSelectRow(vlistviewGetList(_patterList),
			       vlistviewGetSelection(_patternList),
			       vmdrawPatternCount - 1);
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


/* * * * * * * * Primary Pattern Window Functions * * * * * * * */

/*
 * vmdrawCreatePatternWindow
 *
 * Load up and initialize the Pattern window
 */
void vmdrawCreatePatternWindow()
{
    vlist		*listData;
    vmenu		*menu;
    vdropsite		*drop;

    if (vmdrawPatternWindow != NULL) {
        if (!vdialogIsOpen(vmdrawPatternWindow))
            vdialogOpen(vmdrawPatternWindow);
	vwindowRaise((vwindow *) vmdrawPatternWindow);
        return;
    }

    vmdrawPatternWindow =
	vmdrawLoadDialog(vnameInternGlobalLiteral("Patterns"));

    _patternList    = (vlistview *)
        vdialogFindItem(vmdrawPatternWindow, vnameInternGlobalLiteral("PatList"));
    _currentPatternItem    = 
        vdialogFindItem(vmdrawPatternWindow, vnameInternGlobalLiteral("Pattern"));
    _patternItem    = 
        vdialogFindItem(vmdrawPatternWindow, vnameInternGlobalLiteral("EditPattern"));
    _patEditItem    =
        vdialogFindItem(vmdrawPatternWindow, vnameInternGlobalLiteral("PatEdit"));
    _currentPatternBox =
	vdialogFindItem(vmdrawPatternWindow, vnameInternGlobalLiteral("PatternBox"));
    _patternBox =
	vdialogFindItem(vmdrawPatternWindow, vnameInternGlobalLiteral("EditPatternBox"));
    _colorMenu      = (vcontrol *)
        vdialogFindItem(vmdrawPatternWindow, vnameInternGlobalLiteral("Color"));
    menu	    = vcontrolGetMenu(_colorMenu);

    vlistviewSetSelectNotify(_patternList, 	 _patternListNotify);
    vmenuSetNotify(menu, 			 _setColor);

    vdialogInvalItem(_patternItem, 0);

    /* install current pattern box dropsite */
    drop = vdropsiteCreateInternal();
    vdropsiteSetData(drop, (void *) _currentPatternBox);
    vdropsiteSetNotify(drop, _vmdrawCurrentPatternBoxDropsiteNoteProc);
    vdialogSetItemDropsite(_currentPatternBox, drop);

    /* install edit pattern box dropsite */
    drop = vdropsiteCreateInternal();
    vdropsiteSetData(drop, (void *) _patternBox);
    vdropsiteSetNotify(drop, _vmdrawEditPatternBoxDropsiteNoteProc);
    vdialogSetItemDropsite(_patternBox, drop);

    /* install pattern list dropsite */
    drop = vdropsiteCreateInternal();
    vdropsiteSetData(drop, (void *) _patternList);
    vdropsiteSetNotify(drop, _vmdrawPatternListDropsiteNoteProc);
    vdialogSetItemDropsite(vlistviewGetItem(_patternList), drop);

    /*
     * Setup the pattern list
     */

    vlistviewSetList(_patternList, listData = vlistCreate());
    vlistviewSetSelection(_patternList, vlistCreateSelection(listData));
    vlistSetSelectMethod(listData, vlistviewGetSelection(_patternList),
			 vlistONE_ONLY_SELECTION);
    vlistSetRowCount(listData, vmdrawPatternCount);
    vlistSetCellValue(listData, vmdrawPatternCount - 1, 0, NULL);

    vmdrawEditPattern(&_editingPattern);

    vdialogMove(vmdrawPatternWindow, 300, 200);

    vdialogOpen(vmdrawPatternWindow);
}

void vmdrawEditPattern(
    vmdrawPattern	*pattern
    )
{
    if (pattern != &_editingPattern)
	vmdrawCopyPattern(pattern, &_editingPattern);

    vdialogInvalItem(_patternItem, 0);
    vdialogInvalItem(_patEditItem, 0);
}

vmdrawPattern *vmdrawLoadPatterns(
    vresource		resource,
    int			*patternCount
    )
{
    vresource           patternres, entryRes;
    int                 count, i = 0;
    vmdrawPattern       *scan, *patterns;

    if (!vresourceTestGet(resource, vnameInternGlobalLiteral("Pattern Set"), &patternres))
        return(NULL);

    *patternCount = count = vresourceCountComponents(patternres);

    scan = patterns = (vmdrawPattern *) vmemAlloc(sizeof(vmdrawPattern) * count);

    while (count-- > 0) {
	  
        entryRes = vresourceGetAt(patternres, i);

        vmdrawLoadPattern(entryRes, scan);
        i++;
        scan++;
    }

    return(patterns);
}

/*
 * vmdrawLoadPattern
 *
 * Load an individual pattern
 */
void vmdrawLoadPattern(
    vresource           resource,
    vmdrawPattern       *pattern
    )
{
    vresource           patRes;
    vbool		b;

    /* Pattern */

    patRes = vresourceGet(resource,
                          vnameInternGlobalLiteral("Pattern"));
    pattern->image = vimageLoad(patRes);
        
    /* Transparent? */

    if (vresourceTestGetBoolean(resource, vname_Transparency, &b))
	pattern->transparent = TRUE;
    else 
	pattern->transparent = FALSE;
}

void vmdrawSavePatterns(
    vresource		resource,
    vmdrawPattern	*patterns,
    int			count
    )
{
    vresource           patternres, entryRes;
    int                 i = 0;

    patternres = vresourceCreateArray
      (resource, vnameInternGlobalLiteral("Pattern Set"), vresourceDICT, count);

    while (count-- > 0) {
	  
        entryRes = vresourceCreateAt(patternres, i, vresourceDICT);
        
        vmdrawStorePattern(entryRes, patterns);
        i++;
        patterns++;
    }
}

/*
 * vmdrawStorePattern
 *
 * Store an individual pattern
 */
void vmdrawStorePattern(
    vresource		resource,
    vmdrawPattern	*pattern
    )
{       
    vimageStore(pattern->image, vresourceMake(resource, 
				      vnameInternGlobalLiteral("Pattern")));

    if (pattern->transparent)
	vresourceSetBoolean(resource, vname_Transparency, TRUE);
    else
	vresourceRemoveIfExists(resource, vname_Transparency);
}

/*
 * vmdrawCopyPattern
 */
void vmdrawCopyPattern(
    vmdrawPattern	*pattern,
    vmdrawPattern	*target
    )
{
    vimageDestroy(target->image);

    target->image       = vimageClone(pattern->image);
    target->transparent = pattern->transparent;
}

/*
 * vmdrawCopyInitPattern
 */
void vmdrawCopyInitPattern(
    vmdrawPattern	*pattern,
    vmdrawPattern	*target
    )
{
    target->image       = vimageClone(pattern->image);
    target->transparent = pattern->transparent;
}

/*
 * vmdrawDestroyPattern
 */
void vmdrawDestroyPattern(
    vmdrawPattern	*pattern
    )
{
    vimageDestroy(pattern->image);
}

/*
 * vmdrawPatternFillRect
 * 
 * Fill the rectangle with the givenn pattern
 */
void vmdrawPatternFillRect(
    vmdrawPattern	*pattern,
    const vrect		*r,
    vdrawcontext	*context
    )
{ 
    vrect	imageRect;

    if (pattern->transparent)
	return;

    vrectSet(0, 0, r->w, r->h, &imageRect);

    vdrawcontextDrawImageTiled(context, pattern->image, &imageRect, r);
}

/*
 * vmdrawCreatePatternImage
 *
 * Create a new image for using in a pattern.  The image contains
 * the "preset" palette of colors.
 */
vimage *vmdrawCreatePatternImage()
{
    vimage		*image;

    image = vimageCreate();

    vimageSetPalette(image, vmdrawPalette);

    return(image);
}

/* * * * * * * * * * * Dialog Item Methods * * * * * * * */

/*
 * _vmdrawPatternItemDrawWith
 *
 * Draw a pattern dialog item - this dialog item is simply filled with
 * the current pattern or the editing pattern
 */
static void _vmdrawPatternItemDrawWith(
    vdialogItem		*item,
    vdrawcontext	*context
    )
{
    const vrect         *r;

    vclassSendSuper(defaultPatternClass, vdialogDRAW_ITEM_WITH,
		    (item, context));

    r = vdialogGetItemRect(item);

    vmdrawPushPopPen(TRUE, context);
    if (item == _currentPatternItem)
    	vmdrawPatternFillRect(&vmdrawCurrentPattern, r, context);
    else
    	vmdrawPatternFillRect(&_editingPattern, r, context);
    vmdrawPushPopPen(FALSE, context);
}

/*
 * _vmdrawPatEditItemDrawnWith
 *
 * Draw the pattern editor item.  This an 8x8 fat bits view of the
 * image of the pattern.
 */
static void _vmdrawPatEditItemDrawWith(
    vdialogItem		*item,
    vdrawcontext	*context
    )
{
    vdrawpen		*pen = vdrawcontextGetPen(context);
    const vrect         *r;
    vrect		box, origBox;
    int			i, j;
    vpixmap		*map;
    vpixmapScanner	scan;
    vpixmapValue	value;
    vcolorPalette	*palette;
    vcolor		*color, *saveColor;

    vclassSendSuper(defaultPatEditClass, vdialogDRAW_ITEM_WITH,
		    (item, context));

    r   	= vdialogGetItemRect(item);
    map 	= vimageGetMap(_editingPattern.image);
    palette	= vimageGetPalette(_editingPattern.image);
    saveColor	= vdrawpenGetColor(pen);

    /*
     * Scan the bits in the pixmap
     */

    vpixmapInitScanner(&scan, map);

    vrectSet(r->x+4, r->y+4, vmdrawBOX_SIZE, vmdrawBOX_SIZE, &origBox);

    for (i=0; i<8; i++) {

        box = origBox;

        for (j=0; j<8;j++) {

	    value = vpixmapReadAt(&scan, j, i);

	    color = vcolorInternSpec(vcolorGetPaletteSpecAt(palette, value));
	    vdrawpenSetColor(pen, color);

	    vdrawcontextFillRectangles(context, &box, 1);
	    vcolorDestroy(color);

            vrectOffset(&box, vmdrawBOX_SIZE + 1, 0, &box);
        }
        
        vrectOffset(&origBox, 0, vmdrawBOX_SIZE + 1, &origBox);
    }

    vdrawpenSetColor(pen, saveColor);
}

/*
 * _vmdrawPatEditButtonDown
 *
 * Handle button-downs in the pattern editing item.  Toggle the clicked
 * on bit from background-to-current color or from color-to-background.
 */
int _vmdrawPatEditButtonDown(
    vdialogItem		*item,
    vevent		*ev
    )
{
    int                 row, col;
    const vrect         *r;
    vrect               box;
    vpixmap		*map;
    vcolorPalette	*palette;
    vpixmapScanner	scan;
    vpixmapValue	value;
    vdrawcontext	*context;
    vcolor		*color;

    /* Compute the row and column */

    r   = vdialogGetItemRect(item);
    row = veventGetPointerY(ev) - r->y;
    col = veventGetPointerX(ev) - r->x;
    
    if (row < 4 || row >= (vmdrawBOX_SIZE + 1) * 8 + 4)
        return(FALSE);
    if (col < 4 || col >= (vmdrawBOX_SIZE + 1) * 8 + 4)
        return(FALSE);

    row = (row - 4) / (vmdrawBOX_SIZE + 1);
    col = (col - 4) / (vmdrawBOX_SIZE + 1);

    map     = vimageGetMap(_editingPattern.image);
    palette = vimageGetPalette(_editingPattern.image);

    vpixmapInitScanner(&scan, map);
    value = vpixmapReadAt(&scan, col, row);
    value = (value == _editingIndex ? 0 : _editingIndex);

    context = vdialogCreateItemDrawcontext(item);

    vrectSet(r->x+4, r->y+4, vmdrawBOX_SIZE, vmdrawBOX_SIZE, &box);
    vrectOffset(&box, (vmdrawBOX_SIZE + 1) * col,
                (vmdrawBOX_SIZE + 1) * row, &box);

    color = vcolorInternSpec(vcolorGetPaletteSpecAt(palette, value));
    vdrawpenSetColor(vdrawcontextGetPen(context), color);
    vcolorDestroy(color);

    vdrawcontextFillRectangles(context, &box, 1);
    vdrawcontextDestroy(context);

    vpixmapWriteAt(&scan, col, row, value);
    vpixmapDestroyScanner(&scan);

    vimageMarkModified(_editingPattern.image);

    vdialogInvalItem(_patternItem, 0);

    return(TRUE);
}

/* * * * * * *  DRAGGABLE LIST ITEM CLASS METHODS   * * * * * * */


/*
 * _vmdrawDragNotifyAction
 */
static void _vmdrawNotifyPatDragAction(
    vdrag       *drag,
    int		 dragAction,
    vevent      *event
    )
{
    vbool		fromList = (vdragGetData(drag) ==
				    (void *) _patternList);
    vbool		remove;

    remove = (fromList && event != NULL && _vmdrawDragListRow > 1 &&
	      (veventGetWindow(event) !=
	       vdialogGetWindow(vmdrawPatternWindow) ||
	       !vrectContainsPoint(vlistviewGetListRect(_patternList),
				   veventGetPointerX(event),
				   veventGetPointerY(event))));

    if (dragAction == vdragACTION_DROP && remove) {
	vmdrawPattern	*pattern;

	pattern = vmdrawPatterns + _vmdrawDragListRow;
	vmdrawPatternCount--;

	vimageDestroy(pattern->image);

	(void) vmemMove(pattern + 1, pattern,
	   sizeof(vmdrawPattern) * (vmdrawPatternCount - _vmdrawDragListRow));

	vmdrawPatterns = (vmdrawPattern *) vmemRealloc(vmdrawPatterns,
			     sizeof(vmdrawPattern) * vmdrawPatternCount);
    	vlistSetRowCount(vlistviewGetList(_patternList), vmdrawPatternCount);
        vlistSetCellValue(vlistviewGetList(_patternList),
			  vmdrawPatternCount - 1, 0, NULL);
    }

    if (dragAction == vdragACTION_DROP ||
	dragAction == vdragACTION_ABORT) {
	vdragDestroyLater(drag);
	if (event != NULL)
	    vdragSetFeedbackCursor(drag, veventGetWindow(event), NULL);
    }
}

/*
 * _vmdrawNotifyPatDragFeedbackWith
 */
static void _vmdrawNotifyPatDragFeedbackWith(
    vdrag		*drag,
    int			 dropAction,
    vevent		*event,
    vrect		*drawRect,
    vdrawcontext	*context
    )
{
    vrect		 r = *drawRect;
    vbool		 fromList = (vdragGetData(drag) ==
				     (void *) _patternList);
    vcursor		*cursor = NULL;

    vmdrawPushPopPen(TRUE, context);
    vdrawpenSetLineWidth(vdrawcontextGetPen(context), 1);
    vdrawcontextDrawRectanglesInside(context, drawRect, 1);

    if (fromList)
	vmdrawPatternFillRect(vmdrawPatterns + _vmdrawDragListRow, &r,
			      context);
    else
	vmdrawPatternFillRect(&_editingPattern, &r, context);

    vmdrawPushPopPen(FALSE, context);

    /*
     * if the mouse isn't over a dropsite which will accept it, and it's not
     * over the list it came from, then this is a place where the user could
     * drop to _remove_ the pattern from the list.
     */
    if (fromList && dropAction == vdragDROP_ACTION_NONE && event != NULL) {
	if (vwindowGetPointerWindow() != vdialogGetWindow(vmdrawPatternWindow))
	    cursor = vlafGetCursor(vlafCURSOR_GOOD_DROP);
	else {
	    int				 x = veventGetPointerX(event);
	    int				 y = veventGetPointerY(event);

	    if (veventGetWindow(event) !=
		vdialogGetWindow(vmdrawPatternWindow))
		vwindowTransformPoint(veventGetWindow(event),
				      vdialogGetWindow(vmdrawPatternWindow),
				      x, y, &x, &y);
	    if (!vrectContainsPoint(vlistviewGetListRect(_patternList), x, y))
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

static vdragClass *_vmdrawGetPatListDragClass(
    void
    )
{
    if (_vmdrawPatListDragClass == NULL) {
	vdragClass			*clas;

	clas = vclassReproduce(vdragGetDefaultClass());
	vclassSetNameScribed(clas, vcharScribeLiteral("_vmdrawPatListDrag"));
	vclassSet(clas, vdragNOTIFY_ACTION, _vmdrawNotifyPatDragAction);
	vclassSet(clas, vdragNOTIFY_FEEDBACK_WITH,
		  _vmdrawNotifyPatDragFeedbackWith);
	_vmdrawPatListDragClass = clas;
    }

    return _vmdrawPatListDragClass;
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

    return (vclassSendSuper(defaultPatListViewClass,
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

            drag = vdragCreateOfClass(_vmdrawGetPatListDragClass());
            vdragSetData(drag, view);

            vlistviewMapPointToCell(view, pt, &_vmdrawDragListRow, &col);

            vlistviewGetCellRect(view, _vmdrawDragListRow, col, &r);

            vdragSetMaxSize(drag, r.w, r.h);
	    vdragSetOffset(drag, pt->x - r.x, pt->y - r.y);

            vdragStart(drag, event);
        }
        return(TRUE);
    }

    return(vclassSendSuper(defaultPatListViewClass, vdialogHANDLE_ITEM_DRAG,
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

    vclassSendSuper(defaultPatListViewClass, vobjectDESTROY, (view));
}

/*
 * _vmdrawDrawPatternCellWith
 *
 * Draw a cell in the pattern list
 */
static void _vmdrawDrawPatternCellWith(
    vlistview		*listItem,
    int			row,
    int			col, 
    int			selected,
    vrect		*r,
    vdrawcontext	*context
    )
{
    vrect		box;

    vmdrawPushPopPen(TRUE, context);
    vrectInset(r, 3, 3, &box);

    if (row == 0)		/* No Pattern Cell */
	vdrawcontextDrawStringCenterScribed(context,
					    vcharScribeLiteral("No Pattern"),
					    r);
     else
	vmdrawPatternFillRect(vmdrawPatterns + row, &box, context);

    vmdrawPushPopPen(FALSE, context);
}

/*
 * _vmdrawHandlePatButtonDown
 */
int _vmdrawHandlePatButtonDown(
    vdialogItem	*item,
    vevent      *event
    )
{
    const vrect		*r;
    vpoint		*pt;

    _vmdrawDragging = FALSE;
    
    if (item != _currentPatternItem) {

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

    return (vclassSendSuper(defaultPatternClass,
                            vdialogHANDLE_ITEM_BUTTON_DOWN, 
                            (item, event)));
}

/*
 * _vmdrawHandlePatDrag
 */
int _vmdrawHandlePatDrag(
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

            drag = vdragCreateOfClass(_vmdrawGetPatListDragClass());
            vdragSetData(drag, item);

	    r = vdialogGetItemRect(item);
            vdragSetMaxSize(drag, r->w, r->h);
	    vdragSetOffset(drag, pt->x - r->x, pt->y - r->y);

            vdragStart(drag, event);
        }
        return(TRUE);
    }

    return(vclassSendSuper(defaultPatternClass, vdialogHANDLE_ITEM_DRAG,
                           (item, event)));
}

/*
 * _vmdrawHandlePatButtonUp
 */
int _vmdrawHandlePatButtonUp(
    vdialogItem	*item,
    vevent      *event
    )
{
    if (veventGetBinding(event) == vname_Adjust)
        veventSetBinding(event, vname_Drag);

    else if (_vmdrawDragging)
        return(TRUE);

    return (vclassSendSuper(defaultPatternClass,
                            vdialogHANDLE_ITEM_BUTTON_UP,
                            (item, event)));
}

/* * * * * *   STARTUP AND SHUTDOWN * * * * * */

/*
 * _vmdrawPatternShutdown
 *
 * Cleanup after the Pattern window
 */
static void _vmdrawPatternShutdown(void)
{
    vclassDestroy(defaultPatternClass);
    vclassDestroy(defaultPatEditClass);

    vmdrawDestroyPattern(&_editingPattern);
}

/*
 * vmdrawPatternStartup
 *
 * One-time setup for the Pattern window
 */
void vmdrawPatternStartup()
{
    /*
     * Setup the pat edit dialog item class
     */

    defaultPatEditClass = vclassReproduce(vdialogGetBoxItemClass());
	
    vclassSetNameScribed(defaultPatEditClass,
                         vcharScribeLiteral("vmdrawPatEditItem"));

    vclassSet(defaultPatEditClass,
	      vdialogDRAW_ITEM_WITH,   		_vmdrawPatEditItemDrawWith);
    vclassSet(defaultPatEditClass,
	      vdialogHANDLE_ITEM_BUTTON_DOWN,	_vmdrawPatEditButtonDown);

    /*
     * Setup the pattern dialog item class
     */

    defaultPatternClass = vclassReproduce(vdialogGetDefaultItemClass());
	
    vclassSetNameScribed(defaultPatternClass,
                         vcharScribeLiteral("vmdrawPatternItem"));

    vclassSet(defaultPatternClass,
	      vdialogDRAW_ITEM_WITH,   		_vmdrawPatternItemDrawWith);
    vclassSet(defaultPatternClass,
              vdialogHANDLE_ITEM_BUTTON_DOWN,   _vmdrawHandlePatButtonDown);
    vclassSet(defaultPatternClass,
              vdialogHANDLE_ITEM_DRAG,          _vmdrawHandlePatDrag);
    vclassSet(defaultPatternClass,
              vdialogHANDLE_ITEM_BUTTON_UP,     _vmdrawHandlePatButtonUp);


    /*
     * Create the default draggable list item class & keyitem class
     */

    defaultPatListViewClass = vclassReproduce(vlistviewGetDefaultClass());

    vclassSetNameScribed(defaultPatListViewClass,
                         vcharScribeLiteral("vmdrawPatternListView"));

    vclassSet(defaultPatListViewClass,
              vdialogHANDLE_ITEM_BUTTON_DOWN,     _vmdrawHandleListButtonDown);
    vclassSet(defaultPatListViewClass,
              vdialogHANDLE_ITEM_DRAG,            _vmdrawHandleListDrag);
    vclassSet(defaultPatListViewClass,
              vobjectDESTROY,		        _vmdrawDestroyList);
    vclassSet(defaultPatListViewClass,
	      vlistviewDRAW_CELL_CONTENTS_WITH,	  _vmdrawDrawPatternCellWith);

    _editingPattern.image = vmdrawCreatePatternImage();
    vmdrawCopyPattern(vmdrawPatterns + 1, &_editingPattern);

    vclientRegisterShutdown(_vmdrawPatternShutdown);
}



/* $Id: text.c,v 1.6 1997/10/23 21:39:43 gregt Exp $ */

/************************************************************

    text.c
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

#ifndef  vexINCLUDED
#include vexHEADER
#endif

#ifndef  vfixedINCLUDED
#include vfixedHEADER
#endif

#ifndef  vrectINCLUDED
#include vrectHEADER
#endif

#ifndef  vcharINCLUDED
#include vcharHEADER
#endif

#ifndef  vnameINCLUDED
#include vnameHEADER
#endif

#ifndef  vclassINCLUDED
#include vclassHEADER
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

#ifndef  vstylechsrINCLUDED
#include vstylechsrHEADER
#endif

#include "micdraw.h"

static vtextviewClass		*defaultFloatTextViewClass;
static vtextviewClass		*defaultEditTextViewClass;
static vtextClass		*defaultTextClass;

/*
 * vmdrawCreateTextObject
 *
 * Create a new text data object - set up the default ruler and style
 */
void vmdrawCreateTextObject(
    vmdrawObjectData	*objectData
    )
{
    vtextRuler	*ruler;
    vtextStyle	*style;
    vfont		*font;
	
    objectData->text = vtextCreateOfClass(defaultTextClass);

    font  = vfontFindScribed(vcharScribeLiteral("family:helvetica-face:medium-size:12"));
    style = vtextCreateStyle();
    vtextSetDefaultStyleOwned(objectData->text, style);
    vtextSetStyleFont(objectData->text, style, font, TRUE);

    ruler = vtextCreateRuler();
    vtextSetRulerAutoCalc(objectData->text, ruler, TRUE);
    vtextInstallRulerOwned(objectData->text, ruler);
    vtextSetDefaultRuler(objectData->text, ruler);

    vtextCalculate(objectData->text);
}

/*
 * vmdrawCreateFloatTextView
 */
vtextview *vmdrawCreateFloatTextView()
{
    return(vtextviewCreateOfClass(defaultFloatTextViewClass));
}

/*
 * vmdrawPositionEditTextView
 *
 * Position the edit text view such that is exactly overlaps the text object
 */
void vmdrawPositionEditTextView(
    vmdrawDocument 	        *data,
    vdomainObject               *object
    )
{
    vrect                       r;

    /*
     * Account for the joints
     */

    vrectInset(vdomainGetObjectBounds
	       (vdomainviewGetDomain(data->domainView), object),
               (2*vmdrawJOINT_SIZE), (2*vmdrawJOINT_SIZE), &r);

    /*
     * Move the editing text view to the objects position
     */

    vdomainviewTranslateRect(data->domainView, &r, vdomainviewTO_DIALOG);
    vdialogSetItemRect(vtextviewGetItem(data->editTextView), &r);
}

/*
 * vmdrawEnableEditing
 * 
 * Enable editing for text object represented by the domain object 'object'.
 * the "editingObject' field of the document is set, and the editing text
 * view is moved into place and shown.
 */
void vmdrawEnableEditing(
    vmdrawDocument 	        *data,
    vdomainObject               *object
    )
{
    vmdrawObjectData            *objectData;
    vdomain                     *domain;

    domain     = vdomainviewGetDomain(data->domainView);
    objectData = (vmdrawObjectData *) vdomainGetObjectData(domain, object);

    data->editingObject = object;

    /*
     * Disengage the editing text view from old text data object 
     */
    vtextviewSetTextData(data->editTextView, NULL);

    /*
     * Set the editing text view to view the text data object for the object
     * First set the selection, then the text data
     */

    vtextviewSetSelection(data->editTextView, 
                          vtextCreateSelection(objectData->text));
    vtextviewSetTextData(data->editTextView, objectData->text);

    /*	
     * The editing text view may have been scrolled from a previous edit.
     * Make sure it's at the top of the text.
     */

    vtextviewScroll(data->editTextView, 0, 0);

    /*	
     * Position the edit text view
     */

    vmdrawPositionEditTextView(data, object);

    /*	
     * Enable and show the editing text view, and focus the item
     */
      
    vdialogEnableItem(vtextviewGetItem(data->editTextView));
    vdialogShowItem(vtextviewGetItem(data->editTextView));
    vdialogSetItemListFocus(vdialogGetItemItemList
	(vtextviewGetItem(data->editTextView)),
	 vtextviewGetItem(data->editTextView));

    /*
     * Select the beggining of the text
     */

    vtextSelectRange(vtextviewGetTextData(data->editTextView),
		     vtextviewGetSelection(data->editTextView), 0, 0);

    vdomainviewInvalObjects(data->domainView, vdomainObjectToSet(object), 0);

    /*
     * Enable "Apply Style" commands
     */

    vmdrawChangeDocumentState(data, vnameInternGlobalLiteral("Apply Style"),
			      NULL);
#if  (mdrawUSE_DAS)
    if (data->observerSessionText != NULL)
	vtextInstallObserver(objectData->text, data->observerSessionText);
#endif
}

/*
 * vmdrawDisableEditing 
 * 
 * Disabled editing of a text object.  Disabled and hide the editing text
 * view, and, reset the palette to the arrow palette entry if the palette
 * is not locked.
 */
void vmdrawDisableEditing(
    vmdrawDocument 	        *data,
    vbool			adjustPalette
    )
{
    if (data->editingObject != NULL) {
#if  (mdrawUSE_DAS)
	if (data->observerSessionText != NULL) {
	    vmdrawObjectData	*objectData;

	    objectData = (vmdrawObjectData *)
			vdomainGetObjectData(
					vdomainviewGetDomain(data->domainView),
					data->editingObject);
	    /**  !!! this function gets called twice sometimes (always?)
	     **  !!! and observer may not be registered.  I'm not sure if
	     **  !!! it is ok to just check the adjustPalette flag or what.
	     **/
	    vexWITH_HANDLING {
		vtextUninstallObserver(objectData->text,
				       data->observerSessionText);
	    }
	    vexON_EXCEPTION;
	    vexEND_HANDLING;
	}
#endif

	vdialogDisableItem(vtextviewGetItem(data->editTextView));
	vdialogHideItem(vtextviewGetItem(data->editTextView));

	vdomainviewInvalObjects(data->domainView,
			    vdomainObjectToSet(data->editingObject), 0);

	if (data->lockedCell == -1 && adjustPalette)
            vpaletteSetSelection(data->palette, 
                                 vpaletteFindItem(data->palette, 
				       vnameInternGlobalLiteral("Arrow")));
 
	data->editingObject = NULL;

	/*
	 * Disable "Apply Style" commands
	 */

	vmdrawChangeDocumentState(data,
				vnameInternGlobalLiteral("Apply Style"), NULL);
    }
}

/* * * * * * * * * Text Class Methods * * * * * * */

/*
 * vmdrawAutoCalcRuler
 *
 * Handle wrapping to the edge of the view
 */
static void _vmdrawAutoCalcRuler(
    vtext		*editRec,
    vtextRuler		*ruler
    )
{
    vdomainObject       *object;
    vfixed		 rightIndent;
    vrect		*r;

    object = (vdomainObject *) vtextGetData(editRec);

    if (object == NULL)
        return;
    
    r 		= vdomainGetObjectBounds(NULL, object);
    rightIndent = vfixedFromInt(r->w - (4*vmdrawJOINT_SIZE));

    vtextSetRulerWrap(editRec, ruler, TRUE);
    vtextSetRulerRightIndent(editRec, ruler, rightIndent);
}

/*
 * vmdrawApplyStyle
 *
 * Apply routine for the style chooser.  Apply the style to the editing
 * text view of the Target document.
 */
int vmdrawApplyStyle(
    vstylechsr   *styleChsrer, 
    vtextStyle   *newStyle
    )
{
    vtextStyle		*style;
    vtext		*editRec;

    if (vmdrawTargetDocument->editingObject == NULL)
	return(TRUE);

    editRec   = vtextviewGetTextData(vmdrawTargetDocument->editTextView);

    style = vtextCreateStyle();
    vtextCopyStyle(newStyle, style);
    vtextInstallStyleOwned(editRec, style);
    vtextApplyStyle(editRec,
		    vtextviewGetSelection(vmdrawTargetDocument->editTextView),
		    style);

    return(TRUE);
}

/*
 * vmdrawApplyJustification
 *
 * Apply the justification to all selected text objects in the target 
 * document.
 */
void vmdrawApplyJustification(
    const vname		*name
    )
{
    vtextRuler			*ruler;
    vdomain			*domain;
    vdomainObject		*scan;
    vdomainSelection		selection;
    vmdrawObjectData		*objectData;

    domain    = vdomainviewGetDomain(vmdrawTargetDocument->domainView);
    selection = vdomainviewGetSelection(vmdrawTargetDocument->domainView);
    scan      = vdomainTopObject(domain);

    while (scan != NULL) {

	/*
	 * Is the object a text object and is it selected?
	 */

	if (vdomainGetObjectType(domain, scan) == vmdrawTEXT_TOOL &&
	    vdomainIsObjectSelected(domain, selection, scan)) {

	    /*
	     * Extract the default ruler and set it's justification
	     * attribute
	     */

	    objectData  = (vmdrawObjectData *)	
		vdomainGetObjectData(domain, scan);
	    ruler = vtextGetDefaultRuler(objectData->text);
	    vtextSetRulerAttribute(ruler, vtext_Justification, name);
	    vdomainviewInvalObjects(vmdrawTargetDocument->domainView,
				    vdomainObjectToSet(scan), 0);

	    /*	
	     * Since the ruler is an autocalc ruler, we need to force the
	     * recalculation.
	     */

	    vtextCalculate(objectData->text); 
	}
	
	scan = vdomainNextObjectBehind(scan);
    }
}

/* * * * * * * * * Float & Edit Text View Class Methods * * * * * * */

/*
 * _vmdrawDrawFloatBackgroundWith
 *
 * Draw the background of text objects with their patterns.
 */
static void _vmdrawDrawFloatBackgroundWith(
    vtextview		*textView,
    vrect		*r,
    vdrawcontext	*context
    )
{	
    vmdrawObjectData	*objectData;

    objectData = (vmdrawObjectData *) vtextviewGetData(textView);

    vmdrawPatternFillRect(&objectData->pattern, r, context);
}

/*
 * _vmdrawDrawEditView
 *
 * Clip to the domain view that contains the text object before drawing
 * the editing text view.
 */
static void _vmdrawDrawEditViewWith(
    vtextview		*textView,
    vdrawcontext	*context
    )
{	
    vmdrawDocument		*data;
    vrect			r;

    data = (vmdrawDocument *) vtextviewGetData(textView);
    r    = *vdomainviewGetViewArea(data->domainView);
    vdomainviewTranslateRect(data->domainView, &r, vdomainviewTO_DIALOG);

    vdrawcontextClipRectangles(context, &r, 1);

    vclassSendSuper(defaultEditTextViewClass, vdialogDRAW_ITEM_WITH,
		    (textView, context));
}

/*
 * _vmdrawDrawCaret
 *
 * Clip to the domain view that contains the text object before drawing
 * the cursor.
 */
static void _vmdrawDrawCaretWith(
    vtextview		*textView,
    vrect		*caretRect,
    vdrawcontext	*context
    )
{	
    vmdrawDocument		*data;
    vrect			r;

    data = (vmdrawDocument *) vtextviewGetData(textView);
    r    = *vdomainviewGetViewArea(data->domainView);
    vdomainviewTranslateRect(data->domainView, &r, vdomainviewTO_DIALOG);

    vdrawcontextClipRectangles(context, &r, 1);

    vclassSendSuper(defaultEditTextViewClass, vtextviewDRAW_CARET_WITH,
		    (textView, caretRect, context));
}

/* * * * * *   STARTUP AND SHUTDOWN * * * * * */

/*
 * vmdrawTextStartup
 *
 * Initialize the text classes
 */
void vmdrawTextStartup()
{
    /* 
     * Create the float text view class - handle background pattern drawing
     */

    defaultFloatTextViewClass = vclassReproduce(vtextviewGetDefaultClass());

    vclassSetNameScribed(defaultFloatTextViewClass,
                         vcharScribeLiteral("vmdrawFloatTextViewClass"));

    vclassSet(defaultFloatTextViewClass,
	      vtextviewDRAW_BACKGROUND_WITH,   _vmdrawDrawFloatBackgroundWith);

    /* 
     * Create the edit text view class - clip when drawing to domain view
     */

    defaultEditTextViewClass = vclassReproduce(vtextviewGetDefaultClass());

    vclassSetNameScribed(defaultEditTextViewClass,
                         vcharScribeLiteral("vmdrawEditTextView"));

    vclassSet(defaultEditTextViewClass,
	      vdialogDRAW_ITEM_WITH,		_vmdrawDrawEditViewWith);
    vclassSet(defaultEditTextViewClass,
	      vtextviewDRAW_CARET_WITH,		_vmdrawDrawCaretWith);

    /*
     * Set up the text class
     */

    defaultTextClass = vclassReproduce(vtextGetDefaultClass());
    
    vclassSetNameScribed(defaultTextClass,
			 vcharScribeLiteral("vmdrawText"));
			 
    vclassSet(defaultTextClass, vtextCALC_RULER, _vmdrawAutoCalcRuler);
}


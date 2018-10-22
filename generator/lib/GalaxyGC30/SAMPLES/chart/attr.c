/* $Id: attr.c,v 1.2 1993/11/30 19:33:44 markd Exp $ */
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

/* attr.c -- Implementation for an attribute-notification dialog
 *
 * Module:
 *	xattribute
 *
 * Docs and description are in xattr.h
 *
 * See file chart.c for more comments about this whole project.
 */

#ifndef  vportINCLUDED
#include <vport.h>		/* for v*HEADER */
#endif

#ifndef  vapplicationINCLUDED
#include vapplicationHEADER
#endif

#ifndef  vclientINCLUDED
#include vclientHEADER
#endif

#ifndef  vcontrolINCLUDED
#include vcontrolHEADER
#endif

#ifndef  vdialogINCLUDED
#include vdialogHEADER
#endif

#ifndef  vdictINCLUDED
#include vdictHEADER
#endif

#ifndef  veventINCLUDED
#include veventHEADER
#endif

#ifndef  vnumINCLUDED
#include vnumHEADER
#endif

#ifndef  vpoolINCLUDED
#include vpoolHEADER
#endif

#ifndef  vresourceINCLUDED
#include vresourceHEADER
#endif

#ifndef  vsliderINCLUDED
#include vsliderHEADER
#endif

#include "xcolspot.h"
#include "xattr.h"

/* How it works:
 * -------------
 * Clients register interest in a particular attribute by name.  
 * e.g. "Line Width", "Point Color".  Whenever that particular attribute
 * changes via the attribute dialog, all of the clients are notified.
 *
 * The atribute names are identical to the tags of the dialog items that
 * control that attribute.  When the dialog item changes state, all 
 * clients registered under that tag name are called, along with interesting
 * information.
 */




/* The attribute dialog */
static vdialog *dialog = NULL;


/* the place where client interest is stored.  This is used to map the
 * attribute name/tag name to the a set of records that has the information
 * to call them with */
static vdict *dispatch = NULL;


/* there is one of these for each client-attribute interest */
typedef struct interestRecord {
    const void		  *data;   /* client-useful info   */
    xattributeNoteProc     notify; /* the function to call */
    struct interestRecord *NeXT;   /* if multiple clients are interested in */
} interestRecord;		   /* the same attribute                    */


/* where the dictionary entries for the clients come from */
static vpool *interestPool = NULL;


/* the attribute names available */
const vname *xattr_Line_Width = NULL;
const vname *xattr_Line_6_Color = NULL;
const vname *xattr_Line_5_Color = NULL;
const vname *xattr_Line_4_Color = NULL;
const vname *xattr_Line_3_Color = NULL;
const vname *xattr_Line_2_Color = NULL;
const vname *xattr_Line_1_Color = NULL;
const vname *xattr_Label_Color = NULL;
const vname *xattr_Point_Color = NULL;
const vname *xattr_Big_and_Scrolling = NULL;
const vname *xattr_Big_and_Scrolling_Scatter = NULL;
const vname *xattr_Dashed_Lines = NULL;
const vname *xattr_Point_Images = NULL;
const vname *xattr_Custom_Point_Image = NULL;




/*
 * ----- Attribute registration and notification
 */


/* xattributeRegisterInterest -- tells this module that someone wants to be
 *			         called when an attribute changes.
 *
 *  -> atributeName -- the name of the attribute they're interested in.
 *  -> data	    -- a piece of data meaningful to the client.  This will
 *		       passed back when the client is notified.
 *  -> notify	    -- the code to call when the attribute changes
 */
void xattributeRegisterInterest (const vname *attributeName,
				 const void  *data,
				 xattributeNoteProc notify)
{
    interestRecord *record;
    interestRecord *oldRecord = NULL;

    oldRecord = (interestRecord*)vdictLoad (dispatch, attributeName);

    record = vpoolAlloc (interestPool);
    record->data = data;
    record->notify = notify;
    record->NeXT = oldRecord;

    vdictStore (dispatch, attributeName, record);

} /* xattributeRegisterInterest */




/* _xattributeDispatch -- tell all clients interested in this attribute
 *			  that it has changed.
 *
 *  -> attributeName -- the attribute that changed
 *  -> value	     -- the new value.  The client knows that a particular
 *			returns a particular value, so they'll know how to
 *			cast this
 */
static void _xattributeDispatch (const vname *attributeName,
				 const void *value)
{
    interestRecord *record;

    record = (interestRecord*)vdictLoad (dispatch, attributeName);

    while (record != NULL) {
	if (record->notify != NULL) {
	    (record->notify)(record->data, attributeName, value);
	}
	record = record->NeXT;
    }
} /* _xattributeDispatch */




/* xattributeRefreshEverybody -- go through all of the attributes and tell
 *				 all of the clients the current value.
 */
void xattributeRefreshEverybody (void)
{
    int i, scratch;
    vdialogItem *item;

    /* walkin' the dialog! walkin' the dialog!  that's cool.  */
    for (i = 0; i < vdialogGetItemCount(dialog); i++) {
	item = vdialogGetItemAt (dialog, i);
	
	if (vclassIsKindOf(vdialogGetItemClass(item),
			   vsliderGetDefaultClass())) {
	    scratch = vcontrolGetValue ((vcontrol*)item),

	    _xattributeDispatch (vdialogGetItemTag(item), &scratch);

	} else if (vclassIsKindOf (vdialogGetItemClass(item),
				   vcontrolGetToggleClass())) {

	    if (vcontrolGetValue((vcontrol*)item)) {
		_xattributeDispatch (vdialogGetItemTag(item), vname_On);
	    } else {
		_xattributeDispatch (vdialogGetItemTag(item), vname_Off);
	    }

	} else if (vclassIsKindOf (vdialogGetItemClass(item),
				   xcolorspotGetDefaultClass())) {
	    _xattributeDispatch (vdialogGetItemTag(item),
				 vdialogDetermineItemBackground(item));
	}
    }
} /* xattributeRefreshEverybody */




/*
 * ----- Dialog-item notifies
 */


/* _xattributeSliderNotify -- notification function for any sliders in
 *			      the attribute dialog.  It notifies clients
 *			      of the change.
 *
 *  -> slider -- the slider that had a change of value
 *  -> event  -- the event that caused it
 *
 * If the slider has anything under the data pointer, it's assumed to be
 * dialog item.  This item's title will be set to the value of the slider.
 * Handy for automagic association between a slider and a textitem.
 */
static void _xattributeSliderNotify (vcontrol *slider, vevent *event)
{
    vdialogItem *item;
    int value;

    item = (vdialogItem*) vcontrolGetData (slider);

    value = vcontrolGetValue (slider);

    if (item != NULL) {
	vdialogSetItemTitleScribed (item, vnumScribeInt(value));
    }
    
    _xattributeDispatch (vdialogGetItemTag(vcontrolGetItem(slider)), &value);
    
} /* _xattributeSliderNotify */




/* _xattributeCheckboxNotify -- notification function for any checkboxes
 *				in the attribute dialog.  It notifies clients
 *				of the change.
 *
 *  -> checkbox -- the checkbox that changed state
 *  -> event    -- the event that diddit.
 */
static void _xattributeCheckboxNotify (vcontrol *checkbox, vevent *event)
{
    _xattributeDispatch (vdialogGetItemTag(vcontrolGetItem(checkbox)),
			 (vcontrolGetValue(checkbox)) ? vname_On : vname_Off);
} /* _xattributeCheckboxNotify */




/* _xattributeCheckboxNotify -- notification function for any color spots
 *				in the attribute dialog.  It notifies clients
 *				of the change.
 *
 *  -> checkbox -- the checkbox that changed state
 *  -> event    -- the event that diddit.  (actually a vcolor, but it's
 *		   to be ignored anyway.
 */
static void _xattributeColorspotNotify (vdialogItem *item, vevent *event)
{
    _xattributeDispatch (vdialogGetItemTag(item),
			 vdialogDetermineItemBackground(item));
} /* _xattributeColorspotNotify */




/*
 * ----- Attribute Dialog stuff
 */


/* _setupContents -- walks the dialog attaching notification functions 
 *		     to the appropriate items.
 *
 *  -> dialog - -the dialog to set up.
 *
 * One cool thing this does is auto-associate a slider and a label item.
 * When a slider is found, a label item with the same tag as the slider
 * is searched for.  If it exists, then it will always have a textual
 * representation of the slider's value. 
 */
static void _setupContents (vdialog *dialog)
{
    int i;
    vdialogItem *item;
    const vname *tag;
    vrect rect;
    
    /* arrange it first-off so that label widths are left wide enuf */
    rect = *vwindowGetRect (vdialogGetWindow(dialog));
    rect.x = rect.y = 0;

    vdialogArrange (dialog, &rect);

    /* now walk the dialog and attach notifies to the appropriate items */
    for (i = 0; i < vdialogGetItemCount(dialog); i++) {
	item = vdialogGetItemAt (dialog, i);
	
	if (vclassIsKindOf(vdialogGetItemClass(item),
			   vsliderGetDefaultClass())) {
	    vdialogItem *label;

	    tag = vdialogGetItemTag(item);

	    /* we want to find a label item with the same tag.  Rather
	     * than relying on empirical evidence of the order that dialog
	     * findItem finds its stuff.  Set the tag the the slider to
	     * be something different.  Doesn't matter what.  Then look
	     * for the (union) label, then restore the slider to its
	     * previous tag.  The words "Galaxy" and "Spam" were chosen
	     * out of not-so-thin air.
	     */

	    if (tag == vname_Galaxy) {
		vdialogSetItemTag (item, vnameInternGlobalLiteral("Spam"));
	    } else {
		vdialogSetItemTag (item, vname_Galaxy);
	    }

	    label = vdialogFindItem (dialog, tag);

	    if (label != NULL) {
		vdialogSetItemData (item, label);
		vdialogSetItemTitleScribed (label,
					    vnumScribeInt
					    (vcontrolGetValue((vcontrol*)item
							      )));
	    }
	    
	    vdialogSetItemTag (item, tag);

	    vcontrolSetNotify ((vcontrol*)item, _xattributeSliderNotify);

	} else if (vclassIsKindOf (vdialogGetItemClass(item),
				   vcontrolGetToggleClass())) {
	    vcontrolSetNotify ((vcontrol*)item, _xattributeCheckboxNotify);

	} else if (vclassIsKindOf (vdialogGetItemClass(item),
				   xcolorspotGetDefaultClass())) {
	    xcolorspotSetNotify (item, _xattributeColorspotNotify);
	}
    }

} /* _setupContents */




/*
 * ----- Command stuff
 */


/* This is kinda overkill for attaching one and only one command to the
 * dialog's command space.  But what the hey, this code already existed
 * and works.
 */


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

	vdictStore (commandDict, 
		    vnameInternGlobalLiteral(commandScan->tagName), 
		    functionCommand);
    }

    vcommandAddSpaceDictOwned (commandSpace, vname_Command, commandDict);
    vwindowSetSpaceOwned (vdialogGetWindow(dialog), commandSpace);
    
} /* _setupCommands */




/*
 * ----- Managerial Duties
 */


/* _xattributeShutdown -- clean up any mess this module made.
 */
static void _xattributeShutdown (void)
{
    vdialogDestroy (dialog);
    vdictDestroy (dispatch);
    vpoolDestroyUnbalanced (interestPool);
} /* _xattributeShutdown */




/* xattributeStartup -- initialize this module and set up exported constants.
 */
void xattributeStartup (void)
{
    (void) xattributeGetAttributeDialog ();

    interestPool = vpoolCreate (sizeof(interestRecord));
    dispatch = vdictCreate (vnameHash);

    xattr_Line_Width = vnameInternGlobalLiteral("Line Width");
    xattr_Line_6_Color = vnameInternGlobalLiteral("Line 6 Color");
    xattr_Line_5_Color = vnameInternGlobalLiteral("Line 5 Color");
    xattr_Line_4_Color = vnameInternGlobalLiteral("Line 4 Color");
    xattr_Line_3_Color = vnameInternGlobalLiteral("Line 3 Color");
    xattr_Line_2_Color = vnameInternGlobalLiteral("Line 2 Color");
    xattr_Line_1_Color = vnameInternGlobalLiteral("Line 1 Color");
    xattr_Label_Color = vnameInternGlobalLiteral("Label Color");
    xattr_Point_Color = vnameInternGlobalLiteral("Point Color");
    xattr_Big_and_Scrolling = vnameInternGlobalLiteral("Big and Scrolling");
    xattr_Big_and_Scrolling_Scatter = (vnameInternGlobalLiteral
				       ("Big and Scrolling Scatter"));
    xattr_Dashed_Lines = vnameInternGlobalLiteral("Dashed Lines");
    xattr_Point_Images = vnameInternGlobalLiteral("Point Images");
    xattr_Custom_Point_Image = vnameInternGlobalLiteral("Custom Point Image");
    
    vclientRegisterShutdown (_xattributeShutdown);

} /* xattributeStartup */




/* xattributeGetAttributeDialog -- return the attribute dialog so that it
 *				   can be positioned and opened.  This dialog
 *				   isn't open by default.
 * <-  -- the attribute dialog.
 */
vdialog *xattributeGetAttributeDialog (void)
{
    if (dialog == NULL) {
	vresource appres, dialogres;

	appres = vapplicationGetResources (vapplicationGetCurrent());
	dialogres = vresourceGet (appres,
				  vnameInternGlobalLiteral("Attributes"));
	dialog = vdialogLoad (dialogres);
	_setupCommands (dialog);
	_setupContents (dialog);
    }

    return (dialog);

} /* xattributeGetAttributeDialog */


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

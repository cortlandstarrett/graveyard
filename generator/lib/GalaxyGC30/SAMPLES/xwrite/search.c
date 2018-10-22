/* $Id: search.c,v 1.1 1994/03/30 23:08:42 dimitri Exp $ */

/************************************************************

    search.c
    C Source to xwrite

    (c) Copyright Visix Software Inc.
    All rights reserved

************************************************************/
 
#include "micwrite.h"

#if vdebugDEBUG
#define vdebugTAG "xwriteSearch"
#endif

enum {
    writeFIND_BUTTON		= 0,
    writeCHANGE_FIND_BUTTON	= 1,
    writeCHANGE_BUTTON		= 2,
    writeCHANGE_ALL_BUTTON	= 3
    };

writeSearchDoc			*writeSearchWindow   = NULL;
short		 		writeSearchOptions   = 0;

static writeDocument		*targetDocument	       		= NULL;
static writeSearchDocClass	*defaultSearchClass    		= NULL;
static vtextObserverClass	*defaultSearchObserverClass 	= NULL;
static vdict		 	defaultFocusCommands;
static vbutton			*searchButtons[4];
static vtextObserver		*searchObserver = NULL;

void writeCreateSearchWindow(void)
{
    vdialog		*dialog;
    vcommandSpace	*space;

    if (writeSearchWindow != NULL) {

        if (!vdialogIsOpen(&writeSearchWindow->dialog))
            vdialogOpen(&writeSearchWindow->dialog);
	vwindowRaise(vdialogGetWindow(&writeSearchWindow->dialog));

        return;
    }

    writeSearchWindow = (writeSearchDoc *) 
	writeLoadDialog(vnameInternGlobalLiteral("Search"));

    dialog = &writeSearchWindow->dialog;
    
    if (wrtDialog != NULL)
	vwindowPlace(vdialogGetWindow(dialog), vdialogGetWindow(wrtDialog),
		     vrectPLACE_LEFT | vrectPLACE_ALIGN,
		     vrectPLACE_BOTTOM | vrectPLACE_NEAR);
    else
	writeCenterWindow(vdialogGetWindow(dialog));

    writeSearchWindow->target = (vtextitem *)
        vdialogFindItem(dialog, vnameInternGlobalLiteral("FindText"));
    writeSearchWindow->replace = (vtextitem *)
        vdialogFindItem(dialog, vnameInternGlobalLiteral("ReplaceText"));

    searchButtons[writeFIND_BUTTON] = (vbutton *) 
	vdialogFindItem(dialog, vnameInternGlobalLiteral("Find Button"));
    searchButtons[writeCHANGE_FIND_BUTTON] = (vbutton *) 
	vdialogFindItem(dialog, vnameInternGlobalLiteral("Change Then Find"));
    searchButtons[writeCHANGE_BUTTON] = (vbutton *) 
	vdialogFindItem(dialog, vnameInternGlobalLiteral("Change"));
    searchButtons[writeCHANGE_ALL_BUTTON] = (vbutton *) 
	vdialogFindItem(dialog, vnameInternGlobalLiteral("Change All"));

    vdialogSetDefFocus(dialog, vtextitemGetItem(writeSearchWindow->target));

    writeBuildWindowMenus();

    /*
     * Add the focus command dictionary to the dialog's command space, so
     * that these command get redirected to the focus item
     */
    
    space = vclassGet(vdialogGetClass(dialog), vobjectSPACE);
    vcommandAddSpaceDict(space, vname_Command, &defaultFocusCommands);
    
    writeChangeDocumentState(NULL, vnameInternGlobalLiteral("Replace Same"), 
			     vname_Enabled);

    writeSetTargetDocument(NULL);

    vdialogOpen(dialog);
}

/*
 * _writeDestroySearch
 *
 * Close the search window
 */
static void _writeDestroySearch(
    writeSearchDoc	*searchData
    )
{
    vclassSendSuper(defaultSearchClass, vobjectDESTROY, (searchData));

    writeSearchWindow = NULL;

    writeBuildWindowMenus();

    writeChangeDocumentState(NULL, vnameInternGlobalLiteral("Replace Same"),
			     vname_Disabled);
}

/*
 * writeSearchDocument
 *
 * Handle all types of searching for document
 */
vbool writeSearchDocument(
    writeDocument	*data,
    vdict		*context
    )
{
    vchar 	        *findText, result[1024];
    const vchar         *target = NULL;
    vtextview           *textView;
    vtextPosition	*position;
    vtext               *targetText;
    long                length, pos = 0;
    int		        method;
    int			resultLength = 0;
    vbool		wrapped = FALSE, backwards;
    static vchar	_lastText[1026];
    static vchar	*_lastSearchText = NULL;
    
    if (context != NULL) {

        if (vdictLoad(context, write_Option) == write_Selection) {
            writeGetSelection(data, 0);
            target = writeSelection;
        }
	else if (vdictLoad(context, write_Option) == write_Again &&
		 _lastSearchText != NULL) {
	    target 		= _lastSearchText;
	}
        else
            target = vdictLoad(context, write_Target);
    }

    targetText = vtextviewGetTextData(data->textItem);

    if (target == NULL) {

        if (writeSearchWindow == NULL)
            return(FALSE);

	textView      = vtextitemGetView(writeSearchWindow->target);
        findText      = vtextGetTextAt(vtextviewGetTextData(textView), 0);
        length        = vtextLength(vtextviewGetTextData(textView));
        findText[length]  = '\0';
    }

    else {
        findText      = (vchar *) target;
        length        = vcharLength(target);
    }

    _lastSearchText = _lastText;
    (void) vcharCopyBounded(findText, _lastText, 1024);

    if (length == 0 || vtextLength(targetText) == 0)
        return(FALSE);
    
    backwards = ((writeSearchOptions & writeBACKWARD_SEARCH) != 0);

    if (vdictLoad(context, vname_Direction) == write_Reverse)
        backwards = !backwards;
        
    if ((writeSearchOptions & writeREGEXP_SEARCH) || 
	(context != NULL && ( vdictLoad(context, write_Regexp) != NULL)))
        method = backwards ? vtextREGEXP_BACKWARD_SEARCH : vtextREGEXP_SEARCH;
    else
        method = backwards ? vtextBACKWARD_SEARCH : vtextFORWARD_SEARCH;
    
    position = vtextGetPosition(vtextviewGetSelection(data->textItem));

    if (backwards)
        pos = position->start;
    else
        pos = position->end;

    if (context != NULL && (vdictLoad(context, write_First) == write_First)) {
	backwards = FALSE;
        pos = 0;
    }

SearchAgain:

    pos = vtextSearch(targetText, pos, findText, result, 1024, method, NULL,
		      (writeSearchOptions & writeCASE_SENSITIVE) != 0);

    if (pos >= 0) {
   
	resultLength = vcharLength(result);
 
	/*
	 * Check for whole word - if the option is enabled
	 */

	if (writeSearchOptions & writeWHOLE_WORD) {
	
	    vchar	*textptr;

	    /* Check start of word */

	    if (pos > 0) {

		textptr = vtextGetTextAt(targetText, pos-1);

		if (!vtextIsWordBreak(targetText, textptr, 1)) {
		    pos = (backwards ? pos : pos + resultLength);
		    goto SearchAgain;
		}
	    }

	    /* Check end of word */

	    if ((pos + resultLength) < vtextLength(targetText)) {

		textptr = vtextGetTextAt(targetText, pos + resultLength);

		if (!vtextIsWordBreak(targetText, textptr, 1)) {
		    pos = (backwards ? pos : pos + resultLength);
		    goto SearchAgain;
		}
	    }
	}
    }

    if (pos >= 0) {

        vtextSelectRange(targetText,
			 vtextviewGetSelection(data->textItem),
                         pos, pos + resultLength); /* length); */
        vtextviewScrollToStart(data->textItem, vtextviewSTS_HORIZONTAL |
                               vtextviewSTS_VERTICAL);
	return(TRUE);
    }

    else if (!wrapped && (writeSearchOptions & writeWRAP_SEARCH)) {

	pos = (backwards ? vtextLength(targetText) : 0);
	wrapped = TRUE;

	goto SearchAgain;
    }

    return(FALSE);
}

/*
 * writeChangeInDocument
 */
void writeChangeInDocument(
    writeDocument	*data,
    vdict		*context
    )
{
    vstr	*str;

    str  = vtextitemGetTextAsString(writeSearchWindow->replace);

    vtextInsert(vtextviewGetTextData(targetDocument->textItem),
		vtextviewGetSelection(targetDocument->textItem),
		str, vcharLength(str));

    vtextviewNotifyUndo(targetDocument->textItem, 
			vcharScribeLiteral("Change"));

    vstrDestroy(str);
}

/*
 * writeChangeAllInDocument
 *
 * Change all occurences in the selection (if there is a selection) or 
 * change all occurences from the current point on
 */
void writeChangeAllInDocument(
    writeDocument	*data,
    vdict		*context
    )
{
    vchar 	        *findText, result[1024];
    vtextview           *textView;
    vtextPosition	position;
    vtext               *targetText;
    long                length, pos;
    int		        method;
    vbool		backwards, changeInSelection;
    
    if (writeSearchWindow == NULL)
	return;

    targetText = vtextviewGetTextData(data->textItem);

    textView      = vtextitemGetView(writeSearchWindow->target);
    findText      = vtextGetTextAt(vtextviewGetTextData(textView), 0);
    length        = vtextLength(vtextviewGetTextData(textView));
    findText[length] = '\0';
    
    if (length == 0)
        return;
    
    backwards = ((writeSearchOptions & writeBACKWARD_SEARCH) != 0);

    if ((writeSearchOptions & writeREGEXP_SEARCH) || 
	(context != NULL && ( vdictLoad(context, write_Regexp) != NULL)))
        method = backwards ? vtextREGEXP_BACKWARD_SEARCH : vtextREGEXP_SEARCH;
    else
        method = backwards ? vtextBACKWARD_SEARCH : vtextFORWARD_SEARCH;
    
    position = *vtextGetPosition(vtextviewGetSelection(data->textItem));

    changeInSelection = (position.start != position.end);

    if (backwards)
        pos = changeInSelection ? position.end : position.start;
    else
        pos = changeInSelection ? position.start : position.end;

    for (;;) {

	pos = vtextSearch(targetText, pos, findText, result, 1024,
			  method, NULL,
			  (writeSearchOptions & writeCASE_SENSITIVE) != 0);
	
	if (pos < 0)
	    break;

        vtextSelectRange(vtextviewGetTextData(data->textItem),
			 vtextviewGetSelection(data->textItem),
                         pos, pos + vcharLength(result)); /* length); */

	writeChangeInDocument(data, NULL);

	if ((writeSearchOptions & writeBACKWARD_SEARCH) == 0)
	    pos = vtextSelectionEnd(vtextviewGetSelection(data->textItem));

	if (changeInSelection) {
	    
	    if (!backwards && pos >= position.end)
		break;
	    else if (backwards && pos <= position.start)
		break;
	}
    }
}

/* * * * * * *   SEARCH OBSERVER    * * * * * */

static void _writeObserverSelect(
    vtextObserver		*observer,
    register vtextSelection     *selection,
    register int                state
    )
{
    vtextPosition	*position;
    static 		lastState = 0;

     if (writeSearchWindow == NULL)
 	return;
 
    if (vtextviewGetSelection(targetDocument->textItem) != selection)
        return;

    position = 
	vtextGetPosition(vtextviewGetSelection(targetDocument->textItem));

    if (state == vtextSELECTION_HAS_CHANGED) {
	
       if (position->length == 0) {
	  if (lastState)
	     vbuttonSetTitle(searchButtons[writeCHANGE_ALL_BUTTON],
			     write_ChangeAll);
       }

       else {
	  if (lastState == 0)
	     vbuttonSetTitle(searchButtons[writeCHANGE_ALL_BUTTON],
			     write_ChangeSelection);
       }
       
       lastState = position->length;
    }
}

/*
 * writeSetTargetDocument
 *
 * Set the target document that command from the search window will operate
 * on
 */
void writeSetTargetDocument(
    writeDocument	*target
    )
{
    int		i;

    if (((target != NULL && targetDocument == NULL) ||
	 (target == NULL && targetDocument != NULL))
	&& (writeSearchWindow != NULL)) {

	  for (i=0; i<4; i++) {
	     
	     if (target == NULL)
		vbuttonDisable(searchButtons[i]);
	     else
		vbuttonEnable(searchButtons[i]);
	  }
       }


    if (targetDocument != NULL)
	vtextUninstallObserver(vtextviewGetTextData(targetDocument->textItem),
			       searchObserver);

    targetDocument = target;

    if (target != NULL) {

	vtextInstallObserver(vtextviewGetTextData(target->textItem),
			     searchObserver);

	_writeObserverSelect(searchObserver, 
			     vtextviewGetSelection(target->textItem), 
			     vtextSELECTION_HAS_CHANGED);
    }
}	

/*
 * writeGetTargetDocument
 */
writeDocument *writeGetTargetDocument(void)
{
    return(targetDocument);
}


/* * * * * * * * SEARCH WINDOW COMMAND SPACE * * * * * * * * */

static int _writeIssueSearchCommand(
    writeSearchDoc      *data,
    int		        selector,
    vdict               *context
    )
{
    switch (selector) {
	
    case comFIND_BUTTON:
	if (targetDocument != NULL)
	    writeSearchDocument(targetDocument, context);
        return(TRUE);

    case comCHANGE_THEN_FIND:
    case comCHANGE:
	if (targetDocument != NULL) {
	    
	    writeChangeInDocument(targetDocument, context);

	    if (selector == comCHANGE_THEN_FIND)	
		writeSearchDocument(targetDocument, context);
	}
        return(TRUE);

    case comFIND_THEN_CHANGE:
	if (targetDocument != NULL) {
	    
	    if (writeSearchDocument(targetDocument, context))
		writeChangeInDocument(targetDocument, context);
	}
        return(TRUE);

    case comCHANGE_ALL:
	if (targetDocument != NULL)
	    writeChangeAllInDocument(targetDocument, context);
        return(TRUE);

    case comCLOSE_SEARCH:
	writeDestroySearchWindow(data);
	return(TRUE);

    }

    return vclassSendSuper(defaultSearchClass,
			   vobjectISSUE_SELECTOR,
			   (data, selector, context));
}

static int _writeQuerySearchCommand(
    writeSearchDoc      *data,
    int		        selector,
    vdict               *context
    )
{
    return vclassSendSuper(defaultSearchClass,
			   vobjectQUERY_SELECTOR,
			   (data, selector, context));
}


/* * * * * *   STARTUP AND SHUTDOWN * * * * * */

/*
 * writeSearchStartup
 *
 * One-time setup of all search classes, commands, and more
 */
void writeSearchStartup()
{
    typedef struct {
	const char *id;
    } selectDef;

    register selectDef  *selectScan;

    static selectDef focusDefs[] = {
	{ "Cut", 			},
	{ "Copy", 			},
	{ "Paste", 			},
	{ "Clear", 			},
	{ "Select All", 		},
	{ NULL }
    };

    /*
     * Create the default search window class
     */

    defaultSearchClass = vclassSpawn(vdialogGetDefaultClass(),
				     sizeof(writeSearchDocClass));
	
    vclassSetNameScribed(defaultSearchClass,
                         vcharScribeLiteral("writeSearch"));
    vclassSetObjectSize(defaultSearchClass, sizeof(writeSearchDoc));

    vclassSet(defaultSearchClass,
              vobjectDESTROY,           _writeDestroySearch);
    vclassSet(defaultSearchClass, 
              vobjectISSUE_SELECTOR,    _writeIssueSearchCommand);
    vclassSet(defaultSearchClass, 
              vobjectQUERY_SELECTOR,    _writeQuerySearchCommand);

    /*
     * Create our observer class too monitor selection change, and change
     * the Change All button to "Change Selection" when there is a selection
     */

    defaultSearchObserverClass =
	vclassReproduce(vtextGetDefaultObserverClass());
    
    vclassSet(defaultSearchObserverClass,
	      vtextObserverSELECT,	_writeObserverSelect);

    searchObserver = vtextCreateObserverOfClass(defaultSearchObserverClass);

    /* Initialize focus def */

    vdictInit(&defaultFocusCommands, vnameHash);

    for (selectScan = focusDefs; selectScan->id!=NULL; selectScan++) {

	vdictStore(&defaultFocusCommands, vnameInternGlobalScribed
		   (vcharScribeLiteral(selectScan->id)),
		   vdialogCreateFocusCommand());
    }
}


/*
 * writeSearchShutdown
 */
void writeSearchShutdown()
{
    vcommandDestroyDict(&defaultFocusCommands);

    vtextDestroyObserver(searchObserver);
}


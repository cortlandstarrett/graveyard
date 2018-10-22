/* $Id: document.c,v 1.75 1997/10/23 21:39:43 gregt Exp $ */ 
/************************************************************

    document.c
    C Implementation file for the MicroDraw sample Document

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

#ifndef  vdebugINCLUDED
#include vdebugHEADER
#endif

#ifndef  vexINCLUDED
#include vexHEADER
#endif

#ifndef  vrectINCLUDED
#include vrectHEADER
#endif

#ifndef  vpointINCLUDED
#include vpointHEADER
#endif

#ifndef  vmatrixINCLUDED
#include vmatrixHEADER
#endif

#ifndef  vcharINCLUDED
#include vcharHEADER
#endif

#ifndef  vstrINCLUDED
#include vstrHEADER
#endif

#ifndef  vnameINCLUDED
#include vnameHEADER
#endif

#ifndef  vdictINCLUDED
#include vdictHEADER
#endif

#ifndef  veventINCLUDED
#include veventHEADER
#endif

#ifndef  vtimerINCLUDED
#include vtimerHEADER
#endif

#ifndef  vfsINCLUDED
#include vfsHEADER
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

#ifndef  vobjectINCLUDED
#include vobjectHEADER
#endif

#ifndef  vcommandINCLUDED
#include vcommandHEADER
#endif

#ifndef  vundoINCLUDED
#include vundoHEADER
#endif

#ifndef  vcolorINCLUDED
#include vcolorHEADER
#endif

#ifndef  vimageINCLUDED
#include vimageHEADER
#endif

#ifndef  vtextINCLUDED
#include vtextHEADER
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

#ifndef  vlafINCLUDED
#include vlafHEADER
#endif

#ifndef  vdialogINCLUDED
#include vdialogHEADER
#endif

#ifndef  vmenubarINCLUDED
#include vmenubarHEADER
#endif

#ifndef  vtextviewINCLUDED
#include vtextviewHEADER
#endif

#ifndef  vlistviewINCLUDED
#include vlistviewHEADER
#endif

#ifndef  vpaletteINCLUDED
#include vpaletteHEADER
#endif

#ifndef  vdomainviewINCLUDED
#include vdomainviewHEADER
#endif

#ifndef  vnoticeINCLUDED
#include vnoticeHEADER
#endif

#ifndef  vfilechsrINCLUDED
#include vfilechsrHEADER
#endif

#ifndef  vstylechsrINCLUDED
#include vstylechsrHEADER
#endif

#ifndef  vsessionINCLUDED
#include vsessionHEADER
#endif

#ifndef  vserviceINCLUDED
#include vserviceHEADER
#endif

#include "micdraw.h"

#if (vdebugDEBUG)
static const char _vmdrawTag[] = "vmdrawDocument";
#define vdebugTAG _vmdrawTag
#endif

/* #define vmdrawDEBUG             1 */

extern vtimer                   *positionTimer;

vdialog				*vmdrawPositionWindow = NULL;
vdialogItem			*vmdrawPositionItem;
vcolor                		*vmdrawEdgeColor;

static vmdrawDocumentClass	*defaultDocumentClass;
static vdomainObserverClass	*defaultObserverClass;
static vdialogItemClass		*defaultItemClass;
static vdialogItemClass		*defaultPosItemClass;
static vpaletteClass		*defaultPaletteClass;
static vmenuItemClass		*defaultWindowMenuItemClass;
static vdict		 	defaultFocusCommands;
static vcommandSpace     	defaultSpace, *tempSpace;
static vimage			*offscreenImage = NULL;

static vbyte			_vmdrawNewSlots[vmdrawMAX_DOCUMENTS + 1];
static vdict            	selectionState, noselectionState;
static vdict		 	standardState;
static vmenu			*defaultWindowMenu;

static void 		_vmdrawPaletteNotify(vlistview *, int);
static void		_vmdrawUndoNotify(vdomainview *, vundoAction *);
static void		_vmdrawDomainSelectNotify(vdialogItem *, vevent *);
static int 		_vmdrawSaveAndCloseNotify(vfilechsr *, vfsPath*);

static int _closeHook(vdialog *d, vevent *ev)
{
    vmdrawDocument	*data = (vmdrawDocument *) d;
    
    if (vmdrawIsDocumentValid(data)) {
	vmdrawDestroyDocument(data);
	return(FALSE);
    }
    else
	return(TRUE);
}

/*
 * _vmdrawCreateDocument
 *
 * Called by vmdrawNewDocument and vmdrawOpenDocument to obtain a new
 * initialized document (dialog) in which to draw in.  Reads the
 * dialog in from the resource file, and then sets up the document data
 */
static vmdrawDocument *_vmdrawCreateDocument(
    vmdrawTemplatePreferenceData	*prefs
    )
{
    vmdrawDocument	*data;
    vdomain		*domain;
    vcommandSpace	*space;
    vdomainObserver	*observer;
#ifndef vmdrawDEBUG
    vmenu               *menu;
#endif

    data = (vmdrawDocument *) vmdrawLoadDialog(vname_Document);

    vdialogMove(&data->dialog, 400, 400);

    /*
     * Add the document to the list of documents
     */

    data->next = vmdrawDocumentList;
    vmdrawDocumentList = data;

    /*
     * Initialize the document data
     */

    data->fileSpec       = vresourceNULL;
    data->newIndex	 = 0;
    data->undoLog	 = vundoCreateLog();
    data->name		 = NULL;
    data->documentWidth  = prefs->documentWidth;
    data->documentHeight = prefs->documentHeight;
    data->currentTool    = vmdrawARROW_TOOL;
    data->viewSettings	 = prefs->viewSettings;
    data->alignOption	 = prefs->alignOption;
    data->flags		 = 0;
    data->resizeObject   = NULL;
    data->editingObject  = NULL;
    data->lockedCell     = -1;
    data->scale	         = prefs->scale;
    data->matrix	 = *vmatrixIdent();
    data->floatTextView  = vmdrawCreateFloatTextView();
    data->editTextView	 = (vtextview *)
	vdialogFindItem(&data->dialog, vname_Text);

    /* Setup the floating and edit text views */

    vdialogHideItem(vtextviewGetItem(data->floatTextView));
    vdialogSetItemBorder(vtextviewGetItem(data->floatTextView), FALSE);
    vdialogSetItemBorder(vtextviewGetItem(data->editTextView), FALSE);
    vtextviewSetLeftMargin(data->floatTextView, 2);
    vtextviewSetLeftMargin(data->editTextView, 2);

    /* Setup the undo log */

    vundoMarkLogSaved(data->undoLog);
    vundoSetLogData(data->undoLog, data);

    /*
     * Create our command space, create our own standard state dictionary
     * and add the standard state and no selection state dictionaries
     * to the command space
     */

    data->space 	  = vcommandCreateSpace();
    data->standardState   = vdictClone(&standardState);
    vcommandAddSpaceDict(data->space, vname_State, data->standardState);
    vcommandAddSpaceDict(data->space, vname_State, &noselectionState);
    
    vundoInstallLogCommands(data->undoLog, data->space);

    /*
     * Find some needed dialog items 
     */

    data->domainView	= (vdomainview *)
                          vdialogFindItem(&data->dialog, vname_Domain);
    data->palette	= (vpalette *)
                          vdialogFindItem(&data->dialog, vname_Palette);
    data->menuBar	= (vmenubar *)
                          vdialogFindItem(&data->dialog, vname_MenuBar);
    data->scaleItem     = vdialogFindItem(&data->dialog,
                                     vnameInternGlobalLiteral("Scale"));
    data->windowMenu    = vmenubarFindMenu(data->menuBar,
				     vnameInternGlobalLiteral("WindowMenu"));

#ifndef vmdrawDEBUG
    menu = vmenubarFindMenu(data->menuBar,
                            vnameInternGlobalLiteral("DebugMenu"));
    vmenubarDeleteMenu(data->menuBar, menu);
    vmenuDestroy(menu);
#endif

    vdomainviewSetData(data->domainView, data);
    vdialogSetItemData(data->scaleItem, data);
    vpaletteSetData(data->palette, data);
    vtextviewSetData(data->editTextView, data);

    /*
     * Set up our palette 
     */

    vlistviewSetSelectNotify(vpaletteGetListview(data->palette),
			     _vmdrawPaletteNotify);
    vpaletteSetSelection(data->palette, 
        vpaletteFindItem(data->palette, vnameInternGlobalLiteral("Arrow")));

    /*
     * Set up our domain
     */
 
    domain = vmdrawCreateDomain();
    vdomainSetGrid(domain, &prefs->grid);
    vdomainSetOrientation(domain, vdomainORIENT_BOTTOM_LEFT);
    vdomainResize(domain, data->documentWidth, data->documentHeight);
    vdomainSetData(domain, data);

    vdomainviewSetDomain(data->domainView, domain);
    vdomainviewSetSelection(data->domainView, vdomainCreateSelection(domain));
    vdialogSetItemNotify(vdomainviewGetItem(data->domainView),
			 _vmdrawDomainSelectNotify);

    vdomainviewSetDrawObjectWithProc(data->domainView, vmdrawDrawObjectWith);
    vdomainviewSetDrawSelectionWithProc(data->domainView,
					vmdrawSelectObjectJointsWith);
    vdomainviewSetUndoNotify(data->domainView, _vmdrawUndoNotify);
    vdomainviewSetEventClass(data->domainView, vmdrawDefaultEventClass);
    vdomainviewSetOffscreenDrawing(data->domainView, TRUE);

    vdomainSetRectIntersectFunc(vdomainviewGetDomain(data->domainView),
				vmdrawRectIntersect);

    /* Set up the domain observer */

    observer = vdomainCreateObserverOfClass(defaultObserverClass);
    vdomainSetObserverData(observer, data);
    vdomainInstallObserverOwned(domain, observer);
    vdomainSetUndoObserver(domain, vdomainGetDefaultUndoObserverClass());

    /*
     * Add the focus command dictionary to the dialog's command space, so
     * that these command get redirected to the focus item
     */
    
    space = vclassGet(vdialogGetClass(&data->dialog), vobjectSPACE);
    vcommandAddSpaceDict(space, vname_Command, &defaultFocusCommands);
    
    vdialogSetCloseHook(&data->dialog, _closeHook);

#if (mdrawUSE_DAS)
    data->session = NULL;
    data->service = NULL;
    data->observerSessionDomain = NULL;
    data->observerSessionText = NULL;
    data->dictObjectMap = NULL;
    data->idNext = 1;
#endif

    return(data);
}

/*
 * _vmdrawSetDocumentTemplate
 */
static void _vmdrawSetDocumentTemplate(
    vmdrawDocument		 *data,
    vmdrawTemplatePreferenceData *templat
    )
{
    templat->newDocumentRect =
        *vwindowGetRect((vwindow *) data);
    templat->grid  		= *vdomainGetGrid(vdomainviewGetDomain
						  (data->domainView));
    templat->scale		= data->scale;
    templat->viewSettings	= data->viewSettings;
    templat->alignOption	= data->alignOption;
    templat->documentWidth	= data->documentWidth;
    templat->documentHeight	= data->documentHeight;
}

/*
 * _vmdrawRegisterUntitled
 *
 * Register a new untitled document. Find a uniqued Untitled "#" to 
 * assign the document (stored in "newIndex", then creates and sets
 * the title appropriately
 */
static void _vmdrawRegisterUntitled(vmdrawDocument *data)
{
    vstr		*title;
    int                 i;

    /*
     * Assign a unique "new" index for the scratch data
     */

    for (i=0; i<vmdrawMAX_DOCUMENTS; i++) {
        if (_vmdrawNewSlots[i] == 0) {
            _vmdrawNewSlots[i] = 1;
            break;
        }
    }
    data->newIndex = i;
    title = vresourceGetStringAt(vmdrawMessages, vmdrawMSG_UNTITLED);
    (void) vstrAppendScribed(title, vnumScribeInt(data->newIndex));
    data->name = title;
}

/*
 * vmdrawNewDocument
 * 
 * Creates a new empty "Untitled" document.
 */
vmdrawDocument *vmdrawNewDocument()
{
    vmdrawDocument	*data;
    const vrect		*r;

    data                = _vmdrawCreateDocument(&vmdrawTemplatePreferences);
    data->fileSpec 	= vresourceNULL;

    _vmdrawRegisterUntitled(data);

    vdialogSetTitle(&data->dialog, data->name);

    if (vmdrawTemplatePreferences.newDocumentRect.y != 0)
        vwindowSetRect((vwindow *) data,
                       &vmdrawTemplatePreferences.newDocumentRect); 
    else {
        vmdrawCenterWindow(vdialogGetWindow(&data->dialog));
    }

    /* If there is a window already open, place it wrt that window */

    if (wrtDialog != NULL) {
        r = vwindowGetRect((vwindow *) vdialogGetWindow(wrtDialog));
        vwindowMove(vdialogGetWindow(&data->dialog), r->x + 30, r->y - 30);
    }
    
    vwindowSetSpace((vwindow *) data, data->space);
    
    /* Rebuild the window menu */
    
    vmdrawBuildWindowMenus();
    
    vdialogOpen(&data->dialog);
    return  data;
}

/*
 * vmdrawOpenDocument
 * 
 * Opens and reads in a saved document.
 */
void vmdrawOpenDocument(
    vfsPath	*filePath
    )
{
    vmdrawDocument		 *data;
    vdomain			 *domain, *oldDomain;
    volatile vresource		 fileSpec;
    volatile int		 flags = 0;
    vmdrawTemplatePreferenceData templat;
    vstr			 *str;
    vdomainObserver		 *observer;

    if (!vfsAccess(filePath, vfsFILE_EXISTS))
        return;
    
    vexWITH_HANDLING {

	if (!vfsAccess(filePath, vfsCAN_WRITE)) {
	    fileSpec = vresourceOpenFile(filePath, vfsOPEN_READ_ONLY);
	    flags |= vmdrawDOC_READ_ONLY;
	}
	else {
	    fileSpec = vresourceOpenFile(filePath, vfsOPEN_READ_WRITE);
	    flags &= ~vmdrawDOC_READ_ONLY;
	}
    }
    vexON_EXCEPTION {
        
        str = vresourceGetStringAt(vmdrawMessages, vmdrawMSG_READ_ERROR);
        vmdrawAlert(NULL, str);
        vstrDestroy(str);
	vexClear();
	return;
    }
    vexEND_HANDLING;

    templat  = vmdrawTemplatePreferences;
    
    vmdrawLoadTemplate(fileSpec, &templat);
    
    data 	   = _vmdrawCreateDocument(&templat);
    data->fileSpec = fileSpec;
    data->name     = vstrClone(vfsGetPathElementAt(filePath,
						   vfsGetPathElementCount(filePath)-1));
    data->flags	   |= flags;
    
    /*
     * Load up the document - first the text and styles itself.  Since
     * the object are loaded via vdomainLoad, we need to destroy the
     * domain that vmdrawCreateDocument created - We cannot destroy the
     * domain, however, until we do vdomainviewSetDomain with the new
     * domain.
     */
    
    oldDomain   = vdomainviewGetDomain(data->domainView);

    vexWITH_HANDLING {

	domain = vdomainLoad(data->fileSpec);

	vdomainviewSetDomain(data->domainView, domain);
	vdomainDestroy(oldDomain);
	vdomainviewSetSelection(data->domainView, vdomainCreateSelection(domain));
	vdomainSetData(domain, data);
	
	vmdrawRecalcLayering(data);
    }
    vexON_EXCEPTION {

        str = vresourceGetStringAt(vmdrawMessages, vmdrawMSG_READ_ERROR);
        vmdrawAlert(NULL, str);
        vstrDestroy(str);

	domain = oldDomain;
    }
    vexEND_HANDLING;

    
    /* Set up the domain observer */

    observer = vdomainCreateObserverOfClass(defaultObserverClass);
    vdomainSetObserverData(observer, data);
    vdomainInstallObserverOwned(domain, observer);
    vdomainSetUndoObserver(domain, vdomainGetDefaultUndoObserverClass());

    /*
     * Now any of our stuff (placement rect & pen set)
     */
    
    vwindowSetRect((vwindow *) data, &templat.newDocumentRect);
    
    vwindowSetSpace((vwindow *) data, data->space);
    
    vdialogSetTitle(&data->dialog, data->name);
    
    /* Rebuild the window menu */
    
    vmdrawBuildWindowMenus();
    
    vdialogOpen(&data->dialog);
}

/* * * * * * * * *  Validating a Document * * * * * * * */

static int _saveChanges(
    vnotice		*notice,
    vevent		*event
    )
{
    vmdrawDocument	*data = (vmdrawDocument *) vnoticeGetData(notice);
    
    if (vmdrawSaveDocument(data, NULL) != vmdrawDID_SAVE_AS)
	vmdrawDestroyDocument(data);
    else
	vfilechsrSetApply(vmdrawSaveWindow, _vmdrawSaveAndCloseNotify);
	
    return(TRUE);
}

static int _closeAnyway(
    vnotice		*notice,
    vevent		*event
    )
{
    vmdrawDocument	*data = (vmdrawDocument *) vnoticeGetData(notice);

    vmdrawDestroyDocument(data);
    return(TRUE);
}

/*
 * vmdrawIsDocumentValid
 *
 * vdialogDESTROY method for draw documents.  Checks for saving before
 * close the file.
 */
vbool vmdrawIsDocumentValid(
    vmdrawDocument	*data
    )
{
    vstr                *str;

    if (!vundoIsLogSaved(data->undoLog) &&
        (data->flags & vmdrawDOC_READ_ONLY) == 0) {

        str = vresourceGetStringAt(vmdrawMessages, vmdrawMSG_SAVE_CHANGES);
	vmdrawReplaceStrings(&str, vcharScribe(data->name), NULL);
        vmdrawConfirmation(&data->dialog, str, _saveChanges, _closeAnyway);
        vstrDestroy(str);

	return(FALSE);
    }

    return(TRUE);
}

#if (mdrawUSE_DAS)

static void _micdrawNoOpNotify(
    vsession		*session,
    vsessionEvent	*event
    )
{
    /*
     * this notify is used to get around a bug in some of the 2.0 libs
     * with sync end of a session.  once the bug has been fixed this
     * can be replaced with just setting the session notify to NULL.
     */
    
} /* _micdrawNoOpNotify */

#endif

/* * * * * * * * *  Destroying a Document * * * * * * * */
/*
 * _vmdrawDestroyDocument
 *
 * The destroy method for the document class
 */
static void _vmdrawDestroyDocument(
    vmdrawDocument	*data
    )
{
    vmdrawDocument		*prev;
    vdomain			*domain;
    vmdrawTemplatePreferenceData templat;

    if (data->fileSpec != vresourceNULL &&
	(data->flags & vmdrawDOC_READ_ONLY) == 0) {

        _vmdrawSetDocumentTemplate(data, &templat);
        vmdrawStoreTemplate(data->fileSpec, &templat);

    }

    /*
     * Remove the document from the list of documents
     */

    if (data == vmdrawDocumentList)
        vmdrawDocumentList = data->next;
    else {
        prev = vmdrawDocumentList;
        while (prev->next != NULL) {
            if (prev->next == data) {
                prev->next = data->next;
                break;
            }
	    prev = prev->next;
        }
    }

    /*
     * Close the resource file associated with the document OR if it 
     * is a Untitled documents, free up the untitled slot
     */

    if (data->fileSpec == vresourceNULL)
        _vmdrawNewSlots[data->newIndex] = 0;
    else
        vresourceCloseFile(data->fileSpec);

    /*
     * Unset it as the target document if it is the target document
     */

    if (vmdrawTargetDocument == data)
	vmdrawSetTargetDocument(NULL);

    /*
     * Destroy the command space, standard state dict, undo log
     * and the domain data
     */
    
    vwindowSetSpace((vwindow *) data, NULL);

    vcommandRemoveSpaceDict(data->space, vname_State, data->standardState);
    vdictDestroy(data->standardState);
    vundoDestroyLog(data->undoLog); 

    domain = vdomainviewGetDomain(data->domainView);
    vdomainviewSetDomain(data->domainView, NULL);
    vdomainDestroy(domain);

    vtextviewDestroy(data->floatTextView);
    vstrDestroy(data->name);

    vcommandDestroySpace(data->space);

    /* Rebuild the window menu */

    vmdrawBuildWindowMenus();

#if (mdrawUSE_DAS)
    if (data->session != NULL) {
	vsessionSetNotify(data->session, _micdrawNoOpNotify);
	vsessionSetDestroyWhenInactive(data->session, TRUE);
	vsessionEnd(data->session);
    }
    if (data->service != NULL) {
	mdrawUnregisterDocument(data);
	vserviceDestroy(data->service);
    }
    if (data->observerSessionDomain != NULL)
	vdomainDestroyObserver(data->observerSessionDomain);
    if (data->observerSessionText != NULL)
	vtextDestroyObserver(data->observerSessionText);
    if (data->dictObjectMap != NULL)
	vdictDestroy(data->dictObjectMap);
#endif

    if (vmdrawDocumentList == NULL)
        veventStopProcessing();

    vclassSendSuper(defaultDocumentClass, vobjectDESTROY, (data));
}

/* * * * * * * * *  Saving a Document * * * * * * * */

/*
 * _vmdrawSaveNotify
 *
 * Notify function for the save confirm dialog.  Creates a new file
 * resets the document name, and then saves the document
 */
static int _vmdrawSaveNotify(
    vfilechsr		*chooser,
    vfsPath		*filePath
    )
{
    vmdrawDocument	*data;

    if (vfsAccess(filePath, vfsFILE_EXISTS)) {

	vfsRemove(filePath);
    }/*
    else {
        vfsCreateFile(filePath, vfsOWNER_WRITE | vfsOWNER_READ);
    } */
    
    data = (vmdrawDocument *) vfilechsrGetData(chooser);

    if (data->fileSpec != vresourceNULL)
        vresourceCloseFile(data->fileSpec);

    data->fileSpec = vresourceCreateFile(filePath, 
                                         vfsOWNER_READ | vfsOWNER_WRITE);
    vstrDestroy(data->name);
    data->name  = vstrClone(vfsGetPathElementAt(filePath,
				      vfsGetPathElementCount(filePath)-1));

    vdialogSetTitle(&data->dialog, data->name);

    if (data->newIndex >= 0) {
        _vmdrawNewSlots[data->newIndex] = -1;
        data->newIndex = -1;
    }

    vmdrawSaveDocument(data, NULL);

    return(TRUE);
}

static int _vmdrawSaveAndCloseNotify(
    vfilechsr		*chooser,
    vfsPath		*filePath
    )
{
    vmdrawDocument *data = (vmdrawDocument *) vfilechsrGetData(chooser);

    _vmdrawSaveNotify(chooser, filePath);

    vmdrawDestroyDocument(data);

    return(TRUE);
}

/*
 * vmdrawSaveDocument
 *
 * Save a Document.  If the document has not been saved before (Untitled doc)
 * or the context dictionary contains the option "As" (for Save As), then
 * bring up the file chooser to save the file.
 */
vbool vmdrawSaveDocument(
    vmdrawDocument	*data,
    vdict		*context
    )
{
    vstr        *str;

    if (data->fileSpec == vresourceNULL || (context != NULL &&
	vdictLoad(context, vmdraw_Option) != NULL)) {

        if (vmdrawSaveWindow != NULL) {
	    if (!vdialogIsOpen(vfilechsrGetDialog(vmdrawSaveWindow)))
	        vdialogOpen(vfilechsrGetDialog(vmdrawSaveWindow));
	    vwindowRaise(vdialogGetWindow(vfilechsrGetDialog(vmdrawSaveWindow)));
	    vfilechsrSetData(vmdrawSaveWindow, data);
	    vfilechsrSetApply(vmdrawSaveWindow, _vmdrawSaveNotify);
           return(FALSE);
        }

        vmdrawSaveWindow = vfilechsrCreate();
	vfilechsrSetType(vmdrawSaveWindow, vfilechsrPUT);
	vfilechsrSetData(vmdrawSaveWindow, data);
	vfilechsrSetApply(vmdrawSaveWindow, _vmdrawSaveNotify);
	vfilechsrSetDirectory(vmdrawSaveWindow, vfsGetAppDirPath());

        str = vresourceGetStringAt(vmdrawMessages, vmdrawMSG_SAVE_DOCUMENT);
        vdialogSetTitle(vfilechsrGetDialog(vmdrawSaveWindow), str);
        vstrDestroy(str);

	vdialogOpen(vfilechsrGetDialog(vmdrawSaveWindow));
    
	/* Rebuild the window menu */

	vmdrawBuildWindowMenus();

	return(vmdrawDID_SAVE_AS);
    }

    if (data->flags & vmdrawDOC_READ_ONLY) {

        str = vresourceGetStringAt(vmdrawMessages,	
				   vmdrawMSG_CANT_SAVE_CHANGES);
        vmdrawAlert(&data->dialog, str);
        vstrDestroy(str);

	return(vmdrawWAS_READ_ONLY);
    }

    /*
     * Store the document
     */

    vdomainStore(vdomainviewGetDomain(data->domainView), data->fileSpec);

    /*
     * Store the document placement
     */

    vresourceStoreRect(vwindowGetRect((vwindow *) data),
		       vresourceMake(data->fileSpec, vname_Rect));

    vresourceFlush(data->fileSpec);

    vundoMarkLogSaved(data->undoLog);
   
    return(vmdrawSAVED);
}


/*
 * vmdrawChangeDocumentState
 *
 * Change the value a one of the standard document states
 */
void vmdrawChangeDocumentState(
    vmdrawDocument      *data,
    const vname		*name,
    const vname		*value
    )
{
    if (value != NULL)
	vdictStore(data->standardState, name, value);

    if (data != NULL)
        vobjectPropagateChange(vwindowGetObject((vwindow *) data),
                               vname_State, name, value);
}

/* * * * * * Domain View Event Handlers * * * * * * * */

/*
 * _vmdrawObserverSelect
 *
 * Change document state when the selection changes
 */
void _vmdrawObserverSelect(
    vdomainObserver	*observer,
    vdomainObjectSet	*set,
    vdomainSelection	selection,
    int			selected
    )
{
    vmdrawChangeDocumentState(
                 (vmdrawDocument *) vdomainGetObserverData(observer),
	         vnameInternGlobalLiteral("Apply Justification"), NULL);

    vmdrawSetTargetDocument((vmdrawDocument *)vdomainGetObserverData(observer));
}

/*
 * _vdmdrawUndoNotify
 *
 * Handle undo actions from the domain
 */
static void _vmdrawUndoNotify(
    vdomainview		*domainView,
    vundoAction		*undoAction
    )
{
    vmdrawDocument	*data;

    data = (vmdrawDocument *) vdomainviewGetData(domainView);

    vundoAddLogAction(data->undoLog, undoAction);
}

/*
 * _vmdrawDomainSelectNotify
 *
 * Handle maintain select and unselected state
 */
static void _vmdrawDomainSelectNotify(
    vdialogItem		*item,
    vevent		*event
    )
{
    vdomainview		*domainView = (vdomainview *) item;
    vdomain		*domain;
    int                 selectCount;
    vmdrawDocument      *data;

    data        = (vmdrawDocument *) vdomainviewGetData(domainView);
    domain      = vdomainviewGetDomain(domainView);
    selectCount = vdomainSelectedObjects(domain, 
                                         vdomainviewGetSelection(domainView));

    if (selectCount == 0) {
        if (data->flags & vmdrawDOC_SELECTION) {
            vcommandReplaceSpaceDict(data->space, vname_State,
                                     &selectionState, &noselectionState);
            data->flags &= ~vmdrawDOC_SELECTION;
        }
    }
    else {
        if ((data->flags & vmdrawDOC_SELECTION) == 0) {
            vcommandReplaceSpaceDict(data->space, vname_State,
                                     &noselectionState, &selectionState);
            data->flags |= vmdrawDOC_SELECTION;
        }
    }   
}

#ifdef vmdrawDEBUG
/*
 * _vmdrawDumpObjects
 */
static void _vmdrawDumpObjects(
    vmdrawDocument      *data,
    vdomainObjectSet    *objectSet
    )
{
    vdomainObjectSetIterator    iterator;
    vdomainObject               *object;
    vrect                       *r, r1, r2;
    vdomain			*domain;
    vmdrawObjectData		*objectData;

    domain = vdomainviewGetDomain(data->domainView);
    
    vdomainInitObjectSetIterator(&iterator, objectSet);
        
    while (vdomainNextObjectSetIterator(&iterator)) {
            
        object     = vdomainGetObjectSetIteratorObject(&iterator);
        r          = vdomainGetObjectBounds(domain, object);
	objectData = (vmdrawObjectData *) vdomainGetObjectData(domain, object);
        r1	   = *r;

        vdomainviewTranslateRect(data->domainView, &r1, vdomainviewTO_DIALOG);
        r2 = r1;
	vdomainviewTranslateRect(data->domainView, &r2, vdomainviewTO_DOMAIN);
        
        printf("\n\nObject (%x)\n", (int) object);
        printf("    Bounds:              %d %d %d %d\n", r->x, r->y, r->w, r->h);
        printf("    Bounds: (translated) %d %d %d %d\n", r2.x, r2.y, r2.w, r2.h);
        printf("    Bounds: (dialog):    %d %d %d %d\n", r1.x, r1.y, r1.w, r1.h);
        printf("    Type:                %d\n", vdomainGetObjectType(domain, object));
        printf("    ");

        if (vdomainIsObjectAnchored(domain, object))
            printf("Anchored, ");
        else
            printf("Not Anchored, ");

        if (vdomainIsObjectOpaque(domain, object))
            printf("Opaque, ");
        else
            printf("Not Opaque, ");

        if (vdomainIsObjectHidden(domain, object))
            printf("Hidden, ");
        else
            printf("Not Hidden, ");

        if (vdomainIsObjectUnselectable(domain, object))
            printf("Unselectable, ");
        else
            printf("Not Unselectable, ");

        if (vdomainIsObjectSelectNotify(domain, object))
            printf("SelectNotify, ");
        else
            printf("Not SelectNotify, ");
    }
    printf("\n");
    vdomainDestroyObjectSetIterator(&iterator);
}
#endif

/* * * * * * * Scale Items Handling * * * * * * * */

/*
 * _vmdrawDrawScaleItemWith
 *
 * Draw the "Scale" dialog item - showing the current scale of the document
 */
static void _vmdrawDrawScaleItemWith(
    vdialogItem		*item,
    vdrawcontext	*context
    )
{
    vmdrawDocument      *data;
    const vrect         *r;

    vclassSendSuper(defaultItemClass, vdialogDRAW_ITEM_WITH, (item, context));

    data    = (vmdrawDocument *) vdialogGetItemData(item);

    r = vdialogGetItemRect(item);
    vdrawcontextSetCurrentPoint(context, r->x + 5, r->y + 4);
    vdrawcontextDrawStringScribed(context, vnumScribeFloat(data->scale), NULL);
}

/* * * * * * * Position Item Handling * * * * * * * */

/*
 * vmdrawCreatePositionWindow
 *
 * Load up and initialize the Position window
 */
void vmdrawCreatePositionWindow()
{

    if (vmdrawPositionWindow != NULL) {
        if (!vdialogIsOpen(vmdrawPositionWindow))
            vdialogOpen(vmdrawPositionWindow);
        return;
      }

    vmdrawPositionWindow = 
	vmdrawLoadDialog(vnameInternGlobalLiteral("Position"));

    vmdrawPositionItem = vdialogFindItem(vmdrawPositionWindow, 
					 vnameInternGlobalLiteral("Position"));
					 
    vdialogMove(vmdrawPositionWindow, 300, 200);

    vdialogOpen(vmdrawPositionWindow);

    vtimerStart(positionTimer);
}

/*
 * _vmdrawDrawPosItemWith
 *
 * Draw the "Position" dialog item - showing the current mouse position
 */
static void _vmdrawDrawPosItemWith(
    vdialogItem		*item,
    vdrawcontext	*context
    )
{
    vrect		r;
    const vrect		*r2;
    vdrawcontext	*imageContext;
    double              lineWidth;
    vcolor		*bgColor, *color;

    r2 = vdialogGetItemRect(item);
    r = *r2;

    if (offscreenImage == NULL)
	return;

    if (r.w != vimageGetWidth(offscreenImage) ||
	r.h != vimageGetHeight(offscreenImage))
        vimageSetSize(offscreenImage, r.w, r.h);

    imageContext = vdrawCreateImageDrawcontext(offscreenImage);
    r.x = r.y = 0;

    color       = vdrawpenGetColor(vdrawcontextGetPen(context));
    bgColor	= vdrawpenGetComplementColor(vdrawcontextGetPen(context));
    lineWidth   = vdrawpenGetLineWidth(vdrawcontextGetPen(context));

    vdrawpenSetColor(vdrawcontextGetPen(imageContext), bgColor);
    vdrawcontextFillRectangles(imageContext, &r, 1);

    vdrawcontextDrawHilitedRectanglesInside(imageContext, &r, 1,
		     vdialogDetermineItemColor(item, vdrawCOLOR_SHADOW_BOTTOM),
		       vdialogDetermineItemColor(item, vdrawCOLOR_SHADOW_TOP));

    if (vmdrawCurrentPosition.x != -1) {

	vdrawpenSetColor(vdrawcontextGetPen(imageContext), color);
	vdrawpenSetLineWidth(vdrawcontextGetPen(imageContext), lineWidth);

	vdrawcontextSetCurrentPoint(imageContext, 20, 30);
	vdrawcontextDrawStringScribed(imageContext,
				      vnumScribeInt(vmdrawCurrentPosition.x),
				      NULL);
	vdrawcontextSetCurrentPoint(imageContext, 20, 10);
	vdrawcontextDrawStringScribed(imageContext,
				      vnumScribeInt(vmdrawCurrentPosition.y),
				      NULL);
    }
    vdrawcontextDestroy(imageContext);

    vdrawcontextSetCurrentPoint(context, r2->x, r2->y);
    vdrawcontextDrawImage(context, offscreenImage, NULL);
}

/* * * * * * * Palette Handling * * * * * * * */

/*
 * _vmdrawPaletteNotify
 *
 * Notification of a palette selection - determine the new
 * current tool
 */
static void _vmdrawPaletteNotify(
    vlistview		*item,
    int			state
    )
{
    vpaletteItem        *paletteItem;
    vmdrawDocument	*data;
    vrect		r;
    int 		rectInset;

    data 	= (vmdrawDocument *) vlistviewGetData(item);
    paletteItem = vpaletteGetSelection((vpalette *) item);

    data->lockedCell  = -1;
    data->currentTool = vpaletteGetItemIndex((vpalette *) item, paletteItem)+1;

    if (vlistviewGetLastPointerClickCount(item) > 1) {

        data->lockedCell = data->currentTool - 1;
	rectInset        = vclassGet(vlistviewGetClass(item),
                                     vlistviewSELECTION_INSET);
	vlistviewGetCellRect(item, data->currentTool - 1, 0, &r);
	vrectInset(&r, -rectInset, -rectInset, &r);
	vdialogInvalItemRect(vlistviewGetItem(item), &r, vwindowINVAL_OPAQUE);
	return;
    }

    if (state != vlistviewSELECTION_HAS_CHANGED)
	return;
	
    /*
     * Disabled editing whenever they select from the palette again.
     */

    vmdrawDisableEditing(data, FALSE);

    /* Set the track mode */

    if (data->currentTool == vmdrawARROW_TOOL)
        vdomainviewSetTrackMode(data->domainView, 
                                vdomainviewTRACK_SELECT | vdomainviewTRACK_DRAG);
    else
        vdomainviewSetTrackMode(data->domainView, vdomainviewTRACK_NONE);
}


/* * * Window Menu Building and Handling * * * */

/*
 * _vmdrawDrawWindowMenuItemWith
 *
 * Draw prodedure for a window menu item.  Draws a "modified" indicator
 * before the document name if appropriate
 */
static void _vmdrawDrawWindowMenuItemWith(
    vmenuItem		*item,
    const vrect		*bounds,
    const vrect		*content,
    vdrawcontext	*context
    )
{
    vmdrawDocument	*data;

    data = (vmdrawDocument *) vmenuGetItemData(item);

    vdrawcontextSetCurrentPoint(context, content->x, content->y);
    if (!vundoIsLogSaved(data->undoLog))
	vdrawcontextDrawStringScribed(context, vcharScribeLiteral("*"), NULL);
    vdrawcontextDrawStringScribed(context,
				  vcharScribe(vmenuGetItemTitle(item)), NULL);
}

/*
 * _vmdrawSelectWindow
 * 
 * Notify prodedure for a window menu item - raise the associated dialog
 */
static void _vmdrawSelectWindow(
    vmenuItem		*item,
    vevent		*event
    )
{
    vwindowRaise((vwindow *) vmenuGetItemData(item));
}

/*
 * _vmdrawAddItem
 *
 * Support routine for _vmdrawCreateWindowMenu.  Append a new menu
 * item to a window menu, sets the title, data and notification
 * functions for the menu item.
 */
static void _vmdrawAddItem(
    vmenu             *menu,
    vwindow           *window,
    const vchar       *name
    )
{
    vmenuItem		*item;

    item = vmenuCreateItem();

    vmenuSetItemData(item, window);
    vmenuSetItemNotify(item, _vmdrawSelectWindow);
    vmenuSetItemTitle(item, name);
    vmenuAppendItem(menu, item);
}

/*
 * _vmdrawCreateWindowMenu
 *
 * Create a window menu that can be copied into all document window's
 */
static vmenu *_vmdrawCreateWindowMenu(void)
{
    vmenu               *windowMenu;
    vmenuItem           *item;
    vbool		hasUtil;
    vmdrawDocument       *data;

    windowMenu = vmenuClone(defaultWindowMenu);
    
    hasUtil = (vmdrawOpenWindow != NULL       || vmdrawSaveWindow != NULL);

    /*
     * First, add all of the documents to the document menu
     */

    data = vmdrawDocumentList;
    while (data != NULL) {
        _vmdrawAddItem(windowMenu, vdialogGetWindow(&data->dialog), 
                      vdialogGetTitle(&data->dialog));
        data = data->next;
    }
   
    /*
     * If we have utility windows, add  a seperator item
     */

    if (hasUtil) {
        item = vmenuCreateSeparatorItem();
        vmenuAppendItem(windowMenu, item);
    }

    /*
     * Now, add all of the utility windows
     */

    if (vmdrawOpenWindow != NULL)
        _vmdrawAddItem(windowMenu,
                      vdialogGetWindow(vfilechsrGetDialog(vmdrawOpenWindow)),
		      vdialogGetTitle(vfilechsrGetDialog(vmdrawOpenWindow)));

    if (vmdrawSaveWindow != NULL)
        _vmdrawAddItem(windowMenu,
                      vdialogGetWindow(vfilechsrGetDialog(vmdrawSaveWindow)),
		      vdialogGetTitle(vfilechsrGetDialog(vmdrawSaveWindow)));

    return(windowMenu);
}

/*
 * vmdrawBuildWindowMenus
 *
 * Rebuild the window menu for every document
 */
void vmdrawBuildWindowMenus()
{         
    vmenu		*menu;
    vmdrawDocument	*data;

    /*
     * Add the window to the window menu.  We need to add it to all 
     * window menus in all open windows.
     */
    
    menu = _vmdrawCreateWindowMenu();
    data = vmdrawDocumentList;

    while (data != NULL) {
        vmenuCopy(menu, data->windowMenu);
	vmenuSetLeader(data->windowMenu, (vwindow *) data);
        data = data->next;
    }

    vmenuDestroy(menu);
}

/* * * * * * * * * Palette Class Methods * * * * * * */

/*
 * _vmdrawDrawPaletteBackground
 */
static void _vmdrawDrawPaletteBackgroundWith(
    vpalette		*palette,
    int			row,
    int			col,
    int			selected,
    vrect		*r,
    vdrawcontext	*context
    )
{
    vdialogItem		*item;
    vlist		*list = vlistviewGetList((vlistview *) palette);
    vpaletteItem	*paletteItem;
    vcolor              *saveColor, *color;
    vmdrawDocument	*data;

    item = vpaletteGetItem(palette);
    data = (vmdrawDocument *) vpaletteGetData(palette);

    paletteItem   = (vpaletteItem *) vlistGetCellValue( list, row, col );
    
    /* Don't draw border for NULL/non-items */
    
    if (paletteItem == NULL)
      return;

    if (selected) {
        color = (data->lockedCell != row) ?
            vdialogDetermineItemColor(item, vdrawCOLOR_BACKGROUND) :
                vmdrawLockedColor;
	if (vlaf3D())
	    vdrawcontextFillHilitedRectanglesInside(context, r, 1, color,
	       vdialogDetermineItemColor(item, vdrawCOLOR_SHADOW_BOTTOM),
	       vdialogDetermineItemColor(item, vdrawCOLOR_SHADOW_TOP));
	else {
	    saveColor = vdrawpenGetColor(vdrawcontextGetPen(context));
	    if (color != vmdrawLockedColor)
		color = vdialogDetermineItemColor(item, vdrawCOLOR_FOREGROUND);
	    vdrawpenSetColor(vdrawcontextGetPen(context), color);
	    vdrawcontextFillRectangles(context, r, 1);
	    vdrawpenSetColor(vdrawcontextGetPen(context), saveColor);
	    vdrawcontextDrawRectanglesInside(context, r, 1);
	}
    }
    else {
        vclassSendSuper(defaultPaletteClass,
			vlistviewDRAW_CELL_BACKGROUND_WITH,
                        (palette, row, col, selected, r, context));
    }
}

/*
 * _vmdrawPaletteButtonDown
 */
static int _vmdrawPaletteButtonDown(
    vpalette            *palette,
    vevent              *ev
    )
{
    vmdrawDocument      *data;

    data = (vmdrawDocument *) vpaletteGetData(palette);

    data->lockedCell  = -1;

    return(
           vclassSendSuper(defaultPaletteClass, vdialogHANDLE_ITEM_BUTTON_DOWN,
                           (palette, ev)));
}

/* * * * * * * * * * * DOCUMENT COMMAND SPACE * * * * * * * * * */

static vdict  defaultKeyMap;

static void _vmdrawInitDocumentSpace(void)
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
	{ "Duplicate", 			},
	{ "Select All", 		},
	{ NULL }
    };

    vdictInit(&defaultFocusCommands, vnameHash);

    for (selectScan = focusDefs; selectScan->id!=NULL; selectScan++) {

	vdictStore(&defaultFocusCommands, vnameInternGlobalScribed
		   (vcharScribeLiteral(selectScan->id)),
		   vdialogCreateFocusCommand());
    }

    vcommandCopyInitSpace(vclassGet(vdialogGetDefaultClass(),
				    vobjectSPACE), &defaultSpace);

    vdictCopyInit(vclassGet(vdialogGetDefaultClass(),
			    vobjectKEY_MAP),  &defaultKeyMap);

    tempSpace = vmdrawLoadSpace(vnameInternGlobalLiteral("Document Space"));

    {
        vcommandSpaceIterator iterator;
        vcommandInitSpaceIterator(&iterator, tempSpace);
        while (vcommandNextSpaceIterator(&iterator)) {
            vcommandAddSpaceDict(&defaultSpace, 
                                 vcommandGetSpaceIteratorAttr(&iterator),
                                 vcommandGetSpaceIteratorDict(&iterator));
            if (vcommandGetSpaceIteratorAttr(&iterator) == vname_Key)
                vcommandMapKeyDict(vcommandGetSpaceIteratorDict(&iterator),
                                   &defaultKeyMap);
	}
	
        vcommandDestroySpaceIterator(&iterator);
    }
}

static void _vmdrawInitStateDictionaries(void)
{
    typedef struct {
        const char	*id;
	short		state;
    } stateDef;

    register stateDef   *states;

    static stateDef selStateDefs[] = {
        { "Cut",          	TRUE },
        { "Copy",         	TRUE },
        { "Clear",	  	TRUE },
        { "Duplicate",	  	TRUE },
	{ NULL }
    };
    
    static stateDef noselStateDefs[] = {
        { "Cut",          	FALSE },
        { "Copy",         	FALSE },
        { "Clear",	  	FALSE },
        { "Duplicate",	  	FALSE },
	{ NULL }
    };

    static stateDef standardStateDefs[] = { 
        { "Zoom In",                    TRUE },
        { "Zoom Out",                   TRUE },
        { "Paste",                      TRUE },
        { "Apply Style",                FALSE },
        { "Apply Justification",        FALSE },
        { "Apply Case",       		FALSE },
	{ NULL }
    };
 
    /*
     * Now create the state dictionaries
     */

    vdictInit(&selectionState, vnameHash);
    vdictInit(&noselectionState, vnameHash);
    vdictInit(&standardState, vnameHash);

    for (states = selStateDefs; states->id!=NULL; states++)
        vdictStore(&selectionState, vnameInternGlobalScribed
		   (vcharScribeLiteral(states->id)),  (void *)
		   (states->state ? vname_Enabled : vname_Disabled));

    for (states = noselStateDefs; states->id!=NULL; states++)
        vdictStore(&noselectionState, vnameInternGlobalScribed
		   (vcharScribeLiteral(states->id)), (void *)
		   (states->state ? vname_Enabled : vname_Disabled));

    for (states = standardStateDefs; states->id!=NULL; states++)
        vdictStore(&standardState, vnameInternGlobalScribed
		   (vcharScribeLiteral(states->id)),  (void *)
		   (states->state ? vname_Enabled : vname_Disabled));
}

static int _vmdrawIssueDocumentCommand(
    vmdrawDocument       *data,
    int		        selector,
    vdict               *context
    )
{
    vbool		set;
    vdomainObjectSet    *objectSet;
    vdomain             *domain;
    vtextStyle		*style;
    vtext		*editRec;
    const vchar         *option;
    vtextSelection	*selection;
#ifdef vmdrawDEBUG
    vpoint              bufpt;
#endif

    objectSet = vdomainGetObjectSet(vdomainviewGetDomain(data->domainView),
				    vdomainviewGetSelection(data->domainView),
				    vdomainSELECTED, NULL);
    domain    = vdomainviewGetDomain(data->domainView);
    option    = (const vchar *) vdictLoad(context, vmdraw_Option);
    
    switch (selector) {
	
    case comCLOSE_WINDOW:
	if (!vmdrawIsDocumentValid(data))
	    break;

	vmdrawDestroyDocument(data);
	break;

    case comSAVE:
	vmdrawSaveDocument(data, context);
	break;

    case comREVERT:
	break;

    case comSAVE_TEMPLATE:
        _vmdrawSetDocumentTemplate(data, &vmdrawTemplatePreferences);
	return(TRUE);

    case comPEN:
	vmdrawCreatePenWindow();
	vmdrawSetTargetDocument(data);
	break;

    case comPATTERN:
	vmdrawCreatePatternWindow();
	vmdrawSetTargetDocument(data);
	break;

    case comPOSITION:
	vmdrawCreatePositionWindow();
	break;

    case comSET_STYLE:
	vmdrawOpenStyleChooser();
	vstylechsrSetApply(vmdrawStyleChooser, vmdrawApplyStyle);
	vmdrawSetTargetDocument(data);
	break;

    case comDRAWING_SIZE:
        vmdrawSetDrawingSize(data);
        break;

    case comSET_GRID:
        vmdrawSetGrid(data);
        break;

    case comSHOW_HORIZONTAL_SCROLL_BAR:
	set = vdomainviewHasHorzBar(data->domainView) ? FALSE : TRUE;
	vdomainviewSetHorzBar(data->domainView, set);
        break;

    case comSHOW_VERTICAL_SCROLL_BAR:
	set = vdomainviewHasVertBar(data->domainView) ? FALSE : TRUE;
        vdomainviewSetVertBar(data->domainView, set);
        break;

    case comSHOW_LAYERING:
	data->viewSettings ^= vmdrawSHOW_LAYERING;
	vmdrawRecalcLayering(data);
	vdomainviewInval(data->domainView);
        break;

    case comOFFSCREEN_DRAWING:
	vdomainviewSetOffscreenDrawing(data->domainView,
			    !vdomainviewIsOffscreenDrawing(data->domainView));
	break;

    case comSNAP_TO_GRID:
	data->flags ^= vmdrawDOC_SNAP_TO_GRID;
	vdomainviewSetDragSnapToGrid(data->domainView,
			    (data->flags & vmdrawDOC_SNAP_TO_GRID) != 0);
	break;

    case comGRID_LINES:
	data->viewSettings ^= vmdrawVIEW_GRID_LINES;
	vdomainviewInval(data->domainView);
	break;

    case comMOVE:
        if (option == vmdraw_Front)
            vdomainLayerObjects(domain, objectSet, vdomainLAYER_TOFRONT);
        else if (option == vmdraw_Forward)
            vdomainLayerObjects(domain, objectSet, vdomainLAYER_FRONT);
        else if (option == vmdraw_Back)
            vdomainLayerObjects(domain, objectSet, vdomainLAYER_TOBACK);
        else if (option == vmdraw_Backward)
            vdomainLayerObjects(domain, objectSet, vdomainLAYER_BACK);
        else if (option == vmdraw_Target)
            vdomainShuffleObjects(domain, objectSet->objects[0],
                                  data->targetObject, TRUE);
	vdomainviewNotifyUndo(data->domainView, 
			      vcharScribeLiteral("Layering Change"));

	vmdrawRecalcLayering(data);

	break;

    case comALIGN:
        if (option == vname_Left)
            vdomainAlignObjects(domain, objectSet, data->alignOption,
                                vdomainALIGN_LEFT, vdomainALIGN_NONE);
        else if (option == vname_Right)
	    vdomainAlignObjects(domain, objectSet, data->alignOption,
                                vdomainALIGN_RIGHT, vdomainALIGN_NONE);
        else if (option == vname_Top)
            vdomainAlignObjects(domain, objectSet, data->alignOption,
                                vdomainALIGN_NONE, vdomainALIGN_TOP);
        else if (option == vname_Bottom)
            vdomainAlignObjects(domain, objectSet, data->alignOption,
                                vdomainALIGN_NONE, vdomainALIGN_BOTTOM);
        else if (option == vmdraw_Horizontal)
            vdomainAlignObjects(domain, objectSet, data->alignOption,
                                vdomainALIGN_CENTER, vdomainALIGN_NONE);
        else if (option == vmdraw_Vertical)
            vdomainAlignObjects(domain, objectSet, data->alignOption,
                                vdomainALIGN_NONE, vdomainALIGN_CENTER);
        else if (option == vmdraw_Grid)
            data->alignOption = vdomainALIGN_TO_GRID;
        else if (option == vmdraw_Objects)
            data->alignOption = vdomainALIGN_TO_OBJECTS;
	vdomainviewNotifyUndo(data->domainView, 
			      vcharScribeLiteral("Align"));
        break;

    case comDISTRIBUTE:
        if (option == vname_Left)
            vdomainDistributeObjects(domain, objectSet, 
                         vdomainDISTRIBUTE_LEFT, vdomainDISTRIBUTE_NONE);
        else if (option == vname_Right)
            vdomainDistributeObjects(domain, objectSet, 
			 vdomainDISTRIBUTE_RIGHT, vdomainDISTRIBUTE_NONE);
        else if (option == vname_Top)
            vdomainDistributeObjects(domain, objectSet, 
			 vdomainDISTRIBUTE_NONE, vdomainDISTRIBUTE_TOP);
        else if (option == vname_Bottom)
            vdomainDistributeObjects(domain, objectSet, 
			 vdomainDISTRIBUTE_NONE, vdomainDISTRIBUTE_BOTTOM);
        else if (option == vmdraw_Horizontal)
            vdomainDistributeObjects(domain, objectSet, 
			 vdomainDISTRIBUTE_CENTER, vdomainDISTRIBUTE_NONE);
        else if (option == vmdraw_Vertical)
            vdomainDistributeObjects(domain, objectSet, 
			 vdomainDISTRIBUTE_NONE, vdomainDISTRIBUTE_CENTER);
	vdomainviewNotifyUndo(data->domainView, 
			      vcharScribeLiteral("Distribute"));
        break;

    case comORIGIN_AT_TOP_LEFT:
        vdomainSetOrientation(vdomainviewGetDomain(data->domainView),
              vdomainGetOrientation(vdomainviewGetDomain(data->domainView))
                          == vdomainORIENT_TOP_LEFT ?
                          vdomainORIENT_BOTTOM_LEFT : vdomainORIENT_TOP_LEFT);
        break;

    case comSET_TARGET_OBJECT:
        if (objectSet->numObjects > 0)
            data->targetObject = objectSet->objects[0];
        break;
	
    case comZOOM_IN:
    case comZOOM_OUT:
	if (selector == comZOOM_IN) {
            data->scale *= 2;
            vmatrixScale(&data->matrix, 2, 2, &data->matrix);
        }
        else {
            data->scale /= 2;
            vmatrixScale(&data->matrix, 0.5, 0.5, &data->matrix);
        }

	vmdrawChangeDocumentState
            (data,  vnameInternGlobalScribed(vcharScribeLiteral("Zoom In")),
             (data->scale >= 3200 ? vname_Disabled : vname_Enabled));
        vmdrawChangeDocumentState
            (data,  vnameInternGlobalScribed(vcharScribeLiteral("Zoom Out")),
             (data->scale <= 12.5 ? vname_Disabled : vname_Enabled));

        vdomainviewSetMatrix(data->domainView, &data->matrix);
	vdialogInvalItem(data->scaleItem, 0);
	break;

    case comAPPLY_STYLE:
	vmdrawSetTargetDocument(data);
	option = (const vchar *) vdictLoad(context, vname_Attribute);
	if (option == NULL)
	    break;

	if (vmdrawTargetDocument->editingObject == NULL)
	    return(TRUE);

	editRec   = vtextviewGetTextData(vmdrawTargetDocument->editTextView);
	selection = vtextviewGetSelection(vmdrawTargetDocument->editTextView);

	if (option == vnameInternGlobalLiteral("Plain")) {

	    vtextUnapplyStyle(editRec, selection, NULL);
	}
	else {

	    const vname	  *onOrOff = vname_On;

	    /*
	     * Determine whether to turn the attribute on or off by
	     * getting the style at the start of the selection.  Do the
	     * opposite of what is set.
	     */

	    style = vtextStyleAtPosition(editRec, 
					 vtextSelectionStart(selection));

	    if (style != NULL) {
		if (vtextGetStyleAttribute(style, option) == vname_On)
		    onOrOff = vname_Off;
		vtextDestroyStyle(style);
	    }

	    style = vtextCreateStyle();
	    vtextSetStyleAttribute(style, option, onOrOff);
	    vmdrawApplyStyle(NULL, style);
	    vtextDestroyStyle(style);
	}
	break;

    case comAPPLY_JUSTIFICATION:
	vmdrawSetTargetDocument(data);
	option = (const vchar *) vdictLoad(context, vname_Attribute);
	vmdrawApplyJustification(option);
	break;

    case comAPPLY_CASE:
	vmdrawSetTargetDocument(data);
	option = (const vchar *) vdictLoad(context, vname_Attribute);

	if (vmdrawTargetDocument->editingObject == NULL)
	    return(TRUE);

	vobjectIssueCommand((vobject *) vmdrawTargetDocument->editTextView,
			    option, context);
	break;

#ifdef vmdrawDEBUG
    case comDUMP_OBJECTS:
	_vmdrawDumpObjects(data, objectSet);
	break;

    case comDRAG:
        option = (const vchar *) vdictLoad(context, vmdraw_Option);
        if (option == vmdraw_All)
            vdomainviewSetDragOutline(data->domainView,
                                      vdomainviewOUTLINE_ALL);
        else if (option == vmdraw_Limit)
            vdomainviewSetDragOutline(data->domainView,
                                      vdomainviewOUTLINE_LIMITRECT);
        else if (option == vmdraw_Two)
            vdomainviewSetDragOutline(data->domainView,
                                      vdomainviewOUTLINE_TWO);
        else if (option == vmdraw_None)
            vdomainviewSetDragOutline(data->domainView, 
                                      vdomainviewOUTLINE_NONE);
        else if (option == vmdraw_Normal)   
            vdomainviewSetDragMethod(data->domainView,
                                     vdomainviewDRAG_NORMAL);
        else if (option == vmdraw_Auto)
            vdomainviewSetDragMethod(data->domainView,
                                     vdomainviewDRAG_AUTOSCROLL);
        else if (option == vmdraw_External)
            vdomainviewSetDragMethod(data->domainView,
                                     vdomainviewEXTERNAL_DRAG);
        break;

    case comSELECTION:
        option = (const vchar *) vdictLoad(context, vmdraw_Option);
        if (option == vmdraw_Enclose)
            vdomainviewSetSelectEnclosed(data->domainView,
                            !vdomainviewIsSelectEnclosed(data->domainView));
        else if (option == vmdraw_Single)
            vdomainviewSetSingleSelection(data->domainView,
                            !vdomainviewIsSingleSelection(data->domainView));
        else if (option == vmdraw_Live)
            vdomainviewSetLiveSelection(data->domainView,
                            !vdomainviewIsLiveSelection(data->domainView));
        break;

    case comVIRTUAL_BOUNDS:
        bufpt.x = bufpt.y = 10;
        vdomainSetVirtualBuffer(vdomainviewGetDomain(data->domainView),
                                 &bufpt);
        vdomainSetVirtualBounds(vdomainviewGetDomain(data->domainView),
            !vdomainGetVirtualBounds(vdomainviewGetDomain(data->domainView)));;
        break;
#endif

#if (mdrawUSE_DAS)
    case  comREGISTER:
	mdrawRegisterDocument(data);
	break;

    case  comUNREGISTER:
	mdrawUnregisterDocument(data);
	break;
#endif

    default:
        vdomainDestroyObjectSet(objectSet);
        return vclassSendSuper(defaultDocumentClass,
                               vobjectISSUE_SELECTOR,
                               (data, selector, context));
    }

    vdomainDestroyObjectSet(objectSet);

    return(TRUE);
}

static int _vmdrawQueryDocumentCommand(
    vmdrawDocument      *data,
    int		        selector,
    vdict               *context
    )
{
    const vchar         *option;
    const vname		*name;
    vbool		on;

    /* So we don't crash when the menu bar unmaps its
     * keys - and our domain is already destroyed 
     */
    if (vdomainviewGetDomain(data->domainView) == NULL)
	return(TRUE);

    switch (selector) {
	
    case comZOOM_IN:      
        name = (data->scale > 3200 ? vname_Disabled : vname_Enabled);
        vdictStore(context, vname_State, name);
        break;

    case comZOOM_OUT:    
        name = (data->scale < 12.5 ? vname_Disabled : vname_Enabled);
        vdictStore(context, vname_State, name);
        break;

    case comSAVE:       
        if ( ( !vundoIsLogSaved(data->undoLog) &&
              (data->flags & vmdrawDOC_READ_ONLY) == 0 ) ||
            data->fileSpec == vresourceNULL ||
	    vdictLoad(context, vmdraw_Option) != NULL)
            name = vname_Enabled;
        else
            name = vname_Disabled;

        vdictStore(context, vname_State, name);
        break;

    case comSHOW_HORIZONTAL_SCROLL_BAR:
        vdictStore(context, vname_Toggle, (vchar *)
                   (vdomainviewHasHorzBar(data->domainView) ?
                   vname_On: vname_Off));
        break;

    case comSHOW_VERTICAL_SCROLL_BAR:
        vdictStore(context, vname_Toggle, (vchar *)
                   (vdomainviewHasVertBar(data->domainView) ?
                   vname_On: vname_Off));
        break;

    case comSNAP_TO_GRID:
	vdictStore(context, vname_Toggle, (vchar *)
		   (vdomainviewIsDragSnapToGrid(data->domainView) ?
		    vname_On : vname_Off));
	break;

    case comOFFSCREEN_DRAWING:
	vdictStore(context, vname_Toggle, (vchar *)
		   (vdomainviewIsOffscreenDrawing(data->domainView) ?
		    vname_On : vname_Off));
	break;

    case comGRID_LINES:
	vdictStore(context, vname_Toggle, (vchar *)
		   ((data->viewSettings & vmdrawVIEW_GRID_LINES) ?
		    vname_On : vname_Off));
	break;

    case comSHOW_LAYERING:
	vdictStore(context, vname_Toggle, (vchar *)
		   ((data->viewSettings & vmdrawSHOW_LAYERING) ?
		    vname_On : vname_Off));
	break;

    case comDRAG:
        option = (const vchar *) vdictLoad(context, vmdraw_Option);
        if (option == vmdraw_All)
            on = (vdomainviewGetDragOutline(data->domainView)
		  == vdomainviewOUTLINE_ALL);
        else if (option == vmdraw_Limit)
            on = (vdomainviewGetDragOutline(data->domainView)
                  ==  vdomainviewOUTLINE_LIMITRECT);
        else if (option == vmdraw_Two)
            on = (vdomainviewGetDragOutline(data->domainView)   
                  == vdomainviewOUTLINE_TWO);
        else if (option == vmdraw_None)
            on = (vdomainviewGetDragOutline(data->domainView)
                  == vdomainviewOUTLINE_NONE);
        else if (option == vmdraw_Normal)   
            on = (vdomainviewGetDragMethod(data->domainView)
                 == vdomainviewDRAG_NORMAL);
        else if (option == vmdraw_Auto)
            on = (vdomainviewGetDragMethod(data->domainView)
                  == vdomainviewDRAG_AUTOSCROLL);
        else if (option == vmdraw_External)
            on = (vdomainviewGetDragMethod(data->domainView)
                  == vdomainviewEXTERNAL_DRAG);
        else
            break;
	vdictStore(context, vname_Toggle, on ? vname_On : vname_Off);
        break;

    case comSELECTION:
        option = (const vchar *) vdictLoad(context, vmdraw_Option);
        if (option == vmdraw_Enclose)
            on = vdomainviewIsSelectEnclosed(data->domainView);
        else if (option == vmdraw_Single)
            on = vdomainviewIsSingleSelection(data->domainView);
        else if (option == vmdraw_Live)
            on = vdomainviewIsLiveSelection(data->domainView);
        else
            break;
	vdictStore(context, vname_Toggle, on ? vname_On : vname_Off);
        break;

    case comALIGN:
        option = (const vchar *) vdictLoad(context, vmdraw_Option);
        if (option == vmdraw_Grid)
            on = (data->alignOption == vdomainALIGN_TO_GRID);
        else if (option == vmdraw_Objects)
            on = (data->alignOption == vdomainALIGN_TO_OBJECTS);
        else
            break;
	vdictStore(context, vname_Toggle, on ? vname_On : vname_Off);
        break;

    case comORIGIN_AT_TOP_LEFT:
        vdictStore(context, vname_Toggle, 
	     vdomainGetOrientation(vdomainviewGetDomain(data->domainView))
		   == vdomainORIENT_TOP_LEFT ?
		   vname_On : vname_Off);
        break;

    case comVIRTUAL_BOUNDS:
        vdictStore(context, vname_Toggle, 
	     vdomainGetVirtualBounds(vdomainviewGetDomain(data->domainView)) ?
		   vname_On : vname_Off);
        break;

    case comAPPLY_JUSTIFICATION:
        {
	    vdomain			*domain;
	    vdomainObject		*scan = NULL;
	    vdomainSelection		selection;
	    const vname			*tag;

	    domain    = vdomainviewGetDomain(data->domainView);
	    selection = vdomainviewGetSelection(data->domainView);
	    tag       = vname_Disabled;

	    if (domain != NULL)
		scan = vdomainTopObject(domain);
	    
	    while (scan != NULL) {
		
		if (vdomainGetObjectType(domain, scan) == vmdrawTEXT_TOOL &&
		    vdomainIsObjectSelected(domain, selection, scan)) {
		    tag = vname_Enabled;
		    break;
		}
		
		scan = vdomainNextObjectBehind(scan);
	    }

	    vdictStore(context, vname_State, tag);
	}
	break;

    case comAPPLY_STYLE:
    case comAPPLY_CASE:
	vdictStore(context, vname_State, data->editingObject != NULL
		   ? vname_Enabled : vname_Disabled);
	break;
    }

    if (selector > vdialogNEXT_SELECT && selector < comMAX_DOC_SELECTOR)
	return(TRUE);

    return vclassSendSuper(defaultDocumentClass,
			   vobjectQUERY_SELECTOR,
			   (data, selector, context));
}

/* * * * * *   STARTUP AND SHUTDOWN * * * * * */

/*
 * vmdrawDocumentStartup
 *
 * One-time setup of all document classes, commands, and more
 */
void vmdrawDocumentStartup()
{
    int			i;
    vresource   	res;

    /*
     * Initialize the document command space 
     */

    _vmdrawInitDocumentSpace();

    /*
     * Setup the document dialog class - handles cleaning up when
     * the document is destroyed, as well as the issue and query 
     * selectors
     */

    defaultDocumentClass = vclassSpawn(vdialogGetDefaultClass(),
				       sizeof(vmdrawDocumentClass));
	
    vclassSetNameScribed(defaultDocumentClass,
                         vcharScribeLiteral("vmdrawDocument"));
    vclassSetObjectSize(defaultDocumentClass, sizeof(vmdrawDocument));

    vclassSet(defaultDocumentClass,
              vobjectDESTROY,                   _vmdrawDestroyDocument);
    vclassSet(defaultDocumentClass, 
              vobjectSPACE,                     &defaultSpace);
    vclassSet(defaultDocumentClass,
	      vobjectKEY_MAP,			&defaultKeyMap);
    vclassSet(defaultDocumentClass, 
              vobjectISSUE_SELECTOR,            _vmdrawIssueDocumentCommand);
    vclassSet(defaultDocumentClass,
              vobjectQUERY_SELECTOR,            _vmdrawQueryDocumentCommand);

    /*
     * Setup our special dialog item that show scaling
     */

    defaultItemClass = vclassReproduce(vdialogGetBoxItemClass());
	
    vclassSetNameScribed(defaultItemClass,
                         vcharScribeLiteral("vmdrawDialogItem"));

    vclassSet(defaultItemClass,
              vdialogDRAW_ITEM_WITH,		_vmdrawDrawScaleItemWith);

    /*
     * Setup the palette item class.  We need to be able to draw the
     * selected background of a palette item in 2 ways, temporarily selected
     * and permanently selected
     */

    defaultPaletteClass = vclassReproduce(vpaletteGetDefaultClass());
	
    vclassSetNameScribed(defaultPaletteClass,
                         vcharScribeLiteral("vmdrawPalette"));

    vclassSet(defaultPaletteClass,
              vlistviewDRAW_CELL_BACKGROUND_WITH,
	      _vmdrawDrawPaletteBackgroundWith);
    vclassSet(defaultPaletteClass,
              vdialogHANDLE_ITEM_BUTTON_DOWN,   _vmdrawPaletteButtonDown);

    /*
     * Create the domain observer class - we need to monitor any selection
     * changes
     */

    defaultObserverClass = vclassReproduce(vdomainGetDefaultObserverClass());
    
    vclassSetNameScribed(defaultObserverClass,
                         vcharScribeLiteral("vmdrawObserverClass"));

    vclassSet(defaultObserverClass,
	      vdomainObserverSELECT,		_vmdrawObserverSelect);
    
    /*
     * Setup the position dialog's position item, displaying the current
     * position of the mouse in document coordintes for the docuemnt
     * the mouse is currently over
     */

    defaultPosItemClass = vclassReproduce(vdialogGetDefaultItemClass());
	
    vclassSetNameScribed(defaultPosItemClass,
                         vcharScribeLiteral("vmdrawPosItem"));

    vclassSet(defaultPosItemClass,
              vdialogDRAW_ITEM_WITH,		_vmdrawDrawPosItemWith);

    /*
     * Setup the window menu item class - to draw the window menu with
     * state icons next to the entries
     */

    defaultWindowMenuItemClass = vclassReproduce(vmenuGetDefaultItemClass());
    vclassSetNameScribed(defaultWindowMenuItemClass,
			 vcharScribeLiteral("vmdrawWindowMenuItem"));
    vclassSet(defaultWindowMenuItemClass,
	      vmenuDRAW_ITEM_WITH,		_vmdrawDrawWindowMenuItemWith);

    for (i=0; i<vmdrawMAX_DOCUMENTS; i++)
        _vmdrawNewSlots[i] = 0;
    _vmdrawNewSlots[0] = 1;

    defaultWindowMenu = vmenuLoad(vresourceGet
		     (vmdrawResFile, vnameInternGlobalLiteral("WindowMenu")));
     
    offscreenImage = vwindowCreateBufferImage(77, 50);

    vmdrawEdgeColor = vresourceTestGet(vmdrawResFile,
		   vnameInternGlobalLiteral("Edge Color"), &res) ?
		   vcolorLoadIntern(res) : NULL;

    _vmdrawInitStateDictionaries();
}

/*
 * vmdrawDocumentShutdown
 *
 * Cleanup after ourselves
 */
void vmdrawDocumentShutdown()
{
    vdictDestroy(&selectionState);
    vdictDestroy(&noselectionState);
    vdictDestroy(&standardState);

    vmenuDestroy(defaultWindowMenu);

    vimageDestroy(offscreenImage);

    vcommandDestroySpace(&defaultSpace);
    vcommandDestroySpace(tempSpace);
    vcommandDestroyDict(&defaultFocusCommands);
    vdictDestroy(&defaultKeyMap);

    offscreenImage = NULL;
}

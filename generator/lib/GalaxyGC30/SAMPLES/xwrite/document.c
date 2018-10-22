/* $Id: document.c,v 1.17 1997/09/23 17:59:57 dimitri Exp $ */

/************************************************************

    document.c
    C Source to xwrite

    (c) Copyright Visix Software Inc.
    All rights reserved

************************************************************/
 
#include "micwrite.h"

#if vdebugDEBUG
#define vdebugTAG "xwriteDocument"
#endif

static writeDocumentClass	*defaultDocumentClass;
static vdialogItemClass		*defaultRibbonClass;
static vtextrulerClass		*defaultTextRulerClass;
static vtextviewClass		*defaultTextViewClass;
static vdialogItemClass		*defaultIconBoxClass;
static vmenuItemClass		*defaultWindowMenuItemClass;
       vtextClass		*defaultTextClass;

static vcommandSpace     	defaultSpace, *tempSpace;
static vdict		 	defaultFocusCommands;
static vimage			*modifiedImage, *readOnlyImage;
static vimage			*offscreenImage;
static vbyteSigned		_writeNewSlots[writeMAX_DOCUMENTS + 1];
static vdict            	selectionState, noselectionState;
static vdict		 	standardState;
static vnotice 			*_alert = NULL;
static vtextStyle               *_chooserStyle = NULL;

#if writeDEBUG
static vbool			clickStyleInfo = FALSE;
#endif

static void             _writeUndoNotify(vtextview *, vundoAction *);
static void             _writeTextNotify(vtextview *, vevent *, int);
static int 		_writeSaveAndCloseNotify(vfilechsr *, vfsPath*);

static int _closeHook(vdialog *d, vevent *ev)
{
    writeDocument	*data = (writeDocument *) d;
    
    if (writeIsDocumentValid(data)) {
	writeDestroyDocument(data);
	return(FALSE);
    }
    else
	return(TRUE);
}

/*
 * _writeCreateDocument
 *
 * Called by writeNewDocument and writeOpenDocument to obtain a new
 * initialized document (dialog) in which to draw in.  Reads the
 * dialog in from the resource file, and then sets up the document data
 */
static writeDocument *_writeCreateDocument(
    writeTemplatePreferenceData	*prefs
    )
{
    writeDocument   		*data;
    vtextStyle          	*style;	
    vtextRuler			*ruler;
    vtextSelection      	*selection;
    vtext			*editRec;
    vcommandSpace		*space;
    writeStyle			*scan;
#ifndef writeDEBUG
    vmenu               *menu;
#endif

    data = (writeDocument *) writeLoadDialog(vname_Document);

    /*
     * Add the document to the list of documents
     */

    data->next = writeDocumentList;
    writeDocumentList = data;

    /*
     * Initialize the document data
     */

    data->fileSpec      = vresourceNULL;
    data->newIndex	= 0;
    data->styleCount	= 0;
    data->undoLog	= vundoCreateLog();
    data->markList	= NULL;
    data->styleList	= NULL;
    data->name		= NULL;
    data->flags		= writeTemplatePreferences.flags;

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

    data->ruler 	= (vtextruler *) 
                          vdialogFindItem(&data->dialog, write_Ruler);

    data->iconBox 	= vdialogFindItem(&data->dialog, write_IconBox);

    data->ribbon        = vdialogFindItem(&data->dialog, write_Ribbon);

    data->combo         = (vcombo *)
                          vdialogFindItem(&data->dialog, vtext_Styles);

    vdialogSetItemData(data->iconBox, data);
    vdialogSetItemData(data->ribbon, data);
    vtextrulerSetData(data->ruler, data);

    scan = writeStyleList;
    while (scan != NULL) {
        vcomboAppendText(data->combo, scan->name);
        scan = scan->next;
    }

    vcomboSelectText(data->combo, write_Normal);

    /*
     * Now create the view record
     */

    data->textItem = (vtextview *)
        vdialogFindItem(&data->dialog, vname_TextView);
    vtextviewSetHorzBar(data->textItem, TRUE);
    vtextviewSetVertBar(data->textItem, TRUE);
    vtextviewSetData(data->textItem,    data);

    data->menuBar    = (vmenubar *) 
                       vdialogFindItem(&data->dialog, vname_MenuBar);
    data->markMenu   = vmenubarFindMenu(data->menuBar, 
				     vnameInternGlobalLiteral("ToolsMenu"));
    data->markMenu   = vmenuGetItemSubMenu(vmenuFindItem(data->markMenu,
			   vnameInternGlobalLiteral("MarkersMenu")));
    data->windowMenu = vmenubarFindMenu(data->menuBar,
				     vnameInternGlobalLiteral("WindowMenu"));
    vmenuSetData(data->markMenu, data);

#ifndef writeDEBUG
    menu = vmenubarFindMenu(data->menuBar,
                            vnameInternGlobalLiteral("DebugMenu"));
    vmenubarDeleteMenu(data->menuBar, menu);
    vmenuDestroy(menu);
#endif

    /*
     * Create a marker menu for the text view dialog item popup menu
     */
     
    data->popupMarkMenu = vmenuCreate();
    vmenuSetData(data->popupMarkMenu, data);
    vdialogSetItemMenu(vtextviewGetItem(data->textItem), data->popupMarkMenu);

    vdialogSetDefFocus(&data->dialog,
		       vtextviewGetItem(data->textItem));
    
    /*
     * Set up the text view and text data objects
     */

    editRec   = vtextCreateOfClass(defaultTextClass);
    selection = vtextCreateSelection(editRec);
    vtextSetData(editRec, data);
    vtextviewSetTextData(data->textItem, editRec);
    vtextviewSetSelection(data->textItem, selection);
    vtextviewSetUndoNotify(data->textItem, 	_writeUndoNotify);
    vtextviewSetNotify(data->textItem,		_writeTextNotify);

    style = vtextCreateStyle();
    vtextCopyStyle(writeNormalStyle->style, style);
    vtextSetDefaultStyleOwned(editRec, style);

    /*
     * Add the default write ruler
     */

    ruler = vtextCreateRuler();
    vtextSetRulerRightIndent(editRec, ruler, vfixedFromInt(400));
    vtextSetRulerWrap(editRec, ruler, TRUE);
    vtextSetRulerTabWidth(editRec, ruler, vfixedFromInt(48));
    vtextSetDefaultRulerOwned(editRec, ruler);

    /* Set up the text ruler */

    vtextrulerSetTextData(data->ruler, editRec);
    vtextrulerSetSelection(data->ruler, selection);

    /*
     * Add the undo observer
     */

    vtextSetUndoObserver(editRec, vtextGetDefaultUndoObserverClass()); 

    /*
     * Add the focus command dictionary to the dialog's command space, so
     * that these command get redirected to the focus item
     */
    
    space = vclassGet(vdialogGetClass(&data->dialog), vobjectSPACE);
    vcommandAddSpaceDict(space, vname_Command, &defaultFocusCommands);
    
    vdialogSetCloseHook(&data->dialog, _closeHook);

    return(data);
}

/*
 * _writeSetDocumentTemplate
 */
static void _writeSetDocumentTemplate(
    writeDocument		 *data,
    writeTemplatePreferenceData  *templ
    )
{
    templ->newDocumentRect      = *vwindowGetRect((vwindow *) data);
    templ->flags        	= data->flags;
}

/*
 * _writeRegisterUntitled
 *
 * Register a new untitled document. Find a uniqued Untitled "#" to 
 * assign the document (stored in "newIndex", then creates and sets
 * the title appropriately
 */
static void _writeRegisterUntitled(writeDocument *data)
{
    vstr		*title;
    int                 i;

    /*
     * Assign a unique "new" index for the scratch data
     */

    for (i=0; i<writeMAX_DOCUMENTS; i++) {
        if (_writeNewSlots[i] == 0) {
            _writeNewSlots[i] = 1;
            break;
        }
    }
    data->newIndex = i;
    title = vresourceGetStringAt(writeMessages, writeMSG_UNTITLED);
    (void) vstrAppendScribed(title, vnumScribeInt(data->newIndex));
    data->name = title;
}

/*
 * writeNewDocument
 * 
 * Create a new empty edit record
 */
void writeNewDocument(void)
{
    writeDocument	*data;
    vtext	 	*editRec;
    const vrect		*r;

    /*
     * Set up an empty text data record
     */

    data                = _writeCreateDocument(&writeTemplatePreferences);
    editRec		= vtextviewGetTextData(data->textItem);
    data->fileSpec 	= vresourceNULL;

    vtextAppendBlock(editRec, vmemAlloc(vtextTEXT_BLOCK_SIZE * sizeof(vchar)),
		     0, vtextTEXT_BLOCK_SIZE);
    vtextCalculate(editRec);

    _writeRegisterUntitled(data);

    vdialogSetTitle(&data->dialog, data->name);

    if (writeTemplatePreferences.newDocumentRect.y != 0)
        vwindowSetRect((vwindow *) data,
                       &writeTemplatePreferences.newDocumentRect); 
    else {
        writeCenterWindow(vdialogGetWindow(&data->dialog));
    }

    /* If there is a window already open, place it wrt that window */

    if (wrtDialog != NULL) {
        r = vwindowGetRect((vwindow *) vdialogGetWindow(wrtDialog));
        vwindowMove(vdialogGetWindow(&data->dialog), r->x + 30, r->y - 30);
    }

    vwindowSetSpace((vwindow *) data, data->space);

    writeSetDocumentIcon(data, writeDOC_READ_ONLY, FALSE);
 
    /* Rebuild the window menu */

    writeBuildWindowMenus();

    _alert = NULL;

    vdialogOpen(&data->dialog);
}

/*
 * writeOpenDocument
 *
 * open a new document and read in the specified file into it
 */
void writeOpenDocument(
    const  vfsPath		*filePath
    )
{
    writeDocument		*data;
    vtext			*editRec, *oldEditRec;
    vstr               		*str;
    volatile vresource		 fileSpec;
    volatile unsigned short	 flags = 0;
    writeTemplatePreferenceData  templ;

    if (!vfsAccess(filePath, vfsFILE_EXISTS))
        return;

    _alert = NULL;

    vexWITH_HANDLING {

        if (!vfsAccess(filePath, vfsCAN_WRITE)) {
            fileSpec = vresourceOpenFile(filePath, vfsOPEN_READ_ONLY);
            flags |= writeDOC_READ_ONLY;
        }
        else {
            fileSpec = vresourceOpenFile(filePath, vfsOPEN_READ_WRITE);
            flags &= ~writeDOC_READ_ONLY;
        }
    }
    vexON_EXCEPTION {
        
        writeImportDocument(filePath, xcharsetFindSystem(), 
			    xctransORDER_IMPLICIT);
	vexClear();

        str = vresourceGetStringAt(writeMessages, writeMSG_IMPORTING);
        _alert = writeAlert(NULL, str);
        vstrDestroy(str);

	return;
    }
    vexEND_HANDLING;

    templ  = writeTemplatePreferences;

    writeLoadTemplate(fileSpec, &templ);

    data 		= _writeCreateDocument(&templ);
    data->fileSpec 	= fileSpec;
    data->name          = vstrClone(vfsGetPathElementAt(filePath,
				      vfsGetPathElementCount(filePath)-1));
    data->flags        |= flags;
 
    /*
     * Load up the document - first the text and styles itself
     */

    oldEditRec = vtextviewGetTextData(data->textItem);

    vexWITH_HANDLING {

	editRec    = vtextLoad(data->fileSpec);
	
	vtextviewSetTextData(data->textItem, editRec);
	vtextviewSetSelection(data->textItem, vtextCreateSelection(editRec));

	vtextrulerSetTextData(data->ruler, editRec);
	vtextrulerSetSelection(data->ruler, vtextviewGetSelection(data->textItem));
	vtextSetData(editRec, data);

	vtextDestroy(oldEditRec);

    }
    vexON_EXCEPTION {

        str = vresourceGetStringAt(writeMessages, writeMSG_READ_ERROR);
        _alert = writeAlert(NULL, str);
        vstrDestroy(str);

	editRec  = oldEditRec;

	data->fileSpec = vresourceNULL;
    }
    vexEND_HANDLING;

    vtextSetUndoObserver(editRec, vtextGetDefaultUndoObserverClass());

    vtextSelectRange(editRec, vtextviewGetSelection(data->textItem), 0, 0);

    /*
     * Now load the markers
     */

    writeLoadMarkers(data, data->fileSpec);
 
    vwindowSetRect((vwindow *) data, &templ.newDocumentRect);
    
    vwindowSetSpace((vwindow *) data, data->space);

    vdialogSetTitle(&data->dialog, data->name);

    writeSetDocumentIcon(data, writeDOC_READ_ONLY,
                         (vbool)((data->flags & writeDOC_READ_ONLY) != 0));

    /* Rebuild the window menu */

    writeBuildWindowMenus();

    vdialogOpen(&data->dialog);
}

void _writeImportNotifyProc(xctrans *trans, int level, vscribe *msg)
{
   fprintf(vdebugGetWarningStream(), "xctrans notice, level %d:", level);
   vcharDumpScribed(msg, vdebugGetWarningStream());
   fputc('\n', vdebugGetWarningStream());

}


/*
 * writeImportDocument
 *
 * Import a text file
 */
void writeImportDocument(
    const  vfsPath		*filePath,
    int                          charset,
    int                          byteOrder
    )
{
   writeDocument	*data;
   vtext		*editRec;
   vchar		*remainLineBuffer, *newText, *start, *end;
   vchar		*lastEOL, *ultimateEOL;
   vbool		done = vFALSE, lineTooLong = vFALSE;
   long  		currentLength = 0, currentLengthToEOL, 
                        availableLength, length;
   vfsFile		*fileSpec;
   short		remainLineBufferSize = 0;
   const vrect		*r, *dr;
   
   xctrans             *trans;
   
   if (!vfsAccess(filePath, vfsCAN_READ))
      return;
   
   data = _writeCreateDocument(&writeTemplatePreferences);
   
   fileSpec = vfsOpenFile(filePath, vfsOPEN_READ_ONLY);

   editRec     = vtextviewGetTextData(data->textItem);
   _alert	= NULL;
   
   trans = xctransCreate();
   xctransSetEOL(trans, vtextEOLN);
   xctransSetCharset(trans, charset);
   xctransSetByteOrder(trans, byteOrder);
   xctransSetNotify(trans, _writeImportNotifyProc);
   
   /*
    * remainLineBuffer is a temporary buffer, used to keep around remaining
    * parts of lines, since text in a text block must be separated on
    * line boundaries.
    */
   
   remainLineBuffer = vmemAlloc(vtextTEXT_BLOCK_SIZE * sizeof(vchar));
   remainLineBufferSize = 0;
   
   while (!done) 
      {
	 newText = vmemAlloc(vtextTEXT_BLOCK_SIZE * sizeof(vchar));

	 ultimateEOL = newText;
	 
	 /*
	  * Place any text that is in the remainLine buffer 
	  * into the new text block.
	  */
	 
	 (void)vmemCopy(remainLineBuffer, newText, 
			remainLineBufferSize * sizeof(vchar));
	 
	 availableLength = vtextINIT_TEXT_SIZE - remainLineBufferSize;
	 
	 end = newText + remainLineBufferSize;
	 
	 while (availableLength > 0)
	    {
	       start = end;
	       lastEOL = start;
	       end = xctransReadFromFile(trans, fileSpec, start, 
					 vMIN(availableLength, 
					      xctransBUFFER_SIZE),
					 &lastEOL
					 );
	       
	       /*
		* update ultimate EOL if an EOL delimiter was found
		*/

	       if (lastEOL > start) 
		  {
		     ultimateEOL = lastEOL;
		  }

	       if ((length = end - start) == 0)
		  {
		     done = vTRUE;  /* EOF */
		     break;
		  }
	       
	       availableLength -= length;
	    }
	 
	 if (!done)
	    {
	       currentLength = end - newText;
	       currentLengthToEOL = ultimateEOL - newText;
	       
	       if (currentLengthToEOL == 0) 
		  {
		     /*
		      * no EOL in text block, add one at the end of block
		      */
		     lineTooLong = vTRUE;
		     currentLength++;
		     currentLengthToEOL = currentLength;
		  }
	       
	       remainLineBufferSize = currentLength - currentLengthToEOL;
	       (void)vmemCopy(newText + currentLengthToEOL, remainLineBuffer, 
			      remainLineBufferSize * sizeof(vchar));
	       
	       /*
		* add the extra EOL, if necessary
		*/
	       
	       if (lineTooLong)
		  *(newText + (currentLength-1)) = vtextEOLN;
	    }
	 else	       
	    {  
	       /*
		* if last block, include all text regardless
		*/
	       currentLengthToEOL = end - newText;
	    }
	 
	 vtextAppendBlock(editRec, newText, currentLengthToEOL,
			  vtextTEXT_BLOCK_SIZE);
      }
   
   xctransDestroy(trans);
   
   vmemFree(remainLineBuffer);
   
   vtextCalculate(editRec);
   
   _writeRegisterUntitled(data);
   
   vdialogSetTitle(&data->dialog, data->name);
   
   if (writeTemplatePreferences.newDocumentRect.y != 0)
      vwindowSetRect((vwindow *) data,
		     &writeTemplatePreferences.newDocumentRect); 
   else 
      {
	 r  = vwindowGetRect(vwindowGetRoot());
	 dr = vwindowGetRect(vdialogGetWindow(&data->dialog));
	 vwindowMove(vdialogGetWindow(&data->dialog),
		     r->x + (r->w - dr->w) / 2,
		     r->y + (r->h - dr->h) / 2);
      }
   
   /* If there is a window already open, place it wrt that window */
   
   if (wrtDialog != NULL) 
      {
	 r = vwindowGetRect((vwindow *) vdialogGetWindow(wrtDialog));
	 vwindowMove(vdialogGetWindow(&data->dialog), r->x + 30, r->y - 30);
      }
   
   vwindowSetSpace((vwindow *) data, data->space);
   
   writeSetDocumentIcon(data, writeDOC_READ_ONLY, FALSE);
   
   /* Rebuild the window menu */
   
   writeBuildWindowMenus();
   
   vdialogOpen(&data->dialog);
}

/* * * * * * * * *  Validating a Document * * * * * * * */

static int _saveChanges(
    vnotice		*notice,
    vevent		*event
    )
{
    writeDocument	*data = (writeDocument *) vnoticeGetData(notice);
    
    if (writeSaveDocument(data, NULL) != writeDID_SAVE_AS)
	writeDestroyDocument(data);
    else
	vfilechsrSetApply(writeSaveWindow, _writeSaveAndCloseNotify);
	
    return(TRUE);
}

static int _closeAnyway(
    vnotice		*notice,
    vevent		*event
    )
{
    writeDocument	*data = (writeDocument *) vnoticeGetData(notice);

    writeDestroyDocument(data);
    return(TRUE);
}

/*
 * writeIsDocumentValid
 *
 * vdialogDESTROY method for draw documents.  Checks for saving before
 * close the file.
 */
vbool writeIsDocumentValid(
    writeDocument	*data
    )
{
    vstr                *str;

    if (!vundoIsLogSaved(data->undoLog) &&
        (data->flags & writeDOC_READ_ONLY) == 0) {

        str = vresourceGetStringAt(writeMessages, writeMSG_SAVE_CHANGES);
	writeReplaceStrings(&str, vcharScribe(data->name), NULL);
        writeConfirmation(&data->dialog, str, _saveChanges, _closeAnyway);
        vstrDestroy(str);

	return(FALSE);
    }

    return(TRUE);
}

/* * * * * * * * *  Destroying a Document * * * * * * * */

/*
 * _writeDestroyDocument
 */
static void _writeDestroyDocument(
    writeDocument	*data
    )
{
    writeDocument		*prev;

    writeTemplatePreferenceData templ;

    if (data->fileSpec != vresourceNULL &&
	(data->flags & writeDOC_READ_ONLY) == 0) {

        _writeSetDocumentTemplate(data, &templ);
        writeStoreTemplate(data->fileSpec, &templ);

    }

    /*
     * Remove the document from the list of documents
     */

    if (data == writeDocumentList)
        writeDocumentList = data->next;
    else {
        prev = writeDocumentList;
        while (prev->next != NULL) {
            if (prev->next == data) {
                prev->next = data->next;
                break;
            }
	    prev = prev->next;
        }
    }

    writeRemoveAllMarkers(data);

    if (data == writeGetTargetDocument())
	writeSetTargetDocument(NULL);

    if (writeStyleChooser != NULL &&
	data == (writeDocument *) vstylechsrGetData(writeStyleChooser))
	vstylechsrSetData(writeStyleChooser, NULL);

    /*
     * Close the resource file associated with the document OR if it 
     * is a Untitled documents, free up the untitled slot
     */

    if (data->fileSpec == vresourceNULL)
        _writeNewSlots[data->newIndex] = 0;
    else
        vresourceCloseFile(data->fileSpec);

    /*
     * Reset the window command space
     * Query Selector uses this as a shutdown sign
     */

    vwindowSetSpace((vwindow *) data, NULL);

    /*
     * Destroy the text data, the undo log,
     * the command space, the standard state dict.
     */
    
    vtextDestroy(vtextviewGetTextData(data->textItem));
    vundoDestroyLog(data->undoLog); 

    vcommandRemoveSpaceDict(data->space, vname_State, data->standardState);
    vdictDestroy(data->standardState);
    vcommandDestroySpace(data->space);

    vstrDestroy(data->name);

    /* 
     * Rebuild the window menu 
     */

    writeBuildWindowMenus();

    if (writeDocumentList == NULL)
        veventStopProcessing();

    vclassSendSuper(defaultDocumentClass, vobjectDESTROY, (data));
}

/* * * * * * * * *  Saving a Document * * * * * * * */

static int _writeSaveNotify(
    vfilechsr		*chooser,
    vfsPath		*filePath
    )
{
    writeDocument	*data;
    const vchar         *oldTitle;

    if (vfsAccess(filePath, vfsFILE_EXISTS)) {

	vfsRemove(filePath);
    }
    else {

        vfsCreateFile(filePath, vfsOWNER_WRITE | vfsOWNER_READ);
    }
    
    data = (writeDocument *) vfilechsrGetData(chooser);

    if (data->fileSpec != vresourceNULL)
        vresourceCloseFile(data->fileSpec);

    data->fileSpec = vresourceCreateFile(filePath, 
                                         vfsOWNER_READ | vfsOWNER_WRITE);
    vstrDestroy(data->name);
    data->name  = vstrClone(vfsGetPathElementAt(filePath,
				      vfsGetPathElementCount(filePath)-1));

    oldTitle = vwindowGetTitle(vdialogGetWindow(&data->dialog));
    if (vcharCompare(data->name, vdialogGetTitle(&data->dialog))) {
 
       vdialogSetTitle(&data->dialog, data->name);

        /* Rebuild the window menu */
	writeBuildWindowMenus();
    }

    if (data->newIndex >= 0) {
        _writeNewSlots[data->newIndex] = -1;
        data->newIndex = -1;
    }

    writeSaveDocument(data, NULL);

    return(TRUE);
}

static int _writeSaveAndCloseNotify(
    vfilechsr		*chooser,
    vfsPath		*filePath
    )
{
    writeDocument *data = (writeDocument *) vfilechsrGetData(chooser);

    _writeSaveNotify(chooser, filePath);

    writeDestroyDocument(data);

    return(TRUE);
}

/*
 * writeSaveDocument
 *
 * Save a Document
 */
vbool writeSaveDocument(
    writeDocument	*data,
    vdict		*context
    )
{
    vstr        	*str;

    if (data->fileSpec == vresourceNULL || (context != NULL && 
	vdictLoad(context, write_Option) != NULL)) {

        if (writeSaveWindow != NULL) {
	    if (!vdialogIsOpen(vfilechsrGetDialog(writeSaveWindow)))
	        vdialogOpen(vfilechsrGetDialog(writeSaveWindow));
	    vwindowRaise(vdialogGetWindow
			 (vfilechsrGetDialog(writeSaveWindow)));
	    vfilechsrSetData(writeSaveWindow, data);
	    vfilechsrSetApply(writeSaveWindow, _writeSaveNotify);
           return(FALSE);
        }
        writeSaveWindow = vfilechsrCreate();
	vfilechsrSetType(writeSaveWindow, vfilechsrPUT);
	vfilechsrSetData(writeSaveWindow, data);
	vfilechsrSetApply(writeSaveWindow, _writeSaveNotify);
	vfilechsrSetDirectory(writeSaveWindow, vfsGetAppDirPath());

        str = vresourceGetStringAt(writeMessages, writeMSG_SAVE_DOCUMENT);
        vdialogSetTitle(vfilechsrGetDialog(writeSaveWindow), str);
        vstrDestroy(str);

	vdialogOpen(vfilechsrGetDialog(writeSaveWindow));

	/* Rebuild the window menu */

	writeBuildWindowMenus();

        return(FALSE);
    }

    if (data->flags & writeDOC_READ_ONLY) {

        str = vresourceGetStringAt(writeMessages, writeMSG_CANT_SAVE_CHANGES);
        writeAlert(&data->dialog, str);
        vstrDestroy(str);

        return(FALSE);
    }

    /*
     * Store the document - first the text and styles itself
     */

    vtextStore(vtextviewGetTextData(data->textItem), data->fileSpec);

    /*
     * Write out markers, and the destroy the marker list
     */

    writeStoreMarkers(data, data->fileSpec);
 
    vresourceStoreRect(vwindowGetRect((vwindow *) data),
		       vresourceMake(data->fileSpec, vname_Rect));
    vresourceFlush(data->fileSpec);

    vundoMarkLogSaved(data->undoLog);
   
    writeSetDocumentIcon(data, writeDOC_MODIFIED,
			 (vbool)(!vundoIsLogSaved(data->undoLog)));
    
    /*
     * The following is an illegal hack - it makes sure that we generate
     * a new undo action if we continue typing after the save.  The next
     * Galaxy release will have a legal way of doing this
     */

    {
        _vtextSetLastUndoPosition(-2);
    }

    return(TRUE);
}

/* * * * * * * * *  Exporting a Document * * * * * * * */

static int _writeExportNotify(xcflchsr *chooser, vfsPath *filePath,
			      int charset, int byteOrder)
{
   writeDocument	*data;
   vfsFile              *fileSpec;
   xctrans              *trans;
   vtext                *editRec;
   int                   length, remainingLength, numchars;
   vchar                *start;

   if (vfsAccess(filePath, vfsFILE_EXISTS)) 
      {
	 if (vfsAccess(filePath, vfsCAN_WRITE))
	    vfsRemove(filePath);
	 else 
	    return(vTRUE);
      }

   vfsCreateFile(filePath, vfsOWNER_WRITE | vfsOWNER_READ);
   
   fileSpec = vfsOpenFile(filePath, vfsOPEN_READ_WRITE);
   
   data = (writeDocument *) xcflchsrGetData(chooser);
   
   /*
    *  export the text object
    */

   trans = xctransCreate();
   xctransSetEOL(trans, vtextEOLN);
   xctransSetCharset(trans, charset);
   xctransSetByteOrder(trans, byteOrder);

   editRec     = vtextviewGetTextData(data->textItem);
   length      = vtextLength(editRec);

   remainingLength = length;
   while (remainingLength > 0)
      {
	 start = vtextGetTextAt(editRec, length - remainingLength);

	 if (start)
	    {
	       numchars = xctransWriteLineToFile(trans, fileSpec, start, 
						 remainingLength);
	       remainingLength -= (numchars + 1);
	       
	    }
	 else 
	    break;
      }

   vfsCloseFile(fileSpec);
   
   xctransDestroy(trans);
   
   return(vTRUE);
}

/*
 * writeExportDocument
 *
 * Export a Document
 */
vbool writeExportDocument(
    writeDocument	*data,
    vdict		*context
    )
{
   if (writeExportWindow != NULL) 
      {
	 if (!vdialogIsOpen(xcflchsrGetDialog(writeExportWindow)))
	    vdialogOpen(xcflchsrGetDialog(writeExportWindow));

	 vwindowRaise(vdialogGetWindow(xcflchsrGetDialog(writeExportWindow)));
	 xcflchsrSetData(writeExportWindow, (void *)data);
	 return(vTRUE);
      }
   
   /*
    * Create the Export window dialog
    */

   if (vprefLoadScribed(vcharScribeLiteral("exportsplit")) != NULL)
      {
	 writeExportWindow = xcflchsrCreateSplit();
      }
   else
      {
	 writeExportWindow = xcflchsrCreate();
      }

   xcflchsrSetApply(writeExportWindow, _writeExportNotify);
   xcflchsrSetData(writeExportWindow, (void *)data);

   vfilechsrSetType(xcflchsrGetFilechsr(writeExportWindow), vfilechsrPUT);
   vfilechsrSetDirectory(xcflchsrGetFilechsr(writeExportWindow), 
			 vfsGetAppDirPath());

   
   vdialogSetTitleScribed(xcflchsrGetDialog(writeExportWindow),
			  vcharScribeLiteral("Export File"));
   
   xcflchsrOpen(writeExportWindow);
   
   /* Rebuild the window menu */
   
   writeBuildWindowMenus();
   
   return(vTRUE);
}

/*
 * writeGetSelection
 *
 * Gets the selected text (up to 1024 characters) and puts it in the global 
 * string 'writeSelection' - used for searching.  If 'limit' is TRUE, 
 * this means only to get a selection if the selected text is on one line, 
 * and is < 'limit' characters. Return TRUE if this case, FALSE otherwise.
 */
vbool writeGetSelection(
    writeDocument	*data,
    int			limit
    )
{
    vtextSelection	*selection;
    vtext		*editRec;

    if (data == NULL) {
	writeSelection[0] = '\0';
	return(FALSE);
    }

    editRec   = vtextviewGetTextData(data->textItem);
    selection = vtextviewGetSelection(data->textItem);

    writeSelectionLength = vtextGetPosition(selection)->length;

    if (limit && (vtextSelectedLines(selection) != 1L || 
		  writeSelectionLength >= limit))
	return(FALSE);
    if (writeSelectionLength == 0)
	return(FALSE);
	
    if (writeSelectionLength > 1024)
        writeSelectionLength = 1024;
    vtextGetText(editRec, selection,
		 writeSelection, writeSelectionLength);
    writeSelection[writeSelectionLength] = '\0';
    return(TRUE);
}

/*
 * writeSetDocumentIcon
 *
 * Draw or removed the modified document icon
 */
void writeSetDocumentIcon(
    writeDocument	*data,
    unsigned short      flag,
    vbool               enable
    )
{
    vrect               r;

    if (!enable && (data->flags & flag) == 0)
        return;
    if (enable && (data->flags & flag))
        return;

    data->flags ^= flag;

    r = *vwindowGetRect((vwindow *) data);
    r.x = r.y = 0;
    vdialogArrange((vdialog *) data, &r);

    {
       /*
	* update the window menus
	*/

       writeDocument *list = writeDocumentList;

       while (list != NULL) {
	  vmenuChangedSize(list->windowMenu);
	  list = list->next;
       }
    }
}

/*
 * writeChangeDocumentState
 *
 * Change the value a one of the standard document states
 */
void writeChangeDocumentState(
    writeDocument	*data,
    const vname		*name,
    const vname		*value
    )
{
    writeDocument	*scan;

    scan = (data == NULL ? writeDocumentList : data);
    
    while (scan != NULL) {

	vdictStore(scan->standardState, name, value);

	vobjectPropagateChange(vwindowGetObject((vwindow *) scan),
                               vname_State, name, value);
	scan = scan->next;

	if (data != NULL)
	    break;
    }
}

/* * * * * * * * * * * Handle the Icon Box * * * * * * * * * */

static void _writeDrawIconBox(
    vdialogItem		*item
    )
{
    const vrect		*r;
    writeDocument	*data;

    if (!vdialogItemIsVisible(item))
        return;

    r 	 = vdialogGetItemRect(item);
    data = (writeDocument *) vdialogGetItemData(item);

    vdrawMoveTo(r->x, r->y);

    if (data->flags & writeDOC_MODIFIED) {
        vdrawImageCompositeIdent(modifiedImage);
	vdrawRMoveTo(28, 0);
    }
    if (data->flags & writeDOC_READ_ONLY) {
        vdrawImageCompositeIdent(readOnlyImage);
	vdrawRMoveTo(28, 0);
    }
}

static void _writeIconBoxNaturalSize(
    vdialogItem		*item,
    int			*w,
    int			*h
    )
{
    writeDocument       *data;

    vclassSendSuper(defaultIconBoxClass, vdialogGET_ITEM_NATURAL_SIZE,
                    (item, w, h));

    data = (writeDocument *) vdialogGetItemData(item);
    *w = 0;

    if (data->flags & writeDOC_MODIFIED)
        *w += 24;
    if (data->flags & writeDOC_READ_ONLY)
        *w += 24;
    if (data->flags & (writeDOC_READ_ONLY | writeDOC_MODIFIED))
        *w += 4;
}

/* * * * * * * * * * * Handle the Ribbon * * * * * * * * * */

static void _writeDrawRibbon(
    vdialogItem		*item
    )
{
    const vrect		*r;
    writeDocument	*data;
    vcolor              *foreground;

    if (!vdialogItemIsVisible(item))
        return;

    r 	 = vdialogGetItemRect(item);
    data = (writeDocument *) vdialogGetItemData(item);

    if (vlaf3D())
        vdrawRectsHiliteFillInside(r, 1,
	  vdialogDetermineItemBackground(item),
	  vdialogDetermineItemColor(item, vdrawCOLOR_SHADOW_TOP),
	  vdialogDetermineItemColor(item, vdrawCOLOR_SHADOW_BOTTOM));
    else {
	foreground = vdialogDetermineItemForeground(item);
	vdrawRectsHiliteFillInside(r, 1,
		vdialogDetermineItemBackground(item),
                foreground, foreground);
    }
}

static void _writeRibbonNaturalSize(
    vdialogItem		*item,
    int			*w,
    int			*h
    )
{
    int			x;
    writeDocument	*data;

    vclassSendSuper(defaultRibbonClass, vdialogGET_ITEM_NATURAL_SIZE,
                    (item, w, h));
    
    data = (writeDocument *) vdialogGetItemData(item);

    if ((data->flags & writeDOC_SHOW_RIBBON) == 0)
        *h = 0;
    else {
	vdialogGetItemNaturalSize((vdialogItem *) data->combo,
				  &x, h);
	*h += 12;
    }
}

static void _writeRibbonMinSize(
    vdialogItem		*item,
    int			*w,
    int			*h
    )
{
    int			x;
    writeDocument	*data;

    vclassSendSuper(defaultRibbonClass, vdialogGET_ITEM_MIN_SIZE,
                    (item, w, h));

    data = (writeDocument *) vdialogGetItemData(item);

    if ((data->flags & writeDOC_SHOW_RIBBON) == 0)
        *h = 0;
    else {
	vdialogGetItemMinSize((vdialogItem *) data->combo,
				  &x, h);
	*h += 12;
    }
}

static int _writeRibbonSeparation(
    vdialogItem         *item,
    vdialogItem         *to,
    unsigned int        which
    )
{
    writeDocument	*data;
    int                 val;

    data 	= (writeDocument *) vdialogGetItemData(item);
    
    val = vclassSendSuper(defaultRibbonClass,
                     vdialogGET_ITEM_NATURAL_SEPARATION, (item, to, which));

    if (to == (vdialogItem *) data->ruler) {

	if ((data->flags & writeDOC_SHOW_RIBBON) == 0)
            val = 0;
        else if (val > 0)
            val = 3;
    }
 
    return(val);
}

/* * * * * * * * * * * Handle the Text Ruler * * * * * * * * * */

static void _writeTextRulerNaturalSize(
    vtextruler		*item,
    int			*w,
    int			*h
    )
{
    vclassSendSuper(defaultTextRulerClass, vdialogGET_ITEM_NATURAL_SIZE,
                    (item, w, h));

    if ((((writeDocument *) vtextrulerGetData(item))->flags &
	 writeDOC_SHOW_RULER) == 0)
        *h = 0;
}

static void _writeTextRulerMinSize(
    vtextruler		*item,
    int			*w,
    int			*h
    )
{
    vclassSendSuper(defaultTextRulerClass, vdialogGET_ITEM_MIN_SIZE,
                    (item, w, h));

    if ((((writeDocument *) vtextrulerGetData(item))->flags &
	 writeDOC_SHOW_RULER) == 0)
        *h = 0;
}

static int _writeTextRulerSeparation(
    vtextruler         *item,
    vdialogItem         *to,
    unsigned int        which
    )
{
    writeDocument	*data;
    int                 val;

    data 	= (writeDocument *) vtextrulerGetData(item);
    
    val = vclassSendSuper(defaultTextRulerClass,
                     vdialogGET_ITEM_NATURAL_SEPARATION, (item, to, which));

    if (to == (vdialogItem *) data->textItem) {

	if ((data->flags & writeDOC_SHOW_RULER) == 0)
            val = 0;
        else if (val > 0)
            val = 3;
    }

    else if (to == (vdialogItem *) data->ribbon) {

        if ((data->flags & writeDOC_SHOW_RIBBON) == 0)
            val = 0;
        else if (val > 0)
            val = 3;
    }       
    
    return(val);
}

/* * * * * * * * * * * Handle the Text View * * * * * * * * * */

static int _writeTextViewSeparation(
    vtextview           *item,
    vdialogItem         *to,
    unsigned int        which
    )
{
    writeDocument	*data;
    int                 val;

    data 	= (writeDocument *) vtextviewGetData(item);

    val = vclassSendSuper(defaultTextViewClass, 
                     vdialogGET_ITEM_NATURAL_SEPARATION, (item, to, which));

    if (to == (vdialogItem *) data->ruler) {

	if ((data->flags & writeDOC_SHOW_RULER) == 0)
            val = 0;
        else if (val > 0)
            val = 1;
    }
    
    return(val);
}

/* * * * * *  Marker Menus  * * * * * */

/*
 * _writeJumpMarkerNotify
 *
 * Menu item notification function to handle jumping to the menu
 * item marker
 */
static void _writeJumpMarkerNotify(
    vmenuItem	*item,
    vevent	*event
    )
{
    writeMarker         *marker;
    writeDocument       *data;

    data = (writeDocument *) vmenuGetData(vmenuDetermineItemMenu(item));
    marker = (writeMarker *) vmenuGetItemData(item);

    writeSelectMarker(data, marker);
}

/*
 * writeAddMarkerMenu
 * 
 * Add a marker to the marker menu
 */
void writeAddMarkerMenu(
    writeDocument	*data,
    writeMarker		*marker
    )
{
    vmenuItem	  	*item;

    item = vmenuCreateItem();
    vmenuSetItemTitle(item, marker->name);
    vmenuSetItemData(item, marker);
    vmenuSetItemNotify(item, _writeJumpMarkerNotify);
    vmenuSetItemFont(item, vfontFindScribed(vcharScribeLiteral
			  ("family:helvetica-face:medium-size:10")));

    vmenuAppendItem(data->markMenu, item);
    vmenuAppendItem(data->popupMarkMenu, vmenuCloneItem(item));

    data->markMenuCount++;
}

/*
 * writeRemoveMarkerMenu
 * 
 * Remove a marker from the marker menu
 */
void writeRemoveMarkerMenu(
    writeDocument	*data,
    writeMarker		*marker
    )
{
    vmenuItem	  	*item;
    int			count, i, j;
    vmenu               *menu;

    for (j=0; j<2; j++) {
        
        menu = (j == 0 ? data->markMenu : data->popupMarkMenu);

	count = vmenuGetItemCount(menu);
    
        for (i=0; i<count; i++) {
        
            item = vmenuGetItemAt(menu, i);

            if (vmenuGetItemData(item) == marker) {
                vmenuDeleteItem(menu, item);
		vmenuDestroyItem(item);
                break;
            }
        }
    }

    data->markMenuCount--;
}

/* * * Window Menu Building and Handling * * * */

static void _writeDrawWindowMenuItem(
    vmenuItem		*item,
    const vrect		*bounds,
    const vrect		*content
    )
{
    writeDocument	*data;
    vchar                asterisk = vcharFromLiteral('*');

    data = (writeDocument *) vmenuGetItemData(item);
    
    vdrawMoveTo(content->x, content->y);
    if (!vundoIsLogSaved(data->undoLog))
        vdrawSizedShow(&asterisk, 1);
    vdrawShow(item->title);
}

static void _writeCalcWindowMenuItemMetrics(
    vmenuItem		*item,
    vmenuItemMetrics    *metrics
    )
{
    writeDocument	*data;
    vchar                asterisk = vcharFromLiteral('*');

    vclassSendSuper(defaultWindowMenuItemClass, vmenuCALC_ITEM_METRICS,
		    (item, metrics));

    data = (writeDocument *) vmenuGetItemData(item);
    
    if (!vundoIsLogSaved(data->undoLog)) {
        vfont *font;

	font = vmenuDetermineItemFont(item);
        metrics->width += vfontSizedStringWidthX(font, &asterisk, 1);
    }
}

static void _writeSelectWindow(
    vmenuItem		*item,
    vevent		*event
    )
{
    vwindowRaise((vwindow *) vmenuGetItemData(item));
}

static void _writeAddItem(
    vmenu             *menu,
    vwindow           *window,
    const vchar       *name, 
    int /*vbool*/      flag
    )
{
    vmenuItem		*item;

    if (flag)
       item = vmenuCreateItemOfClass(defaultWindowMenuItemClass);
    else
       item = vmenuCreateItem();

    vmenuSetItemData(item, window);
    vmenuSetItemNotify(item, _writeSelectWindow);
    vmenuSetItemTitle(item, name);
    vmenuAppendItem(menu, item);
}

/*
 * _writeCreateWindowMenu
 *
 * Create a window menu that can be copied into all document window's
 */
static vmenu *_writeCreateWindowMenu(void)
{
    vmenu               *windowMenu;
    vmenuItem           *item;
    vbool		hasUtil;
    writeDocument       *data;

    windowMenu = vmenuCreate();
    vmenuSetTitleScribed(windowMenu, vcharScribeLiteral("Window"));
    
    hasUtil = (writeOpenWindow != NULL    || writeSaveWindow != NULL   ||
	       writeImportWindow != NULL  || writeExportWindow != NULL || 
	       writeSearchWindow != NULL  || writeMarkWindow != NULL   || 
	       writeUnmarkWindow != NULL  || writeStyleChooser != NULL || 
	       writeStyleWindow != NULL);

    /*
     * First, add all of the documents to the document menu
     */

    data = writeDocumentList;
    while (data != NULL) {
        _writeAddItem(windowMenu, vdialogGetWindow(&data->dialog), 
                      vdialogGetTitle(&data->dialog), vTRUE);
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

    if (writeOpenWindow != NULL)
        _writeAddItem(windowMenu,
                      vdialogGetWindow(vfilechsrGetDialog(writeOpenWindow)),
		      vdialogGetTitle(vfilechsrGetDialog(writeOpenWindow)),
		      vFALSE);

    if (writeSaveWindow != NULL)
        _writeAddItem(windowMenu,
                      vdialogGetWindow(vfilechsrGetDialog(writeSaveWindow)),
		      vdialogGetTitle(vfilechsrGetDialog(writeSaveWindow)),
		      vFALSE);

    if (writeImportWindow != NULL)
        _writeAddItem(windowMenu, 
		      vdialogGetWindow(xcflchsrGetDialog(writeImportWindow)),
		      vdialogGetTitle(xcflchsrGetDialog(writeImportWindow)),
		      vFALSE);

    if (writeExportWindow != NULL)
        _writeAddItem(windowMenu, 
		      vdialogGetWindow(xcflchsrGetDialog(writeExportWindow)),
		      vdialogGetTitle(xcflchsrGetDialog(writeExportWindow)),
		      vFALSE);

    if (writeStyleChooser != NULL)
        _writeAddItem(windowMenu,
		      vdialogGetWindow(vstylechsrGetDialog(writeStyleChooser)),
		      vdialogGetTitle(vstylechsrGetDialog(writeStyleChooser)),
		      vFALSE);

    if (writeMarkWindow != NULL)
        _writeAddItem(windowMenu,
		      vdialogGetWindow(vconfirmGetDialog(writeMarkWindow)),
		      vdialogGetTitle(vconfirmGetDialog(writeMarkWindow)),
		      vFALSE);

    if (writeUnmarkWindow != NULL)
        _writeAddItem(windowMenu,
		      vdialogGetWindow(vconfirmGetDialog(writeUnmarkWindow)),
		      vdialogGetTitle(vconfirmGetDialog(writeUnmarkWindow)),
		      vFALSE);

    if (writeSearchWindow != NULL)
        _writeAddItem(windowMenu,
		      vdialogGetWindow(&writeSearchWindow->dialog),
		      vdialogGetTitle(&writeSearchWindow->dialog),
		      vFALSE);

    if (writeStyleWindow != NULL)
        _writeAddItem(windowMenu,
		      vdialogGetWindow(&writeStyleWindow->dialog),
		      vdialogGetTitle(&writeStyleWindow->dialog),
		      vFALSE);
	
    return(windowMenu);
}

/*
 * writeBuildWindowMenus
 */
void writeBuildWindowMenus()
{         
    vmenu		*menu;
    writeDocument	*data;

    /*
     * Add the window to the window menu.  We need to add it to all 
     * window menus in all open windows.
     */
    
    menu = _writeCreateWindowMenu();
    data = writeDocumentList;

    while (data != NULL) {
        vmenuCopy(menu, data->windowMenu);
	vmenuSetLeader(data->windowMenu, (vwindow *) data);
        data = data->next;
    }

    vmenuDestroy(menu);
}

/* * * * * * * Text View Notify * * * * * * * */

static void _writeTextNotify(
    vtextview		*textView,
    vevent		*ev,
    int			 message
    )
{
    writeDocument	        *data;
    vtextSelection              *selection;
    vbool			selectState;

    selection	= vtextviewGetSelection(textView);
    data	= (writeDocument *) vtextviewGetData(textView);
    
    if (message == vtextviewSELECT_NOTIFY) {

        if (vtextGetPosition(selection)->length == 0) {
	    selectState = FALSE;
	    if (data->flags & writeDOC_SELECT_STATE) {
                vcommandReplaceSpaceDict(data->space, vname_State,
                                         &selectionState, &noselectionState);
                data->flags &= ~writeDOC_SELECT_STATE;
            }
        }
        else {
            selectState = TRUE;
	    if ((data->flags & writeDOC_SELECT_STATE) == 0) {
                vcommandReplaceSpaceDict(data->space, vname_State,
                                         &noselectionState, &selectionState);
                data->flags |= writeDOC_SELECT_STATE;
            }
        } 
#if writeDEBUG
	if (clickStyleInfo) {
            
            vtextStyleTag       **styles;
            int                 styleCount, position, i = 0;
            vtext               *editRec;
            extern              _vtextDumpStyle(vtextStyle *, FILE *);
	    vtextStyleTransitionIterator iterator;

            editRec    = vtextviewGetTextData(data->textItem);
            position   = vtextGetPosition(vtextviewGetSelection
                                          (data->textItem))->start;

	    vtextInitStyleTransitionIterator(&iterator, editRec, position);
	    if (!vtextNextStyleTransitionIterator(&iterator))
	        return;

	    styles     = vtextGetStyleTransitionIteratorStyles(&iterator);
	    styleCount = vtextGetStyleTransitionIteratorCount(&iterator);

            printf("----------------------------\n");
            printf(" %d Styles at position %d\n", styleCount, position);
            printf("  Style #%d\n", i++);
            while (styleCount-- > 0) {
                _vtextDumpStyle((*styles)->style, NULL);
                styles++;
            }
            printf("----------------------------\n");
	}
#endif
    }
}

/* * * * * * * Undo * * * * * * * */

static void _writeUndoNotify(
    vtextview		*textView,
    vundoAction		*action
    )
{
    writeDocument       *data;

    data = (writeDocument *) vtextviewGetData(textView);

    writeSetDocumentIcon(data, writeDOC_MODIFIED, TRUE);

    vundoAddLogAction(data->undoLog, action);
}

/* * * * * * * * * * * DOCUMENT COMMAND SPACE * * * * * * * * * */

static vdict  defaultKeyMap;

static void _writeApplyStyle(
    vtext		*editRec,
    vtextSelection	*selection,
    vtextStyle		*style
    )
{	
    vtextApplyStyle(editRec, selection, style);
}

static int _writeStyleNotify(
    vstylechsr		*styleChooser,
    vtextStyle		*newStyle
    )
{
    writeDocument	*data;
    vtextStyle		*style;
    vtext		*editRec;

    data = (writeDocument *) vstylechsrGetData(styleChooser);

    if (data == NULL)
	return(FALSE);

    editRec  = vtextviewGetTextData(data->textItem);

    style = vtextFindStyle(editRec, newStyle);

    if (style == NULL) {
	style = vtextCreateStyle();
	vtextCopyStyle(newStyle, style);
	vtextInstallStyleOwned(editRec, style);
    }

    _writeApplyStyle(editRec, vtextviewGetSelection(data->textItem), style);

    return(TRUE);
}

static void _writeInitDocumentSpace(void)
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
	{ "Rectangular Edit", 		},
	{ "Overstrike Edit", 		},
	{ "Show Hidden Text", 		},
	{ "Display Selection", 		},
	{ "Drag Drop Edit", 		},
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

    tempSpace = writeLoadSpace(vnameInternGlobalLiteral("Document Space"));

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

static void _writeInitStateDictionaries(void)
{
    typedef struct {
        const char	*id;
	short		state;
    } stateDef;

    register stateDef   *states;
    static vbool	_inited = FALSE;

    static stateDef selStateDefs[] = {
        { "Cut",          	TRUE },
        { "Copy",         	TRUE },
        { "Clear",	  	TRUE },
        { "Append Copy",  	TRUE },
        { "Append Cut",   	TRUE },
        { "Upper Case",   	TRUE },
        { "Lower Case",   	TRUE },
        { "Capitalize",   	TRUE },
        { "Toggle Case",   	TRUE },
        { "Find Selection",   	TRUE },
        { "First Occurence",   	TRUE },
        { "Reverse Find Selection",TRUE },
	{ NULL }
    };
    
    static stateDef noselStateDefs[] = {
        { "Cut",          	FALSE },
        { "Copy",         	FALSE },
        { "Clear",	  	FALSE },
        { "Append Copy",  	FALSE },
        { "Append Cut",   	FALSE },
        { "Upper Case",   	FALSE },
        { "Lower Case",   	FALSE },
        { "Capitalize",   	FALSE },
        { "Toggle Case",  	FALSE },
        { "Find Selection",  	FALSE },
        { "First Occurence",   	FALSE },
        { "Reverse Find Selection",FALSE },
	{ NULL }
    };

    static stateDef standardStateDefs[] = {
        { "Unmark",             	FALSE },
        { "Push Position",      	FALSE },
        { "Pop Position",       	FALSE }, 
	{ "Replace Same",		FALSE },
	{ NULL }
    };
 
    if (_inited)
        return;
    _inited = TRUE;

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

static int _writeIssueDocumentCommand(
    writeDocument       *data,
    int		        selector,
    vdict               *context
    )
{
    vrect                       r;
    vbool			set;
    vchar			*name;
    const vname			*option;
    vtext			*editRec;
    vtextSelection              *selection;
    vtextStyle			*style;
    vtextPosition		*position;
    vtextGraphic		*graphic;

    extern void			_vtextDumpStyles(vtext *, FILE *);
    extern void			_vtextDumpRulers(vtext *, FILE *);
    extern void			_vtextDumpBlocks(vtext *, FILE *);

    editRec = vtextviewGetTextData(data->textItem);

    switch (selector) {
	
    case comCLOSE_WINDOW:
	if (!writeIsDocumentValid(data))
	    break;

	writeDestroyDocument(data);
	return(TRUE);

    case comSAVE:
	writeSaveDocument(data, context);
	return(TRUE);

    case comEXPORT:
	writeExportDocument(data, context);
	return(TRUE);

    case comSAVE_TEMPLATE_DOCUMENT:
        _writeSetDocumentTemplate(data, &writeTemplatePreferences);
	return(TRUE);

    case comREVERT:
	return(TRUE);

    case comINSERT_GRAPHIC:
	graphic = vtextCreateGraphic();
	vtextInsertGraphicObjectOwned(editRec,
				      vtextviewGetSelection(data->textItem),
				      graphic);
	return(TRUE);

    case comFIND:
	writeSearchDocument(data, context);
	return(TRUE);

    case comREPLACE:
	vobjectDispatchCommand((vobject *) writeSearchWindow,
			       vnameInternGlobalLiteral("Find Then Change"),
			       NULL);
	return(TRUE);

    case comMARK:
	name = (vchar *) vdictLoad(context, write_Target);
	if (name == NULL) {
            writeCreateMarkWindow();
	    return(TRUE);
        }

	selection = vtextviewGetSelection(data->textItem);
        writeAddMarker(data, name,
                       vtextGetPosition(selection)->start,
                       vtextGetPosition(selection)->end);
	return(TRUE);

    case comUNMARK:
        writeCreateUnmarkWindow();
   	writeLoadUnmarkWindow(data, TRUE);
	return(TRUE);

    case comSHOW_RULER:
	(data)->flags ^= writeDOC_SHOW_RULER;
        if ((data)->flags & writeDOC_SHOW_RULER)
            vdialogShowItem((vdialogItem *) data->ruler);
        else
            vdialogHideItem((vdialogItem *) data->ruler);
srplace:    
        r = *vwindowGetRect((vwindow *) data);
        r.x = r.y = 0;
        vdialogArrange((vdialog *) data, &r);
        return(TRUE);

    case comSHOW_RIBBON:
	data->flags ^= writeDOC_SHOW_RIBBON;
        if (data->flags & writeDOC_SHOW_RIBBON) {
	    vdialogShowItem(data->ribbon);
	    vdialogShowItem(vcomboGetItem(data->combo));
        }
        else {;
	    vdialogHideItem(data->ribbon);
	    vdialogHideItem(vcomboGetItem(data->combo));
        }
        goto srplace;

    case comSHOW_HORIZONTAL_SCROLL_BAR:
	set = vtextviewHasHorzBar(data->textItem) ? FALSE : TRUE;
	vtextviewSetHorzBar(data->textItem, set);
        return(TRUE);

    case comSHOW_VERTICAL_SCROLL_BAR:
	set = vtextviewHasVertBar(data->textItem) ? FALSE : TRUE;
        vtextviewSetVertBar(data->textItem, set);
        return(TRUE);

    case comFORMAT:
	position = vtextGetPosition(vtextviewGetSelection(data->textItem));
    
	if (_chooserStyle) {
	    vtextDestroyStyle(_chooserStyle);
	    _chooserStyle = NULL;
	 }
	style = vtextStyleAtPosition(editRec, position->start);

	if (style == NULL)
	    style = vtextGetDefaultStyle(data->textItem->textData);
	else
	    _chooserStyle = style;

	writeOpenStyleChooser();

	vstylechsrSetStyle(writeStyleChooser, style);
	vstylechsrSetData(writeStyleChooser, data);
	vstylechsrSetApply(writeStyleChooser, _writeStyleNotify);
	
	return(TRUE);

    case comAPPLY_TEXT_STYLE:
	option = (const vchar *) vdictLoad(context, vname_Attribute);
	if (option == NULL)
	    break;

	if (option == vnameInternGlobalLiteral("Plain")) {

	    vtextUnapplyStyle(editRec, vtextviewGetSelection(data->textItem),
			      vtextALL_STYLES);
	}
	else {
	   
	    const vname	  *onOrOff = vname_On;

	    /*
	     * Determine whether to turn the attribute on or off by
	     * getting the style at the start of the selection.  Do the
	     * opposite of what is set.
	     */

	    position = vtextGetPosition(vtextviewGetSelection(data->textItem));
	    style = vtextStyleAtPosition(editRec, position->start);

	    if (style != NULL) {
		if (vtextGetStyleAttribute(style, option) == vname_On)
		    onOrOff = vname_Off;
		vtextDestroyStyle(style);
	    }

	    style = vtextCreateStyle();
	    vtextSetStyleAttribute(style, option, onOrOff);
	    vtextInstallStyleOwned(editRec, style);
	    _writeApplyStyle(editRec, vtextviewGetSelection(data->textItem), style);
	}
	break;

    case comSEARCH:
	wrtDialog = &data->dialog;
	writeCreateSearchWindow();
	writeSetTargetDocument(data);
	return(TRUE);

    case comVIEW:
	return(TRUE);

    case comVIEW_NORMAL:
	if (vtextGetView(editRec) != vtextVIEW_NORMAL)
	   vtextSetView(editRec, vtextVIEW_NORMAL);
	break;

    case comVIEW_INVISIBLES:
	if (vtextGetView(editRec) != vtextVIEW_INVISIBLES)
	   vtextSetView(editRec, vtextVIEW_INVISIBLES);
	break;

    case comVIEW_KEYCODES:
	if (vtextGetView(editRec) != vtextVIEW_KEYCODE)
	   vtextSetView(editRec, vtextVIEW_KEYCODE);
	break;


#if writeDEBUG
    case comDBG_DUMP_STYLES:
	_vtextDumpStyles(editRec, NULL);
	return(TRUE);

    case comDBG_DUMP_RULERS:
	_vtextDumpRulers(editRec, NULL);
	return(TRUE);

    case comDBG_DUMP_BLOCKS:
	_vtextDumpBlocks(editRec, NULL);
	return(TRUE);

    case comDBG_STYLE_TEST:
	return(TRUE);

    case comDBG_CLICK_STYLE_INFO:
	clickStyleInfo = !clickStyleInfo;
	return(TRUE);

#endif
    }

    return vclassSendSuper(defaultDocumentClass,
			   vobjectISSUE_SELECTOR,
			   (data, selector, context));
}

static int _writeQueryDocumentCommand(
    writeDocument       *data,
    int		        selector,
    vdict               *context
    )
{
    const vname		*name;
    vtext               *editRec;

    if (vwindowGetSpace((vwindow *)data) == NULL) {
       /*
	* document in the process of being destroyed
	*/
       return(FALSE);
    }

    editRec = vtextviewGetTextData(data->textItem);

    switch (selector) {
	
    case comSAVE:    
        if ( ( !vundoIsLogSaved(data->undoLog) &&
              (data->flags & writeDOC_READ_ONLY) == 0 ) ||
            data->fileSpec == vresourceNULL ||
	    vdictLoad(context, write_Option) != NULL)
            name = vname_Enabled;
        else
            name = vname_Disabled;

        vdictStore(context, vname_State, name);
        break;
        
    case comSHOW_RIBBON:
        vdictStore(context, vname_Toggle, (vchar *)
                   ((data->flags & writeDOC_SHOW_RIBBON) ?
                   vname_On: vname_Off));
        break;

    case comSHOW_HORIZONTAL_SCROLL_BAR:
        vdictStore(context, vname_Toggle, (vchar *)
                   (vtextviewHasHorzBar(data->textItem) ?
                   vname_On: vname_Off));
        break;

    case comSHOW_VERTICAL_SCROLL_BAR:
        vdictStore(context, vname_Toggle, (vchar *)
                   (vtextviewHasVertBar(data->textItem) ?
                   vname_On: vname_Off));
        break;

    case comSHOW_RULER:
        vdictStore(context, vname_Toggle, (vchar *)
                   ((data->flags & writeDOC_SHOW_RULER) ?
                   vname_On: vname_Off));
        break;

    case comVIEW:
	if (vdictLoad(context, vname_Attribute) == 
	    vnameInternGlobalLiteral("Normal"))
	    vdictStore(context, vname_Toggle, vname_On); 
	else
	    vdictStore(context, vname_Toggle, vname_Off);
	break;

    case comVIEW_NORMAL:
	vdictStore(context, vname_Toggle, (vchar *) 
		   ((vtextGetView(editRec) == vtextVIEW_NORMAL) ?
		  vname_On: vname_Off));
	break;

    case comVIEW_INVISIBLES:
	vdictStore(context, vname_Toggle, (vchar *)
		   ((vtextGetView(editRec) == vtextVIEW_INVISIBLES) ?
		  vname_On: vname_Off));
	break;

    case comVIEW_KEYCODES:
	vdictStore(context, vname_Toggle, (vchar *)
		   ((vtextGetView(editRec) == vtextVIEW_KEYCODE) ?
		  vname_On: vname_Off));
	break;

    case comREPLACE:
	vdictStore(context, vname_State, writeSearchWindow == NULL ?
		   vname_Disabled : vname_Enabled);
	break;

#if writeDEBUG
    case comDBG_CLICK_STYLE_INFO:
        vdictStore(context, vname_Toggle, (vchar *)
                   (clickStyleInfo ? vname_On: vname_Off));
#endif
    default:
	if (selector > vdialogNEXT_SELECT && 
	    selector <= comDBG_CLICK_STYLE_INFO)
	    vdictStore(context, vname_Dispatch, vname_Enabled);
	break;
    }

    if (selector > vdialogNEXT_SELECT &&
	selector <=  comDBG_CLICK_STYLE_INFO)
	return(TRUE);

    return vclassSendSuper(defaultDocumentClass,
			   vobjectQUERY_SELECTOR,
			   (data, selector, context));
}

static void _writePropagateChangeDict(
    writeDocument	*data,
    const vname		*attr,
    vdict		*context
    )
{
    if (attr == vname_State)
	writeSetDocumentIcon(data, writeDOC_MODIFIED,
			     (vbool)(!vundoIsLogSaved(data->undoLog)));
    vclassSendSuper(defaultDocumentClass,
                    vobjectPROPAGATE_CHANGE_DICT,
                    (data, attr, context));
}

static void _writeDocOpen(
    writeDocument	*data
    )
{
    vclassSendSuper(defaultDocumentClass, vwindowOPEN, (data));

    if (_alert != NULL)
	vwindowRaise((vwindow *) _alert);
}

/* * * * * *   STARTUP AND SHUTDOWN * * * * * */

/*
 * writeDocumentStartup
 *
 * One-time setup of all document classes, commands, and more
 */
void writeDocumentStartup()
{
    vresource	imageDict;
    int		i;
    extern void _writeRemoveTag(vtext *, vtextTag *); /* in mark.c */

    /*
     * Initialize the document command space 
     */

    _writeInitDocumentSpace();

    /*
     * Setup the document dialog class - handles cleaning up when
     * the document is destroyed, as well as the issue and query 
     * selectors
     */

    defaultDocumentClass = vclassSpawn(vdialogGetDefaultClass(),
					   sizeof(writeDocumentClass));
	
    vclassSetNameScribed(defaultDocumentClass,
                         vcharScribeLiteral("vwriteDocument"));
    vclassSetObjectSize(defaultDocumentClass, sizeof(writeDocument));

    vclassSet(defaultDocumentClass,
              vobjectDESTROY,                   _writeDestroyDocument);
    vclassSet(defaultDocumentClass, 
              vobjectSPACE,                     &defaultSpace);
    vclassSet(defaultDocumentClass,
	      vobjectKEY_MAP,			&defaultKeyMap);
    vclassSet(defaultDocumentClass, 
              vobjectISSUE_SELECTOR,            _writeIssueDocumentCommand);
    vclassSet(defaultDocumentClass,
              vobjectQUERY_SELECTOR,            _writeQueryDocumentCommand);
    vclassSet(defaultDocumentClass,	
	      vobjectPROPAGATE_CHANGE_DICT,	_writePropagateChangeDict);
    vclassSet(defaultDocumentClass,
	      vwindowOPEN,			_writeDocOpen);

    /*
     * Setup the Icon Box class for the dialog item that will 
     * draw any icon indicators for the document
     */

    defaultIconBoxClass = vclassReproduce(vdialogGetDefaultItemClass());
    vclassSetNameScribed(defaultIconBoxClass,
                         vcharScribeLiteral("vwriteIconBox"));
    vclassSet(defaultIconBoxClass, 
              vdialogDRAW_ITEM,                 _writeDrawIconBox);
    vclassSet(defaultIconBoxClass,
              vdialogGET_ITEM_NATURAL_SIZE, 	_writeIconBoxNaturalSize);

    /*
     * Setup the Bar dialog item
     */

    defaultRibbonClass = vclassReproduce(vdialogGetBoxItemClass());
    vclassSetNameScribed(defaultRibbonClass,
                         vcharScribeLiteral("writeRibbon"));

    vclassSet(defaultRibbonClass, 
              vdialogDRAW_ITEM,                 _writeDrawRibbon);
    vclassSet(defaultRibbonClass,
              vdialogGET_ITEM_NATURAL_SIZE, 	_writeRibbonNaturalSize);
    vclassSet(defaultRibbonClass,
	      vdialogGET_ITEM_NATURAL_SEPARATION, _writeRibbonSeparation);
    vclassSet(defaultRibbonClass,
	      vdialogGET_ITEM_MIN_SIZE, 	_writeRibbonMinSize);

    /*
     * Setup the Text Ruler class
     */

    defaultTextRulerClass = vclassReproduce(vtextrulerGetDefaultClass());
    vclassSetNameScribed(defaultTextRulerClass,
                         vcharScribeLiteral("writeTextRuler"));

    vclassSet(defaultTextRulerClass,
              vdialogGET_ITEM_NATURAL_SIZE, 	_writeTextRulerNaturalSize);
    vclassSet(defaultTextRulerClass,
	      vdialogGET_ITEM_NATURAL_SEPARATION, _writeTextRulerSeparation);
    vclassSet(defaultTextRulerClass,
	      vdialogGET_ITEM_MIN_SIZE,		_writeTextRulerMinSize);

    /*
     * Setup the window menu item class - to draw the window menu with
     * state icons next to the entries
     */

    defaultWindowMenuItemClass = vclassReproduce(vmenuGetDefaultItemClass());
    vclassSetNameScribed(defaultWindowMenuItemClass,
			 vcharScribeLiteral("writeWindowMenuItem"));
    vclassSet(defaultWindowMenuItemClass,
	      vmenuDRAW_ITEM,			_writeDrawWindowMenuItem);
    vclassSet(defaultWindowMenuItemClass,
	      vmenuCALC_ITEM_METRICS,	 _writeCalcWindowMenuItemMetrics);

    /*
     * Setup the Text View class 
     */

    defaultTextViewClass = vclassReproduce(vtextviewGetDefaultClass());
    vclassSetNameScribed(defaultTextViewClass,
                         vcharScribeLiteral("writeTextView"));
    vclassSet(defaultTextViewClass,
	      vdialogGET_ITEM_NATURAL_SEPARATION, _writeTextViewSeparation);

    /*
     * Set up the text data class
     */
   
    defaultTextClass = vclassReproduce(vtextGetDefaultClass());
	
    vclassSetNameScribed(defaultTextClass,
			 vcharScribeLiteral("vwriteText"));

    vclassSet(defaultTextClass, vtextREMOVE_TAG,      _writeRemoveTag);

    for (i=0; i<writeMAX_DOCUMENTS; i++)
        _writeNewSlots[i] = 0;
    _writeNewSlots[0] = 1;

    _writeInitStateDictionaries();

    /*
     * Read in some images
     */
                 
    imageDict	  = vresourceGet(writeResFile, vname_Image);

    modifiedImage = vimageLoad(vresourceGet
                      (imageDict, vnameInternGlobalLiteral("Modified")));
    readOnlyImage = vimageLoad(vresourceGet
                      (imageDict, vnameInternGlobalLiteral("ReadOnly")));

    offscreenImage = vwindowCreateBufferImage(100, 16);
}

/*
 * writeDocumentShutdown
 *
 * Cleanup after ourselves
 */
void writeDocumentShutdown()
{
    vclassDestroy(defaultDocumentClass);
    vclassDestroy(defaultIconBoxClass);
    vclassDestroy(defaultTextRulerClass);
    vclassDestroy(defaultTextViewClass);
    vclassDestroy(defaultRibbonClass);
    vclassDestroy(defaultWindowMenuItemClass);
    vclassDestroy(defaultTextClass);

    vimageDestroy(modifiedImage);
    vimageDestroy(readOnlyImage);
    vimageDestroy(offscreenImage);

    vdictDestroy(&selectionState);
    vdictDestroy(&noselectionState);
    vdictDestroy(&standardState);

    vcommandDestroySpace(&defaultSpace);
    vcommandDestroySpace(tempSpace);
    vcommandDestroyDict(&defaultFocusCommands);
    vdictDestroy(&defaultKeyMap);

    if (_chooserStyle) {
       vtextDestroyStyle(_chooserStyle);
       _chooserStyle = NULL;
    }
}

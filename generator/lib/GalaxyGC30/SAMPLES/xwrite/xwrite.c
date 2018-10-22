/* $Id: xwrite.c,v 1.2 1996/12/06 16:58:40 dimitri Exp $ */
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
 * Subject to the foregoing, you are permitted to copy, modify, and distribute
 * the Sample Code for any purpose and without fee, provided that (i) a
 * copyright notice in the form of "Copyright 1992 Visix Software Inc.,
 * 11440 Commerce Park Drive, Reston, VA  22091. All Rights Reserved" appears
 * in all copies, (ii) both the copyright notice and this permission notice
 * appear in supporting documentation and (iii) you are a valid licensee of
 * Galaxy Application Environment.
 ---------------------------------------------------------------------------*/

/****************************************************************************
 * Executable Name: xwrite
 * Source Files:    micwrite.c	App command space, init, utility functions
 * 		    document.c  document creating, saving, loading, document
 *				command space.
 * 	       	    mark.c
 *		    pref.c      Load/store of user prefs & default prefs
 *		    search.c
 *		    style.c
 *
 *                  xctrans.c   input/output character translation
 *                  xcflchsr.c  selection of text file, encoding, byte order
 *                  xtxtview.c  input handling modifications for textviews
 *
 * Header Files:    micwrite.h 
 *
 *                  xctrans.h
 *                  xcflchsr.h
 *                  xtxtview.h
 *
 * Resource Files:  xwrite.h
 *
 * Managers Illustrated:
 *     Text Manager
 *
 * Description Of Sample:
 * 
 * This example creates a simple word processing program.
 *
 * Things this module demonstrates:
 *   -- Subclassing
 *   -- Use of text data objects and text views
 *   -- Use of text observers
 *
 * How to use it:
 *
 * The calls are somewhat patterned after the Galaxy API, except with
 * module prefix of "write" ( Visix Write )
 *
 * Known bugs / limitations / missing features:
 *
 *   Cut/Copy/Paste does not copy text styles.
 *
 * 
 * History:
 *     Written for 2.0 release, 28-Nov-93
 *     Edited for  2.0 Unicode release, March 94
 ****************************************************************************/

#include "micwrite.h"

#if vdebugDEBUG
#define vdebugTAG "xwriteMicwrite"
#endif

/*
 * Globals
 */

vcommandSelectorClass		*defaultSelectorClass	  = NULL;
writeDocument			*writeDocumentList = NULL;
vfilechsr			*writeOpenWindow   	  = NULL;
vfilechsr			*writeSaveWindow   	  = NULL;
xcflchsr			*writeImportWindow   	  = NULL;
xcflchsr			*writeExportWindow   	  = NULL;
vstylechsr			*writeStyleChooser	  = NULL;
vdialog				*wrtDialog		  = NULL;
const vchar         		*_writePredefs[_write_Count];
vresource			 writeMessages;
vchar		 		 writeSelection[1025];
int		 	 	 writeSelectionLength = 0;
vresource		 	 writeResFile;
vresource		 	 writeUserPrefFile;
vcommandSpace     		*defaultSpace;

static    vnotice		*confirmNotice = NULL;
static    vnotice               *alertNotice = NULL;
static    vdialog	 	*aboutDialog = NULL;
static    vdialog		*infoDialog  = NULL;

int main(
    short       	argc,
    char         	**argv
    )
{
    vfsPath		**paths;
    vfsInfo     	info;
    int			numFiles;
    vbool       	opened = FALSE;

    vprefStoreScribed(vcharScribeLiteral("importsplit"),
		      vcharScribeCharacter(0));
    vprefStoreScribed(vcharScribeLiteral("exportsplit"),
		      vcharScribeCharacter(0));
    vprefStoreScribed(vcharScribeLiteral("nomultikb"),
		      vcharScribeCharacter(0));

    vprefSetArgs(argc, argv);

    (void)vwindowGetDefaultClass();

    (void)vtextGetDefaultClass();
    if (vprefLoadScribed(vcharScribeLiteral("nomultikb")) == NULL)
       {
	  xtxtviewStartup();
       }
    else
       (void)vtextviewGetDefaultClass();

    (void)vtextitemGetDefaultClass();
    (void)vtextrulerGetDefaultClass();
       
    (void)vbuttonGetDefaultClass();
    (void)vcomboGetDefaultClass();
    (void)vcomboGetPopdownClass();
    (void)vcommandGetDefaultClass();
    (void)vconfirmGetDefaultClass();
    (void)vcontainerGetDefaultClass();
    (void)vcontrolGetDefaultClass();
    (void)vcontrolGetOptionMenuClass();
    (void)vcontrolGetToggleClass();
    (void)vdialogGetDefaultClass();
    (void)vdialogGetDefaultItemClass();
    (void)vfilechsrGetDefaultClass();
    (void)vfontchsrGetDefaultClass();
    (void)vmenuGetDefaultClass();
    (void)vmenuGetDefaultItemClass();
    (void)vmenubarGetDefaultClass();

    writeStartup();
    writeDocumentStartup();
    writeSearchStartup();
    writeMarkStartup();
    writeStyleStartup();


    /*
     * Now process the arguments
     */

    vfsGetArgs(&numFiles, (const vfsPath ***) &paths);

    while (numFiles-- > 1) {

        if (vfsAccess(paths[numFiles], vfsFILE_EXISTS)) {

            vfsGetFileInfo(paths[numFiles], &info);

            if (vfsIsFile(&info)) {
                writeOpenDocument(paths[numFiles]);
                opened = TRUE;
            }
        }
    }

    if (!opened)
        writeNewDocument();

    veventProcess();
    
   /*
    * flush events, make sure all DestroyLater events are handled
    * before modules shut down
    */
    veventFlushProcessing();

    writeMarkShutdown();
    writePreferencesShutdown();
    writeShutdown();
    writeDocumentShutdown();
    writeSearchShutdown();
    writeStyleShutdown();

    exit(EXIT_SUCCESS);
    return EXIT_FAILURE;
}

/*
 * _writeOpenFile
 *
 * Apply function for Open file chooser - open the selected document
 */
static int _writeOpenFile(vfilechsr *fileChooser, vfsPath *filePath)
{
    writeOpenDocument(filePath);  
    return(TRUE);
}
 
/*
 * _writeImportFile
 *
 * Apply function for Import file chooser - import the selected document
 */
static int _writeImportFile(xcflchsr *ximportChooser, vfsPath *path, 
			    int charset, int byteOrder)
{
    writeImportDocument(path, charset, byteOrder);

    return TRUE;
}
 
/*
 * writeCenterWindow
 *
 * Center the given window in the root window
 */
void writeCenterWindow(
    vwindow		*window
    )
{
    const vrect         *r, *dr;

    r  = vwindowGetRect(vwindowGetRoot());
    dr = vwindowGetRect(window);
        
    vwindowMove(window,
                r->x + (r->w - dr->w) / 2,
                r->y + (r->h - dr->h) / 2);
}

/* 
 * writeOpenStyleChooser
 */
void writeOpenStyleChooser()
{
    /*
     * If the style chooser has been created, open (if not open) and raise
     * the style chooser
     */

    if (writeStyleChooser != NULL) {
        if (!vdialogIsOpen(vstylechsrGetDialog(writeStyleChooser)))
            vdialogOpen(vstylechsrGetDialog(writeStyleChooser));
        vwindowRaise(vdialogGetWindow(vstylechsrGetDialog(writeStyleChooser)));
        return;
    }
    
    /*
     * Create and open the style chooser
     */
    
    writeStyleChooser = vstylechsrCreate();
    vstylechsrOpen(writeStyleChooser);

    writeBuildWindowMenus();
}

/* * * * * *    Alert and Confiramation dialog handling   * * * * * */

static void _writePlaceNotice(
    vnotice		*notice,
    vdialog		*dialog
    )
{
    if (dialog != NULL) {
	if (vwindowIsIconified(vdialogGetWindow(dialog)))
	    vwindowUniconify(vdialogGetWindow(dialog));
	vnoticePlace(notice, dialog,
		     vrectPLACE_CENTER, vrectPLACE_CENTER );
	vwindowSetLeader(vnoticeGetWindow(notice), vdialogGetWindow(dialog));
    }
    else
	writeCenterWindow((vwindow *) notice);
}

/*
 * writeAlert
 *
 * Display an alert with the given message
 */
vnotice *writeAlert(
    vdialog		*dialog,
    vchar		*message
    )
{
    if (alertNotice == NULL)
        alertNotice = vnoticeCreate();
    vnoticeSetText(alertNotice, message);
    _writePlaceNotice(alertNotice, dialog);
    vdialogOpen(vnoticeGetDialog(alertNotice));
    return(alertNotice);
}

/*
 * writeConfirmation
 *
 * Display a general confirmation dialog with the given message.  Also
 * set the ok and no hooks functions, as well as the confirm's data.
 */
vnotice *writeConfirmation(
    vdialog		*dialog,
    vchar		*message,
    vnoticeHookProc	okHook,
    vnoticeHookProc	noHook
    )
{
    if (confirmNotice == NULL)
        confirmNotice = vnoticeCreate();
    vnoticeSetCancel(confirmNotice, TRUE);
    vnoticeSetCaution(confirmNotice, TRUE);
    vnoticeSetText(confirmNotice, message);
    vnoticeSetOkHook(confirmNotice, okHook);
    vnoticeSetNoHook(confirmNotice, noHook);
    vnoticeSetData(confirmNotice, dialog);
    _writePlaceNotice(confirmNotice, dialog);
    vdialogOpen(vnoticeGetDialog(confirmNotice));
    return(confirmNotice);
}

/*
 * writeModalConfirmation
 *
 * Display a general confirmation dialog with the given message.  Also
 * set the ok and no hooks functions, as well as the confirm's data.
 */
const vname *writeModalConfirmation(
    vdialog	*dialog,
    vchar	*message
    )
{
    if (confirmNotice == NULL)
        confirmNotice = vnoticeCreate();

    vnoticeSetCaution(confirmNotice, TRUE);
    vnoticeSetCancel(confirmNotice, TRUE);
    vnoticeSetOkHook(confirmNotice, NULL);
    vnoticeSetNoHook(confirmNotice, NULL);
    vnoticeSetCancelHook(confirmNotice, NULL);
    vnoticeSetText(confirmNotice, message);

    _writePlaceNotice(confirmNotice, dialog);

    return(vnoticeProcess(confirmNotice));
}

static vstr *_replaceStr(vstr *str, vchar *match, vscribe *replace)
{
    vchar		*ptr;
    size_t		 len;
    size_t		 replaceLen;
    size_t       	 matchLen;

    len = vcharLength(str);
    matchLen   = vcharLength(match);
    replaceLen = vscribeGetLength(replace);

    str = vstrSetSize(str, len - matchLen + replaceLen);
    ptr = vcharSearch(str, match);
    (void)vmemMove(ptr + matchLen, ptr + replaceLen, 
		   sizeof(vchar) * (len - (ptr + matchLen - str)));
    vcharCopyScribedBounded(replace, ptr, replaceLen);
    len = len - matchLen + replaceLen;
    str[len] = '\0';

    return(str);
}

/* 
 * writeReplaceStrings
 */
void writeReplaceStrings(
    vstr 		**strPtr, 
    vscribe 		*s1, 
    vscribe 		*s2
    )
{
    vchar	search[3];
    vstr	*str;

    str = *strPtr;

    vcharCopyScribed(vcharScribeLiteral("^1"), search);

    if (vcharSearch(str, search) && s1)
	str = _replaceStr(str, search, s1);
       
    vcharCopyScribed(vcharScribeLiteral("^2"), search);
    if (vcharSearch(str, search) && s2)
	str = _replaceStr(str, search, s2);

    *strPtr = str;
}

vdialog *writeLoadDialog(const vname *tag)
{
    vresource   res;

    res = vresourceGet(writeResFile, vnameInternGlobalLiteral("Dialogs"));
    return(vdialogLoad(vresourceGet(res, tag)));
}

vcommandSpace *writeLoadSpace(const vname *tag)
{
    vresource   res;

    res = vresourceGet(writeResFile, vnameInternGlobalLiteral("Command Spaces"));
    return(vcommandLoadSpace(vresourceGet(res, tag)));
}

/* * * * * * * * * * * APPLICATION COMMAND SPACE * * * * * * * * */

/*
 * _writeInitApplicationSpace
 *
 * Load the application command space from the resource file.
 * Also - create our pre-defined vnames.
 */
static void _writeInitApplicationSpace(void)

{     
    int                   i;
    static const char    *predefStrings[_write_Count] = {
        "Write",
        "Append",
        "Tag",
        "Target",
        "Option",
        "As",
        "Copy",
        "Quick",
        "Selection",
        "Again",
        "Reverse",
        "Path",
        "Enable",
        "Disable",  
        "Show",
        "Hide",
	"First",
	"By",
	"Ruler",
	"IconBox",
	"Ribbon",
	"Invisible1",
	"Regexp",
	"Normal Style",
	"Normal",
	"Marker",
	"Change All",
	"Change Selection"
    };

    defaultSpace = 
	writeLoadSpace(vnameInternGlobalLiteral("Application Space"));
    
    vapplicationSetSpaceOwned(vapplicationGetCurrent(), defaultSpace);
  
    /*
     * Setup the additional names that can be entries into the context table
     * for commands
     */

    for (i = 0; i<_write_Count; i++)
      _writePredefs[i] = vnameInternGlobalScribed
	(vcharScribeLiteral(predefStrings[i]));
}

/*
 * _writeIssueApplicationCommand
 *
 * Issues a selector-based command to Preditor
 *
 * Parameters:
 *      id              the name of the command
 *      selector        its selector
 *      attr2value      the context of the command
 *
 * Returns TRUE if a binding was executed
 */
static int _writeIssueApplicationCommand(
    vcommandSelector	*command,
    vdict               *context
    )
{
    int                 selector;
    
    selector = vcommandGetSelector(command);

    switch (selector) {
	
    case comNEW_DOCUMENT:
	/*
	 * Set the wrtDialog (with respect to dialog) to the one this
	 * command originated from.  The new document will be place offset
	 * to this dialog.
	 */
        wrtDialog = (vdialog *) vdictLoad(context, vname_Dialog);
	writeNewDocument();
	return(TRUE);

    case comQUIT:
	if (writeCloseAllDocuments())
	    veventStopProcessing();
	else
	    veventCancelQuit();
	return(TRUE);

    case comABOUT_WRITE:
	/*
	 * If the about dialog is already created, open it (if not open) and
	 * raise it.
	 */
        if (aboutDialog != NULL) {
	    if (!vdialogIsOpen(aboutDialog))
	        vdialogOpen(aboutDialog);
	    vwindowRaise(vdialogGetWindow(aboutDialog));
            return(TRUE);
        }

	/*
	 * Create the About dialog
	 */

	aboutDialog = writeLoadDialog(vnameInternGlobalLiteral("About"));
	writeCenterWindow((vwindow *) aboutDialog);
	vdialogOpen(aboutDialog);
	return(TRUE);

    case comINFORMATION:
	/*
	 * If the info window is already created, open it (if not open) and
	 * raise it.
	 */
        if (infoDialog != NULL) {
	    if (!vdialogIsOpen(infoDialog))
	        vdialogOpen(infoDialog);
	    vwindowRaise(vdialogGetWindow(infoDialog));
            return(TRUE);
        }

	/*
	 * Create the Information dialog
	 */

	infoDialog = writeLoadDialog(vnameInternGlobalLiteral("Help"));
	writeCenterWindow((vwindow *) infoDialog);
	vdialogOpen(infoDialog);
	return(TRUE); 

    case comIMPORT:
	/*
	 * If the Import window is already created, open it (if not open) and
	 * raise it.
	 */
        if (writeImportWindow != NULL) {
	    if (!vdialogIsOpen(xcflchsrGetDialog(writeImportWindow)))
	        vdialogOpen(xcflchsrGetDialog(writeImportWindow));
	    vwindowRaise
	       (vdialogGetWindow(xcflchsrGetDialog(writeImportWindow)));
            return(TRUE);
        }

	/*
	 * Create the Import window dialog
	 */

	if (vprefLoadScribed(vcharScribeLiteral("importsplit")) != NULL)
	   {
	      writeImportWindow = xcflchsrCreateSplit();
	   }
	else
	   {
	      writeImportWindow = xcflchsrCreate();
	   }

	vdialogSetTitleScribed(xcflchsrGetDialog(writeImportWindow),
			       vcharScribeLiteral("Import File"));

	xcflchsrSetApply(writeImportWindow, _writeImportFile);

	vfilechsrSetType(xcflchsrGetFilechsr(writeImportWindow), 
			 vfilechsrGET);
	vfilechsrSetSelection (xcflchsrGetFilechsr(writeImportWindow), 
			       vfilechsrSINGLE);
	vfilechsrSetDirectory(xcflchsrGetFilechsr(writeImportWindow), 
			      vfsGetAppDirPath());
	vfilechsrSetOptions
	   (xcflchsrGetFilechsr(writeImportWindow),
	    (vfilechsrGetOptions(xcflchsrGetFilechsr(writeImportWindow)))
	    | vfilechsrOPTION_FILE_MUST_EXIST);
	
	xcflchsrOpen(writeImportWindow);
	writeBuildWindowMenus();
        return(TRUE);


    case comOPEN_REQUEST:
	/*
	 * If the Open window is already created, open it (if not open) and
	 * raise it.
	 */
        if (writeOpenWindow != NULL) {
	    if (!vdialogIsOpen(vfilechsrGetDialog(writeOpenWindow)))
	        vdialogOpen(vfilechsrGetDialog(writeOpenWindow));
	    vwindowRaise(vdialogGetWindow(vfilechsrGetDialog(writeOpenWindow)));
            return(TRUE);
        }

	/*
	 * Create the Open window dialog
	 */

	writeOpenWindow = vfilechsrCreate();
	vdialogSetTitleScribed(vfilechsrGetDialog(writeOpenWindow),
			       vcharScribeLiteral("Open File"));
	vfilechsrSetApply(writeOpenWindow,     _writeOpenFile);
	vfilechsrSetDirectory(writeOpenWindow, vfsGetAppDirPath());
	vfilechsrSetOptions(writeOpenWindow, 
			    vfilechsrGetOptions(writeOpenWindow) |
			    vfilechsrOPTION_FILE_MUST_EXIST);
	vfilechsrOpen(writeOpenWindow);
	writeBuildWindowMenus();

        return(TRUE);

    case comACTIVATE_SEARCH:
        wrtDialog = (vdialog *) vdictLoad(context, vname_Dialog);
	writeCreateSearchWindow();
	return(TRUE);

    case comSTYLES:
	writeCreateStyleWindow();
	return(TRUE);

    case comWHOLE_WORD:
        writeSearchOptions ^= writeWHOLE_WORD;
        return(TRUE);

    case comCASE_SENSITIVE:
        writeSearchOptions ^= writeCASE_SENSITIVE;
        return(TRUE);

    case comSEARCH_BACKWARDS:
        writeSearchOptions ^= writeBACKWARD_SEARCH;
        return(TRUE);

    case comPATTERN_SEARCH:
        writeSearchOptions ^= writeREGEXP_SEARCH;
        return(TRUE);

    case comWRAP_SEARCH:
        writeSearchOptions ^= writeWRAP_SEARCH;
        return(TRUE);

    case comGLOBAL_SEARCH:
        writeSearchOptions ^= writeGLOBAL_SEARCH;
        return(TRUE);
    }

    return vclassSendSuper(defaultSelectorClass,
			   vcommandISSUE, (command, context));
}

/*
 * _writeQueryApplicationCommand
 *
 * Querys a selector-based command to Preditor
 *
 * Parameters:
 *      id              the name of the command
 *      selector        its selector
 *      attr2value      the context of the command
 *
 * Returns TRUE if a binding was executed
 */
static int _writeQueryApplicationCommand(
    vcommandSelector	*command,
    vdict               *context
    )
{
    int                 selector;

    selector = vcommandGetSelector(command);

    switch (selector) {

    case comWHOLE_WORD:
        vdictStore(context, vname_Toggle, (vchar *)
          ((writePreferences.searchPrefs & writeWHOLE_WORD) ?
           vname_On : vname_Off));
	return(TRUE);

    case comCASE_SENSITIVE:
        vdictStore(context, vname_Toggle, (vchar *)
          ((writePreferences.searchPrefs & writeCASE_SENSITIVE) ?
           vname_On : vname_Off));
	return(TRUE);

    case comSEARCH_BACKWARDS:
        vdictStore(context, vname_Toggle, (vchar *)
          ((writePreferences.searchPrefs & writeBACKWARD_SEARCH) ?
           vname_On : vname_Off));
	return(TRUE);

    case comPATTERN_SEARCH:
        vdictStore(context, vname_Toggle, (vchar *)
          ((writePreferences.searchPrefs & writeREGEXP_SEARCH) ?
           vname_On : vname_Off));
	return(TRUE);

    case comWRAP_SEARCH:
        vdictStore(context, vname_Toggle, (vchar *)
          ((writePreferences.searchPrefs & writeWRAP_SEARCH) ?
           vname_On : vname_Off));
	return(TRUE);

    case comGLOBAL_SEARCH:
        vdictStore(context, vname_Toggle, (vchar *)
          ((writePreferences.searchPrefs & writeGLOBAL_SEARCH) ?
           vname_On : vname_Off));
	return(TRUE);
    }

    return vclassSendSuper(defaultSelectorClass,
			   vcommandQUERY, (command, context));
}

/* * * * * *   STARTUP AND SHUTDOWN * * * * * */

static int mySeperation(vdialogItem *item, vdialogItem *to, unsigned int which)
{
    if (vlafButtItems()/* && vdialogItemHasBorder(item) */)
    {
	if (vlaf3D())
	    return 0;
	else
	    return -vlafLineWidth();
    }
    else
    {
	return 3;  /* laf based constant?? */
    }
}

/*
 * writeStartup
 *
 * One-time setup for application commands, default utilitty and 
 * confirm dialog classes, and more
 */
void writeStartup()
{
    /*
     * Set our application title
     */

    vapplicationSetTitleScribed(vapplicationGetCurrent(),
				vcharScribeLiteral("Micwrite"));

    /*
     * Get our application resource file and preferences file
     */

    writeResFile      = vapplicationGetResources(vapplicationGetCurrent()); 
    writeUserPrefFile = vapplicationGetPreferences(vapplicationGetCurrent());
 
    /*
     * Set up the default selector class for application commands
     */

    defaultSelectorClass = vclassReproduce(vobjectGetCommandClass());

    vclassSetNameScribed(defaultSelectorClass,
			 vcharScribeLiteral("writeSelector"));

    vclassSet(defaultSelectorClass, vcommandISSUE,
	      _writeIssueApplicationCommand);
    vclassSet(defaultSelectorClass, vcommandQUERY,
	      _writeQueryApplicationCommand);

    _writeInitApplicationSpace();
 
    writePreferencesStartup();

    /*
     * Get the string arrays 
     */

    writeMessages =
      vresourceGet(writeResFile, vnameInternGlobalLiteral("Messages"));

    /*
     * The following patches _vdialogGetItemNaturalSeparation, setting
     * it to be 3, instead of 5.  This should be removed when this 
     * constant is a laf attribute
     */

    vclassSet(vdialogGetDefaultItemClass(), 
	      vdialogGET_ITEM_NATURAL_SEPARATION, mySeperation);
    vclassSet((vdialogItemClass *) vtextviewGetDefaultClass(),
	      vdialogGET_ITEM_NATURAL_SEPARATION, mySeperation);
    vclassSet((vdialogItemClass *) vtextitemGetDefaultClass(),
	      vdialogGET_ITEM_NATURAL_SEPARATION, mySeperation);
    vclassSet((vdialogItemClass *) vtextrulerGetDefaultClass(),
	      vdialogGET_ITEM_NATURAL_SEPARATION, mySeperation);
    vclassSet((vdialogItemClass *) vdialogGetBoxItemClass(),
	      vdialogGET_ITEM_NATURAL_SEPARATION, mySeperation);
}

/*
 * writeShutdown
 *
 * Cleanup after ourselves
 */
void writeShutdown()
{
    if (writeOpenWindow != NULL)
       {
	  vfilechsrDestroy(writeOpenWindow);
	  writeOpenWindow = NULL;
       }
    if (writeSaveWindow != NULL)
       {
	  vfilechsrDestroy(writeSaveWindow);
	  writeSaveWindow = NULL;
       }
    if (writeImportWindow != NULL)
       {
	  xcflchsrDestroy(writeImportWindow);
	  writeImportWindow = NULL;
       }
    if (writeExportWindow != NULL)
       {
	  xcflchsrDestroy(writeExportWindow);
	  writeExportWindow = NULL;
       }
    if (writeStyleChooser != NULL)
       {
	  vstylechsrDestroy(writeStyleChooser);
	  writeStyleChooser = NULL;
       }

    if (writeSearchWindow != NULL)
       {
	  vwindowDestroy((vwindow *) writeSearchWindow);
	  writeSearchWindow = NULL;
       }
    if (writeStyleWindow != NULL)
       {
	  vwindowDestroy((vwindow *) writeStyleWindow);
	  writeStyleWindow = NULL;
       }
    if (writeMarkWindow != NULL)
       {
	  vconfirmDestroy(writeMarkWindow);
	  writeMarkWindow = NULL;
       }
    if (writeUnmarkWindow != NULL)
       {
	  vconfirmDestroy(writeUnmarkWindow);
	  writeUnmarkWindow = NULL;
       }

    if (confirmNotice != NULL)
       {
	  vnoticeDestroy(confirmNotice);
	  confirmNotice = NULL;
       }
    if (alertNotice != NULL)
       {
	  vnoticeDestroy(alertNotice);
	  alertNotice = NULL;
       }
    if (aboutDialog != NULL)
       {
	  vdialogDestroy(aboutDialog);
	  aboutDialog = NULL;
       }
    if (infoDialog != NULL)
       {
        vdialogDestroy(infoDialog);
	  infoDialog = NULL;
       }

    /* Force space destruction before we destroy the selector class */

    vapplicationSetSpace(vapplicationGetCurrent(), NULL);
    vclassDestroy(defaultSelectorClass);
}

/*
 * writeCloseAllDocuments
 */
vbool writeCloseAllDocuments()
{
    const vname		*name;
    vstr		*str;
    writeDocument	*scan;

    scan = writeDocumentList;

    while (scan != NULL) {

	if (!vundoIsLogSaved(scan->undoLog) &&
	    (scan->flags & writeDOC_READ_ONLY) == 0) {

	    str = vresourceGetStringAt(writeMessages, writeMSG_SAVE_CHANGES);
	    writeReplaceStrings(&str, vcharScribe(scan->name), NULL);
	    name = writeModalConfirmation(&scan->dialog, str);
	    vstrDestroy(str);

	    if (name == vname_Ok) {
		if (writeSaveDocument(scan, NULL) !=
		    writeSAVED)
		    return(FALSE);
	    }
	    
	    else if (name == vname_Cancel)
		return(FALSE);
		
	}
      
	writeDestroyDocument(scan);

	scan = scan->next;
    }
  
    return( TRUE );
}

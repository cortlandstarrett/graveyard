/* $Id: micdraw.c,v 1.26 1997/10/23 21:39:43 gregt Exp $ */
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

/****************************************************************************
 * Executable Name: micdraw
 * Source Files:    micdraw.c	App command space, init, utility functions
 *		    canvas.c    domain, domain view, domain view event classes
 * 		    document.c  document creating, saving, loading, document
 *				command space.
 * 	       	    object.c    creating & drawing objects, intersection funcs.
 *		    pattern.c   patterns - load/store, using, drawing, etc.
 *		    pen.c	pens - load/store, using, drawing, etc.
 *		    pref.c      Load/store of user prefs & default prefs
 *		    text.c	text objects in canvas - editing & drawing,
 *				applying styles, justification, etc.
 *		    micdas.c	the das code need to make a document a
 *				provider/consumer.
 * Header Files:    micdraw.h 
 * Resource Files:  micdraw.h
 *
 * Managers Illustrated:
 *     Domain Manager, Drawing Manager, Text Manager, Drag Manager
 *
 * Description Of Sample:
 * 
 * This example creates a basic drawing program. The drawing program lets
 * you create objects on a canvas, manipulate these objects, zoom in and out
 * of the document, create patterns and pens, save and load documents,
 * and much more.
 *
 * Things this module demonstrates:
 *   -- Subclassing
 *   -- Use of domains and domainviews
 *   -- Use of domain observers
 *   -- Use of domain view events
 *   -- Use of text objects and text views in domains
 *   -- Drawing patterns, lines with dashes, arrows, etc.
 *   -- Zooming in and out of a domain view
 *   -- Extensive use of the "Track" domain view event
 *   -- Using drag manager to drag patterns and pens around
 *
 * How to use it:
 *
 * The calls are somewhat patterned after the Galaxy API, except with
 * module prefix of "vmdraw" ( Visix Micro Draw )
 *
 * Known bugs / limitations / missing features:
 *
 * Filled ovals and round rects do not work correctly - there is a bug
 *  in the drawing manager with clip paths
 * Layering numbers not updated when copying/cutting/pasting/duplicating
 * Applying Plain style not implemented
 * Objects with thick pens or arrows may draw outside of object bounds - 
 *  causing garbage to be left on screen
 * Revert not implemented
 * Can't "nudge" objects with arrow keys
 * 
 * History:
 *     Written for 2.0 release, 28-Nov-93
 ****************************************************************************/

#include <vport.h>

#ifndef  vstdlibINCLUDED
#include vstdlibHEADER
#endif

#ifndef  vdebugINCLUDED
#include vdebugHEADER
#endif

#ifndef  vexINCLUDED
#include vexHEADER
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

#ifndef  vtimestampINCLUDED
#include vtimestampHEADER
#endif

#ifndef  vscribeINCLUDED
#include vscribeHEADER
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

#ifndef  vprefINCLUDED
#include vprefHEADER
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

#ifndef  vdomainINCLUDED
#include vdomainHEADER
#endif

#ifndef  vcursorINCLUDED
#include vcursorHEADER
#endif

#ifndef  vwindowINCLUDED
#include vwindowHEADER
#endif

#ifndef  vapplicationINCLUDED
#include vapplicationHEADER
#endif

#ifndef  vlafINCLUDED
#include vlafHEADER
#endif

#ifndef  vdialogINCLUDED
#include vdialogHEADER
#endif

#ifndef  vtextitemINCLUDED
#include vtextitemHEADER
#endif

#ifndef  vpaletteINCLUDED
#include vpaletteHEADER
#endif

#ifndef  vdomainviewINCLUDED
#include vdomainviewHEADER
#endif

#ifndef  vconfirmINCLUDED
#include vconfirmHEADER
#endif

#ifndef  vnoticeINCLUDED
#include vnoticeHEADER
#endif

#ifndef  vcolorchsrINCLUDED
#include vcolorchsrHEADER
#endif

#ifndef  vfilechsrINCLUDED
#include vfilechsrHEADER
#endif

#ifndef  vstylechsrINCLUDED
#include vstylechsrHEADER
#endif

#ifndef  vstartupINCLUDED
#include vstartupHEADER
#endif

#include "micdraw.h"

#if vdebugDEBUG
static const char _vmicrodrawTag[] = "vmicrodraw";
#define vdebugTAG _vmicrodrawTag
#endif

/*
 * Globals
 */

vcommandSelectorClass		*defaultSelectorClass	  = NULL;
vmdrawDocument  		*vmdrawDocumentList 	  = NULL;
vmdrawDocument			*vmdrawTargetDocument	  = NULL;
vfilechsr			*vmdrawOpenWindow   	  = NULL;
vfilechsr			*vmdrawSaveWindow   	  = NULL;
vcolorchsr			*vmdrawColorChooser	  = NULL;
vstylechsr			*vmdrawStyleChooser	  = NULL;
vconfirm			*vmdrawDrawingSizeConfirm = NULL;
vconfirm			*vmdrawSetGridConfirm     = NULL;
vdialog				*wrtDialog		  = NULL;
vresource			vmdrawResFile;
vresource			vmdrawUserPrefFile;
vmdrawPen			*vmdrawPens;
vmdrawPen			 vmdrawCurrentPen;
int			    	 vmdrawPenCount;
vmdrawPattern			*vmdrawPatterns;
vmdrawPattern			 vmdrawCurrentPattern;
int			    	 vmdrawPatternCount;
vpoint			    	 vmdrawCurrentPosition = { -1, -1 };
vcommandSpace     		*defaultSpace;
vcolor				*vmdrawLockedColor;
const vchar         		*_vmdrawPredefs[_vmdraw_Count];
vresource		 	 vmdrawMessages;
vcursor				*vmdrawGoodDropCursor;
vcursor				*vmdrawBadDropCursor;


static    vnotice		*confirmNotice = NULL;
static    vnotice               *alertNotice = NULL;
static    vdialog		*aboutDialog = NULL;
static	  vdialog		*infoDialog  = NULL;
          vtimer		*positionTimer = NULL;


int main(
    int          argc,
    char        *argv[]
    )
{
    vfsPath		**paths;
    vfsInfo     	info;
    int			numFiles;
    vbool       	opened = FALSE;

    vprefStoreScribed(vcharScribeLiteral("das"),vcharScribeLiteral(""));
    vstartup(argc, argv);
    vdomainStartup();

    vmdrawStartup();
    vmdrawDocumentStartup();
    vmdrawPenStartup();
    vmdrawPatternStartup();
    vmdrawCanvasStartup();
    vmdrawTextStartup();

    if (vprefLoadScribed(vcharScribeLiteral("das")) != NULL) {
	mdrawOpenServiceChooser();
	opened = TRUE;
    }
    
    /*
     * Now process the arguments
     */

    vfsGetArgs(&numFiles, (const vfsPath ***) &paths);

    while (numFiles-- > 1) {

        if (vfsAccess(paths[numFiles], vfsFILE_EXISTS)) {

            vfsGetFileInfo(paths[numFiles], &info);

            if (vfsIsFile(&info)) {
                vmdrawOpenDocument(paths[numFiles]);
                opened = TRUE;
            }
        }
    }

    if (!opened)
        vmdrawNewDocument();

    veventProcess();
    
    vmdrawPreferencesShutdown();
    vmdrawShutdown();
    vmdrawDocumentShutdown();

    exit(EXIT_SUCCESS);
    return EXIT_FAILURE;
}

/*
 * _vmdrawOpenFile
 *
 * Apply function for Open file chooser - open the selected document
 */
static int _vmdrawOpenFile(vfilechsr *fileChooser, vfsPath *filePath)
{
    vmdrawOpenDocument(filePath);  
    return(TRUE);
}
 
/* * * * * *    Alert and Confiramation dialog handling   * * * * * */

static void _vmdrawPlaceNotice(
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
	vmdrawCenterWindow((vwindow *) notice);
}

/*
 * vmdrawAlert
 *
 * Display an alert with the given message
 */
vnotice *vmdrawAlert(
    vdialog		*dialog,
    vchar		*message
    )
{
    if (alertNotice == NULL)
        alertNotice = vnoticeCreate();
    vnoticeSetText(alertNotice, message);
    _vmdrawPlaceNotice(alertNotice, dialog);
    vdialogOpen(vnoticeGetDialog(alertNotice));
    return(alertNotice);
}

/*
 * vmdrawConfirmation
 *
 * Display a general confirmation dialog with the given message.  Also
 * set the ok and no hooks functions, as well as the confirm's data.
 */
vnotice *vmdrawConfirmation(
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
    _vmdrawPlaceNotice(confirmNotice, dialog);
    vdialogOpen(vnoticeGetDialog(confirmNotice));
    return(confirmNotice);
}

/*
 * vmdrawModalConfirmation
 *
 * Display a general confirmation dialog with the given message.  Also
 * set the ok and no hooks functions, as well as the confirm's data.
 */
const vname *vmdrawModalConfirmation(
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

    _vmdrawPlaceNotice(confirmNotice, dialog);

    return(vnoticeProcess(confirmNotice));
}

/*
 * vmdrawCenterWindow
 *
 * Center the given window in the root window
 */
void vmdrawCenterWindow(
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
 * vmdrawReplaceStrings
 */
void vmdrawReplaceStrings(
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

/* 
 * vmdrawOpenColorChooser
 */
void vmdrawOpenColorChooser()
{
    /*
     * If the color chooser has been created, open (if not open) and raise
     * the color chooser
     */

    if (vmdrawColorChooser != NULL) {
        if (!vdialogIsOpen(vcolorchsrGetDialog(vmdrawColorChooser)))
            vdialogOpen(vcolorchsrGetDialog(vmdrawColorChooser));
        vwindowRaise(vdialogGetWindow(vcolorchsrGetDialog(vmdrawColorChooser)));
        return;
    }
        
    /*
     * Create and open the color chooser
     */

    vmdrawColorChooser = vcolorchsrCreate();
    vcolorchsrOpen(vmdrawColorChooser);
}

/* 
 * vmdrawOpenStyleChooser
 */
void vmdrawOpenStyleChooser()
{
    /*
     * If the style chooser has been created, open (if not open) and raise
     * the style chooser
     */

    if (vmdrawStyleChooser != NULL) {
        if (!vdialogIsOpen(vstylechsrGetDialog(vmdrawStyleChooser)))
            vdialogOpen(vstylechsrGetDialog(vmdrawStyleChooser));
        vwindowRaise(vdialogGetWindow(vstylechsrGetDialog(vmdrawStyleChooser)));
        return;
    }
    
    /*
     * Create and open the style chooser
     */
    
    vmdrawStyleChooser = vstylechsrCreate();
    vstylechsrOpen(vmdrawStyleChooser);
}

static void _setTitle(vdialog *dialog, vstr *suffix, char *name)
{
    vstr	*title;

    title = vstrCloneScribed(vcharScribeLiteral(name));
    title = vstrAppend(title, suffix);
    vdialogSetTitle(dialog, title);
    vstrDestroy(title);
}

/*
 * vmdrawSetTargetDocument
 *
 * Set the target document -- the document that operations from the
 * pattern, pen and style windows will operate on.
 */
void vmdrawSetTargetDocument(
    vmdrawDocument	*data
    )
{
    vstr		*str;

    vmdrawTargetDocument = data;

    if (data == NULL)
	data = vmdrawDocumentList;

    if (data == NULL)
	str = vstrCloneScribed(vcharScribeLiteral(" <No Target>"));
    else {
	str = vstrCloneScribed(vcharScribeLiteral(" ("));
	str = vstrAppend(str, data->name);
	str = vstrAppendScribed(str, vcharScribeLiteral(")"));
    }

    if (vmdrawPenWindow != NULL)
	_setTitle(vmdrawPenWindow, str, "Pen");

    if (vmdrawPatternWindow != NULL)
	_setTitle(vmdrawPatternWindow, str, "Pattern");

    if (vmdrawStyleChooser != NULL)
	_setTitle(vstylechsrGetDialog(vmdrawStyleChooser), str, "Style Chooser");

    vstrDestroy(str);
}

/*
 * _handlePositionTimer
 *
 * This is the timer handler for the position dialog. Every time the
 * handler gets called, we recompute the current position for the domain
 * that the cursor is currently in - and update the position display.
 */
static void _handlePositionTimer(
    register vtimer	*timer
    )
{  
    int         	x, y, locX, locY;
    vmdrawDocument	*data;
    vpoint              pt;
    vrect		*r;
   
    /*
     * If the position window is not created or open - nothing to do
     */

    if (vmdrawPositionWindow == NULL || !vdialogIsOpen(vmdrawPositionWindow))
        return;

    /*
     * Get the current mouse position in root window coordinates
     */

    vwindowGetPointer(vwindowGetRoot(), &x, &y);

    vmdrawCurrentPosition.x = -1;
    vmdrawCurrentPosition.y = -1;

    /*
     * We are going to scan all documents. (we keep a linked list of them,
     * and vmdrawDocumentList points to the head of the lsit).
     * For each document - we see if the mouse is in the domain view area
     * for the document.  Once we find a domain view the mouse is in, we
     * update the global variable vmdrawCurrentPostion, and inval the display.
     * If mouse is not in any domain view - we set vmdrawCurrentPosition to
     * (-1,-1) - causing the display to be empty (no position)
     */

    data = vmdrawDocumentList;

    while (data != NULL) {

	/*
	 * Translate the root window x,y coordinate to window coordinates
	 * for the current document in the scan
	 */

        vwindowTransformPoint(vwindowGetRoot(), (vwindow *) data,
                              x, y, &locX, &locY);

	r = vdomainviewGetViewArea(data->domainView);

	pt.x = locX;
	pt.y = locY;

	/*
	 * Translate the point to domain coordinates
	 */

	vdomainviewTranslatePoint(data->domainView, &pt, 
				  vdomainviewTO_DOMAIN);

	/*
	 * Is the pt in the view area (domain coordinates)
	 */

        if (vrectContainsPoint(r, pt.x, pt.y)) {

            vmdrawCurrentPosition.x = pt.x;
            vmdrawCurrentPosition.y = pt.y;
	    break;
        }

	data = data->next;
    }

    vdialogInvalItem(vmdrawPositionItem, vwindowINVAL_OPAQUE);
}

vdialog *vmdrawLoadDialog(const vname *tag)
{
    vresource   res;

    res = vresourceGet(vmdrawResFile, vnameInternGlobalLiteral("Dialogs"));
    return(vdialogLoad(vresourceGet(res, tag)));
}

vcommandSpace *vmdrawLoadSpace(const vname *tag)
{
    vresource   res;

    res = vresourceGet(vmdrawResFile, vnameInternGlobalLiteral("Command Spaces"));
    return(vcommandLoadSpace(vresourceGet(res, tag)));
}


/* * * * * * * Drawing Size Confirm Dialog Handling * * * * * * * */

/*
 * _vmdrawDrawingSizeApply
 *
 * The apply handler for the drawing size confirmation dialog.
 * Get the height and width text entry values, and resize the
 * domain.
 */
static int _vmdrawDrawingSizeApply(vconfirm *confirm, vevent *ev) 
{
    vtextitem           *hitem, *witem;
    vmdrawDocument      *data;
    int                 width, height;

    data = (vmdrawDocument *) vconfirmGetData(confirm);

    witem = (vtextitem *)
        vdialogFindItem(vconfirmGetDialog(confirm), vname_Width);

    hitem = (vtextitem *)
        vdialogFindItem(vconfirmGetDialog(confirm), vname_Height);


    vexWITH_HANDLING {

	width  = vtextitemGetTextAsInt(witem);
	height = vtextitemGetTextAsInt(hitem);

	if (width > 0 && height > 0) {
	    data->documentWidth  = width;
	    data->documentHeight = height;
	    vdomainResize(vdomainviewGetDomain(data->domainView),
			  data->documentWidth, data->documentHeight);
	}

    }
    vexON_EXCEPTION {
    }
    vexEND_HANDLING; 

    return(TRUE);
}

/*
 * vmdrawSetDrawingSize
 *
 * Load up and initialize the Drawing Size confirm dialog
 */
void vmdrawSetDrawingSize(
    vmdrawDocument *data
    )
{
    vtextitem           *item;

    /*
     * If the drawing size confirm dialog has been created, open it (if
     * not open) - otherwise load it from the resouce file.
     */

    if (vmdrawDrawingSizeConfirm != NULL) {
        if (!vconfirmIsOpen(vmdrawDrawingSizeConfirm))
            vconfirmOpen(vmdrawDrawingSizeConfirm);
    }
    else {
        vmdrawDrawingSizeConfirm = (vconfirm *)
	    vmdrawLoadDialog(vnameInternGlobalLiteral("Drawing Size"));

        vmdrawCenterWindow((vwindow *) vmdrawDrawingSizeConfirm);

        vconfirmOpen(vmdrawDrawingSizeConfirm);
        
        vconfirmSetApplyHook(vmdrawDrawingSizeConfirm,
                             _vmdrawDrawingSizeApply);
    }

    vconfirmSetData(vmdrawDrawingSizeConfirm, data);
   
    /*
     * Initalize the confirm dialog with current width/height values
     */

    item = (vtextitem *)
        vdialogFindItem(vconfirmGetDialog(vmdrawDrawingSizeConfirm),    
                        vname_Width);
    vtextitemSetTextScribed(item, vnumScribeInt(data->documentWidth));
    item = (vtextitem *)
        vdialogFindItem(vconfirmGetDialog(vmdrawDrawingSizeConfirm), 
                        vname_Height);
    vtextitemSetTextScribed(item, vnumScribeInt(data->documentHeight));

}

/* * * * * * * Set Grid Confirm Handling * * * * * * * */

/*
 * Convience macro to retrieve a text item from the grid confirm dialog
 */

#define _getTextItem(c,n)                               \
    (vtextitem *) vdialogFindItem(vconfirmGetDialog(c), \
                                  vnameInternGlobalLiteral(n))

/*
 * _vmdrawSetGridApply
 *
 * The apply function for the Set Grid confirmation dialog - handles
 * setting the grid for the document
 */
static int _vmdrawSetGridApply(vconfirm *confirm, vevent *ev) 
{
    vtextitem           *item;
    vmdrawDocument      *data;
    vdomainGrid         grid;

    data = (vmdrawDocument *) vconfirmGetData(confirm);

    /*
     * Get the values - if there is a bogus entry - don't set the grid
     */

    vexWITH_HANDLING {

	item = _getTextItem(confirm, "XSpacing");
	grid.xSpacing = vtextitemGetTextAsInt(item);

	item = _getTextItem(confirm, "YSpacing");
	grid.ySpacing = vtextitemGetTextAsInt(item);

	item = _getTextItem(confirm, "XSkew");
	grid.xSkew = vtextitemGetTextAsInt(item);

	item = _getTextItem(confirm, "YSkew");
	grid.ySkew = vtextitemGetTextAsInt(item);

	vdomainSetGrid(vdomainviewGetDomain(data->domainView), &grid);

	vdialogInvalItem(vdomainviewGetItem(data->domainView), 0);

    }
    vexON_EXCEPTION {
    }
    vexEND_HANDLING; 

    return(TRUE);
}

/*
 * vmdrawSetGrid
 *
 * Load up and initialize the Drawing Size confirm dialog
 */
void vmdrawSetGrid(
    vmdrawDocument *data
    )
{
    vdomainGrid         *grid;
    vtextitem           *item;

    /*
     * If the set grid confirmation dialog is already created, open it (if
     * not open), otherwise, load it from the resource file.
     */

    if (vmdrawSetGridConfirm != NULL) {
        if (!vconfirmIsOpen(vmdrawSetGridConfirm))
            vconfirmOpen(vmdrawSetGridConfirm);
    }

    else {
        vmdrawSetGridConfirm = (vconfirm *)
	    vmdrawLoadDialog(vnameInternGlobalLiteral("Set Grid"));

        vmdrawCenterWindow((vwindow *) vmdrawSetGridConfirm);

        vconfirmOpen(vmdrawSetGridConfirm);

        vconfirmSetApplyHook(vmdrawSetGridConfirm, _vmdrawSetGridApply);
    }

    vconfirmSetData(vmdrawSetGridConfirm, data);

    /*
     * Initialize the confirmation dialog with values from the document
     */

    grid   = vdomainGetGrid(vdomainviewGetDomain(data->domainView));

    item = _getTextItem(vmdrawSetGridConfirm, "XSpacing");
    vtextitemSetTextScribed(item, vnumScribeInt(grid->xSpacing));
    item = _getTextItem(vmdrawSetGridConfirm, "YSpacing");
    vtextitemSetTextScribed(item, vnumScribeInt(grid->ySpacing));
    item = _getTextItem(vmdrawSetGridConfirm, "XSkew");
    vtextitemSetTextScribed(item, vnumScribeInt(grid->xSkew));
    item = _getTextItem(vmdrawSetGridConfirm, "YSkew");
    vtextitemSetTextScribed(item, vnumScribeInt(grid->ySkew));
}

/* * * * * * * * * * * APPLICATION COMMAND SPACE * * * * * * * * */

/*
 * _vmdrawInitApplicationSpace
 *
 * Load the application command space from the resource file.
 * Also - create our pre-defined vnames.
 */
static void _vmdrawInitApplicationSpace(void)
{      
    int			  i;
    static const char    *predefStrings[_vmdraw_Count] = {
        "Option",
        "As",
        "Front",
        "Back",
        "Forward",
        "Backward",
        "Target",
        "Vertical",
        "Horizontal",
        "Grid",  
        "Limit",
        "Two",
	"None",
	"Normal",
	"Auto",
	"External",
	"Enclose",
	"Single",
	"Live",
	"Objects",
	"All",
	"In"
    };

    defaultSpace =
	vmdrawLoadSpace(vnameInternGlobalLiteral("Application Space"));
    
    vapplicationSetSpaceOwned(vapplicationGetCurrent(), defaultSpace);
  
    /*
     * Setup the additional names that can be entries into the context table
     * for commands
     */

    for (i = 0; i<_vmdraw_Count; i++)
      _vmdrawPredefs[i] = vnameInternGlobalScribed
	(vcharScribeLiteral(predefStrings[i]));
}

/*
 * _vmdrawIssueApplicationCommand
 *
 * Issues a selector-based command to Preditor
 *
 * Parameters:
 *      command		the selector command
 *      context         the context of the command
 *
 * Returns TRUE if a binding was executed
 */
static int _vmdrawIssueApplicationCommand(
    vcommandSelector	*command,
    vdict               *context
    )
{
    int			selector;

    selector = vcommandGetSelector(command);

    switch (selector) {
	
    case comNEW_DOCUMENT:
	/*
	 * Set the wrtDialog (with respect to dialog) to the one this
	 * command originated from.  The new document will be place offset
	 * to this dialog.
	 */
        wrtDialog = (vdialog *) vdictLoad(context, vname_Dialog);
	vmdrawNewDocument();
	return(TRUE);


    case comQUIT:
	if (vmdrawCloseAllDocuments())
	    veventStopProcessing();
	else
	    veventCancelQuit();
	return(TRUE);

    case comABOUT_MICRO_DRAW:
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

	aboutDialog = vmdrawLoadDialog(vnameInternGlobalLiteral("About"));
	vmdrawCenterWindow((vwindow *) aboutDialog);
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

	infoDialog = vmdrawLoadDialog(vnameInternGlobalLiteral("Help"));
	vmdrawCenterWindow((vwindow *) infoDialog);
	vdialogOpen(infoDialog);
	return(TRUE); 

#if (mdrawUSE_DAS)
    case comCONNECT:
	mdrawOpenServiceChooser();
	return(TRUE);
#endif

    case comOPEN_REQUEST:
	/*
	 * If the Open window is already created, open it (if not open) and
	 * raise it.
	 */
        if (vmdrawOpenWindow != NULL) {
	    if (!vdialogIsOpen(vfilechsrGetDialog(vmdrawOpenWindow)))
	        vdialogOpen(vfilechsrGetDialog(vmdrawOpenWindow));
	    vwindowRaise(vdialogGetWindow(vfilechsrGetDialog(vmdrawOpenWindow)));
            return(TRUE);
        }

	/*
	 * Create the Open window dialog
	 */

	vmdrawOpenWindow = vfilechsrCreate();
	vdialogSetTitleScribed(vfilechsrGetDialog(vmdrawOpenWindow),
			       vcharScribeLiteral("Open File"));
	vfilechsrSetApply(vmdrawOpenWindow,     _vmdrawOpenFile);
	vfilechsrSetDirectory(vmdrawOpenWindow, vfsGetAppDirPath());
	vfilechsrSetOptions(vmdrawOpenWindow, 
			    vfilechsrGetOptions(vmdrawOpenWindow) |
			    vfilechsrOPTION_FILE_MUST_EXIST);
	vfilechsrOpen(vmdrawOpenWindow);

        return(TRUE);
    }

    return vclassSendSuper(defaultSelectorClass,
			   vcommandISSUE, (command, context));
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
 * vmdrawStartup
 *
 * One-time setup for application commands, default utilitty and 
 * confirm dialog classes, and more
 */
void vmdrawStartup()
{
    vresource 		res;
    const vname		*goodTag;
    const vname		*badTag;

    /*
     * Set our application title
     */

    vapplicationSetTitleScribed(vapplicationGetCurrent(),
				vcharScribeLiteral("Microdraw"));

    /*
     * Get our application resource file and preferences file
     */

    vmdrawResFile      = vapplicationGetResources(vapplicationGetCurrent()); 
    vmdrawUserPrefFile = vapplicationGetPreferences(vapplicationGetCurrent());
 
    /*
     * Set up the default selector class for application commands
     */

    defaultSelectorClass = vclassReproduce(vobjectGetCommandClass());

    vclassSetNameScribed(defaultSelectorClass,
			 vcharScribeLiteral("vmdrawSelector"));

    vclassSet(defaultSelectorClass, vcommandISSUE,
	      _vmdrawIssueApplicationCommand);

    /*
     * Load the color palette used for creating patterns
     */

    vmdrawPalette = 
	vcolorLoadPalette(vresourceGet(vmdrawResFile, vname_Palette));

    /*
     * Load up the default pens 
     */

    vmdrawPens = vmdrawLoadPens(vmdrawUserPrefFile, &vmdrawPenCount);
    if (vmdrawPens == NULL)
      vmdrawPens = vmdrawLoadPens(vmdrawResFile, &vmdrawPenCount);
    vmdrawCopyPen(vmdrawPens, &vmdrawCurrentPen);

    /*
     * Load up the default patterns 
     */

    vmdrawPatterns = vmdrawLoadPatterns(vmdrawUserPrefFile, &vmdrawPatternCount);
    if (vmdrawPatterns == NULL)
      vmdrawPatterns = vmdrawLoadPatterns(vmdrawResFile, &vmdrawPatternCount);
    vmdrawCopyInitPattern(vmdrawPatterns, &vmdrawCurrentPattern);

    /*
     * Load the locked color.  This is the color used to fill the background
     * of the document palette when the palette entry is "locked" - meaning
     * is won't change back to the arrow palette entry after the object is
     * created.
     */

    vmdrawLockedColor = vresourceTestGet(vmdrawResFile,
		 vnameInternGlobalLiteral("Locked Color"), &res) ?
		   vcolorLoadIntern(res) : NULL;

    _vmdrawInitApplicationSpace();

    vmdrawPreferencesStartup();

    /*
     * Get the string arrays 
     */

    vmdrawMessages =
      vresourceGet(vmdrawResFile, vnameInternGlobalLiteral("Messages"));

    /*
     * Create the position dialog timer
     */
    
    positionTimer = vtimerCreate();

    vtimerSetData(positionTimer, NULL);
    vtimerSetCallback(positionTimer, _handlePositionTimer);
    vtimerSetPeriod(positionTimer, 0, 50*vtimestampMILLISECOND);
    vtimerSetRecurrent(positionTimer);

    /*
     * Get the drop cursors
     */

    res = vresourceGet(vmdrawResFile, vnameInternGlobalLiteral("Cursors"));

    if (vwindowIsMonochrome()) {
	goodTag = vnameInternGlobalLiteral("MonoGoodDropCursor");
	badTag = vnameInternGlobalLiteral("MonoBadDropCursor");
    }
    else {
	goodTag = vnameInternGlobalLiteral("GoodDropCursor");
	badTag = vnameInternGlobalLiteral("BadDropCursor");
    }

    vmdrawBadDropCursor  = vcursorLoad(vresourceGet(res, badTag));
    vmdrawGoodDropCursor = vcursorLoad(vresourceGet(res, goodTag));

    /*
     * The following patches _vdialogGetItemNaturalSeparation, setting
     * it to be 3, instead of 5.  This should be removed when this 
     * constant is a laf attribute
     */

    vclassSet(vdialogGetDefaultItemClass(), 
	      vdialogGET_ITEM_NATURAL_SEPARATION, mySeperation);
    vclassSet((vdialogItemClass *) vdomainviewGetDefaultClass(),
	      vdialogGET_ITEM_NATURAL_SEPARATION, mySeperation);
    vclassSet((vdialogItemClass *) vpaletteGetDefaultClass(),
	      vdialogGET_ITEM_NATURAL_SEPARATION, mySeperation);
}

/*
 * vmdrawShutdown
 *
 * Cleanup after ourselves
 */
void vmdrawShutdown()
{
    int			count;
    vmdrawPen		*pen;
    vmdrawPattern	*pattern;

    /*
     * Save the pens and patterns - saved in the user preference file so
     * when microdrawis started again, his/her pens/patterns will still be
     * there.
     */

    vmdrawSavePens(vmdrawUserPrefFile, vmdrawPens, vmdrawPenCount);
    vmdrawSavePatterns(vmdrawUserPrefFile, vmdrawPatterns, vmdrawPatternCount);

    if (vmdrawOpenWindow != NULL)
        vfilechsrDestroy(vmdrawOpenWindow);
    if (vmdrawSaveWindow != NULL)
        vfilechsrDestroy(vmdrawSaveWindow);
    if (vmdrawColorChooser != NULL)
        vcolorchsrDestroy(vmdrawColorChooser);
    if (vmdrawStyleChooser != NULL)
        vstylechsrDestroy(vmdrawStyleChooser);
    if (vmdrawPenWindow != NULL)
        vdialogDestroy(vmdrawPenWindow);
    if (vmdrawPatternWindow != NULL)
        vdialogDestroy(vmdrawPatternWindow);
    if (vmdrawPositionWindow != NULL)
        vdialogDestroy(vmdrawPositionWindow);
    if (vmdrawDrawingSizeConfirm != NULL)
        vconfirmDestroy(vmdrawDrawingSizeConfirm);
    if (vmdrawSetGridConfirm != NULL)
        vconfirmDestroy(vmdrawSetGridConfirm);

    vcolorDestroy(vmdrawLockedColor);

    if (confirmNotice != NULL)
        vnoticeDestroy(confirmNotice);
    if (alertNotice != NULL)
        vnoticeDestroy(alertNotice);
    if (aboutDialog != NULL)
        vdialogDestroy(aboutDialog);
    if (infoDialog != NULL)
        vdialogDestroy(infoDialog);

    vtimerDestroy(positionTimer);

    /* Destroy the pens */

    count = vmdrawPenCount;
    pen   = vmdrawPens;
    while (count-- > 0)
        vmdrawDestroyPen(pen++);

    /* Destroy the patterns */

    count   = vmdrawPatternCount;
    pattern = vmdrawPatterns;
    while (count-- > 0)
        vmdrawDestroyPattern(pattern++);

    vmemFree(vmdrawPens);
    vmemFree(vmdrawPatterns);

    vmdrawDestroyPen(&vmdrawCurrentPen);
    vmdrawDestroyPattern(&vmdrawCurrentPattern);

    vcolorDestroyPalette(vmdrawPalette);

    vcursorDestroy(vmdrawGoodDropCursor);
    vcursorDestroy(vmdrawBadDropCursor);

    /* Force space destruction before we destroy the selector class */

    vapplicationSetSpace(vapplicationGetCurrent(), NULL);
    vclassDestroy(defaultSelectorClass);
}

/*
 * vmdrawCloseAllDocuments
 */
vbool vmdrawCloseAllDocuments()
{
    const vname		*name;
    vstr		*str;
    vmdrawDocument	*scan;

    scan = vmdrawDocumentList;

    while (scan != NULL) {

	if (!vundoIsLogSaved(scan->undoLog) &&
	    (scan->flags & vmdrawDOC_READ_ONLY) == 0) {

	    str = vresourceGetStringAt(vmdrawMessages, vmdrawMSG_SAVE_CHANGES);
	    vmdrawReplaceStrings(&str, vcharScribe(scan->name), NULL);
	    name = vmdrawModalConfirmation(&scan->dialog, str);
	    vstrDestroy(str);

	    if (name == vname_Ok) {
		if (vmdrawSaveDocument(scan, NULL) !=
		    vmdrawSAVED)
		    return(FALSE);
	    }
	    
	    else if (name == vname_Cancel)
		return(FALSE);
		
	}
      
	vmdrawDestroyDocument(scan);

	scan = scan->next;
    }
  
    return( TRUE );
}

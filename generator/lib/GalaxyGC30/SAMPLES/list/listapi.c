/* $Id: listapi.c,v 1.21 1994/02/16 19:41:11 chad Exp $
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
 * copyright notice in the in the form of "Copyright 1994 Visix Software Inc.,
 * 11440 Commerce Park Drive, Reston, VA  22091. All Rights Reserved" appears
 * in all copies, (ii) both the copyright notice and this permission notice
 * appear in supporting documentation and (iii) you are a valid licensee of
 * Galaxy Application Environment.
 */

/* listapi.c -- C implementation for the list manager api playground
 *
 * vlist is a collection of distinct Galaxy list manager applications,
 * ranging from a simple list to stocks and bondage to life.
 *
 * The various parts of this demo are:
 * vlist.c     -- Chief overlord and starter-up of the other demos.
 * listlife.c  -- Conway's game o' life.
 * listapi.c   -- Fiddle with the API and see what does what. (this file)
 * listcell.c     -- Do in-cell editing.
 *   xincell.h    -- interface to in-cell editing subclass.
 *   incell.c     -- implementation of in-cell editing subclass.
 */

/* This file demonstrates these concepts:
 *    Using the list manager
 *        Custom cell drawing procedures
 *        Selection filters
 *        Selection notify
 *        Selection iterators
 *    Simple subclassing
 *    Use of subordinate dialogs
 *    Use of font and color choosers
 *    Simple use of the command manager.
 */


/* Galaxy headers */
#ifndef vportINCLUDED		/* for v*HEADER */
#include <vport.h>
#endif

#ifndef  vstdlibINCLUDED		/* for bsearch and rand */
#include vstdlibHEADER
#endif

#ifndef  vpoolINCLUDED
#include vpoolHEADER
#endif

#ifndef  vmemINCLUDED
#include vmemHEADER
#endif

#ifndef  vclientINCLUDED
#include vclientHEADER
#endif

#ifndef  veventINCLUDED
#include veventHEADER
#endif

#ifndef  vcommandINCLUDED
#include vcommandHEADER
#endif

#ifndef  vclassINCLUDED
#include vclassHEADER
#endif

#ifndef  vdialogINCLUDED
#include vdialogHEADER
#endif

#ifndef  vcontrolINCLUDED
#include vcontrolHEADER
#endif

#ifndef  vlistINCLUDED
#include vlistHEADER
#endif

#ifndef  vliststrINCLUDED
#include vliststrHEADER
#endif

#ifndef  vlistviewINCLUDED
#include vlistviewHEADER
#endif

#ifndef  vbuttonINCLUDED
#include vbuttonHEADER
#endif

#ifndef  vtextitemINCLUDED
#include vtextitemHEADER
#endif

#ifndef  vfontchsrINCLUDED
#include vfontchsrHEADER
#endif

#ifndef  vcolorchsrINCLUDED
#include vcolorchsrHEADER
#endif

#ifndef  vnumINCLUDED
#include vnumHEADER
#endif


/* Private headers */
#include "listdemo.h"



/* ------------------ Useful macro ------------------ */


#define TAG(s)	vnameInternGlobalLiteral ((s))



/* ------------------ Default values for sizes ------------------ */


#define apiDEFAULT_COLUMN_WIDTH		80
#define apiNARROW_COLUMN_WIDTH		25
#define apiWIDE_COLUMN_WIDTH	       150

#define apiSHORT_ROW_HEIGHT		 9
#define apiTALL_ROW_HEIGHT		60

#define apiRAND_WIDTH_RANGE		90
#define apiRAND_WIDTH_BOTTOM		30
#define apiRAND_HEIGHT_RANGE		60
#define apiRAND_HEIGHT_BOTTOM		 5


/* the apiRock (a place to hide data under) is how this module can easily
 * manipulate multiple windows.  It grabs the rock from underneath the
 * data pointer of whatever object it has handy, and then uses it to 
 * get to interesting componenets.  The rocks themselves come from a pool.
 */
typedef struct apiRock {
    vdialogItem *infoLabel;   /* status line */
    vlistview   *listview;    /* the listview being abused */
    vlist	*imageList;   /* list containing pointers to images */
    vliststr	*stringList;  /* list containing strings */
    vresource    apiResources;/* resource where subordinate dialogs live */
} apiRock;


/* the place where rocks come from */
static vpool *apiRockPool = NULL;


/* holder for the windows that we create, and later will need to destroy */
static windowset *apiWindowset;


/* font chooser */
static vfontchsr	*_apiFontOfWisdom  = NULL;

/* color choosers */
static vcolorchsr	*_apiForegroundColorChooser  = NULL;
static vcolorchsr	*_apiBackgroundColorChooser  = NULL;


/* One of the parts of this demo is drawing a list of images.  Rather than
 * consuming vast tracts of memory by duplicating the image, each image 
 * only exists in one place in memory, and the list cell values are just 
 * pointers to the images.
 */

/* the array of all of our images */
static vimage **imageArray;

/* the number of images in the above array */
static int imageArrayCount;

/* This maps image pointers to their tag names, for use in the "draw both"
 * drawing model
 */
static vdict *imageDict;




/* ------------------ module global variables ------------------ */


/* command subclass to handle the selection type radio-group menu. */
static vcommandSelectorClass	*_apiSelectTypeCommandClass = NULL;

/* command subclass to handle the selection filter radio-group menu. */
static vcommandSelectorClass	*_apiFilterTypeCommandClass = NULL;

/* our vlistview subclass called "api listview" */
static vlistviewClass	*_apilistviewClass = NULL;



/* ------------------ Forward references to other stuff ------------------ */

static void     _apiOpenSetCellValueDialog (apiRock *rock);
static void     _apiCloseSetCellValueDialog (void);
static vdialog *_apiSetCellValueDialog = NULL;

static void     _apiOpenSetScrollbarMarginDialog (apiRock *rock);
static void     _apiCloseSetScrollbarMarginDialog (void);
static vdialog *_apiSetScrollbarMarginDialog = NULL;

static void     _apiOpenSetRowCountDialog (apiRock *rock);
static void     _apiCloseSetRowCountDialog (void);
static vdialog *_apiSetRowCountDialog = NULL;

static void     _apiOpenSetColumnCountDialog (apiRock *rock);
static void     _apiCloseSetColumnCountDialog (void);
static vdialog *_apiSetColumnCountDialog = NULL;

static void     _apiOpenSetColumnWidthDialog (apiRock *rock);
static void     _apiCloseSetColumnWidthDialog (void);
static vdialog *_apiSetColumnWidthDialog = NULL;

static void     _apiOpenSetRowHeightDialog (apiRock *rock);
static void     _apiCloseSetRowHeightDialog (void);
static vdialog *_apiSetRowHeightDialog = NULL;




/* ------------------ Command selector enums ------------------ */

enum { 
    apiSELECT_NO_SELECTION = 1,
    apiSELECT_RECTANGULAR_SELECTION,
    apiSELECT_ONE_ONLY_SELECTION,
    apiSELECT_FREE_SELECTION,
    apiSELECT_EVEN_ODD_SELECTION_FILTER,
    apiSELECT_PRIME_SELECTION_FILTER,
    apiSELECT_NO_SELECTION_FILTER
};




/* ------------------ Random Assortment of Functions ------------------ */


/* _apiNoteTextScribed -- stick some text into our notify region.
 *
 *  -> rock	    -- the apiRock containing pointers to interesting stuff.
 *  -> textScribe   -- the scribe for the text to put in there.
 */
static void _apiNoteTextScribed (apiRock *rock, vscribe *textScribe)
{
    vdialogSetItemTitleScribed (rock->infoLabel, textScribe);

} /* _apiNoteTextScribed */




/* _apiNoteTextLiteral -- convenience function to put a literal string into
 *			our notify region.
 *
 *  -> r        -- the apiRock containing pointers to interesting stuff.
 *  -> L	-- the literal string.
 */
#define _apiNoteTextLiteral(r,L) _apiNoteTextScribed((r), \
						     vcharScribeLiteral((L)));




/* _apiAttrToRock -- map a command's attr2value dictionary to an apiRock
 *		     suitable for further violence.
 *
 *  -> attr2value -- a context dictionary from a command
 * <-             -- the apiRock appropriate for the command's context.
 */
static apiRock *_apiAttrToRock (vdict *attr2value)
{
    vdialog *dialog = (vdialog*)vdictLoad (attr2value, vname_Dialog);

    return ((apiRock*)vdialogGetData(dialog));

} /* _apiAttrToRock */




/* _apiFontApply -- apply function for our font chooser.
 *
 *  -> fontChooser	-- the font chooser the user apply'd on
 *  -> font		-- the currently selected font
 * <-  		        -- TRUE if font is acceptable, FALSE otherwise
 */
static int _apiFontApply (vfontchsr *fontChooser, vfont *font)
{
    apiRock *rock = (apiRock*)vfontchsrGetData (fontChooser);
    
    vdialogSetItemFont (vlistviewGetItem(rock->listview), font);

    vlistviewSetRowHeight (rock->listview, vlistviewALL_ROWS,
			   vfontHeight(font) + vfontDescent(font));

    _apiNoteTextLiteral (rock,
			 "vdialogSetItemFont (vlistviewGetItem(listview), "
			 "font);");
    
    return (TRUE);

} /* _apiFontApply */




/* _apiColorForegroundApply -- apply function for our foreground color chooser.
 *
 *  -> colorChooser	-- the color chooser the user apply'd on
 *  -> color		-- the currently selected color
 */
static void _apiColorForegroundApply (vcolorchsr *colorChooser, vcolor *color)
{
    apiRock *rock = (apiRock*)vcolorchsrGetData (colorChooser);

    vdialogSetItemForeground (vlistviewGetItem(rock->listview), color);

    _apiNoteTextLiteral (rock, 
			 "vdialogSetItemForeground (vlistviewGetItem(listview)"
			 ", color);");

} /* _apiColorForegroundApply */




/* _apiColorBackgroundApply -- apply function for our background color chooser.
 *
 *  -> colorChooser	-- the color chooser the user apply'd on
 *  -> color		-- the currently selected color
 */
static void _apiColorBackgroundApply (vcolorchsr *colorChooser, vcolor *color)
{
    apiRock *rock = (apiRock*)vcolorchsrGetData (colorChooser);

    vdialogSetItemBackground (vlistviewGetItem(rock->listview), color);

    _apiNoteTextLiteral (rock,
			 "vdialogSetItemBackground (vlistviewGetItem(listview)"
			 ", color);");

} /* _apiColorBackgroundApply */




/* _apiListviewSelectionNotify -- selection notify proc for the listview.
 *
 *  -> listview	   -- the listview o' happiness
 *  -> frob	   -- one of these three:
 *		      vlistviewSELECTION_WILL_CHANGE
 *		      vlistviewSELECTION_IS_CHANGING
 *		      vlistviewSELECTION_HAS_CHANGED
 */
static void _apiListviewSelectionNotify (vlistview *listview, int frob)
{
    apiRock *rock = (apiRock*)vlistviewGetData (listview);

    switch (frob) {

	case vlistviewSELECTION_WILL_CHANGE: {
	    _apiNoteTextLiteral (rock, "selection will change");
	    break;
	}

	case vlistviewSELECTION_IS_CHANGING: {
	    vlist	*list = vlistviewGetList (listview);
	    int		 row = 0, column = 0;
	    vpoint	 point;

	    vlistviewGetLastPointerPosition (listview,
					     &point.x, &point.y);
					     
	    vlistviewMapPointToCell (listview, &point, &row, &column);

	    if (list == vliststrGetList(rock->stringList)) {
		vchar	*value;
		
		value = (vchar*)vlistGetCellValue (list, row, column);
		
		_apiNoteTextScribed (rock, vscribeScribeMulti
				     (vcharScribeLiteral ("selection is "
							  "changing: "),
				      ((value == NULL)
				       ? vcharScribeLiteral ("NULL value.")
				       : vcharScribe ((vchar*)vlistGetCellValue 
						      (list, row, column))),
				      NULL));
	    } else {
		vimage *value;

		value = (vimage*)vlistGetCellValue (list, row, column);

		_apiNoteTextScribed (rock, vscribeScribeMulti
				     (vcharScribeLiteral ("selection is "
							  "changing: "),
				      ((value == NULL)
				       ? vcharScribeLiteral ("NULL value.")
				       : vcharScribe (vdictLoad
						      (imageDict, value))),
				      NULL));
	    }

	    break;
	}

	case vlistviewSELECTION_HAS_CHANGED: {
	    _apiNoteTextLiteral (rock, "selection has changed");
	    break;
	}
    }
} /* _apiListviewSelectionNotify */




/* _apiListviewScrollNotify -- override method telling when the listview
 * 			has been scrolled.
 * 
 *  -> listview	    -- da listview
 *  -> horzDistance -- # of pixels^H^H^H^H^H^H user space units scrolled
 *		       horizontally
 *  -> vertDistance -- ditto, but vertically.
 */
static void _apiListviewScrollNotify (vlistview *listview, 
				      int horzDistance, int vertDistance)
{
    apiRock *rock = (apiRock*)vlistviewGetData (listview);

    _apiNoteTextScribed (rock, vscribeScribeMulti
			 (vcharScribeLiteral ("Scrolling: "),
			  vnumScribeInt (horzDistance),
			  vcharScribeLiteral (" horizontally, "),
			  vnumScribeInt (vertDistance),
			  vcharScribeLiteral (" vertically."),
			  NULL));

} /* _apiListviewScrollNotify */




/* _apiListviewTraverseVector -- give feedback when keyboard traversal
 *			is happening.
 *
 *  -> listview	    -- the listview
 *  -> rowDelta	    -- row delta
 *  -> columnDelta  -- column delta.  (great comments, huh?)
 */
static void _apiListviewTraverseVector (vlistview *listview,
					int rowDelta, int columnDelta)
{
    apiRock *rock = (apiRock*)vlistviewGetData (listview);
    _apiNoteTextScribed (rock, vscribeScribeMulti
			 (vcharScribeLiteral ("Focus move: "),
			  vnumScribeInt (rowDelta),
			  ((rowDelta == 1)
			   ? vcharScribeLiteral (" row, ")
			   : vcharScribeLiteral (" rows, ")),
			  vnumScribeInt (columnDelta),
			  ((columnDelta == 1)
			   ? vcharScribeLiteral (" column. ")
			   : vcharScribeLiteral (" columns. ")),
			  NULL));

    /* since this is a method that does Real Work, funnel it back to the
     * listview class.  This gives us an opportunity to fiddle with the
     * row and column delta if we really wanted to. */

    vclassSend (vlistviewGetDefaultClass(),
		vlistviewTRAVERSE_VECTOR,
		(listview, rowDelta, columnDelta));
    
} /* _apiListviewTraverseVector */




/* _apiEvenOddSelectionFilter -- filter out every other cell (i.e. all
 *			cells whose row+column sum is even.
 *
 *  -> listview	   -- the listview filtering the selection
 *  -> selection   -- the selection being filtered.
 */
static void _apiEvenOddSelectionFilter (vlistview *listview,
					vlistSelection *selection)
{
    vlistIterator	iterator;
    int			row, column;

    /* iterate over selection removing the cells we don't want. */

    vlistInitSelectionIterator (&iterator, selection);

    while (vlistNextIterator (&iterator)) {
	row = vlistGetIteratorRow (&iterator);
	column = vlistGetIteratorColumn (&iterator);

	if ((row + column) % 2) {
	    vlistUnselectCell (vlistviewGetList (listview),
			       selection, row, column);
	}
    }

    vlistDestroyIterator (&iterator);

} /* _apiEvenOddSelectionFilter */




/* _apiStringContentProc -- draws the list's cell interpreting the cell's
 *			    contents as a string.
 *
 *  -> listview    -- the listview needing a cell drawn
 *  -> row, column -- the cell to be drawn
 *  -> selected    -- TRUE if the cell should be drawn selected, FALSE
 *		      otherwise.
 *  -> rect        -- the cell's rectangle.
 *
 * This is actually the default way the List Manager draws cells if you
 * don't specify a content proc.
 */
static void _apiStringContentProc (vlistview *listview, int row, int column,
				   int selected, vrect *rect)
{
    const void *data;
    short cellmargin;
    vrect anotherRect; /* so that we don't change the rect given to us */

    /* this is the way vlistview draws its cell contents in all 
     * look and feels
     */
    if (vlistviewGetList(listview) != NULL) {
	data = vlistGetCellValue (vlistviewGetList(listview), row, column);
	
	if (data != NULL) {
	    cellmargin = vclassGet (vlistviewGetClass(listview), 
				    vlistviewCELL_CONTENT_INDENT);
	    anotherRect = *rect;
	    anotherRect.x += cellmargin;
	    anotherRect.w -= cellmargin;
	    vdrawRectShowCenterY ((vchar *)data, &anotherRect);
	}
    }
   
} /* _apiStringContentProc */




/* _apiImageContentProc -- draws the list's cell interpreting the cell's
 *			   contents as an image.
 *
 *  -> listview    -- the listview needing a cell drawn
 *  -> row, column -- the cell to be drawn
 *  -> selected    -- TRUE if the cell should be drawn selected, FALSE
 *		      otherwise.
 *  -> rect        -- the cell's rectangle.
 */
static void _apiImageContentProc (vlistview *listview, int row, int column,
				  int selected, vrect *rect)
{
    const void *data;

    /* use the macro version just for fun */
    data = vlistMGetCellValue (vlistviewGetList(listview), row, column);

    if (data != NULL) {
	vdrawMoveTo (rect->x + 3, rect->y + 3);

	if (vimageGetTransparency ((vimage*)data)) {
	    vdrawImageCompositeIdent ((vimage*)data);
	} else {
	    vdrawImageIdent ((vimage*)data);
	}
    }

} /* _apiImageContentProc */





/* _apiBothContentProc -- draws the list's cell interpreting the cell's
 *			  contents as an image, as well as looking up the
 *			  image's name and displaying that as well.
 *
 *  -> listview    -- the listview needing a cell drawn
 *  -> row, column -- the cell to be drawn
 *  -> selected    -- TRUE if the cell should be drawn selected, FALSE
 *		      otherwise.
 *  -> rect        -- the cell's rectangle.
 */
static void _apiBothContentProc (vlistview *listview, int row, int column,
				 int selected, vrect *rect)
{
    const vname *tagge;
    vimage *image;
    vrect anotherRect;

    image = (vimage*)vlistGetCellValue (vlistviewGetList(listview),
					row, column);

    if (image != NULL) {

	/* draw the image */
	vdrawMoveTo (rect->x + 3, rect->y + 3);

	if (vimageGetTransparency (image)) {
	    vdrawImageCompositeIdent (image);
	} else {
	    vdrawImageIdent (image);
	}
	/* figure out where the name should go */
	anotherRect = *rect;
	anotherRect.x += vimageGetWidth(image) + 5;

	/* determine the image name */
	tagge = vdictLoad (imageDict, image);

	/* display it */
	vdrawRectShowCenterY (tagge, &anotherRect);
    }

} /* _apiBothContentProc */




/* table of primes for determining primeness of a number.  This table
 * covers primes up to 200 */

static int primecount = 48;

static int primes[] = {
      2,   3,   5,   7,  11,  13,  17,  19,  23,  29,  31,  37,  41,  43, 
     47,  53,  59,  61,  67,  71,  73,  79,  83,  89,  97, 101, 103, 107,
    109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181,
    191, 193, 197, 199
};




/* comparison function for bsearch */
static int _apiIsPrimeCompar (const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
} /* _apiIsPrimeCompar */




/* _apiIsPrime -- determines the primeness of a given number.
 *
 *  -> num	-- the prime candidate.
 * <-		-- TRUE if the number is prime, FALSE otherwise.
 *
 * Note -- this function only handles primes up to the size of the prime table
 */
static int _apiIsPrime (int num)
{
    return ((int)bsearch (&num, primes, primecount,
			  sizeof(int), _apiIsPrimeCompar));
} /* apiIsPrime */




/* _apiPrimeSelectionFilter -- filter out cells whose row+column sums to a
 *			prime.
 *
 *  -> listview	   -- the listview filtering the selection
 *  -> selection   -- the selection being filtered.
 */
static void _apiPrimeSelectionFilter (vlistview *listview,
				      vlistSelection *selection)
{
    vlistIterator	iterator;
    int			row, column;

    /* iterate over the selection, removing cells we don't want. */

    vlistInitSelectionIterator (&iterator, selection);

    while (vlistNextIterator (&iterator)) {
	row = vlistGetIteratorRow (&iterator);
	column = vlistGetIteratorColumn (&iterator);

	if (!_apiIsPrime(row + column)) {
	    vlistUnselectCell (vlistviewGetList (listview),
			       selection, row, column);
	}
    }

    vlistDestroyIterator (&iterator);
   
} /* _apiPrimeSelectionFilter */




/* _apiSetupImageList -- stuff images into a list.
 *
 *  -> appResource -- the resource that contains the image dictionary
 *
 * It gets the images from a dictionary called "listdemoAPI_IMAGES"
 * It modifies _apiImageList as well.
 */
static void _apiSetupImageList (apiRock *rock)
{
    size_t	   component;
    vresource      imagedictRes, imageRes;
    const vname   *tag;
    int		    i, j, val;

    if (imageDict == NULL) {
	imageDict = vdictCreate (vdictHashGeneric);
	imagedictRes = vresourceGet (rock->apiResources, TAG("Images"));
	imageArrayCount = vresourceCountComponents (imagedictRes);
	imageArray = (vimage**)vmemAlloc (sizeof(vimage*) * imageArrayCount);

	for (component = 0; component < imageArrayCount; component++) {
	    imageRes = vresourceGetNthComponent (imagedictRes, component,&tag);
	    imageArray[component] = vimageLoad (imageRes);
	    vdictStore (imageDict, imageArray[component], tag);
	}
    }

    if (rock->imageList == NULL) {
	rock->imageList = vlistCreate ();
	vlistSetRowCount (rock->imageList, 50);
	vlistSetColumnCount (rock->imageList, 50);
    }

    for (i = 0; i < vlistGetRowCount(rock->imageList); i++) {
	for (j = 0; j < vlistGetColumnCount(rock->imageList); j++) {
	    val = rand() % imageArrayCount;
	    vlistSetCellValue (rock->imageList, i, j, imageArray[val]);
	}
    }

} /* _apiSetupImageList */




/* _apiRemoveReferences -- clears out the use of an apiRock that will shortly
 *			   cease to exist.  It closes any subordinate dialogs
 *			   that are affecting the listview under this rock,
 *			   and clears out their data pointers.
 *
 *  -> rock -- the apiRock what will shortly go away.
 */
static void _apiRemoveReferences (apiRock *rock)
{
    /* make sure that anybody with a reference to us gets cleaned out */
    if (_apiFontOfWisdom != NULL) {
	if (vfontchsrGetData (_apiFontOfWisdom) == rock) {
	    vfontchsrSetData (_apiFontOfWisdom, NULL);
	    vfontchsrClose (_apiFontOfWisdom);
	}
    }

    if (_apiForegroundColorChooser != NULL) {
	if (vcolorchsrGetData (_apiForegroundColorChooser) == rock) {
	    vcolorchsrSetData (_apiForegroundColorChooser, NULL);
	    vcolorchsrClose (_apiForegroundColorChooser);
	}
    }

    if (_apiBackgroundColorChooser != NULL) {
	if (vcolorchsrGetData (_apiBackgroundColorChooser) == rock) {
	    vcolorchsrSetData (_apiBackgroundColorChooser, NULL);
	    vcolorchsrClose (_apiBackgroundColorChooser);
	}
    }

    if (_apiSetCellValueDialog != NULL) {
	if (vdialogGetData (_apiSetCellValueDialog) == rock) {
	    vdialogSetData (_apiSetCellValueDialog, NULL);
	    vdialogClose (_apiSetCellValueDialog);
	}
    }

    if (_apiSetScrollbarMarginDialog != NULL) {
	if (vdialogGetData (_apiSetScrollbarMarginDialog) == rock) {
	    vdialogSetData (_apiSetScrollbarMarginDialog, NULL);
	    vdialogClose (_apiSetScrollbarMarginDialog);
	}
    }

    if (_apiSetRowCountDialog != NULL) {
	if (vdialogGetData (_apiSetRowCountDialog) == rock) {
	    vdialogSetData (_apiSetRowCountDialog, NULL);
	    vdialogClose (_apiSetRowCountDialog);
	}
    }

    if (_apiSetColumnCountDialog != NULL) {
	if (vdialogGetData (_apiSetColumnCountDialog) == rock) {
	    vdialogSetData (_apiSetColumnCountDialog, NULL);
	    vdialogClose (_apiSetColumnCountDialog);
	}
    }

    if (_apiSetColumnWidthDialog != NULL) {
	if (vdialogGetData (_apiSetColumnWidthDialog) == rock) {
	    vdialogSetData (_apiSetColumnWidthDialog, NULL);
	    vdialogClose (_apiSetColumnWidthDialog);
	}
    }

    if (_apiSetRowHeightDialog != NULL) {
	if (vdialogGetData (_apiSetRowHeightDialog) == rock) {
	    vdialogSetData (_apiSetRowHeightDialog, NULL);
	    vdialogClose (_apiSetRowHeightDialog);
	}
    }

} /* _apiRemoveReferences */




/* _apiCleanupDialog -- destroy any subordinate objects that won't be destroyed
 *		        automagically.  In this case, the vlist's need to be
 *			excised, and the apiRock returned to its pool.
 *
 *  -> dialog -- the dialog to cleanup after
 */
static void _apiCleanupDialog (vdialog *dialog)
{
    apiRock *rock = (apiRock*)vdialogGetData (dialog);

    /* make sure that folks refering to this rock are turned off */
    _apiRemoveReferences (rock);

    /* string lists clean up after themselves */
    vliststrDestroy (rock->stringList);

    if (rock->imageList != NULL) {
	vlistDestroy (rock->imageList); /* the actual image storage is in
					 * the image dictionary*/
    }

    vpoolFree (apiRockPool, rock);

} /* _apiCleanupDialog */




/* ------------------ Command implementation ------------------ */

/* these are the functions called when function commands get issued.
 * The ordering of these functions in the source file are arbitrary.
 * search for the one you want.  The table of mappings between functions
 * and command tags is found in the "mappings" section that follows.
 */



/* _apiCloseIssue -- issue close command - close the window.
 *
 *  -> func	  -- the command being handled.
 *  -> attr2value -- attribute dictionary.
 * <-		  -- TRUE if we handled it, FALSE otherwise
 */
static int _apiCloseIssue (vcommandFunction *func, vdict *attr2value)
{
    apiRock *rock = _apiAttrToRock (attr2value);
    vdialog *dialog;
    
    /* wave good bye */
    
    _apiNoteTextLiteral (rock, "Bye Bye!");

    dialog = (vdialog*)vdictLoad (attr2value, vname_Dialog);

    _apiCleanupDialog (dialog);
    vwindowDestroyLater (vdialogGetWindow(dialog));

    /* since we're destroying it, we don't need our windowset to keep
     * track of it
     */
    windowsetRemoveDialog (apiWindowset, dialog);
    
    return (TRUE);

} /* _apiCloseIssue */




/* _apiSelectAllIssue -- issue command to select all
 *
 *  -> func	  -- the command being handled.
 *  -> attr2value -- attribute dictionary.
 * <-		  -- TRUE if we handled the command, FALSE otherwise
 */
static int _apiSelectAllIssue (vcommandFunction *func, vdict *attr2value)
{
    apiRock *rock = _apiAttrToRock (attr2value);

    vlistSelectAll (vlistviewGetList(rock->listview),
		    vlistviewGetSelection(rock->listview));

    _apiNoteTextLiteral (rock, "vlistSelectAll (vlistviewGetList(view), "
			 "vlistviewGetSelection(view));");

    return (TRUE);

} /* _apiSelectAllIssue */




/* _apiUnselectAllIssue -- issue command to select all
 *
 *  -> func	  -- the command being handled.
 *  -> attr2value -- attribute dictionary.
 * <-		  -- TRUE if we handled the command, FALSE otherwise
 */
static int _apiUnselectAllIssue (vcommandFunction *func, vdict *attr2value)
{
    apiRock *rock = _apiAttrToRock (attr2value);

    vlistUnselectAll (vlistviewGetList(rock->listview),
		      vlistviewGetSelection(rock->listview));

    _apiNoteTextLiteral (rock, "vlistUnselectAll (vlistviewGetList(view), "
			 "vlistviewGetSelection(view));");
    return (TRUE);

} /* _apiUnselectAllIssue */




/* _apiSelectRandomIssue -- issue command to select randomly
 *
 *  -> func	  -- the command being handled.
 *  -> attr2value -- attribute dictionary.
 * <-		  -- TRUE if we handled the command, FALSE otherwise
 */
static int _apiSelectRandomIssue (vcommandFunction *func, vdict *attr2value)
{
    apiRock *rock = _apiAttrToRock (attr2value);
    int		 i, row, column, width, height;
    vlist	*list = vlistviewGetList (rock->listview);
    int		 rowCount, columnCount;

    rowCount = vlistGetRowCount (list);
    columnCount = vlistGetColumnCount (list);

    for (i = 0; i < 14; i++) {
	int blorf;
	
	blorf = rand();
	row = abs(blorf) % columnCount;
	
	blorf = rand();
	column = abs(blorf) % rowCount;

	blorf = rand();
	width = abs(blorf) % 20; /* !!! parameterize */
	
	blorf = rand();
	height = abs(blorf) % 20; /* !!! ditto        */
	
	vlistSelectRange (list,
			  vlistviewGetSelection(rock->listview),
			  row, column, width, height);
    }

    _apiNoteTextLiteral (rock, "vlistSelectRange (vlistviewGetList(view), "
			 "vlistviewGetSelection(view), r, c, w, h);");
    return (TRUE);

} /* _apiSelectRandomIssue */




/* _apiUnselectRandomIssue -- issue command to unselect randomly
 *
 *  -> func	  -- the command being handled.
 *  -> attr2value -- attribute dictionary.
 * <-		  -- TRUE if we handled the command, FALSE otherwise
 */
static int _apiUnselectRandomIssue (vcommandFunction *func, vdict *attr2value)
{
    apiRock *rock = _apiAttrToRock (attr2value);
    int		 i, row, column, width, height;
    vlist	*list = vlistviewGetList (rock->listview);
    int		 rowCount, columnCount;

    rowCount = vlistGetRowCount (list);
    columnCount = vlistGetColumnCount (list);

    for (i = 0; i < 14; i++) {
	int blorf;
	
	blorf = rand();
	row = abs(blorf) % columnCount;
	
	blorf = rand();
	column = abs(blorf) % rowCount;

	blorf = rand();
	width = abs(blorf) % 20; /* !!! parameterize */
	
	blorf = rand();
	height = abs(blorf) % 20; /* !!! ditto        */
	
	vlistUnselectRange (list,
			    vlistviewGetSelection(rock->listview),
			    row, column, width, height);
    }

    _apiNoteTextLiteral (rock, "vlistUnselectRange (vlistviewGetList(view), "
			 "vlistviewGetSelection(view), r, c, w, h);");
    return (TRUE);

} /* _apiUnselectRandomIssue */




/* _apiRandomRowHeightIssue -- issue command to randomize row heights
 *
 *  -> func	  -- the command being handled.
 *  -> attr2value -- attribute dictionary.
 * <-		  -- TRUE if we handled the command, FALSE otherwise
 */
static int _apiRandomRowHeightIssue (vcommandFunction *func, vdict *attr2value)
{
    apiRock *rock = _apiAttrToRock (attr2value);
    int 	 row;
    vlist	*list = vlistviewGetList(rock->listview);
    
    for (row = 0;  row < vlistGetRowCount (list);  row++) {

	int blorf = rand();

	blorf = ((abs(blorf) % apiRAND_HEIGHT_RANGE) + apiRAND_HEIGHT_BOTTOM);

	vlistviewSetRowHeight (rock->listview, row, blorf);
    }

    _apiNoteTextLiteral (rock, 
			 "vlistviewSetRowHeight (listview, row, height);");
    return (TRUE);

} /* _apiRandomRowHeightIssue */




/* _apiRandomColumnWidthIssue -- issue command to randomize column widths
 *
 *  -> func	  -- the command being handled.
 *  -> attr2value -- attribute dictionary.
 * <-		  -- TRUE if we handled the command, FALSE otherwise
 */
static int _apiRandomColumnWidthIssue (vcommandFunction *func, 
				       vdict *attr2value)
{
    apiRock *rock = _apiAttrToRock (attr2value);
    int 	 column;
    vlist	*list = vlistviewGetList(rock->listview);
    
    for (column = 0;  column < vlistGetColumnCount (list);  column++) {

	int blorf = rand();

	blorf = ((abs(blorf) % apiRAND_WIDTH_RANGE) + apiRAND_WIDTH_BOTTOM);

	vlistviewSetColumnWidth (rock->listview, column, blorf);
    }

    _apiNoteTextLiteral (rock,
			 "vlistviewSetColumnWidth (listview, column, width);");
    return (TRUE);

} /* _apiRandomColumnWidthIssue */




/* _apiShortRowsIssue -- issue command to make all rows short
 *
 *  -> func	  -- the command being handled.
 *  -> attr2value -- attribute dictionary.
 * <-		  -- TRUE if we handled the command, FALSE otherwise
 */
static int _apiShortRowsIssue (vcommandFunction *func, vdict *attr2value)
{
    apiRock *rock = _apiAttrToRock (attr2value);

    vlistviewSetRowHeight (rock->listview, vlistviewALL_ROWS,
			   apiSHORT_ROW_HEIGHT);

    _apiNoteTextScribed (rock, vscribeScribeMulti 
			 (vcharScribeLiteral("vlistviewSetRowHeight "
					     "(listview, vlistviewALL_ROWS, "),
			  vnumScribeInt (apiSHORT_ROW_HEIGHT),
			  vcharScribeLiteral (");"),
			  NULL));
    return (TRUE);

} /* _apiShortRowsIssue */




/* _apiNarrowColumnsIssue -- issue command to make all columns narrow
 *
 *  -> func	  -- the command being handled.
 *  -> attr2value -- attribute dictionary.
 * <-		  -- TRUE if we handled the command, FALSE otherwise
 */
static int _apiNarrowColumnsIssue (vcommandFunction *func, vdict *attr2value)
{
    apiRock *rock = _apiAttrToRock (attr2value);

    vlistviewSetColumnWidth (rock->listview, vlistviewALL_COLUMNS,
			     apiNARROW_COLUMN_WIDTH);

    _apiNoteTextScribed (rock, vscribeScribeMulti 
			 (vcharScribeLiteral ("vlistviewSetColumnWidth "
					      "(listview, vlistviewALL_"
					      "COLUMNS, "),
			  vnumScribeInt (apiNARROW_COLUMN_WIDTH),
			  vcharScribeLiteral (");"),
			  NULL));
    return (TRUE);

} /* _apiNarrowColumnsIssue */




/* _apiTallRowsIssue -- issue command to make all rows tall
 *
 *  -> func	  -- the command being handled.
 *  -> attr2value -- attribute dictionary.
 * <-		  -- TRUE if we handled the command, FALSE otherwise
 */
static int _apiTallRowsIssue (vcommandFunction *func, vdict *attr2value)
{
    apiRock *rock = _apiAttrToRock (attr2value);

    vlistviewSetRowHeight (rock->listview, vlistviewALL_ROWS,
			   apiTALL_ROW_HEIGHT);

    _apiNoteTextScribed (rock, vscribeScribeMulti 
			 (vcharScribeLiteral ("vlistviewSetRowHeight "
					      "(listview, vlistviewALL_"
					      "ROWS, "),
			  vnumScribeInt (apiTALL_ROW_HEIGHT),
			  vcharScribeLiteral (");"),
			  NULL));
    return (TRUE);

} /* _apiTallRowsIssue */




/* _apiWideColumnsIssue -- issue command to make all columns wide
 *
 *  -> func	  -- the command being handled.
 *  -> attr2value -- attribute dictionary.
 * <-		  -- TRUE if we handled the command, FALSE otherwise
 */
static int _apiWideColumnsIssue (vcommandFunction *func, vdict *attr2value)
{
    apiRock *rock = _apiAttrToRock (attr2value);

    vlistviewSetColumnWidth (rock->listview, vlistviewALL_COLUMNS,
			     apiWIDE_COLUMN_WIDTH);

    _apiNoteTextScribed (rock, vscribeScribeMulti 
			 (vcharScribeLiteral("vlistviewSetRowHeight "
					     "(listview, vlistviewALL_ROWS, "),
			  vnumScribeInt (apiWIDE_COLUMN_WIDTH),
			  vcharScribeLiteral (");"),
			  NULL));
    return (TRUE);

} /* _apiWideColumnsIssue */





/* _apiSetFontIssue -- issue command to bring up the font chooser.
 *
 *  -> func	  -- the command being handled.
 *  -> attr2value -- attribute dictionary.
 * <-		  -- TRUE if we handled the command, FALSE otherwise
 */
static int _apiSetFontIssue (vcommandFunction *func, vdict *attr2value)
{
    apiRock *rock = _apiAttrToRock (attr2value);

    /* if the font chooser hasn't been born yet, create it. */

    if (_apiFontOfWisdom == NULL) {
	_apiFontOfWisdom = vfontchsrCreate ();
	vfontchsrSetApply (_apiFontOfWisdom, _apiFontApply);
    }
    
    vfontchsrSetFont (_apiFontOfWisdom,
		      vdialogDetermineItemFont(vlistviewGetItem
					       (rock->listview)));
    vfontchsrSetData (_apiFontOfWisdom, rock);
    vfontchsrOpen (_apiFontOfWisdom);

    _apiNoteTextLiteral (rock, "vfontchsrOpen (fontchsr);");

    return (TRUE);

} /* _apiSetFontIssue */




/* _apiSetForegroundIssue -- issue command to bring up a color chooser to
 *			set the foreground color.
 *
 *  -> func	  -- the command being handled.
 *  -> attr2value -- attribute dictionary.
 * <-		  -- TRUE if we handled the command, FALSE otherwise
 */
static int _apiSetForegroundIssue (vcommandFunction *func, vdict *attr2value)
{
    apiRock *rock = _apiAttrToRock (attr2value);

    /* if the foreground color chooser hasn't been created yet, create it */

    if (_apiForegroundColorChooser == NULL) {
	_apiForegroundColorChooser = vcolorchsrCreate ();
	vcolorchsrSetApply (_apiForegroundColorChooser,
			    _apiColorForegroundApply);
    }

    /* set the color to the current foreground color */
    vcolorchsrSetColor (_apiForegroundColorChooser,
			vdialogDetermineItemForeground
			(vlistviewGetItem(rock->listview)));
    vcolorchsrSetData (_apiForegroundColorChooser, rock);
    vcolorchsrOpen (_apiForegroundColorChooser);

    _apiNoteTextLiteral (rock, "vcolorchsrOpen (colorchsr);");

    return (TRUE);

} /* _apiSetForegroundIssue */




/* _apiSetBackgroundIssue -- issue command to bring up a color chooser to
 *			set the foreground color.
 *
 *  -> func	  -- the command being handled.
 *  -> attr2value -- attribute dictionary.
 * <-		  -- TRUE if we handled the command, FALSE otherwise
 */
static int _apiSetBackgroundIssue (vcommandFunction *func, vdict *attr2value)
{
    apiRock *rock = _apiAttrToRock (attr2value);

    /* if the birth hasn't been created it, background color chooser it! */

    if (_apiBackgroundColorChooser == NULL) {
	_apiBackgroundColorChooser = vcolorchsrCreate ();
	vcolorchsrSetApply (_apiBackgroundColorChooser, 
			    _apiColorBackgroundApply);
    }

    /* set the color to the current background color */
    vcolorchsrSetColor (_apiBackgroundColorChooser,
			vdialogDetermineItemBackground
			(vlistviewGetItem(rock->listview)));
    vcolorchsrSetData (_apiBackgroundColorChooser, rock);
    vcolorchsrOpen (_apiBackgroundColorChooser);

    _apiNoteTextLiteral (rock, "vcolorchsrOpen (colorchsr);");

    return (TRUE);

} /* _apiSetBackgroundIssue */




/* _apiScroll2SelectionIssue -- issue command to scroll the selection into view
 *
 *  -> func	  -- the command being handled.
 *  -> attr2value -- attribute dictionary.
 * <-		  -- TRUE if we handled the command, FALSE otherwise
 */
static int _apiScroll2SelectionIssue (vcommandFunction *func, 
				      vdict *attr2value)
{
    apiRock *rock = _apiAttrToRock (attr2value);

    vlistviewScrollSelectionIntoView (rock->listview);
    
    _apiNoteTextLiteral (rock, "vlistviewScrollSelectionIntoView (listview);");

    return (TRUE);

} /* _apiScroll2SelectionIssue */




/* _apiScroll2FocusIssue -- issue command to scroll the focus into view
 *
 *  -> func	  -- the command being handled.
 *  -> attr2value -- attribute dictionary.
 * <-		  -- TRUE if we handled the command, FALSE otherwise
 */
static int _apiScroll2FocusIssue (vcommandFunction *func, vdict *attr2value)
{
    apiRock *rock = _apiAttrToRock (attr2value);

    vlistviewScrollFocusIntoView (rock->listview);

    _apiNoteTextLiteral (rock, "vlistviewScrollFocusIntoView (listview);");

    return (TRUE);

} /* _apiScroll2FocusIssue */




/* _apiScrollLeftIssue -- issue command to scroll 1 cell left
 *
 *  -> func	  -- the command being handled.
 *  -> attr2value -- attribute dictionary.
 * <-		  -- TRUE if we handled the command, FALSE otherwise
 */
static int _apiScrollLeftIssue (vcommandFunction *func, vdict *attr2value)
{
    apiRock *rock = _apiAttrToRock (attr2value);

    /* scroll row delta and column delta */
    vlistviewScroll (rock->listview, 0, -1);

    _apiNoteTextLiteral (rock, "vlistviewScroll (listview, 0, -1);");

    return (TRUE);

} /* _apiScrollLeftIssue */




/* _apiScrollRightIssue -- issue command to scroll 1 cell rights
 *
 *  -> func	  -- the command being handled.
 *  -> attr2value -- attribute dictionary.
 * <-		  -- TRUE if we handled the command, FALSE otherwise
 */
static int _apiScrollRightIssue (vcommandFunction *func, vdict *attr2value)
{
    apiRock *rock = _apiAttrToRock (attr2value);

    /* scroll row delta and column delta */
    vlistviewScroll (rock->listview, 0, 1);

    _apiNoteTextLiteral (rock, "vlistviewScroll (listview, 0, 1);");

    return (TRUE);

} /* _apiScrollRightIssue */




/* _apiScrollUpIssue -- issue command to scroll 1 cell up
 *
 *  -> func	  -- the command being handled.
 *  -> attr2value -- attribute dictionary.
 * <-		  -- TRUE if we handled the command, FALSE otherwise
 */
static int _apiScrollUpIssue (vcommandFunction *func, vdict *attr2value)
{
    apiRock *rock = _apiAttrToRock (attr2value);

    /* scroll row delta and column delta */
    vlistviewScroll (rock->listview, -1, 0);

    _apiNoteTextLiteral (rock, "vlistviewScroll (listview, -1, 0);");

    return (TRUE);

} /* _apiScrollUpIssue */




/* _apiScrollDownIssue -- issue command to scroll 1 cell down
 *
 *  -> func	  -- the command being handled.
 *  -> attr2value -- attribute dictionary.
 * <-		  -- TRUE if we handled the command, FALSE otherwise
 */
static int _apiScrollDownIssue (vcommandFunction *func, vdict *attr2value)
{
    apiRock *rock = _apiAttrToRock (attr2value);

    /* scroll row delta and column delta */
    vlistviewScroll (rock->listview, 1, 0);

    _apiNoteTextLiteral (rock, "vlistviewScroll (listview, 1, 0);");

    return (TRUE);

} /* _apiScrollDownIssue */




/* _apiScrollAroundIssue -- issue command to scroll around
 *
 *  -> func	  -- the command being handled.
 *  -> attr2value -- attribute dictionary.
 * <-		  -- TRUE if we handled the command, FALSE otherwise
 */
static int _apiScrollAroundIssue (vcommandFunction *func, vdict *attr2value)
{
    apiRock *rock = _apiAttrToRock (attr2value);

    /* ??? work around bug in menu/listviews.  This causes the menu to
     * contain part of the scrolled list. */
    vdialogItemDrawDevice (vlistviewGetItem (rock->listview));

    /* should do some kind of randomization here */
    /* the vlistviewDraws are here to force a redraw rather than waiting
     * for update events. */
    vlistviewScroll (rock->listview,  0, 1);
    vlistviewDraw (rock->listview);
    vlistviewScroll (rock->listview,  1, -1);
    vlistviewDraw (rock->listview);
    vlistviewScroll (rock->listview,  0, 2);
    vlistviewDraw (rock->listview);
    vlistviewScroll (rock->listview,  2, 1);
    vlistviewDraw (rock->listview);
    vlistviewScroll (rock->listview,  1, -1);
    vlistviewDraw (rock->listview);
    vlistviewScroll (rock->listview,  0, -2);
    vlistviewDraw (rock->listview);
    vlistviewScroll (rock->listview, -1, 1);
    vlistviewDraw (rock->listview);
    vlistviewScroll (rock->listview,  0, 1);
    vlistviewDraw (rock->listview);
    vlistviewScroll (rock->listview,  3, -3);
    vlistviewDraw (rock->listview);
    vlistviewScroll (rock->listview,  0, -1);
    vlistviewDraw (rock->listview);
    vlistviewScroll (rock->listview, -3, -1);
    vlistviewDraw (rock->listview);
    vlistviewScroll (rock->listview,  1, 1);
    vlistviewDraw (rock->listview);
    vlistviewScroll (rock->listview,  2, -1);
    vlistviewDraw (rock->listview);
    vlistviewScroll (rock->listview,  0, 3);
    vlistviewDraw (rock->listview);

    _apiNoteTextLiteral (rock, "vlistviewScroll (listview, rowDelta, "
			 "columnDelta);");

    return (TRUE);

} /* _apiScrollAroundIssue */




/* _apiScrollHomeIssue -- issue command to scroll to (0,0)
 *
 *  -> func	  -- the command being handled.
 *  -> attr2value -- attribute dictionary.
 * <-		  -- TRUE if we handled the command, FALSE otherwise
 */
static int _apiScrollHomeIssue (vcommandFunction *func, vdict *attr2value)
{
    apiRock *rock = _apiAttrToRock (attr2value);

    vlistviewScrollToCell (rock->listview, 0, 0);

    _apiNoteTextLiteral (rock, "vlistviewScrollToCell (listview, 0, 0);");

    return (TRUE);

} /* _apiETScrollHome */




/* _apiScrollEndIssue -- issue command to scroll to bottom-right
 *
 *  -> func	  -- the command being handled.
 *  -> attr2value -- attribute dictionary.
 * <-		  -- TRUE if we handled the command, FALSE otherwise
 */
static int _apiScrollEndIssue (vcommandFunction *func, vdict *attr2value)
{
    apiRock *rock = _apiAttrToRock (attr2value);
    vlist	*list = vlistviewGetList (rock->listview);

    vlistviewScrollToCell (rock->listview, 
			   vlistGetRowCount(list) - 1,
			   vlistGetColumnCount(list) - 1);

    _apiNoteTextScribed (rock, vscribeScribeMulti 
			 (vcharScribeLiteral ("vlistviewScrollToCell "
					      "(listview, "),
			  vnumScribeInt (vlistGetRowCount(list) - 1),
			  vcharScribeLiteral (", "),
			  vnumScribeInt (vlistGetColumnCount(list) - 1),
			  vcharScribeLiteral (");"),
			  NULL));
    return (TRUE);

} /* _apiScrollEndIssue */




/* _apiCountSelectedCellsIssue -- issue command to count # of selected cells
 *
 *  -> func	  -- the command being handled.
 *  -> attr2value -- attribute dictionary.
 * <-		  -- TRUE if we handled the command, FALSE otherwise
 */
static int _apiCountSelectedCellsIssue (vcommandFunction *func, 
					vdict *attr2value)
{
    apiRock *rock = _apiAttrToRock (attr2value);
    int		count;

    count = vlistCountSelectedCells (vlistviewGetList(rock->listview),
				     vlistviewGetSelection(rock->listview));

    _apiNoteTextScribed (rock, vscribeScribeMulti
			 (vcharScribeLiteral ("Counted "),
			  vnumScribeInt (count),
			  (count==1) 
			  ? vcharScribeLiteral (" cell.")
			  : vcharScribeLiteral (" cells."),
			  NULL));
    return (TRUE);

} /* _apiCountSelectedCellsIssueIssue */




/* _apiIterateCellsIssue -- issue command to iterate over the selection
 *
 *  -> func	  -- the command being handled.
 *  -> attr2value -- attribute dictionary.
 * <-		  -- TRUE if we handled the command, FALSE otherwise
 */
static int _apiIterateCellsIssue (vcommandFunction *func, vdict *attr2value)
{
    apiRock *rock = _apiAttrToRock (attr2value);
    vlistIterator	iterator;

    vlistInitSelectionIterator (&iterator,
				vlistviewGetSelection(rock->listview));

    while (vlistNextIterator(&iterator)) {
	int	row, column;

	row = vlistGetIteratorRow (&iterator);
	column = vlistGetIteratorColumn (&iterator);

	_apiNoteTextScribed (rock, vscribeScribeMulti
			     (vcharScribeLiteral ("Iterated over ("),
			      vnumScribeInt (row),
			      vcharScribeLiteral (", "),
			      vnumScribeInt (column),
			      vcharScribeLiteral (") with contents "),
			      vcharScribe ((vchar*)vlistGetCellValue
					   (vlistviewGetList(rock->listview),
					    row, column)),
			      NULL));
    }

    vlistDestroyIterator (&iterator);

    return (TRUE);

} /* _apiIterateCellsIssue */




/* _apiAtLeastOneIssue -- issue command to set at-least-one selection.
 *
 *  -> func	  -- the command being handled.
 *  -> attr2value -- attribute dictionary.
 * <-		  -- TRUE if we handled the command, FALSE otherwise
 */
static int _apiAtLeastOneIssue (vcommandFunction *func, vdict *attr2value)
{
    apiRock *rock = _apiAttrToRock (attr2value);
    /* the toggling of the menu checkbox is handled automagically */
    
    if (vlistHasAtLeastOneSelection (vlistviewGetList(rock->listview),
				     vlistviewGetSelection(rock->listview))) {

	vlistSetAtLeastOneSelection (vlistviewGetList(rock->listview),
				     vlistviewGetSelection(rock->listview),
				     FALSE);
	_apiNoteTextLiteral (rock, "vlistSetAtLeastOneSelection "
			     "(vlistviewGetList("
			     "view), vlistviewGetSelection(view), FALSE);");
    } else {

	vlistSetAtLeastOneSelection (vlistviewGetList(rock->listview),
				     vlistviewGetSelection(rock->listview),
				     TRUE);
	_apiNoteTextLiteral (rock, "vlistSetAtLeastOneSelection "
			     "(vlistviewGetList("
			     "view), vlistviewGetSelection(view), TRUE);");
    }

    return (TRUE);

} /* _apiAtLeastOneIssue */




/* _apiImmutableIssue -- issue command to set immutable selection
 *
 *  -> func	  -- the command being handled.
 *  -> attr2value -- attribute dictionary.
 * <-		  -- TRUE if we handled the command, FALSE otherwise
 */
static int _apiImmutableIssue (vcommandFunction *func, vdict *attr2value)
{
    apiRock *rock = _apiAttrToRock (attr2value);
    /* the toggling of the menu checkbox is handled automagically */

    if (vlistIsSelectionImmutable (vlistviewGetList(rock->listview),
				 vlistviewGetSelection(rock->listview))) {

	vlistSetSelectionImmutable (vlistviewGetList(rock->listview),
				    vlistviewGetSelection(rock->listview),
				    FALSE);
	_apiNoteTextLiteral (rock, "vlistSetSelectionImmutable "
			     "(vlistviewGetList("
			     "view), vlistviewGetSelection(view), FALSE);");
    } else {

	vlistSetSelectionImmutable (vlistviewGetList(rock->listview),
				 vlistviewGetSelection(rock->listview),
				 TRUE);
	_apiNoteTextLiteral (rock, "vlistSetSelectionImmutable "
			     "(vlistviewGetList("
			     "view), vlistviewGetSelection(view), TRUE);");
    }

    return (TRUE);

} /* _apiImmutableIssue */




/* _apiNoExtendSelectionIssue -- issue command to turn off extend selection.
 *
 *  -> func       -- the command being handled
 *  -> attr2value -- attribute dictioanry
 * <-		  -- TRUE if we handled the command, FALSE otherwise
 */
static int _apiNoExtendSelectionIssue (vcommandFunction *func, 
				       vdict *attr2value)
{
    apiRock *rock = _apiAttrToRock (attr2value);

    /* the toggling of the menu radio button is handled automagically */
    
    vlistSetExtendColumnSelection (vlistviewGetList(rock->listview),
				   vlistviewGetSelection(rock->listview),
				   FALSE);

    vlistSetExtendRowSelection (vlistviewGetList(rock->listview),
				vlistviewGetSelection(rock->listview), FALSE);

    _apiNoteTextLiteral (rock, "Turned off selection extension.");


    return (TRUE);

} /* _apiNoExtendSelectionIssue */




/* _apiExtendRowIssue -- issue command to set row selection extension
 *
 *  -> func	  -- the command being handled.
 *  -> attr2value -- attribute dictionary.
 * <-		  -- TRUE if we handled the command, FALSE otherwise
 */
static int _apiExtendRowIssue (vcommandFunction *func, vdict *attr2value)
{
    apiRock *rock = _apiAttrToRock (attr2value);

    /* the toggling of the menu radio button is handled automagically */
    
    vlistSetExtendColumnSelection (vlistviewGetList(rock->listview),
				   vlistviewGetSelection(rock->listview),
				   FALSE);

    vlistSetExtendRowSelection (vlistviewGetList(rock->listview),
				vlistviewGetSelection(rock->listview), TRUE);

    _apiNoteTextLiteral (rock, "vlistSetExtendRowSelection (vlistviewGetList("
			 "view), vlistviewGetSelection(view), TRUE);");

    return (TRUE);

} /* _apiExtendRowIssue */




/* _apiExtendColumnIssue -- issue command to set column selection extension
 *
 *  -> func	  -- the command being handled.
 *  -> attr2value -- attribute dictionary.
 * <-		  -- TRUE if we handled the command, FALSE otherwise
 */
static int _apiExtendColumnIssue (vcommandFunction *func, vdict *attr2value)
{
    apiRock *rock = _apiAttrToRock (attr2value);

    /* the toggling of the menu radio button is handled automagically */
    
    vlistSetExtendRowSelection (vlistviewGetList(rock->listview),
				vlistviewGetSelection(rock->listview), FALSE);

    vlistSetExtendColumnSelection (vlistviewGetList(rock->listview),
				   vlistviewGetSelection(rock->listview),
				   TRUE);

    _apiNoteTextLiteral (rock, "vlistSetExtendRowSelection (vlistviewGetList("
			 "view), vlistviewGetSelection(view), TRUE);");

    return (TRUE);

} /* _apiExtendColumnIssue */




/* _apiNoRearrangeIssue -- issue command to turn off rearranging.
 *
 *  -> func	  -- the command being handled.
 *  -> attr2value -- attribute dictionary.
 * <-		  -- TRUE if we handled the command, FALSE otherwise
 */
static int _apiNoRearrangeIssue (vcommandFunction *func, vdict *attr2value)
{
    apiRock *rock = _apiAttrToRock (attr2value);

    /* the toggling of the menu checkbox is handled automagically */

    vlistviewSetRearrange (rock->listview, vlistviewNO_REARRANGE);

    return (TRUE);

} /* _apiNoRearrangeIssue */




/* _apiRowRerrangeIssue -- issue command to turn on/off row rearranging
 *
 *  -> func	  -- the command being handled.
 *  -> attr2value -- attribute dictionary.
 * <-		  -- TRUE if we handled the command, FALSE otherwise
 */
static int _apiRowRearrangeIssue (vcommandFunction *func, vdict *attr2value)
{
    apiRock *rock = _apiAttrToRock (attr2value);

    /* the toggling of the menu checkbox is handled automagically */

    vlistviewSetRearrange (rock->listview, vlistviewROW_REARRANGE);

    return (TRUE);

} /* _apiRowRearrangeIssue */




/* _apiColumnRearrangeIssue -- issue command to turn on/off column rearranging
 *
 *  -> func	  -- the command being handled.
 *  -> attr2value -- attribute dictionary.
 * <-		  -- TRUE if we handled the command, FALSE otherwise
 */
static int _apiColumnRearrangeIssue (vcommandFunction *func, vdict *attr2value)
{
    apiRock *rock = _apiAttrToRock (attr2value);

    /* the toggling of the menu checkbox is handled automagically */

    vlistviewSetRearrange (rock->listview, vlistviewCOLUMN_REARRANGE);

    return (TRUE);

} /* _apiColumnRearrangeIssue */




/* _apiBorderIssue -- issue command to turn on/off the border
 *
 *  -> func	  -- the command being handled.
 *  -> attr2value -- attribute dictionary.
 * <-		  -- TRUE if we handled the command, FALSE otherwise
 */
static int _apiBorderIssue (vcommandFunction *func, vdict *attr2value)
{
    apiRock *rock = _apiAttrToRock (attr2value);

    /* the toggling of the menu checkbox is handled automagically */

    if (vlistviewHasBorder (rock->listview)) {

	vlistviewSetBorder (rock->listview, FALSE);
	_apiNoteTextLiteral (rock, "vlistviewSetBorder (listview, FALSE);");

    } else {

	vlistviewSetBorder (rock->listview, TRUE);
	_apiNoteTextLiteral (rock, "vlistviewSetBorder (listview, TRUE);");

    }

    /* could also do vdialogSetItemBorder (vlistviewGetItem(listview), T/F); */

    return (TRUE);

} /* _apiBorderIssue */




/* _apiAutoscrollIssue -- issue command to turn on/off autoscrolling
 *
 *  -> func	  -- the command being handled.
 *  -> attr2value -- attribute dictionary.
 * <-		  -- TRUE if we handled the command, FALSE otherwise
 */
static int _apiAutoscrollIssue (vcommandFunction *func, vdict *attr2value)
{
    apiRock *rock = _apiAttrToRock (attr2value);

    /* the toggling of the menu checkbox is handled automagically */

    if (vlistviewHasAutoScroll (rock->listview)) {

	vlistviewSetAutoScroll (rock->listview, FALSE);
	_apiNoteTextLiteral (rock, "vlistviewSetAutoscroll "
			     "(listview, FALSE);");

    } else {

	vlistviewSetAutoScroll (rock->listview, TRUE);
	_apiNoteTextLiteral (rock, "vlistviewSetAutoscroll (listview, TRUE);");

    }

    return (TRUE);

} /* _apiAutoscrollIssue */




/* _apiHorzBarIssue -- issue command to turn on/off horizontal scrollbar
 *
 *  -> func	  -- the command being handled.
 *  -> attr2value -- attribute dictionary.
 * <-		  -- TRUE if we handled the command, FALSE otherwise
 */
static int _apiHorzBarIssue (vcommandFunction *func, vdict *attr2value)
{
    apiRock *rock = _apiAttrToRock (attr2value);

    /* the toggling of the menu checkbox is handled automagically */

    if (vlistviewHasHorzBar (rock->listview)) {

	vlistviewSetHorzBar (rock->listview, FALSE);
	_apiNoteTextLiteral (rock, "vlistviewSetHorzBar (listview, FALSE);");

    } else {

	vlistviewSetHorzBar (rock->listview, TRUE);
	_apiNoteTextLiteral (rock, "vlistviewSetHorzBar (listview, TRUE);");

    }

    return (TRUE);

} /* _apiHorzBarIssue */




/* _apiVertBarIssue -- issue command to turn on/off vertical scrollbar
 *
 *  -> func	  -- the command being handled.
 *  -> attr2value -- attribute dictionary.
 * <-		  -- TRUE if we handled the command, FALSE otherwise
 */
static int _apiVertBarIssue (vcommandFunction *func, vdict *attr2value)
{
    apiRock *rock = _apiAttrToRock (attr2value);
    /* the toggling of the menu checkbox is handled automagically */

    if (vlistviewHasVertBar (rock->listview)) {

	vlistviewSetVertBar (rock->listview, FALSE);
	_apiNoteTextLiteral (rock, "vlistviewSetVertBar (listview, FALSE);");

    } else {

	vlistviewSetVertBar (rock->listview, TRUE);
	_apiNoteTextLiteral (rock, "vlistviewSetVertBar (listview, TRUE);");

    }

    return (TRUE);

} /* _apiVertBarIssue */




/* _apiTraversalWrapIssue -- issue command to turn on/off traversal wrap
 *
 *  -> func	  -- the command being handled.
 *  -> attr2value -- attribute dictionary.
 * <-		  -- TRUE if we handled the command, FALSE otherwise
 */
static int _apiTraversalWrapIssue (vcommandFunction *func, vdict *attr2value)
{
    apiRock *rock = _apiAttrToRock (attr2value);
    /* the toggling of the menu checkbox is handled automagically */

    if (vlistviewHasTraversalWrap (rock->listview)) {

	vlistviewSetTraversalWrap (rock->listview, FALSE);
	_apiNoteTextLiteral (rock, "vlistviewSetTraversalWrap "
			     "(listview, FALSE);");

    } else {

	vlistviewSetTraversalWrap (rock->listview, TRUE);
	_apiNoteTextLiteral (rock, "vlistviewSetTraversalWrap "
			     "(listview, TRUE);");

    }

    return (TRUE);

} /* _apiTraversalWrapIssue */




/* _apiGrabbingHandIssue -- issue command to turn on/off grabbing hand
 *
 *  -> func	  -- the command being handled.
 *  -> attr2value -- attribute dictionary.
 * <-		  -- TRUE if we handled the command, FALSE otherwise
 */
static int _apiGrabbingHandIssue (vcommandFunction *func, vdict *attr2value)
{
    apiRock *rock = _apiAttrToRock (attr2value);
    /* the toggling of the menu checkbox is handled automagically */

    if (vlistviewHasGrabbingHand (rock->listview)) {

	vlistviewSetGrabbingHand (rock->listview, FALSE);
	_apiNoteTextLiteral (rock, "vlistviewSetGrabbingHand "
			     "(listview, FALSE);");

    } else {

	vlistviewSetGrabbingHand (rock->listview, TRUE);
	_apiNoteTextLiteral (rock, "vlistviewSetGrabbingHand "
			     "(listview, TRUE);");

    }

    return (TRUE);

} /* _apiGrabbingHandIssue */




/* _apiSelectionSenseIssue -- issue command to turn on/off selection sense
 *
 *  -> func	  -- the command being handled.
 *  -> attr2value -- attribute dictionary.
 * <-		  -- TRUE if we handled the command, FALSE otherwise
 */
static int _apiSelectionSenseIssue (vcommandFunction *func, vdict *attr2value)
{
    apiRock *rock = _apiAttrToRock (attr2value);
    /* the toggling of the menu checkbox is handled automagically */

    if (vlistviewHasSelectionSense (rock->listview)) {

	vlistviewSetSelectionSense (rock->listview, FALSE);
	_apiNoteTextLiteral (rock, "vlistviewSetSelectionSense "
			     "(listview, FALSE);");

    } else {

	vlistviewSetSelectionSense (rock->listview, TRUE);
	_apiNoteTextLiteral (rock, "vlistviewSetSelectionSense "
			     "(listview, TRUE);");
    }

    return (TRUE);

} /* _apiSelectionSenseIssue */




/* _apiDrawingSelectionIssue -- issue command to turn on/off drawing selection
 *
 *  -> func	  -- the command being handled.
 *  -> attr2value -- attribute dictionary.
 * <-		  -- TRUE if we handled the command, FALSE otherwise
 */
static int _apiDrawingSelectionIssue (vcommandFunction *func, 
				      vdict *attr2value)
{
    apiRock *rock = _apiAttrToRock (attr2value);
    /* the toggling of the menu checkbox is handled automagically */

    if (vlistviewHasDrawingSelection (rock->listview)) {

	vlistviewSetDrawingSelection (rock->listview, FALSE);
	_apiNoteTextLiteral(rock, "vlistviewSetDrawingSelection "
			    "(listview, FALSE);");

    } else {

	vlistviewSetDrawingSelection (rock->listview, TRUE);
	_apiNoteTextLiteral(rock, "vlistviewSetDrawingSelection "
			    "(listview, TRUE);");
    }

    return (TRUE);

} /* _apiDrawingSelectionIssue */




/* _apiKeyboardSelectionIssue -- issue command to turn on/off keyboard 
 *			selection
 *
 *  -> func	  -- the command being handled.
 *  -> attr2value -- attribute dictionary.
 * <-		  -- TRUE if we handled the command, FALSE otherwise
 */
static int _apiKeyboardSelectionIssue (vcommandFunction *func, 
				       vdict *attr2value)
{
    apiRock *rock = _apiAttrToRock (attr2value);
    /* the toggling of the menu checkbox is handled automagically */

    if (vlistviewHasUseKeyboardSelection (rock->listview)) {

	vlistviewSetUseKeyboardSelection (rock->listview, FALSE);
	_apiNoteTextLiteral (rock, "vlistviewSetUseKeyboardSelection "
			     "(listview, FALSE);");

    } else {

	vlistviewSetUseKeyboardSelection (rock->listview, TRUE);
	_apiNoteTextLiteral (rock, "vlistviewSetUseKeyboardSelection "
			     "(listview, TRUE);");
    }

    return (TRUE);

} /* _apiKeyboardSelectionIssue */




/* _apiKeyboardTraversalIssue -- issue command to enable / disable item
 *
 *  -> func	  -- the command being handled.
 *  -> attr2value -- attribute dictionary.
 * <-		  -- TRUE if we handled the command, FALSE otherwise
 */
static int _apiKeyboardTraversalIssue (vcommandFunction *func, 
				       vdict *attr2value)
{
    apiRock *rock = _apiAttrToRock (attr2value);
    /* the toggling of the menu checkbox is handled automagically */

    if (vlistviewHasUseKeyboardTraversal (rock->listview)) {

	vlistviewSetUseKeyboardTraversal (rock->listview, FALSE);
	_apiNoteTextLiteral (rock, "vlistviewSetUseKeyboardTraversal "
			     "(listview, FALSE);");

    } else {

	vlistviewSetUseKeyboardTraversal (rock->listview, TRUE);
	_apiNoteTextLiteral (rock, "vlistviewSetUseKeyboardTraversal "
			     "(listview, TRUE);");
    }

    return (TRUE);

} /* _apiKeyboardTraversalIssue */




/* _apiIssue -- issue command to enable / disable the listview
 *
 *  -> func	  -- the command being handled.
 *  -> attr2value -- attribute dictionary.
 * <-		  -- TRUE if we handled the command, FALSE otherwise
 */
static int _apiDisableIssue (vcommandFunction *func, vdict *attr2value)
{
    apiRock *rock = _apiAttrToRock (attr2value);
    /* the toggling of the menu checkbox is handled automagically */

    if (vdialogItemIsEnabled(vlistviewGetItem(rock->listview))) {

	vdialogDisableItem (vlistviewGetItem(rock->listview));
	_apiNoteTextLiteral (rock, "vdialogDisableItem (vlistviewGetItem("
			     "listview));");

    } else {

	vdialogEnableItem (vlistviewGetItem(rock->listview));
	_apiNoteTextLiteral (rock, "vdialogEnableItem (vlistviewGetItem("
			     "listview));");
    }

    return (TRUE);

} /* _apiDisableIssue */





/* _apiSetCellValueIssue -- issue command to open up a dialog to set cell's
 *			values
 *
 *  -> func	  -- the command being handled.
 *  -> attr2value -- attribute dictionary.
 * <-		  -- TRUE if we handled the command, FALSE otherwise
 */
static int _apiSetCellValueIssue (vcommandFunction *func, vdict *attr2value)
{
    apiRock *rock = _apiAttrToRock (attr2value);

    if (vlistviewGetList(rock->listview) == vliststrGetList(rock->stringList)){
	_apiOpenSetCellValueDialog (rock);
	
	_apiNoteTextLiteral (rock, "Opened cell value editing dialog.\n");
    } else {
	_apiNoteTextLiteral (rock, 
			     "Cell value editing dialog only "
			     "supported for strings.");
    }

    return (TRUE);

} /* _apiSetCellValueIssue */




/* _apiSetScrollbarMarginIssue -- issue command to open up a dialog to set
 *			the scrollbar margin
 *
 *  -> func	  -- the command being handled.
 *  -> attr2value -- attribute dictionary.
 * <-		  -- TRUE if we handled the command, FALSE otherwise
 */
static int _apiSetScrollbarMarginIssue (vcommandFunction *func,
					vdict *attr2value)
{
    apiRock *rock = _apiAttrToRock (attr2value);
    _apiOpenSetScrollbarMarginDialog (rock);

    _apiNoteTextLiteral (rock, "Opened scrollbar margin editing dialog.\n");

    return (TRUE);

} /* _apiSetScrollbarMarginIssue */




/* _apiSetRowCountIssue -- issue command to open up a dialog to set
 *			the row count
 *
 *  -> func	  -- the command being handled.
 *  -> attr2value -- attribute dictionary.
 * <-		  -- TRUE if we handled the command, FALSE otherwise
 */
static int _apiSetRowCountIssue (vcommandFunction *func,
				 vdict *attr2value)
{
    apiRock *rock = _apiAttrToRock (attr2value);
    _apiOpenSetRowCountDialog (rock);

    _apiNoteTextLiteral (rock, "Opened row count editing dialog.\n");

    return (TRUE);

} /* _apiSetRowCountIssue */




/* _apiSetColumnCountIssue -- issue command to open up a dialog to set
 *			the column count
 *
 *  -> func	  -- the command being handled.
 *  -> attr2value -- attribute dictionary.
 * <-		  -- TRUE if we handled the command, FALSE otherwise
 */
static int _apiSetColumnCountIssue (vcommandFunction *func,
				    vdict *attr2value)
{
    apiRock *rock = _apiAttrToRock (attr2value);

    _apiOpenSetColumnCountDialog (rock);

    _apiNoteTextLiteral (rock, "Opened column count editing dialog.\n");

    return (TRUE);

} /* _apiSetColumnCountIssue */




/* _apiGetRowCountIssue -- issue command to display the row count
 *
 *  -> func	  -- the command being handled.
 *  -> attr2value -- attribute dictionary.
 * <-		  -- TRUE if we handled the command, FALSE otherwise
 */
static int _apiGetRowCountIssue (vcommandFunction *func,
				 vdict *attr2value)
{
    apiRock *rock = _apiAttrToRock (attr2value);

    _apiNoteTextScribed (rock, vscribeScribeMulti
			 (vcharScribeLiteral ("vlistGetRowCount ("
					      "vlistviewGetList(view)) ==  "),
			  vnumScribeInt (vlistGetRowCount 
					 (vlistviewGetList(rock->listview))),
			  NULL));
    return (TRUE);

} /* _apiGetRowCountIssue */




/* _apiGetColumnCountIssue -- issue command to display the column count
 *
 *  -> func	  -- the command being handled.
 *  -> attr2value -- attribute dictionary.
 * <-		  -- TRUE if we handled the command, FALSE otherwise
 */
static int _apiGetColumnCountIssue (vcommandFunction *func,
				    vdict *attr2value)
{
    apiRock *rock = _apiAttrToRock (attr2value);

    _apiNoteTextScribed (rock, vscribeScribeMulti
			 (vcharScribeLiteral ("vlistGetColumnCount ("
					      "vlistviewGetList(view)) ==  "),
			  vnumScribeInt (vlistGetColumnCount 
					 (vlistviewGetList(rock->listview))),
			  NULL));

    return (TRUE);

} /* _apiGetColumnCountIssue */




/* _apiSetColumnWidthIssue -- issue command to open up a dialog to set
 *			the column width
 *
 *  -> func	  -- the command being handled.
 *  -> attr2value -- attribute dictionary.
 * <-		  -- TRUE if we handled the command, FALSE otherwise
 */
static int _apiSetColumnWidthIssue (vcommandFunction *func,
				    vdict *attr2value)
{
    apiRock *rock = _apiAttrToRock (attr2value);

    _apiOpenSetColumnWidthDialog (rock);

    _apiNoteTextLiteral (rock, "Opened column width editing dialog.\n");

    return (TRUE);

} /* _apiSetColumnWidthIssue */




/* _apiSetRowHeightIssue -- issue command to open up a dialog to set
 *			the row height
 *
 *  -> func	  -- the command being handled.
 *  -> attr2value -- attribute dictionary.
 * <-		  -- TRUE if we handled the command, FALSE otherwise
 */
static int _apiSetRowHeightIssue (vcommandFunction *func,
				    vdict *attr2value)
{
    apiRock *rock = _apiAttrToRock (attr2value);

    _apiOpenSetRowHeightDialog (rock);

    _apiNoteTextLiteral (rock, "Opened row height editing dialog.\n");

    return (TRUE);

} /* _apiSetRowHeightIssue */




/* _apiGetRowHeightIssue -- issue command to display the row height
 *
 *  -> func	  -- the command being handled.
 *  -> attr2value -- attribute dictionary.
 * <-		  -- TRUE if we handled the command, FALSE otherwise
 */
static int _apiGetRowHeightIssue (vcommandFunction *func, vdict *attr2value)
{
    apiRock *rock = _apiAttrToRock (attr2value);
    int row, column;

    /* If the user selects more than one cell, the results are undefined --
     * this call could pick any selected cell */

    vlistGetSelectedCell (vlistviewGetList (rock->listview), 
			  vlistviewGetSelection (rock->listview),
			  &row, &column);

    if (row == vlistNO_CELLS_SELECTED) {

	_apiNoteTextLiteral (rock, "Cannot get row height -- "
			     "no cell selected.\n");

    } else {
	int height = vlistviewGetRowHeight (rock->listview, row);

	_apiNoteTextScribed (rock, vscribeScribeMulti
			     (vcharScribeLiteral ("vlistviewGetRowHeight ("
						  "listview, "),
			      vnumScribeInt (row),
			      vcharScribeLiteral (", "),
			      vnumScribeInt (column),
			      vcharScribeLiteral (") == "),
			      vnumScribeInt (height),
			      NULL));
    } 

    return (TRUE);

} /* _apiGetRowHeightIssue */




/* _apiGetColumnWidthIssue -- issue command to display the column width
 *
 *  -> func	  -- the command being handled.
 *  -> attr2value -- attribute dictionary.
 * <-		  -- TRUE if we handled the command, FALSE otherwise
 */
static int _apiGetColumnWidthIssue (vcommandFunction *func, vdict *attr2value)
{
    apiRock *rock = _apiAttrToRock (attr2value);
    int row, column;

    /* if the user selects more than one cell, the results are undefined --
     * this call could pick any selected cell */

    vlistGetSelectedCell (vlistviewGetList (rock->listview), 
			  vlistviewGetSelection (rock->listview),
			  &row, &column);

    if (column == vlistNO_CELLS_SELECTED) {

	_apiNoteTextLiteral (rock, "Cannot get column width -- no cell "
			     "selected.\n");

    } else {
	int width = vlistviewGetColumnWidth (rock->listview, column);

	_apiNoteTextScribed (rock, vscribeScribeMulti
			     (vcharScribeLiteral ("vlistviewGetColumnWidth ("
						  "listview, "),
			      vnumScribeInt (row),
			      vcharScribeLiteral (", "),
			      vnumScribeInt (column),
			      vcharScribeLiteral (") == "),
			      vnumScribeInt (width),
			      NULL));
    }

    return (TRUE);

} /* _apiGetColumnWidthIssue */




/* _apiRemoveRowIssue -- issue command to delete selected rows.
 *
 *  -> func	  -- the command being handled.
 *  -> attr2value -- attribute dictionary.
 * <-		  -- TRUE if we handled the command, FALSE otherwise
 */
static int _apiRemoveRowIssue (vcommandFunction *func, vdict *attr2value)
{
    apiRock *rock = _apiAttrToRock (attr2value);
    vbyte	   *thingie;
    vlist	   *list = vlistviewGetList (rock->listview);
    vlistIterator   iterator;
    int		    row;

    /* this is the only good way to remove all of the rows in a selection.
     * If you iterate over the selection moving rows, you'll potentially
     * try to remove rows multiple times, or the removal of a row will
     * change the row numbers for other cells in the selection, leading to
     * utter chaos.
     *
     * What we do is iterate over the selection and accumulate the selected
     * rows in another data structure (in this case, an array of booleans.)
     * The we go over this data structure in *reverse* order.  If we don't
     * do that, row numbers will get out of sync.
     *
     * e.g. rows 1, 3, and 7 were selected and marked for removal.  When
     * you remove row 1, all subsequent rows get shifted down one index.
     * we then have to remove rows 2 and 6 to do what the user wanted, but
     * our array has 3 and 7 still marked for removal.
     */

    /* table of selected rows. */
    thingie = (vbyte*)vmemAllocAndClear (vlistGetRowCount(list) 
					 * sizeof(vbyte));

    vlistInitSelectionIterator (&iterator,
				vlistviewGetSelection (rock->listview));

    /* mark each row that has a selected cell in it */
    while (vlistNextIterator (&iterator)) {
	row = vlistGetIteratorRow (&iterator);
	thingie[row] = TRUE;
    }

    vlistDestroyIterator (&iterator);


    /* sign the death warrants. */
    for (row = (vlistGetRowCount(list) - 1); row >= 0; row--) {
	if (thingie[row]) {
	    vlistRemoveRow (list, row);
	}
    }

    vmemFree (thingie);

    _apiNoteTextLiteral (rock, "vlistRemoveRow (vlistviewGetList"
			 "(listview), row);");

    return (TRUE);

} /* _apiRemoveRowIssue */




/* _apiRemoveColumnIssue -- issue command to delete selected rows.
 *
 *
 *  -> func	  -- the command being handled.
 *  -> attr2value -- attribute dictionary.
 * <-		  -- TRUE if we handled the command, FALSE otherwise
 */
static int _apiRemoveColumnIssue (vcommandFunction *func, vdict *attr2value)
{
    apiRock *rock = _apiAttrToRock (attr2value);
    vbyte	   *thingie;
    vlist	   *list = vlistviewGetList (rock->listview);
    vlistIterator   iterator;
    int		    column;

    /* see comment in _apiRemoveRowIssue */

    /* table of selected columns. */
    thingie = (vbyte*)vmemAllocAndClear (vlistGetColumnCount(list) 
					 * sizeof(vbyte));

    vlistInitSelectionIterator (&iterator,
				vlistviewGetSelection (rock->listview));

    /* mark each row that has a selected cell in it */
    while (vlistNextIterator (&iterator)) {
	column = vlistGetIteratorColumn (&iterator);
	thingie[column] = TRUE;
    }

    vlistDestroyIterator (&iterator);


    /* kill hurt maim destroy */
    for (column = (vlistGetColumnCount(list) - 1); column >= 0; column--) {
	if (thingie[column]) {
	    vlistRemoveColumn (list, column);
	}
    }

    vmemFree (thingie);

    _apiNoteTextLiteral (rock, "vlistRemoveColumn "
			 "(vlistviewGetList(listview), column);");

    return (TRUE);

} /* _apiRemoveColumnIssue */




/* _apiInsertRowIssue -- issue command to insert after selected rows.
 *
 *
 *  -> func	  -- the command being handled.
 *  -> attr2value -- attribute dictionary.
 * <-		  -- TRUE if we handled the command, FALSE otherwise
 */
static int _apiInsertRowIssue (vcommandFunction *func, vdict *attr2value)
{
    apiRock *rock = _apiAttrToRock (attr2value);
    vbyte	   *thingie;
    vlist	   *list = vlistviewGetList (rock->listview);
    vlistIterator   iterator;
    int		    row;

    /* see comment in _apiRemoveRowIssue.  The same concepts apply here */

    /* table of selected rows */
    thingie = (vbyte*)vmemAllocAndClear (vlistGetRowCount(list) 
					 * sizeof(vbyte));

    vlistInitSelectionIterator (&iterator,
				vlistviewGetSelection (rock->listview));

    /* mark each row that has a selected cell in it */
    while (vlistNextIterator (&iterator)) {
	row = vlistGetIteratorRow (&iterator);
	thingie[row] = TRUE;
    }

    vlistDestroyIterator (&iterator);


    /* insert the new rows */
    for (row = (vlistGetRowCount(list) - 1); row >= 0; row--) {
	if (thingie[row]) {
	    vlistInsertRow (list, row);
	}
    }

    vmemFree (thingie);

    _apiNoteTextLiteral (rock, "vlistInsertRow (vlistviewGetList"
			 "(listview), row);");

    return (TRUE);

} /* _apiInsertRowIssue */




/* _apiInsertColumnIssue -- issue command to insert selected rows.
 *
 *
 *  -> func	  -- the command being handled.
 *  -> attr2value -- attribute dictionary.
 * <-		  -- TRUE if we handled the command, FALSE otherwise
 */
static int _apiInsertColumnIssue (vcommandFunction *func, vdict *attr2value)
{
    apiRock *rock = _apiAttrToRock (attr2value);
    vbyte	   *thingie;
    vlist	   *list = vlistviewGetList (rock->listview);
    vlistIterator   iterator;
    int		    column;

    /* see comment in _apiRemoveRowIssue.  The same concepts apply here */

    /* table of selected rows */
    thingie = (vbyte*)vmemAllocAndClear (vlistGetColumnCount(list) 
					 * sizeof(vbyte));

    vlistInitSelectionIterator (&iterator,
				vlistviewGetSelection (rock->listview));

    /* mark each row that has a selected cell in it */
    while (vlistNextIterator (&iterator)) {
	column = vlistGetIteratorColumn (&iterator);
	thingie[column] = TRUE;
    }

    vlistDestroyIterator (&iterator);


    /* insert the new columns */
    for (column = (vlistGetColumnCount(list) - 1); column >= 0; column--) {
	if (thingie[column]) {
	    vlistInsertColumn (list, column);
	}
    }

    vmemFree (thingie);

    _apiNoteTextLiteral (rock,"vlistInsertColumn (vlistviewGetList(listview), "
			 "column);");

    return (TRUE);

} /* _apiInsertColumnIssue */




/* _apiSwapRowsIssue -- issue command to swap rows
 *
 *
 *  -> func	  -- the command being handled.
 *  -> attr2value -- attribute dictionary.
 * <-		  -- TRUE if we handled the command, FALSE otherwise
 */
static int _apiSwapRowsIssue (vcommandFunction *func, vdict *attr2value)
{
    apiRock *rock = _apiAttrToRock (attr2value);
    int 	   *thingie; /* list of selected rows */
    int		   *thingieScan;
    vlist	   *list = vlistviewGetList (rock->listview);
    vlistIterator   iterator;
    int		    row;
    int		    count = 0;
    int		    i;

    thingie = (int*)vmemAllocAndClear (vlistGetRowCount(list) 
					 * sizeof(int));

    vlistInitSelectionIterator (&iterator,
				vlistviewGetSelection (rock->listview));

    /* mark the thingie array with TRUE for each row that has some
     * part of the selection in it */
    while (vlistNextIterator (&iterator)) {
	row = vlistGetIteratorRow (&iterator);
	thingie[row] = TRUE;
    }

    vlistDestroyIterator (&iterator);

    /* gather the numbers of the rows with the selection in them to
     * the beginning of the array. */
    for (count = 0, i = 0; i < vlistGetRowCount (list); i++) {
	if (thingie[i]) {
	    thingie[count] = i;
	    count++;
	}
    }

    thingieScan = thingie;

    if (count > 1) {   /* can't swap 1 row */
	for (count--, thingieScan = thingie; count; count--, thingieScan++) {
	    vlistSwapRows (list, *thingieScan, *(thingieScan + 1));
	}
    }

    vmemFree (thingie);

    _apiNoteTextLiteral (rock, "vlistSwapRows (vlistviewGetList(listview), "
			 "row1, row2);");

    return (TRUE);

} /* _apiSwapRowsIssue */




/* _apiSwapColumnsIssue -- issue command to swap columns
 *
 *
 *  -> func	  -- the command being handled.
 *  -> attr2value -- attribute dictionary.
 * <-		  -- TRUE if we handled the command, FALSE otherwise
 */
static int _apiSwapColumnsIssue (vcommandFunction *func, vdict *attr2value)
{
    apiRock *rock = _apiAttrToRock (attr2value);
    int 	   *thingie; /* list of selected columns */
    int		   *thingieScan;
    vlist	   *list = vlistviewGetList (rock->listview);
    vlistIterator   iterator;
    int		    column;
    int		    count = 0;
    int		    i;

    thingie = (int*)vmemAllocAndClear (vlistGetColumnCount(list) 
					 * sizeof(int));

    vlistInitSelectionIterator (&iterator,
				vlistviewGetSelection (rock->listview));

    /* mark the thingie array with TRUE for each column that has some
     * part of the selection in it */
    while (vlistNextIterator (&iterator)) {
	column = vlistGetIteratorColumn (&iterator);
	thingie[column] = TRUE;
    }

    vlistDestroyIterator (&iterator);

    /* gather the numbers of the columns with the selection in them to
     * the beginning of the array. */
    for (count = 0, i = 0; i < vlistGetColumnCount (list); i++) {
	if (thingie[i]) {
	    thingie[count] = i;
	    count++;
	}
    }

    thingieScan = thingie;

    if (count > 1) {   /* can't swap 1 column */
	for (count--, thingieScan = thingie; count; count--, thingieScan++) {
	    vlistSwapColumns (list, *thingieScan, *(thingieScan + 1));
	}
    }

    vmemFree (thingie);

    _apiNoteTextLiteral (rock, "vlistSwapColumns (vlistviewGetList(listview), "
			 "column1, row2);");

    return (TRUE);

} /* _apiSwapColumnsIssue */




/* _apiCalcImageNameWidth -- returns the width of the widest string (plus
 *			     padding) that names an image given a listview
 *			     that has a font.
 *
 *  -> listview -- the listview
 * <-           -- the width of the widest string in the listview's font, 
 *		   plus an aesthteic pad.
 */
static int _apiCalcImageNameWidth (vlistview *listview)
{
    vdictIterator iterator;
    vfont *font;
    int max = 0;
    int val;

    font = vdialogDetermineItemFont (vlistviewGetItem(listview));

    /* loop over the image->name map dict and find the maxWidth of the names */
    vdictInitIterator (&iterator, imageDict);
    
    while (vdictNextIterator(&iterator)) {
	val = vfontStringWidthX (font, vdictGetIteratorValue(&iterator));
	max = vMAX (val, max);
    }
    vdictDestroyIterator (&iterator);

    max += 2 * vclassGet (vlistviewGetClass(listview),
			  vlistviewCELL_CONTENT_INDENT);
    return (max);

} /* _apiCalcImageNameWidth */




/* _apiDrawBothIssue -- Set cell drawing to be text and images.
 *
 *  -> func	  -- the command being handled.
 *  -> attr2value -- attribute dictionary.
 * <-		  -- TRUE if we handled it, FALSE otherwise
 */
static int _apiDrawBothIssue (vcommandFunction *func, vdict *attr2value)
{
    apiRock *rock = _apiAttrToRock (attr2value);

    /* make sure we have an image list to draw */
    if (rock->imageList == NULL) {
	_apiNoteTextLiteral (rock, "Loading image resources... "
			     "Hang on please...");
	_apiSetupImageList (rock);
    }

    vlistviewSetList (rock->listview, rock->imageList);
    vlistviewSetRowHeight (rock->listview, vlistviewALL_ROWS, 46);
    vlistviewSetColumnWidth (rock->listview, vlistviewALL_COLUMNS,
			     _apiCalcImageNameWidth(rock->listview) + 46);
    vlistviewSetCellContentProc (rock->listview, _apiBothContentProc);

    _apiNoteTextLiteral (rock, "_apiDrawBothIssue");

    /* close the setCellValue dialog -- there's not a UI for setting
     * image values yet.
     */
    if (   (_apiSetCellValueDialog != NULL)
	&& (vdialogIsOpen (_apiSetCellValueDialog))) {
	vdialogClose (_apiSetCellValueDialog);
    }

    return (TRUE);

} /* _apiDrawBothIssue */




/* _apiDrawAsTextIssue -- Set cell drawing to text
 *
 *  -> func	  -- the command being handled.
 *  -> attr2value -- attribute dictionary.
 * <-		  -- TRUE if we handled it, FALSE otherwise
 */
static int _apiDrawAsTextIssue (vcommandFunction *func, vdict *attr2value)
{
    apiRock *rock = _apiAttrToRock (attr2value);

    vlistviewSetList (rock->listview, vliststrGetList(rock->stringList));
    vlistviewSetCellContentProc (rock->listview, _apiStringContentProc);

    _apiNoteTextLiteral (rock, "_apiDrawAsTextIssue");

    return (TRUE);

} /* _apiDrawAsTextIssue */




/* _apiDrawImageIssue -- Set cell drawing to Images
 *
 *  -> func	  -- the command being handled.
 *  -> attr2value -- attribute dictionary.
 * <-		  -- TRUE if we handled it, FALSE otherwise
 */
static int _apiDrawImageIssue (vcommandFunction *func, vdict *attr2value)
{
    apiRock *rock = _apiAttrToRock (attr2value);

    /* make sure we have an image list to draw */
    if (rock->imageList == NULL) {
	_apiNoteTextLiteral (rock, "Loading image resources... "
			     "Hang on please...");
	_apiSetupImageList (rock);
    }
    vlistviewSetList (rock->listview, rock->imageList);
    vlistviewSetRowHeight (rock->listview, vlistviewALL_ROWS, 46);
    vlistviewSetColumnWidth (rock->listview, vlistviewALL_COLUMNS, 46);
    vlistviewSetCellContentProc (rock->listview, _apiImageContentProc);

    _apiNoteTextLiteral (rock, "_apiDrawImageIssue");

    /* close the setCellValue dialog -- there's not a UI for setting
     * image values yet.
     */
    if (   (_apiSetCellValueDialog != NULL)
	&& (vdialogIsOpen (_apiSetCellValueDialog))) {
	vdialogClose (_apiSetCellValueDialog);
    }

    return (TRUE);

} /* _apiDrawImageIssue */




/* _apiHorzGridIssue -- Turn on horizontal grid lines
 *
 *  -> func	  -- the command being handled.
 *  -> attr2value -- attribute dictionary.
 * <-		  -- TRUE if we handled it, FALSE otherwise
 */
static int _apiHorzGridIssue (vcommandFunction *func, vdict *attr2value)
{
    apiRock *rock = _apiAttrToRock (attr2value);
    
    if (vlistviewHasHorzGrid (rock->listview)) {
	vlistviewSetHorzGrid (rock->listview, FALSE);
	_apiNoteTextLiteral (rock, "vlistviewSetHorzGrid (listview, FALSE);");
    } else {
	vlistviewSetHorzGrid (rock->listview, TRUE);
	_apiNoteTextLiteral (rock, "vlistviewSetHorzGrid (listview, TRUE);");
    }
	
    return (TRUE);

} /* _apiHorzGridIssue */




/* _apiVertGridIssue -- Turn on vertical grid lines
 *
 *  -> func	  -- the command being handled.
 *  -> attr2value -- attribute dictionary.
 * <-		  -- TRUE if we handled it, FALSE otherwise
 */
static int _apiVertGridIssue (vcommandFunction *func, vdict *attr2value)
{
    apiRock *rock = _apiAttrToRock (attr2value);

    if (vlistviewHasVertGrid (rock->listview)) {
	vlistviewSetVertGrid (rock->listview, FALSE);
	_apiNoteTextLiteral (rock, "vlistviewSetVertGrid (listview, FALSE);");

    } else {
	vlistviewSetVertGrid (rock->listview, TRUE);
	_apiNoteTextLiteral (rock, "vlistviewSetVertGrid (listview, TRUE);");
    }

    return (TRUE);

} /* _apiVertGridIssue */




/* --------------- Selector Based command implementations ----------------- */


/* _apiSelectionCommandIssue -- handle the command generated.  The command
 *			has a selector value associated with it that 
 *			determines what functionality to execute.
 *
 *  -> command	     -- the command being handled
 *  -> attr2value    -- the context this command is being handled in.
 * <-  		     -- TRUE if we handled the command, FALSE otherwise
 */
static int _apiSelectionCommandIssue (vcommandSelector *command,
				      vdict            *attr2value)
{
    apiRock *rock = _apiAttrToRock (attr2value);
    int	  	    selector = vcommandGetSelector (command);

    vlist          *list = vlistviewGetList (rock->listview);
    vlistSelection *selection = vlistviewGetSelection (rock->listview);

    switch (selector) {
	case apiSELECT_FREE_SELECTION: {
	    vlistSetSelectMethod (list, selection, vlistFREE_SELECTION);

	    _apiNoteTextLiteral (rock, "vlistSetSelectMethod (vlistviewGetList"
				 "(view), vlistviewGetSelection(view), "
				 "vlistFREE_SELECTION);");
	    break;
	}
	case apiSELECT_RECTANGULAR_SELECTION: {
	    vlistSetSelectMethod (list, selection, vlistRECTANGULAR_SELECTION);

	    _apiNoteTextLiteral (rock, "vlistSetSelectMethod (vlistviewGetList"
				 "(view), vlistviewGetSelection(view), "
				 "vlistRECTANGULAR_SELECTION);");
	    break;
	}
	case apiSELECT_ONE_ONLY_SELECTION: {
	    vlistSetSelectMethod (list, selection, vlistONE_ONLY_SELECTION);

	    _apiNoteTextLiteral (rock, "vlistSetSelectMethod (vlistviewGetList"
				 "(view), vlistviewGetSelection(view), "
				 "vlistONE_ONLY_SELECTION);");
	    break;
	}
	case apiSELECT_NO_SELECTION: {
	    vlistSetSelectMethod (list, selection, vlistNO_SELECTION);

	    _apiNoteTextLiteral (rock, "vlistSetSelectMethod (vlistviewGetList"
				 "(view), vlistviewGetSelection(view), "
				 "vlistNO_SELECTION);");
	    break;
	}
	default: {
	    vdebugWarn ("bad selection selector selection.\n");
	    break;
	}
    }

    return (TRUE);

} /* _apiSelectionCommandIssue */




/* _apiSelectionCommandIssue -- handle the command generated.  The command
 *			has a selector value associated with it that 
 *			determines what functionality to execute.
 *
 *  -> command	     -- the command being handled
 *  -> attr2value    -- the context this command is being handled in.
 * <-  		     -- TRUE if we handled the command, FALSE otherwise
 */
static int _apiFilterCommandIssue (vcommandSelector *command,
				   vdict	    *attr2value)
{
    apiRock *rock = _apiAttrToRock (attr2value);
    int		selector = vcommandGetSelector (command);

    switch (selector) {
	case apiSELECT_EVEN_ODD_SELECTION_FILTER: {
	    vlistviewSetSelectionFilter (rock->listview,
					 _apiEvenOddSelectionFilter);

	    _apiNoteTextLiteral (rock, "vlistviewSetSelectionFilter "
				 "(listview, myEvenOddFilter);");
	    break;
	}
	case apiSELECT_PRIME_SELECTION_FILTER: {
	    vlistviewSetSelectionFilter (rock->listview,
					 _apiPrimeSelectionFilter);

	    _apiNoteTextLiteral (rock, "vlistviewSetSelectionFilter "
				 "(listview, myPrimeFilter);");
	    break;
	}
	case apiSELECT_NO_SELECTION_FILTER: {
	    vlistviewSetSelectionFilter (rock->listview,
					 (vlistviewSelectionFilterProc)NULL);

	    _apiNoteTextLiteral (rock, "vlistviewSetSelectionFilter "
				 "(listview, "
				 "(vlistviewSelectionFilterProc)NULL);");
	    break;
	}
	default: {
	    vdebugWarn ("bad bad naughty evil zoot!\n");
	    break;
	}
    }

    return (TRUE);

} /* _apiSelectionCommandIssue */




/* ----------------- Command Mappings ------------------- */

static vcommandFunctionTemplate apiCommandDefs[] = {
    { "Close Window",            _apiCloseIssue,              NULL },
    { "Close",                   _apiCloseIssue,              NULL },
    { "At Least One Selection",  _apiAtLeastOneIssue,         NULL },
    { "Immutable Selection",     _apiImmutableIssue,          NULL },
    { "No Selection Extension",	 _apiNoExtendSelectionIssue,  NULL },
    { "Extend Row Selection",    _apiExtendRowIssue,          NULL },
    { "Extend Column Selection", _apiExtendColumnIssue,       NULL },
    { "Select All",              _apiSelectAllIssue,          NULL },
    { "Unselect All",            _apiUnselectAllIssue,        NULL },
    { "Select Randomly",         _apiSelectRandomIssue,       NULL },
    { "Unselect Randomly",       _apiUnselectRandomIssue,     NULL },
    { "Count Selected Cells",    _apiCountSelectedCellsIssue, NULL },
    { "Iterate Selected Cells",  _apiIterateCellsIssue,       NULL },
    { "Set Row Height...",       _apiSetRowHeightIssue,       NULL },
    { "Set Column Width...",     _apiSetColumnWidthIssue,     NULL },
    { "Get Row Height",          _apiGetRowHeightIssue,       NULL },
    { "Get Column Width",        _apiGetColumnWidthIssue,     NULL },
    { "Random Row Heights",      _apiRandomRowHeightIssue,    NULL },
    { "Random Column Widths",    _apiRandomColumnWidthIssue,  NULL },
    { "Short Rows",              _apiShortRowsIssue,          NULL },
    { "Narrow Columns",          _apiNarrowColumnsIssue,      NULL },
    { "Tall Rows",               _apiTallRowsIssue,           NULL },
    { "Wide Columns",            _apiWideColumnsIssue,        NULL },
    { "Set Font...",             _apiSetFontIssue,            NULL },
    { "Set Foreground Color...", _apiSetForegroundIssue,      NULL },
    { "Set Background Color...", _apiSetBackgroundIssue,      NULL },
    { "Set Scrollbar Margin...", _apiSetScrollbarMarginIssue, NULL },
    { "Row Rearrange",           _apiRowRearrangeIssue,       NULL },
    { "Column Rearrange",        _apiColumnRearrangeIssue,    NULL },
    { "No Rearrange",            _apiNoRearrangeIssue,        NULL },
    { "Grabbing Hand",           _apiGrabbingHandIssue,       NULL },
    { "Drawing Selection",       _apiDrawingSelectionIssue,   NULL },
    { "Scroll To Selection",     _apiScroll2SelectionIssue,   NULL },
    { "Scroll To Focus",         _apiScroll2FocusIssue,       NULL },
    { "Scroll Left",             _apiScrollLeftIssue,         NULL },
    { "Scroll Right",            _apiScrollRightIssue,        NULL },
    { "Scroll Up",               _apiScrollUpIssue,           NULL },
    { "Scroll Down",             _apiScrollDownIssue,         NULL },
    { "Scroll All Around",       _apiScrollAroundIssue,       NULL },
    { "Scroll Home",             _apiScrollHomeIssue,         NULL },
    { "Scroll End",              _apiScrollEndIssue,          NULL },
    { "Disabled",                _apiDisableIssue,            NULL },
    { "Remove Row",              _apiRemoveRowIssue,          NULL },
    { "Remove Column",           _apiRemoveColumnIssue,       NULL },
    { "Insert Row",              _apiInsertRowIssue,          NULL },
    { "Insert Column",           _apiInsertColumnIssue,       NULL },
    { "Swap Rows",               _apiSwapRowsIssue,           NULL },
    { "Swap Columns",            _apiSwapColumnsIssue, 	      NULL },
    { "Set Row Count...",        _apiSetRowCountIssue,        NULL },
    { "Set Column Count...",     _apiSetColumnCountIssue,     NULL },
    { "Get Row Count",           _apiGetRowCountIssue,        NULL },
    { "Get Column Count",        _apiGetColumnCountIssue,     NULL },
    { "Set Cell Value...",	 _apiSetCellValueIssue,       NULL },
    { "Border",                  _apiBorderIssue,             NULL },
    { "Autoscroll",              _apiAutoscrollIssue,         NULL },
    { "Keyboard Traversal Wrap", _apiTraversalWrapIssue,      NULL },
    { "Keyboard Selection",      _apiKeyboardSelectionIssue,  NULL },
    { "Keyboard Traversal",      _apiKeyboardTraversalIssue,  NULL },
    { "Selection Sense",         _apiSelectionSenseIssue,     NULL },
    { "Horizontal Scrollbar",    _apiHorzBarIssue,            NULL },
    { "Vertical Scrollbar",      _apiVertBarIssue,            NULL },
    { "Draw Strings",	         _apiDrawAsTextIssue,	      NULL },
    { "Draw Images",	    	 _apiDrawImageIssue,	      NULL },
    { "Draw Both",	    	 _apiDrawBothIssue,	      NULL },
    { "Horizontal Grid Lines",	 _apiHorzGridIssue,	      NULL },
    { "Vertical Grid Lines",	 _apiVertGridIssue,	      NULL },
    { NULL,                      NULL,                        NULL }
};



typedef struct selectorSelectDef {
    const char		*tagName;
    int			 selector;
} selectorSelectDef;


/* the enums for these guys are located at the beginning of this file */

static selectorSelectDef apiSelectionDefs[] = {
    { "No Selection",            apiSELECT_NO_SELECTION          },
    { "Rectangular Selection",   apiSELECT_RECTANGULAR_SELECTION },
    { "One-Only Selection",      apiSELECT_ONE_ONLY_SELECTION    },
    { "Free Selection",          apiSELECT_FREE_SELECTION        },
    { NULL,			 0                               }
};


static selectorSelectDef apiFilterDefs[] = {
    { "Even/Odd Selection Filter",        apiSELECT_EVEN_ODD_SELECTION_FILTER},
    { "Prime Row/Column Selection Filter",apiSELECT_PRIME_SELECTION_FILTER   },
    { "No Selection Filter",              apiSELECT_NO_SELECTION_FILTER      },
    { NULL,			          0                             }
};




/* ----------------- Misc Support stuff ----------------- */


/* _apiSetupCommands -- attachs commands for the various menu items
 *			in the api diddler.  It does so by creating a
 *			command space and attaching it to the dialog's
 * 			window.
 *  -> dialog -- the dialog to attach the command space to
 */
void _apiSetupCommands (vdialog *dialog)
{
    vcommandFunction	*functionCommand;
    vcommandSelector	*commandSelector;
    selectorSelectDef	*selectorScan;
    vdict		*commandDict;
    vcommandSpace	*commandSpace;
    vcommandFunctionTemplate *selectScan;

    /* create a dictionary that will store all of our commands */
    commandDict = vdictCreate (vnameHash);
    
    /* create a brand new command space that will hold our dictionary */
    commandSpace = vcommandCreateSpace ();
    


    /* cycle through our apiCommandDefs[] and create the command
     * bindings.   To add more commands, add to the apiCommandDefs array
     * up above. */

    for (selectScan = apiCommandDefs; 
	 selectScan->name != NULL;  selectScan++) {

	/* create a new command... */
	functionCommand =  vcommandCreateFunctionOfClass 
	(vcommandGetDefaultFunctionClass());

	/* ... set its issuing function if it has one ... */
	if (selectScan->issueFunc) {
	    vcommandSetFunctionIssue (functionCommand, selectScan->issueFunc);
	}

	/* ... and set its query function if it has one ... */
	if (selectScan->queryFunc) {
	    vcommandSetFunctionQuery (functionCommand, selectScan->queryFunc);
	}

	/* ... and store that pupper into our command dictionary. */
	vdictStore (commandDict, TAG(selectScan->name),
		    functionCommand);
    }



    /* now create a command subclass for a selector-based set of commands.
     * this particular group handles a menu radio group for selection types */
    
    _apiSelectTypeCommandClass = vclassReproduce (vobjectGetCommandClass());

    vclassSet (_apiSelectTypeCommandClass,
	       vcommandISSUE,
	       _apiSelectionCommandIssue);

    /* now cycle through our apiSelectionDefs */

    for (selectorScan = apiSelectionDefs;
	 selectorScan->tagName != NULL; selectorScan++) {
	
	/* create a new selector command ... */
	commandSelector = vcommandCreateSelectorOfClass 
	(_apiSelectTypeCommandClass);

	/* ... set its selector integer ... */
	vcommandSetSelector (commandSelector, selectorScan->selector);

	/* ... stash it in our dictionary */
	vdictStore (commandDict, TAG(selectorScan->tagName),
		    commandSelector);
    }



    /* now create another command subclass for a selector-based set of
     * commands. this particular group handles a menu radio group for 
     * selection filters */
    
    _apiFilterTypeCommandClass = vclassReproduce (vobjectGetCommandClass());

    vclassSet (_apiFilterTypeCommandClass,
	       vcommandISSUE,
	       _apiFilterCommandIssue);

    /* now cycle through our apiSelectionDefs */

    for (selectorScan = apiFilterDefs;
	 selectorScan->tagName != NULL; selectorScan++) {
	
	/* create a new selector command ... */
	commandSelector = vcommandCreateSelectorOfClass 
	(_apiFilterTypeCommandClass);

	/* ... set its selector integer ... */
	vcommandSetSelector (commandSelector, selectorScan->selector);

	/* ... stash it in our dictionary */
	vdictStore (commandDict, TAG(selectorScan->tagName),
		    commandSelector);
    }


    /* now attach our command dictionary to the command space. */
    vcommandAddSpaceDictOwned (commandSpace, vname_Command,
			       commandDict);


    /* and finally, attach this space to the dialog's window. */
    vwindowSetSpaceOwned (vdialogGetWindow(dialog), commandSpace);

} /* _apiSetupCommands */





/* _apiShutdown -- shutdown listapi.c, clean up our mess, put away
 *			our toys and go home.
 */
static void _apiShutdown (void)
{
    windowsetIterator    iterator;
    vdialog 		*dialog;

    if (_apiFontOfWisdom != NULL) {
	vfontchsrDestroy (_apiFontOfWisdom);
    }
    
    if (_apiBackgroundColorChooser != NULL) {
	vcolorchsrDestroy (_apiBackgroundColorChooser);
    }
    
    if (_apiForegroundColorChooser != NULL) {
	vcolorchsrDestroy (_apiForegroundColorChooser);
    }

    if (imageDict != NULL) {
	vdictIterator iterator;
	vdictInitIterator (&iterator, imageDict);
	while (vdictNextIterator (&iterator)) {
	    vimageDestroy ((vimage*)vdictGetIteratorKey(&iterator));
	}
	vdictDestroy (imageDict);
    }

    if (imageArray != NULL) {
	vmemFree (imageArray);
    }

    windowsetInitIterator (&iterator, apiWindowset);
    while (windowsetNextIterator (&iterator)) {
	dialog = windowsetGetIteratorDialog (&iterator);
	if (dialog) {
	    _apiCleanupDialog (dialog);
	    vdialogDestroy (dialog);
	}
    }
    windowsetDestroyIterator (&iterator);

    windowsetDestroyUnbalanced (apiWindowset);

    if (_apiSetCellValueDialog != NULL) {
	vdialogDestroy (_apiSetCellValueDialog);
    }

    if (_apiSetRowHeightDialog != NULL) {
	vdialogDestroy (_apiSetRowHeightDialog);
    }
    
    if (_apiSetColumnWidthDialog != NULL) {
	vdialogDestroy (_apiSetColumnWidthDialog);
    }
    
    if (_apiSetColumnCountDialog != NULL) {
	vdialogDestroy (_apiSetColumnCountDialog);
    }
    
    if (_apiSetRowCountDialog != NULL) {
	vdialogDestroy (_apiSetRowCountDialog);
    }
    
    if (_apiSetScrollbarMarginDialog != NULL) {
	vdialogDestroy (_apiSetScrollbarMarginDialog);
    }

    vpoolDestroy (apiRockPool);

} /* _apiShutdown */




/* _apiRegisterAPIListviewClass -- create and register a subclass of
 *			vlistview used in our API dialog.
 */
static void _apiRegisterAPIListviewClass (void)
{
    if (_apilistviewClass == NULL) {

	_apilistviewClass = vclassReproduce (vlistviewGetDefaultClass());

	vclassSetNameScribed (_apilistviewClass, 
			      vcharScribeLiteral("api listview"));

	/* these are to peek at some of the inner listmanager workings.
	 * You don't need to override these for ordinary everyday work
	 */
	vclassSet (_apilistviewClass,
		   vlistviewNOTIFY_SCROLL,
		   _apiListviewScrollNotify);

	vclassSet (_apilistviewClass,
		   vlistviewTRAVERSE_VECTOR,
		   _apiListviewTraverseVector);


    }
} /* _apiRegisterAPIListviewClass */



/* _apiSetupListview -- stuff stuff into the listview.
 * 
 *  -> listview	 -- the listview to stuff.
 */
static void _apiSetupListview (vlistview *listview)
{
    int		i, j;
    apiRock *rock = (apiRock*)vlistviewGetData(listview);

    vlistviewSetColumnWidth (listview, vlistviewALL_COLUMNS,
			     apiDEFAULT_COLUMN_WIDTH);

    rock->stringList = vliststrCreate ();

    for (i = 0; i < 50; i++) {
	for (j = 0; j < 50; j++) {
	    
	    vliststrSetCellValueScribed (rock->stringList, i, j,
					 vcharScribeFormatLiteral
					 ("(%d, %d)", i, j));

	}
    }

    vlistviewSetList (listview, vliststrGetList (rock->stringList));

    vlistviewSetSelectNotify (listview, _apiListviewSelectionNotify);
    vlistviewSetCellContentProc (listview, _apiStringContentProc);

    vlistviewSetHorzBar (listview, TRUE);
    vlistviewSetVertBar (listview, TRUE);

} /* _apiSetupListview */




/* listdemoNewAPI -- creates a new window which lets you play with most
 *		     list manager features
 *
 *  -> resource -- a resource dictionary containing our resources
 */
void listdemoNewAPI (vresource resource)
{
    vresource	dialogRes;
    vdialog *dialog;
    apiRock *rock;

    /* create our apilistview subclass */
    if (_apilistviewClass == NULL) {
	/* create and register our lifelistview subclass */
	_apiRegisterAPIListviewClass ();

	apiRockPool = vpoolCreate (sizeof(apiRock));

	/* create our windowset so we can clean up our mess afterwards */
	apiWindowset = windowsetCreate ();

	/* get called at the end of time */
	vclientRegisterShutdown (_apiShutdown);
    }
    
    rock = vpoolAlloc (apiRockPool);

    /* snarf the resource for the dialog */
    dialogRes = vresourceGet (resource, TAG("Dialog"));
    
    /* create an instance from the resource */
    dialog = vdialogLoad (dialogRes);
    vdialogSetData (dialog, rock);
    windowsetAddDialog (apiWindowset, dialog);
    
    /* attach command space */
    _apiSetupCommands (dialog);

    /* turnerize the menubar */
    listdemoColorizeMenubar (dialog, NULL);
    
    /* snarf our listview and set it up */
    rock->listview = (vlistview*)vdialogFindItem (dialog, 
							     TAG("listview"));
    vlistviewSetData (rock->listview, rock);
    rock->apiResources = resource;
    rock->imageList = NULL;
    rock->infoLabel = vdialogFindItem (dialog, TAG("Message Text"));
    vlistviewSetData (rock->listview, rock);
    
    _apiSetupListview (rock->listview);
    
    /* clear out our text field */
    _apiNoteTextLiteral (rock, "Welcome to the List Manager.");

    /* show that pupper */
    vdialogOpen (dialog);
	
} /* listdemoNewAPI */




/* ------------------ Support Dialog stuff ------------------ */



/* ------------------ Set Cell Value Dialog stuff ------------------ */


static vtextitem  *_apiSetCellValueTextItem = NULL;


/* _apiApplySetCellValue -- sets the cell value of all selected cells to
 * 			what was typed into the text box.
 *
 *  -> button   -- the pushbutton that handled the event
 *  -> event	-- the event that triggered this.
 */
static void _apiApplySetCellValue (vbutton *button, vevent *event)
{
    apiRock	*rock = (apiRock*)vdialogGetData (vdialogDetermineItemDialog
						  (vbuttonGetItem(button)));
    vlistIterator	iterator;

    /* cycle over the selection and change it's cell value */
    
    vlistInitSelectionIterator (&iterator,
				vlistviewGetSelection(rock->listview));

    while (vlistNextIterator(&iterator)) {
	int	row, column;

	row = vlistGetIteratorRow (&iterator);
	column = vlistGetIteratorColumn (&iterator);

	vliststrSetCellValueScribed ((vliststr*)(vlistviewGetList
						 (rock->listview)),
				     row, column,
				     vtextitemGetTextScribed
				     (_apiSetCellValueTextItem));

    }

    vlistDestroyIterator (&iterator);

    _apiNoteTextScribed (rock, vscribeScribeMulti
			 (vcharScribeLiteral ("vlistSetCellValue ("
					      "vlistviewGetList(view), "
					      "row, column, "),
			  vtextitemGetTextScribed(_apiSetCellValueTextItem),
			  vcharScribeLiteral (");"),
			  NULL));
} /* _apiApplySetCellValue */




/* _apiCancelSetCellValue -- Close the SetCellValue dialog
 *
 *  -> button   -- the pushbutton that handled the event
 *  -> event	-- the event that triggered this.
 */
static void _apiCancelSetCellValue (vbutton *button, vevent *event)
{
    _apiCloseSetCellValueDialog ();
} /* _apiCancelSetCellValue */




/* _apiOpenSetCellValueDialog -- opens a dialog where the users can set
 *			the value of selected cells.
 */
static void _apiOpenSetCellValueDialog (apiRock *rock)
{
    if (_apiSetCellValueDialog == NULL) {
	vresource	dialogRes = vresourceNULL;
	vbutton	       *apply = NULL, *cancel = NULL;

	dialogRes = vresourceGet (rock->apiResources, TAG("Set Cell Value"));

	_apiSetCellValueDialog = vdialogLoad (dialogRes);

	apply = (vbutton*)vdialogFindItem (_apiSetCellValueDialog,
					   TAG("apiSCV_APPLY_BUTTON"));
	cancel = (vbutton*)vdialogFindItem (_apiSetCellValueDialog,
					    TAG("apiSCV_CANCEL_BUTTON"));

	vbuttonSetNotify (apply, _apiApplySetCellValue);
	vbuttonSetNotify (cancel, _apiCancelSetCellValue);

	_apiSetCellValueTextItem = ((vtextitem*)vdialogFindItem 
				    (_apiSetCellValueDialog,
				     TAG("apiSCV_EDIT_TEXT")));
	
    }
    vdialogSetData (_apiSetCellValueDialog, rock);
    vdialogOpen (_apiSetCellValueDialog);
    vwindowRaise (vdialogGetWindow(_apiSetCellValueDialog));

} /* _apiOpenSetCellValueDialog */




/* _apiCloseSetCellValueDialog -- closes the dialog where the users can set
 *			the value of selected cells.
 */
static void _apiCloseSetCellValueDialog (void)
{
    if (_apiSetCellValueDialog) {
	vdialogClose (_apiSetCellValueDialog);
	vdialogSetData (_apiSetCellValueDialog, NULL);
    }
} /* _apiOpenSetCellValueDialog */




/* ------------------ Set Scrollbar Margin Dialog stuff ------------------ */


/* _apiApplySetScrollbarMargin -- sets the scrollbar margin of the listview
 *			to the value in the slider.
 *
 *
 *  -> button   -- the pushbutton that handled the event
 *  -> event	-- the event that triggered this.
 */
static void _apiApplySetScrollbarMargin (vbutton *button, vevent *event)
{
    apiRock	*rock = (apiRock*)vdialogGetData (vdialogDetermineItemDialog
						  (vbuttonGetItem(button)));
    vcontrol	*slider = (vcontrol*)vbuttonGetData (button);
    
    vlistviewSetScrollBarMargin (rock->listview, vcontrolGetValue (slider));

    _apiNoteTextScribed (rock, vscribeScribeMulti 
			 (vcharScribeLiteral ("vlistviewSetScrollBarMargin ("
					      "listview, vlistviewALL_ROWS, "),
			  vnumScribeInt(vcontrolGetValue (slider)),
			  vcharScribeLiteral (");"),
			  NULL));

} /* _apiApplySetScrollbarMargin */




/* _apiCancelSetScrollbarMargin -- Close the SetScrollbarMargin dialog
 *
 *  -> button   -- the pushbutton that handled the event
 *  -> event	-- the event that triggered this.
 */
static void _apiCancelSetScrollbarMargin (vbutton *button, vevent *event)
{
    _apiCloseSetScrollbarMarginDialog ();
} /* _apiCancelSetScrollbarMargin */




/* _apiSetScrollbarMarginSliderNotify -- sets a text item to the value
 * 		of the slider during tracking.
 *
 *  -> slider  -- the slider being fiddled with -- the text item is stored
 *		  in the slider's data.
 *  -> event   -- the event that started this hellish ride.
 */
static void _apiSetScrollbarMarginSliderNotify (vcontrol *slider,
						vevent *event)
{
    vtextitemSetTextScribed ((vtextitem*)vcontrolGetData(slider),
			     vnumScribeInt(vcontrolGetValue(slider)));
} /* _apiSetScrollbarMarginSliderNotify */




/* _apiOpenSetScrollbarMarginDialog -- opens a dialog where the users can set
 *			the value of selected cells.
 */
static void _apiOpenSetScrollbarMarginDialog (apiRock *rock)
{
    if (_apiSetScrollbarMarginDialog == NULL) {
	vresource	dialogRes = vresourceNULL;
	vbutton	       *apply = NULL, *cancel = NULL;
	vcontrol       *slider = NULL;
	vtextitem      *sliderValue = NULL;

	dialogRes = vresourceGet(rock->apiResources,
				 TAG("Set Scrollbar Margin"));

	_apiSetScrollbarMarginDialog = vdialogLoad (dialogRes);

	apply = (vbutton*)vdialogFindItem (_apiSetScrollbarMarginDialog,
					   TAG("apiSSM_APPLY_BUTTON"));
	cancel = (vbutton*)vdialogFindItem (_apiSetScrollbarMarginDialog,
					    TAG("apiSSM_CANCEL_BUTTON"));
	slider = (vcontrol*)vdialogFindItem (_apiSetScrollbarMarginDialog,
					     TAG("apiSSM_SLIDER"));
	sliderValue = (vtextitem*)vdialogFindItem(_apiSetScrollbarMarginDialog,
						  TAG("apiSSM_SLIDER_VALUE"));

	vbuttonSetNotify (apply, _apiApplySetScrollbarMargin);
	vbuttonSetNotify (cancel, _apiCancelSetScrollbarMargin);

	vbuttonSetData (apply, vdialogFindItem (_apiSetScrollbarMarginDialog,
						TAG("apiSSM_SLIDER")));

	vcontrolSetData (slider, sliderValue);
	vcontrolSetNotify (slider, _apiSetScrollbarMarginSliderNotify);

    }

    vdialogOpen (_apiSetScrollbarMarginDialog);
    vdialogSetData (_apiSetScrollbarMarginDialog, rock);
    vwindowRaise (vdialogGetWindow (_apiSetScrollbarMarginDialog));

} /* _apiOpenSetScrollbarMarginDialog */




/* _apiCloseSetScrollbarMarginDialog -- closes the dialog where the users can
 *			set the value of selected cells.
 */
static void _apiCloseSetScrollbarMarginDialog (void)
{
    if (_apiSetScrollbarMarginDialog != NULL) {
	vdialogClose (_apiSetScrollbarMarginDialog);
	vdialogSetData (_apiSetScrollbarMarginDialog, NULL);
    }
} /* _apiOpenSetScrollbarMarginDialog */





/* ------------------ Set Row Count stuff ------------------ */


static vtextitem  *_apiSetRowCountTextItem = NULL;


/* _apiApplySetRowCount -- sets the row count to what was typed into 
 *			the text box.
 *
 *  -> button   -- the pushbutton that handled the event
 *  -> event	-- the event that triggered this.
 */
static void _apiApplySetRowCount (vbutton *button, vevent *event)
{
    apiRock	*rock = (apiRock*)vdialogGetData (vdialogDetermineItemDialog
						  (vbuttonGetItem(button)));
    int			value;

    value = vtextitemGetTextAsInt (_apiSetRowCountTextItem);

    vlistSetRowCount (vlistviewGetList (rock->listview), value);
    
    _apiNoteTextScribed (rock, vscribeScribeMulti
			 (vcharScribeLiteral ("vlistSetRowCount ("
					      "vlistviewGetList(view), "),
			  vnumScribeInt (value),
			  vcharScribeLiteral (");"),
			  NULL));

} /* _apiApplySetRowCount */




/* _apiCancelSetRowCount -- Close the SetRowCount dialog
 *
 *  -> button   -- the pushbutton that handled the event
 *  -> event	-- the event that triggered this.
 */
static void _apiCancelSetRowCount (vbutton *button, vevent *event)
{
    _apiCloseSetRowCountDialog ();
} /* _apiCancelSetRowCount */




/* _apiOpenSetRowCountDialog -- opens a dialog where the users can set
 * 			the row count by typing into a textfield
 */
static void _apiOpenSetRowCountDialog (apiRock *rock)
{
    if (_apiSetRowCountDialog == NULL) {
	vresource	dialogRes = vresourceNULL;
	vbutton	       *apply = NULL, *cancel = NULL;

	dialogRes = vresourceGet (rock->apiResources,
				  TAG("Set Row Count"));

	_apiSetRowCountDialog = vdialogLoad (dialogRes);

	apply = (vbutton*)vdialogFindItem (_apiSetRowCountDialog,
					   TAG("apiSRC_APPLY_BUTTON"));
	cancel = (vbutton*)vdialogFindItem (_apiSetRowCountDialog,
					    TAG("apiSRC_CANCEL_BUTTON"));

	vbuttonSetNotify (apply, _apiApplySetRowCount);
	vbuttonSetNotify (cancel, _apiCancelSetRowCount);
	
	_apiSetRowCountTextItem = (vtextitem*)vdialogFindItem
	(_apiSetRowCountDialog,	 TAG("apiSRC_EDIT_TEXT"));
				   
    }

    vdialogOpen (_apiSetRowCountDialog);
    vdialogSetData (_apiSetRowCountDialog,rock);
    vwindowRaise (vdialogGetWindow(_apiSetRowCountDialog));

} /* _apiOpenSetRowCountDialog */




/* _apiCloseSetRowCountDialog -- closes the dialog where the users can set
 *			the value of selected cells.
 */
static void _apiCloseSetRowCountDialog (void)
{
    if (_apiSetRowCountDialog != NULL) {
	vdialogClose (_apiSetRowCountDialog);
	vdialogSetData (_apiSetRowCountDialog, NULL);
    }
} /* _apiOpenSetRowCountDialog */





/* ------------------ Set Column Count stuff ------------------ */


static vtextitem  *_apiSetColumnCountTextItem = NULL;


/* _apiApplySetColumnCount -- sets the column count to what was typed into 
 *			the text box.
 *
 *  -> button   -- the pushbutton that handled the event
 *  -> event	-- the event that triggered this.
 */
static void _apiApplySetColumnCount (vbutton *button, vevent *event)
{
    apiRock	*rock = (apiRock*)vdialogGetData (vdialogDetermineItemDialog
						  (vbuttonGetItem(button)));
    int			value;

    value = vtextitemGetTextAsInt (_apiSetColumnCountTextItem);

    vlistSetColumnCount (vlistviewGetList (rock->listview), value);
    
    _apiNoteTextScribed (rock, vscribeScribeMulti
			 (vcharScribeLiteral ("vlistSetColumnCount ("
					      "vlistviewGetList(view), "),
			  vnumScribeInt (value),
			  vcharScribeLiteral (");"),
			  NULL));

} /* _apiApplySetColumnCount */




/* _apiCancelSetColumnCount -- Close the SetColumnCount dialog
 *
 *  -> button   -- the pushbutton that handled the event
 *  -> event	-- the event that triggered this.
 */
static void _apiCancelSetColumnCount (vbutton *button, vevent *event)
{
    _apiCloseSetColumnCountDialog ();
} /* _apiCancelSetColumnCount */




/* _apiOpenSetColumnCountDialog -- opens a dialog where the users can set
 * 			the column count by typing into a textfield
 */
static void _apiOpenSetColumnCountDialog (apiRock *rock)
{
    if (_apiSetColumnCountDialog == NULL) {
	vresource	dialogRes = vresourceNULL;
	vbutton	       *apply = NULL, *cancel = NULL;

	dialogRes = vresourceGet (rock->apiResources,
				  TAG("Set Column Count"));

	_apiSetColumnCountDialog = vdialogLoad (dialogRes);

	apply = (vbutton*)vdialogFindItem (_apiSetColumnCountDialog,
					   TAG("apiSCC_APPLY_BUTTON"));
	cancel = (vbutton*)vdialogFindItem (_apiSetColumnCountDialog,
					    TAG("apiSCC_CANCEL_BUTTON"));

	vbuttonSetNotify (apply, _apiApplySetColumnCount);
	vbuttonSetNotify (cancel, _apiCancelSetColumnCount);

	_apiSetColumnCountTextItem = (vtextitem*)vdialogFindItem 
	(_apiSetColumnCountDialog, TAG("apiSCC_EDIT_TEXT"));
	
    }
    vdialogOpen (_apiSetColumnCountDialog);
    vdialogSetData (_apiSetColumnCountDialog, rock);
    vwindowRaise (vdialogGetWindow(_apiSetColumnCountDialog));
} /* _apiOpenSetColumnCountDialog */




/* _apiCloseSetColumnCountDialog -- closes the dialog where the users can set
 *			the value of selected cells.
 */
static void _apiCloseSetColumnCountDialog (void)
{
    if (_apiSetColumnCountDialog != NULL) {
	vdialogClose (_apiSetColumnCountDialog);
	vdialogSetData (_apiSetColumnCountDialog, NULL);
    }
} /* _apiOpenSetColumnCountDialog */




/* ------------------ Set Column Width Dialog stuff ------------------ */


static vtextitem  *_apiSetColumnWidthTextItem = NULL;



/* _apiApplySetColumnWidth -- sets the cell value of all selected cells to
 * 			what was typed into the text box.
 *
 *  -> button   -- the pushbutton that handled the event
 *  -> event	-- the event that triggered this.
 */
static void _apiApplySetColumnWidth (vbutton *button, vevent *event)
{
    apiRock	*rock = (apiRock*)vdialogGetData (vdialogDetermineItemDialog
						  (vbuttonGetItem(button)));
    vlistIterator	iterator;
    int			value;

    value = vtextitemGetTextAsInt (_apiSetColumnWidthTextItem);
    
    vlistInitSelectionIterator (&iterator,
				vlistviewGetSelection(rock->listview));

    while (vlistNextIterator(&iterator)) {
	int	column;

	column = vlistGetIteratorColumn (&iterator);

	vlistviewSetColumnWidth (rock->listview, column, value);
    }
    
    vlistDestroyIterator (&iterator);

    _apiNoteTextScribed (rock, vscribeScribeMulti
			 (vcharScribeLiteral ("vlistviewSetColumnWidth ("
					      "listview, column, "),
			  vnumScribeInt (value),
			  vcharScribeLiteral (");"),
			  NULL));
} /* _apiApplySetColumnWidth */




/* _apiCancelSetColumnWidth -- Close the SetColumnWidth dialog
 *
 *  -> button   -- the pushbutton that handled the event
 *  -> event	-- the event that triggered this.
 */
static void _apiCancelSetColumnWidth (vbutton *button, vevent *event)
{
    _apiCloseSetColumnWidthDialog ();
} /* _apiCancelSetColumnWidth */




/* _apiOpenSetColumnWidthDialog -- opens a dialog where the users can set
 *			the value of selected cells.
 */
static void _apiOpenSetColumnWidthDialog (apiRock *rock)
{
    if (_apiSetColumnWidthDialog == NULL) {
	vresource	dialogRes = vresourceNULL;
	vbutton	       *apply = NULL, *cancel = NULL;

	dialogRes = vresourceGet (rock->apiResources,
				  TAG("Set Column Width"));

	_apiSetColumnWidthDialog = vdialogLoad (dialogRes);

	apply = (vbutton*)vdialogFindItem (_apiSetColumnWidthDialog,
					   TAG("apiSCW_APPLY_BUTTON"));
	cancel = (vbutton*)vdialogFindItem (_apiSetColumnWidthDialog,
					    TAG("apiSCW_CANCEL_BUTTON"));

	vbuttonSetNotify (apply, _apiApplySetColumnWidth);
	vbuttonSetNotify (cancel, _apiCancelSetColumnWidth);

	_apiSetColumnWidthTextItem = (vtextitem*)vdialogFindItem 
	(_apiSetColumnWidthDialog, TAG("apiSCW_EDIT_TEXT"));
	
    }

    vdialogOpen (_apiSetColumnWidthDialog);
    vdialogSetData (_apiSetColumnWidthDialog, rock);
    vwindowRaise (vdialogGetWindow(_apiSetColumnWidthDialog));

} /* _apiOpenSetColumnWidthDialog */




/* _apiCloseSetColumnWidthDialog -- closes the dialog where the users can set
 *			the value of selected cells.
 */
static void _apiCloseSetColumnWidthDialog (void)
{
    if (_apiSetColumnWidthDialog != NULL) {
	vdialogClose (_apiSetColumnWidthDialog);
	vdialogSetData (_apiSetColumnWidthDialog, NULL);
    }
} /* _apiOpenSetColumnWidthDialog */





/* ------------------ Set Row Height Dialog stuff ------------------ */


static vtextitem  *_apiSetRowHeightTextItem = NULL;



/* _apiApplySetRowHeight -- sets the cell value of all selected cells to
 * 			what was typed into the text box.
 *
 *  -> button   -- the pushbutton that handled the event
 *  -> event	-- the event that triggered this.
 */
static void _apiApplySetRowHeight (vbutton *button, vevent *event)
{
    apiRock	*rock = (apiRock*)vdialogGetData (vdialogDetermineItemDialog
						  (vbuttonGetItem(button)));
    vlistIterator	iterator;
    int			value;

    value = vtextitemGetTextAsInt (_apiSetRowHeightTextItem);
    
    vlistInitSelectionIterator (&iterator,
				vlistviewGetSelection(rock->listview));

    while (vlistNextIterator(&iterator)) {
	int	row;

	row = vlistGetIteratorRow (&iterator);

	vlistviewSetRowHeight (rock->listview, row, value);
    }
    
    vlistDestroyIterator (&iterator);

    _apiNoteTextScribed (rock, vscribeScribeMulti
			 (vcharScribeLiteral ("vlistviewSetRowHeight ("
					      "listview, column, "),
			  vnumScribeInt (value),
			  vcharScribeLiteral (");"),
			  NULL));

} /* _apiApplySetRowHeight */




/* _apiCancelSetRowHeight -- Close the SetRowHeight dialog
 *
 *  -> button   -- the pushbutton that handled the event
 *  -> event	-- the event that triggered this.
 */
static void _apiCancelSetRowHeight (vbutton *button, vevent *event)
{
    _apiCloseSetRowHeightDialog ();
} /* _apiCancelSetRowHeight */




/* _apiOpenSetRowHeightDialog -- opens a dialog where the users can set
 *			the value of selected cells.
 */
static void _apiOpenSetRowHeightDialog (apiRock *rock)
{
    if (_apiSetRowHeightDialog == NULL) {
	vresource	dialogRes = vresourceNULL;
	vbutton	       *apply = NULL, *cancel = NULL;

	dialogRes = vresourceGet (rock->apiResources,
				  TAG("Set Row Height"));
	
	_apiSetRowHeightDialog = vdialogLoad (dialogRes);

	apply = (vbutton*)vdialogFindItem (_apiSetRowHeightDialog,
					   TAG("apiSRH_APPLY_BUTTON"));
	cancel = (vbutton*)vdialogFindItem (_apiSetRowHeightDialog,
					    TAG("apiSRH_CANCEL_BUTTON"));

	vbuttonSetNotify (apply, _apiApplySetRowHeight);
	vbuttonSetNotify (cancel, _apiCancelSetRowHeight);

	_apiSetRowHeightTextItem = (vtextitem*)vdialogFindItem 
	(_apiSetRowHeightDialog, TAG("apiSRH_EDIT_TEXT"));
    }

    vdialogOpen (_apiSetRowHeightDialog);
    vdialogSetData (_apiSetRowHeightDialog, rock);
    vwindowRaise (vdialogGetWindow(_apiSetRowHeightDialog));

} /* _apiOpenSetRowHeightDialog */




/* _apiCloseSetRowHeightDialog -- closes the dialog where the users can set
 *			the value of selected cells.
 */
static void _apiCloseSetRowHeightDialog (void)
{
    if (_apiSetRowHeightDialog != NULL) {
	vdialogClose (_apiSetRowHeightDialog);
	vdialogSetData (_apiSetRowHeightDialog, NULL);
    }
} /* _apiCloseSetRowHeightDialog */




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


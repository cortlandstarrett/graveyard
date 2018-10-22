/* $Id: master.c,v 1.6 1995/04/27 18:05:24 chad Exp $ */

/*****************************************************************************
 * included files
 ****************************************************************************/

#include <vport.h>

#ifndef  vlafINCLUDED
#include vlafHEADER
#endif

#ifndef  vcommINCLUDED
#include vcommHEADER
#endif

#ifndef  vapplicationINCLUDED
#include vapplicationHEADER
#endif

#ifndef  vbuttonINCLUDED
#include vbuttonHEADER
#endif 

#ifndef  vdasservINCLUDED
#include vdasservHEADER
#endif

#ifndef  vdatatagINCLUDED
#include vdatatagHEADER
#endif

#ifndef  vdialogINCLUDED
#include vdialogHEADER
#endif

#ifndef  vdictINCLUDED
#include vdictHEADER
#endif

#ifndef  vimageINCLUDED
#include vimageHEADER
#endif

#ifndef  vnameINCLUDED
#include vnameHEADER
#endif 

#ifndef  vserviceINCLUDED
#include vserviceHEADER
#endif

#ifndef  vsessionINCLUDED
#include vsessionHEADER
#endif

#ifndef  vstartupINCLUDED
#include vstartupHEADER
#endif

#ifndef  vstdlibINCLUDED
#include vstdlibHEADER
#endif

#ifndef  utilityINCLUDED
#include "utility.h"
#endif

#if (vdebugDEBUG)
static const char _Tag[] = __FILE__;
#define vdebugTAG _Tag
#endif

/******************************************************************************
 * private constants
 *****************************************************************************/

#define mandelbrotX   -2.3
#define mandelbrotY   -1.5
#define mandelbrotW    4.0
#define mandelbrotH    3.0

#define cellWIDTH      64
#define cellHEIGHT     48
 
/******************************************************************************
 * private structures
 *****************************************************************************/

typedef struct {
    int                   buttonDownX, buttonDownY;
    int                   buttonUpX, buttonUpY;
    int                   rows, columns;
    vbool                *dirty;
    double		  setX, setY;
    double		  setW, setH;
    vdialogItem          *pictureDialogItem;
    vbutton              *zoomInButton;
    vbutton              *zoomOutButton;
    int                   sessionCount;
    vsession            **sessions;
} masterGlobals;

/******************************************************************************
 * private variables
 *****************************************************************************/

static vdialogItemClass         *_dialogItemClass;
static vdialog                  *_dialog;
static masterGlobals            *_globals;

/******************************************************************************
 * private functions
 *****************************************************************************/

static void    _masterSendCell(vsession *session);

/*
 * _masterNotifyStatement get notified for what happens to a statement
 * statement -> the statement we are getting the notify about
 * event     -> what happened to the statement
 */

static void _masterNotifyStatement (vsessionStatement      *statement, 
				    vsessionStatementEvent *event)
{
    vimage        *image;
    int            cellX, cellY, cellW, cellH;
    int            size, *buffer;
    
    switch (vsessionGetStatementEventCode(event))
    {
    case vsessionStatementEVENT_COMPLETED:

	/*
	 * Get results
	 */
	
        vsessionGetStatementReturnValue(statement, &size, &buffer);
	
	/* 
	 * Since buffer contains as [cellX, cellY, cellW, cellH, cellBuffer],
	 * derive out cellX, cellY, cellW, cellH, cellBuffer from this buffer
	 */
	
	cellX = buffer[0];
	cellY = buffer[1];
	cellW = buffer[2];
	cellH = buffer[3];
	
	/* 
	 * Re-use the session for next cell
	 */

	_masterSendCell(vsessionGetStatementSession(statement));
	
	/*
	 * Deal with the data
	 */
	
	image = vdialogGetItemImage(_globals->pictureDialogItem);
	utilityAppendCellToImage(image,
				 cellX, cellY, cellW, cellH, &buffer[4]);
	vdialogInvalItem(_globals->pictureDialogItem, vwindowINVAL_OPAQUE);
	
	
	/*
	 * Finished with the statement's buffer
	 */
	
	vmemFree(buffer);
	break;

    case vsessionStatementEVENT_CANNOT_SEND:

	/*
	 * Mark this cell dirty
	 */

	size = (int)vsessionGetStatementData(statement);
	_globals->dirty[size] = TRUE;

	vdebugMAdvise(("MASTER: Cannot send statement to a SLAVE.\n"));

	break;

    case vsessionStatementEVENT_FAILED:

	/*
	 * Mark this cell dirty
	 */

	size = (int)vsessionGetStatementData(statement);
	_globals->dirty[size] = TRUE;

	vdebugMAdvise(("MASTER: Statement failed by a SLAVE.\n"));

	break;

    case vsessionStatementEVENT_END_SESSION:

	/*
	 * Mark this cell dirty
	 */

	size = (int)vsessionGetStatementData(statement);
	_globals->dirty[size] = TRUE;

	vdebugMAdvise(("MASTER: Statement ended with a SLAVE.\n"));

	break;

    default:
	break;
    }
    
} /* _masterNotifyStatement */

/*
 * _masterConstructCell returns x,y,w,h of cell i
 * index  -> ith cell to request for (up to cellSIZExcellSIZE cells)
 * width  -> the global width of image
 * height -> the global height of image
 * cell   <- the rect of a cell
 */

static void _masterConstructCell(int index, int width, int height, vrect *cell)
{
    int x, y;
    int x1, x2, y1, y2;

    y = index/_globals->columns;
    x = index%_globals->columns;
    
    x1 = x*width/_globals->columns;
    y1 = y*height/_globals->rows;
    
    x2 = (x + 1)*width/_globals->columns;
    y2 = (y + 1)*height/_globals->rows;
    
    vrectSet(x1, y1, x2 - x1, y2 - y1, cell);

} /* _masterConstructCell */


/*
 * _masterFindDirtyCellIndex scans for dirty cells and returns an index
 *   <- index of the first dirty cell found, -1 if no cells are dirty.
 */

static int _masterFindDirtyCellIndex()
{
    int    index;
    vbool *b;

    b = _globals->dirty + _globals->columns*_globals->rows - 1;
    while (b >= _globals->dirty && *b == FALSE)
	b--;

    index = b - _globals->dirty;
    return index;

} /* _masterFindDirtyCellIndex */

/*
 * _masterSend sends off a portion of the image to the service
 * service -> the service to send the part too
 */

static void _masterSendCell(vsession *session)
{
    vsessionStatement *statement;
    int                imageW, imageH, index;
    vrect              cell;

    index = _masterFindDirtyCellIndex();
    if (index >= 0)
    {
	/*
	 * Disable zoom buttons
	 */

	vdialogDisableItem(vbuttonGetItem(_globals->zoomInButton));
	vdialogDisableItem(vbuttonGetItem(_globals->zoomOutButton));

	/*
	 * Get the info of the cell and mark it clean
	 */

	imageW = vdialogGetItemW(_globals->pictureDialogItem);
	imageH = vdialogGetItemH(_globals->pictureDialogItem);
	_masterConstructCell(index, imageW, imageH, &cell);
	_globals->dirty[index] = FALSE;
	
	/*
	 * Build the statement to dispatch
	 */
	
	statement = vsessionCreateStatement();
	vsessionSetStatementSession(statement, session);
	vsessionSetStatementSignature(statement, utilityGetSignature());
	vsessionSetDestroyStatementWhenFinished(statement, TRUE);
	vsessionSetStatementArgs(statement, imageW, imageH, 
				 cell.x, cell.y, cell.w, cell.h,
				 _globals->setX, _globals->setY,
				 _globals->setW, _globals->setH);
	vsessionSetStatementNotify(statement, _masterNotifyStatement);
	vsessionSetStatementData(statement, (void *)index);
	vsessionSendStatement(statement);
    }
    else 
    {
	/*
	 * Enable zoom buttons
	 */

	vdialogEnableItem(vbuttonGetItem(_globals->zoomInButton));
	vdialogEnableItem(vbuttonGetItem(_globals->zoomOutButton));
    }
    
} /* _masterSendCell */

/*
 * _masterNotifySession get notified for session startup
 * session -> the session
 * event   -> the event handler
 */

static void _masterNotifySession(vsession *session, vsessionEvent *event)
    
{
    switch (vsessionGetEventCode(event))
    {
    case vsessionEVENT_BEGIN:
	vdebugMAdvise(("MASTER: Begin session with a SLAVE.\n"));
	_masterSendCell(session);
	break;

    case vsessionEVENT_CANNOT_BEGIN:
	vdebugMAdvise(("MASTER: Cannot begin session with a SLAVE.\n"));
	break;

    case vsessionEVENT_END:
	vdebugMAdvise(("MASTER: End session with a SLAVE.\n"));
	break;

    default:
	break;
    }
    
} /* _masterNotifySession */

/*
 * _masterWipeOffSessions wipes off all available sessions
 */

static void _masterWipeOffSessions(void)
{
    int index;

    if (_globals->sessions != NULL) 
    {
	for (index = _globals->sessionCount - 1; index >= 0; index--)
	    if (_globals->sessions[index] != NULL)
		vsessionDestroy(_globals->sessions[index]);
	vmemFree(_globals->sessions);
    };

} /* _masterWipeOffSessions */

/*
 * _masterNotifyStatementMatch get notified of the matched statement
 * statement -> the statement requesting for matching services
 * event     -> the event handler
 */

static void _masterNotifyStatementMatch(vsessionStatement      *statement,
					vsessionStatementEvent *event)
{
    int       scrapCount;
    vscrap  **scraps;
    int       code;
    int       index;
    
    code = vsessionGetStatementEventCode(event);
    switch (code)
    {
    case vsessionStatementEVENT_COMPLETED:

	/*
	 * Wipe out old sessions
	 */

	_masterWipeOffSessions();

	/*
	 * Collect all sessions
	 */
	
	vsessionGetStatementReturnValue(statement, &scrapCount, &scraps);
	_globals->sessions = vmemAlloc(scrapCount * sizeof(vsession *));
	_globals->sessionCount = scrapCount;

	if (scrapCount == 0)
	    vdebugMAdvise(("MASTER: No running SLAVES. Execute at least one.\n"));
	
	for (index = 0; index < scrapCount; index++)
	{
	    _globals->sessions[index] = vsessionCreate();
	    vsessionSetAttributesFromScrap(_globals->sessions[index], 
					   scraps[index]); 
	    vsessionSetNotify(_globals->sessions[index], _masterNotifySession);
	    vsessionBegin(_globals->sessions[index]);
	}

	if (scraps != NULL)
	    vmemFree(scraps);

	break;

    case vsessionStatementEVENT_CANNOT_SEND:
	vdebugMAdvise(("MASTER: Cannot send statement to Service Broker.\n"));
	break;

    case vsessionStatementEVENT_FAILED:
	vdebugMAdvise(("MASTER: Statement failed by Service Broker.\n"));
	break;

    case vsessionStatementEVENT_END_SESSION:
	vdebugMAdvise(("MASTER: Statement ended with Service Broker.\n"));
	break;

    default:
	break;
    }

    vsessionEnd(vsessionGetStatementSession(statement));

} /* _masterNotifyStatementMatch */


/*
 * _masterScanSlavesAndSendCell scans the networks for slaves to draw cells
 */


static void _masterScanSlavesAndSendCell(void)
{
    vdatatag            *volatile datatag    = NULL;
    vsession            *volatile session    = NULL;
    vsessionStatement   *volatile statement  = NULL;
    vdict               *volatile dict       = NULL;

    vexUNWIND_PROTECT {
	
	/*
	 *  Create dictionary to match with
	 */

	dict = vdictCreate(vnameHash);
	vdictStore(dict, vname_Title,
		   vnameInternGlobalScribed(utilityGetMandelbrotName()));
	
	/*
	 *  StartUp datatag
	 */
	
	datatag = vdatatagCreateDict();
	vdatatagSetDictElementDatatag(datatag, vname_Title, vdatatagGetTag());
	
	/*
	 *  Create session
	 */
	
	session = vsessionCreate();
	vsessionSetAttributesFromScrap(session, 
				       vdasservCreateAttributeScrap());

	vsessionBegin(session);
	
	/*
	 *  Create statement
	 */
	
	statement =
	    vdasservMakeMatchStatement(session,
				       vdatatagScrapFromValue(datatag, dict));
    }
    vexON_UNWIND {
    	if (dict)
	    vdictDestroy(dict);
	if (datatag)
	    vdatatagDestroy(datatag);
	if (!statement)
	    vexPropagate(vexGetRootClass(), vexNULL);
    }
    vexEND_UNWIND;
    
    vsessionSetDestroyStatementWhenFinished(statement, TRUE);
    vsessionSetDestroyWhenInactive(session, TRUE);
    vsessionSetStatementNotify(statement, _masterNotifyStatementMatch);
    vsessionSendStatement(statement);

} /* _masterScanSlavesAndSendCell */


/*
 * _masterConstructZoomRect construct the (yellow) zoom rect
 * dialogItem  -> dialogItem containing the image
 * buttonDownX -> X where the mouse button is pressed
 * buttonDownY -> Y where the mouse button is pressed
 * buttonUpX   -> X where the mouse button is released
 * buttonUpY   -> Y where the mouse button is released
 * rect        <- zoom rect containing both (x,y) in the same aspect as dialogItem
 */ 

static void _masterConstructZoomRect(vdialogItem *dialogItem,
				     int buttonDownX, int buttonDownY,
				     int buttonUpX, int buttonUpY, vrect *rect)
{
    int width, height;
    
    width = vdialogGetItemW(dialogItem);
    height = vdialogGetItemH(dialogItem);
    
    vrectSetPoints(buttonDownX, buttonDownY, buttonUpX, buttonUpY, rect);
    
    if (rect->w > rect->h*width/height)
	vrectInset(rect, 0, (rect->h - rect->w*height/width)/2, rect);
    else if (rect->h > rect->w*height/width)
	vrectInset(rect, (rect->w - rect->h*width/height)/2, 0, rect);

} /* _masterConstructZoomRect */


/*
 * _masterMarkImageDirty marks all cells in image dirty so it will be drawn
 *     by DAS in the future.
 */

static void _masterMarkImageDirty(void)
{
    vbool *b;

    /*
     * Mark all cells dirty
     */

    b = _globals->dirty;
    b += _globals->columns*_globals->rows;
    while (b > _globals->dirty)
    {
	b--;
	*b = TRUE;
    }

    /*
     * Let all slaves re-draw the cells
     */

    _masterScanSlavesAndSendCell();

} /* _masterMarkImageDirty */


/*
 * _masterResizeImage resize the image
 * dialogItem -> the dialogItem containing the image to resize to dialogItem's
 */

static void _masterResizeImage(vdialogItem *dialogItem)
{
    int width, height;


    /*
     * Resize the image
     */

    width = vdialogGetItemW(dialogItem);
    height = vdialogGetItemH(dialogItem);
    vimageSetSize(vdialogGetItemImage(dialogItem), width, height);

    /*
     * Reset the number of rows and columns of cells
     */

    _globals->columns = width/cellWIDTH;
    if (_globals->columns*cellWIDTH < width)
	_globals->columns++;

    _globals->rows = height/cellHEIGHT;
    if (_globals->rows*cellHEIGHT < height)
	_globals->rows++;

    if (_globals->dirty)
	vmemFree(_globals->dirty);
    _globals->dirty = (vbool *)
	vmemAlloc(_globals->rows*_globals->columns*sizeof(vbool));

    /*
     * Reset the setH so that each pixel remains 1 by 1 unit.
     */
    
    _globals->setH = _globals->setW*height/width;

    /*
     * Mark this image dirty so it will be redrawn via DAS in the future
     */

    _masterMarkImageDirty();
}

/*
 * _masterDrawImageAndZoomRect draws both image and zoom rect
 * dialogItem -> dialogItem contaning image
 */

static void _masterDrawImageAndZoomRect(vdialogItem *dialogItem)
{
    vrect zoomRect;

    vdrawGSave();
    vdialogItemDrawDevice(dialogItem);
    vdrawNewPath();
    vdrawMoveTo(vdialogGetItemX(dialogItem), vdialogGetItemY(dialogItem));
    vdrawImageIdent(vdialogGetItemImage(dialogItem));
    
    _masterConstructZoomRect(dialogItem, 
			     _globals->buttonDownX, _globals->buttonDownY,
			     _globals->buttonUpX, _globals->buttonUpY, 
			     &zoomRect);
    vdrawFSetRGBColor(1.0, 1.0, 0.0);
    vdrawRectsClip(vdialogGetItemRect(dialogItem), 1);
    vdrawTranslate(vdialogGetItemX(dialogItem), vdialogGetItemY(dialogItem));
    vdrawRectsStroke(&zoomRect, 1);
    vdrawGRestore();
}

static void _masterDrawPicture(vdialogItem *dialogItem)
{
    vimage      *image;

    image = vdialogGetItemImage(dialogItem);
    if (image == NULL) 
    {
	image = vimageCreate();
	vimageSetTrueColor(image, TRUE);
	vimageSetDepth(image, 24);
	vdialogSetItemImageOwned(dialogItem, image);
	_masterResizeImage(dialogItem);
	vpixmapClear(vimageGetMap(image), 0);
    }
    else if (vdialogGetItemW(dialogItem) != vimageGetWidth(image) ||
	     vdialogGetItemH(dialogItem) != vimageGetHeight(image))
    {
	_masterResizeImage(dialogItem);
	vpixmapClear(vimageGetMap(image), 0);
    }

    _masterDrawImageAndZoomRect(dialogItem);
}


#if (vportWIN_MAC)
static int _masterGetMacNaturalSeparation(vdialogItem *item, 
					   vdialogItem *to,
					   unsigned int which)
{
    int separation;

    separation = vclassSendSuper(_dialogItemClass, 
    		                 vdialogGET_ITEM_NATURAL_SEPARATION, 
    		                 (item, to, which));
    if (vlafAppear()==vlafMAC && separation<5)
      separation = 5;
    
    return separation;
}
#endif


static int _masterHandlePictureButtonDown(vdialogItem *dialogItem,
					  vevent *event)
{
    if (vclassSendSuper(_dialogItemClass, vdialogHANDLE_ITEM_BUTTON_DOWN,
			(dialogItem, event)))
	return TRUE;
    
    _globals->buttonDownX = _globals->buttonUpX = 
	veventGetPointerX(event) - vdialogGetItemX(dialogItem);
    _globals->buttonDownY = _globals->buttonUpY =
	veventGetPointerY(event) - vdialogGetItemY(dialogItem);

    vdrawGSave();
    vdialogItemDrawDevice(dialogItem);
    vdrawNewPath();
    vdrawMoveTo(vdialogGetItemX(dialogItem), vdialogGetItemY(dialogItem));
    vdrawImageIdent(vdialogGetItemImage(dialogItem));
    vdrawGRestore();
    
    return TRUE;
}

static int _masterHandlePictureButtonUp(vdialogItem *dialogItem, vevent *event)
{
    vclassSendSuper(_dialogItemClass,
		    vdialogHANDLE_ITEM_BUTTON_UP, (dialogItem, event));
    
    _globals->buttonUpX = 
	veventGetPointerX(event) - vdialogGetItemX(dialogItem);
    _globals->buttonUpY =
	veventGetPointerY(event) - vdialogGetItemY(dialogItem);
    
    _masterDrawImageAndZoomRect(dialogItem);

    return TRUE;
}

static int _masterHandlePictureDrag(vdialogItem *dialogItem, vevent *event)
{
    vclassSendSuper(_dialogItemClass,
		    vdialogHANDLE_ITEM_DRAG, (dialogItem, event));
    
    _globals->buttonUpX =
	veventGetPointerX(event) - vdialogGetItemX(dialogItem);
    _globals->buttonUpY = 
	veventGetPointerY(event) - vdialogGetItemY(dialogItem);
    
    _masterDrawImageAndZoomRect(dialogItem);

    return TRUE;
}

/*
 * _masterNotifyButtonZoomIn get notified and zooms in the mandelbrot set
 * button -> button to be notified
 * event  -> the notify event
 */

static void _masterNotifyButtonZoomIn(vbutton *button, vevent *event)
{
    double  setX, setY;
    double  setW, setH;
    double  factor;
    int     imageWidth, imageHeight;
    vrect   zoomRect;
    
    
    _masterConstructZoomRect(_globals->pictureDialogItem,
			     _globals->buttonDownX, _globals->buttonDownY,
			     _globals->buttonUpX, _globals->buttonUpY,
			     &zoomRect);
    
    imageWidth  = vdialogGetItemW(_globals->pictureDialogItem);
    imageHeight = vdialogGetItemH(_globals->pictureDialogItem);
    
    factor = _globals->setW/imageWidth;

    setX = _globals->setX + factor*zoomRect.x;
    setY = _globals->setY + factor*zoomRect.y;
    setW = factor*zoomRect.w;
    setH = setW*imageHeight/imageWidth;
    
    _globals->setX = setX;
    _globals->setY = setY;
    _globals->setW = setW;
    _globals->setH = setH;

    _masterMarkImageDirty();
}

/*
 * _masterNotifyButtonZoomOut get notified and zooms out the mandelbrot set
 * button -> button to be notified
 * event  -> the notify event
 */

static void _masterNotifyButtonZoomOut(vbutton *button, vevent *event)
{
    double setX, setY;
    double setW, setH;
    double factor;
    int    imageWidth, imageHeight;
    vrect  zoomRect;
    
    
    _masterConstructZoomRect(_globals->pictureDialogItem,
			     _globals->buttonDownX, _globals->buttonDownY,
			     _globals->buttonUpX, _globals->buttonUpY,
			     &zoomRect);
    
    imageWidth  = vdialogGetItemW(_globals->pictureDialogItem);
    imageHeight = vdialogGetItemH(_globals->pictureDialogItem);
    
    factor = _globals->setW/zoomRect.w;
    
    setX = _globals->setX - factor*zoomRect.x;
    setY = _globals->setY - factor*zoomRect.y;
    setW = factor*imageWidth;
    setH = factor*imageHeight;
    
    _globals->setX = setX;
    _globals->setY = setY;
    _globals->setW = setW;
    _globals->setH = setH;
    
    _masterMarkImageDirty();
}

static void _masterNotifyButtonQuit(vbutton *button, vevent *event)
{
    veventStopProcessing();
}

/******************************************************************************
 * Initialization functions
 *****************************************************************************/

/*
 * _masterShutdown cleans up
 */

static void _masterShutdown(void)
{
    _masterWipeOffSessions();

    if (_dialog)
    {
	vdialogDestroy(_dialog);
	_dialog = NULL;
    }

    if (_globals) 
    {
	if (_globals->dirty)
	    vmemFree(_globals->dirty);
	vmemFree(_globals);
	_globals = NULL;
    }
}

static void _masterStartup(void)
{
    vresource          resource;
    vdialogItem       *dialogItem;
    vdialogItem       *newDialogItem;
    vbutton           *button;
    const vname       *name;
   
   vcommRegisterAllDrivers();
  
    /*
     * DialogItem class...
     */
    
    _dialogItemClass = vclassReproduce(vdialogGetDefaultItemClass());
    vclassSet(_dialogItemClass, vdialogHANDLE_ITEM_BUTTON_DOWN, 
	      _masterHandlePictureButtonDown);
    vclassSet(_dialogItemClass, vdialogHANDLE_ITEM_BUTTON_UP,
	      _masterHandlePictureButtonUp);
    vclassSet(_dialogItemClass, vdialogHANDLE_ITEM_DRAG,
	      _masterHandlePictureDrag);
    vclassSet(_dialogItemClass, vdialogDRAW_ITEM,
	      _masterDrawPicture);

#if (vportWIN_MAC)
    vclassSet(_dialogItemClass, vdialogGET_ITEM_NATURAL_SEPARATION,
    	      _masterGetMacNaturalSeparation);
#endif
    
    /*
     * Set globals field...
     */
    
    _globals =
	(masterGlobals*)vmemAllocAndClear((size_t)sizeof(masterGlobals));
    _globals->setX = mandelbrotX;
    _globals->setY = mandelbrotY;
    _globals->setW = mandelbrotW;
    _globals->setH = mandelbrotH;
    
    /*
     * Get resources from .vr file...
     */
    
    name = vnameInternGlobalLiteral("Main_Dialog"); 
    resource = vapplicationGetResources(vapplicationGetCurrent());
    resource = vresourceGet(resource, name);
    
    /*
     * Main dialog...
     */
    
    _dialog = vdialogLoad(resource);
    vwindowPlace(vdialogGetWindow(_dialog), vwindowGetRoot(),
                 vrectPLACE_CENTER, vrectPLACE_CENTER);
    
    /*
     * Picture DialogItem...
     */
    
    name = vnameInternGlobalLiteral("Picture");
    newDialogItem = vdialogCreateItemOfClass(_dialogItemClass);
    dialogItem = (vdialogItem*)vdialogFindItem(_dialog, name);
    vdialogCopyItem(dialogItem, newDialogItem);
    vdialogSetItemListItemAt(vdialogGetItemList(_dialog),
			     vdialogGetItemIndex(_dialog, dialogItem),
			     newDialogItem);
    vdialogDestroyItem(dialogItem);
    _globals->pictureDialogItem = newDialogItem;
    
    /*
     * Zoom In Button...
     */
    
    name = vnameInternGlobalLiteral("Zoom In");
    button = (vbutton*)vdialogFindItem(_dialog, name);
    vbuttonSetNotify(button, _masterNotifyButtonZoomIn);
    _globals->zoomInButton = button;
    
    /*
     * Zoom Out Button...
     */
    
    name = vnameInternGlobalLiteral("Zoom Out");
    button = (vbutton*)vdialogFindItem(_dialog, name);
    vbuttonSetNotify(button, _masterNotifyButtonZoomOut);
    _globals->zoomOutButton = button;
    
    /*
     * Quit Button...
     */
    
    name = vnameInternGlobalLiteral("Quit");
    button = (vbutton*)vdialogFindItem(_dialog, name);
    vbuttonSetNotify(button, _masterNotifyButtonQuit);
}

/******************************************************************************
 * public functions
 *****************************************************************************/

/*
 * main is the image generator client
 * argc -> number of arguments in the command line
 * argv -> list of arguments in the command line
 *      <- exit status
 */

int main(int argc, char *argv[])
{
    
    vstartup(argc, argv);
    
    /*
     * set up our globals, dialog, etc.
     */
    
    _masterStartup();
    
    /*
     * Opens up master dialog
     */

    vdialogOpen(_dialog);

    /*
     * Let's do some work...
     */
    
    veventProcess();
    
    /*
     * cleanup our globals, service, etc.
     */
    
    _masterShutdown();
    
    exit(EXIT_SUCCESS);
    return EXIT_FAILURE;
}

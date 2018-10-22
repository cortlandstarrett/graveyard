/* $Id: slave.c,v 1.6 1995/05/02 21:04:13 abstine Exp $ */

/******************************************************************************
 * include files
 *****************************************************************************/

#include <vport.h>

#ifndef  vlafINCLUDED
#include vlafHEADER
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

#ifndef  vdialogINCLUDED
#include vdialogHEADER
#endif

#ifndef  veventINCLUDED
#include veventHEADER
#endif

#ifndef  vscrapINCLUDED
#include vscrapHEADER
#endif

#ifndef  vserviceINCLUDED
#include vserviceHEADER
#endif

#ifndef  vstartupINCLUDED
#include vstartupHEADER
#endif

#ifndef  vstdlibINCLUDED
#include vstdlibHEADER
#endif

#ifndef  vsessionINCLUDED
#include vsessionHEADER
#endif

#ifndef  vcommINCLUDED
#include vcommHEADER
#endif

#ifndef  vprefINCLUDED
#include vprefHEADER
#endif

#ifndef utilityINCLUDED
#include "utility.h"
#endif

/******************************************************************************
 * private variables
 *****************************************************************************/

static vservice	                *_service;
static vsession                 *_session;
static vdialogItemClass         *_dialogItemClass;
static vdialog                  *_dialog;
static vdialogItem              *_pictureDialogItem;
static vbutton                  *_quitButton;
static const vname              *nameEmpty;

/******************************************************************************
 * private functions
 *****************************************************************************/

static void _slaveDrawPicture(vdialogItem *dialogItem)
{
    const vrect *rect;
    vimage      *image;

    rect = vdialogGetItemRect(dialogItem);
    image = vdialogGetItemImage(dialogItem);

    if (image == NULL) 
    {
	image = vimageCreate();
	vimageSetSize(image, rect->w, rect->h);
	vimageSetTrueColor(image, TRUE);
	vimageSetDepth(image, 24);
	vpixmapClear(vimageGetMap(image), 0);
	vdialogSetItemImageOwned(dialogItem, image);
    }
    else if (rect->w != vimageGetWidth(image) ||
	     rect->h != vimageGetHeight(image))
    {
	vimageSetSize(image, rect->w, rect->h);
	vpixmapClear(vimageGetMap(image), 0);
    }

    vdrawGSave();
    vdrawNewPath();
    vdrawMoveTo(rect->x, rect->y);
    vdrawImageIdent(image);
    vdrawGRestore();
}


#if (vportWIN_MAC)
static int _slaveGetMacNaturalSeparation(vdialogItem *item, 
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

/*
 * _slaveNotifySession : the notify function for the mendalbrot server
 * session -> the session that received the event
 * event   -> the event for the session note proc to react too
 */

static void _slaveNotifySession(vsession *session, vsessionEvent *event)
{
    switch(vsessionGetEventCode(event))
    {
    case  vsessionEVENT_BEGIN:
	vdebugAdvise("SLAVE: Begin session.\n");
	break;

    case  vsessionEVENT_END:
	vdebugAdvise("SLAVE: End session.\n");
	break;

    case  vsessionEVENT_CANNOT_BEGIN:
	vdebugAdvise("SLAVE: Cannot begin session.\n");
	break;

    default:
	break;
    }
} /* _slaveNotifySession */

/*
 * _slaveHandlePrimitive handles the calculation for a region
 *           of the mandelbrot set
 * primitive  -> the primitive to handle
 * session    -> session primitive is for
 * args       -> arguments to primitive
 */

static vscrap *_slaveHandlePrimitive(vservicePrimitive *primitive,
				     vsession          *session,
				     vscrap            *args)
{
    vscrap        *scrap;
    int            imageW, imageH;
    double         setX, setY, setW, setH;
    int            cellX, cellY, cellW, cellH, size;
    int           *buffer;
    vimage        *image;

    /*
     * Get arguments to get started
     */

    vserviceGetPrimitiveArgs(primitive, args, 
			     &imageW, &imageH,
			     &cellX, &cellY, &cellW, &cellH,
			     &setX,  &setY,  &setW, &setH);
    
    /*
     * Now trim the cellWidth and cellHeight to the image edge
     */
    
    if (cellX + cellW > imageW)
	cellW = imageW - cellX;
    if (cellY + cellH > imageH)
	cellH = imageH - cellY;
    
    buffer = (int *)vmemAlloc((4+cellW*cellH)*sizeof(int));
    
    /*
     * calculate mandelbrot piece for this cell
     */
    
    utilityCalcMandelbrot(imageW, imageH, cellX, cellY, cellW, cellH,
			  setX, setY, setW, setH, &buffer[4]);


    /*
     * Update image
     */
    
    image = vdialogGetItemImage(_pictureDialogItem);
    vpixmapClear(vimageGetMap(image), 0);
    utilityAppendCellToImage(image, 
			     (vdialogGetItemW(_pictureDialogItem) - cellW)/2,
			     (vdialogGetItemH(_pictureDialogItem) - cellH)/2,
			     cellW, cellH, &buffer[4]);
    vdialogInvalItem(_pictureDialogItem, vwindowINVAL_OPAQUE);

    /*
     * Set up the return array
     * (the return array contains: [cellX, cellY, cellW, cellH, cellBuffer])
     */

    size = cellW*cellH + 4;
    buffer[0] = cellX;
    buffer[1] = cellY;
    buffer[2] = cellW; 
    buffer[3] = cellH;
    scrap = vserviceMakePrimitiveReturnScrap(primitive, session,
					     size, buffer);

    vmemFree(buffer);

    return scrap;
    
} /* _slaveHandlePrimitive */

static void _slaveNotifyButtonQuit(vbutton *button, vevent *event)
{
    vsessionEnd(_session);
    veventStopProcessing();
}

/******************************************************************************
 * Initialization functions
 *****************************************************************************/

/*
 * _slaveStartup sets up globals, service, etc.
 */

static void _slaveStartup(void)
{
    vservicePrimitive	*primitive;
    vresource            resource;
    vdialogItem         *dialogItem;
    vdialogItem         *newDialogItem;
    vbutton             *button;
    const vname         *name;
    const vchar         *sPref;

    /*
     * DialogItem class...
     */
    
    _dialogItemClass = vclassReproduce(vdialogGetDefaultItemClass());
    vclassSet(_dialogItemClass, vdialogDRAW_ITEM,
	      _slaveDrawPicture);

#if (vportWIN_MAC)
    vclassSet(_dialogItemClass, vdialogGET_ITEM_NATURAL_SEPARATION,
    	      _slaveGetMacNaturalSeparation);
#endif

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
    
    /*
     * Picture DialogItem...
     */
    
    name = vnameInternGlobalLiteral("Picture");
    newDialogItem = vdialogCreateItemOfClass(_dialogItemClass);
    dialogItem = vdialogFindItem(_dialog, name);
    vdialogCopyItem(dialogItem, newDialogItem);
    vdialogSetItemListItemAt(vdialogGetItemList(_dialog),
			     vdialogGetItemIndex(_dialog, dialogItem),
			     newDialogItem);
    vdialogDestroyItem(dialogItem);
    _pictureDialogItem = newDialogItem;
    
    /*
     * Quit Button...
     */
    
    name = vnameInternGlobalLiteral("Quit");
    button = (vbutton*)vdialogFindItem(_dialog, name);
    vbuttonSetNotify(button, _slaveNotifyButtonQuit);
    _quitButton = button;
    
    /*
     * create our service to export
     */
    
    _service = vserviceCreate();
    
    /*
     * add the attributes to the service
     */
    
    vserviceSetAttribute(_service, vname_Name, vdatatagGetTag(),
			 vnameInternGlobalLiteral("Mandelbrot Slave"));
    
    if ((sPref = vprefLoad(vsession_Transport)))
        if (vcharCompare(sPref, nameEmpty) != 0)
	    vserviceSetAttributeTag(_service, vsession_Transport,
				    vnameInternGlobal(sPref));
    if ((sPref = vprefLoad(vsession_Port)))
        if (vcharCompare(sPref, nameEmpty) != 0)
	    vserviceSetAttribute(_service, vsession_Port, vdatatagGetString(),
				 sPref);
    /*
     * Call the sub-init function that returns the name of this module
     * and then set that as an attribute that was also registered
     */
    
    vserviceSetAttributeScribe(_service, vname_Title, 
			       utilityGetMandelbrotName());
    
    /*
     * create the primative for the service
     */
    
    primitive = vserviceCreatePrimitive();
    vserviceSetPrimitiveSignature(primitive, utilityGetSignature());
    vserviceSetPrimitiveHandler(primitive, _slaveHandlePrimitive);
    vserviceAddPrimitiveOwned(_service, primitive);
    
    /*
     * now we are all ready, so let it be registered
     */
    
    vserviceEnable(_service);
    vdasservRegisterService(_service);

    /* 
     * Establishing session with service
     */
    
    _session = vsessionCreate();
    vsessionSetNotify(_session, _slaveNotifySession);
    vsessionSetService(_session, _service);
    vsessionSetAttributesFromScrap(_session, vdasservCreateAttributeScrap());
    vsessionBegin(_session);

} /* _slaveStartup */

/*
 * _slaveShutdown takes down global variables and dispose of services
 */

static void _slaveShutdown(void)
{
    /*
     * destroy the service
     */

    if (_service)
    {
	vdasservUnregisterService(_service);
	vserviceDestroy(_service);
	_service = NULL;
    }

    /*
     * destroy the dialog
     */

    if (_dialog)
    {
	vdialogDestroy(_dialog);
	_dialog = NULL;
    }

} /* _slaveShutdown */

/******************************************************************************
 * public functions
 *****************************************************************************/

/*
 * main is the basic main for slave
 * argc -> the number of arguments in the command line
 * argv -> the array of arguments in the command line
 *      <- exit status
 */

int main(int argc, char *argv[])
{
    /*
     * Init some prefs that we interested in
     */
    nameEmpty = vnameInternGlobalLiteral(" ");
    vprefStore(vsession_Transport, nameEmpty);
    vprefStore(vsession_Port, nameEmpty);

    vstartup(argc, argv);
    
    vcommRegisterAllDrivers();
    /*
     * set up our globals, service, etc.
     */
    
    _slaveStartup();
    
    /*
     * Opens up slave dialog
     */

    vdialogOpen(_dialog);

    /*
     * Let's do some work...
     */
    
    veventProcess();
    
    /*
     * cleanup our globals, service, etc.
     */
    
    _slaveShutdown();
    
    exit(EXIT_SUCCESS);
    return EXIT_FAILURE;
}


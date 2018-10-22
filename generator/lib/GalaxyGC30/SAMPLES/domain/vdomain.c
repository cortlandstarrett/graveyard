/* $Id: vdomain.c,v 1.8 1997/10/21 18:05:45 gregt Exp $
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
 * copyright notice in the in the form of "Copyright 1992 Visix Software Inc.,
 * 11440 Commerce Park Drive, Reston, VA  22091. All Rights Reserved" appears
 * in all copies, (ii) both the copyright notice and this permission notice
 * appear in supporting documentation and (iii) you are a valid licensee of
 * Galaxy Application Environment.
 */

/* Galaxy headers */
#include <vport.h>

#ifndef  vtimeINCLUDED
#include vtimeHEADER
#endif

#ifndef  vstdlibINCLUDED
#include vstdlibHEADER
#endif

#ifndef  vexINCLUDED
#include vexHEADER
#endif

#ifndef  vmemINCLUDED
#include vmemHEADER
#endif

#ifndef  vpoolINCLUDED
#include vpoolHEADER
#endif

#ifndef  vrectINCLUDED
#include vrectHEADER
#endif

#ifndef  vmatrixINCLUDED
#include vmatrixHEADER
#endif

#ifndef  vcharINCLUDED
#include vcharHEADER
#endif

#ifndef  vnameINCLUDED
#include vnameHEADER
#endif

#ifndef  vkeyINCLUDED
#include vkeyHEADER
#endif

#ifndef  veventINCLUDED
#include veventHEADER
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

#ifndef  vcolorINCLUDED
#include vcolorHEADER
#endif

#ifndef  vimageINCLUDED
#include vimageHEADER
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

#ifndef  vapplicationINCLUDED
#include vapplicationHEADER
#endif

#ifndef  vdialogINCLUDED
#include vdialogHEADER
#endif

#ifndef  vmenubarINCLUDED
#include vmenubarHEADER
#endif

#ifndef  vcontrolINCLUDED
#include vcontrolHEADER
#endif

#ifndef  vsliderINCLUDED
#include vsliderHEADER
#endif

#ifndef  vbuttonINCLUDED
#include vbuttonHEADER
#endif

#ifndef  vtextitemINCLUDED
#include vtextitemHEADER
#endif

#ifndef  vdomainviewINCLUDED
#include vdomainviewHEADER
#endif

#ifndef  vdomainitemINCLUDED
#include vdomainitemHEADER
#endif


typedef struct
{
  vcolor	*color;
  int		 position;
  int		 imageIndex;
}
objectData;

vdomain				*demoDomain = NULL;
vdomainview			*demoDomainView = NULL;
vdomainitem			*demoDomainItem = NULL;
vdialog				*demoDialog = NULL;
vtextitemClass			*demoHookedTextClass = NULL;

vtextitem			*demoObjectCountText = NULL;
vcontrol			*demoHorizBarCheckBox = NULL;
vcontrol			*demoHorizScrollingCheckBox = NULL;
vcontrol			*demoVertBarCheckBox = NULL;
vcontrol			*demoVertScrollingCheckBox = NULL;
vcontrol			*demoGrabbingHandCheckBox = NULL;
vcontrol			*demoBorderCheckBox = NULL;
vcontrol			*demoLiveSelectionCheckBox = NULL;
vcontrol			*demoSingleSelectionCheckBox = NULL;
vcontrol			*demoSelectEnclosedCheckBox = NULL;
vcontrol			*demoSelectAutoScrollCheckBox = NULL;
vcontrol			*demoDragTypePopup = NULL;
vcontrol			*demoOutlineTypePopup = NULL;
vcontrol			*demoDrawTypePopup = NULL;
vcontrol			*demoSnapToGridCheckBox = NULL;
vtextitem			*demoScrollbarMarginText = NULL;
vtextitem			*demoScrollIncrementText = NULL;
vbutton				*demoCloseButton = NULL;
vcontrol			*demoRotateSlider = NULL;
vcontrol			*demoScaleSlider = NULL;

#define demoDRAG_TYPES	3
int			demoDragTypeValues[demoDRAG_TYPES]
  = { vdomainviewDRAG_AUTOSCROLL, vdomainviewDRAG_NORMAL,
      vdomainviewEXTERNAL_DRAG };

#define demoOUTLINE_TYPES	4
int			demoOutlineTypeValues[demoOUTLINE_TYPES]
  = { vdomainviewOUTLINE_ALL, vdomainviewOUTLINE_LIMITRECT,
      vdomainviewOUTLINE_TWO, vdomainviewOUTLINE_NONE };

enum	{demoDRAW_BOXES = 0, demoDRAW_IMAGES = 1, demoDRAW_TEXT = 2};

#define demoDRAW_TYPES		3
int			demoDrawTypeValues[demoDRAW_TYPES]
  = { demoDRAW_BOXES, demoDRAW_IMAGES, demoDRAW_TEXT};

vpool				*objectDataPool;
vimage			       **imageArray;
int				 imageArrayCount;
int				 drawType;

void demoLoad(void);
void demoDialogNotify(vdialog *dialog, vevent *event);
void demoResizeDialog(vdialog *dialog);
void demoUnload(void);
void demoOpen(void);
void demoClose(void);
void demoLoadImages(void);
void demoUnloadImages(void);

static void _demoAddObjects(long count);
static void _demoRemoveObjects(long count);
static void _demoDrawObject(vdomainview *view, vdomainObject *object,
			    vdrawcontext *context);
static void _demoDrawSelection(vdomainview *view, vdomainObject *object,
			       vdrawcontext *contextOrig);
static void _demoUpdateDomain(void);
static void _demoNotifyCloseButton(vbutton *button, vevent *event);
static void _demoNotifyItem(vdialogItem *item, vevent *event);
static int _demoHookText(vtextitem *item, vevent *event);


/**********
 * main:
 *
 **********/
int main
  (int				argc,
   char				**argv)
{

  vprefSetArgs(argc, argv);
  vapplicationStartup();
  vwindowStartup();
  vbuttonStartup();
  vcontrolStartup();
  vdialogStartup();
  vdomainitemStartup();
  vmenuStartup();
  vmenubarStartup();
  vsliderStartup();
  vtextitemStartup();

  srand(time((time_t *)NULL));
  objectDataPool = vpoolCreate(sizeof(objectData));

  demoLoadImages();
  demoLoad();
  demoOpen();

  /* Process events until the window is closed */

  veventProcess();

  demoUnload();
  demoUnloadImages();
  vpoolDestroy(objectDataPool);

  exit( EXIT_SUCCESS );
  return EXIT_FAILURE;
}  /**  main()  **/


/**********
 * demoLoad:
 *
 **********/
void demoLoad
  (void)
{
  register int		i, itemCount;
  vdialogItem		*item;	
  vresource		resource;
  vdomainGrid		grid;

  demoHookedTextClass = vclassReproduce(vtextitemGetDefaultClass());
  vclassSetNameScribed(demoHookedTextClass,
		       vcharScribeLiteral("domaindemoHookedTextClass"));

  vclassSet(demoHookedTextClass, vdialogHANDLE_ITEM_KEY_DOWN, _demoHookText);

  resource = vresourceGet(vapplicationGetResources(vapplicationGetCurrent()),
			  vname_Dialog);

  demoDialog = vdialogLoad(resource);
  vdialogSetNotify(demoDialog, demoDialogNotify);

  demoDomainItem = (vdomainitem *) vdialogFindItem(demoDialog, vname_Domain);
  vdialogSetItemFocusable(vdomainitemGetItem(demoDomainItem), TRUE);
							 
  demoDomain = vdomainitemGetDomain(demoDomainItem);
  vdomainResize(demoDomain, 1000, 1000); 
  vdomainSetOrientation(demoDomain, vdomainORIENT_BOTTOM_LEFT);
  grid.xSpacing = 20;
  grid.ySpacing = 20;
  grid.xSkew = 0;
  grid.ySkew = 0;
  vdomainSetGrid(demoDomain, &grid);

  demoDomainView = vdomainitemGetView(demoDomainItem);
  vdomainviewSetTrackMode(demoDomainView, 
			  vdomainviewTRACK_SELECT | vdomainviewTRACK_DRAG);
  vdomainviewSetDrawObjectWithProc(demoDomainView, _demoDrawObject);
  vdomainviewSetDrawSelectionWithProc(demoDomainView, _demoDrawSelection);

  itemCount = vdialogGetItemCount(demoDialog);
  for (i = 0; i < itemCount; i++)
    {
      item = vdialogGetItemAt(demoDialog, i);
      vdialogSetItemNotify(item, _demoNotifyItem);
    }

  demoObjectCountText = (vtextitem *)
    vdialogFindItem(demoDialog, vnameInternGlobalLiteral("ObjectCount"));
  demoHorizBarCheckBox = (vcontrol *)
    vdialogFindItem(demoDialog, vnameInternGlobalLiteral("HorizBar"));
  demoHorizScrollingCheckBox = (vcontrol *)
    vdialogFindItem(demoDialog, vnameInternGlobalLiteral("HorizScrolling"));
  demoVertBarCheckBox = (vcontrol *)
    vdialogFindItem(demoDialog, vnameInternGlobalLiteral("VertBar"));
  demoVertScrollingCheckBox = (vcontrol *)
    vdialogFindItem(demoDialog, vnameInternGlobalLiteral("VertScrolling"));
  demoGrabbingHandCheckBox = (vcontrol *)
    vdialogFindItem(demoDialog, vnameInternGlobalLiteral("GrabbingHand"));
  demoBorderCheckBox = (vcontrol *)
    vdialogFindItem(demoDialog, vnameInternGlobalLiteral("Border"));
  demoLiveSelectionCheckBox = (vcontrol *)
    vdialogFindItem(demoDialog, vnameInternGlobalLiteral("LiveSelection"));
  demoSingleSelectionCheckBox = (vcontrol *)
    vdialogFindItem(demoDialog, vnameInternGlobalLiteral("SingleSelection"));
  demoSelectEnclosedCheckBox = (vcontrol *)
    vdialogFindItem(demoDialog, vnameInternGlobalLiteral("SelectEnclosed"));
  demoSelectAutoScrollCheckBox = (vcontrol *)
    vdialogFindItem(demoDialog, vnameInternGlobalLiteral("AutoScroll"));
  demoDragTypePopup = (vcontrol *)
    vdialogFindItem(demoDialog, vnameInternGlobalLiteral("DragType"));
  demoOutlineTypePopup = (vcontrol *)
    vdialogFindItem(demoDialog, vnameInternGlobalLiteral("OutlineType"));
  demoDrawTypePopup = (vcontrol *)
    vdialogFindItem(demoDialog, vnameInternGlobalLiteral("drawType"));
  demoSnapToGridCheckBox = (vcontrol *)
    vdialogFindItem(demoDialog, vnameInternGlobalLiteral("SnapToGrid"));
  demoScrollbarMarginText = (vtextitem *)
    vdialogFindItem(demoDialog, vnameInternGlobalLiteral("ScrollbarMargin"));
  demoScrollIncrementText = (vtextitem *)
    vdialogFindItem(demoDialog, vnameInternGlobalLiteral("ScrollIncrement"));
  demoCloseButton = (vbutton *)
    vdialogFindItem(demoDialog, vnameInternGlobalLiteral("Close"));
  demoRotateSlider = (vcontrol *)
    vdialogFindItem(demoDialog, vnameInternGlobalLiteral("Rotate"));
  demoScaleSlider = (vcontrol *)
    vdialogFindItem(demoDialog, vnameInternGlobalLiteral("Scale"));

  vbuttonSetNotify(demoCloseButton, _demoNotifyCloseButton);

  vdialogSetAbandon(demoDialog, vbuttonGetItem(demoCloseButton));
  vdialogResize(demoDialog, 600, 440);
  vdialogMove(demoDialog, 20, 20);

  _demoUpdateDomain();

}  /**  demoLoad()  **/

/**********
 * demoLoadImages:
 *
 **********/
void demoLoadImages
  (void)
{
  register int		component;
  vresource		resource, imageRes;
  const vname		*tag;

  resource = vresourceGet(vapplicationGetResources(vapplicationGetCurrent()),
			  vnameInternGlobalLiteral("Images"));

  imageArrayCount = vresourceCountComponents(resource);
  imageArray = (vimage **) vmemAlloc(sizeof (vimage *) * imageArrayCount);
  
  for (component = 0; component < imageArrayCount; component++)
  {
    imageRes = vresourceGetNthComponent(resource, component, &tag);
    imageArray[component] = vimageLoad(imageRes);
  }
}

/**********
 * demoUnloadImages:
 *
 **********/
void demoUnloadImages
  (void)
{
  register int		component;

  for (component = 0; component < imageArrayCount; component++)
  {
    vimageDestroy(imageArray[component]);
  }
  vmemFree(imageArray);
}

/**********
 * demoDialogNotify:
 *
 **********/
void demoDialogNotify
  (vdialog			*dialog,
   vevent			*event)
{

  if (veventGetType(event) == veventWINDOW_STATE && veventIsClose(event))
    {
      veventStopProcessing();
    }

  if (veventGetType(event) == veventWINDOW_CONFIGURE)
    {
      _demoUpdateDomain();
    }

}  /**  demoDialogNotify()  **/


/**********
 * demoUnload:
 *
 **********/
void demoUnload
  (void)
{

  if (demoDialog == NULL)
    return;

  _demoRemoveObjects(vdomainObjectCount(demoDomain));

  vdialogDestroy(demoDialog);
  demoDialog = NULL;

  vclassDestroy(demoHookedTextClass);
  demoHookedTextClass = NULL;

}  /**  demoUnload()  **/


/**********
 * demoOpen:
 *
 **********/
void demoOpen
  (void)
{
  int		w, h;

  if (demoDialog == NULL)
    demoLoad();

  vdialogCalcMinSize(demoDialog, &w, &h);
  vdialogResize(demoDialog, w, h);
  vwindowPlace(vdialogGetWindow(demoDialog), vwindowGetRoot(),
	       vrectPLACE_INSET | vrectPLACE_LEFT, vrectPLACE_CENTER);
  vdialogOpen(demoDialog);

}  /**  demoOpen()  **/


/**********
 * demoClose:
 *
 **********/
void demoClose
  (void)
{

  if (demoDialog == NULL)
    return;

  vdialogClose(demoDialog);

}  /**  demoClose()  **/


/**********
 * _demoAddObjects:
 *
 **********/
static void _demoAddObjects
  (long					count)
{
  register long				i;
  vdomainObjectSet			*objectSet;
  vrect					*bounds;
  vrect					rect;
  vdomainObject				*object;
  vcolorSpec				 spec;
  vcolor				*color;
  vimage				*image;
  objectData				*data;
  int					 imageIndex;

  if (demoDialog == NULL)
    demoLoad();

  objectSet = vdomainCreateObjectSet(NULL);

  vcolorInitSpec(&spec);

  for (i = 0; i < count; i++)
    {
      imageIndex = (i % imageArrayCount);
      image  = imageArray[imageIndex];
      bounds = vdomainGetBounds(demoDomain);

      switch (drawType)
      {
        case demoDRAW_BOXES:
	  vrectSet(rand() % (bounds->w - 50),
		   rand() % (bounds->h - 50),
		   rand() % 100 + 2, rand() % 100 + 2, &rect);
	  break;

        case demoDRAW_IMAGES:
	  vrectSet(rand() % (bounds->w - vimageGetWidth(image) - 4),
		   rand() % (bounds->h - vimageGetHeight(image) - 4),
		   vimageGetWidth(image) + 4,
		   vimageGetHeight(image) + 4, &rect);
	  break;

        case demoDRAW_TEXT:
	  vrectSet(rand() % (bounds->w - 50),
		   rand() % (bounds->h - 50),
		   rand() % 100 + 2, rand() % 100 + 2, &rect);
	  break;
      }

      object = vdomainAddObject(demoDomain);
      vdomainSetObjectBounds(demoDomain, vdomainObjectToSet(object), &rect);
      vcolorSetSpecRGB(&spec, 
		       rand() % vcolorCOMPONENT_MAX,
		       rand() % vcolorCOMPONENT_MAX,
		       rand() % vcolorCOMPONENT_MAX);
      color = vcolorInternSpec(&spec);

      data = vpoolAlloc(objectDataPool);
      data->color = color;
      data->position = i;
      data->imageIndex = imageIndex;

      vdomainSetObjectData(demoDomain, vdomainObjectToSet(object), data);

      vdomainAddToObjectSet(&objectSet, object);
    }

  vcolorDestroySpec(&spec);

  vdomainShowObjects(demoDomain, objectSet);

  vdomainDestroyObjectSet(objectSet);

}  /**  _demoAddObjects()  **/


/**********
 * _demoRemoveObjects:
 *
 **********/
static void _demoRemoveObjects
  (long					count)
{
  register long				i;
  vdomainObjectSet			*objectSet;
  vdomainObject				*object;
  objectData				*data;

  objectSet = vdomainCreateObjectSet(NULL);

  object = vdomainTopObject(demoDomain);

  for (i = 0; i < count; i++)
    {
      data = (objectData *) vdomainGetObjectData(demoDomain, object);
      vcolorRelease(data->color);
      vpoolFree(objectDataPool, data);
      vdomainAddToObjectSet(&objectSet, object);

      object = vdomainNextObjectBehind(object);
    }

  vdomainRemoveObjects(demoDomain, objectSet);

  vdomainDestroyObjectSet(objectSet);

}  /**  _demoRemoveObjects()  **/


/**********
 * _demoDrawObject:
 *
 * This is the object drawing routine.   Our objects are boxes or images.
 *
 **********/
static void _demoDrawObject
  (vdomainview				*view,
   vdomainObject			*object,
   vdrawcontext				*context)
{
  const vrect				*bounds;
  vcolor				*oldColor;
  objectData				*data;
  vimage				*image;

  data = (objectData *) vdomainGetObjectData(demoDomain, object);
  bounds = vdomainGetObjectBounds(demoDomain, object);

  switch (drawType)
  {
    case demoDRAW_BOXES:
      oldColor = vdrawpenGetColor(vdrawcontextGetPen(context));
      vdrawpenSetColor(vdrawcontextGetPen(context), data->color);
      vdrawcontextFillRectangles(context, bounds, 1);
      vdrawpenSetColor(vdrawcontextGetPen(context), oldColor);
      break;

    case demoDRAW_IMAGES:
      image = imageArray[data->imageIndex];
      vdrawcontextDrawImagePoint(context, image, bounds->x + 2, bounds->y + 2);
      break;

    case demoDRAW_TEXT:
      vdrawcontextDrawStringCenterScribed(context,
					  vnumScribeInt(data->position),
					  bounds);
      break;
  }
}  /**  _demoDrawObject()  **/


/**********
 * _demoDrawSelection:
 *
 * This is the selection drawing routine.  For boxes the selection indication
 * is inverting diagonal lines from corner to corner. For images, the selection
 * indicator is a black rectangle around the image.
 *
 **********/
static void _demoDrawSelection
  (vdomainview				*view,
   vdomainObject			*object,
   vdrawcontext				*contextOrig)
{
  vdrawcontext				*context;
  const vrect				*bounds;

  context = vdrawcontextClone(contextOrig);
  vdrawpenSetDrawingFunction(vdrawcontextGetPen(context), vdrawFUNC_INVERT);
  bounds = vdomainGetObjectBounds(demoDomain, object);
  vdrawcontextClipRectangles(context, bounds, 1);
  vdrawpenSetLineWidth(vdrawcontextGetPen(context), 1);

  switch (drawType)
  {
    case demoDRAW_BOXES:
      vdrawcontextSetCurrentPoint(context, bounds->x, bounds->y + 1);
      vdrawcontextDrawLineTo(context, bounds->x + bounds->w,
			     bounds->y + bounds->h + 1);
      vdrawcontextSetCurrentPoint(context, bounds->x, bounds->y + bounds->h);
      vdrawcontextDrawLineTo(context, bounds->x + bounds->w, bounds->y);
      break;

    case demoDRAW_IMAGES:
      vdrawpenSetLineWidth(vdrawcontextGetPen(context), 2);
      /** |              | **/
      /** V FALL THROUGH V **/

    case demoDRAW_TEXT:
      vdrawcontextDrawRectanglesInside(context, bounds, 1);
      break;
  }

  vdrawcontextDestroy(context);
}  /**  _demoDrawSelection()  **/


/**********
 * _demoUpdateDomain:
 *
 **********/
static void _demoUpdateDomain
  (void)
{
  int				oldCount, newCount, newDrawType;
  int				newMargin;
  vbool				doRegenerateObjects;
  vmatrix			matrix;
  double			scaleX, scaleY;

  vexWITH_HANDLING {
    newMargin = vtextitemGetTextAsInt(demoScrollbarMarginText);
  } vexON_EXCEPTION {
    newMargin = vdomainviewGetScrollbarMargin(demoDomainView);
  } vexEND_HANDLING;

  if (newMargin < -1)
    newMargin = vdomainviewGetScrollbarMargin(demoDomainView);

  vdomainviewSetHorzBar(demoDomainView,
			vcontrolGetValue(demoHorizBarCheckBox));
  vdomainviewSetHorzLocked(demoDomainView,
			  !vcontrolGetValue(demoHorizScrollingCheckBox));
  vdomainviewSetVertBar(demoDomainView,
			vcontrolGetValue(demoVertBarCheckBox));
  vdomainviewSetVertLocked(demoDomainView,
			   !vcontrolGetValue(demoVertScrollingCheckBox));
  vdomainviewSetGrabbingHand(demoDomainView,
			     vcontrolGetValue(demoGrabbingHandCheckBox));
  vdialogSetItemBorder(vdomainviewGetItem(demoDomainView),
		       vcontrolGetValue(demoBorderCheckBox));
  vdomainviewSetLiveSelection(demoDomainView,
			      vcontrolGetValue(demoLiveSelectionCheckBox));
  vdomainviewSetSingleSelection(demoDomainView,
				vcontrolGetValue(demoSingleSelectionCheckBox));
  vdomainviewSetSelectEnclosed(demoDomainView,
			       vcontrolGetValue(demoSelectEnclosedCheckBox));
  vdomainviewSetAutoScroll(demoDomainView,
			   vcontrolGetValue(demoSelectAutoScrollCheckBox));
  vdomainviewSetDragMethod(demoDomainView,
			   demoDragTypeValues
			      [vcontrolGetValue(demoDragTypePopup)]);
  vdomainviewSetDragOutline(demoDomainView,
			    demoOutlineTypeValues
			       [vcontrolGetValue(demoOutlineTypePopup)]);
  vdomainviewSetDragSnapToGrid(demoDomainView,
			       vcontrolGetValue(demoSnapToGridCheckBox));
  vdomainviewSetScrollbarMargin(demoDomainView, newMargin);

  vexWITH_HANDLING {
    newCount = vtextitemGetTextAsInt(demoScrollIncrementText);
    if (newCount >= 0)
      vdomainviewSetScrollIncrement(demoDomainView, newCount);
  } vexON_EXCEPTION {
  } vexEND_HANDLING;

  newDrawType = demoDrawTypeValues[vcontrolGetValue(demoDrawTypePopup)];

  doRegenerateObjects = FALSE;
  if (newDrawType != drawType)
    {
      doRegenerateObjects = TRUE;
      drawType = newDrawType;
    }

  scaleX  = vcontrolGetValue(demoScaleSlider) / 100.0;
  scaleY  = scaleX;
  matrix = *vmatrixIdent();
  vmatrixScale(&matrix, scaleX, scaleY, &matrix);
  vmatrixTranslate(&matrix, 500, 500, &matrix);
  vmatrixRotate(&matrix, vcontrolGetValue(demoRotateSlider), &matrix);
  vmatrixTranslate(&matrix, -500, -500, &matrix);
  vdomainviewSetMatrix(demoDomainView, &matrix);

  oldCount = vdomainObjectCount(demoDomain);
  vexWITH_HANDLING {
    newCount = vtextitemGetTextAsInt(demoObjectCountText);
  } vexON_EXCEPTION {
    newCount = oldCount;
  } vexEND_HANDLING;

  if (newCount < 0)
    newCount = oldCount;

  if (doRegenerateObjects)
    {
      _demoRemoveObjects(oldCount);
      _demoAddObjects(newCount);
    }
  else
  {
    if (oldCount < newCount)
      _demoAddObjects(newCount - oldCount);
    else if (newCount < oldCount)
      _demoRemoveObjects(oldCount - newCount);
  }
}  /**  _demoUpdateDomain()  **/


/**********
 * _demoNotifyCloseButton:
 *
 **********/
static void _demoNotifyCloseButton
  (vbutton                        *button,
   vevent                         *event)
{

  demoClose();
  veventStopProcessing();

}  /**  _demoNotifyCloseButton()  **/


/**********
 * _demoNotifyItem:
 *
 **********/
static void _demoNotifyItem
  (vdialogItem			*item,
   vevent			*event)
{
  
  if (item != (vdialogItem *) demoDomainView)
    _demoUpdateDomain();

}  /**  _demoNotifyItem()  **/


/**********
 * _demoHookText:
 *
 **********/
static int _demoHookText
  (vtextitem			*item,
   vevent			*event)
{
  
  if (vkeyGetStrokeKey(veventGetKeyStroke(event)) == vkeyRETURN)
    {
      _demoUpdateDomain();
      return(TRUE);
    }

  return(vclassSendSuper(demoHookedTextClass,
			 vdialogHANDLE_ITEM_KEY_DOWN, (item, event)));
}  /**  _demoHookText()  **/

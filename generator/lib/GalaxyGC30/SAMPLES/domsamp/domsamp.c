/* $Id: domsamp.c,v 1.16 1995/09/29 19:23:55 gregt Exp $ */
/* domsamp
 *
 * yet more sample code showing more neato domain things.
 */

#include <vport.h>

#ifndef vstdlibINCLUDED
#include vstdlibHEADER
#endif

#ifndef vdebugINCLUDED
#include vdebugHEADER
#endif

#ifndef vexINCLUDED
#include vexHEADER
#endif

#ifndef vmemINCLUDED
#include vmemHEADER
#endif

#ifndef vrectINCLUDED
#include vrectHEADER
#endif

#ifndef vpointINCLUDED
#include vpointHEADER
#endif

#ifndef vcharINCLUDED
#include vcharHEADER
#endif

#ifndef vstrINCLUDED
#include vstrHEADER
#endif

#ifndef vnameINCLUDED
#include vnameHEADER
#endif

#ifndef vdictINCLUDED
#include vdictHEADER
#endif

#ifndef veventINCLUDED
#include veventHEADER
#endif

#ifndef vresourceINCLUDED
#include vresourceHEADER
#endif

#ifndef vnumINCLUDED
#include vnumHEADER
#endif

#ifndef vprefINCLUDED
#include vprefHEADER
#endif

#ifndef vclassINCLUDED
#include vclassHEADER
#endif

#ifndef vobjectINCLUDED
#include vobjectHEADER
#endif

#ifndef vcommandINCLUDED
#include vcommandHEADER
#endif

#ifndef vcolorINCLUDED
#include vcolorHEADER
#endif

#ifndef vfontINCLUDED
#include vfontHEADER
#endif

#ifndef vtextINCLUDED
#include vtextHEADER
#endif

#ifndef vdomainINCLUDED
#include vdomainHEADER
#endif

#ifndef vdrawINCLUDED
#include vdrawHEADER
#endif

#ifndef vwindowINCLUDED
#include vwindowHEADER
#endif

#ifndef vmenuINCLUDED
#include vmenuHEADER
#endif

#ifndef vapplicationINCLUDED
#include vapplicationHEADER
#endif

#ifndef vdialogINCLUDED
#include vdialogHEADER
#endif

#ifndef vmenubarINCLUDED
#include vmenubarHEADER
#endif

#ifndef vcontrolINCLUDED
#include vcontrolHEADER
#endif

#ifndef vbuttonINCLUDED
#include vbuttonHEADER
#endif

#ifndef vcontainerINCLUDED
#include vcontainerHEADER
#endif

#ifndef vtextviewINCLUDED
#include vtextviewHEADER
#endif

#ifndef vtextitemINCLUDED
#include vtextitemHEADER
#endif

#ifndef vdomainviewINCLUDED
#include vdomainviewHEADER
#endif

#ifndef vdomainitemINCLUDED
#include vdomainitemHEADER
#endif

#ifndef vconfirmINCLUDED
#include vconfirmHEADER
#endif

#ifndef vtextrulerINCLUDED
#include vtextrulerHEADER
#endif

#if (vportPEEK)
#ifndef  peekINCLUDED
#include <peek.h>
#endif
#endif

#include "mydview.h"
#include "domres.h"
#include "domnames.h"
#include "domsamp.h"
#include "prefs.h"

#if (vdebugDEBUG)
static const char _domsampTAG[] = "domsamp";
#define vdebugTAG _domsampTAG
#endif

enum {
  comOPEN,
  comSAVE,
  comPREFERENCES,
  comADD_OBJECTS,
  comREMOVE_OBJECTS,
  comCONNECT_OBJECTS,
  comDISCONNECT_OBJECTS,
  comHIDE_OBJECTS,
  comSHOW_ALL_OBJECTS,
  comSCROLL_TO_SELECTED,
  comMAKE_UNSELECTABLE,
  comTOGGLE_VIRTUAL,
  comTOGGLE_LONG,
  comTOGGLE_TOP_LEFT,
  comEDIT_GRID,
  comVIEW_COORDS,
  comPRINT_DOMAIN,
  comDOMAIN_INSTALLED,
  comTRACK_SELECT,
  comTRACK_DRAG,
  comTRACK_AUTOSCROLL,
  comLIVE_SELECTION,
  comSELECT_ENCLOSED,
  comSINGLE_SELECTION,
  comGRABBING_HAND,
  comDRAG_PROHIBITED,
  comOFFSCREEN_DRAWING,
  comEDIT_MATRIX,
  comOUTLINE_ALL,
  comOUTLINE_TWO,
  comOUTLINE_LIMIT_RECT,
  comOUTLINE_NONE,
  comNORMAL_DRAG,
  comAUTOSCROLL_DRAG,
  comEXTERNAL_DRAG,
  comSNAP_OFF,
  comSNAP_NO_ALIGN,
  comSNAP_ALIGN_ONE,
  comSNAP_ALIGN_LIMIT,
  comSMART_SCROLLBARS,
  comHORIZONTAL_BAR,
  comVERTICAL_BAR,
  comSHOW_GRID,
  comDRAG_ON_UNSELECTABLES,
  comCOUNT
};

static const vcommandSelectorTemplate comTemplate[] = {
  {"Open", comOPEN},
  {"Save", comSAVE},
  {"Preferences", comPREFERENCES},
  {"AddObjects", comADD_OBJECTS},
  {"RemoveObjects", comREMOVE_OBJECTS},
  {"ConnectObjects", comCONNECT_OBJECTS},
  {"DisconnectObjects", comDISCONNECT_OBJECTS},
  {"HideObjects", comHIDE_OBJECTS},
  {"ShowAllObjects", comSHOW_ALL_OBJECTS},
  {"ScrollToSelected", comSCROLL_TO_SELECTED},
  {"MakeUnselectable", comMAKE_UNSELECTABLE},
  {"ToggleVirtual", comTOGGLE_VIRTUAL},
  {"ToggleLong", comTOGGLE_LONG},
  {"ToggleTopLeft", comTOGGLE_TOP_LEFT},
  {"EditGrid", comEDIT_GRID},
  {"ViewCoords", comVIEW_COORDS},
  {"PrintDomain", comPRINT_DOMAIN},
  {"DomainInstalled", comDOMAIN_INSTALLED},
  {"TrackSelect", comTRACK_SELECT},
  {"TrackDrag", comTRACK_DRAG},
  {"TrackAutoScroll", comTRACK_AUTOSCROLL},
  {"LiveSelection", comLIVE_SELECTION},
  {"SelectEnclosed", comSELECT_ENCLOSED},
  {"SingleSelection", comSINGLE_SELECTION},
  {"GrabbingHand", comGRABBING_HAND},
  {"DragProhibited", comDRAG_PROHIBITED},
  {"OffscreenDrawing", comOFFSCREEN_DRAWING},
  {"EditMatrix", comEDIT_MATRIX},
  {"OutlineAll", comOUTLINE_ALL},
  {"OutlineTwo", comOUTLINE_TWO},
  {"OutlineLimitRect", comOUTLINE_LIMIT_RECT},
  {"OutlineNone", comOUTLINE_NONE},
  {"NormalDrag", comNORMAL_DRAG},
  {"AutoScrollDrag", comAUTOSCROLL_DRAG},
  {"ExternalDrag", comEXTERNAL_DRAG},
  {"SnapOff", comSNAP_OFF},
  {"SnapNoAlign", comSNAP_NO_ALIGN},
  {"SnapAlignOne", comSNAP_ALIGN_ONE},
  {"SnapAlignLimit", comSNAP_ALIGN_LIMIT},
  {"SmartScrollbars", comSMART_SCROLLBARS},
  {"HorizontalBar", comHORIZONTAL_BAR},
  {"VerticalBar", comVERTICAL_BAR},
  {"ShowGrid", comSHOW_GRID},
  {"DragOnUnselectables", comDRAG_ON_UNSELECTABLES}
};

vpointLong objectSizes[objCOUNT] = {
  {30, 30},
  {30, 30},
  {30, 30},
  {0, 0}
};

/*****************************************************************************
  some whacky stuff for the boxitem subclass...
   ***************************************************************************/

static vwindowClass *_coordSysWindowClass = NULL;

void coordSysWindowUpdate(vwindow *win)
{
  if (vwindowIsOpen(win))
    vwindowInval(win, 0);
}

static void _coordSysChangedParentAttribute(register vwindow *window, 
					    const vname *attr, vdict *context)
{
#if vdebugDEBUG
  if (attr==NULL || context==NULL)
    vexGenerateArgNull();
#endif

  vdebugTraceEnter(_coordSysChangedParentAttribute);

  if (attr == domnames_DomainCoords)
    vwindowInval(window, 0);
  else
    vclassSendSuper(_coordSysWindowClass, vobjectCHANGED_PARENT_ATTRIBUTE,
		    (window, attr, context));

  vdebugTraceLeave();
}

static void _coordSysWindowDraw(vwindow *win)
{
  vdomainview *dview;
  double sx, sy;
  const vrect *winBounds;
  vrectLong *viewable;
  vrectFloat viewArea;

  vclassSendSuper(_coordSysWindowClass, vwindowDRAW, (win));

  dview = myDomainViewGetView(appDataGetMview(coordSysGetAppData(win)));
  if (vdomainviewGetDomain(dview) == NULL)
    return;

  viewable = vdomainviewGetViewableArea(dview);
  winBounds = vwindowGetRect(win);
  sx = ((double) winBounds->w) / ((double) viewable->w);
  sy = ((double) winBounds->h) / ((double) viewable->h);
  vdrawGSave();
  vdrawSetColor(vcolorGetBlack());
  vdrawFScale(sx, sy);
  vdrawFTranslate(-viewable->x, -viewable->y);
  viewArea.x = viewable->x + vdomainviewGetScrollTranslation(dview)->x;
  viewArea.y = viewable->y + vdomainviewGetScrollTranslation(dview)->y;
  viewArea.w = vdomainviewGetDomainRect(dview)->w;
  viewArea.h = vdomainviewGetDomainRect(dview)->h;
  vdrawFRectsFill(&viewArea, 1);
  vdrawGRestore();
}

static int _coordSysWindowHandleButtonUp(vwindow *win, vevent *event)
{
  vclassSendSuper(_coordSysWindowClass, vwindowHANDLE_BUTTON_UP,
		  (win, event));
  vwindowClose(win);
  return TRUE;
}

vwindowClass *coordSysWindowGetDefaultClass(void)
{
  if (_coordSysWindowClass == NULL) {
    register vwindowClass *clas;

    clas = vclassReproduce(vwindowGetDefaultClass());
    vclassSetNameScribed(clas, vcharScribeLiteral("coordSysWindow"));
    vclassSet(clas, vobjectCHANGED_PARENT_ATTRIBUTE, _coordSysChangedParentAttribute);
    vclassSet(clas, vwindowDRAW,		_coordSysWindowDraw);
    vclassSet(clas, vwindowHANDLE_BUTTON_UP,	_coordSysWindowHandleButtonUp);
    _coordSysWindowClass = clas;
  }
  return _coordSysWindowClass;
}


/*****************************************************************************
  various functions at the app level...
   ***************************************************************************/

static void addObjects(vconfirm *addItems)
{
  vdebugTraceEnter(addObjects);

  if (!vconfirmIsOpen(addItems))
    vconfirmOpen(addItems);
  else
    vwindowRaise(vconfirmGetWindow(addItems));
  
  vdebugTraceLeave();
}

static void removeObjects(vdialog *mainDialog)
{
  vdomainview *dview;
  vdomain *dom;
  vdomainObjectSet *set;

  vdebugTraceEnter(removeObjects);

  dview =
    myDomainViewGetView(appDataGetMview(mainDialogGetAppData(mainDialog)));
  dom = vdomainviewGetDomain(dview);
  set = vdomainGetObjectSet(dom, vdomainviewGetSelection(dview),
			    vdomainSELECTED, NULL);
  vdomainRemoveObjects(dom, set);
  vdomainDestroyObjectSet(set);

  vdebugTraceLeave();
}

static void connectObjects(vdialog *mainDialog)
{
  vdomainview *dview;
  vdomain *dom;
  vdomainObjectSet *set;
  vdomainObjectSetIterator iter;
  vdomainObject *firstObj;
  vdomainObject *conObj;

  vdebugTraceEnter(connectObjects);

  dview =
    myDomainViewGetView(appDataGetMview(mainDialogGetAppData(mainDialog)));
  dom = vdomainviewGetDomain(dview);
  set = vdomainGetObjectSet(dom, vdomainviewGetSelection(dview),
			    vdomainSELECTED, NULL);
  vdomainInitObjectSetIterator(&iter, set);
  if (vdomainNextObjectSetIterator(&iter)) {
    firstObj = vdomainGetObjectSetIteratorObject(&iter);
    while (vdomainNextObjectSetIterator(&iter)) {
      conObj = vdomainGetObjectSetIteratorObject(&iter);
      vdomainConnectObjects(dom, firstObj, conObj);
    }
  }
  vdomainDestroyObjectSetIterator(&iter);
  vdomainDestroyObjectSet(set);

  vdebugTraceLeave();
}

static void disconnectObjects(vdialog *mainDialog)
{
  vdomainview *dview;
  vdomain *dom;
  vdomainObjectSet *set;

  vdebugTraceEnter(disconnectObjects);

  dview =
    myDomainViewGetView(appDataGetMview(mainDialogGetAppData(mainDialog)));
  dom = vdomainviewGetDomain(dview);
  set = vdomainGetObjectSet(dom, vdomainviewGetSelection(dview),
			    vdomainSELECTED, NULL);
  vdomainDisconnectObjects(dom, set);
  vdomainDestroyObjectSet(set);

  vdebugTraceLeave();
}

static void hideObjects(vdialog *mainDialog)
{
  vdomainview *dview;
  vdomain *dom;
  vdomainObjectSet *set;

  vdebugTraceEnter(hideObjects);

  dview =
    myDomainViewGetView(appDataGetMview(mainDialogGetAppData(mainDialog)));
  dom = vdomainviewGetDomain(dview);
  set = vdomainGetObjectSet(dom, vdomainviewGetSelection(dview),
			    vdomainSELECTED, NULL);
  vdomainHideObjects(dom, set);
  vdomainDestroyObjectSet(set);

  vdebugTraceLeave();
}

static void showAllObjects(vdialog *mainDialog)
{
  vdomainview *dview;
  vdomain *dom;
  vdomainObjectSet *set;

  vdebugTraceEnter(showAllObjects);

  dview =
    myDomainViewGetView(appDataGetMview(mainDialogGetAppData(mainDialog)));
  dom = vdomainviewGetDomain(dview);
  set = vdomainGetObjectSet(dom, 0, vdomainHIDDEN, NULL);
  vdomainShowObjects(dom, set);
  vdomainDestroyObjectSet(set);

  vdebugTraceLeave();
}

static void scrollToSelected(vdialog *mainDialog)
{
  vdomainview *dview;
  vdomainObjectSet *objSet;
  vdomainObjectSetIterator iterator;

  vdebugTraceEnter(scrollToSelected);

  dview =
    myDomainViewGetView(appDataGetMview(mainDialogGetAppData(mainDialog)));
  objSet = vdomainGetObjectSet(vdomainviewGetDomain(dview),
			       vdomainviewGetSelection(dview),
			       vdomainSELECTED, NULL);
  vdomainInitObjectSetIterator(&iterator, objSet);
  if (vdomainNextObjectSetIterator(&iterator))
    vdomainviewScrollToObject(dview,
			      vdomainGetObjectSetIteratorObject(&iterator),
			      5, 5, 5, 5, vTRUE, NULL, NULL);
  vdomainDestroyObjectSetIterator(&iterator);
  vdomainDestroyObjectSet(objSet);

  vdebugTraceLeave();
}

static void makeUnselectable(vdialog *mainDialog)
{
  vdomain		*dom;
  vdomainview		*dview;
  vdomainObjectSet	*objSet;

  vdebugTraceEnter(makeUnselectable);

  dview =
    myDomainViewGetView(appDataGetMview(mainDialogGetAppData(mainDialog)));
  dom = vdomainviewGetDomain(dview);
  objSet = vdomainGetObjectSet(dom, vdomainviewGetSelection(dview),
			       vdomainSELECTED, NULL);
  vdomainUnselectObjects(dom, vdomainviewGetSelection(dview), objSet);
  vdomainSetObjectUnselectable(dom, objSet, vTRUE);
  vdomainDestroyObjectSet(objSet);

  vdebugTraceLeave();
}

static void toggleLong(vdialog *mainDialog, vbool state)
{
  myDomainView *mview;

  vdebugTraceEnter(toggleLong);

  mview = appDataGetMview(mainDialogGetAppData(mainDialog));
  myDomainViewSetLong(mview, state);

  vdebugTraceLeave();
}

static void toggleVirtualBounds(vdialog *mainDialog, vbool state)
{
  myDomainView *mview;

  vdebugTraceEnter(toggleVirtualBounds);

  mview = appDataGetMview(mainDialogGetAppData(mainDialog));
  vdomainSetVirtualBounds(vdomainviewGetDomain(myDomainViewGetView(mview)),
			  state);
  myDomainViewRecalcBars(mview);

  vdebugTraceLeave();
}

static void toggleTopLeft(vdialog *mainDialog, vbool state)
{
  myDomainView *mview;

  vdebugTraceEnter(toggleTopLeft);

  mview = appDataGetMview(mainDialogGetAppData(mainDialog));
  vdomainSetOrientation(vdomainviewGetDomain(myDomainViewGetView(mview)),
			state ? vdomainORIENT_TOP_LEFT :
			vdomainORIENT_BOTTOM_LEFT);

  vdebugTraceLeave();
}

static void editGrid(vconfirm *conf)
{
  appData *data;
  vdomainview *dview;
  vtextitem *titem;
  vdomainGrid grid;

  vdebugTraceEnter(editGrid);

  data = editGridGetAppData(conf);
  dview = myDomainViewGetView(appDataGetMview(data));
  grid = *vdomainGetGrid(vdomainviewGetDomain(dview));

  titem = (vtextitem *) vdialogFindItem(vconfirmGetDialog(conf),
					domres_XSpacing);
  vtextitemSetTextScribed(titem, vnumScribeInt(grid.xSpacing));
  titem = (vtextitem *) vdialogFindItem(vconfirmGetDialog(conf),
					domres_YSpacing);
  vtextitemSetTextScribed(titem, vnumScribeInt(grid.ySpacing));
  titem = (vtextitem *) vdialogFindItem(vconfirmGetDialog(conf),
					domres_XSkew);
  vtextitemSetTextScribed(titem, vnumScribeInt(grid.xSkew));
  titem = (vtextitem *) vdialogFindItem(vconfirmGetDialog(conf),
					domres_YSkew);
  vtextitemSetTextScribed(titem, vnumScribeInt(grid.ySkew));

  if (!vconfirmIsOpen(conf))
    vconfirmOpen(conf);
  else
    vwindowRaise(vconfirmGetWindow(conf));

  vdebugTraceLeave();
}

static void domainInstalled(vdialog *mainDialog, vbool state)
{
  vdomainview *dview =
    myDomainViewGetView(appDataGetMview(mainDialogGetAppData(mainDialog)));
  static vdomain *savedDomain;

  if (!state) {
    savedDomain = vdomainviewGetDomain(dview);
    vdomainviewSetDomain(dview, NULL);
    vwindowPropagateChange(vdialogGetWindow(mainDialog), vname_State,
			   domres_DomainMenu, vname_Disabled);
    vwindowPropagateChange(vdialogGetWindow(mainDialog), vname_State,
			   domres_ObjectsMenu, vname_Disabled);
  } else {
    vdomainviewSetDomain(dview, savedDomain);
    vwindowPropagateChange(vdialogGetWindow(mainDialog), vname_State,
			   domres_DomainMenu, vname_Enabled);
    vwindowPropagateChange(vdialogGetWindow(mainDialog), vname_State,
			   domres_ObjectsMenu, vname_Enabled);
  }    
}

static void editMatrix(vconfirm *conf)
{
  vdebugTraceEnter(editMatrix);

  if (!vconfirmIsOpen(conf))
    vconfirmOpen(conf);
  else
    vwindowRaise(vconfirmGetWindow(conf));

  vdebugTraceLeave();
}

static int mainIssueFunc(vcommandSelector *com, vdict *context)
{
  int selector = vcommandGetSelector(com);
  vdialog *mainDialog = (vdialog *) vdictLoad(context, vname_Document);
  myDomainView *mview;
  vdomainview *dview;
  appData *data;
  vbool toggleState;
  int retVal = vTRUE;

  vdebugTraceEnter(mainIssueFunc);

  if (mainDialog == NULL) {
    vdebugTraceClear();
    return vFALSE;
  }
  data = mainDialogGetAppData(mainDialog);
  mview = appDataGetMview(data);
  dview = myDomainViewGetView(mview);
  toggleState = ((vname *) vdictLoad(context, vname_Toggle)) == vname_On ?
    vTRUE : vFALSE;

  vdebugMInform(("issuing %s\n", comTemplate[selector].name));

  switch (selector) {
  case comOPEN:
    break;
  case comSAVE:
    break;
  case comPREFERENCES:
    prefsOpen(appDataGetPrefsConfirm(data));
    break;
  case comADD_OBJECTS:
    addObjects(appDataGetAddItemsConfirm(data));
    break;
  case comREMOVE_OBJECTS:
    removeObjects(mainDialog);
    break;
  case comCONNECT_OBJECTS:
    connectObjects(mainDialog);
    break;
  case comDISCONNECT_OBJECTS:
    disconnectObjects(mainDialog);
    break;
  case comHIDE_OBJECTS:
    hideObjects(mainDialog);
    break;
  case comSHOW_ALL_OBJECTS:
    showAllObjects(mainDialog);
    break;
  case comSCROLL_TO_SELECTED:
    scrollToSelected(mainDialog);
    break;
  case comMAKE_UNSELECTABLE:
    makeUnselectable(mainDialog);
    break;
  case comTOGGLE_VIRTUAL:
    toggleVirtualBounds(mainDialog, toggleState);
    break;
  case comTOGGLE_LONG:
    toggleLong(mainDialog, toggleState);
    break;
  case comTOGGLE_TOP_LEFT:
    toggleTopLeft(mainDialog, toggleState);
    break;
  case comEDIT_GRID:
    editGrid(appDataGetEditGridConfirm(data));
    break;
  case comVIEW_COORDS:
    vwindowOpen((mainDialogGetAppData(mainDialog))->coordSys);
    break;
  case comPRINT_DOMAIN:
    {
      const vname *tag;

      if ((tag = (const vname *) vdictLoad(context, vname_Tag)) == NULL) {
	retVal = vFALSE;
      } else {
	vdictStore(context, vname_Operator,
		   vdialogGetItemObject(vdomainviewGetItem(dview)));
	vdictStore(context, vname_Tag, vname_Print);
	retVal =
	  vobjectIssueCommand(vdialogGetItemObject(vdomainviewGetItem(dview)),
			      vname_Print, context);
      }
    }
    break;
  case comDOMAIN_INSTALLED:
    domainInstalled(mainDialog, toggleState);
    break;
  case comTRACK_SELECT:
    vdomainviewSetTrackMode(dview, toggleState ?
			    vdomainviewGetTrackMode(dview) |
			    vdomainviewTRACK_SELECT :
			    vdomainviewGetTrackMode(dview) &
			    ~vdomainviewTRACK_SELECT);
    break;
  case comTRACK_DRAG:
    vdomainviewSetTrackMode(dview, toggleState ?
			    vdomainviewGetTrackMode(dview) |
			    vdomainviewTRACK_DRAG :
			    vdomainviewGetTrackMode(dview) &
			    ~vdomainviewTRACK_DRAG);
    break;
  case comTRACK_AUTOSCROLL:
    vdomainviewSetAutoScroll(dview, toggleState);
    break;
  case comLIVE_SELECTION:
    vdomainviewSetLiveSelection(dview, toggleState);
    break;
  case comSELECT_ENCLOSED:
    vdomainviewSetSelectEnclosed(dview, toggleState);
    break;
  case comSINGLE_SELECTION:
    vdomainviewSetSingleSelection(dview, toggleState);
    break;
  case comGRABBING_HAND:
    vdomainviewSetGrabbingHand(dview, toggleState);
    break;
  case comDRAG_PROHIBITED:
    vdomainviewSetDragProhibited(dview, toggleState);
    break;
  case comOFFSCREEN_DRAWING:
    vdomainviewSetOffscreenDrawing(dview, toggleState);
    break;
  case comEDIT_MATRIX:
    editMatrix(appDataGetEditMatrixConfirm(data));
    break;
  case comOUTLINE_ALL:
    if (toggleState)
      vdomainviewSetDragOutline(dview, vdomainviewOUTLINE_ALL);
    break;
  case comOUTLINE_TWO:
    if (toggleState)
      vdomainviewSetDragOutline(dview, vdomainviewOUTLINE_TWO);
    break;
  case comOUTLINE_LIMIT_RECT:
    if (toggleState)
      vdomainviewSetDragOutline(dview, vdomainviewOUTLINE_LIMITRECT);
    break;
  case comOUTLINE_NONE:
    if (toggleState)
      vdomainviewSetDragOutline(dview, vdomainviewOUTLINE_NONE);
    break;
  case comNORMAL_DRAG:
    if (toggleState)
      vdomainviewSetDragMethod(dview, vdomainviewDRAG_NORMAL);
    break;
  case comAUTOSCROLL_DRAG:
    if (toggleState)
      vdomainviewSetDragMethod(dview, vdomainviewDRAG_AUTOSCROLL);
    break;
  case comEXTERNAL_DRAG:
    if (toggleState)
      vdomainviewSetDragMethod(dview, vdomainviewEXTERNAL_DRAG);
    break;
  case comSNAP_OFF:
    if (toggleState)
      vdomainviewSetDragSnapMode(dview, vdomainviewSNAP_OFF);
    break;
  case comSNAP_NO_ALIGN:
    if (toggleState)
      vdomainviewSetDragSnapMode(dview, vdomainviewSNAP_NO_ALIGN);
    break;
  case comSNAP_ALIGN_ONE:
    if (toggleState)
      vdomainviewSetDragSnapMode(dview, vdomainviewSNAP_ALIGN_ONE);
    break;
  case comSNAP_ALIGN_LIMIT:
    if (toggleState)
      vdomainviewSetDragSnapMode(dview, vdomainviewSNAP_ALIGN_LIMIT);
    break;
  case comSMART_SCROLLBARS:
    myDomainViewSetSmartScrollbars(mview, toggleState);
    vwindowPropagateChange(vdialogGetWindow(mainDialog), vname_State,
			   domres_HorizontalBar, NULL);
    vwindowPropagateChange(vdialogGetWindow(mainDialog), vname_State,
			   domres_VerticalBar, NULL);
    break;
  case comHORIZONTAL_BAR:
    vdomainviewSetHorzBar(dview, toggleState);
    break;
  case comVERTICAL_BAR:
    vdomainviewSetVertBar(dview, toggleState);
    break;
  case comSHOW_GRID:
    myDomainViewShowGridVertices(mview, toggleState);
    break;
  case comDRAG_ON_UNSELECTABLES:
    myDomainViewSetDragOnUnselectables(mview, toggleState);
    break;
  default:
    retVal = vFALSE;
    break;
  };
  vdebugTraceLeave();
  return retVal;
}

static int mainQueryFunc(vcommandSelector *com, vdict *context)
{
  int selector = vcommandGetSelector(com);
  vdialog *mainDialog = (vdialog *) vdictLoad(context, vname_Document);
  vbool retVal = vTRUE;

  vdebugTraceEnter(mainQueryFunc);

  vdebugMInform(("querying %s\n", comTemplate[selector].name));

  if (mainDialog != NULL) {
    myDomainView *mview = appDataGetMview(mainDialogGetAppData(mainDialog));
    vdomainview *dview = myDomainViewGetView(mview);

    switch (selector) {
    case comTOGGLE_VIRTUAL:
      vdictStore(context, vname_Toggle,
		 vdomainGetVirtualBounds(vdomainviewGetDomain(dview)) ?
		 vname_On : vname_Off);
      break;
    case comTOGGLE_LONG:
      vdictStore(context, vname_Toggle, myDomainViewIsLong(mview) ?
		 vname_On : vname_Off);
      break;
    case comTOGGLE_TOP_LEFT:
      vdictStore(context, vname_Toggle,
		 vdomainGetOrientation(vdomainviewGetDomain(dview)) ==
		 vdomainORIENT_TOP_LEFT ? vname_On : vname_Off);
      break;
    case comDOMAIN_INSTALLED:
      vdictStore(context, vname_Toggle, vdomainviewGetDomain(dview) != NULL ?
		 vname_On : vname_Off);
      break;
    case comTRACK_SELECT:
      vdictStore(context, vname_Toggle, vdomainviewGetTrackMode(dview) &
		 vdomainviewTRACK_SELECT ? vname_On : vname_Off);
      break;
    case comTRACK_DRAG:
      vdictStore(context, vname_Toggle, vdomainviewGetTrackMode(dview) &
		 vdomainviewTRACK_DRAG ? vname_On : vname_Off);
      break;
    case comTRACK_AUTOSCROLL:
      vdictStore(context, vname_Toggle, vdomainviewIsAutoScroll(dview) ?
		 vname_On : vname_Off);
      break;
    case comLIVE_SELECTION:
      vdictStore(context, vname_Toggle, vdomainviewIsLiveSelection(dview) ?
		 vname_On : vname_Off);
      break;
    case comSELECT_ENCLOSED:
      vdictStore(context, vname_Toggle, vdomainviewIsSelectEnclosed(dview) ?
		 vname_On : vname_Off);
      break;
    case comSINGLE_SELECTION:
      vdictStore(context, vname_Toggle, vdomainviewIsSingleSelection(dview) ?
		 vname_On : vname_Off);
      break;
    case comGRABBING_HAND:
      vdictStore(context, vname_Toggle, vdomainviewHasGrabbingHand(dview) ?
		 vname_On : vname_Off);
      break;
    case comDRAG_PROHIBITED:
      vdictStore(context, vname_Toggle, vdomainviewIsDragProhibited(dview) ?
		 vname_On : vname_Off);
      break;
    case comOFFSCREEN_DRAWING:
      vdictStore(context, vname_Toggle, vdomainviewIsOffscreenDrawing(dview) ?
		 vname_On : vname_Off);
      break;
    case comOUTLINE_ALL:
      vdictStore(context, vname_Toggle, vdomainviewGetDragOutline(dview) ==
		 vdomainviewOUTLINE_ALL ? vname_On : vname_Off);
      break;
    case comOUTLINE_TWO:
      vdictStore(context, vname_Toggle, vdomainviewGetDragOutline(dview) ==
		 vdomainviewOUTLINE_TWO ? vname_On : vname_Off);
      break;
    case comOUTLINE_LIMIT_RECT:
      vdictStore(context, vname_Toggle, vdomainviewGetDragOutline(dview) ==
		 vdomainviewOUTLINE_LIMITRECT ? vname_On : vname_Off);
      break;
    case comOUTLINE_NONE:
      vdictStore(context, vname_Toggle, vdomainviewGetDragOutline(dview) ==
		 vdomainviewOUTLINE_NONE ? vname_On : vname_Off);
      break;
    case comNORMAL_DRAG:
      vdictStore(context, vname_Toggle, vdomainviewGetDragMethod(dview) ==
		 vdomainviewDRAG_NORMAL ? vname_On : vname_Off);
      break;
    case comAUTOSCROLL_DRAG:
      vdictStore(context, vname_Toggle, vdomainviewGetDragMethod(dview) ==
		 vdomainviewDRAG_AUTOSCROLL ? vname_On : vname_Off);
      break;
    case comEXTERNAL_DRAG:
      vdictStore(context, vname_Toggle, vdomainviewGetDragMethod(dview) ==
		 vdomainviewEXTERNAL_DRAG ? vname_On : vname_Off);
      break;
    case comSNAP_OFF:
      vdictStore(context, vname_Toggle, vdomainviewGetDragSnapMode(dview) ==
		 vdomainviewSNAP_OFF ? vname_On : vname_Off);
      break;
    case comSNAP_NO_ALIGN:
      vdictStore(context, vname_Toggle, vdomainviewGetDragSnapMode(dview) ==
		 vdomainviewSNAP_NO_ALIGN ? vname_On : vname_Off);
      break;
    case comSNAP_ALIGN_ONE:
      vdictStore(context, vname_Toggle, vdomainviewGetDragSnapMode(dview) ==
		 vdomainviewSNAP_ALIGN_ONE ? vname_On : vname_Off);
      break;
    case comSNAP_ALIGN_LIMIT:
      vdictStore(context, vname_Toggle, vdomainviewGetDragSnapMode(dview) ==
		 vdomainviewSNAP_ALIGN_LIMIT ? vname_On : vname_Off);
      break;
    case comSMART_SCROLLBARS:
      vdictStore(context, vname_Toggle, myDomainViewHasSmartScrollbars(mview) ?
		 vname_On : vname_Off);
      break;
    case comHORIZONTAL_BAR:
      vdictStore(context, vname_Toggle, vdomainviewHasHorzBar(dview) ?
		 vname_On : vname_Off);
      vdictStore(context, vname_State, myDomainViewHasSmartScrollbars(mview) ?
		 vname_Disabled : vname_Enabled);
      break;
    case comVERTICAL_BAR:
      vdictStore(context, vname_Toggle, vdomainviewHasVertBar(dview) ?
		 vname_On : vname_Off);
      vdictStore(context, vname_State, myDomainViewHasSmartScrollbars(mview) ?
		 vname_Disabled : vname_Enabled);
      break;
    case comSHOW_GRID:
      vdictStore(context, vname_Toggle,
		 myDomainViewIsShowingGridVertices(mview) ? vname_On :
		 vname_Off);
      break;
    case comDRAG_ON_UNSELECTABLES:
      vdictStore(context, vname_Toggle,
		 myDomainViewHasDragOnUnselectables(mview) ? vname_On :
		 vname_Off);
      break;
    default:
      retVal = vFALSE;
      break;
    }
  }

  vdebugTraceLeave();
  return retVal;
}

static void setupMainDialog(vdialog *mainDialog)
{
  vcommandSpace *space = vcommandCreateSpace();
  vcommandSelectorClass *selClass;
  vdict *comDict;
  vwindow *root;

  root = vwindowGetRoot();
  vdialogResize(mainDialog, vwindowGetW(root) / 3, vwindowGetH(root) / 3);
  vwindowPlace(vdialogGetWindow(mainDialog), root,
	       vrectPLACE_INSET | vrectPLACE_LEFT,
	       vrectPLACE_CENTER);

  vwindowSetSpaceOwned(vdialogGetWindow(mainDialog), space);
  selClass = vclassReproduce(vobjectGetCommandClass());
  vclassSet(selClass, vcommandISSUE, mainIssueFunc);
  vclassSet(selClass, vcommandQUERY, mainQueryFunc);
  comDict = vcommandCreateDictOfClassSelectorTemplates(selClass,
						       comTemplate,
						       comCOUNT);
  vdictStore(comDict, domres_Select_All, vdialogCreateFocusCommand());
  vdictStore(comDict, domres_Align_To_Objects, vdialogCreateFocusCommand());
  vdictStore(comDict, domres_Align_To_Grid, vdialogCreateFocusCommand());
  vdictStore(comDict, domres_Align_Vertical_Centers,
	     vdialogCreateFocusCommand());
  vdictStore(comDict, domres_Align_Left, vdialogCreateFocusCommand());
  vdictStore(comDict, domres_Align_Bottom, vdialogCreateFocusCommand());
  vdictStore(comDict, domres_Align_Top, vdialogCreateFocusCommand());
  vdictStore(comDict, domres_Align_Right, vdialogCreateFocusCommand());
  vdictStore(comDict, domres_Align_Horizontal_Centers,
	     vdialogCreateFocusCommand());
  vcommandAddSpaceDictOwned(space, vname_Command, comDict);
}

static void updateCoordContainer(vtextitem *view, vevent *event, int msg)
{
  if (msg == vtextviewACCEPT_NOTIFY) {
    vdialog *conf = vdialogDetermineItemDialog(vtextitemGetItem(view));
    vcontainer *cont =
      (vcontainer *) vdialogFindItem(conf, domres_coordContainer);
    vcontrol *ctrl =
      (vcontrol *) vdialogFindItem(conf, domres_toggleRandom);
    int count;

    vexWITH_HANDLING {
      count = vtextitemGetTextAsInt(view);
    } vexON_EXCEPTION {
      vtextitemSetText(view, vnameNULL);
      vexClear();
      return;
    } vexEND_HANDLING;

    if (count > 1) {
      vdialogDisableItem(vcontainerGetItem(cont));
      vcontrolSetValue(ctrl, 1);
    }
  }
}

static void updateCoordContainer2(vcontrol *ctrl, vevent *event)
{
  vdialog *conf = vdialogDetermineItemDialog(vcontrolGetItem(ctrl));
  vcontainer *cont =
    (vcontainer *) vdialogFindItem(conf, domres_coordContainer);

  if (vcontrolGetValue(ctrl))
    vdialogDisableItem(vcontainerGetItem(cont));
  else
    vdialogEnableItem(vcontainerGetItem(cont));
}

static int applyAdd(vconfirm *conf, vevent *event)
{
  vdomainview *dview;
  vdomain *dom;
  vtextitem *countItem;
  vcontrol *typeControl;
  vcontrol *randControl;
  int type, randomPlacement, randomTypes, band, image;
  long count;
  vrectLong domBounds, objBounds;
  vrect rect;
  bandNames *bands;
  imageStruct *images;
  vfont *font;
  vdomainObject *obj;
  vdomainObjectSet *objSet;
  
  vdebugTraceEnter(applyAdd);
  dview = myDomainViewGetView(appDataGetMview(addItemsGetAppData(conf)));
  bands = appDataGetBands(addItemsGetAppData(conf));
  images = appDataGetImages(addItemsGetAppData(conf));
  font = vdialogDetermineItemFont(vdomainviewGetItem(dview));

  dom = vdomainviewGetDomain(dview);
  if (vdomainIsLong(dom))
    domBounds = *vdomainGetBoundsLong(dom);
  else {
    vrect *bounds = vdomainGetBounds(dom);
    vrectToLong(bounds, &domBounds);
  }
  countItem = (vtextitem *) vdialogFindItem(vconfirmGetDialog(conf),
					    domres_objectCount);
  typeControl = (vcontrol *) vdialogFindItem(vconfirmGetDialog(conf),
					     domres_objectType);
  randControl = (vcontrol *) vdialogFindItem(vconfirmGetDialog(conf),
					     domres_toggleRandom);
  vexWITH_HANDLING {
    count = vtextitemGetTextAsFloat(countItem);
  } vexON_EXCEPTION {
    vtextitemSetText(countItem, vnameNULL);
    vexClear();
    vdebugTraceClear();
    return vFALSE;
  } vexEND_HANDLING;

  type = vcontrolGetValue(typeControl);
  randomTypes = (type == objRANDOM) ? 1 : 0;
  randomPlacement = vcontrolGetValue(randControl);
  if (!randomPlacement) {
    vcontainer *cont = (vcontainer *) vdialogFindItem(vconfirmGetDialog(conf),
						      domres_coordContainer);
    vtextitem *xPos = (vtextitem *) vcontainerFindItem(cont, domres_xCoord);
    vtextitem *yPos = (vtextitem *) vcontainerFindItem(cont, domres_yCoord);

    vexWITH_HANDLING {
      objBounds.x = vtextitemGetTextAsFloat(xPos);
      objBounds.y = vtextitemGetTextAsFloat(yPos);
    } vexON_EXCEPTION {
      randomPlacement = 1;
    } vexEND_HANDLING;
  }

  objSet = vdomainCreateObjectSet(NULL);

  while (count-- > 0) {
    obj = vdomainAddObject(dom);
    vdomainAddToObjectSet(&objSet, obj);
    if (randomTypes) {
      type = rand() % (objCOUNT - 1);
      vdomainSetObjectType(dom, vdomainObjectToSet(obj), type);
    }
    switch (type) {
    case objTEXT:
      band = rand() % bands->count;
      vfontSizedStringBounds(font, bands->names[band].text,
			     bands->names[band].length, &rect);
      if (randomPlacement)
	vrectSetLong(domBounds.x + (rand() % (domBounds.w - rect.w)),
		     domBounds.y + (rand() % (domBounds.h - rect.h)),
		     rect.w, rect.h, &objBounds);
      else {
	objBounds.w = rect.w;
	objBounds.h = rect.h;
      }
      vdomainSetObjectData(dom, vdomainObjectToSet(obj),
			   (void *) &(bands->names[band]));
      break;
    case objIMAGE:
      image = rand() % images->count;
      if (randomPlacement)
	vrectSetLong(domBounds.x + (rand() %
				    (domBounds.w -
				     vimageGetWidth(images->imArray[image]))),
		     domBounds.y + (rand() %
				    (domBounds.h -
				     vimageGetHeight(images->imArray[image]))),
		     vimageGetWidth(images->imArray[image]),
		     vimageGetHeight(images->imArray[image]), &objBounds);
      else {
	objBounds.w = vimageGetWidth(images->imArray[image]);
	objBounds.h = vimageGetHeight(images->imArray[image]);
      }
      vdomainSetObjectData(dom, vdomainObjectToSet(obj),
			   (void *) images->imArray[image]);
      break;
    case objRECT:
    case objTRIANGLE:
    case objCIRCLE:
    default:
      if (randomPlacement)
	vrectSetLong(domBounds.x + (rand() % (domBounds.w - objectSizes[type].x)),
		     domBounds.y + (rand() % (domBounds.h - objectSizes[type].y)),
		     objectSizes[type].x, objectSizes[type].y, &objBounds);
      else {
	objBounds.w = objectSizes[type].x;
	objBounds.h = objectSizes[type].y;
      }
      break;
    }
    if (vdomainIsLong(dom))
      vdomainSetObjectBoundsLong(dom, vdomainObjectToSet(obj), &objBounds);
    else {
      vrectFromLong(&objBounds, &rect);
      vdomainSetObjectBounds(dom, vdomainObjectToSet(obj), &rect);
    }
  }
  if (!randomTypes)
    vdomainSetObjectType(dom, objSet, type);
  vdomainShowObjects(dom, objSet);
  vdomainDestroyObjectSet(objSet);

  vdebugTraceLeave();
  return vTRUE;
}

static void setupAddItems(vconfirm *conf)
{
  vtextitem *count;
  vcontrol *random;

  count = (vtextitem *) vdialogFindItem(vconfirmGetDialog(conf),
					domres_objectCount);
  random = (vcontrol *) vdialogFindItem(vconfirmGetDialog(conf),
					domres_toggleRandom);
  vtextitemSetNotify(count, updateCoordContainer);
  vcontrolSetNotify(random, updateCoordContainer2);
  vconfirmSetApplyHook(conf, applyAdd);
  vwindowSetLeader(vconfirmGetWindow(conf),
	     vdialogGetWindow(appDataGetMainDialog(addItemsGetAppData(conf))));
}

static int applyEditGrid(vconfirm *conf, vevent *event)
{
  vdomainview *dview;
  vtextitem *titem;
  volatile vbool retVal = vTRUE;
  vdomainGrid grid = {0, 0, 0, 0};

  vdebugTraceEnter(applyEditGrid);

  dview = myDomainViewGetView(appDataGetMview(editGridGetAppData(conf)));
  vexWITH_HANDLING {
    titem = (vtextitem *) vdialogFindItem(vconfirmGetDialog(conf),
					  domres_XSpacing);
    grid.xSpacing = vtextitemGetTextAsInt(titem);
    titem = (vtextitem *) vdialogFindItem(vconfirmGetDialog(conf),
					  domres_YSpacing);
    grid.ySpacing = vtextitemGetTextAsInt(titem);
    titem = (vtextitem *) vdialogFindItem(vconfirmGetDialog(conf),
					  domres_XSkew);
    grid.xSkew = vtextitemGetTextAsInt(titem);
    titem = (vtextitem *) vdialogFindItem(vconfirmGetDialog(conf),
					  domres_YSkew);
    grid.ySkew = vtextitemGetTextAsInt(titem);
  } vexON_EXCEPTION {
    retVal = vFALSE;
  } vexEND_HANDLING;

  if (retVal != vFALSE) {
    vdomainSetGrid(vdomainviewGetDomain(dview), &grid);
    vdomainviewInval(dview);
  }

  vdebugTraceLeave();
  return retVal;
}

static void setupEditGrid(vconfirm *conf)
{
  vconfirmSetApplyHook(conf, applyEditGrid);
  vwindowSetLeader(vconfirmGetWindow(conf),
	     vdialogGetWindow(appDataGetMainDialog(editGridGetAppData(conf))));
}

static int applyEditMatrix(vconfirm *conf, vevent *event)
{
  volatile vbool retVal = vTRUE;
  vdomainview *dview;
  vtextitem *titem;
  double sx, sy, r, tx, ty;
  static vmatrix mtx;

  vdebugTraceEnter(applyEditMatrix);

  mtx = *vmatrixIdent();

  dview = myDomainViewGetView(appDataGetMview(matrixGetAppData(conf)));
  titem = (vtextitem *) vdialogFindItem(vconfirmGetDialog(conf),
					domres_scaleX);
  vexWITH_HANDLING {
    sx = vtextitemGetTextAsFloat(titem);
  } vexON_EXCEPTION {
    sx = 1;
  } vexEND_HANDLING;
  titem = (vtextitem *) vdialogFindItem(vconfirmGetDialog(conf),
					domres_scaleY);
  vexWITH_HANDLING {
    sy = vtextitemGetTextAsFloat(titem);
  } vexON_EXCEPTION {
    sy = 1;
  } vexEND_HANDLING;
  titem = (vtextitem *) vdialogFindItem(vconfirmGetDialog(conf),
					domres_rotate);
  vexWITH_HANDLING {
    r = vtextitemGetTextAsFloat(titem);
  } vexON_EXCEPTION {
    r = 0;
  } vexEND_HANDLING;
  titem = (vtextitem *) vdialogFindItem(vconfirmGetDialog(conf),
					domres_translateX);
  vexWITH_HANDLING {
    tx = vtextitemGetTextAsFloat(titem);
  } vexON_EXCEPTION {
    tx = 0;
  } vexEND_HANDLING;
  titem = (vtextitem *) vdialogFindItem(vconfirmGetDialog(conf),
					domres_translateY);
  vexWITH_HANDLING {
    ty = vtextitemGetTextAsFloat(titem);
  } vexON_EXCEPTION {
    ty = 0;
  } vexEND_HANDLING;

  vmatrixScale(&mtx, sx, sy, &mtx);
  vmatrixRotate(&mtx, r, &mtx);
  vmatrixTranslate(&mtx, tx, ty, &mtx);
  if (vmatrixIsIdent(&mtx))
    vdomainviewSetMatrix(dview, NULL);
  else {
    vexWITH_HANDLING {
      vdomainviewSetMatrix(dview, &mtx);
    } vexON_EXCEPTION {
      retVal = vFALSE;
    } vexEND_HANDLING;
  }
  myDomainViewRecalcBars(appDataGetMview(matrixGetAppData(conf)));

  vdebugTraceLeave();
  return retVal;
}

static void setupEditMatrix(vconfirm *conf)
{
  vconfirmSetApplyHook(conf, applyEditMatrix);
  vwindowSetLeader(vconfirmGetWindow(conf),
	       vdialogGetWindow(appDataGetMainDialog(matrixGetAppData(conf))));
}

static void setupBandNames(vresource namesRes, bandNames *bands)
{
  size_t i;

  bands->count = vresourceCountComponents(namesRes);
  bands->names = (bandName *) vmemAlloc(sizeof(bandName) * bands->count);

  for (i = 0; i < bands->count; i++) {
    bands->names[i].text = vresourceGetStringAt(namesRes, i);
    bands->names[i].length = vcharLength(bands->names[i].text);
  }
}

static void cleanupBandNames(bandNames *bands)
{
  size_t i = bands->count;
  bandName *scan = &(bands->names[i-1]);

  while(i--) {
    vstrDestroy(scan->text);
    scan--;
  }
  vmemFree((void *) bands->names);
}

static void setupImages(vresource imagesRes, imageStruct *images)
{
  size_t i;
  const vname *tag;

  images->count = vresourceCountComponents(imagesRes);
  images->imArray = (vimage **) vmemAlloc(sizeof(vimage *) * images->count);

  for (i = 0; i < images->count; i++) {
    tag = vresourceGetNthTag(imagesRes, i);
    images->imArray[i] = vimageLoad(vresourceGet(imagesRes, tag));
  }
}

static void cleanupImages(imageStruct *images)
{
  size_t i = images->count;
  vimage **scan = &(images->imArray[i-1]);

  while (i--) {
    vimageDestroy(*scan);
    scan--;
  }
  vmemFree((void *) images->imArray);
}

static void setupObjectSizes(vresource objectSizesRes)
{
  vresource	obj;
  size_t	count, i;

  count = vresourceCountComponents(objectSizesRes);
  for (i = 0; (i < count) && (i < objCOUNT); i++) {
    obj = vresourceGetAt(objectSizesRes, i);
    objectSizes[i].x = vresourceGetInteger(obj, domres_X);
    objectSizes[i].y = vresourceGetInteger(obj, domres_Y);
  }
}

static void mainDialogNotify(vdialog *mainDialog, vevent *event)
{
  if (veventGetType(event) == veventWINDOW_STATE &&
      veventIsClose(event))
    veventStopProcessing();
}

int main(int argc, char *argv[])
{
  vresource appRes;
  vresource mainDialogRes;
  vresource addItemsConfirmRes;
  vresource gridConfirmRes;
  vresource prefsConfirmRes;
  vresource matrixConfirmRes;
  vresource coordSysWindowRes;
  vresource bandNamesRes;
  vresource imagesRes;
  vresource objectSizesRes;
  vdialog *mainDialog;
  appData data;

  vprefSetArgs(argc, argv);
  (void) vapplicationGetDefaultClass();
  (void) vwindowGetDefaultClass();
  (void) vbuttonGetDefaultClass();
  (void) vcommandGetDefaultClass();
  (void) vconfirmGetDefaultClass();
  (void) vcontainerGetDefaultClass();
  (void) vcontrolGetDefaultClass();
  (void) vcontrolGetOptionMenuClass();
  (void) vcontrolGetToggleClass();
  (void) vdialogGetDefaultClass();
  (void) vdialogGetDefaultItemClass();
  (void) vdomainGetDefaultClass();
  (void) vdomainGetDefaultObserverClass();
  (void) vdomainviewGetDefaultClass();
#if (vportPEEK)
  (void) vlistGetDefaultClass();
  (void) vlistitemGetDefaultClass();
  (void) vlistviewGetDefaultClass();
#endif
  (void) vmenuGetDefaultItemClass();
  (void) vmenuGetDefaultClass();
  (void) vmenubarGetDefaultClass();
  (void) vobjectGetDefaultAttributedClass();
  (void) vobjectGetDefaultClass();
  (void) vtextGetDefaultClass();
  (void) vtextitemGetDefaultClass();
  (void) vtextrulerGetDefaultClass();
  (void) vtextviewGetDefaultClass();
  (void) myDomainViewGetDefaultClass();
  (void) coordSysWindowGetDefaultClass();

#if (vportPEEK)
  peekInitialize(vTRUE);
#endif

  domresInternNames();
  domnamesInternNames();

  appRes = vapplicationGetResources(vapplicationGetCurrent());
  mainDialogRes = vresourceGet(appRes, domres_mainDialog);
  mainDialog = vdialogLoad(mainDialogRes);
  data.mainDialog = mainDialog;
  mainDialogSetAppData(mainDialog, &data);
  appDataSetMview(&data,
		  (myDomainView *) vdialogFindItem(mainDialog,
						   domres_myDomainView));
  vdialogSetNotify(mainDialog, mainDialogNotify);
  setupMainDialog(mainDialog);

  if (vresourceTestGet(appRes, domres_objectSizes, &objectSizesRes))
    setupObjectSizes(objectSizesRes);

  coordSysWindowRes = vresourceGet(appRes, domres_coordSysWindow);
  data.coordSys = vwindowLoad(coordSysWindowRes);
  coordSysSetAppData(data.coordSys, &data);

  addItemsConfirmRes = vresourceGet(appRes, domres_addItemsConfirm);
  data.addItems = vconfirmLoad(addItemsConfirmRes);
  addItemsSetAppData(data.addItems, &data);
  setupAddItems(data.addItems);

  gridConfirmRes = vresourceGet(appRes, domres_gridConfirm);
  data.editGrid = vconfirmLoad(gridConfirmRes);
  editGridSetAppData(data.editGrid, &data);
  setupEditGrid(data.editGrid);

  prefsConfirmRes = vresourceGet(appRes, domres_prefsConfirm);
  appDataSetPrefsConfirm(&data, vconfirmLoad(prefsConfirmRes));
  prefsSetAppData(appDataGetPrefsConfirm(&data), &data);
  prefsSetup(appDataGetPrefsConfirm(&data));

  matrixConfirmRes = vresourceGet(appRes, domres_matrixConfirm);
  appDataSetEditMatrixConfirm(&data, vconfirmLoad(matrixConfirmRes));
  matrixSetAppData(appDataGetEditMatrixConfirm(&data), &data);
  setupEditMatrix(appDataGetEditMatrixConfirm(&data));

  bandNamesRes = vresourceGet(appRes, domres_Bands);
  setupBandNames(bandNamesRes, appDataGetBands(&data));

  imagesRes = vresourceGet(appRes, domnames_Images);
  setupImages(imagesRes, appDataGetImages(&data));

  vdialogOpen(mainDialog);

  veventProcess();

  vconfirmDestroy(data.addItems);
  vconfirmDestroy(data.editGrid);
  vconfirmDestroy(appDataGetEditMatrixConfirm(&data));
  prefsShutdown(appDataGetPrefsConfirm(&data));
  vconfirmDestroy(appDataGetPrefsConfirm(&data));
  vwindowDestroy(data.coordSys);
  vdialogDestroy(mainDialog);
  cleanupBandNames(appDataGetBands(&data));
  cleanupImages(appDataGetImages(&data));

#if (vportPEEK)
  peekShutdown();
#endif

  exit(EXIT_SUCCESS);
  return EXIT_FAILURE;
}

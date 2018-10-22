/* $Id: mydview.c,v 1.16 1997/09/17 17:32:03 gregt Exp $ */
/* mydview
 *
 * my domainview subclass
 */

#include <vport.h>
#include vscribeHEADER
#include vcharHEADER
#include vcolorHEADER
#include vclassHEADER
#include vdomainHEADER
#include vprintHEADER
#include vapplicationHEADER
#include vdomainviewHEADER
#include "mydview.h"
#include "domsamp.h"
#include "domnames.h"
#include "domres.h"

#if (vdebugDEBUG)
static const char _mydviewTAG[] = "mydview";
#define vdebugTAG _mydviewTAG
#endif

/* prototypes */
static void _myDomainViewStartup(void);

/* global data */
static myDomainViewClass *_myDViewClass = NULL;
static vdomainClass *_myDomainClass = NULL;
static vdomainObserverClass *_myObserverClass = NULL;
static int _hBarHeight, _vBarWidth;

/* private constants */

enum {
  DEFAULT_FLAGS = _myDomainViewSMART_SCROLLBARS
};

myDomainViewClass *myDomainViewGetDefaultClass(void)
{
  if (_myDViewClass == NULL)
    _myDomainViewStartup();
  return _myDViewClass;
}

void myDomainViewSetLong(myDomainView *mview, vbool isLong)
{
  vdebugTraceEnter(myDomainViewSetLong);

  if ((isLong && myDomainViewIsLong(mview)) ||
      (!isLong && !myDomainViewIsLong(mview))) {
    vdebugTraceClear();
    return;
  }

  vdebugTraceLeave();
}

static vbool _myDomainIntersectFunc(vdomain *dom,
				    vdomainObject *obj1,
				    vdomainObject *obj2)
{
  if (vdomainIsLong(dom))
    return(vrectMIntersectsLong(vdomainGetObjectBoundsLong(dom, obj1),
			       vdomainGetObjectBoundsLong(dom, obj2)));
  else
    return(vrectMIntersects(vdomainGetObjectBounds(dom, obj1),
			   vdomainGetObjectBounds(dom, obj2)));
}

static vbool _myDomainRectIntersectFunc(vdomain *dom,
					vdomainObject *obj,
					vrect *r)
{
  return(vrectMIntersects(r, vdomainGetObjectBounds(dom, obj)));
}

static vbool _myDomainRectIntersectFuncLong(vdomain *dom,
					    vdomainObject *obj,
					    vrectLong *r)
{
  vbool retVal = FALSE;

  switch (vdomainGetObjectType(dom, obj)) {
  case objTRIANGLE:
    {
      vrectFloat fbounds;
      float m;

      vrectLongToFloat(vdomainGetObjectBoundsLong(dom, obj), &fbounds);
      m = 2.0 * fbounds.h / fbounds.w;
      retVal = (fbounds.y + fbounds.h > r->y &&
		(fbounds.x + fbounds.w - r->x > 0 ||
		 r->x + r->w - fbounds.x > 0));
    }
    break;
  case objRECT:
  default:
    retVal = vrectMIntersectsLong(r, vdomainGetObjectBoundsLong(dom, obj));
    break;
  }
  return retVal;
}

static vrectLong *_LongCloneSetFromFloat(const vrectFloat *rects, int count)
{
  vrectLong *clone, *scan;

  scan = clone = vrectCreateSetLong(count);
  while (count--) {
    scan->x = (long) floor(rects->x);
    scan->y = (long) floor(rects->y);
    scan->w = (long) ceil(rects->x + rects->w) - scan->x;
    scan->h = (long) ceil(rects->y + rects->h) - scan->y;
    scan++;
    rects++;
  }
  return clone;
}

/* _intrClipBounds:
 *
 * Returns a set of vrectLongs which need to have the background drawn in 'em.
 * The caller must destroy the vrectLong set.
 */
static vrectLong *_intrClipBounds(myDomainView *mview, int *intrCount)
{
  int i, count, ucount, vcount;
  const vrectFloat *rects;
  vrectLong *urects, *vrects;
  vrectLong *retRects, *longScan;

  vdebugTraceEnter(_intrClipBounds);

  vdrawFClipBounds(&rects, &ucount);
  urects = _LongCloneSetFromFloat(rects, ucount);
  vdrawFViewClipBounds(&rects, &vcount);
  vrects = _LongCloneSetFromFloat(rects, vcount);
  retRects = vrectIntersectSetsLong(urects, vrects, ucount, vcount, intrCount);
  vrectDestroySetLong(urects);
  vrectDestroySetLong(vrects);

#if (vdebugDEBUG)
  count = *intrCount;
  longScan = retRects;
  i = 0;
  vdebugMTrace(("Intersecting bounds:\n"));
  while (count--) {
#if DEBUG_INVAL_RECTS
    vrectFloat rect;
#endif /* DEBUG_INVAL_RECTS */
    vdebugMTrace(("\t%d: {%3d, %3d, %3d, %3d}\n", i++, longScan->x,
		  longScan->y, longScan->w, longScan->h));
#if DEBUG_INVAL_RECTS
    vrectLongToFloat(longScan, &rect);
    vdrawFRectsFill(&rect, 1);
#endif /* DEBUG_INVAL_RECTS */
    longScan++;
  }
#endif /* (vdebugDEBUG) */

  vdebugTraceLeave();

  return retRects;
}

static void _myDomainViewBackground(myDomainView *mview)
{
  register vdomainGrid grid;

  vdebugTraceEnter(_myDomainViewBackground);

  vclassSendSuper(_myDViewClass, vdomainviewBACKGROUND, (mview));

  if (myDomainViewGetDomain(mview) != NULL) {
    grid = *vdomainGetGrid(myDomainViewGetDomain(mview));
    if (myDomainViewIsShowingGridVertices(mview) &&
	grid.xSpacing != 0 && grid.ySpacing != 0) {
      vcolor *color = vdialogDetermineItemColor(myDomainViewGetItem(mview),
						vdrawCOLOR_BACKGROUND_HILITE);
      long x, x0, y, xMax, yMax, tmp;
      vrectFloat drawRect = {0, 0, 1, 1};
      int intrCount;
      vrectLong *intrClip, *scan;

      vdrawGSave();

      if (vdomainIsLong(myDomainViewGetDomain(mview))) {
	vrectFloat	spamRect;

	vrectLongToFloat(vdomainGetBoundsLong(myDomainViewGetDomain(mview)),
			 &spamRect);
	vdrawFRectsClip(&spamRect, 1);
      } else
	vdrawRectsClip(vdomainGetBounds(myDomainViewGetDomain(mview)), 1);

      vdrawSetColor(color);

      scan = intrClip = _intrClipBounds(mview, &intrCount);
      while(intrCount--) {
	if ((tmp = scan->x % (2 * grid.xSpacing)) < 0)
	  tmp += 2 * grid.xSpacing;
	x = x0 = scan->x - tmp;
	if ((tmp = scan->y % (2 * grid.ySpacing)) < 0)
	  tmp += 2 * grid.ySpacing;
	y = scan->y - tmp;
	xMax = scan->x + scan->w;
	yMax = scan->y + scan->h;
	while (y < yMax) {
	  while (x < xMax) {
	    drawRect.x = x;
	    drawRect.y = ((x / grid.xSpacing) & 1) ? y + grid.ySkew : y;
	    vdrawFRectsFill(&drawRect, 1);
	    x += grid.xSpacing;
	  }
	  y += grid.ySpacing;
	  if ((y / grid.ySpacing) & 1)
	    x = x0 + grid.xSkew;
	  else
	    x = x0;
	}
	scan++;
      }
      vdrawGRestore();
      vrectDestroySetLong(intrClip);
    }
  }

  vdebugTraceLeave();
}

static vbool _myDomainViewHandleResizeEvent(myDomainView *mview,
					    vdomainviewResizeEvent *event)
{
  if (myDomainViewHasSmartScrollbars(mview))
    myDomainViewRecalcBars(mview);
  vapplicationChangedAttributeNone(vapplicationGetCurrent(),
				   domnames_DomainCoords);

  return vclassSendSuper(_myDViewClass, vdomainviewHANDLE_RESIZE_EVENT,
			 (mview, event));
}

static vbool _myDomainViewHandleScrollEvent(myDomainView *mview,
					    vdomainviewScrollEvent *event)
{
  vapplicationChangedAttributeNone(vapplicationGetCurrent(),
				   domnames_DomainCoords);
  return vclassSendSuper(_myDViewClass, vdomainviewHANDLE_SCROLL_EVENT,
			 (mview, event));
}

static vbool _myDomainViewHandleButtonDownEvent(myDomainView *mview,
					     vdomainviewButtonDownEvent *event)
{
  if (myDomainViewHasDragOnUnselectables(mview) &&
      (event->clickedOnObject != NULL) &&
      vdomainIsObjectUnselectable(myDomainViewGetDomain(mview),
				  event->clickedOnObject)) {
    mview->trackMode = vdomainviewGetTrackMode(myDomainViewGetView(mview));
    vdomainviewSetTrackMode(myDomainViewGetView(mview),
			    mview->trackMode & ~vdomainviewTRACK_DRAG);
  } else
    mview->trackMode = 0;

  return vclassSendSuper(_myDViewClass, vdomainviewHANDLE_BUTTON_DOWN_EVENT,
			 (mview, event));
}

static vbool _myDomainViewHandleButtonUpEvent(myDomainView *mview,
					      vdomainviewButtonUpEvent *event)
{
  if (myDomainViewHasDragOnUnselectables(mview) && mview->trackMode != 0)
    vdomainviewSetTrackMode(myDomainViewGetView(mview), mview->trackMode);

  return vclassSendSuper(_myDViewClass, vdomainviewHANDLE_BUTTON_UP_EVENT,
			 (mview, event));
}

/* enable or disable the scrollbars according to the domain bounds
 * and the domainview's itemRect.
 */
void _myDomainViewRecalcBars(myDomainView *mview)
{
  vdomainview *dview = myDomainViewGetView(mview);
  vrect itemRect;
  vrectLong ldomBounds;
  short borderInset = vclassGet(_myDViewClass, vdomainviewBORDER_INSET);
  int sMargin = vdomainviewGetScrollBarMargin(dview);
  int needHoriz, needVert;
  static vbool recurseProtect = vFALSE;

  vdebugTraceEnter(_myDomainViewRecalcBars);

  itemRect = *vdialogGetItemRect(vdomainviewGetItem(dview));

  if (recurseProtect ||
      !vdialogItemIsOpen(vdomainviewGetItem(dview)) ||
      !myDomainViewHasSmartScrollbars(mview) ||
      myDomainViewGetDomain(mview) == NULL) {
    vdebugTraceClear();
    return;
  }

  if (vdomainIsLong(vdomainviewGetDomain(dview)))
    ldomBounds = *vdomainGetBoundsLong(vdomainviewGetDomain(dview));
  else {
    vrect *domBounds = vdomainGetBounds(vdomainviewGetDomain(dview));
    vrectToLong(domBounds, &ldomBounds);
  }
  vdomainviewTranslateRectLong(dview, &ldomBounds, vdomainviewTO_DIALOG);
  vrectInset(&itemRect, borderInset, borderInset, &itemRect);
  if (itemRect.w < ldomBounds.w)
    needHoriz = TRUE;
  else if (itemRect.w - _vBarWidth - sMargin >= ldomBounds.w)
    needHoriz = FALSE;
  else
    needHoriz = -1;
  if (itemRect.h < ldomBounds.h)
    needVert = TRUE;
  else if (itemRect.h - _hBarHeight - sMargin >= ldomBounds.h)
    needVert = FALSE;
  else
    needVert = -1;

  if (needVert == -1)
    needVert = (needHoriz == TRUE) ? TRUE : FALSE;
  if (needHoriz == -1)
    needHoriz = (needVert == TRUE) ? TRUE : FALSE;

  recurseProtect = vTRUE;
  vdomainviewSetHorzBar(dview, needHoriz);
  vdomainviewSetVertBar(dview, needVert);
  recurseProtect = vFALSE;

  vwindowPropagateChange(vdialogDetermineItemWindow(myDomainViewGetItem(mview)),
			 vname_Toggle, domres_HorizontalBar, NULL);
  vwindowPropagateChange(vdialogDetermineItemWindow(myDomainViewGetItem(mview)),
			 vname_Toggle, domres_VerticalBar, NULL);

  vdebugTraceLeave();
}

void _myDomainViewSetSmartScrollbars(myDomainView *mview, vbool hasSmart)
{
  vdebugTraceEnter(_myDomainViewSetSmartScrollbars);

  if ((hasSmart && myDomainViewHasSmartScrollbars(mview)) ||
      (!hasSmart && !myDomainViewHasSmartScrollbars(mview))) {
    vdebugTraceClear();
    return;
  }

  if (hasSmart) {
    mview->flags |= _myDomainViewSMART_SCROLLBARS;
    myDomainViewRecalcBars(mview);
  } else
    mview->flags &= ~_myDomainViewSMART_SCROLLBARS;

  vdebugTraceLeave();
}

void _myDomainViewShowGridVertices(myDomainView *mview, vbool showGrid)
{
  vdebugTraceEnter(_myDomainViewShowGridVertices);

  if ((showGrid && myDomainViewIsShowingGridVertices(mview)) ||
      (!showGrid && !myDomainViewIsShowingGridVertices(mview))) {
    vdebugTraceClear();
    return;
  }

  if (showGrid)
    mview->flags |= _myDomainViewSHOW_GRID;
  else
    mview->flags &= ~_myDomainViewSHOW_GRID;

  vdomainviewInval(myDomainViewGetView(mview));

  vdebugTraceLeave();
}

static void _myDomainViewSetSelColor(myDomainView *mview, vcolor *color)
{
  vdebugTraceEnter(_myDomainViewSetSelColor);

  mview->selColor = (color == NULL) ? vcolorGetWhite() : color;

  vdebugTraceLeave();
}

static void _myDomainViewSetDragOnUnselectables(myDomainView *mview,
						vbool hasDrag)
{
  if (hasDrag)
    mview->flags |= _myDomainViewDRAG_UNSELECTABLES;
  else
    mview->flags &= ~_myDomainViewDRAG_UNSELECTABLES;
}

static void _myDomainViewDrawObjectProc(vdomainview *dview, vdomainObject *obj)
{
  vrect *bounds;
  vrectLong *lbounds;
  myDomainView *mview = (myDomainView *) dview;
  vdomain *dom = vdomainviewGetDomain(dview);
  vrectFloat fbounds;
  vcolor *color;

  if (vdomainIsLong(dom)) {
    lbounds = vdomainGetObjectBoundsLong(dom, obj);
    vrectLongToFloat(lbounds, &fbounds);
  } else {
    bounds = vdomainGetObjectBounds(dom, obj);
    vrectToFloat(bounds, &fbounds);
  }

  /*
   * someday this will support selection indication via a DrawSelection
   * proc.  right now, however, we just draw the object differently if
   * it's selected.
   */

  if (vdomainIsObjectSelected(dom, vdomainviewGetSelection(dview), obj))
    color = myDomainViewGetSelColor(mview);
  else
    color = vcolorGetBlack();

  vdrawGSave();
  vdrawSetColor(color);
  vdrawFRectsClip(&fbounds, 1);

  switch(vdomainGetObjectType(dom, obj)) {
  case objRECT:
    vdrawFRectsFill(&fbounds, 1);
    break;
  case objTRIANGLE:
    vdrawNewPath();
    vdrawFMoveTo(fbounds.x, fbounds.y);
    vdrawFLineTo(fbounds.x + fbounds.w - 1.0, fbounds.y);
    vdrawFLineTo(fbounds.x + fbounds.w / 2.0, fbounds.y + fbounds.h - 1.0);
    vdrawClosePath();
    vdrawFill();
    break;
  case objCIRCLE: {
    float r;

    vdrawNewPath();
    r =  fbounds.w < fbounds.h ? fbounds.w / 2.0 : fbounds.h / 2.0;
    vdrawFMoveTo(fbounds.x + fbounds.w / 2.0 + r, fbounds.y + fbounds.h / 2.0);
    vdrawFArc(fbounds.x + fbounds.w / 2.0, fbounds.y + fbounds.h / 2.0, r,
	      0, 360);
    vdrawClosePath();
    vdrawFill();
    }
    break;
  case objTEXT: {
    bandName *band = (bandName *) vdomainGetObjectData(dom, obj);
    vfont *font = vdrawGetFont();
    vrect rect;

    vfontSizedStringBounds(font, band->text, band->length, &rect);
    if (vdomainGetOrientation(dom) == vdomainORIENT_BOTTOM_LEFT) {
      vdrawFMoveTo(fbounds.x - rect.x, fbounds.y - rect.y);
      vdrawSizedShow(band->text, band->length);
    } else {
      vmatrix fmat;
      vfont *newfont;

      vmatrixScale(vfontGetMatrix(font), 1.0, -1.0, &fmat);
      newfont = vfontMake(vfontGetFace(font), &fmat);
      vdrawSetFont(newfont);
      vdrawFMoveTo(fbounds.x - rect.x, fbounds.y + rect.y + fbounds.h);
      vdrawSizedShow(band->text, band->length);
    }
    }
    break;
  case objIMAGE: {
    vimage *image = (vimage *) vdomainGetObjectData(dom, obj);

    if (vdomainGetOrientation(dom) == vdomainORIENT_BOTTOM_LEFT) {
      vdrawFMoveTo(fbounds.x, fbounds.y);
      vdrawImageCompositeIdent(image);
    } else {
      vmatrix	mtx;

      vmatrixScale(vmatrixIdent(), 1.0, -1.0, &mtx);
      vmatrixTranslate(&mtx, -fbounds.x, -fbounds.y - fbounds.h, &mtx);
      vdrawImageComposite(image, &mtx);
    }
    }
    break;
  default:
    break;
  }
  vdrawGRestore();
}

/*
 * _myDomainViewDrawSelection
 *
 * a pretty bad drawSelectionProc which just draws an X through the object.
 * this is horribly primitive, and looks bad for most objects.  for now,
 * this isn't used.  all selection drawing is done in the drawObjectProc.
 * in the future, there may be some more intelligent selection drawing
 * done in here.
 */
#ifdef MUST_IMPLEMENT_DRAW_SELECTION
static void _myDomainViewDrawSelection(vdomainview *dview, vdomainObject *obj)
{
  vrect *bounds;
  vrectLong *lbounds;
  myDomainView *mview = (myDomainView *) dview;
  vdomain *dom = vdomainviewGetDomain(dview);
  vrectFloat fbounds;

  if (vdomainIsLong(dom)) {
    lbounds = vdomainGetObjectBoundsLong(dom, obj);
    vrectLongToFloat(lbounds, &fbounds);
  } else {
    bounds = vdomainGetObjectBounds(dom, obj);
    vrectToFloat(bounds, &fbounds);
  }

  vdrawGSave();
  vdrawSetColor(vcolorGetBlack());
  vdrawSetComplement(myDomainViewGetSelColor(mview));
  vdrawSetFunction(vdrawFUNC_COMPLEMENT);
  vdrawSetLineWidth(1);
  vdrawFRectsClip(&fbounds, 1);

  vdrawFMoveTo(fbounds.x, fbounds.y);
  vdrawFLineTo(fbounds.x + fbounds.w - 1, fbounds.y + fbounds.h - 1);
  vdrawFMoveTo(fbounds.x, fbounds.y + fbounds.h - 1);
  vdrawFLineTo(fbounds.x + fbounds.w - 1, fbounds.y);
  vdrawStroke();

  vdrawGRestore();
}
#endif /* MUST_IMPLEMENT_DRAW_SELECTION */

static void _myDomainViewResizeTextObjects(myDomainView *mview)
{
  vdomainObject *obj;
  vdomainObjectSet *set;
  vdomainObjectSetIterator iterator;
  vdomain *dom = myDomainViewGetDomain(mview);
  vdomainview *dview = myDomainViewGetView(mview);
  vfont *font = vdialogDetermineItemFont(myDomainViewGetItem(mview));
  vrect bounds;
  vrectLong lbounds;
  bandName *band;

  if (dom == NULL)
    return;

  set = vdomainGetObjectSet(dom, vdomainviewGetSelection(dview), vdomainALL,
			    NULL);
  vdomainInitObjectSetIterator(&iterator, set);
  while (vdomainNextObjectSetIterator(&iterator)) {
    obj = vdomainGetObjectSetIteratorObject(&iterator);
    switch (vdomainGetObjectType(dom, obj)) {
    case objTEXT:
      if (vdomainIsLong(dom))
	lbounds = *vdomainGetObjectBoundsLong(dom, obj);
      else
	vrectToLong(vdomainGetObjectBounds(dom, obj), &lbounds);
      band = (bandName *) vdomainGetObjectData(dom, obj);
      vfontSizedStringBounds(font, band->text, band->length, &bounds);
      lbounds.w = bounds.w;
      lbounds.h = bounds.h;
      if (vdomainIsLong(dom))
	vdomainSetObjectBoundsLong(dom, vdomainObjectToSet(obj), &lbounds);
      else {
	vrectFromLong(&lbounds, &bounds);
	vdomainSetObjectBounds(dom, vdomainObjectToSet(obj), &bounds);
      }
      break;
    default:
      break;
    }
  }
  vdomainDestroyObjectSetIterator(&iterator);
  vdomainDestroyObjectSet(set);
}

/* _myDomainViewJobNoteProc
 *
 * the beginning of printing support.  this currently just prints a single
 * page.  in the future, it may scroll around the domain, printing multiple
 * pages which can be put together to form the big picture.
 */
static void _myDomainViewJobNoteProc(vprint * printer, int flag)
{
  myDomainView	*mview = (myDomainView *) vprintGetData(printer);
  myDomainView	*pview;
  vdomain	*domain = myDomainViewGetDomain(mview);
  vwindow	*window = (vwindow *) vprintGetDocumentOwner(printer);
  vrect		rect;
  const vrectLong *area;
  unsigned short pw, ph;	/* page width and height */

  if ((domain != NULL) && flag) {

    vwindowBlock(window);

    vrectFromFloat(vprintGetPage(printer), &rect);

    pview = myDomainViewClone(mview);
    myDomainViewSetSmartScrollbars(pview, vFALSE);
    vdomainviewSetHorzBar(myDomainViewGetView(pview), vFALSE);
    vdomainviewSetVertBar(myDomainViewGetView(pview), vFALSE);
    vdialogSetItemBorder(myDomainViewGetItem(pview), vFALSE);
    vdialogSetItemBackground(myDomainViewGetItem(pview), vcolorGetWhite());
    rect.x = rect.y = 36;
    rect.w -= 72;
    rect.h -= 72;
    pw = rect.w;
    ph = rect.h;
    area = vdomainviewGetViewableArea(myDomainViewGetView(pview));

    vexWITH_HANDLING {

      long		wleft, hleft;

      vprintOpenDocument(printer);
      hleft = area->h;
      do {				/* iterate over rows of pages*/
	/* size the item properly */
	rect.h = (hleft < rect.h) ? hleft : ph;
	vdialogSetItemRect(myDomainViewGetItem(pview), &rect);
	vdomainviewSetScrollTranslation(myDomainViewGetView(pview),
					0, area->h - hleft,
					(vdomainX_RELATIVE |
					 vdomainY_ABSOLUTE));
	wleft = area->w;
	do {				/* iterate over columns in row */
	  /* size the item properly */
	  rect.w = (wleft < rect.w) ? wleft : pw;
	  vdialogSetItemRect(myDomainViewGetItem(pview), &rect);
	  vdomainviewSetScrollTranslation(myDomainViewGetView(pview),
					  area->w - wleft, 0,
					  (vdomainX_ABSOLUTE |
					   vdomainY_RELATIVE));
	  vprintOpenPage(printer);
	  vdialogSetItemDraw(myDomainViewGetItem(pview));
	  vdomainviewDraw(myDomainViewGetView(pview));
	  vprintClosePage(printer);
	} while ((wleft -= rect.w) != 0);
      } while ((hleft -= rect.h) != 0);
      vprintCloseDocument(printer);

    } vexON_EXCEPTION {

      vdebugMWarn(("Printing generated an exception\n"));
      if (vprintPageIsOpen(printer))
	vprintClosePage(printer);
      if (vprintDocumentIsOpen(printer))
	vprintCloseDocument(printer);
#if (vdebugDEBUG)
      vexDumpChain(vdebugGetWarningStream());
#else
      vwindowBeep();
#endif
    } vexEND_HANDLING;

    vdomainviewSetDomain(myDomainViewGetView(pview), NULL);
    myDomainViewDestroy(pview);

    vwindowUnblock(window);

  }

  vobjectDestroyLater(vprintGetObject(printer));
}

static void _myDomainViewInit(myDomainView *mview)
{
  vdomain *domain;
  vdomainview *dview;
  int spam;

  vdebugTraceEnter(_myDomainViewInit);

  vclassSendSuper(_myDViewClass, vobjectINIT, (mview));
  mview->flags = DEFAULT_FLAGS;
  mview->selColor = vcolorGetWhite();
  dview = myDomainViewGetView(mview);
  domain = vdomainCreateOfClass(_myDomainClass);
  vdomainSetData(domain, (void *) dview);
  vdomainviewSetDomain(dview, domain);
  vdomainviewSetSelection(dview, vdomainCreateSelection(domain));
  vdomainviewSetDrawObjectProc(dview, _myDomainViewDrawObjectProc);
#ifdef MUST_IMPLEMENT_DRAW_SELECTION
  vdomainviewSetDrawSelectionProc(dview, _myDomainViewDrawSelection);
#endif /* MUST_IMPLEMENT_DRAW_SELECTION */

  vdomainviewSetHorzBar(dview, vTRUE);
  vdialogGetItemNaturalSize(vcontrolGetItem(vdomainviewGetHorzScrollbar(dview)),
			    &spam, &_hBarHeight);
  vdomainviewSetHorzBar(dview, vFALSE);

  vdomainviewSetVertBar(dview, vTRUE);
  vdialogGetItemNaturalSize(vcontrolGetItem(vdomainviewGetVertScrollbar(dview)),
			    &_vBarWidth, &spam);
  vdomainviewSetVertBar(dview, vFALSE);

  vdebugTraceLeave();
}

static void _myDomainViewLoadInit(myDomainView *mview, vresource res)
{
  vresource selColorRes;
  vdomainview *dview;
  vdomain *domain;
  vbool hasBar;
  int spam;

  vdebugTraceEnter(_myDomainViewLoadInit);

  vclassSendSuper(_myDViewClass, vobjectLOAD_INIT, (mview, res));

  mview->flags = DEFAULT_FLAGS;
  dview = myDomainViewGetView(mview);
  domain = vdomainCreateOfClass(_myDomainClass);
  vdomainSetData(domain, (void *) dview);
  vdomainviewSetDomain(dview, domain);
  vdomainviewSetSelection(dview, vdomainCreateSelection(domain));
  mview->selColor =
    vresourceTestGet(res, domnames_selColorSpec, &selColorRes) ?
      vcolorLoadIntern(selColorRes) : vcolorGetWhite();

  hasBar = vdomainviewHasHorzBar(dview);
  if (!hasBar)
    vdomainviewSetHorzBar(dview, vTRUE);
  vdialogGetItemNaturalSize(vcontrolGetItem(vdomainviewGetHorzScrollbar(dview)),
			    &spam, &_hBarHeight);
  if (!hasBar)
    vdomainviewSetHorzBar(dview, vFALSE);

  hasBar = vdomainviewHasVertBar(dview);
  if (!hasBar)
    vdomainviewSetVertBar(dview, vTRUE);
  vdialogGetItemNaturalSize(vcontrolGetItem(vdomainviewGetVertScrollbar(dview)),
			    &_vBarWidth, &spam);
  if (!hasBar)
    vdomainviewSetVertBar(dview, vFALSE);

  vdomainviewSetDrawObjectProc(dview, _myDomainViewDrawObjectProc);
#ifdef MUST_IMPLEMENT_DRAW_SELECTION
  vdomainviewSetDrawSelectionProc(dview, _myDomainViewDrawSelection);
#endif /* MUST_IMPLEMENT_DRAW_SELECTION */

  vdebugTraceLeave();
}

static void _myDomainViewDestroy(myDomainView *mview)
{
  vdomain *domain;

  domain = myDomainViewGetDomain(mview);
  vclassSendSuper(_myDViewClass, vobjectDESTROY, (mview));
  if (domain != NULL)
    vdomainDestroy(domain);
}

static void _myDomainViewChangedAttribute(myDomainView *mview,
					  const vname *attr,
					  vdict *context)
{
  vclassSendSuper(_myDViewClass, vobjectCHANGED_ATTRIBUTE,
		  (mview, attr, context));

  if (attr == vname_Font)
    _myDomainViewResizeTextObjects(mview);
}

static int _myDomainViewIssueSelector(myDomainView *mview, int selector,
				       vdict *context)
{
  int		retVal = vTRUE;
  vdomain	*domain = myDomainViewGetDomain(mview);
  vprint	*printer;

  if (domain == NULL)
    return vclassSendSuper(_myDViewClass, vobjectISSUE_SELECTOR,
			   (mview, selector, context));

  switch (selector) {
  case vdialogITEM_SELECT_DOWN:
    vdomainviewScroll(myDomainViewGetView(mview), 0, domain &&
		      vdomainGetOrientation(domain) == vdomainORIENT_TOP_LEFT ?
		      20 : -20, vdomainRELATIVE);
    break;
  case vdialogITEM_SELECT_UP:
    vdomainviewScroll(myDomainViewGetView(mview), 0, domain &&
		      vdomainGetOrientation(domain) == vdomainORIENT_TOP_LEFT ?
		      -20 : 20, vdomainRELATIVE);
    break;
  case vdialogITEM_SELECT_LEFT:
    vdomainviewScroll(myDomainViewGetView(mview), -20, 0, vdomainRELATIVE);
    break;
  case vdialogITEM_SELECT_RIGHT:
    vdomainviewScroll(myDomainViewGetView(mview), 20, 0, vdomainRELATIVE);
    break;
#if 0
  case vdomainviewSELECT_SELECT_ALL:
    /* the default selectAll for a domainview doesn't select hidden obejcts.
       this will. */
    vdomainSelectAll(myDomainViewGetDomain(mview),
		     vdomainviewGetSelection(myDomainViewGetView(mview)),
		     vTRUE, vTRUE);
    break;
#endif
  case vdialogITEM_SELECT_PRINT:
    printer = vprintCreate();
    vprintSetDocumentOwner(printer,
			   vwindowGetObject(vdialogDetermineItemWindow
					      (myDomainViewGetItem(mview))));
    vprintSetDocumentTitle(printer, vname_Domain);
    vprintSetJobNotify(printer, _myDomainViewJobNoteProc);
    vprintSetData(printer, mview);
    vprintConfirmJob(printer);
    break;
  default:
    retVal = vclassSendSuper(_myDViewClass, vobjectISSUE_SELECTOR,
			     (mview, selector, context));
    break;
  }

  return retVal;
}

static void _myDomainViewOpen(myDomainView *mview)
{
  vdomainview *dview = myDomainViewGetView(mview);
  vrect itemRect;
  vrectLong ldomBounds;
  short borderInset = vclassGet(_myDViewClass, vdomainviewBORDER_INSET);

  itemRect = *vdialogGetItemRect(vdomainviewGetItem(dview));

  vrectInset(&itemRect, borderInset, borderInset, &itemRect);
  ldomBounds.x = ldomBounds.y = 0.0;
  ldomBounds.w = itemRect.w;
  ldomBounds.h = itemRect.h;
  if (vdomainIsLong(vdomainviewGetDomain(dview)))
    vdomainSetBoundsLong(vdomainviewGetDomain(dview), &ldomBounds);
  else {
    vrect domBounds;
    vrectFromLong(&ldomBounds, &domBounds);
    vdomainSetBounds(vdomainviewGetDomain(dview), &domBounds);
  }

  vclassSendSuper(_myDViewClass, vdialogOPEN_ITEM, (mview));
  if (myDomainViewHasSmartScrollbars(mview))
    myDomainViewRecalcBars(mview);
}

static void _myDomainViewSetRect(myDomainView *mview, const vrect *rect)
{
  vclassSendSuper(_myDViewClass, vdialogSET_ITEM_RECT, (mview, rect));
  if (myDomainViewHasSmartScrollbars(mview))
    myDomainViewRecalcBars(mview);
  vapplicationChangedAttributeNone(vapplicationGetCurrent(),
				   domnames_DomainCoords);
}

/* _myDomainViewInvalRect
 *
 * since the background of the domainview is always being drawn, we can
 * safely make most invals opaque.  if offscreen drawing is off (which
 * makes 'em opaque for us) and the rect to be invalidated lies entirely
 * within the area of the domainview which is actually observing the domain,
 * make the inval opaque.
 */
static void _myDomainViewInvalRect(myDomainView *mview, const vrect *rect,
				   int flags)
{
  if (!vdomainviewIsOffscreenDrawing(myDomainViewGetView(mview)) &&
      vrectEncloses(vdomainviewGetDomainRect(myDomainViewGetView(mview)),
		    rect))
    flags |= vwindowINVAL_OPAQUE;

  vclassSendSuper(_myDViewClass, vdialogINVAL_ITEM_RECT,
		  (mview, rect, flags));
}

static void _myDomainInit(vdomain *dom)
{
  vdebugTraceEnter(_myDomainInit);

  vclassSendSuper(_myDomainClass, vobjectINIT, (dom));

  vdomainSetIntersectFunc(dom, _myDomainIntersectFunc);
  if (vdomainIsLong(dom))
    vdomainSetRectIntersectFuncLong(dom, _myDomainRectIntersectFuncLong);
  else
    vdomainSetRectIntersectFunc(dom, _myDomainRectIntersectFunc);

  vdebugTraceLeave();
}

static void _myDomainViewStartup(void)
{
  register myDomainViewClass *clas;
  register vdomainClass *dclas;
  register vdomainObserverClass *oclas;

  if (_myDViewClass != NULL)
    return;

  clas = vclassSpawn(vdomainviewGetDefaultClass(),
		     sizeof(myDomainViewClass));

  vclassSetNameScribed(clas, vcharScribeLiteral("myDomainView"));
  vclassSetObjectSize(clas, sizeof(myDomainView));
  vclassSet(clas, vobjectINIT,			_myDomainViewInit);
  vclassSet(clas, vobjectLOAD_INIT,		_myDomainViewLoadInit);
  vclassSet(clas, vobjectDESTROY,		_myDomainViewDestroy);
  vclassSet(clas, vobjectCHANGED_ATTRIBUTE,	_myDomainViewChangedAttribute);
  vclassSet(clas, vobjectISSUE_SELECTOR,	_myDomainViewIssueSelector);
  vclassSet(clas, vdialogOPEN_ITEM,		_myDomainViewOpen);
  vclassSet(clas, vdialogSET_ITEM_RECT,		_myDomainViewSetRect);
  vclassSet(clas, vdialogINVAL_ITEM_RECT,	_myDomainViewInvalRect);
  vclassSet(clas, vdomainviewBACKGROUND,	_myDomainViewBackground);
  vclassSet(clas, vdomainviewHANDLE_RESIZE_EVENT,
	    _myDomainViewHandleResizeEvent);
  vclassSet(clas, vdomainviewHANDLE_SCROLL_EVENT,
	    _myDomainViewHandleScrollEvent);
  vclassSet(clas, vdomainviewHANDLE_BUTTON_DOWN_EVENT,
	    _myDomainViewHandleButtonDownEvent);
  vclassSet(clas, vdomainviewHANDLE_BUTTON_UP_EVENT,
	    _myDomainViewHandleButtonUpEvent);
  vclassSet(clas, myDomainViewRECALC_BARS,	_myDomainViewRecalcBars);
  vclassSet(clas, myDomainViewSET_SMART_SCROLLBARS,
	    _myDomainViewSetSmartScrollbars);
  vclassSet(clas, myDomainViewSHOW_GRID_VERTICES,
	    _myDomainViewShowGridVertices);
  vclassSet(clas, myDomainViewSET_SEL_COLOR,	_myDomainViewSetSelColor);
  vclassSet(clas, myDomainViewSET_DRAG_ON_UNSELECTABLES,
	    _myDomainViewSetDragOnUnselectables);
  _myDViewClass = clas;

  dclas = vclassReproduce(vdomainGetDefaultLongClass());

  vclassSetNameScribed(dclas, vcharScribeLiteral("myDomain"));
  vclassSet(dclas, vobjectINIT,			_myDomainInit);
  _myDomainClass = dclas;

  oclas = vclassReproduce(vdomainGetDefaultObserverClass());

  vclassSetNameScribed(oclas, vcharScribeLiteral("myObserverClass"));
/*  vclassSet(oclas, vdomainObserverRESIZE_DOMAIN,	_myObserverResizeDomain);
  vclassSet(oclas, vdomainObserverRESIZE_DOMAIN_LONG,	_myObserverResizeDomainLong); */
  _myObserverClass = oclas;
}

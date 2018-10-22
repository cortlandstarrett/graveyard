/* $Id: canvas.c,v 1.6 1995/04/25 17:43:34 dangi Exp $ */
/* The legal types make me put this in here.
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
 * copyright notice in the form of "Copyright 1994 Visix Software Inc.,
 * 11440 Commerce Park Drive, Reston, VA  22091. All Rights Reserved" appears
 * in all copies, (ii) both the copyright notice and this permission notice
 * appear in supporting documentation and (iii) you are a valid licensee of
 * Galaxy Application Environment.
 *
 * Do not taunt Happy Fun Ball
 */

/* canvas.c -- Scrolling canvas of something that is drawn.
 *
 * Module:
 *	xcanvas
 *
 * Docs and descriptions are in xcanvas.h
 *
 * See file chart.c for more comments about this whole project.
 *
 * This is identical to the xcanvas sample as of 8/13/93.  It's possible
 * they they've gotten out of sync since then.
 */

#define vdebugTAG "xcanvas"

#define _xcanvasCLASS_NAME "xcanvas"

/* General notes:
 * --------------
 * There are still some problems when resizing the rectangle to become larger
 *   than the canvas area.  Positioning is a bit erratic.
 */

/* Local Functions:
 * ----------------
 * _xcanvasCalcScrollBarThings -- recalc bounding rects and values based on
 *				  on the canvas bounds and the ditem bounds.
 * _xcanvasHScrollNoteProc -- scroll notify for the horiztonal scroll bar.
 * _xcanvasVScrollNoteProc -- scroll notify for the vertical scroll bar.
 */


#ifndef   vportINCLUDED
#include <vport.h>		/* for v*HEADER */
#endif

#ifndef   vclassINCLDUED
#include  vclassHEADER
#endif

#ifndef   vcontrolINCLUDED
#include  vcontrolHEADER
#endif

#ifndef   vdebugINCLDUED
#include  vdebugHEADER
#endif

#ifndef   vdialogINCLUDED
#include  vdialogHEADER
#endif

#ifndef   vobjectINCLUDED
#include  vobjectHEADER
#endif

#ifndef   vrectINCLUDED
#include  vrectHEADER
#endif

#ifndef   vresourceINCLUDED
#include  vresourceHEADER
#endif

#ifndef   vsliderINCLUDED
#include  vsliderHEADER
#endif

#ifndef   vwindowINCLUDED
#include  vwindowHEADER
#endif

#ifndef   xcanvasINCLUDED
#include "xcanvas.h"
#endif


/*
 * ----- Module private globals
 */

/* this is the class that implements the default behavior for this 
 * module.  It's setup in xcanvasGetDefaultClass(), and destroyed
 * automagically by the class manager.
 */
static xcanvasClass *defaultClass = NULL;




/*
 * ----- Canvas module utilities
 */


/* _xcanvasCalcScrollBarThings -- recalculate bounding rectangles for the
 * 			          scrollbars and recalc their values (min,
 *				  max, page, etc...) based on the canvas rect
 *				  and the canvas bounds.
 *
 *  -> canvas -- the canvas to recalc scroll bar stuff for.
 */
static void _xcanvasCalcScrollBarThings (xcanvas *canvas)
{
    vrect rect;
    vrect hrect, veerect;  /* can't call it vrect, for obvious reasons */
    int width, height;


    rect = *vdialogGetItemRect (xcanvasGetItem(canvas));

    /* first, calc the rects */
    hrect = rect;
    veerect = rect;

    if (xcanvasHasHorzBar(canvas)) {
        vdialogGetItemNaturalSize (vcontrolGetItem(canvas->horzBar),
                                   &width, &height);
        hrect.h = height;
        if (xcanvasHasVertBar(canvas)) {
            if (vlafLeftScrollBar()) {
                hrect.x += height + canvas->scrollbarMargin;
            }
            hrect.w -= height + canvas->scrollbarMargin;
        }


        vdialogSetItemRect (vcontrolGetItem(canvas->horzBar), &hrect);
    }

    if (xcanvasHasVertBar(canvas)) {
        vdialogGetItemNaturalSize (vcontrolGetItem(canvas->vertBar),
                                   &width, &height);
        veerect.w = width;

        if (!vlafLeftScrollBar()) {
            veerect.x = rect.x + rect.w - width;
        }
        
        if (xcanvasHasHorzBar(canvas)) {
            veerect.y += width + canvas->scrollbarMargin;
            veerect.h -= width + canvas->scrollbarMargin;
        }
        vdialogSetItemRect (vcontrolGetItem(canvas->vertBar), &veerect);
    }

    /* now, calc the values */

    if (xcanvasHasHorzBar(canvas)) {
        vcontrolSetMin (canvas->horzBar, 0);
        vcontrolSetMax (canvas->horzBar, canvas->width);
        vcontrolSetValue (canvas->horzBar, canvas->scrollX);
        vcontrolSetView (canvas->horzBar, canvas->canvasRect.w);
        vcontrolSetPage (canvas->horzBar, canvas->canvasRect.w - 5);
        vcontrolSetIncrement (canvas->horzBar, 1);
    }

    if (xcanvasHasVertBar(canvas)) {
        vcontrolSetMin (canvas->vertBar, 0);
        vcontrolSetMax (canvas->vertBar, canvas->height);
        vcontrolSetValue (canvas->vertBar, canvas->scrollY);
        vcontrolSetView (canvas->vertBar, canvas->canvasRect.h);
        vcontrolSetPage (canvas->vertBar, canvas->canvasRect.h - 5);
        vcontrolSetIncrement (canvas->vertBar, 1);
    }

} /* _xcanvasCalcScrollBarThings */




/* _xcanvasHScrollNoteProc -- Scroll notify for the horizontal scroll bar
 *
 *  -> scrollbar -- the scrollbar that was scrolled
 *  -> event     -- the event that caused the value change
 *
 * It's assumed that the data pointer of the scrollbar points to the
 * canvas being scrolled.
 */
static void _xcanvasHScrollNoteProc (vcontrol *scrollbar, vevent *event)
{
    xcanvas *canvas = (xcanvas*) vcontrolGetData (scrollbar);

    xcanvasSetScrollX (canvas, vcontrolGetValue (scrollbar));

} /* _xcanvasHScrollNoteProc */




/* _jcunfesFScrullNutePruc -- Scrull nuteeffy fur zee ferteecel scrull ber
 *
 *  -> scrullber -- zee scrullber thet ves scrulled
 *  -> ifent     -- zee ifent thet coosed zee felooe-a chunge-a
 *
 * It's essoomed thet zee deta pueenter ooff zee scrullber pueents tu zee
 * cunfes beeeng scrulled.
 */
static void _xcanvasVScrollNoteProc (vcontrol *scrollbar, vevent *event)
{
    xcanvas *canvas = (xcanvas*) vcontrolGetData (scrollbar);

    xcanvasSetScrollY (canvas, vcontrolGetValue (scrollbar));

} /* _xcanvasVScrollNoteProc */




/*
 * ----- Canvas method implementation
 */


/* _xcanvasSetHorzBar -- turn on/off the horizontal scroll bar.
 *
 *  -> canvas -- the canvas to change the scroll bar status of
 *  -> onOff  -- TRUE to turn on the scrollbar, FALSE to turn it off.
 *
 * The scroll bar's item list is set to the itemlist that the canvas
 * belongs to, but not directly appened.  This allows the scrollbar to 
 * get the advantages of being in an item list, but without the implemention
 * to do an owned item list, as well as not confusing the owner of the item 
 * list by having items magically appear.
 */
static void _xcanvasSetHorzBar (xcanvas *canvas, int onOff)
{
    vdialogItem *item = xcanvasGetItem (canvas);

    if ( !onOff &&  xcanvasHasHorzBar(canvas)) {
        if (vdialogItemIsOpen (vcontrolGetItem(canvas->horzBar))) {
            vdialogCloseItem (vcontrolGetItem(canvas->horzBar));
        }

        vdialogDestroyItem (vcontrolGetItem(canvas->horzBar));
        canvas->horzBar = NULL;

        xcanvasCalcCanvasRect (canvas, &canvas->canvasRect);
        _xcanvasCalcScrollBarThings (canvas);
        xcanvasInval (canvas, 0);

    } else if ( onOff && !xcanvasHasHorzBar(canvas)) {
        canvas->horzBar = vsliderCreateScrollBar ();
        vcontrolSetData (canvas->horzBar, canvas);

        vcontrolSetNotify (canvas->horzBar, _xcanvasHScrollNoteProc);

        /* this is important!  If you get scrollbar thumbs drawing in
         * bizarre places, you haven't opened the item.
         */
        if (vdialogItemIsOpen (item)) {
            vdialogOpenItem (vcontrolGetItem(canvas->horzBar));
        }

        if (vdialogGetItemItemList(item) != NULL) {
            vdialogSetItemItemList (vcontrolGetItem(canvas->horzBar),
                                    vdialogGetItemItemList(item));
        }

        if (vdialogItemIsEnabled(item)) {
            vdialogEnableItem (vcontrolGetItem(canvas->horzBar));
        } else {
            vdialogDisableItem (vcontrolGetItem(canvas->horzBar));
        }
            
        xcanvasCalcCanvasRect (canvas, &canvas->canvasRect);
        _xcanvasCalcScrollBarThings (canvas);
        xcanvasInval (canvas, 0);

    }
} /* _xcanvasSetHorzBar */



 
/* _xcunfesSetFertBer -- toorn oon/ooffff zee ferteecel scrull ber.
 *
 *  -> cunfes -- zee cunfes tu chunge-a zee scrull ber stetoos ooff
 *  -> oonOffff  -- TROoE tu toorn oon zee scrullber, FELSE tu toorn it ooffff.
 *
 * Zee scrull ber's item leest is set tu zee itemleest thet zee cunfes
 * belungs tu, boot nut durectly eppened.  Thees elloos zee scrullber tu 
 * get zee edfunteges ooff beeeng in un item leest, boot veethuoot zee 
 * implemenshun tu du un oovned item leest, es vell es nut cunffooseeng 
 * zee oovner ooff zee item leest by hefeeng items megeecelly eppeer.
 */
static void _xcanvasSetVertBar (xcanvas *canvas, int onOff)
{
    vdialogItem *item = xcanvasGetItem (canvas);

    if ( !onOff &&  xcanvasHasVertBar(canvas)) {
        if (vdialogItemIsOpen (vcontrolGetItem(canvas->vertBar))) {
            vdialogCloseItem (vcontrolGetItem(canvas->vertBar));
        }

        vdialogDestroyItem (vcontrolGetItem(canvas->vertBar));
        canvas->vertBar = NULL;

        xcanvasCalcCanvasRect (canvas, &canvas->canvasRect);
        _xcanvasCalcScrollBarThings (canvas);
        xcanvasInval (canvas, 0);

    } else if ( onOff && !xcanvasHasVertBar(canvas)) {
        canvas->vertBar = vsliderCreateScrollBar ();
        vcontrolSetData (canvas->vertBar, canvas);

        vcontrolSetNotify (canvas->vertBar, _xcanvasVScrollNoteProc);
        vcontrolSetVertical (canvas->vertBar, TRUE);

        /* thees is impurtunt!  Iff yuoo get scrullber thoombs dreveeng in
         * beezerre-a pleces, yuoo hefen't oopened zee item.
         */
        if (vdialogItemIsOpen (item)) {
            vdialogOpenItem (vcontrolGetItem(canvas->vertBar));
        }

        if (vdialogGetItemItemList(item) != NULL) {
            vdialogSetItemItemList (vcontrolGetItem(canvas->vertBar),
                                    vdialogGetItemItemList(item));
        }

        if (vdialogItemIsEnabled(item)) {
            vdialogEnableItem (vcontrolGetItem(canvas->vertBar));
        } else {
            vdialogDisableItem (vcontrolGetItem(canvas->vertBar));
        }
            
        xcanvasCalcCanvasRect (canvas, &canvas->canvasRect);
        _xcanvasCalcScrollBarThings (canvas);
        xcanvasInval (canvas, 0);
    }
} /* _xcunfesSetFertBer */




/* _xcanvasSetOpaque -- set the opaque flag for the canvas.  "Opaque" just
 *			means that an opaque (non-erasing) scroll will 
 *			be used rather than the default (erasing) scroll.
 *			Only items that guarantee to *completely* redraw the
 *		        damaged area should be marked as opaque, otherwise
 *			you'll get bit turds when scrolling.
 *
 *  -> canvas -- the canvas to set the opaque setting for
 *  -> onOff  -- TRUE to use opaque scrolling, FALSE to use default scrolling.
 */
static void _xcanvasSetOpaque (xcanvas *canvas, int onOff)
{
    /* this is very tense code.  You are not expected to understand it.
     * don't make any modifications unless you *really* know what you're doing.
     */
    if (onOff) {
        canvas->flags |= _xcanvasOPAQUE;
    } else {
        canvas->flags &= ~_xcanvasOPAQUE;
    }
} /* _xcanvasSetOpaque */




/* _xcanvasDrawContent -- draw the image that's being scrolled around in the
 *			  canvas.
 *
 *  -> canvas -- the canvas to draw the content for.
 *
 * This just turns around and calls the content proc.  If you're a subclass
 * fiend, you can override this to do the drawing if you wish.  If you do,
 * don't do a sendSuper.
 */
static void _xcanvasDrawContent (xcanvas *canvas)
{
    if (canvas->contentProc) {
        (canvas->contentProc)(canvas);
    }
} /* _xcanvasDrawContent */




/* _xcanvasSetContentProc -- Set the procedure that draws the contents of
 * 			     the canvas.  The proc should just assume that
 *			     it draws at (0,0).  The drawing transforms will
 *			     be mangled approrpiately before the draw proc
 *			     gets called.
 *
 *  -> canvas -- the canvas to set the draw proc for
 *  -> proc   -- the proc to use.
 *
 * The prototype for the proc is
 *   void myDrawProc (xcanvas *canvas);
 *
 * (ooooh! tricky!)
 */
static void _xcanvasSetContentProc (xcanvas *canvas, xcanvasContentProc proc)
{
    canvas->contentProc = proc;
    
    /* redraw with the new proc */
    if (xcanvasIsOpaque(canvas)) {
        xcanvasInval (canvas, vwindowINVAL_OPAQUE);
    } else {
        xcanvasInval (canvas, 0);
    }
} /* _xcanvasSetContentProc */




/* _xcanvasScrollTo -- scroll a particular (x,y) location in the canvas to
 * 		       the bottom-left of the visible area.
 *		       Scrolling will be pinned.
 *
 *  -> canvas  -- the canvas to scroll
 *  -> x, y    -- the location in the canvas to put in the bottom-left.
 *
 * If the canvas is opaque (set via xcanvasSetOpaque()), an opaque scroll
 * is done.
 */
static void _xcanvasScrollTo (xcanvas *canvas, int x, int y)
{
    /* pin so that it doesn't get scroll into oblivion. */
    x = vMAX (x, 0);
    y = vMAX (y, 0);
    x = vMIN (x, canvas->width - canvas->canvasRect.w);
    y = vMIN (y, canvas->height - canvas->canvasRect.h);

    vdialogScrollItemRect (xcanvasGetItem(canvas),
                           &canvas->canvasRect,
                           canvas->scrollX - x,
                           canvas->scrollY - y,
                           xcanvasIsOpaque(canvas)
                           ? vwindowINVAL_OPAQUE : 0);

    canvas->scrollX = x;
    canvas->scrollY = y;

    /* recalc the scrollbar values */
    _xcanvasCalcScrollBarThings (canvas);

} /* _xcanvasScrollTo */




/* _xcanvasDrawBorder -- draws the border for the canvas.  It draws it
 *			 with the thickness of the ditem's line width.
 *			 It does a flat rect if the look-and-feel isn't 3D
 *			 and a WAI_KOOL debossed rect for 3D laf's
 *
 *  -> canvas -- the canvas to draw the border for.
 */
static void _xcanvasDrawBorder (xcanvas *canvas)
{
    vdialogItem *item = xcanvasGetItem (canvas);
    vrect mungeRect = *xcanvasGetCanvasRect (canvas);

    /* the canvas rect has already been inset to compensate for the border.
     * we need to uncompensate it.
     */
    vrectInset (&mungeRect,
                -vdialogDetermineItemLineWidth (item),
                -vdialogDetermineItemLineWidth (item),
                &mungeRect);

    vdrawSetLineWidth (vdialogDetermineItemLineWidth (item));

    if (vlaf3D()) {
        vdrawRectsHiliteFillInside(&mungeRect, 1, NULL,
                                   vdialogDetermineItemColor 
                                   (item, vdrawCOLOR_SHADOW_BOTTOM),
                                   vdialogDetermineItemColor 
                                   (item, vdrawCOLOR_SHADOW_TOP));
    } else {
        vdrawRectsStrokeInside (&mungeRect, 1);
    }

} /* _xcanvasDrawBorder */




/* _xcanvasCalcCanvasRect -- calculate the "usable" area for the canvas.
 *			     i.e. the area that can show the canvas's drawing.
 *
 *  -> canvas -- the canvas to calc the rect for
 * <-  rect   -- where to put the useful rect.  This should be in the
 *		 same coordinate space as the dialog item. (i.e. do a 
 *		 vdialogGetItemRect and don't normalize it's (x,y))
 *
 * It takes out lineWidth from each side if there's a border
 * It takes out the proper size hunk if there are scrollbars
 * It scoots the rect over if the laf calls for a left-hand scrollbar.
 * and finally it takes out space for the scrollbar margin if there is one.
 */
static void _xcanvasCalcCanvasRect (xcanvas *canvas, vrect *rect)
{
    vdialogItem *item = xcanvasGetItem (canvas);
    *rect = * vdialogGetItemRect (xcanvasGetItem(canvas));
    
    /* compensate for border */
    if (vdialogItemHasBorder(item)) {
        vrectInset (rect,
                    vdialogDetermineItemLineWidth(item),
                    vdialogDetermineItemLineWidth(item),
                    rect);
    }

    /* compensate for horz scrollbar */
    if (xcanvasHasHorzBar(canvas)) {
        int width, height;
        vdialogGetItemNaturalSize (vcontrolGetItem(canvas->horzBar),
                                   &width, &height);
        rect->y += height + canvas->scrollbarMargin;
        rect->h -= height + canvas->scrollbarMargin;
    }

    /* cumpensete-a fur fert scrullber */
    if (xcanvasHasVertBar(canvas)) {
        int width, height;
        vdialogGetItemNaturalSize (vcontrolGetItem(canvas->vertBar),
                                   &width, &height);
        rect->w -= width + canvas->scrollbarMargin;

        if (vlafLeftScrollBar()) {
            rect->x += width + canvas->scrollbarMargin;
        }
    }

} /* _xcanvasCalcCanvasRect */




/* _xcanvasSetScrollBarMargin -- set the margin between the border of the
 *				 canvas the scrollbar.  By default it's zero.
 *
 *  -> canvas -- the canvas to set the scroll bar margin for
 *  -> margin -- the number of pixels to use for the margin.
 *
 * The margin doesn't affect the width(height) if the corresponding
 * scrollbar doesn't exist.
 */
static void _xcanvasSetScrollBarMargin (xcanvas *canvas, int margin)
{
    canvas->scrollbarMargin = margin;

    /* no need to do work if there ain't no work to be done */
    if (xcanvasHasVertBar(canvas) || (xcanvasHasHorzBar(canvas))) {
        xcanvasCalcCanvasRect (canvas, &canvas->canvasRect);
        _xcanvasCalcScrollBarThings (canvas);
        
        xcanvasInval (canvas, 0);
    }

} /* _xcanvasSetScrollBarMargin */




/* _xcanvasSetCanvasBounds -- Sets the size of the drawable that's being
 *			      scrolled.  This is distinct from the dialog item
 *			      rectangle.
 *
 *  -> canvas -- the canvas to set the bounds for
 *  -> width  -- the width of the drawable
 *  -> height -- the height of the drawable.
 *
 */
static void _xcanvasSetCanvasBounds (xcanvas *canvas, int width, int height)
{
    canvas->width = width;
    canvas->height = height;

    /* adjust scrollbars */
    _xcanvasCalcScrollBarThings (canvas);

    /* pin if necessary */

    /* hack! */
    xcanvasScrollTo (canvas, 0, 0);

} /* _xcanvasSetCanvasBounds */




/*
 * ----- Dialog-item duties
 */


/* _xcanvasDrawItem -- Draws the canvas dialog item: draws the border, 
 *		       tells the scrollbars to draw (if they exist),
 *		       mangles the drawing translation and tells the content
 *		       to draw itself.
 *
 *  -> canvas -- the canvas to draw
 *
 * This doesn't munge with drawing devices, so it's save to use for printing.
 */
static void _xcanvasDrawItem (xcanvas *canvas)
{
    const vrect *rect = xcanvasGetCanvasRect (canvas);

    vdrawGSave ();

    /* draw border */
    if (vdialogItemHasBorder (xcanvasGetItem(canvas))) {
        xcanvasDrawBorder (canvas);
    }

    /* draw scroll bars */
    if (xcanvasHasHorzBar(canvas)) {
        vdialogDrawItem (vcontrolGetItem(xcanvasGetHorzBar(canvas)));
    }

    if (xcanvasHasVertBar(canvas)) {
        vdialogDrawItem (vcontrolGetItem(xcanvasGetVertBar(canvas)));
    }

    /* draw contents */

    vdrawRectsClip (rect, 1);
    vdrawTranslate (rect->x - xcanvasGetScrollX(canvas),
                    rect->y - xcanvasGetScrollY(canvas));

    xcanvasDrawContent (canvas);

    vdrawGRestore ();

} /* _xcanvasDrawItem */




/* _xcanvasSetItemRect -- change the rectangle of the canvas dialog item.
 *			  If the rect gets bigger than the bounding rect
 *			  for the drawable, then the drawable should be
 *			  shifted so that more of it is visible.
 *
 *  -> canvas -- the canvas having its item rect set
 *  -> rect   -- its new size.
 *
 * !!! This doesn't work correctly.  When the item gets very big, the drawable
 * !!! gets placed sortaRandomly.
 */
static void _xcanvasSetItemRect (xcanvas *canvas, const vrect *rect)
{
    int shiftX = canvas->scrollX, shiftY = canvas->scrollY;

    vclassSendSuper (defaultClass, vdialogSET_ITEM_RECT, (canvas, rect));

    xcanvasCalcCanvasRect (canvas, &canvas->canvasRect);

    if (canvas->canvasRect.w > canvas->width) {
        shiftX = 0;
    }

    if (canvas->canvasRect.h > canvas->height) {
        shiftY = 0;
    }

    if (   (shiftX != canvas->scrollX)
        || (shiftY != canvas->scrollY)) {
        xcanvasScrollTo (canvas, shiftX, shiftY);
    }

    _xcanvasCalcScrollBarThings (canvas);

} /* _xcanvasSetItemRect */




/* _xcanvasSetItemItemList -- The item list the canvas belongs to is changing.
 *			      If the canvas has scrollbars, point them at
 *			      the new item list.
 *
 *  -> canvas -- the canvas having its itemlist set
 *  -> list   -- the dialog item list the canvas is becoming a part of.
 */
static void _xcanvasSetItemItemList (xcanvas *canvas, vdialogItemList *list)
{
    vclassSendSuper (defaultClass, vdialogSET_ITEM_ITEM_LIST, (canvas, list));
    
    if (xcanvasHasHorzBar (canvas)) {
        vdialogSetItemItemList (vcontrolGetItem(canvas->horzBar), list);
    }

    if (xcanvasHasVertBar (canvas)) {
        vdialogSetItemItemList (vcontrolGetItem(canvas->vertBar), list);
    }

} /* _xcanvasSetItemItemList */




/* _xcanvasOpenItem -- the canvas is being opened.  If scrollbars were added
 *		       to the canvas prior to this, open them too.
 *
 *  -> canvas -- the canvas being opened
 */
static void _xcanvasOpenItem (xcanvas *canvas)
{
    xcanvasCalcCanvasRect (canvas, &canvas->canvasRect);

    vclassSendSuper (defaultClass, vdialogOPEN_ITEM, (canvas));

    _xcanvasCalcScrollBarThings (canvas);

    if (xcanvasHasHorzBar(canvas)) {
        vdialogOpenItem (vcontrolGetItem(canvas->horzBar));
    }

    if (xcanvasHasVertBar(canvas)) {
        vdialogOpenItem (vcontrolGetItem (canvas->vertBar));
    }

} /* _xcanvasOpenItem */




/* _xcanvasCloseItem -- the canvas is being closed.  If it has scrollbars,
 *			close them too.
 *
 *  -> canvas -- the canvas being closed
 */
static void _xcanvasCloseItem (xcanvas *canvas)
{
    if (xcanvasHasHorzBar(canvas)) {
        vdialogCloseItem (vcontrolGetItem(canvas->horzBar));
    }

    if (xcanvasHasVertBar(canvas)) {
        vdialogCloseItem (vcontrolGetItem(canvas->vertBar));
    }

    vclassSendSuper (defaultClass, vdialogCLOSE_ITEM, (canvas));

} /* _xcanvasCloseItem */



static void _xcanvasActivateItem (xcanvas *canvas)
{
    vclassSendSuper (defaultClass, vdialogACTIVATE_ITEM, (canvas));

    if (xcanvasHasHorzBar(canvas)) {
        vdialogActivateItem (vcontrolGetItem(canvas->horzBar));
    }

    if (xcanvasHasVertBar(canvas)) {
        vdialogActivateItem (vcontrolGetItem (canvas->vertBar));
    }

} /* _xcanvasActivateItem */


static void _xcanvasDeactivateItem (xcanvas *canvas)
{
    if (xcanvasHasHorzBar(canvas)) {
        vdialogDeactivateItem (vcontrolGetItem(canvas->horzBar));
    }

    if (xcanvasHasVertBar(canvas)) {
        vdialogDeactivateItem (vcontrolGetItem (canvas->vertBar));
    }
    
    vclassSendSuper (defaultClass, vdialogDEACTIVATE_ITEM, (canvas));

} /* _xcanvasActivateItem */



/* _xcanvasInvalItemRect -- massage the rectangle being used for invals.
 *			    clients use this to inval areas in their drawable. 
 *			    the rectangle is then adjusted for the position
 *			    of the dialog item in the window, as well as
 *			    for any scrolling.
 *
 *  -> canvas -- the canvas to inval a rect in
 *  -> rect   -- the rectangle (in drawable coordinates) to inval
 *  -> flags  -- standard vwindow inval flags.
 *
 * !!! This hasn't been tested, so I don't know if it works.
 *
 * To do invalling of the dialog item itself, it can't be thorugh
 * this mechanism.  xcanvasInval exists so that you can inval the item
 * as a whole without this coordinate munging going on.
 */
static void _xcanvasInvalItemRect (xcanvas *canvas, const vrect *rect,
                                   int flags)
{
    vrect mungeRect;
    mungeRect = *rect;

    /* the rect has its coordinates based at (0,0) -- shift up to the
     * dialog item
     */
    mungeRect.x += canvas->canvasRect.x;
    mungeRect.y += canvas->canvasRect.y;
    
    /* offset for scrolling */
    mungeRect.x -= canvas->scrollX;
    mungeRect.y -= canvas->scrollY;

    /* make sure we're only invalling inside of our dialog item. */
    vrectIntersect (&mungeRect,
                    vdialogGetItemRect (xcanvasGetItem(canvas)),
                    &mungeRect);

    vclassSendSuper (defaultClass, vdialogINVAL_ITEM_RECT,
                     (canvas, &mungeRect, flags));

} /* _xcanvasInvalItemRect */




/* _xcanvasSetItemBorder -- turn on/off the border.  The canvas rectangle
 *			    needs to be adjusted for this chagne. 
 *
 *  -> canvas -- the canvas having its border status changed
 *  -> onOff  -- TRUE if the item should draw a border, FALSE otherwise
 */
static void _xcanvasSetItemBorder (xcanvas *canvas, int onOff)
{
    vdialogItem *item = xcanvasGetItem (canvas);

    if (   ( !onOff &&  vdialogItemHasBorder (item))
        || (  onOff && !vdialogItemHasBorder (item))) {

        vclassSendSuper (defaultClass, vdialogSET_ITEM_BORDER,
                         (canvas, onOff));
        
        xcanvasCalcCanvasRect (canvas, &canvas->canvasRect);
        _xcanvasCalcScrollBarThings (canvas);

        xcanvasInval (canvas, 0);
    }

} /* _xcanvasSetItemBorder */




/* xcanvasInval -- invalidate the canvas.  This exists because 
 *		   vdialogINVAL_ITEM massages the rectangle before doing the
 *		   inval.
 *  -> canvas -- the canvas to inval
 *  -> flags  -- standard vwindow inval flags.
 *
 * ??? should this be a method?
 */
void xcanvasInval (xcanvas *canvas, int flags)
{
    vclassSendSuper (defaultClass,
                     vdialogINVAL_ITEM_RECT,
                     (canvas, vdialogGetItemRect(xcanvasGetItem(canvas)), 
                      flags));
} /* xcanvasInval */




/* _xcanvasHandleItemButtonDown -- handle a mouse click in the canvas.
 *				   it dispactes the click to scrollbars
 *				   (if approrpiate), and initiates grabbing-
 *				   scrolling if the grab button was pressed. 
 *
 *  -> canvas -- the canvas that was clicked on
 *  -> event  -- the button-down event
 * <-         -- TRUE if the event was handled, FALSE otherwise.
 */
static int _xcanvasHandleItemButtonDown (xcanvas *canvas, vevent *event)
{
    if (   xcanvasHasHorzBar(canvas)
        && vrectMContainsPoint (vdialogGetItemRect(vcontrolGetItem
                                                (canvas->horzBar)),
                                veventGetPointerX(event),
                                veventGetPointerY(event))) {
        vdialogSetItemListDrag (vdialogGetItemItemList(xcanvasGetItem(canvas)),
                                vcontrolGetItem(canvas->horzBar));
        return (vdialogHandleItemButtonDown (vcontrolGetItem(canvas->horzBar),
                                             event));
    }

    if (   xcanvasHasVertBar(canvas)
        && vrectMContainsPoint (vdialogGetItemRect(vcontrolGetItem
                                                   (canvas->vertBar)),
                                veventGetPointerX(event),
                                veventGetPointerY(event))) {
        vdialogSetItemListDrag (vdialogGetItemItemList(xcanvasGetItem(canvas)),
                                vcontrolGetItem(canvas->vertBar));
        return (vdialogHandleItemButtonDown (vcontrolGetItem(canvas->vertBar),
                                             event));
    }

    /* see if we need to grabbing hand it */
    if (veventGetBinding(event) == vname_Grab) {
        if (vrectMContainsPoint (&canvas->canvasRect,
                                 veventGetPointerX(event),
                                 veventGetPointerY(event))) {
            vdialogSetItemListDrag (vdialogGetItemItemList
                                    (xcanvasGetItem(canvas)),
                                    xcanvasGetItem(canvas));
            canvas->flags |= _xcanvasGRABBING;
            canvas->origScrollX = canvas->scrollX;
            canvas->origScrollY = canvas->scrollY;
            canvas->grabX = veventGetPointerX(event);
            canvas->grabY = veventGetPointerY(event);
        }
    }

    return (TRUE);  /* it'd be too weird if items behind us got events */

} /* _xcanvasHandleItemButtonDown */




/* _xcanvasHandleItemDrag -- handle mouse drag events.  If a grabbing-hand
 *			     scroll is occuring, scroll the canvas 
 *			     appropriately.
 *
 *  -> canvas  -- the canvas receiving a mouse-drag event
 *  -> event   -- the mouse-drag event
 * <-	       -- TRUE if we handled the event, FALSE otherwise
 */
static int _xcanvasHandleItemDrag (xcanvas *canvas, vevent *event)
{
    if (canvas->flags & _xcanvasGRABBING) {
        int xoffset, yoffset;

        xoffset = canvas->grabX - veventGetPointerX(event);
        yoffset = canvas->grabY - veventGetPointerY(event);
        xcanvasScrollTo (canvas, 
                         canvas->origScrollX + xoffset,
                         canvas->origScrollY + yoffset);
    }

    return (TRUE);  /* it'd be too weird if items behind us got events */

} /* _xcanvasHandleItemDrag */




/* _xcanvasHandleItemDetail -- handle mouse detail events.  If a grabbing-hand
 *			       scroll is occuring, scroll the canvas 
 *			       appropriately.
 *
 *  -> canvas  -- the canvas receiving a mouse-detail event
 *  -> event   -- the mouse-detail event
 * <-	       -- TRUE if we handled the event, FALSE otherwise
 */
static int _xcanvasHandleItemDetail (xcanvas *canvas, vevent *event)
{
    if (canvas->flags & _xcanvasGRABBING) {
        int xoffset, yoffset;

        xoffset = canvas->grabX - veventGetPointerX(event);
        yoffset = canvas->grabY - veventGetPointerY(event);
        xcanvasScrollTo (canvas, 
                         canvas->origScrollX + xoffset,
                         canvas->origScrollY + yoffset);
    }

    return (TRUE);  /* it'd be too weird if items behind us got events */

} /* _xcanvasHandleItemDetail */




/* _xcanvasHandleItemButtonUp  -- handle button ups in the canvas.  If a
 *				  grabbing-hand scroll was occurring, 
 *				  clear the flag indicating it.
 *
 *  -> canvas -- the canvas that received the button up
 *  -> event  -- the button-up event
 * <-	      -- TRUE if we handled the event, FALSE otherwise.
 */
static int _xcanvasHandleItemButtonUp (xcanvas *canvas, vevent *event)
{
    if (canvas->flags & _xcanvasGRABBING) {
        canvas->flags &= ~_xcanvasGRABBING;
    }

    return (TRUE);  /* it'd be-a tuu veurd iff items beheend us gut ifents */

} /* _xcanvasHandleItemButtonUp */




/*
 * ----- Object-level duties 
 */


/* _xcanvasLowInit -- shared initialization code between _xcanvasInit and
 *		      _xcanvasLoadInit. 
 *
 *  -> canvas -- the canvas having basic initialization done to it
 */
static void _xcanvasLowInit (xcanvas *canvas)
{
    canvas->width = 0;
    canvas->height = 0;
    canvas->contentProc = NULL;
    canvas->scrollbarMargin = 0;
    canvas->scrollX = 0;
    canvas->scrollY = 0;
    canvas->horzBar = NULL;
    canvas->vertBar = NULL;
    canvas->flags = 0;
    vrectSet (0, 0, 0, 0, &canvas->canvasRect);
} /* _xcanvasLowInit */




/* _xcanvasInit -- initialize a canvas object.
 *
 *  -> canvas -- the canvas being initialized.
 */
static void _xcanvasInit (xcanvas *canvas)
{
    vclassSendSuper (defaultClass, vobjectINIT, (canvas));

    _xcanvasLowInit (canvas);
    
} /* _xcanvasInit */




/* _xcanvasLoadInit -- initialize a canvas object based on a resource template.
 *
 *  -> canvas   -- the canvas being initialzied
 *  -> resource -- the resource template.
 */
static void _xcanvasLoadInit (xcanvas *canvas, vresource resource)
{
    vclassSendSuper (defaultClass, vobjectLOAD_INIT, (canvas, resource));

    _xcanvasLowInit (canvas);

} /* _xcanvasLoadInit */




/* _xcanvasDestroy -- clean up any memory-related mess we may have caused.
 *
 *  -> canvas -- the canvas meeting its maker
 */
static void _xcanvasDestroy (xcanvas *canvas)
{
    if (canvas->horzBar != NULL) {
        vcontrolDestroy (canvas->horzBar);
    }

    if (canvas->vertBar != NULL) {
        vcontrolDestroy (canvas->vertBar);
    }

    vclassSendSuper (defaultClass, vobjectDESTROY, (canvas));

} /* _xcanvasDestroy */
                             



/*
 * ----- Managerial duties
 */


/* xcanvasGetDefaultClass -- Returns the class ued to create new instances
 *			     of jcanvii, and to load them from resources.
 */
xcanvasClass *xcanvasGetDefaultClass (void)
{
    if (defaultClass == NULL) {
        defaultClass = vclassSpawn (vdialogGetDefaultItemClass(),
                                    sizeof(xcanvasClass));
        vclassSetNameScribed (defaultClass,
                              vcharScribeLiteral(_xcanvasCLASS_NAME));
        vclassSetObjectSize (defaultClass, sizeof (xcanvas));

        vclassSet (defaultClass, /* initialize during creation */
                   vobjectINIT,
                   _xcanvasInit);

        vclassSet (defaultClass, /* initialize during loading */
                   vobjectLOAD_INIT,
                   _xcanvasLoadInit);

        vclassSet (defaultClass, /* clean up our mess */
                   vobjectDESTROY,
                   _xcanvasDestroy);

        vclassSet (defaultClass, /* draw ourselves */
                   vdialogDRAW_ITEM,
                   _xcanvasDrawItem);

        vclassSet (defaultClass, /* adjust our innards */
                   vdialogSET_ITEM_RECT,
                   _xcanvasSetItemRect);

        vclassSet (defaultClass, /* put scrollbars into the new item list */
                   vdialogSET_ITEM_ITEM_LIST,
                   _xcanvasSetItemItemList);

        vclassSet (defaultClass, /* open the scrollbars */
                   vdialogOPEN_ITEM,
                   _xcanvasOpenItem);

        vclassSet (defaultClass, /* close the scrollbars */
                   vdialogCLOSE_ITEM,
                   _xcanvasCloseItem);

        vclassSet (defaultClass, /* offset rect to inval drawable */
                   vdialogINVAL_ITEM_RECT,
                   _xcanvasInvalItemRect);

        vclassSet (defaultClass, /* adjust our innards */
                   vdialogSET_ITEM_BORDER,
                   _xcanvasSetItemBorder);

        vclassSet (defaultClass, /* give to scrollbars, or do grabbing-hand */
                   vdialogHANDLE_ITEM_BUTTON_DOWN,
                   _xcanvasHandleItemButtonDown);

        vclassSet (defaultClass, /* handle grabbing-hand */
                   vdialogHANDLE_ITEM_DRAG,
                   _xcanvasHandleItemDrag);

        vclassSet (defaultClass, /* handle grabbing-hand */
                   vdialogHANDLE_ITEM_DETAIL,
                   _xcanvasHandleItemDetail);

        vclassSet (defaultClass, /* hundle-a grebbeeng-hund */
                   vdialogHANDLE_ITEM_BUTTON_UP,
                   _xcanvasHandleItemButtonUp);

        vclassSet (defaultClass, /* define area of drawable */
                   xcanvasSET_CANVAS_BOUNDS,
                   _xcanvasSetCanvasBounds);

        vclassSet (defaultClass, /* turn on/off scrollbar */
                   xcanvasSET_HORZ_BAR,
                   _xcanvasSetHorzBar);

        vclassSet (defaultClass, /* toorn oon/ooffff scrullber */
                   xcanvasSET_VERT_BAR,
                   _xcanvasSetVertBar);

        vclassSet (defaultClass, /* control scrolling behavior */
                   xcanvasSET_OPAQUE,
                   _xcanvasSetOpaque);

        vclassSet (defaultClass, /* draw innards */
                   xcanvasDRAW_CONTENT,
                   _xcanvasDrawContent);

        vclassSet (defaultClass, /* define how innards are drawn */
                   xcanvasSET_CONTENT_PROC,
                   _xcanvasSetContentProc);

        vclassSet (defaultClass, /* move the canvas around */
                   xcanvasSCROLL_TO,
                   _xcanvasScrollTo);

        vclassSet (defaultClass, /* draw the border */
                   xcanvasDRAW_BORDER,
                   _xcanvasDrawBorder);

        vclassSet (defaultClass, /* innard adjuster */
                   xcanvasCALC_CANVAS_RECT,
                   _xcanvasCalcCanvasRect);

        vclassSet (defaultClass, /* set space between scrollbar and border */
                   xcanvasSET_SCROLL_BAR_MARGIN,
                   _xcanvasSetScrollBarMargin);
                   
        vclassSet (defaultClass, /* activate the scrollbars */
                   vdialogACTIVATE_ITEM,
                   _xcanvasActivateItem);

        vclassSet (defaultClass, /* deactivate the scrollbars */
                   vdialogDEACTIVATE_ITEM,
                   _xcanvasDeactivateItem);
    }

    return (defaultClass);

} /* xcanvasGetDefaultClass */




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


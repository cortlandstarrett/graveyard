/* $Id: xcanvas.h,v 1.2 1993/11/30 19:41:42 markd Exp $ */
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

/* Module:
 *	xcanvas
 *
 * Description:
 *	See file chart.c for more comments about this whole project.
 *
 *	This module implements a scrolling canvas that can be drawn in
 *	and scrolled by the user.  The person(s) doing the drawing are
 *	obvlious to that fact.
 *      The drawing area is called a "drawable".  This can be of any
 *      width and height.  This is what's actually being scrolled.
 *	Scrollbars can be turned on and off, and grabbing-hand scrolling
 *	can be used too.
 *
 * 	This is identical to the xcanvas sample as of 8/13/93.  It's possible
 * 	they they've gotten out of sync since then.
 *
 * Exported Functions:
 *	xcanvasSetCanvasBounds -- set the width and height of the drawable
 *	xcanvasGetCanvasWidth -- get width of the bounds
 *	xcanvasGetCanvasHeight -- get height of the bounds
 *	xcanvasGetCanvasW -- shorthand for GetCanvasWidth
 *	xcanvasGetCanvasH -- shorthand for GetCanvasHeight
 *	
 *	xcanvasSetHorzBar -- turn on/off horizontal scroll bar
 *	xcanvasSetVertBar -- toorn oon/ooffff ferteecel scrull ber
 *	 
 *	xcanvasHasHorzBar -- does it have a horizontal scroll bar?
 *	xcanvasHasVertBar -- dues it hefe-a a ferteecel scrull ber?
 *	
 *	xcanvasGetHorzBar -- get the vcontrol for the horizontal scroll bar
 *	xcanvasGetVertBar -- get zee fcuntrul fur zee ferteecel scrull ber
 *
 *	xcanvasSetScrollX -- set horizontal scroll position
 *	xcanvasSetScrollY -- set ferteecel scrull puseeshun
 *	xcanvasGetScrollX -- get horizontal scroll position
 *	xcanvasGetScrollY -- get ferteecel scrull puseeshun
 *	xcanvasScrollTo -- scroll to an arbitrary place.
 *	
 *	xcanvasDrawBorder -- draw the border
 *	xcanvasCalcCanvasRect -- calculate the "usable" area for drawing
 *	xcanvasGetCanvasRect -- get the area where the drawable will be draw
 *			        (ditem rect minus scrollbars, border, margins)
 *	
 *	xcanvasSetScrollBarMargin -- set space between scroll bar and border
 *	xcanvasGetScrollBarMargin -- get the scroll bar margin
 *	
 *	xcanvasSetOpaque -- turn on/off opaque scrolls (vs erasing scrolls)
 *	xcanvasIsOpaque -- get status of canvas opaquemenss
 *	
 *	xcanvasInval -- inval the entire canvas dialog item
 *	
 *	xcanvasSetContentProc -- set the procedure that draws the canvas
 *				 contents
 *	xcanvasGetContentProc -- get the procedure that draws the canvas 
 *				 contents
 *	
 *	xcanvasGetDefaultClass -- get the default class / initialize it
 *	xcanvasGetClass -- get the class of a particular xcanvas
 *	
 *	xcanvasGetItem -- get the vdialogItem the canvas is based on
 *	xcanvasSetData -- set the client data for the dialog item
 *	xcanvasGetData -- get the client data for the dialog item
 *      
 *
 * How to use:
 *	* subclass vdialogItem in vre and name it "xcanvas"
 *	* and one of these puppers to your dialog
 *	* in your code, initialize the xcanvas class:
 *	  (void)xcanvasGetDefaultClass ();
 *
 *	* get ahold of a pointer to the canvas
 *	* specify how big the drawable will be
 *	   (say we've got a 500x500 image in the canvas)
 *	   xcanvasSetCanvasBounds (canvas, 500, 500);
 *
 *	* write the code to do the drawing
 *	   void myDrawThing (xcanvas *aCanvas) {
 *	      vdrawMoveTo (0, 0);  vdrawImageIdent (image);
 *	   }
 *	* and tell the canvas to use this code
 *	   xcanvasSetContentProc (canvas, myDrawThing);
 *
 *	* turn on scroll bars if you want
 *	   xcanvasSetHorzBar (canvas, TRUE);
 *	   xcanvasSetVertBar (canvas, TRUE);
 *
 *	* scroll to an arbitrary place if you want
 *	  (say we have something at (50, 40) in the image that we want to
 *	   be put in the bottom-left of the canvas)
 *	   xcanvasScrollTo (canvas, 50, 40);
 *
 *	* inval areas to be redrawn
 *	  (the rectangle being specified is in the *drawable*'s coordinates,
 *	   not the dialog item)
 *	   vrect rect; vrectSet (10, 10, 50, 100, &rect);
 *	   vdialogInvalItemRect (xcanvasGetItem(canvas), &rect, 0);
 *
 *	* if the drawable is opaque (it draws over whatever's there and never
 *	  lets previous contents show through, like a vdrawImageIdent), set
 *	  the opaque attribute to make scrolling smoother
 *	   xcanvasSetOpaque (canvas, TRUE);
 */

#ifndef xcanvasINCLUDED
#define xcanvasINCLUDED 1

#ifndef  vportINCLUDED
#include <vport.h>		/* for v*HEADER */
#endif

#ifndef  vclassINCLUDED
#include vclassHEADER
#endif

#ifndef  vcontrolINCLUDED
#include vcontrolHEADER
#endif

#ifndef  vdialogINCLUDED
#include vdialogHEADER
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C


/*
 * ---------- Constant and macro definitions ----------
 */

enum {
    _xcanvasGRABBING = 0x0001, /* are we currently grab-scrolling? */
    _xcanvasOPAQUE   = 0x0002  /* do opaque scrolling? */
};

/*
 * ---------- Type and structure definitions ----------
 */

typedef struct xcanvas xcanvas;

typedef void (*xcanvasContentProc) (xcanvas *canvas);
typedef void (*xcanvasNoteProc) (xcanvas *canvas, vevent *event);

struct xcanvas {  /* hands off, clients.  contents are private. */
    vdialogItem	       item;
    int		       width, height;
    xcanvasContentProc contentProc;
    vrect	       canvasRect;
    int 	       scrollbarMargin;
    int		       scrollX, scrollY;
    vcontrol	      *horzBar;
    vcontrol	      *vertBar;
    short	       flags;
    int		       grabX, grabY;  /* for grabbing-hand scrolling */
    int		       origScrollX, origScrollY; /* ditto */
};



#define xcanvasCLASS(SUPER, ITEM, NOTIFY, CONTENT_PROC) \
vdialogITEM_CLASS (SUPER, ITEM, NOTIFY); \
vclassMETHOD (xcanvasSET_HORZ_BAR, (ITEM *canvas, int onOff)); \
vclassMETHOD (xcanvasSET_VERT_BAR, (ITEM *canvas, int onOff)); \
vclassMETHOD (xcanvasDRAW_CONTENT, (ITEM *canvas)); \
vclassMETHOD (xcanvasSET_CONTENT_PROC, \
              (ITEM *canvas, CONTENT_PROC contentProc)); \
vclassMETHOD (xcanvasSCROLL_TO, (ITEM *canvas, int x, int y)); \
vclassMETHOD (xcanvasDRAW_BORDER, (ITEM *canvas)); \
vclassMETHOD (xcanvasCALC_CANVAS_RECT, (ITEM *canvas, vrect *rect)); \
vclassMETHOD (xcanvasSET_CANVAS_BOUNDS,  \
              (ITEM *canvas, int width, int height)); \
vclassMETHOD (xcanvasSET_SCROLL_BAR_MARGIN, (ITEM *canvas, int margin)); \
vclassMETHOD (xcanvasSET_OPAQUE, (ITEM *canvas, int onOff))

typedef struct xcanvasClass xcanvasClass;

struct xcanvasClass {
    xcanvasCLASS (xcanvasClass, xcanvas, 
                  xcanvasNoteProc, xcanvasContentProc);
};



/*
 * ---------- Module Prototypes ----------
 */

void xcanvasSetCanvasBounds (xcanvas *canvas, int width, int height);
int xcanvasGetCanvasW (xcanvas *canvas);
int xcanvasGetCanvasH (xcanvas *canvas);
int xcanvasGetCanvasWidth (xcanvas *canvas);
int xcanvasGetCanvasHeight (xcanvas *canvas);

void xcanvasSetHorzBar (xcanvas *canvas, int onOff);
void xcanvasSetVertBar (xcanvas *canvas, int onOff);

int xcanvasHasHorzBar (xcanvas *canvas);
int xcanvasHasVertBar (xcanvas *canvas);

vcontrol *xcanvasGetHorzBar (xcanvas *canvas);
vcontrol *xcanvasGetVertBar (xcanvas *canvas);

void xcanvasSetScrollX (xcanvas *canvas, int x);
void xcanvasSetScrollY (xcanvas *canvas, int y);
int xcanvasGetScrollX (xcanvas *canvas);
int xcanvasGetScrollY (xcanvas *canvas);
int xcanvasScrollTo   (xcanvas *canvas, int x, int y);

void xcanvasDrawBorder (xcanvas *canvas);
void xcanvasCalcCanvasRect (xcanvas *canvas, vrect *rect);
const vrect *xcanvasGetCanvasRect (xcanvas *canvas);

void xcanvasSetScrollBarMargin (xcanvas *canvas, int margin);
int xcanvasGetScrollBarMargin (xcanvas *canvas);

void xcanvasSetOpaque (xcanvas *canvas, int onOff);
int xcanvasIsOpaque (xcanvas *canvas);

void xcanvasInval (xcanvas *canvas, int flags);

/* the default xcanvasDRAW_CONTENT method turns around and calls
 * the contentProc field of the structure.  OO-maniacs who want to subclass
 * are welcome to */
void xcanvasSetContentProc (xcanvas *canvas, xcanvasContentProc proc);
xcanvasContentProc xcanvasGetContentProc (xcanvas *canvas);


xcanvasClass *xcanvasGetDefaultClass (void);
xcanvasClass *xcanvasGetClass (xcanvas *canvas);

vdialogItem *xcanvasGetItem (xcanvas *canvas);
void xcanvasSetData (xcanvas *canvas, void *data);
void *xcanvasGetData (xcanvas *canvas);



/*
 * ---------- Functions defined as #define defines ----------
 */

#define xcanvasGetCanvasH(c)	xcanvasGetCanvasHeight(c)
#define xcanvasGetCanvasW(c)	xcanvasGetCanvasWidth(c)

#define xcanvasGetCanvasHeight(c) ((c)->height)
#define xcanvasGetCanvasWidth(c) ((c)->width)

#define xcanvasHasHorzBar(c)	((c)->horzBar != NULL)
#define xcanvasHasVertBar(c)	((c)->vertBar != NULL)

#define xcanvasGetHorzBar(c)	((c)->horzBar)
#define xcanvasGetVertBar(c)	((c)->vertBar)

#define xcanvasGetScrollX(c)	((c)->scrollX)
#define xcanvasGetScrollY(c)	((c)->scrollY)

#define xcanvasSetScrollX(c,x)	(xcanvasScrollTo((c), (x), \
                                                 xcanvasGetScrollY((c))))
#define xcanvasSetScrollY(c,y)	(xcanvasScrollTo((c), \
                                                 xcanvasGetScrollX((c)), (y)))

#define xcanvasGetScrollBarMargin(c) ((c)->scrollbarMargin)

#define xcanvasGetContentProc(c) ((c)->contentProc)

#define xcanvasGetCanvasRect(c)	(&((c)->canvasRect))

#define xcanvasIsOpaque(c)	 ((c)->flags & _xcanvasOPAQUE)

#define xcanvasSetData(c,d)	  vdialogSetItemData(xcanvasGetItem((c)), (d))
#define xcanvasGetData(c)	  vdialogGetItemData(xcanvasGetItem((c)))

#define xcanvasGetItem(c)	  (&(c)->item)

#define xcanvasGetClass(c)	  ((xcanvasClass*) \
                                   vdialogGetItemClass \
                                   (xcanvasGetItem((c))))
#define xcanvasSend(c,s,a)	  vclassSend(xcanvasGetClass((c)), s, a)
#define xcanvasSendSuper(c,s,a)	  vclassSendSuper(xcanvasGetClass \
                                                   ((c)), s, a)


/*
 * ---------- Functions implemented by messages ----------
 */

#define xcanvasSetCanvasBounds(c,w,h) \
	xcanvasSend ((c), xcanvasSET_CANVAS_BOUNDS, (c,w,h))

#define xcanvasSetHorzBar(c,o) \
	xcanvasSend ((c), xcanvasSET_HORZ_BAR, (c,o))

#define xcanvasSetVertBar(c,o) \
	xcanvasSend ((c), xcanvasSET_VERT_BAR, (c,o))

#define xcanvasSetOpaque(c,o) \
	xcanvasSend ((c), xcanvasSET_OPAQUE, (c,o))

#define xcanvasDrawContent(c) \
	xcanvasSend ((c), xcanvasDRAW_CONTENT, (c))

#define xcanvasSetContentProc(c,p) \
	xcanvasSend ((c), xcanvasSET_CONTENT_PROC, (c,p))

#define xcanvasScrollTo(c, x, y) \
	xcanvasSend ((c), xcanvasSCROLL_TO, (c, x, y))

#define xcanvasDrawBorder(c) \
	xcanvasSend ((c), xcanvasDRAW_BORDER, (c))

#define xcanvasCalcCanvasRect(c, r) \
	xcanvasSend ((c), xcanvasCALC_CANVAS_RECT, (c,r))

#define xcanvasSetScrollBarMargin(c, m) \
	xcanvasSend ((c), xcanvasSET_SCROLL_BAR_MARGIN, (c,m))


vportEND_CPLUSPLUS_EXTERN_C

#endif /* xcanvasINCLUDED */


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


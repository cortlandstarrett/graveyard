/* $Id: gcitem.h,v 1.2 1993/11/30 19:35:40 markd Exp $ */
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

/* gcitem.h -- A dialog item that will draw a chartview
 *
 * Module:
 *	gchartitem
 *
 * Description:
 *	See file chart.c for more comments about this whole project.
 *
 *	This module implements a subclass of dialogItem (xcanvas, actually)
 *	that draws a given chartview and allows scrolling
 *
 *      Note that grabbing-hand scrolling is implemented, so be sure to tell
 *	your users!
 *
 * Exported Functions:
 *	gchartitemSetChartview -- associate a chartview with this item.
 *				  each chart item only displays/scrolls
 *				  a single chartview
 *	gchartitemGetChartview -- return the chartview that this item is
 *				  showing
 *	
 *	gchartitemSetChartSize -- set the size the chart should be.  note that
 *				  this is independent of the size of the 
 *				  chartitem displaying the chartview.  If this
 *				  rect is bigger than that chartitem's dialog
 *				  item rect, then scrolling can happen.
 *	
 *	gchartitemSetHorzBar -- Turn on/off the horizontal scroll bar
 *	gchartitemSetVertBar -- Turn on/off the vertical scroll bar
 *	
 *	gchartitemHasHorzBar -- returns the on/off state of the horzontal
 *				scroll bar
 *	gchartitemHasVertBar -- returns the on/off state of the vertical
 *				scroll bar
 *	
 *	gchartitemGetHorzBar -- returns the vcontrol that is the horizontal
 * 				scroll bar
 *	gchartitemGetVertBar -- returns the vcontrol that is the vertical
 *				scrollbar
 *	
 *	gchartitemGetItem -- returns the dialog item the chartitem is built
 *			     upon.  Please note that this item is not a
 *			     scrollbar
 *	gchartitemGetCanvas -- returns the xcanvas that this chartitem is
 *			     built upon.  Please note that this also is not a
 *			     scrollbar.
 *	
 *	gchartitemGetDefaultClass
 *	gchartitemGetClass
 *	
 *	gchartitemGetObject
 *	gchartitemCreate
 *	gchartitemCreateOfClass
 *	gchartitemDestroy
 *	gchartitemDump
 *
 *
 * How to use:
 *	* create it or get it from a dialog
 *	  gchartitem *chartitem = (gchartitem*)vdialogFindItem(dialog, ...);
 *
 *	* associate a chartview
 *	  gchartview *chartview = _getSomeChartviewFromSomewhere();
 *	  gchartitemSetChartview (chartitem, chartview);
 *
 *	* set the size of the chart guts
 *	  gchartitemSetChartSize (chartitem, 1000, 500);
 *
 *	* turn on scrollbars, if that turns you on
 *	  gchartitemSetHorzBar (chartitem, TRUE);
 *	  gchartitemSetVertBar (chartitem, TRUE);
 *
 *	* note that the chartitem does *not* destroy the chartview for you.
 */

#ifndef gcitemINCLUDED
#define gcitemINCLUDED 1

#ifndef  vportINCLUDED
#include <vport.h>		/* for v*HEADER */
#endif

#ifndef  vclassINCLUDED
#include vclassHEADER
#endif

#ifndef  vdialogINCLUDED
#include vdialogHEADER
#endif

#ifndef  veventINCLUDED
#include veventHEADER
#endif

#ifndef  vobjectINCLUDED
#include vobjectHEADER
#endif

#ifndef  gcviewINCLUDED
#include "gcview.h"
#endif

#ifndef  xcanvasINCLUDED
#include "xcanvas.h"
#endif




/*
 * ---------- Type and structure definitions ----------
 */


typedef struct gchartitem gchartitem;


/* dummies, really */
typedef void (*gchartitemContentProc) (gchartitem *item);
typedef void (*gchartitemNoteProc) (gchartitem *item, vevent *event);


struct gchartitem {
    xcanvas	canvas;
    gchartview *chartview;
};


#define gchartitemCLASS(SUPER, ITEM, NOTIFY, CONTENT_PROC, CHARTVIEW)	\
xcanvasCLASS (SUPER, ITEM, NOTIFY, CONTENT_PROC);			\
vclassMETHOD (gchartitemSET_CHARTVIEW,					\
              (ITEM *item, CHARTVIEW *view))


typedef struct gchartitemClass gchartitemClass;

struct gchartitemClass {
    gchartitemCLASS (gchartitemClass, gchartitem,
                     gchartitemNoteProc, gchartitemContentProc,
                     gchartview);
};




/*
 * ---------- Module Prototypes ----------
 */


void gchartitemSetChartview (gchartitem *item, gchartview *view);
gchartview *gchartitemGetChartview (gchartitem *item);

void gchartitemSetChartSize (gchartitem *item, int width, int height);

void gchartitemSetHorzBar (gchartitem *item, int onOff);
void gchartitemSetVertBar (gchartitem *item, int onOff);

int gchartitemHasHorzBar (gchartitem *item);
int gchartitemHasVertBar (gchartitem *item);

vcontrol *gchartitemGetHorzBar (gchartitem *item);
vcontrol *gchartitemGetVertBar (gchartitem *item);


vdialogItem *gchartitemGetItem (gchartitem *item);
xcanvas *gchartitemGetCanvas (gchartitem *item);

gchartitemClass *gchartitemGetDefaultClass (void);
gchartitemClass *gchartitemGetClass (gchartitem *item);

vobject *gchartitemGetObject (gchartitem *item);
gchartitem *gchartitemCreate (void);
gchartitem *gchartitemCreateOfClass (gchartitemClass *clas);
void gchartitemDestroy (gchartitem *item);
void gchartitemDump (gchartitem *item, FILE *stream);




/*
 * ---------- Functions defined as #define defines ----------
 */


#define gchartitemGetChartview(d)	((d)->chartview)

#define gchartitemGetCanvas(d)	( &((d)->canvas) )
#define gchartitemGetItem(d)	( xcanvasGetItem(gchartitemGetCanvas((d))))
#define gchartitemGetObject(d)	( vdialogGetItemObject(gchartitemGetItem \
                                                       ((d))))
#define gchartitemCreate()   gchartitemCreateOfClass(gchartitemGetDefaultClass\
                                                     ())
#define gchartitemCreateOfClass(c) ((gchartitem*)vobjectCreateOfClass \
                                   ((vobjectClass*)(c)))
#define gchartitemDestroy(d)	vobjectDestroy(gchartitemGetObject((d)))
#define gchartitemSetTag(d)	vobjectSetTag(gchartitemGetObject((d)))
#define gchartitemGetTag(d)	vobjectGetTag(gchartitemGetObject((d)))

#define gchartitemGetClass(d)	( (gchartitemClass*)vobjectGetClass \
                                 (gchartitemGetObject((d)))  )
#define gchartitemSend(o,s,a)	vclassSend(gchartitemGetClass((o)), s, a)

#define gchartitemSetChartSize(d,w,h) (xcanvasSetCanvasBounds \
                                       (gchartitemGetCanvas((d)), (w), (h)))

#define gchartitemSetHorzBar(d,o) (xcanvasSetHorzBar \
                                   (gchartitemGetCanvas((d)), o))
#define gchartitemSetVertBar(d,o) (xcanvasSetVertBar \
                                   (gchartitemGetCanvas((d)), o))

#define gchartitemHasHorzBar(d) (xcanvasHasHorzBar \
                                   (gchartitemGetCanvas((d))))
#define gchartitemHasVertBar(d) (xcanvasHasVertBar \
                                   (gchartitemGetCanvas((d))))
#define gchartitemGetHorzBar(d) (xcanvasGetHorzBar \
                                   (gchartitemGetCanvas((d))))
#define gchartitemGetVertBar(d) (xcanvasGetVertBar \
                                   (gchartitemGetCanvas((d))))



/*
 * ---------- Functions implemented by messages ----------
 */


#define gchartitemSetChartview(i,v)	\
	gchartitemSend ((i), gchartitemSET_CHARTVIEW, (i,v))


#endif /* gcitemINCLUDED */


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

/* $Id: gcview.h,v 1.2 1993/11/30 19:35:54 markd Exp $ */
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

/* gcview.h -- "container" for chart drawables
 *
 * Module:
 *	gchartview
 *
 * Description:
 *	See file chart.c for more comments about this whole project.
 *
 *	this module implements a continer-like object for chart drawawbles.
 *	It handles some of the dirty work of adjusting for axes and telling
 *	each drawable to draw itself.
 *
 *	This isn't a dialog item, but Yet Another Object that draws itself
 *	into a given rectangle.  Hence you could draw into a dialog item
 *	or domain item without having to futz around with item lists and all
 *	that nonsense.
 *
 *	For a dialog item that uses these, look for gchartitem
 *
 * Exported Functions:
 *	gchartviewDraw -- tell the chartview to draw each of the drawables
 *			  contained inside of it.
 *	
 *	gchartviewSetRect -- set the bounding rectangle for the entire 
 *			     chartview.  The drawables inside will be resized
 *			     approrpiately.
 *	gchartviewGetRect -- return the bounding rect for the chartview
 *
 *	gchartviewAddDrawable -- add a drawable to the chartview.  The new
 *				 drawable will be drawn on top of other 
 *				 drawables.
 *	gchartviewRemoveDrawable -- remove a particular drawable.  Does not
 *				    change the layer ordering of the surviving
 *				    drawwables.
 *	gchartviewGetDrawableAt -- returns the drawable at a particular index.
 *	
 *	gchartviewGetDrawableCount -- returns the number of drawables this
 *				      chartview owns.
 *	
 *	gchartviewAdjustMargins -- Adjust the left/right/top/bottom margins
 *				   of each of the drawables to compensate
 *				   for the axes and their locations of 
 *				   the other drawables.
 *	
 *	gchartviewGetDefaultClass
 *	gchartviewGetClass
 *	
 *	gchartviewGetObject
 *	
 *	gchartviewCreate
 *	gchartviewCreateOfClass
 *	gchartviewDestroy
 *	gchartviewSetTag
 *	gchartviewGetTag
 *	
 *	gchartviewDump
 *
 *
 * How to use:
 *	* create it
 *	  gchartview *chartview = gchartviewCreate ();
 *
 *	* use it
 *	  gchartviewAddDrawable (chartview, aDrawable);
 *	  gchartviewAddDrawable (chartview, anotherDrawable);
 *	  vrectSet (10, 10, 500, 1000, &someRect);
 *	  gchartviewSetRect (chartview, &someRect);
 *
 *	  when something wants it drawn, like a domain object or dialog item,
 *	  do a gchartviewDraw (chartview);
 *
 *	* destroy it
 *	  (be sure to destroy the drawables added to it)
 *	  gchartviewDestroy (chartview);
 */


#ifndef gcviewINCLUDED
#define gcviewINCLUDED 1

#ifndef  vportINCLUDED
#include <vport.h>		/* for v*HEADER */
#endif

#ifndef  vclassINCLUDED
#include vclassHEADER
#endif

#ifndef  vnameINCLUDED
#include vnameHEADER
#endif

#ifndef  vobjectINCLUDED
#include vobjectHEADER
#endif

#ifndef  vrectINCLUDED
#include vrectHEADER
#endif

#ifndef  gdrawbleINCLUDED
#include "gdrawble.h"
#endif




/*
 * ---------- Constant and macro definitions ----------
 */


enum {
    _gchartviewDIRTY = 0x0001
};




/*
 * ---------- Type and structure definitions ----------
 */


typedef struct gchartview gchartview;

struct gchartview {
    vobject	object;
    short 	flags;
    int		drawableCount;
    gdrawable **drawables;
    vrect	rect;
};


#define gchartviewCLASS(SUPER, CHARTVIEW, DRAWABLE)			\
vobjectCLASS     (SUPER, CHARTVIEW);					\
vclassMETHOD	 (gchartviewDRAW,					\
                  (CHARTVIEW *view));					\
vclassMETHOD	 (gchartviewSET_RECT,					\
                  (CHARTVIEW *view, const vrect *rect));		\
\
vclassMETHOD     (gchartviewADD_DRAWABLE,				\
                  (CHARTVIEW *view, DRAWABLE *drawable));		\
vclassMETHOD     (gchartviewREMOVE_DRAWABLE,				\
                  (CHARTVIEW *view, DRAWABLE *drawable));		\
vclassMETHOD_RET (gchartviewGET_DRAWABLE_AT, DRAWABLE *,		\
                  (CHARTVIEW *view, int at));				\
\
vclassMETHOD     (gchartviewADJUST_MARGINS,    				\
                  (CHARTVIEW *view))

typedef struct gchartviewClass gchartviewClass;

struct gchartviewClass {
    gchartviewCLASS (gchartviewClass, gchartview, gdrawable);
};




/*
 * ---------- Module Prototypes ----------
 */


void gchartviewDraw (gchartview *view);

void gchartviewSetRect (gchartview *view, const vrect *rect);
const vrect *gchartviewGetRect (gchartview *view);

void gchartviewAddDrawable (gchartview *view, gdrawable *drawable);
void gchartviewRemoveDrawable (gchartview *view, gdrawable *drawable);
gdrawable *gchartviewGetDrawableAt (gchartview *view, int at);

int gchartviewGetDrawableCount (gchartview *view);

void gchartviewAdjustMargins (gchartview *view);


gchartviewClass *gchartviewGetDefaultClass (void);
gchartviewClass *gchartviewGetClass (gchartview *view);

vobject *gchartviewGetObject (gchartview *view);

gchartview *gchartviewCreate (void);
gchartview *gchartviewCreateOfClass (gchartviewClass *clas);
void gchartviewDestroy (gchartview *view);
void gchartviewSetTag (gchartview *view, const vname *tag);
const vname *gchartviewGetTag (gchartview *view);

void gchartviewDump (gchartview *view, FILE *stream);




/*
 * ---------- Functions defined as #define defines ----------
 */


#define gchartviewGetRect(v)	       (&(v)->rect)
#define gchartviewGetDrawableCount(v)  ((v)->drawableCount)

#define gchartviewGetObject(d)	( &((d)->object) )
#define gchartviewCreate()   gchartviewCreateOfClass(gchartviewGetDefaultClass\
                                                     ())
#define gchartviewCreateOfClass(c) ((gchartview*)vobjectCreateOfClass \
                                   ((vobjectClass*)(c)))
#define gchartviewDestroy(d)	vobjectDestroy(gchartviewGetObject((d)))
#define gchartviewSetTag(d)	vobjectSetTag(gchartviewGetObject((d)))
#define gchartviewGetTag(d)	vobjectGetTag(gchartviewGetObject((d)))

#define gchartviewGetClass(d)	( (gchartviewClass*)vobjectGetClass \
                                 (gchartviewGetObject((d)))  )
#define gchartviewSend(o,s,a)	vclassSend(gchartviewGetClass((o)), s, a)




/*
 * ---------- Functions implemented by messages ----------
 */

#define gchartviewDraw(v) \
	gchartviewSend ((v), gchartviewDRAW, (v))

#define gchartviewSetRect(v,r) \
	gchartviewSend ((v), gchartviewSET_RECT, (v,r))

#define gchartviewAddDrawable(v,d) \
	gchartviewSend ((v), gchartviewADD_DRAWABLE, (v,d))

#define gchartviewRemoveDrawable(v,d) \
	gchartviewSend ((v), gchartviewREMOVE_DRAWABLE, (v,d))

#define gchartviewGetDrawableAt(v,i) \
	gchartviewSend ((v), gchartviewGET_DRAWABLE_AT, (v,i))

#define gchartviewAdjustMargins(v) \
	gchartviewSend ((v), gchartviewADJUST_MARGINS, (v))


#endif /* gcviewINCLUDED */


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

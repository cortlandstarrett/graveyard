/* $Id: gscatdr.h,v 1.2 1993/11/30 19:37:16 markd Exp $ */
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

/* gscatdr.h -- Interface to a chart drawable that does scatter charts.
 *
 * Module:
 *	gscatdraw.h
 *
 * Description:
 *	See file chart.c for more comments about this whole project.
 *
 *	this particular module draws a scatter chart for one data accessor.
 * 
 *	This is the Gary Gordon memorial manager
 *
 * 	The X axis values come from the accessor's index, the Y values come
 *	from the accessor's value.  They really should be two elements of an
 *	accessor vector.
 *
 * Exported Functions:
 *	 gscatdrawSetPointColor -- Set the color that scatter points will be
 *				   drawn in
 *	 gscatdrawGetPointColor -- Get the scatter point drawing color
 *
 *	 gscatdrawSetLabelColor -- Set the color that scatter point labels
 *				   will be drawn in.
 *	 gscatdrawGetLabelColor -- get the scatter point label color
 *
 *	 gscatdrawSetLabelFont -- Set the font that the scatter point labels
 *				  will be drawn in.
 *	 gscatdrawGetLabelFont -- get the font that the scatter points 
 *				  arrrgggh!  I can't take it anymore!
 *
 *	 gscatdrawSetPointDrawProc -- Set a procedure for drawing the points.
 *				      if no proc is specified, a hollow circle
 *				      will be drawn centered around the point.
 *	 gscatdrawGetPointDrawProc -- return the point drawing procedure, NULL
 *				      one hasn't been set.
 *	 gscatdrawDrawPoint -- actually invoke the code to draw the point
 *
 *	 gscatdrawDrawLabel -- Draw the label.  The rectangle that this
 *			       will draw in is calculated in the
 *			       gscatdrawPositionLabelRects.
 *
 *	 gscatdrawPositionLabelRects -- calculate the location of the bounding
 *					rects for the point labels.  
 *					By default, the rects are put to the
 *					right of the data point, unless it
 *					falls off the right edge.  Then
 *					it will be moved to the left of the 
 *					data point.  Doing a Good Job with
 *					this is an NP-Complete problem, so good
 *					luck!
 *	
 *	 gscatdrawCalcLabelSize -- Returns the width/height of a particular
 *				   label.
 *	 
 *	 gscatdrawSetPointSize -- Set the size to draw the data points
 *	 gscatdrawGetPointHeight -- get the points' height
 *	 gscatdrawGetPointWidth -- get the points' width.
 *	 
 *	 gscatdrawDump
 *	 
 *	 gscatdrawGetDefaultClass
 *	 gscatdrawGetClass
 *	 
 *	 gscatdrawGetObject
 *	 gscatdrawGetDrawable -- get the gdrawable object that underlies
 *				 the scatdraw.
 *	 gscatdrawCreate
 *	 gscatdrawCreateOfClass
 *	 gscatdrawDestroy
 *	 gscatdrawSetTag
 *	 gscatdrawGetTag
 *
 *	 There are also convenience functions for the entire drawable
 *	 API, but take gscatdraws instead of just drawables.
 *	 
 *
 * How to use:
 *	* Create one
 *	  gscatdraw *scatdraw = gscatdrawCreate ();
 *
 *	* Hook up an accessor to it. (the X axis values are from the index,
 *	  the Y axis values are the accessor value)
 *	  accessor = gspamaccCreate ();
 *	  gscatdrawAddAccessor (scatdraw, accessor);
 *
 *	* Set the color/font/point-size if you want
 *	  gscatdrawSetPointColor (scatdraw, color);
 *	  gscatdrawSetLabelColor (scatdraw, anotherColor);
 *	  gscatdrawSetLabelFont (scatdraw, someFontFromSomewhere);
 *
 *
 * Defaults:
 *	x/y axis size      -- 30 pixels
 *	default point size -- 9x9 pixels
 */


#ifndef gscatdrINCLUDED
#define gscatdrINCLUDED 1

#ifndef  vportINCLUDED
#include <vport.h>		/* for v*HEADER */
#endif

#ifndef  vclassINCLUDED
#include vclassHEADER
#endif

#ifndef  vcolorINCLUDED
#include vcolorHEADER
#endif

#ifndef  vfontINCLUDED
#include vfontHEADER
#endif

#ifndef  vnameINCLUDED
#include vnameHEADER
#endif

#ifndef  vobjectINCLUDED
#include vobjectHEADER
#endif

#ifndef  vpointINCLUDED
#include vpointHEADER
#endif

#ifndef  vrectINCLUDED
#include vrectHEADER
#endif

#ifndef  gaccessINCLUDED
#include "gaccess.h"
#endif

#ifndef  gdrawbleINCLUDED
#include "gdrawble.h"
#endif




/*
 * ---------- Constant and macro definitions ----------
 */


enum {
    _gscatdrawDIRTY	= 0x0001
};




/*
 * ---------- Type and structure definitions ----------
 */


typedef struct gscatdraw gscatdraw;

typedef void (*gscatdrawPointDrawProc) (gscatdraw *scat,
                                        int index, int vectorPos,
                                        int x, int y); /* center */

struct gscatdraw {
    gdrawable  drawable;
    short      flags;
    vpoint    *pointCache; /* set of point bounds */
    vrect     *labelCache; /* set of label rectangles */
    vcolor    *pointColor;
    vcolor    *labelColor;
    vfont     *labelFont;
    int	       pointWidth, pointHeight;

    gscatdrawPointDrawProc pointDrawProc;
};


#define gscatdrawCLASS(SUPER, DRAWABLE, ACCESSOR, POINT_DRAW_PROC)	     \
gdrawableCLASS (SUPER, DRAWABLE, ACCESSOR);				     \
vclassMETHOD (gscatdrawSET_POINT_COLOR,					     \
              (DRAWABLE *scat, vcolor *color));				     \
vclassMETHOD (gscatdrawSET_LABEL_COLOR,					     \
              (DRAWABLE *scat, vcolor *color));				     \
vclassMETHOD (gscatdrawSET_LABEL_FONT,					     \
              (DRAWABLE *scat, vfont *font));				     \
vclassMETHOD (gscatdrawSET_POINT_DRAW_PROC,				     \
              (DRAWABLE *scat, POINT_DRAW_PROC drawProc));		     \
vclassMETHOD (gscatdrawDRAW_POINT,					     \
              (DRAWABLE *scat, int index, int vectorPos, int x, int y));     \
vclassMETHOD (gscatdrawDRAW_LABEL,				     	     \
              (DRAWABLE *scat, int index, int vectorPos, const vrect *rect));\
vclassMETHOD (gscatdrawPOSITION_LABEL_RECTS,				     \
              (DRAWABLE *scat, const vpoint *points, vrect *labelRects,	     \
               int count, const vrect *bounds));			     \
vclassMETHOD (gscatdrawSET_POINT_SIZE,					     \
              (DRAWABLE *scat, int width, int height));			     \
vclassMETHOD (gscatdrawCALC_LABEL_SIZE,					     \
              (DRAWABLE *scat, int index, int vectorPos, 		     \
               int *width, int *height))

typedef struct gscatdrawClass gscatdrawClass;

struct gscatdrawClass {
    gscatdrawCLASS (gscatdrawClass, gscatdraw, gaccessor, 
                    gscatdrawPointDrawProc);
};




/*
 * ---------- Module Prototypes ----------
 */


void gscatdrawSetPointColor (gscatdraw *scat, vcolor *color);
vcolor *gscatdrawGetPointColor (gscatdraw *scat);

void gscatdrawSetLabelColor (gscatdraw *scat, vcolor *color);
vcolor *gscatdrawGetLabelColor (gscatdraw *scat);

void gscatdrawSetLabelFont (gscatdraw *scat, vfont *font);
vfont *gscatdrawGetLabelFont (gscatdraw *scat);

void gscatdrawSetPointDrawProc (gscatdraw *scat, gscatdrawPointDrawProc proc);
gscatdrawPointDrawProc gscatdrawGetPointDrawProc (gscatdraw *scat);
void gscatdrawDrawPoint (gscatdraw *scat, int index, int vectorPos, 
                         int x, int y);

void gscatdrawDrawLabel (gscatdraw *scat, int index, int vectorPos);

void gscatdrawPositionLabelRects (gscatdraw *scat, const vpoint *points, 
                                  vrect *labelRects, int count,
                                  const vrect *bounds);

void gscatdrawCalcLabelSize(gscatdraw *scat, int index, int vectorPos,
                             int *width, int *height);

void gscatdrawSetPointSize (gscatdraw *scat, int width, int height);
int gscatdrawGetPointHeight (gscatdraw *scat);
int gscatdrawGetPointWidth (gscatdraw *scat);

void gscatdrawDump (gscatdraw *scat, FILE *stream);


gscatdrawClass *gscatdrawGetDefaultClass (void);
gscatdrawClass *gscatdrawGetClass (gscatdraw *scat);

vobject *gscatdrawGetObject (gscatdraw *scat);
gdrawable *gscatdrawGetDrawable (gscatdraw *scat);

gscatdraw *gscatdrawCreate (void);
gscatdraw *gscatdrawCreateOfClass (gscatdrawClass *clas);
void gscatdrawDestroy (gscatdraw *scat);
void gscatdrawSetTag (gscatdraw *scat, const vname *tag);
const vname *gscatdrawGetTag (gscatdraw *scat);


/* conveniences */

void gscatdrawDraw (gscatdraw *scat);
void gscatdrawDrawXAxis (gscatdraw *scat);
void gscatdrawDrawYAxis (gscatdraw *scat);
void gscatdrawDrawLegend (gscatdraw *scat, const vrect *rect);

void gscatdrawSetRect (gscatdraw *scat, const vrect *rect);
const vrect *gscatdrawGetRect (gscatdraw *scat);

void gscatdrawSetXPos (gscatdraw *scat, int position);
int gscatdrawGetXPos (gscatdraw *scat, int position);

void gscatdrawSetYPos (gscatdraw *scat, int position);
int gscatdrawGetYPos (gscatdraw *scat, int position);


void gscatdrawSetContinuousX (gscatdraw *scat, int onOff);
int gscatdrawGetContinuousX (gscatdraw *scat);

void gscatdrawSetContinuousY (gscatdraw *scat, int onOff);
int gscatdrawGetContinuousY (gscatdraw *scat);

int gscatdrawIsXContinuous (gscatdraw *scat);
int gscatdrawIsXDiscrete (gscatdraw *scat);
int gscatdrawIsYContinuous (gscatdraw *scat);
int gscatdrawIsYDiscrete (gscatdraw *scat);

void gscatdrawSetDrawX (gscatdraw *scat, int onOff);
int gscatdrawGetDrawX (gscatdraw *scat);

void gscatdrawSetDrawY (gscatdraw *scat, int onOff);
int gscatdrawGetDrawY (gscatdraw *scat);

void gscatdrawSetDrawableMargins (gscatdraw *scat,
                                  int topMargin, int leftMargin,
                                  int bottomMargin, int rightMargin);
void gscatdrawGetDrawableMargins (gscatdraw *scat, 
                                  int *topMargin, int *leftMargin,
                                  int *bottomMargin, int *rightMargin);

void gscatdrawSetTopMargin (gscatdraw *scat, int topMargin);
void gscatdrawSetLeftMargin (gscatdraw *scat, int leftMargin);
void gscatdrawSetBottomMargin (gscatdraw *scat, int bottomMargin);
void gscatdrawSetRightMargin (gscatdraw *scat, int rightMargin);

int gscatdrawGetTopMargin (gscatdraw *scat);
int gscatdrawGetLeftMargin (gscatdraw *scat);
int gscatdrawGetBottomMargin (gscatdraw *scat);
int gscatdrawGetRightMargin (gscatdraw *scat);

void gscatdrawGetNaturalAxisSize (gscatdraw *scat,
                                  int *xheight, int *ywidth);

void gscatdrawGetRatio (gscatdraw *scat, int *width, int *height);

void gscatdrawAddAccessor (gscatdraw *scat, gaccessor *accessor);
void gscatdrawRemoveAccessor (gscatdraw *scat, gaccessor *accessor);
int gscatdrawGetAccessorCount (gscatdraw *scat);
gaccessor *gscatdrawGetAccessorAt (gscatdraw *scat, gaccessor *accessor);
int gscatdrawInUpButt (gscatdraw *scat);

void gscatdrawGetLegendNaturalSize (gscatdraw *scat, int *width, int *height);




/*
 * ---------- Functions defined as #define defines ----------
 */


#define gscatdrawGetPointColor(d)	((d)->pointColor)
#define gscatdrawGetLabelColor(d)	((d)->labelColor)
#define gscatdrawGetLabelFont(d)	((d)->labelFont)
#define gscatdrawGetPointDrawProc(d) 	((d)->pointDrawProc)
#define gscatdrawGetPointHeight(d)	((d)->pointHeight)
#define gscatdrawGetPointWidth(d)	((d)->pointWidth)

#define gscatdrawGetDrawable(d)	( &((d)->drawable))
#define gscatdrawGetObject(d)	(gdrawableGetObject(gscatdrawGetDrawable((d))))
#define gscatdrawCreate()   gscatdrawCreateOfClass(gscatdrawGetDefaultClass())
#define gscatdrawCreateOfClass(c) ((gscatdraw*)vobjectCreateOfClass \
                                   ((vobjectClass*)(c)))
#define gscatdrawDestroy(d)	vobjectDestroy(gscatdrawGetObject((d)))
#define gscatdrawSetTag(d)	vobjectSetTag(gscatdrawGetObject((d)))
#define gscatdrawGetTag(d)	vobjectGetTag(gscatdrawGetObject((d)))

#define gscatdrawGetClass(d)	( (gscatdrawClass*)vobjectGetClass \
                                 (gscatdrawGetObject((d)))  )
#define gscatdrawSend(o,s,a)	vclassSend(gscatdrawGetClass((o)), s, a)


/* conveniences */

#define gscatdrawDraw(d)	gdrawableDraw(gscatdrawGetDrawable((d)))
#define gscatdrawDrawXAxis(d)	gdrawableDrawXAxis(gscatdrawGetDrawable((d)))
#define gscatdrawDrawYAxis(d)	gdrawableDrawYAxis(gscatdrawGetDrawable((d)))
#define gscatdrawDrawLegend(d,r) (gdrawableDrawLegend \
                                  (gscatdrawGetDrawable((d)),(r)))

#define gscatdrawSetRect(d,r)   gdrawableSetRect(gscatdrawGetDrawable((d)),(r))
#define gscatdrawGetRect(d)     gdrawableGetRect(gscatdrawGetDrawable((d)))
#define gscatdrawSetXPos(d,p)   gdrawableSetXPos(gscatdrawGetDrawable((d)),(p))
#define gscatdrawGetXPos(d)     gdrawableGetXPos(gscatdrawGetDrawable((d)))

#define gscatdrawSetYPos(d,p)   gdrawableSetYPos(gscatdrawGetDrawable((d)),(p))
#define gscatdrawGetYPos(d)     gdrawableGetYPos(gscatdrawGetDrawable((d)))

#define gscatdrawSetDrawX(d,o)   gdrawableSetDrawX(gscatdrawGetDrawable((d)), \
                                                   (o))
#define gscatdrawGetDrawX(d)     gdrawableGetDrawX(gscatdrawGetDrawable((d)))

#define gscatdrawSetDrawY(d,o)   gdrawableSetDrawY(gscatdrawGetDrawable((d)), \
                                                   (o))
#define gscatdrawGetDrawY(d)     gdrawableGetDrawY(gscatdrawGetDrawable((d)))

#define gscatdrawGetRatio(d,w,h) gdrawableGetRatio(gscatdrawGetDrawable((d)), \
                                                   (w),(h))

#define gscatdrawAddAccessor(d,a) (gdrawableAddAccessor \
                                   (gscatdrawGetDrawable((d)),(a)))
#define gscatdrawRemoveAccessor(d,a) (gdrawableRemoveAccessor \
                                      (gscatdrawGetDrawable((d)),(a)))
#define gscatdrawGetAccessorCount(d) (gdrawableGetAccessorCount \
                                      (gscatdrawGetDrawable((d))))
#define gscatdrawGetAccessorAt(d,a)  (gdrawableGetAccessorAt \
                                      (gscatdrawGetDrawable((d)),(a)))
#define gscatdrawGetLegendNaturalSize(d,w,h) (gdrawableGetLegndNaturalSize \
                                              (gscatdrawGetDrawable((d)), \
                                               (w),(h)))

#define gscatdrawSetDrawableMargins(d,t,l,b,r)  (gdrawableSetDrawableMargins \
                                                 (gscatdrawGetDrawable((d)), \
                                                  (t),(l),(b),(r)))

#define gscatdrawGetDrawableMargins(d,t,l,b,r)  (gdrawableGetDrawableMargins \
                                                 (gscatdrawGetDrawable((d)), \
                                                  (t),(l),(b),(r)))

#define gscatdrawSetMarginSpace(d,x,y) (gdrawableSetMarginSpace \
                                        (gscatdrawGetDrawable((d)), \
                                         (x),(y)))

#define gscatdrawGetMarginSpace(d,x,y) gdrawableGetMarginSpace \
                                        (gscatdrawGetDrawable((d)), \
                                         (x),(y))

#define gscatdrawSetTopMargin(d,m)  (gdrawableSetTopMargin    \
                                     (gscatdrawGetDrawable((d)),(m)))
#define gscatdrawSetLeftMargin(d,m)  (gdrawableSetLeftMargin    \
                                      (gscatdrawGetDrawable((d)), (m)))
#define gscatdrawSetBottomMargin(d,m)  (gdrawableSetBottomMargin    \
                                        (gscatdrawGetDrawable((d)), (m)))
#define gscatdrawSetRightMargin(d,m)  (gdrawableSetRightmargin    \
                                       (gscatdrawGetDrawable((d)), (m)))
                                       
#define gscatdrawGetTopMargin(d)  (gdrawableGetTopMargin    \
                                   (gscatdrawGetDrawable((d))))
#define gscatdrawGetLeftMargin(d)  (gdrawableGetLeftMargin    \
                                    (gscatdrawGetDrawable((d))))
#define gscatdrawGetBottomMargin(d)  (gdrawableGetBottomMargin    \
                                      (gscatdrawGetDrawable((d))))
#define gscatdrawGetRightMargin(d)  (gdrawableGetRightMargin    \
                                     (gscatdrawGetDrawable((d))))

#define gscatdrawGetNaturalAxisSize(d,x,y)  (gdrawableGetNaturalAxisSize    \
                                             (gscatdrawGetDrawable((d)),    \
                                              (x),(y)))

#define gscatdrawSetContinuousX(d,o)	(gdrawableSetContinuousX	\
                                         (gscatdrawGetDrawable((d)), (o)))
#define gscatdrawGetContinuousX(d)	(gdrawableGetContinuousX	\
                                         (gscatdrawGetDrawable((d))))
#define gscatdrawSetContinuousY(d,o)	(gdrawableSetContinuousY	\
                                         (gscatdrawGetDrawable((d)), (o)))
#define gscatdrawGetContinuousY(d)	(gdrawableGetContinuousY	\
                                         (gscatdrawGetDrawable((d))))
#define gscatdrawIsXContinuous(d)	(gdrawableIsXContinuous	\
                                         (gscatdrawGetDrawable((d))))
#define gscatdrawIsXDiscrete(d)		(gdrawableIsXDiscrete	\
                                         (gscatdrawGetDrawable((d))))
#define gscatdrawIsYContinuous(d)	(gdrawableIsYContinuous	\
                                         (gscatdrawGetDrawable((d))))
#define gscatdrawIsYDiscrete(d)		(gdrawableIsYDiscrete	\
                                         (gscatdrawGetDrawable((d))))



/*
 * ---------- Functions implemented by messages ----------
 */


#define gscatdrawSetPointColor(d,c) \
	gscatdrawSend((d), gscatdrawSET_POINT_COLOR, (d,c))

#define gscatdrawSetLabelColor(d,c) \
	gscatdrawSend((d), gscatdrawSET_LABEL_COLOR, (d,c))

#define gscatdrawSetLabelFont(d,f) \
	gscatdrawSend((d), gscatdrawSET_LABEL_FONT, (d,f))

#define gscatdrawSetPointDrawProc(d,p) \
	gscatdrawSend((d), gscatdrawSET_POINT_DRAW_PROC, (d,p))

#define gscatdrawDrawPoint(d,i,v,x,y) \
	gscatdrawSend((d), gscatdrawDRAW_POINT, (d,i,v,x,y))

#define gscatdrawDrawLabel(d,i,v,r) \
	gscatdrawSend((d), gscatdrawDRAW_LABEL, (d,i,v,r))

#define gscatdrawPositionLabelRects(d,p,l,c,b) \
	gscatdrawSend((d), gscatdrawPOSITION_LABEL_RECTS, (d,p,l,c,b))

#define gscatdrawSetPointSize(d,w,h) \
	gscatdrawSend((d), gscatdrawSET_POINT_SIZE, (d,w,h))

#define gscatdrawCalcLabelSize(d,i,v,w,h) \
	gscatdrawSend((d), gscatdrawCALC_LABEL_SIZE, (d,i,v,w,h))

#endif /* gscatdrINCLUDED */


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

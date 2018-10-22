/* $Id: glinedr.h,v 1.2 1993/11/30 19:36:41 markd Exp $ */
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

/* glinedr.h -- Interface to a chart drawable that does line charts.
 *
 * Module:
 *	glinedraw
 *
 * Description:
 *	See file chart.c for more comments about this whole project.
 *
 *	this particular module draws a single line chart for one data accessor.
 *
 * Exported Functions:
 *	 glinedrawSetLineColor -- Set the color to be used to draw the line
 *	 glinedrawGetLineColor -- Get the color used to draw the line
 *	 
 *	 glinedrawSetLineDash -- Set the dash pattern to be used to draw the
 *				 line. (see docs for vdrawFSetDash)
 *	 glinedrawGetLineDash -- returns the various parameters for the line
 *				 dash.
 *	 
 *	 glinedrawSetLineWidth -- set the line width to be used to draw the
 *				  line
 *	 glinedrawGetLineWidth -- returns the line width used to draw the line.
 *	 
 *	 glinedrawSetPointDrawProc -- set a draw proc that gets called for
 *				      each point, allowing for little pictures
 *				      to be drawn at each point.
 *	 glinedrawGetPointDrawProc -- returns the point draw proc
 *	 glinedrawDrawPoint -- call the draw proc for a particular point
 *	 
 *	 glinedrawSetLineForm -- set the form (point-to-point or step-wise) 
 *				 of the line.
 *	 glinedrawGetLineForm -- returns the line form
 *	 
 *	 glinedrawGetDefaultClass
 *	 glinedrawGetClass 
 *	 
 *	 glinedrawGetObject 
 *	 glinedrawGetDrawable -- returns the drawable the line chart was 
 *				 built in.
 *	 
 *	 glinedrawCreate
 *	 glinedrawCreateOfClass
 *	 glinedrawDestroy 
 *	 glinedrawSetTag
 *	 glinedrawGetTag
 *	 glinedrawDump
 *
 *	 There are also convenience functions for the entire drawable
 *	 API, but take glinedraws instead of just drawables.
 *	 
 *
 * How to use:
 *	* Create one
 *	  glinedraw *linedraw = glinedrawCreate ();
 *
 *	* Hook up an accessor to it
 *	  accessor = glistaccCreate (); ...
 *	  glinedrawAddAccessor (linedraw, accessor);
 *
 *	* Set the color if you want
 *	  glinedrawSetLineColor (linedraw, someColor);
 *
 *	* Set the dash too if you want.
 *	  float thignie[2]
 *        thingie[0] = 20; \* on  *\
 *        thingie[1] = 5;  \* off *\
 *        glinedrawSetLineDash (linedraw, 2, thingie, 0);
 *
 *
 * Defaults:
 *	x/y axis size -- 30 pixels (number taken out of thin air)
 *	legend size -- 100 wide 20 high. (really should be computed based on
 *		       font/title/etc)
 */


#ifndef glinedrINCLUDED
#define glinedrINCLUDED 1

#ifndef   vportINCLUDED
#include <vport.h>		/* for v*HEADER */
#endif

#ifndef   vclassINCLUDED
#include  vclassHEADER
#endif

#ifndef   vcolorINCLUDED
#include  vcolorHEADER
#endif

#ifndef   vnameINCLUDED
#include  vnameHEADER
#endif

#ifndef   vobjectINCLUDED
#include  vobjectHEADER
#endif

#ifndef   vrectINCLUDED
#include  vrectHEADER
#endif

#ifndef   gaccessINCLUDED
#include "gaccess.h"
#endif

#ifndef   gdrawbleINCLUDED
#include "gdrawble.h"
#endif




/*
 * ---------- Constant and macro definitions ----------
 */


enum {
    glinedrawPOINT_TO_POINT     = 0x0001,
    glinedrawSTEP_FORM		= 0x0002,
    _glinedrawLINE_FORM		= glinedrawPOINT_TO_POINT | glinedrawSTEP_FORM,
    _glinedrawHAS_DASH		= 0x0004
};




/*
 * ---------- Type and structure definitions ----------
 */


typedef struct glinedraw glinedraw;

typedef void (*glinedrawPointDrawProc) (glinedraw *line,
                                        int index, int vectorPos,
                                        int x, int y); /* center */

struct glinedraw {
    gdrawable	drawable;
    short 	flags;

    int 	dashSize;
    float      *dashPat;
    double	dashOffset;

    int		lineWidth;
    vcolor     *lineColor;

    glinedrawPointDrawProc pointDrawProc;

};


#define glinedrawCLASS(SUPER, DRAWABLE, ACCESSOR, POINT_DRAW_PROC)	     \
gdrawableCLASS (SUPER, DRAWABLE, ACCESSOR);				     \
vclassMETHOD (glinedrawSET_LINE_COLOR,					     \
              (DRAWABLE *line, vcolor *color));				     \
vclassMETHOD (glinedrawSET_LINE_DASH,					     \
              (DRAWABLE *line, int size, const float *pat, double offset));  \
vclassMETHOD (glinedrawSET_LINE_WIDTH,					     \
              (DRAWABLE *line, int width));				     \
vclassMETHOD (glinedrawSET_POINT_DRAW_PROC,				     \
              (DRAWABLE *line, POINT_DRAW_PROC drawProc));		     \
vclassMETHOD (glinedrawDRAW_POINT,					     \
              (DRAWABLE *line, int index, int vectorPos, int x, int y));     \
vclassMETHOD (glinedrawSET_LINE_FORM,					     \
              (DRAWABLE *line, int lineForm))



typedef struct glinedrawClass glinedrawClass;

struct glinedrawClass {
    glinedrawCLASS (glinedrawClass, glinedraw, gaccessor,
                    glinedrawPointDrawProc);
};




/*
 * ---------- Module Prototypes ----------
 */


void glinedrawSetLineColor (glinedraw *line, vcolor *color);
vcolor *glinedrawGetLineColor (glinedraw *line);

void glinedrawSetLineDash (glinedraw *line,
                           int size, const float *pat, double offset);
void glinedrawGetLineDash (glinedraw *line,
                           int *size, const float **pat, double *offset);

void glinedrawSetLineWidth (glinedraw *line, int width);
int glinedrawGetLineWidth (glinedraw *line);

void glinedrawSetPointDrawProc (glinedraw *line, glinedrawPointDrawProc proc);
glinedrawPointDrawProc glinedrawGetPointDrawProc (glinedraw *line);
void glinedrawDrawPoint (glinedraw *line, int index, int vectorPos, 
                         int x, int y);

void glinedrawSetLineForm (glinedraw *line, int lineForm);
int glinedrawGetLineForm (glinedraw *line);


glinedrawClass *glinedrawGetDefaultClass (void);
glinedrawClass *glinedrawGetClass (glinedraw *line);

vobject *glinedrawGetObject (glinedraw *line);
gdrawable *glinedrawGetDrawable (glinedraw *line);

glinedraw *glinedrawCreate (void);
glinedraw *glinedrawCreateOfClass (glinedrawClass *clas);
void glinedrawDestroy (glinedraw *line);
void glinedrawSetTag (glinedraw *line, const vname *tag);
const vname *glinedrawGetTag (glinedraw *line);

void glinedrawDump (glinedraw *line, FILE *stream);


/* conveniences */

void glinedrawDraw (glinedraw *line);
void glinedrawDrawXAxis (glinedraw *line);
void glinedrawDrawYAxis (glinedraw *line);
void glinedrawDrawLegend (glinedraw *line, const vrect *rect);

void glinedrawSetRect (glinedraw *line, const vrect *rect);
const vrect *glinedrawGetRect (glinedraw *line);

void glinedrawSetXPos (glinedraw *line, int position);
int glinedrawGetXPos (glinedraw *line, int position);

void glinedrawSetYPos (glinedraw *line, int position);
int glinedrawGetYPos (glinedraw *line, int position);

void glinedrawSetContinuousX (glinedraw *line, int onOff);
int glinedrawGetContinuousX (glinedraw *line);

void glinedrawSetContinuousY (glinedraw *line, int onOff);
int glinedrawGetContinuousY (glinedraw *line);

int glinedrawIsXContinuous (glinedraw *line);
int glinedrawIsXDiscrete (glinedraw *line);
int glinedrawIsYContinuous (glinedraw *line);
int glinedrawIsYDiscrete (glinedraw *line);

void glinedrawSetDrawX (glinedraw *line, int onOff);
int glinedrawGetDrawX (glinedraw *line);

void glinedrawSetDrawY (glinedraw *line, int onOff);
int glinedrawGetDrawY (glinedraw *line);

void glinedrawSetDrawableMargins (glinedraw *line, 
                                  int topMargin, int leftMargin,
                                  int bottomMargin, int rightMargin);
void glinedrawGetDrawableMargins (glinedraw *line, 
                                  int *topMargin, int *leftMargin,
                                  int *bottomMargin, int *rightMargin);

void glinedrawSetTopMargin (glinedraw *line, int topMargin);
void glinedrawSetLeftMargin (glinedraw *line, int leftMargin);
void glinedrawSetBottomMargin (glinedraw *line, int bottomMargin);
void glinedrawSetRightMargin (glinedraw *line, int rightMargin);

int glinedrawGetTopMargin (glinedraw *line);
int glinedrawGetLeftMargin (glinedraw *line);
int glinedrawGetBottomMargin (glinedraw *line);
int glinedrawGetRightMargin (glinedraw *line);

void glinedrawGetNaturalAxisSize (glinedraw *line,
                                  int *xheight, int *ywidth);


void glinedrawGetRatio (glinedraw *line, int *width, int *height);

void glinedrawAddAccessor (glinedraw *line, gaccessor *accessor);
void glinedrawRemoveAccessor (glinedraw *line, gaccessor *accessor);
int glinedrawGetAccessorCount (glinedraw *line);
gaccessor *glinedrawGetAccessorAt (glinedraw *line, gaccessor *accessor);

void glinedrawGetLegendNaturalSize (glinedraw *line, int *width, int *height);




/*
 * ---------- Functions defined as #define defines ----------
 */


#define glinedrawGetLineColor(d)   ((d)->lineColor);

#define glinedrawGetLineDash(d,s,p,o) { do {   (s) = (d)->dashSize; \
                                               (p) = (d)->dashPat;  \
                                               (o) = (d)->dashOffset; \
                                           } while (0); }
#define glinedrawGetLineWidth(d)   ((d)->lineWidth)
#define glinedrawGetPointDrawProc(d) ((d)->pointDrawProc)
#define glinedrawGetLineForm(d)	    ((d)->flags & _glinedrawLINE_FORM)

#define glinedrawGetDrawable(d)	( &((d)->drawable) )
#define glinedrawGetObject(d)	(gdrawableGetObject(glinedrawGetDrawable((d))))
#define glinedrawCreate()   glinedrawCreateOfClass(glinedrawGetDefaultClass())
#define glinedrawCreateOfClass(c) ((glinedraw*)vobjectCreateOfClass \
                                   ((vobjectClass*)(c)))
#define glinedrawDestroy(d)	vobjectDestroy(glinedrawGetObject((d)))
#define glinedrawSetTag(d)	vobjectSetTag(glinedrawGetObject((d)))
#define glinedrawGetTag(d)	vobjectGetTag(glinedrawGetObject((d)))

#define glinedrawGetClass(d)	( (glinedrawClass*)vobjectGetClass \
                                 (glinedrawGetObject((d)))  )
#define glinedrawSend(o,s,a)	vclassSend(glinedrawGetClass((o)), s, a)

/* conveniences */

#define glinedrawDraw(d)	gdrawableDraw(glinedrawGetDrawable((d)))
#define glinedrawDrawXAxis(d)	gdrawableDrawXAxis(glinedrawGetDrawable((d)))
#define glinedrawDrawYAxis(d)	gdrawableDrawYAxis(glinedrawGetDrawable((d)))
#define glinedrawDrawLegend(d,r) (gdrawableDrawLegend \
                                  (glinedrawGetDrawable((d)),(r)))

#define glinedrawSetRect(d,r)   gdrawableSetRect(glinedrawGetDrawable((d)),(r))
#define glinedrawGetRect(d)     gdrawableGetRect(glinedrawGetDrawable((d)))
#define glinedrawSetXPos(d,p)   gdrawableSetXPos(glinedrawGetDrawable((d)),(p))
#define glinedrawGetXPos(d)     gdrawableGetXPos(glinedrawGetDrawable((d)))

#define glinedrawSetYPos(d,p)   gdrawableSetYPos(glinedrawGetDrawable((d)),(p))
#define glinedrawGetYPos(d)     gdrawableGetYPos(glinedrawGetDrawable((d)))

#define glinedrawSetDrawX(d,o)   gdrawableSetDrawX(glinedrawGetDrawable((d)), \
                                                   (o))
#define glinedrawGetDrawX(d)     gdrawableGetDrawX(glinedrawGetDrawable((d)))

#define glinedrawSetDrawY(d,o)   gdrawableSetDrawY(glinedrawGetDrawable((d)), \
                                                   (o))
#define glinedrawGetDrawY(d)     gdrawableGetDrawY(glinedrawGetDrawable((d)))

#define glinedrawGetRatio(d,w,h) gdrawableGetRatio(glinedrawGetDrawable((d)), \
                                                   (w),(h))

#define glinedrawAddAccessor(d,a) (gdrawableAddAccessor \
                                   (glinedrawGetDrawable((d)),(a)))
#define glinedrawRemoveAccessor(d,a) (gdrawableRemoveAccessor \
                                      (glinedrawGetDrawable((d)),(a)))
#define glinedrawGetAccessorCount(d) (gdrawableGetAccessorCount \
                                      (glinedrawGetDrawable((d))))
#define glinedrawGetAccessorAt(d,a)  (gdrawableGetAccessorAt \
                                      (glinedrawGetDrawable((d)),(a)))
#define glinedrawGetLegendNaturalSize(d,w,h) (gdrawableGetLegndNaturalSize \
                                              (glinedrawGetDrawable((d)), \
                                               (w),(h)))

#define glinedrawSetDrawableMargins(d,t,l,b,r)  (gdrawableSetDrawableMargins \
                                                 (glinedrawGetDrawable((d)), \
                                                  (t),(l),(b),(r)))

#define glinedrawGetDrawableMargins(d,t,l,b,r)  (gdrawableGetDrawableMargins \
                                                 (glinedrawGetDrawable((d)), \
                                                  (t),(l),(b),(r)))

#define glinedrawSetMarginSpace(d,x,y) (gdrawableSetMarginSpace \
                                        (glinedrawGetDrawable((d)), \
                                         (x),(y)))

#define glinedrawGetMarginSpace(d,x,y) gdrawableGetMarginSpace \
                                        (glinedrawGetDrawable((d)), \
                                         (x),(y))

#define glinedrawSetTopMargin(d,m)  (gdrawableSetTopMargin    \
                                     (glinedrawGetDrawable((d)),(m)))
#define glinedrawSetLeftMargin(d,m)  (gdrawableSetLeftMargin    \
                                      (glinedrawGetDrawable((d)), (m)))
#define glinedrawSetBottomMargin(d,m)  (gdrawableSetBottomMargin    \
                                        (glinedrawGetDrawable((d)), (m)))
#define glinedrawSetRightMargin(d,m)  (gdrawableSetRightmargin    \
                                       (glinedrawGetDrawable((d)), (m)))
                                       
#define glinedrawGetTopMargin(d)  (gdrawableGetTopMargin    \
                                   (glinedrawGetDrawable((d))))
#define glinedrawGetLeftMargin(d)  (gdrawableGetLeftMargin    \
                                    (glinedrawGetDrawable((d))))
#define glinedrawGetBottomMargin(d)  (gdrawableGetBottomMargin    \
                                      (glinedrawGetDrawable((d))))
#define glinedrawGetRightMargin(d)  (gdrawableGetRightMargin    \
                                     (glinedrawGetDrawable((d))))

#define glinedrawGetNaturalAxisSize(d,x,y)  (gdrawableGetNaturalAxisSize    \
                                             (glinedrawGetDrawable((d)),    \
                                              (x),(y)))

#define glinedrawSetContinuousX(d,o)	(gdrawableSetContinuousX	\
                                         (glinedrawGetDrawable((d)), (o))
#define glinedrawGetContinuousX(d)	(gdrawableGetContinuousX	\
                                         (glinedrawGetDrawable((d))))
#define glinedrawSetContinuousY(d,o)	(gdrawableSetContinuousY	\
                                         (glinedrawGetDrawable((d)), (o)))
#define glinedrawGetContinuousY(d)	(gdrawableGetContinuousY	\
                                         (glinedrawGetDrawable((d))))
#define glinedrawIsXContinuous(d)	(gdrawableIsXContinuous	\
                                         (glinedrawGetDrawable((d))))
#define glinedrawIsXDiscrete(d)		(gdrawableIsXDiscrete	\
                                         (glinedrawGetDrawable((d))))
#define glinedrawIsYContinuous(d)	(gdrawableIsYContinuous	\
                                         (glinedrawGetDrawable((d))))
#define glinedrawIsYDiscrete(d)		(gdrawableIsYDiscrete	\
                                         (glinedrawGetDrawable((d))))



/*
 * ---------- Functions implemented by messages ----------
 */


#define glinedrawSetLineColor(d,c) \
	glinedrawSend((d), glinedrawSET_LINE_COLOR, (d,c))

#define glinedrawSetLineDash(d,s,p,o) \
	glinedrawSend((d), glinedrawSET_LINE_DASH, (d,s,p,o))

#define glinedrawSetLineWidth(d,w) \
	glinedrawSend((d), glinedrawSET_LINE_WIDTH, (d,w))

#define glinedrawSetPointDrawProc(d,p) \
	glinedrawSend((d), glinedrawSET_POINT_DRAW_PROC, (d,p))

#define glinedrawDrawPoint(d,i,v,x,y) \
	glinedrawSend((d), glinedrawDRAW_POINT, (d,i,v,x,y))

#define glinedrawSetLineForm(d,f) \
	glinedrawSend((d), glinedrawSET_LINE_FORM, (d,f))

#endif /* glinedrINCLUDED */


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

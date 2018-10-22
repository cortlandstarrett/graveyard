/* $Id: gdrawble.h,v 1.2 1993/11/30 19:36:20 markd Exp $ */
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

/* gdrawable.h -- Interface to drawable chart-hunks.
 *
 * Module:
 *	gdrawable
 *
 * Description:
 *	See file chart.c for more comments about this whole project.
 *
 *	This module is an abstract superclass for a "drawable", a 
 *	chart element that can draw a specified hunk of data in
 *	some meaningful format.
 *
 *	This particular module does no drawing, just sets up the infrastructure
 *	for subclasses to build upon.  It also defines the way the chart view
 *	will lay out the drawables in a nice and pleasing manner.
 *
 *	I take that back.  It does do some primitive drawing of the X and Y
 *	axes, since the way it draws will be pretty common across many
 *	chart types.
 *
 *	Data access is through "accessors".  See gaccessor.h and the
 *	documentation (if there is any) for details on making and using
 *	accessors.
 *
 *	Multiple accesors exists so that things like bar/stacked-bar/area-
 *	charts could use different data sets.  A drawable that implements these
 *	could have each bar come from a different accessor.
 *
 *	Things that use drawables will typically be able to handle multiple
 *	drawables.  The "Drawable Margins" exist to make layering these puppers
 *	yield nicer results.
 *	Say you wanted a chart with a double-Y axis, where each axis is 30
 *	pixels wide.  You'd make one drawable have a left-hand Y axis and
 *	set its right margin to be 30 (so that it won't overlap the other
 *	axis).  Make the other drawable have a left margin of 30 (so that it
 *	skips over the first drawable's axis) and set the right-hand Y axis
 *	attribute.  When the drawable goes to draw. the charts will line
 *	up because the margin and axis sizes are the same.
 *
 *	The "MarginSpace" is different. (sorry for the similar names).  This
 *	is the spacing between the drawing for the axis and where the chart
 *	begins.  If the y-axis space was 5. then there would be 5 pixels
 *	between the edge of the y axis and the start of the charting.  This
 *	is useful if the chart drawing extends beyound the point being drawn,
 *	or if the X-axis label is too wide.
 *
 * Exported Functions:
 *
 *	 gdrawableDraw -- Draw the drawable
 *	 gdrawableDrawXAxis -- Draw the drawable's X axis.  This is called for
 *			       you by gdrawableDraw()
 *	 gdrawableDrawYAxis -- Draw the drawable's Y axis.  This is called for
 *			       you by gdrawableDraw()
 *	 gdrawableDrawLegend -- Draw the entry for the chart legend in a  
 *			        supplied rectangle.
 *	 
 *	 gdrawableSetRect -- Set the total rectangle (including axes and 
 *			     spaces) that the drawable can draw in.
 *	 gdrawableGetRect -- Returns the drawable's rectangle
 *	 
 *	 gdrawableCalcUsefulRect -- Calc the area that's available for drawing
 *				    the chart data.  This rect is
 *				    gdrawableGetRect minus space for the 
 *				    axes, borders, and margins.
 *	 gdrawableCalcPointPoints -- Returns an array of (x,y) pairs 
 *				     of locations in the usefulRect for the
 *				     data points of the drawable's 0th
 *				     accessor.
 *
 *	 gdrawableAddAccessor -- Add an accessor for the drawable to use.
 *	 gdrawableRemoveAccessor -- Remvoe an accessor
 *	 gdrawableGetAccessorCount -- Return the number of accessors this
 *				      drawable is using
 *	 gdrawableGetAccessorAt -- Return an accessor at a given index
 *	 
 *	 gdrawableSetXPos -- Set the location of the X axis.  The location
 *			     is indicated by passing gdrawableTOP_X or
 *			     gdrawableBOTTOM_X
 *	 gdrawableGetXPos -- returns one of the above constants indicating 
 *			     where the X axis will be drawn
 *	 
 *	 gdrawableSetYPos -- Set the location of the Y axis.  The location is
 *			     indicated by passing gdrawableLEFT_Y or 
 *			     gdrawableRIGHT_Y.
 *	 gdrawableGetYPos -- returns one of the above constants indicatin
 *			     where the Y axis will be drawn
 *	 
 *	 gdrawableSetDrawX -- Turns on/off X axis drawing
 *	 gdrawableGetDrawX -- Returns the on/off status of X axis drawing
 *	 
 *	 gdrawableSetDrawY -- Turns on/off Y axis drawing
 *	 gdrawableGetDrawY -- Returns the on/off status of Y axis drawing
 *	 
 *	 gdrawableSetAxisFont -- Sets the font used to draw text along the
 *				 X & Y axis, as well as for string size
 *				 calculations for axis layout.
 *	 gdrawableGetAxisFont -- Aiieee! Death from above!  Run!  Run!
 *	 
 *	 gdrawableSetAxisColor -- Sets the color to be used to draw the lines
 *				  of the X & Y axis.
 *	 gdrawableGetAxisColor  -- Returns the axis drawing color.
 *	 
 *	 gdrawableSetContinuousX -- Indicates if the X axis is a continuous
 *				    range (like in a scatter graph) or 
 *				    discrete jumps (like dates in stock price
 *				    thingie)  (pretty much discrete all the
 *				    time)
 *	 gdrawableGetContinuousX -- Returns the continuosity state of the
 *				    X axis.
 *	 
 *	 gdrawableSetContinuousY -- Indicates if the Y axis is a continuous 
 *				    range or discrete jumps.  (pretty much
 *				    always continuous)
 *	 gdrawableGetContinuousY -- Returns the continuosity state of the 
 *				    Y axis.
 *	 
 *	 gdrawableIsXContinuous -- Convenience for gdrawGetContinuousX
 *	 gdrawableIsXDiscrete  -- Convenience for !gdrawGetContinuousX
 *	 gdrawableIsYContinuous -- Convenience for gdrawGetContinuousY
 *	 gdrawableIsYDiscrete  -- Convenience for !gdrawGetContinuousY
 *	 
 *	 gdrawableSetDrawableMargins -- Sets the top/left/bottom/right margins
 *					for the drawable. (see comments above)
 *	 gdrawableGetDrawableMargins -- Returns the 4 margin values
 *	 
 *	 gdrawableSetTopMargin -- Convenience for setting one of the margins
 *	 gdrawableSetLeftMargin -- ditto
 *	 gdrawableSetBottomMargin -- ditto
 *	 gdrawableSetRightMargin -- ditto
 *	 
 *	 gdrawableGetTopMargin -- Convenience for getting one of the margins
 *	 gdrawableGetLeftMargin -- ditto
 *	 gdrawableGetBottomMargin -- ditto
 *	 gdrawableGetRightMargin -- ditto
 *	 
 *	 gdrawableGetNaturalAxisSize -- Returns the width of the Y axis and
 *				        the height of the X axis.  These are
 *					the values used to calculate the
 *					useful rectangle
 *	 
 *	 gdrawableSetMarginSpace -- Sets the space between the axis and the
 *				    beginning (ending) of chart drawing.
 *				    (see comments above)
 *	 gdrawableGetMarginSpace -- Returns the above value thingie
 *	 
 *	 gdrawableGetRatio -- returns the width-to-height ratio that the
 *			      chart wants to be drawn at.  Excess space in
 *			      either dimension will go unsued.  If this 
 *			      returns gdrawableRATIO_DONT_CARE, then the
 *			      chart can be scaled to any rectangle
 *	 
 *	 gdrawableGetLegendNaturalSize -- get the size that the legend
 *					  thingie describing this drawable
 *					  wants to be.  Drawable containers
 *					  that supply legends will use this
 *					  to figure out how big to make the
 *					  legend.
 *	 
 *	 gdrawableGetDefaultClass -- 
 *	 gdrawableGetClass  --
 *	 
 *	 gdrawableGetObject --
 *	 gdrawableCreate --
 *	 gdrawableCreateOfClass --
 *	 gdrawableDestroy --
 *	 gdrawableSetTag --
 *	 gdrawableGetTag --
 *	 
 *	 gdrawableDump 
 *	 
 * How to use:
 *	* create one.  (usually you'd create a subclass since out-of-the-box
 *	  drawables are kinda boring)
 *	  gdrawable *drawable = gdrawableCreate ();
 *
 *	* add an accessor for it to use
 *	  accessor = glistaccCreate(); ...
 *	  gdrawableAddAccessor (drawable, accessor);
 *
 *	  multiple accessors can be added to each drawable.  It's up to the
 *	  drawable subclass to actually use them.
 *
 *	* set the font (this is important).  This is so axis drawing can be
 *	  done.
 *	  gdrawableSetAxisFont (drawable, aFontGottenFromSomewhere)
 *
 *	* set the margin space if you want a little breathing room between
 *	  the edge of the axis and the start of the chart.
 *	  gdrawableSetMarginSpace (drawable, 5, 10);
 *
 *	* If you want the axes to go to different places, tell it so.
 *	  gdrawableSetXPos (drawable, gdrawableTOP_X);
 *	  gdrawableSetYPos (drawable, gdrawableRIGHT_Y);
 *
 * Defaults:
 *	chart rect: (0,0,0,0);
 *	x/y axis space: 0
 *	margins: 0
 */


#ifndef gdrawableINCLUDED
#define gdrawableINCLUDED 1

#ifndef   vportINCLUDED
#include <vport.h>		/* for v*HEADER */
#endif

#ifndef  vclassINCLUDED
#include vclassHEADER
#endif

#ifndef  vcolorINCLDED
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

#ifndef  gaccessorINCLUDED
#include "gaccess.h"
#endif




/*
 * ---------- Constant and macro definitions ----------
 */


enum { /* flags */
    gdrawableLEFT_Y	 = 0x0001,
    gdrawableRIGHT_Y	 = 0x0002,
    _gdrawableY_FLAGS	 = gdrawableLEFT_Y | gdrawableRIGHT_Y,
    
    gdrawableTOP_X	 = 0x0004,
    gdrawableBOTTOM_X	 = 0x0008,
    _gdrawableX_FLAGS	 = gdrawableTOP_X | gdrawableBOTTOM_X,

    _gdrawableDRAW_X	 = 0x0010,
    _gdrawableDRAW_Y	 = 0x0020,
    _gdrawableDRAW_FLAGS = _gdrawableDRAW_X | _gdrawableDRAW_Y,

    _gdrawableCONTINUOUS_X	 = 0x0040,
    _gdrawableCONTINUOUS_Y	 = 0x0080,
    _gdrawableCONTINUOSITY_FLAGS = (  _gdrawableCONTINUOUS_X 
                                    | _gdrawableCONTINUOUS_Y)
};

enum {
    gdrawableRATIO_DONT_CARE = -1,
    gdrawableNO_CHANGE 	     = -1   /* for margin setting */
};




/*
 * ---------- Type and structure definitions ----------
 */


typedef struct gdrawable gdrawable;

struct gdrawable {
    vobject	object;
    vrect	chartRect;
    short	flags;
    gaccessor **accessors;
    int		accessorCount;
    int		topMargin, leftMargin, bottomMargin, rightMargin;
    int		xaxisSpace, yaxisSpace;
    vfont      *axisFont;
    vcolor     *axisColor;
};



#define gdrawableCLASS(SUPER, DRAWABLE, ACCESSOR)			\
vobjectCLASS     (SUPER, DRAWABLE);					\
vclassMETHOD     (gdrawableDRAW, 					\
                  (DRAWABLE *drawable));				\
\
vclassMETHOD     (gdrawableDRAW_X_AXIS,					\
                  (DRAWABLE *drawable));				\
vclassMETHOD     (gdrawableDRAW_Y_AXIS,					\
                  (DRAWABLE *drawable));				\
\
vclassMETHOD     (gdrawableDRAW_LEGEND,					\
                  (DRAWABLE *drawable, const vrect *rect));		\
\
vclassMETHOD     (gdrawableSET_RECT,					\
                  (DRAWABLE *drawable, const vrect *rect));		\
\
vclassMETHOD	 (gdrawableCALC_USEFUL_RECT,				\
                  (DRAWABLE *drawable, vrect *usefulRect));		\
vclassMETHOD_RET (gdrawableCALC_POINT_POINTS, vpoint *,			\
                  (DRAWABLE *drawable));				\
\
vclassMETHOD     (gdrawableSET_X_POS,					\
                  (DRAWABLE *drawable, int position));			\
vclassMETHOD     (gdrawableSET_Y_POS,					\
                  (DRAWABLE *drawable, int position));			\
\
vclassMETHOD	 (gdrawableSET_DRAW_X,					\
                  (DRAWABLE *drawable, int onOff));			\
vclassMETHOD	 (gdrawableSET_DRAW_Y,					\
                  (DRAWABLE *drawable, int onOff));			\
\
vclassMETHOD	 (gdrawableSET_CONTINUOUS_X,				\
                  (DRAWABLE *drawable, int onOff));			\
vclassMETHOD	 (gdrawableSET_CONTINUOUS_Y,				\
                  (DRAWABLE *drawable, int onOff));			\
\
vclassMETHOD	 (gdrawableSET_DRAWABLE_MARGINS,			\
                  (DRAWABLE *drawable, int topMargin, int leftMargin,	\
                   int bottomMargin, int rightMargin));			\
\
vclassMETHOD	 (gdrawableSET_AXIS_FONT,				\
                  (DRAWABLE *drawable, vfont *font));			\
vclassMETHOD	 (gdrawableSET_AXIS_COLOR,				\
                  (DRAWABLE *drawable, vcolor *color));			\
\
vclassMETHOD     (gdrawableGET_NATURAL_AXIS_SIZE,			\
                  (DRAWABLE *drawable, int *xheight, int *ywidth));	\
\
vclassMETHOD	 (gdrawableSET_MARGIN_SPACE,				\
                  (DRAWABLE *drawable, 					\
                   int xaxisSpace, int yaxisSpace));			\
\
vclassMETHOD     (gdrawableGET_RATIO,					\
                  (DRAWABLE *drawable, int *width, int *height));	\
\
vclassMETHOD     (gdrawableADD_ACCESSOR,				\
                  (DRAWABLE *drawable, ACCESSOR *accessor));		\
vclassMETHOD     (gdrawableREMOVE_ACCESSOR,				\
                  (DRAWABLE *drawable, ACCESSOR *accessor));		\
vclassMETHOD_RET (gdrawableGET_ACCESSOR_AT, ACCESSOR *,			\
                  (DRAWABLE *drawable, int at));			\
\
vclassMETHOD     (gdrawableGET_LEGEND_NATURAL_SIZE, 			\
                  (DRAWABLE *drawable, int *width, int *height))


typedef struct gdrawableClass gdrawableClass;

struct gdrawableClass {
    gdrawableCLASS (gdrawableClass, gdrawable, gaccessor);
};




/*
 * ---------- Module Prototypes ----------
 */


void gdrawableDraw (gdrawable *drawable);
void gdrawableDrawXAxis (gdrawable *drawable);
void gdrawableDrawYAxis (gdrawable *drawable);
void gdrawableDrawLegend (gdrawable *drawable, const vrect *rect);

void gdrawableSetRect (gdrawable *drawable, const vrect *rect);
const vrect *gdrawableGetRect (gdrawable *drawable);

void gdrawableCalcUsefulRect (gdrawable *drawable, vrect *rect);
vpoint *gdrawableCalcPointPoints (gdrawable *drawable);

void gdrawableSetXPos (gdrawable *drawable, int position);
int gdrawableGetXPos (gdrawable *drawable, int position);

void gdrawableSetYPos (gdrawable *drawable, int position);
int gdrawableGetYPos (gdrawable *drawable, int position);

void gdrawableSetDrawX (gdrawable *drawable, int onOff);
int gdrawableGetDrawX (gdrawable *drawable);

void gdrawableSetDrawY (gdrawable *drawable, int onOff);
int gdrawableGetDrawY (gdrawable *drawable);

void gdrawableSetAxisFont (gdrawable *drawable, vfont *font);
vfont *gdrawableGetAxisFont (gdrawable *drawable);

void gdrawableSetAxisColor (gdrawable *drawable, vcolor *color);
vcolor *gdrawableGetAxisColor (gdrawable *drawable);

void gdrawableSetContinuousX (gdrawable *drawable, int onOff);
int gdrawableGetContinuousX (gdrawable *drawable);

void gdrawableSetContinuousY (gdrawable *drawable, int onOff);
int gdrawableGetContinuousY (gdrawable *drawable);

int gdrawableIsXContinuous (gdrawable *drawable);
int gdrawableIsXDiscrete (gdrawable *drawable);
int gdrawableIsYContinuous (gdrawable *drawable);
int gdrawableIsYDiscrete (gdrawable *drawable);


void gdrawableSetDrawableMargins (gdrawable *drawable, 
                                  int topMargin, int leftMargin,
                                  int bottomMargin, int rightMargin);
void gdrawableGetDrawableMargins (gdrawable *drawable, 
                                  int *topMargin, int *leftMargin,
                                  int *bottomMargin, int *rightMargin);

void gdrawableSetTopMargin (gdrawable *drawable, int topMargin);
void gdrawableSetLeftMargin (gdrawable *drawable, int leftMargin);
void gdrawableSetBottomMargin (gdrawable *drawable, int bottomMargin);
void gdrawableSetRightMargin (gdrawable *drawable, int rightMargin);

int gdrawableGetTopMargin (gdrawable *drawable);
int gdrawableGetLeftMargin (gdrawable *drawable);
int gdrawableGetBottomMargin (gdrawable *drawable);
int gdrawableGetRightMargin (gdrawable *drawable);


void gdrawableGetNaturalAxisSize (gdrawable *drawable,
                                  int *xheight, int *ywidth);

void gdrawableSetMarginSpace (gdrawable *drawable, 
                              int xaxisSpace, int yaxisSpace);
void gdrawableGetMarginSpace (gdrawable *drawable,
                              int *xaxisSpace, int *yaxisSpace);

void gdrawableGetRatio (gdrawable *drawable, int *width, int *height);

void gdrawableAddAccessor (gdrawable *drawable, gaccessor *accessor);
void gdrawableRemoveAccessor (gdrawable *drawable, gaccessor *accessor);
int gdrawableGetAccessorCount (gdrawable *drawable);
gaccessor *gdrawableGetAccessorAt (gdrawable *drawable, gaccessor *accessor);

void gdrawableGetLegendNaturalSize (gdrawable *drawable, 
                                    int *width, int *height);


gdrawableClass *gdrawableGetDefaultClass (void);
gdrawableClass *gdrawableGetClass (gdrawable *drawable);

vobject *gdrawableGetObject (gdrawable *drawable);

gdrawable *gdrawableCreate (void);
gdrawable *gdrawableCreateOfClass (gdrawableClass *clas);
void gdrawableDestroy (gdrawable *drawable);
void gdrawableSetTag (gdrawable *drawable, const vname *tag);
const vname *gdrawableGetTag (gdrawable *drawable);

void gdrawableDump (gdrawable *drawable, FILE *stream);




/*
 * ---------- Functions defined as #define defines ----------
 */


#define gdrawableGetRect(d)	( &((d)->chartRect) )
#define gdrawableGetXPos(d)	((d)->flags & _gdrawableX_FLAGS)
#define gdrawableGetYPos(d)	((d)->flags & _gdrawableY_FLAGS)

#define gdrawableGetDrawX(d)	((d)->flags & _gdrawableDRAW_X)
#define gdrawableGetDrawY(d)	((d)->flags & _gdrawableDRAW_Y)

#define gdrawableGetContinousX(d) ((d)->flags & _gdrawableCONTINUOUS_X)
#define gdrawableGetContinousY(d) ((d)->flags & _gdrawableCONTINUOUS_Y)

#define gdrawableIsXContinuous(d) ((d)->flags & _gdrawableCONTINUOUS_X)
#define gdrawableIsYContinuousY(d) ((d)->flags & _gdrawableCONTINUOUS_Y)

#define gdrawableIsXDiscrete(d) (!((d)->flags & _gdrawableCONTINUOUS_X))
#define gdrawableIsYDiscrete(d) (!((d)->flags & _gdrawableCONTINUOUS_Y))

#define gdrawableGetAccessorCount(d)  ((d)->accessorCount)

#define gdrawableGetDrawableMargins(d,t,l,b,r) do{ *(t) = ((d)->topMargin);   \
                                                   *(l) = ((d)->leftMargin);  \
                                                   *(b) = ((d)->bottomMargin);\
                                                   *(r) = ((d)->rightMargin); \
                                               } while (0)

#define gdrawableGetMarginSpace(d,x,y) do { *(x) = ((d)->xaxisSpace); \
                                            *(y) = ((d)->yaxisSpace); \
                                        } while (0)

#define gdrawableGetAxisFont(d)  ((d)->axisFont)
#define gdrawableGetAxisColor(d) ((d)->axisColor)

#define gdrawableSetTopMargin(d,m) (gdrawableSetDrawableMargins \
                                    ((d),\
                                     (m), \
                                     gdrawableNO_CHANGE,\
                                     gdrawableNO_CHANGE,\
                                     gdrawableNO_CHANGE))
#define gdrawableSetLeftMargin(d,m) (gdrawableSetDrawableMargins \
                                     ((d),\
                                      gdrawableNO_CHANGE,\
                                      (m), \
                                      gdrawableNO_CHANGE,\
                                      gdrawableNO_CHANGE))
#define gdrawableSetBottomMargin(d,m) (gdrawableSetDrawableMargins \
                                       ((d),\
                                        gdrawableNO_CHANGE,\
                                        gdrawableNO_CHANGE,\
                                        (m), \
                                        gdrawableNO_CHANGE))
#define gdrawableSetRightMargin(d,m) (gdrawableSetDrawableMargins \
                                      ((d),\
                                       gdrawableNO_CHANGE,\
                                       gdrawableNO_CHANGE,\
                                       gdrawableNO_CHANGE,\
                                       (m)))

#define gdrawableGetTopMargin(d)	((d)->topMargin)
#define gdrawableGetLeftMargin(d)	((d)->leftMargin)
#define gdrawableGetBottomMargin(d)	((d)->bottomMargin)
#define gdrawableGetRightMargin(d)	((d)->rightMargin)


#define gdrawableGetObject(d)	( &((d)->object) )
#define gdrawableCreate()   gdrawableCreateOfClass(gdrawableGetDefaultClass())
#define gdrawableCreateOfClass(c) ((gdrawable*)vobjectCreateOfClass \
                                   ((vobjectClass*)(c)))
#define gdrawableDestroy(d)	vobjectDestroy(gdrawableGetObject((d)))
#define gdrawableSetTag(d)	vobjectSetTag(gdrawableGetObject((d)))
#define gdrawableGetTag(d)	vobjectGetTag(gdrawableGetObject((d)))

#define gdrawableGetClass(d)	( (gdrawableClass*)vobjectGetClass \
                                 (gdrawableGetObject((d)))  )
#define gdrawableSend(o,s,a)	vclassSend(gdrawableGetClass((o)), s, a)




/*
 * ---------- Functions implemented by messages ----------
 */


#define gdrawableDraw(d) \
	gdrawableSend ((d), gdrawableDRAW, (d))

#define gdrawableDrawXAxis(d) \
	gdrawableSend ((d), gdrawableDRAW_X_AXIS, (d))

#define gdrawableDrawYAxis(d) \
	gdrawableSend ((d), gdrawableDRAW_Y_AXIS, (d))

#define gdrawableDrawLegend(d,r) \
	gdrawableSend ((d), gdrawableDRAW_LEGEND, (d,r))

#define gdrawableSetRect(d,r) \
	gdrawableSend ((d), gdrawableSET_RECT, (d,r))

#define gdrawableCalcUsefulRect(d,r) \
	gdrawableSend ((d), gdrawableCALC_USEFUL_RECT, (d,r))

#define gdrawableCalcPointPoints(d) \
	gdrawableSend ((d), gdrawableCALC_POINT_POINTS, (d))

#define gdrawableSetXPos(d,p) \
	gdrawableSend ((d), gdrawableSET_X_POS, (d,p))

#define gdrawableSetYPos(d,p) \
	gdrawableSend ((d), gdrawableSET_Y_POS, (d,p))

#define gdrawableSetContinuousX(d,o) \
	gdrawableSend ((d), gdrawableSET_CONTINUOUS_X, (d,o))

#define gdrawableSetContinuousY(d,o) \
	gdrawableSend ((d), gdrawableSET_CONTINUOUS_Y, (d,o))

#define gdrawableSetDrawX(d,o) \
	gdrawableSend ((d), gdrawableSET_DRAW_X, (d,o))

#define gdrawableSetDrawY(d,o) \
	gdrawableSend ((d), gdrawableSET_DRAW_Y, (d,o))

#define gdrawableSetDrawableMargins(d,t,l,b,r) \
	gdrawableSend ((d), gdrawableSET_DRAWABLE_MARGINS, (d,t,l,b,r))

#define gdrawableSetAxisFont(d,f) \
	gdrawableSend ((d), gdrawableSET_AXIS_FONT, (d,f))

#define gdrawableSetAxisColor(d,c) \
	gdrawableSend ((d), gdrawableSET_AXIS_COLOR, (d,c))

#define gdrawableGetNaturalAxisSize(d,x,y) \
	gdrawableSend ((d), gdrawableGET_NATURAL_AXIS_SIZE, (d,x,y))

#define gdrawableGetRatio(d,w,h) \
	gdrawableSend ((d), gdrawableGET_RATIO, (d,w,h))

#define gdrawableSetMarginSpace(d,x,y) \
	gdrawableSend ((d), gdrawableSET_MARGIN_SPACE, (d,x,y))

#define gdrawableAddAccessor(d,a) \
	gdrawableSend ((d), gdrawableADD_ACCESSOR, (d,a))

#define gdrawableRemoveAccessor(d,a) \
	gdrawableSend ((d), gdrawableREMOVE_ACCESSOR, (d,a))

#define gdrawableGetAccessorAt(d,a) \
	gdrawableSend ((d), gdrawableGET_ACCESSOR_AT, (d,a))

#define gdrawableGetLegendNaturalSize(d,w,h) \
	gdrawableSend ((d), gdrawableGET_LEGEND_NATURAL_SIZE, (d,w,h))

#endif /* gdrawableINCLUDED */


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

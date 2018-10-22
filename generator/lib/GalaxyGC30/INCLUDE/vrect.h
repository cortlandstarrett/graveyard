/* $Id: vrect.h,v 1.38 1996/03/23 00:40:47 chad Exp $ */

/************************************************************

    vrect.h

    C Interface file for the Rectangle Library

    (c) Copyright Visix Software Inc.
    All rights reserved

************************************************************/

#ifndef vrectINCLUDED
#define vrectINCLUDED 1

#ifndef  vportINCLUDED
#include <vport.h>
#endif

#ifndef  vdebugINCLUDED
#include vdebugHEADER
#endif

#ifndef  vmemINCLUDED
#include vmemHEADER
#endif

#ifndef  vfixedINCLUDED
#include vfixedHEADER
#endif

#ifndef  vclientINCLUDED
#include vclientHEADER
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * * * * * * * * * * PUBLIC CONSTANT DEFINITIONS * * * * * * * * * *
 */

enum {
    vrectPLACE_LEFT                 = 0x0000,
    vrectPLACE_RIGHT	            = 0x0008,
    vrectPLACE_BOTTOM	            = vrectPLACE_LEFT,
    vrectPLACE_TOP                  = vrectPLACE_RIGHT,

    vrectPLACE_NEAR	            = 0x0000,
    vrectPLACE_ADJACENT             = 0x0001,
    vrectPLACE_STRADDLE             = 0x0002,
    vrectPLACE_ALIGN	            = 0x0003,
    vrectPLACE_INSET	            = 0x0004,
    vrectPLACE_HALF	            = 0x0005,
    vrectPLACE_CENTER	            = 0x0006
};

/*
 * * * * * * * * * * PUBLIC TYPE DEFINITIONS * * * * * * * * * *
 */

typedef struct vrect                vrect;
typedef struct vrectLong            vrectLong;
typedef struct vrectFloat           vrectFloat;
typedef struct vrectFixed           vrectFixed;

struct vrect {
    short                           x, y;
    short                           w, h;
};

struct vrectLong {
    long                            x, y;
    long                            w, h;
};

struct vrectFloat {
    float                           x, y;
    float                           w, h;
};

struct vrectFixed {
    vfixed                          x, y;
    vfixed                          w, h;
};

/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */

void vrectStartup(void);


/*
 * rectangles
 */

const vrect *vrectNull(
    void
    );

int vrectIsEmpty(
    const vrect                    *rect
    );

int vrectMIsEmpty(
    const vrect                    *rect
    );

int vrectContainsPoint(
    const vrect                    *rect,
    int                             x,
    int                             y
    );

int vrectMContainsPoint(
    const vrect                    *rect,
    int                             x,
    int                             y
    );

int vrectIsEqual(
    const vrect                    *rect1,
    const vrect                    *rect2
    );

int vrectMIsEqual(
    const vrect                    *rect1,
    const vrect                    *rect2
    );

int vrectIntersects(
    const vrect                    *rect1,
    const vrect                    *rect2
    );

int vrectMIntersects(
    const vrect                    *rect1,
    const vrect                    *rect2
    );

int vrectEncloses(
    const vrect                    *rect1,
    const vrect                    *rect2
    );

int vrectMEncloses(
    const vrect                    *rect1,
    const vrect                    *rect2
    );

void vrectSet(
    int                             x,
    int                             y,
    int                             w,
    int                             h,
    vrect                          *rrect
    );

void vrectSetPoints(
    int                             x0,
    int                             y0,
    int                             x1,
    int                             y1,
    vrect                          *rrect
    );

void vrectOffset(
    const vrect                    *rect,
    int                             dx,
    int                             dy,
    vrect                          *rrect
    );

void vrectInset(
    const vrect                    *rect,
    int                             dx,
    int                             dy,
    vrect                          *rrect
    );

void vrectIntersect(
    const vrect                    *rect1,
    const vrect                    *rect2,
    vrect                          *rrect
    );

void vrectUnion(
    const vrect                    *rect1,
    const vrect                    *rect2,
    vrect                          *rrect
    );

void vrectPin(
    const vrect                    *rect1,
    const vrect                    *rect2,
    vrect                          *rrect
    );

void vrectLimit(
    const vrect                    *rect1,
    const vrect                    *rect2,
    vrect                          *rrect
    );

int vrectPlaceCoordinate(
    int                             mode,
    int                             w,
    int                             bx,
    int                             bw
    );

void vrectPlace(
    const vrect                    *rect,
    const vrect                    *base,
    int                             modeX,
    int                             modeY,
    vrect                          *rrect
    );

vrect *vrectCreateSet(
    int                             count
    );

vrect *vrectCloneSet(
    const vrect		           *rects,
    int                             count
    );

void vrectDestroySet(
    vrect		           *rects
    );

int vrectSetContainsPoint(
    const vrect                    *rects,
    int                             count,
    int                             x,
    int                             y
    );

int vrectIntersectsSet(
    const vrect                    *rect,
    const vrect                    *rects,
    int                             count
    );

void vrectIntersectSet(
    const vrect                    *rects,
    int                             count,
    vrect                          *rrect
    );

void vrectUnionSet(
    const vrect                    *rects,
    int                             count,
    vrect                          *rrect
    );

vrect *vrectIntersectSets(
    const vrect                    *rects1,
    const vrect                    *rects2,
    int                             count1,
    int                             count2,
    int                            *sectCount
    );

vrect *vrectUnionSets(
    const vrect                    *rects1,
    const vrect                    *rects2,
    int                             count1,
    int                             count2,
    int                            *unionCount
    );

vrect *vrectDifferenceSets(
    const vrect                    *rects1,
    const vrect                    *rects2,
    int                             count1,
    int                             count2,
    int                            *diffCount
    );

void vrectToLong(
    const vrect		           *rect,
    vrectLong                      *rrect
    );

void vrectFromLong(
    const vrectLong                *rect,
    vrect		           *rrect
    );

void vrectToFloat(
    const vrect		           *rect,
    vrectFloat                     *rrect
    );

void vrectFromFloat(
    const vrectFloat               *rect,
    vrect		           *rrect
    );

void vrectToFixed(
    const vrect		           *rect,
    vrectFixed                     *rrect
    );

void vrectFromFixed(
    const vrectFixed               *rect,
    vrect		           *rrect
    );

void vrectFloatToFixed(
    const vrectFloat               *rect,
    vrectFixed                     *rrect
    );

void vrectFloatFromFixed(
    const vrectFixed               *rect,
    vrectFloat                     *rrect
    );

/*
 * long rectangles
 */

const vrectLong *vrectNullLong(
    void
    );

int vrectIsEmptyLong(
    const vrectLong                *rect
    );

int vrectMIsEmptyLong(
    const vrectLong                *rect
    );

int vrectContainsPointLong(
    const vrectLong                *rect,
    long                            x,
    long                            y
    );

int vrectMContainsPointLong(
    const vrectLong                *rect,
    long                            x,
    long                            y
    );

int vrectIsEqualLong(
    const vrectLong                *rect1,
    const vrectLong                *rect2
    );

int vrectMIsEqualLong(
    const vrectLong                *rect1,
    const vrectLong                *rect2
    );

int vrectIntersectsLong(
    const vrectLong                *rect1,
    const vrectLong                *rect2
    );

int vrectMIntersectsLong(
    const vrectLong                *rect1,
    const vrectLong                *rect2
    );

int vrectEnclosesLong(
    const vrectLong                *rect1,
    const vrectLong                *rect2
    );

int vrectMEnclosesLong(
    const vrectLong                *rect1,
    const vrectLong                *rect2
    );

void vrectSetLong(
    long                            x,
    long                            y,
    long                            w,
    long                            h,
    vrectLong                      *rrect
    );

void vrectSetPointsLong(
    long                            x0,
    long                            y0,
    long                            x1,
    long                            y1,
    vrectLong                      *rrect
    );

void vrectOffsetLong(
    const vrectLong                *rect,
    long                            dx,
    long                            dy,
    vrectLong                      *rrect
    );

void vrectInsetLong(
    const vrectLong                *rect,
    long                            dx,
    long                            dy,
    vrectLong                      *rrect
    );

void vrectIntersectLong(
    const vrectLong                *rect1,
    const vrectLong                *rect2,
    vrectLong                      *rrect
    );

void vrectUnionLong(
    const vrectLong                *rect1,
    const vrectLong                *rect2,
    vrectLong                      *rrect
    );

void vrectPinLong(
    const vrectLong                *rect1,
    const vrectLong                *rect2,
    vrectLong                      *rrect
    );

void vrectLimitLong(
    const vrectLong                *rect1,
    const vrectLong                *rect2,
    vrectLong                      *rrect
    );

vrectLong *vrectCreateSetLong(
    int                             count
    );

vrectLong *vrectCloneSetLong(
    const vrectLong                *rects,
    int                             count
    );

void vrectDestroySetLong(
    vrectLong                      *rects
    );

int vrectSetContainsPointLong(
    const vrectLong                *rects,
    int                             count,
    long                            x,
    long                            y
    );

int vrectIntersectsSetLong(
    const vrectLong                *rect,
    const vrectLong                *rects,
    int                             count
    );

void vrectIntersectSetLong(
    const vrectLong                *rects,
    int                             count,
    vrectLong                      *rrect
    );

void vrectUnionSetLong(
    const vrectLong                *rects,
    int                             count,
    vrectLong                      *rrect
    );

vrectLong *vrectIntersectSetsLong(
    const vrectLong                *rects1,
    const vrectLong                *rects2,
    int                             count1,
    int                             count2,
    int                            *sectCount
    );

vrectLong *vrectUnionSetsLong(
    const vrectLong                *rects1,
    const vrectLong                *rects2,
    int                             count1,
    int                             count2,
    int                            *unionCount
    );

vrectLong *vrectDifferenceSetsLong(
    const vrectLong                *rects1,
    const vrectLong                *rects2,
    int                             count1,
    int                             count2,
    int                            *diffCount
    );

void vrectLongToFloat(
    const vrectLong                *rect,
    vrectFloat                     *rrect
    );

void vrectLongFromFloat(
    const vrectFloat               *rect,
    vrectLong		           *rrect
    );

void vrectLongToFixed(
    const vrectLong	           *rect,
    vrectFixed                     *rrect
    );

void vrectLongFromFixed(
    const vrectFixed               *rect,
    vrectLong		           *rrect
    );

/*
 * * * * * * * * * * PRIVATE VARIABLE DECLARATIONS * * * * * * * * * *
 */

extern vportLINK const vrect                  _vrectNull;
extern vportLINK const vrectLong              _vrectNullLong;

/*
 * * * * * * * * * * PRIVATE FUNCTION PROTOTYPES * * * * * * * * * *
 */

/*
 * rectangles
 */

#if (vdebugDEBUG)

vrect *_vrectCreateSetDebug(
    int                             count,
    const char                     *tag,
    const char                     *file,
    int                             line
    );

vrect *_vrectCloneSetDebug(
    const vrect		           *rects,
    int                             count,
    const char                     *tag,
    const char                     *file,
    int                             line
    );

#else

vrect *_vrectCreateSetDebug(
    int                             count
    );

vrect *_vrectCloneSetDebug(
    const vrect		           *rects,
    int                             count
    );

#endif

#if (vdebugDEBUG)
vrect *_vrectDissectSets(
    const vrect                    *rects1,
    const vrect                    *rects2,
    int                             count1,
    int                             count2,
    int                             colors1,
    int                             colors2,
    int                             dissectColors,
    int                            *dissectCount,
    const char                     *tag,
    const char                     *file,
    int                             line
    );
#else
vrect *_vrectDissectSets(
    const vrect                    *rects1,
    const vrect                    *rects2,
    int                             count1,
    int                             count2,
    int                             colors1,
    int                             colors2,
    int                             dissectColors,
    int                            *dissectCount
    );
#endif

/*
 * long rectangles
 */

#if (vdebugDEBUG)

vrectLong *_vrectCreateSetLongDebug(
    int                             count,
    const char                     *tag,
    const char                     *file,
    int                             line
    );

vrectLong *_vrectCloneSetLongDebug(
    const vrectLong                *rects,
    int                             count,
    const char                     *tag,
    const char                     *file,
    int                             line
    );

#else

vrectLong *_vrectCreateSetLongDebug(
    int                             count
    );

vrectLong *_vrectCloneSetLongDebug(
    const vrectLong                *rects,
    int                             count
    );

#endif

#if (vdebugDEBUG)
vrectLong *_vrectDissectSetsLong(
    const vrectLong                *rects1,
    const vrectLong                *rects2,
    int                             count1,
    int                             count2,
    int                             colors1,
    int                             colors2,
    int                             dissectColors,
    int                            *dissectCount,
    const char                     *tag,
    const char                     *file,
    int                             line
    );
#else
vrectLong *_vrectDissectSetsLong(
    const vrectLong                *rects1,
    const vrectLong                *rects2,
    int                             count1,
    int                             count2,
    int                             colors1,
    int                             colors2,
    int                             dissectColors,
    int                            *dissectCount
    );
#endif

void	_vrectCopy(const vrect *rect, vrect *rrect);
short	_vrectGetX(const vrect *rect);
short	_vrectGetY(const vrect *rect);
short	_vrectGetWidth(const vrect *rect);
short	_vrectGetHeight(const vrect *rect);
void	_vrectSetX(vrect *rect, int x);
void	_vrectSetY(vrect *rect, int y);
void	_vrectSetWidth(vrect *rect, int width);
void	_vrectSetHeight(vrect *rect, int height);

void	_vrectCopyLong(const vrectLong *rect, vrectLong *rrect);
long	_vrectGetXLong(const vrectLong *rect);
long	_vrectGetYLong(const vrectLong *rect);
long	_vrectGetWidthLong(const vrectLong *rect);
long	_vrectGetHeightLong(const vrectLong *rect);
void	_vrectSetXLong(vrectLong *rect, long x);
void	_vrectSetYLong(vrectLong *rect, long y);
void	_vrectSetWidthLong(vrectLong *rect, long width);
void	_vrectSetHeightLong(vrectLong *rect, long height);

void 	_vrectSetFixed(vfixed x, vfixed y, vfixed w, vfixed h,
		       vrectFixed *rrect);
void	_vrectCopyFixed(const vrectFixed *rect, vrectFixed *rrect);
vfixed	_vrectGetXFixed(const vrectFixed *rect);
vfixed	_vrectGetYFixed(const vrectFixed *rect);
vfixed	_vrectGetWidthFixed(const vrectFixed *rect);
vfixed	_vrectGetHeightFixed(const vrectFixed *rect);
void	_vrectSetXFixed(vrectFixed *rect, vfixed x);
void	_vrectSetYFixed(vrectFixed *rect, vfixed y);
void	_vrectSetWidthFixed(vrectFixed *rect, vfixed width);
void	_vrectSetHeightFixed(vrectFixed *rect, vfixed height);

void	_vrectSetFloat(double x, double y, double w, double h,
		       vrectFloat *rrect);
void	_vrectCopyFloat(const vrectFloat *rect, vrectFloat *rrect);
double	_vrectGetXFloat(const vrectFloat *rect);
double	_vrectGetYFloat(const vrectFloat *rect);
double	_vrectGetWidthFloat(const vrectFloat *rect);
double	_vrectGetHeightFloat(const vrectFloat *rect);
void	_vrectSetXFloat(vrectFloat *rect, double x);
void	_vrectSetYFloat(vrectFloat *rect, double y);
void	_vrectSetWidthFloat(vrectFloat *rect, double width);
void	_vrectSetHeightFloat(vrectFloat *rect, double height);

/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * *
 */

/*
 * rectangles
 */

#define vrectNull()               (&_vrectNull)
#define vrectMIsEmpty(r)          ((r)->w<=0 || (r)->h<=0)
#define vrectMContainsPoint(r, px, py) \
    ((px)>=(r)->x && (py)>=(r)->y && (px)<(r)->x+(r)->w && (py)<(r)->y+(r)->h)
#define vrectMIsEqual(r1, r2) \
    ((r1)->x==(r2)->x && (r1)->y==(r2)->y && \
     (r1)->w==(r2)->w && (r1)->h==(r2)->h)
#define vrectMIntersects(r1, r2) \
    ((r1)->x+(r1)->w>(r2)->x && (r2)->x+(r2)->w>(r1)->x && \
     (r1)->y+(r1)->h>(r2)->y && (r2)->y+(r2)->h>(r1)->y)
#define vrectMEncloses(r1, r2) \
    ((r1)->x<=(r2)->x && (r1)->y<=(r2)->y && \
     (r1)->x+(r1)->w>=(r2)->x+(r2)->w && (r1)->y+(r1)->h>=(r2)->y+(r2)->h)

#if (vdebugDEBUG)
#define vrectCreateSet(n) \
    _vrectCreateSetDebug(n, vmemTAG, __FILE__, __LINE__)
#define vrectCloneSet(r, n) \
    _vrectCloneSetDebug(r, n, vmemTAG, __FILE__, __LINE__)
#define vrectIntersectSets(r1, r2, n1, n2, n) \
    _vrectDissectSets(r1, r2, n1, n2, 1, 2, 3, n, vmemTAG, __FILE__, __LINE__)
#define vrectUnionSets(r1, r2, n1, n2, n) \
    _vrectDissectSets(r1, r2, n1, n2, 1, 1, 1, n, vmemTAG, __FILE__, __LINE__)
#define vrectDifferenceSets(r1, r2, n1, n2, n) \
    _vrectDissectSets(r1, r2, n1, n2, 1, 2, 1, n, vmemTAG, __FILE__, __LINE__)
#else
#define vrectCreateSet(n) \
    _vrectCreateSetDebug(n)
#define vrectCloneSet(r, n) \
    _vrectCloneSetDebug(r, n)
#define vrectIntersectSets(r1, r2, n1, n2, n) \
    _vrectDissectSets(r1, r2, n1, n2, 1, 2, 3, n)
#define vrectUnionSets(r1, r2, n1, n2, n) \
    _vrectDissectSets(r1, r2, n1, n2, 1, 1, 1, n)
#define vrectDifferenceSets(r1, r2, n1, n2, n) \
    _vrectDissectSets(r1, r2, n1, n2, 1, 2, 1, n)
#endif

/*
 * long rectangles
 */

#define vrectNullLong()           (&_vrectNullLong)
#define vrectMIsEmptyLong(r)      ((r)->w<=0 || (r)->h<=0)
#define vrectMContainsPointLong(r, px, py) \
    ((px)>=(r)->x && (py)>=(r)->y && (px)<(r)->x+(r)->w && (py)<(r)->y+(r)->h)
#define vrectMIsEqualLong(r1, r2) \
    ((r1)->x==(r2)->x && (r1)->y==(r2)->y && \
     (r1)->w==(r2)->w && (r1)->h==(r2)->h)
#define vrectMIntersectsLong(r1, r2) \
    ((r1)->x+(r1)->w>(r2)->x && (r2)->x+(r2)->w>(r1)->x && \
     (r1)->y+(r1)->h>(r2)->y && (r2)->y+(r2)->h>(r1)->y)
#define vrectMEnclosesLong(r1, r2) \
    ((r1)->x<=(r2)->x && (r1)->y<=(r2)->y && \
     (r1)->x+(r1)->w>=(r2)->x+(r2)->w && (r1)->y+(r1)->h>=(r2)->y+(r2)->h)

#if (vdebugDEBUG)
#define vrectCreateSetLong(n) \
    _vrectCreateSetLongDebug(n, vmemTAG, __FILE__, __LINE__)
#define vrectCloneSetLong(r, n) \
    _vrectCloneSetLongDebug(r, n, vmemTAG, __FILE__, __LINE__)
#define vrectIntersectSetsLong(r1, r2, n1, n2, n) \
    _vrectDissectSetsLong(r1, r2, n1, n2, 1, 2, 3, n, \
			  vmemTAG, __FILE__, __LINE__)
#define vrectUnionSetsLong(r1, r2, n1, n2, n) \
    _vrectDissectSetsLong(r1, r2, n1, n2, 1, 1, 1, n, \
			  vmemTAG, __FILE__, __LINE__)
#define vrectDifferenceSetsLong(r1, r2, n1, n2, n) \
    _vrectDissectSetsLong(r1, r2, n1, n2, 1, 2, 1, n, \
			  vmemTAG, __FILE__, __LINE__)
#else
#define vrectCreateSetLong(n) \
    _vrectCreateSetLongDebug(n)
#define vrectCloneSetLong(r, n) \
    _vrectCloneSetLongDebug(r, n)
#define vrectIntersectSetsLong(r1, r2, n1, n2, n) \
    _vrectDissectSetsLong(r1, r2, n1, n2, 1, 2, 3, n)
#define vrectUnionSetsLong(r1, r2, n1, n2, n) \
    _vrectDissectSetsLong(r1, r2, n1, n2, 1, 1, 1, n)
#define vrectDifferenceSetsLong(r1, r2, n1, n2, n) \
    _vrectDissectSetsLong(r1, r2, n1, n2, 1, 2, 1, n)
#endif


#define _vrectGetX(r)			((r)->x)
#define _vrectGetY(r)			((r)->y)
#define _vrectGetWidth(r)		((r)->w)
#define _vrectGetHeight(r)		((r)->h)
#define _vrectSetX(r, xv)		((r)->x = xv)
#define _vrectSetY(r, yv)		((r)->y = yv)
#define _vrectSetWidth(r, wv)		((r)->w = wv)
#define _vrectSetHeight(r, hv)		((r)->h = hv)

#define _vrectGetXLong(r)		((r)->x)
#define _vrectGetYLong(r)		((r)->y)
#define _vrectGetWidthLong(r)		((r)->w)
#define _vrectGetHeightLong(r)		((r)->h)
#define _vrectSetXLong(r, xv)		((r)->x = xv)
#define _vrectSetYLong(r, yv)		((r)->y = yv)
#define _vrectSetWidthLong(r, wv)	((r)->w = wv)
#define _vrectSetHeightLong(r, hv)	((r)->h = hv)

#define _vrectGetXFixed(r)		((r)->x)
#define _vrectGetYFixed(r)		((r)->y)
#define _vrectGetWidthFixed(r)		((r)->w)
#define _vrectGetHeightFixed(r)		((r)->h)
#define _vrectSetXFixed(r, xv)		((r)->x = xv)
#define _vrectSetYFixed(r, yv)		((r)->y = yv)
#define _vrectSetWidthFixed(r, wv)	((r)->w = wv)
#define _vrectSetHeightFixed(r, hv)	((r)->h = hv)

#define _vrectGetXFloat(r)		((double)((r)->x))
#define _vrectGetYFloat(r)		((double)((r)->y))
#define _vrectGetWidthFloat(r)		((double)((r)->w))
#define _vrectGetHeightFloat(r)		((double)((r)->h))
#define _vrectSetXFloat(r, xv)		((r)->x = (float)xv)
#define _vrectSetYFloat(r, yv)		((r)->y = (float)yv)
#define _vrectSetWidthFloat(r, wv)	((r)->w = (float)wv)
#define _vrectSetHeightFloat(r, hv)	((r)->h = (float)hv)


vportEND_CPLUSPLUS_EXTERN_C

#endif /* #ifndef vrectINCLUDED */


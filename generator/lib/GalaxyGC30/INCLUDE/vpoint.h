/* $Id: vpoint.h,v 1.24 1996/03/23 00:40:44 chad Exp $ */

/************************************************************

    vpoint.h

    C Interface file for the Point Library

    (c) Copyright Visix Software Inc.
    All rights reserved

************************************************************/

#ifndef vpointINCLUDED
#define vpointINCLUDED 1

#ifndef  vportINCLUDED
#include <vport.h>
#endif

#ifndef  vfixedINCLUDED
#include vfixedHEADER
#endif

#ifndef  vrectINCLUDED
#include vrectHEADER
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * * * * * * * * * * PUBLIC TYPE DEFINITIONS * * * * * * * * * *
 */

typedef struct vpoint               vpoint;
typedef struct vpointLong           vpointLong;
typedef struct vpointFloat          vpointFloat;
typedef struct vpointFixed          vpointFixed;

struct vpoint {
    short                           x, y;
};

struct vpointLong {
    long                            x, y;
};

struct vpointFloat {
    float                           x, y;
};

struct vpointFixed {
    vfixed                          x, y;
};

/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */

/*
 * points
 */

const vpoint *vpointNull(
    void
    );

int vpointIsEqual(
    const vpoint                   *point1,
    const vpoint                   *point2
    );

int vpointMIsEqual(
    const vpoint                   *point1,
    const vpoint                   *point2
    );

int vpointInsideRect(
    const vpoint                   *point,
    const vrect                    *rect
    );

int vpointMInsideRect(
    const vpoint                   *point,
    const vrect                    *rect
    );

int vpointInsideRectSet(
    const vpoint                   *point,
    const vrect                    *rects,
    int                             count
    );

void vpointSet(
    int                             x,
    int                             y,
    vpoint                         *rpoint
    );

void vpointSetRect(
    const vpoint                   *point0,
    const vpoint                   *point1,
    vrect                          *rrect
    );

void vpointAdd(
    const vpoint                   *point1,
    const vpoint                   *point2,
    vpoint                         *rpoint
    );

void vpointMAdd(
    const vpoint                   *point1,
    const vpoint                   *point2,
    vpoint                         *rpoint
    );

void vpointSub(
    const vpoint                   *point1,
    const vpoint                   *point2,
    vpoint                         *rpoint
    );

void vpointMSub(
    const vpoint                   *point1,
    const vpoint                   *point2,
    vpoint                         *rpoint
    );

void vpointRectPin(
    const vpoint                   *point,
    const vrect                    *rect,
    vpoint                         *rpoint
    );

/*
 * long points
 */

const vpointLong *vpointNullLong(
    void
    );

int vpointIsEqualLong(
    const vpointLong               *point1,
    const vpointLong               *point2
    );

int vpointMIsEqualLong(
    const vpointLong               *point1,
    const vpointLong               *point2
    );

int vpointInsideRectLong(
    const vpointLong               *point,
    const vrectLong                *rect
    );

int vpointMInsideRectLong(
    const vpointLong               *point,
    const vrectLong                *rect
    );

int vpointInsideRectSetLong(
    const vpointLong               *point,
    const vrectLong                *rects,
    int                             count
    );

void vpointSetLong(
    long                            x,
    long                            y,
    vpointLong                     *rpoint
    );

void vpointSetRectLong(
    const vpointLong               *point0,
    const vpointLong               *point1,
    vrectLong                      *rrect
    );

void vpointAddLong(
    const vpointLong               *point1,
    const vpointLong               *point2,
    vpointLong                     *rpoint
    );

void vpointMAddLong(
    const vpointLong               *point1,
    const vpointLong               *point2,
    vpointLong                     *rpoint
    );

void vpointSubLong(
    const vpointLong               *point1,
    const vpointLong               *point2,
    vpointLong                     *rpoint
    );

void vpointMSubLong(
    const vpointLong               *point1,
    const vpointLong               *point2,
    vpointLong                     *rpoint
    );

void vpointRectPinLong(
    const vpointLong               *point,
    const vrectLong                *rect,
    vpointLong                     *rpoint
    );

/*
 * * * * * * * * * * PRIVATE FUNCTION PROTOTYPES * * * * * * * * * *
 */

void	_vpointCopy(const vpoint *point, vpoint *rpoint);
short	_vpointGetX(const vpoint *point);
short	_vpointGetY(const vpoint *point);
void	_vpointSetX(vpoint *point, int x);
void	_vpointSetY(vpoint *point, int y);

void	_vpointCopyLong(const vpointLong *point, vpointLong *rpoint);
long	_vpointGetXLong(const vpointLong *point);
long	_vpointGetYLong(const vpointLong *point);
void	_vpointSetXLong(vpointLong *point, long x);
void	_vpointSetYLong(vpointLong *point, long y);

void	_vpointSetFixed(vfixed x, vfixed y, vpointFixed *rpoint);
void	_vpointCopyFixed(const vpointFixed *point, vpointFixed *rpoint);
vfixed	_vpointGetXFixed(const vpointFixed *point);
vfixed	_vpointGetYFixed(const vpointFixed *point);
void	_vpointSetXFixed(vpointFixed *point, vfixed x);
void	_vpointSetYFixed(vpointFixed *point, vfixed y);

void	_vpointSetFloat(double x, double y, vpointFloat *rpoint);
void	_vpointCopyFloat(const vpointFloat *point, vpointFloat *rpoint);
double	_vpointGetXFloat(const vpointFloat *point);
double	_vpointGetYFloat(const vpointFloat *point);
void	_vpointSetXFloat(vpointFloat *point, double x);
void	_vpointSetYFloat(vpointFloat *point, double y);

/*
 * * * * * * * * * * PRIVATE VARIABLE DECLARATIONS * * * * * * * * * *
 */

extern vportLINK const vpoint                 _vpointNull;
extern vportLINK const vpointLong             _vpointNullLong;

/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * *
 */

/*
 * points
 */

#define vpointNull()              (&_vpointNull)
#define vpointMIsEqual(p1, p2)    ((p1)->x==(p2)->x && (p1)->y==(p2)->y)
#define vpointInsideRect(p, r)      vrectContainsPoint(r, (p)->x, (p)->y)
#define vpointMInsideRect(p, r)     vrectMContainsPoint(r, (p)->x, (p)->y)
#define vpointInsideRectSet(p, r, n) \
    vrectSetContainsPoint(r, n, (p)->x, (p)->y)
#define vpointSet(px, py, p)        (void)((p)->x = (px), (p)->y = (py))
#define vpointSetRect(p0, p1, r) \
    vrectSetPoints((p0)->x, (p0)->y, (p1)->x, (p1)->y, r)
#define vpointMAdd(p1, p2, rp) \
    (void)((rp)->x = (p1)->x+(p2)->x, (rp)->y = (p1)->y+(p2)->y)
#define vpointMSub(p1, p2, rp) \
    (void)((rp)->x = (p1)->x-(p2)->x, (rp)->y = (p1)->y-(p2)->y)

/*
 * long points
 */

#define vpointNullLong()           (&_vpointNullLong)
#define vpointMIsEqualLong(p1, p2) ((p1)->x==(p2)->x && (p1)->y==(p2)->y)
#define vpointInsideRectLong(p, r)   vrectContainsPointLong(r, (p)->x, (p)->y)
#define vpointMInsideRectLong(p, r)  vrectMContainsPointLong(r, (p)->x, (p)->y)
#define vpointInsideRectSetLong(p, r, n) \
    vrectSetContainsPointLong(r, n, (p)->x, (p)->y)
#define vpointSetLong(px, py, p)    (void)((p)->x = (px), (p)->y = (py))
#define vpointSetRectLong(p0, p1, r) \
    vrectSetPointsLong((p0)->x, (p0)->y, (p1)->x, (p1)->y, r)
#define vpointMAddLong(p1, p2, rp) \
    (void)((rp)->x = (p1)->x+(p2)->x, (rp)->y = (p1)->y+(p2)->y)
#define vpointMSubLong(p1, p2, rp) \
    (void)((rp)->x = (p1)->x-(p2)->x, (rp)->y = (p1)->y-(p2)->y)


#define _vpointGetX(p)			((p)->x)
#define _vpointGetY(p)			((p)->y)
#define _vpointSetX(p, xv)		((p)->x = xv)
#define _vpointSetY(p, yv)		((p)->y = yv)

#define _vpointGetXLong(p)		((p)->x)
#define _vpointGetYLong(p)		((p)->y)
#define _vpointSetXLong(p, xv)		((p)->x = xv)
#define _vpointSetYLong(p, yv)		((p)->y = yv)

#define _vpointGetXFixed(p)		((p)->x)
#define _vpointGetYFixed(p)		((p)->y)
#define _vpointSetXFixed(p, xv)		((p)->x = xv)
#define _vpointSetYFixed(p, yv)		((p)->y = yv)

#define _vpointGetXFloat(p)		((double)((p)->x))
#define _vpointGetYFloat(p)		((double)((p)->y))
#define _vpointSetXFloat(p, xv)		((p)->x = (float)xv)
#define _vpointSetYFloat(p, yv)		((p)->y = (float)yv)


#define _vpointSetFixed(px, py, p) \
    { (p)->x = (px); (p)->y = (py); }
#define _vpointSetFloat(px, py, p) \
    { (p)->x = (float)(px); (p)->y = (float)(py); }

#define _vpointCopy(p, t) \
    { (t)->x = (p)->x; (t)->y = (p)->y; }
#define _vpointCopyLong(p, t) \
    { (t)->x = (p)->x; (t)->y = (p)->y; }
#define _vpointCopyFixed(p, t) \
    { (t)->x = (p)->x; (t)->y = (p)->y; }
#define _vpointCopyFloat(p, t) \
    { (t)->x = (p)->x; (t)->y = (p)->y; }


vportEND_CPLUSPLUS_EXTERN_C

#endif /* #ifndef vpointINCLUDED */


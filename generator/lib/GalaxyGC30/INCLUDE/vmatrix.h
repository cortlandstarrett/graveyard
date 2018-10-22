/* $Id: vmatrix.h,v 1.26 1996/09/01 18:47:52 abstine Exp $ */

/************************************************************

    vmatrix.h

    C Interface file for the Matrix Library

    (c) Copyright Visix Software Inc.
    All rights reserved

************************************************************/

#ifndef vmatrixINCLUDED
#define vmatrixINCLUDED 1

#ifndef  vportINCLUDED
#include <vport.h>
#endif

#ifndef  vcharINCLUDED
#include vcharHEADER
#endif

#ifndef  vrectINCLUDED
#include vrectHEADER
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * * * * * * * * * * PUBLIC CONSTANT DEFINITIONS * * * * * * * * * *
 */

#define vmatrixSTRING_MAX         (14*6+8)

/*
 * * * * * * * * * * PUBLIC TYPE DEFINITIONS * * * * * * * * * *
 */

typedef struct vmatrix              vmatrix;

struct vmatrix {
    float                           a, b, c, d;
    float                           tx, ty;
};

/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */

int vmatrixIsIdent(
    const vmatrix                  *mtx
    );

int vmatrixIsEqual(
    const vmatrix                  *mtx1, 
    const vmatrix                  *mtx2
    );

int vmatrixCompareDABC(
    const vmatrix                  *mtx1, 
    const vmatrix                  *mtx2,
    double                         *diff
    );

const vmatrix *vmatrixIdent(
    void
    );

void vmatrixConcat(
    const vmatrix                  *mtx1, 
    const vmatrix                  *mtx2,
    vmatrix                        *rmtx
    );

void vmatrixInvert(
    const vmatrix                  *mtx, 
    vmatrix                        *rmtx
    );

void vmatrixRotate(
    const vmatrix                  *mtx, 
    double                          angle,
    vmatrix                        *rmtx
    );

void vmatrixScale(
    const vmatrix                  *mtx, 
    double                          x,
    double                          y,
    vmatrix                        *rmtx
    );

void vmatrixTranslate(
    const vmatrix                  *mtx, 
    double                          x,
    double                          y,
    vmatrix                        *rmtx
    );

void vmatrixDTransform(
    const vmatrix                  *mtx, 
    double                          x,
    double                          y,
    double                         *rx,
    double                         *ry
    );

void vmatrixTransform(
    const vmatrix                  *mtx, 
    double                          x,
    double                          y,
    double                         *rx,
    double                         *ry
    );

void vmatrixRectTransform(
    const vmatrix                  *mtx, 
    const vrectFloat               *rect,
    vrectFloat                     *rrect
    );

void vmatrixToString(
    const vmatrix                  *mtx,
    vchar                          *rstr
    );
    
void vmatrixFromString(
    const vchar                    *str,
    vmatrix                        *rmtx
    );

/*
 * * * * * * * * * * PRIVATE FUNCTION PROTOTYPES * * * * * * * * * *
 */

void	_vmatrixSet(double a, double b, double c, double d,
		    double tx, double ty, vmatrix *matrix);
void	_vmatrixCopy(const vmatrix *matrix, vmatrix *rmatrix);
double	_vmatrixGetA(const vmatrix *matrix);
double	_vmatrixGetB(const vmatrix *matrix);
double	_vmatrixGetC(const vmatrix *matrix);
double	_vmatrixGetD(const vmatrix *matrix);
double	_vmatrixGetTX(const vmatrix *matrix);
double	_vmatrixGetTY(const vmatrix *matrix);
void	_vmatrixSetA(vmatrix *matrix, double x);
void	_vmatrixSetB(vmatrix *matrix, double y);
void	_vmatrixSetC(vmatrix *matrix, double width);
void	_vmatrixSetD(vmatrix *matrix, double height);
void	_vmatrixSetTX(vmatrix *matrix, double height);
void	_vmatrixSetTY(vmatrix *matrix, double height);

void	_vmatrixRotate(const vmatrix *, double x, vmatrix *rmtx);
void	_vmatrixScale(const vmatrix *, double x, double y, vmatrix *rmtx);
void	_vmatrixTranslate(const vmatrix *, double x, double y, vmatrix *rmtx);

void	_vmatrixDTransform(const vmatrix *matrix, double x, double y,
			   double *rx, double *ry);
void	_vmatrixTransform(const vmatrix *matrix, double x, double y,
			  double *rx, double *ry);


/*
 * * * * * * * * * * PRIVATE VARIABLE DECLARATIONS * * * * * * * * * *
 */

extern vportLINK const vmatrix                _vmatrixIdent;

#if !(vportREENTRANT)
extern vportLINK double                       _vmatrixDouble;
#endif
/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * *
 */

#define vmatrixIdent()            (&_vmatrixIdent)
#if !(vportREENTRANT)
#define vmatrixIsEqual(m1, m2) \
    (vmatrixCompareDABC(m1, m2, &_vmatrixDouble)==0)
#endif

#define vmatrixIsIdent(m)           vmatrixIsEqual(m, &_vmatrixIdent)


#define _vmatrixGetA(m)		((double)((m)->a))
#define _vmatrixGetB(m)		((double)((m)->b))
#define _vmatrixGetC(m)		((double)((m)->c))
#define _vmatrixGetD(m)		((double)((m)->d))
#define _vmatrixGetTX(m)	((double)((m)->tx))
#define _vmatrixGetTY(m)	((double)((m)->ty))
#define _vmatrixSetA(m, av)	((m)->a = (float)av)
#define _vmatrixSetB(m, bv)	((m)->b = (float)bv)
#define _vmatrixSetC(m, cv)	((m)->c = (float)cv)
#define _vmatrixSetD(m, dv)	((m)->d = (float)dv)
#define _vmatrixSetTX(m, txv)	((m)->tx = (float)txv)
#define _vmatrixSetTY(m, tyv)	((m)->ty = (float)tyv)

#define vmatrixRotate(m, a, rm)	_vmatrixRotate(m, (double)(a), rm)
#define vmatrixScale(m, x, y, rm) \
    _vmatrixScale(m, (double)(x), (double)(y), rm)
#define vmatrixTranslate(m, x, y, rm) \
    _vmatrixTranslate(m, (double)(x), (double)(y), rm)

#define vmatrixDTransform(m, x, y, rx, ry) \
    _vmatrixDTransform(m, (double)(x), (double)(y), rx, ry)
#define vmatrixTransform(m, x, y, rx, ry) \
    _vmatrixTransform(m, (double)(x), (double)(y), rx, ry)

vportEND_CPLUSPLUS_EXTERN_C

#endif /* #ifndef vmatrixINCLUDED */


/* $Id: vtransform.h,v 1.16 1996/03/23 00:40:49 chad Exp $ */

/************************************************************

    vtransform.h

    C Interface file for the Transformation Library

    (c) Copyright Visix Software Inc.
    All rights reserved

************************************************************/

#ifndef vtransformINCLUDED
#define vtransformINCLUDED 1

#ifndef  vportINCLUDED
#include <vport.h>
#endif

#ifndef  vfloatINCLUDED
#include vfloatHEADER
#endif

#ifndef  vfixedINCLUDED
#include vfixedHEADER
#endif

#ifndef  vmatrixINCLUDED
#include vmatrixHEADER
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * * * * * * * * * * PUBLIC CONSTANT DEFINITIONS * * * * * * * * * *
 */

enum {
    vtransformTRANSLATE_X           = 0x0001,
    vtransformTRANSLATE_Y           = 0x0002,
    vtransformTRANSLATE             = 
	vtransformTRANSLATE_X|vtransformTRANSLATE_Y,
    vtransformINVERT_X              = 0x0004,
    vtransformINVERT_Y              = 0x0008,
    vtransformINVERT                = vtransformINVERT_X|vtransformINVERT_Y,
    vtransformSCALE_X               = 0x0010,
    vtransformSCALE_Y               = 0x0020,
    vtransformSCALE                 = vtransformSCALE_X|vtransformSCALE_Y,
    vtransformROTATE                = 0x0040
};

/*
 * * * * * * * * * * PUBLIC TYPE DEFINITIONS * * * * * * * * * *
 */

typedef struct vtransform           vtransform;

struct vtransform {
    unsigned short                  flags;
    vfixed                          a, b, c, d;
    vfixed                          tx, ty;
};

/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */

const vtransform *vtransformIdent(
    void
    );

void vtransformInvert(
    const vtransform               *transform,
    vtransform                     *rtransform
    );

void vtransformRound(
    const vtransform               *transform,
    vtransform                     *rtransform
    );

void vtransformFromMatrix(
    const vmatrix                  *mtx,
    vtransform                     *transform
    );

void vtransformToMatrix(
    const vtransform               *transform,
    vmatrix                        *mtx
    );

/*
 * * * * * * * * * * PRIVATE FUNCTION PROTOTYPES * * * * * * * * * *
 */

void		_vtransformCopy(const vtransform *transform,
				vtransform *rtransform);
vfixed		_vtransformGetA(const vtransform *transform);
vfixed		_vtransformGetB(const vtransform *transform);
vfixed		_vtransformGetC(const vtransform *transform);
vfixed		_vtransformGetD(const vtransform *transform);
vfixed		_vtransformGetTX(const vtransform *transform);
vfixed		_vtransformGetTY(const vtransform *transform);
unsigned int	_vtransformGetComplexity(const vtransform *transform);
void		_vtransformSetA(vtransform *transform, vfixed x);
void		_vtransformSetB(vtransform *transform, vfixed y);
void		_vtransformSetC(vtransform *transform, vfixed width);
void		_vtransformSetD(vtransform *transform, vfixed height);
void		_vtransformSetTX(vtransform *transform, vfixed height);
void		_vtransformSetTY(vtransform *transform, vfixed height);
void		_vtransformSetComplexity(vtransform *transform,
					 unsigned int complexity);

/*
 * * * * * * * * * * PRIVATE VARIABLE DECLARATIONS * * * * * * * * * *
 */

extern vportLINK const vtransform             _vtransformIdent;

/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * *
 */

#define vtransformIdent()         (&_vtransformIdent)

#define _vtransformGetA(m)		((m)->a)
#define _vtransformGetB(m)		((m)->b)
#define _vtransformGetC(m)		((m)->c)
#define _vtransformGetD(m)		((m)->d)
#define _vtransformGetTX(m)		((m)->tx)
#define _vtransformGetTY(m)		((m)->ty)
#define _vtransformGetComplexity(m)	((unsigned int)((m)->flags))
#define _vtransformSetA(m, av)	 	((m)->a = av)
#define _vtransformSetB(m, bv)		((m)->b = bv)
#define _vtransformSetC(m, cv)		((m)->c = cv)
#define _vtransformSetD(m, dv)		((m)->d = dv)
#define _vtransformSetTX(m, txv)	((m)->tx = txv)
#define _vtransformSetTY(m, tyv)	((m)->ty = tyv)
#define _vtransformSetComplexity(m, f)	((m)->flags = (unsigned short)(f))


vportEND_CPLUSPLUS_EXTERN_C

#endif /* #ifndef vtransformINCLUDED */


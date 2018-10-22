/* $Id: vfixed.h,v 1.19 1997/09/22 20:38:49 chad Exp $ */

/************************************************************

    vfixed.h

    C Interface file for the Fixed Point Library

    (c) Copyright Visix Software Inc.
    All rights reserved

************************************************************/

#ifndef vfixedINCLUDED
#define vfixedINCLUDED 1

#ifndef  vportINCLUDED
#include <vport.h>
#endif

#ifndef  vlimitsINCLUDED
#include vlimitsHEADER
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * * * * * * * * * * PUBLIC CONSTANT DEFINITIONS * * * * * * * * * *
 */

#define vfixedFRAC_BITS		  (vportLONG_BIT/2)
#define vfixedZERO		  ((vfixed)0)
#define vfixedONE		 (((vfixed)1)<<vfixedFRAC_BITS)
#define vfixedEPSILON             ((vfixed)1)
#define vfixedMAX		  ((vfixed)LONG_MAX)
#define vfixedMIN		  ((vfixed)LONG_MIN)

/*
 * * * * * * * * * * PUBLIC TYPE DEFINITIONS * * * * * * * * * *
 */

typedef long			    vfixed;

/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */

vfixed vfixedFromInt(
    int				    n
    );

vfixed vfixedFromFloat(
    double			    x
    );

int vfixedToInt(
    vfixed			    x
    );

double vfixedToFloat(
    vfixed			    x
    );

vfixed vfixedFloor(
    vfixed			    x
    );

vfixed vfixedCeil(
    vfixed			    x
    );

vfixed vfixedRound(
    vfixed			    x
    );

vfixed vfixedAbs(
    vfixed			    x
    );

vfixed vfixedMul(
    vfixed			    x,
    vfixed			    y
    );

vfixed vfixedMulQuick(
    vfixed			    x,
    vfixed			    y
    );

vfixed vfixedDiv(
    vfixed			    x,
    vfixed			    y
    );

vfixed vfixedDivQuick(
    vfixed			    x,
    vfixed			    y
    );

/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * *
 */

#define vfixedFromInt(n)	  ((vfixed)(n)<<vfixedFRAC_BITS)

vfixed _vfixedFromFloat(double x);
#define vfixedFromFloat(x)	    _vfixedFromFloat((double)(x))

#if (vportRIGHT_SHIFT_ARITHMETIC)
#define vfixedToInt(x)		  ((int)((x)>>(vfixed)vfixedFRAC_BITS))
#else
#define vfixedToInt(x)		  ((int)((x)/vfixedONE))
#endif

#define vfixedToFloat(x)	  ((double)(x)/vfixedONE)
#define vfixedFloor(x)		  ((x)&~(vfixedONE-1))
#define vfixedCeil(x)		    vfixedFloor((x)+vfixedONE-1)
#define vfixedRound(x)		    vfixedFloor((x)+vfixedONE/2)

#if (vportRIGHT_SHIFT_ARITHMETIC)
#define vfixedMulQuick(x, y) \
    (((x)>>(vfixed)vfixedFRAC_BITS/2)*((y)>>(vfixed)vfixedFRAC_BITS/2))
#define vfixedDivQuick(x, y) \
    (((x)/((y)>>vfixedFRAC_BITS*3/4))<<vfixedFRAC_BITS/4)
#else
#define vfixedMulQuick(x, y) \
    (((x)/(1<<vfixedFRAC_BITS/2))*((y)/(1<<vfixedFRAC_BITS/2)))
#define vfixedDivQuick(x, y) \
    (((x)/((y)/(vfixedONE*3/4)))<<vfixedFRAC_BITS/4)
#endif

vportEND_CPLUSPLUS_EXTERN_C

#endif /* #ifndef vfixedINCLUDED */


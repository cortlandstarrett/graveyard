/* $Id: vmath.h,v 1.18 1997/04/21 16:54:05 robert Exp $ */

#ifndef vmathINCLUDED
#define vmathINCLUDED

/*
        +---------------------------------------------------------------+
        |                                                               |
        |            vmath.h - Visix Math Header                        |
        |            ========================================           |
        |                                                               |
        +---------------------------------------------------------------+
        |                                                               |
        | (c) Copyright 1991, Visix Software, Inc., All rights reserved.|
        |                                                               |
        +---------------------------------------------------------------+
        |                                                               |
        |                          DESCRIPTION                          |
        |                          ===========                          |
        |                                                               |
        |       This file is intended to replace math.h with            |
        |       the "Right Thing", as defined by ANSI C.                |
        |                                                               |
        +---------------------------------------------------------------+
*/


/*
 * Include any files this header depends upon
 */

#ifndef vportINCLUDED
#include <vport.h>
#endif


/*
 * Include the system version of math.h, if its not too bad
 */

vportBEGIN_CPLUSPLUS_HEADER_PROTECTION

/*
 * protect math.h from our C++ keyword class MACRO
 */

#if (!vportDONT_MACRO_CPLUSPLUS_KEYWORDS && !defined(__cplusplus))
#undef class
#endif

#if ( ! vportBAD_MATH_HDR )
#include <math.h>
#endif

#if ( vportUSE_FPMATH_HDR )
#include <fp.h>
#endif

#if (!vportDONT_MACRO_CPLUSPLUS_KEYWORDS && !defined(__cplusplus))
#define class vportBREAK_class
#endif

vportEND_CPLUSPLUS_HEADER_PROTECTION


/*
 * Fix up anything that may have been wrong
 */


/*
 * Add some more useful stuff
 */

vportBEGIN_CPLUSPLUS_EXTERN_C

double vmathINFINITY        (void);
double vmathNAN             (void);

double vmathRound           (double d);   /* deprecated; backward compat */

long   vmathRoundTowardsZero(double d);

int    vmathFloatIsInfinite (double d);
int    vmathFloatIsNaN      (double d);
int    vmathFloatIsZero     (double d);
int    vmathFloatHasSignBit (double d);

vportEND_CPLUSPLUS_EXTERN_C

#define vmathINFINITY()         (HUGE_VAL)
#define vmathNAN()              (vportNAN)

#define vmathRound(x)           floor((x)+0.5)

#if (vportDOUBLE_CAST_LONG_ROUNDS_TOWARD_ZERO)
#define vmathRoundTowardsZero(x)        (x)
#elif (vportDOUBLE_CAST_LONG_TRUNCATES_TOWARD_ZERO)
#define vmathRoundTowardsZero(x)        ((x)>0.0 ? (x)+0.5 : (x)-0.5)
#elif (vportDOUBLE_CAST_LONG_TRUNCATES_DOWN)
#define vmathRoundTowardsZero(x)        ((x)+0.5)
#elif (vportDOUBLE_CAST_LONG_TRUNCATES_UP)
#define vmathRoundTowardsZero(x)        ((x)-0.5)
#else
#define vmathRoundTowardsZero(x)        vmathRound(x)
#endif

#if (vportPRE_SUN_OS_5_0)
#define vmathFloatIsInfinite(d) (isinf(d))
#define vmathFloatIsNaN(d)      (isnan(d))
#define vmathFloatIsZero(d)     (iszero(d))
#define vmathFloatHasSignBit(d) (signbit(d))
#else
#define vmathFloatIsInfinite(d) ((d)>=vmathINFINITY()||(d)<=-vmathINFINITY())
#define vmathFloatIsNaN(d)      ((d)==vmathNAN())
#define vmathFloatIsZero(d)     ((d)==0.0||(d)==-0.0)
#define vmathFloatHasSignBit(d) ((d)<0)
#endif

#ifndef vmathPI
#ifdef M_PI
#define vmathPI M_PI
#else
#define M_PI 3.14159265358979323846
#define vmathPI M_PI
#endif
#endif

#ifndef vmathPI2
#ifdef M_PI_2
#define vmathPI2 M_PI_2
#else
#define vmathPI2 1.57079632679489661923
#endif
#endif

#ifndef vmath2PI
#define vmath2PI (vmathPI + vmathPI)
#endif

#ifndef vmathE
#ifdef M_E
#define vmathE M_E
#else
#define vmathE 2.7182818284590452354
#endif
#endif

#endif /* #ifndef vmathINCLUDED */

/*
 * Formatting information for emacs
 *
 * Local Variables:
 * c-argdecl-indent:4
 * c-brace-imaginary-offset:0
 * c-brace-offset:-4
 * c-continued-brace-offset:0
 * c-continued-statement-offset:4
 * c-extra-brace-offset:0
 * c-file-offsets:((block-open . -))
 * c-file-style:"BSD"
 * c-indent-level:4
 * c-label-offset:-4
 * tab-stop-list:(4 8 12 16 20 24 28 32 36 40 44 48 52 56 60 64 68 72 76 80) 
 * tab-width:4
 * End:
 */


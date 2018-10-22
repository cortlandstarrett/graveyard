/* $Id: vfloat.h,v 1.6 1994/08/31 19:31:27 chad Exp $ */

#ifndef vfloatINCLUDED
#define vfloatINCLUDED 1

/*
	+---------------------------------------------------------------+
	|								|
	|	     vfloat.h - Visix Float Header			|
	|								|
	+---------------------------------------------------------------+
	|								|
	| (c) Copyright 1990, Visix Software, Inc., All rights reserved.|
	|								|
	+---------------------------------------------------------------+
	|								|
	|			   DESCRIPTION				|
	|			   ===========				|
	|								|
	|	This file is intended to replace float.h with		|
	|	the "Right Thing".  To use this file, replace any	|
	|	instances of #include <float.h> with			|
	|	#include <vfloat.h>.					|
	|								|
	+---------------------------------------------------------------+
*/


/*
 * Include any files this header depends upon
 */

#ifndef  vportINCLUDED		/* for v*HEADER */
#include <vport.h>
#endif

#ifndef  vlimitsINCLUDED	/* some FLT_* constants are here */
#include vlimitsHEADER
#endif


/*
 * Include the system version of float.h, if it isn't too bad
 */

vportBEGIN_CPLUSPLUS_HEADER_PROTECTION

#if ( ! vportBAD_FLOAT_HDR )
#include <float.h>
#endif

vportEND_CPLUSPLUS_HEADER_PROTECTION


/*
 * Fix up anything that may have been wrong with the system version of float.h
 */

#ifndef FLT_RADIX
#define FLT_RADIX	2	/* radix of exponent representation */
#endif

#ifndef FLT_ROUNDS
#define FLT_ROUNDS	(-1)	/* rounding mode for floating pt. addition; */
				/* 0:towards zero, 1:to nearest, 2:toward   */
				/* +infinity, 3:toward -infinity,  */
				/* -1:indeterminable  */
#endif

#ifndef FLT_MAX
#define FLT_MAX		(1E+37)	/* from K&R C v2.0 pg.257 */
#endif

#ifndef FLT_MIN
#define FLT_MIN		(1E-37)	/* from K&R C v2.0 pg.257 */
#endif

#ifndef FLT_DIG
#define FLT_DIG		6	/* digits of precision of a "float" */
				/* from K&R C v2.0 pg.258 */
#endif

#ifndef DBL_MAX
#define DBL_MAX		(1E+37)	/* max value of a "double" */
				/* from K&R C v2.0 pg.258 */
#endif

#ifndef DBL_MIN
#define DBL_MIN		(1E-37)	/* min decimal value of a "double" */
				/* from K&R C v2.0 pg.258 */
#endif

#ifndef DBL_DIG
#define DBL_DIG		10	/* number of digits of precision of a "double" */
				/* from K&R C v2.0 pg.258 */
#endif

#ifndef FLT_MANT_DIG
#define FLT_MANT_DIG	15	/* number of digits in floating pt mantissa */
#endif

#ifndef FLT_EPSILON
#define FLT_EPSILON	(1E-5)	/* from K&R C v2.0 pg. 257 */
#endif

#ifndef FLT_MIN_EXP
#define FLT_MIN_EXP	(-148)	/* min integer such that 2**FLT_MIN_EXP-1 is a normalized number */
#endif

#ifndef FLT_MIN_10_EXP
#define FLT_MIN_10_EXP	(-37)	/* min integer such that 10**FLT_MIN_10_EXP */
				/* is a normalized number */
#endif

#ifndef FLT_MAX_EXP
#define FLT_MAX_EXP	128	/* max integer such that 2**FLT_MAX_EXP-1 is a normalized float number */
#endif

#ifndef FLT_MAX_10_EXP
#define FLT_MAX_10_EXP	37	/* max integer such that 10**FLT_MAX_10_EXP */
				/* is a finite representable number */
#endif

#ifndef DBL_MANT_DIG
#define DBL_MANT_DIG	50	/* number of digits in floating pt mantissa */
#endif

#ifndef DBL_EPSILON
#define DBL_EPSILON	(1E-9)	/* min positive floating point number x such*/
				/* that 1+x != 1.0,b**(e-max)		*/
				/* from K&R C v2.0 pg.258 */
#endif

#ifndef DBL_MIN_EXP
#define DBL_MIN_EXP	(-1073) /* min integer such that 2**DBL_MIN_EXP-1 is a normalized number */
#endif

#ifndef DBL_MIN_10_EXP
#define DBL_MIN_10_EXP	(-307)	/* min integer such that 10**DBL_MIN_10_EXP */
				/* is a normalized number */
#endif

#ifndef DBL_MAX_EXP
#define DBL_MAX_EXP	1024	/* max integer such that 2**DBL_MAX_EXP-1 is a representable finite number */ 
#endif

#ifndef DBL_MAX_10_EXP
#define DBL_MAX_10_EXP	307	/* max integer such that 10**DBL_MAX_10_EXP */
				/* is a finite representable number */
#endif

#ifndef LDBL_MANT_DIG
#define LDBL_MANT_DIG	53	/* number digits in mantissa; same as for DBL */
#endif

#ifndef LDBL_EPSILON
#define LDBL_EPSILON	(1E-16)	/* min positive floating point number x such */
				/* that 1+x != 1.0,b**(e-max)		*/
#endif

#ifndef LDBL_DIG
#define LDBL_DIG	15	/* number of decimal digits of precision */
#endif

#ifndef LDBL_MIN_EXP
#define LDBL_MIN_EXP	(-1023)	/* min negative integer such that FLT_RADIX**  */
				/* LDBL_MIN_EXP is normalized float-point numbr*/
#endif

#ifndef LDBL_MIN
#define LDBL_MIN	(1E-307)	/* min normalized double */
#endif

#ifndef LDBL_MIN_10_EXP
#define LDBL_MIN_10_EXP (-307)	/* min negative integer such that 10**LDBL_MIN*/
				/*_10_EXP    is in range of normalized numbers*/
#endif

#ifndef LDBL_MAX_EXP
#define LDBL_MAX_EXP	1023	/* max integer such that FLT_RADIX raised to  */
				/* that power - 1 is a representable finite   */
				/* floating point number		      */
#endif

#ifndef LDBL_MAX
#define LDBL_MAX	(1E+307)	/* max representable finit floating point no. */
#endif

#ifndef LDBL_MAX_10_EXP
#define LDBL_MAX_10_EXP 307	/* max integer such that 10**LDBL_MAX_10_EXP  */
				/* is a representable finite float-point number*/
#endif


/*
 * * * * * * * * * * * * * * * * Miscellaneous * * * * * * * * * * * * * * * *
 */

/*
 * Formatting information for emacs in c-mode
 *
 * Local Variables:
 * c-indent-level:4
 * c-continued-statement-offset:2
 * c-brace-offset:-2
 * c-brace-imaginary-offset:0
 * c-argdecl-indent:4
 * c-label-offset:-2
 * End:
 */

#endif /* vfloatINCLUDED */


/* $Id: vlonglong.h,v 1.33 1997/04/17 21:25:55 scotth Exp $ */

#ifndef vlonglongINCLUDED
#define vlonglongINCLUDED 1

/*
 * Include any other files this header depends upon
 */

#ifndef  vportINCLUDED		/* for v*HEADER */
#include <vport.h>
#endif

#ifndef  vstdINCLUDED		/* for vbool */
#include vstdHEADER
#endif

#ifndef  vlimitsINCLUDED
#include vlimitsHEADER
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C

/************************************************************************
  MACROS
 ************************************************************************/

#define vlonglongSCALAR \
    (vportLONG_BIT>=64 || (vportHAS_LONG_LONG && vportUSE_LONG_LONG) || \
     vportWIN32_MSVC)

#if vlonglongSCALAR
# if (_AIX32 || (__hp9000s700 || __hp9000s800))
# define vlonglongCONSTANT(l) l##ll
# else
# define vlonglongCONSTANT(l) l
# endif
#endif


/************************************************************************
  CONSTANTS
 ************************************************************************/

#define vlonglongBIT (LONG_BIT+32)


/************************************************************************
  TYPES
 ************************************************************************/

#if (vportLONG_BIT >= 64)

typedef long vlonglong;

#elif vportHAS_LONG_LONG && vportUSE_LONG_LONG

typedef long long vlonglong;

#elif (vportWIN32_MSVC)

typedef __int64 vlonglong;

#else

/*
 * ASSUMPTION : long is 4 bytes
 * so create an 8 byte struct from 2 longs
 */
typedef struct vlonglong {
#if (vportBIG_ENDIAN_LONG)
  long		high;
  unsigned long	low;
#else
  unsigned long	low;
  long		high;
#endif
} vlonglong;

#endif


/************************************************************************
  PROTOTYPES
 ************************************************************************/

long		 vlonglongGetHigh( vlonglong ll );
unsigned long	 vlonglongGetLow( vlonglong ll );
vlonglong	 vlonglongMake( long high, unsigned long low );
vlonglong	 vlonglongConstructLiteral( long high, unsigned long low );

vbool		 vlonglongGreaterThan( vlonglong a, vlonglong b );
vbool		 vlonglongGreaterThanUnsigned( vlonglong a, vlonglong b );
vbool		 vlonglongLessThan( vlonglong a, vlonglong b );
vbool		 vlonglongLessThanUnsigned( vlonglong a, vlonglong b );
vbool		 vlonglongEqualTo( vlonglong a, vlonglong b );
vbool		 vlonglongIsZero( vlonglong a );

int		 vlonglongCompare( vlonglong a, vlonglong b );
int		 vlonglongCompareUnsigned( vlonglong a, vlonglong b );

vlonglong        vlonglongAdd( vlonglong a, vlonglong b );
vlonglong        vlonglongSubtract( vlonglong a, vlonglong b );
vlonglong        vlonglongMultiply( vlonglong a, vlonglong b );
vlonglong        vlonglongDivide( vlonglong a, vlonglong b );
vlonglong        vlonglongRemainder( vlonglong a, vlonglong b );
void             vlonglongDivideRemainder( vlonglong a, vlonglong b,
					   vlonglong *q, vlonglong *r );

vlonglong        vlonglongNegate( vlonglong a );
vlonglong	 vlonglongIncrement( vlonglong a);
vlonglong	 vlonglongDecrement( vlonglong a);

vlonglong        vlonglongShiftLeft( vlonglong a, unsigned int n );
vlonglong        vlonglongShiftRight( vlonglong a, unsigned int n );
vlonglong        vlonglongShiftRightArithmetic( vlonglong a, unsigned int n );

vlonglong        vlonglongAnd( vlonglong a, vlonglong b );
vlonglong        vlonglongOr( vlonglong a, vlonglong b );
vlonglong        vlonglongXor( vlonglong a, vlonglong b );
vlonglong        vlonglongComplement( vlonglong a );

vlonglong        vlonglongFromInteger( long n );
long             vlonglongToInteger( vlonglong a );
vlonglong        vlonglongFromUnsignedInteger( unsigned long n );
unsigned long    vlonglongToUnsignedInteger( vlonglong a );
vlonglong        vlonglongFromFloat( double x );
double           vlonglongToFloat( vlonglong a );
vlonglong        vlonglongUnsignedFromFloat( double x );
double           vlonglongUnsignedToFloat( vlonglong a );


/************************************************************************
  PRIVATE PROTOTYPES
 ************************************************************************/

#if (!vlonglongSCALAR)

vlonglong	 _vlonglongMake( long high, unsigned long low );

vlonglong        _vlonglongAdd( vlonglong a, vlonglong b );
vlonglong        _vlonglongSubtract( vlonglong a, vlonglong b );
vlonglong        _vlonglongMultiply( vlonglong a, vlonglong b );
vlonglong        _vlonglongDivide( vlonglong a, vlonglong b );
vlonglong        _vlonglongRemainder( vlonglong a, vlonglong b );
void             _vlonglongDivideRemainder( vlonglong a, vlonglong b,
					    vlonglong *q, vlonglong *r );

vlonglong        _vlonglongNegate( vlonglong a );
vlonglong	 _vlonglongIncrement( vlonglong a);
vlonglong	 _vlonglongDecrement( vlonglong a);

vlonglong        _vlonglongShiftLeft( vlonglong a, unsigned int n );
vlonglong        _vlonglongShiftRight( vlonglong a, unsigned int n );
vlonglong        _vlonglongShiftRightArithmetic( vlonglong a, unsigned int n );

vlonglong        _vlonglongAnd( vlonglong a, vlonglong b );
vlonglong        _vlonglongOr( vlonglong a, vlonglong b );
vlonglong        _vlonglongXor( vlonglong a, vlonglong b );
vlonglong        _vlonglongComplement( vlonglong a );

vlonglong        _vlonglongFromInteger( long n );
long             _vlonglongToInteger( vlonglong a );
vlonglong        _vlonglongFromUnsignedInteger( unsigned long n );
unsigned long    _vlonglongToUnsignedInteger( vlonglong a );
vlonglong        _vlonglongFromFloat( double x );
double           _vlonglongToFloat( vlonglong a );
vlonglong        _vlonglongUnsignedFromFloat( double x );
double           _vlonglongUnsignedToFloat( vlonglong a );

#endif /* #if !vlonglongSCALAR */


/************************************************************************
  MACROS
 ************************************************************************/


#if (vlonglongSCALAR)

#define vlonglongGetHigh( vll )		  ((long)((vll) >> 32))
#define vlonglongGetLow( vll )		  ((unsigned long)((vll) & 0xffffffff))
#define vlonglongMake( h, l )             (((vlonglong)(h) << 32) \
					   | (vlonglong)(l))
#define vlonglongConstructLiteral( h, l ) (((vlonglong)(h) << 32) \
					   | (vlonglong)(l))

#define vlonglongGreaterThan( a, b )	  ((a) > (b))
#define vlonglongLessThan( a, b )	  ((a) < (b))
#define vlonglongEqualTo( a, b )	  ((a) == (b))
#define vlonglongIsZero( a )              ((a) == 0)

#if (vportHAS_LONG_LONG && vportUSE_LONG_LONG)
#define vlonglongGreaterThanUnsigned( a, b ) \
    ((unsigned long long)(a) > (unsigned long long)(b))
#define vlonglongLessThanUnsigned( a, b ) \
    ((unsigned long long)(a) < (unsigned long long)(b))
#elif (vportWIN32_MSVC)
#define vlonglongGreaterThanUnsigned( a, b ) \
    ((unsigned __int64)(a) > (unsigned __int64)(b))
#define vlonglongLessThanUnsigned( a, b ) \
    ((unsigned __int64)(a) < (unsigned __int64)(b))
#else
#define vlonglongGreaterThanUnsigned( a, b ) \
    ((unsigned long)(a) > (unsigned long)(b))
#define vlonglongLessThanUnsigned( a, b ) \
    ((unsigned long)(a) < (unsigned long)(b))
#endif

#define vlonglongAdd( a, b )	          ((a) + (b))
#define vlonglongSubtract( a, b )	  ((a) - (b))
#define vlonglongMultiply( a, b )	  ((a) * (b))
#define vlonglongDivide( a, b )	          ((a) / (b))
#define vlonglongRemainder( a, b )	  ((a) % (b))
#define vlonglongDivideRemainder( a, b, q, r ) \
    ((void)(*(q) = (a) / (b), *(r) = (a) % (b)))

#define vlonglongNegate( a )	          (-(a))
#define vlonglongIncrement( a )	          (++(a))
#define vlonglongDecrement( a )	          (--(a))

#define vlonglongShiftLeft( a, n )	  ((a) << (n))

#if (vportHAS_LONG_LONG && vportUSE_LONG_LONG)
#define vlonglongShiftRight( a, n ) \
    ((vlonglong)(((unsigned long long)(a)) >> (n)))
#elif (vportWIN32_MSVC)
#define vlonglongShiftRight( a, n ) \
    ((vlonglong)(((unsigned __int64)(a)) >> (n)))
#else
#define vlonglongShiftRight( a, n ) \
    ((vlonglong)(((unsigned long)(a)) >> (n)))
#endif

#if (vportRIGHT_SHIFT_ARITHMETIC)
#define vlonglongShiftRightArithmetic( a, n )	  ((a) >> (n))
#else
#define vlonglongShiftRightArithmetic( a, n )	  ((a) / ((vlonglong)1 << (n)))
#endif

#define vlonglongAnd( a, b )	          ((a) & (b))
#define vlonglongOr( a, b )	          ((a) | (b))
#define vlonglongXor( a, b )	          ((a) ^ (b))
#define vlonglongComplement( a )	  (~(a))

#define vlonglongFromInteger( n )	  ((vlonglong)(n))
#define vlonglongToInteger( a )	          ((long)(a))
#define vlonglongFromUnsignedInteger( n ) ((vlonglong)(n))
#define vlonglongToUnsignedInteger( a )	  ((unsigned long)(a))
#define vlonglongFromFloat( x )	          ((vlonglong)(x))
#define vlonglongToFloat( a )	          ((double)(a))
#define vlonglongUnsignedFromFloat( x )   ((vlonglong)(x))
#define vlonglongUnsignedToFloat( a )     ((double)(a))

#else

/*
 * ASSUMPTION : long is 4 bytes
 * so create an 8 byte struct from 2 longs
 */

#define vlonglongGetHigh( vll )		   ((vll).high)
#define vlonglongGetLow( vll )		   ((vll).low)
#define vlonglongMake( h, l )             _vlonglongMake( h, l )
#define vlonglongConstructLiteral( h, l )  {(l), (h)}

#define vlonglongGreaterThan( a, b )	   ((a).high > (b).high ||	     \
					    ((a).high == (b).high &&         \
					     (a).low > (b).low))
#define vlonglongLessThan( a, b )	   ((a).high < (b).high ||	     \
					    ((a).high == (b).high &&         \
					     (a).low < (b).low))
#define vlonglongEqualTo( a, b )	   ((a).high == (b).high &&	     \
					    (a).low  == (b).low)
#define vlonglongIsZero( a )               ((a).high == 0 && (a).low == 0)

#define vlonglongGreaterThanUnsigned( a, b ) \
    ((unsigned long) (a).high > (unsigned long) (b).high ||	     \
     ( (a).high == (b).high && (a).low > (b).low))
#define vlonglongLessThanUnsigned( a, b ) \
    ((unsigned long) (a).high < (unsigned long) (b).high ||	     \
     ( (a).high == (b).high && (a).low < (b).low))

#define vlonglongAdd( a, b )              _vlonglongAdd( a, b )
#define vlonglongSubtract( a, b )	  _vlonglongSubtract( a, b )
#define vlonglongMultiply( a, b )	  _vlonglongMultiply( a, b )
#define vlonglongDivide( a, b )	          _vlonglongDivide( a, b )
#define vlonglongRemainder( a, b )	  _vlonglongRemainder( a, b )
#define vlonglongDivideRemainder( a, b, q, r ) \
    _vlonglongDivideRemainder( a, b, q, r )

#define vlonglongNegate( a )	          _vlonglongNegate( a )
#define vlonglongIncrement( a )	          _vlonglongIncrement( a )
#define vlonglongDecrement( a )	          _vlonglongDecrement( a )

#define vlonglongShiftLeft( a, n )	  _vlonglongShiftLeft( a, n )
#define vlonglongShiftRight( a, n )       _vlonglongShiftRight( a, n )
#define vlonglongShiftRightArithmetic( a, n ) \
    _vlonglongShiftRightArithmetic( a, n )

#define vlonglongAnd( a, b )	          _vlonglongAnd( a, b )
#define vlonglongOr( a, b )	          _vlonglongOr( a, b )
#define vlonglongXor( a, b )	          _vlonglongXor( a, b )
#define vlonglongComplement( a )	  _vlonglongComplement( a )

#define vlonglongFromInteger( n )	  _vlonglongFromInteger( n )
#define vlonglongToInteger( a )	          _vlonglongToInteger( a )
#define vlonglongFromUnsignedInteger( n ) _vlonglongFromUnsignedInteger( n )
#define vlonglongToUnsignedInteger( a )	  _vlonglongToUnsignedInteger( a )
#define vlonglongFromFloat( x )	          _vlonglongFromFloat( x )
#define vlonglongToFloat( a )	          _vlonglongToFloat( a )
#define vlonglongUnsignedFromFloat( x )	  _vlonglongUnsignedFromFloat( x )
#define vlonglongUnsignedToFloat( a )	  _vlonglongUnsignedToFloat( a )

#endif /* #if vlonglongSCALAR */

#define vlonglongCompare( a, b ) \
    (vlonglongGreaterThan( a, b ) ? 1 : \
     (vlonglongLessThan( a, b ) ? -1 : 0))
#define vlonglongCompareUnsigned( a, b ) \
    (vlonglongGreaterThanUnsigned( a, b ) ? 1 : \
     (vlonglongLessThanUnsigned( a, b ) ? -1 : 0))


vportEND_CPLUSPLUS_EXTERN_C


#endif /* #ifndef vlonglongINCLUDED */


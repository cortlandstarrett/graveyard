/* $Id: vnum.h,v 1.38 1997/06/19 00:14:03 robert Exp $ */

/************************************************************

    vnum.h
    Visix internationalized number formatting and parsing routines

    (c) Copyright Visix Software Inc.
    All rights reserved

************************************************************/

#ifndef vnumINCLUDED
#define vnumINCLUDED 1

#ifndef  vportINCLUDED		/* for v*HEADER */
#include <vport.h>
#endif

#ifndef  vstrINCLUDED
#include vstrHEADER
#endif

#ifndef  vregexpINCLUDED
#include vregexpHEADER
#endif

#ifndef  vresourceINCLUDED
#include vresourceHEADER
#endif

#ifndef  vloadableINCLUDED
#include vloadableHEADER
#endif

#ifndef  vlonglongINCLUDED
#include vlonglongHEADER
#endif


vportBEGIN_CPLUSPLUS_EXTERN_C


/*
 * * * * * * * * * * * * * Types * * * * * * * * * * * * * *
 */

typedef struct vnumDigitSet		vnumDigitSet;
typedef struct vnumFormat		vnumFormat;
typedef struct vnumFormatIterator       vnumFormatIterator;


vportALIAS(vnum, void)

/*
 * * * * * * * * * * * * * Constants * * * * * * * * * * * * * *
 */

enum
{
  vnumFORMAT_TEXT,
  vnumFORMAT_NEGATIVE_TEXT,
  vnumFORMAT_POSITIVE_TEXT,
  vnumFORMAT_PADDING,
  vnumFORMAT_WHITE_SPACE,
  vnumFORMAT_EXPONENT,
  vnumFORMAT_DIGITS,
  vnumFORMAT_DECIMAL
};

/*
 * Exceptions:
 */

typedef struct vnumSyntaxException
{
  vexException	parent;
  vchar		*position;
} vnumSyntaxException;

typedef struct vnumRangeException
{
  vexException	parent;
} vnumRangeException;

/*
 * * * * * * * * * * * * * Function Prototypes * * * * * * * * * * * * * *
 */

void vnumStartup(void);

/*
 * Number ==> string:
 */

vscribe 	*vnumScribeInt(int number);
vscribe 	*vnumScribeUInt(unsigned int number);
vscribe		*vnumScribeLong(long number);
vscribe		*vnumScribeULong(unsigned long number);
vscribe		*vnumScribeLongLong(vlonglong number);
vscribe		*vnumScribeFloat(double number);

vscribe 	*vnumScribeIntFormatted(int number, 
					vnumDigitSet *digits,
					vnumFormat *numberFormat,
					vnumFormat *expFormat, 
					int approximateOk,
					int precision);
vscribe 	*vnumScribeUIntFormatted(unsigned int number, 
					vnumDigitSet *digits,
					vnumFormat *numberFormat,
					vnumFormat *expFormat, 
					int approximateOk,
					int precision);
vscribe 	*vnumScribeLongFormatted(long number, 
					 vnumDigitSet *digits,
					 vnumFormat *numberFormat,
					 vnumFormat *expFormat, 
					 int approximateOk,
					 int precision);
vscribe 	*vnumScribeULongFormatted(unsigned long number, 
					  vnumDigitSet *digits,
					  vnumFormat *numberFormat,
					  vnumFormat *expFormat, 
					  int approximateOk,
					  int precision);
vscribe 	*vnumScribeLongLongFormatted(vlonglong number, 
					 vnumDigitSet *digits,
					 vnumFormat *numberFormat,
					 vnumFormat *expFormat, 
					 int approximateOk,
					 int precision);
vscribe 	*vnumScribeFloatFormatted(double number, 
					  vnumDigitSet *digits,
					  vnumFormat *numberFormat,
					  vnumFormat *expFormat, 
					  int approximateOk,
					  int precision);

vscribe		*vnumScribeGeneral(vbyte *digits, int digitCount, 
				   int exponent, int /*vbool*/ negative,
				   vnumDigitSet *digitSet, 
				   vnumFormat *numberFormat,
				   vnumFormat *exponentFormat,
				   int approximateOk);

size_t		vnumGetScribeDigitsBefore(vscribe *scribe);
void		vnumSetScribeDigitsBefore(vscribe *scribe, size_t digits);

size_t		vnumGetScribeDigitsAfter(vscribe *scribe);
void		vnumSetScribeDigitsAfter(vscribe *scribe, size_t digits);

void		vnumSetScribeTruncateZeroes(vscribe *scribe, 
					    int /* vbool */ value);
vbool		vnumGetScribeTruncateZeroes(vscribe *scribe);


/*
 * String ==> number
 */

int		vnumParseInt(const vchar *source, vchar **end);
unsigned int	vnumParseUInt(const vchar *source, vchar **end);
long		vnumParseLong(const vchar *source, vchar **end);
unsigned long	vnumParseULong(const vchar *source, vchar **end);
vlonglong	vnumParseLongLong(const vchar *source, vchar **end);
double		vnumParseFloat(const vchar *source, vchar **end);

int		vnumSizedParseInt(const vchar *source, size_t sourceLength,
				  vchar **end);
unsigned int	vnumSizedParseUInt(const vchar *source, size_t sourceLength,
				   vchar **end);
long		vnumSizedParseLong(const vchar *source, size_t sourceLength,
				   vchar **end);
unsigned long	vnumSizedParseULong(const vchar *source, size_t sourceLength,
				    vchar **end);
vlonglong	vnumSizedParseLongLong(const vchar *source, 
				       size_t sourceLength, vchar **end);
double		vnumSizedParseFloat(const vchar *source, size_t sourceLength,
				    vchar **end);

int		vnumParseIntFormatted(const vchar *source, 
				      vchar **end, 
				      vnumDigitSet *digits,
				      vnumFormat *numberFormat, 
				      vnumFormat *expFormat,
				      int approximateOk);
unsigned int	vnumParseUIntFormatted(const vchar *source, 
				       vchar **end, 
				       vnumDigitSet *digits,
				       vnumFormat *numberFormat, 
				       vnumFormat *expFormat,
				       int approximateOk);
long		vnumParseLongFormatted(const vchar *source, 
				       vchar **end,
				       vnumDigitSet *digits,
				       vnumFormat *numberFormat, 
				       vnumFormat *expFormat,
				       int approximateOk);
unsigned long	vnumParseULongFormatted(const vchar *source, 
					vchar **end,
					vnumDigitSet *digits,
					vnumFormat *numberFormat, 
					vnumFormat *expFormat,
					int approximateOk);
vlonglong	vnumParseLongLongFormatted(const vchar *source, 
				       vchar **end,
				       vnumDigitSet *digits,
				       vnumFormat *numberFormat, 
				       vnumFormat *expFormat,
				       int approximateOk);
double		vnumParseFloatFormatted(const vchar *source, 
					vchar **end,
					vnumDigitSet *digits,
					vnumFormat *numberFormat, 
					vnumFormat *expFormat,
					int approximateOk);

int		vnumSizedParseIntFormatted(const vchar *source, 
					   size_t sourceLength,
					   vchar **end,
					   vnumDigitSet *digits,
					   vnumFormat *numberFormat, 
					   vnumFormat *expFormat,
					   int approximateOk);
unsigned int	vnumSizedParseUIntFormatted(const vchar *source,
					    size_t sourceLength,
					    vchar **end,
					    vnumDigitSet *digits,
					    vnumFormat *numberFormat, 
					    vnumFormat *expFormat,
					    int approximateOk);
long		vnumSizedParseLongFormatted(const vchar *source,
					    size_t sourceLength,
					    vchar **end,
					    vnumDigitSet *digits,
					    vnumFormat *numberFormat, 
					    vnumFormat *expFormat,
					    int approximateOk);
unsigned long	vnumSizedParseULongFormatted(const vchar *source,
					     size_t sourceLength, 
					     vchar **end,
					     vnumDigitSet *digits,
					     vnumFormat *numberFormat, 
					     vnumFormat *expFormat,
					     int approximateOk);
vlonglong	vnumSizedParseLongLongFormatted(const vchar *source,
					    size_t sourceLength,
					    vchar **end,
					    vnumDigitSet *digits,
					    vnumFormat *numberFormat, 
					    vnumFormat *expFormat,
					    int approximateOk);
double		vnumSizedParseFloatFormatted(const vchar *source,
					     size_t sourceLength,
					     vchar **end,
					     vnumDigitSet *digits,
					     vnumFormat *numberFormat, 
					     vnumFormat *expFormat,
					     int approximateOk);

void		vnumParseGeneral(const vchar *source, vchar **end, 
				 vnumDigitSet *digitSet, 
				 vnumFormat *numberFormat, 
				 vnumFormat *expFormat,
				 vbyte *digits, int *digitSize, int *exponent,
				 vbool *negative, vbool *overflow);
void		vnumSizedParseGeneral(const vchar *source,
				      size_t sourceLength, 
				      vchar **end,
				      vnumDigitSet *digitSet, 
				      vnumFormat *numberFormat,
				      vnumFormat *expFormat,
				      vbyte *digits, int *digitSize,
				      int *exponent,
				      vbool *negative, vbool *overflow);

/*
 * Predefined (internationalized) formats & types:
 */

vnumDigitSet	*vnumGetDecimalDigitSet(void);
vnumDigitSet 	*vnumGetBinaryDigitSet(void);
vnumDigitSet	*vnumGetOctalDigitSet(void);
vnumDigitSet 	*vnumGetHexDigitSet(void);

vnumFormat	*vnumGetNormalFormat(void);
vnumFormat	*vnumGetExponentFormat(void);
vnumFormat	*vnumGetMoneyFormat(void);

/*
 * Digits:
 */

vnumDigitSet	*vnumCreateDigitSet(vchar *digits);
vnumDigitSet	*vnumCreateDigitSetScribed(vscribe *digits);
vnumDigitSet    *vnumCloneDigitSet(const vnumDigitSet *digits);
vnumDigitSet 	*vnumLoadDigitSet(vresource r);
void 		vnumStoreDigitSet(vnumDigitSet *ds, vresource r); 
void		vnumDestroyDigitSet(vnumDigitSet *digits);
int		vnumGetDigitSetBase(const vnumDigitSet *digits);
vchar		vnumGetDigitSetDigit(const vnumDigitSet *digits, int number);
const vchar	*vnumGetDigitSetDigits(const vnumDigitSet *digits);
int		vnumMatchDigitSet(vnumDigitSet *digits, vchar digit);

/*
 * Custom formats:
 */

vnumFormat	*vnumCreateFormat(void);
void             vnumInitFormat (vnumFormat *f);
vnumFormat	*vnumCloneFormat(const vnumFormat *f);
vnumFormat 	*vnumLoadFormat(vresource r);
void            vnumCopyInitFormat(vnumFormat *src, vnumFormat *dest);
void            vnumCopyFormat(vnumFormat *src, vnumFormat *dest);
void 		vnumStoreFormat(vnumFormat *f, vresource r);
void		vnumDestroyFormat(vnumFormat *f);

int		vnumGetFormatComponentCount(vnumFormat *f);

void 		vnumInsertFormatText(vnumFormat *f, int index,
				     const vchar *show, vregexp *match);
void 		vnumInsertFormatTextScribed(vnumFormat *f, int index,
					    vscribe *show, vregexp *match);
void 		vnumInsertFormatNegText(vnumFormat *f, int index,
					const vchar  *show, vregexp *match);
void 		vnumInsertFormatNegTextScribed(vnumFormat *f, int index,
					    vscribe *show, vregexp *match);
void 		vnumInsertFormatPosText(vnumFormat *f, int index,
				     const vchar *show, vregexp *match);
void 		vnumInsertFormatPosTextScribed(vnumFormat *f, int index,
					    vscribe *show, vregexp *match);
void 		vnumInsertFormatPadding(vnumFormat *f, int index,
					int /*vchar*/ character,
					int repetition);
void		vnumInsertFormatWhiteSpace(vnumFormat *f, int index,
					   int /*vbool*/ required,
					   int /*vbool*/ shown);
void		vnumInsertFormatDigits(vnumFormat *f, int index,
				       int groupingCount,
				       int /* vchar */ groupingCharacter,
				       int fixedCount);
void		vnumInsertFormatDecimal(vnumFormat *f, int index,
					int /* vchar */ decimalPoint);
void		vnumInsertFormatExponent(vnumFormat *f, int index);

vbool		vnumRemoveFormatComponentAt(vnumFormat *f, int index);

int		vnumGetFormatTypeAt(vnumFormat *f, int index);
const vchar	*vnumGetFormatTextShowAt(vnumFormat *f, int index);
const vregexp	*vnumGetFormatTextMatchAt(vnumFormat *f, int index);
vchar		vnumGetFormatPaddingCharacterAt(vnumFormat *f, int index);
int		vnumGetFormatPaddingRepetitionAt(vnumFormat *f, int index);
int		vnumGetFormatDigitsGroupingCountAt(vnumFormat *f, int index);
vchar		vnumGetFormatDigitsGroupingCharacterAt(vnumFormat *f,
						       int index);
int		vnumGetFormatDigitsCountAt(vnumFormat *f, int index);
vchar		vnumGetFormatDecimalPointAt(vnumFormat *f, int index);
vbool		vnumIsFormatWhiteSpaceRequiredAt(vnumFormat *f, int index);
vbool		vnumIsFormatWhiteSpaceShownAt(vnumFormat *f, int index);

/*
 * Number format iterator
 */

void		vnumInitFormatIterator(vnumFormatIterator *i,
				       vnumFormat *format); 
vbool		vnumNextFormatIterator(vnumFormatIterator *i);
void		vnumDestroyFormatIterator(vnumFormatIterator *i);


int		vnumGetFormatIteratorIndex(const vnumFormatIterator *i);
int		vnumGetFormatIteratorType(const vnumFormatIterator *i);
const vchar	*vnumGetFormatIteratorTextShow(const vnumFormatIterator *i);
const vregexp	*vnumGetFormatIteratorTextMatch(const vnumFormatIterator *i);
vchar		vnumGetFormatIteratorPaddingCharacter(const 
						      vnumFormatIterator *i);
int		vnumGetFormatIteratorPaddingRepetition(const 
						       vnumFormatIterator *i);
int		vnumGetFormatIteratorDigitsGroupingCount(const 
						 vnumFormatIterator *i);
vchar		vnumGetFormatIteratorDigitsGroupingCharacter(const 
						     vnumFormatIterator *i);
int		vnumGetFormatIteratorDigitsCount(const vnumFormatIterator *i);
vchar		vnumGetFormatIteratorDecimalPoint(const vnumFormatIterator *i);
vbool		vnumIsFormatIteratorWhiteSpaceRequired(const 
							vnumFormatIterator *i);
vbool		vnumIsFormatIteratorWhiteSpaceShown(const 
						     vnumFormatIterator *i);


/*
 * Exceptions:
 */

vnumSyntaxException *vnumGetSyntaxException(void);
const vexClass *vnumGetSyntaxExceptionClass(void);
vchar *vnumGetSyntaxExceptionPosition(vnumSyntaxException *e);

vnumRangeException *vnumGetRangeException(void);
const vexClass *vnumGetRangeExceptionClass(void);


/*
 * deprecated
 */

void 		vnumAddFormatText(vnumFormat *f, vnumFormatIterator *before,
				  const vchar *show, vregexp *match);
void 		vnumAddFormatTextScribed(vnumFormat *f, 
					 vnumFormatIterator *before,
					 vscribe *show, vregexp *match);
void 		vnumAddFormatNegText(vnumFormat *f, vnumFormatIterator *before,
				     const vchar  *show, vregexp *match);
void 		vnumAddFormatNegTextScribed(vnumFormat *f, 
					    vnumFormatIterator *before,
					    vscribe *show, vregexp *match);
void 		vnumAddFormatPosText(vnumFormat *f, vnumFormatIterator *before,
				     const vchar *show, vregexp *match);
void 		vnumAddFormatPosTextScribed(vnumFormat *f,
					    vnumFormatIterator *before,
					    vscribe *show, vregexp *match);
void 		vnumAddFormatPadding(vnumFormat *f, vnumFormatIterator *before,
				     int /*vchar*/ character, int repetition);
void		vnumAddFormatWhiteSpace(vnumFormat *f, 
					vnumFormatIterator *before,
					int /*vbool*/ required,
					int /*vbool*/ shown);
void		vnumAddFormatDigits(vnumFormat *f, vnumFormatIterator *before, 
				    int groupingCount,
				    int /* vchar */ groupingCharacter,
				    int count);
void		vnumAddFormatDecimal(vnumFormat *f, vnumFormatIterator *before,
				     int /* vchar */ decimalPoint);
void		vnumAddFormatExponent(vnumFormat *f,
				      vnumFormatIterator *before);

vbool		vnumRemoveFormatComponent(vnumFormat *f,
					  vnumFormatIterator *i);


/*
 * * * * * * * * * * * Privately Exported Types * * * * * * * * * * * * *
 */

struct vnumDigitSet
{
  int 		 base;
  vstr 		*digits;
  vbool          contiguousDigits;
};

typedef struct _vnumFormatComponent
{
  short type;
  union 
    {
      struct 
	{
	  vstr 		*print;
	  vregexp	*match;
	} string;
      struct
	{
	  int 		repetition;
	  vchar		character;
	} padding;
      struct
	{
	  short		fixedCount;
	  short		groupingCount;
	  vchar		groupingCharacter;
	} digits;
      struct 
	{
	  vchar		decimalPoint;
	} decimal;
      struct 
	{
	  vbool		required;
	  vbool		shown;
	} whiteSpace;
    } u;
} _vnumFormatComponent;

struct vnumFormat
{
  vloadable		object;
  _vnumFormatComponent	*components;	/* varray */
  short			decimalIndex;
  short			hasFixedDigitsAfterDecimal;
  vbool			checked;
  unsigned              flags;
};

#define vnumFormatCLASS(SUPER, OBJECT)				      \
    vloadableCLASS(SUPER, OBJECT)

typedef struct vnumFormatClass	vnumFormatClass;

struct vnumFormatClass {
    vnumFormatCLASS(vnumFormatClass, vnumFormat);
};


struct vnumFormatIterator
{
  vnumFormat		*format;
  int			 index;
};

/*
 * * * * * * * * * * * * Privately Exported Constants * * * * * * * * * * * *
 */

enum
{
  _vnumPOOL_FORMAT      = 0x01,
  _vnumOPTIMIZE_PARSE   = 0x02
};

#define _vnumUNSIZED            vportINT_MAX

/*
 * * * * * * * * * * * * Privately Exported Variables * * * * * * * * * * * *
 */

extern vportLINK const vexClass _vnumSyntaxExceptionClass;
extern vportLINK const vexClass _vnumRangeExceptionClass;

/*
 * * * * * * * * * * * Privately Exported Prototypes * * * * * * * * * * * * *
 */

vnumFormatClass *_vnumGetDefaultFormatClass(void);

vnumFormatClass *_vnumGetFormatClass(
    vnumFormat			   *format
    );

vloadable *_vnumGetFormatObject(
    vnumFormat			   *format
    );

vnumFormat *_vnumCreateFormatOfClass(
    vnumFormatClass                   *clas
    );

void _vnumInitFormatOfClass(
    vnumFormat                        *format,
    vnumFormatClass                   *clas
    );

/*
 * * * * * * * * * * * * * * * Function MACROs * * * * * * * * * * * * * * *
 */


#define vnumCreateDigitSet(d)	\
    vnumCreateDigitSetScribed(vcharScribe(d))

#define vnumGetDigitSetBase(d) 		((d)->base)
#define vnumGetDigitSetDigit(d,i)	((d)->digits[(i)])
#define vnumGetDigitSetDigits(d)	((d)->digits)

#define _vnumGetFormatObject(s) \
    (vportBASE_OBJECT(s, object))

#define _vnumGetFormatClass(s) \
    ((vnumFormatClass*)vloadableGetClass(_vnumGetFormatObject(s)))

#define _vnumCreateFormatOfClass(c) \
    ((vnumFormat*)vloadableCreateOfClass((vloadableClass*)(c)))

#define _vnumInitFormatOfClass(s, c) \
    vloadableInitOfClass(_vnumGetFormatObject(s), (vloadableClass*)(c))

#define vnumCreateFormat() \
    (_vnumCreateFormatOfClass(_vnumGetDefaultFormatClass()))

#define vnumInitFormat(s) \
    (_vnumInitFormatOfClass(s, _vnumGetDefaultFormatClass()))

#define vnumCopyInitFormat(s, d) \
    vloadableCopyInit (_vnumGetFormatObject(s), _vnumGetFormatObject(d))

#define vnumCopyFormat(s, d) \
    vloadableCopy (_vnumGetFormatObject(s), _vnumGetFormatObject(d))

#define vnumDestroyFormat(s) \
    vloadableDestroy(_vnumGetFormatObject(s))

#define vnumCloneFormat(s) \
    ((vnumFormat*)vloadableClone(_vnumGetFormatObject(s)))

#define vnumStoreFormat(s, r) \
    vclassSend(_vnumGetFormatClass(s), vloadableSTORE, (s, r))

#define vnumGetFormatTypeAt(f, i) \
    ((f)->components[i].type)
#define vnumGetFormatPaddingRepetitionAt(f, i) \
    ((f)->components[i].u.padding.repetition)
#define vnumGetFormatPaddingCharacterAt(f, i) \
    ((f)->components[i].u.padding.character)
#define vnumGetFormatDigitsCountAt(f, i) \
    ((f)->components[i].u.digits.fixedCount)
#define vnumGetFormatDigitsGroupingCountAt(f, i) \
    ((f)->components[i].u.digits.groupingCount)
#define vnumGetFormatDigitsGroupingCharacterAt(f, i) \
    ((f)->components[i].u.digits.groupingCharacter)
#define vnumGetFormatDecimalPointAt(f, i) \
    ((f)->components[i].u.decimal.decimalPoint)
#define vnumIsFormatWhiteSpaceRequiredAt(f, i) \
    ((f)->components[i].u.whiteSpace.required)
#define vnumIsFormatWhiteSpaceShownAt(f, i) \
    ((f)->components[i].u.whiteSpace.shown)

#define vnumInsertFormatText(f,i,s,m) \
    vnumInsertFormatTextScribed((f),(i),vcharScribe(s),(m))
#define vnumInsertFormatNegText(f,i,s,m) \
    vnumInsertFormatNegTextScribed((f),(i),vcharScribe(s),(m))
#define vnumInsertFormatPosText(f,i,s,m) \
    vnumInsertFormatPosTextScribed((f),(i),vcharScribe(s),(m))

#define vnumDestroyFormatIterator(i)	

#define vnumGetFormatIteratorIndex(i) \
    ((i)->index)
#define vnumGetFormatIteratorType(i) \
    vnumGetFormatTypeAt((i)->format, (i)->index)
#define vnumGetFormatIteratorTextShow(i) \
    vnumGetFormatTextShowAt((i)->format, (i)->index)
#define vnumGetFormatIteratorTextMatch(i) \
    vnumGetFormatTextMatchAt((i)->format, (i)->index)
#define vnumGetFormatIteratorPaddingRepetition(i) \
    vnumGetFormatPaddingRepetitionAt((i)->format, (i)->index)
#define vnumGetFormatIteratorPaddingCharacter(i) \
    vnumGetFormatPaddingCharacterAt((i)->format, (i)->index)
#define vnumGetFormatIteratorDigitsCount(i) \
    vnumGetFormatDigitsCountAt((i)->format, (i)->index)
#define vnumGetFormatIteratorDigitsGroupingCount(i) \
    vnumGetFormatDigitsGroupingCountAt((i)->format, (i)->index)
#define vnumGetFormatIteratorDigitsGroupingCharacter(i) \
    vnumGetFormatDigitsGroupingCharacterAt((i)->format, (i)->index)
#define vnumGetFormatIteratorDecimalPoint(i) \
    vnumGetFormatDecimalPointAt((i)->format, (i)->index)
#define vnumIsFormatIteratorWhiteSpaceRequired(i) \
    vnumIsFormatWhiteSpaceRequiredAt((i)->format, (i)->index)
#define vnumIsFormatIteratorWhiteSpaceShown(i) \
    vnumIsFormatWhiteSpaceShownAt((i)->format, (i)->index)

#define _vnumIteratorToIndex(b) \
	((b) != NULL ? ((vnumFormatIterator *)(b))->index : -1)
#define vnumAddFormatTextScribed(f, b, s, m) \
    vnumInsertFormatTextScribed(f, _vnumIteratorToIndex(b), s, m)
#define vnumAddFormatNegTextScribed(f, b, s, m) \
    vnumInsertFormatNegTextScribed(f, _vnumIteratorToIndex(b), s, m)
#define vnumAddFormatPosTextScribed(f, b, s, m) \
    vnumInsertFormatPosTextScribed(f, _vnumIteratorToIndex(b), s, m)
#define vnumAddFormatText(f,i,s,m) \
    vnumAddFormatTextScribed((f),(i),vcharScribe(s),(m))
#define vnumAddFormatNegText(f,i,s,m) \
    vnumAddFormatNegTextScribed((f),(i),vcharScribe(s),(m))
#define vnumAddFormatPosText(f,i,s,m) \
    vnumAddFormatPosTextScribed((f),(i),vcharScribe(s),(m))
#define vnumAddFormatPadding(f, b, c, r) \
    vnumInsertFormatPadding(f, _vnumIteratorToIndex(b), c, r)
#define vnumAddFormatWhiteSpace(f, b, r, s) \
    vnumInsertFormatWhiteSpace(f, _vnumIteratorToIndex(b), r, s)
#define vnumAddFormatExponent(f, b) \
    vnumInsertFormatExponent(f, _vnumIteratorToIndex(b))
#define vnumAddFormatDigits(f, b, g, c, x) \
    vnumInsertFormatDigits(f, _vnumIteratorToIndex(b), g, c, x)
#define vnumAddFormatDecimal(f, b, d) \
    vnumInsertFormatDecimal(f, _vnumIteratorToIndex(b), d)

#define vnumRemoveFormatComponent(f, i) \
    vnumRemoveFormatComponentAt(f, (i) != NULL ? (i)->index : -1)

#define vnumParseGeneral(s,e,ds,nf,ef,db,dsize,exp,neg,ovf) \
   vnumSizedParseGeneral (s, _vnumUNSIZED, e, ds, nf, ef, db, dsize, exp, neg, ovf)
#define vnumParseLongFormatted(s,e,d,nf,ef,a) \
   vnumSizedParseLongFormatted (s, _vnumUNSIZED, e, d, nf, ef, a)
#define vnumParseLong(s,e) \
   vnumSizedParseLong (s, _vnumUNSIZED, e)
#define vnumParseIntFormatted(s,e,d,nf,ef,a) \
   vnumSizedParseIntFormatted (s, _vnumUNSIZED, e, d, nf, ef, a)
#define vnumParseInt(s,e) \
   vnumSizedParseInt (s, _vnumUNSIZED, e)
#define vnumParseUInt(s,e) \
   vnumSizedParseUInt (s, _vnumUNSIZED, e)
#define vnumParseUIntFormatted(s,e,d,nf,ef,a) \
   vnumSizedParseUIntFormatted (s, _vnumUNSIZED, e, d, nf, ef, a)
#define vnumParseULong(s,e) \
   vnumSizedParseULong (s, _vnumUNSIZED, e)
#define vnumParseULongFormatted(s,e,d,nf,ef,a) \
   vnumSizedParseULongFormatted (s, _vnumUNSIZED, e, d, nf, ef, a)
#define vnumParseLongLongFormatted(s,e,d,nf,ef,a) \
   vnumSizedParseLongLongFormatted (s, _vnumUNSIZED, e, d, nf, ef, a)
#define vnumParseFloatFormatted(s,e,d,nf,ef,a) \
   vnumSizedParseFloatFormatted (s, _vnumUNSIZED, e, d, nf, ef, a)
#define vnumParseFloat(s,e) \
   vnumSizedParseFloat (s, _vnumUNSIZED, e)

#define vnumSizedParseLongLong(s,l,e) \
    vnumSizedParseLongLongFormatted(s,l,e, vnumGetDecimalDigitSet(), \
				    vnumGetNormalFormat(), \
				    vnumGetExponentFormat(), FALSE);
#define vnumParseLongLong(s,e) \
   vnumSizedParseLongLong (s, _vnumUNSIZED, e)

#define vnumScribeIntFormatted(n,t,nf,ef,a,ro) \
    vnumScribeLongFormatted((long)(n),(t),(nf),(ef),(a),(ro))

#define vnumScribeUIntFormatted(n,t,nf,ef,a,ro) \
    vnumScribeULongFormatted((unsigned long)(n),(t),(nf),(ef),(a),(ro))

#define vnumScribeInt(n) \
    vnumScribeIntFormatted((n), vnumGetDecimalDigitSet(), \
			   vnumGetNormalFormat(), NULL, FALSE, -1)

#define vnumScribeUInt(n) \
    vnumScribeUIntFormatted((n), vnumGetDecimalDigitSet(), \
			   vnumGetNormalFormat(), NULL, FALSE, -1)

#define vnumScribeLong(n) \
    vnumScribeLongFormatted((n), vnumGetDecimalDigitSet(), \
			    vnumGetNormalFormat(), NULL, FALSE, -1)

#define vnumScribeULong(n) \
    vnumScribeULongFormatted((n), vnumGetDecimalDigitSet(), \
			    vnumGetNormalFormat(), NULL, FALSE, -1)

#define vnumScribeLongLong(n) \
    vnumScribeLongLongFormatted((n), vnumGetDecimalDigitSet(), \
				vnumGetNormalFormat(), NULL, FALSE, -1)


/*
 * Exceptions:
 */

#define vnumGetSyntaxException() \
    ((vnumSyntaxException *)  \
     vexGetExceptionOfClass(&_vnumSyntaxExceptionClass))
#define vnumGetSyntaxExceptionClass()		(&_vnumSyntaxExceptionClass)
#define vnumGetSyntaxExceptionPosition(e)  	((e)->position)

#define vnumGetRangeException() \
    ((vnumRangeException *)  \
     vexGetExceptionOfClass(&_vnumRangeExceptionClass))
#define vnumGetRangeExceptionClass()		(&_vnumRangeExceptionClass)


vportEND_CPLUSPLUS_EXTERN_C


#endif /* #ifndef vnumINCLUDED */


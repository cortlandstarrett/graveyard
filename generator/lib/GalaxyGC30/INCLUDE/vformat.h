/* $Id: vformat.h,v 1.34 1997/10/24 23:26:35 robert Exp $ */

/* vformat.h
 *
 * Copyright (C) 1996 Visix Software.  All Rights Reserved
 *
 */

#ifndef vformatINCLUDED
#define vformatINCLUDED 1

#ifndef vportINCLUDED
#include <vport.h>
#endif

#ifndef vstdINCLUDED
#include vstdHEADER
#endif

#ifndef vclassINCLUDED
#include vclassHEADER
#endif

#ifndef vinstanceINCLUDED
#include vinstanceHEADER
#endif

#ifndef vresourceINCLUDED
#include vresourceHEADER
#endif

#ifndef vnumINCLUDED
#include vnumHEADER
#endif

#ifndef vdateINCLUDED
#include vdateHEADER
#endif

#ifndef vcolorINCLUDED
#include vcolorHEADER
#endif

#ifndef vlistINCLUDED
#include vlistHEADER
#endif

#ifndef viteratorINCLUDED
#include viteratorHEADER
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * * * * * * * * * * PUBLIC CONSTANT DEFINITIONS * * * * * * * * * *
 */

/*
 * * FORMAT ALIGNMENT CODES
 */
enum
{
    vformatALIGN_LEFT,
    vformatALIGN_RIGHT,
    vformatALIGN_CENTER
};

/*
 * * FORMAT VALIDITY CODES
 */
enum
{
    vformatVALID,
    vformatPARTIALLY_VALID,
    vformatINVALID
};

/*
 * * * * * * * * * * PUBLIC TYPE DEFINITIONS * * * * * * * * * *
 */

typedef struct vformat
               vformat;

typedef struct vformatClass
               vformatClass;

typedef struct vformatSegment
               vformatSegment;

typedef struct vformatSegmentClass
               vformatSegmentClass;

typedef struct vformatParseRange
               vformatParseRange;

typedef struct vformatParseRangeClass
               vformatParseRangeClass;

typedef        int
               vformatPatternIndex;

typedef        int
               vformatSegmentIndex;

typedef struct vformatSegmentIterator
               vformatSegmentIterator;

typedef struct vformatParseException
               vformatParseException;

typedef struct vformatNumber
               vformatNumber;

typedef struct vformatNumberClass
               vformatNumberClass;

typedef struct vformatNumberSegment
               vformatNumberSegment;

typedef struct vformatNumberSegmentClass
               vformatNumberSegmentClass;

typedef struct vformatBoolean
               vformatBoolean;

typedef struct vformatBooleanClass
               vformatBooleanClass;

typedef struct vformatBooleanSegment
               vformatBooleanSegment;

typedef struct vformatBooleanSegmentClass
               vformatBooleanSegmentClass;

typedef struct vformatDouble
               vformatDouble;

typedef struct vformatDoubleClass
               vformatDoubleClass;

typedef struct vformatDoubleSegment
               vformatDoubleSegment;

typedef struct vformatDoubleSegmentClass
               vformatDoubleSegmentClass;

typedef struct vformatLong
               vformatLong;

typedef struct vformatLongClass
               vformatLongClass;

typedef struct vformatLongSegmentClass
               vformatLongSegmentClass;

typedef struct vformatLongSegment
               vformatLongSegment;

typedef struct vformatULong
               vformatULong;

typedef struct vformatULongClass
               vformatULongClass;

typedef struct vformatULongSegment
               vformatULongSegment;

typedef struct vformatULongSegmentClass
               vformatULongSegmentClass;

typedef struct vformatDate
               vformatDate;

typedef struct vformatDateClass
               vformatDateClass;

typedef struct vformatDateSegment
               vformatDateSegment;

typedef struct vformatDateSegmentClass
               vformatDateSegmentClass;

/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */

/*
 * * FORMAT PARSE EXCEPTION INTERFACE
 */

vformatParseException *
vformatGetParseException (
    void
);

int
vformatGetParseExceptionOffset (
    vformatParseException *exception
);

int
vformatGetParseExceptionCode (
    vformatParseException *exception
);

void
vformatOFFSET (
    void    *exception,
    va_list *ap
);

void
vformatREMAINDER (
    void    *exception,
    va_list *ap
);

void
vformatERROR_CODE (
    void    *exception,
    va_list *ap
);

const vexClass *
vformatGetParseExceptionClass (
    void
);


/*
 * * FORMAT INTERFACE
 */

void 
vformatStartup (
    void
);

vformatClass *
vformatGetDefaultClass (
    void
);

vformatClass *
vformatGetClass (
    vformat *format
);

vinstance *
vformatGetInstance (
    vformat *format
);

vloadable *
vformatGetLoadable (
    vformat *format
);

vformat *
vformatCreate (
    void
);

vformat *
vformatClone (
    vformat *format
);

void
vformatInit (
    vformat *format
);

void
vformatCopy (
    vformat *dest,
    vformat *src
);

void
vformatCopyInit (
    vformat *dest,
    vformat *src
);

void
vformatDump (
    vformat *format,
    FILE    *stream
);

void
vformatDestroy (
    vformat *format
);

vformat *
vformatCreateOfClass (
    vformatClass *clas
);

void
vformatInitOfClass (
    vformat      *format,
    vformatClass *clas
);

vformat *
vformatLoad (
    vresource res
);

void
vformatLoadPatterns (
    vformat   *format,
    vresource  res
);

void
vformatStore (
    vformat   *format,
    vresource  res
);

int
vformatDetermineValidity (
    vformat     *format,
    const vchar *string
);

vbool
vformatIsValid (
    vformat     *format,
    const vchar *string
    );

vbool
vformatIsPartiallyValid (
    vformat     *format,
    const vchar *string
);

void
vformatSetPatterns (
    vformat      *format,
    const vchar **string, 
    int           count
);

void
vformatInsertPatternScribed (
    vformat *format,
    vscribe *scribe,
    int      index
);

void
vformatInsertPattern (
    vformat     *format,
    const vchar *string,
    int          index
);

void
vformatSetPatternIndex (
    vformat *format,
    int      oldIndex,
    int      newIndex
);

vstr *
vformatGetPatternAt (
    vformat *format,
    int      index
);

void
vformatAppendPattern (
    vformat     *format,
    const vchar *string
);

void
vformatDestroyPatternAt (
    vformat *format,
    int      index
);

int
vformatGetPatternCount (
    const vformat *format
);

int
vformatGetOutputPatternIndex (
    vformat *format
);

void
vformatSetOutputPatternIndex (
    vformat *format,
    int      indx
);

void
vformatSetSharedAlias (
    vformat     *format,
    const vname *aliasTag
);

const vname *
vformatGetSharedAlias (
    vformat *format
);

int
vformatGetSegmentCount (
    vformat *format
);

const vformatSegment *
vformatGetPatternSegmentAt (
    vformat *format,
    int      patternIndex,
    int      segmentIndex
);

/*
 * * FORMAT SEGMENT INTERFACE
 */

vformatSegmentClass *
vformatGetDefaultSegmentClass (
    void
);

vformatSegmentClass *
vformatGetSegmentClass (
    vformatSegment *segment
);

vinstance *
vformatGetSegmentInstance (
    vformatSegment *segment
);

vformatSegment *
vformatCreateSegment (
    void
);

vformatSegment *
vformatCreateSegmentOfClass (
    vformatSegmentClass *clas
);

void
vformatDumpSegment (
    const vformatSegment *segment,
    FILE                 *stream
);

void
vformatDestroySegment (
    vformatSegment *segment
);

void
vformatInitSegment (
    vformatSegment *segment
);

const vchar *
vformatGetSegmentString (
    vformatSegment *segment
);

void
vformatSetSegmentString (
    vformatSegment *segment,
    const vchar    *string
);

vcolor *
vformatGetSegmentColor (
    vformatSegment *segment
);

void
vformatSetSegmentColor (
    vformatSegment *segment,
    vcolor         *color
);

int
vformatGetSegmentAlignment (
    vformatSegment *segment
);

void
vformatSetSegmentAlignment (
    vformatSegment *segment,
    int             alignment
);

void
vformatParseSegment (
    vformatSegment *segment,
    int             segmentIndex
);

void
vformatParseSegmentPattern (
    vformatSegment    *segment,
    vformatParseRange *range
);

/*
 * * FORMAT SEGMENT ITERATOR INTERFACE
 */

void
vformatInitSegmentIterator (
    vformatSegmentIterator *iter,
    const vformat          *format
);

vbool
vformatNextSegmentIterator (
    vformatSegmentIterator *iterator
);

const vformat *
vformatGetSegmentIteratorFormat(
    vformatSegmentIterator *iterator
);

const vformatSegment *
vformatGetSegmentIteratorSegment (
    vformatSegmentIterator *iterator
);

int
vformatGetSegmentIteratorSegmentIndex (
    vformatSegmentIterator *iterator
);

int
vformatGetSegmentIteratorPatternIndex (
    vformatSegmentIterator *iterator
);

void
vformatDestroySegmentIterator (
    vformatSegmentIterator *iterator
);


/*
 * * FORMAT PARSE RANGE INTERFACE
 */

vformatParseRangeClass *
vformatGetDefaultParseRangeClass (
    void
);

vformatParseRangeClass *
vformatGetParseRangeClass (
    vformatParseRange *range
);

vinstance *
vformatGetParseRangeInstance (
    vformatParseRange *range
);

vformatParseRange *
vformatCreateParseRange (
    void
);

vformatParseRange *
vformatCreateParseRangeOfClass (
    vformatParseRangeClass *clas
);

void
vformatDumpParseRange (
    const vformatParseRange *range,
    FILE                    *stream
);

void
vformatDestroyParseRange (
    vformatParseRange *range
);

void
vformatInitParseRange (
    vformatParseRange *range
);

void
vformatSetParseRange (
    vformatParseRange *range,
    int                pos,
    int                len
);

void
vformatGetParseRange (
    vformatParseRange *range,
    int               *pos,
    int               *len
);

void
vformatSetParseRangeStart (
    vformatParseRange *range,
    int                pos
);

int
vformatGetParseRangeStart (
    vformatParseRange *range
);


void
vformatSetParseRangeLength (
    vformatParseRange *range,
    int                len
);

int
vformatGetParseRangeLength (
    vformatParseRange *range
);

void
vformatIncrementParseRangeStart (
    vformatParseRange *range,
    int                len
);

void
vformatDecrementParseRangeLength (
    vformatParseRange *range,
    int                len
);


/*
 * * NUMBER FORMAT INTERFACE
 */

void
vformatStartupNumber (
    void
);

vformatNumberClass *
vformatGetDefaultNumberClass (
    void
);

vformatNumberClass *
vformatGetNumberClass (
    vformatNumber *format
);

vloadable *
vformatGetNumberLoadable (
    vformatNumber *format
);

vformat *
vformatGetNumberBase (
    vformatNumber *format
);

vformatNumber *
vformatCreateNumber (
    void
);

vformatNumber *
vformatCloneNumber (
    vformatNumber *format
);

void
vformatInitNumber (
    vformatNumber *format
);

void
vformatCopyNumber (
    vformatNumber *dest,
    vformatNumber *src
);

void
vformatCopyInitNumber (
    vformatNumber *dest,
    vformatNumber *src
);

void
vformatDumpNumber (
    vformatNumber *format,
    FILE          *stream
);

void
vformatDestroyNumber (
    vformatNumber *format
);

vformatNumber *
vformatLoadNumber (
    vresource res
);

void
vformatLoadNumberPatterns (
    vformatNumber *format,
    vresource      res
);

void
vformatStoreNumber (
    vformatNumber *format,
    vresource       res
);

void
vformatSetNumberOutputPatternIndex (
    vformatNumber  *format,
    int             indx
);

int
vformatGetNumberOutputPatternIndex (
    vformatNumber *format
);

void
vformatSetNumberPatterns (
    vformatNumber   *format,
    const vchar    **strings,
    int              count
);

int
vformatDetermineNumberValidity (
    vformatNumber *format,
    const vchar   *string
);

vbool
vformatIsNumberValid (
    vformatNumber *format,
    const vchar   *string
    );

vbool
vformatIsNumberPartiallyValid (
    vformatNumber *format,
    const vchar   *string
);

void
vformatInsertNumberPatternScribed (
    vformatNumber *format,
    vscribe       *scribe,
    int            index
);

void
vformatInsertNumberPattern (
    vformatNumber *format,
    const vchar   *pattern,
    int            index
);

void
vformatSetNumberPatternIndex (
    vformatNumber *format,
    int            oldIndex,
    int            newIndex
);


void
vformatAppendNumberPattern (
    vformatNumber *format,
    const vchar   *pattern
);

void
vformatDestroyNumberPatternAt (
    vformatNumber *format,
    int            index
);

long
vformatGetNumberPatternCount (
    const vformatNumber *format
);

int
vformatGetNumberSegmentCount (
    vformatNumber *format
);

const vformatNumberSegment *
vformatGetNumberPatternSegmentAt (
    vformatNumber *format,
    int            patternIndex,
    int            segmentIndex
);

vbool
vformatIsNumberStrict (
    const vformatNumber *format
);

void
vformatSetNumberStrict (
    vformatNumber *format,
    vbool          strict
);
/*
 * * NUMBER FORMAT SEGMENT INTERFACE
 */

vformatNumberSegmentClass *
vformatGetDefaultNumberSegmentClass (
    void
);

vinstance *
vformatGetNumberSegmentInstance (
    vformatNumberSegment *segment
);

vformatSegment *
vformatGetNumberSegmentBase (
    vformatNumberSegment *segment
);

vformatNumberSegment *
vformatCreateNumberSegment (
    void
);

vformatNumberSegment *
vformatCreateNumberSegmentOfClass (
    vformatNumberSegmentClass *clas
);

void
vformatDumpNumberSegment (
    const vformatNumberSegment *segment,
    FILE                       *stream
);

void
vformatDestroyNumberSegment (
    vformatNumberSegment *segment
);

void
vformatInitNumberSegment (
    vformatNumberSegment *segment
);

const vchar *
vformatGetNumberSegmentString (
    const vformatNumberSegment *segment
);

void
vformatSetNumberSegmentString (
    vformatNumberSegment *segment,
    const vchar          *string
);

vcolor *
vformatGetNumberSegmentColor (
    const vformatNumberSegment *segment
);

void
vformatSetNumberSegmentColor (
    vformatNumberSegment *segment,
    vcolor               *color
);

int
vformatGetNumberSegmentAlignment (
    const vformatNumberSegment *segment
);

void
vformatSetNumberSegmentAlignment (
    vformatNumberSegment *segment,
    int                   alignment
);

void
vformatSetNumberSegmentPrefix (
    vformatNumberSegment *segment,
    const vchar          *prefix
);

const vchar *
vformatGetNumberSegmentPrefix (
    const vformatNumberSegment *segment
);

void
vformatSetNumberSegmentSuffix (
    vformatNumberSegment *segment,
    const vchar          *suffix
);

const vchar *
vformatGetNumberSegmentSuffix (
    const vformatNumberSegment *segment
);

double
vformatGetNumberSegmentScale (
    const vformatNumberSegment *segment
);

void
vformatSetNumberSegmentScale (
    vformatNumberSegment *segment,
    double                scale
);

void
vformatParseNumberSegment (
    vformatNumberSegment *segment,
    int                   segmentIndex
);

void
vformatParseNumberSegmentPattern (
    vformatNumberSegment *segment,
    vformatParseRange    *range
);


/*
 * * BOOLEAN FORMAT INTERFACE
 */

void
vformatStartupBoolean (
    void
);

vformatBooleanClass *
vformatGetDefaultBooleanClass (
    void
);

vformatBooleanClass *
vformatGetBooleanClass (
    vformatBoolean *format
);

vloadable *
vformatGetBooleanLoadable (
    vformatBoolean *format
);

vformat *
vformatGetBooleanBase (
    vformatBoolean *format
);

vformatBoolean *
vformatCreateBoolean (
    void
);

vformatBoolean *
vformatCloneBoolean (
    vformatBoolean *format
);

void
vformatInitBoolean (
    vformatBoolean *format
);

void
vformatCopyBoolean (
    vformatBoolean *dest,
    vformatBoolean *src
);

void
vformatCopyInitBoolean (
    vformatBoolean *dest,
    vformatBoolean *src
);

void
vformatDumpBoolean (
    vformatBoolean *format,
    FILE           *stream
);

void
vformatDestroyBoolean (
    vformatBoolean *format
);

vformatBoolean *
vformatLoadBoolean (
    vresource res
);

void
vformatLoadBooleanPatterns (
    vformatBoolean *format,
    vresource       res
);

void
vformatStoreBoolean (
    vformatBoolean *format,
    vresource       res
);

vscribe *
vformatScribeBoolean (
    vformatBoolean *format,
    vbool           value
);

vbool
vformatParseBoolean (
    vformatBoolean *format,
    const vchar    *string
);

int
vformatDetermineBooleanValidity (
    vformatBoolean *format,
    const vchar    *string
);

vbool
vformatIsBooleanValid (
    vformatBoolean *format,
    const vchar    *string
    );

vbool
vformatIsBooleanPartiallyValid (
    vformatBoolean *format,
    const vchar    *string
);

int
vformatGetBooleanOutputSegmentIndex (
    vformatBoolean *format,
    vbool           value
);

const vformatBooleanSegment *
vformatGetBooleanOutputSegment (
    vformatBoolean *format,
    vbool           value
);

void
vformatSetBooleanOutputPatternIndex (
    vformatBoolean  *format,
    int              index
);

int
vformatGetBooleanOutputPatternIndex (
    vformatBoolean *format
);

void
vformatSetBooleanPatterns (
    vformatBoolean  *format,
    const vchar    **strings,
    int              count
);

void
vformatInsertBooleanPatternScribed (
    vformatBoolean *format,
    vscribe        *scribe,
    int             index
);

void
vformatInsertBooleanPattern (
    vformatBoolean *format,
    const vchar    *string,
    int             index
);

void
vformatSetBooleanPatternIndex (
    vformatBoolean *format,
    int             oldIndex,
    int             newIndex
);

void
vformatAppendBooleanPattern (
    vformatBoolean *format,
    const vchar    *string
);

void
vformatDestroyBooleanPatternAt (
    vformatBoolean *format,
    int             index
);

long
vformatGetBooleanPatternCount (
    const vformatBoolean *format
);

int
vformatGetBooleanSegmentCount (
    vformatBoolean *format
);

const vformatBooleanSegment *
vformatGetBooleanPatternSegmentAt (
    vformatBoolean *format,
    int             patternIndex,
    int             segmentIndex
);

/*
 * * BOOLEAN FORMAT SEGMENT INTERFACE
 */

vformatBooleanSegmentClass *
vformatGetDefaultBooleanSegmentClass (
    void
);

vinstance *
vformatGetBooleanSegmentInstance (
    vformatBooleanSegment *segment
);

vformatSegment *
vformatGetBooleanSegmentBase (
    vformatBooleanSegment *segment
);

vformatBooleanSegment *
vformatCreateBooleanSegment (
    void
);

vformatBooleanSegment *
vformatCreateBooleanSegmentOfClass (
    vformatBooleanSegmentClass *clas
);

void
vformatDumpBooleanSegment (
    const vformatBooleanSegment *segment,
    FILE                        *stream
);

void
vformatDestroyBooleanSegment (
    vformatBooleanSegment *segment
);

void
vformatInitBooleanSegment (
    vformatBooleanSegment *segment
);

const vchar *
vformatGetBooleanSegmentString (
    vformatBooleanSegment *segment
);

void
vformatSetBooleanSegmentString (
    vformatBooleanSegment *segment,
    const vchar           *string
);

vcolor *
vformatGetBooleanSegmentColor (
    vformatBooleanSegment *segment
);

void
vformatSetBooleanSegmentColor (
    vformatBooleanSegment *segment,
    vcolor                *color
);

int
vformatGetBooleanSegmentAlignment (
    vformatBooleanSegment *segment
);

void
vformatSetBooleanSegmentAlignment (
    vformatBooleanSegment *segment,
    int                    alignment
);

const vchar *
vformatGetBooleanSegmentFormat (
    vformatBooleanSegment *segment
);

void
vformatSetBooleanSegmentFormat (
    vformatBooleanSegment *segment,
    const vchar           *string
);

void
vformatParseBooleanSegment (
    vformatBooleanSegment *segment,
    int                    segmentIndex
);

void
vformatParseBooleanSegmentPattern (
    vformatBooleanSegment *segment,
    vformatParseRange     *range
);


/*
 * * DOUBLE FORMAT INTERFACE
 */

void
vformatStartupDouble (
    void
);

vformatDoubleClass *
vformatGetDefaultDoubleClass (
    void
);

vformatDoubleClass *
vformatGetDoubleClass (
    vformatDouble *format
);

vloadable *
vformatGetDoubleLoadable (
    vformatDouble *format
);

vformat *
vformatGetDoubleBase (
    vformatDouble *format
);

vformatNumber *
vformatGetDoubleNumber (
    vformatDouble *format
);

vformatDouble *
vformatCreateDouble (
    void
);

vformatDouble *
vformatCloneDouble (
    vformatDouble *format
);

void
vformatInitDouble (
    vformatDouble *format
);

void
vformatCopyDouble (
    vformatDouble *dest,
    vformatDouble *src
);

void
vformatCopyInitDouble (
    vformatDouble *dest,
    vformatDouble *src
);

void
vformatDumpDouble (
    vformatDouble *format,
    FILE          *stream
);

void
vformatDestroyDouble (
    vformatDouble *format
);

vformatDouble *
vformatLoadDouble (
    vresource res
);

void
vformatLoadDoublePatterns (
    vformatDouble *format,
    vresource      res
);

void
vformatStoreDouble (
    vformatDouble *format,
    vresource      res
);

vscribe *
vformatScribeDouble (
    vformatDouble *format,
    double         value
);

void
vformatSetDoubleOutputPatternIndex (
    vformatDouble *format,
    int            index
);

int
vformatGetDoubleOutputPatternIndex (
    vformatDouble *format
);

int
vformatGetDoubleOutputSegmentIndex (
    vformatDouble *format,
    double         value
);

const vformatDoubleSegment *
vformatGetDoubleOutputSegment (
    vformatDouble *format,
    double         value
);

double
vformatParseDouble (
    vformatDouble *format,
    const vchar   *string
);

int
vformatDetermineDoubleValidity (
    vformatDouble *format,
    const vchar   *string
);

vbool
vformatIsDoubleValid (
    vformatDouble *format,
    const vchar   *string
    );

vbool
vformatIsDoublePartiallyValid (
    vformatDouble *format,
    const vchar   *string
);

void
vformatSetDoublePatterns (
    vformatDouble  *format,
    const vchar   **strings,
    int             count
);

void
vformatInsertDoublePatternScribed (
    vformatDouble *format,
    vscribe       *scribe,
    int            index
);

void
vformatInsertDoublePattern (
    vformatDouble *format,
    const vchar   *string,
    int            index
);

void
vformatSetDoublePatternIndex (
    vformatDouble *format,
    int            oldIndex,
    int            newIndex
);

void
vformatAppendDoublePattern (
    vformatDouble *format,
    const vchar   *string
);

void
vformatDestroyDoublePatternAt (
    vformatDouble *format,
    int            at
);

long
vformatGetDoublePatternCount (
    const vformatDouble *format
);

int
vformatGetDoubleSegmentCount (
    vformatDouble *format
);

const vformatDoubleSegment *
vformatGetDoublePatternSegmentAt (
    vformatDouble *format,
    int            patternIndex,
    int            segmentIndex
);

/*
 * * DOUBLE FORMAT SEGMENT INTERFACE
 */

vformatDoubleSegmentClass *
vformatGetDefaultDoubleSegmentClass (
    void
);

vformatNumberSegment *
vformatGetDoubleSegmentBase (
    vformatDoubleSegment *segment
);

vformatDoubleSegment *
vformatCreateDoubleSegment (
    void
);

vformatDoubleSegment *
vformatCreateDoubleSegmentOfClass (
    vformatDoubleSegmentClass *clas
);

void
vformatDumpDoubleSegment (
    const vformatDoubleSegment *segment,
    FILE                       *stream
);

void
vformatDestroyDoubleSegment (
    vformatDoubleSegment *segment
);

void
vformatInitDoubleSegment (
    vformatDoubleSegment *segment
);

const vchar *
vformatGetDoubleSegmentString (
    const vformatDoubleSegment *segment
);

void
vformatSetDoubleSegmentString (
    vformatDoubleSegment *segment,
    const vchar          *string
);

vcolor *
vformatGetDoubleSegmentColor (
    const vformatDoubleSegment *segment
);

void
vformatSetDoubleSegmentColor (
    vformatDoubleSegment *segment,
    vcolor               *color
);

int
vformatGetDoubleSegmentAlignment (
    const vformatDoubleSegment *segment
);

void
vformatSetDoubleSegmentAlignment (
    vformatDoubleSegment *segment,
    int                   alignment
);

void
vformatSetDoubleSegmentPrefix (
    vformatDoubleSegment *segment,
    const vchar          *prefix
);

const vchar *
vformatGetDoubleSegmentPrefix (
    const vformatDoubleSegment *segment
);

void
vformatSetDoubleSegmentSuffix (
    vformatDoubleSegment *segment,
    const vchar          *suffix
);

const vchar *
vformatGetDoubleSegmentSuffix (
    const vformatDoubleSegment *segment
);

double
vformatGetDoubleSegmentScale (
    const vformatDoubleSegment *segment
);

void
vformatSetDoubleSegmentScale (
    vformatDoubleSegment *segment,
    double                scale
);

void
vformatParseDoubleSegment (
    vformatDoubleSegment *segment,
    int                   segmentIndex
);

void
vformatParseDoubleSegmentPattern (
    vformatDoubleSegment *segment,
    vformatParseRange    *range
);


/*
 * * LONG FORMAT INTERFACE
 */

void
vformatStartupLong (
    void
);

vformatLongClass *
vformatGetDefaultLongClass (
    void
);

vformatLongClass *
vformatGetLongClass (
    vformatLong *format
);

vloadable *
vformatGetLongLoadable (
    vformatLong *format
);

vformat *
vformatGetLongBase (
    vformatLong *format
);

vformatNumber *
vformatGetLongNumber (
    vformatLong *format
);

vformatLong *
vformatCreateLong (
    void
);

vformatLong *
vformatCloneLong (
    vformatLong *format
);

void
vformatInitLong (
    vformatLong *format
);

void
vformatCopyLong (
    vformatLong *dest,
    vformatLong *src
);

void
vformatCopyInitLong (
    vformatLong *dest,
    vformatLong *src
);

void
vformatDumpLong (
    vformatLong *format,
    FILE        *stream
    );

void
vformatDestroyLong (
    vformatLong *format
);

vformatLong *
vformatLoadLong (
    vresource res
);

void
vformatLoadLongPatterns (
    vformatLong *format,
    vresource    res
);

void
vformatStoreLong (
    vformatLong *format,
    vresource    res
);

vscribe *
vformatScribeLong (
    vformatLong *format,
    long         value
);

void
vformatSetLongOutputPatternIndex (
    vformatLong *format,
    int          index
);

int
vformatGetLongOutputPatternIndex (
    vformatLong *format
);

int
vformatGetLongOutputSegmentIndex (
    vformatLong *format,
    long         value
);

const vformatLongSegment *
vformatGetLongOutputSegment (
    vformatLong *format,
    long         value
);

long
vformatParseLong (
    vformatLong *format,
    const vchar *string
);

int
vformatDetermineLongValidity (
    vformatLong *format,
    const vchar *string
);

vbool
vformatIsLongValid (
    vformatLong *format,
    const vchar *string
);

vbool
vformatIsLongPartiallyValid (
    vformatLong *format,
    const vchar *string
);

void
vformatSetLongPatterns (
    vformatLong  *format,
    const vchar **strings,
    int           count
);

void
vformatInsertLongPatternScribed (
    vformatLong *format,
    vscribe     *scribe,
    int          index
);

void
vformatInsertLongPattern (
    vformatLong *format,
    const vchar *string,
    int          index
);

void
vformatSetLongPatternIndex (
    vformatLong *format,
    int          oldIndex,
    int          newIndex
);

void
vformatAppendLongPattern (
    vformatLong *format,
    const vchar *string
);

void
vformatDestroyLongPatternAt (
    vformatLong *format,
    int          index
);

long
vformatGetLongPatternCount (
    const vformatLong *format
);

int
vformatGetLongSegmentCount (
    vformatLong *format
);

const vformatLongSegment *
vformatGetLongPatternSegmentAt (
    vformatLong *format,
    int          patternIndex,
    int          segmentIndex
);

/*
 * * LONG FORMAT SEGMENT INTERFACE
 */

vformatLongSegmentClass *
vformatGetDefaultLongSegmentClass (
    void
);

vformatNumberSegment *
vformatGetLongSegmentBase (
    vformatLongSegment *segment
);

vformatLongSegment *
vformatCreateLongSegment (
    void
);

vformatLongSegment *
vformatCreateLongSegmentOfClass (
    vformatLongSegmentClass *clas
);

void
vformatDumpLongSegment (
    const vformatLongSegment *segment,
    FILE                     *stream
);

void
vformatDestroyLongSegment (
    vformatLongSegment *segment
);

void
vformatInitLongSegment (
    vformatLongSegment *segment
);

const vchar *
vformatGetLongSegmentString (
    const vformatLongSegment *segment
);

void
vformatSetLongSegmentString (
    vformatLongSegment *segment,
    const vchar        *string
);

vcolor *
vformatGetLongSegmentColor (
    const vformatLongSegment *segment
);

void
vformatSetLongSegmentColor (
    vformatLongSegment *segment,
    vcolor             *color
);

int
vformatGetLongSegmentAlignment (
    const vformatLongSegment *segment
);

void
vformatSetLongSegmentAlignment (
    vformatLongSegment *segment,
    int                 alignment
);

void
vformatSetLongSegmentPrefix (
    vformatLongSegment *segment,
    const vchar        *prefix
);

const vchar *
vformatGetLongSegmentPrefix (
    const vformatLongSegment *segment
);

void
vformatSetLongSegmentSuffix (
    vformatLongSegment *segment,
    const vchar        *suffix
);

const vchar *
vformatGetLongSegmentSuffix (
    const vformatLongSegment *segment
);

long
vformatGetLongSegmentScale (
    const vformatLongSegment *segment
);

void
vformatSetLongSegmentScale (
    vformatLongSegment *segment,
    long                scale
);

void
vformatParseLongSegment (
    vformatLongSegment *segment,
    int                 segmentIndex
);

void
vformatParseLongSegmentPattern (
    vformatLongSegment *segment,
    vformatParseRange  *range
);


/*
 * * UNSIGNED LONG FORMAT INTERFACE
 */

void
vformatStartupULong (
    void
);

vformatULongClass *
vformatGetDefaultULongClass (
    void
);

vformatULongClass *
vformatGetULongClass (
    vformatULong *format
);

vloadable *
vformatGetULongLoadable (
    vformatULong *format
);

vformat *
vformatGetULongBase (
    vformatULong *format
);

vformatNumber *
vformatGetULongNumber (
    vformatULong *format
);

vformatULong *
vformatCreateULong (
    void
);

vformatULong *
vformatCloneULong (
    vformatULong *format
);

void
vformatInitULong (
    vformatULong *format
);

void
vformatCopyULong (
    vformatULong *dest,
    vformatULong *src
);

void
vformatCopyInitULong (
    vformatULong *dest,
    vformatULong *src
);

void
vformatDumpULong (
    vformatULong *format,
    FILE         *stream
);

void
vformatDestroyULong (
    vformatULong *format
);

vformatULong *
vformatLoadULong (
    vresource res
);

void
vformatLoadULongPatterns (
    vformatULong *format,
    vresource     res
);

void
vformatStoreULong (
    vformatULong *format,
    vresource     res
);

vscribe *
vformatScribeULong (
    vformatULong  *format,
    unsigned long  value
);

void
vformatSetULongOutputPatternIndex (
    vformatULong *format,
    int           indx
);

int
vformatGetULongOutputPatternIndex (
    vformatULong *format
);

int
vformatGetULongOutputSegmentIndex (
    vformatULong *format,
    unsigned long value
);

const vformatULongSegment *
vformatGetULongOutputSegment (
    vformatULong *format,
    long          value
);

unsigned long
vformatParseULong (
    vformatULong *format,
    const vchar  *string
);

int
vformatDetermineULongValidity (
    vformatULong *format,
    const vchar  *string
);

vbool
vformatIsULongValid (
    vformatULong *format,
    const vchar  *string
);

vbool
vformatIsULongPartiallyValid (
    vformatULong *format,
    const vchar  *string
);

void
vformatSetULongPatterns (
    vformatULong  *format,
    const vchar  **strings,
    int            count
);

void
vformatInsertULongPatternScribed (
    vformatULong *format,
    vscribe      *scribe,
    int           index
);

void
vformatInsertULongPattern (
    vformatULong  *format,
    const vchar   *string,
    int            index
);

void
vformatSetULongPatternIndex (
    vformatULong *format,
    int           oldIndex,
    int           newIndex
);

void
vformatAppendULongPattern (
    vformatULong  *format,
    const vchar   *string
);

void
vformatDestroyULongPatternAt (
    vformatULong *format,
    int           index
);

long
vformatGetULongPatternCount (
    const vformatULong  *format
);

int
vformatGetULongSegmentCount (
    vformatULong *format
);

const vformatULongSegment *
vformatGetULongPatternSegmentAt (
    vformatULong *format,
    int           patternIndex,
    int           segmentIndex
);

/*
 * * UNSIGNED LONG FORMAT SEGMENT INTERFACE
 */

vformatULongSegmentClass *
vformatGetDefaultULongSegmentClass (
    void
);

vformatNumberSegment *
vformatGetULongSegmentBase (
    vformatULongSegment *segment
);

vformatULongSegment *
vformatCreateULongSegment (
    void
);

vformatULongSegment *
vformatCreateULongSegmentOfClass (
    vformatULongSegmentClass *clas
);

void
vformatDumpULongSegment (
    const vformatULongSegment *segment,
    FILE                      *stream
);

void
vformatDestroyULongSegment (
    vformatULongSegment *segment
);

void
vformatInitULongSegment (
    vformatULongSegment *segment
);

const vchar *
vformatGetULongSegmentString (
    const vformatULongSegment *segment
);

void
vformatSetULongSegmentString (
    vformatULongSegment *segment,
    const vchar         *string
);

vcolor *
vformatGetULongSegmentColor (
    const vformatULongSegment *segment
);

void
vformatSetULongSegmentColor (
    vformatULongSegment *segment,
    vcolor              *color
);

int
vformatGetULongSegmentAlignment (
    const vformatULongSegment *segment
);

void
vformatSetULongSegmentAlignment (
    vformatULongSegment *segment,
    int                  alignment
);

void
vformatSetULongSegmentPrefix (
    vformatULongSegment *segment,
    const vchar         *prefix
);

const vchar *
vformatGetULongSegmentPrefix (
    const vformatULongSegment *segment
);

void
vformatSetULongSegmentSuffix (
    vformatULongSegment *segment,
    const vchar         *suffix
);

const vchar *
vformatGetULongSegmentSuffix (
    const vformatULongSegment *segment
);

long
vformatGetULongSegmentScale (
    const vformatULongSegment *segment
);

void
vformatSetULongSegmentScale (
    vformatULongSegment *segment,
    long                 scale
);

void
vformatParseULongSegment (
    vformatULongSegment *segment,
    int                  segmentIndex
);

void
vformatParseULongSegmentPattern (
    vformatULongSegment *segment,
    vformatParseRange   *range
);


/*
 * * DATE FORMAT INTERFACE
 */

void
vformatStartupDate (
    void
);

vformatDateClass *
vformatGetDefaultDateClass (
    void
);

vformatDateClass *
vformatGetDateClass (
    vformatDate *format
);

vloadable *
vformatGetDateLoadable (
    vformatDate *format
);

vformat *
vformatGetDateBase (
    vformatDate *format
);

vformatDate *
vformatCreateDate (
    void
);

vformatDate *
vformatCloneDate (
    vformatDate *format
);

void
vformatInitDate (
    vformatDate *format
);

void
vformatCopyDate (
    vformatDate *dest,
    vformatDate *src
);

void
vformatCopyInitDate (
    vformatDate *dest,
    vformatDate *src
);

void
vformatDumpDate (
    vformatDate *format,
    FILE        *stream
);

void
vformatDestroyDate (
    vformatDate *format
);

vformatDate *
vformatLoadDate (
    vresource res
);

void
vformatLoadDatePatterns (
    vformatDate *format,
    vresource    res
);

void
vformatStoreDate (
    vformatDate *format,
    vresource    res
);

vscribe *
vformatScribeDate (
    vformatDate *format,
    const vdate *value
);

void
vformatSetDateOutputPatternIndex (
    vformatDate *format,
    int          indx
);

int
vformatGetDateOutputPatternIndex (
    vformatDate *format
);

int
vformatGetDateOutputSegmentIndex (
    vformatDate *format,
    const vdate *value
);

const vformatDateSegment *
vformatGetDateOutputSegment (
    vformatDate *format,
    const vdate *value
);

vdate *
vformatParseDate (
    vformatDate *format,
    const vchar *string
);

int
vformatDetermineDateValidity (
    vformatDate *format,
    const vchar *string
);

vbool
vformatIsDateValid (
    vformatDate *format,
    const vchar *string
);

vbool
vformatIsDatePartiallyValid (
    vformatDate *format,
    const vchar *string
);

void
vformatSetDatePatterns (
    vformatDate  *format,
    const vchar **strings,
    int           count
);

void
vformatInsertDatePatternScribed (
    vformatDate *format,
    vscribe     *scribe,
    int          count
);

void
vformatInsertDatePattern (
    vformatDate *format,
    const vchar *string,
    int          count
);

void
vformatSetDatePatternIndex (
    vformatDate *format,
    int          oldIndex,
    int          newIndex
);

void
vformatAppendDatePattern (
    vformatDate *format,
    const vchar *string
);

void
vformatDestroyDatePatternAt (
    vformatDate *format,
    int          index
);

long
vformatGetDatePatternCount (
    const vformatDate *format
);

int
vformatGetDateSegmentCount (
    vformatDate *format
);

const vformatDateSegment *
vformatGetDatePatternSegmentAt (
    vformatDate *format,
    int          patternIndex,
    int          segmentIndex
);

/*
 * * DATE FORMAT SEGMENT INTERFACE
 */

vformatDateSegmentClass *
vformatGetDefaultDateSegmentClass (
    void
);

vinstance *
vformatGetDateSegmentInstance (
    vformatDateSegment *segment
);

vformatSegment *
vformatGetDateSegmentBase (
    vformatDateSegment *segment
);

vformatDateSegment *
vformatCreateDateSegment (
    void
);

vformatDateSegment *
vformatCreateDateSegmentOfClass (
    vformatDateSegmentClass *clas
);

void
vformatDumpDateSegment (
    const vformatDateSegment *segment,
    FILE                     *stream
);

void
vformatDestroyDateSegment (
    vformatDateSegment *segment
);

void
vformatInitDateSegment (
    vformatDateSegment *segment
);

const vchar *
vformatGetDateSegmentString (
    const vformatDateSegment *segment
);

void
vformatSetDateSegmentString (
    vformatDateSegment *segment,
    const vchar        *string
);

vcolor *
vformatGetDateSegmentColor (
    const vformatDateSegment *segment
);

void vformatSetDateSegmentColor (
    vformatDateSegment *segment,
    vcolor             *color
);

int
vformatGetDateSegmentAlignment (
    const vformatDateSegment *segment
);

void
vformatSetDateSegmentAlignment (
    vformatDateSegment *segment,
    int                 alignment
);

vdateFormat *
vformatGetDateSegmentFormat (
    const vformatDateSegment *segment
);

void
vformatSetDateSegmentFormat (
    vformatDateSegment *segment,
    vdateFormat        *format
);

void
vformatParseDateSegment (
    vformatDateSegment *segment,
    int                 segmentIndex
);

void
vformatParseDateSegmentPattern (
    vformatDateSegment *segment,
    vformatParseRange  *range
);


/*
 * * DEFAULT, SHARED FORMATS
 */

vformatDate *
vformatGetDefaultDate (
    void
);

vformatLong *
vformatGetDefaultLong (
    void
);

vformatULong *
vformatGetDefaultULong (
    void
);

vformatDouble *
vformatGetDefaultDouble (
    void
);

vformatBoolean *
vformatGetDefaultBoolean (
    void
);

void
vformatInitDefaultNamedFormat (
    vformat     *format,
    const vname *name
);

void
vformatDestroyDefaultNamedFormat (
    const vname *name
);

vformat *
vformatGetDefaultNamedFormat (
    const vname *name
);

/*
 * * * * * * * * * * PRIVATE CONSTANT DEFINITIONS * * * * * * * * * *
 */

enum
{
    _vformatFLAG_LAST
};

enum
{
    _vformatNumberFLAG_TRUNCATE_ZEROES = _vformatFLAG_LAST
};

/*
 * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * *
 */

/*
 * * FORMAT DEFINITION
 */

struct vformat
{
    vloadable    loadable;
    vlist       *segments;
    int          outputIndex;
    const vname *sharedAlias;
};

struct vformatSegment
{
    vinstance  instance;
    vstr      *pattern;
    vcolor    *color;
    int        alignment;
    int        flags;
};

struct vformatSegmentIterator
{
    viterator      iterator;
    vlistIterator  li;
    vformat       *format;
};
                                                                               
#define vformatCLASS(CLASS, FORMAT)                                            \
                                                                               \
    vloadableCLASS (CLASS, FORMAT);                                            \
                                                                               \
    vclassVARIABLE (vformatSEGMENT_CLASS, vformatSegmentClass *);              \
    vclassVARIABLE (vformatSEGMENT_COUNT, int);                                \
                                                                               \
    vclassMETHOD (vformatSET_OUTPUT_PATTERN_INDEX,                             \
        (FORMAT *format, int indx));                                           \
    vclassMETHOD (vformatSET_PATTERNS,                                         \
        (FORMAT *format, const vchar **strings, int count));                   \
    vclassMETHOD (vformatINSERT_PATTERN_SCRIBED,                               \
        (FORMAT *format, vscribe *scribe, int index));                         \
    vclassMETHOD (vformatSET_PATTERN_INDEX,                                    \
        (FORMAT *format, int oldIndex, int newIndex));                         \
    vclassMETHOD_RET (vformatDETERMINE_VALIDITY, int,                          \
        (FORMAT *format, const vchar *string));                                \
    vclassMETHOD (vformatLOAD_PATTERNS,                                        \
        (FORMAT *format, vresource strArr));                                   \
    vclassMETHOD (vformatDESTROY_PATTERN_AT,                                   \
        (FORMAT *format, int at))

struct vformatClass
{
    vformatCLASS (vformatClass,
                  vformat);
};

/*
 * * FORMAT SEGMENT DEFINITION
 */

#define vformatSEGMENT_CLASS(CLASS, SEGMENT)                                   \
                                                                               \
    vinstanceCLASS (CLASS, SEGMENT);                                           \
                                                                               \
    vclassMETHOD (vformatSET_SEGMENT_STRING,                                   \
        (SEGMENT *segment, const vchar *pattern));                             \
    vclassMETHOD (vformatSET_SEGMENT_COLOR,                                    \
        (SEGMENT *segment, vcolor *color));                                    \
    vclassMETHOD (vformatSET_SEGMENT_ALIGNMENT,                                \
        (SEGMENT *segment, int alignment));                                    \
    vclassMETHOD (vformatPARSE_SEGMENT,                                        \
        (SEGMENT *segment, int segmentIndex));                                 \
    vclassMETHOD (vformatPARSE_SEGMENT_PATTERN,                                \
        (SEGMENT *segment, vformatParseRange *range));                         \
    vclassMETHOD (vformatDUMP_SEGMENT,                                         \
        (const SEGMENT *segment, FILE *stream))

struct vformatSegmentClass
{
    vformatSEGMENT_CLASS (vformatSegmentClass, 
                          vformatSegment);
};

/*
 * * FORMAT PARSE RANGE DEFINITION
 */

struct vformatParseRange
{
    vinstance instance;

    int       pos,
              len;
};

#define vformatPARSE_RANGE_CLASS(CLASS, OBJECT)                              \
        vinstanceCLASS (CLASS, OBJECT)

struct vformatParseRangeClass
{
    vformatPARSE_RANGE_CLASS (vformatParseRangeClass,
                              vformatParseRange);
};

/*
 * * FORMAT PARSE EXCEPTION DEFINITION
 */

struct vformatParseException
{
    vexException  parent;
    int           errCode;
    int           offset;
};

#define vformatSEGMENT_ITERATOR_CLASS(CLASS, ITERATOR)                       \
        viteratorCLASS (CLASS, ITERATOR)

typedef struct vformatSegmentIteratorClass
               vformatSegmentIteratorClass;

struct vformatSegmentIteratorClass
{
    vformatSEGMENT_ITERATOR_CLASS (vformatSegmentIteratorClass,
                                   vformatSegmentIterator);
};

/*
 * * NUMBER FORMAT DEFINITION
 */

struct vformatNumber
{
    vformat format;
    vbool   strict;
};

struct vformatNumberSegment
{
    vformatSegment  segment;

    vstr           *prefix,
                   *suffix;
    double          scale;
};

#define vformatNUMBER_CLASS(CLASS, FORMAT)                                     \
    vformatCLASS (CLASS, FORMAT);                                              \
                                                                               \
    vclassMETHOD (vformatSET_NUMBER_STRICT,                                    \
        (FORMAT *format, vbool isStrict))

struct vformatNumberClass
{
    vformatNUMBER_CLASS (vformatNumberClass,
                         vformatNumber);
};

#define vformatNUMBER_SEGMENT_CLASS(CLASS, OBJECT)                             \
    vformatSEGMENT_CLASS (CLASS, OBJECT);                                      \
                                                                               \
    vclassVARIABLE (vformatNUMBER_SEGMENT_DIGIT_SYMBOLS, const vname *)

struct vformatNumberSegmentClass
{
    vformatNUMBER_SEGMENT_CLASS (vformatNumberSegmentClass,
                                 vformatNumberSegment);
};


/*
 * * BOOLEAN FORMAT DEFINITION
 */

struct vformatBoolean
{
    vformat format;
};

struct vformatBooleanSegment
{
    vformatSegment  segment;
    vstr           *format;
};

#define vformatBOOLEAN_CLASS(CLASS, FORMAT)                                  \
                                                                             \
    vformatCLASS (CLASS, FORMAT);                                            \
                                                                             \
    vclassMETHOD_RET (vformatSCRIBE_BOOLEAN, vscribe *,                      \
        (FORMAT *format, vbool value));                                      \
    vclassMETHOD_RET (vformatPARSE_BOOLEAN, vbool,                           \
        (FORMAT *format, const vchar *str))

struct vformatBooleanClass
{
    vformatBOOLEAN_CLASS (vformatBooleanClass,
                          vformatBoolean);
};

#define vformatBOOLEAN_SEGMENT_CLASS(CLASS, OBJECT)                          \
    vformatSEGMENT_CLASS (CLASS, OBJECT)

struct vformatBooleanSegmentClass
{
    vformatBOOLEAN_SEGMENT_CLASS (vformatBooleanSegmentClass,
                                  vformatBooleanSegment);
};


/*
 * * DOUBLE FORMAT DEFINITION
 */

enum _vformatDigitRunType
{
    _vformatDIGIT_RUN_WHOLE_PART  = 0,
    _vformatDIGIT_RUN_REMAINDER   = 1,
    _vformatDIGIT_RUN_EXPONENT    = 2,
    _vformatDIGIT_RUN_NUMERATOR   = 3,
    _vformatDIGIT_RUN_DENOMINATOR = 4,
    _vformatDIGIT_RUN_COUNT       = 5

};

enum _vformatRunFillMode
{
    _vformatFILL_RUN_LEFT,
    _vformatFILL_RUN_RIGHT
};

typedef enum   _vformatDigitRunType
               _vformatDigitRunType;

typedef enum   _vformatRunFillMode
               _vformatRunFillMode;

typedef struct _vformatDigitRun
               _vformatDigitRun;

struct _vformatDigitRun
{
    int                 zeroFillDigits,
                        spaceFillDigits,
                        maxDigits;
    _vformatRunFillMode mode;
    vbool               group;
};

struct vformatDouble
{
    vformatNumber number;
};

struct vformatDoubleSegment
{
    vformatNumberSegment segment;

    _vformatDigitRun     runs [_vformatDIGIT_RUN_COUNT];
    unsigned int         flags;
    vbool                hasDecimal;
    int                  fractionalBase;
    vbool                reduceFraction;
};

#define vformatDOUBLE_CLASS(CLASS, FORMAT)                                   \
                                                                             \
    vformatNUMBER_CLASS (CLASS, FORMAT);                                     \
                                                                             \
    vclassMETHOD_RET (vformatSCRIBE_DOUBLE, vscribe *,                       \
        (FORMAT *format, double value));                                     \
    vclassMETHOD_RET (vformatPARSE_DOUBLE, double,                           \
        (FORMAT *format, const vchar *str))

struct vformatDoubleClass
{
    vformatDOUBLE_CLASS (vformatDoubleClass,
                         vformatDouble);
};

#define vformatDOUBLE_SEGMENT_CLASS(CLASS, OBJECT)                           \
    vformatNUMBER_SEGMENT_CLASS (CLASS, OBJECT)

struct vformatDoubleSegmentClass
{
    vformatDOUBLE_SEGMENT_CLASS (vformatDoubleSegmentClass,
                                 vformatDoubleSegment);
};

/*
 * * LONG FORMAT DEFINITION
 */

struct vformatLong
{
    vformatNumber number;
};

struct vformatLongSegment
{
    vformatNumberSegment segment;

    _vformatDigitRun     run;
};

#define vformatLONG_CLASS(CLASS, FORMAT)                                     \
                                                                             \
    vformatNUMBER_CLASS (CLASS, FORMAT);                                     \
                                                                             \
    vclassMETHOD_RET (vformatSCRIBE_LONG, vscribe *,                         \
        (FORMAT *format, long value));                                       \
    vclassMETHOD_RET (vformatPARSE_LONG, long,                               \
        (FORMAT *format, const vchar *str))

struct vformatLongClass
{
    vformatLONG_CLASS (vformatLongClass,
                       vformatLong);
};

#define vformatLONG_SEGMENT_CLASS(CLASS, OBJECT)                             \
    vformatNUMBER_SEGMENT_CLASS (CLASS, OBJECT)

struct vformatLongSegmentClass
{
    vformatLONG_SEGMENT_CLASS (vformatLongSegmentClass,
                               vformatLongSegment);
};

/*
 * * UNSIGNED LONG FORMAT DEFINITION
 */

struct vformatULong
{
    vformatNumber number;
};

struct vformatULongSegment
{
    vformatNumberSegment segment;

    _vformatDigitRun     run;
};

#define vformatULONG_CLASS(CLASS, FORMAT)                                    \
                                                                             \
    vformatNUMBER_CLASS (CLASS, FORMAT);                                     \
                                                                             \
    vclassMETHOD_RET (vformatSCRIBE_ULONG, vscribe *,                        \
        (FORMAT *format, unsigned long value));                              \
    vclassMETHOD_RET (vformatPARSE_ULONG, unsigned long,                     \
        (FORMAT *format, const vchar *str))

struct vformatULongClass
{
    vformatULONG_CLASS (vformatULongClass,
                        vformatULong);
};

#define vformatULONG_SEGMENT_CLASS(CLASS, OBJECT)                            \
    vformatNUMBER_SEGMENT_CLASS (CLASS, OBJECT)

struct vformatULongSegmentClass
{
    vformatULONG_SEGMENT_CLASS (vformatULongSegmentClass,
                                vformatULongSegment);
};

/*
 * * DATE FORMAT DEFINITION
 */

struct vformatDate
{
    vformat format;
};

struct vformatDateSegment
{
    vformatSegment  segment;
    vdateFormat    *format;
    vnumFormat     *numfmt;
    vbool           hour24;
};

#define vformatDATE_CLASS(CLASS, FORMAT)                                     \
                                                                             \
    vformatCLASS (CLASS, FORMAT);                                            \
                                                                             \
    vclassMETHOD_RET (vformatSCRIBE_DATE, vscribe *,                         \
        (FORMAT *format, const vdate *value));                               \
    vclassMETHOD_RET (vformatPARSE_DATE, vdate *,                            \
        (FORMAT *format, const vchar *str))

struct vformatDateClass
{
    vformatDATE_CLASS (vformatDateClass,
                       vformatDate);
};

#define vformatDATE_SEGMENT_CLASS(CLASS, OBJECT)                             \
    vformatSEGMENT_CLASS (CLASS, OBJECT)

struct vformatDateSegmentClass
{
    vformatDATE_SEGMENT_CLASS (vformatDateSegmentClass,
                               vformatDateSegment);
};


/*
 * * * * * * * * * * PRIVATE FUNCTION PROTOTYPES * * * * * * * * * *
 */

viterator *_vformatGetSegmentIteratorIterator(vformatSegmentIterator *iterator);

/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * *
 */

/*
 * * FORMAT PARSE EXCEPTION MACROS
 */

#define vformatGetParseException()                                           \
  ((vformatParseException *)                                                 \
    vexGetExceptionOfClass (                                                 \
        vformatGetParseExceptionClass ()))

#define vformatGetParseExceptionOffset(e)                                    \
    ((e)->offset)

#define vformatGetParseExceptionCode(e)                                      \
    ((e)->errCode)

/*
 * * FORMAT MACROS
 */

#define vformatGetLoadable(format)                                           \
    vportBASE_OBJECT (                                                       \
        (format),                                                            \
        loadable)

#define vformatGetInstance(format)                                           \
    vloadableGetInstance (                                                   \
        vformatGetLoadable (format))

#define vformatCreateOfClass(c)                                              \
    ((vformat *)                                                             \
        vloadableCreateOfClass (                                             \
            (vloadableClass *) (c)))

#define vformatCreate()                                                      \
    vformatCreateOfClass (                                                   \
        vformatGetDefaultClass ())

#define vformatClone(format)                                                 \
    ((vformat *)                                                             \
        vloadableClone (                                                     \
            vformatGetLoadable (format)))

#define vformatInit(format)                                                  \
  vformatInitOfClass (                                                       \
        (format),                                                            \
        vformatGetDefaultClass ())

#define vformatInitOfClass(format, clas)                                     \
  vloadableInitOfClass (                                                     \
        vformatGetLoadable (format),                                         \
        (vformatClass *)(clas))

#define vformatCopy(src, dest)                                               \
    vloadableCopy (                                                          \
        vformatGetLoadable (src),                                            \
        vformatGetLoadable (dest))

#define vformatCopyInit(src, dest)                                           \
    vloadableCopyInit (                                                      \
        vformatGetLoadable (src),                                            \
        vformatGetLoadable (dest))

#define vformatDump(format, stream)                                          \
    vloadableDump (                                                          \
        vformatGetLoadable (format),                                         \
        (stream))

#define vformatDestroy(format)                                               \
    vloadableDestroy (                                                       \
        vformatGetLoadable (format))

#define vformatLoad(res)                                                     \
    ((vformat *)                                                             \
        vloadableLoad (res))

#define vformatLoadPatterns(format, res)                                     \
    vclassSend (                                                             \
        vformatGetClass (format),                                            \
        vformatLOAD_PATTERNS,                                                \
        (format, res)) 

#define vformatGetSegmentCount(format)                                       \
    vclassGet (                                                              \
        vformatGetClass (format),                                            \
        vformatSEGMENT_COUNT)

#define vformatStore(format, res)                                            \
    vloadableStore (                                                         \
        vformatGetLoadable (format),                                         \
        (res))

#define vformatGetClass(format)                                              \
    ((vformatClass *)                                                        \
        vloadableGetClass (                                                  \
            vformatGetLoadable (format)))

#define vformatDetermineValidity(format, string)                             \
    vclassSend (                                                             \
        vformatGetClass (format),                                            \
        vformatDETERMINE_VALIDITY,                                           \
        (format, string))

#define vformatSetPatterns(format, strings, count)                           \
    vclassSend (                                                             \
        vformatGetClass (format),                                            \
        vformatSET_PATTERNS,                                                 \
        (format, strings, count))

#define vformatInsertPatternScribed(format, scribe, index)                   \
    vclassSend (                                                             \
        vformatGetClass (format),                                            \
        vformatINSERT_PATTERN_SCRIBED,                                       \
        (format, scribe, index))

#define vformatInsertPattern(format, string, index)                          \
    vformatInsertPatternScribed (                                            \
        (format),                                                            \
        vcharScribe (string),                                                \
        (index))

#define vformatAppendPattern(format, string)                                 \
    vformatInsertPattern (                                                   \
        (format),                                                            \
        (string),                                                            \
        vformatGetPatternCount (format))

#define vformatDestroyPatternAt(format, index)                               \
    vclassSend (                                                             \
        vformatGetClass (format),                                            \
        vformatDESTROY_PATTERN_AT,                                           \
        (format, index))

#define vformatGetSegmentInstance(segment)                                   \
    vportBASE_OBJECT (                                                       \
        (segment),                                                           \
        instance)

#define vformatSetPatternIndex(format, oldIndex, newIndex)                   \
    vclassSend (                                                             \
        vformatGetClass (format),                                            \
        vformatSET_PATTERN_INDEX,                                            \
        (format, oldIndex, newIndex))

#define vformatSetOutputPatternIndex(format, index)                          \
	vclassSend (                                                             \
        vformatGetClass (format),                                            \
        vformatSET_OUTPUT_PATTERN_INDEX,                                     \
        (format, index))

#define vformatGetOutputPatternIndex(format)                                 \
    ((format)->outputIndex)

#define vformatSetSharedAlias(format, alias)                                 \
    ((format)->sharedAlias = alias)

#define vformatGetSharedAlias(format)                                        \
    ((format)->sharedAlias)

#define vformatDumpSegment(segment, stream)                                  \
    vclassSend (                                                             \
        vformatGetSegmentClass (segment),                                    \
        vformatDUMP_SEGMENT,                                                 \
        (segment, stream))

/*
 * * FORMAT SEGMENT MACROS
 */

#define vformatGetSegmentClass(segment)                                      \
    ((vformatSegmentClass *)                                                 \
        vinstanceGetClass (                                                  \
            vformatGetSegmentInstance (segment)))

#define vformatCreateSegment()                                               \
    ((vformatSegment *)                                                      \
        vinstanceCreateOfClass (                                             \
            vformatGetDefaultSegmentClass ()))

#define vformatCreateSegmentOfClass(clas)                                    \
    ((vformatSegment *)                                                      \
        vinstanceCreateOfClass (                                             \
            (vinstanceClass *) (clas)))

#define vformatDestroySegment(segment)                                       \
    vinstanceDestroy (                                                       \
        vformatGetSegmentInstance (segment))

#define vformatInitSegmentOfClass(segment, clas)                             \
    vinstanceInitOfClass (                                                   \
        vformatGetSegmentInstance (segment),                                 \
        (vinstanceClass *) (clas))

#define vformatInitSegment(segment)                                          \
    vformatInitSegmentOfClass (                                              \
        segment,                                                             \
        vformatGetDefaultSegmentClass ())

#define vformatSetSegmentString(segment, string)                             \
    vclassSend (                                                             \
        vformatGetSegmentClass (segment),                                    \
        vformatSET_SEGMENT_STRING,                                           \
        (segment, string))

#define vformatGetSegmentString(segment)                                     \
    ((const vchar *) ((segment)->pattern))

#define vformatSetSegmentColor(segment, color)                               \
    vclassSend (                                                             \
        vformatGetSegmentClass (segment),                                    \
        vformatSET_SEGMENT_COLOR,                                            \
        (segment, color))

#define vformatGetSegmentColor(segment)                                      \
    ((segment)->color)

#define vformatSetSegmentAlignment(segment, alignment)                       \
    vclassSend (                                                             \
        vformatGetSegmentClass (segment),                                    \
        vformatSET_SEGMENT_ALIGNMENT,                                        \
        (segment, alignment))

#define vformatGetSegmentAlignment(segment)                                  \
    ((segment)->alignment)

#define vformatGetSegmentFlags(segment)                                      \
    ((segment)->flags)

#define vformatParseSegment(segment, segmentIndx)                            \
    vclassSend (                                                             \
        vformatGetSegmentClass (segment),                                    \
        vformatPARSE_SEGMENT,                                                \
        (segment, segmentIndx))

#define vformatParseSegmentPattern(segment, range)                           \
    vclassSend (                                                             \
        vformatGetSegmentClass (segment),                                    \
        vformatPARSE_SEGMENT_PATTERN,                                        \
        (segment, range))

/*
 * * FORMAT SEGMENT ITERATOR MACROS
 */

#define _vformatGetSegmentIteratorIterator(_iter)                             \
    vportBASE_OBJECT (                                                       \
        (_iter),                                                             \
        iterator)

#define vformatNextSegmentIterator(iter)                                     \
    viteratorNext (                                                          \
        _vformatGetSegmentIteratorIterator (iter))

#define vformatGetSegmentIteratorSegment(iter)                               \
    ((const vformatSegment *)                                                \
        viteratorGetElement (                                                \
            _vformatGetSegmentIteratorIterator (iter)))

#define vformatDestroySegmentIterator(iter)                                  \
    viteratorDestroy (                                                       \
        _vformatGetSegmentIteratorIterator (iter))

/*
 * * FORMAT PARSE RANGE MACROS
 */

#define vformatGetParseRangeInstance(range)                                  \
    vportBASE_OBJECT (                                                       \
        (range),                                                             \
        instance)

#define vformatGetParseRangeClass(range)                                     \
    ((vformatParseRangeClass *)                                              \
        vinstanceGetClass (                                                  \
            vformatGetParseRangeInstance (range)))

#define vformatCreateParseRangeOfClass(clas)                                 \
    ((vformatParseRange *)                                                   \
        vinstanceCreateOfClass (                                             \
            (vinstanceClass *) (clas)))

#define vformatCreateParseRange()                                            \
    vformatCreateParseRangeOfClass (                                         \
        vformatGetDefaultParseRangeClass ()))

#define vformatDestroyParseRange(range)                                      \
    vinstanceDestroy (                                                       \
        vformatGetParseRangeInstance (range))

#define vformatInitParseRangeOfClass(range, clas)                            \
    vinstanceInitOfClass (                                                   \
        vformatGetParseRangeInstance (range),                                \
        (vinstanceClass *) clas)

#define vformatInitParseRange(range)                                         \
    vformatInitParseRangeOfClass (                                           \
        range,                                                               \
        vformatGetDefaultParseRangeClass ())

/*
 * * NUMBER FORMAT MACROS
 */

#define vformatGetNumberBase(_format)                                        \
    vportBASE_OBJECT (                                                       \
        (_format),                                                           \
        format)

#define vformatCreateNumber()                                                \
    ((vformatNumber *)                                                       \
        vformatCreateOfClass (                                               \
            vformatGetDefaultNumberClass ()))

#define vformatCloneNumber(format)                                           \
    ((vformatNumber *)                                                       \
        vformatClone (                                                       \
            vformatGetNumberBase (format)))

#define vformatInitNumber(format)                                            \
    vformatInit (                                                            \
        vformatGetNumberBase (format))

#define vformatCopyNumber(dest, src)                                         \
    vformatCopy (                                                            \
        vformatGetNumberBase (dest),                                         \
        vformatGetNumberBase (src))

#define vformatCopyInitNumber(dest, src)                                     \
    vformatCopyInit (                                                        \
        vformatGetNumberBase (dest),                                         \
        vformatGetNumberBase (src))

#define vformatDumpNumber(format, stream)                                    \
    vformatDump (                                                            \
        vformatGetNumberBase (format),                                       \
        stream)

#define vformatDestroyNumber(format)                                         \
    vformatDestroy (                                                         \
        vformatGetNumberBase (format))

#define vformatLoadNumber(res)                                               \
    ((vformatNumber *)                                                       \
        vformatLoad (res))

#define vformatLoadNumberPatterns(format, res)                               \
    vformatLoadPatterns (                                                    \
        vformatGetNumberBase (format),                                       \
        (res))

#define vformatStoreNumber(format, res)                                      \
    vformatStore (                                                           \
        vformatGetNumberBase (format),                                       \
        (res))

#define vformatGetNumberClass(format)                                        \
    ((vformatNumberClass *)                                                  \
        (vformatGetClass (                                                   \
            vformatGetNumberBase (format))))

#define vformatGetNumberLoadable(format)                                     \
    vformatGetLoadable (                                                     \
        vformatGetNumberBase (format))

#define vformatSetNumberOutputPatternIndex(format, index)                    \
    vformatSetOutputPatternIndex (                                           \
        vformatGetNumberBase (format),                                       \
        (index))

#define vformatGetNumberOutputPatternIndex(format)                           \
    vformatGetOutputPatternIndex (                                           \
        vformatGetNumberBase (format))

#define vformatSetNumberPatterns(format, strings, count)                     \
    vformatSetPatterns (                                                     \
        vformatGetNumberBase (format),                                       \
        (strings),                                                           \
        (count))

#define vformatInsertNumberPatternScribed(format, scribe, index)           \
    vformatInsertPatternScribed (                                          \
        vformatGetNumberBase (format),                                       \
        (scribe),                                                            \
        (index))

#define vformatInsertNumberPattern(format, string, index)                  \
    vformatInsertPattern (                                                 \
        vformatGetNumberBase (format),                                       \
        (string),                                                            \
        (index))

#define vformatSetNumberPatternIndex(format, oldIndex, newIndex)             \
    vformatSetPatternIndex (                                                 \
        vformatGetNumberBase (format),                                       \
        (oldIndex),                                                          \
        (newIndex))

#define vformatAppendNumberPattern(format, string)                           \
    vformatAppendPattern (                                                   \
        vformatGetNumberBase (format),                                       \
        (string))

#define vformatDestroyNumberPatternAt(format, index)                         \
    vformatDestroyPatternAt (                                                \
        vformatGetNumberBase (format),                                       \
        (index))

#define vformatGetNumberPatternCount(format)                                 \
    vformatGetPatternCount (                                                 \
        vformatGetNumberBase (format))

#define vformatGetNumberSegmentCount(format)                                 \
    vclassSend (                                                             \
        vformatGetNumberClass (format),                                      \
        vformatGET_SEGMENT_COUNT)

#define vformatGetNumberPatternSegmentAt(f, pi, si)                          \
    ((const vformatNumberSegment *)                                          \
        vformatGetPatternSegmentAt (                                         \
            vformatGetNumberBase (f),                                        \
            (pi),                                                            \
            (si)))

#define vformatIsNumberValid(format, string)                                 \
    vformatIsValid (                                                         \
        vformatGetNumberBase (format),                                       \
        (string))

#define vformatIsNumberPartiallyValid(format, string)                        \
    vformatIsPartiallyValid (                                                \
        vformatGetNumberBase (format),                                       \
        (string))

#define vformatDetermineNumberValidity(format, string)                       \
    vformatDetermineValidity (                                               \
        vformatGetNumberBase (format),                                       \
        (string))

#define vformatIsNumberStrict(format)                                        \
    ((format)->strict)

/*
 * * NUMBER FORMAT SEGMENT MACROS
 */

#define vformatGetNumberSegmentClass(segment)                                \
    ((vformatNumberSegmentClass *)                                           \
        vinstanceGetClass (                                                  \
            vformatGetNumberSegmentInstance (segment)))

#define vformatCreateNumberSegment()                                         \
    ((vformatNumberSegment *)                                                \
        vinstanceCreateOfClass (                                             \
            vformatGetDefaultNumberSegmentClass ()))

#define vformatCreateNumberSegmentOfClass(clas)                              \
    ((vformatNumberSegment *)                                                \
        vinstanceCreateOfClass (                                             \
            (vinstanceClass *) (clas)))
                                                     
#define vformatGetNumberSegmentBase(_segment)                                \
    vportBASE_OBJECT (                                                       \
        (_segment),                                                          \
        segment)
    
#define vformatGetNumberSegmentInstance(segment)                             \
    vformatGetSegmentInstance (                                              \
        vformatGetNumberSegmentBase (segment)) 

#define vformatDumpNumberSegment(segment, stream)                            \
    vformatDumpSegment (                                                     \
        vformatGetNumberSegmentBase (segment),                               \
        (stream))

#define vformatDestroyNumberSegment(segment)                                 \
    vformatDestroySegment (                                                  \
        vformatGetNumberSegmentBase (segment))

#define vformatInitNumberSegment(segment)                                    \
    vformatInitSegment (                                                     \
        vformatGetNumberSegmentBase (segment))

#define vformatGetNumberSegmentString(segment)                               \
    vformatGetSegmentString (                                                \
        vformatGetNumberSegmentBase (segment))

#define vformatSetNumberSegmentString(segment)                               \
    vformatSetSegmentString (                                                \
        vformatGetNumberSegmentBase (segment))

#define vformatGetNumberSegmentColor(segment)                                \
    vformatGetSegmentColor (                                                 \
        vformatGetNumberSegmentBase (segment))

#define vformatGetNumberSegmentAlignment(segment)                            \
    vformatGetSegmentAlignment (                                             \
        vformatGetNumberSegmentBase (segment))

#define vformatGetNumberSegmentScale(segment)                                \
    ((segment)->scale)

#define vformatParseNumberSegment(segment, segIndx)                          \
    vformatParseSegment (                                                    \
        vformatGetNumberSegmentBase (segment),                               \
        (segIndx))

#define vformatParseNumberSegmentPattern(segment, range)                     \
    vformatParseSegmentPattern (                                             \
        vformatGetNumberSegmentBase (segment),                               \
        (range))

/*
 * * BOOLEAN FORMAT MACROS
 */

#define vformatGetBooleanBase(_format)                                       \
    vportBASE_OBJECT (                                                       \
        (_format),                                                           \
        format)

#define vformatCreateBoolean()                                               \
    ((vformatBoolean *)                                                      \
        vformatCreateOfClass (                                               \
            vformatGetDefaultBooleanClass ()))

#define vformatCloneBoolean(format)                                          \
    ((vformatBoolean *)                                                      \
        vformatClone (                                                       \
            vformatGetBooleanBase (format)))

#define vformatInitBoolean(format)                                           \
    vformatInit (                                                            \
        vformatGetBooleanBase (format))

#define vformatCopyBoolean(dest, src)                                        \
    vformatCopy (                                                            \
        vformatGetBooleanBase (dest),                                        \
        vformatGetBooleanBase (src))

#define vformatCopyInitBoolean(dest, src)                                    \
    vformatCopyInit (                                                        \
        vformatGetBooleanBase (dest),                                        \
        vformatGetBooleanBase (src))

#define vformatDumpBoolean(format, stream)                                   \
    vformatDump (                                                            \
        vformatGetBooleanBase (format),                                      \
        (stream))

#define vformatDestroyBoolean(format)                                        \
    vformatDestroy (                                                         \
        vformatGetBooleanBase (format))

#define vformatLoadBoolean(res)                                              \
    ((vformatBoolean *)                                                      \
        vformatLoad (res))

#define vformatLoadBooleanPatterns(format, res)                              \
    vformatLoadPatterns (                                                    \
        vformatGetBooleanBase (format),                                      \
        (res))

#define vformatStoreBoolean(format, res)                                     \
    vformatStore (                                                           \
        vformatGetBooleanBase (format),                                      \
        (res))

#define vformatGetBooleanClass(format)                                       \
    ((vformatBooleanClass *)                                                 \
        vformatGetClass (                                                    \
            vformatGetBooleanBase (format)))

#define vformatGetBooleanLoadable(format)                                    \
    vformatGetLoadable (                                                     \
        vformatGetBooleanBase (format))

#define vformatSetBooleanOutputPatternIndex(format, index)                   \
    vformatSetOutputPatternIndex (                                           \
        vformatGetBooleanBase (format),                                      \
        (index))

#define vformatGetBooleanOutputPatternIndex(format)                          \
    vformatGetOutputPatternIndex (                                           \
        vformatGetBooleanBase (format))

#define vformatSetBooleanPatterns(format, strings, count)                    \
    vformatSetPatterns (                                                     \
        vformatGetBooleanBase (format),                                      \
        (strings),                                                           \
        (count))

#define vformatInsertBooleanPatternScribed(format, scribe, index)          \
    vformatInsertPatternScribed (                                          \
        vformatGetBooleanBase (format),                                      \
        (scribe),                                                            \
        (index))

#define vformatInsertBooleanPattern(format, string, index)                 \
    vformatInsertPattern (                                                 \
        vformatGetBooleanBase (format),                                      \
        (string),                                                            \
        (index))

#define vformatSetBooleanPatternIndex(format, oldIndex, newIndex)            \
    vformatSetPatternIndex (                                                 \
        vformatGetBooleanBase (format),                                      \
        (oldIndex),                                                          \
        (newIndex))

#define vformatAppendBooleanPattern(format, string)                          \
    vformatAppendPattern (                                                   \
        vformatGetBooleanBase (format),                                      \
        (string))

#define vformatDestroyBooleanPatternAt(format, index)                        \
    vformatDestroyPatternAt (                                                \
        vformatGetBooleanBase (format),                                      \
        (index))

#define vformatGetBooleanPatternCount(format)                                \
    vformatGetPatternCount (                                                 \
        vformatGetBooleanBase (format))

#define vformatGetBooleanSegmentCount(format)                                \
    vclassSend (                                                             \
        vformatGetBooleanClass (format),                                     \
        vformatGET_SEGMENT_COUNT)

#define vformatGetBooleanPatternSegmentAt(f, pi, si)                         \
    ((const vformatBooleanSegment *)                                         \
        vformatGetPatternSegmentAt (                                         \
            vformatGetBooleanBase (f),                                       \
            (pi),                                                            \
            (si)))

#define vformatIsBooleanValid(format, string)                                \
    vformatIsValid (                                                         \
        vformatGetBooleanBase (format),                                      \
        (string))

#define vformatIsBooleanPartiallyValid(format, string)                       \
    vformatIsPartiallyValid (                                                \
        vformatGetBooleanBase (format),                                      \
        (string))

#define vformatDetermineBooleanValidity(format, string)                      \
    vformatDetermineValidity (                                               \
        vformatGetBooleanBase (format),                                      \
        (string))

#define vformatParseBoolean(format, string)                                  \
    vclassSend (                                                             \
        vformatGetBooleanClass (format),                                     \
        vformatPARSE_BOOLEAN,                                                \
        (format, string))

#define vformatScribeBoolean(format, value)                                  \
    vclassSend (                                                             \
        vformatGetBooleanClass (format),                                     \
        vformatSCRIBE_BOOLEAN,                                               \
        (format, value))

/*
 * * BOOLEAN FORMAT SEGMENT MACROS
 */

#define vformatCreateBooleanSegment()                                        \
    vformatCreateBooleanSegmentOfClass (                                     \
        vformatGetDefaultBooleanSegmentClass ())

#define vformatCreateBooleanSegmentOfClass(clas)                             \
    ((vformatBooleanSegment *)                                               \
        vinstanceCreateOfClass (                                             \
            (vinstanceClass *) (clas)))

#define vformatGetBooleanSegmentBase(_segment)                               \
    vportBASE_OBJECT (                                                       \
        (_segment),                                                          \
        segment)
    
#define vformatGetBooleanSegmentInstance(segment)                            \
    vformatGetSegmentInstance (                                              \
        vformatGetBooleanSegmentBase (segment)) 

#define vformatDumpBooleanSegment(segment, stream)                           \
    vformatDumpSegment (                                                     \
        vformatGetBooleanSegmentBase (segment),                              \
        (stream))

#define vformatDestroyBooleanSegment(segment)                                \
    vformatDestroySegment (                                                  \
        vformatGetBooleanSegmentBase (segment))

#define vformatInitBooleanSegment(segment)                                   \
    vformatInitSegment (                                                     \
        vformatGetBooleanSegmentBase (segment))

#define vformatGetBooleanSegmentString(segment)                              \
    vformatGetSegmentString (                                                \
        vformatGetBooleanSegmentBase (segment))

#define vformatSetBooleanSegmentString(segment)                              \
    vformatSetSegmentString (                                                \
        vformatGetBooleanSegmentBase (segment))

#define vformatGetBooleanSegmentColor(segment)                               \
    vformatGetSegmentColor (                                                 \
        vformatGetBooleanSegmentBase (segment))

#define vformatSetBooleanSegmentColor(segment, color)                        \
    vformatSetSegmentColor (                                                 \
        vformatGetBooleanSegmentBase (segment),                              \
        (color))

#define vformatGetBooleanSegmentAlignment(segment)                           \
    vformatGetSegmentAlignment (                                             \
        vformatGetBooleanSegmentBase (segment))

#define vformatSetBooleanSegmentAlignment(segment, alignment)                \
    vformatSetSegmentAlignment (                                             \
        vformatGetBooleanSegmentBase (segment),                              \
        (alignment))
     
#define vformatGetBooleanSegmentFormat(segment)                              \
    ((const vchar *) (segment)->format)

#define vformatParseBooleanSegment(segment, segIndx)                         \
    vformatParseSegment (                                                    \
        vformatGetBooleanSegmentBase (segment),                              \
        (segIndx))

#define vformatParseBooleanSegmentPattern(segment, range)                    \
    vformatParseSegmentPattern (                                             \
        vformatGetBooleanSegmentBase (segment),                              \
        (range))

/*
 * * DOUBLE FORMAT MACROS
 */

#define vformatGetDoubleNumber(format)                                         \
    vportBASE_OBJECT (                                                       \
        (format),                                                            \
        number)

#define vformatGetDoubleBase(format)                                           \
    vformatGetNumberBase(vformatGetDoubleNumber(format))

#define vformatCreateDouble()                                                \
    ((vformatDouble *)                                                       \
        vformatCreateOfClass (                                               \
            vformatGetDefaultDoubleClass ()))

#define vformatCloneDouble(format)                                           \
    ((vformatDouble *)                                                       \
        vformatCloneNumber (                                                 \
            vformatGetDoubleNumber (format)))

#define vformatInitDouble(format)                                            \
    vformatInitNumber (                                                      \
        vformatGetDoubleNumber (format))

#define vformatCopyDouble(dest, src)                                         \
    vformatCopyNumber (                                                      \
        vformatGetDoubleNumber (dest),                                         \
        vformatGetDoubleNumber (src))

#define vformatCopyInitDouble(dest, src)                                     \
    vformatCopyInitNumber (                                                  \
        vformatGetDoubleNumber (dest),                                         \
        vformatGetDoubleNumber (src))

#define vformatDumpDouble(format, stream)                                    \
    vformatDumpNumber (                                                      \
        vformatGetDoubleNumber (format),                                       \
        stream)

#define vformatDestroyDouble(format)                                         \
    vformatDestroyNumber (                                                   \
        vformatGetDoubleNumber (format))

#define vformatLoadDouble(res)                                               \
    ((vformatDouble *)                                                       \
        vformatLoadNumber (res))

#define vformatLoadDoublePatterns(format, res)                               \
    vformatLoadNumberPatterns (                                              \
        vformatGetDoubleNumber (format),                                       \
        (res))

#define vformatStoreDouble(format, res)                                      \
    vformatStoreNumber (                                                     \
        vformatGetDoubleNumber (format),                                       \
        (res))

#define vformatGetDoubleLoadable(format)                                     \
    vformatGetNumberLoadable (                                               \
        vformatGetDoubleNumber (format))

#define vformatGetDoubleClass(format)                                        \
    ((vformatDoubleClass *)                                                  \
        vformatGetNumberClass (                                              \
            vformatGetDoubleNumber (format)))

#define vformatParseDouble(format, string)                                   \
    vclassSend (                                                             \
        vformatGetDoubleClass (format),                                      \
        vformatPARSE_DOUBLE,                                                 \
        (format, string))

#define vformatScribeDouble(format, value)                                   \
    vclassSend (                                                             \
        vformatGetDoubleClass (format),                                      \
        vformatSCRIBE_DOUBLE,                                                \
        (format, value))                                                     

#define vformatSetDoublePatterns(format, strings, count)                     \
    vformatSetNumberPatterns (                                               \
        vformatGetDoubleNumber (format),                                       \
        (strings),                                                           \
        (count))

#define vformatInsertDoublePatternScribed(format, scribe, index)           \
    vformatInsertNumberPatternScribed (                                    \
        vformatGetDoubleNumber (format),                                       \
        (scribe),                                                            \
        (index))

#define vformatInsertDoublePattern(format, string, index)                  \
    vformatInsertNumberPattern (                                           \
        vformatGetDoubleNumber (format),                                       \
        (string),                                                            \
        (index))

#define vformatSetDoublePatternIndex(format, oldIndex, newIndex)             \
    vformatSetNumberPatternIndex (                                           \
        vformatGetDoubleNumber (format),                                       \
        (oldIndex),                                                          \
        (newIndex))

#define vformatAppendDoublePattern(format, string)                           \
    vformatAppendNumberPattern (                                             \
        vformatGetDoubleNumber (format),                                       \
        (string))

#define vformatDestroyDoublePatternAt(format, index)                         \
    vformatDestroyNumberPatternAt (                                          \
        vformatGetDoubleNumber (format),                                       \
        (index))

#define vformatGetDoublePatternCount(format)                                 \
    vformatGetNumberPatternCount (                                           \
        vformatGetDoubleNumber (format))

#define vformatGetDoubleSegmentCount(format)                                 \
    vformatGetNumberSegmentCount (                                           \
        vformatGetDoubleNumber (format))

#define vformatGetDoublePatternSegmentAt(f, pi, si)                          \
    ((const vformatDoubleSegment *)                                          \
        vformatGetNumberPatternSegmentAt (                                   \
            vformatGetDoubleNumber (f),                                        \
            (pi),                                                            \
            (si)))

#define vformatSetDoubleOutputPatternIndex(format, index)                    \
    vformatSetNumberOutputPatternIndex (                                     \
        vformatGetDoubleNumber (format),                                       \
        (index))

#define vformatGetDoubleOutputPatternIndex(format)                           \
    vformatGetNumberOutputPatternIndex (                                     \
        vformatGetDoubleNumber (format))

#define vformatIsDoubleValid(format, string)                                 \
    vformatIsNumberValid (                                                   \
        vformatGetDoubleNumber (format),                                       \
        (string))

#define vformatIsDoublePartiallyValid(format, string)                        \
    vformatIsNumberPartiallyValid (                                          \
        vformatGetDoubleNumber (format),                                       \
        (string))

#define vformatDetermineDoubleValidity(format, string)                       \
    vformatDetermineNumberValidity (                                         \
        vformatGetDoubleNumber (format),                                       \
        (string))

/*
 * * DOUBLE FORMAT SEGMENT MACROS
 */

#define vformatCreateDoubleSegment()                                         \
    ((vformatDoubleSegment *)                                                \
        vformatCreateNumberSegment ())

#define vformatCreateDoubleSegmentOfClass(clas)                              \
    ((vformatDoubleSegment *)                                                \
        vinstanceCreateOfClass (                                             \
            (vinstanceClass *) (clas)))

#define vformatGetDoubleSegmentBase(segment)                                 \
    ((vformatNumberSegment *) segment)

#define vformatDumpDoubleSegment(segment, stream)                            \
    vformatDumpNumberSegment (                                               \
        vformatGetDoubleSegmentBase (segment),                               \
        (stream))

#define vformatDestroyDoubleSegment(segment)                                 \
    vformatDestroyNumberSegment (                                            \
        vformatGetDoubleSegmentBase (segment))

#define vformatInitDoubleSegment(segment)                                    \
    vformatInitNumberSegment (                                               \
        vformatGetDoubleSegmentBase (segment))

#define vformatGetDoubleSegmentString(segment)                               \
    vformatGetNumberSegmentString (                                          \
        vformatGetDoubleSegmentBase (segment))

#define vformatSetDoubleSegmentString(segment, string)                       \
    vformatSetNumberSegmentString (                                          \
        vformatGetDoubleSegmentBase (segment),                               \
        (string))

#define vformatSetDoubleSegmentPrefix(segment, prefix)                       \
    vformatSetNumberSegmentPrefix (                                          \
        vformatGetDoubleSegmentBase (segment),                               \
         prefix)

#define vformatGetDoubleSegmentPrefix(segment)                               \
    vformatGetNumberSegmentPrefix (                                          \
        vformatGetDoubleSegmentBase (segment))

#define vformatSetDoubleSegmentSuffix(segment, suffix)                       \
    vformatSetNumberSegmentSuffix (                                          \
        vformatGetDoubleSegmentBase (segment),                               \
        suffix)

#define vformatGetDoubleSegmentSuffix(segment)                               \
    vformatGetNumberSegmentSuffix (                                          \
        vformatGetDoubleSegmentBase (segment))

#define vformatGetDoubleSegmentColor(segment)                                \
    vformatGetNumberSegmentColor (                                           \
        vformatGetDoubleSegmentBase (segment))

#define vformatSetDoubleSegmentColor(segment, color)                         \
    vformatSetNumberSegmentColor (                                           \
        vformatGetDoubleSegmentBase (segment),                               \
        (color))

#define vformatGetDoubleSegmentAlignment(segment)                            \
    vformatGetNumberSegmentAlignment (                                       \
        vformatGetDoubleSegmentBase (segment))

#define vformatSetDoubleSegmentAlignment(segment, alignment)                 \
    vformatSetNumberSegmentAlignment (                                       \
        vformatGetDoubleSegmentBase (segment),                               \
        (alignment))

#define vformatGetDoubleSegmentScale(segment)                                \
    vformatGetNumberSegmentScale (                                           \
        vformatGetDoubleSegmentBase (segment))

#define vformatSetDoubleSegmentScale(segment, scale)                         \
    vformatSetNumberSegmentScale (                                           \
        vformatGetDoubleSegmentBase (segment),                               \
        (scale))

#define vformatParseDoubleSegment(segment, segIndx)                          \
    vformatParseNumberSegment (                                              \
        vformatGetDoubleSegmentBase (segment),                               \
        (segIndx))

#define vformatParseDoubleSegmentPattern(segment, range)                     \
    vformatParseNumberSegmentPattern (                                       \
        vformatGetDoubleSegmentBase (segment),                               \
        (range))

/*
 * * LONG FORMAT MACROS
 */

#define vformatGetLongNumber(format)                                           \
    vportBASE_OBJECT (                                                       \
        (format),                                                            \
        number)

#define vformatGetLongBase(format)                                           \
    vformatGetNumberBase(vformatGetLongNumber(format))

#define vformatCreateLong()                                                  \
    ((vformatLong *)                                                         \
        vformatCreateOfClass (                                               \
            vformatGetDefaultLongClass ()))

#define vformatCloneLong(format)                                             \
    ((vformatLong *)                                                         \
        vformatCloneNumber (                                                 \
            vformatGetLongNumber (format)))

#define vformatInitLong(format)                                              \
    vformatInitNumber (                                                      \
        vformatGetLongNumber (format))

#define vformatCopyLong(dest, src)                                           \
    vformatCopyNumber (                                                      \
        vformatGetLongNumber (dest),                                           \
        vformatGetLongNumber (src))

#define vformatCopyInitLong(dest, src)                                       \
    vformatCopyInitNumber (                                                  \
        vformatGetLongNumber (dest),                                           \
        vformatGetLongNumber (src))

#define vformatDumpLong(format, stream)                                      \
    vformatDumpNumber (                                                      \
        vformatGetLongNumber (format),                                         \
        (stream))

#define vformatDestroyLong(format)                                           \
    vformatDestroyNumber (                                                   \
        vformatGetLongNumber (format))

#define vformatLoadLong(res)                                                 \
    ((vformatLong *)                                                         \
        vformatLoadNumber (res))

#define vformatLoadLongPatterns(format, res)                                 \
    vformatLoadNumberPatterns (                                              \
        vformatGetLongNumber (format),                                         \
        (res))

#define vformatStoreLong(format, res)                                        \
    vformatStoreNumber (                                                     \
        vformatGetLongNumber (format),                                         \
        (res))

#define vformatGetLongClass(format)                                          \
    ((vformatLongClass *)                                                    \
        vformatGetNumberClass (                                              \
            vformatGetLongNumber (format)))

#define vformatGetLongLoadable(format)                                       \
    vformatGetNumberLoadable (                                               \
        vformatGetLongNumber (format))

#define vformatSetLongOutputPatternIndex(format, index)                      \
    vformatSetNumberOutputPatternIndex (                                     \
        vformatGetLongNumber (format),                                         \
        (index))

#define vformatGetLongOutputPatternIndex(format)                             \
    vformatGetNumberOutputPatternIndex (                                     \
        vformatGetLongNumber (format))

#define vformatSetLongPatterns(format, strings, count)                       \
    vformatSetNumberPatterns (                                               \
        vformatGetLongNumber (format),                                         \
        (strings),                                                           \
        (count))

#define vformatInsertLongPatternScribed(format, scribe, index)             \
    vformatInsertNumberPatternScribed (                                    \
        vformatGetLongNumber (format),                                         \
        (scribe),                                                            \
        (index))

#define vformatInsertLongPattern(format, string, index)                    \
    vformatInsertNumberPattern (                                           \
        vformatGetLongNumber (format),                                         \
        (string),                                                            \
        (index))

#define vformatSetLongPatternIndex(format, oldIndex, newIndex)               \
    vformatSetNumberPatternIndex (                                           \
        vformatGetLongNumber (format),                                         \
        (oldIndex),                                                          \
        (newIndex))

#define vformatAppendLongPattern(format, string)                             \
    vformatAppendNumberPattern (                                             \
        vformatGetLongNumber (format),                                         \
        (string))

#define vformatDestroyLongPatternAt(format, index)                           \
    vformatDestroyNumberPatternAt (                                          \
        vformatGetLongNumber (format),                                         \
        (index))

#define vformatGetLongPatternCount(format)                                   \
    vformatGetNumberPatternCount (                                           \
        vformatGetLongNumber (format))

#define vformatGetLongSegmentCount(format)                                   \
    vformatGetNumberSegmentCount (                                           \
        vformatGetLongNumber (format))

#define vformatGetLongPatternSegmentAt(f, pi, si)                            \
    ((const vformatLongSegment *)                                            \
        vformatGetNumberPatternSegmentAt (                                   \
            vformatGetLongNumber (f),                                          \
            (pi),                                                            \
            (si)))

#define vformatIsLongValid(format, string)                                   \
    vformatIsNumberValid (                                                   \
        vformatGetLongNumber (format),                                         \
        (string))

#define vformatIsLongPartiallyValid(format, string)                          \
    vformatIsNumberPartiallyValid (                                          \
        vformatGetLongNumber (format),                                         \
        (string))

#define vformatDetermineLongValidity(format, string)                         \
    vformatDetermineNumberValidity (                                         \
        vformatGetLongNumber (format),                                         \
        (string))

#define vformatParseLong(format, string)                                     \
    vclassSend (                                                             \
        vformatGetLongClass (format),                                        \
        vformatPARSE_LONG,                                                   \
        (format, string))

#define vformatScribeLong(format, value)                                     \
    vclassSend (                                                             \
        vformatGetLongClass (format),                                        \
        vformatSCRIBE_LONG,                                                  \
        (format, value))

/*
 * * LONG FORMAT SEGMENT MACROS
 */

#define vformatCreateLongSegment()                                           \
    ((vformatLongSegment *)                                                  \
        vformatCreateNumberSegment ())

#define vformatCreateLongSegmentOfClass(clas)                                \
    ((vformatLongSegment *)                                                  \
        vinstanceCreateOfClass (                                             \
            (vinstanceClass *) (clas)))

#define vformatGetLongSegmentBase(segment)                                   \
    ((vformatNumberSegment *) segment)

#define vformatDumpLongSegment(segment, stream)                              \
    vformatDumpNumberSegment (                                               \
        vformatGetLongSegmentBase (segment),                                 \
        (stream))

#define vformatDestroyLongSegment(segment)                                   \
    vformatDestroyNumberSegment (                                            \
        vformatGetLongSegmentBase (segment))

#define vformatInitLongSegment(segment)                                      \
    vformatInitNumberSegment (                                               \
        vformatGetLongSegmentBase (segment))

#define vformatGetLongSegmentString(segment)                                 \
    vformatGetNumberSegmentString (                                          \
        vformatGetLongSegmentBase (segment))

#define vformatSetLongSegmentString(segment, string)                         \
    vformatSetNumberSegmentString (                                          \
        vformatGetLongSegmentBase (segment),                                 \
        (string))

#define vformatSetLongSegmentPrefix(segment, prefix)                         \
    vformatSetNumberSegmentPrefix (                                          \
        vformatGetLongSegmentBase (segment),                                 \
         prefix)

#define vformatGetLongSegmentPrefix(segment)                                 \
    vformatGetNumberSegmentPrefix (                                          \
        vformatGetLongSegmentBase (segment))

#define vformatSetLongSegmentSuffix(segment, suffix)                         \
    vformatSetNumberSegmentSuffix (                                          \
        vformatGetLongSegmentBase (segment),                                 \
        suffix)

#define vformatGetLongSegmentSuffix(segment)                                 \
    vformatGetNumberSegmentSuffix (                                          \
        vformatGetLongSegmentBase (segment))

#define vformatGetLongSegmentColor(segment)                                  \
    vformatGetNumberSegmentColor (                                           \
        vformatGetLongSegmentBase (segment))

#define vformatSetLongSegmentColor(segment, color)                           \
    vformatSetNumberSegmentColor (                                           \
        vformatGetLongSegmentBase (segment),                                 \
        (color))

#define vformatGetLongSegmentAlignment(segment)                              \
    vformatGetNumberSegmentAlignment (                                       \
        vformatGetLongSegmentBase (segment))

#define vformatSetLongSegmentAlignment(segment, alignment)                   \
    vformatSetNumberSegmentAlignment (                                       \
        vformatGetLongSegmentBase (segment),                                 \
        (alignment))

#define vformatGetLongSegmentScale(segment)                                  \
    vformatGetNumberSegmentScale (                                           \
        vformatGetLongSegmentBase (segment))

#define vformatSetLongSegmentScale(segment, scale)                           \
    vformatSetNumberSegmentScale (                                           \
        vformatGetLongSegmentBase (segment),                                 \
        (scale))

#define vformatParseLongSegment(segment, segIndx)                            \
    vformatParseNumberSegment (                                              \
        vformatGetLongSegmentBase (segment),                                 \
        (segIndx))

#define vformatParseLongSegmentPattern(segment, range)                       \
    vformatParseNumberSegmentPattern (                                       \
        vformatGetLongSegmentBase (segment),                                 \
        (range))

/*
 * * UNSIGNED LONG FORMAT MACROS
 */

#define vformatGetULongNumber(format)                                          \
    vportBASE_OBJECT (                                                       \
        (format),                                                            \
        number)

#define vformatGetULongBase(format)                                           \
    vformatGetNumberBase(vformatGetULongNumber(format))

#define vformatCreateULong()                                                 \
    ((vformatULong *)                                                        \
        vformatCreateOfClass (                                               \
            vformatGetDefaultULongClass ()))

#define vformatCloneULong(format)                                            \
    ((vformatULong *)                                                        \
        vformatCloneNumber (                                                 \
            vformatGetULongNumber (format)))

#define vformatInitULong(format)                                             \
    vformatInitNumber (                                                      \
        vformatGetULongNumber (format))

#define vformatCopyULong(dest, src)                                          \
    vformatCopyNumber (                                                      \
        vformatGetULongNumber (dest),                                          \
        vformatGetULongNumber (src))

#define vformatCopyInitULong(dest, src)                                      \
    vformatCopyInitNumber (                                                  \
        vformatGetULongNumber (dest),                                          \
        vformatGetULongNumber (src))

#define vformatDumpULong(format, stream)                                     \
    vformatDumpNumber (                                                      \
        vformatGetULongNumber (format),                                        \
        stream)

#define vformatDestroyULong(format)                                          \
    vformatDestroyNumber (                                                   \
        vformatGetULongNumber (format))

#define vformatLoadULong(res)                                                \
    ((vformatULong *)                                                        \
        vformatLoadNumber (res))

#define vformatLoadULongPatterns(format, res)                                \
    vformatLoadNumberPatterns (                                              \
        vformatGetULongNumber (format),                                        \
        res)

#define vformatStoreULong(format, res)                                       \
    vformatStoreNumber (                                                     \
        vformatGetULongNumber (format),                                        \
        res)

#define vformatGetULongClass(format)                                         \
    ((vformatULongClass *)                                                   \
        vformatGetNumberClass (                                              \
            vformatGetULongNumber (format)))

#define vformatGetULongLoadable(format)                                      \
    vformatGetNumberLoadable (                                               \
        vformatGetULongNumber (format))

#define vformatSetULongOutputPatternIndex(format, index)                     \
    vformatSetNumberOutputPatternIndex (                                     \
        vformatGetULongNumber (format),                                        \
        index)

#define vformatGetULongOutputPatternIndex(format)                            \
    vformatGetNumberOutputPatternIndex (                                     \
        vformatGetULongNumber (format))

#define vformatSetULongPatterns(format, strings, count)                      \
    vformatSetNumberPatterns (                                               \
        vformatGetULongNumber (format),                                        \
        strings,                                                             \
        count)

#define vformatInsertULongPatternScribed(format, scribe, index)            \
    vformatInsertNumberPatternScribed (                                    \
        vformatGetULongNumber (format),                                        \
        scribe,                                                              \
        index)

#define vformatInsertULongPattern(format, string, index)                   \
    vformatInsertNumberPattern (                                           \
        vformatGetULongNumber (format),                                        \
        string,                                                              \
        index)

#define vformatSetULongPatternIndex(format, oldIndex, newIndex)              \
    vformatSetNumberPatternIndex (                                           \
        vformatGetULongNumber (format),                                        \
        oldIndex,                                                            \
        newIndex)

#define vformatAppendULongPattern(format, string)                            \
    vformatAppendNumberPattern (                                             \
        vformatGetULongNumber (format),                                        \
        string)

#define vformatDestroyULongPatternAt(format, index)                          \
    vformatDestroyNumberPatternAt (                                          \
        vformatGetULongNumber (format),                                        \
        index)

#define vformatGetULongPatternCount(format)                                  \
    vformatGetNumberPatternCount (                                           \
        vformatGetULongNumber (format))

#define vformatGetULongSegmentCount(format)                                  \
    vformatGetNumberSegmentCount (                                           \
        vformatGetULongNumber (format))

#define vformatGetULongPatternSegmentAt(f, pi, si)                           \
    ((const vformatULongSegment *)                                           \
        vformatGetNumberPatternSegmentAt (                                   \
            vformatGetULongNumber (f),                                         \
            (pi),                                                            \
            (si)))

#define vformatIsULongValid(format, string)                                  \
    vformatIsNumberValid (                                                   \
        vformatGetULongNumber (format),                                        \
        string)

#define vformatIsULongPartiallyValid(format, string)                         \
    vformatIsNumberPartiallyValid (                                          \
        vformatGetULongNumber (format),                                        \
        string)

#define vformatDetermineULongValidity(format, string)                        \
    vformatDetermineNumberValidity (                                         \
        vformatGetULongNumber (format),                                        \
        (string))

#define vformatParseULong(format, string)                                    \
    vclassSend (                                                             \
        vformatGetULongClass (format),                                       \
        vformatPARSE_ULONG,                                                  \
        (format, string))

#define vformatScribeULong(format, value)                                    \
    vclassSend (                                                             \
        vformatGetULongClass (format),                                       \
        vformatSCRIBE_ULONG,                                                 \
        (format, value))

/*
 * * UNSIGNED LONG FORMAT SEGMENT MACROS
 */

#define vformatCreateULongSegment()                                          \
    ((vformatULongSegment *)                                                 \
        vformatCreateNumberSegment ())

#define vformatCreateULongSegmentOfClass(clas)                               \
    ((vformatULongSegment *)                                                 \
        vinstanceCreateOfClass (                                             \
            (vinstanceClass *) (clas)))

#define vformatGetULongSegmentBase(segment)                                  \
    ((vformatNumberSegment *) segment)

#define vformatDumpULongSegment(segment, stream)                             \
    vformatDumpNumberSegment (                                               \
        vformatGetULongSegmentBase (segment),                                \
        (stream))

#define vformatDestroyULongSegment(segment)                                  \
    vformatDestroyNumberSegment (                                            \
        vformatGetULongSegmentBase (segment))

#define vformatInitULongSegment(segment)                                     \
    vformatInitNumberSegment (                                               \
        vformatGetULongSegmentBase (segment))

#define vformatGetULongSegmentString(segment)                                \
    vformatGetNumberSegmentString (                                          \
        vformatGetULongSegmentBase (segment))

#define vformatSetULongSegmentString(segment, string)                        \
    vformatSetNumberSegmentString (                                          \
        vformatGetULongSegmentBase (segment),                                \
        (string))

#define vformatSetULongSegmentPrefix(segment, prefix)                        \
    vformatSetNumberSegmentPrefix (                                          \
        vformatGetULongSegmentBase (segment),                                \
         prefix)

#define vformatGetULongSegmentPrefix(segment)                                \
    vformatGetNumberSegmentPrefix (                                          \
        vformatGetULongSegmentBase (segment))

#define vformatSetULongSegmentSuffix(segment, suffix)                        \
    vformatSetNumberSegmentSuffix (                                          \
        vformatGetULongSegmentBase (segment),                                \
        suffix)

#define vformatGetULongSegmentSuffix(segment)                                \
    vformatGetNumberSegmentSuffix (                                          \
        vformatGetULongSegmentBase (segment))

#define vformatGetULongSegmentColor(segment)                                 \
    vformatGetNumberSegmentColor (                                           \
        vformatGetULongSegmentBase (segment))

#define vformatSetULongSegmentColor(segment, color)                          \
    vformatSetNumberSegmentColor (                                           \
        vformatGetULongSegmentBase (segment),                                \
        (color))

#define vformatGetULongSegmentAlignment(segment)                             \
    vformatGetNumberSegmentAlignment (                                       \
        vformatGetULongSegmentBase (segment))

#define vformatSetULongSegmentAlignment(segment, alignment)                  \
    vformatSetNumberSegmentAlignment (                                       \
        vformatGetULongSegmentBase (segment),                                \
        (alignment))

#define vformatGetULongSegmentScale(segment)                                 \
    vformatGetNumberSegmentScale (                                           \
        vformatGetULongSegmentBase (segment))

#define vformatSetULongSegmentScale(segment, scale)                          \
    vformatSetNumberSegmentScale (                                           \
        vformatGetULongSegmentBase (segment),                                \
        (scale))

#define vformatParseULongSegment(segment, segIndx)                           \
    vformatParseNumberSegment (                                              \
        vformatGetULongSegmentBase (segment),                                \
        (segIndx))

#define vformatParseULongSegmentPattern(segment, range)                      \
    vformatParseNumberSegmentPattern (                                       \
        vformatGetULongSegmentBase (segment),                                \
        (range))

/*
 * * DATE FORMAT MACROS
 */

#define vformatGetDateBase(_format)                                          \
    vportBASE_OBJECT (                                                       \
        (_format),                                                           \
        format)

#define vformatCreateDate()                                                  \
    ((vformatDate *)                                                         \
        vformatCreateOfClass (                                               \
            vformatGetDefaultDateClass ()))

#define vformatCloneDate(format)                                             \
    ((vformatDate *)                                                         \
        vformatClone (                                                       \
            vformatGetDateBase (format)))

#define vformatInitDate(format)                                              \
    vformatInit (                                                            \
        vformatGetDateBase (format))

#define vformatCopyDate(dest, src)                                           \
    vformatCopy (                                                            \
        vformatGetDateBase (dest),                                           \
        vformatGetDateBase (src))

#define vformatCopyInitDate(dest, src)                                       \
    vformatCopyInit (                                                        \
        vformatGetDateBase (dest),                                           \
        vformatGetDateBase (src))

#define vformatDumpDate(format, stream)                                      \
    vformatDump (                                                            \
        vformatGetDateBase (format),                                         \
        stream)

#define vformatDestroyDate(format)                                           \
    vformatDestroy (                                                         \
        vformatGetDateBase (format))

#define vformatLoadDate(res)                                                 \
    ((vformatDate *)                                                         \
        vformatLoad (res))

#define vformatLoadDatePatterns(format, res)                                 \
    vformatLoadPatterns (                                                    \
        vformatGetDateBase (format),                                         \
        res)

#define vformatStoreDate(format, res)                                        \
    vformatStore (                                                           \
        vformatGetDateBase (format),                                         \
        res)

#define vformatGetDateClass(format)                                          \
    ((vformatDateClass *)                                                    \
        vformatGetClass (                                                    \
            vformatGetDateBase (format)))

#define vformatGetDateLoadable(format)                                       \
    vformatGetLoadable (                                                     \
        vformatGetDateBase (format))

#define vformatGetDateOutputPatternIndex(format)                             \
    vformatGetOutputPatternIndex (                                           \
        vformatGetDateBase (format))

#define vformatGetDateOutputSegmentIndex(f, d)                               \
    (0)

#define vformatSetDateOutputPatternIndex(format, index)                      \
    vformatSetOutputPatternIndex (                                           \
        vformatGetDateBase (format),                                         \
        index)

#define vformatSetDatePatterns(format, strings, count)                       \
    vformatSetPatterns (                                                     \
        vformatGetDateBase (format),                                         \
        strings,                                                             \
        count)

#define vformatInsertDatePatternScribed(format, scribe, index)             \
    vformatInsertPatternScribed (                                          \
        vformatGetDateBase (format),                                         \
        scribe,                                                              \
        index)

#define vformatInsertDatePattern(format, string, index)                    \
    vformatInsertPattern (                                                 \
        vformatGetDateBase (format),                                         \
        string,                                                              \
        index)

#define vformatSetDatePatternIndex(format, oldIndex, newIndex)               \
    vformatSetPatternIndex (                                                 \
        vformatGetDateBase (format),                                         \
        oldIndex,                                                            \
        newIndex)

#define vformatAppendDatePattern(format, string)                             \
    vformatAppendPattern (                                                   \
        vformatGetDateBase (format),                                         \
        string)

#define vformatDestroyDatePatternAt(format, index)                           \
    vformatDestroyPatternAt (                                                \
        vformatGetDateBase (format),                                         \
        index)

#define vformatGetDatePatternCount(format)                                   \
    vformatGetPatternCount (                                                 \
        vformatGetDateBase (format))

#define vformatGetDateSegmentCount(format)                                   \
    vclassSend (                                                             \
        vformatGetDateClass (format),                                        \
        vformatGET_SEGMENT_COUNT)

#define vformatGetDatePatternSegmentAt(f, pi, si)                            \
    ((const vformatDateSegment *)                                            \
        vformatGetPatternSegmentAt (                                         \
            vformatGetDateBase (f),                                          \
            (pi),                                                            \
            (si)))

#define vformatScribeDate(format, value)                                     \
    vclassSend (                                                             \
        vformatGetDateClass (format),                                        \
        vformatSCRIBE_DATE,                                                  \
        (format, value))

#define vformatParseDate(format, string)                                     \
    vclassSend (                                                             \
        vformatGetDateClass (format),                                        \
        vformatPARSE_DATE,                                                   \
        (format, string))

#define vformatIsDateValid(format, string)                                   \
    vformatIsValid (                                                         \
        vformatGetDateBase (format),                                         \
        string)

#define vformatIsDatePartiallyValid(format, string)                          \
    vformatIsPartiallyValid (                                                \
        vformatGetDateBase (format),                                         \
        string)

#define vformatDetermineDateValidity(format, string)                         \
    vformatDetermineValidity (                                               \
        vformatGetDateBase (format),                                         \
        (string))

/*
 * * DATE FORMAT SEGMENT MACROS
 */

#define vformatCreateDateSegment()                                           \
    ((vformatDateSegment *)                                                  \
        vinstanceCreateOfClass (                                             \
            vformatGetDefaultDateSegmentClass ()))

#define vformatCreateDateSegmentOfClass(clas)                                \
    ((vformatDateSegment *)                                                  \
        vinstanceCreateOfClass (                                             \
            (vinstanceClass *) (clas)))

#define vformatGetDateSegmentBase(_segment)                                  \
    vportBASE_OBJECT (                                                       \
        (_segment),                                                          \
        segment)
    
#define vformatGetDateSegmentInstance(segment)                               \
    vformatGetSegmentInstance (                                              \
        vformatGetDateSegmentBase (segment)) 

#define vformatDumpDateSegment(segment, stream)                              \
    vformatDumpSegment (                                                     \
        vformatGetDateSegmentBase (segment),                                 \
        stream)

#define vformatDestroyDateSegment(segment)                                   \
    vformatDestroySegment (                                                  \
        vformatGetDateSegmentBase (segment))

#define vformatInitDateSegment(segment)                                      \
    vformatInitSegment (                                                     \
        vformatGetDateSegmentBase (segment))

#define vformatGetDateSegmentString(segment)                                 \
    vformatGetSegmentString (                                                \
        vformatGetDateSegmentBase (segment))

#define vformatSetDateSegmentString(segment)                                 \
    vformatSetSegmentString (                                                \
        vformatGetDateSegmentBase (segment))

#define vformatGetDateSegmentColor(segment)                                  \
    vformatGetSegmentColor (                                                 \
        vformatGetDateSegmentBase (segment))

#define vformatGetDateSegmentAlignment(segment)                              \
    vformatGetSegmentAlignment (                                             \
        vformatGetDateSegmentBase (segment))

#define vformatGetDateSegmentFormat(segment)                                 \
    ((segment)->format)

#define vformatParseDateSegment(segment, segIndx)                            \
    vformatParseSegment (                                                    \
        vformatGetDateSegmentBase (segment),                                 \
        segIndx)

#define vformatParseDateSegmentPattern(segment, range)                       \
    vformatParseSegmentPattern (                                             \
        vformatGetDateSegmentBase (segment),                                 \
        (range))

vportEND_CPLUSPLUS_EXTERN_C

#endif /* vformatINCLUDED */


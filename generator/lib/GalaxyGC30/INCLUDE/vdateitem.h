/* $Id: vdateitem.h,v 1.16 1997/06/27 01:50:05 robert Exp $ */

/* vdateitem - a date input item */

#ifndef vdateitemINCLUDED
#define vdateitemINCLUDED 1

#ifndef vportINCLUDED
#include <vport.h>
#endif

#ifndef vstdINCLUDED
#include vstdHEADER
#endif

#ifndef veventINCLUDED
#include veventHEADER
#endif

#ifndef vdictHEADER
#include vdictHEADER
#endif

#ifndef vformatINCLUDED
#include vformatHEADER
#endif

#ifndef vdateINCLUDED
#include vdateHEADER
#endif

#ifndef vtimestampINCLUDED
#include vtimestampHEADER
#endif

#ifndef vtypeditemINCLUDED
#include vtypeditemHEADER
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * * * * * * * * * TYPE AND STRUCTURE DEFINITIONS * * * * * * * * * *
 */

/*
 * * DATE ITEM FORWARD DECLARATION
 */
typedef struct vdateitem
               vdateitem;

typedef struct vdateitemClass
               vdateitemClass;

typedef vtypeditemText
        vdateitemText;

typedef vtypeditemTextClass
        vdateitemTextClass;


/*
 * * CLIENT NOTIFICATION PROCEDURE PROTOTYPE
 */
typedef void (*vdateitemNoteProc) (
    vdateitem *item,
    int        msg
);

/*
 * * CLIENT VALIDATION PROCEDURE PROTOTYPE
 */
typedef vbool (*vdateitemValidatorProc) (
    vdateitem *item
);

/*
 * * INCREMENT CODES
 */
enum
{
    vdateitemUP = vtypeditemUP,
    vdateitemDOWN,
    vdateitemNO_DIRECTION
};

/*
 * * NOTIFICATION CODES
 */
enum
{
    vdateitemNOTIFY_FOCUS = vtypeditemNOTIFY_FOCUS,
    vdateitemNOTIFY_UNFOCUS,
    vdateitemNOTIFY_VALID,
    vdateitemNOTIFY_PARTIALLY_VALID,
    vdateitemNOTIFY_INVALID,
    vdateitemNOTIFY_NEXT
};

/*
 * * SELECTOR COMMAND DISCRIMINATORS
 */
enum
{
    vdateitemSELECT_SECONDS = vtypeditemNEXT_SELECT,
    vdateitemSELECT_MINUTES,
    vdateitemSELECT_HOURS,
    vdateitemSELECT_DAYS,
    vdateitemSELECT_WEEKS,
    vdateitemSELECT_MONTHS,
    vdateitemSELECT_YEARS,
    vdateitemSELECT_INCREMENT,
    vdateitemSELECT_SET_CURRENT,
    vdateitemNEXT_SELECT
};


/*
 * * DATE ITEM INSTANCE DEFINITION
 */
struct vdateitem
{
    vtypeditem     base_object;
    vdate          value;
    unsigned long  flags;
    vdict         *incrementInfo;
};


/*
 * * DATE ITEM CLASS DEFINITION
 */
#define vdateitemCLASS(SUPER, ITEM, NOTIFY, VALIDATOR_PROC)                  \
                                                                             \
    vtypeditemCLASS (SUPER, ITEM, NOTIFY, VALIDATOR_PROC);                   \
                                                                             \
    vclassMETHOD_RET (vdateitemGET_VALUE, const vdate *,                     \
        (ITEM *item));                                                       \
    vclassMETHOD     (vdateitemSET_VALUE,                                    \
        (ITEM *item, const vdate *value))                                    \

struct vdateitemClass
{
    vdateitemCLASS (
        vdateitemClass,
        vdateitem,
        vdateitemNoteProc,
        vdateitemValidatorProc);
};

/*
 * * * * * * * * * DATE ITEM FUNCTION PROTOTYPES * * * * * * * * * *
 */

void
vdateitemStartup (
    void
);

vdateitemClass *
vdateitemGetDefaultClass (
    void
);

vdateitem *
vdateitemCreate (
    void
);

vdateitem *
vdateitemCreateOfClass (
    vdateitemClass *clas
);

vtypeditem *
vdateitemGetTypeditem (
    vdateitem *item
);

vobject *
vdateitemGetObject (
    vdateitem *item
);

vdialogItem *
vdateitemGetItem (
    vdateitem *item
);

vdateitem *
vdateitemClone (
    vdateitem *item
);

void
vdateitemCopy (
    vdateitem *src,
    vdateitem *dest
);

void
vdateitemCopyInit (
    vdateitem *src,
    vdateitem *dest
);

void
vdateitemInit (
    vdateitem *item
);

void
vdateitemInitOfClass (
    vdateitem		*item,
    vdateitemClass	*clas
);

void
vdateitemDump (
    vdateitem *item,
    FILE      *stream
);

void
vdateitemDestroy (
    vdateitem *item
);

vdateitem *
vdateitemLoad (
    vresource resource
);

void
vdateitemLoadInit (
    vdateitem *item,
    vresource  resource
);

void
vdateitemStore (
    vdateitem *item,
    vresource  resource
);

void
vdateitemSetData (
    vdateitem *item,
    void      *data
);

vdateitemClass *
vdateitemGetClass (
    vdateitem *item
);

void *
vdateitemGetData (
    vdateitem *item
);

vdateitemNoteProc
vdateitemGetNotify (
    vdateitem *item
);

void
vdateitemSetNotify (
    vdateitem         *item,
    vdateitemNoteProc  notify
);

void
vdateitemNotify (
    vdateitem *item,
    int        msg
);

vdateitemValidatorProc
vdateitemGetValidator (
    vdateitem *item
);

void
vdateitemSetValidator (
    vdateitem              *item,
    vdateitemValidatorProc  validatorProc
);

void
vdateitemSetTextData (
    vdateitem *item,
    vtext     *text
);

vobservable *
vdateitemGetField (
    vdateitem *item
);

void
vdateitemSetField (
    vdateitem *item,
    vobservable *field
);

void
vdateitemSetObserving (
    vdateitem *item,
    vbool      isObserving
);

vbool
vdateitemIsObserving (
    vdateitem *item
);

void
vdateitemSetString (
    vdateitem	*item,
    const vchar *text
);

vstr *
vdateitemGetTransientString (
    vdateitem *item
);

vscribe *
vdateitemGetTransientStringScribed (
    vdateitem *item
);

int
vdateitemGetLength (
    vdateitem *item
);

void
vdateitemSetStringScribed (
    vdateitem *item,
    vscribe   *scribe
);

void
vdateitemInsertString (
    vdateitem *item,
    long       selStart,
    long       selLength,
    vchar     *s,
    long       len
);

void
vdateitemDeleteString (
    vdateitem *item,
    long       selStart,
    long       selLength
);

void
vdateitemSelectRange (
    vdateitem *item, 
    long       begin,
    long       len
);

vstr *
vdateitemGetString (
    vdateitem *item
);

vscribe *
vdateitemGetStringScribed (
    vdateitem *item
);

vscribe *
vdateitemGetSubstrScribed (
    vdateitem *item,
    long       begin,
    long       len
);

vscribe *
vdateitemGetSelectionScribed (
    vdateitem *item
);

vdateitemText *
vdateitemCreateTextData (
    vdateitem *item
);

void
vdateitemSetForeground (
    vdateitem *item,
    vcolor    *fg
);

vcolor *
vdateitemGetForeground (
    vdateitem *item
);

void
vdateitemSetJustification (
    vdateitem *item,
    int        justification
);

int
vdateitemGetJustification (
    vdateitem *item
);

vbool
vdateitemIsValid (
    vdateitem *item
);

void
vdateitemSetDirty (
    vdateitem *item,
    vbool      dirty
);

vbool
vdateitemIsDirty (
    vdateitem *item
);

void
vdateitemSync (
    vdateitem *item
);

void
vdateitemSetFormat (
    vdateitem   *item,
    vformatDate *format
);

void
vdateitemSetFormatOwned (
    vdateitem   *item,
    vformatDate *format
);

vformatDate *
vdateitemGetFormat (
    vdateitem *item
);

const vdate *
vdateitemGetValue (
    vdateitem *item
);

void
vdateitemSetValue (
    vdateitem   *item,
    const vdate *value
);

void
vdateitemIncrement (
    vdateitem *item,
    int        dir
);

void
vdateitemAddSeconds (
    vdateitem *item,
    int        seconds
);

void
vdateitemAddMinutes (
    vdateitem *item,
    int        minutes
);

void
vdateitemAddHours (
    vdateitem *item,
    int        hours
);

void
vdateitemAddDays (
    vdateitem *item,
    int        days
);

void
vdateitemAddWeeks (
    vdateitem *item,
    int        weeks
);

void
vdateitemAddMonths (
    vdateitem *item,
    int        months
);

void
vdateitemAddYears (
    vdateitem *item,
    int        years
);

void
vdateitemSetCurrent (
    vdateitem *item
);

vbool
vdateitemHasBeepIfInvalid (
    vdateitem *item
);

void
vdateitemSetBeepIfInvalid (
    vdateitem *item,
    vbool      flag
);

vbool
vdateitemHasKeepFocusIfInvalid (
    vdateitem *item
);

void
vdateitemSetKeepFocusIfInvalid (
    vdateitem *item,
    vbool      flag
);

vbool
vdateitemHasNeverInvalid (
    vdateitem *item
);

void
vdateitemSetNeverInvalid (
    vdateitem *item,
    vbool      flag
);

vbool
vdateitemHasValidateOnChange (
    vdateitem *item
);

void
vdateitemSetValidateOnChange (
    vdateitem *item,
    vbool      flag
);

vbool
vdateitemIsNull (
    vdateitem *item
);

void
vdateitemSetNull (
    vdateitem *item,
    vbool      isNull
);

void
vdateitemSetEmptyIsNull (
    vdateitem *item,
    vbool      emptyIsNull
);

vbool
vdateitemHasEmptyIsNull (
    vdateitem *item
);

void
vdateitemSetInformingField (
    vdateitem *item,
    vbool      informing
);

vbool
vdateitemIsInformingField (
    vdateitem *item
);

/*
 * * * * * * * * * * PRIVATE MACRO DEFINITIONS * * * * * * * * * *
 */

#define vdateitemGetTypeditem(f)                                             \
    vportBASE_OBJECT (                                                       \
        (f),                                                                 \
        base_object)

#define vdateitemGetObject(f)                                                \
    vtypeditemGetObject (                                                    \
        vdateitemGetTypeditem (f))

#define vdateitemGetItem(f)                                                  \
    vtypeditemGetItem (                                                      \
        vdateitemGetTypeditem (f))

#define vdateitemCreateOfClass(c)                                            \
	((vdateitem *)                                                           \
        vtypeditemCreateOfClass (                                            \
            (vtypeditemClass *) (c)))

#define vdateitemClone(f)                                                    \
	((vdateitem *)                                                           \
        vtypeditemClone (                                                    \
            vdateitemGetTypeditem(f)))

#define vdateitemInitOfClass(f, c)                                           \
	vtypeditemInitOfClass (                                                  \
        vdateitemGetTypeditem (f),                                           \
        (vdateitemClass *) (c))

#define vdateitemInit(f)                                                     \
    vdateitemInitOfClass (                                                   \
        (f),                                                                 \
        vdateitemGetDefaultClass ());

#define vdateitemCopyInit(f, t)                                              \
    vtypeditemCopyInit (                                                     \
        vdateitemGetTypeditem (f),                                           \
        vdateitemGetTypeditem (t))

#define vdateitemLoad(r)                                                     \
    ((vdateitem *)                                                           \
        vtypeditemLoad (                                                     \
            vdateitemGetTypeditem (r)))

#define vdateitemLoadInit(f, r)                                              \
    vtypeditemLoadInit (                                                     \
        vdateitemGetTypeditem (f),                                           \
        (r))

#define vdateitemDump(f, s)                                                  \
    vtypeditemDump (                                                         \
        vdateitemGetTypeditem (f),                                           \
        (s))

#define vdateitemDestroy(f)                                                  \
    vtypeditemDestroy (                                                      \
        vdateitemGetTypeditem (f))

#define vdateitemGetClass(f)                                                 \
	((vdateitemClass *)                                                      \
        vtypeditemGetClass (                                                 \
            vdateitemGetTypeditem (f)))

#define vdateitemCopy(f, t)                                                  \
    vclassSend (                                                             \
        vdateitemGetClass (f),                                               \
        vobjectCOPY,                                                         \
        (f, t))

#define vdateitemStore(f, t)                                                 \
    vclassSend (                                                             \
        vdateitemGetClass (f),                                               \
        vobjectSTORE,                                                        \
        (f, t))

#define vdateitemGetNotify(f)                                                \
    ((vdateitemNoteProc)                                                     \
        vtypeditemGetNotify (                                                \
            vdateitemGetTypeditem (f))

#define vdateitemSetNotify(f, n)                                             \
    vtypeditemSetNotify (                                                    \
        vdateitemGetTypeditem (f),                                           \
        (vtypeditemNoteProc) (n))

#define vdateitemNotify(d, m)                                                \
    vtypeditemNotify (                                                       \
        vdateitemGetTypeditem (d),                                           \
        (m))

#define vdateitemGetField(i)                                                 \
    vtypeditemGetField (                                                     \
        vdateitemGetTypeditem (i))

#define vdateitemSetField(i, f)                                              \
    vtypeditemSetField (                                                     \
        vdateitemGetTypeditem (i),                                           \
        (f))

#define vdateitemSetObserving(i, o)                                          \
    vtypeditemSetObserving (                                                 \
        vdateitemGetTypeditem (i),                                           \
        (o))

#define vdateitemIsObserving(i)                                              \
    vtypeditemIsObserving (                                                  \
        vdateitemGetTypeditem (i))

#define vdateitemGetValidator(f)                                             \
    ((vdateitemValidatorProc)                                                \
        vtypeditemGetValidator (                                             \
            vdateitemGetTypeditem (f)))

#define vdateitemSetValidator(f, p)                                          \
    vtypeditemSetValidator (                                                 \
        vdateitemGetTypeditem (f),                                           \
        (vtypeditemValidatorProc) (p))

#define vdateitemSetData(f, d)                                               \
    vtypeditemSetData (                                                      \
        vdateitemGetTypeditem (f),                                           \
        (d))

#define vdateitemGetData(f)                                                  \
    vtypeditemGetData (                                                      \
        vdateitemGetTypeditem (f))

#define vdateitemSetString(f, s)                                             \
    vtypeditemSetString (                                                    \
        vdateitemGetTypeditem (f),                                           \
        (s))

#define vdateitemGetTransientString(f)                                       \
    vtypeditemGetTransientString (                                           \
        vdateitemGetTypeditem (f))

#define vdateitemGetTransientStringScribed(f)                                \
    vtypeditemGetTransientStringScribed (                                    \
        vdateitemGetTypeditem (f))

#define vdateitemGetLength(f)                                                \
    vtypeditemGetLength (                                                    \
        vdateitemGetTypeditem (f))

#define vdateitemSetStringScribed(f, s)                                      \
    vtypeditemSetStringScribed (                                             \
        vdateitemGetTypeditem (f),                                           \
        (s))

#define dateitemInsertString(f, start, len, str, strLen)                     \
    vtypeditemInsertString (                                                 \
        vdateitemGetTypeditem (f),                                           \
        (start),                                                             \
        (len),                                                               \
        (str),                                                               \
        (strLen))

#define vdateitemDeleteString(f, start, len)                                 \
    vtypeditemDeleteString (                                                 \
        vdateitemGetTypeditem (f),                                           \
        (start),                                                             \
        (len))

#define vdateitemCreateTextData(f)                                           \
    vtypeditemCreateTextData (                                               \
        vdateitemGetTypeditem (f))

#define vdateitemSelectRange(f, b, l)                                        \
    vtypeditemSelectRange (                                                  \
        vdateitemGetTypeditem (f),                                           \
        (b),                                                                 \
        (l))

#define vdateitemGetString(f)                                                \
    vtypeditemGetString (                                                    \
        vdateitemGetTypeditem (f))

#define vdateitemGetStringScribed(f)                                         \
    vtypeditemGetStringScribed (                                             \
        vdateitemGetTypeditem (f))

#define vdateitemGetSubstrScribed(f, b, l)                                   \
    vtypeditemGetSubstrScribed (                                             \
        vdateitemGetTypeditem (f),                                           \
        (b),                                                                 \
        (l))

#define vdateitemSetForeground(i, c)                                         \
    vtypeditemSetForeground (                                                \
        vdateitemGetTypeditem (i),                                           \
        (c))

#define vdateitemGetForeground(i)                                            \
    vtypeditemGetForeground (                                                \
        vdateitemGetTypeditem (i))

#define vdateitemSetJustification(f, j)                                      \
    vtypeditemSetJustification (                                             \
        vdateitemGetTypeditem (f),                                           \
        (j))

#define vdateitemGetJustification(f)                                         \
    vtypeditemGetJustification (                                             \
        vdateitemGetTypeditem (f))

#define vdateitemIsValid(f)                                                  \
    vtypeditemIsValid (                                                      \
        vdateitemGetTypeditem (f))

#define vdateitemSetDirty(f, d)                                              \
    vtypeditemSetDirty (                                                     \
        vdateitemGetTypeditem (f),                                           \
        (d))

#define vdateitemIsDirty(f)                                                  \
    vtypeditemIsDirty (                                                      \
        vdateitemGetTypeditem (f))

#define vdateitemSetFormat(f, p)                                             \
    vtypeditemSetFormat (                                                    \
        vdateitemGetTypeditem (f),                                           \
        (vformat *) (p))

#define vdateitemSetFormatOwned(f, p)                                        \
    vtypeditemSetFormatOwned (                                               \
        vdateitemGetTypeditem (f),                                           \
        (vformat *) (p))

#define vdateitemGetFormat(f)                                                \
    ((vformatDate *)                                                         \
        vtypeditemGetFormat (                                                \
            vdateitemGetTypeditem (f)))

#define vdateitemGetValue(f)                                                 \
    vclassSend (                                                             \
        vdateitemGetClass (f),                                               \
        vdateitemGET_VALUE,                                                  \
        (f))

#define vdateitemSetValue(f, v)                                              \
    vclassSend (                                                             \
        vdateitemGetClass (f),                                               \
        vdateitemSET_VALUE,                                                  \
        (f, v))

#define vdateitemIncrement(f)                                                \
    vtypeditemIncrement (                                                    \
        vdateitemGetClass (f))

#define vdateitemHasBeepIfInvalid(f)                                         \
    vtypeditemHasBeepIfInvalid (                                             \
        vdateitemGetTypeditem (f))

#define vdateitemSetBeepIfInvalid(f, d)                                      \
    vtypeditemSetBeepIfInvalid (                                             \
        vdateitemGetTypeditem (f),                                           \
        (d))

#define vdateitemHasKeepFocusIfInvalid(f)                                    \
    vtypeditemHasKeepFocusIfInvalid (                                        \
        vdateitemGetTypeditem (f))

#define vdateitemSetKeepFocusIfInvalid(f, b)                                 \
    vtypeditemSetKeepFocusIfInvalid (                                        \
        vdateitemGetTypeditem (f),                                           \
        (b))

#define vdateitemHasNeverInvalid(f)                                          \
    vtypeditemHasNeverInvalid (                                              \
        vdateitemGetTypeditem (f))

#define vdateitemSetNeverInvalid(f, b)                                       \
    vtypeditemSetNeverInvalid (                                              \
        vdateitemGetTypeditem (f),                                           \
        (b))

#define vdateitemHasValidateOnChange(f)                                      \
    vtypeditemHasValidateOnChange (                                          \
        vdateitemGetTypeditem (f))

#define vdateitemSetValidateOnChange(f, b)                                   \
    vtypeditemSetValidateOnChange (                                          \
        vdateitemGetTypeditem (f),                                           \
        (b))

#define vdateitemIsNull(i)                                                   \
    vtypeditemIsNull (                                                       \
        vdateitemGetTypeditem (i))

#define vdateitemSetNull(i, n)                                               \
    vtypeditemSetNull (                                                      \
        vdateitemGetTypeditem (i),                                           \
        (n))

#define vdateitemHasEmptyIsNull(i)                                           \
    vtypeditemHasEmptyIsNull (                                               \
        vdateitemGetTypeditem (i))

#define vdateitemSetEmptyIsNull(i, n)                                        \
    vtypeditemSetEmptyIsNull (                                               \
        vdateitemGetTypeditem (i),                                           \
        (n))

#define vdateitemSetInformingField(i, f)                                     \
    vtypeditemSetInformingField (                                            \
        vdateitemGetTypeditem (i),                                           \
        (f))

#define vdateitemIsInformingField(i)                                         \
    vtypeditemIsInformingField (                                             \
        vdateitemGetTypeditem (i))

vportEND_CPLUSPLUS_EXTERN_C

#endif /* vdateitemINCLUDED */

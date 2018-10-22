/* $Id: vdoubleitem.h,v 1.11 1997/06/27 01:50:05 robert Exp $ */

/* vdoubleitem - a double input item */

#ifndef vdoubleitemINCLUDED
#define vdoubleitemINCLUDED 1

#ifndef vportINCLUDED
#include <vport.h>
#endif

#ifndef veventINCLUDED
#include veventHEADER
#endif

#ifndef vformatINCLUDED
#include vformatHEADER
#endif

#ifndef vnumINCLUDED
#include vnumHEADER
#endif

#ifndef vtypeditemINCLUDED
#include vtypeditemHEADER
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * * * * * * * * * TYPE AND STRUCTURE DEFINITIONS * * * * * * * * * *
 */

/*
 * * DATE ITEM TYPE FORWARD DECLARATION
 */
typedef struct vdoubleitem
               vdoubleitem;

typedef struct vdoubleitemClass
               vdoubleitemClass;

typedef vtypeditemText 
        vdoubleitemText;

typedef vtypeditemTextClass
        vdoubleitemTextClass;

/*
 * * CLIENT NOTIFICATION PROCEDURE PROTOTYPE
 */
typedef void (*vdoubleitemNoteProc) (
    vdoubleitem *item,
    int          msg
);

/*
 * * CLIENT VALIDATION PROCEDURE PROTOTYPE
 */
typedef vbool (*vdoubleitemValidatorProc) (
    vdoubleitem *item
);

/*
 * * INCREMENT CODES
 */
enum
{
    vdoubleitemUP = vtypeditemUP,
    vdoubleitemDOWN,
    vdoubleitemNO_DIRECTION
};

/*
 * * NOTIFICATION CODES
 */
enum
{
    vdoubleitemNOTIFY_FOCUS = vtypeditemNOTIFY_FOCUS,
    vdoubleitemNOTIFY_UNFOCUS,
    vdoubleitemNOTIFY_VALID,
    vdoubleitemNOTIFY_PARTIALLY_VALID,
    vdoubleitemNOTIFY_INVALID,
    vdoubleitemNOTIFY_NEXT
};

/*
 * * DOUBLE ITEM INSTANCE DEFINITION
 */
struct vdoubleitem
{
    vtypeditem    typeditem;
    double        value;
    unsigned long flags;
    double        increment;
};


/*
 * * DOUBLE ITEM CLASS DEFINITION
 */
#define vdoubleitemCLASS(SUPER, ITEM, NOTIFY, VALIDATOR_PROC)                \
                                                                             \
    vtypeditemCLASS (SUPER, ITEM, NOTIFY, VALIDATOR_PROC);                   \
                                                                             \
    vclassMETHOD_RET (vdoubleitemGET_VALUE, double,                          \
        (ITEM *item));                                                       \
    vclassMETHOD     (vdoubleitemSET_VALUE,                                  \
        (ITEM *item, double value));                                         \
    vclassMETHOD     (vdoubleitemSET_INCREMENT,                              \
        (ITEM *item, double increment))

struct vdoubleitemClass
{
    vdoubleitemCLASS (
        vdoubleitemClass,
        vdoubleitem,
        vdoubleitemNoteProc,
        vdoubleitemValidatorProc);
};

/*
 * * * * * * * * * DOUBLE ITEM FUNCTION PROTOTYPES * * * * * * * * * *
 */

void
vdoubleitemStartup (
    void
);

vdoubleitemClass *
vdoubleitemGetDefaultClass (
    void
);

vdoubleitemClass *
vdoubleitemGetClass (
    vdoubleitem *item
);

vdoubleitem *
vdoubleitemCreate (
    void
);

vdoubleitem *
vdoubleitemCreateOfClass (
    vdoubleitemClass *clas
);

vtypeditem *
vdoubleitemGetTypeditem (
    vdoubleitem *item
);

vdialogItem *
vdoubleitemGetItem (
    vdoubleitem *item
);

vdoubleitem *
vdoubleitemClone (
    vdoubleitem *item
);

void
vdoubleitemCopy (
    vdoubleitem *src,
    vdoubleitem *dest
);

void
vdoubleitemCopyInit (
    vdoubleitem *src,
    vdoubleitem *dest
);

void
vdoubleitemInit (
    vdoubleitem *item
);

void
vdoubleitemInitOfClass (
    vdoubleitem      *item,
    vdoubleitemClass *clas
);

void
vdoubleitemDump (
    vdoubleitem *item,
    FILE        *stream
);

void
vdoubleitemDestroy (
    vdoubleitem *item
);

vdoubleitem *
vdoubleitemLoad (
    vresource resource
);

void
vdoubleitemLoadInit (
    vdoubleitem *item,
    vresource    resource
);

void
vdoubleitemStore (
    vdoubleitem *item,
    vresource    resource
);

void *
vdoubleitemGetData (
    vdoubleitem *item
);

void
vdoubleitemSetData (
    vdoubleitem *item,
    const void  *data
);

vdoubleitemNoteProc
vdoubleitemGetNotify (
    vdoubleitem *item
);

void
vdoubleitemSetNotify (
    vdoubleitem         *item,
    vdoubleitemNoteProc  notify
);

void
vdoubleitemNotify (
    vdoubleitem *item,
    int          msg
);

vdoubleitemValidatorProc
vdoubleitemGetValidator (
    vdoubleitem *item
);

void
vdoubleitemSetValidator (
    vdoubleitem              *item,
    vdoubleitemValidatorProc  validatorProc
);

vdoubleitemText *
vdoubleitemGetTextData (
    vdoubleitem *item
);

void
vdoubleitemSetTextData (
    vdoubleitem     *item,
    vdoubleitemText *text
);

vstr *
vdoubleitemGetString (
    vdoubleitem *item
);

void
vdoubleitemSetString (
    vdoubleitem *item,
    const vchar *text
);

vstr *
vdoubleitemGetTransientString (
    vdoubleitem *item
);

vscribe *
vdoubleitemGetTransientStringScribed (
    vdoubleitem *item
);

int
vdoubleitemGetLength (
    vdoubleitem *item
);

vscribe *
vdoubleitemGetStringScribed (
    vdoubleitem *item
);

void
vdoubleitemSetStringScribed (
    vdoubleitem *item,
    vscribe     *scribe
);

vscribe *
vdoubleitemGetSubstrScribed (
    vdoubleitem *item,
    long         begin,
    long         len
);

void
vdoubleitemInsertString (
    vdoubleitem *item,
    long         selStart,
    long         selLength,
    vchar       *s,
    long         len
);

void
vdoubleitemDeleteString (
    vdoubleitem *item,
    long         selStart,
    long         selLength
);

void
vdoubleitemSelectRange (
    vdoubleitem *item, 
    long         begin,
    long         len
);

void
vdoubleitemSelectAll (
    vdoubleitem *item
);

vdoubleitemText *
vdoubleitemCreateTextData (
    vdoubleitem *item
);

vtextSelection *
vdoubleitemGetSelection (
    vdoubleitem *item
);

void
vdoubleitemSetSelection (
    vdoubleitem    *item,
    vtextSelection *selection
);

vscribe *
vdoubleitemGetSelectionScribed (
    vdoubleitem *item
);

vcolor *
vdoubleitemGetForeground (
    vdoubleitem *item
);

void
vdoubleitemSetForeground (
    vdoubleitem *item,
    vcolor      *fg
);

int
vdoubleitemGetJustification (
    vdoubleitem *item
);

void
vdoubleitemSetJustification (
    vdoubleitem *item,
    int          justification
);

vformatDouble *
vdoubleitemGetFormat (
    vdoubleitem *item
);

void
vdoubleitemSetFormat (
    vdoubleitem   *item,
    vformatDouble *format
);

void
vdoubleitemSetFormatOwned (
    vdoubleitem   *item,
    vformatDouble *format
);

vobservable *
vdoubleitemGetField (
    vdoubleitem *item
);

void
vdoubleitemSetField (
    vdoubleitem *item,
    vobservable *field
);

void
vdoubleitemSetObserving (
    vdoubleitem *item,
    vbool        observing
);

vbool
vdoubleitemIsObserving (
    vdoubleitem *item
);

double
vdoubleitemGetValue (
    vdoubleitem *item
);

void
vdoubleitemSetValue (
    vdoubleitem *item,
    double       value
);

void
vdoubleitemSetIncrement (
    vdoubleitem *item,
    double       increment
);

double
vdoubleitemGetIncrement (
    vdoubleitem *item
);

double
vdoubleitemDetermineIncrement (
    vdoubleitem *item
);

void
vdoubleitemIncrement (
    vdoubleitem *item,
    int          dir
);

void
vdoubleitemSetEditable (
    vdoubleitem *item
);

vbool
vdoubleitemIsValid (
    vdoubleitem *item
);

vbool
vdoubleitemIsDirty (
    vdoubleitem *item
);

void
vdoubleitemSetDirty (
    vdoubleitem *item,
    vbool        dirty
);

vbool
vdoubleitemIsOneLine (
    vdoubleitem *item
);

void
vdoubleitemSetOneLine (
    vdoubleitem *item,
    vbool        oneLine
);

vbool
vdoubleitemIsSelectable (
    vdoubleitem *item
);

void
vdoubleitemSetSelectable (
    vdoubleitem *item,
    vbool        selectable
);

vbool
vdoubleitemIsModifiable (
    vdoubleitem *item
);

void vdoubleitemSetModifiable (
    vdoubleitem *item,
    vbool        modifiable
);

vbool
vdoubleitemHasBeepIfInvalid (
    vdoubleitem *item
);

void
vdoubleitemSetBeepIfInvalid (
    vdoubleitem *item,
    vbool        beepIfInvalid
);

vbool
vdoubleitemHasKeepFocusIfInvalid (
    vdoubleitem *item
);

void
vdoubleitemSetKeepFocusIfInvalid (
    vdoubleitem *item,
    vbool        flag
);

vbool
vdoubleitemHasNeverInvalid (
    vdoubleitem *item
);

void
vdoubleitemSetNeverInvalid (
    vdoubleitem *item,
    vbool        flag
);

vbool
vdoubleitemHasValidateOnChange (
    vdoubleitem *item
);

void
vdoubleitemSetValidateOnChange (
    vdoubleitem *item,
    vbool        flag
);

vbool
vdoubleitemIsNull (
    vdoubleitem *item
);

void
vdoubleitemSetNull (
    vdoubleitem *item,
    vbool        isNull
);

void
vdoubleitemSetEmptyIsNull (
    vdoubleitem *item,
    vbool        emptyIsNull
);

vbool
vdoubleitemHasEmptyIsNull (
    vdoubleitem *item
);

void
vdoubleitemSetInformingField (
    vdoubleitem *item,
    vbool        informing
);

vbool
vdoubleitemIsInformingField (
    vdoubleitem *item
);

long
vdoubleitemGetMaxLength (
    vdoubleitem *item
);

void
vdoubleitemSetMaxLength (
    vdoubleitem *item,
    long         maxLength
);

void
vdoubleitemFocus (
    vdoubleitem *item
);

void
vdoubleitemUnfocus (
    vdoubleitem *item
);

vdoubleitem *
vdoubleitemTextGetDoubleitem (
    vdoubleitemText *text
);

vtypeditemText *
vdoubleitemTextGetTypeditemText (
    vdoubleitemText *text
);

vtext *
vdoubleitemTextGetText (
    vdoubleitemText *text
);

/*
 * * * * * * * * * * PRIVATE MACRO DEFINITIONS * * * * * * * * * *
 */

#define vdoubleitemGetTypeditem(f)                                           \
    vportBASE_OBJECT (                                                       \
        (f),                                                                 \
        typeditem)

#define vdoubleitemGetItem(f)                                                \
    vtypeditemGetItem (                                                      \
        vdoubleitemGetTypeditem (f))

#define vdoubleitemCreateOfClass(c)                                          \
    ((vdoubleitem *)                                                         \
        vtypeditemCreateOfClass (                                            \
            (vtypeditemClass *) (c)))

#define vdoubleitemCreate()                                                  \
    vdoubleitemCreateOfClass (                                               \
        vdoubleitemGetDefaultClass ())

#define vdoubleitemClone(f)                                                  \
    ((vdoubleitem *)                                                         \
        vtypeditemClone (                                                    \
            vdoubleitemGetTypeditem(f)))

#define vdoubleitemInitOfClass(f, c)                                         \
    vtypeditemInitOfClass (                                                  \
        vdoubleitemGetTypeditem (f),                                         \
        (vdoubleitemClass *) (c))

#define vdoubleitemInit(f)                                                   \
    vdoubleitemInitOfClass (                                                 \
        (f),                                                                 \
        vdoubleitemGetDefaultClass ());

#define vdoubleitemCopyInit(f, t)                                            \
    vtypeditemCopyInit (                                                     \
        vdoubleitemGetTypeditem (f),                                         \
        (vtypeditem *) (t))

#define vdoubleitemLoad(r)                                                   \
    ((vdoubleitem *)                                                         \
        vtypeditemLoad (                                                     \
            vdoubleitemGetTypeditem (r)))

#define vdoubleitemLoadInit(f, r)                                            \
    vtypeditemLoadInit (                                                     \
        vdoubleitemGetTypeditem (f),                                         \
        (r))

#define vdoubleitemDump(i, s)                                                \
    vtypeditemDump (                                                         \
        vdoubleitemGetTypeditem (i),                                         \
        (s))

#define vdoubleitemDestroy(f)                                                \
    vtypeditemDestroy (                                                      \
        vdoubleitemGetTypeditem (f))

#define vdoubleitemGetClass(f)                                               \
    ((vdoubleitemClass *)                                                    \
        vtypeditemGetClass (                                                 \
            vdoubleitemGetTypeditem (f)))

#define vdoubleitemGetNotify(f)                                              \
    ((vdoubleitemNoteProc)                                                   \
        vtypeditemGetNotify (                                                \
            vdoubleitemGetTypeditem (f)))

#define vdoubleitemSetNotify(f, n)                                           \
    vtypeditemSetNotify (                                                    \
        vdoubleitemGetTypeditem (f),                                         \
        (vtypeditemNoteProc) (n))

#define vdoubleitemNotify(d, m)                                              \
    vtypeditemNotify (                                                       \
        vdoubleitemGetTypeditem (d),                                         \
        (m))

#define vdoubleitemGetValidator(f)                                           \
    ((vdoubleitemValidatorProc)                                              \
        vtypeditemGetValidator (                                             \
            vdoubleitemGetTypeditem (f)))

#define vdoubleitemSetValidator(f, p)                                        \
    vtypeditemSetValidator (                                                 \
        vdoubleitemGetTypeditem (f),                                         \
        (vtypeditemValidatorProc) (p))

#define vdoubleitemSetData(f, d)                                             \
    vtypeditemSetData (                                                      \
        vdoubleitemGetTypeditem (f),                                         \
        (d))

#define vdoubleitemGetData(f)                                                \
    vtypeditemGetData (                                                      \
        vdoubleitemGetTypeditem (f))

#define vdoubleitemGetString(f)                                              \
    vtypeditemGetString (                                                    \
        vdoubleitemGetTypeditem (f))

#define vdoubleitemSetString(f, s)                                           \
    vtypeditemSetString (                                                    \
        vdoubleitemGetTypeditem (f),                                         \
        (s))

#define vdoubleitemGetTransientString(f)                                     \
    vtypeditemGetTransientString (                                           \
        vdoubleitemGetTypeditem (f))

#define vdoubleitemGetTransientStringScribed(f)                              \
    vtypeditemGetTransientStringScribed (                                    \
        vdoubleitemGetTypeditem (f))

#define vdoubleitemGetLength(f)                                              \
    vtypeditemGetLength (                                                    \
        vdoubleitemGetTypeditem (f))

#define vdoubleitemGetStringScribed(f)                                       \
    vtypeditemGetStringScribed (                                             \
        vdoubleitemGetTypeditem (f))

#define vdoubleitemSetStringScribed(f, s)                                    \
    vtypeditemSetStringScribed (                                             \
        vdoubleitemGetTypeditem (f),                                         \
        (s))

#define vdoubleitemGetSubstrScribed(f, b, l)                                 \
    vtypeditemGetSubstrScribed (                                             \
        vdoubleitemGetTypeditem (f),                                         \
        (b),                                                                 \
        (l))

#define vdoubleitemInsertString(f, start, len, str, strLen)                  \
    vtypeditemInsertString (                                                 \
        vdoubleitemGetTypeditem (f),                                         \
        (start),                                                             \
        (len),                                                               \
        (str),                                                               \
        (strLen))

#define vdoubleitemDeleteString(f, start, len)                               \
    vtypeditemDeleteString (                                                 \
        vdoubleitemGetTypeditem (f),                                         \
        (start),                                                             \
        (len))

#define vdoubleitemSelectRange(f, b, l)                                      \
    vtypeditemSelectRange (                                                  \
        vdoubleitemGetTypeditem (f),                                         \
        (b),                                                                 \
        (l))

#define vdoubleitemSelectAll(f)                                              \
    vtypeditemSelectAll (                                                    \
        vdoubleitemGetTypeditem (f))

#define vdoubleitemCreateTextData(f)                                         \
    vtypeditemCreateTextData (                                               \
        vdoubleitemGetTypeditem (f))

#define vdoubleitemGetSelection(f)                                           \
    vtypeditemGetSelection (                                                 \
        vdoubleitemGetTypeditem (f))

#define vdoubleitemSetSelection(f, s)                                        \
    vtypeditemSetSelection (                                                 \
        vdoubleitemGetTypeditem (f),                                         \
        (s))

#define vdoubleitemGetSelectionScribed(f)                                    \
    vtypeditemGetSelectionScribed (                                          \
        vdoubleitemGetTypeditem (f))

#define vdoubleitemGetForeground(i)                                          \
    vtypeditemGetForeground (                                                \
        vdoubleitemGetTypeditem (i))

#define vdoubleitemSetForeground(i, c)                                       \
    vtypeditemSetForeground (                                                \
        vdoubleitemGetTypeditem (i),                                         \
        (c))

#define vdoubleitemGetJustification(f)                                       \
   vtypeditemGetJustification (                                              \
        vdoubleitemGetTypeditem (f))

#define vdoubleitemSetJustification(f, j)                                    \
    vtypeditemSetJustification (                                             \
        vdoubleitemGetTypeditem (f), j)

#define vdoubleitemGetFormat(f)                                              \
    ((vformatDouble *)                                                       \
        vtypeditemGetFormat (                                                \
            vdoubleitemGetTypeditem (f)))

#define vdoubleitemSetFormat(f, p)                                           \
    vtypeditemSetFormat (                                                    \
        vdoubleitemGetTypeditem (f),                                         \
        (vformat *) (p))

#define vdoubleitemSetFormatOwned(f, p)                                      \
    vtypeditemSetFormatOwned (                                               \
        vdoubleitemGetTypeditem (f),                                         \
        (vformat *) (p))

#define vdoubleitemGetField(f)                                               \
    vtypeditemGetField (                                                     \
        vdoubleitemGetTypeditem (f))

#define vdoubleitemSetField(f, p)                                            \
    vtypeditemSetField (                                                     \
        vdoubleitemGetTypeditem (f),                                         \
        (p))

#define vdoubleitemIsObserving(i)                                            \
    vtypeditemIsObserving (                                                  \
        vdoubleitemGetTypeditem (i))

#define vdoubleitemSetObserving(i, o)                                        \
    vtypeditemSetObserving (                                                 \
        vdoubleitemGetTypeditem (i),                                         \
        (o))

#define vdoubleitemGetIncrement(f)                                           \
    ((f)->increment)

#define vdoubleitemSetEditable(f)                                            \
    vtypeditemSetEditable (                                                  \
        vdoubleitemGetTypeditem (f))

#define vdoubleitemIsValid(f)                                                \
    vtypeditemIsValid (                                                      \
        vdoubleitemGetTypeditem (f))

#define vdoubleitemIsDirty(f)                                                \
    vtypeditemIsDirty (                                                      \
        vdoubleitemGetTypeditem (f))

#define vdoubleitemSetDirty(f, d)                                            \
    vtypeditemSetDirty (                                                     \
        vdoubleitemGetTypeditem (f),                                         \
        (d))

#define vdoubleitemIsOneLine(f)                                              \
    vtypeditemIsOneLine (                                                    \
        vdoubleitemGetTypeditem (f))

#define vdoubleitemSetOneLine(f, d)                                          \
    vtypeditemSetOneLine (                                                   \
        vdoubleitemGetTypeditem (f),                                         \
        (d))

#define vdoubleitemIsSelectable(f)                                           \
    vtypeditemIsSelectable (                                                 \
        vdoubleitemGetTypeditem (f))

#define vdoubleitemSetSelectable(f, d)                                       \
    vtypeditemSetSelectable (                                                \
        vdoubleitemGetTypeditem (f),                                         \
        (d))

#define vdoubleitemIsModifiable(f)                                           \
    vtypeditemIsModifiable (                                                 \
        vdoubleitemGetTypeditem (f))

#define vdoubleitemSetModifiable(f, d)                                       \
    vtypeditemSetModifiable (                                                \
        vdoubleitemGetTypeditem (f),                                         \
        (d))

#define vdoubleitemHasBeepIfInvalid(f)                                       \
    vtypeditemHasBeepIfInvalid (                                             \
        vdoubleitemGetTypeditem (f))

#define vdoubleitemSetBeepIfInvalid(f, d)                                    \
    vtypeditemSetBeepIfInvalid (                                             \
        vdoubleitemGetTypeditem (f),                                         \
        (d))

#define vdoubleitemHasKeepFocusIfInvalid(f)                                  \
    vtypeditemHasKeepFocusIfInvalid (                                        \
        vdoubleitemGetTypeditem (f))

#define vdoubleitemSetKeepFocusIfInvalid(f, b)                               \
    vtypeditemSetKeepFocusIfInvalid (                                        \
        vdoubleitemGetTypeditem (f),                                         \
        (b))

#define vdoubleitemHasNeverInvalid(f)                                        \
    vtypeditemHasNeverInvalid (                                              \
        vdoubleitemGetTypeditem (f))

#define vdoubleitemSetNeverInvalid(f, b)                                     \
    vtypeditemSetNeverInvalid (                                              \
        vdoubleitemGetTypeditem (f),                                         \
        (b))

#define vdoubleitemHasValidateOnChange(f)                                    \
    vtypeditemHasValidateOnChange (                                          \
        vdoubleitemGetTypeditem (f))

#define vdoubleitemSetValidateOnChange(f, b)                                 \
    vtypeditemSetValidateOnChange (                                          \
        vdoubleitemGetTypeditem (f),                                         \
        (b))

#define vdoubleitemIsNull(i)                                                 \
    vtypeditemIsNull (                                                       \
        vdoubleitemGetTypeditem (i))

#define vdoubleitemSetNull(i, n)                                             \
    vtypeditemSetNull (                                                      \
        vdoubleitemGetTypeditem (i),                                         \
        (n))

#define vdoubleitemHasEmptyIsNull(i)                                         \
    vtypeditemHasEmptyIsNull (                                               \
        vdoubleitemGetTypeditem (i))

#define vdoubleitemSetEmptyIsNull(i, n)                                      \
    vtypeditemSetEmptyIsNull (                                               \
        vdoubleitemGetTypeditem (i),                                         \
        (n))

#define vdoubleitemSetInformingField(i, f)                                   \
    vtypeditemSetInformingField (                                            \
        vdoubleitemGetTypeditem (i),                                         \
        (f))

#define vdoubleitemIsInformingField(i)                                       \
    vtypeditemIsInformingField (                                             \
        vdoubleitemGetTypeditem (i))

#define vdoubleitemGetMaxLength(f)                                           \
    vtypeditemGetMaxLength (                                                 \
        vdoubleitemGetTypeditem (f))

#define vdoubleitemSetMaxLength(f, l)                                        \
    vtypeditemSetMaxLength (                                                 \
        vdoubleitemGetTypeditem (f),                                         \
        (l))

#define vdoubleitemFocus(f)                                                  \
    vtypeditemFocus (                                                        \
        vdoubleitemGetTypeditem (f))

#define vdoubleitemUnfocus(f)                                                \
    vtypeditemUnfocus (                                                      \
        vdoubleitemGetTypeditem (f))

#define vdoubleitemTextGetTypeditemText(t)                                   \
    ((vtypeditemText *) (t))

#define vdoubleitemTextGetText(t)                                            \
    vtypeditemTextGetText (                                                  \
        vdoubleitemTextGetTypeditemText (t))

#define vdoubleitemTextGetDoubleitem(t)                                      \
    ((vdoubleitem *)                                                         \
        vtypeditemTextGetTypeditem (                                         \
            vdoubleitemTextGetTypeditemText (t)))

/*
 * * * * * * * * * * PRIVATE FUNCTION MESSAGE DEFINITIONS * * * * * * * * * *
 */

#define vdoubleitemCopy(f, t)                                                \
    vclassSend (                                                             \
        vdoubleitemGetClass (f),                                             \
        vobjectCOPY,                                                         \
        (f, t))

#define vdoubleitemStore(f, t)                                               \
    vclassSend (                                                             \
        vdoubleitemGetClass (f),                                             \
        vobjectSTORE,                                                        \
        (f, t))

#define vdoubleitemGetValue(f)                                               \
    vclassSend (                                                             \
        vdoubleitemGetClass (f),                                             \
        vdoubleitemGET_VALUE,                                                \
        (f))

#define vdoubleitemSetValue(f, v)                                            \
    vclassSend (                                                             \
        vdoubleitemGetClass (f),                                             \
        vdoubleitemSET_VALUE,                                                \
        (f, v))

#define vdoubleitemSetIncrement(f, i)                                        \
    vclassSend (                                                             \
        vdoubleitemGetClass (f),                                             \
        vdoubleitemSET_INCREMENT,                                            \
        (f, i))

#define vdoubleitemIncrement(i, d)                                           \
    vclassSend (                                                             \
        vdoubleitemGetClass (i),                                             \
        vtypeditemINCREMENT,                                                 \
        (i, d))

/*
 * * * * * * * * * DOUBLE ITEM GLOBAL VARIABLES * * * * * * * * * *
 */

vportEND_CPLUSPLUS_EXTERN_C

#endif /* vdoubleitemINCLUDED */

/* $Id: vlongitem.h,v 1.14 1997/10/23 17:43:14 garyk Exp $ */

/* vlongitem - a long integer input item */

#ifndef vlongitemINCLUDED
#define vlongitemINCLUDED 1

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
 * * LONG ITEM TYPE FORWARD DECLARATION
 */
typedef struct vlongitem
               vlongitem;

typedef struct vlongitemClass
               vlongitemClass;

typedef vtypeditemText
        vlongitemText;

typedef vtypeditemTextClass
        vlongitemTextClass;

/*
 * * CLIENT NOTIFICATION PROCEDURE PROTOTYPE
 */
typedef void (*vlongitemNoteProc) (
    vlongitem *item,
    int        msg
);

/*
 * * CLIENT VALIDATION PROCEDURE PROTOTYPE
 */
typedef vbool (*vlongitemValidatorProc) (
    vlongitem *item
);

/*
 * * INCREMENT CODES
 */
enum
{
    vlongitemUP = vtypeditemUP,
    vlongitemDOWN,
    vlongitemNO_DIRECTION
};

/*
 * * NOTIFICATION CODES
 */
enum
{
    vlongitemNOTIFY_FOCUS = vtypeditemNOTIFY_FOCUS,
    vlongitemNOTIFY_UNFOCUS,
    vlongitemNOTIFY_VALID,
    vlongitemNOTIFY_PARTIALLY_VALID,
    vlongitemNOTIFY_INVALID,
    vlongitemNOTIFY_NEXT
};

/*
 * * LONG ITEM INSTANCE DEFINITION
 */
struct vlongitem
{
    vtypeditem    typeditem;
    long          value;
    unsigned long flags;
    int           increment;
};


#define vlongitemCLASS(SUPER, ITEM, NOTIFY, VALIDATOR_PROC)                  \
                                                                             \
    vtypeditemCLASS (SUPER, ITEM, NOTIFY, VALIDATOR_PROC);                   \
                                                                             \
    vclassMETHOD_RET (vlongitemGET_VALUE, long,                              \
        (ITEM *item));                                                       \
    vclassMETHOD     (vlongitemSET_VALUE,                                    \
        (ITEM *item, long value));                                           \
    vclassMETHOD     (vlongitemSET_INCREMENT,                                \
        (ITEM *item, long increment))

struct vlongitemClass
{
    vlongitemCLASS (
        vlongitemClass,
        vlongitem,
        vlongitemNoteProc,
        vlongitemValidatorProc);
};

/*
 * * * * * * * * * LONG ITEM FUNCTION PROTOTYPES * * * * * * * * * *
 */

void
vlongitemStartup (
    void
);

vlongitemClass *
vlongitemGetDefaultClass (
    void
);

vlongitem *
vlongitemCreate (
    void
);

vlongitem *
vlongitemCreateOfClass (
    vlongitemClass *clas
);

vlongitemClass *
vlongitemGetClass (
    vlongitem *item
);

vtypeditem *
vlongitemGetTypeditem (
    vlongitem *item
);

vdialogItem *
vlongitemGetItem (
    vlongitem *item
);

vlongitem *
vlongitemClone (
    vlongitem *item
);

void
vlongitemCopy (
    vlongitem *src,
    vlongitem *dest
);

void
vlongitemCopyInit (
    vlongitem *src,
    vlongitem *dest
);

void
vlongitemInit (
    vlongitem *item
);

void
vlongitemInitOfClass (
    vlongitem       *item,
    vlongitemClass  *clas
);

void
vlongitemDump (
    vlongitem *item,
    FILE      *stream
);

void
vlongitemDestroy (
    vlongitem *item
);

vlongitem *
vlongitemLoad (
    vresource resource
);

void
vlongitemLoadInit (
    vlongitem *item,
    vresource  resource
);

void
vlongitemStore (
    vlongitem *item,
    vresource  resource
);

void *
vlongitemGetData (
    vlongitem *item
);

void
vlongitemSetData (
    vlongitem  *item,
    const void *data
);

vlongitemNoteProc
vlongitemGetNotify (
    vlongitem *item
);

void
vlongitemSetNotify (
    vlongitem         *item,
    vlongitemNoteProc  notify
);

void
vlongitemNotify (
    vlongitem *item,
    int        msg
);

vlongitemValidatorProc
vlongitemGetValidator (
    vlongitem *item
);

void
vlongitemSetValidator (
    vlongitem              *item,
    vlongitemValidatorProc  validatorProc
);

vlongitemText *
vlongitemGetTextData (
    vlongitem *item
);

void
vlongitemSetTextData (
    vlongitem     *item,
    vlongitemText *text
);

vstr *
vlongitemGetString (
    vlongitem *item
);

void
vlongitemSetString (
    vlongitem   *item,
    const vchar *text
);

vstr *
vlongitemGetTransientString (
    vlongitem *item
);

vscribe *
vlongitemGetTransientStringScribed (
    vlongitem *item
);

int
vlongitemGetLength (
    vlongitem *item
);

vscribe *
vlongitemGetStringScribed (
    vlongitem *item
);

void
vlongitemSetStringScribed (
    vlongitem *item,
    vscribe   *scribe
);

vscribe *
vlongitemGetSubstrScribed (
    vlongitem *item,
    long       begin,
    long       len
);

void
vlongitemInsertString (
    vlongitem *item,
    long       selStart,
    long       selLength,
    vchar     *s,
    long       len
);

void
vlongitemDeleteString (
    vlongitem *item,
    long       selStart,
    long       selLength
);

void
vlongitemSelectRange (
    vlongitem *item, 
    long       begin,
    long       len
);

void
vlongitemSelectAll (
    vlongitem *item
);

vtextSelection *
vlongitemGetSelection (
    vlongitem *item
);

void
vlongitemSetSelection (
    vlongitem      *item,
    vtextSelection *selection
);

vscribe *
vlongitemGetSelectionScribed (
    vlongitem *item
);

vlongitemText *
vlongitemCreateTextData (
    vlongitem *item
);

vcolor *
vlongitemGetForeground (
    vlongitem *item
);

void
vlongitemSetForeground (
    vlongitem *item,
    vcolor    *fg
);

int
vlongitemGetJustification (
    vlongitem *item
);

void
vlongitemSetJustification (
    vlongitem *item,
    int        justification
);

vformatLong *
vlongitemGetFormat (
    vlongitem *item
);

void
vlongitemSetFormat (
    vlongitem   *item,
    vformatLong *format
);

void
vlongitemSetFormatOwned (
    vlongitem   *item,
    vformatLong *format
);

vobservable *
vlongitemGetField (
    vlongitem *item
);

void
vlongitemSetField (
    vlongitem *item,
    vobservable *field
);

void
vlongitemSetObserving (
    vlongitem *item,
    vbool      observing
);

vbool
vlongitemIsObserving (
    vlongitem *item
);

long
vlongitemGetValue (
    vlongitem *item
);

void
vlongitemSetValue (
    vlongitem *item,
    long       value
);

long
vlongitemGetIncrement (
    vlongitem *item
);

void
vlongitemSetIncrement (
    vlongitem *item,
    long       increment
);

void
vlongitemIncrement (
    vlongitem *item,
    int        dir
);

void
vlongitemSetEditable (
    vlongitem *item
);

vbool
vlongitemIsValid (
    vlongitem *item
);

vbool
vlongitemIsDirty (
    vlongitem *item
);

void
vlongitemSetDirty (
    vlongitem *item,
    vbool      dirty
);

vbool
vlongitemIsOneLine (
    vlongitem *item
);

void
vlongitemSetOneLine (
    vlongitem *item,
    vbool      oneLine
);

vbool
vlongitemIsSelectable (
    vlongitem *item
);

void
vlongitemSetSelectable (
    vlongitem *item,
    vbool      selectable
);

vbool
vlongitemIsModifiable (
    vlongitem *item
);

void
vlongitemSetModifiable (
    vlongitem *item,
    vbool      modifiable
);

vbool
vlongitemHasBeepIfInvalid (
    vlongitem *item
);

void
vlongitemSetBeepIfInvalid (
    vlongitem *item,
    vbool      beepIfInvalid
);

vbool
vlongitemHasKeepFocusIfInvalid (
    vlongitem *item
);

void
vlongitemSetKeepFocusIfInvalid (
    vlongitem *item,
    vbool      flag
);

vbool
vlongitemHasNeverInvalid (
    vlongitem *item
);

void
vlongitemSetNeverInvalid (
    vlongitem *item,
    vbool      flag
);

vbool
vlongitemHasValidateOnChange (
    vlongitem *item
);

void
vlongitemSetValidateOnChange (
    vlongitem *item,
    vbool      flag
);

vbool
vlongitemIsNull (
    vlongitem *item
);

void
vlongitemSetNull (
    vlongitem *item,
    vbool      isNull
);

void
vlongitemSetEmptyIsNull (
    vlongitem *item,
    vbool      emptyIsNull
);

vbool
vlongitemHasEmptyIsNull (
    vlongitem *item
);

void
vlongitemSetInformingField (
    vlongitem *item,
    vbool      informing
);

vbool
vlongitemIsInformingField (
    vlongitem *item
);

long
vlongitemGetMaxLength (
    vlongitem *item
);

void
vlongitemSetMaxLength (
    vlongitem *item,
    long       maxLength
);

void
vlongitemFocus (
    vlongitem *item
);

void
vlongitemUnfocus (
    vlongitem *item
);

vlongitem *
vlongitemTextGetLongitem (
    vlongitemText *text
);

vtypeditemText *
vlongitemTextGetTypeditemText (
    vlongitemText *text
);

vtext *
vlongitemTextGetText (
    vlongitemText *text
);

/*
 * * * * * * * * * * PRIVATE MACRO DEFINITIONS * * * * * * * * * *
 */

#define vlongitemGetTypeditem(f)                                             \
    vportBASE_OBJECT (                                                       \
        (f),                                                                 \
        typeditem)

#define vlongitemGetItem(f)                                                  \
    vtypeditemGetItem (                                                      \
        vlongitemGetTypeditem (f))

#define vlongitemCreateOfClass(c)                                            \
    ((vlongitem *)                                                           \
        vtypeditemCreateOfClass (                                            \
            (vtypeditemClass *) (c)))

#define vlongitemCreate()                                                    \
    vlongitemCreateOfClass (                                                 \
        vlongitemGetDefaultClass ())

#define vlongitemGetClass(f)                                                 \
    ((vlongitemClass *)                                                      \
        vtypeditemGetClass (                                                 \
            vlongitemGetTypeditem (f)))

#define vlongitemClone(f)                                                    \
    ((vlongitem *)                                                           \
        vtypeditemClone (                                                    \
            vlongitemGetTypeditem(f)))

#define vlongitemInitOfClass(f, c)                                           \
    vtypeditemInitOfClass (                                                  \
        vlongitemGetTypeditem (f),                                           \
            (vlongitemClass *) (c))

#define vlongitemInit(f)                                                     \
    vlongitemInitOfClass (                                                   \
        (f),                                                                 \
        vlongitemGetDefaultClass ());

#define vlongitemCopyInit(f, t)                                              \
    vtypeditemCopyInit (                                                     \
        vlongitemGetTypeditem (f),                                           \
        (vtypeditem *) (t))

#define vlongitemLoad(r)                                                     \
    ((vlongitem *)                                                           \
        vtypeditemLoad (                                                     \
            vlongitemGetTypeditem (r)))

#define vlongitemLoadInit(f, r)                                              \
    vtypeditemLoadInit (                                                     \
        vlongitemGetTypeditem (f),                                           \
        (r))

#define vlongitemDump(i, s)                                                  \
    vtypeditemDump (                                                         \
        vlongitemGetTypeditem (i),                                           \
        (s))

#define vlongitemDestroy(f)                                                  \
    vtypeditemDestroy (                                                      \
        vlongitemGetTypeditem (f))

#define vlongitemGetData(f)                                                  \
    vtypeditemGetData (                                                      \
        vlongitemGetTypeditem (f))
        
#define vlongitemSetData(f, d)                                               \
    vtypeditemSetData (                                                      \
        vlongitemGetTypeditem (f),                                           \
        (d))

#define vlongitemGetNotify(f)                                                \
    ((vlongitemNoteProc)                                                     \
        vtypeditemGetNotify (                                                \
            vlongitemGetTypeditem (f)))

#define vlongitemSetNotify(f, n)                                             \
    vtypeditemSetNotify (                                                    \
        vlongitemGetTypeditem (f),                                           \
        (vtypeditemNoteProc) (n))

#define vlongitemNotify(l, m)                                                \
    vtypeditemNotify (                                                       \
        vlongitemGetTypeditem (l),                                           \
        (m))

#define vlongitemSetValidator(f, p)                                          \
    vtypeditemSetValidator (                                                 \
        vlongitemGetTypeditem (f),                                           \
        (vtypeditemValidatorProc) (p))

#define vlongitemGetValidator(f)                                             \
    ((vlongitemValidatorProc)                                                \
        vtypeditemGetValidator (                                             \
            vlongitemGetTypeditem (f)))

#define vlongitemGetTextData(f)                                              \
    vtypeditemGetTextData (                                                  \
        vlongitemGetTypeditem (f))

#define vlongitemSetTextData(f, t)                                           \
    vtypeditemSetTextData (                                                  \
        vlongitemGetTypeditem (f),                                           \
        (t))

#define vlongitemGetString(f)                                                \
    vtypeditemGetString (                                                    \
        vlongitemGetTypeditem (f))

#define vlongitemSetString(f, s)                                             \
    vtypeditemSetString (                                                    \
        vlongitemGetTypeditem (f),                                           \
        (s))

#define vlongitemGetTransientString(f)                                       \
    vtypeditemGetTransientString (                                           \
        vlongitemGetTypeditem (f))

#define vlongitemGetTransientStringScribed(f)                                \
    vtypeditemGetTransientStringScribed (                                    \
        vlongitemGetTypeditem (f))

#define vlongitemGetLength(f)                                                \
    vtypeditemGetLength (                                                    \
        vlongitemGetTypeditem (f))

#define vlongitemGetStringScribed(f)                                         \
    vtypeditemGetStringScribed (                                             \
        vlongitemGetTypeditem (f))

#define vlongitemSetStringScribed(f, s)                                      \
    vtypeditemSetStringScribed (                                             \
        vlongitemGetTypeditem (f),                                           \
        (s))

#define vlongitemGetSubstrScribed(f, b, l)                                   \
    vtypeditemGetSubstrScribed (                                             \
        vlongitemGetTypeditem (f),                                           \
        (b),                                                                 \
        (l))

#define vlongitemInsertString(f, start, len, str, strLen)                    \
    vtypeditemInsertString (                                                 \
        vlongitemGetTypeditem (f),                                           \
        (start),                                                             \
        (len),                                                               \
        (str),                                                               \
        (strLen))

#define vlongitemDeleteString(f, start, len)                                 \
    vtypeditemDeleteString (                                                 \
        vlongitemGetTypeditem (f),                                           \
        (start),                                                             \
        (len))

#define vlongitemSelectRange(f, b, l)                                        \
    vtypeditemSelectRange (                                                  \
        vlongitemGetTypeditem (f),                                           \
        (b),                                                                 \
        (l))

#define vlongitemSelectAll(f)                                                \
    vtypeditemSelectAll (                                                    \
        vlongitemGetTypeditem (f))

#define vlongitemGetSelection(f)                                             \
    vtypeditemGetSelection (                                                 \
        vlongitemGetTypeditem (f))

#define vlongitemSetSelection(f, s)                                          \
    vtypeditemSetSelection (                                                 \
        vlongitemGetTypeditem (f),                                           \
        (s))

#define vlongitemGetSelectionScribed(f)                                      \
    vtypeditemGetSelectionScribed (                                          \
        vlongitemGetTypeditem (f))

#define vlongitemCreateTextData(f)                                           \
    vtypeditemCreateTextData (                                               \
        vlongitemGetTypeditem (f))

#define vlongitemGetForeground(i)                                            \
    vtypeditemGetForeground (                                                \
        vlongitemGetTypeditem (i))

#define vlongitemSetForeground(i, c)                                         \
    vtypeditemSetForeground (                                                \
        vlongitemGetTypeditem (i),                                           \
        (c))

#define vlongitemGetJustification(f)                                         \
    vtypeditemGetJustification (                                             \
        vlongitemGetTypeditem (f))

#define vlongitemSetJustification(f, j)                                      \
    vtypeditemSetJustification (                                             \
        vlongitemGetTypeditem (f),                                           \
        (j))

#define vlongitemGetFormat(f)                                                \
    ((vformatLong *)                                                         \
        vtypeditemGetFormat (                                                \
            vlongitemGetTypeditem (f)))

#define vlongitemSetFormat(f, p)                                             \
    vtypeditemSetFormat (                                                    \
        vlongitemGetTypeditem (f),                                           \
        (vformat *) (p))

#define vlongitemSetFormatOwned(f, p)                                        \
    vtypeditemSetFormatOwned (                                               \
        vlongitemGetTypeditem (f),                                           \
        (vformat *) (p))

#define vlongitemGetField(f)                                                 \
    vtypeditemGetField (                                                     \
        vlongitemGetTypeditem (f))

#define vlongitemSetField(f, p)                                              \
    vtypeditemSetField (                                                     \
        vlongitemGetTypeditem (f),                                           \
        (p))

#define vlongitemIsObserving(i)                                              \
    vtypeditemIsObserving (                                                  \
        vlongitemGetTypeditem (i))

#define vlongitemSetObserving(i, o)                                          \
    vtypeditemSetObserving (                                                 \
        vlongitemGetTypeditem (i),                                           \
        (o))

#define vlongitemGetIncrement(f)                                             \
    ((f)->increment)

#define vlongitemSetEditable(f)                                              \
    vtypeditemSetEditable (                                                  \
        vlongitemGetTypeditem (f))

#define vlongitemIsValid(f)                                                  \
    vtypeditemIsValid (                                                      \
        vlongitemGetTypeditem (f))

#define vlongitemIsDirty(f)                                                  \
    vtypeditemIsDirty (                                                      \
        vlongitemGetTypeditem (f))

#define vlongitemSetDirty(f, d)                                              \
    vtypeditemSetDirty (                                                     \
        vlongitemGetTypeditem (f),                                           \
        (d))

#define vlongitemIsOneLine(f)                                                \
    vtypeditemIsOneLine (                                                    \
        vlongitemGetTypeditem (f))

#define vlongitemSetOneLine(f, d)                                            \
    vtypeditemSetOneLine (                                                   \
        vlongitemGetTypeditem (f),                                           \
        (d))

#define vlongitemIsSelectable(f)                                             \
    vtypeditemIsSelectable (                                                 \
        vlongitemGetTypeditem (f))

#define vlongitemSetSelectable(f, d)                                         \
    vtypeditemSetSelectable (                                                \
        vlongitemGetTypeditem (f),                                           \
        (d))

#define vlongitemIsModifiable(f)                                             \
    vtypeditemIsModifiable (                                                 \
        vlongitemGetTypeditem (f))

#define vlongitemSetModifiable(f, d)                                         \
    vtypeditemSetModifiable (                                                \
        vlongitemGetTypeditem (f),                                           \
        (d))

#define vlongitemHasBeepIfInvalid(f)                                         \
    vtypeditemHasBeepIfInvalid (                                             \
        vlongitemGetTypeditem (f))

#define vlongitemSetBeepIfInvalid(f, d)                                      \
    vtypeditemSetBeepIfInvalid (                                             \
        vlongitemGetTypeditem (f),                                           \
        (d))

#define vlongitemHasKeepFocusIfInvalid(f)                                    \
    vtypeditemHasKeepFocusIfInvalid (                                        \
        vlongitemGetTypeditem (f))

#define vlongitemSetKeepFocusIfInvalid(f, b)                                 \
    vtypeditemSetKeepFocusIfInvalid (                                        \
        vlongitemGetTypeditem (f),                                           \
        (b))

#define vlongitemHasNeverInvalid(f)                                          \
    vtypeditemHasNeverInvalid (                                              \
        vlongitemGetTypeditem (f))

#define vlongitemSetNeverInvalid(f, b)                                       \
    vtypeditemSetNeverInvalid (                                              \
        vlongitemGetTypeditem (f),                                           \
        (b))

#define vlongitemHasValidateOnChange(f)                                      \
    vtypeditemHasValidateOnChange (                                          \
        vlongitemGetTypeditem (f))

#define vlongitemSetValidateOnChange(f, b)                                   \
    vtypeditemSetValidateOnChange (                                          \
        vlongitemGetTypeditem (f),                                           \
        (b))

#define vlongitemIsNull(i)                                                   \
    vtypeditemIsNull (                                                       \
        vlongitemGetTypeditem (i))

#define vlongitemSetNull(i, n)                                               \
    vtypeditemSetNull (                                                      \
        vlongitemGetTypeditem (i),                                           \
        (n))

#define vlongitemHasEmptyIsNull(i)                                           \
    vtypeditemHasEmptyIsNull (                                               \
        vlongitemGetTypeditem (i))

#define vlongitemSetEmptyIsNull(i, n)                                        \
    vtypeditemSetEmptyIsNull (                                               \
        vlongitemGetTypeditem (i),                                           \
        (n))

#define vlongitemSetInformingField(i, f)                                     \
    vtypeditemSetInformingField (                                            \
        vlongitemGetTypeditem (i),                                           \
        (f))

#define vlongitemIsInformingField(i)                                         \
    vtypeditemIsInformingField (                                             \
        vlongitemGetTypeditem (i))

#define vlongitemGetMaxLength(f)                                             \
    vtypeditemGetMaxLength (                                                 \
        vlongitemGetTypeditem (f))

#define vlongitemSetMaxLength(f, l)                                          \
    vtypeditemSetMaxLength (                                                 \
        vlongitemGetTypeditem (f),                                           \
        (l))

#define vlongitemFocus(f)                                                    \
    vtypeditemFocus (                                                        \
        vlongitemGetTypeditem (f))

#define vlongitemUnfocus(f)                                                  \
    vtypeditemUnfocus (                                                      \
        vlongitemGetTypeditem (f))

#define vlongitemTextGetTypeditemText(t)                                     \
    ((vtypeditemText *) (t))

#define vlongitemTextGetText(t)                                              \
    vtypeditemTextGetText (                                                  \
        vlongitemTextGetTypeditemText (t))

#define vlongitemTextGetLongitem(t)                                          \
    ((vlongitem *)                                                           \
        vtypeditemTextGetTypeditem (                                         \
            vlongitemTextGetTypeditemText (t)))

#define vlongitemIncrement(i, d)                                             \
    vtypeditemIncrement (                                                    \
        vlongitemGetTypeditem (i),                                           \
        (d))

/*
 * * * * * * * * * * PRIVATE FUNCTION MESSAGE DEFINITIONS * * * * * * * * * *
 */

#define vlongitemCopy(f, t)                                                  \
    vclassSend (                                                             \
        vlongitemGetClass (f),                                               \
        vobjectCOPY,                                                         \
        (f, t))

#define vlongitemStore(f, t)                                                 \
    vclassSend (                                                             \
        vlongitemGetClass (f),                                               \
        vobjectSTORE,                                                        \
        (f, t))

#define vlongitemGetValue(f)                                                 \
    vclassSend (                                                             \
        vlongitemGetClass (f),                                               \
        vlongitemGET_VALUE,                                                  \
        (f))

#define vlongitemSetValue(f, v)                                              \
    vclassSend (                                                             \
        vlongitemGetClass (f),                                               \
        vlongitemSET_VALUE,                                                  \
        (f, v))

#define vlongitemSetIncrement(f, i)                                          \
    vclassSend (                                                             \
        vlongitemGetClass (f),                                               \
        vlongitemSET_INCREMENT,                                              \
        (f, i))

/*
 * * * * * * * * * LONG ITEM GLOBAL VARIABLES * * * * * * * * * *
 */

vportEND_CPLUSPLUS_EXTERN_C

#endif /* vlongitemINCLUDED */

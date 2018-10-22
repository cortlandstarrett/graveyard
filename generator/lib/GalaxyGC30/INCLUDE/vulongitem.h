/* $Id: vulongitem.h,v 1.10 1997/10/23 17:43:14 garyk Exp $ */

/* vulongitem - an unsigned long integer input item */

#ifndef vulongitemINCLUDED
#define vulongitemINCLUDED 1

#ifndef vportINCLUDED
#include <vport.h>
#endif

#ifndef vscribeINCLUDED
#include vscribeHEADER
#endif

#ifndef vcharINCLUDED
#include vcharHEADER
#endif

#ifndef veventINCLUDED
#include veventHEADER
#endif

#ifndef vresourceINCLUDED
#include vresourceHEADER
#endif

#ifndef vclassINCLUDED
#include vclassHEADER
#endif

#ifndef vobjectINCLUDED
#include vobjectHEADER
#endif

#ifndef vtextINCLUDED
#include vtextHEADER
#endif

#ifndef vformatINCLUDED
#include vformatHEADER
#endif

#ifndef vtypeditemINCLUDED
#include vtypeditemHEADER
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * * * * * * * * * TYPE AND STRUCTURE DEFINITIONS * * * * * * * * * *
 */

/*
 * * UNSIGNED LONG ITEM FORWARD DECLARATION
 */
typedef struct vulongitem
               vulongitem;

typedef struct vulongitemClass
               vulongitemClass;

typedef vtypeditemText
        vulongitemText;

typedef vtypeditemTextClass
        vulongitemTextClass;

/*
 * * CLIENT NOTIFICATION PROCEDURE PROTOTYPE
 */
typedef void (*vulongitemNoteProc) (
    vulongitem *item,
    int         msg
);

/*
 * * CLIENT VALIDATION PROCEDURE PROTOTYPE
 */
typedef vbool (*vulongitemValidatorProc) (
    vulongitem *item
);

/*
 * * INCREMENT CODES
 */
enum
{
    vulongitemUP = vtypeditemUP,
    vulongitemDOWN,
    vulongitemNO_DIRECTION
};

/*
 * * NOTIFICATION CODES
 */
enum
{
    vulongitemNOTIFY_FOCUS = vtypeditemNOTIFY_FOCUS,
    vulongitemNOTIFY_UNFOCUS,
    vulongitemNOTIFY_VALID,
    vulongitemNOTIFY_PARTIALLY_VALID,
    vulongitemNOTIFY_INVALID,
    vulongitemNOTIFY_NEXT
};

/*
 * * UNSIGNED LONG INSTANCE DEFINITION
 */
struct vulongitem
{
    vtypeditem    typeditem;
    unsigned long value;
    unsigned long flags;
    int           increment;
};

/*
 * * UNSIGNED LONG CLASS DEFINITION
 */
#define vulongitemCLASS(SUPER, ITEM, NOTIFY, VALIDATOR_PROC)                 \
                                                                             \
    vtypeditemCLASS (SUPER, ITEM, NOTIFY, VALIDATOR_PROC);                   \
                                                                             \
    vclassMETHOD_RET (vulongitemGET_VALUE, unsigned long,                    \
        (ITEM *item));                                                       \
    vclassMETHOD     (vulongitemSET_VALUE,                                   \
        (ITEM *item, unsigned long value));                                  \
    vclassMETHOD     (vulongitemSET_INCREMENT,                               \
        (ITEM *item, long increment))

struct vulongitemClass
{
    vulongitemCLASS (
        vulongitemClass,
        vulongitem,
        vulongitemNoteProc,
        vulongitemValidatorProc);
};

/*
 * * * * * * * * * UNSIGNED LONG ITEM FUNCTION PROTOTYPES * * * * * * * * * *
 */

void
vulongitemStartup (
    void
);

vulongitemClass *
vulongitemGetDefaultClass (
    void
);

vulongitem *
vulongitemCreate (
    void
);

vulongitem *
vulongitemCreateOfClass (
    vulongitemClass *clas
);

vulongitemClass *
vulongitemGetClass (
    vulongitem *item
);

vtypeditem *
vulongitemGetTypeditem (
    vulongitem *item
);

vdialogItem *
vulongitemGetItem (
    vulongitem *item
);

vulongitem *
vulongitemClone (
    vulongitem *item
);

void
vulongitemCopy (
    vulongitem *src,
    vulongitem *dest
);

void
vulongitemCopyInit (
    vulongitem *src,
    vulongitem *dest
);

void
vulongitemInit (
    vulongitem *item
);

void
vulongitemInitOfClass (
    vulongitem      *item,
    vulongitemClass *clas
);

void
vulongitemDump (
    vulongitem *item,
    FILE       *stream
);

void
vulongitemDestroy (
    vulongitem *item
);

vulongitem *
vulongitemLoad (
    vresource resource
);

void
vulongitemLoadInit (
    vulongitem *item,
    vresource  resource
);

void
vulongitemStore (
    vulongitem *item,
    vresource  resource
);

void *
vulongitemGetData (
    vulongitem *item
);

void
vulongitemSetData (
    vulongitem *item,
    const void *data
);

vulongitemNoteProc
vulongitemGetNotify (
    vulongitem *item
);

void
vulongitemSetNotify (
    vulongitem         *item,
    vulongitemNoteProc  notify
);

void
vulongitemNotify (
    vulongitem *item,
    int         msg
);

vulongitemValidatorProc
vulongitemGetValidator (
    vulongitem *item
);

void
vulongitemSetValidator (
    vulongitem              *item,
    vulongitemValidatorProc  validatorProc
);

vulongitemText *
vulongitemGetTextData (
    vulongitem *item
);

void
vulongitemSetTextData (
    vulongitem     *item,
    vulongitemText *text
);

vstr *
vulongitemGetString (
    vulongitem *item
);

void
vulongitemSetString (
    vulongitem  *item,
    const vchar *text
);

vstr *
vulongitemGetTransientString (
    vulongitem *item
);

vscribe *
vulongitemGetTransientStringScribed (
    vulongitem *item
);

int
vulongitemGetLength (
    vulongitem *item
);

vscribe *
vulongitemGetStringScribed (
    vulongitem *item
);

void
vulongitemSetStringScribed (
    vulongitem *item,
    vscribe    *scribe
);

vscribe *
vulongitemGetSubstrScribed (
    vulongitem *item,
    long       begin,
    long       len
);

void
vulongitemInsertString (
    vulongitem *item,
    long       selStart,
    long       selLength,
    vchar     *s,
    long       len
);

void
vulongitemDeleteString (
    vulongitem *item,
    long       selStart,
    long       selLength
);

void
vulongitemSelectRange (
    vulongitem *item, 
    long       begin,
    long       len
);

void
vulongitemSelectAll (
    vulongitem *item
);

vtextSelection *
vulongitemGetSelection (
    vulongitem *item
);

void
vulongitemSetSelection (
    vulongitem     *item,
    vtextSelection *selection
);

vscribe *
vulongitemGetSelectionScribed (
    vulongitem *item
);

vulongitemText *
vulongitemCreateTextData (
    vulongitem *item
);

vcolor *
vulongitemGetForeground (
    vulongitem *item
);

void
vulongitemSetForeground (
    vulongitem *item,
    vcolor     *fg
);

int
vulongitemGetJustification (
    vulongitem *item
);

void
vulongitemSetJustification (
    vulongitem *item,
    int         justification
);

vobservable *
vulongitemGetField (
    vulongitem *item
);

void
vulongitemSetField (
    vulongitem *item,
    vobservable *field
);

void
vulongitemSetObserving (
    vulongitem *item,
    vbool       isObserving
);

vbool
vulongitemIsObserving (
    vulongitem *item
);

vformatULong *
vulongitemGetFormat (
    vulongitem *item
);

void
vulongitemSetFormat (
    vulongitem   *item,
    vformatULong *format
);

void
vulongitemSetFormatOwned (
    vulongitem   *item,
    vformatULong *format
);

void
vulongitemSetEditable (
    vulongitem *item
);

vbool
vulongitemIsValid (
    vulongitem *item
);

vbool
vulongitemIsDirty (
    vulongitem *item
);

void
vulongitemSetDirty (
    vulongitem *item,
    vbool       dirty
);

vbool
vulongitemIsOneLine (
    vulongitem *item
);

void
vulongitemSetOneLine (
    vulongitem *item,
    vbool       oneLine
);

vbool
vulongitemIsSelectable (
    vulongitem *item
);

void
vulongitemSetSelectable (
    vulongitem *item,
    vbool       selectable
);

vbool
vulongitemIsModifiable (
    vulongitem *item
);

void
vulongitemSetModifiable (
    vulongitem *item,
    vbool       modifiable
);

vbool
vulongitemHasBeepIfInvalid (
    vulongitem *item
);

void
vulongitemSetBeepIfInvalid (
    vulongitem *item,
    vbool       beepIfInvalid
);

vbool
vulongitemHasKeepFocusIfInvalid (
    vulongitem *item
);

void
vulongitemSetKeepFocusIfInvalid (
    vulongitem *item,
    vbool       flag
);

vbool
vulongitemHasNeverInvalid (
    vulongitem *item
);

void
vulongitemSetNeverInvalid (
    vulongitem *item,
    vbool       flag
);

vbool
vulongitemHasValidateOnChange (
    vulongitem *item
);

void
vulongitemSetValidateOnChange (
    vulongitem *item,
    vbool       flag
);

vbool
vulongitemIsNull (
    vulongitem *item
);

void
vulongitemSetNull (
    vulongitem *item,
    vbool       isNull
);

void
vulongitemSetEmptyIsNull (
    vulongitem *item,
    vbool       emptyIsNull
);

vbool
vulongitemHasEmptyIsNull (
    vulongitem *item
);

void
vulongitemSetInformingField (
    vulongitem *item,
    vbool       informing
);

vbool
vulongitemIsInformingField (
    vulongitem *item
);

long
vulongitemGetMaxLength (
    vulongitem *item
);

void
vulongitemSetMaxLength (
    vulongitem *item,
    long        maxLength
);

void
vulongitemFocus (
    vulongitem *item
);

void
vulongitemUnfocus (
    vulongitem *item
);

unsigned long
vulongitemGetValue (
    vulongitem *item
);

void
vulongitemSetValue (
    vulongitem    *item,
    unsigned long  value
);

long
vulongitemGetIncrement (
    vulongitem *item
);

void
vulongitemSetIncrement (
    vulongitem *item,
    long        increment
);

void
vulongitemIncrement (
    vulongitem *item,
    int        dir
);

vulongitem *
vulongitemTextGetUlongitem (
    vulongitemText *text
);

vtypeditemText *
vulongitemTextGetTypeditemText (
    vulongitemText *text
);

vtext *
vulongitemTextGetText (
    vulongitemText *text
);

/*
 * * * * * * * * * * PRIVATE MACRO DEFINITIONS * * * * * * * * * *
 */

#define vulongitemGetTypeditem(f)                                            \
    vportBASE_OBJECT (                                                       \
        (f),                                                                 \
        typeditem)

#define vulongitemGetItem(f)                                                 \
    vtypeditemGetItem (                                                      \
        vulongitemGetTypeditem (f))

#define vulongitemCreateOfClass(c)                                           \
    ((vulongitem *)                                                          \
        vtypeditemCreateOfClass (                                            \
            (vtypeditemClass *) (c)))

#define vulongitemCreate()                                                   \
    vulongitemCreateOfClass (                                                \
        vulongitemGetDefaultClass ())

#define vulongitemClone(f)                                                   \
    ((vulongitem *)                                                          \
        vtypeditemClone (                                                    \
            vulongitemGetTypeditem (f)))

#define vulongitemInitOfClass(f, c)                                          \
    vtypeditemInitOfClass (                                                  \
        vulongitemGetTypeditem (f),                                          \
        (vulongitemClass *) (c))

#define vulongitemGetClass(f)                                                \
    ((vulongitemClass *)                                                     \
        vtypeditemGetClass (                                                 \
            vulongitemGetTypeditem (f)))

#define vulongitemInit(f)                                                    \
    vulongitemInitOfClass (                                                  \
        (f),                                                                 \
        vulongitemGetDefaultClass ());

#define vulongitemCopyInit(f, t)                                             \
    vtypeditemCopyInit (                                                     \
        vulongitemGetTypeditem (f),                                          \
        (vtypeditem *) (t))

#define vulongitemLoad(r)                                                    \
    ((vulongitem *)                                                          \
        vtypeditemLoad (                                                     \
            vulongitemGetTypeditem (r)))

#define vulongitemLoadInit(f, r)                                             \
    vtypeditemLoadInit (                                                     \
        vulongitemGetTypeditem (f),                                          \
        (r))

#define vulongitemDump(i, s)                                                 \
    vtypeditemDump (                                                         \
        vulongitemGetTypeditem (i),                                          \
        (s))

#define vulongitemDestroy(f)                                                 \
    vtypeditemDestroy (                                                      \
        vulongitemGetTypeditem (f))

#define vulongitemGetNotify(f)                                               \
    ((vulongitemNoteProc)                                                    \
        vtypeditemGetNotify (                                                \
            vulongitemGetTypeditem (f)))

#define vulongitemSetNotify(f, n)                                            \
    vtypeditemSetNotify (                                                    \
        vulongitemGetTypeditem (f),                                          \
        (vtypeditemNoteProc) (n))

#define vulongitemNotify(u, m)                                               \
    vtypeditemNotify (                                                       \
        vulongitemGetTypeditem (u),                                          \
        (m))

#define vulongitemGetValidator(f)                                            \
    ((vulongitemValidatorProc)                                               \
        vtypeditemGetValidator (                                             \
            vulongitemGetTypeditem (f)))

#define vulongitemSetValidator(f, p)                                         \
    vtypeditemSetValidator (                                                 \
        vulongitemGetTypeditem (f),                                          \
        (vtypeditemValidatorProc) (p))

#define vulongitemGetData(f)                                                 \
    vtypeditemGetData (                                                      \
        vulongitemGetTypeditem (f))

#define vulongitemSetData(f, d)                                              \
    vtypeditemSetData (                                                      \
        vulongitemGetTypeditem (f),                                          \
        (d))

#define vulongitemGetTextData(f)                                             \
    vtypeditemGetTextData (                                                  \
        vulongitemGetTypeditem (f))

#define vulongitemSetTextData(f, t)                                          \
    vtypeditemSetTextData (                                                  \
        vulongitemGetTypeditem (f),                                          \
        vulongitemTextGetTypeditemText (t))

#define vulongitemGetString(f)                                               \
    vtypeditemGetString (                                                    \
        vulongitemGetTypeditem (f))

#define vulongitemSetString(f, s)                                            \
    vtypeditemSetString (                                                    \
        vulongitemGetTypeditem (f),                                          \
        (s))

#define vulongitemGetTransientString(f)                                      \
    vtypeditemGetTransientString (                                           \
        vulongitemGetTypeditem (f))

#define vulongitemGetTransientStringScribed(f)                               \
    vtypeditemGetTransientStringScribed (                                    \
        vulongitemGetTypeditem (f))

#define vulongitemGetLength(f)                                               \
    vtypeditemGetLength (                                                    \
        vulongitemGetTypeditem (f))

#define vulongitemGetStringScribed(f)                                        \
    vtypeditemGetStringScribed (                                             \
        vulongitemGetTypeditem (f))

#define vulongitemSetStringScribed(f, s)                                     \
    vtypeditemSetStringScribed (                                             \
        vulongitemGetTypeditem (f),                                          \
        (s))

#define vulongitemGetSubstrScribed(f, b, l)                                  \
    vtypeditemGetSubstrScribed (                                             \
        vulongitemGetTypeditem (f),                                          \
        (b),                                                                 \
        (l))

#define vulongitemInsertString(f, start, len, str, strLen)                   \
    vtypeditemInsertString (                                                 \
        vulongitemGetTypeditem (f),                                          \
        (start),                                                             \
        (len),                                                               \
        (str),                                                               \
        (strLen))

#define vulongitemDeleteString(f, start, len)                                \
    vtypeditemDeleteString (                                                 \
        vulongitemGetTypeditem (f),                                          \
        (start),                                                             \
        (len))

#define vulongitemSelectRange(f, b, l)                                       \
    vtypeditemSelectRange (                                                  \
        vulongitemGetTypeditem (f),                                          \
        (b),                                                                 \
        (l))

#define vulongitemSelectAll(f)                                               \
    vtypeditemSelectAll (                                                    \
        vulongitemGetTypeditem (f))

#define vulongitemGetSelection(f)                                            \
    vtypeditemGetSelection (                                                 \
        vulongitemGetTypeditem (f))

#define vulongitemSetSelection(f, s)                                         \
    vtypeditemSetSelection (                                                 \
        vulongitemGetTypeditem (f),                                          \
        (s))

#define vulongitemGetSelectionScribed(f)                                     \
    vtypeditemGetSelectionScribed (                                          \
        vulongitemGetTypeditem (f))

#define vulongitemCreateTextData(f)                                          \
    vtypeditemCreateTextData (                                               \
        vulongitemGetTypeditem (f))

#define vulongitemSetEditable(f)                                             \
    vtypeditemSetEditable (                                                  \
        vulongitemGetTypeditem (f))

#define vulongitemIsValid(f)                                                 \
    vtypeditemIsValid (                                                      \
        vulongitemGetTypeditem (f))

#define vulongitemIsDirty(f)                                                 \
    vtypeditemIsDirty (                                                      \
        vulongitemGetTypeditem (f))

#define vulongitemSetDirty(f, d)                                             \
    vtypeditemSetDirty (                                                     \
        vulongitemGetTypeditem (f),                                          \
        (d))

#define vulongitemIsOneLine(f)                                               \
    vtypeditemIsOneLine (                                                    \
        vulongitemGetTypeditem (f))

#define vulongitemSetOneLine(f, d)                                           \
    vtypeditemSetOneLine (                                                   \
        vulongitemGetTypeditem (f),                                          \
        (d))

#define vulongitemIsSelectable(f)                                            \
    vtypeditemIsSelectable (                                                 \
        vulongitemGetTypeditem (f))

#define vulongitemSetSelectable(f, d)                                        \
    vtypeditemSetSelectable (                                                \
        vulongitemGetTypeditem (f),                                          \
        (d))

#define vulongitemIsModifiable(f)                                            \
    vtypeditemIsModifiable (                                                 \
        vulongitemGetTypeditem (f))

#define vulongitemSetModifiable(f, d)                                        \
    vtypeditemSetModifiable (                                                \
        vulongitemGetTypeditem (f),                                          \
        (d))

#define vulongitemHasBeepIfInvalid(f)                                        \
    vtypeditemHasBeepIfInvalid (                                             \
        vulongitemGetTypeditem (f))

#define vulongitemSetBeepIfInvalid(f, d)                                     \
    vtypeditemSetBeepIfInvalid (                                             \
        vulongitemGetTypeditem (f),                                          \
        (d))

#define vulongitemHasKeepFocusIfInvalid(f)                                   \
    vtypeditemHasKeepFocusIfInvalid (                                        \
        vulongitemGetTypeditem (f))

#define vulongitemSetKeepFocusIfInvalid(f, b)                                \
    vtypeditemSetKeepFocusIfInvalid (                                        \
        vulongitemGetTypeditem (f),                                          \
        (b))

#define vulongitemHasNeverInvalid(f)                                         \
    vtypeditemHasNeverInvalid (                                              \
        vulongitemGetTypeditem (f))

#define vulongitemSetNeverInvalid(f, b)                                      \
    vtypeditemSetNeverInvalid (                                              \
        vulongitemGetTypeditem (f),                                          \
        (b))

#define vulongitemHasValidateOnChange(f)                                     \
    vtypeditemHasValidateOnChange (                                          \
        vulongitemGetTypeditem (f))

#define vulongitemSetValidateOnChange(f, b)                                  \
    vtypeditemSetValidateOnChange (                                          \
        vulongitemGetTypeditem (f),                                          \
        (b))

#define vulongitemIsNull(i)                                                  \
    vtypeditemIsNull (                                                       \
        vulongitemGetTypeditem (i))

#define vulongitemSetNull(i, n)                                              \
    vtypeditemSetNull (                                                      \
        vulongitemGetTypeditem (i),                                          \
        (n))

#define vulongitemHasEmptyIsNull(i)                                          \
    vtypeditemHasEmptyIsNull (                                               \
        vulongitemGetTypeditem (i))

#define vulongitemSetEmptyIsNull(i, n)                                       \
    vtypeditemSetEmptyIsNull (                                               \
        vulongitemGetTypeditem (i),                                          \
        (n))

#define vulongitemSetInformingField(i, f)                                    \
    vtypeditemSetInformingField (                                            \
        vulongitemGetTypeditem (i),                                          \
        (f))

#define vulongitemIsInformingField(i)                                        \
    vtypeditemIsInformingField (                                             \
        vulongitemGetTypeditem (i))

#define vulongitemGetMaxLength(f)                                            \
    vtypeditemGetMaxLength (                                                 \
        vulongitemGetTypeditem (f))

#define vulongitemSetMaxLength(f, l)                                         \
    vtypeditemSetMaxLength (                                                 \
        vulongitemGetTypeditem (f),                                          \
        (l))

#define vulongitemFocus(f)                                                   \
    vtypeditemFocus (                                                        \
        vulongitemGetTypeditem (f))

#define vulongitemUnfocus(f)                                                 \
    vtypeditemUnfocus (                                                      \
        vulongitemGetTypeditem (f))

#define vulongitemGetFormat(f)                                               \
    ((vformatULong *)                                                        \
        vtypeditemGetFormat (                                                \
            vulongitemGetTypeditem (f)))

#define vulongitemSetFormat(f, p)                                            \
    vtypeditemSetFormat (                                                    \
        vulongitemGetTypeditem (f),                                          \
        (vformat *) (p))

#define vulongitemGetField(f)                                                \
    vtypeditemGetField (                                                     \
        vulongitemGetTypeditem (f))

#define vulongitemSetField(f, p)                                             \
    vtypeditemSetField (                                                     \
        vulongitemGetTypeditem (f),                                          \
        (p))

#define vulongitemIsObserving(i)                                             \
    vtypeditemIsObserving (                                                  \
        vulongitemGetTypeditem (i))

#define vulongitemSetObserving(i, o)                                         \
    vtypeditemSetObserving (                                                 \
        vulongitemGetTypeditem (i),                                          \
        (o))

#define vulongitemSetFormatOwned(f, p)                                       \
    vtypeditemSetFormatOwned (                                               \
        vulongitemGetTypeditem (f),                                          \
        (vformat *) (p))

#define vulongitemGetIncrement(f)                                            \
    ((f)->increment)

#define vulongitemIncrement(i, d)                                            \
    vtypeditemIncrement (                                                    \
        vulongitemGetTypeditem (i),                                          \
        (d))

#define vulongitemGetForeground(i)                                           \
    vtypeditemGetForeground (                                                \
        vulongitemGetTypeditem (i))

#define vulongitemSetForeground(i, c)                                        \
    vtypeditemSetForeground (                                                \
        vulongitemGetTypeditem (i),                                          \
        (c))

#define vulongitemGetJustification(f)                                        \
   vtypeditemGetJustification (                                              \
        vulongitemGetTypeditem (f))

#define vulongitemSetJustification(f, j)                                     \
   vtypeditemSetJustification (                                              \
        vulongitemGetTypeditem (f),                                          \
        (j))

#define vulongitemTextGetTypeditemText(t)                                    \
    ((vtypeditemText *) (t))

#define vulongitemTextGetText(t)                                             \
    vtypeditemTextGetText (                                                  \
        vulongitemTextGetTypeditemText (t))

#define vulongitemTextGetUlongitem(t)                                        \
    ((vulongitem *)                                                          \
        vtypeditemTextGetTypeditem (                                         \
            vulongitemTextGetTypeditemText (t)))

/*
 * * * * * * * * * * PRIVATE FUNCTION MESSAGE DEFINITIONS * * * * * * * * * *
 */

#define vulongitemCopy(f, t)                                                 \
    vclassSend (                                                             \
        vulongitemGetClass (f),                                              \
        vobjectCOPY,                                                         \
        (f, t))

#define vulongitemStore(f, t)                                                \
    vclassSend (                                                             \
        vulongitemGetClass (f),                                              \
        vobjectSTORE,                                                        \
        (f, t))

#define vulongitemGetValue(f)                                                \
    vclassSend (                                                             \
        vulongitemGetClass (f),                                              \
        vulongitemGET_VALUE,                                                 \
        (f))

#define vulongitemSetValue(f, v)                                             \
    vclassSend (                                                             \
        vulongitemGetClass (f),                                              \
        vulongitemSET_VALUE,                                                 \
        (f, v))

#define vulongitemSetIncrement(f, i)                                         \
    vclassSend (                                                             \
        vulongitemGetClass (f),                                              \
        vulongitemSET_INCREMENT,                                             \
        (f, i))

/*
 * * * * * * * * * UNSIGNED LONG ITEM GLOBAL VARIABLES * * * * * * * * * *
 */

vportEND_CPLUSPLUS_EXTERN_C

#endif /* vulongitemINCLUDED */

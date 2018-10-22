/* $Id: vboolitem.h,v 1.13 1997/06/27 01:50:05 robert Exp $ */

/* vboolitem - a boolean input item */

#ifndef vboolitemINCLUDED
#define vboolitemINCLUDED 1

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
 * * ITEM TYPE FORWARD DECLARATION
 */
typedef struct vboolitem
               vboolitem;

typedef struct vboolitemClass
               vboolitemClass;

/*
 * * BOOLEAN ITEM TEXT INSTANCE FORWARD DECLARATION
 */
typedef vtypeditemText
        vboolitemText;

/*
 * * BOOLEAN ITEM TEXT CLASS FORWARD DECLARATION
 */
typedef vtypeditemTextClass
        vboolitemTextClass;

/*
 * * CLIENT NOTIFICATION PROCEDURE PROTOTYPE
 */
typedef void (*vboolitemNoteProc) (
    vboolitem *item,
    int        msg
);

/*
 * * CLIENT VALIDATION PROCEDURE PROTOTYPE
 */
typedef vbool (*vboolitemValidatorProc) (
    vboolitem *item
);

/*
 * * INCREMENT CODES
 */
enum
{
    vboolitemUP = vtypeditemUP,
    vboolitemDOWN,
    vboolitemNO_DIRECTION
};

/*
 * * NOTIFICATION CODES
 */
enum
{
    vboolitemNOTIFY_FOCUS = vtypeditemNOTIFY_FOCUS,
    vboolitemNOTIFY_UNFOCUS,
    vboolitemNOTIFY_VALID,
    vboolitemNOTIFY_PARTIALLY_VALID,
    vboolitemNOTIFY_INVALID,
    vboolitemNOTIFY_NEXT
};

/*
 * * BOOLEAN ITEM INSTANCE DEFINITION
 */
struct vboolitem
{
    vtypeditem    typeditem;
    vbool         value;
    unsigned long flags;
};


/*
 * * BOOLEAN ITEM CLASS DEFINITION
 */
#define vboolitemCLASS(SUPER, ITEM, NOTIFY, VALIDATOR_PROC)                  \
                                                                             \
    vtypeditemCLASS (SUPER, ITEM, NOTIFY, VALIDATOR_PROC);                   \
                                                                             \
    vclassMETHOD_RET (vboolitemGET_VALUE, vbool,                             \
        (ITEM *item));                                                       \
    vclassMETHOD     (vboolitemSET_VALUE,                                    \
        (ITEM *item, vbool value));                                          \
    vclassMETHOD     (vboolitemTOGGLE,                                       \
        (ITEM *item))

struct vboolitemClass
{
    vboolitemCLASS (
        vboolitemClass,
        vboolitem,
        vboolitemNoteProc,
        vboolitemValidatorProc);
};

/*
 * * * * * * * * * BOOLEAN ITEM FUNCTION PROTOTYPES * * * * * * * * * *
 */

void
vboolitemStartup (
    void
);

vboolitemClass *
vboolitemGetDefaultClass (
    void
);

vboolitem *
vboolitemCreate (
    void
);

vboolitem *
vboolitemCreateOfClass (
    vboolitemClass *clas
);

vtypeditem *
vboolitemGetTypeditem (
    vboolitem *item
);

vdialogItem *
vboolitemGetItem (
    vboolitem *item
);

vboolitemClass *
vboolitemGetClass (
    vboolitem *item
);

vboolitem *
vboolitemClone (
    vboolitem *item
);

void
vboolitemCopy (
    vboolitem *src,
    vboolitem *dest
);

void
vboolitemCopyInit (
    vboolitem *src,
    vboolitem *dest
);

void
vboolitemInit (
    vboolitem *item
);

void
vboolitemInitOfClass (
    vboolitem       *item,
    vboolitemClass  *clas
);

void
vboolitemDump (
    vboolitem *item,
    FILE      *stream
);

void
vboolitemDestroy (
    vboolitem *item
);

vboolitem *
vboolitemLoad (
    vresource resource
);

void
vboolitemLoadInit (
    vboolitem *item,
    vresource  resource
);

void
vboolitemStore (
    vboolitem *item,
    vresource  resource
);

void *
vboolitemGetData (
    vboolitem *item
);

void
vboolitemSetData (
    vboolitem  *item,
    const void *data
);

vboolitemNoteProc
vboolitemGetNotify (
    vboolitem *item
);

void
vboolitemSetNotify (
    vboolitem         *item,
    vboolitemNoteProc *notify
);

void
vboolitemNotify (
    vboolitem *item,
    int        msg
);

vboolitemValidatorProc
vboolitemGetValidator (
    vboolitem *item
);

void
vboolitemSetValidator (
    vboolitem              *item,
    vboolitemValidatorProc  validatorProc
);

vboolitemText *
vboolitemGetTextData (
    vboolitem *item
);

void
vboolitemSetTextData (
    vboolitem     *item,
    vboolitemText *text
);

vstr *
vboolitemGetString (
    vboolitem *item
);

void
vboolitemSetString (
    vboolitem   *item,
    const vchar *text
);

vstr *
vboolitemGetTransientString (
    vboolitem *item
);

vscribe *
vboolitemGetTransientStringScribed (
    vboolitem *item
);

int
vboolitemGetLength (
    vboolitem *item
);

vscribe *
vboolitemGetStringScribed (
    vboolitem *item
);

void
vboolitemSetStringScribed (
    vboolitem *item,
    vscribe   *scribe
);

vscribe *
vboolitemGetSubstrScribed (
    vboolitem *item,
    long       begin,
    long       len
);

void
vboolitemInsertString (
    vboolitem *item,
    long       selStart,
    long       selLength,
    vchar     *s,
    long       len
);

void
vboolitemDeleteString (
    vboolitem *item,
    long       selStart,
    long       selLength
);

void
vboolitemSelectRange (
    vboolitem *item, 
    long       begin,
    long       len
);

void
vboolitemSelectAll (
    vboolitem *item
);

vtextSelection *
vboolitemGetSelection (
    vboolitem *item
);

void
vboolitemSetSelection (
    vboolitem      *item,
    vtextSelection *selection
);

vscribe *
vboolitemGetSelectionScribed (
    vboolitem *item
);

vboolitemText *
vboolitemCreateTextData (
    vboolitem *item
);

vcolor *
vboolitemGetForeground (
    vboolitem *item
);

void
vboolitemSetForeground (
    vboolitem *item,
    vcolor    *fg
);

int
vboolitemGetJustification (
    vboolitem *item
);

void
vboolitemSetJustification (
    vboolitem *item,
    int        justification
);

vformatBoolean *
vboolitemGetFormat (
    vboolitem *item
);

void
vboolitemSetFormat (
    vboolitem      *item,
    vformatBoolean *format
);

void
vboolitemSetFormatOwned (
    vboolitem      *item,
    vformatBoolean *format
);

vobservable *
vboolitemGetField (
    vboolitem *item
);

void
vboolitemSetField (
    vboolitem *item,
    vobservable *field
);

void
vboolitemSetObserving (
    vboolitem *item,
    vbool      observing
);

vbool
vboolitemIsObserving (
    vboolitem *item
);

vbool
vboolitemGetValue (
    vboolitem *item
);

void
vboolitemSetValue (
    vboolitem *item,
    vbool      value
);

void
vboolitemToggle (
    vboolitem *item
);

vbool
vboolitemIsValid (
    vboolitem *item
);

vbool
vboolitemIsDirty (
    vboolitem *item
);

void
vboolitemSetDirty (
    vboolitem *item,
    vbool      dirty
);

vbool
vboolitemIsSelectable (
    vboolitem *item
);

void
vboolitemSetSelectable (
    vboolitem *item,
    vbool       selectable
);

vbool
vboolitemIsModifiable (
    vboolitem *item
);

void
vboolitemSetModifiable (
    vboolitem *item,
    vbool       modifiable
);

vbool
vboolitemIsStatic (
    vboolitem *item
);

void
vboolitemSetStatic (
    vboolitem *item
);

vbool
vboolitemHasBeepIfInvalid (
    vboolitem *item
);

void
vboolitemSetBeepIfInvalid (
    vboolitem *item,
    vbool      beep
);

vbool
vboolitemHasKeepFocusIfInvalid (
    vboolitem *item
);

void
vboolitemSetKeepFocusIfInvalid (
    vboolitem *item,
    vbool      flag
);

vbool
vboolitemHasNeverInvalid (
    vboolitem *item
);

void
vboolitemSetNeverInvalid (
    vboolitem *item,
    vbool      flag
);

vbool
vboolitemHasValidateOnChange (
    vboolitem *item
);

void
vboolitemSetValidateOnChange (
    vboolitem *item,
    vbool      flag
);

vbool
vboolitemIsNull (
    vboolitem *item
);

void
vboolitemSetNull (
    vboolitem *item,
    vbool      isNull
);

void
vboolitemSetEmptyIsNull (
    vboolitem *item,
    vbool      emptyIsNull
);

vbool
vboolitemHasEmptyIsNull (
    vboolitem *item
);

void
vboolitemSetInformingField (
    vboolitem *item,
    vbool      informing
);

vbool
vboolitemIsInformingField (
    vboolitem *item
);

void
vboolitemFocus (
    vboolitem *item
);

void
vboolitemUnfocus (
    vboolitem *item
);

void
vboolitemIncrement (
    vboolitem *item,
    int        direction
);

void
vboolitemSync (
    vboolitem *item
);

vboolitem *
vboolitemTextGetBoolitem (
    vboolitemText *text
);

vtypeditemText *
vboolitemTextGetTypeditemText (
    vboolitemText *text
);

vtext *
vboolitemTextGetText (
    vboolitemText *text
);

/*
 * * * * * * * * * * PRIVATE MACRO DEFINITIONS * * * * * * * * * *
 */

#define vboolitemGetTypeditem(f)                                             \
    vportBASE_OBJECT (                                                       \
        (f),                                                                 \
        typeditem)

#define vboolitemGetItem(f)                                                  \
    vtypeditemGetItem (                                                      \
        vboolitemGetTypeditem (f))

#define vboolitemGetClass(f)                                                 \
    ((vboolitemClass *)                                                      \
        vtypeditemGetClass (                                                 \
            vboolitemGetTypeditem (f)))

#define vboolitemCreateOfClass(c)                                            \
    ((vboolitem *)                                                           \
        vtypeditemCreateOfClass (                                            \
            (vtypeditemClass *) (c)))

#define vboolitemCreate()                                                    \
    vboolitemCreateOfClass (                                                 \
        vboolitemGetDefaultClass ())

#define vboolitemClone(f)                                                    \
    ((vboolitem *)                                                           \
        vtypeditemClone (                                                    \
            vboolitemGetTypeditem(f)))

#define vboolitemInitOfClass(f, c)                                           \
    vtypeditemInitOfClass (                                                  \
        vboolitemGetTypeditem (f),                                           \
        (vboolitemClass *) (c))

#define vboolitemInit(f)                                                     \
    vboolitemInitOfClass (                                                   \
        (f),                                                                 \
        vboolitemGetDefaultClass ());

#define vboolitemCopyInit(f, t)                                              \
    vtypeditemCopyInit (                                                     \
        vboolitemGetTypeditem (f),                                           \
        (vtypeditem *) (t))

#define vboolitemLoad(r)                                                     \
    ((vboolitem *)                                                           \
        vtypeditemLoad (                                                     \
        vboolitemGetTypeditem (r)))

#define vboolitemLoadInit(f, r)                                              \
    vtypeditemLoadInit (                                                     \
        vboolitemGetTypeditem (f),                                           \
        (r))

#define vboolitemDump(i, s)                                                  \
    vtypeditemDump (                                                         \
        vboolitemGetTypeditem (i),                                           \
        (s))

#define vboolitemDestroy(f)                                                  \
    vtypeditemDestroy (                                                      \
        vboolitemGetTypeditem (f))

#define vboolitemGetNotify(f)                                                \
    ((vboolitemNoteProc)                                                     \
        vtypeditemGetNotify (                                                \
            vboolitemGetTypeditem (f)))

#define vboolitemSetNotify(f, n)                                             \
    vtypeditemSetNotify (                                                    \
        vboolitemGetTypeditem (f),                                           \
        (vtypeditemNoteProc) (n))

#define vboolitemNotify(b, m)                                                \
    vtypeditemNotify (                                                       \
        vboolitemGetTypeditem (b),                                           \
        (m))

#define vboolitemGetValidator(f)                                             \
    ((vboolitemValidatorProc)                                                \
        vtypeditemGetValidator (                                             \
            vboolitemGetTypeditem (f)))

#define vboolitemSetValidator(f, p)                                          \
    vtypeditemSetValidator (                                                 \
        vboolitemGetTypeditem (f),                                           \
        (vtypeditemValidatorProc) (p))

#define vboolitemGetData(f)                                                  \
    vtypeditemGetData (                                                      \
        vboolitemGetTypeditem (f))

#define vboolitemSetData(f, d)                                               \
    vtypeditemSetData (                                                      \
        vboolitemGetTypeditem (f),                                           \
        (d))

#define vboolitemGetString(f)                                                \
    vtypeditemGetString (                                                    \
        vboolitemGetTypeditem (f))

#define vboolitemSetString(f, s)                                             \
    vtypeditemSetString (                                                    \
        vboolitemGetTypeditem (f),                                           \
        (s))

#define vboolitemGetTransientString(f)                                       \
    vtypeditemGetTransientString (                                           \
        vboolitemGetTypeditem (f))

#define vboolitemGetTransientStringScribed(f)                                \
    vtypeditemGetTransientStringScribed (                                    \
        vboolitemGetTypeditem (f))

#define vboolitemGetLength(f)                                                \
    vtypeditemGetLength (                                                    \
        vboolitemGetTypeditem (f))

#define vboolitemGetStringScribed(f)                                         \
    vtypeditemGetStringScribed (                                             \
        vboolitemGetTypeditem (f))

#define vboolitemSetStringScribed(f, s)                                      \
    vtypeditemSetStringScribed (                                             \
        vboolitemGetTypeditem (f),                                           \
        (s))

#define vboolitemGetSubstrScribed(f, b, l)                                   \
    vtypeditemGetSubstrScribed (                                             \
        vboolitemGetTypeditem (f),                                           \
        (b),                                                                 \
        (l))

#define vboolitemInsertString(f, start, len, str, strLen)                    \
    vtypeditemInsertString (                                                 \
        vboolitemGetTypeditem (f),                                           \
        (start),                                                             \
        (len),                                                               \
        (str),                                                               \
        (strLen))

#define vboolitemDeleteString(f, start, len)                                 \
    vtypeditemDeleteString (                                                 \
        vboolitemGetTypeditem (f),                                           \
        (start),                                                             \
        (len))

#define vboolitemCreateTextData(f)                                           \
    vtypeditemCreateTextData (                                               \
        vboolitemGetTypeditem (f))

#define vboolitemSelectRange(f, b, l)                                        \
    vtypeditemSelectRange (                                                  \
        vboolitemGetTypeditem (f),                                           \
        (b),                                                                 \
        (l))

#define vboolitemSelectAll(f)                                                \
    vtypeditemSelectAll (                                                    \
        vboolitemGetTypeditem (f))

#define vboolitemGetSelection(f)                                             \
    vtypeditemGetSelection (                                                 \
        vboolitemGetTypeditem (f))

#define vboolitemSetSelection(f, s)                                          \
    vtypeditemSetSelection (                                                 \
        vboolitemGetTypeditem (f),                                           \
        (s))

#define vboolitemGetSelectionScribed(f)                                      \
    vtypeditemGetSelectionScribed (                                          \
        vboolitemGetTypeditem (f))

#define vboolitemGetTextData(f)                                              \
    ((vboolitemText *)                                                       \
        vtypeditemGetTextData (                                              \
            vboolitemGetTypeditem (f)))

#define vboolitemSetTextData(f, t)                                           \
    vtypeditemSetTextData (                                                  \
        vboolitemGetTypeditem (f),                                           \
        vboolitemTextGetTypeditemText(t))

#define vboolitemIsValid(f)                                                  \
    vtypeditemIsValid (                                                      \
        vboolitemGetTypeditem (f))

#define vboolitemIsDirty(f)                                                  \
    vtypeditemIsDirty (                                                      \
        vboolitemGetTypeditem (f))

#define vboolitemSetDirty(f, d)                                              \
    vtypeditemSetDirty (                                                     \
        vboolitemGetTypeditem (f),                                           \
        (d))

#define vboolitemGetFormat(f)                                                \
    ((vformatBoolean *)                                                      \
        vtypeditemGetFormat (                                                \
        vboolitemGetTypeditem (f)))

#define vboolitemSetFormat(f, p)                                             \
    vtypeditemSetFormat (                                                    \
        vboolitemGetTypeditem (f),                                           \
        (vformat *) (p))

#define vboolitemSetFormatOwned(f, p)                                        \
    vtypeditemSetFormatOwned (                                               \
        vboolitemGetTypeditem (f),                                           \
        (vformat *) (p))

#define vboolitemGetField(f)                                                 \
    vtypeditemGetField (                                                     \
        vboolitemGetTypeditem (f))

#define vboolitemSetField(f, p)                                              \
    vtypeditemSetField (                                                     \
        vboolitemGetTypeditem (f),                                           \
        (p))

#define vboolitemIsObserving(i)                                              \
    vtypeditemIsObserving (                                                  \
        vboolitemGetTypeditem (i))

#define vboolitemSetObserving(i, o)                                          \
    vtypeditemSetObserving (                                                 \
        vboolitemGetTypeditem (i),                                           \
        (o))

#define vboolitemGetForeground(i)                                            \
    vtypeditemGetForeground (                                                \
        vboolitemGetTypeditem (i))

#define vboolitemSetForeground(i, c)                                         \
    vtypeditemSetForeground (                                                \
        vboolitemGetTypeditem (i),                                           \
        (c))

#define vboolitemGetJustification(f)                                         \
   vtypeditemGetJustification (                                              \
        vboolitemGetTypeditem (f))

#define vboolitemSetJustification(f, j)                                      \
   vtypeditemSetJustification (                                              \
        vboolitemGetTypeditem (f),                                           \
        (j))

#define vboolitemIsSelectable(f)                                             \
    vtypeditemIsSelectable (                                                 \
        vboolitemGetTypeditem (f))

#define vboolitemSetSelectable(f, s)                                         \
    vtypeditemSetSelectable (                                                \
        vboolitemGetTypeditem (f),                                           \
        (s))

#define vboolitemIsModifiable(f)                                             \
    vtypeditemIsModifiable (                                                 \
        vboolitemGetTypeditem (f))

#define vboolitemSetModifiable(f, m)                                         \
    vtypeditemSetModifiable (                                                \
        vboolitemGetTypeditem (f),                                           \
        (m))

#define vboolitemIsStatic(f)                                                 \
    vtypeditemIsStatic (                                                     \
        vboolitemGetTypeditem (f))

#define vboolitemSetStatic(f)                                                \
    vtypeditemSetStatic (                                                    \
        vboolitemGetTypeditem (f))

#define vboolitemHasBeepIfInvalid(f)                                         \
    vtypeditemHasBeepIfInvalid (                                             \
        vboolitemGetTypeditem (f))

#define vboolitemSetBeepIfInvalid(f, l)                                      \
    vtypeditemSetBeepIfInvalid (                                             \
        vboolitemGetTypeditem (f),                                           \
        (l))

#define vboolitemHasKeepFocusIfInvalid(f)                                    \
    vtypeditemHasKeepFocusIfInvalid (                                        \
        vboolitemGetTypeditem (f))

#define vboolitemSetKeepFocusIfInvalid(f, b)                                 \
    vtypeditemSetKeepFocusIfInvalid (                                        \
        vboolitemGetTypeditem (f),                                           \
        (b))

#define vboolitemHasNeverInvalid(f)                                          \
    vtypeditemHasNeverInvalid (                                              \
        vboolitemGetTypeditem (f))

#define vboolitemSetNeverInvalid(f, b)                                       \
    vtypeditemSetNeverInvalid (                                              \
        vboolitemGetTypeditem (f),                                           \
        (b))

#define vboolitemHasValidateOnChange(f)                                      \
    vtypeditemHasValidateOnChange (                                          \
        vboolitemGetTypeditem (f))

#define vboolitemSetValidateOnChange(f, b)                                   \
    vtypeditemSetValidateOnChange (                                          \
        vboolitemGetTypeditem (f),                                           \
        (b))

#define vboolitemIsNull(i)                                                   \
    vtypeditemIsNull (                                                       \
        vboolitemGetTypeditem (i))

#define vboolitemSetNull(i, n)                                               \
    vtypeditemSetNull (                                                      \
        vboolitemGetTypeditem (i),                                           \
        (n))

#define vboolitemHasEmptyIsNull(i)                                           \
    vtypeditemHasEmptyIsNull (                                               \
        vboolitemGetTypeditem (i))

#define vboolitemSetEmptyIsNull(i, n)                                        \
    vtypeditemSetEmptyIsNull (                                               \
        vboolitemGetTypeditem (i),                                           \
        (n))

#define vboolitemSetInformingField(i, f)                                     \
    vtypeditemSetInformingField (                                            \
        vboolitemGetTypeditem (i),                                           \
        (f))

#define vboolitemIsInformingField(i)                                         \
    vtypeditemIsInformingField (                                             \
        vboolitemGetTypeditem (i))

#define vboolitemFocus(f)                                                    \
    vtypeditemFocus (                                                        \
        vboolitemGetTypeditem (f))

#define vboolitemUnfocus(f)                                                  \
    vtypeditemUnfocus (                                                      \
        vboolitemGetTypeditem (f))

#define vboolitemIncrement(f, d)                                             \
    vtypeditemIncrement (                                                    \
        vboolitemGetTypeditem (f),                                           \
        (d))

#define vboolitemSync(f)                                                     \
    vtypeditemSync (                                                         \
        vboolitemGetTypeditem (f))

#define vboolitemTextGetBoolitem(t)                                          \
    ((vboolitem *)                                                           \
        vtypeditemTextGetTypeditem (                                         \
            vboolitemTextGetTypeditemText (t)))

#define vboolitemTextGetTypeditemText(t)                                     \
    ((vtypeditemText *)(t))

#define vboolitemTextGetText(t)                                              \
    vtypeditemTextGetText (                                                  \
        vboolitemTextGetTypeditemText (t))

/*
 * * * * * * * * * * PRIVATE FUNCTION MESSAGE DEFINITIONS * * * * * * * * * *
 */

#define vboolitemCopy(f, t)                                                  \
    vclassSend (                                                             \
        vboolitemGetClass (f),                                               \
        vobjectCOPY, (f, t))

#define vboolitemStore(f, t)                                                 \
    vclassSend (                                                             \
        vboolitemGetClass (f),                                               \
        vobjectSTORE,                                                        \
        (f, t))

#define vboolitemGetValue(f)                                                 \
    vclassSend (                                                             \
        vboolitemGetClass (f),                                               \
        vboolitemGET_VALUE,                                                  \
        (f))

#define vboolitemSetValue(f, v)                                              \
    vclassSend (                                                             \
        vboolitemGetClass (f),                                               \
        vboolitemSET_VALUE,                                                  \
        (f, v))

#define vboolitemToggle(f)                                                   \
    vclassSend (                                                             \
        vboolitemGetClass (f),                                               \
        vboolitemTOGGLE,                                                     \
        (f))

vportEND_CPLUSPLUS_EXTERN_C

#endif /* vboolitemINCLUDED */

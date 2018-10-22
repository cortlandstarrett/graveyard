/* $Id: vtypeditem.h,v 1.15 1997/10/23 17:43:14 garyk Exp $ */

#ifndef vtypeditemINCLUDED
#define vtypeditemINCLUDED 1

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

#ifndef vdialogINCLUDED
#include vdialogHEADER
#endif

#ifndef vtextitemINCLUDED
#include vtextitemHEADER
#endif

#ifndef vstritemINCLUDED
#include vstritemHEADER
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * * * * * * * * * TYPE AND STRUCTURE DEFINITIONS * * * * * * * * * *
 */

/*
 * * TYPED ITEM FORWARD DECLARATION
 */
typedef struct vtypeditem
               vtypeditem;

typedef struct vtypeditemClass
               vtypeditemClass;

typedef        vstritemText
               vtypeditemText;

typedef        vstritemTextClass
               vtypeditemTextClass;

/*
 * * CLIENT NOTIFICATION PROCEDURE PROTOTYPE
 */
typedef void (*vtypeditemNoteProc) (
        vtypeditem *item,
        int         msg
);

/*
 * * CLIENT VALIDATION PROCEDURE PROTOTYPE
 */
typedef vbool (*vtypeditemValidatorProc) (
    vtypeditem *item
);

/*
 * * NOTIFICATION CODES
 */
enum
{
    vtypeditemNOTIFY_FOCUS = vstritemNOTIFY_FOCUS,
    vtypeditemNOTIFY_UNFOCUS,
    vtypeditemNOTIFY_VALID,
    vtypeditemNOTIFY_PARTIALLY_VALID,
    vtypeditemNOTIFY_INVALID,
    vtypeditemNOTIFY_NEXT
};

/*
 * * INCREMENT CODES
 */
enum
{
    vtypeditemUP,
    vtypeditemDOWN,
    vtypeditemNO_DIRECTION
};

/*
 * * SELECTOR COMMAND DISCRIMINATORS
 */
enum
{
    vtypeditemSELECT_INCREMENT = vstritemNEXT_SELECT,
    vtypeditemSELECT_SYNC,
    vtypeditemNEXT_SELECT
};

/*
 * * TYPED ITEM INSTANCE DEFINITION
 */
struct vtypeditem
{
    vstritem stritem;
};

/*
 * * TYPED ITEM CLASS DEFINITION
 */
#define vtypeditemCLASS(SUPER, ITEM, NOTIFY, VALIDATOR_PROC)                 \
                                                                             \
    vstritemCLASS (SUPER, ITEM, NOTIFY, VALIDATOR_PROC);                     \
                                                                             \
    vclassMETHOD (vtypeditemINCREMENT,                                       \
        (ITEM *item, int direction));                                        \
    vclassMETHOD (vtypeditemSYNC,                                            \
        (ITEM *item))

struct vtypeditemClass
{
    vtypeditemCLASS (
        vtypeditemClass,
        vtypeditem,
        vtypeditemNoteProc,
        vtypeditemValidatorProc);
};


/*
 * * * * * * * * * TYPED ITEM FUNCTION PROTOTYPES * * * * * * * * * *
 */

void
vtypeditemStartup (
    void
);

vtypeditemClass *
vtypeditemGetDefaultClass (
    void
);

vtypeditemTextClass *
vtypeditemGetDefaultTextClass (
    void
);

vtypeditem *
vtypeditemCreate (
    void
);

vtypeditem *
vtypeditemCreateOfClass (
    vtypeditemClass *clas
);

vtypeditemClass *
vtypeditemGetClass (
    vtypeditem *item
);

vtypeditem *
vtypeditemClone (
    vtypeditem *item
);

void
vtypeditemCopy (
    vtypeditem *src,
    vtypeditem *dest
);

void
vtypeditemCopyInit (
    vtypeditem *src,
    vtypeditem *dest
);

void
vtypeditemInit (
    vtypeditem *item
);

void
vtypeditemInitOfClass (
    vtypeditem      *item,
    vtypeditemClass *clas
);

vstritem *
vtypeditemGetStritem (
    vtypeditem *item
);

vtextview *
vtypeditemGetView (
    vtypeditem *item
);

vdialogItem *
vtypeditemGetItem (
    vtypeditem *item
);

vobject *
vtypeditemGetObject (
    vtypeditem *item
);

void
vtypeditemDump (
    vtypeditem *item,
    FILE       *stream
);

void
vtypeditemDestroy (
    vtypeditem *item
);

vtypeditem *
vtypeditemLoad (
    vresource resource
);

void
vtypeditemLoadInit (
    vtypeditem *item,
    vresource   resource
);

void
vtypeditemStore (
    vtypeditem *item,
    vresource   resource
);

vtypeditemText *
vtypeditemGetTextData (
    vtypeditem *item
);

void
vtypeditemSetTextData (
    vtypeditem     *item,
    vtypeditemText *text
);

vobservable *
vtypeditemGetField (
    vtypeditem *item
);

void
vtypeditemSetField (
    vtypeditem *item,
    vobservable *field
);

void
vtypeditemSetObserving (
    vtypeditem *item,
    vbool       isObserving
);

vbool
vtypeditemIsObserving (
    vtypeditem *item
);

vstr *
vtypeditemGetString (
    vtypeditem *item
);

void
vtypeditemSetString (
    vtypeditem  *item,
    const vchar *text
);

vstr *
vtypeditemGetTransientString (
    vtypeditem *item
);

vscribe *
vtypeditemGetTransientStringScribed (
    vtypeditem *item
);

int
vtypeditemGetLength (
    vtypeditem *item
);

vscribe *
vtypeditemGetStringScribed (
    vtypeditem *item
);

void
vtypeditemSetStringScribed (
    vtypeditem *item,
    vscribe    *scribe
);

vscribe *
vtypeditemGetSubstrScribed (
    vtypeditem *item,
    long        begin,
    long        len
);

void
vtypeditemInsertString (
    vtypeditem *item,
    long        selStart,
    long        selLength,
    vchar      *s,
    long        len
);

void
vtypeditemDeleteString (
    vtypeditem *item,
    long        selStart,
    long        selLength
);

void
vtypeditemSelectRange (
    vtypeditem *item, 
    long        begin,
    long        len
);

vtextSelection *
vtypeditemGetSelection (
    vtypeditem *item
);

void
vtypeditemSetSelection (
    vtypeditem     *item,
    vtextSelection *selection
);

vscribe *
vtypeditemGetSelectionScribed (
    vtypeditem *item
);

vtypeditemText *
vtypeditemCreateTextData (
    vtypeditem *item
);

void *
vtypeditemGetData (
    vtypeditem *item
);

void
vtypeditemSetData (
    vtypeditem *item,
    const void *data
);

vtypeditemNoteProc
vtypeditemGetNotify (
    vtypeditem *item
);

void
vtypeditemSetNotify (
    vtypeditem         *item,
    vtypeditemNoteProc  notify
);

void
vtypeditemNotify (
    vtypeditem *item,
    int         msg
);

vtypeditemValidatorProc
vtypeditemGetValidator (
    vtypeditem *item
);

void
vtypeditemSetValidator (
    vtypeditem              *item,
    vtypeditemValidatorProc  validateProc
);

vcolor *
vtypeditemGetForeground (
    vtypeditem *item
);

void
vtypeditemSetForeground (
    vtypeditem *item,
    vcolor    *fg
);

int
vtypeditemGetJustification (
    vtypeditem *item
);

void
vtypeditemSetJustification (
    vtypeditem *item,
    int         justification
);

void
vtypeditemSetEditable (
    vtypeditem *item
);

vbool
vtypeditemIsOneLine (
    vtypeditem *item
);

void
vtypeditemSetOneLine (
    vtypeditem *item,
    vbool       oneline
);

vbool
vtypeditemIsSelectable (
    vtypeditem *item
);

void
vtypeditemSetSelectable (
    vtypeditem *item,
    vbool       selectable
);

vbool
vtypeditemIsModifiable (
    vtypeditem *item
);

void
vtypeditemSetModifiable (
    vtypeditem *item,
    vbool       modifiable
);

vbool
vtypeditemIsStatic (
    vtypeditem *item
);

void
vtypeditemSetStatic (
    vtypeditem *item
);

vbool
vtypeditemHasBeepIfInvalid (
    vtypeditem *item
);

void
vtypeditemSetBeepIfInvalid (
    vtypeditem *item,
    vbool       beep
);

vbool
vtypeditemHasKeepFocusIfInvalid (
    vtypeditem *item
);

void
vtypeditemSetKeepFocusIfInvalid (
    vtypeditem *item,
    vbool       flag
);

vbool
vtypeditemHasNeverInvalid (
    vtypeditem *item
);

void
vtypeditemSetNeverInvalid (
    vtypeditem *item,
    vbool       flag
);

vbool
vtypeditemHasValidateOnChange (
    vtypeditem *item
);

void
vtypeditemSetValidateOnChange (
    vtypeditem *item,
    vbool       flag
);

vbool
vtypeditemIsNull (
    vtypeditem *item
);

void
vtypeditemSetNull (
    vtypeditem *item,
    vbool       isNull
);

void
vtypeditemSetEmptyIsNull (
    vtypeditem *item,
    vbool       emptyIsNull
);

vbool
vtypeditemHasEmptyIsNull (
    vtypeditem *item
);

void
vtypeditemSetInformingField (
    vtypeditem *item,
    vbool       informing
);

vbool
vtypeditemIsInformingField (
    vtypeditem *item
);

vbool
vtypeditemIsDirty (
    vtypeditem *item
);

void
vtypeditemSetDirty (
    vtypeditem *item,
    vbool       dirty
);

long
vtypeditemGetMaxLength (
    vtypeditem *item
);

void
vtypeditemSetMaxLength (
    vtypeditem *item,
    long        maxLength
);

void 
vtypeditemSelectAll (
    vtypeditem *item
);

vbool
vtypeditemIsValid (
    vtypeditem *item
);

void
vtypeditemFocus (
    vtypeditem *item
);

void
vtypeditemUnfocus (
    vtypeditem *item
);

vformat 
vtypeditemGetFormat (
    vtypeditem *item
);

void
vtypeditemSetFormat (
    vtypeditem *item,
    vformat    *format
);

void
vtypeditemSetFormatOwned (
    vtypeditem *item,
    vformat    *format
);

void
vtypeditemIncrement (
    vtypeditem *item,
    int         direction
);

void
vtypeditemSync (
    vtypeditem *item
);

vtypeditem *
vtypeditemTextGetTypeditem (
    vtypeditemText *text
);

vtext *
vtypeditemTextGetText (
    vtypeditemText *text
);

/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * *
 */

#define vtypeditemGetStritem(i)                                              \
    vportBASE_OBJECT(                                                        \
        (i),                                                                 \
        stritem)

#define vtypeditemGetView(f)                                                 \
    vstritemGetView (                                                        \
        vtypeditemGetStritem (f))

#define vtypeditemGetItem(f)                                                 \
    vtextviewGetItem (                                                       \
        vtypeditemGetView (f))

#define vtypeditemGetObject(i)                                               \
    vstritemGetObject (                                                      \
        vtypeditemGetStritem (i))

#define vtypeditemCreateOfClass(c)                                           \
    ((vtypeditem *)                                                          \
        vstritemCreateOfClass (                                              \
            (vstritemClass *) (c)))

#define vtypeditemCreate()                                                   \
    vtypeditemCreateOfClass (                                                \
        vtypeditemGetDefaultClass ())

#define vtypeditemClone(f)                                                   \
    ((vtypeditem *)                                                          \
        vstritemClone (                                                      \
            vtypeditemGetStritem (f)))

#define vtypeditemInitOfClass(f, c)                                          \
    vdialogInitItemOfClass (                                                 \
        (vdialogItem *) (f),                                                 \
        (vdialogItemClass *) (c))

#define vtypeditemInit(f)                                                    \
    vtypeditemInitOfClass (                                                  \
        (f),                                                                 \
        vtypeditemGetDefaultClass ());

#define vtypeditemCopyInit(f, t)                                             \
    vstritemCopyInitItem (                                                   \
        vtypeditemGetStritem (f),                                            \
        (vstritem *) (t))

#define vtypeditemLoad(r)                                                    \
    ((vtypeditem *)                                                          \
        vstritemLoad (r))

#define vtypeditemLoadInit(f, r)                                             \
    vstritemLoadInit (                                                       \
        vtypeditemGetStritem (f),                                            \
        (r))

#define vtypeditemDump(f, s)                                                 \
    vobjectDump (                                                            \
        vtypeditemGetObject (f),                                             \
        (s))

#define vtypeditemDestroy(f)                                                 \
    vstritemDestroy (                                                        \
        vtypeditemGetStritem (f))

#define vtypeditemGetClass(f)                                                \
    ((vtypeditemClass *)                                                     \
        vstritemGetClass (                                                   \
            vtypeditemGetStritem (f)))

#define vtypeditemGetTextData(f)                                             \
    ((vtypeditemText *)                                                      \
        vstritemGetTextData (                                                \
            vtypeditemGetStritem (f)))

#define vtypeditemSetTextData(i, t)                                          \
    vstritemSetTextData (                                                    \
        vtypeditemGetStritem (i),                                            \
        (vstritemText *) (t))

#define vtypeditemTextGetTypeditem(t)                                        \
    ((vtypeditem *)                                                          \
        vstritemTextGetStritem ((vstritemText *) (t)))

#define vtypeditemGetField(i)                                                \
    vstritemGetField (                                                       \
        vtypeditemGetStritem (i))

#define vtypeditemSetField(i, f)                                             \
    vstritemSetField (                                                       \
        vtypeditemGetStritem (i),                                            \
        (f))

#define vtypeditemSetObserving(i, o)                                         \
    vstritemSetObserving (                                                   \
        vtypeditemGetStritem (i),                                            \
        (o))

#define vtypeditemIsObserving(i)                                             \
    vstritemIsObserving (                                                    \
        vtypeditemGetStritem (i))

#define vtypeditemGetSelection(f)                                            \
    vstritemGetSelection (                                                   \
        vtypeditemGetStritem (f))

#define vtypeditemSetSelection(f, s)                                         \
    vstritemSetSelection (                                                   \
        vtypeditemGetStritem (f),                                            \
        (s))

#define vtypeditemIsStatic(f)                                                \
    vstritemIsStatic (                                                       \
        vtypeditemGetStritem (f))

#define vtypeditemSetStatic(f)                                               \
    vstritemSetStatic (                                                      \
        vtypeditemGetStritem (f))

#define vtypeditemIsOneLine(f)                                               \
    vstritemIsOneLine (                                                      \
        vtypeditemGetStritem (f))

#define vtypeditemSetOneLine(f, o)                                           \
   vstritemSetOneLine (                                                      \
        vtypeditemGetStritem (f),                                            \
        (o))

#define vtypeditemIsModifiable(f)                                            \
    vstritemIsModifiable (                                                   \
        vtypeditemGetStritem (f))

#define vtypeditemSetModifiable(f, m)                                        \
    vstritemSetModifiable (                                                  \
        vtypeditemGetStritem (f),                                            \
        (m))

#define vtypeditemIsSelectable(f)                                            \
    vstritemIsSelectable (                                                   \
        vtypeditemGetStritem (f))

#define vtypeditemSetSelectable(f, s)                                        \
    vstritemSetSelectable (                                                  \
        vtypeditemGetStritem (f),                                            \
        (s))

#define vtypeditemGetForeground(i)                                           \
    vstritemGetForeground (                                                  \
        vtypeditemGetStritem (i))

#define vtypeditemSetForeground(i, c)                                        \
    vstritemSetForeground (                                                  \
        vtypeditemGetStritem (i),                                            \
        (c))

#define vtypeditemGetJustification(f)                                        \
    vstritemGetJustification (                                               \
        vtypeditemGetStritem (f))

#define vtypeditemSetJustification(f, j)                                     \
    vstritemSetJustification (                                               \
        vtypeditemGetStritem (f),                                            \
        (j))

#define vtypeditemGetData(f)                                                 \
    vstritemGetData (                                                        \
        vtypeditemGetStritem (f))

#define vtypeditemSetData(f, d)                                              \
    vstritemSetData (                                                        \
        vtypeditemGetStritem (f),                                            \
        (d))

#define vtypeditemGetNotify(f)                                               \
    ((vtypeditemNoteProc)                                                    \
        vstritemGetNotify (                                                  \
            vtypeditemGetStritem (f)))

#define vtypeditemSetNotify(s, n)                                            \
    vstritemSetNotify (                                                      \
        vtypeditemGetStritem (s),                                            \
        (vstritemNoteProc) (n))

#define vtypeditemNotify(t, m)                                               \
    vstritemNotify (                                                         \
        vtypeditemGetStritem (t),                                            \
        (m))

#define vtypeditemGetValidator(f)                                            \
    ((vtypeditemValidatorProc)                                               \
        vstritemGetValidator (                                               \
            vtypeditemGetStritem (f)))

#define vtypeditemSetValidator(f, p)                                         \
    vstritemSetValidator (                                                   \
        vtypeditemGetStritem (f),                                            \
        (vstritemValidatorProc) (p))

#define vtypeditemSelectAll(f)                                               \
    vstritemSelectAll (                                                      \
        vtypeditemGetStritem (f))

#define vtypeditemFocus(f)                                                   \
    vstritemFocus (                                                          \
        vtypeditemGetStritem (f))

#define vtypeditemUnfocus(f)                                                 \
    vstritemUnfocus (                                                        \
        vtypeditemGetStritem (f))

#define vtypeditemGetFormat(f)                                               \
    vstritemGetFormat (                                                      \
        vtypeditemGetStritem (f))

#define vtypeditemSetFormat(i, f)                                            \
    vstritemSetFormat (                                                      \
        vtypeditemGetStritem (i),                                            \
        (f))

#define vtypeditemSetFormatOwned(i, f)                                       \
    vstritemSetFormatOwned (                                                 \
        vtypeditemGetStritem (i),                                            \
        (f))

#define vtypeditemIsDirty(i)                                                 \
    vstritemIsDirty (                                                        \
        vtypeditemGetStritem (i))

#define vtypeditemSetDirty(i, d)                                             \
    vstritemSetDirty (                                                       \
        vtypeditemGetStritem (i),                                            \
        (d))

#define vtypeditemCopy(f, t)                                                 \
    vstritemCopy (                                                           \
        vtypeditemGetStritem (f),                                            \
        (t))

#define vtypeditemStore(f, t)                                                \
    vstritemStore (                                                          \
        vtypeditemGetStritem (f),                                            \
        (t))

#define vtypeditemInsertString(f, start, len, str, strLen)                   \
    vstritemInsertString (                                                   \
        vtypeditemGetStritem (f),                                            \
        (start),                                                             \
        (len),                                                               \
        (str),                                                               \
        (strLen))

#define vtypeditemDeleteString(f, start, len)                                \
    vstritemDeleteString (                                                   \
        vtypeditemGetStritem (f),                                            \
        (start),                                                             \
        (len))

#define vtypeditemSelectRange(f, b, l)                                       \
    vstritemSelectRange (                                                    \
        vtypeditemGetStritem (f),                                            \
        (b),                                                                 \
        (l))

#define vtypeditemGetString(f)                                               \
    vstritemGetString (                                                      \
        vtypeditemGetStritem (f))

#define vtypeditemSetString(f, s)                                            \
    vstritemSetString (                                                      \
        vtypeditemGetStritem (f),                                            \
        (s))

#define vtypeditemGetTransientString(f)                                      \
    vstritemGetTransientString (                                             \
        vtypeditemGetStritem (f))

#define vtypeditemGetTransientStringScribed(f)                               \
    vstritemGetTransientStringScribed (                                      \
        vtypeditemGetStritem (f))

#define vtypeditemGetLength(f)                                               \
    vstritemGetLength (                                                      \
        vtypeditemGetStritem (f))

#define vtypeditemGetStringScribed(f)                                        \
    vstritemGetStringScribed (                                               \
        vtypeditemGetStritem (f))

#define vtypeditemSetStringScribed(f, s)                                     \
    vstritemSetStringScribed (                                               \
        vtypeditemGetStritem (f),                                            \
        (s))

#define vtypeditemGetSubstrScribed(f, b, l)                                  \
    vstritemGetSubstrScribed (                                               \
        vtypeditemGetStritem (f),                                            \
        (b),                                                                 \
        (l))

#define vtypeditemIsValid(f)                                                 \
    vstritemIsValid (                                                        \
        vtypeditemGetStritem (f))

#define vtypeditemSetEditable(f)                                             \
    vstritemSetEditable (                                                    \
        vtypeditemGetStritem (f))

#define vtypeditemGetMaxLength(f)                                            \
    vstritemGetMaxLength (                                                   \
        vtypeditemGetStritem (f))

#define vtypeditemSetMaxLength(f, l)                                         \
    vstritemSetMaxLength (                                                   \
        vtypeditemGetStritem (f),                                            \
        (l))

#define vtypeditemHasBeepIfInvalid(f)                                        \
    vstritemHasBeepIfInvalid (                                               \
        vtypeditemGetStritem (f))

#define vtypeditemSetBeepIfInvalid(f, l)                                     \
    vstritemSetBeepIfInvalid (                                               \
        vtypeditemGetStritem (f),                                            \
        (l))

#define vtypeditemHasKeepFocusIfInvalid(f)                                   \
    vstritemHasKeepFocusIfInvalid (                                          \
        vtypeditemGetStritem (f))

#define vtypeditemSetKeepFocusIfInvalid(f, b)                                \
    vstritemSetKeepFocusIfInvalid (                                          \
        vtypeditemGetStritem (f),                                            \
        (b))

#define vtypeditemHasNeverInvalid(f)                                         \
    vstritemHasNeverInvalid (                                                \
        vtypeditemGetStritem (f))

#define vtypeditemSetNeverInvalid(f, b)                                      \
    vstritemSetNeverInvalid (                                                \
        vtypeditemGetStritem (f),                                            \
        (b))

#define vtypeditemHasValidateOnChange(f)                                     \
    vstritemHasValidateOnChange (                                            \
        vtypeditemGetStritem (f))

#define vtypeditemSetValidateOnChange(f, b)                                  \
    vstritemSetValidateOnChange (                                            \
        vtypeditemGetStritem (f),                                            \
        (b))

#define vtypeditemIsNull(i)                                                  \
    vstritemIsNull (                                                         \
        vtypeditemGetStritem (i))

#define vtypeditemSetNull(i, n)                                              \
    vstritemSetNull (                                                        \
        vtypeditemGetStritem (i),                                            \
        (n))

#define vtypeditemHasEmptyIsNull(i)                                          \
    vstritemHasEmptyIsNull (                                                 \
        vtypeditemGetStritem (i))

#define vtypeditemSetEmptyIsNull(i, n)                                       \
    vstritemSetEmptyIsNull (                                                 \
        vtypeditemGetStritem (i),                                            \
        (n))

#define vtypeditemSetInformingField(i, f)                                    \
    vstritemSetInformingField (                                              \
        vtypeditemGetStritem (i),                                            \
        (f))

#define vtypeditemIsInformingField(i)                                        \
    vstritemIsInformingField (                                               \
        vtypeditemGetStritem (i))

#define vtypeditemTextGetText(t)                                             \
    vstritemTextGetText ((vstritemText *) (t))

/*
 * * * * * * * * * * PRIVATE FUNCTION MESSAGE DEFINITIONS * * * * * * * * * *
 */

#define vtypeditemCreateTextData(f)                                          \
    vclassSend (                                                             \
        vtypeditemGetClass (f),                                              \
        vtextitemCREATE_TEXT_DATA,                                           \
        (f))

#define vtypeditemIncrement(t, d)                                            \
    vclassSend (                                                             \
        vtypeditemGetClass (t),                                              \
        vtypeditemINCREMENT,                                                 \
        (t, d))

#define vtypeditemSync(f)                                                    \
    vclassSend (                                                             \
        vtypeditemGetClass (f),                                              \
        vtypeditemSYNC,                                                      \
        (f))

/*
 * * * * * * * * * TYPED ITEM GLOBAL VARIABLES * * * * * * * * * *
 */

vportEND_CPLUSPLUS_EXTERN_C

#endif /* vtypeditemINCLUDED */

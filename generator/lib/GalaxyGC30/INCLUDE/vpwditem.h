/* $Id: vpwditem.h,v 1.8 1997/11/11 21:28:07 garyk Exp $ */

#ifndef vpwditemINCLUDED
#define vpwditemINCLUDED 1

#ifndef vportINCLUDED
#include <vport.h>
#endif

#ifndef vstdINCLUDED
#include vstdHEADER
#endif

#ifndef vscribeINCLUDED
#include vscribeHEADER
#endif

#ifndef vcharINCLUDED
#include vcharHEADER
#endif

#ifndef vstrINCLUDED
#include vstrHEADER
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
 * * PASSWORD ITEM TYPE FORWARD DECLARATION
 */
typedef struct vpwditem
               vpwditem;

typedef struct vpwditemClass
               vpwditemClass;

typedef        vstritemText
               vpwditemText;

typedef        vstritemTextClass
               vpwditemTextClass;
/*
 * * CLIENT NOTIFICATION PROCEDURE PROTOTYPE
 */
typedef void (*vpwditemNoteProc) (
        vpwditem *item,
        int       msg
);

/*
 * * CLIENT VALIDATION PROCEDURE PROTOTYPE
 */
typedef vbool (*vpwditemValidatorProc) (
    vpwditem *item
);

/*
 * * NOTIFICATION CODES
 */
enum
{
    vpwditemNOTIFY_FOCUS = vstritemNOTIFY_FOCUS,
    vpwditemNOTIFY_UNFOCUS,
    vpwditemNOTIFY_VALID,
    vpwditemNOTIFY_PARTIALLY_VALID,
    vpwditemNOTIFY_INVALID,
    vpwditemNOTIFY_NEXT
};

/*
 * * PASSWORD ITEM INSTANCE DEFINITION
 */
struct vpwditem
{
    vstritem stritem;
};

/*
 * * PASSWORD ITEM CLASS DEFINITION
 */
#define vpwditemCLASS(SUPER, ITEM, NOTIFY, VALIDATOR_PROC)                   \
        vstritemCLASS(SUPER, ITEM, NOTIFY, VALIDATOR_PROC)

struct vpwditemClass
{
    vpwditemCLASS (
        vpwditemClass,
        vpwditem,
        vpwditemNoteProc,
        vpwditemValidatorProc);
};


/*
 * * * * * * * * * PASSWORD ITEM FUNCTION PROTOTYPES * * * * * * * * * *
 */

void
vpwditemStartup (
    void
);

vpwditemClass *
vpwditemGetDefaultClass (
    void
);

vpwditemClass *
vpwditemGetClass (
    vpwditem *item
);

vpwditem *
vpwditemCreate (
    void
);

vpwditem *
vpwditemCreateOfClass (
    vpwditemClass *clas
);

vpwditem *
vpwditemClone (
    vpwditem *item
);

vstritem *
vpwditemGetStritem (
    vpwditem *item
);

vtextview *
vpwditemGetView (
    vpwditem *item
);

vdialogItem *
vpwditemGetItem (
    vpwditem *item
);

vobject *
vpwditemGetObject (
    vpwditem *item
);

void
vpwditemCopy (
    vpwditem *src,
    vpwditem *dest
);

void
vpwditemCopyInit (
    vpwditem *src,
    vpwditem *dest
);

void
vpwditemInit (
    vpwditem *item
);

void
vpwditemInitOfClass (
    vpwditem        *item,
    vpwditemClass   *clas
);

void
vpwditemDump (
    vpwditem *item,
    FILE     *stream
);

void
vpwditemDestroy (
    vpwditem *item
);

vpwditem *
vpwditemLoad (
    vresource resource
);

void
vpwditemLoadInit (
    vpwditem  *item,
    vresource  resource
);

void
vpwditemStore (
    vpwditem *item,
    vresource   resource
);

vpwditemText *
vpwditemGetTextData (
    vpwditem *item
);

void
vpwditemSetTextData (
    vpwditem     *item,
    vpwditemText *text
);

vstr *
vpwditemGetString (
    vpwditem *item
);

void
vpwditemSetString (
    vpwditem    *item,
    const vchar *text
);

vstr *
vpwditemGetTransientString (
    vpwditem *item
);

vscribe *
vpwditemGetTransientStringScribed (
    vpwditem *item
);

vscribe *
vpwditemGetStringScribed (
    vpwditem *item
);

void
vpwditemSetStringScribed (
    vpwditem *item,
    vscribe  *scribe
);

int
vpwditemGetLength (
    vpwditem *item
);

vscribe *
vpwditemGetSubstrScribed (
    vpwditem *item,
    long      begin,
    long      len
);

void
vpwditemInsertString (
    vpwditem *item,
    long      selStart,
    long      selLength,
    vchar    *s,
    long      len
);

void
vpwditemDeleteString (
    vpwditem *item,
    long      selStart,
    long      selLength
);

void
vpwditemSelectRange (
    vpwditem *item, 
    long      begin,
    long      len
);

vtextSelection *
vpwditemGetSelection (
    vpwditem *item
);

void
vpwditemSetSelection (
    vpwditem       *item,
    vtextSelection *selection
);

vscribe *
vpwditemGetSelectionScribed (
    vpwditem *item
);

vpwditemText *
vpwditemCreateTextData (
    vpwditem *item
);

void *
vpwditemGetData (
    vpwditem *item
);

void
vpwditemSetData (
    vpwditem   *item,
    const void *data
);

vpwditemNoteProc
vpwditemGetNotify (
    vpwditem *item
);

void
vpwditemSetNotify (
    vpwditem         *item,
    vpwditemNoteProc  notify
);

void
vpwditemNotify (
    vpwditem *item,
    int       msg
);

vbool
vpwditemIsStatic (
    vpwditem *item
);

void
vpwditemSetStatic (
    vpwditem *item
);

int
vpwditemGetMaxLength (
    vpwditem *item
);

void
vpwditemSetMaxLength (
    vpwditem *item,
    int       maxLen
);

vbool
vpwditemHasBeepIfInvalid (
    vpwditem *item
);

void
vpwditemSetBeepIfInvalid (
    vpwditem *item,
    vbool     beep
);

vbool
vpwditemHasKeepFocusIfInvalid (
    vpwditem *item
);

void
vpwditemSetKeepFocusIfInvalid (
    vpwditem *item,
    vbool     flag
);

vbool
vpwditemHasNeverInvalid (
    vpwditem *item
);

void
vpwditemSetNeverInvalid (
    vpwditem *item,
    vbool     flag
);

vbool
vpwditemHasValidateOnChange (
    vpwditem *item
);

void
vpwditemSetValidateOnChange (
    vpwditem *item,
    vbool     flag
);

void
vpwditemSetEditable (
    vpwditem *item
);

vcolor *
vpwditemGetForeground (
    vpwditem *item
);

void
vpwditemSetForeground (
    vpwditem *item,
    vcolor   *fg
);

int
vpwditemGetJustification (
    vpwditem *item
);

void
vpwditemSetJustification (
    vpwditem *item,
    int       justification
);

vbool
vpwditemIsOneLine (
    vpwditem *item
);

void
vpwditemSetOneLine (
    vpwditem *item,
    vbool     oneline
);

vbool
vpwditemIsSelectable (
    vpwditem *item
);

void
vpwditemSetSelectable (
    vpwditem *item,
    vbool     selectable
);

vbool
vpwditemIsModifiable (
    vpwditem *item
);

void
vpwditemSetModifiable (
    vpwditem *item,
    vbool     modifiable
);

vbool
vpwditemIsDirty (
    vpwditem *item
);

void
vpwditemSetDirty (
    vpwditem *item,
    vbool     dirty
);

void
vpwditemSelectAll (
    vpwditem *item
);

void
vpwditemFocus (
    vpwditem *item
);

void
vpwditemUnfocus (
    vpwditem *item
);

vpwditem *
vpwditemTextGetPwditem (
    vpwditemText *text
);

vstritemText *
vpwditemTextGetStritemText (
    vpwditemText *text
);

vtext *
vpwditemTextGetText (
    vpwditemText *text
);

/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * *
 */

#define vpwditemGetStritem(i)                                                \
    vportBASE_OBJECT (                                                       \
        (i),                                                                 \
        stritem)

#define vpwditemGetView(f)                                                   \
    vstritemGetView (                                                        \
        vpwditemGetStritem (f))

#define vpwditemGetItem(f)                                                   \
    vtextviewGetItem (                                                       \
        vpwditemGetView (f))

#define vpwditemGetObject(i)                                                 \
    vdialogGetItemObject (                                                   \
        vpwditemGetItem (i))

#define vpwditemCreate()                                                     \
    vpwditemCreateOfClass (                                                  \
        vpwditemGetDefaultClass ())

#define vpwditemCreateOfClass(c)                                             \
    ((vpwditem *)                                                            \
        vstritemCreateOfClass (                                              \
            (vstritemClass *) (c)))

#define vpwditemClone(f)                                                     \
    ((vpwditem *)                                                            \
        vstritemClone (                                                      \
            vpwditemGetStritem (f)))

#define vpwditemInitOfClass(f, c)                                            \
    vdialogInitItemOfClass (                                                 \
        (vdialogItem *) (f),                                                 \
        (vdialogItemClass *) (c))

#define vpwditemInit(f)                                                      \
    vpwditemInitOfClass (                                                    \
        (f),                                                                 \
        vpwditemGetDefaultClass ());

#define vpwditemCopyInit(f, t)                                               \
    vstritemCopyInit (                                                       \
        vpwditemGetStritem (f),                                              \
        (vstritem *) (t))

#define vpwditemLoad(r)                                                      \
    ((vpwditem *)                                                            \
        vstritemLoad (r))

#define vpwditemLoadInit(f, r)                                               \
    vstritemLoadInit (                                                       \
        vpwditemGetStritem (f),                                              \
        (r))

#define vpwditemDump(f, s)                                                   \
    vobjectDump (                                                            \
        vpwditemGetObject (f),                                               \
        (s))

#define vpwditemDestroy(f)                                                   \
    vstritemDestroy (                                                        \
        vpwditemGetStritem (f))

#define vpwditemGetClass(f)                                                  \
    ((vpwditemClass *)                                                       \
        vstritemGetClass (                                                   \
            vpwditemGetStritem (f)))

#define vpwditemSetTextData(i, t)                                            \
    vstritemSetTextData (                                                    \
        vpwditemGetStritem (i),                                              \
        (vstritemText *) t)

#define vpwditemGetTextData(f)                                               \
    ((vpwditemText *)                                                        \
        vstritemGetTextData (                                                \
            vpwditemGetStritem (f)))

#define vpwditemTextGetPwditem(t)                                            \
    ((vpwditem *)                                                            \
        vstritemTextGetStritem (                                             \
            (vstritemText *) (t)))

#define vpwditemGetSelection(f)                                              \
    vstritemGetSelection (                                                   \
        vpwditemGetStritem (f))

#define vpwditemGetSelectionScribed(f)                                       \
    vstritemGetSelectionScribed (                                            \
        vpwditemGetStritem (f))

#define vpwditemSetSelection(f, s)                                           \
    vstritemSetSelection (                                                   \
        vpwditemGetStritem (f),                                              \
        (s))

#define vpwditemGetMaxLength(f)                                              \
    vstritemGetMaxLength (                                                   \
        vpwditemGetStritem (f))

#define vpwditemSetMaxLength(f, l)                                           \
    vstritemSetMaxLength (                                                   \
        vpwditemGetStritem (f),                                              \
        (l))

#define vpwditemHasBeepIfInvalid(f)                                          \
    vstritemHasBeepIfInvalid (                                               \
        vpwditemGetStritem (f))

#define vpwditemSetBeepIfInvalid(f, l)                                       \
    vstritemSetBeepIfInvalid (                                               \
        vpwditemGetStritem (f),                                              \
        (l))

#define vpwditemHasKeepFocusIfInvalid(f)                                     \
    vstritemHasKeepFocusIfInvalid (                                          \
        vpwditemGetStritem (f))

#define vpwditemSetKeepFocusIfInvalid(f, b)                                  \
    vstritemSetKeepFocusIfInvalid (                                          \
        vpwditemGetStritem (f),                                              \
        (b))

#define vpwditemHasNeverInvalid(f)                                           \
    vstritemHasNeverInvalid (                                                \
        vpwditemGetStritem (f))

#define vpwditemSetNeverInvalid(f, b)                                        \
    vstritemSetNeverInvalid (                                                \
        vpwditemGetStritem (f),                                              \
        (b))

#define vpwditemHasValidateOnChange(f)                                       \
    vstritemHasValidateOnChange (                                            \
        vpwditemGetStritem (f))

#define vpwditemSetValidateOnChange(f, b)                                    \
    vstritemSetValidateOnChange (                                            \
        vpwditemGetStritem (f),                                              \
        (b))

#define vpwditemIsStatic(f)                                                  \
    vstritemIsStatic (                                                       \
        vpwditemGetStritem (f))

#define vpwditemIsOneLine(f)                                                 \
    vstritemIsOneLine (                                                      \
        vpwditemGetStritem (f))

#define vpwditemSetOneLine(f, o)                                             \
    vstritemSetOneLine (                                                     \
        vpwditemGetStritem (f),                                              \
        (o))

#define vpwditemSetModifiable(f, m)                                          \
    vstritemSetModifiable (                                                  \
        vpwditemGetStritem (f),                                              \
        (m))

#define vpwditemIsModifiable(f)                                              \
    vstritemIsModifiable (                                                   \
        vpwditemGetStritem (f))

#define vpwditemSetSelectable(f, s)                                          \
    vstritemSetSelectable (                                                  \
        vpwditemGetStritem (f),                                              \
        (s))

#define vpwditemIsSelectable(f)                                              \
    vstritemIsSelectable (                                                   \
        vpwditemGetStritem (f))

#define vpwditemSetForeground(p, c)                                          \
    vstritemSetForeground (                                                  \
        vpwditemGetStritem (p),                                              \
        (c))

#define vpwditemGetForeground(p)                                             \
    vstritemGetForeground (                                                  \
        vpwditemGetStritem (p))

#define vpwditemSetJustification(f, j)                                       \
    vstritemSetJustification (                                               \
        vpwditemGetStritem (f),                                              \
        (j))

#define vpwditemGetJustification(f)                                          \
    vstritemGetJustification (                                               \
        vpwditemGetStritem (f))

#define vpwditemGetData(f)                                                   \
    vstritemGetData (                                                        \
        vpwditemGetStritem (f))

#define vpwditemSetNotify(s, n)                                              \
    vstritemSetNotify (                                                      \
        vpwditemGetStritem (s),                                              \
        (vpwditemNoteProc) (n))

#define vpwditemNotify(p, m)                                                 \
    vstritemNotify (                                                         \
        vpwditemGetStritem (p),                                              \
        (m))

#define vpwditemGetNotify(f)                                                 \
    ((vpwditemNoteProc)                                                      \
        vstritemGetNotify (                                                  \
            vpwditemGetStritem (f)))

#define vpwditemSelectAll(f)                                                 \
    vstritemSelectAll (                                                      \
        vpwditemGetStritem (f))

#define vpwditemFocus(f)                                                     \
    vstritemFocus (                                                          \
        vpwditemGetStritem (f))

#define vpwditemUnfocus(f)                                                   \
    vstritemUnfocus (                                                        \
        vpwditemGetStritem (f))

#define vpwditemSetDirty(i, d)                                               \
    vstritemSetDirty (                                                       \
        vpwditemGetStritem (i),                                              \
        (d))

#define vpwditemIsDirty(i)                                                   \
    vstritemIsDirty (                                                        \
        vpwditemGetStritem (i))

#define vpwditemCopy(f, t)                                                   \
    vstritemCopy (                                                           \
        vpwditemGetStritem (f),                                              \
        (t))

#define vpwditemStore(f, t)                                                  \
    vstritemStore (                                                          \
        vpwditemGetStritem (f),                                              \
        (t))

#define vpwditemSetData(f, d)                                                \
    vstritemSetData (                                                        \
        vpwditemGetStritem (f),                                              \
        (d))

#define vpwditemSetStatic(f)                                                 \
    vstritemSetStatic (                                                      \
        vpwditemGetStritem (f))

#define vpwditemSetEditable(f)                                               \
    vstritemSetEditable (                                                    \
        vpwditemGetStritem (f))

#define vpwditemSetString(f, s)                                              \
    vstritemSetString (                                                      \
        vpwditemGetStritem (f),                                              \
        (s))

#define vpwditemGetTransientString(f)                                        \
    vstritemGetTransientString (                                             \
        vpwditemGetStritem (f))

#define vpwditemGetTransientStringScribed(f)                                 \
    vstritemGetTransientStringScribed (                                      \
        vpwditemGetStritem (f))

#define vpwditemGetPasswordString(f)                                         \
    vpwditemGetTransientString (f)

#define vpwditemGetPasswordStringScribed(f)                                  \
    vpwditemGetTransientStringScribed (f)

#define vpwditemGetLength(i)                                                 \
    vstritemGetLength (                                                      \
        vpwditemGetStritem (i))

#define vpwditemInsertString(f, start, len, str, strLen)                     \
    vstritemInsertString (                                                   \
        vpwditemGetStritem (f),                                              \
        (start),                                                             \
        (len),                                                               \
        (str),                                                               \
        (strLen))

#define vpwditemDeleteString(f, start, len)                                  \
    vstritemDeleteString (                                                   \
        vpwditemGetStritem (f),                                              \
        (start),                                                             \
        (len))

#define vpwditemSelectRange(f, b, l)                                         \
    vstritemSelectRange (                                                    \
        vpwditemGetStritem (f),                                              \
        (b),                                                                 \
        (l))

#define vpwditemGetSubstrScribed(f, b, l)                                    \
    vstritemGetSubstrScribed (                                               \
        vpwditemGetStritem (f),                                              \
        (b),                                                                 \
        (l))

#define vpwditemSetStringScribed(f, s)                                       \
    vstritemSetStringScribed (                                               \
        vpwditemGetStritem (f),                                              \
        (s))

#define vpwditemGetString(f)                                                 \
    vstritemGetString (                                                      \
        vpwditemGetStritem (f))

#define vpwditemGetStringScribed(f)                                          \
    vstritemGetStringScribed (                                               \
        vpwditemGetStritem (f))

#define vpwditemTextGetStritemText(t)                                        \
    vportBASE_OBJECT (                                                       \
        (t),                                                                 \
        editrec)

#define vpwditemTextGetText(t)                                               \
    vstritemTextGetText (                                                    \
        vpwditemTextGetStritemText (t))

#define vpwditemSetEchoChar(p, c)                                            \
    vstritemSetEchoChar (                                                    \
        vpwditemGetStritem (p), (c))

#define vpwditemHasEchoChar(p)                                               \
    vstritemHasEchoChar (                                                    \
        vpwditemGetStritem (p))

#define vpwditemGetEchoChar(p)                                               \
    vstritemGetEchoChar (                                                    \
        vpwditemGetStritem (p))

#define vpwditemClearEchoChar(p)                                             \
    vstritemClearEchoChar (                                                  \
        vpwditemGetStritem (p))

/*
 * * * * * * * * * * PRIVATE FUNCTION MESSAGE DEFINITIONS * * * * * * * * * *
 */

#define vpwditemCreateTextData(f)                                            \
    vclassSend (                                                             \
        vpwditemGetClass (f),                                                \
        vtextitemCREATE_TEXT_DATA,                                           \
        (f))

/*
 * * * * * * * * * PASSWORD ITEM GLOBAL VARIABLES * * * * * * * * * *
 */

vportEND_CPLUSPLUS_EXTERN_C

#endif /* vpwditemINCLUDED */

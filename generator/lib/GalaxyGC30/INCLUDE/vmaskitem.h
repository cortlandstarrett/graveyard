/* $Id: vmaskitem.h,v 1.9 1997/11/12 18:30:42 garyk Exp $ */

#ifndef vmaskitemINCLUDED
#define vmaskitemINCLUDED 1

#ifndef vportINCLUDED
#include <vport.h>
#endif

#ifndef vstdINCLUDED
#include vstdHEADER
#endif

#ifndef vstritemINCLUDED
#include vstritemHEADER
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * * * * * * * * * TYPE AND STRUCTURE DEFINITIONS * * * * * * * * * *
 */

/*
 * * MASK ITEM TYPE FORWARD DECLARATION
 */
typedef struct vmaskitem
               vmaskitem;

typedef struct vmaskitemClass
               vmaskitemClass;

typedef struct vmaskitemText
               vmaskitemText;

typedef struct vmaskitemTextClass
               vmaskitemTextClass;

/*
 * * CLIENT NOTIFICATION PROCEDURE PROTOTYPE
 */
typedef void (*vmaskitemNoteProc) (
    vmaskitem *item,
    int        msg
);

/*
 * * CLIENT VALIDATION PROCEDURE PROTOTYPE
 */
typedef vbool (*vmaskitemValidatorProc) (
    vmaskitem *item
);

/*
 * * NOTIFICATION CODES
 */
enum
{
    vmaskitemNOTIFY_FOCUS = vstritemNOTIFY_FOCUS,
    vmaskitemNOTIFY_UNFOCUS,
    vmaskitemNOTIFY_VALID,
    vmaskitemNOTIFY_PARTIALLY_VALID,
    vmaskitemNOTIFY_INVALID,
    vmaskitemNOTIFY_NEXT
};

/*
 * * MASK ITEM INSTANCE DEFINITION
 */
struct vmaskitem
{
    vstritem        stritem;
    vstr           *mask;
    unsigned short  flags;
};


/*
 * * MASK ITEM CLASS DEFINITION
 */
#define vmaskitemCLASS(SUPER, ITEM, NOTIFY, VALIDATOR_PROC)                  \
                                                                             \
        vstritemCLASS (SUPER, ITEM, NOTIFY, VALIDATOR_PROC);                 \
                                                                             \
        vclassMETHOD (vmaskitemSET_MASK_SCRIBED,                             \
            (ITEM *item, vscribe *scribe))


struct vmaskitemClass
{
    vmaskitemCLASS (
        vmaskitemClass,
        vmaskitem,
        vmaskitemNoteProc,
        vmaskitemValidatorProc);
};


/*
 * MASK ITEM TEXT INSTANCE DEFINITION
 */

struct vmaskitemText
{
    vstritemText editrec;
    vbool        insertMode;
};

/*
 * MASK ITEM TEXT CLASS DEFINITION
 */

#define vmaskitemTextCLASS(SUPER, TEXT, SELECTION, RULER, STYLE)             \
        vstritemTextCLASS(SUPER, TEXT, SELECTION, RULER, STYLE)

struct vmaskitemTextClass
{
    vmaskitemTextCLASS (
        vmaskitemTextClass,
        vmaskitemText,
        vtextSelection, 
        vtextRuler,
        vtextStyle
    );
};
           

/*
 * * * * * * * * * MASK ITEM FUNCTION PROTOTYPES * * * * * * * * * *
 */

void
vmaskitemStartup (
    void
);

vmaskitemClass *
vmaskitemGetDefaultClass (
    void
);

vmaskitemTextClass *
vmaskitemGetDefaultTextClass (
    void
);

vmaskitemText *
vmaskitemTextGetStritemText (
    vmaskitemText *text
);

vtext *
vmaskitemTextGetText (
    vmaskitemText *text
);

vmaskitem *
vmaskitemCreate (
    void
);

vmaskitem *
vmaskitemCreateOfClass (
    vmaskitemClass *clas
);

vmaskitem *
vmaskitemClone (
    vmaskitem *item
);

void
vmaskitemCopy (
    vmaskitem *src,
    vmaskitem *dest
);

void
vmaskitemCopyInit (
    vmaskitem *src,
    vmaskitem *dest
);

void
vmaskitemInit (
    vmaskitem *item
);

void
vmaskitemInitOfClass (
    vmaskitem      *item,
    vmaskitemClass *clas
);

void
vmaskitemDump (
    vmaskitem *item,
    FILE      *stream
);

void
vmaskitemDestroy (
    vmaskitem *item
);

vstritem *
vmaskitemGetStritem (
    vmaskitem *item
);

vtextview *
vmaskitemGetView (
    vmaskitem *item
);

vdialogItem *
vmaskitemGetItem (
    vmaskitem *item
);

vobject *
vmaskitemGetObject (
    vmaskitem *item
);

vmaskitem *
vmaskitemLoad (
    vresource resource
);

void
vmaskitemLoadInit (
    vmaskitem *item,
    vresource  resource
);

void
vmaskitemStore (
    vmaskitem *item,
    vresource  resource
);

void
vmaskitemSetTextData (
    vmaskitem     *item,
    vmaskitemText *text
);

vmaskitemText *
vmaskitemGetTextData (
    vmaskitem     *item
);

void
vmaskitemSetString (
    vmaskitem   *item,
    const vchar *text
);

vstr *
vmaskitemGetTransientString (
    vmaskitem *item
);

vscribe *
vmaskitemGetTransientStringScribed (
    vmaskitem *item
);

int
vmaskitemGetLength (
    vmaskitem *item
);

void
vmaskitemInsertString (
    vmaskitem *item,
    long      selStart,
    long      selLength,
    vchar    *s,
    long      len
);

void
vmaskitemDeleteString (
    vmaskitem *item,
    long      selStart,
    long      selLength
);

void
vmaskitemSelectRange (
    vmaskitem *item, 
    long      begin,
    long      len
);

void
vmaskitemSetStringScribed (
    vmaskitem *item,
    vscribe  *scribe
);

vstr *
vmaskitemGetString (
    vmaskitem *item
);

vscribe *
vmaskitemGetStringScribed (
    vmaskitem *item
);

vscribe *
vmaskitemGetSubstrScribed (
    vmaskitem *item,
    long      begin,
    long      len
);

int
vmaskitemGetMaxLength (
    vmaskitem *item
);

void
vmaskitemSetMaxLength (
    vmaskitem *item,
    int        maxLen
);

vtextSelection *
vmaskitemGetSelection (
    vmaskitem *item
);

vscribe *
vmaskitemGetSelectionScribed (
    vmaskitem *item
);

void
vmaskitemSetSelection (
    vmaskitem      *item,
    vtextSelection *selection
);

vmaskitemText *
vmaskitemCreateTextData (
    vmaskitem *item
);

vmaskitem *
vmaskitemTextGetMaskitem (
    vmaskitemText *text
);

void
vmaskitemSetData (
    vmaskitem  *item,
    const void *data
);

void
vmaskitemSetStatic (
    vmaskitem *item
);

void
vmaskitemSetEditable (
    vmaskitem *item
);

void
vmaskitemSetJustification (
    vmaskitem *item,
    int       justification
);

void
vmaskitemSetNotify (
    vmaskitem         *item,
    vmaskitemNoteProc  proc
);

void
vmaskitemNotify (
    vmaskitem *item,
    int        msg
);

vmaskitemNoteProc
vmaskitemGetNotify (
    vmaskitem *item
);

vbool
vmaskitemIsOneLine (
    vmaskitem *item
);

void
vmaskitemSetOneLine (
    vmaskitem *item,
    vbool      oneline
);

void
vmaskitemSetSelectable (
    vmaskitem *item,
    int        selectable
);

void
vmaskitemSetModifiable (
    vmaskitem *item,
    int        modifiable
);

void
vmaskitemSetDirty (
    vmaskitem *item,
    vbool      dirty
);

void
vmaskitemSetBeepIfInvalid (
    vmaskitem *item,
    vbool      flag
);

vbool
vmaskitemHasBeepIfInvalid (
    vmaskitem *item
);

vbool
vmaskitemHasKeepFocusIfInvalid (
    vmaskitem *item
);

void
vmaskitemSetKeepFocusIfInvalid (
    vmaskitem *item,
    vbool      flag
);

vbool
vmaskitemHasNeverInvalid (
    vmaskitem *item
);

void
vmaskitemSetNeverInvalid (
    vmaskitem *item,
    vbool      flag
);

vbool
vmaskitemHasValidateOnChange (
    vmaskitem *item
);

void
vmaskitemSetValidateOnChange (
    vmaskitem *item,
    vbool      flag
);

vmaskitemClass *
vmaskitemGetClass (
    vmaskitem *item
);

void *
vmaskitemGetData (
    vmaskitem *item
);

vbool
vmaskitemIsStatic (
    vmaskitem *item
);

vcolor *
vmaskitemGetForeground (
    vmaskitem *item
);

void
vmaskitemSetForeground (
    vmaskitem *item,
    vcolor    *fg
);

int
vmaskitemGetJustification (
    vmaskitem *item
);

vbool
vmaskitemIsSelectable (
    vmaskitem *item
);

vbool
vmaskitemIsModifiable (
    vmaskitem *item
);

vbool
vmaskitemIsDirty (
    vmaskitem *item
);

void
vmaskitemSelectAll (
    vmaskitem *item
);

void
vmaskitemFocus (
    vmaskitem *item
);

void
vmaskitemUnfocus (
    vmaskitem *item
);

void
vmaskitemSetMask (
    vmaskitem   *item,
    const vchar *mask
);

void
vmaskitemSetMaskScribed (
    vmaskitem *item,
    vscribe   *scribe
);

const vchar *
vmaskitemGetMask (
    vmaskitem *item
);

vbool
vmaskitemIsValid (
    vmaskitem *item
);

/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * *
 */

#define vmaskitemCreate()                                                    \
    vmaskitemCreateOfClass (                                                 \
        vmaskitemGetDefaultClass ())

#define vmaskitemGetStritem(i)                                               \
    vportBASE_OBJECT (                                                       \
        (i),                                                                 \
        stritem)

#define vmaskitemTextGetStritemText(t)                                       \
    vportBASE_OBJECT (                                                       \
        (t),                                                                 \
        editrec)

#define vmaskitemTextGetText(t)                                              \
    vstritemTextGetText (                                                    \
        vmaskitemTextGetStritemText (t))

#define vmaskitemGetObject(i)                                                \
    vtextitemGetObject (                                                     \
        vmaskitemGetStritem (i))

#define vmaskitemGetView(f)                                                  \
    vstritemGetView (                                                        \
        vmaskitemGetStritem (f))

#define vmaskitemGetItem(f)                                                  \
    vtextviewGetItem (                                                       \
        vmaskitemGetView (f))

#define vmaskitemCreateOfClass(c)                                            \
    ((vmaskitem *)                                                           \
        vstritemCreateOfClass (                                              \
            (vstritemClass *) (c)))

#define vmaskitemClone(f)                                                    \
    ((vmaskitem *)                                                           \
        vstritemClone (                                                      \
            vmaskitemGetStritem (f)))

#define vmaskitemInitOfClass(f, c)                                           \
    vdialogInitItemOfClass (                                                 \
        (vdialogItem *) (f),                                                 \
        (vdialogItemClass *) (c))

#define vmaskitemInit(f)                                                     \
    vmaskitemInitOfClass (                                                   \
        (f),                                                                 \
        vmaskitemGetDefaultClass ());

#define vmaskitemCopyInit(f, t)                                              \
    vstritemCopyInitItem (                                                   \
        vmaskitemGetStritem (f),                                             \
        (vstritem *) (t))

#define vmaskitemLoad(r)                                                     \
    ((vmaskitem *)                                                           \
        vstritemLoad (r))

#define vmaskitemLoadInit(f, r)                                              \
    vstritemLoadInit (                                                       \
        vmaskitemGetStritem (f),                                             \
        (r))

#define vmaskitemDump(f, s)                                                  \
    vobjectDump (                                                            \
        vmaskitemGetObject (f),                                              \
        (s))

#define vmaskitemDestroy(f)                                                  \
    vstritemDestroy (                                                        \
        vmaskitemGetStritem (f))

#define vmaskitemGetClass(f)                                                 \
    ((vmaskitemClass *)                                                      \
        vstritemGetClass (                                                   \
            vmaskitemGetStritem (f)))

#define vmaskitemSetTextData(i, t)                                           \
    vstritemSetTextData (                                                    \
        vmaskitemGetStritem (i),                                             \
        (vstritemText *) (t))

#define vmaskitemGetTextData(f)                                              \
    ((vmaskitemText *)                                                       \
        vstritemGetTextData (                                                \
            vmaskitemGetStritem (f)))

#define vmaskitemTextGetMaskitem(t)                                          \
    ((vmaskitem *)                                                           \
        vstritemTextGetStritem (                                             \
            (vstritemText *) (t)))

#define vmaskitemGetSelection(f)                                             \
    vstritemGetSelection (                                                   \
        vmaskitemGetStritem (f))

#define vmaskitemGetSelectionScribed(f)                                      \
    vstritemGetSelectionScribed (                                            \
        vmaskitemGetStritem (f))

#define vmaskitemSetSelection(f, s)                                          \
    vstritemSetSelection (                                                   \
        vmaskitemGetStritem (f),                                             \
        (s))

#define vmaskitemIsStatic(f)                                                 \
    vstritemIsStatic (                                                       \
        vmaskitemGetStritem (f))

#define vmaskitemSetStatic(f)                                                \
    vstritemSetStatic (                                                      \
        vmaskitemGetStritem (f))

#define vmaskitemIsOneLine(f)                                                \
    vstritemIsOneLine (                                                      \
        vmaskitemGetStritem (f))

#define vmaskitemSetOneLine(f, o)                                            \
    vstritemSetOneLine (                                                     \
        vmaskitemGetStritem (f),                                             \
        (o))

#define vmaskitemIsSelectable(f)                                             \
    vstritemIsSelectable (                                                   \
        vmaskitemGetStritem (f))

#define vmaskitemHasBeepIfInvalid(f)                                         \
    vstritemHasBeepIfInvalid (                                               \
        vmaskitemGetStritem (f))

#define vmaskitemSetBeepIfInvalid(f, o)                                      \
    vstritemSetBeepIfInvalid (                                               \
        vmaskitemGetStritem (f),                                             \
        (o))

#define vmaskitemHasKeepFocusIfInvalid(f)                                    \
    vstritemHasKeepFocusIfInvalid (                                          \
        vmaskitemGetStritem (f))

#define vmaskitemSetKeepFocusIfInvalid(f, b)                                 \
    vstritemSetKeepFocusIfInvalid (                                          \
        vmaskitemGetStritem (f),                                             \
        (b))

#define vmaskitemHasNeverInvalid(f)                                          \
    vstritemHasNeverInvalid (                                                \
        vmaskitemGetStritem (f))

#define vmaskitemSetNeverInvalid(f, b)                                       \
    vstritemSetNeverInvalid (                                                \
        vmaskitemGetStritem (f),                                             \
        (b))

#define vmaskitemHasValidateOnChange(f)                                      \
    vstritemHasValidateOnChange (                                            \
        vmaskitemGetStritem (f))

#define vmaskitemSetValidateOnChange(f, b)                                   \
    vstritemSetValidateOnChange (                                            \
        vmaskitemGetStritem (f),                                             \
        (b))

#define vmaskitemSetSelectable(f)                                            \
    vstritemSetSelectable (                                                  \
        vmaskitemGetStritem (f))

#define vmaskitemSetForeground(i, c)                                         \
    vstritemSetForeground (                                                  \
        vmaskitemGetStritem (i),                                             \
        (c))

#define vmaskitemGetForeground(i)                                            \
    vstritemGetForeground (                                                  \
        vmaskitemGetStritem (i))

#define vmaskitemSetJustification(f, j)                                      \
    vstritemSetJustification (                                               \
        vmaskitemGetStritem (f),                                             \
        (j))

#define vmaskitemGetJustification(f)                                         \
    vstritemGetJustification (                                               \
        vmaskitemGetStritem (f))

#define vmaskitemGetData(f)                                                  \
    vstritemGetData (                                                        \
        vmaskitemGetStritem (f))

#define vmaskitemSetNotify(s, n)                                             \
    vstritemSetNotify (                                                      \
        vmaskitemGetStritem (s),                                             \
        (vmaskitemNoteProc) (n))

#define vmaskitemNotify(b, m)                                                \
    vstritemNotify (                                                         \
        vmaskitemGetStritem (b),                                             \
        (m))

#define vmaskitemGetNotify(f)                                                \
    ((vmaskitemNoteProc)                                                     \
        vstritemGetNotify (                                                  \
            vmaskitemGetStritem (f)))

#define vmaskitemSelectAll(f)                                                \
    vstritemSelectAll (                                                      \
        vmaskitemGetStritem (f))

#define vmaskitemSetModifiable(f, m)                                         \
    vstritemSetModifiable (                                                  \
        vmaskitemGetStritem (f),                                             \
        (m))

#define vmaskitemIsModifiable(f)                                             \
    vstritemIsModifiable (                                                   \
        vmaskitemGetStritem (f))

#define vmaskitemSetEditable(f, m)                                           \
    vstritemSetEditable (                                                    \
        vmaskitemGetStritem (f),                                             \
        (m))

#define vmaskitemFocus(f)                                                    \
    vstritemFocus (                                                          \
        vmaskitemGetStritem (f))

#define vmaskitemUnfocus(f)                                                  \
    vstritemUnfocus (                                                        \
        vmaskitemGetStritem (f))

#define vmaskitemSetDirty(i, d)                                              \
    vstritemSetDirty (                                                       \
        vmaskitemGetStritem (i),                                             \
        (d))

#define vmaskitemIsDirty(i)                                                  \
    vstritemIsDirty (                                                        \
        vmaskitemGetStritem (i))

#define vmaskitemCopy(f, t)                                                  \
    vstritemCopy (                                                           \
        vmaskitemGetStritem (f),                                             \
        (t))

#define vmaskitemStore(f, t)                                                 \
    vstritemStore (                                                          \
        vmaskitemGetStritem (f),                                             \
        (t))

#define vmaskitemSetData(f, d)                                               \
    vstritemSetData (                                                        \
        vmaskitemGetStritem (f),                                             \
        (d))

#define vmaskitemSetString(f, s)                                             \
    vstritemSetString (                                                      \
        vmaskitemGetStritem (f),                                             \
        (s))

#define vmaskitemGetTransientString(f)                                       \
    vstritemGetTransientString (                                             \
        vmaskitemGetStritem (f))

#define vmaskitemGetTransientStringScribed(f)                                \
    vstritemGetTransientStringScribed (                                      \
        vmaskitemGetStritem (f))

#define vmaskitemGetLength(f)                                                \
    vstritemGetLength (                                                      \
        vmaskitemGetStritem (f))

#define vmaskitemInsertString(f, start, len, str, strLen)                    \
    vstritemInsertString (                                                   \
        vmaskitemGetStritem (f),                                             \
        (start),                                                             \
        (len),                                                               \
        (str),                                                               \
        (strLen))

#define vmaskitemDeleteString(f, start, len)                                 \
    vstritemDeleteString (                                                   \
        vmaskitemGetStritem (f),                                             \
        (start),                                                             \
        (len))

#define vmaskitemSelectRange(f, b, l)                                        \
    vstritemSelectRange (                                                    \
        vmaskitemGetStritem (f),                                             \
        (b),                                                                 \
        (l))

#define vmaskitemGetSubstrScribed(f, b, l)                                   \
    vstritemGetSubstrScribed (                                               \
        vmaskitemGetStritem (f),                                             \
        (b),                                                                 \
        (l))

#define vmaskitemSetStringScribed(f, s)                                      \
    vstritemSetStringScribed (                                               \
        vmaskitemGetStritem (f),                                             \
        (s))

#define vmaskitemGetString(f)                                                \
    vstritemGetString (                                                      \
        vmaskitemGetStritem (f))

#define vmaskitemGetStringScribed(f)                                         \
    vstritemGetStringScribed (                                               \
        vmaskitemGetStritem (f))

#define vmaskitemGetMask(i)                                                  \
    ((i)->mask)

#define vmaskitemIsValid(i)                                                  \
    vstritemIsValid (                                                        \
        vmaskitemGetStritem (i))

#define vmaskitemSetMaxLength(i, l)                                          \
    vstritemSetMaxLength (                                                   \
        vmaskitemGetStritem (i),                                             \
        (l))

#define vmaskitemGetMaxLength(i)                                             \
    vstritemGetMaxLength (                                                   \
        vmaskitemGetStritem (i))

/*
 * * * * * * * * * * PRIVATE FUNCTION MESSAGE DEFINITIONS * * * * * * * * * *
 */

#define vmaskitemCreateTextData(f)                                           \
    vclassSend (                                                             \
        vmaskitemGetClass (f),                                               \
        vtextitemCREATE_TEXT_DATA,                                           \
        (f))

#define vmaskitemSetMaskScribed(i, s)                                        \
    vclassSend (                                                             \
        vmaskitemGetClass (i),                                               \
        vmaskitemSET_MASK_SCRIBED,                                           \
        (i, s))

/*
 * * * * * * * * * PASSWORD ITEM GLOBAL VARIABLES * * * * * * * * * *
 */

vportEND_CPLUSPLUS_EXTERN_C

#endif /* vmaskitemINCLUDED */

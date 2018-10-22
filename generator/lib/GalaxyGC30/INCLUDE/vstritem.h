/* $Id: vstritem.h,v 1.28 1997/11/11 21:28:07 garyk Exp $ */

/* vstritem - a string input item */

#ifndef vstritemINCLUDED
#define vstritemINCLUDED 1

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

#ifndef vformatINCLUDED
#include vformatHEADER
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * * * * * * * * * TYPE AND STRUCTURE DEFINITIONS * * * * * * * * * * * * * *
 */

/*
 * * STRING ITEM FORWARD DECLARATION
 */
typedef struct vstritem
               vstritem;

typedef struct vstritemClass
               vstritemClass;

typedef struct vstritemText
               vstritemText;

typedef struct vstritemTextClass
               vstritemTextClass;

/*
 * * CLIENT NOTIFICATION PROCEDURE PROTOTYPE
 */
typedef void (*vstritemNoteProc) (
    vstritem *item,
    int       msg
);

/*
 * * CLIENT VALIDATION PROCEDURE PROTOTYPE
 */
typedef int (*vstritemValidatorProc) (
    vstritem *item
);    

/*
 * * NOTIFICATION CODES
 */
enum
{
    vstritemNOTIFY_FOCUS,
    vstritemNOTIFY_UNFOCUS,
    vstritemNOTIFY_VALID,
    vstritemNOTIFY_PARTIALLY_VALID,
    vstritemNOTIFY_INVALID,
    vstritemNOTIFY_NEXT
};


/*
 * * PRIVATES STATE FLAGS
 */
enum
{
    _vstritemFORMAT_OWNED             = 0x0001,
    _vstritemIS_DIRTY                 = 0x0002,
    _vstritemBEEP_IF_INVALID          = 0x0004,
    _vstritemTEST_VALIDITY_ON_CHANGE  = 0x0008,
    _vstritemCANNOT_BE_INVALID        = 0x0010,
    _vstritemKEEP_FOCUS_IF_INVALID    = 0x0020,
    _vstritemIS_NULL                  = 0x0040,
    _vstritemEMPTY_IS_NULL            = 0x0080,
    _vstritemINFORMING_FIELD          = 0x0100,
    _vstritemIN_INSERT                = 0x0200,
    _vstritemIN_DELETE                = 0x0400,
    _vstritemHAS_ECHO_CHAR            = 0x0800
};

/*
 * * SELECTOR COMMAND DISCRIMINATORS
 */
enum
{
    vstritemNEXT_SELECT = vtextviewNEXT_SELECT
};

/*
 * * STRING ITEM INSTANCE DEFINITION
 */
struct vstritem
{
    vtextitem              textitem;
    vformat               *format;
    vstritemNoteProc       notify;
    vstritemValidatorProc  validator;
    unsigned short         flags;
    long                   maxLength;
    vchar                  echoChar;
};

/*
 * * STRING ITEM CLASS DEFINITION
 */
#define vstritemCLASS(SUPER, ITEM, NOTIFY, VALIDATOR_PROC)                   \
                                                                             \
    vtextitemCLASS (SUPER, ITEM, vtextitemNoteProc);                         \
                                                                             \
    vclassMETHOD (vstritemINSERT_STRING,                                     \
        (ITEM *item, long start, long len, vchar *s, long slen));            \
    vclassMETHOD (vstritemDELETE_STRING,                                     \
        (ITEM *item, long start, long len));                                 \
    vclassMETHOD (vstritemSELECT_RANGE,                                      \
        (ITEM *item, long start, long len));                                 \
    vclassMETHOD_RET (vstritemGET_SUBSTR_SCRIBED, vscribe *,                 \
        (ITEM *item, long start, long len));                                 \
    vclassMETHOD (vstritemSET_FORMAT,                                        \
        (ITEM *item, vformat *format));                                      \
    vclassMETHOD (vstritemSET_NOTIFY,                                        \
        (ITEM *item, NOTIFY notify));                                        \
    vclassMETHOD (vstritemSET_VALIDATOR,                                     \
        (ITEM *item, VALIDATOR_PROC proc));                                  \
    vclassMETHOD_RET (vstritemVALIDATE, int,                                 \
        (ITEM *item));                                                       \
    vclassMETHOD (vstritemSET_STRING_SCRIBED,                                \
        (ITEM *item, vscribe *scribe));                                      \
    vclassMETHOD (vstritemSET_MAX_LENGTH,                                    \
        (ITEM *item, long maxLength));                                       \
    vclassMETHOD (vstritemSET_BEEP_IF_INVALID,                               \
        (ITEM *item, vbool flag));                                           \
    vclassMETHOD (vstritemSET_KEEP_FOCUS_IF_INVALID,                         \
        (ITEM *item, vbool flag));                                           \
    vclassMETHOD (vstritemSET_NEVER_INVALID,                                 \
        (ITEM *item, vbool flag));                                           \
    vclassMETHOD (vstritemSET_VALIDATE_ON_CHANGE,                            \
        (ITEM *item, vbool flag));                                           \
    vclassMETHOD (vstritemSET_DIRTY,                                         \
        (ITEM *item, vbool dirty));                                          \
    vclassMETHOD (vstritemSET_ECHO_CHAR,                                     \
        (ITEM *item, vchar echoChar));                                       \
    vclassMETHOD (vstritemCLEAR_ECHO_CHAR,                                   \
        (ITEM *item));                                                       \
    vclassMETHOD (vstritemNOTIFY,                                            \
        (ITEM *item, int msg));                                              \
    vclassMETHOD (vstritemSET_NULL,                                          \
        (ITEM *item, vbool isNull));                                         \
    vclassMETHOD (vstritemSET_EMPTY_IS_NULL,                                 \
        (ITEM *item, vbool emptyIsNull));                                    \
    vclassMETHOD (vstritemSET_INFORMING_FIELD,                               \
        (ITEM *item, vbool informing))


struct vstritemClass
{
    vstritemCLASS (
        vstritemClass, 
        vstritem, 
        vstritemNoteProc,
        vstritemValidatorProc);
};

struct vstritemText
{
    vtextitemText   editrec;
    vtext          *realText;
    vtextSelection *realSelection;
    vbool           insertMode;
};

#define vstritemTextCLASS(SUPER, TEXT, SELECTION, RULER, STYLE)	             \
       vtextitemTextCLASS(SUPER, TEXT, SELECTION, RULER, STYLE)

struct vstritemTextClass
{
    vstritemTextCLASS (
        vstritemTextClass, 
        vstritemText, 
        vtextSelection, 
        vtextRuler, 
        vtextStyle
    );
};
           
/*
 * * * * * * * * * STRING ITEM FUNCTION PROTOTYPES * * * * * * * * * *
 */

void
vstritemStartup (
    void
);

vstritemClass *
vstritemGetDefaultClass (
    void
);

vstritemTextClass *
vstritemGetDefaultTextClass (
    void
);

vstritem *
vstritemCreate (
    void
);

vstritem *
vstritemCreateOfClass (
    vstritemClass *clas
);

vstritem *
vstritemClone (
    vstritem *item
);

void
vstritemCopy (
    vstritem *src,
    vstritem *dest
);

void
vstritemCopyInit (
    vstritem *src,
    vstritem *dest
);

void
vstritemInit (
    vstritem *item
);

void
vstritemInitOfClass (
    vstritem      *item,
    vstritemClass *clas
);

void
vstritemDump (
    vstritem *item,
    FILE     *stream
);

void
vstritemDestroy (
    vstritem *item
);

vstritem *
vstritemLoad (
    vresource resource
);

void
vstritemLoadInit (
    vstritem  *item,
    vresource  resource
);

void
vstritemStore (
    vstritem  *item,
    vresource  resource
);

void
vstritemSetTextData (
    vstritem     *item,
    vstritemText *text
);

void
vstritemSetTextDataOwned (
    vstritem     *item,
    vstritemText *text
);

vobservable *
vstritemGetField (
    vstritem *item
);

void
vstritemSetField (
    vstritem    *item,
    vobservable *field
);

void
vstritemSetObserving (
    vstritem *item,
    vbool     isObserving
);

vbool
vstritemIsObserving (
    vstritem *item
);

void
vstritemSetDirty (
    vstritem *item,
    vbool     dirty
);

vbool
vstritemIsDirty (
    vstritem *item
);

void
vstritemSetEchoChar (
    vstritem *item,
    vchar     c
);

vchar
vstritemGetEchoChar (
    vstritem *item
);

vbool
vstritemHasEchoChar (
    vstritem *item
);

void
vstritemClearEchoChar (
    vstritem *item
);

void
vstritemSetString (
    vstritem    *item,
    const vchar *text
);

void
vstritemSetStringScribed (
    vstritem *item,
    vscribe  *scribe
);

int
vstritemGetLength (
    vstritem *item
);

void
vstritemInsertString (
    vstritem *item,
    long      selStart,
    long      selLength,
    vchar    *s,
    long      len
);

void
vstritemDeleteString (
    vstritem *item,
    long      selStart,
    long      selLength
);

void
vstritemSelectRange (
    vstritem *item, 
    long      start,
    long      end
);

vstr *
vstritemGetString (
    vstritem *item
);

vstr *
vstritemGetTransientString (
    vstritem *item
);

vscribe *
vstritemGetTransientStringScribed (
    vstritem *item
);

vscribe *
vstritemGetStringScribed (
    vstritem *item
);

vscribe *
vstritemGetSubstrScribed (
    vstritem *item,
    long      begin,
    long      len
);

vtextSelection *
vstritemGetSelection (
    vstritem *item
);

void
vstritemSetSelection (
    vstritem       *item,
    vtextSelection *selection
);

vscribe *
vstritemGetSelectionScribed (
    vstritem *item
);

vstritemText *
vstritemCreateTextData (
    vstritem *item
);

vstritemText *
vstritemGetTextData (
    vstritem *item
);

void
vstritemSetData (
    vstritem *item,
    void     *data
);

vstritemNoteProc
vstritemGetNotify (
    vstritem *item
);

void
vstritemSetNotify (
    vstritem         *item,
    vstritemNoteProc  notify
);

void
vstritemNotify (
    vstritem *item,
    int       msg
);

vstritemValidatorProc
vstritemGetValidator (
    vstritem *item
);

void
vstritemSetValidator (
    vstritem              *item,
    vstritemValidatorProc  validatorProc
);

int
vstritemValidate (
    vstritem *item
);

void
vstritemSetStatic (
    vstritem *item
);

void
vstritemSetEditable (
    vstritem *item
);

void
vstritemSetForeground (
    vstritem *item,
    vcolor   *fg
);

vcolor *
vstritemGetForeground (
    vstritem *item
);

void
vstritemSetJustification (
    vstritem *item,
    int       justification
);

vbool
vstritemIsOneLine (
    vstritem *item
);

void
vstritemSetOneLine (
    vstritem *item,
    int       oneline
);

void
vstritemSetSelectable (
    vstritem *item,
    int       selectable
);

void
vstritemSetModifiable (
    vstritem *item,
    int       modifiable
);

void
vstritemSetMaxLength (
    vstritem *item,
    long      maxLength
);

void
vstritemSetBeepIfInvalid (
    vstritem *item,
    vbool     flag
);

void
vstritemSetKeepFocusIfInvalid (
    vstritem *item,
    vbool     flag
);

void
vstritemSetNeverInvalid (
    vstritem *item,
    vbool     flag
);

void
vstritemSetValidateOnChange (
    vstritem *item,
    vbool     flag
);

void
vstritemSetNull (
    vstritem *item,
    vbool     isNull
);

vbool
vstritemIsNull (
    vstritem *item
);

void
vstritemSetEmptyIsNull (
    vstritem *item,
    vbool     emptyIsNull
);

vbool
vstritemHasEmptyIsNull (
    vstritem *item
);

void
vstritemSetInformingField (
    vstritem *item,
    vbool     informing
);

vbool
vstritemIsInformingField (
    vstritem *item
);

/* Text attribute access */

vstritemClass *
vstritemGetClass (
    vstritem *item
);

void *
vstritemGetData (
    vstritem *item
);

vbool
vstritemIsStatic (
    vstritem *item
);

int
vstritemGetJustification (
    vstritem *item
);

vbool
vstritemIsSelectable (
    vstritem *item
);

vbool
vstritemIsModifiable (
    vstritem *item
);

long
vstritemGetMaxLength (
    vstritem *item
);

vbool
vstritemHasBeepIfInvalid (
    vstritem *item
);

vbool
vstritemHasKeepFocusIfInvalid (
    vstritem *item
);

vbool
vstritemHasNeverInvalid (
    vstritem *item
);

vbool
vstritemHasValidateOnChange (
    vstritem *item
);

/* Other Routines */

void
vstritemSelectAll (
    vstritem *item
);

void
vstritemFocus (
    vstritem *item
);

void
vstritemUnfocus (
    vstritem *item
);

vformat *
vstritemGetFormat (
    vstritem *item
);

void
vstritemSetFormat (
    vstritem *item,
    vformat  *format
);

void
vstritemSetFormatOwned (
    vstritem *item,
    vformat  *format
);

vtextitem *
vstritemGetTextitem (
    vstritem *item
);

vtextview *
vstritemGetView (
    vstritem *item
);

vdialogItem *
vstritemGetItem (
    vstritem *item
);

vobject *
vstritemGetObject (
    vstritem *item
);

vbool
vstritemIsValid (
    vstritem *item
);

/*
 * STRING ITEM TEXT DATA ROUTINES
 */

vtextitemText *
vstritemTextGetTextitemText (
    vstritemText *text
);

vtext *
vstritemTextGetText (
    vstritemText *text
);

vstritem *
vstritemTextGetStritem (
    vstritemText *text
);

void
vstritemTextSetStritem (
    vstritemText *text,
    vstritem     *vstritem
);

void
vstritemTextSetData (
    vstritemText *text, 
    void         *data
);

void *
vstritemTextGetData (
    vstritemText *text
);

/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * *
 */

#define vstritemGetTextitem(i)                                               \
    vportBASE_OBJECT(                                                        \
        (i),                                                                 \
        textitem)

#define vstritemGetView(f)                                                   \
    (vtextitemGetView (                                                      \
        vstritemGetTextitem (f)))

#define vstritemGetItem(f)                                                   \
    (vtextviewGetItem (                                                      \
        vstritemGetView (f)))

#define vstritemGetObject(i)                                                 \
    vdialogGetItemObject (                                                   \
        vstritemGetItem (i))

#define vstritemCreateOfClass(c)                                             \
    ((vstritem *)                                                            \
        vtextitemCreateOfClass (                                             \
            (vtextitemClass *) (c)))

#define vstritemClone(f)                                                     \
    ((vstritem *)                                                            \
        vdialogCloneItem (                                                   \
            (vdialogItem *) (f)))

#define vstritemInitOfClass(f, c)                                            \
    vdialogInitItemOfClass (                                                 \
        (vdialogItem *) (f),                                                 \
        (vdialogItemClass *) (c))

#define vstritemInit(f)                                                      \
    vstritemInitOfClass ((f),                                                \
        vstritemGetDefaultClass ());

#define vstritemCopyInit(f, t)                                               \
    vtextitemCopyInitItem (                                                  \
        vstritemGetTextitem (f),                                             \
        (vtextitem *) (t))

#define vstritemCopy(f, t)                                                   \
    vtextitemCopy (                                                          \
        vstritemGetTextitem (f),                                             \
        vstritemGetTextitem (t))

#define vstritemStore(f, t)                                                  \
    vtextitemStore (                                                         \
        vstritemGetTextitem (f),                                             \
        vstritemGetTextitem (t))

#define vstritemSetData(f, d)	                                             \
    vtextitemSetData (                                                       \
        vstritemGetTextitem (f),                                             \
        (d))

#define vstritemLoad(r)                                                      \
    ((vstritem *)                                                            \
        vdialogLoadItem (r))

#define vstritemLoadInit(f, r)                                               \
    vdialogLoadInitItem (                                                    \
        vstritemGetItem (f),                                                 \
        (r))

#define vstritemDump(i, s)                                                   \
    vobjectDump (                                                            \
        vstritemGetObject (i),                                               \
        (s))

#define vstritemDestroy(f)                                                   \
    vdialogDestroyItem (                                                     \
        vstritemGetItem (f))

#define vstritemGetClass(f)                                                  \
    ((vstritemClass *)                                                       \
        vdialogGetItemClass (                                                \
            (vdialogItem *) (f)))

#define vstritemGetTextData(f)                                               \
    ((vstritemText *)                                                        \
        vtextviewGetTextData (                                               \
            vstritemGetView (f)))

#define vstritemSetTextData(f, t)                                            \
    vtextviewSetTextData (                                                   \
            vstritemGetView (f),                                             \
            vstritemTextGetText (t))

#define vstritemSetTextDataOwned(f, t)                                       \
    vtextviewSetTextDataOwned (                                              \
            vstritemGetView (f),                                             \
            vstritemTextGetText (t))

#define vstritemGetFormat(f)                                                 \
    ((f)->format)

#define vstritemGetField(i)                                                  \
    vdialogGetItemField (                                                    \
        vstritemGetItem (i))

#define vstritemSetField(i, f)                                               \
    vdialogSetItemField (                                                    \
        vstritemGetItem (i),                                                 \
        (f))

#define vstritemSetObserving(i, o)                                           \
    vdialogSetItemObserving (                                                \
        vstritemGetItem (i),                                                 \
        (o))

#define vstritemIsObserving(i)                                               \
    vdialogItemIsObserving (                                                 \
        vstritemGetItem (i))

#define vstritemGetSelection(f)                                              \
    vtextviewGetSelection (                                                  \
        vstritemGetView (f))

#define vstritemSetSelection(f, s)                                           \
    vtextviewSetSelection (                                                  \
        vstritemGetView(f),                                                  \
        (s))

#define vstritemSetEditable(f)                                               \
    vtextitemSetEditable (                                                   \
        vstritemGetTextitem (f))

#define vstritemSetStatic(f)                                                 \
    vtextitemSetStatic (                                                     \
        vstritemGetTextitem (f))

#define vstritemIsStatic(f)                                                  \
    (!vstritemIsModifiable(f) &&                                             \
     !vstritemIsSelectable(f))

#define vstritemIsOneLine(f)                                                 \
    vtextitemIsOneLine (                                                     \
        vstritemGetTextitem (f))

#define vstritemSetOneLine(f, o)                                             \
    vtextitemSetOneLine (                                                    \
        vstritemGetTextitem (f),                                             \
        o)

#define vstritemIsModifiable(f)                                              \
    vtextitemIsModifiable (                                                  \
        vstritemGetTextitem (f))

#define vstritemIsSelectable(f)                                              \
    vtextitemIsSelectable (                                                  \
        vstritemGetTextitem (f))

#define vstritemSetForeground(i, c)                                          \
    vdialogSetItemForeground (                                               \
        vstritemGetItem (i),                                                 \
        (c))

#define vstritemGetForeground(i)                                             \
    vdialogGetItemForeground (                                               \
        vstritemGetItem (i))

#define vstritemSetJustification(f, j)                                       \
    vtextitemSetJustification (                                              \
        vstritemGetTextitem (f),                                             \
        (j))

#define vstritemGetJustification(f)                                          \
    vtextitemGetJustification (                                              \
        vstritemGetTextitem (f))

#define vstritemSetSelectable(f)                                             \
    vtextitemSetSelectable (                                                 \
        vstritemGetTextitem (f))

#define vstritemGetData(f)                                                   \
    vdialogGetItemData (                                                     \
        vstritemGetItem (f))

#define vstritemGetNotify(i)                                                 \
    ((i)->notify)

#define vstritemGetValidator(f)                                              \
    ((f)->validator)

#define vstritemSetModifiable(f, m)                                          \
    vtextitemSetModifiable (                                                 \
        vstritemGetTextitem (f),                                             \
        (m))

#define vstritemFocus(f)                                                     \
    vdialogFocusItem (                                                       \
        vstritemGetItem (f))

#define vstritemUnfocus(f)                                                   \
    vdialogUnfocusItem (                                                     \
        vstritemGetItem (f))

#define vstritemGetTransientString(f)                                        \
    vstrCloneScribed (                                                       \
        vstritemGetTransientStringScribed (f))

#define vstritemSetDirty(f, d)                                               \
    vclassSend (                                                             \
        vstritemGetClass (f),                                                \
        vstritemSET_DIRTY,                                                   \
        (f, d))

#define vstritemSetEchoChar(f, e)                                            \
    vclassSend (                                                             \
        vstritemGetClass (f),                                                \
        vstritemSET_ECHO_CHAR,                                               \
        (f, e))

#define vstritemClearEchoChar(f)                                             \
    vclassSend (                                                             \
        vstritemGetClass (f),                                                \
        vstritemCLEAR_ECHO_CHAR,                                             \
        (f))

#define vstritemIsDirty(f)                                                   \
    ((f)->flags & _vstritemIS_DIRTY)

#define vstritemGetMaxLength(f)                                              \
    ((f)->maxLength)

#define vstritemHasBeepIfInvalid(f)                                          \
    (((f)->flags & _vstritemBEEP_IF_INVALID) != 0)

#define vstritemHasKeepFocusIfInvalid(f)                                     \
    (((f)->flags & _vstritemKEEP_FOCUS_IF_INVALID) != 0)

#define vstritemHasNeverInvalid(f)                                           \
    (((f)->flags & _vstritemCANNOT_BE_INVALID) != 0)

#define vstritemHasEmptyIsNull(f)                                            \
    (((f)->flags & _vstritemEMPTY_IS_NULL) != 0)

#define vstritemIsInformingField(f)                                          \
    (((f)->flags & _vstritemINFORMING_FIELD) != 0)

#define vstritemIsNull(f)                                                    \
    (((f)->flags & _vstritemIS_NULL) != 0)

#define vstritemHasValidateOnChange(f)                                       \
    (((f)->flags & _vstritemTEST_VALIDITY_ON_CHANGE) != 0)

#define vstritemGetEchoChar(f)                                               \
    ((f)->echoChar)

#define vstritemHasEchoChar(f)                                               \
    (((f)->flags & _vstritemHAS_ECHO_CHAR) != 0)

#define vstritemTextGetTextitemText(t)                                       \
    vportBASE_OBJECT (                                                       \
        (t),                                                                 \
        editrec)

#define vstritemTextGetText(t)                                               \
    vtextitemTextGetText (                                                   \
        vstritemTextGetTextitemText (t))

#define vstritemTextSetData(t, d)                                            \
    vtextSetData (                                                           \
        vstritemTextGetText (t),                                             \
        (d))

#define vstritemTextGetData(t)                                               \
    vtextGetData (                                                           \
        vstritemTextGetText (t))

#define vstritemTextGetStritem(t)                                            \
    ((vstritem *)                                                            \
        vstritemTextGetData (t))

#define vstritemTextSetStritem(t, i)                                         \
        vstritemTextSetData (t, i)

#define vstritemGetLength(i)                                                 \
    vtextLength (                                                            \
        vstritemTextGetText (                                                \
            vstritemGetTextData (i)))

#define vstritemSelectAll(f)                                                 \
    vstritemSelectRange (                                                    \
        (f),                                                                 \
        0,                                                                   \
        vstritemGetLength (f))

/*
 * * * * * * * * * * PRIVATE FUNCTION MESSAGE DEFINITIONS * * * * * * * * * *
 */

#define vstritemSetNotify(f, n)                                              \
    vclassSend (                                                             \
        vstritemGetClass (f),                                                \
        vstritemSET_NOTIFY,                                                  \
        (f, n))

#define vstritemNotify(i, m)                                                 \
    vclassSend (                                                             \
        vstritemGetClass (i),                                                \
        vstritemNOTIFY,                                                      \
        (i, m))
 
#define vstritemSetFormat(t, f)                                              \
    vclassSend (                                                             \
        vstritemGetClass (t),                                                \
        vstritemSET_FORMAT,                                                  \
        (t, f))

#define vstritemSetStringScribed(f, s)                                       \
    vclassSend (                                                             \
        vstritemGetClass (f),                                                \
        vstritemSET_STRING_SCRIBED,                                          \
        (f, s))

#define vstritemInsertString(f, start, len, str, strLen)                     \
    vclassSend (                                                             \
        vstritemGetClass (f),                                                \
        vstritemINSERT_STRING,                                               \
        (f, start, len, str, strLen));

#define vstritemDeleteString(f, start, len)                                  \
    vclassSend (                                                             \
        vstritemGetClass (f),                                                \
        vstritemDELETE_STRING,                                               \
        (f, start, len));

#define vstritemCreateTextData(f)                                            \
    ((vstritemText *)                                                        \
        vclassSend (                                                         \
            vstritemGetClass (f),                                            \
            vtextitemCREATE_TEXT_DATA,                                       \
            (f)))

#define vstritemSelectRange(f, s, e)                                         \
    vclassSend (                                                             \
        vstritemGetClass (f),                                                \
        vstritemSELECT_RANGE,                                                \
        (f, s, e))

#define vstritemGetSubstrScribed(f, b, l)                                    \
    vclassSend (                                                             \
        vstritemGetClass (f),                                                \
        vstritemGET_SUBSTR_SCRIBED,                                          \
        (f, b, l))

#define vstritemSetValidator(f, p)                                           \
    vclassSend (                                                             \
        vstritemGetClass (f),                                                \
        vstritemSET_VALIDATOR,                                               \
        (f, p))

#define vstritemValidate(i)                                                  \
    vclassSend (                                                             \
        vstritemGetClass (i),                                                \
        vstritemVALIDATE,                                                    \
        (i))

#define vstritemSetMaxLength(f, l)                                           \
    vclassSend (                                                             \
        vstritemGetClass (f),                                                \
        vstritemSET_MAX_LENGTH,                                              \
        (f, l))

#define vstritemIsValid(f)                                                   \
    vclassSend (                                                             \
        vstritemGetClass (f),                                                \
        vdialogITEM_IS_VALID,                                                \
        (f))

#define vstritemSetBeepIfInvalid(f, b)                                       \
    vclassSend (                                                             \
        vstritemGetClass (f),                                                \
        vstritemSET_BEEP_IF_INVALID,                                         \
        (f, b))

#define vstritemSetKeepFocusIfInvalid(f, b)                                  \
    vclassSend (                                                             \
        vstritemGetClass (f),                                                \
        vstritemSET_KEEP_FOCUS_IF_INVALID,                                   \
        ((f), (b)))

#define vstritemSetNeverInvalid(f, b)                                        \
    vclassSend (                                                             \
        vstritemGetClass (f),                                                \
        vstritemSET_NEVER_INVALID,                                           \
        ((f), (b)))

#define vstritemSetValidateOnChange(f, b)                                    \
    vclassSend (                                                             \
        vstritemGetClass (f),                                                \
        vstritemSET_VALIDATE_ON_CHANGE,                                      \
        ((f), (b)))

#define vstritemSetNull(i, n)                                                \
    vclassSend (                                                             \
        vstritemGetClass (i),                                                \
        vstritemSET_NULL,                                                    \
        ((i), (n)))

#define vstritemSetEmptyIsNull(i, n)                                         \
    vclassSend (                                                             \
        vstritemGetClass (i),                                                \
        vstritemSET_EMPTY_IS_NULL,                                           \
        ((i), (n)))

#define vstritemSetInformingField(i, f)                                      \
    vclassSend (                                                             \
        vstritemGetClass (i),                                                \
        vstritemSET_INFORMING_FIELD,                                         \
        ((i), (f)))

/*
 * * * * * * * * * STRING ITEM GLOBAL VARIABLES * * * * * * * * * *
 */


vportEND_CPLUSPLUS_EXTERN_C

#endif /* vstritemINCLUDED */

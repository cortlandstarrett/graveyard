#include <vport.h>
#include vgalaxyHEADER

#define TAG(s) vnameInternGlobalLiteral (s)

typedef struct Dialog            Dialog;
typedef struct DialogClass       DialogClass;
typedef struct completeitem      completeitem;
typedef struct completeitemClass completeitemClass;
typedef struct completelist      completelist;
typedef struct completelistClass completelistClass;

static completelistClass *_completelistClass = NULL;
static DialogClass       *_dialogClass       = NULL;
static completeitemClass *_completeitemClass = NULL;

#define completeitemCLASS(SUPER, ITEM) \
    vstritemCLASS (SUPER, ITEM, vstritemNoteProc, vstritemValidatorProc)

struct completeitemClass
{
    completeitemCLASS (
        completeitemClass, 
        completeitem);
};

struct completeitem
{
    vstritem stritem;
    vbool    completing;
};

#define completelistCLASS(SUPER, ITEM) \
    vlistitemCLASS (SUPER, ITEM, vlistitemNoteProc)

struct completelistClass
{
    completelistCLASS (completelistClass, completelist);
};

struct completelist
{
    vlistitem listitem;
};

#define DialogCLASS(SUPER, DIALOG) \
    vdialogCLASS(SUPER, DIALOG, vdialogNoteProc, vdialogItem, vdialogItemList)

struct DialogClass
{
    DialogCLASS (DialogClass, Dialog);
};

struct Dialog
{
    vdialog       dialog;
    completeitem *completeItem;
    completelist *completeList;
};

static const vchar *
_completelistFindCompletion (completelist *, const vchar *, int *, int *);

static void
_completeitemInsertString (completeitem *, long, long, vchar *, long);


static void
_dialogLoadInit (
        Dialog    *dialog,
        vresource  res
    )
{
    vclassSendSuper (_dialogClass, vobjectLOAD_INIT, (dialog, res));

    dialog->completeItem = (completeitem *)
        vdialogFindItem ((vdialog *) dialog, TAG ("CompleteItem"));
    dialog->completeList = (completelist *)
        vdialogFindItem ((vdialog *) dialog, TAG ("CompleteList"));
}

static void
_dialogClose (Dialog *dialog)
{
    vclassSendSuper (_dialogClass, vwindowCLOSE, (dialog));
    veventStopProcessing ();
}
 
static DialogClass *
_dialogGetDefaultClass (void)
{
    DialogClass *clas = vclassReproduce (vdialogGetDefaultClass ());

    vclassSetNameScribed (clas, vcharScribeLiteral ("Dialog"));
    vclassSetObjectSize  (clas, sizeof (Dialog));

    vclassSet (clas, vobjectLOAD_INIT, _dialogLoadInit);
    vclassSet (clas, vwindowCLOSE,     _dialogClose);

    return (clas);
}

static vbool
_completeitemSelectionAtEnd (completeitem *item)
{
    vbool result   = vFALSE;
    long  selStart = vtextviewSelStart (vstritemGetView ((vstritem *) item)),
          selEnd   = vtextviewSelEnd   (vstritemGetView ((vstritem *) item)),
          sLen     = vstritemGetLength ((vstritem *) item);

    if (selStart == sLen && selEnd == sLen)
        result = vTRUE;

    return (result);
}

static void
_completeitemSafeSetString (
        completeitem *item,
        const vchar  *s
    )
{
    item->completing = vTRUE;
    vstritemSetString ((vstritem *) item, s);
    item->completing = vFALSE;
}

static void
_completeitemSafeInsertString (
        completeitem *item,
        long          selStart,
        long          selLen,
        vchar        *str,
        long          strLen
    )
{
    item->completing = vTRUE;
    _completeitemInsertString (item, selStart, selLen, str, strLen);
    item->completing = vFALSE;
}

static void
_completeitemInsertString (
        completeitem *item,
        long          selStart,
        long          selLen,
        vchar        *str,
        long          strLen
    )
{
    vclassSendSuper (_completeitemClass,
        vstritemINSERT_STRING, (item, selStart, selLen, str, strLen));

    if (item->completing == vFALSE)
    {
        Dialog       *dialog = (Dialog *)
                          vdialogDetermineItemDialog (
                            vstritemGetItem ((vstritem *) item));
        completelist *list   = dialog->completeList;
        vstr         *s = NULL;
        const vchar  *completion;
        int           completionLen,
                      atRow;

        if (_completeitemSelectionAtEnd (item)     &&
            (s = vstritemGetString ((vstritem *) item)) != NULL && 
            (completion =
                _completelistFindCompletion (list, s,
                    &completionLen, &atRow)) != NULL)
        {
            int selStart = vstritemGetLength ((vstritem *) item);

            _completeitemSafeInsertString (item, selStart,
                0, (vchar *) completion, completionLen);

            vstritemSelectRange ((vstritem *) item, selStart,
                vstritemGetLength ((vstritem *) item));
        }

        if (s != NULL)
            vstrDestroy (s);
    }
}

static void
_completeitemLoadInit (
        completeitem *item,
        vresource     res
    )
{
    vclassSendSuper (_completeitemClass,
        vobjectLOAD_INIT, (item, res));

    item->completing = vFALSE;
    /* vstritemSetValidateOnChange (
        (vstritem *) item,
        vFALSE); */
}

static void
_completeitemNotify (
        completeitem *item,
        vevent       *event,
        int           msg
    )
{
    switch (msg)
    {
        case vtextviewACCEPT_NOTIFY:
        {
            Dialog       *dialog = (Dialog *) vdialogDetermineItemDialog (
                            vstritemGetItem ((vstritem *) item));
            completelist *list   = dialog->completeList;
            vlist        *ld     = vlistitemGetList ((vlistitem *) list);
            vstr         *s      = vstritemGetString ((vstritem *) item);
            const vchar  *completion;
            int           sLen, foundLen, row;

            if (s && (sLen = vcharLength (s)) > 0)
            {
                completion = _completelistFindCompletion (list, s, &foundLen, &row);

                if ((completion != NULL)       &&
                    (*completion == vcharNULL) &&
                    (foundLen == 0))
                {
                    vlistMoveRow (ld, row, 0);
                }
                else
                {
                    vlistitemPrependScribed ((vlistitem *) list, vstrScribe (s));
                    s = NULL;
                }

                _completeitemSafeSetString (item, vcharGetEmptyString ());
            }

            if (s != NULL)
                vstrDestroy (s);
        }
    }
}

static completeitemClass *
_completeitemGetDefaultClass (void)
{
    completeitemClass *clas = vclassReproduce (vstritemGetDefaultClass ());

    vclassSetNameScribed (clas, vcharScribeLiteral ("CompleteItem"));
    vclassSetObjectSize  (clas, sizeof (completeitem));

    vclassSet (clas, vobjectLOAD_INIT,      _completeitemLoadInit);
    vclassSet (clas, vstritemINSERT_STRING, _completeitemInsertString);
    vclassSet (clas, vtextviewNOTIFY,       _completeitemNotify);

    return (clas);
}

int
_completelistHandleKeyDown (
        completelist *list,
        vevent       *event
    )
{
    const vname *binding;
    int          row;

    if (event != NULL                                &&
        (binding = veventGetBinding (event)) != NULL &&
        binding == TAG ("Delete")                    &&
        (row = vlistitemGetSelectedRow ((vlistitem *) list)) !=
            vlistitemNO_CELLS_SELECTED) 
    {
        vlistitemRemoveRow ((vlistitem *) list, row);
        return (TRUE);
    }

    return (vclassSendSuper (_completelistClass,
        vdialogHANDLE_ITEM_KEY_DOWN, (list, event)));
}

static void
_completelistNotifySelect (
        completelist *list,
        int           state
    )
{
    if (state == vlistitemSELECTION_HAS_CHANGED)
    {
        int row = vlistitemGetSelectedRow ((vlistitem *) list);

        if (row != vlistitemNO_CELLS_SELECTED)
        {
            Dialog       *dialog = (Dialog *) vdialogDetermineItemDialog (
                                                vlistitemGetItem ((vlistitem *) list));
            const vchar  *s      = vlistitemGetValueAt ((vlistitem *) dialog->completeList, row);
            completeitem *item   = dialog->completeItem;

            _completeitemSafeSetString (item, s);
        }
    }
}

const vchar *
_completelistFindCompletion (
        completelist *list,
        const vchar  *prefix,
        int          *len,
        int          *atRow
    )
{
    const vchar *result = NULL,
                *s;
    int          prefixLen = vcharLength (prefix);

    if (prefix != NULL)
    {
        int row,
            rowCount = vlistitemGetRowCount ((vlistitem *) list);
    
        for (row = 0; row < rowCount; row++)
        {
            s = vlistitemGetValueAt ((vlistitem *) list, row);

            if (vcharCompareBounded (prefix, s, prefixLen) == 0)
            {
                result = s + prefixLen;

                if (len != NULL)
                    *len = vcharLength (result);

                if (atRow != NULL)
                    *atRow = row;

                break; 
            }    
        }
    }

    return (result);
}

static completelistClass *
_completelistGetDefaultClass (void)
{
    completelistClass *clas = vclassReproduce (vlistitemGetDefaultClass ());

    vclassSetNameScribed (clas, vcharScribeLiteral ("CompleteList"));
    vclassSetObjectSize  (clas, sizeof (completelist));

    vclassSet (clas, vdialogHANDLE_ITEM_KEY_DOWN, _completelistHandleKeyDown);
    vclassSet (clas, vlistviewNOTIFY_SELECT,      _completelistNotifySelect);

    return (clas);    
}

int
main (int argc, char **argv)
{
    vapplication *app;
    vresource     appRes,
                  dialogRes;
    Dialog       *dialog;

    vstartup (argc, argv);

    _completeitemClass = _completeitemGetDefaultClass ();
    _completelistClass = _completelistGetDefaultClass ();
    _dialogClass       = _dialogGetDefaultClass ();

    app       = vapplicationGetCurrent ();
    appRes    = vapplicationGetResources (app);
    dialogRes = vresourceGet (appRes, TAG ("Dialog"));
    dialog    = (Dialog *) vdialogLoad (dialogRes);
    
    if (dialog != NULL)
    {
        vdialogOpen ((vdialog *) dialog);
        veventProcess ();
        vdialogDestroy ((vdialog *) dialog);
    }
    else
        vdebugWarn (("Unable to location dialog. Exiting."));

    exit (EXIT_SUCCESS);
    return (EXIT_FAILURE);
}

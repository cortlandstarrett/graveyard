/* $Id: format.c,v 1.8 1997/09/08 21:30:44 garyk Exp $ */

/*
 * vFix:
 *  - use a tableview for the patterns list so we can have
 *    nice row/column headings and maybe autoscrollbars, etc.
 *  - add an error log textview below notebook;
 *    flush all exception information there
 */

#include <vport.h>
#include vgalaxyHEADER

static vdialog   *_dialog;
static vtextitem *_sample;
static vtextitem *_patternErrors;
static vtextitem *_inputErrors;

typedef struct _pageAssociates
               _pageAssociates;

typedef void (*sampleHandler) (
    _pageAssociates *assoc
);

struct _pageAssociates
{
    vlistitem        *listitem;
    vstritem         *scratchPad;
    vtypeditem       *input;
    vdialogLabelItem *inputFeedback;
    vformat          *format;
    sampleHandler     sampleHandler;
    vbool             settingScratch;
    vbool             insertingScratch;
};


static void
_enableSample (
        _pageAssociates *assoc
    )
{
    vdebugTraceEnter (_enableSample);

    vdebugIF ((assoc == NULL),
        vexGenerateMessagedArgNull ("Null page associate."));

    vdialogEnableItem (vtextitemGetItem (_sample));
    vdialogEnableItem (vtypeditemGetItem (assoc->input));        

    vtypeditemSetFormat (assoc->input, assoc->format);

    if (assoc->sampleHandler != NULL)
        (assoc->sampleHandler) (assoc);

    vtextitemSetText (_patternErrors, vcharGetEmptyString ());
    vtextitemSetText (_inputErrors, vcharGetEmptyString ());

    vdebugTraceLeave ();

} /* _enableSample */


static void
_disableSample (
        _pageAssociates *assoc
    )
{
    vdebugTraceEnter (_disableSample);

    vdebugIF ((assoc == NULL),
        vexGenerateMessagedArgNull ("Null page associate."));

    vdialogDisableItem (vtextitemGetItem (_sample));        
    vdialogDisableItem (vtypeditemGetItem (assoc->input));        

    vdebugTraceLeave ();

} /* _disableSample */


static void
_setSampleTextScribed (
        _pageAssociates *assoc,
        vscribe         *scribe
    )
{
    vdebugTraceEnter (_setSampleTextScribed);

    vdebugIF ((assoc == NULL),
        vexGenerateMessagedArgNull ("Null page associate."));
    vdebugIF ((scribe == NULL),
        vexGenerateMessagedArgNull ("Null scribe."));

    vtextitemSetTextScribed (_sample, scribe);

    vdebugTraceLeave ();

} /* _setSampleTextScribed */


static void
_setSampleTextColor (
        _pageAssociates *assoc,
        vcolor          *fg
    )
{
    vdebugTraceEnter (_setSampleTextColor);

    vdebugIF ((assoc == NULL),
        vexGenerateMessagedArgNull ("Null page associate."));

    vdialogSetItemForeground (vtextitemGetItem (_sample), fg);
    vdialogSetItemForeground (vtypeditemGetItem (assoc->input), fg);

    vdebugTraceLeave ();

} /* _setSampleTextColor */


static void
_setSampleTextAlignment (
        _pageAssociates *assoc,
        int              alignment
    )
{
    vdebugTraceEnter (_setSampleTextAlignment);

    vdebugIF ((assoc == NULL),
        vexGenerateMessagedArgNull ("Null page associate."));

    vtextitemSetJustification (_sample, alignment);
    vtypeditemSetJustification (assoc->input, alignment);

    vdebugTraceLeave ();

} /* _setSampleTextAlignment */


static void
_setSampleVisuals (
        _pageAssociates *assoc,
        vscribe         *text,
        vcolor          *color,
        int              alignment
    )
{
    vdebugTraceEnter (_setSampleVisuals);

    vdebugIF ((assoc == NULL),
        vexGenerateMessagedArgNull ("Null page associate."));

    if (text == NULL)
        text = vcharScribe (vcharGetEmptyString ());

    _setSampleTextScribed (assoc, text);
    _setSampleTextColor (assoc, color);
    _setSampleTextAlignment (assoc, alignment);

    vdebugTraceLeave ();

} /* _setSampleVisuals */


static void
_safeSetSampleVisuals (
        _pageAssociates      *assoc,
        vscribe              *scribe,
        const vformatSegment *segment
    )
{
    vcolor *fg;
    int     alignment;

    vdebugTraceEnter (_safeSetSampleVisuals);

    vdebugIF ((assoc == NULL),
        vexGenerateMessagedArgNull ("Null page associate."));

    fg        = vformatGetSegmentColor (segment);
    alignment = vformatGetSegmentAlignment (segment);

    vexWITH_HANDLING
    {
        _setSampleVisuals (assoc, scribe, fg, alignment);
    }
    vexON_EXCEPTION
    {
        _setSampleTextScribed (
            assoc,
            vcharScribe (vcharGetEmptyString ()));

    } vexEND_HANDLING;

    vdebugTraceLeave ();

} /* _safeSetSampleVisuals */


static void
_handleBooleanSample (
        _pageAssociates *assoc
    )
{
    static vbool          value;
    vscribe              *scribe;
    const vformatSegment *segment;
    vformatBoolean       *format;
    vboolitem            *item;
    vfield               *field;

    vdebugTraceEnter (_handleBooleanSample);

    vdebugIF ((assoc == NULL),
        vexGenerateMessagedArgNull ("Null page associated."));

    format  = (vformatBoolean *) assoc->format;
    item    = (vboolitem *)   assoc->input;
    field   = (vfield *) vboolitemGetField (item);
    value   = vfieldGetBoolean (field);
    scribe  = vformatScribeBoolean (format, value);
    segment = vformatGetBooleanSegmentBase (
                vformatGetBooleanOutputSegment (format, value));

    _safeSetSampleVisuals (assoc, scribe, segment);

    vboolitemSetValue (item, value);

    vdebugTraceLeave ();

} /* _handleBooleanSample */


static void
_handleDateSample (
        _pageAssociates *assoc
    )
{
    vdate                *value;
    vscribe              *scribe;
    const vformatSegment *segment;
    vformatDate          *format;
    vdateitem            *item;
    vfield               *field;

    vdebugTraceEnter (_handleDateSample);

    vdebugIF ((assoc == NULL),
        vexGenerateMessagedArgNull ("Null page associate."));

    format  = (vformatDate *) assoc->format;
    item    = (vdateitem *)   assoc->input;
    field   = (vfield *) vdateitemGetField (item);
    value   = vfieldGetDate (field);

    if (value == NULL)
    {
        vdate now;

        vdateInit (&now);
        vdateSetCurrent (&now);
        vfieldSetDate (field, &now);
        vdateDestroy (&now);

        value = vfieldGetDate (field);
    }

    scribe  = vformatScribeDate (format, value);
    segment = vformatGetDateSegmentBase (
                vformatGetDateOutputSegment (format, value));

    _safeSetSampleVisuals (assoc, scribe, segment);

    vdateitemSetValue (item, value);

    vdebugTraceLeave ();

} /* _handleDateSample */


static void
_handleLongSample (
        _pageAssociates *assoc
    )
{
    long                  value;
    vscribe              *scribe;
    const vformatSegment *segment;
    vformatLong          *format;
    vlongitem            *item;
    vfield               *field;

    vdebugTraceEnter (_handleDateSample);

    vdebugIF ((assoc == NULL),
        vexGenerateMessagedArgNull ("Null page associate."));

    format  = (vformatLong *) assoc->format;
    item    = (vlongitem *)   assoc->input;
    field   = (vfield *) vlongitemGetField (item);
    value   = vfieldGetLong (field);
    scribe  = vformatScribeLong (format, value);
    segment = vformatGetNumberSegmentBase (
                vformatGetLongSegmentBase (
                    vformatGetLongOutputSegment (format, value)));

    _safeSetSampleVisuals (assoc, scribe, segment);

    vlongitemSetValue (item, value);

    vdebugTraceLeave ();

} /* _handleLongSample */


static void
_handleDoubleSample (
        _pageAssociates *assoc
    )
{
    double                value;
    vscribe              *scribe;
    const vformatSegment *segment;
    vformatDouble        *format;
    vdoubleitem          *item;
    vfield               *field;

    vdebugTraceEnter (_handleDoubleSample);

    vdebugIF ((assoc == NULL),
        vexGenerateMessagedArgNull ("Null page associate."));

    format  = (vformatDouble *) assoc->format;
    item    = (vdoubleitem *)   assoc->input;
    field   = (vfield *) vdoubleitemGetField (item);
    value   = vfieldGetDouble (field);
    scribe  = vformatScribeDouble (format, value);
    segment = vformatGetNumberSegmentBase (
                vformatGetDoubleSegmentBase (
                    vformatGetDoubleOutputSegment (format, value)));

    _safeSetSampleVisuals (assoc, scribe, segment);

    vdoubleitemSetValue (item, value);

    vdebugTraceLeave ();

} /* _handleDoubleSample */


static void
_handleULongSample (
        _pageAssociates *assoc
    )
{
    unsigned long         value;
    vscribe              *scribe;
    const vformatSegment *segment;
    vformatULong         *format;
    vulongitem           *item;
    vfield               *field;

    vdebugTraceEnter (_handleULongSample);

    vdebugIF ((assoc == NULL),
        vexGenerateMessagedArgNull ("Null page associate."));

    format  = (vformatULong *) assoc->format;
    item    = (vulongitem *)   assoc->input;
    field   = (vfield *) vulongitemGetField (item);
    value   = vfieldGetUnsignedLong (field);
    scribe  = vformatScribeULong (format, value);
    segment = vformatGetNumberSegmentBase (
                vformatGetULongSegmentBase (
                    vformatGetULongOutputSegment (format, value)));

    _safeSetSampleVisuals (assoc, scribe, segment);

    vulongitemSetValue (item, value);

    vdebugTraceLeave ();

} /* _handleULongSample */


static void
_safeSetScratchPadFromRow (
        _pageAssociates *assoc,
        int              row
    )
{
    vdebugTraceEnter (_safeSetScratchPadFromRow);

    vdebugIF ((assoc == NULL),
        vexGenerateMessagedArgNull ("Null page associate."));
    vdebugIF ((row < 0),
        vexGenerateMessagedArgRange ("Negative pattern list row index."));

    vformatSetOutputPatternIndex (
        assoc->format,
        row);

    assoc->settingScratch = vTRUE;

    vstritemSetStringScribed (
        assoc->scratchPad,
        vlistitemGetValueAtScribed (
            assoc->listitem,
            row));

    assoc->settingScratch = vFALSE;

    vdebugTraceLeave ();

} /* _safeSetScratchPadFromRow */


static void
_selectPatternForScratchPad (
        vlistitem *listitem,
        int        state
    )
{
    vdebugTraceEnter (_selectPatternForScratchPad);

    vdebugIF ((listitem == NULL),
        vexGenerateMessagedArgNull ("Null listitem."));

    if (state == vlistitemSELECTION_HAS_CHANGED)
    {
        int row = vlistitemGetSelectedRow (listitem);

        if (row != vlistitemNO_CELLS_SELECTED)
            _safeSetScratchPadFromRow (
                (_pageAssociates *) vlistitemGetData (listitem),
                row);
    }

    vdebugTraceLeave ();

} /* _selectPatternForScratchPad */


static void
_inputNotify (
        vtypeditem *item,
        int         msg
    )
{
    static vcolor   *red = NULL,
                    *blue,
                    *yellow;
    _pageAssociates *assoc;

    vdebugTraceEnter (_inputNotify);

    vdebugIF ((item == NULL),
        vexGenerateMessagedArgNull ("Null typed item."));

    assoc = (_pageAssociates *) vtypeditemGetData (item);

    if (red == NULL)
    {
        vcolorSpec spec;

        vcolorInitSpec (&spec);

        vcolorFSetSpecRGB (&spec, 1.0, 0.0, 0.0);
        red = vcolorInternSpec (&spec);

        vcolorFSetSpecRGB (&spec, 0.0, 0.0, 1.0);
        blue = vcolorInternSpec (&spec);

        vcolorFSetSpecCMY (&spec, 0.0, 0.0, 1.0);
        yellow = vcolorInternSpec (&spec);

        vcolorDestroySpec (&spec);
    }

    switch (msg)
    {
        case vtypeditemNOTIFY_INVALID:
            vdialogSetItemForeground (assoc->inputFeedback, red);
            break;
        case vtypeditemNOTIFY_PARTIALLY_VALID:
            vdialogSetItemForeground (assoc->inputFeedback, yellow);
            break;
        case vtypeditemNOTIFY_FOCUS:
        case vtypeditemNOTIFY_UNFOCUS:
            break;
        case vtypeditemNOTIFY_VALID:
            vdialogSetItemForeground (assoc->inputFeedback, blue);
            break;
        default:
            break;
    }

    vdebugTraceLeave ();

} /* _inputNotify */


static void
_onMovePattern (
        vlistObserver *observer,
        int            from,
        int            to,
        int            count,
        int            type
    )
{
    vdebugTraceEnter (_onMovePattern);

    vdebugIF ((observer == NULL),
        vexGenerateMessagedArgNull ("Null list observer."));

    vclassSendSuper (vlistGetObserverClass (observer),
        vlistObserverMOVE_RANGE,
        (observer, from, to, count, type));

    if (type == vlistROW)
    {
        _pageAssociates *assoc;

        assoc = (_pageAssociates *)
                    vlistGetObserverData (observer);

        if (assoc != NULL)
            vformatSetPatternIndex (
                assoc->format,
                from,
                to);
    }

    vdebugTraceLeave ();

} /* _onMovePattern */


static void
_onRemovePattern (
        vlistObserver *observer,
        int            victim,
        int            count,
        int            type
    )
{
    vdebugTraceEnter (_onRemovePattern);

    vdebugIF ((observer == NULL),
        vexGenerateMessagedArgNull ("Null list observer."));

    vclassSendSuper (vlistGetObserverClass (observer),
        vlistObserverREMOVE_RANGE,
        (observer, victim, count, type));

    if (type == vlistROW)
    {
        _pageAssociates *assoc;

        assoc = (_pageAssociates *)
                    vlistGetObserverData (observer);

        if (assoc != NULL)
            vformatDestroyPatternAt (
                assoc->format,
                victim);
    }

    vdebugTraceLeave ();

} /* _onRemovePattern */


static vlistObserver *
_getPatternListObserver (void)
{
    vlistObserverClass *clas;
    vlistObserver      *result;

    vdebugTraceEnter (_getPatternListObserver);

    clas =
        vclassReproduce (
            vlistGetDefaultObserverClass ());

    vclassSet (clas, vlistObserverMOVE_RANGE,
                    _onMovePattern);
    vclassSet (clas, vlistObserverREMOVE_RANGE,
                    _onRemovePattern);

    result = vlistCreateObserverOfClass (clas);    

    vdebugTraceLeave ();

    return (result);

} /* _getPatternListObserver */


static void
_setupPage (
        const vnotebook *notebook,
        const vname     *pageName,
        vformat         *format,
        vfield          *field,
        sampleHandler    handler
    )
{
    vnotebookPage   *page;
    vcontainer      *container;
    vlistitem       *listitem;
    vlistObserver   *observer;
    int              row,
                     patternCount;
    _pageAssociates *assoc;

    vdebugTraceEnter (_setupPage);

    vdebugIF ((pageName == NULL),
        vexGenerateMessagedArgNull ("Null page name."));
    vdebugIF ((format == NULL),
        vexGenerateMessagedArgNull ("Null format."));

    page         = vnotebookFindPage (notebook, pageName);
    container    = vnotebookGetPageContainer (page);
    listitem     = (vlistitem *)
                        vcontainerFindItem (
                            container,
                            vnameInternGlobalLiteral ("patterns"));
    patternCount = vformatGetPatternCount (format);

    for (row = 0; row < patternCount; row++)
        vlistitemAppendScribed (
            listitem,
            vstrScribe (vformatGetPatternAt (format, row)));

    vlistitemSetSelectNotify (
        listitem,
        _selectPatternForScratchPad);

    assoc                = (_pageAssociates *) 
                            vmemAllocAndClear (sizeof (_pageAssociates));
    assoc->scratchPad    = (vstritem *)
                            vcontainerFindItem (
                                    container, 
                                    vnameInternGlobalLiteral ("ScratchPad"));
    assoc->input         = (vtypeditem *)
                            vcontainerFindItem (
                                    container,
                                    vnameInternGlobalLiteral ("input"));
    assoc->inputFeedback = (vdialogLabelItem *)
                            vcontainerFindItem (
                                    container,
                                    vnameInternGlobalLiteral ("input feedback"));
    assoc->listitem      = listitem;
    assoc->format        = format;
    assoc->sampleHandler = handler;

    vlistitemSetData     (listitem,          assoc);
    vstritemSetData      (assoc->scratchPad, assoc);
    vtypeditemSetData    (assoc->input,      assoc);
    vnotebookSetPageData (page,              assoc);

    vtypeditemSetNotify (assoc->input, _inputNotify);

    observer = _getPatternListObserver ();

    vlistSetObserverData (
        observer,
        assoc);

    vlistInstallObserverOwned (
        vlistitemGetList (listitem),
        observer);

    vtypeditemSetField (assoc->input, (vobservable *) field);

    vdebugTraceLeave ();

} /* _setupPage */


static vtextitem *
_findErrorPageTextitem (
        const vnotebook *notebook,
        const vname     *pageName
    )
{
    vtextitem     *result;
    vnotebookPage *page;
    vcontainer    *container;

    vdebugTraceEnter (_findErrorPageTextitem);
    vdebugIF ((notebook == NULL),
        vexGenerateMessagedArgNull ("Null notebook."));
    vdebugIF ((pageName == NULL),
        vexGenerateMessagedArgNull ("Null page name."));

    page      = (vnotebookPage *)
        vnotebookFindPage (notebook, pageName);
    container = (vcontainer *)
        vnotebookGetPageContainer (page);
    result    = (vtextitem *)
        vcontainerGetItemAt (container, 0);

    vdebugTraceLeave ();

    return (result);

} /* _findErrorPageTextitem */


static void
_setupItems (vdialog *pDialog)
{
    vnotebook *notebook;

    _sample = (vtextitem *)
        vdialogFindItem (
            pDialog,
            vnameInternGlobalLiteral ("sample"));

    notebook = (vnotebook *)
        vdialogFindItem (
            pDialog,
            vnameInternGlobalLiteral ("Error Notebook"));
    _patternErrors =
        _findErrorPageTextitem (
            notebook,
            vnameInternGlobalLiteral ("Pattern Errors"));
    _inputErrors =
        _findErrorPageTextitem (
            notebook,
            vnameInternGlobalLiteral ("Input Errors"));

    notebook = (vnotebook *)
        vdialogFindItem (
            pDialog,
            vnameInternGlobalLiteral ("notebook"));

    _setupPage (
        notebook,
        vnameInternGlobalLiteral ("Boolean"),
        (vformat *) vformatGetDefaultBoolean (),
        (vfield *) vfieldCreateBoolean (),
        _handleBooleanSample);

    _setupPage (
        notebook,
        vnameInternGlobalLiteral ("Date/Time"),
        (vformat *) vformatGetDefaultDate (),
        (vfield *) vfieldCreateDate (),
        _handleDateSample);

    _setupPage (
        notebook,
        vnameInternGlobalLiteral ("Long"),
        (vformat *) vformatGetDefaultLong (),
        (vfield *) vfieldCreateLong (),
        _handleLongSample);

    _setupPage (
        notebook,
        vnameInternGlobalLiteral ("Double"),
        (vformat *) vformatGetDefaultDouble (),
        (vfield *) vfieldCreateDouble (),
        _handleDoubleSample);

    _setupPage (
        notebook,
        vnameInternGlobalLiteral ("Unsigned Long"),
        (vformat *) vformatGetDefaultULong (),
        (vfield *) vfieldCreateUnsignedLong (),
        _handleULongSample);

} /* _setupItems */


static vstr *
_exceptionToString (
        vexException *exception
    )
{
    vstr           *result;
    static FILE    *tmp = NULL;
    static vfsFile *tmpFile;
    static vchar    buf[256];

    vdebugTraceEnter (_exceptionToString);

    vdebugIF ((exception == NULL),
        vexGenerateMessagedArgNull ("Null exception."));

    result = vstrCreate ();

    if (tmp == NULL)
    {       
        vstr    *tmpl    = vstrCloneScribed (vcharScribeLiteral ("_testXXXXX.XXX"));
        vchar   *tmpName = vfsGenerateTempName (tmpl);
        vfsPath *tmpPath = vfsPathFromStr (tmpName);

        vexWITH_HANDLING
        {
            vfsCreateFile (tmpPath, vfsOWNER_PERMISSIONS_MASK |
                                    vfsOTHER_READ             |
                                    vfsOTHER_WRITE);
        }
        vexON_EXCEPTION
        {
            NULL;             
        } vexEND_HANDLING;

        tmpFile = vfsOpenFile (tmpPath, vfsOPEN_READ_WRITE | vfsOPEN_TEXT_MODE);
        tmp     = vfsGetFilePtr (tmpFile);

        vstrDestroy (tmpl);
        vfsDestroyPath (tmpPath);
    }

    vfsTruncateOpenFile (tmpFile);
    vexDumpChain (tmp);
    fflush (tmp);
    vfsRewindFile (tmpFile);

    while (vfsReadString (buf, sizeof (buf), tmpFile))
        result = vstrAppend (result, buf);
    
    vdebugTraceLeave ();

    return (result);

} /* _exceptionToString */


static void
_dumpExceptionChainToErrorLog (
        vtextitem    *log,
        vexException *exception

    )
{
    vtext          *text;
    vtextSelection *sel;
    vstr           *str;

    vdebugTraceEnter (_dumpExceptionChainToErrorLog);

    vdebugIF ((log == NULL),
        vexGenerateMessagedArgNull ("Null textitem."));

    text = vtextitemGetTextData (log);
    sel  = vtextitemGetSelection (log);
    str  = _exceptionToString (exception);

    vtextselectionSelectRange (sel, 0, vtextLength (text));
    vtextInsert (text, sel, str, vcharLength (str));
    vtextselectionSelectRange (sel, 0, 0);

    vstrDestroy (str);

    vdebugTraceLeave ();

} /* _dumpExceptionChainToErrorLog */


static void
_updateFormatFromScratchPad (
        _pageAssociates *assoc
    )
{
    int   outIndex;
    vstr *str;

    vdebugTraceEnter (_updateFormatFromScratchPad);

    vdebugIF ((assoc == NULL),
        vexGenerateMessagedArgNull ("Null page associates."));

    outIndex = vformatGetOutputPatternIndex (assoc->format);
    str      = vtextitemGetTextAsString (
                    vstritemGetTextitem (assoc->scratchPad));

    if (str != NULL && *str != vcharNULL)
    {
        vexWITH_HANDLING
        {
            vformatInsertPattern (assoc->format, str, outIndex);
            vformatDestroyPatternAt (assoc->format, outIndex + 1);

            vlistitemSetValueAtScribed (
                assoc->listitem,
                vcharScribe (str),
                outIndex);

            _enableSample (assoc);
        }
        vexON_EXCEPTION
        {
            _disableSample (assoc);
            _dumpExceptionChainToErrorLog (
                _patternErrors,
                vexGetException ());
        } vexEND_HANDLING;
    }
    else
    {
        _disableSample (assoc);        
    }

    if (str != NULL)
        vstrDestroy (str);
    
    vdebugTraceLeave ();

} /* _updateFormatFromScratchPad */

        
static void
_insertPatternString (
        vstritem *item,
        long      selStart,
        long      selLen,
        vchar    *str,
        long      strLen
    )
{
    _pageAssociates *assoc;

    vdebugTraceEnter (_insertPatternString);

    assoc = (_pageAssociates *) vstritemGetData (item);

    assoc->insertingScratch = vTRUE;

    vclassSendSuper (vstritemGetClass (item),
        vstritemINSERT_STRING,
        (item, selStart, selLen, str, strLen));

    assoc->insertingScratch = vFALSE;

    if (assoc->settingScratch == vFALSE)
        _updateFormatFromScratchPad (assoc);
    else
        _enableSample (assoc);

    vdebugTraceLeave ();

} /* _insertPatternString */


static void
_deletePatternString (
        vstritem    *item,
        long         selStart,
        long         selLen
    )
{
    _pageAssociates *assoc;

    vdebugTraceEnter (_deletePatternString);

    assoc = (_pageAssociates *) vstritemGetData (item);

    vclassSendSuper (vstritemGetClass (item),
        vstritemDELETE_STRING,
        (item, selStart, selLen));

    if (assoc->settingScratch == vFALSE &&
        assoc->insertingScratch == vFALSE)
    {
        _updateFormatFromScratchPad (assoc);
    }

    vdebugTraceLeave ();

} /* _deletePatternString */


static void
_startupPatternItem (void)
{
    vstritemClass *clas;

    vdebugTraceEnter (_startupPatternItem);

    vclassSetNameScribed (
        clas = vclassReproduce (vstritemGetDefaultClass ()),
        vcharScribeLiteral ("PatternItem"));

    vclassSet (clas,
        vstritemINSERT_STRING, 
        _insertPatternString);
    vclassSet (clas,
        vstritemDELETE_STRING,
        _deletePatternString);

    vdebugTraceLeave ();

} /* _startupPatternItem */



static int
_handlePatternListKeyDown (
        vlistitem *item,
        vevent    *event
    )
{
    int          result;
    const vname *binding;

    vdebugTraceEnter (_handlePatternListKeyDown);

    result = FALSE;

    if (event != NULL)
    {
        binding = veventGetBinding (event);

        if (binding == vnameInternGlobalLiteral ("Delete"))
        {
            int row;

            row = vlistitemGetSelectedRow (item);
            if (row != vlistitemNO_CELLS_SELECTED)
            {
                vlistitemRemoveRow (item, row);
                result = TRUE;
            }
        }
    }

    if (result != TRUE)
        result = vclassSendSuper (vlistitemGetClass (item),
            vdialogHANDLE_ITEM_KEY_DOWN,
            (item, event));

    vdebugTraceLeave ();

    return (result);

} /* _handlePatternListKeyDown */


static void
_listitemOpen (
        vlistitem *item
    )
{
    vlistviewSelectNoteProc  notify;
    vlistview               *view;

    vdebugTraceEnter (_listitemOpen);

    vclassSendSuper (vlistitemGetClass (item),
        vdialogOPEN_ITEM, (item));

    view   = vlistitemGetView (item);
    notify = vlistviewGetSelectNotify (view);

    if (notify != NULL)
        (*notify) (view, vlistitemSELECTION_HAS_CHANGED);

    vdebugTraceLeave ();

} /* _listitemOpen */


static void
_startupPatternList (void)
{
    vlistitemClass *clas;

    vdebugTraceEnter (_startupPatternList);

    vclassSetNameScribed (
        clas = vclassReproduce (vlistitemGetDefaultClass ()),
        vcharScribeLiteral ("PatternList"));

    vclassSet (clas, 
        vdialogHANDLE_ITEM_KEY_DOWN, 
        _handlePatternListKeyDown);
    vclassSet (clas, vdialogOPEN_ITEM,
        _listitemOpen);

    vdebugTraceLeave ();

} /* _startupPatternList */


static int
_dialogCloseHook (
        vdialog *dialog,
        vevent  *event
    )
{
    vdebugTraceEnter (_dialogCloseHook);

    vdebugIF ((dialog == NULL),
        vexGenerateMessagedArgNull ("Null dialog."));
    vdebugIF ((event == NULL),
        vexGenerateMessagedArgNull ("Null event."));

    veventStopProcessing ();

    vdebugTraceLeave ();

    return (FALSE);

} /* _dialogCloseHook */


static void
_startup (int argc, char **argv)
{
    vapplication *app;
    vresource     appRes,
                  dialogRes;

    vstartup (argc, argv);

    _startupPatternItem ();
    _startupPatternList ();

    app       = vapplicationGetCurrent ();
    appRes    = vapplicationGetResources (app);
    dialogRes = vresourceGet (appRes, 
                              vnameInternGlobalLiteral ("Dialog"));
    _dialog   = vdialogLoad (dialogRes);

    vdebugMessagedAssert (
        _dialog,
        "Dialog not initialized");

    _setupItems (_dialog);

    vdialogSetCloseHook (
        _dialog,
        _dialogCloseHook);

    vdialogOpen (_dialog);

} /* _startup */


static void
_shutdownItems (vdialog *dialog)
{
    vnotebook       *notebook;
    vnotebookPage   *page;
    int              pageCount,
                     i;
    _pageAssociates *assoc;

    notebook = (vnotebook *)
        vdialogFindItem (
            dialog,
            vnameInternGlobalLiteral ("notebook"));

    pageCount = vnotebookGetPageCount (notebook);

    for (i = 0; i < pageCount; i++)
    {
        page  = vnotebookGetPageAt (notebook, i);
        assoc = (_pageAssociates *) vnotebookGetPageData (page);

        if (assoc != NULL)
            vmemFree (assoc);
    }

} /* _shutdownItems */


static void
_shutdown (void)
{
    vdebugTraceEnter (_shutdown);

    _shutdownItems (_dialog);

    vdialogDestroy (_dialog);
    _dialog = NULL;

    vdebugTraceLeave ();

} /* _shutdown */


static void
_process (void)
{
    vdebugTraceEnter (_process);

    veventProcess ();

    vdebugTraceLeave ();

} /* _process */


int
main (int argc, char **argv)
{
    _startup (argc, argv);
    _process ();
    _shutdown ();

    exit (EXIT_SUCCESS);
    return (EXIT_FAILURE);            

} /* main */

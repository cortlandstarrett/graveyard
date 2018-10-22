/* $Id: vtext.h,v 1.193 1997/10/22 17:34:04 robert Exp $ */

/************************************************************

    vtext.h
    C Interface to the Text Manager

    (c) Copyright Visix Software  1991
    All rights reserved

************************************************************/

#ifndef vtextINCLUDED
#define vtextINCLUDED 1

#ifndef  vportINCLUDED		/* for v*HEADER */
#include <vport.h>
#endif

#ifndef  vstdINCLUDED		/* for vbool, vbyte */
#include vstdHEADER
#endif

#ifndef  vcharINCLUDED
#include vcharHEADER
#endif

#ifndef  vfontINCLUDED
#include vfontHEADER
#endif

#ifndef  vimageINCLUDED
#include vimageHEADER
#endif

#ifndef  vobjectINCLUDED
#include vobjectHEADER
#endif

#ifndef  vclassINCLUDED
#include vclassHEADER
#endif

#ifndef  vpoolINCLUDED
#include vpoolHEADER
#endif

#ifndef  vcolorINCLUDED
#include vcolorHEADER
#endif

#ifndef vdrawcontextINCLUDED
#include vdrawcontextHEADER
#endif

#ifndef  vtextselectionINCLUDED
#include vtextselectionHEADER
#endif

#ifndef  viteratorINCLUDED
#include viteratorHEADER
#endif

#ifndef  vobserverINCLUDED
#include vobserverHEADER
#endif

#ifndef  vundoINCLUDED
#include vundoHEADER
#endif


vportBEGIN_CPLUSPLUS_EXTERN_C


/*
 * * * * * * * * * * PUBLIC CONSTANT DEFINITIONS * * * * * * * * * *
 */

#define vtextNO_CHANGE		    (-1)
#define vtextSEARCH_FAILED	    (-1)
#define vtextTEXT_BLOCK_SIZE	    8192
#define vtextINIT_TEMP_BLOCK_SIZE   256
#define vtextINIT_TEXT_SIZE	    7680
#define vtextALL_STYLES		    (NULL)
#define vtextALL_RULERS		    (NULL)

enum {
    vtextBACKSPACE	     = 8,
    vtextEOLN		     = 10,
    vtextDELETE_CHAR	     = 127
};

/* Values for VIEW attribute */

enum {
    vtextVIEW_NORMAL		= 0,
    vtextVIEW_INVISIBLES	= 1,
    vtextVIEW_KEYCODE		= 2
};

/* Values for 'tabType' parameter to vtextRulerAddTab */

enum {
    vtextFLUSH_LEFT_TAB		= 0,
    vtextFLUSH_RIGHT_TAB	= 1,
    vtextCENTER_TAB		= 2,
    vtextDECIMAL_TAB		= 3
};

/* Values for return status of a processing function to vtextProcess() */

enum {
    vtextERROR		    	= (-1),
    vtextSUCCESS		= 0,
    vtextMORE_SPACE 	    	= 1,
    vtextSTOP		    	= 2
};

/*
 * Value for 'tabSettings' parameter to vtextProcess() and for
 * vtextTabsToSpaces() and vtextSpacesToTabs()
 */

enum {
    vtextLEADING_ONLY		= 0x0001,
    vtextCONVERT_IN_QUOTES	= 0x0002,
    vtextCONVERT_IN_USERAREA	= 0x0008,
    vtextCONVERT_ALL		= vtextCONVERT_IN_QUOTES |
    				  vtextCONVERT_IN_USERAREA,
    vtextCONVERT_ALL_LEADING	= vtextCONVERT_IN_QUOTES |
    				  vtextCONVERT_IN_USERAREA |
				  vtextLEADING_ONLY
};

/* Values for 'flags' parameter to vtextProcess() */

enum {
    vtextNO_PROCESS_BUFFER	= 0x0001,
    vtextPROCESS_HIDDEN		= 0x0002,
    vtextOVERRIDE_RECT_MODE	= 0x0004,
    vtextREQUEST_NUM_LINES	= 0x0008,
    vtextCOPY_TO_BUFFER		= 0x0010,
    vtextEXPAND_TABS		= 0x0020,
    vtextENTAB			= 0x0040,
    _vtextWHOLE_LINES  	        = 0x0080,
    vtextWHOLE_LINES		= _vtextWHOLE_LINES |
                                  vtextOVERRIDE_RECT_MODE,
    vtextNO_EOLN		= 0x0100,
    vtextEND_WITH_EOLN		= 0x0200
};

/* Values for searchMethod parameter to vtextSearch() */

enum {
    vtextFORWARD_SEARCH		= 1,
    vtextBACKWARD_SEARCH	= 2,
    vtextREGEXP_SEARCH		= 3,
    vtextREGEXP_BACKWARD_SEARCH	= 4
};

/* Value for 'location' parameter to vtextSelectLines() */

enum {
    vtextLINE_ALL		= 1,
    vtextLINE_START 		= 2,
    vtextLINE_END		= 3,
    vtextLINE_END_NO_EOL	= 4,
    vtextLINE_END2		= 4,
    vtextLINE_ALL_WRAPPED	= 5
};

/* Values for 'selectMethod' parameter to 'vtextSetSelectMethod' */

enum {
    vtextSELECT_NORMAL		= vtextselectionSELECT_NORMAL,
    vtextSELECT_RECTANGULAR	= vtextselectionSELECT_RECTANGULAR,
    vtextSELECT_LINES		= vtextselectionSELECT_LINES,
    vtextSELECT_UNION		= vtextselectionSELECT_UNION,
    vtextSELECT_DISCONTIGUOUS	= vtextselectionSELECT_DISCONTIGUOUS
							/* Not implemented */
};

/* Values for 'operation' parameter for a vtextGraphicProc */

enum {
    vtextGRAPHIC_DRAW		= 0,
    vtextGRAPHIC_CALC_WIDTH	= 1,
    vtextGRAPHIC_CALC_HEIGHT	= 2,
    vtextGRAPHIC_CALC_DESCENT	= 3
};

/* Values for state parameter to Observer Select message */

enum {
    vtextSELECTION_WILL_CHANGE		= 0,
    vtextSELECTION_HAS_CHANGED		= 1
};

/* Values for state parameter to Observer SelectMethod message */

enum {
    vtextSELECT_METHOD_WILL_CHANGE	= 1,
    vtextSELECT_METHOD_HAS_CHANGED	= 2
};

/* Values for 'invisible' parameter to vtextSet/GetInvisibleImage */

enum {
    vtextINVISIBLE_EOLN		= 0,
    vtextINVISIBLE_TAB		= 1,
    vtextINVISIBLE_UNKNOWN	= 2,
    vtextINVISIBLE_SPACE	= 3,
    vtextINVISIBLE_LAST
};

/*
 * Attribute types
 */
enum {
    vtextATTR_BAD		= 0,
    vtextATTR_FONT		= 1,
    vtextATTR_COLOR,
    vtextATTR_INTEGER,
    vtextATTR_BOOLEAN,
    vtextATTR_FIXED,
    vtextATTR_NAME,
    vtextATTR_GRAPHIC,
    vtextATTR_DATA
    };

/* Style attributes */

#define vtext_Ascent            (_vtextPredefs[_vtext_Ascent])
#define vtext_Descent           (_vtextPredefs[_vtext_Descent])
#define vtext_Font              (_vtextPredefs[_vtext_Font])
#define vtext_Color             (_vtextPredefs[_vtext_Color])
#define vtext_BackgroundColor   (_vtextPredefs[_vtext_BackgroundColor])
#define vtext_Size              (_vtextPredefs[_vtext_Size])
#define vtext_Bold              (_vtextPredefs[_vtext_Bold])
#define vtext_Underline         (_vtextPredefs[_vtext_Underline])
#define vtext_Invert            (_vtextPredefs[_vtext_Invert])
#define vtext_Italic            (_vtextPredefs[_vtext_Italic])
#define vtext_Strikethru        (_vtextPredefs[_vtext_Strikethru])
#define vtext_Hidden            (_vtextPredefs[_vtext_Hidden])
#define vtext_Graphic           (_vtextPredefs[_vtext_Graphic])

/* Ruler Attributes */

#define vtext_LeftIndent        (_vtextPredefs[_vtext_LeftIndent])
#define vtext_RightIndent       (_vtextPredefs[_vtext_RightIndent])
#define vtext_FirstLineIndent   (_vtextPredefs[_vtext_FirstLineIndent])
#define vtext_Justification     (_vtextPredefs[_vtext_Justification])
/*      vtext_Ascent */
/*      vtext_Descent */
#define vtext_SpacingBefore     (_vtextPredefs[_vtext_SpacingBefore])
#define vtext_SpacingAfter      (_vtextPredefs[_vtext_SpacingAfter])
#define vtext_Wrap              (_vtextPredefs[_vtext_Wrap])
#define vtext_TabWidth          (_vtextPredefs[_vtext_TabWidth])

/* Name constants defined by vtext */

#define vtext_Mode              (_vtextPredefs[_vtext_Mode])
#define vtext_View              (_vtextPredefs[_vtext_View])
#define vtext_Styles            (_vtextPredefs[_vtext_Styles])
#define vtext_Rulers            (_vtextPredefs[_vtext_Rulers])
#define vtext_StyleChanges      (_vtextPredefs[_vtext_StyleChanges])
#define vtext_StylePosition     (_vtextPredefs[_vtext_StylePosition])
#define vtext_StyleIndex        (_vtextPredefs[_vtext_StyleIndex])
#define vtext_RulerChanges      (_vtextPredefs[_vtext_RulerChanges])
#define vtext_RulerLine         (_vtextPredefs[_vtext_RulerLine])
#define vtext_RulerIndex        (_vtextPredefs[_vtext_RulerIndex])
#define vtext_Tabs              (_vtextPredefs[_vtext_Tabs])
#define vtext_TabStop           (_vtextPredefs[_vtext_TabStop])
#define vtext_TabType           (_vtextPredefs[_vtext_TabType])
#define vtext_Hidden            (_vtextPredefs[_vtext_Hidden])
#define vtext_TextData          (_vtextPredefs[_vtext_TextData])
#define vtext_DefaultStyle      (_vtextPredefs[_vtext_DefaultStyle])
#define vtext_DefaultRuler      (_vtextPredefs[_vtext_DefaultRuler])
#define vtext_Ruler   		(_vtextPredefs[_vtext_Ruler])
#define vtext_StyleTags		(_vtextPredefs[_vtext_StyleTags])
#define vtext_RulerTags		(_vtextPredefs[_vtext_RulerTags])
#define vtext_Start		(_vtextPredefs[_vtext_Start])
#define vtext_End		(_vtextPredefs[_vtext_End])
#define vtext_Before		(_vtextPredefs[_vtext_Before])
#define vtext_After		(_vtextPredefs[_vtext_After])
#define vtext_Attributes	(_vtextPredefs[_vtext_Attributes])
#define vtext_Left		(_vtextPredefs[_vtext_Left])
#define vtext_Center		(_vtextPredefs[_vtext_Center])
#define vtext_Right		(_vtextPredefs[_vtext_Right])
#define vtext_Full		(_vtextPredefs[_vtext_Full])
#define vtext_Style		(_vtextPredefs[_vtext_Style])
#define vtext_Data		(_vtextPredefs[_vtext_Data])
#define vtext_UndoObserver	(_vtextPredefs[_vtext_UndoObserver])

/* types for vtextGetOccurrenceType and vtextSetOccurrenceType */
enum {
    vtextINSERT_TEXT_OCCURRENCE		= 1,
    vtextDELETE_TEXT_OCCURRENCE		= 2,
    vtextPRE_INSERT_TEXT_OCCURRENCE	= 3,
    vtextPRE_DELETE_TEXT_OCCURRENCE	= 4,
    vtextRULER_CHANGE_OCCURRENCE	= 5,
    vtextSTYLE_CHANGE_OCCURRENCE	= 6,
    vtextSELECT_OCCURRENCE		= 7,
    vtextSET_SELECT_METHOD_OCCURRENCE	= 8,
    vtextCALCULATE_OCCURRENCE		= 9,
    vtextDESTROY_OCCURRENCE		= 10,
    _vtextOCCURRENCE_COUNT
};

/*
 * * * * * * * * * * PUBLIC TYPE DEFINITIONS * * * * * * * * * *
 */

#ifndef vtextselectionINCLUDED
typedef struct vtext			  vtext;
#endif
typedef struct vtextClass		  vtextClass;

typedef vtextselection			  vtextSelection;
typedef vtextselectionClass		  vtextSelectionClass;

typedef struct vtextStyle		  vtextStyle;
typedef struct vtextStyleClass		  vtextStyleClass;

typedef struct vtextRuler		  vtextRuler;
typedef struct vtextRulerClass		  vtextRulerClass;

typedef struct vtextTab			  vtextTab;

typedef struct vtextGraphic		  vtextGraphic;
typedef struct vtextGraphicClass	  vtextGraphicClass;

typedef struct vtextOccurrence		  vtextOccurrence;
typedef struct vtextOccurrenceClass	  vtextOccurrenceClass;

typedef struct vtextObserver		  vtextObserver;
typedef struct vtextObserverClass	  vtextObserverClass;
typedef vtextObserver			  vtextUndoObserver;

typedef vobservableObserverIterator	  vtextObserverIterator;

typedef struct vtextTag			  vtextTag;
typedef struct vtextStyleTag		  vtextStyleTag;
typedef struct vtextRulerTag		  vtextRulerTag;

typedef struct vtextTagIterator		  vtextTagIterator;
typedef struct vtextTagTransitionIterator vtextTagTransitionIterator;
typedef vtextTagTransitionIterator	  vtextStyleTransitionIterator;
typedef vtextTagTransitionIterator	  vtextRulerTransitionIterator;

typedef struct vtextAttributeSet	  vtextAttributeSet;
typedef struct vtextAttributeSetIterator  vtextAttributeSetIterator;

typedef vexException			  vtextNoAppliedStyleException;
typedef vexException			  vtextNoAppliedRulerException;

typedef vtextselectionPosition		  vtextPosition;

typedef struct vtextProcessInfo {
    vtext	    *editRec;
    long	    lineNumber;
    long	    position;
    short	    linePosition;
    long	    linesAffected;
    long	    linesAdded;
    long	    textGrowth;
    vtextselection  *selection;
} vtextProcessInfo;

typedef struct vtextLineMetricRec {
    long		position;
    vchar		*text;
    long		length;
    short		lineHeight;
    short		lineDescent;
    vfixed		lineOrigin;
    vfixed		lineWidth;
    vbool		firstLine;
} vtextLineMetricRec;

typedef struct vtextWidthInfo {
    vfixed	        pos;
    vtextStyle	        *style;
} vtextWidthInfo;

typedef short (*vtextProcessingFunc)(
    vchar 		*sourceText,
    long 		sourceLength,
    vchar 		*destinationText,
    long 		*destinationLength,
    vtextProcessInfo 	*pInfo
    );

typedef vbool (*vtextSearchFunc)(
    vtext 	*editRec,
    int 	ch,
    int 	prevch
    );

typedef int (*vtextGraphicProc)(
    vtext 	*editRec,
    void 	*data,
    vevent 	*event,
    int 	operation
    );


/*
 * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * *
 */

/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */

void vtextStartup(void);


/* Text Data Functions */

vtextClass *vtextGetDefaultClass(void);

/* Initialization and allocation */

vtextClass *vtextGetClass(
    vtext		*editRec
    );

vobject *vtextGetObject (
    vtext	*text
    );

vobservable *vtextGetObservable (
    vtext	*text
    );

vloadable *vtextGetLoadable (
    vtext	*text
    );

vinstance *vtextGetInstance (
    vtext	*text
    );

vtext *vtextCreate(void);

vtext *vtextCreateOfClass(
    vtextClass		*clas
    );

vtext *vtextClone(
    vtext	    	*editRec
    );

void vtextCopy(
    vtext		*editRec,
    vtext		*target
    );

void vtextCopyInit(
    vtext		*editRec,
    vtext		*target
    );

void vtextInit(
    vtext		*editRec
    );

void vtextInitOfClass(
    vtext		*editRec,
    vtextClass		*clas
    );

void vtextDestroy(
    vtext		*editRec
    );

void vtextDestroyText(
    vtext		*editRec
    );

vtext *vtextLoad(
    vresource           resource
    );

void vtextLoadInit(
    vtext               *editRec,
    vresource           resource
    );

void vtextStore(
    vtext               *editRec,
    vresource           resource
    );

void vtextDump(
    vtext               *editRec,
    FILE		*stream
    );

/* Editing operations */

void vtextInsert(
    vtext		*editRec,
    vtextSelection	*selection,
    const vchar		*textPtr,
    long		length
    );

void vtextDelete(
    vtext		*editRec,
    vtextSelection	*selection
    );

void vtextKey(
    vtext		*editRec,
    vtextSelection	*selection,
    int			ch		/* Cast to vchar */
    );

void vtextInsertGraphicObject(
    vtext	        *editRec,
    vtextSelection	*selection,
    vtextGraphic        *graphic
    );

void vtextInsertGraphicObjectOwned(
    vtext	        *editRec,
    vtextSelection	*selection,
    vtextGraphic        *graphic
    );

void vtextInsertGraphic(
    vtext	        *editRec,
    vtextSelection	*selection,
    vtextGraphicProc	graphicProc,
    void		*data
    );

long vtextSearch(
    vtext		*editRec,
    long		pos,
    vchar		*target,
    vchar		*result,
    long		resultMax,
    long		searchMethod,
    vtextSearchFunc	searchFunc,
    int			caseSensitive
    );

long vtextSimpleSearch(
    vtext		*editRec,
    long		pos,
    vchar		*target
    );

long vtextFunctionSearch(
    vtext		*editRec,
    long		pos,
    vtextSearchFunc	searchFunc
    );

void vtextProcess(
    vtext	   	*editRec,
    vtextSelection	*selection,
    vtextProcessingFunc	processingFunc,
    unsigned int   	flags,
    unsigned int	tabSettings
    );

void vtextTabsToSpaces(
    vtext	   	*editRec,
    vtextSelection	*selection,
    unsigned int	tabSettings
    );

void vtextSpacesToTabs(
    vtext	   	*editRec,
    vtextSelection	*selection,
    unsigned int	tabSettings
    );

void vtextAppendBlock(
    vtext		*editRec,
    vchar		*text,
    long		length,
    long		textAllocSize
    );

/* Text attribute modification */

void vtextSetData(
    vtext		*editRec,
    void		*data
    );

void vtextSetView(
    vtext	    	*editRec,
    int 	    	view
    );

void vtextSetDefaultStyle(
    vtext		*editRec,
    vtextStyle		*style
    );

void vtextSetDefaultStyleOwned(
    vtext		*editRec,
    vtextStyle		*style
    );

void vtextSetDefaultRuler(
    vtext		*editRec,
    vtextRuler		*ruler
    );

void vtextSetDefaultRulerOwned(
    vtext		*editRec,
    vtextRuler		*ruler
    );

void vtextSetOverstrike(
    vtext		*editRec,
    int 		overstrike
    );

void vtextSetAutoIndent(
    vtext		*editRec,
    int 		autoIndent
    );

void vtextSetShowHidden(
    vtext		*editRec,
    int			showHidden
    );

void vtextLock(
    vtext		*editRec
    );

void vtextUnlock(
    vtext		*editRec
    );

void vtextInstallObserver(
    vtext		*editRec,
    vtextObserver	*observer
    );

void vtextInstallObserverOwned(
    vtext		*editRec,
    vtextObserver	*observer
    );

void vtextUninstallObserver(
    vtext		*editRec,
    vtextObserver	*observer
    );

void vtextSetUndoObserver(
    vtext		*editRec,
    vtextObserverClass	*observerClass
    );

void vtextSetUndoActionList(
    vtext		*editRec,
    vundoActionList  	*list
    );

/* Text attribute access */

void *vtextGetData(
    vtext		*editRec
    );

vbyte vtextGetView(
    vtext	    	*editRec
    );

vtextStyle *vtextGetDefaultStyle(
    vtext		*editRec
    );

vtextRuler *vtextGetDefaultRuler(
    vtext		*editRec
    );

vbool vtextIsOverstrike(
    vtext		*editRec
    );

vbool vtextIsAutoIndent(
    vtext		*editRec
    );

vbool vtextGetShowHidden(
    vtext		*editRec
    );

vbool vtextIsLocked(
    vtext		*editRec);

vtextObserverClass *vtextGetUndoObserver(
    vtext		*editRec
    );

vundoActionList *vtextGetUndoActionList(
    vtext		*editRec
    );

/* File Input/Output */

void vtextImportFile(
    vtext		*editRec,
    const vfsPath	*filePath
    );

void vtextExportFile(
    vtext		*editRec,
    const vfsPath	*filePath
    );

/* Text Occurrence Entrypoints */

vtextOccurrenceClass *vtextGetDefaultOccurrenceClass(
    void
    );

vtextOccurrenceClass *vtextGetOccurrenceClass(
    vtextOccurrence	 *occurrence
    );

voccurrence *vtextGetOccurrenceOccurrence(
    vtextOccurrence	 *occurrence
    );

vinstance *vtextGetOccurrenceInstance(
    vtextOccurrence	 *occurrence
    );

vtextOccurrence *vtextCreateOccurrenceOfClass(
    vtextOccurrenceClass *clas
    );

vtextOccurrence *vtextCreateOccurrence(
    );

void vtextInitOccurrenceOfClass(
    vtextOccurrence	 *occurrence,
    vtextOccurrenceClass *clas
    );

void vtextInitOccurrence(
    vtextOccurrence	 *occurrence
    );

void vtextDestroyOccurrence(
    vtextOccurrence	 *occurrence
    );

vtext *vtextGetOccurrenceText(
    vtextOccurrence	 *occurrence
    );

int vtextGetOccurrenceType(
    vtextOccurrence	 *occurrence
    );

vtextSelection *vtextGetOccurrenceSelection(
    vtextOccurrence	 *occurrence
    );

vtextRuler *vtextGetOccurrenceRuler(
    vtextOccurrence	 *occurrence
    );

vtextStyle *vtextGetOccurrenceStyle(
    vtextOccurrence	 *occurrence
    );

int vtextGetOccurrenceState(
    vtextOccurrence	 *occurrence
    );

long vtextGetOccurrencePosition(
    vtextOccurrence	 *occurrence
    );

long vtextGetOccurrenceDelta(
    vtextOccurrence	 *occurrence
    );

long vtextGetOccurrenceStart(
    vtextOccurrence	 *occurrence
    );

long vtextGetOccurrenceEnd(
    vtextOccurrence	 *occurrence
    );

long vtextGetOccurrenceStartLine(
    vtextOccurrence	 *occurrence
    );

long vtextGetOccurrenceEndLine(
    vtextOccurrence	 *occurrence
    );

void vtextSetOccurrenceText(
    vtextOccurrence	 *occurrence,
    vtext		 *text
    );

void vtextSetOccurrenceType(
    vtextOccurrence	 *occurrence,
    int			  type
    );

void vtextSetOccurrenceSelection(
    vtextOccurrence	 *occurrence,
    vtextSelection	 *selection
    );

void vtextSetOccurrenceRuler(
    vtextOccurrence	 *occurrence,
    vtextRuler		 *ruler
    );

void vtextSetOccurrenceStyle(
    vtextOccurrence	 *occurrence,
    vtextStyle		 *style
    );

void vtextSetOccurrenceState(
    vtextOccurrence	 *occurrence,
    int			  state
    );

void vtextSetOccurrencePosition(
    vtextOccurrence	 *occurrence,
    long		  position
    );

void vtextSetOccurrenceDelta(
    vtextOccurrence	 *occurrence,
    long		  delta
    );

void vtextSetOccurrenceStart(
    vtextOccurrence	 *occurrence,
    long		  startLine
    );

void vtextSetOccurrenceEnd(
    vtextOccurrence	 *occurrence,
    long		  endLine
    );

void vtextSetOccurrenceStartLine(
    vtextOccurrence	 *occurrence,
    long		  startLine
    );

void vtextSetOccurrenceEndLine(
    vtextOccurrence	 *occurrence,
    long		  endLine
    );


/* Observer Initialization and allocation */

vtextObserverClass *vtextGetDefaultObserverClass(void);

vtextObserverClass *vtextGetDefaultUndoObserverClass(void);

vtextObserverClass *vtextGetObserverClass(
    vtextObserver	*observer
    );

vobserver *vtextGetObserverObserver (
    vtextObserver	*observer
    );

vobservable *vtextGetObserverObservable (
    vtextObserver	*observer
    );

vloadable *vtextGetObserverLoadable (
    vtextObserver	*observer
    );

vinstance *vtextGetObserverInstance (
    vtextObserver	*observer
    );

vtextObserver *vtextCreateObserver(void);

vtextObserver *vtextCreateObserverOfClass(
    vtextObserverClass	*clas
    );

vtextObserver *vtextCloneObserver(
    vtextObserver	*observer
    );

void vtextCopyObserver(
    vtextObserver	*observer,
    vtextObserver	*target
    );

void vtextCopyInitObserver(
    vtextObserver	*observer,
    vtextObserver	*target
    );

void vtextInitObserver(
    vtextObserver	*observer
    );

void vtextInitObserverOfClass(
    vtextObserver	*observer,
    vtextObserverClass	*clas
    );

void vtextDestroyObserver(
    vtextObserver	*observer
    );

/* Observer attribute modification and access */
 
void vtextSetObserverData(
    vtextObserver	*observer,
    void		*data
    );

void vtextDisableObserver(
    vtextObserver	*observer
    );

void vtextEnableObserver(
    vtextObserver	*observer
    );

void *vtextGetObserverData(
    vtextObserver	*observer
    );

vbool vtextObserverIsEnabled(
    vtextObserver	*observer
    );

void vtextSetObserverOwner(
    vtextObserver	*observer,
    vtext		*owner
    );

vtext *vtextGetObserverOwner(
    vtextObserver	*observer
    );

/* Observer Iterator */

void vtextInitObserverIterator(
    vtextObserverIterator	*iterator,
    vtext			*editRec
    );

vbool vtextNextObserverIterator(
    vtextObserverIterator	*iterator
    );

void vtextDestroyObserverIterator(
    vtextObserverIterator	*iterator
    );

vtextObserver *vtextGetObserverIteratorObserver(
    vtextObserverIterator	*iterator
    );

/* Graphic Operations */

vtextGraphicClass *vtextGetDefaultGraphicClass(void);

vtextGraphicClass *vtextGetGraphicClass(
    vtextGraphic	*graphic
    );

vloadable *vtextGetGraphicLoadable(
    vtextGraphic	*graphic
    );

vtextGraphic *vtextCreateGraphic(void);

vtextGraphic *vtextCreateGraphicOfClass(
    vtextGraphicClass	*clas
    );

vtextGraphic *vtextCloneGraphic(
    vtextGraphic	*graphic
    );

void vtextCopyGraphic(
    vtextGraphic	*graphic,
    vtextGraphic	*target
    );

void vtextCopyInitGraphic(
    vtextGraphic	*graphic,
    vtextGraphic	*target
    );

void vtextInitGraphic(
    vtextGraphic	*graphic
    );

void vtextInitGraphicOfClass(
    vtextGraphic	*graphic,
    vtextGraphicClass	*clas
    );

void vtextDestroyGraphic(
    vtextGraphic	*graphic
    );

vtextGraphic *vtextLoadGraphic(
    vresource           resource
    );

void vtextLoadInitGraphic(
    vtextGraphic	*graphic,
    vresource           resource
    );

void vtextStoreGraphic(
    vtextGraphic	*graphic,
    vresource           resource
    );

void vtextDrawGraphic(
    vtextGraphic	*graphic
    );

void vtextDrawGraphicWith(
    vtextGraphic	*graphic,
    vdrawcontext        *context
    );

/* Graphic attribute modification and access */
 
void vtextSetGraphicData(
    vtextGraphic	*graphic,
    void		*data
    );

void vtextSetGraphicMetrics(
    vtextGraphic	*graphic,
    int			width,
    int			height,
    int			descent
    );

void vtextSetGraphicWidth(
    vtextGraphic	*graphic,
    int			width
    );

void vtextSetGraphicHeight(
    vtextGraphic	*graphic,
    int			height
    );

void vtextSetGraphicDescent(
    vtextGraphic	*graphic,
    int			descent
    );

void *vtextGetGraphicData(
    vtextGraphic	*graphic
    );

int vtextGetGraphicWidth(
    vtextGraphic	*graphic
    );

int vtextGetGraphicHeight(
    vtextGraphic	*graphic
    );

int vtextGetGraphicDescent(
    vtextGraphic	*graphic
    );

vtext *vtextGetGraphicOwner(
    vtextGraphic	*graphic
    );

/* Tag operations */

vtextTag *vtextCreateTag(void);

void vtextInitTag(
    vtextTag		*tag
    );

void vtextDestroyTag(
    vtextTag		*tag
    );

void vtextAddTag(
    vtext		*editRec,
    vtextTag		*tag
    );

void vtextRemoveTag(
    vtext		*editRec,
    vtextTag		*tag
    );

void vtextWarpTag(
    vtext		*editRec,
    vtextTag		*tag,
    long		position,
    long		delta
    );

void vtextSetTagRange(
    vtextTag		*tag,
    long		start,
    long		end
    );

void vtextDumpTag(
    vtextTag		*tag,
    FILE		*theStream
    );

void vtextInitTagIterator(
    vtextTagIterator	*iterator,
    vtext		*editRec,
    long		pos
    );

void vtextInitNamedTagIterator(
    vtextTagIterator	*iterator,
    vtext		*editRec,
    const vname		*name,
    long		pos
    );

int vtextNextTagIterator(
    vtextTagIterator	*iterator
    );

void vtextDestroyTagIterator(
    vtextTagIterator	*iterator
    );

vtextTag *vtextGetTagIteratorTag(
    vtextTagIterator	*iterator
    );

void vtextInitTagTransitionIterator(
    vtextTagTransitionIterator		*iterator,
    vtext				*editRec,
    const vname				*name,
    long				position
    );

int vtextNextTagTransitionIterator(
    vtextTagTransitionIterator          *iterator
    );

void vtextDestroyTagTransitionIterator(
    vtextTagTransitionIterator          *iterator
    );

vtextTag **vtextGetTagTransitionIteratorTags(
    vtextTagTransitionIterator          *iterator
    );

int vtextGetTagTransitionIteratorCount(
    vtextTagTransitionIterator          *iterator
    );
     
long vtextGetTagTransitionIteratorPosition(
    vtextTagTransitionIterator          *iterator
    );

/* Tag attribute modification/access */

void vtextSetTagName(
    vtextTag		*tag,
    const vname		*name
    );

void vtextSetTagPermanent(
    vtextTag		*tag,
    int			permanent
    );

void vtextSetTagFixed(
    vtextTag		*tag,
    int			fixed
    );

const vname *vtextGetTagName(
    vtextTag		*tag
    );

vbool vtextIsTagPermanent(
    vtextTag		*tag
    );

vbool vtextIsTagFixed(
    vtextTag		*tag
    );

int vtextGetTagStart(
    vtextTag		*tag
    );

int vtextGetTagEnd(
    vtextTag		*tag
    );

/* Style Initialization and allocation */

vtextStyleClass *vtextGetDefaultStyleClass(void);

vtextStyleClass *vtextGetStyleClass(
    vtextStyle		*style
    );

vloadable *vtextGetStyleLoadable(
    vtextStyle		*style
    );

vtextStyle *vtextCreateStyle(void);

vtextStyle *vtextCreateStyleOfClass(
    vtextStyleClass	*clas
    );

vtextStyle *vtextCloneStyle(
    vtextStyle		*style
    );

void vtextCopyStyle(
    vtextStyle		*style,
    vtextStyle		*target
    );

void vtextCopyInitStyle(
    vtextStyle		*style,
    vtextStyle		*target
    );

void vtextInitStyle(
    vtextStyle		*style
    );

void vtextInitStyleOfClass(
    vtextStyle		*style,
    vtextStyleClass	*clas
    );

void vtextDestroyStyle(
    vtextStyle		*style
    );

vtextStyle *vtextLoadStyle(
    vresource           resource
    );

void vtextLoadInitStyle(
    vtextStyle		*style,
    vresource           resource
    );

void vtextStoreStyle(
    vtextStyle		*style,
    vresource           resource
    );

vtextStyle *vtextGetGlobalDefaultStyle(void);

void vtextSetGlobalDefaultStyle(
    vtextStyle 		*style
    );

void vtextSetGlobalDefaultStyleOwned(
    vtextStyle		*style
    );

void vtextDumpStyle(
    vtextStyle		*style,
    FILE		*theStream
    );

/* Style Operations */

void vtextInstallStyle(
    vtext		*editRec,
    vtextStyle		*style
    );

void vtextInstallStyleOwned(
    vtext		*editRec,
    vtextStyle		*style
    );

void vtextRemoveStyle(
    vtext		*editRec,
    vtextStyle		*style
    );

void vtextApplyStyle(
    vtext		*editRec,
    vtextSelection	*selection,
    vtextStyle		*style
    );

void vtextApplyStyleRange(
    vtext		*editRec,
    long		start,
    long		end,
    vtextStyle		*style
    );

void vtextUnapplyStyle(
    vtext		*editRec,
    vtextSelection	*selection,
    vtextStyle		*style
    );

void vtextUnapplyStyleRange(
    vtext		*editRec,
    long		start,
    long		end,
    vtextStyle		*style
    );

void vtextMergeStyles(
    vtextStyle		*style,
    vtextStyle		*toStyle
    );

void vtextMergeStyleTags(
    vtext		*editRec,
    vtextStyleTag	**styleTags,
    int			count,
    vtextStyle		*newStyle
    );

int vtextTagsInRange(
    vtext *editRec, 
    const vname *name, 
    long start,
    long end, 
    vtextTag ***tags, 
    int endpointsOnly, 
    int sorted
    );

vbool vtextCompareStyles(
    vtextStyle		*style1,
    vtextStyle		*style2
    );

vfont *vtextDetermineStyleFont(
    vtextStyle		*style
    );

vtextStyle *vtextFindStyle(
    vtext		*editRec,
    vtextStyle		*style
    );

vtextStyle *vtextStyleAtPosition(
    vtext		*editRec,
    long		position
    );

short vtextStyleCount(
    vtext		*editRec
    );

vtextStyle *vtextGetStyleAt(
    vtext		*editRec,
    int			index
    );

void vtextReplaceStyle(
    vtext		*editRec,
    vtextStyle		*oldStyle,
    vtextStyle		*newStyle
    );

void vtextSetStyleAutoCalc(
    vtext		*editRec,
    vtextStyle		*style,
    int			autoCalc
    );

vbool vtextGetStyleAutoCalc(
    vtext		*editRec,
    vtextStyle		*style
    );

void vtextCalcStyle(
    vtext		*editRec,
    vtextStyle		*style
    );

/* Style Attributes */

void vtextSetStyleAttribute(
    vtextStyle		*style,
    const vname		*attribute,
    const void		*value
    );

void vtextSetStyleAttributeScalar(
    vtextStyle		*style,
    const vname		*attribute,
    long		scalar
    );

int vtextGetStyleAttributeType(
    vtextStyle		*style,
    const vname		*attribute
    );

const void *vtextGetStyleAttribute(
    vtextStyle		*style,
    const vname		*attribute
    );

long vtextGetStyleAttributeScalar(
    vtextStyle		*style,
    const vname		*attribute
    );

void vtextRemoveStyleAttribute(
    vtextStyle		*style,
    const vname		*attribute
    );

vtext *vtextGetStyleOwner(
    vtextStyle		*style
    );

void vtextSetStyleOwner(
    vtextStyle		*style,
    vtext		*editRec
    );

/* Style - transition iterator */

void vtextInitStyleTransitionIterator(
    vtextStyleTransitionIterator	*iterator,
    vtext				*editRec,
    long				position
    );

int vtextNextStyleTransitionIterator(
    vtextStyleTransitionIterator          *iterator
    );

void vtextDestroyStyleTransitionIterator(
    vtextStyleTransitionIterator          *iterator
    );

vtextStyleTag **vtextGetStyleTransitionIteratorStyles(
    vtextStyleTransitionIterator          *iterator
    );

long vtextGetStyleTransitionIteratorCount(
    vtextStyleTransitionIterator          *iterator
    );
     
long vtextGetStyleTransitionIteratorPosition(
    vtextStyleTransitionIterator          *iterator
    );

/* Ruler Initialization and allocation */

vtextRulerClass *vtextGetDefaultRulerClass(void);

vtextRulerClass *vtextGetRulerClass(
    vtextRuler		*ruler
    );

vloadable *vtextGetRulerLoadable(
    vtextRuler		*ruler
    );

vtextRuler *vtextCreateRuler(void);

vtextRuler *vtextCreateRulerOfClass(
    vtextRulerClass	*clas
    );

vtextRuler *vtextCloneRuler(
    vtextRuler		*ruler
    );

void vtextCopyRuler(
    vtextRuler		*ruler,
    vtextRuler		*target
    );

void vtextCopyInitRuler(
    vtextRuler		*ruler,
    vtextRuler		*target
    );

void vtextInitRuler(
    vtextRuler		*ruler
    );

void vtextInitRulerOfClass(
    vtextRuler		*ruler,
    vtextRulerClass	*clas
    );

void vtextDestroyRuler(
    vtextRuler		*ruler
    );

vtextRuler *vtextLoadRuler(
    vresource           resource
    );

void vtextLoadInitRuler(
    vtextRuler		*ruler,
    vresource           resource
    );

void vtextStoreRuler(
    vtextRuler		*ruler,
    vresource           resource
    );

vtextRuler *vtextGetGlobalDefaultRuler(void);

void vtextSetGlobalDefaultRuler(
    vtextRuler 		*ruler
    );

void vtextSetGlobalDefaultRulerOwned(
    vtextRuler 		*ruler
    );

void vtextDumpRuler(
    vtextRuler		*ruler,
    FILE		*theStream
    );

/* Ruler operations */

void vtextInstallRuler(
    vtext		*editRec,
    vtextRuler		*ruler
    );

void vtextInstallRulerOwned(
    vtext		*editRec,
    vtextRuler		*ruler
    );

void vtextRemoveRuler(
    vtext		*editRec,
    vtextRuler		*ruler
    );

void vtextApplyRuler(
    vtext		*editRec,
    vtextSelection	*selection,
    vtextRuler		*ruler
    );

void vtextApplyRulerRange(
    vtext		*editRec,
    long		 startLine,
    long		 endLine,
    vtextRuler		*ruler
    );

void vtextUnapplyRuler(
    vtext		*editRec,
    vtextSelection	*selection,
    vtextRuler		*ruler
    );

void vtextUnapplyRulerRange(
    vtext		*editRec,
    long		 startLine,
    long		 endLine,
    vtextRuler		*ruler
    );

void vtextMergeRulers(
    vtextRuler		*ruler,
    vtextRuler		*toRuler
    );

void vtextMergeRulerTags(
    vtext		*editRec,
    vtextRulerTag	**rulerTags,
    int			count,
    vtextRuler		*newRuler
    );

vbool vtextCompareRulers(
    vtextRuler		*ruler1,
    vtextRuler		*ruler2
    );

vtextRuler *vtextFindRuler(
    vtext		*editRec,
    vtextRuler		*ruler
    );

vtextRuler *vtextRulerAtLine(
    vtext		*editRec,
    long		lineNumber
    );

short vtextRulerCount(
    vtext		*editRec
    );

vtextRuler *vtextGetRulerAt(
    vtext		*editRec,
    int			index
    );

void vtextCalcRuler(
    vtext		*editRec,
    vtextRuler		*ruler
    );

void vtextReplaceRuler(
    vtext		*editRec,
    vtextRuler		*oldRuler,
    vtextRuler		*newRuler
    );

void vtextSetRulerAutoCalc(
    vtext		*editRec,
    vtextRuler		*ruler,
    int			autoCalc
    );

vbool vtextGetRulerAutoCalc(
    vtext		*editRec,
    vtextRuler		*ruler
    );

/* Ruler Attributes */

void vtextSetRulerAttribute(
    vtextRuler		*ruler,
    const vname		*attribute,
    const void		*value
    );

void vtextSetRulerAttributeScalar(
    vtextRuler		*ruler,
    const vname		*attribute,
    long		value
    );

int vtextGetRulerAttributeType(
    vtextRuler		*ruler,
    const vname		*attribute
    );

const void *vtextGetRulerAttribute(
    vtextRuler		*ruler,
    const vname		*attribute
    );

long vtextGetRulerAttributeScalar(
    vtextRuler		*ruler,
    const vname		*attribute
    );

void vtextRemoveRulerAttribute(
    vtextRuler		*ruler,
    const vname		*attribute
    );

vtext *vtextGetRulerOwner(
    vtextRuler		*ruler
    );

void vtextSetRulerOwner(
    vtextRuler		*ruler,
    vtext		*editRec
    );

/* Ruler - transition iterator */

void vtextInitRulerTransitionIterator(
    vtextRulerTransitionIterator	*iterator,
    vtext				*editRec,
    int					lineNumber
    );

int vtextNextRulerTransitionIterator(
    vtextRulerTransitionIterator          *iterator
    );

void vtextDestroyRulerTransitionIterator(
    vtextRulerTransitionIterator          *iterator
    );

vtextRulerTag **vtextGetRulerTransitionIteratorRulers(
    vtextRulerTransitionIterator          *iterator
    );

int vtextGetRulerTransitionIteratorCount(
    vtextRulerTransitionIterator          *iterator
    );
     
int vtextGetRulerTransitionIteratorLine(
    vtextRulerTransitionIterator          *iterator
    );

/* Ruler - tab operations */

void vtextRulerAddTab(
    vtext		*editRec,
    vtextRuler		*ruler,
    vfixed		position,
    int			tabType
    );

int vtextRulerRemoveTab(
    vtext		*editRec,
    vtextRuler		*ruler,
    vfixed		position
    );

vfixed vtextRulerFindTab(
    vtext		*editRec,
    vtextRuler		*ruler,
    vfixed		position,
    int			*tabType
    );

void vtextRulerResetTabs(
    vtext		*editRec,
    vtextRuler		*ruler
    );

vfixed vtextRulerMaxTab(
    vtext		*editRec,
    vtextRuler		*ruler
    );

int vtextRulerTabCount(
    vtext		*editRec,
    vtextRuler		*ruler
    );

vtextTab *vtextRulerTabs(
    vtext		*editRec,
    vtextRuler		*ruler
    );

vfixed vtextRulerGetTabAt(
    vtext		*editRec,
    vtextRuler		*ruler,
    int			 index
    );

int vtextRulerGetTabTypeAt(
    vtext		*editRec,
    vtextRuler		*ruler,
    int			 index
    );

int vtextRulerFindTabIndex(
    vtext		*editRec,
    vtextRuler		*ruler,
    vfixed		position
    );

/* Attribute Sets */

vtextAttributeSet *vtextCreateAttributeSet(void);

void vtextCopyAttributeSet(
    vtextAttributeSet		*set,
    vtextAttributeSet		*target
    );

vtextAttributeSet *vtextCloneAttributeSet(
    vtextAttributeSet		*set
    );

void vtextDestroyAttributeSet(
    vtextAttributeSet		*set
    );

void vtextAddAttribute(
    vtextAttributeSet		*set,
    const vname			*name,
    int				 type
    );

void vtextRemoveAttribute(
    vtextAttributeSet		*set,
    const vname			*name
    );

int vtextGetAttributeType(
    vtextAttributeSet		*set, 
    const vname			*name
    );

void vtextInitAttributeSetIterator(
    vtextAttributeSetIterator	*iterator,
    vtextAttributeSet		*set
    );

int vtextNextAttributeSetIterator(
    vtextAttributeSetIterator	*iterator
    );

void vtextDestroyAttributeSetIterator(
    vtextAttributeSetIterator	*iterator
    );

const vname *vtextGetAttributeSetIteratorName(
    vtextAttributeSetIterator	*iterator
    );

int vtextGetAttributeSetIteratorType(
    vtextAttributeSetIterator	*iterator
    );
     
/* Hidden text */

void vtextHide(
    vtext		*editRec,
    vtextSelection	*selection
    );

void vtextShow(
    vtext		*editRec,
    vtextSelection	*selection
    );

/* Accessing the text object */

long vtextLength(
    vtext		*editRec
    );

long vtextLines(
    vtext		*editRec
    );

/* Utilities and General Info */

long vtextLinePosition(
    vtext		*editRec,
    long		lineNum
    );

long vtextLineFromPosition(
    vtext		*editRec,
    long		position
    );

void vtextLineMetrics(
    vtext		*editRec,
    long		lineNum,
    vtextLineMetricRec	*metrics
    );

long vtextHeightOfLines(
    vtext		*editRec,
    long		startLine,
    long		endLine
    );

long vtextLinesInHeight(
    vtext		*editRec,
    long		height,
    long		startLineNum
    );

void vtextLineRange(
    vtext		*editRec,
    long		lineNumber,
    long		*startLineNumber,
    long		*endLineNumber
    );

void vtextPositionParagraph(
    vtext *editRec, 
    long position,
    long *start, 
    long *end
    );

vchar *vtextGetTextAt(
    vtext		*editRec,
    long		pos
    );

long vtextGetText(
    vtext		*editRec,
    vtextSelection	*selection,
    vchar		*text,
    long		length
    );

long vtextGetTextRange(
    vtext		*editRec,
    long		start,
    long		end,
    vchar		*text,
    long		length
    );

long vtextGetTextLine(
    vtext		*editRec,
    vtextSelection	*selection,
    vchar		*buffer,
    long		length,
    long		theLineNumber
    );

vscribe *vtextScribeText(
    vtext		*editRec,
    vtextSelection	*selection
    );

vscribe *vtextScribeTextRange(
    vtext		*editRec,
    long		start,
    long		end
    );

vscribe *vtextScribeTextLines(
    vtext		*editRec,
    long		startLine,
    long		endLine
    );

 
void vtextCopyText(
    vtext               *editRec,
    vtextSelection      *selection,
    vtextSelection      *destSelection
    );
 
vbool vtextIsWordBreak(
    vtext		*editRec,
    vchar		*text,
    long		length
    );

vbool vtextIsWrapBreak(
    vtext		*editRec,
    vchar		*text,
    long		length
    );

short vtextValidatePos(
    vtext		*editRec,
    long		*pos
    );

long vtextPointToPosition(
    vtext		*editRec,
    long                lineNum,
    int			pt,
    short               *linePos
    );

int vtextPositionToPoint(
    vtext		*editRec,
    long                pos
    );

short vtextAdjustPositions(
    long		*startPos,
    long		*endPos,
    long		pos,
    long		delta
    );

void vtextPosCheck(
    long		*x,
    long		*y
    );

void vtextCheckEndOfLine(
    vchar		*ptr,
    long		*length,
    int			fromend
    );

/* Low-level routines */

void vtextCalculate(
    vtext		*editRec
    );

vtextWidthInfo *vtextCalcWidths(
    vtext 		*editRec,
    vtextSelection	*selection,
    vchar		*text,
    long		*length,
    long		position,
    long		checkForStart
    );

vbool vtextIsInWord(
    vtext		*editRec,
    long		position,
    vchar		c
    );

vbool vtextCanWrapAfter(
    vtext		*editRec,
    long		position,
    vchar		c
    );

vimage *vtextGetInvisibleImage(
    int			invisible
    );

void vtextSetInvisibleImage(
    int			invisible,
    vimage              *image
    );

vimage *vtextDetermineInvisibleImage(
    int			ch
    );

void _vtextSetReturnValue(
    vtext		*editRec,
    int			returnValue
    );

/* Exception Functions */

const vexClass *vtextGetNoAppliedStyleExceptionClass(
    void
    );

const vexClass *vtextGetNoAppliedRulerExceptionClass(
    void
    );

vtextNoAppliedStyleException *vtextGetNoAppliedStyleException(
    void
    );

vtextNoAppliedRulerException *vtextGetNoAppliedRulerException(
    void
    );

/* Deprecated Functions */

vtextSelection *vtextCreateSelection(vtext *editRec);
vtextSelection *vtextCloneSelection(vtext *editRec, vtextSelection *selection);
void vtextCopySelection(vtextSelection *selection, vtextSelection *target);
void vtextCopyInitSelection(vtext *editRec, vtextSelection *selection,
			    vtextSelection *target);
void vtextInitSelection(vtext *editRec, vtextSelection *selection);
void vtextDestroySelection(vtext *editRec, vtextSelection *selection);
void vtextSetSelectMethod(vtext *editRec, vtextSelection *selection,
			  int method);
vbyte vtextGetSelectMethod(vtext *editRec, vtextSelection *selection);
void vtextSelectRange(vtext *editRec, vtextSelection *selection,
		      long start, long end);
void vtextSelectRangeRectangular(vtext *editRec, vtextSelection *selection,
				 long start, long end, int xstart, int xend);
void vtextSelectLines(vtext *editRec, vtextSelection *selection,
		      long start, long end, int location);
void vtextSelectTag(vtext *editRec, vtextSelection *selection, vtextTag *tag);

long vtextSelectedLines(vtextSelection *selection);
long vtextCurrLineNum(vtextSelection *selection);
long vtextSelectionStart(vtextSelection *selection);
long vtextSelectionEnd(vtextSelection *selection);
long vtextSelectionCaret(vtextSelection *selection);
long vtextSelectionLength(vtextSelection *selection);
long vtextStartPos(vtextSelection *selection);
long vtextEndPos(vtextSelection *selection);
int vtextStartPixel(vtextSelection *selection);
int vtextEndPixel(vtextSelection *selection);

vtextStyle   *vtextAddStyle(vtext *editRec);
vtextStyle   *vtextCreateGlobalStyle(void);
vbool         vtextIsStyleGraphic(vtext *editRec, vtextStyle *style);
void          vtextSetStyleFont(vtext *editRec, vtextStyle *style,
				vfont *font, vbool computeMetrics);
void          vtextSetStyleData(vtext *editRec, vtextStyle *style, void *data);
void          vtextSetStyleDescent(vtext *editRec, vtextStyle *style,
				   int descent);
void          vtextSetStyleAscent(vtext *editRec, vtextStyle *style,
				  int ascent);
void          vtextSetStyleSize(vtext *editRec, vtextStyle *style,
				int size);
void          vtextSetStyleColor(vtext *editRec, vtextStyle *style,
				 vcolor *color);
void          vtextSetStyleBackgroundColor(vtext *editRec, vtextStyle *style,
					   vcolor *color);
void          vtextSetStyleBold(vtext *editRec, vtextStyle *style,
				int bold);
void          vtextSetStyleUnderline(vtext *editRec, vtextStyle *style,
				     int underline);
void          vtextSetStyleInvert(vtext *editRec, vtextStyle *style,
				  int invert);
void          vtextSetStyleItalic(vtext *editRec, vtextStyle *style,
				  int italic);
void          vtextSetStyleStrikethru(vtext *editRec, vtextStyle *style,
				      int strikethru);
void          vtextSetStyleHidden(vtext *editRec, vtextStyle *style,
				  int hidden);
vfont 	     *vtextGetStyleFont(vtext *editRec, vtextStyle *style);
void         *vtextGetStyleData(vtext *editRec, vtextStyle *style);
int 	      vtextGetStyleDescent(vtext *editRec, vtextStyle *style);
int 	      vtextGetStyleAscent(vtext *editRec, vtextStyle *style);
int 	      vtextGetStyleSize(vtext *editRec, vtextStyle *style);
vcolor       *vtextGetStyleColor(vtext *editRec, vtextStyle *style);
vcolor       *vtextGetStyleBackgroundColor(vtext *editRec, vtextStyle *style);
int           vtextGetStyleBold(vtext *editRec, vtextStyle *style);
int           vtextGetStyleUnderline(vtext *editRec, vtextStyle *style);
int           vtextGetStyleInvert(vtext *editRec, vtextStyle *style);
int           vtextGetStyleItalic(vtext *editRec, vtextStyle *style);
int           vtextGetStyleStrikethru(vtext *editRec, vtextStyle *style);
int           vtextGetStyleHidden(vtext *editRec, vtextStyle *style);
vtextGraphic *vtextGetStyleGraphic(vtext *editRec, vtextStyle *style);
vtextRuler   *vtextAddRuler(vtext *editRec);
vtextRuler   *vtextCreateGlobalRuler(void);
void          vtextSetRulerJustification(vtext *editRec, vtextRuler *ruler,
					 int justification);
void          vtextSetRulerAscent(vtext *editRec, vtextRuler *ruler,
				  int ascent);
void          vtextSetRulerDescent(vtext *editRec, vtextRuler *ruler,
				   int descent);
void          vtextSetRulerWrap(vtext *editRec, vtextRuler *ruler,
				int wrap);
void          vtextSetRulerLeftIndent(vtext *editRec, vtextRuler *ruler,
				      vfixed indent);
void          vtextFSetRulerLeftIndent(vtext *editRec, vtextRuler *ruler,
				       double indent);
void          vtextSetRulerRightIndent(vtext *editRec, vtextRuler *ruler,
				       vfixed indent);
void          vtextFSetRulerRightIndent(vtext *editRec, vtextRuler *ruler,
				        double indent);
void          vtextSetRulerFirstLineIndent(vtext *editRec, vtextRuler *ruler,
					   vfixed indent);
void          vtextFSetRulerFirstLineIndent(vtext *editRec, vtextRuler *ruler,
					    double indent);
void          vtextSetRulerTabWidth(vtext *editRec, vtextRuler *ruler,
				    vfixed tabWidth);
void          vtextFSetRulerTabWidth(vtext *editRec, vtextRuler *ruler,
				     double tabWidth);
void	      vtextSetRulerSpacingBefore(vtext *editRec, vtextRuler *ruler,
					 int spacing);
void	      vtextSetRulerSpacingAfter(vtext *editRec, vtextRuler *ruler,
					int spacing);
void          vtextSetRulerData(vtext *editRec, vtextRuler *ruler, void *data);
vbyte         vtextGetRulerJustification(vtext *editRec, vtextRuler *ruler);
short         vtextGetRulerAscent(vtext *editRec, vtextRuler *ruler);
short         vtextGetRulerDescent(vtext *editRec, vtextRuler *ruler);
vbool         vtextGetRulerWrap(vtext *editRec, vtextRuler *ruler);
vfixed        vtextGetRulerLeftIndent(vtext *editRec, vtextRuler *ruler);
double        vtextFGetRulerLeftIndent(vtext *editRec, vtextRuler *ruler);
vfixed        vtextGetRulerRightIndent(vtext *editRec, vtextRuler *ruler);
double        vtextFGetRulerRightIndent(vtext *editRec, vtextRuler *ruler);
vfixed        vtextGetRulerFirstLineIndent(vtext *editRec, vtextRuler *ruler);
double        vtextFGetRulerFirstLineIndent(vtext *editRec, vtextRuler *ruler);
vfixed        vtextGetRulerTabWidth(vtext *editRec, vtextRuler *ruler);
double        vtextFGetRulerTabWidth(vtext *editRec, vtextRuler *ruler);
void          *vtextGetRulerData(vtext *editRec, vtextRuler *ruler);
short	      vtextGetRulerSpacingBefore(vtext *editRec, vtextRuler *ruler);
short	      vtextGetRulerSpacingAfter(vtext *editRec, vtextRuler *ruler);
long 	      vtextSelectedWrappedLines(vtextSelection *selection);
long 	      vtextWrappedLines(vtext *editRec);
void 	      vtextSetStyle(vtext *editRec, vtextSelection *selection,
			    vtextStyle *style);
void 	      vtextSetRuler(vtext *editRec, vtextSelection *selection,
			    vtextRuler *ruler);
void	      vtextDestroyGlobalStyle(vtextStyle *style);
void	      vtextDestroyGlobalRuler(vtextRuler *ruler);
void 	      vtextCheckLength(vchar *ptr, short *length, int fromend);

vtextPosition *vtextGetPosition(vtextSelection *selection);

/*
 * * * * * * * * * PRIVATE TEXT MANAGER GLOBAL VARIABLES * * * * * * * * * *
 */

extern vportLINK const vchar 		*_vtextPredefs[];

extern vportLINK const vexClass            _vtextNoAppliedStyleExceptionClass;
extern vportLINK const vexClass            _vtextNoAppliedRulerExceptionClass;

/*
 * * * * * * * * * * PRIVATE CONSTANT DEFINITIONS * * * * * * * * * *
 */

#define _vtextTAG_CACHE		    10

/* Editing modes - values for 'mode' field in vtext structure */

enum {
    _vtextCOPY_HIDDEN_MODE       = 0x0002,
    _vtextAUTO_INDENT_MODE       = 0x0004,
    _vtextOVERSTRIKE_MODE        = 0x0008,
    _vtextLOCKED		 = 0x0010,
    _vtextSHOW_HIDDEN		 = 0x0020
};

/* Value for 'operation' parameter to _vtextAdjustTabs() */

enum {
    _vtextADD_TAB		= 1,
    _vtextREMOVE_TAB		= 2,
    _vtextRESET_TABS		= 4
};

/* Values for 'flag' field in vtextStyle */

enum {
    _vtextSTYLE_OWNED		= 0x0001,
    _vtextSTYLE_APPLIED		= 0x0002,
    _vtextSTYLE_AUTOCALC	= 0x0004,
    _vtextSTYLE_OWNS_GRAPHIC	= 0x0008,
    _vtextSTYLE_IS_GRAPHIC	= 0x0010
};

/* Values for 'flag' field in vtextRuler */

enum {
    _vtextRULER_OWNED		= 0x0001,
    _vtextRULER_APPLIED		= 0x0002,
    _vtextRULER_AUTOCALC	= 0x0004
};

/* Values for 'flag' field in vtextGraphic */

enum {
    _vtextGRAPHIC_OWNED		= 0x0001
};

/* Values for 'flag' field in vtextObserver */

enum {
    _vtextOBSERVER_OWNED	= 0x0001,
    _vtextOBSERVER_DISABLED     = 0x0002
};

/* Values for 'justification' parameter to vtextSetRulerJustification */

enum {
    vtextLEFT_JUSTIFY		= 0,
    vtextRIGHT_JUSTIFY		= 1,
    vtextCENTER_JUSTIFY		= 2,
    vtextFULL_JUSTIFY		= 3
};

/* Values for boolean style & ruler attributes */

enum {
    vtextAUTO			= (-2),
    vtextDONT_CARE		= (-1),
    vtextOFF			= 0,
    vtextON			= 1
};

/*
 * Global Internal Strings
 */

enum {
    _vtext_Mode,
    _vtext_View,
    _vtext_Styles,
    _vtext_Rulers,
    _vtext_StyleChanges,
    _vtext_StylePosition,
    _vtext_StyleIndex,
    _vtext_RulerChanges,
    _vtext_RulerLine,
    _vtext_RulerIndex,
    _vtext_FirstLineIndent,
    _vtext_LeftIndent,
    _vtext_RightIndent,
    _vtext_Justification,
    _vtext_Ascent,
    _vtext_Descent,
    _vtext_Wrap,
    _vtext_Tabs,
    _vtext_TabStop,
    _vtext_TabType,
    _vtext_Hidden,
    _vtext_TextData,
    _vtext_DefaultStyle,
    _vtext_DefaultRuler,
    _vtext_Ruler,
    _vtext_StyleTags,
    _vtext_RulerTags,
    _vtext_Start,
    _vtext_End,
    _vtext_Size,
    _vtext_Before,
    _vtext_After,
    _vtext_Font,
    _vtext_Color,
    _vtext_BackgroundColor,
    _vtext_Bold,
    _vtext_Italic,
    _vtext_Underline,
    _vtext_Invert,
    _vtext_Strikethru,
    _vtext_SpacingBefore,	
    _vtext_SpacingAfter,
    _vtext_TabWidth,
    _vtext_Graphic,
    _vtext_Attributes,
    _vtext_Left,
    _vtext_Center,
    _vtext_Right,
    _vtext_Full,
    _vtext_Style,
    _vtext_Data,
    _vtext_UndoObserver,
    _vtext_Count
};

/*
 * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * *
 */

typedef  union _vtextAttrValue		_vtextAttrValue;
typedef struct _vtextAttrDict		_vtextAttrDict;
typedef struct _vtextAttrType		_vtextAttrType;
typedef struct _vtextAux		_vtextAux;
typedef struct _vtextLineInfo		_vtextLineInfo;
typedef struct _vtextTextBlock		_vtextTextBlock;


/*
 * vtextTag
 */

typedef struct _vtextTagPosition {
    unsigned int		pos       : 28;
    unsigned int		start     : 1;
    unsigned int		cont      : 1;
    unsigned int		fixed     : 1;
    unsigned int		permanent : 1;
    _vtextTextBlock	 	*block;
} _vtextTagPosition;

typedef struct _vtextTagContinuation {
    _vtextTagPosition	pos;
    vtextTag		*tag;
} _vtextTagContinuation;

struct vtextTag {
    _vtextTagPosition		start;
    _vtextTagPosition		end;
    const vname			*name;
    unsigned int		layer;
};

struct vtextStyleTag {
    vtextTag     tag;
    vtextStyle	 *style;
};

struct vtextRulerTag {
    vtextTag		tag;
    vtextRuler		*ruler;
};

struct vtextTagIterator {
    vtext			*editRec;
    const vname			*name;
    int				initPos;
    _vtextTagPosition           **pos;
    _vtextTextBlock		*textBlock;
};

struct vtextTagTransitionIterator {
    vtext	        	*editRec;
    _vtextTextBlock		*block;
    const vname			*name;
    long                 	 position;
    _vtextTagPosition  	       **scan;
    
    union {
        vtextTag            	*tagList[_vtextTAG_CACHE];
        vtextTag		**tagsList;
    } u;
    int                  	 tagListCount;
    int 			 tagAllocated;
};   
   

vportALIAS(vtextStyleTransitionIterator, vtextTagTransitionIterator)
vportALIAS(vtextRulerTransitionIterator, vtextTagTransitionIterator)

/*
 * _vtextTextBlock
 */

struct _vtextLineInfo {
    long		     lineStart;
    short		     ascent;
    short		     descent;
    vfixed		     origin;
    vfixed		     width;

};

struct _vtextTextBlock {
    long		     length;
    long		     lines;
    long		     offset;
    long		     linenumber;
    long		     textAlloc;
    vchar		     *text;

    long		     tagCount;
    long		     tagAlloc;
    _vtextTagPosition	     **tags;

    _vtextTextBlock	     *next;
    _vtextTextBlock	     *prev;
    vtext		     *owner;

    vbool		     lastblock;
    vbyte		     tempblock;
    long		     lineInfoSize;
    _vtextLineInfo	     *lineInfo;
};

/*
 * Attributes
 */

struct _vtextAttrType {
    const vname		*name;
    int			type;
};

struct vtextAttributeSet {
    int			count;
    int			alloced;
    _vtextAttrType	*types;
};

struct _vtextAttrDict {
    int			count;
    int			alloced;
    _vtextAttrType	**types;
    _vtextAttrValue     *values;
};

union _vtextAttrValue {
    const void                     *pointer;
    long                            scalar;
};

struct vtextAttributeSetIterator {
    vtextAttributeSet	*set;
    _vtextAttrType	*scan;
};

/*
 * vtextStyle
 *
 * Information pertain to font, styled text
 */

struct vtextStyle {
    vloadable		object;
    _vtextAttrDict	attributes;
    int			flags;
    int			index;
    vtext		*owner;
};

#define vtextStyleCLASS(SUPER, STYLE)					      \
  vloadableCLASS(SUPER, STYLE);              			   	      \
  vclassVARIABLE(vtextStyleATTRIBUTE_SET, vtextAttributeSet *);	 	      \
  vclassMETHOD(vtextStyleSET_ATTRIBUTE,   (STYLE *style, const vname *name,   \
					   const void *pointer, long scalar));\
  vclassMETHOD_RET(vtextStyleDETERMINE_FONT, vfont *, (STYLE *style));	      \
  vclassMETHOD(vtextStyleCALC,		  (STYLE *style))
 
struct vtextStyleClass {
    vtextStyleCLASS(vtextStyleClass, vtextStyle);
};

/*
 * vtextRuler - Per ruler information
 */

struct vtextTab {
    vfixed		tab;
    vbyte		type;
};

struct vtextRuler {
    vloadable		object;
    _vtextAttrDict	attributes;
    int			flags;
    int			index;
    vtext		*owner;

    vfixed		maxTab;    	/* Pixel location of last custom tab */
    short		numTabs;        /* Number of custom tabs             */
    short		tabAlloc;
    vtextTab		*tabs;
};

#define vtextRulerCLASS(SUPER, RULER)					      \
  vloadableCLASS(SUPER, RULER);              			   	      \
  vclassVARIABLE(vtextRulerATTRIBUTE_SET,  vtextAttributeSet *);	      \
  vclassMETHOD(vtextRulerSET_ATTRIBUTE,   (RULER *ruler, const vname *name,   \
					   const void *pointer, long scalar));\
  vclassMETHOD(vtextRulerCALC,		  (RULER *ruler))

struct vtextRulerClass {
    vtextRulerCLASS(vtextRulerClass, vtextRuler);
};


/*
 * vtext
 */

struct vtext {
    vobject		object;
    vbyte		mode;		/* Editing Modes		     */
    vbyte		view;		/* Global viewing style		     */

    long	 	length;		/* Allow for up to 2 giga Bytes!     */
    long	 	numLines;	/* Total number of lines	     */

    void	 	*data;		/* Generic data - client specified   */
    _vtextTextBlock	*textBlocks;	/* Linked list of text blocks	     */

    vundoActionList	*undoActions;

    vtextRuler		*defaultRuler;
    vtextStyle		*defaultStyle;
    int			tagLayer;

    short		selectionCount;
    vtextSelection	**selectionList;  /* Array of selections pointers  */

    vtextOccurrence	*savedOccurrence;

    _vtextAux		*aux;
};

struct _vtextAux {

    short		styles;
    int			stylesAlloc;
    vtextStyle		**styleList;	 /* Array of styles pointers     */

    long        	styleTags;
    vpool		*styleTagsPool;

    short               rulers;
    long		rulersAlloc;
    vtextRuler          **rulerList;     /* Array of rulers pointers     */

    long                rulerTags;
    vpool		*rulerTagsPool;

    int			returnValue;
};


#define vtextCLASS(SUPER, TEXT, SELECTION, RULER, STYLE)		      \
 vobjectCLASS(SUPER, TEXT);               			   	      \
 vclassMETHOD(vtextAPPEND_BLOCK,     (TEXT *editRec, vchar *text, 	      \
				      long length, long textAllocSize));      \
 vclassMETHOD(vtextINSERT,	     (TEXT *editRec, SELECTION *selection,    \
				      const vchar *text, long length));	      \
 vclassMETHOD(vtextINSERT_GRAPHIC,   (TEXT *editRec, SELECTION *selection,    \
				      vtextGraphicProc graphicProc, void *data));\
 vclassMETHOD(vtextINSERT_GRAPHIC_OBJECT, 				      \
	                             (TEXT *editRec, SELECTION *selection,    \
				      vtextGraphic *graphic));	 	      \
 vclassMETHOD(vtextDELETE,	     (TEXT *editRec, SELECTION *selection));  \
 vclassMETHOD(vtextKEY,	    	     (TEXT *editRec, SELECTION *selection,    \
				      int key));			      \
 vclassMETHOD(vtextPROCESS,	     (TEXT *editRec, SELECTION *selection,    \
				      vtextProcessingFunc processingFunc,     \
				      unsigned int options, 		      \
				      unsigned int tabSettings));  	      \
 vclassMETHOD(vtextSELECT_RANGE,     (TEXT *editRec, SELECTION *selection,    \
				      long start, long end));		      \
 vclassMETHOD(vtextSELECT_RANGE_RECTANGULAR,                                  \
				     (TEXT *editRec, SELECTION *selection,    \
				      long start, long end,		      \
				      int xstart, int xend));		      \
 vclassMETHOD(vtextSELECT_LINES,     (TEXT *editRec, SELECTION *selection,    \
				      long start, long end, int location));   \
 vclassMETHOD(vtextLINE_RANGE,       (TEXT *editRec, long lineNumber, 	      \
				      long *startLine, long *endLine));	      \
 vclassMETHOD(vtextCALCULATE,        (TEXT *editRec));			      \
 vclassMETHOD(vtextADD_TAG,	     (TEXT *editRec, vtextTag *tag));	      \
 vclassMETHOD(vtextREMOVE_TAG,       (TEXT *editRec, vtextTag *tag));	      \
 vclassMETHOD(vtextWARP_TAG,	     (TEXT *editRec, vtextTag *tag, long position, long delta));\
 vclassMETHOD(vtextAPPLY_STYLE,      (TEXT *editRec, STYLE *style, 	      \
				      long start, long end));                 \
 vclassMETHOD(vtextAPPLY_RULER,      (TEXT *editRec, RULER *ruler,	      \
				      long startLine, long endLine));	      \
 vclassMETHOD(vtextUNAPPLY_STYLE,    (TEXT *editRec, STYLE *style, 	      \
				      long start, long end));                 \
 vclassMETHOD(vtextUNAPPLY_RULER,    (TEXT *editRec, RULER *ruler,	      \
				      long startLine, long endLine));	      \
 vclassMETHOD(vtextCALC_RULER,       (TEXT *editRec, RULER *ruler)); 	      \
 vclassMETHOD(vtextCALC_STYLE,       (TEXT *editRec, STYLE *style));  	      \
 vclassMETHOD(vtextHIDE, 	     (TEXT *editRec, SELECTION *selection));  \
 vclassMETHOD(vtextSHOW, 	     (TEXT *editRec, SELECTION *selection));  \
 vclassMETHOD(vtextOBSERVE_INSERT,     (TEXT *editRec, long pos, long delta));\
 vclassMETHOD(vtextOBSERVE_DELETE,     (TEXT *editRec, long pos, long delta));\
 vclassMETHOD(vtextOBSERVE_PRE_INSERT, (TEXT *editRec, long pos, long delta));\
 vclassMETHOD(vtextOBSERVE_PRE_DELETE, (TEXT *editRec, long pos, long delta));\
 vclassMETHOD(vtextOBSERVE_RULER_CHANGE, (TEXT *editRec, RULER *ruler,        \
					  long startLine, long endLine));     \
 vclassMETHOD(vtextOBSERVE_STYLE_CHANGE, (TEXT *editRec, STYLE *style,	      \
					  long start, long end));	      \
 vclassMETHOD(vtextOBSERVE_SELECT_METHOD,(TEXT *editRec, SELECTION *selection,\
					  int selectMethod));		      \
 vclassMETHOD(vtextOBSERVE_CALCULATE,    (TEXT *editRec));  		      \
 vclassMETHOD(vtextOBSERVE_SELECT,       (TEXT *editRec, SELECTION *selection,\
					  int state)); 		 	      \
 vclassMETHOD(vtextOBSERVE_DESTROY,       (TEXT *editRec));    		      \
 vclassMETHOD_RET(vtextDETERMINE_STYLE_FONT, vfont *, 			      \
		     (TEXT *editRec, STYLE *style));			      \
 vclassMETHOD_RET(vtextIS_IN_WORD,  vbool,				      \
		     (TEXT *editRec, long position, vchar c));		      \
 vclassMETHOD_RET(vtextCAN_WRAP_AFTER,  vbool,				      \
		     (TEXT *editRec, long position, vchar c));		      \
 vclassMETHOD_RET(vtextWORD_BREAK,  vbool,				      \
		     (TEXT *editRec, vchar *text, long len));  		      \
 vclassMETHOD_RET(vtextWRAP_BREAK,  vbool,				      \
		     (TEXT *editRec, vchar *text, long len));  		      \
 vclassMETHOD_RET(vtextUSER_AREA,  vbool,				      \
		     (TEXT *editRec, vchar *text, long len));  		      \
 vclassMETHOD_RET(vtextCALC_WIDTHS, vtextWidthInfo *,		              \
		     (TEXT *editRec, SELECTION *selection, vchar *text,       \
		      long *length, long position, long linenumber)) 

struct vtextClass {
    vtextCLASS(vtextClass, vtext, vtextSelection, vtextRuler,
	      vtextStyle);
};


/*
 * vtextGraphic
 */

struct vtextGraphic {
    vloadable		object;
    int			(*proc)(vtext *editRec, void *, vevent *,
				int operation);
    void                *data;
    int			w;
    int			h;
    short		descent;
    unsigned short	flags;
    vtextStyle		*style;
    vtext		*owner;
};

#define vtextGraphicCLASS(SUPER, GRAPHIC)				      \
    vloadableCLASS(SUPER, GRAPHIC);              			   	      \
    vclassMETHOD(vtextGraphicDRAW,      (GRAPHIC * graphic));                 \
    vclassMETHOD(vtextGraphicDRAW_WITH,                                       \
		 (GRAPHIC * graphic, vdrawcontext *context))

struct vtextGraphicClass {
    vtextGraphicCLASS(vtextGraphicClass, vtextGraphic);
};


/*
 * vtextOccurrence
 */

struct vtextOccurrence {
    voccurrence		 super;

    int			 type;
    vtextSelection      *selection;
    vtextRuler		*ruler;
    vtextStyle		*style;
    int			 state;
    long		 position;
    long		 delta;
    long		 start;
    long		 end;
    long		 startLine;
    long		 endLine;
};

#define vtextOCCURRENCE_CLASS(CLASS, OCCURRENCE)			     \
    voccurrenceCLASS(CLASS, OCCURRENCE)

struct vtextOccurrenceClass
{
  vtextOCCURRENCE_CLASS(vtextOccurrenceClass, vtextOccurrence);
};


/*
 * vtextObserver
 */

struct vtextObserver {
    vobserver	 super;

    vtext	*owner;
};

#define vtextObserverCLASS(SUPER, OBSERVER, RULER, STYLE, SELECTION)	      \
 vobserverCLASS(SUPER, OBSERVER);    			   		      \
 vclassMETHOD(vtextObserverINSERT,	 (OBSERVER *observer, 		      \
					  long pos, long delta));	      \
 vclassMETHOD(vtextObserverDELETE,	 (OBSERVER *observer, 		      \
					  long pos, long delta));	      \
 vclassMETHOD(vtextObserverPRE_INSERT,   (OBSERVER *observer, 		      \
					  long pos, long delta)); 	      \
 vclassMETHOD(vtextObserverPRE_DELETE,   (OBSERVER *observer,		      \
					  long pos, long delta));	      \
 vclassMETHOD(vtextObserverRULER_CHANGE, (OBSERVER *observer, RULER *ruler,   \
					  long startLine, long endLine));     \
 vclassMETHOD(vtextObserverSTYLE_CHANGE, (OBSERVER *observer, STYLE *style,   \
					  long start, long end)); 	      \
 vclassMETHOD(vtextObserverSELECT_METHOD,(OBSERVER *observer, SELECTION       \
					  *selection, int selectMethod));     \
 vclassMETHOD(vtextObserverCALCULATE,    (OBSERVER *observer));		      \
 vclassMETHOD(vtextObserverSELECT,       (OBSERVER *observer, 		      \
					  SELECTION *selection, int state));  \
 vclassMETHOD(vtextObserverDESTROY,	 (OBSERVER *observer))

struct vtextObserverClass {
    vtextObserverCLASS(vtextObserverClass, vtextObserver, vtextRuler,
		       vtextStyle, vtextSelection);
};


vportALIAS(vtextUndoObserver, vtextObserver)

vportALIAS(vtextObserverIterator, vobservableObserverIterator)


/*
 * * * * * * * * * * PRIVATE FUNCTION PROTOTYPES * * * * * * * * * *
 */

void 	 _vtextInitTagTransitionIterator(vtextTagTransitionIterator *iterator,
					 vtext *editRec, const vname *name,
					 long position, int inBlock);
vfixed	 _vtextAdjustTabs(vtext *editRec, vtextRuler *ruler, vfixed positiong,
			 int operation, int tabType);

vbool	_vtextDetermineWrapBreak(vtext *editRec, vchar *text, long length);
vbool	_vtextDetermineWordBreak(vtext *editRec, vchar *text, long length);

void	 _vtextSetStyleBoolean(vtextStyle *style, const vname *name,
			       int state);
int 	 _vtextGetStyleBoolean(vtextStyle *style, const vname *name);
void 	 _vtextSetStyleScalar(vtextStyle *style, const vname *name,
			      long scalar);
void 	 _vtextSetStylePointer(vtextStyle *style, const vname *name,
			       void *pointer);
long 	 _vtextGetStyleScalar(vtextStyle *style, const vname *name);
void	 _vtextSetRulerBoolean(vtextRuler *ruler, const vname *name,
			       int state);
int 	 _vtextGetRulerBoolean(vtextRuler *ruler, const vname *name);
void	 _vtextSetRulerJust(vtextRuler *ruler, const vname *name, int just);
int 	 _vtextGetRulerJust(vtextRuler *ruler, const vname *name);
void 	 _vtextSetRulerScalar(vtextRuler *ruler, const vname *name,
			      long scalar);
void 	 _vtextSetRulerPointer(vtextRuler *ruler, const vname *name,
			       void *pointer);
long 	 _vtextGetRulerScalar(vtextRuler *ruler, const vname *name);
void	 _vtextSetAttribute(vtextAttributeSet *attrSet,
			    _vtextAttrDict *attributes, const vname *name,
			    const void *pointer, long scalar);
const void *_vtextGetAttribute(_vtextAttrDict *attributes, const vname *n);
long 	 _vtextGetAttributeScalar(_vtextAttrDict *attr, const vname *n);
void     _vtextRemoveAttribute(_vtextAttrDict *attr, const vname *n);

void	 _vtextDumpBlocks(vtext *editRec, FILE *stream);
void	 _vtextDumpStyles(vtext *editRec, FILE *stream);
void	 _vtextDumpRulers(vtext *editRec, FILE *stream);

void	 _vtextSetStyleAttributeRaw(vtextStyle *style, const vname *name,
				    const void *pointer, long scalar);
void	 _vtextSetRulerAttributeRaw(vtextRuler *ruler, const vname *name,
				    const void *pointer, long scalar);

void	 _vtextCopySelection(vtext *editRec, vtextSelection *selection,
			 vtextSelection *target);
long	 _vtextSelectedLines(vtext *editRec, vtextSelection *selection);
long	 _vtextGetSelectedLine(vtext *editRec, vtextSelection *selection);
long	 _vtextCurrLineNum(vtext *editRec, vtextSelection *selection);
long	 _vtextSelectionStart(vtext *editRec, vtextSelection *selection);
long	 _vtextSelectionEnd(vtext *editRec, vtextSelection *selection);
long	 _vtextSelectionCaret(vtext *editRec, vtextSelection *selection);
long	 _vtextSelectionLength(vtext *editRec, vtextSelection *selection);
long	 _vtextStartPos(vtext *editRec, vtextSelection *selection);
long	 _vtextEndPos(vtext *editRec, vtextSelection *selection);
int	 _vtextStartPixel(vtext *editRec, vtextSelection *selection);
int	 _vtextEndPixel(vtext *editRec, vtextSelection *selection);
vtextPosition *_vtextGetPosition(vtext *editRec, vtextSelection *selection);
long     _vtextGetLastUndoPosition(void);
void     _vtextSetLastUndoPosition(long pos);

double   _vtextFixedAttributeToFloat(vfixed value);
vfixed   _vtextFixedAttributeFromFloat(double value);

#if vdebugDEBUG
vscribe *_vtextScribeTextDebug(vtext *editRec, vtextSelection *selection,
			       const char *tag, const char *file, int line);
#else
vscribe *_vtextScribeTextNondebug(vtext *editRec, vtextSelection *selection);
#endif

/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * *
 */

#define vtextGetObject(e)	(vportBASE_OBJECT((e), object))
#define vtextGetObservable(e) \
    vobjectGetObservable(vtextGetObject(e))
#define vtextGetLoadable(e) \
    vobservableGetLoadable(vtextGetObservable(e))
#define vtextGetInstance(e) \
    vloadableGetInstance(vtextGetLoadable(e))
#define vtextGetClass(e)        \
    ((vtextClass*)vobservableGetClass(vtextGetObservable(e)))

#define vtextCreateOfClass(c)   \
    ((vtext *) vobservableCreateOfClass((vobservableClass *)(c)))
#define vtextCreate()		vtextCreateOfClass(vtextGetDefaultClass())

#define vtextInitOfClass(i, c)  \
    vobservableInitOfClass(vtextGetObservable(i), (vobservableClass*)(c))
#define vtextInit(i)		vtextInitOfClass(i, vtextGetDefaultClass())
#define vtextCopyInit(e,t)      \
    vobservableCopyInit(vtextGetObservable(e), vtextGetObservable(t))
#define vtextCopy(e,t)          \
    vobservableCopy(vtextGetObservable(e), vtextGetObservable(t))
#define vtextStore(e,r)        \
    vobservableStore(vtextGetObservable(e), r)
#define vtextLoad(r)            ((vtext*)vobservableLoad(r))
#define vtextLoadInit(e,r)      vobservableLoadInit(vtextGetObservable(e), r)
#define vtextDestroy(e)		 vobservableDestroy(vtextGetObservable(e))

#define vtextSetData(e,d)		((e)->data = (d))
#define vtextGetClass(e)		\
    ((vtextClass*)vobservableGetClass(vtextGetObservable(e)))
#define vtextGetData(e)			((e)->data)
#define vtextGetView(e)			((e)->view)

#define vtextIsWrapBreak(e,s,l)	 (!_vtextDetermineWrapBreak(e,s,l))
#define vtextIsWordBreak(e,s,l)	 (!_vtextDetermineWordBreak(e,s,l))

#define vtextGetDefaultStyle(e)		((e)->defaultStyle)
#define vtextGetDefaultRuler(e)		((e)->defaultRuler)

#define vtextStyleCount(e)		((e)->aux ? (e)->aux->styles : 0)
#define vtextGetStyleAt(e,i)		((e)->aux->styleList[i])

#define vtextSetStyleAutoCalc(e,s,a)	(a ? 			\
		((s)->flags |=  _vtextSTYLE_AUTOCALC) :  	\
		((s)->flags &= ~_vtextSTYLE_AUTOCALC)) 
#define vtextGetStyleAutoCalc(e,s)	\
                  (((s)->flags & _vtextSTYLE_AUTOCALC) != 0)
#define vtextInstallStyleOwned(e,s)	  ((s)->flags |= _vtextSTYLE_OWNED, \
					   vtextInstallStyle(e,s))
#define vtextInstallRulerOwned(e,s)	  ((s)->flags |= _vtextRULER_OWNED, \
					   vtextInstallRuler(e,s))
#define vtextSetDefaultStyleOwned(e,s)	  ((s)->flags |= _vtextSTYLE_OWNED, \
					   vtextSetDefaultStyle(e,s))
#define vtextSetDefaultRulerOwned(e,s)	  ((s)->flags |= _vtextRULER_OWNED, \
					   vtextSetDefaultRuler(e,s))

#define vtextRulerCount(e)		((e)->aux ? (e)->aux->rulers : 0)
#define vtextGetRulerAt(e,i)		((e)->aux->rulerList[i])

#define vtextRulerAddTab(e,r,p, t)  _vtextAdjustTabs(e,r,p,_vtextADD_TAB, (t))
#define vtextRulerRemoveTab(e,r,p)  _vtextAdjustTabs(e,r,p,_vtextREMOVE_TAB, 0)
#define vtextRulerResetTabs(e,r)    _vtextAdjustTabs(e,r,0,_vtextRESET_TABS, 0)
#define vtextRulerMaxTab(e,r)	     ((r)->maxTab)
#define vtextRulerTabCount(e,r)	     ((r)->numTabs)
#define vtextRulerTabs(e,r)	     ((r)->tabs)

#define vtextSetRulerAutoCalc(e,s,a)	(a ? 			\
		((s)->flags |=  _vtextRULER_AUTOCALC) :  	\
		((s)->flags &= ~_vtextRULER_AUTOCALC)) 
#define vtextGetRulerAutoCalc(e,r)	\
                  (((r)->flags & _vtextRULER_AUTOCALC) != 0)

#define vtextSetOverstrike(e,o)	(o ? 				\
		((e)->mode |=  _vtextOVERSTRIKE_MODE) :  	\
		((e)->mode &= ~_vtextOVERSTRIKE_MODE)) 
#define vtextSetAutoIndent(e,a)	(a ? 				\
		((e)->mode |=  _vtextAUTO_INDENT_MODE) :  	\
		((e)->mode &= ~_vtextAUTO_INDENT_MODE))  

#define vtextLock(e)		((e)->mode |= _vtextLOCKED)

#define vtextGetShowHidden(e)        \
                  (((e)->mode & _vtextSHOW_HIDDEN) != 0)
#define vtextIsOverstrike(e)        \
                  (((e)->mode & _vtextOVERSTRIKE_MODE) != 0)
#define vtextIsAutoIndent(e)        \
                  (((e)->mode & _vtextAUTO_INDENT_MODE) != 0)
#define vtextIsLocked(e)            \
                  (((e)->mode & _vtextLOCKED) != 0)

#define vtextSetUndoActionList(e,l)	((e)->undoActions = (l))
#define vtextGetUndoActionList(e)	((e)->undoActions)

#define vtextLength(e)		((e)->length)
#define vtextLines(e)		((e)->numLines)

#define vtextTabsToSpaces(e,s,t) vtextProcess(e,s,NULL,vtextEXPAND_TABS,t)
#define vtextSpacesToTabs(e,s,t) \
  vtextProcess(e,s,NULL,vtextENTAB | vtextCOPY_TO_BUFFER,t)

#define vtextSimpleSearch(e,p,t)	\
    vtextSearch(e, p, t, NULL, 0, vtextFORWARD_SEARCH, NULL, FALSE)
#define vtextFunctionSearch(e,p,f)	\
    vtextSearch(e, p, NULL, NULL, 0, vtextFORWARD_SEARCH, f, FALSE)


/*
 * Text observers
 */

#define vtextGetObserverObserver(o)	vportBASE_OBJECT(o, super)
#define vtextGetObserverObservable(o) \
    vobserverGetObservable(vtextGetObserverObserver(o))
#define vtextGetObserverLoadable(o) \
    vobservableGetLoadable(vtextGetObserverObservable(o))
#define vtextGetObserverInstance(o) \
    vloadableGetInstance(vtextGetObserverLoadable(o))
#define vtextGetObserverClass(o) \
    ((vtextObserverClass*)vloadableGetClass(vtextGetObserverLoadable(o)))

#define vtextCreateObserverOfClass(c)   	\
    ((vtextObserver *) vloadableCreateOfClass((vloadableClass *)(c)))
#define vtextCreateObserver()		\
    (vtextCreateObserverOfClass(vtextGetDefaultObserverClass()))
#define vtextInitObserverOfClass(g, c)  	\
    vloadableInitOfClass(vtextGetObserverLoadable(g), (vloadableClass*)(c))
#define vtextInitObserver(g)	     	\
    vtextInitObserverOfClass(g, vtextGetDefaultObserverClass())
#define vtextDestroyObserver(g)	\
    vloadableDestroy(vtextGetObserverLoadable(g))

#define vtextCloneObserver(g)	\
    ((vtextObserver *) vloadableClone(vtextGetObserverLoadable(g)))
#define vtextCopyObserver(g,t)	\
    vloadableCopy(vtextGetObserverLoadable(g), vtextGetObserverLoadable(t))
#define vtextCopyInitObserver(g,t)      	\
    vloadableCopyInit(vtextGetObserverLoadable(g), vtextGetObserverLoadable(t))

#define vtextSetObserverData(o,d) \
    vobserverSetData(vtextGetObserverObserver(o), d)
#define vtextGetObserverData(o) \
    vobserverGetData(vtextGetObserverObserver(o))

#define vtextSetObserverOwner(o,l) \
    ((o)->owner = (l))
#define vtextGetObserverOwner(o) \
    ((o)->owner)

#define vtextDisableObserver(o) \
    vobserverDisable(vtextGetObserverObserver(o))
#define vtextEnableObserver(o) \
    vobserverEnable(vtextGetObserverObserver(o))
#define vtextObserverIsEnabled(o)  \
    vobserverIsEnabled(vtextGetObserverObserver(o))


#define vtextInstallObserver(e,o) \
    vobservableInstallObserver(vtextGetObservable(e), \
			       vtextGetObserverObservable(o))
#define vtextInstallObserverOwned(e,o) \
    vobservableInstallObserverOwned(vtextGetObservable(e), \
				    vtextGetObserverObservable(o))
#define vtextUninstallObserver(e,o) \
    vobservableUninstallObserver(vtextGetObservable(e), \
				    vtextGetObserverObservable(o))


#define vtextNextObserverIterator(i) \
    vobservableNextObserverIterator(i)
#define vtextDestroyObserverIterator(i) \
    vobservableDestroyObserverIterator(i)
#define vtextGetObserverIteratorObserver(i) \
    ((vtextObserver *) vobservableGetObserverIteratorObserver( \
					(vobservableObserverIterator *) i))



/*
 * Text occurrences
 */

#define vtextGetOccurrenceOccurrence(o)	vportBASE_OBJECT(o, super)
#define vtextGetOccurrenceInstance(o) \
    voccurrenceGetInstance(vtextGetOccurrenceOccurrence(o))
#define vtextGetOccurrenceClass(o) \
    ((vtextOccurrenceClass *) \
     voccurrenceGetClass(vtextGetOccurrenceOccurrence(o)))

#define vtextCreateOccurrenceOfClass(c)   	\
    ((vtextOccurrence *) voccurrenceCreateOfClass((voccurrenceClass *)(c)))
#define vtextCreateOccurrence()		\
    (vtextCreateOccurrenceOfClass(vtextGetDefaultOccurrenceClass()))
#define vtextInitOccurrenceOfClass(o, c)  	\
    voccurrenceInitOfClass(vtextGetOccurrenceOccurrence(o), \
			   (voccurrenceClass*)(c))
#define vtextInitOccurrence(o)	     	\
    vtextInitOccurrenceOfClass(o, vtextGetDefaultOccurrenceClass())
#define vtextDestroyOccurrence(o)	\
    voccurrenceDestroy(vtextGetOccurrenceOccurrence(o))

#define vtextGetOccurrenceText(o) \
    ((vtext *) voccurrenceGetAnnouncer(vtextGetOccurrenceOccurrence(o)))
#define vtextGetOccurrenceType(o) \
    ((o)->type)
#define vtextGetOccurrenceSelection(o) \
    ((o)->selection)
#define vtextGetOccurrenceRuler(o) \
    ((o)->ruler)
#define vtextGetOccurrenceStyle(o) \
    ((o)->style)
#define vtextGetOccurrenceState(o) \
    ((o)->state)
#define vtextGetOccurrencePosition(o) \
    ((o)->position)
#define vtextGetOccurrenceDelta(o) \
    ((o)->delta)
#define vtextGetOccurrenceStart(o) \
    ((o)->start)
#define vtextGetOccurrenceEnd(o) \
    ((o)->end)
#define vtextGetOccurrenceStartLine(o) \
    ((o)->startLine)
#define vtextGetOccurrenceEndLine(o) \
    ((o)->endLine)

#define vtextSetOccurrenceText(o, l) \
    voccurrenceSetAnnouncer(vtextGetOccurrenceOccurrence(o), \
			    vtextGetInstance(l))
#define vtextSetOccurrenceType(o, t) \
    ((o)->type = (t))
#define vtextSetOccurrenceSelection(o, s) \
    ((o)->selection = (s))
#define vtextSetOccurrenceRuler(o, r) \
    ((o)->ruler = (r))
#define vtextSetOccurrenceStyle(o, s) \
    ((o)->style = (s))
#define vtextSetOccurrenceState(o, s) \
    ((o)->state = (s))
#define vtextSetOccurrencePosition(o, p) \
    ((o)->position = (p))
#define vtextSetOccurrenceDelta(o, d) \
    ((o)->delta = (d))
#define vtextSetOccurrenceStart(o, s) \
    ((o)->start = (s))
#define vtextSetOccurrenceEnd(o, e) \
    ((o)->end = (e))
#define vtextSetOccurrenceStartLine(o, s) \
    ((o)->startLine = (s))
#define vtextSetOccurrenceEndLine(o, e) \
    ((o)->endLine = (e))

/*
 * Text graphics
 */

#define vtextGetGraphicLoadable(g)	(vportBASE_OBJECT((g), object))
#define vtextGetGraphicClass(g)		\
    ((vtextGraphicClass*)vloadableGetClass(vtextGetGraphicLoadable(g)))

#define vtextCreateGraphicOfClass(c)   	\
    ((vtextGraphic *) vloadableCreateOfClass((vloadableClass *)(c)))
#define vtextCreateGraphic()		\
    vtextCreateGraphicOfClass(vtextGetDefaultGraphicClass())
#define vtextInitGraphicOfClass(g, c)  	\
    vloadableInitOfClass(vtextGetGraphicLoadable(g), (vloadableClass*)(c))
#define vtextInitGraphic(g)	     	\
    vtextInitGraphicOfClass(g, vtextGetDefaultGraphicClass())
#define vtextCopyInitGraphic(g,t)      	\
    vloadableCopyInit(vtextGetGraphicLoadable(g), vtextGetGraphicLoadable(t))
#define vtextCopyGraphic(g,t)           \
    vloadableCopy(vtextGetGraphicLoadable(g), vtextGetGraphicLoadable(t))
#define vtextStoreGraphic(g,r)          \
    vloadableStore(vtextGetGraphicLoadable(g), r)
#define vtextLoadGraphic(r)            ((vtextGraphic*)vloadableLoad(r))
#define vtextLoadInitGraphic(g,r)	\
    vloadableLoadInit(vtextGetGraphicLoadable(g), r)
#define vtextDestroyGraphic(g)	 	\
    vloadableDestroy(vtextGetGraphicLoadable(g))

#define vtextSetGraphicData(g,d)	((g)->data = d)
#define vtextSetGraphicWidth(g,w)	vtextSetGraphicMetrics(g,w,-1,-1)
#define vtextSetGraphicHeight(g,h)	vtextSetGraphicMetrics(g,-1,h,-1)
#define vtextSetGraphicDescent(g,d)	vtextSetGraphicMetrics(g,-1,-1,d)
#define vtextGetGraphicData(g)		((g)->data)
#define vtextGetGraphicWidth(g)		((g)->w)
#define vtextGetGraphicHeight(g)	((g)->h)
#define vtextGetGraphicDescent(g)	((g)->descent)
#define vtextGetGraphicOwner(g)		((g)->owner)

/*
 * Text styles
 */

#define vtextGetStyleLoadable(s)		(vportBASE_OBJECT((s), object))
#define vtextGetStyleClass(g)		\
    ((vtextStyleClass*)vloadableGetClass(vtextGetStyleLoadable(g)))

#define vtextCreateStyleOfClass(c)   	\
    ((vtextStyle *) vloadableCreateOfClass((vloadableClass *)(c)))
#define vtextCreateStyle()		\
    vtextCreateStyleOfClass(vtextGetDefaultStyleClass())
#define vtextInitStyleOfClass(g, c)  	\
    vloadableInitOfClass(vtextGetStyleLoadable(g), (vloadableClass*)(c))
#define vtextInitStyle(g)	     	\
    vtextInitStyleOfClass(g, vtextGetDefaultStyleClass())
#define vtextCopyInitStyle(g,t)      	\
    vloadableCopyInit(vtextGetStyleLoadable(g), vtextGetStyleLoadable(t))
#define vtextCopyStyle(g,t)             \
    vloadableCopy(vtextGetStyleLoadable(g), vtextGetStyleLoadable(t))
#define vtextStoreStyle(g,r)            \
    vloadableStore(vtextGetStyleLoadable(g), r)
#define vtextDestroyStyle(g)	 	\
    vloadableDestroy(vtextGetStyleLoadable(g))

#define vtextSetGlobalDefaultStyleOwned(s)	\
    ((s)->flags |= _vtextSTYLE_OWNED, vtextSetGlobalDefaultStyle(s))

#define vtextGetStyleOwner(g)		((g)->owner)

/*
 * Text rulers
 */

#define vtextGetRulerLoadable(r)		(vportBASE_OBJECT((r), object))
#define vtextGetRulerClass(g)		\
    ((vtextRulerClass*)vloadableGetClass(vtextGetRulerLoadable(g)))

#define vtextCreateRulerOfClass(c)   	\
    ((vtextRuler *) vloadableCreateOfClass((vloadableClass *)(c)))
#define vtextCreateRuler()		\
    vtextCreateRulerOfClass(vtextGetDefaultRulerClass())
#define vtextInitRulerOfClass(g, c)  	\
    vloadableInitOfClass(vtextGetRulerLoadable(g), (vloadableClass*)(c))
#define vtextInitRuler(g)	     	\
    vtextInitRulerOfClass(g, vtextGetDefaultRulerClass())
#define vtextCopyInitRuler(g,t)      	\
    vloadableCopyInit(vtextGetRulerLoadable(g), vtextGetRulerLoadable(t))
#define vtextCopyRuler(g,t)             \
    vloadableCopy(vtextGetRulerLoadable(g), vtextGetRulerLoadable(t))
#define vtextStoreRuler(g,r)            \
    vloadableStore(vtextGetRulerLoadable(g), r)
#define vtextDestroyRuler(g)	 	\
    vloadableDestroy(vtextGetRulerLoadable(g))

#define vtextSetGlobalDefaultRulerOwned(s)	\
    ((s)->flags |= _vtextRULER_OWNED, vtextSetGlobalDefaultRuler(s))

#define vtextGetRulerOwner(g)		((g)->owner)

/*
 * Text tags
 */

#define _vtextGetStyleTagTag(s)		(vportBASE_OBJECT((s), tag))
#define _vtextGetRulerTagTag(r)		(vportBASE_OBJECT((r), tag))

#define vtextGetTagTransitionIteratorTags(i)	\
    ((((i)->tagAllocated) > 0) ? (i)->u.tagsList : (i)->u.tagList)
#define vtextGetTagTransitionIteratorCount(i)	((i)->tagListCount)
#define vtextGetTagTransitionIteratorPosition(i) \
    ((i)->block->offset + (i)->position)

#define vtextSetTagName(t,n)		((t)->name = (n))
#define vtextGetTagName(t)		((t)->name)
#define vtextSelectTag(e,s,t)		\
      vtextSelectRange(e, s, vtextGetTagStart(t), vtextGetTagEnd(t))
#define vtextInitTagIterator(i,e,p)	vtextInitNamedTagIterator(i,e,NULL,p)
#define vtextDestroyTagIterator(i)

#define vtextSetTagPermanent(t,p)	\
    ((t)->start.permanent = (p?1:0),(t)->end.permanent = (p?1:0))
#define vtextSetTagFixed(t,p)	\
    ((t)->start.fixed = (p?1:0),(t)->end.fixed = (p?1:0))
#define vtextIsTagPermanent(t)		((t)->start.permanent)
#define vtextIsTagFixed(t)		((t)->start.fixed)

/*
 * Text transition iterators
 */

#define vtextInitStyleTransitionIterator(i,e,p) 		\
    vtextInitTagTransitionIterator(				\
      (vtextTagTransitionIterator *)(i), e, vtext_Style, p)
#define vtextNextStyleTransitionIterator(i) 			\
    vtextNextTagTransitionIterator((vtextTagTransitionIterator *)(i))
#define vtextDestroyStyleTransitionIterator(i) 			\
    vtextDestroyTagTransitionIterator((vtextTagTransitionIterator *)(i))
#define vtextGetStyleTransitionIteratorStyles(i) 		\
    ((vtextStyleTag **) \
	vtextGetTagTransitionIteratorTags((vtextTagTransitionIterator *)(i)))
#define vtextGetStyleTransitionIteratorCount(i) 		\
    vtextGetTagTransitionIteratorCount((vtextTagTransitionIterator *)(i))
#define vtextGetStyleTransitionIteratorPosition(i) 		\
    vtextGetTagTransitionIteratorPosition((vtextTagTransitionIterator *)(i))

#define vtextNextRulerTransitionIterator(i) 			\
    vtextNextTagTransitionIterator((vtextTagTransitionIterator *)(i))
#define vtextDestroyRulerTransitionIterator(i) 			\
    vtextDestroyTagTransitionIterator((vtextTagTransitionIterator *)(i))
#define vtextGetRulerTransitionIteratorRulers(i) 		\
    ((vtextRulerTag **) \
	vtextGetTagTransitionIteratorTags((vtextTagTransitionIterator *)(i)))
#define vtextGetRulerTransitionIteratorCount(i) 		\
    vtextGetTagTransitionIteratorCount((vtextTagTransitionIterator *)(i))
#define vtextGetRulerTransitionIteratorLine(i) 			\
    vtextLineFromPosition((i)->editRec, 			\
     vtextGetTagTransitionIteratorPosition((vtextTagTransitionIterator *)(i)))

/*
 * Text attribute set iterators
 */

#define vtextGetAttributeSetIteratorName(i)	((i)->scan->name)
#define vtextGetAttributeSetIteratorType(i)	((i)->scan->type)
#define vtextDestroyAttributeSetIterator(i)

/*
 * Text exceptions
 */

#define vtextGetNoAppliedStyleExceptionClass() \
    (&_vtextNoAppliedStyleExceptionClass)
#define vtextGetNoAppliedRulerExceptionClass() \
    (&_vtextNoAppliedRulerExceptionClass)
#define vtextGetNoAppliedStyleException() \
    ((vtextNoAppliedStyleException*) \
         vexGetExceptionOfClass(&_vtextNoAppliedStyleExceptionClass))
#define vtextGetNoAppliedRulerException() \
    ((vtextNoAppliedRulerException*) \
         vexGetExceptionOfClass(&_vtextNoAppliedRulerExceptionClass))

/*
 * Text selections
 */

#define vtextCopySelection(s, t) \
   (vtextselectionCopy(s, t))
#define vtextCopyInitSelection(e, s, t) \
   (vtextselectionCopyInit(s, t), vtextselectionSetText(t, e))
#define vtextInitSelection(e, s) \
   (vtextselectionInit(s), vtextselectionSetText(s, e))
#define vtextDestroySelection(e, s) \
   (vtextselectionSetText((s), NULL), vtextselectionDestroy(s))
#define vtextSetSelectMethod(e, s, m) \
   (vtextselectionSetSelectMethod(s, m))
#define vtextGetSelectMethod(e, s) \
   (vtextselectionGetSelectMethod(s))

#define _vtextCopySelection(e,s,t) \
    (vtextselectionSetText(t, e), vtextselectionCopy(s, t))
#define _vtextSelectedLines(e, s) \
    (vtextselectionSetText(s, e), vtextselectionGetLineCount(s))
#define _vtextCurrLineNum(e, s) \
    (vtextselectionSetText(s, e), vtextselectionGetStartLine(s))
#define _vtextGetSelectedLine(e, s) \
    (vtextselectionSetText(s, e), vtextselectionGetStartLine(s))
#define _vtextSelectionStart(e, s) \
    (vtextselectionSetText(s, e), vtextselectionGetStart(s))
#define _vtextSelectionEnd(e, s) \
    (vtextselectionSetText(s, e), vtextselectionGetEnd(s))
#define _vtextSelectionCaret(e, s) \
    (vtextselectionSetText(s, e), vtextselectionGetCaret(s))
#define _vtextSelectionLength(e, s) \
    (vtextselectionSetText(s, e), vtextselectionGetLength(s))
#define _vtextStartPos(e, s) \
    (vtextselectionSetText(s, e), \
     vtextselectionGetStart(s) \
     - vtextselectionGetLineStart(s, vtextselectionGetStartLine(s)))
#define _vtextEndPos(e, s) \
    (vtextselectionSetText(s, e), \
     vtextselectionGetEnd(s) \
     - vtextselectionGetLineStart(s, vtextselectionGetEndLine(s)))
#define _vtextStartPixel(e, s) \
    (vtextselectionSetText(s, e), vtextselectionGetLeftPoint(s))
#define _vtextEndPixel(e, s) \
    (vtextselectionSetText(s, e), vtextselectionGetRightPoint(s))
#define _vtextGetPosition(e, s) \
    (vtextselectionSetText(s, e), _vtextselectionGetPositionInfo(s))

#define vtextSelectedLines(s) \
    (vtextselectionGetLineCount(s))
#define vtextCurrLineNum(s) \
    (vtextselectionGetStartLine(s))
#define vtextSelectionStart(s) \
    (vtextselectionGetStart(s))
#define vtextSelectionEnd(s) \
    (vtextselectionGetEnd(s))
#define vtextSelectionCaret(s) \
    (vtextselectionGetCaret(s))
#define vtextSelectionLength(s) \
    (vtextselectionGetLength(s))
#define vtextStartPos(s) \
    (vtextselectionGetStart(s) \
     - vtextselectionGetLineStart(s, vtextselectionGetStartLine(s)))
#define vtextEndPos(s) \
    (vtextselectionGetEnd(s) \
     - vtextselectionGetLineStart(s, vtextselectionGetEndLine(s)))
#define vtextStartPixel(s) \
    (vtextselectionGetLeftPoint(s))
#define vtextEndPixel(s) \
    (vtextselectionGetRightPoint(s))
#define vtextGetPosition(s) \
    (_vtextselectionGetPositionInfo(s))

/*
 * * * * * * * PRIVATE BACKWARD COMPATIBILITY MACRO DEFINITIONS * * * * * *
 */

#define vtextSetRuler(e,s,r)		vtextApplyRuler(e,s,r)
#define vtextSetStyle(e,s,r)		vtextApplyStyle(e,s,r)
#define vtextWrappedLines(e)		vtextLines(e)
#define vtextSelectedWrappedLines(s)	vtextSelectedLines(s)
#define vtextCreateGlobalStyle()	vtextCreateStyle()
#define vtextCreateGlobalRuler()	vtextCreateRuler()

#define vtextSetStyleFont(e,s,f,c)     _vtextSetStylePointer(s, vtext_Font, f)
#define vtextSetStyleData(e,s,d)       _vtextSetStylePointer(s, vtext_Data, d)
#define vtextSetStyleColor(e,s,c)      _vtextSetStylePointer(s, vtext_Color, c)
#define vtextSetStyleBackgroundColor(e,s,c) _vtextSetStylePointer(s, vtext_BackgroundColor, c)
#define vtextSetStyleDescent(e,s,d)    _vtextSetStyleScalar(s, vtext_Descent, d)
#define vtextSetStyleAscent(e,s,d)     _vtextSetStyleScalar(s, vtext_Ascent, d)
#define vtextSetStyleSize(e,s,d)       _vtextSetStyleScalar(s, vtext_Size, d)
#define vtextSetStyleBold(e,s,d)       _vtextSetStyleBoolean(s, vtext_Bold, d)
#define vtextSetStyleUnderline(e,s,d)  _vtextSetStyleBoolean(s, vtext_Underline, d)
#define vtextSetStyleInvert(e,s,d)     _vtextSetStyleBoolean(s, vtext_Invert, d)
#define vtextSetStyleItalic(e,s,d)     _vtextSetStyleBoolean(s, vtext_Italic, d)
#define vtextSetStyleStrikethru(e,s,d) _vtextSetStyleBoolean(s, vtext_Strikethru, d)
#define vtextSetStyleHidden(e,s,d)     _vtextSetStyleBoolean(s, vtext_Hidden, d)

#define vtextGetStyleAttribute(s,a) 	_vtextGetAttribute(&(s)->attributes, a)
#define vtextGetStyleAttributeScalar(s,a)	\
    _vtextGetAttributeScalar(&(s)->attributes, a)

#define vtextGetStyleFont(e,s)	   ((vfont *) vtextGetStyleAttribute(s, vtext_Font))
#define vtextGetStyleData(e,s)	   ((void *) vtextGetStyleAttribute(s, vtext_Data))
#define vtextGetStyleColor(e,s)	   ((vcolor *) vtextGetStyleAttribute(s, vtext_Color))
#define vtextGetStyleBackgroundColor(e,s) ((vcolor *) vtextGetStyleAttribute(s, vtext_BackgroundColor))
#define vtextGetStyleDescent(e,s)  _vtextGetStyleScalar(s, vtext_Descent)
#define vtextGetStyleAscent(e,s)   _vtextGetStyleScalar(s, vtext_Ascent)
#define vtextGetStyleSize(e,s)     _vtextGetStyleScalar(s, vtext_Size)
#define vtextGetStyleBold(e,s)	     _vtextGetStyleBoolean(s, vtext_Bold)
#define vtextGetStyleUnderline(e,s)  _vtextGetStyleBoolean(s, vtext_Underline)
#define vtextGetStyleInvert(e,s)     _vtextGetStyleBoolean(s, vtext_Invert)
#define vtextGetStyleItalic(e,s)     _vtextGetStyleBoolean(s, vtext_Italic)
#define vtextGetStyleStrikethru(e,s) _vtextGetStyleBoolean(s, vtext_Strikethru)
#define vtextGetStyleHidden(e,s)     _vtextGetStyleBoolean(s, vtext_Hidden)
#define vtextGetStyleGraphic(e,s)  ((vtextGraphic *) (vtextGetStyleAttribute((s), vtext_Graphic)))
#define vtextIsStyleGraphic(e,s)   (vtextGetStyleAttribute((s), \
					   vtext_Graphic) != NULL)

#define vtextSetRulerLeftIndent(e,r,v) 	    _vtextSetRulerScalar(r, vtext_LeftIndent, v)
#define vtextSetRulerRightIndent(e,r,v)     _vtextSetRulerScalar(r, vtext_RightIndent, v)
#define vtextSetRulerFirstLineIndent(e,r,v) _vtextSetRulerScalar(r, vtext_FirstLineIndent, v)
#define vtextSetRulerTabWidth(e,r,v) 	    _vtextSetRulerScalar(r, vtext_TabWidth, v)
#define vtextFSetRulerLeftIndent(e,r,v) 	    _vtextSetRulerScalar(r, vtext_LeftIndent, _vtextFixedAttributeFromFloat(v))
#define vtextFSetRulerRightIndent(e,r,v)     _vtextSetRulerScalar(r, vtext_RightIndent, _vtextFixedAttributeFromFloat(v))
#define vtextFSetRulerFirstLineIndent(e,r,v) _vtextSetRulerScalar(r, vtext_FirstLineIndent, _vtextFixedAttributeFromFloat(v))
#define vtextFSetRulerTabWidth(e,r,v) 	    _vtextSetRulerScalar(r, vtext_TabWidth, _vtextFixedAttributeFromFloat(v))

#define vtextSetRulerJustification(e,r,v)   _vtextSetRulerJust(r, vtext_Justification, v)
#define vtextSetRulerDescent(e,s,d) 	    _vtextSetRulerScalar(s, vtext_Descent, d)
#define vtextSetRulerAscent(e,s,d)  	    _vtextSetRulerScalar(s, vtext_Ascent, d)
#define vtextSetRulerSpacingBefore(e,s,d)   _vtextSetRulerScalar(s, vtext_SpacingBefore, d)
#define vtextSetRulerSpacingAfter(e,s,d)    _vtextSetRulerScalar(s, vtext_SpacingAfter, d)
#define vtextSetRulerWrap(e,s,d)   	    _vtextSetRulerBoolean(s, vtext_Wrap, d)
#define vtextSetRulerData(e,s,d)   	    _vtextSetRulerPointer(s, vtext_Data, d)

#define vtextGetRulerAttribute(r,a) 	_vtextGetAttribute(&(r)->attributes, a)
#define vtextGetRulerAttributeScalar(r,a)	\
    _vtextGetAttributeScalar(&(r)->attributes, a)

#define vtextGetRulerLeftIndent(e,r)	  ((vfixed) _vtextGetRulerScalar(r, vtext_LeftIndent))
#define vtextGetRulerRightIndent(e,r)	  ((vfixed) _vtextGetRulerScalar(r, vtext_RightIndent))
#define vtextGetRulerFirstLineIndent(e,r) ((vfixed) _vtextGetRulerScalar(r, vtext_FirstLineIndent))
#define vtextGetRulerTabWidth(e,r)	  ((vfixed) _vtextGetRulerScalar(r, vtext_TabWidth))
#define vtextFGetRulerLeftIndent(e,r)	  (_vtextFixedAttributeToFloat(_vtextGetRulerScalar(r, vtext_LeftIndent)))
#define vtextFGetRulerRightIndent(e,r)	  (_vtextFixedAttributeToFloat(_vtextGetRulerScalar(r, vtext_RightIndent)))
#define vtextFGetRulerFirstLineIndent(e,r) (_vtextFixedAttributeToFloat(_vtextGetRulerScalar(r, vtext_FirstLineIndent)))
#define vtextFGetRulerTabWidth(e,r)	  (_vtextFixedAttributeToFloat(_vtextGetRulerScalar(r, vtext_TabWidth)))

#define vtextGetRulerJustification(e,r)	  _vtextGetRulerJust(r, vtext_Justification)
#define vtextGetRulerAscent(e,r)	  ((short)_vtextGetRulerScalar(r, vtext_Ascent))
#define vtextGetRulerDescent(e,r)	  ((short)_vtextGetRulerScalar(r, vtext_Descent))
#define vtextGetRulerSpacingBefore(e,r)	  ((short)_vtextGetRulerScalar(r, vtext_SpacingBefore))
#define vtextGetRulerSpacingAfter(e,r)	  ((short)_vtextGetRulerScalar(r, vtext_SpacingAfter))
#define vtextGetRulerWrap(e,s)    	  _vtextGetRulerBoolean(s, vtext_Wrap)
#define vtextGetRulerData(e,s)	  	  ((void *) vtextGetRulerAttribute(s, vtext_Data))

/*
 * * * * * * * * * * PRIVATE FUNCTION MESSAGE DEFINITIONS * * * * * * * * * *
 */

#define vtextAppendBlock(e,t,l,z) vclassSend(vtextGetClass(e), \
					    vtextAPPEND_BLOCK, (e,t,l,z))
#define vtextInsert(e,s,d,o)	 vclassSend(vtextGetClass(e), \
					    vtextINSERT, (e,s,d,o))
#define vtextDelete(e,s)	 vclassSend(vtextGetClass(e), \
					    vtextDELETE, (e,s))
#define vtextKey(e,s,c)		 vclassSend(vtextGetClass(e), \
					    vtextKEY, (e,s,c))
#define vtextProcess(e,s,f,i,t)	 vclassSend(vtextGetClass(e), \
					    vtextPROCESS, (e,s,f,i,t))
#define vtextSelectRange(e,s,a,b) vclassSend(vtextGetClass(e), \
					    vtextSELECT_RANGE, (e,s,a,b))
#define vtextSelectRangeRectangular(e,s,a,b,x,y)	       		     \
				 vclassSend(vtextGetClass(e), 		     \
					    vtextSELECT_RANGE_RECTANGULAR,   \
					    (e,s,a,b,x,y))
#define vtextSelectLines(e,s,a,b,m) vclassSend(vtextGetClass(e), \
					    vtextSELECT_LINES, (e,s,a,b,m))
#define vtextInsertGraphic(e,s,c,l) vclassSend(vtextGetClass(e), \
					    vtextINSERT_GRAPHIC, (e,s,c,l))
#define vtextInsertGraphicObject(e,s,g) vclassSend(vtextGetClass(e), \
					   vtextINSERT_GRAPHIC_OBJECT, (e,s,g))
#define vtextInsertGraphicObjectOwned(e,s,g) 		\
             ((g)->flags |= _vtextGRAPHIC_OWNED,  \
	      vtextInsertGraphicObject(e,s,g))

#define vtextHide(e,a)           vclassSend(vtextGetClass(e), \
					    vtextHIDE, (e,a))
#define vtextShow(e,a)           vclassSend(vtextGetClass(e), \
					    vtextSHOW, (e,a))
#define vtextCalculate(e)	 vclassSend(vtextGetClass(e), \
					    vtextCALCULATE, (e))
#define vtextAddTag(e,t)	 vclassSend(vtextGetClass(e), \
					    vtextADD_TAG, (e,t))
#define vtextRemoveTag(e,t)	 vclassSend(vtextGetClass(e), \
					    vtextREMOVE_TAG, (e,t))
#define vtextWarpTag(e,t,p,d)	 vclassSend(vtextGetClass(e), \
					    vtextWARP_TAG, (e,t,p,d))
#define vtextLineRange(e,l,a,b)	 vclassSend(vtextGetClass(e), \
					    vtextLINE_RANGE, (e,l,a,b))
#define vtextCalcWidths(e,s,t,l,p,n) vclassSend(vtextGetClass(e), \
					    vtextCALC_WIDTHS, (e,s,t,l,p,n))
#define _vtextDetermineWrapBreak(e,s,l) vclassSend(vtextGetClass(e), \
					    vtextWRAP_BREAK, (e,s,l))
#define _vtextDetermineWordBreak(e,s,l) vclassSend(vtextGetClass(e), \
					    vtextWORD_BREAK, (e,s,l))
#define vtextIsInWord(e,p,c)	vclassSend(vtextGetClass(e), \
					   vtextIS_IN_WORD, (e,p,c))
#define vtextCanWrapAfter(e,p,c) vclassSend(vtextGetClass(e), \
					    vtextCAN_WRAP_AFTER, (e,p,c))

#define vtextCalcStyle(e,s)	vclassSend(vtextGetClass(e), \
					    vtextCALC_STYLE, (e,s))
#define vtextCalcRuler(e,r)	vclassSend(vtextGetClass(e), \
					    vtextCALC_RULER, (e,r))

#define vtextDrawGraphic(g)	 vclassSend(vtextGetGraphicClass(g), \
					    vtextGraphicDRAW, (g))
#define vtextDrawGraphicWith(g,c) vclassSend(vtextGetGraphicClass(g), \
					    vtextGraphicDRAW_WITH, (g,c))

#define vtextDetermineStyleFont(g)				   \
				 vclassSend(vtextGetStyleClass(g), \
					    vtextStyleDETERMINE_FONT, (g))

#define vtextDestroyGlobalStyle(g)	vtextDestroyStyle(g)

#define _vtextSetStyleAttributeRaw(g,a,v,s) \
    vclassSend(vtextGetStyleClass(g), vtextStyleSET_ATTRIBUTE, (g, a, v, s))
#define vtextSetStyleAttribute(g,a,v) \
    _vtextSetStyleAttributeRaw(g, a, (void *) (v), 0)
#define vtextSetStyleAttributeScalar(g,a,v) \
    _vtextSetStyleAttributeRaw(g, a, NULL, v)

#define vtextRemoveStyleAttribute(s,a)    \
    _vtextRemoveAttribute(&(s)->attributes, a)


#define vtextDestroyGlobalRuler(r)	vtextDestroyRuler(r)

#define _vtextSetRulerAttributeRaw(g,a,v,s) \
    vclassSend(vtextGetRulerClass(g), vtextRulerSET_ATTRIBUTE, (g, a, v, s))
#define vtextSetRulerAttribute(g,a,v) \
    _vtextSetRulerAttributeRaw(g, a, (void *) (v), 0)
#define vtextSetRulerAttributeScalar(g,a,v) \
    _vtextSetRulerAttributeRaw(g, a, NULL, v)

#define vtextRemoveRulerAttribute(s,a)    \
    _vtextRemoveAttribute(&(s)->attributes, a)


#if vdebugDEBUG
#define vtextScribeText(e, s)	\
    _vtextScribeTextDebug(e, s, vdebugTAG, __FILE__, __LINE__)
#else
#define vtextScribeText(e, s)	\
    _vtextScribeTextNondebug(e, s)
#endif

#if vdebugDEBUG


#endif

vportEND_CPLUSPLUS_EXTERN_C


#endif /* #ifndef vtextINCLUDED */

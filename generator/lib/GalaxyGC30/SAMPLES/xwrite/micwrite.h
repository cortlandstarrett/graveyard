/* $Id: micwrite.h,v 1.6 1997/04/16 18:25:48 david Exp $ */

/************************************************************

    micwrite.h
    C Interface to xwrite

    (c) Copyright Visix Software Inc.
    All rights reserved

************************************************************/

#ifndef writeINCLUDED
#define writeINCLUDED 1

#ifndef  vportINCLUDED
#include <vport.h>		/* for v*HEADER */
#endif

#ifndef  vgalaxyINCLUDED
#include vgalaxyHEADER
#endif

#ifndef  xctransINCLUDED
#include "xctrans.h"
#endif

#ifndef  xcflchsrINCLUDED
#include "xcflchsr.h"
#endif

#ifndef  xtextviewINCLUDED
#include "xtxtview.h"
#endif

/*
 * * * * * * * * * CONSTANTS AND MACRO DEFINITIONS * * * * * * * * * *
 */

#define writeMAX_DOCUMENTS		100

/*
 * Array values in the global string resource array
 */

enum {
    writeMSG_UNTITLED		= 0,
    writeMSG_SAVE_CHANGES,
    writeMSG_ALREADY_EXISTS,
    writeMSG_SAVE_DOCUMENT,
    writeMSG_CANT_SAVE_CHANGES,
    writeMSG_IMPORTING,
    writeMSG_READ_ERROR
    };

/* Values for search options */

enum {
    writeCASE_SENSITIVE    = 0x0001,
    writeWHOLE_WORD	    = 0x0002,
    writeBACKWARD_SEARCH   = 0x0004,
    writeREGEXP_SEARCH	    = 0x0008,
    writeWRAP_SEARCH	    = 0x0010,
    writeGLOBAL_SEARCH	    = 0x0020
};

/* Values for 'flags' field in writeData */

enum {
    writeDOC_SHOW_RULER		= 0x0001,
    writeDOC_SHOW_RIBBON	= 0x0002,
    writeDOC_SELECT_STATE	= 0x0008,
    writeDOC_MODIFIED		= 0x0010,
    writeDOC_READ_ONLY		= 0x0020
};

/*
 * Values for 'flag' field in writeStyle structure
 */

enum {
    writeSTYLE_GLOBAL		= 0x0001
};

/*
 * Preference options
 */

enum {
    writePREF_BACKUP                    = 0x0001,
    writePREF_AUTO_STROKE               = 0x0020,
    writePREF_AUTO_TIME                 = 0x0040,
    writePREF_FULL_TITLES		= 0x0080
};

/* Returns values for writeSaveDocument */

enum {
    writeDID_SAVE_AS		= 0,
    writeSAVED			= 1,
    writeWAS_READ_ONLY		= 2
    };

/*
 * Application Commands
 */

enum {
    comNEW_DOCUMENT		= vdialogNEXT_SELECT,
    comINFORMATION,
    comQUIT,
    comACTIVATE_SEARCH,
    comABOUT_WRITE,
    comPREFERENCES,
    comOPEN_REQUEST,
    comINCREMENTAL_SEARCH,
    comSTYLES,
    comIMPORT,
    comWHOLE_WORD,
    comCASE_SENSITIVE,
    comSEARCH_BACKWARDS,
    comPATTERN_SEARCH,
    comWRAP_SEARCH,
    comGLOBAL_SEARCH
};

/*
 * Document Commands
 */

enum {
    comCLOSE_WINDOW		= vdialogNEXT_SELECT,
    comREVERT,
    comSAVE,
    comSEARCH,
    comSAVE_TEMPLATE_DOCUMENT,
    comFIND,
    comREPLACE,
    comGOTO_MARKER,
    comSET_SEARCH_AREA,
    comMARK,
    comUNMARK,
    comSHOW_RULER,
    comSHOW_RIBBON,
    comSHOW_VERTICAL_SCROLL_BAR,
    comSHOW_HORIZONTAL_SCROLL_BAR,
    comPUSH_POSITION,
    comPOP_POSITION,
    comFORMAT,
    comEXPORT,
    comINSERT_GRAPHIC,
    comAPPLY_TEXT_STYLE,
    comVIEW,
    comVIEW_NORMAL,
    comVIEW_INVISIBLES,
    comVIEW_KEYCODES,
    comXXX2,
    comDBG_DUMP_STYLES,
    comDBG_DUMP_RULERS,
    comDBG_DUMP_BLOCKS,
    comDBG_STYLE_TEST,
    comDBG_CLICK_STYLE_INFO
};

/*
 * Search Window Commands
 */

enum {
    comSHOW_FOUND_TEXT		= vdialogNEXT_SELECT,
    comFIND_BUTTON,
    comCLOSE_SEARCH,
    comCHANGE_SELECTION,
    comCHANGE_THEN_FIND,
    comCHANGE,
    comCHANGE_ALL,
    comFIND_THEN_CHANGE
};

/*
 * Style Window Commands
 */

enum {
    comNEW_STYLE		= vdialogNEXT_SELECT,
    comAPPLY_STYLE,
    comCLOSE_STYLE,
    comEDIT_STYLE
};

/*
 * Global preditor strings text view strings
 */

enum {
    _write_Write,
    _write_Append,
    _write_Tag,
    _write_Target,
    _write_Option,
    _write_As,
    _write_Copy,
    _write_Quick,
    _write_Selection,
    _write_Again,
    _write_Reverse,
    _write_Path,
    _write_Enable,
    _write_Disable,
    _write_Show,
    _write_Hide,
    _write_First,
    _write_By,
    _write_Ruler,
    _write_IconBox,
    _write_Ribbon,
    _write_Invisible1,
    _write_Regexp,
    _write_NormalStyle,
    _write_Normal,
    _write_Marker,
    _write_ChangeAll,
    _write_ChangeSelection,
    _write_Count
};

#define write_Append       	(_writePredefs[_write_Append])
#define write_Tag       	(_writePredefs[_write_Tag])
#define write_Target       	(_writePredefs[_write_Target])
#define write_Option       	(_writePredefs[_write_Option])
#define write_As       		(_writePredefs[_write_As])
#define write_Copy       	(_writePredefs[_write_Copy])
#define write_Quick       	(_writePredefs[_write_Quick])
#define write_Selection       	(_writePredefs[_write_Selection])
#define write_Again       	(_writePredefs[_write_Again])
#define write_Reverse       	(_writePredefs[_write_Reverse])
#define write_Path       	(_writePredefs[_write_Path])
#define write_Enable       	(_writePredefs[_write_Enable])
#define write_Disable       	(_writePredefs[_write_Disable])
#define write_Show       	(_writePredefs[_write_Show])
#define write_Hide       	(_writePredefs[_write_Hide])
#define write_First      	(_writePredefs[_write_First])
#define write_By	     	(_writePredefs[_write_By])
#define write_Ruler	     	(_writePredefs[_write_Ruler])
#define write_IconBox	     	(_writePredefs[_write_IconBox])
#define write_Ribbon	     	(_writePredefs[_write_Ribbon])
#define write_Invisible1     	(_writePredefs[_write_Invisible1])
#define write_Regexp     	(_writePredefs[_write_Regexp])
#define write_NormalStyle     	(_writePredefs[_write_NormalStyle])
#define write_Normal     	(_writePredefs[_write_Normal])
#define write_Marker     	(_writePredefs[_write_Marker])
#define write_ChangeAll     	(_writePredefs[_write_ChangeAll])
#define write_ChangeSelection  	(_writePredefs[_write_ChangeSelection])

/*
 * * * * * * * * * TYPE AND STRUCTURE DEFINITIONS * * * * * * * * * *
 */

typedef struct writeDocument		writeDocument;
typedef struct writeDocumentClass	writeDocumentClass;

struct writeDocument {
    vdialog			dialog;
    struct writeDocument	*next;
    vchar			*name;
    vresource			fileSpec;
    int				newIndex;
    unsigned short		flags;
    vundoLog			*undoLog;

    short			autostrokes;
    short			autominutes;

    struct writeMarker		*markList;
    int				markMenuCount;

    short			styleCount;
    struct writeStyle		*styleList;
    
    vtextview			*textItem; 
    vdialogItem			*ribbon;
    vtextruler			*ruler;
    vdialogItem			*iconBox;
    vcombo			*combo;

    vmenubar			*menuBar;
    vmenu			*markMenu;
    vmenu			*popupMarkMenu;
    vmenu			*windowMenu;

    vdict			*standardState;
    vcommandSpace		*space;
};

#define writeDocumentCLASS(SUPER, DIALOG)	                             \
    vdialogCLASS(SUPER, DIALOG, vdialogNoteProc, vdialogItem,		     \
		 vdialogItemList); 					     \
    vclassMETHOD(writeDocumentNO_OP, (DIALOG *))

struct writeDocumentClass {
    writeDocumentCLASS(writeDocumentClass, writeDocument);
};

/*
 * Markers
 */

typedef struct writeMarker {
    vtextTag		tag;
    writeDocument	*data;
    vchar		name[32];
    struct writeMarker	*next;
} writeMarker;

/*
 * Preference information
 */

typedef struct writePreferenceData {
    short	    numAutoStrokes;  /* Number of strokes between saves */
    short	    numAutoMinutes;  /* Number of minutes between saves */
    unsigned long   options;
    short	    maxUndos;	     /* Levels of Undo		        */
    unsigned short  searchPrefs;    /* Search Preferences	       */
    short	    sourceAdjust;
} writePreferenceData;
    

typedef struct writeTemplatePreferenceData {
    vrect		newDocumentRect;
    int			flags;
    struct writeStyle	*styleList;
} writeTemplatePreferenceData;

/*
 * Search window
 */

typedef struct writeSearchDoc		writeSearchDoc;
typedef struct writeSearchDocClass	writeSearchDocClass;

struct writeSearchDoc {
    vdialog		dialog;
    vbool		searchSelection;
    vbool		incremental;
    vbyte		flags;
    vbyte		reservedFlag;
    short		currentText;
    vtextitem           *target;
    vtextitem           *replace;
    long		incrementalPos;

    vchar               targetText[1024];
    vchar               replaceText[1024];
};

#define writeSearchDocCLASS(SUPER, DIALOG)				     \
    vdialogCLASS(SUPER, DIALOG, vdialogNoteProc, vdialogItem,		     \
		 vdialogItemList); 					     \
    vclassMETHOD(writeSearchDocNOOP, (DIALOG *))

struct writeSearchDocClass {
    writeSearchDocCLASS(writeSearchDocClass, writeSearchDoc);
};

/*
 * Style window and write style
 */

typedef struct writeStyleDoc		writeStyleDoc;
typedef struct writeStyleDocClass	writeStyleDocClass;

struct writeStyleDoc {
    vdialog		dialog;
    vtextStyle		*selectedStyle;

    int			untitledCount;

    vtextitem		*description;
    vlistview		*styleList;
};

#define writeStyleDocCLASS(SUPER, DIALOG)				     \
    vdialogCLASS(SUPER, DIALOG, vdialogNoteProc, vdialogItem,		     \
		 vdialogItemList); 					     \
    vclassMETHOD(writeStyleDocNOOP, (DIALOG *))

struct writeStyleDocClass {
    writeStyleDocCLASS(writeStyleDocClass, writeStyleDoc);
};


typedef struct writeStyle {
    const vname		*name;
    vtextStyle		*style;
    int			flags;
    struct writeStyle   *next;
} writeStyle;


/*
 * * * * * * * * * PREDITOR FUNCTION PROTOTYPES * * * * * * * * * *
 */

/* micwrite.c */

int main(
    short       	argc,
    char       		**argv
    );

vnotice *writeAlert(
    vdialog		*dialog,
    vchar		*message
    );

vnotice *writeConfirmation(
    vdialog		*dialog,
    vchar		*message,
    vnoticeHookProc	okHook,
    vnoticeHookProc	noHook
    );

const vname *writeModalConfirmation(
    vdialog	*dialog,
    vchar	*message
    );

void writeCenterWindow(
    vwindow		*window
    );

void writeReplaceStrings(
    vstr 		**strPtr, 
    vscribe 		*s1, 
    vscribe 		*s2
    );

void writeOpenStyleChooser(void);

vdialog *writeLoadDialog(
    const vname 	*tag
    );

vcommandSpace *writeLoadSpace(
    const vname 	*tag
    );

void writeStartup(void);

void writeShutdown(void);

vbool writeCloseAllDocuments(void);

/* document.c */

void writeNewDocument(void);

void writeOpenDocument(
    const vfsPath	*filePath
    );

void writeImportDocument(
    const  vfsPath		*filePath,
    int                          charset,
    int                          byteOrder			 
    );

void writeCloseDocument(
    writeDocument	*data,
    vdict		*context
    );

vbool writeSaveDocument(
    writeDocument	*data,
    vdict		*context
    );


vbool writeExportDocument(
    writeDocument	*data,
    vdict		*context
    );

vbool writeIsDocumentValid(
    writeDocument	*data
    );

vbool writeGetSelection(
    writeDocument	*data,
    int			limit
    );

void writeSetDocumentIcon(
    writeDocument	*data,
    unsigned short	flag,
    vbool		enable
    );

void writeChangeDocumentState(
    writeDocument	*data,
    const vname		*name,
    const vname		*value
    );

void writeBuildWindowMenus(void);

void writeDocumentStartup(void);

void writeDocumentShutdown(void);

/* mark.c */

void writeCreateMarkWindow(void);

void writeCreateUnmarkWindow(void);

void writeLoadUnmarkWindow(
    writeDocument	*data,
    vbool               setTarget
    );

writeMarker *writeAddMarker(
    writeDocument	*data,
    vchar               *markerName,
    long		start,
    long		end
    );

void writeRemoveMarker(
    writeDocument 	*data,
    writeMarker		*marker
    );

void writeRemoveAllMarkers(
    writeDocument	*data
    );

void writeAddMarkerMenu(
    writeDocument	*data,
    writeMarker		*marker
    );

void writeRemoveMarkerMenu(
    writeDocument	*data,
    writeMarker		*marker
    );

void writeSelectMarker(
    writeDocument       *data,
    writeMarker		*marker
    );

void writeStoreMarkers(
    writeDocument	*data,
    vresource		res
    );

void writeLoadMarkers(
    writeDocument	*data,
    vresource		res
    );

void writeMarkStartup(void);

void writeMarkShutdown(void);

/* pref.c */

void writeLoadTemplate(
    vresource			res,
    writeTemplatePreferenceData	*prefs
    );

void writeStoreTemplate(
    vresource			res,
    writeTemplatePreferenceData	*prefs
    );

void writePreferencesStartup(void);

void writePreferencesShutdown(void);

/* search.c */

void writeCreateSearchWindow(void);

void writeDestroySearchWindow(
    writeSearchDoc	*data
    );

vbool writeSearchDocument(
    writeDocument	*data,
    vdict		*context
    );

void writeChangeInDocument(
    writeDocument	*data,
    vdict		*context
    );

void writeChangeAllInDocument(
    writeDocument	*data,
    vdict		*context
    );

void writeSetTargetDocument(
    writeDocument	*target
    );

writeDocument *writeGetTargetDocument(void);

void writeSearchStartup(void);

void writeSearchShutdown(void);

/* style.c */

void writeCreateStyleWindow(void);

void writeDestroyStyleWindow(
    writeStyleDoc	*data
    );

void writeLoadStyleWindow(
    writeDocument	*data,
    vbool               setTarget
    );

writeStyle *writeCreateStyle(void);

void writeDestroyStyle(
    writeStyle		*style
    );

writeStyle *writeLoadStyleList(
    vresource		res
    );

void writeStoreStyleList(
    writeStyle		*styleList,
    vresource		res
    );

void writeDestroyStyleList(
    writeStyle		**styleList
    );

void writeStyleStartup(void);

void writeStyleShutdown(void);

/*
 * * * * * * * * * FUNCTIONS IMPLEMENTED AS MACROS * * * * * * * *
 */

#define writeDestroyDocument(d)		vwindowDestroyLater((vwindow *) (d))
#define writeDestroySearchWindow(d)	vwindowDestroyLater((vwindow *) (d))
#define writeDestroyStyleWindow(d)	vwindowDestroyLater((vwindow *) (d))

/*
 * * * * * * * * GLOBAL VARIABLES * * * * * * * * * *
 */

extern writeDocument		    *writeDocumentList;
extern const vchar 		    *_writePredefs[];
extern vresource		    writeResFile;
extern vresource		    writeUserPrefFile;
extern vdialog			    *wrtDialog;
extern vfilechsr		    *writeOpenWindow;
extern vfilechsr		    *writeSaveWindow;
extern xcflchsr 		    *writeImportWindow;
extern xcflchsr 		    *writeExportWindow;
extern vstylechsr		    *writeStyleChooser;
extern vconfirm			    *writeMarkWindow;
extern vconfirm	    	            *writeUnmarkWindow;
extern writeSearchDoc		    *writeSearchWindow;
extern short			    writeSearchOptions;


extern writeStyleDoc		    *writeStyleWindow;
extern writeStyle                   *writeStyleList;
extern int			    writeStyleCount;
extern writeStyle		    *writeNormalStyle;


extern vchar			    writeSelection[];
extern int			    writeSelectionLength;
extern vresource	            writeMessages;

extern writePreferenceData          writePreferences;
extern writeTemplatePreferenceData  writeTemplatePreferences;

#endif /* #ifndef writeINCLUDED */

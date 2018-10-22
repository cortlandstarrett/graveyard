/* $Id: vfilechsr.h,v 1.56 1997/09/02 19:38:27 robert Exp $ */

/************************************************************

    vfilechsr.h
    C Interface to the File Chooser

    (c) Copyright Visix Software  1991
    All rights reserved

************************************************************/

#ifndef vfilechsrINCLUDED
#define vfilechsrINCLUDED 1

#ifndef  vportINCLUDED
#include <vport.h>			/* for v*HEADER */
#endif

#ifndef  vdictINCLUDED
#include vdictHEADER
#endif

#ifndef  vfsINCLUDED
#include vfsHEADER
#endif

#ifndef  vmenuINCLUDED
#include vmenuHEADER
#endif

#ifndef  vdialogINCLUDED
#include vdialogHEADER
#endif

#ifndef  vcontrolINCLUDED
#include vcontrolHEADER
#endif

#ifndef  vmenubarINCLUDED
#include vmenubarHEADER
#endif

#ifndef  vconfirmINCLUDED
#include vconfirmHEADER
#endif

#ifndef  vtextitemINCLUDED
#include vtextitemHEADER
#endif

#ifndef  vlistINCLUDED
#include vlistHEADER
#endif

#ifndef  vlistviewINCLUDED
#include vlistviewHEADER
#endif



vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * * * * * * * * * * PUBLIC CONSTANT DEFINITIONS * * * * * * * * * *
 */

/* File Chooser command selector values */

enum {
    vfilechsrSELECT_HOME        = vdialogNEXT_SELECT,
    vfilechsrSELECT_MARK,
    vfilechsrSELECT_UNMARK,
    vfilechsrSELECT_VIEW_BY,
    vfilechsrSELECT_COMPLETE,
    vfilechsrNEXT_SELECT
};

/* Values for file chooser 'selection' behavior */

enum {
     vfilechsrSINGLE		= 1,
     vfilechsrMULTIPLE		= 2
};

/* Values for file chooser 'type' */

enum {
     vfilechsrGET		 = 1,
     vfilechsrPUT		 = 0
};

/* Values for 'direction' parameter to vfilechsrShiftDirectory() */

enum {
    vfilechsrUP			= 1,
    vfilechsrDOWN	        = 2
};

/* Values for file chooser options */
enum {
    vfilechsrOPTION_SHOW_READONLY= 0x01,
    vfilechsrOPTION_CONFIRM_OVERWRITE= 0x02,
    vfilechsrOPTION_FILE_MUST_EXIST= 0x04,
    vfilechsrOPTION_PATH_MUST_EXIST= 0x08,
    vfilechsrOPTION_HIDE_HIDDEN=0x10,
    vfilechsrOPTION_ONLY_DIRS=0x20,
    vfilechsrOPTION_MULTIPLE_ABANDON=0x40,
    vfilechsrOPTION_DEFAULT_READONLY= 0x80,
    vfilechsrOPTION_HIDE_PATH_ENTRY= 0x100,
    vfilechsrOPTION_READONLY= 0x1000,
    vfilechsrOPTION_OVERWRITE= 0x2000,
    vfilechsrOPTION_DIR=0x4000
};


/* The default number of history item allow in a file chooser */
#define vfilechsrDEFAULT_MAX_HIST_LIST_ITEMS 5


/* The maximum directory lists shown by the file chooser */
#define vfilechsrMAX_NUM_LISTS	5



/* Default tags used to build system filter type list resources */
#define vfilechsrViewName       (_vfilechsrPredefs[_vfilechsr_ViewName])
#define vfilechsrFiltersMenuName (_vfilechsrPredefs[_vfilechsr_FiltersMenuName])
#define vfilechsrFileTypeRootDictName (_vfilechsrPredefs[_vfilechsr_FileTypes])
#define vfilechsrUnixDictName	(_vfilechsrPredefs[_vfilechsr_Unix])
#define vfilechsrDOSDictName	(_vfilechsrPredefs[_vfilechsr_DOS])
#define vfilechsrMacintoshDictName (_vfilechsrPredefs[_vfilechsr_Macintosh])
#define vfilechsrOS2DictName	(_vfilechsrPredefs[_vfilechsr_OS2])
#define vfilechsrVMSDictName	(_vfilechsrPredefs[_vfilechsr_VMS])
#define vfilechsrWindowsNTDictName (_vfilechsrPredefs[_vfilechsr_NT])
#define vfilechsrWindowsDictName vfilechsrDOSDictName
#define vfilechsrCaseInsensitiveName (_vfilechsrPredefs[_vfilechsr_CaseInsenstive])
#define vfilechsrDelimiterName (_vfilechsrPredefs[_vfilechsr_Delimiter])
#define vfilechsrExtensionName (_vfilechsrPredefs[_vfilechsr_DefExtension])
#define vfilechsrPatternSupplement (_vfilechsrPredefs[_vfilechsr_PatternSupplement])
#define vfilechsrFilterSpecsId (_vfilechsrPredefs[_vfilechsr_FilterSpecsId])



/*
 * * * * * * * * * * PUBLIC TYPE DEFINITIONS * * * * * * * * * *
 */

typedef struct vfilechsr		vfilechsr;
typedef struct vfilechsrClass		vfilechsrClass;
typedef struct vfilechsrEntry 		vfilechsrEntry;

typedef int (*vfilechsrCompareFunc)(
    const vfilechsrEntry	*entry1,
    const vfilechsrEntry	*entry2
    );

typedef int (*vfilechsrApplyFunc)(
    vfilechsr 		*fileChooser,
    vfsPath 		*path
    );

typedef int (*vfilechsrFilterFunc)(
    vfsPath		*dirPath,
    vfilechsrEntry	*entry,
    vfsPath		*entryPath
    );
    
/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */

void vfilechsrStartup(void);


/* File Chooser Class Functions */

vfilechsrClass *vfilechsrGetDefaultClass(void);

/* Initialization and allocation */

vfilechsr *vfilechsrCreate(void);

vfilechsr *vfilechsrCreateOfClass(
    vfilechsrClass	*clas
    );

void vfilechsrDestroy(
    vfilechsr		*fileChooser
    );

void vfilechsrOpen(
    vfilechsr		*fileChooser
    );

const vname *vfilechsrProcess(
    vfilechsr		*fileChooser
    );

void vfilechsrClose(
    vfilechsr		*fileChooser
    );

/* File Chooser Operations */

void vfilechsrComplete(
    vfilechsr		*fileChooser
    );

void vfilechsrRescan(
    vfilechsr		*fileChooser
    );

void vfilechsrAddViewBy(
    vfilechsr		 *fileChooser,
    const vchar		 *viewByName,
    vfilechsrCompareFunc compareFunc
    );

void vfilechsrRemoveViewBy(
    vfilechsr		 *fileChooser,
    const vchar		 *viewByName
    );

/* File Chooser attribute modification */

void vfilechsrSetApply(
    vfilechsr		*fileChooser,
    vfilechsrApplyFunc	applyFunc
    );

void vfilechsrSetDirectory(
    vfilechsr		*fileChooser,
    const vfsPath	*newPath
    );

void vfilechsrSetFile(
    vfilechsr		*fileChooser,
    const vfsPath	*newFile
    );

void vfilechsrSetFileIndex(
    vfilechsr		*fileChooser,
    int			 row
    );

void vfilechsrShiftDirectory(
    vfilechsr		*fileChooser,
    int			direction
    );

void vfilechsrSetData(
    vfilechsr		*fileChooser,
    void		*data
    );

void vfilechsrSetType(
    vfilechsr		*fileChooser,
    int			type
    );

void vfilechsrSetSelection(
    vfilechsr		*fileChooser,
    int			selection
    );

void vfilechsrSetMinListWidth(
    vfilechsr		*fileChooser,
    int			minListWidth
    );

void vfilechsrSetConfirmOverwrite(
    vfilechsr		*fileChooser,
    int			doConfirm				  
    );

void vfilechsrSetPreferNative(
    vfilechsr		*fileChooser,
    int			 doNative
    );

void vfilechsrSetOverridePreferNative(
    vfilechsr		*fileChooser,
    int			 doNative
    );

void vfilechsrSetDocumentNameScribed(
    vfilechsr		*fileChooser,
    vscribe		*documentName
    );

void vfilechsrSetDocumentName(
    vfilechsr		*fileChooser,
    const vchar		*documentName
    );

void vfilechsrSetPromptNameScribed(
    vfilechsr		*fileChooser,
    vscribe		*promptName
    );

void vfilechsrSetPromptName(
    vfilechsr		*fileChooser,
    const vchar		*promptName
    );

void vfilechsrSetCompletionKeystroke(
    vfilechsr		*fileChooser,
    int			 wantCompletion,
    vkeyStroke		 keystroke
    );

void vfilechsrSetTitle(
    vfilechsr		*fileChooser,
    const vchar		*title
    );

void vfilechsrSetTitleScribed(
    vfilechsr		*fileChooser,
    vscribe		*title
    );

void vfilechsrSetLeader(
    vfilechsr		*fileChooser,
    vwindow		*leader
    );

void vfilechsrPlace(
    vfilechsr		*fileChooser,
    vdialog		*base,
    int			 modeX,
    int			 modeY
    );

void vfilechsrSetOptions(
    vfilechsr		*fileChooser,
    unsigned int	 options
    );

void vfilechsrSetMaxHistoryCount(
    vfilechsr		*fileChooser,
    short		 historyCount
    );

void vfilechsrClearHistory(
    vfilechsr		*fileChooser
    );

void vfilechsrAddFilterBySystemType(
    vfilechsr 		*fileChooser,
    vresource 		 filterTypes,
    const vname		*addFilter,
    const vname		*defaultFilter
    );			 

void vfilechsrAddFilterByPatternScribed(
    vfilechsr		*fileChooser,
    const vname		*id,
    vscribe		*title,
    vscribe		*pattern,
    int			 makeDefaultSelection
    );

void vfilechsrAddFilterByPattern(
    vfilechsr		*fileChooser,
    const vname		*id,
    const vchar		*title,
    const vchar		*pattern,
    int			 makeDefaultSelection
    );

void vfilechsrAddFilterByProcScribed(
    vfilechsr		*fileChooser,
    const vname		*id,
    vscribe		*title,
    vfilechsrFilterFunc	 proc,
    int			 makeDefaultSelection
    );

void vfilechsrAddFilterByProc(
    vfilechsr		*fileChooser,
    const vname		*id,
    const vchar		*title,
    vfilechsrFilterFunc  proc,
    int			 makeDefaultSelection
    );

void vfilechsrRemoveFilter(
    vfilechsr		*fileChooser,
    const vname		*id
    );

void vfilechsrRemoveFilters(
    vfilechsr		*fileChooser,
    const vname		*id,
    ...
    );

void vfilechsrSetActiveFilter(
    vfilechsr		*fileChooser,
    const vname		*id
    );

void vfilechsrSetDefaultExtension(
    vfilechsr		*fileChooser,
    const vchar		*extenion
    );

void vfilechsrSetDefaultExtensionScribed(
    vfilechsr		*fileChooser,
    vscribe		*extension
    );


/* File Chooser attribute access */

vfilechsrClass *vfilechsrGetClass(
    vfilechsr		*fileChooser
    );

vtextitem *vfilechsrGetTextEntry(
    vfilechsr		*fileChooser
    );

vfsPath *vfilechsrGetDirectory(
    vfilechsr		*fileChooser
    );

vfsPath *vfilechsrGetNthDirectory(
    vfilechsr		*fileChooser,
    int			 index
    );

int vfilechsrGetSelectedDirectoryIndex(
    vfilechsr		*fileChooser
    );

vfsPath **vfilechsrGetHistoryListCopy(
    vfilechsr		*fileChooser
    );

vfilechsrApplyFunc vfilechsrGetApply(
     vfilechsr		*fileChooser
    );

void *vfilechsrGetData(
    vfilechsr		*fileChooser
    );

int vfilechsrGetType(
    vfilechsr		*fileChooser
    );

int vfilechsrGetSelection(
    vfilechsr		*fileChooser
    );

int vfilechsrGetMinListWidth(
    vfilechsr		*fileChooser
    );

short vfilechsrGetMaxHistoryCount(
    vfilechsr		*fileChooser
    );

vbool vfilechsrIsConfirmOverwrite(
    vfilechsr		*fileChooser
    );

int vfilechsrPrefersNative(
    vfilechsr		*fileChooser
    );

unsigned int vfilechsrGetChoiceOptions(
    vfilechsr		*fileChooser
    );

unsigned int vfilechsrGetOptions(
    vfilechsr		*fileChooser
    );

const vname *vfilechsrGetActiveFilter(
    vfilechsr		*fileChooser
    );

const vchar *vfilechsrGetActiveFilterExtension(
    vfilechsr		*fileChooser
    );

const vname *vfilechsrGetActiveViewBy(
    vfilechsr		*fileChooser
    );

unsigned vfilechsrHasFilter(
    vfilechsr		*fileChooser,
    const vname     *id
    );

const vchar *vfilechsrGetDefaultExtension(
    vfilechsr		*fileChooser
    );

/* File chooser Entry attribute access */

const vchar *vfilechsrGetEntryName(  
    vfilechsrEntry	*entry
    );

const vfsInfo *vfilechsrGetEntryInfo(  
    vfilechsrEntry	*entry
    );

vbool vfilechsrGetEntryCanRead(  
    vfilechsrEntry	*entry

    );

vbool vfilechsrGetEntryCanWrite(  
    vfilechsrEntry	*entry
    );

vfsPath *vfilechsrGetEntryPath(
    vfilechsrEntry	*entry
    );

/* Other Routines */

vconfirm *vfilechsrGetConfirm(
    vfilechsr		*fileChooser
    );

vdialog *vfilechsrGetDialog(
    vfilechsr		*fileChooser
    );

vmenubar *vfilechsrGetMenuBar(
    vfilechsr		*fileChooser
    );

vchar vfilechsrGetDefaultPatternListDelimiter(
    void
    );

void vfilechsrMakeFilterSpecRootResource(
    vresource		 resource,
    int			 clean
    );
    

/*
 * * * * * * * * * * PRIVATE CONSTANT DEFINITIONS * * * * * * * * * *
 */

#define _vfilechsrHISTORY_LIST	        1
#define _vfilechsrMARKED_LIST		2
#define _vfilechsrSUFFIX_LEN		10
#define _vfilechsrFILE_ENTRY_SIZE	10
#define _vfilechsrLIST_SPACING		5


/*
 * Global file chooser strings
 */

enum {
    _vfilechsr_ViewName,
    _vfilechsr_FiltersMenuName,
    _vfilechsr_FileTypes,
    _vfilechsr_Unix,
    _vfilechsr_DOS,
    _vfilechsr_NT,
    _vfilechsr_Macintosh,
    _vfilechsr_OS2,
    _vfilechsr_VMS,
    _vfilechsr_CaseInsenstive,
    _vfilechsr_Delimiter,
    _vfilechsr_DefExtension,
    _vfilechsr_FilterSpecsId,
    _vfilechsr_PatternSupplement,
    _vfilechsr_Count
};

/*
 * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * *
 */

struct vfilechsrEntry {
    vchar	       *name;
    vfsInfo             info;
    vbool		canRead;
    vbool		canWrite;
    vfsPath	        *path;
};

typedef struct vfilechsrDirectory {
    vlist   	    	    	*list;
    vlistSelection  	    	*selection;
    vlistview	    	    	*currentView;
    vfilechsr	    	    	*fileChooser;
    vfsPath			*path;
    vtimestamp			modified;
    vfilechsrEntry		*entries;
    int				numEntries;
    int				entrySize;
    struct vfilechsrDirectory	*next;
} vfilechsrDirectory;


typedef struct _vfilechsrFilterPair {
  const vname		*id;
  vstr			*title;
  unsigned int		 flags;
  const void		*raw;
  const void		*ext;
  const void		*supplement;
  union {
    const void		*data;
    vfilechsrFilterFunc  proc;
  }u;
}_vfilechsrFilterPair;


typedef struct _vfilechsrFilterList {
  unsigned short 	count;
  unsigned short 	type;
  _vfilechsrFilterPair  pairs[1];
}_vfilechsrFilterList;


struct vfilechsr {
    vconfirm		confirm;
    vbyte		type;
    vbyte		selection;
    vbool		doConfirm;
    int			minListWidth;

    vdict		views;
    const vname		*viewBy;

    vfilechsrDirectory  *currDir;
    vfilechsrDirectory	*dirList;

    int			markEntries;
    short		histEntries;
    short		maxHistCount;

    int			numLists;
    vlistview		*listview[vfilechsrMAX_NUM_LISTS];
    vdialogItem		*title[vfilechsrMAX_NUM_LISTS];
    int			naturalListSize;

    vcontrol		*hierControl;
    vtextitem		*pathEntry;
    vtextitem		*nameItem;
    vmenubar		*menuBar;
    vbutton		*leftArrow;
    vbutton		*rightArrow;
    vcontrol		*readonlyControl;

    vfilechsrApplyFunc	apply;

    unsigned int	  doSys:1;
    unsigned int	  doSysOverride:1;
    unsigned int	  isBlocking:1;
    unsigned int	  usingOK:1;
    unsigned int	  dirty:1;
    unsigned int	  volatileIsDir:1;
    unsigned int	  unInited:1;
    unsigned int	  entryUpdateOn:1;
    unsigned int	  ignoreSelNotify:1;
    short		  defaultPairIndex;
    short		  customPairIndex;
    unsigned int	  options;
    unsigned int	  choiceOptions;
    const void 	         *sysData;
    _vfilechsrFilterPair *defaultPair;
    _vfilechsrFilterList *filterPairs;
    vmenu		 *filterMenu;
    const vname		 *choiceTag;
    vstr		 *ext;
    vbuttonNoteProc	  hiddenNotify;
    int			  volatileRow;
};

/*
 * File Chooser Class definition
 */

#define vfilechsrCLASS(SUPER, FILECHSR, NOTIFY)				      \
    vconfirmCLASS(SUPER, FILECHSR, NOTIFY);				      \
    vclassMETHOD_RET(vfilechsrFILTER, vbool,				      \
		     (FILECHSR *fileChooser, vfilechsrEntry *entry));	      \
    vclassMETHOD_RET(vfilechsrFILTER_BY_NAME, vbool,			      \
		     (FILECHSR *fileChooser, const vchar *entry));	      \
    vclassMETHOD_RET(vfilechsrCOMPARE_FOR_VIEW, int,			      \
		     (FILECHSR *fileChooser, const vchar *first,	      \
		      const vchar *second));				      \
    vclassMETHOD_RET(vfilechsrHOOK_APPLY_FILE, int,			      \
		     (FILECHSR *fileChooser, vfsPath *path));		      \
    vclassMETHOD(vfilechsrSET_DIRECTORY,				      \
		 (FILECHSR *fileChooser, const vfsPath *path));		      \
    vclassMETHOD(vfilechsrSHIFT_DIRECTORY,				      \
		 (FILECHSR *fileChooser, int direction));		      \
    vclassMETHOD(vfilechsrCOMPLETE,					      \
		 (FILECHSR *fileChooser));				      \
    vclassMETHOD(vfilechsrADD_VIEW_BY,					      \
		 (FILECHSR *fileChooser, const vchar *viewByName,	      \
		  vfilechsrCompareFunc compareFunc));			      \
    vclassMETHOD(vfilechsrREMOVE_VIEW_BY,				      \
		 (FILECHSR *fileChooser, const vchar *viewByName))

struct vfilechsrClass {
    vfilechsrCLASS(vfilechsrClass, vfilechsr, vconfirmHookProc);
};


/*
 * * * * * * * * * * PRIVATE FUNCTION PROTOTYPES * * * * * * * * * *
 */

void _vfilechsrSortDirectoryList(vfilechsr *fileChooser, vlist *list);

/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * *
 */

#define vfilechsrCreate() \
	(vfilechsrCreateOfClass(vfilechsrGetDefaultClass()))

#define vfilechsrCreateOfClass(c)	\
	((vfilechsr *) vconfirmCreateOfClass((vconfirmClass *) (c)))

#define vfilechsrGetClass(f)	((vfilechsrClass*) vconfirmGetClass \
				 (vfilechsrGetConfirm(f)))

#define vfilechsrGetData(f)		vconfirmGetData(vfilechsrGetConfirm(f))
#define vfilechsrGetType(f)		((f)->type)
#define vfilechsrGetSelection(f)	((f)->selection)
#define vfilechsrGetOpenNotify(f)	((f)->notify)
#define vfilechsrGetMinListWidth(f)	((f)->minListWidth)
#define vfilechsrGetDirectory(f)	((f)->currDir->path)
#define vfilechsrDestroy(f)		vconfirmDestroy(vfilechsrGetConfirm(f))
#define vfilechsrGetConfirm(f)		vportBASE_OBJECT((f), confirm)
#define vfilechsrGetDialog(f)		\
	(vconfirmGetDialog(vfilechsrGetConfirm(f)))
#define vfilechsrGetMenuBar(f)		((f)->menuBar)
#define vfilechsrGetTextEntry(f)	((f)->pathEntry)
#define vfilechsrGetApply(f)		((f)->apply)
#define vfilechsrGetMaxHistoryCount(f)  ((f)->maxHistCount)
#define vfilechsrGetChoiceOptions(f)    ((f)->choiceOptions)
#define vfilechsrGetOptions(f)          ((f)->options)
#define vfilechsrGetDefaultExtension(f)  ((const vchar*)(f)->ext)
#define vfilechsrGetActiveFilter(f) 	\
	((f)->defaultPair ? (f)->defaultPair->id : (const vname *)NULL)
#define vfilechsrGetActiveFilterExtension(f) \
        ((f)->defaultPair ? (const vchar*)((f)->defaultPair->ext) : (const vchar*)NULL)
#define vfilechsrGetActiveViewBy(f) 	\
	((f)->viewBy)

#define vfilechsrSetConfirmOverwrite(f,d)	((f)->doConfirm = ((d) != 0))
#define vfilechsrIsConfirmOverwrite(f)		((f)->doConfirm)
#define vfilechsrSetPreferNative(f,b)		((f)->doSys = ((b) != 0))
#define vfilechsrPrefersNative(f)		((f)->doSys || (f)->doSysOverride)
#define vfilechsrSetOverridePreferNative(f,b)	((f)->doSysOverride = ((b) != 0))

#define vfilechsrGetEntryName(e)	((e)->name)
#define vfilechsrGetEntryInfo(e)	(&(e)->info)
#define vfilechsrGetEntryCanRead(e)	((e)->canRead)
#define vfilechsrGetEntryCanWrite(e)	((e)->canWrite)
#define vfilechsrGetEntryPath(e)	((e)->path)


#define vfilechsrSetPromptName(f,p) \
	vfilechsrSetPromptNameScribed((f), (p) ? vcharScribe(p) : (vscribe *)NULL)

#define vfilechsrSetDocumentName(f,d) \
	vfilechsrSetDocumentNameScribed((f), (d) ? vcharScribe(d) : (vscribe *)NULL)

#define vfilechsrAddFilterByPattern(f,_id,t,p,b) \
	vfilechsrAddFilterByPatternScribed((f), (_id), \
					   (t) ? vcharScribe(t) : (vscribe *)NULL, \
					   vcharScribe(p), (b))
#define vfilechsrAddFilterByProc(f,_id,t,p,b) \
	vfilechsrAddFilterByProcScribed((f), (_id), \
					(t) ? vcharScribe(t) : (vscribe *)NULL, \
					(p), (b))

#define vfilechsrSetDefaultExtension(f,x) \
        vfilechsrSetDefaultExtensionScribed((f), (x) ? vcharScribe(x) : (vscribe *)NULL)

#define vfilechsrPlace(f, b, mx, my) \
  vdialogPlace(vfilechsrGetDialog(f), b, mx, my)

/*
 * * * * * * * * * * PRIVATE FUNCTION MESSAGE DEFINITIONS * * * * * * * * * *
 */

#define vfilechsrSetData(f,d)		\
	vclassSend(vfilechsrGetClass(f), vwindowSET_DATA, (f, d))

#define vfilechsrSetDirectory(f, p)     \
	vclassSend(vfilechsrGetClass(f), vfilechsrSET_DIRECTORY, (f, p))

#define vfilechsrShiftDirectory(f, p)   \
	vclassSend(vfilechsrGetClass(f), vfilechsrSHIFT_DIRECTORY, (f, p))

#define vfilechsrAddViewBy(f,n,c)       \
	vclassSend(vfilechsrGetClass(f), vfilechsrADD_VIEW_BY, (f,n,c))

#define vfilechsrRemoveViewBy(f,n)      \
	vclassSend(vfilechsrGetClass(f), vfilechsrREMOVE_VIEW_BY, (f,n))

#define vfilechsrOpen(c)		\
	vclassSend(vfilechsrGetClass(c), vwindowOPEN, (c))

#define vfilechsrClose(c)		\
	vclassSend(vfilechsrGetClass(c), vwindowCLOSE, (c))

#define vfilechsrComplete(f)       	\
	vclassSend(vfilechsrGetClass(f), vfilechsrCOMPLETE, (f))

#define vfilechsrSetTitle(f,t) 		\
	vfilechsrSetTitleScribed((f), (t) ? vcharScribe(t) : (vscribe *)NULL)

#define vfilechsrSetTitleScribed(f,s) 	\
	vclassSend(vfilechsrGetClass(f), vwindowSET_TITLE_SCRIBED, (f, (s)))

#define vfilechsrSetLeader(f,d) 	\
	vclassSend(vfilechsrGetClass(f), vwindowSET_LEADER, (f, (d)))


/*
 * * * * * * * * * FILE CHOOSER GLOBAL VARIABLES * * * * * * * * * *
 */

extern vportLINK const vchar 		*_vfilechsrPredefs[];

vportEND_CPLUSPLUS_EXTERN_C


#endif /* #ifndef vfilechsrINCLUDED */


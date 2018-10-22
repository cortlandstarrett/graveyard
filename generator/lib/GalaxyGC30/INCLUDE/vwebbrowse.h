/* $Id: vwebbrowse.h,v 1.7 1997/11/06 20:01:26 robert Exp $ */

/* -----------------------------------------------------------------------
 *
 *  vwebbrowse.h
 *
 *  Programming interface to the root vwebbrowse class
 *
 *  (c) Copyright Visix Software
 *  All rights reserved
 *
 * -----------------------------------------------------------------------
 */

#ifndef vwebbrowseINCLUDED
#define vwebbrowseINCLUDED	1

#ifndef  vportINCLUDED
#include <vport.h>
#endif 

#ifndef  vdialogINCLUDED
#include vdialogHEADER
#endif

#ifndef  vurlINCLUDED
#include vurlHEADER
#endif

#ifndef  vprocessINCLUDED
#include vprocessHEADER
#endif

#ifndef  vmutexINCLUDED
#include vmutexHEADER
#endif


vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * * * * * * * * * * PUBLIC GLOBAL VARIABLES * * * * * * * * * *
 */

/*
 * * * * * * * * * * PUBLIC CONSTANT DEFINITIONS * * * * * * * * 
 */

enum
{
  vwebbrowseEventCANNOT_LAUNCH,
  vwebbrowseEventGOTO_URL_SUCCESS,
  vwebbrowseEventGOTO_URL_FAILURE,
  vwebbrowseEventCANNOT_CONTACT,
  vwebbrowseEventNEXT_EVENT
};

enum
{
  vwebbrowseProcessEventSTARTED,
  vwebbrowseProcessEventCANNOT_START,
  vwebbrowseProcessEventNEXT_EVENT
};

/*
 * * * * * * * * * * PUBLIC TYPE DEFINITIONS * * * * * * * * * *
 */

typedef struct	vwebbrowse		       	vwebbrowse;
typedef struct	vwebbrowseClass			vwebbrowseClass;       
typedef 	int				vwebbrowseEvent;

typedef struct	vwebbrowseDefault		vwebbrowseDefault;
typedef struct	vwebbrowseNetscape		vwebbrowseNetscape;
typedef struct	vwebbrowseExplorer		vwebbrowseExplorer;

typedef struct	vwebbrowseDefaultClass		vwebbrowseDefaultClass;
typedef struct	vwebbrowseNetscapeClass		vwebbrowseNetscapeClass;
typedef struct	vwebbrowseExplorerClass		vwebbrowseExplorerClass;

typedef struct	vwebbrowseProcess		vwebbrowseProcess;
typedef struct	vwebbrowseProcessClass		vwebbrowseProcessClass;       
typedef 	int				vwebbrowseProcessEvent;

typedef struct	vwebbrowseNetscapeProcess	vwebbrowseNetscapeProcess;
typedef struct	vwebbrowseNetscapeProcessClass	vwebbrowseNetscapeProcessClass; 

typedef struct	vwebbrowseExplorerProcess	vwebbrowseExplorerProcess;
typedef struct	vwebbrowseExplorerProcessClass	vwebbrowseExplorerProcessClass; 

typedef void 	(*vwebbrowseNoteProc)(
    vwebbrowse   			*browser,
    vwebbrowseEvent			 event
    );

typedef void 	(*vwebbrowseProcessNoteProc)(
    vwebbrowseProcess   			*browserProcess,
    vwebbrowseProcessEvent			 event
    );


/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * 
 */

/*
 * vwebbrowse, Base Class
 */

void vwebbrowseStartup(
    void
    );

vwebbrowseClass *vwebbrowseGetDefaultClass(
    void
    );

vwebbrowseClass *vwebbrowseGetClass(
    vwebbrowse		*browser
    );

vwebbrowse *vwebbrowseCreateOfClass(
    vwebbrowseClass	*browserClass
    );

vwebbrowse *vwebbrowseCreate(
    void
    );

void vwebbrowseInitOfClass(
    vwebbrowse		*browser,
    vwebbrowseClass	*clas
    );

void vwebbrowseInit(
    vwebbrowse		*browser
    );

vwebbrowse *vwebbrowseDestroy(
    vwebbrowse		*browser
    );

vinstance *vwebbrowseGetInstance(
    vwebbrowse		*browser
    );

vbool vwebbrowseStart(
    vwebbrowse		*browser,
    vurl		*url
    );

vbool vwebbrowseGotoURL(
    vwebbrowse		*browser,
    vurl		*url
    );

void vwebbrowseRaise(
    vwebbrowse		*browser
    );

void vwebbrowseNotify(
    vwebbrowse		*browser,
    vwebbrowseEvent	 event
    );

void vwebbrowseSetAutoRaise(
    vwebbrowse		*browser,
    vbool		 yesNo
    );

vbool vwebbrowseIsAutoRaise(
    vwebbrowse		*browser
    );

void vwebbrowseSetName(
    vwebbrowse		*browser,
    const vchar		*name
    );

void vwebbrowseSetNameScribed(
    vwebbrowse		*browser,
    vscribe		*scribe
    );

const vchar *vwebbrowseGetName(
    vwebbrowse		*browser
    );

void vwebbrowseSetNotify(
    vwebbrowse		*browser,
    vwebbrowseNoteProc	 noteProc
    );

vwebbrowseNoteProc vwebbrowseGetNotify(
    vwebbrowse		*browser
    );

vwebbrowseProcess *vwebbrowseGetProcess(
    vwebbrowse		*browser
    );

void vwebbrowseSetProcessOwned(
    vwebbrowse		*browser,
    vwebbrowseProcess     *process
    );


/*
 * vwebbrowseNetscape
 */

void vwebbrowseStartupNetscape(
    void
    );

vwebbrowseNetscapeClass *vwebbrowseGetDefaultNetscapeClass(
    void
    );

vwebbrowseNetscapeClass *vwebbrowseGetNetscapeClass(
    vwebbrowseNetscape		*browser
    );

vwebbrowseNetscape *vwebbrowseCreateNetscapeOfClass(
    vwebbrowseNetscapeClass	*browserClass
    );

vwebbrowseNetscape *vwebbrowseCreateNetscape(
    void
    );

void vwebbrowseInitNetscapeOfClass(
    vwebbrowseNetscape		*browser,
    vwebbrowseNetscapeClass	*clas
    );

void vwebbrowseInitNetscape(
    vwebbrowseNetscape		*browser
    );

vwebbrowseNetscape *vwebbrowseDestroyNetscape(
    vwebbrowseNetscape		*browser
    );

vwebbrowse *vwebbrowseGetNetscapeWebbrowse(
    vwebbrowseNetscape		*browser
    );

/*
 * vwebbrowseExplorer
 */

void vwebbrowseStartupExplorer(
    void
    );

vwebbrowseExplorerClass *vwebbrowseGetDefaultExplorerClass(
    void
    );

vwebbrowseExplorerClass *vwebbrowseGetExplorerClass(
    vwebbrowseExplorer		*browser
    );

vwebbrowseExplorer *vwebbrowseCreateExplorerOfClass(
    vwebbrowseExplorerClass	*browserClass
    );

vwebbrowseExplorer *vwebbrowseCreateExplorer(
    void
    );

void vwebbrowseInitExplorerOfClass(
    vwebbrowseExplorer		*browser,
    vwebbrowseExplorerClass	*clas
    );

void vwebbrowseInitExplorer(
    vwebbrowseExplorer		*browser
    );

vwebbrowseExplorer *vwebbrowseDestroyExplorer(
    vwebbrowseExplorer		*browser
    );

vwebbrowse *vwebbrowseGetExplorerWebbrowse(
    vwebbrowseExplorer		*browser
    );

/*
 * vwebbrowseDefault
 */

void vwebbrowseStartupDefault(
    void
    );

vwebbrowseDefaultClass *vwebbrowseGetDefaultDefaultClass(
    void
    );

vwebbrowseDefaultClass *vwebbrowseGetDefaultWebbrowseClass(
    vwebbrowseDefault		*browser
    );

vwebbrowseDefault *vwebbrowseCreateDefaultOfClass(
    vwebbrowseDefaultClass	*browserClass
    );

vwebbrowseDefault *vwebbrowseCreateDefault(
    void
    );

void vwebbrowseInitDefaultOfClass(
    vwebbrowseDefault		*browser,
    vwebbrowseDefaultClass	*clas
    );

void vwebbrowseInitDefault(
    vwebbrowseDefault		*browser
    );

vwebbrowseDefault *vwebbrowseDestroyDefault(
    vwebbrowseDefault		*browser
    );

vwebbrowse *vwebbrowseGetDefaultWebbrowse(
    vwebbrowseDefault		*browser
    );

/* 
 * vwebbrowseProcess	
 */
void vwebbrowseStartupProcess(
    void
    );

vwebbrowseProcessClass *vwebbrowseGetDefaultProcessClass(
    void
    );

vwebbrowseProcessClass *vwebbrowseGetProcessClass(
    vwebbrowseProcess		*browserProcess
    );

vwebbrowseProcess *vwebbrowseCreateProcessOfClass(
    vwebbrowseProcessClass	*browserProcessClass
    );

vwebbrowseProcess *vwebbrowseCreateProcess(
    void
    );

void vwebbrowseInitProcessOfClass(
    vwebbrowseProcess		*browserProcess,
    vwebbrowseProcessClass	*clas
    );

void vwebbrowseInitProcess(
    vwebbrowseProcess		*browserProcess
    );

void vwebbrowseDestroyProcess(
    vwebbrowseProcess		*browserProcess
    );

vprocess *vwebbrowseGetProcessProcess(
    vwebbrowseProcess		*browserProcess
    );

vbool vwebbrowseStartProcess(
    vwebbrowseProcess		*browserProcess
    );

void vwebbrowseNotifyProcess(
    vwebbrowseProcess		*browserProcess,
    vwebbrowseProcessEvent	 event
    );

void vwebbrowseSetProcessStartupURL(
    vwebbrowseProcess		*browserProcess,
    vurl			*url
    );

vurl *vwebbrowseGetProcessStartupURL(
    vwebbrowseProcess		*browserProcess
    );

void vwebbrowseSetProcessWebbrowse(
    vwebbrowseProcess		*browserProcess,
    vwebbrowse			*browser
    );

vwebbrowse *vwebbrowseGetProcessWebbrowse(
    vwebbrowseProcess		*browserProcess
    );

void vwebbrowseSetProcessNotify(
    vwebbrowseProcess		*browserProcess,
    vwebbrowseProcessNoteProc	 noteProc
    );

vwebbrowseProcessNoteProc vwebbrowseGetProcessNotify(
    vwebbrowseProcess		*browserProcess
    );

/*
 * vwebbrowseNetscapeProcess
 */

vwebbrowseNetscapeProcessClass *vwebbrowseGetDefaultNetscapeProcessClass(
    void
    );

vwebbrowseNetscapeProcessClass *vwebbrowseGetNetscapeProcessClass(
    vwebbrowseNetscapeProcess		*browserProcess
    );

vwebbrowseNetscapeProcess *vwebbrowseCreateNetscapeProcessOfClass(
    vwebbrowseNetscapeProcessClass	*browserProcessClass
    );

vwebbrowseNetscapeProcess *vwebbrowseCreateNetscapeProcess(
    void
    );

void vwebbrowseInitNetscapeProcessOfClass(
    vwebbrowseNetscapeProcess		*browserProcess,
    vwebbrowseNetscapeProcessClass	*clas
    );

void vwebbrowseInitNetscapeProcess(
    vwebbrowseNetscapeProcess		*browserProcess
    );

void vwebbrowseDestroyNetscapeProcess(
    vwebbrowseNetscapeProcess		*browserProcess
    );

vwebbrowseProcess *vwebbrowseGetNetscapeProcessProcess(
    vwebbrowseNetscapeProcess		*browserProcess
    );

vbool vwebbrowseStartNetscapeProcess(
    vwebbrowseNetscapeProcess		*browserProcess
    );

/*
 * vwebbrowseExplorerProcess
 */

vwebbrowseExplorerProcessClass *vwebbrowseGetDefaultExplorerProcessClass(
    void
    );

vwebbrowseExplorerProcessClass *vwebbrowseGetExplorerProcessClass(
    vwebbrowseExplorerProcess		*browserProcess
    );

vwebbrowseExplorerProcess *vwebbrowseCreateExplorerProcessOfClass(
    vwebbrowseExplorerProcessClass	*browserProcessClass
    );

vwebbrowseExplorerProcess *vwebbrowseCreateExplorerProcess(
    void
    );

void vwebbrowseInitExplorerProcessOfClass(
    vwebbrowseExplorerProcess		*browserProcess,
    vwebbrowseExplorerProcessClass	*clas
    );

void vwebbrowseInitExplorerProcess(
    vwebbrowseExplorerProcess		*browserProcess
    );

void vwebbrowseDestroyExplorerProcess(
    vwebbrowseExplorerProcess		*browserProcess
    );

vwebbrowseProcess *vwebbrowseGetExplorerProcessProcess(
    vwebbrowseExplorerProcess		*browserProcess
    );

vbool vwebbrowseStartExplorerProcess(
    vwebbrowseExplorerProcess		*browserProcess
    );


/*
 * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * *
 */

typedef struct	_vwebbrowseHandle		_vwebbrowseHandle;
typedef struct	_vwebbrowseBrowserInfo		_vwebbrowseBrowserInfo;

struct vwebbrowse 
{
    vinstance     	 instance;
    const vchar		*name;
    vwebbrowseProcess	*process;
    unsigned short	 flags;
    vrect		*rect;
    vwebbrowseNoteProc	 notify;
    _vwebbrowseHandle	*handle;
};

#define vwebbrowseCLASS(SUPER, BROWSER)				              \
    vinstanceCLASS(SUPER, BROWSER);				              \
    vclassMETHOD_RET(vwebbrowseSTART, vbool, 				      \
		     (BROWSER *browser, vurl *url));			      \
    vclassMETHOD_RET(vwebbrowseGOTO_URL, vbool, 			      \
		     (BROWSER *browser, vurl *url));			      \
    vclassMETHOD(vwebbrowseRAISE, (BROWSER *browser)); 			      \
    vclassMETHOD(vwebbrowseNOTIFY, (BROWSER *browser, 			      \
				    vwebbrowseEvent event));		      \
    vclassMETHOD(vwebbrowseSET_PROCESS_OWNED, (BROWSER *browser, 	      \
				       vwebbrowseProcess *process)); 	      \
    vclassMETHOD(vwebbrowseSET_AUTO_RAISE, (BROWSER *browser, vbool yesNo));  \
    vclassMETHOD(vwebbrowseSET_NAME_SCRIBED, 				      \
		 (BROWSER *browser, vscribe *scribe)); 			      \
    vclassMETHOD(vwebbrowseSET_NOTIFY, (BROWSER *browser, 		      \
				      vwebbrowseNoteProc noteProc))


struct vwebbrowseClass {
    vwebbrowseCLASS(vwebbrowseClass, vwebbrowse);
};

enum 
{
    _vwebbrowseAUTO_RAISE		= 0x0001,
    _vwebbrowseSYSTEM_DEFAULT		= 0x0002,
    _vwebbrowseSTARTED		        = 0x0004,
    _vwebbrowseNAME_OWNED		= 0x0008,
    /*
     * This flag is used only in netscape.c
     */
    _vwebbrowseJUST_SENT_COMMAND	= 0x0010 
};

/*
 * vwebbrowseNetscape
 */

struct vwebbrowseNetscape
{
    vwebbrowse		 browser;
    _vwebbrowseBrowserInfo *info;
};

#define vwebbrowseNetscapeCLASS(SUPER, BROWSER)			              \
    vwebbrowseCLASS(SUPER, BROWSER)

struct vwebbrowseNetscapeClass {
    vwebbrowseNetscapeCLASS(vwebbrowseNetscapeClass, vwebbrowseNetscape);
};


/*
 * vwebbrowseExplorer
 */

struct vwebbrowseExplorer
{
    vwebbrowse		 browser;
    _vwebbrowseBrowserInfo *info;
};

#define vwebbrowseExplorerCLASS(SUPER, BROWSER)			              \
    vwebbrowseCLASS(SUPER, BROWSER)

struct vwebbrowseExplorerClass {
    vwebbrowseExplorerCLASS(vwebbrowseExplorerClass, vwebbrowseExplorer);
};


/*
 * vwebbrowseDefault
 */

struct vwebbrowseDefault
{
    vwebbrowse		 browser;
    vwebbrowse		*defaultBrowser;
};

#define vwebbrowseDefaultCLASS(SUPER, BROWSER)			              \
    vwebbrowseCLASS(SUPER, BROWSER)

struct vwebbrowseDefaultClass {
    vwebbrowseDefaultCLASS(vwebbrowseDefaultClass, vwebbrowseDefault);
};

/* 
 * vwebbrowseProcess
 */

struct vwebbrowseProcess 
{
    vprocess    	 	 process;
    vwebbrowse			*browser;
    vwebbrowseProcessNoteProc    notify;
    vurl			*url;

    unsigned int                 seconds;
    vevent                      *event;
};
#define vwebbrowseProcessCLASS(SUPER, PROCESS)                                \
    vprocessCLASS(SUPER, PROCESS);                                            \
    vclassMETHOD(vwebbrowseNOTIFY_PROCESS,                                    \
                 (PROCESS *process, vwebbrowseProcessEvent event));           \
    vclassMETHOD(vwebbrowseSET_PROCESS_WEBBROWSE,                             \
                 (PROCESS *process, vwebbrowse *browser));                    \
    vclassMETHOD(vwebbrowseSET_PROCESS_NOTIFY,                                \
                 (PROCESS *process, vwebbrowseProcessNoteProc noteProc));     \
    vclassMETHOD(vwebbrowseSET_PROCESS_STARTUP_URL,	                      \
                 (PROCESS *process, vurl *url))

struct vwebbrowseProcessClass {
vwebbrowseProcessCLASS(vwebbrowseProcessClass, vwebbrowseProcess); };

struct vwebbrowseNetscapeProcess 
{
    vwebbrowseProcess    	 	 process;
};

#define vwebbrowseNetscapeProcessCLASS(SUPER, PROCESS)			      \
    vprocessCLASS(SUPER, PROCESS)

struct vwebbrowseNetscapeProcessClass {
    vwebbrowseProcessCLASS(vwebbrowseNetscapeProcessClass,		      \
			 vwebbrowseNetscapeProcess);
};


struct vwebbrowseExplorerProcess 
{
    vwebbrowseProcess    	 	 process;
};

#define vwebbrowseExplorerProcessCLASS(SUPER, PROCESS)			      \
    vprocessCLASS(SUPER, PROCESS)

struct vwebbrowseExplorerProcessClass {
    vwebbrowseProcessCLASS(vwebbrowseExplorerProcessClass,		      \
			 vwebbrowseExplorerProcess);
};


/*
 * * * * * * * * * * PRIVATE FUNCTION PROTOTYPES * * * * * * * * * *
 */

/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * *
 */
#define vwebbrowseGetInstance(b)	vportBASE_OBJECT(b, instance)
#define vwebbrowseGetClass(b)						      \
    ((vwebbrowseClass*)vinstanceGetClass(vwebbrowseGetInstance(b)))
#define vwebbrowseCreateOfClass(c) 					      \
    ((vwebbrowse *)vinstanceCreateOfClass((vinstanceClass*)(c)))
#define vwebbrowseCreate() 						      \
    vwebbrowseCreateOfClass(vwebbrowseGetDefaultClass())
#define vwebbrowseDestroy(b)						      \
    vinstanceDestroy(vwebbrowseGetInstance(b))
#define vwebbrowseInitOfClass(b, c) 					      \
    vinstanceInitOfClass(vwebbrowseGetInstance(b), (vinstanceClass*)(c))
#define vwebbrowseInit(b)					              \
    vwebbrowseInitOfClass(b, vwebbrowseGetDefaultClass())

#define vwebbrowseGetProcess(b)	(b)->process
#define vwebbrowseGetName(b)	(b)->name
#define vwebbrowseGetNotify(b)	(b)->notify
#define vwebbrowseIsAutoRaise(b)					      \
    ((((b)->flags & _vwebbrowseAUTO_RAISE) ? vTRUE : vFALSE))
#define vwebbrowseSetName(b, n)	vwebbrowseSetNameScribed(b, vcharScribe(n))

#define vwebbrowseGetNetscapeWebbrowse(b)	vportBASE_OBJECT((b), browser)
#define vwebbrowseGetNetscapeClass(b)	((vwebbrowseNetscapeClass*)	      \
    vwebbrowseGetClass(vwebbrowseGetNetscapeWebbrowse(b)))
#define vwebbrowseCreateNetscapeOfClass(c) 				      \
    ((vwebbrowseNetscape *)vwebbrowseCreateOfClass((vwebbrowseClass*)(c)))
#define vwebbrowseCreateNetscape() 					      \
    vwebbrowseCreateNetscapeOfClass(vwebbrowseGetDefaultNetscapeClass())
#define vwebbrowseDestroyNetscape(b)					      \
    vwebbrowseDestroy(vwebbrowseGetNetscapeWebbrowse(b))
#define vwebbrowseInitNetscapeOfClass(b, c)				      \
    vwebbrowseInitOfClass(vwebbrowseGetNetscapeWebbrowse(b), 		      \
			  (vwebbrowseClass*)(c))
#define vwebbrowseInitNetscape(b)				              \
    vwebbrowseInitNetscapeOfClass(b, vwebbrowseGetDefaultNetscapeClass())

#define vwebbrowseGetExplorerWebbrowse(b)	vportBASE_OBJECT(b, browser)
#define vwebbrowseGetExplorerClass(b)	((vwebbrowseExplorerClass*)	      \
    vwebbrowseGetClass(vwebbrowseGetExplorerWebbrowse(b)))
#define vwebbrowseCreateExplorerOfClass(c) 				      \
    ((vwebbrowseExplorer *)vwebbrowseCreateOfClass((vwebbrowseClass*)(c)))
#define vwebbrowseCreateExplorer() 					      \
    vwebbrowseCreateExplorerOfClass(vwebbrowseGetDefaultExplorerClass())
#define vwebbrowseDestroyExplorer(b)					      \
    vwebbrowseDestroy(vwebbrowseGetExplorerWebbrowse(b))
#define vwebbrowseInitExplorerOfClass(b, c)				      \
    vwebbrowseInitOfClass(vwebbrowseGetExplorerWebbrowse(b), 		      \
			  (vwebbrowseClass*)(c))
#define vwebbrowseInitExplorer(b)				              \
    vwebbrowseInitExplorerOfClass(b, vwebbrowseGetDefaultExplorerClass())

#define vwebbrowseGetDefaultWebbrowse(b)	vportBASE_OBJECT(b, browser)
#define vwebbrowseGetDefaultWebbrowseClass(b) ((vwebbrowseDefaultClass*)      \
    vwebbrowseGetClass(vwebbrowseGetDefaultWebbrowse(b)))
#define vwebbrowseCreateDefaultOfClass(c) 			 	      \
    ((vwebbrowseDefault *)vwebbrowseCreateOfClass((vwebbrowseClass*)(c)))
#define vwebbrowseCreateDefault() 				 	      \
    vwebbrowseCreateDefaultOfClass(vwebbrowseGetDefaultDefaultClass())
#define vwebbrowseDestroyDefault(b)					      \
    vwebbrowseDestroy(vwebbrowseGetDefaultWebbrowse(b))
#define vwebbrowseInitDefaultOfClass(b, c)				      \
    vwebbrowseInitOfClass(vwebbrowseGetDefaultWebbrowse(b), 		      \
			  (vwebbrowseClass*)(c))
#define vwebbrowseInitDefault(b)				              \
    vwebbrowseInitDefaultOfClass(b, vwebbrowseGetDefaultDefaultClass())

#define vwebbrowseGetProcessProcess(b)	vportBASE_OBJECT(b, process)
#define vwebbrowseGetProcessClass(b)					      \
    ((vwebbrowseProcessClass*)vprocessGetClass(vwebbrowseGetProcessProcess(b)))
#define vwebbrowseCreateProcessOfClass(c) 				      \
    ((vwebbrowseProcess *)vprocessCreateOfClass((vprocessClass*)(c)))
#define vwebbrowseCreateProcess() 					      \
    vwebbrowseCreateProcessOfClass(vwebbrowseGetDefaultProcessClass())
#define vwebbrowseDestroyProcess(b)					      \
    vprocessDestroy(vwebbrowseGetProcessProcess(b))
#define vwebbrowseInitProcessOfClass(b, c) 				      \
    vprocessInitOfClass(vwebbrowseGetProcessProcess(b), (vprocessClass*)(c))
#define vwebbrowseInitProcess(b)				              \
    vwebbrowseInitProcessOfClass(b, vwebbrowseGetDefaultProcessClass())

#define vwebbrowseStartProcess(b)					      \
    vprocessStart(vwebbrowseGetProcessProcess(b))

#define vwebbrowseGetProcessStartupURL(b)		(b)->url
#define vwebbrowseGetProcessWebbrowse(b)		(b)->browser

#define vwebbrowseGetNetscapeProcessProcess(b)	vportBASE_OBJECT(b, process)
#define vwebbrowseGetNetscapeProcessClass(b)				      \
    ((vwebbrowseNetscapeProcessClass*)					      \
     vwebbrowseGetProcessClass(vwebbrowseGetProcessProcess(b)))
#define vwebbrowseCreateNetscapeProcessOfClass(c) 			      \
    ((vwebbrowseNetscapeProcess *)					      \
     vwebbrowseCreateProcessOfClass((vwebbrowseProcessClass*)(c)))
#define vwebbrowseCreateNetscapeProcess() 				      \
    vwebbrowseCreateNetscapeProcessOfClass(				      \
      vwebbrowseGetDefaultNetscapeProcessClass())
#define vwebbrowseDestroyNetscapeProcess(b)				      \
    vwebbrowseDestroyProcess(vwebbrowseGetNetscapeProcessProcess(b))
#define vwebbrowseInitNetscapeProcessOfClass(b, c) 			      \
    vwebbrowseInitProcessOfClass(vwebbrowseGetNetscapeProcessProcess(b),      \
			       (vwebbrowseProcessClass*)(c))
#define vwebbrowseInitNetscapeProcess(b)				      \
    vwebbrowseInitNetscapeProcessOfClass(b, 				      \
      vwebbrowseGetDefaultNetscapeProcessClass())

#define vwebbrowseGetExplorerProcessProcess(b)	vportBASE_OBJECT(b, process)
#define vwebbrowseGetExplorerProcessClass(b)				      \
    ((vwebbrowseExplorerProcessClass*)					      \
     vwebbrowseGetProcessClass(vwebbrowseGetProcessProcess(b)))
#define vwebbrowseCreateExplorerProcessOfClass(c) 			      \
    ((vwebbrowseExplorerProcess *)					      \
     vwebbrowseCreateProcessOfClass((vwebbrowseProcessClass*)(c)))
#define vwebbrowseCreateExplorerProcess() 				      \
    vwebbrowseCreateExplorerProcessOfClass(				      \
      vwebbrowseGetDefaultExplorerProcessClass())
#define vwebbrowseDestroyExplorerProcess(b)				      \
    vwebbrowseDestroyProcess(vwebbrowseGetExplorerProcessProcess(b))
#define vwebbrowseInitExplorerProcessOfClass(b, c) 			      \
    vwebbrowseInitProcessOfClass(vwebbrowseGetExplorerProcessProcess(b),      \
			       (vwebbrowseProcessClass*)(c))
#define vwebbrowseInitExplorerProcess(b)				      \
    vwebbrowseInitExplorerProcessOfClass(b, 				      \
      vwebbrowseGetDefaultExplorerProcessClass())

/*
 * * * * * * * * * * PRIVATE FUNCTION MESSAGE DEFINITIONS * * * * * * * * * *
 */

#define vwebbrowseStart(b, c)						      \
    vclassSend(vwebbrowseGetClass(b), vwebbrowseSTART, (b, c))
#define vwebbrowseGotoURL(b, u)						      \
    vclassSend(vwebbrowseGetClass(b), vwebbrowseGOTO_URL, (b, u))
#define vwebbrowseNotify(b, e)						      \
    vclassSend(vwebbrowseGetClass(b), vwebbrowseNOTIFY, (b, e))
#define vwebbrowseRaise(b)						      \
    vclassSend(vwebbrowseGetClass(b), vwebbrowseRAISE, (b))
#define vwebbrowseSetAutoRaise(d, b)					      \
    vclassSend(vwebbrowseGetClass(d), vwebbrowseSET_AUTO_RAISE, (d, b))
#define vwebbrowseSetNotify(b, n)				              \
    vclassSend(vwebbrowseGetClass(b), vwebbrowseSET_NOTIFY, (b, n))
#define vwebbrowseSetProcessOwned(b, p)				              \
    vclassSend(vwebbrowseGetClass(b), vwebbrowseSET_PROCESS_OWNED, (b, p))
#define vwebbrowseSetNameScribed(b, n)				              \
    vclassSend(vwebbrowseGetClass(b), vwebbrowseSET_NAME_SCRIBED, (b, n))

#define vwebbrowseSetProcessNotify(b, n)			              \
    vclassSend(vwebbrowseGetProcessClass(b), 				      \
	       vwebbrowseSET_PROCESS_NOTIFY, (b, n))
#define vwebbrowseSetProcessWebbrowse(b, r)			              \
    vclassSend(vwebbrowseGetProcessClass(b), 				      \
	       vwebbrowseSET_PROCESS_WEBBROWSE, (b, r))
#define vwebbrowseNotifyProcess(b, e)				              \
    vclassSend(vwebbrowseGetProcessClass(b), vwebbrowseNOTIFY_PROCESS, (b, e))
#define vwebbrowseSetProcessStartupURL(b, c)			              \
    vclassSend(vwebbrowseGetProcessClass(b), 				      \
	       vwebbrowseSET_PROCESS_STARTUP_URL, (b, c))

vportEND_CPLUSPLUS_EXTERN_C

#endif /* vwebbrowseINCLUDED */










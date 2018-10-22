/* $Id: vhelp.h,v 1.39 1997/11/06 19:39:50 robert Exp $ */

/* -----------------------------------------------------------------------
 *
 *  vhelp.h
 *
 *  Programming interface to the low level help system
 *
 *  (c) Copyright Visix Software
 *  All rights reserved
 *
 * -----------------------------------------------------------------------
 */


#ifndef vhelpINCLUDED
#define vhelpINCLUDED	1

#ifndef vportINCLUDED
#include <vport.h>
#endif

#ifndef vcharINCLUDED
#include vcharHEADER
#endif
#ifndef vscribeINCLUDED
#include vscribeHEADER
#endif
#ifndef vrectINCLUDED
#include vrectHEADER
#endif
#ifndef vclassINCLUDED
#include vclassHEADER
#endif
#ifndef vinstanceINCLUDED
#include vinstanceHEADER
#endif
#ifndef vresourceINCLUDED
#include vresourceHEADER
#endif
#ifndef vhelpobjectINCLUDED
#include vhelpobjectHEADER
#endif
#ifndef vhelphypertextINCLUDED
#include vhelphypertextHEADER
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C


/*
 * * * * * * * * * * * * PUBLIC CONSTANT DEFINITIONS * * * * * * * * * * *
 */


enum {
    vhelpEventOPENED_WINDOW		=   1,
    vhelpEventCLOSED_WINDOW		=   2,
    vhelpEventCHANGED_CONTEXT		=   3,
    vhelpEventCHANGED_KEYWORD		=   4,
    vhelpEventOPENED_FILE		=   5,
    vhelpEventOPENED_TABLE_OF_CONTENTS	=   6,
    vhelpEventUNKNOWN_CODE		= -10,
    vhelpEventCANNOT_CONTACT_SERVER	= -11,
    vhelpEventREQUEST_FAILED		= -12,
    vhelpEventCANNOT_SEND_MESSAGE	= -13
};


/*
 * * * * * * * * * * * * * PUBLIC TYPE DEFINITIONS * * * * * * * * * * * *
 */


typedef struct vhelpWindow		vhelpWindow;
typedef        vhelpWindow		vhelpMSWWindow;
typedef struct vhelpWindowClass		vhelpWindowClass;

typedef int				vhelpEvent;

typedef void (*vhelpWindowNoteProc)(
    vhelpWindow			*window,
    vhelpEvent			 event
    );


/*
 * * * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * * * *
 */


void vhelpStartup(void);

void vhelpStartupWinHelp(void);

void vhelpStartupTooltip(void);

void vhelpStartupStatus(void);

void vhelpStartupDefaultHTML(void);

void vhelpStartupNetscape(void);

void vhelpStartupExplorer(void);

vhelpWindowClass *vhelpGetRootWindowClass(void);

vhelpWindowClass *vhelpGetGalaxyWindowClass(void);

vhelpWindowClass *vhelpGetMSWWindowClass(void);

vhelpWindowClass *vhelpGetOldGalaxyWindowClass(void);


vhelpWindow  *vhelpCreateWindowOfClass(
    vhelpWindowClass	*clas
    );

void vhelpCloseWindow(
    vhelpWindow		*window
    );

void vhelpDestroyWindow(
    vhelpWindow		*window
    );

void vhelpDestroyWindowLater(
    vhelpWindow		*window
    );

vhelpWindowClass *vhelpGetWindowClass(
    vhelpWindow		*window
    );

vinstance *vhelpGetWindowInstance(
    vhelpWindow		*window
    );


/*
 * Global Window funtions
 */

vhelpWindow *vhelpGetDefaultGlobalWindow(void);

vhelpWindow *vhelpGetSystemGlobalWindow(
    vhelpWindow		*window  /* to tell which system */
    );


/*
 * window display functions
 */

void vhelpSwitchWindowToContext(
    vhelpWindow		*window,
    const vchar		*context,
    const vrect		*rectPlace
    );

void vhelpSwitchWindowToContextScribed(
    vhelpWindow		*window,
    vscribe		*context,
    const vrect		*rectPlace
    );

void vhelpSwitchWindowToNestedContext(
    vhelpWindow		*window,
    const vchar	       **arrayContext,
    int			 count,
    const vrect		*rectPlace
    );

void vhelpSwitchWindowToKeyword(
    vhelpWindow		*window,
    const vchar		*keyword,
    const vrect		*rectPlace
    );

void vhelpSwitchWindowToKeywordScribed(
    vhelpWindow		*window,
    vscribe		*scribeKeyword,
    const vrect		*rectPlace
    );

void vhelpOpenWindowTableOfContents(
    vhelpWindow		*window,
    const vrect		*rectPlace
    );


/*
 * window attr functions
 */

void vhelpSetWindowData(
    vhelpWindow		*window,
    void		*data
    );

void *vhelpGetWindowData(
    vhelpWindow		*window
    );

void vhelpSetWindowNotify(
    vhelpWindow		*window,
    vhelpWindowNoteProc	 noteProc
    );

vhelpWindowNoteProc vhelpGetWindowNotify(
    vhelpWindow		*window
    );

void vhelpNotifyWindow(
    vhelpWindow		*window,
    vhelpEvent		 event
    );


/*
 * misc functions...
 */


void vhelpShutdownWindow(
    vhelpWindow		*window /* to tell which system */
    );

void vhelpOpenFile(
    vhelpWindow		*window, /* tell which system */
    const vfsPath	*path,
    int			 zero, /* set to zero */
    const vrect		*rectPlace
    );

vbool vhelpEventIsError(
    vhelpEvent		 event
    );

void vhelpSetApplicationName(
    const vchar		*name
    );

void vhelpSetApplicationNameScribed(
    vscribe		*name
    );

const vchar *vhelpGetApplicationName(void);


/*
 * for handling of Default system
 */

void vhelpSetDefaultWindowClass(
    vhelpWindowClass	*windowClass
    );

vhelpWindowClass *vhelpGetDefaultWindowClass(void);


void vhelpUseGalaxyHelpSystem(void);

void vhelpUseMSWindowsHelpSystem(void);

void vhelpUseOldGalaxyHelpSystem(void);

int vhelpGalaxyHelpSystemIsAvailable(void);

int vhelpOldGalaxyHelpSystemIsAvailable(void);

int vhelpMSWindowsHelpSystemIsAvailable(void);


/* !!! SPAM !!!
 */

void vhelpUseNativeHelpSystem(void);
int vhelpNativeHelpSystemIsAvailable(void);

void _vhelpSetApplicationResource(
    vresource		 res
    );

vresource _vhelpGetApplicationResource(void);


/*
 * * * * * * * * * * * * DEPRECATED DEFINITIONS * * * * * * * * * * *
 */


/* use CreateOfClass */
vhelpWindow *vhelpCreateWindow(void);

/* fetch the default or for a given class */
vhelpWindow *vhelpGetGlobalWindow(void);


/* use the window one to say which system */
void vhelpShutdownServer(void);


/* use keyword functions instead */
void  vhelpSwitchToConcept(vhelpWindow *window, const vchar *sConcept,
			   const vrect *rectPlace);
void  vhelpSwitchToConceptScribed(vhelpWindow *window, vscribe *scribeConcept,
				  const vrect *rectPlace);
/* use api with "Window" in name */
void vhelpSwitchToContext(vhelpWindow *window, const vchar *context,
			  const vrect *rectPlace);
void vhelpSwitchToContextScribed(vhelpWindow *window, vscribe *context,
				 const vrect *rectPlace);
void vhelpSwitchToNestedContext(vhelpWindow *window,
				const vchar **arrayContext, int count,
				const vrect *rectPlace);
void vhelpSwitchToKeyword(vhelpWindow *window, const vchar *keyword,
			  const vrect *rectPlace);
void vhelpSwitchToKeywordScribed(vhelpWindow *window, vscribe *scribeKeyword,
				 const vrect *rectPlace);


/*
 * * * * * * * * * * * * PRIVATE CONSTANT DEFINITIONS * * * * * * * * * * *
 */


/*
 * * * * * * * * * * * * PRIVATE VARIABLE DECLARATIONS * * * * * * * * * * *
 */


/*
 * * * * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * * * *
 */

typedef vhelpWindowClass *(*_vhelpStarterProc)();

typedef void (*vhelpPrivateNoteProc)(
    vhelpWindow			*window,
    vhelpEvent			 event
    );

struct vhelpWindow {
    vinstance			 instance;
    vhelpWindowNoteProc		 noteProc;
    vhelpPrivateNoteProc	 privateNotify;
    vhelphypertext		*display;
    void			*data;
};

#define vhelpWindowCLASS(SUPER, OBJ)					\
    vinstanceCLASS(SUPER, OBJ);						\
    vclassMETHOD_RET(vhelpGET_SYSTEM_GLOBAL_WINDOW, vhelpWindow *,	\
		     (OBJ *dummy));					\
    vclassMETHOD(vhelpSHUTDOWN, (OBJ *dummy));				\
    vclassMETHOD(vhelpOPEN_FILE,					\
		 (OBJ *dummy, const vfsPath *path, int forThisApp,	\
		  const vrect *rect));					\
    vclassMETHOD(vhelpNOTIFY, (OBJ *window, vhelpEvent event));		\
    vclassMETHOD(vhelpCLOSE_WINDOW, (OBJ *window));			\
    vclassMETHOD(vhelpOPEN_TABLE_OF_CONTENTS,				\
		 (OBJ *window, const vrect *rect));			\
    vclassMETHOD(vhelpSWITCH_KEYWORD,					\
		 (OBJ *window , const vchar *context, const vrect *rect)); \
    vclassMETHOD(vhelpSWITCH_KEYWORD_SCRIBED,				\
		 (OBJ *window , vscribe *context, const vrect *rect));	\
    vclassMETHOD(vhelpSWITCH_CONTEXT,					\
		 (OBJ *window, const vchar *context, const vrect *rect)); \
    vclassMETHOD(vhelpSWITCH_CONTEXT_SCRIBED,				\
		 (OBJ *window, vscribe *context, const vrect *rect));	\
    vclassMETHOD(vhelpSWITCH_NESTED_CONTEXT,				\
		 (OBJ *window, const vchar **array, int count,		\
		  const vrect *rect))

struct vhelpWindowClass {
    vhelpWindowCLASS(vhelpWindowClass, vhelpWindow);
};

vportALIAS(vhelpMSWWindow, vhelpWindow)

/*
 * * * * * * * * * * * * PRIVATE FUNCTION PROTOTYPES * * * * * * * * * * *
 */

void _vhelpSetWindowPrivateNotify (vhelpWindow *window, vhelpEvent event);
void _vhelpSetWindowHypertext (vhelpWindow *window, vhelphypertext *display);
vhelphypertext *_vhelpGetWindowHypertext (vhelpWindow *window);

/*
 * * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * *
 */


#define vhelpGetWindowClass(win) \
  (vhelpWindowClass *)vinstanceGetClass((vinstance *)win)

#define vhelpGetWindowInstance(win) \
  vportBASE_OBJECT((win), instance)

#define vhelpCreateWindowOfClass(c) \
  (vhelpWindow *)vinstanceCreateOfClass((vinstanceClass *)c)

#define vhelpEventIsError(msg)			((msg) < 0)
    
#define vhelpSetApplicationName(s) \
  vhelpSetApplicationNameScribed(vcharScribe(s))

#define vhelpGetWindowNotify(win)		((win)->noteProc)

#define vhelpSetWindowData(win, p)		((win)->data = (p))
    
#define vhelpGetWindowData(win)			((win)->data)

#define _vhelpSetWindowPrivateNotify(win, n)	((win)->privateNotify = (n))

#define _vhelpGetWindowHypertext(win)		((win)->display)

#define _vhelpSetWindowHypertext(win, d)	((win)->display = (d))

/*
 * * * * * * * * * * * * FUNCTIONS DEFINED AS MESSAGES * * * * * * * * * *
 */


#define vhelpDestroyWindow(win) \
  vinstanceDestroy((vinstance *)win)

#define vhelpDestroyWindowLater(win) \
  vinstanceDestroyLater((vinstance *)win)

#define vhelpNotifyWindow(win, event) \
  vclassSend(vhelpGetWindowClass(win), vhelpNOTIFY, (win, event))

#define vhelpGetSystemGlobalWindow(win) \
  vclassSend(vhelpGetWindowClass(win), vhelpGET_SYSTEM_GLOBAL_WINDOW, (win))

#define vhelpShutdownWindow(win) \
  vclassSend(vhelpGetWindowClass(win), vhelpSHUTDOWN, (win))

#define vhelpOpenFile(win, path, zero, rect) \
  vclassSend(vhelpGetWindowClass(win), vhelpOPEN_FILE, \
	     (win, path, zero, rect))

#define vhelpCloseWindow(win) \
  vclassSend(vhelpGetWindowClass(win), vhelpCLOSE_WINDOW, (win))

#define vhelpOpenWindowTableOfContents(win, rect) \
  vclassSend(vhelpGetWindowClass(win), vhelpOPEN_TABLE_OF_CONTENTS, \
	     (win, rect))

#define vhelpSwitchWindowToKeyword(win, keyword, rect) \
  vclassSend(vhelpGetWindowClass(win), vhelpSWITCH_KEYWORD, \
	     (win, keyword, rect))

#define vhelpSwitchWindowToKeywordScribed(win, keyword, rect) \
  vclassSend(vhelpGetWindowClass(win), vhelpSWITCH_KEYWORD_SCRIBED, \
	     (win, keyword, rect))

#define vhelpSwitchWindowToContext(win, context, rect) \
  vclassSend(vhelpGetWindowClass(win), vhelpSWITCH_CONTEXT, \
	     (win, context, rect))

#define vhelpSwitchWindowToContextScribed(win, context, rect) \
  vclassSend(vhelpGetWindowClass(win), vhelpSWITCH_CONTEXT_SCRIBED, \
	     (win, context, rect))

#define vhelpSwitchWindowToNestedContext(win, array, n, rect) \
  vclassSend(vhelpGetWindowClass(win), vhelpSWITCH_NESTED_CONTEXT, \
	     (win, array, n, rect))


/*
 * * * * * * * * * * * * * * * DEAD FUNCTIONS * * * * * * * * * * * * * *
 */


#define vhelpCreateWindow() \
  vhelpCreateWindowOfClass(vhelpGetGalaxyWindowClass())

#define vhelpGetGlobalWindow() \
  vhelpGetDefaultGlobalWindow()

#define vhelpShutdownServer() \
  vhelpShutdownWindow(vhelpGetGlobalWindow())

#define vhelpSwitchToConcept(w, k, r) \
  vhelpSwitchWindowToKeyword(w, k, r)

#define vhelpSwitchToConceptScribed(w, k, r) \
  vhelpSwitchWindowToKeywordScribed(w, k, r)

#define vhelpSwitchToContext(w, c, r) \
  vhelpSwitchWindowToContext(w, c, r)

#define vhelpSwitchToContextScribed(w, c, r) \
  vhelpSwitchWindowToContextScribed(w, c, r)

#define vhelpSwitchToNestedContext(w, ac, c, r) \
  vhelpSwitchWindowToNestedContext(w, ac, c, r)

#define vhelpSwitchToKeyword(w, k, r) \
  vhelpSwitchWindowToKeyword(w, k, r)

#define vhelpSwitchToKeywordScribed(w, k, r) \
  vhelpSwitchWindowToKeywordScribed(w, k, r)

#define vhelpUseGalaxyHelpSystem() \
    vhelpSetDefaultWindowClass(vhelpGetGalaxyWindowClass())

#define vhelpUseMSWindowsHelpSystem() \
    vhelpSetDefaultWindowClass(vhelpGetMSWWindowClass())

#define vhelpUseOldGalaxyHelpSystem() \
    "old (Looking Glass) help system no longer available"

#define vhelpGetOldGalaxyWindowClass() \
    "old (Looking Glass) help system no longer available"

#define vhelpOldGalaxyHelpSystemIsAvailable()  FALSE

vportEND_CPLUSPLUS_EXTERN_C


#endif

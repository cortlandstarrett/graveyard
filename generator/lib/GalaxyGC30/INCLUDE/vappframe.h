/* $Id: vappframe.h,v 1.24 1997/06/17 21:16:32 alexey Exp $ */

/******************************************
 * vappframe.h
 *
 * Application Frame Manager header file
 *
 * Part of Galaxy Application Environment
 *
 * Copyright (C) 1995 Visix Software Inc.
 * All rights reserved.
 ******************************************/


#ifndef vappframeINCLUDED
#define vappframeINCLUDED 1

#ifndef  vportINCLUDED		/* for v*HEADER */
#include <vport.h>
#endif

#ifndef  vstddefINCLUDED	/* for size_t */
#include vstddefHEADER
#endif

#ifndef  vstdioINCLUDED		/* for FILE */
#include vstdioHEADER
#endif

#ifndef  vstdINCLUDED		/* for vbool */
#include vstdHEADER
#endif

#ifndef  vfsINCLUDED
#include vfsHEADER
#endif

#ifndef  vevent2INCLUDED
#include vevent2HEADER
#endif

#ifndef  vloadableINCLUDED
#include vloadableHEADER
#endif

#ifndef  vobservableINCLUDED
#include vobservableHEADER
#endif

#ifndef  vresourceINCLUDED
#include vresourceHEADER
#endif

#ifndef  vtimestampINCLUDED
#include vtimestampHEADER
#endif

#ifndef  vsequenceINCLUDED
#include vsequenceHEADER
#endif

#ifndef  vmappingINCLUDED
#include vmappingHEADER
#endif

#ifndef  vapplicationINCLUDED
#include vapplicationHEADER
#endif

#ifndef  vresolverINCLUDED
#include <vresolver.h>
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C


/*
 * * * * * * * * * * * * * PUBLIC CONSTANTS * * * * * * * * * * * * * *
 */

enum
{
  vappframeOPEN_SPLASH_PHASE = 0,
  vappframeOPEN_PHASE,
  vappframeCLOSE_SPLASH_PHASE,
  vappframeCHECK_PHASE,
  vappframeCLOSE_PHASE,
  vappframeSHUTDOWN_PHASE,
  _vappframePHASE_COUNT
};


/*
 * * * * * * * * * * * * * PUBLIC TYPES * * * * * * * * * * * * * *
 */

typedef struct vappframeClass			vappframeClass;
typedef struct vappframeWithEventsClass		vappframeWithEventsClass;

typedef struct vappframe			vappframe;
typedef struct vappframeWithEvents		vappframeWithEvents;

/*
 * * * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * * *
 */

void vappframeStartup(
	void
	);

/*
 * Application frame create/destruction routines.
 */


vappframeClass	*vappframeGetDefaultClass(
	void
	);

vappframeWithEventsClass *vappframeGetDefaultWithEventsClass(
	void
	);

vappframeClass	*vappframeGetClass(
	vappframe			*appframe
	);

vappframeWithEventsClass *vappframeGetWithEventsClass(
	vappframeWithEvents		*appframe
	);

vappframe	*vappframeGetWithEventsBase(
	vappframeWithEvents		*appframe
	);

vobservable	*vappframeGetObservable(
	vappframe			*appframe
	);

vloadable	*vappframeGetLoadable(
	vappframe			*appframe
	);

vinstance	*vappframeGetInstance(
	vappframe			*appframe
	);

vappframe	*vappframeCreate(
	void
	);

vappframeWithEvents *vappframeCreateWithEvents(
	void
	);

vappframe	*vappframeCreateOfClass(
	vappframeClass			*clas
	);

vappframeWithEvents *vappframeCreateWithEventsOfClass(
	vappframeWithEventsClass	*clas
	);

void		 vappframeInit(
	vappframe			*appframe
	);

void		 vappframeInitWithEvents(
	vappframeWithEvents		*appframe
	);

void		 vappframeInitOfClass(
	vappframe			*appframe,
	vappframeClass			*clas
	);

void		 vappframeInitWithEventsOfClass(
	vappframeWithEvents		*appframe,
	vappframeWithEventsClass	*clas
	);

void		 vappframeDestroy(
	vappframe			*appframe
	);

void		 vappframeSetGlobal(
	vappframe			*appframe
	);

vappframe	*vappframeGetGlobal(
	void
	);

void		 vappframeDoOpenSplash(
	vappframe			*appframe
	);

void		 vappframeDoOpen(
	vappframe			*appframe
	);

void		 vappframeDoCloseSplash(
	vappframe			*appframe
	);

void		 vappframeDoClose(
	vappframe			*appframe
	);

void		 vappframeDoCheck(
	vappframe			*appframe
	);

void		 vappframeDoShutdown(
	vappframe			*appframe
	);


/*
 * Application frame attributes.
 */

void 		vappframeSetApplication(
        vappframe                  	*appframe,
        vapplication			*application
        );

vapplication 	*vappframeGetApplication(
    	vappframe                   	*appframe
    	);

void 		vappframeSetResolver(
        vappframe                  	*appframe,
        vresolver			*resolver
        );

vresolver 	*vappframeGetResolver(
    	vappframe                   	*appframe
    	);

void 		vappframeSetPreferences(
    	vappframe                   	*appframe,
    	vresource                       resource
    	);

vresource 	vappframeGetPreferences(
    	vappframe                   	*appframe
    	);

vresource 	vappframeGetSystemPreferences(
    	vappframe                   	*appframe
    	);

void		vappframeSetArguments(
	vappframe			*appframe,
	size_t				 argCount,
	const vchar		       **args
	);

int 		vappframeGetArgumentCount(
        vappframe                   	*appframe
    	);

const vchar 	*vappframeGetArgumentAt(
        vappframe                   	*appframe,
    	int				index
    	);

void		vappframeSetSplashDelay(
        vappframe			*appframe,
        vtimestamp			delay
        );

vtimestamp	vappframeGetSplashDelay(
        vappframe			*appframe
        );

void		vappframeSetCheckDelay(
        vappframe			*appframe,
        vtimestamp			delay
        );

vtimestamp	vappframeGetCheckDelay(
        vappframe			*appframe
        );

void		vappframeSetSplashDialogResolvePath(
	vappframe			*appframe,
	const vchar			*resolvePath
	);        

void		vappframeSetSplashDialogResolvePathScribed(
	vappframe			*appframe,
	vscribe				*resolvePath
	);        

const vchar	*vappframeGetSplashDialogResolvePath(
	vappframe			*appframe
	);

void		vappframeSetInitialDialogResolvePath(
	vappframe			*appframe,
	const vchar			*resolvePath
	);        

void		vappframeSetInitialDialogResolvePathScribed(
	vappframe			*appframe,
	vscribe				*resolvePath
	);        

const vchar	*vappframeGetInitialDialogResolvePath(
	vappframe			*appframe
	);

/*
 * Application frame running operations.
 */

void		 vappframeStart(
        void
	);
	
void		 vappframeStartWithArgs(
	size_t				 argCount,
	const vchar		       **args
	);
	
void		 vappframeStop(
	void
	);
	
void		 vappframeResume(
	void
	);
	
void		 vappframeAbort(
	void
	);
	
/*
 * C startup routines
 */

int		 vappframeMain(
	int				 argumentCount,
	char				**argumentList
	);
	

/*
 * * * * * * * * * * PUBLIC MACROS * * * * * * * * * *
 */

#ifndef vappframeNAME


#if !(vportBAD_CPP_POUND)

#define vappframeMAKE_NAMES()
#define vappframeNAME(n) vnameInternGlobalLiteral(#n)

#else /* (vportBAD_CPP_POUND) */

#define vappframeMAKE_NAMES()
#define vappframeNAME(n) vnameInternGlobalLiteral("n")

#endif /* (vportBAD_CPP_POUND) */


#endif /* ndef vappframeNAMES */

/*
 * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * *
 */

typedef vbool (*_vappframeHookProc)(vappframe *appframe);

/*
 * Application frames
 */

struct vappframe
{
  vobservable		 observable;

  vbool			 stopping;
  vbyte			 phase;
  vsequence		*phases[_vappframePHASE_COUNT];
  vtimestamp		 splashDelay;
  vtimestamp		 checkDelay;
  
  int			 argumentCount;
  vstr	       	       **arguments;

  vstr			*splashDialogPath;
  vstr			*initialDialogPath;

  vapplication		*application;

  _vappframeHookProc	 checkHookProc;
  _vappframeHookProc	 startHookProc;
  _vappframeHookProc	 stopHookProc;
  _vappframeHookProc	 resumeHookProc;
  _vappframeHookProc	 abortHookProc;
};


#define vappframeCLASS(CLASS, APPFRAME)					      \
    vobservableCLASS(CLASS, APPFRAME);					      \
    vclassMETHOD(vappframeDO_OPEN_SPLASH, (APPFRAME *appframe));	      \
    vclassMETHOD(vappframeDO_OPEN, (APPFRAME *appframe));		      \
    vclassMETHOD(vappframeDO_CLOSE_SPLASH, (APPFRAME *appframe));	      \
    vclassMETHOD(vappframeDO_CHECK, (APPFRAME *appframe));		      \
    vclassMETHOD(vappframeDO_CLOSE, (APPFRAME *appframe));		      \
    vclassMETHOD(vappframeDO_SHUTDOWN, (APPFRAME *appframe));		      \
    vclassMETHOD(vappframeSTART, (APPFRAME *appframe));			      \
    vclassMETHOD(vappframeSTOP, (APPFRAME *appframe));			      \
    vclassMETHOD(vappframeRESUME, (APPFRAME *appframe));		      \
    vclassMETHOD(vappframeABORT, (APPFRAME *appframe))


struct vappframeClass
{
  vappframeCLASS(vappframeClass, vappframe);
};


struct vappframeWithEvents
{
  vappframe		 base;

  vevent2		*event;
  vevent2Loop		*loop;
  vtimestamp		 splashTimeout;
  vinstance		*splashDialog;
  vinstance		*initialDialog;
};


struct vappframeWithEventsClass
{
  vappframeCLASS(vappframeWithEventsClass, vappframeWithEvents);
};


/*
 * * * * * * * * * * * * * PRIVATELY exported variables * * * * * * * * * *
 */

/*
 * * * * * * * * * * * * * PRIVATELY exported prototypes * * * * * * * * * *
 */

vbool vappframePerformOneTask(vappframe *appframe, int phase);
vbool vappframePerformTasksTimed(vappframe *appframe, int phase,
				 vtimestamp timeout);
void vappframePerformAllTasks(vappframe *appframe, int phase);
void vappframePerformMandatoryTasks(vappframe *appframe, int phase);
void vappframeInsertTaskOwned(vappframe *appframe, int phase,
			      int index, vobservable *task);
void vappframeAppendTaskOwned(vappframe *appframe, int phase,
			      vobservable *task);
vobservable *vappframeRemoveTaskAt(vappframe *appframe, int phase, int index);
int vappframeGetTaskCount(vappframe *appframe, int phase);
vobservable *vappframeGetTaskAt(vappframe *appframe, int phase, int index);


void _vappframeSendStart(vappframe *appframe);
void _vappframeSendStop(vappframe *appframe);
void _vappframeSendResume(vappframe *appframe);
void _vappframeSendAbort(vappframe *appframe);
 
void _vappframeSetCheckHookProc(vappframe *appframe, _vappframeHookProc proc);
void _vappframeSetStartHookProc(vappframe *appframe, _vappframeHookProc proc);
void _vappframeSetStopHookProc(vappframe *appframe, _vappframeHookProc proc);
void _vappframeSetResumeHookProc(vappframe *appframe, _vappframeHookProc proc);
void _vappframeSetAbortHookProc(vappframe *appframe, _vappframeHookProc proc);

_vappframeHookProc _vappframeGetCheckHookProc(vappframe *appframe);
_vappframeHookProc _vappframeGetStartHookProc(vappframe *appframe);
_vappframeHookProc _vappframeGetStopHookProc(vappframe *appframe);
_vappframeHookProc _vappframeGetResumeHookProc(vappframe *appframe);
_vappframeHookProc _vappframeGetAbortHookProc(vappframe *appframe);

/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * *
 */

/*
 * Application frames
 */

#define vappframeGetObservable(f) \
	vportBASE_OBJECT(f, observable)

#define vappframeGetLoadable(f) \
	vobservableGetLoadable(vappframeGetObservable(f))

#define vappframeGetInstance(f) \
	vobservableGetInstance(vappframeGetObservable(f))

#define vappframeGetClass(f) \
	((vappframeClass *) vloadableGetClass(vappframeGetLoadable(f)))

#define vappframeGetWithEventsBase(f) \
	vportBASE_OBJECT(f, base)

#define vappframeGetWithEventsClass(f) \
	((vappframeWithEventsClass *) \
	 vappframeGetClass(vappframeGetWithEventsBase(f)))

#define vappframeCreateOfClass(c) \
	((vappframe *) vloadableCreateOfClass((vloadableClass *)(c)))

#define vappframeCreate() \
	vappframeCreateOfClass(vappframeGetDefaultClass())

#define vappframeCreateWithEventsOfClass(c) \
	((vappframeWithEvents *) vappframeCreateOfClass((vappframeClass *)(c)))

#define vappframeCreateWithEvents() \
	vappframeCreateWithEventsOfClass(vappframeGetDefaultWithEventsClass())

#define vappframeInitOfClass(f,c) \
	vloadableInitOfClass(vappframeGetLoadable(f), (vloadableClass *)(c))

#define vappframeInit(f) \
	vappframeInitOfClass(f, vappframeGetDefaultClass())

#define vappframeInitWithEventsOfClass(f,c) \
	vappframeInitOfClass(vappframeGetWithEventsBase(f), \
			     (vappframeClass *)(c))

#define vappframeInitWithEvents(f) \
	vappframeInitWithEventsOfClass(f, vappframeGetDefaultWithEventsClass())

#define vappframeDestroy(f) \
	vloadableDestroy(vappframeGetLoadable(f))

#define vappframeGetApplication(a) \
    	((a)->application)

#define vappframeGetArgumentCount(a) \
    	((a)->argumentCount)

#define vappframeGetArgumentAt(a, i) \
    	((a)->arguments[(i)])

#define vappframeSetSplashDelay(a, p) \
	((a)->splashDelay = (p))

#define vappframeGetSplashDelay(a) \
	((a)->splashDelay)

#define vappframeSetCheckDelay(a, p) \
	((a)->checkDelay = (p))

#define vappframeGetCheckDelay(a) \
	((a)->checkDelay)

#define vappframeGetSplashDialogResolvePath(a) \
	((a)->splashDialogPath)

#define vappframeGetInitialDialogResolvePath(a) \
	((a)->initialDialogPath)

#define _vappframeSetCheckHookProc(a,p) ((a)->checkHookProc = (p))
#define _vappframeSetStartHookProc(a,p) ((a)->startHookProc = (p))
#define _vappframeSetStopHookProc(a,p) ((a)->stopHookProc = (p))
#define _vappframeSetResumeHookProc(a,p) ((a)->resumeHookProc = (p))
#define _vappframeSetAbortHookProc(a,p) ((a)->abortHookProc = (p))

#define _vappframeGetCheckHookProc(a,p) ((a)->checkHookProc)
#define _vappframeGetStartHookProc(a,p) ((a)->startHookProc)
#define _vappframeGetStopHookProc(a,p) ((a)->stopHookProc)
#define _vappframeGetResumeHookProc(a,p) ((a)->resumeHookProc)
#define _vappframeGetAbortHookProc(a,p) ((a)->abortHookProc)

/*
 * * * * * * * * * * PRIVATE FUNCTION MESSAGE DEFINITIONS * * * * * * * * * *
 */

/*
 * Application frames
 */

#define vappframeDoOpenSplash(f) \
      vclassSend(vappframeGetClass(f), vappframeDO_OPEN_SPLASH, (f))

#define vappframeDoOpen(f) \
      vclassSend(vappframeGetClass(f), vappframeDO_OPEN, (f))

#define vappframeDoCloseSplash(f) \
      vclassSend(vappframeGetClass(f), vappframeDO_CLOSE_SPLASH, (f))

#define vappframeDoCheck(f) \
      vclassSend(vappframeGetClass(f), vappframeDO_CHECK, (f))

#define vappframeDoClose(f) \
      vclassSend(vappframeGetClass(f), vappframeDO_CLOSE, (f))

#define vappframeDoShutdown(f) \
      vclassSend(vappframeGetClass(f), vappframeDO_SHUTDOWN, (f))

#define _vappframeSendStart(f) \
      vclassSend(vappframeGetClass(f), vappframeSTART, (f))

#define _vappframeSendStop(f) \
      vclassSend(vappframeGetClass(f), vappframeSTOP, (f))

#define _vappframeSendResume(f) \
      vclassSend(vappframeGetClass(f), vappframeRESUME, (f))

#define _vappframeSendAbort(f) \
      vclassSend(vappframeGetClass(f), vappframeABORT, (f))


vportEND_CPLUSPLUS_EXTERN_C

#endif /* #ifndef vappframeINCLUDED */

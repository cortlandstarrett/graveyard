/* $Id: ttask.h,v 1.3 1994/12/05 15:47:33 simone Exp $ */
/******************************************************************************
 *                  (c) Copyright 1993-94 Visix Software Inc.                 *
 *                            All rights reserved.                            *
 *                                                                            *
 *    The following Sample Code is provided for your reference purposes in    *
 *     connection with your use of the Galaxy Application Environment (TM)    *
 *     software product which you have licensed from Visix Software, Inc.     *
 * ("Visix"). The Sample code is provided to you without any warranty of any  *
 *     kind whatsoever and you agree to be responsible for the use and/or     *
 *   incorporation of the Sample Code into any software product you develop.  *
 *  You agree to fully and completely indemnify and hold Visix harmless from  *
 * any and all loss, claim, liability or damages with respect to your use of  *
 *    the Sample Code. Subject to the foregoing, you are permitted to copy,   *
 *   modify, and distribute the Sample Code for any purpose and without fee,  *
 * provided that (i) a copyright notice in the in the form of "Copyright 1992,*
 *  93 Visix Software Inc., 11440 Commerce Park Drive, Reston, VA  22091. All *
 * Rights Reserved" appears in all copies, (ii) both the copyright notice and *
 *  this permission notice appear in supporting documentation and (iii) you   *
 *            are a valid licensee of Galaxy Application Environment.         *
 *                                                                            *
 ******************************************************************************
 *                                                                            *
 * Description:                                                               *
 *     Written to demonstrate how the Galaxy/C class mangler can be used for  *
 *     generic (non-UI) design. Basically a task is an action you'd want done *
 *     later: either the next time through the event loop or after a specified*
 *     delay amount of time. The root class "ttask" is an abstract class that *
 *     must be subclassed. Several "ready-to-use" subclasses have been imple- *
 *     mented for illustrative purpose: ttaskQueue, ttaskExternal, and        *
 *     ttaskCmdDispatcher.                                                    *
 *                                                                            *
 *     As a whole the module (all task source files) illustrate some other    *
 *     tips/techniques wrt. the galaxy debugging and exception managers. The  *
 *     standalone application "boinker" was written to use show some of the   *
 *     (more superfluous) ways the task classes could be used.                *
 *                                                                            *
 *     Managers Used:                                                         *
 *         o Exception Manager - we create one or two exception subclasses    *
 *         o Debugging Manager - we include several examples of how the misc  *
 *           vdebug macros and routines can be used to implement argument,    *
 *           return-value, pre-post condition, and assertion checking...      *
 *         o Class Manager - we use to class manager to implement non-GUI     *
 *           classes                                                          *
 *         o Event Manager - if you've ever wanted to know how to use client  *
 *           events, you're looking at the right sample...specifically,       *
 *           we rely on client events to implement our task class(es).        *
 *                                                                            *
 * Modification History:                                                      *
 *     o 09-14-94: ssmc, created for The Galaxy Developers Conference 1994    *
 *                                                                            *
 * Special Usage Notes:                                                       *
 *     o assumes sizeof(vchar) is NOT greater than sizeof(unsigned char)      *
 *     o we're only using ASCII characters in task names (sorry erik...)      *
 *                                                                            *
 * Text Editor Formatting:                                                    *
 *     Symantec: Tab(4), Font(Any Fixed Width)                                *
 *     Emacs: see end of file for info                                        *
 *                                                                            *
 ******************************************************************************
 */

#ifndef ttaskINCLUDED
#define ttaskINCLUDED	1


#ifndef  vportINCLUDED
#include <vport.h>
#endif

#ifndef  vstdargINCLUDED
#include vstdargHEADER
#endif

#ifndef  vdebugINCLUDED
#include vdebugHEADER
#endif

#ifndef  vexINCLUDED
#include vexHEADER
#endif

#ifndef  vtimestampINCLUDED
#include vtimestampHEADER
#endif

#ifndef  veventINCLUDED
#include veventHEADER
#endif

#ifndef  vtimerINCLUDED
#include vtimerHEADER
#endif

#ifndef  vstrINCLUDED
#include vstrHEADER
#endif

#ifndef  vclassINCLUDED
#include vclassHEADER
#endif

#ifndef  vobjectINCLUDED
#include vobjectHEADER
#endif


/*
 *+------------------------------------------------------------------------+
 * public const, type declarations
 *+------------------------------------------------------------------------+
 */

/*
 * Versioning (mostly for resource-based object). Ignored to date.
 */
#define ttaskVERSION_1 1
#define ttaskCURRENT_VERSION ttaskVERSION_1



/*
 * Our Exception Subclass:
 *		Keeps track of the task's description as part of exception
 *		data. This description can be used in error notices, etc.
 */
typedef struct ttaskStateException ttaskStateException;




/*
 * Our Abstract Task Class:
 *		A Task is an action you'd want done later: either the next 
 *		time through the event loop or after a specified amount of
 *		time. tasks (like timers) can be recurrent or can fire
 *		for a fixed number of times. tasks can delete themselves
 *		("auto-delete") once they've finished performing their
 *		action. tasks can be blocked st. they won't perform any action
 *		-- even if their delay time expires. and finally, users 
 *		can associate a description (ie. natural language not a
 *		cryptic tag) with each task. this description can be used
 *		in error notices, status windows, etc.
 */
typedef struct ttask ttask;
typedef struct ttaskClass ttaskClass;



/* 
 * Our Task Class that calls External Procs:
 *		This task subclass will iteratively call a series of external
 *		(to self) procedure references. The task will fire once for
 *		each associated procedure. So if you add 10 proc ptrs, the task
 *		will fire 10 times, returning to the event loop between each
 *		call.
 *
 *		ProcInitializers are a convenient initializer aggregate for
 *		this subclass.
 */
typedef struct ttaskExternal ttaskExternal;
typedef struct ttaskExternalClass ttaskExternalClass;

typedef void (*ttaskExternalProcPtr)(ttaskExternal*, const void*);
typedef struct ttaskExternalProcInitializer {
	const char				*description;
	ttaskExternalProcPtr	 proc;
	const void				*data;
}ttaskExternalProcInitializer;



/*
 * Our Task Class that issues a Galaxy Command:
 *		This task subclass will issue a vcommand to a specific galaxy
 *		object everytime it fires. So, for instance, it could be used to
 *		from a vconfirm hook proc to do work -after- leaving the hook
 *		proc. If not given an explicit target (kind of vobjectAttributed)
 *		the task will issue a command to the current vapplication.
 */
typedef struct ttaskCmdDispatcher ttaskCmdDispatcher;
typedef struct ttaskCmdDispatcherClass ttaskCmdDispatcherClass;



/*
 *+------------------------------------------------------------------------+
 * public entry points
 *+------------------------------------------------------------------------+
 */

/* TTASK ------------------------------------------------------------------+ 
 */


ttaskClass *ttaskGetDefaultClass(
	void
	);

ttask *ttaskCreateOfClass(
	ttaskClass					*clas
	);

ttask *ttaskCreate(
	void
	);

ttask *ttaskCreateOneShotOfClass(		/* max-iterations = 1, auto-deletes */
	ttaskClass					*clas
	);

ttask *ttaskCreateOneShot(
	void
	);

ttask *ttaskLoad(
	vresource					 resource
	);

ttask *ttaskClone(
	ttask						*task
	);

void ttaskInitOfClass(
	ttask						*task,
	ttaskClass					*clas
	);
	
void ttaskInit(
	ttask						*task
	);

void ttaskLoadInit(
	ttask						*task,
	vresource					 resource
	);

void ttaskCopy(
	ttask						*task,
	ttask						*copy
	);

void ttaskCopyInit(
	ttask						*task,
	ttask						*copy
	);

void ttaskDestroy(
	ttask						*task
	);

void ttaskDestroyLater(
	ttask						*task
	);

void ttaskStore(
	ttask						*task,
	vresource					 resource
	);

void ttaskPost(
	ttask						*task
	);

void ttaskFire(
	ttask						*task
	);

void ttaskExpire(
	ttask						*task
	);

void ttaskAutoDelete(
	ttask						*task,
	unsigned					 suicide
	);

void ttaskSetMaxIterations(
	ttask						*task,
	unsigned short				 iterations
	);

void ttaskSetMinDelay(
	ttask						*task,
	vtimestamp					*min_delay
	);

void ttaskDescribeAsScribed(
	ttask						*task,
	vscribe						*description
	);

void ttaskDescribeAs(
	ttask						*task,
	const vchar					*description
	);

void ttaskSetData(
	ttask						*task,
	const void					*rock
	);

void ttaskBlock(
	ttask						*task
	);

void ttaskUnBlock(
	ttask						*task
	);

unsigned ttaskIsBlocked(
	ttask						*task
	);

unsigned short ttaskGetMaxIterations(
	ttask						*task
	);

unsigned short ttaskGetCompletions(
	ttask						*task
	);

unsigned short ttaskGetRemaining(
	ttask						*task
	);

unsigned ttaskIsFinished(
	ttask						*task
	);

unsigned ttaskIsBlocked(
	ttask						*task
	);

unsigned ttaskIsUnBlocked(
	ttask						*task
	);

const vchar *ttaskGetDescription(
	ttask						*task
	);

unsigned ttaskIsLocked(
	ttask						*task
	);

const void *ttaskGetData(
	ttask						*task
	);

vtimestamp *ttaskGetMinDelayTimestamp(
	ttask						*task
	);

vobject *ttaskToObject(
	ttask						*task
	);

ttaskClass *ttaskGetClass(
	ttask						*task
	);



/* TTASK EXTERNAL PROC CALLER ---------------------------------------------+ 
 */



ttaskExternalClass *ttaskExternalGetDefaultClass(
	void
	);

ttaskExternal *ttaskExternalCreateFrom(
	ttaskExternalProcInitializer *inis
	);

ttaskExternal *ttaskExternalCreateOfClass(
	ttaskExternalClass			*clas
	);

ttaskExternal *ttaskExternalCreate(
	void
	);

ttaskExternal *ttaskExternalLoad(
	vresource					 resource
	);

ttaskExternal *ttaskExternalClone(
	ttaskExternal				*task
	);

void ttaskExternalInitOfClass(
	ttaskExternal				*task,
	ttaskExternalClass			*clas
	);
	
void ttaskExternalInit(
	ttaskExternal				*task
	);

void ttaskExternalLoadInit(
	ttaskExternal				*task,
	vresource					 resource
	);

void ttaskExternalCopy(
	ttaskExternal				*task,
	ttaskExternal				*copy
	);

void ttaskExternalCopyInit(
	ttaskExternal				*task,
	ttaskExternal				*copy
	);

void ttaskExternalDestroy(
	ttaskExternal				*task
	);

void ttaskExternalAdd(
	ttaskExternal				*task,
	ttaskExternalProcPtr		 proc,
	const void					*data,
	const vchar					*description
	);

void ttaskExternalRemoveFirst(
	ttaskExternal				*task,
	ttaskExternalProcPtr		 proc
	);

ttaskExternalProcPtr ttaskExternalNextWaiting(
	ttaskExternal				*task
	);

void ttaskExternalPost(
	ttaskExternal				*task
	);

void ttaskExternalSetMinDelay(
	ttaskExternal				*task,
	vtimestamp					*min_delay
	);

void ttaskExternalAutoDelete(
	ttaskExternal				*task,
	unsigned					 suicide
	);

void ttaskExternalDescribeAsScribed(
	ttaskExternal				*task,
	vscribe						*description
	);

void ttaskExternalDescribeAs(
	ttaskExternal				*task,
	const vchar					*description
	);

void ttaskExternalSetData(
	ttaskExternal				*task,
	const void					*rock
	);

const void *ttaskExternalGetData(
	ttaskExternal				*task
	);

unsigned ttaskExternalBreakProcError(
	ttaskExternal				*task
	);

const vchar *ttaskExternalGetDescription(
	ttaskExternal				*task
	);

vobject *ttaskExternalToObject(
	ttaskExternal				*task
	);

ttask *ttaskExternalToTask(
	ttaskExternal				*task
	);

ttaskExternalClass *ttaskExternalGetClass(
	ttaskExternal				*task
	);



/* TTASK COMMAND DISPATCHER -----------------------------------------------+ 
 */



ttaskCmdDispatcherClass *ttaskCmdDispatcherGetDefaultClass(
	void
	);

ttaskCmdDispatcher* ttaskCmdDispatcherCreateOfClass(
	ttaskCmdDispatcherClass		*clas
	);

ttaskCmdDispatcher* ttaskCmdDispatcherCreate(
	void
	);

ttaskCmdDispatcher* ttaskCmdDispatcherCreateLinked(
	vobjectAttributed			*target,
	const vname					*cmdname
	);

ttaskCmdDispatcher *ttaskCmdDispatcherCreateOneShot(
	void
	);

const vname* ttaskCmdDispatcherGetContextIdentifier(
	void
	);

ttaskCmdDispatcher *ttaskCmdDispatcherLoad(
	vresource					 resource
	);

ttaskCmdDispatcher *ttaskCmdDispatcherClone(
	ttaskCmdDispatcher				*task
	);

void ttaskCmdDispatcherInitOfClass(
	ttaskCmdDispatcher				*task,
	ttaskCmdDispatcherClass			*clas
	);
	
void ttaskCmdDispatcherInit(
	ttaskCmdDispatcher				*task
	);

void ttaskCmdDispatcherLoadInit(
	ttaskCmdDispatcher				*task,
	vresource					 resource
	);

void ttaskCmdDispatcherCopy(
	ttaskCmdDispatcher				*task,
	ttaskCmdDispatcher				*copy
	);

void ttaskCmdDispatcherCopyInit(
	ttaskCmdDispatcher				*task,
	ttaskCmdDispatcher				*copy
	);

void ttaskCmdDispatcherDestroy(
	ttaskCmdDispatcher				*task
	);

void ttaskCmdDispatcherPost(
	ttaskCmdDispatcher				*task
	);

void ttaskCmdDispatcherSetMinDelay(
	ttaskCmdDispatcher				*task,
	vtimestamp					*min_delay
	);

void ttaskCmdDispatcherAutoDelete(
	ttaskCmdDispatcher				*task,
	unsigned					 suicide
	);

void ttaskCmdDispatcherDescribeAsScribed(
	ttaskCmdDispatcher				*task,
	vscribe						*description
	);

void ttaskCmdDispatcherDescribeAs(
	ttaskCmdDispatcher				*task,
	const vchar					*description
	);

void ttaskCmdDispatcherSetData(
	ttaskCmdDispatcher				*task,
	const void					*rock
	);

const void *ttaskCmdDispatcherGetData(
	ttaskCmdDispatcher				*task
	);

const vchar *ttaskCmdDispatcherGetDescription(
	ttaskCmdDispatcher				*task
	);

vobject *ttaskCmdDispatcherToObject(
	ttaskCmdDispatcher				*task
	);

ttask *ttaskCmdDispatcherToTask(
	ttaskCmdDispatcher				*task
	);

ttaskCmdDispatcherClass *ttaskCmdDispatcherGetClass(
	ttaskCmdDispatcher				*task
	);


/* EXCEPTIONS -------------------------------------------------------------+ 
 */


ttaskStateException *ttaskGetStateException(
	void
	);

void ttaskGenerateState(
	ttask						*task,
	const char					*message
	);

void ttaskGenerateStateNoMessage(
	ttask						*task
	);

const vexClass *ttaskGetStateExceptionClass(
	void
	);



/*
 *+------------------------------------------------------------------------+
 * private type definitions (run away!!)
 *+------------------------------------------------------------------------+
 */


/* TTASK ------------------------------------------------------------------+ 
 */

struct ttask {
	vobject			base;				/* base class's object type */
	void		   *trigger;			/* My stuff... */
	unsigned short	completions;
	unsigned short	iterations;
	unsigned short	blocks;
	unsigned short	locks;
	vstr	       *description;
	vtimestamp		period;
	const void	   *rock;
	unsigned int	triggerkind:2;
	unsigned int	delayed:1;
	unsigned int	suicide:1;
};


#define ttaskCLASS(argCLAS, argTASK) \
	vobjectCLASS(argCLAS, argTASK); 									\
	vclassVARIABLE(ttaskDESCRIPTION, const vchar*); 					\
	vclassMETHOD(ttaskPOST, (argTASK*)); 								\
	vclassMETHOD(ttaskEXECUTE, (argTASK*)); 							\
	vclassMETHOD(ttaskEXPIRE, (argTASK*)); 								\
	vclassMETHOD(ttaskFIRE, (argTASK*)); 								\
	vclassMETHOD(ttaskAUTO_DELETE, (argTASK*, unsigned)); 				\
	vclassMETHOD(ttaskBLOCK, (argTASK*, vtimestamp*)); 					\
	vclassMETHOD(ttaskUNBLOCK, (argTASK*)); 							\
	vclassMETHOD(ttaskSET_MAX_ITERATIONS, (argTASK*, unsigned short)); 	\
	vclassMETHOD(ttaskSET_MIN_DELAY, (argTASK*, vtimestamp*)); 			\
	vclassMETHOD(ttaskADVANCE, (argTASK*, unsigned short)); 			\
	vclassMETHOD(ttaskCLEAR_TRIGGER, (argTASK*)); 						\
	vclassMETHOD_RET(ttaskGET_AGAIN, unsigned, (argTASK*)); 			\
	vclassMETHOD(ttaskDESCRIBE_AS, (argTASK*, vscribe*)); 				\
	vclassMETHOD_RET(ttaskGET_DESCRIPTION, const vchar*, (argTASK*)); 	\
	vclassMETHOD(ttaskSET_DATA, (argTASK*, const void*))

struct ttaskClass {
	ttaskCLASS(ttaskClass, ttask);
};



/* TTASK EXTERNAL PROC CALLER ---------------------------------------------+ 
 */



typedef struct _ttaskExternalProc _ttaskExternalProc;

struct ttaskExternal {
	ttask				base;			/* Base class's object type */
	_ttaskExternalProc	*b, *e, *x;		/* My Stuff... */
	unsigned			aborted:1;
};


#define ttaskExternalCLASS(argCLAS, argETASK) \
	ttaskCLASS(argCLAS, argETASK); 											\
	vclassVARIABLE(ttaskExternalBREAK_STATUS, unsigned); 					\
	vclassMETHOD(ttaskExternalADD, 											\
		(argETASK*, ttaskExternalProcPtr, const void*, const vchar*)); 		\
	vclassMETHOD(ttaskExternalREMOVE, (argETASK*, ttaskExternalProcPtr)); 	\
	vclassMETHOD_RET(ttaskExternalPEEK, ttaskExternalProcPtr, (argETASK*)); \
	vclassMETHOD_RET(ttaskExternalGET_BREAK_STATUS, unsigned, (argETASK*)); \
	vclassMETHOD(ttaskExternalNOTE_ERROR, 									\
		(argETASK*, ttaskExternalProcPtr, const void *, const vchar*)); 	\
	vclassMETHOD(ttaskExternalCALL_ALL, (argETASK*))
	
struct ttaskExternalClass {
	ttaskExternalCLASS(ttaskExternalClass, ttaskExternal);
};



/* TTASK COMMAND DISPATCHER -----------------------------------------------+ 
 */



struct ttaskCmdDispatcher {
	ttask					 base;		/* Base class's object type */
	vobjectAttributed	   	*target;	/* My Stuff... */
	const vname				*cmdname;
};


#define ttaskCmdDispatcherCLASS(argCLAS, argDTASK) \
	ttaskCLASS(argCLAS, argDTASK); 												\
	vclassMETHOD(ttaskCmdDispatcherMAKE_CONTEXT, (argDTASK*, vdict*)); 			\
	vclassMETHOD(ttaskCmdDispatcherSET_COMMAND_NAME, (argDTASK*, const vname*));\
	vclassMETHOD(ttaskCmdDispatcherSET_TARGET, (argDTASK*, vobjectAttributed*));\
	vclassMETHOD(ttaskCmdDispatcherNOTE_ERROR, (argDTASK*)); 					\
	vclassMETHOD_RET(ttaskCmdDispatcherGET_TARGET, vobjectAttributed*, (argDTASK*))

struct ttaskCmdDispatcherClass {
	ttaskCmdDispatcherCLASS(ttaskCmdDispatcherClass, ttaskCmdDispatcher);
};


/*
 *+------------------------------------------------------------------------+
 * private macro definitions
 *+------------------------------------------------------------------------+
 */


/* TTASK ------------------------------------------------------------------+ 
 */

/* 
 * This will be used to track blocking/unblocking (which, if not used
 * properly, can cause lots o' problems...)
 * An example of writing a distince "Debug" version for tracing...
 */
#if (vdebugDEBUG)
extern void _ttaskBlockDBG(ttask*, vtimestamp*, const char*, int);
extern void _ttaskUnBlockDBG(ttask*, const char*, int);
#endif

/*
 * Macros definitions for "Public" interface
 */
#define ttaskToObject(tt)			(&(tt)->base)
#define ttaskGetTag(tt)				vobjectGetTag(ttaskToObject(tt))
#define ttaskGetClass(tt)			((ttaskClass*)vobjectGetClass(&(tt)->base))
#define ttaskSend(tt,m,a)			vclassSend(ttaskGetClass(tt),m,a)
#define ttaskCreateOfClass(c)		((ttask*)vobjectCreateOfClass((vobjectClass*)(c)))
#define ttaskCreate()				ttaskCreateOfClass(ttaskGetDefaultClass())
#define ttaskCreateOneShot()		ttaskCreateOneShotOfClass(ttaskGetDefaultClass())
#define ttaskClone(tt)				((ttask*)vobjectClone(&(tt)->base))
#define ttaskDestroy(tt)			ttaskSend(tt, vinstanceDESTROY, (tt))

#define ttaskLoad(r)				((ttask*)vobjectLoad(r))
#define ttaskLoadInit(tt,r)			vobjectLoadInit(&(tt)->base, r)
#define ttaskInitOfClass(tt,c)		vobjectInitOfClass(&(tt)->base, (vobjectClass*)(c))
#define ttaskInit(tt)				ttaskInitOfClass(tt, ttaskGetDefaultClass())
#define ttaskDestroyLater(tt)		vobjectDestroyLater(&(tt)->base)
#define ttaskCopyInit(tt,dup)		vobjectCopyInit(&(tt)->base, &(dup)->base)
#define ttaskCopy(tt,dup)			ttaskSend(tt, vobjectCOPY, (tt,dup))
#define ttaskStore(tt,r)			ttaskSend(tt, vobjectSTORE, (tt,r))

#define ttaskPost(tt)				ttaskSend(tt, ttaskPOST, (tt))
#define ttaskFire(tt)				ttaskSend(tt, ttaskFIRE, (tt))
#define ttaskAutoDelete(tt,b)		ttaskSend(tt, ttaskAUTO_DELETE, (tt,b))
#define ttaskSetMaxIterations(tt,n)	ttaskSend(tt, ttaskSET_MAX_ITERATIONS, (tt,n))
#define ttaskSetMinDelay(tt,tm)		ttaskSend(tt, ttaskSET_MIN_DELAY, (tt,tm))
#define ttaskDescribeAsScribed(tt,sc) ttaskSend(tt, ttaskDESCRIBE_AS, (tt,sc))
#define ttaskDescribeAs(tt,ch)		ttaskSend(tt, ttaskDESCRIBE_AS, (tt, ch ? vcharScribe(ch) : NULL))
#define ttaskSetData(tt,d)			ttaskSend(tt, ttaskSET_DATA, (tt,d))

#if (vdebugDEBUG)
#define ttaskBlock(tt, tm)			_ttaskBlockDBG(tt, tm, __FILE__, __LINE__)
#define ttaskUnBlock(tt)			_ttaskUnBlockDBG(tt, __FILE__, __LINE__)
#else
#define ttaskBlock(tt, tm)			ttaskSend(tt, ttaskBLOCK, (tt,tm))
#define ttaskUnBlock(tt)			ttaskSend(tt, ttaskUNBLOCK, (tt))
#endif

#define ttaskGetMaxIterations(tt)	((tt)->iterations)
#define ttaskGetCompletions(tt)		((tt)->completions)
#define ttaskGetRemaining(tt)		((tt)->trigger ? 0 : (tt)->iterations-(tt)->completions)
#define ttaskIsFinished(tt)			(!ttaskAgain(tt))
#define ttaskIsBlocked(tt)			((tt)->blocks>0)
#define ttaskIsUnblocked(tt)		(!ttaskIsBlocked(tt))
#define ttaskGetDescription(tt)		ttaskSend(tt, ttaskGET_DESCRIPTION, (tt))
#define ttaskGetData(tt)			((tt)->rock)
#define ttaskGetMinDelayTimestamp(tt) ((tt)->period)


/*
 * Macros definitions for "Protected" interface
 */
#define ttaskClearTrigger(tt)		ttaskSend(tt, ttaskCLEAR_TRIGGER, (tt))
#define ttaskAdvance(tt,n)			ttaskSend(tt, ttaskADVANCE, (tt,n))
#define ttaskAgain(tt)				ttaskSend(tt, ttaskGET_AGAIN, (tt))
#define ttaskExpire(tt)				ttaskSend(tt, ttaskEXPIRE, (tt))
#define ttaskExecute(tt)			ttaskSend(tt, ttaskEXECUTE, (tt))

#define ttaskOf(it)					((ttask*)(it))
#define ttaskIsLocked(tt)			((tt)->locks)




/* TTASK EXTERNAL PROC CALLER ---------------------------------------------+ 
 */


/* 
 * This will be used to track removal of procedure from the task's list
 * An example of writing a distince "Debug" version for tracing...
 */
#if (vdebugDEBUG)
extern void _ttaskExternalRemoveDBG(ttaskExternal*, ttaskExternalProcPtr, const char*, int);
#endif

/*
 * Macros definitions for "Public" interface
 */
#define ttaskExternalToObject(tt)		ttaskToObject(&(tt)->base)
#define ttaskExternalToTask(tt)			(&(tt)->base)
#define ttaskExternalGetTag(tt)			ttaskGetTag(&(tt)->base)
#define ttaskExternalGetClass(tt)		((ttaskExternalClass*)ttaskGetClass(&(tt)->base))
#define ttaskESend(tt,m,a)				vclassSend(ttaskExternalGetClass(tt),m,a)
#define ttaskExternalCreateOfClass(c)	((ttaskExternal*)ttaskCreateOfClass((ttaskClass*)(c)))
#define ttaskExternalCreate()			ttaskExternalCreateOfClass(ttaskExternalGetDefaultClass())
#define ttaskExternalDestroy(tt)		ttaskESend(tt, vinstanceDESTROY, (tt))

#define ttaskExternalAdd(tt,fn,d,id)		ttaskESend(tt, ttaskExternalADD, (tt,fn,d,id))
#define ttaskExternalCallAll(tt)			ttaskESend(tt, ttaskExternalCALL_ALL, (tt))
#define ttaskExternalNextWaiting(tt)		ttaskESend(tt, ttaskExternalPEEK, (tt))
#define ttaskExternalBreakProcError(tt)		ttaskESend(tt, ttaskExternalGET_BREAK_STATUS, (tt))
#define ttaskExternalNoteError(tt,fn,d,id) 	ttaskESend(tt, ttaskExternalNOTE_ERROR, (tt,fn,d,id))

#if (vdebugDEBUG)
#define ttaskExternalRemoveFirst(tt,fn)	   _ttaskExternalRemoveDBG(tt, fn, __FILE__, __LINE__)
#else
#define ttaskExternalRemoveFirst(tt,fn)		ttaskESend(tt, ttaskExternalREMOVE, (tt,fn))
#endif

#define ttaskExternalGetDescription(tt)			ttaskESend(tt, ttaskGET_DESCRIPTION, (tt))
#define ttaskExternalPost(tt)					ttaskESend(tt, ttaskPOST, (tt))
#define ttaskExternalAutoDelete(tt,b)			ttaskESend(tt, ttaskAUTO_DELETE, (tt,b))
#define ttaskExternalSetMaxIterations(tt,n)		ttaskESend(tt, ttaskSET_MAX_ITERATIONS, (tt,n))
#define ttaskExternalSetMinDelay(tt,tm)			ttaskESend(tt, ttaskSET_MIN_DELAY, (tt,tm))
#define ttaskExternalDescribeAsScribed(tt,sc) 	ttaskESend(tt, ttaskDESCRIBE_AS, (tt,sc))
#define ttaskExternalDescribeAs(tt,ch)			ttaskESend(tt, ttaskDESCRIBE_AS, (tt, ch ? vcharScribe(ch) : NULL))
#define ttaskExternalSetData(tt,d)				ttaskESend(tt, ttaskSET_DATA, (tt,d))
#define ttaskExternalGetData(tt)				ttaskGetData(&(tt)->base)

/*
 * Macros definitions for "Protected" interface
 */
#define ttaskExternalExecute(tt)			ttaskESend(tt, ttaskEXECUTE, (tt))



/* TTASK COMMAND DISPATCHER -----------------------------------------------+ 
 */


/*
 * Macros definitions for "Public" interface
 */
#define ttaskCmdDispatcherToObject(tt)		ttaskToObject(&(tt)->base)
#define ttaskCmdDispatcherToTask(tt)		(&(tt)->base)
#define ttaskCmdDispatcherGetTag(tt)		ttaskGetTag(&(tt)->base)
#define ttaskCmdDispatcherGetClass(tt)		((ttaskCmdDispatcherClass*)ttaskGetClass(&(tt)->base))

#define ttaskCDSend(tt,m,a)					vclassSend(ttaskCmdDispatcherGetClass(tt),m,a)
#define ttaskCmdDispatcherCreateOfClass(c)	((ttaskCmdDispatcher*)ttaskCreateOfClass((ttaskClass*)(c)))
#define ttaskCmdDispatcherCreate()			ttaskCmdDispatcherCreateOfClass(ttaskCmdDispatcherGetDefaultClass())
#define ttaskCmdDispatcherCreateOneShot()	((ttaskCmdDispatcher*)ttaskCreateOneShotOfClass(ttaskCmdDispatcherGetDefaultClass()))
#define ttaskCmdDispatcherDestroy(tt)		ttaskCDSend(tt, vinstanceDESTROY, (tt))

#define ttaskCmdDispatcherGetDescription(tt)		ttaskCDSend(tt, ttaskGET_DESCRIPTION, (tt))
#define ttaskCmdDispatcherPost(tt)					ttaskCDSend(tt, ttaskPOST, (tt))
#define ttaskCmdDispatcherAutoDelete(tt,b)			ttaskCDSend(tt, ttaskAUTO_DELETE, (tt,b))
#define ttaskCmdDispatcherSetMaxIterations(tt,n) 	ttaskCDSend(tt, ttaskSET_MAX_ITERATIONS, (tt,n))
#define ttaskCmdDispatcherSetMinDelay(tt,tm)		ttaskCDSend(tt, ttaskSET_MIN_DELAY, (tt,tm))
#define ttaskCmdDispatcherDescribeAsScribed(tt,sc)	ttaskCDSend(tt, ttaskDESCRIBE_AS, (tt,sc))
#define ttaskCmdDispatcherDescribeAs(tt,ch)			ttaskCDSend(tt, ttaskDESCRIBE_AS, (tt, ch ? vcharScribe(ch) : NULL))
#define ttaskCmdDispatcherSetData(tt,d)				ttaskCDSend(tt, ttaskSET_DATA, (tt,d))
#define ttaskCmdDispatcherGetData(tt)				ttaskGetData(&(tt)->base)

#define ttaskCmdDispatcherSetName(tt,vc)		ttaskCDSend(tt, ttaskCmdDispatcherSET_COMMAND_NAME, (tt,vc))
#define ttaskCmdDispatcherSetTarget(tt,t)		ttaskCDSend(tt, ttaskCmdDispatcherSET_TARGET, (tt,t))
#define ttaskCmdDispatcherNoteError(tt)			ttaskCDSend(tt, ttaskCmdDispatcherNOTE_ERROR, (tt))
#define ttaskCmdDispatcherDetermineTarget(tt)	ttaskCDSend(tt, ttaskCmdDispatcherGET_TARGET, (tt))


/*
 * Macros definitions for "Protected" interface
 */
#define ttaskCmdDispatcherExecute(tt)			ttaskCDSend(tt, ttaskEXECUTE, (tt))
#define ttaskCmdDispatcherMakeContext(tt,d)		ttaskCDSend(tt, ttaskCmdDispatcherMAKE_CONTEXT, (tt,d))



/* EXCEPTIONS -------------------------------------------------------------+ 
 */
 
enum {
	ttaskMAX_NAME = 24
};

struct ttaskStateException {
	vexValueException		base;						/* Base class's object */
	vchar				    taskname[ttaskMAX_NAME];	/* task's description */
};

extern vexClass __ttaskStateExceptionClass;		/* Global class variable */
extern void ttaskStateTASK(void*, va_list*);			/* Our "ArgEater" */


#define ttaskGetStateExceptionClass() 				\
	(&__ttaskStateExceptionClass)
#define ttaskGetStateException()					\
	vexGetExceptionOfClass(ttaskGetStateExceptionClass())
#define ttaskGenerateState(tt, msg)					\
	vexGenerate(ttaskGetStateExceptionClass(), 		\
				vexMESSAGE, msg, vexERRNO, 0, 		\
				ttaskStateTASK, tt, vexNULL)
#define ttaskGenerateStateNoMessage(tt)				\
	vexGenerate(ttaskGetStateExceptionClass(), 		\
				ttaskStateTASK, tt, vexERRNO, 0, 	\
				 vexNULL)


/* ttaskINCLUDED */
#endif


/*
 *+------------------------------------------------------------------------+
 * emacs editor formatting information:
 *+------------------------------------------------------------------------+
 */

/*
 * Local Variables:
 * c-indent-level:4
 * c-continued-statement-offset:4
 * c-brace-offset:0
 * c-brace-imaginary-offset:0
 * c-argdecl-indent:5
 * c-label-offset:0
 * c-tab-always-indent:nil
 * tab-stop-list:(4 8 12 16 20 24 28 32 36 40 44 48 52 56 64 72 80 88 96 104)
 * tab-width:4
 * indent-tabs-mode:t
 * truncate-lines:t
 * End:
 */

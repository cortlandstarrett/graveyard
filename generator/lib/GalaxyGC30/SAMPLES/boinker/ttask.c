/* $Id: ttask.c,v 1.6 1996/09/25 21:34:50 alexey Exp $ */
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
 *     o 05-03-95: ssmc, removed sizeof(vchar)==sizeof(char) requirement      *
 *                                                                            *
 * Special Usage Notes:                                                       *
 *     o <none>                                                               *
 *                                                                            *
 * Text Editor Formatting:                                                    *
 *     Symantec: Tab(4), Font(Any Fixed Width)                                *
 *     Emacs: see end of file for info                                        *
 *                                                                            *
 ******************************************************************************
 */

/*
 *+------------------------------------------------------------------------+
 * dependencies:
 *+------------------------------------------------------------------------+
 */

#include <vport.h>
#include vstdlibHEADER
#include vlimitsHEADER
#include vdebugHEADER
#include vexHEADER
#include vscribeHEADER
#include vnameHEADER
#include vresourceHEADER
#include vtimestampHEADER
#include veventHEADER
#include vclientHEADER
#include vtimerHEADER
#include vinstanceHEADER
#include vstdHEADER
#include vclassHEADER
#include vobjectHEADER
#include vcommandHEADER

#include "ttask.h"


/*
 *+------------------------------------------------------------------------+
 * private constants, variables, prototypes
 *+------------------------------------------------------------------------+
 */


#define CLASSNAME    "ttask"
#define ScribeOf(_l) vcharScribeLiteral(_l)


#if (vdebugDEBUG)
static const char *const _debugTag = CLASSNAME;
#define vdebugTAG _debugTag
#endif


enum {
	_NO_KIND = 0x00,
	_TIMER   = 0x01,
	_EVENT   = 0x02
};


typedef struct _ttaskClientGlobals {
	ttaskClass		*defaultClass;
	const vname		*undefined;
}_ttaskClientGlobals;

static void **mGlobals = NULL;
#define mgPtr ((_ttaskClientGlobals*)*mGlobals)
#define taskSendSuper(m,a) vclassSendSuper(mgPtr->defaultClass, m,a)



static void	taskStartupClient(void);
static void taskPost(ttask*);


/*
 *+------------------------------------------------------------------------+
 * public routines
 *+------------------------------------------------------------------------+
 */


/*
 * ttaskGetDefaultClass()
 * return the class mangler's reference for our ttask base class. will
 * auto-initialize the module's global stuffage if necessary...
 * -> void
 * <- class, the ttaskClass reference
 */
ttaskClass*
ttaskGetDefaultClass(void)
{
	if (!mGlobals)
		mGlobals = vclientRegisterModule();
			
	if (!*mGlobals)
		taskStartupClient();

	return mgPtr->defaultClass;
}




/*
 * ttaskCreateOneShotOfClass()
 * overload of the default creation method; create a ttask object
 * that will execute once and auto-delete.
 * -> clas, the task's class
 * <- task, the newly created task
 */
ttask*
ttaskCreateOneShotOfClass(ttaskClass *clas)
{
	ttask *task;
	
	task = ttaskCreateOfClass(clas);
	task->iterations = 1;
	task->suicide = vTRUE;
	
	return task;
}


/*
 *+------------------------------------------------------------------------+
 * private routines - abstract tasks
 *+------------------------------------------------------------------------+
 */

/*
 * taskCommonInit() 
 * does initialization common to both Init() and LoadInit() methods.
 * -> task, the task to init
 * <- void
 */
static void taskCommonInit(register ttask *task)
{
	task->delayed		= vFALSE;
	task->triggerkind	= _NO_KIND;
	task->trigger		= NULL;
	task->blocks		= 0;
	task->locks			= 0;
	task->suicide		= vFALSE;
	task->completions	= 0;
	task->iterations 	= 0;
	task->period        = vtimestampMake(0,0);
	task->description	= NULL;
	task->rock			= NULL;
}





/*
 * taskCommonCopy() 
 * does copy-initialization common to both Copy() and CopyInit() 
 * methods. Overwrites current values (does not free anything).
 * -> from, the task to copy from
 * -> copy, the task to copy to
 * <- void
 */
static void taskCommonCopy(register ttask *from, register ttask *copy)
{
	copy->triggerkind	= from->triggerkind;
	copy->trigger		= NULL;
	copy->delayed		= from->delayed;
	copy->blocks		= 0;
	copy->locks			= 0;
	copy->completions	= 0;
	copy->suicide		= from->suicide;
	copy->iterations	= from->iterations;
	copy->description	= from->description ? vstrClone(from->description) : NULL;
	copy->period		= vtimestampMake(vtimestampGetSeconds(from->period),
		                      vtimestampGetNanoseconds(from->period));
	copy->rock			= from->rock;
}





/*
 * taskInit()
 * initialize a memory-based task object
 * -> task, the task to initialize
 * <- void
 */
static void taskInit(register ttask *task)
{
	taskSendSuper(vinstanceINIT, (task));
	
	taskCommonInit(task);
}




/*
 * taskLoadInit()
 * initialize a resource-based task object
 * -> task, the task to initialize
 * -> res,  the resource from which to get stored values
 * <- void
 */
static void taskLoadInit(register ttask *task, vresource res)
{
	taskSendSuper(vobjectLOAD_INIT, (task, res));
	
	taskCommonInit(task);
}




/*
 * taskCopyInit()
 * initialize a memory-based task object using values from an
 * existing task object.
 * -> from, the task to use
 * -> task, the task to initialize
 * <- void
 */
static void taskCopyInit(register ttask *from, register ttask *task)
{
	taskSendSuper(vobjectCOPY_INIT, (from, task));
	
	taskCommonCopy(from, task);
}




/*
 * taskCopy()
 * reinitialize a task object using values from an existing task 
 * object. unlike CopyInit() assume the task object has already
 * been initialized.
 * -> from, the task to use
 * -> task, the task to initialize
 * <- void
 */
static void taskCopy(register ttask *from, register ttask *task)
{
	if (task->trigger && ttaskIsUnblocked(task))
		vexGenerate(vexGetArgClass(), vexMESSAGE, "copy: overwriting "
					"active task!", vexERRNO, 0, vexNULL);

	taskSendSuper(vobjectCOPY, (from, task));
	
	if (task->trigger)
		ttaskClearTrigger(task);
	
	taskCommonCopy(from, task);
}




/*
 * taskDestroy()
 * free any instance-specific memory; the inherited method will 
 * do the actual object deletion if necessary.
 * -> task, the task to destroy
 * <- void
 */
static void taskDestroy(register ttask *task)
{
	if (task->trigger)
		ttaskClearTrigger(task);

	if (task->description)
		vstrDestroy(task->description);
	
	taskSendSuper(vinstanceDESTROY, (task));
}




/*
 * taskClearTrigger()
 * if the task is active, disable the trigger object (timer/event).
 * this has the effect of deactivating the task itself.
 * -> task, the task to deactivate
 * <- void
 */
static void taskClearTrigger(register ttask *task)
{
	if (task->trigger)
		{
			switch (task->triggerkind) {
				case _TIMER:
					vtimerDestroy((vtimer*)task->trigger);
					break;
				case _EVENT:
					veventSetClientData((vevent*)task->trigger, NULL);
					break;
				default:
					vdebugMWarn(("clear-trigger: unknown trigger kind!?\n"));
					break;
			}
				
			task->trigger = NULL;
			task->triggerkind = _NO_KIND;
		}
}




/*
 * taskAdvance()
 * advance the task's completions by a specified count. a task's
 * completion value usually determines if the task is reposted.
 * -> task,  the task
 * -> delta, the additional number of completions
 * <- void
 */
static void taskAdvance(register ttask *task, unsigned short delta)
{
	task->completions += delta;
}




/*
 * taskAgain()
 * determine whether the task should be executed at least one more
 * time.
 * -> task,  the task
 * <- [t/f], true if more iterations, else false
 */
static unsigned taskAgain(register ttask *task)
{
	return (task->completions < task->iterations);
}




/*
 * taskSetMaxIterations()
 * set the maximum number of times this task will execute. a task may
 * execute a total less than the requested maximum (for example if the
 * task is blocked).
 * -> task,  the task
 * -> count, the max iterations
 * <- void
 */
static void taskSetMaxIterations(register ttask *task, unsigned short count)
{
	task->iterations = count;
}




/*
 * taskMakeClientEvent()
 * allocate/initialize a client event for tasks. uses min priority
 * for the event (st. other events like updates can be processed ahead
 * o' us)
 * -> handler, the event handler proc ptr
 * -> data,    untyped data to associated w/ client event
 * <- event,   the new client event
 */
static vevent* taskMakeClientEvent(veventHandlerProc handler, 
								   const void *data)
{
	register vevent *event;
	
	event = veventCreateClient();
	veventSetClientData(event, data);
	veventSetTarget(event, handler);
	veventSetPriority(event, veventPRIORITY_MIN);
	
	return event;
}




/*
 * taskNukeTimer()
 * client event handler that's used to auto-delete task timers
 * -> event, the client event
 * <- TRUE
 */
static int taskNukeTimer(vevent *event)
{
	vtimer *timer = (vtimer*)veventGetClientData(event);

	if (timer)
		vtimerDestroy(timer);

	return vTRUE;
}




/*
 * taskFireTimer()
 * timer notification for timer-based tasks; just calls the task's
 * fire method and if necessary reposts the task.
 * -> timer, our task timer (use data field fer the task)
 * <- void
 */
static void taskFireTimer(register vtimer *timer)
{
	if (vtimerGetData(timer))
		{
			register ttask  *task = (ttask*)vtimerGetData(timer);
			register vevent *event;
			
			ttaskFire(task);
			
			task->trigger = NULL;
			if (ttaskAgain(task))
				{
					unsigned short save = task->completions;
					taskPost(task);
					task->completions = save;
				}
			event = taskMakeClientEvent(taskNukeTimer, timer);
			veventPost( event );
		}
}




/*
 * taskInstallTimer()
 * installs a task timer; used by tasks with an associated minimum
 * delay. Note the timer is not defined to be recurrent; whether a
 * task is reposted is determined after each firing.
 * -> task, the task
 * <- void
 */
static void taskInstallTimer(register ttask *task)
{
	register vtimer	*timer;
	
	timer = vtimerCreate();
	vtimerSetNotify(timer, taskFireTimer);
	vtimerSetData(timer, task);
	
	vtimerSetPeriod(timer, vtimestampGetSeconds(task->period), 
		vtimestampGetNanoseconds(task->period));

	task->trigger = timer;
	task->triggerkind = _TIMER;
	
	vtimerStart(timer);
}




/*
 * taskFireEvent()
 * client event handler for event-based tasks. just calls the task's
 * fire method and if necessary reposts the task.
 * -> event, the task client event (use data field for task)
 * <- TRUE
 */
static int taskFireEvent(vevent *event)
{
	if (veventGetClientData(event))
		{
			register ttask  *task = (ttask*)veventGetClientData(event);

			ttaskFire(task);

			if (!ttaskAgain(task))
				task->trigger = NULL;
			else
				{
					if (veventGetPriority(event)>veventPRIORITY_MIN)
						veventSetPriority(event, veventPRIORITY_MIN);
					veventPost(event);
				}
		}

	return vTRUE;
}




/*
 * taskInstallEvent()
 * post a client event; used by tasks with NO associated minimum
 * delay. After each firing a task is reposted if necessary. Note
 * the first time a event-based task is fired we use "default" 
 * event priority instead of minimum; each subsequent firing is
 * done at minimum priority.
 * -> task, the task
 * <- void
 */
static void taskInstallEvent(register ttask *task)
{
	register vevent *event;
	
	event = taskMakeClientEvent(taskFireEvent, task);
	veventSetPriority(event, veventPRIORITY_DEFAULT);

	task->trigger = event;
	task->triggerkind = _EVENT;
	
	veventPost(event);
}




/*
 * taskNuke()
 * client event handler used to auto-delete tasks
 * -> event, the client event
 * <- TRUE
 */
static int taskNuke(vevent *event)
{
	ttask *task = (ttask*)veventGetClientData(event);

	if (task)
		ttaskDestroy(task);

	return vTRUE;
}




/*
 * taskPost()
 * post a task for execution. If the task's max iterations is not
 * greater than 0, the task will never fire. A posted task
 * will always return to the event loop at least once. It is an
 * exception to post a task that is currently active (ie. has been
 * posted and has not completed).
 * -> task, the task to post
 * <- void
 */
static void taskPost(register ttask *task)
{	
	vdebugIF(task->trigger, vexGenerate(vexGetValueNullClass(), vexMESSAGE,
	        "post: non-NULL trigger!?", vexERRNO, 0, vexNULL));
	
	task->completions = 0;

	if (task->completions<task->iterations)
		if (task->delayed)
			taskInstallTimer(task);
		else
			taskInstallEvent(task);
	else
	if (task->suicide)
	{
		vevent* event;
		
		event = taskMakeClientEvent(taskNuke, task);
		veventPost(event);
	}
}




/*
 * taskFire()
 * try to execute a task. If the task is currently blocked, it will be
 * expire (silently). if a task has multiple iterations, the completion
 * count is incremented by 1 and the task is reposted.
 * -> task, the task to fire
 * <- void
 */
static void taskFire(register ttask *task)
{
	task->locks++;
	if (!ttaskIsBlocked(task)) ttaskExecute(task);
	else ttaskExpire(task);
	task->locks--;

	ttaskAdvance(task, 1);
	
	if (!ttaskAgain(task) && task->suicide)
	{
		vevent* event;
		
		event = taskMakeClientEvent(taskNuke, task);
		veventPost(event);
	}
}




/*
 * taskExpire()
 * a task as fired while it's blocked. do what (if any) special
 * processing for this case...
 * -> task, the task
 * <- void
 */
static void taskExpire(register ttask *task)
{
#if vdebugDEBUG
	vscribe *scribe;

	scribe = vcharScribeFormatLiteral
		("expire: the task %s has expired\n", ttaskGetDescription(task));

	vcharDumpScribed(scribe, vdebugGetWarningStream());
#endif
}




/*
 * taskExecute()
 * do whatever work this task's was designed to accomplish -- this method
 * must be overridden!
 * -> task, the task
 * <- void
 */
static void taskExecute(register ttask *task)
{
#if vdebugDEBUG
	vscribe *scribe;

	scribe = vcharScribeFormatLiteral
		("execute: for the task %s should be overridden!\n", 
		 ttaskGetDescription(task));

	vcharDumpScribed(scribe, vdebugGetWarningStream());
#endif
}




/*
 * taskAutoDelete()
 * sets the task's auto deletion attributed (t/f). If a task is set
 * to auto delete, it will destroy itself after completion
 * -> task, the task
 * -> zap,  true for auto delete, else fals
 * <- void
 */
static void taskAutoDelete(register ttask *task, unsigned zap)
{
	task->suicide = zap ? 1 : 0;
}




/*
 * taskBlock()
 * block a task indefinitely or for a specified period of time. a blocked 
 * task continues to fire at the appropriate times, but will not execute
 * any work (silently expires). _ttaskBlockDBG is a debug version that 
 * includes additional file/line information for tracing purposes.
 * -> task, the task to block
 * -> time, NULL for indefinite blockage, or the amount of time
 *          to block fer
 * <- void
 */
static void taskBlock(register ttask *task, vtimestamp *duration)
{
	vdebugMessagedAssert((task->blocks<USHRT_MAX), "block: too many blocks");
	task->blocks++;
}


#if (vdebugDEBUG)

void _ttaskBlockDBG(register ttask *task, vtimestamp *duration,
					const char *file, int line)
{
	if (task->blocks==USHRT_MAX)
		vexGenerate(vexGetValueRangeClass(), vexMESSAGE,
			"block: too many blocks!", vexERRNO, 0, vexFILE, file, 
			vexLINE, line, vexNULL);

	if (vdebugActiveAt(vdebugTAG, vdebugGetInfoLevel()))
		{
			register FILE *fp = vdebugGetInfoStream();
			if (!duration)
			{
				fprintf(fp, "\tIndefinite block installing for 0x%lx; "
						    "file: %s, line: %d\n", 
						task, file, line);
			}
			else
			{
				fprintf(fp, "\tTimed block installing for 0x%lx; "
							"file: %s, line: %d\n",
						task, file, line);
				fprintf(fp, "\t    secs: %l, nanos: %lu\n", 
						vtimestampGetSeconds(*duration), 
						vtimestampGetNanoseconds(*duration));
			}
			fflush(fp);
		}

	ttaskSend(task, ttaskBLOCK, (task,duration));
}
#endif




/*
 * taskUnBlock()
 * unblocks a task. a blocked task continues to fire at the appropriate 
 * times, but will not execute any work (silently expires). _ttaskUnBlockDBG 
 * is a debug version that includes additional file/line information for 
 * tracing purposes.
 * -> task, the task
 * <- void
 */
static void taskUnBlock(register ttask *task)
{
	vdebugMessagedAssert((task->blocks>0), "unblock: no blocks!");
	task->blocks--;
}


#if (vdebugDEBUG)

void _ttaskUnBlockDBG(register ttask *task, const char *file, int line)
{
	if (!task->blocks)
		vexGenerate(vexGetValueNullClass(), vexMESSAGE,
			"unblock: no blocks!", vexERRNO, 0, vexFILE, file, 
			vexLINE, line, vexNULL);

	if (vdebugActiveAt(vdebugTAG, vdebugGetInfoLevel()))
		{
			fprintf(vdebugGetInfoStream(), "\tBlock unstalling for 0x%lx; "
					"file: %s, line: %d\n", task, file, line);
			fflush(vdebugGetInfoStream());
		}

	ttaskSend(task, ttaskUNBLOCK, (task));
}

#endif




/*
 * taskSetMinDelay()
 * sets the minimum time delay between firings of the task. If NULL
 * there will be no user-specified delay (there is always the delay of
 * returning to an event loop).
 * -> task, the task
 * -> time, NULL for no delay, or the minimum time delay between
 *          firings
 * <- void
 */
static void taskSetMinDelay(register ttask *task, vtimestamp* delay)
{
	vtimestamp zero;

	zero = vtimestampMake(0,0);

#if (vdebugDEBUG)
	if (task->trigger && (task->triggerkind == _TIMER))
		vdebugMWarn(("set-min-delay: called while task active!\n"));
#endif

	if (delay && !vtimestampEqualTo(*delay, zero))
		{
			task->period  = *delay;
			task->delayed = vTRUE;
		}
	else
		{
			task->period  = zero;
			task->delayed = vFALSE;
		}
}




/*
 * taskDescribeAs()
 * assign a user-readable description to the task; this description
 * can be used in status items, error notices, etc.
 * -> task,   the task
 * -> scribe, the description scribe (can be NULL)
 * <- void
 */
static void taskDescribeAs(register ttask *task, vscribe *scribe)
{
	if (task->description)
		{
			vstrDestroy(task->description);
			task->description= NULL;
		}
	
	if (scribe)
		task->description = vstrCloneScribed(scribe);
}




/*
 * taskGetDescription()
 * returns a user-readable description of the task. will never return
 * NULL. if the task does not have a instance-level description, will
 * use the class description.
 * -> task, the task
 * <- description
 */
static const vchar *taskGetDescription(register ttask *task)
{
	register const vchar *it;

	it = task->description;
	if (!it)
		it = vclassGet(ttaskGetClass(task), ttaskDESCRIPTION);
	if (!it)
		it = mgPtr->undefined;
	
	return it;
}




/*
 * taskSetRock()
 * remember a untyped user-specified data reference (or a rock).
 * -> task, the task
 * -> rock, the untyped data
 * <- void
 */
static void taskSetRock(register ttask *task, const void *rock)
{
	task->rock = rock;
}




/*
 * taskStartupClient()
 * initialize our client mangler stuff; register our subclasses (not
 * global classes).
 * -> void
 * <- void
 */
static void taskStartupClient(void)
{
	register ttaskClass	*clas;

	vclientAllocateModule(mGlobals, sizeof(_ttaskClientGlobals));

	mgPtr->undefined = vnameInternGlobalLiteral("stuff...");

	clas = vclassSpawn(vobjectGetDefaultClass(), sizeof(ttaskClass));
	vclassSetObjectSize(clas, sizeof(ttask));
	vclassSetNameScribed(clas, ScribeOf(CLASSNAME));

	vclassSet(clas, vinstanceINIT, taskInit);
	vclassSet(clas, vinstanceDESTROY, taskDestroy);
	vclassSet(clas, vobjectLOAD_INIT, taskLoadInit);
	vclassSet(clas, vobjectCOPY, taskCopy);
	vclassSet(clas, vobjectCOPY_INIT, taskCopyInit);
	
	vclassSet(clas, ttaskPOST, taskPost);
	vclassSet(clas, ttaskEXECUTE, taskExecute);
	vclassSet(clas, ttaskEXPIRE, taskExpire);
	vclassSet(clas, ttaskFIRE, taskFire);
	vclassSet(clas, ttaskAUTO_DELETE, taskAutoDelete);
	vclassSet(clas, ttaskBLOCK, taskBlock);
	vclassSet(clas, ttaskUNBLOCK, taskUnBlock);
	vclassSet(clas, ttaskSET_MAX_ITERATIONS, taskSetMaxIterations);
	vclassSet(clas, ttaskSET_MIN_DELAY, taskSetMinDelay);
	vclassSet(clas, ttaskADVANCE, taskAdvance);
	vclassSet(clas, ttaskCLEAR_TRIGGER, taskClearTrigger);
	vclassSet(clas, ttaskGET_AGAIN, taskAgain);
	vclassSet(clas, ttaskDESCRIBE_AS, taskDescribeAs);
	vclassSet(clas, ttaskGET_DESCRIPTION, taskGetDescription);
	vclassSet(clas, ttaskDESCRIPTION, NULL);
	vclassSet(clas, ttaskSET_DATA, taskSetRock);
	
	mgPtr->defaultClass = clas;
}


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

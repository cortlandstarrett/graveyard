/* $Id: dtask.c,v 1.3 1996/08/21 15:39:54 david Exp $ */
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
#include vclientHEADER
#include vinstanceHEADER
#include vstdHEADER
#include vclassHEADER
#include vobjectHEADER
#include vcommandHEADER
#include vapplicationHEADER

#include "ttask.h"


/*
 *+------------------------------------------------------------------------+
 * private constants, variables, prototypes
 *+------------------------------------------------------------------------+
 */

#define CLASSNAME "ttaskCmdDispatcher"


#if (vdebugDEBUG)
static const char *const _debugTag = CLASSNAME;
#define vdebugTAG _debugTag
#endif


#define TAG(_l)	vnameInternGlobalLiteral(_l)


typedef struct _ttaskClientGlobals {
	ttaskCmdDispatcherClass  *defaultClass;
	const vname				 *contextId;
}_ttaskClientGlobals;

static void **mGlobals = NULL;
#define mgPtr ((_ttaskClientGlobals*)*mGlobals)
#define taskSendSuper(m,a) vclassSendSuper(mgPtr->defaultClass, m,a)


static void	taskStartupClient(void);


/*
 *+------------------------------------------------------------------------+
 * public routines
 *+------------------------------------------------------------------------+
 */


ttaskCmdDispatcherClass*
ttaskCmdDispatcherGetDefaultClass(void)
{
	if (!mGlobals)
		mGlobals = vclientRegisterModule();
	if (!*mGlobals)
		taskStartupClient();

	return mgPtr->defaultClass;
}



/* */
const vname *
ttaskCmdDispatcherGetContextIdentifier(void)
{
	if (!mGlobals || !*mGlobals)
		(void)ttaskCmdDispatcherGetDefaultClass();
	
	return mgPtr->contextId;
}



/* */
ttaskCmdDispatcher*
ttaskCmdDispatcherCreateLinked(vobjectAttributed *target, const vname *cmdname)
{
	ttaskCmdDispatcher *task;

	if (target && !vobjectIsKindOf(target, vobjectGetDefaultAttributedClass()))
		vexGenerate(vexGetArgClass(), vexMESSAGE, 
				    "create-linked: target not kind-of vobjectAttributed!",
				    vexERRNO, 0, vexNULL);
	
	task = ttaskCmdDispatcherCreate();
	task->target  = target;
	task->cmdname = cmdname;
	
	return task;
}
	



/*
 *+------------------------------------------------------------------------+
 * private definition: ttaskCmdDispatcher
 *+------------------------------------------------------------------------+
 */



/* */
static void taskCommonInit(register ttaskCmdDispatcher *task)
{
	task->target  = NULL;
	task->cmdname = NULL;
}




/* */
static void taskCommonCopy(register ttaskCmdDispatcher *from, 
						   register ttaskCmdDispatcher *copy)
{
	copy->target  = from->target;
	copy->cmdname = from->cmdname;
}




/* */
static void taskSetCommandName(register ttaskCmdDispatcher *task,
							   const vname *cmdname)
{
	task->cmdname = cmdname;
}




/* */
static void taskSetTarget(register ttaskCmdDispatcher *task, 
						  vobjectAttributed *target)
{
	if (target && !vobjectIsKindOf(target, vobjectGetDefaultAttributedClass()))
		vexGenerate(vexGetArgClass(), vexMESSAGE, 
				    "set-target: target not kind-of vobjectAttributed!",
				    vexERRNO, 0, vexNULL);
	
	task->target = target;
}




/* */
static vobjectAttributed* taskGetTarget(register ttaskCmdDispatcher *task)
{
	return task->target ? task->target 
					 : vapplicationGetObject(vapplicationGetCurrent());
}




/* */
static void taskMakeContext(register ttaskCmdDispatcher *task,
							register vdict *context)
{
	vobjectAttributed *target;

	vdebugIF(!context, vexGenerate(vexGetArgNullClass(), vexMESSAGE,
			 "make-context: NULL context!", vexERRNO, 0, vexNULL));

	if (!task->cmdname || !*task->cmdname)
		vexGenerate(vexGetValueNullClass(), vexMESSAGE, 
					"make-context: invalid command name", vexERRNO, 0, 
					vexNULL);

	target = ttaskCmdDispatcherDetermineTarget(task);

	vobjectGetContextAttributes(target, context);
	vobjectGetAllAttributes(target, context);

	vdictStore(context, vname_Tag, task->cmdname);
	vdictStore(context, mgPtr->contextId, task);
}




/* */
static void taskExecute(register ttaskCmdDispatcher *task)
{
	if (task->cmdname && *task->cmdname)
		{
			vdict context;
			vdictInit(&context, vnameHash);
			vexWITH_HANDLING
			{
				ttaskCmdDispatcherMakeContext(task, &context);
				(void)vobjectIssueCommand
					(ttaskCmdDispatcherDetermineTarget(task), 
					 task->cmdname, &context);
				vdictDestroy(&context);
			}
			vexON_EXCEPTION
			{
				vdictDestroy(&context);
				ttaskCmdDispatcherNoteError(task);
			}
			vexEND_HANDLING;
		}
}




/* */
static void taskInit(register ttaskCmdDispatcher *task)
{
	taskSendSuper(vinstanceINIT, (task));
	
	taskCommonInit(task);
}




/* */
static void taskLoadInit(register ttaskCmdDispatcher *task, vresource res)
{
	taskSendSuper(vobjectLOAD_INIT, (task, res));
	
	taskCommonInit(task);

	if (!vresourceTestGetTag(res, mgPtr->contextId, &task->cmdname)
		&& ttaskCmdDispatcherGetTag(task))
		task->cmdname = ttaskCmdDispatcherGetTag(task);
}




/* */
static void taskCopyInit(ttaskCmdDispatcher *from, ttaskCmdDispatcher *task)
{
	taskSendSuper(vobjectCOPY_INIT, (from, task));
	
	taskCommonCopy(from, task);
}




/* */
static void taskCopy(ttaskCmdDispatcher *from, ttaskCmdDispatcher *task)
{
	taskSendSuper(vobjectCOPY, (from, task));
		
	taskCommonCopy(from, task);
}




/* */
static void taskStore(ttaskCmdDispatcher *task, vresource res)
{
	taskSendSuper(vobjectSTORE, (task,res));
	
	if (task->cmdname && task->cmdname!=vnameNULL)
		vresourceSetTag(res, mgPtr->contextId, task->cmdname);
	else
		vresourceRemoveIfExists(res, mgPtr->contextId);
}




/* */
static void taskNoteError(ttaskCmdDispatcher *task)
{
	vdebugMWarn(("execute: task (0x%lx) has failed\n", task));
}




/* */
static void taskStartupClient(void)
{
	register ttaskCmdDispatcherClass	*clas;

	vclientAllocateModule(mGlobals, sizeof(_ttaskClientGlobals));

	clas = vclassSpawn(ttaskGetDefaultClass(), sizeof(ttaskCmdDispatcherClass));
	vclassSetObjectSize(clas, sizeof(ttaskCmdDispatcher));
	vclassSetNameScribed(clas, vcharScribeLiteral(CLASSNAME));

	vclassSet(clas, vinstanceINIT, taskInit);
	vclassSet(clas, vobjectLOAD_INIT, taskLoadInit);
	vclassSet(clas, vobjectCOPY, taskCopy);
	vclassSet(clas, vobjectCOPY_INIT, taskCopyInit);
	vclassSet(clas, vobjectSTORE, taskStore);

	vclassSet(clas, ttaskEXECUTE, taskExecute);

	vclassSet(clas, ttaskCmdDispatcherMAKE_CONTEXT, taskMakeContext);
	vclassSet(clas, ttaskCmdDispatcherSET_COMMAND_NAME, taskSetCommandName);
	vclassSet(clas, ttaskCmdDispatcherSET_TARGET, taskSetTarget);
	vclassSet(clas, ttaskCmdDispatcherNOTE_ERROR, taskNoteError);
	vclassSet(clas, ttaskCmdDispatcherGET_TARGET, taskGetTarget);
	
	mgPtr->defaultClass = clas;
	mgPtr->contextId = TAG("ttaskDispatcher");
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

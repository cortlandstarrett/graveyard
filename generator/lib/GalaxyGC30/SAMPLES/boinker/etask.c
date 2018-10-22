/* $Id: etask.c,v 1.6 1996/08/21 15:40:53 david Exp $ */
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

#include "ttask.h"


/*
 *+------------------------------------------------------------------------+
 * private constants, variables, prototypes
 *+------------------------------------------------------------------------+
 */


#define CLASSNAME "ttaskExternal"


#if (vdebugDEBUG)
static const char *const _debugTag = CLASSNAME;
#define vdebugTAG _debugTag
#endif

enum {
	_BLK = 4
};


struct _ttaskExternalProc {
	ttaskExternalProcPtr	fn;
	const void		   		*data;
	const vchar		   		*id;
};


typedef struct _ttaskClientGlobals {
	ttaskExternalClass		*defaultClass;
}_ttaskClientGlobals;

static void **mGlobals = NULL;
#define mgPtr ((_ttaskClientGlobals*)*mGlobals)
#define taskSendSuper(m,a) vclassSendSuper(mgPtr->defaultClass, m,a)
#define taskNonNil(t) ((!(t)->aborted) && (t)->b && ((t)->e>(t)->b))


static void	taskStartupClient(void);


/*
 *+------------------------------------------------------------------------+
 * doing the exceptional thang...
 *+------------------------------------------------------------------------+
 */

void ttaskStateTASK(void *generic, va_list *ap)
{
	register ttaskStateException *tse =
		(ttaskStateException*)generic;

	ttask *task = va_arg(*ap, ttask*);

	vchar *cp = vcharCopyBounded
		(ttaskGetDescription(task), tse->taskname, ttaskMAX_NAME-1);
	*cp = vcharNULL;
}


static void ttaskStateDumper(void *generic, FILE *fp)
{
	register ttaskStateException *tse = (ttaskStateException*)generic;
    char ascii[ttaskMAX_NAME+1];

	(void)vcharExportBounded(vcharScribeASCIIExport(tse->taskname), 
							 ascii, ttaskMAX_NAME*sizeof(char));
	fprintf(fp, "\tTask: %s\n", ascii);
}


vexClass __ttaskStateExceptionClass = {0};


/*
 *+------------------------------------------------------------------------+
 * public routines
 *+------------------------------------------------------------------------+
 */


ttaskExternalClass*
ttaskExternalGetDefaultClass(void)
{
	if (!mGlobals)
		mGlobals = vclientRegisterModule();
	if (!*mGlobals)
		taskStartupClient();

	return mgPtr->defaultClass;
}




ttaskExternal*
ttaskCreateFrom(ttaskExternalProcInitializer *ini)
{
	ttaskExternal *volatile task;

	vdebugIF(!ini, vexGenerate(vexGetArgNullClass(), vexMESSAGE,
	         "create-from: NULL initializers!", vexERRNO, 0, vexNULL));

	task = ttaskExternalCreate();
	
	vexWITH_HANDLING
	{
		while (ini->proc)
			{
				ttaskExternalAdd(task, ini->proc, ini->data, 
								 vnameInternGlobalLiteral(ini->description));
				ini++;
			}
	}
	vexON_EXCEPTION
	{
		ttaskExternalDestroy(task);
		vexPropagate(NULL, vexNULL);
	}
	vexEND_HANDLING;
	
	return task;
}



/*
 *+------------------------------------------------------------------------+
 * private definition: ttaskExternal
 *+------------------------------------------------------------------------+
 */

/* */
#define nprocsize(_n) ((_n)*sizeof(_ttaskExternalProc))



/* */
static void taskAlloc(register ttaskExternal *task, unsigned n)
{
	task->b = (_ttaskExternalProc*)vmemAlloc(nprocsize(n));
	task->e = task->b;
	task->x = task->b + n;
}




/* */
static void taskCommonInit(register ttaskExternal *task)
{
	task->b = NULL;
	task->e = NULL;
	task->x = NULL;
	task->aborted = vFALSE;
}




/* */
static void taskCommonCopy(register ttaskExternal *from, 
						   register ttaskExternal *copy)
{
	int n = from->b ? (from->x-from->b) : 0;
	
	if (n)
		{
			taskAlloc(copy, (unsigned)n);
			(void)vmemCopy(from->b, copy->b, nprocsize(n));
		}
	else
		{
			copy->b = copy->e = copy->x = NULL;
		}
	
	copy->aborted = vFALSE;
}




/* */
static void taskAppend(register ttaskExternal *task, 
					   ttaskExternalProcPtr proc, const void *data,
					   const vchar *id)
{
	int n;

	vdebugIF(!proc, vexGenerate(vexGetArgNullClass(), vexMESSAGE,
			 "add: NULL proc ptr!", vexERRNO, 0, vexNULL));

	if (!task->b)
		taskAlloc(task, _BLK);

	else
  	if (task->e == task->x)
  		{
  			void *p;
    		n = task->x-task->b;
    		p = vmemRealloc(task->b, nprocsize(n+_BLK));
    		task->b = p;
    		task->e = task->b+n;
    		task->x = task->e+_BLK;
  		}

  	task->e->fn   = proc;
  	task->e->data = data;
  	task->e->id   = id;

	n = ttaskGetMaxIterations(ttaskOf(task));
  	task->e++;
	taskSendSuper(ttaskSET_MAX_ITERATIONS, (task, n+1));
}




/* */
static void taskRemove(register ttaskExternal *task,
					   ttaskExternalProcPtr proc)
{
	vdebugIF(!proc, vexGenerate(vexGetArgNullClass(), vexMESSAGE,
			 "remove: NULL proc ptr!", vexERRNO, 0, vexNULL));

	if (taskNonNil(task))
		{
			register _ttaskExternalProc *p;
			int i=0;

			for (p = task->b; p<task->e; p++, i++)
				if (p->fn == proc)
					break;

			if ((p<task->e) && (i>=(int)ttaskGetCompletions(ttaskOf(task))))
				{
					int n = (task->e-p) -1;
					if (n>0)
						(void)vmemMove(&task->b[i+1], &task->b[i],
									   nprocsize(n));
					--task->e;
					vdebugAssert(task->e>=task->b);
					
					i = ttaskGetMaxIterations(ttaskOf(task));
					taskSendSuper(ttaskSET_MAX_ITERATIONS, (task, i-1));
				}
		}
}




/* */

#if (vdebugDEBUG)

void _ttaskExternalRemoveDBG(register ttaskExternal *task,
					         ttaskExternalProcPtr proc, const char *file,
					         int line)
{
	if (!task->b)
		vdebugMWarn(("remove: *empty*\n\tfile: %s\n\tline: %d\n", file, line));

	if (ttaskIsLocked(ttaskOf(task)))
		vexGenerate(ttaskGetStateExceptionClass(), 
					vexMESSAGE, "remove: locked!",
					ttaskStateTASK, task,
					vexERRNO, 0, 
					vexFILE, file, vexLINE, line, 
					vexNULL);

	ttaskESend(task, ttaskExternalREMOVE, (task, proc));
}

#endif




/* */
static ttaskExternalProcPtr taskPeek(register ttaskExternal *task)
{
	return taskNonNil(task) ? 
		task->e[-1].fn : (ttaskExternalProcPtr)NULL;
}




/* */
static void taskInit(register ttaskExternal *task)
{
	taskSendSuper(vinstanceINIT, (task));
	
	taskCommonInit(task);
}




/* */
static void taskLoadInit(register ttaskExternal *task, vresource res)
{
	taskSendSuper(vobjectLOAD_INIT, (task, res));
	
	taskCommonInit(task);
}




/* */
static void taskCopyInit(ttaskExternal *from, ttaskExternal *task)
{
	taskSendSuper(vobjectCOPY_INIT, (from, task));
	
	taskCommonCopy(from, task);
}




/* */
static void taskCopy(ttaskExternal *from, ttaskExternal *task)
{
	taskSendSuper(vobjectCOPY, (from, task));
	
	if (task->b)
		vmemFree((void*)task->b), task->b = NULL;
	
	taskCommonCopy(from, task);
}




/* */
static void taskDestroy(register ttaskExternal *task)
{
	if (task->b)
		vmemFree((void*)task->b);
	
	taskSendSuper(vinstanceDESTROY, (task));
}




/* */
static unsigned taskAskBreak(register ttaskExternal *task)
{
	return vclassGet(ttaskExternalGetClass(task), 
					 ttaskExternalBREAK_STATUS);
}




/* */
static void taskNoteError(ttaskExternal *task, ttaskExternalProcPtr proc,
						  const void *data, const vchar *name)
{
#if (vdebugDEBUG)
	vscribe *scribe;

	scribe = vcharScribeFormatLiteral
		("execute: task (0x%lx, %S) has failed.\n",
		 proc, name ? vcharScribe(name) : vcharScribeLiteral("*unknown*"));

	vcharDumpScribed(scribe, vdebugGetWarningStream());

#endif
}




/* */
static void taskExecute(ttaskExternal *task_)
{
	ttaskExternal *volatile task = task_;

	vdebugIF((task->aborted), 
		vexGenerate(ttaskGetStateExceptionClass(), 
					vexMESSAGE, "execute: been aborted!",
					ttaskStateTASK, task,
					vexERRNO, 0, vexNULL));

	if (taskNonNil(task))
		{
			int n = (int)ttaskGetCompletions(ttaskOf(task));
			_ttaskExternalProc *volatile p = &task->b[n];
			
			if ( (p>=task->b) && (p<task->e) )
				vexWITH_HANDLING
				{
					p->fn(task, p->data);
				}
				vexON_EXCEPTION
				{
					if (ttaskExternalBreakProcError(task))
						task->aborted = vTRUE;

					ttaskExternalNoteError(task, p->fn, p->data, p->id);
				}
				vexEND_HANDLING;
		}
}




/* */
static void taskCallAllSync(ttaskExternal *task_)
{	
	ttaskExternal *volatile task = task_;

	vdebugIF((task->aborted), 
		ttaskGenerateState(task, "execute-all: been aborted!"));

	if (ttaskIsLocked(ttaskOf(task)))
		ttaskGenerateState(task, "execute-all: locked");

	if (taskNonNil(task))
		{
			int volatile n = (int)ttaskGetCompletions(ttaskOf(task));
			_ttaskExternalProc *volatile p = &task->b[n];

			n = 0;			
			if ( (p>=task->b) && (p<task->e) )
				while ( p<task->e )
					{
						vexWITH_HANDLING
						{
							p->fn(task, p->data);
							n++;
						}
						vexON_EXCEPTION
						{
							if (ttaskExternalBreakProcError(task))
								task->aborted = vTRUE;
		
							ttaskExternalNoteError(task, p->fn, p->data, p->id);
						}
						vexEND_HANDLING;
						
						if (task->aborted)
							break;
						p++;
					}
			if (n>0 && !task->aborted)
				ttaskAdvance(ttaskOf(task), (unsigned short)n);
		}
}




/* */
static unsigned taskAgain(register ttaskExternal *task)
{
	if (task->aborted)
		return vFALSE;
	else
		return taskSendSuper(ttaskGET_AGAIN, (task));
}




/* */
static void taskPost(register ttaskExternal *task)
{
	task->aborted = vFALSE;
	
	taskSendSuper(ttaskPOST, (task));
}




/* */
static void taskIgnoreMaxIterations(register ttaskExternal *task,
									unsigned short ignored)
{
	vdebugMWarn(("set-max-iterations: this value is determined!"));
}




/* */
static const vchar *taskGetDescription(register ttaskExternal *task)
{
	register const vchar *it= NULL;

	if (taskNonNil(task))
		{
			int n = (int)ttaskGetCompletions(ttaskOf(task));
			it = task->b[n].id;
		}
	
	if (!it)
		it = taskSendSuper(ttaskGET_DESCRIPTION, (task));
	
	return it;
}




/* */
static void taskStartupClient(void)
{
	register ttaskExternalClass	*clas;

	vexInitClass(&__ttaskStateExceptionClass, vexGetValueClass(),
				 "Task State", sizeof(ttaskStateException),
				 ttaskStateDumper);

	vclientAllocateModule(mGlobals, sizeof(_ttaskClientGlobals));

	clas = vclassSpawn(ttaskGetDefaultClass(), sizeof(ttaskExternalClass));
	vclassSetObjectSize(clas, sizeof(ttaskExternal));
	vclassSetNameScribed(clas, vcharScribeLiteral(CLASSNAME));

	vclassSet(clas, vinstanceINIT, taskInit);
	vclassSet(clas, vinstanceDESTROY, taskDestroy);
	vclassSet(clas, vobjectLOAD_INIT, taskLoadInit);
	vclassSet(clas, vobjectCOPY, taskCopy);
	vclassSet(clas, vobjectCOPY_INIT, taskCopyInit);
	
	vclassSet(clas, ttaskSET_MAX_ITERATIONS, taskIgnoreMaxIterations);
	vclassSet(clas, ttaskPOST, taskPost);
	vclassSet(clas, ttaskGET_AGAIN, taskAgain);
	vclassSet(clas, ttaskEXECUTE, taskExecute);
	vclassSet(clas, ttaskGET_DESCRIPTION, taskGetDescription);

	vclassSet(clas, ttaskExternalADD, taskAppend);
	vclassSet(clas, ttaskExternalREMOVE, taskRemove);
	vclassSet(clas, ttaskExternalPEEK, taskPeek);
	vclassSet(clas, ttaskExternalBREAK_STATUS, vTRUE);
	vclassSet(clas, ttaskExternalGET_BREAK_STATUS, taskAskBreak);
	vclassSet(clas, ttaskExternalNOTE_ERROR, taskNoteError);
	vclassSet(clas, ttaskExternalCALL_ALL, taskCallAllSync);
	
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

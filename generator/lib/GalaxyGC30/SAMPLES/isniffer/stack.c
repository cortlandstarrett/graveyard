/* $Id: stack.c,v 1.1 1994/08/20 14:17:22 chad Exp $ */
/****************************************************************************
 *                (c) Copyright 1991-1994 Visix Software, Inc.              *
 *                           All rights reserved.                           *
 * The following Sample Code is provided for your reference purposes in     *
 * connection with your use of the Galaxy Application Environment (TM)      *
 * software product which you have licensed from Visix Software, Inc.       *
 * ("Visix"). The Sample code is provided to you without any warranty of any*
 * kind and you agree to be responsible for the use and/or incorporation    *
 * of the Sample Code into any software product you develop. You agree to   *
 * fully and completely indemnify and hold Visix harmless from any and all  *
 * loss, claim, liability or damages with respect to your use of the Sample *
 * Code.                                                                    *
 *                                                                          *
 * Subject to the foregoing, you are permitted to copy, modify, and         *
 * distribute the Sample Code for any purpose, and without fee, provided    *
 * that (i) a copyright notice in the in the form of "Copyright 1992 Visix  *
 * Software Inc., 11440 Commerce Park Drive, Reston, VA  22091. All Rights  *
 * Reserved" appears in all copies, (ii) both the copyright notice and this *
 * permission notice appear in all supporting documentation and (iii) you   *
 * are a valid licensee of The Galaxy Application Environment.              *
 *                                                                          *
 ****************************************************************************
 *                                                                          *
 * Description:                                                             *
 *     This module implements a very simple stack module. used by isnoop &  *
 *     sample browser code.                                                 *
 *                                                                          *
 * Modification History:                                                    *
 *     o 12-11-93: created for galaxy 2.0 (ssmc)                            *
 *                                                                          *
 * Special Usage Notes:                                                     *
 *     o stack elements are restricted to sizeof(void*) and smaller.        *
 *                                                                          *
 * Text Editor Formatting:                                                  *
 *     Symantec: Tab(8), Font(Any Fixed Width)                              *
 *     Emacs: see end of file for info                                      *
 *                                                                          *
 ****************************************************************************
 */

#include <vport.h>
#include vstdioHEADER
#include vstdlibHEADER
#include vdebugHEADER
#include vexHEADER
#include vmemHEADER
#include vpoolHEADER
#include vclientHEADER
#include vstdHEADER

#include "tstack.h"


/* our vdebug tag */
#if (vdebugDEBUG)
static const char *const _stackTag = "tstack";
#define vdebugTAG _stackTag
#endif

/*
 *+------------------------------------------------------------------------+
 * private constants, variables, prototypes
 *+------------------------------------------------------------------------+
 */

#define tstackBLK     4
#define tstackXS     (2*tstackBLK)
#define tstackDYN    0x1

static int	tstackInitialized = FALSE;
static vpool   *tstackPool = NULL;
static int	tstackUsesPools = FALSE;

static void	tstackFit(tstack*);
static void	tstackInitModule(void);
static void	tstackQuitModule(void);


/*
 *+------------------------------------------------------------------------+
 * exported routines
 *+------------------------------------------------------------------------+
 */

void
tstackStartupManager(int usePools)
{
  if (!tstackInitialized)
    {
      tstackUsesPools = usePools;
      tstackInitModule();
    }
  return;
}




tstack*
tstackCreate(void)
{
  register tstack *stk;

  if (!tstackInitialized) 
    tstackInitModule();

  stk = tstackPool ? (tstack*)vpoolAlloc(tstackPool) 
                  : (tstack*)vmemAlloc(sizeof(tstack));

  stk->top = stk->bot = stk->max = NULL;
  stk->flags = 0;
  stk->blk = 0;
  stk->flags |= tstackDYN;

  return stk;
}




tstack*
tstackCreateSized(int cnt)
{
  register tstack *stk;

  vdebugIF((cnt<=0), vexGenerate(vexGetArgRangeClass(), vexMESSAGE,
           "create sized: count less than or equal zero", vexERRNO, 0,
           vexNULL));

  stk = tstackCreate();
  cnt = vMAX(tstackBLK, cnt);
  stk->bot = (void**)vmemAlloc(cnt*sizeof(void*));
  stk->top = stk->bot;
  stk->max = stk->bot + cnt;

  return stk;
}




void
tstackInit(register tstack *stk)
{
  vdebugIF((!stk), vexGenerate(vexGetArgNullClass(), vexMESSAGE,
           "init: NULL tstack ref!", vexERRNO, vexNULL));

  if (!tstackInitialized)
    tstackInitModule();

  stk->top = stk->bot = stk->max = NULL;
  stk->flags = 0;
  stk->blk = 0;

  return;
}




tstack*
tstackClone(register tstack *stk)
{
  register tstack *dup;
  register void	 **ptr;

  vdebugIF((!stk), vexGenerate(vexGetArgNullClass(), vexMESSAGE,
           "clone: NULL tstack ref!", vexERRNO, vexNULL));

  dup = tstackCreateSized(tstackGetSize(stk));
  ptr = stk->top-1;
  while (ptr>=stk->bot) {
    tstackPsh(dup, *ptr);
    ptr--;
  }
  return dup;
}




void
tstackDestroy(register tstack *stk)
{
  vdebugIF((!stk), vexGenerate(vexGetArgNullClass(), vexMESSAGE,
           "destroy: NULL tstack ref!", vexERRNO, vexNULL));

  if (stk->bot) 
    vmemFree(stk->bot);

  if (stk->flags & tstackDYN)
    {
      if (tstackPool) vpoolFree(tstackPool, stk);
      else vmemFree(stk);
    }
  return;
}




void
tstackSetExpandSize(tstack *stk, unsigned short blk)
{
#if vdebugDEBUG
  if (!stk)
    vexGenerate(vexGetArgNullClass(), vexMESSAGE, "set expand size: NULL "
                "tstack ref!", vexERRNO, 0, vexNULL);
  if (blk==0)
    vexGenerate(vexGetArgRangeClass(), vexMESSAGE, "set expand size: size "
                "is 0", vexERRNO, 0, vexNULL);
#endif

  if (blk<tstackBLK) blk = 0;
  stk->blk = blk;
  return;
}




void
tstackReset(tstack *stk)
{
  vdebugIF((!stk), vexGenerate(vexGetArgNullClass(), vexMESSAGE,
           "reset: NULL tstack ref!", vexERRNO, vexNULL));

  if (stk->bot)
    vmemFree(stk->bot);

  stk->top = stk->bot = stk->max = NULL;
  return;
}




void
tstackPsh(register tstack *stk, void *itm)
{
  void	*tmp;
  int	 cnt,blk;

#if vdebugDEBUG
  if (!stk)
    vexGenerate(vexGetArgNullClass(), vexMESSAGE, "push: NULL tstack ref!",
                vexERRNO, 0, vexNULL);
  if (!itm)
    vexGenerate(vexGetArgNullClass(), vexMESSAGE, "push: NULL item ref!",
                vexERRNO, 0, vexNULL);
#endif

  blk = stk->blk ? stk->blk : tstackBLK;

  if (stk->bot==NULL)
    {
      stk->top = stk->bot = (void**)vmemAlloc(sizeof(void*)*blk);
      stk->max = stk->bot + blk;
    }
  else
  if (stk->top==stk->max)
    {
      cnt = stk->max-stk->bot;
      tmp = vmemRealloc(stk->bot, (cnt+blk)*sizeof(void*));
      stk->bot = (void**)tmp;
      stk->top = stk->bot+cnt;
      stk->max = stk->bot+cnt+blk;
    }
  
 *stk->top = itm;
  stk->top++;

  return;
}




void*
tstackPop(register tstack *stk)
{
  void	*val;

#if vdebugDEBUG
  if (!stk)
    vexGenerate(vexGetArgNullClass(),  vexMESSAGE, "pop: NULL tstack ref!",
                vexERRNO, 0, vexNULL);
  if (!stk->top || (stk->bot==stk->top))
    vexGenerate(vexGetArgRangeClass(), vexMESSAGE, "pop: tstack empty!",
                vexERRNO, 0, vexNULL);
#endif

  stk->top--;
  val = *stk->top;

  tstackFit(stk);

  return val;
}




void
tstackUnlk(register tstack *stk, register int cnt)
{
  register int lim;

#if vdebugDEBUG
  if (!stk)
    vexGenerate(vexGetArgNullClass(),  vexMESSAGE, "unlk: NULL tstack ref!",
                vexERRNO, 0, vexNULL);
  if (!stk->top || (stk->bot==stk->top))
    vexGenerate(vexGetArgRangeClass(), vexMESSAGE, "unlk: tstack empty!",
                vexERRNO, 0, vexNULL);
#endif

  lim = stk->top-stk->bot;
  if (cnt>lim) cnt=lim;

  stk->top -= cnt;
  tstackFit(stk);

  return;
}


/*
 *+------------------------------------------------------------------------+
 * private routines
 *+------------------------------------------------------------------------+
 */

static void
tstackFit(register tstack *stk)
{
  register int	cnt;
  void		*tmp;
  int		 xs, blk;

  xs  = stk->blk ? 2*stk->blk : tstackXS;
  cnt = stk->max-stk->top;
  if (cnt>xs)
    {
      blk = stk->blk ? stk->blk : tstackBLK;
      cnt = stk->top-stk->bot;
      tmp = vmemRealloc(stk->bot, (cnt+blk)*sizeof(void*));
      stk->bot = (void**)tmp;
      stk->top = stk->bot+cnt;
      stk->max = stk->bot+cnt+blk;
    }
  return;
}




static void
tstackQuitModule(void)
{
  if (tstackPool)
    vpoolDestroy(tstackPool);
  return;
}




static void
tstackInitModule(void)
{
  if (tstackUsesPools)
    {
      tstackPool = vpoolCreate(sizeof(tstack));
      vclientRegisterGlobalShutdown(tstackQuitModule);
    }
  tstackInitialized = TRUE;
  return;
}

/*
  +-------------------------------------------------------------------------+
   MISC formatting information for emacs in c-mode
  +-------------------------------------------------------------------------+
 */

/*
 * Local Variables:
 * c-indent-level:2
 * c-continued-statement-offset:2
 * c-brace-offset:0
 * c-brace-imaginary-offset:0
 * c-argdecl-indent:5
 * c-label-offset:0
 * c-tab-always-indent:nil
 * End:
 */

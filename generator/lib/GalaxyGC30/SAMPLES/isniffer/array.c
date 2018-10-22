/* $Id: array.c,v 1.2 1995/08/01 21:11:52 simone Exp $ */
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
 *     This module implements a very simple array module. used by isnoop &  *
 *     sample browser code.                                                 *
 *                                                                          *
 * Modification History:                                                    *
 *     o 12-11-93: created for galaxy 2.0 (ssmc)                            *
 *                                                                          *
 * Special Usage Notes:                                                     *
 *     o                                                                    *
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
#include vstdHEADER

#include "tarray.h"


/* our vdebug tag */
#if (vdebugDEBUG)
static const char *const _arrayTag = "tarray";
#define vdebugTAG _arrayTag
#endif

/*
 *+------------------------------------------------------------------------+
 * private constants, variables, prototypes
 *+------------------------------------------------------------------------+
 */

#define tarrayBLK 4

static void tarrayFit(tarray*);
static void tarrayExpand(tarray*);

/*
 *+------------------------------------------------------------------------+
 * exported routines
 *+------------------------------------------------------------------------+
 */

static void
tarrayInit(register tarray *a, size_t size)
{
  vdebugIF((!a), vexGenerate(vexGetArgNullClass(), vexMESSAGE, 
          "init: NULL tarray ref!", vexERRNO, 0, vexNULL));

  if (size<sizeof(int)) 
    size = sizeof(int);
  else if (size%sizeof(int)) 
    size = (size/sizeof(int) + 1)*sizeof(int);

  a->size = size;
  a->blk  = tarrayBLK;
  a->mem  = NULL;
  a->max  = 0;
  a->num  = 0;

  return;
}




tarray *
tarrayCreate(size_t size)
{
  register tarray *a;

  a = (tarray*)vmemAlloc(sizeof(tarray));
  tarrayInit(a, size);

  return a;
}




tarray *
tarrayCreateSized(size_t size, unsigned short max)
{
  register tarray *a;

  vdebugIF((max==0), vexGenerate(vexGetArgRangeClass(), vexMESSAGE,
           "create sized: size is equal to zero!", 
           vexERRNO, 0, vexNULL));

  a = tarrayCreate(size);

  a->mem = (vbyte*)vmemAllocAndClear(max*size);
  a->max = max;

  return a;
}




tarray *
tarrayClone(register tarray *a)
{
  register tarray *c;

  vdebugIF((!a), vexGenerate(vexGetArgNullClass(), vexMESSAGE,
           "clone: NULL tarray ref!", vexERRNO, 0, vexNULL));

  if (!a->mem || !a->num) 
    c = tarrayCreate(a->size);
  else {
    c = tarrayCreateSized(a->size, a->max);
    (void)vmemCopy(a->mem, c->mem, a->max*a->size);
    c->num = a->num;
  }
  
  c->blk = a->blk;

  return c;
}




void
tarrayDestroy(register tarray *a)
{
  vdebugIF((!a), vexGenerate(vexGetArgNullClass(), vexMESSAGE,
           "destroy: NULL tarray ref!", vexERRNO, 0, vexNULL));

  if (a->mem) vmemFree(a->mem);
  vmemFree(a);
  return;
}




void
tarraySetExpandSize(register tarray *a, unsigned short blk)
{
#if vdebugDEBUG
  if (!a)
    vexGenerate(vexGetArgNullClass(), vexMESSAGE, "set expand size: NULL "
                "tarray ref!", vexERRNO, 0, vexNULL);
  if (blk==0)
    vexGenerate(vexGetArgRangeClass(), vexMESSAGE,"set expand size: block "
                "size is equal to zero!", vexERRNO, 0, vexNULL);
#endif

  a->blk = vMAX(tarrayBLK,blk);
  return;
}




void
tarrayAppendItem(register tarray *a, void *info)
{
  vdebugIF((!a), vexGenerate(vexGetArgNullClass(), vexMESSAGE,
           "append item: NULL tarray ref!", vexERRNO, 0, vexNULL));

  tarrayExpand(a);
  (void)vmemMove(info, &a->mem[a->size*a->num], a->size);
  a->num++;
  return;
}




void
tarrayDeleteItem(register tarray *a, unsigned short index)
{
#if vdebugDEBUG
  if (!a) 
    vexGenerate(vexGetArgNullClass(), vexMESSAGE, "delete item: NULL "
                "tarray ref!", vexERRNO, 0, vexNULL);
  if (index>=a->num)
    vexGenerate(vexGetArgRangeClass(), vexMESSAGE, "delete item: index "
                "is out of range!", vexERRNO, 0, vexNULL);
#endif

  if (a->num>0 && (index!=a->num-1))
    (void)vmemMove(&a->mem[a->size*(index+1)], &a->mem[a->size*index],
		   a->size*(a->num-index-1));
  a->num--;
  tarrayFit(a);
  return;
}




void
tarrayInsertItem(register tarray *a, unsigned short index, void *info)
{
#if vdebugDEBUG
  if (!a) 
    vexGenerate(vexGetArgNullClass(), vexMESSAGE, "insert item: NULL "
                "tarray ref!", vexERRNO, 0, vexNULL);
  if (index>a->num)
    vexGenerate(vexGetArgRangeClass(), vexMESSAGE, "insert item: index "
                "is out of range!", vexERRNO, 0, vexNULL);
#endif

  tarrayExpand(a);
  if (index!=a->num)
    (void)vmemMove(&a->mem[a->size*index], &a->mem[a->size*(index+1)],
		   a->size*(a->num-index));
  (void)vmemMove(info, &a->mem[a->size*index], a->size);
  a->num++;
  return;
}




void
tarrayZeroNumber(register tarray *a)
{
  vdebugIF((!a), vexGenerate(vexGetArgNullClass(), vexMESSAGE,
           "zero: NULL tarray ref!", vexERRNO, 0, vexNULL));
  a->num = 0;
  if (a->max) tarrayFit(a);
  return;
}




void
tarrayReserveSize(register tarray *a, unsigned short max)
{
#if vdebugDEBUG
  if (!a)
    vexGenerate(vexGetArgNullClass(), vexMESSAGE, "reserve size: NULL "
                "tarray ref!", vexERRNO, 0, vexNULL);
  if (max==0)
    vexGenerate(vexGetArgRangeClass(), vexMESSAGE, "reserve size: size "
                "is equal to zero", vexERRNO, 0, vexNULL);
#endif

  if (a->max<max) 
    {
      if (!a->mem)
	a->mem = vmemAlloc(a->size*max);
      else 
	a->mem = vmemRealloc(a->mem, a->size*max);
      a->max = max;
    }
  return;
}




#if vdebugDEBUG           /* --------------- vdebugDEBUG --------------- */
unsigned
tarrayGetNumber(register tarray *a)
{
  if (!a)
    vexGenerate(vexGetArgNullClass(), vexMESSAGE,
		"get number: NULL tarray ref!", vexERRNO, 0, vexNULL);

  return (unsigned)a->num;
}




void *
tarrayAt(register tarray *a, unsigned short index)
{
  if (!a) 
    vexGenerate(vexGetArgNullClass(), vexMESSAGE,
		"at: NULL tarray ref!", vexERRNO, 0, vexNULL);
  if (index>=a->num)
    vexGenerate(vexGetArgRangeClass(), vexMESSAGE, "at: index is out "
                "of range!", vexERRNO, 0, vexNULL);

  return (void*)&a->mem[a->size*index];
}




void *
tarrayAtStop(register tarray *a)
{
  if (!a)
    vexGenerate(vexGetArgNullClass(), vexMESSAGE,
		"at stop: NULL tarray ref!", vexERRNO, 0, vexNULL);

  return (void*)&a->mem[a->size*a->num];
}




size_t
tarrayGetElementSize(register tarray *a)
{
  if (!a) 
    vexGenerate(vexGetArgNullClass(), vexMESSAGE,
		"get elemsize: NULL tarray ref!", vexERRNO, 0, vexNULL);

  return a->size;
}




void *
tarrayGetTarray(register tarray *a)
{
  if (!a) 
    vexGenerate(vexGetArgNullClass(), vexMESSAGE,
		"get tarray: NULL tarray ref!", vexERRNO, 0, vexNULL);

  return (void*)a->mem;
}

#endif                    /* --------------- vdebugDEBUG --------------- */

/*
 *+------------------------------------------------------------------------+
 * private routines
 *+------------------------------------------------------------------------+
 */

static void
tarrayExpand(register tarray *a)
{
  if (!a->mem)
    {
      a->mem = vmemAlloc(a->size*a->blk);
      a->max = a->blk;
    }
  else
  if (a->num==a->max)
    {
      a->mem = vmemRealloc(a->mem, (a->max+a->blk)*a->size);
      a->max += a->blk;
    
    }
  return;
}




static void
tarrayFit(register tarray *a)
{
  register unsigned num;

  num = a->num/a->blk;
  if (!num || a->num%a->blk) num++;
  num *= a->blk;
  if (a->max-num)
    {
      void *mem;
      mem    = vmemRealloc(a->mem, num*a->size);
      a->mem = (vbyte*)mem;
      a->max = num;
    }
  return;
}


/*
  +-------------------------------------------------------------------------+
   formatting information for emacs in c-mode
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

/* $Id: tarray.h,v 1.2 1995/08/01 21:11:32 simone Exp $ */
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

#ifndef tarrayINCLUDED
#define tarrayINCLUDED 1

#ifndef vportINCLUDED
#include <vport.h>
#endif

#ifndef vstddefINCLUDED
#include vstddefHEADER
#endif


/*
 *+------------------------------------------------------------------------+
 * public types
 *+------------------------------------------------------------------------+
 */

typedef struct tarray {
  size_t	size;
  unsigned short blk;
  unsigned short num, max;
  vbyte		*mem;
}tarray;


/*
 *+------------------------------------------------------------------------+
 * exported routines
 *+------------------------------------------------------------------------+
 */

tarray *tarrayCreate(size_t);
tarray *tarrayCreateSized(size_t, unsigned short);
tarray *tarrayClone(tarray*);
void tarrayDestroy(tarray*);
void tarraySetExpandSize(tarray*,unsigned short);
void tarrayAppendItem(tarray*,void*);
void tarrayDeleteItem(tarray*,unsigned short);
void tarrayInsertItem(tarray*,unsigned short,void*);
void tarrayReserveSize(tarray*,unsigned short);
unsigned tarrayGetNumber(tarray*);
void tarrayZeroNumber(tarray*);
void *tarrayAt(tarray*,unsigned short);
void *tarrayAtStart(tarray*);
void *tarrayAtStop(tarray*);
size_t tarrayGetElementSize(tarray*);
void *tarrayGetArray(tarray*);

/*
 *+------------------------------------------------------------------------+
 * private macros
 *+------------------------------------------------------------------------+
 */

#if (!vdebugDEBUG)
#define tarrayAt(a,i) 		((void*)(&(a)->mem[(a)->size*(i)]))
#define tarrayAtStop(a)		((void*)(&(a)->mem[(a)->size*(a)->num]))
#define tarrayGetNumber(a) 	((unsigned)(a)->num)
#define tarrayGetTarray(a)  	((void*)(a)->mem)
#define tarrayGetElementSize(a)	((a)->size)
#endif

#define tarrayAtStart(a)	tarrayAt(a,0)
#define tarrayAtStartAs(a,t)	((t)tarrayAtStart(a))
#define tarrayAtStopAs(a,t)	((t)tarrayAtStop(a))
#define tarrayAtAs(a,i,t) 	((t)tarrayAt(a,i))
#define tarrayGetTarrayAs(a,t)	((t)tarrayGetTarray(a))

/* tarrayINCLUDED */
#endif


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

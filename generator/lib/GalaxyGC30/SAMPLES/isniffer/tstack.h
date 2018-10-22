/* $Id: tstack.h,v 1.2 1995/05/02 10:45:11 brad Exp $ */
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
 *     o                                                                    *
 *                                                                          *
 * Text Editor Formatting:                                                  *
 *     Symantec: Tab(8), Font(Any Fixed Width)                              *
 *     Emacs: see end of file for info                                      *
 *                                                                          *
 ****************************************************************************
 */

#ifndef tstackINCLUDED
#define tstackINCLUDED 1

#ifndef vportINCLUDED
#include <vport.h>
#endif

typedef struct tstack {
  unsigned short flags;
  unsigned short blk;
  void	**top, **bot, **max;
}tstack;


void tstackStartupManager(int usePools);
tstack *tstackCreate(void);
tstack *tstackCreateSized(int);
void tstackInit(tstack*);
tstack *tstackClone(tstack*);
void tstackSetExpandSize(tstack*,unsigned short);
void tstackDestroy(tstack*);
void tstackReset(tstack*);
void tstackPsh(tstack*, void*);
void *tstackPop(tstack*);
void tstackUnlk(tstack*, int);
int tstackGetNumber(tstack*);
int tstackIsEmpty(tstack*);


#define tstackPush(s,v)		tstackPsh(s,(void*)(v))
#define tstackPopAs(s,t)	((t)tstackPop(s))
#define tstackIsEmpty(s)	((!(s)->bot) || ((s)->top==(s)->bot))
#define tstackGetNumber(s)	(!(s)->bot ? 0 : (s)->top-(s)->bot)
#define tstackGetSize(s)  		tstackGetNumber(s)

/* tstackINCLUDED */
#endif

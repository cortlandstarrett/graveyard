/* $Id: spin.c,v 1.2 1995/08/01 21:12:41 simone Exp $ */
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
 *                                                                          *
 ****************************************************************************
 */

/* for v*HEADER */
#include <vport.h>

/* ANSI headers */
#include vstdioHEADER
#include vstdlibHEADER

/* Galaxy headers */
#include vdebugHEADER
#include vexHEADER
#include vmemHEADER
#include vcharHEADER
#include vstrHEADER
#include vnameHEADER
#include vresourceHEADER
#include vcursorHEADER

#include vwindowHEADER
#include vdialogHEADER

/* Our headers */
#include "names.h"
#include "isnf.h"
#include "utils.h"


/* Define our debug tag for vdebug manager */
#if vdebugDEBUG
static const char *const _moduleTag = "spin-docktor";
#define vdebugTAG _moduleTag
#endif



void
isnfStartupSpinDocktor(isnifferApp *app)
{
  vresource ares;
  unsigned n= 0;
  isnifferCursors *curp = &app->cursors;

  if ( !vresourceTestGet(app->resources, TAG("spin-docktor"), &ares) ||
      vresourceType(ares)!=vresourceARRAY      || 
      vresourceArrayType(ares)!=vresourceDICT  ||
      (n= vresourceCountComponents(ares)) == 0 )

    vexGenerate(vexGetValueClass(), vexMESSAGE,
		"spin-docktor: cursors resource phffhted!", vexERRNO, 0,
		vexNULL);

  curp->cursors  = (vcursor**)vmemAllocAndClear(n*sizeof(vcursor*));
  curp->resource = ares;
  curp->count    = (unsigned short)n;
  curp->at       = 0;
  curp->level	 = 0;
}



void
isnfShutdownSpinDocktor(isnifferApp *app)
{
  if (app->cursors.cursors) {
    register unsigned short i;
    register isnifferCursors *curp;
    for (i=0, curp= &app->cursors; i<curp->count; i++)
      if (curp->cursors[i])
	vcursorDestroy(curp->cursors[i]);
    vmemFree((void*)curp->cursors);
  }
}



void
isnfSpinDocktorWannaSpinPlease(void)
{
  register isnifferCursors *curp = &isnfGet()->cursors;
  curp->level++;
  if (curp->level==1) {
    curp->at = 0;
    if (isnfIsBlocked())
      vwindowUnblock(vdialogGetWindow(isnfGet()->requestor));
    isnfSpinDocktorSpinBabySpin();
  }
}



void
isnfSpinDocktorSpinBabySpin(void)
{
  register isnifferCursors *curp = &isnfGet()->cursors;
  if (curp->level>0) {
    register vcursor **curs = &curp->cursors[curp->at];

    if (!*curs)
      *curs = vcursorLoad(vresourceGetAt(curp->resource, curp->at));
    vwindowSetCursor(vdialogGetWindow(isnfGet()->requestor), *curs);
    curp->at = (int)(curp->at+1)%(int)curp->count;
  }
#if vdebugDEBUG
  else
    vdebugWarn("i'm fallen and i can't get up!\n");
#endif
}



void
isnfSpinDocktorStopImTooDizzy(void)
{
  register isnifferCursors *curp = &isnfGet()->cursors;
  if (curp->level>0) {
    curp->level--;
    if (!curp->level) {
      vwindowSetCursor(vdialogGetWindow(isnfGet()->requestor), NULL);
      if (isnfIsBlocked())
	vwindowBlock(vdialogGetWindow(isnfGet()->requestor));
    }
  }
#if vdebugDEBUG
  else
    vdebugWarn("i'm trying to think but nuthin' happening!?!\n");
#endif
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

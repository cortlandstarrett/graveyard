/* $Id: group.c,v 1.3 1995/04/27 00:52:25 abstine Exp $ */
/* group.c -- implementation of group objects
 *
 * Gotta have some legalese:
 * The following Sample Code is provided for your reference purposes in
 * connection with your use of the Galaxy Application Environment (TM) software
 * product which you have licensed from Visix Software, Inc. ("Visix").
 * The Sample code is provided to you without any warranty of any kind
 * whatsoever and you agree to be responsible for the use and/or incorporation
 * of the Sample Code into any software product you develop. You agree to fully
 * and completely indemnify and hold Visix harmless from any and all loss,.
 * claim, liability or damages with respect to your use of the Sample Code.  
 *
 * Subject to the foregoing, you are permitted to copy, modify, and distribute
 * the Sample Code for any purpose and without fee, provided that (i) a
 * copyright notice in the in the form of "Copyright 1994 Visix Software Inc.,
 * 11440 Commerce Park Drive, Reston, VA  22091. All Rights Reserved" appears
 * in all copies, (ii) both the copyright notice and this permission notice
 * appear in supporting documentation and (iii) you are a valid licensee of
 * Galaxy Application Environment.
 *
 * Do not taunt Happy Fun Ball.
 */


#include <vport.h>

#ifndef  vclientINCLUDED
#include vclientHEADER
#endif

#ifndef  vapplicationINCLUDED
#include vapplicationHEADER
#endif

#ifndef  xpacemakerINCLUDED
#include "xpacemak.h"
#endif

#ifndef  xgroupINCLUDED
#include "xgroup.h"
#endif

#if (vportBAD_CC_SCOPING)
#define x X
#define y Y
#endif

static xgroupClass *g_defaultClass;
static vcolorPalette *g_palette;


/*
 * ----- method implementation
 */


static void _xgroupInit (xgroup *group)
{
    vclassSendSuper (g_defaultClass, vinstanceINIT, (group));
    
    group->image = 0;
    group->width = group->height = 0;
    group->x = group->y = -1;
    group->calculator = NULL;

    if (g_palette == NULL) {
	vresource appres, resource;

	appres = vapplicationGetResources (vapplicationGetCurrent());
	resource = vresourceGet (appres, 
				 vnameInternGlobalLiteral("Color Palette"));
	g_palette = vcolorLoadPalette (resource);
    }

} /* _xgroupInit */



static void _xgroupDestroy (xgroup *group)
{
    if (group->image != NULL) {
	vimageDestroy (group->image);
    }

    vclassSendSuper (g_defaultClass, vinstanceDESTROY, (group));

} /* _xgroupDestroy */



static void _xgroupDoWork (xgroup *group)
{
    xpacemaker *pacemaker = xgroupGetPacemaker(group);
    vbyte val;
    int i;

    for (i = 0; i < 50; i++) {
	vpixmapMoveTo (&group->scanner, group->x, group->y);
	val = xgroupCalculatePoint (group, group->x, group->y);
	
	vpixmapWrite (&group->scanner, val);
	
	group->x++;
	
	if (group->y == (group->height - 1)) {
	    xpacemakerFinish (pacemaker);
	    break;
	} else if (group->x == group->width) {
	    group->y++;
	    group->x = 0;
	}
    }

    vclassSendSuper (g_defaultClass, xpacemakerDO_WORK, (group));

} /* _xgroupDoWork */



static void _xgroupSetCalculator (xgroup *group, xgroupCalcFunc calculator)
{
    group->calculator = calculator;
} /* _xgroupSetCalculator */



static void _xgroupCalculate (xgroup *group, int async)
{
    xpacemaker *pacemaker = xgroupGetPacemaker (group);

    if ((group->width) > 0 && (group->height > 0)) {
	vpixmapInitScanner (&group->scanner, vimageGetMap(group->image));
	group->x = group->y = 0;

	if (async) {
	    xpacemakerStart (pacemaker);
	} else {
	    while (   !xpacemakerIsFinished(pacemaker) 
		   && !xpacemakerIsTerminated(pacemaker)) {
		xpacemakerDoWork (pacemaker);
	    }
	}
    }

} /* _xgroupCalculate */



static vbyte _xgroupCalculatePoint (xgroup *group, int x, int y)
{
    vbyte ret = 0;

    if (group->calculator != NULL) {
	ret = (group->calculator)(x, y);
    }

    return (ret);

} /* _xgroupCalculatePoint */



static void _xgroupSetSize (xgroup *group, int width, int height)
{
    group->width = width;
    group->height = height;
    
    if (group->image != NULL) {
	vimageDestroy (group->image);
    }

    if ((width <= 0) || (height <= 0)) {
	group->image = NULL;
    } else {
	group->image = vimageCreateSpecific (width, height, 256);
	vimageSetPalette (group->image, g_palette);
    }

} /* _xgroupSetSize */




/*
 * ----- Housekeeping
 */

static void _xgroupShutdown (void)
{
    if (g_palette != NULL) {
	vcolorDestroyPalette (g_palette);
    }

} /* _xgroupShutdown */

xgroupClass *xgroupGetDefaultClass (void)
{
    if (g_defaultClass == NULL) {

	/* make the class, set the method table size, the name, and
	 * the instance size
	 */
	g_defaultClass = vclassSpawn (xpacemakerGetDefaultClass(),
				      sizeof(xgroupClass));
	vclassSetNameScribed (g_defaultClass, vcharScribeLiteral("xgroup"));
	vclassSetObjectSize (g_defaultClass, sizeof(xgroup));

	vclassSet (g_defaultClass,
		   vinstanceINIT,
		   _xgroupInit);

	vclassSet (g_defaultClass,
		   vinstanceDESTROY,
		   _xgroupDestroy);
	
	vclassSet (g_defaultClass,
		   xpacemakerDO_WORK,
		   _xgroupDoWork);
	
	vclassSet (g_defaultClass,
		   xgroupSET_CALCULATOR,
		   _xgroupSetCalculator);
	
	vclassSet (g_defaultClass,
		   xgroupCALCULATE,
		   _xgroupCalculate);
	
	vclassSet (g_defaultClass,
		   xgroupCALCULATE_POINT,
		   _xgroupCalculatePoint);

	vclassSet (g_defaultClass,
		   xgroupSET_SIZE,
		   _xgroupSetSize);

	vclientRegisterGlobalShutdown (_xgroupShutdown);
    }

    return (g_defaultClass);

} /* xgroupGetDefaultClass */


/* Formatting information for emacs in c-mode
 *
 * Local Variables:
 * c-indent-level:4
 * c-continued-statement-offset:0
 * c-brace-offset:0
 * c-brace-imaginary-offset:0
 * c-argdecl-indent:0
 * c-label-offset:0
 * End:
 */



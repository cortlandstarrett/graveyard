/* $Id: vtooltip.h,v 1.3 1996/07/09 22:23:51 scotth Exp $ */

/************************************************************

    vtooltip.h

    C Interface file for the Tool-Tip Manager

    (c) Copyright Visix Software Inc.
    All rights reserved

************************************************************/

#ifndef vtooltipINCLUDED
#define vtooltipINCLUDED

#ifndef  vportINCLUDED
#include <vport.h>
#endif

#ifndef  vwindowINCLUDED
#include vwindowHEADER
#endif


vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * * * * * * * * * * PUBLIC CONSTANT DEFINITIONS * * * * * * * * * *
 */

/*
 * * * * * * * * * * PUBLIC TYPE DEFINITIONS * * * * * * * * * *
 */

/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */

vwindow *vtooltipGetWindow (vwindow *window);
void vtooltipClose      (vwindow *window);
void vtooltipPoint      (vwindow *window, int x, int y);
void vtooltipPost       (vwindow *tip, vwindow *leader, const vrect *fence);
void vtooltipPostScribed(vscribe *scribe, vwindow *leader, const vrect *fence);
void vtooltipReset      (vwindow *window);


/*
 * * * * * * * * * * PRIVATE CONSTANT DEFINITIONS * * * * * * * * * *
 */

/*
 * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * *
 */

/*
 * * * * * * * * * * PRIVATE FUNCTION PROTOTYPES * * * * * * * * * *
 */

/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * *
 */

/*
 * * * * * * * * * * PRIVATE FUNCTION MESSAGE DEFINITIONS * * * * * * * * * *
 */

vportEND_CPLUSPLUS_EXTERN_C

#endif /* #ifndef vtooltipINCLUDED */


/* $Id: progress.c,v 1.5 1994/02/28 17:52:47 simone Exp $ */

/*----------------------------------------------------------------------------
 *
 * The following Sample Code is provided for your reference purposes in
 * connection with your use of the Galaxy Application Environment (TM) software
 * product which you have licensed from Visix Software, Inc. ("Visix").
 * The Sample code is provided to you without any warranty of any kind
 * whatsoever and you agree to be responsible for the use and/or incorporation
 * of the Sample Code into any software product you develop. You agree to fully
 * and completely indemnify and hold Visix harmless from any and all loss,
 * claim, liability or damages with respect to your use of the Sample Code.  
 *
 * Subject to the foregoing, you are permitted to copy, modify, and distribute
 * the Sample Code for any purpose and without fee, provided that (i) a
 * copyright notice in the form of "Copyright 1992 Visix Software Inc.,
 * 11440 Commerce Park Drive, Reston, VA  22091. All Rights Reserved" appears
 * in all copies, (ii) both the copyright notice and this permission notice
 * appear in supporting documentation and (iii) you are a valid licensee of
 * Galaxy Application Environment.
 ---------------------------------------------------------------------------*/

/****************************************************************************
 *
 * Source File:		progress.c
 *
 * See file main.c for a full comment about this sample code.
 *
 * History:
 * $Log: progress.c,v $
 * Revision 1.5  1994/02/28  17:52:47  simone
 * vince beautified comments a bit.
 *
 * Revision 1.4  1993/12/03  04:53:25  chad
 * fixed to chain dialogs
 *
 * Revision 1.3  1993/12/02  05:42:07  simone
 * a. updated so progress dialog loaded from resource file,
 *    not created on fly.
 *
 * Revision 1.2  1993/11/11  23:20:55  chad
 * updated to use v*HEADER
 *
 * Revision 1.1  1993/07/21  13:50:23  chad
 * Initial revision
 *
 *
 ****************************************************************************/

#ifndef  vportINCLUDED
#include <vport.h>		/* for v*HEADER */
#endif

#ifndef  vdebugINCLUDED
#include vdebugHEADER
#endif

#ifndef  vnameINCLUDED
#include vnameHEADER
#endif

#ifndef  vresourceINCLUDED
#include vresourceHEADER
#endif

#ifndef  vapplicationINCLUDED
#include vapplicationHEADER
#endif

#ifndef  vdialogINCLUDED
#include vdialogHEADER
#endif

#ifndef  vcontrolINCLUDED
#include vcontrolHEADER
#endif

#ifndef  vsliderINCLUDED
#include vsliderHEADER
#endif

#include "progress.h"

#if (vdebugDEBUG)

/*
 * Override the vdebugTAG in such a way that dumb compilers which don't
 * uniquify string constants won't create tons of tags
 */
static const char * const	_progressTAG = "progress";
#define vdebugTAG		_progressTAG

#endif


/*
 * Convenience for interning literal strings to galaxy's global
 * vname table
 */
#define _TAG(literal) vnameInternGlobalLiteral(literal)



/*
 * Function:    progressCreate()
 * Description: Loads a progress dialog with the progress percentage set to 0
 * Input:       void
 * Output:      The new progress dialog
 */
progress_t *progressCreate( void )
{
    progress_t	*progress;
    vcontrol	*slider;
    vresource	 resource;

    vdebugTraceEnter( progressCreate );

    resource = vapplicationGetResources( vapplicationGetCurrent() );
    resource = vresourceGet( resource, _TAG( "ProgressDialog" ) );
    progress = _progressLoad( resource );

    slider = (vcontrol *) progressFindItem( progress, _TAG( "Slider" ) );
    vcontrolSetValue( slider, 0 );

    vdebugTraceLeave();

    return progress;
}


/*
 * Function:    progressSet()
 * Description: Updates a progress dialog
 * Input:       progress - the progress dialog
 *		amount - the percent of the task that's completed
 * Output:      void
 */
void progressSet( progress_t *progress, double amountCompleted )
{
    vcontrol	*slider;

    vdebugTraceEnter( progressSet );

    slider = (vcontrol *) progressFindItem( progress, _TAG( "Slider" ) );
    vcontrolSetValue( slider,
		     (int)(amountCompleted * (double)vcontrolGetMax( slider ))
		    );

    vdialogInvalItem( vcontrolGetItem( slider ), vwindowINVAL_IMMEDIATE );

    vdebugTraceLeave();
}


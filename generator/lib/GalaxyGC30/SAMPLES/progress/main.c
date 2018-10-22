/* $Id: main.c,v 1.7 1995/04/05 23:14:22 chad Exp $ */

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
 * Executable Name: progress
 * Source Files:    main.c
 * Header Files:    progress.h
 * Resource Files:  
 *
 * Managers Illustrated:
 *	vevent
 *
 * Description Of Sample:
 *	Shows how to do work while updating a progress window
 *
 * History:
 * $Log: main.c,v $
 * Revision 1.7  1995/04/05  23:14:22  chad
 * fixed to not swamp Windows event queues
 *
 * Revision 1.6  1994/02/28  17:52:39  simone
 * vince beautified comments a bit.
 *
 * Revision 1.5  1993/12/06  21:24:12  simone
 * a. autoinitialized variable to nuke purify warning
 *
 * Revision 1.4  1993/12/03  04:53:25  chad
 * fixed to chain dialogs
 *
 * Revision 1.3  1993/12/02  05:42:29  simone
 * a. updated so the dialogs are loaded from resource file,
 *    not created on the fly
 * b. the progress dialogs are not positioned properly for
 *    all platforms
 * c. updated to include "Quit" button
 *
 * Revision 1.2  1993/11/11  23:20:55  chad
 * updated to use v*HEADER
 *
 * Revision 1.1  1993/07/21  13:52:22  chad
 * Initial revision
 *
 *
 ****************************************************************************/

#ifndef  vportINCLUDED
#include <vport.h>		/* for v*HEADER */
#endif

#ifndef  vstdlibINCLUDED
#include vstdlibHEADER		/* for EXIT_* and rand */
#endif

#ifndef  vdebugINCLUDED
#include vdebugHEADER
#endif

#ifndef  vrectINCLUDED
#include vrectHEADER
#endif

#ifndef  vnameINCLUDED
#include vnameHEADER
#endif

#ifndef vnumINLUDED
#include vnumHEADER
#endif

#ifndef  vresourceINCLUDED
#include vresourceHEADER
#endif

#ifndef  vwindowINCLUDED
#include vwindowHEADER
#endif

#ifndef  vapplicationINCLUDED
#include vapplicationHEADER
#endif

#ifndef  vdialogINCLUDED
#include vdialogHEADER
#endif

#ifndef  veventINCLUDED
#include veventHEADER
#endif

#ifndef  vbuttonINCLUDED
#include vbuttonHEADER
#endif

#ifndef  vstartupINCLUDED
#include vstartupHEADER
#endif

#include "progress.h"

#if (vdebugDEBUG)

/*
 * Override the vdebugTAG in such a way that dumb compilers which don't
 * uniquify string constants won't create tons of tags
 */
static const char		_progressTAG[] = "main";
#define vdebugTAG		_progressTAG

#endif


#define ITERATION_MAX		10000


/*
 * Convenience for interning literal strings to galaxy's global
 * vname table
 */
#define _TAG(literal) vnameInternGlobalLiteral(literal)



/*
 * All work state that must be maintained from one iteration to the next
 * is stored here.  Nothing can be stored on the stack since the stack is
 * unrolled and rerolled each time iteration through the work.
 */
typedef struct work_t {
    progress_t		*progress;
    int			 iteration;
    vbutton		*button;

    int			 state;
    int			 of;
    int			 the;
    int			 work;
    int			 being;
    int			 done;
} work_t;


/*
 * Yicky global st we can position progress dialog wrt. the main
 * dialog window and stop all progress if user hits quit prematurely
 */
static int	quitting = FALSE;


/*
 * This is the basic work procedure.
 * It is called to do one iteration's worth of work
 * It then reposts it's continuation event so that it will get called again
 */
int DoAnIterationOfWork( vevent *event )
{
    work_t		*work;
    progress_t		*progress;
    int			 iteration;
    vbool		 doWork;
    vbutton		*button;

    vdebugTraceEnter( DoAnIterationOfWork );

    work = (work_t *) veventGetClientData( event );
    progress = work->progress;
    doWork = !quitting && vdialogIsOpen( progressGetDialog( progress ) );
    iteration = ++work->iteration;

    /*
     * We're about to do some work that will "block" us temporarily, so
     * we call the pre-block handler proc to give fair notice
     */
    if ( doWork )
    {
        (veventGetPreBlockHandlerProc())();

	/*
	 * Normally, real work would be done here, but for this example...
	 */
        work->state = rand() % 10 + 5;
	for (work->of=0, work->the=0; work->of < work->state; ++work->of)
	    work->the += work->of / work->state;
    
	/*
	 * Every now and then we update the progress indicator
	 */
	if ( iteration % 400 == 0 )
	{
	    progressSet( progress, (double)iteration / (double)ITERATION_MAX );
	}
    
    }
    /*
     * If the user hasn't dismissed us and we're not done, 
     * repost a continuation event. Note: it's ok to repost an 
     * existing vevent!
     */
    if ( doWork && iteration < ITERATION_MAX )
    {
        veventPost( event );
    }
    else
    {
	button = work->button;
	if (vbuttonGetData( button ) == progressGetDialog( progress ))
	    vbuttonSetData( button,
			   vdialogDetermineItemDialog(vbuttonGetItem(button)));
	progressDestroyLater( progress );
	vmemFree( work );
    }
    
    vdebugTraceLeave();

    /*
     * return TRUE to indicate that we handled this event
     */
    return TRUE;
}

/*
 * This procedure will get called once the progress dialog is initially 
 * opened. It will start the work process after the dialog has been 
 * successfully drawn so that we don't get any ugly, half-drawn dialogs 
 * on screen
 */
void HandleProgressOpen( vdialog *dialog, vevent *event )
{
    vevent	*newEvent;

    vdebugTraceEnter( HandleProgressOpen );

    newEvent = veventCreateClient();
    veventSetTarget( newEvent, DoAnIterationOfWork );
    veventSetClientData( newEvent, (work_t *) vdialogGetData( dialog ) );
    veventSetPriority( newEvent, veventPRIORITY_MIN );
    veventPost( newEvent );

    vdialogSetNotify( dialog, NULL );

    vdebugTraceLeave();
}

/*
 * This is the "New" button notify handler
 * It creates and initializes the work to be done, makes a progress indicator
 * dialog and waits for that dialog to be opened.
 */
void DoWork( vbutton *button, vevent *event )
{
    static int		 _numberwindows = 1;
    work_t		*work;
    progress_t		*progress;

    vdebugTraceEnter( DoWork );

    work = vmemAlloc( sizeof *work );
    progress = progressCreate();
    work->progress = progress;
    work->iteration = 0;
    work->button = button;

    vdialogSetTitleScribed( progressGetDialog( progress ), 
			    vnumScribeInt( _numberwindows++ ) );

    /*
     * You want to do work here, but you need to wait until the
     * progress indicator has actually been opened, so we wait for just
     * that to occur.
     */
    vdialogSetNotify( progressGetDialog( progress ), HandleProgressOpen );
    vdialogSetData( progressGetDialog( progress ), work );

    /*
     * Position the new progress dialog
     */
    vdialogPlace( progressGetDialog( progress ),
		 (vdialog *) vbuttonGetData( button ),
		 vrectPLACE_CENTER, vrectPLACE_NEAR );
    vbuttonSetData( button, progressGetDialog( progress ) );

    vdialogOpen( progressGetDialog( progress ) );

    vdebugTraceLeave();
}

/*
 * Called when something interesting happens to the dialog
 * We only care when it's closed so we can stop the program
 */
void HandleMainDialog( vdialog *dialog, vevent *event )
{
    vdebugTraceEnter( HandleMainDialog );
    
    if (veventIsClose( event ))
    {
	vdebugInform( "Dialog closed\n" );
	
	veventStopProcessing();
    }
    
    vdebugTraceLeave();
}

/*
 * This is the "Quit" button notify handler.
 * It stops the program.
 */
void DoQuit( vbutton *button, vevent *event )
{
    vdebugTraceEnter( DoQuit );

    quitting = TRUE;
    veventStopProcessing();

    vdebugTraceLeave();
}


/*
 * main
 */
int main( int argc, char *argv[] )
{
    vdialog		*dialog;
    vbutton		*button;
    vresource		 resource;
    
    /*
     * Initialize the galaxy runtime environment
     */
    vstartup( argc, argv );

    vdebugTraceEnter( main );


    /*
     * Load our main dialog from a resource file
     */
    resource = vapplicationGetResources( vapplicationGetCurrent() );
    resource = vresourceGet( resource, _TAG( "Dialog" ) );

    dialog = vdialogLoad( resource );
    vdialogSetNotify( dialog, HandleMainDialog );


    /*
     * Our "New" button for creating progress windows
     */
    button = (vbutton *) vdialogFindItem( dialog, _TAG("New") );
    vbuttonSetNotify( button, DoWork );
    vbuttonSetData( button, dialog );

    /*
     * Our "Quit" button
     */
    button = (vbutton *) vdialogFindItem( dialog, _TAG("Quit") );
    vbuttonSetNotify( button, DoQuit );


    /*
     * Open the main window
     */
    vwindowPlace( vdialogGetWindow( dialog ), vwindowGetRoot(), 
		  vrectPLACE_CENTER, vrectPLACE_TOP | vrectPLACE_INSET );
    vdialogOpen( dialog );


    /*
     * Process events until quit
     */
    veventProcess();


    /*
     * Clean up
     */
    vdialogDestroy( dialog );

    vdebugTraceLeave();


    /*
     * Leave
     */
    exit( EXIT_SUCCESS );
    return EXIT_FAILURE;
}


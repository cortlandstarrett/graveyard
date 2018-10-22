/* $Id: animcur.c,v 1.6 1996/03/18 20:32:11 stevek Exp $ */
/* 
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
 * copyright notice in the form of "Copyright 1995 Visix Software Inc.,
 * 11440 Commerce Park Drive, Reston, VA  22091. All Rights Reserved" appears
 * in all copies, (ii) both the copyright notice and this permission notice
 * appear in supporting documentation and (iii) you are a valid licensee of
 * Galaxy Application Environment.
 */
 
/* 
 * Executable Name: ac
 * Source Files:    ac.c
 * Resource Files:  ac.vr
 *
 * Managers Illustrated:
 *      Command, Cursor and Timer Managers.
 *
 * Description Of Sample:
 *      This demo shows how to do simple cursor animation with Galaxy.  Many
 *      of the attributes can be controlled within the resource file, and it
 *      is relatively simple to add animated cursors to existing programs.
 *
 *      A top-level dictionary is used to store two settings for the animated
 *      cursors as well as a dictionary containing the cursors themselves.  
 *      This sample looks for a dictionary named "AnimCursor" containing the
 *      following:
 *
 *      Tag        Description
 *      ---------------------------------------------------------------------
 *      Bounce     A boolean value for determing whether animation bounces
 *      FPS        An integer for setting the desired frames per second
 *      Cursors    Dictionary of vcursors
 * 
 *      There are additional animated cursors included with the sample.  To
 *      use these, rename them as "AnimCursor" within the Visual Resource
 *      Builder.
 *
 *      The functions below are used for setting up the animated cursors and
 *      using them.  You might, for example, use the start and stop functions
 *      below instead of the usual blocking (hourglass) cursor.
 *
 *      Function                Description
 *      ---------------------------------------------------------------------
 *      animcursorCreate        Creates and returns an anim cursor 
 *      animcursorDestroy       Frees resources associated with an anim cursor
 *      animcursorSetDialog     Sets the dialog an anim cursor is in
 *      animcursorStart         Starts the timer for the anim cursor
 *      animcursorStop          Stops the timer and restores the cursor
 *      animcursorTimerHandler  The timer handler for the anim cursor
 *
 * History:
 *      Written for 2.1 release November 1994
 */

#include <vport.h>

#include vstdlibHEADER
#include vrectHEADER
#include vclassHEADER
#include vnameHEADER
#include veventHEADER
#include vresourceHEADER
#include vwindowHEADER
#include vapplicationHEADER
#include vdialogHEADER
#include vstartupHEADER
#include vcommandHEADER
#include vcursorHEADER
#include vtimerHEADER
#include vmemHEADER
#include vtestHEADER

/* Tag function struct */
typedef struct
{
    const  char     *tagString;
    vcommandFunc     issueProc;
} tagFuncBindings;

/* Animated cursor struct */
typedef struct
{
    vcursor     **Cursors;     /* Array of pointers to vcursors */
    vcursor      *Default;     /* Default cursor for dialog     */
    int           Index;       /* Current frame                 */
    int           Delta;       /* Delta value for index         */
    int           Max;         /* Number of frames              */
    vbool         Bounce;      /* Bounce animation or not       */
    int           FPS;         /* Frames per second             */
    vdialog      *Dialog;      /* Dialog that cursor is in      */
    vtimer       *Timer;       /* Timer for cursor              */
    vbool         TimerOn;     /* Timer on/off boolean          */
} animCursorStruct;

/* Forward references */
static void dialogNotify(vdialog *dialog, vevent *event);
static void setFunctionCommands(vdialog *dialog, tagFuncBindings bindings[]);
static int  quitCommand(vcommandFunction *command, vdict *context);
static int  cursorTesterCommand(vcommandFunction *command, vdict *context);
animCursorStruct *animcursorCreate(const vname *animCursorTag);
static void animcursorDestroy(animCursorStruct *animCursor);
static void animcursorSetDialog(animCursorStruct *animCursor, vdialog *dialog);
static void animcursorStart(animCursorStruct *animCursor);
static void animcursorStop(animCursorStruct *animCursor);
static void animcursorTimerHandler(vtimer *timer);

int main (int argc, char **argv)
{
    animCursorStruct   *animCursor;
    vdialog            *dialog;
    vresource           resource;

    tagFuncBindings     bindings[] = 
    {   
	{ "cursorTesterCommand",     cursorTesterCommand },
	{ "quitCommand",             quitCommand         },
	{ NULL }
    }; 

    /* Initialize Galaxy */
    vstartup (argc, argv);

    /* Connect to any running testing tools */
    vtestStartup();

    /* Load the dialog from the application resource file. */
    resource = vresourceGet(vapplicationGetResources(vapplicationGetCurrent()),
			    vnameInternGlobalLiteral("Dialog"));
    dialog = vdialogLoad(resource);

    /* Set the dialog's notify */
    vdialogSetNotify(dialog, dialogNotify);

    /* Setup the function commands */
    setFunctionCommands(dialog, bindings);

    /* Create an animated cursor */
    animCursor = animcursorCreate(vnameInternGlobalLiteral("AnimCursor"));

    /* Set the animated cursor */
    animcursorSetDialog(animCursor, dialog);

    /* Open the dialog */
    vdialogOpen(dialog);

    /* Enter the event loop */
    veventProcess();

    /* Destroy the animated cursor */
    animcursorDestroy(animCursor);

    /* Destroy the dialog */
    vdialogDestroy(dialog);

    /* Exit */
    exit(EXIT_SUCCESS);
    return EXIT_FAILURE;
}
 
/* Create an animated cursor and return it */
animCursorStruct *animcursorCreate(const vname *animCursorTag)
{
    animCursorStruct   *animCursor;
    const vname        *tag;
    vresource           resource;
    vresource           cursorDict;
    vresource           cursorRes;
    int                 resCount;
    int                 index;

    /* allocate memory for the animCursorStruct */
    animCursor = (animCursorStruct *) vmemAlloc(sizeof(animCursorStruct));

    /* Initialize a few values */
    animCursor->Index = 0;
    animCursor->Max = 0;
    animCursor->Bounce = vFALSE;
    animCursor->FPS = 0;

    /* Get the dictionary containing the cursors */
    resource = vresourceGet(vapplicationGetResources(vapplicationGetCurrent()),
			    animCursorTag);

    /* See if there is an cursors dictionary */
    if (vresourceTestGet(resource, vnameInternGlobalLiteral("Cursors"),
			 &cursorDict))
    {
	/* Find out how many images are there */
	resCount = vresourceCountComponents(cursorDict);

	/* Allocate memory for the array of vcursor pointers */
	animCursor->Cursors = (vcursor **) vmemAlloc(sizeof(vcursor *) * 
						     resCount);

	/* Iterate over the cursors and load them */
	for (index = 0; index < resCount; index++)
	{	
	    tag = vresourceGetNthTag(cursorDict, index);

	    /* Get the cursor resource */
	    cursorRes = vresourceGet(cursorDict, tag);

	    /* Load the cursor */
	    animCursor->Cursors[animCursor->Index] = vcursorLoad(cursorRes);

	    /* Check to see that a cursor was loaded */
	    if (animCursor->Cursors[animCursor->Index] != NULL)
	    {
		/* Increment the index */
		animCursor->Index++;	    
		animCursor->Max++;
	    }
	}
    }

    /* Get the desired frames per second */
    vresourceTestGetInteger(resource, vnameInternGlobalLiteral("FPS"),
				 &animCursor->FPS);

    /* Get the bounce setting */
    vresourceTestGetBoolean(resource, vnameInternGlobalLiteral("Bounce"),
			    &animCursor->Bounce);

    /* Set index and delta values */
    animCursor->Index = 0;
    animCursor->Delta = 1;

    /* Setup a timer */
    animCursor->Timer = vtimerCreate();
    vtimerSetRecurrent(animCursor->Timer);
    vtimerSetNotify(animCursor->Timer, animcursorTimerHandler);

    /* Set the number of frames per second desired */
    vtimerSetPeriod(animCursor->Timer, 0, (1000000000 / animCursor->FPS));

    /* Set the timer's data pointer to the animCursor */
    vtimerSetData(animCursor->Timer, animCursor);

    /* Set the flag */
    animCursor->TimerOn = FALSE;

    /* Return the cursor */
    return animCursor;
}

/* Destroy an animated cursor */
static void animcursorDestroy(animCursorStruct *animCursor)
{
    int index;

    /* Destroy the timer */
    vtimerDestroy(animCursor->Timer);

    /* Destroy each vcursor */
    for (index = 0; index < animCursor->Max; index++)
    {
	if (animCursor->Cursors[index])
	    vcursorDestroy(animCursor->Cursors[index]);
    }

    /* Free the memory for the array of vcursor pointers */
    if (animCursor->Cursors)
        vmemFree(animCursor->Cursors);

    /* Free the memory for the animCursorStruct */
    if (animCursor)
        vmemFree(animCursor);

}

/* Set the dialog that an animated cursor is in */ 
static void animcursorSetDialog(animCursorStruct *animCursor, vdialog *dialog)
{
    /* Check to see if dialog is non-null */
    if (dialog)
    {
	animCursor->Dialog = dialog;

	/* Set the dialog's data pointer to the animated cursor */
	vdialogSetData(dialog, animCursor);
    }
}

/* Start the animated cursor */
static void animcursorStart(animCursorStruct *animCursor)
{
    vwindow *window;

    if (animCursor->Max > 0)
    {
	/* Get the window for the dialog */
	window = vdialogGetWindow(animCursor->Dialog);

	/* Determine the default cursor */
	animCursor->Default = vwindowDetermineCursor(window);
    
	/* Set the index to zero */
	animCursor->Index = 0;

	/* Set the flag */
	animCursor->TimerOn = TRUE;

	/* Turn the timer on */
	vtimerStart(animCursor->Timer);
    }
}

/* Stop the animated cursor */
static void animcursorStop(animCursorStruct *animCursor)
{
    if (animCursor->Max > 0)
    {
	/* Set the flag */
	animCursor->TimerOn = FALSE;

	/* Turn the timer off */
	vtimerStop(animCursor->Timer);

	/* Restore the default cursor */
	vwindowSetCursor(vdialogGetWindow(animCursor->Dialog),
			 animCursor->Default);
    }
}

/* Timer handler for cursor animation */
static void animcursorTimerHandler(vtimer *timer)
{
    animCursorStruct *animCursor;

    /* Get the animCursorStruct pointer */
    animCursor = (animCursorStruct *) vtimerGetData(timer);

    /* Set the cursor */
    if (animCursor->Dialog)
    {
	vwindowSetCursor(vdialogGetWindow(animCursor->Dialog),
			 animCursor->Cursors[animCursor->Index]); 
    }

    /* Increment the index by the delta */
    animCursor->Index += animCursor->Delta;

    /* See if we need to bounce or wrap */
    if (animCursor->Bounce)
    {
	/* Check for bounds and change delta if necessary */
	if ((animCursor->Index >= (animCursor->Max - 1)) ||
	    (animCursor->Index <= 0))
	{
	    animCursor->Delta = -animCursor->Delta;
	}
    }
    else
    {
	/* Check for bounds and wrap if necessary */
	if (animCursor->Index >= animCursor->Max)
	{
	    animCursor->Index = 0;
	}
    }       
}

/* Quit command function */
static int quitCommand(vcommandFunction *command, vdict *context)
{
    veventStopProcessing();
 
    return TRUE;
}

/* Cursor tester command function */
static int cursorTesterCommand(vcommandFunction *command, vdict *context)
{
    vdialog *dialog;
    animCursorStruct *animCursor;

    dialog = (vdialog *) vdictLoad(context,vname_Dialog);

    animCursor = (animCursorStruct *) vdialogGetData(dialog);

    if (animCursor->TimerOn)
    {
	animcursorStop(animCursor);
    }
    else
    {
	animcursorStart(animCursor);
    }

    return TRUE;
}

/* Dialog notification procedure */
static void dialogNotify(vdialog *dialog, vevent *event)

{
    /* Check for a window close event */
    if ((veventGetType(event) == veventWINDOW_STATE) && 
	veventIsClose(event))
    {
        veventStopProcessing();
    }
}

/* convenience function for setting function commands */
void setFunctionCommands(vdialog *dialog, tagFuncBindings bindings[])
{
    vcommandSpace     *commandSpace;
    vdict             *commandDictionary;
    vcommandFunction  *functionCommand;
    tagFuncBindings   *bindPtr;
    
    commandDictionary = vdictCreate(vnameHash);
 
    for(bindPtr = bindings; bindPtr->tagString != NULL; bindPtr++)
    {
        functionCommand = vcommandCreateFunction();
	vcommandSetFunctionIssue(functionCommand, bindPtr->issueProc);
	vdictStore(commandDictionary,
                   vnameInternGlobalLiteral(bindPtr->tagString), 
                   functionCommand);
    }
    commandSpace = vcommandCreateSpace();
    vcommandAddSpaceDictOwned(commandSpace,
                              vname_Command,
                              commandDictionary);
    vwindowSetSpaceOwned(vdialogGetWindow(dialog), commandSpace);
}

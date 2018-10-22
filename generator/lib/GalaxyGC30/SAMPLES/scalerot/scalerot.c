/* $Id: scalerot.c,v 1.5 1995/04/25 14:47:43 dangi Exp $ */
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
 * copyright notice in the form of "Copyright 1994 Visix Software Inc.,
 * 11440 Commerce Park Drive, Reston, VA  22091. All Rights Reserved" appears
 * in all copies, (ii) both the copyright notice and this permission notice
 * appear in supporting documentation and (iii) you are a valid licensee of
 * Galaxy Application Environment.
 */

/* 
 * Executable Name: scalerot
 * Source Files:    scalerot.c
 * Resource Files:  scalerot.vr
 *
 * Managers Illustrated:
 *      Class, Color, Command, and Draw.
 *
 * Description Of Sample:
 *      This sample rotates and scales an image while keeping it centered
 *      within the dialog.  It provides a slider for each of these operations
 *      and commands to scale and rotate through a range, as well as one for
 *      quitting the demo.  These commands may be accessed through buttons and
 *      through menus.  The image may be changed by editing the resource file.
 *
 * History:
 *      Written for 2.0 release June 1994.  
 *      Cleaned up for 2.1 release November 1994.
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
#include vcontainerHEADER
#include vstartupHEADER
#include vcontrolHEADER
#include vspinnerHEADER
#include vdrawHEADER
#include vcommandHEADER
#include vnumHEADER
#include vtimerHEADER

/* Structs */
typedef struct
{
    vimage         *demoImage;
    vimage         *destImage;
    vdialogItem    *Canvas;
    vwindow        *Window;
    const vrect    *Rect;
    vcolor         *Background;
    vtimer         *Timer;
    vcontrol       *scaleSlider;
    vcontrol       *rotateSlider;
    vspinner       *speedSpinner;
    vdialogItem    *scaleLabel;
    vdialogItem    *rotateLabel;
    vrect           imageRect;
    int             imageMax;
    int             imageWidth;
    int             imageHeight;
    int             lastRotation;
    double          lastScaling;
    vbool           rotateOn;
    vbool           scaleOn;
    int             rotateDelta;
    double          scaleDelta;
    int             timerSpeed;
} canvasStruct;

/* Forward references */
static void dialogNotify(vdialog *dialog, vevent *event);
static void rotateSlider(vcontrol *control, vevent *event);
static void scaleSlider(vcontrol *control, vevent *event);
static void speedSpinner(vspinner *spinner, vevent *event);
static void drawCanvas(vdialogItem *canvas);
static void drawImageInCanvas(canvasStruct *canvasInfo,
			      int rotation, double scaling);
static int  quitCommand(vcommandFunction *command, vdict *context);
static int  rotateOnCommand(vcommandFunction *command, vdict *context);
static int  scaleOnCommand(vcommandFunction *command, vdict *context);
static int  rotateGoCommand(vcommandFunction *command, vdict *context);
static int  scaleGoCommand(vcommandFunction *command, vdict *context);
static void repeatTimerHandler(vtimer *timer);
static void checkTimer(canvasStruct *canvasInfo);
static void setFunctionCommands(vdialog *dialog, 
				vcommandFunctionTemplate commandBindings[],
				int commandCount);

int main(int argc, char **argv)
{
    vdialogItemClass *canvasClass;
    vdialog          *dialog;
    vcontainer       *container;
    canvasStruct      canvasInfo;
    vresource         resource;
    int               commandCount;

    vcommandFunctionTemplate commands[] = 
    {
	{"QuitCommand",        quitCommand,        NULL},
	{"RotateOnCommand",    rotateOnCommand,    NULL},
	{"ScaleOnCommand",     scaleOnCommand,     NULL},
	{"RotateGoCommand",    rotateGoCommand,    NULL},
	{"ScaleGoCommand",     scaleGoCommand,     NULL},
    }; 
    
    commandCount = sizeof(commands) / sizeof(commands[0]);

    /* Initialize Galaxy */
    vstartup (argc, argv);

    /* Create the canvas subclass */
    canvasClass = vclassReproduce(vdialogGetDefaultItemClass());
    vclassSetNameScribed(canvasClass, 
			 vcharScribeLiteral("CanvasItem"));

    /* Override the draw method */
    vclassSet(canvasClass, vdialogDRAW_ITEM, drawCanvas);

    /* Load the dialog and set its notify and data */
    resource = vresourceGet(vapplicationGetResources(vapplicationGetCurrent()),
			    vnameInternGlobalLiteral("Dialog"));
    dialog = vdialogLoad(resource);
    vdialogSetData(dialog, &canvasInfo);
    vdialogSetNotify(dialog, dialogNotify);

    /* Setup the command space for the dialog */
    setFunctionCommands(dialog, commands, commandCount);

    /* Load the canvas */
    canvasInfo.Canvas = vdialogFindItem(dialog, 
					vnameInternGlobalLiteral("Canvas"));
    vdialogSetItemData(canvasInfo.Canvas, &canvasInfo);
    canvasInfo.Background = vdialogDetermineItemBackground(canvasInfo.Canvas);

    /* Load the rotate slider and set its notify and data */
    canvasInfo.rotateSlider = (vcontrol *) vdialogFindItem(dialog,
			          vnameInternGlobalLiteral("RotateSlider"));
    vcontrolSetNotify(canvasInfo.rotateSlider, rotateSlider);
    vcontrolSetData(canvasInfo.rotateSlider, &canvasInfo);
    canvasInfo.lastRotation = vcontrolGetValue(canvasInfo.rotateSlider);
    canvasInfo.rotateDelta = vcontrolGetPage(canvasInfo.rotateSlider);

    /* Load the scale slider and set its notify and data */
    canvasInfo.scaleSlider = (vcontrol *) vdialogFindItem(dialog,
			         vnameInternGlobalLiteral("ScaleSlider"));
    vcontrolSetNotify(canvasInfo.scaleSlider, scaleSlider);
    vcontrolSetData(canvasInfo.scaleSlider, &canvasInfo);
    canvasInfo.lastScaling = (((double) vcontrolGetValue(canvasInfo.scaleSlider)) / 
			      (double) 100.0);
    canvasInfo.scaleDelta = (((double) vcontrolGetPage(canvasInfo.scaleSlider)) / 
			     (double) 100.0);

    /* Find the values container */
    container = (vcontainer *) vdialogFindItem(dialog,
			       vnameInternGlobalLiteral("ValuesContainer"));

    /* Load the rotate label */
    canvasInfo.rotateLabel = vcontainerFindItem(container,
						vnameInternGlobalLiteral("RotateLabel"));
    vdialogSetItemTitleScribed(canvasInfo.rotateLabel, 
			       vnumScribeInt(canvasInfo.lastRotation));

    /* Load the scale label */
    canvasInfo.scaleLabel = vcontainerFindItem(container,
					       vnameInternGlobalLiteral("ScaleLabel"));
    vdialogSetItemTitleScribed(canvasInfo.scaleLabel, 
			       vnumScribeFloatFormatted(canvasInfo.lastScaling,
							vnumGetDecimalDigitSet(), 
							vnumGetNormalFormat(),
							NULL, TRUE, 2));

    /* Find the repeat container */
    container = (vcontainer *) vdialogFindItem(dialog,
			       vnameInternGlobalLiteral("RepeatContainer"));

    /* Load the speed slider and set its notify and data */
    canvasInfo.speedSpinner = (vspinner *) vcontainerFindItem(container,
			          vnameInternGlobalLiteral("SpeedSpinner"));
    vspinnerSetNotify(canvasInfo.speedSpinner, speedSpinner);
    vspinnerSetData(canvasInfo.speedSpinner, &canvasInfo);
    canvasInfo.timerSpeed = vspinnerGetValue(canvasInfo.speedSpinner);

    /* Load the demo image */
    resource = vresourceGet(vapplicationGetResources(vapplicationGetCurrent()),
			  vnameInternGlobalLiteral("Image"));
    canvasInfo.demoImage = vimageLoad(resource);
    vrectSet(0, 0, 
	     vimageGetWidth(canvasInfo.demoImage), 
	     vimageGetHeight(canvasInfo.demoImage), 
	     &canvasInfo.imageRect);

    /* Set the destination image to null */
    canvasInfo.destImage = NULL;

    /* Center the window */
    vwindowPlace(vdialogGetWindow(dialog), vwindowGetRoot(),
		 vrectPLACE_CENTER, vrectPLACE_CENTER);

    /* Open the dialog */
    vdialogOpen(dialog);

    /* Get the canvas' window */
    canvasInfo.Window = vdialogDetermineItemWindow(canvasInfo.Canvas);

    /* Set the booleans */
    canvasInfo.rotateOn = FALSE;
    canvasInfo.scaleOn = FALSE;

    /* Setup a timer */
    canvasInfo.Timer = vtimerCreate();
    vtimerSetRecurrent(canvasInfo.Timer);
    vtimerSetNotify(canvasInfo.Timer, repeatTimerHandler);

    /* Set timer's period to get 3 fps */
    vtimerSetPeriod(canvasInfo.Timer, 0, (vtimestampSECOND / canvasInfo.timerSpeed));

    /* Set the timer's data pointer to the canvas info */
    vtimerSetData(canvasInfo.Timer, &canvasInfo);

    /* Enter the event loop */
    veventProcess();

    /* Return resources to the system */
    vtimerDestroy(canvasInfo.Timer);
    vdialogDestroy(dialog);
    vimageDestroy(canvasInfo.demoImage);
    vimageDestroy(canvasInfo.destImage);

    vclassDestroy(canvasClass);

    exit (EXIT_SUCCESS);
    return EXIT_FAILURE;
}

/* Quit command function */
static int quitCommand(vcommandFunction *command, vdict *context)
{
    veventStopProcessing();
 
    return TRUE;
}


static void checkTimer(canvasStruct *canvasInfo)
{
    if (canvasInfo->rotateOn || canvasInfo->scaleOn)
    {
	vtimerStart(canvasInfo->Timer);
    }
    else
    {
	vtimerStop(canvasInfo->Timer);

	/* Update the sliders */
	vcontrolSetValue(canvasInfo->scaleSlider, (int) (canvasInfo->lastScaling * 100));
	vcontrolSetValue(canvasInfo->rotateSlider, canvasInfo->lastRotation);

	/* Update the labels */
	vdialogSetItemTitleScribed(canvasInfo->rotateLabel, 
				   vnumScribeInt(canvasInfo->lastRotation));
	vdialogSetItemTitleScribed(canvasInfo->scaleLabel,
				   vnumScribeFloatFormatted(canvasInfo->lastScaling,
							    vnumGetDecimalDigitSet(), 
							    vnumGetNormalFormat(),
							    NULL, TRUE, 2));
    }
}

static int rotateOnCommand(vcommandFunction *command, vdict *context)
{
    canvasStruct  *canvasInfo;
    vdialog       *dialog;

    /* Get the data from the context */
    dialog = (vdialog *) vdictLoad(context, vname_Dialog);
    canvasInfo = (canvasStruct *) vdialogGetData(dialog);

    /* Toggle the rotation */
    if (canvasInfo->rotateOn)
        canvasInfo->rotateOn = FALSE;
    else
        canvasInfo->rotateOn = TRUE;

    /* Start or stop the timer */
    checkTimer(canvasInfo);

    return TRUE;
}

static int scaleOnCommand(vcommandFunction *command, vdict *context)
{
    canvasStruct  *canvasInfo;
    vdialog       *dialog;

    /* Get the data from the context */
    dialog = (vdialog *) vdictLoad(context, vname_Dialog);
    canvasInfo = (canvasStruct *) vdialogGetData(dialog);

    if (canvasInfo->scaleOn)
        canvasInfo->scaleOn = FALSE;
    else
    {
        canvasInfo->scaleOn = TRUE;

	/* Set delta based on current size */
	if ((canvasInfo->lastScaling >= 1.0) && (canvasInfo->scaleDelta > 0))
	{
	    /* Reverse the scale delta */
	    canvasInfo->scaleDelta = -canvasInfo->scaleDelta;
	}

	if (canvasInfo->lastScaling <= fabs(canvasInfo->scaleDelta))
	{
	    /* Reverse the scale delta */
	    canvasInfo->scaleDelta = -canvasInfo->scaleDelta;
	}
    }

    /* Start or stop the timer */
    checkTimer(canvasInfo);

    return TRUE;
}

static int scaleGoCommand(vcommandFunction *command, vdict *context)
{
    canvasStruct  *canvasInfo;
    vdialog       *dialog;
    vcontainer    *container;
    int            value;
    double         scale, last, inc;

    /* Get the data from the context */
    dialog = (vdialog *) vdictLoad(context, vname_Dialog);
    canvasInfo = (canvasStruct *) vdialogGetData(dialog);
    container = (vcontainer *) vdialogFindItem(dialog,
			       vnameInternGlobalLiteral("ScaleContainer"));

    /* Get the last scaling value */
    last = canvasInfo->lastScaling;

    /* Get the spinner value and compute the increment */
    value = vspinnerGetValue((vspinner *) vcontainerFindItem(container,
			     vnameInternGlobalLiteral("ScaleIncSpinner")));
    inc = last / (double) value;

    /* Check for zooming direction */
    if (vcontrolGetValue((vcontrol *) vcontainerFindItem(container,
			 vnameInternGlobalLiteral("ZoomInOn"))))
    {
	/* Zoom in until size is just greater than increment */
	for (scale = last; scale > inc; scale -= inc)
            drawImageInCanvas(canvasInfo, canvasInfo->lastRotation, scale);

	/* Zoom back out to original size */
	for (; scale <= last; scale += inc)
            drawImageInCanvas(canvasInfo, canvasInfo->lastRotation, scale);
    }
    else
    {
	/* Zoom out until image is 2X size */
	for (scale = last; scale < (last * 2); scale += inc)
            drawImageInCanvas(canvasInfo, canvasInfo->lastRotation, scale);

	/* Zoom back in to original size */
	for (; scale >= last; scale -= inc)
            drawImageInCanvas(canvasInfo, canvasInfo->lastRotation, scale);
    }

    /* Return to original position */
    drawImageInCanvas(canvasInfo, canvasInfo->lastRotation, last);

    /* Update the sliders */
    vcontrolSetValue(canvasInfo->scaleSlider, (int) (canvasInfo->lastScaling * 100));
    vcontrolSetValue(canvasInfo->rotateSlider, canvasInfo->lastRotation);

    return TRUE;
}

static int rotateGoCommand(vcommandFunction *command, vdict *context)
{
    canvasStruct  *canvasInfo;
    vdialog       *dialog;
    vcontainer    *container;
    int            rotation, last, inc;
    int            angle;

    /* Get the data from the context */
    dialog = (vdialog *) vdictLoad(context, vname_Dialog);
    canvasInfo = (canvasStruct *) vdialogGetData(dialog);
    container = (vcontainer *) vdialogFindItem(dialog,
			       vnameInternGlobalLiteral("RotateContainer"));

    /* Get the last rotation value */
    last = canvasInfo->lastRotation;

    /* Get the increment */
    inc = vspinnerGetValue((vspinner *) vcontainerFindItem(container,
			   vnameInternGlobalLiteral("RotateIncSpinner")));

    /* Check the direction to rotate */
    if (vcontrolGetValue((vcontrol *) vcontainerFindItem(container,
			 vnameInternGlobalLiteral("ClockwiseOn"))))
    {
	/* Rotate clockwise 360 degrees by increment */
	for (rotation = last; rotation > (last - 360); rotation -= inc)
	{
	    /* Check rotation value */
	    if (rotation >= 180)
	        angle = (rotation - 360);
	    else
	        angle = rotation;

	    /* Draw image using new rotation */
	    drawImageInCanvas(canvasInfo, angle, 
			      canvasInfo->lastScaling);
	}
    }
    else
    {
	/* Rotate 360 degrees counter-clockwise by increment */
	for (rotation = last; rotation < (last + 360); rotation += inc)
	{
	    /* Check rotation value */
	    if (rotation <= -180)
	        angle = (rotation + 360);
	    else
	        angle = rotation;

	    /* Draw image using new rotation */
	    drawImageInCanvas(canvasInfo, angle, 
			      canvasInfo->lastScaling);
	}
    }

    /* Return to original position */
    drawImageInCanvas(canvasInfo, last, canvasInfo->lastScaling);

    /* Update the sliders */
    vcontrolSetValue(canvasInfo->scaleSlider, (int) (canvasInfo->lastScaling * 100));
    vcontrolSetValue(canvasInfo->rotateSlider, canvasInfo->lastRotation);

    return TRUE;
}

static void repeatTimerHandler(vtimer *timer)
{
    canvasStruct *canvasInfo;
    int           rotate;
    double        scale;

    canvasInfo = (canvasStruct *) vtimerGetData(timer);

    /* See if rotation is turned on */
    if (canvasInfo->rotateOn)
    {
	/* Compute the new rotation */
	rotate = canvasInfo->lastRotation + canvasInfo->rotateDelta;
    }
    else
        rotate = canvasInfo->lastRotation;
    
    /* See if scaling is turned on */
    if (canvasInfo->scaleOn)
    {
	scale = canvasInfo->lastScaling + canvasInfo->scaleDelta;

	/* See if size is greater than 1X and scale delta is positive */
	if ((scale > (1.0 - fabs(canvasInfo->scaleDelta))) && 
	    (canvasInfo->scaleDelta > 0))
	{
	    /* Reverse the scale delta */
	    canvasInfo->scaleDelta = -canvasInfo->scaleDelta;

	    /* Check size */
	    scale += canvasInfo->scaleDelta;

	    /* Reverse the rotation delta */
	    canvasInfo->rotateDelta = -canvasInfo->rotateDelta;
	}

	/* See if size is less than delta */
	if (scale < fabs(canvasInfo->scaleDelta))
	{
	    /* Reverse the scale delta */
	    canvasInfo->scaleDelta = -canvasInfo->scaleDelta;
	    
	    /* Check size */
	    scale += canvasInfo->scaleDelta;
	}
    }
    else
        scale = canvasInfo->lastScaling;

    /* Draw it */
    drawImageInCanvas(canvasInfo, rotate, scale); 
       
    /* Update the labels */
    vdialogSetItemTitleScribed(canvasInfo->rotateLabel, 
			       vnumScribeInt(canvasInfo->lastRotation));
    vdialogSetItemTitleScribed(canvasInfo->scaleLabel,
			       vnumScribeFloatFormatted(canvasInfo->lastScaling,
							vnumGetDecimalDigitSet(), 
							vnumGetNormalFormat(),
							NULL, TRUE, 2));
}

static void drawImageInCanvas(canvasStruct *canvasInfo,
			      int rotation, double scaling)
{
    /* Do a bit of error avoidance */
    if (scaling <= 0.0)
        scaling = 0.01;

    if (rotation > 180)
        rotation -= 360;

    if (rotation < -180)
        rotation += 360;

    /* Set the destination image as the device */
    vdrawImageDevice(canvasInfo->destImage);

    /* Set the color and fill the area */
    vdrawSetColor(canvasInfo->Background);
    vdrawRectFill(0, 0, canvasInfo->imageWidth, canvasInfo->imageHeight);

    /* Translate to origin, rotate, scale, and move back */
    vdrawTranslate((canvasInfo->imageWidth / 2), 
		   (canvasInfo->imageHeight / 2));
    vdrawRotate(rotation);
    vdrawFScale(scaling, scaling);
    vdrawMoveTo(-(canvasInfo->imageRect.w / 2), 
		-(canvasInfo->imageRect.h / 2));

    /* Draw the image */
    vdrawImageIdent(canvasInfo->demoImage);

    /* Set window as device*/
    vwindowDrawDevice(canvasInfo->Window);

    /* Move to coordinates and draw them image */
    vdrawMoveTo(canvasInfo->Rect->x, canvasInfo->Rect->y);
    vdrawImageIdent(canvasInfo->destImage);
    
    /* Set the last values */
    canvasInfo->lastScaling = scaling;
    canvasInfo->lastRotation = rotation;

}

/* Rotation slider notification procedure */
static void rotateSlider(vcontrol *control, vevent *event)
{
    canvasStruct *canvasInfo;

    canvasInfo = (canvasStruct *) vcontrolGetData(control);

    /* Draw image using new slider value */
    drawImageInCanvas(canvasInfo, vcontrolGetValue(control), 
		      canvasInfo->lastScaling);

    /* Update the labels */
    vdialogSetItemTitleScribed(canvasInfo->rotateLabel, 
			       vnumScribeInt(canvasInfo->lastRotation));
}

/* Scale slider notification procedure */
static void scaleSlider(vcontrol *control, vevent *event)
{
    canvasStruct *canvasInfo;
    double        newScaling;

    canvasInfo = (canvasStruct *) vcontrolGetData(control);

    /* Compute the new scaling factor based on the control value */
    newScaling = ((double) vcontrolGetValue(control)) / ((double) 100.0);

    /* Draw the image using the new value */
    drawImageInCanvas(canvasInfo, canvasInfo->lastRotation, newScaling);

    /* Update the labels */
    vdialogSetItemTitleScribed(canvasInfo->scaleLabel,
			       vnumScribeFloatFormatted(canvasInfo->lastScaling,
							vnumGetDecimalDigitSet(), 
							vnumGetNormalFormat(),
							NULL, TRUE, 2));
}

/* Speed spinner notification procedure */
static void speedSpinner(vspinner *spinner, vevent *event)
{
    canvasStruct *canvasInfo;

    canvasInfo = (canvasStruct *) vspinnerGetData(spinner);

    /* Get the timer speed from the spinner */
    canvasInfo->timerSpeed = vspinnerGetValue(spinner);

    /* Set the timer period */
    vtimerSetPeriod(canvasInfo->Timer, 0, (vtimestampSECOND / canvasInfo->timerSpeed));
}

/* New draw function for the canvas subclass */
static void drawCanvas(vdialogItem *canvas)
{
    canvasStruct *canvasInfo;

    canvasInfo = (canvasStruct *) vdialogGetItemData(canvas);

    /* Get the canvas's rect */
    canvasInfo->Rect = vdialogGetItemRect(canvas);
    
    /* Get rid of old image, find new size, and create new image */
    if (canvasInfo->destImage != NULL) 
	vimageDestroy(canvasInfo->destImage);

    if (canvasInfo->Rect->w < canvasInfo->Rect->h) 
	canvasInfo->imageMax = canvasInfo->Rect->w;
    else 
	canvasInfo->imageMax = canvasInfo->Rect->h;
    
    canvasInfo->destImage = vwindowCreateBufferImage(canvasInfo->Rect->w,
				     canvasInfo->Rect->h);   

    canvasInfo->imageWidth = canvasInfo->Rect->w;
    canvasInfo->imageHeight = canvasInfo->Rect->h;
   
    /* Draw our image in the canvas */
    drawImageInCanvas(canvasInfo, canvasInfo->lastRotation, 
		      canvasInfo->lastScaling);
}

/* Dialog notification procedure */
static void dialogNotify(vdialog *dialog, vevent *event)
{
    if ((veventGetType(event) == veventWINDOW_STATE) && veventIsClose(event)) 
        veventStopProcessing();
}

/* Convenience function for setting function commands */
void setFunctionCommands(vdialog *dialog, vcommandFunctionTemplate commandBindings[],
                         int commandCount)
{
    vcommandSpace     *commandSpace;
    vdict             *commandDictionary;
 
    if ((commandSpace = vapplicationGetSpace(vapplicationGetCurrent())) == NULL)
    {
        commandSpace = vcommandCreateSpace();
        vapplicationSetSpaceOwned(vapplicationGetCurrent(), commandSpace);
    }
 
    commandDictionary = vcommandCreateDictFunctionTemplates(commandBindings, commandCount);
 
    vcommandAddSpaceDictOwned(commandSpace, vname_Command, commandDictionary);
}

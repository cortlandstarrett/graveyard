/* $Id: drawboth.c,v 1.16 1997/09/18 19:02:26 shawn Exp $
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
 * copyright notice in the in the form of "Copyright 1992 Visix Software Inc.,
 * 11440 Commerce Park Drive, Reston, VA  22091. All Rights Reserved" appears
 * in all copies, (ii) both the copyright notice and this permission notice
 * appear in supporting documentation and (iii) you are a valid licensee of
 * Galaxy Application Environment.
 */

#include "vport.h"
#include vhelpgalaxyHEADER

/* Private headers */
#include "drawdemo.h"

/**********
 * Control variables:
 **********/

vbool                           drawdemoIsDedicated = FALSE;
vbool                           drawdemoDoStartOver = TRUE;
vbool                           drawdemoDoStopAtNext = FALSE;
vbool                           drawdemoIsHalted = FALSE;

/**********
 * State variables:
 **********/

vdrawGState                     *drawdemoGState = NULL;
vfont                           *drawdemoFont = NULL;
vcolorSpec                       spec;
vcolor                          *drawdemoColor = NULL;
int                              drawdemoObjectCount = 100;
int                              drawdemoObjectType = drawdemoDRAW_LINES;
vbool                            drawdemoDoDashed = FALSE;
vbool                            drawdemoIsMonochrome = FALSE;
vbool                            drawdemoDoChangeFont = FALSE;
int                              drawdemoFillType = drawdemoSTROKE;

/**********
 * User interface variables:
 **********/

vdialogClass                    *drawdemoHookedDialogClass;
vdialog                         *drawdemoDialog = NULL;

vdialogItemClass                *drawdemoFabricClass;
vdialogItem                     *drawdemoFabric;

vcontrol                        *drawdemoDedicatedCheckBox = NULL;
vcontrol                        *drawdemoOneAtTimeCheckBox = NULL;
vtextitem                       *drawdemoObjectCountText = NULL;
vcontrol                        *drawdemoObjectTypePopup = NULL;
vmenu                           *drawdemoObjectTypePopupMenu = NULL;
vcontrol                        *drawdemoMonochromeCheckBox = NULL;
vcontrol                        *drawdemoExclusiveOrCheckBox = NULL;
vcontrol                        *drawdemoFillTypePopup = NULL;
vmenu                           *drawdemoFillTypePopupMenu = NULL;
vtextitem                       *drawdemoRotateAngleText = NULL;
vtextitem                       *drawdemoScaleXText = NULL;
vtextitem                       *drawdemoScaleYText = NULL;
vtextitem                       *drawdemoLineWidthText = NULL;
vtextitem                       *drawdemoFlatnessText = NULL;
vcontrol                        *drawdemoDashedCheckBox = NULL;
vcontrol                        *drawdemoLineCapPopup = NULL;
vmenu                           *drawdemoLineCapPopupMenu = NULL;
vcontrol                        *drawdemoLineJoinPopup = NULL;
vmenu                           *drawdemoLineJoinPopupMenu = NULL;
vtextitem                       *drawdemoMiterLimitText = NULL;
vbutton                         *drawdemoStartButton = NULL;
vbutton                         *drawdemoChangeFontButton = NULL;
vbutton                         *drawdemoCloseButton = NULL;

vfontchsr                       *drawdemoFontChooser = NULL;

/**********
 * Values used to build option menus (should be in resource file):
 **********/

int                             drawdemoObjectTypeValues[drawdemoOBJECT_TYPES]
  = { drawdemoDRAW_LINES, drawdemoDRAW_RECTS, drawdemoDRAW_CURVES,
      drawdemoDRAW_CW_ARCS, drawdemoDRAW_TEXT };

int                             drawdemoFillTypeValues[drawdemoFILL_TYPES]
  = { drawdemoSTROKE, drawdemoFILL, drawdemoEO_FILL, drawdemoCLIP,
      drawdemoEO_CLIP, drawdemoBORDERED };

int                             drawdemoLineCapValues[drawdemoLINE_CAPS]
  = { vdrawCAP_BUTT, vdrawCAP_PROJECTING, vdrawCAP_ROUND };

int                             drawdemoLineJoinValues[drawdemoLINE_JOINS]
  = { vdrawJOIN_BEVEL, vdrawJOIN_MITER, vdrawJOIN_ROUND };

/**********
 * Short strings to draw text objects (should be in resource file):
 **********/

const char                      *drawdemoPhrases[drawdemoPHRASES]
  = { "class", "application", "window", "dialog", "menu", "pinned menu",
      "dialog item", "control", "toggle", "slider", "scroll bar",
      "option menu", "button", "container", "text", "icon", "box",
      "list", "palette", "menu bar", "domain", "ruler", "drag box",
      "time item", "menu item", "push pin", "separator", "toggle", "sub-menu"};


/**********
 * main:
 *
 **********/
int main(int argc, char *argv[])
{
    
    /*
     * Read user preferences from the command line arguments:
     */
    vstartup(argc, argv);

    /*
     * Force use of MSWindows help system, if it's here
     */
    if (vhelpMSWindowsHelpSystemIsAvailable ())
    { 
      vhelpUseMSWindowsHelpSystem ();
    }
    else
    {
      vhelpgalaxyStartupGalaxy();
    }
    
    /*
     * Initialize the randomizer:
     */
    srand(time((time_t *)NULL));
    
    /*
     * Make the custom classes for the demo
     */
    drawdemoMakeClasses();
    
    /*
     * Setup the draw demo global variables (dialog):
     */
    drawdemoLoad();
    
    /*
     * Since the drawing tends to suck on servers a little, we will
     * force on the one check box:
     */
    vcontrolSetValue(drawdemoOneAtTimeCheckBox, 1);
    
    /*
     * Bind the notify procs:
     */
    drawdemoSetNotifyStuff();
    
    /*
     * Open the draw demo main dialog:
     */
    drawdemoOpen();
    
    /*
     * Process events until the window is closed:
     */
    veventProcess();
    
    /*
     * Free up all items pointed to by draw demo global variables:
     */
    drawdemoUnload();
    
    exit( EXIT_SUCCESS );
    return EXIT_FAILURE;
}  /**  main()  **/


/**********
 * drawdemoMakeClasses:
 *      Makes the custom classes for the draw demos
 *
 **********/
void drawdemoMakeClasses(void)
{
    vstr                                *title;
    
    /*
     * Customize the dialog class to intercept button down events:
     */
    
    drawdemoHookedDialogClass = vclassReproduce(vdialogGetDefaultClass());
    title = vstrCloneScribed(vcharScribeLiteral("drawdemoHookedDialogClass"));
    vclassSetName(drawdemoHookedDialogClass, title);
    vstrDestroy(title);
    
    vclassSet(drawdemoHookedDialogClass, vwindowHANDLE_BUTTON_DOWN,
	      drawdemoHandleMouseDown);
    
    
    /*
     * Customize the dialog item class to draw item as we wish:
     */
    
    drawdemoFabricClass = vclassReproduce(vdialogGetDefaultItemClass());
    title = vstrCloneScribed(vcharScribeLiteral("drawdemoFabricClass"));
    vclassSetName(drawdemoFabricClass, title);
    vstrDestroy(title);
    
    vclassSet(drawdemoFabricClass, vdialogDRAW_ITEM, drawdemoDraw);
    vclassSet(drawdemoFabricClass, vdialogDRAW_ITEM_FOCUS, drawdemoDraw);
}


/**********
 * drawdemoSetNotifyStuff:
 *      Sets the button notification functions (could use commands instead)
 *
 **********/
void drawdemoSetNotifyStuff(void)
{
    vbuttonSetNotify(drawdemoStartButton, drawdemoNotifyStartButton);
    
    vbuttonSetNotify(drawdemoChangeFontButton, drawdemoNotifyChangeFontButton);
    
    vbuttonSetNotify(drawdemoCloseButton, drawdemoNotifyCloseButton);
}


/**********
 * drawdemoUnload:
 *      Frees up the items pointed to by the draw demo's global variables.
 *
 **********/
void drawdemoUnload(void)
{

    /*
     * don't do anything if the dialog point is already null
     */
    if (drawdemoDialog == NULL)
      return;
    
    /*
     * our drawing color
     */
    if (drawdemoColor != NULL) {
	vcolorRelease(drawdemoColor);
	drawdemoColor = NULL;
    }
    
    /*
     * the drawing state information
     */
    if (drawdemoGState != NULL)
      vdrawDestroyGState(drawdemoGState);
    
    /*
     * release the font chooser
     */
    if (drawdemoFontChooser != NULL)
      vfontchsrDestroy(drawdemoFontChooser);
    
    /*
     * the main dialog itself
     */
    vdialogDestroy(drawdemoDialog);
    drawdemoDialog = NULL;
    
    /*
     * and finally the two custom classes we created
     */
    vclassDestroy(drawdemoHookedDialogClass);
    
    vclassDestroy(drawdemoFabricClass);
    
}  /**  drawdemoUnload()  **/


/**********
 * drawdemoNotifyStartButton:
 *      The notification function for the start button
 *
 **********/
void drawdemoNotifyStartButton(vbutton *button, vevent *event)
{
    /*
     * flips the globals to start at the beginning of a draw cycle
     */
    
    drawdemoIsHalted = FALSE;
    drawdemoDoStartOver = TRUE;
    drawdemoDoStopAtNext = FALSE;

    /*
     * disable the start button
     */
    vdialogDisableItem(vbuttonGetItem(drawdemoStartButton));

    /*
     * give the dialog no focus
     */
    vdialogSetFocus(drawdemoDialog, NULL);

    /*
     * start the drawing up
     */
    drawdemoDraw(drawdemoFabric);
    
}  /**  drawdemoNotifyStartButton()  **/


/**********
 * drawdemoNotifyChangeFontButton:
 *      The notification function for the font button
 *
 **********/
void drawdemoNotifyChangeFontButton(vbutton *button, vevent *event)
{
    /*
     * make sure we have a font chooser already
     */
    
    if (drawdemoFontChooser == NULL) {
	drawdemoFontChooser = vfontchsrCreate();
	vfontchsrSetFont(drawdemoFontChooser, drawdemoFont);
	vfontchsrSetApply(drawdemoFontChooser, drawdemoApplyFont);
    }
    
    /*
     * bring up the font chooser
     */
    
    vdialogOpen(vfontchsrGetDialog(drawdemoFontChooser));
    
}  /**  drawdemoNotifyChangeFontButton()  **/


/**********
 * drawdemoApplyFont:
 *      The notification function for the Apply button in the font chooser
 *
 **********/
int drawdemoApplyFont(vfontchsr *fontChooser, vfont *font)
{
    /*
     * keep track of the font so we can use it to draw if needed
     */
    drawdemoFont = font;

    /*
     * flag to start the drawing over since we just changed the
     * drawing font
     */
    drawdemoDoStartOver = TRUE;

    return(TRUE);
}  /**  drawdemoApplyFont()  **/


/**********
 * drawdemoNotifyCloseButton:
 *      The notification function for the close button for the demo dialog
 *
 **********/
void drawdemoNotifyCloseButton(vbutton *button, vevent *event)
{

    /*
     * close the dialog
     */
    drawdemoClose();

    /*
     * tell the event loop to exit when done
     */
    veventStopProcessing();

}  /**  drawdemoNotifyCloseButton()  **/


/**********
 * drawdemoHandleMouseDown:
 *      The custom handler to call when a mouse down occures in
 *      the main window
 *
 **********/
int drawdemoHandleMouseDown(vdialog *dialog, vevent *event)
{

    /*
     * stop the drawing loop
     */
    drawdemoIsHalted = TRUE;

    /*
     * enable the start button
     */
    vdialogEnableItem(vbuttonGetItem(drawdemoStartButton));

    /*
     * send the message on to the default button down handler for the
     * dialog
     */
    return(vclassSend(vdialogGetDefaultClass(),
		      vwindowHANDLE_BUTTON_DOWN, (dialog, event)));
}  /**  drawdemoHandleMouseDown()  **/


/**********
 * drawdemoDraw:
 *      The drawing procedure for our custom dialog item class
 *
 **********/
void drawdemoDraw(vdialogItem *item)
{
    int                          i;
    vevent                      *event;
    vrect			 rect;

    /*
     * get our demo area's rect
     */
    rect = *vdialogGetItemRect(item);

    /*
     * put the border around the draw area
     */
    i = vdrawGetLineWidth();
    vdrawSetLineWidth(2);
    vdrawRectsHiliteFillInside
	(&rect, 1, NULL,
	 vdialogDetermineItemColor(item, vdrawCOLOR_SHADOW_BOTTOM),
	 vdialogDetermineItemColor(item, vdrawCOLOR_SHADOW_TOP));
    vdrawSetLineWidth(i);
    
    /*
     * nothing needs to be done if we stopped the drawing
     * or the dialog is not open
     */
    if (drawdemoIsHalted || !(vdialogIsOpen(drawdemoDialog)))
      return;

    /*
     * when we finish a cycle through the loop, and the once check box
     * was set, flag out of the draw loop and enable the start button.
     */
    if (drawdemoDoStartOver && drawdemoDoStopAtNext) {
	drawdemoIsHalted = TRUE;
	
	vdialogEnableItem(vbuttonGetItem(drawdemoStartButton));
	
	return;
    }

    /*
     * save the current state since we play with stuff...
     */
    vdrawGSave();

    /*
     * The drawdemoGState is set up in the drawdemoDrawSetup routine
     * and then it is saved.  This way the setup doesn't have to be
     * done each time, the saved one is restored on each pass through
     * here.
     */
     
    /*
     * are we starting from the beginning?
     */
    if (drawdemoDoStartOver) {
	/*
	 * destroy the old drawing state we had
	 */
	if (drawdemoGState != NULL)
	  vdrawDestroyGState(drawdemoGState);

	/*
	 * collect the drawing info from the dialog items
	 */
	drawdemoDrawSetup();

	if (drawdemoIsDedicated)
	  drawdemoGState = NULL;
	else
	  drawdemoGState = vdrawCreateGState();
    } else {
	/*
	 * drawing was already going...
	 */
	if (drawdemoGState != NULL)
	  vdrawSetGState(drawdemoGState);
    }
    
    /*
     * fast draw or timer draw?
     */
    if (drawdemoIsDedicated) {
	/*
	 * draw all of the objects left to go
	 */
	for (i = 0; i < drawdemoObjectCount; i++)
	  drawdemoDrawOne();
	  
	drawdemoDoStartOver = TRUE;

    } else {

	/*
	 * draw one item
	 */
	drawdemoDrawOne();
	  
	drawdemoObjectCount--;
	
	/*
	 * reach the end of the set yet?
	 */
	if (drawdemoObjectCount <= 0)
	  drawdemoDoStartOver = TRUE;
	else
	  drawdemoDoStartOver = FALSE;
    }

    /*
     * post an application even into the future to handle the next drawing
     * operation.  The handler for the event is set directly to our custom
     * handler.  We then also set the priority of the event as low as possible
     * so that any other events will get done first
     */
    event = veventCreateApplication();
    veventSetTarget(event, drawdemoHandleCustomEvent);
    veventSetPriority(event, veventPRIORITY_MIN);
    veventPost(event);

    /*
     * now we reset the drawing environment to the stored one to get rid
     * of all of our changes
     */
    vdrawGRestore();
    
}  /**  drawdemoDraw()  **/


/**********
 * drawdemoHandleCustomEvent:
 *      The handler for our custom events that trigger drawing
 *
 **********/
int drawdemoHandleCustomEvent(vevent *event)
{
    vbool                               isDedicated;
    
    /*
     * collect the fastest check box value
     */
    isDedicated = (vcontrolGetValue(drawdemoDedicatedCheckBox) != 0);

    /*
     * set our globals to match the setting
     */
    if (isDedicated != drawdemoIsDedicated) {
	drawdemoDoStartOver = TRUE;
	drawdemoIsDedicated = isDedicated;
    }

    /*
     * do a draw on the demo area
     */
    drawdemoDraw(drawdemoFabric);

    /*
     * we handled this event, so we return that fact
     */
    return(TRUE);

}  /**  drawdemoHandleCustomEvent()  **/


/**********
 * drawdemoDrawSetup:
 *      Collects the settings from the dialog items
 *
 **********/
void drawdemoDrawSetup(void)
{
    vrect                       rect;
    vrect                       inset;
    double                      rotateAngle;
    double                      scaleX, scaleY;
    double                      flatness;
    double                      miterLimit;
    double                      lineWidth;
    int                         lineCap, lineJoin;
    
    /*
     * if the dialog isn't open yet, then skip it for now
     */
    if (!vdialogIsOpen(drawdemoDialog))
      return;

    /*
     * Since the drawing is timer driven, it is possible that
     * the current device wasn't the demo window,  so we set it
     */
    vwindowDrawDevice(vdialogGetWindow(drawdemoDialog));

    /*
     * get our demo area's rect
     */
    rect = *vdialogGetItemRect(drawdemoFabric);

    /*
     * put the border around the draw area
     */
    vdrawTranslate(rect.x, rect.y);
    vdrawSetLineWidth(2);
    rect.x = 0;
    rect.y = 0;
    vdrawRectsHiliteFillInside
      (&rect, 1,
       vdialogDetermineItemBackground(drawdemoFabric),
       vdialogDetermineItemColor(drawdemoFabric, vdrawCOLOR_SHADOW_BOTTOM),
       vdialogDetermineItemColor(drawdemoFabric, vdrawCOLOR_SHADOW_TOP));

    /*
     * set to clip to the area inside the draw area's border
     */
    vrectInset(&rect, 2, 2, &inset);
    vdrawRectsClip(&inset, 1);

    /*
     * set the color to the right one for the dialog item
     */
    vdrawSetColor(vdialogDetermineItemForeground(drawdemoFabric));

    /*
     * Collect the setting from the object type and file type option menus
     */
    drawdemoObjectType =
      drawdemoObjectTypeValues[vcontrolGetValue(drawdemoObjectTypePopup)];
    drawdemoFillType =
      drawdemoFillTypeValues[vcontrolGetValue(drawdemoFillTypePopup)];

    /*
     * See if the monochrome check box was turned on
     */
    drawdemoIsMonochrome = (vcontrolGetValue(drawdemoMonochromeCheckBox) != 0);

    /*
     * Set the font we are to use
     */
    if (drawdemoFont != NULL)
      vdrawSetFont(drawdemoFont);

    /*
     * collect the rotation angle, and set it
     */
    rotateAngle = vtextitemGetTextAsFloat(drawdemoRotateAngleText);
    if (rotateAngle != 0.0)
      vdrawFRotate(rotateAngle);

    /*
     * collect the scaling factors to use and set them
     */
    scaleX = vtextitemGetTextAsFloat(drawdemoScaleXText);
    scaleY = vtextitemGetTextAsFloat(drawdemoScaleYText);
    if (scaleX != 1.0 || scaleY != 1.0)
      vdrawFScale(scaleX, scaleY);

    /*
     * read in the flatness (for curves) and set it
     */
    flatness = vtextitemGetTextAsFloat(drawdemoFlatnessText);
    if (flatness != 0.0)
      vdrawSetFlat(flatness);

    /*
     * See if we are doing color X-or and set so
     */
    if (vcontrolGetValue(drawdemoExclusiveOrCheckBox) != 0)
      vdrawSetFunction(vdrawFUNC_XOR);

    /*
     * read the line cap type, and set it accordingly
     */
    lineCap = drawdemoLineCapValues[vcontrolGetValue(drawdemoLineCapPopup)];
    vdrawSetLineCap(lineCap);

    /*
     * read in the line joint type, and set it accordingly
     */
    lineJoin = drawdemoLineJoinValues[vcontrolGetValue(drawdemoLineJoinPopup)];
    vdrawSetLineJoin(lineJoin);

    /*
     * read in the line width setting, and set it
     */
    lineWidth = vtextitemGetTextAsFloat(drawdemoLineWidthText);
    if (lineWidth >= 0.0)
      vdrawSetLineWidth(lineWidth);

    /*
     * Are we doing dashed lines?
     */
    drawdemoDoDashed = (vcontrolGetValue(drawdemoDashedCheckBox) != 0);

    /*
     * What is the mitering limit set too
     */
    miterLimit = vtextitemGetTextAsFloat(drawdemoMiterLimitText);
    if (miterLimit >= 1.0)
      vdrawSetMiterLimit(miterLimit);

    /*
     * How many object are we going to draw?
     */
    drawdemoObjectCount = vtextitemGetTextAsInt(drawdemoObjectCountText);

    /*
     * And lastly, are we going to do the drawing just once or more times?
     */
    drawdemoDoStopAtNext = (vcontrolGetValue(drawdemoOneAtTimeCheckBox) != 0);

    /*
     * Are we going to go back to the event loop between drawing each 
     * individual object, or just at the end of each cycle ?
     */
    drawdemoIsDedicated = (vcontrolGetValue(drawdemoDedicatedCheckBox) != 0);

}  /**  drawdemoDrawSetup()  **/


/**********
 * drawdemoDrawOne:
 *      This draws one object into the draw area
 *
 **********/
void drawdemoDrawOne(void)
{
    int                          i;
    int                          width, height;
    unsigned int                 randomNumber;
    int                          segments;
    int                          dashes;
    float                        dashLengths[4];
    int                          x1, y1, x2, y2, x3, y3, x4, y4;
    int                          w1, h1;
    int                          radius;
    int                          angle1, angle2;
    int                          phraseIndex;
    vstr                        *phrase;
    int                          gap;
    vcolor                      *oldColor;

    /*
     * no work to do if the window isn't open
     */
    if (!vdialogIsOpen(drawdemoDialog))
      return;

    /*
     * collect the size of our drawing area
     */
    width = vdialogGetItemW(drawdemoFabric) - 2;
    height = vdialogGetItemH(drawdemoFabric) - 2;

    if (!drawdemoIsMonochrome) {
	/*
	 * the monochrome check box wasn't on, so pick a random color
	 */
	vcolorInitSpec(&spec);
	vcolorSetSpecRGB(&spec,
			 rand()<<8 % vcolorCOMPONENT_MAX,
			 rand()<<8 % vcolorCOMPONENT_MAX,
			 rand()<<8 % vcolorCOMPONENT_MAX);

	/*
	 * because the color is in use by the gState, we can't
	 * destroy it until after the new one is installed
	 */
	oldColor = drawdemoColor;
	drawdemoColor = vcolorInternSpec(&spec);
	vdrawSetColor(drawdemoColor);
	vcolorDestroySpec(&spec);
	vcolorRelease(oldColor);
    }

    /*
     * are we doing dashed lines? (and not text or images)
     */
    if (drawdemoDoDashed &&
	drawdemoObjectType != drawdemoDRAW_TEXT &&
	drawdemoObjectType != drawdemoDRAW_IMAGES) {

	/*
	 * make a random dash pattern
	 */

	dashes = 0;
	randomNumber = rand();
        /* ensure eight random and distinct values between 1 - 8 */
	randomNumber = ((randomNumber / 333) & 0x7) + 1;
	for (i = 0; i < 4; i++) {
	    dashLengths[dashes] = (float)(randomNumber);
	    dashes++;
	    randomNumber = (((randomNumber % 5)+1) * (i+1) );
	}

	/*
	 * set our dash pattern
	 */
	vdrawFSetDash(dashes, dashLengths, randomNumber);
    }

    /*
     * The drawing routines are done by making a path out of the current
     * object, and then the path is worked on acording to the fill type
     */
    switch(drawdemoObjectType) {
      case drawdemoDRAW_LINES:
      case drawdemoDRAW_CURVES:
      case drawdemoDRAW_ARCS:
	segments = 3;
	randomNumber = rand();
	for (i = 0; i < 32; i++) {
	    if ((randomNumber & 1) != 0)
	      break;
	    
	    segments++;
	    randomNumber >>= 1;
	}

	vdrawNewPath();
      
	x1 = rand() % width;
	y1 = rand() % height;
	vdrawMoveTo(x1, y1);

	for (i = 0; i < segments; i++) {
	    x2 = rand() % width;
	    y2 = rand() % height;
	    
	    switch(drawdemoObjectType) {
	      case drawdemoDRAW_LINES:
		vdrawLineTo(x2, y2);
		break;
		
	      case drawdemoDRAW_CURVES:
		x3 = rand() % width;
		y3 = rand() % height;
		x4 = rand() % width;
		y4 = rand() % height;
		vdrawCurveTo(x3, y3, x4, y4, x2, y2);
		break;
		
	      case drawdemoDRAW_ARCS:
		x3 = rand() % width;
		y3 = rand() % height;
		radius = (rand() % width + height) + 1;
		
		vdrawArcT(x3, y3, x2, y2, radius);
		break;
		
	      default:
		break;
	    }
	}

	if (drawdemoObjectType == drawdemoDRAW_CURVES) {
	    x3 = rand() % width;
	    y3 = rand() % height;
	    x4 = rand() % width;
	    y4 = rand() % height;
	    vdrawCurveTo(x3, y3, x4, y4, x1, y1);
	}

	vdrawClosePath();

	switch(drawdemoFillType) {
	  case drawdemoSTROKE:
	    vdrawStroke();
	    break;
	    
	  case drawdemoFILL:
	    vdrawFill();
	    break;
	    
	  case drawdemoEO_FILL:
	    vdrawEOFill();
	    break;
	    
	  case drawdemoCLIP:
	    vdrawClip();
	    break;
	    
	  case drawdemoEO_CLIP:
	    vdrawEOClip();
	    break;
	    
	  case drawdemoBORDERED:
	    vdrawGSave();
	    vdrawFill();
	    vdrawGRestore();
	    vdrawSetColor(vcolorGetBlack());
	    vdrawStroke();
	    break;
	    
	  default:
	    break;
	}

	break;
	
      case drawdemoDRAW_CW_ARCS:
	vdrawNewPath();
	
	x1 = rand() % width;
	y1 = rand() % height;
	vdrawMoveTo(x1, y1);
	
	x2 = x1 + (rand() % 100) - 50;
	y2 = y1 + (rand() % 100) - 50;
	angle1 = rand() % 360;
	angle2 = rand() % 360;
	radius = (rand() % 50) + 1;
	
	vdrawArcN(x1, y1, radius, angle1, angle2);

	vdrawClosePath();
	
	switch(drawdemoFillType) {
	  case drawdemoSTROKE:
	    vdrawStroke();
	    break;

	  case drawdemoFILL:
	    vdrawFill();
	    break;
	    
	  case drawdemoEO_FILL:
	    vdrawEOFill();
	    break;
	    
	  case drawdemoCLIP:
	    vdrawClip();
	    break;
	    
	  case drawdemoEO_CLIP:
	    vdrawEOClip();
	    break;

	  case drawdemoBORDERED:
	    vdrawGSave();
	    vdrawFill();
	    vdrawGRestore();
	    vdrawSetColor(vcolorGetBlack());
	    vdrawStroke();
	    break;

	  default:
	    break;
	}

	break;

      case drawdemoDRAW_RECTS:
	x1 = rand() % width;
	y1 = rand() % height;
	x2 = rand() % width;
	y2 = rand() % height;
	
	if (x1 < x2)
	  w1 = x2 - x1;
	else if (x2 < x1) {
	    w1 = x1 - x2;
	    x1 = x2;
	} else
	  w1 = 1;

	if (y1 < y2)
	  h1 = y2 - y1;
	else if (y2 < y1) {
	    h1 = y1 - y2;
	    y1 = y2;
	} else
	  h1 = 1;

	switch(drawdemoFillType) {
	  case drawdemoSTROKE:
	    vdrawRectStroke(x1, y1, w1, h1);
	    break;
	    
	  case drawdemoFILL:
	  case drawdemoEO_FILL:
	    vdrawRectFill(x1, y1, w1, h1);
	    break;
	    
	  case drawdemoCLIP:
	  case drawdemoEO_CLIP:
	    vdrawRectClip(x1, y1, w1, h1);
	    break;
	    
	  case drawdemoBORDERED:
	    vdrawRectFill(x1, y1, w1, h1);
	    vdrawSetColor(vcolorGetBlack());
	    vdrawRectStroke(x1, y1, w1, h1);
	    break;
	    
	  default:
	    break;
	}

	break;

      case drawdemoDRAW_TEXT:
	x1 = rand() % width;
	y1 = rand() % height;
	vdrawMoveTo(x1, y1);

	phraseIndex = rand() % drawdemoPHRASES;

	phrase = vstrCloneScribed(vcharScribeLiteral
				  (drawdemoPhrases[phraseIndex]));
	vdrawShow(phrase);
	vstrDestroy(phrase);
	
	break;
	
      case drawdemoDRAW_IMAGES:
	break;
    }

    /*
     * If this was either of the clipping fills and not
     * text or images, then the area is filled with lines
     * that are trimmed by the path as a clipping region.
     */
    if ((drawdemoFillType == drawdemoCLIP ||
	 drawdemoFillType == drawdemoEO_CLIP) &&
	drawdemoObjectType != drawdemoDRAW_TEXT &&
	drawdemoObjectType != drawdemoDRAW_IMAGES) {

	vdrawNewPath();

	y1 = (rand() % 100);
	y2 = (rand() % 100);

	gap = 2 * vdrawGetLineWidth();
	
	if (y1 < y2) {
	    i = y1 - y2;
	    y1 = i;
	    y2 = 0;
	} else {
	    i = y2 - y1;
	    y1 = 0;
	    y2 = i;
	}

	while (i < height) {
	    vdrawMoveTo(0, y1);
	    vdrawLineTo(width, y2);
	    vdrawStroke();
	    
	    y1 += gap;
	    y2 += gap;
	    i += gap;
	}
    }

}  /**  drawdemoDrawOne()  **/


/**********
 * drawdemoOpen:
 *      Open the dialog up, and post our drawing event to start things up
 *
 **********/
void drawdemoOpen(void)
{
    vevent                      *event;

    if (drawdemoDialog == NULL)
      drawdemoLoad();

    vdialogOpen(drawdemoDialog);

    drawdemoDoStartOver = TRUE;

    /*
     * get that event going
     */
    event = veventCreateApplication();
    veventSetTarget(event, drawdemoHandleCustomEvent);
    veventSetPriority(event, veventPRIORITY_MIN);
    veventPost(event);

}  /**  drawdemoOpen()  **/


/**********
 * drawdemoClose:
 *      Close our dialog down
 *
 **********/
void drawdemoClose(void)
{

  if (drawdemoDialog == NULL)
    return;

  vdialogClose(drawdemoDialog);

}  /**  drawdemoClose()  **/



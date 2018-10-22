/* $Id: vdraw.c,v 1.2 1995/03/28 23:27:18 andrew Exp $
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

/* Private headers */
#include "drawdemo.h"

/**********
 * User interface variables:
 **********/

vdialogItem			*drawdemoObjectCountLabel = NULL;
vdialogItem			*drawdemoRotateAngleLabel = NULL;
vdialogItem			*drawdemoScaleXLabel = NULL;
vdialogItem			*drawdemoScaleYLabel = NULL;
vdialogItem			*drawdemoLineWidthLabel = NULL;
vdialogItem			*drawdemoFlatnessLabel = NULL;
vdialogItem			*drawdemoMiterLimitLabel = NULL;
vdialogItem			*drawdemoCopyrightLabel = NULL;
vdialogItem			*drawdemoReservedLabel = NULL;

/**********
 * Labels used to build option menus (should be in resource file):
 **********/

const char			*drawdemoObjectTypeLabels[drawdemoOBJECT_TYPES]
  = { "Lines", "Rectangles", "Curves", "Arcs", "Text" };

const char			*drawdemoFillTypeLabels[drawdemoFILL_TYPES]
  = { "Outlined", "Filled", "Even-odd", "Clip", "E-o Clip", "Bordered" };

const char			*drawdemoLineCapLabels[drawdemoLINE_CAPS]
  = { "Non-projecting Line Caps", "Projecting Line Caps",
      "Rounded Line Caps" };

const char			*drawdemoLineJoinLabels[drawdemoLINE_JOINS]
  = { "Beveled Line Joints", "Mitered Line Joints", "Rounded Line Joints" };


/**********
 * One private function here
 **********/

void _drawdemoResizeDialog(
  vdialog			*dialog
);


/**********
 * drawdemoLoad:
 *	Sets up the draw demo's global variables.
 *
 **********/
void drawdemoLoad(void)
{
    int				 i;
    vstr			*title;
    vmenuItem			*menuItem;

    /*
     * Make the draw demo's main dialog from customized class:
     */
    
    drawdemoDialog = vdialogCreateOfClass(drawdemoHookedDialogClass);
    title = vstrCloneScribed(vcharScribeLiteral("Visix's Galaxy Draw Demo"));
    vdialogSetTitle(drawdemoDialog, title);
    vstrDestroy(title);
    vdialogSetNotify(drawdemoDialog, drawdemoDialogNotify);

    /*
     * Text objects will initially be drawn in the application default font:
     */

    drawdemoFont = vapplicationGetFont(vapplicationGetCurrent());
    
    /*
     * Make the draw demo's drawing fabric from customized class:
     */

    drawdemoFabric = vdialogCreateItemOfClass(drawdemoFabricClass);
    vdialogAppendItem(drawdemoDialog, drawdemoFabric);

    /*
     * Make and initialize all of the standard dialog items
     * (should be in resource file):
     */
    
    drawdemoDedicatedCheckBox = vcontrolCreateToggle();
    vcontrolSetExclusive(drawdemoDedicatedCheckBox, FALSE);
    title = vstrCloneScribed(vcharScribeLiteral("Fastest"));
    vcontrolSetTitle(drawdemoDedicatedCheckBox, title);
    vstrDestroy(title);
    vdialogAppendItem(drawdemoDialog,
		      vcontrolGetItem(drawdemoDedicatedCheckBox));
    
    drawdemoOneAtTimeCheckBox = vcontrolCreateToggle();
    vcontrolSetExclusive(drawdemoOneAtTimeCheckBox, FALSE);
    title = vstrCloneScribed(vcharScribeLiteral("Once"));
    vcontrolSetTitle(drawdemoOneAtTimeCheckBox, title);
    vstrDestroy(title);
    vdialogAppendItem(drawdemoDialog,
		      vcontrolGetItem(drawdemoOneAtTimeCheckBox));
    
    drawdemoObjectCountLabel = vdialogCreateLabelItem();
    vdialogSetItemTitleScribed(drawdemoObjectCountLabel,
			       vcharScribeLiteral("# Objects:"));
    vdialogAppendItem(drawdemoDialog, drawdemoObjectCountLabel);
    
    drawdemoObjectCountText = vtextitemCreate();
    vtextitemSetOneLine(drawdemoObjectCountText, TRUE);
    vtextitemSetEditable(drawdemoObjectCountText);
    vtextitemSetTextScribed(drawdemoObjectCountText, vnumScribeInt(100));
    vdialogAppendItem(drawdemoDialog,
		      vtextitemGetItem(drawdemoObjectCountText));
    
    drawdemoObjectTypePopup = vcontrolCreateOptionMenu();
    drawdemoObjectTypePopupMenu = vmenuCreate();
    for (i = 0; i < drawdemoOBJECT_TYPES; i++) {
	/* Build up option menu */
	menuItem = vmenuCreateItem();
	title =
	  vstrCloneScribed(vcharScribeLiteral(drawdemoObjectTypeLabels[i]));
	vmenuSetItemTitle(menuItem, title);
	vstrDestroy(title);
	vmenuAppendItem(drawdemoObjectTypePopupMenu, menuItem);
    }
    vcontrolSetMenu(drawdemoObjectTypePopup, drawdemoObjectTypePopupMenu);
    vdialogAppendItem(drawdemoDialog, 
		      vcontrolGetItem(drawdemoObjectTypePopup));
    
    drawdemoMonochromeCheckBox = vcontrolCreateToggle();
    vcontrolSetExclusive(drawdemoMonochromeCheckBox, FALSE);
    title = vstrCloneScribed(vcharScribeLiteral("Monochrome"));
    vcontrolSetTitle(drawdemoMonochromeCheckBox, title);
    vstrDestroy(title);
    vdialogAppendItem(drawdemoDialog,
		      vcontrolGetItem(drawdemoMonochromeCheckBox));
    
    drawdemoExclusiveOrCheckBox = vcontrolCreateToggle();
    vcontrolSetExclusive(drawdemoExclusiveOrCheckBox, FALSE);
    title = vstrCloneScribed(vcharScribeLiteral("X-or Colors"));
    vcontrolSetTitle(drawdemoExclusiveOrCheckBox, title);
    vstrDestroy(title);
    vdialogAppendItem(drawdemoDialog,
		      vcontrolGetItem(drawdemoExclusiveOrCheckBox));
    
    drawdemoFillTypePopup = vcontrolCreateOptionMenu();
    drawdemoFillTypePopupMenu = vmenuCreate();
    for (i = 0; i < drawdemoFILL_TYPES; i++) {
	/* Build up option menu */
	menuItem = vmenuCreateItem();
	title =
	  vstrCloneScribed(vcharScribeLiteral(drawdemoFillTypeLabels[i]));
	vmenuSetItemTitle(menuItem, title);
	vstrDestroy(title);
	vmenuAppendItem(drawdemoFillTypePopupMenu, menuItem);
    }
    vcontrolSetMenu(drawdemoFillTypePopup, drawdemoFillTypePopupMenu);
    vdialogAppendItem(drawdemoDialog, 
		      vcontrolGetItem(drawdemoFillTypePopup));
    
    drawdemoRotateAngleLabel = vdialogCreateLabelItem();
    vdialogSetItemTitleScribed(drawdemoRotateAngleLabel,
			       vcharScribeLiteral("Rotate Angle:"));
    vdialogAppendItem(drawdemoDialog, drawdemoRotateAngleLabel);
    
    drawdemoRotateAngleText = vtextitemCreate();
    vtextitemSetOneLine(drawdemoRotateAngleText, TRUE);
    vtextitemSetEditable(drawdemoRotateAngleText);
    vtextitemSetTextScribed(drawdemoRotateAngleText, vnumScribeFloat(0.0));
    vdialogAppendItem(drawdemoDialog,
		      vtextitemGetItem(drawdemoRotateAngleText));
    
    drawdemoScaleXLabel = vdialogCreateLabelItem();
    vdialogSetItemTitleScribed(drawdemoScaleXLabel,
			       vcharScribeLiteral("Scale X:"));
    vdialogAppendItem(drawdemoDialog, drawdemoScaleXLabel);
    
    drawdemoScaleXText = vtextitemCreate();
    vtextitemSetOneLine(drawdemoScaleXText, TRUE);
    vtextitemSetEditable(drawdemoScaleXText);
    vtextitemSetTextScribed(drawdemoScaleXText, vnumScribeFloat(1.0));
    vdialogAppendItem(drawdemoDialog,
		      vtextitemGetItem(drawdemoScaleXText));
    
    drawdemoScaleYLabel = vdialogCreateLabelItem();
    vdialogSetItemTitleScribed(drawdemoScaleYLabel,
			       vcharScribeLiteral("Y:"));
    vdialogAppendItem(drawdemoDialog, drawdemoScaleYLabel);

    drawdemoScaleYText = vtextitemCreate();
    vtextitemSetOneLine(drawdemoScaleYText, TRUE);
    vtextitemSetEditable(drawdemoScaleYText);
    vtextitemSetTextScribed(drawdemoScaleYText, vnumScribeFloat(1.0));
    vdialogAppendItem(drawdemoDialog,
		      vtextitemGetItem(drawdemoScaleYText));
    
    drawdemoLineWidthLabel = vdialogCreateLabelItem();
    vdialogSetItemTitleScribed(drawdemoLineWidthLabel,
			       vcharScribeLiteral("Line Width:"));
    vdialogAppendItem(drawdemoDialog, drawdemoLineWidthLabel);

    drawdemoLineWidthText = vtextitemCreate();
    vtextitemSetOneLine(drawdemoLineWidthText, TRUE);
    vtextitemSetEditable(drawdemoLineWidthText);
    vtextitemSetTextScribed(drawdemoLineWidthText, vnumScribeFloat(1.0));
    vdialogAppendItem(drawdemoDialog,
		      vtextitemGetItem(drawdemoLineWidthText));
    
    drawdemoFlatnessLabel = vdialogCreateLabelItem();
    vdialogSetItemTitleScribed(drawdemoFlatnessLabel,
			       vcharScribeLiteral("Flatness:"));
    vdialogAppendItem(drawdemoDialog, drawdemoFlatnessLabel);

    
    drawdemoFlatnessText = vtextitemCreate();
    vtextitemSetOneLine(drawdemoFlatnessText, TRUE);
    vtextitemSetEditable(drawdemoFlatnessText);
    vtextitemSetTextScribed(drawdemoFlatnessText, vnumScribeFloat(0.0));
    vdialogAppendItem(drawdemoDialog,
		      vtextitemGetItem(drawdemoFlatnessText));
    
    drawdemoDashedCheckBox = vcontrolCreateToggle();
    vcontrolSetExclusive(drawdemoDashedCheckBox, FALSE);
    title = vstrCloneScribed(vcharScribeLiteral("Dashed Lines: "));
    vcontrolSetTitle(drawdemoDashedCheckBox, title);
    vstrDestroy(title);
    vdialogAppendItem(drawdemoDialog,
		      vcontrolGetItem(drawdemoDashedCheckBox));
    
    drawdemoLineCapPopup = vcontrolCreateOptionMenu();
    drawdemoLineCapPopupMenu = vmenuCreate();
    for (i = 0; i < drawdemoLINE_CAPS; i++) {
	/* Build up option menu */
	menuItem = vmenuCreateItem();
	title =
	  vstrCloneScribed(vcharScribeLiteral(drawdemoLineCapLabels[i]));
	vmenuSetItemTitle(menuItem, title);
	vstrDestroy(title);
	vmenuAppendItem(drawdemoLineCapPopupMenu, menuItem);
    }
    vcontrolSetMenu(drawdemoLineCapPopup, drawdemoLineCapPopupMenu);
    vdialogAppendItem(drawdemoDialog, 
		      vcontrolGetItem(drawdemoLineCapPopup));
    
    drawdemoLineJoinPopup = vcontrolCreateOptionMenu();
    drawdemoLineJoinPopupMenu = vmenuCreate();
    for (i = 0; i < drawdemoLINE_JOINS; i++) {
	/* Build up option menu */
	menuItem = vmenuCreateItem();
	title =
	  vstrCloneScribed(vcharScribeLiteral(drawdemoLineJoinLabels[i]));
	vmenuSetItemTitle(menuItem, title);
	vstrDestroy(title);
	vmenuAppendItem(drawdemoLineJoinPopupMenu, menuItem);
    }
    vcontrolSetMenu(drawdemoLineJoinPopup, drawdemoLineJoinPopupMenu);
    vdialogAppendItem(drawdemoDialog, 
		      vcontrolGetItem(drawdemoLineJoinPopup));
    
    drawdemoMiterLimitLabel = vdialogCreateLabelItem();
    vdialogSetItemTitleScribed(drawdemoMiterLimitLabel,
			       vcharScribeLiteral("Miter Limit:"));
    vdialogAppendItem(drawdemoDialog, drawdemoMiterLimitLabel);

    drawdemoMiterLimitText = vtextitemCreate();
    vtextitemSetOneLine(drawdemoMiterLimitText, TRUE);
    vtextitemSetEditable(drawdemoMiterLimitText);
    vtextitemSetTextScribed(drawdemoMiterLimitText, vnumScribeFloat(10.0));
    vdialogAppendItem(drawdemoDialog,
		      vtextitemGetItem(drawdemoMiterLimitText));
    
    drawdemoStartButton = vbuttonCreate();
    title = vstrCloneScribed(vcharScribeLiteral("Start"));
    vbuttonSetTitle(drawdemoStartButton, title);
    vstrDestroy(title);
    vdialogDisableItem(vbuttonGetItem(drawdemoStartButton));
    vdialogAppendItem(drawdemoDialog, vbuttonGetItem(drawdemoStartButton));
    vdialogSetConfirm(drawdemoDialog, vbuttonGetItem(drawdemoStartButton));
    
    drawdemoChangeFontButton = vbuttonCreate();
    title = vstrCloneScribed(vcharScribeLiteral("Change Font"));
    vbuttonSetTitle(drawdemoChangeFontButton, title);
    vstrDestroy(title);
    vdialogEnableItem(vbuttonGetItem(drawdemoChangeFontButton));
    vdialogAppendItem(drawdemoDialog,
		      vbuttonGetItem(drawdemoChangeFontButton));
    
    drawdemoCopyrightLabel = vdialogCreateLabelItem();
    vdialogSetItemTitleScribed(drawdemoCopyrightLabel,
	vcharScribeLiteral("Copyright (C) 1986-1992, Visix Software Inc."));
    vdialogAppendItem(drawdemoDialog, drawdemoCopyrightLabel);

    drawdemoReservedLabel = vdialogCreateLabelItem();
    vdialogSetItemTitleScribed(drawdemoReservedLabel,
			       vcharScribeLiteral("All Rights Reserved"));
    vdialogAppendItem(drawdemoDialog, drawdemoReservedLabel);

    drawdemoCloseButton = vbuttonCreate();
    title = vstrCloneScribed(vcharScribeLiteral("Close"));
    vbuttonSetTitle(drawdemoCloseButton, title);
    vstrDestroy(title);
    vdialogEnableItem(vbuttonGetItem(drawdemoCloseButton));
    vdialogAppendItem(drawdemoDialog, vbuttonGetItem(drawdemoCloseButton));
    vdialogSetAbandon(drawdemoDialog, vbuttonGetItem(drawdemoCloseButton));
    
    /*
     * Allocate a color slot:
     */
    
    drawdemoColor = vcolorGetBlack();
    
    /*
     * Size the dialog to a comfortable initial size:
     */
    
    vdialogResize(drawdemoDialog, 600, 520);
    
    /*
     * Place all of the dialog items according to the initial size:
     */
    
    _drawdemoResizeDialog(drawdemoDialog);
    
    /*
     * Move the dialog to an arbitrary place:
     */
    
    vdialogMove(drawdemoDialog, 20, 20);
    
}  /**  drawdemoLoad()  **/


/**********
 * drawdemoDialogNotify:
 *	Receives all of the dialog (window) events

 **********/
void drawdemoDialogNotify(vdialog *dialog, vevent *event)
{

    /*
     * Look for a close event:
     */

    if (veventGetType(event) == veventWINDOW_STATE && veventIsClose(event)) {
	/*
	 * If the main draw demo dialog is closed by the user, there is
	 * nothing further to do:
	 */

	veventStopProcessing();
    }

    /*
     * Look for a configure event:
     */

    if (veventGetType(event) == veventWINDOW_CONFIGURE) {
	/*
	 * Place all of the dialog items according to the new size:
	 */

	_drawdemoResizeDialog(dialog);
    }

}  /**  drawdemoDialogNotify()  **/


/**********
 * _drawdemoResizeDialog:
 *	Places of the dialog items according to the current dialog dimensions.
 *
 **********/
void _drawdemoResizeDialog(vdialog *dialog)
{
    vrect			bounds;
    int				dialogWidth, dialogHeight;

    if (drawdemoDialog != dialog)
      drawdemoDialog = dialog;

    dialogWidth = vwindowGetW(vdialogGetWindow(drawdemoDialog));
    dialogHeight = vwindowGetH(vdialogGetWindow(drawdemoDialog));

    /*
     * Place the dialog items by hand (should be done with springs in
     * resource file):
     */

    vrectSet(10, dialogHeight - 25, 100, 20, &bounds);
    vdialogSetItemRect(vcontrolGetItem(drawdemoDedicatedCheckBox), &bounds);
    vrectSet(110, dialogHeight - 25, 100, 20, &bounds);
    vdialogSetItemRect(vcontrolGetItem(drawdemoOneAtTimeCheckBox), &bounds);
    vrectSet(10, dialogHeight - 55, 100, 20, &bounds);
    vdialogSetItemRect(drawdemoObjectCountLabel, &bounds);
    vrectSet(110, dialogHeight - 55, 100, 20, &bounds);
    vdialogSetItemRect(vtextitemGetItem(drawdemoObjectCountText), &bounds);
    vrectSet(10, dialogHeight - 93, 100, 30, &bounds);
    vdialogSetItemRect(vcontrolGetItem(drawdemoObjectTypePopup), &bounds);
    vrectSet(110, dialogHeight - 93, 100, 30, &bounds);
    vdialogSetItemRect(vcontrolGetItem(drawdemoFillTypePopup), &bounds);
    vrectSet(10, dialogHeight - 116, 100, 20, &bounds);
    vdialogSetItemRect(vcontrolGetItem(drawdemoMonochromeCheckBox), &bounds);
    vrectSet(110, dialogHeight - 116, 100, 20, &bounds);
    vdialogSetItemRect(vcontrolGetItem(drawdemoExclusiveOrCheckBox), &bounds);
    vrectSet(10, dialogHeight - 145, 100, 20, &bounds);
    vdialogSetItemRect(drawdemoRotateAngleLabel, &bounds);
    vrectSet(110, dialogHeight - 145, 100, 20, &bounds);
    vdialogSetItemRect(vtextitemGetItem(drawdemoRotateAngleText), &bounds);
    vrectSet(10, dialogHeight - 170, 60, 20, &bounds);
    vdialogSetItemRect(drawdemoScaleXLabel, &bounds);
    vrectSet(70, dialogHeight - 170, 55, 20, &bounds);
    vdialogSetItemRect(vtextitemGetItem(drawdemoScaleXText), &bounds);
    vrectSet(135, dialogHeight - 170, 20, 20, &bounds);
    vdialogSetItemRect(drawdemoScaleYLabel, &bounds);
    vrectSet(155, dialogHeight - 170, 55, 20, &bounds);
    vdialogSetItemRect(vtextitemGetItem(drawdemoScaleYText), &bounds);
    vrectSet(10, dialogHeight - 195, 100, 20, &bounds);
    vdialogSetItemRect(drawdemoFlatnessLabel, &bounds);
    vrectSet(110, dialogHeight - 195, 100, 20, &bounds);
    vdialogSetItemRect(vtextitemGetItem(drawdemoFlatnessText), &bounds);
    vrectSet(10, dialogHeight - 218, 200, 20, &bounds);
    vdialogSetItemRect(vcontrolGetItem(drawdemoDashedCheckBox), &bounds);
    vrectSet(10, dialogHeight - 247, 100, 20, &bounds);
    vdialogSetItemRect(drawdemoLineWidthLabel, &bounds);
    vrectSet(110, dialogHeight - 247, 100, 20, &bounds);
    vdialogSetItemRect(vtextitemGetItem(drawdemoLineWidthText), &bounds);
    vrectSet(10, dialogHeight - 284, 200, 30, &bounds);
    vdialogSetItemRect(vcontrolGetItem(drawdemoLineCapPopup), &bounds);
    vrectSet(10, dialogHeight - 314, 200, 30, &bounds);
    vdialogSetItemRect(vcontrolGetItem(drawdemoLineJoinPopup), &bounds);
    vrectSet(10, dialogHeight - 341, 100, 20, &bounds);
    vdialogSetItemRect(drawdemoMiterLimitLabel, &bounds);
    vrectSet(110, dialogHeight - 341, 100, 20, &bounds);
    vdialogSetItemRect(vtextitemGetItem(drawdemoMiterLimitText), &bounds);
    
    vrectSet(15, 90, 190, 30, &bounds);
    vdialogSetItemRect(vbuttonGetItem(drawdemoStartButton), &bounds);
    vrectSet(15, 50, 190, 30, &bounds);
    vdialogSetItemRect(vbuttonGetItem(drawdemoChangeFontButton), &bounds);
    vrectSet(15, 10, 190, 30, &bounds);
    vdialogSetItemRect(vbuttonGetItem(drawdemoCloseButton), &bounds);
    
    /*
     * The drawing fabric uses whatever horizontal space is left over:
     */
    
    vrectSet(220, 45, dialogWidth - 220, dialogHeight - 45, &bounds);
    vdialogSetItemRect(drawdemoFabric, &bounds);
    
    vrectSet(220, 20, dialogWidth - 220, 20, &bounds);
    vdialogSetItemRect(drawdemoCopyrightLabel, &bounds);
    
    vrectSet(220, 0, dialogWidth - 220, 20, &bounds);
    vdialogSetItemRect(drawdemoReservedLabel, &bounds);

}  /**  _drawdemoResizeDialog()  **/




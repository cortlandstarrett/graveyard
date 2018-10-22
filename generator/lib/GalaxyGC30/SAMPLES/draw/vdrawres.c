/* $Id: vdrawres.c,v 1.2 1994/05/17 18:03:19 jim Exp $
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
 * drawdemoLoad:
 *	Sets up the draw demo's global variables by fetching the dialog
 *	from the resource file
 *
 **********/
void drawdemoLoad(void)
{
    vresource			resource, dialogRes;
    
    /*
     * Pull the dialog out of resource since we have our
     * classes made already
     */
    resource = vapplicationGetResources( vapplicationGetCurrent() );
    
    dialogRes = vresourceGet(resource, 
			     vnameInternGlobalLiteral("DrawDemo2Dialog"));
    drawdemoDialog = vdialogLoad(dialogRes);
    
    vdialogSetNotify(drawdemoDialog, drawdemoDialogNotify);
    
    /*
     * Pull the references to all the standard dialog stuff out of
     * the file.
     */
    
    drawdemoDedicatedCheckBox = (vcontrol *)
      vdialogFindItem(drawdemoDialog, vnameInternGlobalLiteral("Dedicated"));
    
    drawdemoOneAtTimeCheckBox = (vcontrol *)
      vdialogFindItem(drawdemoDialog, vnameInternGlobalLiteral("DrawOnce"));
    
    drawdemoObjectCountText = (vtextitem *)
      vdialogFindItem(drawdemoDialog, vnameInternGlobalLiteral("ObjectCount"));
    
    drawdemoObjectTypePopup = (vcontrol *)
      vdialogFindItem(drawdemoDialog, vnameInternGlobalLiteral("ObjectType"));
    drawdemoObjectTypePopupMenu = vcontrolGetMenu(drawdemoObjectTypePopup);
    
    drawdemoFillTypePopup = (vcontrol *)
      vdialogFindItem(drawdemoDialog, vnameInternGlobalLiteral("FillType"));
    drawdemoFillTypePopupMenu = vcontrolGetMenu(drawdemoFillTypePopup);
    
    drawdemoMonochromeCheckBox = (vcontrol *)
      vdialogFindItem(drawdemoDialog, vnameInternGlobalLiteral("Monochrome"));
    
    drawdemoExclusiveOrCheckBox = (vcontrol *)
      vdialogFindItem(drawdemoDialog, vnameInternGlobalLiteral("XorColors"));
    
    drawdemoRotateAngleText = (vtextitem *)
      vdialogFindItem(drawdemoDialog, vnameInternGlobalLiteral("RotateAngle"));
    
    drawdemoScaleXText = (vtextitem *)
      vdialogFindItem(drawdemoDialog, vnameInternGlobalLiteral("ScaleX"));
    
    drawdemoScaleYText = (vtextitem *)
      vdialogFindItem(drawdemoDialog, vnameInternGlobalLiteral("ScaleY"));
    
    drawdemoFlatnessText = (vtextitem *)
      vdialogFindItem(drawdemoDialog, vnameInternGlobalLiteral("Flatness"));
    
    drawdemoDashedCheckBox = (vcontrol *)
      vdialogFindItem(drawdemoDialog, vnameInternGlobalLiteral("Dashed"));
    
    drawdemoLineWidthText = (vtextitem *)
      vdialogFindItem(drawdemoDialog, vnameInternGlobalLiteral("LineWidth"));
    
    drawdemoLineCapPopup = (vcontrol *)
      vdialogFindItem(drawdemoDialog, vnameInternGlobalLiteral("LineCap"));
    drawdemoLineCapPopupMenu = vcontrolGetMenu(drawdemoLineCapPopup);
    
    drawdemoLineJoinPopup = (vcontrol *)
      vdialogFindItem(drawdemoDialog, vnameInternGlobalLiteral("LineJoin"));
    drawdemoLineJoinPopupMenu = vcontrolGetMenu(drawdemoLineJoinPopup);
    
    drawdemoMiterLimitText = (vtextitem *)
      vdialogFindItem(drawdemoDialog, vnameInternGlobalLiteral("MiterLimit"));
    
    drawdemoStartButton = (vbutton *)
      vdialogFindItem(drawdemoDialog, vnameInternGlobalLiteral("StartBtn"));
    
    drawdemoChangeFontButton = (vbutton *)
      vdialogFindItem(drawdemoDialog, vnameInternGlobalLiteral("FontBtn"));
    
    drawdemoCloseButton = (vbutton *)
      vdialogFindItem(drawdemoDialog, vnameInternGlobalLiteral("CloseBtn"));
    
    drawdemoFabric = (vdialogItem *)
      vdialogFindItem(drawdemoDialog, vnameInternGlobalLiteral("DemoFabric"));
    
    /*
     * Text objects will initially be drawn in the application default font:
     */
    drawdemoFont = vapplicationGetFont(vapplicationGetCurrent());
    
    /*
     * Allocate a color slot:
     */
    drawdemoColor = vcolorGetBlack();
    
}  /**  drawdemoLoad()  **/


/**********
 * drawdemoDialogNotify:
 *	Receives all of the dialog (window) events.
 *
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
}  /**  drawdemoDialogNotify()  **/

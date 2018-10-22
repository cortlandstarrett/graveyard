/* $Id: textprnt.c,v 1.8 1997/10/27 22:20:50 jim Exp $
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
 * copyright notice in the in the form of "Copyright 1992,93 Visix Software
 *  Inc., 11440 Commerce Park Drive, Reston, VA  22091. All Rights Reserved"
 * appears in all copies, (ii) both the copyright notice and this permission
 * notice appear in supporting documentation and (iii) you are a valid
 * licensee of Galaxy Application Environment.
 */

/****************************************************************************
 * executable:    textprnt or textprnt.exe
 * source files:  textprnt.c
 * resource file: textprnt.vr
 *
 * managers illustrated: Print Manager, Text Manager
 *
 * This program illustrates how to quickly get started using the vprint
 * module. It loads a single window containing a vtextitem, and provides
 * several menu options for print processing
 * 
 * To end the demo, select "Quit" from the dialog's "File" menu or just
 * close the main dialog's window
 *
 ****************************************************************************/


#include <vport.h>		/* for v*HEADER */
#include vstdlibHEADER	
#include vexHEADER
#include vrectHEADER
#include vnameHEADER
#include veventHEADER
#include vresourceHEADER
#include vcolorHEADER
#include vfontHEADER
#include vtextHEADER
#include vdrawHEADER
#include vprintHEADER
#include vmenuHEADER
#include vapplicationHEADER
#include vdialogHEADER
#include vmenubarHEADER
#include vtextviewHEADER
#include vtextitemHEADER
#include vfontchsrHEADER
#include vstartupHEADER

/*
 * Stop processing if our top-level dialog is closed, or if the "Quit"
 * menu item is selected.
 */

void dialogNotify(vdialog *dialog, vevent *event)
{
  if (veventGetType(event) == veventWINDOW_STATE && veventIsClose(event)) {
    veventStopProcessing();
  }
}


void quitNotify(vmenuItem *mitem, vevent *event)
{
  veventStopProcessing();
}


/*
 *  confirmJobNotify
 *
 *  Print the textitem.
 *
 */

void confirmJobNotify (vprint *volatile printer, int flag)
{
  /* 
   * <printer> and <printView> need to be "volatile", just like
   * any other variables used:
   *   in an exception handler (vexON_EXCEPTION), or
   *   after an exception handler drops through because it handled
   *     the exception and didn't call vexPropagate
   */   
  vtextview    *volatile printView = NULL;
  vtextview    *view;
  vrect		pageRect, adjustedRect;
  int		lines, totalLines, startLine, endLine;
  int		height, diff;
  
  if(!flag) return;
  
  vexWITH_HANDLING
  {
    vdrawGSave();

    vprintOpenDocument(printer);

    view = (vtextview *) vprintGetData(printer);
    
    /* 
     * Clone the textview so we can change it for printing
     * without messing up the original.
     */
    printView = vtextviewClone(view);
  
    /* Scroll to the top of the textitem */
    vtextviewScroll(printView, 1, 0);
    
    /* Turn off the border */
    vdialogSetItemBorder(vtextviewGetItem(printView),FALSE);

    /* Get the current page rectangle from the printer */
    vrectFromFloat(vprintGetPaper(printer),&pageRect);
    /* Add one-inch margins */
    /*
     * A more sophisticated application that allowed the user to set the
     * margins instead of using fixed one-inch margins should check the
     * resulting rect against vprintGetPage and adjust or warn if the 
     * margins go outside the printable area of the page.
     */
    vrectInset(&pageRect, 72, 72, &pageRect);

    /* Set it to black-on-white */
    vdialogSetItemBackground (vtextviewGetItem(printView),vcolorGetWhite());
    vdialogSetItemForeground(vtextviewGetItem(printView),vcolorGetBlack());
    
    /* Turn off scrollbars */
    vtextviewSetHorzBar(printView, FALSE);
    vtextviewSetVertBar(printView, FALSE);

    totalLines = vtextLines(vtextviewGetTextData(printView));

    for (startLine = 1; startLine <= totalLines; startLine += lines)
    {

      vprintOpenPage(printer);

      /* Scroll to the top of the page */
      vtextviewScroll(printView, startLine, 0);

      /* Set the textview rect to match the current page, with margins */
      vdialogSetItemRect(vtextviewGetItem(printView),&pageRect);
      lines = vtextviewLines(printView);
      endLine = startLine+lines-1;
      if (endLine > totalLines)
      	endLine = totalLines;

      /* 
       * If necessary, adjust the rect so the last line is not clipped,
       * but if one whole line will not fit on the page, clip it.
       */
      height = vtextHeightOfLines(vtextviewGetTextData(printView),
    		    	    	        startLine, endLine);
      if (lines > 1 && height > pageRect.h)
      {
        diff = pageRect.h - vtextHeightOfLines(vtextviewGetTextData(printView),
	                                       startLine, endLine - 1);
	lines--;
	
        vrectSet(pageRect.x, pageRect.y, pageRect.w, pageRect.h, 
                 &adjustedRect);
        adjustedRect.y += diff;
        adjustedRect.h -= diff;
        vdialogSetItemRect(vtextviewGetItem(printView),&adjustedRect);
      }

      /* Print the item */
      vdialogSetItemDraw(vtextviewGetItem(printView));
      vdialogDrawItem(vtextviewGetItem(printView));

      vprintClosePage(printer);
    }
    
    vprintCloseDocument(printer);
    
  } vexON_EXCEPTION {
    
    /* Make sure printing is closed down. */
    if (vprintPageIsOpen(printer)) vprintClosePage(printer);
    if (vprintDocumentIsOpen(printer)) vprintCloseDocument(printer);

    /* 
     * If the user canceled, drop out of the vexWITH_HANDLING block
     * and continue normally. Otherwise, assume a fairly serious
     * error occurred; just clean up and pass along the exception,
     * in this case causing the program to exit.
     *
     * In a real program, you might just handle all exceptions
     * during printing (by notifying the user, taking corrective
     * action, or just doing nothing) so your application doesn't
     * exit unexpectedly due to printing problems.
     */ 
    if (!vprintGetJobCanceledException()) {
      if (printView) vtextviewDestroy(printView);
      vdrawGRestore();
      vexPropagate(vexGetRootClass(), vexNULL);
    }
    
  } vexEND_HANDLING;

  /* Destroy the printing view */
  if (printView) vtextviewDestroy(printView);
  vdrawGRestore();
}


/*
 *  PrintNotify
 *
 *  Confirm printing of the textitem.
 *
 */

void printNotify (vmenuItem *mitem, vevent *event)
{
  vprint      *printer;
  vtextitem   *textItem;
  
  textItem    = (vtextitem *) vmenuGetItemData(mitem);
  printer = (vprint *)vtextitemGetData(textItem);

  vprintSetJobNotify(printer, (vprintNoteProc)confirmJobNotify);
  
  vprintSetData(printer, (void *)vtextitemGetView(textItem));
  
  vprintConfirmJob(printer);
}


/*
 *  printSetupNotify
 *
 *  Confirms the print style
 *
 */

void printSetupNotify (vmenuItem *mitem, vevent *event)
{
  vprint      *printer;
  vtextitem   *textItem;
  
  textItem    = (vtextitem *) vmenuGetItemData(mitem);
  printer = (vprint *)vtextitemGetData(textItem);

  vprintConfirmStyle(printer);
}


/*
 *  chooseFontNotify
 *
 *  let the user pick a font
 *
 */

void chooseFontNotify (vmenuItem *mitem, vevent *event)
{
  vfontchsr   *chsr;
  vtextitem   *textItem;
  
  chsr    = (vfontchsr *) vmenuGetItemData(mitem);
  textItem = (vtextitem *) vfontchsrGetData(chsr);
  
  vfontchsrSetFont(chsr, vdialogDetermineItemFont(vtextitemGetItem(textItem)));
  vfontchsrOpen(chsr);
}


int chooseFontApply (vfontchsr *chsr, vfont *font)
{
  vtextitem	*textItem;

  textItem = (vtextitem *) vfontchsrGetData(chsr);
  vdialogSetItemFont(vtextitemGetItem(textItem), font);
  return vTRUE;
}

int main(int argc, char *argv[])
{
  vdialog	*dialog;
  vtextitem	*textItem;
  vresource	res;
  vmenubar	*menubar;
  vmenu		*menu;
  vmenuItem	*mitem;
  vprint	*printer;
  vfontchsr	*chsr;

  /*
   * Initialize galaxy runtime environment
   */
  vstartup(argc, argv);

  /*
   * Enable print dialogs, since this is a graphical app
   */
  vprintEnableConfirms();

  /*
   * Load the main dialog
   */
  res    = vresourceGet(vapplicationGetResources(vapplicationGetCurrent()),
  			vnameInternGlobalLiteral("MainDialog"));
  dialog = vdialogLoad(res);
  vdialogSetNotify(dialog, dialogNotify);

  textItem = (vtextitem*)vdialogFindItem(dialog, 
					 vnameInternGlobalLiteral("Text"));

  chsr = vfontchsrCreate();
  vfontchsrSetData(chsr, textItem);
  vfontchsrSetApply(chsr, chooseFontApply);

  /* Set up the 'print' menu item */
  menubar = (vmenubar*)vdialogFindItem(dialog, 
				     vnameInternGlobalLiteral("Menu Bar"));
  menu    = vmenubarFindMenu(menubar, vnameInternGlobalLiteral("FileMenu"));
  mitem   = vmenuFindItem(menu, vnameInternGlobalLiteral("DoPrint"));
  vmenuSetItemData(mitem, textItem);
  vmenuSetItemNotify(mitem, printNotify);
  
  /* Set up the 'print setup' menu item */
  mitem   = vmenuFindItem(menu, vnameInternGlobalLiteral("PrintSetup"));
  vmenuSetItemData(mitem, textItem);
  vmenuSetItemNotify(mitem, printSetupNotify);

  /* Set up the 'choose font' menu item */
  mitem   = vmenuFindItem(menu, vnameInternGlobalLiteral("ChooseFont"));
  vmenuSetItemData(mitem, chsr);
  vmenuSetItemNotify(mitem, chooseFontNotify);

  /* Set up the 'quit' menu item */
  mitem   = vmenuFindItem(menu, vnameInternGlobalLiteral("Quit"));
  vmenuSetItemNotify(mitem, quitNotify);

  printer = vprintCreateOfClass(vprintGetInteractiveClass());
  vprintSetDocumentOwner(printer, vdialogGetObject(dialog));
  vtextitemSetData(textItem, (void *)printer);

  vdialogOpen(dialog);
  
  /* Process events until the window is closed */
  
  veventProcess();
  
  /* Clean up our stuff */
  
  vdialogDestroy(dialog);
  
  vprintDestroy(printer);

  vfontchsrDestroy(chsr);

  exit(EXIT_SUCCESS);
  
  return EXIT_FAILURE;
}

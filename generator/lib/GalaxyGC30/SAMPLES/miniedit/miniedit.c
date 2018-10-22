/* $Id: miniedit.c,v 1.43 1995/06/30 19:48:03 dimitri Exp $
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

/************************************************************

    vedit.c
    Mini text editor using the Text Manager

************************************************************/

#ifndef  vportINCLUDED
#include <vport.h>		/* for v*HEADER */
#endif

#ifndef  vstdlibINCLUDED
#include vstdlibHEADER
				/* for exit(), etc. */
#endif

#ifndef  vstrINCLUDED
#include vstrHEADER
#endif

#ifndef  veventINCLUDED
#include veventHEADER
#endif

#ifndef  vfsINCLUDED
#include vfsHEADER
#endif

#ifndef  vprefINCLUDED
#include vprefHEADER
#endif

#ifndef  vdomainINCLUDED
#include vdomainHEADER
#endif

#ifndef  vdialogINCLUDED
#include vdialogHEADER
#endif

#ifndef  vtextviewINCLUDED
#include vtextviewHEADER
#endif

#ifndef  vfontchsrINCLUDED
#include vfontchsrHEADER
#endif

#ifndef  vstartupINCLUDED
#include vstartupHEADER
#endif

#if (vdebugDEBUG)
static const char		 _vminieditTag[] = "vminiedit";
#define vdebugTAG		 _vminieditTag
#endif

vfontchsr	*fontChooserWindow = NULL;

/*
 * Stop processing if our top-level dialog is closed
 */
void dialogNotify(vdialog *dialog, vevent *event)
{
    vrect		 bounds;
    vtextview		*textview;

    if (veventIsClose(event)) 
    {
	veventStopProcessing();
    } 
    else if (veventIsSize(event)) 
    {
	bounds = *vwindowGetRect(vdialogGetWindow(dialog));
	bounds.x = 0;
	bounds.y = 0;
	vrectInset(&bounds, 6, 6, &bounds);
	textview = (vtextview*)vdialogGetData(dialog);
	vdialogSetItemRect(vtextviewGetItem(textview), &bounds);
    }
}

/*
 * reopen the font chooser if a selection is made
 */
void textviewNotify(vtextview *textview, vevent *event, int message)
{
    vdebugTraceEnter(textviewNotify);

    if (   (message == vtextviewSELECT_NOTIFY)
	&& (vtextSelectionLength(vtextviewGetSelection(textview)) > 0))
    {
	vdebugMTrace(("SELECT_NOTIFY\n"));
	vfontchsrOpen(fontChooserWindow);
    }

    vdebugTraceLeave();
}

/*
 * Create a new empty edit record
 */
void newDocument(vtextview *textView)
{
    vtext	 *editRec;

    editRec = vtextviewGetTextData(textView);

    vtextAppendBlock(editRec, 
		     (vchar *) vmemAlloc(vtextTEXT_BLOCK_SIZE * sizeof(vchar)),
		     0, vtextTEXT_BLOCK_SIZE);
    vtextCalculate(editRec);

    vtextSelectRange(editRec, vtextviewGetSelection(textView), 0, 0);
}

/*
 * open a new document and read in the specified file into it
 */
void openDocument(vtextview *textView, vfsPath *path)
{
    vtext		*editRec;
    vchar		*remainsBuffer, *buffer, *readBuffer, *blockBuffer;
    vfsFile * volatile	 fileSpec = NULL;
    vbool  volatile 	 done = FALSE, paragraphTooLong = FALSE;
    long		 availableLength;
    long		 remainsLength;
    long		 length, lastEOLN;
    long		 lengthWithEndOfLine;
    long		 blockLength;
    
    vexWITH_HANDLING 
    {
	fileSpec = vfsOpenFile(path, vfsOPEN_READ_ONLY | vfsOPEN_TEXT_MODE);
    }
    vexON_EXCEPTION 
    {
	vwindowBeep();
    }
    vexEND_HANDLING;

    if (fileSpec == NULL) 
    {
        newDocument(textView);
    }
    else
    {
	/*
	 * scan the text file; build nicely sized blocks of complete
	 * paragraphs; paragraphs end with an EOLN character
	 * (force EOLN character if strings get too unwieldy)
	 * call vtextAppendBlock on each well-formed block 
	 */

	editRec = vtextviewGetTextData(textView);

	/*
	 * remainsBuffer is a temporary buffer, used to keep around 
	 * starts of paragraphs that were read in without reaching 
	 * the EOLN character
	 */
    
	remainsBuffer = 
	   (vchar *) vmemAlloc(vtextTEXT_BLOCK_SIZE * sizeof(vchar));

	remainsLength = 0;

	while (!done)
	{
	    /*
	     * the blockBuffer points to the buffer that will be appended
	     * to the text object as one block via vtextAppendBlock;
	     * a new remainsBuffer gets allocated here
	     */
    
	    blockBuffer = remainsBuffer;

	    remainsBuffer = 
	       (vchar *) vmemAlloc(vtextTEXT_BLOCK_SIZE * sizeof(vchar));
    
	    availableLength = vtextINIT_TEXT_SIZE - remainsLength;
	    blockLength     = remainsLength;
	    buffer          = blockBuffer + remainsLength;

	    /*
	     * lastEOLN is the last character position just past 
	     * an EOLN character
	     */
	     
	    lastEOLN        = 0;
	    /*
	     * vfsReadString returns at most availableLength - 1 characters
	     * the last character may be an EOLN character (the only EOLN
	     * character in the string returned)
	     */
	    while (availableLength > 1) 
	    {
	       readBuffer = vfsReadString(buffer, availableLength, fileSpec);
	       
	       if (readBuffer == NULL) 
	       {
		  length = 0;
		  done = TRUE;	/* EOF */
		  break;
	       } 
	       else 
	       {
		  length = vcharLength(buffer);
		  /*
		   * length >=1
		   * update lastEOLN position if applicable
		   */
		  if (buffer[length - 1] == vtextEOLN)
		  {
		     lastEOLN = blockLength + length;
		  }
	       }

	       blockLength     += length;
	       availableLength -= length;
	       buffer          += length;
	    }

	    if (!done)
	    {
		if (lastEOLN == 0)
		{
		    paragraphTooLong = TRUE;
		    /*
		     * increment length for EOLN character
		     * to be added to the blockBuffer
		     */
		    blockLength++;
		    lengthWithEndOfLine = blockLength;
		}
		else
		{
		    lengthWithEndOfLine = lastEOLN;
		}
    
		/*
		 * copy characters past the last EOLN character
		 * of the blockBuffer into the remainsBuffer
		 */
		remainsLength = blockLength - lengthWithEndOfLine;
		(void)vmemCopy(blockBuffer + lengthWithEndOfLine, 
			       remainsBuffer, 
			       remainsLength * sizeof(vchar));
    
		/*
		 * add the EOLN character to the blockBuffer
		 * if necessary (not in the file data)
		 * has to be done after the remains were copied over
		 * to the remainsBuffer
		 */
		if (paragraphTooLong)
		    blockBuffer[blockLength - 1] = vtextEOLN;
	    }
	    else 
	    {
		lengthWithEndOfLine = blockLength;
	    }
    
	    vtextAppendBlock(editRec, blockBuffer, lengthWithEndOfLine,
			     vtextTEXT_BLOCK_SIZE);
	}
    
	/*
	 * free the extra remainsBuffer lying around
	 */
	vmemFree(remainsBuffer);

	vtextCalculate(editRec);

	vtextSelectRange(editRec, vtextviewGetSelection(textView), 0, 0);

	vfsCloseFile(fileSpec);
    }
}

/*
 * take the user-chosen font and apply to the currently visible selection
 */
int applyFont(vfontchsr *fontChsrer, vfont *font)
{
    vtextStyle		*style;
    vtextview		*textView;

    textView = (vtextview *) vfontchsrGetData(fontChsrer);
    style    = vtextCreateStyle();

    vtextSetStyleAttribute(style, vtext_Font, font);

    vtextInstallStyleOwned(vtextviewGetTextData(textView), style);

    vtextApplyStyle(vtextviewGetTextData(textView),
		    vtextviewGetSelection(textView), style);

    /*
     * return TRUE to indicate the font choice was OK and the chooser
     * may be closed
     */
    return TRUE;
}

int main(int argc, char *argv[])
{

    vdialog		*newDialog;
    vtext		*editRec;
    vtextview		*textView;
    vtextStyle		*style;	
    vrect		bounds;
    vtextSelection	*selection;
    vfsPath		**paths;
    int			numFiles;

    vstartup(argc, argv);

    /*
     * Create a dialog to display the domain in 
     */

    newDialog = vdialogCreate();
    
    vdialogSetTitleScribed(newDialog,
		  vcharScribeLiteral("Miniedit - Text Manager Example"));
    vdialogSetNotify(newDialog, dialogNotify);
    vdialogResize(newDialog, 600, 400);
    vdialogMove(newDialog, 20, 20);

    /*
     * Create the text data
     */
    
    editRec = vtextCreate();
    
    /*
     * Now create the text view
     */

    textView = vtextviewCreate();

    /*
     * Create a selection for our view
     */

    selection = vtextCreateSelection(editRec);

    vtextviewSetTextData(textView, editRec);
    vtextviewSetSelection(textView, selection);
    vtextviewSetHorzBar(textView, TRUE);
    vtextviewSetVertBar(textView, TRUE);

    /* 
     * Set the default style for our text view
     */

    style = vtextCreateStyle();
    vtextSetStyleAttribute(style, vtext_Font,
			   vfontFindScribed(vcharScribeLiteral(
		           "family:fixed-size:13-face:semicondensed")));
    vtextSetDefaultStyleOwned(editRec, style);

    /*
     * Add the text view dialog item to the dialog and set the size of the
     * text view to be the size of the dialog inset 6 pixels.
     */

    vrectSet(0, 0, 600, 400, &bounds);
    vrectInset(&bounds, 6, 6, &bounds);
    vdialogSetItemRect(vtextviewGetItem(textView), &bounds);

    vdialogAppendItem(newDialog, vtextviewGetItem(textView));
    vdialogSetDefFocus(newDialog, vtextviewGetItem(textView));
    vdialogSetData(newDialog, textView);

    /*
     * If there was a command line argument, try to open the file,
     * otherwise, open an empty file
     */

    vfsGetArgs(&numFiles, (const vfsPath ***)&paths);
    if (numFiles > 1)
        openDocument(textView, paths[1]);
    else
        newDocument(textView);

    /* 
     * Now set up a font chsring window that will let us apply 
     * styles to text selections
     */

    fontChooserWindow = vfontchsrCreate();
    vfontchsrSetData(fontChooserWindow, textView);
    vfontchsrSetApply(fontChooserWindow, applyFont);
    vdialogPlace(vfontchsrGetDialog(fontChooserWindow), newDialog,
		 vrectPLACE_RIGHT | vrectPLACE_NEAR, vrectPLACE_ALIGN);

    /* now set it up so that any text manipulation reopens the fontchsr */

    vtextviewSetNotify(textView, textviewNotify);

    /* Now that everything is ready, open the windows */

    vdialogOpen(newDialog);
    vfontchsrOpen(fontChooserWindow);

    /* Process events until the window is closed */

    veventProcess();

#if (vdebugDEBUG)
    /*
     * Clean up our stuff
     * 'vdialogDestroy' will destory our text view for us
     * We have to destroy the text data
     */

    vdialogDestroy(newDialog);
    vtextDestroy(editRec);

    if (fontChooserWindow != NULL)
	vfontchsrDestroy(fontChooserWindow);
#endif

    exit(EXIT_SUCCESS);
    return EXIT_FAILURE;
}

/* $Id: dragimg.c,v 1.5 1997/11/19 23:42:54 gregt Exp $ */

/* The legal types make me put this here.
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
 * copyright notice in the form of "Copyright 1994 Visix Software Inc.,
 * 11440 Commerce Park Drive, Reston, VA  22091. All Rights Reserved" appears
 * in all copies, (ii) both the copyright notice and this permission notice
 * appear in supporting documentation and (iii) you are a valid licensee of
 * Galaxy Application Environment.
 *
 * Do not taunt Happy Fun Ball.
 */

/* Executable Name: dragimg
 * Source Files:    dragimg.c
 * Header Files:    none
 * Resource Files:  dragimg.vr
 *
 * Managers Illustrated:
 *     vimage, vpixmap, vdraw
 *
 * Description Of Sample:
 *     This sample shows how to "live drag" an image across a dialog.
 *     To do "drag and drop" style user interaction, please see the 
 *     Drag Manager
 *
 *
 * History:
 *	Written for Galaxy 1.2 release, 7/14/93
 *	Updated to show how to update changed items 7/19/93
 *	Minor house-cleaning (using command templates, minimal startup, etc)
 *         10/6/94
 */


/* This sample show how to "live drag" an image across a dialog.  It does
 * so by polling the mouse position, then drawing the image where the mouse
 * is located.  It "removes" the image from the previous location by copying
 * in bits from an off-screen bitmap of the virgin unmolested dialog.
 */


/* more details:
 * When the program starts up, an offscreen bitmap is created with
 * vwindowCreateBufferImage (which is necessary so that you can do
 * a vdrawImageDevice to draw into it).  The dialog is then drawn onto
 * the bitmap, giving a pristine copy of the dialog for reference when 
 * repairing any damage we may do to it.
 *
 * A timer is also set up that polls the mouse position.
 *
 * When the timer fires, the mouse position is determined so we know
 * where to draw the image we're dragging around (called the "image").  
 * Another offscreen bitmap, (the "workImage"), is created to be the size
 * of the union of the rectangle of image's old location and it's new location.
 * The pristine bits are copied from the original bitmap (called the 
 * "dialogImage") into the workImage, The image's new location is then drawn
 * in there, and then the workImage is drawn into the dialog.  This 
 * intermediate image (the workImage) is what gives the smoothness to the
 * drawing.  The user never sees any erasing and redrawing, just an
 * instantaneous "jump" of the image from one place to another.  The tradeoff
 * for this is the memory overhead for the original copy of the dialog.
 *
 * Known limitations / exercises for the user:
 *
 *  Changes in the dialog size do not update the dialogImage's bitmap.
 *      If the user resizes the dialog, you'll need to create a new image
 *      of the proper size and redraw the window.
 *
 *  The dragged image can't straddle the window's border.
 *      Right now, the timer handler that drives this whole shebang pins
 *      the image so that it is completly inside the borders of the window.
 *      If you allowed it to be partially off, you'll need to do extra 
 *      math and more complicated pixmap operations. Otherwise you'll get
 *      vpixmap range exceptions trying to do operations on non-existent
 *      portions of pixmaps.
 *
 *  Full-screen dragging isn't implemented.
 *      A similar technique can be used for full-screen dragging, but
 *      isn't advisable.  The overhead for creating an off-screen image
 *      for the entire screen would be immense.  Plus there is the problem
 *      of your process not owning the entire screen.  Some other process
 *      could draw something that would get obliterated by the dragging code.
 *      You'd need to snarf only the chunks you need from the screen during
 *      dragging.  You could do a vwindowGrabInput to temporarily "lock"
 *      the screen so that others wouldn't be able to write to it.
 *
 *  Some dialog item states aren't reflected in the off-screen bitmap, such
 *      as focus drawing.
 */

#ifndef vportINCLUDED
#include <vport.h>
#endif

/* for EXIT_SUCCESS et. al. */
#ifndef vstdlibINCLUDED
#include vstdlibHEADER
#endif

#ifndef vtimerINCLUDED
#include vtimerHEADER
#endif

#ifndef vimageINCLUDED
#include vimageHEADER
#endif

#ifndef vprefINCLUDED
#include vprefHEADER
#endif

#ifndef vapplicationINCLUDED
#include vapplicationHEADER
#endif

#ifndef vdialogINCLUDED
#include vdialogHEADER
#endif

/* we've got buttons in our sample dialog */
#ifndef vbuttonINCLUDED
#include vbuttonHEADER
#endif

/* and containers */
#ifndef vcontainerINCLUDED
#include vcontainerHEADER
#endif

/* and controls */
#ifndef vcontrolINCLUDED
#include vcontrolHEADER
#endif

/* and textitems */
#ifndef vtextitemINCLUDED
#include vtextitemHEADER
#endif




/* handy macro */
#define TAG(s)	vnameInternGlobalLiteral((s))


/* this is the image that will get dragged around
 */
static vimage *image = NULL;

/* convenience cache of the image's width and height.  It just saves
 * repeated calls to the vimageGetWidth(), vimageGetHeight() routines.
 */
static int imageW, imageH;


/* the pristine bits that we use to clean up the mess caused by dragging
 */
static vimage *dialogImage = NULL;


/* where the image is currently shown.  This is where we need to clean up.
 */
static vrect imageRect = {-1, -1, -1, -1};



/*
 * ----- 
 */


/* _timerNotify -- the timer notification function that just-so-happens to
 *                 live drag an image around the dialog.
 *
 *  -> timer -- the timer that fired.
 *
 * This timer has the dialog dragging the image stored in its data pointer.
 */
static void _timerNotify (vtimer *timer)
{
    int      x, y;      /* where the mouse is now */
    vrect    rect;      /* new location of the dragged image */
    vrect    unionRect; /* union of rect and imageRect */
    vdialog *dialog = vtimerGetData (timer); /* the dialog we're dragging in */
    vwindow *window;    /* convenience pointer. */

    /* just so we don't have to do vdialogGetWindow() all over the place */
    window = vdialogGetWindow (dialog);

    /* find out where the mouse cursor is now.  The (x, y) is relative to
     * the bottom-left of our dialog
     */
    vwindowGetPointer (window, &x, &y);

    /* pin it so we won't have to do straddle calculations*/
    {
	/* off bottom or left */
	if (x < 0) x = 0;
	if (y < 0) y = 0;

	/* off right side */
	if (x > (vwindowGetW(window) - imageW)) {
	    x = vwindowGetW(window) - imageW;
	}

	/* off top */
	if (y > (vwindowGetH(window) - imageH)) {
	    y = vwindowGetH(window) - imageH;
	}
    }

    /* if this is the first time through, draw the image and initialize
     * the global "imageRect"
     */
    if (imageRect.x == -1) {

	/* The current drawing device is undefined now.  Force it to be
	 * what we want.  We better save the current GState first, in case
	 * someone is using it.
	 */
	vdrawGSave ();

	vwindowDrawDevice (window);

	/* our image has a mask.  If it didn't have a mask, just use
	 * vdrawImageIdent()
	 */
	vdrawMoveTo (x, y);
	vdrawImageCompositeIdent (image);

	vdrawGRestore ();
	
	vrectSet (x, y, imageW, imageH, &imageRect);
	
    } else {

	/* figure out where the image should go now */
	vrectSet (x, y, imageW, imageH, &rect);
	
	/* this is the area we'll need to redraw. */
	vrectUnion (&imageRect, &rect, &unionRect);
	
	{
	    vimage *workImage = vwindowCreateBufferImage (unionRect.w,
							  unionRect.h);

	    /* copy the damaged area from the pristine bits to the
	     * work area.  We don't need to erase the image before hand
	     * because it is being completely replaced by the 
	     * original dialog bits.
	     */
	    vpixmapCopyRect (vimageGetMap(dialogImage),
			     vimageGetMap(workImage),
			     unionRect.x,
			     unionRect.y,
			     unionRect.w,
			     unionRect.h,
			     0,
			     0);
	    
	    /* now draw image into workImage */
	    
	    /* we don't know whose drawing context we'll screw up, so
	     * save it first
	     */
	    vdrawGSave ();

	    /* draw into workImage */
	    vdrawImageDevice (workImage);

	    /* draw the image */
	    vdrawMoveTo (x - unionRect.x, y - unionRect.y);
	    vdrawImageCompositeIdent (image);

	    /* now get ready to draw into the dialog */
	    vwindowDrawDevice (window);
	    
	    vdrawMoveTo (unionRect.x, unionRect.y);
	    vdrawImageIdent (workImage);

	    /* clean up our drawing context mess */
	    vdrawGRestore ();
	    
	    /* get rid the workImage */
	    vimageDestroy (workImage);
	}

	/* update imageRect to reflect its new location */
	imageRect.x = x;
	imageRect.y = y;
    }

} /* _timerNotify */




/* _updateDialogImage -- updates the offscreen dialog image with
 *			 the bits for a dialog item that has changed.
 *
 *  -> dialog   -- the dialog that had a changed item
 *  -> image    -- the off-screen image to draw in.
 *  -> item     -- the dialog item to draw.
 *
 * If we didn't update the dialog image, the old image would get restored
 * when the user drags the image back over the item.  To see what I mean,
 * comment out everything in this function, turn on a checkbox, and drag
 * over it.
 *
 * Doing things like checkboxes and one-line textitems is easy.  Just
 * call this when the command is issued or the notification is called.
 *
 * For things like lists and domains (and text when set up for more
 * sophisticated stuff), you'll need to watch all of the different things
 * that can change: scrolling, selection, keyboard traversal, etc...
 */
static void _updateDialogImage (vdialog *dialog, vimage *image,
				vdialogItem *item)
{
    vcolorScheme		 scheme;

    /* we don't know whose GState we're mucking with */
    vdrawGSave ();

    /* draw into the image */
    vdrawImageDevice (image);

    /* get things set up so the dialog can draw properly */
    vdrawSetFont (vdialogDetermineItemFont(item));
    vdrawSetLineWidth (vdialogDetermineItemLineWidth(item));
    vcolorInitScheme (&scheme);
    vdialogDetermineItemColorSchemeState (item, vcolorFLAG_FOREGROUND |
					  vcolorFLAG_BACKGROUND, &scheme);
    vdrawSetColor (vcolorGetSchemeForeground(&scheme));
    vdrawSetComplement (vcolorGetSchemeBackground(&scheme));
    vcolorDestroyScheme (&scheme);

    /* actually draw it */
    vdialogDrawItem (item);

    vdrawGRestore ();

} /* _updateDialogImage */




/* _checkboxIssue -- issue function for checkboxes.  This update the
 *		     off-screen image to reflect the change in state.
 *
 *  -> command    -- the function command for the checkbox that was triggered
 *  -> attr2value -- context dictionary
 * <-		  -- TRUE if we handled it, FALSE otherwise
 */
static int _checkboxIssue (vcommandFunction *command, vdict *attr2value)
{
    _updateDialogImage ((vdialog*)vdictLoad (attr2value, vname_Dialog),
			dialogImage,
			(vdialogItem*)vdictLoad(attr2value, vname_Operator));
    return (TRUE);
} /* _checkboxIssue */




/* textitemNotify -- update the off-screen bits to track changes made
 *		     to a textitem.
 *
 *  -> textitem -- the textitem that had something done to it
 *  -> event    -- the event that happened.
 *  -> message  -- what happened.
 */
static void textitemNotify (vtextitem *textitem, vevent *event, int message)
{
    vdialogItem *item = vtextitemGetItem (textitem);

    /* we only act on vtextviewSELECT_NOTIFY, since it will get called
     * on all interesting changes (selection gets changed, text
     * is inserted or deleted, etc...)
     */
    if (message == vtextviewSELECT_NOTIFY) {
	_updateDialogImage (vdialogDetermineItemDialog (item),
			    dialogImage,
			    item);
    }

} /* textitemNotify */




/* _setupDialog -- get the offscreen bitmap ready and start up the timer.
 *
 *  -> dialog -- the dialog to set up.  Also the dialog we'll drag in
 */
static void _setupDialog (vdialog *dialog)
{
    vwindow *window = vdialogGetWindow (dialog);
    vtimer  *timer;
    vtextitem *textitem;

    /* make something to keep the unmolested bits in */
    dialogImage = vwindowCreateBufferImage (vwindowGetW(window),
					    vwindowGetH(window));

    /* save the drawing context, because we're about to mess with it */
    vdrawGSave ();

    /* draw into the image */
    vdrawImageDevice (dialogImage);
    

    /* erase the image first, otherwise we'll get random garbage in it */
    vdrawSetColor (vwindowDetermineColor (window, vdrawCOLOR_BACKGROUND));
    vdrawRectFill (0, 0, vwindowGetW(window), vwindowGetH(window));

    /* get things set up so the dialog can draw properly */
    vdrawSetFont (vwindowDetermineFont (window));
    vdrawSetLineWidth (vwindowDetermineLineWidth (window));
    vdrawSetColor (vwindowDetermineColor (window, vdrawCOLOR_FOREGROUND));
    vdrawSetComplement (vwindowDetermineColor (window, vdrawCOLOR_BACKGROUND));
    vwindowDraw (window);

    /* clean up our GState mess */
    vdrawGRestore ();

    /* create the timer and let it get started. */
    timer = vtimerCreate ();
    vtimerSetPeriod (timer, 0, vtimestampSECOND / 16);
    vtimerSetRecurrent (timer);
    vtimerSetCallback (timer, _timerNotify);
    vtimerSetData (timer, dialog);
    vtimerStart (timer);

    vdialogSetData (dialog, timer);

    /* and set up the textitem to so that we can update the off-screen
     * image when the text changes.
     */
    textitem = (vtextitem*) vdialogFindItem (dialog, TAG("textitem"));
    vtextitemSetNotify (textitem, textitemNotify);
    vtextviewSetOffscreenDrawing (vtextitemGetView(textitem), TRUE);

} /* _setupDialog */




/* _shutdownDialog -- clean up this dialog *except* for the actual 
 *		      vdialogDestroy
 *
 *  -> dialog -- the dialog to shut down
 */
static void _shutdownDialog (vdialog *dialog)
{
    vtimer *timer;

    /* sometimes timers leak 24 bytes.  Don't panic, This is a bug. */
    timer = (vtimer*)vdialogGetData (dialog);
    vtimerStop (timer);
    vtimerDestroy (timer);

} /* _shutdownDialog */




/* _generalSetup -- get the image we'll be dragging
 */
static void _generalSetup (void)
{
    vresource imageres;

    vbuttonStartup ();
    vcontainerStartup ();
    vcontrolStartup ();
    vtextitemStartup ();
    vdialogStartup ();

    if (image == NULL) {
	imageres = vresourceGet (vapplicationGetResources
				 (vapplicationGetCurrent()),
				 TAG("Image"));
	image = vimageLoad (imageres);
	imageW = vimageGetWidth (image);
	imageH = vimageGetHeight (image);
    }

} /* _generalSetup */




/* _generalShutdown -- clean up our mess.
 */
static void _generalShutdown (void)
{
    if (image != NULL) {
	vimageDestroy (image);
    }

    if (dialogImage != NULL) {
	vimageDestroy (dialogImage);
    }

} /* _generalShutdown */




/*
 * ----- Generic Scaffolding follows
 */


static int _quitIssue (vcommandFunction *command, vdict *attr2value)
{
    veventStopProcessing ();
    return (TRUE);
} /* _quitNotify */



static int _closeIssue (vcommandFunction *command, vdict *attr2value)
{
    veventStopProcessing ();
    return (TRUE);
} /* _closeIssue */





static vcommandFunctionTemplate commandTable[] = {
    { "Check Box",	       _checkboxIssue,		NULL },
    { "Radio Group",	       _checkboxIssue,		NULL },

    { "Close",		       _closeIssue,		NULL },
    { "Quit",		       _quitIssue,		NULL },
};



/* _setupCommands -- set up a command space in the given dialog.
 */
static void _setupCommands (vdialog *dialog)
{
    vcommandSpace *space;
    vdict *dict;

    dict = (vcommandCreateDictFunctionTemplates
	    (commandTable,
	     sizeof(commandTable) / sizeof(vcommandFunctionTemplate)));
						
    space = vcommandCreateSpace ();

    vcommandAddSpaceDictOwned (space, vname_Command, dict);

    vwindowSetSpaceOwned (vdialogGetWindow(dialog), space);
    
} /* _setupCommands */






int main (int argc, char *argv[])
{
    vresource appres, dialogres;
    vdialog *dialog;

    vprefSetArgs (argc, argv);

    _generalSetup ();

    appres = vapplicationGetResources (vapplicationGetCurrent());
    dialogres = vresourceGet (appres, TAG("Dialog"));

    dialog = vdialogLoad (dialogres);

    _setupCommands (dialog);

    /* note that the _setupDialog comes *after* the vdialogOpen.
     * some things (like radio groups and checkboxes) don't draw correctly
     * until the dialog is opened.
     */

    vdialogOpen (dialog);

    _setupDialog (dialog);

    veventProcess ();

    _shutdownDialog (dialog);

    vdialogDestroy (dialog);

    _generalShutdown ();

    exit (EXIT_SUCCESS);
    return (EXIT_FAILURE);

} /* main */





/*
 * Formatting information for emacs in c-mode
 *
 * Local Variables:
 * c-indent-level:4
 * c-continued-statement-offset:0
 * c-brace-offset:0
 * c-brace-imaginary-offset:0
 * c-argdecl-indent:0
 * c-label-offset:0
 * End:
 */


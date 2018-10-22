/* $Id: spam.c,v 1.9 1994/06/21 13:26:21 thomas Exp $ */
/* The legal types make me put this in here.
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
 * Do not taunt Happy Fun Ball
 */

/* Executable Name:	vspam
 * Source Files:	_vspam.c
 * Header Files:
 * Library Source:
 * Library Headers:
 * Resource Files:
 *
 * Managers Illustrated:
 *	Window (vwindow)
 *	Event (vevent)
 *
 * Description Of Sample:
 *	This sample shows how to draw graphics directly on the root window.
 *
 *	When running, this sample will pop up a graphic every now and then.
 *
 *	This sample has no window associated with it and must be terminated
 *	via the operating system.
 *
 * 	The heart of this sample is an offscreen image.  Since we are
 *	drawing directly on the root window, we need to be able to restore
 *	what we are drawing over when the program is done.  This is achieved
 *	by taking a snopshot of the area about to be drawn upon and stashing
 *	it away.  Later, when the drawing is to be taken down, the offscreen
 *	image is used to restore the damaged area.
 *
 * History:
 * $Log: spam.c,v $
 * Revision 1.9  1994/06/21  13:26:21  thomas
 * fixed includes for makedepend
 *
 * Revision 1.8  1994/02/16  08:24:45  chad
 * tweaked
 *
 * Revision 1.7  1994/02/16  06:37:41  chad
 * nuked global variables w and h to not conflict with mac types.h enums of v and h
 *
 * Revision 1.6  1994/02/05  22:38:50  chad
 * commented/copyrighted
 *
 */

#ifndef  vportINCLUDED		/* for v*HEADER */
#include <vport.h>
#endif

#ifndef  vstdlibINCLUDED	/* for rand, exit */
#include vstdlibHEADER
#endif

#ifndef  vdrawINCLUDED
#include vdrawHEADER
#endif

#ifndef  veventINCLUDED
#include veventHEADER
#endif

#ifndef  vfontINCLUDED
#include vfontHEADER
#endif

#ifndef  vimageINCLUDED
#include vimageHEADER
#endif

#ifndef  vmatrixINCLUDED
#include vmatrixHEADER
#endif

#ifndef  vprefINCLUDED
#include vprefHEADER
#endif

#ifndef  vrectINCLUDED
#include vrectHEADER
#endif

#ifndef  vstrINCLUDED
#include vstrHEADER
#endif

#ifndef  vwindowINCLUDED
#include vwindowHEADER
#endif

#ifndef  vtimestampINCLUDED
#include vtimestampHEADER
#endif

#ifndef  vapplicationINCLUDED
#include vapplicationHEADER
#endif

static vstr	   *spam;
static vcolor	   *pink;
static vfont	   *font;
static vimage	   *iroot, *save;
static vrectFloat   bounds;
static vrect	    damage, idamage;


static int handleSpam(vevent *event);
static int handleUnspam(vevent *event);

/*
 * handleSpam is called to put up a graphic at a random location
 * this will need to be taken down later, so handleSpam also
 * posts a future event that will later call handleUnspam
 */
static int handleSpam(vevent *event)
{
    vmatrix    mtx;
    double     scale;
    vrectFloat fdamage;

    /*
     * figure out where the graphic is going to go
     */

    scale = (rand()%1000)/1000.0;

    vmatrixTranslate(vmatrixIdent(), rand()%vwindowGetW(vwindowGetRoot()),
		     rand()%vwindowGetH(vwindowGetRoot()), &mtx);
    vmatrixScale(&mtx, scale, scale, &mtx);
    vmatrixRotate(&mtx, rand()%360, &mtx);

    vmatrixRectTransform(&mtx, &bounds, &fdamage);
    vrectFromFloat(&fdamage, &damage);

    idamage.x = idamage.y = 0;
    idamage.w = damage.w;
    idamage.h = damage.h;

    /*
     * save the original area into an offscreen image for later restoration
     */
    vdrawImageDevice(save);
    vdrawRectImage(iroot, &damage, &idamage);

    /*
     * actually put up the graphic
     */
    vwindowDrawDevice(vwindowGetRoot());
    vdrawConcat(&mtx);
    vdrawSetColor(pink);
    vdrawMoveTo(0, 0);
    vdrawShow(spam);

    veventSetTarget(event, handleUnspam);
    veventPostFuture(event, 0, 200*vtimestampMILLISECOND);

    vwindowSyncEvents();

    /*
     * the event was succesfully handled
     */
    return TRUE;
}

/*
 * handleUnspam is called to erase the graphic previously put up by handlSpam
 */
static int handleUnspam(vevent *event)
{
    /*
     * clear the previous graphic by drawing the original, saved area
     * back over top of the damaged area where the graphic was
     */
    vwindowDrawDevice(vwindowGetRoot());
    vdrawRectImage(save, &idamage, &damage);

    /*
     * set up the next call to handleSpam
     */
    veventSetTarget(event, handleSpam);
    veventPostFuture(event, 0, 500*vtimestampMILLISECOND);

    /*
     * the event was succesfully handled
     */
    return TRUE;
}


int main(int argc, char *argv[])
{
    vevent	*event;
    vrectFixed	 fbounds;
    double	 maxw, maxh;
    int		 max;
    vcolorSpec	 spec;

    spam = vstrCloneScribed(vcharScribeLiteral("Spam"));

    vprefSetArgs(argc, argv);

    vwindowOpen(vwindowGetRoot());

    vcolorInitSpec(&spec);
    vcolorFSetSpecRGB(&spec, 1.0, 0.5, 0.75);
    pink = vcolorInternSpec(&spec);

    font = vwindowDetermineFont(vwindowGetRoot());

    vfontFixStringBounds(font, spam, &fbounds);
    vrectFloatFromFixed(&fbounds, &bounds);

    iroot = vwindowToImage(vwindowGetRoot());

    /*
     * set up an offscreen image big enough to hold the area about to
     * be damaged
     */
    maxw = bounds.w;
    maxh = bounds.h;
    max	 = ceil(sqrt(maxw*maxw+maxh*maxh));
    save = vwindowCreateBufferImage(max, max);

    event = veventCreateClient();

    veventSetTarget(event, handleSpam);
    veventPost(event);
    veventProcess();

    vimageDestroy(iroot);
    vimageDestroy(save);
    vcolorRelease(pink);
    vstrDestroy(spam);

    exit(EXIT_SUCCESS);
    return EXIT_FAILURE;
}


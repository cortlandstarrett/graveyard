/* $Id: splash.c,v 1.3 1993/11/14 01:57:29 chad Exp $
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

#ifndef  vportINCLUDED
#include <vport.h>		/* for v*HEADER */
#endif

#ifndef  vdialogINCLUDED
#include vdialogHEADER
#endif

#ifndef  veventINCLUDED
#include veventHEADER
#endif

#ifndef  vresourceINCLUDED
#include vresourceHEADER
#endif

#ifndef  vobjectINCLUDED
#include vobjectHEADER
#endif

#ifndef  vapplicationINCLUDED
#include vapplicationHEADER
#endif

#include "splash.h"

/*******************************************************************/
/*                  Private functions                              */
/*******************************************************************/

/*********
 *  handler
 *
 *  An event handler to get us going.  This is necessary so the
 *  splash dialog will get drawn properly.
 *
 **********/
static int handler (vevent *event)
{
  vdialog        *splashDialog = NULL;
  splashInitProc  initProc;

  if (event)
    splashDialog = (vdialog *) veventGetClientData(event);
  else
    return(TRUE);

  initProc = (splashInitProc) vdialogGetData(splashDialog);

  if (initProc != NULL)
    initProc(splashDialog);  /* do all application initialization */

  return(TRUE);
}


/*********
 *  splashNotify()
 *
 *  The notification function for the splash dialog.
 *  When the splash window gets an Uniconify STATE event (which will
 *  happen when it is explicitly opened), then cause an immediate update
 *  (to draw the splash dialog) and post the event to go to the handler()
 *  routine to allow for application initialization.
 *
 **********/
static void splashNotify (vdialog *dialog, vevent *event)
{
  int et;

  et = veventGetType (event);
  
  if (et == veventWINDOW_STATE && veventIsOpen (event))
    {
      /* force the splash window to be drawn */
      vwindowInval (vdialogGetWindow (dialog), vwindowINVAL_UPDATE);
      /* clear the event queue */
      vwindowFlushRequests ();
      /* post event to handler() */
      event = veventCreateClient ();
      veventSetClientData (event, dialog);
      veventSetPriority (event, veventPRIORITY_MIN);
      veventSetTarget (event, handler);
      veventPost (event);
    }

  return;
  
}

/*******************************************************************/
/*                  Public functions                              */
/*******************************************************************/


/*********
 * splashdialogCreate()
 *
 * Create the splash dialog by getting it from the resource file.
 *********/
vdialog *splashdialogCreate()
{
  vdialog  *theSplashDialog;

  vresource res =
    vresourceGet(vapplicationGetResources(vapplicationGetCurrent()),
		 vnameInternGlobalLiteral("nameSPLASH_DIALOG"));
  theSplashDialog = vdialogLoad(res);

  return(theSplashDialog);
}



/*********
 *  splash()
 *
 *  Get the splash dialog going. This routine is usually called by the
 *  application's main(). We are given the splashDialog, and the
 *  application's initialization function (proc) to be called while the
 *  splash dialog is visible to the user.
 *
 **********/
void splash(vdialog *splashDialog, splashInitProc proc)
{
  
  /*
   *  Opening a dialog outside of the event loop is a little complicated.
   *  You can't just open the dialog and continue processing since the
   *  dialog manager is event driven.  Instead you need to wait for
   *  notification of the window being uniconified.  When this occurs, you
   *  need to force the window to be drawn, then post an event with a handler
   *  which knows where the application initialization code really is.
   */

  vwindowPlace (vdialogGetWindow (splashDialog), vwindowGetRoot (),
		 vrectPLACE_CENTER, vrectPLACE_CENTER);
  vdialogSetNotify (splashDialog, splashNotify);
  vdialogSetData (splashDialog, (void *) proc);
  vdialogOpen (splashDialog);
  vwindowBlock (vdialogGetWindow(splashDialog)); /* use the hourglass cursor */

}


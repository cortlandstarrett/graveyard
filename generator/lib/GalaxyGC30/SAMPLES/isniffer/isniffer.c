/* $Id: isniffer.c,v 1.6 1997/07/30 14:19:49 gregt Exp $ */
/****************************************************************************
 *                (c) Copyright 1991-1994 Visix Software, Inc.              *
 *                           All rights reserved.                           *
 * The following Sample Code is provided for your reference purposes in     *
 * connection with your use of the Galaxy Application Environment (TM)      *
 * software product which you have licensed from Visix Software, Inc.       *
 * ("Visix"). The Sample code is provided to you without any warranty of any*
 * kind and you agree to be responsible for the use and/or incorporation    *
 * of the Sample Code into any software product you develop. You agree to   *
 * fully and completely indemnify and hold Visix harmless from any and all  *
 * loss, claim, liability or damages with respect to your use of the Sample *
 * Code.                                                                    *
 *                                                                          *
 * Subject to the foregoing, you are permitted to copy, modify, and         *
 * distribute the Sample Code for any purpose, and without fee, provided    *
 * that (i) a copyright notice in the in the form of "Copyright 1992 Visix  *
 * Software Inc., 11440 Commerce Park Drive, Reston, VA  22091. All Rights  *
 * Reserved" appears in all copies, (ii) both the copyright notice and this *
 * permission notice appear in all supporting documentation and (iii) you   *
 * are a valid licensee of The Galaxy Application Environment.              *
 *                                                                          *
 ****************************************************************************
 *                                                                          *
 * Description:                                                             *
 *     Main() module for isniffer application. initializes and shutdowns    *
 *     the program; creates and initializes the global "isnifferApp" data.  *
 *     note we don't provide a complete set of accessors to the global data *
 *     so secondary modules (viewers,snooper,utils,etc.) are expected to    *
 *     directly access the global data fields through isnfGet() <shudder>...*
 *                                                                          *
 * Modification History:                                                    *
 *     o 12-11-93: created for galaxy 2.0 (ssmc)                            *
 *                                                                          *
 * Text Editor Formatting:                                                  *
 *     Symantec: Tab(8), Font(Any Fixed Width)                              *
 *     Emacs: see end of file for info                                      *
 *                                                                          *
 ****************************************************************************
 */

/* for v*HEADER */
#include <vport.h>

/* ANSI headers */
#include vstdioHEADER
#include vstdlibHEADER

/* Galaxy headers */
#ifndef  vstdINCLUDED
#include vstdHEADER
#endif

#ifndef  vdebugINCLUDED
#include vdebugHEADER
#endif

#ifndef  vexINCLUDED
#include vexHEADER
#endif

#ifndef  vmemINCLUDED
#include vmemHEADER
#endif

#ifndef  vrectINCLUDED
#include vrectHEADER
#endif

#ifndef  vcharINCLUDED
#include vcharHEADER
#endif

#ifndef  vstrINCLUDED
#include vstrHEADER
#endif

#ifndef  vnameINCLUDED
#include vnameHEADER
#endif

#ifndef  vdictINCLUDED
#include vdictHEADER
#endif

#ifndef  vkeyINCLUDED
#include vkeyHEADER
#endif

#ifndef  veventINCLUDED
#include veventHEADER
#endif

#ifndef  vfsINCLUDED
#include vfsHEADER
#endif

#ifndef  vresourceINCLUDED
#include vresourceHEADER
#endif

#ifndef  vprefINCLUDED
#include vprefHEADER
#endif

#ifndef  vcommandINCLUDED
#include vcommandHEADER
#endif

#ifndef  vimageINCLUDED
#include vimageHEADER
#endif

#ifndef  vwindowINCLUDED
#include vwindowHEADER
#endif

#ifndef  vapplicationINCLUDED
#include vapplicationHEADER
#endif

#ifndef  vdialogINCLUDED
#include vdialogHEADER
#endif

#ifndef  vnoticeINCLUDED
#include vnoticeHEADER
#endif

#ifndef  vstartupINCLUDED
#include vstartupHEADER
#endif

/* Our headers */
#include "names.h"
#include "geticons.h"
#include "statitem.h"
#include "isnf.h"
#include "utils.h"
#include "com.h"
#include "help.h"
#include "view.h"
#include "snoop.h"



/* Define our debug tag for vdebug manager */
#if vdebugDEBUG
static const char *const _mainTag = "main";
#define vdebugTAG _mainTag
#endif



/*
 *+------------------------------------------------------------------------+
 * private constants, variables, prototypes
 *+------------------------------------------------------------------------+
 */
isnifferApp		gApp= {0};

static void		appInit(void);
static void		appInitSniffRequestControls(void);
static void		appInitCommands(void);
static void		appOpenSniffRequestControls(void);
static void		appQuit(void);
static void		appShutdown(void);
static int		appQuitFromCloseAdornment(vdialog*,vevent*);
static int		appQuitFromCommand(vcommandFunction*,vdict*);


/*
 *+------------------------------------------------------------------------+
 * private: initialization
 *+------------------------------------------------------------------------+
 */

/********
 * appInit initializes the image sniffer application; initializes the
 * global isnifferApp structure. checks for the "tempdir" option (where
 * temporary image store files are kept).
 *
 * -> void 
 * <- void
 *********/
static void
appInit(void)
{
  register isnifferApp	*app= isnfGet();
  vstr			*str;
  vresource		 res;
  const vchar		*v;
  const isnifferPrefs	*prefs;

  appInitNames();

  if (!(v=vprefLoad(appname_Verbose)) || vcharCompare(v,vname_Off)==0)
    vdebugSetAdviceLevel(vdebugLEVEL_OFF);

  vexWITH_HANDLING {
    app->app = vapplicationGetCurrent();
    vapplicationSetData(app->app, app);

    /* load/cache common resources (barfs if can't find any) */
    app->resources = vapplicationGetResources(app->app);
    app->messages  = vresourceGet(app->resources, appname_Messages);
    app->strings   = vresourceGet(app->resources, appname_Strings);
    app->version   = vresourceGetString(app->resources, appname_VersionString);

    res = vresourceGet(app->resources, appname_Icon);
    vapplicationSetIconOwned(app->app, vimageLoad(res));
    str = vresourceGetString(app->resources, appname_Title);
    vapplicationSetTitle(app->app, str);
    vstrDestroy(str);

    res = vresourceGet(app->resources, appname_SnoopDialog); /*force*/
    res = vresourceGet(app->resources, appname_ViewerIcon);
    app->viewerIcon = vimageLoad(res);

    isnfStartupPreferences(app);
    prefs = isnfGetPreferences();
    app->recursive = prefs->recursive;
    app->all = prefs->all;
  }

  /* :-( something in startup died... */
  vexON_EXCEPTION {
    vexPropagate(vexGetModuleStartupClass(), vexMESSAGE, 
		 "Problem locating application resources", vexERRNO, 0,
		 vexNULL);
  }
  vexEND_HANDLING;


  /* load the main sniff-request view; attach toplevel commands */
  appInitSniffRequestControls();
  appInitCommands();

  return;
}




/********
 * appInitSniffRequestControls loads/inits the main sniff
 * requestor window (it's actually a vmainview, which supports MDI (windows),
 * or global menubar and floating palettss(mac), or top-level window
 * with iconview (others).
 *
 * -> void
 * <- void
 *********/
static void
appInitSniffRequestControls(void)
{
  register isnifferApp	*app= isnfGet();
  vresource		 res;

  /* be sure to register our statusbox class -before- loading
   * the main dialogue */
  res = vresourceGet(app->resources, appname_StatusLookImages);
  statusboxStartupManager(res);

  res = vresourceGet(app->resources, appname_SnoopDialog);
  app->requestor = vdialogLoad(res);
  app->object = vwindowGetObject(vdialogGetWindow(app->requestor));
  vdialogSetCloseHook(app->requestor, appQuitFromCloseAdornment);
  vdialogSetData(app->requestor,app);

  /* cache reference to status item */
  app->statusitem = vdialogFindItem(app->requestor, appname_MainStatusBox);
  if (!app->statusitem)
    vexGenerate(vexGetModuleStartupClass(), vexMESSAGE,
		"Missing required items in application's dialog(s)", 
		vexERRNO, 0, vexNULL);

  /* center dialogue on main screen */
  vwindowPlace(vdialogGetWindow(app->requestor), vwindowGetRoot(),
	       vrectPLACE_CENTER, vrectPLACE_CENTER);
  return;
}



/********
 * appInitCommands initializes the toplevel application commands and
 * attaches 'em to the main sniffer requestor dialogue.
 *
 * -> void
 * <- void
 *********/
static void
appInitCommands(void)
{
  register isnifferApp	    *app= isnfGet();
  vcommandFunction	    *com;
  register appCommandSpace  *aspace = &app->cmdspace;

  vexWITH_HANDLING {
    /* attach command space to requestor window since all other 
     * windows follow it (it's da leader) so our space will be
     * included in the ui hierarchy */
    appInitCommandSpaceDescription(vcommandCreateSpace(), aspace);
    vwindowSetSpaceOwned(vdialogGetWindow(app->requestor), aspace->space);

    /* init help, snoopers, and viewers, and add their global commands */
    isnfStartupHelp(app);
    isnfStartupSnooperManager(app);
    isnfStartupPreferencesChooza(app);
    isnfStartupSpinDocktor(app);


    /* add univeral "Quit" command explicitly */
    com = vcommandCreateFunction();
    vcommandSetFunctionIssue(com, appQuitFromCommand);
    appAddUnivFunctionToCommandSpaceDescription(aspace, appname_QuitAct,
                  com, vkeyNULL_STROKE);

    /* finally commit all the dictionaries to our space */
    appCommitCommandSpaceDescription(aspace);
  }

  vexON_EXCEPTION {
    vexPropagate(vexGetModuleStartupClass(), vexMESSAGE, 
		 "Problem initializing application commands", 
		 vexERRNO, 0, vexNULL);
  }
  vexEND_HANDLING;

  return;
}


/********
 * appOpenSniffRequestControls actually opens the sniffer
 * mainview and other controls; separated from init in case we want 
 * to do stuff between loading and opening.
 *
 * -> void
 * <- void
 *********/
static void
appOpenSniffRequestControls(void)
{
  register isnifferApp *app = isnfGet();

  /* open */
  vdialogOpen(app->requestor);

  /* process startup file arguments */
  isnfProcessStartupSnoopRequests(app);
  return;
}


/*
 *+------------------------------------------------------------------------+
 * private: shutdown
 *+------------------------------------------------------------------------+
 */

/********
 * appConfirmQuitWhenBusy is called when user dismisses the quit
 * confirmation notice; application quits if the response was "yes."
 *
 * -> reply, [yes,no,cancel]
 * -> ignored
 * <- void
 *********/
static void
appConfirmQuitWhenBusy(int reply, void *data)
{
  if (reply==responseYES) {
    gApp.busy=0;
    appQuit();
  }
  return;
}



/********
 * appQuit quits the application; if the application is currently
 * blocked (by modal window of some kind) puts up a quit confirmation
 * notice.
 *
 * -> void
 * <- void
 *********/
static void
appQuit(void)
{
  register isnifferApp *app = isnfGet();
  if (app->busy)
    isnfAskUser(msgWantToReallyQuitWhenBusy,vFALSE,appConfirmQuitWhenBusy,
		NULL,NULL);
  else {
    isnfStopProcessingSnoopers(&gApp);
    veventStopProcessing();
    gApp.quitting = vTRUE;
  }
  return;
}



/********
 * appShutdown cleans up the memory used by the snooper application;
 * mostly a noop if not debugging.
 *
 * -> void
 * <- void
 *********/

static void
appShutdownSafe(void)
{
#if vmemBALANCE
  register isnifferApp *app= isnfGet();

  if (app->requestor)
    vdialogDestroy(app->requestor);
  if (app->infoNotice)
    vnoticeDestroy(app->infoNotice);
  if (app->quesNotice) {
    vmemFree((void*)vnoticeGetData(app->quesNotice));
    vnoticeDestroy(app->quesNotice);
  }
  if (app->noticeIcon)
    vimageDestroy(app->noticeIcon);
  if (app->viewerIcon)
    vimageDestroy(app->viewerIcon);
  if (app->status)
    vdialogDestroy(app->status);
  if (app->wholeimage)
    vimageDestroy(app->wholeimage);
  if (app->pieceimage)
    vimageDestroy(app->pieceimage);

  if (app->tempdir)
    vfsDestroyPath(app->tempdir);

  if (app->version)
    vstrDestroy(app->version);
#endif
}

static void
appShutdown(void)
{
  /* save our any preferences changes */
  isnfShutdownPreferences(isnfGet());
  isnfShutdownSnooperManager(isnfGet());

#if vmemBALANCE
  isnfShutdownSpinDocktor(isnfGet());
  appShutdownSafe();
#endif
}




/********
 * appQuitFromCommand is called when user selects "Quit" ui item
 * (menu/button). calls appQuit.
 *
 * -> com,     the quit command
 * -> context, the command's context dictionary
 * <- TRUE
 *********/
static int
appQuitFromCommand(vcommandFunction *com, vdict *context)
{
  appQuit();
  return vTRUE;
}



/********
 * appQuitFromCloseAdornment is called when user selects the window 
 * manager's close adornment (goaway box or system menu). always returns
 * TRUE st we can block closes.
 *
 * -> dialog, the main dialogue
 * -> event,  the event that triggered the close notification
 * <- TRUE
 *********/
static int
appQuitFromCloseAdornment(vdialog *dialog, vevent *event)
{
  appQuit();
  return vTRUE; /* -> let our code do the close */
}



/*
 *+------------------------------------------------------------------------+
 * public: misc
 *+------------------------------------------------------------------------+
 */

/********
 * isnfIsProcessingUserRequests checks if there are still snoops in
 * progress.
 *
 * -> void
 * <- [T/F], TRUE if snooping, else FALSE
 *********/
int
isnfIsProcessingUserRequests(void)
{
  return isnfGetNumberSnoopersProcessing();
}



/*
 *+------------------------------------------------------------------------+
 * main()
 *+------------------------------------------------------------------------+
 */
int 
main(int argc, char **argv)
{
  int	volatile exitcode = EXIT_SUCCESS;

  vexStartup();   /* can't do vexWITH_HANDLING before this! */

  /* :-) */
  vexWITH_HANDLING
    {
      vstartup(argc, argv);
      appInit();
      appOpenSniffRequestControls();
      veventProcess();
      appShutdown();
    }
  /* :-( */
  vexON_EXCEPTION
    {
      vexDumpChain(vdebugGetWarningStream());
      vexClear();
      appShutdownSafe();
      exitcode = EXIT_FAILURE;
    }
  /* 8-| */
  vexEND_HANDLING;

  exit(exitcode);
  return EXIT_FAILURE; /* should never reach */

}


/*
  +-------------------------------------------------------------------------+
   MISC formatting information for emacs in c-mode
  +-------------------------------------------------------------------------+
 */

/*
 * Local Variables:
 * c-indent-level:2
 * c-continued-statement-offset:2
 * c-brace-offset:0
 * c-brace-imaginary-offset:0
 * c-argdecl-indent:5
 * c-label-offset:0
 * c-tab-always-indent:nil
 * End:
 */

/********
 * this function does stuff
 *
 * -> 
 * <- 
 *********/

/* $Id: boxt.c,v 1.3 1996/10/03 19:33:02 alexey Exp $ */
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
 *     This little program tests the statusbox item "statusbox"; item used  *
 *     by the isniff application. it is _not_ a general purpose status item!*
 *                                                                          *
 * Modification History:                                                    *
 *     o 12-11-93: created for galaxy 2.0 (ssmc)                            *
 *                                                                          *
 * Special Usage Notes:                                                     *
 *     o                                                                    *
 *                                                                          *
 * Text Editor Formatting:                                                  *
 *     Symantec: Tab(8), Font(Any Fixed Width)                              *
 *     Emacs: see end of file for info                                      *
 *                                                                          *
 ****************************************************************************
 */

/* For v*HEADER */
#include <vport.h>

/* ANSI headers */
#include vstdioHEADER
#include vstdlibHEADER

/* Galaxy headers */
#include vdebugHEADER
#include vexHEADER
#include vmemHEADER
#include vcharHEADER
#include vstrHEADER
#include vnameHEADER
#include veventHEADER
#include vresourceHEADER
#include vwindowHEADER
#include vcontrolHEADER
#include vbuttonHEADER
#include vtextHEADER
#include vtextitemHEADER
#include vdialogHEADER
#include vapplicationHEADER
#include vstartupHEADER

/* Our includes */
#include "names.h"
#include "statitem.h"


/* Define our debug module for debug manager */
#if vdebugDEBUG
static const char *const _mainTag = "status-item-tester";
#define vdebugTAG _mainTag
#endif


enum {
  NAME_ICON,
  NAME_DIALOG,
  NAME_STATUS_BOX,
  NAME_BEGIN, NAME_INCR, NAME_DECR, NAME_END, 
  NAME_FLASH, NAME_MESSAGE,
  NAME_QUIT,
  NAME_COUNT
};

static const vname *names[NAME_COUNT];
static const char  *literals[NAME_COUNT]= {
  "icon",
  "dialog",
  "box",
  "start", "incr", "decr", "stop", 
  "flash", "message",
  "quit-app"
};

#define name_icon	names[NAME_ICON]
#define name_dialog	names[NAME_DIALOG]
#define name_box	names[NAME_STATUS_BOX]
#define name_start	names[NAME_BEGIN]
#define name_incr	names[NAME_INCR]
#define name_decr	names[NAME_DECR]
#define name_stop	names[NAME_END]
#define name_flash	names[NAME_FLASH]
#define name_message	names[NAME_MESSAGE]
#define name_quit	names[NAME_QUIT]

static vapplication	*app;
static vresource	 resources;
static vdialog		*dialog;
static vtextitem	*textitem;
static vbutton		*startButton, *stopButton, *incrButton, *decrButton;
static vbutton		*flashButton;
static vdialogItem	*box;

static void
initnames(void)
{
  register const vname **name;
  register const char  **scan, **stop;
  name = names;
  scan = literals, stop = scan+NAME_COUNT;
  for (; scan<stop; scan++,name++)
    *name = vnameInternGlobalLiteral(*scan);
  return;
}

static vstr *
getstring(void)

{
  vtext   *text;
  size_t   len;
  vstr    *str;
  text = vtextitemGetTextData(textitem);
  len  = vtextLength(text);
  if (!len) return NULL;
  str  = vstrCreateSized(len + 1);
  vtextitemGetText(textitem, str, len + 1);
  return str;
}

static void
winAcknowledgeClose(vdialog *dialog, vevent *event)
{
  if (veventIsClose(event))
    veventStopProcessing();
  return;
}

static void
graphicStartUsing(vbutton *btn, vevent *event)
{
  statusboxTurnOnGraphicsMode(box);
  vbuttonEnable(incrButton);
  vbuttonEnable(decrButton);
  vbuttonEnable(stopButton);
  vbuttonDisable(btn);
  return;
}

static void
graphicStopUsing(vbutton *btn, vevent *event)
{
  statusboxTurnOffGraphicsMode(box);
  vbuttonDisable(incrButton);
  vbuttonDisable(decrButton);
  vbuttonDisable(btn);
  vbuttonEnable(startButton);
  return;
}

static void
graphicIncr(vbutton *btn, vevent *event)
{
  statusboxUpdateImageCount(box, 1);
  return;
}

static void
graphicDecr(vbutton *btn, vevent *event)
{
  vexWITH_HANDLING
  {
    statusboxUpdateImageCount(box, -1);
  }
  vexON_EXCEPTION
  {
    vwindowBeep();
    vexDumpChain(vdebugGetWarningStream());
    vexClear();
  }
  vexEND_HANDLING;
  return;
}

static void
messageFlash(vbutton *btn, vevent *event)
{
  vstr *str;
  str = getstring();
  if (!str) vwindowBeep();
  else statusboxFlashMessageOwned(box, str);
  return;
}

static void
quitApp(vbutton *btn, vevent *event)
{
  veventStopProcessing();
  return;
}

int 
main(int argc, char **argv)
{
  vresource 	 res;
  vbutton	*btn;
  int		 volatile retcode = EXIT_SUCCESS;
  
  vexStartup();

  vexWITH_HANDLING
    {
      vstartup(argc, argv);

      app = vapplicationGetCurrent();
      resources = vapplicationGetResources(app);
      initnames();
      res = vresourceGet(resources, name_icon);
      vapplicationSetIconOwned(app, vimageLoad(res));

      appInitNames();
      res = vresourceGet(resources, appname_MainStatusBox);
      statusboxStartupManager(res);

      res = vresourceGet(resources, name_dialog);
      dialog = vdialogLoad(res);
      vdialogSetNotify(dialog, winAcknowledgeClose);

      box = vdialogFindItem(dialog, name_box);

      startButton = (vbutton*)vdialogFindItem(dialog, name_start);
      vbuttonSetNotify(startButton, graphicStartUsing);
      incrButton = (vbutton*)vdialogFindItem(dialog, name_incr);
      vbuttonSetNotify(incrButton, graphicIncr);
      decrButton = (vbutton*)vdialogFindItem(dialog, name_decr);
      vbuttonSetNotify(decrButton, graphicDecr);
      stopButton = (vbutton*)vdialogFindItem(dialog, name_stop);
      vbuttonSetNotify(stopButton, graphicStopUsing);

      flashButton = (vbutton*)vdialogFindItem(dialog, name_flash);
      vbuttonSetNotify(flashButton, messageFlash);
      textitem = (vtextitem*)vdialogFindItem(dialog, name_message);

      btn = (vbutton*)vdialogFindItem(dialog, name_quit);
      vbuttonSetNotify(btn, quitApp);

      vbuttonDisable(incrButton);
      vbuttonDisable(decrButton);
      vbuttonDisable(stopButton);
      vbuttonEnable(startButton);

      vwindowPlace(vdialogGetWindow(dialog), vwindowGetRoot(),
		   vrectPLACE_CENTER, vrectPLACE_CENTER);
      vdialogOpen(dialog);

      veventProcess();
      vdialogDestroy(dialog);
    }
  vexON_EXCEPTION
    {
      vdebugBE(vexDumpChain(vdebugGetWarningStream()));
      retcode = EXIT_FAILURE;
      vexClear();
    }
  vexEND_HANDLING;


  exit(retcode);
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


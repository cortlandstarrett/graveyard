/* $Id: help.c,v 1.1 1997/09/25 19:50:10 shawn Exp $ */
/*
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
 * copyright notice in the in the form of "Copyright 1993-97 Visix Software,
 * Inc., 11440 Commerce Park Drive, Reston, VA  22091. All Rights Reserved" 
 * appears in all copies, (ii) both the copyright notice and this permission 
 * notice appear in supporting documentation and (iii) you are a valid 
 * licensee of Galaxy Application Environment.
 */

/****************************************************************************
 * Source File, help.c
 *
 * Managers Illustrated:
 *     vhelp (new classes introduced in Galaxy 3.0)
 *
 * Description Of Sample:
 *     This sample demonstrates how to use the help features intoduced
 *     in Galaxy 3.0.  These include tooltips, status help, and 
 *     HTML context sensitive help.
 *
 *     Users have to do very little to make this work.  Cool, eh?
 *     I'll discuss each type of help we're using:
 *
 *     Tooltips (Phrase)
 *       Tooltips are one way of displaying "phrase" help, so named
 *       because it is used to display very short information.
 *       The help locator (vhelptextlocator) will search the command
 *       spaces and the top level of the application resource file
 *       for dictionaries named "Phrase" (you can change this name
 *       if you want, see vhelptextlocator).  These dictionaries
 *       should contain mappings between object tags and the text to
 *       be displayed.
 *
 *       In this sample, the tooltar button tooltip text is stored
 *       in the top level of the application resource file.  Check
 *       out the "Phrase" dictionary there.  Note that the "ContainerItem"
 *       string maps has an empty value.  This is a handy way of 
 *       clearing the displayed text.
 *
 *       The "Open Confirm" button's tooltip is stored in a command
 *       space.  See _setConfirmButtonHelpText below.
 * 
 *     Status
 *       Status help is normally displayed in a vstatusbar's default
 *       item.  Status help is announced via an observer mechanism from
 *       a vhelpstatus help display so other items can easily observe
 *       status help announcements.
 *  
 * 	 Like phrase help, help text can be located either in command
 *       space dictionaries or in the application resource file.
 *       Check out the "Status" dictionary in the resource file and
 *       the function _setConfirmButtonHelpText below.
 * 
 *     HTML (context-sensitive)
 *       HTML documentation is displayed in an HTML browser.  This is
 *	 either Netscape Navigator or MS Internet Explorer.  The
 *	 documentation is located in a single directory (named "doc"
 *	 by default).  In this sample, we change the name to avoid
 *	 the application looking in <GALAXYHOME>/doc.  HTML help,
 *       like other forms of hypertext help in Galaxy, uses help
 *       contexts.  Help contexts are formed by appending the tags
 *       of objects relative to how they are arranged in the UI
 *       hierarchy.  Check out the documentation on vhelphtmllocator
 *       for more information on help contexts.  By default, a text file 
 *       is used to specify mappings between help contexts and URL's.
 *       This file's name is helpmap.txt.   It's in the helpdoc directory.
 *	 Check it out, too, for more fun info.
 *
 * History:
 *     Written for 3.0 release.
 ****************************************************************************/

#ifndef  vportINCLUDED
#include <vport.h>		/* for v*HEADER */
#endif

#ifndef  vstdlibINCLUDED
#include vstdlibHEADER
#endif

#ifndef  vprefINCLUDED
#include vprefHEADER
#endif

#ifndef  vapplicationINCLUDED
#include vapplicationHEADER
#endif

#ifndef  vconfirmINCLUDED
#include vconfirmHEADER
#endif

#ifndef  vcontainerINCLUDED
#include vcontainerHEADER
#endif

#ifndef  vbuttonINCLUDED
#include vbuttonHEADER
#endif

#ifndef  vmenubarINCLUDED
#include vmenubarHEADER
#endif

#ifndef  vtextitemINCLUDED
#include vtextitemHEADER
#endif

#ifndef  vtoolbarINCLUDED
#include vtoolbarHEADER
#endif

#ifndef  vtoolbuttonINCLUDED
#include vtoolbuttonHEADER
#endif

#ifndef  vtoolbarSeparatorINCLUDED
#include vtoolbarSeparatorHEADER
#endif

#ifndef  vstatusbarINCLUDED
#include vstatusbarHEADER
#endif

#ifndef  vhelpINCLUDED
#include vhelpHEADER
#endif

#ifndef  vhelptextINCLUDED
#include vhelptextHEADER
#endif

#ifndef  vhelpregistryINCLUDED
#include vhelpregistryHEADER
#endif

#ifndef  vhelphtmllocatorINCLUDED
#include vhelphtmllocatorHEADER
#endif

/*
 * Globals, for simiplicity in this sample.
 */
vconfirm	*confirm;
vdict		*phraseDict;
vdict		*statusDict;

/*
 * _setConfirmButtonHelpText
 *
 * Setup the help text (both phrase and status) for the button in
 * this container.
 *
 * Putting help text information in a command space is spiffy because
 * we can easily change it at run-time (as the status of things change,
 * etc.).
 */
static void _setConfirmButtonHelpText(vcontainer *container)
{
  vcommandSpace	*space;

  vhelptextTemplate	phraseHelp[] =
  {
    {"Open Confirm",	"Open Confirm (boy, that's helpful)"}
  };

  vhelptextTemplate	statusHelp[] =
  {
    {"Open Confirm",	"Open a confirm dialog that's got "\
                        "some context sensitive help."}
  };

  phraseDict = vhelptextCreateDictFromTemplates(phraseHelp,
				 sizeof(phraseHelp)/sizeof(vhelptextTemplate));
  statusDict = vhelptextCreateDictFromTemplates(statusHelp,
				sizeof(statusHelp)/sizeof(vhelptextTemplate));

  space = vcommandCreateSpace();

  vcommandAddSpaceDictOwned(space, vnameInternGlobalLiteral("Phrase"), 
			    phraseDict);
  vcommandAddSpaceDictOwned(space, vnameInternGlobalLiteral("Status"),
			    statusDict);

  vdialogSetItemSpaceOwned(vcontainerGetItem(container), space);
} /* _setConfirmButtonHelpText */

/*
 * _freeConfirmButtonHelpText
 *
 * The dictionaries in which the help text is stored will be destroyed
 * automatically but we still need to release the contents of the 
 * dictionaries.
 */
static void _freeConfirmButtonHelpText(void)
{
  vhelptextClearDict(phraseDict);
  vhelptextClearDict(statusDict);
} /* _freeConfirmButtonHelpText */

/*
 * _buttonNotify
 *
 * Shutdown when the time comes.
 */
static void _buttonNotify(vbutton *button, vevent *event)
{
  vconfirmOpen(confirm);
} /* _buttonNotify */

/*
 * _dialogNotify
 *
 * Shutdown when the time comes.
 */
static void _dialogNotify(vdialog *dialog, vevent *event)
{
  if (veventIsClose(event))
  {
    veventStopProcessing();
  }
} /* _dialogNotify */

int main(short argc, char **argv)
{
  vresource		 resource;
  vdialog     		*dialog;
  vcontainer		*container;
  vbutton		*button;
  vhelpobject		*helpobject;
  vhelphtmllocator	*helplocator;

  /*
   * Kick off.
   */
  vprefSetArgs(argc, argv);

  /*
   *  Initialize proper classes.
   */
  vconfirmStartup();
  vtoolbarStartup();
  vtoolbuttonStartup();
  vtoolbarSeparatorStartup();
  vstatusbarStartup();
  vbuttonStartup();
  vmenubarStartup();
  vtextitemStartup();

  /*
   * Initialize the help classes that we will be using.
   * This also creates default instances of the appropriate help objects.
   */
  vhelpStartupTooltip();
  vhelpStartupStatus();
  vhelpStartupDefaultHTML();

  /*
   * Make an alteration to the default help object implementing 
   * hypertext (HTML) help.  This sample might look in Galaxy's
   * "doc" directory (the help locator will search <GALAXYHOME>/doc) 
   * so we'll give it a different directory name. 
   */
  helpobject = vhelpregistrySearch(vhelpregistryGetGlobal(), vname_Hypertext);
  helplocator = (vhelphtmllocator *)vhelpobjectGetLocator(helpobject);
  vhelphtmllocatorSetDocDirectoryNameScribed(helplocator, 
					     vcharScribeLiteral("helpdoc"));

  resource = vapplicationGetResources(vapplicationGetCurrent());
  dialog = vdialogLoad(vresourceGet(resource, 
				    vnameInternGlobalLiteral("Dialog")));
  vdialogSetNotify(dialog, _dialogNotify);

  /*
   * Get at the stuff in the dialog.
   */
  container = (vcontainer *) vdialogFindItem(dialog, 
				    vnameInternGlobalLiteral("ContainerItem"));

  button = (vbutton *) vcontainerFindItem(container,
				     vnameInternGlobalLiteral("Open Confirm"));
  vbuttonSetNotify(button, _buttonNotify);

  /*
   * Setup some additional help text.
   */
  _setConfirmButtonHelpText(container);

  /*
   * Turn on motion events.
   * This will activate help reguests for phrase (tooltip) and
   * status help.
   */
  vwindowSetMotion(vdialogGetWindow(dialog), TRUE);

  confirm = vconfirmLoad(vresourceGet(resource, 
				   vnameInternGlobalLiteral("ConfirmDialog")));
  
  /*
   * Make the confirm a follower of the dialog. 
   * This will change it's fully qualified help context.
   */
  vwindowSetLeader(vconfirmGetWindow(confirm), vdialogGetWindow(dialog));

  vdialogOpen(dialog);

  /*
   * Start event loop.
   */
  veventProcess();

  /*
   * Clean up.
   * First, free the help text we put in command spaces.
   */
  _freeConfirmButtonHelpText();
  vdialogDestroy(dialog);
  vconfirmDestroy(confirm);

  exit(EXIT_SUCCESS);
  return(EXIT_FAILURE);
} /* main */

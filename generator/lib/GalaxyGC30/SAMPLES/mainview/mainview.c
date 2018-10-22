/* $Id: mainview.c,v 1.3 1995/02/28 23:04:17 gregt Exp $
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
 * executable:    mainview or mainview.exe
 * source files:  mainview.c
 * resource file: mainview.vr
 *
 * managers illustrated: vmainview Manager
 *
 * This program illustrates how to quickly get started using the vmainview
 * module. It loads a single window (we'll call it the "main" window) and
 * attaches two other windows (called "children" windows).
 * 
 * To end the demo, select "Quit" from the main dialog's "FMX" menu or
 * just close the main dialog's window
 *
 ****************************************************************************/


#include <vport.h>		/* for v*HEADER */
#include vstdlibHEADER		/* for EXIT_* */
#include vnameHEADER
#include vrectHEADER
#include vresourceHEADER
#include veventHEADER
#include vapplicationHEADER
#include vwindowHEADER
#include vmenuHEADER
#include vdialogHEADER
#include vmenubarHEADER
#include vmainviewHEADER
#include vstartupHEADER


/*
 * Useful macros
 */
#define TAG(x)           vnameInternGlobalLiteral(x)
#define APP_RESOURCES()  vapplicationGetResources(vapplicationGetCurrent())

/*
 * For position on screen
 */
#define CENTER_WIN(d)	 vwindowPlace(vdialogGetWindow(d), vwindowGetRoot(),\
				      vrectPLACE_CENTER, vrectPLACE_CENTER)
#if (!vportMS_WINDOWS)
#define STACK_WINS(v,p,c1,c2)  \
  { vwindowPlace(vdialogGetWindow(c1),vdialogGetWindow(p),\
	 vrectPLACE_INSET|vrectPLACE_LEFT, vrectPLACE_INSET|vrectPLACE_TOP); \
    vwindowPlace(vdialogGetWindow(c2),vdialogGetWindow(c1),\
	 vrectPLACE_INSET|vrectPLACE_LEFT, vrectPLACE_INSET|vrectPLACE_TOP);}
#else
#define STACK_WINS(v,p,c1,c2)	\
  vmainviewCascade(v)
#endif



/*
 * HandleQuit - stop the program.
 */
static void HandleQuit(vmenuItem *mitem, vevent *event)
{
  veventStopProcessing();
}

/*
 * HandleClose - stop the program if close
 */
static void HandleClose(vdialog *dialog, vevent *event)
{
  if (veventGetType(event) == veventWINDOW_STATE && veventIsClose(event))
    veventStopProcessing();
}

/*
 * HandleChildClose - handle close event for childs windows
 */
static void HandleChildClose(vdialog *dialog, vevent *event)
{
  vmainview	*view;

  if (veventGetType(event) == veventWINDOW_STATE && veventIsClose (event))
    {
      view = (vmainview *)vdialogGetData(dialog);
      vmainviewRemoveWindow(view, vdialogGetWindow(dialog));
    }
}

/*
 * HandleRemove - removes a child window
 */
static void HandleRemove(vmenuItem *mitem, vevent *event)
{
  vdialog 	*child;
  vmainview	*view;

  view = (vmainview*)vmenuGetItemData(mitem);
  if (view)
    {
      child = (vdialog*)vmenuGetData(vmenuDetermineItemMenu(mitem));
      vdialogClose(child);
      vmainviewRemoveWindow(view, vdialogGetWindow(child)); 
    }
}

/*
 * SetItemNotify - sets up a menu item's notify function
 */
static void SetItemNotify(vmainview *view, vdialog *dialog, 
			  const char *menuId, const char *mitemId, 
			  vmenuItemNoteProc notify)
{
  vmenubar	*menubar;
  vmenu		*menu;
  vmenuItem	*mitem;

  menubar = (vmenubar*)vdialogFindItem(dialog, TAG("Menu Bar"));
  menu    = vmenubarFindMenu(menubar, TAG(menuId));
  vmenuSetData(menu, dialog);

  mitem   = vmenuFindItem(menu, TAG(mitemId));
  vmenuSetItemData(mitem, view);
  vmenuSetItemNotify(mitem, notify);
}



/*
 * main() - create a main window with 2 child windows.
 */
int
main(int argc, char *argv[])
{
  vresource             res;
  vdialog              *dialog, *child1, *child2;
  vdialogItem          *ditem;
  vmainview            *view;


  /*
   * Initialize galaxy runtime environment
   */
  vstartup(argc, argv);
  

  /*
   * Load the main dialog; make it the "main" window in 
   * galaxy's eyes.
   */
  res        = vresourceGet(APP_RESOURCES(), TAG("frame"));
  dialog     = vdialogLoad(res);
  vwindowAddStyle(vdialogGetWindow(dialog), vwindowSTYLE_MAIN);


  /*
   * Attach a "vmainview" to the main window
   */
  view  = vmainviewCreate();
  ditem = vdialogFindItem(dialog, TAG("dummy"));
  vdialogSetItemRect(vmainviewGetItem(view), vdialogGetItemRect(ditem));
  vdialogSetItemListItemAt(vdialogGetItemList(dialog), 
			   vdialogGetItemIndex(dialog, ditem),
			   vmainviewGetItem(view));
  vdialogDestroyItem(ditem);


  /*
   * For "Quit" and "Close"
   */
  SetItemNotify(view, dialog, "FMENUX", "Quit", HandleQuit);
  vdialogSetNotify(dialog, HandleClose);


  /*
   * Attach child #1 to main window
   */
  res    = vresourceGet(APP_RESOURCES(), TAG("child1"));
  child1 = vdialogLoad(res);
  SetItemNotify(view, child1, "MENU1", "CloseChild", HandleRemove);
  vmainviewAddWindow(view, vdialogGetWindow(child1));
  vdialogSetNotify(child1, HandleChildClose);
  vdialogSetData(child1, view);

  /*
   * Attach child #2 to main window
   */
  res    = vresourceGet(APP_RESOURCES(), TAG("child2"));
  child2 = vdialogLoad(res);
  SetItemNotify(view, child2, "MENUA", "CloseChild", HandleRemove);
  vmainviewAddWindow(view, vdialogGetWindow(child2));
  vdialogSetNotify(child2, HandleChildClose);
  vdialogSetData(child2, view);

  
  /*
   * Open all the windows (main and 2 children)
   */
  CENTER_WIN(dialog);
  STACK_WINS(view, dialog, child1, child2);  
  vdialogOpen(dialog);
  vdialogOpen(child1);
  vdialogOpen(child2);

  /*
   * Main event loop
   */
  veventProcess();


  /*
   * Cleanup
   */
  if (vdialogIsOpen(child1))
    {
      vdialogClose(child1);
      vmainviewRemoveWindow(view, vdialogGetWindow(child1));
    }
  vdialogDestroy(child1);
  
  if (vdialogIsOpen(child2))
    {
      vdialogClose(child2);
      vmainviewRemoveWindow(view, vdialogGetWindow(child2));
    }
  vdialogDestroy(child2);

  vdialogDestroy(dialog);


  /*
   * Bye
   */
  exit(EXIT_SUCCESS);
  return EXIT_FAILURE; /* never reached */
}

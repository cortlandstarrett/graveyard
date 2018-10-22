/* $Id: xruntest.c,v 1.4 1997/11/17 18:32:56 gary Exp $ */

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
 * copyright notice in the in the form of "Copyright 1992 Visix Software Inc.,
 * 11440 Commerce Park Drive, Reston, VA  22091. All Rights Reserved" appears
 * in all copies, (ii) both the copyright notice and this permission notice
 * appear in supporting documentation and (iii) you are a valid licensee of
 * Galaxy Application Environment.
 */

/*
 * xruntest - XRunner/WinRunner integration sample - see readme file for
 * full description.
 * Important note: don't forget to specify a testing library preference
 * or else the sample won't do Context Sensitive recording.  It is most
 * convenient to specify this on the command line, such as:
 *
 * xruntest -vtestlib vmicrun1d.dll
 *
 * where "vtestlib" is the name of the Galaxy preference, and the following
 * argument is the desired DLL (shared object, on Unix) to test with
 * (currently only one testing library, the WinRunner/XRunner integration is
 * supported, in both debug and non-debug flavors).  Note that this DLL is
 * loaded as the program is running, so the linker doesn't need to resolve
 * any references to it when building the sample.  Also, as a result of this
 * scheme, you may leave your call to vtestStartup() in your code, even when
 * not testing.
 */

#include <vport.h>
#ifndef vapplicationINCLUDED
#include vapplicationHEADER
#endif

#ifndef vbuttonINCLUDED
#include vbuttonHEADER
#endif

#ifndef vcontainerINCLUDED
#include vcontainerHEADER
#endif

#ifndef vlistitemINCLUDED
#include vlistitemHEADER
#endif

#ifndef vmenubarINCLUDED
#include vmenubarHEADER
#endif

#ifndef vnotebookINCLUDED
#include vnotebookHEADER
#endif

#ifndef vspinnerINCLUDED
#include vspinnerHEADER
#endif

#ifndef vstartupINCLUDED
#include vstartupHEADER
#endif

#ifndef vstdlibINCLUDED
#include vstdlibHEADER
#endif

#ifndef vtestINCLUDED
#include vtestHEADER
#endif

#ifndef vtoolbarINCLUDED
#include vtoolbarHEADER
#endif

#ifndef vtoolbuttonINCLUDED
#include vtoolbuttonHEADER
#endif

#ifndef vtreeINCLUDED
#include vtreeHEADER
#endif

#ifndef vtreelistINCLUDED
#include vtreelistHEADER
#endif

#define TAG(s) vnameInternGlobalLiteral(s)
#define appResources() vapplicationGetResources(vapplicationGetCurrent())

static void myDialNotify(vdialog *dialog, vevent *event)
{
  if (veventIsClose(event))
    veventStopProcessing();
  return;
}

void quitNotify(vmenuItem *item, vevent *event)
{
  veventStopProcessing();
  return;
}

vtreelistTree *_buildSampleTree(void)
{
  vtreelistTree	*sampleTree,
  		*tree,
  		*childTree,
  		*childTree2;

  sampleTree = vtreelistCreateTree();
  vtreelistSetTreeTitleScribed(sampleTree,
      vcharScribeLiteral("All My Children"));

  tree = vtreelistCreateTree();
  vtreelistSetTreeTitleScribed(tree, vcharScribeLiteral("Naughty Children"));
  childTree = vtreelistCreateTree();
  vtreelistSetTreeTitleScribed(childTree, vcharScribeLiteral("Billy"));
  vtreelistSetTreeExpandable(childTree, vFALSE);
  vtreelistAppendTreeChild(tree, childTree);
  childTree = vtreelistCreateTree();
  vtreelistSetTreeTitleScribed(childTree, vcharScribeLiteral("Suzy"));
  vtreelistSetTreeExpandable(childTree, vFALSE);
  vtreelistAppendTreeChild(tree, childTree);
  childTree = vtreelistCreateTree();
  vtreelistSetTreeTitleScribed(childTree,
      vcharScribeLiteral("Really Bad Children"));
  vtreelistAppendTreeChild(tree, childTree);
  childTree2 = vtreelistCreateTree();
  vtreelistSetTreeTitleScribed(childTree2, vcharScribeLiteral("Stinky"));
  vtreelistSetTreeExpandable(childTree2, vFALSE);
  vtreelistAppendTreeChild(childTree, childTree2);
  vtreelistAppendTreeChild(sampleTree, tree);

  tree = vtreelistCreateTree();
  vtreelistSetTreeTitleScribed(tree, vcharScribeLiteral("Polite Children"));
  childTree = vtreelistCreateTree();
  vtreelistSetTreeTitleScribed(childTree, vcharScribeLiteral("Harold"));
  vtreelistSetTreeExpandable(childTree, vFALSE);
  vtreelistAppendTreeChild(tree, childTree);
  childTree = vtreelistCreateTree();
  vtreelistSetTreeTitleScribed(childTree, vcharScribeLiteral("Prissy"));
  vtreelistSetTreeExpandable(childTree, vFALSE);
  vtreelistAppendTreeChild(tree, childTree);
  vtreelistAppendTreeChild(sampleTree, tree);

  return sampleTree;
}

int main(int argc, char *argv[])
{
  vresource	resource;
  vdialog	*dialog;
  vmenubar	*menuBar;
  vmenu		*fileMenu;
  vmenuItem	*quitItem;
  vnotebook	*notebook;
  vcontainer	*container;
  vtreelist	*treeList;

  vstartup(argc, argv);

  /*
   * startup for the Galaxy connection with mic_if for WinRunner/XRunner
   */
  vtestStartup();
 
  resource = vresourceGet(appResources(), TAG("Dialog"));
  dialog = vdialogLoad(resource);
  vdialogSetNotify(dialog, myDialNotify);

  menuBar = (vmenubar *) vdialogFindItem(dialog, TAG("Menu Bar"));
  fileMenu = (vmenu *) vmenubarFindMenu(menuBar, TAG("FileMenu"));
  quitItem = vmenuFindItem(fileMenu, TAG("Quit"));
  vmenuSetItemNotify(quitItem, quitNotify);
  notebook = (vnotebook *) vdialogFindItem(dialog, TAG("Notebook"));
  container = vnotebookGetPageContainer(vnotebookGetPageAt(notebook, 1));
  treeList = (vtreelist *) vcontainerFindItem(container, TAG("TreeList"));
  vtreelistSetTreeOwned(treeList, _buildSampleTree());

  vdialogOpen(dialog);
  veventProcess();

  vdialogDestroy(dialog);
  exit(EXIT_SUCCESS);
  return 0;
}




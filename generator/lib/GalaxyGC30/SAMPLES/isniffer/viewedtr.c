/* $Id: viewedtr.c,v 1.1 1994/08/19 00:09:06 simone Exp $ */
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
 *                       viewer image editor routines                       *
 *                                                                          *
 ****************************************************************************
 */

/* for v*HEADER */
#include <vport.h>

/* ANSI headers */
#include vstdioHEADER
#include vstdlibHEADER

/* Galaxy headers */
#include vdebugHEADER
#include vexHEADER
#include vcharHEADER
#include vnameHEADER
#include vdictHEADER
#include vfsHEADER
#include vresourceHEADER
#include veventHEADER
#include vobjectHEADER
#include vwindowHEADER
#include vdialogHEADER
#include viconviewHEADER
#include vapplicationHEADER
#include vimageedtrHEADER

/* Our headers */
#include "tstack.h"
#include "tarray.h"
#include "iman.h"
#include "names.h"
#include "isnf.h"
#include "utils.h"
#include "view.h"
#include "viewpriv.h"


/* Define our debug tag for vdebug manager */
#if vdebugDEBUG
static const char *const _editedtrTag = "viewer-image-editor";
#define vdebugTAG _editedtrTag
#endif


/*
 *+------------------------------------------------------------------------+
 * private constants, variables, prototypes
 *+------------------------------------------------------------------------+
 */


#define edtrGetDialog(e) (vimageedtrGetDialog(e))
#define edtrGetWindow(e) (vdialogGetWindow(vimageedtrGetDialog(e)))
#define edtrGetInfo(e)	 ((edtrInfo*)vimageedtrGetData(e))

typedef struct edtrInfo {
  viewer	*view;
  viconviewIcon	*icon;
}edtrInfo;


/********
 * edtrPlace
 *
 * ->
 * <-
 ********/
#define edtrPlace(_view, _edtr) \
  vwindowPlace(edtrGetWindow(_edtr), viewerGetWindow(_view), \
	       vrectPLACE_LEFT|vrectPLACE_INSET, \
	       vrectPLACE_TOP|vrectPLACE_INSET)

/********
 * edtrAskUser
 *
 * ->
 * <-
 ********/

static const vname *
edtrAskUserIfSaveChanges(vimageedtr *edtr, int wantCancel)
{
  register vnotice 	*notice;
  vstr			*str;
  vwindow		*w;
  const vname		*response;

  notice = vnoticeCreate();
  vnoticeSetCaution(notice, vTRUE);
  vnoticeSetCancel(notice, wantCancel);

  str = isnfMsgFrom(msgWantToSaveImageChanges);
  vnoticeSetTextScribed(notice, vstrScribe(str));

  str = isnfStrFrom(strSaveImageNoticeTitle);
  vnoticeSetTitleScribed(notice, vstrScribe(str));

  w = edtrGetWindow(edtr);
  if (!vwindowIsVisible(w))
    vwindowUniconify(w);
  vwindowRaise(w);
  vwindowPlace(vnoticeGetWindow(notice), w, 
	       vrectPLACE_CENTER, vrectPLACE_CENTER);

  isnfBlock(vnoticeGetDialog(notice));
  response = vnoticeProcess(notice);
  vnoticeDestroy(notice);
  isnfUnBlock();

  return response;
}


/********
 * edtrSetNewImage
 *
 * ->
 * <- void
 ********/
static void
edtrSetNewImage(vimageedtr *edtr, vimage *newimage)
{
  register edtrInfo *info = edtrGetInfo(edtr);

  vimageedtrSetImage(edtr, NULL);
  viewerCommitUndoables(info->view);
  vieweritemAcceptChangedImage
    (info->view, viewerGetIconItem(info->icon), newimage);
  viewerUpdateDirtyDependentInterface(info->view);
  viewerUpdateUndoInterface(info->view);
}


/********
 * edtrAcceptChanges is called then the image editor closes. this 
 * is not a hook routine so we can't prevent the editor from closing.
 * if we're not quitting, ask user if any changes should be saved.
 *
 * -> edtr,
 * -> image, 
 * <- void
 ********/
static void
edtrAcceptChanges(vimageedtr *edtr, vimage *newimage)
{
  if (newimage) {
    edtrInfo   *info;
    int		nukeIt = vTRUE;

    info = edtrGetInfo(edtr);

    if (!isnfIsQuitting() && info && info->view && info->icon)
      if (edtrAskUserIfSaveChanges(edtr, vFALSE)==vname_Ok) {
	edtrSetNewImage(edtr, newimage);
	nukeIt = vFALSE;
      }

    if (nukeIt) {
      vimageedtrSetImage(edtr, NULL);
      vimageDestroy(newimage);
    }

    if (info) {
      info->view = NULL;
      info->icon = NULL;
    }
  }
}


/********
 * edtrMake
 *
 * ->
 * <-
 ********/
static vimageedtr*
edtrMake(void)
{
  vimageedtr	*edtr;
  edtrInfo	*data;

  edtr = vimageedtrCreate();
  isnfGet()->imageEditor = edtr;

  vimageedtrSetApply(edtr, edtrAcceptChanges);

  vmenubarSetLocal(vimageedtrGetMenuBar(edtr), vTRUE);
  vdialogSetTitleScribed(vimageedtrGetDialog(edtr), 
			 vstrScribe(isnfStrFrom(strImageEditorTitle)));
  vwindowSetLeader(edtrGetWindow(edtr), 
		   vdialogGetWindow(isnfGet()->requestor));

  data = (edtrInfo*)vmemAlloc(sizeof(edtrInfo));
  data->view = NULL;
  data->icon = NULL;
  vimageedtrSetData(edtr, data);

  return edtr;
}


/********
 * viewerCommitImageEditor
 *
 * ->
 * <-
 ********/
void
viewerCommitImageEditor(viewer *view, vieweritem *item)
{
  vimageedtr 	*edtr = isnfGet()->imageEditor;
  edtrInfo	*info;
  vbool		 commit;

  /* If we're open and editing, just nuke the image and 
   * close editor */

  if (edtr && vwindowIsOpen(edtrGetWindow(edtr))) {
    info = edtrGetInfo(edtr);

    commit = vFALSE;
    if (!item)
      commit = (info->view==view);
    else
      commit = (viewerGetIconItem(info->icon)==item);

    if (commit) {
      vimage *img = vimageedtrGetImage(edtr);
      vimageedtrSetImage(edtr, NULL);
      info->icon = NULL;
      info->view = NULL;
      if (img)
	vimageDestroy(img);
      vimageedtrClose(edtr);
      if (item)
	item->editing = vFALSE;
    }
  }
}


/********
 * viewerShutdownImageEditor
 *
 * -> void
 * <- void
 ********/
void
viewerShutdownImageEditor(void)
{
  vimageedtr *edtr = isnfGet()->imageEditor;
  vimage     *img;
  edtrInfo   *info;

  if (edtr) {
    img = vimageedtrGetImage(edtr);
    if (img) {
      vimageedtrSetImage(edtr, NULL);
      vimageDestroy(img);
    }
    info = edtrGetInfo(edtr);
    vmemFree((void*)info);
    vimageedtrSetData(edtr, NULL);
    vimageedtrDestroy(edtr);

    isnfGet()->imageEditor = NULL;
  }
}


/********
 * viewerOpenImageEditor opens the image editor for the given icon item's
 * image (will prompt user for save change if something else currently
 * being edited).
 *
 * -> view, the viewer
 * -> icon, the icon to edit
 * <- void
 *********/
void
viewerOpenImageEditor(viewer *view, viconviewIcon *icon)
{
  vimageedtr	*edtr;
  vbool		 open;
  vwindow	*w;
  vieweritem	*item;
  edtrInfo	*info;
  vimage 	*img;

  vdebugTraceEnter(viewerOpenImageEditor);
  vdebugIF(!icon, vexGenerate(vexGetArgNullClass(), vexMESSAGE,
           "open image editor: NULL icon argument!", vexERRNO, 0,
           vexNULL));

  /* we're busy */
  isnfBlock(NULL);
  isnfInformUserByMessageBoxImmediately(msgOpeningImageEditor);


  /* create image editor is this is first time used */
  edtr = isnfGet()->imageEditor;
  if (!edtr) {
    edtr = edtrMake();
    info = edtrGetInfo(edtr);
    open = vFALSE;
  }


  /* else ask user whether to save any changes to current
   * image */
  else
  if ((open=vwindowIsOpen((w=edtrGetWindow(edtr))))) {
    const vname *act;

    /* same -> do nuthin but make sure visible */
    info = edtrGetInfo(edtr);
    if (info->icon==icon) {
      if (!vwindowIsVisible(w))
	vwindowUniconify(w);
      vwindowRaise(w);
      goto bye;
    }

    vdebugIF(!info->icon, vexGenerate(vexGetValueNullClass(), vexMESSAGE,
            "open image editor: editor open w/o associated item!?",
            vexERRNO, 0, vexNULL));
    item = viewerGetIconItem(info->icon);

    /* whaddaya wanna do? */
    img = vimageedtrGetImage(edtr);
    act = edtrAskUserIfSaveChanges(edtr, vTRUE);

    if (act==vname_Cancel)
      goto bye;
    else
    if (act==vname_Ok) {
      edtrSetNewImage(edtr, img);
    }
    /* (act==vname_No) */
    else {
      vimageedtrSetImage(edtr, NULL);
      vimageDestroy(img);
    }

    info->icon    = NULL;
    info->view    = NULL;
    item->editing = vFALSE;
  }
  else
    info = edtrGetInfo(edtr);


  /* Update the image we're editing */
  item = viewerGetIconItem(icon);
  if (!item->loaded)
    viewerLoadItem(view, icon);
  img = vimageClone(item->sniffed);
  vimageedtrSetImage(edtr, img);

  info->view = view;
  info->icon = icon;


  /* Open the editor or make frontmost if already open */
  edtrPlace(view, edtr);
  if (!open)
    vimageedtrOpen(edtr);

  bye:
  isnfUnBlock();
  vdebugTraceLeave();
}





/*
  +-------------------------------------------------------------------------+
   formatting information for emacs in c-mode
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


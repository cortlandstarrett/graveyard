/* $Id: viewedit.c,v 1.3 1997/07/10 20:48:31 gregt Exp $ */
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
 *                            viewer edit commands                          *
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
#include vmemHEADER
#include vcharHEADER
#include vstrHEADER
#include vnameHEADER
#include vdictHEADER
#include vfsHEADER
#include vresourceHEADER
#include veventHEADER
#include vobjectHEADER
#include vclassHEADER
#include vnumHEADER
#include vcommandHEADER
#include vwindowHEADER
#include vmenuHEADER
#include vdialogHEADER
#include vundoHEADER
#include vdomainHEADER
#include vdomainviewHEADER
#include viconviewHEADER
#include vconfirmHEADER
#include vfilechsrHEADER
#include vapplicationHEADER

/* Our headers */
#include "iman.h"
#include "tstack.h"
#include "tarray.h"
#include "names.h"
#include "statitem.h"
#include "com.h"
#include "isnf.h"
#include "statwin.h"
#include "utils.h"
#include "view.h"
#include "viewpriv.h"


/* Define our debug tag for vdebug manager */
#if vdebugDEBUG
static const char *const _editcmdsTag = "viewer-edit-commands";
#define vdebugTAG _editcmdsTag
#endif


/*
 *+------------------------------------------------------------------------+
 * private constants, variables, prototypes
 *+------------------------------------------------------------------------+
 */

typedef struct pasteAction {
  vundoAction 	action;		/* super */
  viewer	*view;		/* associated viewer */
  tarray	*items;		/* items to paste or un-paste */
  unsigned	deep:1;		/* TRUE if a paste (not paste-alias) */
  unsigned	dirty:1;	/* TRUE if viewer was dirty before me */
}pasteAction;

typedef struct cutAction {
  vundoAction 	action;		/* super */
  viewer	*view;		/* associated viewer */
  tarray	*items;		/* items to remove-insert */
  unsigned	dirty:1;	/* TRUE if viewer was dirty before me */
}cutAction;

typedef cutAction removeAction;

static vstr			*undoTitle = NULL;
static vstr			*undoTemplateTitle = NULL;
static vstr			*redoTemplateTitle = NULL;
static vundoActionClass 	*pasteActionClass = NULL;
static vundoActionClass 	*cutActionClass = NULL;
static vundoActionClass 	*removeActionClass = NULL;
static const vname		*titlePasteAction, *titlePasteAsAliasAction;
static const vname		*titleDuplicateAction, *titleDuplicateAsAliasAction;
static const vname		*titleCutAction, *titleClearAction;
static const vname		*titleRemoveAllAction, *titlePasteAsGroupAction;


static void			editSaveSelection(viewer*);
static void			editDestroySelection(viewer*);

static void			editUpdateSelectionDependentInterface(viewer*);
static void			editUpdateClipboardDependentInterface(viewer*);

static int			editUndoRedo(vcommandFunction*,vdict*);
static int			editCopy(vcommandFunction*,vdict*);
static int			editPaste(vcommandFunction*,vdict*);
static int			editPasteAsAliases(vcommandFunction*,vdict*);
static int			editPasteAsGroup(vcommandFunction*,vdict*);
static int			editDuplicate(vcommandFunction*,vdict*,int);
static int			editDup(vcommandFunction*,vdict*);
static int			editDupAsAliases(vcommandFunction*,vdict*);
static int			editCut(vcommandFunction*,vdict*,int);
static int			editCopyThenCut(vcommandFunction*,vdict*);
static int			editCutNoCopy(vcommandFunction*,vdict*);
static int			editRemoveAll(vcommandFunction*,vdict*);
static int			editQueryUndoRedo(vcommandFunction*,vdict*);
static int			editOpenImageEditor(vcommandFunction*,vdict*);

static void			pasteAddIcons(viewer*,tarray*);
static void			pasteAddAliasIcons(viewer*,tarray*);
static void			pasteRemoveIcons(viewer*,tarray*);
static void			pasteRemoveAliasIcons(viewer*,tarray*);
static void			pasteDestroyIcons(viewer*,tarray*);
static void			pasteDoAct(vundoAction*);
static void			pasteDestroy(vundoAction*);
static void			cutDoAct(vundoAction*);
static void			cutDestroy(vundoAction*);
static void			removeCheckClipSelection(viewer*, const vname*);
static void			removeRemoveIcons(viewer*,tarray*);
static void			removeAddIcons(viewer*,tarray*);
static void			removeDestroyIcons(viewer*,tarray*,int);
static int			removeLookup(const vname*, tarray*);
static void			removeGetOthers(viconviewIcon*, const vname*,
						tarray*, viconview*);
static void			removeDoAct(vundoAction*);
static void			removeDestroy(vundoAction*);

static appFunctionCmd fcmds[]= {
  {{appNAME_ACT_UNDO, 1,0, vkeyNULL_STROKE}, editUndoRedo, editQueryUndoRedo},
  {{appNAME_ACT_CUT, 1,0, vkeyNULL_STROKE}, editCopyThenCut, NULL},
  {{appNAME_ACT_REMOVE, 1,0, vkeyNULL_STROKE}, editRemoveAll, NULL},
  {{appNAME_ACT_COPY, 1,0, vkeyNULL_STROKE}, editCopy, NULL},
  {{appNAME_ACT_PASTE,1,0, vkeyNULL_STROKE}, editPaste, NULL},
  {{appNAME_ACT_CLEAR, 1,0, vkeyNULL_STROKE}, editCutNoCopy, NULL},
  {{appNAME_ACT_PASTE_ALIAS,1,0, vkeyNULL_STROKE}, editPasteAsAliases, NULL},
  {{appNAME_ACT_PASTE_DICT,1,0, vkeyNULL_STROKE}, editPasteAsGroup, NULL},
  {{appNAME_ACT_DUPLICATE,1,0, vkeyNULL_STROKE}, editDup, NULL},
  {{appNAME_ACT_DUPLICATE_ALIAS,1,0, vkeyNULL_STROKE}, editDupAsAliases, NULL},
  {{appNAME_ACT_EDIT_IMAGE, 1,0, vkeyNULL_STROKE}, editOpenImageEditor, NULL},
  {{-1},NULL,NULL}
};

/*
 *+------------------------------------------------------------------------+
 * query for selection and/or clipboard dependent commands: we can use
 * the same query for several function since the behaviors are identical
 * and depend only on the viewer's current selection or clipboard status.
 *+------------------------------------------------------------------------+
 */

static int seldependents[]= {	/* commands that are selection dependent */
  appNAME_ACT_CUT,
  appNAME_ACT_COPY,
  appNAME_ACT_CLEAR,
  appNAME_ACT_DUPLICATE,
  appNAME_ACT_DUPLICATE_ALIAS,
  appNAME_ACT_REMOVE,
  appNAME_ACT_EDIT_IMAGE,
  appNAME_ACT_BOINK,
  -1
};
static int clipdependents[]= {	/* commands that are clipboard dependent */
  appNAME_ACT_PASTE,
  appNAME_ACT_PASTE_ALIAS,
  appNAME_ACT_PASTE_DICT,
  -1
};
static int dirtydependents[]= {	/* commands that are viewer-dirty dependent */
  appNAME_ACT_SAVE,
  appNAME_ACT_REVERT,
  -1
};

/********
 * editMakeUndoTitle makes an up-to-date undo/redo title based on the
 * state of the viewer's undo action list.
 *
 * -> viewer, the viewer
 * <- title,  the undo command title
 ********/
static vstr*
editMakeUndoTitle(viewer *view)
{
  vstr *title = NULL;

  if (!view->actions) {
    title = undoTitle;	/* "Undo <none>" */
  }
  else {
    if (vundoGetActionListState(view->actions)==vundoDONE)
      title = isnfReplaceMulti(undoTemplateTitle, 
                 vundoGetActionListName(view->actions), NULL);
    else
      title = isnfReplaceMulti(redoTemplateTitle, 
                 vundoGetActionListName(view->actions), NULL);
  }
  return title;
}


/********
 * viewerUpdateUndoInterface is called whenever an "Undo" or "Redo" command
 * is completed. Updates the Undo/Redo titles properly to reflect the
 * state and name of the command. Note we update the state dictionary so we
 * don't need the provide that information w/ a query function.
 *
 * -> viewer, the viewer
 * <- void
 ********/
void
viewerUpdateUndoInterface(register viewer *view)
{
  const vname 	*state;
  vstr		*title;
  vbool		 undoable;

  undoable = viewerLastActionIsUndoable(view);
  state =  undoable ? vname_Enabled : vname_Disabled;
  vdictStore(viewerGetStateDict(view), appname_UndoAct, state);
  vwindowPropagateChange(vdialogGetWindow((view)->dialog), 
      vname_State, appname_UndoAct, state);

  title = editMakeUndoTitle(view);
  vwindowPropagateChange(vdialogGetWindow((view)->dialog), 
			 vname_Title, appname_UndoAct, title);
  if (undoable)
    vstrDestroy(title);

  return;
}

/********
 * editUpdateSelectionDependentInterface is called whenever the 
 * selection state changes. Updates the misc Edit commands that manipulate
 * the clipboard. Note we update the state dictionary so we
 * don't need the provide that information w/ a query function.
 *
 * -> viewer, the viewer
 * <- void
 ********/
static void
editUpdateSelectionDependentInterface(viewer *view)
{
  register int 		*i;
  vdict			dic;
  register const vname	*state;

  vdictInit(&dic, vnameHash);
  state = view->noselection ? vname_Disabled : vname_Enabled;
  for (i= seldependents; *i>=0; i++) {
    vdictStore(&dic, appName(*i), state);
    vdictStore(viewerGetStateDict(view), appName(*i), state);
  }
  vwindowPropagateChangeDict(vdialogGetWindow(view->dialog), 
			     vname_State, &dic);
  vdictDestroy(&dic);
  return;
}

/********
 * editUpdateClipboardDependentInterface is called whenever the 
 * clipboard contents change. Updates the misc Edit commands that manipulate
 * the clipboard. Note we update the state dictionary so we
 * don't need the provide that information w/ a query function.
 *
 * -> viewer, the viewer
 * <- void
 ********/
static void
editUpdateClipboardDependentInterface(viewer *view)
{
  register int 		*i;
  vdict			dic;
  register const vname	*state;

  vdictInit(&dic, vnameHash);
  state = view->clipsel ? vname_Enabled : vname_Disabled;
  for (i= clipdependents; *i>=0; i++) {
    vdictStore(&dic, appName(*i), state);
    vdictStore(viewerGetStateDict(view), appName(*i), state);
  }
  vwindowPropagateChangeDict(vdialogGetWindow(view->dialog), 
			     vname_State, &dic);
  vdictDestroy(&dic);
  return;
}



/********
 * viewerUpdateDirtyDependentInterface is called whenver the contents
 * of the viewer's store changes (cut/paste/duplicate/etc). Updates
 * Save type commands.
 *
 * -> viewer, the viewer
 * <- void
 ********/
void
viewerUpdateDirtyDependentInterface(viewer *view)
{
  register int 		*i;
  vdict			dic;
  register const vname	*state;

  vdictInit(&dic, vnameHash);
  state = view->dirty ? vname_Enabled : vname_Disabled;
  for (i= dirtydependents; *i>=0; i++) {
    vdictStore(&dic, appName(*i), state);
    vdictStore(viewerGetStateDict(view), appName(*i), state);
  }
  vwindowPropagateChangeDict(vdialogGetWindow(view->dialog), 
			     vname_State, &dic);
  vdictDestroy(&dic);
  return;
}


/********
 * editQueryUndoRedo sets the current title of the undo command.
 * We need this routine because we don't have a vname_Title dictionary
 * associated w/ our command space. Warning: if the title is being set
 * the string must be persistent until the next Undo query.
 *
 * -> command, the command
 * -> context, [filled-in] command context
 * <- TRUE
 ********/
static int
editQueryUndoRedo(vcommandFunction *com, vdict *context)
{
  viewer *view = viewerFromContext(context);
  vstr *title;

  if (view->undotitle) {
    vstrDestroy(view->undotitle);
    view->undotitle = NULL;
  }

  title = editMakeUndoTitle(view);
  vdictStore(context, vname_Title, title); /* !must be persistent!*/
  if (viewerLastActionIsUndoable(view))
    view->undotitle = title;

  return vTRUE;
}


/*
 *+------------------------------------------------------------------------+
 * shared by viewer's code in view.c: 
 *+------------------------------------------------------------------------+
 */

/********
 * viewerEditStartup initializes this module. called by viewer 
 * initialization routine.
 *
 * -> app, the application
 * <- void
 ********/
void
viewerEditStartup(isnifferApp *app)
{
  register vundoActionClass *clas;
  register vstr		    *title;

  /* mega undo actions' titles */
  undoTitle = isnfStrFrom(strTitleGenericUndo);
  undoTemplateTitle = isnfStrFrom(strTitleGenericUndoTemplate);
  redoTemplateTitle = isnfStrFrom(strTitleGenericRedoTemplate);

  title = isnfStrFrom(strTitlePasteAction);
  titlePasteAction = vnameInternGlobal(title);
  vstrDestroy(title);

  title = isnfStrFrom(strTitlePasteAsAliasAction);
  titlePasteAsAliasAction = vnameInternGlobal(title);
  vstrDestroy(title);

  title = isnfStrFrom(strTitleDuplicateAction);
  titleDuplicateAction = vnameInternGlobal(title);
  vstrDestroy(title);

  title = isnfStrFrom(strTitleDuplicateAsAliasAction);
  titleDuplicateAsAliasAction = vnameInternGlobal(title);
  vstrDestroy(title);

  title = isnfStrFrom(strTitleCutAction);
  titleCutAction = vnameInternGlobal(title);
  vstrDestroy(title);

  title = isnfStrFrom(strTitleClearAction);
  titleClearAction = vnameInternGlobal(title);
  vstrDestroy(title);

  title = isnfStrFrom(strTitleRemoveAllAction);
  titleRemoveAllAction = vnameInternGlobal(title);
  vstrDestroy(title);

  title = isnfStrFrom(strTitlePasteAsGroupAction);
  titlePasteAsGroupAction = vnameInternGlobal(title);
  vstrDestroy(title);

  /* paste class */
  clas  = vclassReproduce(vundoGetDefaultActionClass());
  vclassSetObjectSize(clas, sizeof(pasteAction));
  vclassSet(clas, vundoACT, pasteDoAct);
  vclassSet(clas, vundoDESTROY, pasteDestroy);
  pasteActionClass = clas;

  /* cut class */
  clas  = vclassReproduce(vundoGetDefaultActionClass());
  vclassSetObjectSize(clas, sizeof(cutAction));
  vclassSet(clas, vundoACT, cutDoAct);
  vclassSet(clas, vundoDESTROY, cutDestroy);
  cutActionClass = clas;

  /* remove-all class */
  clas  = vclassReproduce(vundoGetDefaultActionClass());
  vclassSetObjectSize(clas, sizeof(removeAction));
  vclassSet(clas, vundoACT, removeDoAct);
  vclassSet(clas, vundoDESTROY, removeDestroy);
  removeActionClass = clas;

  return;
}

/********
 * viewerEditShutdown shuts down this module. called by the viewer
 * shutdown routine.
 *
 * -> void
 * <- void
 ********/
void
viewerEditShutdown(void)
{
  if (undoTitle)
    vstrDestroy(undoTitle);
  if (undoTemplateTitle)
    vstrDestroy(undoTemplateTitle);
  if (redoTemplateTitle)
    vstrDestroy(redoTemplateTitle);
  viewerShutdownImageEditor();
  return;
}

/********
 * viewerEditAttachCommands is called to attach dialog-level edit
 * commands to a viewer dialogue's space.
 *
 * -> view, the viewer
 * <- void
 ********/
void
viewerEditAttachCommands(register viewer *view)
{
  appAddFunctionsToCommandSpaceDescription(&view->aspace, fcmds);
  view->noselection = vTRUE;
  return;
}

/********
 * viewerEditDestroy is called to clean up any edit command specific
 * information associated w/ viewer.
 *
 * #a# our menu queries might use these variables, make sure they're
 *     not pointing to the 0xdeadbeef.
 *
 * -> view, the viewer
 * <- void
 ********/
void
viewerEditDestroy(viewer *view)
{
  viewerCommitImageEditor(view, NULL);
  if (view->clipsel)
    editDestroySelection(view);
  if (viewerLastActionIsUndoable(view))
    viewerCommitUndoables(view);
  if (view->undotitle)
    vstrDestroy(view->undotitle);

  /* #a# */
  view->clipsel   = NULL;
  view->actions   = NULL;
  view->undotitle = NULL;

  return;
}

/*
 *+------------------------------------------------------------------------+
 * private: utils shared by commands
 *+------------------------------------------------------------------------+
 */
/********
 * editCopyOrigItem is called to copy an active vieweritem to our hoaky
 * clipboard. Note this retrieves a new reference to the item's image.
 *
 * !one day we should update this code to use vscraps and vclipbroads!
 *
 * -> icon,  the item from the viewer's iconview
 * -> item,  the vieweritem to fill in
 * <- void
 ********/
static void
editCopyOrigItem(viconviewIcon *icon, register vieweritem *item)
{
  register vieweritem *orig;

  orig = viewerGetIconItem(icon);
  *item = *orig;
  item->sniffed   = imanagerRetrieveImage(iman, item->tag, NULL);
  item->thumbnail = NULL;
  item->loaded    = vTRUE;
  item->pool      = vFALSE;
  item->icon	  = NULL;
  item->pos       = viconviewGetIconPosition(icon);
  item->others    = NULL;
  item->editing   = vFALSE;

  if (orig->sniffed==orig->displayed)
    item->displayed= item->sniffed;
}

/********
 * viewerCommitUndoables commits the last undoable operation. 
 * resets the undo action list to NULL.
 *
 * -> view, the viewer
 * <- void
 ********/
void
viewerCommitUndoables(viewer *view)
{
  if (view->actions) {
    vundoDestroyActionList(view->actions);
    view->actions = NULL;
  }
  return;
}

/********
 * editSaveSelection saves the current selection to our private
 * clipboard selection (store REFERENCES to items).
 *
 * -> viewer, the view
 * <- void
 ********/
static void
editSaveSelection(viewer *view)
{
  viconview				*iconview;
  vdomainObjectSetIterator		iterator;
  register vdomainObjectSetIterator	*iter = &iterator;
  vieweritem				itemstorage;
  register vieweritem			*item = &itemstorage;
  tarray				*a;
  vdomainObject				*obj;
  viconviewIcon				*icon;
  vdomain				*dom;
  vdomainObjectSet			*set;

  /* destroy any info that's already there */
  editDestroySelection(view);

  /* grab the current selection */
  iconview = viewerGetIconview(view);
  dom = viconviewGetDomain(iconview);
  set = vdomainGetObjectSet(dom, 
                vdomainviewGetSelection(viconviewGetDomainView(iconview)),
		vdomainSELECTED | vdomainMATCHFUNC | vdomainLOGICAL_AND, 
		viewerMatchOnlyImages);

  /* alloc size of selection */
  a = tarrayCreateSized(sizeof(vieweritem), vdomainGetObjectSetCount(set));
  imanagerSetActiveImageStore(iman, view->store);

  /* insert a REFERENCE of each item's image/name/position */
  vdomainInitObjectSetIterator(iter, set);
  while (vdomainNextObjectSetIterator(iter)) {
    obj  = vdomainGetObjectSetIteratorObject(iter);
    icon = viconviewIconFromObject(obj);
    editCopyOrigItem(icon, item);
    tarrayAppendItem(a, item);
  }
  vdomainDestroyObjectSetIterator(iter);
  vdomainDestroyObjectSet(set);

  /* attach to viewer */
  if (!tarrayGetNumber(a)) {
    tarrayDestroy(a);
    view->clipsel = NULL;
  }
  else
    view->clipsel = a;

  return;
}

/********
 * editDestroySelection releases the references stored in our
 * private clipboard selection and resets the selection empty.
 *
 * -> viewer, the viewer
 * <- void
 ********/
static void
editDestroySelection(viewer *view)
{
  register tarray *a;
  register vieweritem *scan, *stop;

  a = view->clipsel;
  if (a) {
    vdebugIF(!tarrayGetNumber(a), vexGenerate(vexGetValueClass(), vexMESSAGE,
             "destroy-clip: empty selection was saved!?!", vexERRNO, 0, 
             vexNULL));
    imanagerSetActiveImageStore(iman, view->store);
    scan = tarrayAtStartAs(a, vieweritem*);
    stop = tarrayAtStopAs(a, vieweritem*);
    for (; scan<stop; scan++)
      imanagerReleaseImage(iman, scan->sniffed, scan->tag);
    tarrayDestroy(a);
    view->clipsel = NULL;
  }
  return;
}


/********
 * editRefreshSelection updates the selection to contain the set of
 * objects newly created by an edit command (paste, duplicate, etc.)
 *
 * -> view,     the viewer
 * -> set,      the new set or NULL if nuke selection
 * -> iconview, the viewer's viconview
 * <- void
 *********/
static void
editRefreshSelection(viewer *view, vdomainObjectSet *set, viconview *iconview)
{
  if (set) {
    vdomainSelectAll(viconviewGetDomain(iconview), 
		 vdomainviewGetSelection(viconviewGetDomainView(iconview)),
		 vFALSE, vFALSE);
    vdomainSelectObjects(viconviewGetDomain(iconview), 
	         vdomainviewGetSelection(viconviewGetDomainView(iconview)),
		 set);
    view->noselection = vFALSE;
  }
  else {
    vdomainSelectAll(viconviewGetDomain(iconview), 
		 vdomainviewGetSelection(viconviewGetDomainView(iconview)),
		 vFALSE, vFALSE);
    view->noselection = vTRUE;
  }

  editUpdateSelectionDependentInterface(view);
}


/*
 *+------------------------------------------------------------------------+
 * edit issue command
 *+------------------------------------------------------------------------+
 */

/********
 * viewerEditHandleSelectIcon is called when the user changes the selection
 * in the viewer's iconview. Handle double clicks (opens image editor),
 * and updates availability of all selection-dependent commands.
 *
 * -> iconview, the viewer's iconview
 * -> icon,     the affected icon item
 * -> event,    the triggering event (can be NULL)
 * -> selected, TRUE if item being selected else FALSE
 * <- void
 *********/
void
viewerEditHandleSelectIcon(viconview *iconview, viconviewIcon *icon, 
		           vevent *event, vbool selected)
{
  viewer *view = (viewer*)viconviewGetData(iconview);
  int number= 0;

  /* update interface dependent on selection */
  if (event) {
    int	noselection;
    number = vdomainviewSelectedObjects(viconviewGetDomainView(iconview));
    noselection = (number==0);
    if (view->noselection != noselection) {
      view->noselection = noselection;
      editUpdateSelectionDependentInterface(view);
    }
  }

  /* handle double-clicks, note 2items/icon */
  if (event && selected && veventGetPointerClickCount(event)==2 &&
      number==2)
    viewerOpenImageEditor(view, icon);

  return;
}


/*
 *+------------------------------------------------------------------------+
 * private command: undo/redo last thingy
 *+------------------------------------------------------------------------+
 */

/********
 * editUndoRedo is called when the user selected the undo item (which is
 * actually titled either "Undo <Command Name>" or "Redo <Command Name>").
 * Undoooos or Redoooos the last Undooooable or Redoooable command.
 *
 * -> com,     the Undo/Redo command
 * -> context, the command's context
 * <- TRUE
 *********/
static int
editUndoRedo(vcommandFunction *com, vdict *context)
{
  viewer *view = viewerFromContext(context);
  if (view->actions) {
    vundoActActionList(view->actions);
    viewerUpdateUndoInterface(view);
  }
  return vTRUE;
}

/*
 *+------------------------------------------------------------------------+
 * private command: copying selection to "clipboard"
 *+------------------------------------------------------------------------+
 */

/********
 * editCopy is called when the the "Copy selection" command is triggered.
 * Copies the current icon selection to our private clipboard.
 *
 * -> com,     the command
 * -> context, the command's context
 * <- TRUE
 *********/
static int
editCopy(vcommandFunction *com, vdict *context)
{
  viewer  *view;
  int	   commited;

  /* nuke last undoable (?!) */
  view = viewerFromContext(context);
  if ((commited = viewerLastActionIsUndoable(view)))
    viewerCommitUndoables(view);

  /* save the current selection - this destroys what exists */
  editSaveSelection(view);
  vdebugIF(!view->clipsel, vexGenerate(vexGetValueNullClass(), vexMESSAGE,
           "copy-selection: command active when no selection?!", vexERRNO, 0,
           vexNULL));

  /* update commands that require a valid clip selection */
  editUpdateClipboardDependentInterface(view);

  /* update the undo interface to reflect we've commited the last */
  if (commited)
    viewerUpdateUndoInterface(view);
  return vTRUE;
}

/*
 *+------------------------------------------------------------------------+
 * private command: pasting. there are 2 types of pasting: "deep" and 
 * "shallow" pasting. deep pasting inserts a unique copy of the item into
 * the image store while "shallow" pasting inserts an reference to an existing
 * item (which itself may be an alias). shallow pasting is used to test 
 * multiple retrieves of a single image with the image manager, while deep
 * pasting tests the undoablity of additions in the image manager.
 *
 * note: remember paste actions are done _in_addition_to_ the imanager's
 *       own undoable actions!
 *+------------------------------------------------------------------------+
 */

#define TEENY_OFFSET 15 /* offset pasted items little bit from original */

/********
 * pasteAddIcons is called to perform a "deep" paste operation on the given
 * viewer's iconview. Adds the (icon) contents of the given array to the 
 * viewer's iconview. Assumes the array contains vieweritem references and 
 * is NOT empty!
 *
 * -> view,  the viewer
 * -> array, the array of vieweritems* (obtained from clipboard)
 * <- void
 *********/
static void
pasteAddIcons(viewer *view, tarray *a)
{
  viconview			*iconview;
  vdomainObjectSet		*set;
  register viconviewIcon	*icon;
  register vieweritem		**scan, **stop;
  viconviewView			*iconiconview;
  vdomainObject			*iconobj, *nameobj;

  /* we only show the icon view */
  iconiconview = viconviewGetIconView();
  iconview = viewerGetIconview(view);

  /* add items to the iconview */
  set  = vdomainCreateObjectSet(NULL); 
  scan = tarrayAtStartAs(a, vieweritem**);
  stop = tarrayAtStopAs(a, vieweritem**);
  for (; scan<stop; scan++) {
    icon = (*scan)->icon;
    if (!icon) { /* not being re-done...*/
      icon = (*scan)->icon = viconviewCreateIcon();
      viconviewSetIconData(icon, *scan);
      (*scan)->pos.x += TEENY_OFFSET; /* originally down to the right */
      (*scan)->pos.y -= TEENY_OFFSET;
    }
    vieweritemDetermineDisplayedImage(view, *scan, iconiconview);
    viconviewAddIcon(iconview, icon);
    viconviewSetIconPosition(icon, &(*scan)->pos);
    viconviewGetIconObjects(icon, &iconobj, &nameobj);
    vdomainAddToObjectSet(&set, iconobj);
  }

  /* select the new doohickies */
  editRefreshSelection(view, set, iconview);
  vdomainDestroyObjectSet(set);

  return;
}

/********
 * pasteRemoveIcons is called to undo a deep paste. Removes the items icons
 * from the viewer's iconview but does not destroy the actual vieweritem
 * structures.
 *
 * -> view,  the viewer
 * -> array, the array of vieweritem ptrs added through pasteAddIcons
 * <- void
 *********/
static void
pasteRemoveIcons(viewer *view, tarray *a)
{
  register vieweritem	**scan, **stop;
  register viconview 	*iconview;

  iconview = viewerGetIconview(view);
  scan = tarrayAtStartAs(a, vieweritem**);
  stop = tarrayAtStopAs(a, vieweritem**);
  for (; scan<stop; scan++) {
    (*scan)->pos = viconviewGetIconPosition((*scan)->icon);
    viconviewRemoveIcon(iconview, (*scan)->icon);
  }

  editRefreshSelection(view, NULL, iconview);
  return;
}


/********
 * pasteAddAliasIcons is called to perform a "shallow" paste. Adds the 
 * (vieweritem) contents of the given array to the viewer's iconview - the
 * icon items contain a REFERENCE to the image not an actual duplicate.
 * Assumes the array is NOT empty.
 *
 * -> view,  the viewer
 * -> array, the array of vieweritem ptrs to add
 * <- void
 *********/
static void
pasteAddAliasIcons(viewer *view, tarray *a)
{
  viconview			*iconview;
  vdomainObjectSet		*set;
  register viconviewIcon	*icon;
  register vieweritem		**scan, **stop;
  viconviewView			*iconiconview;
  vdomainObject			*iconobj, *nameobj;

  /* we only show the icon view */
  iconview = viewerGetIconview(view);
  iconiconview = viconviewGetIconView();

  /* we want to explicitly retrieve from the viewer's store */
  imanagerSetActiveImageStore(iman, view->store);

  /* add items to the iconview */
  set  = vdomainCreateObjectSet(NULL); 
  scan = tarrayAtStartAs(a, vieweritem**);
  stop = tarrayAtStopAs(a, vieweritem**);
  for (; scan<stop; scan++) {
    icon = (*scan)->icon;
    if (!icon) { /* not being re-done */
      icon = (*scan)->icon = viconviewCreateIcon();
      viconviewSetIconData(icon, *scan);
      (*scan)->pos.x += TEENY_OFFSET; /* originally down to the right */
      (*scan)->pos.y -= TEENY_OFFSET;
    }
    (*scan)->sniffed = imanagerRetrieveImage(iman, (*scan)->tag, NULL);
    (*scan)->loaded  = vTRUE;
    vieweritemDetermineDisplayedImage(view, *scan, iconiconview);
    viconviewAddIcon(iconview, icon);
    viconviewSetIconPosition(icon, &(*scan)->pos);
    viconviewGetIconObjects(icon, &iconobj, &nameobj);
    vdomainAddToObjectSet(&set, iconobj);
  }

  /* select the new doohickies */
  editRefreshSelection(view, set, iconview);
  vdomainDestroyObjectSet(set);

  return;
}

/********
 * pasteRemoveIcons is called to undo a shallow paste. Removes the items'
 * icons from the viewer's iconview but does not destroy the actual 
 * vieweritem structures (remains viable for "Redo").
 *
 * #a#	done in case the actual image referenced by our tag changes
 * 	between undo and redo,(not needed for this case, but done to 
 *	demonstrate this potential situation...)
 *
 * -> view,  the viewer
 * -> array, the array of vieweritem ptrs used by pasteAddAliasIcons
 * <- void
 *********/
static void
pasteRemoveAliasIcons(viewer *view, tarray *a)
{
  register viconview	*iconview;
  register vieweritem	**scan, **stop;

  /* we want to explicitly nuke from the view's store */
  iconview = viewerGetIconview(view);
  imanagerSetActiveImageStore(iman, view->store);

  /* remove items from the view and store */
  scan = tarrayAtStartAs(a, vieweritem**);
  stop = tarrayAtStopAs(a, vieweritem**);
  for (; scan<stop; scan++) {
    imanagerReleaseImage(iman, (*scan)->sniffed, (*scan)->tag);
    (*scan)->pos = viconviewGetIconPosition((*scan)->icon);
    /* #a# see comment in header */
    (*scan)->sniffed   = NULL;
    (*scan)->displayed = NULL;
    (*scan)->loaded    = vFALSE;
    vieweritemNukeThumbnail(*scan);
    viconviewRemoveIcon(iconview, (*scan)->icon);
  }
  editRefreshSelection(view, NULL, iconview);
  return;
}

/********
 * pasteDestroyIcons destroys the iconview icons associated with the given
 * array of vieweritems. Used to commit an undone "paste" operation on
 * a viewer's iconview.
 *
 * -> view,  the viewer
 * -> array, the array of vieweritem ptrs passed to pasteAddIcons or 
 *           pasteAddAliasIcons.
 * <- void
 *********/
static void
pasteDestroyIcons(viewer *view, tarray *a)
{
  register vieweritem	**scan, **stop;
  scan = tarrayAtStartAs(a, vieweritem**);
  stop = tarrayAtStopAs(a, vieweritem**);
  for (; scan<stop; scan++) {
    viconviewDestroyIcon((*scan)->icon);
    vieweritemDestroy(*scan);
  }
  return;
}

/********
 * pasteDoAct is called by the Paste Undoable action to Do, Undo, or
 * Redo the actual paste operation.
 *
 * -> action the paste undoable action
 * <- void
 *********/
static void
pasteDoAct(vundoAction *action)
{
  register pasteAction *act = (pasteAction*)action;
  switch (vundoGetActionState(action)) {

    /* ORIG action (1st time) */
    case vundoNEW: {
      act->dirty = viewerIsDirty(act->view);
      /* fall through */
    }

    /* [RE]DO action */
    case vundoUNDONE: {
      if (act->deep) pasteAddIcons(act->view, act->items);
      else pasteAddAliasIcons(act->view, act->items);
      if (act->deep) viewerTouch(act->view, vTRUE);
      break;
    }

    /* UNDO action */
    case vundoDONE:   {
      if (act->deep) pasteRemoveIcons(act->view, act->items);
      else pasteRemoveAliasIcons(act->view, act->items);
      if (act->deep && !act->dirty) viewerTouch(act->view, vFALSE);
      break;
    }
  }
  vclassSendSuper(pasteActionClass, vundoACT, (action));
  viewerUpdateDirtyDependentInterface(act->view);
  return;
}

/********
 * pasteDestroy is called to destroy a Paste Undoable action. Does
 * the proper cleanup depending on whether the action was undone.
 *
 * -> action, the paste action
 * <- void
 *********/
static void
pasteDestroy(vundoAction *action)
{
  register pasteAction *act = (pasteAction*)action;
  switch (vundoGetActionState(action)) {

    /* was UNDONE */
    case vundoUNDONE: {
      pasteDestroyIcons(act->view, act->items);
      /*>>fall-through<<*/
    }

    /* was DONE */
    case vundoDONE:   {
      tarrayDestroy(act->items);
      break;
    }
  }
  vclassSendSuper(pasteActionClass, vundoDESTROY, (action));
  return;
}

/********
 * editPaste is called whenever the (deep) Paste command is triggered
 * in a viewer dialog.  Pastes copies of the clipboard contents. Undoable
 * command.
 *
 * -> com,     the paste command
 * -> context, the command's context
 * <- TRUE
 *********/
static int
editPaste(vcommandFunction *com, vdict *context)
{
  register viewer	*view;
  viconview		*iconview;
  register vieweritem	*scan, *stop;
  vieweritem		*item;
  vundoAction		*act;
  pasteAction		*pasteAct;
  tarray		*a;
  viconviewView		*iconiconview;
  tarray		*volatile a_v = NULL;
  vundoActionList	*volatile list_v = NULL;
  viewer		*volatile view_v;


  /* pull our objects from context */
  view_v = view = viewerFromContext(context);
  vdebugIF((!view->clipsel), vexGenerate(vexGetValueNullClass(), vexMESSAGE,
           "paste-clip: command active when no clipboard?!", vexERRNO, 0,
           vexNULL));


  /* commit(make permanent) the last undoable edit action */
  viewerCommitUndoables(view);
  list_v = view->actions = vundoCreateActionList();


  /* add duplicates of selected items to the iconview */
  vexWITH_HANDLING
    {
      /* create array of vieweritems to keep track of the images
       * created for the paste. if user undoes and then redoes operation 
       * we can't do a retrieve for the redo! */
      a_v = a = tarrayCreateSized(sizeof(vieweritem*),
				  tarrayGetNumber(view->clipsel));
      iconiconview = viconviewGetIconView();
      iconview = viewerGetIconview(view);

      /* add each item to image store, appending each associated undo
       * action to the action list */
      scan = tarrayAtStartAs(view->clipsel, vieweritem*);
      stop = tarrayAtStopAs(view->clipsel, vieweritem*);
      for (; scan<stop; scan++, view->last++) {
	item = vieweritemAlloc();
	item->sniffed = vimageClone(scan->sniffed);
	do {
	  item->tag = vnameInternGlobalScribed(vnumScribeInt(view->last));
	  if (imanagerGetNumberOfImageUsers(iman, view->store, item->tag)
	      <=0)
	    break;
	  view->last++;
	}while(1);
	item->name    = item->tag;
	item->pos     = scan->pos;
	item->loaded  = vTRUE;
	imanagerAddImageToImageStoreUndoable(iman, view->store, 
		      item->sniffed, item->tag, (void**)&act);
	vundoAddActionListAction(view->actions, act);
	tarrayAppendItem(a, &item);
      }

      /* create action that will add/remove icons from iconview */
      pasteAct = (pasteAction*)vundoCreateActionOfClass(pasteActionClass);
      pasteAct->view  = view;
      pasteAct->items = a;
      pasteAct->deep  = vTRUE;

      /* do action for 1st time, set state to done */
      vundoActAction((vundoAction*)pasteAct);

      /* append to action list -- done after imanager's stuff! */
      vundoAddActionListAction(view->actions, (vundoAction*)pasteAct);
      vundoSetActionListName(view->actions, titlePasteAction);
      a_v = NULL;

      /* advance the list's state to DONE */
      vundoActActionList(view->actions);
    }

  /* if we've barfted for some reason, try to cleanup for a complete
   * recovery (yeh right)*/
  vexON_EXCEPTION
    {
      vdebugBE(vexDumpChain(vdebugGetWarningStream()));
      if (a_v) {
	if (tarrayGetNumber(a_v)) {
	  vieweritem **pscan, **pstop;
	  pscan = tarrayAtStartAs(a_v, vieweritem**);
	  pstop = tarrayAtStopAs(a_v, vieweritem**);
	  for (; pscan<pstop; pscan++) {
	    if ((*pscan)->sniffed)
	      vimageDestroy((*pscan)->sniffed);
	    vieweritemDestroy(*pscan);
	  }
	}
	tarrayDestroy(a_v);
      }
      if (list_v) 
	vundoDestroyActionList(list_v);
      view_v->actions = NULL;
      vexClear();
    }
  vexEND_HANDLING;

  viewerUpdateUndoInterface(view_v);
  return vTRUE;
}

/********
 * editPasteAliases is called whenever the (shallow) Paste command is 
 * triggered in a viewer dialog.  Pastes aliases of the clipboard contents. 
 * Undoable command.
 *
 * -> com,     the paste command
 * -> context, the command's context
 * <- TRUE
 *********/
static int
editPasteAsAliases(vcommandFunction *com, vdict *context)
{
  register viewer	*view;
  viconview		*iconview;
  register vieweritem	*scan, *stop;
  vieweritem		*item;
  pasteAction		*pasteAct;
  tarray		*a;
  viconviewView		*iconiconview;
  tarray		*volatile a_v = NULL;
  vundoActionList	*volatile list_v = NULL;
  viewer		*volatile view_v;


  /* pull our objects from context */
  view_v = view = viewerFromContext(context);
  vdebugIF((!view->clipsel), vexGenerate(vexGetValueNullClass(), vexMESSAGE,
           "paste-aliases: command active when no clipboard?!", vexERRNO, 0,
           vexNULL));


  /* commit(make permanent) the last undoable edit action */
  viewerCommitUndoables(view);
  list_v = view->actions = vundoCreateActionList();


  /* add aliases of selected items to the iconview */
  vexWITH_HANDLING
    {
      /* create tarray of viewer items to keep track of the images
       * created for the paste. if user undoes and then redoes operation 
       * we can do a release or retrieve image! */
      a_v = a = tarrayCreateSized(sizeof(vieweritem*),
				  tarrayGetNumber(view->clipsel));
      iconiconview = viconviewGetIconView();
      iconview = viewerGetIconview(view);

      /* add each item to array -- don't create new tags for the 
       * items since we're testing multiple references to a single image */
      scan = tarrayAtStartAs(view->clipsel, vieweritem*);
      stop = tarrayAtStopAs(view->clipsel, vieweritem*);
      for (; scan<stop; scan++) {
	item = vieweritemAlloc();
	item->tag = item->name = scan->tag;
	item->pos = scan->pos;
	tarrayAppendItem(a, &item);
      }

      /* create action that will add/remove icons from iconview
       * and retrieve/release images from store */
      pasteAct = (pasteAction*)vundoCreateActionOfClass(pasteActionClass);
      pasteAct->view  = view;
      pasteAct->items = a;
      pasteAct->deep  = vFALSE;

      /* do action for 1st time, set state to done */
      vundoActAction((vundoAction*)pasteAct);

      /* append to the action list */
      vundoAddActionListAction(view->actions, (vundoAction*)pasteAct);
      vundoSetActionListName(view->actions, titlePasteAsAliasAction);
      a_v = NULL;

      /* advance the list's state to DONE */
      vundoActActionList(view->actions);
    }

  /* if we've barfted for some reason, try to cleanup for a complete
   * recovery (yeh right)*/
  vexON_EXCEPTION
    {
      vdebugBE(vexDumpChain(vdebugGetWarningStream()));
      if (a_v) {
	if (tarrayGetNumber(a_v)) {
	  vieweritem **scanp, **stopp;
	  scanp = tarrayAtStartAs(a_v, vieweritem**);
	  stopp = tarrayAtStopAs(a_v, vieweritem**);
	  for (; scanp<stopp; scanp++)
	    vieweritemDestroy(*scanp);
	}
	tarrayDestroy(a_v);
      }
      if (list_v) 
	vundoDestroyActionList(list_v);
      view_v->actions = NULL;
      vexClear();
    }
  vexEND_HANDLING;

  viewerUpdateUndoInterface((viewer*)view_v);
  return vTRUE;
}

/*
 *+------------------------------------------------------------------------+
 * private command: duplicating selection. really a combination of copy
 * and paste.
 *+------------------------------------------------------------------------+
 */

/********
 * editDuplicate is called when the either a deep or shallow "Duplicate" 
 * command is triggered. First copies the current selection, then does
 * either a deep or shallow paste. Undoable command.
 *
 * -> com,     the triggering command (deep or shallow)
 * -> context, the command's context
 * <- TRUE
 *********/
static int
editDuplicate(vcommandFunction *com, vdict *context, int deep)
{
  viewer	*view;
  tarray	*saveclip;

  /* save the current clipboard to a local variable; 
   * setup the viewer with the current selection in the clipboard */
  view = viewerFromContext(context);
  saveclip = view->clipsel;
  view->clipsel = NULL; /*!ouch!*/
  editSaveSelection(view);
  vdebugIF(!view->clipsel, vexGenerate(vexGetValueNullClass(), vexMESSAGE,
           "duplicate-selection: command active when no selection?!", 
           vexERRNO, 0, vexNULL));

  /* pretend we're a paste command using the transient clipboard;
   * remember to reflect the duplicate command in any undo ui
   * objects instead of a paste command */
  if (deep) {
    (void)editPaste(com, context);
    if (view->actions)
      vundoSetActionListName(view->actions, titleDuplicateAction);
  }
  else {
    (void)editPasteAsAliases(com, context);
    if (view->actions)
      vundoSetActionListName(view->actions, titleDuplicateAsAliasAction);
  }

  /* restore the true "clipboard" selection */ 
  editDestroySelection(view);
  view->clipsel = saveclip; /*!ouch!*/

  /* done */
  return vTRUE;
}

static int
editDup(vcommandFunction *com, vdict *context)
{
  return editDuplicate(com, context, vTRUE);
}

static int
editDupAsAliases(vcommandFunction *com, vdict *context)
{
  return editDuplicate(com, context, vFALSE);
}

/*
 *+------------------------------------------------------------------------+
 * private command: removing selections to "clipboard." NOTE: this has 
 * nothing to do with vclipboards! this is an internal fako-bako clipboard
 * doohickum!
 *+------------------------------------------------------------------------+
 */

/********
 * cutDoAct is called by the Cut Undoable action to Do, Undo, or
 * Redo the actual cut operation.
 *
 * -> action, the undoable cut action
 * <- void
 *********/
static void
cutDoAct(vundoAction *action)
{
  register cutAction *act = (cutAction*)action;
  switch (vundoGetActionState(action)) {

    /* ORIG action (1st time) */
    case vundoNEW: {
      act->dirty = viewerIsDirty(act->view);
      /* fall through */
    }

    /* [RE]DO action */
    case vundoUNDONE: {
      pasteRemoveIcons(act->view, act->items);
      viewerTouch(act->view, vTRUE);
      break;
    }

    /* UNDO action */
    case vundoDONE:   {
      pasteAddIcons(act->view, act->items);
      if (!act->dirty) viewerTouch(act->view, vFALSE);
      break;
    }
  }
  vclassSendSuper(cutActionClass, vundoACT, (action));

  viewerUpdateDirtyDependentInterface(act->view);

  return;
}

/********
 * cutDestroy is called to destroy an Undoable Cut action. Does
 * the proper cleanup depending on whether the action was undone.
 *
 * -> action, the cut action
 * <- void
 *********/
static void
cutDestroy(vundoAction *action)
{
  register cutAction *act = (cutAction*)action;
  switch (vundoGetActionState(action)) {

    /* was DONE */
    case vundoDONE: {
      register vieweritem **scan, **stop;
      imanagerSetActiveImageStore(iman, act->view->store);
      scan = tarrayAtStartAs(act->items, vieweritem**);
      stop = tarrayAtStopAs(act->items, vieweritem**);
      for (; scan<stop; scan++) {
	imanagerReleaseImage(iman, (*scan)->sniffed, (*scan)->tag);
	viconviewDestroyIcon((*scan)->icon);
	vieweritemDestroy(*scan);
      }

      /*>>fall-through<<*/
    }

    /* was UNDONE */
    case vundoUNDONE:   {
      tarrayDestroy(act->items);
      break;
    }
  }
  vclassSendSuper(cutActionClass, vundoDESTROY, (action));
  return;
}

/********
 * editCut is called whenever the Cut command is triggered in a viewer
 * dialog. Copies the current selection to the clipboard, then removes
 * the item references from the viewer's iconview. The items are
 * NOT destroyed since the action is undoable.
 *
 * -> com,     the cut command
 * -> context, the command's context
 * <- TRUE
 *********/
static int
editCut(vcommandFunction *com, vdict *context, int toclip) 
{
  viewer			*view;
  viconview			*iconview;
  vieweritem			*item;
  register viconviewIcon	*icon;
  cutAction			*cutAct;
  tarray			*a;
  viconviewView			*iconiconview;
  vdomainObjectSetIterator	iterator, *iter = &iterator;
  vdomainObjectSet		*set;
  tarray			*volatile a_v = NULL;
  vundoActionList		*volatile list_v = NULL;
  viewer			*volatile view_v;
  vdomainObjectSet		*volatile set_v = NULL;


  /* nuke last undoable (?!) */
  view_v = view = viewerFromContext(context);
  viewerCommitUndoables(view);

  /* remove selected items from the iconview */
  vexWITH_HANDLING
    {
      /* remember what was selected for future pastes; otherwise
       * leave the clip as-is */
      if (toclip) editSaveSelection(view);
      list_v = view->actions = vundoCreateActionList();

      /* create array of viewer items to keep track of the images
       * created for the paste. if user undoes and then redoes operation 
       * we DO NOT release or retrieve images; we use the original image
       * reference!*/
      iconiconview = viconviewGetIconView();
      iconview = viewerGetIconview(view);
      set_v = set = vdomainGetObjectSet(viconviewGetDomain(iconview), 
                vdomainviewGetSelection(viconviewGetDomainView(iconview)),
		vdomainSELECTED | vdomainMATCHFUNC | vdomainLOGICAL_AND, 
		viewerMatchOnlyImages);
      a_v = a = tarrayCreateSized(sizeof(vieweritem*),
				 vdomainGetObjectSetCount(set));

      /* add each item to array -- remember the item's tag, image and
       * position. we don't retrieve or release the image */
      vdomainInitObjectSetIterator(iter, set);
      while (vdomainNextObjectSetIterator(iter)) {
	icon = viconviewIconFromObject(vdomainGetObjectSetIteratorObject(iter));
	item = viewerGetIconItem(icon);
	if (!item->loaded) 
	  viewerLoadItem(view, icon); /*!?possible?!*/
	else if (item->editing)
	  viewerCommitImageEditor(view, item);
	tarrayAppendItem(a, &item);
      }
      vdomainDestroyObjectSetIterator(iter);
      vdomainDestroyObjectSet(set);
      set_v = NULL;

      /* create action that will add/remove icons from iconview, and
       * if action done, release images from the view's image store */
      cutAct = (cutAction*)vundoCreateActionOfClass(cutActionClass);
      cutAct->view  = view;
      cutAct->items = a;

      /* do action for 1st time, set state to done */
      vundoActAction((vundoAction*)cutAct);

      /* append to the action list */
      vundoAddActionListAction(view->actions, (vundoAction*)cutAct);
      vundoSetActionListName(view->actions, toclip ? titleCutAction : 
			     titleClearAction); 
      a_v = NULL;

      /* advance the list's state to DONE */
      vundoActActionList(view->actions);
    }

  /* if we've barfted for some reason, try to cleanup for a complete
   * recovery (yeh right)*/
  vexON_EXCEPTION
    {
      vdebugBE(vexDumpChain(vdebugGetWarningStream()));
      if (a_v)
	tarrayDestroy((tarray*)a_v);
      if (set_v)
	vdomainDestroyObjectSet((vdomainObjectSet*)set_v);
      if (list_v) 
	vundoDestroyActionList((vundoActionList*)list_v);
      view_v->actions = NULL;
      vexClear();
    }
  vexEND_HANDLING;


  /* update ui items to reflect new clip and/or undo */
  viewerUpdateUndoInterface((viewer*)view_v);
  if (toclip) editUpdateClipboardDependentInterface((viewer*)view_v);
  return vTRUE;
}

static int
editCopyThenCut(vcommandFunction *com, vdict *context)
{
  return editCut(com, context, vTRUE); /* use synthetic command? */
}

static int
editCutNoCopy(vcommandFunction *com, vdict *context)
{
  return editCut(com, context, vFALSE); /* use synthetic command? */
}


/*
 *+------------------------------------------------------------------------+
 * private command: removing selection AND all aliases. Has nothing to do 
 * with vclipboards! this is an internal fako-bako clipboard doohickum! 
 * Tests the removal command of the image manager.
 *+------------------------------------------------------------------------+
 */

static void
removeCheckClipSelection(viewer *view, register const vname *tag)
{
  register tarray	*a;
  register int		i;
  register vieweritem	*item;

  /* boink */
  if (!view->clipsel)
    return;

  /* !assumes the active image store's been set! */
  a = view->clipsel;
  for (i=tarrayGetNumber(a)-1; i>=0; i--) {
    item = tarrayAtAs(a, i, vieweritem*);
    if (tag == item->tag) {
      imanagerReleaseImage(iman, item->sniffed, item->tag);
      tarrayDeleteItem(a, i);
    }
    /* clip should never be empty */
    if (!tarrayGetNumber(a)) {
      tarrayDestroy(a);
      view->clipsel = NULL;
      editUpdateClipboardDependentInterface(view);
    }
  }
  return;
}

static void
removeRemoveIcons(viewer *view, tarray *a)
{
  register int			 max;
  register vieweritem		**scan, **stop;
  viconview			*iconview;
  vieweritem			**oscan;

  iconview = viewerGetIconview(view);
  imanagerSetActiveImageStore(iman, view->store);

  scan = tarrayAtStartAs(a, vieweritem**);
  stop = tarrayAtStopAs(a, vieweritem**);
  for (; scan<stop; scan++) {
    if ((*scan)->others) {
      oscan = tarrayAtStartAs((*scan)->others, vieweritem**);
      max   = tarrayGetNumber((*scan)->others);
      for (; max; max--, oscan++) {
	imanagerReleaseImage(iman, (*oscan)->sniffed, (*oscan)->tag);
	(*oscan)->pos = viconviewGetIconPosition((*oscan)->icon);
	viconviewRemoveIcon(iconview, (*oscan)->icon);
      }
    }
    imanagerReleaseImage(iman, (*scan)->sniffed, (*scan)->tag);
    (*scan)->pos = viconviewGetIconPosition((*scan)->icon);
    viconviewRemoveIcon(iconview, (*scan)->icon);
  }
  editRefreshSelection(view, NULL, iconview);

  return;
}

static void
removeAddIcons(viewer *view, tarray *a)
{
  register vieweritem		*item;
  vieweritem			**scan, **stop, **oscan;
  register int			 max;
  vdomainObjectSet		*set;
  viconview			*iconview;
  viconviewView			*iconiconview;
  vdomainObject			*iconobj, *nameobj;

  imanagerSetActiveImageStore(iman, view->store);
  iconview = viewerGetIconview(view);
  iconiconview = viconviewGetIconView();
  set = vdomainCreateObjectSet(NULL);

  scan = tarrayAtStartAs(a, vieweritem**);
  stop = tarrayAtStopAs(a, vieweritem**);
  for (; scan<stop; scan++) {
    if ((*scan)->others) {
      oscan = tarrayAtStartAs((*scan)->others, vieweritem**);
      max   = tarrayGetNumber((*scan)->others);
      for (; max; max--, oscan++) {
	item = *oscan;
	item->sniffed = imanagerRetrieveImage(iman, item->tag, NULL);
	vieweritemDetermineDisplayedImage(view, item, iconiconview);
	viconviewAddIcon(iconview, item->icon);
	viconviewSetIconPosition(item->icon, &item->pos);
	viconviewGetIconObjects(item->icon, &iconobj, &nameobj);
	vdomainAddToObjectSet(&set, iconobj);
      }
    }
    item = *scan;
    item->sniffed = imanagerRetrieveImage(iman, item->tag, NULL);
    vieweritemDetermineDisplayedImage(view, item, iconiconview);
    viconviewAddIcon(iconview, item->icon);
    viconviewSetIconPosition(item->icon, &item->pos);
    viconviewGetIconObjects(item->icon, &iconobj, &nameobj);
    vdomainAddToObjectSet(&set, iconobj);
  }

  /* select the inserted doohickies */
  editRefreshSelection(view, set, iconview);
  vdomainDestroyObjectSet(set);

  return;
}

static void
removeDestroyIcons(viewer *view, tarray *a, register int deep)
{
  register vieweritem	**scan, **stop;
  register vieweritem	**oscan;
  register int		  max;

  scan = tarrayAtStartAs(a, vieweritem**);
  stop = tarrayAtStopAs(a, vieweritem**);
  for (; scan<stop; scan++) {
    if ((*scan)->others) {
      if (deep) {
	oscan = tarrayAtStartAs((*scan)->others, vieweritem**);
	max   = tarrayGetNumber((*scan)->others);
	for (; max; max--, oscan++) {
	  viconviewDestroyIcon((*oscan)->icon);
	  vieweritemDestroy(*oscan);
	}
      }
      tarrayDestroy((*scan)->others);
    }
    if (deep) {
      viconviewDestroyIcon((*scan)->icon);
      vieweritemDestroy(*scan);
    }
  }
  return;
}

static int
removeLookup(register const vname *tag, tarray *a)
{
  register vieweritem 	**scan,**stop;
  int		         found = vFALSE;

  if (tarrayGetNumber(a)) {
    scan = tarrayAtStartAs(a, vieweritem**);
    stop = tarrayAtStopAs(a, vieweritem**);
    for (; scan<stop; scan++)
      if (tag == (*scan)->tag) {
	found = vTRUE;
	break;
      }
  }
  return found;
}

static void
removeGetOthers(viconviewIcon *primary, register const vname *tag, 
		tarray *a, viconview *iconview)
{
  register viconviewIcon	*icon;
  viconviewIterator		iterator;
  register viconviewIterator	*iter= &iterator;
  viconviewView			*iconiconview;
  vieweritem			*item;

  viconviewInitIterator(iter, iconview);
  iconiconview = viconviewGetIconView();
  while (viconviewNextIterator(iter)) {
    icon = viconviewGetIteratorIcon(iter);
    if ((icon!=primary) && (viewerGetIconItem(icon)->tag==tag)) {
      item = viewerGetIconItem(icon);
      tarrayAppendItem(a, &item);
    }
  }
  viconviewDestroyIterator(iter);
  return;
}

static void
removeDoAct(vundoAction *action)
{
  register removeAction *act = (removeAction*)action;
  switch (vundoGetActionState(action)) {

    /* ORIG action (1st time) */
    case vundoNEW: {
      act->dirty = viewerIsDirty(act->view);
      /* fall through */
    }

    /* REDO action */
    case vundoUNDONE: {
      removeRemoveIcons(act->view, act->items);
      viewerTouch(act->view, vTRUE);
      break;
    }

    /* UNDO action */
    case vundoDONE:   {
      removeAddIcons(act->view, act->items);
      if (!act->dirty) viewerTouch(act->view, vFALSE);
      break;
    }
  }
  vclassSendSuper(removeActionClass, vundoACT, (action));

  viewerUpdateDirtyDependentInterface(act->view);

  return;
}

static void
removeDestroy(vundoAction *action)
{
  register removeAction *act = (removeAction*)action;
  switch (vundoGetActionState(action)) {

    /* was DONE */
    case vundoDONE: {
      removeDestroyIcons(act->view, act->items, vTRUE);
      tarrayDestroy(act->items);
      break;
    }

    /* was UNDONE */
    case vundoUNDONE:   {
      removeDestroyIcons(act->view, act->items, vFALSE);
      tarrayDestroy(act->items);
      break;
    }
  }
  vclassSendSuper(removeActionClass, vundoDESTROY, (action));
  return;
}

static int
editRemoveAll(vcommandFunction *com, vdict *context)
{
  viewer			*view;
  viconview			*iconview;
  vieweritem			*item;
  register viconviewIcon	*icon;
  removeAction			*removeAct;
  vundoAction			*act;
  tarray			*a;
  viconviewView			*iconiconview;
  vdomainObjectSetIterator	iterator, *iter = &iterator;
  int				users;
  vieweritem			**scan, **stop;
  vdomainObjectSet		*set;
  tarray			*volatile a_v = NULL;
  vundoActionList		*volatile list_v = NULL;
  viewer			*volatile view_v;
  vdomainObjectSet		*volatile set_v = NULL;


  /* nuke last undoable (?!) */
  view_v = view = viewerFromContext(context);
  viewerCommitUndoables(view);

  /* remove selected items and all aliases from the iconview */
  vexWITH_HANDLING
    {
      /* our new action list: for each selected item we insert
       * a remove action and THEN a remove storeitem action --
       * in that order! */
      list_v = view->actions = vundoCreateActionList();

      /* create array of viewer items to keep track of the images
       * removed. if user undoes and then redoes operation we can
       * release and retrieve images; we use the original icon
       * reference!*/
      iconiconview = viconviewGetIconView();
      iconview = viewerGetIconview(view);
      set_v = set = vdomainGetObjectSet(viconviewGetDomain(iconview), 
                vdomainviewGetSelection(viconviewGetDomainView(iconview)),
		vdomainSELECTED | vdomainMATCHFUNC | vdomainLOGICAL_AND, 
		viewerMatchOnlyImages);
      a_v = a = tarrayCreateSized(sizeof(vieweritem*),
				  vdomainGetObjectSetCount(set));

      /* add each item to array -- remember the item's tag, image and
       * icon. we must also make sure we check the clipboard for items
       * we're about to remove. if the clipboard contains a reference
       * to an item, it should be removed from the clip's list! */
      imanagerSetActiveImageStore(iman, view->store);
      vdomainInitObjectSetIterator(iter, set);
      while (vdomainNextObjectSetIterator(iter)) {

	/* retrieve iconview item */
	icon = viconviewIconFromObject(vdomainGetObjectSetIteratorObject(iter));
	item = viewerGetIconItem(icon);
	if (!item->loaded)
	  viewerLoadItem(view, icon); /*!?possible?!*/
	else if (item->editing)
	  viewerCommitImageEditor(view, item);

	/* if not already included, process */
	if (!removeLookup(item->tag, a)) {
	  if (view->clipsel) removeCheckClipSelection(view, item->tag);
	  users = imanagerGetNumberOfImageUsers(iman, view->store, item->tag);
	  if (users==1)
	    item->others = NULL;
	  else {
	    item->others = tarrayCreateSized(sizeof(vieweritem*), users-1);
	    removeGetOthers(icon, item->tag, item->others, iconview);
	  }
	  tarrayAppendItem(a, &item);
	}
      }

      vdomainDestroyObjectSetIterator(iter);
      vdomainDestroyObjectSet(set);
      set_v = NULL;

      /* create action that will add/remove icons from iconview, and
       * if action done, destroy icons from iconview */
      removeAct = (removeAction*)vundoCreateActionOfClass(removeActionClass);
      removeAct->view = view;
      removeAct->items = a;

      /* do action for 1st time, set state to done. this removes the
       * items from the iconview -- not the image store! */
      vundoActAction((vundoAction*)removeAct);

      /* make remove-iconview-items 1st in the action list */
      vundoAddActionListAction(view->actions, (vundoAction*)removeAct);
      a_v = NULL;

      /* remove each item from the image store -- we have to do this AFTER
       * we've removed ALL the references to an image (otherwise the 
       * imanager generate "item-is-being-used" exceptions) */
      scan = tarrayAtStartAs(a, vieweritem**);
      stop = tarrayAtStopAs(a, vieweritem**);
      for (; scan<stop; scan++) {
	imanagerRemoveImageFromImageStoreUndoable(iman, view->store, 
                      (*scan)->tag, (void**)&act);
	vundoAddActionListAction(view->actions, act);
      }

      /* advance the list's state to DONE */
      vundoActActionList(view->actions);
      vundoSetActionListName(view->actions, titleRemoveAllAction);
    }

  /* if we've barfted for some reason, try to cleanup for a complete
   * recovery (yeh right)*/
  vexON_EXCEPTION
    {
      vdebugBE(vexDumpChain(vdebugGetWarningStream()));
      if (a_v) {
	vieweritem **oscan,**ostop;
	a = a_v;
	if (tarrayGetNumber(a)) {
	  scan = tarrayAtStartAs(a, vieweritem**);
	  stop = tarrayAtStopAs(a, vieweritem**);
	  for (; scan<stop; scan++) {
	    if ((*scan)->others) {
	      oscan = tarrayAtStartAs((*scan)->others, vieweritem**);
	      ostop = tarrayAtStopAs((*scan)->others, vieweritem**);
	      for (; oscan<ostop; oscan++)
		vieweritemDestroy(*oscan);
	      tarrayDestroy((*scan)->others);
	    }
	    vieweritemDestroy(*scan);
	  }
	}
	tarrayDestroy(a);
      }
      if (set_v)
	vdomainDestroyObjectSet(set_v);
      if (list_v) 
	vundoDestroyActionList(list_v);
      view_v->actions = NULL;
      vexClear();
    }
  vexEND_HANDLING;


  /* update ui items to reflect new clip and/or undo */
  viewerUpdateUndoInterface(view_v);
  return vTRUE;
}


/*
 *+------------------------------------------------------------------------+
 * private command: pasting contents of clipboards as a dictionary of
 * new images. Tests the image manager's paste-as-dict routines.
 *+------------------------------------------------------------------------+
 */

static int
editPasteAsGroup(vcommandFunction *com, vdict *context)
{
  register viewer		*view;
  register vieweritem		*scan, *stop;
  vieweritem			*item;
  pasteAction			*pasteAct;
  vundoAction			*act;
  tarray			*a;
  vdict				*dict;
  tarray			*volatile a_v = NULL;
  vundoActionList		*volatile list_v = NULL;
  viewer			*volatile view_v;
  vdict				*volatile dict_v = NULL;

  view = viewerFromContext(context);
  vdebugIF(!view->clipsel, vexGenerate(vexGetValueNullClass(), vexMESSAGE,
           "paste-group: command active when no selection?!", 
           vexERRNO, 0, vexNULL));

  /* if only one item in clip, then do as paste operation */
  if (tarrayGetNumber(view->clipsel)==1) {
    (void)editPaste(com, context);
    if (view->actions)
      vundoSetActionListName(view->actions, titlePasteAsGroupAction);
  }

  /* else do it */
  else {
    /* commit(make permanent) the last undoable */
    view_v = view;
    viewerCommitUndoables(view);

    /* add clip selection as a group instead of indivdually to store */
    vexWITH_HANDLING
      {
	/* new action list */
	list_v = view->actions = vundoCreateActionList();

	/* create array to keep track of iconview items during any
	 * undoooes and redoooes
	 */
	a_v = a = tarrayCreateSized(sizeof(vieweritem*), 
				    tarrayGetNumber(view->clipsel));

	/* create dictionary to hold COPIES of images in clip - we must
	 * explicitly clone the images since the paste operation doesn't work
	 * with store-references! */
	dict_v = dict = vdictCreate(vnameHashString);
	scan = tarrayAtStartAs(view->clipsel, vieweritem*);
	stop = tarrayAtStopAs(view->clipsel, vieweritem*);
	for (; scan<stop; scan++, view->last++) {
	  item = vieweritemAlloc();
	  item->sniffed = vimageClone(scan->sniffed);
	  do {
	    item->tag = vnameInternGlobalScribed(vnumScribeInt(view->last));
	    if (imanagerGetNumberOfImageUsers(iman, view->store, item->tag)
		<=0)
	      break;
	    view->last++;
	  }while(1);
	  item->name   = item->tag;
	  item->pos    = scan->pos;
	  item->loaded = vTRUE;
	  vdictStore(dict, item->tag, item->sniffed);
	  tarrayAppendItem(a, &item);
	}

	/* paste the dictionary o' image references into the viewer's
	 * image store -- insert 1st in action list */
	imanagerPasteImagesIntoImageStoreUndoable(iman, view->store, dict, (void**)&act);
	vundoAddActionListAction(view->actions, act);

	/* once we've done the paste, the store assumes ownership of 
	 * the images so we don't want to free 'em twice if failure after
	 * this point */
	vdictDestroy(dict);
	dict_v = NULL;

	/* create action that will add/remove icons from iconview */
	pasteAct = (pasteAction*)vundoCreateActionOfClass(pasteActionClass);
	pasteAct->view = view;
	pasteAct->items = a;
	pasteAct->deep = vTRUE;

	/* do action for 1st time, set state to done */
	vundoActAction((vundoAction*)pasteAct);

	/* append to action list -- done after imanager's stuff! */
	vundoAddActionListAction(view->actions, (vundoAction*)pasteAct);
	vundoSetActionListName(view->actions, titlePasteAsGroupAction);
	a_v = NULL;

	/* advance the list's state to DONE */
	vundoActActionList(view->actions);
      }
    vexON_EXCEPTION
      {
	vdebugBE(vexDumpChain(vdebugGetWarningStream()));
	if (a_v) {
	  a = a_v;
	  if (dict_v && tarrayGetNumber(a)) {
	    vieweritem **pscan, **pstop;
	    pscan = tarrayAtStartAs(a, vieweritem**);
	    pstop = tarrayAtStopAs(a, vieweritem**);
	    for (; pscan<pstop; pscan++) {
	      if ((*pscan)->sniffed) 
		vimageDestroy((*pscan)->sniffed);
	      vieweritemDestroy(*pscan);
	    }
	  }
	  tarrayDestroy(a);
	}
	if (dict_v)
	  vdictDestroy(dict_v);
	if (list_v) 
	  vundoDestroyActionList(list_v);
	view_v->actions = NULL;
	vexClear();
      }
    vexEND_HANDLING;

    viewerUpdateUndoInterface(view_v);
  }

  return vTRUE;
}


/*
 *+------------------------------------------------------------------------+
 * private: update an item's sniffed image. updates all references
 * (including any in the view's clip) to the new image. called by the
 * image editor.
 *+------------------------------------------------------------------------+
 */


/********
 * replaceSetItemImage
 *
 * ->
 * <-
 ********/
static void
replaceSetItemImage(viewer *view, vieweritem *item)
{
  /* zap any thumbnail images */ 
  if (item->thumbnail) {
    vimageDestroy(item->thumbnail);
    item->thumbnail = NULL;
    item->munged = vFALSE;
  }

  /* recalc the item's image for display */
  item->sniffed   = imanagerRetrieveImage(iman, item->tag, NULL);
  item->displayed = NULL;
  vieweritemDetermineDisplayedImage(view, item, viconviewGetIconView());
}

/********
 * replaceCheckClipSelection
 *
 * ->
 * <-
 ********/
static int
replaceCheckClipSelection(viewer *view, register const vname *tag)
{
  register tarray	*a;
  register int		i;
  register vieweritem	*item;
  int			atindex = -1;

  /* boink */
  if (!view->clipsel)
    return atindex;

  /* !assumes the active image store's been set! */
  a = view->clipsel;
  for (i=tarrayGetNumber(a)-1; i>=0; i--) {
    item = tarrayAtAs(a, i, vieweritem*);
    if (tag == item->tag) {
      imanagerReleaseImage(iman, item->sniffed, item->tag);
      atindex = i;
      break;
    }
  }
  return atindex;
}

/********
 * replaceSetClipImage
 *
 * ->
 * <-
 ********/
static void
replaceSetClipImage(viewer *view, int atindex)
{
  vieweritem *item;

  if (atindex>=0) {
    item = tarrayAtAs(view->clipsel, atindex, vieweritem*);

    if (item->sniffed==item->displayed)
      item->displayed = item->sniffed = 
	imanagerRetrieveImage(iman, item->tag, NULL);
    else
      item->sniffed = imanagerRetrieveImage(iman, item->tag, NULL);
  }
}


/********
 * vieweritemAcceptChangedImage
 *
 * ->
 * <-
 ********/
void
vieweritemAcceptChangedImage(viewer *view, vieweritem *item, 
			     vimage *newimage)
{
  vundoAction	*ignoredAction;
  tarray	*a;
  vieweritem 	**scan, **stop;
  int		clipindex;

  /* load up all the "others" referencing the primary tag */
  a = tarrayCreate(sizeof(vieweritem*));
  removeGetOthers(item->icon, item->tag, a, viewerGetIconview(view));
  tarrayAppendItem(a, &item);
  clipindex = replaceCheckClipSelection(view, item->tag);

  /* replace stored image associated w/ reference - this is
   * an undoable operation but we're going to ignore this
   * feature...*/
  imanagerSetActiveImageStore(iman, view->store);
  scan = tarrayAtStartAs(a, vieweritem**);
  stop = tarrayAtStopAs(a, vieweritem**);
  for (; scan<stop; scan++)
    imanagerReleaseImage(iman, (*scan)->sniffed, item->tag);

  imanagerAddImageToImageStoreUndoable
    (iman, view->store, newimage, item->tag, (void**)&ignoredAction);
  vundoDestroyAction(ignoredAction);

  /* replace all references to the item */
  scan = tarrayAtStartAs(a, vieweritem**);
  stop = tarrayAtStopAs(a, vieweritem**);
  for (; scan<stop; scan++)
    replaceSetItemImage(view, *scan);
  if (clipindex>=0)
    replaceSetClipImage(view, clipindex);

  /* something's changed */
  viewerTouch(view, vTRUE);
  tarrayDestroy(a);
}

/*
 *+------------------------------------------------------------------------+
 * private command: edit the selected image -> only one at a time!
 *+------------------------------------------------------------------------+
 */
static int
editOpenImageEditor(vcommandFunction *com, vdict *context)
{
  int			   dink = vFALSE;
  vdomainObjectSet	  *set;
  viewer		  *view = viewerFromContext(context);
  vdomainObjectSetIterator iter;
  viconviewIcon		  *icon;
  viconview		  *iconview;

  /* see how many items are selected */	
  iconview = viewerGetIconview(view);
  set = vdomainGetObjectSet(viconviewGetDomain(iconview), 
	    vdomainviewGetSelection(viconviewGetDomainView(iconview)),
	    vdomainSELECTED | vdomainMATCHFUNC | vdomainLOGICAL_AND, 
	    viewerMatchOnlyImages);
  dink = vdomainGetObjectSetCount(set)!=1;


  /* can only edit one thingy at a time */
  if (dink)
    isnfInformUser(msgCantOpenMultipleImages, viewerGetDialog(view));

  /* open for editing */
  else {
    vdomainInitObjectSetIterator(&iter, set);
    (void)vdomainNextObjectSetIterator(&iter);
    icon = viconviewIconFromObject(vdomainGetObjectSetIteratorObject(&iter));
    vdomainDestroyObjectSetIterator(&iter);
    viewerOpenImageEditor(view, icon);
  }

  /* bye */
  vdomainDestroyObjectSet(set);
  return vTRUE;
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

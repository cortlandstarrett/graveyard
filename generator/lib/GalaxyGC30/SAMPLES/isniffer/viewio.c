/* $Id: viewio.c,v 1.3 1996/08/21 15:52:23 david Exp $ */
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
 *                              viewer io commands                          *
 *                                                                          *
 ****************************************************************************
 */

/* for v*HEADER */
#include <vport.h>

/* ANSI headers */
#include vstdioHEADER
#include vstdlibHEADER
#include vmathHEADER /* for ceil() */

/* Galaxy headers */
#include vdebugHEADER
#include vexHEADER
#include vmemHEADER
#include vcharHEADER
#include vstrHEADER
#include vnameHEADER
#include vdictHEADER
#include vfsHEADER
#include vdrawHEADER
#include vobjectHEADER
#include vclassHEADER
#include vcommandHEADER
#include vprintHEADER
#include vwindowHEADER
#include vdialogHEADER
#include viconviewHEADER
#include vfilechsrHEADER
#include vnumHEADER

/* Our headers */
#include "iman.h"
#include "tstack.h"
#include "tarray.h"
#include "names.h"
#include "isnf.h"
#include "utils.h"
#include "view.h"
#include "viewpriv.h"

/*
 *+------------------------------------------------------------------------+
 * private constants, variables, prototypes
 *+------------------------------------------------------------------------+
 */

#define fcmdsPRINT_STYLE 2
#define pathLEAF(_path) vfsGetPathElementAt((_path), \
    vfsGetPathElementCount((_path))-1)

static int 	fileSave(vcommandFunction*,vdict*);
static int 	fileSaveAs(vcommandFunction*,vdict*);
static int 	fileRevert(vcommandFunction*,vdict*);
static int 	filePrint(vcommandFunction*,vdict*);
static int 	fileConfirmPrintSetup(vcommandFunction*,vdict*);
static void	printSendJobThenNukePrinter(vprint*,int);
static void	printSaveStyleThenNukePrinter(vprint*,int);
static void	printDoPageAdornments(viewer*,vprint*,viewerPrintJob*);
static void	printDoPageContents(viewer*,vprint*,viewerPrintJob*);

static appFunctionCmd fcmds[]= {
  {{appNAME_ACT_SAVE,1,0, vkeyNULL_STROKE}, fileSave, NULL},
  {{appNAME_ACT_SAVE_AS,1,1, vkeyNULL_STROKE}, fileSaveAs, NULL},
  {{appNAME_ACT_CONFIRM_PRINTSTYLE, 1,0, vkeyNULL_STROKE}, 
     fileConfirmPrintSetup, NULL}, /* !must be 2! */
  {{appNAME_ACT_PRINT, 1,1, vkeyNULL_STROKE}, filePrint, NULL},
  {{appNAME_ACT_REVERT, 1,0, vkeyNULL_STROKE}, fileRevert, NULL},
  {{-1},NULL,NULL}
};

static vstr	*pageLabelTemplate;
static vstr	*pageNoTemplate;
static vimage	*pageImage = NULL;
static vfont	*pageDefaultFont;



/********
 * viewerFileStartup, viewerFileShutdown
 *
 * ->
 * <-
 ********/
void
viewerFileStartup(isnifferApp *app)
{
  pageLabelTemplate = isnfStrFrom(strPageLabelTemplate);
  pageNoTemplate    = isnfStrFrom(strPageNoTemplate);
  pageDefaultFont   = vfontFindScribed
    (vcharScribeLiteral("font:helvetica-face:medium-size:10"));
}

void
viewerFileShutdown(void)
{
#if (vmemBALANCE)

  if (pageLabelTemplate)
    vstrDestroy(pageLabelTemplate);
  if (pageNoTemplate)
    vstrDestroy(pageNoTemplate);

  if (pageImage)
    vimageDestroy(pageImage);

#endif
}


/********
 * viewerFileAttachCommands is called to attach dialog-level i/o
 * commands to a viewer dialogue's space.
 *
 * -> view, the viewer
 * <- void
 ********/
void
viewerFileAttachCommands(register viewer *view)
{
  /* Turn on print style stuff if ok (if no dialog at all, it's
   * inappropriate to have the item in the ui since we just use
   * the defaults) */
  if (isnfStyleConfirmationIsAvailable())
    fcmds[fcmdsPRINT_STYLE].cmd.statevalue = vTRUE;

  appAddFunctionsToCommandSpaceDescription(&view->aspace, fcmds);
  return;
}

/****************************************************************************
 *                                                                          *
 *                            viewer save commands                          *
 *                                                                          *
 ****************************************************************************
 */


/* Define our debug tag for vdebug manager */
#if vdebugDEBUG
static const char *const _savecmdsTag = "viewer-save-commands";
#define vdebugTAG _savecmdsTag
#endif


/********
 * viewerSaveFile is called by the delayed event handler.
 * we delay saving the file 'til after the file chooser
 * has been dismissed (this works well w/ system modal 
 * native choosers too).
 *
 * -> event, our client event
 * <- TRUE
 ********/
static int
viewerSaveFile(vevent *event)
{
  viewer	*view;

  /* actual saving */
  view = (viewer*)veventGetClientData(event);
  viewerSave(view);
  view->save = vTRUE;
  view->ignoresave = vFALSE;

  /* reflect to user we got it */
  viewerSetTitle(view);

  return vTRUE;
}

/********
 * viewerSetPermFileAndSaveLater is called by the file chooser
 * when the user selects a file (hits OK). posts an event to 
 * do the actual opening after the chooser's been dismissed.
 *
 * -> filechsr, the file chooser
 * -> path,     the full path to the user's selection
 * <- void
 ********/
static int
viewerSetPermFileAndSaveLater(vfilechsr *chsr, vfsPath *path)
{
  vfsPath	*dir;
  int		 ok;
  viewer	*view;

  view  = (viewer*)vfilechsrGetData(chsr);
  dir   = vfsClonePath(path);
  vfsTruncatePath(dir, 1);

  /* Make sure we can save to this directory */
  if ((ok=vfsAccess(dir, vfsCAN_READ|vfsCAN_WRITE))) {

    /* save the name of the permanent file */
    if (view->perm)
      vfsDestroyPath(view->perm);
    view->perm = vfsClonePath(path);

    /* actually save after dismiss chooser */
    viewerInstallDelayHandler(viewerSaveFile, view);
  }
  else 
    isnfInformUser(msgSelectedDirectoryNotWritable, 
		   vfilechsrGetDialog(chsr));

  vfsDestroyPath(dir);

  return ok;
}

/********
 * viewerSaveTo is called to display the save file chooser for
 * a sniffed file. note the new path becomes the file's perm
 * file. doesn't return until user hits OK or cancel's operation.
 *
 * -> view, the viewer
 * <- void
 ********/
void
viewerSaveTo(viewer *view)
{
  isnifferApp	*app;
  vdialog	*dialog;
  vstr		*title;
  viewer	*volatile view_v;

  view_v = view;

  vexWITH_HANDLING
    {
      /* if first time, allocate new put file chooser */
      if (!saveChsr) {
	app = isnfGet();

	saveChsr = vfilechsrCreate();
	vfilechsrSetType(saveChsr, vfilechsrPUT);
	vfilechsrSetApply(saveChsr, viewerSetPermFileAndSaveLater);

	/* specific title since we got 2 choosers */
	dialog = vfilechsrGetDialog(saveChsr);
	title = isnfStrFrom(strTitlePutChsr);
	vfilechsrSetTitle(saveChsr, title);
	vstrDestroy(title);

	/* place wrt. to the viewer's dialogue */ 
	vfilechsrPlace(saveChsr, view->dialog, 
		       vrectPLACE_CENTER, vrectPLACE_CENTER);
	vfilechsrSetLeader(saveChsr, vdialogGetWindow(view->dialog));

	/* we must set the chooser's data field BEFORE opening it! */
	vfilechsrSetData(saveChsr, view);

	/* open by default in our writable directory */
	vfilechsrSetDirectory(saveChsr, writableDirectory);
      }
      else {
	/* we must set the chooser's data field BEFORE opening it! */
	vfilechsrSetData(saveChsr, view);
	dialog = vfilechsrGetDialog(saveChsr);
      }

      /* tell the application we're doing sumthin' */
      isnfBlock(dialog);
      vwindowUnblock(vdialogGetWindow(dialog));

      /* block until they dismiss the chooser */
      (void)vfilechsrProcess(saveChsr);
    }

  /* well poop; not a fatal error though(!?!) */
  vexON_EXCEPTION
    {
      vdebugBE(vexDumpChain(vdebugGetWarningStream()));
      vexClear();
      isnfInformUser(msgCantOpenSaveToChooser, view_v->dialog);
    }
  vexEND_HANDLING;


  /* cleanup */
  isnfUnBlock();
  return;
}

/********
 * viewerSave is called to save a viewer's images to a permanent
 * file. if the user hasn't saved before, works through 
 * viewerSaveTo above.
 *
 * -> view, the viewer
 * <- void
 ********/
void
viewerSave(viewer *view)
{
  viewer *volatile view_v;

  /* if we don't have a permanent home git one */
  if (!view->perm) {
    viewerSaveTo(view);
  }

  /* save changes to resource file */
  else {
    view_v = view;
    vexUNWIND_PROTECT
      {
	imanagerSaveImageStore(iman, view->store);
	viewerSaveToPermanentFile(view);
	viewerSwitchFileIcon(view, appname_OpenedPermFileIcon);
      }
    vexON_UNWIND
      {
	view_v->dirty = vFALSE;
	if (vexGetRootException()) {
	  vdebugBE(vexDumpChain(vdebugGetWarningStream()));
	  vexClear();
	}
      }
    vexEND_UNWIND;
  }
  return;
}

/********
 * viewerSaveToPermanentFile does the actual file system operations
 * to save the viewer's images to the temporary resource file. Note
 * the temporary file itself is NOT moved to the permanent file.
 * Used by viewerSaveTo and viewerSave.
 *
 * -> view, the viewer
 * <- void
 ********/
void
viewerSaveToPermanentFile(register viewer *view)
{
  viewer		*volatile view_v;
  register vresource	dst;
  vresource		volatile dst_v;

  vdebugIF((!view->temp || !view->perm), vexGenerate(vexGetArgNullClass(),
           vexMESSAGE, "viewer-save: temp or perm file is NULL!", 
           vexERRNO, 0, vexNULL));

  view_v  = view;
  dst_v   = vresourceNULL;

  vexUNWIND_PROTECT
    {
      if (vfsAccess(view->perm, vfsFILE_EXISTS))
	vfsRemove(view->perm); /* !?ack?! */
      dst_v = dst = viewerNewTypedFile(view->perm, viewerFileMASK);
      vresourceCopyCompact(view->root, dst);
      vresourceCloseFile(dst);
      dst_v = vresourceNULL;
      view->save = vFALSE;
      view->ignoresave = vTRUE;
    }
  vexON_UNWIND
    {
      if (dst_v!=vresourceNULL) {
	vresourceCloseFile(dst_v);
	vfsRemove(view_v->perm);
      }
      if (vexGetRootException()) {
	vdebugBE(vexDumpChain(vdebugGetWarningStream()));
	isnfInformUser(msgCantSaveFileWellPoop, NULL);
	vexClear();
      }
    }
  vexEND_UNWIND;
  return;
}

/********
 * viewerMoveTempFileToPermanentFile moves the viewer's temporary
 * file to its where the permanent reference .
 *
 * -> view, the viewer
 * <- void
 ********/
void
viewerMoveTempFileToPermanentFile(register viewer *view_)
{
  viewer *volatile view = view_;

  vdebugIF((!view->temp || !view->perm), vexGenerate(vexGetArgNullClass(),
           vexMESSAGE, "viewer-move: temp or perm file is NULL!", 
           vexERRNO, 0, vexNULL));
  /*
   * On some platforms, a cross-device move will fail. we prepare
   * for this by wrapping w/ specific exception handler...note 
   * there ain't much we can do now except not nuke the temp file.
   */
  vexWITH_HANDLING
    {
      vfsRename(view->temp, view->perm);
    }
  vexON_EXCEPTION
    {
      if (vfsGetException()) {  /* voops... */
	vdebugBE(vexDumpChain(vdebugGetWarningStream()));
	isnfInformUser(msgCantSaveFileWellPoop, NULL);
	vexClear();
      }
      else
	vexPropagate(vexGetAppClass(), vexMESSAGE, "cannot move "
		     "temp file to perm file", vexERRNO, 0, vexNULL);
    }
  vexEND_HANDLING;

  vfsDestroyPath(view->temp);
  view->temp = NULL;
  vfsDestroyPath(view->perm);
  view->perm = NULL;
  return;
}

/********
 * fileSaveAs
 *
 * ->
 * <-
 ********/
static int
fileSaveAs(vcommandFunction *com, vdict *context)
{
  viewer *view;
  view = viewerFromContext(context);
  viewerSaveTo(view);
  return vTRUE;
}

/********
 * fileSave
 *
 * ->
 * <-
 ********/
static int
fileSave(vcommandFunction *com, vdict *context)
{
  register viewer *view;

  view = viewerFromContext(context);
  vdebugIF((view->perm && !view->dirty), vexGenerate(vexGetValueClass(), 
           vexMESSAGE,"save-file: command active when file not changed", 
           vexERRNO, 0, vexNULL));

  /* if we don't have a permanent home git one */
  if (!view->perm) {
    viewerSaveTo(view);
  }

  /* save changes to resource file */
  else {
    viewerCommitUndoables(view);
    viewerSave(view);
    viewerUpdateUndoInterface(view);
    viewerUpdateDirtyDependentInterface(view);
  }

  return vTRUE;
}


/********
 * fileRevert
 *
 * ->
 * <-
 ********/
static int
fileRevert(vcommandFunction *com, vdict *context)
{
  viewer *view = viewerFromContext(context);
  isnfInformUser(msgFeatureUnimplemented, viewerGetDialog(view));
  return vTRUE;
}



/********
 * viewerNewTypedFile
 *
 * ->
 * <-
 ********/

vresource
viewerNewTypedFile(vfsPath *path, vfsMode mood)
{
  vresource resfile;
  resfile = vresourceCreateFile(path, mood);
  return resfile;
}

/****************************************************************************
 *                                                                          *
 *                            viewer print commands                         *
 *                                                                          *
 ****************************************************************************
 */

#define USERSPACE_DPI_H    72.0
#define USERSPACE_DPI_V    72.0

#define MIN_V_INFO_SIZE	   29.0
#define MAX_V_INFO_SIZE    40.0


/********
 * printPrepareJob
 * 
 * -> view,    the viewer
 * -> printer, 
 * -> info,    [filled-in]
 * <- [t/f],   true if stuff to print in job
 ********/
static int
printPrepareJob(viewer *view, vprint *printer, viewerPrintJob *job)
{
  unsigned short on1Page;
  int		 objectcount;
  float		 d;

  /* if nuthin' to print */
  objectcount = viconviewGetIconCount(viewerGetIconview(view));
  if (!objectcount)
    return vFALSE;


  /* phffht */
  if (job->prefs.extra && !pageImage) {
    vresource res;
    res = vresourceGet(isnfGet()->resources, appname_GlassImage);
    pageImage = vimageLoad(res);
  }

  /* standard page layout only adjusts for a user-defined
     margin (see preferences) */
  job->page    = *vprintGetPage(printer);
  job->page.y += job->prefs.pvm;
  job->page.x += job->prefs.phm;
  job->page.h -= 2*(int)job->prefs.pvm;
  job->page.w -= 2*(int)job->prefs.phm;


  /* account for a border and other print preferences */
  job->content = job->page;

  /* -> a. border */
  if (job->prefs.border) {
    d = job->prefs.linewidth;
    job->content.x += d,   job->content.y += d;
    job->content.w -= 2*d, job->content.h -= 2*d;
  }

  /* -> b. header or footer */
  if (job->prefs.number || job->prefs.extra) {
    vfont *font = job->prefs.font ? job->prefs.font : pageDefaultFont;
    d = vfontHeight(font)+vfontDescent(font);
    if (job->prefs.extra)
      d = vMAX(d, vimageGetHeight(pageImage));
    d += job->prefs.linewidth+2;

    if (d<MIN_V_INFO_SIZE) d = MIN_V_INFO_SIZE;
    else 
    if (d>MAX_V_INFO_SIZE) d = MAX_V_INFO_SIZE;

    job->extra      = job->content;
    job->extra.h    = d;
    job->content.h -= d;

    if (job->prefs.header)
      job->extra.y   += job->content.h;
    else
      job->content.y += d;
  }

  /* determine number of items per page -- rather simplistic
   * algorithm: we stuff an equal number thumbnails on each
   * page until we run out of images... */
  job->iw = view->thumbsize.x + 2*job->prefs.ihm;
  job->ih = view->thumbsize.y + 2*job->prefs.ivm;

  job->across = (unsigned short)(job->content.w/(float)job->iw);
  if (!job->across) job->across = 1; /*!?! - small page! */

  job->down = (unsigned short)(job->content.h/(float)job->ih);
  if (!job->down) job->down = 1;     /* !?!- small page! */

  on1Page = job->across*job->down;
  job->numpages = (unsigned short)objectcount/on1Page;

  if (!job->numpages)
    job->numpages = 1;

  /* now center the content rect horizontally on the page by offseting
   * x coordinate -- no need to adjust the width since the "across"
   * count will stop the drawing */
  job->content.x += (job->content.w-(float)((int)job->across*(int)job->iw))/2.;
  
  
  /* let's start at the very beginning...a very good place
   * to start. when you read you begin with A-B-C. A-B-C. when you
   * sing you begin with Do-Re-Me. Do-Re-Me. the first three
   * notes just happen to be ... Do-Re-Me ... ugh ... oh sorry
   * i wandered. the page number range should be adjusted by
   * the vprintConfirmJob notification handler */
  job->at     = 0;
  job->start  = 0;
  job->stop   = job->numpages;

  return vTRUE;
}


/********
 * printMakePrinter
 *
 * ->
 * <-
 ********/
static vprint *
printMakePrinter(viewer *view)
{
  register vprint *printer;

  /*
   * See if we've saved general print style information 
   * (applies to all jobs) for this view.
   */
  if (view->printstyle){
    vresource res = vresourceGet(view->root, appname_PrintStyleInfo);
    printer = vprintLoad(res);
  }
  /* 
   * Nope. use default print style (preferences)
   */
  else {
    printer = vprintCreate();
  }

  /*
   * Associate w/ single view...
   */
  view->printer = printer;
  vprintSetData(printer, view);

  /*
   * Job and Style callbacks (used by style and job confirmation
   * dialogs)
   */
  vprintSetJobNotify(printer, printSendJobThenNukePrinter);
  vprintSetStyleNotify(printer, printSaveStyleThenNukePrinter);

  return printer;
}


/********
 * printNukePrinter
 *
 * -> event, the client event we posted
 * <- vTRUE
 ********/
static int
printNukePrinter(vevent *event)
{
  vprint *printer = (vprint*)veventGetClientData(event);

  vprintDestroy(printer);
  return vTRUE;
}


/********
 * printSendJobThenNukePrinter
 *
 * ->
 * <-
 ********/
static void
printSendJobThenNukePrinter(vprint *printer, int good)
{
  viewer  	*view = (viewer*)vprintGetData(printer);
  viewerPrintJob job;

  /* only if the user confirmed the job (automatic on platforms
   * that don't have a confirm-job dialog */

  if (good) {
    job.prefs = isnfGetPreferences()->pp; /* should this be per view? */
    if (printPrepareJob(view, printer, &job))
      viewerPrint(view, printer, &job);
  }

  view->printer = NULL;
  viewerInstallDelayHandler(printNukePrinter, printer);
}


/********
 * printSaveStyleThenNukePrinter
 *
 * ->
 * <-
 ********/
static void
printSaveStyleThenNukePrinter(vprint *printer, int good)
{
  viewer *volatile view_v = (viewer*)vprintGetData(printer);

  /* Only if user confirmed the style change (automatic on platforms
     that don't have a style confirmation dialog) */
  if (good)
    vexWITH_HANDLING
      {
	vprintStore(printer, vresourceMake(view_v->root,appname_PrintStyleInfo));
	view_v->printstyle = vTRUE;
      }
    vexON_EXCEPTION
      {
	vdebugBE(vexDumpChain(vdebugGetWarningStream()));
	vexClear();
	isnfInformUser(msgCantSavePrintStyle, view_v->dialog);
      }
    vexEND_HANDLING;

  viewerInstallDelayHandler(printNukePrinter, view_v->printer);
  view_v->printer = NULL;
}



/********
 * viewerPrint
 *
 * -> view,    the viewer
 * -> printer, the printer 
 * <- void
 ********/
void
viewerPrint(viewer *volatile view, vprint *volatile printer, 
	    viewerPrintJob *volatile job)
{
  viconview			*iconview;
  viconviewIterator		 iterator;
  viconviewIterator		*volatile iter = &iterator;
  vbool				 volatile redRum;
  vbool				 volatile opened;

  /* nuthin to print */
  if (job->at>=job->numpages)
    return;

  /* indicatte we're doing sumthin', open document */
  isnfBlock(NULL);
  vdrawGSave();
  vprintSetSpool(printer, vTRUE);
  vprintOpenDocument(printer);


  /* our page contents are determined (rather arbitrarily) by
   * the iconview's object iterator -- it is not based on visual
   * location of the images in the viewer!*/
  iconview = viewerGetIconview(view);
  viconviewInitIterator(iter, iconview);


  /* make sure we're starting from the correct item wrt. the starting 
   * page number */
  job->iter = iter;
  if (job->start) {
    register int skip = job->start*job->across*job->down;
    while (skip--)
      (void)viconviewNextIterator(iter);
  }

  /* setup the page-size that all pages will use */
  vprintSetPage(printer, &job->page);

  /* print each page, make sure we cleanup if something dies... */
  redRum = vFALSE;
  for (opened = vFALSE, job->at=job->start; job->at<job->stop && !redRum; 
       opened = vFALSE, job->at++) {
    vdrawGSave();
    vexUNWIND_PROTECT 
      {
	vprintOpenPage(printer), opened = vTRUE;
	vdrawSetLineWidth(1);

	printDoPageAdornments(view, printer, job);
	printDoPageContents(view, printer, job);
      }
    vexON_UNWIND 
      {
	if (opened)
	  vprintClosePage(printer);
	if (vexGetRootException()) {
	  vdebugBE(vexDumpChain(vdebugGetWarningStream()));
	  redRum = vTRUE;
	}
      } 
    vexEND_UNWIND;
    vdrawGRestore();
  }

  /* nuke these */
  viconviewDestroyIterator(iter);

  /* close document, clear blockage... */
  vprintCloseDocument(printer);
  vdrawGRestore();
  isnfUnBlock();
}


/********
 * printDoPageAdornments
 *
 * ->
 * <-
 ********/
static void
printDoPageAdornments(viewer *view, vprint *printer, viewerPrintJob *job)
{
  int		 lineW, lineH;
  vfont		*font;
  vchar		 numchars[11]; /* !!allows more than 99999 thingies!! */
  float		 w, wleft;
  vstr		*s;

  vdrawGSave(); /* !-> we clip <-! */
  lineW = vdrawGetLineWidth();

  vdrawSetColor(vcolorGetBlack());
  vdrawSetLineWidth(job->prefs.linewidth);

  /* border around the entire page */
  if (job->prefs.border)
    vdrawFRectsStroke(&job->page, 1);

  /* extra goodies to show more printing stuff */
  if (job->prefs.number || job->prefs.extra)
    {
      font = job->prefs.font ? job->prefs.font : pageDefaultFont;
      vdrawSetFont(font);
      lineH = vfontHeight(font)+vfontDescent(font);

      /* always the page number to the right o' extra */
      (void)vcharCopyScribed(vnumScribeUInt(job->at), numchars);
      s = isnfReplaceMulti(pageNoTemplate, numchars, NULL);
      w = vfontStringWidthX(font, s) + isnfH_ITEM_MARGIN;
      if (w>job->page.w) w = job->page.w;

      vdrawFMoveTo(job->extra.x+job->extra.w-w,
		   job->extra.y+(job->extra.h-lineH)/2);
      vdrawShow(s);
      vstrDestroy(s);


      /* draw a line to differentiate the header/footer block; do
       * this here since we clip below */
      vdrawSetLineWidth(lineW);
      if (job->prefs.header)
	vdrawFMoveTo(job->extra.x, job->extra.y);
      else
	vdrawFMoveTo(job->extra.x, job->extra.y+job->extra.h);
      vdrawFRLineTo(job->extra.w, 0);
      vdrawStroke();


      /* if extra, include the number of objects and file name */
      wleft = job->page.w-w-isnfH_ITEM_MARGIN;
      if (job->prefs.extra && (wleft>vimageGetWidth(pageImage))) {
	const vchar *filename;
	int         objectcount;

	/* make sure we don't spooge on any other area */
	job->extra.w  = wleft-isnfH_ITEM_MARGIN;
	job->extra.x += isnfH_ITEM_MARGIN;
	vdrawFRectsClip(&job->extra, 1);

	/* calculate a string based on filename and # sniffed images */
	objectcount = viconviewGetIconCount(viewerGetIconview(view));
	filename = view->save ? pathLEAF(view->perm) : pathLEAF(view->temp);
	(void)vcharCopyScribed(vnumScribeLong(objectcount), numchars);
	s = isnfReplaceMulti(pageLabelTemplate, filename, numchars, NULL);

	/* draw the "sniffed" image leftmost, then the string */
	vdrawFMoveTo(job->extra.x,
		     job->extra.y+(job->extra.h-vimageGetHeight(pageImage))/2);
	vdrawImageIdent(pageImage);
	vdrawFMoveTo(job->extra.x+vimageGetWidth(pageImage)+isnfH_ITEM_MARGIN,
		     job->extra.y+(job->extra.h-lineH)/2);
	vdrawShow(s);
	vstrDestroy(s);
      }
      /* ack...finally */
    }

  vdrawGRestore();
}

/********
 * printDoPageContents
 *
 * ->
 * <-
 ********/
static void
printDoPageContents(viewer *view, vprint *printer, viewerPrintJob *job)
{
  int		r,c;
  float		x,y;
  vbool		redRum;
  vieweritem	*item;

  /* for each row, draw a line of image thumbnails */
  for (y=job->content.y+job->content.h, r=0, redRum=vFALSE; 
       r<(int)job->down && !redRum; r++) {

    /* position wrt to row, column = 1st */
    y -= job->ih;
    x  = job->content.x;

    /* for each column, draw items */
    for (c=0; c<(int)job->across && !redRum; c++, x += job->iw) {

      /* any more (maybe no if less than an entire page) */
      if (!viconviewNextIterator(job->iter)) {
	redRum = vTRUE;
	break;
      }

      /* draw image in slot */
      vdrawFMoveTo(x+job->prefs.ihm, y+job->prefs.ivm);
      item = viewerGetIconItem(viconviewGetIteratorIcon(job->iter));
      if (!item->loaded)
	viewerLoadItem(view, viconviewGetIteratorIcon(job->iter));
      if (item->thumbnail)
	vdrawImageIdent(item->thumbnail);
      else
	vdrawImageIdent(item->sniffed);
    }
  }/*each*/
}

/********
 * viewerConfirmPrintJob
 * can be called from viewer's ui or mainview's ui!
 *
 * #a# see description of isnfPrintConfirmationIsAvailable
 *
 * ->
 * <-
 ********/
void
viewerConfirmPrintJob(viewer *view)
{
  vprint *printer;

  vdebugTraceEnter(viewerConfirmPrintJob);

  isnfBlock(NULL);
  isnfInformUserByMessageBoxImmediately(msgPrintingThumbnails);
  printer = printMakePrinter(view);

  if (isnfPrintConfirmationIsAvailable()) /* #a# */
    vprintConfirmJob(printer);
  else
    printSendJobThenNukePrinter(printer, vTRUE);

  isnfUnBlock();
  vdebugTraceLeave();
}

/********
 * viewerConfirmPrintStyle
 * can be called from either viewer ui or mainview's ui!
 *
 * #a# see description of isnfStyleConfirmationIsAvailable
 *
 * ->
 * <-
 ********/
void
viewerConfirmPrintStyle(viewer *view)
{
  vprint *printer;

  vdebugTraceEnter(viewerConfirmPrintStyle);

  isnfBlock(NULL);
  printer = printMakePrinter(view);

  if (isnfStyleConfirmationIsAvailable()) /* #a# */
    vprintConfirmStyle(printer);
  else
    printSaveStyleThenNukePrinter(printer, vTRUE);

  isnfUnBlock();
  vdebugTraceLeave();
}

/********
 * filePrint
 *
 * ->
 * <-
 ********/
static int
filePrint(vcommandFunction *com, vdict *context)
{
  viewer *view;
  view = viewerFromContext(context);
  viewerConfirmPrintJob(view);
  return vTRUE;
}

/********
 * fileConfirmPrintSetup
 *
 * ->
 * <-
 ********/
static int
fileConfirmPrintSetup(vcommandFunction *com, vdict *context)
{
  viewer *view;
  view = viewerFromContext(context);
  viewerConfirmPrintStyle(view);
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

/********
 * xspam()
 *
 * ->
 * <-
 ********/

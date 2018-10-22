/* $Id: snoop.c,v 1.2 1996/08/21 15:52:23 david Exp $ */
/****************************************************************************
 *               (c) Copyright 1991-1994 Visix Software, Inc.               *
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
 *     Handles the main sniffer dialog and feedback while files are being   *
 *     snooped. Passes snooped images unto viewers.                         *
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

/* for v*HEADER */
#include <vport.h>

/* ANSI headers */
#include vstdioHEADER
#include vstdlibHEADER
#include vstdargHEADER

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
#include vkeyHEADER
#include veventHEADER
#include vclassHEADER
#include vobjectHEADER
#include vclientHEADER
#include vstdHEADER

#include vprefHEADER
#include vwindowHEADER
#include vdialogHEADER
#include vcommandHEADER
#include vfilechsrHEADER
#include vapplicationHEADER

/* Our headers */
#include "tstack.h"
#include "tarray.h"
#include "names.h"
#include "geticons.h"
#include "statitem.h"
#include "isnf.h"
#include "utils.h"
#include "com.h"
#include "statwin.h"
#include "view.h"
#include "snoop.h"


/* Define our debug tag for vdebug manager */
#if vdebugDEBUG
static const char *const _snooperTag = "snooper";
#define vdebugTAG _snooperTag
#endif



/*
 *+------------------------------------------------------------------------+
 * private constants, variables, prototypes
 *+------------------------------------------------------------------------+
 */
enum {
  comTOGGLE_RECURSION,		/* snoop recusively */
  comTOGGLE_CHECK_ALL		/* snoop all resource types */
};

enum {
  optionRECURSIVE = 0x01,
  optionALL = 0x02
};

typedef struct snooper {
  const vstr	*filepath;	/* pathname of source snoop file */
  statusgraphic	*graphic;	/* user feedback dialogue */
  int		 imagecount;	/* number of images found */
  unsigned	 options;	/* options used to snoop file */
}snooper;


static vbool		initialized = vFALSE;
static vbool		terminated = vFALSE;
static vfilechsr	*chsr = NULL;
static tarray		*snoopers = NULL;


/* >> must be before command initializers << */
static void		snooperDoIt(isnifferApp*,const vfsPath*);
static void		snooperProcessBatch(const vchar*,int,...);
static int		snooperGetNumber(void);
static void	        snooperCreate(const vchar*);
static void		snooperDestroy(const vchar*,unsigned int);
static snooper	       *snooperLocate(const vchar*,unsigned int,int*);
static int		snooperAcceptFile(vfilechsr*,vfsPath*);
static int		snooperLetUserChoose(vcommandFunction*,vdict*);
static int		snooperSuspend(vcommandFunction*,vdict*);
static int		snooperResume(vcommandFunction*,vdict*);
static int		snooperSetSnoopOption(vcommandSelector*,vdict*);
static int		snooperAcceptExternFile(vcommandFunction*,vdict*);
static vcommandSelectorClass *getselectorClass(void);

static appFunctionCmd fcmds[]= {
  {{appNAME_ACT_SNOOP,   1,1, vkeyNULL_STROKE}, snooperLetUserChoose, NULL},
  {{appNAME_ACT_SUSPEND, 1,0, vkeyNULL_STROKE}, snooperSuspend, NULL},
  {{appNAME_ACT_RESUME,  1,0, vkeyNULL_STROKE}, snooperResume, NULL},
  {{appNAME_ACT_OPEN,    1,0, vkeyNULL_STROKE}, snooperAcceptExternFile, NULL},
  {{-1},NULL}
};

static appSelectorCmd scmds[]= {
  {{appNAME_ACT_DO_RECUR, 0,0, vkeyNULL_STROKE}, comTOGGLE_RECURSION},
  {{appNAME_ACT_DO_ALL,   0,0, vkeyNULL_STROKE}, comTOGGLE_CHECK_ALL},
  {{-1}}
};


/*
 *+------------------------------------------------------------------------+
 * exported routines
 *+------------------------------------------------------------------------+
 */
/********
 * isnfStartupSnooperManager initializes the snooper module.
 * basically adds its toplevel commands to the application's 
 * command space.
 *
 * -> app, the application
 * <- void
 *********/
void
isnfStartupSnooperManager(isnifferApp *app)
{
  if (!initialized) {
    appAddSelectorsToCommandSpaceDescription(isnfGetCommandSpaceDescription(),
                     scmds, getselectorClass());
    appAddFunctionsToCommandSpaceDescription(isnfGetCommandSpaceDescription(),
                     fcmds);
    isnfStartupViewerManager(app);
    initialized = vTRUE;
  }
  return;
}

/********
 * isnfStopProcessingSnoopers stops any snoops in progress.
 *
 * -> app, the application
 * <- void
 *********/
void
isnfStopProcessingSnoopers(isnifferApp *app)
{
  if (initialized) {
    terminated = vTRUE;
    if (isnfGetNumberViewersProcessing())
      isnfStopProcessingViewers(app);
    if (snooperGetNumber()) {
      isnfAbandonAllSearches();
#if vmemBALANCE
      {
	register snooper *scan,*stop;
	for (scan=tarrayAtStartAs(snoopers,snooper*), 
	     stop=tarrayAtStopAs(snoopers, snooper*); scan<stop; scan++)
	  isnfDeleteStatusDialogGraphic(scan->graphic);
      }
#endif
    }
  }
  return;
}

/********
 * isnfShutdownSnooperManager shutdowns the modules -- does NOT stop
 * snoops in progress (this should be done by isnfStopProcessingSnoopers). 
 * cleans up any memory used by module.
 *
 * -> app, the application
 * <- void
 *********/
void
isnfShutdownSnooperManager(isnifferApp *app)
{
  if (initialized) {
    isnfShutdownViewerManager(app);
    if (chsr) {
      vfilechsrDestroy(chsr);
      chsr = NULL;
    }
    if (snoopers)
      tarrayDestroy(snoopers);
    snoopers = NULL;
  }
  return;
}

/********
 * isnfProcessStartupSnoopRequests processes any files from the user's
 * startup preferences (either through a command line or the options window
 * on mac platform). note we assume the filenames are part of the
 * applications arglist (ala main())
 *
 * -> app, the application
 * <- void
 *********/
void
isnfProcessStartupSnoopRequests(isnifferApp *app)
{
  const vfsPath	**paths;
  int		num;

  if (!initialized) 
    vexGenerate(vexGetModuleStateClass(), vexMESSAGE, 
      "module must be initialized before processing possible", vexERRNO, 0,
       vexNULL);

  vfsGetArgs(&num, &paths);
  if (num>1)
    for (--num; num; num--)
      if (!isnfGetViewer(paths[num])) snooperDoIt(app, paths[num]);

  return;
}


/********
 * isnfGetNumberSnoopersProcessing returns the number of ongoing and
 * completed snoops.
 *
 * -> void
 * <- int, the number of ongoing and finished snoops
 *********/
int
isnfGetNumberSnoopersProcessing(void)
{
  return snooperGetNumber() + isnfGetNumberViewersProcessing();
}

/*
 *+------------------------------------------------------------------------+
 * private: activating/deactivating suspend and resume command
 *+------------------------------------------------------------------------+
 */

#define suspendEnable(a)	\
  vobjectPropagateChange(a->object, vname_State, appname_SuspendAct, \
			 vname_Enabled)
#define suspendDisable(a)	\
  vobjectPropagateChange(a->object, vname_State, appname_SuspendAct, \
			 vname_Disabled)
#define resumeEnable(a)		\
  vobjectPropagateChange(a->object, vname_State, appname_ResumeAct, \
			 vname_Enabled)
#define resumeDisable(a)	\
  vobjectPropagateChange(a->object, vname_State, appname_ResumeAct, \
			 vname_Disabled)

/*
 *+------------------------------------------------------------------------+
 * private: snooping multiple files at once
 *+------------------------------------------------------------------------+
 */

/********
 * snooperLocate tries to find the snooper associated with a given 
 * file. if no snooper returns NULL.
 *
 * ->  path, the file we're interested in
 * ->  options, the snooping options (ignored for now)
 * <-> pos, the array index of the file (if found)
 * <-  snooper, snooper reference or NULL if not found
 *********/
static snooper*
snooperLocate(const vchar *filepath, unsigned options, int *pos)
{
  int max;
  register snooper *scan,*stop;

  if (pos) 
    *pos = -1;
  if (snoopers && (max=tarrayGetNumber(snoopers))>0) {
    for (scan= tarrayAtStartAs(snoopers,snooper*), stop= scan+max;
	 scan<stop; scan++)
      if (scan->filepath==filepath) {
	if (pos) 
	  *pos = scan-tarrayAtStartAs(snoopers,snooper*);
	return scan;
      }
  }
  return NULL;
}

/********
 * snooperCreate allocates and initializes a new snooper for the
 * given file. this does -NOT- start the snoop.
 *
 * -> path, the file we're interested in
 * <- void
 *********/
static void
snooperCreate(const vchar *filepath)
{
  isnifferApp		*app;
  snooper		localsnoop;
  register snooper	*snoop= &localsnoop;

  if (!snoopers) snoopers = tarrayCreate(sizeof(snooper));
  app = isnfGet();
  snoop->options = 0;
  if (app->recursive) snoop->options |= optionRECURSIVE;
  if (app->all) snoop->options |= optionALL;
  snoop->graphic = NULL;
  snoop->filepath = filepath;
  snoop->imagecount = 0;
  tarrayAppendItem(snoopers, snoop);
  return;
}

/********
 * snooperDestroy zaps any memory used by a snooper. should be
 * called after the snooper has completed or aborted.
 *
 * -> path, the snooper's file (used to locate snooper)
 * -> options, ditto (although ignored for now)
 * <- void
 *********/
static void
snooperDestroy(const vchar *filepath, unsigned options)
{
  snooper *snoop;
  int	   pos;
  if ((snoop=snooperLocate(filepath, options, &pos)))
    tarrayDeleteItem(snoopers, pos);
  return;
}

/********
 * snooperGetNumber returns the number of snoopers (ongoing and 
 * completed)
 *
 * -> void
 * <- int, the number of total snoopers
 *********/
static int
snooperGetNumber(void)
{
  return (snoopers ? tarrayGetNumber(snoopers) : 0);
}

/********
 * snooperDoIt actually begins snoopage of a given file.
 *
 * -> app, the application
 * -> file, the file we wanna snoop
 * <- void
 *********/
static void
snooperDoIt(register isnifferApp *app, const vfsPath *path)
{
  const vchar *filepath;

  vexWITH_HANDLING {
    filepath = isnfSearchFile(path, app->recursive, vFALSE, app->all, 
			      snooperProcessBatch);
    if (filepath)
      suspendEnable(app);
  }
  vexON_EXCEPTION {
    vdebugBE(vexDumpChain(vdebugGetWarningStream()));
    vexClear();
    isnfInformUser(msgCantSnoopFile,NULL);
  }
  vexEND_HANDLING;
  return;
}

/********
 * snooperProcessBatch is called whenever something "interesting" 
 * occurs during a snoop; called by the isniffer module. currently it
 * processes "push/pop" resources and "found/saved" images messages
 * (shows up visually in the status graphic progress dialog).
 *
 * -> file, the file in question
 * -> who, identifier for rest of message
 * -> ..., depends on what "who" is
 * <- void
 *********/
static void
snooperProcessBatch(const vchar *filepath, int who, ...)
{
  register isnifferApp	*app;
  va_list		ap;
  int			count, result;
  vresource		file;
  tstack		*images;
  int			*relinquish;
  int			done;
  int			flush = vTRUE;
  snooper		*snoop = NULL;

  if (who!=isnfSEARCH_BEGIN && who!=isnfSEARCH_EMPTY_FILE) {
    snoop = snooperLocate(filepath, 0, NULL);
    vdebugIF((!snoop), vexGenerate(vexGetReturnNullClass(), vexMESSAGE,
             "report: can't locate snooper's filepath key!", vexERRNO, 0,
             vexNULL));
  }

  app = isnfGet();
  va_start(ap,who);

  switch(who) {
    case isnfSEARCH_FOUND_IMAGE: {
      snoop->imagecount++;
      if (!(snoop->imagecount%isnfIMAGE_BATCH_SIZE))
	statusboxUpdateImageCount(snoop->graphic->find,1);
      else
	flush = vFALSE;
      break;
    }
    case isnfSEARCH_PUSH_RES: 	{
      count = va_arg(ap, int);
      statusboxUpdateImageCount(snoop->graphic->search,count);
      break;
    }
    case isnfSEARCH_POP_RES: 	{
      count = va_arg(ap, int);
      statusboxUpdateImageCount(snoop->graphic->search,-count);
      break;
    }

    case isnfSEARCH_BEGIN: {
      file = va_arg(ap,vresource);
      snooperCreate(filepath);
      snoop = snooperLocate(filepath, 0, NULL);
      vdebugIF((!snoop), vexGenerate(vexGetReturnNullClass(), vexMESSAGE,
             "report: can't locate snooper's filepath key!", vexERRNO, 0,
             vexNULL));
      snoop->graphic = isnfNewStatusDialogGraphic(filepath, NULL);
      break;
    }

    case isnfSEARCH_SUSPEND:
    case isnfSEARCH_END:   {
      file       = va_arg(ap, vresource);
      images     = va_arg(ap, tstack*);
      relinquish = va_arg(ap, int*);
      done       = (who==isnfSEARCH_END);
      result     = isnfGiveImagesToViewer(filepath, images, file, 
					  snoop->graphic, done);
      if (done || result==viewerERROR) {
	if (done && result==viewerSUCCESS)
	  statusboxTurnOffGraphicsMode(snoop->graphic->search);
	snooperDestroy(filepath, snoop->options);
	if (result==viewerEMPTY)
	  isnfInformUserByMessageBox(msgSelectedFileHasNoIcons);
	else
	if (result==viewerERROR && !done)
	  isnfAbandonSearch(filepath);
	if (snooperGetNumber()==0) {
	  suspendDisable(app), resumeDisable(app);
	}
      }
     *relinquish = vTRUE;
      if (done) 
	flush = vFALSE;
      break;
    }

    case isnfSEARCH_EMPTY_FILE: {
      vfsPath *path;
      path = va_arg(ap,vfsPath*);
      if (snooperGetNumber()==0) {
	suspendDisable(app), resumeDisable(app);
      }
      isnfInformUserByMessageBox(msgSelectedFileIsEmpty);
      flush = vFALSE;
      break;
    }
#if vdebugDEBUG
    default: {
      vdebugTrace("reflect: unrecognized callback token!?!\n");
      break;
    }
#endif
  }

  va_end(ap);
  if (flush) vwindowFlushRequests();

  return;
}

/*
 *+------------------------------------------------------------------------+
 * private: selecting snoop file with file chooser or from finder
 *+------------------------------------------------------------------------+
 */

/********
 * snooperAcceptFile called when the user selects one or more files
 * for snoopage. calls snooperDoIt if the file is okidoki.
 *
 * -> chsr, the file chooser
 * -> path, the user's selection (or one if many)
 * <- [T/F], TRUE if can use item, else FALSE
 *********/
static int
snooperAcceptFile(vfilechsr *chsr, vfsPath *path)
{
  register isnifferApp *app;
  int		        ok;
  vdialog	       *dialog;

  app = (isnifferApp*)vfilechsrGetData(chsr);
  dialog = vfilechsrGetDialog(chsr);
  ok = vTRUE;

  if (!isnfGetViewer(path)) 
    snooperDoIt(app,path);
  else {
    isnfInformUser(msgSelectedFileAlreadySnooped,dialog);
    ok = vFALSE;
  }

  return ok;
}


/********
 * snooperAcceptExternFile is called when user opens a resource file
 * from "finder-like" environments (eg. mac/chicago/etc.) on the
 * mac for example, dropping a resource file on the isniffer application
 * will land here...
 *
 * -> com, the snoop this command
 * -> context, the command's context
 * <- TRUE
 *********/
static int
snooperAcceptExternFile(vcommandFunction *com, vdict *context)
{
  vfsPath *path = (vfsPath*)vdictLoad(context, vname_DocumentPath);

  if (path)
    if (!isnfGetViewer(path)) 
      snooperDoIt(isnfGet(),path);
    else
      isnfInformUser(msgSelectedFileAlreadySnooped,NULL);

  return vTRUE;
}

/********
 * snooperLetUserChoose is called when user selects the "snoop" item;
 * opens a filechooser for user to select which files.
 *
 * -> com, the snoop command
 * -> context, the command's context
 * <- TRUE
 *********/
static int
snooperLetUserChoose(vcommandFunction *com, vdict *context)
{
  register isnifferApp *app= isnfGet();

  /* find out if we've got a writable temporary directory */
  if (!isnfGotTemporaryStorageForViewers())
    return vTRUE;

  /* create a "global" chooser */
  if (!chsr) {
    vstr *title;

    vexWITH_HANDLING {
      /* create new file chooser object */
      chsr = vfilechsrCreate();
      vfilechsrSetType(chsr, vfilechsrGET);
      vfilechsrSetApply(chsr, snooperAcceptFile);
      vfilechsrSetData(chsr, app);
      vfilechsrSetSelection(chsr, vfilechsrMULTIPLE);
      vfilechsrSetOptions(chsr, vfilechsrOPTION_HIDE_HIDDEN
			  |vfilechsrOPTION_FILE_MUST_EXIST);

      /* specific name */
      title = isnfStrFrom(strTitleGetChsr);
      vfilechsrSetTitle(chsr, title);
      vstrDestroy(title);

      /* specific filetypes (all or only galaxy resource files) */
      vfilechsrAddFilterBySystemType(chsr, vresourceNULL, vname_Default,
				     NULL);
      vfilechsrAddFilterBySystemType(chsr, vresourceNULL, TAG("Resource"),
				     TAG("Resource"));

      /* place wrt. the the main dialog */
      vfilechsrPlace(chsr, app->requestor, vrectPLACE_CENTER,
		     vrectPLACE_CENTER);

      /* set the original directory to the app's startup directory */
      vfilechsrSetDirectory(chsr, vfsGetStartupDirPath());
    }
    vexON_EXCEPTION {
      vdebugBE(vexDumpChain(vdebugGetWarningStream()));
      vexClear();
      isnfInformUser(msgCantInitFileChooser,NULL);
    }
    vexEND_HANDLING;
  }


  /* open the chooser */
  vexWITH_HANDLING
  {
    if (vdialogIsOpen(vfilechsrGetDialog(chsr))) {
      if (!vwindowIsVisible(vdialogGetWindow(vfilechsrGetDialog(chsr))))
	vwindowUniconify(vdialogGetWindow(vfilechsrGetDialog(chsr)));
      vwindowRaise(vdialogGetWindow(vfilechsrGetDialog(chsr)));
    }
    else
      vfilechsrOpen(chsr);
  }
  vexON_EXCEPTION
  {
    vdebugBE(vexDumpChain(vdebugGetWarningStream()));
    vexClear();
    isnfInformUser(msgCantOpenFileChooser,NULL);
  }
  vexEND_HANDLING;

  return vTRUE;
}

/*
 *+------------------------------------------------------------------------+
 * private: suspending/resuming snoops in progress
 *+------------------------------------------------------------------------+
 */

/********
 * snooperSuspend is called when the user selects the "suspend" item 
 * during snoop. note this applies to -all- ongoing snoops not
 * a single file.
 *
 * -> com, the suspend command
 * -> context, the command's context
 * <- TRUE
 *********/
static int
snooperSuspend(vcommandFunction *com, vdict *context)
{
  register isnifferApp *app=isnfGet();
  isnfSuspendAllSearches(vTRUE);
  suspendDisable(app), resumeEnable(app);
  return vTRUE;
}

/********
 * snooperResume is called when the user selects the "resume" item
 * after a suspension. note this applies to -all- ongoing snoops not
 * a single file.
 *
 * -> com, the resume command
 * -> context, the command's context
 * <- TRUE
 *********/
static int
snooperResume(vcommandFunction *com, vdict *context)
{
  register isnifferApp *app=isnfGet();
  isnfResumeAllSearches();
  resumeDisable(app), suspendEnable(app);
  return vTRUE;
}

/*
 *+------------------------------------------------------------------------+
 * private: acknowledging changes in snoop options
 *+------------------------------------------------------------------------+
 */

/********
 * snooperSetSnoopOption is called when the user toggles the misc. snoopage 
 * options (eg. snoop all resources). applies to the next snoop.
 *
 * -> com, the "toggle" command
 * -> context, the command's context
 * <- TRUE
 *********/
static int
snooperSetSnoopOption(vcommandSelector *com, vdict *context)
{
  isnifferApp	*app=isnfGet();
  int		 handled;
  const vname	*toggled;

  handled = vTRUE;
  switch (vcommandGetSelector(com)) {
    case comTOGGLE_RECURSION: {
      toggled = (const vname*)vdictLoad(context, vname_Toggle);
      if (toggled) {
	app->recursive = (toggled==vname_On);
	if (!app->recursive)
	  vobjectPropagateChange(app->object, vname_State, appname_DoAllAct,
				 vname_Disabled);
	else
	  vobjectPropagateChange(app->object, vname_State, appname_DoAllAct,
				 vname_Enabled);
      }
      break;
    }
    case comTOGGLE_CHECK_ALL: {
      toggled = (const vname*)vdictLoad(context, vname_Toggle);
      if (toggled)
	app->all = (toggled==vname_On);
      break;
    }
    default: {
      handled = vFALSE;
    }
  }

  return handled;
}


/********
 * snooperSetSnoopContext is called to set up touchy-feeling of the misc
 * snoop options based on preferences/app settings.
 *
 * -> com, the "toggle" command
 * -> context, the command's context
 * <- TRUE
 *********/
static int
snooperSetSnoopContext(vcommandSelector *com, vdict *context)
{
  isnifferApp *app = isnfGet();

  switch (vcommandGetSelector(com)) {
    case comTOGGLE_RECURSION: {
      vdictStore(context, vname_Toggle, app->recursive ? vname_On : vname_Off);
      vdictStore(context, vname_State, vname_Enabled);
      break;
    }
    case comTOGGLE_CHECK_ALL: {
      vdictStore(context, vname_Toggle, app->all ? vname_On : vname_Off);
      vdictStore(context, vname_State, app->recursive ? vname_Enabled : vname_Disabled);
      break;
    }
  }
  return vTRUE;
}


/********
 * getselectorClass returns the selector command class used by our
 * snooperSetSnoopOption command.
 *
 * -> void
 * <- selector class
 *********/
static vcommandSelectorClass*
getselectorClass(void)
{
  static vcommandSelectorClass *selclass = NULL;
  if (!selclass) {
    register vcommandSelectorClass *clas;
    clas = vclassReproduce(vobjectGetCommandClass());
    vclassSet(clas, vcommandISSUE, snooperSetSnoopOption);
    vclassSet(clas, vcommandQUERY, snooperSetSnoopContext);
    selclass = clas;
  }
  return selclass;
}


#if 0
/*
 *+------------------------------------------------------------------------+
 * private: viewing snooped icon source
 *+------------------------------------------------------------------------+
 */
/********
 * snooperOpenViewer belongs to spamoids.
 *
 * -> 
 * <- TRUE
 *********/
static int
snooperOpenViewer(vcommandFunction *com, vdict *context)
{
  return vTRUE;
}
#endif

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

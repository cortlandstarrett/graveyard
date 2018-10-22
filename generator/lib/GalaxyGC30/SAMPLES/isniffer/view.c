/* $Id: view.c,v 1.3 1996/08/21 15:52:23 david Exp $ */
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
 *     Handles the icon viewer dialogues.                                   *
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
#include vdrawHEADER
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



/* Define our debug module for debug manager */
#if vdebugDEBUG
static const char *const _viewerTag = "viewer";
#define vdebugTAG _viewerTag
#endif


/*
 *+------------------------------------------------------------------------+
 * private constants, variables, prototypes
 *+------------------------------------------------------------------------+
 */

static const vname	*name_FileFrom;
static const vname	*name_Last;
static const vname	*name_Class;
static const vname	*name_Images;
static const vname	*name_StoreResource;
static const vname	*name_ItemTag;
static tarray		*viewers = NULL;
static int		 numAdders = 0;
static vpool		*vieweritemPool = NULL;
vfsPath		        *writableDirectory = NULL;
static vfilechsr	*tempChsr = NULL;
vfilechsr		*saveChsr = NULL;
imanager		*iman = NULL;

static vfsPath		*tempfileGetHome(void);
static vfsPath		*tempfileCreate(const vchar*);
static void		tempfileGetResources(vfsPath*,vresource*,vresource*,vresource*);
static void		tempfileCreateImageAdder(viewer*,tstack*,vresource, statusgraphic*);
static void		tempfileDestroyImageAdder(imageadder*);
static void		tempfileAddImagesToImageAdder(imageadder*,tstack*);
static int		tempfileHandleImageAdderRequest(vevent*);
static void		tempfileHandleImageAdderDone(imageadder*);
static void		tempfilePostImageAdder(imageadder*);

static viewer		*viewerAlloc(void);
static viewer		*viewerLookup(const vchar*,unsigned,int*);
static viewer		*viewerCreate(const vchar*,tstack*,vresource,statusgraphic*);
static void		viewerUpdate(viewer *view,tstack*);
static void		viewerCreateFileIcon(const vchar*, viewer*);
static void		viewerSelectFileIcon(viconview*,viconviewIcon*,vevent*,vbool);
static void		viewerCreateDialog(viewer*);
static vmenu		*viewerMakeMenu(viewer*);
static void		viewerSetMenu(viewer*, vmenu*);
static void		viewerCreateIcons(viewer*);
static void		viewerOpen(viewer*);
static void		viewerDestroyIcons(viewer*);
static void		viewerDestroy(viewer*);
static void		viewerDestroyFileIcon(viconviewIcon*);
static void		viewerDrawItem(vdomainview*,vdomainObject*);
static void		viewerClose(viewer*);
static int		viewerHandleDestroyLater(vevent*);
static void		viewerDestroyLater(viewer*);
static int		viewerHandleWindowManagerCloseRequest(vdialog*,vevent*);
static int		viewerCloseCommand(vcommandFunction*,vdict*);
static int		viewerHideCommand(vcommandFunction*,vdict*);
static int		viewerToggleDisplayCommand(vcommandFunction*, vdict*);
static int		viewerToggleDisplayQuery(vcommandFunction*, vdict*);
static int		viewerToggleTitlesCommand(vcommandFunction*, vdict*);
static int		viewerToggleTitlesQuery(vcommandFunction*, vdict*);
static int		viewerCleanupCommand(vcommandFunction*, vdict*);
static void		viewerHandleUserResponseToSaveRequest(int,void*);


/*
 *+------------------------------------------------------------------------+
 * exported routines:
 *+------------------------------------------------------------------------+
 */

/********
 * isnfStartupViewerManager initializes the viewer module. basically
 * adds its top-level commands to the application's command space.
 *
 * -> app, the application
 * <- void
 *********/
void
isnfStartupViewerManager(isnifferApp *app)
{
  register viconview *iconview;
  vstr *str;

  vexWITH_HANDLING
    {
      iman = imanagerCreateEditable(app->app);
      iconview = (viconview*)vdialogFindItem(app->requestor, appname_ReqView);
      viconviewSetData(iconview, app);
      viconviewSetSelectNotify(iconview, viewerSelectFileIcon);
      viconviewSetView(iconview, viconviewGetIconView());

      str = isnfStrFrom(strTitleFrom);
      name_FileFrom = vnameInternGlobal(str);
      vstrDestroy(str);
      str = isnfStrFrom(strTitleNumberImagesSnooped);
      name_Last = vnameInternGlobal(str);
      vstrDestroy(str);

      /* this names are cheating, but we need to manipulate image stores
	 without going through the imanager api */
      name_Images = vnameInternGlobalLiteral("images");
      name_Class = vnameInternGlobalLiteral("image-store");
      name_StoreResource = imanagerGetImageStoreResourceTag(iman);
      name_ItemTag = vnameInternGlobalLiteral("im-tag");

      viewerFileStartup(app);
      viewerEditStartup(app);
    }
  vexON_EXCEPTION
    {
      vexPropagate(vexGetModuleStartupClass(), vexMESSAGE, 
		   "Problem initializing snooped file viewers", vexERRNO, 0,
		   vexNULL);
    }
  vexEND_HANDLING;
  return;
}

/********
 * isnfStopProcessingViewers stops any snoops in progress.
 *
 * -> app, the application
 * <- void
 *********/
void
isnfStopProcessingViewers(isnifferApp *app)
{
  register viewer **scan,**stop;
  if (viewers && tarrayGetNumber(viewers)>0) {
    scan = tarrayAtStartAs(viewers,viewer**);
    stop = tarrayAtStopAs(viewers,viewer**); 
    for (; scan<stop; scan++) {
      if ((*scan)->adder)
	(*scan)->adder->aborted = vTRUE;
    }
  }
  return;
}


/********
 * isnfShutdownViewerManager shuts down the viewer module.
 *
 * -> app, the application
 * <- void
 *********/
void
isnfShutdownViewerManager(isnifferApp *app)
{
  register viconview	       	*iconview;
  viconviewIterator		 iterator;
  register viconviewIterator   	*iter= &iterator;
  viewer			**scan;
  int				i;

  if (viewers) {
    i = tarrayGetNumber(viewers)-1;
    for(; i>=0; i--) {
      scan = tarrayAtAs(viewers, i, viewer**);
      (*scan)->ignoresave = vTRUE;
      viewerDestroy(*scan);
    }
    iconview = (viconview*)vdialogFindItem(app->requestor, appname_ReqView);
    viconviewInitIterator(iter, iconview);
    while (viconviewNextIterator(iter))
      viewerDestroyFileIcon(viconviewGetIteratorIcon(iter));
    viconviewDestroyIterator(iter);
    tarrayDestroy(viewers);
    viewers = NULL;
  }

  if (tempChsr)
    vfilechsrDestroy(tempChsr);
  if (saveChsr)
    vfilechsrDestroy(saveChsr);

  viewerFileShutdown();
  viewerEditShutdown();

  if (iman) 
    imanagerDestroy(iman);
  if (writableDirectory)
    vfsDestroyPath(writableDirectory);
  if (vieweritemPool)
    vpoolDestroy(vieweritemPool);
  return;
}

/********
 * isnfGetViewer checks if a snoop is progress or has already been 
 * done for a given file.
 *
 * -> file,  the file to check
 * <- [t/f], TRUE if searching or already searched
 *********/
int
isnfGetViewer(const vfsPath *path)
{
  vstr *str;
  viewer *view;
  str = vfsPathToStr(path);
  view = viewerLookup(str,0,NULL);
  vstrDestroy(str);
  return view ? vTRUE : vFALSE;
}

/********
 * isnfGiveImagesToViewer is called when user suspends a snoop and/or
 * the snoop completes. basically takes the found images and starts
 * adding them to the viewer's iconview. if the file is new, a new
 * viewer structure is created for it.
 *
 * -> path,     the path of file that's being searched (it's key)
 * -> images,   the found images (can be NULL or empty)
 * -> file,     the resource file that's being searched
 * -> graphic,  status graphic for this snoop (updated as images
 *	        are added
 * -> [t/f],    TRUE if the file snoop if finished (otherwise just
 *	        suspended or live feed)
 * <- [1/0/-1], 1 if file is empty
 *              0 if no error
 *             -1 if error of somekind
 *********/
int
isnfGiveImagesToViewer(const vchar *filepath, tstack *images, vresource scanfile,
		       statusgraphic *graphic, int done)
{
  int	result = 0;
  viewer *view;
  int num;

  view = viewerLookup(filepath,0,NULL);
  num = images ? tstackGetSize(images) : 0;

  /* check if nothing to do */
  if (!view && num<=0) {
    if (images) 
      tstackDestroy(images);
    result = 1; /* => empty */
  }

  /* else update viewer-adder */
  else {

    /* if nothing this time */
    if (num<=0) {
      if (images) 
	tstackDestroy(images);
    }
    /* else create and/or update adder */
    else {
      if (!view) view = viewerCreate(filepath, images, scanfile, graphic);
      else viewerUpdate(view, images);
    }
    /* make sure adder knows our state so it knows what to do
     * when it's done */
    if (view)
      if (!done) 
	view->adder->waiting = vTRUE;
      else 
	view->adder->waiting = vFALSE;

    /* somethin' happened */
    if (!view)
      result = -1;
  }

  /* if nothing to read or error, close file immediately */
  if ((result==1 || result== -1) && done) {
    vresourceCloseFile(scanfile);
    isnfDeleteStatusDialogGraphic(graphic);
  }

  return result;
}

/********
 * isnfGetNumberViewersProcessing returns the number of views
 * being processed (images being added to their iconviews).
 *
 * -> void
 * <- int, number of processing views
 *********/
int
isnfGetNumberViewersProcessing(void)
{
  return numAdders;
}


/********
 * isnfGotTemporaryStorageForViewers checks if we've got a 
 * writable directory where we can store temporary snooped image
 * files (note it might require asking user for a location ala
 * a directory picker).
 *
 * -> void
 * <- [t/f] TRUE if we've got a writeable directory
 *********/
int
isnfGotTemporaryStorageForViewers(void)
{
  vfsPath *temp;
  int ok;
  temp = tempfileGetHome();
  ok = temp!=NULL;
  if (temp) vfsDestroyPath(temp);
  if (!ok) isnfInformUserByMessageBox(msgNeedWritableTempDirectory);
  return ok;
}


/*
 *+------------------------------------------------------------------------+
 * private: managing the temp icon files (small ahem...hack to test
 * image stores. we assume full knowledge of image manager's classes!)
 *+------------------------------------------------------------------------+
 */
#if vdebugDEBUG
#undef vdebugTAG
static const char *const _tempfileTag = "viewer-tempfile";
#define vdebugTAG _tempfileTag
#endif

#define adderBATCH isnfIMAGE_BATCH_SIZE


/********
 * tempfileSetHome is called when the user hits "Apply" or "OK" from
 * the directory chooser. Returns TRUE if the selected directory is
 * writable.
 * -> chsr,  the file chooser
 * -> it,    the selected directory path
 * <- [t/f], TRUE if directory writable, otherwise FALSE
 ********/
static int
tempfileSetHome(vfilechsr *chsr, vfsPath *it)
{
  int		 ok;

  ok = vfsAccess(it, vfsCAN_READ|vfsCAN_WRITE);
  if (ok)
    writableDirectory= vfsClonePath(it);
  else
    isnfInformUser(msgSelectedDirectoryNotWritable, vfilechsrGetDialog(chsr));

  return ok;
}

/********
 * tempfileGetHome returns a writable directory for temporary
 * snooped image files. returns NULL if user cancelled or could
 * not located directory.
 *
 * -> void
 * <- path, the temp file directory's (full) path
 *********/
static vfsPath*
tempfileGetHome(void)
{
  if (!writableDirectory)
    if ((isnfGet())->tempdir)
      writableDirectory = vfsClonePath((isnfGet())->tempdir);
    else
      {
	vdialog   *dialog;
      
	/* by default use the location o' the executable */
	writableDirectory = vfsCloneAppDirPath();

	/* if can't use, ask user for a writable directory */
	if (!vfsAccess(writableDirectory, vfsCAN_READ|vfsCAN_WRITE)) {
	  isnifferApp *app = isnfGet();
	  vstr	      *title;

	  vfsDestroyPath(writableDirectory);
	  writableDirectory = NULL;

	  tempChsr = vfilechsrCreate();
	  vfilechsrSetType(tempChsr, vfilechsrGET);
	  vfilechsrSetApply(tempChsr, tempfileSetHome);
	  vfilechsrSetSelection(tempChsr, vfilechsrSINGLE);
	  vfilechsrSetOptions(tempChsr, vfilechsrOPTION_PATH_MUST_EXIST |
			      vfilechsrOPTION_ONLY_DIRS |
			      vfilechsrOPTION_HIDE_HIDDEN);

	  dialog = vfilechsrGetDialog(tempChsr);
	  title = isnfStrFrom(strTitleTempFilesPutChsr);
	  vfilechsrSetTitle(tempChsr, title);
	  vstrDestroy(title);

	  vfilechsrPlace(tempChsr, app->requestor, vrectPLACE_CENTER,
			 vrectPLACE_CENTER);
	  vfilechsrSetLeader(tempChsr, vdialogGetWindow(app->requestor));

	  vfilechsrSetDirectory(tempChsr, vfsGetStartupDirPath());
	  (void)vfilechsrProcess(tempChsr);
	}/*no*/
      }

  return writableDirectory ? vfsClonePath(writableDirectory) : NULL;
}

/********
 * tempfileCreate creates a new (temporary) resource file to hold
 * snooped images. used to test that imanager reads/writes image
 * and db information properly. note the file created/init and
 * _closed_ before returning (it'll be opened as necessary by adders).
 *
 * -> path, the snooped resource file
 * <- path, the imanager image file to hold found images
 *********/
static vfsPath*
tempfileCreate(const vchar *filepath)
{
  vfsPath		*path;
  vstr			*str;
  vresource		 resfile, store, images;
  vfsPath		*volatile path_v;
  vresource	 	volatile resfile_v;

  path_v = NULL;
  resfile_v = vresourceNULL;

  vexWITH_HANDLING
    {
      /* get a filename that doesn't exist */
      path_v = path = tempfileGetHome();
      if (!path) 
	vexGenerate(vexGetAbandonClass(), vexMESSAGE, "cannot locate "
		    "a writable directory", vexERRNO, 0, vexNULL);
      for (;;)
	{
	  str = vstrCloneScribed(vcharScribeLiteral("xsXXXXXX.vr"));
	  vfsAppendPath(path, vfsGenerateTempName(str), NULL);
	  vstrDestroy(str);
	  if (!vfsAccess(path, vfsFILE_EXISTS))
	    break;
	  vfsTruncatePath(path,1);
	}

      /* create-open file */
      resfile = viewerNewTypedFile(path, viewerFileMASK);
      resfile_v = resfile;
      store = vresourceCreate(resfile, name_StoreResource, vresourceDICT);

      /* create "standard" image store dict */
      vresourceSetTag(store, vname_Class, name_Class);
      images = vresourceCreate(store, name_Images, vresourceDICT);

      /* our own information*/
      vresourceSetString(resfile, appname_VersionString, isnfGetVersionString());
      vresourceSetString(resfile, name_FileFrom, filepath);
      vresourceSetInteger(resfile, name_Last, 1);

      /* close file */
      vresourceCloseFile(resfile);
    }
  vexON_EXCEPTION
    {
      int msg;
      vdebugBE(vexDumpChain(vdebugGetWarningStream()));
      if (vexGetAbandonException()) msg = msgNeedWritableTempDirectory;
      else if (vexGetModuleLimitException()) msg = msgTooManyResourceFilesOpen;
      else if (vfsGetException()) msg = msgProblemSavingSnoopFileImages;
      else msg = msgCantViewSnoopFile;
      if (resfile_v!=vresourceNULL) vresourceCloseFile(resfile_v);
      if (path_v) vfsDestroyPath(path_v);
      isnfInformUser(msg,NULL);
      vexClear();
      path = NULL;
    }
  vexEND_HANDLING;

  return path;
}

/********
 * tempfileGetResources opens a temporary image file (created with
 * tempfileCreate) and retrieves the imanager image resources.
 *
 * -> path, the temporary image file
 * -> resfile, [fill-in] the root resource for file
 * -> store, [optional, fill-in] the imanager image store resource
 * -> images, [optional, fill-in] the image store's image list
 * <- void
 *********/
static void
tempfileGetResources(vfsPath *filepath, 
		     vresource* resfile, vresource *store, vresource *images)
{
  vdebugIF((!filepath || !resfile), vexGenerate(vexGetArgNullClass(), 
           vexMESSAGE, "retrieve resources of NULL path or resfile ptr!", 
	   vexERRNO, 0, vexNULL));
  *resfile = vresourceOpenFile(filepath, vfsOPEN_READ_WRITE);
  if (store) {
    *store = vresourceGet(*resfile, name_StoreResource);
    if (images)
      *images = vresourceGet(*store, name_Images);
  }
  return;
}


#if vdebugDEBUG
#undef vdebugTAG
static const char *const _adderTag = "viewer-image-adder";
#define vdebugTAG _adderTag
#endif


/********
 * tempfileCreateImageAdder allocs/inits a new "adder" for a image
 * file. adders incrementally save all the snooped images to the
 * image file (ala batches and client events).
 *
 * -> view,    the viewer for the retrieved images
 * -> images,  the first batch of retrieved images to process
 * -> file,    the root resource of file being scanned (!image file)
 * -> graphic, the status graphic our adders need to update as
 *             images are saved.
 * <- void
 *********/
static void
tempfileCreateImageAdder(viewer *view, tstack *scanimages, vresource scanfile,
			 statusgraphic *graphic)
{
  register imageadder *adder;

  vdebugIF((!view || !view->temp), vexGenerate(vexGetArgNullClass(),
           vexMESSAGE, "create: no view and/or temp file created!", 
           vexERRNO, 0, vexNULL));

  /* Note: since we can't tell the event manager to disregard pending 
   * events we must use the viewer to set our "aborted" flag in case 
   * the user quits the application or cancels the operation before 
   * we're done; this way we cleanup properly and don't continue to 
   * re-post ourselves.
   */
  adder = (imageadder*)vmemAlloc(sizeof(imageadder));
  adder->view     = view;
  adder->stk      = scanimages;
  adder->scanfile = scanfile;
  adder->filepath = view->temp;
  adder->resfile  = vresourceNULL;
  adder->images   = vresourceNULL;
  adder->waiting  = vFALSE;
  adder->aborted  = vFALSE;
  adder->last     = 1; /* 1-based */
  adder->graphic  = graphic;
  adder->number   = 0;

  view->adder = adder;
  tempfilePostImageAdder(adder);
  numAdders++;
  return;
}

/********
 * tempfileDestroyImageAdder nukes the given image adder and
 * any memory it's allocated. use after the adder has completed
 * it's mission or the snoop's been aborted. warning: this will
 * close the temporary image file! dismisses the snoop's status
 * dialog if all no more adders for the file.
 *
 * -> adder, the adder to nuke
 * <- void
 *********/
static void
tempfileDestroyImageAdder(register imageadder *adder)
{
  tstackDestroy(adder->stk);
  vresourceCloseFile(adder->scanfile);
  if (!(adder->waiting && adder->aborted))
    isnfDeleteStatusDialogGraphic(adder->graphic);
  if (adder->resfile!=vresourceNULL)
    vresourceCloseFile(adder->resfile);
  vmemFree(adder);
  numAdders--;
  return;
}

/********
 * tempfileAddImagesToImageAdder adds another batch of images to
 * the batch currently being processed by an adder. used to 
 * start processing found images whenever user suspends snoop in
 * progress. basically no-op if snoop's been aborted.
 *
 * -> adder, the image adder
 * -> image, stack of new images (!NULL)
 * <- void
 *********/
static void
tempfileAddImagesToImageAdder(imageadder *adder, register tstack *src)
{
  register tstack  	*dst;
  register int	   	i,max;
  register void		*imageref;

  vdebugIF((!src), vexGenerate(vexGetArgNullClass(), vexMESSAGE,
	    "add images: adding NULL tstack of images!", vexERRNO, 0, 
             vexNULL));
  if (!adder->aborted) {
    dst = adder->stk;
    for (i=0, max=tstackGetSize(src); i<max; i++) {
      imageref = tstackPop(src);
      tstackPush(dst,imageref);
    }
  }
  tstackDestroy(src);
  return;
}

/********
 * tempfileHandleImageAdderRequest is called to handle image adder
 * events. basically copies a BATCH number of images to the image
 * file and updates the status dialog (if necessary). if all the
 * adder's images are copied and the file isn't still being 
 * processed (by more adders, or is still being snooped) closes
 * the temporary file and creates a viewer icon for the file.
 *
 * #a#	in case we snooped one of own sniffer document file. we need
 *      to make sure the store's identifying tag matches what we
 *	want!
 *
 * -> event, adder event
 * <- TRUE
 *********/
static int
tempfileHandleImageAdderRequest(vevent *event)
{
  register imageadder	*adder;
  const vname		*tag, *prevtag;
  int			i,max;
  vresource		src,dst;

  /* we expect this */
  adder = (imageadder*)veventGetClientData(event);

  /* if we been aborted, nuke self, view, and temp file */
  if (adder->aborted) {
    /* close file, since viewer nukes it */
    if (adder->resfile!=vresourceNULL) 
      vresourceCloseFile(adder->resfile);
    adder->resfile= vresourceNULL;
    /* this nukes temp file */
    adder->view->adder = NULL;
    viewerDestroy(adder->view);
    tempfileDestroyImageAdder(adder);
    return vTRUE;
  }

  /* if we've got stuff to add (not waiting for suspended grab) */
  if (tstackGetSize(adder->stk)) {

    /* if need to, open the resource file */
    if (adder->resfile==vresourceNULL) {
      vresource unused;
      tempfileGetResources(adder->filepath, &adder->resfile, &unused, 
			   &adder->images);
    }

    /* add at most BATCH images to file */
    for (i= adder->last, max=i+vMIN(tstackGetSize(adder->stk),adderBATCH);
	 i<max; i++) {
      src = tstackPopAs(adder->stk, vresource);
      tag = vnameInternGlobalScribed(vnumScribeInt(i));
      dst = vresourceMake(adder->images, tag);
      vresourceCopy(src,dst);
      if (vresourceTestGetTag(dst, name_ItemTag, &prevtag)) /* #a# */
	vresourceSetTag(dst, name_ItemTag, tag);
      adder->number++;
    }

    /* give user some visual feed back */
    if (!(adder->number%adderBATCH)) {
      statusboxUpdateImageCount(adder->graphic->find, -1);
      vwindowFlushRequests();
    }

    /* remember these */
    vresourceSetInteger(adder->resfile, name_Last, i);
    adder->last = i;
  }

  /* if not finished or waiting on suspended grab operation, 
   * repost self; otherwise finish adding (yippee!)
   */
  if (tstackGetSize(adder->stk) || adder->waiting) {
    if (tstackIsEmpty(adder->stk) && adder->resfile!=vresourceNULL) {
      vresourceCloseFile(adder->resfile);
      adder->resfile= vresourceNULL;
    }
    tempfilePostImageAdder(adder);
  }
  else
    tempfileHandleImageAdderDone(adder);


  /* always ours */
  return vTRUE;
}

/********
 * tempfileHandleImageAdderDone is called after all snooped images 
 * have been copied to the temp image file. updates the file's
 * viewers and dismisses the status dialog if no more ongoing
 * snoops.
 *
 * -> adder, the image adder
 * <- void
 *********/
static void
tempfileHandleImageAdderDone(imageadder *adder)
{
  isnifferApp *app = isnfGet();
  viewer      *view = adder->view;

  vdebugAdvise("done processing %s\n", (char*)view->from);
  view->last = adder->last;
  tempfileDestroyImageAdder(adder);
  view->adder = NULL;
  viewerCreateFileIcon(view->from, view);
  vwindowBeep();
  if (!isnfIsProcessingUserRequests() && vdialogIsOpen(app->status))
    vdialogClose(app->status);
  return;
}

/********
 * tempfilePostImageAdder posts an image adder event. see 
 * tempfileHandleImageAdderRequest.
 *
 * -> adder, the adder
 * <- void
 *********/
static void
tempfilePostImageAdder(imageadder *adder)
{
  vevent *event;

  event = veventCreateClient();
  veventSetPriority(event, veventPRIORITY_MIN);
  veventSetTarget(event, tempfileHandleImageAdderRequest);
  veventSetClientData(event, adder);
  veventPost(event);
  return;
}


/*
 *+------------------------------------------------------------------------+
 * private: managing data associated w/ iconview items in each viewer
 * window.
 *+------------------------------------------------------------------------+
 */

#if vdebugDEBUG
#undef vdebugTAG
static const char *const _vieweritemTag = "vieweritem";
#define vdebugTAG _vieweritemTag
#endif

/********
 * vieweritemAlloc allocs and initializes a new vieweritem 
 * structure.
 *
 * -> void
 * <- item, newly create item
 ********/
vieweritem*
vieweritemAlloc(void)
{
  register vieweritem *item;

  if (!vieweritemPool)
    vieweritemPool = vpoolCreate(sizeof(vieweritem));

  item = (vieweritem*)vpoolAlloc(vieweritemPool);

  (void)vmemSet(item, 0, sizeof(vieweritem));
  item->name = vnameNULL;
  item->pool = vTRUE;

  return item;
}

/********
 * vieweritemFree destroy memory used by vieweritem. does NOT
 * destroy item item's image.
 *
 * -> item, the vieweritem
 * <- void
 ********/
void
vieweritemFree(vieweritem *item)
{
  vdebugIF(!vieweritemPool, vexGenerate(vexGetModuleStateClass(), vexMESSAGE,
           "item free: pool not allocated!?", vexERRNO, 0, vexNULL));
  if (item && item->pool)
    vpoolFree(vieweritemPool, (void*)item);
}

/********
 * vieweritemDetermineDisplayedImage
 *
 * ->
 * <- void
 ********/
void
vieweritemDetermineDisplayedImage(viewer *view, vieweritem *item, 
				  viconviewView *iconiconview)
{
  vpoint *thumbsize = &view->thumbsize;

  vdebugIF(!item || !item->sniffed, vexGenerate(vexGetArgNullClass(),
           vexMESSAGE, "determine item image: NULL item or store image!",
           vexERRNO, 0, vexNULL));
  vdebugIF(!item->icon, vexGenerate(vexGetArgNullClass(),
           vexMESSAGE, "determine item image: NULL iconview icon!",
           vexERRNO, 0, vexNULL));

  /* create a thumbnail if necessary (only if image LARGER) */
  if (!item->thumbnail && (vimageGetWidth (item->sniffed)>thumbsize->x ||
			   vimageGetHeight(item->sniffed)>thumbsize->y)) {
    vmatrix mtx;

    /* remember the scale maps coordinates from thumbnail space to 
     * image space, so we need the inverse of the scale thumb::image!*/
    vmatrixScale(vmatrixIdent(), 
		 (double)vimageGetWidth(item->sniffed)/(double)thumbsize->x, 
		 (double)vimageGetHeight(item->sniffed)/(double)thumbsize->y, 
		 &mtx);

    item->thumbnail = vwindowCreateBufferImage(thumbsize->x, thumbsize->y);
    vdrawGSave();
    vdrawImageDevice(item->thumbnail);
    vdrawMoveTo(0,0);
    vdrawSetColor(vdialogDetermineItemBackground(viconviewGetItem
                  (viewerGetIconview(view))));
    vdrawRectFill(0, 0, thumbsize->x, thumbsize->y);
    vdrawMoveTo(0,0);
    vdrawImageComposite(item->sniffed, &mtx);
    vdrawGRestore();

    /* remember we've scaled the sniffed image */
    item->thumbnailname = vnameInternGlobalScribed
      (vscribeScribeMulti(vnameScribeGlobal(item->name), 
			  vcharScribeLiteral("{scale}"), NULL));
    item->munged = vTRUE;
  }

  /* figure out which image is displayed */
  if (!viewerShowThumbnail(view) || !item->thumbnail) {
    if (item->displayed != item->sniffed) {
      item->displayed = item->sniffed;
      viconviewSetIconName(item->icon, item->name);
      viconviewSetIconImage(item->icon, iconiconview, item->displayed);
    }
  }
  else {
    if (item->displayed != item->thumbnail) {
      item->displayed = item->thumbnail;
      viconviewSetIconName(item->icon, item->thumbnailname);
      viconviewSetIconImage(item->icon, iconiconview, item->displayed);
    }
  }
}

/********
 * vieweritemNukeThumbnail
 *
 * ->
 * <-
 ********/
void
vieweritemNukeThumbnail(vieweritem *item)
{
  vdebugIF(!item, vexGenerate(vexGetArgNullClass(), vexMESSAGE, 
           "nuke item thumbnail: NULL item!", vexERRNO, 0, vexNULL));

  if (item && item->thumbnail && item->munged) {
    vimageDestroy(item->thumbnail);
    item->thumbnail = NULL;
    item->munged = vFALSE;
  }

}

/********
 * vieweritemDestroy destroy a vieweritem and all associated memory.
 * this WILL destory any associated images!
 *
 * -> item, viewer item to destroy
 * <- void
 ********/
void
vieweritemDestroy(vieweritem *item)
{
  vdebugIF(!item, vexGenerate(vexGetArgNullClass(), vexMESSAGE, 
           "destroy item: NULL item!", vexERRNO, 0, vexNULL));

  vieweritemNukeThumbnail(item);
  vieweritemFree(item);
}



/*
 *+------------------------------------------------------------------------+
 * private: viewing the temp/perm icon files (small ahem...hack to test
 * image stores. we assume full knowledge of image managers classes!)
 *+------------------------------------------------------------------------+
 */

#if vdebugDEBUG
#undef vdebugTAG
#define vdebugTAG _viewerTag
#endif


#define MAXLISTING 50 /* most items show in popup of viewer items */

/********
 * viewerAlloc allocs and initializes a new viewer structure.
 *
 * -> void
 * <- view, newly created view
 *********/
static viewer*
viewerAlloc(void)
{
  register viewer     *view;
  const isnifferPrefs *prefs = isnfGetPreferences();

  view = vmemAllocAndClear(sizeof(viewer));
  view->root        = vresourceNULL;
  view->store 	    = vresourceNULL;
  view->ignoresave  = vTRUE;

  view->thumbnail   = prefs->thumbnails;
  view->fullpath    = prefs->titles;
  view->thumbsize.x = view->thumbsize.y = prefs->diff_thumbsize ? 
    prefs->thumbsize : isnfMIN_THUMBSIZE;

  return view;
}

/********
 * viewerLookup returns the viewer that maps to a given file
 * path. returns NULL if no match.
 *
 * -> path,   the snooped file's (full) path
 * -> 0,      snoop options for file (ignored for now)
 * -> posref, [fill-in] the viewer's index in the global viewer
 *            array
 * <- viewer, NULL if no match, else the viewer reference
 ********/
static viewer*
viewerLookup(const vchar *filepath, unsigned options, int *pos)
{
  viewer          	*view = NULL;
  register viewer 	**scan,**stop;
  viewer	  	**start;

  if (pos)
    *pos = -1;
  if (viewers && tarrayGetNumber(viewers)>0) {
    scan = start = tarrayAtStartAs(viewers,viewer**);
    stop = tarrayAtStopAs(viewers,viewer**); 
    for (; scan<stop; scan++)
      if (vcharCompare((*scan)->from, filepath)==0) {
	view = *scan;
	if (pos) 
	  *pos = scan-start;
	break;
      }
  }
  return view;
}

/********
 * viewerCreate create a new viewer structure and associates it
 * with the given snoop file. viewerLookup should be called before
 * this routine to make sure the file hasn't already been attached
 * to a viewer!
 *
 * -> path,    the snooped file's (full) path
 * -> image,   [optional] the initial stack of images from the snoop 
 * -> file,    the resource file that's being searched
 * -> graphic, status graphic for this snoop (updated as images
 *	       are added
 * <- viewer,  the new viewer or NULL if the tempfile couldn't be
 *	       created
 ********/
static viewer*
viewerCreate(const vchar *filepath, tstack *images, vresource scanfile,
	     statusgraphic *graphic)
{
  viewer *view;

  view = viewerAlloc();
  view->temp = tempfileCreate(filepath);
  if (!view->temp) {
    vmemFree(view);
    view = NULL;
  }
  else {
    view->from = vstrClone(filepath);
    tempfileCreateImageAdder(view, images, scanfile, graphic);
    if (!viewers) viewers = tarrayCreate(sizeof(viewer*));
    tarrayAppendItem(viewers, &view);
    vdebugAdvise("created: %s\n", (char*)filepath);
  }
  return view;
}

/********
 * viewerUpdate adds another batch of sniffed images to a viewer.
 *
 * -> viewer, the viewer
 * -> images, the stack of images
 * <- void
 ********/
static void
viewerUpdate(register viewer *view, tstack *images)
{
  vdebugIF((!view), vexGenerate(vexGetArgNullClass(), vexMESSAGE,
           "update: NULL viewer -- need to create first!", 
           vexERRNO, 0, vexNULL));
  tempfileAddImagesToImageAdder(view->adder, images);
  return;
}

/********
 * viewerGetIconview returns the viconview used by the viewer
 * dialog to display thumbnails of the snooped images
 *
 * -> viewer, the viewer
 * <- iconview
 ********/
viconview*
viewerGetIconview(viewer *view)
{
  vdebugIF(!view, vexGenerate(vexGetArgNullClass(), vexMESSAGE, 
           "get iconview: NULL view argument", vexERRNO, 0, vexNULL));
  return (viconview*)vdialogFindItem(view->dialog, appname_ViewerView);
}

/********
 * viewerFromContext takes a vcommand context dictionary and returns
 * the associated viewer or NULL of none. should only be used from
 * viewer command spaces!
 *
 * -> context, the command context dictionary
 * <- viewer,  the viewer
 ********/
viewer*
viewerFromContext(vdict *context)
{
  vdialog *dialog;
  dialog = (vdialog*)vdictLoad(context, vname_Dialog);
  vdebugIF((!dialog), vexGenerate(vexGetValueNullClass(), vexMESSAGE,
           "from context: no dialog in context!", vexERRNO, 0, vexNULL));
  return (viewer*)vdialogGetData(dialog);
}

/********
 * viewerCreateFileIcon creates a icon for the viewer document and 
 * adds it to the main window.
 *
 * -> path,   the full path of the snooped file
 * -> viewer, the associated viewer
 * <- void
 ********/
static void
viewerCreateFileIcon(const vchar *filepath, viewer *view)
{
  isnifferApp	*app = isnfGet();
  int		last;
  viconviewIcon	*icon;
  viconview	*iconview;
  vdomainObject	*iobj, *nobj;
  viewericon	*data;

  data = (viewericon*)vmemAlloc(sizeof(viewericon));
  data->path = vfsPathFromStr(filepath);
  data->tag  = appname_TempFileIcon;
  last = vfsGetPathElementCount(data->path)-1;
  icon = viconviewCreateIcon();
  viconviewSetIconName(icon, vfsGetPathElementAt(data->path,last));
  viconviewSetIconData(icon, data);
  iconview = (viconview*)vdialogFindItem(app->requestor, appname_ReqView);
  viconviewSetIconImage(icon, viconviewGetIconView(),
          imanagerRetrieveGlobalImage(iman, data->tag));
  viconviewAddIcon(iconview, icon);
  viconviewGetIconObjects(icon, &iobj, &nobj);
  vdomainviewScrollToObject(viconviewGetDomainView(iconview),iobj,
			    5,5,5,5,vTRUE,NULL,NULL);
  view->icon = icon;
  return;
}

/********
 * viewerSwitchFileIcon switches the viewer's document icon between
 * its open and closed states. a viewer is open if it's window is
 * open.
 *
 * -> viewer, the viewer
 * -> tag,    the new state represented by the image's key
 * <- void
 ********/
void
viewerSwitchFileIcon(register viewer *view, const vname *newtag)
{
  register viewericon *data;

  data = (viewericon*)viconviewGetIconData(view->icon);
  imanagerReleaseGlobalImage(iman, viconviewGetIconImage(view->icon,
		    viconviewGetIconView()), data->tag);
  data->tag = newtag;
  viconviewSetIconImage(view->icon, viconviewGetIconView(),
                   imanagerRetrieveGlobalImage(iman, data->tag));
  return;
}

/********
 * viewerSelectFileIcon is called when the user double clicks on the
 * viewers document icon. just opens the viewer window.
 *
 * -> iconview, the iconview
 * -> icon,     the selected icon
 * -> event,    the trigger event
 * -> selected, TRUE if selected
 * <- void
 ********/
static void
viewerSelectFileIcon(viconview *iconview, viconviewIcon *icon, vevent *event, 
		     vbool selected)
{
  if (event && selected && veventGetPointerClickCount(event)==2) {
    vstr *filepath;
    viewer *view;
    filepath = vfsPathToStr(((viewericon*)viconviewGetIconData(icon))->path);
    view = viewerLookup(filepath,0,NULL);
    vstrDestroy(filepath);
    vdebugIF((!view), vexGenerate(vexGetReturnNullClass(), vexMESSAGE,
             "select file icon: no view associated with icon!", vexERRNO, 0,
              vexNULL));
    viewerOpen(view);
  }
  return;
}

/********
 * viewerCreateDialog creates a new dialogue for a image viewer. note
 * this does NOT add the viewer to the main document list! the viewer's
 * structure is updated to hold the new dialog information.
 *
 * -> viewer, the viewer
 * <- void
 ********/
static void
viewerCreateDialog(viewer *view)
{
  isnifferApp		*app = isnfGet();
  register vdialog	*dialog;
  appCommandSpace	*aspace;
  vcommandFunction	*com;
  vresource		 res;
  vdomainview		*domview;

  /* ze dialogue */
  res = vresourceGet(app->resources, appname_ViewerDialog);
  dialog = vdialogLoad(res);
  vdialogPlace(dialog, app->requestor, 
	       vrectPLACE_STRADDLE|vrectPLACE_RIGHT, vrectPLACE_CENTER);
  vwindowSetLeader(vdialogGetWindow(dialog), vdialogGetWindow(app->requestor));
  vdialogSetIcon(dialog, app->viewerIcon);

  /* for (hopefully) faster scrolling */
  domview = (vdomainview*)vdialogFindItem(dialog, appname_ViewerView);
  vdomainviewSetOffscreenDrawing(domview, vTRUE);

  /* ze save-confirmation */
  vdialogSetCloseHook(dialog, viewerHandleWindowManagerCloseRequest);

  /* ze clothes commands */
  aspace = &view->aspace;
  appInitCommandSpaceDescription(vcommandCreateSpace(), aspace);
  vwindowSetSpaceOwned(vdialogGetWindow(dialog), aspace->space);
  com = vcommandCreateFunction();
  vcommandSetFunctionIssue(com, viewerCloseCommand);
  appAddUnivFunctionToCommandSpaceDescription(aspace, vname_Close,
                      com, vkeyNULL_STROKE);
  com = vcommandCreateFunction();
  vcommandSetFunctionIssue(com, viewerCloseCommand);
  appAddUnivFunctionToCommandSpaceDescription(aspace, appname_CloseMenuAct,
                      com, vkeyNULL_STROKE);

  /* ze hide command */
  com = vcommandCreateFunction();
  vcommandSetFunctionIssue(com, viewerHideCommand);
  appAddUnivFunctionToCommandSpaceDescription(aspace, appname_HideAct,
                      com, vkeyNULL_STROKE);

  /* toggle displayed views */
  com = vcommandCreateFunction();
  vcommandSetFunctionIssue(com, viewerToggleDisplayCommand);
  vcommandSetFunctionQuery(com, viewerToggleDisplayQuery);
  appAddUnivFunctionToCommandSpaceDescription(aspace,
                      appname_ToggleThumbnailAct, com, vkeyNULL_STROKE);

  /* toggle full pathnames in titles */
  com = vcommandCreateFunction();
  vcommandSetFunctionIssue(com, viewerToggleTitlesCommand);
  vcommandSetFunctionQuery(com, viewerToggleTitlesQuery);
  appAddUnivFunctionToCommandSpaceDescription(aspace,
                      appname_ToggleTitlesAct, com, vkeyNULL_STROKE);

  /* cleanup viewer icons */
  com = vcommandCreateFunction();
  vcommandSetFunctionIssue(com, viewerCleanupCommand);
  appAddUnivFunctionToCommandSpaceDescription(aspace,
                      appname_CleanupAct, com, vkeyNULL_STROKE);

  /* done */
  view->dialog = dialog;
  vdialogSetData(dialog, view);
  viewerSetTitle(view);
  return;
}

/********
 * viewerSetMenu sets the menu associated with the viewer's 
 * viconview.
 *
 * -> viewer, the viewer
 * -> menu,   the new menu
 * <- void
 ********/
static void
viewerSetMenu(viewer *view, vmenu *menu)
{
  vdialogItem *ditem;
  ditem = vdialogFindItem(view->dialog, appname_ViewerView);
  vdialogSetItemMenu(ditem, menu);
  return;
}

/********
 * viewerMakeMenu creates a menu of all the _original_ sniffed images
 * in the viewer; list does not take any edits into account. the menu
 * is _not_ attached to the view!
 *
 * -> viewer, the viewer
 * <- menu,   the new image menu
 ********/
static vmenu*
viewerMakeMenu(viewer *view)
{
  const vname		**tags;
  register vmenuItem	*item;
  vstr			*title;
  register const vname	**scan;
  vmenu			*menu;
  register int		num;

  /* we could easily iterate over the iconview, but i wanna
   * test the image mangler; besides, the image manager returns
   * an exclusive listing (no duplicates),so here goes...*/
  tags = imanagerCreateListingOfImageStoreImages(iman, view->store);
  if (!tags) {
    menu = NULL;
  }
  else {
    /* brand spanking new */
    menu = vmenuCreate();

    /* insert a "fake" title */
    item = vmenuCreateItem();
    title = isnfStrFrom(strTitleImagesListing);
    vmenuSetItemTitle(item, title);
    vstrDestroy(title);
    vmenuDisableItem(item);
    vmenuAppendItem(menu, item);
    item = vmenuCreateSeparatorItem();
    vmenuAppendItem(menu, item);

    /* insert the listing after separator */
    for (scan=tags,num=0; *scan && num!=MAXLISTING; scan++,num++) {
      item = vmenuCreateItem();
      vmenuSetItemTitle(item, *scan); /* ?!use shared scribe!? */
      vmenuAppendItem(menu, item);
    }

    /* and now for the wimpy way to deal with a ui problem... */
    if (*scan && num==MAXLISTING) {
      item = vmenuCreateItem();
      title = isnfStrFrom(strTitleImagesListingTooLong);
      vmenuSetItemTitle(item, title);
      vstrDestroy(title);
      vmenuDisableItem(item);
      vmenuAppendItem(menu, item);
    }

    /* cleanup listing */
    imanagerDestroyListingOfImageStoreImages(iman, view->store, tags);
  }

  /* done */
  return menu;
}

/********
 * viewerCreateIcons loads/forms all the sniffed images for the viewer
 * into the iconview. this is particularly slow for lots of images.
 * (viconview optimization?)
 *
 * -> viewer, the viewer
 * <- void
 ********/
static void
viewerCreateIcons(viewer *view)
{
  register viconviewIcon	*icon;
  register viconview		*iconview;
  register int			 i,count;
  vresource			 images, ires;
  const vname			*tag;
  vieweritem			*item;

  /* fix so we load images as necessary */
  iconview = (viconview*)vdialogFindItem(view->dialog, appname_ViewerView);
  viconviewSetData(iconview, view);
  view->draw = vdomainviewGetDrawObjectProc(viconviewGetDomainView(iconview));
  vdomainviewSetDrawObjectProc(viconviewGetDomainView(iconview), viewerDrawItem);
  vdomainviewSetData(viconviewGetDomainView(iconview), view);
  viconviewSetView(iconview, viconviewGetIconView());

  /* setup to activate command triggers based on selection */
  viconviewSetSelectNotify(iconview, viewerEditHandleSelectIcon);

  /* entertain user <for >20 items it's noticeable> */
  isnfInformUserByMessageBoxImmediately(msgUnpackingSnoopedImagesToMemory);
  isnfSpinDocktorWannaSpinPlease();

  /* load the view with all snooped images (long...) */
  images = vresourceGet(view->store, name_Images);
  count  = vresourceCountComponents(images);
  for (i=0; i<count; i++) {
    ires = vresourceGetNthComponent(images, i, &tag);
    item = vieweritemAlloc();
    item->tag  = tag;
    item->name = tag;
    icon = viconviewCreateIcon();
    item->icon = icon;
    viconviewSetIconName(icon, item->name);
    viconviewSetIconData(icon, item);
    viconviewAddIcon(iconview, icon);
    if ((i%isnfIMAGE_BATCH_SIZE)==0) isnfSpinDocktorSpinBabySpin();
  }

  /* finished long operation */
  isnfSpinDocktorStopImTooDizzy();

  return;
}

/********
 * viewerOpen opens a viewer dialog; this opens the viewer's document
 * icon.
 *
 * -> viewer, the viewer
 * <- void
 ********/
static void
viewerOpen(register viewer *view)
{
  int check = vFALSE;

  /* if don't already got one o' dem dialogues */
  if (!view->dialog) {
    /* if we snooped lots o' images this could be long */
    isnfBlock(NULL);

    /* ze dialogue, also creates command space */
    viewerCreateDialog(view);

    /* ze icons store */
    tempfileGetResources(view->temp, &view->root, &view->store, NULL);
    imanagerRegisterAsImageStore(iman, view->store);
    viewerCreateIcons(view);
    viewerSetMenu(view, viewerMakeMenu(view));

    /* attach file/edit commands, commit cmds to space */
    viewerFileAttachCommands(view);
    viewerEditAttachCommands(view);
    appCommitCommandSpaceDescription(&view->aspace);

    /* unblock a long operation */
    isnfUnBlock();
  }
  else
    check = vTRUE;

  /* reflect the open state in requestor window */
  viewerSwitchFileIcon(view, view->perm ? appname_OpenedPermFileIcon 
		       : appname_OpenedTempFileIcon);

  /* ze open */
  vdialogOpen(view->dialog);
  if (check)
    vwindowRaise(vdialogGetWindow(view->dialog));

  return;
}

/********
 * viewerTouch marks the viewer document as dirty/clean. if the
 * viewer is marked dirty, the user is prompted to save changes
 * when the viewer's dialog is closed.
 *
 * -> viewer, the viewer
 * -> [t/f],  TRUE if dirty, FALSE otherwise
 * <- void
 ********/
void
viewerTouch(viewer *view, int value)
{
  view->dirty = value ? vTRUE : vFALSE;
  return;
}

/********
 * viewerDestroyIcons destroys all sniffed icons associated with a 
 * viewer's iconview. called by viewerDestroy.
 *
 * -> viewer, the viewer
 * <- void
 ********/
static void
viewerDestroyIcons(viewer *view)
{
  register viconview	       	*iconview;
  viconviewIterator		 iterator;
  register viconviewIterator   	*iter= &iterator;
  register viconviewIcon	*icon;
  vieweritem			*item;

  iconview = viewerGetIconview(view);
  viconviewInitIterator(iter, iconview);
  imanagerSetActiveImageStore(iman, view->store);
  while (viconviewNextIterator(iter)) {
    icon = viconviewGetIteratorIcon(iter);
    item = (vieweritem*)viconviewGetIconData(icon);
    if (item->loaded)
      imanagerReleaseImage(iman, item->sniffed, item->tag);
    viconviewSetIconData(icon, NULL);
    vieweritemDestroy(item);
  }
  viconviewDestroyIterator(iter);
  imanagerUnRegisterAsImageStore(iman, view->store);

  return;
}

/********
 * viewerDestroy nukes a viewer and all associated memory. the temporary
 * image file is destroyed if it hasn't been explicitly saved.
 *
 * -> viewer, the viewer
 * <- void
 ********/
static void
viewerDestroy(register viewer *view)
{
  vdebugIF((!view), vexGenerate(vexGetArgNullClass(), vexMESSAGE,
           "destroy: NULL view argument!", vexERRNO, 0, vexNULL));
  vdebugIF(view->from, vdebugAdvise("viewer: deleted %s\n", (char*)view->from));

  viewerEditDestroy(view);

  if (view->from) {
    int	pos;
    if (viewerLookup(view->from, 0, &pos))
      tarrayDeleteItem(viewers, pos);
  }
  if (view->store!=vresourceNULL && view->dialog)
    viewerDestroyIcons(view);
  if (view->dialog)
    vdialogDestroy(view->dialog);

  if (view->root!=vresourceNULL)
    vresourceCloseFile(view->root);

  if (!view->ignoresave && view->save && view->temp)
    viewerMoveTempFileToPermanentFile(view);

  if (view->temp) {
    vfsRemove(view->temp);
    vfsDestroyPath(view->temp);
  }

  if (view->from)
    vstrDestroy(view->from);
  if (view->perm)
    vfsDestroyPath(view->perm);

  vmemFree(view);
  return;
}

/********
 * viewerDestroyFileIcon nukes the viewer's document icon from the
 * mainview's icon list.
 *
 * -> icon, the viconview icon
 * <- void
 ********/
static void
viewerDestroyFileIcon(viconviewIcon *icon)
{
  register viewericon *data;
  data = (viewericon*)viconviewGetIconData(icon);
  imanagerReleaseGlobalImage(iman, 
    viconviewGetIconImage(icon,viconviewGetIconView()), data->tag);
  vfsDestroyPath(data->path);
  vmemFree(data);
  return;
}

/********
 * viewerLoadItem is called to retrieve an icon reference from the
 * image manager. when icons are added to the iconview they're not
 * acutally loaded/formed until necessary (ie. when shown or printed).
 *
 * -> viewer, the viewer
 * -> icon,   the icon that needs loading
 * <- void
 ********/
void
viewerLoadItem(viewer *view, register viconviewIcon *icon)
{
  vieweritem 	*item;

  vdebugAdvise("loading icon: %s\n", (char*)viconviewGetIconName(icon));
  item = (vieweritem*)viconviewGetIconData(icon);

  /* always store the image we retrieve from the store separately */
  imanagerSetActiveImageStore(iman, view->store);
  item->sniffed = imanagerRetrieveImage(iman, item->tag, NULL);

  /* determine what image to display (we allow thumbnails of really
   * humongous images) */
  vieweritemDetermineDisplayedImage(view, item, viconviewGetIconView());

  item->loaded = vTRUE;
  return;
}

/********
 * viewerDrawItem is called to draw each object in the viewer's viconview.
 * this routine will load the image if this is the first time it's being
 * drawn.
 *
 * -> domview, the iconview's vdomainview
 * -> object,  the specific object to draw
 * <- void
 ********/
static void
viewerDrawItem(vdomainview *dview, vdomainObject *obj)
{
  viewer *view;
  viconviewIcon	*icon;

  view = (viewer*)vdomainviewGetData(dview);
  icon = viconviewIconFromObject(obj);
  if (!viewerGetIconItem(icon)->loaded)
    viewerLoadItem(view, icon);
  view->draw(dview, obj);
  return;
}

/********
 * viewerClose closes/destroy the viewer's dialog. if the user has changed
 * the viewer's image list, the user is prompted to save the changes to a
 * permanent file.
 *
 * -> viewer, the viewer
 * <- void
 ********/
static void
viewerClose(viewer *view)
{
  if (!view->dirty)
    viewerDestroyLater(view);
  else
    isnfAskUser(msgWantToPermanentlySaveChanges, vTRUE, 
		viewerHandleUserResponseToSaveRequest, view, view->dialog);
  return;
}

/********
 * viewerHandleDestroyLater is called to handle a destroy later request
 * for a viewer. see viewerDestroyLater.
 *
 * -> event, the client event
 * <- TRUE
 ********/
static int
viewerHandleDestroyLater(vevent *event)
{
  isnifferApp *app = isnfGet();
  viewer      *view = (viewer*)veventGetClientData(event);

  vdebugAdvise("viewer: closing %s\n", (char*)view->from);
  if (view->icon) {
    viconview *iconview;
    iconview = (viconview*)vdialogFindItem(app->requestor,appname_ReqView);
    viconviewRemoveIcon(iconview, view->icon);
    viewerDestroyFileIcon(view->icon);
    viconviewDestroyIcon(view->icon);
    view->icon = NULL;
  }

  viewerDestroy(view);
  return vTRUE;
}

/********
 * viewerDestroyLater posts a client event that will do the actual
 * destroy of a viewer. used if the user selects 'NO' from the save changes
 * confirmation notice.
 *
 * -> viewer, the viewer to destroy later
 * <- void
 ********/
static void
viewerDestroyLater(viewer *view)
{
  register vevent *event;
  event = veventCreateClient();
  veventSetPriority(event, veventPRIORITY_MAX);
  veventSetTarget(event, viewerHandleDestroyLater);
  veventSetClientData(event, view);
  veventPost(event);
  return;
}

/********
 * viewerSetTitle updates the viewer dialog's title based on the current
 * "full titles" option and the saved state of the sniffed file. Note the
 * full titles option is initialized at dialog creation time.
 *
 * -> view, the viewer
 * <- void
 ********/
void
viewerSetTitle(viewer *view)
{
  vstr	*longform;

  if (view->save)
    longform = vfsPathToStr(view->perm);
  else
    longform = vstrCopyMulti(name_FileFrom, view->from, NULL, NULL);

  if (view->fullpath)
    vdialogSetTitle(view->dialog, longform);
  else {
    const vchar *cp;
    const vchar *pathSep;

    pathSep = vfsGetPathSeparatorString();
    cp = vcharSearchBackwards(longform, pathSep);
    if (!cp)
      vdialogSetTitle(view->dialog, longform);
    else
      vdialogSetTitle(view->dialog, &cp[vcharLength(pathSep)]);
  }

  vstrDestroy(longform);
}


/********
 * viewerHandleWindowManagerCloseRequest is called when the user selects
 * the "close" item from the window manager menu or frame (this is the
 * "go-away" box on the mac).
 *
 * -> dialog, the viewer dialog
 * -> event,  the associated event (ignored)
 * <- TRUE,   tells the vwindow manager _not_ to close the window
 ********/
static int
viewerHandleWindowManagerCloseRequest(vdialog *dialog, vevent *event)
{
  viewer *view;
  view = (viewer*)vdialogGetData(dialog);
  if (!isnfIsBlocked()) viewerClose(view);
  else isnfInformUser(msgNeedToCompleteTheSaveInProgress, dialog);
  return vTRUE; /* -> let our code do the close */ 
}

/********
 * viewerCloseCommand is called when the user selects "Close"
 * from the viewer's dialog menu. just calls viewerClose
 *
 * -> command, the command
 * -> context, the command's context
 * <- TRUE
 ********/
static int
viewerCloseCommand(vcommandFunction *func, vdict *context)
{
  viewer *view = viewerFromContext(context);
  viewerClose(view);
  return vTRUE;
}

/********
 * viewerHideCommand is called when the user selects "Hide"
 * from the viewer's dialog menu. closes the viewer's dialog
 * without destroying it.
 *
 * -> command, the command
 * -> context, the command's context
 * <- TRUE
 ********/
static int
viewerHideCommand(vcommandFunction *func, vdict *context)
{
  viewer *view = viewerFromContext(context);
  vdialogClose(view->dialog);
  viewerSwitchFileIcon(view, view->perm ? appname_PermFileIcon 
		       : appname_TempFileIcon);
  return vTRUE;
}

/********
 * viewerHandleUserResponseToSaveRequest is called then the user
 * selects "Yes", "No", or "Cancel" from the save changes confirmation
 * dialog.
 *
 * -> reply, the response [yes,no,cancel]
 * -> data,  data field (as passed to isnfAskUser). contains our
 *           viewer's reference
 * <- void
 ********/
static void
viewerHandleUserResponseToSaveRequest(int reply, void *data)
{
  viewer *view = (viewer*)data;
  switch (reply) {
    case responseYES: {
      viewerSave(view);
      if (viewerIsWaiting(view))
	break;
    }
    case responseNO:  {
      viewerDestroyLater(view);
      break;
    }
  }
  return;
}


/********
 * viewerToggleDisplayCommand is called when the user toggles the
 * display-by (thumbnail or original) option.
 *
 * -> command, the command
 * -> context, the command's context
 * <- TRUE
 ********/
static int
viewerToggleDisplayCommand(vcommandFunction *func, vdict *context)
{
  viewer 			*view = viewerFromContext(context);
  const vname			*value;
  vbool		 		 wasOn;
  register viconview	       	*iconview;
  viconviewIterator		 iterator;
  register viconviewIterator   	*iter= &iterator;
  register viconviewIcon	*icon;
  vieweritem			*item;

  wasOn = view->thumbnail;  
  value = (const vname*)vdictLoad(context, vname_Toggle);
  view->thumbnail = (value==vname_On) ? vTRUE : vFALSE;

  if (wasOn != view->thumbnail) {
    iconview = viewerGetIconview(view);
    viconviewInitIterator(iter, iconview);
    imanagerSetActiveImageStore(iman, view->store);
    while (viconviewNextIterator(iter)) {
      icon = viconviewGetIteratorIcon(iter);
      item = (vieweritem*)viconviewGetIconData(icon);
      if (item->loaded && item->munged)
	vieweritemDetermineDisplayedImage(view, item, viconviewGetIconView());
    }
    viconviewDestroyIterator(iter);
  }
  
  return vTRUE;
}

static int
viewerToggleDisplayQuery(vcommandFunction *func, vdict *context)
{
  viewer *view = viewerFromContext(context);
  vdictStore(context, vname_Toggle, view->thumbnail ? vname_On : vname_Off);
  return vTRUE;
}


/********
 * viewerToggleTitlesCommand is called when the user toggles the
 * full-titles option.
 *
 * -> command, the command
 * -> context, the command's context
 * <- TRUE
 ********/
static int
viewerToggleTitlesCommand(vcommandFunction *func, vdict *context)
{
  viewer	*view = viewerFromContext(context);
  const vname 	*value;

  value = (const vname*)vdictLoad(context, vname_Toggle);
  view->fullpath = (value==vname_On) ? vTRUE : vFALSE;
  viewerSetTitle(view);

  return vTRUE;
}

static int
viewerToggleTitlesQuery(vcommandFunction *func, vdict *context)
{
  viewer *view = viewerFromContext(context);
  vdictStore(context, vname_Toggle, view->fullpath ? vname_On : vname_Off);
  return vTRUE;
}


/********
 * viewerCleanupCommand
 *
 * ->
 * <- TRUE
 ********/
static int
viewerCleanupCommand(vcommandFunction *com, vdict *context)
{
  viewer *view = viewerFromContext(context);
  viconviewCleanup(viewerGetIconview(view));
  return vTRUE;
}



/********
 * viewerInstallDelayHandler is called to install a delayed task.
 * for example, a hook handler from a file chooser. to support system-modal 
 * native dialogs, we postpone actually opening or doing long 
 * procedures 'til after the dialog's been dismissed (or at list
 * the apply returns).
 *
 * -> handler, the event handler
 * -> data,    any data caller wants associated w/ event
 * <- void
 ********/
void
viewerInstallDelayHandler(veventHandlerProc handler, void *data)
{
  register vevent *event;

  event = veventCreateClient();

  veventSetTarget(event, handler);
  veventSetPriority(event, veventPRIORITY_MAX);
  veventSetClientData(event, data);

  veventPost(event);
}


/********
 * viewerMatchOnlyImages
 *
 * -> 
 * <- [t/f], TRUE if include item in object set
 ********/
vbool
viewerMatchOnlyImages(vdomain *dom, vdomainSelection sel, 
		      vdomainObject *obj)
{
  return vdomainGetObjectType(dom, obj)==viconviewIMAGE_TYPE;
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

/* $Id: geticons.c,v 1.4 1996/11/05 20:35:20 lis Exp $ */
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
 *     Scans a given resource file for all vimages; can handle an arbitary  *
 *     number of files at once (using client events to do the actual file   *
 *     reading). Any found images are passed to an "observer"; in our case  *
 *     the snooper and/or viewer modules.                                   *
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
#include vdictHEADER
#include vfsHEADER
#include vresourceHEADER
#include veventHEADER
#include vclientHEADER
#include vimageHEADER
#include vstdHEADER

/* Our headers */
#include "tstack.h"
#include "geticons.h"


/* Our debug tag for the vdebug manager */
#if vdebugDEBUG
static const char *const _moduleTag = "grab-icons";
#define vdebugTAG _moduleTag
#endif

/*
 *+------------------------------------------------------------------------+
 * private names
 *+------------------------------------------------------------------------+
 */
enum {
  VIMAGE,VPALETTE,
  VDIALOG,VCONFIRM,VNOTICE,
  VCONTAINER,VCONTAINER_GRP,
  VICONVIEW,VMAINVIEW,
  VNOTEBOOK,
  NAME_COUNT
};

static const vname *names[NAME_COUNT];
static const char  *literals[NAME_COUNT]= {
  "vimage", "vpalette", "vdialog", "vconfirm", "vnotice",
  "vcontainer", "vcontainerGroup",
  "viconview", "vmainview", "vnotebook"
};

#define name_vimage		names[VIMAGE]
#define name_vpalette		names[VPALETTE]
#define name_vdialog		names[VDIALOG]
#define name_vconfirm		names[VCONFIRM]
#define name_vnotice		names[VNOTICE]
#define name_vcontainer		names[VCONTAINER]
#define name_vcontainergroup	names[VCONTAINER_GRP]
#define name_viconview		names[VICONVIEW]
#define name_vmainview		names[VMAINVIEW]
#define name_vnotebook		names[VNOTEBOOK]

/*
 *+------------------------------------------------------------------------+
 * private constants, variables, prototypes
 *+------------------------------------------------------------------------+
 */

#define generateAlreadyProcessingException()	\
  vexGenerate(vexGetAppClass(), vexMESSAGE, "Already Processing...", \
	      vexERRNO, 0, vexNULL)
#define propagateCantOpenFileException() \
  vexPropagate(vexGetAppClass(), \
	       vexMESSAGE, "Problem Opening Resource File", vexERRNO, 0, \
	       vexNULL)


typedef struct scandata scandata;
typedef struct filedata filedata;
struct scandata {
  filedata	*file;		/* file we're scanning */ 
  vresource	 res;		/* dict or array parent */
  int		 next;		/* next component index */
  tstack	*stk;		/* stack of resources we're scanning */
  tstack        *others;	/* as we scan we remember children to scan */
  void	       (*proc)(scandata*, int *repost);  /* process index'th item */
};

struct filedata {
  vstr		       *filepath;	/* key for our global dictionary */
  tstack	       *images;		/* stack of images found so far */
  tstack	       *scans;		/* if suspended these are scans in progress */
  vresource	 	root;		/* root of our resource file */
  isnfSearchObserver	observer;	/* hook. notified at misc. points */
  int			numscans;	/* number of "simultaneous" scans */
  unsigned		recursive:1;	/* TRUE if can search children */
  unsigned		all:1;		/* TRUE if search objects as dicts */
  unsigned		preload:1;	/* TRUE if images should be loaded */
  unsigned	 	aborted:1;	/* TRUE if all scans should be terminated */
  unsigned		relinquished:1;	/* TRUE if relinquish images to observers */
  unsigned		suspended:1;	/* TRUE if all scans suspended */
};

static vdict		*files = NULL;		/* all processing files */
static vbool		 quitting = vFALSE;

static void	       	scanRememberImage(scandata*,vresource,const vname*);
static void		scanRememberOther(scandata*,vresource,const vname*);
static int		scanPrepareNextResource(scandata*);
static void		scanNew(filedata*,tstack*);
static void		scanDelete(scandata*);
static void		scanSuspend(scandata*);
static void		scanResume(filedata*);
static int		scanEventHandler(vevent*);
static void		scanPost(scandata*);
static void		scanFinish(scandata*);

static void		doclas(scandata*,vresource,const vname*);
static void		dotype(scandata*,vresource,const vname*);
static void		dodict(scandata*,vresource,const vname*);
static void		doarray(scandata*, vresource);
static void		nextditem(scandata*,int*);
static void		nextaitem(scandata*,int*);

static filedata	       *fileLookup(const vfsPath*);
static filedata	       *fileCreate(const vfsPath*,int,int,int,isnfSearchObserver);
static void		fileDelete(filedata*);
static void		fileFlushImages(filedata*);
static void		fileFlush(filedata*);

static void		startup(void);
static void		geticonsshutdown(void);

/*
 *+------------------------------------------------------------------------+
 * exported routines
 *+------------------------------------------------------------------------+
 */

/********
 * isnfSearchFile takes a resource file and tries to retrieve all the 
 * vimages it can find (how hard it looks can be controlled, to some 
 * degree, by sniffage options). the images are passed to an
 * observer which can assume ownership or let this module destroy
 * them once the sniffage is complete.
 *
 * -> path, the file to sniff
 * -> [t/f], TRUE if composite resources can be recursively searched
 * -> [t/f], TRUE if images should be preloaded and passed to the
 *           observer as a stack of vimages instead of a stack of 
 *           vresources
 * -> [t/f], TRUE if all composite resources should searched (nullifies
 *           the recursive option if TRUE)
 * -> procptr, observer - called when "interesting" events occur
 * <- string, stringized version of sniffee's file path; can be used
 *	     as key for other routines.
 *********/
const vstr*
isnfSearchFile(const vfsPath *path, int recursive, int preload, int all, 
	       isnfSearchObserver obs)
{
  filedata *file;

  vdebugIF((!path), vexGenerate(vexGetArgNullClass(), vexMESSAGE,
           "search file: NULL path argument!", vexERRNO, 0, vexNULL));

  file = fileLookup(path);
  if (file) 
    generateAlreadyProcessingException();

  if (!recursive && all) 
    all = vFALSE;
  file = fileCreate(path, recursive, preload, all, obs);

  return file ? (const vstr*)file->filepath : NULL;
}



/********
 * isnfAbandonSearch aborts sniffage on the given file. does nothing
 * if not sniffing file or the sniffage been completed.
 *
 * -> name, stringized version of the sniffee's file path.
 *          pass NULL to abandon -ALL- ongoing sniffs.
 * <- void
 *********/
void
isnfAbandonSearch(const vstr *filepath)
{
  register filedata *file;

  if (!files) 
    return;

  if (filepath) {
    file = (filedata*)vdictLoad(files,filepath);
    if (file) file->aborted = vTRUE;
  }
  else {
    vdictIterator iterator;
    register vdictIterator *iter= &iterator;
    vdictInitIterator(iter, files);
    while (vdictNextIterator(iter)) {
      file = (filedata*)vdictGetIteratorValue(iter);
      file->aborted = vTRUE;
    }
    vdictDestroyIterator(iter);
  }

  return;
}



/********
 * isnfSuspendSearch suspends sniffage on the given file. does nothing 
 * if not sniffing file or the sniffage has been completed.
 *
 * -> name, stringized version of the sniffee's file path.
 *          pass NULL to suspend -ALL- ongoing sniffages.
 * <- void
 *********/
void
isnfSuspendSearch(const vstr *filepath, int flush)
{
  register filedata *file;

  if (!files) 
    return;

  if (filepath) {
    file = (filedata*)vdictLoad(files,filepath);
    if (file) file->suspended = vTRUE;
    if (flush) fileFlush(file);
  }
  else {
    vdictIterator iterator;
    register vdictIterator *iter= &iterator;
    vdictInitIterator(iter, files);
    while (vdictNextIterator(iter)) {
      file = (filedata*)vdictGetIteratorValue(iter);
      file->suspended = vTRUE;
      if (flush) fileFlush(file);
    }
    vdictDestroyIterator(iter);
  }

  return;
}



/********
 * isnfResumeSearch resumes suspended sniffage on the given
 * file. does nothing if not sniffing file, the sniffage's been 
 * completed, or the sniffage is not suspended.
 *
 * -> name, stringized version of the sniffee's file path.
 *          pass NULL to resume -ALL- ongoing sniffages.
 * <- void
 *********/
void
isnfResumeSearch(const vstr *filepath)
{
  register filedata *file;

  if (!files) 
    return;

  if (filepath) {
    file = (filedata*)vdictLoad(files,filepath);
    if (file && file->suspended) {
      scanResume(file);
      file->suspended = vFALSE;
    }
  }
  else {
    vdictIterator iterator;
    register vdictIterator *iter= &iterator;
    vdictInitIterator(iter, files);
    while (vdictNextIterator(iter)) {
      file = (filedata*)vdictGetIteratorValue(iter);
      if (file->suspended) {
	scanResume(file);
	file->suspended = vFALSE;
      }
    }
    vdictDestroyIterator(iter);
  }

  return;
}


/*
 *+------------------------------------------------------------------------+
 * private routines - scans
 *+------------------------------------------------------------------------+
 */

/********
 * newstack creates a new tstack and initializes it's expand-by size
 * to 10.
 *
 * -> void
 * <- stack, new tstack
 *********/
static tstack*
newstack(void)
{
  register tstack *stk;
  stk = tstackCreateSized(10);
  tstackSetExpandSize(stk,10);
  return stk;
}

/********
 * scanRememberImage pushes a found image unto the scanner's
 * image stack. if the preload option is ON the item is stored
 * as the vimage otherwise it's stored as the vresource. calls
 * the observer with the "isnfSEARCH_FOUND_IMAGE" message.
 *
 * -> scan, scanner
 * -> img, the newly retrieved image resource
 * -> tag, [optional] the name associated w/ resource
 * <- void
 *********/
static void
scanRememberImage(scandata *scan, vresource img, const vname *tag)
{
  register filedata *file= scan->file;
  if (!file->images) 
    file->images = newstack();
  if (file->preload)
    tstackPush(file->images, vimageLoad(img));
  else
    tstackPush(file->images, img);
  if (file->observer)
    file->observer(file->filepath,isnfSEARCH_FOUND_IMAGE,tag);
  return;
}

/********
 * scanPrepareNextResource checks the scanner's resource stack
 * for the next resource to search. always returns FALSE if 
 * the scan's been aborted. calls the observer with the 
 * "isnfSEARCH_POP_RES" message.
 *
 * -> scan, scanner
 * <- [t/f], returns FALSE if nothing more to scan
 *********/
static int
scanPrepareNextResource(register scandata *scan)
{
  register vresource 	res = vresourceNULL;
  register size_t	num = 0;

  if (scan->file->aborted)
    return vFALSE;
  while (!tstackIsEmpty(scan->stk)) {
    res = tstackPopAs(scan->stk, vresource);
    if (scan->file->observer)
      scan->file->observer(scan->file->filepath,isnfSEARCH_POP_RES,1);
    num = vresourceCountComponents(res);
    if (num>0)
      break;
  }
  if (!num && tstackIsEmpty(scan->stk))
    return vFALSE;
  scan->res  = res;
  scan->proc = (vresourceType(res)==vresourceDICT) ? nextditem : nextaitem;
  scan->next = num-1;
  return vTRUE;
}

/********
 * scanRememberOther pushes a composite resource (dict or array) unto
 * the scanner's "other resource stack" for processing later. used for
 * sub-dictionary and sub-array resources while scanning a resource.
 *
 * -> scan, the scanner
 * -> res, the resource to remember
 * -> tag, the resource's associated name
 * <- void
 *********/
static void
scanRememberOther(register scandata *scan, vresource res, const vname* tag)
{
  if (!scan->others)
    scan->others = newstack();
  tstackPush(scan->others, res);
  return;
}

/********
 * scanNew creates a new scanner for the given file; the scan is posted
 * and begins the next time we return to the event loop. note the scan
 * isn't necessarily associated with the root resource of the file; it
 * can for example be a list of nested dictionaries found by another scan.
 * calls the observer with the "isnfSEARCH_PUSH_RES" message.
 *
 * -> file, the file to scan
 * -> resources, stack of base resources to scan
 * <- void
 *********/
static void
scanNew(filedata *file, tstack *resources)
{
  register scandata *scan;

  vdebugIF((!file || !resources), vexGenerate(vexGetArgNullClass(), 
           vexMESSAGE, "scanNew: NULL argument(s)!", vexERRNO, 0, vexNULL));
  scan = (scandata*)vmemAllocAndClear(sizeof(scandata));
  scan->file = file;
  scan->stk  = resources;
  if (scan->file->observer)
    scan->file->observer(scan->file->filepath, isnfSEARCH_PUSH_RES, 
			 tstackGetSize(resources));
  if (!scanPrepareNextResource(scan)) {
    scanDelete(scan);
    return;
  }
  else {
    file->numscans++;
    scanPost(scan);
  }
  return;
}

/********
 * scanDelete destroys a scanner and cleans up memory allocated
 * by it. the scanner should've aborted or finished before scanDelete
 * is called.
 *
 * -> scan, the scanner
 * <- void
 *********/
static void
scanDelete(scandata *scan)
{
  vdebugIF((!scan), vexGenerate(vexGetArgNullClass(), vexMESSAGE, 
           "scanDelete: NULL scan ref!", vexERRNO, 0, vexNULL));
  if (scan->others) tstackDestroy(scan->others);
  tstackDestroy(scan->stk);
  vmemFree(scan);
  return;
}

/********
 * scanSuspend suspends a scan in progress. suspended scans are
 * pushed unto a stack since a single file can have multiple
 * scans working simultaneously.
 *
 * -> scan, the scanner
 * <- void
 *********/
static void
scanSuspend(scandata *scan)
{
  register filedata  *file = scan->file;
  if (!file->scans) file->scans = tstackCreate();
  tstackPush(file->scans, scan);
  return;
}

/********
 * scanResume resumes all suspended scans for the given file; does 
 * nothing if the file snooping has was aborted or wasn't suspended. 
 * note there can be several independent scans working for a single 
 * file (for handling nested resources).
 *
 * -> file, the scanning file
 * <- void
 *********/
static void
scanResume(register filedata *file)
{
  register scandata *scan;
  vdebugIF(!file->scans, vexGenerate(vexGetArgClass(), vexMESSAGE,
           "scanResume: file has no scan stack!", vexERRNO, 0, vexNULL));
  while (!tstackIsEmpty(file->scans)) {
    scan = tstackPopAs(file->scans, scandata*);
    scanPost(scan);
  }
  tstackDestroy(file->scans);
  file->scans = NULL;
  return;
}

/********
 * scanEventHandler called to handle a "process scan" event. this
 * routine simply tells the scanner to do its thang and then reposts
 * itself if the scan wasn't completed. we use events to do actual
 * scanning st a) we can have lots of 'em going at one time and b)
 * the user can suspend or abort a file snoop.
 * 
 * #a# 	it's optimal to repost an existing event instead of creating
 * 	a whole new one.
 *
 * -> event, the event
 * <- TRUE
 *********/
static int
scanEventHandler(vevent *event)
{
  register scandata *scan;
  int repostSame;

  scan = (scandata*)veventGetClientData(event);
  if (scan->file->suspended)
    scanSuspend(scan);
  else {
    scan->proc(scan, &repostSame);
    if (repostSame) 
      veventPost(event); /* #a# */
    else if (scanPrepareNextResource(scan))
      veventPost(event); /* #a# */
    else
      scanFinish(scan);
  }
  return vTRUE;
}

/********
 * scanPost posts an event to do the actual scanning of the file.
 * using events enables us to process multiple files and multiple
 * searches with a single file. Also because we return to the
 * event loop often, the user can suspend/resume/abort snoops in
 * progress.
 *
 * #a#	use minimum priority to let updates, moosedowns, and keydowns
 * 	through!
 *
 * -> scan, the scanner
 * <- void
 *********/
static void
scanPost(scandata *scan)
{
  vevent *event;
  event = veventCreateClient();
  veventSetPriority(event, veventPRIORITY_MIN); /* #a# */
  veventSetTarget(event, scanEventHandler);
  veventSetClientData(event, scan);
  veventPost(event);
  return;
}

/********
 * scanFinish is called after a single scan is done. if while
 * scanning the scanner encountered nested resources (and saved them 
 * on its "other" stack), it initiates a new scan for those resources.
 * the observer is called with a "isnfSEARCH_END" message if there aren't
 * any more scans for the file. if the observer doesn't assume 
 * ownership of the found images, they are destroyed.
 *
 * -> scan, the scanner
 * <- void
 *********/
static void
scanFinish(scandata *scan)
{
  register filedata *file = scan->file;

  vdebugIF((!file->aborted && !tstackIsEmpty(scan->stk)), 
	   vexGenerate(vexGetArgClass(), vexMESSAGE, "scanFinish: "
           "scan not aborted and isn't finished!?", vexERRNO, 0, vexNULL));

  if (!file->aborted)
    if (scan->others && !tstackIsEmpty(scan->others)) {
      scanNew(scan->file, scan->others);
      scan->others = NULL;
    }
  file->numscans--;
  scanDelete(scan);
  if (!file->numscans) {
    int relinquish=vFALSE;
    if (!file->aborted) {
      if (file->observer)
	file->observer(file->filepath, isnfSEARCH_END, file->root, 
		       file->images, &relinquish);
      if (!file->relinquished)
	file->relinquished= relinquish;
      /* !possible that the observer aborted if problem! */
      if (file->aborted && file->relinquished)
	file->images = NULL;
    }
    fileDelete(file);
  }
  return;
}

/*
 *+------------------------------------------------------------------------+
 * private routines - interpreting resources
 *+------------------------------------------------------------------------+
 */

/********
 * doclas called to handle searching of some kind of vclass-based
 * resource. if recursive/all the sub-dictionaries are searched, 
 * otherwise just looks at base level for a directory with tag "Image" 
 * (see dotype routine).
 *
 * -> scan, the scanner
 * -> res, the resource to snoop
 * -> who, [optional] name associated with the resource
 * <- void
 *********/
static void
doclas(scandata *scan, vresource res, const vname *who)
{
  /* If not recursive just look at base level */
  if (!scan->file->recursive)
    dotype(scan, res, who);

  /* else if do as dict */
  else if (scan->file->all)
    scanRememberOther(scan, res, who);

  /* else cheat: look for objects of galaxy classes likely to 
   * contain icons -- doesn't deal with user-defined classes!*/
  else  {
    register const vname *tag;
    tag = vresourceGetTag(res, vname_Class);
    if (vcharCompare(tag, name_vpalette)==0        || /* cheating */
	vcharCompare(tag, name_vdialog)==0         ||
	vcharCompare(tag, name_vconfirm)==0        ||
	vcharCompare(tag, name_vcontainer)==0      ||
	vcharCompare(tag, name_vcontainergroup)==0 ||
	vcharCompare(tag, name_viconview)==0       ||
	vcharCompare(tag, name_vmainview)==0	   ||
	vcharCompare(tag, name_vnotebook)==0
	)
      scanRememberOther(scan, res, who);
    else
      dotype(scan, res, who);
  }
  return;
}

/********
 * dotype called to search a generic dictionary resource. just looks
 * at the base level for a dictionary with tag "Image" (since lots
 * of folks use vname_Image to tag images).
 *
 * -> scan, the scanner
 * -> res, the resource to snoop
 * -> who, [optional] name associated with the resource
 * <- void
 *********/
static void
dotype(scandata *scan, vresource res, const vname *who)
{
  const vname	*tag;
  vresource	 img;

  /* Check type, might store images at base level */
  if (vresourceTestGet(res, vname_Image, &img) &&
      vresourceType(img)==vresourceDICT)
    {
      /* See if the type has a more-specific name */
      if (vresourceTestGetTag(res, vname_Tag, &tag))
	who = tag;

      /* Process the possible image */
      dodict(scan, img, who);
    }
  return;
}

/********
 * dodict takes a dictionary resource and tries to determine
 * if it's a vimage, another galaxy vclass resource, or a user-defined
 * dictionary. if it's an image it's stashed away. if it's an object
 * resource it's passed to doclas. if it's a just a undefined 
 * dictionary and recursive option is ON, it's remembered for later 
 * processing.
 *
 * -> scan, the scanner
 * -> res, the dictionary resource we're snooping
 * -> who, [optional] name associated with resource
 * <- void
 *********/
static void
dodict(scandata *scan, vresource res, const vname *who)
{
  const vname *tag;

  /* Ignore if it's a complex class object other than image */
  if (vresourceTestGetTag(res, vname_Class, &tag)) {
    if (vcharCompare(tag, name_vimage)!=0)
      doclas(scan, res, who);
    else
      scanRememberImage(scan, res, who);
  }

  /* Ignore if it's a typed-dictionary other that vimage */
  else
  if (vresourceTestGetTag(res, vname_Type, &tag)) {
    if (vcharCompare(tag, name_vimage)!=0) {
      if (!scan->file->recursive || !scan->file->all)
	dotype(scan, res, who);
      else
	scanRememberOther(scan, res, who);
    }
    else
      scanRememberImage(scan, res, who);
  }

  /* Otherwise dictionary, so remember as possible source */
  else
  if (scan->file->recursive)
    scanRememberOther(scan, res, who);

  return;
}

/********
 * doarray takes an array resource and if it's not empty, creates
 * a new scan [thread] for it. used by nextaitem.
 *
 * -> scan, the scanner
 * -> res, the array resource we're snooping
 * <- void
 *********/
static void
doarray(scandata *scan, register vresource res)
{
  register tstack  *stk;
  register size_t  i,num;

  /* For an array of arrays (eek) start an independent scan */
  num= vresourceCountComponents(res);
  if (num>0) {
    stk= tstackCreate();
    for (i=0; i<num; i++) tstackPush(stk, vresourceGetAt(res, i));
    scanNew(scan->file, stk);
  }
  return;
}

/********
 * nextditem is called by scanner's event processing to 
 * handle next search in a dictionary resource.
 *
 * -> scan, the scanner
 * -> res, the dictionary resource we're snooping
 * -> who, [optional] name associated with resource
 * <- void
 *********/
static void
nextditem(scandata *scan, int *repost)
{
  vresource    ires;
  const vname *tag;

  if (scan->file->aborted) {
    *repost = vFALSE;
    return;
  }
  ires= vresourceGetNthComponent(scan->res, scan->next, &tag);
  if (vresourceType(ires)==vresourceDICT)
    dodict(scan, ires, tag);
  else
  if (scan->file->recursive && (vresourceType(ires)==vresourceARRAY)) {
    int atype= vresourceArrayType(ires);
    if (atype==vresourceDICT)
      scanRememberOther(scan, ires, tag);
    else
    if (atype==vresourceARRAY) /* possible? */
      doarray(scan, ires);
  }
  if ((*repost=(scan->next!=0)))
    scan->next--;
  return;
}

/********
 * nextaitem is called by scanner's event processing to 
 * handle next search in an array resource.
 *
 * -> scan, the scanner
 * -> res, the array resource we're snooping
 * -> who, [optional] name associated with resource
 * <- void
 *********/
static void
nextaitem(scandata *scan, int *repost)
{
  vresource ires;

  if (scan->file->aborted) {
    *repost = vFALSE;
    return;
  }
  ires= vresourceGetAt(scan->res, scan->next);
  if (vresourceType(ires)==vresourceDICT)
    dodict(scan, ires, NULL);
  else
  if (vresourceType(ires)==vresourceARRAY)
    scanRememberOther(scan, ires, NULL);

  if ((*repost=(scan->next!=0)))
    scan->next--;
  return;
}

/*
 *+------------------------------------------------------------------------+
 * private routines - files
 *+------------------------------------------------------------------------+
 */

/********
 * fileLookup checks if the given path (full) is already being
 * searched.
 *
 * -> path, the (full) path to look for
 * <- filedata, NULL if the file isn't being searched, otherwise
 *		it's data block ptr
 *********/
static filedata*
fileLookup(const vfsPath *path)
{
  filedata *file = NULL;
  if (files) {
    vdictIterator iterator;
    register vdictIterator *iter= &iterator;
    register vstr *s= vfsPathToStr(path);
    register filedata *next;
    vdictInitIterator(iter, files);
    while (vdictNextIterator(iter)) {
      next = (filedata*)vdictGetIteratorValue(iter);
      if (vcharCompare(next->filepath, s)==0) {
	file = next;
	break;
      }
    }
    vdictDestroyIterator(iter);
    vstrDestroy(s);
  }
  return file;
}

/********
 * fileFlushImages nukes the images found by a file search; frees
 * the actual vimage if the images have been preloaded (formed).
 *
 * -> file, the searched file
 * <- void
 *********/
static void
fileFlushImages(register filedata *file)
{
  register vimage *image;
  if (file->images) {
    if (file->preload)
      while (!tstackIsEmpty(file->images)) {
	image = tstackPopAs(file->images, vimage*);
	vimageDestroy(image);
      }
    tstackDestroy(file->images);
    file->images = NULL;
  }
  return;
}

/********
 * fileFlush is called after _all_ scans have completed
 * for a file. if there is an observer, it's called with the 
 * "isnfSEARCH_SUSPEND" message (st it can assume ownership
 * of any found images).
 *
 * -> file, the file
 * <- void
 *********/
static void
fileFlush(register filedata *file)
{
  if (!file->observer) fileFlushImages(file);
  else {
    int relinquish= vFALSE;
    file->observer(file->filepath, isnfSEARCH_SUSPEND, file->root, 
		   file->images, &relinquish);
    if (!relinquish) fileFlushImages(file);
    else file->images = NULL;
    if (!file->relinquished) file->relinquished = relinquish;
  }
  return;
}

/********
 * fileCreate creates/associates our filedata structure with
 * a file. structure used to track information while scanning
 * file. note this _opens_ the file for searching! if the file
 * is empty or is not a Galaxy resource file returns NULL.
 *
 * -> path, the (full) path to search
 * -> [t/f], TRUE if composite resources can be recursively searched
 * -> [t/f], TRUE if images should be preloaded and passed to the
 *           observer as a stack of vimages instead of a stack of 
 *           vresources
 * -> [t/f], TRUE if all composite resources should searched (nullifies
 *           the recursive option if TRUE)
 * -> procptr, observer - called when "interesting" events occur
 * <- file,  the new filedata refptr for the file or NULL if file
 *	     empty or is not Galaxy resource file
 *********/
static filedata*
fileCreate(const vfsPath *path, int recursive, int preload, int alltypes,
	   isnfSearchObserver obs)
{
  register filedata 	*file;
  filedata		*volatile filev;
  tstack		*volatile stk;
  size_t		 num;
  vbool			 volatile empty = vFALSE;

  if (!files) startup();

  file  = (filedata*)vmemAllocAndClear(sizeof(filedata));
  filev = file;
  vexWITH_HANDLING {
    /* If file empty don't bother going further */
    file->root = vresourceOpenFile(path, vfsOPEN_READ_ONLY);
    num = vresourceCountComponents(file->root);
    if (num<=0) {
      vresourceCloseFile(file->root);
      vmemFree(file);
      if (obs)
	obs(NULL,isnfSEARCH_EMPTY_FILE,path);
      empty = vTRUE;
    }
    /* setup for scan */
    else {
      file->filepath = vfsPathToStr(path);
      stk = tstackCreate();
      tstackPush(stk, file->root);
    }
  }
  vexON_EXCEPTION {
    if (filev->root!=vresourceNULL) vresourceCloseFile(filev->root);
    if (filev->filepath) vstrDestroy(filev->filepath);
    vmemFree((void*)filev);
    propagateCantOpenFileException();
  }
  vexEND_HANDLING;

  /* phffht */
  if (empty) 
    return NULL;
  file->recursive = recursive;
  file->preload = preload;
  file->observer = obs;
  file->all = alltypes;
  vdictStore(files, file->filepath, file);

  /* post scan */
  if (obs) 
    obs(file->filepath,isnfSEARCH_BEGIN, file->root);
  scanNew(file, stk);
  return file;
}

/********
 * fileDelete cleans up a filedata structure - called when the
 * file is finished being searched or the search has been aborted.
 * will not close file if the observer has assumed control of
 * the found images (the resfile must stay open for the resource
 * references to remain valid).
 *
 * -> file, the filedata
 * <- void
 *********/
static void
fileDelete(register filedata *file)
{
  vdebugIF((!file || !files), vexGenerate(vexGetArgNullClass(), vexMESSAGE,
           "fileDelete: NULL argument(s)!", vexERRNO, 0, vexNULL));

  vdictRemove(files, file->filepath);
  vstrDestroy(file->filepath);

  if (file->scans) {
    register scandata *scan;
    while (!tstackIsEmpty(file->scans)) {
      scan= tstackPopAs(file->scans, scandata*);
      scanDelete(scan);
    }
    tstackDestroy(file->scans);
  }

  if (!file->relinquished) {
    fileFlushImages(file);
    vresourceCloseFile(file->root);
  }
  else if (file->aborted && file->images)
    fileFlushImages(file);

  vmemFree(file);
  return;
}

/*
 *+------------------------------------------------------------------------+
 * private routines - module
 *+------------------------------------------------------------------------+
 */

/********
 * startup initializes module-level stuff
 *
 * -> void
 * <- void
 *********/
static void
startup(void)
{
  register const vname **name;
  register const char  **scan, **stop;

  files = vdictCreate(vnameHashString);
  scan  = literals, stop = scan+NAME_COUNT, name = names;
  for (; scan<stop; scan++, name++)
    *name = vnameInternGlobalLiteral(*scan);
  vclientRegisterGlobalShutdown(geticonsshutdown);
  return;
}

/********
 * geticonsshutdown cleans up any module-level stuff; deletes any
 * active files.
 *
 * -> void
 * <- void
 *********/
static void
geticonsshutdown(void)
{
  if (files) {
    vdictIterator iterator;
    register vdictIterator *iter= &iterator;
    register filedata *file;
    quitting = vTRUE;
    vdictInitIterator(iter, files);
    while (vdictNextIterator(iter)) {
      file = (filedata*)vdictGetIteratorValue(iter);
      vdebugWarn("undeleted file '%s'\n", file->filepath);
      file->aborted = vTRUE;
      fileDelete(file);
    }
    vdictDestroyIterator(iter);
    vdictDestroy(files);
  }
  return;
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

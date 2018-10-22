/* $Id: viewpriv.h,v 1.1 1994/08/19 00:05:16 simone Exp $ */
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
 *                                                                          *
 ****************************************************************************
 */

#ifndef viewprivINCLUDED
#define viewprivINCLUDED 1

#ifndef veventINCLUDED
#include veventHEADER
#endif

#ifndef vprintINCLUDED
#include vprintHEADER
#endif

/*
 *+------------------------------------------------------------------------+
 * private constants, types, variables
 *+------------------------------------------------------------------------+
 */

enum {
  viewerDisplay_Thumbnail,
  viewerDisplay_Original
};

typedef struct imageadder imageadder;
typedef struct viewer viewer;
struct viewer {
  vfsPath		*temp;	  /* the temp file we're saved to */
  vfsPath		*perm;	  /* the perm file we're saved to */
  imageadder		*adder;	  /* used to add images during snoop */
  vresource		 root;	  /* rut of the temp resource file */
  vresource		 store;	  /* store in temp resource file */
  vdialog		*dialog;  /* the viewer dialogue */
  vstr			*from;	  /* the full pathname of file snooped */
  unsigned 		 options; /* options file snooped with */
  vdomainviewDrawObjectProc draw; /* original iconview object drawProc */
  viconviewIcon		*icon;	  /* viewer's icon in requestor! */
  int			 last;    /* next unique id in store */
  vundoActionList	*actions; /* last undoable action */
  appCommandSpace	 aspace;  /* for updating state bindings */
  tarray		*clipsel; /* the viewer's internal clipboard */
  vstr			*undotitle; /* last dynamically created undo title */
  vpoint		 thumbsize; /* thumbnail's dimensions */
  vprint		*printer;  /* [temp] used to print items */
  unsigned	 	 dirty:1; /* true if the store's been changed */
  unsigned		 noselection:1; /* true if nothing selected */
  unsigned		 waiting:1; /* true if waiting for save-to chsr */
  unsigned		 save:1; /* true if the store should be saved */
  unsigned		 ignoresave:1; /* true if the save flag is ignored */
  unsigned 		 thumbnail:1; /* true if show thumbnails only */
  unsigned		 fullpath:1; /* true if show full path to sniff file */
  unsigned 		 printstyle:1; /* true if saved print style */
};
  /* Snooped images are displayed by "viewers." a viewer is basically an 
       iconview of all found images. Viewers are also the primary interface
       for testing the image manager - we create a temporary resource file
       containing an image store of all found images. The viewer lets 
       the user cut, copy, duplicate, paste, save, etc the images (thereby 
       changing the image store we created and testing the misc image manager
       routines). Additionally we get to test the "undoable" image manager
       operations. Later it would be nice to hook up the galaxy icon editor 
       to enable users to edit the images as well. */



struct imageadder {
  viewer	*view;		/* owner */
  tstack	*stk;		/* stack o' images to copy ala grab */ 
  vresource	 scanfile;	/* file images are being grabbed from */
  vfsPath	*filepath;	/* convenience, same as viewer->temp */
  vresource	 resfile;	/* dynamic, resfile root as we copy to it */
  vresource	 images;	/* dynamic, images of image-store */
  int		 last;          /* next unique id in store */
  int		 number;        /* number of images found so far */
  statusgraphic	*graphic;       /* graphic in the global progress dialog */
  unsigned  	 aborted:1;	/* TRUE if we should abort the additions */
  unsigned  	 waiting:1;	/* TRUE if we should wait; suspended grab */
};
  /* A viewer can start stashing found images at any point during a
       snoop search. Actually we expect a snooper to start feeding the
       viewer at either of two points: the user has suspended a snoop in
       progress, or the snooper has completed the search. If the user 
       suspends a snoop, the snooper passes any images it has found so far
       to the file's associated viewer (if it's the first time, a new
       viewer is created for the the file). Similarly when the snooper is
       finished searching it passes all remaining images to the viewer.In
       order to support this possible "overlapping" of operations, snooped
       images are added to viewers through "adders." Adders have a stack
       of images it adds to a temporary file in batches. Whenever the 
       snooper passes more images to the viewer, they are added to the 
       adder's stack. If the adder finishes adding all of its images and 
       the snooper hasn't completed its search, the adder waits for the
       snooper to finish. Adders open and close the temporary resource
       file as appropriate. Note: a viewer isn't attached to the global
       list until its adder has completely processed all images and the
       search is completed. */



typedef struct viewericon {
  vfsPath	*path;	/* path of item we originally snooped */
  const vname	*tag;	/* global icon we're currently displaying */
}viewericon;
  /* A viewer is represented in the global "requestor" dialog by an
       iconview icon (created after all images have been processed and
       added to the temporary resource file and remove when the viewer
       is closed). Each icon has in its data field a reference to a 
       viewericon structure. The "open-action" for these icons opens its 
       viewer dialog. */



extern imanager *iman;
  /* The image manager was designed/written with the assumption of one
       instance per vapplication. We declare the snooper's image manager
       within the viewer module since that's the only place it's used. */



typedef struct vieweritem {
  const vname	*tag;	/* the name used to retrieve image from store */
  vimage	*sniffed; /* the image as retrieved from store */
  const vname	*name;	/* the name displayed in iconview */
  vimage	*displayed; /* the image displayed in iconview */
  viconviewIcon	*icon;	/* the iconview icon */
  vpoint	 pos;	/* it's position */
  vimage	*thumbnail; /* only if sniffed image too big for thumbnail */
  const vname	*thumbnailname; /* delta'ed name to show it's a scale */
  tarray	*others; /* array of aliases (vieweritems) */
  unsigned int	 loaded:1; /* true if loaded for drawing */
  unsigned int	 munged:1; /* true if sniffed image shrunk to thumbnail */
  unsigned int	 editing:1; /* true if currently editing image */
  unsigned int	 pool:1; /* spam'n-cheez */
}vieweritem;
  /* This is the structure most of the undoable commands use to track viewer's
       iconview items. We have to keep track of the image's tag as well
       as its image reference to enable easy release/retrieve from the image 
       store. For operations that do a "removal" type operation, we remember 
       the item's position at the momemt it was removed so it can be 
       repositioned should the operation be undone. */


typedef struct viewerPrintJob {
  isnifferPrintPrefs	prefs;	/* prefs (margins,etc.) */
  unsigned short 	iw, ih;	/* item dims (based on prefs and thumbnail) */
  unsigned short 	across;	/* number of items across a page -> after */
  unsigned short 	down;	/* number of items down a page -> after */
  unsigned short 	numpages; /* number of pages in "full" job */
  vrectFloat		page;	/* DEFAULT page rect -> without border, etc. */
  vrectFloat		content; /* page rect to use for items */
  vrectFloat		extra;  /* page rect used for header or footer*/
  unsigned short	start, stop, at;
  viconviewIterator 	*iter;
}viewerPrintJob;
  /* Stuff for printing ... thank you very much! */



extern vfsPath *writableDirectory;
  /* Our temporary snoop files have to go someplace. By default we use
      the directory containing the executable. If this directory isn't
      writable, we have to ask the user to select a writable directory.
      In any case this contains the location we can save temp files to */



extern vfilechsr *saveChsr;
  /* User wants to save temporary snooped file to a permanent resource 
       file. This is the global save chooser variable for dis. */


/*
 *+------------------------------------------------------------------------+
 * shared macros and routines prototypes
 *+------------------------------------------------------------------------+
 */

#define viewerFileMASK   \
 (vfsOWNER_READ|vfsOWNER_WRITE|vfsGROUP_READ|vfsOTHER_READ)

#define viewerIsDirty(_view) ((_view)->dirty)
#define viewerIsOpen(_view) ((_view)->dialog && vdialogIsOpen((_view)->dialog))
#define viewerIsWaiting(_view) ((_view)->waiting)
#define viewerLastActionIsUndoable(_view) ((_view)->actions!=NULL)
#define viewerGetStateDict(_view) ((_view)->aspace.state)
#define viewerGetDialog(_view) ((_view)->dialog)
#define viewerGetWindow(_view) (vdialogGetWindow((_view)->dialog))
#define viewerShowThumbnail(_view) ((_view)->thumbnail)
#define viewerShowOriginal(_view) (!viewerShowThumbnail(_view))
#define viewerGetIconItem(_icon) ((vieweritem*)viconviewGetIconData(_icon))

void	   viewerTouch(viewer*,int);
void	   viewerLoadItem(viewer*, viconviewIcon*);
viconview *viewerGetIconview(viewer*);
viewer	  *viewerFromContext(vdict*);
void	   viewerSave(viewer*);
void	   viewerSaveTo(viewer*);
void	   viewerSaveToPermanentFile(viewer*);
void	   viewerMoveTempFileToPermanentFile(viewer*);
void	   viewerSwitchFileIcon(viewer*, const vname*);
void	   viewerSetTitle(viewer*);
void	   viewerInstallDelayHandler(veventHandlerProc, void*);
void	   viewerPrint(viewer*volatile,vprint*volatile,viewerPrintJob*volatile);
void	   viewerPrintPage(viewer*,vprint*,viewerPrintJob*);
void	   viewerConfirmPrintJob(viewer*);
void	   viewerConfirmPrintStyle(viewer*);
vbool	   viewerMatchOnlyImages(vdomain*,vdomainSelection, vdomainObject*);

vieweritem *vieweritemAlloc(void);
void vieweritemFree(vieweritem*);
void vieweritemDestroy(vieweritem*);
void vieweritemDetermineDisplayedImage(viewer*, vieweritem*, viconviewView*);
void vieweritemNukeThumbnail(vieweritem*);
void vieweritemAcceptChangedImage(viewer*, vieweritem*, vimage*);

void	viewerEditStartup(isnifferApp*);
void	viewerEditShutdown(void);
void	viewerEditHandleSelectIcon(viconview*,viconviewIcon*,vevent*,vbool);
void	viewerEditAttachCommands(viewer*);
void	viewerEditDestroy(viewer*);
void	viewerOpenImageEditor(viewer*, viconviewIcon*);
void	viewerCommitImageEditor(viewer*, vieweritem*);
void	viewerShutdownImageEditor(void);

void	viewerCommitUndoables(viewer*);
void	viewerUpdateUndoInterface(viewer*);
void	viewerUpdateDirtyDependentInterface(viewer*);

void	viewerFileStartup(isnifferApp*);
void	viewerFileAttachCommands(viewer*);
void	viewerFileShutdown(void);
vresource viewerNewTypedFile(vfsPath*,vfsMode);




/* viewprivINCLUDED */
#endif

/* $Id: isnf.h,v 1.1 1994/08/19 00:04:17 simone Exp $ */
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

#ifndef isnfINCLUDED
#define isnfINCLUDED 1

#ifndef vportINCLUDED
#include <vport.h>
#endif

#ifndef vdictINCLUDED
#include vdictHEADER
#endif

#ifndef vresourceINCLUDED
#include vresourceHEADER
#endif

#ifndef vcommandINCLUDED
#include vcommandHEADER
#endif

#ifndef vimageINCLUDED
#include vimageHEADER
#endif

#ifndef vfontINCLUDED
#include vfontHEADER
#endif

#ifndef vcursorINCLUDED
#include vcursorHEADER
#endif

#ifndef vdialogINCLUDED
#include vdialogHEADER
#endif

#ifndef vconfirmINCLUDED
#include vconfirmHEADER
#endif

#ifndef vnoticeINCLUDED
#include vnoticeHEADER
#endif

#ifndef vfilechsrINCLUDED
#include vfilechsrHEADER
#endif

#ifndef vapplicationINCLUDED
#include vapplicationHEADER
#endif

#ifndef vimageedtrINCLUDED
#include vimageedtrHEADER
#endif

#ifndef commandINCLUDED
#include "com.h"
#endif


/* */

enum {
  isnfIMAGE_BATCH_SIZE = 5,
  isnfMIN_THUMBSIZE    = 40,
  isnfMAX_THUMBSIZE    = 100,
  isnfH_ITEM_MARGIN    = 5,
  isnfV_ITEM_MARGIN    = 10,
  isnfH_PAGE_MARGIN    = 20,
  isnfV_PAGE_MARGIN    = 20
};

enum {
  strTitleFrom,
  strTitleNumberImagesSnooped,
  strTitlePutChsr,
  strTitleGetChsr,
  strTitleTempFilesPutChsr,
  strTitleLookStatusItem,
  strTitleFindStatusItem,
  strTitleImagesListing,
  strTitleImagesListingTooLong,
  strTitleGenericUndo,
  strTitlePasteAction,
  strTitlePasteAsAliasAction,
  strTitleDuplicateAction,
  strTitleDuplicateAsAliasAction,
  strTitleCutAction,
  strTitleClearAction,
  strTitleRemoveAllAction,
  strTitlePasteAsGroupAction,
  strTitleBoinkAction,
  strTitleGenericUndoTemplate,
  strTitleGenericRedoTemplate,
  strTitleAbbrViewerTemplate,
  strPageNoTemplate,
  strPageLabelTemplate,
  strSaveImageNoticeTitle,
  strImageEditorTitle
};

enum {
  msgCantSnoopMoreThanOneFile,
  msgCantSnoopFile,
  msgCantSnoopSelectedFile,
  msgSelectedFileIsEmpty,
  msgCantInitFileChooser,
  msgCantOpenFileChooser,
  msgTooManyResourceFilesOpen,
  msgCantViewSnoopFile,
  msgProblemSavingSnoopFileImages,
  msgSelectedFileHasNoIcons,
  msgSelectedFileAlreadySnooped,
  msgUnpackingSnoopedImagesToMemory,
  msgNeedWritableTempDirectory,
  msgSelectedDirectoryNotWritable,
  msgWantToPermanentlySaveChanges,
  msgCantOpenSaveToChooser,
  msgWantToReallyQuitWhenBusy,
  msgNeedToCompleteTheSaveInProgress,
  msgCantSaveFileWellPoop,
  msgCantSavePrintStyle,
  msgCantPrintJob,
  msgWantToSaveImageChanges,
  msgOpeningImageEditor,
  msgPrintingThumbnails,
  msgCantOpenMultipleImages,
  msgFeatureUnimplemented,
  msgInvalidThumbsize
};



typedef struct isnifferPrintPrefs {
  unsigned short ihm, ivm;	/* vert and horiz margins between items */
  unsigned short phm, pvm;	/* printer vertical and horiz margins */
  vfont		*font;		/* header font */
  short		 linewidth;
  unsigned int	 border:1;	/* want border */
  unsigned int	 header:1;	/* was extra info at top vs. bottom */
  unsigned int	 number:1;	/* want page numbers */
  unsigned int	 extra:1;
}isnifferPrintPrefs;

typedef struct isnifferPrefs {
  isnifferPrintPrefs 	pp;		/* printing preferences, see above */
  unsigned int 		all:1;		/* sniff all types of composite resources */
  unsigned int		recursive:1; 	/* sniff recusively -> all */
  unsigned int		thumbnails:1; 	/* thumbnails on by default */
  unsigned int		titles:1; 	/* full titles on by default */
  unsigned int		diff_thumbsize:1; /* user-specified thumbnail size */
  short			thumbsize;
  vconfirm		*conf; 		/* [transient] da window */
}isnifferPrefs;
  /* Storage for all viewer preferences (print, view, sniffage, etc.) */


typedef struct isnifferCursors {
  vresource		resource;	/* the array of cursor resources */
  vcursor		**cursors;	/* loaded cursors */
  unsigned short	count;		/* cached; the size of array */
  unsigned short	at;		/* current pos */
  unsigned short	level;		/* for nestability */
}isnifferCursors;


typedef struct isnifferApp {
  vapplication		*app;		/* galaxy application object */
  vresource		 resources;	/* handle to all app's resource file */
  vresource		 messages;	/* global message - used in info/messagebox */
  vresource		 strings;	/* global strings */
  vstr			*version;	/* displayable string for app's version */

  appCommandSpace	 cmdspace;	/* isniffer's global commands eg. quit */
  vdialog		*requestor;	/* the primary controls (vmainview) */
  vobject		*object;	/* convenience for switching command state */
  vdialogItem		*statusitem;	/* message box in primary window */
  vfsPath		*tempdir;	/* to place temp snooped files */

  vimage		*viewerIcon;	/* icons assoc. with viewers */
  vimageedtr		*imageEditor;	/* image editor for sniffed stuff */

  vnotice		*infoNotice;	/* global "info" notice - see appInformUser */
  vnotice		*quesNotice;	/* global "ask" notice - see appAskUser */
  vimage		*noticeIcon;	/* phffht: just to be weird */

  vdialog		*status;	/* global sniffing status dialog */
  vimage		*wholeimage;	/* images for "found image" graphic */
  vimage		*pieceimage;	/* ditto */

  isnifferCursors	 cursors;	/* i was bored */

  vbyte			 busy;		/* block level of application (limited user input) */
  unsigned int		 recursive:1;	/* user wants a recursive search */
  unsigned int		 all:1;		/* user wants to check all aggregate resources */
  unsigned int		 quitting:1;

}isnifferApp;


isnifferApp *isnfGet(void);
int isnfIsProcessingUserRequests(void);
const vchar *isnfGetVersionString(void);
appCommandSpace *isnfGetCommandSpaceDescription(void);
const isnifferPrefs *isnfGetPreferences(void);
void isnfStartupPreferences(isnifferApp*);
void isnfStartupPreferencesChooza(isnifferApp*);
void isnfShutdownPreferences(isnifferApp*);

void isnfStartupSpinDocktor(isnifferApp*);
void isnfShutdownSpinDocktor(isnifferApp*);
void isnfSpinDocktorWannaSpinPlease(void);
void isnfSpinDocktorSpinBabySpin(void);
void isnfSpinDocktorStopImTooDizzy(void);

extern isnifferApp gApp;
#define isnfGet() (&gApp)
#define isnfGetVersionString() ((const vchar*)gApp.version)
#define isnfGetCommandSpaceDescription() (&gApp.cmdspace)
#define isnfIsQuitting() (gApp.quitting)


/* isnfINCLUDED */
#endif

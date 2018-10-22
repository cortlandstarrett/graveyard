/* $Id: names.c,v 1.1 1994/08/19 00:06:37 simone Exp $ */
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
 *     This module defines the global names used by the isnoop application  *
 *                                                                          *
 * Modification History:                                                    *
 *     o 12-11-93: created for galaxy 2.0 (ssmc)                            *
 *                                                                          *
 * Text Editor Formatting:                                                  *
 *     Symantec: Tab(8), Font(Any Fixed Width)                              *
 *     Emacs: see end of file for info                                      *
 *                                                                          *
 ****************************************************************************
 */

#include <vport.h>
#include vstdioHEADER
#include vstdlibHEADER
#include vstdargHEADER
#include vmemHEADER
#include vdebugHEADER
#include vexHEADER
#include vcharHEADER
#include vstrHEADER
#include vnameHEADER

#include "names.h"


/* define our vdebug module tag */
#if (vdebugDEBUG && 0)
static const char *const _namesTag = "names";
#define vdebugTAG _namesTag
#endif

/*
 *+------------------------------------------------------------------------+
 * private constants, variables, etc.
 *+------------------------------------------------------------------------+
 */

const vname *appNames[appNAME_COUNT];
static const char *appLiterals[appNAME_COUNT]= {
  "title",
  "icon",
  "exit",
  "messages",
  "strings",
  "info-notice",
  "ques-notice",
  "notice-icon",
  "version",
  "print-style",

  "%1s",
  "%2s",
  "%3s",
  "%4s",

  "requestor",
  "snooped-files-label",
  "files",
  "cSnoop",
  "cSuspend",
  "cResume",
  "Quit",
  "cHelp",
  "cAdjustPrefs",
  "Open",
  "cRecursive",
  "cAllTypes",
  "status",

  "temp-file",
  "temp-file-opened",
  "perm-file",
  "perm-file-opened",

  "viewer",
  "viewer-icon",
  "glass",
  "icons",
  "cClothes",	/* clothes...get it?!...arf! arf! */
  "cHide",
  "cCleanup",
  "cToggleTitles",
  "cThumbnail",
  "cSave",
  "cSaveAs",
  "cRevert",
  "cPageSetup",
  "cPrint",
  "Undo",
  "Cut",
  "Copy",
  "Paste",
  "Clear",
  "Duplicate",
  "cPasteAlias",
  "cDuplicateAlias",
  "cRemoveAll",
  "cPasteDict",
  "cEditImage",
  "cBoinkImage",
  "cUsingOverview",

  "status",
  "status-box-look",
  "status-box-find",
  "null",
  "whole",
  "piece",

  "prefs",

  "help",
  "tempdir",
  "tempfolder",
  "verbose",
  "recursive",
  "allresources",
  "thumbnails",
  "fulltitles",
  "thumbsize",
  "thumbsize-actual",
  "header",
  "footer",
  "border",
  "pages",
  "errata"
};

/*
 *+------------------------------------------------------------------------+
 * exported routines
 *+------------------------------------------------------------------------+
 */

void
appInitNames(void)
{
  register const vname **name = appNames;
  register const char  **scan, **stop;

  scan = appLiterals, stop = scan+appNAME_COUNT;
  for (; scan<stop; scan++,name++)
    *name = vnameInternGlobalLiteral(*scan);
  return;
}




const char *
appNameLiteral(int token)
{
  return appLiterals[token];
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

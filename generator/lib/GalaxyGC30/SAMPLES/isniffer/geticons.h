/* $Id: geticons.h,v 1.1 1994/08/19 00:03:48 simone Exp $ */
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
 *  The grabicons module is the guts of the "sniffing" code. it actually    *
 *  opens the file and traverses the resource hierarchy looking for vimages.*
 *  it works through a generic "observer" to pass back any goodies it       *
 *  finds. it has no knowledge of the specific isniffer code, nor does      *
 *  it know about temporary image stores, viewers, etc. it can be used      *
 *  by any application to yank vimages out of a resource file. wrt to our   *
 *  isniffer application, this module is used by the snooper code to        *
 *  get the images from the file.                                           *
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

#ifndef grabiconsINCLUDED
#define grabiconsINCLUDED 1

#ifndef vportINCLUDED
#include <vport.h>
#endif

#ifndef vstrINCLUDED
#include vstrHEADER
#endif

#ifndef vfsINCLUDED
#include vfsHEADER
#endif


enum {
  isnfSEARCH_EMPTY_FILE, /* empty file, (who,vfsPath*) */
  isnfSEARCH_BEGIN,	 /* begin scanning, (who,vresource) */
  isnfSEARCH_END,	 /* end scanning, (who,vresource,stack*,int*) */
  isnfSEARCH_SUSPEND,	 /* suspended scanning, (who,vresource,stack*,int*) */
  isnfSEARCH_FOUND_IMAGE,/* found image, (who,const vname*) */
  isnfSEARCH_PUSH_RES,	 /* add resource(s) to scanlist, (who,int) */
  isnfSEARCH_POP_RES	 /* remove resource(s) from scanlist, (who,int) */
};
  /* Message identifiers passed to the observer at discreet points in the
       sniffage. The observer can use this identifier to determine the 
       rest of the message (a variable list is used for args). */


typedef void (*isnfSearchObserver)(const vchar*, int, ...);
  /* Declaration of the generic "observer" that is associated with a 
       particular sniffage. note this observer is NOT modeled after the
       generic galaxy observer mechanism. */


const vstr *isnfSearchFile(const vfsPath*, int, int, int, isnfSearchObserver);
  /* Open the file referenced by the given path, sniff about, yank any 
       vimages found and pass along to an "observer."  This routine isn't 
       guaranteed to find all images, although, it usually will if the "all" 
       and "recursive" options are enabled. Warning: this routine does
       NOT work sequentially - it batches vevents to do the actual file
       traversal. When the search is actually finished the observer is 
       called with a isnfSEARCH_END message! */

void isnfAbandonSearch(const vstr*);
  /* Abandon ship. Stop all searching for the given file. Does nothing if 
       the file isn't being sniffed. Pass NULL to stop sniffage an all 
       files. Will NOT pass isnfSEARCH_END to any observers. */

void isnfSuspendSearch(const vstr*, int);
  /* Suspends searches on one or more files. Pass NULL to suspend searches
       on all files. Calls observer(s) with isnfSEARCH_SUSPEND message,
       passing along any images found so far. */

void isnfResumeSearch(const vstr*);
  /* Resume searches on one or more files. Pass NULL to resume searches
       on all files. Observers should be written to deal with multiple
       suspends and resumes. */

void isnfAbandonAllSearches(void);
  /* Convenience routine. Abandon searches on all files. Same as calling
       isnfAbandonSearch(NULL) */

void isnfSuspendAllSearches(int);
  /* Convenience routine. Suspend searches on all files. Same as calling
       isfSuspendSearch(NULL,flush) */

void isnfResumeAllSearches(void);
  /* Convenience routine. Resume searches on all files. Same as calling
       isfResumeSearch(NULL) */


/*
 * Private macros, etc.
 */
#define isnfAbandonAllSearches()       isnfAbandonSearch(NULL)
#define isnfSuspendAllSearches(_flush) isnfSuspendSearch(NULL, (_flush))
#define isnfResumeAllSearches()        isnfResumeSearch(NULL)


/* grabiconsINCLUDED */
#endif

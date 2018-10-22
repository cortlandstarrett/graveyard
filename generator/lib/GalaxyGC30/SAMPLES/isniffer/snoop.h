/* $Id: snoop.h,v 1.1 1994/08/19 00:05:37 simone Exp $ */
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

#ifndef snoopINCLUDED
#define snoopINCLUDED 1

#ifndef isnfINCLUDED
#include "isnf.h"
#endif

/* The snooper module is responsible for searching resource files for
    galaxy images. once all the images have been retrieved from a 
    resource file, they are saved to a temporary resource file for viewing.
    if the user doesn't save this file to a permanent version it is 
    destroyed at shutdown. the images are saved as an imanager "image store"
    along with some other information describing from what file the images 
    were snooped. */


void isnfStartupSnooperManager(isnifferApp*);
  /* Initialize the snooper module and add any "univeral" snooper/viewer 
       commands to the applications command space. */


void isnfStopProcessingSnoopers(isnifferApp*);
  /* Stop processing any "snoops" in progress. this doesn't actually stop
       any pending snoop events (flushed when app calls veventStopProcessing).
       it does prevent any new events from getting posted. */


void isnfShutdownSnooperManager(isnifferApp*);
  /* Shutdown the snooper and viewer modules. should only be called at 
       quitting time. */


void isnfProcessStartupSnoopRequests(isnifferApp*);
  /* Processing any startup file arguments. the user can specify snoopable
       files on the command line (unix/dos/vms). For systems that don't
       support argv (to main()) this is essentially a no-op */


int isnfGetNumberSnoopersProcessing(void);
  /* Return the number of snoops in progress */

/* snoopINCLUDED */
#endif

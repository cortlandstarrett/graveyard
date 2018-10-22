/* $Id: view.h,v 1.1 1994/08/19 00:05:27 simone Exp $ */
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

#ifndef viewINCLUDED
#define viewINCLUDED 1

#ifndef vportINCLUDED
#include <vport.h>
#endif

#ifndef vcharINCLUDED
#include vcharHEADER
#endif

#ifndef vfsINCLUDED
#include vfsHEADER
#endif

#ifndef vresourceINCLUDED
#include vresourceHEADER
#endif

#ifndef tstackINCLUDED
#include "tstack.h"
#endif

#ifndef isnfINCLUDED
#include "isnf.h"
#endif

#ifndef statwinINCLUDED
#include "statwin.h"
#endif

/* Snooped images are displayed by "viewers." a viewer is basically an 
    iconview of all found images. Viewers are also the primary interface
    for testing the image manager - we create a temporary resource file
    containing an image store of all found images. The viewer lets 
    the user cut, copy, duplicate, paste, save, etc the images (thereby 
    changing the image store we created and testing the misc image manager
    routines). Additionally we get to test the "undoable" image manager
    operations. Later it would be nice to hook up the galaxy icon editor 
    to enable users to edit the images as well. */


enum {
  viewerSUCCESS =  0,
  viewerEMPTY   =  1,
  viewerERROR   = -1
};
  /* Returned by isnfGiveImagesToViewer. If a file contained no images a 
       viewer is NOT created for the file. Alternatively, if an error occurs
       trying to create a viewer viewerERROR is returned. */


void isnfStartupViewerManager(isnifferApp*);
  /* Initialize the viewer module and add any "univeral" viewer 
       commands to the applications command space. */


void isnfStopProcessingViewers(isnifferApp*);
  /* Stop processing any active image adders. this doesn't actually stop
       any pending add events (flushed when app calls veventStopProcessing).
       it does prevent any new events from getting posted and prevents the
       pending ones from doing anything. */


int isnfGetNumberViewersProcessing(void);
  /* Return the number of viewers in process of adding images and/or waiting 
       for snoopers to resume */


void isnfShutdownViewerManager(isnifferApp*);
  /* Shutdown the viewer modules. should only be called at quitting time
       since it destroys all viewers -- including viewer dialogs */


int isnfGetViewer(const vfsPath*);
  /* Check if the given file already has an associated viewer => it's being
       snooped or has already been snooped. */


int isnfGiveImagesToViewer(const vchar*,tstack*,vresource,statusgraphic*,int);
  /* Pass along a stack of images to the viewer mangler. If the file is
       new, a new viewer is created for it; otherwise the images are added
       to the viewer's list */


int isnfGotTemporaryStorageForViewers(void);
  /* Check if we've got a writable directory for our temporary image store
     files. */

/* viewINCLUDED */
#endif

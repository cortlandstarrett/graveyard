/******************************************************************************
*               (c) Copyright 1991,92,93 Visix Software, Inc.              
*                           All rights reserved.                           
* The following Sample Code is provided for your reference purposes in     
* connection with your use of the Galaxy Application Environment (TM)      
* software product which you have licensed from Visix Software, Inc.       
* ("Visix"). The Sample code is provided to you without any warranty of any
* kind and you agree to be responsible for the use and/or incorporation    
* of the Sample Code into any software product you develop. You agree to   
* fully and completely indemnify and hold Visix harmless from any and all  
* loss, claim, liability or damages with respect to your use of the Sample 
* Code.                                                                    
*                                                                          
* Subject to the foregoing, you are permitted to copy, modify, and         
* distribute the Sample Code for any purpose, and without fee, provided    
* that (i) a copyright notice in the in the form of "Copyright 1992 Visix  
* Software Inc., 11440 Commerce Park Drive, Reston, VA  22091. All Rights  
* Reserved" appears in all copies, (ii) both the copyright notice and this 
* permission notice appear in all supporting documentation and (iii) you   
* are a valid licensee of The Galaxy Application Environment.              
*                                                                          
******************************************************************************
*	$Id: linedom.c,v 1.5 1995/08/22 19:41:05 scotth Exp $
*
*       linedom.c
*
*       Main program for the linedom demo.  This program creates a
*       domain view that shows a series of connected lines and endpoints. 
*       The lines or points can then be dragged. The connected lines
*       will live update as the drag occurs to show where things are 
*       connected.
*
******************************************************************************/

/* Galaxy Includes */
#include <vgalaxy.h>

/* Application Includes */
#include "domain.h"

/*******************************************************************/
/*                  Private variables                              */
/*******************************************************************/

/*******************************************************************/
/*                  Private functions                              */
/*******************************************************************/

/*
 *  quitNotify
 *
 *  The button's notify procedure.  It's just to get us out
 *  of the program.
 *
 */


static void quitNotify (vbutton *button, vevent *event)

{

  veventStopProcessing ();

}

/*
 *  dialogCloseHook
 *
 *  Catch close and stop processing
 *
 */

static int dialogCloseHook (vdialog *dialog, vevent *event)

{

  veventStopProcessing ();
  return TRUE;

}

/*******************************************************************/
/*                  Public functions                               */
/*******************************************************************/

/*
 *  main
 *
 *  Set things up and get into the event loop.  We need to load
 *  our dialog, set up the domain and get into the event loop.
 *
 */

int main (int argc, char *argv[])

{

  vresource         resource;
  vresource         dialogResource;
  vdialog          *dialog;
  vdomainview      *domainview;
  vdomain          *domain;
  vbutton          *button;
  myDomainObject   *myObject;

  vstartup(argc,argv);

  resource = vapplicationGetResources (vapplicationGetCurrent ());

  /* get dialog */
  dialogResource = vresourceGet (resource,
				 vnameInternGlobalLiteral ("dialog"));
  dialog = vdialogLoad(dialogResource);

  /* set up dialog notify */
  vdialogSetCloseHook (dialog, dialogCloseHook);

  /* set up quit button */
  button = (vbutton *)
    vdialogFindItem (dialog, vnameInternGlobalLiteral ("quit"));
  vbuttonSetNotify (button, quitNotify);

  /* set up domain view */
  domainview = (vdomainview *)
    vdialogFindItem(dialog, vnameInternGlobalLiteral("domainview"));
  domainSetupView (domainview);
  domain = vdomainviewGetDomain (domainview);

  /* Set up some lines */
  myObject = domainAddPoint (domain, 10, 10);
  myObject = domainConnectLine (domain, myObject, 50, 50);
  myObject = domainConnectPoint (domain, myObject);
  myObject = domainConnectLine (domain, myObject, 75, 20);
  myObject = domainConnectPoint (domain, myObject);
  myObject = domainConnectLine (domain, myObject, 130, 65);
  myObject = domainConnectPoint (domain, myObject);

  /* open the dialog and start the event loop */
  vdialogOpen(dialog);
  veventProcess();

  /* bye bye */
  domainCleanupView (domainview);
  vdialogDestroy(dialog);

  exit (EXIT_SUCCESS);
  return EXIT_FAILURE;
}

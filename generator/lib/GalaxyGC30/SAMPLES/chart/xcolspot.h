/* $Id: xcolspot.h,v 1.2 1993/11/30 19:41:50 markd Exp $ */
/* The legal types make me put this in here.
 *
 * The following Sample Code is provided for your reference purposes in
 * connection with your use of the Galaxy Application Environment (TM) software
 * product which you have licensed from Visix Software, Inc. ("Visix").
 * The Sample code is provided to you without any warranty of any kind
 * whatsoever and you agree to be responsible for the use and/or incorporation
 * of the Sample Code into any software product you develop. You agree to fully
 * and completely indemnify and hold Visix harmless from any and all loss,
 * claim, liability or damages with respect to your use of the Sample Code.  
 *
 * Subject to the foregoing, you are permitted to copy, modify, and distribute
 * the Sample Code for any purpose and without fee, provided that (i) a
 * copyright notice in the form of "Copyright 1994 Visix Software Inc.,
 * 11440 Commerce Park Drive, Reston, VA  22091. All Rights Reserved" appears
 * in all copies, (ii) both the copyright notice and this permission notice
 * appear in supporting documentation and (iii) you are a valid licensee of
 * Galaxy Application Environment.
 *
 * Do not taunt Happy Fun Ball
 */

/* xcolspot.h -- Interface to a color spot / color editing dialog item
 *
 * Module: 
 *	xcolorspot
 *
 * Description
 *	See file chart.c for more comments about this whole project.
 *
 *	This module implements a dialog item of class "xcolorspot".  It
 *	draws a box with its background color filling up the item's rectangle
 *	and a border around the box of the dialog item's foreground color.
 *	Clicking on the box will bring up a color chooser.  Changing the
 *	color will then call the item's notify function.
 *
 *	All references to "spot" are homage to Leader Kibo's dog.
 *	HappyNet Uber Alles!
 *
 * Exported Functions:
 *	xcolorspotGetDefaultClass -- get the class used to make new colorspots
 *	xcolorspotSetNotify -- set the notify function for the color spot
 *
 * How to use:
 *	* go to vre and make a subclas of vdialogItem.  Call it xcolorspot
 *
 *	* start up the manager
 *	  (void)xcolorspotGetDefaultClass();
 *
 *	* write a notify to handle the color change
 *	  void myNotify (vdialogItem *spot, vevent *event)
 *	  {
 *	      event is to be ignored -- it's not a valid event.
 *	  } \* myNotify *\
 *
 *	* attach the notify
 *	  xcolorspotSetNotify (spot, myNotify);
 *
 *	* sit back and let xcolorspot do the work.
 */


#ifndef xcolspotINCLUDED
#define xcolspotINCLUDED 1

#ifndef  vportINLUDED
#include <vport.h>		/* for v*HEADER */
#endif

#ifndef  vdialogINLUDED
#include vdialogHEADER
#endif

/* exported interface */

vdialogItemClass *xcolorspotGetDefaultClass (void);
void xcolorspotSetNotify (vdialogItem *colorspot, vdialogItemNoteProc *notify);

/* functions defined as #define defines */

#define xcolorspotSetNotify(c,n)   vdialogSetItemNotify((c),(n))


#endif /* xcolorspotINCLUDED */


/*
 * Formatting information for emacs in c-mode
 *
 * Local Variables:
 * c-indent-level:4
 * c-continued-statement-offset:0
 * c-brace-offset:0
 * c-brace-imaginary-offset:0
 * c-argdecl-indent:0
 * c-label-offset:0
 * End:
 */

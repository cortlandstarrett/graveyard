/* $Id: xlist.h,v 1.2 1993/11/30 19:42:09 markd Exp $ */
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

/* xlist.h -- Interface to a dialog showing a list to allow users to
 *	      select a subrange.
 *
 * Module:
 *	xdemolist
 *
 * Description:
 *	See file chart.c for more comments about this whole project.
 *
 *	This module manages a vlist and a dialog containing a vlistview
 *	that contains a set of data.  The user can select a range of stuff
 *	in the dialog, click a button to define a subset of the list to
 *	be used by whomever wants to use it.
 *
 * Exported Functions:
 *	xdemolistSetNotify -- sets the notify function that will be called
 *			      when the list's subset changes
 *	xdemolistGetListDialog -- get the dialog the user can click in.  This
 *				  dialog is closed when first gotten, so you
 *				  can position where you want and open when 
 *				  you want.
 *	xdemolistGetList -- get the vlist that's underneath the dialog.
 *
 * How to use:
 *	* get the dialog and open it
 *	  vdialog *listDialog = xdemolistGetListDialog();
 *	  vdialogOpen (listDialog);
 *
 *      * write the notify function
 *	  void myListDemoNotify (int startIndex, int stopindex) {}
 *        The passed-in values are the beginning and ending indices
 *	  of the selected range, inclusive
 *
 *	* get the list so you can get data out of it
 *	  vlist *list = xdemolistGetList ();
 *	  ... = vlistGetCellValue (list, ...);
 */


#ifndef xlistINCLUDED
#define xlistINCLUDED 1

#ifndef  vportINCLUDED
#include <vport.h>		/* for v*HEADER */
#endif

#ifndef  vdialogINCLUDED
#include vdialogHEADER
#endif

#ifndef  vlistINCLUDED
#include vlistHEADER
#endif



typedef void (*xdemolistNoteProc) (int startIndex, int stopIndex);

void xdemolistSetNotify (xdemolistNoteProc notify);

vdialog *xdemolistGetListDialog (void);

vlist *xdemolistGetList (void);


#endif /* xlistINCLUDED */


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


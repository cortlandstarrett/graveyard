/* $Id: xattr.h,v 1.2 1993/11/30 19:41:33 markd Exp $ */
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

/* xattr.h -- Interface to an attribute notification system.
 *
 * Module:
 *	xattribute
 *
 * Description:
 *	See file chart.c for more comments about this whole project.
 *
 *	This module acts like a lightweight observer system.  There exist
 *	a set of "attributes" that could change at any time.  These attributes
 *	have a dialog (or set of dialogs) that can change the values.  Clients
 *	(the folks interested in the attribute values) register interest in
 *	a particular attribute.  When that attribute changes value, the
 *	client functions are called.
 *
 * Exported Functions:
 *	xattributeStartup -- get the attribute module set up for business
 *	xattributeGetAttributeDialog -- get the dialog that controls the
 *					attributes.  It's not open, so you
 *					can position and open it to wherever
 *					you want
 *	xattributeRegisterInterest -- tell the module that you're interested
 *				      in a particular attribute.
 *	xattributeRefreshEverybody -- iterate over all attributes and notify
 *				      all interested clients of the values.
 *				      usful for initial setup based on the 
 *				      attribute dialog.
 *
 * Exported Constants:
 *	xattr_blah_blah_blah -- a vname of "blah blah blah", identical for
 *				case, and _'s replaced by blanks.
 *				the type of the attribute is in a comment
 *				later on in this header.
 *
 * How to use:
 *	* startup the manager
 *	  xattributeStartup ();
 *
 *	* write code to handle the attribute notification
 *	  void myNoteProc (const void *data, const vname *attrName,
 *			   const void *value)
 *	  {
 *            data is something that is meaningful this code
 *	      attrName is the name of the attribute
 *	      value is some value, varies depending on the attribute
 *	  }
 *
 *	* register interest
 *	  xattributeRegisterInterest (xattr_Spam_Hog, someDataThat'sMeaningful,
 *				      myNoteProc);
 *
 *	* after you've registered everybody, update your attributes to match
 *	  those in the attr dialog
 *	  xattributeRefereshEverybody ();
 *
 *	* get the attribute dialog so you can open it and place it when/where
 *	  appropriate.
 *	  vdialog *dialog = xattributeGetAttributeDialog ();
 */


#ifndef xattrINCLUDED
#define xattrINCLUDED 1

#ifndef  vportINCLUDED
#include <vport.h>		/* for v*HEADER */
#endif

#ifndef  vdialogINCLUDED
#include vdialogHEADER
#endif

typedef void (*xattributeNoteProc) (const void *data,
				    const vname *attributeName,
				    const void  *value);

void xattributeStartup ();

vdialog *xattributeGetAttributeDialog (void);


void xattributeRegisterInterest (const vname *attributeName,
				 const void  *data,
				 xattributeNoteProc notify);

void xattributeRefreshEverybody (void);

extern const vname *xattr_Line_Width;	 /* (int *) */
extern const vname *xattr_Line_6_Color;  /* (vcolor *) */
extern const vname *xattr_Line_5_Color;  /* (vcolor *) */
extern const vname *xattr_Line_4_Color;  /* (vcolor *) */
extern const vname *xattr_Line_3_Color;  /* (vcolor *) */
extern const vname *xattr_Line_2_Color;  /* (vcolor *) */
extern const vname *xattr_Line_1_Color;  /* (vcolor *) */
extern const vname *xattr_Label_Color;   /* (vcolor *) */
extern const vname *xattr_Point_Color;   /* (vcolor *) */
extern const vname *xattr_Big_and_Scrolling;         /* vname_On / vname_Off */
extern const vname *xattr_Big_and_Scrolling_Scatter; /* vname_On / vname_Off */
extern const vname *xattr_Dashed_Lines;       /* vname_On / vname_Off */
extern const vname *xattr_Point_Images;       /* vname_On / vname_Off */
extern const vname *xattr_Custom_Point_Image; /* vname_On / vname_Off */

#endif /* xattrINCLUDED */


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

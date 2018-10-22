/* $Id: statitem.h,v 1.1 1994/08/19 00:03:28 simone Exp $ */
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
 *     This module implements the graphic/text status box item used by the  *
 *     isnoop application. it is _not_ a general purpose status item!       *
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

#ifndef statitemINCLUDED
#define statitemINCLUDED 1

#ifndef vportINCLUDED
#include <vport.h>
#endif

#ifndef vstrINCLUDED
#include vstrHEADER
#endif

#ifndef vresourceINCLUDED
#include vresourceHEADER
#endif

#ifndef vimageINCLUDED
#include vimageHEADER
#endif

#ifndef vdialogINCLUDED
#include vdialogHEADER
#endif



#define statusboxCLASS_NAME "statusbox"

enum{
  statusboxWHOLE_IMAGE,
  statusboxPIECE_IMAGE,
  statusboxBOTH_IMAGES
};


void statusboxStartupManager(
  vresource 		images_data
  );
  
const vdialogItemClass *statusboxGetDefaultClass(
  void
  );

void statusboxFlashMessageOwned(
  vdialogItem*		box,
  vstr*			message
  );

void statusboxTurnOnGraphicsMode(
  vdialogItem*		box
  );

void statusboxTurnOffGraphicsMode(
  vdialogItem*		box
  );

void statusboxUpdateImageCount(
  vdialogItem*		box,
  int           	delta
  );

void statusboxSetGraphicImages(
  vdialogItem*		box,
  vimage*       	whole,
  vimage*       	piece
  );

/* statitemINCLUDED */
#endif



/*
  +-------------------------------------------------------------------------+
   MISC formatting information for emacs in c-mode
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

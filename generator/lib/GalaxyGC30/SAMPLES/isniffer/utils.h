/* $Id: utils.h,v 1.2 1994/09/06 16:20:27 simone Exp $ */
/****************************************************************************
 *               (c) Copyright 1991,92,93 Visix Software, Inc.              *
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

#ifndef utilsINCLUDED
#define utilsINCLUDED 1

#ifndef vportINCLUDED
#include <vport.h>
#endif

#ifndef vdebugINCLUDED
#include vdebugHEADER
#endif

#ifndef vresourceINCLUDED
#include vresourceHEADER
#endif

#ifndef vnameINCLUDED
#include vnameHEADER
#endif

#ifndef vdialogINCLUDED
#include vdialogHEADER
#endif

#ifndef isnfINCLUDED
#include "isnf.h"
#endif

#ifndef statitemINCLUDED
#include "statitem.h"
#endif

enum {responseYES, responseNO, responseCANCEL};
typedef void (*askInvoker)(int,void*);

void 	isnfInitTheseNames(const char**, const vname**, unsigned int);
vstr   *isnfStrFrom(int);
vstr   *isnfReplaceMulti(const vchar*, ...);
void 	isnfInformUser(int, vdialog*);
void 	isnfInformUserByMessageBox(int);
void 	isnfInformUserByMessageBoxImmediately(int);
void 	isnfAskUser(int, int, askInvoker,void*,vdialog*);

void 	isnfBlock(vdialog*);
void 	isnfUnBlock(void);
int  	isnfIsBlocked(void);

int	isnfPrintConfirmationIsAvailable(void);
int	isnfStyleConfirmationIsAvailable(void);



/*
 * private macros, etc.
 */
#define isnfIsBlocked() (gApp.busy!=0)
#if vdebugDEBUG
void _isnfUnBlock(const char*, int);
#define isnfUnBlock() _isnfUnBlock(__FILE__, __LINE__)
#else
void _isnfUnBlock(void);
#define isnfUnBlock() _isnfUnBlock()
#endif

#define isnfInformUserByMessageBox(i) \
  statusboxFlashMessageOwned(gApp.statusitem, \
	   vresourceGetStringAt(gApp.messages,(i)))

#define isnfInformUserByMessageBoxImmediately(i) \
  isnfInformUserByMessageBox(i), \
        vdialogInvalItem(gApp.statusitem, vwindowINVAL_UPDATE)

#define isnfStrFrom(i) vresourceGetStringAt(gApp.strings, (i))
#define isnfMsgFrom(i) vresourceGetStringAt(gApp.messages, (i))


/* utilsINCLUDED */
#endif

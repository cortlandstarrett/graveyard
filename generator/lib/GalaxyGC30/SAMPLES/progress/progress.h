/* $Id: progress.h,v 1.3 1993/12/02 05:41:52 simone Exp $ */

/*---------------------------------------------------------------------------
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
 * copyright notice in the form of "Copyright 1992 Visix Software Inc.,
 * 11440 Commerce Park Drive, Reston, VA  22091. All Rights Reserved" appears
 * in all copies, (ii) both the copyright notice and this permission notice
 * appear in supporting documentation and (iii) you are a valid licensee of
 * Galaxy Application Environment.
 ----------------------------------------------------------------------------*/

/****************************************************************************
 *
 * Header File, progress.h
 *
 * See file main.c for a full comment about this sample code.
 *
 * History:
 * $Log: progress.h,v $
 * Revision 1.3  1993/12/02  05:41:52  simone
 * a. added some new macros for progress.c
 *
 * Revision 1.2  1993/11/11  23:20:55  chad
 * updated to use v*HEADER
 *
 * Revision 1.1  1993/07/21  13:49:56  chad
 * Initial revision
 *
 *
 ****************************************************************************/

#ifndef progressINCLUDED
#define progressINCLUDED 1

#ifndef  vportINCLUDED
#include <vport.h>		/* for v*HEADER */
#endif

#ifndef  vnameINCLUDED
#include vnameHEADER
#endif

#ifndef  vdialogINCLUDED
#include vdialogHEADER
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * * * * * * * * * CONSTANTS AND MACRO DEFINITIONS * * * * * * * * *
 */



/*
 * * * * * * * * * TYPE AND STRUCTURE DEFINITIONS * * * * * * * * * *
 */

typedef vdialog progress_t;

/*
 * * * * * * * * * PRIVATE EXTERNAL VARIABLES * * * * * * * * * * * *
 */



/*
 * * * * * * * * * FUNCTION PROTOTYPES * * * * * * * * * * * * * * * *
 */

progress_t	*progressCreate( void );
void		 progressDestroy( progress_t * );
void		 progressDestroyLater( progress_t * );
vdialog		*progressGetDialog( progress_t * );
void		 progressSet( progress_t *, double );
void		 progressSetData( progress_t *, const void * );
vdialogItem	*progressFindItem( progress_t *, const vname * );

/*
 * * * * * * * * * FUNCTIONS DEFINED AS #define MACROS * * * * * * * *
 */

#define progressDestroyLater(p)	\
    (vwindowDestroyLater(vdialogGetWindow(progressGetDialog(p))))
#define progressDestroy(p)      vdialogDestroy((vdialog*)(p))
#define progressGetDialog(p)	((vdialog*)(p))
#define _progressLoad(r)	((progress_t *)vdialogLoad((r)))
#define progressFindItem(p,t)	vdialogFindItem((vdialog*)(p), (t))
#define progressSetData(p,d)	vdialogSetData((vdialog*)(p), (d))

vportEND_CPLUSPLUS_EXTERN_C

#endif


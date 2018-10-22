/* $Id: xtxtview.h,v 1.1 1994/03/30 23:05:34 dimitri Exp $ */

/************************************************************

    xtxtview.h
    C Interface file for the xtxtview module

    (c) Copyright Visix Software Inc.
    All rights reserved

************************************************************/

#ifndef xtxtviewINCLUDED
#define xtxtviewINCLUDED 1

#ifndef  vportINCLUDED
#include <vport.h>		/* for v*HEADER */
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * globals modifiable through preferences
 */

extern vchar xtxtviewQuote;
extern vchar xtxtviewTonos;    
extern vchar xtxtviewDialytika;

void  xtxtviewStartup(void);

vportEND_CPLUSPLUS_EXTERN_C

#endif

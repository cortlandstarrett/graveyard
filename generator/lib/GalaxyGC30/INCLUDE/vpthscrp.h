/* $Id: vpthscrp.h,v 1.1 1994/10/10 21:09:06 gary Exp $ */

/****************************************************************
 *
 * vpthscrp.h
 *
 * C Interface file for vfsPath <=> vscrap conversion utilities
 *
 * Copyright (c) Visix Software, Incorporated
 * All Rights Reserved
 *
 ****************************************************************/

#ifndef vpathscrapINCLUDED
#define vpathscrapINCLUDED 1

#ifndef vportINCLUDED
#include <vport.h>
#endif

#ifndef vfsINCLUDED
#include vfsHEADER
#endif

#ifndef vscrapINCLUDED
#include vscrapHEADER
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C

/****************************************************************
 * Public function prototypes.
 ****************************************************************/

vscrap *vpathscrapGetPathScrap(vfsPath *path);

vfsPath *vpathscrapGetScrapPath(vscrap *scrap);

vportEND_CPLUSPLUS_EXTERN_C

#endif

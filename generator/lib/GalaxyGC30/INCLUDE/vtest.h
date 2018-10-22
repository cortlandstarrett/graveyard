/* $Id: vtest.h,v 1.8 1997/10/14 17:05:28 gary Exp $ */

/************************************************************

    vtest.h

    C Interface for raw events using the Testing Module Manager

    (c) Copyright Visix Software Inc.
    All rights reserved

************************************************************/

#ifndef vtestINCLUDED
#define vtestINCLUDED

#ifndef vdialogINCLUDED
#include <vdialog.h>
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * Structure used to register query pointer, object enumeration and
 * end object use procedures for a user-defined subclass of dialog item.
 */
#define vtestALL_OBJECTS	0
#define vtestDISPLAYED_OBJECTS	1

typedef struct
{
#if (vportCPLUSPLUS_SOURCE)
  vkind			*itemClass;
#else
  vdialogItemClass	*itemClass;
#endif /* vportCPLUSPLUS_SOURCE */

  vdialogItem		*(*queryProc)(vdialogItem *item, int x, int y);
  vdialogItem		**(*enumProc)(vdialogItem *item, int *count,
			    unsigned checkMask);
  void			(*endUseProc)(void);
} vtestComplexItemInfo;



#if (vportCPLUSPLUS_SOURCE)

/*
 * Routine to establish connection with testing program and initialize
 * internal state for testing.
 */
void vtestStartup(void);

/*
 * Function used to register the above structure
 */
void vtestRegisterComplexItemClass(vtestComplexItemInfo *infoPtr);

#else

void vtestStartup(void);
void vtestRegisterComplexItemClass(vtestComplexItemInfo *infoPtr);

#endif /* vportCPLUSPLUS_SOURCE */

vportEND_CPLUSPLUS_EXTERN_C

#endif







/* $Id: vhelpreflocator.h,v 1.6 1997/09/11 23:13:33 robert Exp $ */

/* -----------------------------------------------------------------------
 *
 *  vhelpreflocator.h
 *
 *  Programming interface to the root vhelpreflocator
 *
 *  (c) Copyright Visix Software
 *  All rights reserved
 *
 * -----------------------------------------------------------------------
 */

#ifndef vhelpreflocatorINCLUDED
#define vhelpreflocatorINCLUDED	1

#ifndef  vportINCLUDED
#include <vport.h>
#endif

#ifndef  vhelplocatorINCLUDED
#include vhelplocatorHEADER
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * * * * * * * * * * PUBLIC TYPE DEFINITIONS * * * * * * * * * *
 */

typedef 	vhelplocator			vhelpreflocator;
typedef		vhelplocatorClass		vhelpreflocatorClass;       

/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */

/*
 * Creation/Destruction/Class Management
 */

vhelpreflocatorClass *vhelpreflocatorGetDefaultClass(
    void
    );

vhelpreflocatorClass *vhelpreflocatorGetClass(
    vhelplocator	*helplocator
    );

vhelpreflocator *vhelpreflocatorCreateOfClass(
    vhelpreflocatorClass	*helpreflocatorClass
    );

vhelpreflocator *vhelpreflocatorCreate(
    void
    );

void vhelpreflocatorInitOfClass(
   vhelpreflocator		*helpreflocator,
   vhelpreflocatorClass		*clas
   );

void vhelpreflocatorInit(
   vhelpreflocator		*helpreflocator
   );

vhelpreflocator *vhelpreflocatorDestroy(
   vhelpreflocator		*helpreflocator
   );

vhelplocator *vhelpreflocatorGetLocator(
    vhelpreflocator		*helpreflocator
    );

/*
 * Class specific API.
 */

vbool vhelpreflocatorLocateHelp(
    vhelpreflocator	*helplocator,
    vhelprequest	*request
    );

/*
 * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * * *
 */

#define vhelpreflocatorCLASS	vhelplocatorCLASS

/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * * *
 */
#define vhelpreflocatorGetLocator(o)     ((vhelplocator *)(o))
#define vhelpreflocatorGetClass(l)				        \
    ((vhelpreflocatorClass*)						\
      vhelplocatorGetClass(vhelpreflocatorGetLocator(l)))
#define vhelpreflocatorCreateOfClass(c) 				\
    ((vhelpreflocator *)						\
      vhelplocatorCreateOfClass((vhelpreflocatorClass*)(c)))
#define vhelpreflocatorInitOfClass(o, c) 				\
      vhelplocatorInitOfClass(vhelpreflocatorGetLocator(o), 		\
       (vhelplocatorClass*)(c))
#define vhelpreflocatorInit(l)						\
      vprefreflocatorInitOfClass(l, vhelpreflocatorGetDefaultClass())
#define vhelpreflocatorCreate()						\
      vhelpreflocatorCreateOfClass(vhelpreflocatorGetDefaultClass())

#define vhelpreflocatorLocateHelp(l, r)					\
      vhelplocatorLocateHelp(vhelpreflocatorGetLocator(l), r)

/*
 * * * * * * * * * * PRIVATE FUNCTION MESSAGE DEFINITIONS * * * * * * * * * *
 */


vportEND_CPLUSPLUS_EXTERN_C

#endif /* vhelpreflocatorINCLUDED */

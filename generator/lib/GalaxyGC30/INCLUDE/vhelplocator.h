/* $Id: vhelplocator.h,v 1.5 1997/11/14 19:55:05 robert Exp $ */

/* -----------------------------------------------------------------------
 *
 *  vhelplocator.h
 *
 *  Programming interface to the root vhelplocator
 *
 *  (c) Copyright Visix Software
 *  All rights reserved
 *
 * -----------------------------------------------------------------------
 */

#ifndef vhelplocatorINCLUDED
#define vhelplocatorINCLUDED	1

#ifndef  vportINCLUDED
#include <vport.h>
#endif

#ifndef  vhelprequestINCLUDED
#include vhelprequestHEADER
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * * * * * * * * * * PUBLIC TYPE DEFINITIONS * * * * * * * * * *
 */

typedef struct	vhelplocator			vhelplocator;
typedef struct	vhelplocatorClass		vhelplocatorClass;       

/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */

/*
 * Creation/Destruction/Class Management
 */
vhelplocatorClass *vhelplocatorGetRootClass(void);

vhelplocatorClass *vhelplocatorGetClass(
    vhelplocator	*helplocator
    );

vhelplocator *vhelplocatorCreateOfClass(
    vhelplocatorClass	*helplocatorClass
    );

void vhelplocatorInitOfClass(
   vhelplocator		*helplocator,
   vhelplocatorClass	*clas
   );

vinstance *vhelplocatorGetInstance(
    vhelplocator	*helplocator
    );

/*
 * Class specific API.
 */

vbool vhelplocatorLocateHelp(
    vhelplocator	*helplocator,
    vhelprequest	*request
    );

void vhelplocatorReference(
    vhelplocator	*helplocator
);

void vhelplocatorUnreference(
    vhelplocator	*helplocator
);

/*
 * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * *
 */

struct vhelplocator {
    vinstance		instance;
    unsigned short	refCount;
};

#define vhelplocatorCLASS(SUPER, HELPLOC)			        \
    vinstanceCLASS(SUPER, HELPLOC);				        \
    vclassMETHOD_RET(vhelplocatorLOCATE_HELP, vbool,			\
		     (HELPLOC *helploc, vhelprequest *request))

struct vhelplocatorClass {
    vhelplocatorCLASS(vhelplocatorClass, vhelplocator);
};

/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * *
 */
#define vhelplocatorGetInstance(l)     vportBASE_OBJECT((l), instance)
#define vhelplocatorGetClass(l)						\
    ((vhelplocatorClass*)vinstanceGetClass(vhelplocatorGetInstance(l)))
#define vhelplocatorCreateOfClass(c) 					\
    ((vhelplocator *)vinstanceCreateOfClass((vinstanceClass*)(c)))
#define vhelplocatorInitOfClass(o, c) 					\
    vinstanceInitOfClass(vhelplocatorGetInstance(o), 			\
      (vobservableClass*)(c))

/*
 * * * * * * * * * * PRIVATE FUNCTION MESSAGE DEFINITIONS * * * * * * * * * *
 */
#define vhelplocatorLocateHelp(l, r)					\
    vclassSend(vhelplocatorGetClass(l), vhelplocatorLOCATE_HELP, (l, r))

vportEND_CPLUSPLUS_EXTERN_C

#endif /* vhelplocatorINCLUDED */

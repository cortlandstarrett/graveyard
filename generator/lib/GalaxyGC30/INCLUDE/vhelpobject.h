/* $Id: vhelpobject.h,v 1.6 1997/09/11 23:07:52 robert Exp $ */

/* -----------------------------------------------------------------------
 *
 *  vhelpobject.h
 *
 *  Programming interface to the root vhelpobject class
 *
 *  (c) Copyright Visix Software
 *  All rights reserved
 *
 * -----------------------------------------------------------------------
 */

#ifndef vhelpobjectINCLUDED
#define vhelpobjectINCLUDED	1

#ifndef vportINCLUDED
#include <vport.h>
#endif

#ifndef  vobjectINCLUDED
#include vobjectHEADER
#endif

#ifndef  vhelpdisplayINCLUDED
#include vhelpdisplayHEADER
#endif

#ifndef  vhelplocatorINCLUDED
#include vhelplocatorHEADER
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * * * * * * * * * * PUBLIC TYPE DEFINITIONS * * * * * * * * * *
 */

typedef struct	vhelpobject			vhelpobject;
typedef struct	vhelpobjectClass		vhelpobjectClass;       


/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */

/*
 * Creation/Destruction/Class Management
 */

vhelpobjectClass *vhelpobjectGetDefaultClass(
    void
    );

vhelpobjectClass *vhelpobjectGetClass(
    vhelpobject		*helpobject
    );

vhelpobject *vhelpobjectCreateOfClass(
    vhelpobjectClass	*helpobjectClass
    );

vhelpobject *vhelpobjectCreate(
    void
    );

void vhelpobjectInitOfClass(
   vhelpobject		*helpobject,
   vhelpobjectClass	*clas
   );

void vhelpobjectInit(
   vhelpobject		*helpobject
   );

vhelpobject *vhelpobjectDestroy(
   vhelpobject		*helpobject
   );

vinstance *vhelpobjectGetInstance(
    vhelpobject		*helpobject
    );

/*
 * Class specific API.
 */

vbool vhelpobjectDisplayHelp(
    vhelpobject		*helpobject,
    vhelprequest	*request
    );

void vhelpobjectUndisplayHelp(
    vhelpobject		*helpobject,
    vhelprequest	*request
    );

vhelplocator *vhelpobjectGetLocator(
    vhelpobject		*helpobject
    );

vhelpdisplay *vhelpobjectGetDisplay(
    vhelpobject		*helpobject
    );

void vhelpobjectSetLocator(
    vhelpobject		*helpobject,
    vhelplocator	*helplocator
    );

void vhelpobjectSetDisplay(
    vhelpobject		*helpobject,
    vhelpdisplay	*helpdisplay
    );

/*
 * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * *
 */

struct vhelpobject {
    vinstance     instance;
    vhelplocator *locator;
    vhelpdisplay *display;
};

#define vhelpobjectCLASS(SUPER, HELP_OBJ)			        \
    vinstanceCLASS(SUPER, HELP_OBJ);				        \
    vclassMETHOD(vhelpobjectSET_LOCATOR,		      		\
		 (HELP_OBJ *helpobj, vhelplocator *helploc));		\
    vclassMETHOD(vhelpobjectSET_DISPLAY,				\
		 (HELP_OBJ *helpobj, vhelpdisplay *helpdis));		\
    vclassMETHOD_RET(vhelpobjectDISPLAY_HELP, vbool,			\
		 (HELP_OBJ *helpobj, vhelprequest *request));		\
    vclassMETHOD(vhelpobjectUNDISPLAY_HELP,		      		\
		 (HELP_OBJ *helpobj, vhelprequest *request))

struct vhelpobjectClass {
    vhelpobjectCLASS(vhelpobjectClass, vhelpobject);
};

/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * *
 */
#define vhelpobjectGetInstance(o)	vportBASE_OBJECT(o, instance)
#define vhelpobjectGetClass(o)						\
    ((vhelpobjectClass*)vinstanceGetClass(vhelpobjectGetInstance(o)))
#define vhelpobjectCreateOfClass(c) 					\
    ((vhelpobject *)vinstanceCreateOfClass((vinstanceClass*)(c)))
#define vhelpobjectCreate() 						\
    vhelpobjectCreateOfClass(vhelpobjectGetDefaultClass())
#define vhelpobjectDestroy(o)						\
    vinstanceDestroy(vhelpobjectGetInstance(o))
#define vhelpobjectInitOfClass(o, c) 					\
    vinstanceInitOfClass(vhelpobjectGetInstance(o),		 	\
			 (vinstanceClass*)(c))
#define vhelpobjectInit(o)						\
    vhelpobjectInitOfClass(o, vhelpobjectGetDefaultClass())

#define vhelpobjectGetDisplay(o)	((o)->display)
#define vhelpobjectGetLocator(o)	((o)->locator)

/*
 * * * * * * * * * * PRIVATE FUNCTION MESSAGE DEFINITIONS * * * * * * * * * *
 */

#define vhelpobjectDisplayHelp(h, r)					\
    vclassSend(vhelpobjectGetClass(h), vhelpobjectDISPLAY_HELP, (h, r))
#define vhelpobjectUndisplayHelp(h, r)					\
    vclassSend(vhelpobjectGetClass(h), vhelpobjectUNDISPLAY_HELP, (h, r))
#define vhelpobjectSetDisplay(h, d)					\
    vclassSend(vhelpobjectGetClass(h), vhelpobjectSET_DISPLAY, (h, d))
#define vhelpobjectSetLocator(h, l)					\
    vclassSend(vhelpobjectGetClass(h), vhelpobjectSET_LOCATOR, (h, l))

vportEND_CPLUSPLUS_EXTERN_C

#endif /* vhelpobjectINCLUDED */








/* $Id: vhelpregistry.h,v 1.4 1997/09/11 23:07:52 robert Exp $ */

/* -----------------------------------------------------------------------
 *
 *  vhelpregistry.h
 *
 *  Programming interface to the root vhelpregistry class
 *
 *  (c) Copyright Visix Software
 *  All rights reserved
 *
 * -----------------------------------------------------------------------
 */

#ifndef vhelpregistryINCLUDED
#define vhelpregistryINCLUDED	1

#ifndef vportINCLUDED
#include <vport.h>
#endif

#ifndef  vobjectINCLUDED
#include vobjectHEADER
#endif

#ifndef  vhelpobjectINCLUDED
#include vhelpobjectHEADER
#endif


vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * * * * * * * * * * PUBLIC TYPE DEFINITIONS * * * * * * * * * *
 */

typedef struct	vhelpregistry			vhelpregistry;
typedef struct	vhelpregistryClass		vhelpregistryClass;       


/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */

/*
 * Creation/Destruction/Class Management
 */

void vhelpregistryStartup(
    void
    );

vhelpregistryClass *vhelpregistryGetDefaultClass(
    void
    );

vhelpregistryClass *vhelpregistryGetClass(
    vhelpregistry	*helpregistry
    );

vhelpregistry *vhelpregistryCreateOfClass(
    vhelpregistryClass	*helpregistryClass
    );

vhelpregistry *vhelpregistryCreate(
    void
    );

vhelpregistry *vhelpregistryInitOfClass(
   vhelpregistry	*helpregistry,
   vhelpregistryClass	*clas
   );

vhelpregistry *vhelpregistryInit(
   vhelpregistry	*helpregistry
   );

vhelpregistry *vhelpregistryDestroy(
   vhelpregistry	*helpregistry
   );

vinstance *vhelpregistryGetInstance(
    vhelpregistry	*helpregistry
    );

/*
 * Class specific API.
 */

vhelpobject *vhelpregistrySearchFromObject(
    vhelpregistry	*registry,
    vobject		*object,
    const vname		*name
    );

vhelpobject *vhelpregistrySearch(
    vhelpregistry	*registry,
    const vname		*name
    );
			      
void vhelpregistryRegisterHelpobject(
    vhelpregistry	*registry,
    vhelpobject		*object,
    const vname		*name
    );

/*
 * Utility calls.
 */
vhelpregistry *vhelpregistryGetGlobal(
    void
    );

void vhelpregistrySetGlobal(
    vhelpregistry	*registry
    );

/*
 * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * *
 */

struct vhelpregistry {
    vinstance     instance;
    vdict	 *dict;
};

#define vhelpregistryCLASS(SUPER, HELP_REG)			              \
    vinstanceCLASS(SUPER, HELP_REG);				              \
    vclassMETHOD_RET(vhelpregistrySEARCH_FROM_OBJECT, vhelpobject *,	      \
		 (HELP_REG *registry, vobject *object, const vname *name));   \
    vclassMETHOD_RET(vhelpregistrySEARCH, vhelpobject *,		      \
		 (HELP_REG *registry, const vname *name)); 		      \
    vclassMETHOD(vhelpregistryREGISTER_HELPOBJECT,			      \
		 (HELP_REG *registry, vhelpobject *object, const vname *name))

struct vhelpregistryClass {
    vhelpregistryCLASS(vhelpregistryClass, vhelpregistry);
};

/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * *
 */
#define vhelpregistryGetInstance(o)	vportBASE_OBJECT(o, instance)
#define vhelpregistryGetClass(o)					      \
    ((vhelpregistryClass*)vinstanceGetClass(vhelpregistryGetInstance(o)))
#define vhelpregistryCreateOfClass(c) 					      \
    ((vhelpregistry *)vinstanceCreateOfClass((vinstanceClass*)(c)))
#define vhelpregistryCreate() 						      \
    vhelpregistryCreateOfClass(vhelpregistryGetDefaultClass())
#define vhelpregistryDestroy(o)						      \
    vinstanceDestroy(vhelpregistryGetInstance(o))
#define vhelpregistryInitOfClass(o, c) 				       	      \
    vinstanceInitOfClass(vhelpregistryGetInstance(o), (vinstanceClass*)(c))
#define vhelpregistryInit(o)						      \
    vhelpregistryInitOfClass(o, vhelpregistryGetDefaultClass())

/*
 * * * * * * * * * * PRIVATE FUNCTION MESSAGE DEFINITIONS * * * * * * * * * *
 */

#define vhelpregistrySearchFromObject(r, o, n)				      \
    vclassSend(vhelpregistryGetClass(r), 				      \
	       vhelpregistrySEARCH_FROM_OBJECT, (r, o, n))
#define vhelpregistrySearch(r, n)					      \
    vclassSend(vhelpregistryGetClass(r), 				      \
	       vhelpregistrySEARCH, (r, n))
#define vhelpregistryRegisterHelpobject(r, o, n)			      \
    vclassSend(vhelpregistryGetClass(r), 				      \
	       vhelpregistryREGISTER_HELPOBJECT, (r, o, n))

vportEND_CPLUSPLUS_EXTERN_C

#endif /* vhelpregistryINCLUDED */








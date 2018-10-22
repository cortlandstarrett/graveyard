/* $Id: vobserver.h,v 1.4 1997/04/21 16:58:24 robert Exp $ */

/************************************************************

    vobserver.h

    C Interface file for the object observers

    (c) Copyright Visix Software Inc.
    All rights reserved

************************************************************/

#ifndef vobserverINCLUDED
#define vobserverINCLUDED

#ifndef  vportINCLUDED
#include <vport.h>
#endif

#ifndef  vstdioINCLUDED
#include vstdioHEADER
#endif

#ifndef  vdebugINCLUDED
#include vdebugHEADER
#endif

#ifndef  vexINCLUDED
#include vexHEADER
#endif

#ifndef  vmemINCLUDED
#include vmemHEADER
#endif

#ifndef  vnameINCLUDED
#include vnameHEADER
#endif

#ifndef  vdictINCLUDED
#include vdictHEADER
#endif

#ifndef  veventINCLUDED
#include veventHEADER
#endif

#ifndef  vresourceINCLUDED
#include vresourceHEADER
#endif

#ifndef  vclassINCLUDED
#include vclassHEADER
#endif

#ifndef  vobservableINCLUDED
#include vobservableHEADER
#endif


vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * * * * * * * * * * PUBLIC CONSTANT DEFINITIONS  * * * * * * * * * *
 */

/*
 * * * * * * * * * * PUBLIC TYPE DEFINITIONS * * * * * * * * * *
 */

typedef struct vobserver		vobserver;
typedef struct vobserverClass		vobserverClass;

/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */

void vobserverStartup(void);


/*
 * observers
 */

vobserverClass *vobserverGetDefaultClass(
    void
    );

vobservable *vobserverGetObservable(
    vobserver                      *observer
    );

vloadable *vobserverGetLoadable(
    vobserver                      *observer
    );

vinstance *vobserverGetInstance(
    vobserver                      *observer
    );

vobserverClass *vobserverGetClass(
    vobserver                      *observer
    );

vobserver *vobserverCreateOfClass(
    vobserverClass                 *clas
    );

void vobserverInitOfClass(
    vobserver                      *observer,
    vobserverClass                 *clas
    );

vobserver *vobserverClone(
    vobserver                      *observer
    );

void vobserverCopy(
    vobserver                      *observer,
    vobserver                      *target
    );

void vobserverCopyInit(
    vobserver                      *observer,
    vobserver                      *target
    );

vobserver *vobserverLoad(
    vresource                       resource
    );

void vobserverLoadInit(
    vobserver                      *observer,
    vresource                       resource
    );

void vobserverStore(
    vobserver                      *observer,
    vresource                       resource
    );

const vname *vobserverGetTag(
    vobserver                      *observer
    );

void vobserverSetTag(
    vobserver                      *observer,
    const vname                    *tag
    );

void vobserverDestroy(
    vobserver                      *observer
    );

void vobserverEnable(
    vobserver			   *observer
    );

void vobserverDisable(
    vobserver			   *observer
    );

vbool vobserverIsEnabled(
    vobserver			   *observer
    );

void vobserverSetData(
    vobserver                      *observer,
    const void			   *data
    );

const void *vobserverGetData(
    vobserver                      *observer
    );

void vobserverSetPatron(
    vobserver                      *observer,
    vinstance			   *patron
    );

vinstance *vobserverGetPatron(
    vobserver                      *observer
    );

void vobserverSetDesiredOccurrenceClass(
    vobserver                      *observer,
    const voccurrenceClass         *occurClass
    );

const voccurrenceClass *vobserverGetDesiredOccurrenceClass(
    vobserver                      *observer
    );

/*
 * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * *
 */

enum {
    _vobserverDISABLED		= 0x01
};

struct vobserver {
    vobservable			 object;

    unsigned short		 flags;
    vinstance			*patron;
    const voccurrenceClass	*occurClass;
    const void			*data;
};

#define vobserverCLASS(SUPER, OBSERVER)                                       \
    vobservableCLASS(SUPER, OBSERVER);                                        \
    vclassVARIABLE(vobserverDESIRED_OCCURRENCE_CLASS,			      \
		   const voccurrenceClass *);				      \
    vclassMETHOD(vobserverSET_DESIRED_OCCURRENCE_CLASS,			      \
		 (OBSERVER *observer,					      \
		  const voccurrenceClass *occurClass));			      \
    vclassMETHOD(vobserverENABLE, (OBSERVER *observer));		      \
    vclassMETHOD(vobserverDISABLE, (OBSERVER *observer));		      \
    vclassMETHOD(vobserverSET_PATRON,					      \
		 (OBSERVER *observer, vinstance *patron));		      \
    vclassMETHOD(vobserverSET_DATA,					      \
		 (OBSERVER *observer, const void *data))

struct vobserverClass {
    vobserverCLASS(vobserverClass, vobserver);
};


/*
 * * * * * * * * * * PRIVATE VARIABLE DECLARATIONS * * * * * * * * * *
 */

/*
 * * * * * * * * * * PRIVATE FUNCTION PROTOTYPES * * * * * * * * * *
 */

/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * *
 */

/*
 * observers
 */

#define vobserverGetObservable(o) \
	vportBASE_OBJECT(o, object)
#define vobserverGetLoadable(o) \
	vobservableGetLoadable(vobserverGetObservable(o))
#define vobserverGetInstance(o) \
	vloadableGetInstance(vobserverGetLoadable(o))
#define vobserverGetClass(o) \
	((vobserverClass *) vloadableGetClass(vobserverGetLoadable(o)))

#define vobserverCreateOfClass(c) \
	((vobserver *) vloadableCreateOfClass((vloadableClass *)(c)))
#define vobserverInitOfClass(o,c) \
	vloadableInitOfClass(vobserverGetLoadable(o), (vloadableClass *)(c))
#define vobserverDestroy(o) \
	vloadableDestroy(vobserverGetLoadable(o))

#define vobserverCopy(o,t) \
	vloadableCopy(vobserverGetLoadable(o), vobserverGetLoadable(t))

#define vobserverClone(o) \
    	((vobserver *) \
	 vloadableCloneOfSubclass(vobserverGetLoadable(o), \
			  (vloadableClass*) vobserverGetDefaultClass()))
#define vobserverCopyInit(o,t) \
    	vloadableCopyInitOfSubclass(vobserverGetLoadable(o), \
			    vobserverGetLoadable(t), \
			    (vloadableClass*) vobserverGetDefaultClass())

#define vobserverLoad(r) \
    	((vobserver *) vloadableLoadOfSubclass(r, \
				 (vloadableClass*) vobserverGetDefaultClass()))
#define vobserverLoadInit(o,r) \
    	vloadableLoadInitOfSubclass(vobserverGetLoadable(o), (r), \
			    (vloadableClass*) vobserverGetDefaultClass())
#define vobserverStore(o,r) \
	vloadableStore(vobserverGetLoadable(o), (r))

#define vobserverGetTag(o) \
	vloadableGetTag(vobserverGetLoadable(o))
#define vobserverSetTag(o, t) \
	vloadableSetTag(vobserverGetLoadable(o), t)

#define vobserverIsEnabled(o) \
	(((o)->flags & _vobserverDISABLED) == 0)

#define vobserverGetData(o) \
	((o)->data)
#define vobserverGetPatron(o) \
	((o)->patron)
#define vobserverGetDesiredOccurrenceClass(o) \
	((o)->occurClass)


/*
 * * * * * * * * * * PRIVATE FUNCTION MESSAGE DEFINITIONS * * * * * * * * * *
 */

/*
 * observers
 */

#define vobserverEnable(o) \
    vclassSend(vobserverGetClass(o), vobserverENABLE, (o))
#define vobserverDisable(o) \
    vclassSend(vobserverGetClass(o), vobserverDISABLE, (o))
#define vobserverSetData(o, d) \
    vclassSend(vobserverGetClass(o), vobserverSET_DATA, (o, d))
#define vobserverSetPatron(o, p) \
    vclassSend(vobserverGetClass(o), vobserverSET_PATRON, (o, p))
#define vobserverSetDesiredOccurrenceClass(o, c) \
    vclassSend(vobserverGetClass(o), vobserverSET_DESIRED_OCCURRENCE_CLASS, \
	       (o, c))


vportEND_CPLUSPLUS_EXTERN_C


#ifdef  vportNULL_HEADER
#ifdef  vobserverHEADER
#undef  vobserverHEADER
#endif
#define vobserverHEADER vportNULL_HEADER
#endif


#endif /* #ifndef vobserverINCLUDED */


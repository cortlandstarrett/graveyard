/* $Id: vmapping.h,v 1.7 1997/06/19 21:30:21 robert Exp $ */

/************************************************************

    vmapping.h

    C Interface file for the Class Manager loadable objects

    (c) Copyright Visix Software Inc.
    All rights reserved

************************************************************/

#ifndef vmappingINCLUDED
#define vmappingINCLUDED

#ifndef	 vportINCLUDED
#include <vport.h>
#endif

#ifndef	 vstdioINCLUDED
#include vstdioHEADER
#endif

#ifndef	 vdebugINCLUDED
#include vdebugHEADER
#endif

#ifndef	 vexINCLUDED
#include vexHEADER
#endif

#ifndef	 vmemINCLUDED
#include vmemHEADER
#endif

#ifndef	 vnameINCLUDED
#include vnameHEADER
#endif

#ifndef	 vresourceINCLUDED
#include vresourceHEADER
#endif

#ifndef	 vclassINCLUDED
#include vclassHEADER
#endif

#ifndef	 vobservableINCLUDED
#include vobservableHEADER
#endif


vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * * * * * * * * * * PUBLIC CONSTANT DEFINITIONS  * * * * * * * * * *
 */

/*
 * * * * * * * * * * PUBLIC TYPE DEFINITIONS * * * * * * * * * *
 */

typedef struct vmappingAnyKey		vmappingAnyKey;
typedef struct vmappingAnyKeyClass	vmappingAnyKeyClass;

typedef struct vmapping			vmapping;
typedef struct vmappingClass		vmappingClass;

typedef vmapping			vmappingLoadable;

typedef unsigned long (*vmappingHashFunc)(
    const void                     *p
    );

/*
 * iterators
 */

typedef struct vmappingAnyKeyIterator	vmappingAnyKeyIterator;
typedef vmappingAnyKeyIterator		vmappingIterator;

/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */

void vmappingStartup(void);


/*
 * mappings with vname keys
 */

vmappingClass *vmappingGetDefaultClass(
    void
    );

vmappingClass *vmappingGetDefaultLoadableClass(
    void
    );

vmappingAnyKey *vmappingGetAnyKey(
    vmapping			*mapping
    );

vinstance *vmappingGetInstance(
    vmapping			*mapping
    );

vloadable *vmappingGetLoadable(
    vmapping			*mapping
    );

vobservable *vmappingGetObservable(
    vmapping			*mapping
    );

vmappingClass *vmappingGetClass(
    vmapping			*mapping
    );

vmapping *vmappingCreateOfClass(
    vmappingClass		*clas
    );

vmapping *vmappingCreate(
    void
    );

vmapping *vmappingCreateLoadable(
    void
    );

void vmappingInitOfClass(
    vmapping			*mapping, 
    vmappingClass		*clas
    );

void vmappingInit(
    vmapping			*mapping
    );

void vmappingInitLoadable(
    vmapping			*mapping
    );

void vmappingDestroy(
    vmapping			*mapping
    );

vmapping *vmappingClone(
    vmapping			*mapping
    );

void vmappingCopy(
    vmapping			*source,
    vmapping			*target
    );

void vmappingCopyInit(
    vmapping			*source,
    vmapping			*target
    );

vmapping *vmappingLoad(
    vresource			 resource
    );

void vmappingLoadInit(
    vmapping			*mapping,
    vresource			 resource
    );

void vmappingStore(
    vmapping			*mapping,
    vresource			 resource
    );

vinstance *vmappingAddElementShared(
    vmapping			*mapping,
    const vname			*key,
    vinstance			*element
    );

vinstance *vmappingAddElementOwned(
    vmapping			*mapping,
    const vname			*key,
    vinstance			*element
    );

vinstance *vmappingRemoveElement(
    vmapping			*mapping,
    const vname			*key
    );

vinstance *vmappingGetElement(
    vmapping			*mapping,
    const vname			*key
    );

vinstance *vmappingTestGetElement(
    vmapping			*mapping,
    const vname			*key
    );

vbool vmappingIsElementOwned(
    vmapping			*mapping,
    const vname			*key
    );

void vmappingSetElementOwned(
    vmapping			*mapping,
    const vname			*key,
    int				 owned
    );

/*
 * mappings with any keys
 */

vmappingAnyKeyClass *vmappingGetDefaultAnyKeyClass(
    void
    );

vinstance *vmappingGetAnyKeyInstance(
    vmappingAnyKey		*mapping
    );

vloadable *vmappingGetAnyKeyLoadable(
    vmappingAnyKey		*mapping
    );

vobservable *vmappingGetAnyKeyObservable(
    vmappingAnyKey		*mapping
    );

vmappingAnyKeyClass *vmappingGetAnyKeyClass(
    vmappingAnyKey		*mapping
    );

vmappingAnyKey *vmappingCreateAnyKeyOfClass(
    vmappingAnyKeyClass		*clas
    );

vmappingAnyKey *vmappingCreateAnyKey(
    void
    );

void vmappingInitAnyKeyOfClass(
    vmappingAnyKey		*mapping, 
    vmappingAnyKeyClass		*clas
    );

void vmappingInitAnyKey(
    vmappingAnyKey		*mapping
    );

void vmappingDestroyAnyKey(
    vmappingAnyKey		*mapping
    );

vmappingAnyKey *vmappingCloneAnyKey(
    vmappingAnyKey		*mapping
    );

void vmappingCopyAnyKey(
    vmappingAnyKey		*source,
    vmappingAnyKey		*target
    );

void vmappingCopyInitAnyKey(
    vmappingAnyKey		*source,
    vmappingAnyKey		*target
    );

vinstance *vmappingAddAnyKeyElementShared(
    vmappingAnyKey		*mapping,
    const void			*key,
    vinstance			*element
    );

vinstance *vmappingAddAnyKeyElementOwned(
    vmappingAnyKey		*mapping,
    const void			*key,
    vinstance			*element
    );

vinstance *vmappingRemoveAnyKeyElement(
    vmappingAnyKey		*mapping,
    const void			*key
    );

vinstance *vmappingGetAnyKeyElement(
    vmappingAnyKey		*mapping,
    const void			*key
    );

vinstance *vmappingTestGetAnyKeyElement(
    vmappingAnyKey		*mapping,
    const void			*key
    );

vbool vmappingIsAnyKeyElementOwned(
    vmappingAnyKey		*mapping,
    const void			*key
    );

void vmappingSetAnyKeyElementOwned(
    vmappingAnyKey		*mapping,
    const void			*key,
    int				 owned
    );

/*
 * vname key iterator
 */

void vmappingInitIterator(
    vmappingIterator		*iterator,
    vmapping			*mapping
    );

int vmappingNextIterator(
    vmappingIterator		*iterator
    );

void vmappingDestroyIterator(
    vmappingIterator		*iterator
    );

const vname *vmappingGetIteratorKey(
    vmappingIterator		*iterator
    );

vinstance *vmappingGetIteratorElement(
    vmappingIterator		*iterator
    );

/*
 * any key iterator
 */

void vmappingInitAnyKeyIterator(
    vmappingAnyKeyIterator	*iterator,
    vmappingAnyKey		*mapping
    );

int vmappingNextAnyKeyIterator(
    vmappingAnyKeyIterator	*iterator
    );

void vmappingDestroyAnyKeyIterator(
    vmappingAnyKeyIterator	*iterator
    );

const void *vmappingGetAnyKeyIteratorKey(
    vmappingAnyKeyIterator	*iterator
    );

vinstance *vmappingGetAnyKeyIteratorElement(
    vmappingAnyKeyIterator	*iterator
    );

/*
 * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * *
 */

enum {
    _vmappingNO_ELEMENTS_OWNED		= 0x00,
    _vmappingSOME_ELEMENTS_OWNED	= 0x01,
    _vmappingALL_ELEMENTS_OWNED		= 0x02,
    _vmappingOWNED_UNDETERMINED		= 0x04
};


/*
 * any key mappings
 */

struct vmappingAnyKey {
    vobservable			 object;
    unsigned short		 flags;
    vdict			*elements;
    vdict			*ownedElements;
};

#define vmappingANY_KEY_CLASS(SUPER, MAPPING)				      \
    vobservableCLASS(SUPER, MAPPING);					      \
    vclassVARIABLE(vmappingHASH_FUNC, vmappingHashFunc);		      \
    vclassVARIABLE(vmappingELEMENT_CLASS, const vinstanceClass *);	      \
    vclassMETHOD_RET(vmappingADD_ELEMENT, vinstance *,			      \
		 (MAPPING *mapping, const void *key, vinstance *element));   \
    vclassMETHOD_RET(vmappingREMOVE_ELEMENT, vinstance *,		      \
		 (MAPPING *mapping, const void *key));			      \
    vclassMETHOD(vmappingSET_ELEMENT_OWNED,				      \
		 (MAPPING *mapping, const void *key, int owned))

struct vmappingAnyKeyClass {
    vmappingANY_KEY_CLASS(vmappingAnyKeyClass, vmappingAnyKey);
};

/*
 * vname key mappings
 */

struct vmapping {
    vmappingAnyKey		 super;
};

#define vmappingCLASS(SUPER, MAPPING) \
    vmappingANY_KEY_CLASS(SUPER, MAPPING)

struct vmappingClass {
    vmappingCLASS(vmappingClass, vmapping);
};

vportALIAS(vmappingLoadable, vmapping)

/*
 * iterator
 */

struct vmappingAnyKeyIterator {
    vdictIterator		 dictIterator;
};

vportALIAS(vmappingIterator, vmappingAnyKeyIterator)

/*
 * * * * * * * * * * PRIVATE VARIABLE DECLARATIONS * * * * * * * * * *
 */

/*
 * * * * * * * * * * PRIVATE FUNCTION PROTOTYPES * * * * * * * * * *
 */

vinstance *_vmappingAddAnyKeyElementRaw(vmappingAnyKey *mapping,
					const void *key,
					vinstance *element);

int _vmappingNextNonNullDictIterator(vdictIterator *dictIterator);
				     

/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * *
 */

/*
 * any key mappings
 */

#define vmappingGetAnyKeyObservable(m)	vportBASE_OBJECT(m, object)
#define vmappingGetAnyKeyLoadable(m) \
    vobservableGetLoadable(vmappingGetAnyKeyObservable(m))
#define vmappingGetAnyKeyInstance(m) \
    vloadableGetInstance(vmappingGetAnyKeyLoadable(m))
#define vmappingGetAnyKeyClass(m) \
    ((vmappingAnyKeyClass*)vinstanceGetClass(vmappingGetAnyKeyInstance(m)))

#define vmappingCreateAnyKeyOfClass(c) \
    ((vmappingAnyKey *) vinstanceCreateOfClass((vinstanceClass *)(c)))
#define vmappingCreateAnyKey() \
    vmappingCreateAnyKeyOfClass(vmappingGetDefaultAnyKeyClass())
#define vmappingInitAnyKeyOfClass(m,c) \
    vinstanceInitOfClass(vmappingGetAnyKeyInstance(m), (vinstanceClass *)(c))
#define vmappingInitAnyKey(m) \
    vmappingInitAnyKeyOfClass((m), vmappingGetDefaultAnyKeyClass())
#define vmappingDestroyAnyKey(m) \
    vinstanceDestroy(vmappingGetAnyKeyInstance(m))

#define vmappingCloneAnyKey(m) \
    ((vmappingAnyKey *) vloadableClone(vmappingGetAnyKeyLoadable(m)))
#define vmappingCopyAnyKey(m,t) \
    vloadableCopy(vmappingGetAnyKeyLoadable(m), vmappingGetAnyKeyLoadable(t))
#define vmappingCopyInitAnyKey(m,t) \
    vloadableCopyInit(vmappingGetAnyKeyLoadable(m), \
		      vmappingGetAnyKeyLoadable(t))

/*
 * vname key mappings
 */

#define vmappingGetAnyKey(m)	vportBASE_OBJECT(m, super)
#define vmappingGetObservable(m)  \
    vmappingGetAnyKeyObservable(vmappingGetAnyKey(m))
#define vmappingGetLoadable(m)  \
    vmappingGetAnyKeyLoadable(vmappingGetAnyKey(m))
#define vmappingGetInstance(m)  \
    vmappingGetAnyKeyInstance(vmappingGetAnyKey(m))
#define vmappingGetClass(m) \
    ((vmappingClass*)vinstanceGetClass(vmappingGetInstance(m)))

#define vmappingCreateOfClass(c) \
    ((vmapping *) vinstanceCreateOfClass((vinstanceClass *)(c)))
#define vmappingCreate() \
    vmappingCreateOfClass(vmappingGetDefaultClass())
#define vmappingCreateLoadable() \
    vmappingCreateOfClass(vmappingGetDefaultLoadableClass())
#define vmappingInitOfClass(m,c) \
    vinstanceInitOfClass(vmappingGetInstance(m), (vinstanceClass *)(c))
#define vmappingInit(m) \
    vmappingInitOfClass((m), vmappingGetDefaultClass())
#define vmappingInitLoadable(m) \
    vmappingInitOfClass((m), vmappingGetDefaultLoadableClass())
#define vmappingDestroy(m) \
    vinstanceDestroy(vmappingGetInstance(m))

#define vmappingClone(m) \
    ((vmapping *) vloadableCloneOfSubclass(vmappingGetLoadable(m), \
				 (vloadableClass *) vmappingGetDefaultClass()))
#define vmappingCopy(m,t) \
    vloadableCopy(vmappingGetLoadable(m), vmappingGetLoadable(t))
#define vmappingCopyInit(m,t) \
    vloadableCopyInitOfSubclass(vmappingGetLoadable(m), \
				vmappingGetLoadable(t), \
				(vloadableClass *) vmappingGetDefaultClass())

#define vmappingLoad(r) \
    ((vmapping *) vloadableLoadOfSubclass(r, \
				 (vloadableClass *) vmappingGetDefaultClass()))
#define vmappingLoadInit(m,r) \
    vloadableLoadInitOfSubclass(vmappingGetLoadable(m), (r), \
				(vloadableClass *) vmappingGetDefaultClass())
#define vmappingStore(m,r) \
    vloadableStore(vmappingGetLoadable(m), (r))

/*
 * iterators
 */

#define vmappingInitAnyKeyIterator(i,m) \
    vdictInitIterator(&(i)->dictIterator, (m)->elements);
#define vmappingNextAnyKeyIterator(i) \
    _vmappingNextNonNullDictIterator(&(i)->dictIterator)
#define vmappingDestroyAnyKeyIterator(i) \
    vdictDestroyIterator(&(i)->dictIterator)
#define vmappingGetAnyKeyIteratorKey(i) \
    (vdictGetIteratorKey(&(i)->dictIterator))
#define vmappingGetAnyKeyIteratorElement(i) \
    ((vinstance *) vdictGetIteratorValue(&(i)->dictIterator))

#define vmappingInitIterator(i,m) \
    vmappingInitAnyKeyIterator(i,vmappingGetAnyKey(m))
#define vmappingNextIterator(i) \
    vmappingNextAnyKeyIterator(i)
#define vmappingDestroyIterator(i) \
    vmappingDestroyAnyKeyIterator(i)
#define vmappingGetIteratorKey(i) \
    ((const vname *) vmappingGetAnyKeyIteratorKey(i))
#define vmappingGetIteratorElement(i) \
    vmappingGetAnyKeyIteratorElement(i)


/*
 * * * * * * * * * * PRIVATE FUNCTION MESSAGE DEFINITIONS * * * * * * * * * *
 */

#define _vmappingAddAnyKeyElementRaw(m,k,e) \
    vclassSend(vmappingGetAnyKeyClass(m), vmappingADD_ELEMENT, (m, k, e))
#define vmappingRemoveAnyKeyElement(m,k) \
    vclassSend(vmappingGetAnyKeyClass(m), vmappingREMOVE_ELEMENT, (m, k))
#define vmappingSetAnyKeyElementOwned(m,k,o) \
    vclassSend(vmappingGetAnyKeyClass(m), vmappingSET_ELEMENT_OWNED, (m, k, o))

vportEND_CPLUSPLUS_EXTERN_C


#ifdef	vportNULL_HEADER
#undef	vmappingHEADER
#define vmappingHEADER vportNULL_HEADER
#endif


#endif /* #ifndef vmappingINCLUDED */


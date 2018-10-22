/* $Id: vobservable.h,v 1.7 1997/10/01 21:59:19 robert Exp $ */

/************************************************************

    vobservable.h

    C Interface file for the Class Manager observable objects

    (c) Copyright Visix Software Inc.
    All rights reserved

************************************************************/

#ifndef vobservableINCLUDED
#define vobservableINCLUDED

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

#ifndef  vresourceINCLUDED
#include vresourceHEADER
#endif

#ifndef  vclassINCLUDED
#include vclassHEADER
#endif

#ifndef  vloadableINCLUDED
#include vloadableHEADER
#endif

#ifndef  voccurrenceINCLUDED
#include voccurrenceHEADER
#endif

#ifndef  viteratorINCLUDED
#include viteratorHEADER
#endif


vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * * * * * * * * * * PUBLIC TYPE DEFINITIONS * * * * * * * * * *
 */

typedef struct vobservable			vobservable;
typedef struct vobservableClass			vobservableClass;

typedef struct vobservableObserverIterator	vobservableObserverIterator;
typedef struct vobservableObserverIteratorClass	\
					      vobservableObserverIteratorClass;


/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */

void vobservableStartup(void);


vobservableClass *vobservableGetDefaultClass(
    void
    );

vloadable *vobservableGetLoadable(
    vobservable				*object
    );

vinstance *vobservableGetInstance(
    vobservable				*object
    );

vobservableClass *vobservableGetClass(
    vobservable				*object
    );

vobservable *vobservableCreateOfClass(
    vobservableClass			*observableClass
    );

vobservable *vobservableInitOfClass(
    vobservable				*object,
    vobservableClass			*observableClass
    );

void vobservableDestroy(
    vobservable				*object
    );

vobservable *vobservableClone(
    vobservable				*object
    );

void vobservableCopyInit(
    vobservable				*object,
    vobservable				*target
    );

void vobservableCopy(
    vobservable				*object,
    vobservable				*target
    );

vobservable *vobservableLoad(
    vresource				 resource
    );

void vobservableLoadInit(
    vobservable				*object,
    vresource				 resource
    );

void vobservableStore(
    vobservable				*object,
    vresource				 resource
    );

void vobservableDump(
    vobservable				*object,
    FILE				*stream
    );

const vname *vobservableGetTag(
    vobservable			       *object
    );

void vobservableSetTag(
    vobservable				*object,
    const vname				*tag
    );

void vobservableInstallObserver(
    vobservable				*object,
    vobservable				*observer
    );

void vobservableInstallObserverOwned(
    vobservable				*object,
    vobservable				*observer
    );

void vobservableUninstallObserver(
    vobservable				*object,
    vobservable				*observer
    );

vbool vobservableWillObserve(
    vobservable				*object,
    vclass /* voccurrenceClass */	*occurrenceClass
    );

void vobservableObserve(
    vobservable				*object,
    voccurrence				*occurrence
    );

vbool vobservableShouldAnnounce(
    vobservable				*object,
    vclass /* voccurrenceClass */	*occurrenceClass
    );

void vobservableAnnounce(
    vobservable				*object,
    voccurrence				*occurrence
    );

/*
 * object observer iterators
 */

vobservableObserverIteratorClass *vobservableGetDefaultObserverIteratorClass(
    void
    );

vobservableObserverIteratorClass *vobservableGetObserverIteratorClass(
    vobservableObserverIterator		*iterator
    );

viterator *vobservableGetObserverIteratorIterator(
    vobservableObserverIterator		*iterator
    );

void vobservableInitObserverIterator(
    vobservableObserverIterator		*iterator,
    vobservable				*object
    );

void vobservableDestroyObserverIterator(
    vobservableObserverIterator		*iterator
    );

vbool vobservableNextObserverIterator(
    vobservableObserverIterator		*iterator
    );

vobservable *vobservableGetObserverIteratorObserver(
    vobservableObserverIterator		*iterator
    );


/*
 * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * *
 */

struct vobservable {
    vloadable			 loadable;
    vobservable			*observer;
};

#define vobservableCLASS(SUPER, OBJECT)					      \
    vloadableCLASS(SUPER, OBJECT);					      \
    vclassMETHOD(vobservableINSTALL_OBSERVER,				      \
		 (OBJECT *object, vobservable *observer));		      \
    vclassMETHOD(vobservableINSTALL_OBSERVER_OWNED,			      \
		 (OBJECT *object, vobservable *observer));		      \
    vclassMETHOD(vobservableUNINSTALL_OBSERVER,				      \
		 (OBJECT *object, vobservable *observer));		      \
    vclassMETHOD_RET(vobservableWILL_OBSERVE, vbool,			      \
		 (OBJECT *object, voccurrenceClass *occurrenceClass));	      \
    vclassMETHOD(vobservableOBSERVE,					      \
		 (OBJECT *object, voccurrence *occurrence));		      \
    vclassMETHOD_RET(vobservableSHOULD_ANNOUNCE, vbool,			      \
		 (OBJECT *object, voccurrenceClass *occurrenceClass));	      \
    vclassMETHOD(vobservableANNOUNCE,					      \
		 (OBJECT *object, voccurrence *occurrence))


struct vobservableClass {
    vobservableCLASS(vobservableClass, vobservable);
};


struct vobservableObserverIterator {
  viterator			 super;

  vobservable			*single;
  vobservable			*list;
  int				 listIndex;
};

#define vobservableOBSERVER_ITERATOR_CLASS(CLASS, ITERATOR)		      \
    viteratorCLASS(CLASS, ITERATOR)

struct vobservableObserverIteratorClass {
    vobservableOBSERVER_ITERATOR_CLASS(vobservableObserverIteratorClass,
				vobservableObserverIterator);
};


/*
 * * * * * * * * * * PRIVATE FUNCTION PROTOTYPES * * * * * * * * * *
 */

/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * *
 */

#define vobservableGetLoadable(o)       vportBASE_OBJECT(o, loadable)
#define vobservableGetInstance(o) \
    vloadableGetInstance(vobservableGetLoadable(o))
#define vobservableGetClass(o) \
    ((vobservableClass*)vloadableGetClass(vobservableGetLoadable(o)))
#define vobservableCreateOfClass(o) \
    ((vobservable *)vloadableCreateOfClass((vloadableClass*)(o)))
#define vobservableInitOfClass(o, c) \
    vloadableInitOfClass(vobservableGetLoadable(o), (vloadableClass*)(c))
#define vobservableDestroy(o) \
    vloadableDestroy(vobservableGetLoadable(o))
#define vobservableGetTag(o) \
    vloadableGetTag(vobservableGetLoadable(o))
#define vobservableSetTag(o, t) \
    vloadableSetTag(vobservableGetLoadable(o), t)
#define vobservableLoad(r) \
    ((vobservable *)vloadableLoadOfSubclass(r, \
			       (vloadableClass *)vobservableGetDefaultClass()))
#define vobservableLoadInit(o, r) \
    vloadableLoadInitOfSubclass(vobservableGetLoadable(o), r, \
				(vloadableClass *)vobservableGetDefaultClass())
#define vobservableStore(o, r) \
    vloadableStore(vobservableGetLoadable(o), r)
#define vobservableDump(o, s) \
    vloadableDump(vobservableGetLoadable(o), s)
#define vobservableCopy(o, t) \
    vloadableCopy(vobservableGetLoadable(o), vobservableGetLoadable(t))
#define vobservableCopyInit(o, t) \
    vloadableCopyInitOfSubclass(vobservableGetLoadable(o), \
				vobservableGetLoadable(t), \
				(vloadableClass *)vobservableGetDefaultClass())
#define vobservableClone(o) \
    ((vobservable *)vloadableCloneOfSubclass(vobservableGetLoadable(o), \
			       (vloadableClass *)vobservableGetDefaultClass()))


#define vobservableGetObserverIteratorIterator(i) \
    vportBASE_OBJECT(i, super)
#define vobservableGetObserverIteratorClass(i) \
    ((vobservableObserverIteratorClass *) \
     viteratorGetClass(vobservableGetObserverIteratorIterator(i)))

#define vobservableDestroyObserverIterator(i) \
    viteratorDestroy(vobservableGetObserverIteratorIterator(i))
#define vobservableNextObserverIterator(i) \
    viteratorNext(vobservableGetObserverIteratorIterator(i))
#define vobservableGetObserverIteratorObserver(i) \
    ((vobservable *) \
     viteratorGetElement(vobservableGetObserverIteratorIterator(i)))

/*
 * * * * * * * * * * PRIVATE FUNCTION MESSAGE DEFINITIONS * * * * * * * * * *
 */

#define vobservableInstallObserver(o, b) \
    vclassSend(vobservableGetClass(o), vobservableINSTALL_OBSERVER, (o, b))
#define vobservableInstallObserverOwned(o, b) \
    vclassSend(vobservableGetClass(o), vobservableINSTALL_OBSERVER_OWNED, \
	       (o, b))
#define vobservableUninstallObserver(o, b) \
    vclassSend(vobservableGetClass(o), vobservableUNINSTALL_OBSERVER, (o, b))
#define vobservableWillObserve(o, c) \
    vclassSend(vobservableGetClass(o), vobservableWILL_OBSERVE, \
	       (o, ((voccurrenceClass *)(c))))
#define vobservableObserve(o, c) \
    vclassSend(vobservableGetClass(o), vobservableOBSERVE, (o, c))
#define vobservableShouldAnnounce(o, c) \
    vclassSend(vobservableGetClass(o), vobservableSHOULD_ANNOUNCE, \
	       (o, ((voccurrenceClass *)(c))))
#define vobservableAnnounce(o, c) \
    vclassSend(vobservableGetClass(o), vobservableANNOUNCE, (o, c))


vportEND_CPLUSPLUS_EXTERN_C


#ifdef  vportNULL_HEADER
#undef  vobservableHEADER
#define vobservableHEADER vportNULL_HEADER
#endif


#endif /* #ifndef vobservableINCLUDED */


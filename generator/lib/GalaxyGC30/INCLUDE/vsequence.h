/* $Id: vsequence.h,v 1.5 1997/09/17 18:50:28 robert Exp $ */

/************************************************************

    vsequence.h

    C Interface file for the Class Manager loadable objects

    (c) Copyright Visix Software Inc.
    All rights reserved

************************************************************/

#ifndef vsequenceINCLUDED
#define vsequenceINCLUDED

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

typedef struct vsequence		vsequence;
typedef struct vsequenceClass		vsequenceClass;

typedef vsequence			vsequenceLoadable;


/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */

void vsequenceStartup(void);


vsequenceClass *vsequenceGetDefaultClass(
    void
    );

vsequenceClass *vsequenceGetDefaultLoadableClass(
    void
    );

vinstance *vsequenceGetInstance(
    vsequence			*sequence
    );

vloadable *vsequenceGetLoadable(
    vsequence			*sequence
    );

vobservable *vsequenceGetObservable(
    vsequence			*sequence
    );

vsequenceClass *vsequenceGetClass(
    vsequence			*sequence
    );

vsequence *vsequenceCreateOfClass(
    vsequenceClass		*clas
    );

vsequence *vsequenceCreate(
    void
    );

vsequence *vsequenceCreateLoadable(
    void
    );

void vsequenceInitOfClass(
    vsequence			*sequence, 
    vsequenceClass		*clas
    );

void vsequenceInit(
    vsequence			*sequence
    );

void vsequenceInitLoadable(
    vsequence			*sequence
    );

void vsequenceDestroy(
    vsequence			*sequence
    );

vsequence *vsequenceClone(
    vsequence			*sequence
    );

void vsequenceCopy(
    vsequence			*source,
    vsequence			*target
    );

void vsequenceCopyInit(
    vsequence			*source,
    vsequence			*target
    );

vsequence *vsequenceLoad(
    vresource			 resource
    );

void vsequenceLoadInit(
    vsequence			*sequence,
    vresource			 resource
    );

void vsequenceStore(
    vsequence			*sequence,
    vresource			 resource
    );

void vsequenceAppendElementShared(
    vsequence			*sequence,
    vinstance			*element
    );

void vsequenceAppendElementOwned(
    vsequence			*sequence,
    vinstance			*element
    );

void vsequenceInsertElementShared(
    vsequence			*sequence,
    int				 index,
    vinstance			*element
    );

void vsequenceInsertElementOwned(
    vsequence			*sequence,
    int				 index,
    vinstance			*element
    );

vinstance *vsequenceRemoveElementAt(
    vsequence			*sequence,
    int				 index
    );

vinstance *vsequenceRemoveElement(
    vsequence			*sequence,
    vinstance			*element
    );

vinstance *vsequenceReplaceElementAtShared(
    vsequence			*sequence,
    int				 index,
    vinstance			*element
    );

vinstance *vsequenceReplaceElementAtOwned(
    vsequence			*sequence,
    int				 index,
    vinstance			*element
    );

int vsequenceGetElementCount(
    vsequence			*sequence
    );

vinstance *vsequenceGetElementAt(
    vsequence			*sequence,
    int				 index
    );

int vsequenceGetElementIndex(
    vsequence			*sequence,
    vinstance			*element
    );

void vsequenceMoveIndex(
    vsequence			*sequence,
    int				 currentIndex,
    int				 newIndex
    );

void vsequenceMoveElement(
    vsequence			*sequence,
    vinstance			*element,
    int				 index
    );

vbool vsequenceIsIndexOwned(
    vsequence			*sequence,
    int				 index
    );

void vsequenceSetIndexOwned(
    vsequence			*sequence,
    int				 index,
    int				 owned
    );


/*
 * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * *
 */

enum {
    _vsequenceNO_ELEMENTS_OWNED		= 0x00,
    _vsequenceSOME_ELEMENTS_OWNED	= 0x01,
    _vsequenceALL_ELEMENTS_OWNED	= 0x02
};


struct vsequence {
    vobservable			  object;
    unsigned short		  flags;
    vinstance			**elements, **stop, **max, **allocMax;
};

#define vsequenceCLASS(SUPER, SEQUENCE)					      \
    vobservableCLASS(SUPER, SEQUENCE);					      \
    vclassVARIABLE(vsequenceELEMENT_CLASS, const vinstanceClass *);	      \
    vclassMETHOD(vsequenceAPPEND_ELEMENT,				      \
		 (SEQUENCE *sequence, vinstance *element));		      \
    vclassMETHOD_RET(vsequenceREMOVE_ELEMENT_AT, vinstance *,		      \
		 (SEQUENCE *sequence, int index));			      \
    vclassMETHOD_RET(vsequenceREPLACE_ELEMENT_AT, vinstance *,		      \
		 (SEQUENCE *sequence, int index, vinstance *element));	      \
    vclassMETHOD(vsequenceMOVE_INDEX,					      \
		 (SEQUENCE *sequence, int currentIndex, int newIndex));	      \
    vclassMETHOD(vsequenceSET_INDEX_OWNED,				      \
		 (SEQUENCE *sequence, int index, int owned))

struct vsequenceClass {
    vsequenceCLASS(vsequenceClass, vsequence);
};


vportALIAS(vsequenceLoadable, vsequence)


/*
 * * * * * * * * * * PRIVATE VARIABLE DECLARATIONS * * * * * * * * * *
 */

/*
 * * * * * * * * * * PRIVATE FUNCTION PROTOTYPES * * * * * * * * * *
 */

void _vsequenceAppendElementRaw(
    vsequence			*sequence,
    vinstance			*element
    );

vinstance *_vsequenceReplaceElementAtRaw(
    vsequence			*sequence,
    int				 index,
    vinstance			*element
    );

/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * *
 */

#define vsequenceGetObservable(s)    vportBASE_OBJECT(s, object)
#define vsequenceGetLoadable(s) \
    vobservableGetLoadable(vsequenceGetObservable(s))
#define vsequenceGetInstance(s) \
    vloadableGetInstance(vsequenceGetLoadable(s))
#define vsequenceGetClass(s) \
    ((vsequenceClass*)vinstanceGetClass(vsequenceGetInstance(s)))

#define vsequenceCreateOfClass(c) \
    ((vsequence *) vinstanceCreateOfClass((vinstanceClass *)(c)))
#define vsequenceCreate() \
    vsequenceCreateOfClass(vsequenceGetDefaultClass())
#define vsequenceCreateLoadable() \
    vsequenceCreateOfClass(vsequenceGetDefaultLoadableClass())
#define vsequenceInitOfClass(s,c) \
    vinstanceInitOfClass(vsequenceGetInstance(s), (vinstanceClass *)(c))
#define vsequenceInit(s) \
    vsequenceInitOfClass((s), vsequenceGetDefaultClass())
#define vsequenceInitLoadable(s) \
    vsequenceInitOfClass((s), vsequenceGetDefaultLoadableClass())
#define vsequenceDestroy(s) \
    vinstanceDestroy(vsequenceGetInstance(s))

#define vsequenceClone(s) \
    ((vsequence *) vloadableCloneOfSubclass(vsequenceGetLoadable(s), \
				(vloadableClass *) vsequenceGetDefaultClass()))
#define vsequenceCopy(s,t) \
    vloadableCopy(vsequenceGetLoadable(s), vsequenceGetLoadable(t))
#define vsequenceCopyInit(s,t) \
    vloadableCopyInitOfSubclass(vsequenceGetLoadable(s), \
				vsequenceGetLoadable(t), \
				(vloadableClass *) vsequenceGetDefaultClass())

#define vsequenceLoad(r) \
    ((vsequence *) vloadableLoadOfSubclass(r, \
				(vloadableClass *) vsequenceGetDefaultClass()))
#define vsequenceLoadInit(s,r) \
    vloadableLoadInitOfSubclass(vsequenceGetLoadable(s), (r), \
				(vloadableClass *) vsequenceGetDefaultClass())
#define vsequenceStore(s,r) \
    vloadableStore(vsequenceGetLoadable(s), (r))


/*
 * * * * * * * * * * PRIVATE FUNCTION MESSAGE DEFINITIONS * * * * * * * * * *
 */

#define _vsequenceAppendElementRaw(s,e) \
    vclassSend(vsequenceGetClass(s), vsequenceAPPEND_ELEMENT, (s, e))
#define vsequenceRemoveElementAt(s,i) \
    vclassSend(vsequenceGetClass(s), vsequenceREMOVE_ELEMENT_AT, (s, i))
#define _vsequenceReplaceElementAtRaw(s,i,e) \
    vclassSend(vsequenceGetClass(s), vsequenceREPLACE_ELEMENT_AT, (s, i, e))
#define vsequenceMoveIndex(s,i,n) \
    vclassSend(vsequenceGetClass(s), vsequenceMOVE_INDEX, (s, i, n))
#define vsequenceSetIndexOwned(s,i,o) \
    vclassSend(vsequenceGetClass(s), vsequenceSET_INDEX_OWNED, (s, i, o))


vportEND_CPLUSPLUS_EXTERN_C


#ifdef	vportNULL_HEADER
#undef	vsequenceHEADER
#define vsequenceHEADER vportNULL_HEADER
#endif


#endif /* #ifndef vsequenceINCLUDED */


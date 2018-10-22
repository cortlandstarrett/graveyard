/* $Id: voccurrence.h,v 1.3 1996/06/18 23:04:59 robert Exp $ */

/************************************************************

    voccurrence.h

    C Interface file for the observation occurrences

    (c) Copyright Visix Software Inc.
    All rights reserved

************************************************************/

#ifndef voccurrenceINCLUDED
#define voccurrenceINCLUDED

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

#ifndef  vclassINCLUDED
#include vclassHEADER
#endif

#ifndef  vinstanceINCLUDED
#include vinstanceHEADER
#endif


vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * * * * * * * * * * PUBLIC CONSTANT DEFINITIONS  * * * * * * * * * *
 */

/*
 * * * * * * * * * * PUBLIC TYPE DEFINITIONS * * * * * * * * * *
 */

typedef struct voccurrence		voccurrence;
typedef struct voccurrenceClass		voccurrenceClass;

typedef struct voccurrenceDestroyed	voccurrenceDestroyed;
typedef struct voccurrenceDestroyedClass
					voccurrenceDestroyedClass;

typedef struct voccurrenceEvent		voccurrenceEvent;
typedef struct voccurrenceEventClass	voccurrenceEventClass;

typedef struct voccurrenceStateChanged	voccurrenceStateChanged;
typedef struct voccurrenceStateChangedClass
					voccurrenceStateChangedClass;

typedef struct voccurrenceAttributeChanged
					voccurrenceAttributeChanged;
typedef struct voccurrenceAttributeChangedClass
					voccurrenceAttributeChangedClass;


/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */

void voccurrenceStartup(void);


/*
 * occurrences
 */

voccurrenceClass *voccurrenceGetDefaultClass(
    void
    );

vinstance *voccurrenceGetInstance(
    voccurrence                      *occurrence
    );

voccurrenceClass *voccurrenceGetClass(
    voccurrence                      *occurrence
    );

voccurrence *voccurrenceCreateOfClass(
    voccurrenceClass                 *clas
    );

void voccurrenceInitOfClass(
    voccurrence                      *occurrence,
    voccurrenceClass                 *clas
    );

void voccurrenceDestroy(
    voccurrence                      *occurrence
    );

void voccurrenceSetAnnouncer(
    voccurrence                      *occurrence,
    vinstance			     *announcer
    );

vinstance *voccurrenceGetAnnouncer(
    voccurrence                      *occurrence
    );


/*
 * destroyed occurrences:
 */

voccurrenceDestroyedClass *voccurrenceGetDefaultDestroyedClass(
    void
    );

voccurrenceDestroyed *voccurrenceCreateDestroyed(
    void
    );

voccurrence *voccurrenceGetDestroyedOccurrence(
    voccurrenceDestroyed	     *occurrence
    );

voccurrenceDestroyedClass *voccurrenceGetDestroyedClass(
    voccurrenceDestroyed	     *occurrence
    );

voccurrence *voccurrenceMakeDestroyed(
    void
    );


/*
 * event occurrences:
 */

voccurrenceEventClass *voccurrenceGetDefaultEventClass(
    void
    );

voccurrenceEvent *voccurrenceCreateEvent(
    void
    );

voccurrence *voccurrenceGetEventOccurrence(
    voccurrenceEvent		     *occurrence
    );

voccurrenceEventClass *voccurrenceGetEventClass(
    voccurrenceEvent		     *occurrence
    );

void voccurrenceSetEvent(
    voccurrenceEvent                 *occurrence,
    vevent			     *event
    );

vevent *voccurrenceGetEvent(
    voccurrenceEvent                 *occurrence
    );

voccurrence *voccurrenceMakeEvent(
    vevent			     *event
    );


/*
 * state changed occurrences:
 */

voccurrenceStateChangedClass *voccurrenceGetDefaultStateChangedClass(
    void
    );

voccurrenceStateChanged *voccurrenceCreateStateChanged(
    void
    );

voccurrence *voccurrenceGetStateChangedOccurrence(
    voccurrenceStateChanged	     *occurrence
    );

voccurrenceStateChangedClass *voccurrenceGetStateChangedClass(
    voccurrenceStateChanged	     *occurrence
    );

void voccurrenceSetOldState(
    voccurrenceStateChanged          *occurrence,
    const vname			     *oldState
    );

void voccurrenceSetNewState(
    voccurrenceStateChanged          *occurrence,
    const vname			     *newState
    );

const vname *voccurrenceGetOldState(
    voccurrenceStateChanged          *occurrence
    );

const vname *voccurrenceGetNewState(
    voccurrenceStateChanged          *occurrence
    );

voccurrence *voccurrenceMakeStateChanged(
    const vname			     *oldState,
    const vname			     *newState
    );


/*
 * attribute changed occurrences:
 */

voccurrenceAttributeChangedClass *voccurrenceGetDefaultAttributeChangedClass(
    void
    );

voccurrenceAttributeChanged *voccurrenceCreateAttributeChanged(
    void
    );

voccurrence *voccurrenceGetAttributeChangedOccurrence(
    voccurrenceAttributeChanged	     *occurrence
    );

voccurrenceAttributeChangedClass *voccurrenceGetAttributeChangedClass(
    voccurrenceAttributeChanged	     *occurrence
    );

void voccurrenceSetAttributeName(
    voccurrenceAttributeChanged      *occurrence,
    const vname			     *attributeName
    );

void voccurrenceSetOldAttributeValue(
    voccurrenceAttributeChanged      *occurrence,
    vinstance			     *oldValue
    );

void voccurrenceSetNewAttributeValue(
    voccurrenceAttributeChanged      *occurrence,
    vinstance			     *newValue
    );

const vname *voccurrenceGetAttributeName(
    voccurrenceAttributeChanged      *occurrence
    );

vinstance *voccurrenceGetOldAttributeValue(
    voccurrenceAttributeChanged      *occurrence
    );

vinstance *voccurrenceGetNewAttributeValue(
    voccurrenceAttributeChanged      *occurrence
    );

voccurrence *voccurrenceMakeAttributeChanged(
    const vname			     *attributeName,
    vinstance			     *oldValue,
    vinstance			     *newValue
    );


/*
 * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * *
 */


struct voccurrence {
    vinstance			 instance;
    vinstance			*announcer;
};

#define voccurrenceCLASS(SUPER, OCCURRENCE)                                   \
    vinstanceCLASS(SUPER, OCCURRENCE);					      \
    vclassMETHOD(voccurrenceSET_ANNOUNCER,				      \
		 (OCCURRENCE *occurrence, vinstance *announcer))

struct voccurrenceClass {
    voccurrenceCLASS(voccurrenceClass, voccurrence);
};


struct voccurrenceDestroyed {
    voccurrence			 super;
};

#define voccurrenceDESTROYED_CLASS(SUPER, OCCURRENCE)                         \
    voccurrenceCLASS(SUPER, OCCURRENCE)

struct voccurrenceDestroyedClass {
    voccurrenceDESTROYED_CLASS(voccurrenceDestroyedClass,
			       voccurrenceDestroyed);
};


struct voccurrenceEvent {
    voccurrence			 super;
    vevent			*event;
};

#define voccurrenceEVENT_CLASS(SUPER, OCCURRENCE)                             \
    voccurrenceCLASS(SUPER, OCCURRENCE);				      \
    vclassMETHOD(voccurrenceSET_EVENT,					      \
		 (OCCURRENCE *occurrence, vevent *event))

struct voccurrenceEventClass {
    voccurrenceEVENT_CLASS(voccurrenceEventClass, voccurrenceEvent);
};


struct voccurrenceStateChanged {
    voccurrence			 super;
    const vname			*oldState;
    const vname			*newState;
};

#define voccurrenceSTATE_CHANGED_CLASS(SUPER, OCCURRENCE)	              \
    voccurrenceCLASS(SUPER, OCCURRENCE);				      \
    vclassMETHOD(voccurrenceSET_OLD_STATE,				      \
		 (OCCURRENCE *occurrence, const vname *oldState));	      \
    vclassMETHOD(voccurrenceSET_NEW_STATE,				      \
		 (OCCURRENCE *occurrence, const vname *newState))

struct voccurrenceStateChangedClass {
    voccurrenceSTATE_CHANGED_CLASS(voccurrenceStateChangedClass,
				       voccurrenceStateChanged);
};


struct voccurrenceAttributeChanged {
    voccurrence			 super;
    const vname			*attributeName;
    vinstance			*oldValue;
    vinstance			*newValue;
};

#define voccurrenceATTRIBUTE_CHANGED_CLASS(SUPER, OCCURRENCE)                 \
    voccurrenceCLASS(SUPER, OCCURRENCE);				      \
    vclassMETHOD(voccurrenceSET_ATTRIBUTE_NAME,				      \
		 (OCCURRENCE *occurrence, const vname *attributeName));	      \
    vclassMETHOD(voccurrenceSET_OLD_ATTRIBUTE_VALUE,			      \
		 (OCCURRENCE *occurrence, vinstance *oldValue));	      \
    vclassMETHOD(voccurrenceSET_NEW_ATTRIBUTE_VALUE,			      \
		 (OCCURRENCE *occurrence, vinstance *newValue))

struct voccurrenceAttributeChangedClass {
    voccurrenceATTRIBUTE_CHANGED_CLASS(voccurrenceAttributeChangedClass,
				       voccurrenceAttributeChanged);
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
 * occurrences
 */

#define voccurrenceGetInstance(o) \
	vportBASE_OBJECT(o, instance)
#define voccurrenceGetClass(o) \
	((voccurrenceClass *) \
	   vinstanceGetClass(voccurrenceGetInstance(o)))

#define voccurrenceCreateOfClass(c) \
	((voccurrence *) vinstanceCreateOfClass((vinstanceClass *)(c)))
#define voccurrenceInitOfClass(o,c) \
	vinstanceInitOfClass((vinstance *)(o), (vinstanceClass *)(c))
#define voccurrenceDestroy(o) \
	vinstanceDestroy((vinstance *)(o))

#define voccurrenceGetAnnouncer(o) \
	((o)->announcer)

#define voccurrenceGetDestroyedOccurrence(o) \
	vportBASE_OBJECT(o, super)
#define voccurrenceGetDestroyedClass(o) \
	((voccurrenceDestroyedClass *) \
	   voccurrenceGetClass(voccurrenceGetDestroyedOccurrence(o)))

#define voccurrenceCreateDestroyed() \
	((voccurrenceDestroyed *) voccurrenceCreateOfClass( \
	    (voccurrenceClass *) voccurrenceGetDefaultDestroyedClass()))

#define voccurrenceGetEventOccurrence(o) \
	vportBASE_OBJECT(o, super)
#define voccurrenceGetEventClass(o) \
	((voccurrenceEventClass *) \
	   voccurrenceGetClass(voccurrenceGetEventOccurrence(o)))

#define voccurrenceCreateEvent() \
	((voccurrenceEvent *) voccurrenceCreateOfClass( \
	    (voccurrenceClass *) voccurrenceGetDefaultEventClass()))

#define voccurrenceGetEvent(o) \
	((o)->event)

#define voccurrenceGetStateChangedOccurrence(o) \
	vportBASE_OBJECT(o, super)
#define voccurrenceGetStateChangedClass(o) \
	((voccurrenceStateChangedClass *) \
	   voccurrenceGetClass(voccurrenceGetStateChangedOccurrence(o)))

#define voccurrenceCreateStateChanged() \
	((voccurrenceStateChanged *) voccurrenceCreateOfClass( \
	    (voccurrenceClass *) voccurrenceGetDefaultStateChangedClass()))

#define voccurrenceGetOldState(o) \
	((o)->oldState)
#define voccurrenceGetNewState(o) \
	((o)->newState)

#define voccurrenceGetAttributeChangedOccurrence(o) \
	vportBASE_OBJECT(o, super)
#define voccurrenceGetAttributeChangedClass(o) \
	((voccurrenceAttributeChangedClass *) \
	   voccurrenceGetClass(voccurrenceGetAttributeChangedOccurrence(o)))

#define voccurrenceCreateAttributeChanged() \
	((voccurrenceAttributeChanged *) voccurrenceCreateOfClass( \
	    (voccurrenceClass *) voccurrenceGetDefaultAttributeChangedClass()))

#define voccurrenceGetAttributeName(o) \
	((o)->attributeName)
#define voccurrenceGetOldAttributeValue(o) \
	((o)->oldValue)
#define voccurrenceGetNewAttributeValue(o) \
	((o)->newValue)


/*
 * * * * * * * * * * PRIVATE FUNCTION MESSAGE DEFINITIONS * * * * * * * * * *
 */

#define voccurrenceSetAnnouncer(o, a) \
    vclassSend(voccurrenceGetClass(o), voccurrenceSET_ANNOUNCER, \
	       (o, a))

#define voccurrenceSetEvent(o, e) \
    vclassSend(voccurrenceGetEventClass(o), voccurrenceSET_EVENT, \
	       (o, e))

#define voccurrenceSetOldState(o, os) \
    vclassSend(voccurrenceGetStateChangedClass(o), voccurrenceSET_OLD_STATE, \
	       (o, os))

#define voccurrenceSetNewState(o, ns) \
    vclassSend(voccurrenceGetStateChangedClass(o), voccurrenceSET_NEW_STATE, \
	       (o, ns))

#define voccurrenceSetAttributeName(o, n) \
    vclassSend(voccurrenceGetAttributeChangedClass(o), \
	       voccurrenceSET_ATTRIBUTE_NAME, \
	       (o, n))

#define voccurrenceSetOldAttributeValue(o, ov) \
    vclassSend(voccurrenceGetAttributeChangedClass(o), \
	       voccurrenceSET_OLD_ATTRIBUTE_VALUE, \
	       (o, ov))

#define voccurrenceSetNewAttributeValue(o, nv) \
    vclassSend(voccurrenceGetAttributeChangedClass(o), \
	       voccurrenceSET_NEW_ATTRIBUTE_VALUE, \
	       (o, nv))


vportEND_CPLUSPLUS_EXTERN_C


#ifdef  vportNULL_HEADER
#ifdef  voccurrenceHEADER
#undef  voccurrenceHEADER
#endif
#define voccurrenceHEADER vportNULL_HEADER
#endif


#endif /* #ifndef voccurrenceINCLUDED */


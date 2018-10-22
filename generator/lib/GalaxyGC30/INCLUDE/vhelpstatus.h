/* $Id: vhelpstatus.h,v 1.3 1997/11/14 18:42:22 paulm Exp $ */

/* -----------------------------------------------------------------------
 *
 *  vhelpstatus.h
 *
 *  Programming interface to the vhelpstatus class
 *
 *  (c) Copyright Visix Software
 *  All rights reserved
 *
 * -----------------------------------------------------------------------
 */

#ifndef vhelpstatusINCLUDED
#define vhelpstatusINCLUDED	1

#ifndef vportINCLUDED
#include <vport.h>
#endif

#ifndef  vhelpdisplayINCLUDED
#include vhelpdisplayHEADER
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * * * * * * * * * * PUBLIC TYPE DEFINITIONS * * * * * * * * * *
 */

typedef struct	vhelpstatus			vhelpstatus;
typedef struct	vhelpstatusClass		vhelpstatusClass;

typedef struct	vhelpstatusOccurrence		vhelpstatusOccurrence;
typedef struct	vhelpstatusOccurrenceClass	vhelpstatusOccurrenceClass;

/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */

void vhelpstatusStartup(
    void
    );

vhelpstatusClass *vhelpstatusGetDefaultClass(
    void
    );

vhelpstatus *vhelpstatusCreateOfClass(
    vhelpstatusClass	*clas
    );

vhelpstatusClass *vhelpstatusGetClass(
    vhelpstatus		*helpdisplay
    );

vhelpstatus *vhelpstatusCreate(
    void
    );

void vhelpstatusInitOfClass(
    vhelpstatus		*helpdisplay,
    vhelpstatusClass	*clas
    );

void vhelpstatusInit(
    vhelpstatus		*helpdisplay
    );

void vhelpstatusDestroy(
    vhelpstatus		*helpdisplay
    );

vhelpdisplay *vhelpstatusGetDisplay(
    vhelpstatus		*helpdisplay
    );

void vhelpstatusInstallObserver(
    vhelpstatus		*helpdisplay,
    vobservable		 observer
    );

void vhelpstatusUninstallObserver(
    vhelpstatus		*helpdisplay,
    vobservable		 observer
    );

void vhelpstatusAnnounce(
    vhelpstatus		*helpdisplay,
    voccurrence		*occurrence
    );


void vhelpstatusStartupOccurrence(
    void
    );

vhelpstatusOccurrenceClass *vhelpstatusGetDefaultOccurrenceClass(
    void
    );

vhelpstatusOccurrence *vhelpstatusCreateOccurrenceOfClass(
    vhelpstatusClass			*clas
    );

vhelpstatusOccurrenceClass *vhelpstatusGetOccurrenceClass(
    vhelpstatus				*occurrence
    );

vhelpstatusOccurrence *vhelpstatusCreateOccurrence(
    void
    );

void vhelpstatusInitOccurrenceOfClass(
    vhelpstatusOccurrence		*occurrence,
    vhelpstatusOccurrenceClass		*clas
    );

void vhelpstatusInitOccurrence(
    vhelpstatusOccurrence		*occurrence
    );

void vhelpstatusDestroyOccurrence(
    vhelpstatusOccurrence		*occurrence
    );

voccurrence *vhelpstatusGetOccurrenceOccurrence(
    vhelpstatusOccurrence		*occurrence
    );

const vchar *vhelpstatusGetOccurrenceString(
    vhelpstatusOccurrence		*occurrence
    );

void vhelpstatusSetOccurrenceString(
    vhelpstatusOccurrence		*occurrence,
    const vchar                         *string
    );

void vhelpstatusSetOccurrenceStringScribed(
    vhelpstatusOccurrence		*occurrence,
    vscribe                             *scribe
    );

/*
 * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * *
 */

struct vhelpstatus {
    vhelpdisplay	display;
};

#define vhelpstatusCLASS(SUPER, HELPDIS)		        	\
    vhelpdisplayCLASS(SUPER, HELPDIS)

struct vhelpstatusClass {
    vhelpstatusCLASS(vhelpstatusClass, vhelpstatus);
};

struct vhelpstatusOccurrence {
    voccurrence		 occurrence;
    const vchar		*string;
    unsigned short	 flags;
};

#define vhelpstatusOccurrenceCLASS(SUPER, OCCURRENCE)	        	\
    voccurrenceCLASS(SUPER, OCCURRENCE);				\
    vclassMETHOD(vhelpstatusSET_OCCURRENCE_STRING_SCRIBED, 		\
		 (OCCURRENCE *occurrence, vscribe *scribe))

struct vhelpstatusOccurrenceClass {
    vhelpstatusOccurrenceCLASS(vhelpstatusOccurrenceClass, 		\
			       vhelpstatusOccurrence);
};

/*
 * Flag values.
 */
enum 
{
    _vhelpstatusOCCURRENCE_STRING_OWNED = 0x0001
};

/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * *
 */
#define vhelpstatusGetDisplay(d)     vportBASE_OBJECT((d), display)
#define vhelpstatusGetClass(d)						\
    ((vhelpstatusClass*)						\
     vhelpdisplayGetClass(vhelpstatusGet(d)))
#define vhelpstatusCreateOfClass(c) 					\
    ((vhelpstatus *)							\
     vhelpdisplayCreateOfClass((vhelpstatusClass*)(c)))
#define vhelpstatusCreate()						\
    vhelpstatusCreateOfClass(vhelpstatusGetDefaultClass())
#define vhelpstatusInitOfClass(d, c) 					\
    vhelpdisplayInitOfClass(vhelpstatusGetDisplay(d),			\
			    (vhelpdisplayClass*)(c))
#define vhelpstatusInit(d) 						\
    vhelpstatusInitOfClass((d), vhelpstatusGetDefaultClass())
#define vhelpstatusDestroy(d)					        \
    vhelpdisplayDestroy(vhelpstatusGetDisplay(d))
#define vhelpstatusInstallObserver(d, o)				\
    vobservableInstallObserver(vhelpdisplayGetObservable(		\
        vhelpstatusGetDisplay(d)), (o))
#define vhelpstatusUninstallObserver(d, o)				\
    vobservableUninstallObserver(vhelpdisplayGetObservable(		\
        vhelpstatusGetDisplay(d)), (o))
#define vhelpstatusAnnounce(d, o)					\
    vobservableAnnounce(vhelpdisplayGetObservable(			\
        vhelpstatusGetDisplay(d)), (o))

#define vhelpstatusGetOccurrenceOccurrence(o)		     		\
    vportBASE_OBJECT((o), occurrence)
#define vhelpstatusGetOccurrenceClass(o)				\
    ((vhelpstatusOccurrenceClass*)					\
     voccurrenceGetClass(vhelpstatusGetOccurrenceOccurrence(o)))
#define vhelpstatusCreateOccurrenceOfClass(c) 				\
    ((vhelpstatusOccurrence *)						\
     voccurrenceCreateOfClass((vhelpstatusOccurrenceClass*)(c)))
#define vhelpstatusCreateOccurrence()					\
    vhelpstatusCreateOccurrenceOfClass(vhelpstatusGetDefaultOccurrenceClass())
#define vhelpstatusInitOccurrenceOfClass(o, c) 				\
    voccurrenceInitOfClass(vhelpstatusGetOccurrenceOccurrence(o),	\
			    (voccurrenceClass*)(c))
#define vhelpstatusInitOccurrence(o) 					\
    vhelpstatusInitOccurrenceOfClass((o), 				\
        vhelpstatusGetDefaultOccurrenceClass())
#define vhelpstatusDestroyOccurrence(o)				        \
    voccurrenceDestroy(vhelpstatusGetOccurrenceOccurrence(o))

#define vhelpstatusSetOccurrenceString(o, s)				\
    vhelpstatusSetOccurrenceStringScribed(o, vcharScribe(s))
#define vhelpstatusGetOccurrenceString(o)		(o)->string


/*
 * * * * * * * * * * PRIVATE FUNCTION MESSAGE DEFINITIONS * * * * * * * * * *
 */

#define vhelpstatusSetOccurrenceStringScribed(o, s)			\
    vclassSend(vhelpstatusGetOccurrenceClass(o),			\
	       vhelpstatusSET_OCCURRENCE_STRING_SCRIBED, (o, s))

vportEND_CPLUSPLUS_EXTERN_C

#endif /* vhelpstatusINCLUDED */



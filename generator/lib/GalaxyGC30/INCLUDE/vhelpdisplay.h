/* $Id: vhelpdisplay.h,v 1.4 1997/11/14 19:55:05 robert Exp $ */

/* -----------------------------------------------------------------------
 *
 *  vhelpdisplay.h
 *
 *  Programming interface to the root vhelpdisplay class
 *
 *  (c) Copyright Visix Software
 *  All rights reserved
 *
 * -----------------------------------------------------------------------
 */

#ifndef vhelpdisplayINCLUDED
#define vhelpdisplayINCLUDED	1

#ifndef vportINCLUDED
#include <vport.h>
#endif

#ifndef  vhelprequestINCLUDED
#include vhelprequestHEADER
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * * * * * * * * * * PUBLIC TYPE DEFINITIONS * * * * * * * * * *
 */

typedef struct	vhelpdisplay			vhelpdisplay;
typedef struct	vhelpdisplayClass		vhelpdisplayClass;       

/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */

/*
 * Creation/Destruction/Class Management
 */


vhelpdisplayClass *vhelpdisplayGetRootClass(void);

vhelpdisplayClass *vhelpdisplayGetClass(
    vhelpdisplayClass	*helpdisplayClass
    );

vhelpdisplay *vhelpdisplayCreateOfClass(
    vhelpdisplayClass	*helpdisplayClass
    );

vhelpdisplay *vhelpdisplayInitOfClass(
   vhelpdisplay		*helpdisplay,
   vhelpdisplayClass	*clas
   );

vobservable *vhelpdisplayGetObservable(
    vhelpdisplay	*helpdisplay
    );

/*
 * Class specific API.
 */

vbool vhelpdisplayDisplayHelp(
    vhelpdisplay	*helpdisplay,
    vhelprequest	*request
    );

void vhelpdisplayUndisplayHelp(
    vhelpdisplay	*helpdisplay,
    vhelprequest	*request
    );

void vhelpdisplayReference(
    vhelpdisplay	*helpdisplay
);

void vhelpdisplayUnreference(
    vhelpdisplay	*helpdisplay
);


/*
 * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * *
 */

struct vhelpdisplay {
    vobservable		observable;
    unsigned short	refCount;
};

#define vhelpdisplayCLASS(SUPER, HELPDIS)			        \
    vobservableCLASS(SUPER, HELPDIS);				        \
    vclassMETHOD_RET(vhelpdisplayDISPLAY_HELP, vbool,	      		\
		     (HELPDIS *helpdis, vhelprequest *request));	\
    vclassMETHOD(vhelpdisplayUNDISPLAY_HELP,				\
		     (HELPDIS *helpdis, vhelprequest *request))

struct vhelpdisplayClass {
    vhelpdisplayCLASS(vhelpdisplayClass, vhelpdisplay);
};

/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * *
 */
#define vhelpdisplayGetObservable(d)	vportBASE_OBJECT((d), observable)
#define vhelpdisplayGetClass(d)						\
    ((vhelpdisplayClass*)vobservableGetClass(vhelpdisplayGetObservable(d)))
#define vhelpdisplayCreateOfClass(c) 					\
    ((vhelpdisplay *)vobservableCreateOfClass((vhelpdisplayClass*)(c)))
#define vhelpdisplayInitOfClass(d, c) 					\
    (vhelpdisplay *)vobservableInitOfClass(vhelpdisplayGetObservable(d),\
					   (vobservableClass*)(c))
/*
 * * * * * * * * * * PRIVATE FUNCTION MESSAGE DEFINITIONS * * * * * * * * * *
 */

#define vhelpdisplayDisplayHelp(h, r)					\
    vclassSend(vhelpdisplayGetClass(h), vhelpdisplayDISPLAY_HELP, (h, r))
#define vhelpdisplayUndisplayHelp(h, r)					\
    vclassSend(vhelpdisplayGetClass(h), vhelpdisplayUNDISPLAY_HELP, (h, r))


vportEND_CPLUSPLUS_EXTERN_C

#endif /* vhelpdisplayINCLUDED */



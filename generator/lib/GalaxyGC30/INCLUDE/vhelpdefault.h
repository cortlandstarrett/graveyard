/* $Id: vhelpdefault.h,v 1.4 1997/11/06 19:39:50 robert Exp $ */

/* -----------------------------------------------------------------------
 *
 *  vhelpdefault.h
 *
 *  Programming interface to using the system default HTML browser as 
 *  a help display
 *
 *  (c) Copyright Visix Software
 *  All rights reserved
 *
 * -----------------------------------------------------------------------
 */

#ifndef vhelpdefaultINCLUDED
#define vhelpdefaultINCLUDED	1

#ifndef vportINCLUDED
#include <vport.h>
#endif

#ifndef  vhelphypertextINCLUDED
#include vhelphypertextHEADER
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * * * * * * * * * * PUBLIC TYPE DEFINITIONS * * * * * * * * * *
 */
typedef struct	vhelpdefault		vhelpdefault;
typedef struct	vhelpdefaultClass	vhelpdefaultClass;

/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */
/*
 * Creation/Destruction/Class Management
 */

void vhelpdefaultStartup(
    void
    );

vhelpdefaultClass *vhelpdefaultGetDefaultClass(
    void
    );

vhelpdefaultClass *vhelpdefaultGetClass(
    vhelpdefaultClass	*helpdisplayClass
    );

vhelpdefault *vhelpdefaultCreateOfClass(
    vhelpdefaultClass	*helpdisplayClass
    );

void vhelpdefaultInitOfClass(
   vhelpdefault		*helpdisplay,
   vhelpdefaultClass		*clas
   );

void vhelpdefaultInit(
    vhelpdefault		*helpdisplay
    );

void vhelpdefaultDestroy(
    vhelpdefault		*helpdisplay
    );

vhelpdefault *vhelpdefaultCreate(
    void
    );

vhelphypertext *vhelpdefaultGetHypertext(
    vhelpdefault		*helpdisplay
    );

vbool vhelpdefaultDisplayHelp(
    vhelpdefault		*helpdisplay,
    vhelprequest		*request
    );

void vhelpdefaultUndisplayHelp(
    vhelpdefault		*helpdisplay,
    vhelprequest		*request
    );

/*
 * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * *
 */
struct vhelpdefault {
    vhelphypertext		 hypertext;
    unsigned short		 flags;
};

#define vhelpdefaultCLASS(SUPER, HELPDIS)		        	      \
    vhelphypertextCLASS(SUPER, HELPDIS)

struct vhelpdefaultClass {
    vhelpdefaultCLASS(vhelpdefaultClass, vhelpdefault);
};

/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * *
 */
#define vhelpdefaultGetHypertext(d)	vportBASE_OBJECT((d), hypertext)
#define vhelpdefaultGetClass(d)					\
    ((vhelpdefaultClass*)						\
     vhelphypertextGetClass(vhelpdefaultGetHypertext(d)))
#define vhelpdefaultCreateOfClass(c) 					\
    ((vhelpdefault *)							\
     vhelphypertextCreateOfClass((vhelphypertextClass*)(c)))
#define vhelpdefaultCreate()						\
    vhelpdefaultCreateOfClass(vhelpdefaultGetDefaultClass())
#define vhelpdefaultInitOfClass(d, c) 					\
    vhelphypertextInitOfClass(vhelpdefaultGetHypertext(d),		\
			      (vhelphypertextClass*)(c))
#define vhelpdefaultInit(d)						\
    vhelpdefaultInitOfClass(d, vhelpdefaultGetDefaultClass())

#define vhelpdefaultDisplayHelp(d, r)				\
    vhelphypertextDisplayHelp(vhelpdefaultGetHypertext(d), r)
#define vhelpdefaultUndisplayHelp(d, r)				\
    vhelphypertextUndisplayHelp(vhelpdefaultGetHypertext(d), r)

/*
 * * * * * * * * * * PRIVATE FUNCTION MESSAGE DEFINITIONS * * * * * * * * * *
 */

vportEND_CPLUSPLUS_EXTERN_C

#endif /* vhelpdefaultINCLUDED */















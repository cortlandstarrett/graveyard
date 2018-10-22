/* $Id: vhelpexplorer.h,v 1.4 1997/11/06 19:39:50 robert Exp $ */

/* -----------------------------------------------------------------------
 *
 *  vhelpexplorer.h
 *
 *  Programming interface to using Internet Explorer as a help display.
 *
 *  (c) Copyright Visix Software
 *  All rights reserved
 *
 * -----------------------------------------------------------------------
 */

#ifndef vhelpexplorerINCLUDED
#define vhelpexplorerINCLUDED	1

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
typedef struct	vhelpexplorer		vhelpexplorer;
typedef struct	vhelpexplorerClass	vhelpexplorerClass;

/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */
/*
 * Creation/Destruction/Class Management
 */

void vhelpexplorerStartup(
    void
    );

vhelpexplorerClass *vhelpexplorerGetDefaultClass(
    void
    );

vhelpexplorerClass *vhelpexplorerGetClass(
    vhelpexplorerClass	*helpdisplayClass
    );

vhelpexplorer *vhelpexplorerCreateOfClass(
    vhelpexplorerClass	*helpdisplayClass
    );

void vhelpexplorerInitOfClass(
   vhelpexplorer		*helpdisplay,
   vhelpexplorerClass		*clas
   );

void vhelpexplorerInit(
    vhelpexplorer		*helpdisplay
    );

void vhelpexplorerDestroy(
    vhelpexplorer		*helpdisplay
    );

vhelpexplorer *vhelpexplorerCreate(
    void
    );

vhelphypertext *vhelpexplorerGetHypertext(
    vhelpexplorer		*helpdisplay
    );

vbool vhelpexplorerDisplayHelp(
    vhelpexplorer		*helpdisplay,
    vhelprequest		*request
    );

void vhelpexplorerUndisplayHelp(
    vhelpexplorer		*helpdisplay,
    vhelprequest		*request
    );

/*
 * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * *
 */
struct vhelpexplorer {
    vhelphypertext		 hypertext;
    unsigned short		 flags;
};

#define vhelpexplorerCLASS(SUPER, HELPDIS)		        	      \
    vhelphypertextCLASS(SUPER, HELPDIS)

struct vhelpexplorerClass {
    vhelpexplorerCLASS(vhelpexplorerClass, vhelpexplorer);
};

/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * *
 */
#define vhelpexplorerGetHypertext(d)	vportBASE_OBJECT((d), hypertext)
#define vhelpexplorerGetClass(d)					\
    ((vhelpexplorerClass*)						\
     vhelphypertextGetClass(vhelpexplorerGetHypertext(d)))
#define vhelpexplorerCreateOfClass(c) 					\
    ((vhelpexplorer *)							\
     vhelphypertextCreateOfClass((vhelphypertextClass*)(c)))
#define vhelpexplorerCreate()						\
    vhelpexplorerCreateOfClass(vhelpexplorerGetDefaultClass())
#define vhelpexplorerInitOfClass(d, c) 					\
    vhelphypertextInitOfClass(vhelpexplorerGetHypertext(d),		\
			      (vhelphypertextClass*)(c))
#define vhelpexplorerInit(d)						\
    vhelpexplorerInitOfClass(d, vhelpexplorerGetDefaultClass())

#define vhelpexplorerDisplayHelp(d, r)					\
    vhelphypertextDisplayHelp(vhelpexplorerGetHypertext(d), r)
#define vhelpexplorerUndisplayHelp(d, r)				\
    vhelphypertextUndisplayHelp(vhelpexplorerGetHypertext(d), r)

/*
 * * * * * * * * * * PRIVATE FUNCTION MESSAGE DEFINITIONS * * * * * * * * * *
 */

vportEND_CPLUSPLUS_EXTERN_C

#endif /* vhelpexplorerINCLUDED */















/* $Id: vhelpnetscape.h,v 1.11 1997/11/06 19:39:50 robert Exp $ */

/* -----------------------------------------------------------------------
 *
 *  vhelpnetscape.h
 *
 *  Programming interface to using Netscape as a help display
 *
 *  (c) Copyright Visix Software
 *  All rights reserved
 *
 * -----------------------------------------------------------------------
 */

#ifndef vhelpnetscapeINCLUDED
#define vhelpnetscapeINCLUDED	1

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
typedef struct	vhelpnetscape		vhelpnetscape;
typedef struct	vhelpnetscapeClass	vhelpnetscapeClass;

/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */
/*
 * Creation/Destruction/Class Management
 */

void vhelpnetscapeStartup(
    void
    );

vhelpnetscapeClass *vhelpnetscapeGetDefaultClass(
    void
    );

vhelpnetscapeClass *vhelpnetscapeGetClass(
    vhelpnetscapeClass	*helpdisplayClass
    );

vhelpnetscape *vhelpnetscapeCreateOfClass(
    vhelpnetscapeClass	*helpdisplayClass
    );

void vhelpnetscapeInitOfClass(
   vhelpnetscape		*helpdisplay,
   vhelpnetscapeClass		*clas
   );

void vhelpnetscapeInit(
    vhelpnetscape		*helpdisplay
    );

void vhelpnetscapeDestroy(
    vhelpnetscape		*helpdisplay
    );

vhelpnetscape *vhelpnetscapeCreate(
    void
    );

vhelphypertext *vhelpnetscapeGetHypertext(
    vhelpnetscape		*helpdisplay
    );

vbool vhelpnetscapeDisplayHelp(
    vhelpnetscape		*helpdisplay,
    vhelprequest		*request
    );

void vhelpnetscapeUndisplayHelp(
    vhelpnetscape		*helpdisplay,
    vhelprequest		*request
    );

/*
 * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * *
 */
struct vhelpnetscape {
    vhelphypertext		 hypertext;
    unsigned short		 flags;
};

#define vhelpnetscapeCLASS(SUPER, HELPDIS)		        	      \
    vhelphypertextCLASS(SUPER, HELPDIS)

struct vhelpnetscapeClass {
    vhelpnetscapeCLASS(vhelpnetscapeClass, vhelpnetscape);
};

/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * *
 */
#define vhelpnetscapeGetHypertext(d)	vportBASE_OBJECT((d), hypertext)
#define vhelpnetscapeGetClass(d)					\
    ((vhelpnetscapeClass*)						\
     vhelphypertextGetClass(vhelpnetscapeGetHypertext(d)))
#define vhelpnetscapeCreateOfClass(c) 					\
    ((vhelpnetscape *)							\
     vhelphypertextCreateOfClass((vhelphypertextClass*)(c)))
#define vhelpnetscapeCreate()						\
    vhelpnetscapeCreateOfClass(vhelpnetscapeGetDefaultClass())
#define vhelpnetscapeInitOfClass(d, c) 					\
    vhelphypertextInitOfClass(vhelpnetscapeGetHypertext(d),		\
			      (vhelphypertextClass*)(c))
#define vhelpnetscapeInit(d)						\
    vhelpnetscapeInitOfClass(d, vhelpnetscapeGetDefaultClass())

#define vhelpnetscapeDisplayHelp(d, r)				\
    vhelphypertextDisplayHelp(vhelpnetscapeGetHypertext(d), r, i)
#define vhelpnetscapeUndisplayHelp(d, r)				\
    vhelphypertextUndisplayHelp(vhelpnetscapeGetHypertext(d), r)

/*
 * * * * * * * * * * PRIVATE FUNCTION MESSAGE DEFINITIONS * * * * * * * * * *
 */

vportEND_CPLUSPLUS_EXTERN_C

#endif /* vhelpnetscapeINCLUDED */















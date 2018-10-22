/* $Id: vhelptooltip.h,v 1.4 1997/09/11 22:59:08 robert Exp $ */

/* -----------------------------------------------------------------------
 *
 *  vhelptooltip.h
 *
 *  Programming interface to the vhelptooltip class
 *
 *  (c) Copyright Visix Software
 *  All rights reserved
 *
 * -----------------------------------------------------------------------
 */

#ifndef vhelptooltipINCLUDED
#define vhelptooltipINCLUDED	1

#ifndef vportINCLUDED
#include <vport.h>
#endif

#ifndef  vhelpdisplayINCLUDED
#include vhelpdisplayHEADER
#endif

#ifndef  vtooltipINCLUDED
#include vtooltipHEADER
#endif


vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * * * * * * * * * * PUBLIC TYPE DEFINITIONS * * * * * * * * * *
 */

typedef struct	vhelptooltip		vhelptooltip;
typedef struct	vhelptooltipClass	vhelptooltipClass;

/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */

/*
 * Creation/Destruction/Class Management
 */
void vhelptooltipStartup(
    void
    );

vhelptooltipClass *vhelptooltipGetDefaultClass(
    void
    );

vhelptooltip *vhelptooltipCreateOfClass(
    vhelptooltipClass	*clas
    );

vhelptooltipClass *vhelptooltipGetClass(
    vhelptooltip		*helpdisplay
    );

vhelptooltip *vhelptooltipCreate(
    void
    );

void vhelptooltipInitOfClass(
    vhelptooltip		*helpdisplay,
    vhelptooltipClass	*clas
    );

void vhelptooltipInit(
    vhelptooltip		*helpdisplay
    );

void vhelptooltipDestroy(
    vhelptooltip		*helpdisplay
    );

vhelpdisplay *vhelptooltipGetDisplay(
    vhelptooltip		*helpdisplay
    );

/*
 * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * *
 */

struct vhelptooltip {
    vhelpdisplay	 display;
    vwindow		*window;
};

#define vhelptooltipCLASS(SUPER, HELPDIS)		        	\
    vhelpdisplayCLASS(SUPER, HELPDIS)

struct vhelptooltipClass {
    vhelptooltipCLASS(vhelptooltipClass, vhelptooltip);
};

/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * *
 */
#define vhelptooltipGetDisplay(d)     vportBASE_OBJECT((d), display)
#define vhelptooltipGetClass(d)						\
    ((vhelptooltipClass*)						\
     vhelpdisplayGetClass(vhelptooltipGet(d)))
#define vhelptooltipCreateOfClass(c) 					\
    ((vhelptooltip *)							\
     vhelpdisplayCreateOfClass((vhelptooltipClass*)(c)))
#define vhelptooltipCreate()						\
    vhelptooltipCreateOfClass(vhelptooltipGetDefaultClass())
#define vhelptooltipInitOfClass(d, c) 					\
      vhelpdisplayInitOfClass(vhelptooltipGetDisplay(d),		\
			      (vhelpdisplayClass*)(c))
#define vhelptooltipInit(d) 						\
      vhelptooltipInitOfClass((d), vhelptooltipGetDefaultClass())

/*
 * * * * * * * * * * PRIVATE FUNCTION MESSAGE DEFINITIONS * * * * * * * * * *
 */

vportEND_CPLUSPLUS_EXTERN_C

#endif /* vhelptooltipINCLUDED */

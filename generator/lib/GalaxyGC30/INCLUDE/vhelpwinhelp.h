/* $Id: vhelpwinhelp.h,v 1.5 1997/11/06 19:39:50 robert Exp $ */

/* -----------------------------------------------------------------------
 *
 *  vhelpwinhelp.h
 *
 *  Programming interface to using WinHelp as a help display
 *
 *  (c) Copyright Visix Software
 *  All rights reserved
 *
 * -----------------------------------------------------------------------
 */

#ifndef vhelpwinhelpINCLUDED
#define vhelpwinhelpINCLUDED	1

#ifndef vportINCLUDED
#include <vport.h>
#endif

#ifndef vhelpINCLUDED
#include vhelpHEADER
#endif

#ifndef  vhelphypertextINCLUDED
#include vhelphypertextHEADER
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * * * * * * * * * * PUBLIC TYPE DEFINITIONS * * * * * * * * * *
 */
typedef struct	vhelpwinhelp		vhelpwinhelp;
typedef struct	vhelpwinhelpClass	vhelpwinhelpClass;

/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */
/*
 * Creation/Destruction/Class Management
 */

void vhelpwinhelpStartup(
    void
    );

vhelpwinhelpClass *vhelpwinhelpGetDefaultClass(
    void
    );

vhelpwinhelpClass *vhelpwinhelpGetClass(
    vhelpwinhelpClass	*helpdisplayClass
    );

vhelpwinhelp *vhelpwinhelpCreateOfClass(
    vhelpwinhelpClass	*helpdisplayClass
    );

void vhelpwinhelpInitOfClass(
   vhelpwinhelp		*helpdisplay,
   vhelpwinhelpClass	*clas
   );

void vhelpwinhelpInit(
    vhelpwinhelp		*helpdisplay
    );

void vhelpwinhelpDestroy(
    vhelpwinhelp		*helpdisplay
    );

vhelpwinhelp *vhelpwinhelpCreate(
    void
    );

vhelphypertext *vhelpwinhelpGetHypertext(
    vhelpwinhelp		*helpdisplay
    );

vbool vhelpwinhelpDisplayHelp(
    vhelpwinhelp		*helpdisplay,
    vhelprequest	*request,
    vinstance		*helpData
    );

void vhelpwinhelpUndisplayHelp(
    vhelpwinhelp		*helpdisplay,
    vhelprequest	*request
    );

/*
 * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * *
 */
struct vhelpwinhelp {
    vhelphypertext		 hypertext;
    vhelpWindow			*helpWindow;
    unsigned short		 flags;
};

#define vhelpwinhelpCLASS(SUPER, HELPDIS)		        	      \
    vhelphypertextCLASS(SUPER, HELPDIS)

struct vhelpwinhelpClass {
    vhelpwinhelpCLASS(vhelpwinhelpClass, vhelpwinhelp);
};

/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * *
 */
#define vhelpwinhelpGetHypertext(d)	vportBASE_OBJECT((d), hypertext)
#define vhelpwinhelpGetClass(d)					        \
    ((vhelpwinhelpClass*)						\
     vhelphypertextGetClass(vhelpwinhelpGetHypertext(d)))
#define vhelpwinhelpCreateOfClass(c) 					\
    ((vhelpwinhelp *)							\
     vhelphypertextCreateOfClass((vhelphypertextClass*)(c)))
#define vhelpwinhelpCreate()						\
    vhelpwinhelpCreateOfClass(vhelpwinhelpGetDefaultClass())
#define vhelpwinhelpInitOfClass(d, c) 					\
    vhelphypertextInitOfClass(vhelpwinhelpGetHypertext(d),		\
			      (vhelphypertextClass*)(c))
#define vhelpwinhelpInit(d)						\
    vhelpwinhelpInitOfClass(d, vhelpwinhelpGetDefaultClass())

#define vhelpwinhelpDisplayHelp(d, r, i)				\
    vhelphypertextDisplayHelp(vhelpwinhelpGetHypertext(d), r, i);
#define vhelpwinhelpUndisplayHelp(d, r)				        \
    vhelphypertextUndisplayHelp(vhelpwinhelpGetHypertext(d), r);

/*
 * * * * * * * * * * PRIVATE FUNCTION MESSAGE DEFINITIONS * * * * * * * * * *
 */

vportEND_CPLUSPLUS_EXTERN_C

#endif /* vhelpwinhelpINCLUDED */















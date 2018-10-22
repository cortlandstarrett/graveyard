/* $Id: vhelpgalaxy.h,v 1.8 1997/09/23 20:24:38 shawn Exp $ */

/* -----------------------------------------------------------------------
 *
 *  vhelpgalaxy.h
 *
 *  Programming interface to using the Galaxy Help Server as a help display
 *
 *  (c) Copyright Visix Software
 *  All rights reserved
 *
 * -----------------------------------------------------------------------
 */

#ifndef vhelpgalaxyINCLUDED
#define vhelpgalaxyINCLUDED	1

#ifndef  vportINCLUDED
#include <vport.h>
#endif

#ifndef  vhelpINCLUDED
#include vhelpHEADER
#endif

#ifndef  vhelphypertextINCLUDED
#include vhelphypertextHEADER
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * * * * * * * * * * PUBLIC TYPE DEFINITIONS * * * * * * * * * *
 */
typedef struct	vhelpgalaxy		vhelpgalaxy;
typedef struct	vhelpgalaxyClass	vhelpgalaxyClass;

typedef struct 	vhelpGalaxyWindow	vhelpGalaxyWindow;

/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */
void vhelpgalaxyStartup(
    void
    );

void vhelpgalaxyStartupGalaxy(
    void
    );

vhelpgalaxyClass *vhelpgalaxyGetDefaultClass(
    void
    );

vhelpgalaxyClass *vhelpgalaxyGetClass(
    vhelpgalaxyClass	*helpdisplayClass
    );

vhelpgalaxy *vhelpgalaxyCreateOfClass(
    vhelpgalaxyClass	*helpdisplayClass
    );

void vhelpgalaxyInitOfClass(
   vhelpgalaxy		*helpdisplay,
   vhelpgalaxyClass	*clas
   );

void vhelpgalaxyInit(
    vhelpgalaxy		*helpdisplay
    );

void vhelpgalaxyDestroy(
    vhelpgalaxy		*helpdisplay
    );

vhelpgalaxy *vhelpgalaxyCreate(
    void
    );

vhelphypertext *vhelpgalaxyGetHypertext(
    vhelpgalaxy		*helpdisplay
    );

vbool vhelpgalaxyDisplayHelp(
    vhelpgalaxy		*helpdisplay,
    vhelprequest	*request,
    vinstance		*helpData
    );

void vhelpgalaxyUndisplayHelp(
    vhelpgalaxy		*helpdisplay,
    vhelprequest	*request
    );

/*
 * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * *
 */
struct vhelpGalaxyWindow {
    vhelpWindow		 win;
    int			 winId;
    unsigned int	 flags;
};

struct vhelpgalaxy {
    vhelphypertext		 hypertext;
    vhelpWindow			*helpWindow;
    unsigned short		 flags;
};

#define vhelpgalaxyCLASS(SUPER, HELPDIS)		        	      \
    vhelphypertextCLASS(SUPER, HELPDIS)

struct vhelpgalaxyClass {
    vhelpgalaxyCLASS(vhelpgalaxyClass, vhelpgalaxy);
};

/*
 * * * * * * * * * * PRIVATE FUNCTION PROTOTYPES * * * * * * * * * *
 */
vhelpWindowClass *_vhelpGalaxyStarter(void);

/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * *
 */
#define vhelpgalaxyGetHypertext(d)	vportBASE_OBJECT((d), hypertext)
#define vhelpgalaxyGetClass(d)					        \
    ((vhelpgalaxyClass*)						\
     vhelphypertextGetClass(vhelpgalaxyGetHypertext(d)))
#define vhelpgalaxyCreateOfClass(c) 					\
    ((vhelpgalaxy *)							\
     vhelphypertextCreateOfClass((vhelphypertextClass*)(c)))
#define vhelpgalaxyCreate()						\
    vhelpgalaxyCreateOfClass(vhelpgalaxyGetDefaultClass())
#define vhelpgalaxyInitOfClass(d, c) 					\
    vhelphypertextInitOfClass(vhelpgalaxyGetHypertext(d),		\
			      (vhelphypertextClass*)(c))
#define vhelpgalaxyInit(d)						\
    vhelpgalaxyInitOfClass(d, vhelpgalaxyGetDefaultClass())

#define vhelpgalaxyDisplayHelp(d, r, i)				\
    vhelphypertextDisplayHelp(vhelpgalaxyGetHypertext(d), r, i);
#define vhelpgalaxyUndisplayHelp(d, r)				        \
    vhelphypertextUndisplayHelp(vhelpgalaxyGetHypertext(d), r);

/*
 * * * * * * * * * * PRIVATE FUNCTION MESSAGE DEFINITIONS * * * * * * * * * *
 */

vportEND_CPLUSPLUS_EXTERN_C

#if (vportUSE_LIB_PRAGMAS && !defined(vhgLIB_MEMBER))
# ifdef vportGALAXY_LIB_SUFFIX
#  pragma comment(lib, "vhg" vportGALAXY_LIB_SUFFIX ".lib")
# else
#  if (vportCPLUSPLUS_SOURCE)
#   if (vportI18N)
#    if (vdebugDEBUG)
#     ifdef _RTLDLL
#      pragma comment(lib, "vhgp.lib")
#     else
#      pragma comment(lib, "vhgps.lib")
#     endif /* (_RTLDLL) */
#    else
#     ifdef _RTLDLL
#      pragma comment(lib, "vhgo.lib")
#     else
#      pragma comment(lib, "vhgos.lib")
#     endif /* (_RTLDLL) */
#    endif /* (vdebugDEBUG) */
#   else
#    if (vdebugDEBUG)
#     ifdef _RTLDLL
#      pragma comment(lib, "vhgn.lib")
#     else
#      pragma comment(lib, "vhgns.lib")
#     endif /* (_RTLDLL) */
#    else
#     ifdef _RTLDLL
#      pragma comment(lib, "vhgm.lib")
#     else
#      pragma comment(lib, "vhgms.lib")
#     endif /* (_RTLDLL) */
#    endif /* (vdebugDEBUG) */
#   endif /* (vportI18N) */
#  else
#   if (vportI18N)
#    if (vdebugDEBUG)
#     ifdef _RTLDLL
#      pragma comment(lib, "vhgl.lib")
#     else
#      pragma comment(lib, "vhgls.lib")
#     endif /* (_RTLDLL) */
#    else
#     ifdef _RTLDLL
#      pragma comment(lib, "vhgk.lib")
#     else
#      pragma comment(lib, "vhgks.lib")
#     endif /* (_RTLDLL) */
#    endif /* (vdebugDEBUG) */
#   else
#    if (vdebugDEBUG)
#     ifdef _RTLDLL
#      pragma comment(lib, "vhgj.lib")
#     else
#      pragma comment(lib, "vhgjs.lib")
#     endif /* (_RTLDLL) */
#    else
#     ifdef _RTLDLL
#      pragma comment(lib, "vhgi.lib")
#     else
#      pragma comment(lib, "vhgis.lib")
#     endif /* (_RTLDLL) */
#    endif /* (vdebugDEBUG) */
#   endif /* (vportI18N) */
#  endif /* (vportCPLUSPLUS_SOURCE) */
# endif /* defined vportGALAXY_LIB_SUFFIX */
#endif /* vportUSE_LIB_PRAGMAS && !defined(vhgLIB_MEMBER) */

#endif /* vhelpgalaxyINCLUDED */

/* $Id: vdockcont.h,v 1.3 1997/07/21 23:55:23 robert Exp $ */

/************************************************************

    vdockcont.h

    C Interface file for vdockcontainer

    (c) Copyright Visix Software Inc.
    All rights reserved

************************************************************/

#ifndef vdockcontINCLUDED
#define vdockcontainerINCLUDED 1
#define vdockcontINCLUDED 1

#ifndef  vportINCLUDED
#include <vport.h>
#endif

#ifndef  vresourceINCLUDED
#include vresourceHEADER
#endif

#ifndef  vclassINCLUDED
#include vclassHEADER
#endif

#ifndef  vcontainerINCLUDED
#include vcontainerHEADER
#endif

#ifndef  vdockINCLUDED
#include vdockHEADER
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C


/*
 * * * * * * * * * * PUBLIC CONSTANT DEFINITIONS * * * * * * * * * *
 */

enum {
    vdockcontainerID_ATTRIBUTE_DOCK_LEFT	= vcontainerNEXT_ID_ATTRIBUTE,
    vdockcontainerID_ATTRIBUTE_DOCK_RIGHT,
    vdockcontainerID_ATTRIBUTE_DOCK_BOTTOM,
    vdockcontainerID_ATTRIBUTE_DOCK_TOP,
    vdockcontainerID_ATTRIBUTE_EMPTY_PADDING,
    vdockcontainerNEXT_ID_ATTRIBUTE
};

enum {
    vdockcontainerNEXT_SELECT		= vcontainerNEXT_SELECT
};

enum {
    vdockcontainerDOCK_LEFT		= 0,
    vdockcontainerDOCK_RIGHT,
    vdockcontainerDOCK_BOTTOM,
    vdockcontainerDOCK_TOP
};


/*
 * * * * * * * * * * PUBLIC TYPE DEFINITIONS * * * * * * * * * *
 */

typedef struct vdockcontainer		vdockcontainer;
typedef struct vdockcontainerClass	vdockcontainerClass;


/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */

void vdockcontainerStartup(
    void
    );

vdockcontainerClass *vdockcontainerGetDefaultClass(
    void
    );

vdockcontainer *vdockcontainerCreateOfClass(
    vdockcontainerClass			*clas
    );

vdockcontainer *vdockcontainerCreate(
    void
    );

void vdockcontainerInitOfClass(
    vdockcontainer			*dockcont,
    vdockcontainerClass			*clas
    );

void vdockcontainerInit(
    vdockcontainer			*dockcont
    );

void vdockcontainerDestroy(
    vdockcontainer			*dockcont
    );

vdockcontainer *vdockcontainerClone(
    vdockcontainer			*dockcont
    );

void vdockcontainerCopyInit(
    vdockcontainer			*dockcont,
    vdockcontainer			*target
    );

void vdockcontainerCopy(
    vdockcontainer			*dockcont,
    vdockcontainer			*target
    );

vdockcontainer *vdockcontainerLoad(
    vresource				 resource
    );

void vdockcontainerLoadInit(
    vdockcontainer			*dockcont,
    vresource				 resource
    );

void vdockcontainerStore(
    vdockcontainer			*dockcont,
    vresource				 resource
    );

void vdockcontainerSetDock(
    vdockcontainer			*dockcont,
    int					 whichDock,
    vbool				 onOff
    );

void vdockcontainerSetEmptyPadding(
    vdockcontainer			*dockcont,
    short				 padding
    );

vcontainer *vdockcontainerGetContainer(
    vdockcontainer			*dockcont
    );

vdialogItem *vdockcontainerGetItem(
    vdockcontainer			*dockcont
    );

vobjectAttributed *vdockcontainerGetObject(
    vdockcontainer			*dockcont
    );

vdockcontainerClass *vdockcontainerGetClass(
    vdockcontainer			*dockcont
    );

vbool vdockcontainerHasDock(
    vdockcontainer			*dockcont,
    int					 whichDock
    );

vdock *vdockcontainerGetDock(
    vdockcontainer			*dockcont,
    int					 whichDock
    );

short vdockcontainerGetEmptyPadding(
    vdockcontainer			*dockcont
    );


/*
 * * * * * * * * * * PRIVATE CONSTANT DEFINITIONS * * * * * * * * * *
 */


/*
 * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * *
 */

struct vdockcontainer {
    vcontainer				 container;
    short				 padding;
};

#define vdockcontainerCLASS(SUPER, DOCKCONT, NOTIFY)			      \
    vcontainerCLASS(SUPER, DOCKCONT, NOTIFY);				      \
    vclassMETHOD(vdockcontainerSET_DOCK, (DOCKCONT *, int dock, vbool offOn));\
    vclassMETHOD(vdockcontainerSET_EMPTY_PADDING, (DOCKCONT *, short padding))

struct vdockcontainerClass {
    vdockcontainerCLASS(vdockcontainerClass, vdockcontainer,
			vcontainerNoteProc);
};


/*
 * * * * * * * * * * PRIVATE FUNCTION PROTOTYPES * * * * * * * * * *
 */


/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * *
 */

#define vdockcontainerGetContainer(d)					      \
	vportBASE_OBJECT(d, container)
#define vdockcontainerGetItem(d)					      \
	vcontainerGetItem(vdockcontainerGetContainer(d))
#define vdockcontainerGetObject(d)					      \
	vcontainerGetObject(vdockcontainerGetContainer(d))

#define vdockcontainerCreateOfClass(c)					      \
	((vdockcontainer *) vcontainerCreateOfClass((vcontainerClass *) (c)))
#define vdockcontainerCreate()						      \
	vdockcontainerCreateOfClass(vdockcontainerGetDefaultClass())
#define vdockcontainerInitOfClass(d, c)					      \
	vcontainerInitOfClass(vdockcontainerGetContainer(d),		      \
			      (vcontainerClass *) (c))
#define vdockcontainerInit(d)						      \
	vdockcontainerInitOfClass(d, vdockcontainerGetDefaultClass())
#define vdockcontainerDestroy(d)					      \
	vcontainerDestroy(vdockcontainerGetContainer(d))
#define vdockcontainerClone(d)						      \
	((vdockcontainer *) vcontainerClone(vdockcontainerGetContainer(d)))
#define vdockcontainerCopyInit(d, t)					      \
	vcontainerCopyInit(vdockcontainerGetContainer(d),		      \
			   vdockcontainerGetContainer(t))
#define vdockcontainerCopy(d, t)					      \
	vcontainerCopy(vdockcontainerGetContainer(d),			      \
		       vdockcontainerGetContainer(t))
#define vdockcontainerLoad(r)						      \
	((vdockcontainer *) vcontainerLoad(r))
#define vdockcontainerLoadInit(d, r)					      \
	vcontainerLoadInit(vdockcontainerGetContainer(d), r)
#define vdockcontainerStore(d, r)					      \
	vcontainerStore(vdockcontainerGetContainer(d), r)
#define vdockcontainerGetClass(d)					      \
	((vdockcontainerClass *)					      \
	 vcontainerGetClass(vdockcontainerGetContainer(d)))
#define vdockcontainerGetEmptyPadding(d)				      \
	((d)->padding)


/*
 * * * * * * * * * * PRIVATE FUNCTION MESSAGE DEFINITIONS * * * * * * * * * *
 */

#define vdockcontainerSetDock(d, o, b)					      \
	vclassSend(vdockcontainerGetClass(d), vdockcontainerSET_DOCK,	      \
		   (d, o, b))
#define vdockcontainerSetEmptyPadding(d, p)				      \
	vclassSend(vdockcontainerGetClass(d), vdockcontainerSET_EMPTY_PADDING,\
		   (d, p))


/*
 * Formatting information for emacs in c-mode and cc-mode
 *
 * Local Variables:
 * c-indent-level:			 4
 * c-continued-statement-offset:	 4
 * c-label-offset:			-4
 * c-file-style:			"BSD"
 * c-file-offsets:			((block-open . -))
 * End:
 */

vportEND_CPLUSPLUS_EXTERN_C

#endif /* #ifndef vdockcontINCLUDED */

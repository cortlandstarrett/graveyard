/* $Id: vdock.h,v 1.6 1997/04/18 21:05:49 robert Exp $ */

/************************************************************

    vdock.h

    C Interface file for Docks

    (c) Copyright Visix Software Inc.
    All rights reserved

************************************************************/

#ifndef  vdockINCLUDED
#define  vdockINCLUDED 1

#ifndef  vportINCLUDED
#include <vport.h>
#endif

#ifndef  vrectINCLUDED
#include vrectHEADER
#endif

#ifndef  vnameINCLUDED
#include vnameHEADER
#endif

#ifndef  vclassINCLUDED
#include vclassHEADER
#endif

#ifndef  vwindowINCLUDED
#include vwindowHEADER
#endif

#ifndef  vdialogINCLUDED
#include vdialogHEADER
#endif

#ifndef  vdropINCLUDED
#include vdropHEADER
#endif

#ifndef  vdockerINCLUDED
#include vdockerHEADER
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C


/*
 * * * * * * * * * * PUBLIC CONSTANT DEFINITIONS * * * * * * * * * *
 */


/*
 * * * * * * * * * * PUBLIC TYPE DEFINITIONS * * * * * * * * * *
 */

typedef struct vdockClass		 vdockClass;

#ifndef  _vdockDEFINED_VDOCK
typedef struct vdock			 vdock;
#define  _vdockDEFINED_VDOCK (1) /** circular dependency **/
#endif


/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */

void vdockStartup(
    void
    );

vdockClass *vdockGetDefaultClass(
    void
    );

vdock *vdockCreateOfClass(
    vdockClass				*clas
    );

vdock *vdockCreate(
    void
    );

void vdockInitOfClass(
    vdock				*dock,
    vdockClass				*clas
    );

void vdockInit(
    vdock				*dock
    );

void vdockDestroy(
    vdock				*dock
    );

vdock *vdockClone(
    vdock				*dock
    );

void vdockCopyInit(
    vdock				*dock,
    vdock				*target
    );

void vdockCopy(
    vdock				*dock,
    vdock				*target
    );

void vdockSetTag(
    vdock				*dock,
    const vname				*tag
    );

void vdockSetData(
    vdock				*dock,
    const void				*data
    );

void vdockSetRect(
    vdock				*dock,
    const vrect				*rect
    );

void vdockSetWindow(
    vdock				*dock,
    vwindow				*window
    );

void vdockSetOwner(
    vdock				*dock,
    vdialogItem				*owner
    );

vdropsite *vdockGetDropsite(
    vdock				*dock
    );

vloadable *vdockGetLoadable(
    vdock				*dock
    );

vinstance *vdockGetInstance(
    vdock				*dock
    );

vdockClass *vdockGetClass(
    vdock				*dock
    );

const vname *vdockGetTag(
    vdock				*dock
    );

const void *vdockGetData(
    vdock				*dock
    );

const vrect *vdockGetRect(
    vdock				*dock
    );

vwindow *vdockGetWindow(
    vdock				*dock
    );

vdialogItem *vdockGetOwner(
    vdock				*dock
    );

void vdockAddDocker(
    vdock				*dock,
    vdocker				*docker,
    const vrect				*rect
    );

void vdockRemoveDocker(
    vdock				*dock,
    vdocker				*docker
    );

int vdockGetDockerCount(
    vdock				*dock
    );

vdocker *vdockFindDocker(
    vdock				*dock,
    const vname				*tag
    );

/* vdockDragEngineClass */

vdragEngineClass *vdockGetDragEngineClass(
    void
    );


/*
 * * * * * * * * * * PRIVATE CONSTANT DEFINITIONS * * * * * * * * * *
 */


/*
 * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * *
 */

struct vdock {
    vdropsite				 drop;
    vdialogItem				*owner;
};

#define vdockCLASS(SUPER, DOCK, NOTIFY, DOCKER)				      \
    vdropsiteCLASS(SUPER, DOCK, NOTIFY);				      \
    vclassVARIABLE(vdockDRAG_ENGINE, vdragEngine *);                          \
    vclassMETHOD(vdockSET_OWNER, (DOCK *dock, vdialogItem *owner));	      \
    vclassMETHOD(vdockADD_DOCKER,					      \
		 (DOCK *dock, DOCKER *docker, const vrect *rect));	      \
    vclassMETHOD(vdockREMOVE_DOCKER, (DOCK *dock, DOCKER *docker));	      \
    vclassMETHOD_RET(vdockGET_DOCKER_COUNT, int, (DOCK *dock));		      \
    vclassMETHOD_RET(vdockFIND_DOCKER, DOCKER *,			      \
		     (DOCK *dock, const vname *tag))

struct vdockClass {
    vdockCLASS(vdockClass, vdock, vdropsiteNoteProc, vdocker);
};


/*
 * * * * * * * * * * PRIVATE FUNCTION PROTOTYPES * * * * * * * * * *
 */


/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * *
 */

#define vdockGetDropsite(d)						      \
	vportBASE_OBJECT(d, drop)
#define vdockGetLoadable(d)						      \
	vdropsiteGetLoadable(vdockGetDropsite(d))
#define vdockGetInstance(d)						      \
	vdropsiteGetInstance(vdockGetDropsite(d))

#define vdockCreateOfClass(c)						      \
	((vdock *) vdropsiteCreateOfClass((vdropsiteClass *) (c)))
#define vdockCreate()							      \
	vdockCreateOfClass(vdockGetDefaultClass())
#define vdockInitOfClass(d, c)						      \
	vdropsiteInitOfClass(vdockGetDropsite(d), (vdropsiteClass *) (c))
#define vdockInit(d)							      \
	vdockInitOfClass(d, vdockGetDefaultClass())
#define vdockDestroy(d)							      \
	vdropsiteDestroy(vdockGetDropsite(d))
#define vdockClone(d)							      \
	((vdock *) vdropsiteClone(vdockGetDropsite(d)))
#define vdockCopyInit(d, t)						      \
	vdropsiteCopyInit(vdockGetDropsite(d), vdockGetDropsite(t))
#define vdockCopy(d, t)							      \
	vdropsiteCopy(vdockGetDropsite(d), vdockGetDropsite(t))
#define vdockSetTag(d, t)						      \
	vdropsiteSetTag(vdockGetDropsite(d), t)
#define vdockSetData(d, a)						      \
	vdropsiteSetData(vdockGetDropsite(d), a)
#define vdockSetRect(d, r)						      \
	vdropsiteSetRect(vdockGetDropsite(d), r)
#define vdockSetWindow(d, w)						      \
	vdropsiteSetWindow(vdockGetDropsite(d), w)
#define vdockGetClass(d)						      \
	((vdockClass *) vdropsiteGetClass(vdockGetDropsite(d)))
#define vdockGetTag(d)							      \
	vdropsiteGetTag(vdockGetDropsite(d))
#define vdockGetData(d)							      \
	vdropsiteGetData(vdockGetDropsite(d))
#define vdockGetRect(d)							      \
	vdropsiteGetRect(vdockGetDropsite(d))
#define vdockGetWindow(d)						      \
	vdropsiteGetWindow(vdockGetDropsite(d))
#define vdockGetOwner(d)						      \
	((d)->owner)


/*
 * * * * * * * * * * PRIVATE FUNCTION MESSAGE DEFINITIONS * * * * * * * * * *
 */

#define vdockSetOwner(d, o)						      \
	vclassSend(vdockGetClass(d), vdockSET_OWNER, (d, o))
#define vdockAddDocker(d, o, r)						      \
	vclassSend(vdockGetClass(d), vdockADD_DOCKER, (d, o, r))
#define vdockRemoveDocker(d, o)						      \
	vclassSend(vdockGetClass(d), vdockREMOVE_DOCKER, (d, o))
#define vdockGetDockerCount(d)						      \
	vclassSend(vdockGetClass(d), vdockGET_DOCKER_COUNT, (d))
#define vdockFindDocker(d, t)						      \
	vclassSend(vdockGetClass(d), vdockFIND_DOCKER, (d, t))


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

#endif /* #ifndef vdockINCLUDED */

/* $Id: vdocker.h,v 1.17 1997/10/08 23:28:43 bill Exp $ */

/************************************************************

    vdocker.h

    C Interface file for Dockable Items

    (c) Copyright Visix Software Inc.
    All rights reserved

************************************************************/

#ifndef  vdockerINCLUDED
#define  vdockerINCLUDED 1

#ifndef  vportINCLUDED
#include <vport.h>
#endif

#ifndef  vrectINCLUDED
#include vrectHEADER
#endif

#ifndef  vnameINCLUDED
#include vnameHEADER
#endif

#ifndef  veventINCLUDED
#include veventHEADER
#endif

#ifndef  vresourceINCLUDED
#include vresourceHEADER
#endif

#ifndef  vclassINCLUDED
#include vclassHEADER
#endif

#ifndef  voccurrenceINCLUDED
#include voccurrenceHEADER
#endif

#ifndef  vwindowINCLUDED
#include vwindowHEADER
#endif

#ifndef  vdialogINCLUDED
#include vdialogHEADER
#endif

#ifndef  vcontainerINCLUDED
#include vcontainerHEADER
#endif

#ifndef  vdragINCLUDED
#include vdragHEADER
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C


/*
 * * * * * * * * * * PUBLIC CONSTANT DEFINITIONS * * * * * * * * * *
 */

enum {
    vdockerSPAN_NONE			 = 0x0000,
    vdockerSPAN_X_WHEN_HORIZONTAL	 = 0x0001,
    vdockerSPAN_X_WHEN_VERTICAL		 = 0x0002,
    vdockerSPAN_Y_WHEN_HORIZONTAL	 = 0x0004,
    vdockerSPAN_Y_WHEN_VERTICAL		 = 0x0008,
    vdockerSPAN_HORIZONTAL		 = vdockerSPAN_X_WHEN_HORIZONTAL |
                                           vdockerSPAN_X_WHEN_VERTICAL,
    vdockerSPAN_VERTICAL		 = vdockerSPAN_Y_WHEN_HORIZONTAL |
                                           vdockerSPAN_Y_WHEN_VERTICAL,
    vdockerSPAN_BREADTH			 = vdockerSPAN_X_WHEN_HORIZONTAL |
                                           vdockerSPAN_Y_WHEN_VERTICAL,
    vdockerSPAN_DEPTH			 = vdockerSPAN_Y_WHEN_HORIZONTAL |
                                           vdockerSPAN_X_WHEN_VERTICAL,
    _vdockerSPAN_MASK			 = 0x000f
};

enum {
    vdockerSPAN_FILL_NONE       	 = 0x0000,
    vdockerSPAN_FILL_X	 	 	 = 0x0010,
    vdockerSPAN_FILL_Y		 	 = 0x0020,
    vdockerSPAN_FILL		 	 = vdockerSPAN_FILL_X |
                                           vdockerSPAN_FILL_Y,
    _vdockerSPAN_FILL_MASK		 = 0x0030
};


enum {
    vdockerID_ATTRIBUTE_FLOATING	= vcontainerNEXT_ID_ATTRIBUTE,
    vdockerID_ATTRIBUTE_LOCKED,
    vdockerID_ATTRIBUTE_DOCK,
    vdockerID_ATTRIBUTE_HELD_ITEM,
    vdockerNEXT_ID_ATTRIBUTE
};

enum {
    vdockerSELECT_TOGGLE_FLOATING	= vcontainerNEXT_SELECT,
    vdockerSELECT_TOGGLE_SHOWN,
    vdockerNEXT_SELECT
};

enum {
    vdockerFLOATING_RECT,
    vdockerDOCKED_HORIZONTAL_RECT,
    vdockerDOCKED_VERTICAL_RECT
};

/*
 * * * * * * * * * * PUBLIC TYPE DEFINITIONS * * * * * * * * * *
 */

typedef struct vdocker			 vdocker;
typedef struct vdockerClass		 vdockerClass;
typedef struct vdockerDrag		 vdockerDrag;
typedef struct vdockerDragClass		 vdockerDragClass;

typedef void (*vdockerNoteProc)(
    vdocker				*docker,
    vevent				*event
    );

#ifndef  _vdockDEFINED_VDOCK
typedef struct vdock			 vdock;
#define  _vdockDEFINED_VDOCK (1) /** circular dependency **/
#endif


/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */

void vdockerStartup(
    void
    );

vdockerClass *vdockerGetDefaultClass(
    void
    );

vdocker *vdockerCreateOfClass(
    vdockerClass			*clas
    );

vdocker *vdockerCreate(
    void
    );

void vdockerInitOfClass(
    vdocker				*docker,
    vdockerClass			*clas
    );

void vdockerInit(
    vdocker				*docker
    );

void vdockerDestroy(
    vdocker				*docker
    );

vdocker *vdockerClone(
    vdocker				*docker
    );

void vdockerCopyInit(
    vdocker				*docker,
    vdocker				*target
    );

void vdockerCopy(
    vdocker				*docker,
    vdocker				*target
    );

vdocker *vdockerLoad(
    vresource				 resource
    );

void vdockerLoadInit(
    vdocker				*docker,
    vresource				 resource
    );

void vdockerStore(
    vdocker				*docker,
    vresource				 resource
    );

void vdockerSetData(
    vdocker				*docker,
    const void				*data
    );

void vdockerSetTag(
    vdocker				*docker,
    const vname				*tag
    );

void vdockerSetNotify(
    vdocker				*docker,
    vdockerNoteProc			 noteProc
    );

void vdockerSetFloating(
    vdocker				*docker,
    vbool				 floating
    );

void vdockerSetLocked(
    vdocker				*docker,
    vbool				 locked
    );

void vdockerSetHeldItem(
    vdocker				*docker,
    vdialogItem				*item
    );

void vdockerSetOverDockDragLineWidth(
    vdocker				*docker,
    short				 width
    );

void vdockerSetDragLineWidth(
    vdocker				*docker,
    short				 width
    );

void vdockerSetDock(
    vdocker				*docker,
    vdock				*dock
    );

void vdockerSetDragSubclass(
    vdocker				*docker,
    vclass				*clas
    );

void vdockerDetermineDragRect(
    vdocker				*docker,
    vdockerDrag				*drag,
    vdock				*dock,
    vrect				*rrect
    );

void vdockerSetSpanStyle(
    vdocker				*docker,
    int					 spanStyle
    );

void vdockerSetSpanFillModifiers(
    vdocker				*docker,
    int					 spanModifiers
    );

void vdockerSetDockedHorizontalRect(
    vdocker				*docker,
    const vrect				*rect
    );
    
void vdockerSetDockedVerticalRect(
    vdocker				*docker,
    const vrect				*rect
    );
    
void vdockerSetFloatingRect(
    vdocker				*docker,
    const vrect				*rect
    );

vdialogItem *vdockerGetItem(
    vdocker				*docker
    );

vobjectAttributed *vdockerGetObject(
    vdocker				*docker
    );

vobservable *vdockerGetObservable(
    vdocker				*docker
    );

vdockerClass *vdockerGetClass(
    vdocker				*docker
    );

const void *vdockerGetData(
    vdocker				*docker
    );

vdockerNoteProc vdockerGetNotify(
    vdocker				*docker
    );

const vname *vdockerGetTag(
    vdocker				*docker
    );

vbool vdockerIsOpen(
    vdocker				*docker
    );

vbool vdockerIsFloating(
    vdocker				*docker
    );

vbool vdockerIsLocked(
    vdocker				*docker
    );

vbool vdockerIsShown(
    vdocker				*docker
    );

vdialogItem *vdockerGetHeldItem(
    vdocker				*docker
    );

short vdockerGetOverDockDragLineWidth(
    vdocker				*docker
    );

short vdockerGetDragLineWidth(
    vdocker				*docker
    );

vdock *vdockerGetDock(
    vdocker				*docker
    );

vdockerDragClass *vdockerGetDragSubclass(
    vdocker				*docker
    );

int vdockerGetSpanStyle(
    vdocker				*docker
    );

int vdockerGetSpanFillModifiers(
    vdocker				*docker
    );

const vrect *vdockerGetDockedHorizontalRect(
    vdocker				*docker
    );
    
const vrect *vdockerGetDockedVerticalRect(
    vdocker				*docker
    );
    
const vrect *vdockerGetFloatingRect(
    vdocker				*docker
    );

vdialog *vdockerGetDialog(
    vdocker				*docker
    );

vdockerDrag *vdockerCreateDrag(
    vdocker				*docker
    );

void vdockerOpen(
    vdocker				*docker
    );

void vdockerClose(
    vdocker				*docker
    );

void vdockerHide(
    vdocker				*docker
    );

void vdockerShow(
    vdocker				*docker
    );

/* vdockerDrag prototypes */

vdockerDragClass *vdockerGetBaseDragClass(
    void
    );

void vdockerDestroyDrag(
    vdockerDrag				*drag
    );

void vdockerDestroyDragLater(
    vdockerDrag				*drag
    );

void vdockerSetDragDocker(
    vdockerDrag				*drag,
    vdocker				*owner
    );

void vdockerSetDragRect(
    vdockerDrag				*drag,
    const vrect				*rect
    );

vdrag *vdockerGetDragDrag(
    vdockerDrag				*drag
    );

vinstance *vdockerGetDragInstance(
    vdockerDrag				*drag
    );

vdockerDragClass *vdockerGetDragClass(
    vdockerDrag				*drag
    );

vdocker *vdockerGetDragDocker(
    vdockerDrag				*drag
    );

const vrect *vdockerGetDragRect(
    vdockerDrag				*drag
    );

void vdockerDetermineDragDragRect(
    vdockerDrag				*drag,
    vdock				*dock,
    vrect				*rrect
    );

vbool vdockerQueryDragEnterDock(
    vdockerDrag				*drag,
    vdock				*dock
    );

void vdockerNotifyDragDrop(
    vdockerDrag				*drag,
    vdock				*dock
    );


/*
 * * * * * * * * * * PRIVATE CONSTANT DEFINITIONS * * * * * * * * * *
 */

enum {
    _vdockerFLOATING			= 0x0001,
    _vdockerLOCKED			= 0x0002,
    _vdockerBEGUN_DOCKED		= 0x0004,
    _vdockerDUMPING			= 0x0008,
    _vdockerFORCE_UNDOCK		= 0x0010,
    _vdockerPERFORM_DRAG		= 0x0020,
    _vdockerCONSTRAINING		= 0x0080,
    _vdockerFIRST_CLICK			= 0x0100,
    _vdockerJUST_DOCKED                 = 0x0200
};


/*
 * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * *
 */

struct vdocker {
    vcontainer				 container;
    vdialog				*dialog;
    vdockerDragClass			*dragClass;
    vdockerDrag				*activeDrag;
    unsigned short			 flags;
    int					 spanStyle;
    short				 overDockDragLineWidth;
    short				 dragLineWidth;
    vrect				 lastFloatingRect;
    vrect				 lastDockedHorzRect;
    vrect				 lastDockedVertRect;
    vdock				*dock;
};

#define vdockerCLASS(SUPER, DOCKER, NOTIFY, DRAG)			      \
    vcontainerCLASS(SUPER, DOCKER, NOTIFY);				      \
    vclassMETHOD_RET(vdockerCREATE_DRAG, DRAG *, (DOCKER *docker));	      \
    vclassMETHOD(vdockerOPEN, (DOCKER *docker));			      \
    vclassMETHOD(vdockerCLOSE, (DOCKER *docker));			      \
    vclassMETHOD(vdockerSET_FLOATING, (DOCKER *docker, vbool floating));      \
    vclassMETHOD(vdockerSET_LOCKED, (DOCKER *docker, vbool locked));	      \
    vclassMETHOD(vdockerSET_HELD_ITEM, (DOCKER *docker, vdialogItem *item));  \
    vclassMETHOD(vdockerSET_DOCK, (DOCKER *docker, vdock *dock));	      \
    vclassMETHOD(vdockerDETERMINE_DRAG_RECT,				      \
		 (DOCKER *docker, vdockerDrag *drag, 			      \
                  vdock *dock, vrect *rrect));				      \
    vclassMETHOD(vdockerSET_SPAN_STYLE,                                       \
		 (DOCKER *docker, int spanStyle));			      \
    vclassMETHOD(vdockerSET_SPAN_FILL_MODIFIERS,                              \
		 (DOCKER *docker, int spanModifiers));                        \
    vclassMETHOD(vdockerSET_REMEMBERED_RECT,                                  \
                 (DOCKER *docker, int whichRect, const vrect *rect))

struct vdockerClass {
    vdockerCLASS(vdockerClass, vdocker, vdockerNoteProc, vdockerDrag);
};

struct vdockerDrag {
    vdrag				 drag;
    vdocker				*docker;
    vrect				 rect;
    vrect				 lastRect;
    int					 lastWidth;
    vdock				*dock;
};

#define vdockerDragCLASS(SUPER, DRAG)    				      \
    vdragCLASS(SUPER, DRAG);    					      \
    vclassMETHOD(vdockerSET_DRAG_DOCKER, (DRAG *drag, vdocker *owner));	      \
    vclassMETHOD(vdockerSET_DRAG_RECT, (DRAG *drag, const vrect *rect));      \
    vclassMETHOD(vdockerDETERMINE_DRAG_DRAG_RECT,			      \
		 (DRAG *drag, vdock *dock, vrect *rrect));		      \
    vclassMETHOD_RET(vdockerQUERY_DRAG_ENTER_DOCK, vbool,		      \
		     (DRAG *drag, vdock *dock));			      \
    vclassMETHOD(vdockerNOTIFY_DRAG_DROP, (DRAG *drag, vdock *dock))

struct vdockerDragClass {
    vdockerDragCLASS(vdockerDragClass, vdockerDrag);
};

/*
 * * * * * * * * * * PRIVATE FUNCTION PROTOTYPES * * * * * * * * * *
 */

void _vdockerSendSetRememberedRect(vdocker *docker, int whichRect,
				   const vrect *rect);

/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * *
 */

#define _vdockerGetContainer(d)						      \
	vportBASE_OBJECT(d, container)
#define vdockerGetItem(d)						      \
	vcontainerGetItem(_vdockerGetContainer(d))
#define vdockerGetObject(d)						      \
	vcontainerGetObject(_vdockerGetContainer(d))
#define vdockerGetObservable(d)						      \
	vobjectGetObservable(vdockerGetObject(d))

#define vdockerCreateOfClass(c)						      \
	((vdocker *) vcontainerCreateOfClass((vcontainerClass *) (c)))
#define vdockerCreate()							      \
	vdockerCreateOfClass(vdockerGetDefaultClass())
#define vdockerClone(d)							      \
	((vdocker *) vcontainerClone(_vdockerGetContainer(d)))
#define vdockerInitOfClass(d, c)					      \
	vcontainerInitOfClass(_vdockerGetContainer(d), (vcontainerClass *)(c)))
#define vdockerInit(d)							      \
	vdockerInitOfClass(d, vdockerGetDefaultClass())
#define vdockerDestroy(d)						      \
	vcontainerDestroy(_vdockerGetContainer(d))
#define vdockerCopy(d, t)						      \
	vcontainerCopy(_vdockerGetContainer(d), _vdockerGetContainer(t))
#define vdockerCopyInit(d, t)						      \
	vcontainerCopyInit(_vdockerGetContainer(d), _vdockerGetContainer(t))
#define vdockerLoad(r)							      \
	((vdocker *) vcontainerLoad(r))
#define vdockerLoadInit(d, r)						      \
	vcontainerLoadInit(_vdockerGetContainer(d), r)
#define vdockerStore(d, r)						      \
	vcontainerStore(_vdockerGetContainer(d), r)
#define vdockerSetData(d, v)						      \
	vcontainerSetData(_vdockerGetContainer(d), v)
#define vdockerSetTag(d, t)						      \
	vdialogSetItemTag(vdockerGetItem(d), t)
#define vdockerSetNotify(d, n)						      \
	vcontainerSetNotify(_vdockerGetContainer(d), (vcontainerNoteProc) (n))
#define vdockerGetClass(d)						      \
	((vdockerClass *) vcontainerGetClass(_vdockerGetContainer(d)))
#define vdockerGetData(d)						      \
	vcontainerGetData(_vdockerGetContainer(d))
#define vdockerGetTag(d)						      \
	vdialogGetItemTag(vdockerGetItem(d))
#define vdockerGetNotify(d)						      \
	((vdockerNoteProc) vcontainerGetNotify(_vdockerGetContainer(d)))
#define vdockerGetDialog(d)						      \
	((d)->dialog)
#define vdockerIsFloating(d)						      \
	(((d)->flags & _vdockerFLOATING) ? vTRUE : vFALSE)
#define vdockerIsOpen(d)						      \
	(vdockerIsFloating(d) ? vdialogIsOpen(vdockerGetDialog(d)) :	      \
				vdialogItemIsOpen(vdockerGetItem(d)))
#define vdockerIsLocked(d)						      \
	(((d)->flags & _vdockerLOCKED) ? vTRUE : vFALSE)
#define vdockerIsShown(d)						      \
	vdialogItemIsShown(vdockerGetItem(d))
#define vdockerGetOverDockDragLineWidth(d)				      \
	((d)->overDockDragLineWidth)
#define vdockerGetDragLineWidth(d)					      \
	((d)->dragLineWidth)
#define vdockerGetDragSubclass(d)					      \
	((d)->dragClass)
#define vdockerGetDock(d)						      \
	((d)->dock)
#define vdockerGetSpanStyle(d)   ((d)->spanStyle & _vdockerSPAN_MASK)
#define vdockerGetSpanFillModifiers(d)                                        \
        ((d)->spanStyle & _vdockerSPAN_FILL_MASK)
#define vdockerHide(d)							      \
	vdialogHideItem(vdockerGetItem(d))
#define vdockerShow(d)							      \
	vdialogShowItem(vdockerGetItem(d))

#define vdockerGetDragDrag(d)						      \
	vportBASE_OBJECT(d, drag)
#define vdockerGetDragInstance(d)					      \
	vdragGetInstance(vdockerGetDragDrag(d))

#define vdockerDestroyDrag(d)						      \
	vdragDestroy(vdockerGetDragDrag(d))
#define vdockerDestroyDragLater(d)					      \
	vdragDestroyLater(vdockerGetDragDrag(d))
#define vdockerGetDragClass(d)						      \
	((vdockerDragClass *) vdragGetClass(vdockerGetDragDrag(d)))
#define vdockerGetDragDocker(d)						      \
	((d)->docker)
#define vdockerGetDragRect(d)						      \
	((const vrect *) &(d)->rect)


/*
 * * * * * * * * * * PRIVATE FUNCTION MESSAGE DEFINITIONS * * * * * * * * * *
 */

#define vdockerCreateDrag(d)						      \
	vclassSend(vdockerGetClass(d), vdockerCREATE_DRAG, (d))
#define vdockerOpen(d)							      \
	vclassSend(vdockerGetClass(d), vdockerOPEN, (d))
#define vdockerClose(d)							      \
	vclassSend(vdockerGetClass(d), vdockerCLOSE, (d))
#define vdockerSetFloating(d, f)					      \
	vclassSend(vdockerGetClass(d), vdockerSET_FLOATING, (d, f))
#define vdockerSetLocked(d, l)						      \
	vclassSend(vdockerGetClass(d), vdockerSET_LOCKED, (d, l))
#define vdockerSetHeldItem(d, i)					      \
	vclassSend(vdockerGetClass(d), vdockerSET_HELD_ITEM, (d, i))
#define vdockerSetDock(d, s)						      \
	vclassSend(vdockerGetClass(d), vdockerSET_DOCK, (d, s))
#define vdockerDetermineDragRect(d, g, k, r)                                  \
	vclassSend(vdockerGetClass(d), vdockerDETERMINE_DRAG_RECT, (d,g,k,r))
#define vdockerSetSpanStyle(d, s)				              \
	vclassSend(vdockerGetClass(d), vdockerSET_SPAN_STYLE, (d, s))
#define vdockerSetSpanFillModifiers(d, s)				      \
	vclassSend(vdockerGetClass(d), vdockerSET_SPAN_FILL_MODIFIERS, (d, s))
#define _vdockerSendSetRememberedRect(d, w, r)                                \
	vclassSend(vdockerGetClass(d), vdockerSET_REMEMBERED_RECT,            \
                   (d, w, r))
#define vdockerSetFloatingRect(d, r)                                          \
        _vdockerSendSetRememberedRect(d, vdockerFLOATING_RECT, r)
#define vdockerSetDockedHorizontalRect(d, r)                                  \
        _vdockerSendSetRememberedRect(d, vdockerDOCKED_HORIZONTAL_RECT, r)
#define vdockerSetDockedVerticalRect(d, r)                                    \
        _vdockerSendSetRememberedRect(d, vdockerDOCKED_VERTICAL_RECT, r)
    

#define vdockerSetDragDocker(d, o)					      \
	vclassSend(vdockerGetDragClass(d), vdockerSET_DRAG_DOCKER, (d, o))
#define vdockerSetDragRect(d, r)					      \
	vclassSend(vdockerGetDragClass(d), vdockerSET_DRAG_RECT, (d, r))
#define vdockerDetermineDragDragRect(d, o, r)				      \
	vclassSend(vdockerGetDragClass(d), vdockerDETERMINE_DRAG_DRAG_RECT,   \
		   (d, o, r))
#define vdockerQueryDragEnterDock(d, o)					      \
	vclassSend(vdockerGetDragClass(d), vdockerQUERY_DRAG_ENTER_DOCK,      \
		   (d, o))
#define vdockerNotifyDragDrop(d, o)					      \
	vclassSend(vdockerGetDragClass(d), vdockerNOTIFY_DRAG_DROP, (d, o))


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

#endif /* #ifndef vdockerINCLUDED */

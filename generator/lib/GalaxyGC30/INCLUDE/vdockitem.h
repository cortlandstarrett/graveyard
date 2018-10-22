/* $Id: vdockitem.h,v 1.10 1997/09/02 17:29:00 robert Exp $ */

/************************************************************

    vdockitem.h

    C Interface file for vdockitem

    (c) Copyright Visix Software Inc.
    All rights reserved

************************************************************/

#ifndef  vdockitemINCLUDED
#define  vdockitemINCLUDED 1

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

#ifndef  vobjectINCLUDED
#include vobjectHEADER
#endif

#ifndef  vdialogINCLUDED
#include vdialogHEADER
#endif

#ifndef  vdockerINCLUDED
#include vdockerHEADER
#endif

#ifndef  vdockINCLUDED
#include vdockHEADER
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C


/*
 * * * * * * * * * * PUBLIC CONSTANT DEFINITIONS * * * * * * * * * *
 */

enum {
    vdockitemID_ATTRIBUTE_CONTENT	= vdialogITEM_NEXT_ID_ATTRIBUTE,
    vdockitemID_ATTRIBUTE_SOLUTION,
    vdockitemID_ATTRIBUTE_VERTICAL,
    vdockitemID_ATTRIBUTE_DOCKING_ENABLED,
    vdockitemID_ATTRIBUTE_GROW_DIRECTION_POSITIVE,
    vdockitemID_ATTRIBUTE_EMPTY_PADDING,
    vdockitemID_ATTRIBUTE_WRAP,
    vdockitemNEXT_ID_ATTRIBUTE
};

enum {
    vdockitemNEXT_SELECT		= vdialogITEM_NEXT_SELECT
};


/*
 * * * * * * * * * * PUBLIC TYPE DEFINITIONS * * * * * * * * * *
 */

typedef struct vdockitem		 vdockitem;
typedef struct vdockitemClass		 vdockitemClass;
typedef struct vdockitemDockerIterator	 vdockitemDockerIterator;

typedef void (*vdockitemNoteProc)(
    vdockitem				*dock,
    vevent				*event
    );

#ifndef  _vdockDEFINED_VDOCK
typedef struct vdock			 vdock;
#define  _vdockDEFINED_VDOCK (1) /** circular dependency **/
#endif


/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */

void vdockitemStartup(
    void
    );

vdockitemClass *vdockitemGetDefaultClass(
    void
    );

vdockitem *vdockitemCreateOfClass(
    vdockitemClass			*clas
    );

vdockitem *vdockitemCreate(
    void
    );

void vdockitemInitOfClass(
    vdockitem				*dock,
    vdockitemClass			*clas
    );

void vdockitemInit(
    vdockitem				*dock
    );

void vdockitemDestroy(
    vdockitem				*dock
    );

vdockitem *vdockitemClone(
    vdockitem				*dock
    );

void vdockitemCopyInit(
    vdockitem				*dock,
    vdockitem				*target
    );

void vdockitemCopy(
    vdockitem				*dock,
    vdockitem				*target
    );

vdockitem *vdockitemLoad(
    vresource				 resource
    );

void vdockitemLoadInit(
    vdockitem				*dock,
    vresource				 resource
    );

void vdockitemStore(
    vdockitem				*dock,
    vresource				 resource
    );

void vdockitemSetNotify(
    vdockitem				*dock,
    vdockitemNoteProc			 noteProc
    );

void vdockitemSetData(
    vdockitem				*dock,
    const void				*data
    );

void vdockitemSetVertical(
    vdockitem				*dock,
    vbool				 vertical
    );

void vdockitemSetDockingEnabled(
    vdockitem				*dock,
    vbool				 enabled
    );

void vdockitemSetGrowDirectionPositive(
    vdockitem				*dock,
    vbool				 positive
    );

void vdockitemSetWrap(
    vdockitem				*dock,
    vbool				 wrap
    );

void vdockitemSetFlush(
    vdockitem				*dock,
    vbool				 flush
    );

void vdockitemSetEmptyPadding(
    vdockitem				*dock,
    short				 padding
    );

vdialogItem *vdockitemGetItem(
    vdockitem				*dock
    );

vobject *vdockitemGetObject(
    vdockitem				*dock
    );

vobservable *vdockitemGetObservable(
    vdockitem				*dock
    );

vdockitemClass *vdockitemGetClass(
    vdockitem				*dock
    );

vdockitemNoteProc vdockitemGetNotify(
    vdockitem				*dock
    );

const void *vdockitemGetData(
    vdockitem				*dock
    );

vdock *vdockitemGetDock(
    vdockitem				*dock
    );

const vrect *vdockitemGetContent(
    vdockitem				*dock
    );

vdialogItemList *vdockitemGetItemList(
    vdockitem				*dock
    );

vbool vdockitemIsVertical(
    vdockitem				*dock
    );

vbool vdockitemIsDockingEnabled(
    vdockitem				*dock
    );

vbool vdockitemIsGrowDirectionPositive(
    vdockitem				*dock
    );

vbool vdockitemHasWrap(
    vdockitem				*dock
    );

vbool vdockitemIsFlush(
    vdockitem				*dock
    );

short vdockitemGetEmptyPadding(
    vdockitem				*dock
    );

void vdockitemAddDocker(
    vdockitem				*dock,
    vdocker				*docker,
    const vrect				*rect
    );

void vdockitemRemoveDocker(
    vdockitem				*dock,
    vdocker				*docker
    );

void vdockitemArrange(
    vdockitem				*dock,
    const vrect				*rect
    );

void vdockitemCalcContent(
    vdockitem				*dock,
    vrect				*rect
    );

void vdockitemCalcMinSize(
    vdockitem				*dock,
    int					*w,
    int					*h
    );

int vdockitemGetDockerCount(
    vdockitem				*dock
    );

vdocker *vdockitemFindDocker(
    vdockitem				*dock,
    const vname				*tag
    );

vbool vdockitemQueryAcceptDocker(
    vdockitem				*dock,
    vdocker				*docker
    );

void vdockitemLoadLayout(
    vdockitem				*dock,
    vresource				 resource
    );

void vdockitemStoreLayout(
    vdockitem				*dock,
    vresource				 resource
    );

/* vdockitemDockerIterator prototypes */

void vdockitemInitDockerIterator(
    vdockitemDockerIterator		*iterator,
    vdockitem				*dock
    );

int vdockitemNextDockerIterator(
    vdockitemDockerIterator		*iterator
    );

void vdockitemDestroyDockerIterator(
    vdockitemDockerIterator		*iterator
    );

vdocker *vdockitemGetDockerIteratorDocker(
    vdockitemDockerIterator		*iterator
    );


/*
 * * * * * * * * * * PRIVATE CONSTANT DEFINITIONS * * * * * * * * * *
 */

enum {
    _vdockitemVERTICAL			= 0x0001,
    _vdockitemDOCKING_ENABLED		= 0x0002,
    _vdockitemFIRST_CLICK		= 0x0004,
    _vdockitemGROW_POSITIVE		= 0x0008,
    _vdockitemCHANGED_SIZE		= 0x0010,
    _vdockitemCHANGED_SOLUTION		= 0x0020,
    _vdockitemDIM_VALID			= 0x0040,
    _vdockitemFLUSH			= 0x0080,
    _vdockitemPADDING_SET		= 0x0100,
    _vdockitemCALCULATE_SIZE		= 0x0200,
    _vdockitemCHANGED_CHILD_SIZE	= 0x0400,
    _vdockitemWRAP			= 0x0800
};


/*
 * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * *
 */

typedef struct _vdockitemRow		_vdockitemRow;

struct vdockitem {
    vdialogItem				 item;
    vrect				 content;
    unsigned short			 flags;
    short				 minDim, newDim, deltaH, padding;
    short				 bw; /* border width */
    _vdockitemRow			*dockers;
    vdialogItemList			*itemList;
    vdock				*drop;
};

#define vdockitemCLASS(SUPER, DOCK, NOTIFY)				      \
    vdialogITEM_CLASS(SUPER, DOCK, NOTIFY);				      \
    vclassVARIABLE(vdockitemEMPTY_PADDING, short);			      \
    vclassMETHOD_RET(vdockitemCREATE_ITEM_LIST,	vdialogItemList *,	      \
		     (DOCK *dock));					      \
    vclassMETHOD(vdockitemADD_DOCKER,					      \
		 (DOCK *dock, vdocker *docker, const vrect *rect));	      \
    vclassMETHOD(vdockitemREMOVE_DOCKER, (DOCK *dock, vdocker *docker));      \
    vclassMETHOD(vdockitemARRANGE, (DOCK *dock, const vrect *rect));	      \
    vclassMETHOD(vdockitemCALC_MIN_SIZE, (DOCK *dock, int *w, int *h));	      \
    vclassMETHOD(vdockitemSET_VERTICAL, (DOCK *dock, vbool vertical));	      \
    vclassMETHOD(vdockitemSET_DOCKING_ENABLED,				      \
		 (DOCK *dock, vbool enabled));				      \
    vclassMETHOD(vdockitemSET_GROW_DIRECTION_POSITIVE,			      \
		 (DOCK *dock, vbool positive));				      \
    vclassMETHOD(vdockitemSET_WRAP, (DOCK *dock, vbool wrap));                \
    vclassMETHOD(vdockitemSET_EMPTY_PADDING, (DOCK *dock, short padding));    \
    vclassMETHOD(vdockitemSET_FLUSH, (DOCK *dock, vbool flush));	      \
    vclassMETHOD_RET(vdockitemQUERY_ACCEPT_DOCKER, vbool,		      \
		     (DOCK *dock, vdocker *docker));                          \
    vclassMETHOD(vdockitemSTORE_LAYOUT,                                       \
		     (DOCK *dock, vresource res));                            \
    vclassMETHOD(vdockitemLOAD_LAYOUT,                                        \
		     (DOCK *dock, vresource res))

struct vdockitemClass {
    vdockitemCLASS(vdockitemClass, vdockitem, vdockitemNoteProc);
};

struct vdockitemDockerIterator {
    vdockitem				 *dockitem;
    _vdockitemRow			 *rowScan;
    vdialogItem				**dockerScan;
};


/*
 * * * * * * * * * * PRIVATE FUNCTION PROTOTYPES * * * * * * * * * *
 */

vobjectPartialChildIteratorClass *_vdockitemGetPartialChildIteratorClass(
    void
    );


/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * *
 */

#define vdockitemGetItem(d)						      \
	vportBASE_OBJECT(d, item)
#define vdockitemGetObject(d)						      \
	vdialogGetItemObject(vdockitemGetItem(d))
#define vdockitemGetObservable(d)					      \
	vobjectGetObservable(vdockitemGetObject(d))

#define vdockitemCreateOfClass(c)					      \
	((vdockitem *) vdialogCreateItemOfClass((vdialogItemClass *) (c)))
#define vdockitemCreate()						      \
	vdockitemCreateOfClass(vdockitemGetDefaultClass())
#define vdockitemInitOfClass(d, c)					      \
	vdialogInitItemOfClass(vdockitemGetItem(d),			      \
			       (vdialogItemClass *) (c)))
#define vdockitemInit(d)						      \
	vdockitemInitOfClass(d, vdockitemGetDefaultClass())
#define vdockitemDestroy(d)						      \
	vdialogDestroyItem(vdockitemGetItem(d))
#define vdockitemClone(d)						      \
	((vdockitem *) vdialogCloneItem(vdockitemGetItem(d)))
#define vdockitemCopyInit(d, t)						      \
	vdialogCopyInitItem(vdockitemGetItem(d), vdockitemGetItem(t))
#define vdockitemCopy(d, t)						      \
	vdialogCopyItem(vdockitemGetItem(d), vdockitemGetItem(t))
#define vdockitemLoad(r)						      \
	((vdockitem *) vdialogLoadItem(r))
#define vdockitemLoadInit(d, r)						      \
	vdialogLoadInitItem(vdockitemGetItem(d), r)
#define vdockitemStore(d, r)						      \
	vdialogStoreItem(vdockitemGetItem(d), r)
#define vdockitemSetData(d, v)						      \
	vdialogSetItemData(vdockitemGetItem(d), v)
#define vdockitemSetNotify(d, n)					      \
	vdialogSetItemNotify(vdockitemGetItem(d), (vdialogItemNoteProc) (n))
#define vdockitemGetClass(d)						      \
	((vdockitemClass *) vdialogGetItemClass(vdockitemGetItem(d)))
#define vdockitemGetNotify(d)						      \
	((vdockitemNoteProc) vdialogGetItemNotify(vdockitemGetItem(d)))
#define vdockitemGetData(d)						      \
	vdialogGetItemData(vdockitemGetItem(d))
#define vdockitemGetDock(d)						      \
	((d)->drop)
#define vdockitemGetContent(d)						      \
	((const vrect *) &(d)->content)
#define vdockitemGetItemList(d)						      \
	((d)->itemList)
#define vdockitemIsVertical(d)						      \
	(((d)->flags & _vdockitemVERTICAL) ? vTRUE : vFALSE)
#define vdockitemIsDockingEnabled(d)					      \
	(((d)->flags & _vdockitemDOCKING_ENABLED) ? vTRUE : vFALSE)
#define vdockitemIsGrowDirectionPositive(d)				      \
	(((d)->flags & _vdockitemGROW_POSITIVE) ? vTRUE : vFALSE)
#define vdockitemHasWrap(d)						      \
	(((d)->flags & _vdockitemWRAP) ? vTRUE : vFALSE)
#define vdockitemIsFlush(d)						      \
	(((d)->flags & _vdockitemFLUSH) ? vTRUE : vFALSE)
#define vdockitemGetEmptyPadding(d)					      \
	((d)->padding)

#define vdockitemDestroyDockerIterator(i)
#define vdockitemGetDockerIteratorDocker(i)				      \
	((vdocker *) *(i)->dockerScan)


/*
 * * * * * * * * * * PRIVATE FUNCTION MESSAGE DEFINITIONS * * * * * * * * * *
 */

#define vdockitemAddDocker(d, o, r)					      \
	vclassSend(vdockitemGetClass(d), vdockitemADD_DOCKER, (d, o, r))
#define vdockitemRemoveDocker(d, o)					      \
	vclassSend(vdockitemGetClass(d), vdockitemREMOVE_DOCKER, (d, o))
#define vdockitemArrange(d, r)						      \
	vclassSend(vdockitemGetClass(d), vdockitemARRANGE, (d, r))
#define vdockitemCalcMinSize(d, w, h)					      \
	vclassSend(vdockitemGetClass(d), vdockitemCALC_MIN_SIZE, (d, w, h))
#define vdockitemSetVertical(d, v)					      \
	vclassSend(vdockitemGetClass(d), vdockitemSET_VERTICAL, (d, v))
#define vdockitemSetDockingEnabled(d, e)				      \
	vclassSend(vdockitemGetClass(d), vdockitemSET_DOCKING_ENABLED, (d, e))
#define vdockitemSetGrowDirectionPositive(d, i)				      \
	vclassSend(vdockitemGetClass(d),                                      \
            vdockitemSET_GROW_DIRECTION_POSITIVE, (d, i))
#define vdockitemSetWrap(d, i)						      \
	vclassSend(vdockitemGetClass(d), vdockitemSET_WRAP, (d, i))
#define vdockitemSetEmptyPadding(d, p)					      \
	vclassSend(vdockitemGetClass(d), vdockitemSET_EMPTY_PADDING, (d, p))
#define vdockitemSetFlush(d, f)						      \
	vclassSend(vdockitemGetClass(d), vdockitemSET_FLUSH, (d, f))
#define vdockitemQueryAcceptDocker(d, o)				      \
	vclassSend(vdockitemGetClass(d), vdockitemQUERY_ACCEPT_DOCKER, (d, o))
#define vdockitemLoadLayout(d, r)				              \
	vclassSend(vdockitemGetClass(d), vdockitemLOAD_LAYOUT, (d, r))
#define vdockitemStoreLayout(d, r)				              \
	vclassSend(vdockitemGetClass(d), vdockitemSTORE_LAYOUT, (d, r))


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

#endif /* #ifndef vdockitemINCLUDED */

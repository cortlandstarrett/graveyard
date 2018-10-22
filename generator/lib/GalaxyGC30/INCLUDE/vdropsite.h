/* $Id: vdropsite.h,v 1.8 1997/05/27 20:49:30 robert Exp $ */

/************************************************************

    vdrop.h

    C Interface file for Drop Sites

    (c) Copyright Visix Software Inc.
    All rights reserved

************************************************************/

#ifndef  vdropINCLUDED
#define  vdropINCLUDED 1

#ifndef  vportINCLUDED
#include <vport.h>
#endif

#ifndef  vrectINCLUDED
#include vrectHEADER
#endif

#ifndef  veventINCLUDED
#include veventHEADER
#endif

#ifndef  vclassINCLUDED
#include vclassHEADER
#endif

#ifndef  vloadableINCLUDED
#include vloadableHEADER
#endif

#ifndef  vwindowINCLUDED
#include vwindowHEADER
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * * * * * * * * * * PUBLIC CONSTANT DEFINITIONS * * * * * * * * * *
 */

enum {
  vdropFEEDBACK_REJECT         = 0x00000000,
  vdropFEEDBACK_MOVE           = 0x00000001,
  vdropFEEDBACK_COPY           = 0x00000002,
  vdropFEEDBACK_LINK           = 0x00000004,
  vdropFEEDBACK_REJECT_RETRY   = 0x00000008
};

/* Notify states */
enum {
    vdropSTATE_ENTER			= 0,
    vdropSTATE_DETAIL,
    vdropSTATE_LEAVE,
    vdropSTATE_DROP
};


/*
 * * * * * * * * * * PUBLIC TYPE DEFINITIONS * * * * * * * * * *
 */

typedef struct vdropsiteClass		 vdropsiteClass;

#if (!_vdragDefined)
typedef struct vdrag vdrag;
typedef struct vdragEngine vdragEngine;
typedef struct vdropsite		 vdropsite;
typedef vdropsite	        	 vdropsiteInternal;
#define _vdragDefined 1
#endif

typedef int (*vdropsiteNoteProc)(
    vdropsite				*drop,
    vdrag				*drag,
    vevent				*event,
    int					 state
    );

/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */

void vdropsiteStartup(
    void
    );

vdropsiteClass *vdropsiteGetDefaultClass(
    void
    );

vdropsiteClass *vdropsiteGetDefaultInternalClass(
    void
    );

vdropsite *vdropsiteCreateOfClass(
    vdropsiteClass			*clas
    );

vdropsite *vdropsiteCreate(
    void
    );

vdropsite *vdropsiteCreateInternal(
    void
    );

vdropsite *vdropsiteClone(
    vdropsite				*drop
    );

void vdropsiteInitOfClass(
    vdropsite				*drop,
    vdropsiteClass			*clas
    );

void vdropsiteInit(
    vdropsite				*drop
    );

void vdropsiteDestroy(
    vdropsite				*drop
    );

void vdropsiteCopy(
    vdropsite				*drop,
    vdropsite				*target
    );

void vdropsiteCopyInit(
    vdropsite				*drop,
    vdropsite				*target
    );

vdropsite *vdropsiteLoad(
    vresource				 resource
    );

void vdropsiteLoadInit(
    vdropsite				*drop,
    vresource				 resource
    );

void vdropsiteStore(
    vdropsite				*drop,
    vresource				 resource
    );

void vdropsiteSetTag(
    vdropsite				*drop,
    const vname				*tag
    );

void vdropsiteSetData(
    vdropsite				*drop,
    const void				*data
    );

void vdropsiteSetNotify(
    vdropsite				*drop,
    vdropsiteNoteProc			 noteProc
    );

void vdropsiteSetRect(
    vdropsite				*drop,
    const vrect				*rect
    );

void vdropsiteSetWindow(
    vdropsite				*drop,
    vwindow				*window
    );

void vdropsiteEnable(
    vdropsite                           *drop
    );

void vdropsiteDisable(  
    vdropsite                           *drop
    );

vloadable *vdropsiteGetLoadable(
    vdropsite				*drop
    );

vinstance *vdropsiteGetInstance(
    vdropsite				*drop
    );

vdropsiteClass *vdropsiteGetClass(
    vdropsite				*drop
    );

const vname *vdropsiteGetTag(
    vdropsite				*drop
    );

const void *vdropsiteGetData(
    vdropsite				*drop
    );

vdropsiteNoteProc vdropsiteGetNotify(
    vdropsite				*drop
    );

const vrect *vdropsiteGetRect(
    vdropsite				*drop
    );

vwindow *vdropsiteGetWindow(
    vdropsite				*drop
    );

vbool vdropsiteIsEnabled(
    vdropsite                           *drop
    );

int vdropsiteHandleEnter(
    vdropsite				*drop,
    vdrag				*drag,
    vevent				*event
    );

int vdropsiteHandleDetail(
    vdropsite				*drop,
    vdrag				*drag,
    vevent				*event
    );

void vdropsiteHandleLeave(
    vdropsite				*drop,
    vdrag				*drag
    );

void vdropsiteHandleDrop(
    vdropsite				*drop,
    vdrag				*drag,
    vevent				*event
    );

/*
 * * * * * * * * * * PRIVATE CONSTANT DEFINITIONS * * * * * * * * * *
 */

#define _vdropsiteDISABLED 0x00000001

/*
 * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * *
 */

struct vdropsite {
    vloadable				 loadable;
    vwindow				*window;
    vrect				 rect;
    vdropsiteNoteProc			 noteProc;
    const void				*data;
    unsigned long                        flags;
};

#define vdropsiteCLASS(SUPER, DROP, NOTIFY)				      \
    vloadableCLASS(SUPER, DROP);					      \
    vclassMETHOD_RET(vdropsiteHANDLE_ENTER, int,			      \
		     (DROP *dropsite, vdrag *drag, vevent *event));	      \
    vclassMETHOD_RET(vdropsiteHANDLE_DETAIL, int,			      \
		     (DROP *dropsite, vdrag *drag, vevent *event));	      \
    vclassMETHOD(vdropsiteHANDLE_LEAVE,					      \
		 (DROP *dropsite, vdrag *drag));		              \
    vclassMETHOD(vdropsiteHANDLE_DROP,					      \
		 (DROP *dropsite, vdrag *drag, vevent *event));		      \
    vclassMETHOD(vdropsiteSET_DATA, (DROP *dropsite, const void *data));      \
    vclassMETHOD(vdropsiteSET_NOTIFY, (DROP *dropsite, NOTIFY noteProc));     \
    vclassMETHOD(vdropsiteSET_RECT, (DROP *dropsite, const vrect *rect));     \
    vclassMETHOD(vdropsiteSET_WINDOW, (DROP *dropsite, vwindow *window));     \
    vclassMETHOD(vdropsiteENABLE, (DROP *dropsite));                          \
    vclassMETHOD(vdropsiteDISABLE, (DROP *dropsite))

struct vdropsiteClass {
    vdropsiteCLASS(vdropsiteClass, vdropsite, vdropsiteNoteProc);
};


vportALIAS(vdropsiteInternal, vdropsite)

/*
 * * * * * * * * * * PRIVATE FUNCTION PROTOTYPES * * * * * * * * * *
 */

int _vdropsiteCallNoteProc(
    vdropsite				*drop,
    vdrag				*drag,
    vevent				*event,
    int					 state
    );

int _vdropsiteSendEnter(
    vdropsite				*drop,
    vdrag				*drag,
    vevent				*event
    );

int _vdropsiteSendDetail(
    vdropsite				*drop,
    vdrag				*drag,
    vevent				*event
    );

void _vdropsiteSendLeave(
    vdropsite				*drop,
    vdrag				*drag,
    vevent				*event
    );

void _vdropsiteSendDrop(
    vdropsite				*drop,
    vdrag				*drag,
    vevent				*event
    );

/* this belongs in vdrag when vdrop is exported */

vdropsite *_vdragGetTargetdropsite(
    vdrag				*drag
    );

/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * *
 */

#define vdropsiteGetLoadable(d)						      \
	vportBASE_OBJECT(d, loadable)
#define vdropsiteGetInstance(d)						      \
	vloadableGetInstance(vdropsiteGetLoadable(d))

#define vdropsiteCreateOfClass(c)					      \
	((vdropsite *) vinstanceCreateOfClass((vinstanceClass *) (c)))
#define vdropsiteCreate()						      \
	vdropsiteCreateOfClass(vdropsiteGetDefaultClass())
#define vdropsiteCreateInternal()					      \
	vdropsiteCreateOfClass(vdropsiteGetDefaultInternalClass())
#define vdropsiteClone(d)						      \
	((vdropsite *) vloadableClone(vdropsiteGetLoadable(d)))
#define vdropsiteInitOfClass(d, c)					      \
	vloadableInitOfClass(vdropsiteGetLoadable(d), (vloadableClass *) (c)))
#define vdropsiteInit(d)						      \
	vdropsiteInitOfClass(d, vdropsiteGetDefaultClass())
#define vdropsiteDestroy(d)						      \
	vinstanceDestroy(vdropsiteGetInstance(d))
#define vdropsiteCopy(d, t)						      \
	vloadableCopy(vdropsiteGetLoadable(d), vdropsiteGetLoadable(t))
#define vdropsiteCopyInit(d, t)						      \
	vloadableCopyInit(vdropsiteGetLoadable(d), vdropsiteGetLoadable(t))
#define vdropsiteLoad(r)						      \
	((vdropsite *) vloadableLoad(r))
#define vdropsiteLoadInit(d, r)						      \
	vloadableLoadInit(vdropsiteGetLoadable(d), r)
#define vdropsiteStore(d, r)						      \
	vloadableStore(vdropsiteGetLoadable(d), r)
#define vdropsiteGetClass(d)						      \
	((vdropsiteClass *) vloadableGetClass(vdropsiteGetLoadable(d)))
#define vdropsiteGetTag(d)						      \
	vloadableGetTag(vdropsiteGetLoadable(d))
#define vdropsiteGetRect(d)						      \
	(&(d)->rect)
#define vdropsiteGetWindow(d)						      \
	((d)->window)
#define vdropsiteGetData(d)						      \
	((d)->data)
#define vdropsiteGetNotify(d)						      \
	((d)->noteProc)
#define vdropsiteSetTag(d, t)						      \
	vloadableSetTag(vdropsiteGetLoadable(d), t)
#define vdropsiteIsEnabled(d)                                                 \
        ((d)->flags & _vdropsiteDISABLED ? vFALSE : vTRUE)

#define _vdropsiteCallNoteProc(d, s, e, t)				      \
	(((d)->noteProc != NULL) ? (*(d)->noteProc)(d, s, e, t) : 0)


/*
 * * * * * * * * * * PRIVATE FUNCTION MESSAGE DEFINITIONS * * * * * * * * * *
 */

#define vdropsiteHandleEnter(d, s, e)					      \
	vclassSend(vdropsiteGetClass(d), vdropsiteHANDLE_ENTER, (d, s, e))
#define vdropsiteHandleDetail(d, s, e)					      \
	vclassSend(vdropsiteGetClass(d), vdropsiteHANDLE_DETAIL, (d, s, e))
#define vdropsiteHandleLeave(d, s)					      \
	vclassSend(vdropsiteGetClass(d), vdropsiteHANDLE_LEAVE, (d, s))
#define vdropsiteHandleDrop(d, s, e)					      \
	vclassSend(vdropsiteGetClass(d), vdropsiteHANDLE_DROP, (d, s, e))
#define vdropsiteSetData(d, v)						      \
	vclassSend(vdropsiteGetClass(d), vdropsiteSET_DATA, (d, v))
#define vdropsiteSetNotify(d, n)					      \
	vclassSend(vdropsiteGetClass(d), vdropsiteSET_NOTIFY, (d, n))
#define vdropsiteSetRect(d, r)						      \
	vclassSend(vdropsiteGetClass(d), vdropsiteSET_RECT, (d, r))
#define vdropsiteSetWindow(d, w)					      \
	vclassSend(vdropsiteGetClass(d), vdropsiteSET_WINDOW, (d, w))
#define vdropsiteEnable(d)                                                    \
	vclassSend(vdropsiteGetClass(d), vdropsiteENABLE, (d))
#define vdropsiteDisable(d)					              \
	vclassSend(vdropsiteGetClass(d), vdropsiteDISABLE, (d))


/*
 * Formatting information for emacs in c-mode
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

#endif /* #ifndef vdropINCLUDED */

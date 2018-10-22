/* $Id: vkeyitem.h,v 1.11 1994/05/14 01:35:07 robert Exp $ */

/************************************************************

    vkeyitem.h
    C Interface to the Keyitem dialog item

    (c) Copyright Visix Software  1991
    All rights reserved

************************************************************/

#ifndef vkeyitemINCLUDED
#define vkeyitemINCLUDED 1

#ifndef  vportINCLUDED
#include <vport.h>		/* for v*HEADER */
#endif

#ifndef  vkeyINCLUDED
#include vkeyHEADER
#endif

#ifndef  vstrINCLUDED
#include vstrHEADER
#endif

#ifndef  vdialogINCLUDED
#include vdialogHEADER
#endif


vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * * * * * * * * * * PUBLIC CONSTANT DEFINITIONS * * * * * * * * * *
 */

/*
 * * * * * * * * * * PUBLIC TYPE DEFINITIONS * * * * * * * * * *
 */

typedef struct vkeyitem 	vkeyitem;
typedef struct vkeyitemClass	vkeyitemClass;


typedef void (*vkeyitemNoteProc)(
    vkeyitem 		*keyitem,
    vevent 		*event
    );

/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */

void vkeyitemStartup(void);


/* Keyitem Class Functions */

vkeyitemClass *vkeyitemGetDefaultClass(void);

/* Initialization and allocation */

vkeyitem *vkeyitemCreate(void);

vkeyitem *vkeyitemCreateOfClass(
    vkeyitemClass	*clas
    );
    
vkeyitem *vkeyitemClone(
    vkeyitem	    	*keyitem
    );

void vkeyitemCopy(
    vkeyitem	    	*keyitem,
    vkeyitem	    	*target
    );

void vkeyitemCopyInit(
    vkeyitem	    	*keyitem,
    vkeyitem	    	*target
    );

void vkeyitemInit(
    vkeyitem	    	*keyitem
    );

void vkeyitemInitOfClass(
    vkeyitem		*keyitem,
    vkeyitemClass	*clas
    );

void vkeyitemDestroy(
    vkeyitem	    	*keyitem   
    );

vkeyitem *vkeyitemLoad(
    vresource		resource
    );

void vkeyitemLoadInit(
    vkeyitem		*keyitem,
    vresource		resource
    );

void vkeyitemStore(
    vkeyitem		*keyitem,
    vresource		resource
    );

/* Key item attribute modification */

void vkeyitemSetNotify(
    vkeyitem		*keyitem,
    vkeyitemNoteProc	noteProc
    );

void vkeyitemSetData(
    vkeyitem		*keyitem,
    const void		*data
    );

void vkeyitemSetKeystroke(
    vkeyitem		*keyitem,
    vkeyStroke		keystroke
    );

/* Key item attribute access */

vkeyitemClass *vkeyitemGetClass(
    vkeyitem          	*keyitem
    );

vkeyitemNoteProc vkeyitemGetNotify(
    vkeyitem          	*keyitem
    );

const void *vkeyitemGetData(
    vkeyitem            *keyitem
    );

vkeyStroke vkeyitemGetKeystroke(
    vkeyitem		*keyitem
    );

/* Other */

vdialogItem *vkeyitemGetItem(
    vkeyitem		*keyitem
    );

/*
 * * * * * * * * * * PRIVATE CONSTANT DEFINITIONS * * * * * * * * * *
 */

/*
 * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * *
 */

struct vkeyitem {
    vdialogItem	    	item;
    vkeyStroke		keystroke;
};

#define vkeyitemCLASS(SUPER, ITEM)				            \
    vdialogITEM_CLASS(SUPER, ITEM, vkeyitemNoteProc);	            \
    vclassMETHOD(vkeyitemSET_KEYSTROKE,	   (ITEM *keyitem, vkeyStroke stroke))

struct vkeyitemClass {
    vkeyitemCLASS(vkeyitemClass, vkeyitem);
};

/*
 * * * * * * * * * * PRIVATE FUNCTION PROTOTYPES * * * * * * * * * *
 */

/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * *
 */

#define vkeyitemGetItem(k)		(vportBASE_OBJECT((k), item))

#define vkeyitemCreateOfClass(c)	\
	((vkeyitem *) vdialogCreateItemOfClass((vdialogItemClass *) (c)))
#define vkeyitemCreate()	   vkeyitemCreateOfClass(vkeyitemGetDefaultClass())
#define vkeyitemClone(d)     ((vkeyitem *) vdialogCloneItem(vkeyitemGetItem(d)))
#define vkeyitemInitOfClass(e,c)	\
	vdialogInitItemOfClass((vdialogItem  *) (e), (vdialogItemClass *) (c))
#define vkeyitemInit(e)	       vkeyitemInitOfClass(e, vkeyitemGetDefaultClass());
#define vkeyitemCopyInit(c,t)	\
	vdialogCopyInitItem(vkeyitemGetItem(c), vkeyitemGetItem(t))
#define vkeyitemLoad(r)          ((vkeyitem*)vdialogLoadItem(r))
#define vkeyitemLoadInit(c,r)    vdialogLoadInitItem(vkeyitemGetItem(c), r)
#define vkeyitemDestroy(d)	\
	vdialogDestroyItem(vkeyitemGetItem(d))

#define vkeyitemGetClass(d)	\
	((vkeyitemClass*) vdialogGetItemClass(vkeyitemGetItem(d)))

#define vkeyitemGetData(e)     	 	vdialogGetItemData(vkeyitemGetItem(e))
#define vkeyitemGetKeystroke(k)		((k)->keystroke)

#define vkeyitemSetNotify(k,p)		\
	 (vdialogSetItemNotify(vkeyitemGetItem(k), (vdialogItemNoteProc) (p)))
#define vkeyitemGetNotify(e)		\
	 ((vkeyitemNoteProc ) vdialogGetItemNotify(vkeyitemGetItem(e)))

/*
 * * * * * * * * * * PRIVATE FUNCTION MESSAGE DEFINITIONS * * * * * * * * * *
 */


#define vkeyitemCopy(d,t)	\
	vclassSend(vkeyitemGetClass(d), vobjectCOPY, (d, t))

#define vkeyitemStore(d,r)	\
	vclassSend(vkeyitemGetClass(d), vobjectSTORE, (d, r))

#define vkeyitemSetKeystroke(r,k)	\
	vclassSend(vkeyitemGetClass(r), vkeyitemSET_KEYSTROKE,(r, k))

#define vkeyitemSetData(e, d)	\
	vclassSend(vkeyitemGetClass(e), vdialogSET_ITEM_DATA, (e, d))


vportEND_CPLUSPLUS_EXTERN_C


#endif /* #ifndef vkeyitemINCLUDED */


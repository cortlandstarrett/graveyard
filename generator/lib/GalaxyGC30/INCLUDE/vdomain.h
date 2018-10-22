/* $Id: vdomain.h,v 1.90 1997/10/01 22:02:29 robert Exp $ */

/************************************************************

    domain.h
    C Interface file for the Domain Manager

    (c) Copyright Visix Software Inc.
    All rights reserved

************************************************************/

#ifndef vdomainINCLUDED
#define vdomainINCLUDED 1

#ifndef  vportINCLUDED		/* for v*HEADER */
#include <vport.h>
#endif

#ifndef  vstdINCLUDED		/* for vbool, vbyte */
#include vstdHEADER
#endif

#ifndef  vexINCLUDED
#include vexHEADER
#endif

#ifndef  vmutexINCLUDED
#include vmutexHEADER
#endif

#ifndef  vrectINCLUDED
#include vrectHEADER
#endif

#ifndef  vpointINCLUDED
#include vpointHEADER
#endif

#ifndef  vcharINCLUDED
#include vcharHEADER
#endif

#ifndef  vresourceINCLUDED
#include vresourceHEADER
#endif

#ifndef  vclassINCLUDED
#include vclassHEADER
#endif

#ifndef  vloadableINCLUDED
#include vloadableHEADER
#endif

#ifndef  vobjectINCLUDED
#include vobjectHEADER
#endif

#ifndef  vundoINCLUDED
#include vundoHEADER
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * * * * * * * * * * PUBLIC CONSTANT DEFINITIONS * * * * * * * * * *
 */

/*
 * Values for 'criteria' parameter to:
 *	vdomainObjectsInArea()	vdomainObjectsAtPoint(),
 *	vdomainGetObjectSet()
 */

enum {
    vdomainSELECTED		= 0x02,
    vdomainUNSELECTED		= 0x04,
    vdomainMATCHFUNC		= 0x08,
    vdomainHIDDEN		= 0x10,
    vdomainNONSELECTABLE	= 0x20,
    vdomainALL			= vdomainHIDDEN | vdomainSELECTED |
                                  vdomainUNSELECTED | vdomainNONSELECTABLE,
    vdomainINTERSECTS_BOUNDS	= 0x40,
    vdomainLOGICAL_AND		= 0x80
};

/* Values for 'positioning' parameter to vdomainMoveObjects() */

enum {
    vdomainX_RELATIVE		= 0x0001,
    vdomainX_ABSOLUTE		= 0x0002,
    vdomainY_RELATIVE		= 0x0004,
    vdomainY_ABSOLUTE		= 0x0008,
    vdomainRELATIVE		= (vdomainX_RELATIVE | vdomainY_RELATIVE),
    vdomainABSOLUTE		= (vdomainX_ABSOLUTE | vdomainY_ABSOLUTE)
};

/* Values for 'alignOption' parameter to vdomainAlignObjects() */

enum {
    vdomainALIGN_TO_OBJECTS    	= 1,
    vdomainALIGN_TO_GRID	= 2
};

/* Values for 'horizontal/verticalAlignment' params to vdomainAlignObjects() */

enum {
    vdomainALIGN_NONE		= 0,
    vdomainALIGN_LEFT		= 1,
    vdomainALIGN_TOP		= 2,
    vdomainALIGN_RIGHT		= 3,
    vdomainALIGN_BOTTOM		= 4,
    vdomainALIGN_CENTER		= 5
};

/* Values for 'hor/verticalDistribution' params to vdomainDistributeObjects() */

enum {
    vdomainDISTRIBUTE_NONE	= 0,
    vdomainDISTRIBUTE_LEFT	= 1,
    vdomainDISTRIBUTE_TOP	= 2,
    vdomainDISTRIBUTE_RIGHT	= 3,
    vdomainDISTRIBUTE_BOTTOM	= 4,
    vdomainDISTRIBUTE_CENTER	= 5
};

/* Values for 'layerOption' parameter to: vdomainLayerObjects() */

enum {
    vdomainLAYER_TOBACK		= 1,
    vdomainLAYER_TOFRONT	= 2,
    vdomainLAYER_BACK		= 3,
    vdomainLAYER_FRONT		= 4
};


/*
 * Values for OREINTATION  attribute
 */

enum {
    vdomainORIENT_BOTTOM_LEFT   = 0,
    vdomainORIENT_TOP_LEFT	= 1
};

#define vdomain_VirtualBuffer  	(_vdomainPredefs[_vdomain_VirtualBuffer])
#define vdomain_Grid		(_vdomainPredefs[_vdomain_Grid])
#define vdomain_Orientation	(_vdomainPredefs[_vdomain_Orientation])
#define vdomain_Objects		(_vdomainPredefs[_vdomain_Objects])
#define vdomain_Connected	(_vdomainPredefs[_vdomain_Connected])
#define vdomain_VirtualView  	(_vdomainPredefs[_vdomain_VirtualView])
#define vdomain_LongDomain  	(_vdomainPredefs[_vdomain_LongDomain])


/*
 * * * * * * * * * * PUBLIC TYPE DEFINITIONS * * * * * * * * * *
 */

typedef struct vdomain			vdomain;
typedef vdomain				vdomainLong;
typedef struct vdomainClass		vdomainClass;
typedef struct vdomainObserver		vdomainObserver;
typedef vdomainObserver			vdomainUndoObserver;
typedef struct vdomainObserverClass	vdomainObserverClass;
typedef struct vdomainObserverIterator	vdomainObserverIterator;
typedef struct vdomainObject		vdomainObject;
typedef struct vdomainObjectSet		vdomainObjectSet;
typedef         int			vdomainSelection;
typedef struct vdomainGrid		vdomainGrid;
typedef struct vdomainObjectSetIterator vdomainObjectSetIterator;

typedef vbool (*vdomainIntersectFunc)(
    vdomain		*domain,
    vdomainObject 	*object1,
    vdomainObject	*object2
    );

typedef vbool (*vdomainRectIntersectFunc)(
    vdomain		*domain,
    vdomainObject	*object,
    vrect 		*r
    );

typedef vbool (*vdomainRectIntersectFuncLong)(
    vdomain		*domain,
    vdomainObject	*object,
    vrectLong		*r
    );

typedef vbool	(*vdomainMatchFunc)(
    vdomain		*domain,
    vdomainSelection 	selection,
    vdomainObject	*object
    );

/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */

void vdomainStartup(void);


/* Domain Class Functions */

vdomainClass *vdomainGetDefaultClass(void);

vdomainClass *vdomainGetDefaultLongClass(void);

vdomainObserverClass *vdomainGetDefaultObserverClass(void);

vdomainObserverClass *vdomainGetDefaultUndoObserverClass(void);

/* Initialization and allocation */

vdomain *vdomainCreate(void);

vdomain *vdomainCreateLong(void);

vdomain *vdomainCreateOfClass(
    vdomainClass	*clas
    );
        
vdomain *vdomainClone(
    vdomain	    	*domain
    );

void vdomainCopy(
    vdomain	    	*domain,
    vdomain	    	*targetDomain
    );

void vdomainCopyInit(
    vdomain	    	*domain,
    vdomain	    	*targetDomain
    );

void vdomainInit(
    vdomain	    	*domain
    );

void vdomainInitLong(
    vdomain	    	*domain
    );

void vdomainInitOfClass(
    vdomain		*domain,
    vdomainClass	*clas
    );

void vdomainDestroy(
    vdomain	    	*domain
    );

vdomain *vdomainLoad(
    vresource           resource
    );

void vdomainLoadInit(
    vdomain             *domain,
    vresource           resource
    );

void vdomainStore(
    vdomain             *domain,
    vresource           resource
    );

void vdomainCopyObjectList(
    vdomain	    	*domain,
    vdomain	    	*targetDomain
    );

/* Domain Operations */

void vdomainResize(
    vdomain		*domain,
    unsigned int 	width,
    unsigned int 	height
    );
    
void vdomainSetBounds(
    vdomain		*domain,
    vrect		*bounds
    );

void vdomainSetBoundsLong(
    vdomain		*domain,
    vrectLong		*bounds
    );

vdomainObject *vdomainAddObject(
    vdomain		*domain
    );

void vdomainAddInitObject(
    vdomain		*domain,
    vdomainObject	*object
    );
    
void vdomainCopyObject(
    vdomain		*domain,
    vdomainObject	*object,
    vdomainObject	*target
    );
    
void vdomainCopyInitObject(
    vdomain		*domain,
    vdomainObject	*object,
    vdomainObject	*target
    );
    
void vdomainDestroyObject(
    vdomain		*domain,
    vdomainObject	*object
    );

void vdomainStoreObject(
    vdomain		*domain,
    vdomainObject	*object,
    vresource		resource
    );

void vdomainLoadInitObject(
    vdomain		*domain,
    vdomainObject	*object,
    vresource		resource
    );

void vdomainRemoveObjects(
    vdomain		*domain,
    vdomainObjectSet	*objectsSet
    );

vrect *vdomainGetBounds(
    vdomain		*domain
    );

vrectLong *vdomainGetBoundsLong(
    vdomain		*domain
    );

vrect *vdomainLimitRect(
    vdomain		*domain
    );

vrectLong *vdomainLimitRectLong(
    vdomain		*domain
    );

long vdomainObjectCount(
    vdomain		*domain
    );

/* Domain attribute modification */

void vdomainSetData(
    vdomain		*domain,
    void		*data
    );

void vdomainSetGrid(
    vdomain		*domain,
    vdomainGrid		*grid
    );
    
void vdomainSetVirtualBounds(
    vdomain		*domain,
    int 		virtualBounds
    );

void vdomainSetVirtualBuffer(
    vdomain		*domain,
    vpoint		*virtualBuffer
    );

void vdomainSetVirtualView(
    vdomain		*domain,
    vrect		*virtualView
    );

void vdomainSetVirtualViewLong(
    vdomain		*domain,
    vrectLong		*virtualView
    );

void vdomainSetOrientation(
    vdomain		*domain,
    int 		orientation
    );

void vdomainSetIntersectFunc(
    vdomain			*domain,
    vdomainIntersectFunc	intersectFunc
    );

void vdomainSetRectIntersectFunc(
    vdomain			*domain,
    vdomainRectIntersectFunc	rectIntersectFunc
    );

void vdomainSetRectIntersectFuncLong(
    vdomain			 *domain,
    vdomainRectIntersectFuncLong rectIntersectFunc
    );

void vdomainSetUndoObserver(
    vdomain		    	*domain,
    vdomainObserverClass	*observerClass
    );

void vdomainSetUndoActionList(
    vdomain		    	*domain,
    vundoActionList	  	*list
    );

/* Domain attribute access */

vobject *vdomainGetObject(
    vdomain		*domain
    );

vloadable *vdomainGetLoadable(
    vdomain		*domain
    );

vdomainClass *vdomainGetClass(
    vdomain		*domain
    );

void *vdomainGetData(
    vdomain		*domain
    );
    
vdomainGrid *vdomainGetGrid(
    vdomain		*domain
    );

vbool vdomainGetVirtualBounds(
    vdomain		*domain
    );

vpoint *vdomainGetVirtualBuffer(
    vdomain		*domain
    );

vrect *vdomainGetVirtualView(
    vdomain		*domain
    );

vrectLong *vdomainGetVirtualViewLong(
    vdomain		*domain
    );

vbyte vdomainGetOrientation(
    vdomain		*domain
    );
 
vdomainIntersectFunc vdomainGetIntersectFunc(
    vdomain		*domain
    );

vdomainRectIntersectFunc vdomainGetRectIntersectFunc(
    vdomain		*domain
    );

vdomainRectIntersectFuncLong vdomainGetRectIntersectFuncLong(
    vdomain		*domain
    );

vdomainObserverClass *vdomainGetUndoObserver(
    vdomain		*domain
    );

vundoActionList *vdomainGetUndoActionList(
    vdomain		*domain
    );
 
/* Object Operations */

void vdomainMoveObjects(
    vdomain		*domain,
    vdomainObjectSet	*objectSet,
    int			deltaX,
    int			deltaY,
    int			positioning
    );

void vdomainScaleObjects(
    vdomain		*domain,
    vdomainObjectSet	*objectSet,
    double		width,
    double		height
    );

void vdomainResizeObjects(
    vdomain		*domain,
    vdomainObjectSet	*objectSet,
    int			width,
    int			height
    );

void vdomainSelectAll(
    vdomain		*domain,
    vdomainSelection	selection,
    int 		select,
    int 		selectHidden
    );
    
void vdomainAlignObjects(
    vdomain		*domain,
    vdomainObjectSet	*objectSet,
    int			alignOption,
    int			horizontalAlignment,
    int			verticalAlignment
    );

void vdomainDistributeObjects(
    vdomain		*domain,
    vdomainObjectSet	*objectSet,
    int			horizontalDistribution,
    int			verticalDistribution
    );

void vdomainLayerObjects(
    vdomain		*domain,
    vdomainObjectSet	*objectSet,
    int			layerOption
    );

void vdomainShuffleObjects(
    vdomain		*domain,
    vdomainObject	*moveObject,
    vdomainObject	*targetObject,
    int 		behind
    );

vdomainObject *vdomainTopObject(
    vdomain		*domain
    );

vdomainObject *vdomainNextObjectBehind(
    vdomainObject	*targetObject
    );

vdomainObject *vdomainNextObjectInFront(
    vdomainObject	*targetObject
    );

void vdomainSortObjects(
    vdomain		*domain,
    vdomainObjectSet	*objectSet
    );

vbool vdomainObjectsIntersect(
    vdomain		*domain,
    vdomainObject	*object1,
    vdomainObject	*object2
    );

vbool vdomainObjectIntersectsRect(
    vdomain		*domain,
    vdomainObject	*object,
    vrect		*rect
    );

vbool vdomainObjectIntersectsRectLong(
    vdomain		*domain,
    vdomainObject	*object,
    vrectLong		*rect
    );

/* Object attributes modification */

void vdomainSetObjectData(
    vdomain		*domain,
    vdomainObjectSet	*objectSet,
    void		*data
    );
    
void vdomainSetObjectBounds(
    vdomain		*domain,
    vdomainObjectSet	*objectSet,
    vrect		*bounds
    );

void vdomainSetObjectBoundsLong(
    vdomain		*domain,
    vdomainObjectSet	*objectSet,
    vrectLong		*bounds
    );
    
void vdomainSetObjectType(
    vdomain		*domain,
    vdomainObjectSet	*objectSet,
    unsigned int 	type
    );

void vdomainSetObjectAnchored(
    vdomain		*domain,
    vdomainObjectSet	*objectSet,
    int 		anchored
    );
  
void vdomainSetObjectOpaque(
    vdomain		*domain,
    vdomainObjectSet	*objectSet,
    int 		opaque
    );
      
void vdomainHideObjects(
    vdomain		*domain,
    vdomainObjectSet	*objectSet
    );
    
void vdomainShowObjects(
    vdomain		*domain,
    vdomainObjectSet	*objectSet
    );
    
void vdomainSetObjectUnselectable(
    vdomain		*domain,
    vdomainObjectSet	*objectSet,
    int 		unselectable
    );
    
void vdomainSetObjectSelectNotify(
    vdomain		*domain,
    vdomainObjectSet	*objectSet,
    int 		selectNotify
    );
    
/* Object attributes access */

void *vdomainGetObjectData(
    vdomain		*domain,
    vdomainObject	*object
    );
    
vrect *vdomainGetObjectBounds(
    vdomain		*domain,
    vdomainObject	*object
    );
    
vrectLong *vdomainGetObjectBoundsLong(
    vdomain		*domain,
    vdomainObject	*object
    );
    
unsigned int vdomainGetObjectType(
    vdomain		*domain,
    vdomainObject	*object
    );

vbool vdomainIsObjectAnchored(
    vdomain		*domain,
    vdomainObject	*object
    );
    
vbool vdomainIsObjectOpaque(
    vdomain		*domain,
    vdomainObject	*object
    );
    
vbool vdomainIsObjectHidden(
    vdomain		*domain,
    vdomainObject	*object
    );
    
vbool vdomainIsObjectUnselectable(
    vdomain		*domain,
    vdomainObject	*object
    );
    
vbool vdomainIsObjectSelectNotify(
    vdomain		*domain,
    vdomainObject	*object
    );
    
/* Object Connectivity */

void vdomainConnectObjects(
    vdomain		*domain,
    vdomainObject	*object1,
    vdomainObject	*object2
    );

void vdomainDisconnectObjects(
    vdomain		*domain,
    vdomainObjectSet	*objectSet
    );

vdomainObjectSet *vdomainGetConnectedSet(
    vdomain		*domain,
    vdomainObject	*object
    );

/* Spatial operations */

vdomainObjectSet *vdomainObjectsInArea(
    vdomain		*domain,
    vrect		*area,
    vdomainSelection	selection,
    int			oneObjectOnly,
    int			enclosure,
    int			criteria,
    vdomainMatchFunc	matchFunc
    );

vdomainObjectSet *vdomainObjectsInAreaLong(
    vdomain		*domain,
    vrectLong		*area,
    vdomainSelection	selection,
    int			oneObjectOnly,
    int			enclosure,
    int			criteria,
    vdomainMatchFunc	matchFunc
    );

vdomainObjectSet *vdomainObjectsAtPoint(
    vdomain		*domain,
    vpoint	    	*point,
    vdomainSelection	selection,
    int			oneObjectOnly,
    int		 	criteria,
    vdomainMatchFunc	matchFunc
    );

vdomainObjectSet *vdomainObjectsAtPointLong(
    vdomain		*domain,
    vpointLong	    	*point,
    vdomainSelection	selection,
    int			oneObjectOnly,
    int		 	criteria,
    vdomainMatchFunc	matchFunc
    );

/* Object Sets */

vdomainObjectSet *vdomainCreateObjectSet(
    vdomainObject	*initObject
    );

void vdomainAddToObjectSet(
    vdomainObjectSet	**objectSet,
    vdomainObject	*object
    );

void vdomainRemoveFromObjectSet(
    vdomainObjectSet	*objectSet,
    vdomainObject	*object
    );

vbool vdomainFoundInObjectSet(
    vdomainObjectSet	*objectSet,
    vdomainObject	*object
    );

vdomainObjectSet *vdomainCloneObjectSet(
    vdomainObjectSet	*objectSet
    );

vdomainObjectSet *vdomainCopyObjectSet(
    vdomainObjectSet	*objectSet,
    vdomainObjectSet	*targetSet
    );

void vdomainDestroyObjectSet(
    vdomainObjectSet	*objectSet
    );

int vdomainGetObjectSetCount(
    vdomainObjectSet	*objectSet
    );

vdomainObjectSet *vdomainObjectToSet(
    vdomainObject	*object
    );

vdomainObjectSet *vdomainGetObjectSet(
    vdomain		*domain,
    vdomainSelection	selection,
    int			criteria,
    vdomainMatchFunc	matchFunc
    );

void vdomainInitObjectSetIterator(
    vdomainObjectSetIterator	*iterator,
    vdomainObjectSet		*objectSet
    );

int vdomainNextObjectSetIterator(
    vdomainObjectSetIterator	*iterator
    );

void vdomainDestroyObjectSetIterator(
    vdomainObjectSetIterator	*iterator
    );

vdomainObject *vdomainGetObjectSetIteratorObject(
    vdomainObjectSetIterator	*iterator
    );

/* Selection operations */

vdomainSelection vdomainCreateSelection(
    vdomain		*domain
    );

void vdomainDestroySelection(
    vdomain		*domain,
    vdomainSelection	selection
    );

int vdomainSelectedObjects(
    vdomain		*domain,
    vdomainSelection	selection
    );

void vdomainSelectObjects(
    vdomain		*domain,
    vdomainSelection	selection,
    vdomainObjectSet	*objectSet
    );

void vdomainUnselectObjects(
    vdomain		*domain,
    vdomainSelection	selection,
    vdomainObjectSet	*objectSet
    );

vbool vdomainIsObjectSelected(
    vdomain		*domain,
    vdomainSelection	selection,
    vdomainObject	*object
    );
    
/* Observer operations */

vdomainObserver *vdomainCreateObserver(void);

vdomainObserver *vdomainCreateObserverOfClass(
    vdomainObserverClass	*clas
    );

vdomainObserver *vdomainCloneObserver(
    vdomainObserver	*observer
    );

void vdomainCopyObserver(
    vdomainObserver	*observer,
    vdomainObserver	*target
    );

void vdomainCopyInitObserver(
    vdomainObserver	*observer,
    vdomainObserver	*target
    );

void vdomainInitObserver(
    vdomainObserver	*observer
    );

void vdomainInitObserverOfClass(
    vdomainObserver	*observer,
    vdomainObserverClass	*clas
    );

void vdomainDestroyObserver(
    vdomainObserver	*observer
    );

/* Observer Operations */

void vdomainInstallObserver(
    vdomain		*domain,
    vdomainObserver	*observer
    );

void vdomainInstallObserverOwned(
    vdomain		*domain,
    vdomainObserver	*observer
    );

void vdomainUninstallObserver(
    vdomain		*domain,
    vdomainObserver	*observer
    );

void vdomainInitObserverIterator(
    vdomainObserverIterator	*iterator,
    vdomain			*domain
    );

vbool vdomainNextObserverIterator(
    vdomainObserverIterator	*iterator
    );

void vdomainDestroyObserverIterator(
    vdomainObserverIterator	*iterator
    );

vdomainObserver *vdomainGetObserverIteratorObserver(
    vdomainObserverIterator	*iterator
    );

/* Observer attribute modification and access */
 
void vdomainSetObserverData(
    vdomainObserver	*observer,
    void		*data
    );

void vdomainDisableObserver(
    vdomainObserver	*observer
    );

void vdomainEnableObserver(
    vdomainObserver	*observer
    );

vdomainObserverClass *vdomainGetObserverClass(
    vdomainObserver	*observer
    );

void *vdomainGetObserverData(
    vdomainObserver	*observer
    );

vbool vdomainObserverIsEnabled(
    vdomainObserver	*observer
    );

vdomain *vdomainGetObserverOwner(
    vdomainObserver	*observer
    );

vobject *vdomainGetObserverObject(
    vdomainObserver	*observer
    );

vloadable *vdomainGetObserverLoadable(
    vdomainObserver	*observer
    );

/* Other Routines */

void vdomainBoundingRect(
    vdomain		*domain,
    vrect		*boundingRect,
    vdomainObjectSet	*objectSet
    );

void vdomainBoundingRectLong(
    vdomain		*domain,
    vrectLong		*boundingRect,
    vdomainObjectSet	*objectSet
    );

vbool vdomainIsLong(
    vdomain		*domain
    );

void vdomainSnapPointToGrid(
    vdomain		*domain,
    long		x,
    long		y,
    long		*gx,
    long		*gy
    );

/*
 * * * * * * * * * * PRIVATE CONSTANT DEFINITIONS * * * * * * * * * *
 */

/* Values for 'attributes' field in the vdomain structure */

enum {
    _vdomainVIRTUAL_BOUNDS	= 0x0001,
    _vdomainHORZ_LOCKED		= 0x0002,
    _vdomainVERT_LOCKED		= 0x0004
};

/* Values for 'attributes' field in the vdomainObject structure */

enum {
    _vdomainOBJ_HIDDEN		= 0x0001,
    _vdomainOBJ_REDRAW		= 0x0002,
    _vdomainOBJ_ANCHORED	= 0x0004,
    _vdomainOBJ_UNSELECTABLE	= 0x0008,
    _vdomainOBJ_SELECTNOTIFY	= 0x0010,
    _vdomainOBJ_OPAQUE		= 0x0040,
    _vdomainOBJ_OVERLAPPED	= 0x0200,
    _vdomainOBJ_LAST		= 0x0400,
    _vdomainOBJ_USED		= 0x0800,
    _vdomainOBJ_MARKED		= 0x1000
};

/* Values for 'flag' field in vdomainObserver */

enum {
    _vdomainOBSERVER_OWNED	= 0x0001,
    _vdomainOBSERVER_DISABLED   = 0x0002
};


#define _vdomainSET_THRESHOLD	     16
#define _vdomainSTATIC_SETS	     10
#define _vdomainSETMASK		     ((1 << vdomainSTATIC_SETS) - 1)
#define _vdomainATTR_MASK	  (_vdomainOBJ_MARKED | _vdomainOBJ_USED | \
                                  _vdomainOBJ_LAST   | _vdomainOBJ_OVERLAPPED)

/*
 * Global Internal Strings
 */

enum {
    _vdomain_VirtualBuffer,
    _vdomain_Grid,
    _vdomain_Orientation,
    _vdomain_Objects,
    _vdomain_Connected,
    _vdomain_VirtualView,
    _vdomain_LongDomain,
    _vdomain_Count
};

/*
 * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * *
 */

struct vdomainObject {
    union {
	vrectLong		longBounds;
	vrect			bounds;
    } u;
    unsigned short		attributes;
    unsigned short		type;
    long			selected;
    void			*data;
    vdomain			*domain;
    vdomainObject		*above;
    vdomainObject		*behind;
    vdomainObject		*connected;
};

struct vdomainObjectSet {
    long		setSize;
    long		numObjects;
    vdomainObject	*objects[1];
};


typedef struct _vdomainBigObjectSet {
    long		setSize;
    long		numObjects;
    vdomainObject	*objects[_vdomainSET_THRESHOLD];
} _vdomainBigObjectSet;


struct vdomainGrid {
    int		xSpacing;
    int		ySpacing;
    int		xSkew;
    int		ySkew;
};

struct vdomainObjectSetIterator {
    vdomainObjectSet		*objectSet;
    vdomainObject		**object;
    int				count;
};

typedef struct _vdomainSelection {
    vbool			unused;
    int				selectCount;
} _vdomainSelection;

/*
 * vdomain
 */

typedef struct _vdomainShortInfo {
    vrect			bounds;
    vrect			virtualView;
    vrect			limitRect;
    vdomainRectIntersectFunc	rectIntersectFunc;
} _vdomainShortInfo;

typedef struct _vdomainLongInfo {
    vrectLong			 bounds;
    vrectLong			 virtualView;
    vrectLong			 limitRect;
    vdomainRectIntersectFuncLong rectIntersectFunc;
} _vdomainLongInfo;

struct vdomain {
    vobject			object;

    vpoint		 	virtualBuffer;
    vdomainGrid			grid;
    void			*data;
    long			numberObjects;

    union {
	_vdomainShortInfo	info;
	_vdomainLongInfo	longInfo;
    } u;

    unsigned int		limitRectDirty	: 4;
    unsigned int		longDomain	: 4;
    unsigned int		orientation	: 8;
    unsigned int		attributes	: 16;

    vdomainIntersectFunc	intersectFunc;

    short			selections;
    short			usedSelections;
    _vdomainSelection		*selectionList;

    short			observers;
    vdomainObserver		**observerList;	/* Array of observers  */

    vdomainObject		*topObject;

    vundoActionList		*undoActions;
};

vportALIAS(vdomainLong, vdomain)

/*
 * vdomainObserver
 */

struct vdomainObserver {
    vobject			object;
    void			*data;
    int				flags;
    vdomainObserver		*id;
    vdomain			*owner;
};

vportALIAS(vdomainUndoObserver, vdomainObserver)

struct vdomainObserverIterator {
    vdomainObserver		**scan;
    int				count;
    vdomain			*domain;
};

typedef struct  {
    vdomainObjectSet  setOfOne;
} _vdomainThreadLocals;

/*
 * Domain Class Definition
 */

#define vdomainCLASS(SUPER, DOMAIN, OBJECT, OBJECTSET, SELECTION)	      \
 vobjectCLASS(SUPER, DOMAIN);						      \
 vclassMETHOD(vdomainSET_BOUNDS,        (DOMAIN *domain, vrect *bounds));     \
 vclassMETHOD(vdomainSET_BOUNDS_LONG,   (DOMAIN *domain, vrectLong *bounds)); \
 vclassMETHOD_RET(vdomainADD_OBJECT,    OBJECT *, (DOMAIN *domain));          \
 vclassMETHOD(vdomainADD_INIT_OBJECT,   (DOMAIN *domain, OBJECT *object));    \
 vclassMETHOD(vdomainCOPY_OBJECT,       (DOMAIN *domain, OBJECT *object,      \
					 OBJECT *target));		      \
 vclassMETHOD(vdomainCOPY_INIT_OBJECT,  (DOMAIN *domain, OBJECT *object,      \
					 OBJECT *target));  		      \
 vclassMETHOD(vdomainDESTROY_OBJECT,    (DOMAIN *domain, OBJECT *object));    \
 vclassMETHOD(vdomainSTORE_OBJECT,      (DOMAIN *domain, OBJECT *object,      \
					 vresource resource));    	      \
 vclassMETHOD(vdomainLOAD_INIT_OBJECT,  (DOMAIN *domain, OBJECT *object,      \
					 vresource resource));  	      \
 vclassMETHOD(vdomainREMOVE_OBJECTS,    (DOMAIN *domain, OBJECTSET *objectSet));	      \
 vclassMETHOD(vdomainCOPY_OBJECT_LIST,  (DOMAIN *domain, DOMAIN *target));    \
 vclassMETHOD(vdomainMOVE_OBJECTS,      (DOMAIN *domain, OBJECTSET *objectSet,\
					 int deltaX, int deltaY, 	      \
					 int positioning));		      \
 vclassMETHOD(vdomainSCALE_OBJECTS,     (DOMAIN *domain, OBJECTSET *objectSet,\
					 double width, double height));       \
 vclassMETHOD(vdomainRESIZE_OBJECTS,    (DOMAIN *domain, OBJECTSET *objectSet,\
					 int width, int height));   	      \
 vclassMETHOD(vdomainALIGN_OBJECTS,     (DOMAIN *domain, OBJECTSET *objectSet,\
					 int alignOptions, 		      \
					 int horizontalAlignment,	      \
					 int verticalAlignment));	      \
 vclassMETHOD(vdomainDISTRIBUTE_OBJECTS,(DOMAIN *domain, OBJECTSET *objectSet,\
					 int horizontalDistribution,	      \
					 int verticalDistribution));	      \
 vclassMETHOD(vdomainLAYER_OBJECTS,     (DOMAIN *domain, OBJECTSET *objectSet,\
					 int layerOption));		      \
 vclassMETHOD(vdomainSHUFFLE_OBJECTS,   (DOMAIN *domain, OBJECT *moveObject,  \
					 OBJECT *targetObject, int behind));  \
 vclassMETHOD(vdomainCONNECT_OBJECTS,   (DOMAIN *domain, OBJECT *object1,     \
					 OBJECT *object2));   		      \
 vclassMETHOD(vdomainDISCONNECT_OBJECTS,(DOMAIN *domain, OBJECTSET *objectSet));             \
 vclassMETHOD_RET(vdomainGET_CONNECTED_SET, OBJECTSET *,	              \
		                        (DOMAIN *domain, OBJECT *object));    \
 vclassMETHOD(vdomainSORT_OBJECTS,      (DOMAIN *domain, OBJECTSET *objectSet));    	      \
 vclassMETHOD(vdomainHIDE_OBJECTS,	(DOMAIN *domain, OBJECTSET *objectSet));  	      \
 vclassMETHOD(vdomainSHOW_OBJECTS,	(DOMAIN *domain, OBJECTSET *objectSet));  	      \
 vclassMETHOD(vdomainSET_OBJECT_BOUNDS, (DOMAIN *domain, OBJECTSET *objectSet,\
					 vrect *bounds)); 		      \
 vclassMETHOD(vdomainSET_OBJECT_BOUNDS_LONG,				      \
	                                (DOMAIN *domain, OBJECTSET *objectSet,\
					 vrectLong *bounds)); 		      \
 vclassMETHOD(vdomainSELECT_OBJECTS,    (DOMAIN *domain, SELECTION selection, \
					 OBJECTSET *objectSet)); 	      \
 vclassMETHOD(vdomainUNSELECT_OBJECTS,	(DOMAIN *domain, SELECTION selection, \
					 OBJECTSET *objectSet));	      \
 vclassMETHOD(vdomainBOUNDING_RECT,     (DOMAIN *domain, vrect *boundingRect, \
					 OBJECTSET *objectSet)); 	      \
 vclassMETHOD(vdomainBOUNDING_RECT_LONG,(DOMAIN *domain, 		      \
					 vrectLong *boundingRect,	      \
					 OBJECTSET *objectSet)); 	      \
 vclassMETHOD(vdomainSELECT_ALL,	(DOMAIN *domain, SELECTION selection, \
					 int select, int selectHidden));      \
 vclassMETHOD(vdomainRECALC_LIMIT_RECT, (DOMAIN *domain, vrect *rect));       \
 vclassMETHOD(vdomainRECALC_LIMIT_RECT_LONG,				      \
	                                (DOMAIN *domain, vrectLong *rect));   \
 vclassMETHOD(vdomainSNAP_POINT_TO_GRID,(DOMAIN *domain, long x, long y,      \
					 long *gx, long *gy));		      \
 vclassMETHOD(vdomainOBSERVE_ADD,	(DOMAIN *domain, OBJECT *object));    \
 vclassMETHOD(vdomainOBSERVE_REMOVE,	(DOMAIN *domain, OBJECTSET *objectSet)); 	      \
 vclassMETHOD(vdomainOBSERVE_RESIZE_DOMAIN,(DOMAIN *domain, vrect *bounds));  \
 vclassMETHOD(vdomainOBSERVE_RESIZE_DOMAIN_LONG,			      \
	                                (DOMAIN *domain, vrectLong *bounds)); \
 vclassMETHOD(vdomainOBSERVE_MOVE,      (DOMAIN *domain, OBJECTSET *objectSet,\
					 vpoint *delta, int positioning,      \
					 int before));			      \
 vclassMETHOD(vdomainOBSERVE_MOVE_LONG, (DOMAIN *domain, OBJECTSET *objectSet,\
					 vpointLong *delta, int positioning,  \
					 int before));			      \
 vclassMETHOD(vdomainOBSERVE_RESIZE,    (DOMAIN *domain, OBJECTSET *objectSet,\
					 int before));	  		      \
 vclassMETHOD(vdomainOBSERVE_HIDE,	(DOMAIN *domain, OBJECTSET *objectSet,\
					 int hide));     		      \
 vclassMETHOD(vdomainOBSERVE_LAYER,     (DOMAIN *domain, OBJECT *object,      \
					 OBJECT *wasBehind));   	      \
 vclassMETHOD(vdomainOBSERVE_ORIENT,	(DOMAIN *domain, int orientation));   \
 vclassMETHOD(vdomainOBSERVE_SELECT,    (DOMAIN *domain, OBJECTSET *objectSet,\
					 SELECTION selection, int bSelected));\
 vclassMETHOD(vdomainOBSERVE_DESTROY,   (DOMAIN *domain))

struct vdomainClass {
    vdomainCLASS(vdomainClass, vdomain, vdomainObject, vdomainObjectSet,
		 vdomainSelection);
};

/*
 * Domain Observer Class
 */

#define vdomainObserverCLASS(SUPER, OBSERVER, SEL, OBJECT, OBJSET)  	      \
 vobjectCLASS(SUPER, OBSERVER);    			   		      \
 vclassMETHOD(vdomainObserverADD,    (OBSERVER *observer, OBJECT *object));   \
 vclassMETHOD(vdomainObserverREMOVE, (OBSERVER *observer, OBJSET *objectSet));\
 vclassMETHOD(vdomainObserverRESIZE_DOMAIN,				      \
	                             (OBSERVER *observer, vrect *bounds));    \
 vclassMETHOD(vdomainObserverRESIZE_DOMAIN_LONG,			      \
	                             (OBSERVER *observer, vrectLong *bounds));\
 vclassMETHOD(vdomainObserverMOVE,   (OBSERVER *observer, OBJSET *objectSet,  \
				      vpoint *delta, int positioning, 	      \
				      int before));			      \
 vclassMETHOD(vdomainObserverMOVE_LONG,(OBSERVER *observer, OBJSET *objectSet,\
				      vpointLong *delta, int positioning,     \
				      int before));			      \
 vclassMETHOD(vdomainObserverRESIZE, (OBSERVER *observer, OBJSET *objectSet,  \
				      int before));	  		      \
 vclassMETHOD(vdomainObserverHIDE,   (OBSERVER *observer, OBJSET *objectSet,  \
				      int hide));        		      \
 vclassMETHOD(vdomainObserverLAYER,  (OBSERVER *observer, OBJECT *object,     \
				      OBJECT *wasBehind));     		      \
 vclassMETHOD(vdomainObserverORIENT, (OBSERVER *observer, int orientation));  \
 vclassMETHOD(vdomainObserverSELECT, (OBSERVER *observer, OBJSET *objectSet,  \
				      SEL selection, int bSelected));          \
 vclassMETHOD(vdomainObserverDESTROY,(OBSERVER *observer))

struct vdomainObserverClass {
    vdomainObserverCLASS(vdomainObserverClass, vdomainObserver,
			 vdomainSelection,  vdomainObject,
		         vdomainObjectSet);
};


/*
 * * * * * * * * * * PRIVATE FUNCTION PROTOTYPES * * * * * * * * * *
 */

vdomainObject *_vdomainAllocObject(void);
void 	_vdomainRecalcVirtualBounds(vdomain *domain);
void 	_vdomainCleanupObjectSets(void);
vdomainObject *_vdomainAddObject(vdomain *domain);
void 	_vdomainAddInitObject(vdomain *domain, vdomainObject *object);
void 	_vdomainCopyObject(vdomain *domain, vdomainObject *object,
			   vdomainObject *target);
void 	_vdomainCopyInitObject(vdomain *domain, vdomainObject *object,
			       vdomainObject *target);
void 	_vdomainRemoveObjects(vdomain *domain, vdomainObjectSet *set);
void 	_vdomainMoveObjects(vdomain *domain, vdomainObjectSet *set,
			    int deltaX, int deltaY, int positioning);
void 	_vdomainSelectObjects(vdomain *domain, vdomainSelection selection,
			      vdomainObjectSet *set);
void 	_vdomainUnselectObjects(vdomain *domain, vdomainSelection selection,
				vdomainObjectSet *set);
void 	_vdomainBoundingRect(vdomain *domain, vrect *rect,
			     vdomainObjectSet *set);
void 	_vdomainBoundingRectLong(vdomain *domain, vrectLong *rect,
				 vdomainObjectSet *set);
void 	_vdomainSelectAll(vdomain *domain, vdomainSelection selection,
			  int select, int selectHidden);
void	_vdomainCleanupPool(void);
void 	_vdomainRecalcLimitRect(vdomain *domain, vrect *rect);
void 	_vdomainRecalcLimitRectLong(vdomain *domain, vrectLong *rect);
void 	_vdomainRecalcLimitRect2(vdomain *domain, vrect *rect);
void 	_vdomainRecalcLimitRect2Long(vdomain *domain, vrectLong *rect);
void	_vdomainSnapPointToGrid(vdomain *domain, long x, long y, long *gx,
				long *gy);
void 	_vdomainScaleObjects(vdomain *domain, vdomainObjectSet *set,
			     double width, double height);
void 	_vdomainResizeObjects(vdomain *domain, vdomainObjectSet *set,
			      int width, int height);
void 	_vdomainAlignObjects(vdomain *domain, vdomainObjectSet *set,
			     int alignOption, int horizAlignment,
			     int vertAlignment);
void	_vdomainDistributeObjects(vdomain *domain, vdomainObjectSet *set,
				  int horizDistribution, int vertDistribution);
void	_vdomainLayerObjects(vdomain *domain, vdomainObjectSet *set,
			     int layerOption);
void	_vdomainShuffleObjects(vdomain *domain, vdomainObject *moveObject,
			       vdomainObject *targetObject, int behind);
void	_vdomainConnectObjects(vdomain *domain, vdomainObject *object1,
			       vdomainObject *object2);
void 	_vdomainDisconnectObjects(vdomain *domain, vdomainObjectSet *set);
vdomainObjectSet *_vdomainGetConnectedSet(vdomain *domain,
					  vdomainObject *object);
void	_vdomainSortObjects(vdomain *domain, vdomainObjectSet *set);
void	_vdomainSetObjectBounds(vdomain *domain, vdomainObjectSet *set,
				vrect *rect);
void	_vdomainSetObjectBoundsLong(vdomain *domain, vdomainObjectSet *set,
				    vrectLong *rect);
void	_vdomainShowObjects(vdomain *domain, vdomainObjectSet *set);
void	_vdomainHideObjects(vdomain *domain, vdomainObjectSet *set);
void	_vdomainSetAttributes(vdomainObjectSet *objectSet, int attributes,
			      vbool set);
void	_vdomainDestroyObject(vdomain *domain, vdomainObject *object);
void	_vdomainStoreObject(vdomain *domain, vdomainObject *object,
			    vresource resource);
void	_vdomainLoadInitObject(vdomain *domain, vdomainObject *object,
			       vresource resource);
void     _vdomainStartup(void);
void     _vdomainInitObserverClass(void);
void	 _vdomainInitUndoObserverClass(void);
_vdomainThreadLocals *_vdomainGetThreadLocals(void);

vdomainObject *_vdomainNextObjectBehind(vdomain *domain,
					vdomainObject *targetObject);
vdomainObject *_vdomainNextObjectInFront(vdomain *domain,
					 vdomainObject *targetObject);

void     _vdomainObserveAdd(vdomain *domain, vdomainObject *object);
void	 _vdomainObserveRemove(vdomain *domain, vdomainObjectSet *set);
void	 _vdomainObserveResizeDomain(vdomain *domain, vrect *rect);
void	 _vdomainObserveResizeDomainLong(vdomain *domain, vrectLong *rect);
void	 _vdomainObserveMove(vdomain *domain, vdomainObjectSet *set,
			     vpoint *delta, int positioning, int before);
void	 _vdomainObserveMoveLong(vdomain *domain, vdomainObjectSet *set,
				 vpointLong *delta, int positioning,
				 int before);
void	 _vdomainObserveResize(vdomain *domain, vdomainObjectSet *set,
			       int before);
void	 _vdomainObserveHide(vdomain *domain, vdomainObjectSet *set,
			     int hide);
void	 _vdomainObserveLayer(vdomain *domain, vdomainObject *object,
			      vdomainObject *wasBehind);
void	 _vdomainObserveOrient(vdomain *domain, int orientation);
void	 _vdomainObserveSelect(vdomain *domain, vdomainObjectSet *set,
			       vdomainSelection selection, int bSelected);
void	 _vdomainObserveDestroy(vdomain *domain);


/*
 * * * * * * * * * DOMAIN MANAGER PRIVATE VARIABLES * * * * * * * * * *
 */

typedef struct _vdomainGlobals {
    vbool		 allocObjectSets;
    vdomainClass	 *defaultClass;
    vdomainClass	 *defaultLongClass;
    vbool	         observerNotifyOff;
    vdomainObserverClass *defaultObserverClass;
    vdomainObserverClass *defaultUndoObserverClass;
    vundoActionClass     *defaultUndoMoveClass;
    vundoActionClass     *defaultUndoResizeClass;
    vundoActionClass     *defaultUndoLayerClass;
    vundoActionClass     *defaultUndoAddClass;
    vundoActionClass     *defaultUndoRemoveClass;
} _vdomainGlobals;


extern vportLINK void 			**_vdomainMaster;
extern vportLINK const vchar 		*_vdomainPredefs[];
extern vportLINK const vexClass		_vdomainNoSelectionExceptionClass;
extern vportLINK const vexClass		_vdomainWrongTypeExceptionClass; 
extern vportLINK vmutex			_vdomainMutex;
extern vportLINK vbool			_vdomainInitialized;

/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * *
 */

#define vdomainGetObject(d)		vportBASE_OBJECT(d, object)
#define vdomainGetLoadable(d)		vobjectGetLoadable(vdomainGetObject(d))

#define vdomainCreateOfClass(c)		\
	((vdomain *) vloadableCreateOfClass((vloadableClass *)(c)))
#define vdomainCreate()			\
	vdomainCreateOfClass(vdomainGetDefaultClass())
#define vdomainCreateLong()		\
	vdomainCreateOfClass(vdomainGetDefaultLongClass())
#define vdomainDestroy(d)		vloadableDestroy(vdomainGetLoadable(d))

#define vdomainInitOfClass(d, c)	\
	vloadableInitOfClass(vdomainGetLoadable(d), (vloadableClass*)(c))
#define vdomainInit(i)			\
	vdomainInitOfClass(i, vdomainGetDefaultClass())
#define vdomainInitLong(i)		\
	vdomainInitOfClass(i, vdomainGetDefaultLongClass())
#define vdomainClone(d)			\
	((vdomain *) vloadableCloneOfSubclass(vdomainGetLoadable(d),	      \
				  (vloadableClass *) vdomainGetDefaultClass()))
#define vdomainCopyInit(c,t)		\
	vloadableCopyInitOfSubclass(vdomainGetLoadable(c),		      \
				    vdomainGetLoadable(t),		      \
				   (vloadableClass *) vdomainGetDefaultClass())
#define vdomainCopy(d, t)		\
	vloadableCopy(vdomainGetLoadable(d), vdomainGetLoadable(t))
#define vdomainLoad(r)			\
	((vdomain *) vloadableLoadOfSubclass(r,				      \
				  (vloadableClass *) vdomainGetDefaultClass()))
#define vdomainLoadInit(d,r)		\
	vloadableLoadInitOfSubclass(vdomainGetLoadable(d), r,		      \
				   (vloadableClass *) vdomainGetDefaultClass())
#define vdomainStore(d, r)		\
	vloadableStore(vdomainGetLoadable(d), r)
#define vdomainGetObserverObject(o)	vportBASE_OBJECT(o, object)

#define vdomainGetObserverLoadable(o)	\
	vobjectGetLoadable(vdomainGetObserverObject(o))
#define vdomainCreateObserverOfClass(c)	\
	((vdomainObserver *) vloadableCreateOfClass((vloadableClass *)(c)))
#define vdomainCreateObserver()		\
	vdomainCreateObserverOfClass(vdomainGetDefaultObserverClass())
#define vdomainDestroyObserver(g)	\
	vloadableDestroy(vdomainGetObserverLoadable(g))
#define vdomainInitObserverOfClass(g, c)	\
	vloadableInitOfClass(vdomainGetObserverLoadable(g), (vloadableClass*)(c))
#define vdomainInitObserver(g)		\
	vdomainInitObserverOfClass(g, vdomainGetDefaultObserverClass())
#define vdomainCloneObserver(g)		\
	((vdomainObserver *)		\
	 vloadableCloneOfSubclass(vdomainGetObserverLoadable(g),	      \
			  (vloadableClass *) vdomainGetDefaultObserverClass()))
#define vdomainCopyInitObserver(g,t)	\
	vloadableCopyInitOfSubclass(vdomainGetObserverLoadable(g),	      \
				    vdomainGetObserverLoadable(t),	      \
			   (vloadableClass *) vdomainGetDefaultObserverClass())
#define vdomainCopyObserver(g, t)	\
	vloadableCopy(vdomainGetObserverLoadable(t), vdomainGetObserverLoadable(t))
#define vdomainObjectCount(d)		((d)->numberObjects)
#define vdomainGetOrientation(d)	((d)->orientation)
#define vdomainIsLong(d)		((d)->longDomain)
#define vdomainGetClass(d)		\
	((vdomainClass*)vloadableGetClass(vdomainGetLoadable(d)))
#define vdomainGetObserverClass(g)	\
	((vdomainObserverClass*)vloadableGetClass(vdomainGetObserverLoadable(g)))
#define vdomainGetData(d)		((d)->data)
#define vdomainSetData(d, dt)		((d)->data = (dt))
#define vdomainGetGrid(d)		(&(d)->grid)
#define vdomainSetGrid(d, g)		((d)->grid = (*g))
#define vdomainGetVirtualBuffer(d)	(&(d)->virtualBuffer)
#define vdomainSetVirtualBuffer(d,v)	((d)->virtualBuffer = (*v))
#define vdomainGetVirtualView(d)	(&(d)->u.info.virtualView)
#define vdomainGetVirtualViewLong(d)	(&(d)->u.longInfo.virtualView)
#define vdomainGetIntersectFunc(d)	((d)->intersectFunc)
#define vdomainGetRectIntersectFunc(d)	((d)->u.info.rectIntersectFunc)
#define vdomainGetRectIntersectFuncLong(d) ((d)->u.longInfo.rectIntersectFunc)
#define vdomainSetIntersectFunc(d,p)	((d)->intersectFunc = (p))
#define vdomainSetUndoActionList(d,l)	((d)->undoActions = (l))
#define vdomainGetUndoActionList(d)	((d)->undoActions)

#define vdomainGetVirtualBounds(d)	\
	(((d)->attributes & _vdomainVIRTUAL_BOUNDS) != 0)
#define vdomainSetVirtualBounds(d,s) {	\
	if (s)   (d)->attributes |= _vdomainVIRTUAL_BOUNDS;	\
	else	 (d)->attributes &= ~_vdomainVIRTUAL_BOUNDS;	\
	}

#define vdomainTopObject(d)		((d)->topObject)
#define vdomainNextObjectBehind(o)	((o)->behind)
#define vdomainNextObjectInFront(o)	((o)->above)
#define _vdomainNextObjectBehind(d, o)	vdomainNextObjectBehind(o)
#define _vdomainNextObjectInFront(d, o)	vdomainNextObjectInFront(o)

#define vdomainSelectedObjects(d,s)	\
	(((d)->selectionList + (s))->selectCount)

#define vdomainGetObjectData(d,o)	((o)->data)
#define vdomainGetObjectBounds(d,o)	(&(o)->u.bounds)
#define vdomainGetObjectBoundsLong(d,o)	(&(o)->u.longBounds)
#define vdomainGetObjectType(d,o)	((o)->type)
#define vdomainIsObjectSelected(d,s,o)	((vbool)((o)->selected & (1 << s)))
#define vdomainIsObjectAnchored(d,o)	\
	(((o)->attributes & _vdomainOBJ_ANCHORED) != 0)
#define vdomainIsObjectOpaque(d,o)	\
	(((o)->attributes & _vdomainOBJ_OPAQUE) != 0)
#define vdomainIsObjectHidden(d,o)	\
	(((o)->attributes & _vdomainOBJ_HIDDEN) != 0)
#define vdomainIsObjectUnselectable(d,o)\
	(((o)->attributes & _vdomainOBJ_UNSELECTABLE) != 0)
#define vdomainIsObjectSelectNotify(d,o)\
	(((o)->attributes & _vdomainOBJ_SELECTNOTIFY) != 0)

#define vdomainSetObjectOpaque(d,o,s)	\
	_vdomainSetAttributes(o, _vdomainOBJ_OPAQUE, (vbool)s)
#define vdomainSetObjectAnchored(d,o,s)	\
	_vdomainSetAttributes(o, _vdomainOBJ_ANCHORED, (vbool)s)
#define vdomainSetObjectUnselectable(d,o,s)	\
	_vdomainSetAttributes(o, _vdomainOBJ_UNSELECTABLE, (vbool)s)
#define vdomainSetObjectSelectNotify(d,o,s)	\
	_vdomainSetAttributes(o, _vdomainOBJ_SELECTNOTIFY, (vbool)s)

#define vdomainDestroyObjectSetIterator(i)
#define vdomainGetObjectSetIteratorObject(i)	(*(i)->object)
#define vdomainNextObjectSetIterator(i)		((i)->object++, ((i)->count--))
#define vdomainGetObjectSetCount(o)		((o)->numObjects)

#define vdomainInstallObserverOwned(e,o)\
	((o)->flags |= _vdomainOBSERVER_OWNED, vdomainInstallObserver(e,o))
#define vdomainSetObserverData(o,d)	((o)->data = d)
#define vdomainGetObserverData(o)	((o)->data)
#define vdomainGetObserverOwner(o)	((o)->owner)

#define vdomainDisableObserver(o)	\
	((o)->flags |= _vdomainOBSERVER_DISABLED)
#define vdomainEnableObserver(o)	\
	((o)->flags &= ~_vdomainOBSERVER_DISABLED)
#define vdomainObserverIsEnabled(o)	\
	(((o)->flags & _vdomainOBSERVER_DISABLED) == 0)

#define vdomainGetObserverIteratorObserver(i)	(*(i)->scan)
#define vdomainDestroyObserverIterator(i)

/*
 * * * * * * * * * * PRIVATE FUNCTION MESSAGE DEFINITIONS * * * * * * * * * *
 */

#define vdomainAddObject(d)	  vclassSend(vdomainGetClass(d), \
					     vdomainADD_OBJECT, (d))
#define vdomainAddInitObject(d,o) vclassSend(vdomainGetClass(d), \
					     vdomainADD_INIT_OBJECT, (d,o))
#define vdomainCopyObject(d,o,t)  vclassSend(vdomainGetClass(d), \
					     vdomainCOPY_OBJECT, (d,o,t))
#define vdomainCopyInitObject(d,o,t)  vclassSend(vdomainGetClass(d), \
					     vdomainCOPY_INIT_OBJECT, (d,o,t))
#define vdomainDestroyObject(d,o) vclassSend(vdomainGetClass(d), \
					     vdomainDESTROY_OBJECT, (d,o))
#define vdomainStoreObject(d,o,r) vclassSend(vdomainGetClass(d), \
					     vdomainSTORE_OBJECT, (d,o,r))
#define vdomainLoadInitObject(d,o,r) vclassSend(vdomainGetClass(d), \
					     vdomainLOAD_INIT_OBJECT, (d,o,r))
#define vdomainRemoveObjects(d,o) vclassSend(vdomainGetClass(d), \
					     vdomainREMOVE_OBJECTS, (d,o))
#define vdomainCopyObjectList(d,t) vclassSend(vdomainGetClass(d), \
					     vdomainCOPY_OBJECT_LIST, (d,t))
#define vdomainSelectAll(d,s,a,b) vclassSend(vdomainGetClass(d), \
					     vdomainSELECT_ALL, (d,s,a,b))
#define vdomainRecalcLimitRect(d,r,b)  vclassSend(vdomainGetClass(d), \
					     vdomainRECALC_LIMIT_RECT, (d,r))
#define _vdomainRecalcLimitRect2(d,r)  vclassSend(vdomainGetClass(d), \
					     vdomainRECALC_LIMIT_RECT, (d,r))
#define _vdomainRecalcLimitRect2Long(d,r) vclassSend(vdomainGetClass(d), \
					     vdomainRECALC_LIMIT_RECT_LONG, (d,r))
#define vdomainSelectObjects(d,s,o)    vclassSend(vdomainGetClass(d), \
					     vdomainSELECT_OBJECTS,(d,s,o))
#define vdomainUnselectObjects(d,s,o)  vclassSend(vdomainGetClass(d), \
					     vdomainUNSELECT_OBJECTS, (d,s,o))
#define vdomainBoundingRect(d,r,o)     vclassSend(vdomainGetClass(d), \
					     vdomainBOUNDING_RECT, (d,r,o))
#define vdomainBoundingRectLong(d,r,o) vclassSend(vdomainGetClass(d), \
					     vdomainBOUNDING_RECT_LONG, (d,r,o))
#define vdomainMoveObjects(d,o,a,b,c) vclassSend(vdomainGetClass(d), \
					     vdomainMOVE_OBJECTS, (d,o,a,b,c))
#define vdomainScaleObjects(d,o,x,y)   vclassSend(vdomainGetClass(d), \
					     vdomainSCALE_OBJECTS, (d,o,x,y))
#define vdomainResizeObjects(d,o,x,y)  vclassSend(vdomainGetClass(d), \
					     vdomainRESIZE_OBJECTS, (d,o,x,y))
#define vdomainAlignObjects(d,o,a,h,v) vclassSend(vdomainGetClass(d), \
					     vdomainALIGN_OBJECTS, (d,o,a,h,v))
#define vdomainDistributeObjects(d,o,h,v) vclassSend(vdomainGetClass(d), \
					     vdomainDISTRIBUTE_OBJECTS, (d,o,h,v))
#define vdomainLayerObjects(d,o,l)     vclassSend(vdomainGetClass(d), \
					     vdomainLAYER_OBJECTS, (d,o,l))
#define vdomainShuffleObjects(d,m,t,b) vclassSend(vdomainGetClass(d), \
					     vdomainSHUFFLE_OBJECTS, (d,m,t,b))
#define vdomainConnectObjects(d,o,o2)  vclassSend(vdomainGetClass(d), \
					     vdomainCONNECT_OBJECTS, (d,o,o2))
#define vdomainDisconnectObjects(d,o)  vclassSend(vdomainGetClass(d), \
					     vdomainDISCONNECT_OBJECTS, (d,o))
#define vdomainGetConnectedSet(d,o)    vclassSend(vdomainGetClass(d), \
					     vdomainGET_CONNECTED_SET, (d,o))
#define vdomainSetBounds(d,b)	       vclassSend(vdomainGetClass(d), \
					     vdomainSET_BOUNDS, (d,b))
#define vdomainSetBoundsLong(d,b)      vclassSend(vdomainGetClass(d), \
					     vdomainSET_BOUNDS_LONG, (d,b))
#define vdomainSortObjects(d,o)        vclassSend(vdomainGetClass(d), \
					     vdomainSORT_OBJECTS, (d,o))
#define vdomainHideObjects(d,o)        vclassSend(vdomainGetClass(d), \
					     vdomainHIDE_OBJECTS, (d,o))
#define vdomainShowObjects(d,o)        vclassSend(vdomainGetClass(d), \
					     vdomainSHOW_OBJECTS, (d,o))
#define vdomainSetObjectBounds(d,o,r)   vclassSend(vdomainGetClass(d), \
					     vdomainSET_OBJECT_BOUNDS, (d,o,r))
#define vdomainSetObjectBoundsLong(d,o,r) vclassSend(vdomainGetClass(d), \
					     vdomainSET_OBJECT_BOUNDS_LONG, (d,o,r))
#define vdomainSnapPointToGrid(d,x,y,gx,gy) vclassSend(vdomainGetClass(d),    \
					     vdomainSNAP_POINT_TO_GRID, (d,x,y,gx,gy))

vportEND_CPLUSPLUS_EXTERN_C


#endif /* #ifndef vdomainINCLUDED */
 

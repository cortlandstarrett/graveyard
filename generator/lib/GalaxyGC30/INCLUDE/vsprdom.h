/* $Id: vsprdom.h,v 1.38 1996/11/28 01:12:40 robert Exp $ */

/************************************************************

    sprdom.h
    C Interface file for the Domain Manager

    (c) Copyright Visix Software Inc.
    All rights reserved

************************************************************/

#ifndef vspringdomINCLUDED
#define vspringdomINCLUDED 1

#ifndef  vportINCLUDED		/* for v*HEADER */
#include <vport.h>
#endif

#ifndef  vstdINCLUDED		/* for vbool */
#include vstdHEADER
#endif

#ifndef  vrectINCLUDED
#include vrectHEADER
#endif

#ifndef  vclassINCLUDED
#include vclassHEADER
#endif

#ifndef  vobjectINCLUDED
#include vobjectHEADER
#endif

#ifndef  vundoINCLUDED
#include vundoHEADER
#endif

#ifndef  vdomainINCLUDED
#include vdomainHEADER
#endif

#ifndef  vspringINCLUDED
#include vspringHEADER
#endif

#ifndef  vdialogINCLUDED
#include vdialogHEADER
#endif


vportBEGIN_CPLUSPLUS_EXTERN_C


/*
 * * * * * * * * * CONSTANTS AND MACRO DEFINITIONS * * * * * * * * * *
 */

/*
 * mask elements:
 */
enum {
    _vspringdomFORWARD_CONNECTION       = 0x0001,
    _vspringdomFORWARD_EDGE             = 0x0002,
    _vspringdomVERTICAL_DIMENSION       = 0x0004
};

/*
 * Dimension component
 */
enum {
    _vspringdomHORIZONTAL      = 0,
    _vspringdomVERTICAL        = _vspringdomVERTICAL_DIMENSION
};

/*
 * Dimensionless edge component
 */
enum {
    _vspringdomBACK            = 0,
    _vspringdomFORWARD         = _vspringdomFORWARD_EDGE
};

/*
 * Dimensionless connection component
 */
enum {
    _vspringdomBACK_OUTSIDE    = 0,
    _vspringdomBACK_INSIDE     = _vspringdomFORWARD_CONNECTION,
    _vspringdomFORWARD_INSIDE  = _vspringdomFORWARD_EDGE,
    _vspringdomFORWARD_OUTSIDE = _vspringdomFORWARD_EDGE
      				   | _vspringdomFORWARD_CONNECTION
};

/*
 * Edges specifications
 */
enum {
    vspringdomLEFT         = _vspringdomBACK,
    vspringdomRIGHT        = _vspringdomFORWARD,
    vspringdomBOTTOM       = _vspringdomBACK | _vspringdomVERTICAL_DIMENSION,
    vspringdomTOP          = _vspringdomFORWARD | _vspringdomVERTICAL_DIMENSION
};

/*
 * Connection specifications
 */
enum {
    vspringdomLEFT_OUTSIDE   = _vspringdomBACK_OUTSIDE,
    vspringdomLEFT_INSIDE    = _vspringdomBACK_INSIDE,
    vspringdomRIGHT_INSIDE   = _vspringdomFORWARD_INSIDE,
    vspringdomRIGHT_OUTSIDE  = _vspringdomFORWARD_OUTSIDE,
    vspringdomBOTTOM_OUTSIDE = _vspringdomBACK_OUTSIDE
      				 | _vspringdomVERTICAL_DIMENSION,
    vspringdomBOTTOM_INSIDE  = _vspringdomBACK_INSIDE
      				 | _vspringdomVERTICAL_DIMENSION,
    vspringdomTOP_INSIDE     = _vspringdomFORWARD_INSIDE
      				 | _vspringdomVERTICAL_DIMENSION,
    vspringdomTOP_OUTSIDE    = _vspringdomFORWARD_OUTSIDE
      				 | _vspringdomVERTICAL_DIMENSION
};

/*
 * Connection stretch factors
 */
enum {
    vspringdomDEFAULT_SPRING
      = vspringDEFAULT_SPRING >> vspringSTRETCH_FACTOR_SHIFT,
    vspringdomEIGHT_TIMES_SPRING
      = vspringEIGHT_TIMES_SPRING >> vspringSTRETCH_FACTOR_SHIFT,
    vspringdomFOUR_TIMES_SPRING
      = vspringFOUR_TIMES_SPRING >> vspringSTRETCH_FACTOR_SHIFT,
    vspringdomDOUBLE_SPRING
      = vspringDOUBLE_SPRING >> vspringSTRETCH_FACTOR_SHIFT,
    vspringdomSINGLE_SPRING
      = vspringSINGLE_SPRING >> vspringSTRETCH_FACTOR_SHIFT,
    vspringdomHALF_SPRING
      = vspringHALF_SPRING >> vspringSTRETCH_FACTOR_SHIFT,
    vspringdomQUARTER_SPRING
      = vspringQUARTER_SPRING >> vspringSTRETCH_FACTOR_SHIFT,
    vspringdomEIGHTH_SPRING
      = vspringEIGHTH_SPRING >> vspringSTRETCH_FACTOR_SHIFT,
    vspringdomSTRETCH_FACTOR_MAX
      = vspringSTRETCH_FACTOR_MAX >> vspringSTRETCH_FACTOR_SHIFT
};


/*
 * Pool size constants:
 */
enum {
    _vspringdomPOOL_SIZE	= 64,
    _vspringdomPOOL_ARRAY_SIZE	= 50
};


/*
 * * * * * * * * * TYPE AND STRUCTURE DEFINITIONS * * * * * * * * * *
 */

typedef struct vspringdomConnection	vspringdomConnection;
typedef struct _vspringdomEdge		_vspringdomEdge;
typedef struct _vspringdomEdgePair	_vspringdomEdgePair;
typedef struct _vspringdomDimension	_vspringdomDimension;
typedef struct vspringdomObject		vspringdomObject;
typedef struct vspringdom		vspringdom;
typedef vdomainObserver			vspringdomObserver;
typedef vspringdomObserver		vspringdomUndoObserver;
typedef vspringArrangerClass		vspringdomArrangerClass;

#if (!vportCPLUSPLUS_SOURCE)
typedef struct vspringdomObjectSet	vspringdomObjectSet;
#else /* (vportCPLUSPLUS_SOURCE) */
typedef vdomainObjectSet		vspringdomObjectSet;
#endif /* (vportCPLUSPLUS_SOURCE) */

struct vspringdomConnection {
    _vspringdomEdge			*to;
    short				length;
    unsigned int			which		: 3;
    unsigned int			stretches	: 1;
    unsigned int			useNaturalBase  : 1;
    unsigned int			isLocked        : 1;
    vbyte				stretchFactor;
};

struct _vspringdomEdge {
    /*
     * WARNING: the position and order of the first two fields cannot change.
     */
    vspringdomConnection		back;
    vspringdomConnection		forward;
    /*
     * WARNING: the position and order of the first two fields cannot change.
     */
    vspringdomConnection		**connected;
    short				location;    /* redundant ??? */
    _vspringdomEdge			*group;
    _vspringdomEdge			*nextGroup;
    _vspringdomEdge			*nextEdgeInGroup;
    unsigned int			isError     : 1;
    unsigned int			visitedMark : 1;
    unsigned int			movingMark  : 1;
};

struct _vspringdomEdgePair {
    /*
     * WARNING: the position and order of the first two fields cannot change.
     */
    _vspringdomEdge			backEdge;
    _vspringdomEdge			forwardEdge;
    /*
     * WARNING: the position and order of the first two fields cannot change.
     */
    unsigned int			isBorder   : 1;
};

struct _vspringdomDimension {
    _vspringdomEdgePair			border;
    _vspringdomEdge			*groups;
};

struct vspringdomObject {
    /*
     * WARNING: the position and order of the first three fields cannot change.
     */
    vdomainObject			domainObject;
    _vspringdomEdgePair			horizontal;
    _vspringdomEdgePair			vertical;
    /*
     * WARNING: the position and order of the first three fields cannot change.
     */
    vspringdom				*springdom;
    int					orderIndex;
    unsigned int			used : 1;
    unsigned int			last : 1;
    unsigned int			moved : 1;
    unsigned int			marked : 1;
};

#if (!vportCPLUSPLUS_SOURCE)
struct vspringdomObjectSet {
    long		setSize;
    long		numObjects;
    vspringdomObject	*objects[1];
};
#endif /* (!vportCPLUSPLUS_SOURCE) */

typedef int (*vspringdomIndexFunc)(vspringdom		*springdom,
				   vspringdomObject	*object);

struct vspringdom {
    /*
     * WARNING: the position and order of the first three fields cannot change.
     */
    vdomain				domain;
    _vspringdomDimension		horizontal;
    _vspringdomDimension		vertical;
    /*
     * WARNING: the position and order of the first three fields cannot change.
     */
    vrect				borderBounds;
    vrect				newBorderBounds;
    vspringdomIndexFunc			indexFunc;
    vspringdomArrangerClass		*arrangerClass;
    vdialogItemList			*itemList;
    vspringSolution			*solution;
    unsigned int			needsRecalc : 1;
    unsigned int			didOrderChange : 1;
    unsigned int			stretchesConnections : 1;
    unsigned int			verboseRecalc : 1;
    unsigned int			constrainBorder : 1;
};

/*
 * Class Definitions
 */

#define vspringdomCLASS(SUPER, DOMAIN, OBJECT, OBJECTSET, SELECTION)	      \
    vdomainCLASS(SUPER, DOMAIN, OBJECT, OBJECTSET, SELECTION);		      \
    vclassMETHOD(vspringdomSET_ITEM_LIST,				      \
		 (DOMAIN *springdom, vdialogItemList *itemList));	      \
    vclassMETHOD(vspringdomSET_BORDER_BOUNDS,				      \
		 (DOMAIN *springdom, const vrect *bounds));		      \
    vclassMETHOD(vspringdomOBSERVE_RECALCULATE, (DOMAIN *));		      \
    vclassMETHOD(vspringdomOBSERVE_RESIZE_BORDER,			      \
		 (DOMAIN *, vrect *oldBounds));				      \
    vclassMETHOD(vspringdomOBSERVE_CONNECT_TO_OBJECT_EDGE,		      \
		 (DOMAIN *, OBJECT *from, int fromWhich,	 	      \
		  OBJECT *oldTo, int oldToEdge));  			      \
    vclassMETHOD(vspringdomOBSERVE_SET_CONNECTION_FIXED_BASE,		      \
		 (DOMAIN *, OBJECT *object,int which, int oldLength));	      \
    vclassMETHOD(vspringdomOBSERVE_SET_CONNECTION_LOCKED,		      \
		 (DOMAIN *, OBJECT *object,int which, int oldLocked));	      \
    vclassMETHOD(vspringdomOBSERVE_SET_CONNECTION_STRETCHES,		      \
		 (DOMAIN *, OBJECT *object,int which, int oldStretches));     \
    vclassMETHOD(vspringdomOBSERVE_SET_CONNECTION_STRETCH_FACTOR,	      \
		 (DOMAIN *, OBJECT *object,int which, int oldStretchFactor)); \
    vclassMETHOD(vspringdomOBSERVE_USE_CONNECTION_NATURAL_BASE,		      \
		 (DOMAIN *, OBJECT *object,int which,			      \
		  int oldUseNaturalBase));				      \
    vclassMETHOD(vspringdomOBSERVE_MARK_CONNECTION_ERROR,		      \
		 (DOMAIN *, OBJECT *object,int which, int oldHasError))

typedef struct vspringdomClass	   vspringdomClass;

struct vspringdomClass {
    vspringdomCLASS(vspringdomClass, vspringdom, vspringdomObject,
		    vspringdomObjectSet, vdomainSelection);
};


/*
 * Domain Observer Class - Global
 */

#define vspringdomObserverCLASS(SUPER, OBSERVER, SELECTION, OBJECT, OBJECTSET)\
    vdomainObserverCLASS(SUPER, OBSERVER, SELECTION, OBJECT, OBJECTSET);      \
    vclassMETHOD(vspringdomObserverRECALCULATE, (OBSERVER *));		      \
    vclassMETHOD(vspringdomObserverRESIZE_BORDER,			      \
		 (OBSERVER *, vrect *oldBounds));			      \
    vclassMETHOD(vspringdomObserverCONNECT_TO_OBJECT_EDGE,		      \
		 (OBSERVER *, OBJECT *from, int fromWhich,	 	      \
		  OBJECT *oldTo, int oldToEdge));  			      \
    vclassMETHOD(vspringdomObserverSET_CONNECTION_FIXED_BASE,		      \
		 (OBSERVER *, OBJECT *object,int which, int oldLength));      \
    vclassMETHOD(vspringdomObserverSET_CONNECTION_LOCKED,		      \
		 (OBSERVER *, OBJECT *object,int which, int oldLocked));      \
    vclassMETHOD(vspringdomObserverSET_CONNECTION_STRETCHES,		      \
		 (OBSERVER *, OBJECT *object,int which, int oldStretches));   \
    vclassMETHOD(vspringdomObserverSET_CONNECTION_STRETCH_FACTOR,	      \
		 (OBSERVER *, OBJECT *object,int which,int oldStretchFactor));\
    vclassMETHOD(vspringdomObserverUSE_CONNECTION_NATURAL_BASE,		      \
		 (OBSERVER *, OBJECT *object,int which,			      \
		  int oldUseNaturalBase));				      \
    vclassMETHOD(vspringdomObserverMARK_CONNECTION_ERROR,		      \
		 (OBSERVER *, OBJECT *object,int which, int oldHasError))


typedef struct vspringdomObserverClass		vspringdomObserverClass;

struct vspringdomObserverClass {
    vspringdomObserverCLASS(vspringdomObserverClass, vdomainObserver,
			    vdomainSelection, vspringdomObject,
			    vspringdomObjectSet);
};


/*
 * * * * * * * * * MANAGER FUNCTION PROTOTYPES * * * * * * * * * *
 */

void vspringdomStartup(void);


/* Initialization and allocation */

vspringdomClass *vspringdomGetDefaultClass(void);

vspringdomObserverClass *vspringdomGetDefaultObserverClass(void);

vspringdomArrangerClass *vspringdomGetDefaultArrangerClass(void);

vspringdomObserverClass *vspringdomGetDefaultUndoObserverClass(void);

vspringdom *vspringdomCreate(void);

vspringdom *vspringdomCreateOfClass(
    vspringdomClass	*clas
    );
    
void vspringdomInit(
    vspringdom	    	*springdom
    );

void vspringdomInitOfClass(
    vspringdom		*springdom,
    vspringdomClass	*clas
    );

void vspringdomDestroy(
    vspringdom	    	*springdom
    );

vspringdom *vspringdomClone(
    vspringdom	    	*springdom
    );

void vspringdomCopy(
    vspringdom	    	*springdom,
    vspringdom	    	*targetSpringdom
    );

void vspringdomCopyInit(
    vspringdom	    	*springdom,
    vspringdom	    	*targetSpringdom
    );

vspringdom *vspringdomLoad(
    vresource           resource
    );

void vspringdomLoadInit(
    vspringdom          *springdom,
    vresource           resource
    );

void vspringdomStore(
    vspringdom          *springdom,
    vresource           resource
    );

/* Spring Domain Operations */

vspringdomObject *vspringdomAddObject(
	vspringdom		*springdom
	);

void vspringdomAddInitObject(
	vspringdom		*springdom,
	vspringdomObject	*object
	);

void vspringdomCopyObject(
	vspringdom		*springdom,
	vspringdomObject	*object,
	vspringdomObject	*target
	);
    
void vspringdomCopyInitObject(
	vspringdom		*springdom,
	vspringdomObject	*object,
	vspringdomObject	*target
	);
    
void vspringdomRemoveObjects(
	vspringdom		*springdom,
	vspringdomObjectSet	*objectsSet
	);

void vspringdomRecalculate(
	vspringdom		*springdom
	);

vspringSolution *vspringdomCompile(
	vspringdom		*springdom
	);

void vspringdomRecompile(
	vspringdom		*springdom,
	vspringSolution		*solution
	);

vspringdom *vspringdomDecompile(
	vspringSolution		*solution
	);

void vspringdomRedecompile(
	vspringdom		*springdom,
	vspringSolution		*solution
	);

/* Spring Domain Attributes Modification */

void vspringdomSetData(
	vspringdom		*springdom,
	void			*data
	);

void vspringdomSetBorderBounds(
	vspringdom		*springdom,
	const vrect		*bounds
	);

void vspringdomSetCompleteRecalc(
	vspringdom		*springdom,
        int /* vbool */		complete
	);

void vspringdomSetConstrainBorder(
	vspringdom		*springdom,
        int /* vbool */		constrain
	);

void vspringdomSetIndexFunc(
	vspringdom		*springdom,
	vspringdomIndexFunc	func
	);

void vspringdomSetArrangerClass(
	vspringdom		*springdom,
	vspringdomArrangerClass	*arrangerClass
	);

void vspringdomSetItemList(
	vspringdom		*springdom,
	vdialogItemList		*itemList
	);

void vspringdomSetSolution(
	vspringdom		*springdom,
	vspringSolution		*solution
	);


/* Spring Domain Attributes Access */

vspringdomClass *vspringdomGetClass(
	vspringdom		*springdom
	);

vdomain *vspringdomGetDomain(
	vspringdom		*springdom
	);

vspringdom *vspringdomGetFromDomain(
	vdomain			*domain
	);

vspringdomObject *vspringdomGetBorder(
	vspringdom		*springdom
	);

void *vspringdomGetData(
	vspringdom		*springdom
	);

vrect *vspringdomGetBorderBounds(
	vspringdom		*springdom
	);

vbool vspringdomHasCompleteRecalc(
	vspringdom		*springdom
	);

vbool vspringdomHasConstrainBorder(
	vspringdom		*springdom
	);

vspringdomIndexFunc vspringdomGetIndexFunc(
	vspringdom		*springdom
	);

vspringdomArrangerClass *vspringdomGetArrangerClass(
	vspringdom		*springdom
	);

vdialogItemList *vspringdomGetItemList(
	vspringdom		*springdom
	);

vspringSolution *vspringdomGetSolution(
	vspringdom		*springdom
	);

void vspringdomCalcMinSize(
	vspringdom		*springdom,
	int			*width,
	int			*height
	);


/* Spring Object Operations */

void vspringdomRelocateObjects(
	vspringdom		*springdom,
	vspringdomObjectSet	*objectSet,
	int			dx,
	int			dy,
	int			dw,
	int			dh
	);


/* Spring Object Attributes Modification */

void vspringdomSetObjectData(
	vspringdom		*springdom,
	vspringdomObjectSet	*objectSet,
	void			*data
	);

void vspringdomResetObjectConnections(
	vspringdom		*springdom,
	vspringdomObject	*object
	);

void vspringdomResetConnection(
	vspringdom		*springdom,
        vspringdomConnection	*connection
	);

void vspringdomConnectToObjectEdge(
	vspringdom		*springdom,
	vspringdomConnection	*connection,
	vspringdomObject	*toObject,
	int	 		toEdge
	);

void vspringdomReflectConnection(
	vspringdom		*springdom,
	vspringdomConnection	*connection
	);

void vspringdomSetConnectionFixedBase(
	vspringdom		*springdom,
	vspringdomConnection	*connection,
	int			length
	);

void vspringdomUseConnectionNaturalBase(
	vspringdom		*springdom,
	vspringdomConnection	*connection,
	int	 		useNaturalBase
	);

void vspringdomSetConnectionLocked(
	vspringdom		*springdom,
	vspringdomConnection	*connection,
	int			 isLocked
	);

void vspringdomSetConnectionStretches(
	vspringdom		*springdom,
	vspringdomConnection	*connection,
	int	 		stretches
	);

void vspringdomSetConnectionStretchFactor(
	vspringdom		*springdom,
	vspringdomConnection	*connection,
	int	 		stretchFactor
	);

void vspringdomFSetConnectionStretchFactor(
	vspringdom		*springdom,
	vspringdomConnection	*connection,
	double	 		stretchFactor
	);

/* Spring Object Attributes Access */

vdomainObject *vspringdomGetDomainObject(
	vspringdom		*springdom,
	vspringdomObject	*object
	);

vspringdomObject *vspringdomGetFromDomainObject(
	vspringdom		*springdom,
	vdomainObject		*domainObject
	);

vdomainObjectSet *vspringdomGetDomainObjectSet(
        vspringdom		*springdom,
	vspringdomObjectSet	*objectSet
	);

vspringdomObjectSet *vspringdomGetFromDomainObjectSet(
        vspringdom		*springdom,
	vdomainObjectSet	*domainObjectSet
	);

vspringdomObjectSet *vspringdomObjectToSet(
	vspringdomObject	*object
	);

void *vspringdomGetObjectData(
	vspringdom		*springdom,
	vspringdomObject	*object
	);

int vspringdomGetObjectIndex(
	vspringdom		*springdom,
	vspringdomObject	*object
	);

vspringdomObject *vspringdomGetObjectAt(
	vspringdom		*springdom,
        int			 index
	);

vspringdomConnection *vspringdomGetObjectConnection(
	vspringdom		*springdom,
	vspringdomObject	*object,
	int	 		which
	);

vspringdomObject *vspringdomGetObjectConnectedTo(
	vspringdom		*springdom,
	vspringdomConnection	*connection
	);

int vspringdomGetEdgeConnectedTo(
	vspringdom		*springdom,
	vspringdomConnection	*connection
	);

vspringdomObjectSet *vspringdomGetObjectsConnectedToEdge(
	vspringdom		*springdom,
	vspringdomObject	*toObject,
	int			toEdge
	);

vbool vspringdomIsConnectionReflected(
	vspringdom		*springdom,
	vspringdomConnection	*connection
	);

int vspringdomGetConnectionFixedBase(
	vspringdom		*springdom,
	vspringdomConnection	*connection
	);

vbool vspringdomUsesConnectionNaturalBase(
	vspringdom		*springdom,
	vspringdomConnection	*connection
	);

vbool vspringdomIsConnectionLocked(
	vspringdom		*springdom,
	vspringdomConnection	*connection
	);

vbool vspringdomGetConnectionStretches(
	vspringdom		*springdom,
	vspringdomConnection	*connection
	);

int vspringdomGetConnectionStretchFactor(
	vspringdom		*springdom,
	vspringdomConnection	*connection
	);

double vspringdomFGetConnectionStretchFactor(
	vspringdom		*springdom,
	vspringdomConnection	*connection
	);

int vspringdomGetConnectionNaturalBase(
	vspringdom		*springdom,
	vspringdomConnection	*connection
	);

int vspringdomGetConnectionCurrentLength(
	vspringdom		*springdom,
	vspringdomConnection	*connection
	);

vbool vspringdomHasConnectionError(
	vspringdom		*springdom,
	vspringdomConnection	*connection
	);

vbool vspringdomHasObjectError(
	vspringdom		*springdom,
	vspringdomObject	*object
	);

int vspringdomGetObjectEdgeLocation(
	vspringdom		*springdom,
	vspringdomObject	*object,
	int	 		edge
	);


/*
 * * * * * * * * * P_R_I_V_A_T_E FUNCTION PROTOTYPES * * * * * * * * * *
 */

vdomainObject *_vspringdomGetDomainObject(vspringdomObject *object);

vspringdomObject *_vspringdomAllocObject(void);
void	_vspringdomFreeObject(vspringdomObject *object);

int _vspringdomDefaultIndexFunc(vspringdom *springdom,
				vspringdomObject *object);

void _vspringdomSetConnectionFixedBase(
    vspringdom			*springdom,
    vspringdomConnection	*connection,
    int				length,
    int				fixCorresponding
    );

void _vspringdomSetConnectionStretches(
    vspringdom			*springdom,
    vspringdomConnection	*connection,
    int				stretches,
    int				fixCorresponding
    );

void _vspringdomSetConnectionStretchFactor(
    vspringdom			*springdom,
    vspringdomConnection	*connection,
    int				stretchFactor,
    int				fixCorresponding
    );

void _vspringdomUseConnectionNaturalBase(
    vspringdom			*springdom,
    vspringdomConnection	*connection,
    int				useNaturalBase,
    int				fixCorresponding
    );

void _vspringdomSetConnectionLocked(
    vspringdom			*springdom,
    vspringdomConnection	*connection,
    int				isLocked,
    int				fixCorresponding
    );

void _vspringdomSetIsolatedConnections(
    vspringdom			*springdom,
    vspringdomObjectSet		*objectSet,
    vspringSolution		*isolatedConnections
    );

vspringSolution *_vspringdomGetIsolatedConnections(
    vspringdom			*springdom,
    vspringdomObjectSet		*objectSet
    );

void _vspringdomSetObjectCount(
    vspringdom			*springdom,
    int				 itemCount
    );

void _vspringdomSetAllConnections(
    vspringdom			*springdom,
    vspringSolution		*allConnections
    );

vspringSolution *_vspringdomGetAllConnections(
    vspringdom			*springdom
    );

vspringSolution *_vspringdomGetAllConnectionsFromSolution(
    vspringSolution		*solution
    );

vspringSolution *_vspringdomLoadAllConnections(
    vresource			resource
    );

/*
 * * * * * * * * * PRIVATE VARIABLES * * * * * * * *
 */

typedef struct _vspringdomGlobals {
    vspringdomClass		*defaultClass;
    vspringdomObserverClass	*defaultObserverClass;
    vspringdomArrangerClass	*defaultArrangerClass;
    const vname			*connectionsTag;
} _vspringdomGlobals;

extern vportLINK _vspringdomGlobals     _vspringdomMaster;

extern vportLINK vspringdomObjectSet	_vspringdomSetOfOne;


/*
 * * * * * * * * * FUNCTIONS IMPLEMENTED AS MACROS * * * * * * * *
 */

#define vspringdomCreateOfClass(c)	\
		     ((vspringdom *) vobjectCreateOfClass((vobjectClass *)(c)))
#define vspringdomCreate() \
  		     vspringdomCreateOfClass(vspringdomGetDefaultClass())

#define vspringdomClone(sd)	((vspringdom *) vdomainClone((vdomain *) (sd)))

#define vspringdomInitOfClass(sd, c) \
		     vobjectInitOfClass((vobject *)(sd), (vobjectClass *)(c))
#define vspringdomInit(sd) \
		     vspringdomInitOfClass(sd, vspringdomGetDefaultClass())
	
#define vspringdomDestroy(sd)	 \
		     vobjectDestroy((vobject *)(sd))

#define vspringdomCopy(sd,t)	 \
	vclassSend(vspringdomGetClass(sd), vobjectCOPY, (sd,t))
#define vspringdomCopyInit(sd,t) \
	vclassSend(vspringdomGetClass(sd), vobjectCOPY_INIT, (sd,t))

#define vspringdomLoad(r)	  ((vspringdom *)vdomainLoad(r))
#define vspringdomLoadInit(sd, r) \
	vclassSend(vspringdomGetClass(sd), vobjectLOAD_INIT, (sd,r))

#define vspringdomStore(sd,r)	\
	vclassSend(vspringdomGetClass(sd), vobjectSTORE, (sd,r))

#define vspringdomSetBorderBounds(sd,r) \
	vclassSend(vspringdomGetClass(sd), vspringdomSET_BORDER_BOUNDS, \
		   (sd, r))
#define vspringdomSetItemList(sd,l) \
	vclassSend(vspringdomGetClass(sd), vspringdomSET_ITEM_LIST, (sd, l))

#define vspringdomAddObject(sd) \
	vclassSend(vspringdomGetClass(sd), vdomainADD_OBJECT, (sd))
#define vspringdomAddInitObject(sd, sdo) \
	vclassSend(vspringdomGetClass(sd), vdomainADD_INIT_OBJECT, (sd, sdo))
#define vspringdomCopyObject(sd, sdo,t) \
	vclassSend(vspringdomGetClass(sd), vdomainCOPY_OBJECT,(sd, sdo,t))
#define vspringdomCopyInitObject(sd, sdo,t) \
	vclassSend(vspringdomGetClass(sd), vdomainCOPY_INIT_OBJECT,(sd, sdo,t))

#define vspringdomRemoveObjects(sd,sdo) \
	vclassSend(vspringdomGetClass(sd), vdomainREMOVE_OBJECTS, (sd,sdo))

#define vspringdomGetDomain(sd)			(vportBASE_OBJECT((sd), domain))
#define vspringdomGetFromDomain(d)		((vspringdom *)(d))

#define vspringdomGetClass(sd) \
	((vspringdomClass*)vdomainGetClass(vspringdomGetDomain(sd)))

#define vspringdomSetIndexFunc(sd,f) \
	((void)((sd)->indexFunc \
		= ((f) == NULL) ? _vspringdomDefaultIndexFunc : (f)))
#define vspringdomGetIndexFunc(sd)		((sd)->indexFunc)

#define vspringdomSetArrangerClass(sd,ac)  \
	((void)((sd)->arrangerClass \
		= ((ac) == NULL) ? vspringdomGetDefaultArrangerClass() : (ac)))
#define vspringdomGetArrangerClass(sd)	   ((sd)->arrangerClass)
#define vspringdomGetItemList(sd)	   ((sd)->itemList)

#define vspringdomSetData(sd,d) \
			vdomainSetData(vspringdomGetDomain(sd), d)
#define vspringdomGetData(sd) \
			vdomainGetData(vspringdomGetDomain(sd))

#define vspringdomGetBorder(sd)			(NULL)

#define _vspringdomGetDomainObject(sdo)	  vportBASE_OBJECT(sdo, domainObject)
#define vspringdomGetDomainObject(sd,sdo)	_vspringdomGetDomainObject(sdo)
#define vspringdomGetFromDomainObject(sd,o)	((vspringdomObject *) (o))

#define vspringdomObjectToSet(object)					\
		(_vspringdomSetOfOne.objects[0] = (object), \
		 &_vspringdomSetOfOne)

#define vspringdomGetDomainObjectSet(sd,sdos)	 ((vdomainObjectSet *)(sdos))
#define vspringdomGetFromDomainObjectSet(sd,dos) ((vspringdomObjectSet *)(dos))

#define vspringdomSetObjectData(sd,os,d) \
	vdomainSetObjectData(vspringdomGetDomain(sd), \
			     vspringdomGetDomainObjectSet(sd,os),d)

#define vspringdomGetObjectData(sd,o) \
	vdomainGetObjectData(vspringdomGetDomain(sd), \
			     vspringdomGetDomainObject(sd,o))

#define vspringdomGetObjectIndex(sd,o) \
        (((sd)->indexFunc)(sd, o))

#define vspringdomGetBorderBounds(sd)		(&(sd)->borderBounds)

#define vspringdomSetConnectionFixedBase(sd,c,l) \
			_vspringdomSetConnectionFixedBase(sd,c,l,TRUE)
#define vspringdomSetConnectionStretches(sd,c,rd) \
  			_vspringdomSetConnectionStretches(sd,c,rd,TRUE)
#define vspringdomSetConnectionStretchFactor(sd,c,rd) \
  			_vspringdomSetConnectionStretchFactor(sd,c,rd,TRUE)
#define vspringdomUseConnectionNaturalBase(sd,c,rs) \
  			_vspringdomUseConnectionNaturalBase(sd,c,rs,TRUE)
#define vspringdomSetConnectionLocked(sd,c,l) \
  			_vspringdomSetConnectionLocked(sd,c,l,TRUE)

#define vspringdomGetConnectionFixedBase(sd,c)		((c)->length)
#define vspringdomUsesConnectionNaturalBase(sd,c)	((c)->useNaturalBase)
#define vspringdomGetConnectionStretches(sd,c)		((c)->stretches)
#define vspringdomGetConnectionStretchFactor(sd,c)	((c)->stretchFactor)
#define vspringdomIsConnectionLocked(sd,c)		((c)->isLocked)

#define vspringdomHasCompleteRecalc(sd)		((sd)->verboseRecalc)
#define vspringdomSetConstrainBorder(sd,v)	((sd)->constrainBorder = (v))
#define vspringdomHasConstrainBorder(sd)	((sd)->constrainBorder)


vportEND_CPLUSPLUS_EXTERN_C


#endif /* #ifndef vspringdomINCLUDED */


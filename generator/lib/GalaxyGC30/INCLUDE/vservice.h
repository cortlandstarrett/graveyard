/* $Id: vservice.h,v 1.49 1997/11/18 20:17:53 robert Exp $ */

/************************************************************

    vservice.h

    C Interface file for the Service Manager

    (c) Copyright 1993, 1994 Visix Software Inc.
    All rights reserved

************************************************************/

#ifndef vserviceINCLUDED	/**----------  vserviceINCLUDED  ----------**/
#define vserviceINCLUDED	(1)

#ifndef  vportINCLUDED		/* for v*HEADER */
#include <vport.h>
#endif

#ifndef  vstdioINCLUDED		/**  for definition of FILE	**/
#include vstdioHEADER
#endif

#ifndef  vnameINCLUDED		/**  Name Manager		**/
#include vnameHEADER
#endif

#ifndef  vdictINCLUDED		/**  Attribute dictionaries, etc **/
#include vdictHEADER
#endif

#ifndef  vscrapINCLUDED		/**  Representation Manager	**/
#include vscrapHEADER
#endif
#ifndef  vcommandINCLUDED
#include  vcommandHEADER
#endif

#ifndef  vsignatureINCLUDED	/**  for statement signatures	**/
#include vsignatureHEADER
#endif
#ifndef  vsiggrpINCLUDED
#include  <vsiggrp.h>
#endif
#ifndef  vsessionINCLUDED	/**  Session Manager		**/
#include vsessionHEADER
#endif

#ifndef  vdebugDEBUG
#ifndef  vdebugINCLUDED		/**  for defn of vdebugDEBUG	**/
#include vdebugHEADER
#endif
#endif


vportBEGIN_CPLUSPLUS_EXTERN_C


/*===========================================================================*\
 * * * * * * * * * * * *  PUBLIC  CONSTANT  DEFINITIONS  * * * * * * * * * * *
\*===========================================================================*/
enum vserviceEventCode {
    vserviceEVENT_ENABLED,
    vserviceEVENT_DISABLED,
    vserviceEVENT_CANNOT_ENABLE
};

enum {
    vserviceFLAG_DEBUG			= 0x0001,
    vserviceFLAG_DEBUG_NOTIFY		= 0x0002,
    vserviceFLAG_DEBUG_ALL		= 0x0003
};

enum {
    vservicePrimitiveFLAG_DEBUG		= 0x0100,
    vservicePrimitiveFLAG_DEBUG_ARG	= 0x0200,
    vservicePrimitiveFLAG_DEBUG_RESULT	= 0x0400,
    vservicePrimitiveFLAG_DEBUG_ALL	= 0x0700
};



/*===========================================================================*\
 * * * * * * * * * * * * *  PUBLIC  TYPE  DEFINITIONS  * * * * * * * * * * * *
\*===========================================================================*/
#ifndef  _vserviceDEFINED_VSERVICE
typedef struct vservice	 vservice;
#define  _vserviceDEFINED_VSERVICE (1)	/** circular dependency  **/
#endif
typedef struct vserviceClass			vserviceClass;
typedef struct vservicePrimitive		vservicePrimitive;
typedef struct vservicePrimitiveClass		vservicePrimitiveClass;
typedef struct vservicePrimitiveContext		vservicePrimitiveContext;
typedef struct vservicePrimitiveContextClass	vservicePrimitiveContextClass;

typedef struct vservicePrimitiveIterator	vservicePrimitiveIterator;
typedef struct vserviceSessionIterator		vserviceSessionIterator;

typedef int					vserviceEvent;
typedef enum vserviceEventCode			vserviceEventCode;

typedef void (*vserviceNoteProc)( vservice *service, vserviceEvent *event );

typedef void (*vservicePrimitiveContextHandlerProc)(
	vservicePrimitiveContext *context
	);

/**  depricated type
 **/
typedef vscrap 	*(*vservicePrimitiveHandlerProc)(
	vservicePrimitive	*primitive,
	vsession		*session,
	vscrap			*scrapArgs
	);


#define  vserviceCLASS( _SUPER, _OBJECT )				\
	vloadableCLASS( _SUPER, _OBJECT );				\
	vclassVARIABLE( vserviceTEMPLATE_SESSION_CLASS, vsessionClass * ); \
	vclassMETHOD( vserviceENABLE, (_OBJECT *service) );		\
	vclassMETHOD( vserviceDISABLE, (_OBJECT *service) )

#define  vservicePrimitiveCLASS( _SUPER, _OBJECT )			\
	vinstanceCLASS( _SUPER, _OBJECT );				\
	vclassMETHOD( vservicePrimitiveHANDLE_CONTEXT,			\
		     	(_OBJECT *prim, vservicePrimitiveContext *context))

/*===========================================================================*\
 * * * * * * * * * * *   PUBLIC  FUNCTION  PROTOTYPES  * * * * * * * * * * * *
\*===========================================================================*/

void vserviceStartup( void );
vserviceClass  *vserviceGetDefaultClass( void );


/**********************
 **  service creation
 **********************/
vservice  *vserviceCreate(void);

vservice  *vserviceCreateOfClass(
	vserviceClass	*clas
	);

void  vserviceInit(
	vservice	*service
	);

void  vserviceInitOfClass(
	vservice	*service,
	vserviceClass	*clas
	);

vservice  *vserviceClone(
	vservice	*service
	);

vservice  *vserviceLoad(
	vresource	 resource
	);

void vserviceLoadInit(
	vservice	*service,
	vresource	 resource
	);

void vserviceStore(
	vservice	*service,
	vresource	 resource
	);

void  vserviceDestroy(
	vservice	*service
	);


/**********************
 **  enabling
 **********************/
void  vserviceEnable(
	vservice	*service
	);

void  vserviceDisable(
	vservice	*service
	);

vbool  vserviceIsEnabled(
	vservice	*service
	);


/****************************************
 **  attributes and attribute iterators
 ****************************************/
vscrap  *vserviceMakeAttributeScrap(
	vservice		*service
	);

void  vserviceSetAttribute(
	vservice		*service,
	const vname		*name,
	vdatatag		*datatag,	/* NULL destroys */
	...		/* value for datatag */
	);

void  vserviceGetAttribute(
	vservice		*service,
	const vname		*name,
	...		/* pointer to storage for value */
	);

vdatatag  *vserviceFindAttributeDatatag(
	vservice		*service,
	const vname		*name
	);

void  vserviceSetAttributesFromScrap(
	vservice		*service,
	vscrap			*scrap
	);

void  vserviceSetAttributeScalar(
	vservice		*service,
	const vname		*name,
	long			 value
	);

long  vserviceFindAttributeScalar(
	vservice	*service,
	const vname	*name
	);

void  vserviceSetAttributeFloat(
	vservice		*service,
	const vname		*name,
	double			 value
	);

double  vserviceFindAttributeFloat(
	vservice	*service,
	const vname	*name
	);

void  vserviceSetAttributeScribed(
	vservice		*service,
	const vname		*name,
	vscribe			*scribeValue
	);

vscribe  *vserviceFindAttributeScribe(
	vservice	*service,
	const vname	*name
	);

void  vserviceSetAttributeTag(
	vservice		*service,
	const vname		*name,
	const vname		*nameValue
	);

const vname  *vserviceFindAttributeTag(
	vservice	*service,
	const vname	*name
	);


/*********************
 **  signature groups
 *********************/
void  vserviceAddSignatureGroup(
	vservice	*service,
	vsignatureGroup	*group
	);

void  vserviceRemoveSignatureGroup(
	vservice	*service,
	const vname	*tag
	);

/****************************************
 **  primitives and primitive iterators
 ****************************************/
void  vserviceAddPrimitiveOwned(
	vservice		*service,
	vservicePrimitive	*primitive	/* NULL destroys */
	);

void  vserviceRemovePrimitive(
	vservice		*service,
	vservicePrimitive	*primitive
	);

vservicePrimitive  *vserviceFindPrimitive(
	vservice		*service,
	const vname		*tag
	);

void  vserviceInitPrimitiveIterator(
	vservicePrimitiveIterator	*iterator,
	vservice			*service
	);

void  vserviceDestroyPrimitiveIterator(
	vservicePrimitiveIterator	*iterator
	);

vbool  vserviceNextPrimitiveIterator(
	vservicePrimitiveIterator	*iterator
	);

vservicePrimitive  *vserviceGetPrimitiveIteratorValue(
	vservicePrimitiveIterator	*iterator
	);


/**********************
 **  other service
 **********************/
vserviceClass *vserviceGetClass(
	vservice	*service
	);

vloadable  *vserviceGetLoadable(
	vservice	*service
	);

vsession  *vserviceSpawnSession(
	vservice	*service
	);

void  vserviceDump(
	vservice	*service,
	FILE		*fp
	);

vserviceNoteProc  vserviceGetNotify(
	vservice	*session
	);

void  vserviceSetNotify(
	vservice		*session,
	vserviceNoteProc	 fnNotify
	);

void  *vserviceGetData(
	vservice	*service
	);

void  vserviceSetData(
	vservice	*service,
	void		*data
	);

void  vserviceSetSessionClass(
	vservice	*service,
	vsessionClass	*clas
	);

vsessionClass  *vserviceGetSessionClass(
	vservice	*service
	);

void  vserviceSetSessionNotify(
	vservice		*service,
	vsessionNoteProc	 fnNotify
	);

vsessionNoteProc  vserviceGetSessionNotify(
	vservice	*service
	);


/***************
 **  debugging
 ***************/
unsigned int  vserviceGetGeneralDebugFlags(
	vservice	*service
	);

void  vserviceSetGeneralDebugFlags(
	vservice	*service,
	unsigned int	 flags
	);

unsigned int  vserviceGetPrimitiveDebugFlags(
	vservice	*service
	);

void  vserviceSetPrimitiveDebugFlags(
	vservice	*service,
	unsigned int	 flags
	);



/**********************
 **  Session iterators
 **********************/
void  vserviceInitSessionIterator(
	vserviceSessionIterator	*iterator,
	vservice		*service
	);

void  vserviceDestroySessionIterator(
	vserviceSessionIterator	*iterator
	);

vbool  vserviceNextSessionIterator(
	vserviceSessionIterator	*iterator
	);

vsession  *vserviceGetSessionIteratorValue(
	vserviceSessionIterator	*iterator
	);


/**********************
 **  service events
 **********************/
vserviceEventCode  vserviceGetEventCode(
	vserviceEvent	*event
	);

/***********************
 **  primitive creation
 ***********************/
vservicePrimitiveClass  *vserviceGetDefaultPrimitiveClass( void );
vservicePrimitiveClass  *vserviceGetCommandPrimitiveClass( void );

vservicePrimitive  *vserviceCreatePrimitive(void);
vservicePrimitive  *vserviceCreatePrimitiveOfClass(
	vservicePrimitiveClass *clas
	);

void  vserviceInitPrimitive(
	vservicePrimitive	*primitive
	);

void  vserviceInitPrimitiveOfClass(
	vservicePrimitive	*primitive,
	vservicePrimitiveClass	*clas
	);

void  vserviceDestroyPrimitive(
	vservicePrimitive	*primitive
	);

vservicePrimitive *vserviceLoadPrimitive( vresource res );
void  vserviceStorePrimitive( vservicePrimitive *prim, vresource res );



/***********************
 **  other primitive
 ***********************/
vinstance  *vserviceGetPrimitiveInstance(
	vservicePrimitive	*primitive
	);

vservicePrimitiveClass  *vserviceGetPrimitiveClass(
	vservicePrimitive	*primitive
	);

vservicePrimitiveClass  *vserviceGetPrimitiveClass(
	vservicePrimitive	*primitive
	);

void  vserviceSetPrimitiveSignature(
	vservicePrimitive	*primitive,
	vsignature		*signature
	);

vsignature  *vserviceGetPrimitiveSignature(
	vservicePrimitive	*primitive
	);

vservicePrimitiveContextHandlerProc vserviceGetPrimitiveContextHandler(
	vservicePrimitive	*prim
	);

void  vserviceSetPrimitiveContextHandler(
	vservicePrimitive			*prim,
	vservicePrimitiveContextHandlerProc	 fnHandler
	);

void  *vserviceGetPrimitiveData(
	vservicePrimitive		*primitive
	);

void  vserviceSetPrimitiveData(
	vservicePrimitive	*primitive,
	void			*data
	);

/**************************
 **  predefined primtives
 **	!!! move these
 **************************/
vservicePrimitive  *vserviceCreatePingPrimitive(void);
vservicePrimitive  *vserviceCreateShutdownPrimitive(void);
vservicePrimitive  *vserviceCreateIssueCommandPrimitive(void);


/*******************************
 **  deprecated functions
 *******************************/
vsession  *vserviceGetTemplateSession(
	vservice	*service
	);

void  vserviceSetAttributeScribe(
	vservice	*service,
	const vname	*name,
	vscribe		*scribeValue
	);

vservicePrimitiveHandlerProc  vserviceGetPrimitiveHandler(
	vservicePrimitive	*primitive
	);

void  vserviceSetPrimitiveHandler(
	vservicePrimitive		*primitive,
	vservicePrimitiveHandlerProc	 fnHandler
	);

void vserviceGetPrimitiveArgs(
	vservicePrimitive	*primitive,
	vscrap			*scrapArgs,
	...		/**  pointers to storage expected by signature  **/
	);

vscrap *vserviceMakePrimitiveReturnScrap(
	vservicePrimitive	*primitive,
	vsession		*session,
	...		/**  value expected by signature  **/
	);


/****************************************
 **  depricated attributed objects
 **  !!! perhaps make subclass for this
 ****************************************/
void  vserviceAddObject(
	vservice	*service,
	const vname	*name,
	vobject		*object
	);

void  vserviceRemoveObject(
	vservice	*service,
	const vname	*name		   
	);

vobject  *vserviceFindObject(
	vservice	*service,
	const vname	*name
	);


/*******************************************
 **  depricated only work on default class
 *******************************************/
vservicePrimitive  *vserviceClonePrimitive(
	vservicePrimitive	*primitive
	);

void  vserviceCopyInitPrimitive(
	vservicePrimitive	*primitiveSource,
	vservicePrimitive	*primitiveDest
	);


/*===========================================================================*\
 * * * * * * * * *  EXCEPTION  DEFINITIONS   PUBLIC/PRIVATE  * * * * * * * * *
\*===========================================================================*/

typedef struct vserviceException {
    vexException	 exception;
    vservice		*service;
} vserviceException;

typedef vserviceException  vserviceCannotEnableException;

vserviceCannotEnableException  *vserviceGetCannotEnableException(void);

vexClass  *vserviceGetCannotEnableExceptionClass(void);

#define  vserviceGetCannotEnableException()			\
   (vserviceException *)vexGetExceptionOfClass(			\
		vserviceGetCannotEnableExceptionClass())

void  vserviceSERVICE(
	void	*exception,
	va_list	*ap
	);


/*===========================================================================*\
 * * * * * * * * * * *   PRIVATE  CONSTANT  DEFINITIONS  * * * * * * * * * * *
\*===========================================================================*/


/*===========================================================================*\
 * * * * * * * * * * * *   PRIVATE  TYPE  DEFINITIONS  * * * * * * * * * * * *
\*===========================================================================*/
/**********************
 **  services
 **********************/
struct _vserviceData;

struct vserviceClass {
    vserviceCLASS( vserviceClass, vservice );
};
    
struct vservice {
    vloadable			 loadable;
    struct _vserviceData	*privateData;
    void			*data;
    vsessionNoteProc		 fnNotifySession;
    vserviceNoteProc		 fnNotify;
    unsigned int		 flagsDebug;
    vdict			 dictPrimitives;
};

struct vservicePrimitiveIterator {
    vdictIterator		 dict;
};


struct vserviceSessionIterator {
    int				  nSessions;
    vsession			**arraySessions;
};


/**********************
 **  primitives
 **********************/
struct vservicePrimitive {
    vinstance				instance;
    vsignature				*signature;
    void				*data;
    vservicePrimitiveHandlerProc	fnHandler;
    vservicePrimitiveContextHandlerProc fnContextHandler;
};


struct vservicePrimitiveClass {
    vservicePrimitiveCLASS( vservicePrimitiveClass, vservicePrimitive );
};


/*===========================================================================*\
 * * * * * * * * * * *   PRIVATE  FUNCTION  PROTOTYPES * * * * * * * * * * * *
\*===========================================================================*/

/**********************
 **  service creation
 **********************/
#if  (vdebugDEBUG)			/*----------  vdebugDEBUG  ----------*/
vservice  *_vserviceCreateDebug(
	const char	*tag,
	const char	*file,
	int		 line
	);

vservice  *_vserviceCloneDebug(
	vservice	*service,
	const char	*tag,
	const char	*file,
	int		 line
	);
#endif					/*----------  vdebugDEBUG  ----------*/


/*===========================================================================*\
 * * * * * * * * *  PRIVATE  FUNCTION  MACRO  DEFINITIONS  * * * * * * * * * *
\*===========================================================================*/
/**********************
 **  service object
 **********************/
#define  vserviceGetLoadable(_service)		\
    vportBASE_OBJECT(_service, loadable)

#define  vserviceGetClass(_service)		\
    (vserviceClass *)vloadableGetClass(vserviceGetLoadable(_service))


/**********************
 **  service creation
 **********************/
#define  vserviceCreateOfClass(_clas)	\
    (vservice *)vloadableCreateOfClass(_clas)

#define  vserviceInitOfClass(_service, _clas)	\
    vloadableInitOfClass(vserviceGetLoadable(_service), _clas)

#define  vserviceCreate()		\
    vserviceCreateOfClass(vserviceGetDefaultClass())

#define  vserviceInit(_service)		\
    vserviceInitOfClass(_service, vserviceGetDefaultClass())

#define  vserviceDestroy(_service)		\
    vloadableDestroy(vserviceGetLoadable(_service))

#define  vserviceClone(_service)		\
    (vservice *)vloadableClone(vserviceGetLoadable(_service))

#define  vserviceLoad(_res)					\
    (vservice *)vloadableLoad(_res)

#define  vserviceLoadInit(_service, _res)	\
    vloadableLoadInit(vserviceGetLoadable(_service), _res)

#define  vserviceStore(_service, _res)		\
    vloadableStore(vserviceGetLoadable(_service), _res)
    
#define  vserviceDump(_service, _fp)		\
    vloadableDump(vserviceGetLoadable(_service), _fp)



/**********************
 **  service events
 **********************/
#define  vserviceGetEventCode(_event)					\
    (*(vserviceEventCode *)(_event))

/**********************
 **  primitive creation
 **********************/
#define vserviceGetPrimitiveInstance(p) \
    (vportBASE_OBJECT(p, instance))

#define  vserviceCreatePrimitive()				\
    vserviceCreatePrimitiveOfClass( vserviceGetDefaultPrimitiveClass() )
#define  vserviceCreatePrimitiveOfClass( _clas )		\
    (vservicePrimitive *)vinstanceCreateOfClass( (vinstanceClass *)_clas )

#define  vserviceInitPrimitive(_p)				\
    vserviceInitPrimitiveOfClass( _p, vserviceGetDefaultPrimitiveClass() )
#define  vserviceInitPrimitiveOfClass( _p, _clas )		\
    vinstanceInitOfClass( vserviceGetPrimitiveInstance(_p),	\
			  (vinstanceClass *)_clas )

#define  vserviceDestroyPrimitive(_prim)	\
    vinstanceDestroy(vserviceGetPrimitiveInstance(_prim))

    

/**********************
 **  other primitive
 **********************/
#define vserviceGetPrimitiveClass(p) \
 ((vservicePrimitiveClass*)vinstanceGetClass(vserviceGetPrimitiveInstance(p)))

#if  (!vdebugDEBUG)			/*----  #if    !vdebugDEBUG  ----*/
#define  vserviceSetPrimitiveSignature(_prim, _sig)			\
    (void)((_prim)->signature = (_sig))
#endif					/*----  #endif !vdebugDEBUG  ----*/

#define  vserviceGetPrimitiveSignature(_prim)				\
    ((_prim)->signature)

#define  vserviceSetPrimitiveContextHandler(_prim, _handler)	\
    (void)((_prim)->fnContextHandler = (_handler))

#define  vserviceGetPrimitiveContextHandler(_prim)		\
   (_prim)->fnContextHandler

#define  vserviceGetPrimitiveData(_prim)				\
    ((_prim)->data)

#define  vserviceSetPrimitiveData(_prim, _data)				\
    (void)((_prim)->data = (_data))

/**  depricated
 **/
#define  vserviceGetPrimitiveHandler(_prim)				\
    ((_prim)->fnHandler)

#define  vserviceSetPrimitiveHandler(_prim, _fn)			\
    (void)((_prim)->fnHandler = (_fn))


/****************************************
 **  attributes and primitives
 ****************************************/
#define  vserviceSetAttributeScalar(_service, _name, _value)		\
    vserviceSetAttribute(_service, _name, vdatatagGetInteger(), _value)

#define  vserviceSetAttributeFloat(_service, _name, _value)		\
    vserviceSetAttribute(_service, _name, vdatatagGetSingleFloat(), _value)

/** !!!  Treat scribes as tags until there is a scribe datatag
 **/
#define  vserviceSetAttributeScribed(_service, _name, _value)		\
    vserviceSetAttribute(_service, _name, vdatatagGetTag(),		\
    			vnameInternGlobalScribed(_value))

#define  vserviceSetAttributeTag(_service, _name, _value)		\
    vserviceSetAttribute(_service, _name, vdatatagGetTag(), _value)

#define  vserviceFindPrimitive(_service, _name)				\
    (vservicePrimitive *)vdictLoad(&(_service)->dictPrimitives, _name)


/************************
 **  primitive iterators
 ************************/
#define  vserviceInitPrimitiveIterator(_iterator, _service)		\
    vdictInitIterator(&(_iterator)->dict, &(_service)->dictPrimitives)

#define  vserviceDestroyPrimitiveIterator(_iterator)			\
    vdictDestroyIterator(&(_iterator)->dict)

#define  vserviceNextPrimitiveIterator(_iterator)			\
    vdictNextIterator(&(_iterator)->dict)

#define  vserviceGetPrimitiveIteratorValue(_iterator)			\
    (vservicePrimitive *)vdictGetIteratorValue(&(_iterator)->dict)


/**********************
 **  other service
 **********************/
#define  vserviceRemovePrimitive(_service, _prim)			\
    vdictRemove(&(_service)->dictPrimitives,				\
		vsignatureGetTag(vserviceGetPrimitiveSignature(_prim)))

#define  vserviceGetNotify(_service)					\
    (_service)->fnNotify

#define  vserviceSetNotify(_service, _fn)				\
    (_service)->fnNotify = (_fn)

#define  vserviceGetData(_service)					\
    (_service)->data

#define  vserviceSetData(_service, _data)				\
    (void)((_service)->data = (_data))

#define  vserviceGetSessionNotify(_service)				\
    (_service)->fnNotifySession

#define  vserviceSetSessionNotify(_service, _fn)			\
    (_service)->fnNotifySession = (_fn)


/*********************
 **  debugging
 *********************/
#if  (vdebugDEBUG)			/*----  #if     vdebugDEBUG  ----*/

#define  vserviceGetGeneralDebugFlags(_service)				\
    ((_service)->flagsDebug & vserviceFLAG_DEBUG_ALL)

#define  vserviceSetGeneralDebugFlags(_service, _flags)			\
    ((_service)->flagsDebug = (_flags & vserviceFLAG_DEBUG_ALL)		\
		    | ((_service)->flagsDebug & ~vserviceFLAG_DEBUG_ALL))

#define  vserviceGetPrimitiveDebugFlags(_service)			\
    ((_service)->flagsDebug & vservicePrimitiveFLAG_DEBUG_ALL)

#define  vserviceSetPrimitiveDebugFlags(_service, _flags)		 \
    ((_service)->flagsDebug = (_flags & vservicePrimitiveFLAG_DEBUG_ALL) \
		| ((_service)->flagsDebug & ~vservicePrimitiveFLAG_DEBUG_ALL))


#else					/*----  #else   vdebugDEBUG  ----*/

#define  vserviceGetGeneralDebugFlags(_service)			0
#define  vserviceSetGeneralDebugFlags(_service, _flags)		/*EMPTY*/
#define  vserviceGetPrimitiveDebugFlags(_service)		0
#define  vserviceSetPrimitiveDebugFlags(_service, _flags)	/*EMPTY*/

#endif					/*----  #endif  vdebugDEBUG  ----*/


/**********************
 **  Session iterators
 **********************/
#define  vserviceDestroySessionIterator(_iterator)	/*EMPTY*/

#define  vserviceNextSessionIterator(_iterator)				\
    ((--(_iterator)->nSessions) >= 0)

#define  vserviceGetSessionIteratorValue(_iterator)			\
    (_iterator)->arraySessions[(_iterator)->nSessions]


/*******************************
 **  deprecated macros
 *******************************/

#define  vserviceSetAttributeScribe(_service, _name, _value)		\
         vserviceSetAttributeScribed(_service, _name, _value)


/*===========================================================================*\
 * * * * * * * *  PRIVATE  FUNCTIONS IMPLEMENTED AS METHODS  * * * * * * * * *
\*===========================================================================*/
#define  vserviceEnable(_service)		\
    vclassSend(vserviceGetClass(_service), vserviceENABLE, (_service))

#define  vserviceDisable(_service)		\
    vclassSend(vserviceGetClass(_service), vserviceDISABLE, (_service))

vportEND_CPLUSPLUS_EXTERN_C

#if (vportUSE_LIB_PRAGMAS && !defined(vdasLIB_MEMBER))
# ifdef vportGALAXY_LIB_SUFFIX
#  pragma comment(lib, "vdas" vportGALAXY_LIB_SUFFIX ".lib")
# else
#  if (vportCPLUSPLUS_SOURCE)
#   if (vportI18N)
#    if (vdebugDEBUG)
#     ifdef _RTLDLL
#      pragma comment(lib, "vdasp.lib")
#     else
#      pragma comment(lib, "vdasps.lib")
#     endif /* (_RTLDLL) */
#    else
#     ifdef _RTLDLL
#      pragma comment(lib, "vdaso.lib")
#     else
#      pragma comment(lib, "vdasos.lib")
#     endif /* (_RTLDLL) */
#    endif /* (vdebugDEBUG) */
#   else
#    if (vdebugDEBUG)
#     ifdef _RTLDLL
#      pragma comment(lib, "vdasn.lib")
#     else
#      pragma comment(lib, "vdasns.lib")
#     endif /* (_RTLDLL) */
#    else
#     ifdef _RTLDLL
#      pragma comment(lib, "vdasm.lib")
#     else
#      pragma comment(lib, "vdasms.lib")
#     endif /* (_RTLDLL) */
#    endif /* (vdebugDEBUG) */
#   endif /* (vportI18N) */
#  else
#   if (vportI18N)
#    if (vdebugDEBUG)
#     ifdef _RTLDLL
#      pragma comment(lib, "vdasl.lib")
#     else
#      pragma comment(lib, "vdasls.lib")
#     endif /* (_RTLDLL) */
#    else
#     ifdef _RTLDLL
#      pragma comment(lib, "vdask.lib")
#     else
#      pragma comment(lib, "vdasks.lib")
#     endif /* (_RTLDLL) */
#    endif /* (vdebugDEBUG) */
#   else
#    if (vdebugDEBUG)
#     ifdef _RTLDLL
#      pragma comment(lib, "vdasj.lib")
#     else
#      pragma comment(lib, "vdasjs.lib")
#     endif /* (_RTLDLL) */
#    else
#     ifdef _RTLDLL
#      pragma comment(lib, "vdasi.lib")
#     else
#      pragma comment(lib, "vdasis.lib")
#     endif /* (_RTLDLL) */
#    endif /* (vdebugDEBUG) */
#   endif /* (vportI18N) */
#  endif /* (vportCPLUSPLUS_SOURCE) */
# endif /* defined vportGALAXY_LIB_SUFFIX */
#endif /* vportUSE_LIB_PRAGMAS && "vdasLINK"=="vportLINK" */

#endif				/**----------  vserviceINCLUDED  ----------**/

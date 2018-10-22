/* $Id: vsession.h,v 1.37 1997/09/26 02:39:57 paul Exp $: */

/************************************************************

    vsession.h

    C Interface file for the Session Manager

    (c) Copyright 1994, Visix Software Inc.
    All rights reserved

************************************************************/

#ifndef vsessionINCLUDED	/**----------  vsessionINCLUDED  ----------**/
#define vsessionINCLUDED	(1)

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

#ifndef  vinstanceINCLUDED	/**  implemented as instances	**/
#include vinstanceHEADER
#endif

#ifndef  vscrapINCLUDED		/**  Representation Manager	**/
#include vscrapHEADER
#endif

#ifndef  vdatatagINCLUDED	/**  for attribute typing	**/
#include vdatatagHEADER
#endif

#ifndef  vsignatureINCLUDED	/**  for statement signatures	**/
#include vsignatureHEADER
#endif

#ifndef  vobjectINCLUDED	/**  for object manager **/
#include vobjectHEADER
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
enum {
    vsessionStatementSTATUS_UNSENT		= 0x01000000,
    vsessionStatementSTATUS_PENDING		= 0x02000000,
    vsessionStatementSTATUS_ENDED_SESSION	= 0x03000000,
    vsessionStatementSTATUS_FAILED		= 0x04000000,
    vsessionStatementSTATUS_COMPLETED		= 0x05000000,
    _vsessionStatementMASK_STATUS		= 0x0f000000,	/* private */
    _vsessionStatementFLAG_DESTROY_WHEN_DONE	= 0x10000000	/* private */
};



enum vsessionEventCode {
    vsessionEVENT_BEGIN,
    vsessionEVENT_CANNOT_BEGIN,
    vsessionEVENT_END,
    vsessionEVENT_LOCAL_EXCEPTION
};


#define  _vsessionStatementFLAG_EVENT_INCOMPLETE	0x8000
enum
{
    vsessionStatementEVENT_COMPLETED	= 0x0,
    vsessionStatementEVENT_CANNOT_SEND	= 0x1,
    vsessionStatementEVENT_END_SESSION	= 0x2,
    vsessionStatementEVENT_FAILED	= 0x3
};


/**  general session debugging flags
 **/
enum {
    vsessionFLAG_DEBUG			= 0x000001,
    vsessionFLAG_DEBUG_NOTIFY		= 0x000002,
    vsessionFLAG_DEBUG_ALL		= 0x000003
};

/**  session io debugging flags
 **/
enum {
    vsessionFLAG_DEBUG_IO		= 0x000100,
    vsessionFLAG_DEBUG_IO_BLOCKING	= 0x000200,
    vsessionFLAG_DEBUG_IO_INPUT		= 0x000400,
    vsessionFLAG_DEBUG_IO_OUTPUT	= 0x000800,
    vsessionFLAG_DEBUG_IO_ALL		= 0x000f00
};

/**  statement debugging flags
 **/
enum {
    vsessionStatementFLAG_DEBUG		= 0x010000,
    vsessionStatementFLAG_DEBUG_SEND	= 0x020000,
    vsessionStatementFLAG_DEBUG_NOTIFY	= 0x040000,
    vsessionStatementFLAG_DEBUG_ARG	= 0x100000,
    vsessionStatementFLAG_DEBUG_RESULT	= 0x200000,
    vsessionStatementFLAG_DEBUG_ALL	= 0x370000
};

/*===========================================================================*\
 * * * * * * * * * * * * *  PUBLIC  TYPE  DEFINITIONS  * * * * * * * * * * * *
\*===========================================================================*/
typedef struct vsession			vsession;
typedef struct vsessionClass	        vsessionClass;

typedef int				vsessionEvent;
typedef enum vsessionEventCode		vsessionEventCode;
typedef struct vsessionAttributeIterator vsessionAttributeIterator;

typedef struct vsessionStatement	vsessionStatement;
typedef struct vsessionStatementClass	vsessionStatementClass;

typedef int				vsessionStatementEvent;
typedef int				vsessionStatementEventCode;
typedef int				vsessionStatementStatus;

#ifndef  _vserviceDEFINED_VSERVICE
typedef struct vservice	 vservice;
#define  _vserviceDEFINED_VSERVICE (1)	/** circular dependency  **/
#endif

typedef void  (*vsessionNoteProc)(
	vsession	*session,
	vsessionEvent	*event
	);			 

typedef void  (*vsessionStatementNoteProc)(
	vsessionStatement	*statement,
	vsessionStatementEvent	*event
	);


/*===========================================================================*\
 * * * * * * * * * * *   PUBLIC  FUNCTION  PROTOTYPES  * * * * * * * * * * * *
\*===========================================================================*/

void vsessionStartup(void);


/**********************
 **  session creation
 **********************/
vsession  *vsessionCreate(void);

vsession  *vsessionClone(
	vsession	*session
	);

void  vsessionInit(
	vsession	*session
	);

void  vsessionDestroy(
	vsession	*session
	);

void  _vsessionDestroyFunc(
	vsession	*session
	);

void  vsessionCopyInit(
	vsession	*sessionSource,
	vsession	*sessionDest
	);

vsession *vsessionLoad(
	vresource	 res
	);

void  vsessionLoadInit(
	vsession	*session,
	vresource	 res
	);

void  vsessionStore(
	vsession	*session,
	vresource	 res
	);
    
/**********************
 **  begin/end
 **********************/
void  vsessionBegin(
	vsession	*session
	);

void  vsessionEnd(
	vsession	*session
	);

int   vsessionIsActive(
	vsession	*session
	);

int   vsessionIsActivating(
	vsession	*session
	);

int   vsessionIsDeactivating(
	vsession	*session
	);

int   vsessionIsInactive(
	vsession	*session
	);



/**********************
 **  attributes
 **********************/
void  vsessionSetAttributesFromScrap(
	vsession	*session,
 	vscrap		*scrap
	);
			    
void  vsessionSetAttribute(
	vsession	*session,
	const vname	*name,
	vdatatag	*datatag,	/* NULL destroys */
	...	/* value for datatag */
	);

void  vsessionGetAttribute(
	vsession	*session,
	const vname	*name,
	...	/* pointer to storage for value */
	);

vdatatag  *vsessionFindAttributeDatatag(
	vsession		*session,
	const vname		*name
	);

void  vsessionSetAttributeScalar(
	vsession	*session,
	const vname	*name,
	long		 value
	);

long  vsessionFindAttributeScalar(
	vsession	*session,
	const vname	*name
	);

void  vsessionSetAttributeFloat(
	vsession	*session,
	const vname	*name,
	double		 nValue
	);

double  vsessionFindAttributeFloat(
	vsession	*session,
	const vname	*name
	);

void  vsessionSetAttributeScribed(
	vsession	*session,
	const vname	*name,
	vscribe		*scribeValue
	);

vscribe  *vsessionFindAttributeScribe(
	vsession	*session,
	const vname	*name
	);

void  vsessionSetAttributeTag(
	vsession	*session,
	const vname	*name,
	const vname	*nameValue
	);

const vname  *vsessionFindAttributeTag(
	vsession	*session,
	const vname	*name
	);



/**********************
 **  iterators
 **********************/
void  vsessionInitAttributeIterator(
	vsessionAttributeIterator	*iterator,
	vsession			*session
	);

void  vsessionDestroyAttributeIterator(
	vsessionAttributeIterator	*iterator
	);

vbool  vsessionNextAttributeIterator(
	vsessionAttributeIterator	*iterator
	);

const vname  *vsessionGetAttributeIteratorName(
	vsessionAttributeIterator	*iterator
	);

vdatatag  *vsessionGetAttributeIteratorDatatag(
	vsessionAttributeIterator	*iterator
	);

long  vsessionGetAttributeIteratorValueScalar(
	vsessionAttributeIterator	*iterator
	);

double  vsessionGetAttributeIteratorValueFloat(
	vsessionAttributeIterator	*iterator
	);

vscribe  *vsessionGetAttributeIteratorValueScribe(
	vsessionAttributeIterator	*iterator
	);

const void  *vsessionGetAttributeIteratorValue(
	vsessionAttributeIterator	*iterator
	);



/**********************
 **  other session
 **********************/
vsessionStatementStatus  vsessionCall(
	vsession	*session,
	vtimestamp	*timeout,
	vsignature	*sig,
	...		 /** args for vsessionGetStatementReturnValue (if any)
			  ** followed by args for vsessionSetStatementArgs
			  **/
	);

void  vsessionDump(
	vsession	*session,
	FILE		*fp
	);

int  vsessionGetDestroyWhenInactive(
	vsession	*session
	);

void  vsessionSetDestroyWhenInactive(
	vsession	*session,
	int		 bOn
	);

vservice  *vsessionGetService(
	vsession	*session
	);

void  vsessionSetService(
	vsession	*session,
	vservice	*service
	);

vsessionNoteProc  vsessionGetNotify(
	vsession	*session
	);

void  vsessionSetNotify(
	vsession		*session,
	vsessionNoteProc	 fnNotify
	);

void  vsessionNotify(
	vsession	*session,
        vsessionEvent	*event
	);

void  *vsessionGetData(
	vsession	*session
	);

void  vsessionSetData(
	vsession	*session,
	void		*data
	);


/**************************************
 **  attributed objects	(for commands)
 **************************************/
void  vsessionAddObject(
	vsession	*session,
	const vname	*name,
	vobject		*object
	);

vobject  *vsessionFindObject(
	vsession	*session,
	const vname	*name
	);

void  vsessionRemoveObject(
	vsession	*session,
	const vname	*name
	);



/**********************
 **  session events
 **********************/
vsessionEventCode  vsessionGetEventCode(
	vsessionEvent	*event
	);


/**********************
 **  Generic signatures
 **********************/
vsignature  *vsessionGetShutdownSignature(void);
vsignature  *vsessionGetPingSignature(void);
vsignature  *vsessionGetIssueCommandSignature(void);



/*******************************
 **  create session statements
 *******************************/
vsessionStatementClass *vsessionGetDefaultStatementClass(void);

vsessionStatementClass *vsessionGetStatementClass(
	vsessionStatement	*statement
	);

vinstance *vsessionGetStatementInstance(
	vsessionStatement	*statement
	);

vsessionStatement  *vsessionCreateStatement(void);

void  vsessionInitStatement(
	vsessionStatement	*statement
	);

void  vsessionDestroyStatement(
	vsessionStatement	*statement
	);

void  vsessionNotifyStatement(
	vsessionStatement	*statement,
        vsessionStatementEvent	*event
	);


/*******************************
 **  statement argument lists
 *******************************/
void  vsessionSetStatementArgs(
	vsessionStatement	*statement,
	...		/**  list of values expected by signature  **/
	);

void  vsessionSetStatementArgsScrap(
	vsessionStatement	*statement,
	vscrap			*scrap
	);

void  vsessionGetStatementReturnValue(
	vsessionStatement	*statement,
	...		/**  pointer to storage expected by signature  **/
	);


/**********************
 **  statement other
 **********************/
void  vsessionSetDestroyStatementWhenFinished(
	vsessionStatement	*statement,
	int			 bOn
	);

int  vsessionGetDestroyStatementWhenFinished(
	vsessionStatement	*statement
	);

int  vsessionBlockStatement(
	vsessionStatement	*statement,
	vtimestamp		*timeout
	);

void  vsessionSendStatement(
	vsessionStatement	*statement
	);

vsession  *vsessionGetStatementSession(
	vsessionStatement	*statement
	);

void  vsessionSetStatementSession(
	vsessionStatement	*statement,
	vsession		*session
	);

vsignature  *vsessionGetStatementSignature(
	vsessionStatement	*statement
	);

void  vsessionSetStatementSignature(
	vsessionStatement	*statement,
	vsignature		*signature
	);

void  *vsessionGetStatementData(
	vsessionStatement	*statement
	);

void  vsessionSetStatementData(
	vsessionStatement	*statement,
	void			*data
	);

vsessionStatementNoteProc  vsessionGetStatementNotify(
	vsessionStatement	*statement
	);

void  vsessionSetStatementNotify(
	vsessionStatement		*statement,
	vsessionStatementNoteProc	 fnNotify
	);

vsessionStatementStatus  vsessionGetStatementStatus(
	vsessionStatement	*statement
	);


/**********************
 **  statement events
 **********************/
vbool  vsessionIsStatementEventFinished(
	vsessionStatementEvent	*event
	);

vsessionStatementEventCode  vsessionGetStatementEventCode(
	vsessionStatementEvent	*event
	);


/**********************
 **  statement makers
 **********************/
vsessionStatement  *vsessionMakeStatement(
	vsession		*session,
	vsignature		*sig,
	...		/**  list of values expected by signature  **/
	);

vsessionStatement  *vsessionMakeIssueCommandStatementScribed(
	vsession	*session,
	vscribe		*scribeObjectName,
	vscribe		*scribeCommandName,
	vscrap		*scrapContext
	);

vsessionStatement  *vsessionMakePingStatement(
	vsession	*session
	);

vsessionStatement  *vsessionMakeShutdownStatement(
	vsession	*session
	);


void  vsessionSetIODebugFlags(
	vsession	*session,
	unsigned int	 flags
	);

unsigned int  vsessionGetIODebugFlags(
	vsession	*session
	);

unsigned int  vsessionGetGeneralDebugFlags(
	vsession	*session
	);

void  vsessionSetGeneralDebugFlags(
	vsession	*session,
	unsigned int	 flags
	);

unsigned int  vsessionGetStatementDebugFlags(
	vsession	*session
	);

void  vsessionSetStatementDebugFlags(
	vsession	*session,
	unsigned int	 flags
	);


/*******************************
 **  deprecated functions
 *******************************/
void  vsessionSetAttributeScribe(
	vsession	*session,
	const vname	*name,
	vscribe		*scribeValue
	);

/*===========================================================================*\
 * * * * * * * * *  EXCEPTION  DEFINITIONS   PUBLIC/PRIVATE  * * * * * * * * *
\*===========================================================================*/


/*===========================================================================*\
 * * * * * * * * * * *   PRIVATE  CONSTANT  DEFINITIONS  * * * * * * * * * * *
\*===========================================================================*/

enum {
    _vsessionFLAG_INACTIVE		= 0x01,
    _vsessionFLAG_ACTIVATING		= 0x02,
    _vsessionFLAG_ACTIVE		= 0x04,
    _vsessionFLAG_DEACTIVATING		= 0x08,
    _vsessionMASK_STATUS		= 0x0f,
    _vsessionFLAG_DESTROY_WHEN_INACTIVE	= 0x80
};

enum {
    _vsession_Context,
    _vsession_Location,
    _vsession_Platform,
    _vsession_Port,
    _vsession_Transport,
    _vsessionNUM_PUBLIC_NAMES
};


/*===========================================================================*\
 * * * * * * * * * * * *   PRIVATE  TYPE  DEFINITIONS  * * * * * * * * * * * *
\*===========================================================================*/

/**********************
 **  vsession
 **********************/
struct _vsessionData;

struct vsession {
    vloadable			 loadable;
    vsessionNoteProc		 fnNotify;
    int				 flags;
    vservice			*service;
    struct _vsessionData	*privateData;
    void			*data;
    unsigned int		 flagsDebug;
};

#define  vsessionCLASS(_SUPER, _SESSION)				\
    vloadableCLASS(_SUPER, _SESSION);					\
    vclassMETHOD(vsessionBEGIN, (_SESSION *));				\
    vclassMETHOD(vsessionEND, (_SESSION *));				\
    vclassMETHOD(vsessionSTARTED, (_SESSION *));			\
    vclassMETHOD(vsessionTERMINATED, (_SESSION *));			\
    vclassMETHOD(vsessionSEND_STATEMENT,				\
		 	(_SESSION *session, vsessionStatement *stmnt));	\
    vclassMETHOD_RET(vsessionCALL, vsessionStatementStatus,		\
		    (_SESSION *session, vtimestamp *timeout,		\
		      vsignature *sig, va_list *pResultAndArgList));	\
    vclassMETHOD_RET(vsessionBLOCK, int,				\
		     (_SESSION *session, vtimestamp *timeout));		\
    vclassMETHOD(vsessionNOTIFY,					\
		     (_SESSION *session, vsessionEvent *event))


struct vsessionClass {
    vsessionCLASS(vsessionClass, vsession);
};



/**********************
 **  vsessionStatement
 **********************/
struct vsessionStatement {
    vinstance			 instance;
    vsession			*session;
    vsignature			*signature;
    vscrap			*scrapArgs;
    vscrap			*scrapResult;
    vtimestamp			 timeout;
    unsigned int		 flags;
    vsessionStatementNoteProc	 fnNotify;
    void			*data;
};

#define vsessionStatementCLASS(SUPER, STATEMENT)                         \
    vinstanceCLASS(SUPER, STATEMENT);					 \
    vclassMETHOD(vsessionNOTIFY_STATEMENT,				 \
                 (STATEMENT *statement, vsessionStatementEvent *event))


struct vsessionStatementClass {
    vsessionStatementCLASS(vsessionStatementClass, vsessionStatement);
};




/******************************
 **  vsessionAttributeIterator
 ******************************/
struct  vsessionAttributeIterator
{
    vdictIterator	 iterator;
    vdatatag		*datatagValues;
};


/*===========================================================================*\
 * * * * * * * * * * *   PRIVATE  FUNCTION  PROTOTYPES * * * * * * * * * * * *
\*===========================================================================*/

/**********************
 **  sessions
 **********************/
vsessionClass  *vsessionGetDefaultClass(void);

vloadable  *vsessionGetLoadable(
	vsession	*session
	);

vsessionClass  *vsessionGetClass(
	vsession	*session
	);

vsession *vsessionCreateOfClass(
	vsessionClass	*clas
	);

vsessionStatementStatus  _vsessionCallWithVarArgs(
	vsession	*session,
	vtimestamp	*timeout,
	vsignature	*sig,
	va_list         *arglist
	);

/**********************
 **  statements
 **********************/
#if  (vdebugDEBUG)			/*----------  vdebugDEBUG  ----------*/
vsessionStatement *_vsessionCreateStatementDebug(
	const char	*tag,
	const char	*file,
	int		 line
	);

#endif					/*----------  vdebugDEBUG  ----------*/


/**  misc
 **/
const vname	*_vsessionInternName(int id);

/*===========================================================================*\
 * * * * * * * * *  PRIVATE  FUNCTION  MACRO  DEFINITIONS  * * * * * * * * * *
\*===========================================================================*/
#define  vsessionGetLoadable(_session)					\
    vportBASE_OBJECT(_session, loadable)

#define  vsessionGetClass(_session)					\
    ((vsessionClass *)vloadableGetClass(vsessionGetLoadable(_session)))

#define  vsessionCreateOfClass(_clas)					\
    ((vsession *)vloadableCreateOfClass((vloadableClass *)_clas))

#define  vsessionCreate()						\
	vsessionCreateOfClass(vsessionGetDefaultClass())

#define  vsessionInit(_session)						\
    vloadableInitOfClass(vsessionGetLoadable(_session),			\
			 (vloadableClass *)vsessionGetDefaultClass())

#define  vsessionDestroy(_session)					\
     _vsessionDestroyFunc(_session)

#define  vsessionCopyInit(_src, _dst)					\
    vloadableCopyInit(vsessionGetLoadable(_src), vsessionGetLoadable(_dst))

#define  vsessionClone(_session)					\
    (vsession *)vloadableClone(vsessionGetLoadable(_session))

#define  vsessionLoad(_res)						\
    (vsession *)vloadableLoad(_res)

#define  vsessionLoadInit(_session, _res)				\
    vloadableLoadInit(vsessionGetLoadable(_session), _res)
    
#define  vsessionStore(_session, _res)					\
    vloadableStore(vsessionGetLoadable(_session), _res)
    
#define  vsessionDump(_session, _fp)					\
    vloadableDump(vsessionGetLoadable(_session), _fp)
    

/******************************
 **  attributes and iterators
 ******************************/
#define  vsessionSetAttributeScalar(_session, _name, _value)		\
    vsessionSetAttribute(_session, _name, vdatatagGetInteger(), _value)

#define  vsessionSetAttributeFloat(_session, _name, _value)		\
    vsessionSetAttribute(_session, _name, vdatatagGetSingleFloat(), _value)

/** !!!  Treat scribes as tags until there is a scribe datatag
 **/
#define  vsessionSetAttributeScribed(_session, _name, _value)		\
    vsessionSetAttribute(_session, _name, vdatatagGetTag(),		\
			 vnameInternGlobalScribed(_value))

#define  vsessionSetAttributeTag(_session, _name, _value)		\
    vsessionSetAttribute(_session, _name, vdatatagGetTag(), _value)

#define  vsessionDestroyAttributeIterator(_iterator)		\
    vdictDestroyIterator(&(_iterator)->iterator)

#define  vsessionNextAttributeIterator(_iterator)		\
    vdictNextIterator(&(_iterator)->iterator)

#define  vsessionGetAttributeIteratorName(_iterator)			\
   (const vname *)vdictGetIteratorKey(&(_iterator)->iterator)

#define  vsessionGetAttributeIteratorDatatag(_iterator)			\
   vdatatagGetDictElementDatatag((_iterator)->datatagValues,		\
			 vsessionGetAttributeIteratorName(_iterator))

#define  vsessionGetAttributeIteratorValueScalar(_iterator)		\
   vdictGetIteratorScalar(&(_iterator)->iterator)

#define  vsessionGetAttributeIteratorValueFloat(_iterator)		\
   vdictGetIteratorFloat(&(_iterator)->iterator)

#define  vsessionGetAttributeIteratorValue(_iterator)			\
   vdictGetIteratorValue(&(_iterator)->iterator)

#define  vsessionGetAttributeIteratorValueScribe(_iterator)		\
    vcharScribe((vchar *)vdictGetIteratorValue(&(_iterator)->iterator))



/**********************
 **  begin/end
 **********************/
#define  vsessionIsActivating(_session)					\
    ((_session)->flags & _vsessionFLAG_ACTIVATING)

#define  vsessionIsDeactivating(_session)				\
    ((_session)->flags & _vsessionFLAG_DEACTIVATING)

#define  vsessionIsActive(_session)					\
    ((_session)->flags & _vsessionFLAG_ACTIVE)

#define  vsessionIsInactive(_session)					\
    ((_session)->flags & _vsessionFLAG_INACTIVE)


/**********************
 **  other session
 **********************/
#define  vsessionGetDestroyWhenInactive(_session)			\
    (((_session)->flags & _vsessionFLAG_DESTROY_WHEN_INACTIVE) != 0)

#define  vsessionSetDestroyWhenInactive(_session, _bOn)			\
    if (_bOn) (_session)->flags |= _vsessionFLAG_DESTROY_WHEN_INACTIVE;	\
    else (_session)->flags &= ~_vsessionFLAG_DESTROY_WHEN_INACTIVE


#define  vsessionGetData(_session)					\
    (_session)->data

#define  vsessionSetData(_session, _data)				\
    (_session)->data = (_data)

#define  vsessionGetNotify(_session)					\
    (_session)->fnNotify

#define  vsessionSetNotify(_session, _fn)				\
    (_session)->fnNotify = (_fn)

#define  vsessionGetService(_session)					\
    (_session)->service


/**********************
 **  session events
 **********************/
#define  vsessionGetEventCode(_event)					\
    (*(vsessionEventCode *)(_event))


/**********************
 **  statements
 **********************/

#define vsessionGetStatementInstance(s) \
    (vportBASE_OBJECT(s, instance))

#define vsessionGetStatementClass(s) \
    ((vsessionStatementClass*) \
     vinstanceGetClass(vsessionGetStatementInstance(s)))

#if (vdebugDEBUG)			/*----------  vdebugDEBUG  ----------*/
#define  vsessionCreateStatement()					\
    _vsessionCreateStatementDebug(vmemTAG, __FILE__, __LINE__)

#endif					/*----------  vdebugDEBUG  ----------*/



/**********************
 **  statement other
 **********************/
#define  vsessionGetDestroyStatementWhenFinished(_statement)		\
    (((_statement)->flags & _vsessionStatementFLAG_DESTROY_WHEN_DONE) != 0)

#define  vsessionSetDestroyStatementWhenFinished(_statement, _bOn)	\
    if (_bOn) (_statement)->flags |= _vsessionStatementFLAG_DESTROY_WHEN_DONE;\
    else (_statement)->flags &= ~_vsessionStatementFLAG_DESTROY_WHEN_DONE

#define  vsessionGetStatementSession(_statement)			\
    (_statement)->session

#define  vsessionGetStatementSignature(_statement)			\
    (_statement)->signature

#define  vsessionGetStatementData(_statement)				\
    (_statement)->data

#define  vsessionSetStatementData(_statement, _data)			\
    (_statement)->data = (_data)

#define  vsessionGetStatementNotify(_statement)				\
    (_statement)->fnNotify

#define  vsessionSetStatementNotify(_statement, _fnNotify)		\
    (_statement)->fnNotify = (_fnNotify)

#define  vsessionGetStatementStatus(_statement)				\
    ((vsessionStatementStatus)((_statement)->flags			\
			       & _vsessionStatementMASK_STATUS))


/**********************
 **  statement events
 **********************/
#define  vsessionGetStatementEventCode(_event)				\
    (*(vsessionStatementEventCode *)(_event))
#define  vsessionIsStatementEventFinished(_event)			\
    ((vsessionGetStatementEventCode(_event)				\
     	& _vsessionStatementFLAG_EVENT_INCOMPLETE) == 0)	


/***************
 **  debugging
 ***************/
#if  (vdebugDEBUG)			/*----  #if    vdebugDEBUG  ----*/

#define  vsessionGetGeneralDebugFlags(_session)		\
    ((_session)->flagsDebug & vsessionFLAG_DEBUG_ALL)

#define  vsessionSetGeneralDebugFlags(_session, _flags)			\
    ((_session)->flagsDebug = (_flags & vsessionFLAG_DEBUG_ALL)		\
		    | ((_session)->flagsDebug & ~vsessionFLAG_DEBUG_ALL))

#define  vsessionGetIODebugFlags(_session)		\
    ((_session)->flagsDebug & vsessionFLAG_DEBUG_IO_ALL)

#define  vsessionSetIODebugFlags(_session, _flags)			\
    ((_session)->flagsDebug = (_flags & vsessionFLAG_DEBUG_IO_ALL)	\
		    | ((_session)->flagsDebug & ~vsessionFLAG_DEBUG_IO_ALL))

#define  vsessionGetStatementDebugFlags(_session)		\
    ((_session)->flagsDebug & vsessionStatementFLAG_DEBUG_ALL)

#define  vsessionSetStatementDebugFlags(_session, _flags)		 \
    ((_session)->flagsDebug = (_flags & vsessionStatementFLAG_DEBUG_ALL) \
	    | ((_session)->flagsDebug & ~vsessionStatementFLAG_DEBUG_ALL))


#else					/*----  #else  vdebugDEBUG  ----*/

#define  vsessionGetGeneralDebugFlags(_session)			0
#define  vsessionSetGeneralDebugFlags(_session, _flags)		/*EMPTY*/
#define  vsessionGetIODebugFlags(_session)			0
#define  vsessionSetIODebugFlags(_session, _flags)		/*EMPTY*/
#define  vsessionGetStatementDebugFlags(_session)		0
#define  vsessionSetStatementDebugFlags(_session, _flags)	/*EMPTY*/

#endif					/*----  #endif vdebugDEBUG  ----*/


/*******************************
 **  deprecated macros
 *******************************/
#define  vsessionSetAttributeScribe(_session, _name, _value)		\
         vsessionSetAttributeScribed(_session, _name, _value)

/*===========================================================================*\
 * * * * * * * * *   PRIVATE  CONSTANT  MACRO  DEFINITIONS   * * * * * * * * *
\*===========================================================================*/

#define  vsession_Context	_vsessionInternName(_vsession_Context)
#define  vsession_Location	_vsessionInternName(_vsession_Location)
#define  vsession_Port		_vsessionInternName(_vsession_Port)
#define  vsession_Platform	_vsessionInternName(_vsession_Platform)
#define  vsession_Transport	_vsessionInternName(_vsession_Transport)



/*===========================================================================*\
 * * * * * * * * *   PRIVATE  FUNCTION  METHOD  DEFINITIONS  * * * * * * * * *
\*===========================================================================*/
#define  vsessionBegin(_session)					\
    vclassSend(vsessionGetClass(_session), vsessionBEGIN, (_session))

#define  vsessionEnd(_session)						\
    vclassSend(vsessionGetClass(_session), vsessionEND, (_session))

#define  _vsessionCallWithVarArgs(_session, _timeout, _sig, _arglist)   \
    vclassSend(vsessionGetClass(_session), vsessionCALL,                \
	       (_session, _timeout, _sig, _arglist));
    
#define vsessionNotify(s,e) \
    vclassSend(vsessionGetClass(s), vsessionNOTIFY, (s, e))

#define vsessionNotifyStatement(s,e) \
    vclassSend(vsessionGetStatementClass(s), vsessionNOTIFY_STATEMENT, (s, e))

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

#endif				/**----------  vsessionINCLUDED  ----------**/

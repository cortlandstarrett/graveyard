/* $Id: vurl.h,v 1.10 1997/09/05 20:43:03 robert Exp $ */

/************************************************************

    vurl.h

    C Interface file for universal resource locators

    (c) Copyright Visix Software Inc.
    All rights reserved

************************************************************/

#ifndef  vurlINCLUDED
#define  vurlINCLUDED 1

#ifndef  vportINCLUDED
#include <vport.h>
#endif

#ifndef  vscribeINCLUDED
#include vscribeHEADER
#endif

#ifndef  vcharINCLUDED
#include vcharHEADER
#endif

#ifndef  vnameINCLUDED
#include vnameHEADER
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

vportBEGIN_CPLUSPLUS_EXTERN_C


/*
 * * * * * * * * * * PUBLIC TYPE DEFINITIONS * * * * * * * * * *
 */

typedef struct vurl			 vurl;
typedef struct vurlClass		 vurlClass;


/*
 * * * * * * * * * * PUBLIC MACRO DEFINITIONS * * * * * * * * * *
 */

#define vurl_Ftp			_vurlPredefs[_vurl_Ftp]
#define vurl_Http			_vurlPredefs[_vurl_Http]
#define vurl_Gopher			_vurlPredefs[_vurl_Gopher]
#define vurl_Mailto			_vurlPredefs[_vurl_Mailto]
#define vurl_News			_vurlPredefs[_vurl_News]
#define vurl_Nntp			_vurlPredefs[_vurl_Nntp]
#define vurl_Telnet			_vurlPredefs[_vurl_Telnet]
#define vurl_Wais			_vurlPredefs[_vurl_Wais]
#define vurl_File			_vurlPredefs[_vurl_File]
#define vurl_Prospero			_vurlPredefs[_vurl_Prospero]
#define vurl_Ldap			_vurlPredefs[_vurl_Ldap]
#define vurl_Scheme			_vurlPredefs[_vurl_Scheme]
#define vurl_NetLocation		_vurlPredefs[_vurl_NetLocation]
#define vurl_Path			_vurlPredefs[_vurl_Path]
#define vurl_Parameters			_vurlPredefs[_vurl_Parameters]
#define vurl_Query			_vurlPredefs[_vurl_Query]
#define vurl_Fragment			_vurlPredefs[_vurl_Fragment]


/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */

void vurlStartup(
    void
    );

vurlClass *vurlGetDefaultClass(
    void
    );

vurl *vurlCreateOfClass(
    vurlClass				*clas
    );

vurl *vurlCreate(
    void
    );

void vurlInitOfClass(
    vurl				*url,
    vurlClass				*clas
    );

void vurlInit(
    vurl				*url
    );

void vurlDestroy(
    vurl				*url
    );

vurl *vurlClone(
    vurl				*url
    );

void vurlCopyInit(
    vurl				*url,
    vurl				*target
    );

void vurlCopy(
    vurl				*url,
    vurl				*target
    );

vurl *vurlLoad(
    vresource				 resource
    );

void vurlLoadInit(
    vurl				*url,
    vresource				 resurce
    );

void vurlStore(
    vurl				*url,
    vresource				 resource
    );

void vurlSetTag(
    vurl				*url,
    const vname				*tag
    );

void vurlSetData(
    vurl				*url,
    const void				*data
    );

void vurlSetScheme(
    vurl				*url,
    const vchar				*scheme
    );

void vurlSetSchemeScribed(
    vurl				*url,
    vscribe				*scribe
    );

void vurlSetNetLocation(
    vurl				*url,
    const vchar				*location
    );

void vurlSetNetLocationScribed(
    vurl				*url,
    vscribe				*scribe
    );

void vurlSetPath(
    vurl				*url,
    const vchar				*path
    );

void vurlSetPathScribed(
    vurl				*url,
    vscribe				*scribe
    );

void vurlSetParameters(
    vurl				*url,
    const vchar				*parameters
    );

void vurlSetParametersScribed(
    vurl				*url,
    vscribe				*scribe
    );

void vurlSetQuery(
    vurl				*url,
    const vchar				*query
    );

void vurlSetQueryScribed(
    vurl				*url,
    vscribe				*scribe
    );

void vurlSetFragment(
    vurl				*url,
    const vchar				*fragment
    );

void vurlSetFragmentScribed(
    vurl				*url,
    vscribe				*scribe
    );

vloadable *vurlGetLoadable(
    vurl				*url
    );

vinstance *vurlGetInstance(
    vurl				*url
    );

vurlClass *vurlGetClass(
    vurl				*url
    );

const vname *vurlGetTag(
    vurl				*url
    );

const void *vurlGetData(
    vurl				*url
    );

vbool vurlHasScheme(
    vurl				*url
    );

const vname *vurlGetScheme(
    vurl				*url
    );

vbool vurlHasNetLocation(
    vurl				*url
    );

const vchar *vurlGetNetLocation(
    vurl				*url
    );

vbool vurlHasPath(
    vurl				*url
    );

const vchar *vurlGetPath(
    vurl				*url
    );

vbool vurlHasParameters(
    vurl				*url
    );

const vchar *vurlGetParameters(
    vurl				*url
    );

vbool vurlHasQuery(
    vurl				*url
    );

const vchar *vurlGetQuery(
    vurl				*url
    );

vbool vurlHasFragment(
    vurl				*url
    );

const vchar *vurlGetFragment(
    vurl				*url
    );

vbool vurlIsEmpty(
    vurl				*url
    );

vurl *vurlFromString(
    const vchar				*string
    );

vurl *vurlFromStringScribed(
    vscribe				*scribe
    );

void vurlResolve(
    vurl				*url,
    vurl				*base
    );

vscribe *vurlScribe(
    vurl				*url
    );

vscribe *vurlScribeEncoded(
    vurl				*url
    );

/* URL scribes */

vscribe *vurlScribeDecode(
    const vchar				*string
    );

vscribe *vurlScribeEncode(
    const vchar				*string,
    const vchar				*characters
    );


/*
 * * * * * * * * * * PRIVATE CONSTANT DEFINITIONS * * * * * * * * * *
 */

enum {
    _vurlOWN_NET_LOCATION		= 0x0001,
    _vurlOWN_PATH			= 0x0002,
    _vurlOWN_PARAMETERS			= 0x0004,
    _vurlOWN_QUERY			= 0x0008,
    _vurlOWN_FRAGMENT			= 0x0010
};

enum {
    _vurl_Ftp				= 0,
    _vurl_Http,
    _vurl_Gopher,
    _vurl_Mailto,
    _vurl_News,
    _vurl_Nntp,
    _vurl_Telnet,
    _vurl_Wais,
    _vurl_File,
    _vurl_Prospero,
    _vurl_Ldap,
    _vurl_Scheme,
    _vurl_NetLocation,
    _vurl_Path,
    _vurl_Parameters,
    _vurl_Query,
    _vurl_Fragment,
    _vurlCOUNT
};


/*
 * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * *
 */

struct vurl {
    vloadable				 loadable;
    unsigned short			 flags;
    const void				*data;
    const vname				*scheme;
    const vchar				*netLocation;
    const vchar				*path;
    const vchar				*parameters;
    const vchar				*query;
    const vchar				*fragment;
};

#define vurlCLASS(SUPER, URL)						      \
    vloadableCLASS(SUPER, URL);						      \
    vclassMETHOD(vurlSET_DATA, (URL *url, const void *data));		      \
    vclassMETHOD(vurlSET_SCHEME_SCRIBED, (URL *url, vscribe *scheme));	      \
    vclassMETHOD(vurlSET_NET_LOCATION_SCRIBED, (URL *url, vscribe *location));\
    vclassMETHOD(vurlSET_PATH_SCRIBED, (URL *url, vscribe *path));	      \
    vclassMETHOD(vurlSET_PARAMETERS_SCRIBED, (URL *url, vscribe *parameters));\
    vclassMETHOD(vurlSET_QUERY_SCRIBED, (URL *url, vscribe *query));	      \
    vclassMETHOD(vurlSET_FRAGMENT_SCRIBED, (URL *url, vscribe *fragment));    \
    vclassMETHOD_RET(vurlIS_EMPTY, vbool, (URL *url));			      \
    vclassMETHOD(vurlRESOLVE, (URL *url, URL *base));			      \
    vclassMETHOD_RET(vurlSCRIBE_ENCODED, vscribe *, (URL *url))

struct vurlClass {
    vurlCLASS(vurlClass, vurl);
};

/*
 * This iterator was pulled for now because it's not complete.
 * At some point in the future, it'd be cool to finish implementing 
 * this.
 * 
 * See url.c for the partial implementation and see either Shawn Carnell
 * or Greg Thompson for more info.  This API is documented in vurl.vdr
 * but is marked "prerelease".
 */
typedef struct vurlPathComponentIterator	vurlPathComponentIterator;

struct vurlPathComponentIterator {
    vchar				*path, *scan, *end;
};


/*
 * * * * * * * * * * PRIVATE EXTERNAL VARIABLES * * * * * * * * * *
 */

extern vportLINK const vname		*_vurlPredefs[];


/*
 * * * * * * * * * * PRIVATE PROTOTYPES * * * * * * * * * *
 */

/* 
 * We're keeping this private for now until 1) we understand how
 * feasible it is given the spec and 2) we know if there's going to be
 * an alternative vfsPath (vfile?).  
 */
vurl *_vurlFromPath(
    const vfsPath			*path
    );


#if (vdebugDEBUG)
vscribe *_vurlScribeDecodeDebug(
    const vchar				*string,
    const char				*tag,
    const char				*file,
    int					 line
    );
#else
vscribe *_vurlScribeDecode(
    const vchar				*string
    );
#endif

#if (vdebugDEBUG)
vscribe *_vurlScribeEncodeDebug(
    const vchar				*string,
    const vchar				*characters,
    const char				*tag,
    const char				*file,
    int					 line
    );
#else
vscribe *_vurlScribeEncode(
    const vchar				*string,
    const vchar				*characters
    );
#endif


/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * *
 */

#define vurlGetLoadable(u)						      \
	vportBASE_OBJECT(u, loadable)
#define vurlGetInstance(u)						      \
	vloadableGetInstance(vurlGetLoadable(u))

#define vurlCreateOfClass(c)						      \
	((vurl *) vloadableCreateOfClass((vloadableClass *) (c)))
#define vurlCreate()							      \
	vurlCreateOfClass(vurlGetDefaultClass())
#define vurlInitOfClass(u, c)						      \
	vloadableInitOfClass(vurlGetLoadable(u), (vurlClass *) (c))
#define vurlInit(u)							      \
	vurlInitOfClass(u, vurlGetDefaultClass())
#define vurlDestroy(u)							      \
	vloadableDestroy(vurlGetLoadable(u))
#define vurlClone(u)							      \
	((vurl *) vloadableClone(vurlGetLoadable(u)))
#define vurlCopyInit(u, t)						      \
	vloadableCopyInit(vurlGetLoadable(u), vurlGetLoadable(t))
#define vurlCopy(u, t)							      \
	vloadableCopy(vurlGetLoadable(u), vurlGetLoadable(t))
#define vurlLoad(r)							      \
	((vurl *) vloadableLoad(r))
#define vurlLoadInit(u, r)						      \
	vloadableLoadInit(vurlGetLoadable(u), r)
#define vurlStore(u, r)							      \
	vloadableStore(vurlGetLoadable(u), r)
#define vurlSetTag(u, t)						      \
	vloadableSetTag(vurlGetLoadable(u), t)
#define vurlSetScheme(u, s)						      \
	vurlSetSchemeScribed(u, ((s)?vcharScribe(s):(vscribe *)NULL))
#define vurlSetNetLocation(u, l)					      \
	vurlSetNetLocationScribed(u, ((l)?vcharScribe(l):(vscribe *)NULL))
#define vurlSetPath(u, p)						      \
	vurlSetPathScribed(u, ((p)?vcharScribe(p):(vscribe *)NULL))
#define vurlSetParameters(u, p)						      \
	vurlSetParametersScribed(u, ((p)?vcharScribe(p):(vscribe *)NULL))
#define vurlSetQuery(u, q)						      \
	vurlSetQueryScribed(u, ((q)?vcharScribe(q):(vscribe *)NULL))
#define vurlSetFragment(u, f)						      \
	vurlSetFragmentScribed(u, ((f)?vcharScribe(f):(vscribe *)NULL))
#define vurlGetClass(u)							      \
	((vurlClass *) vloadableGetClass(vurlGetLoadable(u)))
#define vurlGetTag(u)							      \
	vloadableGetTag(vurlGetLoadable(u))
#define vurlGetData(u)							      \
	(u)->data
#define vurlHasScheme(u)						      \
	((u)->scheme != vnameNULL ? vTRUE : vFALSE)
#define vurlGetScheme(u)						      \
	(u)->scheme
#define vurlHasNetLocation(u)						      \
	((u)->netLocation != NULL ? vTRUE : vFALSE)
#define vurlGetNetLocation(u)						      \
	(u)->netLocation
#define vurlHasPath(u)							      \
	((u)->path != NULL ? vTRUE : vFALSE)
#define vurlGetPath(u)							      \
	(u)->path
#define vurlHasParameters(u)						      \
	((u)->parameters != NULL ? vTRUE : vFALSE)
#define vurlGetParameters(u)						      \
	(u)->parameters
#define vurlHasQuery(u)							      \
	((u)->query != NULL ? vTRUE : vFALSE)
#define vurlGetQuery(u)							      \
	(u)->query
#define vurlHasFragment(u)						      \
	((u)->fragment != NULL ? vTRUE : vFALSE)
#define vurlGetFragment(u)						      \
	(u)->fragment
#define vurlFromString(s)						      \
	vurlFromStringScribed(vcharScribe(s))
#if (vdebugDEBUG)
#define vurlScribeDecode(s)						      \
	_vurlScribeDecodeDebug(s, vmemTAG, __FILE__, __LINE__)
#define vurlScribeEncode(s, c)						      \
	_vurlScribeEncodeDebug(s, c, vmemTAG, __FILE__, __LINE__)
#else
#define vurlScribeDecode(s)						      \
	_vurlScribeDecode(s)
#define vurlScribeEncode(s, c)						      \
	_vurlScribeEncode(s, c)
#endif


/*
 * * * * * * * * * * PRIVATE FUNCTION MESSAGE DEFINITIONS * * * * * * * * * *
 */

#define vurlSetData(u, d)						      \
	vclassSend(vurlGetClass(u), vurlSET_DATA, (u, d))
#define vurlSetSchemeScribed(u, s)					      \
	vclassSend(vurlGetClass(u), vurlSET_SCHEME_SCRIBED, (u, s))
#define vurlSetNetLocationScribed(u, s)					      \
	vclassSend(vurlGetClass(u), vurlSET_NET_LOCATION_SCRIBED, (u, s))
#define vurlSetPathScribed(u, s)					      \
	vclassSend(vurlGetClass(u), vurlSET_PATH_SCRIBED, (u, s))
#define vurlSetParametersScribed(u, s)					      \
	vclassSend(vurlGetClass(u), vurlSET_PARAMETERS_SCRIBED, (u, s))
#define vurlSetQueryScribed(u, q)					      \
	vclassSend(vurlGetClass(u), vurlSET_QUERY_SCRIBED, (u, q))
#define vurlSetFragmentScribed(u, s)					      \
	vclassSend(vurlGetClass(u), vurlSET_FRAGMENT_SCRIBED, (u, s))
#define vurlIsEmpty(u)							      \
	vclassSend(vurlGetClass(u), vurlIS_EMPTY, (u))
#define vurlResolve(u, b)						      \
	vclassSend(vurlGetClass(u), vurlRESOLVE, (u, b))
#define vurlScribeEncoded(u)						      \
	vclassSend(vurlGetClass(u), vurlSCRIBE_ENCODED, (u))

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

#endif /* #ifndef vurlINCLUDED */

/* $Id: vhelphtmllocator.h,v 1.11 1997/09/11 23:13:33 robert Exp $ */

/* -----------------------------------------------------------------------
 *
 *  vhelphtmllocator.h
 *
 *  Programming interface to the vhelphtmllocator class.
 *
 *  (c) Copyright Visix Software
 *  All rights reserved
 *
 * -----------------------------------------------------------------------
 */

#ifndef vhelphtmllocatorINCLUDED
#define vhelphtmllocatorINCLUDED	1

#ifndef  vportINCLUDED
#include <vport.h>
#endif

#ifndef  vhelpreflocatorINCLUDED
#include vhelpreflocatorHEADER
#endif

#ifndef  vurlINCLUDED
#include vurlHEADER
#endif

#ifndef  vinstallINCLUDED
#include vinstallHEADER
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * * * * * * * * * * PUBLIC TYPE DEFINITIONS * * * * * * * * * *
 */

typedef struct	vhelphtmllocator		vhelphtmllocator;
typedef	struct	vhelphtmllocatorClass		vhelphtmllocatorClass;       

/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */

/*
 * Creation/Destruction/Class Management
 */

vhelphtmllocatorClass *vhelphtmllocatorGetDefaultClass(
    void
    );

vhelphtmllocatorClass *vhelphtmllocatorGetClass(
    vhelplocator	*helplocator
    );

vhelphtmllocator *vhelphtmllocatorCreateOfClass(
    vhelphtmllocatorClass	*helphtmllocatorClass
    );

vhelphtmllocator *vhelphtmllocatorCreate(
    void
    );

vhelphtmllocator *vhelphtmllocatorInitOfClass(
   vhelphtmllocator		*helphtmllocator,
   vhelphtmllocatorClass		*clas
   );

vhelphtmllocator *vhelphtmllocatorInit(
   vhelphtmllocator		*helphtmllocator
   );

vhelphtmllocator *vhelphtmllocatorDestroy(
   vhelphtmllocator		*helphtmllocator
   );

vhelpreflocator *vhelphtmllocatorGetLocator(
    vhelphtmllocator		*helphtmllocator
    );

/*
 * Class specific API.
 */

vinstance *vhelphtmllocatorLocateHelp(
    vhelphtmllocator	*helplocator,
    vhelprequest	*request
    );

vdict *vhelphtmllocatorGetMapDict(
    vhelphtmllocator	*helplocator
    );

const vchar *vhelphtmllocatorGetMapFileName(
    vhelphtmllocator	*helplocator
    );

void vhelphtmllocatorSetMapFileName(
    vhelphtmllocator	*helplocator,
    const vchar		*name
    );

void vhelphtmllocatorSetMapFileNameScribed(
    vhelphtmllocator	*helplocator,
    vscribe		*scribe
    );

const vchar *vhelphtmllocatorGetDocDirectoryName(
    vhelphtmllocator	*helplocator
    );

void vhelphtmllocatorSetDocDirectoryName(
    vhelphtmllocator	*helplocator,
    const vchar		*name
    );

void vhelphtmllocatorSetDocDirectoryNameScribed(
    vhelphtmllocator	*helplocator,
    vscribe		*scribe
    );

void vhelphtmllocatorSetBaseURLOwned(
    vhelphtmllocator	*helplocator,
    vurl		*url
    );

vurl *vhelphtmllocatorGetBaseURL(
    vhelphtmllocator	*helplocator
    );

vfsPath *vhelphtmllocatorGetMapFilePath(
    vhelphtmllocator	*helplocator
    );

void vhelphtmllocatorSetMapFilePathOwned(
    vhelphtmllocator	*helplocator,
    vfsPath 		*path
    );

/*
 * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * * *
 */
struct vhelphtmllocator {
    vhelpreflocator	 locator;
    unsigned short	 flags;
    const vchar		*dirname;
    const vchar		*filename;
    vfsPath		*path;
    vurl		*base;
    vdict		*map;
    vnameTable		*table;
};

#define vhelphtmllocatorCLASS(SUPER, HELPLOC)		        	\
    vhelpreflocatorCLASS(SUPER, HELPLOC);				\
    vclassMETHOD_RET(vhelphtmllocatorGET_MAP_DICT, vdict *, 		\
		     (HELPLOC *helploc));				\
    vclassMETHOD_RET(vhelphtmllocatorGET_BASE_URL, vurl *,		\
		 (HELPLOC *helploc));					\
    vclassMETHOD(vhelphtmllocatorSET_BASE_URL_OWNED, 			\
		 (HELPLOC *helploc, vurl *url));			\
    vclassMETHOD(vhelphtmllocatorSET_DOC_DIRECTORY_NAME_SCRIBED, 	\
		 (HELPLOC *helploc, vscribe *name));			\
    vclassMETHOD(vhelphtmllocatorSET_MAP_FILE_NAME_SCRIBED, 		\
		 (HELPLOC *helploc, vscribe *name));			\
    vclassMETHOD(vhelphtmllocatorSET_MAP_FILE_PATH_OWNED, 		\
		 (HELPLOC *helploc, vfsPath *path))
    
struct vhelphtmllocatorClass {
    vhelphtmllocatorCLASS(vhelphtmllocatorClass, vhelphtmllocator);
};

/*
 * Flag values.
 */
enum 
{
    _vhelphtmllocatorFILENAME_OWNED 		= 0x0001,
    _vhelphtmllocatorDIRNAME_OWNED		= 0x0002,
    _vhelphtmllocatorCOULDNT_FIND_BASE_URL	= 0x0004
};

/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * * *
 */
#define vhelphtmllocatorGetLocator(o)     vportBASE_OBJECT((o), locator)
#define vhelphtmllocatorGetClass(l)				        \
    ((vhelphtmllocatorClass*)						\
      vhelpreflocatorGetClass(vhelphtmllocatorGetLocator(l)))
#define vhelphtmllocatorCreateOfClass(c) 				\
    ((vhelphtmllocator *)						\
      vhelpreflocatorCreateOfClass((vhelphtmllocatorClass*)(c)))
#define vhelphtmllocatorInitOfClass(o, c) 				\
      vhelpreflocatorInitOfClass(vhelphtmllocatorGetLocator(o),		\
       (vhelplocatorClass*)(c))
#define vhelphtmllocatorInit(l)						\
    vhelphtmllocatorInitOfClass(l, vhelphtmllocatorGetDefaultClass())
#define vhelphtmllocatorCreate()					\
    vhelphtmllocatorCreateOfClass(vhelphtmllocatorGetDefaultClass())

#define vhelphtmllocatorLocateHelp(l, r)				\
    vhelpreflocatorLocateHelp(vhelphtmllocatorGetLocator(l), r)

#define vhelphtmllocatorSetMapFileName(l, n)				\
    vhelphtmllocatorSetMapFileNameScribed(l, vcharScribe(n))

#define vhelphtmllocatorGetMapFileName(l)	(l)->filename
#define vhelphtmllocatorGetMapFilePath(l)	(l)->path
#define vhelphtmllocatorGetDocDirectoryName(l)	(l)->dirname

/*
 * * * * * * * * * * PRIVATE FUNCTION MESSAGE DEFINITIONS * * * * * * * * * *
 */
#define vhelphtmllocatorSetMapFileNameScribed(d, c)			\
    vclassSend(vhelphtmllocatorGetClass(d), 				\
	       vhelphtmllocatorSET_MAP_FILE_NAME_SCRIBED, (d, c))
#define vhelphtmllocatorSetMapFilePathOwned(d, p)			\
    vclassSend(vhelphtmllocatorGetClass(d), 				\
	       vhelphtmllocatorSET_MAP_FILE_PATH_OWNED, (d, p))
#define vhelphtmllocatorSetDocDirectoryNameScribed(d, c)		\
    vclassSend(vhelphtmllocatorGetClass(d), 				\
	       vhelphtmllocatorSET_DOC_DIRECTORY_NAME_SCRIBED, (d, c))
#define vhelphtmllocatorGetBaseURL(d)					\
    vclassSend(vhelphtmllocatorGetClass(d),				\
	       vhelphtmllocatorGET_BASE_URL, (d))
#define vhelphtmllocatorSetBaseURLOwned(d, u)				\
    vclassSend(vhelphtmllocatorGetClass(d), 				\
	       vhelphtmllocatorSET_BASE_URL_OWNED, (d, u))
#define vhelphtmllocatorGetMapDict(d)					\
    vclassSend(vhelphtmllocatorGetClass(d), vhelphtmllocatorGET_MAP_DICT, (d))

vportEND_CPLUSPLUS_EXTERN_C

#endif /* vhelphtmllocatorINCLUDED */




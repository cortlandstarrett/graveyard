/* $Id: vresolver.h,v 1.11 1997/06/19 00:59:07 robert Exp $ */

/************************************************************

    vresolver.h

    C Interface file for the Object Resolver

    (c) Copyright Visix Software Inc.
    All rights reserved

************************************************************/

#ifndef vresolverINCLUDED
#define vresolverINCLUDED 1

#ifndef  vportINCLUDED
#include <vport.h>		/* for v*HEADER */
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

#ifndef  vfsINCLUDED
#include vfsHEADER
#endif

#ifndef  vresourceINCLUDED
#include vresourceHEADER
#endif

#ifndef  vloadableINCLUDED
#include vloadableHEADER
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * * * * * * * * * * PUBLIC CONSTANT DEFINITIONS * * * * * * * * * *
 */

#define vresolver_FilePath		_vresolver_FilePath
#define vresolver_ResourcePath		_vresolver_ResourcePath
#define vresolver_Contents		_vresolver_Contents
#define vresolver_Imports		_vresolver_Imports
#define vresolver_WorkingDirectory	_vresolver_WorkingDirectory
#define vresolver_Linked		_vresolver_Linked
#define vresolver_Relative		_vresolver_Relative

/*
 * * * * * * * * * * PUBLIC TYPE DEFINITIONS * * * * * * * * * *
 */

typedef struct vresolver		vresolver;
typedef struct vresolverClass		vresolverClass;

typedef vresource (*vresolverOpenFileFunc)(
  vfsPath				*path,
  int					 mode
  );

typedef void (*vresolverCloseFileFunc)(
  vresource				 resource
  );

/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */

void vresolverStartup(
    void
    );

/*
 * Resolvers
 */

vresolverClass *vresolverGetDefaultClass(
    void
    );

vresolverClass *vresolverGetClass(
    vresolver		*resolver
    );

vloadable *vresolverGetLoadable(
    vresolver		*resolver
    );

vinstance *vresolverGetInstance(
    vresolver		*resolver
    );

vresolver *vresolverCreate(
    void
    );

vresolver *vresolverCreateOfClass(
    vresolverClass	*clas
    );

void vresolverInit(
    vresolver		*resolver
    );

void vresolverInitOfClass(
    vresolver		*resolver,
    vresolverClass	*clas
    );

void vresolverDestroy(
    vresolver		*resolver
    );

vresolver *vresolverClone(
    vresolver		*resolver
    );

void vresolverCopyInit(
    vresolver		*source,
    vresolver		*target
    );

vresolver *vresolverLoad(
    vresource		 resource
    );

void vresolverLoadInit(
    vresolver		*resolver,
    vresource		 resource
    );

void vresolverCopy(
    vresolver		*source,
    vresolver		*target
    );

void vresolverStore(
    vresolver		*resolver,
    vresource		 resource
    );

void vresolverEmbed(
    vresolver		*resolver,
    vresource		 resource
    );

void vresolverLink(
    vresolver		*resolver,
    vresource		 resource
    );

void vresolverDump(
    vresolver		*resolver,
    FILE		*stream
    );

const vname *vresolverGetTag(
    vresolver		*resolver
    );

void vresolverSetTag(
    vresolver		*resolver
    );

/*
 * global resolvers
 */

vresolver *vresolverGetSystem(
    void
    );

void vresolverSetSystem(
    vresolver		*system
    );

vresolver *vresolverGetAliasResolver(
    void
    );

void vresolverSetAliasResolver(
    vresolver		*resolver
    );

/*
 * vresolver attributes
 */

vresolver *vresolverGetParent(
    vresolver		*resolver
    );

void vresolverSetParent(
    vresolver		*resolver,
    vresolver		*parent
    );

int vresolverGetImportCount(
    vresolver		*resolver
    );

vresolver *vresolverGetImportAt(
    vresolver		*resolver,
    int			 index
    );

void vresolverInsertImport(
    vresolver		*resolver,
    int			 index,
    vresolver		*import
    );

void vresolverAppendImport(
    vresolver		*resolver,
    vresolver		*import
    );

vresolver *vresolverRemoveImportAt(
    vresolver		*resolver,
    int			 index
    );

vbool vresolverIsImportAtOwned(
    vresolver		*resolver,
    int			 index
    );

void vresolverSetImportAtOwned(
    vresolver		*resolver,
    int			 index,
    vbool		 owned
    );

vbool vresolverIsImportAtLinked(
    vresolver		*resolver,
    int			 index
    );

void vresolverSetImportAtLinked(
    vresolver		*resolver,
    int			 index,
    vbool		 link
    );

vbool vresolverIsImportAtRelative(
    vresolver		*resolver,
    int			 index
    );

void vresolverSetImportAtRelative(
    vresolver		*resolver,
    int			 index,
    vbool		 relative
    );

vresource vresolverGetContents(
    vresolver		*resolver
    );

void vresolverSetContents(
    vresolver		*resolver,
    vresource		 contents
    );

const vfsPath *vresolverGetFilePath(
    vresolver		*resolver
    );

const vchar *vresolverGetResourcePath(
    vresolver		*resolver
    );

vscribe *vresolverScribeResourcePath(
    vresolver		*resolver
    );

void vresolverSetPath(
    vresolver		*resolver,
    vfsPath		*filePath,
    const vchar		*resourcePath
    );

void vresolverSetPathScribed(
    vresolver		*resolver,
    vfsPath		*filePath,
    vscribe		*resourcePath
    );

vinstance *vresolverLoadObject(
    vresolver		*resolver,
    vresource		 from
    );

void vresolverSetWorkingDirectory(
    vresolver		*resolver,
    vfsPath		*workingDirectory
    );

vfsPath *vresolverGetWorkingDirectory(
    vresolver		*resolver
    );

/*
 * Absolute lookup routines
 */

vinstance *vresolverGet(
    vresolver		*resolver,
    const vchar		*path,
    vclass		*valueClass
    );

vinstance *vresolverGetScribed(
    vresolver		*resolver,
    vscribe		*path,
    vclass		*valueClass
    );

vresource vresolverGetResource(
    vresolver		*resolver,
    const vchar		*path,
    int			type
    );

vresource vresolverGetResourceScribed(
    vresolver		*resolver,
    vscribe		*path,
    int			type
    );

vresource vresolverGetLoadableResource(
    vresolver		*resolver,
    const vchar		*path,
    vclass		*loadableClass
    );

vresource vresolverGetLoadableResourceScribed(
    vresolver		*resolver,
    vscribe		*path,
    vclass		*loadableClass
    );

/*
 * Relative lookup routines
 */

vinstance *vresolverGetFromObject(
    vresolver		*resolver,
    vinstance		*from,
    const vchar		*path,
    vclass		*valueClass
    );

vinstance *vresolverGetFromObjectScribed(
    vresolver		*resolver,
    vinstance		*from,
    vscribe		*path,
    vclass		*valueClass
    );

vinstance *vresolverGetFrom(
    vresolver		*resolver,
    vresource		from,
    const vchar		*path,
    vclass		*valueClass
    );

vinstance *vresolverGetFromScribed(
    vresolver		*resolver,
    vresource		from,
    vscribe		*path,
    vclass		*valueClass
    );

vresource vresolverGetResourceFrom(
    vresolver		*resolver,
    vresource		from,
    const vchar		*path,
    int			type
    );

vresource vresolverGetResourceFromScribed(
    vresolver		*resolver,
    vresource		 from,
    vscribe		*respathScribe,
    int			type
    );

vresource vresolverGetLoadableResourceFrom(
    vresolver		*resolver,
    vresource		 from,
    const vchar		*path,
    vclass		*loadableClass
    );

vresource vresolverGetLoadableResourceFromScribed(
    vresolver		*resolver,
    vresource		 from,
    vscribe		*pathScribe,
    vclass		*loadableClass
    );

/*
 * Global file funcs
 */

void vresolverSetGlobalFileFuncs(
    vresolverOpenFileFunc	openFunc,
    vresolverCloseFileFunc	closeFunc
    );

void vresolverSetCloseFileFunc(
    vresolver			*resolver,
    vresolverCloseFileFunc	 closeFunc
    );

vresolverCloseFileFunc vresolverGetCloseFileFunc(
    vresolver			*resolver
    );


/*
 * * * * * * * * * * PRIVATE CONSTANT DEFINITIONS * * * * * * * * * *
 */

enum {
    _vresolverIMPORT_OWNED		= 0x0001,
    _vresolverIMPORT_LINKED		= 0x0002,
    _vresolverIMPORT_RELATIVE		= 0x0004
};

extern vportLINK const vname *_vresolver_FilePath;
extern vportLINK const vname *_vresolver_ResourcePath;
extern vportLINK const vname *_vresolver_Imports;
extern vportLINK const vname *_vresolver_Contents;
extern vportLINK const vname *_vresolver_WorkingDirectory;
extern vportLINK const vname *_vresolver_Linked;
extern vportLINK const vname *_vresolver_Relative;

/*
 * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * *
 */

typedef struct _vresolverImport		_vresolverImport;

struct _vresolverImport {
    vresolver		*resolver;
    unsigned short	 flags;
    vresource		 fromResource;
};

struct vresolver {
    vloadable		 super;

    vdict		*resolvedComponents;

    _vresolverImport	*imports;
    short		importsCount, importsAlloc;

    vresolver		*parent;

    vfsPath		*filePath;
    vstr		*resourcePath;
    vresource		 contents;

    vfsPath		*workingDirectory;
    vresolverCloseFileFunc closeFunc;
};

#define vresolverCLASS(CLASS, OBJECT)					    \
    vloadableCLASS(CLASS, OBJECT);					    \
    vclassMETHOD(vresolverEMBED, (OBJECT *resolver, vresource resource));   \
    vclassMETHOD(vresolverLINK, (OBJECT *resolver, vresource resource));    \
    vclassMETHOD_RET(vresolverLOAD_OBJECT, vinstance *, 		    \
		     (OBJECT *resolver, vresource r))

struct vresolverClass {
    vresolverCLASS(vresolverClass, vresolver);
};


/*
 * * * * * * * * * * PRIVATE FUNCTION PROTOTYPES * * * * * * * * * *
 */

/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * *
 */

/*
 * resolvers
 */

#define vresolverGetLoadable(i) 	vportBASE_OBJECT(i, super)
#define vresolverGetInstance(i) \
    vloadableGetInstance(vresolverGetLoadable(i))
#define vresolverGetClass(i) \
    ((vresolverClass *) vinstanceGetClass(vresolverGetInstance(i)))

#define vresolverCreateOfClass(c) \
    ((vresolver *) vinstanceCreateOfClass((vinstanceClass *)(c)))
#define vresolverCreate() \
    vresolverCreateOfClass(vresolverGetDefaultClass())
#define vresolverInitOfClass(i,c) \
    vinstanceInitOfClass(vresolverGetInstance(i), (vinstanceClass *)(c))
#define vresolverInit(i) \
    vresolverInitOfClass(i, vresolverGetDefaultClass())
#define vresolverDestroy(i) \
    vinstanceDestroy(vresolverGetInstance(i))

#define vresolverClone(i) \
    ((vresolver *) vloadableClone(vresolverGetLoadable(i)))
#define vresolverCopy(i,t) \
    vloadableCopy(vresolverGetLoadable(i), vresolverGetLoadable(t))
#define vresolverCopyInit(i,t) \
    vloadableCopyInitOfSubclass(vresolverGetLoadable(i), \
				vresolverGetLoadable(t), \
		(vloadableClass *) vresolverGetDefaultClass())

#define vresolverLoad(r) \
    ((vresolver *) vloadableLoadOfSubclass(r, \
		(vloadableClass *) vresolverGetDefaultClass()))
#define vresolverLoadInit(i,r) \
    vloadableLoadInitOfSubclass(vresolverGetLoadable(i), (r), \
		(vloadableClass *) vresolverGetDefaultClass())
#define vresolverStore(i,r) \
    vloadableStore(vresolverGetLoadable(i), (r))

#define vresolverDump(i,s) \
    vloadableDump(vresolverGetLoadable(i), (s))

#define vresolverGetTag(r) \
    vloadableGetTag(vresolverGetLoadable(r))
#define vresolverSetTag(r,t) \
    vloadableSetTag(vresolverGetLoadable(r), (t))

#define vresolverGetFilePath(r) \
    ((r)->filePath)
#define vresolverGetResourcePath(r) \
    ((r)->resourcePath)
#define vresolverScribeResourcePath(r) \
    (((r)->resourcePath != NULL) \
       ? vcharScribe((r)->resourcePath) : vcharScribe(vcharGetEmptyString()))

#define vresolverLink(r,e) \
    vclassSend(vresolverGetClass(r), vresolverLINK, (r,e))
#define vresolverEmbed(r, e) \
    vclassSend(vresolverGetClass(r), vresolverEMBED, (r,e))
#define vresolverLoadObject(r,f) \
    vclassSend(vresolverGetClass(r), vresolverLOAD_OBJECT, (r,f))

#define vresolverGetParent(r) \
    ((r)->parent)
#define vresolverSetParent(r,p) \
    ((r)->parent = (p))

#define vresolverGetImportCount(r) \
    ((r)->importsCount)
#define vresolverGetImportAt(r,i) \
    ((r)->imports[i].resolver)
#define vresolverIsImportAtOwned(r,i) \
    ((r)->imports[i].flags & _vresolverIMPORT_OWNED ? vTRUE : vFALSE)
#define vresolverIsImportAtLinked(r,i) \
    ((r)->imports[i].flags & _vresolverIMPORT_LINKED ? vTRUE : vFALSE)
#define vresolverIsImportAtRelative(r,i) \
    ((r)->imports[i].flags & _vresolverIMPORT_RELATIVE ? vTRUE : vFALSE)

#define vresolverGetWorkingDirectory(r) \
    ((r)->workingDirectory)
#define vresolverGetCloseFileFunc(r) \
    ((r)->closeFunc)

vportEND_CPLUSPLUS_EXTERN_C

#endif


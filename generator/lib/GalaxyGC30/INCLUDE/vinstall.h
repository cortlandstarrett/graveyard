/* $Id: vinstall.h,v 1.7 1997/05/02 15:51:01 robert Exp $ */

/************************************************************

    vinstall.h

    C Interface file for the Installation Manager

    (c) Copyright Visix Software Inc.
    All rights reserved

************************************************************/

#ifndef vinstallINCLUDED
#define vinstallINCLUDED 1

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

#ifndef  vinstanceINCLUDED
#include vinstanceHEADER
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * * * * * * * * * * PUBLIC CONSTANT DEFINITIONS * * * * * * * * * *
 */

#define vinstall_Application		_vinstall_Application
#define vinstall_ApplicationPreferences	_vinstall_ApplicationPreferences
#define vinstall_Preferences		vname_Preferences
#define vinstall_SearchDirectories	_vinstall_SearchDirectories
#define vinstall_System			_vinstall_System
#define vinstall_SystemPreferences	_vinstall_SystemPreferences



/*
 * * * * * * * * * * PUBLIC TYPE DEFINITIONS * * * * * * * * * *
 */

typedef struct vinstall			vinstall;
typedef struct vinstallClass		vinstallClass;

typedef vbool (*vinstallTestPathFunc)(const void *data, const vfsPath *path);

/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */

void		 vinstallStartup(
	void
	);


/*
 * Installations
 */

vinstallClass	*vinstallGetDefaultClass(
	void
	);

vinstallClass	*vinstallGetClass(
	vinstall			*install
	);

vinstance	*vinstallGetInstance(
	vinstall			*install
	);

vinstall	*vinstallCreate(
	void
	);

vinstall	*vinstallCreateOfClass(
	vinstallClass			*clas
	);

void		 vinstallInit(
	vinstall			*install
	);

void		 vinstallInitOfClass(
	vinstall			*install,
	vinstallClass			*clas
	);

void		 vinstallDestroy(
	vinstall			*install
	);


vinstall	*vinstallGetSearchParent(
	vinstall			*install
	);

void		 vinstallSetSearchParent(
	vinstall			*install,
	vinstall			*parentInstall
	);

vinstall	*vinstallGetSystem(
	void
	);


/*
 * File search routines
 */

int		 vinstallGetSearchDirectoryCount(
	vinstall			*install
	);

vfsPath		*vinstallGetSearchDirectoryAt(
	vinstall			*install,
	int				 index
	);

vbool		 vinstallTestInsertSearchDirectoryOwned(
	vinstall			*install,
	int				 index,
	vfsPath				*path
	);

void		 vinstallInsertSearchDirectoryOwned(
	vinstall			*install,
	int				 index,
	vfsPath				*path
	);

void		 vinstallAppendSearchDirectoryOwned(
	vinstall			*install,
	vfsPath				*path
	);

void		 vinstallRemoveSearchDirectoryAt(
	vinstall			*install,
	int				 index
	);

vfsPath		*vinstallFindDirectoryScribed(
	vinstall			*install,
	vscribe				*directoryScribe
	);

vfsPath		*vinstallFindFileScribed(
	vinstall			*install,
	vscribe				*filenameScribe
	);

vfsPath		*vinstallFindResourceFileScribed(
	vinstall			*install,
	vscribe				*filenameScribe
	);

vfsPath		*vinstallFindDirectory(
	vinstall			*install,
	const vfsPath			*relativePath
	);

vfsPath		*vinstallFindFile(
	vinstall			*install,
	const vfsPath			*relativePath
	);

vfsPath		*vinstallFindResourceFile(
	vinstall			*install,
	const vfsPath			*relativePath
	);

vfsPath		*vinstallTestFindPath(
	vinstall			*install,
	const vfsPath			*relativePath,
	vinstallTestPathFunc		 testerFunc,
	const void			*data
	);

/*
 * File test routines
 */

vbool		 vinstallTestPathExists(
	const void			*data,
	const vfsPath			*path
	);


vbool		 vinstallTestPathIsFile(
	const void			*data,
	const vfsPath			*path
	);

vbool		 vinstallTestPathIsDirectory(
	const void			*data,
	const vfsPath			*path
	);

vbool		 vinstallTestPathIsResourceFile(
	const void			*data,
	const vfsPath			*path
	);


/*
 * Installation directory ($GALAXYHOME, $VIBEHOME, etc.)
 */

const vname	*vinstallGetInstallEnvironmentVariable(
	void
	);


const vfsPath	*vinstallGetInstallDirectory(
	void
	);


const vfsPath	*vinstallGetGalaxyHomeDirectory( /* deprecated */
	void
	);


/*
 * Galaxy system resource file (e.g., "vgalaxy2.vr"):
 */

vresource	 vinstallGetSystemResources(
	void
	);

void		 vinstallSetSystemResources(
	vresource			 resources
	);


/*
 * Galaxy application resource file (e.g., "myapp.vr"):
 */

const vname	*vinstallGetApplicationName(
	void
	);

void		 vinstallSetApplicationName(
	const vname			*name
	);

const vfsPath	*vinstallGetApplicationDirectory(
	void
	);

void		 vinstallSetApplicationDirectory(
        const vfsPath			*directory
	);

vresource	 vinstallGetApplicationResources(
	const vname			*name
	);

void		 vinstallSetApplicationResources(
	const vname			*name,
	vresource			 resources
	);

const vname	*vinstallUseApplicationFilePath(
    	const vchar			*path
    	);

/*
 * Galaxy user resource file (e.g., ".vgalaxy.1.vr", "vgalusr1.vr") :
 */

vresource	 vinstallGetSystemPreferences(
	void
	);

void		 vinstallSetSystemPreferences(
	vresource			 preferences
	);

vresource	 vinstallGetApplicationPreferences(
	const vname			*name
	);

void		 vinstallSetApplicationPreferences(
	const vname			*name,
	vresource			 preferences
	);


/*
 * * * * * * * * * * PRIVATE CONSTANT DEFINITIONS * * * * * * * * * *
 */

extern vportLINK const vname *_vinstall_Application;
extern vportLINK const vname *_vinstall_ApplicationPreferences;
extern vportLINK const vname *_vinstall_SearchDirectories;
extern vportLINK const vname *_vinstall_System;
extern vportLINK const vname *_vinstall_SystemPreferences;
extern vportLINK const vname *_vinstall_star;

/*
 * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * *
 */

struct vinstall {
    vinstance			 super;

    vfsPath		       **searchDirs;
    int				 dirCount;
    int				 dirAlloc;

    vinstall			*parentInstall;

};

#define vinstallCLASS(SUPER, INSTALL)					    \
    vinstanceCLASS(SUPER, INSTALL)

struct vinstallClass {
    vinstallCLASS(vinstallClass, vinstall);
};


/*
 * * * * * * * * * * PRIVATE FUNCTION PROTOTYPES * * * * * * * * * *
 */

int _vinstallSetSystemFileMacIcons(
    const vfsPath 	*path, 
    short 		id,
    int 		isIconFile
    );

int _vinstallSetSystemDirMacIcons(
    const vfsPath 	*dirPath, 
    short 		id
    );

const vname *_vinstallGetResourceFileExtension(void);
vbool _vinstallSavePreferences(vinstall *install);


/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * *
 */

/*
 * installations
 */

#define vinstallGetInstance(i) 	vportBASE_OBJECT(i, super)
#define vinstallGetClass(i) \
    ((vinstallClass *) vinstanceGetClass(vinstallGetInstance(i)))

#define vinstallCreateOfClass(c) \
    ((vinstall *) vinstanceCreateOfClass((vinstanceClass *)(c)))
#define vinstallCreate() \
    vinstallCreateOfClass(vinstallGetDefaultClass())
#define vinstallInitOfClass(i,c) \
    vinstanceInitOfClass(vinstallGetInstance(i), (vinstanceClass *)(c))
#define vinstallInit(i) \
    vinstallInitOfClass(i, vinstallGetDefaultClass())
#define vinstallDestroy(i) \
    vinstanceDestroy(vinstallGetInstance(i))

#define vinstallGetGalaxyHomeDirectory() \
    vinstallGetInstallDirectory()

#define vinstallGetSearchParent(i) \
    ((i)->parentInstall)
#define vinstallSetSearchParent(i,p) \
    ((i)->parentInstall = (p))

#define vinstallAppendSearchDirectoryOwned(i,p) \
    vinstallInsertSearchDirectoryOwned(i, -1, p)

/*
 * * * * * * * * * * PRIVATE FUNCTION MESSAGE DEFINITIONS * * * * * * * * * *
 */


vportEND_CPLUSPLUS_EXTERN_C

#endif


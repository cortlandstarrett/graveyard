/* $Id: vinst.h,v 1.25 1997/10/02 20:01:00 robert Exp $ */

/************************************************************

    vinst.h

    C Interface file for the Installation Manager

    (c) Copyright Visix Software Inc.
    All rights reserved

************************************************************/

#ifndef vinstINCLUDED
#define vinstINCLUDED 1

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

#ifndef  vinstallINCLUDED
#include vinstallHEADER
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * * * * * * * * * * PUBLIC CONSTANT DEFINITIONS * * * * * * * * * *
 */

/*
 * * * * * * * * * * PUBLIC TYPE DEFINITIONS * * * * * * * * * *
 */

vportALIAS(vinst, void)

/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */

void		 vinstStartup(
	void
	);


vfsPath		*vinstFindFileScribed(
	vscribe				 *filenameScribe
	);

vfsPath		*vinstFindResourceFileScribed(
	vscribe				 *filenameScribe
	);

vfsPath		*vinstFindDirectoryScribed(
	vscribe				 *directoryScribe
	);

vfsPath		*vinstFindResource(
	const vchar			*name, 
	const vchar			*filename
	);

vfsPath		*vinstFindSameResourceScribed(
	vscribe				*filename
	);

vresource	 vinstGetSystemResources(
	void
	);


/*
 * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * *
 */

/*
 * * * * * * * * * * PRIVATE FUNCTION PROTOTYPES * * * * * * * * * *
 */

int _vinstSetSystemFileMacIcons(
    const vfsPath 	*path, 
    short 		id,
    int 		isIconFile
    );

int _vinstSetSystemDirMacIcons(
    const vfsPath 	*dirPath, 
    short 		id
    );

const vname *_vinstGetResourceFileExtension(void);

/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * *
 */

#define vinstFindSameResourceScribed(f) \
    vinstallFindResourceFileScribed(vinstallGetSystem(), f)

#define _vinstSetSystemFileMacIcons(p,i,k) \
    _vinstallSetSystemFileMacIcons(p,i,k)
#define _vinstSetSystemDirMacIcons(p,i) \
    _vinstallSetSystemDirMacIcons(p,i)
#define _vinstGetResourceFileExtension() \
    _vinstallGetResourceFileExtension()

/*
 * * * * * * * * * * PRIVATE FUNCTION MESSAGE DEFINITIONS * * * * * * * * * *
 */


vportEND_CPLUSPLUS_EXTERN_C

#endif


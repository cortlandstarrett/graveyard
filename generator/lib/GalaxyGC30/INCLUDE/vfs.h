/* $Id: vfs.h,v 1.110 1997/07/14 19:51:06 robert Exp $ */

/*
	+---------------------------------------------------------------+
	|								|
	|    vfs/vfs.h - Galaxy File System Manager Main Header File	|
	|    =======================================================	|
	|								|
	+---------------------------------------------------------------+
	|								|
	| 	     (c) Copyright 1991,92 Visix Software, Inc. 	|
	|		      All rights reserved.			|
	|								|
	+---------------------------------------------------------------+
	|			   DESCRIPTION				|
	|			   ===========				|
	|								|
	|	This file contains all of the publically exported	|
	|	definitions used by the Galaxy File System Manager.	|
	|	See vfs_private.h for internal vfs data structures, 	|
	|	macros and #defines.					|
	|								|
	+---------------------------------------------------------------+
*/


#ifndef vfsINCLUDED
#define vfsINCLUDED 1

#ifndef  vportINCLUDED
#include <vport.h>
#endif


/* ANSI headers */

#ifndef  vstdioINCLUDED		/* for BUFSIZ */
#include vstdioHEADER
#endif

#ifndef  vlimitsINCLUDED	/* for NAME_MAX, PATH_MAX */
#include vlimitsHEADER
#endif


/* POSIX headers */

#if ( vportNEED_MAC_FILESYSTEM )
#include <files.h>

#else

#ifndef  vsystypesINCLUDED
#include vsystypesHEADER
#endif

#ifndef  vdirentINCLUDED
#include vdirentHEADER
#endif

#ifndef  vsysstatINCLUDED
#include vsysstatHEADER
#endif

#endif

/* Galaxy headers */

#ifndef  vcharINCLUDED
#include vcharHEADER
#endif

#ifndef  vpoolINCLUDED
#include vpoolHEADER
#endif

#ifndef  vclientINCLUDED
#include vclientHEADER
#endif

#ifndef  vstrINCLUDED
#include vstrHEADER
#endif

#ifndef  vtimestampINCLUDED
#include vtimestampHEADER
#endif

#ifndef  vinstanceINCLUDED
#include vinstanceHEADER
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C


/*
 * * * * * * * * * CONSTANTS AND MACRO DEFINITIONS * * * * * * * * * *
 */

#if (NAME_MAX < 255)
#define vfsMAXIMUM_NAME_LEN		255
#else
#define vfsMAXIMUM_NAME_LEN		NAME_MAX
#endif

#define vfsMAXIMUM_PATH_LEN		PATH_MAX

#define vfsIO_BUFFER_SIZE		BUFSIZ			

/* 	
 *	Returned by vfsGetPathVolumeRef() when there is no 
 *	volume reference. On the Mac OS legal volume references
 *      are always negative, so our "not-valid" value should be
 *      positive.
 */
#if ( vportNEED_MAC_FILESYSTEM )
#define vfsNO_VOLUME_REFERENCE		(0)
#define vfsAMBIGUOUS_VOLUME_REFERENCE	(1)
#define vfsINVALID_VOLUME_REFERENCE	(2)
#else
#define vfsNO_VOLUME_REFERENCE	        (-1)	
#endif

/*
 * 	Used by vfsSurrenderFileChannels() to indicate that
 *    	the Galaxy client program wishes to surrender all
 *  	file channels that it has reserved previously. 
 */
#define vfsSURRENDER_ALL_CHANNELS	(-1)

/*
 * 	Value of "no file".
 */

#define vfsNO_FILE			((vfsFile *) NULL)

/*-----------------------------------------------------------------------
 *  File Types/attributes (used internally by the File System Manager
 *  in the vfsInfo structure. Do not change or manipulate this structure
 *  directly.  Use the vfsIs*() macros/functions.)
 *
 *	For internal File System Manager use only!!!
 */
#define vfsFILE				0x00000001
#define vfsDIR				0x00000002
#define vfsSPECIAL			0x00000004
#define vfsLINK				0x00000008
#define vfsVOLUME			0x00000010 /* Some support links to volumes */
/*
 *	Attributes OR'ed with file types above when applicable.
 */
#define vfsRESOLVED_FROM_LINK		0x00000100
#define vfsHIDDEN		        0x00000200
#define vfsARCHIVE			0x00000400 /* DOS archive.	  */
#define vfsSYSTEM			0x00000800 /* DOS/Mac system file.*/
#define vfsEXTRA_FILETYPING		0x10000000 /* Can do more filetyping with system */
/*
 *      On systems that support some level of specific filetyping.
 *      (For example the Mac or VMS)
 */
#define vfsFILETYPE_ASCII_TEXT		0x00000001 /* (usually ascii) text */
#define vfsFILETYPE_EXECUTABLE		0x00000002 /* executable (application) */


/*-----------------------------------------------------------------------*/

/*
 *  Permission constants
 */
#if ( !vportNEED_MAC_FILESYSTEM )
#define vfsOWNER_WRITE			S_IWUSR
#define vfsOWNER_READ			S_IRUSR
#define vfsOWNER_EXECUTE	   	S_IXUSR
#define vfsOWNER_PERMISSIONS_MASK 	S_IRWXU	/* Owner rwx	*/

#define vfsGROUP_WRITE			S_IWGRP
#define vfsGROUP_READ			S_IRGRP
#define vfsGROUP_EXECUTE		S_IXGRP
#define vfsGROUP_PERMISSIONS_MASK 	S_IRWXG	/* Group rwx	*/

#define vfsOTHER_WRITE			S_IWOTH
#define vfsOTHER_READ			S_IROTH
#define vfsOTHER_EXECUTE		S_IXOTH
#define vfsOTHER_PERMISSIONS_MASK 	S_IRWXO	/* Other rwx	*/

#else /* vportNEED_MAC_FILESYSTEM */

#define vfsOWNER_WRITE			00200
#define vfsOWNER_READ			00400
#define vfsOWNER_EXECUTE	   	00100
#define vfsOWNER_PERMISSIONS_MASK       (vfsOWNER_WRITE|vfsOWNER_READ|vfsOWNER_EXECUTE)

#define vfsGROUP_WRITE			00020
#define vfsGROUP_READ			00040
#define vfsGROUP_EXECUTE		00010
#define vfsGROUP_PERMISSIONS_MASK 	(vfsGROUP_WRITE|vfsGROUP_READ|vfsGROUP_EXECUTE)

#define vfsOTHER_WRITE			00002
#define vfsOTHER_READ			00004
#define vfsOTHER_EXECUTE		00001
#define vfsOTHER_PERMISSIONS_MASK 	(vfsOTHER_WRITE|vfsOTHER_READ|vfsOTHER_EXECUTE)

#endif /* vportNEED_MAC_FILESYSTEM */

/*
 *  Access constants
 */
#if ( !vportNEED_MAC_FILESYSTEM )

#define vfsCAN_WRITE			W_OK
#define vfsCAN_READ       		R_OK
#define vfsCAN_EXECUTE			X_OK
#define vfsFILE_EXISTS			F_OK

#else  /* vportNEED_MAC_FILESYSTEM */

#define vfsCAN_READ       		4
#define vfsCAN_WRITE			2
#define vfsCAN_EXECUTE			1
#define vfsFILE_EXISTS			0

#endif /* vportNEED_MAC_FILESYSTEM */


/*
 *  Group/User ID symbolic constants
 */
#if ( !vportNEED_MAC_FILESYSTEM )
#define vfsBAD_UID 	(-1)
#define vfsBAD_GID 	(-1)
#else
#define vfsBAD_UID 	(0)
#define vfsBAD_GID 	(0)
#endif

/*-----------------------------------------------------------------------
 *  vfsFile.mode constants.  (NOTE: the mode field in the vfsFile 
 *				    structure does not correspond to 
 *				    file access modes.  NEVER directly
 *				    change the contents of a vfsFile
 *				    structure.
 */

/*
 *	File open constants
 */
#define vfsOPEN_READ_ONLY		0x00000001
#define vfsOPEN_READ_WRITE 		0x00000002
#define vfsOPEN_WRITE_TRUNCATE 		0x00000004
#define vfsOPEN_APPEND	 		0x00000008
#define vfsALL_OPEN_MODES 		0x0000000f 

/*
 *	For internal File System Manager use only!!!
 */
#define vfsOPEN_NOT_CACHED		0x00000010 /* Do not cache	   */
#define vfsFILE_IN_CACHE		0x00000020 /* File closed in cache */
/*
 *	Used by vfs to mark/identify files that are locked under
 *	certain conditions (This is a hint and is not always guaranteed
 *	to be set if the file is actually locked.  If it is set, all or
 *	some portion of the file is locked.)
 */
#define vfsFILE_IS_LOCKED		0x00000040
/*
 *	Used internally by vfs to mark "files" that cannot legally
 *  	be the target of a seek operation.  (e.g., UNIX pipes and
 *	sockets.)  Set by vfsOpenFile().
 */
#define vfsFILE_SEEK_ILLEGAL		0x00000080
/*
 * For operating systems that have special file sharing modes or
 * "deny bits", the Galaxy default is to allow sharing for both
 * reading and writing.  To turn off one or the other or both,
 * OR in the following flags to the accessType parameter of
 * vfsOpenFile().
 */
#define vfsOPEN_DENY_READ		0x00000200
#define vfsOPEN_DENY_WRITE		0x00000100
#define vfsOPEN_DENY_READ_WRITE	(vfsOPEN_DENY_READ | vfsOPEN_DENY_WRITE)
#define vfsALL_DENY_MODES		0x00000300

/*
 * Some stdio implementations have "binary" and "text" modes for opening
 * files.  The Galaxy default is to use the binary mode, but a text mode
 * is provided to allow proper handling of line terminators.  The flag
 * has no effect on systems without this duality.
 */
#define vfsOPEN_TEXT_MODE		0x00000400

/*-----------------------------------------------------------------------*/


/*
 *  vfsPath.type constants
 */
#define vfsPATH_TYPE_NAME		0x00000001 /* "name" form	 */
#define vfsPATH_TYPE_FULL		0x00000002 /* "/dir/dir" form	 */
#define vfsPATH_TYPE_RELATIVE		0x00000004 /* "./" or "../" form */
#define vfsALL_PATH_TYPES		0x00000007 /* For arg testing	 */

/*-----------------------------------------------------------------------
 *	OR'ed when path is fully canonicalized (not always
 *	accurate to the "outside" world... never explicitly 
 *	use.)
 *
 *	For internal File System Manager use only!!!
 */
#define vfsPATH_TYPE_CANONICAL		0x00000008

/*-----------------------------------------------------------------------*/

/*
 *  	Volume types supported by the File System Manager.  (See 
 *	documentation for vfsGetVolumeType().
 */
#define vfsVOLUME_TYPE_NONEXISTENT	0x00000001 /* Volume nonexistent*/
#define vfsVOLUME_TYPE_UNKNOWN		0x00000002 /* Not known		*/
#define vfsVOLUME_TYPE_REMOVABLE	0x00000004 /* Removeable media	*/
#define vfsVOLUME_TYPE_FIXED		0x00000008 /* Fixed hard disks	*/
#define vfsVOLUME_TYPE_REMOTE		0x00000010 /* Network volumes	*/
#define vfsVOLUME_TYPE_SPECIAL		0x00000020 /* Special volumes	*/
#define vfsALL_VOLUME_TYPES		0x0000003f /* For arg testing	*/

/*-----------------------------------------------------------------------*/

/*
 *  	File types supported by the File System Manager.  (See 
 *	documentation for vfsSetFileType().
 */
#define vfsFILETYPE_UNKNOWN	(-1)	/* Unknown filetype		*/
#define vfsFILETYPE_TEXT	(-2)	/* Stream of characters		*/
#define vfsFILETYPE_APPLICATION	(-3)	/* Launchable application	*/
#define vfsFILETYPE_PICT	(-4)	/* Picture document		*/

/*-----------------------------------------------------------------------*/

/*
 *  	Lock constant indicating lock/test/unlock from the specified
 *  	offset to end-of-file.
 */
#define vfsLOCK_TO_END			0L

/*
 *  Seek constants
 */
#if ( !vportNEED_MAC_FILESYSTEM )
#define vfsSEEK_FROM_START		SEEK_SET
#define vfsSEEK_FROM_CURRENT		SEEK_CUR
#define vfsSEEK_FROM_END		SEEK_END
#else
#define vfsSEEK_FROM_START		0
#define vfsSEEK_FROM_CURRENT		1
#define vfsSEEK_FROM_END		2
#endif

/*
 * 	Type and structure definitions that follow are included in 
 *	the public header file to allow Galaxy Client programs to 
 *	make the proper variable/structure definitions.  DO NOT ACCESS 
 *	OR MANIPULATE THESE STRUCTURES DIRECTLY.  You will compromise
 *	the portability of your Galaxy client program, since these 
 *	structures are subject to change.  Use the File System 
 *	Manager API to manipulate data structures.
 */

typedef long 		vgroupid;	/* Here for compatibility reasons.*/
typedef long		vuserid;	/* Here for compatibility reasons.*/

typedef unsigned long 	vfsType;
typedef unsigned long 	vfsMode;
typedef vgroupid	vfsGroupId;
typedef vuserid		vfsUserId;
typedef int		vfsVolumeRef;
typedef int		vfsFileType;

typedef struct vfsVolume{
  vinstance		 super;

  vfsVolumeRef	 	 volumeRef;	/* In DOS corresponds to the drive
					   number. (i.e., A = 1, Z = 26)  */
  vstr		    	*volumeName;	/* In DOS, corresponds to the 
					   drive letter. (e.g., "A" for A: 
					   drive--not that the colon is
					   not stored.)			  */
} vfsVolume;

/*
 *	Structure to implement the internal volume list.
 */

typedef struct vfsInfo{
  vinstance		 super;

  vfsType 		 fileType;
  vfsMode		 mode;
  vfsGroupId		 groupid;
  vfsUserId		 userid;
  vtimestamp   		 createTime;
  vtimestamp	 	 modTime;
  long			 size;
  unsigned long		 systemFileType;
#if (vportNEED_MAC_FILESYSTEM)
  long			 systemId;
  short			 vrefnum;
#endif
} vfsInfo;

typedef struct vfsFile vfsFile;
typedef struct vfsDir vfsDir;

typedef struct vfsPath{ 
  vinstance		 super;

  vfsVolume   	 	*volume;
  vchar		       **start;
  vchar		       **end;
  vfsType		 type;	/* vfsPATH_TYPE_FULL,  vfsPATH_TYPE_NAME
  				   or vfsPATH_TYPE_RELATIVE 		*/
#if (vportNEED_MAC_FILESYSTEM)
  FSSpec		 spec;
#endif
} vfsPath;

struct vfsDir{
  vinstance		 super;

#if (vportNEED_MAC_FILESYSTEM)
  int			dirVolumeRef;
  long			dirDirID;
  int			dirIndex;
#else
  vfsPath      		*pathName;
  DIR			*dir;
#endif
#if (vportNEED_HPFS_FILESYSTEM)
  vbool			 firstTime;
#endif
};

/*
 *	Data structure to implement part of the File System Manager
 *	file list.  
 */
struct vfsFile{
  vinstance		 super;

  vfsPath	 	*pathName;
#if (vportNEED_MAC_FILESYSTEM)
  short			filePtr;
#else
  FILE			*filePtr;
#endif
  long		 	 offset;
  vfsType	 	 mode;		/* Operating mode, not protection mode*/
  vfsPath  		*cachePath;	/* Used for vfs caching	*/
  vfsFile  		*prev;
  vfsFile  		*next;
};

typedef struct vfsVolumeClass	vfsVolumeClass;
typedef struct vfsPathClass	vfsPathClass;
typedef struct vfsFileClass	vfsFileClass;
typedef struct vfsDirClass	vfsDirClass;
typedef struct vfsInfoClass	vfsInfoClass;

struct vfsVolumeClass {
  vinstanceCLASS(vfsVolumeClass, vfsVolume);
};

struct vfsPathClass {
  vinstanceCLASS(vfsPathClass, vfsPath);
};

struct vfsFileClass {
  vinstanceCLASS(vfsFileClass, vfsFile);
};

struct vfsDirClass {
  vinstanceCLASS(vfsDirClass, vfsDir);
};

struct vfsInfoClass {
  vinstanceCLASS(vfsInfoClass, vfsInfo);
};


typedef struct _vfsVolumeList {
  vfsVolume		*volume;
  struct _vfsVolumeList	*next;
} _vfsVolumeList;

typedef struct vfsVolumeListIterator {
  _vfsVolumeList	*list;
} vfsVolumeListIterator;

#if (!vportCPLUSPLUS_SOURCE)

typedef _vfsVolumeList	vfsVolumeIterator;

#else /* (vportCPLUSPLUS_SOURCE) */

typedef vfsVolumeListIterator vfsVolumeIterator;

#endif /* (vportCPLUSPLUS_SOURCE) */


typedef vexException	 vfsException;

typedef vfsException	   vfsIOException;
/*
 *	Sub-classes of vfsIOException:
 */
typedef vfsIOException	      vfsReadException;
typedef vfsIOException	      vfsWriteException;
typedef vfsIOException	      vfsReadOnlyException;
typedef vfsIOException	      vfsFileSeekException;
typedef vfsIOException	      vfsLockException;

typedef vfsException	   vfsNameException;
/*
 *	Sub-classes of vfsNameException:
 */
typedef vfsNameException      vfsDirNameException;
typedef vfsNameException      vfsFileNameException;

typedef vfsException	   vfsSystemException;
/*
 *	Sub-classes of vfsSystemException:
 */
typedef vfsSystemException       vfsInterruptException;
typedef vfsSystemException       vfsSystemMaxException;
typedef vfsSystemMaxException      vfsNoSpaceException;
typedef vfsSystemMaxException      vfsNoMemoryException;
typedef vfsSystemMaxException      vfsMaxFilesException;
typedef vfsSystemMaxException      vfsMaxPathException;
typedef vfsSystemMaxException      vfsMaxNameException;
typedef vfsSystemMaxException	   vfsMaxLinksException;
typedef vfsSystemMaxException	   vfsMaxLocksException;

typedef vfsException	   vfsRequestException;

/*
 *	Sub-classes of vfsRequestException:
 */
typedef vfsRequestException      vfsIsDirException;
typedef vfsRequestException      vfsAccessException;
typedef vfsRequestException      vfsExistsException;
typedef vfsRequestException      vfsNotEmptyException;

extern vportLINK const vexClass 	 _vfsExceptionClass;

extern vportLINK const vexClass	 _vfsIOExceptionClass;
extern vportLINK const vexClass	    _vfsReadExceptionClass;
extern vportLINK const vexClass	    _vfsWriteExceptionClass;
extern vportLINK const vexClass	    _vfsReadOnlyExceptionClass;
extern vportLINK const vexClass	    _vfsFileSeekExceptionClass;
extern vportLINK const vexClass	    _vfsLockExceptionClass;

extern vportLINK const vexClass	 _vfsNameExceptionClass;
extern vportLINK const vexClass	    _vfsDirNameExceptionClass;
extern vportLINK const vexClass	    _vfsFileNameExceptionClass;

extern vportLINK const vexClass	 _vfsSystemExceptionClass;
extern vportLINK const vexClass	    _vfsInterruptExceptionClass;
extern vportLINK const vexClass	    _vfsSystemMaxExceptionClass;
extern vportLINK const vexClass	       _vfsNoSpaceExceptionClass;
extern vportLINK const vexClass	       _vfsNoMemoryExceptionClass;
extern vportLINK const vexClass	       _vfsMaxFilesExceptionClass;
extern vportLINK const vexClass	       _vfsMaxPathExceptionClass;
extern vportLINK const vexClass	       _vfsMaxNameExceptionClass;
extern vportLINK const vexClass	       _vfsMaxLinksExceptionClass;
extern vportLINK const vexClass	       _vfsMaxLocksExceptionClass;

extern vportLINK const vexClass	 _vfsRequestExceptionClass;
extern vportLINK const vexClass	    _vfsIsDirExceptionClass;
extern vportLINK const vexClass	    _vfsAccessExceptionClass;
extern vportLINK const vexClass	    _vfsExistsExceptionClass;
extern vportLINK const vexClass	    _vfsNotEmptyExceptionClass;

/*
 *	Prototypes for functions to return pointer to the 
 *	highest level exception of a given type.
 */
vfsException	    	    *vfsGetException( void );

vfsIOException		      *vfsGetIOException( void );
vfsReadException		*vfsGetReadException( void );
vfsWriteException		*vfsGetWriteException( void );
vfsReadOnlyException		*vfsGetReadOnlyException( void );
vfsFileSeekException		*vfsGetFileSeekException( void );
vfsLockException		*vfsGetLockException( void );

vfsNameException   	      *vfsGetNameException( void );
vfsDirNameException   	      	*vfsGetDirNameException( void );
vfsFileNameException   	      	*vfsGetFileNameException( void );

vfsSystemException    	      *vfsGetSystemException( void );
vfsInterruptException  	        *vfsGetInterruptException( void );
vfsSystemMaxException  	        *vfsGetSystemMaxException( void );
vfsNoSpaceException  	          *vfsGetNoSpaceException( void );
vfsNoMemoryException  	          *vfsGetNoMemoryException( void );
vfsMaxFilesException  	          *vfsGetMaxFilesException( void );
vfsMaxPathException  	          *vfsGetMaxPathException( void );
vfsMaxNameException  	          *vfsGetMaxNameException( void );
vfsMaxLinksException  	          *vfsGetMaxLinksException( void );
vfsMaxLocksException  	          *vfsGetMaxLocksException( void );

vfsRequestException    	      *vfsGetRequestException( void );
vfsIsDirException    	      	*vfsGetIsDirException( void );
vfsAccessException    	      	*vfsGetAccessException( void );
vfsExistsException    	      	*vfsGetExistsException( void );
vfsNotEmptyException   	      	*vfsGetNotEmptyException( void );

const vexClass	   	*vfsGetExceptionClass( void );

const vexClass		*vfsGetIOExceptionClass( void );
const vexClass		   *vfsGetReadExceptionClass( void );
const vexClass		   *vfsGetWriteExceptionClass( void );
const vexClass		   *vfsGetReadOnlyExceptionClass( void );
const vexClass		   *vfsGetFileSeekExceptionClass( void );
const vexClass		   *vfsGetLockExceptionClass( void );

const vexClass		*vfsGetNameExceptionClass( void );
const vexClass		   *vfsGetDirNameExceptionClass( void );
const vexClass		   *vfsGetFileNameExceptionClass( void );

const vexClass		*vfsGetSystemExceptionClass( void );
const vexClass		   *vfsGetInterruptExceptionClass( void );
const vexClass		   *vfsGetSystemMaxExceptionClass( void );
const vexClass		      *vfsGetNoSpaceExceptionClass( void );
const vexClass		      *vfsGetNoMemoryExceptionClass( void );
const vexClass		      *vfsGetMaxFilesExceptionClass( void );
const vexClass		      *vfsGetMaxPathExceptionClass( void );
const vexClass		      *vfsGetMaxNameExceptionClass( void );
const vexClass		      *vfsGetMaxLinksExceptionClass( void );
const vexClass		      *vfsGetMaxLocksExceptionClass( void );

const vexClass		*vfsGetRequestExceptionClass( void );
const vexClass		   *vfsGetIsDirExceptionClass( void );
const vexClass		   *vfsGetAccessExceptionClass( void );
const vexClass		   *vfsGetExistsExceptionClass( void );
const vexClass		   *vfsGetNotEmptyExceptionClass( void );

/*--------------------------------------------------------------------
 *              F U N C T I O N   P R O T O T Y P E S
 *-------------------------------------------------------------------*/

void vfsInitialize( 
    int 		  numArgs, 
    const vchar        	**args 
    );

void vfsStartup( 
    void
    );

void vfsGetArgs( 
    int 		  *numArgs, 
    const vfsPath	***args 
    );

/*
 *  Functions to manipulate paths
 */
void vfsDestroyPath( 
    vfsPath 		*path
    );

vfsPath	*vfsClonePath( 
    const vfsPath 	*path
    );

void vfsAppendPathScribed( 
    vfsPath 		*path,
    vscribe		*scribe,
    ...
    );

void vfsAppendPath( 
    vfsPath 	      	*path, 
    const vchar		*element,
    ...
    );

void vfsDeletePathElementAt( 
    vfsPath 		*path, 
    int 		 element 
    );

vchar *vfsGetPathElementAt( 
    const vfsPath 	*path, 
    int 		 element 
    );

vstr *vfsClonePathElementAt( 
    const vfsPath 	*path, 
    int 		 element 
    );

int vfsGetPathElementCount( 
    const vfsPath 	*path 
    );

vfsType vfsGetPathType( 
    const vfsPath 	*path 
    );

void vfsDumpPath( 
    FILE 		*file, 
    const vfsPath 	*path 
    );

vbool vfsIsVolumeCaseInsensitive(
    const vfsVolume *volume
    );

int vfsCompareVolume( 
    const vfsVolume 	*volume1, 
    const vfsVolume 	*volume2 
    );

int vfsCompareVolumeCaseInsensitive( 
    const vfsVolume 	*volume1, 
    const vfsVolume 	*volume2 
    );

int vfsComparePath( 
    const vfsPath 	*path1, 
    const vfsPath 	*path2 
    );

int vfsComparePathCaseInsensitive( 
    const vfsPath 	*path1, 
    const vfsPath 	*path2 
    );

vbool vfsIsPathEqual( 
    const vfsPath	*path1,
    const vfsPath  	*path2
    );

void vfsJoinPaths( 
    vfsPath 		*path1, 
    vfsPath 		*path2 
    );

void vfsMakePathCanonical( 
    vfsPath 		*path 
    );

void vfsExpandVariablesInPath( 
    vfsPath 		*path 
    );

vfsPath	*vfsResolvePath( 
    const vfsPath 	*fullPath, 
    const vfsPath 	*relativePath 
    );

void vfsSetPathLeafScribed( 
    vfsPath 		*path, 
    vscribe 		*nameScribe 
    );

void vfsSetPathLeaf( 
    vfsPath 		*path, 
    const vchar 	*name 
    );

vstr *vfsPathToStr( 
    const vfsPath 	*path
    );

vfsPath	*vfsPathFromStrScribed( 
    vscribe		*pathScribe
    );

vfsPath	*vfsPathFromStr( 
    const vchar 	*path
    );

void vfsSetPathVolumeReference( 
    vfsPath 		*path,
    vfsVolumeRef	volRef
    );

void vfsSetPathVolumeNameScribed( 
    vfsPath 		*path, 
    vscribe 		*nameScribe 
    );

void vfsSetPathVolumeName( 
    vfsPath 		*path,
    vchar		*volName
    );

void vfsDestroyPathVolumeName( 
    vfsPath 		*path 
    );

vfsVolumeRef vfsGetPathVolumeRef( 
    vfsPath 		*path
    );

vstr *vfsClonePathVolumeName( 
    vfsPath 		*path
    );

const vchar *vfsGetPathVolumeName( 
    vfsPath 		*path
    );

void vfsSetVolumeNameScribed(
    vfsVolume 		*volume,
    vscribe   		*nameScribe
    );

void vfsSetVolumeName(
    vfsVolume 		*volume, 
    vchar 		*volName
    );

void vfsSetVolumeReference(
    vfsVolume    	*volume,
    vfsVolumeRef   	 volRef
    );

vfsVolumeRef vfsGetVolumeReference(
    const vfsVolume    	*volume
    );

vchar *vfsGetVolumeName(
    const vfsVolume    	*volume
    );

vfsVolume *vfsCreateVolume( 
    void
    );

vfsVolume *vfsCloneVolume( 
    vfsVolume		*volume
    );

void vfsDestroyVolume( 
    vfsVolume		*volume
    );

int vfsGetVolumeType( 
    const vfsVolume	*volume
    );

int vfsIsVolumeValid( 
    const vfsVolume	*volume
    );

vstr *vfsClonePathExtension(
    const vfsPath	*path
    );

void vfsSetPathExtension(
    vfsPath		*path,
    vchar		*extension
    );

void vfsSetPathExtensionScribed(
    vfsPath		*path,
    vscribe		*extension
    );

int vfsComparePathExtension(
    vfsPath		*path1,
    vfsPath		*path2
    );

vfsPath *vfsCloneHomeDirPath( 
    void 
    );

const vfsPath *vfsGetHomeDirPath( 
    void 
    );

vfsPath	*vfsCloneAppDirPath( 
    void 
    );

const vfsPath	*vfsGetAppDirPath( 
    void 
    );

vstr *vfsCloneAppName( 
    void 
    );

const vchar	*vfsGetAppName( 
    void 
    );

vfsPath *vfsFindNameInSearchPathScribed( 
    vscribe 		*nameScribe 
    );

vfsPath *vfsFindNameInSearchPath(
    vchar 		*progname
    );

vbool vfsIsFileInDirectoryScribed( 
    vfsPath 		*dirName, 
    vscribe 		*nameScribe 
    );

vbool vfsIsFileInDirectory( 
    vfsPath 		*dirName, 
    vchar 		*fileName 
    );

void vfsInitVolumeIterator(
    vfsVolumeIterator	**iterator
    );

int vfsNextVolumeIterator(
    vfsVolumeIterator	**iterator
    );

void vfsDestroyVolumeIterator(
    vfsVolumeIterator	**iterator
    );

const vfsVolume *vfsGetVolumeIteratorVolume(
    vfsVolumeIterator	*iterator
    );

const vfsVolume *vfsGetWorkingVolume(
    void
    );

void vfsSetWorkingDir( 
    vfsPath 		*path
    );

const vfsPath *vfsGetWorkingDirPath( 
    void
    );

vfsPath *vfsCloneWorkingDirPath( 
    void
    );

vfsPath *vfsCloneStartupDirPath( 
    void
    );

const vfsPath *vfsGetStartupDirPath( 
    void
    );

void vfsPushDir(
    vfsPath 		*path
    );

void vfsPopDir(
    void
    );


/*
 *  Functions to manipulate directories
 */
vfsDir *vfsOpenDir( 
    const vfsPath 	*path
    );

vstr *vfsReadDir( 
    vfsDir 		*dir
    );

void vfsRewindDir( 
    vfsDir 		*dir
    );

void vfsCloseDir( 
    vfsDir 		*dir
    );

void vfsMakeDir( 
    const vfsPath 	*path,
    vfsMode 		 mode 
    );

void vfsRemoveDir( 
    const vfsPath 	*path
    );

void vfsRename( 
    const vfsPath 	*old, 
    const vfsPath 	*newPath 
    );

void  vfsCopy(
    const vfsPath	*pathFrom,
    const vfsPath	*pathTo
    );

void vfsRemove( 
    const vfsPath 	*path 
    );

void vfsLink( 
    const vfsPath 	*old, 
    const vfsPath 	*newLink 
    );

void vfsGetFileInfo( 
    const vfsPath 	*path, 
    vfsInfo 		*info 
    );

void vfsGetLinkInfo( 
    const vfsPath 	*path, 
    vfsInfo 		*info 
    );

vstr *vfsCloneUserName( 
    vfsInfo 		*info 
    );

vstr *vfsCloneGroupName( 
    vfsInfo 		*info 
    );

vfsPath *vfsGetLinkContents( 
    const vfsPath 	*path 
    );

vbool vfsAccess( 
    const vfsPath       *path, 
    int 		 accessMode 
    );

void vfsChangeOwner( 
    const vfsPath	*path, 
    vfsUserId		 userId 
    );

void vfsChangeGroup( 
    const vfsPath	*path, 
    vfsGroupId		 groupId 
    );

void vfsChangeMode( 
    const vfsPath	*path, 
    vfsMode 		 mode
    );

vchar	*vfsGenerateTempName( 
    vchar 		*templateString
    );

void vfsCreateFile( 
    const vfsPath 	*path, 
    vfsMode 		 mode
    );

vfsFile *vfsCreateFileObject(
    void
    );

vfsFile	*vfsOpenFile( 
    const vfsPath 	*fileName, 
    int 		 accessType 
    );

void vfsOpenFileStream( 
    vfsFile		*file,
    const vfsPath 	*fileName, 
    int 		 accessType 
    );

vbool vfsIsFileStreamOpen(
    const vfsFile	*file
    );

vfsFile	*vfsOpenFileLocalized( 
    const vfsPath 	*fileName, 
    int 		 accessType 
    );

vfsFileType vfsGetFileType(
    const vfsPath	*path
    );

void vfsSetFileType(
    const vfsPath	*path,
    vfsFileType		 type
    );

vfsPath *vfsPathFromFile( 
    vfsFile 		*file 
    );

void vfsTruncateOpenFile( 
    vfsFile 		*file 
    );

void vfsAllowCachingForFile(
    vfsFile 		*file, 
    vbool 		 allowCaching
    );

int vfsGetNumOpenFiles(
    void
    );

int vfsGetNumReservedFileChannels(
    void
    );

int vfsGetNumAvailableFileChannels(
    void
    );

void vfsReserveFileChannels(
    int 		 numChannels
    );

void vfsSurrenderFileChannels(
    int 		 numChannels
    );

void vfsCloseFile( 
    vfsFile 		*file
    );

void vfsCloseFileStream( 
    vfsFile 		*file
    );

void vfsDestroyFileObject( 
    vfsFile 		*file
    );

void vfsFlushFileBuffer( 
    vfsFile 		*file 
    );

int vfsGetFileRefNum( 
    vfsFile 		*file 
    );

FILE *vfsGetFilePtr( 
    vfsFile 		*file 
    );

vbool vfsLockFile( 
    vfsFile 		*file
    );

void vfsUnlockFile( 
    vfsFile 		*file 
    );

vbool vfsIsFileLocked( 
    vfsFile 		*file 
    );

vbool vfsLockFileRange( 
    vfsFile 		*file, 
    long 		 offset, 
    long 		 numBytes 
    );

void vfsUnlockFileRange(
    vfsFile 		*file, 
    long 		 offset, 
    long 		 numBytes 
    );

vbool vfsIsFileRangeLocked( 
    vfsFile 		*file, 
    long 		 offset, 
    long 		 numBytes 
    );

vfsType vfsGetFileAccessType( 
    vfsFile	       *file
    );

vbool vfsIsFileOpen( 
    vfsPath 		*path,
    vfsFile	       **file
    );

long vfsRawReadFile( 
    vbyte 		*buffer, 
    long 		 size, 
    vfsFile 		*file 
    );

long vfsRawWriteFile( 
    vbyte 		*buffer, 
    long 		 size, 
    vfsFile 		*file 
    );

long vfsReadFile( 
    vbyte 		*ptr, 
    long 		 size, 
    long 		 nitems, 
    vfsFile 	 	*file 
    );

void vfsWriteFile( 
    vbyte 		*ptr, 
    long 	 	 size, 
    long 		 nitems, 
    vfsFile 		*file 
    );

vbool vfsGetChar(
    vchar 		*c, 
    vfsFile 		*file
    );

vchar vfsPutChar( 
    vchar 		 c, 
    vfsFile 		*file
    );

vchar *vfsReadString(
    vchar		*buffer,
    int			 bufSize,
    vfsFile		*file
    );

void vfsWriteStringScribed(
    vscribe		*stringScribe,
    vfsFile		*file
    );

void vfsWriteString(
    const vchar		*buffer, 
    vfsFile 		*file
    );

void vfsPrintF(
    vfsFile		*file,
    const char		*formatLiteral,
    ...
    );

void vfsSeekFile(
    vfsFile 		*file, 
    long 		 offset, 
    int 		 from 
    );

void  vfsTruncateFile(
    vfsFile		*file,
    long		 size
    );

vfsPath *vfsCreateRelativePath(
    const vfsPath	*fromPath,
    const vfsPath	*toPath
    );

vfsPath *vfsBuildPathScribed( 
    vfsType 		 type, 
    vscribe		*scribe,
    ... 
    );

vfsPath *vfsBuildPath ( 
    vfsType 		 type, 
    const vchar		*element,
    ... 
    );

vfsPath *vfsCreateRootPath (
    void
    );

void vfsTruncatePath ( 
    vfsPath 		*path, 
    int 		 elements 
    );

const vchar *vfsGetParentPathElementString(
    void
    );

vstr *vfsCloneParentPathElementString(
    void
    );

const vchar *vfsGetCurrentPathElementString(
    void
    );

vstr *vfsCloneCurrentPathElementString(
    void
    );

const vchar *vfsGetPathSeparatorString(
    void
    );

vstr *vfsClonePathSeparatorString(
    void
    );

const vchar *vfsGetRootVolumeElementString(
    void
    );

vstr *vfsCloneRootVolumeElementString(
    void
    );

const vchar *vfsGetVolumeSeparatorString(
    void
    );

vstr *vfsCloneVolumeSeparatorString(
    void
    );

/*---------------------------------------------------------------------
 *  Functions--mapped to macros--to retrieve information contained 
 *  in file status
 */
vfsGroupId     	 vfsGetGroupId(vfsInfo *info);
vfsUserId	 vfsGetUserId(vfsInfo *info);
long		 vfsGetSize(vfsInfo *info);
vfsMode	 	 vfsGetMode(vfsInfo *info);
vtimestamp	 vfsGetModificationTime(vfsInfo *info);
vtimestamp	 vfsGetCreationTime(vfsInfo *info);
vbool		 vfsIsHidden(vfsInfo *info);
vbool		 vfsIsArchive(vfsInfo *info);	/* DOS only.		*/
vbool		 vfsIsSystem(vfsInfo *info);	/* DOS/Mac only.	*/
vbool		 vfsSupportsFileTyping(vfsInfo *info); /* Mac only.	*/
vbool		 vfsIsAsciiText(vfsInfo *info);        /* Mac only.	*/
vbool		 vfsIsExecutable(vfsInfo *info);       /* Mac only.	*/
vbool		 vfsIsLink(vfsInfo *info);
vbool		 vfsIsFile(vfsInfo *info);
vbool		 vfsIsDirectory(vfsInfo *info);
vbool		 vfsIsSpecialFile(vfsInfo *info);
vbool		 vfsIsResolvedFromLink(vfsInfo *info);
/*
 *	File manipulation macro prototyes.
 */
long		vfsGetFilePos(vfsFile *file);
void		vfsRewindFile(vfsFile *file);
/*---------------------------------------------------------------------*/

/*
 * Deprecated Functions:
 */ 

void vfsSetPathVolumeRef( 
    vfsPath 		*path,
    vfsVolumeRef	volRef
    );

/*
 * Private Functions:
 */ 

void _vfsInitVolumeListIterator(
    vfsVolumeListIterator	*iterator
    );

int _vfsNextVolumeListIterator(
    vfsVolumeListIterator	*iterator
    );

void _vfsDestroyVolumeListIterator(
    vfsVolumeListIterator	*iterator
    );

const vfsVolume *_vfsGetVolumeListIteratorVolume(
    vfsVolumeListIterator	*iterator
    );

vinstance *_vfsGetPathInstance(
    vfsPath			*path
    );

vfsPathClass *_vfsGetDefaultPathClass( 
    void
    );

vinstance *_vfsGetVolumeInstance(
    vfsVolume			*volume
    );

vfsVolumeClass *_vfsGetDefaultVolumeClass( 
    void
    );

vinstance *_vfsGetDirInstance(
    vfsDir			*dir
    );

vfsDirClass *_vfsGetDefaultDirClass( 
    void
    );

vinstance *_vfsGetInfoInstance(
    vfsInfo			*info
    );

vfsInfoClass *_vfsGetDefaultInfoClass( 
    void
    );

vinstance *_vfsGetFileInstance(
    vfsFile			*file
    );

vfsFileClass *_vfsGetDefaultFileClass( 
    void
    );

#if vportNEED_MAC_FILESYSTEM
OSErr _vfsMacPathToFSSpec(
    const vfsPath 		*path, 
    FSSpec 			*spec
    );
#endif

#if (vdebugDEBUG)
vfsPath	*_vfsClonePathDebug(
    const vfsPath	*path,
    const char		*module,
    const char		*file,
    const int		 line
    );
#else
vfsPath	*_vfsClonePathNondebug(
    const vfsPath	*path
    );
#endif

/*
 * * * * * * * * * FUNCTIONS DEFINED AS #define MACROS (PRIVATE) * * * * * * * * * *
 */

#define _vfsGetVolumeInstance(v)  vportBASE_OBJECT(v, super)
#define _vfsGetInfoInstance(v)  vportBASE_OBJECT(v, super)
#define _vfsGetPathInstance(v)  vportBASE_OBJECT(v, super)
#define _vfsGetDirInstance(v)  vportBASE_OBJECT(v, super)
#define _vfsGetFileInstance(v)  vportBASE_OBJECT(v, super)

/*
 *  Here for compatibility with previous releases:
 */
#define vfsSetPathVolumeRef(p, v)	(vfsSetPathVolumeReference((p), (v)))

/*
 *  vfsGetGroupId() and vfsGetUserId() will return -1 when 
 *  multi-user access to files/directories is not supported.
 */
#define vfsGetGroupId(Info) 		((Info)->groupid)
#define vfsGetUserId(Info) 		((Info)->userid)

#define vfsGetSize(Info) 		((Info)->size)
/*
 *	vfsGetMode() will return a mode with all permissions set for
 *	operating systems that do not support access permissions.
 */
#define vfsGetMode(Info)		((Info)->mode)
#define vfsGetModificationTime(Info)	((Info)->modTime)
#define vfsGetCreationTime(Info) 	((Info)->createTime)

#define vfsIsFile(Info) \
  (((Info)->fileType & vfsFILE) != 0)
#define vfsIsDirectory(Info) \
  (((Info)->fileType & vfsDIR) != 0)
#define vfsIsSpecialFile(Info) \
  (((Info)->fileType & vfsSPECIAL) != 0)
#define vfsIsLink(Info) \
  (((Info)->fileType & vfsLINK) != 0)
#define vfsIsResolvedFromLink(Info) \
  (((Info)->fileType & vfsRESOLVED_FROM_LINK) != 0)
#define vfsIsHidden(Info) \
  (((Info)->fileType & vfsHIDDEN) != 0)

/*
 * Matching call to vfsCreateFileObject(), takes the liberty of
 * freeing any allocated system resources if not already done.
 */
#define vfsDestroyFileObject(f) vfsCloseFile(f)

/* 
 *  Only useful under DOS.
 */
#define vfsIsArchive(Info) \
  (((Info)->fileType & vfsARCHIVE) != 0)
/* 
 *  Only useful under DOS/Mac
 */
#define vfsIsSystem(Info) \
  (((Info)->fileType & vfsSYSTEM) != 0 )

/*
 * Only useful under systems supporting filetyping (Mac)
 */
#define vfsSupportsFileTyping(Info) \
  (((Info)->fileType & vfsEXTRA_FILETYPING) != 0)
#define vfsIsAsciiText(Info) \
  (vfsSupportsFileTyping(Info) && ((Info)->systemFileType & vfsFILETYPE_ASCII_TEXT)!=0)
#define vfsIsExecutable(Info) \
  (vfsSupportsFileTyping(Info) && ((Info)->systemFileType & vfsFILETYPE_EXECUTABLE)!=0)


#if (!vportCPLUSPLUS_SOURCE)

#define vfsDestroyVolumeIterator(i)	(*(i) = NULL)
#define vfsGetVolumeIteratorVolume(i)	((i)->volume)

#endif /* (!vportCPLUSPLUS_SOURCE) */

#define _vfsDestroyVolumeListIterator(i)	((i)->list = NULL)
#define _vfsGetVolumeListIteratorVolume(i)	((i)->list->volume)

#define vfsGetVolumeReference(v)	((v)->volumeRef)
#define vfsGetVolumeName(v)		((v)->volumeName)

#if (!vportNEED_MAC_FILESYSTEM)
#define vfsGetFilePos(f) \
  ((f)->filePtr == NULL ? (f)->offset : ftell((f)->filePtr))
#endif
#define vfsRewindFile(f) \
  ((vfsSeekFile(f, 0, vfsSEEK_FROM_START)))

#define vfsLockFile(f)			(vfsLockFileRange(f, 0, 0))
#define vfsUnlockFile(f)		(vfsUnlockFileRange(f, 0, 0))
#define vfsGetFileAccessType(f)      	((f)->mode & vfsALL_OPEN_MODES)

#define vfsGetPathType(p)		(((p)->type) & vfsALL_PATH_TYPES)
#define vfsIsPathEqual(p1, p2)		(vfsComparePath(p1, p2) == 0)
#define vfsCreateRootPath()		(vfsBuildPath(vfsPATH_TYPE_FULL, NULL))

#if (vdebugDEBUG)
#define vfsClonePath(p)	   _vfsClonePathDebug(p, vdebugTAG, __FILE__, __LINE__)
#else
#define vfsClonePath(p)	   _vfsClonePathNondebug(p)
#endif

/*
 *	Define functions to return the  highest level exception of 
 *	a given type.
 */
#define vfsGetException()	\
((vfsException *) vexGetExceptionOfClass(&_vfsExceptionClass))

/*
 *	I/O exceptions
 */
#define vfsGetIOException()	\
((vfsIOException *) vexGetExceptionOfClass(&_vfsIOExceptionClass))
#define	vfsGetReadException()	\
((vfsReadException *) vexGetExceptionOfClass(&_vfsReadExceptionClass))
#define	vfsGetWriteException()	\
((vfsWriteException *) vexGetExceptionOfClass(&_vfsWriteExceptionClass))
#define	vfsGetReadOnlyException()	\
((vfsReadOnlyException *) vexGetExceptionOfClass(&_vfsReadOnlyExceptionClass))
#define	vfsGetFileSeekException()	\
((vfsFileSeekException *) vexGetExceptionOfClass(&_vfsFileSeekExceptionClass))
#define	vfsGetLockException()	\
((vfsLockException *) vexGetExceptionOfClass(&_vfsLockExceptionClass))
/*
 *	Name exceptions
 */
#define vfsGetNameException()	\
((vfsNameException *) vexGetExceptionOfClass(&_vfsNameExceptionClass))
#define	vfsGetDirNameException()	\
((vfsDirNameException *) vexGetExceptionOfClass(&_vfsDirNameExceptionClass))
#define	vfsGetFileNameException()	\
((vfsFileNameException *) vexGetExceptionOfClass(&_vfsFileNameExceptionClass))
/*
 *	System exceptions
 */
#define vfsGetSystemException()	\
((vfsSystemException *) vexGetExceptionOfClass(&_vfsSystemExceptionClass))
#define	vfsGetInterruptException()	\
((vfsInterruptException *) vexGetExceptionOfClass(&_vfsInterruptExceptionClass))
#define	vfsGetSystemMaxException()	\
((vfsSystemMaxException *) vexGetExceptionOfClass(&_vfsSystemMaxExceptionClass))
#define	vfsGetNoSpaceException()	\
((vfsNoSpaceException *) vexGetExceptionOfClass(&_vfsNoSpaceExceptionClass))
#define	vfsGetNoMemoryException()	\
((vfsNoMemoryException *) vexGetExceptionOfClass(&_vfsNoMemoryExceptionClass))
#define	vfsGetMaxFilesException()	\
((vfsMaxFilesException *) vexGetExceptionOfClass(&_vfsMaxFilesExceptionClass))
#define	vfsGetMaxPathException()	\
((vfsMaxPathException *) vexGetExceptionOfClass(&_vfsMaxPathExceptionClass))
#define	vfsGetMaxNameException()	\
((vfsMaxNameException *) vexGetExceptionOfClass(&_vfsMaxNameExceptionClass))
#define	vfsGetMaxLinksException()	\
((vfsMaxLinksException *) vexGetExceptionOfClass(&_vfsMaxLinksExceptionClass))
#define	vfsGetMaxLocksException()	\
((vfsMaxLocksException *) vexGetExceptionOfClass(&_vfsMaxLocksExceptionClass))
/*
 *	Request exceptions
 */
#define vfsGetRequestException()	\
((vfsRequestException *) vexGetExceptionOfClass(&_vfsRequestExceptionClass))
#define	vfsGetIsDirException()	\
((vfsIsDirException *) vexGetExceptionOfClass(&_vfsIsDirExceptionClass))
#define vfsGetAccessException()	\
((vfsAccessException *) vexGetExceptionOfClass(&_vfsAccessExceptionClass))
#define vfsGetExistsException()	\
((vfsExistsException *) vexGetExceptionOfClass(&_vfsExistsExceptionClass))
#define vfsGetNotEmptyException()	\
((vfsNotEmptyException *) vexGetExceptionOfClass(&_vfsNotEmptyExceptionClass))

/*
 *	Define exception class retrieval functions.
 */
#define vfsGetExceptionClass() 		(&_vfsExceptionClass)

#define vfsGetIOExceptionClass()	  (&_vfsIOExceptionClass)
#define vfsGetReadExceptionClass()	     (&_vfsReadExceptionClass)
#define vfsGetWriteExceptionClass()	     (&_vfsWriteExceptionClass)
#define vfsGetReadOnlyExceptionClass()	     (&_vfsReadOnlyExceptionClass)
#define vfsGetFileSeekExceptionClass()	     (&_vfsFileSeekExceptionClass)
#define vfsGetLockExceptionClass()	     (&_vfsLockExceptionClass)

#define vfsGetNameExceptionClass()	  (&_vfsNameExceptionClass)
#define vfsGetDirNameExceptionClass()	     (&_vfsDirNameExceptionClass)
#define vfsGetFileNameExceptionClass()	     (&_vfsFileNameExceptionClass)

#define vfsGetSystemExceptionClass()	  (&_vfsSystemExceptionClass)
#define vfsGetInterruptExceptionClass()      (&_vfsInterruptExceptionClass)
#define vfsGetSystemMaxExceptionClass()	     (&_vfsSystemMaxExceptionClass)
#define vfsGetNoSpaceExceptionClass()	        (&_vfsNoSpaceExceptionClass)
#define vfsGetNoMemoryExceptionClass()	        (&_vfsNoMemoryExceptionClass)
#define vfsGetMaxFilesExceptionClass()	        (&_vfsMaxFilesExceptionClass)
#define vfsGetMaxPathExceptionClass()	        (&_vfsMaxPathExceptionClass)
#define vfsGetMaxNameExceptionClass()	        (&_vfsMaxNameExceptionClass)
#define vfsGetMaxLinksExceptionClass()          (&_vfsMaxLinksExceptionClass)
#define vfsGetMaxLocksExceptionClass()          (&_vfsMaxLocksExceptionClass)

#define vfsGetRequestExceptionClass()	  (&_vfsRequestExceptionClass)
#define vfsGetIsDirExceptionClass()	     (&_vfsIsDirExceptionClass)
#define vfsGetAccessExceptionClass()	     (&_vfsAccessExceptionClass)
#define vfsGetExistsExceptionClass()	     (&_vfsExistsExceptionClass)
#define vfsGetNotEmptyExceptionClass()	     (&_vfsNotEmptyExceptionClass)


#if vportNEED_MAC_FILESYSTEM

vfsPath *_vfsCreatePathFromMacRefAndID(
    int 		refNum,
    long 		dirID
    );
    
void _vfsSetFileCreator(
    const vfsPath 	*fileName, 
    const void 		*type
    );
    
void _vfsSetFileOSType(
    const vfsPath 	*fileName, 
    const void 		*type
    );

#define vfsSetMacFileCreator(_fn, _t) 	_vfsSetFileCreator(_fn, _t)
#define vfsSetMacFileType(_fn, _t)    	_vfsSetFileOSType(_fn, _t)

#endif


vportEND_CPLUSPLUS_EXTERN_C
#endif


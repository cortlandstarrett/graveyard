/* $Id: vunistd.h,v 1.43 1997/08/27 20:38:36 lis Exp $ */

#ifndef vunistdINCLUDED
#define vunistdINCLUDED 1

/*
	+---------------------------------------------------------------+
	|								|
	|	     vunistd.h - Visix UniStd Header			|
	|								|
	+---------------------------------------------------------------+
	|								|
	| (c) Copyright 1991, Visix Software, Inc., All rights reserved.|
	|								|
	+---------------------------------------------------------------+
	|								|
	|			   DESCRIPTION				|
	|			   ===========				|
	|								|
	|	This file is intended to replace unistd.h with		|
	|	the "Right Thing" as defined by POSIX.			|
	|								|
	+---------------------------------------------------------------+
*/


/*
 * Include any files this header depends upon
 */

#ifndef  vportINCLUDED		/* for v*HEADER */
#include <vport.h>
#endif

#ifndef  vsystypesINCLUDED	/* for ssize_t */
#include vsystypesHEADER
#endif

#ifndef  vsysfileINCLUDED	/* for L_SET */
#include vsysfileHEADER
#endif

#ifndef  vsysstatINCLUDED	/* to reduce inclusion depth */
#include vsysstatHEADER
#endif

#ifndef  vlibcINCLUDED		/* some systems have a generic libc */
#include vlibcHEADER
#endif

#ifndef  vioINCLUDED		/* some systems have a generic io header */
#include vioHEADER
#endif


/*
 * Include the system version of unistd.h, if its not too bad
 */

vportBEGIN_CPLUSPLUS_HEADER_PROTECTION

#if (!vportBAD_UNISTD_HDR)
#include <unistd.h>
#endif


/*
 * Fix up anything that may have been wrong with the system version of unistd.h
 */

#ifndef FIONREAD
#if (!vportBAD_SYS_IOCTL_HDR)	/* BSD location of FIONREAD */
#include <sys/ioctl.h>
#endif
#ifndef FIONREAD
#if (!vportBAD_SYS_TERMIO_HDR)	/* Sys V location of FIONREAD */
#include <sys/termio.h>
#endif
#ifndef FIONREAD
#if (!vportBAD_SYS_FILIO_HDR)	/* alternate Sys V location of FIONREAD */
#include <sys/filio.h>
#endif
#endif
#endif
#endif

#if (vportNEED_UNIXLIB_HDR)
#include <unixlib.h>            /* alot of unistd.h stuff is here on VMS */
#endif

vportEND_CPLUSPLUS_HEADER_PROTECTION


/* Symbolic constants for the "access" function: */

#ifndef  R_OK
#ifndef  vfcntlINCLUDED		/* some systems put *_OK in fcntl.h */
#include vfcntlHEADER
#endif
#endif

#ifndef R_OK
#define R_OK	04			/* Test for Read permission	*/
#endif
#ifndef W_OK
#define W_OK	02			/* Test for Write permission	*/
#endif
#ifndef X_OK
#define X_OK	01			/* Test for eXecute permission	*/
#endif
#ifndef F_OK
#define F_OK	00			/* Test for existence of File	*/
#endif

#ifndef  NULL
#ifndef  vstdlibINCLUDED	/* some systems put NULL only in stdlib.h */
#include vstdlibHEADER
#endif
#endif

#ifndef NULL
#define	NULL	0
#endif

/* Symbolic constants for the "lockf" function: */

#ifndef F_ULOCK
#define F_ULOCK		0	/* Unlock a previously locked region	    */
#endif
#ifndef F_LOCK
#define F_LOCK		1	/* Lock a region for exclusive use	    */
#endif
#ifndef F_TLOCK
#define F_TLOCK		2	/* Test and lock a region for exclusive use */
#endif
#ifndef F_TEST
#define F_TEST		3	/* Test a region for a previous lock	    */
#endif

/* Symbolic constants for the "lseek" function: */

#ifndef  SEEK_SET
#ifndef  vstdioINCLUDED		/* some systems put SEEK_* in stdio.h */
#include vstdioHEADER
#endif
#endif

/* new style */
#ifndef SEEK_SET	/* Set file pointer to offset */
#ifdef L_SET
#define SEEK_SET	L_SET
#else
#define	SEEK_SET	0
#endif
#endif
#ifndef SEEK_CUR	/* Set file pointer to current plus offset */
#ifdef L_CUR
#define SEEK_CUR	L_CUR
#else
#define	SEEK_CUR	1
#endif
#endif
#ifndef SEEK_END	/* Set file pointer to EOF minus offset */
#ifdef L_END
#define SEEK_END	L_END
#else
#define	SEEK_END	2
#endif
#endif

/* old style */
#ifndef L_SET
#define L_SET		SEEK_SET
#endif
#ifndef L_CUR
#define L_CUR		SEEK_CUR
#endif
#ifndef L_END
#define L_END		SEEK_END
#endif

/* Path Names: */

#ifndef GF_PATH
#define GF_PATH		"/etc/group"	/* Path name of the "group" file     */
#endif
#ifndef PF_PATH
#define PF_PATH		"/etc/passwd"	/* Path name of the "passwd" file    */
#endif
#ifndef IF_PATH
#define IF_PATH		"/usr/include"	/* Path name for the <...> directory */
#endif
#ifndef IN_PATH
#define IN_PATH		"/usr/include"	/* Path name for the <...> directory */
#endif

#if 0
/* POSIX optionals   */
#define _POSIX_JOB_CONTROL	1	/* Job Control Present			*/
#define _POSIX_SAVED_IDS	1	/* Support saved-set-ids feature	*/
#define _POSIX_VERSION		198808L	/* POSIX version			*/
#define _POSIX_CHOWN_RESTRICTED	1	/* chown() restricted to super user	*/
#define _POSIX_NO_TRUNC		1	/* Pathname longer than NAME_MAX err	*/
#define _POSIX_VDISABLE		0	/* termio(s) special character disable	*/
#endif

/* POSIX sysconf() defines */
#ifndef	_SC_ARG_MAX
#define	_SC_ARG_MAX		1
#define	_SC_CHILD_MAX		2
#define	_SC_CLK_TCK		3
#define	_SC_NGROUPS_MAX		4
#define	_SC_OPEN_MAX		5
#define	_SC_JOB_CONTROL		6
#define	_SC_SAVED_IDS		7
#define	_SC_VERSION		8
#endif /* _SC_ARG_MAX */

/* POSIX pathconf() defines */
#ifndef _PC_LINK_MAX
#define	_PC_LINK_MAX		1
#define	_PC_MAX_CANON		2
#define	_PC_MAX_INPUT		3
#define	_PC_NAME_MAX		4
#define	_PC_PATH_MAX		5
#define	_PC_PIPE_BUF		6
#define	_PC_CHOWN_RESTRICTED	7
#define	_PC_NO_TRUNC		8
#define	_PC_VDISABLE		9
#endif /* _PC_LINK_MAX */

vportBEGIN_CPLUSPLUS_EXTERN_C

#if (vportNEED_GETPID_PROTO)
pid_t	 getpid( void );
#endif

#if (vportNEED_RENAME_PROTO)
int	 rename( const char *, const char * );
#endif

#if (vportNEED_CLOSE_PROTO)
int	 close( int );
#endif

#if (vportNEED_READ_PROTO)
ssize_t	 read( int, void *, size_t );
#endif

#if (vportNEED_WRITE_PROTO)
ssize_t	 write( int, const void *, size_t );
#endif

#if (vportNEED_LSEEK_PROTO)
off_t	 lseek( int filedes, off_t offset, int whence );
#endif

#if (vportNEED_GETWD_PROTO)
char	*getwd( char *buf );
#endif

#if (vportNEED_CHDIR_PROTO)
int	 chdir( const char *path );
#endif

#if (vportNEED_RMDIR_PROTO)
int	 rmdir( const char *path );
#endif

#if (vportNEED_LINK_PROTO)
int	 link( const char *path1, const char *path2 );
#endif

#if (vportNEED_UNLINK_PROTO)
int	 unlink( const char *path );
#endif

#if (vportNEED_ACCESS_PROTO)
int	 access( const char *path, int amode );
#endif

#if (vportNEED_CHOWN_PROTO)
int	 chown( const char *path, uid_t owner, gid_t group );
#endif

#if (vportNEED_LOCKF_PROTO)
int	 lockf( int fd, int cmd, long size );
#endif

#if (vportNEED_SYMLINK_PROTO)
int	 symlink( const char *name1, const char *name2 );
#endif

#if (vportNEED_GETUID_PROTO)
uid_t	 getuid( void );
#endif

#if (vportNEED_GETEUID_PROTO)
uid_t	 geteuid( void );
#endif

#if (vportNEED_GETGID_PROTO)
gid_t	 getgid( void );
#endif

#if (vportNEED_GETEGID_PROTO)
gid_t	 getegid( void );
#endif

#if (vportNEED_IOCTL_PROTO)
int	 ioctl( int fd, int request, ... );
#endif

#if (vportNEED_GETCWD_PROTO)
char	*getcwd( char *buf, int size );
#endif

#if (vportNEED_READLINK_PROTO)
int	 readlink( const char *path, void *buf, int bufsizef );
#endif

#if (vportNEED_FTRUNCATE_PROTO)
int	 ftruncate( int fd, off_t length );
#endif

#if (vportBAD_CHOWN)
#define chown(_path,_owner,_group) (errno=0,-1)
#endif

#if (vportBAD_SYMLINK)
#define symlink(_name1,_name2) (errno=0,-1)
#endif

#if (vportBAD_READLINK)
#define readlink(_path,_buf,_bufsiz) (errno=0,-1)
#endif

#if (vportBAD_GETUID)
#define getuid() 0
#endif

#if (vportBAD_GETEUID)
#define geteuid() 0
#endif

#if (vportBAD_GETGID)
#define getgid() 0
#endif

#if (vportBAD_GETEGID)
#define getegid() 0
#endif

#if (vportBAD_LOCKF)
#define lockf(_fd,_func,_size) (errno=0,-1)
#endif

#if (vportBAD_VFORK)
#define vfork() fork()
#endif

#if (vportBAD_FORK)
#define fork() (errno=0,-1)
#endif

#if (vportBAD_READ)
#define read(a,b,c) _read(a,b,c)
#endif

#if (vportBAD_WRITE)
#define write(a,b,c) _write(a,b,c)
#endif

#if (vportBAD_ACCESS)
#define access(a,b) _access(a,b)
#if (vportBAD__ACCESS)
vportLINK int _vcompatAccess( char *__file_spec, int __mode );
#undef access
#define access(a,b) _vcompatAccess(a,b)
#endif
#endif

#if (vportBAD_LSEEK)
#define lseek(a,b,c) _lseek(a,b,c)
#endif

#if (vportBAD_CLOSE)
#define close(a) _close(a)
#endif

#if (vportBAD_CHMOD)
#define chmod(a,b) _chmod(a,b)
#endif

#if (vportBAD_FTRUNCATE)
#if (vportNEED_NOUNDERSCORE_CHSIZE)
#define ftruncate(fd,l) chsize(fd,l)
#else
#define ftruncate(fd,l) _chsize(fd,l)
#endif
#endif


vportEND_CPLUSPLUS_EXTERN_C


/*
 * * * * * * * * * * * * * * * * Miscellaneous * * * * * * * * * * * * * * * *
 */

/*
 * Formatting information for emacs in c-mode
 *
 * Local Variables:
 * c-indent-level:4
 * c-continued-statement-offset:2
 * c-brace-offset:-2
 * c-brace-imaginary-offset:0
 * c-argdecl-indent:4
 * c-label-offset:-2
 * End:
 */


#endif /* #ifndef vunistdINCLUDED */


/* $Id: vsysstat.h,v 1.6 1994/02/19 23:29:16 chad Exp $ */

#ifndef	vsysstatINCLUDED
#define vsysstatINCLUDED 1


/*
 * Include any other files this header depends upon
 */

#ifndef  vportINCLUDED		/* for v*HEADER */
#include <vport.h>
#endif

#ifndef  vsystypesINCLUDED	/* for mode_t */
#include vsystypesHEADER
#endif


/*
 * Include the system version of sys/stat.h, if its not too bad
 */

vportBEGIN_CPLUSPLUS_HEADER_PROTECTION

#if ( ! vportBAD_SYS_STAT_HDR )
#include <sys/stat.h>
#endif

vportEND_CPLUSPLUS_HEADER_PROTECTION


/*
 * Fix up any shortcomings in the included sys/stat.h
 */

#ifndef	_IFBLK
#define	_IFBLK		(0)
#endif

#ifndef	_IFCHR
#define	_IFCHR		(0)
#endif

#ifndef	_IFDIR
#define	_IFDIR		(0)
#endif

#ifndef	_IFIFO
#define	_IFIFO		(0)
#endif

#ifndef	_IFLNK
#define	_IFLNK		(0)
#endif

#ifndef	_IFREG
#define	_IFREG		(0)
#endif

#ifndef	_IFSOCK
#define	_IFSOCK		(0)
#endif

#ifndef _IFMT
#define	_IFMT		(S_IFBLK | S_IFCHR | S_IFDIR | S_IFIFO | S_IFLNK | S_IFREG | S_IFSOCK)
#endif

#ifndef	S_IFBLK
#define	S_IFBLK		_IFBLK
#endif

#ifndef	S_IFCHR
#define	S_IFCHR		_IFCHR
#endif

#ifndef	S_IFDIR
#define	S_IFDIR		_IFDIR
#endif

#ifndef	S_IFIFO
#define	S_IFIFO		_IFIFO
#endif

#ifndef	S_IFLNK
#define	S_IFLNK		_IFLNK
#endif

#ifndef	S_IFREG
#define	S_IFREG		_IFREG
#endif

#ifndef	S_IFSOCK
#define	S_IFSOCK	_IFSOCK
#endif

#ifndef S_IFMT
#define	S_IFMT		_IFMT
#endif

#ifndef S_ISDIR
#if (S_IFDIR)
#define	S_ISDIR(m)	(((m)&S_IFMT) == S_IFDIR)
#else
#define S_ISDIR(m)	(0)
#endif
#endif

#ifndef S_ISFIFO
#if (S_IFIFO)
#define	S_ISFIFO(m)	(((m)&S_IFMT) == S_IFIFO)
#else
#define S_ISFIFO(m)	(0)
#endif
#endif

#ifndef S_ISLNK
#if (S_IFLNK)
#define	S_ISLNK(m)	(((m)&S_IFMT) == S_IFLNK)
#else
#define S_ISLNK(m)	(0)
#endif
#endif

#ifndef S_ISREG
#if (S_IFREG)
#define	S_ISREG(m)	(((m)&S_IFMT) == S_IFREG)
#else
#define S_ISREG(m)	(0)
#endif
#endif

#ifndef S_ISSOCK
#if (S_IFSOCK)
#define	S_ISSOCK(m)	(((m)&S_IFMT) == S_IFSOCK)
#else
#define S_ISSOCK(m)	(0)
#endif
#endif


/*
 * We assume that if one of the following is undefined, then they all are.
 */

#ifndef S_IRUSR
#define S_IRUSR S_IREAD		/* read permission: owner */
#endif
#ifndef S_IWUSR
#define S_IWUSR S_IWRITE	/* write permission: owner */
#endif
#ifndef S_IXUSR
#define S_IXUSR S_IEXEC		/* execute permission: owner */
#endif
#ifndef S_IRWXU
#define S_IRWXU (S_IRUSR|S_IWUSR|S_IXUSR) /* read, write, execute: owner */
#endif
#ifndef S_IRGRP
#define S_IRGRP S_IREAD		/* read permission: group */
#endif
#ifndef S_IWGRP
#define S_IWGRP S_IWRITE	/* write permission: group */
#endif
#ifndef S_IXGRP
#define S_IXGRP S_IEXEC		/* execute permission: group */
#endif
#ifndef S_IRWXG
#define S_IRWXG (S_IRGRP|S_IWGRP|S_IXGRP) /* read, write, execute: group */
#endif
#ifndef S_IROTH
#define S_IROTH S_IREAD		/* read permission: other */
#endif
#ifndef S_IWOTH
#define S_IWOTH S_IWRITE	/* write permission: other */
#endif
#ifndef S_IXOTH
#define S_IXOTH S_IEXEC		/* execute permission: other */
#endif
#ifndef S_IRWXO
#define S_IRWXO (S_IROTH|S_IWOTH|S_IXOTH) /* read, write, execute: other */
#endif

#if (vportBAD_LSTAT)
#define lstat			stat
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C

#if (vportNEED_CHMOD_PROTO)
int	 chmod( const char *path, mode_t mode );
#endif

#if (vportNEED_MKDIR_PROTO)
int	 mkdir( const char *path, mode_t mode );
#endif

#if (vportNEED_STAT_PROTO)
int	 stat( const char *path, struct stat *buf );
#endif

#if (vportNEED_STAT_PROTO)
int	 fstat( int filedes, struct stat *buf );
#endif

#if (vportNEED_LSTAT_PROTO)
int	 lstat( const char *path, struct stat *buf );
#endif


vportEND_CPLUSPLUS_EXTERN_C


#endif /* vsysstatINCLUDED */


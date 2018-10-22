/* $Id: vlimits.h,v 1.25 1997/04/29 22:04:07 alexey Exp $ */

#ifndef vlimitsINCLUDED
#define vlimitsINCLUDED 1


/*
 * Include any other files this header depends upon
 */

#ifndef vportINCLUDED
#include <vport.h>
#endif


/*
 * Include the system version of limits.h, if its not too bad
 */

vportBEGIN_CPLUSPLUS_HEADER_PROTECTION

#if (!vportBAD_LIMITS_HDR)
#include <limits.h>
#endif

vportEND_CPLUSPLUS_HEADER_PROTECTION


/*
 * Fix up anything that may have been wrong
 */

/* some systems put PATH_MAX in unistd.h */
#ifndef  vunistdINCLUDED
#include vunistdHEADER
#endif

/* some systems put PATH_MAX in sys/param.h */
#ifndef  vsysparamINCLUDED
#include vsysparamHEADER
#endif

/* some systems put PATH_MAX in stdio.h */
#ifndef  vstdioINCLUDED
#include vstdioHEADER
#endif

/* some systems put NAME_MAX in direct.h */
#ifndef  vdirentINCLUDED
#include vdirentHEADER
#endif

/* OS/2 puts CCHPATHMAX in a system header */
#if (vportOS_OS2)
# ifndef   vos2INCLUDED
#  include vos2HEADER
# endif
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C

#ifndef CHAR_BIT
#define CHAR_BIT	vportCHAR_BIT
#endif

#ifndef CHAR_MIN
#define CHAR_MIN	0
#endif

#ifndef CHAR_MAX
#define CHAR_MAX	127
#endif

#ifndef SCHAR_MIN
#define SCHAR_MIN	(-128)
#endif

#ifndef SCHAR_MAX
#define SCHAR_MAX	127
#endif

#ifndef UCHAR_MAX
#define UCHAR_MAX	(255U)
#endif

#ifndef SHRT_MIN
#define SHRT_MIN	vportSHRT_MIN
#endif

#ifndef SHRT_MAX
#define SHRT_MAX	vportSHRT_MAX
#endif

#ifndef USHRT_MAX
#define USHRT_MAX	vportUSHRT_MAX
#endif

#ifndef INT_BIT
#define INT_BIT		vportINT_BIT
#endif

#ifndef INT_MIN
#define INT_MIN		vportINT_MIN
#endif

#ifndef INT_MAX
#define INT_MAX		vportINT_MAX
#endif

#if (vportBAD_INT_MIN)
#undef  INT_MIN
#define INT_MIN		_vcompatIntMin
#endif

#ifndef UINT_MAX
#define UINT_MAX	vportUINT_MAX
#endif

#ifndef LONG_BIT
#define LONG_BIT	vportLONG_BIT
#endif

#ifndef LONG_MIN
#define LONG_MIN	vportLONG_MIN
#endif

#if (vportBAD_LONG_MIN)
#undef  LONG_MIN
#define LONG_MIN	_vcompatLongMin
#endif

#ifndef LONG_MAX
#define LONG_MAX	vportLONG_MAX
#endif

#ifndef ULONG_MAX
#define ULONG_MAX	vportULONG_MAX
#endif

#ifndef MB_LEN_MAX
#define	MB_LEN_MAX	1		/* max # of bytes in a multibyte char */
#endif

#ifndef USI_MAX
#define	USI_MAX		UINT_MAX	/* max decimal value of an "unsigned" */
#endif

#if (vportNEED_MAC_FILESYSTEM)
#undef  PATH_MAX
#define PATH_MAX	255
#endif

#if (vportNEED_VMS_FILESYSTEM)
#undef  MAXPATHLEN
#define MAXPATHLEN      255
#endif

#if (vportOS_OS2)
#define PATH_MAX	CCHMAXPATH
#endif

#ifndef PATH_MAX
#ifdef MAXPATHLEN
#define PATH_MAX	MAXPATHLEN
#else
#define PATH_MAX	_POSIX_PATH_MAX
#endif
#endif


/*
 * All POSIX systems must support the following values
 * A system may support less restrictive values
 */

#ifndef _POSIX_ARG_MAX
#define	_POSIX_ARG_MAX		4096
#endif

#ifndef _POSIX_CHILD_MAX
#define	_POSIX_CHILD_MAX	6
#endif

#ifndef	_POSIX_LINK_MAX
#define	_POSIX_LINK_MAX		8
#endif

#ifndef	_POSIX_MAX_CANON
#define	_POSIX_MAX_CANON	255
#endif

#ifndef	_POSIX_MAX_INPUT
#define	_POSIX_MAX_INPUT	255
#endif

#ifndef	_POSIX_NAME_MAX
#define	_POSIX_NAME_MAX		14
#endif

#ifndef	_POSIX_NGROUPS_MAX
#define	_POSIX_NGROUPS_MAX	0
#endif

#ifndef	_POSIX_OPEN_MAX
#define	_POSIX_OPEN_MAX		16
#endif

#ifndef _POSIX_PATH_MAX
#define	_POSIX_PATH_MAX		255
#endif

#ifndef	_POSIX_PIPE_BUF
#define	_POSIX_PIPE_BUF		512
#endif


#if (vportNEED_MAC_FILESYSTEM)
#undef NAME_MAX
#define NAME_MAX		31
#undef OPEN_MAX
#define OPEN_MAX		63
#endif

#if (vportNEED_VMS_FILESYSTEM)
#undef MAXNAMLEN
#define MAXNAMLEN               85
#endif

#ifndef NAME_MAX
#ifdef MAXNAMLEN
#define NAME_MAX MAXNAMLEN
#else
#ifdef _MAX_FNAME
#define NAME_MAX _MAX_FNAME
#else
#define NAME_MAX _POSIX_NAME_MAX
#endif
#endif
#endif

#ifndef OPEN_MAX
/* 
 *	OPEN_MAX is defined by some operating systems.  It is not defined
 *	by SunOS 4.x.x and higher.  Use sysconf(_SC_OPEN_MAX) to obtain
 *	the number on each OS
 *
 *	POSIX "LCD" is 16.
 */
#ifdef FOPEN_MAX
#define OPEN_MAX	FOPEN_MAX
#else
#ifdef NOFILE_IN_U
#define OPEN_MAX	NOFILE_IN_U
#else
#ifdef _POSIX_OPEN_MAX
#define OPEN_MAX	_POSIX_OPEN_MAX
#else
#define OPEN_MAX	16
#endif
#endif
#endif
#endif

/*
 * Miscellaneous values sometimes defined by overachieving limits.h files:
 */

#ifndef NGROUPS_MAX
#ifdef NGROUPS
#define NGROUPS_MAX		NGROUPS
#else
#define	NGROUPS_MAX		16
#endif
#endif


/*
 * Add our own "features"
 */

extern const int	_vcompatIntMin;
extern const long	_vcompatLongMin;


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


#endif /* vlimitsINCLUDED */


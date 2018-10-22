/* $Id: vstring.h,v 1.23 1996/03/22 23:47:38 jim Exp $ */

#ifndef vstringINCLUDED
#define vstringINCLUDED 1

/*
	+---------------------------------------------------------------+
	|								|
	|	     vstring.h - Visix String Header			|
	|								|
	+---------------------------------------------------------------+
	|								|
	| (c) Copyright 1990, Visix Software, Inc., All rights reserved.|
	|								|
	+---------------------------------------------------------------+
	|								|
	|			   DESCRIPTION				|
	|			   ===========				|
	|								|
	|	This file is intended to replace string.h with		|
	|	the "Right Thing".  To use this file, replace any	|
	|	instances of #include <string.h> with			|
	|	#include <vstring.h>.					|
	|								|
	|	This file is meant to conform to the ANSI and POSIX	|
	|	standards for string.h					|
	|								|
	+---------------------------------------------------------------+
*/


/*
 * Include any other files this header depends upon
 */

#ifndef  vportINCLUDED			/* for v*HEADER */
#include <vport.h>
#endif

#ifndef  vstddefINCLUDED		/* for size_t */
#include vstddefHEADER
#endif


/*
 * Include the system version of string.h, if its not too bad
 */

vportBEGIN_CPLUSPLUS_HEADER_PROTECTION

#if ( ! vportBAD_STRING_HDR )
#include <string.h>
#endif


/*
 * Fix up anything that may have been wrong with the included string.h
 */


/*
 * Some systems still define mem*() in memory.h instead of string.h
 */

#if ( vportNEED_MEMORY_HDR )
#include <memory.h>
#endif

vportEND_CPLUSPLUS_HEADER_PROTECTION


vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * We only use ANSI standard str*() and mem*() functions.
 * For systems that don't have them, we define them to reasonable equivalents.
 */

#if ( vportBAD_MEMCMP )
vportLINK int _vcompatMemCmp( const void *, const void *, size_t );
#define memcmp( a, b, size )	_vcompatMemCmp( (a), (b), (size) )
#endif

#if ( vportBAD_MEMCPY )
vportLINK void * _vcompatMemCpy( void *, const void *, size_t );
#define memcpy( a, b, size )	_vcompatMemCpy( (a), (b), (size) )
#endif

#if ( vportBAD_MEMMOVE )
#if vportBAD_BCOPY
vportLINK void * _vcompatMemMove( void *dest, const void *src,
					    size_t len );
#define memmove( a, b, size )	_vcompatMemMove( (a), (b), (size) )
#else
#if vportNEED_BCOPY_PROTO
void bcopy( const void *src, void *dst, int length );
#endif
#define memmove( dst, src, size )	(bcopy( (src), (dst), (size) ), (dst))
#endif
#endif

#if ( vportBAD_MEMSET )
vportLINK void * _vcompatMemSet( void *, int, size_t );
#define memset( a, v, size )	_vcompatMemSet( (a), (v), (size) )
#endif

#if ( vportBAD_STRCHR )
char *index( const char *, int );
char *rindex( const char *, int );
#define strchr			  index
#define strrchr			  rindex
#endif

#if (vportNEED_STRERROR_PROTO)
char *strerror( int errorNumber );
#endif
#if (vportBAD_STRERROR)
#if (vportBAD_SYS_ERRLIST)
#define strerror( errorNumber ) "no message - strerror broken at compile-time"
#else
extern char	*sys_errlist[];
#define strerror( errorNumber ) sys_errlist[errorNumber]
#endif
#endif


#if (vportNEED_STRNCASECMP_PROTO)
int strncasecmp( const char *, const char *, size_t );
#endif
#if (vportNEED_STRCASECMP_PROTO)
int strcasecmp( const char *, const char * );
#endif
#if (vportNEED_STRCAT_PROTO)
char *strcat( char *s1, const char *s2 );
#endif
#if (vportNEED_STRCHR_PROTO)
char *strchr( const char *s, int c );
#endif
#if (vportNEED_STRCMP_PROTO)
int strcmp( const char *s1, const char *s2 );
#endif
#if (vportNEED_STRCPY_PROTO)
char *strcpy( char *s1, const char *s2 );
#endif
#if (vportNEED_STRCSPN_PROTO)
size_t strcspn( const char *s1, const char *s2 );
#endif
#if (vportNEED_STRDUP_PROTO)
char *strdup( char *s1 );
#endif
#if (vportNEED_STRLEN_PROTO)
size_t strlen( const char *s );
#endif
#if (vportNEED_STRNCAT_PROTO)
char *strncat( char *s1, const char *s2, size_t n );
#endif
#if (vportNEED_STRNCMP_PROTO)
int strncmp( const char *s1, const char *s2, size_t n );
#endif
#if (vportNEED_STRNCPY_PROTO)
char *strncpy( char *s1, const char *s2, size_t n );
#endif
#if (vportNEED_STRPBRK_PROTO)
char *strpbrk( const char *s1, const char *s2 );
#endif
#if (vportNEED_STRRCHR_PROTO)
char *strrchr( const char *s, int c );
#endif
#if (vportNEED_STRSPN_PROTO)
size_t strspn( const char *s1, const char *s2 );
#endif
#if (vportNEED_STRSTR_PROTO)
char *strstr( const char *s1, const char *s2 );
#endif
#if (vportNEED_STRTOK_PROTO)
char *strtok( char *s1, const char *s2 );
#endif

#if (vportNEED_MEMMOVE_PROTO)
void *memmove( void *s1, const void *s2, size_t nBytes );
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


#endif /* #ifndef vstringINCLUDED */


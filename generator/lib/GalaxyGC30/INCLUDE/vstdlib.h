/* $Id: vstdlib.h,v 1.43 1997/09/29 22:37:03 jim Exp $ */

#ifndef vstdlibINCLUDED
#define vstdlibINCLUDED 1

/*
	+---------------------------------------------------------------+
	|								|
	|	     vstdlib.h - Visix Stdlib Header			|
	|	     ========================================		|
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
	|	This file is intended to replace stdlib.h with		|
	|	the "Right Thing" as defined by ANSI C.			|
	|								|
	+---------------------------------------------------------------+
*/


/*
 * Include any other files this header depends upon
 */

#ifndef  vportINCLUDED		/* for v*HEADER */
#include <vport.h>
#endif

#ifndef  vstddefINCLUDED	/* for size_t, NULL */
#include vstddefHEADER
#endif

#ifndef  vmathINCLUDED		/* for rand() on some systems */
#include vmathHEADER
#endif

#ifndef  vunistdINCLUDED	/* some systems put exit here */
#include vunistdHEADER
#endif


/*
 * Include the system version of stdlib.h, if its not too bad
 */

vportBEGIN_CPLUSPLUS_HEADER_PROTECTION

#if (! vportBAD_STDLIB_HDR)
#include <stdlib.h>
#endif


/*
 * Fix up anything that may have been wrong with it
 */

#if (vportNEED_MALLOC_HDR)
#include <malloc.h>
#endif

#if (vportNEED_MEMORY_HDR)
#include <memory.h>
#endif

#if (vportNEED_UNIXLIB_HDR)
#include <unixlib.h>           /* most unix stdlib things are here on VMS */
#endif

#if (vportNEED_PROCESS_HDR)
#include <process.h>
#endif

vportEND_CPLUSPLUS_HEADER_PROTECTION

vportBEGIN_CPLUSPLUS_EXTERN_C

#if (vportNEED_DIV_T_TYPE)
typedef struct {
    int		 quotient;
    int		 remainder;
} div_t;
#endif

#if (vportNEED_LDIV_T_TYPE)
typedef struct {
    long	 quotient;
    long	 remainder;
} ldiv_t;
#endif

#if (vportVSTDLIB_USE_CHAR_PTR_INSTEAD_OF_VOID_PTR)
#define _vstdlibVOID		char
#else
#define _vstdlibVOID		void
#endif

#ifndef NULL			/* ANSI defines NULL in several files */
#define NULL	(void*)0
#endif

#ifndef EXIT_FAILURE
#define EXIT_FAILURE	(-1)
#endif

#ifndef EXIT_SUCCESS
#define EXIT_SUCCESS	(0)
#endif

#ifndef MB_CUR_MAX
#define MB_CUR_MAX	1		/* max number bytes in char */
#endif

/*
 * Prototypes
 */

#if (vportNEED_ATOF_PROTO)
double		 atof( const char *nptr );
#endif
#if (vportNEED_ATOI_PROTO)
int		 atoi( const char *nptr );
#endif
#if (vportNEED_ATOL_PROTO)
long		 atol( const char *nptr );
#endif
#if (vportNEED_STRTOD_PROTO)
double		 strtod( const char *nptr, char **endptr );
#endif
#if (vportNEED_STRTOL_PROTO)
long		 strtol( const char *nptr, char **endptr, int base );
#endif
#if (vportNEED_STRTOUL_PROTO)
unsigned long	 strtoul( const char *nptr, char **endptr, int base );
#endif

#if (vportNEED_RAND_PROTO)
int		 rand( void );
#endif
#if (vportNEED_SRAND_PROTO)
void		 srand( unsigned int seed );
#endif

#if (vportNEED_MALLOC_PROTO)
_vstdlibVOID	*malloc( size_t size );
#endif
#if (vportNEED_CALLOC_PROTO)
_vstdlibVOID	*calloc( size_t nmemb, size_t size );
#endif
#if (vportNEED_REALLOC_PROTO)
_vstdlibVOID	*realloc( void *ptr, size_t size );
#endif
#if (vportNEED_FREE_PROTO)
void		 free( void *ptr );
#endif

#if (vportNEED_ABORT_PROTO)
void		 abort( void );
#endif
#if (vportNEED_ATEXIT_PROTO)
int		 atexit( void (*)( void ) );
#endif
#if (vportNEED_EXIT_PROTO)
void		 exit( int status );
#endif
#if (vportNEED_GETENV_PROTO)
char		*getenv( const char *name );
#endif
#if (vportNEED_SYSTEM_PROTO)
int		 system( const char *string );
#endif

#if (vportNEED_BSEARCH_PROTO)
_vstdlibVOID	*bsearch( const void *key, const void *base, size_t nmemb, size_t size, int (*compar)( const void *keyval, const void *datum ) );
#endif
#if (vportNEED_QSORT_PROTO)
void		 qsort( void *base, size_t nmemb, size_t size, int (*compar)( const void *keyval, const void *datum ) );
#endif

#if (vportNEED_ABS_PROTO)
int		 abs( int j );
#endif
#if (vportNEED_LABS_PROTO)
long		 labs( long j );
#endif

#if (vportNEED_DIV_PROTO)
div_t		 div( int number, int denom );
#endif
#if (vportNEED_LDIV_PROTO)
ldiv_t		 ldiv( long int number, long int denom );
#endif

#if (vportNEED_MBLEN_PROTO)
int		 mblen( const char *s, size_t n );
int		 mbtowc( wchar_t *pwc, const char *s, size_t n );
int		 wctomb( char *s, wchar_t wchar );
size_t		 mbstowcs( wchar_t *pwcs, const char *s, size_t n );
size_t		 wcstombs( char *s, const wchar_t *pwcs, size_t n );
#endif

#if (vportNEED_ECVT_PROTO || (vportBAD_ECVT_SCOPE && defined(ecvt)))
#if (vportBAD_ECVT_SCOPE && defined(ecvt))
#undef ecvt
#endif
char		*ecvt( double value, int ndigit, int *decpt, int *sign );
#endif

#if (vportBAD_ATEXIT)
vportLINK	void	_vcompatExit( int );
#undef exit
#define exit	_vcompatExit
vportLINK	int	_vcompatAtExit( void (*func)(void) );
#undef atexit
#define atexit	_vcompatAtExit
#endif

#if (vportBROKEN_GETENV)
vportLINK char *      _vcompatGetEnv( char * );
#define getenv(n) _vcompatGetEnv(n)
#endif

#if (vportBAD_RAND_R)
vportLINK int  _vcompatRand_r(unsigned int * );
#define rand_r(__s) _vcompatRand_r(__s)
#endif

#if( vportBAD_ABORT)
#undef abort
#define abort	vcompatAbort
#endif

/*
 * Privately Exported Calls
 */

vportLINK void   _vcompatCallAtExitList( void );
vportLINK void   vcompatAbort( void );
vportLINK void   vcompatAbortWithMessage( char *message );
vportLINK int	 vcompatAborting( void );


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


#endif	/* #ifndef vstdlibINCLUDED */


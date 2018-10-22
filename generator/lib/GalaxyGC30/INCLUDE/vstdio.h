/* $Id: vstdio.h,v 1.52 1997/01/20 23:09:19 jim Exp $ */

#ifndef vstdioINCLUDED
#define vstdioINCLUDED 1

/*
	+---------------------------------------------------------------+
	|								|
	|	     vstdio.h - Visix Stdio Header			|
	|	     ========================================		|
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
	|	This file is intended to supplant stdio.h with		|
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

#ifndef  vstddefINCLUDED	/* for size_t */
#include vstddefHEADER
#endif

#ifndef  vstdargINCLUDED	/* for va_arg() */
#include vstdargHEADER
#endif


/*
 * Include the system version of stdio.h, if its not too bad
 */

vportBEGIN_CPLUSPLUS_HEADER_PROTECTION

#if (! vportBAD_STDIO_HDR)
#include <stdio.h>
#endif

vportEND_CPLUSPLUS_HEADER_PROTECTION


/*
 * Fix up anything that may have been wrong
 */

#ifndef NULL			/* ANSI defines NULL in several places	*/
#define NULL	0
#endif

#ifndef FILENAME_MAX
#define FILENAME_MAX	255
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C

#ifdef fflush
#define __ansi_fflush 47	/* random number - just to get it defined */
#if (fflush == __ansi_fflush)
#define _vstdioFFLUSH_WAS___ANSI_FFLUSH 1
/* undef fflush to allow us to link gcc .o's with sunacc .so's */
#undef fflush
#endif
#undef __ansi_fflush
#endif

#if (vportNEED_FOPEN_PROTO)
FILE	*fopen( const char *filename, const char *mode );
#endif
#if (vportNEED_FREOPEN_PROTO)
FILE	*freopen( const char *filename, const char *mode, FILE *stream );
#endif
#if (vportNEED_FCLOSE_PROTO)
int	 fclose( FILE * );
#endif
#if (vportNEED_FFLUSH_PROTO)
int	 fflush( FILE * );
#endif
#if (vportNEED_FREAD_PROTO)
size_t	 fread( void *, size_t, size_t, FILE * );
#endif
#if (vportNEED_FWRITE_PROTO)
size_t	 fwrite( const void *, size_t, size_t, FILE * );
#endif
#if (vportNEED_FSEEK_PROTO)
int	 fseek( FILE *, long offset, int whence );
#endif
#if (vportNEED_REWIND_PROTO)
void	 rewind( FILE * );
#endif

#if (vportNEED_PRINTF_PROTO)
int	 printf( const char *, ... );
#endif
#if (vportNEED_FPRINTF_PROTO)
int	 fprintf( FILE *, const char *, ... );
#endif
#if (vportNEED_VPRINTF_PROTO)
int	 vprintf( const char *, va_list );
#endif
#if (vportNEED_VFPRINTF_PROTO)
int	 vfprintf( FILE *, const char *, va_list );
#endif

#if (vportNEED_VSPRINTF_PROTO)
int	 vsprintf( char *s, const char *format, va_list arg);
#endif

#if (vportNEED_FSCANF_PROTO)
int	 fscanf( FILE *, const char *format, ... );
#endif
#if (vportNEED_SSCANF_PROTO)
int	 sscanf( const char *, const char *format, ... );
#endif

#if (vportNEED_FGETC_PROTO)
int	 fgetc( FILE *stream );
#endif
#if (vportNEED_UNGETC_PROTO)
int	 ungetc( int c, FILE *stream );
#endif
#if (vportNEED_FPUTC_PROTO)
int	 fputc( int c, FILE *stream );
#endif
#if (vportNEED_FPUTS_PROTO)
int	 fputs( const char *s, FILE *stream );
#endif
#if (vportNEED_PUTC_PROTO)
int	 putc( int c, FILE *stream );
#endif
#if (vportNEED_PUTS_PROTO)
int	 puts( const char *s );
#endif

#if (vportNEED_REMOVE_PROTO)
int      remove( const char *filename );
#endif

#if (vportNEED_PERROR_PROTO)
void	 perror( const char * );
#endif

#if (vportNEED_POPEN_PROTO)
FILE	*popen( const char *command, const char *type );
#endif
#if (vportNEED_PCLOSE_PROTO)
int	 pclose( FILE * );
#endif

#if (vportNEED__FLSBUF_PROTO)
int	 _flsbuf( unsigned, FILE * );
#endif
#if (vportNEED__FILBUF_PROTO)
int	 _filbuf( FILE * );
#endif

#if (vportNEED_FDOPEN_PROTO)
FILE	*fdopen( int filedes, const char *mode );
#endif

vportEND_CPLUSPLUS_EXTERN_C

/* Get vstdioConsoleDriver ouside of the extern "C" block.  Otherwise it'll
 * contain pointers to C functions instead of pointers to the C++ functions
 * we'll be assigning them */

typedef struct vstdioConsoleDriver vstdioConsoleDriver;

struct vstdioConsoleDriver {
    int (*PrintF)(const char *format_string, ...);
    int (*FPrintF)(FILE *stream, const char *format_string, ...);
    int (*VPrintF)(const char *format_string, va_list ap);
    int (*VFPrintF)(FILE *stream, const char *format_string, va_list ap);
    int (*FPutS)(const char *format_string, FILE *stream);
    int (*PutS)(const char *format_string);
    int (*FPutC)(int c, FILE *stream);
    int (*PutChar)(int c);
    int (*Fflush)(FILE *stream);
    size_t (*Fwrite)(const void *bytes, size_t sz, size_t cnt, FILE *stream);
};

vportBEGIN_CPLUSPLUS_EXTERN_C

#if (!vportDONT_INTERCEPT_STDIO)

vportLINK void vstdioCloseConsole(void);

vportLINK vstdioConsoleDriver * _vstdioGetConsoleDriver(void);

#ifdef  printf
#undef  printf
#endif
#define printf			(*_vstdioGetConsoleDriver()->PrintF)

#ifdef  fprintf
#undef  fprintf
#endif
#define fprintf			(*_vstdioGetConsoleDriver()->FPrintF)

#ifdef  vprintf
#undef  vprintf
#endif
#define vprintf(c,l)		(*_vstdioGetConsoleDriver()->VPrintF)(c,l)

#ifdef  vfprintf
#undef  vfprintf
#endif
#define vfprintf(f,c,l)		(*_vstdioGetConsoleDriver()->VFPrintF)(f,c,l)

#ifdef  fputs
#undef  fputs
#endif
#define fputs(s,f)		(*_vstdioGetConsoleDriver()->FPutS)(s,f)

#ifdef  puts
#undef  puts
#endif
#define puts(s)			(*_vstdioGetConsoleDriver()->PutS)(s)

#ifdef  fputc
#undef  fputc
#endif
#define fputc(c,f)		(*_vstdioGetConsoleDriver()->FPutC)(c,f)

#ifdef  putc
#undef  putc
#endif
#define putc(c,f)		(*_vstdioGetConsoleDriver()->FPutC)(c,f)

#ifdef  putchar
#undef  putchar
#endif
#define putchar(c)		(*_vstdioGetConsoleDriver()->PutChar)(c)

#ifdef  fflush
#undef  fflush
#endif
#define fflush(f)		(*_vstdioGetConsoleDriver()->Fflush)(f)

#ifdef  fwrite
#undef  fwrite
#endif
#define fwrite(b,s,c,f)		(*_vstdioGetConsoleDriver()->Fwrite)(b,s,c,f)

#if (vportBAD_STDIO_HANDLES)

vportLINK FILE *	_vstdioGetOut(void);
vportLINK FILE *	_vstdioGetErr(void);

#undef  stdout
#define stdout	_vstdioGetOut()
#undef  stderr
#define stderr	_vstdioGetErr()

#endif

#else /* if (!vportDONT_INTERCEPT_STDIO) */

#define vstdioCloseConsole()	{ ; }

#if (vportVA_LIST_WAS_ARRAY)
#define vprintf(f,ap)		vprintf(f,&(ap))
#define vfprintf(fp,f,ap)	vfprintf(fp,f,&(ap))
#endif

#if (vportUSE_COMMIT_FOR_FFLUSH)
#define	fflush(f)	(_commit(fileno(f)))
#endif

#endif /* if (!vportDONT_INTERCEPT_STDIO) */

#if (vportVA_LIST_WAS_ARRAY)
#define vsprintf(s,f,ap)	vsprintf(s,f,&(ap))
#endif

vportEND_CPLUSPLUS_EXTERN_C


#ifdef  vportNULL_HEADER
#undef  vstdioHEADER
#define vstdioHEADER vportNULL_HEADER
#endif


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


#endif /* #ifndef vstdioINCLUDED */


/* $Id: vsetjmp.h,v 1.6 1994/07/15 23:52:43 chad Exp $ */

#ifndef vsetjmpINCLUDED
#define vsetjmpINCLUDED 1

/*
	+---------------------------------------------------------------+
	|								|
	|	     vsetjmp.h - Visix Setjmp Header			|
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
	|	This file is intended to replace setjmp.h with		|
	|	the "Right Thing", as defined by ANSI C.		|
	|								|
	+---------------------------------------------------------------+
*/


/*
 * Include any other files this header depends upon
 */

#ifndef vportINCLUDED
#include <vport.h>
#endif


/*
 * Include the system version of setjmp.h, if its not too bad
 */

vportBEGIN_CPLUSPLUS_HEADER_PROTECTION

#if ( ! vportBAD_SETJMP_HDR )
#include <setjmp.h>
#endif

vportEND_CPLUSPLUS_HEADER_PROTECTION


/*
 * Fix up anything that may have been wrong
 */

#if (vportBAD_SETJMP_HDR)

/*
 * HP-UX 9.03 C++ A.03.20 has a bad definition of __EH_JMPBUF_TEMP.
 * We substitute our own version instead.
 */

#ifndef _SYS_STDSYMS_INCLUDED
#  include <sys/stdsyms.h>
#endif /* _SYS_STDSYMS_INCLUDED */

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _INCLUDE__STDC__
#  ifdef __hp9000s300
#    define _JBLEN 100
#    define _EHLEN 3
#    define _EHCONTEXT_START _JBLEN
     typedef int jmp_buf[_JBLEN + _EHLEN];
#  endif /* __hp9000s300 */
#  ifdef __hp9000s800
#    define _JBLEN 50
#    define _EHLEN 3
#    define _EHCONTEXT_START _JBLEN/2
     typedef double jmp_buf[_JBLEN/2 + _EHLEN];
#  endif /* _p9000s800 */

#  if defined(__STDC__) || defined(__cplusplus)
     extern int setjmp(jmp_buf);
     extern void longjmp(jmp_buf, int);
#  else /* not __STDC__ || __cplusplus */
     extern int setjmp();
     extern void longjmp();
#  endif /* __STDC__ || __cplusplus */

#if defined(__cplusplus)
extern jmp_buf * __EH_JMPBUF_TEMP;

#define Setjmp(jmpbuf) \
 ( __EH_JMPBUF_TEMP = &(jmpbuf),\
   __eh_save_context(*(jmp_buf*)__EH_JMPBUF_TEMP),\
   setjmp(*__EH_JMPBUF_TEMP))

#define Longjmp(jmpbuf, retval) \
  __EH_JMPBUF_TEMP = &(jmpbuf); \
  __eh_restore_context((*(jmp_buf*) __EH_JMPBUF_TEMP)); \
  longjmp( *__EH_JMPBUF_TEMP, retval); 
#endif /* __cplusplus */
#endif /* _INCLUDE__STDC__ */

#ifdef _INCLUDE_POSIX_SOURCE
#  ifdef __hp9000s800
     typedef double sigjmp_buf[_JBLEN/2];
#  endif /* __hp9000s800 */
#  ifdef __hp9000s300
     typedef int sigjmp_buf[_JBLEN];
#  endif /* __hp9000s300 */

#    if defined(__STDC__) || defined(__cplusplus)
       extern int sigsetjmp(sigjmp_buf, int);
       extern void siglongjmp(sigjmp_buf, int);
#    else /* not __STDC__ || __cplusplus */
       extern int sigsetjmp();
       extern void siglongjmp();
#    endif /* __STDC__ || __cplusplus*/
#endif /* _INCLUDE_POSIX_SOURCE */

#ifdef _INCLUDE_HPUX_SOURCE
#  if defined(__STDC__) || defined(__cplusplus)
     extern int _setjmp(jmp_buf);
     extern void _longjmp(jmp_buf, int);
#  else /* not __STDC__ || __cplusplus */
     extern int _setjmp();
     extern void _longjmp();
#  endif /* __STDC__ || __cplusplus */
#endif /* _INCLUDE_HPUX_SOURCE */

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern void __eh_save_context(jmp_buf);
extern void __eh_restore_context(jmp_buf);
#endif

#endif /* #if (vportBAD_SETJMP_HDR) */


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

#endif /* #ifndef vsetjmpINCLUDED */


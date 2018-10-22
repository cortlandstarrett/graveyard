/* $Id: vsignal.h,v 1.9 1996/01/25 21:59:45 chad Exp $ */

#ifndef	vsignalINCLUDED
#define	vsignalINCLUDED 1


/*
	+---------------------------------------------------------------+
	|								|
	|	     vsignal.h - Visix Signal Header			|
	|	     ========================================		|
	|								|
	+---------------------------------------------------------------+
	|								|
	| (c) Copyright 1993, Visix Software, Inc., All rights reserved.|
	|								|
	+---------------------------------------------------------------+
	|								|
	|			   DESCRIPTION				|
	|			   ===========				|
	|								|
	|	This file is intended to replace signal.h with		|
	|	the "Right Thing", as defined by POSIX.			|
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
 * Include the system version of signal.h, if its not too bad
 */

vportBEGIN_CPLUSPLUS_HEADER_PROTECTION

#if (!defined(__cplusplus) && !vportDONT_MACRO_CPLUSPLUS_KEYWORDS && _AIX)
#undef except
#endif

#if ( ! vportBAD_SIGNAL_HDR )
#include <signal.h>
#endif

#if (!defined(__cplusplus) && !vportDONT_MACRO_CPLUSPLUS_KEYWORDS && _AIX)
#define except vportBREAK_except
#endif

vportEND_CPLUSPLUS_HEADER_PROTECTION


/*
 * Fix up anything that may have been wrong
 */

vportBEGIN_CPLUSPLUS_EXTERN_C


/*
 * signal() args & returns
 */

#ifndef SIG_ERR
#define	SIG_ERR		(vportSIG_PF_CAST -1)
#endif

#ifndef	SIG_DFL
#define	SIG_DFL		(vportSIG_PF_CAST 0)
#endif

#ifndef	SIG_IGN
#define	SIG_IGN		(vportSIG_PF_CAST 1)
#endif

#ifndef	SIG_HOLD
#define	SIG_HOLD	(vportSIG_PF_CAST 3)
#endif


/*
 * sigprocmask flags
 */

#ifndef	SIG_BLOCK
#define	SIG_BLOCK		0x0001
#endif

#ifndef	SIG_UNBLOCK
#define	SIG_UNBLOCK		0x0002
#endif

#ifndef	SIG_SETMASK
#define	SIG_SETMASK		0x0004
#endif


/*
 * Max number of signals
 */

#ifndef _NSIG
#ifdef NSIG
#define _NSIG NSIG
#else
#define _NSIG 31
#endif
#endif


/*
 * sa_flags flag
 */

#ifndef SA_NOCLDSTOP
#define	SA_NOCLDSTOP	0x0008	/* don't send a SIGCHLD on child stop */
#endif


#if (vportNEED_SIGSET_TYPE)
typedef unsigned long sigset_t;
#endif

#if (vportNEED_SIGACTION_TYPE)
typedef struct sigaction {
	void 		(*sa_handler)();
	sigset_t	sa_mask;
	int		sa_flags;
} sigaction;
#endif

#if 0
void	(*signal(int sig, void (*handler)(int)))();
int	raise( int sig );
int	kill( pid_t p, int sig );
int	sigaction( int signo, sigaction *act, sigaction *oldact );
int	sigaddset( sigset_t *mask, int signo );
int	sigdelset( sigset_t *mask, int signo );
int	sigemptyset( sigset_t *mask );
int	sigfillset( sigset_t *mask );
int	sigismember( sigset_t *mask, int signo );
int	sigpending( sigset_t *set );
int	sigprocmask( int how, sigset_t *set, *oldset );
int	sigsuspend( sigset_t *mask );
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

#endif /* #ifndef vsignalINCLUDED */


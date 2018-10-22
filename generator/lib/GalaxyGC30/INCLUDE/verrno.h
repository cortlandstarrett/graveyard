/* $Id: verrno.h,v 1.6 1992/05/18 18:30:50 chad Exp $ */

#ifndef verrnoINCLUDED
#define verrnoINCLUDED 1


/*
 * Include any other files this header depends upon
 */

#ifndef vportINCLUDED
#include <vport.h>
#endif


/*
 * Include the system version of errno.h, if its not too bad
 */

vportBEGIN_CPLUSPLUS_HEADER_PROTECTION

#if (! vportBAD_ERRNO_HDR)
#include <errno.h>
#endif

vportEND_CPLUSPLUS_HEADER_PROTECTION


/*
 * Fix up anything that may have been wrong with the system version of errno.h
 */

vportBEGIN_CPLUSPLUS_EXTERN_C

#if (vportNEED_ERRNO_DECLARATION)
#ifndef errno
extern volatile int	 errno;
#endif
#endif

#if (verrnoGUESS_UNDEFINED_ERRNOS)

#ifndef EPERM
#define	EPERM	1	/* Not super-user			*/
#endif

#ifndef	ENOENT
#define	ENOENT	2	/* No such file or directory		*/
#endif

#ifndef	ESRCH
#define	ESRCH	3	/* No such process			*/
#endif

#ifndef	EINTR
#define	EINTR	4	/* interrupted system call		*/
#endif

#ifndef	EIO
#define	EIO	5	/* I/O error				*/
#endif

#ifndef	ENXIO
#define	ENXIO	6	/* No such device or address		*/
#endif

#ifndef	E2BIG
#define	E2BIG	7	/* Arg list too long			*/
#endif

#ifndef	ENOEXEC
#define	ENOEXEC	8	/* Exec format error			*/
#endif

#ifndef	EBADF
#define	EBADF	9	/* Bad file number			*/
#endif

#ifndef	ECHILD
#define	ECHILD	10	/* No children				*/
#endif

#ifndef	EAGAIN
#define	EAGAIN	11	/* No more processes			*/
#endif

#ifndef	ENOMEM
#define	ENOMEM	12	/* Not enough core			*/
#endif

#ifndef	EACCES
#define	EACCES	13	/* Permission denied			*/
#endif

#ifndef	EFAULT
#define	EFAULT	14	/* Bad address				*/
#endif

#ifndef	ENOTBLK
#define	ENOTBLK	15	/* Block device required		*/
#endif

#ifndef	EBUSY
#define	EBUSY	16	/* Mount device busy			*/
#endif

#ifndef	EEXIST
#define	EEXIST	17	/* File exists				*/
#endif

#ifndef	EXDEV
#define	EXDEV	18	/* Cross-device link			*/
#endif

#ifndef	ENODEV
#define	ENODEV	19	/* No such device			*/
#endif

#ifndef	ENOTDIR
#define	ENOTDIR	20	/* Not a directory			*/
#endif

#ifndef	EISDIR
#define	EISDIR	21	/* Is a directory			*/
#endif

#ifndef	EINVAL
#define	EINVAL	22	/* Invalid argument			*/
#endif

#ifndef	ENFILE
#define	ENFILE	23	/* File table overflow			*/
#endif

#ifndef	EMFILE
#define	EMFILE	24	/* Too many open files			*/
#endif

#ifndef	ENOTTY
#define	ENOTTY	25	/* Not a typewriter			*/
#endif

#ifndef	ETXTBSY
#define	ETXTBSY	26	/* Text file busy			*/
#endif

#ifndef	EFBIG
#define	EFBIG	27	/* File too large			*/
#endif

#ifndef	ENOSPC
#define	ENOSPC	28	/* No space left on device		*/
#endif

#ifndef	ESPIPE
#define	ESPIPE	29	/* Illegal seek				*/
#endif

#ifndef	EROFS
#define	EROFS	30	/* Read only file system		*/
#endif

#ifndef	EMLINK
#define	EMLINK	31	/* Too many links			*/
#endif

#ifndef	EPIPE
#define	EPIPE	32	/* Broken pipe				*/
#endif

#ifndef	EDOM
#define	EDOM	33	/* Math arg out of domain of func	*/
#endif

#ifndef	ERANGE
#define	ERANGE	34	/* Math result not representable	*/
#endif

#ifndef	ENOMSG
#define	ENOMSG	35	/* No message of desired type		*/
#endif

#ifndef	EIDRM
#define	EIDRM	36	/* Identifier removed			*/
#endif

#ifndef	ECHRNG
#define	ECHRNG	37	/* Channel number out of range		*/
#endif

#ifndef	EL2NSYNC
#define	EL2NSYNC 38	/* Level 2 not synchronized		*/
#endif

#ifndef	EL3HLT
#define	EL3HLT	39	/* Level 3 halted			*/
#endif

#ifndef	EL3RST
#define	EL3RST	40	/* Level 3 reset			*/
#endif

#ifndef	ELNRNG
#define	ELNRNG	41	/* Link number out of range		*/
#endif

#ifndef	EUNATCH
#define	EUNATCH 42	/* Protocol driver not attached		*/
#endif

#ifndef	ENOCSI
#define	ENOCSI	43	/* No CSI structure available		*/
#endif

#ifndef	EL2HLT
#define	EL2HLT	44	/* Level 2 halted			*/
#endif

#ifndef	EDEADLK
#define	EDEADLK	45	/* Deadlock condition.			*/
#endif

#ifndef	ENOLCK
#define	ENOLCK	46	/* No record locks available.		*/
#endif


/*
 * Convergent Error Returns
 */

#ifndef EBADE
#define EBADE	50	/* invalid exchange			*/
#endif

#ifndef EBADR
#define EBADR	51	/* invalid request descriptor		*/
#endif

#ifndef EXFULL
#define EXFULL	52	/* exchange full			*/
#endif

#ifndef ENOANO
#define ENOANO	53	/* no anode				*/
#endif

#ifndef EBADRQC
#define EBADRQC	54	/* invalid request code			*/
#endif

#ifndef EBADSLT
#define EBADSLT	55	/* invalid slot				*/
#endif

#ifndef EDEADLOCK
#define EDEADLOCK 56	/* file locking deadlock error		*/
#endif

#ifndef EBFONT
#define EBFONT	57	/* bad font file fmt			*/
#endif


/*
 * stream problems
 */

#ifndef ENOSTR
#define ENOSTR	60	/* Device not a stream			*/
#endif

#ifndef ENODATA
#define ENODATA	61	/* no data (for no delay io)		*/
#endif

#ifndef ETIME
#define ETIME	62	/* timer expired			*/
#endif

#ifndef ENOSR
#define ENOSR	63	/* out of streams resources		*/
#endif

#ifndef ENONET
#define ENONET	64	/* Machine is not on the network	*/
#endif

#ifndef ENOPKG
#define ENOPKG	65	/* Package not installed		*/
#endif

#ifndef EREMOTE
#define EREMOTE	66	/* The object is remote			*/
#endif

#ifndef ENOLINK
#define ENOLINK	67	/* the link has been severed */
#endif

#ifndef EADV
#define EADV	68	/* advertise error */
#endif

#ifndef ESRMNT
#define ESRMNT	69	/* srmount error */
#endif

#ifndef	ECOMM
#define	ECOMM	70	/* Communication error on send		*/
#endif

#ifndef EPROTO
#define EPROTO	71	/* Protocol error			*/
#endif

#ifndef	EMULTIHOP
#define	EMULTIHOP 74	/* multihop attempted */
#endif

#ifndef	ELBIN
#define	ELBIN	75	/* Inode is remote (not really error)*/
#endif

#ifndef	EDOTDOT
#define	EDOTDOT 76	/* Cross mount point (not really error)*/
#endif

#ifndef EBADMSG
#define EBADMSG 77	/* trying to read unreadable message	*/
#endif

#ifndef ENOTUNIQ
#define ENOTUNIQ 80	/* given log. name not unique */
#endif

#ifndef EBADFD
#define EBADFD	 81	/* f.d. invalid for this operation */
#endif

#ifndef EREMCHG
#define EREMCHG	 82	/* Remote address changed */
#endif


/*
 * shared library problems
 */

#ifndef ELIBACC
#define ELIBACC	83	/* Can't access a needed shared lib.	*/
#endif

#ifndef ELIBBAD
#define ELIBBAD	84	/* Accessing a corrupted shared lib.	*/
#endif

#ifndef ELIBSCN
#define ELIBSCN	85	/* .lib section in a.out corrupted.	*/
#endif

#ifndef ELIBMAX
#define ELIBMAX	86	/* Attempting to link in too many libs.	*/
#endif

#ifndef ELIBEXEC
#define ELIBEXEC	87	/* Attempting to exec a shared library.	*/
#endif


/*
 * POSIX compliance
 */

#ifndef ENAMETOOLONG
#define ENAMETOOLONG	88	/* Filename or Pathname too long */
#endif


/*
 *	System V STREAMS TCP
 */
/* Errors from 4.2 BSD picked up to support sockets */
/* Note that the numbers are different from 4.2 numbering */

#ifndef TCPERR
#define TCPERR		90
#endif

/* non-blocking and interrupt i/o */
#ifndef EWOULDBLOCK
#define EWOULDBLOCK	(TCPERR+0)	 /* Operation would block */
#endif

#ifndef EINPROGRESS
#define EINPROGRESS	(TCPERR+1)	 /* Operation now in progress */
#endif

#ifndef EALREADY
#define EALREADY	(TCPERR+2)	 /* Operation already in progress */
#endif

/* ipc/network software */

/* argument errors */
#ifndef ENOTSOCK
#define ENOTSOCK	(TCPERR+3)	 /* Socket operation on non-socket */
#endif

#ifndef EDESTADDRREQ
#define EDESTADDRREQ	(TCPERR+4)	 /* Destination address required */
#endif

#ifndef EMSGSIZE
#define EMSGSIZE	(TCPERR+5)	 /* Message too long */
#endif

#ifndef EPROTOTYPE
#define EPROTOTYPE	(TCPERR+6)	 /* Protocol wrong type for socket */
#endif

#ifndef EPROTONOSUPPORT
#define EPROTONOSUPPORT (TCPERR+7)	 /* Protocol not supported */
#endif

#ifndef ESOCKTNOSUPPORT
#define ESOCKTNOSUPPORT (TCPERR+8)	 /* Socket type not supported */
#endif

#ifndef EOPNOTSUPP
#define EOPNOTSUPP	(TCPERR+9)	 /* Operation not supported on socket */
#endif

#ifndef EPFNOSUPPORT
#define EPFNOSUPPORT	(TCPERR+10)	 /* Protocol family not supported */
#endif

#ifndef EAFNOSUPPORT
#define EAFNOSUPPORT	(TCPERR+11)	 /* Address family not supported by protocol family */
#endif

#ifndef EADDRINUSE
#define EADDRINUSE	(TCPERR+12)	 /* Address already in use */
#endif

#ifndef EADDRNOTAVAIL
#define EADDRNOTAVAIL	(TCPERR+13)	 /* Can't assign requested address */
#endif

/* operational errors */
#ifndef ENETDOWN
#define ENETDOWN	(TCPERR+14)	 /* Network is down */
#endif

#ifndef ENETUNREACH
#define ENETUNREACH	(TCPERR+15)	 /* Network is unreachable */
#endif

#ifndef ENETRESET
#define ENETRESET	(TCPERR+16)	 /* Network dropped connection on reset */
#endif

#ifndef ECONNABORTED
#define ECONNABORTED	(TCPERR+17)	 /* Software caused connection abort */
#endif

#ifndef ECONNRESET
#define ECONNRESET	(TCPERR+18)	 /* Connection reset by peer */
#endif

#ifndef ENOBUFS
#define ENOBUFS		(TCPERR+19)	 /* No buffer space available */
#endif

#ifndef EISCONN
#define EISCONN		(TCPERR+20)	 /* Socket is already connected */
#endif

#ifndef ENOTCONN
#define ENOTCONN	(TCPERR+21)	 /* Socket is not connected */
#endif

#ifndef ESHUTDOWN
#define ESHUTDOWN	(TCPERR+22)	 /* Can't send after socket shutdown */
#endif

#ifndef ETOOMANYREFS
#define ETOOMANYREFS	(TCPERR+23)	 /* Too many references: can't splice */
#endif

#ifndef ETIMEDOUT
#define ETIMEDOUT	(TCPERR+24)	 /* Connection timed out */
#endif

#ifndef ECONNREFUSED
#define ECONNREFUSED	(TCPERR+25)	 /* Connection refused */
#endif

/* should be rearranged */
#ifndef EHOSTDOWN
#define EHOSTDOWN	(TCPERR+26)	 /* Host is down */
#endif

#ifndef EHOSTUNREACH
#define EHOSTUNREACH	(TCPERR+27)	 /* No route to host */
#endif

#ifndef ENOPROTOOPT
#define ENOPROTOOPT	(TCPERR+28)	 /* Protocol not available */
#endif


#endif	/* (verrnoGUESS_UNDEFINED_ERRNOS) */


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

#endif /* verrnoINCLUDED */


/* $Id: vfcntl.h,v 1.12 1994/09/28 03:07:28 abstine Exp $ */

#ifndef vfcntlINCLUDED
#define vfcntlINCLUDED 1


/*
 * Include any other files this header depends upon
 */

#ifndef vportINCLUDED
#include <vport.h>
#endif

#ifndef  vioINCLUDED
#include vioHEADER
#endif

#ifndef  vsystypesINCLUDED
#include vsystypesHEADER
#endif


/*
 * Include the system version of fcntl.h, if its not too bad
 */

vportBEGIN_CPLUSPLUS_HEADER_PROTECTION

#if ( ! vportBAD_FCNTL_HDR )
#include <fcntl.h>
#endif


/*
 * Fix up anything that may have been wrong
 */

#if (vportNEED_SYS_FCNTL_HDR)
#if (!vportBAD_SYS_FCNTL_HDR)
#include <sys/fcntl.h>
#endif
#endif

#if (vportNEED_FCNTLCOM_HDR)
#if (!vportBAD_FCNTLCOM_HDR)
#include <fcntlcom.h>
#endif
#endif

#if (vportNEED_UNIXIO_HDR)
#include <unixio.h>       /* fcntl type things are here on VMS */
#endif

vportEND_CPLUSPLUS_HEADER_PROTECTION

#ifndef _O_BINARY
#define _O_BINARY	0
#endif

#ifndef O_BINARY
#define O_BINARY	_O_BINARY
#endif

#ifndef O_ACCMODE
#define O_ACCMODE	(O_RDONLY|O_WRONLY|O_RDWR)
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C

#if (vportNEED_CREAT_PROTO)
int	 creat( const char *path, mode_t mode );
#endif

#if (vportNEED_FCNTL_PROTO)
int	 fcntl( int filedes, int cmd, ... );
#endif

#if (vportNEED_OPEN_PROTO)
int	 open( const char *path, int oflag, ... );
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

#endif /* vfcntlINCLUDED */


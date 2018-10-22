/* $Id: vnetdb.h,v 1.5 1994/07/30 00:12:14 chad Exp $ */

#ifndef vnetdbINCLUDED
#define vnetdbINCLUDED 1

/*
	+---------------------------------------------------------------+
	|								|
	|	     vnetdb.h - Visix netdb.h Header			|
	|								|
	+---------------------------------------------------------------+
	|								|
	| (c) Copyright 1992, Visix Software, Inc., All rights reserved.|
	|								|
	+---------------------------------------------------------------+
	|								|
	|			   DESCRIPTION				|
	|			   ===========				|
	|								|
	|	This file is intended to replace netdb.h with		|
	|	the "Right Thing" as defined by POSIX.			|
	|								|
	+---------------------------------------------------------------+
*/


/*
 * Include any files this header depends upon
 */

#ifndef  vportINCLUDED
#include <vport.h>
#endif

/* some systems put MAXHOSTNAMELEN in sys/param.h */
#ifndef  vsysparamINCLUDED
#include vsysparamHEADER
#endif

/* some systems put MAXHOSTNAMELEN in types.h */
#ifndef  vsystypesINCLUDED
#include vsystypesHEADER
#endif


/*
 * Include the system version of netdb.h, if its not too bad
 */

vportBEGIN_CPLUSPLUS_HEADER_PROTECTION

#if (!vportBAD_NETDB_HDR)
#include <netdb.h>
#endif

vportEND_CPLUSPLUS_HEADER_PROTECTION


/*
 * Fix up anything that may have been wrong with the system version of netdb.h
 */

vportBEGIN_CPLUSPLUS_EXTERN_C

#ifndef MAXHOSTNAMELEN
#define MAXHOSTNAMELEN 64
#endif

#if (vportNEED_GETSERVBYNAME_PROTO || (vportBAD_GETSERVBYNAME_SCOPE && defined(getservbyname)))
#if (vportBAD_GETSERVBYNAME_SCOPE && defined(getservbyname))
#undef getservbyname
#endif
struct servent		*getservbyname(const char *name, const char *proto);
#endif

#if (vportNEED_GETHOSTBYNAME_PROTO || (vportBAD_GETHOSTBYNAME_SCOPE && defined(gethostbyname)))
#if (vportBAD_GETHOSTBYNAME_SCOPE && defined(gethostbyname))
#undef gethostbyname
#endif
struct hostent		*gethostbyname(const char *name);
#endif

#if (vportNEED_GETHOSTBYADDR_PROTO || (vportBAD_GETHOSTBYADDR_SCOPE && defined(gethostbyaddr)))
#if (vportBAD_GETHOSTBYADDR_SCOPE && defined(gethostbyaddr))
#undef gethostbyaddr
#endif
struct hostent		*gethostbyaddr(const char *addr, int len, int type);
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


#endif /* vnetdbINCLUDED */


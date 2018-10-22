/* $Id: vgrp.h,v 1.16 1996/09/24 14:44:38 scotth Exp $ */

#ifndef vgrpINCLUDED
#define vgrpINCLUDED 1


/*
	+---------------------------------------------------------------+
	|								|
	|	     vgrp.h - Visix Group Header			|
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
	|	This file is intended to replace grp.h with		|
	|	the "Right Thing", as defined by POSIX.			|
	|								|
	+---------------------------------------------------------------+
*/


/*
 * Include any other files this header depends upon
 */

#ifndef vportINCLUDED		/* for v*HEADER */
#include <vport.h>
#endif

#ifndef  vsystypesINCLUDED	/* for gid_t */
#include vsystypesHEADER
#endif

#if (vportREENTRANT)            /* for FILE*, vmutex */

# ifndef  vstdioINCLUDED
# include vstdioHEADER
# endif

# ifndef vmutexINCLUDED
# include vmutexHEADER
# endif

#endif

/*
 * Include the system version of grp.h, if its not too bad
 */

vportBEGIN_CPLUSPLUS_HEADER_PROTECTION

#if ( ! vportBAD_GRP_HDR )
#include <grp.h>
#endif

vportEND_CPLUSPLUS_HEADER_PROTECTION


vportBEGIN_CPLUSPLUS_EXTERN_C


/*
 * Fix up anything that may have been wrong
 */

#if (vportNEED_GROUP_STRUCT)
struct group {
    char	 *gr_name;
    gid_t	  gr_gid;
    char	**gr_mem;
};
#endif

#if (vportNEED_GETGRGID_PROTO)
struct group	*getgrgid( int );
#endif

#if (vportNEED_GETGRGID_R_PROTO)
extern struct group *getgrgid_r(gid_t, struct group *, char *, int);
#endif

#if (vportNEED_ENDGRENT_PROTO)
void		 endgrent( void );
#endif

#if (vportBAD_GETGRGID)
#define getgrgid( _gid )	((struct group *)NULL)
#endif

#if (vportREENTRANT)
# if (vportBAD_GETGRGID_R)
#  if !(vportBAD_GETGRGID)
#   undef getgrgid_r
#   define getgrgid_r _vcompatGetGrGID_r

vportLINK int _vcompatGetGrGID_r(
   gid_t            gid,
   struct group    *grp,
   char            *buffer,
   size_t           len,
   struct group   **result
   );

#  else
#   define getgrgid_r(_gid,_grp,_buf,_sbuf,_pGrp)  (-1)
#  endif
# endif
#endif

#if (vportBAD_ENDGRENT)
#define endgrent()
#endif

/*
 * For Set and End emulation, we basically just want to
 * grab the global lock, let the caller do what it needs to
 * do and then unlock. If everyone plays nice, this should
 * keep multiple threads from stepping on static data inside
 * the platform supplied libc implementation of the group entity
 * functions.
 *
 * NOTE:
 *    Because of the way Set and End are defined, they must be
 *    used in the same function scope!!
 */

#if (vportREENTRANT)
# if (vportBAD_GRENT_R)
#  if !(vportBAD_ENDGRENT)

vportLINK void _vcompatSetGrEnt_r(
   FILE           **pFileP
   );

#   define setgrent_r(__pFp)                             \
        {                                                \
           vmutexLockGlobalWithHandling();               \
           _vcompatSetGrEnt_r(__pFp)

vportLINK void _vcompatEndGrEnt_r(
   FILE           **pFileP
   );

#   define endgrent_r(__pFp)                             \
           _vcompatEndGrEnt_r(__pFp);                    \
           vmutexUnlockGlobalWithHandling();             \
	}

#  else
#   define setgrent_r(_fileP)
#   define endgrent_r(_fileP)
#  endif
# endif
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

#endif /* vgrpINCLUDED */


/* $Id: vpwd.h,v 1.16 1996/07/16 04:48:11 abstine Exp $ */

#ifndef vpwdINCLUDED
#define vpwdINCLUDED 1


/*
 * Include any other files this header depends upon
 */

#ifndef  vportINCLUDED		/* for v*HEADER */
#include <vport.h>
#endif

#ifndef  vsystypesINCLUDED	/* for uid_t, gid_t */
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
 * Include the system version of pwd.h, if its not too bad
 */

vportBEGIN_CPLUSPLUS_HEADER_PROTECTION

#if ( ! vportBAD_PWD_HDR )
#include <pwd.h>
#endif

vportEND_CPLUSPLUS_HEADER_PROTECTION


vportBEGIN_CPLUSPLUS_EXTERN_C


/*
 * Fix up anything that may have been wrong
 */

#if (vportNEED_PASSWD_STRUCT)
struct passwd {
    char	*pw_name, *pw_dir, *pw_shell;
    uid_t	 pw_uid;
    gid_t	 pw_gid;
};
#endif

#if (vportNEED_GETPWUID_PROTO)
struct passwd	*getpwuid( int );
#endif

#if (vportNEED_ENDPWENT_PROTO && !defined(_G_LIB_VERSION))
void		 endpwent( void );
#endif

#if (vportBAD_GETPWUID)
#define getpwuid( _uid )	((struct passwd *)NULL)
#endif

#if (vportREENTRANT)
# if (vportBAD_GETPWUID_R)
#  if !(vportBAD_GETPWUID)
#   undef getpwuid_r
#   define getpwuid_r   _vcompatGetPwUID_r

vportLINK int _vcompatGetPwUID_r(
   uid_t            uid,
   struct passwd   *pwd,
   char            *buffer,
   size_t           len,
   struct passwd  **result
   );

#  else
#   define getpwuid_r(_uid,_pwd,_buf,_sbuf,_pPwd)  (-1)
#  endif
# endif
#endif

#if (vportBAD_ENDPWENT)
#define endpwent()
#endif

/*
 * For Set and End emulation, we basically just want to
 * grab the global lock, let the caller do what it needs to
 * do and then unlock. If everyone plays nice, this should
 * keep multiple threads from stepping on static data inside
 * the platform supplied libc implementation of the passwd entity
 * functions.
 *
 * NOTE:
 *    Because of the way Set and End are defined, they must be
 *    used in the same function scope!!
 */

#if (vportREENTRANT)
# if (vportBAD_PWENT_R)
#  if !(vportBAD_ENDPWENT)

vportLINK void _vcompatSetPwEnt_r(
   FILE           **pFileP
   );

#   define setpwent_r(__pFp)                             \
        {                                                \
           vmutexLockGlobalWithHandling();               \
           _vcompatSetPwEnt_r(__pFp)

vportLINK void _vcompatEndPwEnt_r(
   FILE           **pFileP
   );

#   define endpwent_r(__pFp)                             \
           _vcompatEndPwEnt_r(__pFp);                    \
           vmutexUnlockGlobalWithHandling();             \
	}

#  else
#   define setpwent_r(_fileP)
#   define endpwent_r(_fileP)
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

#endif /* #ifndef vpwdINCLUDED */


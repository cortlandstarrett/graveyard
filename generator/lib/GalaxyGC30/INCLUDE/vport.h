/* $Id: vport.h,v 1.607 1997/10/25 16:15:10 lis Exp $ */

/************************************************************

    vport.h

    C Interface file for the Porting Manager

    (c) Copyright Visix Software Inc.
    All rights reserved

************************************************************/

#ifndef vportINCLUDED
#define vportINCLUDED 1

/*
 * This file contains porting information useful in the internal
 * implementation of Galaxy.  Nothing in this file should be relied
 * upon by code outside Galaxy in any way.  It is not a documented
 * part of the Galaxy API.  Existance of any section of flags in this
 * file in no way implies that we have support for or will try to
 * support any particular platform.
 *
 * This file should consist only of pre-processor flags that are
 * defined as vTRUE or vFALSE or as one of a set of values also
 * defined in this file.
 *
 * As a general rule, when you need a new flag, have the code assume
 * the feature's existance and either don't use it or fix it back up
 * if a BAD_* flag is set.
 */


/*
 * Include the Header Names mapping file for v*HEADER
 */

#ifndef  vhdrdefsINCLUDED
#include <vhdrdefs.h>
#endif


/*
 * Define some commonly used flags
 */

#ifndef vTRUE
#define vTRUE 1
#endif

#ifndef vFALSE
#define vFALSE 0
#endif

/* for backwards compatability */

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif


/*
 * Include the automaticly generated, porting environment file
 */

#if (!(THINK_C || THINK_CPLUS || __MWERKS__ || __SC__ || __PPCC__))

#ifndef  vportenvINCLUDED
#include <vportenv.h>
#endif

#else

#include <vportmac.h>

#endif


/*
 * Define all possible values of the exported flags
 */

#define vportCODESET_ISO_10646          1
#define vportCODESET_LATIN_1            2
#define vportCODESET_MNLS               3
#define vportCODESET_UNICODE            4
#define vportCODESET_ASCII              5
#define vportCODESET_MACINTOSH          6
#define vportCODESET_WINDOWS            7
#define vportCODESET_SJIS               8
#define vportCODESET_JEUC               9
#define vportCODESET_UTF               10

/*
 *  options:    vportNEED_UNIX_FILESYSTEM
 *              vportNEED_DOS_FILESYSTEM
 *              vportNEED_HPFS_FILESYSTEM
 *              vportNEED_VMS_FILESYSTEM
 *              vportNEED_MAC_FILESYSTEM
 */


/*
 * Set some shorthand version macros
 */

#ifndef vportPRE_WIN_X11R3
#define vportPRE_WIN_X11R3      (vportWIN_X11_VERSION && (vportWIN_X11_VERSION < 0x11030000))
#endif

#ifndef vportPRE_WIN_X11R4
#define vportPRE_WIN_X11R4      (vportWIN_X11_VERSION && (vportWIN_X11_VERSION < 0x11040000))
#endif

#ifndef vportPRE_WIN_X11R5
#define vportPRE_WIN_X11R5      (vportWIN_X11_VERSION && (vportWIN_X11_VERSION < 0x11050000))
#endif

#ifndef vportPRE_WIN_X11R6
#define vportPRE_WIN_X11R6      (vportWIN_X11_VERSION && (vportWIN_X11_VERSION < 0x11060000))
#endif

#ifndef vportPRE_ULTRIX_4_0
#define vportPRE_ULTRIX_4_0     (vportULTRIX_VERSION && (vportULTRIX_VERSION < 0x04000000))
#endif

#ifndef vportPRE_ULTRIX_4_1
#define vportPRE_ULTRIX_4_1     (vportULTRIX_VERSION && (vportULTRIX_VERSION < 0x04010000))
#endif

#ifndef vportPRE_ULTRIX_4_2
#define vportPRE_ULTRIX_4_2     (vportULTRIX_VERSION && (vportULTRIX_VERSION < 0x04020000))
#endif

#ifndef vportPRE_SUN_OS_4_0
#define vportPRE_SUN_OS_4_0     (vportSUN_OS_VERSION && (vportSUN_OS_VERSION < 0x04000000))
#endif

#ifndef vportPRE_SUN_OS_4_1
#define vportPRE_SUN_OS_4_1     (vportSUN_OS_VERSION && (vportSUN_OS_VERSION < 0x04010000))
#endif

#ifndef vportPRE_SUN_OS_4_1_1
#define vportPRE_SUN_OS_4_1_1   (vportSUN_OS_VERSION && (vportSUN_OS_VERSION < 0x04010100))
#endif

#ifndef vportPRE_SUN_OS_5_0
#define vportPRE_SUN_OS_5_0     (vportSUN_OS_VERSION && (vportSUN_OS_VERSION < 0x05000000))
#endif

#ifndef vportPRE_RISC_OS_5_0
#define vportPRE_RISC_OS_5_0    (vportRISC_OS_VERSION && (vportRISC_OS_VERSION < 0x05000000))
#endif

#ifndef vportPRE_HPUX_10
#define vportPRE_HPUX_10        (vportHPUX_VERSION && (vportHPUX_VERSION < 0x10000000))
#endif

#ifndef vportPRE_AIX_4
#define vportPRE_AIX_4          (vportAIX_VERSION && (vportAIX_VERSION < 0x04000000))
#endif

#if (vportWIN_X11_VERSION)
#define vportWIN_X11                    vTRUE
#endif
#if (vportWIN_PM_VERSION)
#define vportWIN_PM                     vTRUE
#endif
#if (vportWIN_MS_WINDOWS_VERSION)
#define vportWIN_MS_WINDOWS             vTRUE
#endif
#if (vportWIN_MAC_VERSION)
#define vportWIN_MAC                    vTRUE
#endif


/*
 * vportOS_*
 */

#ifndef vportOS_UNIX
#define vportOS_UNIX                    vportNEED_UNIX_FILESYSTEM
#endif

#ifndef vportOS_WIN32S
#if (defined(WIN32) || defined(_WIN32) || defined(__WIN32__))
#define vportOS_WIN32S                  vTRUE
#endif
#endif

#ifndef vportOS_WINDOWS
#define vportOS_WINDOWS                 vportOS_WIN32S
#endif

#ifndef vportOS_OS2
#define vportOS_OS2                     __OS2__
#endif

#ifndef vportOS_MAC
#define vportOS_MAC                     vportWIN_MAC_VERSION
#endif

#ifndef vportOS_VMS
#define vportOS_VMS                     (__vms || vms || VMS || __VMS)
#endif

/* backward compatability */
#ifndef vportWIN_NT
#define vportWIN_NT                     (vportOS_WIN32S && vportWIN_MS_WINDOWS)
#endif

/* backward compatability */
#ifndef vportWIN32_MSVC
#define vportWIN32_MSVC                 vportOS_WIN32S_MSVC
#endif

/*
 * Instruction Set Architectures
 */

#if (_M_68K || __MC68881__ || __hp9000s300 || GENERATING68K)
#define vportISA_68K                    1
#endif

#if (_M_ALPHA_)
#define vportISA_ALPHA                  1
#endif

#if (__hp9000s700 || __hp9000s800)
#define vportISA_HPPA                   1
#define vportALIGNMENT_INT              (vportINT_BIT/vportCHAR_BIT)
#define vportALIGNMENT_SHORT            (vportSHORT_BIT/vportCHAR_BIT)
#define vportALIGNMENT_BYTES            (vportDOUBLE_BIT/vportCHAR_BIT)
#endif

#if (atari || commodore || appleII)
#define vportISA_M6502                  1
#endif

#if (_M_MRX000 || _MIPS_ISA)
#define vportISA_MIPS                   1
#define vportALIGNMENT_INT              (vportINT_BIT/vportCHAR_BIT)
#define vportALIGNMENT_SHORT            (vportSHORT_BIT/vportCHAR_BIT)
#define vportALIGNMENT_BYTES            (vportDOUBLE_BIT/vportCHAR_BIT)
#endif

#if (_POWER || _IBMR2)
#define vportISA_POWER                  1
#endif

#if (_M_PPC || __MC601 || __powerc || __powerpc || __PPCC__ || GENERATINGPOWERPC)
#define vportISA_PPC                    1
#endif

#if (sparc || __sparc || __sparc__)
#define vportISA_SPARC                  1
#define vportALIGNMENT_INT              (vportINT_BIT/vportCHAR_BIT)
#define vportALIGNMENT_SHORT            (vportSHORT_BIT/vportCHAR_BIT)
#define vportALIGNMENT_BYTES            (vportDOUBLE_BIT/vportCHAR_BIT)
#endif

#if (_I386 || i386 || __i386 || _M_X86 || _M_IX86 || _M_I386 || __THW_INTEL__)
#define vportISA_X86                    1
#define vportALIGNMENT_INT              1
#define vportALIGNMENT_SHORT            1
#endif

/*
 * Galaxy versioning information
 */

#define vportGALAXY_MAJOR_VERSION       3
#define vportGALAXY_MINOR_VERSION       0
#define vportGALAXY_SUB_MINOR_VERSION   0


#ifndef vportDEBUG
# ifdef vdebugDEBUG
#  define vportDEBUG                                    vdebugDEBUG
# else
#  define vportDEBUG                                    vTRUE
# endif
#endif


/*
 * Define environment specific settings for each porting environment
 */

#if (aiws)
#endif

/* AIX 3.2 and 4.1 */
#if (_AIX)      /* all versions of AIX */
#if (vportPRE_AIX_4)    /* versions of AIX strictly below 4.1 */
# ifndef  vportBAD_AIX_UMS
#  define vportBAD_AIX_UMS                              vTRUE
# endif
# define vportBAD_REMAINDER                             vTRUE
# define vportNEED_GETWD_PROTO                          vTRUE
# define vportUSE_DCE_THREADS                           _THREAD_SAFE
# define vportUSE_POSIX_DRAFT4_GETGRGID_R               vTRUE
# define vportUSE_POSIX_DRAFT4_GETPWUID_R               vTRUE
# define vportUSE_POSIX_DRAFT4_RAND_R                   vTRUE
# define vportUSE_POSIX_DRAFT4_READDIR_R                vTRUE
# if (!__cplusplus && !__GNUC__)
#  define vportHAS_LONG_LONG                            vTRUE
# endif /* if (!__cplusplus && !__GNUC__) */
# if __cplusplus
#  define vportNEED_ENDPWENT_PROTO                      vTRUE
#  define vportNEED_GETHOSTNAME_PROTO                   vTRUE
# endif /* if __cplusplus */
#else                   /* versions of AIX at and above 4.1 */
# ifndef vportBAD_AIX_UMS
# define vportBAD_AIX_UMS                               vFALSE
# endif
# define vportDONT_BREAK_EXCEPT                         vTRUE
# define vportHAS_LONG_LONG                             _LONG_LONG
# define vportUSE_POSIX_DRAFT4_GETGRGID_R               vTRUE
# define vportUSE_POSIX_DRAFT4_GETPWUID_R               vTRUE
# define vportUSE_POSIX_DRAFT7_READDIR_R                vTRUE
# define vportUSE_POSIX_DRAFT7_THREADS                  _THREAD_SAFE
#endif          /* if (vportPRE_AIX_4) else */
#define vportALIGNMENT_BYTES   (vportDOUBLE_BIT/vportCHAR_BIT)
#define vportBAD_INFINITY_CONSTANT                      vTRUE
#define vportBAD_LIBC_HDR                               vTRUE
#define vportBAD_NAN_CONSTANT                           vTRUE
#define vportBAD_TM_ZONE                                vTRUE
#define vportBAD_UDP_FIONREAD                           vTRUE
#define vportBAD_UNION_WAIT                             vTRUE
#define vportBAD_VFORK                                  vTRUE
#define vportBAD_X_SHM                                  vTRUE
#define vportDLL_AIX                                    vTRUE
#define vportOS_UNIX_AIX                                vTRUE
#define vportREENTRANT                                  _THREAD_SAFE
#define vportUSE_LONG_LONG                              vportHAS_LONG_LONG
#if (__GNUC__)
# define vportNEED_ACCEPT_PROTO                         vTRUE
# define vportNEED_BIND_PROTO                           vTRUE
# define vportNEED_BZERO_PROTO                          vTRUE
# define vportNEED_CONNECT_PROTO                        vTRUE
# define vportNEED_ENDPWENT_PROTO                       vTRUE
# define vportNEED_GETHOSTNAME_PROTO                    vTRUE
# define vportNEED_GETSOCKNAME_PROTO                    vTRUE
# define vportNEED_GETSOCKOPT_PROTO                     vTRUE
# define vportNEED_GETTIMEOFDAY_PROTO                   vTRUE
# define vportNEED_IOCTL_PROTO                          vTRUE
# define vportNEED_LISTEN_PROTO                         vTRUE
# define vportNEED_LOCKF_PROTO                          vTRUE
# define vportNEED_RANDOM_PROTO                         vTRUE
# define vportNEED_RECVFROM_PROTO                       vTRUE
# define vportNEED_SENDTO_PROTO                         vTRUE
# define vportNEED_SETSOCKOPT_PROTO                     vTRUE
# define vportNEED_SOCKET_PROTO                         vTRUE
# define vportNEED_SRANDOM_PROTO                        vTRUE
#else           /* ! __GNUC__ */
# define vportBAD_SYS_MNTENT_HDR                        vTRUE
# define vportDONT_DEFINE_NULL_HEADER                   vTRUE
# ifdef __cplusplus /* _AIX && ! __GNUC__ && __cplusplus) */
#  define vportBAD_BOOL                                 vTRUE
# endif /* ifdef __cplusplus */
#endif /* if (__GNUC__) else */
#endif /* if (_AIX) */

#if (__alpha && __osf__)
#include <standards.h>
#ifndef vportDU_SOUND
#define vportDU_SOUND                                   vTRUE
#endif
#if (_POSIX_C_SOURCE < 199506L)
# define vportUSE_POSIX_DRAFT4_GETGRGID_R               vTRUE
# define vportUSE_POSIX_DRAFT4_GETPWUID_R               vTRUE
# define vportUSE_POSIX_DRAFT4_READDIR_R                vTRUE
#endif
#define vportBAD_INFINITY_CONSTANT                      vTRUE
#define vportBAD_LIBC_HDR                               vTRUE
#define vportBAD_NAN_CONSTANT                           vTRUE
#define vportBAD_UDP_FIONREAD                           vTRUE
#define vportBAD_UNION_WAIT                             vTRUE
#define vportDLL_DLSYM                                  vTRUE
#define vportDONT_BREAK_INTERFACE                       vTRUE
#define vportNEED_GETHOSTNAME_PROTO                     vTRUE
#define vportNEED_WAIT3_PROTO                           vTRUE
#ifdef __cplusplus
# define vportBAD_BOOL                                  vTRUE
# define vportBAD_ECVT_SCOPE                            vTRUE
# define vportBAD_GETHOSTBYADDR_SCOPE                   vTRUE
# define vportBAD_GETHOSTBYNAME_SCOPE                   vTRUE
# define vportBAD_GETSERVBYNAME_SCOPE                   vTRUE
# define vportBAD_LONG_MIN                              vTRUE
# define vportINLINE_DECL                               inline
# define vportNEED_LOCKF_PROTO                          vTRUE
# define vportNEED_SELECT_PROTO                         vTRUE
#endif
#if (!vportCPLUSPLUS_SOURCE)
# define vportC_STRUCT                                  struct
#endif
#endif

#if (amix)
#endif

#if (apollo)
#endif

#if (ardent)
#endif

/* A/UX */
#if (AUX)
#if (__GNUC__)
#define vportNEED_ACCEPT_PROTO          vTRUE
#define vportNEED_ATOI_PROTO            vTRUE
#define vportNEED_BCOPY_PROTO           vTRUE
#define vportNEED_BIND_PROTO            vTRUE
#define vportNEED_BZERO_PROTO           vTRUE
#define vportNEED_CALLOC_PROTO          vTRUE
#define vportNEED_CLOSE_PROTO           vTRUE
#define vportNEED_CONNECT_PROTO         vTRUE
#define vportNEED_CTIME_PROTO           vTRUE
#define vportNEED_ECVT_PROTO            vTRUE
#define vportNEED_GETDTABLESIZE_PROTO   vTRUE
#define vportNEED_GETHOSTNAME_PROTO     vTRUE
#define vportNEED_GETWD_PROTO           vTRUE
#define vportNEED_GETSOCKNAME_PROTO     vTRUE
#define vportNEED_GETSOCKOPT_PROTO      vTRUE
#define vportNEED_GETTIMEOFDAY_PROTO    vTRUE
#define vportNEED_SYMLINK_PROTO         vTRUE
#define vportNEED_IOCTL_PROTO           vTRUE
#define vportNEED_LSTAT_PROTO           vTRUE
#define vportNEED_ENDPWENT_PROTO        vTRUE
#define vportNEED_ENDGRENT_PROTO        vTRUE
#define vportNEED_READLINK_PROTO        vTRUE
#define vportNEED_RANDOM_PROTO          vTRUE
#define vportNEED_LISTEN_PROTO          vTRUE
#define vportNEED_LOCKF_PROTO           vTRUE
#define vportNEED_RECVFROM_PROTO        vTRUE
#define vportNEED_SELECT_PROTO          vTRUE
#define vportNEED_SENDTO_PROTO          vTRUE
#define vportNEED_SETSOCKOPT_PROTO      vTRUE
#define vportNEED_SHMAT_PROTO           vTRUE
#define vportNEED_SHMCTL_PROTO          vTRUE
#define vportNEED_SHMDT_PROTO           vTRUE
#define vportNEED_SHMGET_PROTO          vTRUE
#define vportNEED_SOCKET_PROTO          vTRUE
#define vportNEED_TIME_PROTO            vTRUE
#endif /* #if (__GNUC__) */
#define vportBAD_ATEXIT                 vTRUE
#define vportBAD_BSD_ARPA_INET_HDR      vTRUE
#define vportBAD_LIBC_HDR               vTRUE
#define vportBAD_SRANDOM                vTRUE
#define vportBAD_SYS_FCNTL_HDR          vTRUE
#define vportBAD_SYS_SELECT_HDR         vTRUE
#define vportBAD_SYS_MNTENT_HDR         vTRUE
#define vportBAD_SYS_WAIT_HDR           vTRUE
#define vportBAD_TM_ZONE                vTRUE
#define vportBAD_ULIMIT_HDR             vTRUE
#define vportNEED_STRERROR_PROTO        vTRUE
#endif /* #if (AUX) */

/* Borland C/C++ */
#if (defined(__BORLANDC__) && vportOS_WIN32S)
#define MK_FP32(p)                                      ((void*)p)
#define vportAPP_EXPANDS_WILDCARDS                      vTRUE
#define vportBAD_ARPA_INET_HDR                          vTRUE
#define vportBAD_BSD_NETINET_IN_HDR                     vTRUE
#define vportBAD_CHOWN                                  vTRUE
#define vportBAD_DOSSETFILELOCKS                        vTRUE
#define vportBAD_D_INO                                  vTRUE
#define vportBAD_ENDGRENT                               vTRUE
#define vportBAD_ENDPWENT                               vTRUE
#define vportBAD_FORK                                   vTRUE
#define vportBAD_FTRUNCATE                              vTRUE
#define vportBAD_GETDTABLESIZE                          vTRUE
#define vportBAD_GETEGID                                vTRUE
#define vportBAD_GETEUID                                vTRUE
#define vportBAD_GETGID                                 vTRUE
#define vportBAD_GETGRGID                               vTRUE
#define vportBAD_GETGRGID_R                             vTRUE
#define vportBAD_GETPWUID                               vTRUE
#define vportBAD_GETPWUID_R                             vTRUE
#define vportBAD_GETTIMEOFDAY                           vTRUE
#define vportBAD_GETUID                                 vTRUE
#define vportBAD_GETWD                                  vTRUE
#define vportBAD_GRENT_R                                vTRUE
#define vportBAD_GRP_HDR                                vTRUE
#define vportBAD_HTONL                                  vTRUE
#define vportBAD_LIBC_HDR                               vTRUE
#define vportBAD_LOCKF                                  vTRUE
#define vportBAD_LSTAT                                  vTRUE
#define vportBAD_NETDB_HDR                              vTRUE
#define vportBAD_NETINET_IN_HDR                         vTRUE
#define vportBAD_NTOHL                                  vTRUE
#define vportBAD_PATHCONF                               vTRUE
#define vportBAD_PWD_HDR                                vTRUE
#define vportBAD_PWENT_R                                vTRUE
#define vportBAD_RAND_R                                 vTRUE
#define vportBAD_READDIR_R                              vTRUE
#define vportBAD_READLINK                               vTRUE
#define vportBAD_REMAINDER                              vTRUE
#define vportBAD_SELECT                                 vTRUE
#define vportBAD_SLEEP                                  vTRUE
#define vportBAD_STDIO_HANDLES                          vTRUE
#define vportBAD_SYMLINK                                vTRUE
#define vportBAD_SYSCONF                                vTRUE
#define vportBAD_SYSLOG                                 vTRUE
#define vportBAD_SYS_FILE_HDR                           vTRUE
#define vportBAD_SYS_FILIO_HDR                          vTRUE
#define vportBAD_SYS_IOCTL_HDR                          vTRUE
#define vportBAD_SYS_PARAM_HDR                          vTRUE
#define vportBAD_SYS_RESOURCE_HDR                       vTRUE
#define vportBAD_SYS_SELECT_HDR                         vTRUE
#define vportBAD_SYS_SOCKET_HDR                         vTRUE
#define vportBAD_SYS_TERMIO_HDR                         vTRUE
#define vportBAD_SYS_TIMES_HDR                          vTRUE
#define vportBAD_SYS_TIME_HDR                           vTRUE
#define vportBAD_SYS_UIO_HDR                            vTRUE
#define vportBAD_SYS_UN_HDR                             vTRUE
#define vportBAD_SYS_UTSNAME_HDR                        vTRUE
#define vportBAD_SYS_WAIT_HDR                           vTRUE
#define vportBAD_TM_ZONE                                vTRUE
#define vportBAD_ULIMIT                                 vTRUE
#define vportBAD_ULIMIT_HDR                             vTRUE
#define vportBAD_UNISTD_HDR                             vTRUE
#define vportBAD_UNIX_DOMAIN_SOCKETS                    vTRUE
#define vportAMPERSAND_MEMBER_REFERENCE                 vTRUE
#define vportDIRENT_INCLUDES_WINDOWS_H                  vTRUE
#define vportDLL_WIN                                    vTRUE
#define vportDONT_BREAK_INTERFACE                       vTRUE
#define vportHAS_OPEN_DENY                              vTRUE
#define vportMKDIR_ASSUMES_MODE                         vTRUE
#define vportNEED_DOS_FILESYSTEM                        vTRUE
#define vportNEED_GROUP_STRUCT                          vTRUE
#define vportNEED_PASSWD_STRUCT                         vTRUE
#define vportNEED_UNDERSCORE_TIMEZONE                   vTRUE
#define vportNEED_NOUNDERSCORE_CHSIZE                   vTRUE
#define vportOS_WIN32S_BORLAND                          vTRUE
#define vportUNC_PATHNAMES                              vTRUE
#define vportUSES_FONT_PSIZE                            vTRUE
#define vportWINDOWS_SOCKETS                            vTRUE
#define vport__IMPORT                                   __import
#if (defined(__cplusplus) && vportCPLUSPLUS_SOURCE)
# define main(a,b)                                      _vcompatMain(a,b)
#endif
#ifdef _RTLDLL
# define vportDLL_LINK                                 __declspec(dllimport)
# define vportDLL_CLASS_LINK                           __declspec(dllimport)
#endif /* _RTLDLL */

#if (!vgalaxyNO_DEFAULT_LIB)
# define vportUSE_LIB_PRAGMAS                           vTRUE
#endif

#if (!vportGALAXY_LIB_MEMBER)
# if (!vgalaxyNO_DEFAULT_LIB)
#  if (vportCPLUSPLUS_SOURCE)
#   if (vportI18N)
#    if (vportDEBUG)
#     ifdef _RTLDLL
#      pragma comment(lib, "vgalp.lib")
#      pragma comment(lib, "vginitp.lib")
#     else
#      pragma comment(lib, "vgalps.lib")
#      pragma comment(lib, "vginitps.lib")
#     endif /* (_RTLDLL) */
#    else
#     ifdef _RTLDLL
#      pragma comment(lib, "vgalo.lib")
#      pragma comment(lib, "vginito.lib")
#     else
#      pragma comment(lib, "vgalos.lib")
#      pragma comment(lib, "vginitos.lib")
#     endif /* (_RTLDLL) */
#    endif /* (vportDEBUG) */
#   else
#    if (vportDEBUG)
#     ifdef _RTLDLL
#      pragma comment(lib, "vgaln.lib")
#      pragma comment(lib, "vginitn.lib")
#     else
#      pragma comment(lib, "vgalns.lib")
#      pragma comment(lib, "vginitns.lib")
#     endif /* (_RTLDLL) */
#    else
#     ifdef _RTLDLL
#      pragma comment(lib, "vgalm.lib")
#      pragma comment(lib, "vginitm.lib")
#     else
#      pragma comment(lib, "vgalms.lib")
#      pragma comment(lib, "vginitms.lib")
#     endif /* (_RTLDLL) */
#    endif /* (vportDEBUG) */
#   endif /* (vportI18N) */
#  else
#   if (vportI18N)
#    if (vportDEBUG)
#     ifdef _RTLDLL
#      pragma comment(lib, "vgall.lib")
#      pragma comment(lib, "vginitl.lib")
#     else
#      pragma comment(lib, "vgalls.lib")
#      pragma comment(lib, "vginitls.lib")
#     endif /* (_RTLDLL) */
#    else
#     ifdef _RTLDLL
#      pragma comment(lib, "vgalk.lib")
#      pragma comment(lib, "vginitk.lib")
#     else
#      pragma comment(lib, "vgalks.lib")
#      pragma comment(lib, "vginitks.lib")
#     endif /* (_RTLDLL) */
#    endif /* (vportDEBUG) */
#   else
#    if (vportDEBUG)
#     ifdef _RTLDLL
#      pragma comment(lib, "vgalj.lib")
#      pragma comment(lib, "vginitj.lib")
#     else
#      pragma comment(lib, "vgaljs.lib")
#      pragma comment(lib, "vginitjs.lib")
#     endif /* (_RTLDLL) */
#    else
#     ifdef _RTLDLL
#      pragma comment(lib, "vgali.lib")
#      pragma comment(lib, "vginiti.lib")
#     else
#      pragma comment(lib, "vgalis.lib")
#      pragma comment(lib, "vginitis.lib")
#     endif /* (_RTLDLL) */
#    endif /* (vportDEBUG) */
#   endif /* (vportI18N) */
#  endif /* (vportCPLUSPLUS_SOURCE) */
# endif /* !vgalaxyNO_DEFAULT_LIB */
#endif /* !vportGALAXY_LIB_MEMBER */

#endif

/* Data General's DG/UX 5.4 */
#if (__DGUX__)
#define vportBAD_LIBC_HDR                               vTRUE
#define vportBAD_SYS_SELECT_HDR                         vTRUE
#define vportBAD_TM_ZONE                                vTRUE
#define vportBAD_UNION_WAIT                             vTRUE
#define vportINET_ADDR_RETURNS_STRUCT                   vTRUE
#define vportNEED_ACCEPT_PROTO                          vTRUE
#define vportNEED_BIND_PROTO                            vTRUE
#define vportNEED_BZERO_PROTO                           vTRUE
#define vportNEED_CONNECT_PROTO                         vTRUE
#define vportNEED_GETHOSTNAME_PROTO                     vTRUE
#define vportNEED_GETPEERNAME_PROTO                     vTRUE
#define vportNEED_GETSOCKNAME_PROTO                     vTRUE
#define vportNEED_GETSOCKOPT_PROTO                      vTRUE
#define vportNEED_GETTIMEOFDAY_PROTO                    vTRUE
#define vportNEED_GETWD_PROTO                           vTRUE
#define vportNEED_LISTEN_PROTO                          vTRUE
#define vportNEED_RANDOM_PROTO                          vTRUE
#define vportNEED_RECVFROM_PROTO                        vTRUE
#define vportNEED_SELECT_PROTO                          vTRUE
#define vportNEED_SENDTO_PROTO                          vTRUE
#define vportNEED_SETSOCKOPT_PROTO                      vTRUE
#define vportNEED_SOCKET_PROTO                          vTRUE
#define vportNEED_SRANDOM_PROTO                         vTRUE
#define vportNEED_STRERROR_PROTO                        vTRUE
#define _SYSV3_LIMITS_FLAVOR                            vTRUE
#endif

#if (hcx)
#endif

/* EMX gcc under OS/2 2.0 */
#if (__EMX__)
#define vportBAD_ARPA_INET_HDR                          vTRUE
#define vportBAD_BSD_NETINET_IN_HDR                     vTRUE
#define vportBAD_SOCKETS                                vTRUE
#define vportBAD_CHOWN                                  vTRUE
#define vportBAD_ENDGRENT                               vTRUE
#define vportBAD_FORK                                   vTRUE
#define vportBAD_GETDTABLESIZE                          vTRUE
#define vportBAD_GETGRGID                               vTRUE
#define vportBAD_GRP_HDR                                vTRUE
#define vportBAD_HTONL                                  vTRUE
#define vportBAD_LIBC_HDR                               vTRUE
#define vportBAD_LOCKF                                  vTRUE
#define vportBAD_LSTAT                                  vTRUE
#define vportBAD_NETDB_HDR                              vTRUE
#define vportBAD_NETINET_IN_HDR                         vTRUE
#define vportBAD_NTOHL                                  vTRUE
#define vportBAD_PATHCONF                               vTRUE
#define vportBAD_RANDOM                                 vTRUE
#define vportBAD_READLINK                               vTRUE
#define vportBAD_SRANDOM                                vTRUE
#define vportBAD_SYSCONF                                vTRUE
#define vportBAD_SYS_IOCTL_HDR                          vTRUE
#define vportBAD_SYSLOG                                 vTRUE
#define vportBAD_SYS_SELECT_HDR                         vTRUE
#define vportBAD_SYS_SOCKET_HDR                         vTRUE
#define vportBAD_SYS_UN_HDR                             vTRUE
#define vportBAD_SYS_UTSNAME_HDR                        vTRUE
#define vportBAD_TM_ZONE                                vTRUE
#define vportBAD_ULIMIT                                 vTRUE
#define vportBAD_ULIMIT_HDR                             vTRUE
#define vportDLL_OS2                                    vTRUE
#define vportMKDIR_ASSUMES_MODE                         vTRUE
#define vportNEED_ACCESS_PROTO                          vTRUE
#define vportNEED_CHMOD_PROTO                           vTRUE
#define vportNEED_CLOSE_PROTO                           vTRUE
#define vportNEED_GETEGID_PROTO                         vTRUE
#define vportNEED_GETEUID_PROTO                         vTRUE
#define vportNEED_GETGID_PROTO                          vTRUE
#define vportNEED_GETUID_PROTO                          vTRUE
#define vportNEED_GROUP_STRUCT                          vTRUE
#define vportNEED_LSEEK_PROTO                           vTRUE
#define vportNEED_OPEN_PROTO                            vTRUE
#define vportNEED_READ_PROTO                            vTRUE
#define vportNEED_SELECT_PROTO                          vTRUE
#define vportNEED_SSIZE_T_TYPE                          vTRUE
#define vportNEED_STRERROR_PROTO                        vTRUE
#define vportNEED_WRITE_PROTO                           vTRUE
#endif

#if (ENCORE)
#endif

/* FreeBSD 2.x */
#if (__FreeBSD__)
#define vportBAD_DLSYM                                  vTRUE
#define vportBAD_DOSSETFILELOCKS                        vTRUE
#define vportBAD_ECVT                                   vTRUE
#define vportBAD_GETGRGID_R                             vTRUE
#define vportBAD_GETPWUID_R                             vTRUE
#define vportBAD_GRENT_R                                vTRUE
#define vportBAD_LIBC_HDR                               vTRUE
#define vportBAD_LOCKF                                  vTRUE
#define vportBAD_LOCKING                                vTRUE
#define vportBAD_PWENT_R                                vTRUE
#define vportBAD_RAND_R                                 vTRUE
#define vportBAD_READDIR_R                              vTRUE
#define vportBAD_ULIMIT_HDR                             vTRUE
#define vportDLL_DLSYM                                  vTRUE
#define vportDONT_UNION_SEMUN                           vTRUE
#define vportNEED_ECVT_PROTO                            vTRUE
#define vportUSE_POSIX_THREADS                          vTRUE
#endif

/* Hitachi */
#if (__H3050RX)
#define H3050R                                          vTRUE
#define _INCLUDE_POSIX_SOURCE                           vTRUE
#define _INCLUDE_XOPEN_SOURCE                           vTRUE
#define vportBAD_LIBC_HDR                               vTRUE
#define vportBAD_SYS_SELECT_HDR                         vTRUE
#define vportBAD_TM_ZONE                                vTRUE
#define vportBAD_UNION_WAIT                             vTRUE
#define vportFD_SET_CAST                                int*
#define vportRUSAGE_CAST                                int*
#endif

/* HP-UX */
#if (__hp9000s300 || __hp9000s700 || __hp9000s800)
#define vportBAD_GETWD                                  vTRUE
#define vportBAD_LIBC_HDR                               vTRUE
#define vportBAD_RAND_R                                 vTRUE
#define vportBAD_SYS_SELECT_HDR                         vTRUE
#define vportBAD_TM_ZONE                                vTRUE
#define vportBAD_UDP_FIONREAD                           vTRUE
#define vportBAD_UNION_WAIT                             vTRUE
#define vportBAD_X_WINDOW_MANAGER_COMPOUND_TEXT         vTRUE
#define vportDLL_FINDSYM                                vTRUE
#define vportHAS_LONG_LONG                              vTRUE
#define vportUSE_LONG_LONG                              vTRUE
#ifdef __cplusplus
# define vportCPLUSPLUS_EXCEPTIONS                      vFALSE
# if (!__GNUC__)
#  define vportBAD_SIGNED                               vTRUE
#  define vportBAD_VOLATILE                             vTRUE
# endif
#endif
#if (vportPRE_HPUX_10)
# define vportBAD_GETDTABLESIZE                         vTRUE
# define vportBAD_GETGRGID_R                            vTRUE
# define vportBAD_GETPWUID_R                            vTRUE
# define vportBAD_GRENT_R                               vTRUE
# define vportBAD_PWENT_R                               vTRUE
# define vportBAD_RANDOM                                vTRUE
# define vportBAD_READDIR_R                             vTRUE
# define vportBAD_SIGNED                                vTRUE
# define vportBAD_SRANDOM                               vTRUE
# define vportBAD_VOLATILE                              vTRUE
# define vportFD_SET_CAST                               int*
# define vportNEED_MNTENT_HDR                           vTRUE
# define vportNEED_STRERROR_PROTO                       vTRUE
# define vportRUSAGE_CAST                               int*
#else /* HP-UX 10.00 or later */
# if (vportHPUX_VERSION < 0x10100000) /* pre HP-UX 10.10 */
#  define vportFD_SET_CAST                              int*
#  define vportRUSAGE_CAST                              int*
# endif
# define vportUSE_DCE_THREADS                           vTRUE
# define vportUSE_POSIX_DRAFT4_GETGRGID_R               vTRUE
# define vportUSE_POSIX_DRAFT4_GETPWUID_R               vTRUE
# define vportUSE_POSIX_DRAFT4_READDIR_R                vTRUE
#endif
#endif

/* Intergraph Clipper (Clipper Unix (CLIX)) */
#if (clipper || __clipper || __clipper__)
#define vportBAD_GETWD                                  vTRUE
#define vportBAD_LIBC_HDR                               vTRUE
#define vportBAD_SYS_SELECT_HDR                         vTRUE
#define vportBAD_TM_ZONE                                vTRUE
#define vportBAD_ULIMIT_HDR                             vTRUE
#define vportNEED_GETCWD_PROTO                          vTRUE
#define vportNEED_GETGRGID_PROTO                        vTRUE
#define vportNEED_SHMAT_PROTO                           vTRUE
#define vportNEED_STRERROR_PROTO                        vTRUE
#endif

#if (ix386)
#endif

#if (__linux__)
#define vportNEED_STRERROR_PROTO                        vTRUE
#define vportBAD_DOSSETFILELOCKS                        vTRUE
#define vportBAD_LIBC_HDR                               vTRUE
#define vportBAD_LOCKF                                  vTRUE
#define vportBAD_LOCKING                                vTRUE
#define vportBAD_SYS_SELECT_HDR                         vTRUE
#define vportBAD_TM_ZONE                                vTRUE
#define vportBAD_ULIMIT_HDR                             vTRUE
#define vportDONT_UNION_SEMUN                           vTRUE
#define vportBAD_REMAINDER                              vTRUE
#define vportDLL_DLSYM                                  vTRUE
#define vportBAD_GETGRGID_R                             vTRUE
#define vportBAD_GETPWUID_R                             vTRUE
#define vportBAD_GRENT_R                                vTRUE
#define vportBAD_PWENT_R                                vTRUE
#define vportBAD_RAND_R                                 vTRUE
#define vportBAD_READDIR_R                              vTRUE
#define vportBAD_UNION_WAIT                             vTRUE
#define vportUSE_POSIX_THREADS                          vTRUE
#endif

/* MetaWare */
#if (__HIGHC__)
#ifdef unix /* MetaWare High C for NCR SVR4 */
# define vportBAD_GETWD                                 vTRUE
# define vportBAD_LIBC_HDR                              vTRUE
# define vportBAD_TM_ZONE                               vTRUE
# define vportBAD_UNION_WAIT                            vTRUE
# define vportBAD_WAIT3                                 vTRUE
#else /* MetaWare High C for Windows NT */
# define vportBAD_LIBC_HDR                              vTRUE
# define vportBAD_SYS_FILE_HDR                          vTRUE
# define vportBAD_SYS_FILIO_HDR                         vTRUE
# define vportBAD_SYS_IOCTL_HDR                         vTRUE
# define vportBAD_SYSLOG                                vTRUE
# define vportBAD_SYS_PARAM_HDR                         vTRUE
# define vportBAD_SYS_TERMIO_HDR                        vTRUE
# define vportDLL_WIN                                   vTRUE
#endif
#endif

/* MSVC */
#if (_MSC_VER >= 800 && !__HIGHC__)
#define MK_FP32(p)                                      p
#define vportAPP_EXPANDS_WILDCARDS                      vTRUE
#define vportBAD_ARPA_INET_HDR                          vTRUE
#define vportBAD_ATEXIT                                 vTRUE
#define vportBAD_BOOL                                   vTRUE
#define vportBAD_BSD_ARPA_INET_HDR                      vTRUE
#define vportBAD_BSD_NETINET_IN_HDR                     vTRUE
#define vportBAD_BSD_SYS_TYPES_HDR                      vTRUE
#define vportBAD_CHOWN                                  vTRUE
#define vportBAD_CLOSEDIR                               vTRUE
#define vportBAD_DIR                                    vTRUE
#define vportBAD_DIRENT_HDR                             vTRUE
#define vportBAD_DIR_HDR                                vTRUE
#define vportBAD_DOSFINDCLOSE                           vTRUE
#define vportBAD_DOSFINDFIRST                           vTRUE
#define vportBAD_DOSFINDNEXT                            vTRUE
#define vportBAD_DOSSETFILELOCKS                        vTRUE
#define vportBAD_DOS_FILENAME_TRUNCATION                vTRUE
#define vportBAD_ENDGRENT                               vTRUE
#define vportBAD_ENDPWENT                               vTRUE
#define vportBAD_FORK                                   vTRUE
#define vportBAD_FSTAT                                  vTRUE
#define vportBAD_FTRUNCATE                              vTRUE
#define vportBAD_GETDTABLESIZE                          vTRUE
#define vportBAD_GETEGID                                vTRUE
#define vportBAD_GETEUID                                vTRUE
#define vportBAD_GETGID                                 vTRUE
#define vportBAD_GETGRGID                               vTRUE
#define vportBAD_GETGRGID_R                             vTRUE
#define vportBAD_GETPWUID                               vTRUE
#define vportBAD_GETPWUID_R                             vTRUE
#define vportBAD_GETTIMEOFDAY                           vTRUE
#define vportBAD_GETUID                                 vTRUE
#define vportBAD_GETWD                                  vTRUE
#define vportBAD_GRP_HDR                                vTRUE
#define vportBAD_GRENT_R                                vTRUE
#define vportBAD_HTONL                                  vTRUE
#define vportBAD_INFINITY_CONSTANT                      vTRUE
#define vportBAD_LIBC_HDR                               vTRUE
#define vportBAD_LOCKF                                  vTRUE
#define vportBAD_LSTAT                                  vTRUE
#define vportBAD_NAN_CONSTANT                           vTRUE
#define vportBAD_NETDB_HDR                              vTRUE
#define vportBAD_NETINET_IN_HDR                         vTRUE
#define vportBAD_NTOHL                                  vTRUE
#define vportBAD_OPENDIR                                vTRUE
#define vportBAD_OS2_HDR                                vTRUE
#define vportBAD_PATHCONF                               vTRUE
#define vportBAD_PIPE                                   vTRUE
#define vportBAD_PWD_HDR                                vTRUE
#define vportBAD_PWENT_R                                vTRUE
#define vportBAD_RAND_R                                 vTRUE
#define vportBAD_RANDOM                                 vTRUE
#define vportBAD_READDIR                                vTRUE
#define vportBAD_READDIR_R                              vTRUE
#define vportBAD_READLINK                               vTRUE
#define vportBAD_REMAINDER                              vTRUE
#define vportBAD_REWINDDIR                              vTRUE
#define vportBAD_REWINDDIR                              vTRUE
#define vportBAD_RINT                                   vTRUE
#define vportBAD_SELECT                                 vTRUE
#define vportBAD_SLEEP                                  vTRUE
#define vportBAD_SOCKET_CLOSE                           vTRUE
#define vportBAD_SOCKET_IOCTL                           vTRUE
#define vportBAD_SOCKET_READ                            vTRUE
#define vportBAD_SOCKET_WRITE                           vTRUE
#define vportBAD_SRANDOM                                vTRUE
#define vportBAD_STRUCT_DIRENT                          vTRUE
#define vportBAD_SYMLINK                                vTRUE
#define vportBAD_SYSCONF                                vTRUE
#define vportBAD_SYSLOG                                 vTRUE
#define vportBAD_SYS_DIRENT_HDR                         vTRUE
#define vportBAD_SYS_DIR_HDR                            vTRUE
#define vportBAD_SYS_FILE_HDR                           vTRUE
#define vportBAD_SYS_FILIO_HDR                          vTRUE
#define vportBAD_SYS_IOCTL_HDR                          vTRUE
#define vportBAD_SYS_IPC_HDR                            vTRUE
#define vportBAD_SYS_PARAM_HDR                          vTRUE
#define vportBAD_SYS_RESOURCES                          vTRUE
#define vportBAD_SYS_RESOURCE_HDR                       vTRUE
#define vportBAD_SYS_SELECT_HDR                         vTRUE
#define vportBAD_SYS_SHM_HDR                            vTRUE
#define vportBAD_SYS_SOCKET_HDR                         vTRUE
#define vportBAD_SYS_TERMIO_HDR                         vTRUE
#define vportBAD_SYS_TIMES_HDR                          vTRUE
#define vportBAD_SYS_TIME_HDR                           vTRUE
#define vportBAD_SYS_TYPES_HDR                          vTRUE
#define vportBAD_SYS_UIO_HDR                            vTRUE
#define vportBAD_SYS_UN_HDR                             vTRUE
#define vportBAD_SYS_UTIME_HDR                          vTRUE
#define vportBAD_SYS_UTSNAME_HDR                        vTRUE
#define vportBAD_SYS_WAIT_HDR                           vTRUE
#define vportBAD_TM_ZONE                                vTRUE
#define vportBAD_TYPES_HDR                              vTRUE
#define vportBAD_ULIMIT                                 vTRUE
#define vportBAD_ULIMIT_HDR                             vTRUE
#define vportBAD_UNISTD_HDR                             vTRUE
#define vportBAD_UNIX_DOMAIN_SOCKETS                    vTRUE
#define vportBAD_UTIME_HDR                              vTRUE
#define vportBAD_VOLATILE_STRUCT_ASSIGNMENT             vTRUE
#define vportBAD_X_SHM                                  vTRUE
#define vportBAD__DOS_GETDISKFREE                       vTRUE
#define vportBAD__DOS_GETDRIVE                          vTRUE
#define vportBAD__DOS_GETFILEATTR                       vTRUE
#define vportBAD__DOS_SETDRIVE                          vTRUE
#define vportBROKEN_LONG_STRINGS                        vTRUE
#define vportBROKEN_MEMBER_REFERENCE                    vTRUE
#if (vportDEBUG)
#define vportBAD_STDIO_HANDLES                          vTRUE
#else
#define vportDONT_INTERCEPT_STDIO                       vTRUE
#endif
#define vportDLL_WIN                                    vTRUE
#define vportDONT_BREAK_INTERFACE                       vTRUE
#define vportDYNLOAD_WINSOCK                            vTRUE
#define vportHAS_OPEN_DENY                              vTRUE
#define vportHAS_WINMAIN                                vTRUE
#define vportINT64                                      __int64
#define vportMKDIR_ASSUMES_MODE                         vTRUE
#define vportNEED_DOS_FILESYSTEM                        vTRUE
#define vportNEED_GID_T_TYPE                            vTRUE
#define vportNEED_GROUP_STRUCT                          vTRUE
#define vportNEED_MODE_T_TYPE                           vTRUE
#define vportNEED_PASSWD_STRUCT                         vTRUE
#define vportNEED_POPEN_PROTO                           vTRUE
#define vportNEED_PROCESS_HDR                           vTRUE
#define vportNEED_UID_T_TYPE                            vTRUE
#define vportNEED_UNDERSCORE_CLIB_NAMES                 vTRUE
#define vportNEED_UNDERSCORE_TIMEZONE                   vTRUE
#define vportOS_WIN32S_MSVC                             vTRUE
#define vportUNC_PATHNAMES                              vTRUE
#define vportUSE_COMMIT_FOR_FFLUSH                      vTRUE
#define vportUSES_FONT_PSIZE                            vTRUE
#define vportWINDOWS_SOCKETS                            vTRUE
#if (_DLL)
# define vportDLL_LINK                                  __declspec(dllimport)
# define vportDLL_CLASS_LINK                            __declspec(dllimport)
#endif

#if (vportCPLUSPLUS_SOURCE)
# if (vportI18N)
#  if (vportDEBUG)
#   define vportGALAXY_LIB_SUFFIX1  "h"
#  else
#   define vportGALAXY_LIB_SUFFIX1  "g"
#  endif /* (vportDEBUG) */
# else
#  if (vportDEBUG)
#   define vportGALAXY_LIB_SUFFIX1  "f"
#  else
#   define vportGALAXY_LIB_SUFFIX1  "e"
#  endif /* (vportDEBUG) */
# endif /* (vportI18N) */
#else
# if (vportI18N)
#  if (vportDEBUG)
#   define vportGALAXY_LIB_SUFFIX1  "d"
#  else
#   define vportGALAXY_LIB_SUFFIX1  "c"
#  endif /* (vportDEBUG) */
# else
#  if (vportDEBUG)
#   define vportGALAXY_LIB_SUFFIX1  "b"
#  else
#   define vportGALAXY_LIB_SUFFIX1  "a"
#  endif /* (vportDEBUG) */
# endif /* (vportI18N) */
#endif /* (vportCPLUSPLUS_SOURCE) */

#if (_DLL)
# define vportGALAXY_LIB_SUFFIX vportGALAXY_LIB_SUFFIX1
#else
# define vportGALAXY_LIB_SUFFIX vportGALAXY_LIB_SUFFIX1 "s"
#endif

#if (!vgalaxyNO_DEFAULT_LIB)
# define vportUSE_LIB_PRAGMAS                           vTRUE
#endif

#if (!vportGALAXY_LIB_MEMBER)
# if (!vgalaxyNO_DEFAULT_LIB)
#  pragma comment(lib, "vgal" vportGALAXY_LIB_SUFFIX ".lib")
#  pragma comment(lib, "vginit" vportGALAXY_LIB_SUFFIX ".lib")
# endif /* !vgalaxyNO_DEFAULT_LIB */
#endif /* !vportGALAXY_LIB_MEMBER */

#if (vportWIN_X11)
# define main(a, b)                                     _vcompatMain(a, b)
#endif
#endif /* if (_MSC_VER >= 800) */

/* MIPS RISC/OS 4 cc */
#if (mips && !ultrix && !sgi && !__sgi && !_MSC_VER && !__sony && !sinix && !_nec)
#if (vportPRE_RISC_OS_5_0)
#if (!__GNUC__)
#define vportBAD_CONST                                  vTRUE
#endif
#define vportBAD_STDLIB_HDR                             vTRUE
#define vportBAD_SYS_SELECT_HDR                         vTRUE
#define vportBAD_SYS_TIME_HDR                           vTRUE
#define vportFD_SET_CAST                                int*
#define vportNEED_ABORT_PROTO                           vTRUE
#define vportNEED_ABS_PROTO                             vTRUE
#define vportNEED_ACCESS_PROTO                          vTRUE
#define vportNEED_ATEXIT_PROTO                          vTRUE
#define vportNEED_ATOF_PROTO                            vTRUE
#define vportNEED_ATOI_PROTO                            vTRUE
#define vportNEED_ATOL_PROTO                            vTRUE
#define vportNEED_BCOPY_PROTO                           vTRUE
#define vportNEED_BSD_SYS_TIME_HDR                      vTRUE
#define vportNEED_CALLOC_PROTO                          vTRUE
#define vportNEED_CHDIR_PROTO                           vTRUE
#define vportNEED_CHMOD_PROTO                           vTRUE
#define vportNEED_CHOWN_PROTO                           vTRUE
#define vportNEED_CLOSE_PROTO                           vTRUE
#define vportNEED_CREAT_PROTO                           vTRUE
#define vportNEED_ENDGRENT_PROTO                        vTRUE
#define vportNEED_ENDPWENT_PROTO                        vTRUE
#define vportNEED_EXIT_PROTO                            vTRUE
#define vportNEED_FSTAT_PROTO                           vTRUE
#define vportNEED_GETEGID_PROTO                         vTRUE
#define vportNEED_GETENV_PROTO                          vTRUE
#define vportNEED_GETEUID_PROTO                         vTRUE
#define vportNEED_GETGID_PROTO                          vTRUE
#define vportNEED_GETPID_PROTO                          vTRUE
#define vportNEED_GETTIMEOFDAY_PROTO                    vTRUE
#define vportNEED_GETUID_PROTO                          vTRUE
#define vportNEED_LINK_PROTO                            vTRUE
#define vportNEED_LOCKF_PROTO                           vTRUE
#define vportNEED_LSEEK_PROTO                           vTRUE
#define vportNEED_MALLOC_HDR                            vTRUE
#define vportNEED_MKDIR_PROTO                           vTRUE
#define vportNEED_MODE_T_TYPE                           vTRUE
#define vportNEED_OPEN_PROTO                            vTRUE
#define vportNEED_PERROR_PROTO                          vTRUE
#define vportNEED_PID_T_TYPE                            vTRUE
#define vportNEED_QSORT_PROTO                           vTRUE
#define vportNEED_RAND_PROTO                            vTRUE
#define vportNEED_READLINK_PROTO                        vTRUE
#define vportNEED_READ_PROTO                            vTRUE
#define vportNEED_RMDIR_PROTO                           vTRUE
#define vportNEED_SELECT_PROTO                          vTRUE
#define vportNEED_SRAND_PROTO                           vTRUE
#define vportNEED_SSIZE_T_TYPE                          vTRUE
#define vportNEED_STAT_PROTO                            vTRUE
#define vportNEED_SYMLINK_PROTO                         vTRUE
#define vportNEED_TIME_PROTO                            vTRUE
#define vportNEED_TOLOWER_PROTO                         vTRUE
#define vportNEED_TOUPPER_PROTO                         vTRUE
#define vportNEED_UNLINK_PROTO                          vTRUE
#define vportNEED_WRITE_PROTO                           vTRUE
#define vportNEED__FLSBUF_PROTO                         vTRUE
#endif /* if (vportPRE_RISC_OS_5_0) */
#define vportBAD_ARPA_INET_HDR                          vTRUE
#define vportBAD_ATEXIT                                 vTRUE
#define vportBAD_CHOWN_NEGATIVE_ONE                     vTRUE
#define vportBAD_LIBC_HDR                               vTRUE
#define vportBAD_MEMMOVE                                vTRUE
#define vportBAD_NETINET_IN_HDR                         vTRUE
#define vportBAD_STRERROR                               vTRUE
#define vportBAD_SYSCONF                                vTRUE
#define vportBAD_SYS_UN_HDR                             vTRUE
#define vportBAD_SYS_UTIME_HDR                          vTRUE
#define vportBAD_TM_ZONE                                vTRUE
#define vportBAD_ULIMIT_HDR                             vTRUE
#define vportBAD_UTIME_HDR                              vTRUE
#define vportBAD_WAITPID                                vTRUE
#define vportHAS_TLI                                    vTRUE /* !!! BAD_TLI */
#define vportNEED_BSD_SYS_UN_HDR                        vTRUE
#define vportNEED_GETCWD_PROTO                          vTRUE
#define vportNEED_GETGRGID_PROTO                        vTRUE
#define vportNEED_GETPWUID_PROTO                        vTRUE
#define vportNEED_STRERROR_PROTO                        vTRUE
#endif

/* NEC SVR4.2MP-NEC 11.1 for the NEC EWS workstation */
#if (_nec)
#define vportBAD_ATEXIT                                 vTRUE
#define vportBAD_BOOL                                   vTRUE
#define vportBAD_GETWD                                  vTRUE
#define vportBAD_LIBC_HDR                               vTRUE
#define vportBAD_TM_ZONE                                vTRUE
#define vportBAD_UNION_WAIT                             vTRUE
#define vportBAD_WAIT3                                  vTRUE
#define vportCPLUSPLUS_EXCEPTIONS                       vFALSE
#define vportNEED_GETHOSTNAME_PROTO                     vTRUE
#define vportNEED_GETTIMEOFDAY_PROTO                    vTRUE
#if (vportCPLUSPLUS_SOURCE)
#define vportSIG_PF                                     SIG_PF
#endif
#endif

/* NeXT Step 3.0 */
#if (NeXT)
#define vportBAD_DIRECT_HDR                             vTRUE
#define vportBAD_DIRENT_HDR                             vTRUE
#define vportBAD_SYS_SELECT_HDR                         vTRUE
#define vportBAD_SYS_UTSNAME_HDR                        vTRUE
#define vportBAD_ULIMIT_HDR                             vTRUE
#define vportBAD_UNISTD_HDR                             vTRUE
#define vportGETWD_ASSUMES_MAXPATHLEN                   vTRUE
#define vportNEED_ACCESS_PROTO                          vTRUE
#define vportNEED_CLOSEDIR_PROTO                        vTRUE
#define vportNEED_CLOSE_PROTO                           vTRUE
#define vportNEED_LINK_PROTO                            vTRUE
#define vportNEED_LOCKF_PROTO                           vTRUE
#define vportNEED_MODE_T_TYPE                           vTRUE
#define vportNEED_OPENDIR_PROTO                         vTRUE
#define vportNEED_READDIR_PROTO                         vTRUE
#define vportNEED_REWINDDIR_PROTO                       vTRUE
#define vportNEED_RMDIR_PROTO                           vTRUE
#define vportNEED_SSIZE_T_TYPE                          vTRUE
#define vportNEED_STRERROR_PROTO                        vTRUE
#define vportNEED_SYS_FCNTL_HDR                         vTRUE
#define vportNEED_UNLINK_PROTO                          vTRUE
#endif /* if (NeXT) */

/* NCR */
#if (__NCR)
#ifdef __cplusplus /* NCR C++ compiler (probably repackaged Lucid lcc) */
# define vportBAD_ADDRESS_OF_BOUND_FUNCTION             vTRUE
# define vportBAD_BOOL                                  vTRUE
# define vportBAD_GETWD                                 vTRUE
# define vportBAD_SYS_UTSNAME_HDR                       vTRUE
# define vportBAD_TM_ZONE                               vTRUE
# define vportBAD_UNION_WAIT                            vTRUE
# define vportBAD_WAIT3                                 vTRUE
# define vportGETTIMEOFDAY_TAKES_ONE_ARG                vTRUE
# define vportNEED_GETHOSTNAME_PROTO                    vTRUE
#endif
#endif

/* RISC/OS 5 cc -std */
#if (__mips && !ultrix && !sgi && !__sgi && !_MSC_VER && !__GNUC__ && !__sony && !sinix && !_nec)
#define LANGUAGE_C                                      1
#define _mips                                           1
#define vportBAD_ATEXIT                                 vTRUE
#define vportBAD_LIBC_HDR                               vTRUE
#define vportBAD_MEMMOVE                                vTRUE
#define vportBAD_NETINET_IN_HDR                         vTRUE
#define vportBAD_STRERROR                               vTRUE
#define vportBAD_ULIMIT_HDR                             vTRUE
#endif

/* IBM OS/2 32-bit compilers w/ IBM TCP/IP */
#if (__OS2__ && (__IBMC__ || __IBMCPP__))
#if (vportUSE_IBM_TCPIP)
# define vportNEED_TYPES_HDR                            vTRUE
# define vportBAD_ARPA_INET_HDR                         vTRUE
# define vportBAD_SOCKET_WRITE                          vTRUE
# define vportBAD_SOCKET_READ                           vTRUE
# define vportBAD_SYS_UN_HDR                            vTRUE
# define vportBAD_UDP_FIONREAD                          vTRUE
# define vportBAD_UNIX_DOMAIN_SOCKETS                   vTRUE
# define vportBAD_SELECT                                vTRUE
# define vportBAD_SYS_SELECT_HDR                        vFALSE
# define vportBAD_SYS_IOCTL_HDR                         vFALSE
# define vportFD_SET_CAST                               fd_set*
# define BSD_SELECT
#else
# define vportBAD_ARPA_INET_HDR                         vTRUE
# define vportBAD_BSD_NETINET_IN_HDR                    vTRUE
# define vportBAD_GETHOSTNAME                           vTRUE
# define vportBAD_NETDB_HDR                             vTRUE
# define vportBAD_NETINET_IN_HDR                        vTRUE
# define vportBAD_RANDOM                                vTRUE
# define vportBAD_SELECT                                vTRUE
# define vportBAD_SLEEP                                 vTRUE
# define vportBAD_SOCKETS                               vTRUE
# define vportBAD_SRANDOM                               vTRUE
# define vportBAD_SYS_SELECT_HDR                        vTRUE
# define vportBAD_SYS_SOCKET_HDR                        vTRUE
# define vportBAD_SYS_TIME_HDR                          vTRUE
# define vportBAD_SYS_UN_HDR                            vTRUE
# define vportBAD_SYS_IOCTL_HDR                         vTRUE
#endif /* if (vportUSE_IBM_TCPIP) else */
#define vportBAD_ACCESS_ON_DIRS                         vTRUE
#define vportBAD_BOOL                                   vTRUE
#define vportBAD_BSD_ARPA_INET_HDR                      vTRUE
#define vportBAD_CHOWN                                  vTRUE
#define vportBAD_CLOSEDIR                               vTRUE
#define vportBAD_DIR                                    vTRUE
#define vportBAD_DIRENT_HDR                             vTRUE
#define vportBAD_DOS_HDR                                vTRUE
#define vportBAD_ENDGRENT                               vTRUE
#define vportBAD_ENDPWENT                               vTRUE
#define vportBAD_EXECV                                  vTRUE
#define vportBAD_FORK                                   vTRUE
#define vportBAD_GETDISKFREESPACE                       vTRUE
#define vportBAD_GETDRIVETYPE                           vTRUE
#define vportBAD_GETDTABLESIZE                          vTRUE
#define vportBAD_GETEGID                                vTRUE
#define vportBAD_GETEUID                                vTRUE
#define vportBAD_GETFILEATTRIBUTES                      vTRUE
#define vportBAD_GETGID                                 vTRUE
#define vportBAD_GETGRGID                               vTRUE
#define vportBAD_GETGRGID_R                             vTRUE
#define vportBAD_GETPWUID                               vTRUE
#define vportBAD_GETPWUID_R                             vTRUE
#define vportBAD_GETUID                                 vTRUE
#define vportBAD_GETWD                                  vTRUE
#define vportBAD_GRENT_R                                vTRUE
#define vportBAD_GRP_HDR                                vTRUE
#define vportBAD_HTONL                                  vTRUE
#define vportBAD_LIBC_HDR                               vTRUE
#define vportBAD_LOCKF                                  vTRUE
#define vportBAD_LSTAT                                  vTRUE
#define vportBAD_NTOHL                                  vTRUE
#define vportBAD_OPENDIR                                vTRUE
#define vportBAD_PATHCONF                               vTRUE
#define vportBAD_PWD_HDR                                vTRUE
#define vportBAD_PWENT_R                                vTRUE
#define vportBAD_RAND_R                                 vTRUE
#define vportBAD_READDIR                                vTRUE
#define vportBAD_READDIR_R                              vTRUE
#define vportBAD_READLINK                               vTRUE
#define vportBAD_REMAINDER                              vTRUE
#define vportBAD_REWINDDIR                              vTRUE
#define vportBAD_RINT                                   vTRUE
#define vportBAD_STDIO_OUTPUT                           vTRUE
#define vportBAD_SYMLINK                                vTRUE
#define vportBAD_SYSCONF                                vTRUE
#define vportBAD_SYSLOG                                 vTRUE
#define vportBAD_SYS_DIRENT_HDR                         vTRUE
#define vportBAD_SYS_DIR_HDR                            vTRUE
#define vportBAD_SYS_FILE_HDR                           vTRUE
#define vportBAD_SYS_FILIO_HDR                          vTRUE
#define vportBAD_SYS_IPC_HDR                            vTRUE
#define vportBAD_SYS_PARAM_HDR                          vTRUE
#define vportBAD_SYS_RESOURCE_HDR                       vTRUE
#define vportBAD_SYS_SHM_HDR                            vTRUE
#define vportBAD_SYS_TERMIO_HDR                         vTRUE
#define vportBAD_SYS_TIMES_HDR                          vTRUE
#define vportBAD_SYS_UIO_HDR                            vTRUE
#define vportBAD_SYS_UTSNAME_HDR                        vTRUE
#define vportBAD_SYS_WAIT_HDR                           vTRUE
#define vportBAD_TIMEZONE                               vTRUE
#define vportBAD_TM_ZONE                                vTRUE
#define vportBAD_ULIMIT                                 vTRUE
#define vportBAD_ULIMIT_HDR                             vTRUE
#define vportBAD_UNISTD_HDR                             vTRUE
#define vportBAD_UTIME_HDR                              vTRUE
#define vportBAD_WINDOWS_HDR                            vTRUE
#define vportBAD__CHDRIVE                               vTRUE
#define vportBAD__DOS_GETDISKFREE                       vTRUE
#define vportBAD__DOS_GETDRIVE                          vTRUE
#define vportBAD__DOS_GETFILEATTR                       vTRUE
#define vportBAD__DOS_SETDRIVE                          vTRUE
#define vportBAD__GETDRIVE                              vTRUE
#define vportDLL_OS2                                    vTRUE
#define vportHAS_OPEN_DENY                              vTRUE
#define vportMKDIR_ASSUMES_MODE                         vTRUE
#define vportMODE_MASK                                  (S_IREAD | S_IWRITE)
#define vportNEED_CLOSEDIR_PROTO                        vTRUE
#define vportNEED_GETWD_PROTO                           vTRUE
#define vportNEED_GID_T_TYPE                            vTRUE
#define vportNEED_GROUP_STRUCT                          vTRUE
#define vportNEED_HPFS_FILESYSTEM                       vTRUE
#define vportNEED_MODE_T_TYPE                           vTRUE
#define vportNEED_OPENDIR_PROTO                         vTRUE
#define vportNEED_PASSWD_STRUCT                         vTRUE
#define vportNEED_READDIR_PROTO                         vTRUE
#define vportNEED_REWINDDIR_PROTO                       vTRUE
#define vportNEED_STRERROR_PROTO                        vTRUE
#define vportNEED_UID_T_TYPE                            vTRUE
#define vportSIG_PF                                     _SigFunc
#define vportSYSLINK                                    _Optlink
#define vportUNC_PATHNAMES                              vTRUE
#endif /* if (__OS2__ && (__IBMC__ || __IBMCPP__)) */

/* Pyramid */
#if (pyr)
#endif

#if 0
/* SCO 3.2 */
#if (unix && i386 && !__USLC__ && !_SEQUENT_ && !ix386 && !__NCR && !__linux__ && !sun && !__HIGHC__ && !__FreeBSD__)
#define vportBAD_CONST                                  vTRUE
#define vportBAD_GETWD                                  vTRUE
#define vportBAD_LIBC_HDR                               vTRUE
#define vportBAD_SYS_FILIO_HDR                          vTRUE
#define vportBAD_SYS_SELECT_HDR                         vsystimeINCLUDED
#define vportBAD_SYS_UN_HDR                             vTRUE
#define vportBAD_TM_ZONE                                vTRUE
#define vportBAD_UNION_WAIT                             vTRUE
#define vportBAD_UNIX_DOMAIN_SOCKETS                    vTRUE
#define vportBAD_WAIT3                                  vTRUE
#endif
#endif

/* SCO 5 Development System */
#if (_SCO_DS || (__unix && i386 && !__USLC__ && !_SEQUENT_ && !ix386 && !__NCR && !__linux__ && !sun && !__HIGHC__ && !__FreeBSD__))
#define vportBAD_ENDGRENT_R                             vTRUE
#define vportBAD_ENDPWENT_R                             vTRUE
#define vportBAD_GETGRGID_R                             vTRUE
#define vportBAD_GETPWUID_R                             vTRUE
#define vportBAD_LIBC_HDR                               vTRUE
#define vportBAD_SETGRENT_R                             vTRUE
#define vportBAD_SETPWENT_R                             vTRUE
#define vportBAD_SYS_FILIO_HDR                          vTRUE
#define vportUSE_SOLARIS_READDIR_R                      vTRUE
#if (__cplusplus)
extern "C" {extern int gettimeofday(struct timeval *, struct timezone *);}
#endif
#endif

/* Siemens Nixdorf Inc O/S */
#if (sinix)
#define vportBAD_ARPA_INET_HDR                          vTRUE
#define vportBAD_GETWD                                  vTRUE
#define vportBAD_LIBC_HDR                               vTRUE
#define vportBAD_TM_ZONE                                vTRUE
#define vportBAD_UNION_WAIT                             vTRUE
#define vportBAD_WAIT3                                  vTRUE
#define vportCPLUSPLUS_EXCEPTIONS                       vFALSE
#define vportDONT_MACRO_CPLUSPLUS_KEYWORDS              vTRUE
#define vportNEED_ACCEPT_PROTO                          vTRUE
#define vportNEED_BIND_PROTO                            vTRUE
#define vportNEED_CONNECT_PROTO                         vTRUE
#define vportNEED_GETHOSTNAME_PROTO                     vTRUE
#define vportNEED_GETSOCKNAME_PROTO                     vTRUE
#define vportNEED_GETSOCKOPT_PROTO                      vTRUE
#define vportNEED_GETTIMEOFDAY_PROTO                    vTRUE
#define vportNEED_INET_ADDR_PROTO                       vTRUE
#define vportNEED_LISTEN_PROTO                          vTRUE
#define vportNEED_RECVFROM_PROTO                        vTRUE
#define vportNEED_SELECT_PROTO                          vTRUE
#define vportNEED_SENDTO_PROTO                          vTRUE
#define vportNEED_SETSOCKOPT_PROTO                      vTRUE
#define vportNEED_SOCKET_PROTO                          vTRUE
#ifdef __cplusplus
# define vportBAD_GETHOSTBYADDR_SCOPE                   vTRUE
# define vportBAD_GETHOSTBYNAME_SCOPE                   vTRUE
# define vportBAD_GETSERVBYNAME_SCOPE                   vTRUE
# define vportBAD_VOLATILE                              vTRUE
# define vportNEED_GETHOSTBYADDR_PROTO                  vTRUE
# define vportNEED_GETHOSTBYNAME_PROTO                  vTRUE
# define vportNEED_GETSERVBYNAME_PROTO                  vTRUE
#endif
#endif

/* Sequent */
#if (_SEQUENT_)
#if (i386)
#else
#endif
#endif

/* SGI */
#if (sgi || __sgi)
#include <sgidefs.h>
#include <unistd.h> /* #include <standards.h> on IRIX 6 w/o breaking IRIX 5 */
#define vportBAD_ADDRESS_OF_BOUND_FUNCTION              vTRUE
#define vportBAD_ATEXIT                                 vTRUE
#define vportBAD_BOOL                                   vTRUE
#define vportBAD_GRENT_R                                vTRUE
#define vportBAD_INFINITY_CONSTANT                      vTRUE
#define vportBAD_LIBC_HDR                               vTRUE
#define vportBAD_NAN_CONSTANT                           vTRUE
#define vportBAD_PWENT_R                                vTRUE
#define vportBAD_REMAINDER                              vTRUE
#define vportBAD_SYS_SELECT_HDR                         vTRUE
#define vportBAD_TM_ZONE                                vTRUE
#define vportBAD_UDP_FIONREAD                           vTRUE
#define vportBAD_ULIMIT_HDR                             vTRUE
#define vportBAD_UNION_WAIT                             vTRUE
#define vportBAD_VFORK                                  vTRUE
#define vportDLL_DLSYM                                  vTRUE
#define vportDONT_DEFINE_NULL_HEADER                    vTRUE
#define vportDONT_UNION_SEMUN                           vTRUE
#define vportNEED_BSTRING_HDR                           vTRUE
#define vportNEED_ECVT_PROTO                            vTRUE
#define vportNEED_GETDTABLESIZE_PROTO                   vTRUE
#define vportNEED_GETHOSTNAME_PROTO                     vTRUE
#define vportNEED_IOCTL_PROTO                           vTRUE
#define vportNEED_SELECT_PROTO                          vTRUE
#define vportNEED_STRERROR_PROTO                        vTRUE
#define vportSIG_PF                                     SIG_PF
#define vportUSE_POSIX_THREADS                          vTRUE
#if ((_MIPS_SIM == _MIPS_SIM_NABI32) || (_MIPS_SIM == _MIPS_SIM_ABI64))/*-n32*/
# define vportHAS_LONG_LONG                             vTRUE
# define vportUSE_LONG_LONG                             vTRUE
#endif
#if (!defined(_POSIX1C)) /* IRIX 5 */
# define vportNEED_GETGRGID_R_PROTO                     vTRUE
# define vportUSE_SOLARIS_GETGRGID_R                    vTRUE
# define vportUSE_SOLARIS_GETPWUID_R                    vTRUE
# define vportUSE_SOLARIS_READDIR_R                     vTRUE
#endif
#endif

/* Sony NEWS O/S workstation */
#if (__sony)
#define vportBAD_ATEXIT                                 vTRUE
#define vportBAD_BOOL                                   vTRUE
#define vportBAD_GETGRGID_R                             vTRUE
#define vportBAD_GETPWUID_R                             vTRUE
#define vportBAD_GETWD                                  vTRUE
#define vportBAD_GRENT_R                                vTRUE
#define vportBAD_PWENT_R                                vTRUE
#define vportBAD_RAND_R                                 vTRUE
#define vportBAD_READDIR_R                              vTRUE
#define vportBAD_SIGNED                                 vTRUE
#define vportBAD_TM_ZONE                                vTRUE
#define vportBAD_UNION_WAIT                             vTRUE
#define vportBAD_VOLATILE                               vTRUE
#define vportBAD_WAIT3                                  vTRUE
#define vportCPLUSPLUS_EXCEPTIONS                       vFALSE
#define vportGETTIMEOFDAY_TAKES_ONE_ARG                 vTRUE
#define vportNEED_GETHOSTNAME_PROTO                     vTRUE
#endif

/* Sun */
#if (sun || __sparc__)
#if (!defined(__STDC__) && !defined(__GNUC__) && !defined(__CLCC__))
# error wrong compiler - you must use an ANSI capable compiler
#endif
#define vportBAD_ATEXIT                                 vTRUE
#define vportBAD_LIBC_HDR                               vTRUE
#define vportBAD_SYS_MNTENT_HDR                         vTRUE
#define vportDLL_DLSYM                                  vTRUE
#define vportNEED_WAIT3_PROTO                           vTRUE
#if (vportPRE_SUN_OS_5_0)
# define vportBAD_GETGRGID_R                            vTRUE
# define vportBAD_GETPWUID_R                            vTRUE
# define vportBAD_GRENT_R                               vTRUE
# define vportBAD_MEMMOVE                               vTRUE
# define vportBAD_PWENT_R                               vTRUE
# define vportBAD_RAND_R                                vTRUE
# define vportBAD_READDIR_R                             vTRUE
# define vportBAD_STRERROR                              vTRUE
# define vportBAD_STRSTR                                vTRUE
# define vportBAD_UDP_FIONREAD                          vTRUE
# define vportDONT_UNION_SEMUN                          vTRUE
# define vportNAN                                       (quiet_nan(0L))
# define vportNEED_BCOPY_PROTO                          vTRUE
# define vportNEED_FCHMOD_PROTO                         vTRUE
# define vportNEED_FTRUNCATE_PROTO                      vTRUE
# define vportNEED_MKSTEMP_PROTO                        vTRUE
# define vportNEED_MKTEMP_PROTO                         vTRUE
# define vportNEED_SEMCTL_PROTO                         vTRUE
# define vportNEED_SEMGET_PROTO                         vTRUE
# define vportNEED_SEMOP_PROTO                          vTRUE
# define vportNEED_XSHMATTACH_PROTO                     vTRUE
# define vportNEED_XSHMCREATEIMAGE_PROTO                vTRUE
# define vportNEED_XSHMDETACH_PROTO                     vTRUE
# define vportNEED_XSHMGETIMAGE_PROTO                   vTRUE
# define vportNEED_XSHMPUTIMAGE_PROTO                   vTRUE
# define vportNEED_XSHMQUERYVERSION_PROTO               vTRUE
# define vportOS_UNIX_SUNOS                             vTRUE
#else
# define vportBAD_GETWD                                 vTRUE
# define vportBAD_GRENT_R                               vTRUE
# define vportBAD_PWENT_R                               vTRUE
# define vportOS_UNIX_SOLARIS                           vTRUE
# define vportREENTRANT                                 _REENTRANT
# if (vportREENTRANT)
#  if !defined(_POSIX_PTHREAD_SEMANTICS) && !((_POSIX_C_SOURCE - 0) >= 199506L)
#   define vportUSE_SOLARIS_GETGRGID_R                  vTRUE
#   define vportUSE_SOLARIS_GETPWUID_R                  vTRUE
#   define vportUSE_SOLARIS_READDIR_R                   vTRUE
#  endif
# endif
#endif
#if (__OBJECTCENTER__)  /* CenterLine's ObjectCenter 2.0.4 */
# define vportBAD_FLOAT_HDR                             vTRUE
# define vportBAD_SIGNED                                vTRUE
# define vportBAD_VOLATILE                              vTRUE
# ifndef __cplusplus
#  define vportBAD_CONST                                vTRUE
#  define vportBAD_STDARG_HDR                           vTRUE
# endif
#elif (__CODECENTER__)  /* CenterLine's CodeCenter 4.0.4 */
# define vportBAD_CONST                                 vTRUE
# define vportBAD_FLOAT_HDR                             vTRUE
# define vportBAD_SIGNED                                vTRUE
# define vportBAD_VOLATILE                              vTRUE
#elif (__CLCC__)
# ifdef __cplusplus     /* CenterLine's C++ compiler */
#  define vportBAD_ADDRESS_OF_BOUND_FUNCTION            vTRUE
#  define vportBAD_SIGNED                               vTRUE
#  define vportBAD_SYS_SELECT_HDR                       vTRUE
#  define vportBAD_TM_ZONE                              vTRUE
#  define vportBAD_ULIMIT_HDR                           vTRUE
#  define vportBAD_UNION_WAIT                           vTRUE
#  define vportBAD_VOLATILE                             vTRUE
#  define vportBAD_WAIT3                                vTRUE
#  define vportNEED_GETHOSTNAME_PROTO                   vTRUE
# else                  /* CenterLine's C compiler */
#  ifndef __STDC__      /* -traditional */
#   define vportBAD_CPP_POUND                           vTRUE
#   define vportBAD_FLOAT_HDR                           vTRUE
#   define vportBAD_SIGNED                              vTRUE
#   define vportBAD_STDARG_HDR                          vTRUE
#   define vportBAD_VOLATILE                            vTRUE
#  endif
# endif
#elif (__lucid)         /* Lucid C/C++ compiler */
# define vportBAD_SYS_SELECT_HDR                        vTRUE
# define vportBAD_ULIMIT_HDR                            vTRUE
# define vportNEED_GETHOSTNAME_PROTO                    vTRUE
#elif (__GNUC__)
# define vportNEED_GETHOSTNAME_PROTO                    vTRUE
# if (vportPRE_SUN_OS_5_0)
#  define vportBAD_SYS_SELECT_HDR                       vTRUE
#  define vportBAD_ULIMIT_HDR                           vTRUE
#  define vportCPLUSPLUS_EXCEPTIONS                     vFALSE
#  define vportHAS_STRCASECMP                   vTRUE /* !!! BAD_STRCASECMP */
#  define vportHAS_STRNCASECMP                  vTRUE /* !!! BAD_STRNCASECMP */
#  define vportINLINE_DECL                              inline
#  define vportINLINE_EXTERN                            extern inline
#  define vportINLINE_OUTLINE                           
#  define vportNEED_ACCEPT_PROTO                        vTRUE
#  define vportNEED_BIND_PROTO                          vTRUE
#  define vportNEED_BZERO_PROTO                         vTRUE
#  define vportNEED_CLOCKS_PER_SEC                      vTRUE
#  define vportNEED_CLOCK_PROTO                         vTRUE
#  define vportNEED_CONNECT_PROTO                       vTRUE
#  define vportNEED_ECVT_PROTO                          vTRUE
#  define vportNEED_ENDGRENT_PROTO                      vTRUE
#  define vportNEED_ENDPWENT_PROTO                      vTRUE
#  define vportNEED_FCLOSE_PROTO                        vTRUE
#  define vportNEED_FFLUSH_PROTO                        vTRUE
#  define vportNEED_FGETC_PROTO                         vTRUE
#  define vportNEED_FPRINTF_PROTO                       vTRUE
#  define vportNEED_FPUTC_PROTO                         vTRUE
#  define vportNEED_FPUTS_PROTO                         vTRUE
#  define vportNEED_FREAD_PROTO                         vTRUE
#  define vportNEED_FSCANF_PROTO                        vTRUE
#  define vportNEED_FSEEK_PROTO                         vTRUE
#  define vportNEED_FWRITE_PROTO                        vTRUE
#  define vportNEED_GETDTABLESIZE_PROTO                 vTRUE
#  define vportNEED_GETPEERNAME_PROTO                   vTRUE
#  define vportNEED_GETPID_PROTO                        vTRUE
#  define vportNEED_GETSOCKNAME_PROTO                   vTRUE
#  define vportNEED_GETSOCKOPT_PROTO                    vTRUE
#  define vportNEED_GETTIMEOFDAY_PROTO                  vTRUE
#  define vportNEED_GETWD_PROTO                         vTRUE
#  define vportNEED_IOCTL_PROTO                         vTRUE
#  define vportNEED_LISTEN_PROTO                        vTRUE
#  define vportNEED_LOCKF_PROTO                         vTRUE
#  define vportNEED_LSTAT_PROTO                         vTRUE
#  define vportNEED_MEMORY_HDR                          vTRUE
#  define vportNEED_PCLOSE_PROTO                        vTRUE
#  define vportNEED_PERROR_PROTO                        vTRUE
#  define vportNEED_PRINTF_PROTO                        vTRUE
#  define vportNEED_PUTS_PROTO                          vTRUE
#  define vportNEED_RANDOM_PROTO                        vTRUE
#  define vportNEED_READLINK_PROTO                      vTRUE
#  define vportNEED_RECVFROM_PROTO                      vTRUE
#  define vportNEED_RECVMSG_PROTO                       vTRUE
#  define vportNEED_RECV_PROTO                          vTRUE
#  define vportNEED_REMOVE_PROTO                        vTRUE
#  define vportNEED_RENAME_PROTO                        vTRUE
#  define vportNEED_REWIND_PROTO                        vTRUE
#  define vportNEED_SELECT_PROTO                        vTRUE
#  define vportNEED_SEND_PROTO                          vTRUE
#  define vportNEED_SENDMSG_PROTO                       vTRUE
#  define vportNEED_SENDTO_PROTO                        vTRUE
#  define vportNEED_SETSOCKOPT_PROTO                    vTRUE
#  define vportNEED_SHMAT_PROTO                         vTRUE
#  define vportNEED_SHMCTL_PROTO                        vTRUE
#  define vportNEED_SHMDT_PROTO                         vTRUE
#  define vportNEED_SHMGET_PROTO                        vTRUE
#  define vportNEED_SOCKET_PROTO                        vTRUE
#  define vportNEED_SRANDOM_PROTO                       vTRUE
#  define vportNEED_STRCASECMP_PROTO                    vTRUE
#  define vportNEED_STRNCASECMP_PROTO                   vTRUE
#  define vportNEED_SYMLINK_PROTO                       vTRUE
#  define vportNEED_SYSTEM_PROTO                        vTRUE
#  define vportNEED_TIME_PROTO                          vTRUE
#  define vportNEED_TOLOWER_PROTO                       vTRUE
#  define vportNEED_TOUPPER_PROTO                       vTRUE
#  define vportNEED_UNGETC_PROTO                        vTRUE
#  define vportNEED_VFPRINTF_PROTO                      vTRUE
#  define vportNEED_VPRINTF_PROTO                       vTRUE
#  define vportNEED__FILBUF_PROTO                       vTRUE
#  define vportNEED__FLSBUF_PROTO                       vTRUE
#  define vportVSTDLIB_RETURN_INT_INSTEAD_OF_VOID       vTRUE
#  define vportVSTDLIB_USE_CHAR_PTR_INSTEAD_OF_VOID_PTR vTRUE
#  ifndef _G_LIB_VERSION
    /* GNU libg++ includes have their own protos which aren't quite correct */
#   define vportNEED_SSCANF_PROTO               (!defined(_G_LIB_VERSION))
#   define vportNEED_VSPRINTF_PROTO             (!defined(_G_LIB_VERSION))
#  endif
# else  /* gcc on Solaris */
#  define vportBAD_GETDTABLESIZE                        vTRUE
#  define vportBAD_RANDOM                               vTRUE
#  define vportBAD_SRANDOM                              vTRUE
#  define vportBAD_TM_ZONE                              vTRUE
#  define vportBAD_UNION_WAIT                           vTRUE
#  define vportBAD_WAIT3                                vTRUE
#  define vportNEED_SYS_FCNTL_HDR                       vTRUE
# endif /* #if (vportPRE_SUN_OS_5_0) #else */
#else   /* Sun acc and Sun CC */
# define vportBAD_BOOL                                  vTRUE
# define vportINLINE_DECL                               inline
# define vportNEED_GETHOSTNAME_PROTO                    vTRUE
# if (vportPRE_SUN_OS_5_0)      /* SunOS 4.x */
#  define vportBAD_SYS_SELECT_HDR                       vTRUE
#  define vportBAD_ULIMIT_HDR                           vTRUE
#  ifdef __cplusplus
#   define vportSIG_PF                                  SIG_PF
#  else
#   define vportBAD_SIZE_T                              vTRUE
#   define vportNEED_FFLUSH_PROTO                       vTRUE
#  endif
# else                          /* Solaris 2.x */
#  define vportBAD_GETDTABLESIZE                        vTRUE
#  define vportBAD_RANDOM                               vTRUE
#  define vportBAD_SRANDOM                              vTRUE
#  define vportBAD_TM_ZONE                              vTRUE
#  define vportBAD_UNION_WAIT                           vTRUE
#  define vportBAD_WAIT3                                vTRUE
#  define vportNEED_SYS_FCNTL_HDR                       vTRUE
#  define vportDONT_DEFINE_NULL_HEADER                  vTRUE
# endif
#endif /* #if (__OBJECTCENTER__) #elif (__CODECENTER__) #elif ... */
#endif /* #if (sun) */

#if (vportPRE_SUN_OS_5_0)      /* SunOS 4.x */
# if (vportI18N)
#  define vportUSE_SUN_MLE                              vTRUE
# endif
#endif

#if (sysV68)
#endif

#if (sysV88)
#endif

#if (ultrix)
#define vportBAD_LIBC_HDR               vTRUE
#define vportNEED_RANDOM_PROTO          vTRUE
#define vportNEED_SRANDOM_PROTO         vTRUE
#if (__GNUC__)
#define vportBAD_ATEXIT                 vTRUE
#define vportBAD_SYS_MNTENT_HDR         vTRUE
#define vportBAD_SYS_SELECT_HDR         vTRUE
/** xdpyinfo claims that DEC has MIT_SHM, but XShmGetImage is a */
/** sure-fire way to crash any program.  !!! FIXME */
#define vportBAD_X_SHM                  vTRUE
#define vportNEED_ACCEPT_PROTO          vTRUE
#define vportNEED_ATOI_PROTO            vTRUE
#define vportNEED_BIND_PROTO            vTRUE
#define vportNEED_BZERO_PROTO           vTRUE
#define vportNEED_CALLOC_PROTO          vTRUE
#define vportNEED_CLOSE_PROTO           vTRUE
#define vportNEED_CONNECT_PROTO         vTRUE
#define vportNEED_CTIME_PROTO           vTRUE
#define vportNEED_ECVT_PROTO            vTRUE
#define vportNEED_ENDGRENT_PROTO        vTRUE
#define vportNEED_ENDPWENT_PROTO        vTRUE
#define vportNEED_GETDTABLESIZE_PROTO   vTRUE
#define vportNEED_GETHOSTNAME_PROTO     vTRUE
#define vportNEED_GETSOCKNAME_PROTO     vTRUE
#define vportNEED_GETSOCKOPT_PROTO      vTRUE
#define vportNEED_GETTIMEOFDAY_PROTO    vTRUE
#define vportNEED_GETWD_PROTO           vTRUE
#define vportNEED_IOCTL_PROTO           vTRUE
#define vportNEED_LISTEN_PROTO          vTRUE
#define vportNEED_LOCKF_PROTO           vTRUE
#define vportNEED_LSTAT_PROTO           vTRUE
#define vportNEED_READLINK_PROTO        vTRUE
#define vportNEED_RECVFROM_PROTO        vTRUE
#define vportNEED_SELECT_PROTO          vTRUE
#define vportNEED_SENDTO_PROTO          vTRUE
#define vportNEED_SETSOCKOPT_PROTO      vTRUE
#define vportNEED_SOCKET_PROTO          vTRUE
#define vportNEED_STRERROR_PROTO        vTRUE
#define vportNEED_SYMLINK_PROTO         vTRUE
#define vportNEED_TIME_PROTO            vTRUE
#else
/* DEC c89 */
#endif /* (__GNUC__) */
#endif /* (ultrix) */

/* Unixware */
#if (unix && i386 && __USLC__ && !_SEQUENT_ && !ix386 && !__NCR && !__linux__ && !sun && !__HIGHC__ && !__FreeBSD__)
#define vportBAD_GETWD                                  vTRUE
#define vportBAD_LIBC_HDR                               vTRUE
#define vportBAD_TM_ZONE                                vTRUE
#define vportBAD_UNION_WAIT                             vTRUE
#define vportBAD_WAIT3                                  vTRUE
#endif

/* VMS - including VAX and AXP (alpha) OpenVMS */
#if vportOS_VMS
#include <vportvms.h>
#endif

#if (__WATCOMC__)
#define vportBAD_ARPA_INET_HDR                          vTRUE
#define vportBAD_ATEXIT                                 vTRUE
#define vportBAD_BSD_ARPA_INET_HDR                      vTRUE
#define vportBAD_BSD_NETINET_IN_HDR                     vTRUE
#define vportBAD_BSD_SYS_TYPES_HDR                      vTRUE
#define vportBAD_CHOWN                                  vTRUE
#define vportBAD_DIRENT_HDR                             vTRUE
#define vportBAD_DOSFINDCLOSE                           vTRUE
#define vportBAD_DOSFINDFIRST                           vTRUE
#define vportBAD_DOSFINDNEXT                            vTRUE
#define vportBAD_DOSSETFILELOCKS                        vTRUE
#define vportBAD_ENDGRENT                               vTRUE
#define vportBAD_ENDPWENT                               vTRUE
#define vportBAD_EXECV                                  vTRUE
#define vportBAD_FFLUSH                                 vTRUE
#define vportBAD_FORK                                   vTRUE
#define vportBAD_GETDTABLESIZE                          vTRUE
#define vportBAD_GETEGID                                vTRUE
#define vportBAD_GETEUID                                vTRUE
#define vportBAD_GETGID                                 vTRUE
#define vportBAD_GETGRGID                               vTRUE
#define vportBAD_GETHOSTNAME                            vTRUE
#define vportBAD_GETPWUID                               vTRUE
#define vportBAD_GETTIMEOFDAY                           vTRUE
#define vportBAD_GETUID                                 vTRUE
#define vportBAD_GETWD                                  vTRUE
#define vportBAD_GRP_HDR                                vTRUE
#define vportBAD_HTONL                                  vTRUE
#define vportBAD_LIBC_HDR                               vTRUE
#define vportBAD_LOCKF                                  vTRUE
#define vportBAD_LSTAT                                  vTRUE
#define vportBAD_NETDB_HDR                              vTRUE
#define vportBAD_NETINET_IN_HDR                         vTRUE
#define vportBAD_NTOHL                                  vTRUE
#define vportBAD_PATHCONF                               vTRUE
#define vportBAD_PWD_HDR                                vTRUE
#define vportBAD_RANDOM                                 vTRUE
#define vportBAD_READLINK                               vTRUE
#define vportBAD_REWINDDIR                              vTRUE
#define vportBAD_SELECT                                 vTRUE
#define vportBAD_SETLOCALE                              vTRUE
#define vportBAD_SOCKET_CLOSE                           vTRUE
#define vportBAD_SOCKET_IOCTL                           vTRUE
#define vportBAD_SOCKET_READ                            vTRUE
#define vportBAD_SOCKET_WRITE                           vTRUE
#define vportBAD_SRANDOM                                vTRUE
#define vportBAD_STDARG_HDR                             vTRUE
#define vportBAD_STDIO_HANDLES                          vTRUE
#define vportBAD_SYMLINK                                vTRUE
#define vportBAD_SYSCONF                                vTRUE
#define vportBAD_SYS_DIRENT_HDR                         vTRUE
#define vportBAD_SYS_DIR_HDR                            vTRUE
#define vportBAD_SYS_FILE_HDR                           vTRUE
#define vportBAD_SYS_FILIO_HDR                          vTRUE
#define vportBAD_SYS_IOCTL_HDR                          vTRUE
#define vportBAD_SYS_IPC_HDR                            vTRUE
#define vportBAD_SYSLOG                                 vTRUE
#define vportBAD_SYS_PARAM_HDR                          vTRUE
#define vportBAD_SYS_RESOURCE_HDR                       vTRUE
#define vportBAD_SYS_SELECT_HDR                         vTRUE
#define vportBAD_SYS_SHM_HDR                            vTRUE
#define vportBAD_SYS_SOCKET_HDR                         vTRUE
#define vportBAD_SYS_TERMIO_HDR                         vTRUE
#define vportBAD_SYS_TIMES_HDR                          vTRUE
#define vportBAD_SYS_TIME_HDR                           vTRUE
#define vportBAD_SYS_TYPES_HDR                          vTRUE
#define vportBAD_SYS_UIO_HDR                            vTRUE
#define vportBAD_SYS_UN_HDR                             vTRUE
#define vportBAD_SYS_UTIME_HDR                          vTRUE
#define vportBAD_SYS_UTSNAME_HDR                        vTRUE
#define vportBAD_SYS_WAIT_HDR                           vTRUE
#define vportBAD_TM_ZONE                                vTRUE
#define vportBAD_TYPES_HDR                              vTRUE
#define vportBAD_ULIMIT                                 vTRUE
#define vportBAD_ULIMIT_HDR                             vTRUE
#define vportBAD_UNISTD_HDR                             vTRUE
#define vportBAD_UNIX_DOMAIN_SOCKETS                    vTRUE
#define vportBAD_UTIME_HDR                              vTRUE
#define vportDLL_WIN                                    vTRUE
#define vportHAS_OPEN_DENY                              vTRUE
#define vportHAS_WINMAIN                                vTRUE
#define vportMKDIR_ASSUMES_MODE                         vTRUE
#define vportNEED_DOS_FILESYSTEM                        vTRUE
#define vportNEED_FDOPEN_PROTO                          vTRUE
#define vportNEED_GID_T_TYPE                            vTRUE
#define vportNEED_GROUP_STRUCT                          vTRUE
#define vportNEED_HTONL_PROTO                           vTRUE
#define vportNEED_MODE_T_TYPE                           vTRUE
#define vportNEED_NTOHL_PROTO                           vTRUE
#define vportNEED_PASSWD_STRUCT                         vTRUE
#define vportNEED_POPEN_PROTO                           vTRUE
#define vportNEED_STRERROR_PROTO                        vTRUE
#define vportNEED_UID_T_TYPE                            vTRUE
#define vportNEED_WATCOM_THUNK                          vTRUE
#define vportUNC_PATHNAMES                              vTRUE
#define vportUSES_FONT_PSIZE                            vTRUE
#define vportVA_LIST_WAS_ARRAY                          vTRUE
#define vportWINDOWS_SOCKETS                            vTRUE
#endif /* __WATCOMC__ */


/*
 * Define default values for easy porting
 */

#if (vportVISIX)
#ifndef  vportDONT_MACRO_CPLUSPLUS_KEYWORDS
# define vportDONT_MACRO_CPLUSPLUS_KEYWORDS             vFALSE
#endif
#if (vportPEEK)
# ifndef  vprefSetArgs
#  define vprefSetArgs(a,b)                             _visixStartup(a,b)
# endif
# ifndef  vstartup
#  define vstartup(a,b)                                 _visixStartup(a,b)
# endif
#endif
#ifndef  vlafENABLE_MAC
# define vlafENABLE_MAC                                 vTRUE
#endif
#endif

#ifndef vportNAN
#define vportNAN                                        (acos(2.0))
#endif

#ifndef vportC_STRUCT
#define vportC_STRUCT
#endif

#ifndef vportALIGNMENT_BYTES            
#define vportALIGNMENT_BYTES                            4
#endif

#ifndef vportMODE_MASK
#define vportMODE_MASK                                  (~0)
#endif

#if (!defined(vportNEED_UNIX_FILESYSTEM) && !defined(vportNEED_DOS_FILESYSTEM) && !defined(vportNEED_HPFS_FILESYSTEM) && !defined(vportNEED_VMS_FILESYSTEM) && !defined(vportNEED_MAC_FILESYSTEM))
#define vportNEED_UNIX_FILESYSTEM                       vTRUE
#endif

#if (vportBAD_STDIO_HANDLES)
#ifndef vportBAD_STDIO_OUTPUT
#define vportBAD_STDIO_OUTPUT                           vTRUE
#endif
#endif

#if (vportI18N)
#ifndef  vportVCHAR_CODESET
# define vportVCHAR_CODESET                             vportCODESET_UNICODE
#endif
#define vportUSE_MS_WINDOWS_IME                         vportWIN_MS_WINDOWS
#endif

#if (vportOS_WINDOWS)
# ifndef  vportVCHAR_CODESET
#  define vportVCHAR_CODESET                            vportCODESET_WINDOWS
# endif
# ifndef  vportLITERAL_CODESET
#  define vportLITERAL_CODESET                          vportCODESET_WINDOWS
# endif
#elif (vportOS_MAC)
# ifndef  vportVCHAR_CODESET
#  define vportVCHAR_CODESET                            vportCODESET_MACINTOSH
# endif
# ifndef  vportLITERAL_CODESET
#  define vportLITERAL_CODESET                          vportCODESET_MACINTOSH
# endif
#else
# ifndef  vportVCHAR_CODESET
#  define vportVCHAR_CODESET                            vportCODESET_LATIN_1
# endif
# ifndef  vportLITERAL_CODESET
#  define vportLITERAL_CODESET                          vportCODESET_LATIN_1
# endif
#endif

#ifndef vportWIN_RUNNER
#define vportWIN_RUNNER                                 vportWIN_MS_WINDOWS
#endif

#ifndef vportX_RUNNER
#define vportX_RUNNER                                   vportWIN_X11
#endif

#ifndef vportTEST
#define vportTEST                                       vFALSE
#endif

#ifndef vportNATIVE_MENUBAR
#define vportNATIVE_MENUBAR                             vportWIN_MS_WINDOWS
#endif

#ifndef vportOLE
#define vportOLE                                        vportOS_WIN32S
#endif

#ifdef vportOLE
/*
 * we use c-style OLE definitions 
 */
#ifndef CINTERFACE
#define CINTERFACE
#endif
#ifndef COBJMACROS
#define COBJMACROS                                      vTRUE
#endif
#endif

/*
 * select(maxfd,(vportFD_SET_CAST)rfds,(vportFD_SET_CAST)wfds,....
 */
#ifndef vportFD_SET_CAST
#define vportFD_SET_CAST                                fd_set*
#endif

/*
 * wait3(&stat_loc, WNOHANG, (vportRUSAGE_CAST)NULL)
 */
#ifndef vportRUSAGE_CAST
#define vportRUSAGE_CAST                                struct rusage*
#endif

#ifndef vportRIGHT_SHIFT_ARITHMETIC
#define vportRIGHT_SHIFT_ARITHMETIC                     (((-2)>>1)==((-2)/2))
#endif

#ifndef vportBAD_SYS_DIR_HDR
#define vportBAD_SYS_DIR_HDR                            (!vportBAD_DIRENT_HDR)
#endif

#ifndef vportBAD_CPP_POUND
#define vportBAD_CPP_POUND      (vportBAD_CPP_POUND_POUND && (__STDC__ < 1))
#endif

#if (vportBAD_CPP_POUND)
#define vportQUOTE(s) "s"
#else
#define vportQUOTE(s) #s
#endif

#ifndef vportSIG_PF
typedef void (*vportSIG_PF)(int);
#define vportSIG_PF_CAST
#else
#define vportSIG_PF_CAST                                (vportSIG_PF)
#endif

#ifndef vportIMPORT
#define vportIMPORT                                     extern
#endif

#ifndef vportEXPORT
#define vportEXPORT
#endif

#ifndef vportIMPORT_CONST
#define vportIMPORT_CONST                               extern
#endif

#ifndef vportEXPORT_CONST
#define vportEXPORT_CONST
#endif

#ifndef vportDECL
#define vportDECL                                       
#endif

#ifndef vportDLL_LINK
#define vportDLL_LINK                                   
#endif

#ifndef vportDLL_CLASS_LINK
#define vportDLL_CLASS_LINK                                     
#endif

#ifndef vportDLL_CLASS_DEFINE
#define vportDLL_CLASS_DEFINE
#endif

#ifndef vportLINK
# if (vportGALAXY_LIB_MEMBER)
#  define vportLINK
# else
#  define vportLINK                                     vportDLL_LINK
# endif
#endif

#ifndef vportCLASS_LINK
# if (vportGALAXY_LIB_MEMBER)
#  define vportCLASS_LINK
# else
#  define vportCLASS_LINK                               vportDLL_CLASS_LINK
# endif
#endif

#ifndef vportCLASS_DEFINE
# if (vportGALAXY_LIB_MEMBER)
#  define vportCLASS_DEFINE
# else
#  define vportCLASS_DEFINE                             vportDLL_CLASS_DEFINE
# endif
#endif

#ifndef vgalaxyLINK
#define vgalaxyLINK                                     vportLINK
#endif

#ifndef vdasLINK
#define vdasLINK                                        vportDLL_LINK
#else
#define vdasLIB_MEMBER                                  vTRUE
#endif

#ifndef vdasCLASS_LINK
#define vdasCLASS_LINK                                  vdasLINK
#endif

#ifndef vhgLINK
#define vhgLINK                                         vportDLL_LINK
#else
#define vhgLIB_MEMBER                                   vTRUE
#endif

#ifndef vhgCLASS_LINK
#define vhgCLASS_LINK                                   vhgLINK
#endif

#ifndef vmicrunLINK
#define vmicrunLINK                                     vportDLL_LINK
#endif

#ifndef vdbLINK
#define vdbLINK                                         vportDLL_LINK
#endif

#ifndef vdbCLASS_LINK
#define vdbCLASS_LINK                                   vdbLINK
#endif

#ifndef vsprvwLINK
#define vsprvwLINK                                      vportDLL_LINK
#endif

#ifndef vtblvLINK
#define vtblvLINK                                       vportDLL_LINK
#endif

#ifndef vreLINK
#define vreLINK                                         vportDLL_LINK
#endif

#ifndef vsourceLINK
#define vsourceLINK                                     vportDLL_LINK
#endif

#ifndef vlogkernelLINK
#define vlogkernelLINK                                  vportDLL_LINK
#endif

#ifndef vlogext1LINK
#define vlogext1LINK                                    vportDLL_LINK
#endif

#ifndef vhexLINK
#define vhexLINK                                        vportDLL_LINK
#endif

#ifndef vjavaLINK
#define vjavaLINK                                       vportDLL_LINK
#endif

#ifndef vjavacLINK
#define vjavacLINK                                      vportDLL_LINK
#endif

#ifndef v11cLINK
#define v11cLINK                                        vportDLL_LINK
#endif

#ifndef vjavastubLINK
#define vjavastubLINK                                   vportDLL_LINK
#endif

#ifndef vsoundLINK
#define vsoundLINK                                      vportDLL_LINK
#endif

#ifndef vcodetextLINK
#define vcodetextLINK                                   vportDLL_LINK
#endif

#ifndef v11jsLINK
#define v11jsLINK                                       vportDLL_LINK
#endif

#ifndef v11dbLINK
#define v11dbLINK                                       vportDLL_LINK
#endif

#ifndef v11LINK
#define v11LINK                                         vportDLL_LINK
#endif

#ifndef vportSYSLINK
#define vportSYSLINK
#endif

#ifndef vportTHREAD_LOCAL
#define vportTHREAD_LOCAL
#endif

#ifndef vport__IMPORT
#define vport__IMPORT
#endif

#ifndef vportHAS_LONG_LONG
#define vportHAS_LONG_LONG                              __GNUC__
#endif

#ifndef vportUSE_LONG_LONG
#define vportUSE_LONG_LONG                              vFALSE
#endif

#if (!defined(vportINT64) && vportHAS_LONG_LONG)
#define vportINT64                                      long long
#endif

#ifndef vportSYSTEM_HEADERS_NEED_C_LINKAGE_IN_CPLUSPLUS
#define vportSYSTEM_HEADERS_NEED_C_LINKAGE_IN_CPLUSPLUS vFALSE
#endif

#ifndef vportDONT_MACRO_CPLUSPLUS_KEYWORDS
#define vportDONT_MACRO_CPLUSPLUS_KEYWORDS              vTRUE
#endif

#ifndef vportDECLSPEC_THREAD
#define vportDECLSPEC_THREAD
#endif

#ifndef vportTHREAD
#define vportTHREAD
#endif

#ifndef vportMTHREAD_LOCAL
#define vportMTHREAD_LOCAL(t)                           t
#endif

#ifndef vportREENTRANT
#define vportREENTRANT                                  vTRUE
#endif

#ifndef vportINSTALL_ENVIRONMENT_VARIABLE
#define vportINSTALL_ENVIRONMENT_VARIABLE "GALAXYHOME"
#endif

#ifndef vportBAD_CXX_DYNAMIC_CAST
#define vportBAD_CXX_DYNAMIC_CAST                       vTRUE
#endif

/*
 * Add in C++ compatability
 */

#ifndef vportCPLUSPLUS_SOURCE
#define vportCPLUSPLUS_SOURCE                           vFALSE
#endif

#ifndef vportCPLUSPLUS_UNTRANSLATED_SOURCE
#define vportCPLUSPLUS_UNTRANSLATED_SOURCE              vportCPLUSPLUS_SOURCE
#endif

#ifndef vportCPLUSPLUS_BALANCE
#define vportCPLUSPLUS_BALANCE                          vportCPLUSPLUS_SOURCE
#endif

#ifndef vportCPLUSPLUS_EXCEPTIONS
#define vportCPLUSPLUS_EXCEPTIONS                       vportCPLUSPLUS_SOURCE
#endif

#define vportBEGIN_MUST_BE_MACRO
#define vportEND_MUST_BE_MACRO

#define vportALIAS(derived, base)       

#define vportREGISTER_DRIVER(name)              
#define vportSET_DRIVER_FUNCTION(name, func)            func
#define vportSET_DRIVER_VARIABLE(name, var)             var

#ifndef vportWANT_INLINES
#define vportWANT_INLINES                               vTRUE
#endif

#ifndef vportWANT_VIRTUAL_INLINES
#define vportWANT_VIRTUAL_INLINES                       vFALSE
#endif

#ifndef vportWANT_PRIVATE_INLINES
#define vportWANT_PRIVATE_INLINES                       vportWANT_INLINES
#endif

#ifndef vportWANT_PUBLIC_INLINES
#define vportWANT_PUBLIC_INLINES                        vportWANT_INLINES
#endif

#ifndef vportINLINE_DECL
#define vportINLINE_DECL
#endif

#ifndef vportINLINE_EXTERN
#define vportINLINE_EXTERN                              inline
#endif

#ifndef vportINLINE_OUTLINE
#define vportINLINE_OUTLINE                             
#endif

#ifndef vportGALAXY_C_COMPAT
#define vportGALAXY_C_COMPAT                            vTRUE
#endif

#if (!vportCPLUSPLUS_SOURCE)
#define vportBASE_OBJECT(d,b)                           (&(d)->b)
#else
#define vportBASE_OBJECT(d,b)                           (d)
#endif

#if (!vportCPLUSPLUS_SOURCE || vportBAD_CXX_DYNAMIC_CAST)
#define vportCXX_DYNAMIC_CAST(T)                        (T)
#else
#define vportCXX_DYNAMIC_CAST(T)                        dynamic_cast<T>
#endif

#if (!vportCPLUSPLUS_SOURCE || vportBAD_CXX_STATIC_CAST)
#define vportCXX_STATIC_CAST(T)                         (T)
#else
#define vportCXX_STATIC_CAST(T)                         static_cast<T>
#endif

#if (!vportCPLUSPLUS_SOURCE || vportBAD_CXX_CONST_CAST)
#define vportCXX_CONST_CAST(T)                          (T)
#else
#define vportCXX_CONST_CAST(T)                          const_cast<T>
#endif

#if (!vportCPLUSPLUS_SOURCE || vportBAD_CXX_REINTERPRET_CAST)
#define vportCXX_REINTERPRET_CAST(T)                    (T)
#else
#define vportCXX_REINTERPRET_CAST(T)                    reinterpret_cast<T>
#endif


#ifdef __cplusplus

#define vportBEGIN_CPLUSPLUS_EXTERN_C                   extern "C" {
#define vportEND_CPLUSPLUS_EXTERN_C                     }

#if (vportSYSTEM_HEADERS_NEED_C_LINKAGE_IN_CPLUSPLUS)
# define vportBEGIN_CPLUSPLUS_HEADER_PROTECTION         extern "C" {
# define vportEND_CPLUSPLUS_HEADER_PROTECTION           }
#else
# define vportBEGIN_CPLUSPLUS_HEADER_PROTECTION
# define vportEND_CPLUSPLUS_HEADER_PROTECTION
#endif

#else /* #ifdef __cplusplus */

#define vportBEGIN_CPLUSPLUS_EXTERN_C
#define vportEND_CPLUSPLUS_EXTERN_C
#define vportBEGIN_CPLUSPLUS_HEADER_PROTECTION
#define vportEND_CPLUSPLUS_HEADER_PROTECTION

#define vportBREAK___declspec   error KEYWORD___declspec is reserved{)
#define vportBREAK_asm          error KEYWORD_asm is reserved{)
#define vportBREAK_bool         error KEYWORD_bool is reserved{)
#define vportBREAK_catch        error KEYWORD_catch is reserved{)
#define vportBREAK_class        error KEYWORD_class is reserved{)
#define vportBREAK_delete       error KEYWORD_delete is reserved{)
#define vportBREAK_except       error KEYWORD_except is reserved{)
#define vportBREAK_explicit     error KEYWORD_explicit is reserved{)
#define vportBREAK_friend       error KEYWORD_friend is reserved{)
#define vportBREAK_inline       error KEYWORD_inline is reserved{)
#define vportBREAK_interface    error KEYWORD_interface is reserved{)
#define vportBREAK_mutable      error KEYWORD_mutable is reserved{)
#define vportBREAK_new          error KEYWORD_new is reserved{)
#define vportBREAK_operator     error KEYWORD_operator is reserved{)
#define vportBREAK_private      error KEYWORD_private is reserved{)
#define vportBREAK_protected    error KEYWORD_protected is reserved{)
#define vportBREAK_public       error KEYWORD_public is reserved{)
#define vportBREAK_template     error KEYWORD_template is reserved{)
#define vportBREAK_this         error KEYWORD_this is reserved{)
#define vportBREAK_throw        error KEYWORD_throw is reserved{)
#define vportBREAK_try          error KEYWORD_try is reserved{)
#define vportBREAK_typename     error KEYWORD_typename is reserved{)
#define vportBREAK_virtual      error KEYWORD_virtual is reserved{)

#if (!vportDONT_MACRO_CPLUSPLUS_KEYWORDS)

/* Define C++ reserved words to a syntax error in C */

#if ((!vportOS_WIN32S) && (!vportDLL_CFM))
#define __declspec              vportBREAK___declspec
#endif
#ifndef asm
#define asm                     vportBREAK_asm
#endif
#if (!vportOS_WIN32S)
#define bool                    vportBREAK_bool
#endif
#define catch                   vportBREAK_catch
#define class                   vportBREAK_class
#define delete                  vportBREAK_delete
#if (!__BORLANDC__)
#if (!vportDONT_BREAK_EXCEPT)
#define except                  vportBREAK_except
#endif
#define explicit                vportBREAK_explicit
#endif
#define friend                  vportBREAK_friend
#define inline                  vportBREAK_inline
#if (!vportDONT_BREAK_INTERFACE)
#define interface               vportBREAK_interface
#endif
#if (!__BORLANDC__)
#define mutable                 vportBREAK_mutable
#endif
#define new                     vportBREAK_new
#define operator                vportBREAK_operator
#define private                 vportBREAK_private
#define protected               vportBREAK_protected
#define public                  vportBREAK_public
#define template                vportBREAK_template
#define this                    vportBREAK_this
#define throw                   vportBREAK_throw
#if (!defined(try) && !__BORLANDC__)
#define try                     vportBREAK_try
#endif
#if (!__BORLANDC__)
#define typename                vportBREAK_typename
#endif
#define virtual                 vportBREAK_virtual

#endif

#endif /* #ifdef __cplusplus #else */

/*
 * Handle compilers that are lacking
 */

#if (vportBAD_CONST)
#ifndef const
#define const
#endif
#endif

#if (vportBAD_SIGNED)
#ifndef signed
#define signed
#endif
#endif

#if (vportBAD_VOLATILE)
#ifndef volatile
#define volatile
#endif
#endif

/*
 * set up quick header re-inclusion
 */

#ifndef vportNULL_HEADER
# if (!vportDONT_DEFINE_NULL_HEADER)
#  if (vportOS_UNIX)
#   define vportNULL_HEADER                     "/dev/null"
#  elif (vportOS_WINDOWS)
#   define vportNULL_HEADER                     "NUL"
#  endif
# endif
#endif

#ifdef   vportNULL_HEADER
# undef  vportHEADER
# define vportHEADER vportNULL_HEADER
#endif

#endif /* #ifndef vportINCLUDED */


/*
 * Local Variables:
 * c-argdecl-indent:4
 * c-brace-imaginary-offset:0
 * c-brace-offset:-4
 * c-continued-brace-offset:0
 * c-continued-statement-offset:4
 * c-extra-brace-offset:0
 * c-file-offsets:((block-open . -))
 * c-file-style:"BSD"
 * c-indent-level:4
 * c-label-offset:-4
 * indent-tabs-mode:nil
 * tab-width:4
 * End:
 */

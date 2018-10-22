/* $Id: vthreadsys.h,v 1.4 1997/09/11 23:28:40 robert Exp $ */

/************************************************************

    vthreadsys.h

    Platform-specific vthread functions.

    (c) Copyright 1996 Visix Software Inc.
    All rights reserved

************************************************************/

#ifndef vthreadsysINCLUDED
#define vthreadsysINCLUDED 1

#ifndef  vportHEADER
#include <vport.h>
#endif

#ifndef  vstdINCLUDED
#include vstdHEADER
#endif

#ifndef  vthreadINCLUDED
#include vthreadHEADER
#endif

/*
 * Include platform-specific header files. These are required to provide
 * the specific types of the native threads.
 */
#if (vportOS_MAC)
# include <Threads.h>
# include <Timer.h>
# if (vportUSE_PROFILER)
#   include <Profiler.h>
# endif
#endif

#if (vportOS_OS2)
# ifndef  vos2INCLUDED
#  include vos2HEADER
# endif
#endif

#if (vportUSE_DCE_THREADS)
# if (_AIX && !vportDONT_MACRO_CPLUSPLUS_KEYWORDS && !defined(__cplusplus))
#  undef except
# endif
# include <pthread.h>
#endif

#if (vportUSE_POSIX_THREADS)
# include <pthread.h>
# include <sched.h>
#endif

#if (vportUSE_POSIX_DRAFT7_THREADS)
# include <pthread.h>
#endif

#if (vportUSE_POSIX_DRAFT8_THREADS)
# include <pthread.h>
#endif

#if (vportOS_UNIX_SOLARIS)
# include <thread.h>
#endif

#if (vportOS_WIN32S)
# include <process.h>
# include vmswhdrsHEADER
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C

/*===========================================================================*
 * * * * * * * * * * *   PUBLIC  FUNCTION  PROTOTYPES  * * * * * * * * * * * *
 *===========================================================================*/

#if (vportOS_WINDOWS)

HANDLE
vthreadsysGetWin32Thread (
   vthread                 *thread
   );

#elif (vportUSE_DCE_THREADS || vportUSE_POSIX_THREADS || vportUSE_POSIX_DRAFT7_THREADS)

pthread_t *
vthreadsysGetPosixThread (
   vthread                 *thread
   );

#elif (vportOS_UNIX_SOLARIS)

thread_t *
vthreadsysGetSolarisThread (
   vthread                 *thread
   );

#elif (vportOS_MAC)

ThreadID
vthreadsysGetMacThread (
   vthread                 *thread
   );

#elif (vportOS_OS2)

TID
vthreadsysGetOS2Thread (
   vthread                 *thread
   );

#endif

vportEND_CPLUSPLUS_EXTERN_C

#endif /* vthreadsysINCLUDED */

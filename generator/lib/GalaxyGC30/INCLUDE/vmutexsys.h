/* $Id: vmutexsys.h,v 1.8 1997/10/23 15:11:28 mikem Exp $ */

/************************************************************

    vmutexsys.h

    C Interface file for fast, platform-specific mutexes

    (c) Copyright 1996, 1997 Visix Software Inc.
    All rights reserved

************************************************************/

#ifndef vmutexsysINCLUDED
#define vmutexsysINCLUDED 1

#ifndef  vportHEADER
#include <vport.h>
#endif

#ifndef  vstdINCLUDED
#include vstdHEADER
#endif

#ifndef  vstdlibINCLUDED
#include vstdlibHEADER
#endif

#ifndef  vstdioINCLUDED
#include vstdioHEADER
#endif

#ifndef  vexINCLUDED
#include vexHEADER
#endif

#ifndef  vdebugINCLUDED
#include vdebugHEADER
#endif

#ifndef  vmutexINCLUDED
#include vmutexHEADER
#endif

/*
 * Include platform-specific header files. These are required by the
 * implementation of the macros to lock/unlock mutexs.
 */
#if (vportOS_MAC)
# ifndef vportUSE_MAC_THREADS
#  define vportUSE_MAC_THREADS (1)
# endif
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

#if (vportOS_UNIX_SOLARIS)
# ifndef vportUSE_SOLARIS_THREADS
#  define vportUSE_SOLARIS_THREADS (1)
# endif
# include <thread.h>
#endif

#if (vportOS_WINDOWS)
# include <process.h>
# include vmswhdrsHEADER
#endif

#if (vportOS_UNIX_SUNOS)
# ifndef vportUSE_SUNOS_THREADS
#  define vportUSE_SUNOS_THREADS (1)
# endif
vportBEGIN_CPLUSPLUS_EXTERN_C
# include <lwp/lwp.h>
vportEND_CPLUSPLUS_EXTERN_C
int cv_notify(cv_t *);
int cv_wait(cv_t *);
int mon_enter(mon_t *);
int mon_exit(mon_t *);
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C

/*===========================================================================*
 * * * * * * * * * * *   PUBLIC  FUNCTION  PROTOTYPES  * * * * * * * * * * * *
 *===========================================================================*/

/*
 * Recursive mutexes (a single thread may lock these more than once)
 */

void
vmutexMLock (
   vmutex              *mutex
   );

void
vmutexMUnlock (
   vmutex               *mutex
   );

/*
 * Non-recursive mutexes (a single thread may lock these only once)
 */

void
vmutexMLockNR (
   vmutex              *mutex
   );

void
vmutexMUnlockNR (
   vmutex               *mutex
   );

/*===========================================================================*
 * * * * * * * * * * *   PRIVATE  FUNCTION  PROTOTYPES * * * * * * * * * * * *
 *===========================================================================*/


/*===========================================================================*
 * * * * * * * * * * * *   PRIVATE  TYPE  DEFINITIONS  * * * * * * * * * * * *
 *===========================================================================*/

typedef struct _vmutex {
  unsigned int      flags;
  int               depth;
  void             *owner;
#if (vportUSE_DCE_THREADS)
  pthread_mutex_t   m;
#elif (vportUSE_POSIX_THREADS)
  pthread_mutex_t   m;
#elif (vportUSE_POSIX_DRAFT7_THREADS)
  pthread_mutex_t   m;
#elif (vportOS_UNIX_SOLARIS)
  mutex_t           m;
#elif (vportOS_WINDOWS)
  CRITICAL_SECTION  cs;
#elif (vportOS_MAC)
  /*
   * No OS-data needed for Mac.
   */
#elif (vportOS_OS2)
  HMTX              m;
#elif (vportOS_UNIX_SUNOS)
  mon_t             m;
  cv_t              cv;
#endif
  const char       *nameFmt;
  void             *fmtArg;
} _vmutex;

/*===========================================================================*
 * * * * * * * * *  PRIVATE  FUNCTION  MACRO  DEFINITIONS  * * * * * * * * * *
 *===========================================================================*/

#if !(vportDISABLE_THREADS)

#if (vportOS_WINDOWS)
extern vportLINK void *_vthreadersysWin32Thread;

#if (vdebugDEBUG)
#define _vmutexMSetupLock(_m) do {                                           \
                void *o = TlsGetValue((DWORD)_vthreadersysWin32Thread);

#define _vmutexMFinishLock(_m)                                               \
                if ((*(_m))->flags & vmutexTYPE_NON_RECURSIVE)               \
                  vcompatAbortWithMessage("vmutexMLock called on "           \
                                          "non-recursive mutex.");           \
                if ((*(_m))->owner != o) {                                   \
                  EnterCriticalSection(&(*(_m))->cs);                        \
                  (*(_m))->owner = o;                                        \
                }                                                            \
                (*(_m))->depth++;                                            \
              } while (0)

#define vmutexMUnlock(_m) do {                                               \
                if ((*(_m))->flags & vmutexTYPE_NON_RECURSIVE)               \
                  vcompatAbortWithMessage("vmutexMUnlock called on "         \
                                          "non-recursive mutex.");           \
                (*(_m))->depth--;                                            \
                if ((*(_m))->depth == 0) {                                   \
                  (*(_m))->owner = NULL;                                     \
                  LeaveCriticalSection(&(*(_m))->cs);                        \
                }                                                            \
              } while (0)

#define vmutexMLockNR(_m) do {                                               \
                void *o = TlsGetValue((DWORD)_vthreadersysWin32Thread);      \
                if ((*(_m))->flags & vmutexTYPE_RECURSIVE)                   \
                  vcompatAbortWithMessage("vmutexMLockNR called on "         \
                                          "recursive mutex.");               \
                if ((*(_m))->owner == o)                                     \
                  vcompatAbortWithMessage("vmutexMLockNR called twice for "  \
                                          "same mutex.");                    \
                EnterCriticalSection(&(*(_m))->cs);                          \
                (*(_m))->owner = o;                                          \
              } while (0)

#define vmutexMUnlockNR(_m) do {                                             \
                if ((*(_m))->flags & vmutexTYPE_RECURSIVE)                   \
                  vcompatAbortWithMessage("vmutexMUnlockNR called on "       \
                                          "recursive mutex.");               \
                (*(_m))->owner = NULL;                                       \
                LeaveCriticalSection(&(*(_m))->cs);                          \
              } while (0)
#else
#define _vmutexMSetupLock(_m) do {                                           \
                void *o = TlsGetValue((DWORD)_vthreadersysWin32Thread);

#define _vmutexMFinishLock(_m)                                               \
                if ((*(_m))->owner != o) {                                   \
                  EnterCriticalSection(&(*(_m))->cs);                        \
                  (*(_m))->owner = o;                                        \
                }                                                            \
                (*(_m))->depth++;                                            \
              } while (0)

#define vmutexMUnlock(_m) do {                                               \
                (*(_m))->depth--;                                            \
                if ((*(_m))->depth == 0) {                                   \
                  (*(_m))->owner = NULL;                                     \
                  LeaveCriticalSection(&(*(_m))->cs);                        \
                }                                                            \
              } while (0)

#define vmutexMLockNR(_m)                                                    \
                EnterCriticalSection(&(*(_m))->cs)

#define vmutexMUnlockNR(_m)                                                  \
                LeaveCriticalSection(&(*(_m))->cs)
#endif
#elif (vportUSE_DCE_THREADS)
extern vportLINK void *_vthreadersysDCEThread;

#if (vdebugDEBUG)
#define _vmutexMSetupLock(_m) do {                                           \
                void *o;                                                     \
                pthread_getspecific((pthread_key_t)_vthreadersysDCEThread,   \
                                    (pthread_addr_t*)&o);

#define _vmutexMFinishLock(_m)                                               \
                if ((*(_m))->flags & vmutexTYPE_NON_RECURSIVE)               \
                  vcompatAbortWithMessage("vmutexMLock called on "           \
                                          "non-recursive mutex.");           \
                if ((*(_m))->owner != o) {                                   \
                  pthread_mutex_lock(&(*(_m))->m);                           \
                  (*(_m))->owner = o;                                        \
                }                                                            \
                (*(_m))->depth++;                                            \
              } while (0)

#define vmutexMUnlock(_m) do {                                               \
                if ((*(_m))->flags & vmutexTYPE_NON_RECURSIVE)               \
                  vcompatAbortWithMessage("vmutexMUnlock called on "         \
                                          "non-recursive mutex.");           \
                (*(_m))->depth--;                                            \
                if ((*(_m))->depth == 0) {                                   \
                  (*(_m))->owner = NULL;                                     \
                  pthread_mutex_unlock(&(*(_m))->m);                         \
                }                                                            \
              } while (0)

#define vmutexMLockNR(_m) do {                                               \
                void *o;                                                     \
                pthread_getspecific((pthread_key_t)_vthreadersysDCEThread,   \
                                    (pthread_addr_t*)&o);                    \
                if ((*(_m))->flags & vmutexTYPE_RECURSIVE)                   \
                  vcompatAbortWithMessage("vmutexMLockNR called on "         \
                                          "recursive mutex.");               \
                if ((*(_m))->owner == o)                                     \
                  vcompatAbortWithMessage("vmutexMLockNR called twice for "  \
                                          "same mutex.");                    \
                pthread_mutex_lock(&(*(_m))->m);                             \
                (*(_m))->owner = o;                                          \
              } while (0)

#define vmutexMUnlockNR(_m) do {                                             \
                if ((*(_m))->flags & vmutexTYPE_RECURSIVE)                   \
                  vcompatAbortWithMessage("vmutexMUnlockNR called on "       \
                                          "recursive mutex.");               \
                (*(_m))->owner = NULL;                                       \
                pthread_mutex_unlock(&(*(_m))->m);                           \
              } while (0)
#else
#define _vmutexMSetupLock(_m) do {                                           \
                void *o;                                                     \
                pthread_getspecific((pthread_key_t)_vthreadersysDCEThread,   \
                                    (pthread_addr_t*)&o);

#define _vmutexMFinishLock(_m)                                               \
                if ((*(_m))->owner != o) {                                   \
                  pthread_mutex_lock(&(*(_m))->m);                           \
                  (*(_m))->owner = o;                                        \
                }                                                            \
                (*(_m))->depth++;                                            \
              } while (0)

#define vmutexMUnlock(_m) do {                                               \
                (*(_m))->depth--;                                            \
                if ((*(_m))->depth == 0) {                                   \
                  (*(_m))->owner = NULL;                                     \
                  pthread_mutex_unlock(&(*(_m))->m);                         \
                }                                                            \
              } while (0)

#define vmutexMLockNR(_m)                                                    \
                pthread_mutex_lock(&(*(_m))->m)

#define vmutexMUnlockNR(_m)                                                  \
                pthread_mutex_unlock(&(*(_m))->m)
#endif
#elif (vportUSE_POSIX_THREADS)
extern vportLINK void *_vthreadersysPOSIXThread;

#if (vdebugDEBUG)
#define _vmutexMSetupLock(_m) do {                                           \
                void *o = pthread_getspecific(                               \
                                   (pthread_key_t)_vthreadersysPOSIXThread);

#define _vmutexMFinishLock(_m)                                               \
                if ((*(_m))->flags & vmutexTYPE_NON_RECURSIVE)               \
                  vcompatAbortWithMessage("vmutexMLock called on "           \
                                          "non-recursive mutex.");           \
                if ((*(_m))->owner != o) {                                   \
                  pthread_mutex_lock(&(*(_m))->m);                           \
                  (*(_m))->owner = o;                                        \
                }                                                            \
                (*(_m))->depth++;                                            \
              } while (0)

#define vmutexMUnlock(_m) do {                                               \
                if ((*(_m))->flags & vmutexTYPE_NON_RECURSIVE)               \
                  vcompatAbortWithMessage("vmutexMUnlock called on "         \
                                          "non-recursive mutex.");           \
                (*(_m))->depth--;                                            \
                if ((*(_m))->depth == 0) {                                   \
                  (*(_m))->owner = NULL;                                     \
                  pthread_mutex_unlock(&(*(_m))->m);                         \
                }                                                            \
              } while (0)

#define vmutexMLockNR(_m) do {                                               \
                void *o = pthread_getspecific(                               \
                                   (pthread_key_t)_vthreadersysPOSIXThread); \
                if ((*(_m))->flags & vmutexTYPE_RECURSIVE)                   \
                  vcompatAbortWithMessage("vmutexMLockNR called on "         \
                                          "recursive mutex.");               \
                if ((*(_m))->owner == o)                                     \
                  vcompatAbortWithMessage("vmutexMLockNR called twice for "  \
                                          "same mutex.");                    \
                pthread_mutex_lock(&(*(_m))->m);                             \
                (*(_m))->owner = o;                                          \
              } while (0)

#define vmutexMUnlockNR(_m) do {                                             \
                if ((*(_m))->flags & vmutexTYPE_RECURSIVE)                   \
                  vcompatAbortWithMessage("vmutexMUnlockNR called on "       \
                                          "recursive mutex.");               \
                (*(_m))->owner = NULL;                                       \
                pthread_mutex_unlock(&(*(_m))->m);                           \
              } while (0)
#else
#define _vmutexMSetupLock(_m) do {                                           \
                void *o = pthread_getspecific(                               \
                                   (pthread_key_t)_vthreadersysPOSIXThread);

#define _vmutexMFinishLock(_m)                                               \
                if ((*(_m))->owner != o) {                                   \
                  pthread_mutex_lock(&(*(_m))->m);                           \
                  (*(_m))->owner = o;                                        \
                }                                                            \
                (*(_m))->depth++;                                            \
              } while (0)

#define vmutexMUnlock(_m) do {                                               \
                (*(_m))->depth--;                                            \
                if ((*(_m))->depth == 0) {                                   \
                  (*(_m))->owner = NULL;                                     \
                  pthread_mutex_unlock(&(*(_m))->m);                         \
                }                                                            \
              } while (0)

#define vmutexMLockNR(_m)                                                    \
                pthread_mutex_lock(&(*(_m))->m)

#define vmutexMUnlockNR(_m)                                                  \
                pthread_mutex_unlock(&(*(_m))->m)
#endif
#elif (vportUSE_POSIX_DRAFT7_THREADS)
extern vportLINK void *_vthreadersysPOSIXD7Thread;

#if (vdebugDEBUG)
#define _vmutexMSetupLock(_m) do {                                           \
                void *o = pthread_getspecific(                               \
                                   (pthread_key_t)_vthreadersysPOSIXD7Thread);

#define _vmutexMFinishLock(_m)                                               \
                if ((*(_m))->flags & vmutexTYPE_NON_RECURSIVE)               \
                  vcompatAbortWithMessage("vmutexMLock called on "           \
                                          "non-recursive mutex.");           \
                if ((*(_m))->owner != o) {                                   \
                  pthread_mutex_lock(&(*(_m))->m);                           \
                  (*(_m))->owner = o;                                        \
                }                                                            \
                (*(_m))->depth++;                                            \
              } while (0)

#define vmutexMUnlock(_m) do {                                               \
                if ((*(_m))->flags & vmutexTYPE_NON_RECURSIVE)               \
                  vcompatAbortWithMessage("vmutexMUnlock called on "         \
                                          "non-recursive mutex.");           \
                (*(_m))->depth--;                                            \
                if ((*(_m))->depth == 0) {                                   \
                  (*(_m))->owner = NULL;                                     \
                  pthread_mutex_unlock(&(*(_m))->m);                         \
                }                                                            \
              } while (0)

#define vmutexMLockNR(_m) do {                                               \
                void *o = pthread_getspecific(                               \
                                 (pthread_key_t)_vthreadersysPOSIXD7Thread); \
                if ((*(_m))->flags & vmutexTYPE_RECURSIVE)                   \
                  vcompatAbortWithMessage("vmutexMLockNR called on "         \
                                          "recursive mutex.");               \
                if ((*(_m))->owner == o)                                     \
                  vcompatAbortWithMessage("vmutexMLockNR called twice for "  \
                                          "same mutex.");                    \
                pthread_mutex_lock(&(*(_m))->m);                             \
                (*(_m))->owner = o;                                          \
              } while (0)

#define vmutexMUnlockNR(_m) do {                                             \
                if ((*(_m))->flags & vmutexTYPE_RECURSIVE)                   \
                  vcompatAbortWithMessage("vmutexMUnlockNR called on "       \
                                          "recursive mutex.");               \
                (*(_m))->owner = NULL;                                       \
                pthread_mutex_unlock(&(*(_m))->m);                           \
              } while (0)
#else
#define _vmutexMSetupLock(_m) do {                                           \
                void *o = pthread_getspecific(                               \
                                   (pthread_key_t)_vthreadersysPOSIXD7Thread);

#define _vmutexMFinishLock(_m)                                               \
                if ((*(_m))->owner != o) {                                   \
                  pthread_mutex_lock(&(*(_m))->m);                           \
                  (*(_m))->owner = o;                                        \
                }                                                            \
                (*(_m))->depth++;                                            \
              } while (0)

#define vmutexMUnlock(_m) do {                                               \
                (*(_m))->depth--;                                            \
                if ((*(_m))->depth == 0) {                                   \
                  (*(_m))->owner = NULL;                                     \
                  pthread_mutex_unlock(&(*(_m))->m);                         \
                }                                                            \
              } while (0)

#define vmutexMLockNR(_m)                                                    \
                pthread_mutex_lock(&(*(_m))->m)

#define vmutexMUnlockNR(_m)                                                  \
                pthread_mutex_unlock(&(*(_m))->m)
#endif
#elif (vportOS_UNIX_SOLARIS)
extern vportLINK void *_vthreadersysSolarisThread;

#if (vdebugDEBUG)
#define _vmutexMSetupLock(_m) do {                                           \
                void *o;                                                     \
                thr_getspecific((thread_key_t)_vthreadersysSolarisThread,    \
                                &o);

#define _vmutexMFinishLock(_m)                                               \
                if ((*(_m))->flags & vmutexTYPE_NON_RECURSIVE)               \
                  vcompatAbortWithMessage("vmutexMLock called on "           \
                                          "non-recursive mutex.");           \
                if ((*(_m))->owner != o) {                                   \
                  mutex_lock(&(*(_m))->m);                                   \
                  (*(_m))->owner = o;                                        \
                }                                                            \
                (*(_m))->depth++;                                            \
              } while (0)

#define vmutexMUnlock(_m) do {                                               \
                if ((*(_m))->flags & vmutexTYPE_NON_RECURSIVE)               \
                  vcompatAbortWithMessage("vmutexMUnlock called on "         \
                                          "non-recursive mutex.");           \
                (*(_m))->depth--;                                            \
                if ((*(_m))->depth == 0) {                                   \
                  (*(_m))->owner = NULL;                                     \
                  mutex_unlock(&(*(_m))->m);                                 \
                }                                                            \
              } while (0)

#define vmutexMLockNR(_m) do {                                               \
                void *o;                                                     \
                thr_getspecific((thread_key_t)_vthreadersysSolarisThread,    \
                                &o);                                         \
                if ((*(_m))->flags & vmutexTYPE_RECURSIVE)                   \
                  vcompatAbortWithMessage("vmutexMLockNR called on "         \
                                          "recursive mutex.");               \
                if ((*(_m))->owner == o)                                     \
                  vcompatAbortWithMessage("vmutexMLockNR called twice for "  \
                                          "same mutex.");                    \
                mutex_lock(&(*(_m))->m);                                     \
                (*(_m))->owner = o;                                          \
              } while (0)

#define vmutexMUnlockNR(_m) do {                                             \
                if ((*(_m))->flags & vmutexTYPE_RECURSIVE)                   \
                  vcompatAbortWithMessage("vmutexMUnlockNR called on "       \
                                          "recursive mutex.");               \
                (*(_m))->owner = NULL;                                       \
                mutex_unlock(&(*(_m))->m);                                   \
              } while (0)
#else
#define _vmutexMSetupLock(_m) do {                                           \
                void *o;                                                     \
                thr_getspecific((thread_key_t)_vthreadersysSolarisThread, &o);

#define _vmutexMFinishLock(_m)                                               \
                if ((*(_m))->owner != o) {                                   \
                  mutex_lock(&(*(_m))->m);                                   \
                  (*(_m))->owner = o;                                        \
                }                                                            \
                (*(_m))->depth++;                                            \
              } while (0)

#define vmutexMUnlock(_m) do {                                               \
                (*(_m))->depth--;                                            \
                if ((*(_m))->depth == 0) {                                   \
                  (*(_m))->owner = NULL;                                     \
                  mutex_unlock(&(*(_m))->m);                                 \
                }                                                            \
              } while (0)

#define vmutexMLockNR(_m)                                                    \
                mutex_lock(&(*(_m))->m)

#define vmutexMUnlockNR(_m)                                                  \
                mutex_unlock(&(*(_m))->m)
#endif
#elif (vportOS_MAC)
extern vportLINK void *_vthreadersysMacThread;

#if (vdebugDEBUG)
#define _vmutexMSetupLock(_m) do {                                           \
                void *o = _vthreadersysMacThread;

#define _vmutexMFinishLock(_m)                                               \
                if ((*(_m))->flags & vmutexTYPE_NON_RECURSIVE)               \
                  vcompatAbortWithMessage("vmutexMLock called on "           \
                                          "non-recursive mutex.");           \
                while (((*(_m))->owner != NULL) && ((*(_m))->owner != o))    \
                  YieldToAnyThread();                                        \
                (*(_m))->owner = o;                                          \
                (*(_m))->depth++;                                            \
              } while (0)

#define vmutexMUnlock(_m) do {                                               \
                if ((*(_m))->flags & vmutexTYPE_NON_RECURSIVE)               \
                  vcompatAbortWithMessage("vmutexMUnlock called on "         \
                                          "non-recursive mutex.");           \
                if (--(*(_m))->depth == 0) {                                 \
                  (*(_m))->owner = NULL;                                     \
                }                                                            \
              } while (0)

#define vmutexMLockNR(_m) do {                                               \
                void *o = _vthreadersysMacThread;                            \
                if ((*(_m))->flags & vmutexTYPE_RECURSIVE)                   \
                  vcompatAbortWithMessage("vmutexMLockNR called on "         \
                                          "recursive mutex.");               \
                if ((*(_m))->owner == o)                                     \
                  vcompatAbortWithMessage("vmutexMLockNR called twice for "  \
                                          "same mutex.");                    \
                while (((*(_m))->owner != NULL) && ((*(_m))->owner != o))    \
                  YieldToAnyThread();                                        \
                (*(_m))->owner = o;                                          \
              } while (0)

#define vmutexMUnlockNR(_m) do {                                             \
                if ((*(_m))->flags & vmutexTYPE_RECURSIVE)                   \
                  vcompatAbortWithMessage("vmutexMUnlockNR called on "       \
                                          "recursive mutex.");               \
                (*(_m))->owner = NULL;                                       \
              } while (0)
#else
#define _vmutexMSetupLock(_m) do {                                           \
                void *o = _vthreadersysMacThread;

#define _vmutexMFinishLock(_m)                                               \
                while (((*(_m))->owner != NULL) && ((*(_m))->owner != o))    \
                  YieldToAnyThread();                                        \
                (*(_m))->owner = o;                                          \
                (*(_m))->depth++;                                            \
              } while (0)

#define vmutexMUnlock(_m) do {                                               \
                if (--(*(_m))->depth == 0) {                                 \
                  (*(_m))->owner = NULL;                                     \
                }                                                            \
              } while (0)

#define vmutexMLockNR(_m) do {                                               \
                void *o = _vthreadersysMacThread;                            \
                while (((*(_m))->owner != NULL) && ((*(_m))->owner != o))    \
                  YieldToAnyThread();                                        \
                (*(_m))->owner = o;                                          \
              } while (0)

#define vmutexMUnlockNR(_m)                                                  \
                (*(_m))->owner = NULL;
#endif
#elif (vportOS_OS2)
extern vportLINK void **_threadstore(void);

#if (vdebugDEBUG)
#define _vmutexMSetupLock(_m) do {                                           \
                APIRET rc;

#define _vmutexMFinishLock(_m)                                               \
                if ((*(_m))->flags & vmutexTYPE_NON_RECURSIVE)               \
                  vcompatAbortWithMessage("vmutexMLock called on "           \
                                          "non-recursive mutex.");           \
                rc = DosRequestMutexSem((*(_m))->m, SEM_INDEFINITE_WAIT);    \
                if (rc) {                                                    \
                  fprintf(stderr, "_vmutexMFinishLock: DosRequestMutexSem failed.  rc = %d\n", rc);                                                         \
                } else {                                                     \
                  (*(_m))->owner =  (*_threadstore());                       \
                  (*(_m))->depth++;                                          \
                }                                                            \
              } while (0)

#define vmutexMUnlock(_m) do {                                               \
                APIRET  rc;                                                  \
                if ((*(_m))->flags & vmutexTYPE_NON_RECURSIVE)               \
                  vcompatAbortWithMessage("vmutexMUnlock called on "         \
                                          "non-recursive mutex.");           \
                (*(_m))->depth--;                                            \
                if (((*(_m))->depth) == 0) {                                 \
                  (*(_m))->owner = NULL;                                     \
                }                                                            \
                rc = DosReleaseMutexSem((*(_m))->m);                         \
                if (rc) {                                                    \
                  fprintf(stderr, "vmutexMUnlock: DosReleaseMutexSem failed.  rc = %d\n", rc);                                                              \
                  if (((*(_m))->owner) == NULL)                              \
                    (*(_m))->owner = (*_threadstore());                      \
                  (*(_m))->depth++;                                          \
                }                                                            \
              } while (0)

#define vmutexMLockNR(_m) do {                                               \
                APIRET rc;                                                   \
                if ((*(_m))->flags & vmutexTYPE_RECURSIVE)                   \
                  vcompatAbortWithMessage("vmutexMLockNR called on "         \
                                          "recursive mutex.");               \
                if ((*(_m))->owner == (*_threadstore()))                     \
                  vcompatAbortWithMessage("vmutexMLockNR called twice for "  \
                                          "same mutex.");                    \
                rc = DosRequestMutexSem((*(_m))->m, SEM_INDEFINITE_WAIT);    \
                if (rc) {                                                    \
                  fprintf(stderr, "vmutexLockNR: DosRequestMutexSem failed.  rc = %d\n", rc);                                                               \
                } else {                                                     \
                  (*(_m))->owner = (*_threadstore());                        \
                }                                                            \
              } while (0)

#define vmutexMUnlockNR(_m) do {                                             \
                APIRET rc;                                                   \
                if ((*(_m))->flags & vmutexTYPE_RECURSIVE)                   \
                  vcompatAbortWithMessage("vmutexMUnlockNR called on "       \
                                          "recursive mutex.");               \
                (*(_m))->owner = NULL;                                       \
                rc = DosReleaseMutexSem((*(_m))->m);                         \
                if (rc) {                                                    \
                  fprintf(stderr, "vmutexMUnlockNR: DosReleaseMutexSem failed.  rc = %d\n", rc);                                                            \
                  (*(_m))->owner = (*_threadstore());                        \
                }                                                            \
              } while (0)
#else
#define _vmutexMSetupLock(_m)   do {

#define _vmutexMFinishLock(_m)                                               \
		  DosRequestMutexSem((*(_m))->m, SEM_INDEFINITE_WAIT);       \
		  (*(_m))->owner = (*_threadstore());                        \
		  (*(_m))->depth++;                                          \
		} while (0)

#define vmutexMUnlock(_m)       do {                                         \
		  (*(_m))->depth--;                                          \
		  if (((*(_m))->depth) == 0)                                 \
                    (*(_m))->owner = NULL;                                   \
		  DosReleaseMutexSem((*(_m))->m);                            \
		} while (0)

#define vmutexMLockNR(_m)                                                    \
                DosRequestMutexSem((*(_m))->m, SEM_INDEFINITE_WAIT)

#define vmutexMUnlockNR(_m)                                                  \
                DosReleaseMutexSem((*(_m))->m)
#endif
#elif (vportOS_UNIX_SUNOS)
extern vportLINK void *_vthreadersysSunOSThread;

#if (vdebugDEBUG)
#define _vmutexMSetupLock(_m) do {                                           \
                void *o = _vthreadersysSunOSThread;

#define _vmutexMFinishLock(_m)                                               \
                if ((*(_m))->flags & vmutexTYPE_NON_RECURSIVE)               \
                  vcompatAbortWithMessage("vmutexMLock called on "           \
                                          "non-recursive mutex.");           \
                if ((*(_m))->owner != o) {                                   \
                  mon_enter(&(*(_m))->m);                                    \
                  while ((*(_m))->owner != NULL)                             \
                    cv_wait(&(*(_m))->cv);                                   \
                  (*(_m))->owner = o;                                        \
                  mon_exit(&(*(_m))->m);                                     \
                }                                                            \
                (*(_m))->depth++;                                            \
              } while (0)

#define vmutexMUnlock(_m) do {                                               \
                if ((*(_m))->flags & vmutexTYPE_NON_RECURSIVE)               \
                  vcompatAbortWithMessage("vmutexMUnlock called on "         \
                                          "non-recursive mutex.");           \
                (*(_m))->depth--;                                            \
                if ((*(_m))->depth == 0) {                                   \
                  mon_enter(&(*(_m))->m);                                    \
                  (*(_m))->owner = NULL;                                     \
                  cv_notify(&(*(_m))->cv);                                   \
                  mon_exit(&(*(_m))->m);                                     \
                }                                                            \
              } while (0)

#define vmutexMLockNR(_m) do {                                               \
                void *o = _vthreadersysSunOSThread;                          \
                if ((*(_m))->flags & vmutexTYPE_RECURSIVE)                   \
                  vcompatAbortWithMessage("vmutexMLockNR called on "         \
                                          "recursive mutex.");               \
                if ((*(_m))->owner == o)                                     \
                  vcompatAbortWithMessage("vmutexMLockNR called twice for "  \
                                          "same mutex.");                    \
                mon_enter(&(*(_m))->m);                                      \
                while ((*(_m))->owner != NULL)                               \
                  cv_wait(&(*(_m))->cv);                                     \
                (*(_m))->owner = o;                                          \
                mon_exit(&(*(_m))->m);                                       \
              } while (0)

#define vmutexMUnlockNR(_m) do {                                             \
                if ((*(_m))->flags & vmutexTYPE_RECURSIVE)                   \
                  vcompatAbortWithMessage("vmutexMUnlockNR called on "       \
                                          "recursive mutex.");               \
                mon_enter(&(*(_m))->m);                                      \
                (*(_m))->owner = NULL;                                       \
                cv_notify(&(*(_m))->cv);                                     \
                mon_exit(&(*(_m))->m);                                       \
              } while (0)
#else
#define _vmutexMSetupLock(_m) do {                                           \
                void *o = _vthreadersysSunOSThread;

#define _vmutexMFinishLock(_m)                                               \
                if ((*(_m))->owner != o) {                                   \
                  mon_enter(&(*(_m))->m);                                    \
                  while ((*(_m))->owner != NULL)                             \
                    cv_wait(&(*(_m))->cv);                                   \
                  (*(_m))->owner = o;                                        \
                  mon_exit(&(*(_m))->m);                                     \
                }                                                            \
                (*(_m))->depth++;                                            \
              } while (0)

#define vmutexMUnlock(_m) do {                                               \
                (*(_m))->depth--;                                            \
                if ((*(_m))->depth == 0) {                                   \
                  mon_enter(&(*(_m))->m);                                    \
                  (*(_m))->owner = NULL;                                     \
                  cv_notify(&(*(_m))->cv);                                   \
                  mon_exit(&(*(_m))->m);                                     \
                }                                                            \
              } while (0)

#define vmutexMLockNR(_m) do {                                               \
                void *o = _vthreadersysSunOSThread;                          \
                mon_enter(&(*(_m))->m);                                      \
                while ((*(_m))->owner != NULL)                               \
                  cv_wait(&(*(_m))->cv);                                     \
                (*(_m))->owner = o;                                          \
                mon_exit(&(*(_m))->m);                                       \
              } while (0)

#define vmutexMUnlockNR(_m) do {                                             \
                mon_enter(&(*(_m))->m);                                      \
                (*(_m))->owner = NULL;                                       \
                cv_notify(&(*(_m))->cv);                                     \
                mon_exit(&(*(_m))->m);                                       \
              } while (0)
#endif
#endif /* This ends the big block of platform-specific code. */

#define vmutexMLock(_m)                                                      \
                _vmutexMSetupLock(_m) _vmutexMFinishLock(_m)

#else  /* #if !(vportDISABLE_THREADS) */

#define vmutexMLock(_m)      ((void)0)
#define vmutexMUnlock(_m)    ((void)0)
#define vmutexMLockNR(_m)    ((void)0)
#define vmutexMUnlockNR(_m)  ((void)0)

#endif /* #if !(vportDISABLE_THREADS) */

vportEND_CPLUSPLUS_EXTERN_C

#endif /* #ifndef vmutexINCLUDED */


/*
 * Formatting information for emacs in c-mode
 *
 * Local Variables:
 * c-argdecl-indent:3
 * c-brace-imaginary-offset:0
 * c-brace-offset:-3
 * c-continued-brace-offset:0
 * c-continued-statement-offset:3
 * c-indent-level:3
 * c-label-offset:-2
 * tab-width:8
 * End:
 */


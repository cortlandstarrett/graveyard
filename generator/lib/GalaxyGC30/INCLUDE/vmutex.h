/* $Id: vmutex.h,v 1.12 1997/06/29 06:38:19 mikem Exp $ */

/************************************************************

    vmutex.h

    C Interface file for mutexes

    (c) Copyright 1996, 1997 Visix Software Inc.
    All rights reserved

************************************************************/

#ifndef vmutexINCLUDED
#define vmutexINCLUDED 1

#ifndef  vportHEADER
#include <vport.h>
#endif

#ifndef  vstdINCLUDED
#include vstdHEADER
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


/*===========================================================================*
 * * * * * * * * * * * *  PUBLIC  CONSTANT  DEFINITIONS  * * * * * * * * * * *
 *===========================================================================*/

/*
 * vmutex provides mutually exclusive access to a single vthread.
 *
 * Mutexes can be either recursive (default) or non-recursive
 * Recursive mutexes allow the same thread to re-lock the mutex
 * w/o blocking (deadlocking). Non-recursive mutexes may be faster
 * on some platforms.
 */
enum 
{
  vmutexTYPE_RECURSIVE      = 0x00000001,
  vmutexTYPE_NON_RECURSIVE  = 0x00000002
};

#define vmutexNULL           NULL

/*===========================================================================*
 * * * * * * * * * * * * *  PUBLIC  TYPE  DEFINITIONS  * * * * * * * * * * * *
 *===========================================================================*/

typedef struct _vmutex *vmutex;

/*===========================================================================*
 * * * * * * * * * * *   PUBLIC  FUNCTION  PROTOTYPES  * * * * * * * * * * * *
 *===========================================================================*/

void
vmutexStartup (
   void
   );

/*
 * Mutexes
 */

void
vmutexAssertLocked (
   vmutex              *mutex
   );

void
vmutexAssertLockedGlobal (
   void
   );

int
vmutexDetermineType (
   vmutex              *mutex
   );

void
vmutexDestroy (
   vmutex              *mutex
   );

void
vmutexDump (
   vmutex              *mutex,
   FILE                *fp
   );

void
vmutexDumpAll (
   FILE                *fp
   );

const char *
vmutexGetName (
   vmutex              *mutex
   );

vbool
vmutexIsLocked (
   vmutex              *mutex
   );

void
vmutexInit (
   vmutex              *mutex
   );

void
vmutexInitNonrecursive (
   vmutex              *mutex
   );

void
vmutexLock (
   vmutex              *mutex
   );

void
vmutexLockWithHandling (
   vmutex              *mutex
   );

void
vmutexSetName (
   vmutex              *mutex,
   const char          *name
   );

void
vmutexSetNameFormatted (
   vmutex              *mutex,
   const char          *fmt,
   void                *arg
   );

vbool
vmutexTryLock (
   vmutex              *mutex
   );

void
vmutexUnlock (
   vmutex               *mutex
   );

void
vmutexUnlockWithHandling (
   vmutex               *mutex
   );

/*
 * Galaxy global mutex
 */

void
vmutexDumpGlobal (
   FILE                *fp
   );

vbool
vmutexIsLockedGlobal (
   void
   );

void 
vmutexLockGlobal (
   void
   );

void
vmutexLockGlobalWithHandling (
   void
   );

vbool
vmutexTryLockGlobal (
   void
   );

void
vmutexUnlockGlobal (
   void
   );

void
vmutexUnlockGlobalWithHandling (
   void
   );


/*===========================================================================*
 * * * * * * * * * * *   PRIVATE  FUNCTION  PROTOTYPES * * * * * * * * * * * *
 *===========================================================================*/

void
_vmutexHandleVexDestructor (
   void         *dummy
   );

int
_vmutexDetermineType (
   vmutex              *mutex
   );

void
_vmutexDestroy (
   vmutex              *mutex
   );

void
_vmutexDump (
   vmutex              *mutex,
   FILE                *fp
   );

void
_vmutexDumpAll (
   FILE                *fp
   );

const char *
_vmutexGetName (
   vmutex              *mutex
   );

void
_vmutexInit (
   vmutex              *mutex,
   int                  type,
   const char          *nameFmt,
   void                *fmtArg
   );

vbool
_vmutexIsLocked (
   vmutex              *mutex
   );

void
_vmutexLock (
   vmutex              *mutex
   );

void
_vmutexSetName (
   vmutex              *mutex,
   const char          *name
   );

void
_vmutexSetNameFormatted (
   vmutex              *mutex,
   const char          *fmt,
   void                *arg
   );

vbool
_vmutexTryLock (
   vmutex              *mutex
   );

void
_vmutexUnlock (
   vmutex               *mutex
   );

void
_vmutexDumpGlobal (
   FILE                *fp
   );

vbool
_vmutexIsLockedGlobal (
   void
   );

void 
_vmutexLockGlobal (
   void
   );

vbool
_vmutexTryLockGlobal (
   void
   );

void
_vmutexUnlockGlobal (
   void
   );

void
_vmutexFailAssert (
   vmutex               *mutex
   );

void
_vmutexFailAssertGlobal (
   void
   );

/*===========================================================================*
 * * * * * * * * *  PRIVATE  FUNCTION  MACRO  DEFINITIONS  * * * * * * * * * *
 *===========================================================================*/

#if !(vportDISABLE_THREADS)

#define vmutexDestroy(__m)           (_vmutexDestroy)(__m)

#define vmutexDetermineType(__m)     (_vmutexDetermineType)(__m)


#if (vportDEBUG)
# define vmutexDump(__m,__f)         (_vmutexDump)(__m,__f)
# define vmutexDumpAll(__f)          (_vmutexDumpAll)(__f)
#else
# define vmutexDump(__m,__f)         ((void)0)
# define vmutexDumpAll(__f)          ((void)0)
#endif

#define vmutexGetName(__m)           (_vmutexGetName)(__m)

#define vmutexInit(__m)              (_vmutexInit)(__m, vmutexTYPE_RECURSIVE, \
                                                   vportQUOTE(__m), NULL)

#define vmutexInitNonrecursive(__m)  (_vmutexInit)(__m,                      \
                                                   vmutexTYPE_NON_RECURSIVE, \
                                                   vportQUOTE(__m), NULL)

#define vmutexIsLocked(__m)          (_vmutexIsLocked)(__m)

#define vmutexLock(__m)              (_vmutexLock)(__m)

#define vmutexLockWithHandling(__m)  \
               vexPushDestructor((void (*)(void*))_vmutexUnlock, __m);\
               (_vmutexLock)(__m)

#define vmutexSetName(__m,__n)       (_vmutexSetNameFormatted)(__m,__n,NULL)

#define vmutexSetNameFormatted(__m,__f,__a) \
                                     (_vmutexSetNameFormatted)(__m,__f,__a)

#define vmutexTryLock(__m)           (_vmutexTryLock)(__m)

#define vmutexUnlock(__m)            (_vmutexUnlock)(__m)

#define vmutexUnlockWithHandling(__m) \
               vexPopDestructor((void (*)(void*))_vmutexUnlock, __m)

#define vmutexDumpGlobal(__f)        (_vmutexDumpGlobal)(__f)

#define vmutexIsLockedGlobal()       (_vmutexIsLockedGlobal)()

#define vmutexLockGlobal()           (_vmutexLockGlobal)()

#define vmutexLockGlobalWithHandling()      \
               vexPushDestructor(_vmutexHandleVexDestructor, NULL);\
               vmutexLockGlobal()

#define vmutexTryLockGlobal()        (_vmutexTryLockGlobal)()

#define vmutexUnlockGlobal()         (_vmutexUnlockGlobal)()

#define vmutexUnlockGlobalWithHandling()   \
               vexPopDestructor(_vmutexHandleVexDestructor, NULL)

#else

#define vmutexDestroy(__m)              ((void)0)
#define vmutexDetermineType(__m)        ((void)0)
#define vmutexDump(__m,__f)             ((void)0)
#define vmutexDumpAll(__f)              ((void)0)
#define vmutexGetName(__m)              (NULL)
#define vmutexInit(__m)                 ((void)0)
#define vmutexInitNonrecursive(__m)     ((void)0)
#define vmutexIsLocked(__m)             (vTRUE)
#define vmutexLock(__m)                 ((void)0)
#define vmutexLockWithHandling(__m)     ((void)0)
#define vmutexSetName(__m,__n)          ((void)0)
#define vmutexSetNameFormatted(__m,__f,__a) \
                                        ((void)0)
#define vmutexTryLock(__m)              (vTRUE)
#define vmutexUnlock(__m)               ((void)0)
#define vmutexUnlockWithHandling(__m)   ((void)0)

#define vmutexDumpGlobal(__f)           ((void)0)
#define vmutexIsLockedGlobal()          (vTRUE)
#define vmutexLockGlobal()              ((void)0)
#define vmutexLockGlobalWithHandling()  ((void)0)
#define vmutexTryLockGlobal()           (vTRUE)
#define vmutexUnlockGlobal()            ((void)0)
#define vmutexUnlockGlobalWithHandling() \
                                        ((void)0)

#endif /* #if !(vportDISABLE_THREADS #else */


#if (vdebugDEBUG) && !(vportDISABLE_THREADS)

#define vmutexAssertLocked(__m) \
     if (!vmutexIsLocked(__m)) _vmutexFailAssert(__m);

#define vmutexAssertLockedGlobal() \
     if (!vmutexIsLockedGlobal()) _vmutexFailAssertGlobal();

#else

#define vmutexAssertLocked(__m)         ((void)0)
#define vmutexAssertLockedGlobal()      ((void)0)

#endif /* #if !(vportDISABLE_THREADS) */

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


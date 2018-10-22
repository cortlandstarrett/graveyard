
/* $Id: vcondition.h,v 1.6 1997/06/29 06:37:13 mikem Exp $ */

/************************************************************

    vcondition.h

    C Interface file for low level condition variables

    (c) Copyright 1996 Visix Software Inc.
    All rights reserved

************************************************************/

#ifndef vconditionINCLUDED
#define vconditionINCLUDED 1

#ifndef  vportHEADER
#include <vport.h>
#endif

#ifndef  vmutexINCLUDED
#include vmutexHEADER
#endif

#ifndef  vstatusINCLUDED
#include vstatusHEADER
#endif


/*===========================================================================*
 * * * * * * * * * * * *  PUBLIC  CONSTANT  DEFINITIONS  * * * * * * * * * * *
 *===========================================================================*/

/*
 * vcondition provides an efficient synchronization object where
 * a thread could need to wait for an indeterminate amount of time
 *
 */

#define vconditionNULL           NULL

/*===========================================================================*
 * * * * * * * * * * * * *  PUBLIC  TYPE  DEFINITIONS  * * * * * * * * * * * *
 *===========================================================================*/

typedef struct _vcondition *vcondition;

/*===========================================================================*
 * * * * * * * * * * *   PUBLIC  FUNCTION  PROTOTYPES  * * * * * * * * * * * *
 *===========================================================================*/

void
vconditionStartup (
   void
   );

/*
 * Conditions
 */

int
vconditionDestroy (
   vcondition          *condition
   );

int
vconditionDump (
   vcondition          *condition,
   FILE                *fp
   );

const char *
vconditionGetName (
   vcondition          *condition
   );

int
vconditionInit (
   vcondition          *condition
   );

int
vconditionSetName (
   vcondition          *condition,
   const char          *name
   );

int
vconditionSetNameFormatted (
   vcondition          *condition,
   const char          *nameFmt,
   void                *fmtArg
   );

int
vconditionSignal (
   vcondition          *condition
   );

int
vconditionSignalAll (
   vcondition          *condition
   );

int
vconditionWait (
   vcondition          *condition,
   vmutex              *mutex,
   unsigned long        secs,
   unsigned long        nsecs
   );

int
vconditionWaitInterruptable (
   vcondition          *condition,
   vmutex              *mutex,
   unsigned long        secs,
   unsigned long        nsecs
   );

/*===========================================================================*
 * * * * * * * * * * *   PRIVATE  FUNCTION  PROTOTYPES * * * * * * * * * * * *
 *===========================================================================*/

int
_vconditionDestroy (
   vcondition          *condition
   );

int
_vconditionDump (
   vcondition          *condition,
   FILE                *fp
   );

const char *
_vconditionGetName (
   vcondition          *condition
   );

int
_vconditionInit (
   vcondition          *condition,
   const char          *nameFmt,
   void                *fmtArg
   );

int
_vconditionSetNameFormatted (
   vcondition          *condition,
   const char          *nameFmt,
   void                *fmtArg
   );

int
_vconditionSignal (
   vcondition          *condition
   );

int
_vconditionSignalAll (
   vcondition          *condition
   );

int
_vconditionWait (
   vcondition          *condition,
   vmutex              *mutex,
   unsigned long        secs,
   unsigned long        nsecs
   );

int
_vconditionWaitInterruptable (
   vcondition          *condition,
   vmutex              *mutex,
   unsigned long        secs,
   unsigned long        nsecs
   );


/*===========================================================================*
 * * * * * * * * *  PRIVATE  FUNCTION  MACRO  DEFINITIONS  * * * * * * * * * *
 *===========================================================================*/

#if !(vportDISABLE_THREADS)

#define vconditionDestroy(__c)           (_vconditionDestroy)(__c)
#define vconditionDump(__c,__f)          (_vconditionDump)(__c,__f)
#define vconditionGetName(__c)           (_vconditionGetName)(__c)
#define vconditionInit(__c)              (_vconditionInit) \
                                         (__c,vportQUOTE(__c),NULL)
#define vconditionSetName(__c,__n)       (_vconditionSetNameFormatted) \
                                            (__c,__n,NULL)
#define vconditionSetNameFormatted(__c,__f,__a) \
                                         (_vconditionSetNameFormatted) \
                                            (__c,__f,__a)
#define vconditionSignal(__c)            (_vconditionSignal)(__c)
#define vconditionSignalAll(__c)         (_vconditionSignalAll)(__c)
#define vconditionWait(__c,__m,__s,__n)  (_vconditionWait)(__c,__m,__s,__n)
#define vconditionWaitInterruptable(__c,__m,__s,__n) \
                            (_vconditionWaitInterruptable)(__c,__m,__s,__n)

#else

#define vconditionDestroy(__c)           (vstatusSUCCESS)
#define vconditionDump(__c,__f)          (vstatusSUCCESS)
#define vconditionGetName(__c)           (NULL)
#define vconditionInit(__c)              (vstatusSUCCESS)
#define vconditionSetName(__c,__n)       (vstatusSUCCESS)
#define vconditionSignal(__c)            (vstatusSUCCESS)
#define vconditionSignalAll(__c)         (vstatusSUCCESS)
#define vconditionWait(__c,__m,__s,__n)  (vstatusSUCCESS)
#define vconditionWaitInterruptable(__c,__m,__s,__n) \
                                         (vstatusSUCCESS)


#endif /* #if !(vportDISABLE_THREADS) #else */

#endif /* #ifndef vconditionINCLUDED */


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


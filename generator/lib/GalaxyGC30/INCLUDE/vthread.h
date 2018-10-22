/* $Id: vthread.h,v 1.47 1997/10/20 18:48:18 mikem Exp $ */

/************************************************************

    vthread.h

    C Interface file for Thread manager

    (c) Copyright 1996, 1997 Visix Software Inc.
    All rights reserved

************************************************************/

#ifndef vthreadINCLUDED
#define vthreadINCLUDED 1

#ifndef  vportHEADER
#include <vport.h>
#endif

#ifndef vmswhdrsINCLUDED
#include vmswhdrsHEADER
#endif

#ifndef  vstdINCLUDED
#include vstdHEADER
#endif

#ifndef  vexINCLUDED
#include vexHEADER
#endif

#ifndef vsignalINCLUDED
#include vsignalHEADER
#endif

#ifndef vinstanceINCLUDED
#include vinstanceHEADER
#endif


vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * * * * * * * * * * PUBLIC CONSTANT DEFINITIONS * * * * * * * * * *
 */

/*
 * Thread priority ranges. These are the min/max values you can pass to
 * vthreadSetPriority().
 */
enum {
   vthreadPRIORITY_MIN     = 1,
   vthreadPRIORITY_NORMAL  = 5,
   vthreadPRIORITY_MAX     = 10
};

   
/*
 * Thread scheduling scopes. These are the possible values you can pass
 * to vthreadSetScope().
 */
enum {
   vthreadSCOPE_PROCESS,
   vthreadSCOPE_KERNEL
};

   
/*
 * * * * * * * * * * PUBLIC TYPE DEFINITIONS * * * * * * * * * *
 */

#define vthreadLOCAL(l)      vportDECLSPEC_THREAD l vportTHREAD
#define vthreadGroupLOCAL(l) vportDECLSPEC_THREAD l vportTHREAD

typedef int (*vportSYSLINK vthreadRunProc)(void *arg);

typedef void (*vportSYSLINK vthreadInterruptProc)(void *arg);
    
typedef void (*vportSYSLINK vthreadAtExitProc)(void *arg);
    
typedef struct vthread                     vthread;
typedef struct vthreadClass                vthreadClass;
typedef struct vthreadGroup                vthreadGroup;
typedef struct vthreadGroupClass           vthreadGroupClass;
typedef struct vthreadGroupIterator        vthreadGroupIterator;
typedef struct vthreadIterator             vthreadIterator;

typedef struct vthreadInterruptedException   vthreadInterruptedException;
typedef struct vthreadTerminatedException    vthreadTerminatedException;
typedef struct vthreadResourceLimitException vthreadResourceLimitException;
typedef struct vthreadStateActiveException   vthreadStateActiveException;
typedef struct vthreadStateAutoDestroyException
                                             vthreadStateAutoDestroyException;

   
/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */

void
vthreadStartup (
   void
   );

/*
 * Thread class
 */

void
vthreadAtExit (
   vthreadAtExitProc     proc,
   void                 *arg
   );

vthread *
vthreadClone (
   vthread              *thread
   );

void
vthreadCopy (
   vthread              *source,
   vthread              *target
   );

void
vthreadCopyInit (
   vthread              *source,
   vthread              *target
   );

vthread *
vthreadCreate (
   void
   );

vthread *
vthreadCreateOfClass (
   vthreadClass         *clas
   );

void
vthreadDestroy (
   vthread              *thread
   );

vthread *
vthreadDetermine (
   void
   );

void
vthreadDump (
   vthread              *thread,
   FILE                 *fd
   );

void
vthreadExit (
   int                  status
   );

vthreadClass *
vthreadGetClass (
   vthread              *thread
   );

int 
vthreadGetConcurrencyLevel (
   void
   );

void *
vthreadGetData (
   vthread              *thread
   );

vthreadClass *
vthreadGetDefaultClass (
   void 
   );

vthreadGroup*
vthreadGetGroup (
   vthread              *thread
   );

vinstance *
vthreadGetInstance (
   vthread              *thread
   );

int
vthreadGetScope (
   vthread              *thread
   );

size_t
vthreadGetStackSize (
   vthread              *thread
   );

const vname *
vthreadGetTag (
   vthread              *thread
   );

int
vthreadGetTerminationStatus (
   vthread              *thread
   );

void
vthreadInit (
   vthread              *thread
   );

void
vthreadInitOfClass (
   vthread              *thread,
   vthreadClass         *clas
   );

vbool
vthreadIsActive (
   vthread              *thread
   );

vbool
vthreadIsActivating (
   vthread              *thread
   );

vbool
vthreadIsInactive (
   vthread              *thread
   );

vbool
vthreadIsRunning (
   vthread              *thread
   );

vbool
vthreadIsSuspended (
   vthread              *thread
   );

vbool
vthreadIsSuspendRequested (
   vthread              *thread
   );

vbool
vthreadIsTerminated (
   vthread              *thread
   );

vbool
vthreadIsTerminationRequested (
   vthread              *thread
   );

void
vthreadRegisterInterruptProc (
   vthread              *vthread,
   vthreadInterruptProc  proc,
   void                 *arg
   );

void
vthreadResume (
   vthread              *thread
   );

void 
vthreadSetConcurrencyLevel (
   int                   level
   );

void
vthreadSetData (
   vthread              *thread,
   void                 *data
   );

void
vthreadSetScope (
   vthread              *thread,
   int                   scope
   );

void
vthreadSetStackSize (
   vthread              *thread,
   size_t                stacksize
   );

void
vthreadSetTag (
   vthread              *thread,
   const vname          *name
   );

void 
vthreadSetTerminationStatus (
   vthread              *thread,
   int                   status
   );

void
vthreadSleep (
   unsigned long         seconds,
   unsigned long         nanoseconds
   );

void
vthreadSetRunProc (
   vthread              *thread,
   vthreadRunProc        proc
   );

void
vthreadStart (
   vthread              *thread,
   void                 *arg
   );

void
vthreadRequestSuspend (
   vthread              *thread
   );

void
vthreadRequestTermination (
   vthread              *thread
   );

void
vthreadInterrupt (
   vthread              *thread
   );

void
vthreadSetDestroyWhenTerminated (
   vthread              *thread,
   vbool                 on_off
   );

vbool
vthreadWaitForTermination (
   vthread              *thread,
   unsigned long         seconds,
   unsigned long         nanoseconds
   );

/*
 * Thread scheduling
 */
int
vthreadGetPriority (
   vthread              *thread
   );

void
vthreadSetPriority (
   vthread              *thread,
   int                   priority
   );

void
vthreadYield (
   void
   );

/*
 * Thread local storage
 */
void *
vthreadGetLocal (
   void                 *key
   );

void
vthreadInitLocal (
   void                **key
   );

void
vthreadSetLocal (
   void                **key,
   void                 *value
   );

/*
 * Thread exceptions
 */
const vexClass *vthreadGetInterruptedExceptionClass(
    void
    );

const vexClass *vthreadGetTerminatedExceptionClass(
    void
    );

const vexClass *vthreadGetResourceLimitExceptionClass(
    void
    );

const vexClass *vthreadGetStateActiveExceptionClass(
    void
    );

const vexClass *vthreadGetStateAutoDestroyExceptionClass(
    void
    );

   
vthreadInterruptedException *vthreadGetInterruptedException(
    void
    );

vthreadTerminatedException *vthreadGetTerminatedException(
    void
    );

vthreadResourceLimitException *vthreadGetResourceLimitException(
    void
    );

vthreadStateActiveException *vthreadGetStateActiveException(
    void
    );

vthreadStateAutoDestroyException *vthreadGetStateAutoDestroyException(
    void
    );

   
void vthreadGenerateInterruptedException(
    const char                  *message
    );

void vthreadGenerateTerminatedException(
    const char                  *message
    );

void vthreadGenerateResourceLimitException(
    const char                  *message
    );

void vthreadGenerateStateActiveException(
    const char                  *message
    );

void vthreadGenerateStateAutoDestroyException(
    const char                  *message
    );


void vthreadPropagateInterruptedException(
    const char                  *message
    );

void vthreadPropagateTerminatedException(
    const char                  *message
    );

void vthreadPropagateResourceLimitException(
    const char                  *message
    );

void vthreadPropagateStateActiveException(
    const char                  *message
    );

void vthreadPropagateStateAutoDestroyException(
    const char                  *message
    );

/*
 * Thread and thread group iterators
 */
void
vthreadDestroyIterator (
   vthreadIterator      *iter
   );

void
vthreadDestroyGroupIterator (
   vthreadGroupIterator *iter
   );

vthread *
vthreadGetIteratorThread (
   vthreadIterator      *iter
   );

vthreadGroup *
vthreadGetGroupIteratorThreadGroup (
   vthreadGroupIterator *iter
   );

void
vthreadInitIterator (
   vthreadIterator      *iter,
   vthreadGroup         *group
   );

void
vthreadInitGroupIterator (
   vthreadGroupIterator *iter,
   vthreadGroup         *group
   );

vbool
vthreadNextIterator (
   vthreadIterator      *iter
   );

vbool
vthreadNextGroupIterator (
   vthreadGroupIterator *iter
   );


/*
 * Thread groups
 */
void
vthreadAddToGroup (
   vthreadGroup         *group,
   vthread              *thread
   );

vthreadGroup *
vthreadCreateGroup (
   void
   );

vthreadGroup *
vthreadCreateGroupOfClass (
   vthreadGroupClass    *clas
   );

void
vthreadDestroyGroup (
   vthreadGroup         *group
   );

vthreadGroup *
vthreadDetermineGroup (
   void
   );

int
vthreadDetermineGroupCount (
   vthreadGroup         *group
   );

int
vthreadDetermineThreadCount (
   vthreadGroup         *group
   );

void
vthreadDumpGroup (
   vthreadGroup         *group,
   FILE                 *fd
   );

vthreadGroupClass *
vthreadGetDefaultGroupClass (
   void
   );

vthreadGroupClass *
vthreadGetGroupClass (
   vthreadGroup         *group
   );

void *
vthreadGetGroupData (
   vthreadGroup         *group
   );

vinstance *
vthreadGetGroupInstance (
   vthreadGroup         *group
   );

vthreadGroup *
vthreadGetGroupParent (
   vthreadGroup         *group
   );

const vname *
vthreadGetGroupTag (
   vthreadGroup         *group
   );

vthreadGroup *
vthreadGetRootGroup (
   void
   );

void
vthreadInitGroup (
   vthreadGroup         *group
   );

void
vthreadInitGroupOfClass (
   vthreadGroup         *group,
   vthreadGroupClass    *clas
   );

void
vthreadSetGroupData (
   vthreadGroup         *group,
   const void           *data
   );

void
vthreadSetGroupParent (
   vthreadGroup         *group,
   vthreadGroup         *parent
   );

void
vthreadSetGroupTag (
   vthreadGroup         *group,
   const vname          *tag
   );

void
vthreadResumeGroup (
   vthreadGroup         *group
   );

void
vthreadRequestSuspendGroup (
   vthreadGroup         *group
   );

void
vthreadRequestTerminationGroup (
   vthreadGroup         *group
   );

void
vthreadSetDestroyWhenTerminatedGroup (
   vthreadGroup         *group
   );

/*
 * Thread group local storage
 */
void *
vthreadGetGroupLocal (
   void                 *key
   );

void
vthreadInitGroupLocal (
   void                **key
   );

void
vthreadSetGroupLocal (
   void                **key,
   void                 *value
   );

/*
 * Thread group scheduling
 */
void
vthreadSetGroupPriority (
   vthreadGroup         *group,
   int                   priority
   );


/*
 * * * * * * * * * * PRIVATE CONSTANT DEFINITIONS * * * * * * * * * *
 */

/*
 * Thread flags
 */
enum
{
   _vthreadFLAG_DESTROY_WHEN_TERMINATED = 0x000001
};

/*
 * Thread group locals stored in vthreadGroup structure
 */
#define _vthreadGroupLocalStaticSize 4

/*
 * Thread exceptions
 */
extern vportLINK const vexClass _vthreadInterruptedExceptionClass;
extern vportLINK const vexClass _vthreadTerminatedExceptionClass;
extern vportLINK const vexClass _vthreadResourceLimitExceptionClass;
extern vportLINK const vexClass _vthreadStateActiveExceptionClass;
extern vportLINK const vexClass _vthreadStateAutoDestroyExceptionClass;

   
/*
 * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * *
 */

struct vthread 
{
   vinstance       instance;
   vthreadRunProc  start;
   void           *arg;
   void           *data;
   void           *driver;
   unsigned int    flags;
   int             status;
   const vname    *tag;
   vthreadGroup   *group;
};

#define vthreadCLASS(SUPER, THREAD)                                        \
   vinstanceCLASS(SUPER, THREAD);                                          \
   vclassMETHOD(vthreadCOPY, (THREAD *thread, THREAD *target));            \
   vclassMETHOD(vthreadCOPY_INIT, (THREAD *thread, THREAD *target));       \
   vclassMETHOD(vthreadDUMP, (THREAD *thread, FILE *stream));              \
   vclassMETHOD(vthreadREGISTER_INTERRUPT_PROC, (THREAD *thread,           \
                                               vthreadInterruptProc proc,  \
                                               void *arg));                \
   vclassMETHOD(vthreadRESUME, (THREAD *thread));                          \
   vclassMETHOD(vthreadSET_DATA, (THREAD *thread, void *data));            \
   vclassMETHOD(vthreadSET_PRIORITY, (THREAD *thread, int priority));      \
   vclassMETHOD_RET(vthreadGET_PRIORITY, int, (THREAD *thread));           \
   vclassMETHOD(vthreadSET_SCOPE, (THREAD *thread, int scope));            \
   vclassMETHOD_RET(vthreadGET_SCOPE, int, (THREAD *thread));              \
   vclassMETHOD(vthreadSET_STACKSIZE, (THREAD *thread, size_t stacksize)); \
   vclassMETHOD_RET(vthreadGET_STACKSIZE, size_t, (THREAD *thread));       \
   vclassMETHOD(vthreadSET_TAG, (THREAD *thread, const vname *tag));       \
   vclassMETHOD(vthreadSET_TERMINATION_STATUS, (THREAD *thread,            \
                                                int status));              \
   vclassMETHOD(vthreadSLEEP, (THREAD *thread,                             \
                               unsigned long sec,                          \
                               unsigned long nsec));                       \
   vclassMETHOD(vthreadSET_RUN_PROC, (THREAD *thread,                      \
                                      vthreadRunProc proc));               \
   vclassMETHOD(vthreadSTART, (THREAD *thread, void *arg));                \
   vclassMETHOD_RET(vthreadRUN, int, (THREAD *thread, void *arg));         \
   vclassMETHOD(vthreadSUSPEND, (THREAD *thread));                         \
   vclassMETHOD(vthreadREQ_TERMINATION, (THREAD *thread));                 \
   vclassMETHOD(vthreadINTERRUPT, (THREAD *thread));                       \
   vclassMETHOD(vthreadDESTROY_WHEN_TERMINATED, (THREAD *t, vbool b));     \
   vclassMETHOD(vthreadYIELD, (THREAD *thread))

struct vthreadClass 
{
   vthreadCLASS(vthreadClass, vthread);
};

struct vthreadInterruptedException {
   vexException super;
};

struct vthreadTerminatedException {
   vexException super;
};

struct vthreadResourceLimitException {
   vexException super;
};

struct vthreadStateActiveException {
   vexException super;
};

struct vthreadStateAutoDestroyException {
   vexException super;
};

struct vthreadGroup
{
   vinstance       instance;
   const vname     *tag;
   void            *data;
   vdict           *groups;
   vdict           *threads;
   vthreadGroup    *parent;
   vmutex           mutex;
   void           **dynamicLS;
   int              dynamicLSsize;
   void            *staticLS[_vthreadGroupLocalStaticSize];
};

#define vthreadGROUP_CLASS(SUPER, THREAD)                                      \
   vinstanceCLASS(SUPER, THREAD)

struct vthreadGroupClass 
{
   vthreadGROUP_CLASS(vthreadGroupClass, vthreadGroup);
};

struct vthreadIterator
{
   vdictIterator   dictIter;
};

struct vthreadGroupIterator
{
   vdictIterator   dictIter;
};

/*
 * * * * * * * * * * PRIVATE FUNCTION PROTOTYPES * * * * * * * * * *
 */

/*
 * Thread Locals
 */
void *
_vthreadGetLocal (
   void                 *key
   );

void
_vthreadInitLocal (
   void                **key
   );

void
_vthreadSetLocal (
   void                **key,
   void                 *value
   );



/*
 * Thread Groups
 */
void
_vthreadGroupDetachThread (
   vthread              *thread
   );

/*
 * Thread Group Locals
 */

void *
_vthreadGetGroupLocal (
   void                 *key
   );

void
_vthreadInitGroupLocal (
   void                **key
   );

void
_vthreadSetGroupLocal (
   void                **key,
   void                 *value
   );


/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * *
 */

/*
 * Thread Class
 */
#define vthreadGetInstance(__t) \
   (vportBASE_OBJECT(__t, instance))

#define vthreadGetClass(__t) \
  ((vthreadClass *) vinstanceGetClass(vthreadGetInstance(__t)))

#define vthreadCreateOfClass(__c) \
   ((vthread *) vinstanceCreateOfClass((vinstanceClass *)(__c)))

#define vthreadCreate() \
   vthreadCreateOfClass(vthreadGetDefaultClass())

#define vthreadDestroy(__t) \
   vinstanceDestroy(vthreadGetInstance(__t))

#define vthreadCopy(__s,__t) \
   vclassSend(vthreadGetClass(__s), vthreadCOPY, (__s, __t))

#define vthreadCopyInit(__s,__t) \
   vclassSend(vthreadGetClass(__s), vthreadCOPY_INIT, (__s, __t))

#define vthreadDump(__t,__f) \
   vclassSend(vthreadGetClass(__t), vthreadDUMP, (__t,__f))

#define vthreadInit(__t) \
   vthreadInitOfClass((__t), vthreadGetDefaultClass())

#define vthreadInitOfClass(__t,__c) \
   vinstanceInitOfClass(vthreadGetInstance(__t), (vinstanceClass *)(__c))

#define vthreadRegisterInterruptProc(__t,__p,__a) \
   vclassSend(vthreadGetClass(__t), vthreadREGISTER_INTERRUPT_PROC, \
              (__t,__p,__a))

#define vthreadResume(__t) \
   vclassSend(vthreadGetClass(__t), vthreadRESUME, (__t))

#define vthreadSetData(__t,__d) \
   vclassSend(vthreadGetClass(__t), vthreadSET_DATA, (__t,__d))

#define vthreadSetTag(__t,__s) \
   vclassSend(vthreadGetClass(__t), vthreadSET_TAG, (__t,__s))

#define vthreadGetPriority(__t) \
   vclassSend(vthreadGetClass(__t), vthreadGET_PRIORITY, (__t))

#define vthreadSetPriority(__t,__p) \
   vclassSend(vthreadGetClass(__t), vthreadSET_PRIORITY, (__t,__p))

#define vthreadGetScope(__t) \
   vclassSend(vthreadGetClass(__t), vthreadGET_SCOPE, (__t))

#define vthreadSetScope(__t,__s) \
   vclassSend(vthreadGetClass(__t), vthreadSET_SCOPE, (__t,__s))

#define vthreadGetStackSize(__t) \
   vclassSend(vthreadGetClass(__t), vthreadGET_STACKSIZE, (__t))

#define vthreadSetStackSize(__t,__s) \
   vclassSend(vthreadGetClass(__t), vthreadSET_STACKSIZE, (__t,__s))

#define vthreadSetTerminationStatus(__t,__s) \
   vclassSend(vthreadGetClass(__t), vthreadSET_TERMINATION_STATUS, (__t,__s))

#define vthreadSetRunProc(__t,__p) \
   vclassSend(vthreadGetClass(__t), vthreadSET_RUN_PROC, (__t,__p))

#define vthreadStart(__t,__a) \
   vclassSend(vthreadGetClass(__t), vthreadSTART, (__t,__a))

#define vthreadRequestSuspend(__t) \
   vclassSend(vthreadGetClass(__t), vthreadSUSPEND, (__t))

#define vthreadRequestTermination(__t) \
   vclassSend(vthreadGetClass(__t), vthreadREQ_TERMINATION, (__t))

#define vthreadInterrupt(__t) \
   vclassSend(vthreadGetClass(__t), vthreadINTERRUPT, (__t))

#define vthreadSetDestroyWhenTerminated(__t, __b) \
   vclassSend(vthreadGetClass(__t), vthreadDESTROY_WHEN_TERMINATED, (__t, __b))

#define vthreadGetData(__t)              ((__t)->data)
#define vthreadGetTag(__t)               ((__t)->tag)
#define vthreadGetTerminationStatus(__t) ((__t)->status)

/*
 * Thread exceptions
 */
#define vthreadGetInterruptedExceptionClass()                              \
    (&_vthreadInterruptedExceptionClass)

#define vthreadGetTerminatedExceptionClass()                               \
    (&_vthreadTerminatedExceptionClass)

#define vthreadGetResourceLimitExceptionClass()                            \
    (&_vthreadResourceLimitExceptionClass)

#define vthreadGetStateActiveExceptionClass()                              \
    (&_vthreadStateActiveExceptionClass)

#define vthreadGetStateAutoDestroyExceptionClass()                         \
    (&_vthreadStateAutoDestroyExceptionClass)

   
#define vthreadGetInterruptedException()                                   \
    ((vthreadInterruptedException *)vexGetExceptionOfClass(&_vthreadInterruptedExceptionClass))

#define vthreadGetTerminatedException()                                    \
    ((vthreadTerminatedException *)vexGetExceptionOfClass(&_vthreadTerminatedExceptionClass))

#define vthreadGetResourceLimitException()                                 \
    ((vthreadResourceLimitException *)vexGetExceptionOfClass(&_vthreadResourceLimitExceptionClass))

#define vthreadGetStateActiveException()                                   \
    ((vthreadStateActiveException *)vexGetExceptionOfClass(&_vthreadStateActiveExceptionClass))

#define vthreadGetStateAutoDestroyException()                              \
    ((vthreadStateAutoDestroyException *)vexGetExceptionOfClass(&_vthreadStateAutoDestroyExceptionClass))

   
#define vthreadGenerateInterruptedException(m)                             \
    vexGenerate(&_vthreadInterruptedExceptionClass,                        \
                vexMESSAGE, m, vexNULL)

#define vthreadGenerateTerminatedException(m)                              \
    vexGenerate(&_vthreadTerminatedExceptionClass,                         \
                vexMESSAGE, m, vexNULL)

#define vthreadGenerateResourceLimitException(m)                           \
    vexGenerate(&_vthreadResourceLimitExceptionClass,                      \
                vexMESSAGE, m, vexNULL)

#define vthreadGenerateStateActiveException(m)                             \
    vexGenerate(&_vthreadStateActiveExceptionClass,                        \
                vexMESSAGE, m, vexNULL)

#define vthreadGenerateStateAutoDestroyException(m)                        \
    vexGenerate(&_vthreadStateAutoDestroyExceptionClass,                   \
                vexMESSAGE, m, vexNULL)

   
#define vthreadPropagateInterruptedException(m)                            \
     vexPropagate(&_vthreadInterruptedExceptionClass,                      \
                  vexMESSAGE, m, vexNULL)

#define vthreadPropagateTerminatedException(m)                             \
     vexPropagate(&_vthreadTerminatedExceptionClass,                       \
                  vexMESSAGE, m, vexNULL)

#define vthreadPropagateResourceLimitException(m)                          \
     vexPropagate(&_vthreadResourceLimitExceptionClass,                    \
                  vexMESSAGE, m, vexNULL)

#define vthreadPropagateStateActiveException(m)                            \
     vexPropagate(&_vthreadStateActiveExceptionClass,                      \
                  vexMESSAGE, m, vexNULL)

#define vthreadPropagateStateAutoDestroyException(m)                       \
     vexPropagate(&_vthreadStateAutoDestroyExceptionClass,                 \
                  vexMESSAGE, m, vexNULL)

/*
 * Thread locals
 */
#define vthreadGetLocal(_k)                _vthreadGetLocal ((void *)(_k))
#define vthreadSetLocal(_k, _v)            _vthreadSetLocal ((void**)(_k), \
                                                             (void *)(_v))
#define vthreadInitLocal(_k)               _vthreadInitLocal((void**)(_k))


/*
 * Thread groups
 */
#define vthreadGetGroupInstance(__g) \
   (vportBASE_OBJECT(__g, instance))

#define vthreadGetGroupClass(__g) \
  ((vthreadGroupClass *) vinstanceGetClass(vthreadGetGroupInstance(__g)))

#define vthreadCreateGroupOfClass(__c) \
   ((vthreadGroup *) vinstanceCreateOfClass((vinstanceClass *)(__c)))

#define vthreadCreateGroup() \
   vthreadCreateGroupOfClass(vthreadGetDefaultGroupClass())

#define vthreadDestroyGroup(__g) \
   vinstanceDestroy(vthreadGetGroupInstance(__g))

#define vthreadInitGroupOfClass(__g,__c) \
   vinstanceInitOfClass(vthreadGetGroupInstance(__g), (vinstanceClass *)(__c))

#define vthreadInitGroup(__g) \
   vthreadInitGroupOfClass((__g), vthreadGetDefaultGroupClass())

#define vthreadGetGroupData(__g)        ((__g)->data)
#define vthreadGetGroupParent(__g)      ((__g)->parent)
#define vthreadGetGroupTag(__g)         ((__g)->tag)
#define vthreadGetGroup(__t)            ((__t)->group)

/*
 * Thread Group Local Storage
 */
#define vthreadInitGroupLocal(__k)         _vthreadInitGroupLocal((void**)__k)
#define vthreadSetGroupLocal(__k,__v)      _vthreadSetGroupLocal((void**)__k,(void*)__v)
#define vthreadGetGroupLocal(__k)          _vthreadGetGroupLocal((void*)__k)


/*
 * Thread and group iterators
 */

#define vthreadInitIterator(__i,__g)       \
   vdictInitIterator (&(__i)->dictIter, (__g)->threads)
#define vthreadInitGroupIterator(__i,__g)  \
   vdictInitIterator (&(__i)->dictIter, (__g)->groups)
#define vthreadNextIterator(__i)         \
   vdictNextIterator (&(__i)->dictIter)
#define vthreadNextGroupIterator(__i)    \
   vdictNextIterator (&(__i)->dictIter)
#define vthreadGetIteratorThread(__i)    \
   ((vthread *)vdictGetIteratorValue(&(__i)->dictIter))
#define vthreadGetGroupIteratorThreadGroup(__i)\
   ((vthreadGroup *)vdictGetIteratorValue(&(__i)->dictIter))
#define vthreadDestroyIterator(__i)      \
   vdictDestroyIterator(&(__i)->dictIter)
#define vthreadDestroyGroupIterator(__i) \
   vdictDestroyIterator(&(__i)->dictIter)

vportEND_CPLUSPLUS_EXTERN_C

#endif /* #ifndef vthreadINCLUDED */

/*
 *
 * Local Variables:
 * c-argdecl-indent:3
 * c-brace-imaginary-offset:0
 * c-brace-offset:-3
 * c-continued-brace-offset:0
 * c-continued-statement-offset:3
 * c-extra-brace-offset:0
 * c-file-style:"ELLEMTEL"
 * c-file-offsets:((block-open . -)(inclass . 0)(topmost-intro . +)(statement-case-intro . 3)) 
 * c-indent-level:3
 * c-label-offset:-3
 * tab-width:8
 * End:
 */


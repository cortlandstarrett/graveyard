/* $Id: vpool.h,v 1.45 1997/09/22 13:58:48 robert Exp $ */

/************************************************************

    vpool.h

    C Interface file for the Pool Library

    (c) Copyright Visix Software Inc.
    All rights reserved

************************************************************/

#ifndef vpoolINCLUDED
#define vpoolINCLUDED

#ifndef  vportINCLUDED
#include <vport.h>
#endif

#ifndef  vdebugINCLUDED
#include vdebugHEADER
#endif

#ifndef  vmemINCLUDED
#include vmemHEADER
#endif

#ifndef  vmutexINCLUDED
#include vmutexHEADER
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * * * * * * * * * * PUBLIC CONSTANT DEFINITIONS  * * * * * * * * * *
 */

enum {
    vpoolMONITOR_EVENT_START        = 0,
    vpoolMONITOR_EVENT_STOP,
    vpoolMONITOR_EVENT_INIT,
    vpoolMONITOR_EVENT_DESTROY,
    vpoolMONITOR_EVENT_EXPAND,
    vpoolMONITOR_EVENT_ALLOC,
    vpoolMONITOR_EVENT_FREE
};

/*
 * * * * * * * * * * PUBLIC TYPE DEFINITIONS * * * * * * * * * *
 */

typedef struct vpool                vpool;

typedef void (*vpoolExpandProc)(
    vpool                          *pool,
    size_t                          size
    );

typedef struct vpoolMonitorEvent    vpoolMonitorEvent;

typedef void (*vpoolMonitorProc)(
    vpoolMonitorEvent              *event
    );


/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */

void vpoolStartup(void);


vpool *vpoolCreate(
    size_t                          elemSize
    );

void vpoolInit(
    vpool                          *pool,
    size_t                          elemSize
    );

void vpoolDestroy(
    vpool                          *pool
    );

void vpoolValidate(
    vpool                          *pool
    );

int vpoolIsValid(
    vpool                          *pool
    );

void vpoolDestroyUnbalanced(
    vpool                          *pool
    );

void vpoolExpand(
    vpool                          *pool,
    size_t                          count
    );

void vpoolExpandUnsafe(
    vpool                          *pool,
    size_t                          count
    );

void *vpoolAlloc(
    vpool                          *pool
    );

void *vpoolAllocUnsafe(
    vpool                          *pool
    );

void *vpoolAllocDebug(
    vpool                          *pool,
    const char                     *tag,
    const char                     *file,
    int                             line
    );

void *vpoolAllocUnsafeDebug(
    vpool                          *pool,
    const char                     *tag,
    const char                     *file,
    int                             line
    );

void vpoolFree(
    vpool                          *pool,
    void                           *elem
    );

void vpoolFreeUnsafe(
    vpool                          *pool,
    void                           *elem
    );

void vpoolFreeDebug(
    vpool                          *pool,
    void                           *elem,
    const char                     *tag,
    const char                     *file,
    int                             line
    );

void vpoolFreeUnsafeDebug(
    vpool                          *pool,
    void                           *elem,
    const char                     *tag,
    const char                     *file,
    int                             line
    );

void vpoolMarkFreed(
    vpool                          *pool,
    void                           *elem
    );

void vpoolMarkFreedUnsafe(
    vpool                          *pool,
    void                           *elem
    );

void vpoolMarkFreedDebug(
    vpool                          *pool,
    void                           *elem,
    const char                     *tag,
    const char                     *file,
    int                             line
    );

void vpoolMarkFreedUnsafeDebug(
    vpool                          *pool,
    void                           *elem,
    const char                     *tag,
    const char                     *file,
    int                             line
    );

void vpoolDump(
    vpool                          *pool,
    FILE                           *stream
    );

void vpoolDumpAll(
    FILE                           *stream
    );

void vpoolSetExpandProc(
    vpool                          *pool,
    vpoolExpandProc                 expandProc
    );

size_t vpoolGetElemSize(
    vpool                          *pool
    );

size_t vpoolGetCount(
    vpool                          *pool
    );

size_t vpoolGetSize(
    vpool                          *pool
    );

vpoolExpandProc vpoolGetExpandProc(
    vpool                          *pool
    );

void  vpoolSetMutex(
    vpool                          *pool,
    vmutex		           *mutex
    );

vmutex  *vpoolGetMutex(
    vpool                          *pool
    );

int vpoolIsElem(
    vpool                          *pool,
    const void                     *elem
    );

int vpoolIsValidElem(
    vpool                          *pool,
    const void                     *elem
    );

int vpoolIsElemMarkedFree(
    vpool                          *pool, 
    const void                     *elem
    );

void  vpoolLock(
    vpool	*pool
    );

void  vpoolUnlock(
    vpool	*pool
    );

void vpoolRegisterMonitorProc(
    vpoolMonitorProc                monitorProc
    );

void vpoolUnregisterMonitorProc(
    vpoolMonitorProc                monitorProc
    );

void vpoolSetGlobalEnable(
    int                             flag
    );

int vpoolGetGlobalEnable(
    void
    );


/**  monitor events
 **/
int vpoolGetMonitorEventType(
    vpoolMonitorEvent              *event
    );

vpool *vpoolGetMonitorEventPool(
    vpoolMonitorEvent              *event
    );

void *vpoolGetMonitorEventElem(
    vpoolMonitorEvent              *event
    );

const char *vpoolGetMonitorEventTag(
    vpoolMonitorEvent              *event
    );

const char *vpoolGetMonitorEventFile(
    vpoolMonitorEvent              *event
    );

int vpoolGetMonitorEventLine(
    vpoolMonitorEvent              *event
    );



#if (vportCPLUSPLUS_SOURCE)

#define vpoolNEW_DECLARATION(type)					\
    static vpool Pool;							\
    void *operator new(size_t size);					\
    void  operator delete(void *dead, size_t size)

#define vpoolNEW_DEFINITION(type, elemSize)				\
  vpool type::Pool(vsuppressDONT_INIT);					\
  void *type::operator new(size_t size)					\
  {									\
    if (!type::Pool.IsInited())						\
      {									\
        type::Pool.Init(elemSize);					\
	_vpoolDestroyInCleanup(&type::Pool);				\
      }									\
									\
    _vclientSetInNew(TRUE);						\
									\
    if (size <= elemSize)						\
      return vpoolAlloc(&type::Pool);					\
									\
    return _vpoolAllocAnySize(&type::Pool, size);			\
  }									\
  void  type::operator delete(void *dead, size_t size)			\
  {									\
    (void) _vpoolFreeAnySize(&type::Pool, dead, size);			\
  }

#endif /* (vportCPLUSPLUS_SOURCE) */


/*
 * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * *
 */

typedef struct _vpoolBlock          _vpoolBlock;

struct vpool {
    size_t                          elemSize, actualSize;
    vpoolExpandProc                 expandProc;
    _vpoolBlock                    *blocks;
    void                           *free;
    vmutex		           *mutex;

#if (vdebugDEBUG)
    vpool                          *next;
    const char                     *tag;
    const char                     *file;
    int                             line;
    void                          **elems, **elemNext, **elemMax;
#endif

};


struct vpoolMonitorEvent {
    int                             type;
    vpool                          *pool;
    void                           *elem;
    const char                     *tag;
    const char                     *file;
    int                             line;
};


/*
 * * * * * * * * * * PRIVATE VARIABLE DECLARATIONS * * * * * * * * * *
 */

#if (vdebugDEBUG)
extern int                          _vpoolGlobalEnable;
#endif

/*
 * * * * * * * * * * PRIVATE FUNCTION PROTOTYPES * * * * * * * * * *
 */

void _vpoolEmpty(vpool *pool);

#if (vdebugDEBUG)

vpool *_vpoolCreateDebug(
    size_t                          elemSize,
    const char                     *tag,
    const char                     *file,
    int                             line
    );

void _vpoolInitDebug(
    vpool                          *pool,
    size_t                          elemSize,
    const char                     *tag,
    const char                     *file,
    int                             line
    );

void _vpoolDestroyDebug(
    vpool                          *pool,
    const char                     *tag,
    const char                     *file,
    int                             line
    );

void _vpoolValidateDebug(
    vpool                          *pool,
    const char                     *tag,
    const char                     *file,
    int                             line
    );

void _vpoolDestroyUnbalancedDebug(
    vpool                          *pool,
    const char                     *tag,
    const char                     *file,
    int                             line
    );

void _vpoolEmptyDebug(
    vpool			   *pool,
    const char			   *tag, 
    const char			   *file,
    int				    line
    );

void *_vpoolAllocDebug(
    vpool                          *pool,
    const char                     *tag,
    const char                     *file,
    int                             line
    );

void *_vpoolAllocUnsafeDebug(
    vpool                          *pool,
    const char                     *tag,
    const char                     *file,
    int                             line
    );

void _vpoolFreeDebug(
    vpool                          *pool,
    void                           *elem,
    const char                     *tag,
    const char                     *file,
    int                             line
    );

void _vpoolFreeUnsafeDebug(
    vpool                          *pool,
    void                           *elem,
    const char                     *tag,
    const char                     *file,
    int                             line
    );

void _vpoolMarkFreedDebug(
    vpool                          *pool,
    void                           *elem,
    const char                     *tag,
    const char                     *file,
    int                             line
    );

void _vpoolMarkFreedUnsafeDebug(
    vpool                          *pool,
    void                           *elem,
    const char                     *tag,
    const char                     *file,
    int                             line
    );

#else /* (!vdebugDEBUG) */

void _vpoolInitNonDebug(
    vpool                          *pool,
    size_t                          elemSize
    );

void _vpoolValidateNonDebug(
    vpool                          *pool
    );

void *_vpoolAllocNonDebug(
    vpool                          *pool
    );

void *_vpoolAllocUnsafeNonDebug(
    vpool                          *pool
    );

void _vpoolFreeNonDebug(
    vpool                          *pool,
    void                           *elem
    );

void _vpoolFreeUnsafeNonDebug(
    vpool                          *pool,
    void                           *elem
    );

void _vpoolMarkFreedNonDebug(
    vpool                          *pool,
    void                           *elem
    );

void _vpoolMarkFreedUnsafeNonDebug(
    vpool                          *pool,
    void                           *elem
    );

#endif /* (!vdebugDEBUG) */

void _vpoolDestruct(vpool *pool);
void _vpoolDestructUnbalanced(vpool *pool);

#if (vdebugDEBUG)

void _vpoolDestructDebug(vpool *pool, const char *tag, 
			 const char *file, int line);
void _vpoolDestructUnbalancedDebug(vpool *pool, const char *tag, 
				   const char *file, int line);

#endif

#if (vportCPLUSPLUS_SOURCE)

void _vpoolCleanup(
    void
    );

void _vpoolDestroyInCleanup(
    vpool			   *pool
    );

void *_vpoolAllocAnySize(
    vpool                          *pool,
    size_t			    size
    );

void *_vpoolAllocUnsafeAnySize(
    vpool                          *pool,
    size_t			    size
    );

vbool _vpoolFreeAnySize(
    vpool                          *pool,
    void                           *elem,
    size_t			    size
    );

vbool _vpoolFreeUnsafeAnySize(
    vpool                          *pool,
    void                           *elem,
    size_t			    size
    );

#endif /* (vportCPLUSPLUS_SOURCE) */

/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * *
 */

#if (vdebugDEBUG)

#define vpoolCreate(n) \
    _vpoolCreateDebug(n, vmemTAG, __FILE__, __LINE__)
#define vpoolInit(p, n) \
    _vpoolInitDebug(p, n, vmemTAG, __FILE__, __LINE__)
#define vpoolDestroy(p) \
    _vpoolDestroyDebug(p, vmemTAG, __FILE__, __LINE__)
#define vpoolValidate(p) \
    _vpoolValidateDebug(p, vmemTAG, __FILE__, __LINE__)
#define vpoolDestroyUnbalanced(p) \
    _vpoolDestroyUnbalancedDebug(p, vmemTAG, __FILE__, __LINE__)

#define vpoolAlloc(p) \
    _vpoolAllocDebug(p, vmemTAG, __FILE__, __LINE__)
#define vpoolAllocUnsafe(p) \
    _vpoolAllocUnsafeDebug(p, vmemTAG, __FILE__, __LINE__)
#define vpoolAllocDebug(p, t, f, l) \
    _vpoolAllocDebug(p, t, f, l)
#define vpoolAllocUnsafeDebug(p, t, f, l) \
    _vpoolAllocUnsafeDebug(p, t, f, l)

#define vpoolFree(p, e) \
    _vpoolFreeDebug(p, e, vmemTAG, __FILE__, __LINE__)
#define vpoolFreeUnsafe(p, e) \
    _vpoolFreeUnsafeDebug(p, e, vmemTAG, __FILE__, __LINE__)
#define vpoolFreeDebug(p, e, t, f, l) \
    _vpoolFreeUnsafeDebug(p, e, t, f, l)
#define vpoolFreeUnsafeDebug(p, e, t, f, l) \
    _vpoolFreeDebug(p, e, t, f, l)

#define vpoolMarkFreed(p, e) \
    _vpoolMarkFreedDebug(p, e, vmemTAG, __FILE__, __LINE__)
#define vpoolMarkFreedUnsafe(p, e) \
    _vpoolMarkFreedUnsafeDebug(p, e, vmemTAG, __FILE__, __LINE__)
#define vpoolMarkFreedDebug(p, e, t, f, l) \
    _vpoolMarkFreedUnsafeDebug(p, e, t, f, l)
#define vpoolMarkFreedUnsafeDebug(p, e, t, f, l) \
    _vpoolMarkFreedDebug(p, e, t, f, l)

#define _vpoolEmpty(p) \
    _vpoolEmptyDebug(p, vmemTAG, __FILE__, __LINE__)

#define _vpoolDestruct(p) \
    _vpoolDestructDebug(p, vmemTAG, __FILE__, __LINE__)
#define _vpoolDestructUnbalanced(p) \
    _vpoolDestructUnbalancedDebug(p, vmemTAG, __FILE__, __LINE__)


#define vpoolGetGlobalEnable()      (_vpoolGlobalEnable)

#else

#define vpoolInit(p, n) \
    _vpoolInitNonDebug(p, n)
#define _vpoolInitDebug(p, n, t, f, l) \
    _vpoolInitNonDebug(p, n)
#define _vpoolDestroyDebug(p, t, f, l) \
    vpoolDestroy(p)
#define vpoolValidate(p) \
    _vpoolValidateNonDebug(p)
#define _vpoolDestroyUnbalancedDebug(p, t, f, l) \
    vpoolDestroyUnbalanced(p)

#define vpoolAlloc(p) \
    _vpoolAllocNonDebug(p)
#define vpoolAllocUnsafe(p) \
    _vpoolAllocUnsafeNonDebug(p)
#define vpoolAllocDebug(p, t, f, l) \
    _vpoolAllocNonDebug(p)
#define vpoolAllocUnsafeDebug(p, t, f, l) \
    _vpoolAllocUnsafeNonDebug(p)

#define vpoolFree(p, e) \
    _vpoolFreeNonDebug(p, e)
#define vpoolFreeUnsafe(p, e) \
    _vpoolFreeUnsafeNonDebug(p, e)
#define vpoolFreeDebug(p, e, t, f, l) \
    _vpoolFreeNonDebug(p, e)
#define vpoolFreeUnsafeDebug(p, e, t, f, l) \
    _vpoolFreeUnsafeNonDebug(p, e)

#define vpoolMarkFreed(p, e) \
    _vpoolMarkFreedNonDebug(p, e)
#define vpoolMarkFreedUnsafe(p, e) \
    _vpoolMarkFreedUnsafeNonDebug(p, e)
#define vpoolMarkFreedDebug(p, e, t, f, l) \
    _vpoolMarkFreedNonDebug(p, e)
#define vpoolMarkFreedUnsafeDebug(p, e, t, f, l) \
    _vpoolMarkFreedUnsafeNonDebug(p, e)

#define _vpoolEmptyDebug(p, t, f, l) \
    _vpoolEmpty(p)

#define vpoolDestroy(p)             vpoolDestroyUnbalanced(p)
#define _vpoolDestruct(p)             _vpoolDestructUnbalanced(p)

#define _vpoolDestructDebug(p, t, f, l) \
    _vpoolDestruct(p)
#define _vpoolDestructUnbalancedDebug(p, t, f, l) \
    _vpoolDestructUnbalanced(p)



#define  vpoolRegisterMonitorProc( _fn ) 	/*EMPTY*/
#define  vpoolUnregisterMonitorProc( _fn ) 	/*EMPTY*/
#define  vpoolSetGlobalEnable( _b )		/*EMPTY*/
#define  vpoolGetGlobalEnable()			FALSE

#endif


#define vpoolGetElemSize(p)       ((p)->elemSize)
#define vpoolGetExpandProc(p)     ((p)->expandProc)
#define vpoolGetMutex(p)	  ((p)->mutex)


/**  monitor events
 **/
#define vpoolGetMonitorEventType(e) ((e)->type)
#define vpoolGetMonitorEventPool(e) ((e)->pool)
#define vpoolGetMonitorEventElem(e) ((e)->elem)
#define vpoolGetMonitorEventTag(e)  ((e)->tag)
#define vpoolGetMonitorEventFile(e) ((e)->file)
#define vpoolGetMonitorEventLine(e) ((e)->line)


/*******************************************
 **  Convenience macros to ease C++ work
 *******************************************/
#define _vpoolAllocType(t, p)						\
   ((t *)vpoolAlloc(p))
#define _vpoolAllocUnsafeType(t, p)					\
   ((t *)vpoolAllocUnsafe(p))

/* for completeness */
#define _vpoolFreeType(t, p, e)						\
   vpoolFree(p, e)
#define _vpoolFreeUnsafeType(t, p, e)					\
   vpoolFreeUnsafe(p, e)

vportBEGIN_MUST_BE_MACRO

#define vpoolLock(p)							\
   vmutexLockWithHandling(p->mutex)
#define vpoolUnlock(p)							\
   vmutexUnlockWithHandling(p->mutex)

vportEND_MUST_BE_MACRO

vportEND_CPLUSPLUS_EXTERN_C


#if (vportCPLUSPLUS_SOURCE)

_vpoolINLINE void * vpool::Alloc()
{ return vpoolAlloc(this); }

_vpoolINLINE void * vpool::AllocUnsafe()
{ return vpoolAllocUnsafe(this); }

_vpoolINLINE void vpool::Free(void *elem)
{ vpoolFree(this, elem); }

_vpoolINLINE void vpool::FreeUnsafe(void *elem)
{ vpoolFreeUnsafe(this, elem); }

#endif /* (vportCPLUSPLUS_SOURCE) */


#endif /* #ifndef vpoolINCLUDED */


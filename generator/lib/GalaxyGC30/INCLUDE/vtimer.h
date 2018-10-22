/* $Id: vtimer.h,v 1.37 1997/06/19 01:16:55 robert Exp $ */

/************************************************************

    vtimer.h

    C Interface file for the Timer Manager

    (c) Copyright Visix Software Inc.
    All rights reserved

************************************************************/

#ifndef vtimerINCLUDED
#define vtimerINCLUDED 1

#ifndef  vportINCLUDED		/* for v*HEADER */
#include <vport.h>
#endif

#ifndef  vstdINCLUDED		/* for vbyte, vbool */
#include vstdHEADER
#endif

#ifndef  vdebugINCLUDED
#include vdebugHEADER
#endif

#ifndef  veventINCLUDED
#include veventHEADER
#endif

#ifndef  vobservableINCLUDED
#include vobservableHEADER
#endif


vportBEGIN_CPLUSPLUS_EXTERN_C


/*
 * * * * * * * * * * * PUBLIC CONSTANT DEFINITIONS  * * * * * * * * * *
 */


/*
 * * * * * * * * * * * * PUBLIC TYPE DEFINITIONS  * * * * * * * * * *
 */


typedef struct vtimer		  vtimer;
typedef struct vtimerClass	  vtimerClass;

typedef void		(*vtimerNoteProc)(vtimer *timer);

typedef void		(*vtimerSyncProc)(void);


/*
 * * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */


void vtimerStartup(
    void
    );

vtimerClass *vtimerGetDefaultClass(
    void
    );

vinstance *vtimerGetInstance(
    vtimer			*timer
    );

vloadable *vtimerGetLoadable(
    vtimer			*timer
    );

vobservable *vtimerGetObservable(
    vtimer			*timer
    );

vtimerClass *vtimerGetClass(
    vtimer			*timer
    );

vtimer *vtimerCreateOfClass(
    vtimerClass			*clas
    );

void vtimerInitOfClass(
    vtimer			*timer, 
    vtimerClass			*clas
    );

vtimer *vtimerCreate(
    void
    );

vtimer *vtimerCreateDebug(
    const char			*tag,
    const char			*file,
    int				 line
    );

void vtimerInit(
    vtimer			*timer
    );

void vtimerDestroy(
    vtimer			*timer
    );

void vtimerCopy(
    const vtimer		*from,
    vtimer			*to
    );

void vtimerCopyInit(
    const vtimer		*from,
    vtimer			*to
    );

void vtimerCopyInitDebug(
    const vtimer		*from,
    vtimer			*to,
    const char			*tag,
    const char			*file,
    int				 line
    );

vtimer *vtimerClone(
    const vtimer		*timer
    );

vtimer *vtimerCloneDebug(
    const vtimer		*timer,
    const char			*tag,
    const char			*file,
    int				 line
    );

vtimer *vtimerLoad(
    vresource			 resource
    );

void vtimerLoadInit(
    vtimer			*timer,
    vresource			 resource
    );

void vtimerStore(
    vtimer			*timer,
    vresource			 resource
    );

vbool vtimerValidate(
    const vtimer		*timer
    );

void vtimerAssert(
    const vtimer		*timer
    );

void vtimerHandledAssert(
    const vtimer		*timer,
    vdebugAssertionHandler	 handler,
    void			*data
    );

void vtimerStart(
    vtimer			*timer
    );

void vtimerStartDebug(
    vtimer			*timer,
    const char			*tag,
    const char			*file,
    int				 line
    );

void vtimerRestart(
    vtimer			*timer
    );

void vtimerRestartDebug(
    vtimer			*timer,
    const char			*tag,
    const char			*file,
    int				 line
    );

void vtimerStop(
    vtimer			*timer
    );

void vtimerStopDebug(
    vtimer			*timer,
    const char			*tag,
    const char			*file,
    int				 line
    );

void vtimerNotify(
    vtimer			*timer
    );

void vtimerSynchronize(
    vtimer			*timer
    );

vbool vtimerIsActive(
    const vtimer		*timer
    );

void vtimerSetData(
    vtimer			*timer,
    void			*data
    );

void *vtimerGetData(
    const vtimer		*timer
    );

void vtimerSetPeriod(
    vtimer			*timer,
    unsigned long		 seconds,
    unsigned long		 nanoseconds
    );

unsigned long vtimerGetPeriodSeconds(
    const vtimer		*timer
    );

unsigned long vtimerGetPeriodNanoseconds(
    const vtimer		*timer
    );

void vtimerSetNotify(
    vtimer			*timer,
    vtimerNoteProc		 notify
    );

vtimerNoteProc vtimerGetNotify(
    const vtimer		*timer
    );

void vtimerSetRecurrent(
    vtimer			*timer
    );

void vtimerSetOneShot(
    vtimer			*timer
    );

vbool vtimerIsRecurrent(
    const vtimer		*timer
    );

void vtimerSetSynchronous(
    vtimer			*timer
    );

void vtimerSetAsynchronous(
    vtimer			*timer
    );

vbool vtimerIsAsynchronous(
    const vtimer		*timer
    );

void vtimerSetSyncProc(
    vtimer			*timer,
    vtimerSyncProc		 syncProc
    );

vtimerSyncProc vtimerGetSyncProc(
    const vtimer		*timer
    );

void vtimerSetPriority(
    vtimer			*timer,
    int				 priority
    );

int vtimerGetPriority(
    const vtimer		*timer
    );

void vtimerDump(
    const vtimer		*timer,
    FILE			*stream
    );


/*
 * * * * * * * * * * * PRIVATE CONSTANT DEFINITIONS  * * * * * * * * * *
 */


enum {
    _vtimerASYNCHRONOUS_FLAG	= 0x01,
    _vtimerDESTROYED_FLAG	= 0x02,
    _vtimerRECURRENT_FLAG	= 0x04,
    _vtimerREQUEST_SYNC_FLAG	= 0x08
};


/*
 * * * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * *
 */


struct vtimer {
    vobservable			 object;

    vtimerSyncProc		 syncher;
    vtimerNoteProc		 notify;
    
    unsigned long		 period_secs;
    unsigned long		 period_nsecs;
    
    void			*data;
    vevent			*event;
    
    short			 priority;
    vbyte			 depth;
    vbyte			 flags;

#if (vdebugDEBUG)
    int				 signature;
#endif
};


#define vtimerCLASS(SUPER, OBJECT)					      \
    vobservableCLASS(SUPER, OBJECT);					      \
    vclassMETHOD(vtimerNOTIFY, (OBJECT *timer));			      \
    vclassMETHOD(vtimerSYNCHRONIZE, (OBJECT *timer))

struct vtimerClass {
    vtimerCLASS(vtimerClass, vtimer);
};


/*
 * deprecated types
 */

typedef vtimerNoteProc vtimerCallbackProc;


/*
 * * * * * * * * * * PRIVATE VARIABLE DECLARATIONS * * * * * * * * * *
 */


/*
 * * * * * * * * * * * PRIVATE FUNCTION PROTOTYPES * * * * * * * * * *
 */


void _vtimerHandledAssert(
    const vtimer		*timer,
    vdebugAssertionHandler	 handler,
    void			*data,
    const char			*tag,
    const char			*file,
    int				 line
    );


#if (vdebugDEBUG)
vtimer *_vtimerCreateDebug(const char *tag, const char *file, int line);
void _vtimerCopyInitDebug(const vtimer *from, vtimer *to,
			 const char *tag, const char *file, int line);
vtimer *_vtimerCloneDebug(const vtimer *timer,
			 const char *tag, const char *file, int line);
void _vtimerRestartDebug(vtimer *timer,
			const char *tag, const char *file, int line);
void _vtimerStopDebug(vtimer *timer,
		     const char *tag, const char *file, int line);
#else
vtimer *_vtimerCreateNondebug(void);
void _vtimerCopyInitNondebug(const vtimer *from, vtimer *to);
vtimer *_vtimerCloneNondebug(const vtimer *timer);
void _vtimerRestartNondebug(vtimer *timer);
void _vtimerStopNondebug(vtimer *timer);
#endif

/*
 * deprecated prototypes
 */

void vtimerSetCallback(
    vtimer			*timer,
    vtimerNoteProc		 callback
    );

vtimerNoteProc vtimerGetCallback(
    vtimer			*timer
    );


/*
 * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * *
 */


#define vtimerGetObservable(t)	  vportBASE_OBJECT(t, object)
#define vtimerGetLoadable(t) \
    vobservableGetLoadable(vtimerGetObservable(t))
#define vtimerGetInstance(t) \
    vloadableGetInstance(vtimerGetLoadable(t))
#define vtimerGetClass(t) \
    ((vtimerClass*)vinstanceGetClass(vtimerGetInstance(t)))

#define vtimerCreateOfClass(c) \
    ((vtimer *) vinstanceCreateOfClass((vinstanceClass *)(c)))
#define vtimerInitOfClass(t,c) \
    vinstanceInitOfClass(vtimerGetInstance(t), (vinstanceClass *)(c))

#define vtimerLoad(r) \
    ((vtimer *) vloadableLoad(r))
#define vtimerLoadInit(t,r) \
    vloadableLoadInit(vtimerGetLoadable(t), (r))
#define vtimerStore(t,r) \
    vloadableStore(vtimerGetLoadable(t), (r))

#define vtimerDump(t, s) \
    vloadableDump(vtimerGetLoadable(t), (s))

#define vtimerHandledAssert(t, h, d)	_vtimerHandledAssert(t, h, d,	\
							     vdebugTAG,	\
							     __FILE__,	\
							     __LINE__)

#if (vdebugDEBUG)

#define vtimerCreate()			_vtimerCreateDebug(vdebugTAG,\
							  __FILE__, __LINE__)
#define vtimerCreateDebug(tg, fl, ln)	_vtimerCreateDebug(tg, fl, ln)
#define vtimerCopyInit(f, t)		_vtimerCopyInitDebug(f, t, vdebugTAG,\
							    __FILE__, __LINE__)
#define vtimerCopyInitDebug(f, t, tg, fl, ln) \
					_vtimerCopyInitDebug(f, t, tg, fl, ln)
#define vtimerClone(t)			_vtimerCloneDebug((t), vdebugTAG,\
							 __FILE__, __LINE__)
#define vtimerCloneDebug(t, tg, fl, ln)	_vtimerCloneDebug((t), tg, fl, ln)
#define vtimerRestart(t)		_vtimerRestartDebug((t), vdebugTAG,\
							   __FILE__, __LINE__)
#define vtimerRestartDebug(t, tg, fl, ln) \
					_vtimerRestartDebug((t), tg, fl, ln)
#define vtimerStop(t)			_vtimerStopDebug((t), vdebugTAG,\
							__FILE__, __LINE__)
#define vtimerStopDebug(t, tg, fl, ln) \
					_vtimerStopDebug((t), tg, fl, ln)

#define vtimerAssert(t)			vtimerHandledAssert((t), NULL, NULL)

#else

#define vtimerCreate()				_vtimerCreateNondebug()
#define vtimerCreateDebug(tg, fl, ln)		_vtimerCreateNondebug()
#define vtimerCopyInit(f, t)			_vtimerCopyInitNondebug(f, t)
#define vtimerCopyInitDebug(f, t, tg, fl, ln)	_vtimerCopyInitNondebug(f, t)
#define vtimerClone(t)				_vtimerCloneNondebug(t)
#define vtimerCloneDebug(t, tg, fl, ln)		_vtimerCloneNondebug(t)
#define vtimerRestart(t)			_vtimerRestartNondebug(t)
#define vtimerRestartDebug(t, tg, fl, ln)	_vtimerRestartNondebug(t)
#define vtimerStop(t)				_vtimerStopNondebug(t)
#define vtimerStopDebug(t, tg, fl, ln)		_vtimerStopNondebug(t)

#define vtimerAssert(t)			((void)0)

/*
 * only inlined in a non debug
 */

#define vtimerSetPeriod(timer, s, ns) \
  {(timer)->period_secs = (s); (timer)->period_nsecs = (ns);}
#define vtimerSetRecurrent(timer) \
  ((timer)->flags |= _vtimerRECURRENT_FLAG)
#define vtimerSetOneShot(timer) \
  ((timer)->flags &= ~_vtimerRECURRENT_FLAG)

#endif

#define vtimerIsActive(timer)		((timer)->event != NULL)

#define vtimerStart(t)	(void)((!vtimerIsActive(t) && (vtimerRestart(t),0)))
#define vtimerStartDebug(t, tag, f, l)	(void)((!vtimerIsActive(t) &&\
					    (vtimerRestartDebug(t,tag,f,l),0)))


#define vtimerGetData(timer)		((timer)->data)
#define vtimerSetData(timer, _data)	((timer)->data = (_data))

#define vtimerGetPeriodSeconds(timer)	((timer)->period_secs)
#define vtimerGetPeriodNanoseconds(timer) \
  ((timer)->period_nsecs)

#define vtimerSetNotify(timer, note) \
  ((timer)->notify = (note))
#define vtimerGetNotify(timer)		((timer)->notify)

#define vtimerIsRecurrent(timer) \
  (((timer)->flags & _vtimerRECURRENT_FLAG) != 0)

#define vtimerSetAsynchronous(timer) \
  ((timer)->flags |= _vtimerASYNCHRONOUS_FLAG)
#define vtimerSetSynchronous(timer) \
  ((timer)->flags &= ~_vtimerASYNCHRONOUS_FLAG)
#define vtimerIsAsynchronous(timer) \
  (((timer)->flags & _vtimerASYNCHRONOUS_FLAG) != 0)

#define vtimerSetPriority(timer, p)	((timer)->priority = (p))
#define vtimerGetPriority(timer)	((timer)->priority)

#define vtimerGetSyncProc(timer)	((timer)->syncher)

/*
 * deprecated functions
 */
    
#define vtimerSetCallback(timer, proc)		vtimerSetNotify(timer, proc)
#define vtimerGetCallback(timer)		vtimerGetNotify(timer)


/*
 * * * * * * * * * * PRIVATE FUNCTION MESSAGE DEFINITIONS * * * * * * * * * *
 */

#define vtimerNotify(t) \
    vclassSend(vtimerGetClass(t), vtimerNOTIFY, (t))
#define vtimerSynchronize(t) \
    vclassSend(vtimerGetClass(t), vtimerSYNCHRONIZE, (t))


vportEND_CPLUSPLUS_EXTERN_C


#endif /* #ifndef vtimerINCLUDED */


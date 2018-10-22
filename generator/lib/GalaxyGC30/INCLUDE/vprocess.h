/* $Id: vprocess.h,v 1.19 1997/08/21 16:41:46 jim Exp $ */

/************************************************************

    vprocess.h

    C Interface file for Process manager

    (c) Copyright 1996 Visix Software Inc.
    All rights reserved

************************************************************/

#ifndef  vprocessINCLUDED
#define  vprocessINCLUDED 1

#ifndef  vportHEADER
#include <vport.h>
#endif

#ifndef  vstdINCLUDED
#include vstdHEADER
#endif

#ifndef  vfsINCLUDED
#include vfsHEADER
#endif

#ifndef  vcharINCLUDED
#include vcharHEADER
#endif

#ifndef  vinstanceINCLUDED
#include vinstanceHEADER
#endif

#ifndef  vtimestampINCLUDED
#include vtimestampHEADER
#endif

#ifndef  vmutexINCLUDED
#include vmutexHEADER
#endif

#if (vportOS_OS2)
# ifndef   vos2INCLUDED
#  include vos2HEADER
# endif
#endif

#if (vportOS_WIN32S)
# ifndef vmswhdrsINCLUDED
#  include vmswhdrsHEADER
# endif
#endif

#if (vportOS_MAC)
#include <AppleEvents.h>
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C

/*===========================================================================*
 * * * * * * * * * * * *  PUBLIC  CONSTANT  DEFINITIONS  * * * * * * * * * * *
 *===========================================================================*/

/*
 * Process Flag Constants
 */

enum
{
    /* 
     * Process States 
     */
    vprocessSTATE_ACTIVE           = 0x0001,
    vprocessSTATE_INACTIVE         = 0x0002,

    /*
     * Process Priorities
     */

    vprocessPRIORITY_HIGH          = 0x0004,
    vprocessPRIORITY_NORMAL        = 0x0008,
    vprocessPRIORITY_IDLE          = 0x0010,

    /*
     * Process Creation
     */

    vprocessCREATION_DETACHED      = 0x0020,
    vprocessCREATION_CONSOLE       = 0x0040,
    vprocessCREATION_STREAM_INPUT  = 0x0080,
    vprocessCREATION_STREAM_OUTPUT = 0x0100,
    vprocessCREATION_STREAM_ERROR  = 0x0200
};


/*
 * Process Flag Group Masks
 */

#define vprocessSTATE_ALL          (                                         \
    vprocessSTATE_ACTIVE |                                                   \
    vprocessSTATE_INACTIVE         )

#define vprocessPRIORITY_ALL       (                                         \
    vprocessPRIORITY_HIGH |                                                  \
    vprocessPRIORITY_NORMAL |                                                \
    vprocessPRIORITY_IDLE          )

#define vprocessCREATION_ALL       (                                         \
    vprocessCREATION_DETACHED |                                              \
    vprocessCREATION_CONSOLE  |                                              \
    vprocessCREATION_STREAM_INPUT |                                          \
    vprocessCREATION_STREAM_OUTPUT |                                         \
    vprocessCREATION_STREAM_ERROR  )


/*
 * Possible return values for vprocessWaitForTermination
 */

enum
{
    vprocessWAIT_TIMED_OUT,
    vprocessWAIT_CANCELLED,
    vprocessWAIT_FAILED,
    vprocessWAIT_SUCCESS
};

/*===========================================================================*
 * * * * * * * * * * * * *  PUBLIC  TYPE  DEFINITIONS  * * * * * * * * * * * *
 *===========================================================================*/

typedef struct vprocess                    vprocess;
typedef struct vprocessClass               vprocessClass;
typedef struct vprocessArgumentTemplate    vprocessArgumentTemplate;
typedef struct vprocessEnvironmentTemplate vprocessEnvironmentTemplate;

typedef void (*vprocessNotifyProc)(
    vprocess		*process
    );

/*
 * HACK
 *
 * Hack type for now, when interfaces are supported, perhaps this will be
 * a genuine class that "implement" a generic stream interface (that we
 * will use with vfs and vcomm objects).
 */

typedef struct vprocessStream              vprocessStream;
typedef vprocessStream                     vprocessInputStream;
typedef vprocessStream                     vprocessOutputStream;

/*===========================================================================*
 * * * * * * * * * * *   PUBLIC  FUNCTION  PROTOTYPES  * * * * * * * * * * * *
 *===========================================================================*/

/*
 * Process class
 */

void
vprocessCancelWaitForTermination(
    vprocess     		*process
    );

vprocess *
vprocessCreate(
    void
    );

vprocess *
vprocessCreateOfClass(
    vprocessClass		*clas
    );

void
vprocessDestroy(
    vprocess     		*process
    );

void
vprocessDump(
    vprocess     		*process,
    FILE                 	*fp
    );

const vprocessArgumentTemplate *
vprocessGetArguments(
    vprocess			*process
    );

vprocessClass *
vprocessGetClass(
    vprocess			*process
    );

int
vprocessGetCreationFlags(
    vprocess			*process
    );

const void *
vprocessGetData(
    vprocess			*process
    );

vprocessClass *
vprocessGetDefaultClass(
    void 
    );

const vprocessEnvironmentTemplate *
vprocessGetEnvironmentVariables(
    vprocess			*process
    );

vprocessOutputStream *  /* this will change, see "HACK" above */
vprocessGetErrorStream(
    vprocess			*process
    );

vprocessInputStream *  /* this will change, see "HACK" above */
vprocessGetInputStream(
    vprocess			*process
    );

vinstance *
vprocessGetInstance(
    vprocess			*process
    );

vprocessNotifyProc
vprocessGetNotify(
    vprocess			*process
    );

vprocessOutputStream *  /* this will change, see "HACK" above */
vprocessGetOutputStream(
    vprocess			*process
    );

int
vprocessGetPriority(
    vprocess			*process
    );

const vchar *
vprocessGetProgramName(
    vprocess			*process
    );

const vfsPath *
vprocessGetProgramPath(
    vprocess			*process
    );

const vfsPath *
vprocessGetWorkingPath(
    vprocess			*process
    );

int
vprocessGetState(
    vprocess			*process
    );

void 
vprocessInit(
    vprocess			*process
    );

void 
vprocessInitOfClass(
    vprocess			*process,
    vprocessClass		*clas
    );

void
vprocessSetArguments(
    vprocess			*process,
    vprocessArgumentTemplate	*args
    );

void
vprocessSetArgumentsOwned(
    vprocess			*process,
    vprocessArgumentTemplate	*args
    );

void
vprocessSetCreationFlags(
    vprocess			*process,
    int				flags
    );

void
vprocessSetData(
    vprocess			*process,
    void				*data
    );

void
vprocessSetEnvironmentVariables(
    vprocess			*process,
    vprocessEnvironmentTemplate	*args
    );

void
vprocessSetEnvironmentVariablesOwned(
    vprocess			*process,
    vprocessEnvironmentTemplate	*args
    );

void
vprocessSetProgramSignature(
    vprocess			*process,
    void                        *signature
    );

void 
vprocessStartup(
    void
    );

void*
vprocessGetProgramSignature(
    vprocess			*process
    );

void
vprocessSetNotify(
    vprocess			*process,
    vprocessNotifyProc		 notify
    );

void
vprocessSetPriority(
    vprocess			*process,
    int			         priority
    );

void
vprocessSetProgramName(
    vprocess			*process,
    const vchar			*name
    );

void
vprocessSetProgramNameScribed(
    vprocess			*process,
    vscribe			*name
    );

void
vprocessSetProgramPath(
    vprocess			*process,
    vfsPath			*path
    );

void
vprocessSetProgramPathOwned(
    vprocess			*process,
    vfsPath			*path
    );

void
vprocessSetWorkingPath(
    vprocess			*process,
    vfsPath			*path
    );

void
vprocessSetWorkingPathOwned(
    vprocess			*process,
    vfsPath			*path
    );

vbool
vprocessStart(
    vprocess			*process
    );

vbool
vprocessTerminate(
    vprocess			*process,
    int                           status
    );

int
vprocessWaitForTermination(
    vprocess			*process,
    vtimestamp			*timeout,
    int				*status
    );

/* 
 * this API will be used to implement an interface and not be exported,
 * see "HACK" above 
 */
int
vprocessStreamRead(
    vprocessInputStream         *stream,
    vbyte                       *buffer,
    size_t                       count
    );

int
vprocessStreamWrite(
    vprocessOutputStream        *stream,
    vbyte                       *buffer,
    size_t                       count
    );

void
vprocessStreamClose(
    vprocessStream              *stream
    );

vbool
vprocessStreamIsOpen(
    vprocessStream              *stream
    );

/*===========================================================================*
 * * * * * * * * * * * *   PRIVATE  CONSTANT  DEFINITIONS  * * * * * * * * * *
 *===========================================================================*/

/*===========================================================================*
 * * * * * * * * * * * *   PRIVATE  TYPE  DEFINITIONS  * * * * * * * * * * * *
 *===========================================================================*/

struct vprocessArgumentTemplate
{
    vstr         *argument;
};

struct vprocessEnvironmentTemplate
{
    vstr         *variable;
    vstr         *value;
};

struct vprocessStream
{
#if (vportOS_UNIX)
    int           fd;
#elif (vportOS_WIN32S)
    HANDLE        handle;
#elif (vportOS_OS2)
    HFILE         hfile;
    vbool         isValid;
#elif (vportMAC_OS)
    int           dummy;
#endif
};
    
vportALIAS(vprocessInputStream, vprocessStream)
vportALIAS(vprocessOutputStream, vprocessStream)


struct vprocess
{
    vinstance                           super;
    void                               *device;
    const vchar                        *progname;
    const vfsPath                      *progpath;
    const vfsPath                      *workpath;
    int                                 flags;
    vprocessNotifyProc                  notify;
    const vprocessArgumentTemplate     *args;
    const vprocessEnvironmentTemplate  *envs;
    void                               *data;
    int                                 exitstatus;
    vprocessStream                      inputStream;
    vprocessStream                      errorStream;
    vprocessStream                      outputStream;
#if (vportMAC_OS)
    long                                signature;
    AEDesc                              appParam;
#endif
};

#define vprocessCLASS(SUPER, PROCESS)                                     \
   vinstanceCLASS(SUPER, PROCESS);                                        \
   vclassMETHOD_RET(vprocessSTART, vbool, (PROCESS *process));            \
   vclassMETHOD_RET(vprocessTERMINATE, vbool,                             \
		    (PROCESS *process, int status));                      \
   vclassMETHOD_RET(vprocessWAIT_FOR_TERMINATION, int,                    \
		    (PROCESS *process, vtimestamp *timestamp,             \
		     int *status));                                       \
   vclassMETHOD_RET(vprocessGET_STATE, int, (PROCESS *process));          \
   vclassMETHOD(vprocessCANCEL_WAIT_FOR_TERMINATION, (PROCESS *process))

struct vprocessClass
{
    vprocessCLASS(vprocessClass, vprocess);
};

/*===========================================================================*
 * * * * * * * * * * *   PRIVATE  FUNCTION  PROTOTYPES * * * * * * * * * * * *
 *===========================================================================*/

void
vprocessSetState(
   vprocess		*process,
   int                   state
   );

void *
vprocessGetDevice(
   vprocess		*process
   );

void
vprocessSetDevice(
   vprocess		*process,
   void                 *device
   );

#if (vportOS_MAC)

int
vprocessSetMacStartupAE(
   vprocess		*process,
    const AppleEvent    *startupEvent
    );
    
#endif /* vportOS_MAC */

/*===========================================================================*
 * * * * * * * * *  PRIVATE  FUNCTION  MACRO  DEFINITIONS  * * * * * * * * * *
 *===========================================================================*/

#define vprocessGetInstance(t) \
   (vportBASE_OBJECT(t, super))

#define vprocessCreate() \
   vprocessCreateOfClass(vprocessGetDefaultClass())

#define vprocessCreateOfClass(c) \
   ((vprocess *) vinstanceCreateOfClass((vinstanceClass *)(c)))

#define vprocessInit(t) \
   vinstanceInit(vprocessGetInstance(t))

#define vprocessInitOfClass(t, c) \
   vinstanceInitOfClass(vprocessGetInstance(t), (vinstanceClass *)(c))

#define vprocessDestroy(t) \
   vinstanceDestroy(vprocessGetInstance(t))

#define vprocessGetClass(t) \
   ((vprocessClass *) vinstanceGetClass(vprocessGetInstance(t)))

#define vprocessGetArguments(t) \
   (t->args)

#define vprocessGetEnvironmentVariables(t) \
   (t->envs)

#define vprocessGetDevice(t) \
   (t->device)

#define vprocessSetDevice(t, d) \
   (t->device = (d))

#define vprocessGetData(t) \
   (t->data)

#define vprocessSetData(t, d) \
   (t->data = (d))

#define vprocessGetCreationFlags(t) \
   (t->flags & vprocessCREATION_ALL)

#define vprocessSetCreationFlags(t, p) \
   (t->flags &= ~vprocessCREATION_ALL); \
   (t->flags |= ((p) & vprocessCREATION_ALL))

#define vprocessStartup() \
   ((void)vprocessGetDefaultClass())

#define vprocessGetPriority(t) \
   (t->flags & vprocessPRIORITY_ALL)

#define vprocessSetPriority(t, p) \
   (t->flags &= ~vprocessPRIORITY_ALL); \
   (t->flags |= ((p) & vprocessPRIORITY_ALL))

#define vprocessSetState(t, p) \
   (t->flags &= ~vprocessSTATE_ALL); \
   (t->flags |= ((p) & vprocessSTATE_ALL))

#define vprocessGetProgramName(t) \
   (t->progname)

#define vprocessSetProgramName(t, c) \
   vprocessSetProgramNameScribed(t, vcharScribe(c))

#define vprocessGetProgramPath(t) \
   (t->progpath)

#define vprocessGetInputStream(t) \
   ((vprocessInputStream *) &((t)->inputStream))

#define vprocessGetOutputStream(t) \
   ((vprocessOutputStream *) &((t)->outputStream))

#define vprocessGetErrorStream(t) \
   ((vprocessOutputStream *) &((t)->errorStream))

#if (vportMAC_OS)
#define vprocessSetProgramSignature(t,c) \
   ((t)->signature = *(long*)(c))
#define vprocessGetProgramSignature(t) \
   ((void*)&((t)->signature))
#else
#define vprocessSetProgramSignature(t,c) \
   ((void)0)
#define vprocessGetProgramSignature(t) \
   ((void*)NULL)
#endif

/*
 * Virtual methods
 */

#define vprocessStart(t) \
   vclassSend(vprocessGetClass(t), vprocessSTART, (t))

#define vprocessTerminate(t, s) \
   vclassSend(vprocessGetClass(t), vprocessTERMINATE, (t, s))

#define vprocessWaitForTermination(t, tmo, s) \
   vclassSend(vprocessGetClass(t), vprocessWAIT_FOR_TERMINATION, (t, tmo, s))

#define vprocessGetState(t) \
   vclassSend(vprocessGetClass(t), vprocessGET_STATE, (t))

#define vprocessCancelWaitForTermination(t) \
   vclassSend(vprocessGetClass(t), vprocessCANCEL_WAIT_FOR_TERMINATION, (t))

vportEND_CPLUSPLUS_EXTERN_C

#endif /* #ifndef vprocessINCLUDED */

/* $Id: vos2.h,v 1.9 1997/08/21 20:08:28 david Exp $ */

#ifndef vos2INCLUDED
#define vos2INCLUDED 1

/*
	+---------------------------------------------------------------+
	|								|
	|	     vos2.h - Visix Os2 Header				|
	|	     ========================================		|
	|								|
	+---------------------------------------------------------------+
	|								|
	| (c) Copyright 1993, Visix Software, Inc., All rights reserved.|
	|								|
	+---------------------------------------------------------------+
	|								|
	|			   DESCRIPTION				|
	|			   ===========				|
	|								|
	|	This file is intended to replace os2.h with		|
	|	the "Right Thing", as defined by OS/2.			|
	|								|
	+---------------------------------------------------------------+
*/


/*
 * Include any files this header depends upon
 */

#ifndef vportINCLUDED
#include <vport.h>
#endif


/*
 * Include the system version of os2.h, if its not too bad
 */

vportBEGIN_CPLUSPLUS_HEADER_PROTECTION

#if (vportOS_OS2)

#if ( ! vportBAD_OS2_HDR )
#define INCL_DOSNMPIPES
#define INCL_DOSFILEMGR
#define INCL_DOSPROCESS
#define INCL_DOSSEMAPHORES
#define INCL_DOSASYNCTIMER
#define INCL_SPL
#define INCL_SPLDOSPRINT
#define INCL_BASE
#define INCL_PM
#define INCL_NLS
#include <os2.h>
#endif

/*-------------------------------------------------------------------------
 *
 * Define the DosQProcStatus call and associated structures.  This is an
 * undocumented API that may change in the future.  It has been tested
 * successfully with OS/2 versions 2.0, 2.1, 2.11, 3.0 and 4.0.  It is known
 * to behave differently on 16-bit OS/2 systems.
 */

/*
 * This macro converts the 16-bit pointers DosQProcStatus returns to 32-bit
 * pointers 
 */
#define DQPS_PTR(ptr, ofs)    ((void *)((char *)(ptr) + (ofs)))

/*
 * The main structure returned by DosQProcStatus.  Note that many of the
 * ULONGs are really pointers that must be run through the DQPS_PTR macro in
 * order to be used in the 32-bit environment.  Lines that are not commented
 * are lines that I have not been able to figure out or find documentation for
 * yet.
 */
typedef struct _DQPS_PROCSTAT
{
    ULONG  summary;
    ULONG  processes;   /* DQPS_PTR(processes,0) is the first DQPS_PROCESS */
    ULONG  semaphores;  /* DQPS_PTR(semaphores,16) is the 1st DQPS_SEMAPHORE */
    ULONG  unknown1;
    ULONG  sharedmemory; /* DQPS_PTR(sharedmemory,0) is the first DQPS_SHMEM */
    ULONG  modules;      /* DQPS_PTR(modules,0) is the firlst DQPS_MODULE */
    ULONG  unknown2;
    ULONG  unknown3;
} DQPS_PROCSTAT;

typedef DQPS_PROCSTAT *PDQPS_PROCSTAT;

/*
 * Describes a process.  To get from one process to the next process, visit
 * the offset after the last thread structure:
 *
 *   nextproc = DQPS_PTR(proc->threadlist, proc->threads * sizeof(DQPS_THREAD))
 *
 * When the process type for the DQPS_PROCESS is 3, you're at the end of the
 * list.  There is probably a better way to determine this, but my only source
 * didn't have one.  This is a bit of a hack.
 */
typedef struct _DQPS_PROCESS
{
    ULONG  type;         /* record type.  Process type == 1 */
    ULONG  threadlist;   /* DQPS_PTR(threadlist,0) is the first DQPS_THREAD */
    USHORT processid;    /* The process ID for this process */
    USHORT parentid;     /* The process ID for this process's parent process */
    ULONG  sessiontype;  /* process type */
    ULONG  status;       /* see status #define's below */
    ULONG  sessionid;    /* The process's session */
    USHORT modulehandle; /* The program module handle for the process */
    USHORT threads;      /* Number of threads for this process */
    ULONG  reserved1;
    ULONG  reserved2;
    USHORT semaphores;   /* Number of 16-bit semaphores for this process */
    USHORT dlls;         /* Number of modules for this process */
    USHORT shrmems;      /* Number of shared memory handles for this process */
    USHORT reserved3;
    ULONG  semlist;      /* Pointer to first 16-bit semaphore (an array) */
    ULONG  dlllist;      /* Pointer to first module (an array of HMTEs */
    ULONG  shrmemlist;   /* Pointer to first shared memory handle (an array) */
    ULONG  reserved4;
} DQPS_PROCESS;

typedef DQPS_PROCESS *PDQPS_PROCESS;

/*
 * The DQPS_PROCESS statusses are:
 *
 * DQPS_STAT_EXITLIST - process is doing ExitList processing
 * DQPS_STAT_EXIT1    - thread #1 is exiting
 * DQPS_STAT_EXITALL  - The whole process is exiting
 * DQPS_STAT_PARSTAT  - The parent cares about termination
 * DQPS_STAT_SYNCH    - Parent did an exec-and-wait
 * DQPS_STAT_DYING    - Process is dying
 * DQPS_STAT_EMBRYO   - Process is in an embyonic state
 *
 * I thin these are bit flags that can be ORed with each other
 */
#define DQPS_STAT_EXITLIST 0x01
#define DQPS_STAT_EXIT1    0x02
#define DQPS_STAT_EXITALL  0x04
#define DQPS_STAT_PARSTAT  0x10
#define DQPS_STAT_SYNCH    0x20
#define DQPS_STAT_DYING    0x40
#define DQPS_STAT_EMBRYO   0x80

/*
 * Describes a thread.  A list of these is attached to each DQPS_PROCESS,
 * pointed to by its threadlist field.  They are an array whose count is
 * specified in the threads field.
 */
typedef struct _DQPS_THREAD
{
    ULONG  type;         /* Record type.  Thread type == 0x100 */
    USHORT threadid;     /* The thread ID */
    USHORT threadslotid; /* Slot ID */
    ULONG  blockid;      /* ID a blocked thread is blocked on */
    ULONG  priority;     /* Thread priority */
    ULONG  systime;      /* Thread system time */
    ULONG  usertime;     /* Thread user time */
    UCHAR  status;       /* see status #define's below */
    UCHAR  reserved1;
    USHORT reserved2;
} DQPS_THREAD;

typedef DQPS_THREAD *PDQPS_THREAD;

/*
 * The DQPS_THREAD statusses are:
 *
 * DQPS_TSTAT_READY   - Ready to run
 * DQPS_TSTAT_BLOCKED - Blocked.  See the blockid field
 * DQPS_TSTAT_RUNNING - Running - only one thread per CPU can be running
 * DQPS_TSTAT_LOADED  - ?????
 */
#define DQPS_TSTAT_READY   1
#define DQPS_TSTAT_BLOCKED 2
#define DQPS_TSTAT_RUNNING 5
#define DQPS_TSTAT_LOADED  9

/*
 * Describes a module.  They are arranged in a linked list, with each module
 * containing a list of submodules that it contains.
 */
typedef struct _DQPS_MODULE
{
  ULONG  nextmodule;   /* DQPS_PTR(nextmodule,0) is the next on the list */
  USHORT modhandle;    /* The module's module handle */
  USHORT modtype;      /* 0 for a 16-bit module, non-0 for 32-bit */
  ULONG  submodules;   /* Number of submodules. */
  ULONG  segments;     /* ??? Number of segments this module defines */
  ULONG  reserved;
  ULONG  namepointer;  /* DQPS_PTR(namepointer,0) is a PSZ with the name */
  USHORT submodule[1]; /* An array of submodule module handles */
} DQPS_MODULE;

typedef DQPS_MODULE *PDQPS_MODULE;

/*
 * Describes a 16-bit semaphore.  They are arranged in a linked list
 */
typedef struct _DQPS_SEMAPHORE
{
  ULONG  nextsem;   /* DQPS_PTR(nextsem,0) is the next on the list */
  USHORT owner;     /* Slot ID of the thread owning this semaphore */
  UCHAR  flag;      /* system semaphore flag bit field describing the sem */
  UCHAR  refs;      /* Reference count on this semaphore */
  UCHAR  requests;  /* Number of requests by semaphore owner */
  UCHAR  reserved1;
  USHORT reserved2;
  USHORT index;
  USHORT dummy;
  UCHAR  name[1];   /* Variable - null terminated name, sans \SEM */
} DQPS_SEMAPHORE;

typedef DQPS_SEMAPHORE *PDQPS_SEMAPHORE;

/*
 * Describes a shared memory block.  They are in a linked list.
 */
typedef struct _DQPS_SHMEM
{
  ULONG  nextseg;  /* DQPS_PTR(nextseg,0) is the next on the list */
  USHORT handle;   /* The shared memory handle */
  USHORT selector; /* Shared memory selector */
  USHORT refs;     /* Reference count */
  UCHAR  name[1];  /* Variable - null terminated name, sans \SHAREMEM\ */
} DQPS_SHMEM;

typedef DQPS_SHMEM *PDQPS_SHMEM;

/*
 * The actual prototype for DosQProcStatus
 *
 * pbuf is a pointer to a buffer that will be filled in with data
 *
 * cbBuf is the size of that buffer.  65535 maximum.
 *
 * The return value is 0 on success.  An error code on failure.
 */
USHORT APIENTRY16 DosQProcStatus(PVOID pBuf, USHORT cbBuf);

/*
 * Map this call onto a system DLL, since the OS2386.LIB import library
 * doesn't define undocumented entry points.
 */
#pragma import (DosQProcStatus, "DOSQPROCSTATUS", "DOSCALLS", 154)


#endif /* if (vportOS_OS2) */

vportEND_CPLUSPLUS_HEADER_PROTECTION


/*
 * Fix up anything that may have been wrong
 */


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

#endif /* vos2INCLUDED */


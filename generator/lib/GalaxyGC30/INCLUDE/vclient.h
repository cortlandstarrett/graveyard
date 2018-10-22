/* $Id: vclient.h,v 1.25 1996/10/03 19:35:25 mikem Exp $ */

/************************************************************

    vclient.h

    C Interface file for the Client Manager

    (c) Copyright Visix Software Inc.
    All rights reserved

************************************************************/

#ifndef vclientINCLUDED
#define vclientINCLUDED

#ifndef  vportINCLUDED
#include <vport.h>
#endif

#ifndef  vstdioINCLUDED
#include vstdioHEADER
#endif

#ifndef  vstdINCLUDED
#include vstdHEADER
#endif

#ifndef  vdebugINCLUDED
#include vdebugHEADER
#endif

#ifndef  vexINCLUDED
#include vexHEADER
#endif

#ifndef  vmemINCLUDED
#include vmemHEADER
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * * * * * * * * * * PUBLIC TYPE DEFINITIONS * * * * * * * * * *
 */

typedef struct vclient              vclient;

typedef void (*vclientShutdownProc)(
    void
    );

typedef void (*vclientStartupProc)(
    void
    );

/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */

int vclientGetModuleMax(
    void
    );

void vclientSetModuleMax(
    int                             count
    );

void vclientSetCurrent(
    vclient                        *client
    );

vclient *vclientGetRoot(
    void
    );

vclient *vclientGetCurrent(
    void
    );

vclient *vclientCreate(
    void
    );

void vclientDestroy(
    vclient                        *client
    );

void **vclientRegisterModule(
    void
    );

void vclientAllocateModule(
    void                          **master,
    size_t                          size
    );

void vclientRegisterShutdown(
    vclientShutdownProc             shutdown
    );

void vclientRegisterGlobalShutdown(
    vclientShutdownProc             shutdown
    );

void vclientRegisterGlobalStartup(
    vclientStartupProc             startup
    );

void vclientCallGlobalStartups(
    void
    );

vbool vclientCallOneGlobalStartup(
    void
    );

void vclientDump(
    vclient                        *client,
    FILE                           *stream
    );

/*
 * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * *
 */

struct vclient {
    vclientShutdownProc            *shutdowns, *shutdownNext, *shutdownMax;
    void                           **masters;
};

/*
 * * * * * * * * * * PRIVATE VARIABLE DECLARATIONS * * * * * * * * * *
 */

extern vportLINK int                          _vclientHaveArgs;
extern vportLINK int                          _vclientInNew;
extern vportLINK int                          _vclientModuleMax;

/*
 * * * * * * * * * * PRIVATE FUNCTION PROTOTYPES * * * * * * * * * *
 */

#if (vdebugDEBUG)

vclient *_vclientCreateDebug(
    const char                     *tag,
    const char                     *file,
    int                             line
    );

#endif

void _vclientSetHaveArgs(
    int                             flag
    );

int _vclientGetHaveArgs(
    void
    );

void _vclientSetInNew(
    int                             flag
    );

int _vclientIsInNew(
    void
    );

void _vclientRegisterGlobalCleanup(
    vclientShutdownProc             shutdown
    );

/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * *
 */

#if (vdebugDEBUG)
#define vclientCreate() \
    _vclientCreateDebug(vmemTAG, __FILE__, __LINE__)
#endif

#define vclientGetModuleMax()      (_vclientModuleMax)

#define _vclientGetHaveArgs()      (_vclientHaveArgs)
#define _vclientSetInNew(f)        (_vclientInNew = (f))
#define _vclientIsInNew()          (_vclientInNew)

vportEND_CPLUSPLUS_EXTERN_C

#endif /* #ifndef vclientINCLUDED */


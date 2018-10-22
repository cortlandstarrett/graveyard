/* $Id: vbuffer.h,v 1.11 1995/10/02 19:14:20 seanm Exp $ */

/************************************************************

    vbuffer.h

    C Interface file for the Buffer Library

    (c) Copyright Visix Software Inc.
    All rights reserved

************************************************************/

#ifndef vbufferINCLUDED
#define vbufferINCLUDED 1

#ifndef  vportINCLUDED
#include <vport.h>		/* for v*HEADER */
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

#ifndef  vpoolINCLUDED
#include vpoolHEADER
#endif

#ifndef  vclientINCLUDED
#include vclientHEADER
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * * * * * * * * * * PUBLIC TYPE DEFINITIONS * * * * * * * * * *
 */

typedef struct vbuffer              vbuffer;
typedef struct vbufferDevice        vbufferDevice;

struct vbufferDevice {
    unsigned int flags;
    void        *instance;
    void (*Init)(vbuffer *buffer);
    void (*Destroy)(vbuffer *buffer);
    int  (*Import)(vbuffer *buffer, vbuffer *source);
    int  (*Export)(vbuffer *buffer, vbuffer *target);
};

/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */

void vbufferStartup(
    void
    );

int vbufferGetClientFlagCount(
    void
    );

vbuffer *vbufferCreate(
    vbuffer                        *group,
    const vbufferDevice            *device,
    const void                     *owner
    );

vbuffer *vbufferFind(
    vbuffer                        *group,
    const vbufferDevice            *device
    );

void vbufferDestroy(
    vbuffer                        *buffer
    );

void vbufferDestroyGroup(
    vbuffer                        *group
    );

void vbufferMark(
    vbuffer                        *buffer
    );

void vbufferValidate(
    vbuffer                        *buffer
    );

void vbufferInvalidate(
    vbuffer                        *buffer
    );

void vbufferLock(
    vbuffer                        *buffer
    );

void vbufferUnlock(
    vbuffer                        *buffer
    );

void vbufferSetShared(
    vbuffer                        *buffer,
    int                             flag
    );

void vbufferSetClientFlag(
    vbuffer                        *buffer,
    int                             flag
    );

void vbufferSetNthClientFlag(
    vbuffer                        *buffer,
    int                             n,
    int                             flag
    );

void vbufferSetOwner(
    vbuffer                        *buffer,
    const void                     *owner
    );

void vbufferSetScalar(
    vbuffer                        *buffer,
    unsigned long                   scalar
    );

void vbufferSetPointer(
    vbuffer                        *buffer,
    const void                     *pointer
    );

int vbufferIsValid(
    vbuffer                        *buffer
    );

int vbufferIsLocked(
    vbuffer                        *buffer
    );

int vbufferIsShared(
    vbuffer                        *buffer
    );

int vbufferGetClientFlag(
    vbuffer                        *buffer
    );

int vbufferGetNthClientFlag(
    vbuffer                        *buffer,
    int                             n
    );

vbuffer *vbufferGetNext(
    vbuffer                        *buffer
    );

const vbufferDevice *vbufferGetDevice(
    vbuffer                        *buffer
    );

const void *vbufferGetOwner(
    vbuffer                        *buffer
    );

unsigned long vbufferGetScalar(
    vbuffer                        *buffer
    );

const void *vbufferGetPointer(
    vbuffer                        *buffer
    );

/*
 * * * * * * * * * * PRIVATE CONSTANT DEFINITIONS * * * * * * * * * *
 */

enum {
    _vbufferVALID                   = 0x0001,
    _vbufferSHARED                  = 0x0002,
    _vbufferCLIENT_FLAG             = 0x0004
};

#define _vbufferCLIENT_FLAG_COUNT 4

/*
 * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * *
 */

struct vbuffer {
    vbuffer                        *next;
    const vbufferDevice            *device;
    const void                     *owner;
    unsigned short                  flags;
    unsigned short                  locks;
    union {
	unsigned long               scalar;
	const void                 *pointer;
    } u;
};

/*
 * * * * * * * * * * PRIVATE FUNCTION PROTOTYPES * * * * * * * * * *
 */

void _vbufferValidate(
    vbuffer                        *buffer
    );

void _vbufferUnlock(
    vbuffer                        *buffer
    );

/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * *
 */

#define vbufferGetClientFlagCount() (_vbufferCLIENT_FLAG_COUNT)

#define vbufferValidate(b) \
    (void)((b)->flags&_vbufferVALID ? 0 : (_vbufferValidate(b), 0))
#define vbufferInvalidate(b)       (void)((b)->flags &= ~_vbufferVALID)
#define vbufferLock(b)             (void)((b)->locks++)
#define vbufferUnlock(b) \
    (void)((b)->locks>0 ? (b)->locks-- : (_vbufferUnlock(b), 0))

#define vbufferSetOwner(b, o)      (void)((b)->owner = (o))
#define vbufferSetScalar(b, n)     (void)((b)->u.scalar = (n))
#define vbufferSetPointer(b, p)    (void)((b)->u.pointer = (p))
#define vbufferSetShared(b, f) \
    (void)((f) ? ((b)->flags |= _vbufferSHARED) : \
	         ((b)->flags &= ~_vbufferSHARED))
#define vbufferSetNthClientFlag(b, n, f) \
    (void)((f) ? ((b)->flags |= (_vbufferCLIENT_FLAG<<(n))) : \
                 ((b)->flags &= ~(_vbufferCLIENT_FLAG<<(n))))
#define vbufferSetClientFlag(b, f)  vbufferSetNthClientFlag(b, 0, f)

#define vbufferIsValid(b)            (((b)->flags&_vbufferVALID)!=0)
#define vbufferIsLocked(b)           ((b)->locks>0)
#define vbufferIsShared(b)           (((b)->flags&_vbufferSHARED)!=0)
#define vbufferGetNthClientFlag(b, n) \
    (((b)->flags&(_vbufferCLIENT_FLAG<<(n)))!=0)
#define vbufferGetClientFlag(b)      vbufferGetNthClientFlag(b, 0)
#define vbufferGetNext(b)            ((b)->next)
#define vbufferGetDevice(b)          ((b)->device)
#define vbufferGetOwner(b)           ((b)->owner)
#define vbufferGetScalar(b)          ((b)->u.scalar)
#define vbufferGetPointer(b)         ((b)->u.pointer)

vportEND_CPLUSPLUS_EXTERN_C

#endif


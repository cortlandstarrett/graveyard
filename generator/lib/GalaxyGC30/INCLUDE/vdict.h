/* $Id: vdict.h,v 1.39 1997/09/15 20:45:28 robert Exp $ */

/************************************************************

    vdict.h

    C Interface file for the Dictionary Manager

    (c) Copyright Visix Software Inc.
    All rights reserved

************************************************************/

#ifndef vdictINCLUDED
#define vdictINCLUDED

#ifndef  vportINCLUDED
#include <vport.h>
#endif

#ifndef  vlimitsINCLUDED
#include vlimitsHEADER
#endif

#ifndef  vfloatINCLUDED
#include vfloatHEADER
#endif

#ifndef  vstdioINCLUDED
#include vstdioHEADER
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

#ifndef  vnameINCLUDED
#include vnameHEADER
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * * * * * * * * * * PUBLIC CONSTANT DEFINITIONS * * * * * * * * * *
 */

#define vdictNULL_SCALAR            LONG_MIN
#define vdictNULL_FLOAT             FLT_MIN

/*
 * * * * * * * * * * PUBLIC TYPE DEFINITIONS * * * * * * * * * *
 */

typedef struct vdict                vdict;
typedef struct vdictSafe            vdictSafe;
typedef struct vdictIterator        vdictIterator;
typedef struct vdictKeyIterator     vdictKeyIterator;

/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */

unsigned long vdictHashGeneric(
    const void                     *p
    );

vdict *vdictCreate(
    vnameHashFunc                   hashFunc
    );

vdict *vdictClone(
    vdict                          *dict
    );

void vdictInit(
    vdict                          *dict,
    vnameHashFunc                   hashFunc
    );

void vdictDestroy(
    vdict                          *dict
    );

void vdictCopy(
    vdict                          *dict,
    vdict                          *target
    );

void vdictCopyInit(
    vdict                          *dict,
    vdict                          *target
    );

void vdictStore(
    vdict                          *dict,
    const void                     *key,
    const void                     *value
    );

void vdictStoreScalar(
    vdict                          *dict,
    const void                     *key,
    long                            value
    );

void vdictStoreFloat(
    vdict                          *dict,
    const void                     *key,
    double                          value
    );

void vdictAdd(
    vdict                          *dict,
    const void                     *key,
    const void                     *value
    );

void vdictAddScalar(
    vdict                          *dict,
    const void                     *key,
    long                            value
    );

void vdictAddFloat(
    vdict                          *dict,
    const void                     *key,
    double                          value
    );

void vdictRemove(
    vdict                          *dict,
    const void                     *key
    );

void vdictRemoveValue(
    vdict                          *dict,
    const void                     *key,
    const void			   *value			
    );

void vdictRemoveScalar(
    vdict                          *dict,
    const void                     *key,
    long			   value			
    );

void vdictRemoveFloat(
    vdict                          *dict,
    const void                     *key,
    double			   value    
    );

const void *vdictLoad(
    vdict                          *dict,
    const void                     *key
    );

long vdictLoadScalar(
    vdict                          *dict,
    const void                     *key
    );

double vdictLoadFloat(
    vdict                          *dict,
    const void                     *key
    );

void vdictDump(
    vdict                          *dict,
    FILE                           *stream
    );

void vdictSetHashSize(
    vdict                          *dict,
    unsigned long                   hashSize
    );

void vdictSetHashDensity(
    vdict                          *dict,
    unsigned                        hashDensity
    );

vnameHashFunc vdictGetHashFunc(
    vdict                          *dict
    );

unsigned long vdictGetHashSize(
    vdict                          *dict
    );

unsigned vdictGetHashDensity(
    vdict                          *dict
    );

unsigned long vdictGetSize(
    vdict                          *dict
    );

void vdictInitKeyIterator(
    vdictKeyIterator		   *iterator,
    vdict			   *dict,
    const void			   *value
    );

int vdictNextKeyIterator(
    vdictKeyIterator		   *iterator
    );

const void *vdictGetKeyIteratorValue(
    vdictKeyIterator		   *iterator
    );

long vdictGetKeyIteratorScalar(
    vdictKeyIterator		   *iterator
    );

double vdictGetKeyIteratorFloat(
    vdictKeyIterator		   *iterator
    );

void vdictDestroyKeyIterator(
    vdictKeyIterator		   *iterator
    );

void vdictInitIterator(
    vdictIterator                  *iterator,
    vdict                          *dict
    );

int vdictNextIterator(
    vdictIterator                  *iterator
    );

void vdictDestroyIterator(
    vdictIterator                  *iterator
    );

const void *vdictGetIteratorKey(
    vdictIterator                  *iterator
    );

const void *vdictGetIteratorValue(
    vdictIterator                  *iterator
    );

long vdictGetIteratorScalar(
    vdictIterator                  *iterator
    );

double vdictGetIteratorFloat(
    vdictIterator                  *iterator
    );


/**  safe dictionary API
 **/
vdictSafe *vdictCreateSafe(
    vnameHashFunc                   hashFunc
    );

void vdictInitSafe(
    vdictSafe                      *dict,
    vnameHashFunc                   hashFunc
    );

void vdictDestroySafe(
    vdictSafe                      *dict
    );

void vdictStoreSafe(
    vdictSafe                      *dict,
    const void                     *key,
    const void                     *value
    );

void vdictStoreSafeScalar(
    vdictSafe                      *dict,
    const void                     *key,
    long                            value
    );

void vdictStoreSafeFloat(
    vdictSafe                      *dict,
    const void                     *key,
    double                          value
    );

void vdictRemoveSafe(
    vdictSafe                      *dict,
    const void                     *key
    );

const void *vdictLoadSafe(
    vdictSafe                      *dict,
    const void                     *key
    );

long vdictLoadSafeScalar(
    vdictSafe                      *dict,
    const void                     *key
    );

double vdictLoadSafeFloat(
    vdictSafe                      *dict,
    const void                     *key
    );

void  vdictSetSafeMutex(
    vdictSafe                      *dict,
    vmutex		           *mutex
    );

vmutex  *vdictGetSafeMutex(
    vdictSafe                      *dict
    );

vdict *vdictGetSafeUnsafe(
    vdictSafe			   *dict
    );

vdict *vdictLockSafeAndGetUnsafe( vdictSafe *dict );
void  vdictUnlockSafe( vdictSafe *dict );


/*
 * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * *
 */

typedef union _vdictValue           _vdictValue;

struct vdict {
    vnameHashFunc                   hashFunc;
    unsigned long                   hashSize;
    unsigned short                  hashDensity;
    unsigned short		    flags;
    unsigned long                   space;
    unsigned long                   minSpace;
    const void                    **keys;
    const void                    **keyMax;
    _vdictValue                    *values;
};

struct vdictSafe {
    vdict			    dict;
    vmutex		           *mutex;
};

struct vdictKeyIterator {
    vdict			   *dict;
    const void			   *key;
    const void			  **scan;
    _vdictValue			   *value;
};

struct vdictIterator {
    vdict                          *dict;
    const void                    **key;
    _vdictValue			   *value;
};

union _vdictValue {
    const void                     *pointer;
    long                            scalar;
    float                           vfloat;
};


#define _vdictDYNAMIC_FLAG	   0x01

/*
 * * * * * * * * * * PRIVATE FUNCTION PROTOTYPES * * * * * * * * * *
 */

#if (vdebugDEBUG)

vdict *_vdictCreateDebug(
    vnameHashFunc                   hashFunc,
    const char                     *tag,
    const char                     *file,
    int                             line
    );

vdict *_vdictCloneDebug(
    vdict                          *dict,
    const char                     *tag,
    const char                     *file,
    int                             line
    );

vdictSafe *_vdictCreateSafeDebug(
    vnameHashFunc                   hashFunc,
    const char                     *tag,
    const char                     *file,
    int                             line
    );

#else

vdict *_vdictCreateNondebug(
    vnameHashFunc                   hashFunc
    );

vdict *_vdictCloneNondebug(
    vdict                          *dict
    );

vdictSafe *_vdictCreateSafeNondebug(
    vnameHashFunc                   hashFunc
    );

#endif

_vdictValue *_vdictLoadRef(
    vdict                          *dict,
    const void                     *key
    );

/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * *
 */

#if (vdebugDEBUG)

#define vdictCreate(f) \
    _vdictCreateDebug(f, vmemTAG, __FILE__, __LINE__)
#define vdictClone(d) \
    _vdictCloneDebug(d, vmemTAG, __FILE__, __LINE__)
#define vdictCreateSafe(f) \
    _vdictCreateSafeDebug(f, vmemTAG, __FILE__, __LINE__)

#else

#define vdictCreate(f) \
    _vdictCreateNondebug(f)
#define vdictClone(d) \
    _vdictCloneNondebug(d)
#define vdictCreateSafe(f) \
    _vdictCreateSafeNondebug(f)

#endif

#define  vdictGetSafeMutex(_dict)		(_dict)->mutex
#define  vdictGetSafeUnsafe(_dict)	((vdict *)vportBASE_OBJECT(_dict, dict))
#define  vdictLockSafeAndGetUnsafe(_dict)	\
    vdictGetSafeUnsafe(_dict);			\
    vmutexLock((_dict)->mutex)

#define  vdictUnlockSafe(_dict)			\
    vmutexUnlock((_dict)->mutex)

#define vdictGetHashFunc(d)       ((d)->hashFunc)
#define vdictGetHashSize(d)       ((d)->hashSize)
#define vdictGetHashDensity(d)    ((d)->hashDensity)
#define vdictGetSize(d)           ((d)->hashSize-(d)->space)

#define vdictDestroyKeyIterator(i) ((void)0)
#define vdictGetKeyIteratorValue(i) \
    ((i)->value->pointer)
#define vdictGetKeyIteratorScalar(i) \
    ((i)->value->scalar)
#define vdictGetKeyIteratorFloat(i) \
    ((i)->value->vfloat)

#define vdictDestroyIterator(i)  ((void)0)
#define vdictGetIteratorKey(i)   (*(i)->key)
#define vdictGetIteratorValue(i) \
    ((i)->value->pointer)
#define vdictGetIteratorScalar(i) \
    ((i)->value->scalar)
#define vdictGetIteratorFloat(i) \
    ((i)->value->vfloat)

vportEND_CPLUSPLUS_EXTERN_C

#endif /* #ifndef vdictINCLUDED */


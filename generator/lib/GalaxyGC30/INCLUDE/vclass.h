/* $Id: vclass.h,v 1.63 1997/09/16 16:33:55 robert Exp $ */

/************************************************************

    vclass.h

    C Interface file for the Class Manager

    (c) Copyright Visix Software Inc.
    All rights reserved

************************************************************/

#ifndef vclassINCLUDED
#define vclassINCLUDED

#ifndef  vportINCLUDED
#include <vport.h>
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

#ifndef  vclientINCLUDED
#include vclientHEADER
#endif

#ifndef  vpoolINCLUDED
#include vpoolHEADER
#endif

#ifndef  vscribeINCLUDED
#include vscribeHEADER
#endif

#ifndef  vcharINCLUDED
#include vcharHEADER
#endif

#ifndef  vnameINCLUDED
#include vnameHEADER
#endif

#ifndef  vdictINCLUDED
#include vdictHEADER
#endif

#ifndef  vinterfaceINCLUDED
#include <vinterface.h>
#endif


vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * * * * * * * * * * PUBLIC MACRO DEFINITIONS  * * * * * * * * * *
 */

#define vclassVARIABLE(n, t)          t n
#define vclassVARIABLE_ARRAY(n, t, s) t n[s]
#define vclassMETHOD(n, a)            void (*n) a
#define vclassMETHOD_RET(n, t, a)     t (*n) a

#ifndef vclassREGISTER_CLASS_INFO
#define vclassREGISTER_CLASS_INFO   vdebugDEBUG
#endif

/*
 * * * * * * * * * * PUBLIC TYPE DEFINITIONS * * * * * * * * * *
 */

#if (!vportCPLUSPLUS_SOURCE)

typedef void                        vclass;
typedef struct vclassRoot           vclassRoot;

#else /* (vportCPLUSPLUS_SOURCE) */

typedef vkind                       vclass;
typedef vkind                       vclassRoot;

#endif /* (vportCPLUSPLUS_SOURCE) */

typedef void (*vclassMethod)(
    void                           *receiver,
    ...
    );

typedef vclass * (*vclassLoadFunc)(
    const vname                    *name
    );

/*
 * removed const for broken sparc compiler (SC2.0.1)
 * put it back when compiler is fixed
 */

typedef /* const */ vname * (*vclassAliasLoader)(
    const void                     *clas,
    const vname                    *type,
    int                             inst
    );

typedef void (*vclassAliasStorer)(
    const void                     *clas,
    const vname                    *type,
    const vname                    *name
    );

typedef struct vclassSubIterator          vclassSubIterator;
typedef struct vclassInterfaceIterator    vclassInterfaceIterator;

/*
 * exceptions
 */

typedef vnameArgTagException            vclassNotUnderstoodException;
typedef vnameArgTagException            vclassNotFoundException;
typedef vexArgException                 vclassUnnamedException;
typedef struct vclassMismatchException  vclassMismatchException;

/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */

/*
 * Class allocation:
 */

vclassRoot *vclassGetRoot(
    void
    );

vclass *vclassSpawn(
    vclass                         *clas, 
    size_t                          size
    );

vclass *vclassClone(
    vclass                         *clas
    );

vclass *vclassReproduce(
    vclass                         *clas
    );

void vclassDestroy(
    vclass                         *clas
    );

vclass *vclassLoad(
    const vchar                    *name
    );

vclass *vclassLoadScribed(
    vscribe                        *scribe
    );

vclass *vclassLoadNamed(
    const vchar                    *name
    );

vclass *vclassLoadNamedScribed(
    vscribe                        *scribe
    );

void vclassSetLoadFunc(
    vclassLoadFunc                  loadFunc
    );

vclassLoadFunc vclassGetLoadFunc(
    void
    );

/*
 * Instance of class allocation:
 */

void *vclassAlloc(
    vclass                         *clas
    );

#if (vdebugDEBUG)

void *vclassAllocDebug(
    vclass                         *clas,
    const char                     *tag,
    const char                     *file,
    int                             line
    );

#endif

void vclassFree(
    vclass                         *clas,
    void                           *elem
    );

void vclassMarkFreed(
    vclass                         *clas,
    void                           *elem
    );

#if (vdebugDEBUG)

void vclassFreeDebug(
    vclass                         *clas,
    void                           *elem,
    const char                     *tag,
    const char                     *file,
    int                             line
    );

void vclassMarkFreedDebug(
    vclass                         *clas,
    void                           *elem,
    const char                     *tag,
    const char                     *file,
    int                             line
    );

#endif

/*
 * Class attributes:
 */

void vclassDump(
    vclass                         *clas,
    FILE                           *stream
    );

void vclassNotifyName(
    const vclass                   *clas
    );

void vclassSetGlobal(
    vclass                         *clas, 
    int                             flag
    );

void vclassSetData(
    vclass                         *clas, 
    void			   *data
    );

void vclassSetName(
    vclass                         *clas, 
    const vchar                    *name
    );

void vclassSetNameScribed(
    vclass                         *clas, 
    vscribe                        *scribe
    );

void vclassSetNameUnregistered(
    vclass                         *clas, 
    const vchar                    *name
    );

void vclassSetNameUnregisteredScribed(
    vclass                         *clas, 
    vscribe                        *scribe
    );

void vclassSetGlobalName(
    vclass                         *clas, 
    const vchar                    *name
    );

void vclassSetGlobalNameScribed(
    vclass                         *clas, 
    vscribe                        *scribe
    );

void vclassSetObjectSize(
    vclass                         *clas, 
    size_t                          objectSize
    );

void vclassSetObjectHeaderSize(
    vclass                         *clas, 
    size_t                          objectHeaderSize
    );

void vclassSet(
    vclass                         *clas, 
    ...
    );

void vclassSetAt(
    vclass                         *clas, 
    ...
    );

void vclassSetDynamic(
    vclass                         *clas,
    const vname                    *name,
    const void                     *value
    );

vclass *vclassGetSuper(
    vclass                         *clas
    );

void *vclassGetData(
    vclass                         *clas
    );

int vclassIsGlobal(
    const vclass                   *clas
    );

const vname *vclassGetName(
    const vclass                   *clas
    );

size_t vclassGetObjectSize(
    const vclass                   *clas
    );

size_t vclassGetObjectHeaderSize(
    const vclass                   *clas
    );

void *vclassGet(
    const vclass                   *clas,
    ...
    );

void *vclassGetAt(
    const vclass                   *clas,
    ...
    );

const void *vclassGetDynamic(
    vclass                         *clas,
    const vname                    *name
    );

const void *vclassBindDynamic(
    vclass                         *clas,
    const vname                    *name
    );

vbool vclassImplementsInterface(
    vclass			   *implementor,
    vinterface			   *interfac
    );

vinterface *vclassImplementInterface(
    vclass			   *implementor,
    vinterface			   *interfac
    );

vinterface *vclassGetInterfaceImplementation(
    vclass			   *implementor,
    vinterface			   *interfac
    );

vinterface *vclassGetInterfaceNameImplementation(
    vclass			   *implementor,
    const vname			   *interface_name
    );

vinterface *vclassBindToInterface(
    vclass			   *implementor,
    vinterface			   *interfac
    );

vinterface *vclassBindToInterfaceName(
    vclass			   *implementor,
    const vname			   *interface_name
    );

/*
 * Class relationships:
 */

int vclassIsKindOf(
    const vclass                   *clas,
    const vclass                   *super
    );

const vclass *vclassGetCommon(
    const vclass                   *clas1,
    const vclass                   *clas2
    );

void vclassInitSubIterator(
    vclassSubIterator              *iterator,
    vclass                         *clas
    );

int vclassNextSubIterator(
    vclassSubIterator              *iterator
    );

void vclassDestroySubIterator(
    vclassSubIterator              *iterator
    );

vclass *vclassGetSubIteratorClass(
    vclassSubIterator              *iterator
    );

void vclassInitInterfaceIterator(
    vclassInterfaceIterator        *iterator,
    vclass                         *clas
    );

int vclassNextInterfaceIterator(
    vclassInterfaceIterator        *iterator
    );

void vclassDestroyInterfaceIterator(
    vclassInterfaceIterator        *iterator
    );

vinterface *vclassGetInterfaceIteratorImplementation(
    vclassInterfaceIterator        *iterator
    );

/*
 * Class aliases:
 */

const vname *vclassLoadAlias( 
    const vclass                   *clas, 
    const vname                    *type,
    int                             inst
    );

void vclassStoreAlias( 
    const vclass                   *clas, 
    const vname                    *type, 
    const vname                    *name 
    );

vclassAliasLoader vclassGetAliasLoader( 
    void 
    );

void vclassSetAliasLoader( 
    vclassAliasLoader               loader 
    );

vclassAliasStorer vclassGetAliasStorer( 
    void 
    );

void vclassSetAliasStorer( 
    vclassAliasStorer               storer 
    );
 
/*
 * Class message sending:
 */

void vclassSend(
    const vclass                   *clas,
    ...
    );

void vclassSendSuper(
    const vclass                   *clas,
    ...
    );

void vclassSendDynamic(
    const vclass                   *clas,
    const vname                    *selector,
    ...
    );


/*
 * Not Understood exception:
 */

const vexClass *vclassGetNotUnderstoodExceptionClass(
    void
    );

vclassNotUnderstoodException *vclassGetNotUnderstoodException(
    void
    );

const vname *vclassGetNotUnderstoodExceptionSelector(
    vclassNotUnderstoodException   *exception
    );

void vclassNotUnderstoodExceptionSELECTOR(
    void                           *exception,
    va_list                        *args
    );


/*
 * Not Found exception:
 */

const vexClass *vclassGetNotFoundExceptionClass(
    void
    );

vclassNotFoundException *vclassGetNotFoundException(
    void
    );

const vname *vclassGetNotFoundExceptionName(
    vclassNotFoundException *exception  
    );

void vclassNotFoundExceptionNAME(
    void                           *exception,
    va_list                        *args
    );


/*
 * Unnamed exception:
 */

const vexClass *vclassGetUnnamedExceptionClass(
    void
    );

vclassUnnamedException *vclassGetUnnamedException(
    void
    );


/*
 * Mismatch exception:
 */

const vexClass *vclassGetMismatchExceptionClass(
    void
    );

vclassMismatchException *vclassGetMismatchException(
    void
    );

const vname *vclassGetMismatchExceptionExpected(
    vclassMismatchException *exception  
    );

const vname *vclassGetMismatchExceptionFound(
    vclassMismatchException *exception  
    );

void vclassMismatchExceptionEXPECTED(
    void                           *exception,
    va_list                        *args
    );

void vclassMismatchExceptionFOUND(
    void                           *exception,
    va_list                        *args
    );


/*
 * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * *
 */

#if (!vportCPLUSPLUS_SOURCE)

#define vclassROOT(SUPER)                                                     \
    void                     	   *data;                                     \
    SUPER                          *super;                                    \
    vclass                        **subs, **subNext, **subMax;                \
    vclient                        *client;                                   \
    const vname                    *name;                                     \
    size_t                          size;                                     \
    size_t                          objectSize;                               \
    size_t			    objectHeaderSize;			      \
    vpool                          *pool;                                     \
    vdict                          *dict;                                     \
    vdict                          *interfaceDict;                            \
    vclassMETHOD(vclassNOTIFY_NAME, (SUPER *clas))

struct vclassRoot {
    vclassROOT(vclassRoot);
};

struct vclassSubIterator {
    vclass                         **scan;
    vclass                         **stop;
    vclient                        *client;
};

struct vclassInterfaceIterator {
    vinterface                **interfaces, **current, **end;
};

#else /* (vportCPLUSPLUS_SOURCE) */

struct vclassSubIterator {
    const vkind                    *base;
    int                             index, count;
};

#endif /* (vportCPLUSPLUS_SOURCE) */


/*
 * exceptions 
 */

struct vclassMismatchException {
    vexArgException                 parent;
    const vname                    *expected;
    const vname                    *found;
};

/*
 * * * * * * * * * * PRIVATE FUNCTION PROTOTYPES * * * * * * * * * *
 */

#if (vdebugDEBUG)

vclass *_vclassSpawnDebug(
    vclass                         *clas, 
    size_t                          size,
    const char                     *tag,
    const char                     *file,
    int                             line
    );

vclass *_vclassCloneDebug(
    vclass                         *clas,
    const char                     *tag,
    const char                     *file,
    int                             line
    );

#endif

vclassMethod _vclassBindMethodDynamic(
    vclass                         *clas,
    const vname                    *name
    );

const void *_vclassGetInterface(
    vclass                         *clas,
    const vname                    *name
    );

const void *_vclassBindInterface(
    vclass			   *clas,
    const vname			   *key
    );

void _vclassSetInterface(
    vclass                         *clas,
    const vname                    *name,
    const void                     *value
    );

/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * *
 */

#if (!vportCPLUSPLUS_SOURCE)

#if (vdebugDEBUG)
#define vclassSpawn(c, n) \
    _vclassSpawnDebug(c, n, vmemTAG, __FILE__, __LINE__)
#define vclassClone(c) \
    _vclassCloneDebug(c, vmemTAG, __FILE__, __LINE__)
#endif

#define vclassReproduce(c)         vclassSpawn(c, ((vclassRoot*)(c))->size)
#define vclassLoad(s)              vclassLoadScribed(vcharScribe(s))
#define vclassLoadNamedScribed(s)  vclassLoadNamed(vnameInternGlobalScribed(s))

#if (vdebugDEBUG)
#define vclassAlloc(c) \
    vclassAllocDebug(c, vmemTAG, __FILE__, __LINE__)
#define vclassFree(c, e) \
    vclassFreeDebug(c, e, vmemTAG, __FILE__, __LINE__)
#define vclassMarkFreed(c, e) \
    vclassMarkFreedDebug(c, e, vmemTAG, __FILE__, __LINE__)
#endif

#define vclassNotifyName(c)         vclassSend(c, vclassNOTIFY_NAME, (c))

#define vclassSetData(c, d)	  (((vclassRoot*)(c))->data = (d))
#define vclassSetName(c, s)         vclassSetNameScribed(c, vcharScribe(s))
#define vclassSetNameUnregistered(c, s) \
    vclassSetNameUnregisteredScribed(c, vcharScribe(s))
#define vclassSetGlobalName(c, s) \
    vclassSetGlobalNameScribed(c, vcharScribe(s))
#define vclassSet(c, n, v)        ((c)->n = (v))
#define vclassSetAt(c, n, i, v)   ((c)->n[i] = (v))

#define vclassGetSuper(c)         	((c)->super)
#define vclassGetData(c)         	(((vclassRoot*)(c))->data)
#define vclassIsGlobal(c)         	(((vclassRoot*)(c))->client==NULL)
#define vclassGetName(c)          	(((vclassRoot*)(c))->name)
#define vclassGetObjectSize(c)    	(((vclassRoot*)(c))->objectSize)
#define vclassGetObjectHeaderSize(c)    (((vclassRoot*)(c))->objectHeaderSize)
#define vclassGet(c, n)           	((c)->n)
#define vclassGetAt(c, n, i)      	((c)->n[i])

#define vclassDestroySubIterator(i)
#define vclassGetSubIteratorClass(i) (*(i)->scan)

#define vclassSend(c, s, a)       ((*(c)->s) a)
#define vclassSendSuper(c, s, a)  ((*(c)->super->s) a)
#define vclassSendDynamic(c, s, a) ((*_vclassBindMethodDynamic(c, s)) a)

#define vclassGetInterfaceImplementation(c,i) \
    vclassGetInterfaceNameImplementation(c,vclassGetName(i))
#define vclassBindToInterface(c,i) \
    vclassBindToInterfaceName(c,vclassGetName(i))

#endif /* (!vportCPLUSPLUS_SOURCE) */

#define vclassGetNotUnderstoodException() \
    ((vclassNotUnderstoodException*) \
         vexGetExceptionOfClass(vclassGetNotUnderstoodExceptionClass()))
#define vclassGetNotUnderstoodExceptionSelector(e) \
    vnameGetArgExceptionTag(e)

#define vclassNotUnderstoodExceptionSELECTOR    vnameArgTAG

#define vclassGetNotFoundException() \
    ((vclassNotFoundException*) \
         vexGetExceptionOfClass(vclassGetNotFoundExceptionClass()))
#define vclassGetNotFoundExceptionName(e) \
    vnameGetArgExceptionTag(e)

#define vclassNotFoundExceptionNAME             vnameArgTAG

#define vclassGetUnnamedException() \
    ((vclassUnnamedException*) \
         vexGetExceptionOfClass(vclassGetUnnamedExceptionClass()))

#define vclassGetMismatchException() \
    ((vclassMismatchException*) \
         vexGetExceptionOfClass(vclassGetMismatchExceptionClass()))
#define vclassGetMismatchExceptionExpected(e) ((e)->expected)
#define vclassGetMismatchExceptionFound(e) ((e)->found)


vportEND_CPLUSPLUS_EXTERN_C


#ifdef  vportNULL_HEADER
#undef  vclassHEADER
#define vclassHEADER vportNULL_HEADER
#endif


#endif /* #ifndef vclassINCLUDED */


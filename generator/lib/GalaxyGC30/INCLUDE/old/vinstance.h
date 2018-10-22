/* $Id: vinstance.h,v 1.27 1997/09/05 18:55:22 robert Exp $ */

/************************************************************

    vinstance.h

    C Interface file for the Class Manager instances

    (c) Copyright Visix Software Inc.
    All rights reserved

************************************************************/

#ifndef vinstanceINCLUDED
#define vinstanceINCLUDED 1

#ifndef  vportINCLUDED
#include <vport.h>
#endif

#ifndef  vdebugINCLUDED
#include vdebugHEADER
#endif

#ifndef  vmemINCLUDED
#include vmemHEADER
#endif

#ifndef  vclassINCLUDED
#include vclassHEADER
#endif

#if (vportCPLUSPLUS_SOURCE)
#ifndef  vkindINCLUDED          /* needed only for C++ */
#include vkindHEADER
#endif
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * * * * * * * * * * PUBLIC TYPE DEFINITIONS * * * * * * * * * *
 */

typedef struct vinstance            vinstance;
typedef struct vinstanceClass       vinstanceClass;

#if (vdebugDEBUG)
typedef vinstance *(*vinstanceAllocFunc)(vinstanceClass *clas, 
                                         const char *module, const char *file,
                                         int line);
#else
typedef vinstance *(*vinstanceAllocFunc)(vinstanceClass *clas);
#endif

typedef void (*vinstanceDestroyFunc)(vinstance *instance);
typedef void (*vinstanceFreeFunc)(vinstance *instance);
typedef void (*vinstancePreserveFunc)(vinstance *instance);

typedef vinstance *(*vinstanceResolveFunc)(vscribe *path, 
										   vinstanceClass *clas);

typedef struct vinstanceNotFoundException vinstanceNotFoundException;

/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */

void vinstanceStartup(void);

vinstanceClass *vinstanceGetDefaultClass(
    void
    );

vinstance *vinstanceCreateOfClass(
    vinstanceClass                 *clas
    );

void vinstanceInitOfClass(
    vinstance                      *instance,
    vinstanceClass                 *clas
    );

void vinstanceInitClass(
    vinstance                      *instance,
    vinstanceClass                 *clas
    );

void vinstanceDestroy(
    vinstance                      *instance
    );

void vinstanceDestroyLater(
    vinstance                      *instance
    );

void vinstancePreserve(
    vinstance                      *instance
    );

vinstance *vinstanceResolve(	
	const vchar					   *path
	);

vinstance *vinstanceResolveScribed(	
	vscribe						   *path
	);

vinstance *vinstanceResolveLiteral(	
	const vchar					   *path
	);

vinstance *vinstanceResolveOfClass(	
	const vchar					   *path,
	vinstanceClass				   *clas
	);

vinstance *vinstanceResolveOfClassScribed(	
	vscribe						   *path,
	vinstanceClass				   *clas
	);

vinstance *vinstanceResolveOfClassLiteral(	
	const char					   *path,
	vinstanceClass				   *clas
	);

void vinstanceTrace(
    vinstance                      *instance
    );

vinstanceClass *vinstanceGetClass(
    vinstance                      *instance
    );

size_t vinstanceGetSize(
    vinstance                      *instance
    );

int vinstanceIsKindOf(
    const vinstance                *instance,
    const void                     *clas
    );

vinstance *vinstanceAlloc(
    vinstanceClass                 *clas
    );

void vinstanceFree(
    vinstance                      *instance
    );

void vinstanceMarkFreed(
    vinstance                      *instance
    );

vinstanceAllocFunc vinstanceGetAllocFunc(
    void
    );

void vinstanceSetAllocFunc(
    vinstanceAllocFunc              func
    );

vinstanceFreeFunc vinstanceGetFreeFunc(
    void
    );

void vinstanceSetFreeFunc(
    vinstanceFreeFunc               func
    );

vinstanceFreeFunc vinstanceGetMarkFreedFunc(
    void
    );

void vinstanceSetMarkFreedFunc(
    vinstanceFreeFunc               func
    );

vinstanceDestroyFunc vinstanceGetDestroyFunc(
    void
    );

void vinstanceSetDestroyFunc(
    vinstanceDestroyFunc                    func
    );

vinstancePreserveFunc vinstanceGetPreserveFunc(
    void
    );

void vinstanceSetPreserveFunc(
    vinstancePreserveFunc                    func
    );

vinstanceResolveFunc vinstanceGetResolveFunc(
    void
    );

void vinstanceSetResolveFunc(
    vinstanceResolveFunc              func
    );

/*
 * Exceptions:
 */

const vexClass *vinstanceGetNotFoundExceptionClass(
    void
    );

vinstanceNotFoundException *vinstanceGetNotFoundException(
    void
    );

const vchar *vinstanceGetNotFoundExceptionPath(
    vinstanceNotFoundException *exception  
    );

vinstanceClass *vinstanceGetNotFoundExceptionResultClass(
    vinstanceNotFoundException *exception  
    );

void vinstanceNotFoundExceptionPATH(
    void                           *exception,
    va_list                        *args
    );

void vinstanceNotFoundExceptionRESULT_CLASS(
    void                           *exception,
    va_list                        *args
    );

/*
 * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * *
 */

struct vinstance {
    vinstanceClass                 *clas;
};
  
#define vinstanceCLASS(SUPER, INSTANCE)                                       \
    vclassROOT(SUPER);                                                        \
    vclassMETHOD(vinstanceINIT, (INSTANCE *instance));                        \
    vclassMETHOD(vinstanceDESTROY, (INSTANCE *instance));				      \
    vclassMETHOD(vinstanceTRACE, (INSTANCE *instance))

struct vinstanceClass {
    vinstanceCLASS(vinstanceClass, vinstance);
};

struct vinstanceNotFoundException
{
  vexException		super;
  const vchar		*path;
  vinstanceClass	*resultClass;
};

/*
 * * * * * * * * * * PRIVATE VARIABLES * * * * * * * * * *
 */

extern vportLINK vinstanceAllocFunc   _vinstanceAllocFunc;
extern vportLINK vinstanceFreeFunc    _vinstanceFreeFunc;
extern vportLINK vinstanceFreeFunc    _vinstanceMarkFreedFunc;
extern vportLINK vinstanceDestroyFunc _vinstanceDestroyFunc;
extern vportLINK vinstancePreserveFunc _vinstancePreserveFunc;
extern vportLINK vinstanceResolveFunc _vinstanceResolveFunc;

/*
 * * * * * * * * * * PRIVATE FUNCTION PROTOTYPES * * * * * * * * * *
 */

#if (vdebugDEBUG)
vinstance *_vinstanceAllocDebug(vinstanceClass *clas, 
                                const char *tag, const char *file, 
                                int line);

vinstance *_vinstanceCreateOfClassDebug(vinstanceClass *clas,
                                        const char *tag, const char *file,
                                        int line);
#endif


#if (!vportCPLUSPLUS_SOURCE)

#if (vportLIFETIME)

enum
{
    _vinstanceLIFETIME_INIT,
    _vinstanceLIFETIME_DESTROY,
    _vinstanceLIFETIME_DESTROYED
};

typedef void (*_vinstanceLifetimeProc)(vinstance *instance, int message);

_vinstanceLifetimeProc _vinstanceGetLifetimeProc();
void _vinstanceSetLifetimeProc(_vinstanceLifetimeProc lifetimeProc);

extern vportLINK _vinstanceLifetimeProc _vinstanceCurrentLifetimeProc;

#endif /* #if (vportLIFETIME) */

#endif /* #if (!vportCPLUSPLUS_SOURCE) */


/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * *
 */

#if (!vportCPLUSPLUS_SOURCE)

#if (vdebugDEBUG)
#define vinstanceCreateOfClass(c) \
    _vinstanceCreateOfClassDebug(c, vmemTAG, __FILE__, __LINE__)
#endif

#define vinstanceInitClass(i, c)  ((i)->clas = (c))

#define vinstanceGetClass(i)      ((i)->clas)
#define vinstanceGetSize(i)         vclassGetObjectSize((i)->clas)
#define vinstanceIsKindOf(i, c)     vclassIsKindOf((i)->clas, c)

#define vinstanceTrace(i)		   vclassSend(vinstanceGetClass(i), \
											  vinstanceTRACE, (i))

#endif /* (!vportCPLUSPLUS_SOURCE) */

#define vinstanceGetNotFoundException() \
	((vinstanceNotFoundException *) \
	 vexGetExceptionOfClass(vinstanceGetNotFoundExceptionClass()))
#define vinstanceGetNotFoundExceptionPath(e) \
    ((e)->path)
#define vinstanceGetNotFoundExceptionResultClass(e) \
    ((e)->resultClass)

#if (!vportCPLUSPLUS_SOURCE)

#if (vdebugDEBUG)
#define vinstanceAlloc(c)            (*_vinstanceAllocFunc)(c, vmemTAG, \
                                                            __FILE__, __LINE__)
#define _vinstanceAllocDebug(c,t,f,l) (*_vinstanceAllocFunc)(c,t,f,l)
#else
#define vinstanceAlloc(c)            (*_vinstanceAllocFunc)(c)
#endif

#define vinstanceMarkFreed(c)      (*_vinstanceMarkFreedFunc)(c)
#define vinstanceFree(c)           (*_vinstanceFreeFunc)(c)
#define vinstanceDestroy(c)        (*_vinstanceDestroyFunc)(c)
#define vinstancePreserve(c)       (*_vinstancePreserveFunc)(c)

#endif /* (!vportCPLUSPLUS_SOURCE) */

#define vinstanceGetAllocFunc()    (_vinstanceAllocFunc)
#define vinstanceSetAllocFunc(f)   (_vinstanceAllocFunc = (f))

#define vinstanceGetFreeFunc()     (_vinstanceFreeFunc)
#define vinstanceSetFreeFunc(f)   (_vinstanceFreeFunc = (f))

#define vinstanceGetMarkFreedFunc()     (_vinstanceMarkFreedFunc)
#define vinstanceSetMarkFreedFunc(f)   (_vinstanceMarkFreedFunc = (f))

#define vinstanceGetDestroyFunc()  (_vinstanceDestroyFunc)
#define vinstanceSetDestroyFunc(f) (_vinstanceDestroyFunc = (f))

#define vinstanceGetResolveFunc()  (_vinstanceResolveFunc)
#define vinstanceSetResolveFunc(f) (_vinstanceResolveFunc = (f))

#define vinstanceResolve(p) \
	(*_vinstanceResolveFunc)(vcharScribe(p), vinstanceGetDefaultClass())
#define vinstanceResolveScribed(p) \
	(*_vinstanceResolveFunc)(p, vinstanceGetDefaultClass())
#define vinstanceResolveLiteral(p) \
	(*_vinstanceResolveFunc)(vcharScribeLiteral(p), vinstanceGetDefaultClass())
#define vinstanceResolveOfClass(p,c) \
	(*_vinstanceResolveFunc)(vcharScribe(p), c)
#define vinstanceResolveOfClassScribed(p,c) \
	(*_vinstanceResolveFunc)(p, c)
#define vinstanceResolveOfClassLiteral(p,c) \
	(*_vinstanceResolveFunc)(vcharScribeLiteral(p), c)

/*
 * * * * * * * * * * PRIVATE FUNCTION MESSAGE DEFINITIONS * * * * * * * * * *
 */

vportEND_CPLUSPLUS_EXTERN_C

#endif /* #ifndef vinstanceINCLUDED */

/*
 * Formatting information for emacs
 *
 * Local Variables:
 * c-argdecl-indent:4
 * c-brace-imaginary-offset:0
 * c-brace-offset:-4
 * c-continued-brace-offset:0
 * c-continued-statement-offset:4
 * c-extra-brace-offset:0
 * c-file-offsets:((block-open . -))
 * c-file-style:"BSD"
 * c-indent-level:4
 * c-label-offset:-4
 * tab-stop-list:(4 8 12 16 20 24 28 32 36 40 44 48 52 56 60 64 68 72 76 80) 
 * tab-width:4
 * End:
 */


/* $Id: vmodule.h,v 1.11 1997/08/25 19:20:39 jim Exp $ */

/****************************************************************
 *
 * vmodule.h
 *
 * C Interface file for the Dynamic Code Loader Module.
 *
 * Copyright (c) Visix Software, Incorporated
 * All Rights Reserved
 *
 ****************************************************************/

#ifndef vmoduleINCLUDED
#define vmoduleINCLUDED 1

#ifndef vportINCLUDED
#include <vport.h>
#endif

#ifndef vclassINCLUDED
#include vclassHEADER
#endif

#ifndef vfsINCLUDED
#include vfsHEADER
#endif

#ifndef vscribeINCLUDED
#include vscribeHEADER
#endif

#ifndef vinstanceINCLUDED
#include vinstanceHEADER
#endif


vportBEGIN_CPLUSPLUS_EXTERN_C

/****************************************************************
 * Public constant definitions.
 ****************************************************************/

/****************************************************************
 * Public type definitions.
 ****************************************************************/

typedef struct vmoduleClass	vmoduleClass;
typedef struct vmodule		vmodule;

typedef void (*vmoduleShutdownProc)(
    void
    );

typedef void (*vmoduleStartupProc)(
    vmodule *module
    );

/****************************************************************
 * Public function prototypes.
 ****************************************************************/

void vmoduleStartup(
   void
   );

vmoduleClass *vmoduleGetDefaultClass(
   void
   );

vscribe *vmoduleScribeLibraryNameFromBaseScribed(
    vscribe *base
    );

vscribe *vmoduleScribeLibraryNameFromVersionedBaseScribed(
    vscribe *base,
    int      version
    );

vscribe *vmoduleScribeVisixLibraryNameFromBaseScribed(
    vscribe *base
    );

vscribe *vmoduleScribeVisixLibraryNameFromVersionedBaseScribed(
    vscribe *base,
    int      version
    );

void vmoduleAddSearchPathOwned(
    vfsPath     *path
    );

vmoduleClass *vmoduleGetClass(
   vmodule	*module
   );

vinstance *vmoduleGetInstance(
   vmodule	*module
   );

vmodule *vmoduleCreateOfClass(
   vmoduleClass	*clas
   );

vmodule *vmoduleCreate(
   void
   );

void vmoduleInitOfClass(
   vmodule	*module,
   vmoduleClass	*clas
   );

void vmoduleInit(
   vmodule	*module
   );

void vmoduleDestroy(
   vmodule	*module
   );

void vmoduleAttach(
   vmodule	*module,
   vfsPath	*path
   );

void vmoduleAttachSearchScribed(
   vmodule	*module,
   vscribe      *name
   );

void vmoduleDetach(
   vmodule	*module
   );

void vmoduleSetStartupSymbol(
   vmodule	*module,
   vchar        *name
   );

void vmoduleSetStartupSymbolScribed(
   vmodule	*module,
   vscribe      *name
   );

void vmoduleRegisterShutdown(
   vmodule	*module,
   vmoduleShutdownProc	proc
   );

void *vmoduleGetSymbol(
   vmodule	*module,
   const vchar	*symbol
   );

void *vmoduleGetSymbolScribed(
   vmodule	*module,
   vscribe	*symbol
   );

vfsPath *vmoduleGetPath(
   vmodule	*module
   );

vbool vmoduleIsAttached(
   vmodule	*module
   );

void vmoduleDump(
   vmodule	*module,
   FILE		*stream
   );


/****************************************************************
 * Private constant definitions.
 ****************************************************************/

enum {
   _vmoduleATTACHED	 = 0x01
   };

/****************************************************************
 * Private type definitions.
 ****************************************************************/

/*
 * Module class and instance.
 */

typedef struct _vmoduleInfo	_vmoduleInfo;

#define vmoduleCLASS(CLASS, OBJECT)					\
   vinstanceCLASS(CLASS, OBJECT);					\
   vclassMETHOD(vmoduleATTACH, (OBJECT *module, vfsPath *path));	\
   vclassMETHOD_RET(vmoduleGET_SYMBOL_SCRIBED, void *,			\
		    (OBJECT *module, vscribe *symbol));			\
   vclassMETHOD(vmoduleDETACH, (OBJECT *module));			\
   vclassMETHOD(vmoduleDUMP,   (OBJECT *module, FILE *stream));         \
   vclassMETHOD(vmoduleATTACH_SEARCH, (OBJECT *module, vscribe *name)); \
   vclassMETHOD(vmoduleSET_STARTUP_SYMBOL_SCRIBED,                      \
			(OBJECT *module, vscribe *name));               \
   vclassMETHOD(vmoduleREGISTER_SHUTDOWN,                               \
			(OBJECT *module, vmoduleShutdownProc proc))

struct vmoduleClass {
   vmoduleCLASS(vmoduleClass, vmodule);
   };

struct vmodule {
   vinstance		 super;
   int			 flags;
   vfsPath		*path;
   vchar		*startupSymbol;
   vmoduleShutdownProc	*shutdowns, *shutdownNext, *shutdownMax;
   _vmoduleInfo	*info;
   };

/****************************************************************
 * Private variable declarations.
 ****************************************************************/

/****************************************************************
 * Private function prototypes.
 ****************************************************************/

/****************************************************************
 * Private function macro definitions.
 ****************************************************************/

#define vmoduleGetClass(m)						\
   ((vmoduleClass *)vinstanceGetClass((vinstance *)(m)))

#define vmoduleGetInstance(m)						\
   ((vinstance *)vportBASE_OBJECT((m), super))

#define vmoduleCreateOfClass(c)						\
   ((vmodule *)vinstanceCreateOfClass((vinstanceClass *)(c)))

#define vmoduleCreate()							\
   vmoduleCreateOfClass(vmoduleGetDefaultClass())

#define vmoduleInitOfClass(m, c)					\
   vinstanceInitOfClass(vmoduleGetInstance(m), (vinstanceClass *)(c))

#define vmoduleInit(m)							\
   vmoduleInitOfClass((m), vmoduleGetDefaultClass())

#define vmoduleDestroy(m)						\
   vinstanceDestroy(vmoduleGetInstance(m))

#define vmoduleGetSymbol(m, s)						\
   vmoduleGetSymbolScribed((m), vcharScribe(s))

#define vmoduleSetStartupSymbol(m, s)					\
   vmoduleSetStartupSymbolScribed((m), vcharScribe(s))

#define vmoduleGetPath(m)						\
   ((m)->path)

#define vmoduleIsAttached(m)						\
   (((m)->flags & _vmoduleATTACHED) ? vTRUE : vFALSE)

/****************************************************************
 * Private function message definitions.
 ****************************************************************/

#define vmoduleDump(m, s)						\
   vclassSend(vmoduleGetClass(m), vmoduleDUMP, (m, s))

#define vmoduleAttach(m, p)						\
   vclassSend(vmoduleGetClass(m), vmoduleATTACH, (m, p))

#define vmoduleAttachSearchScribed(m, p)				\
   vclassSend(vmoduleGetClass(m), vmoduleATTACH_SEARCH, (m, p))

#define vmoduleDetach(m)						\
   vclassSend(vmoduleGetClass(m), vmoduleDETACH, (m))

#define vmoduleGetSymbolScribed(m, s)					\
   vclassSend(vmoduleGetClass(m), vmoduleGET_SYMBOL_SCRIBED, (m, s))

#define vmoduleSetStartupSymbolScribed(m, s)				\
   vclassSend(vmoduleGetClass(m), vmoduleSET_STARTUP_SYMBOL_SCRIBED, (m, s))

#define vmoduleRegisterShutdown(m, p)					\
   vclassSend(vmoduleGetClass(m), vmoduleREGISTER_SHUTDOWN, (m, p))


vportEND_CPLUSPLUS_EXTERN_C

#endif

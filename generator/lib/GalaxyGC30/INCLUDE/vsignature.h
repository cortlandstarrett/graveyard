/* $Id: vsignature.h,v 1.13 1997/09/19 23:26:34 robert Exp $ */

/*************************************************************************
 *
 * vsignature.h
 *
 * C Interface for function signatures in the Service Manager
 *
 * (c) Copyright Visix Software, Inc.
 * All Rights Resereved
 *
 *************************************************************************/

#ifndef vsignatureINCLUDED
#define vsignatureINCLUDED 1

#ifndef vportINCLUDED
#include <vport.h>
#endif

#ifndef vdatatagINCLUDED
#include vdatatagHEADER
#endif

#ifndef vnameINCLUDED
#include vnameHEADER
#endif

#ifndef vloadableINCLUDED
#include vloadableHEADER
#endif

#ifndef vresourceINCLUDED
#include vresourceHEADER
#endif

#ifndef vstdioINCLUDED
#include vstdioHEADER
#endif


vportBEGIN_CPLUSPLUS_EXTERN_C

/*************************************************************************
 * Public constant definitions.
 *************************************************************************/


/*************************************************************************
 * Public type definitions.
 *************************************************************************/

typedef struct vsignature	vsignature;

/*************************************************************************
 * Public function prototypes.
 *************************************************************************/

void vsignatureStartup(void);


/*
 * Functions to create/initialize a function signature.
 */

vsignature *vsignatureCreate(
   void
   );

void vsignatureInit(
   vsignature		*signature
   );

void vsignatureDestroy(
   vsignature		*signature
   );

vsignature *vsignatureClone(
   vsignature		*signature
   );

void vsignatureCopy(
   vsignature		*src,
   vsignature		*dst
   );

void vsignatureCopyInit(
   vsignature		*src,
   vsignature		*dst
   );

vsignature *vsignatureLoad(
   vresource		resource
   );

void vsignatureLoadInit(
   vsignature		*signature,
   vresource		 resource
   );

void vsignatureStore(
   vsignature		*signature,
   vresource		 resource
   );

void vsignatureDump(
   vsignature		*signature,
   FILE			*stream
   );

/*
 * Functions to get/set the signature name tag.
 */

const vname *vsignatureGetTag(
   vsignature		*signature
   );

void vsignatureSetTag(
   vsignature		*signature,
   const vname		*name
   );

/*
 * Functions to get/set the signature return value datatag.
 */

vdatatag *vsignatureGetReturnDatatag(
   vsignature		*signature
   );

void vsignatureSetReturnDatatag(
   vsignature		*signature,
   vdatatag		*datatag
   );

/*
 * Functions to get/set the signature argument datatags.
 */

void vsignatureConstructArgs(
   vsignature		*signature,
   ...
   );

vdatatagList *vsignatureGetDatatagList(
   vsignature		*signature
   );

void vsignatureAppendDatatag(
   vsignature		*signature,
   vdatatag		*datatag
   );

void vsignatureInsertDatatagAt(
   vsignature		*signature,
   vdatatag		*datatag,
   unsigned int		 index
   );

void vsignatureDeleteDatatagAt(
   vsignature		*signature,
   unsigned int		 index
   );

vdatatag *vsignatureGetDatatagAt(
   vsignature		*signature,
   unsigned int		 index
   );

void vsignatureSetDatatagAt(
   vsignature		*signature,
   unsigned int		 index,
   vdatatag		*datatag
   );

unsigned int vsignatureGetDatatagCount(
   vsignature		*signature
   );

void vsignatureSetDatatagCount(
   vsignature		*signature,
   unsigned int		 count
   );


/*************************************************************************
 * Private type definitions.
 *************************************************************************/

typedef struct _vsignatureClass	_vsignatureClass;

struct _vsignatureClass {
   vloadableCLASS(_vsignatureClass, vsignature);
   };

struct vsignature {
   vloadable		 super;
   vdatatag		*rettype;
   vdatatagList		 arguments;
   };

/*************************************************************************
 * Private function prototypes.
 *************************************************************************/

_vsignatureClass *_vsignatureGetDefaultClass(
   void
   );

_vsignatureClass *_vsignatureGetClass(
   vsignature		*signature
   );

vloadable *_vsignatureGetLoadable(
   vsignature		*signature
   );

vsignature *_vsignatureCreateOfClass(
   _vsignatureClass	*clas
   );

void _vsignatureInitOfClass(
   vsignature		*signature,
   _vsignatureClass	*clas
   );

/*************************************************************************
 * Private function macro definitions.
 *************************************************************************/

#define _vsignatureGetLoadable(s)					\
   vportBASE_OBJECT(s, super)

#define _vsignatureCreateOfClass(s)					\
   ((vsignature *)vloadableCreateOfClass((vloadableClass *)(s)))

#define vsignatureCreate()						\
   _vsignatureCreateOfClass(_vsignatureGetDefaultClass())

#define vsignatureClone(s)						\
   ((vsignature *)vloadableClone(_vsignatureGetLoadable(s)))

#define _vsignatureInitOfClass(s, c)					\
   vloadableInitOfClass(_vsignatureGetLoadable(s), (vloadableClass *)(c))

#define vsignatureInit(s)						\
   _vsignatureInitOfClass(s, _vsignatureGetDefaultClass())

#define vsignatureDestroy(s)						\
   vloadableDestroy(_vsignatureGetLoadable(s))

#define vsignatureCopy(s, d)						\
   vloadableCopy(_vsignatureGetLoadable(s), _vsignatureGetLoadable(d))

#define vsignatureCopyInit(s, d)					\
   vloadableCopyInit(_vsignatureGetLoadable(s), _vsignatureGetLoadable(d))

#define vsignatureStore(s, r)						\
   vloadableStore(_vsignatureGetLoadable(s), r)

#define vsignatureGetTag(s)						\
   vloadableGetTag(_vsignatureGetLoadable(s))

#define vsignatureSetTag(s, t)						\
   vloadableSetTag(_vsignatureGetLoadable(s), (t))

#define vsignatureGetReturnDatatag(s)					\
   ((s)->rettype)

#define vsignatureSetReturnDatatag(s, e)				\
   ((s)->rettype = (e))

#define vsignatureGetDatatagList(s)					\
   (&((s)->arguments))

#define vsignatureAppendDatatag(s, d)					\
   vdatatagAppendList(&((s)->arguments), d)

#define vsignatureInsertDatatagAt(s, d, i)				\
   vdatatagInsertListAt(&((s)->arguments), d, i)

#define vsignatureDeleteDatatagAt(s, i)					\
   vdatatagDeleteListAt(&((s)->arguments), i)

#define vsignatureGetDatatagAt(s, i)					\
   vdatatagGetListAt(&((s)->arguments), i)

#define vsignatureSetDatatagAt(s, i, d)					\
   vdatatagSetListAt(&((s)->arguments), i, d)

#define vsignatureGetDatatagCount(s)					\
   vdatatagGetListCount(&((s)->arguments))

#define vsignatureSetDatatagCount(s, c)					\
   vdatatagSetListCount(&((s)->arguments), c)

#define _vsignatureGetClass(s)						\
   ((_vsignatureClass *)vloadableGetClass((vloadable *)(s)))

/*************************************************************************
 * Private function message definitions.
 *************************************************************************/

#define _vsignatureSend(s, d, a)					\
   vclassSend(_vsignatureGetClass(s), d, a)


vportEND_CPLUSPLUS_EXTERN_C

#endif

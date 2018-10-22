/* $Id: vdatatag.h,v 1.21 1996/03/23 00:44:45 chad Exp $ */

/****************************************************************
 *
 * vdatatag.h
 *
 * C Interface file for the Datatag Manager objects.
 *
 * Copyright (c) Visix Software, Incorporated
 * All Rights Reserved
 *
 ****************************************************************/

#ifndef vdatatagINCLUDED
#define vdatatagINCLUDED 1

#ifndef vportINCLUDED
#include <vport.h>
#endif

#ifndef vclassINCLUDED
#include vclassHEADER
#endif

#ifndef vdictINCLUDED
#include vdictHEADER
#endif

#ifndef vexINCLUDED
#include vexHEADER
#endif

#ifndef vinstanceINCLUDED
#include vinstanceHEADER
#endif

#ifndef vnameINCLUDED
#include vnameHEADER
#endif

#ifndef vresourceINCLUDED
#include vresourceHEADER
#endif


vportBEGIN_CPLUSPLUS_EXTERN_C

/****************************************************************
 * Public constant definitions.
 ****************************************************************/


/****************************************************************
 * Public type definitions.
 ****************************************************************/

/*
 * Datatags.
 */

typedef struct vdatatag			vdatatag;
typedef struct vdatatagList		vdatatagList;
typedef struct vdatatagGroup		vdatatagGroup;
typedef struct vdatatagIterator		vdatatagIterator;
typedef struct vdatatagGroupIterator	vdatatagGroupIterator;

/*
 * Datatag scraps.
 */

typedef struct vdatatagScrapClass	vdatatagScrapClass;
typedef struct vdatatagScrap		vdatatagScrap;

/*
 * Exceptions.
 */

typedef struct vdatatagNotFoundException   vdatatagNotFoundException;
typedef struct vdatatagIncompleteException vdatatagIncompleteException;
typedef struct vdatatagMismatchException   vdatatagMismatchException;

/****************************************************************
 * Public function prototypes.
 ****************************************************************/

void vdatatagStartup(void);


/*
 * Pre-defined datatag functions.
 */

vdatatag *vdatatagGetBoolean(
   void
   );

vdatatag *vdatatagGetCharacter(
   void
   );

vdatatag *vdatatagGetByte(
   void
   );

vdatatag *vdatatagGetUnsignedByte(
   void
   );

vdatatag *vdatatagGetShort(
   void
   );

vdatatag *vdatatagGetUnsignedShort(
   void
   );

vdatatag *vdatatagGetInteger(
   void
   );

vdatatag *vdatatagGetUnsignedInteger(
   void
   );

vdatatag *vdatatagGetLonglong(
   void
   );

vdatatag *vdatatagGetUnsignedLonglong(
   void
   );

vdatatag *vdatatagGetFixed(
   void
   );

vdatatag *vdatatagGetSingleFloat(
   void
   );

vdatatag *vdatatagGetDoubleFloat(
   void
   );

vdatatag *vdatatagGetString(
   void
   );

vdatatag *vdatatagGetTag(
   void
   );

vdatatag *vdatatagGetOpaque(
   void
   );

vdatatag *vdatatagGetDatatag(
   void
   );

vdatatag *vdatatagGetScrap(
   void
   );

/*
 * Datatag functions.
 */

void vdatatagDestroy(
   vdatatag		*datatag
   );

const vname *vdatatagGetName(
   vdatatag		 *datatag
   );

vdatatagGroup *vdatatagGetGroup(
   vdatatag		 *datatag
   );

vscrapClass *vdatatagGetScrapClass(
   vdatatag		*datatag
   );

void vdatatagSetScrapClass(
   vdatatag		*datatag,
   vscrapClass		*clas
   );

void vdatatagDump(
   vdatatag		*datatag,
   FILE			*stream
   );

/*
 * Pointer datatag functions.
 */

vdatatag *vdatatagCreatePointer(
   void
   );

vdatatag *vdatatagGetPointerDatatag(
   vdatatag		*pointer
   );

void vdatatagSetPointerDatatag(
   vdatatag		*pointer,
   vdatatag		*datatag
   );

/*
 * Array datatag functions.
 */

vdatatag *vdatatagCreateArray(
   void
   );

vdatatag *vdatatagGetArrayDatatag(
   vdatatag		*array
   );

void vdatatagSetArrayDatatag(
   vdatatag		*array,
   vdatatag		*datatag
   );

/*
 * Sized array datatag functions.
 */

vdatatag *vdatatagCreateSizedArray(
   void
   );

vdatatag *vdatatagGetSizedArrayDatatag(
   vdatatag		*array
   );

void vdatatagSetSizedArrayDatatag(
   vdatatag		*array,
   vdatatag		*datatag
   );

unsigned int vdatatagGetSizedArrayCount(
   vdatatag		*array
   );

void vdatatagSetSizedArrayCount(
   vdatatag		*array,
   unsigned int		 count
   );

/*
 * Sized opaque datatag functions.
 */

vdatatag *vdatatagCreateSizedOpaque(
   void
   );

unsigned int vdatatagGetSizedOpaqueCount(
   vdatatag		*opaque
   );

void vdatatagSetSizedOpaqueCount(
   vdatatag		*opaque,
   unsigned int		 count
   );

/*
 * Dictionary datatag functions.
 */

vdatatag *vdatatagCreateDict(
   void
   );

vdatatag *vdatatagGetDictElementDatatag(
   vdatatag		*dict,
   const vname		*name
   );

void vdatatagSetDictElementDatatag(
   vdatatag		*dict,
   const vname		*name,
   vdatatag		*datatag
   );

void vdatatagRemoveDictElementDatatag(
   vdatatag		*dict,
   const vname		*name
   );

void vdatatagConstructDict(
   vdatatag		*dict,
   ...
   );

/*
 * Compound datatag functions.
 */

vdatatag *vdatatagCreateCompound(
   void
   );

vdatatagList *vdatatagGetCompoundDatatagList(
   vdatatag		*compound
   );

void vdatatagConstructCompound(
   vdatatag		*compound,
   ...
   );

/*
 * Union datatag functions.
 */

vdatatag *vdatatagCreateUnion(
   void
   );

vdatatag *vdatatagGetUnionElementDatatag(
   vdatatag		*punion,
   int			 selector
   );

void vdatatagSetUnionElementDatatag(
   vdatatag		*punion,
   int			 selector,
   vdatatag		*element
   );

void vdatatagRemoveUnionElementDatatag(
   vdatatag		*punion,
   int			 selector
   );

void vdatatagConstructUnion(
   vdatatag		*punion,
   ...
   );

/*
 * Datatag list functions.
 */

void vdatatagInitList(
   vdatatagList		*list
   );

void vdatatagDestroyList(
   vdatatagList		*list
   );

void vdatatagCopyList(
   vdatatagList		*src,
   vdatatagList		*dest
   );

void vdatatagCopyInitList(
   vdatatagList		*src,
   vdatatagList		*dest
   );

void vdatatagAppendList(
   vdatatagList		*list,
   vdatatag		*element
   );

void vdatatagInsertListAt(
   vdatatagList		*list,
   vdatatag		*element,
   unsigned int		 index
   );

void vdatatagDeleteListAt(
   vdatatagList		*list,
   unsigned int		 index
   );

vdatatag *vdatatagGetListAt(
   vdatatagList		*list,
   unsigned int		 index
   );

void vdatatagSetListAt(
   vdatatagList		*list,
   unsigned int		 index,
   vdatatag		*element
   );

unsigned int vdatatagGetListCount(
   vdatatagList		*list
   );

void vdatatagSetListCount(
   vdatatagList		*list,
   unsigned int		 count
   );

/*
 * Datatag iterator functions.
 */

void vdatatagInitIterator(
   vdatatagIterator	*iter,
   vdatatag		*datatag
   );

vbool vdatatagNextIterator(
   vdatatagIterator	*iter
   );

vdatatag *vdatatagGetIteratorDatatag(
   vdatatagIterator	*iter
   );

const vname *vdatatagGetIteratorDictName(
   vdatatagIterator	*iter
   );

int vdatatagGetIteratorCompoundIndex(
   vdatatagIterator	*iter
   );

int vdatatagGetIteratorUnionSelector(
   vdatatagIterator	*iter
   );

void vdatatagDestroyIterator(
   vdatatagIterator	*iter
   );

/*
 * Datatag group functions.
 */

vdatatagGroup *vdatatagCreateGroup(
   void
   );

void vdatatagInitGroup(
   vdatatagGroup		*group
   );

void vdatatagDestroyGroup(
   vdatatagGroup		*group
   );

vdatatagGroup *vdatatagLoadGroup(
   vresource			res
   );

void vdatatagLoadInitGroup(
   vdatatagGroup		*group,
   vresource			 res
   );

void vdatatagStoreGroup(
   vdatatagGroup		*group,
   vresource			 res
   );

void vdatatagDumpGroup(
   vdatatagGroup		*group,
   FILE				*stream
   );

const vname *vdatatagGetGroupName(
   vdatatagGroup		*group
   );

void vdatatagSetGroupName(
   vdatatagGroup		*group,
   const vname			*name
   );

vdatatagGroup *vdatatagFindGroup(
   const vname			*name
   );

void vdatatagAddToGroup(
   vdatatagGroup		*group,
   const vname			*name,
   vdatatag			*datatag
   );

vdatatag *vdatatagRemoveFromGroup(
   vdatatagGroup		*group,
   const vname			*name
   );

vdatatag *vdatatagLookupInGroup(
   vdatatagGroup	*group,
   const vname		*name
   );

void vdatatagInitGroupIterator(
   vdatatagGroupIterator	*iter,
   vdatatagGroup		*group
   );

vbool vdatatagNextGroupIterator(
   vdatatagGroupIterator	*iter
   );

const vname *vdatatagGetGroupIteratorName(
   vdatatagGroupIterator	*iter
   );

vdatatag *vdatatagGetGroupIteratorDatatag(
   vdatatagGroupIterator	*iter
   );

void vdatatagDestroyGroupIterator(
   vdatatagGroupIterator	*iter
   );

/*
 * Datatag scrap class functions.
 */

vdatatagScrapClass *vdatatagGetDefaultScrapClass(
   void
   );

vdatatagScrapClass *vdatatagGetDatatagScrapClass(
   vdatatagScrap	*scrap
   );

void vdatatagSendScrap(
   vdelegatorStack	*stack,
   ...
   );

vdatatag *vdatatagGetScrapDatatag(
   vscrap		*scrap
   );

/*
 * Datatag scrap creation functions.
 */

vscrap *vdatatagScrapFromValue(
   vdatatag		*datatag,
   ...
   );

vscrap *vdatatagScrapFromValueArg(
   vdatatag		*datatag,
   va_list		*varargs
   );

vscrap *vdatatagScrapFromReference(
   vdatatag		*datatag,
   ...
   );

vscrap *vdatatagScrapFromReferenceArg(
   vdatatag		*datatag,
   va_list		*varargs
   );

/*
 * Datatag list scrap creation functions.
 */

vscrap *vdatatagScrapFromListValues(
   vdatatagList		*list,
   ...
   );

vscrap *vdatatagScrapFromListValueArgs(
   vdatatagList		*list,
   va_list		*varargs
   );

vscrap *vdatatagScrapFromListReferences(
   vdatatagList		*list,
   ...
   );

vscrap *vdatatagScrapFromListReferenceArgs(
   vdatatagList		*list,
   va_list		*varargs
   );

/*
 * Datatag scrap manipulation functions.
 */

void vdatatagSetScrapDatatag(
   vscrap		*scrap,
   vdatatag		*dtag
   );

void vdatatagSetScrapDatatagStack(
   vdelegatorStack	 stack,
   vdatatag		*dtag
   );

void vdatatagSetScrapValue(
   vscrap		*scrap,
   va_list		*varargs
   );

void vdatatagSetScrapValueStack(
   vdelegatorStack	 stack,
   va_list		*varargs
   );

void *vdatatagCreateScrapStorage(
   vscrap		*scrap
   );

void *vdatatagCreateScrapStorageStack(
   vdelegatorStack	stack
   );

void vdatatagInitScrapStorage(
   vscrap		*scrap,
   va_list		*varargs
   );

void vdatatagInitScrapStorageStack(
   vdelegatorStack	 stack,
   va_list		*varargs
   );

size_t vdatatagGetSizeofScrapStorage(
   vscrap		*scrap
   );

size_t vdatatagGetSizeofScrapStorageStack(
   vdelegatorStack	stack
   );

/*
 * Exceptions.
 */

const vexClass *vdatatagGetNotFoundExceptionClass(
   void
   );

vdatatagNotFoundException *vdatatagGetNotFoundException(
   void
   );

const vname *vdatatagGetNotFoundExceptionName(
   vdatatagNotFoundException	*exception
   );

void vdatatagGenerateNotFoundException(
   const vname 			*name,
   const char			*message
   );
   

const vexClass *vdatatagGetIncompleteExceptionClass(
   void
   );

vdatatagIncompleteException *vdatatagGetIncompleteException(
   void
   );

vdatatag *vdatatagGetIncompleteExceptionDatatag(
   vdatatagIncompleteException	*exception
   );

void vdatatagGenerateIncompleteException(
   vdatatag			*datatag,
   const char			*message
   );


const vexClass *vdatatagGetMismatchExceptionClass(
   void
   );

vdatatagMismatchException *vdatatagGetMismatchException(
   void
   );

vdatatag *vdatatagGetMismatchExceptionDatatag(
   vdatatagMismatchException *exception
   );

void vdatatagGenerateMismatchException(
   vdatatag			*datatag,
   const char			*message
   );


/****************************************************************
 * Private constant definitions.
 ****************************************************************/

enum {				/* Predefined Datatags:		*/
   _vdatatagBOOLEAN,		/* vbool			*/
   _vdatatagCHARACTER,		/* vchar			*/
   _vdatatagBYTE,		/*  8 bits of signed protocol	*/
   _vdatatagU_BYTE,		/*  8 bits of unsigned protocol	*/
   _vdatatagSHORT,		/* 16 bits of signed protocol	*/
   _vdatatagU_SHORT,		/* 16 bits of unsigned protocol	*/
   _vdatatagINTEGER,		/* 32 bits of signed protocol	*/
   _vdatatagU_INTEGER,		/* 32 bits of unsigned protocol	*/
   _vdatatagLONGLONG,		/* 64 bits of signed protocol	*/
   _vdatatagU_LONGLONG,		/* 64 bits of unsigned protocol	*/
   _vdatatagFIXED,		/* vfixed			*/
   _vdatatagSINGLE_FLOAT,	/* C float			*/
   _vdatatagDOUBLE_FLOAT,	/* C double			*/
   _vdatatagSTRING,		/* vchar *, vstr *		*/
   _vdatatagTAG,		/* global const vname *		*/
   _vdatatagOPAQUE,		/* size_t, vbyte *		*/
   _vdatatagDATATAG,		/* vdatatag *			*/
   _vdatatagLIST,		/* va_list			*/
   _vdatatagSCRAP,		/* vscrap *			*/
   _vdatatagPREDEFS		/* total predefined types	*/
   };

enum {
   _vdatatagPOINTER		= _vdatatagPREDEFS,
   _vdatatagARRAY,		/* int, vbyte *			*/
   _vdatatagSIZED_ARRAY,	/* vbyte *			*/
   _vdatatagSIZED_OPAQUE,	/* vbyte *			*/
   _vdatatagDICTIONARY,		/* vdict *			*/
   _vdatatagCOMPOUND,		/* void *			*/
   _vdatatagUNION,		/* int, void *			*/
   _vdatatagCOUNT
   };

/*************************************************************************
 * Private type definitions.
 *************************************************************************/

/*
 * Datatags.
 */

typedef struct _vdatatagClass	_vdatatagClass;

#define _vdatatagCLASS(CLASS, OBJECT)					\
   vinstanceCLASS(CLASS, OBJECT);					\
   vclassMETHOD(_vdatatagLOAD_INIT, (OBJECT *datatag, vresource res));	\
   vclassMETHOD(_vdatatagSTORE, (OBJECT *datatag, vresource res));	\
   vclassMETHOD(_vdatatagDUMP, (OBJECT *datatag, FILE *stream))

struct _vdatatagClass {
   _vdatatagCLASS(_vdatatagClass, vdatatag);
   };

struct vdatatag {
   vinstance		 super;
   vscrapClass		*scrapClass;
   vdatatagGroup	*group;
   const vname		*name;
   int			 flags;
   };

/*
 * Datatag lists.
 */

struct vdatatagList {
   vdatatag		**datatags, **stop, **max;
   };

/*
 * Datatag iterators.
 */

struct vdatatagIterator {
   int			 index;
   vdictIterator	 dictIter;
   vdatatag		*dtag;
   };

/*
 * Datatag groups.
 */

struct vdatatagGroup {
   const vname		*name;
   vdict		*datatags;
   };

struct vdatatagGroupIterator {
   vdictIterator	 dictIter;
   };

/*
 * Datatag scrap class and instance.
 */

#define vdatatagScrapCLASS(CLASS, OBJECT)				\
   vscrapCONVERTIBLE_CLASS(CLASS, OBJECT);				\
   vclassMETHOD(vdatatagSET_DATATAG,					\
		(const vdelegatorStack *stack, vdatatag *dtag));	\
   vclassMETHOD(vdatatagSET_VALUE,					\
		(const vdelegatorStack *stack, va_list *varargs));	\
   vclassMETHOD_RET(vdatatagCREATE_STORAGE, void *,			\
		(const vdelegatorStack *stack));			\
   vclassMETHOD(vdatatagINIT_STORAGE,					\
		(const vdelegatorStack *stack, va_list *varargs));	\
   vclassMETHOD_RET(vdatatagSIZEOF_STORAGE, size_t,			\
		(const vdelegatorStack *stack))

struct vdatatagScrapClass {
   vdatatagScrapCLASS(vdatatagScrapClass, vdatatagScrap);
   };

struct vdatatagScrap {
   vscrapConvertible	 super;
   vdatatag		*datatag;
   };

/*
 * Exceptions.
 */

struct vdatatagNotFoundException {
   vexArgException		 super;
   const vname			*name;
   };

struct vdatatagIncompleteException {
   vexArgException		 super;
   vdatatag			*datatag;
   };

struct vdatatagMismatchException {
   vexArgException		 super;
   vdatatag			*datatag;
   };

/*************************************************************************
 * Private variable declarations.
 *************************************************************************/

extern vportLINK const vexClass		_vdatatagNotFoundExceptionClass;
extern vportLINK const vexClass		_vdatatagIncompleteExceptionClass;
extern vportLINK const vexClass		_vdatatagMismatchExceptionClass;

/*************************************************************************
 * Private function prototypes.
 *************************************************************************/

vdatatag *_vdatatagGetPredefined(
   unsigned int		id
   );

#if vdebugDEBUG
vdatatag *_vdatatagCreatePredefinedDebug(
   unsigned int		id,
   const char          *tag,
   const char          *file,
   int                  line
   );
#else
vdatatag *_vdatatagCreatePredefined(
   unsigned int		id
   );
#endif

void _vdatatagNotFoundExceptionNAME(
   void			*exception,
   va_list		*args
   );

void _vdatatagIncompleteExceptionDATATAG(
   void			*exception,
   va_list		*args
   );

void _vdatatagMismatchExceptionDATATAG(
   void			*exception,
   va_list		*args
   );


/*************************************************************************
 * Private function macro definitions.
 *************************************************************************/

#if vdebugDEBUG
#define _vdatatagCreatePredefined(i)                                    \
   _vdatatagCreatePredefinedDebug(i, vdebugTAG, __FILE__, __LINE__)
#endif

#define vdatatagGetBoolean()						\
   _vdatatagGetPredefined(_vdatatagBOOLEAN)

#define vdatatagGetCharacter()						\
   _vdatatagGetPredefined(_vdatatagCHARACTER)

#define vdatatagGetByte()						\
   _vdatatagGetPredefined(_vdatatagBYTE)

#define vdatatagGetUnsignedByte()					\
   _vdatatagGetPredefined(_vdatatagU_BYTE)

#define vdatatagGetShort()						\
   _vdatatagGetPredefined(_vdatatagSHORT)

#define vdatatagGetUnsignedShort()					\
   _vdatatagGetPredefined(_vdatatagU_SHORT)

#define vdatatagGetInteger()						\
   _vdatatagGetPredefined(_vdatatagINTEGER)

#define vdatatagGetUnsignedInteger()					\
   _vdatatagGetPredefined(_vdatatagU_INTEGER)

#define vdatatagGetLonglong()						\
   _vdatatagGetPredefined(_vdatatagLONGLONG)

#define vdatatagGetUnsignedLonglong()					\
   _vdatatagGetPredefined(_vdatatagU_LONGLONG)

#define vdatatagGetSingleFloat()					\
   _vdatatagGetPredefined(_vdatatagSINGLE_FLOAT)

#define vdatatagGetDoubleFloat()					\
   _vdatatagGetPredefined(_vdatatagDOUBLE_FLOAT)

#define vdatatagGetFixed()						\
   _vdatatagGetPredefined(_vdatatagFIXED)

#define vdatatagGetString()						\
   _vdatatagGetPredefined(_vdatatagSTRING)

#define vdatatagGetTag()						\
   _vdatatagGetPredefined(_vdatatagTAG)

#define vdatatagGetOpaque()						\
   _vdatatagGetPredefined(_vdatatagOPAQUE)

#define vdatatagGetDatatag()						\
   _vdatatagGetPredefined(_vdatatagDATATAG)

#define vdatatagGetScrap()						\
   _vdatatagGetPredefined(_vdatatagSCRAP)

#define vdatatagCreatePointer()						\
   _vdatatagCreatePredefined(_vdatatagPOINTER)

#define vdatatagCreateArray()						\
   _vdatatagCreatePredefined(_vdatatagARRAY)

#define vdatatagCreateSizedArray()					\
   _vdatatagCreatePredefined(_vdatatagSIZED_ARRAY)

#define vdatatagCreateSizedOpaque()					\
   _vdatatagCreatePredefined(_vdatatagSIZED_OPAQUE)

#define vdatatagCreateDict()						\
   _vdatatagCreatePredefined(_vdatatagDICTIONARY)

#define vdatatagCreateCompound()					\
   _vdatatagCreatePredefined(_vdatatagCOMPOUND)

#define vdatatagCreateUnion()						\
   _vdatatagCreatePredefined(_vdatatagUNION)

/*
 * General datatag functions.
 */

#define vdatatagGetScrapClass(d)					\
   ((d)->scrapClass)

#define vdatatagGetName(d)						\
   ((d)->name)

#define vdatatagGetGroup(d)						\
   ((d)->group)

/*
 * Datatag group functions.
 */

#define vdatatagGetGroupName(g)						\
   ((g)->name)

#define vdatatagInitGroupIterator(i, g)					\
   vdictInitIterator(&(i)->dictIter, (g)->datatags)

#define vdatatagNextGroupIterator(i)					\
   vdictNextIterator(&(i)->dictIter)

#define vdatatagGetGroupIteratorName(i)					\
   ((const vname *)vdictGetIteratorKey(&(i)->dictIter))

#define vdatatagGetGroupIteratorDatatag(i)				\
   ((vdatatag *)vdictGetIteratorValue(&(i)->dictIter))

#define vdatatagDestroyGroupIterator(i)					\
   vdictDestroyIterator(&(i)->dictIter)

/*
 * Exception functions.
 */

#define vdatatagGetNotFoundExceptionClass()				\
   (&_vdatatagNotFoundExceptionClass)

#define vdatatagGetNotFoundException()					\
   ((vdatatagNotFoundException *)					\
    vexGetExceptionOfClass(&_vdatatagNotFoundExceptionClass))

#define vdatatagGetNotFoundExceptionName(e)				\
   ((e)->name)

#define vdatatagGenerateNotFoundException(n, m)				\
   vexGenerate(&_vdatatagNotFoundExceptionClass, vexMESSAGE, m,		\
		_vdatatagNotFoundExceptionNAME, n, vexNULL)


#define vdatatagGetIncompleteExceptionClass()				\
   (&_vdatatagIncompleteExceptionClass)

#define vdatatagGetIncompleteException()				\
   ((vdatatagIncompleteException *)					\
    vexGetExceptionOfClass(&_vdatatagIncompleteExceptionClass))

#define vdatatagGetIncompleteExceptionDatatag(e)			\
   ((e)->datatag)

#define vdatatagGenerateIncompleteException(d, m)			\
   vexGenerate(&_vdatatagIncompleteExceptionClass, vexMESSAGE, m,	\
		_vdatatagIncompleteExceptionDATATAG, d, vexNULL)


#define vdatatagGetMismatchExceptionClass()				\
   (&_vdatatagMismatchExceptionClass)

#define vdatatagGetMismatchException()					\
   ((vdatatagMismatchException *)					\
    vexGetExceptionOfClass(&_vdatatagMismatchExceptionClass))

#define vdatatagGetMismatchExceptionDatatag(e)				\
   ((e)->datatag)

#define vdatatagGenerateMismatchException(d, m)				\
   vexGenerate(&_vdatatagMismatchExceptionClass, vexMESSAGE, m,		\
		_vdatatagMismatchExceptionDATATAG, d, vexNULL)

/*
 * Datatag scrap function macros.
 */

#define vdatatagGetScrapDatatag(s)					\
   (((vdatatagScrap *)(s))->datatag)

#define vdatatagGetDatatagScrapClass(d)					\
   (vdatatagScrapClass *)vinstanceGetClass((vinstance *)(d))

#define vdatatagSendScrap(s, m, a)					\
   vclassSend(vdatatagGetDatatagScrapClass(vdelegatorGetStackTop(s)), m, a)

#define vdatatagSetScrapDatatag(o, d)					\
   vdatatagSetScrapDatatagStack(vdelegatorMakeObjectStack(o), (d))

#define vdatatagSetScrapValue(o, v)					\
   vdatatagSetScrapValueStack(vdelegatorMakeObjectStack(o), (v))

#define vdatatagCreateScrapStorage(o)					\
   vdatatagCreateScrapStorageStack(vdelegatorMakeObjectStack(o))

#define vdatatagInitScrapStorage(o, s)					\
   vdatatagInitScrapStorageStack(vdelegatorMakeObjectStack(o), (s))

#define vdatatagGetSizeofScrapStorage(o)				\
   vdatatagGetSizeofScrapStorageStack(vdelegatorMakeObjectStack(o))

/*************************************************************************
 * Private function message definitions.
 *************************************************************************/


vportEND_CPLUSPLUS_EXTERN_C

#endif

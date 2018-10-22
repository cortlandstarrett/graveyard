/* $Id: vscrap.h,v 1.36 1997/07/24 17:11:11 robert Exp $ */

/******************************************
 * vscrap.h
 *
 * Scrap Manager header file
 *
 * Part of Galaxy Application Environment
 *
 * Copyright (C) 1993 Visix Software Inc.
 * All rights reserved.
 ******************************************/


#ifndef vscrapINCLUDED
#define vscrapINCLUDED 1

#ifndef  vportINCLUDED		/* for v*HEADER */
#include <vport.h>
#endif

#ifndef  vstddefINCLUDED	/* for size_t */
#include vstddefHEADER
#endif

#ifndef  vstdioINCLUDED		/* for FILE */
#include vstdioHEADER
#endif

#ifndef  vstdINCLUDED		/* for vbool */
#include vstdHEADER
#endif

#ifndef  vscribeINCLUDED
#include vscribeHEADER
#endif

#ifndef  vcharINCLUDED
#include vcharHEADER
#endif

#ifndef  vdictINCLUDED
#include vdictHEADER
#endif

#ifndef  vnameINCLUDED
#include vnameHEADER
#endif

#ifndef  vclassINCLUDED
#include vclassHEADER
#endif

#ifndef  vinstanceINCLUDED
#include vinstanceHEADER
#endif

#ifndef  vdelegatorINCLUDED
#include vdelegatorHEADER
#endif

#ifndef  vfixedINCLUDED
#include vfixedHEADER
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C


/*
 * * * * * * * * * * * * * Types * * * * * * * * * * * * * *
 */

/*
 * a vscrap is just a vinstance.
 */

typedef vinstanceClass 	vscrapClass;
typedef vinstance 	vscrap;

#define vscrapCLASS(CLASS, OBJECT)					\
    vinstanceCLASS(CLASS, OBJECT)

/*
 * Generic scrap iterator
 */

typedef struct vscrapIteratorClass	vscrapIteratorClass;
typedef struct vscrapIterator		vscrapIterator;

#define vscrapITERATOR_CLASS(CLASS, OBJECT)				\
    vinstanceCLASS(CLASS, OBJECT);					\
    vclassMETHOD(vscrapINIT_ITERATOR,					\
		 (OBJECT *iter, const vdelegatorStack *stack));		\
    vclassMETHOD(vscrapDESTROY_ITERATOR, (OBJECT *iter));		\
    vclassMETHOD_RET(vscrapNEXT_ITERATOR, vbool, (OBJECT *iter))

struct vscrapIteratorClass
{
  vscrapITERATOR_CLASS(vscrapIteratorClass, vscrapIterator);
};

struct vscrapIterator
{
  vinstance		instance;
  vdelegatorStack	stack;
};


/*
 * * * Convertible scrap class
 */

typedef struct vscrapConvertibleClass		vscrapConvertibleClass;
typedef vdelegator				vscrapConvertible;

#define vscrapCONVERTIBLE_CLASS(CLASS, OBJECT)				\
    vdelegatorCLASS(CLASS, OBJECT);					\
    vclassMETHOD(vscrapDUMP, (const vdelegatorStack *stack,		\
			      FILE *stream));				\
    vclassVARIABLE(vscrapEXPORT_CLASS, vclass *);			\
    vclassMETHOD(vscrapEXPORT, (const vdelegatorStack *stack, 		\
				const vdelegatorStack *dest)); 		\
    vclassMETHOD(vscrapIMPORT, (const vdelegatorStack *stack,		\
				const vdelegatorStack *source))

struct vscrapConvertibleClass
{
  vscrapCONVERTIBLE_CLASS(vscrapConvertibleClass, vscrapConvertible);
};

/*
 * typeable scrap
 */

typedef struct vscrapTypeableClass	vscrapTypeableClass;
typedef vscrapConvertible		vscrapTypeable;

#define vscrapTYPEABLE_CLASS(CLASS, OBJECT)				\
    vscrapCONVERTIBLE_CLASS(CLASS, OBJECT);				\
    vclassMETHOD_RET(vscrapENTYPE, vbool, 				\
		     (const vdelegatorStack *stack, void *clas))

struct vscrapTypeableClass
{
  vscrapTYPEABLE_CLASS(vscrapTypeableClass, vscrapTypeable);
};


/*
 * * * Abstract classes (types) * * * * * * * 
 */

/*
 * int:
 */

typedef struct vscrapIntegerClass	vscrapIntegerClass;
typedef vscrapConvertible		vscrapInteger;

#define vscrapINTEGER_CLASS(CLASS, OBJECT)				\
    vscrapCONVERTIBLE_CLASS(CLASS, OBJECT);				\
    vclassMETHOD(vscrapSET_INTEGER, (const vdelegatorStack *stack, 	\
				     long value));			\
    vclassMETHOD_RET(vscrapGET_INTEGER, long, (const vdelegatorStack *stack))

struct vscrapIntegerClass
{
  vscrapINTEGER_CLASS(vscrapIntegerClass, vscrapInteger);
};


/*
 * boolean value
 */

typedef struct vscrapBooleanClass	vscrapBooleanClass;
typedef vscrapConvertible		vscrapBoolean;

#define vscrapBOOLEAN_CLASS(CLASS, OBJECT)				\
    vscrapCONVERTIBLE_CLASS(CLASS, OBJECT);				\
    vclassMETHOD(vscrapSET_BOOLEAN, 					\
		 (const vdelegatorStack *stack, int /*vbool*/ value));	\
    vclassMETHOD_RET(vscrapGET_BOOLEAN, vbool, (const vdelegatorStack *stack))

struct vscrapBooleanClass
{
  vscrapBOOLEAN_CLASS(vscrapBooleanClass, vscrapBoolean);
};


/*
 * real number:
 */

typedef struct vscrapFloatClass	vscrapFloatClass;
typedef vscrapConvertible	vscrapFloat;

#define vscrapFLOAT_CLASS(CLASS, OBJECT)				\
    vscrapCONVERTIBLE_CLASS(CLASS, OBJECT);				\
    vclassMETHOD(vscrapSET_FLOAT, (const vdelegatorStack *stack,	\
				   double value));			\
    vclassMETHOD_RET(vscrapGET_FLOAT, double, (const vdelegatorStack *stack))

struct vscrapFloatClass
{
  vscrapFLOAT_CLASS(vscrapFloatClass, vscrapFloat);
};


/*
 * fixed point number:
 */

typedef struct vscrapFixedClass	vscrapFixedClass;
typedef vscrapConvertible	vscrapFixed;

#define vscrapFIXED_CLASS(CLASS, OBJECT)				\
    vscrapCONVERTIBLE_CLASS(CLASS, OBJECT);				\
    vclassMETHOD(vscrapSET_FIXED, (const vdelegatorStack *stack,	\
				   vfixed value));			\
    vclassMETHOD_RET(vscrapGET_FIXED, vfixed, (const vdelegatorStack *stack))

struct vscrapFixedClass
{
  vscrapFIXED_CLASS(vscrapFixedClass, vscrapFixed);
};


/*
 * character:
 */

typedef struct vscrapCharacterClass	vscrapCharacterClass;
typedef vscrapConvertible		vscrapCharacter;

#define vscrapCHARACTER_CLASS(CLASS, OBJECT)				\
    vscrapCONVERTIBLE_CLASS(CLASS, OBJECT);				\
    vclassMETHOD(vscrapSET_CHARACTER, 					\
		 (const vdelegatorStack *stack, int /*vchar*/ value));	\
    vclassMETHOD_RET(vscrapGET_CHARACTER, vchar, 			\
		     (const vdelegatorStack *stack))

struct vscrapCharacterClass
{
  vscrapCHARACTER_CLASS(vscrapCharacterClass, vscrapCharacter);
};


/*
 * string:
 */

typedef struct vscrapStringClass	vscrapStringClass;
typedef vscrapConvertible		vscrapString;

#define vscrapSTRING_CLASS(CLASS, OBJECT)				\
    vscrapCONVERTIBLE_CLASS(CLASS, OBJECT);				\
    vclassMETHOD(vscrapSET_STRING_SCRIBED, 				\
		 (const vdelegatorStack *stack, vscribe *scribe));	\
    vclassMETHOD_RET(vscrapSCRIBE_STRING, vscribe *, 			\
		     (const vdelegatorStack *stack))

struct vscrapStringClass
{
  vscrapSTRING_CLASS(vscrapStringClass, vscrapString);
};


/*
 * tag:
 */

typedef struct vscrapTagClass		vscrapTagClass;
typedef vscrapConvertible		vscrapTag;

#define vscrapTAG_CLASS(CLASS, OBJECT)					\
    vscrapCONVERTIBLE_CLASS(CLASS, OBJECT);				\
    vclassMETHOD(vscrapSET_TAG, 					\
		 (const vdelegatorStack *stack, const vname *tag));	\
    vclassMETHOD_RET(vscrapGET_TAG, const vname *,			\
		     (const vdelegatorStack *stack))

struct vscrapTagClass
{
  vscrapTAG_CLASS(vscrapTagClass, vscrapTag);
};


/*
 * block:
 */

typedef struct vscrapBlockClass		vscrapBlockClass;
typedef vscrapConvertible		vscrapBlock;

#define vscrapBLOCK_CLASS(CLASS, OBJECT)				\
    vscrapCONVERTIBLE_CLASS(CLASS, OBJECT);				\
    vclassMETHOD_RET(vscrapGET_BLOCK_SIZE, size_t, 			\
		     (const vdelegatorStack *stack));			\
    vclassMETHOD(vscrapSET_BLOCK_SIZE, 					\
		 (const vdelegatorStack *stack, size_t size));		\
    vclassMETHOD(vscrapREAD_BLOCK, 					\
		 (const vdelegatorStack *stack, size_t offset,		\
		  size_t count, void *buffer));				\
    vclassMETHOD(vscrapWRITE_BLOCK, 					\
		 (const vdelegatorStack *stack, size_t offset,		\
		  size_t count, const void *buffer));                   \
    vclassMETHOD(vscrapSYNC_BLOCK,                                      \
                 (const vdelegatorStack *stack))

struct vscrapBlockClass
{
  vscrapBLOCK_CLASS(vscrapBlockClass, vscrapBlock);
};


/*
 * compound
 */

typedef struct vscrapCompoundClass	vscrapCompoundClass;
typedef vscrapConvertible		vscrapCompound;

#define vscrapCOMPOUND_CLASS(CLASS, OBJECT)				\
    vscrapCONVERTIBLE_CLASS(CLASS, OBJECT);				\
    vclassVARIABLE(vscrapELEMENT_ITERATOR_CLASS, void *);		\
    vclassMETHOD(vscrapEMPTY_ELEMENTS, (const vdelegatorStack *stack));	\
    vclassMETHOD(vscrapADD_ELEMENT, 					\
		 (const vdelegatorStack *stack, vscrap *scrap))

struct vscrapCompoundClass
{
  vscrapCOMPOUND_CLASS(vscrapCompoundClass, vscrapCompound);
};

/*
 * iterator class for compound
 */

typedef struct vscrapCompoundIteratorClass	vscrapCompoundIteratorClass;
typedef vscrapIterator				vscrapCompoundIterator;

#define vscrapCOMPOUND_ITERATOR_CLASS(CLASS, OBJECT)			\
    vscrapITERATOR_CLASS(CLASS, OBJECT);				\
    vclassMETHOD_RET(vscrapGET_ITERATOR_ELEMENT, vscrap *, (OBJECT *iter))

struct vscrapCompoundIteratorClass
{
  vscrapCOMPOUND_ITERATOR_CLASS(vscrapCompoundIteratorClass, 
				vscrapCompoundIterator);
};

/* 
 * array
 */

typedef struct vscrapArrayClass		vscrapArrayClass;
typedef vscrapCompound			vscrapArray;

#define vscrapARRAY_CLASS(CLASS, OBJECT)				\
    vscrapCOMPOUND_CLASS(CLASS, OBJECT);				\
    vclassMETHOD_RET(vscrapGET_ARRAY_COUNT, size_t,			\
		     (const vdelegatorStack *stack));			\
    vclassMETHOD(vscrapSET_ARRAY_COUNT,					\
		 (const vdelegatorStack *stack, size_t count)); 	\
    vclassMETHOD_RET(vscrapGET_ELEMENT_AT, vscrap *,			\
		     (const vdelegatorStack *stack, size_t index));	\
    vclassMETHOD(vscrapSET_ELEMENT_AT, 					\
		 (const vdelegatorStack *stack, size_t index, vscrap *scrap))

struct vscrapArrayClass
{
  vscrapARRAY_CLASS(vscrapArrayClass, vscrapArray);
};


/*
 * iterator class for array.
 */

typedef struct vscrapArrayIteratorClass	vscrapArrayIteratorClass;
typedef vscrapCompoundIterator		vscrapArrayIterator;

#define vscrapARRAY_ITERATOR_CLASS(CLASS, OBJECT)			\
    vscrapCOMPOUND_ITERATOR_CLASS(CLASS, OBJECT);			\
    vclassMETHOD_RET(vscrapGET_ITERATOR_INDEX, size_t, (OBJECT *iter))

struct vscrapArrayIteratorClass
{
  vscrapARRAY_ITERATOR_CLASS(vscrapArrayIteratorClass, vscrapArrayIterator);
};

/*
 * dictionary
 */

typedef struct vscrapDictionaryClass	vscrapDictionaryClass;
typedef vscrapCompound			vscrapDictionary;

#define vscrapDICTIONARY_CLASS(CLASS, OBJECT)				\
    vscrapCOMPOUND_CLASS(CLASS, OBJECT);				\
    vclassMETHOD_RET(vscrapLOAD_ELEMENT, vscrap *,			\
		     (const vdelegatorStack *stack, const vname *key));	\
    vclassMETHOD(vscrapSTORE_ELEMENT,  					\
		 (const vdelegatorStack *stack, 			\
		  const vname *key, vscrap *scrap)); 			\
    vclassMETHOD(vscrapREMOVE_ELEMENT, 					\
		 (const vdelegatorStack *stack, const vname *key))

struct vscrapDictionaryClass
{
  vscrapDICTIONARY_CLASS(vscrapDictionaryClass, vscrapDictionary);
};

/*
 * iterator class for dictionary
 */

typedef struct vscrapDictionaryIteratorClass	vscrapDictionaryIteratorClass;
typedef vscrapCompoundIterator			vscrapDictionaryIterator;

#define vscrapDICTIONARY_ITERATOR_CLASS(CLASS, OBJECT)			\
    vscrapCOMPOUND_ITERATOR_CLASS(CLASS, OBJECT);			\
    vclassMETHOD_RET(vscrapGET_ITERATOR_KEY, const vname *, (OBJECT *iter))

struct vscrapDictionaryIteratorClass
{
  vscrapDICTIONARY_ITERATOR_CLASS(vscrapDictionaryIteratorClass, 
				vscrapDictionaryIterator);
};


/*
 * Exceptions:
 */

typedef struct vscrapUnimplementedException
{
  vexException 		super;
  vdelegatorStack	stack;
  vinstanceClass	*topClass;
} vscrapUnimplementedException;

typedef struct vscrapCannotConvertException
{
  vexException 		super;
  vdelegatorStack	from;
  vdelegatorStack	to;
  vinstanceClass	*fromTopClass;
  vinstanceClass	*toTopClass;
} vscrapCannotConvertException;


/*
 * * * * * * * * * * * * * * * Prototypes * * * * * * * * * * * * * * * *
 */

void vscrapStartup(void);


/*
 * Generic scrap operations.
 */

vscrapClass *vscrapGetDefaultClass(
    void			
    );

vscrapClass *vscrapGetClass(
    vscrap 			*scrap
    );

void vscrapDestroy(
    vscrap 			*scrap
    );

vbool vscrapIsKindOf(
    vscrap			*scrap,
    void 			*clas
    );

/*
 * Scrap iterator class:
 */

vscrapIteratorClass *vscrapGetDefaultIteratorClass(
    void
    );

vscrapIteratorClass *vscrapGetIteratorClass(
    vscrapIterator 		*iter
    );

vscrapIterator *vscrapCreateIteratorOfClass(
    void 			*clas,
    const vdelegatorStack 	*stack
    );

void vscrapInitIteratorOfClass(
    vscrapIterator 		*iter,
    void 			*clas,
    const vdelegatorStack 	*stack
    );

void vscrapDestroyIterator(
    vscrapIterator 		*iter
    );

vbool vscrapNextIterator(
    vscrapIterator 		*iter
    );

const vdelegatorStack *vscrapGetIteratorStack(
    vscrapIterator 		*iter
    );

/*
 * Convertible scraps:
 */

void vscrapSendConvertible(
    vdelegatorStack		*stack,
    ...
    );

vscrapConvertibleClass *vscrapGetDefaultConvertibleClass(
    void
    );

vscrapConvertibleClass *vscrapGetConvertibleClass(
    vscrapConvertible 		*scrap
    );

void vscrapDump(
    vscrap 			*scrap, 
    FILE 			*stream
    );

void vscrapDumpStack(
    vdelegatorStack 		stack, 
    FILE 			*stream
    );

void vscrapExport(
    vscrap 			*scrap, 
    vscrap 			*dest
    );

void vscrapExportStack(
    vdelegatorStack 		stack, 
    vdelegatorStack 		dest
    );

void vscrapImport(
    vscrap 			*scrap, 
    vscrap 			*source
    );

void vscrapImportStack(
    vdelegatorStack 		stack, 
    vdelegatorStack 		source
    );

void vscrapConvert(
    vscrap 			*from, 
    vscrap 			*to
    );

void vscrapConvertStack(
    vdelegatorStack 		source, 
    vdelegatorStack 		dest
    );

vclass *vscrapGetConvertibleExportClass(
    vscrapConvertible 		*scrap
    );


/*
 * Typeable scraps
 */

void vscrapSendTypeable(
    vdelegatorStack		*stack,
    ...
    );

vscrapTypeableClass *vscrapGetDefaultTypeableClass(
    void
    );

vscrapTypeableClass *vscrapGetTypeableClass(
    vscrapTypeable 		*scrap
    );

vbool vscrapEntype(
    vscrap 			*scrap, 
    void 			*clas
    );

vbool vscrapEntypeStack(
    vdelegatorStack 		stack, 
    void 			*clas
    );

/*
 * Basic functionality classes and calls
 */

/*
 * integer
 */

void vscrapSendInteger(
    vdelegatorStack		*stack,
    ...
    );

vscrapIntegerClass *vscrapGetDefaultIntegerClass(
    void
    );

vscrapIntegerClass *vscrapGetIntegerClass(
    vscrapInteger 		*scrap
    );

long vscrapGetInteger(
    vscrap 			*scrap
    );

long vscrapGetIntegerStack(
    vdelegatorStack 		stack
    );

void vscrapSetInteger(
    vscrap 			*scrap, 
    long 			value
    );

void vscrapSetIntegerStack(
    vdelegatorStack 		stack, 
    long 			value
    );

/*
 * boolean
 */

void vscrapSendBoolean(
    vdelegatorStack		*stack,
    ...
    );

vscrapBooleanClass *vscrapGetDefaultBooleanClass(
    void
    );

vscrapBooleanClass *vscrapGetBooleanClass(
    vscrapBoolean 		*scrap
    );

vbool vscrapGetBoolean(
    vscrap 			*scrap
    );

vbool vscrapGetBooleanStack(
    vdelegatorStack 		stack
    );

void vscrapSetBoolean(
    vscrap 			*scrap, 
    int /*vbool*/ 		value
    );

void vscrapSetBooleanStack(
    vdelegatorStack 		stack, 
    int /*vbool*/ 		value
    );


/* 
 * real
 */

void vscrapSendFloat(
    vdelegatorStack		*stack,
    ...
    );

vscrapFloatClass *vscrapGetDefaultFloatClass(
    void
    );

vscrapFloatClass *vscrapGetFloatClass(
    vscrapFloat 		*scrap
    );

double vscrapGetFloat(
    vscrap 			*scrap
    );

double vscrapGetFloatStack(
    vdelegatorStack 		stack
    );

void vscrapSetFloat(
    vscrap 			*scrap, 
    double 			value
    );

void vscrapSetFloatStack(
    vdelegatorStack 		stack, 
    double 			value
    );

/* 
 * fixed
 */

void vscrapSendFixed(
    vdelegatorStack		*stack,
    ...
    );

vscrapFixedClass *vscrapGetDefaultFixedClass(
    void
    );

vscrapFixedClass *vscrapGetFixedClass(
    vscrapFixed 		*scrap
    );

vfixed vscrapGetFixed(
    vscrap 			*scrap
    );

vfixed vscrapGetFixedStack(
    vdelegatorStack 		stack
    );

void vscrapSetFixed(
    vscrap 			*scrap, 
    vfixed 			value
    );

void vscrapSetFixedStack(
    vdelegatorStack 		stack, 
    vfixed 			value
    );

/*
 * character
 */

void vscrapSendCharacter(
    vdelegatorStack		*stack,
    ...
    );

vscrapCharacterClass *vscrapGetDefaultCharacterClass(
    void
    );

vscrapCharacterClass *vscrapGetCharacterClass(
    vscrapCharacter 		*scrap
    );

vchar vscrapGetCharacter(
    vscrap 			*scrap
    );

vchar vscrapGetCharacterStack(
    vdelegatorStack 		stack
    );

void vscrapSetCharacter(
    vscrap 			*scrap, 
    int /*vchar*/ 		value
    );

void vscrapSetCharacterStack(
    vdelegatorStack 		stack, 
    int /*vchar*/ 		value
    );

/*
 * string
 */

void vscrapSendString(
    vdelegatorStack		*stack,
    ...
    );

vscrapStringClass *vscrapGetDefaultStringClass(
    void
    );

vscrapStringClass *vscrapGetStringClass(
    vscrapString 		*scrap
    );

vscribe *vscrapScribeString(
    vscrap 			*scrap
    );

vscribe *vscrapScribeStringStack(
    vdelegatorStack 		stack
    );

void vscrapSetStringScribed(
    vscrap 			*scrap, 
    vscribe 			*scribe
    );

void vscrapSetStringScribedStack(
    vdelegatorStack 		stack, 
    vscribe 			*scribe
    );

/*
 * tag
 */

void vscrapSendTag(
    vdelegatorStack		*stack,
    ...
    );

vscrapTagClass *vscrapGetDefaultTagClass(
    void
    );

vscrapTagClass *vscrapGetTagClass(
    vscrapTag 			*scrap
    );

const vname *vscrapGetTag(
    vscrap 			*scrap
    );

const vname *vscrapGetTagStack(
    vdelegatorStack 		stack
    );

void vscrapSetTag(
    vscrap 			*scrap, 
    const vname 		*tag
    );

void vscrapSetTagStack(
    vdelegatorStack 		stack, 
    const vname 		*tag
    );

/*
 * block
 */

void vscrapSendBlock(
    vdelegatorStack		*stack,
    ...
    );

vscrapBlockClass *vscrapGetDefaultBlockClass(
    void
    );

vscrapBlockClass *vscrapGetBlockClass(
    vscrapBlock 		*scrap
    );

size_t vscrapGetBlockSize(
    vscrap 			*scrap
    );

size_t vscrapGetBlockSizeStack(
    vdelegatorStack 		stack
    );

void vscrapSetBlockSize(
    vscrap 			*scrap, 
    size_t 			size
    );

void vscrapSetBlockSizeStack(
    vdelegatorStack 		stack, 
    size_t 			size
    );

void vscrapReadBlock(
    vscrap 			*scrap, 
    size_t 			offset, 
    size_t 			count, 
    void 			*buffer
    );

void vscrapReadBlockStack(
    vdelegatorStack 		stack, 
    size_t 			offset, 
    size_t 			count, 
    void 			*buffer
    );

void vscrapWriteBlock(
    vscrap 			*scrap, 
    size_t 			offset, 
    size_t 			count, 
    const void 			*buffer
    );

void vscrapWriteBlockStack(
    vdelegatorStack 		stack, 
    size_t 			offset, 
    size_t 			count, 
    const void 			*buffer
    );

void vscrapSyncBlock(
    vscrap                      *scrap
    );

void vscrapSyncBlockStack(
    vdelegatorStack             stack
    );

/*
 * compound
 */

void vscrapSendCompound(
    vdelegatorStack		*stack,
    ...
    );

vscrapCompoundIteratorClass *vscrapGetDefaultCompoundIteratorClass(
    void
    );

vscrapCompoundIteratorClass *vscrapGetCompoundIteratorClass(
    vscrapCompoundIterator 	*iter
    );

vscrap *vscrapGetCompoundIteratorElement(
    vscrapCompoundIterator 	*iter
    );

vscrapCompoundClass *vscrapGetDefaultCompoundClass(
    void
    );

vscrapCompoundClass *vscrapGetCompoundClass(
    vscrapCompound 		*scrap
    );

void *vscrapGetCompoundElementIteratorClass(
    vscrapCompound 		*scrap
    );

vscrapCompoundIterator *vscrapCreateCompoundElementIterator(
    vscrap 			*scrap
    );

vscrapCompoundIterator *vscrapCreateCompoundElementIteratorStack(
    vdelegatorStack 		stack
    );

void vscrapEmptyElements(
    vscrap 			*scrap
    );

void vscrapEmptyElementsStack(
    vdelegatorStack 		stack
    );

void vscrapAddElement(
    vscrap 			*scrap,
    vscrap 			*element
    );

void vscrapAddElementStack(
    vdelegatorStack 		stack, 
    vscrap 			*element
    );

/*
 * array
 */

void vscrapSendArray(
    vdelegatorStack		*stack,
    ...
    );

vscrapArrayIteratorClass *vscrapGetDefaultArrayIteratorClass(
    void
    );

vscrapArrayIteratorClass *vscrapGetArrayIteratorClass(
    vscrapArrayIterator 	*iter
    );

size_t vscrapGetArrayIteratorIndex(
    vscrapArrayIterator 	*iter
    );

vscrapArrayClass *vscrapGetDefaultArrayClass(
    void
    );

vscrapArrayClass *vscrapGetArrayClass(
    vscrapArray 		*scrap
    );

size_t vscrapGetArrayCount(
    vscrap 			*scrap
    );

size_t vscrapGetArrayCountStack(
    vdelegatorStack 		stack
    );

void vscrapSetArrayCount(
    vscrap 			*scrap, 
    size_t 			count
    );

void vscrapSetArrayCountStack(
    vdelegatorStack 		stack, 
    size_t 			count
    );

vscrap *vscrapGetElementAt(
    vscrap 			*scrap, 
    size_t 			index
    );

vscrap *vscrapGetElementAtStack(
    vdelegatorStack 		stack, 
    size_t 			index
    );

void vscrapSetElementAt(
    vscrap 			*scrap, 
    size_t 			index, 
    vscrap 			*element
    );

void vscrapSetElementAtStack(
    vdelegatorStack 		stack, 
    size_t 			index, 
    vscrap 			*element
    );

/*
 * dictionary
 */

void vscrapSendDictionary(
    vdelegatorStack		*stack,
    ...
    );

vscrapDictionaryIteratorClass *vscrapGetDefaultDictionaryIteratorClass(
    void
    );

vscrapDictionaryIteratorClass *vscrapGetDictionaryIteratorClass(
    vscrapDictionaryIterator 	*iter
    );

const vname *vscrapGetDictionaryIteratorKey(
    vscrapDictionaryIterator 	*iter
    );

vscrapDictionaryClass *vscrapGetDefaultDictionaryClass(
    void
    );

vscrapDictionaryClass *vscrapGetDictionaryClass(
    vscrapDictionary 		*scrap
    );

vscrap *vscrapLoadElement(
    vscrap 			*scrap, 
    const vname 		*key
    );

vscrap *vscrapLoadElementStack(
    vdelegatorStack 		stack, 
    const vname 		*key
    );

void vscrapStoreElement(
    vscrap 			*scrap, 
    const vname 		*key, 
    vscrap 			*element
    );

void vscrapStoreElementStack(
    vdelegatorStack 		stack, 
    const vname 		*key, 
    vscrap 			*element
    );

void vscrapRemoveElement(
    vscrap 			*scrap, 
    const vname 		*key
    );

void vscrapRemoveElementStack(
    vdelegatorStack 		stack, 
    const vname 		*key 
    );

/* 
 * create scraps of native classes
 */

void vscrapRegisterNativeClass(
    void 			*clas, 
    void 			*implementation
    );

vscrap *vscrapCreateReference(
    vscrap 			*scrap
    );

vscrap *vscrapCreateNative(
    void
    );

vscrap *vscrapConvertToNative(
    vscrap 			*from
    );

vscrap *vscrapFromMemory(
    void 			*pointer, 
    size_t 			size
    );

vscrap *vscrapFromMemoryOwned(
    void 			*pointer, 
    size_t 			size
    );

vscrap *vscrapFromMemoryShared(
    void 			*pointer, 
    size_t 			size
    );

vscrap *vscrapFromInteger(
    long 			value
    );

vscrap *vscrapFromBoolean(
    int /*vbool*/ 		value
    );

vscrap *vscrapFromCharacter(
    int /*vchar */ 		value
    );

vscrap *vscrapFromFloat(
    double 			value
    );

vscrap *vscrapFromFixed(
    vfixed 			value
    );

vscrap *vscrapFromString(
    const vchar			*string
    );

vscrap *vscrapFromStringScribed(
    vscribe 			*scribe
    );

vscrap *vscrapFromTag(
    const vname 		*tag
    );

vscrap *vscrapCreateArray(
    void
    );

vscrap *vscrapCreateDictionary(
    void
    );

vscrap *vscrapCreateMemory(
    void
    );

/*
 * Exceptions:
 */

vscrapUnimplementedException *vscrapGetUnimplementedException(
    void	
    );

vdelegatorStack *vscrapGetUnimplementedExceptionStack(
    vscrapUnimplementedException	*exception
    );

void vscrapGenerateUnimplemented(
    const vdelegatorStack		*stack
    );

vscrapCannotConvertException *vscrapGetCannotConvertException(
    void	
    );

vdelegatorStack *vscrapGetCannotConvertExceptionFrom(
    vscrapCannotConvertException	*exception
    );

vdelegatorStack *vscrapGetCannotConvertExceptionTo(
    vscrapCannotConvertException	*exception
    );

void vscrapGenerateCannotConvert(
    const vdelegatorStack		*from,
    const vdelegatorStack		*to
    );


/*
 * * * * * * * * * * * * * PRIVATELY exported variables * * * * * * * * * *
 */

extern vportLINK const vexClass _vscrapUnimplementedExceptionClass;
extern vportLINK const vexClass _vscrapCannotConvertExceptionClass;

void _vscrapFROM(void *exception, va_list *ap);
void _vscrapTO(void *exception, va_list *ap);
void _vscrapSTACK(void *exception, va_list *ap);

/*
 * * * * * * * * * * * * * * * * MACROS * * * * * * * * * * * * * * * * *
 */

#define vscrapGetDefaultClass() 	\
		((vscrapClass *)vinstanceGetDefaultClass())
#define vscrapGetClass(s)	\
		((vscrapClass *)vinstanceGetClass((vinstance *)(s)))

#define vscrapDestroy(s)	vinstanceDestroy((vinstance *)(s))

#define vscrapIsKindOf(s,c)	vdelegatorIsKindOf((vinstance *)(s),c)

#define _vscrapGetIteratorInstance(i) \
    (vportBASE_OBJECT(i, instance))

#define vscrapGetIteratorClass(i) \
    ((vscrapIteratorClass *) vinstanceGetClass(_vscrapGetIteratorInstance(i)))

#define vscrapNextIterator(i) \
    vclassSend(vscrapGetIteratorClass(i), vscrapNEXT_ITERATOR, (i))
#define vscrapGetIteratorStack(i) \
    (&(i)->stack)

#define vscrapGetConvertibleClass(s) \
    ((vscrapConvertibleClass*)vdelegatorGetClass(s))
#define vscrapSendConvertible(s, m, a) \
    vclassSend(vscrapGetConvertibleClass((vscrapConvertible*) \
					 vdelegatorGetStackTop(s)), \
	       m, a)

#define vscrapDump(s, fd) \
    vscrapDumpStack(vdelegatorMakeObjectStack(s), (fd))
#define vscrapExport(s, d) \
    vscrapExportStack(vdelegatorMakeObjectStack(s), \
		      vdelegatorMakeObjectStack(d))
#define vscrapImport(s, d) \
    vscrapImportStack(vdelegatorMakeObjectStack(s), \
		      vdelegatorMakeObjectStack(d))
#define vscrapConvert(s, d) \
    vscrapConvertStack(vdelegatorMakeObjectStack(s), \
		       vdelegatorMakeObjectStack(d))

#define vscrapGetConvertibleExportClass(s) \
    vclassGet(vscrapGetConvertibleClass(s), vscrapEXPORT_CLASS)

#define vscrapGetTypeableClass(s) \
    ((vscrapTypeableClass*)vdelegatorGetClass(s))
#define vscrapSendTypeable(s, m, a) \
    vclassSend(vscrapGetTypeableClass((vscrapTypeable*) \
				      vdelegatorGetStackTop(s)), \
	       m, a)

#define vscrapEntype(s, fd) \
    vscrapEntypeStack(vdelegatorMakeObjectStack(s), (fd))


#define vscrapGetIntegerClass(s) \
    ((vscrapIntegerClass*)vscrapGetConvertibleClass(s))
#define vscrapSendInteger(s, m, a) \
    vclassSend(vscrapGetIntegerClass((vscrapInteger*) \
				     vdelegatorGetStackTop(s)), \
	       m, a)

#define vscrapGetInteger(s) \
    vscrapGetIntegerStack(vdelegatorMakeObjectStack(s))
#define vscrapSetInteger(s, n) \
    vscrapSetIntegerStack(vdelegatorMakeObjectStack(s), (n))


#define vscrapGetBooleanClass(s) \
    ((vscrapBooleanClass*)vscrapGetConvertibleClass(s))
#define vscrapSendBoolean(s, m, a) \
    vclassSend(vscrapGetBooleanClass((vscrapBoolean*) \
				     vdelegatorGetStackTop(s)), \
	       m, a)

#define vscrapGetBoolean(s) \
    vscrapGetBooleanStack(vdelegatorMakeObjectStack(s))
#define vscrapSetBoolean(s, n) \
    vscrapSetBooleanStack(vdelegatorMakeObjectStack(s), (n))


#define vscrapGetFloatClass(s) \
    ((vscrapFloatClass*)vscrapGetConvertibleClass(s))
#define vscrapSendFloat(s, m, a) \
    vclassSend(vscrapGetFloatClass((vscrapFloat*)vdelegatorGetStackTop(s)), \
	       m, a)

#define vscrapGetFloat(s) \
    vscrapGetFloatStack(vdelegatorMakeObjectStack(s))
#define vscrapSetFloat(s, n) \
    vscrapSetFloatStack(vdelegatorMakeObjectStack(s), (n))


#define vscrapGetFixedClass(s) \
    ((vscrapFixedClass*)vscrapGetConvertibleClass(s))
#define vscrapSendFixed(s, m, a) \
    vclassSend(vscrapGetFixedClass((vscrapFixed*)vdelegatorGetStackTop(s)), \
	       m, a)

#define vscrapGetFixed(s) \
    vscrapGetFixedStack(vdelegatorMakeObjectStack(s))
#define vscrapSetFixed(s, n) \
    vscrapSetFixedStack(vdelegatorMakeObjectStack(s), (n))


#define vscrapGetCharacterClass(s) \
    ((vscrapCharacterClass*)vscrapGetConvertibleClass(s))
#define vscrapSendCharacter(s, m, a) \
    vclassSend(vscrapGetCharacterClass((vscrapCharacter*) \
				       vdelegatorGetStackTop(s)), \
	       m, a)

#define vscrapGetCharacter(s) \
    vscrapGetCharacterStack(vdelegatorMakeObjectStack(s))
#define vscrapSetCharacter(s, n) \
    vscrapSetCharacterStack(vdelegatorMakeObjectStack(s), (n))


#define vscrapGetStringClass(s) \
    ((vscrapStringClass*)vscrapGetConvertibleClass(s))
#define vscrapSendString(s, m, a) \
    vclassSend(vscrapGetStringClass((vscrapString*)vdelegatorGetStackTop(s)), \
	       m, a)

#define vscrapScribeString(s) \
    vscrapScribeStringStack(vdelegatorMakeObjectStack(s))
#define vscrapSetStringScribed(s, n) \
    vscrapSetStringScribedStack(vdelegatorMakeObjectStack(s), (n))


#define vscrapGetTagClass(s) \
    ((vscrapTagClass*)vscrapGetConvertibleClass(s))
#define vscrapSendTag(s, m, a) \
    vclassSend(vscrapGetTagClass((vscrapTag*)vdelegatorGetStackTop(s)), \
	       m, a)

#define vscrapGetTag(s) \
    vscrapGetTagStack(vdelegatorMakeObjectStack(s))
#define vscrapSetTag(s, n) \
    vscrapSetTagStack(vdelegatorMakeObjectStack(s), (n))


#define vscrapGetBlockClass(s) \
    ((vscrapBlockClass*)vscrapGetConvertibleClass(s))
#define vscrapSendBlock(s, m, a) \
    vclassSend(vscrapGetBlockClass((vscrapBlock*)vdelegatorGetStackTop(s)), \
	       m, a)

#define vscrapGetBlockSize(s) \
    vscrapGetBlockSizeStack(vdelegatorMakeObjectStack(s))
#define vscrapSetBlockSize(s, n) \
    vscrapSetBlockSizeStack(vdelegatorMakeObjectStack(s), n)
#define vscrapReadBlock(s, o, c, b) \
    vscrapReadBlockStack(vdelegatorMakeObjectStack(s), o, c, b)
#define vscrapWriteBlock(s, o, c, b ) \
    vscrapWriteBlockStack(vdelegatorMakeObjectStack(s), o, c, b)
#define vscrapSyncBlock(s) \
    vscrapSyncBlockStack(vdelegatorMakeObjectStack(s))


#define vscrapGetCompoundClass(s) \
    ((vscrapCompoundClass*)vscrapGetConvertibleClass(s))
#define vscrapSendCompound(s, m, a) \
    vclassSend(vscrapGetCompoundClass((vscrapCompound*) \
				      vdelegatorGetStackTop(s)), \
	       m, a)

#define vscrapEmptyElements(s) \
    vscrapEmptyElementsStack(vdelegatorMakeObjectStack(s))
#define vscrapAddElement(s, e) \
    vscrapAddElementStack(vdelegatorMakeObjectStack(s), (e))


#define vscrapGetCompoundElementIteratorClass(c) \
    vclassGet(vscrapGetCompoundClass(c), vscrapELEMENT_ITERATOR_CLASS) 
#define vscrapCreateCompoundElementIterator(s) \
    vscrapCreateCompoundElementIteratorStack(vdelegatorMakeObjectStack(s))

#define vscrapGetCompoundIteratorClass(i) \
    ((vscrapCompoundIteratorClass *)vscrapGetIteratorClass(i))
#define vscrapGetCompoundIteratorElement(i) \
    vclassSend(vscrapGetCompoundIteratorClass(i), vscrapGET_ITERATOR_ELEMENT, \
	       (i))

#define vscrapGetArrayClass(s) \
    ((vscrapArrayClass*)vscrapGetCompoundClass(s))
#define vscrapSendArray(s, m, a) \
    vclassSend(vscrapGetArrayClass((vscrapArray*)vdelegatorGetStackTop(s)), \
	       m, a)

#define vscrapGetArrayCount(s) \
    vscrapGetArrayCountStack(vdelegatorMakeObjectStack(s))
#define vscrapSetArrayCount(s, n) \
    vscrapSetArrayCountStack(vdelegatorMakeObjectStack(s), (n))
#define vscrapGetElementAt(s, n) \
    vscrapGetElementAtStack(vdelegatorMakeObjectStack(s), (n))
#define vscrapSetElementAt(s, n, e) \
    vscrapSetElementAtStack(vdelegatorMakeObjectStack(s), (n), (e))

#define vscrapGetArrayIteratorClass(i) \
    ((vscrapArrayIteratorClass*)vscrapGetIteratorClass(i))
#define vscrapGetArrayIteratorIndex(i) \
    vclassSend(vscrapGetArrayIteratorClass(i), \
	       vscrapGET_ITERATOR_INDEX, (i))

#define vscrapGetDictionaryClass(s) \
    ((vscrapDictionaryClass*)vscrapGetCompoundClass(s))
#define vscrapSendDictionary(s, m, a) \
    vclassSend(vscrapGetDictionaryClass((vscrapDictionary*) \
					vdelegatorGetStackTop(s)), \
	       m, a)

#define vscrapLoadElement(s, k) \
    vscrapLoadElementStack(vdelegatorMakeObjectStack(s), (k))
#define vscrapStoreElement(s, k, e) \
    vscrapStoreElementStack(vdelegatorMakeObjectStack(s), (k), (e))
#define vscrapRemoveElement(s, k) \
    vscrapRemoveElementStack(vdelegatorMakeObjectStack(s), (k))

#define vscrapGetDictionaryIteratorClass(i) \
    ((vscrapDictionaryIteratorClass*)vscrapGetIteratorClass(i))
#define vscrapGetDictionaryIteratorKey(i) \
    vclassSend(vscrapGetDictionaryIteratorClass(i), \
	       vscrapGET_ITERATOR_KEY, (i))

#define vscrapFromString(s) 		vscrapFromStringScribed(vcharScribe(s))

#define vscrapGetUnimplementedException() \
    ((vscrapUnimplementedException *) \
     vexGetExceptionOfClass(&_vscrapUnimplementedExceptionClass))
#define vscrapGetUnimplementedExceptionStack(e) \
    (&(e)->stack)

#define vscrapGetCannotConvertException() \
    ((vscrapCannotConvertException *) \
     vexGetExceptionOfClass(&_vscrapCannotConvertExceptionClass))
#define vscrapGetCannotConvertExceptionFrom(e) \
    (&(e)->from)
#define vscrapGetCannotConvertExceptionTo(e) \
    (&(e)->to)

#define vscrapGenerateCannotConvert(f, t) \
    vexGenerate(&_vscrapCannotConvertExceptionClass, \
		_vscrapFROM, (f), _vscrapTO, (t), \
		vexNULL)

#define vscrapGenerateUnimplemented(s) \
    vexGenerate(&_vscrapUnimplementedExceptionClass, \
		_vscrapSTACK, (s), \
		vexNULL)

vportEND_CPLUSPLUS_EXTERN_C

#endif /* #ifndef vscrapINCLUDED */


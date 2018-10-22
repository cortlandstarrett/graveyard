/* $Id: vscribe.h,v 1.27 1996/03/23 00:39:52 chad Exp $ */

/******************************************
 * vscribe.h
 * 
 * Scribe header file for String Manager
 * 
 * Part of Galaxy Application Environment
 *
 * Copyright (C) 1992 Visix Software Inc.
 * All rights reserved.
 ******************************************/

#ifndef vscribeINCLUDED
#define vscribeINCLUDED 1


#ifndef  vportINCLUDED		/* for v*HEADER */
#include <vport.h>
#endif

#ifndef  vstdINCLUDED		/* for vbool */
#include vstdHEADER
#endif

#ifndef  vstddefINCLUDED	/* for size_t */
#include vstddefHEADER
#endif

#ifndef  vmemINCLUDED
#include vmemHEADER
#endif
    

vportBEGIN_CPLUSPLUS_EXTERN_C


/*
 * * * * * * * * * * * * * Types * * * * * * * * * * * * * *
 */

typedef struct vscribe		vscribe;
typedef struct vscribeFuncs	vscribeFuncs;

typedef void *(*vscribeScribbleFunc)(vscribe *scribe, void *dest, 
				     size_t destMaxLength); 

typedef size_t (*vscribeLengthFunc)(vscribe *scribe, 
				    size_t destMaxLength);

typedef void (*vscribeFreeDataFunc)(vscribe *scribe);

struct vscribeFuncs
{
  vscribeScribbleFunc		scribble;
  vscribeLengthFunc		length;
  vscribeFreeDataFunc		freeData;
  size_t			defaultUnitSize;
};

struct vscribe
{
  const vscribeFuncs 	*funcs;
  const void		*string;
  const void		*data;
  size_t		unitSize;
  unsigned short	flags;
};

/*
 * * * * * * * * * * * * * Constants * * * * * * * * * * * * * *
 */

#if !(vportBAD_WEAK_EXTERNS)
extern vportLINK const size_t	vscribeMAX_LENGTH;
#endif

/*
 * * * * * * * * * * * * * Functions * * * * * * * * * * * * * *
 */

/* literal */ vscribeFuncs vscribeFuncsDEC(
    vscribeScribbleFunc 	scribble, 
    vscribeLengthFunc 	    	length,
    vscribeFreeDataFunc 	freeData,
    size_t   	    	    	unitSize
    );

/*
 * Create/destroy scribes.
 */

vscribe *vscribeCreate(
    const vscribeFuncs 	    	*funcs
    );

void vscribeDestroy(
    vscribe 	    	    	*scribe
    );

void vscribeSetString(
    vscribe 	    	    	*scribe, 
    const void 	    	    	*string
    );

void *vscribeGetString(
    const vscribe   	    	*scribe
    );

void vscribeSetData(
    vscribe 	    	    	*scribe, 
    const void 	    	    	*data
    );

void *vscribeGetData(
    const vscribe   	    	*scribe
    );

size_t vscribeGetUnitSize(
    const vscribe   	    	*scribe
    );

void vscribeSetUnitSize(
    vscribe   	    		*scribe,
    size_t			size
    );

vbool vscribeIsCopy(
    const vscribe   	    	*scribe
    );

void vscribeSetCopy(
    vscribe 	    	    	*scribe
    );

void vscribeClearCopy(
    vscribe 	    	    	*scribe
    );

vbool vscribeIsCopySized(
    const vscribe   	    	*scribe
    );

void vscribeSetCopySized(
    vscribe 	    	    	*scribe
    );

void vscribeClearCopySized(
    vscribe 	    	    	*scribe
    );

vbool vscribeIsDynamic(
    const vscribe   	    	*scribe
    );

void vscribeSetDynamic(
    vscribe 	    	    	*scribe
    );

void vscribeClearDynamic(
    vscribe 	    	    	*scribe
    );

vbool vscribeIsShare(
    const vscribe   	    	*scribe
    );

void vscribeSetShare(
    vscribe 	    	    	*scribe
    );

void vscribeClearShare(
    vscribe 	    	    	*scribe
    );

vbool vscribeIsShareSized(
    const vscribe   	    	*scribe
    );

void vscribeSetShareSized(
    vscribe 	    	    	*scribe
    );

void vscribeClearShareSized(
    vscribe 	    	    	*scribe
    );

vbool vscribeIsInterned(
    const vscribe   	    	*scribe
    );

void vscribeSetInterned(
    vscribe 	    	    	*scribe
    );

void vscribeClearInterned(
    vscribe 	    	    	*scribe
    );

/*
 * Using scribes:
 */

void *vscribeGetUnscribed(
    vscribe 	    	    	*scribe
    );

void *vscribeScribble(
    vscribe 	    	    	*scribe, 
    void    	    	    	*dest
    );

void *vscribeScribbleBounded(
    vscribe 	    	    	*scribe,
    void    	    	    	*dest, 
    size_t  	    	    	destMaxLength
    );

size_t vscribeGetLength(
    const vscribe   	    	*scribe
    );

size_t vscribeGetLengthBounded(
    const vscribe   	    	*scribe, 
    size_t  	    	    	maxLength
    );

/*
 * Multi scribing:
 */

vscribe *vscribeScribeMulti(
    vscribe 	    	    	*scribe1, 
    ... 
    /* , NULL */
    );

vscribe *vscribeConcatenate(
    vscribe			*scribe1,
    vscribe			*scribe2
    );

#if vdebugDEBUG

vscribe *vscribeCreateDebug(
    const vscribeFuncs 	    	*funcs,
    const char 	    	    	*tag, 
    const char 	    	    	*file, 
    int     	    	    	line
    );

#endif

/*
 * * * * * * * * * * * * * * * Private constants * * * * * * * * * * * * * * *
 */

enum
{
  _vscribeCOPY		= 0x01,
  _vscribeCOPY_SIZED	= 0x02,
  _vscribeDYNAMIC	= 0x04,
  _vscribeSHARE		= 0x08,
  _vscribeSHARE_SIZED	= 0x10,
  _vscribeINTERNED	= 0x20
};

/*
 * * * * * * * * * * * * * * * Function MACROs * * * * * * * * * * * * * * *
 */

/* 
 * This is not the maximum possible value if size_t is unsigned,
 * but it still should be bigger than any reasonable bounds limit
 * and fit in a signed/unsigned int/long on a 32 or 64 bit arch.
 */
#define vscribeMAX_LENGTH		((size_t)0x7fffffff)

vportBEGIN_MUST_BE_MACRO

#define vscribeFuncsDEC(_s, _l, _f, _us)  { _s, _l, _f, _us } 

vportEND_MUST_BE_MACRO

#define vscribeSetString(_s, _d)	((void) ((_s)->string = (_d)))
#define vscribeGetString(_s)		((void *) (_s)->string)

#define vscribeSetData(_s, _d)		((void) ((_s)->data = (_d)))
#define vscribeGetData(_s)		((void *) (_s)->data)

#define vscribeSetUnitSize(_s, _n)	((void ) ((_s)->unitSize = (_n)))
#define vscribeGetUnitSize(_s)		((_s)->unitSize)

#define vscribeIsCopy(_s) \
    (((_s)->flags & \
      (_vscribeCOPY|_vscribeSHARE|_vscribeDYNAMIC|_vscribeINTERNED)) != 0U)
#define vscribeSetCopy(_s) \
    ((void) ((_s)->flags |= _vscribeCOPY))
#define vscribeClearCopy(_s) \
    ((void) ((_s)->flags &= ~_vscribeCOPY))

#define vscribeIsCopySized(_s) \
    (((_s)->flags & \
      (_vscribeCOPY|_vscribeCOPY_SIZED|_vscribeSHARE|_vscribeSHARE_SIZED \
       |_vscribeDYNAMIC|_vscribeINTERNED)) != 0U)
#define vscribeSetCopySized(_s)	\
    ((void) ((_s)->flags |= _vscribeCOPY_SIZED))
#define vscribeClearCopySized(_s) \
    ((void) ((_s)->flags &= ~_vscribeCOPY_SIZED))

#define vscribeIsDynamic(_s) \
    (((_s)->flags & _vscribeDYNAMIC) != 0U)
#define vscribeSetDynamic(_s)	\
    ((void) ((_s)->flags |= _vscribeDYNAMIC))
#define vscribeClearDynamic(_s) \
    ((void) ((_s)->flags &= ~_vscribeDYNAMIC))

#define vscribeIsShare(_s) \
    (((_s)->flags & (_vscribeSHARE|_vscribeINTERNED)) != 0U)
#define vscribeSetShare(_s)	\
    ((void) ((_s)->flags |= _vscribeSHARE))
#define vscribeClearShare(_s) \
    ((void) ((_s)->flags &= ~_vscribeSHARE))

#define vscribeIsShareSized(_s) \
    (((_s)->flags & (_vscribeSHARE|_vscribeSHARE_SIZED|_vscribeINTERNED)) \
     != 0U)
#define vscribeSetShareSized(_s)	\
    ((void) ((_s)->flags |= _vscribeSHARE_SIZED))
#define vscribeClearShareSized(_s) \
    ((void) ((_s)->flags &= ~_vscribeSHARE_SIZED))

#define vscribeIsInterned(_s) \
    (((_s)->flags & _vscribeINTERNED) != 0U)
#define vscribeSetInterned(_s)	\
    ((void) ((_s)->flags |= _vscribeINTERNED))
#define vscribeClearInterned(_s) \
    ((void) ((_s)->flags &= ~_vscribeINTERNED))

#if vdebugDEBUG

#define vscribeCreate(funcs) \
    vscribeCreateDebug(funcs, vmemTAG, __FILE__, __LINE__)

#endif


vportEND_CPLUSPLUS_EXTERN_C


#endif /* #ifndef vscribeINCLUDED */


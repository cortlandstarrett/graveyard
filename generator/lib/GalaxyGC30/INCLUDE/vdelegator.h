/* $Id: vdelegator.h,v 1.10 1996/03/23 00:41:02 chad Exp $ */

/******************************************
 *
 * vdelegator.h
 *
 * Multi-objects 
 *
 * Part of Galaxy Application Environment
 *
 * Copyright (C) 1992 Visix Software Inc.
 * All rights reserved.
 ******************************************/


#ifndef vdelegatorINCLUDED
#define vdelegatorINCLUDED 1

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

#ifndef  vnameINCLUDED
#include vnameHEADER
#endif

#ifndef  vclassINCLUDED
#include vclassHEADER
#endif

#ifndef  vinstanceINCLUDED
#include vinstanceHEADER
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C


/*
 * * * * * * * * * * * * * Types * * * * * * * * * * * * * *
 */


typedef vinstance		vdelegator;
typedef struct vdelegatorClass	vdelegatorClass;

#define _vdelegatorSTACK_SIZE	12

typedef struct vdelegatorStack
{
  short 	top;
  short 	privateTop;
  vinstance 	*objects[_vdelegatorSTACK_SIZE];
} vdelegatorStack;

#define vdelegatorCLASS(CLASS, OBJECT)					\
    vinstanceCLASS(CLASS, OBJECT);					\
    vclassMETHOD_RET(vdelegatorNEXT_DELEGATE, void *,			\
		     (OBJECT *object, void *prev, int seePrivate))

struct vdelegatorClass 
{
  vdelegatorCLASS(vdelegatorClass, vdelegator);
};


typedef struct vdelegatorClassNotFoundException
{
  vexException		super;
  vdelegatorStack	stack;
  void			*clas;
} vdelegatorClassNotFoundException;

  
/*
 * * * * * * * * * * * * * Function Prototypes * * * * * * * * * * * * * *
 */

void vdelegatorStartup(void);

/*
 * Stack routines
 */

vdelegatorStack vdelegatorMakeStack(
    const vdelegatorStack	*stack
    );

vdelegatorStack vdelegatorMakeObjectStack(
    vinstance 			*object
    );

vdelegatorStack vdelegatorMakeResendStack(
    const vdelegatorStack	*stack
    );

vdelegatorStack vdelegatorMakeBackupStack(
    const vdelegatorStack	*stack,
    int				levels
    );

void vdelegatorCopyStack(
    const vdelegatorStack	*from,
    vdelegatorStack		*to
    );

vbool vdelegatorAdvanceStack(
    vdelegatorStack		*stack,
    int /*vbool*/		seePrivates
    );			  

void vdelegatorDirectStack(
    vdelegatorStack		*stack,
    void			*methodClass
    );

void *vdelegatorGetStackNth(
    const vdelegatorStack	*stack,
    size_t			n
    );			   

void *vdelegatorGetStackTop(
    const vdelegatorStack	*stack
    );

void *vdelegatorGetStackBottom(
    const vdelegatorStack	*stack
    );

size_t vdelegatorGetStackHeight(
    const vdelegatorStack 	*stack
    );

void vdelegatorDumpStack(
    const vdelegatorStack	*stack,
    FILE			*fp
    );		       

void vdelegatorDumpStackShallow(
    const vdelegatorStack	*stack,
    FILE			*fp
    );		       

/*
 * Multi-object routines
 */

vdelegatorClass *vdelegatorGetDefaultClass(
    void
    );

vdelegatorClass *vdelegatorGetClass(
    vdelegator			*object
    );

vinstance *vdelegatorGetInstance(
    vdelegator			*object
    );

vbool vdelegatorIsKindOf(
    vinstance			*object,
    void			*clas
    );

vinstance *vdelegatorNextDelegate(
    vdelegator			*object,
    vinstance			*prev,
    int /* vbool */		seePrivate
    );

/*
 * Exceptions:
 */

vdelegatorClassNotFoundException *vdelegatorGetClassNotFoundException(
    void
    );

vdelegatorStack *vdelegatorGetClassNotFoundExceptionStack(
    vdelegatorClassNotFoundException	*e
    );

void *vdelegatorGetClassNotFoundExceptionClass(
    vdelegatorClassNotFoundException	*e
    );


/*
 * * * * * * * * * PRIVATE non-exported variables * * * * * * * * * * 
 */

extern vportLINK const vexClass _vdelegatorClassNotFoundExceptionClass;

/*
 * * * * * * * * * PRIVATE prototypes * * * * * * * * * * 
 */

void *_vdelegatorNextDelegateRaw(
    vdelegator			*object,
    void			*prev,
    int /* vbool */		seePrivate
    );

/*
 * * * * * * * * * * * * * Function MACROS * * * * * * * * * * * * * *
 */

#define vdelegatorGetStackTop(s) \
    ((void *) (s)->objects[(s)->top])
#define vdelegatorGetStackBottom(s) \
    ((void *) (s)->objects[0])
#define vdelegatorGetStackNth(s,n) \
    ((void *) (s)->objects[(s)->top - (n)])
#define vdelegatorGetStackHeight(s) \
    ((s)->top + 1)

#define vdelegatorGetInstance(o) \
    (o)
#define vdelegatorGetClass(o) \
    ((vdelegatorClass*)vinstanceGetClass(vdelegatorGetInstance(o)))

#define _vdelegatorNextDelegateRaw(o, p, s) \
    vclassSend(vdelegatorGetClass(o), vdelegatorNEXT_DELEGATE, ((o),(p),(s)))

#define vdelegatorNextDelegate(o, p, s) \
    ((vinstance *) _vdelegatorNextDelegateRaw(o, p, s))

#define vdelegatorGetClassNotFoundException() \
    ((vdelegatorClassNotFoundException *) \
     vexGetExceptionOfClass(&_vdelegatorClassNotFoundExceptionClass))
#define vdelegatorGetClassNotFoundExceptionStack(e) \
    (&(e)->stack)
#define vdelegatorGetClassNotFoundExceptionClass(e) \
    ((e)->clas)


vportEND_CPLUSPLUS_EXTERN_C

#endif /* #ifndef vdelegatorINCLUDED */


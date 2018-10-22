/* $Id: viterator.h,v 1.8 1997/07/14 19:26:40 robert Exp $ */

/************************************************************

    viterator.h

    (c) Copyright Visix Software Inc.
    All rights reserved

************************************************************/

#ifndef viteratorINCLUDED
#define viteratorINCLUDED

#ifndef	 vportINCLUDED
#include <vport.h>
#endif

#ifndef	 vinstanceINCLUDED
#include vinstanceHEADER
#endif


vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * * * * * * * * * * PUBLIC TYPE DEFINITIONS * * * * * * * * * *
 */

typedef struct viterator		viterator;
typedef struct viteratorGroup		viteratorGroup;

typedef struct viteratorClass		viteratorClass;
typedef struct viteratorGroupClass	viteratorGroupClass;

/*
 * exceptions
 */

typedef vexArgException                 viteratorNotStartedException;
typedef vexArgException                 viteratorNoAvailableElementException;


/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */

void			 viteratorStartup(void);


/*
 * viterator
 */

viteratorClass		*viteratorGetDefaultClass(
	void
	);

viteratorClass		*viteratorGetClass(
	viterator			*iterator
	);

vinstance		*viteratorGetInstance(
	viterator			*iterator
	);

viterator		*viteratorCreateOfClass(
	viteratorClass			*clas
	);

void			 viteratorInitOfClass(
	viterator			*iterator,
	viteratorClass			*clas
	);

void			 viteratorDestroy(
	viterator			*iterator
	);

vbool			 viteratorHasMoreElements(
	viterator			*iterator
	);

void			 viteratorStart(
	viterator			*iterator,
	vinstance			*starter
	);

vbool			 viteratorNext(
	viterator			*iterator
	);

vinstance		*viteratorGetStarter(
	viterator			*iterator
	);

const void		*viteratorGetElementUntyped(
	viterator			*iterator
	);

vinstance		*viteratorGetElement(
	viterator			*iterator
	);

const void		*viteratorGetNextElementUntyped(
	viterator			*iterator
	);

vinstance		*viteratorGetNextElement(
	viterator			*iterator
	);

void			 viteratorFinish(
	viterator			*iterator
	);

/*
 * viteratorGroup
 */

viteratorGroupClass	*viteratorGetDefaultGroupClass(
	void
	);

viteratorGroupClass	*viteratorGetGroupClass(
	viteratorGroup			*iterator
	);

viterator		*viteratorGetGroupIterator(
	viteratorGroup			*iterator
	);

viteratorGroup		*viteratorCreateGroup(
	);

viteratorGroup		*viteratorCreateGroupOfClass(
	viteratorGroupClass		*clas
	);

void			 viteratorInitGroup(
	viteratorGroup			*iterator
	);

void			 viteratorInitGroupOfClass(
	viteratorGroup			*iterator,
	viteratorGroupClass		*clas
	);

void			 viteratorDestroyGroup(
	viteratorGroup			*iterator
	);

void			 viteratorInsertGroupPartOwned(
	viteratorGroup			*iterator,
	int				 index,
	viterator			*partialIterator
	);

void			 viteratorAppendGroupPartOwned(
	viteratorGroup			*iterator,
	viterator			*partialIterator
	);

viterator		*viteratorRemoveGroupPartAt(
	viteratorGroup			*iterator,
	int				 index
	);

int			 viteratorGetGroupPartCount(
	viteratorGroup			*iterator
	);

viterator		*viteratorGetGroupPartAt(
	viteratorGroup			*iterator,
	int				 index
	);

/*
 * exceptions
 */

const vexClass *viteratorGetNotStartedExceptionClass(
    void
    );

const vexClass *viteratorGetNoAvailableElementExceptionClass(
    void
    );

viteratorNotStartedException *viteratorGetNotStartedException(
    void
    );

viteratorNoAvailableElementException *viteratorGetNoAvailableElementException(
    void
    );


/*
 * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * *
 */

enum
{
  _viteratorBEFORE_START	= 0,
  _viteratorAFTER_START		= 1,
  _viteratorAFTER_FIRST		= 2,
  _viteratorAFTER_NEXT		= 3,
  _viteratorAFTER_LAST		= 4
};


struct viterator
{
  vinstance	 super;

  vinstance	*starter;
  vbyte		 state;
};

#define viteratorCLASS(CLASS, ITERATOR)					\
    vinstanceCLASS(CLASS, ITERATOR);					\
    vclassVARIABLE(viteratorTYPED_ELEMENT_CLASS, vclass *);		\
    vclassMETHOD(viteratorSTART,					\
		 (ITERATOR *iterator, vinstance *starter));		\
    vclassMETHOD_RET(viteratorNEXT, vbool, (ITERATOR *iterator));	\
    vclassMETHOD_RET(viteratorGET_ELEMENT_UNTYPED, const void *,\
		     (ITERATOR *iterator));				\
    vclassMETHOD_RET(viteratorGET_ELEMENT_TYPED, vinstance *,	\
		     (ITERATOR *iterator));				\
    vclassMETHOD(viteratorFINISH, (ITERATOR *iterator))

struct viteratorClass
{
  viteratorCLASS(viteratorClass, viterator);
};


struct viteratorGroup
{
  viterator	  iterator;

  int		  partCount, partAlloc;
  viterator	**parts;
};

#define viteratorGROUP_CLASS(CLASS, ITERATOR)				\
    viteratorCLASS(CLASS, ITERATOR);					\
    vclassVARIABLE(viteratorGROUP_PART_CLASS, vclass *);		\
    vclassMETHOD(viteratorINSERT_GROUP_PART_OWNED,			\
		 (ITERATOR *iterator, int index, viterator *partial));  \
    vclassMETHOD_RET(viteratorREMOVE_GROUP_PART_AT, viterator *,	\
		 (ITERATOR *iterator, int index))

struct viteratorGroupClass
{
  viteratorGROUP_CLASS(viteratorGroupClass, viteratorGroup);
};


/*
 * * * * * * * * * * PRIVATE VARIABLE DECLARATIONS * * * * * * * * * *
 */

/*
 * * * * * * * * * * PRIVATE FUNCTION PROTOTYPES * * * * * * * * * *
 */

void _viteratorSendStart(viterator *iterator, vinstance *starter);
vbool _viteratorSendNext(viterator *iterator);
vinstance *_viteratorSendGetElementTyped(viterator *iterator);
const void *_viteratorSendGetElementUntyped(viterator *iterator);
void _viteratorSendFinish(viterator *iterator);


/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * *
 */

#define viteratorGetInstance(i)		vportBASE_OBJECT(i, super)
#define viteratorGetClass(i) \
    ((viteratorClass *) vinstanceGetClass(viteratorGetInstance(i)))

#define viteratorCreateOfClass(c) \
    ((viterator *) vinstanceCreateOfClass((vinstanceClass *)(c)))
#define viteratorInitOfClass(i, c) \
    vinstanceInitOfClass(viteratorGetInstance(i), (vinstanceClass *)(c))
#define viteratorDestroy(i) \
    vinstanceDestroy(viteratorGetInstance(i))

#define viteratorGetStarter(i) \
    ((i)->starter)

#define viteratorGetGroupIterator(i)		vportBASE_OBJECT(i, iterator)
#define viteratorGetGroupClass(i) \
    ((viteratorGroupClass *) \
       viteratorGetClass(viteratorGetGroupIterator(i)))

#define viteratorCreateGroupOfClass(c) \
    ((viteratorGroup *) viteratorCreateOfClass((viteratorClass *)(c)))
#define viteratorCreateGroup() \
    viteratorCreateGroupOfClass(viteratorGetDefaultGroupClass())
#define viteratorInitGroupOfClass(i, c) \
    viteratorInitOfClass(viteratorGetGroupIterator(i), \
			 (viteratorClass *)(c))
#define viteratorInitGroup(i) \
    viteratorInitGroupOfClass(i, viteratorGetDefaultGroupClass())
#define viteratorDestroyGroup(i) \
    viteratorDestroy(viteratorGetGroupIterator(i))

#define viteratorAppendGroupPartOwned(i,p) \
    viteratorInsertGroupPartOwned(i, viteratorGetGroupPartCount(i), p)

#define viteratorGetNotStartedException() \
    ((viteratorNotStartedException*) \
         vexGetExceptionOfClass(viteratorGetNotStartedExceptionClass()))

#define viteratorGetNoAvailableElementException() \
    ((viteratorNoAvailableElementException*) \
        vexGetExceptionOfClass(viteratorGetNoAvailableElementExceptionClass()))

/*
 * * * * * * * * * * PRIVATE FUNCTION MESSAGE DEFINITIONS * * * * * * * * * *
 */

#define _viteratorSendStart(i, s) \
    vclassSend(viteratorGetClass(i), viteratorSTART, (i, s))
#define _viteratorSendNext(i) \
    vclassSend(viteratorGetClass(i), viteratorNEXT, (i))
#define _viteratorSendGetElementUntyped(i) \
    vclassSend(viteratorGetClass(i), viteratorGET_ELEMENT_UNTYPED, (i))
#define _viteratorSendGetElementTyped(i) \
    vclassSend(viteratorGetClass(i), viteratorGET_ELEMENT_TYPED, (i))
#define _viteratorSendFinish(i) \
    vclassSend(viteratorGetClass(i), viteratorFINISH, (i))

#define viteratorInsertGroupPartOwned(i, n, p) \
    vclassSend(viteratorGetGroupClass(i), \
	       viteratorINSERT_GROUP_PART_OWNED, (i, n, p))
#define viteratorRemoveGroupPartAt(i, n) \
    vclassSend(viteratorGetGroupClass(i), \
	       viteratorREMOVE_GROUP_PART_AT, (i, n))

vportEND_CPLUSPLUS_EXTERN_C


#endif /* #ifndef viteratorINCLUDED */

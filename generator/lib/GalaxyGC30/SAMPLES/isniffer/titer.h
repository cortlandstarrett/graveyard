/* $Id: titer.h,v 1.2 1995/02/09 00:04:02 simone Exp $ */
/****************************************************************************
 *                (c) Copyright 1991-1994 Visix Software, Inc.              *
 *                           All rights reserved.                           *
 * The following Sample Code is provided for your reference purposes in     *
 * connection with your use of the Galaxy Application Environment (TM)      *
 * software product which you have licensed from Visix Software, Inc.       *
 * ("Visix"). The Sample code is provided to you without any warranty of any*
 * kind and you agree to be responsible for the use and/or incorporation    *
 * of the Sample Code into any software product you develop. You agree to   *
 * fully and completely indemnify and hold Visix harmless from any and all  *
 * loss, claim, liability or damages with respect to your use of the Sample *
 * Code.                                                                    *
 *                                                                          *
 * Subject to the foregoing, you are permitted to copy, modify, and         *
 * distribute the Sample Code for any purpose, and without fee, provided    *
 * that (i) a copyright notice in the in the form of "Copyright 1992 Visix  *
 * Software Inc., 11440 Commerce Park Drive, Reston, VA  22091. All Rights  *
 * Reserved" appears in all copies, (ii) both the copyright notice and this *
 * permission notice appear in all supporting documentation and (iii) you   *
 * are a valid licensee of The Galaxy Application Environment.              *
 *                                                                          *
 ****************************************************************************
 *                                                                          *
 * Description:                                                             *
 *     This module implements a very simple iterator class. used by isnoop  *
 *     application.                                                         *
 *                                                                          *
 * Modification History:                                                    *
 *     o 12-11-93: created for galaxy 2.0 (ssmc)                            *
 *                                                                          *
 * Special Usage Notes:                                                     *
 *     o                                                                    *
 *                                                                          *
 * Text Editor Formatting:                                                  *
 *     Symantec: Tab(8), Font(Any Fixed Width)                              *
 *     Emacs: see end of file for info                                      *
 ****************************************************************************
 */

#ifndef titeratorINCLUDED
#define titeratorINCLUDED 1

#ifndef vportINCLUDED
#include <vport.h>
#endif

#ifndef vexINCLUDED
#include vexHEADER
#endif

#ifndef vclassINCLUDED
#include vclassHEADER
#endif

#ifndef vobjectINCLUDED
#include vobjectHEADER
#endif


/*
 *+------------------------------------------------------------------------+
 * types and classes
 *+------------------------------------------------------------------------+
 */

typedef struct titerator {
  vobject	baseobject;
  const void   *binding;
  const void   *data;
}titerator;

typedef struct tseqiterator {
  titerator	baseobject;
}tseqiterator;


typedef struct titeratorClass titeratorClass;
#define titeratorCLASS(CLAS, ITERATOR)				\
  vobjectCLASS(CLAS, ITERATOR);					\
  vclassMETHOD_RET(titeratorMORE, int, (ITERATOR*));		\
  vclassMETHOD(titeratorSTART_OVER,(ITERATOR *));		\
  vclassMETHOD(titeratorBIND, (ITERATOR*, const void*));	\
  vclassMETHOD(titeratorADVANCE,(ITERATOR *));			\
  vclassMETHOD_RET(titeratorSET_DATA, const void*, (ITERATOR *, \
						    const void*))

struct titeratorClass {
  titeratorCLASS(titeratorClass, titerator);
};


typedef struct tseqiteratorClass tseqiteratorClass;
#define tseqiteratorCLASS(CLAS, ITERATOR)			\
  titeratorCLASS(CLAS, ITERATOR);				\
  vclassMETHOD_RET(tseqiteratorGET_AT, int, (ITERATOR*));	\
  vclassMETHOD_RET(tseqiteratorGET_REMAINING, int, (ITERATOR *iter))

struct tseqiteratorClass {
  tseqiteratorCLASS(tseqiteratorClass, tseqiterator);
};

/*
 *+------------------------------------------------------------------------+
 * titerator: exported routines
 *+------------------------------------------------------------------------+
 */

titeratorClass	*titeratorGetDefaultClass(
    void
    );

tseqiteratorClass *tseqiteratorGetDefaultClass(
    void
    );

titerator *titeratorCreateOfClass(
    titeratorClass              *clas
    );

tseqiterator *tseqiteratorCreateOfClass(
    tseqiteratorClass           *clas
    );

titerator *titeratorCreate(
    void
    );

tseqiterator *tseqiteratorCreate(
    void
    );

titerator *titeratorClone( 
    titerator                   *iterator
    );

tseqiterator *tseqiteratorClone( 
    tseqiterator                *iterator
    );

void titeratorInitOfClass(
    titerator                   *iterator,
    titeratorClass              *clas
    );

void tseqiteratorInitOfClass(
    tseqiterator                *iterator,
    tseqiteratorClass           *clas
    );

void titeratorInit(
    titerator                   *iterator
    );

void tseqiteratorInit(
    tseqiterator                *iterator
    );

void titeratorDestroy(
    titerator                   *iterator
    );

void tseqiteratorDestroy(
    tseqiterator                *iterator
    );

void titeratorCopy(
    titerator                   *iterator,
    titerator                   *target
    );

void tseqiteratorCopy(
    tseqiterator                *iterator,
    tseqiterator                *target
    );

void titeratorCopyInit(
    titerator                   *iterator,
    titerator                   *target
    );

void tseqiteratorCopyInit(
    tseqiterator                *iterator,
    tseqiterator                *target
    );

titerator *titeratorLoad(
    vresource                    resource
    );

tseqiterator *tseqiteratorLoad(
    vresource                    resource
    );

void titeratorLoadInit(
    titerator                   *iterator,
    vresource                    resource
    );

void tseqiteratorLoadInit(
    tseqiterator                *iterator,
    vresource                    resource
    );

void titeratorStore(
    titerator                   *iterator,
    vresource                    resource
    );

void tseqiteratorStore(
    tseqiterator                *iterator,
    vresource                    resource
    );

int titeratorIsKindOf(
    titerator                 	*iterator,
    titeratorClass              *clas
    );

int tseqiteratorIsKindOf(
    tseqiterator              	*iterator,
    tseqiteratorClass           *clas
    );

void titeratorSetTag(
    titerator                   *iterator,
    const vname                 *tag
    );

void titeratorAssociate(
    titerator                   *iterator,
    const void                  *binding
    );

void tseqiteratorAssociate(
    tseqiterator                *iterator,
    const void                  *binding
    );

int titeratorMore(
    titerator			*iterator
    );

int tseqiteratorMore(
    tseqiterator	   	*iterator
    );

void titeratorStartOver(
    titerator                   *iterator
    );

void tseqiteratorStartOver(
    tseqiterator                *iterator
    );

void titeratorAdvance(
    titerator			*iterator
    );

void tseqiteratorAdvance(
    tseqiterator		*iterator
    );

const void *titeratorSetData(
    titerator                   *iterator,
    const void                  *data
    );

const void *tseqiteratorSetData(
    tseqiterator                *iterator,
    const void                  *data
    );

vobject *titeratorGetObject(
    titerator                   *iterator
    );

titeratorClass *titeratorGetClass(
    titerator                   *iterator
    );

tseqiteratorClass *tseqiteratorGetClass(
    tseqiterator                *iterator
    );

const void *titeratorGetData(
    titerator                   *iterator
    );

const void *tseqiteratorGetData(
    tseqiterator                *iterator
    );

const void *titeratorGetAssociation(
    titerator                   *iterator
    );

const void *tseqiteratorGetAssociation(
    tseqiterator                *iterator
    );

int tseqiteratorGetCurrentIndex(
    tseqiterator       		*iterator
    );

int tseqiteratorGetNumberRemaining(
    tseqiterator		*iterator
    );

/*
 *+------------------------------------------------------------------------+
 * private macros
 *+------------------------------------------------------------------------+
 */

typedef vexValueNullException  titeratorNotAssociatedException;
typedef vexValueException      titeratorAlreadyAssociatedException;
extern vexClass	_titeratorNotAssociatedExceptionClass;
extern vexClass	_titeratorAlreadyAssociatedExceptionClass;

#define titeratorGetObject(_it)		\
  (&(_it)->baseobject)
#define titeratorGetClass(_it)		\
  ((titeratorClass*)vobjectGetClass(&(_it)->baseobject))
#define titeratorGetData(_it)		\
  ((_it)->data)
#define titeratorGetAssociation(_it)	\
  ((_it)->binding)

#define titeratorIsKindOf(_it, _c)			\
  vobjectIsKindOf(&(_it)->baseobject, _c)
#define titeratorCreateOfClass(_c)			\
  ((titerator*)vobjectCreateOfClass((vobjectClass*)(_c)))
#define titeratorCreate()				\
  titeratorCreateOfClass(titeratorGetDefaultClass())
#define titeratorClone(_it)				\
  ((titerator*)vobjectClone(&(_it)->baseobject))
#define titeratorInitOfClass(_it, _c)			\
  vobjectInitOfClass(&(_it)->baseobject, (vobjectClass*)(_c))
#define titeratorInit(_it)				\
  titeratorInitOfClass(_it, titeratorGetDefaultClass())
#define titeratorCopyInit(_it, _tit)			\
  vobjectCopyInit(&(_it)->baseobject, &(_tit)->baseobject)
#define titeratorLoad(_r)				\
  ((titerator*)vobjectLoad(_r))
#define titeratorLoadInit(_it, _r)			\
  vobjectLoadInit(&(_it)->baseobject, _r)

#define titeratorSend(_it, _m, _a)			\
  vclassSend(titeratorGetClass(_it), _m, _a)
#define titeratorDestroy(_it)				\
  titeratorSend(_it, vobjectDESTROY, (_it))
#define titeratorCopy(_it, _tit)			\
  titeratorSend(_it, vobjectCOPY, (_it, _tit))
#define titeratorStore(_it, _r)				\
  titeratorSend(_it, vobjectSTORE, (_it, _r))
#define titeratorSetTag(_it, _t)			\
  titeratorSend(_it, vobjectSET_TAG, (_it, _t))
#define titeratorAssociate(_it, _o)			\
  titeratorSend(_it, titeratorBIND,(_it, _o))
#define titeratorStartOver(_it)				\
  titeratorSend(_it, titeratorSTART_OVER, (_it))
#define titeratorMore(_it)				\
  titeratorSend(_it, titeratorMORE,(_it))
#define titeratorAdvance(_it)				\
  titeratorSend(_it, titeratorADVANCE, (_it))
#define titeratorSetData(_it, _d)			\
  titeratorSend(_it, titeratorSET_DATA,(_it, _d))




#define tseqiteratorGetObject(_it)		\
  (titeratorGetObject(&(_it)->baseobject))
#define tseqiteratorGetiterator(_it)		\
  (&(_it)->baseobject)
#define tseqiteratorGetClass(_it)		\
  ((tseqiteratorClass*)titeratorGetClass(&(_it)->baseobject))
#define tseqiteratorGetData(_it)		\
  titeratorGetData(tseqiteratorGetiterator(_it))
#define tseqiteratorGetAssociation(_it)	\
  titeratorGetAssociation(tseqiteratorGetiterator(_it))

#define tseqiteratorIsKindOf(_it, _c)			\
  titeratorIsKindOf(tseqiteratorGetiterator(_it, _c))
#define tseqiteratorCreateOfClass(_c)			\
  ((tseqiterator*)titeratorCreateOfClass((titeratorClass*)(_c)))
#define tseqiteratorCreate()				\
  tseqiteratorCreateOfClass(tseqiteratorGetDefaultClass())
#define tseqiteratorClone(_it)				\
  ((tseqiterator*)titeratorClone(&(_it)->baseobject))
#define tseqiteratorInitOfClass(_it, _c)		\
  titeratorInitOfClass(&(_it)->baseobject, (titeratorClass*)(_c))
#define tseqiteratorInit(_it)				\
  tseqiteratorInitOfClass(_it, tseqiteratorGetDefaultClass())
#define tseqiteratorCopyInit(_it, _tit)			\
  titeratorCopyInit(&(_it)->baseobject, &(_tit)->baseobject)
#define tseqiteratorLoad(_r)				\
  ((tseqiterator*)vobjectLoad(_r))
#define tseqiteratorLoadInit(_it, _r)			\
  titeratorLoadInit(&(_it)->baseobject, _r)

#define tseqiteratorSend(_it, _m, _a)			\
  vclassSend(tseqiteratorGetClass(_it), _m, _a)
#define tseqiteratorDestroy(_it)			\
  tseqiteratorSend(_it, vobjectDESTROY, (_it))
#define tseqiteratorCopy(_it, _tit)			\
  tseqiteratorSend(_it, vobjectCOPY, (_it, _tit))
#define tseqiteratorStore(_it, _r)			\
  tseqiteratorSend(_it, vobjectSTORE, (_it, _r))
#define tseqiteratorSetTag(_it, _t)			\
  tseqiteratorSend(_it, vobjectSET_TAG, (_it, _t))
#define tseqiteratorAssociate(_it, _o)			\
  tseqiteratorSend(_it, titeratorBIND,(_it, _o))
#define tseqiteratorStartOver(_it)			\
  tseqiteratorSend(_it, titeratorSTART_OVER, (_it))
#define tseqiteratorMore(_it)				\
  tseqiteratorSend(_it, titeratorMORE,(_it))
#define tseqiteratorAdvance(_it)			\
  tseqiteratorSend(_it, titeratorADVANCE, (_it))
#define tseqiteratorSetData(_it, _d)			\
  tseqiteratorSend(_it, titeratorSET_DATA,(_it, _d))
#define tseqiteratorGetNumberRemaining(_it)		\
  tseqiteratorSend(_it, tseqiteratorGET_REMAINING, (_it))
#define tseqiteratorGetCurrentIndex(_it)		\
  tseqiteratorSend(_it, tseqiteratorGET_AT, (_it))

/*
  +-------------------------------------------------------------------------+
   MISC formatting information for emacs in c-mode
  +-------------------------------------------------------------------------+
 */

/*
 * Local Variables:
 * c-indent-level:2
 * c-continued-statement-offset:2
 * c-brace-offset:0
 * c-brace-imaginary-offset:0
 * c-argdecl-indent:5
 * c-label-offset:0
 * c-tab-always-indent:nil
 * End:
 */

/* titeratorINCLUDED */
#endif

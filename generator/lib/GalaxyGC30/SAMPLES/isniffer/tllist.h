/* $Id: tllist.h,v 1.1 1994/08/19 00:02:28 simone Exp $ */
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
 *     This module implements a simple (singly) linked list module. used    *
 *     by the isnoop application.                                           *
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
 *                                                                          *
 ****************************************************************************
 */

#ifndef tllistINCLUDED
#define tllistINCLUDED 1

#ifndef vportINCLUDED
#include <vport.h>
#endif

#ifndef vstdioINCLUDED
#include vstdioHEADER
#endif

#ifndef vdebugINCLUDED
#include vdebugHEADER
#endif

#ifndef vclassINCLUDED
#include vclassHEADER
#endif

#ifndef vobjectINCLUDED
#include vobjectHEADER
#endif

#ifndef titeratorINCLUDED
#include "titer.h"
#endif


/*
 *+------------------------------------------------------------------------+
 * constants
 *+------------------------------------------------------------------------+
 */

enum {
  tllistDESTROY_ITEM = vTRUE,
  tllistDESTROY_ITEMS = vTRUE
};


/*
 *+------------------------------------------------------------------------+
 * types and classes
 *+------------------------------------------------------------------------+
 */

/* --- llistitem; these can be used as surrogates for existing classes
 * --- or as superclasses for new types */

typedef struct tllistitem tllistitem;
struct tllistitem {
  vobject	baseobject;
  tllistitem	*next;
  tllistitem	*prev;
  const void	*data;
};

typedef struct tllistitemClass tllistitemClass;

#define tllistitemCLASS(CLAS, LLITEM)	\
  vobjectCLASS(CLAS, LLITEM);		\
  vclassMETHOD(tllistitemDUMP, (LLITEM*, FILE*, int))

struct tllistitemClass {
  tllistitemCLASS(tllistitemClass, tllistitem);
};



/* --- helper types for the linked list class
 * --- */

typedef int (*tllistComparer)(tllistitem *item, const void *data);


typedef struct tllistIteratorClass tllistIteratorClass;
typedef struct tllistIterator {
  tseqiterator		baseobject;
  tllistitem		*nextitem;
  short			num;
  short			at;
}tllistIterator;

#define tllistIteratorCLASS(CLAS, ITER)	\
  tseqiteratorCLASS(CLAS, ITER);	\
  vclassMETHOD_RET(tllistIteratorNEXT, tllistitem*, (ITER*))

struct tllistIteratorClass {
  tllistIteratorCLASS(tllistIteratorClass, tllistIterator);
};



/* --- the (singly) linked list; used by our snooper program
 * --- */

typedef struct tllist {
  tllistitem	baseobject;
  tllistitem   *head;
  tllistitem   *tail;
}tllist;

typedef struct tllistClass tllistClass;

#define tllistCLASS(SUPER, LLIST)					\
  tllistitemCLASS(SUPER, LLIST);					\
  vclassMETHOD(tllistCLEAR_ITEMS, (LLIST *llist, int deep));		\
  vclassMETHOD(tllistSHALLOW_DESTROY, (LLIST *llist));			\
  vclassMETHOD_RET(tllistGET_HEAD, tllistitem*, (LLIST *llist));	\
  vclassMETHOD_RET(tllistGET_TAIL, tllistitem*, (LLIST *llist));	\
  vclassMETHOD(tllistREVERSE, (LLIST *llist));				\
  vclassMETHOD(tllistAPPEND_ITEMS, (LLIST *llist, tllistitem *item));	\
  vclassMETHOD(tllistDELETE_ITEM, 					\
	       (LLIST *llist, tllistitem *item, int deep));		\
  vclassMETHOD(tllistINSERT_ITEMS, 					\
	       (LLIST *llist, tllistitem *item, int position));		\
  vclassMETHOD_RET(tllistTALLY, int, (LLIST *llist));			\
  vclassMETHOD_RET(tllistLOCATE_ITEM, tllistitem*,			\
		   (LLIST *llist, tllistComparer isEqual, 		\
		    const void *data));					\
  vclassMETHOD_RET(tllistNEW_ITER, tllistIterator*,			\
		   (LLIST *llist));					\
  vclassMETHOD(tllistFREE_ITER, (LLIST*, tllistIterator*))

struct tllistClass {
  tllistCLASS(tllistClass, tllist);
};


/*
 *+------------------------------------------------------------------------+
 * tllistitem: exported routines
 *+------------------------------------------------------------------------+
 */

tllistitemClass *tllistitemGetDefaultClass(
    void
    );

tllistitem *tllistitemCreateOfClass(
    tllistitemClass            *clas
    );

tllistitem *tllistitemCreate(
    void
    );

tllistitem *tllistitemClone(
    tllistitem                 *item
    );

tllistitem *tllistitemLoad(
    vresource                    res
    );

void tllistitemInitOfClass(
    tllistitem                 *item,
    tllistitemClass            *clas
    );

void tllistitemInit(
    tllistitem                 *item
    );

void tllistitemLoadInit(
    tllistitem                 *item,
    vresource                   res
    );

void tllistitemDestroy(
    tllistitem                 *item
    );

void tllistitemDestroyLater(
    tllistitem                 *item
    );

void tllistitemCopy(
    tllistitem                 *item,
    tllistitem                 *target
    );

void tllistitemCopyInit(
    tllistitem                 *item,
    tllistitem                 *target
    );

const void *tllistitemSetData(
    tllistitem                  *item,
    const void			*data
    );

vobject *tllistitemGetObject(
    tllistitem                 *item
    );

tllistitemClass *tllistitemGetClass(
    tllistitem                 *item
    );

const void *tllistitemGetData(
    tllistitem                 *item
    );

int tllistitemIsKindOf(
    tllistitem                 	*item,
    tllistitemClass             *clas
    );

void tllistitemDump(
    tllistitem			*item,
    FILE			*stream,
    int				 deep
    );

/*
 *+------------------------------------------------------------------------+
 * tllist: exported routines
 *+------------------------------------------------------------------------+
 */

tllistClass *tllistGetDefaultClass(
    void
    );

tllist *tllistCreateOfClass(
    tllistClass                 *clas
    );

tllist *tllistCreate(
    void
    );

tllist *tllistClone( 
    tllist                      *llist
    );

void tllistInitOfClass(
    tllist                      *llist,
    tllistClass                 *clas
    );

void tllistInit(
    tllist                      *llist
    );

void tllistDestroy(
    tllist                      *llist
    );

void tllistShallowDestroy(
    tllist                      *llist
    );

void tllistDestroyLater(
    tllist                      *llist
    );

void tllistDeleteAll(
    tllist                      *llist,
    int				 deep
    );

void tllistCopy(
    tllist                      *llist,
    tllist                      *target
    );

void tllistCopyInit(
    tllist                      *llist,
    tllist                      *target
    );

tllist *tllistLoad(
    vresource                    res
    );

void tllistLoadInit(
    tllist                      *llist,
    vresource                    res
    );

void tllistStore(
    tllist                      *llist,
    vresource                    res
    );

tllistitem *tllistGetHead(
    tllist                      *llist
    );

tllistitem *tllistGetTail(
    tllist                      *llist
    );

void tllistReverse(
    tllist                      *llist
    );

void tllistAppendItem(
    tllist                      *llist,
    tllistitem                  *item
    );

void tllistDeleteItem(
    tllist                      *llist,
    tllistitem                  *item,
    int                   	 deep
    );

void tllistDeleteItemBySearch(
    tllist                      *llist,
    tllistComparer               isEqual,
    const void        		*data,
    int                   	 deep
    );

void tllistDeleteThisItemBySearch(
    tllist                      *llist,
    tllistitem			*item,
    int                   	 deep
    );

void tllistInsertItem(
    tllist                      *llist,
    tllistitem                  *item,
    int                   	 position
    );

void tllistInsertItems(
    tllist                      *llist,
    tllistitem                  *item,
    int                   	 position
    );

void tllistLocateItem(
    tllist                      *llist,
    tllistitem			*item
    );

void tllistLocateItemBySearch(
    tllist                      *llist,
    tllistComparer               isEqual,
    const void                	*data
    );

void tllistSetTag(
    tllist                      *llist,
    const vname                 *tag
    );

const void *tllistSetData(
    tllist                      *llist,
    const void                 	*data
    );

int tllistIsKindOf(
    tllist                 	*llist,
    tllistClass                 *clas
    );

int tllistIsEmpty(
    tllist                 	*llist
    );

int tllistGetCount(
    tllist                      *llist
    );

int tllistContainsItem(
    tllist                      *llist,
    tllistitem                  *item
    );

tllistitem *tllistGetItem(
    tllist                      *llist
    );

vobject *tllistGetObject(
    tllist                      *llist
    );

tllistClass *tllistGetClass(
    tllist                      *llist
    );

const void *tllistGetData(
    tllist                      *llist
    );

tllistIterator *tllistCreateIterator(
    tllist                      *llist
    );

void tllistDestroyIterator(
    tllist                      *llist,
    tllistIterator              *iter
    );

void tllistDump(
    tllist                      *llist,
    FILE			*stream,
    int				 deep
    );

/*
 *+------------------------------------------------------------------------+
 * tllistIterator: exported routines
 *+------------------------------------------------------------------------+
 */

int tllistIteratorMore(
    tllistIterator	*iter
    );

void tllistIteratorStartOver(
    tllistIterator	*iter
    );

tllistitem *tllistIteratorNextItem(
    tllistIterator	*iter
    );

int tllistIteratorGetNumberRemaining(
    tllistIterator	*iter
    );

int tllistIteratorGetCurrentIndex(
    tllistIterator   	*iter
    );

tllist *tllistIteratorGetList(
    tllistIterator	*iter
    );

/*
 *+------------------------------------------------------------------------+
 * tllistitem macros
 *+------------------------------------------------------------------------+
 */

#define tllistitemGetObject(_i)					\
  (&(_i)->baseobject)
#define tllistitemGetClass(_i)					\
  ((tllistitemClass*)vobjectGetClass(&(_i)->baseobject))
#define tllistitemGetData(_i)					\
  ((_i)->data)
#define tllistitemIsKindOf(_i, _c)				\
  vobjectIsKindOf(&(_i)->baseobject, (_c))
#define tllistitemSetData(_i, _d)				\
  (_i)->data = (_d)


#define tllistitemCreateOfClass(_c)				\
  ((tllistitem*)vobjectCreateOfClass((vobjectClass*)(_c)))
#define tllistitemCreate()					\
  tllistitemCreateOfClass(tllistitemGetDefaultClass())
#define tllistitemClone(_i)					\
  ((tllistitem*)vobjectClone(&(_i)->baseobject))
#define tllistitemLoad(_r)					\
  ((tllistitem*)vobjectLoad(_r))
#define tllistitemInitOfClass(_i, _c)				\
  vobjectInitOfClass(&(_i)->baseobject, (vobjectClass*)(_c))
#define tllistitemInit(_i)					\
  tllistitemInitOfClass(_i, tllistitemGetDefaultClass())
#define tllistitemDestroyLater(_i)				\
  vobjectDestroyLater(&(_i)->baseobject)
#define tllistitemCopyInit(_i, _ti)				\
  vobjectCopyInit(&(_i)->baseobject, &(_ti)->baseobject)
#define tllistitemLoadInit(_i, _r)				\
  vobjectLoadInit(tllistitemGetObject(_i), _r)



#define tllistitemSend(_i, _m, _a)				\
  vclassSend(tllistitemGetClass(_i), _m, _a)
#define tllistitemDestroy(_i)					\
  tllistitemSend(_i, vobjectDESTROY, (_i))
#define tllistitemCopy(_i, _ti)					\
  tllistSend(_i, vobjectCOPY, (_i, _ti))
#define tllistitemDump(_i,_fp,_b)				\
  tllistSend(_i, tllistitemDUMP, (_i, _fp, _b))


/*
 *+------------------------------------------------------------------------+
 * tllist macros
 *+------------------------------------------------------------------------+
 */

int _tllistitemIsEqual(tllistitem*, tllistitem*);
int _tllistitemIsEqualByData(tllistitem*, tllistitem*);


#define tllistGetObject(_ll)					\
  tllistitemGetObject(&(_ll)->baseobject)
#define tllistGetClass(_ll)					\
  ((tllistClass*)tllistitemGetClass(&(_ll)->baseobject))


#define tllistIsKindOf(_ll, _c)					\
  tllistitemIsKindOf(&(_ll)->baseobject, (_c))
#define tllistCreateOfClass(_c)					\
  ((tllist*)tllistitemCreateOfClass((tllistitemClass*)(_c)))
#define tllistCreate()						\
  tllistCreateOfClass(tllistGetDefaultClass())
#define tllistClone(_ll)					\
  ((tllist*)tllistitemClone(&(_ll)->baseobject))
#define tllistInitOfClass(_ll, _c)				\
  tllistitemInitOfClass(&(_ll)->baseobject, (tllistitemClass*)(_c))
#define tllistInit(_ll)						\
  tllistInitOfClass(_ll, tllistGetDefaultClass())
#define tllistCopyInit(_ll, _tll)				\
  tllistitemCopyInit(&(_ll)->baseobject, &(_tll)->baseobject)
#define tllistLoad(_r)						\
  ((tllist*)vobjectLoad(_r))
#define tllistLoadInit(_ll, _r)					\
  vobjectLoadInit(tllistGetObject(_ll), _r)


#define tllistSend(_ll, _m, _a)					\
  vclassSend(tllistGetClass(_ll), _m, _a)
#define tllistDestroy(_ll)					\
  tllistSend(_ll, vobjectDESTROY, (_ll))
#define tllistShallowDestroy(_ll)				\
  tllistSend(_ll, tllistSHALLOW_DESTROY, (_ll))
#define tllistCopy(_ll, _tll)					\
  tllistSend(_ll, vobjectCOPY, (_ll, _tll))
#define tllistStore(_ll, _r)					\
  tllistSend(_ll, vobjectSTORE, (_ll, _r))
#define tllistSetTag(_ll, _t)					\
  tllistSend(_ll, vobjectSET_TAG, (_ll, _t))
#define tllistDeleteAll(_ll, _b)				\
  tllistSend(_ll, tllistCLEAR_ITEMS,   (_ll, _b))
#define tllistGetCount(_ll)					\
  tllistSend(_ll, tllistTALLY, (_ll))
#define tllistReverse(_ll)					\
  tllistSend(_ll, tllistREVERSE, (_ll))
#define tllistAppendItem(_ll, _i)				\
  tllistSend(_ll, tllistAPPEND_ITEMS,  (_ll, (tllistitem*)(_i)))
#define tllistAppendItems(_ll, _i)				\
  tllistSend(_ll, tllistAPPEND_ITEMS,  (_ll, (tllistitem*)(_i)))
#define tllistDeleteItem(_ll, _i, _d)  				\
  tllistSend(_ll, tllistDELETE_ITEM,  (_ll, (tllistitem*)(_i), _d))
#define tllistDeleteThisItemBySearch(_ll, _i, _d)		\
  tllistDeleteItemBySearch(_ll, _tllistitemIsEqualByData, (void*)(_i), _d)
#define tllistInsertItem(_ll, _i, _n)				\
  tllistSend(_ll, tllistINSERT_ITEMS, (_ll, (tllistitem*)(_i), _n))
#define tllistInsertItems(_ll, _i, _n)				\
  tllistSend(_ll, tllistINSERT_ITEMS, (_ll, (tllistitem*)(_i), _n))
#define tllistLocateItemBySearch(_ll, _c, _d)			\
  tllistSend(_ll, tllistLOCATE_ITEM,  (_ll, _c, _d))
#define tllistLocateItem(_ll, _i)				\
  tllistSend(_ll, tllistLOCATE_ITEM,  				\
	     (_ll, _tllistitemIsEqualByData, (void*)(_i)))
#define tllistGetHead(_ll)					\
  tllistSend(_ll, tllistGET_HEAD, (_ll))
#define tllistGetTail(_ll)					\
  tllistSend(_ll, tllistGET_TAIL, (_ll))
#define tllistCreateIterator(_ll)				\
  tllistSend(_ll, tllistNEW_ITER, (_ll))
#define tllistDestroyIterator(_ll, _it)				\
  tllistSend(_ll, tllistFREE_ITER, (_ll, _it))
#define tllistSetData(_ll, _v)					\
  tllistitemSetData(&(_ll)->baseobject, (_v))
#define tllistGetData(_ll, _v)					\
  tllistitemGetData(&(_ll)->baseobject)
#define tllistDump(_ll, _fp, _b)				\
  tllistSend(_ll, tllistitemDUMP, (_ll, _fp, _b))
#define tllistContainsItem(_ll, _i)				\
  (tllistLocateItemBySearch(_ll, _tllistitemIsEqual, (void*)(_i))!=NULL)
#define tllistIsEmpty(_ll)					\
  (tllistGetHead(_ll)==NULL)



/*
 *+------------------------------------------------------------------------+
 * tllistIterator macros
 *+------------------------------------------------------------------------+
 */

#define tllistIteratorGetClass(_it)				\
  ((tllistIteratorClass*)tseqiteratorGetClass(&(_it)->baseobject))
#define tllistIteratorSend(_it, _m, _a)				\
  vclassSend(tllistIteratorGetClass(_it), _m, _a)
#define tllistIteratorGetList(_it)				\
  ((tllist*)tseqiteratorGetAssociation(&(_it)->baseobject))
#define tllistIteratorMore(_it)					\
  tllistIteratorSend((_it), titeratorMORE, (_it))
#define tllistIteratorStartOver(_it)				\
  tllistIteratorSend((_it), titeratorSTART_OVER, (_it))
#define tllistIteratorGetNumberRemaining(_it)			\
  tllistIteratorSend((_it), tseqiteratorGET_REMAINING, (_it))
#define tllistIteratorGetCurrentIndex(_it)			\
  tllistIteratorSend((_it), tseqiteratorGET_AT, (_it))
#define tllistIteratorNextItem(_it)				\
  tllistIteratorSend((_it), tllistIteratorNEXT, (_it))
#define tllistIteratorAdvance(_it)				\
  tllistIteratorSend((_it), titeratorADVANCE, (_it))


/* tllistINCLUDED */
#endif

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

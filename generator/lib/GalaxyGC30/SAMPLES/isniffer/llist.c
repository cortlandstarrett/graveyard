/* $Id: llist.c,v 1.1 1994/08/19 00:06:12 simone Exp $ */
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

#include <vport.h>
#include vstdioHEADER
#include vstdlibHEADER
#include vdebugHEADER
#include vexHEADER
#include vcharHEADER
#include vstrHEADER
#include vclientHEADER
#include vclassHEADER
#include vobjectHEADER

#include "titer.h"
#include "tllist.h"


/*
 *+------------------------------------------------------------------------+
 * private types and macros
 *+------------------------------------------------------------------------+
 */

/* our module's debug tag */
#if (vdebugDEBUG)
static const char *const _moduleTag = "tllist-module";
#define vdebugTAG _moduleTag
#endif


/* one per client */
typedef struct _moduleGlobals {
  tllistitemClass	*defaultItemClass;
  tllistClass		*defaultClass;
  tllistIteratorClass	*defaultIteratorClass;
}_moduleGlobals;


#define AUTOINIT()	\
  {if (!_tllistMaster || !*_tllistMaster) _tllistStartup(); }

#define globals()			\
  ((_moduleGlobals*)*_tllistMaster)
#define _tllistitemSendSuper(_m,_a)	\
  vclassSendSuper(globals()->defaultItemClass, _m, _a)
#define _tllistSendSuper(_m,_a)		\
  vclassSendSuper(globals()->defaultClass, _m, _a)
#define _iteratorSendSuper(_m, _a)	\
  vclassSendSuper(globals()->defaultIteratorClass, _m, _a)


/*
 *+------------------------------------------------------------------------+
 * private variables and routine declarations
 *+------------------------------------------------------------------------+
 */

static void  	      **_tllistMaster = NULL;
static void		_tllistStartup(void);
static void		_tllistitemInitDefaultClass(void);
static void		_tllistInitDefaultClass(void);
static void		_tllistInitDefaultIteratorClass(void);

static tllistitem	*getTail(tllistitem*);
static void		_tllistitemInit(tllistitem*);
static void		_tllistitemLoadInit(tllistitem*, vresource);
static void		_tllistitemCopyInit(tllistitem*, tllistitem*);
static void		_tllistitemCopy(tllistitem*, tllistitem*);
static void		_tllistitemDump(tllistitem*, FILE*, int);
static void		_tllistInit(tllist*);
static void		_tllistLoadInit(tllist*, vresource);
static void		_tllistDestroy(tllist*);
static void		_tllistDeleteAll(tllist*, int);
static void		_tllistShallowDestroy(tllist*);
static tllistitem      *_tllistGetHead(tllist*);
static tllistitem      *_tllistGetTail(tllist*);
static void		_tllistReverse(tllist*);
static void		_tllistAppendItem(tllist*, tllistitem*);
static void		_tllistDeleteItem(tllist*, tllistitem*, int);
static void		_tllistInsertItem(tllist*, tllistitem*, int);
static int		_tllistCountItems(tllist*);
static tllistitem      *_tllistLocateItem(tllist*, tllistComparer, 
					  const void*);
static void		_tllistCopy(tllist*, tllist*);
static void		_tllistCopyInit(tllist*, tllist*);
static void		_tllistDump(tllist*, FILE*, int);
static tllistIterator  *_tllistNewIterator(tllist*);
static void		_tllistFreeIterator(tllist*, tllistIterator*);

static void		_iteratorInit(tllistIterator*);
static void		_iteratorLoadInit(tllistIterator*, vresource);
static void		_iteratorCopyInit(tllistIterator*, tllistIterator*);
static void		_iteratorCopy(tllistIterator*, tllistIterator*);
static void		_iteratorStartOver(tllistIterator*);
static void		_iteratorAdvance(tllistIterator*);
static int		_iteratorAt(tllistIterator*);
static int		_iteratorRemaining(tllistIterator*);
static tllistitem      *_iteratorNext(tllistIterator*);

/*
 *+------------------------------------------------------------------------+
 * pubics
 *+------------------------------------------------------------------------+
 */


tllistitemClass *
tllistitemGetDefaultClass(void)
{
  AUTOINIT();
  return globals()->defaultItemClass;
}




tllistClass *
tllistGetDefaultClass(void)
{
  AUTOINIT();
  return globals()->defaultClass;
}




void
tllistDestroyLater(tllist *llist)
{
  register tllistitem	*item;

  vdebugIF(!llist, vexGenerate(vexGetArgNullClass(), vexMESSAGE,
           "destroy later: NULL argument!", vexERRNO, 0, vexNULL));

  for (item = llist->head; item; item = item->next)
    tllistitemDestroyLater(item);

  vobjectDestroyLater(tllistGetObject(llist));
  return;
}




void
tllistDeleteItemBySearch(tllist *llist, tllistComparer isequal, 
			 const void *data, int deep)
{
  register tllistitem	*item;

  item = tllistLocateItemBySearch(llist, isequal, data);
  if (item)
    tllistDeleteItem(llist, item, deep);

  return;
}





/*
 *+------------------------------------------------------------------------+
 * private (parts?!)
 *+------------------------------------------------------------------------+
 */


 static void
_tllistStartup(void)
{
  if (!_tllistMaster)
    {
      _tllistMaster = vclientRegisterModule();
    }

  if (!*_tllistMaster)
    {
       vclientAllocateModule(_tllistMaster, sizeof(_moduleGlobals));
      _tllistitemInitDefaultClass();
      _tllistInitDefaultClass();
      _tllistInitDefaultIteratorClass();
    }
}


 static void
_tllistitemInitDefaultClass(void)
{
  register tllistitemClass *clas;

  clas = vclassSpawn(vobjectGetDefaultClass(), sizeof(tllistitemClass));
  vclassSetNameScribed(clas, vcharScribeLiteral("tllistitem"));
  vclassSetObjectSize(clas, sizeof(tllistitem));

  vclassSet(clas, vobjectINIT, 	    _tllistitemInit);
  vclassSet(clas, vobjectLOAD_INIT, _tllistitemLoadInit);
  vclassSet(clas, vobjectCOPY_INIT, _tllistitemCopyInit);
  vclassSet(clas, vobjectCOPY, 	    _tllistitemCopy);
  vclassSet(clas, tllistitemDUMP,   _tllistitemDump);

  globals()->defaultItemClass = clas;
  return;
}


 static void
_tllistInitDefaultClass(void)
{
  register tllistitemClass	*super;
  register tllistClass 		*clas;

  super = globals()->defaultItemClass;
  clas  =  vclassSpawn(super, sizeof(tllistClass));
  vclassSetNameScribed(clas, vcharScribeLiteral("tllist"));
  vclassSetObjectSize(clas, sizeof(tllist));

  vclassSet(clas, vobjectINIT,		_tllistInit);
  vclassSet(clas, vobjectLOAD_INIT,	_tllistLoadInit);
  vclassSet(clas, vobjectDESTROY,	_tllistDestroy);
  vclassSet(clas, vobjectCOPY,		_tllistCopy);
  vclassSet(clas, vobjectCOPY_INIT,	_tllistCopyInit);

  vclassSet(clas, tllistitemDUMP,	_tllistDump);
  vclassSet(clas, tllistCLEAR_ITEMS,	_tllistDeleteAll);
  vclassSet(clas, tllistSHALLOW_DESTROY,_tllistShallowDestroy);
  vclassSet(clas, tllistTALLY,		_tllistCountItems);
  vclassSet(clas, tllistREVERSE,	_tllistReverse);
  vclassSet(clas, tllistINSERT_ITEMS,	_tllistInsertItem);
  vclassSet(clas, tllistAPPEND_ITEMS,	_tllistAppendItem);
  vclassSet(clas, tllistDELETE_ITEM,	_tllistDeleteItem);
  vclassSet(clas, tllistLOCATE_ITEM,	_tllistLocateItem);
  vclassSet(clas, tllistGET_HEAD,	_tllistGetHead);
  vclassSet(clas, tllistGET_TAIL,	_tllistGetTail);
  vclassSet(clas, tllistNEW_ITER,       _tllistNewIterator);
  vclassSet(clas, tllistFREE_ITER,      _tllistFreeIterator);

  globals()->defaultClass = clas;
}




 static void
_tllistInitDefaultIteratorClass(void)
{
  register tllistIteratorClass *clas;

  clas = vclassSpawn(tseqiteratorGetDefaultClass(), 
		     sizeof(tllistIteratorClass));
  vclassSetNameScribed(clas, vcharScribeLiteral("tllistIterator"));
  vclassSetObjectSize(clas, sizeof(tllistIterator));

  vclassSet(clas, vobjectINIT,       _iteratorInit);
  vclassSet(clas, vobjectLOAD_INIT,  _iteratorLoadInit);
  vclassSet(clas, vobjectCOPY_INIT,  _iteratorCopyInit);
  vclassSet(clas, vobjectCOPY,       _iteratorCopy);

  vclassSet(clas, titeratorSTART_OVER,      _iteratorStartOver);
  vclassSet(clas, titeratorADVANCE,         _iteratorAdvance);
  vclassSet(clas, tseqiteratorGET_REMAINING,_iteratorRemaining);
  vclassSet(clas, tseqiteratorGET_AT,       _iteratorAt);
  vclassSet(clas, tllistIteratorNEXT,       _iteratorNext);

  globals()->defaultIteratorClass = clas;
  return;
}



/*
 *+------------------------------------------------------------------------+
 * tllist items
 *+------------------------------------------------------------------------+
 */


#if (vdebugDEBUG)
#undef vdebugTAG
static const char *const _itemTag = "tllistitem";
#define vdebugTAG _itemTag
#endif



static tllistitem*
getTail(register tllistitem *item)
{
  vdebugIF((!item), vexGenerate(vexGetArgNullClass(), vexMESSAGE,
           "get tail: NULL argument!", vexERRNO, 0, vexNULL));

  while (item->next) 
    item = item->next;

  return item;
}





 static void
_tllistitemInit(tllistitem *item)
{
  _tllistitemSendSuper(vobjectINIT, (item));

  item->next = NULL;
  item->prev = NULL;
  item->data = NULL;
}




 static void
_tllistitemLoadInit(tllistitem *item, vresource res)
{
  _tllistitemSendSuper(vobjectLOAD_INIT, (item, res));

  item->next = NULL;
  item->prev = NULL;
  item->data = NULL;
}





 static void
_tllistitemCopyInit(tllistitem *item, tllistitem *target)
{
  _tllistitemSendSuper(vobjectCOPY_INIT, (item, target));

  target->next = NULL;
  target->prev = NULL;
  target->data = item->data;
}




 static void
_tllistitemCopy(tllistitem *item, tllistitem *target)
{
  _tllistitemSendSuper(vobjectCOPY, (item, target));

  target->next = NULL;
  target->prev = NULL;
  target->data = item->data;
}




 static void
_tllistitemDump(register tllistitem *item, register FILE *fp, int deep)
{
  if (!fp)
    fp = vdebugGetInfoStream();

  return;
}




/*
 *+------------------------------------------------------------------------+
 * tllists
 *+------------------------------------------------------------------------+
 */


#if (vdebugDEBUG)
#undef vdebugTAG
static const char *const _llistTag = "tllist";
#define vdebugTAG _llistTag
#endif



 static void
_tllistInit(tllist *llist)
{
  _tllistSendSuper(vobjectINIT, (llist));

  llist->head = NULL;
  llist->tail = NULL;
}





 static void
_tllistLoadInit(tllist *llist, vresource res)
{
  _tllistSendSuper(vobjectLOAD_INIT, (llist, res));

  llist->head = NULL;
  llist->tail = NULL;
}




 static void
_tllistDestroy(tllist *llist)
{
  register tllistitem	*item, *next;

  for (item = llist->head; item;)
    {
      next = item->next;
      tllistitemDestroy(item);
      item = next;
    }

  _tllistSendSuper(vobjectDESTROY, (llist));
}





 static void
_tllistDeleteAll(tllist *llist, register int deep)
{
  register tllistitem	*item, *next;

  for (item = llist->head; item;)
    {
      next = item->next;
      if (deep) 
	tllistitemDestroy(item);
      item = next;
    }

  llist->head= llist->tail= NULL;
}





 static void
_tllistShallowDestroy(tllist *llist)
{
  tllistDeleteAll(llist, FALSE);
  tllistDestroy(llist);
}





 static tllistitem*
_tllistGetHead(tllist *llist)
{
  return llist->head;
}




 static tllistitem*
_tllistGetTail(tllist *llist)
{
  return llist->tail;
}





 static void
_tllistReverse(register tllist *llist)
{
  register tllistitem *next, *prev, *item;

  if (llist->head != llist->tail)
    {
      llist->tail = llist->head;
      prev = next = NULL;
      item = llist->head;
      while (item) 
	{
	  next = item->next;
	  item->next = prev;
	  prev = item;
	  item = next;
	}
      llist->head = prev;
    }
}





 static void
_tllistAppendItem(register tllist *llist, tllistitem *user)
{
  vdebugIF(!user, vexGenerate(vexGetArgNullClass(), vexMESSAGE,
           "append item: NULL item!", vexERRNO, 0, vexNULL));

  if (!llist->head)
    {
      llist->head = user;
      llist->tail = getTail(user);
    }
  else
    {
      llist->tail->next = user;
      llist->tail = getTail(user);
    }
}




 static void
_tllistDeleteItem(tllist *llist, tllistitem *user, int deep)
{
  register tllistitem	*prev, *targ;
  int			 found;

  vdebugIF(!user, vexGenerate(vexGetArgNullClass(), vexMESSAGE,
           "delete item: NULL item!", vexERRNO, 0, vexNULL));

  targ  = llist->head;
  prev  = NULL;
  found = FALSE;

  while (targ) 
    {
      if (targ==user) 
	{
	  if (prev) 
	    prev->next  = targ->next;
	  else 
	    llist->head = targ->next;
	  found = TRUE;
	  break;
	}
      prev = targ;
      targ = targ->next;
    }

  if (found)
    {
      if (deep) 
	tllistitemDestroy(targ);
      else
	targ->next= NULL;
      llist->tail = llist->head ? getTail(llist->head) : NULL;
    }
}





 static void
_tllistInsertItem(tllist *llist, tllistitem *user, int pos)
{
  register tllistitem	*item, *prev, *hold;
  int index;

  vdebugIF(!user, vexGenerate(vexGetArgNullClass(), vexMESSAGE,
           "insert item: NULL item!", vexERRNO, 0, vexNULL));
  vdebugIF((pos<0), vexGenerate(vexGetArgRangeClass(), vexMESSAGE,
           "insert item: index out of list's range", vexERRNO, 0, vexNULL));


  if (!llist->head)
    {
      llist->head = user;
      llist->tail = getTail(user);
    }
  else
    {
      item = llist->head;
      prev = NULL;
      index= pos;

      while (index-- && item/*item->next*/)
	{
	  prev = item;
	  item = item->next;
	}

      if (prev)
	{
	  hold = prev->next;
	  prev->next = user;
	}
      else
	{
	  hold = llist->head;
	}

      item = getTail(user);
      item->next = hold;

      if (!pos) 
	llist->head = user;

      llist->tail = getTail(llist->head);
    }
}





 static int
_tllistCountItems(tllist *llist)
{
  register int		n;
  register tllistitem  *item;

  for (n = 0, item = llist->head; item; item = item->next, n++)
    ;
  return n;
}





 int
_tllistitemIsEqualByData(register tllistitem *item1, 
			 register tllistitem *item2)
{
  return item1->data==item2->data;
}

 int
_tllistitemIsEqual(register tllistitem *item1, 
		   register tllistitem *item2)
{
  return item1==item2;
}




 static tllistitem *
_tllistLocateItem(tllist *llist, tllistComparer isequal, const void *data)
{
  register tllistitem	*item;
  tllistitem		*targ;

  vdebugIF((!isequal), vexGenerate(vexGetArgNullClass(), vexMESSAGE,
          "locate item: NULL comparer proc!", vexERRNO, 0, vexNULL));

  targ = NULL;

  for (item = llist->head; item; item = item->next)
    if (isequal(item, data))
      {
	targ = item;
	break;
      }

  return targ;
}





 static void
_tllistCopy(tllist *llist, register tllist *target)
{
  register tllistitem *item, *copy;

  _tllistSendSuper(vobjectCOPY, (llist, target));

  tllistDeleteAll(target, TRUE);

  for (item = llist->head; item; item = item->next)
    {
      copy = tllistitemClone(item);
      tllistAppendItem(target, copy);
    }
}





 static void
_tllistCopyInit(tllist *llist, tllist *target)
{
  register tllistitem *item, *copy;

  _tllistSendSuper(vobjectCOPY_INIT, (llist, target));

  target->head = NULL;
  target->tail = NULL;

  for (item = llist->head; item; item = item->next)
    {
      copy = tllistitemClone(item);
      tllistAppendItem(target, copy);
    }
}





 static void
_tllistDump(register tllist *llist, register FILE *fp, int deep)
{
#if (vdebugDEBUG && 0)
  if (!fp)
    fp = vdebugGetInfoStream();

  fprintf(fp, "tllist(%p)\n", llist);

  if (!llist->head)
    {
      fprintf(fp, "\t0 items\n");
    }
  else
    {
      register tllistitem *item;
      register int i=0;

      item = llist->head;
      do {
	; /* -> fillin here <- */
	i++;
	item = item->next;
      } while (item);
    }
#endif
}





 static tllistIterator *
_tllistNewIterator(tllist *llist)
{
  register tllistIterator *iter;

  iter = (tllistIterator*)tseqiteratorCreateOfClass
    (globals()->defaultIteratorClass);
  tllistIteratorSend(iter, titeratorBIND, (iter,llist));

  return iter;
}




 static void
_tllistFreeIterator(tllist *llist, tllistIterator *iter)
{
  vdebugIF((!iter), vexGenerate(vexGetArgNullClass(), vexMESSAGE,
           "destroy iterator: NULL iter argument!", vexERRNO, 0, vexNULL));

  if (tllistIteratorGetList(iter)!=llist)
    vexGenerate(vexGetValueClass(), vexMESSAGE, "destroy iterator: iterator "
                "not associated with the list!", vexERRNO, 0, vexNULL);

  tllistIteratorSend(iter, vobjectDESTROY, (iter));
  return;
}



/*
 *+------------------------------------------------------------------------+
 * tllist iterators, private
 *+------------------------------------------------------------------------+
 */

#if (vdebugDEBUG)
#undef vdebugTAG
static const char *const _iterTag = "tllistIterator";
#define vdebugTAG _iterTag
#endif



 static void
_iteratorInit(register tllistIterator *iter)
{
  _iteratorSendSuper(vobjectINIT, (iter));
  iter->nextitem = NULL;
  iter->num = 0;
  iter->at = -1;
}




 static void
_iteratorLoadInit(register tllistIterator *iter, vresource res)
{
  _iteratorSendSuper(vobjectLOAD_INIT, (iter, res));
  iter->nextitem = NULL;
  iter->num = 0;
  iter->at = -1;
}




 static void
_iteratorCopyInit(register tllistIterator *iter, tllistIterator *copy)
{
  _iteratorSendSuper(vobjectCOPY_INIT, (iter, copy));
  copy->nextitem = NULL;
  copy->num = 0;
  copy->at = -1;
}




 static void
_iteratorCopy(register tllistIterator *iter, tllistIterator *copy)
{
  _iteratorSendSuper(vobjectCOPY, (iter, copy));
  copy->nextitem = NULL;
  copy->num = 0;
  copy->at = -1;
}




 static void
_iteratorStartOver(register tllistIterator *iter)
{
  tllist	*list;

  list = tllistIteratorGetList(iter);
  if (!list)
    vexGenerate(vexGetValueNullClass(), vexMESSAGE, "startover: no list",
		vexERRNO, 0, vexNULL);

  iter->num = tllistGetCount(list);
  iter->nextitem = iter->num>0 ? tllistGetHead(list) : NULL;
  iter->at = iter->num>0 ? 0 : -1;
}




 static int
_iteratorRemaining(register tllistIterator *iter)
{
  return iter->num;
}




 static int
_iteratorAt(register tllistIterator *iter)
{
  return iter->at;
}




 static void
_iteratorAdvance(register tllistIterator *iter)
{
  if (!iter->num || !iter->nextitem)
    {
      vdebugWarn("advance: no more items to iterate!\n");
      return;
    }

  iter->at++;
  iter->num--;
  iter->nextitem = iter->nextitem->next;
}




 static tllistitem*
_iteratorNext(register tllistIterator *iter)
{
  tllistitem	*item;

  vdebugIF(!iter->nextitem, vdebugWarn("next: iteration is finished\n"));
  item = iter->nextitem;
  tllistIteratorAdvance(iter);
  return item;
}




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

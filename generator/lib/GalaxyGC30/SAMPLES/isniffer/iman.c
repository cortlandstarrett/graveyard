/* $Id: iman.c,v 1.4 1996/08/21 15:52:23 david Exp $ */
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
 *     Image manager class; allows multiple references to a single vimage.  *
 *     Useful for applications like Looking Glass Professional(tm).         *
 *     Makes heavy use of the following galaxy managers: Class Manager,     *
 *        Command Manager (vcommand), and Undo Manager (vundo)              *
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

/* for v*HEADER */
#include <vport.h>

/* ANSI headers */
#include vstdioHEADER
#include vstdlibHEADER
#include vstdargHEADER

/* Galaxy headers */
#include vdebugHEADER
#include vexHEADER
#include vmemHEADER
#include vpoolHEADER
#include vcharHEADER
#include vstrHEADER
#include vscribeHEADER
#include vnameHEADER
#include vdictHEADER
#include vclientHEADER
#include vresourceHEADER
#include veventHEADER
#include vclassHEADER
#include vstdHEADER
#include vinstanceHEADER
#include vobjectHEADER
#include vimageHEADER
#include vundoHEADER
#include vapplicationHEADER

/* Our headers */
#include "titer.h"
#include "tllist.h"
#include "iman.h"



/* Define our debug tag for vdebug manager */
#if vdebugDEBUG
static const char *const _imanTag = "image-manager";
#define vdebugTAG _imanTag
#endif



/*
 *+------------------------------------------------------------------------+
 *         Image Manager's Names (Resources, Action Titles, etc.)
 *+------------------------------------------------------------------------+
 */

enum {
  NAME_STORE_CLASS,
  NAME_IMAGES,
  NAME_IMAGES_MASKS,
  NAME_GENERIC_IMAGE,
  NAME_IMAGES_COMPONENT,
  NAME_ITEM_TAG,
  NAME_PASTE_IMAGES_ACT,
  NAME_ADD_IMAGE_ACT,
  NAME_REMOVE_IMAGE_ACT,
  NAME_COUNT
};

#define name_PasteImages 	names[NAME_PASTE_IMAGES_ACT]
#define name_AddImage		names[NAME_ADD_IMAGE_ACT]
#define name_RemoveImage	names[NAME_REMOVE_IMAGE_ACT]
#define name_Images		names[NAME_IMAGES]
#define name_GenericImage	names[NAME_GENERIC_IMAGE]
#define name_ImageMasks		names[NAME_IMAGES_MASKS]
#define name_ImagesComponent	names[NAME_IMAGES_COMPONENT]
#define name_ItemTag		names[NAME_ITEM_TAG]
#define name_StoreClass		names[NAME_STORE_CLASS]
#define literal_StoreClass	literals[NAME_STORE_CLASS]

static const vname *names[NAME_COUNT];
static const char  *literals[NAME_COUNT]= {
  "image-store",
  "im-images",
  "im-images-masks",
  "im-generic-image",
  "images",
  "im-tag",
  "Paste",	/* ick...last-resort, application should provide proc */
  "Add",	/* "" */
  "Remove"	/* "" */
};

/*
 *+-----------------------------------------------------------------------+
 *               Image Manager's Private Classes and Types:
 *+-----------------------------------------------------------------------+
 */

/* +----------------------------- STORE-ITEMS ----------------------------+ */

typedef struct istoreitem {
  const vname		*tag;		/* identifier */
  vimage		*image;		/* loaded display image */
  vresource		 res;		/* associated vimage res */
  unsigned short	 users;		/* number of retrieves for image */
  unsigned		 dirty:1;	/* TRUE if this item's been changed */
  unsigned		 transient:1;	/* TRUE if created for "undo" action */
}istoreitem;


typedef struct istoreitemList {
  istoreitem	**b, **e, **x;		/* Begin, End, maX */
}istoreitemList;


/** attribute access **/
#define istoreitemGetImage(i)		((i)->image)
#define istoreitemGetUsers(i)		((i)->users)
#define istoreitemIsTransient(i)	((i)->transient)
#define istoreitemGetRes(i)		((i)->res)
#define istoreitemGetTag(i)		((i)->tag)
#define istoreitemSetTag(i,t)		(i)->tag = (t)
#define istoreitemNeedsLoading(i) 	(!(i)->image && (i)->res!=vresourceNULL)

/** prototypes **/
static void istoreitemResLoad(istoreitem*);
static void istoreitemResUnLoad(istoreitem*);
static void istoreitemDestroy(istoreitem*);


/* +------------------------------- STORES -------------------------------+ */

typedef struct istoreClass istoreClass;
typedef struct istoreEditableClass istoreEditableClass;

typedef struct istore {
  tllistitem		super;		/* super */
  vresource		res;		/* associated dict resource */
  unsigned long		outstanding;	/* number of user of all items */
  vdict		       *dict;		/* items */
  unsigned int		dirty:1;	/* TRUE if been edited since store */
  unsigned int		noedits:1;	/* TRUE if store cannot be changed */
}istore;

#define istoreCLASS(CLASS, STORE)					\
  tllistitemCLASS(CLASS, STORE);					\
  vclassMETHOD(istoreCLEAR, (STORE *));					\
  vclassMETHOD_RET(istoreRETRIEVE, vimage*, (STORE*, const vchar*));	\
  vclassMETHOD_RET(istoreRELEASE, int, (STORE*, const vchar*));		\
  vclassMETHOD_RET(istoreCOUNT_USERS, int, (STORE*, const vchar*));	\
  vclassMETHOD_RET(istoreMAKE_LISTING, const vname**, (STORE *));	\
  vclassMETHOD(istoreFREE_LISTING, (STORE *, const vname**))

#define istoreEditableCLASS(CLASS, STORE)				\
  istoreCLASS(CLASS, STORE);						\
  vclassMETHOD(istorePASTE_IMAGES, (STORE *, vdict*, void**));		\
  vclassMETHOD(istoreADD_IMAGE, (STORE *, vimage*, const vchar*, void**)); \
  vclassMETHOD(istoreREM_IMAGE, (STORE *, const vchar*, void**));	\
  vclassMETHOD(istorePRELOAD, (STORE*))

struct istoreClass {
  istoreCLASS(istoreClass, istore);
};

struct istoreEditableClass {
  istoreEditableCLASS(istoreEditableClass, istore);
};

/** attribute access **/
#define istoreGetLLItem(s)		(&(s)->super)
#define istoreGetObject(s)		tllistitemGetObject(&(s)->super)
#define istoreGetOutstanding(s)		((s)->outstanding)
#define istoreGetRes(s)			((s)->res)
#define istoreGetDict(s)		((s)->dict)
#define istoreGetTag(s)			vobjectGetTag(tllistitemGetObject(&(s)->super))
#define istoreIsDirty(s)		((s)->dirty)
#define istoreIsReadonly(s)		((s)->noedits)
#define istoreGetClass(s)		((istoreClass*)tllistitemGetClass(&(s)->super))
#define istoreGetEditableClass(s)	((istoreEditableClass*)tllistitemGetClass(&(s)->super))
#define istoreGetData(s)		tllistitemGetData(&(s)->super)
#define istoreClearOutstanding(s)	(s)->outstanding = 0
#define istoreSetRes(s,r)		(s)->res = (r)
#define istoreSend(s,m,a)		vclassSend(istoreGetClass(s),m,a)
#define istoreSendEditable(s,m,a)	vclassSend(istoreGetEditableClass(s),m,a)

/** creation **/
#define istoreCreateEditable()	\
  ((istore*)tllistitemCreateOfClass((tllistitemClass*)(imanagerGlobals()->defaultEditableStoreClass)))
#define istoreLoad(r)			((istore*)vobjectLoad(r))

/** other messages **/
#define istoreDestroy(s)		istoreSend(s, vobjectDESTROY, (s))
#define istoreDump(s,fp,b)		istoreSend(s, tllistitemDUMP, (s,fp,b))
#define istoreClear(s)			istoreSend(s, istoreCLEAR, (s))
#define istoreRetrieveImage(s,t)	istoreSend(s, istoreRETRIEVE, (s,t))
#define istoreReleaseImage(s,t)		istoreSend(s, istoreRELEASE, (s,t))
#define istoreCountNumberOfUsers(s,t)	istoreSend(s, istoreCOUNT_USERS, (s,t))
#define istoreMakeListing(s)		istoreSend(s, istoreMAKE_LISTING, (s))
#define istoreFreeListing(s,l)		istoreSend(s, istoreFREE_LISTING, (s,l))
#define istoreStore(s,r)		istoreSendEditable(s, vobjectSTORE, (s,r))
#define istoreCopy(s,t)			istoreSendEditable(s, vobjectCOPY, (s,t))
#define istorePasteImages(s,d,u)	istoreSendEditable(s, istorePASTE_IMAGES, (s,d,u))
#define istoreAddImage(s,img,t,u)	istoreSendEditable(s, istoreADD_IMAGE, (s,img,t,u))
#define istoreRemoveImage(s,t,u)	istoreSendEditable(s, istoreREM_IMAGE, (s,t,u))
#define istorePreloadImages(s)		istoreSendEditable(s, istorePRELOAD, (s))

/** private methods **/
#define istoreDestroyUnbalanced(s)		\
  _istoreDestroyUnbalanced(s)
#define _istoreSendSuper(m,a) 			\
  vclassSendSuper(imanagerGlobals()->defaultStoreClass, m, a)
#define _istoreEditableSendSuper(m,a)		\
  vclassSendSuper(imanagerGlobals()->defaultEditableStoreClass,m,a)


/** undo Add or Remove store item **/
typedef vundoActionClass istoreAddRemImageActionClass;

typedef struct istoreAddRemImageAction {
  vundoAction		 action;	/* super */
  istore		*store;		/* associated store */
  istoreitem		*item;		/* added or removed */
  vdict			*dict;		/* add: used if undo of create dict */
  unsigned int		 addition:1;	/* TRUE if item addition */
  unsigned int		 created:1;	/* add: TRUE if created store dict */
  unsigned int		 dirty:1;	/* store's dirty bit at change */
}istoreAddRemImageAction;



/** undo Paste Image dictionary **/
typedef vundoActionClass istorePasteImagesActionClass;

typedef struct istorePasteImagesAction {
  vundoAction		action;		/* super */
  istore		*store;		/* associated store */
  vdict			*dict;		/* used if store empty or created */
  istoreitemList	ilist;		/* all inserted/changed items */
  int			count;		/* number of items pasted in */
  unsigned int		nuthin:1;	/* paste was a no-op */
  unsigned int		created:1;	/* created new dict for store */
  unsigned int		empty:1;	/* store was empty before paste */
  unsigned int		dirty:1;	/* store's "dirty" bit at paste */
}istorePasteImagesAction;


/** prototypes **/
static void _istoreRegisterClasses(void);
static const vchar *_istorePasteImagesActionGetName(vundoAction*);
static void _istorePasteImagesActionAct(vundoAction*);
static void _istorePasteImagesActionDestroy(vundoAction*);
static istoreAddRemImageActionClass *_istoreGetDefaultAddRemImageActionClass(void);

/* +---------------------------- IMAGE-MANAGER ---------------------------+ */

/** one struct per client **/
typedef struct _imanagerGlobals {
  /* da manager class */
  imanagerClass			*defaultClass;
  imanagerEditableClass		*defaultEditableClass;

  /* image stores */
  istoreClass			*defaultStoreClass;
  istoreEditableClass		*defaultEditableStoreClass;

  /* private to stores, for undo-ing */
  istoreAddRemImageActionClass	*defaultAddRemImageActionClass;
  istorePasteImagesActionClass	*defaultPasteImagesActionClass;
  imanagerUndoActionNamer	 undoNamer;
}_imanagerGlobals;


/** private methods **/
#define imanagerGlobals() ((_imanagerGlobals*)*imanagerMaster)
#define _imanagerCreateOfClass(c)					\
  ((imanager*)vinstanceCreateOfClass((vinstanceClass*)(c)))
#define _imanagerLoadStore(im,r)					\
  imanagerSend(im, imanagerLOAD_STORE, (im,r))
#define _imanagerSendSuper(m,a)						\
  vclassSendSuper(imanagerGlobals()->defaultClass, m, a)
#define imanagerLookupStore(im,r)					\
  _imanagerLookupStore(im,r)


/** variables **/
static void	**imanagerMaster = NULL;
static vpool	*imanagerPool = NULL;


/** prototypes **/
static void     _imanagerInitNames(void);
static void 	_imanagerGlobalShutdown(void);
static void 	_imanagerRegisterClasses(void);
static void    *_imanagerLookupStore(imanager*,vresource);


/*
 *+------------------------------------------------------------------------+
 * Image Manager's Exception Classes:
 *+------------------------------------------------------------------------+
 */

vexClass _imanagerNotRegisteredExceptionClass;
vexClass _imanagerNotSetupExceptionClass;
vexClass _imanagerThingNotSetupExceptionClass;
vexClass _imanagerThingNotFoundExceptionClass;


/*
 *+------------------------------------------------------------------------+
 * Image Store Items:
 *+------------------------------------------------------------------------+
 */


#if vdebugDEBUG
#undef vdebugTAG
static const char *const _itemTag = "store-item";
#define vdebugTAG _itemTag
#endif



static void
istoreitemInit(register istoreitem *item)
{
  item->image = NULL;
  item->res = vresourceNULL;
  item->users = 0;
  item->transient = vFALSE;
  item->tag = NULL;
  item->dirty = vTRUE;

  return;
}



static istoreitem*
istoreitemCreate(void)
{
  register istoreitem *item;

  item = (istoreitem*)vpoolAlloc(imanagerPool);
  istoreitemInit(item);

  return item;
}



static istoreitem*
istoreitemCreateTransient(const vname *tag, vimage *image)
{
  register istoreitem *item;

  vdebugIF((!tag || !image), vexGenerate(vexGetArgNullClass(),
           vexMESSAGE, "create transient: NULL arguments!",
           vexERRNO, 0, vexNULL));

  item = istoreitemCreate();
  item->transient = vTRUE;
  item->image = image;
  item->tag = tag;

  return item;
}



static istoreitem*
istoreitemLoad(vresource res)
{
  register istoreitem *item;

  vdebugIF((vresourceType(res)!=vresourceDICT),  vexGenerate(vexGetArgClass(),
           vexMESSAGE, "load: resource not a dict", vexERRNO, 0, vexNULL));

  item = istoreitemCreate();
  item->res   = res;
  item->dirty = vFALSE;
  if (vresourceTestGetTag(res, name_ItemTag, &item->tag) &&
      *item->tag==vcharNULL)
    item->tag = NULL;

  return item;
}



static void
istoreitemCopy(register istoreitem *item, register istoreitem *copy)
{
  vbool purge = vFALSE;

  vdebugIF((!item || !copy), vexGenerate(vexGetArgNullClass(), vexMESSAGE,
           "copy: NULL argument(s)!", vexERRNO, 0, vexNULL));

  if (copy->image)
  {
    vimageDestroy(copy->image);
    copy->image = NULL;
  }
 
  if ((purge=istoreitemNeedsLoading(item)))
    istoreitemResLoad(item);

  copy->tag       = item->tag;
  copy->image 	  = item->image ? vimageClone(item->image) : NULL;
  copy->users 	  = 0;
  copy->transient = vFALSE;
  copy->dirty     = vTRUE;

  if (purge) istoreitemResUnLoad(item);
  return;
}



static istoreitem*
istoreitemClone(istoreitem *item)
{
  istoreitem *volatile copy;

  copy = istoreitemCreate();
  vexWITH_HANDLING
  {
    istoreitemCopy(item, copy);
  }
  vexON_EXCEPTION
  {
    istoreitemDestroy(copy);
    vexPropagate(vexGetRootClass(), vexMESSAGE, "clone: barfed",vexNULL);
  }
  vexEND_HANDLING;

  return copy;
}



static void
istoreitemDestroy(istoreitem *item)
{
#if vdebugDEBUG
  if (!item)
    vexGenerate(vexGetArgNullClass(), vexMESSAGE, "destroy: NULL item",
                vexERRNO, 0, vexNULL);
  if (!vpoolIsValidElem(imanagerPool, item))
    vexGenerate(vexGetArgClass(), vexMESSAGE, "destroy: item not allocated "
               "by image manager!", vexERRNO, 0, vexNULL);
#endif

  if (item->image)
    vimageDestroy(item->image);

  vpoolFree(imanagerPool, item);

  return;
}



static void
istoreitemResLoad(istoreitem *item)
{
#if vdebugDEBUG 
  if (!item)
    vexGenerate(vexGetArgNullClass(), vexMESSAGE, "res-load: NULL item",
                vexERRNO, 0, vexNULL);
  if (item->image) 
    vdebugWarn("resload: istoreitem res-loaded multiple times or not "
               "cleared after unload?!");
#endif

  if (item->res==vresourceNULL)
    vexGenerate(vexGetArgClass(), vexMESSAGE, "res-load: the given item is "
                "not a resource based item!", vexERRNO, 0, vexNULL);

  item->image = vimageLoad(item->res);
  return;
}



static void
istoreitemResUnLoad(istoreitem *item)
{
  vdebugIF((!item), vexGenerate(vexGetArgNullClass(), vexMESSAGE, 
            "res-unload: NULL item", vexERRNO, 0, vexNULL));

  if (item->res==vresourceNULL)
    vexGenerate(vexGetArgClass(), vexMESSAGE, "res-unload: the given item "
               "is not a resource based item!", vexERRNO, 0, vexNULL);

  if (item->image)
    vimageDestroy(item->image);

  item->image = NULL;
  return;
}



static void
istoreitemStore(register istoreitem *item, vresource res)
{
  int purge = vFALSE;

  if (!item->tag)
    vexGenerate(vexGetArgClass(), vexMESSAGE, "store: item not properly "
                "initialized. missing tag.", vexERRNO, 0, vexNULL);

  if (item->res==vresourceNULL)
  {
    if (!item->image)
      vexGenerate(vexGetArgClass(), vexMESSAGE, "store: item not properly "
                "initialized. missing image.", vexERRNO, 0, vexNULL);
  }
  else
  if (item->res!=res && !item->image)
  {
    purge = vTRUE;
    istoreitemResLoad(item);
  }

  if (item->res==vresourceNULL)
    (void)vresourceMake(res, name_ItemTag);
    
  vresourceSetTag(res, name_ItemTag, item->tag);

  if (item->res!=res || (item->image && item->dirty))
    vimageStore(item->image, res);

  if (purge)
  {
    if (item->dirty)
      item->dirty = vFALSE;
    istoreitemResUnLoad(item);
  }

  item->res = res;
  item->dirty = vFALSE;
  return;
}



static vimage *
istoreitemRetrieve(istoreitem *item)
{
  if (item->res==vresourceNULL && !item->image)
    item->image = vimageCreate();
  else
  if (!item->image)
    istoreitemResLoad(item);

  item->users++;

  return item->image;
}



static void
istoreitemRelease(istoreitem *item, int purge)
{
  if (!item->users || !item->image)
    vexGenerate(vexGetArgClass(), vexMESSAGE, "release: item has no "
                "users and/or no image!", vexERRNO, 0, vexNULL);
  
  item->users--;
  if (!item->users && purge && item->res!=vresourceNULL && !item->dirty)
    istoreitemResUnLoad(item);

  return;
}


#if 0
static int
istoreitemMatches(register istoreitem *item, const vchar *tag)
{
  register int equal;
  
  if (!item->tag) 
    equal = vFALSE;
  else 
    equal = vcharCompare(item->tag, tag)==0;
  
  return equal;
}
#endif


static vimage*
istoreitemSetImage(istoreitem *item, vimage *image, int shallow)
{
  vimage *oldimage;

  if (item->users)
    return NULL;

  oldimage = item->image;

  if (item->image && !shallow)
    {
      vimageDestroy(item->image);
      oldimage = NULL;
    }
  
  item->image = image;
  item->dirty = vTRUE;
  return oldimage;
}



#if vdebugDEBUG
static void
istoreitemDump(register istoreitem *item, register FILE *fp)
{
  char	*ascii;

  if (!fp)
    fp = vdebugGetInfoStream();

  if (item->tag)
    ascii = (char*)vcharExportAlloc(vcharScribeASCIIExport(item->tag));
  else
    ascii = "*undefined*";

  fprintf(fp, "\t\tstore-item(%p, %s)\n", item, ascii);
  fprintf(fp, "\t\t  resource: %ld\n", item->res);
  fprintf(fp, "\t\t  image: %p\n", item->image);
  fprintf(fp, "\t\t  users: %d\n", item->users);
  fprintf(fp, "\t\t  dirty: %c\n", item->dirty ? 'T' : 'F');
  fprintf(fp, "\t\t  transient: %c\n", item->transient ? 'T' : 'F');

  if (item->tag)
    vcharExportFree(ascii);

  return;
}
#endif


/*
 *+------------------------------------------------------------------------+
 * Image Store Item Lists:
 *+------------------------------------------------------------------------+
 */

#if vdebugDEBUG
#undef vdebugTAG
static const char *const _listTag = "store-itemlist";
#define vdebugTAG _listTag
#endif



static void
istoreitemListInit(register istoreitemList *list)
{
  vdebugIF((!list), vexGenerate(vexGetArgNullClass(), vexMESSAGE,
           "init: NULL list!", vexERRNO, 0, vexNULL));

  list->b = (istoreitem**)vmemAlloc(5*sizeof(istoreitem*));
  list->e = list->b;
  list->x = list->b + 5;
  return;
}


static void
istoreitemListFree(register istoreitemList *list)
{
  vdebugIF((!list || !list->b), vexGenerate(vexGetArgNullClass(), vexMESSAGE,
           "free: NULL or empty list!", vexERRNO, 0, vexNULL));

  vmemFree(list->b);
  return;
}


static void
istoreitemListAppend(register istoreitemList *list, istoreitem *item)
{
  vdebugIF((!list || !list->b), vexGenerate(vexGetArgNullClass(), vexMESSAGE,
           "append: NULL or empty list!", vexERRNO, 0, vexNULL));

  if (list->e == list->x)
  {
    int   n = list->x-list->b;
    void *p = vmemRealloc(list->b, (n+5)*sizeof(istoreitem*));
    list->b = p;
    list->e = list->b+n;
    list->x = list->e+5;
  }
  *list->e = item;
  list->e++;
  return;
}


static istoreitem**
istoreitemListGetStart(register istoreitemList *list)
{
  vdebugIF((!list || !list->b), vexGenerate(vexGetArgNullClass(), vexMESSAGE,
           "@start: NULL or empty list!", vexERRNO, 0, vexNULL));

  return list->b;
}


static istoreitem**
istoreitemListGetStop(register istoreitemList *list)
{
  vdebugIF((!list || !list->b), vexGenerate(vexGetArgNullClass(), vexMESSAGE,
           "@stop: NULL or empty list!", vexERRNO, 0, vexNULL));

  return list->e;
}



/*
 *+------------------------------------------------------------------------+
 * Image Stores:
 *+------------------------------------------------------------------------+
 */


#if vdebugDEBUG
#undef vdebugTAG
static const char *const _storeTag = "store";
#define vdebugTAG _storeTag
#endif




 static void
_istoreInitEditable(register istore *store)
{
  _istoreEditableSendSuper(vobjectINIT, (store));

   store->res = vresourceNULL;
   store->outstanding = 0;
   store->dict = vdictCreate(vnameHashString);
   store->dirty = vTRUE;
   store->noedits = vFALSE;

   return;
}



 static void
_istoreLoad(register istore *store, vresource res)
{
  register int	count;
  vresource	ires;
  istoreitem	*item;
  const vname	*tag;
  istore	*volatile store_v;
  
  vdebugIF((vresourceType(res)!=vresourceDICT), vexGenerate(vexGetArgClass(),
           vexMESSAGE, "load: resource is not a dict", vexERRNO, 0, vexNULL));

  _istoreSendSuper(vobjectLOAD_INIT, (store, res));

  store->outstanding = 0;
  store->dirty = vFALSE;
  store->res = res;
  store->dict = vdictCreate(vnameHashString);
  store->noedits = vTRUE;

  if (!vresourceTestGet(res, name_ImagesComponent, &res))
    return;

  store_v = store;

  vexWITH_HANDLING
  {
    count = vresourceCountComponents(res);
    for (--count; count>=0; count--)
    {
      ires = vresourceGetNthComponent(res, count, &tag);
      item = istoreitemLoad(ires);
      if (!item->tag) item->tag = tag;
      vdictStore(store->dict, tag, item);
    }
  }
  vexON_EXCEPTION
  {
    vdictIterator iter;
    vdictInitIterator(&iter, store_v->dict);
    while (vdictNextIterator(&iter))
      istoreitemDestroy((istoreitem*)vdictGetIteratorValue(&iter));
    vdictDestroyIterator(&iter);
    vdictDestroy(store_v->dict);
    store_v->dict = NULL;
    store_v->res = vresourceNULL;
    vexPropagate(vexGetRootClass(), vexMESSAGE, "load: barfed!", vexNULL);
  }
  vexEND_HANDLING;

  return;
}



 static void
_istoreLoadEditable(register istore *store, vresource res)
{
  _istoreEditableSendSuper(vobjectLOAD_INIT, (store,res));
   store->noedits = vFALSE;
   return;
}



 static void
_istoreStoreEditable(register istore *store, vresource res)
{

  vdictIterator			iterator;
  register vdictIterator	*iter= &iterator;
  int				count;
  vresource			sres, ires;
  register istoreitem		*item;
  const vname			*tag;
  
  if (!store->dict)
    vexGenerate(vexGetArgClass(), vexMESSAGE, "save: missing "
               "item dictionary!", vexERRNO, 0, vexNULL);
  vdebugIF((!store->dirty), vdebugWarn("save: store isn't dirty?!\n"));


  /* inherited attributes (esp. vclass identifier). Note we change
   * the resource's class tag back to the read-only version (st
   * it can be read by this class -- problem with storing classes
   * in general) */
 _istoreEditableSendSuper(vobjectSTORE, (store, res));
  vresourceSetTag(res, vname_Class, vnameInternGlobalLiteral(literal_StoreClass));


  /* where the actual images are stored */
  sres = vresourceMake(res, name_ImagesComponent);

  /* remove items that don't belong anymore */
  count = (vresourceType(sres)==vresourceDICT) ? 
           vresourceCountComponents(sres) : 0;
  if (count>0) 
    for (--count; count>=0; count--)
    {
      ires = vresourceGetNthComponent(sres, count, &tag);
      if (!(item=(istoreitem*)vdictLoad(store->dict, tag)))
        vresourceRemoveIfExists(ires, vresourceTAG_NULL);
    }

  /* store items that do belong */
  vdictInitIterator(iter, store->dict);
  while (vdictNextIterator(iter))
  {
    item = (istoreitem*)vdictGetIteratorValue(iter);
    if (!item->tag || (item->res==vresourceNULL && !item->image))
      imanagerGenerateThingNotSetupException("save: found item missing "
                  "tag and/or resource and/or image");
    if (item->res!=vresourceNULL && item->image)
      istoreitemStore(item, item->res);
    else
    if (item->res==vresourceNULL)
    {
      ires = vresourceCreate(sres, item->tag, vresourceDICT);
      istoreitemStore(item, ires);
    }
  }
  vdictDestroyIterator(iter);


  /* remember where we're stored */
  store->res   = res;
  store->dirty = vFALSE;

  return;
}



 static void
_istoreDestroy(istore *store)
{
  istoreClear(store);

  if (store->dict)
    vdictDestroy(store->dict);

  _istoreSendSuper(vobjectDESTROY, (store));

  return;
}



 static void
_istoreDestroyUnbalanced(istore *store)
{
  store->outstanding = 0;
  istoreDestroy(store);
  return;
}



 static void
_istoreClear(istore *store)
{
  vdictIterator		  iterator;
  register vdictIterator *iter = &iterator;
  register istoreitem	 *item;

  if (store->outstanding>0)
    imanagerGenerateThingNotSetupException("clear: has outstanding items!");

  if (store->dict)
  {
    vdictInitIterator(iter, store->dict);
    while (vdictNextIterator(iter))
    {
      item = (istoreitem*)vdictGetIteratorValue(iter);
      istoreitemDestroy(item);
    }
    vdictDestroyIterator(iter);
  }

  store->dirty = vTRUE;
  return;
}



 static void
_istoreCopyEditable(istore *store, istore *copy)
{
  vdictIterator			iterator;
  register vdictIterator	*iter= &iterator;
  register istoreitem		*item, *itemcopy;

  _istoreEditableSendSuper(vobjectCOPY, (store, copy));

  if (copy->dict)
    istoreClear(copy);
  else
  if (store->dict)
    copy->dict = vdictCreate(vnameHashString);

  if (store->dict)
  {
    vdictInitIterator(iter, store->dict);
    while (vdictNextIterator(iter))
    {
      item = (istoreitem*)vdictGetIteratorValue(iter);
      itemcopy = istoreitemClone(item);
      vdictStore(copy->dict, item->tag, itemcopy);
    }
    vdictDestroyIterator(iter);
  }

  copy->outstanding = 0;
  copy->dirty = vTRUE;
  return;
}



 static void
_istoreCopyInitEditable(istore *store, istore *copy)
{
 _istoreInitEditable(copy);
 _istoreCopyEditable(store, copy);
  return;
}



 static void
_istoreFlipFlopImagesEditable(istore *store, istoreitem *temp)
{
  vimage     *image;
  istoreitem *item;

  vdebugIF((store->noedits), vexGenerate(vexGetArgClass(), vexMESSAGE,
           "flipflop image: store is readonly!", vexERRNO, 0, vexNULL));

  item = (istoreitem*)vdictLoad(store->dict, temp->tag);
  image= istoreitemSetImage(item, temp->image, vTRUE);
  (void)istoreitemSetImage(temp, image, vTRUE);

  return;
}



 static void
_istorePasteImagesEditableUndoable(istore *store, vdict *imagedict, 
				   void **retaction)
{
  register istoreitem		*item;
  istoreitem			*temp;
  vimage			*image, *oldimage;
  istoreitemList		*ilist;
  istorePasteImagesActionClass	*actionClas;
  register istorePasteImagesAction *action;
  vdictIterator			 iterator;
  vdictIterator			*iter = &iterator;
  const vname			*tag;
  register int			 empty;
  int				 changed = vFALSE;

  vdebugIF((store->noedits), vexGenerate(vexGetArgClass(), vexMESSAGE,
           "paste images: store is readonly!", vexERRNO, 0, vexNULL));


  /* register paste action class if necessary */
  actionClas = imanagerGlobals()->defaultPasteImagesActionClass;
  if (!actionClas)
    {
      actionClas = vclassReproduce(vundoGetDefaultActionClass());
      vclassSetObjectSize(actionClas, sizeof(istorePasteImagesAction));
      vclassSet(actionClas, vundoGET_NAME, _istorePasteImagesActionGetName);
      vclassSet(actionClas, vundoACT, _istorePasteImagesActionAct);
      vclassSet(actionClas, vundoDESTROY, _istorePasteImagesActionDestroy);
      imanagerGlobals()->defaultPasteImagesActionClass = actionClas;
    }


  /* create new undoable paste action */
  action = (istorePasteImagesAction*)vundoCreateActionOfClass(actionClas);
  action->store = store;
  action->dict  = NULL;
  action->count = 0;


  /* nuthin' to do */
  action->nuthin = !imagedict || vdictGetSize(imagedict)<=0;
  if (action->nuthin)
    {
     *retaction = action;
      vundoActAction((vundoAction*)action);
      return;
    }


  /* remember the state of the store's dict */
  action->empty = empty = (!store->dict || vdictGetSize(store->dict)<=0);
  if ((action->created=!store->dict))
    store->dict=vdictCreate(vnameHashString);
  if (!action->created && empty)
    action->dict=vdictCreate(vnameHashString);


  /* for each item added or changed put an entry in the
   * undo-action's item list...ick
   */
  ilist = &action->ilist;
  istoreitemListInit(ilist);

  vdictInitIterator(iter, imagedict);
  while (vdictNextIterator(iter))
  {
    tag   = vdictGetIteratorKey(iter);
    image = (vimage*)vdictGetIteratorValue(iter);
    item  = NULL;

    if (!empty)
      {
	item = (istoreitem*)vdictLoad(store->dict, tag);
	if (item && (oldimage = istoreitemSetImage(item, image, vTRUE)))
	  {
	    temp = istoreitemCreateTransient(tag, oldimage);
	    istoreitemListAppend(ilist, temp);
	    changed = vTRUE;
	  }
      }

    if (!item)
      {
	item = istoreitemCreate();
	item->tag = tag;
	(void)istoreitemSetImage(item, image, vFALSE);
	vdictStore(store->dict, tag, item);
	istoreitemListAppend(ilist, item);
	item->users++, action->count++;
	changed = vTRUE;
      }
  }
  vdictDestroyIterator(iter);


  /* remember the state of the store before the paste */
  if (!changed)
    {
      if (action->created)
        vdictDestroy(store->dict), store->dict = NULL;
      else 
      if (action->dict)
	vdictDestroy(action->dict);
      istoreitemListFree(ilist);
      action->nuthin = vTRUE;
    }
  else
    {
      action->dirty = store->dirty;
      store->dirty  = vTRUE;
      store->outstanding += action->count;
    }


  /* set the undo state to DONE */
  vundoActAction((vundoAction*)action);
 *retaction = action;


  /* done */
  return;
}



 static void
_istoreAddImageEditableUndoable(istore *store, vimage *image, 
				const vname *tag, void **retaction)
{
  istoreAddRemImageActionClass	*actionClas;
  register istoreAddRemImageAction *action;
  vimage			*oldimage;
  register istoreitem		*item;
  vbool				 changed;

#if vdebugDEBUG
  if (store->noedits)
    vexGenerate(vexGetArgClass(), vexMESSAGE, "add image: store is readonly",
                vexERRNO, 0, vexNULL);
  if (!image || !tag || !retaction)
    vexGenerate(vexGetArgNullClass(), vexMESSAGE, "add image: NULL arguments",
		vexERRNO, 0, vexNULL);
#endif

  /* our undo action */
  actionClas = _istoreGetDefaultAddRemImageActionClass();
  action = (istoreAddRemImageAction*)vundoCreateActionOfClass(actionClas);
  action->store    = store;
  action->addition = vTRUE;

  /* assume nothing done */
  changed = vFALSE;
  action->item = NULL;
  action->dict = NULL;


  /* remember if we created a new store dictionary */
  if (!store->dict)
    action->dict = store->dict = vdictCreate(vnameHashString);


  /* remember if we overwrite an existing item or not */
  oldimage = NULL;
  item = (istoreitem*)vdictLoad(store->dict, tag);

  if (item && (oldimage = istoreitemSetImage(item, image, vTRUE)))
    {
      item = istoreitemCreateTransient(tag, oldimage);
      action->item = item;
      changed = vTRUE;
    }
  else if (!item)
    {
      item = istoreitemCreate();
      item->tag = tag;
      (void)istoreitemSetImage(item, image, vFALSE);
      vdictStore(store->dict, tag, item);
      action->item = item;
      changed = vTRUE;
      item->users++, store->outstanding++;
    }

  /* if not changed free extras now, else remember dirty */
  if (!changed)
    {
      if (action->dict)
	vdictDestroy(store->dict), action->dict = NULL, store->dict = NULL;
      action->item = NULL;
    }
  else
    {
      action->dirty = store->dirty;
      store->dirty  = vTRUE;
    }

  /* set the undo state to DONE */
  vundoActAction((vundoAction*)action);
 *retaction = action;

  return;
}



 static void
_istoreRemoveImageEditableUndoable(istore *store, const vname *tag,
				   void **retaction)
{
  register istoreAddRemImageAction *action;
  istoreAddRemImageActionClass	*actionClas;
  register istoreitem		*item = NULL;

#if vdebugDEBUG
  if (store->noedits)
    vexGenerate(vexGetArgClass(), vexMESSAGE, "del image: store is readonly",
                vexERRNO, 0, vexNULL);
  if (!tag || !retaction)
    vexGenerate(vexGetArgNullClass(), vexMESSAGE, "del image: NULL arguments",
		vexERRNO, 0, vexNULL);
#endif

  /* If we don't have such an item */
  if (!store->dict || !(item= (istoreitem*)vdictLoad(store->dict, tag)))
    imanagerGenerateThingNotFoundException("del image: item not found");


  /* If the item's is currently locked */
  if (item->users>0)
    imanagerGenerateThingNotSetupException("del image: item in use");


  /* our undo action */
  actionClas = _istoreGetDefaultAddRemImageActionClass();
  action = (istoreAddRemImageAction*)vundoCreateActionOfClass(actionClas);
  action->store    = store;
  action->addition = vFALSE;


  /* save the item reference for undooes/redooes */
  action->item  = item;
  action->dirty = store->dirty;


  /* zap it from the store's list */
  vdictRemove(store->dict, tag);
  store->dirty = vTRUE;


  /* set the undo state to DONE */
  vundoActAction((vundoAction*)action);
 *retaction = action;

  return;
}



 static void
_istorePreloadToMemoryEditable(istore *store)
{
  vdictIterator		  iterator;
  register vdictIterator *iter = &iterator;
  register istoreitem	 *item;

  if (store->res==vresourceNULL)
    return;
    
  vdictInitIterator(iter, store->dict);
  while (vdictNextIterator(iter))
    {
      item = (istoreitem*)vdictGetIteratorValue(iter);
      if (item->res!=vresourceNULL && !item->image)
        istoreitemResLoad(item);
    }
  vdictDestroyIterator(iter);

  return;
}



 static vimage*
_istoreRetrieveImage(istore *store, const vchar *str)
{
  vimage		*image = NULL;
  register istoreitem	*item;
  const vname		*tag;


  /* We can quickly check if we've got the image in our
   * store by retrieving the name from the global name table.
   * if the name isn't there, we can't have a matching image.
   */
  if (store->dict)
  {
    tag = vnameGetGlobal(str);
    if (tag)
      {
        item = (istoreitem*)vdictLoad(store->dict, tag);
	vdebugIF(!item, vexGenerate(vexGetReturnNullClass(), vexMESSAGE,
                 "retrieve image: NULL value in dictionary!", vexERRNO, 0,
                 vexNULL));
	image = istoreitemRetrieve(item);
	store->outstanding++;
      }
  }

  return image;
}



 static int
_istoreReleaseImage(istore *store, const vchar *str)
{
  register istoreitem	*item;
  const vname		*tag;
  int			 owned = vFALSE;

  /* We can quickly check if we've got the image in our
   * store by retrieving the name from the global name table.
   * if the name isn't there, we can't have a matching image.
   */
  if (store->dict)
  {
    tag = vnameGetGlobal(str);
    if (tag)
    {
      item = (istoreitem*)vdictLoad(store->dict, tag);
      vdebugIF(!item, vexGenerate(vexGetReturnNullClass(), vexMESSAGE,
               "release image: NULL value in dictionary!", vexERRNO, 0,
               vexNULL));
      istoreitemRelease(item, store->noedits);
      store->outstanding--;
      owned = vTRUE;
    }
  }

  return owned;
}




 static int
_istoreCountImageUsers(istore *store, const vchar *str)
{
  register istoreitem		*item;
  int				 count = -1;
  const vname			*tag;

  /* We can quickly check if we've got the image in our
   * store by retrieving the name from the global name table.
   * if the name isn't there, we can't have a matching image.
   */
  if (store->dict)
  {
    tag = vnameGetGlobal(str);
    if (tag)
    {
      item = (istoreitem*)vdictLoad(store->dict, tag);
      if (item)
	count = item->users;
    }
  }

  return count;
}




 static int
_istoreCmpListingItem(register const void *one, register const void *two)
{
  return vcharCompare(*((const vname**)one), *((const vname**)two));
}

 static const vname**
_istoreCreateListingOfImages(istore *store)
{
  register const vname 		**scan;
  const vname			**tags;
  vdictIterator			 iterator;
  register vdictIterator	*iter = &iterator;
  int				 count;
  register istoreitem		*item;


  if (!store->dict || (count=vdictGetSize(store->dict))<=0)
    return NULL;

  scan = tags = (const vname**)vmemAllocAndClear((count+1)*sizeof(vname*));

  vdictInitIterator(iter, store->dict);
  while (vdictNextIterator(iter))
    {
      item = (istoreitem*)vdictGetIteratorValue(iter);
      if (item->tag)
	*scan++ = item->tag;
      else
	*scan++ = vnameNULL; /*?*/
    }
  vdictDestroyIterator(iter);

  qsort(tags, count, sizeof(const vname*), _istoreCmpListingItem);

  return tags;
}



 static void
_istoreDestroyListingOfImages(istore *store, const vname **tags)
{
  vdebugIF((!tags), vexGenerate(vexGetArgNullClass(), vexMESSAGE,
           "destroy image list: NULL argument!", vexERRNO, 0, vexNULL));
  vmemFree(tags);
  return;
}





static istore*
istoreLoadEditable(vresource res)
{
  register vinstanceClass	*clas;
  register vobject 		*obj;

  clas = (vinstanceClass*)imanagerGlobals()->defaultEditableStoreClass;
  obj  = (vobject*)vclassAlloc(clas);

  vinstanceInitClass((vinstance*)obj, clas);
  vclassSend((vobjectClass*)clas, vobjectLOAD_INIT, (obj,res));

  return (istore*)obj;
}





 static void
_istoreDump(register istore *store, register FILE *fp, int deep)
{
#if vdebugDEBUG
  vdictIterator		  iterator;
  register vdictIterator *iter = &iterator;
  char			 *ascii;

  if (!fp)
    fp = vdebugGetInfoStream();

  if (istoreGetTag(store))
    ascii = (char*)vcharExportAlloc(vcharScribeASCIIExport(istoreGetTag(store)));
  else
    ascii = "*undefined*";

  fprintf(fp, "\tstore(%p, %s)\n", store, ascii);
  fprintf(fp, "\t  resource: %ld\n", store->res);
  fprintf(fp, "\t  dict: %p\n", store->dict);
  fprintf(fp, "\t  outstanding: %ld\n", store->outstanding);
  fprintf(fp, "\t  dirty: %c\n", store->dirty ? 'T' : 'F');
  fprintf(fp, "\t  readonly: %c\n", store->noedits ? 'T' : 'F');

  if (deep)
    if (!store->dict)
      {
	fprintf(fp, "\t  items: *none*\n");
      }
    else
      {
	fprintf(fp, "\t  items:\n");
	vdictInitIterator(iter, store->dict);
	while (vdictNextIterator(iter))
	  istoreitemDump((istoreitem*)vdictGetIteratorValue(iter), fp);
	vdictDestroyIterator(iter);
      }

  if (istoreGetTag(store))
    vcharExportFree(ascii);
#endif
  return;
}







 static void
_istoreRegisterClasses(void)
{
  register istoreClass		*readClas;
  register istoreEditableClass	*editClas;


  /* register with class manager */
  readClas = vclassSpawn(tllistitemGetDefaultClass(), sizeof(istoreClass));
  vclassSetNameScribed(readClas, vcharScribeLiteral(literal_StoreClass));
  vclassSetObjectSize(readClas, sizeof(istore));

  /* inherited */
  vclassSet(readClas, vobjectLOAD_INIT, _istoreLoad);
  vclassSet(readClas, vobjectDESTROY, _istoreDestroy);
  vclassSet(readClas, tllistitemDUMP, _istoreDump);

  /* our messages */
  vclassSet(readClas, istoreCLEAR, _istoreClear);
  vclassSet(readClas, istoreRETRIEVE, _istoreRetrieveImage);
  vclassSet(readClas, istoreRELEASE, _istoreReleaseImage);
  vclassSet(readClas, istoreCOUNT_USERS, _istoreCountImageUsers);
  vclassSet(readClas, istoreMAKE_LISTING, _istoreCreateListingOfImages);
  vclassSet(readClas, istoreFREE_LISTING, _istoreDestroyListingOfImages);

  /* save */
  imanagerGlobals()->defaultStoreClass = readClas;


  /* register with class manager */
  editClas = vclassSpawn(readClas, sizeof(istoreEditableClass));
  vclassSetNameScribed(editClas, vcharScribeLiteral("image-store-editable"));
  vclassSetObjectSize(editClas, sizeof(istore));

  /* inherited */
  vclassSet(editClas, vobjectINIT, _istoreInitEditable);
  vclassSet(editClas, vobjectLOAD_INIT, _istoreLoadEditable);
  vclassSet(editClas, vobjectCOPY, _istoreCopyEditable);
  vclassSet(editClas, vobjectCOPY_INIT, _istoreCopyInitEditable);
  vclassSet(editClas, vobjectSTORE, _istoreStoreEditable);

  /* our messages */
  vclassSet(editClas, istorePRELOAD, _istorePreloadToMemoryEditable);
  vclassSet(editClas, istoreADD_IMAGE, _istoreAddImageEditableUndoable);
  vclassSet(editClas, istoreREM_IMAGE, _istoreRemoveImageEditableUndoable);
  vclassSet(editClas, istorePASTE_IMAGES, _istorePasteImagesEditableUndoable);

  /* save */
  imanagerGlobals()->defaultEditableStoreClass = editClas;


  /* done */
  return;
}


/*
 *+------------------------------------------------------------------------+
 * Undoable Addition and Deletion of Images:
 *+------------------------------------------------------------------------+
 */


#if vdebugDEBUG
#undef vdebugTAG
static const char *const _addremActTag = "add-rem-action";
#define vdebugTAG _addremActTag
#endif



 static const vchar*
_istoreAddRemImageActionGetName(vundoAction *uaction)
{
  register istoreAddRemImageAction *action;
  action = (istoreAddRemImageAction*)uaction;
  return imanagerGlobals()->undoNamer(action->addition ? imanagerUNDO_OP_ADD
				      : imanagerUNDO_OP_REMOVE);
}



 static void
_istoreAddRemImageActionAct(vundoAction *uaction)
{
  register istoreAddRemImageAction	*action;
  register int				 deletion;
  register istoreitem			*item;
  register const vname			*tag = NULL;

  action   = (istoreAddRemImageAction*)uaction;
  deletion = !action->addition;

  if ((item = action->item)) 
    tag = item->tag;

  if (item)
    switch (vundoGetActionState(uaction))
      {
	/* +-------------- UNDO action --------------+ */
	case vundoDONE:   {

	  /* put it back */
	  if (deletion)
	    vdictStore(action->store->dict, tag, item);

	  /* if not new, switch back to original image */
	  else
	  if (item->transient)
	    _istoreFlipFlopImagesEditable(action->store, item);

	  /* else new, so nuke it */
	  else
	    {
	      if (action->dict)
		action->store->dict = NULL;
	      else
		vdictRemove(action->store->dict, tag);

	      action->store->outstanding--;
	    }
	  action->store->dirty = action->dirty;
	  break;
	}
	
	/* +-------------- REDO action --------------+ */
	case vundoUNDONE: {

	  /* remove it again */
	  if (deletion)
	    vdictRemove(action->store->dict, tag);

	  /* if not new, switch back to the newer image */
	  else
	  if (item->transient)
	    _istoreFlipFlopImagesEditable(action->store, item);

	  /* else insert it again */
	  else
	    {
	      if (action->dict)
		action->store->dict = action->dict;
	      else
		vdictStore(action->store->dict, tag, item);

	      action->store->outstanding++;
	    }
	  action->store->dirty = vTRUE;
	  break;
	}
      }

  vclassSendSuper(imanagerGlobals()->defaultAddRemImageActionClass,
		  vundoACT, (uaction));
  return;
}



 static void
_istoreAddRemImageActionDestroy(vundoAction *uaction)
{
  register istoreAddRemImageAction	*action;
  register int				 deletion;
  register istoreitem			*item;

  action   = (istoreAddRemImageAction*)uaction;
  deletion = !action->addition;

  if ((item=action->item))
    switch (vundoGetActionState(uaction))
      {
	/* +--------------- was DONE --------------+ */
	case vundoDONE:   {

	  if (deletion)
	    istoreitemDestroy(item);

	  else
	  if (item->transient)
	    istoreitemDestroy(item);
 
	  break;
	}

	/* +-------------- was UNDONE --------------+ */
	case vundoUNDONE: {

	  if (!deletion)
	    if (item->transient)
	      istoreitemDestroy(item);
	    else
	      {
		istoreitemDestroy(item);
		if (action->dict)
		  vdictDestroy(action->dict);
	      }
	  break;
	}
     }
 
  vclassSendSuper(imanagerGlobals()->defaultAddRemImageActionClass,
		  vundoDESTROY, (uaction));
  return;
}



 static istoreAddRemImageActionClass*
_istoreGetDefaultAddRemImageActionClass(void)
{
  if (!imanagerGlobals()->defaultAddRemImageActionClass)
    {
      register istoreAddRemImageActionClass *clas;
      clas = vclassReproduce(vundoGetDefaultActionClass());
      vclassSetObjectSize(clas, sizeof(istoreAddRemImageAction));
      vclassSet(clas, vundoGET_NAME, _istoreAddRemImageActionGetName);
      vclassSet(clas, vundoACT, _istoreAddRemImageActionAct);
      vclassSet(clas, vundoDESTROY, _istoreAddRemImageActionDestroy);
      imanagerGlobals()->defaultAddRemImageActionClass = clas;
    }
  return imanagerGlobals()->defaultAddRemImageActionClass;
}



/*
 *+------------------------------------------------------------------------+
 * Undoable Pasting of Images:
 *+------------------------------------------------------------------------+
 */

#if (vdebugDEBUG & 0)
#undef vdebugTAG
static const char *const _pasteActTag = "paste-action";
#define vdebugTAG _pasteActTag
#endif



 static const vchar*
_istorePasteImagesActionGetName(vundoAction *uaction)
{
  return imanagerGlobals()->undoNamer(imanagerUNDO_OP_PASTE);
}


 static void
_istorePasteImagesActionAct(vundoAction *uaction)
{
  istorePasteImagesAction	*action;
  istoreitemList		*ilist;
  register istoreitem		**scan, **stop;
  istoreitem			*item, *copy;
  vdict				*tempdict;
  vimage			*saveimage;


  action = (istorePasteImagesAction*)uaction;
  ilist  = &action->ilist;

  if (!action->nuthin)
    switch(vundoGetActionState(uaction))
      {
	/* +-------------- REDO action --------------+ */
	case vundoUNDONE: {
	  if (action->created || action->empty)
	    {
	      tempdict = action->store->dict;
	      action->store->dict = action->dict;
	      action->dict = tempdict;
	    }
	  else
	    {
	      scan = istoreitemListGetStart(ilist);
	      stop = istoreitemListGetStop(ilist);
	      for (; scan<stop; scan++)
		{
		  copy = *scan;
		  
		  /* switch images */
		  if (copy->transient)
		    {
		      item = (istoreitem*)vdictLoad(action->store->dict, copy->tag);
		      saveimage = istoreitemSetImage(item, copy->image, vTRUE);
		      (void)istoreitemSetImage(copy, saveimage, vTRUE);
		    }
		  /* insert item */
		  else
		    vdictStore(action->store->dict, copy->tag, copy);
		}
	    }
	  action->store->outstanding += action->count;
	  action->store->dirty = vTRUE;
	  break;
	}

	/* +-------------- UNDO action --------------+ */
	case vundoDONE:   {
	  if (action->created)
	    {
	      action->dict = action->store->dict;
	      action->store->dict = NULL;
	    }
	  else
	  if (action->empty)
	    {
	      tempdict = action->store->dict;
	      action->store->dict = action->dict;
	      action->dict = tempdict;
	    }
	  else
	    {
	      scan = istoreitemListGetStart(ilist);
	      stop = istoreitemListGetStop(ilist);
	      for (; scan<stop; scan++)
		{
		  copy = *scan;
		  item = (istoreitem*)vdictLoad(action->store->dict, copy->tag);
		  
		  /* switch images */
		  if (copy->transient)
		    {
		      saveimage = istoreitemSetImage(item, copy->image, vTRUE);
		      (void)istoreitemSetImage(copy, saveimage, vTRUE);
		    }
		  /* remove item */
		  else
		    vdictRemove(action->store->dict, copy->tag);
		}
	    }
	  action->store->outstanding -= action->count;
	  action->store->dirty = action->dirty;
	  break;
	}
      }/*switch*/

  vclassSendSuper(imanagerGlobals()->defaultPasteImagesActionClass,
		  vundoACT, (uaction));
  return;
}



 static void
_istorePasteImagesActionDestroy(vundoAction *uaction)
{
  istorePasteImagesAction	*action;
  istoreitemList		*ilist;
  register istoreitem		**scan, **stop;
  vdict				*tempdict;


  action = (istorePasteImagesAction*)uaction;
  ilist  = &action->ilist;

  if (!action->nuthin)
    switch(vundoGetActionState(uaction))
      {
	/* +-------------- was UNDONE --------------+ */
	case vundoUNDONE: {
	  if (action->created || action->empty)
	    {
	      tempdict = action->store->dict;
	      action->store->dict = action->dict;
	      istoreClear(action->store);
	      vdictDestroy(action->dict);
	      action->store->dict  = tempdict;
	      action->store->dirty = action->dirty;
	    }
	  else
	    {
	      scan = istoreitemListGetStart(ilist);
	      stop = istoreitemListGetStop(ilist);
	      for (; scan<stop; scan++)
		istoreitemDestroy(*scan);
	    }
	  break;
	}

	/* +--------------- was DONE ---------------+ */
	case vundoDONE: {
	  if (action->empty)
	    vdictDestroy(action->dict);
	  else 
	  if (!action->created)
	    {
	      scan = istoreitemListGetStart(ilist);
	      stop = istoreitemListGetStop(ilist);
	      for (; scan<stop; scan++)
		if ((*scan)->transient)
		  istoreitemDestroy(*scan);
	    }
	}
      }/*switch*/


  /* clear out itemlist */
  if (!action->nuthin)
    istoreitemListFree(ilist);


  /* hark hark superclass */
  vclassSendSuper(imanagerGlobals()->defaultPasteImagesActionClass,
		  vundoDESTROY, (uaction));
  return;
}



/*
 *+------------------------------------------------------------------------+
 * Image Manager:
 *+------------------------------------------------------------------------+
 */

#if vdebugDEBUG
#undef vdebugTAG
#define vdebugTAG _imanTag
#endif



imanager*
imanagerCreateEither(vapplication *app_, int editable)
{
  imanager *volatile im;
  vapplication *volatile app = app_;

  if (!app)
    app = vapplicationGetCurrent();

  if (!imanagerMaster)
  {
    imanagerMaster = vclientRegisterModule();
    imanagerPool   = vpoolCreate(sizeof(istoreitem));
    _imanagerInitNames();
    vclientRegisterGlobalShutdown(_imanagerGlobalShutdown);

    /* register with exception manager */
    vexInitClass(&_imanagerNotRegisteredExceptionClass, 
		 vexGetValueClass(),
		 "store not registered",
		 sizeof(imanagerNotRegisteredException),
		 (vexDumper)NULL);
    vexInitClass(&_imanagerNotSetupExceptionClass,
		 vexGetModuleStateClass(),
		 "no global store",
		 sizeof(imanagerNotSetupException),
		 (vexDumper)NULL);
    vexInitClass(&_imanagerThingNotSetupExceptionClass,
		 vexGetValueClass(),
		 "op illegal on item",
		 sizeof(imanagerThingNotSetupException),
		 (vexDumper)NULL);
    vexInitClass(&_imanagerThingNotFoundExceptionClass,
		 vexGetValueClass(),
		 "item not found",
		 sizeof(imanagerThingNotFoundException),
		 (vexDumper)NULL);
  }
  
  if (!*imanagerMaster)
  {
    vclientAllocateModule(imanagerMaster, sizeof(_imanagerGlobals));
    _istoreRegisterClasses();
    _imanagerRegisterClasses();
  }

  if (editable) 
    im = _imanagerCreateOfClass(imanagerGlobals()->defaultEditableClass);
  else 
    im = _imanagerCreateOfClass(imanagerGlobals()->defaultClass);

  vexWITH_HANDLING
    {
      imanagerSend(im, imanagerSTARTUP, (im, app));
    }
  vexON_EXCEPTION
    {
      imanagerSend(im, vinstanceDESTROY, (im));
      vexPropagate(vexGetModuleStartupClass(), 
		   vexMESSAGE, "create either: couldn't startup", 
		   vexERRNO, 0, vexNULL);
    }
  vexEND_HANDLING;

  return im;
}




void
imanagerDestroy(register imanager *im)
{
  register tllistIterator	*iter;
  register istore		*store;

  if (!im)
    return;

  if (im->stores)
  {
    iter = tllistCreateIterator(im->stores);

    tllistIteratorStartOver(iter);
    while (tllistIteratorMore(iter))
      {
	store = (istore*)tllistIteratorNextItem(iter);
	istoreClearOutstanding(store);
      }

    tllistDestroyIterator(im->stores, iter);
  }

  imanagerSend(im, vinstanceDESTROY, (im));
  return;
}





const vname *
imanagerGetImageStoreResourceTag(imanager *im)
{
  return name_Images;
}






const vname**
imanagerCreateListingOfImageStoreImages(imanager *im, vresource res)
{
  istore *store = imanagerLookupStore(im, res);

  if (!store)
    return NULL;

  return istoreMakeListing(store);
}





void
imanagerDestroyListingOfImageStoreImages(imanager *im, vresource res, 
					 const vname **listing)
{
  istore *store = imanagerLookupStore(im, res);

  if (!store)
    imanagerGenerateThingNotFoundException
      ("destroy listing: resource not a registered as an image store");

  istoreFreeListing(store, listing);
  return;
}




 static void
_imanagerInitNames(void)
{
  register const vname **name;
  register const char  **scan, **stop;

  name = names;
  scan = literals, stop = scan+NAME_COUNT;
  for (; scan<stop; scan++,name++)
    *name = vnameInternGlobalLiteral(*scan);

  return;
}




 static void
_imanagerInit(register imanager *im)
{
  _imanagerSendSuper(vinstanceINIT, (im));

  im->app          = NULL;
  im->tag          = NULL;
  im->stores       = NULL;
  im->global       = NULL;
  im->active  	   = NULL;
  im->activeRes    = vresourceNULL;
  im->genericImage = NULL;
  im->masks	   = NULL;
  im->reserved	   = NULL;

  return;
}




 static void
_imanagerSetTag(register imanager *im, const vname *tag)
{
  im->tag = tag;
}




 static void
_imanagerStartup(register imanager *im, vapplication *app)
{
  vresource	root, res;
  imanager	*volatile im_v;

  if (!app)
    app = vapplicationGetCurrent();
  im->app = app;

  root = vapplicationGetResources(app);
  if ((root==vresourceNULL) || !vresourceTestGet(root, name_Images, &res))
    vexGenerate(vexGetModuleStateClass(), vexMESSAGE, "startup: missing "
                "required imanager dict resource", vexERRNO, 0, vexNULL);

  im_v = im;
  vexWITH_HANDLING
    {
      im->active = im->global = _imanagerLoadStore(im, res);
      im->stores = tllistCreate();
      tllistAppendItem(im->stores, im->global);
      
      if (!vresourceTestGet(root, name_GenericImage, &res))
        im->genericImage = vimageCreate();
      else
        im->genericImage = vimageLoad(res);

      if (vresourceTestGet(root, name_ImageMasks, &res))
        im->masks = _imanagerLoadStore(im, res);
    }
  vexON_EXCEPTION
    {
       if (im_v->stores) 
        tllistDestroy(im_v->stores);
      else if (im_v->global) 
        istoreDestroy((istore*)im_v->global);
 
      vexPropagate(vexGetAbandonClass(), vexMESSAGE, "startup: can't locate "
                   "required resources", vexERRNO, 0, vexNULL);
    }
  vexEND_HANDLING;

  return;  
}




 static void
_imanagerDestroy(imanager *im)
{
  if (im->stores)
    tllistDestroy(im->stores);
  else 
  if (im->global)
    istoreDestroy((istore*)im->global);

  if (im->genericImage)
    vimageDestroy(im->genericImage);

  if (im->masks)
    istoreDestroyUnbalanced(im->masks);

 _imanagerSendSuper(vinstanceDESTROY, (im));

  return;
}




 static void*
_imanagerLoadImageStore(register imanager *im, vresource res)
{
  return istoreLoad(res);
}

 static void*
_imanagerLoadImageStoreEditable(register imanager *im, vresource res)
{
  return istoreLoadEditable(res);
}




 static void*
_imanagerLookupStore(imanager *im, register vresource res)
{
  vbool				registered;
  register tllistIterator	*iter;
  register istore		*store = NULL;

  if (res==vresourceNULL || (vresourceType(res)!=vresourceDICT))
    vexGenerate(vexGetArgClass(), vexMESSAGE, "lookup store: the given "
		"resource is not a dict resource!", vexERRNO, 0, vexNULL);

  if (!im->global)
    imanagerGenerateNotSetupException
      ("lookup store: manager not initialized (missing global store)");

  iter = tllistCreateIterator(im->stores);
  registered = vFALSE;

  tllistIteratorStartOver(iter);
  while (tllistIteratorMore(iter))
    {
      store = (istore*)tllistIteratorNextItem(iter);
      if (istoreGetRes(store)==res)
	{
	  registered = vTRUE;
	  break;
	}
    }
  tllistDestroyIterator(im->stores, iter);

  return registered ? store : NULL;
}




 static const void*
_imanagerResourceToStore(imanager *im, vresource res)
{
  register istore *store;

  if (res==vresourceNULL)
    store = im->global;
  else
  if (res==im->activeRes) 
    store = im->active;
  else 
    store = imanagerLookupStore(im, res);

  if (!store)
    imanagerGenerateThingNotFoundException
      ("res to store: resource not registered as an image store");

  return store;
}




 static void
_imanagerRegisterStore(imanager *im, vresource res)
{
  register istore *store;

  store = imanagerLookupStore(im, res);
  if (store)
    return;

  store = _imanagerLoadStore(im, res);
  tllistAppendItem(im->stores, store);

  im->active    = store;
  im->activeRes = res;

  return;
}




 static void
_imanagerUnRegisterStore(imanager *im, vresource res)
{
  register istore 	*store;
  int			reset;	

  store = imanagerLookupStore(im, res);
  if (!store)
    imanagerGenerateThingNotFoundException
      ("unregister store: resource not registered as an image store");

  reset = (store==im->active);

  tllistDeleteItem(im->stores, store, tllistDESTROY_ITEM);

  if (reset)
  {
    im->active    = im->global;
    im->activeRes = vresourceNULL;
  }
 
  return;
}




 static void
_imanagerUnRegisterUnbalancedStore(imanager *im, vresource res)
{
  register istore 	*store;
  int			reset;	

  store = imanagerLookupStore(im, res);
  if (!store)
    return;

  reset = (store==im->active);

  tllistDeleteItem(im->stores, store, !tllistDESTROY_ITEM);
  istoreDestroyUnbalanced(store);

  if (reset)
  {
    im->active   = im->global;
    im->activeRes= vresourceNULL;
  }
 
  return;
}




 static void
_imanagerSetActiveStore(register imanager *im, vresource res)
{
  register istore	*store;

  if (res==vresourceNULL)
  {
    im->active = im->global;
  }
  else
  if (im->activeRes!=res)
  {
    store = imanagerLookupStore(im, res);

    if (!store)
      imanagerGenerateThingNotFoundException
	("set active store: resource not registered as an image store");

    im->active  = store;
  }

  im->activeRes = res;
  return;
}




 static vresource
_imanagerGetActiveStore(register imanager *im)
{
  return (im->active && im->active!=im->global) 
  	? istoreGetRes((istore*)im->active) : vresourceNULL;
}




 static void
_imanagerAddImageToStoreUndoable(imanager *im, vresource res, vimage *img, 
			 	 const vname *tag, void **retaction)
{
  register istore *store;

  store = (istore*)_imanagerResourceToStore(im, res);

  istoreAddImage(store, img, tag, retaction);

  return;
}



 static void
_imanagerRemoveImageFromStoreUndoable(imanager *im, vresource res, 
			 	      const vname *tag, void **retaction)
{
  register istore *store;

  store = (istore*)_imanagerResourceToStore(im, res);

  istoreRemoveImage(store, tag, retaction);

  return;
}



 static void
_imanagerPasteResourceImagesIntoStoreUndoable(imanager *im, vresource res,
				      vresource images, void **retaction)
{
  register istore 	*store;
  register int		 count;
  const vname		*tag;
  vdict        		*volatile imagedict;
  vresource		 ires;
  vimage		*image;
  vdictIterator		 iterator, *iter = &iterator;
  int		 	 volatile boinked = vFALSE;

  vdebugIF((images==vresourceNULL || !retaction), 
	   vexGenerate(vexGetArgNullClass(), vexMESSAGE, "paste images: "
		       "NULL argument(s)!", vexERRNO, 0, vexNULL));

  store = (istore*)_imanagerResourceToStore(im, res);
  imagedict = NULL;

  vexUNWIND_PROTECT
    {
      imagedict = vdictCreate(vnameHashString);
      count = vresourceCountComponents(images);
      if (count>0) 
        for (--count; count>=0; count--)
        {
          ires  = vresourceGetNthComponent(images, count, &tag);
          image = vimageLoad(ires);
          vdictStore(imagedict, tag, image);
        }

       /* Remember: store assumes ownership of all images! */
       istorePasteImages(store, imagedict, retaction);
     }
  vexON_UNWIND
    {
       /* If we're here because of an exception, release images */
       if (imagedict && vexGetRootException())
       {
	 boinked = vTRUE;
         vdictInitIterator(iter, (vdict*)imagedict);
	 while (vdictNextIterator(iter))
	   vimageDestroy((vimage*)vdictGetIteratorValue(iter));
	 vdictDestroyIterator(iter);
       }

       /* Always destroy our temporary dictionary */
       vdictDestroy(imagedict);

       /* Propagate any faux-pausies */
       if (boinked)
	 vexPropagate(vexGetAppClass(), vexMESSAGE, "can't paste images",
		      vexERRNO, 0, vexNULL);
    }
  vexEND_UNWIND;
 
  return;
}




 static void
_imanagerPasteImagesIntoStoreUndoable(imanager *im, vresource res,
				      vdict *images, void **retaction)
{
  register istore *store;

  vdebugIF((images==NULL || !retaction), vexGenerate(vexGetArgNullClass(),
           vexMESSAGE, "paste images undoable: NULL argument(s)", vexERRNO,
           0, vexNULL));

  store = (istore*)_imanagerResourceToStore(im, res);

  istorePasteImages(store, images, retaction);
 
  return;
}




 static vimage*
_imanagerRetrieveImage(register imanager *im, const vchar *tag, int *match)
{
  register vimage *image;

  vdebugIF((!tag), vexGenerate(vexGetArgNullClass(), vexMESSAGE, 
           "retrieve image: NULL tag argument!", vexERRNO, 0, vexNULL));

  if (im->active && im->active!=im->global)
    image = istoreRetrieveImage((istore*)im->active, tag);
  else
    image = NULL;

  if (!image)
    image = istoreRetrieveImage((istore*)im->global, tag);

  if (!image)
  {
    if (match) *match = vFALSE;
    image = im->genericImage;
  }
  else
  if (match) *match = vTRUE;

  return image;
}




 static vimage*
_imanagerRetrieveImageGlobal(register imanager *im, const vchar *tag)
{
  register vimage *image;

  vdebugIF((!tag), vexGenerate(vexGetArgNullClass(), vexMESSAGE,
          "retrieve global image: NULL tag argument", vexERRNO, 0, vexNULL));

  image = istoreRetrieveImage((istore*)im->global, tag);

  if (!image)
    image = im->genericImage;

  return image;
}




 static void
_imanagerReleaseImage(imanager *im, vimage *image, const vchar *tag)
{
  int owned;

  vdebugIF((!image || !tag), vexGenerate(vexGetArgNullClass(), vexMESSAGE,
          "release image: NULL argument(s)!", vexERRNO, 0, vexNULL));

  if (image!=im->genericImage)
  {
    owned = vFALSE;
    if (im->active && im->active!=im->global)
      owned = istoreReleaseImage((istore*)im->active, tag);

    if (!owned)
    {
      owned = istoreReleaseImage((istore*)im->global, tag);
      if (!owned) 
	{
	  vdebugWarn("release image: %s -- not owned!\n", (char*)tag);
	  imanagerGenerateThingNotFoundException
	    ("release image: image not found in any registered store!");
	}
    }
  }

  return;
}




  static void
_imanagerReleaseImageGlobal(imanager *im, vimage *image, const vchar *tag)
{
  int owned;

  vdebugIF((!image || !tag), vexGenerate(vexGetArgNullClass(), vexMESSAGE,
          "release global image: NULL argument(s)!", vexERRNO, 0, vexNULL));


  if (image!=im->genericImage)
  {
    owned = istoreReleaseImage((istore*)im->global, tag);
    if (!owned)
      imanagerGenerateThingNotFoundException
	("release global image: image not found in global store!");
  }

  return;
}




 static vimage*
_imanagerRetrieveImageMask(imanager *im, const vchar *tag)
{
  vimage *mask;

  vdebugIF((!tag), vexGenerate(vexGetArgNullClass(), vexMESSAGE,
          "retrieve image mask: NULL tag!", vexERRNO, 0, vexNULL));

  if (im->masks)
    mask = istoreRetrieveImage((istore*)im->masks, tag);
  else
    mask = NULL;

  return mask;
}




 static int
_imanagerGetNumberOfImageUsers(imanager *im, vresource res, const vchar *tag)
{
  register istore *store;


  vdebugIF((!tag), vexGenerate(vexGetArgNullClass(), vexMESSAGE,
          "get number users: NULL tag!", vexERRNO, 0, vexNULL));

  store = (istore*)_imanagerResourceToStore(im, res);

  return istoreCountNumberOfUsers(store, tag);
}




 static vresource
_imanagerMakeImageStore(imanager *im, vresource parent)
{
  vresource		res;
  register istore	*store;

  vdebugIF((parent==vresourceNULL), vexGenerate(vexGetArgNullClass(), 
           vexMESSAGE, "make store: NULL resource!", vexERRNO, 0, vexNULL));

  if (vresourceTestGet(parent, name_Images, &res))
    {
      imanagerRegisterAsImageStore(im, res);
    }
  else
    {
      res = vresourceCreate(parent, name_Images, vresourceDICT);
      store = istoreCreateEditable();
      istoreSetRes(store, res);

      tllistAppendItem(im->stores, store);
      im->active    = store;
      im->activeRes = res;
    }

  return res;
}




 static void
_imanagerNukeImageStoreIfExists(imanager *im, vresource res)
{
  vdebugIF((res==vresourceNULL), vexGenerate(vexGetArgNullClass(), 
           vexMESSAGE, "nuke store: NULL resource!", vexERRNO, 0, vexNULL));

  if (imanagerLookupStore(im, res))
    imanagerUnRegisterAsImageStore(im, res);

  vresourceRemoveIfExists(res, vresourceTAG_NULL);
  return;
}

 


 static void
_imanagerSaveImageStore(imanager *im, vresource res)
{
  istore *store;

  /* can never save to the global store */
  if (res==vresourceNULL)
    vexGenerate(vexGetArgClass(), vexMESSAGE, "save store: cannot save "
		"to the global image store!", vexERRNO, 0, vexNULL);


  /* the image manager's only interface to stores is via resources,
   * so a valid store always has a dict resource already associated */
  store = (istore*)_imanagerResourceToStore(im, res);
  istoreStore(store, res);
  return;
}




 static const vchar *
_imanagerGetUndoActionName(register imanagerUndoOp op)
{
  register const vchar	*title;

  switch (op)
    {
      case imanagerUNDO_OP_ADD: 
        title = name_AddImage; 
	break;
      case imanagerUNDO_OP_REMOVE: 
        title = name_RemoveImage; 
	break;
      default:
        title = name_PasteImages; 
    }
  return title;
}




 static void
_imanagerSetUndoActionNamer(imanager *im, imanagerUndoActionNamer namer)
{
  vdebugIF((!namer), vexGenerate(vexGetArgNullClass(), vexMESSAGE,
           "undo action namer: NULL namer proc!", vexERRNO, 0, vexNULL));
  imanagerGlobals()->undoNamer = namer;
  return;
}




 static void
_imanagerPreloadImageStore(imanager *im, vresource res)
{
  istore *store = (istore*)_imanagerResourceToStore(im, res);
  istorePreloadImages(store);
  return;
}




 static void
_imanagerDump(register imanager *im, register FILE *fp)
{
#if vdebugDEBUG
  if (!fp)
    fp = vdebugGetInfoStream();

  fprintf(fp, "\n  image management:\n");
  fprintf(fp, "     generic-image: %p\n", im->genericImage);
  fprintf(fp, "     global-image-store: %p\n", im->global);
  fprintf(fp, "     active-image-store: %p\n", im->active);
  fprintf(fp, "     active-image-store-resource: %ld\n", im->activeRes);
  fprintf(fp, "     global-masks: %p\n", im->masks);
  fprintf(fp, "     reserved: %p\n", im->reserved);
  fprintf(fp, "     registered-stores: %p\n", im->stores);

  if (im->stores)
    {
      register istore 		*store;
      register tllistIterator   *iter;
      iter = tllistCreateIterator(im->stores);
      tllistIteratorStartOver(iter);
      while (tllistIteratorMore(iter))
	{
	  store = (istore*)tllistIteratorNextItem(iter);
	  istoreDump(store, fp, vTRUE);
	}
      tllistDestroyIterator(im->stores, iter);
    }
#endif
  return;
}




 static void
_imanagerRegisterClasses(void)
{
  register imanagerClass 	  *readClas;
  register imanagerEditableClass  *editClas;

  /* register with class manager */
  readClas = vclassSpawn(vinstanceGetDefaultClass(), sizeof(imanagerClass));
  vclassSetNameScribed(readClas, vcharScribeLiteral("image-manager"));
  vclassSetObjectSize(readClas, sizeof(imanager));

  /* inherited */
  vclassSet(readClas, vinstanceINIT,    _imanagerInit);
  vclassSet(readClas, vinstanceDESTROY, _imanagerDestroy);

  /* our messages */
  vclassSet(readClas, imanagerSTARTUP, _imanagerStartup);
  vclassSet(readClas, imanagerDUMP, _imanagerDump);
  vclassSet(readClas, imanagerSET_TAG, _imanagerSetTag);
  vclassSet(readClas, imanagerREGISTER_STORE, _imanagerRegisterStore);
  vclassSet(readClas, imanagerUNREGISTER_STORE, _imanagerUnRegisterStore);
  vclassSet(readClas, imanagerUNREGISTER_STORE_UNBALANCED, _imanagerUnRegisterUnbalancedStore);
  vclassSet(readClas, imanagerGET_ACTIVE_STORE, _imanagerGetActiveStore);
  vclassSet(readClas, imanagerSET_ACTIVE_STORE, _imanagerSetActiveStore);
  vclassSet(readClas, imanagerGET_STORE, _imanagerResourceToStore);
  vclassSet(readClas, imanagerRETRIEVE_IMAGE, _imanagerRetrieveImage);
  vclassSet(readClas, imanagerRETRIEVE_GLOBAL_IMAGE, _imanagerRetrieveImageGlobal);
  vclassSet(readClas, imanagerRELEASE_IMAGE, _imanagerReleaseImage);
  vclassSet(readClas, imanagerRELEASE_GLOBAL_IMAGE, _imanagerReleaseImageGlobal);
  vclassSet(readClas, imanagerRETRIEVE_MASK, _imanagerRetrieveImageMask);
  vclassSet(readClas, imanagerLOAD_STORE, _imanagerLoadImageStore);
  vclassSet(readClas, imanagerCOUNT_IMAGE_USERS, _imanagerGetNumberOfImageUsers);

  /* save */
  imanagerGlobals()->defaultClass = readClas;


  /* register with class manager */
  editClas = vclassSpawn(readClas, sizeof(imanagerEditableClass));
  vclassSetNameScribed(editClas, vcharScribeLiteral("editable-image-manager"));
  vclassSetObjectSize(editClas, sizeof(imanager));

  /* inherited */
  vclassSet(editClas, imanagerLOAD_STORE, _imanagerLoadImageStoreEditable);

  /* our messages */
  vclassSet(editClas, imanagerMAKE_STORE, _imanagerMakeImageStore);
  vclassSet(editClas, imanagerSAVE_STORE, _imanagerSaveImageStore);
  vclassSet(editClas, imanagerNUKE_STORE, _imanagerNukeImageStoreIfExists);
  vclassSet(editClas, imanagerADD_IMAGE_2STORE, _imanagerAddImageToStoreUndoable);
  vclassSet(editClas, imanagerREMOVE_IMAGE_FROM_STORE, _imanagerRemoveImageFromStoreUndoable);
  vclassSet(editClas, imanagerPASTE_IMAGES_2STORE, _imanagerPasteImagesIntoStoreUndoable);
  vclassSet(editClas, imanagerPASTE_RIMAGES_2STORE, _imanagerPasteResourceImagesIntoStoreUndoable);
  vclassSet(editClas, imanagerPRELOAD_STORE, _imanagerPreloadImageStore);
  vclassSet(editClas, imanagerSET_UNDO_NAMER, _imanagerSetUndoActionNamer);

  /* save */
  imanagerGlobals()->defaultEditableClass = editClas;


  /* save a default undo-namer */
  imanagerGlobals()->undoNamer = _imanagerGetUndoActionName;
  imanagerGlobals()->defaultAddRemImageActionClass = NULL;
  imanagerGlobals()->defaultPasteImagesActionClass = NULL;

  return;
}




 static void
_imanagerGlobalShutdown(void)
{
  if (imanagerPool)
    vpoolDestroy(imanagerPool);
  return;
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

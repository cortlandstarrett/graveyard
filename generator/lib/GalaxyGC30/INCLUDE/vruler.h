/* $Id: vruler.h,v 1.48 1997/09/19 22:57:24 robert Exp $ */

/************************************************************

    vruler.h
    C Interface to the Ruler dialog item

    (c) Copyright Visix Software  1991
    All rights reserved

************************************************************/

#ifndef vrulerINCLUDED
#define vrulerINCLUDED 1

#ifndef  vportINCLUDED
#include <vport.h>		/* for v*HEADER */
#endif

#ifndef  vstrINCLUDED
#include vstrHEADER
#endif

#ifndef  vdialogINCLUDED
#include vdialogHEADER
#endif

#ifndef  vpoolINCLUDED
#include vpoolHEADER
#endif


vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * * * * * * * * * * PUBLIC CONSTANT DEFINITIONS * * * * * * * * * *
 */

/*
 *  Constants for message for ruler notification function
 */

enum {
    vrulerITEM_SELECT		= 1,
    vrulerITEM_DOUBLE        	= 2,
    vrulerREDRAW_ALL     	= 3,	/* obsolete */
    vrulerITEM_WILL_REMOVE	= 4,
    vrulerITEM_REMOVE     	= 5,
    vrulerCOLUMN_MOVE_START  	= 6,	/* archaic  */
    vrulerCOLUMN_MOVE_END  	= 7,	/* archaic  */
    vrulerITEM_MOVE_START	= 6,
    vrulerITEM_MOVE_END		= 7,
    vrulerITEM_RESIZE_START	= 8,
    vrulerITEM_RESIZE_END	= 9,
    vrulerSCROLL_START		= 10,
    vrulerSCROLL_END		= 11,
    vrulerRESIZE		= 12,
    vrulerITEM_ADD		= 13,
    vrulerITEM_HIDE		= 14,
    vrulerITEM_SHOW		= 15
};

/*
 * Values for 'dragOff' operation
 */

enum {
    vrulerDRAG_OFF_REMOVES	= 0,
    vrulerDRAG_OFF_HIDES
};

#define vruler_HiliteItem   (_vrulerPredefs[_vruler_HiliteItem])
#define vruler_Arrangable   (_vrulerPredefs[_vruler_Arrangable])

/*
 * * * * * * * * * * PUBLIC TYPE DEFINITIONS * * * * * * * * * *
 */

typedef struct vruler		vruler;
typedef struct vrulerClass	vrulerClass;
typedef struct vrulerItem	vrulerItem;
typedef struct vrulerItemClass	vrulerItemClass;
typedef struct vrulerIterator   vrulerIterator;

typedef void (*vrulerNoteProc)(
    vruler 		*ruler,
    vevent 		*event,
    vrulerItem 		*rulerItem,
    int 		message
    );

/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */

void vrulerStartup(void);


/* Ruler Class Functions */

vrulerClass *vrulerGetDefaultClass(void);

vrulerItemClass *vrulerGetDefaultItemClass(void);

/* Initialization and allocation */

vruler *vrulerCreate(void);

vruler *vrulerCreateOfClass(
    vrulerClass	*clas
    );
    
vruler *vrulerClone(
    vruler	    	*ruler
    );

void vrulerCopy(
    vruler	    	*ruler,
    vruler	    	*target
    );

void vrulerCopyInit(
    vruler	    	*ruler,
    vruler	    	*target
    );

void vrulerInit(
    vruler	    	*ruler
    );

void vrulerInitOfClass(
    vruler		*ruler,
    vrulerClass	        *clas
    );

void vrulerDestroy(
    vruler	    	*ruler   
    );

vruler *vrulerLoad(
    vresource		resource
    );

void vrulerLoadInit(
    vruler		*ruler,
    vresource		resource
    );

void vrulerStore(
    vruler		*ruler,
    vresource		resource
    );

/* Ruler Operations */

void vrulerInstallItem(
    vruler              *ruler,
    vrulerItem          *rulerItem
    );

void vrulerRemoveItem(
    vruler              *ruler,
    vrulerItem          *rulerItem
    );

vrulerItem *vrulerFindItem(
    vruler		*ruler,
    const vname		*name
    );

int vrulerGetItemCount(
    vruler		*ruler
    );

vrulerItem *vrulerGetItemAt(
    vruler              *ruler,
    int			index
    );

void vrulerCompact(
    vruler              *ruler
    );

/* Ruler attribute modification */

void vrulerSetData(
    vruler		*ruler,
    void		*data
    );

void vrulerSetArrangeable(
    vruler		*ruler,
    int			canArrange
    );

void vrulerSetNotify(
    vruler              *ruler,
    vrulerNoteProc      noteProc
    );

void vrulerSetScrollOffset(
    vruler		*ruler,
    int			offset
    );

void vrulerSetStickyEdges(
    vruler		*ruler,
    int			sticky
    );

void vrulerSetSpacing(
    vruler		*ruler,
    int			spacing
    );

void vrulerSetDragOff(
    vruler		*ruler,
    int			dragOffOp
    );

/* Ruler attribute access */

vrulerClass *vrulerGetClass(
    vruler          	*ruler
    );

void *vrulerGetData(
    vruler              *ruler
    );

vbool vrulerGetArrangeable(
    vruler              *ruler
    );

vrulerNoteProc vrulerGetNotify(
    vruler              *ruler
    );

int vrulerGetScrollOffset(
    vruler              *ruler
    );

vbool vrulerGetStickyEdges(
    vruler		*ruler
    );

int vrulerGetSpacing(
    vruler		*ruler
    );

int vrulerGetDragOff(
    vruler		*ruler
    );

/* Ruler Iterators */

void vrulerInitIterator(
    vrulerIterator      *iterator,
    vruler		*ruler
    );

vbool vrulerNextIterator(
    vrulerIterator	*iterator
    );

void vrulerDestroyIterator(
    vrulerIterator	*iterator
    );

vrulerItem *vrulerGetIteratorItem(
    vrulerIterator	*iterator
    );

/* Ruler Item Operations */

vrulerItem *vrulerCreateItem(void);

vrulerItem *vrulerCreateItemOfClass(
    vrulerItemClass	*clas
    );
    
vrulerItem *vrulerCloneItem(
    vrulerItem		*rulerItem
    );

void vrulerCopyItem(
    vrulerItem		*rulerItem,
    vrulerItem		*target
    );

void vrulerCopyInitItem(
    vrulerItem		*rulerItem,
    vrulerItem		*target
    );

void vrulerInitItem(
    vrulerItem		*rulerItem
    );

void vrulerInitItemOfClass(
    vrulerItem		*rulerItem,
    vrulerItemClass	*clas
    );

void vrulerDestroyItem(
    vrulerItem		*rulerItem
    );

vrulerItem *vrulerLoadItem(
    vresource		resource
    );

void vrulerLoadInitItem(
    vrulerItem		*rulerItem,
    vresource		resource
    );

void vrulerStoreItem(
    vrulerItem		*rulerItem,
    vresource		resource
    );

void vrulerHideItem(
    vrulerItem		*rulerItem
    );

void vrulerShowItem(
    vrulerItem		*rulerItem
    );

vbool vrulerItemIsVisible(
    vrulerItem		*rulerItem
    );

int vrulerGetItemIndex(
    vrulerItem		*rulerItem
    );
	
/* Ruler Item attribute modification */

void vrulerSetItemData(
    vrulerItem          *rulerItem,
    void		*data
    );

void vrulerSetItemName(
    vrulerItem          *rulerItem,
    const vchar		*name
    );

void vrulerSetItemNameScribed(
    vrulerItem          *rulerItem,
    vscribe		*scribe
    );

void vrulerSetItemTag(
    vrulerItem		*rulerItem,
    const vname		*tag
    );

void vrulerSetItemWidth(
    vrulerItem          *rulerItem,
    int                 width
    );

void vrulerSetItemMinWidth(
    vrulerItem          *rulerItem,
    int                 minWidth
    );

void vrulerSetItemMaxWidth(
    vrulerItem          *rulerItem,
    int                 maxWidth
    );

vbool vrulerSetItemOffset(
    vrulerItem          *rulerItem,
    int                 offset
    );

void vrulerSetItemCanRemove(
    vrulerItem          *rulerItem,
    int  /* vbool */    canRemove
    );

void vrulerSetItemHilite(
    vrulerItem          *rulerItem,
    int /* vbool */     hilite
    );

void vrulerSetItemResizable(
    vrulerItem          *rulerItem,
    int /* vbool */     resizable
    );

void vrulerSetItemOwned(
    vrulerItem          *rulerItem,
    int /* vbool */     owned
    );

/* Ruler Item attribute access */

vrulerItemClass *vrulerGetItemClass(
    vrulerItem          *rulerItem
    );

void *vrulerGetItemData(
    vrulerItem          *rulerItem
    );

vchar *vrulerGetItemName(
    vrulerItem          *rulerItem
    );

const vname *vrulerGetItemTag(
    vrulerItem		*rulerItem
    );

int vrulerGetItemWidth(
    vrulerItem          *rulerItem
    );

int vrulerGetItemMinWidth(
    vrulerItem          *rulerItem
    );

int vrulerGetItemMaxWidth(
    vrulerItem          *rulerItem
    );

int vrulerGetItemOffset(
    vrulerItem          *rulerItem
    );
	
vbool vrulerGetItemCanRemove(
    vrulerItem          *rulerItem
    );

vbool vrulerGetItemHilite(
    vrulerItem          *rulerItem
    );

vbool vrulerGetItemResizable(
    vrulerItem          *rulerItem
    );

vbool vrulerGetItemOwned(
    vrulerItem          *rulerItem
    );

/* Other */

void vrulerNotify(
    vruler		*ruler,
    vevent		*event,
    vrulerItem		*item,
    int			message
    );

vdialogItem *vrulerGetItem(
    vruler		*ruler
    );

vruler *vrulerGetItemOwner(
    vrulerItem		*rulerItem
    );

void vrulerInvalItem(
    vrulerItem		*rulerItem
    );

/* Deprecated Functions */

vrulerItem *vrulerAddItem(
    vruler              *ruler
    );

void vrulerSetArrangable(
    vruler		*ruler,
    int			canArrange
    );

vbool vrulerGetArrangable(
    vruler              *ruler
    );


/*
 * * * * * * * * * * PRIVATE CONSTANT DEFINITIONS * * * * * * * * * *
 */

/*
 * Values for the 'flags' field in the vrulerItem structure
 */

enum {
    _vrulerCAN_REMOVE	        = 0x0002,
    _vrulerHILITE		= 0x0004,
    _vrulerREDRAW		= 0x0008,
    _vrulerRESIZABLE		= 0x0010,
    _vrulerOWN_NAME		= 0x0020,
    _vrulerOWNED		= 0x0040,
    _vrulerHIDDEN		= 0x0080,
    _vrulerMARKED		= 0x0100,
    _vrulerSTRETCH_ITEM		= 0x0200
};

/*
 * Global ruler strings
 */

enum {
    _vruler_HiliteItem,
    _vruler_Arrangable,
    _vruler_Count
};

/*
 * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * *
 */

/* 
 * vrulerItem
 */

struct vrulerItem {
    vloadable		object;
    vruler	 	*owner;
    vrulerItem 		*next;
    vstr         	*name;
    vrect         	rect;
    int           	minW;
    int           	maxW;
    int        	  	flags;
    void	  	*data;
};

/* 
 * vruler
 */

struct vruler {
    vdialogItem	    	item;
    int             	numItems;
    int		    	scrollOffset;
    int		    	spacing;
    vrulerItem	    	*rulerItems;
    vrulerItem	    	*hiddenItems;
    vrulerItem	    	*hiliteItem;
    vbool	    	arrangable;
    vbool	    	stickyEdges;
    vbyte		dragOffOp;
    vbyte		deferCompact;

    vrulerNoteProc	noteProc;
};


struct vrulerIterator {
    vruler		*ruler;
    vrulerItem		*item;
    int			stage;
};

/* vruler and ruler item  class */

#define vrulerItemCLASS(SUPER, ITEM)				            \
    vloadableCLASS(SUPER, ITEM);               			   	    \
    vclassMETHOD(vrulerSET_ITEM_WIDTH,      (ITEM *item, int width));	    \
    vclassMETHOD_RET(vrulerSET_ITEM_OFFSET, vbool, (ITEM *item, int offset))

struct vrulerItemClass {
    vrulerItemCLASS(vrulerItemClass, vrulerItem);
};

#define vrulerCLASS(SUPER, RULER, ITEM)	    _vrulerCLASS(SUPER, RULER, ITEM, \
						     vrulerNoteProc)

#define _vrulerCLASS(SUPER, RULER, ITEM, NOTEPROC)		            \
    vdialogITEM_CLASS(SUPER, RULER, NOTEPROC);			            \
    vclassVARIABLE(vrulerBORDER_INSET,       short);			    \
    vclassMETHOD_RET(vrulerADD_ITEM, ITEM *, (RULER *ruler));		    \
    vclassMETHOD(vrulerINSTALL_ITEM,         (RULER *ruler, ITEM *item));   \
    vclassMETHOD(vrulerREMOVE_ITEM,          (RULER *ruler, ITEM *item));   \
    vclassMETHOD(vrulerCOMPACT,	             (RULER *ruler));               \
    vclassMETHOD(vrulerDRAW_ITEM,     (RULER *ruler, ITEM *item, vrect *r));\
    vclassMETHOD(vrulerDRAW_ITEM_BORDER,				    \
				 (RULER *ruler, ITEM *item, vrect *bounds));\
    vclassMETHOD(vrulerDRAW_ITEM_WITH,     (RULER *ruler, ITEM *item, vrect *r, vdrawcontext *context));\
    vclassMETHOD(vrulerDRAW_ITEM_BORDER_WITH,				    \
				 (RULER *ruler, ITEM *item, vrect *bounds, vdrawcontext *context));\
    vclassMETHOD(vrulerNOTIFY,						    \
			(RULER *ruler, vevent *event, ITEM *item, int message))

struct vrulerClass {
    _vrulerCLASS(vrulerClass, vruler, vrulerItem, vrulerNoteProc);
};

/*
 * * * * * * * * * * PRIVATE FUNCTION PROTOTYPES * * * * * * * * * *
 */

/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * *
 */

#define vrulerGetItem(r)		(vportBASE_OBJECT((r), item))
#define _vrulerGetItemLoadable(i)		(vportBASE_OBJECT((i), object))

#define vrulerCreateOfClass(c)	\
	((vruler *) vdialogCreateItemOfClass((vdialogItemClass *) (c)))
#define vrulerCreate()	   vrulerCreateOfClass(vrulerGetDefaultClass())
#define vrulerClone(d)     ((vruler *) vdialogCloneItem(vrulerGetItem(d)))
#define vrulerInitOfClass(e,c)	\
	vdialogInitItemOfClass(vrulerGetItem(e), (vdialogItemClass *) (c))
#define vrulerInit(e)	       vrulerInitOfClass(e, vrulerGetDefaultClass());
#define vrulerCopyInit(c,t)    \
	vdialogCopyInitItem(vrulerGetItem(c), vrulerGetItem(t))
#define vrulerCopy(c,t)	\
        vdialogCopyItem(vrulerGetItem(c), vrulerGetItem(t))
#define vrulerLoad(r)          ((vruler *) vdialogLoadItem(r))
#define vrulerLoadInit(c,r)    vdialogLoadInitItem(vrulerGetItem(c), r)
#define vrulerStore(c,r)       vdialogStoreItem(vrulerGetItem(c), r)
#define vrulerDestroy(d)	\
	vdialogDestroyItem(vrulerGetItem(d))


#define vrulerCreateItemOfClass(c)   \
	((vrulerItem *) vloadableCreateOfClass((vloadableClass *)(c)))
#define vrulerCreateItem()	     \
	vrulerCreateItemOfClass(vrulerGetDefaultItemClass())
#define vrulerCloneItem(i)	     \
	((vrulerItem *) vloadableClone(_vrulerGetItemLoadable(i)))
#define vrulerInitItemOfClass(i, c)  \
	vloadableInitOfClass(_vrulerGetItemLoadable(i), (vloadableClass*)(c))
#define vrulerInitItem(i)	\
	vrulerInitItemOfClass(i, vrulerGetDefaultItemClass())
#define vrulerCopyInitItem(e,t) vloadableCopyInit(_vrulerGetItemLoadable(e),  \
						_vrulerGetItemLoadable(t))
#define vrulerCopyItem(e,t)	vloadableCopy(_vrulerGetItemLoadable(e), \
					    _vrulerGetItemLoadable(t))
#define vrulerLoadItem(r)       ((vrulerItem *) vloadableLoad(r))
#define vrulerLoadInitItem(e,r) vloadableLoadInit(_vrulerGetItemLoadable(e), r)
#define vrulerStoreItem(e, r)	vloadableStore(_vrulerGetItemLoadable(e), r)
#define vrulerDestroyItem(e)	\
	vloadableDestroy(_vrulerGetItemLoadable(e))


#define vrulerGetClass(d)	\
	((vrulerClass *) vdialogGetItemClass(vrulerGetItem(d)))
#define vrulerGetItemClass(i)	\
	((vrulerItemClass *) vloadableGetClass(_vrulerGetItemLoadable(i)))

#define vrulerSetArrangable(r,p)	((r)->arrangable = (p))
#define vrulerGetArrangable(r)		((r)->arrangable)
#define vrulerSetArrangeable(r,p)	((r)->arrangable = (p))
#define vrulerGetArrangeable(r)		((r)->arrangable)
#define vrulerGetData(e)     	 	vdialogGetItemData(vrulerGetItem(e))
#define vrulerGetScrollOffset(r)        ((r)->scrollOffset)
#define vrulerGetStickyEdges(r)         ((r)->stickyEdges)
#define vrulerSetSpacing(r,s)		((r)->spacing = (s))
#define vrulerGetSpacing(r)             ((r)->spacing)
#define vrulerSetDragOff(r,s)		((r)->dragOffOp = (s))
#define vrulerGetDragOff(r)             ((r)->dragOffOp)

#define vrulerSetItemName(i, n)	    vrulerSetItemNameScribed(i, vcharScribe(n))

#define vrulerSetItemMinWidth(r,w)	((r)->minW = (w))
#define vrulerSetItemMaxWidth(r,w)	((r)->maxW = (w))
#define vrulerSetItemData(r,d)		((r)->data = (d))

#define vrulerSetItemCanRemove(r,c)  {				\
		if (c) ((r)->flags |=  _vrulerCAN_REMOVE);	\
                else    (r)->flags &= ~_vrulerCAN_REMOVE;	\
                }
#define vrulerSetItemResizable(r,v)  {				\
		if (v) ((r)->flags |=  _vrulerRESIZABLE);	\
                else    (r)->flags &= ~_vrulerRESIZABLE;	\
                }
#define vrulerSetItemOwned(r,v)  {				\
		if (v) ((r)->flags |=  _vrulerOWNED);		\
                else    (r)->flags &= ~_vrulerOWNED;		\
                }

#define vrulerGetItemName(r)		((r)->name)
#define vrulerGetItemData(r)		((r)->data)
#define vrulerGetItemWidth(r)		((r)->rect.w)
#define vrulerGetItemMinWidth(r)	((r)->minW)
#define vrulerGetItemMaxWidth(r)	((r)->maxW)
#define vrulerGetItemOffset(r)		((r)->rect.x)
#define vrulerGetItemCanRemove(r)	(((r)->flags & _vrulerCAN_REMOVE) != 0)
#define vrulerGetItemHilite(r)		(((r)->flags & _vrulerHILITE) != 0)
#define vrulerGetItemResizable(r)	(((r)->flags & _vrulerRESIZABLE) != 0)
#define vrulerGetItemOwned(r)		(((r)->flags & _vrulerOWNED) != 0)
#define vrulerGetItemTag(i)    	vloadableGetTag(_vrulerGetItemLoadable(i))
#define vrulerSetItemTag(i, t)	vloadableSetTag(_vrulerGetItemLoadable(i), t)
#define vrulerItemIsVisible(i)		(((i)->flags & _vrulerHIDDEN) == 0)

#define vrulerGetItemOwner(r)		((r)->owner)
#define vrulerGetItemCount(r)		((r)->numItems)

#define vrulerSetNotify(r,n)    	((r)->noteProc = (n))
#define vrulerGetNotify(e)  	   	((e)->noteProc)

#define vrulerDestroyIterator(i)	
#define vrulerGetIteratorItem(i)	((i)->item)

/*
 * * * * * * * * * * PRIVATE FUNCTION MESSAGE DEFINITIONS * * * * * * * * * *
 */

#define vrulerAddItem(r)	\
	vclassSend(vrulerGetClass(r), vrulerADD_ITEM, (r))

#define vrulerInstallItem(r,i)	\
	vclassSend(vrulerGetClass(r), vrulerINSTALL_ITEM, (r, i))

#define vrulerRemoveItem(r,i)	\
	vclassSend(vrulerGetClass(r), vrulerREMOVE_ITEM, (r, i))

#define vrulerCompact(r)	\
	vclassSend(vrulerGetClass(r), vrulerCOMPACT, (r))

#define vrulerNotify(r,e,i,m)	\
	vclassSend(vrulerGetClass(r), vrulerNOTIFY, (r, e, i, m))

#define vrulerSetData(e, d)	\
	vclassSend(vrulerGetClass(e), vdialogSET_ITEM_DATA, (e, d))

#define vrulerSetItemWidth(i,o)	\
	vclassSend(vrulerGetItemClass(i), vrulerSET_ITEM_WIDTH, (i, o))

#define vrulerSetItemOffset(i,o)    \
	vclassSend(vrulerGetItemClass(i), vrulerSET_ITEM_OFFSET, (i, o))

/*
 * * * * * * * * * RULER GLOBAL VARIABLES * * * * * * * * * *
 */

extern vportLINK const vchar * _vrulerPredefs[];

vportEND_CPLUSPLUS_EXTERN_C

#endif /* #ifndef vrulerINCLUDED */


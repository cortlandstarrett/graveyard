/* $Id: vpalette.h,v 1.39 1997/10/02 20:59:48 robert Exp $ */

/************************************************************

    vpalette.h

    C Interface file for the palette item

    (c) Copyright Visix Software Inc.
    All rights reserved

************************************************************/

#ifndef vpaletteINCLUDED
#define vpaletteINCLUDED 1

#ifndef  vportINCLUDED		/* for v*HEADER */
#include <vport.h>
#endif

#ifndef  vstdINCLUDED		/* for vbool */
#include vstdHEADER
#endif

#ifndef  vimageINCLUDED
#include vimageHEADER
#endif

#ifndef  vlistviewINCLUDED
#include vlistviewHEADER
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * * * * * * * * * CONSTANTS AND MACRO DEFINITIONS * * * * * * * * * *
 */

/* Values for 'flags' field in palette structure */

enum {
    _vpaletteNOTIFY_ON_BUTTON_UP         = 0x0001,
    _vpaletteAUTO_ARRANGE                = 0x0002,
    _vpaletteREARRANGE	                 = 0x0004
};

/* Values for 'flags' field in palette item structure */

enum {
    _vpaletteITEM_DISABLED		= 0x0001,
    _vpaletteITEM_IMAGE_SHARED		= 0x0002,
    _vpaletteITEM_TITLE_SHARED		= 0x0004
};

/*
 * * * * * * * * * TYPE AND STRUCTURE DEFINITIONS * * * * * * * * * *
 */

typedef struct vpalette		   vpalette;
typedef struct vpaletteClass	   vpaletteClass;

typedef struct vpaletteItem	   vpaletteItem;
typedef struct vpaletteItemClass   vpaletteItemClass;

typedef void (*vpaletteItemNotifyProc)( vpalette *palette,
					vpaletteItem *item );

typedef void (*vpaletteNoteProc)(vpalette *palette, vevent *event);
 
/*
 * * * * * * * * * FUNCTION PROTOTYPES * * * * * * * * * *
 */

void vpaletteStartup(void);


/* Palette operations */

vpaletteClass *vpaletteGetDefaultClass(
    void
    );

vpaletteClass *vpaletteGetClass(
    vpalette			*palette
    );

vlistview *vpaletteGetListview( 
    vpalette			*palette
    );

vdialogItem *vpaletteGetItem(
    vpalette			*palette
    );

vpalette *vpaletteCreate(
    void
    );

vpalette *vpaletteCreateOfClass(
    vpaletteClass        	*clas
    );

void vpaletteInit(
    vpalette			*palette
    );

void vpaletteInitOfClass(
    vpalette			*palette,
    vpaletteClass        	*clas
    );

void vpaletteDestroy(
    vpalette			*palette
    );

vpalette *vpaletteClone(
    vpalette			*palette
    );

void vpaletteCopy(
    vpalette			*from,
    vpalette			*to
    );

void vpaletteCopyInit(
    vpalette			*from,
    vpalette			*to
    );

vpalette *vpaletteLoad(
    vresource			 resource
    );

void vpaletteLoadInit(
    vpalette			*palette,
    vresource			 resource
    );

void vpaletteStore(
    vpalette			*palette,
    vresource			 resource
    );

void vpaletteInsertItem( 
    vpalette			*palette,
    int				 index,
    vpaletteItem	   	*item
    );

void vpaletteAppendItem(
    vpalette			*palette,
    vpaletteItem	   	*item
    );

vpaletteItem *vpaletteRemoveItem( 
    vpalette			*palette,
    vpaletteItem		*item
    );

vpaletteItem *vpaletteRemoveItemIndex( 
    vpalette			*palette,
    int				 index
    );

void vpaletteSetSelection(
    vpalette			*palette,
    vpaletteItem	   	*item
    );

vpaletteItem *vpaletteGetSelection(
    vpalette			*item
    );

vpaletteItem *vpaletteFindItem( 
    vpalette			*palette,
    const vname	   		*tag
    );

int vpaletteGetItemIndex( 
    vpalette 			*palette, 
    vpaletteItem 		*item 
    );

void vpaletteSetItemIndex(
    vpalette			*palette,
    vpaletteItem		*item,
    int				 index
    );

vpaletteItem *vpaletteGetItemAt(
    vpalette			*palette,
    int			 	 index
    );

vpaletteItem *vpaletteReplaceItemAt(
    vpalette			*palette,
    int			 	 index,
    vpaletteItem   		*item
    );

void vpaletteSetData(
    vpalette			*palette,
    void			*data
    );

void *vpaletteGetData(
    vpalette			*palette
    );

void vpaletteSetImageSize( 
    vpalette 			*palette, 
    int 		 	 width, 
    int 		 	 height
    );

int vpaletteGetImageWidth(
    vpalette			*palette
    );

int vpaletteGetImageHeight( 
    vpalette			*palette
    );

void vpaletteSetColumns( 
    vpalette			*palette,
    int			 	 numCols
    );

int vpaletteGetColumnCount(
    vpalette			*palette
    );

int vpaletteGetRowCount(
    vpalette			*palette
    );

int vpaletteGetItemCount( 
    vpalette			*palette
    );

void vpaletteSetNotifyOnButtonUp(
    vpalette	 		*palette,
    int			 	 value
    );

void vpaletteSetAutoArrange(
    vpalette                    *palette,
    int                         autoArrange
    );

void vpaletteSetRearrange(
    vpalette                    *palette,
    int                         rearrange
    );

vbool vpaletteGetNotifyOnButtonUp(
    vpalette			*palette 
    );
    
vbool vpaletteGetAutoArrange(
    vpalette			*palette 
    );

vbool vpaletteGetRearrange(
    vpalette			*palette 
    );
    
int vpaletteGetClickCount( 
    vpalette		      	*palette 
    );


/* Palette Item Operations */

vpaletteItemClass *vpaletteGetDefaultItemClass(void);

vpaletteItemClass *vpaletteGetItemClass(
    vpaletteItem		*item
    );

vobject *vpaletteGetItemObject(
    vpaletteItem		*item
    );

vloadable *vpaletteGetItemLoadable(
    vpaletteItem		*item
    );

vpaletteItem *vpaletteCreateItem(
    void
    );

vpaletteItem *vpaletteCreateItemOfClass(
    vpaletteItemClass		*clas
    );

void vpaletteInitItem(
    vpaletteItem		*item
    );

void vpaletteInitItemOfClass(
    vpaletteItem		*item,
    vpaletteItemClass		*clas
    );

void vpaletteDestroyItem(
    vpaletteItem	   	*item
    );

vpaletteItem *vpaletteLoadItem(
    vresource			 resource
    );

vpaletteItem *vpaletteCloneItem( 
    vpaletteItem		*item 
    );

void vpaletteNotifyItem(
    vpaletteItem		*item
    );

void vpaletteSetItemTag(
    vpaletteItem     		*item,
    const vname			*tag
    );

void vpaletteSetItemData(
    vpaletteItem		*item,
    void			*data
    );

void vpaletteSetItemDisabled(
    vpaletteItem		*item,
    int			 	 value
    );

void vpaletteSetItemImage(
    vpaletteItem		*item,
    vimage			*image
    );

void vpaletteSetItemImageShared(
    vpaletteItem		*item,
    vimage			*image
    );

void vpaletteSetItemImageOwned(
    vpaletteItem		*item,
    vimage			*image
    );

void vpaletteSetItemNotify(
    vpaletteItem		*item,
    vpaletteItemNotifyProc	 notify
    );

void vpaletteSetItemTitleScribed(
    vpaletteItem		*item,
    vscribe			*scribe
    );

vpalette *vpaletteGetItemPalette(
    vpaletteItem		*item
    );

const vname *vpaletteGetItemTag(
    vpaletteItem    		*palette
    );

void *vpaletteGetItemData(
    vpaletteItem		*item 
    );

vbool vpaletteGetItemDisabled(
    vpaletteItem		*item
    );

vimage *vpaletteGetItemImage(
    vpaletteItem		*item
    );

vpaletteItemNotifyProc vpaletteGetItemNotify(
    vpaletteItem		*item
    );

const vchar *vpaletteGetItemTitle(
    vpaletteItem		*item 
    );

/* Deprecated */

void vpaletteDeleteItem( 
    vpalette			*palette,
    vpaletteItem		*item
    );

void vpaletteDeleteItemIndex( 
    vpalette			*palette,
    int				 index
    );

void vpaletteSetItemAt(
    vpalette			*palette,
    int			 	 index,
    vpaletteItem   		*item
    );

void vpaletteSetEditorTag(
    vpalette			*palette,
    const vname			*tag
    );


/*
 * * * * * * * * * PRIVATE TYPES * * * * * * * * * *
 */

/* Palette */

struct vpalette {
  vlistview                      _listview;
  unsigned int                   flags;
  vpaletteItem                 **start;
  vpaletteItem                 **stop;
  int                            numCols;
  int                            width, height;
};

#define vpaletteCLASS(SUPER, PALETTE, ITEM)				    \
                         _vpaletteCLASS(SUPER, PALETTE, ITEM, vpaletteNoteProc)

#define _vpaletteCLASS(SUPER, PALETTE, ITEM, NOTEPROC)			    \
    vlistviewCLASS(SUPER, PALETTE, NOTEPROC);				    \
    vclassMETHOD(vpaletteINSERT_ITEM,					    \
		 (PALETTE *palette, int index, ITEM *item));		    \
    vclassMETHOD(vpaletteAPPEND_ITEM,      (PALETTE *palette, ITEM *item)); \
    vclassMETHOD_RET(vpaletteREMOVE_ITEM_INDEX, ITEM *,			    \
		 (PALETTE *palette, int index));			    \
    vclassMETHOD(vpaletteDELETE_ITEM,	   (PALETTE *palette, ITEM *item)); \
    vclassMETHOD(vpaletteDELETE_ITEM_INDEX,(PALETTE *palette, int index))


struct vpaletteClass {
    _vpaletteCLASS(vpaletteClass, vpalette, vpaletteItem, vpaletteNoteProc);
};


/* Palette Item */

struct vpaletteItem {
  vobject			 object;
  vpalette			*owner;
  int		 	 	 flags;
  vimage   			*image;
  void				*data;
  vpaletteItemNotifyProc	 notify;
  const vchar			*title;
};

#define vpaletteItemCLASS(SUPER, ITEM)					      \
    vobjectCLASS(SUPER, ITEM);						      \
    vclassMETHOD(vpaletteNOTIFY_ITEM, (ITEM *item));                          \
    vclassMETHOD(vpaletteOBSERVE_PALETTE_ITEM,                                \
		 (ITEM *item, vpalette *palette))

struct vpaletteItemClass {
    vpaletteItemCLASS(vpaletteItemClass, vpaletteItem);
};


/*
 * * * * * * * * * * PRIVATE FUNCTION PROTOTYPES * * * * * * * * * *
 */


/*
 * * * * * * * * * PRIVATE FUNCTION MACROS * * * * * * * * * *
 */

#define vpaletteGetListview( p )        (vportBASE_OBJECT((p), _listview))

#define vpaletteGetItem( p ) \
  ( vlistviewGetItem( vpaletteGetListview( p ) ) )

#define vpaletteGetClass(p) \
  ((vpaletteClass*) vdialogGetItemClass((vdialogItem *)(p)))

#define vpaletteCreateOfClass( c ) \
    ( (vpalette*) vdialogCreateItemOfClass( (vdialogItemClass *) (c) ) )
#define vpaletteCreate() \
    vpaletteCreateOfClass( vpaletteGetDefaultClass() )
#define vpaletteClone( p ) \
  ( (vpalette*) vdialogCloneItem( (vdialogItem *) (p) ) )
#define vpaletteInitOfClass( p, c ) \
  vdialogInitItemOfClass( (vdialogItem *) (p), (vdialogItemClass *) (c) )
#define vpaletteInit( p ) \
  vpaletteInitOfClass( p, vpaletteGetDefaultClass() )
#define vpaletteCopyInit( p, t ) \
  vdialogCopyInitItem( (vdialogItem *) (p), (vdialogItem *) (t) )
#define vpaletteLoad( r ) \
  ( (vpalette*) vdialogLoadItem( r ) )
#define vpaletteLoadInit( p, r ) \
   vdialogLoadInitItem( (vdialogItem *) (p), r )
#define vpaletteDestroy( p ) \
   vdialogDestroyItem( (vdialogItem *) (p) )
#define vpaletteCopy( p, t ) \
   vdialogCopyItem( (vdialogItem *) (p), (vdialogItem *) (t) )
#define vpaletteStore( p, r ) \
   vdialogStoreItem( (vdialogItem *) (p), r )
#define vpaletteSetEditorTag( p, t ) \
   vdialogSetItemTag( (vdialogItem *) (p), t )

#define vpaletteGetData( p ) \
   vdialogGetItemData( vpaletteGetItem( p ) )
#define vpaletteSetData( p, d ) \
   vdialogSetItemData( vpaletteGetItem( p ), d )

#define vpaletteGetItemCount( p ) \
  ( (p)->stop - (p)->start )

#define vpaletteGetImageWidth( p ) 	( (p)->width )
#define vpaletteGetImageHeight( p )	( (p)->height )

#define vpaletteGetColumnCount( p )	( (p)->numCols )
#define vpaletteGetRowCount( p ) \
  ( ( vpaletteGetItemCount( p ) + (p)->numCols - 1 ) / (p)->numCols )

#define vpaletteGetNotifyOnButtonUp( p ) \
   ( ((p)->flags & _vpaletteNOTIFY_ON_BUTTON_UP ) != 0 )
#define vpaletteSetNotifyOnButtonUp( p, v ) \
   { if ( v ) (p)->flags |= _vpaletteNOTIFY_ON_BUTTON_UP; \
     else (p)->flags &= (~_vpaletteNOTIFY_ON_BUTTON_UP); }

#define vpaletteGetAutoArrange( p ) \
   ( ((p)->flags & _vpaletteAUTO_ARRANGE ) != 0 )
#define vpaletteSetAutoArrange( p, v ) \
   { if ( v ) (p)->flags |= _vpaletteAUTO_ARRANGE; \
     else (p)->flags &= (~_vpaletteAUTO_ARRANGE); }

#define vpaletteGetRearrange( p ) \
   ( ((p)->flags & _vpaletteREARRANGE ) != 0 )
#define vpaletteSetRearrange( p, v ) \
   { if ( v ) (p)->flags |= _vpaletteREARRANGE; \
     else (p)->flags &= (~_vpaletteREARRANGE); }

#define vpaletteGetClickCount( p ) \
   vlistviewGetLastPointerClickCount( vpaletteGetListview( p ) )

#define vpaletteGetItemAt( p, i ) 	( (p)->start[i] )
#define vpaletteSetItemAt( p, i, pi ) \
   ((void) vpaletteReplaceItemAt(p, i, pi))

/* Palette Items */

#define vpaletteGetItemObject(i) \
    (vportBASE_OBJECT(i, object))
#define vpaletteGetItemLoadable(i) \
    vobjectGetLoadable(vpaletteGetItemObject(i))
#define vpaletteGetItemClass(i) \
    ((vpaletteItemClass*)vloadableGetClass(vpaletteGetItemLoadable(i)))

#define vpaletteCreateItemOfClass(c) \
    ((vpaletteItem*)vloadableCreateOfClass((vloadableClass*)(c)))
#define vpaletteCreateItem() \
    (vpaletteCreateItemOfClass(vpaletteGetDefaultItemClass()))
#define vpaletteInitItemOfClass(i, c) \
    vloadableInitOfClass(vpaletteGetItemLoadable(i), (vloadableClass*)(c))
#define vpaletteInitItem(i) \
    (vpaletteInitItemOfClass(i, vpaletteGetDefaultItemClass()))

#define vpaletteCloneItem(i) \
    ((vpaletteItem*)vloadableClone(vpaletteGetItemLoadable(i)))

#define vpaletteLoadItem(r) \
    ((vpaletteItem*)vloadableLoad(r))

#define vpaletteDestroyItem(i) \
    vloadableDestroy(vpaletteGetItemLoadable(i))

#define vpaletteGetItemTag( i )		\
    vloadableGetTag(vpaletteGetItemLoadable(i))

#define vpaletteSetItemTag( i, t ) \
    vloadableSetTag(vpaletteGetItemLoadable(i), t)

#define vpaletteGetItemDisabled( i ) \
  ( ( (i)->flags & _vpaletteITEM_DISABLED ) != 0 )
#define vpaletteGetItemData( i )	( (i)->data )
#define vpaletteGetItemNotify( i )	( (i)->notify )
#define vpaletteGetItemImage( i )	( (i)->image )
#define vpaletteGetItemTitle( i )	( (i)->title )

#define vpaletteSetItemNotify( i, n )	( (i)->notify = n )
#define vpaletteSetItemData( i, d )	( (i)->data = d )

#define vpaletteGetItemPalette( i )	( (i)->owner )


/*
 * * * * * * * * * FUNCTION DEFINED AS MESSAGES * * * * * * * * * *
 */

#define vpaletteInsertItem(p,n,i) \
    vclassSend( vpaletteGetClass(p), vpaletteINSERT_ITEM, (p,n,i) )
#define vpaletteAppendItem(p,i) \
    vclassSend( vpaletteGetClass(p), vpaletteAPPEND_ITEM, (p,i) )
#define vpaletteRemoveItemIndex(p,i)	\
    vclassSend( vpaletteGetClass(p), vpaletteREMOVE_ITEM_INDEX, (p,i) )

#define vpaletteNotifyItem(i) \
    vclassSend( vpaletteGetItemClass(i), vpaletteNOTIFY_ITEM, (i))

vportEND_CPLUSPLUS_EXTERN_C


#endif /* #ifndef vpaletteINCLUDED */


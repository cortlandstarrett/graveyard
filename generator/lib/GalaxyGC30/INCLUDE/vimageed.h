/* $Id: vimageed.h,v 1.24 1997/10/02 21:42:20 robert Exp $ */

#ifndef vimageedtrINCLUDED
#define vimageedtrINCLUDED 1

#ifndef  vportINCLUDED
#include <vport.h>		/* for v*HEADER */
#endif

#ifndef  vdialogINCLUDED
#include vdialogHEADER
#endif

#ifndef  vcontainerINCLUDED
#include vcontainerHEADER
#endif

#ifndef  vpaletteINCLUDED
#include vpaletteHEADER
#endif

#ifndef  vmenubarINCLUDED
#include vmenubarHEADER
#endif

#ifndef  vimageINCLUDED
#include vimageHEADER
#endif

#ifndef  vcolorchsrINCLUDED
#include vcolorchsrHEADER
#endif

#ifndef  vfontchsrINCLUDED
#include vfontchsrHEADER
#endif

#ifndef  vfilechsrINCLUDED
#include vfilechsrHEADER
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * * * * * * * * * * PUBLIC CONSTANT DEFINITIONS * * * * * * * * * *
 */

enum{
  vimageedtrSELECT_CLOSE	= vdialogNEXT_SELECT,
  vimageedtrSELECT_APPLY	,
  vimageedtrSELECT_SAVE		,
  vimageedtrSELECT_IMPORT	,
  vimageedtrSELECT_EXPORT	,
  vimageedtrSELECT_SET_SIZE	,
  vimageedtrSELECT_REVERT	,
  vimageedtrSELECT_UNDO		,
  vimageedtrSELECT_REDO		,
  vimageedtrSELECT_CUT		,
  vimageedtrSELECT_COPY		,
  vimageedtrSELECT_PASTE    	,
  vimageedtrSELECT_CLEAR	,
  vimageedtrSELECT_ROTATE	,
  vimageedtrSELECT_FLIP_HOR	,
  vimageedtrSELECT_FLIP_VER	,
  vimageedtrSELECT_MASK		,
  vimageedtrSELECT_CROP		,
  vimageedtrSELECT_FAT_BITS 	,
  vimageedtrSELECT_DRAW_CENTER	,
  vimageedtrSELECT_GRID		,
  vimageedtrSELECT_POSITION	,
  vimageedtrSELECT_PREVIEW	,
  vimageedtrSELECT_ZOOM_IN	,
  vimageedtrSELECT_ZOOM_OUT	,
  vimageedtrSELECT_SET_FONT	,
  vimageedtrSELECT_EDIT		,
  vimageedtrSELECT_CREATE	,
  vimageedtrSELECT_DELETE	
};

enum{
  vimageedtrITEM_SELECT_SAVE		= vcontainerNEXT_SELECT,
  vimageedtrITEM_SELECT_IMPORT		,
  vimageedtrITEM_SELECT_EXPORT		,
  vimageedtrITEM_SELECT_SET_SIZE	,
  vimageedtrITEM_SELECT_REVERT		,
  vimageedtrITEM_SELECT_UNDO		,
  vimageedtrITEM_SELECT_REDO		,
  vimageedtrITEM_SELECT_CUT		,
  vimageedtrITEM_SELECT_COPY		,
  vimageedtrITEM_SELECT_PASTE    	,
  vimageedtrITEM_SELECT_CLEAR		,
  vimageedtrITEM_SELECT_ROTATE		,
  vimageedtrITEM_SELECT_FLIP_HOR	,
  vimageedtrITEM_SELECT_FLIP_VER	,
  vimageedtrITEM_SELECT_MASK		,
  vimageedtrITEM_SELECT_CROP		,
  vimageedtrITEM_SELECT_FAT_BITS 	,
  vimageedtrITEM_SELECT_DRAW_CENTER	,
  vimageedtrITEM_SELECT_GRID		,
  vimageedtrITEM_SELECT_POSITION	,
  vimageedtrITEM_SELECT_PREVIEW		,
  vimageedtrITEM_SELECT_ZOOM_IN		,
  vimageedtrITEM_SELECT_ZOOM_OUT	,
  vimageedtrITEM_SELECT_SET_FONT	,
  vimageedtrITEM_SELECT_EDIT		,
  vimageedtrITEM_SELECT_CREATE		,
  vimageedtrITEM_SELECT_DELETE	
};

enum{
  vimageedtrSAVE_ON_CLOSE	= 0x0000,
  vimageedtrCLOSE_ONLY          = 0x0001
};

/*
 * * * * * * * * * * PUBLIC TYPE DEFINITIONS * * * * * * * * * *
 */

typedef struct vimageedtr	 vimageedtr;
typedef struct vimageedtrClass	 vimageedtrClass;

typedef struct vimageedtrItem	 	vimageedtrItem;
typedef struct vimageedtrItemClass	vimageedtrItemClass;

typedef void (*vimageedtrApplyFunc)( vimageedtr *editor, vimage *image );

/*
 * Image Editor Class definition
 */

#define vimageedtrCLASS(SUPER, EDITOR, NOTIFY, ITEM, LIST)                   \
    vdialogCLASS(SUPER, EDITOR, NOTIFY, ITEM, LIST);			     \
    vclassMETHOD_RET(vimageedtrHOOK_APPLY_IMAGE, vbool,			     \
		     (EDITOR *editor, vimage *image));			     \
    vclassMETHOD(vimageedtrAPPLY_IMAGE,					     \
		 (EDITOR *editor, vimage *image))

struct vimageedtrClass {
  vimageedtrCLASS( vimageedtrClass, vimageedtr, vdialogNoteProc, 
		   vdialogItem, vdialogItemList );
};

#define vimageedtrITEM_CLASS(SUPER, ITEM, NOTIFY)                   	\
    vcontainerCLASS(SUPER, ITEM, NOTIFY)

struct vimageedtrItemClass{
  vimageedtrITEM_CLASS( vimageedtrItemClass, vimageedtrItem,
			vcontainerNoteProc );
};

/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */

void vimageedtrStartup(void);


vimageedtrClass *vimageedtrGetDefaultClass(
    void
    );

vimageedtr *vimageedtrCreateOfClass( 
    vimageedtrClass		*clas
    );

vimageedtr *vimageedtrCreate(
    void
    );

void vimageedtrDestroy( 
    vimageedtr			*editor
    );

void vimageedtrOpen(
    vimageedtr			*editor
    );

void vimageedtrClose(
    vimageedtr			*editor
    );

/* Image Editor attribute modification */

void vimageedtrSetData( 
    vimageedtr			*editor,
    void			*data
    );

void vimageedtrSetImage(
    vimageedtr			*editor,
    vimage			*image
    );

void vimageedtrSetApply(
    vimageedtr			*editor,
    vimageedtrApplyFunc		 apply
    );

void vimageedtrSetBitSize(
    vimageedtr			*editor,
    int		 		 bitsize
    );

void vimageedtrSetGrid(
    vimageedtr			*editor,
    /*vbool*/ int	         value
    );

void vimageedtrSetShowLocation(
    vimageedtr			*editor,
    /*vbool*/ int	         value
    );

void vimageedtrSetPreview(
    vimageedtr			*editor,
    /*vbool*/ int	         value
    );

void vimageedtrSetSelection(
    vimageedtr			*editor,
    vimage			*image,
    vimage			*mask,
    int				 locx,
    int				 locy
    );

void vimageedtrSetPalette(
    vimageedtr			*editor,
    const vcolorPalette		*palette,
    int			     	 remap
    );

void vimageedtrSetViewRect(
    vimageedtr			*editor,
    const vrect			*rect
    );

void vimageedtrSetColorChooser(
    vimageedtr			*editor,
    vcolorchsr			*chooser
    );

void vimageedtrSetFontChooser(
    vimageedtr			*editor,
    vfontchsr			*chooser
    );

void vimageedtrSetOpenFileChooser(
    vimageedtr			*editor,
    vfilechsr			*chooser
    );

void vimageedtrSetSaveFileChooser(
    vimageedtr			*editor,
    vfilechsr			*chooser
    );

void vimageedtrSetCloseBehavior(
    vimageedtr			*editor,
    int				 value
    );

/* Image Editor attribute access */

vimageedtrClass *vimageedtrGetClass(
    vimageedtr			*editor
    );

void *vimageedtrGetData(
    vimageedtr			*editor 
    );

vimage *vimageedtrGetImage(
    vimageedtr			*editor
    );

vimageedtrApplyFunc vimageedtrGetApply(
    vimageedtr			*editor
    );

vmenubar *vimageedtrGetMenuBar(
    vimageedtr			*editor
    );

int vimageedtrGetBitSize(
    vimageedtr			*editor
    );

int /*vbool*/ vimageedtrGetGrid(
    vimageedtr			*editor
    );

int /*vbool*/ vimageedtrGetShowLocation(
    vimageedtr			*editor
    );

int /*vbool*/ vimageedtrGetPreview(
    vimageedtr			*editor
    );

vimage *vimageedtrGetSelection(
    vimageedtr			*editor,
    vimage		       **mask,
    int				*locx,
    int				*locy
    );

const vcolorPalette *vimageedtrGetPalette(
    vimageedtr			*editor
    );

const vrect *vimageedtrGetViewRect(
    vimageedtr			*editor
    );

vcolorchsr *vimageedtrGetColorChooser(
    vimageedtr			*editor
    );

vfontchsr *vimageedtrGetFontChooser(
    vimageedtr			*editor
    );

vfilechsr *vimageedtrGetOpenFileChooser(
    vimageedtr			*editor
    );

vfilechsr *vimageedtrGetSaveFileChooser(
    vimageedtr			*editor
    );

int vimageedtrGetCloseBehavior(
    vimageedtr			*editor
    );

/* Other Routines */

vdialog *vimageedtrGetDialog(
    vimageedtr			*editor
    );

int vimageedtrIsModified(
    vimageedtr			*editor
    );

int /*vbool*/ vimageedtrHasSelection(
    vimageedtr			*editor
    );

void vimageedtrClearSelection(
    vimageedtr			*editor
    );

void vimageedtrDropSelection(
    vimageedtr			*editor
    );

void vimageedtrCommitModifications(
    vimageedtr			*editor
    );


vimageedtrItemClass *vimageedtrGetDefaultItemClass(
    void
    );

vimageedtrItem *vimageedtrCreateItemOfClass( 
    vimageedtrItemClass		*clas
    );

vimageedtrItem *vimageedtrCreateItem(
    void
    );

vimageedtrItem *vimageedtrCloneItem(
    vimageedtrItem		*editor
    );

void vimageedtrInitItem(
    vimageedtrItem		*editor
    );

void vimageedtrInitItemOfClass(
    vimageedtrItem		*editor,
    vimageedtrItemClass		*clas
    );

void vimageedtrCopyInitItem(
    vimageedtrItem		*source,
    vimageedtrItem		*target
    );

void vimageedtrCopyItem(
    vimageedtrItem		*source,
    vimageedtrItem		*target
    );

vimageedtrItem *vimageedtrLoadItem(
    vresource			 resource
    );

void vimageedtrLoadInitItem(
    vimageedtrItem		*editor,
    vresource			 resource
    );

void vimageedtrStoreItem(
    vimageedtrItem		*editor,
    vresource			 resource
    );

void vimageedtrDestroyItem( 
    vimageedtrItem		*editor
    );

void vimageedtrOpenItem(
    vimageedtrItem		*editor
    );

void vimageedtrCloseItem(
    vimageedtrItem		*editor
    );

/* Image Editor attribute modification */

void vimageedtrSetItemData( 
    vimageedtrItem		*editor,
    void			*data
    );

void vimageedtrSetItemImage(
    vimageedtrItem		*editor,
    vimage			*image
    );

void vimageedtrSetItemBitSize(
    vimageedtrItem		*editor,
    int		 		 bitsize
    );

void vimageedtrSetItemGrid(
    vimageedtrItem		*editor,
    /*vbool*/ int	         value
    );

void vimageedtrSetItemShowLocation(
    vimageedtrItem		*editor,
    /*vbool*/ int	         value
    );

void vimageedtrSetItemPreview(
    vimageedtrItem		*editor,
    /*vbool*/ int	         value
    );

void vimageedtrSetItemSelection(
    vimageedtrItem		*editor,
    vimage			*image,
    vimage			*mask,
    int				 locx,
    int				 locy
    );

void vimageedtrSetItemPalette(
    vimageedtrItem		*editor,
    const vcolorPalette		*palette,
    int			     	 remap
    );

void vimageedtrSetItemViewRect(
    vimageedtrItem		*editor,
    const vrect			*rect
    );

void vimageedtrSetItemColorChooser(
    vimageedtrItem		*editor,
    vcolorchsr			*chooser
    );

void vimageedtrSetItemFontChooser(
    vimageedtrItem		*editor,
    vfontchsr			*chooser
    );

void vimageedtrSetItemOpenFileChooser(
    vimageedtrItem		*editor,
    vfilechsr			*chooser
    );

void vimageedtrSetItemSaveFileChooser(
    vimageedtrItem		*editor,
    vfilechsr			*chooser
    );

/* Image Editor attribute access */

vimageedtrItemClass *vimageedtrGetItemClass(
    vimageedtrItem		*editor
    );

void *vimageedtrGetItemData(
    vimageedtrItem		*editor 
    );

vimage *vimageedtrGetItemImage(
    vimageedtrItem		*editor
    );

int vimageedtrGetItemBitSize(
    vimageedtrItem		*editor
    );

int /*vbool*/ vimageedtrGetItemGrid(
    vimageedtrItem		*editor
    );

int /*vbool*/ vimageedtrGetItemShowLocation(
    vimageedtrItem		*editor
    );

int /*vbool*/ vimageedtrGetItemPreview(
    vimageedtrItem		*editor
    );

vimage *vimageedtrGetItemSelection(
    vimageedtrItem		*editor,
    vimage		       **mask,
    int				*locx,
    int				*locy
    );

const vcolorPalette *vimageedtrGetItemPalette(
    vimageedtrItem		*editor
    );

const vrect *vimageedtrGetItemViewRect(
    vimageedtrItem		*editor
    );

vcolorchsr *vimageedtrGetItemColorChooser(
    vimageedtrItem		*editor
    );

vfontchsr *vimageedtrGetItemFontChooser(
    vimageedtrItem		*editor
    );

vfilechsr *vimageedtrGetItemOpenFileChooser(
    vimageedtrItem		*editor
    );

vfilechsr *vimageedtrGetItemSaveFileChooser(
    vimageedtrItem		*editor
    );

/* Other Routines */

vdialogItem *vimageedtrGetItemItem(
    vimageedtrItem		*editor
    );

vcontainer *vimageedtrGetItemContainer(
    vimageedtrItem		*editor
    );

int vimageedtrItemIsModified(
    vimageedtrItem		*editor
    );

int /*vbool*/ vimageedtrItemHasSelection(
    vimageedtrItem		*editor
    );

void vimageedtrClearItemSelection(
    vimageedtrItem		*editor
    );

void vimageedtrDropItemSelection(
    vimageedtrItem		*editor
    );

void vimageedtrCommitItemModifications(
    vimageedtrItem		*editor
    );

/*
 * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * *
 */

#ifndef  _vimgedDEFINED_VIMGED
#define  _vimgedDEFINED_VIMGED		/** private type defines  **/

typedef struct vimged		 vimged;
typedef struct vimgedview      	 vimgedview;

#endif  /* _vimgedDEFINED_VIMGED */

struct vimageedtrItem{
  vcontainer	 	 container;
  unsigned short	 flags;
  vbool		 	 hasMask;
  vimage     		*original;
  vimage		*image;
  vimgedview		*imageView;
  vimgedview		*maskView;
  vimgedview		*currView;
  vimged		*imageEditor;
  vimged		*maskEditor;
  vdialogItem		*fgbgItem;
  vdialogItem		*editAreaItem;
  vdialog		*virtualDialog;
  vdialogItem		*virtItem;
  vdialogItem		*mruItem;
  vpalette		*toolPalette;
  vpalette		*lineWtPalette;
  vcontainer		*positions;
  vdialogItem		*xVal;
  vdialogItem		*yVal;
  vdialogItem		*dxVal;
  vdialogItem		*dyVal;
  vdialogItem		*lenVal;
  vdialogItem		*angVal;
  vbool		 	 tracking;
  vpoint	 	 start;
  vimage		*offscreen;
  vrect		 	 newView;
  vcolorchsr		*colorChooser;
  vfontchsr		*fontChooser;
  vfilechsr		*openChooser;
  vfilechsr		*saveChooser;
};

struct vimageedtr{
  vdialog	 	 dialog;
  unsigned int		 flags;
  vimageedtrItem       	*item;
  vmenubar	     	*menubar;
  vimageedtrApplyFunc	 applyFunc;
};

/*
 * * * * * * * * * * PRIVATE FUNCTION PROTOTYPES * * * * * * * * * *
 */

vimage *vimportGIF( vfsPath *path );
void vexportGIF( vfsPath *path, vimage *image );

vimage *_vimageedtrGetSelectionImage( vimageedtr *editor );
vimage *_vimageedtrGetSelectionMask( vimageedtr *editor );
void _vimageedtrGetSelectionOffset( vimageedtr *editor, int *x, int *y );

/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * *
 */

#define vimageedtrCreateOfClass( c )	\
  ( (vimageedtr *) vdialogCreateOfClass( (vdialogClass *) (c) ) )
#define vimageedtrGetClass( c ) \
  ( (vimageedtrClass *) vdialogGetClass( (vdialog *) (c) ) )
#define vimageedtrCreate() \
  vimageedtrCreateOfClass( vimageedtrGetDefaultClass() )
#define vimageedtrDestroy( c ) \
  vdialogDestroy((vdialog *) (c))

#define vimageedtrGetData( e ) \
  ( vdialogGetData( (vdialog *) (e) ) )

#define vimageedtrGetDialog( e )     	( (vdialog *) (e) )

#define vimageedtrSetOpenFileChooser( e, c ) \
  ( (e)->item->openChooser = (c) )
#define vimageedtrSetSaveFileChooser( e, c ) \
  ( (e)->item->saveChooser = (c) )

#define vimageedtrSetFontChooser( e, c ) \
  ( (e)->item->fontChooser = (c) )
#define vimageedtrSetColorChooser( e, c ) \
  ( (e)->item->colorChooser = (c) )

#define vimageedtrGetCloseBehavior( e ) ( (e)->flags )
#define vimageedtrSetCloseBehavior( e, f ) ( (e)->flags = f )

#define vimageedtrGetItemContainer( p ) \
  ( vportBASE_OBJECT( ( p ), container ) )
#define vimageedtrGetItemItem( p ) \
  vcontainerGetItem( vimageedtrGetItemContainer( p ) )

#define vimageedtrGetItemClass( c ) \
  ( (vimageedtrItemClass *) vcontainerGetClass( (vcontainer *) (c) ) )

#define vimageedtrCreateItemOfClass(p) \
    ((vimageedtrItem*) vdialogCreateItemOfClass((vdialogItemClass*)(p)))
#define vimageedtrCreateItem() \
    vimageedtrCreateItemOfClass(vimageedtrGetDefaultItemClass())
#define vimageedtrDestroyItem( p ) \
    vdialogDestroyItem( vimageedtrGetItemItem( p ) )
#define vimageedtrCloneItem(p) \
    ((vimageedtrItem*)vdialogCloneItem((vdialogItem *) p))
#define vimageedtrInitItemOfClass(p, c) \
    vdialogInitItemOfClass((vdialogItem *) (p), (vimageedtrItemClass*)(c))
#define vimageedtrInitItem(p) \
    vimageedtrInitItemOfClass(p, vimageedtrGetDefaultItemClass())
#define vimageedtrCopyInitItem(p, t) \
    vdialogCopyInitItem((vdialogItem *) (p), (vdialogItem *) (t))
#define vimageedtrCopyItem( p, d ) \
    vdialogCopyItem( vimageedtrGetItemItem( p ), \
		     vimageedtrGetItemItem( d ) )
#define vimageedtrLoadItem(r) \
    ((vimageedtrItem *) vdialogLoadItem(r))
#define vimageedtrLoadInitItem(p, r) \
    vdialogLoadInitItem((vdialogItem *)(p), r)
#define vimageedtrStoreItem( p, r ) \
    vdialogStoreItem( vimageedtrGetItemItem( p ), r )
#define vimageedtrGetItemData( p ) \
    vdialogGetItemData( vimageedtrGetItemItem( p ) )
#define vimageedtrSetItemData( p, d ) \
    vdialogSetItemData( vimageedtrGetItemItem( p ), d )

/*
 * * * * * * * * * * PRIVATE FUNCTION MESSAGE DEFINITIONS * * * * * * * * * *
 */

#define vimageedtrSetData( c, d ) \
  vclassSend( vimageedtrGetClass( c ), vwindowSET_DATA, (c, d) )
#define vimageedtrOpen( c ) \
  vclassSend( vimageedtrGetClass( c ), vwindowOPEN, (c) )
#define vimageedtrClose( c ) \
  vclassSend( vimageedtrGetClass( c ), vwindowCLOSE, (c) )


vportEND_CPLUSPLUS_EXTERN_C

#endif /* #ifndef vimageedtrINCLUDED */

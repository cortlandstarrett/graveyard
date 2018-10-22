/* $Id: vmdemo.c,v 1.8 1997/10/16 21:12:33 bill Exp $
 *
 * The following Sample Code is provided for your reference purposes in
 * connection with your use of the Galaxy Application Environment (TM) software
 * product which you have licensed from Visix Software, Inc. ("Visix").
 * The Sample code is provided to you without any warranty of any kind
 * whatsoever and you agree to be responsible for the use and/or incorporation
 * of the Sample Code into any software product you develop. You agree to fully
 * and completely indemnify and hold Visix harmless from any and all loss,
 * claim, liability or damages with respect to your use of the Sample Code.  
 *
 * Subject to the foregoing, you are permitted to copy, modify, and distribute
 * the Sample Code for any purpose and without fee, provided that (i) a
 * copyright notice in the in the form of "Copyright 1992,93,94 Visix Software
 * Inc., 11440 Commerce Park Drive, Reston, VA  22091. All Rights Reserved"
 * appears in all copies, (ii) both the copyright notice and this permission
 * notice appear in supporting documentation and (iii) you are a valid
 * licensee of Galaxy Application Environment.
 */


#ifndef  vportINCLUDED
#include <vport.h>		/* for v*HEADER */
#endif

#include vstdlibHEADER
				/* for exit */
#include vresourceHEADER
#include vlistitemHEADER
#include vlistHEADER
#include vapplicationHEADER
#include vnumHEADER
#include vdialogHEADER
#include vlistviewHEADER
#include vmenuHEADER
#include vmenubarHEADER
#include vstartupHEADER

#if (vdebugDEBUG)
static const char	 _mdemoTag[] = "mdemo";
#define vdebugTAG	 _mdemoTag
#endif

#define entryLEVEL_INSET	8

/*
 *  Resource file entry in list
 */
typedef struct _resEntry{
  struct _resEntry    	*parent;
  vbool		 	 isOpen;
  vbool			 processing;
  vresource	 	 parentRes;
  vresource	 	 resource;
  int		 	 type;
  int		 	 index;
  const vname		*tag;
  vdialogItem		*item;
  int		  	 level;
} _resEntry;

/*
 *  Holds information for dialog
 */
typedef struct _dialogInfo{
  vimage		*downArrow;
  vimage		*rtArrow;
  vdialog		*dialog;
  vlistitem		*colList;
  vlistitem		*rowList;
  vlistitem		*hexList;
  vlistitem		*expandList;
  vdialogItemList	*expandItemList;
  vmenubar		*menubar;
  _resEntry		*entry;
  _resEntry		*start;
} _dialogInfo;

_dialogInfo	 	 info;
vresource	 	 resFile;
long			 blockSize = 0;
vbyte			*block = NULL;
vlistitemClass		*syncScrollClass 	= NULL;
vlistitemClass		*doNothingListClass 	= NULL;
vlistitemClass		*expandListClass 	= NULL;
static vpool		*entryPool 		= NULL;
vresource	 	 examineResFile = vresourceNULL;

/* * * * * * * * Dialog Item List Functions * * * * * * * * */

/*
 *  Since we're handling our own dialog item list, we need to provide
 *  these functions.  Since we're not doing anything fancy with this item list,
 *  just use the vdialog versions.
 */

static vdialog *determineDialog( vobject *owner )
{
  return( vdialogDetermineItemDialog( (vdialogItem *) owner ) );
}

static vcursor *determineCursor( vobject *owner )
{
  return( vdialogDetermineItemCursor( (vdialogItem *) owner ) );
}

static vfont *determineFont( vobject *owner )
{
  return( vdialogDetermineItemFont( (vdialogItem *) owner ) );
}

static void determineColorsFrom( vobject *owner, long flags, vcolor **known,
				 int *ids, int count, vcolor **colors )
{
  vdialogDetermineItemColorsFrom( (vdialogItem *) owner,
				  flags, known, ids, count, colors );
}

static int determineLineWidth( vobject *owner )
{
  return( vdialogDetermineItemLineWidth( (vdialogItem *) owner ) );
}

static void determineBounds( vobject *owner, register vrect *rect )
{
  vdialogDetermineItemListBounds( vdialogGetItemItemList 
				  ( (vdialogItem *) owner ), rect );
}

static void determineContent (vobject *owner, vrect *rect)
{
  vdialogDetermineItemListContent( vdialogGetItemItemList 
				   ( (vdialogItem *) owner), rect );
}

static vdict *determineKeyMap( vobject *owner )
{
  return( vdialogGetItemKeyMap( (vdialogItem *) owner ) );
}

static vdict *determineKeyDispatch (vobject *owner)
{
  return( vdialogGetItemKeyDispatch( (vdialogItem *) owner ) );
}

/*
 *  Our table for the owner functions for our dialog item list 
 */
static vdialogItemListOwnerFuncs ownerFuncs = {
    0,
    determineDialog,
    determineCursor,
    determineFont,
    determineColorsFrom,
    determineLineWidth,
    determineBounds,
    determineContent,
    determineKeyMap,
    determineKeyDispatch
};

/* * * * * * * * Other Functions * * * * * * * * */

/*************************************************************
  _newResEntry

  Create a new resource entry and initialize
**************************************************************/
_resEntry *_newResEntry()
{
  _resEntry	*entry;

  if ( entryPool == NULL )
    entryPool = vpoolCreate( sizeof( _resEntry ) );

  entry = (_resEntry *) vpoolAlloc( entryPool );

  entry->parent		= NULL;
  entry->isOpen		= FALSE;
  entry->processing	= FALSE;
  entry->parentRes	= vresourceNULL;
  entry->tag		= NULL;
  entry->resource	= vresourceNULL;
  entry->type		= vresourceUNTYPED;
  entry->level		= -1;
  entry->index		= -1;
  entry->item		= NULL;
  
  return( entry );
}

/*************************************************************
  closeDict

  Closes dictionary or array resource.
**************************************************************/
static void closeDict( vlistitem *listitem, int row, _resEntry *entry )
{
  _resEntry	*curr;
  vlist		*list = vlistitemGetList( listitem );

  while ( vlistGetRowCount( list ) && row < vlistGetRowCount( list ) )
    {
      curr = (_resEntry *) vlistGetCellValue( list, row, 0 );
      if ( curr == NULL || curr->parent != entry )
	break;

      if ( curr->isOpen )
	closeDict( listitem, row + 1, curr );

      vlistRemoveRow( list, row );
      if ( curr->item )
	{
	  vdialogCloseItem( curr->item );
	  vdialogDeleteItemListItem( vdialogGetItemItemList( curr->item ),
				     curr->item );
	  vdialogDestroyItem( curr->item );
	}

      vpoolFree( entryPool, curr );
    }
}

/*************************************************************
  _resControlNotify
**************************************************************/
static void _resControlNotify( vcontrol *control, vevent *event )
{
  vwindowBeep();
  vdebugInform( "Value changed : %s\n", vcontrolGetValue( control ) ?
	        "TRUE" : "FALSE" );
}

/*************************************************************
  _addControl

  Adds control to resource if it is of proper type
**************************************************************/
static void _addControl( _dialogInfo *info, _resEntry *entry )
{
  vcontrol	*control;

  if ( vresourceType( entry->parentRes ) != vresourceARRAY &&
       vresourceType( entry->resource ) != vresourceDICT &&
       vresourceType( entry->resource ) != vresourceARRAY )
    {
      control = vcontrolCreateToggle();
      vcontrolSetData( control, entry );
      vcontrolSetNotify( control, _resControlNotify );
      entry->item = (vdialogItem *) control;
      vdialogSetItemTitleScribed( entry->item, vcharScribeLiteral( "Option" ) );
      vdialogAppendItemListItem( info->expandItemList, entry->item );
    }
}

/*************************************************************
  openDict

  Opens dictionary or array resource.
**************************************************************/
static void openDict( vlistitem *listitem, int row, _resEntry *parent )
{
  int		 count;
  vresource 	 currRes;
  const vchar  	*currResTag;
  int		 i;
  _resEntry	*info;
  vlist		*list = vlistitemGetList( listitem );
  int		 restype;
  vbool		 isArray = FALSE;
  vresource	 resource;
  _dialogInfo 	*dlogInfo;

  dlogInfo = (_dialogInfo *) vlistitemGetData( listitem );

  if ( parent->parentRes != vresourceNULL)
    isArray = ( vresourceType( parent->parentRes ) == vresourceARRAY );
  
  if ( isArray )
    resource = vresourceGetAt( parent->parentRes, parent->index );
  else
    resource = parent->resource;

  count = vresourceCountComponents( resource );
  if ( count == 0 )
    return;

  for ( i = 0; i < count; i++ )
    {
      if ( parent->type == vresourceDICT )
	{
	  currRes = 
	    vresourceGetNthComponent( resource, i, &currResTag );
	  restype = vresourceType( currRes );
	}
      else 
	{
	  currResTag = vresourceTAG_NULL;
	  currRes = vresourceNULL;
	  restype = vresourceArrayType( resource );
	  if ( restype == vresourceDICT )
	    currRes = vresourceGetAt( resource, i );
	}

      info 		= _newResEntry();
      info->type  	= restype;
      info->level 	= parent->level + 1;
      info->parentRes 	= resource;
      info->resource   	= currRes;
      info->tag		= currResTag;
      info->parent 	= parent;
      info->index	= i;

      _addControl( dlogInfo, info );
      
      vlistInsertRow( list, ++row );
      vlistSetCellValue( list, row, 0, info );

      /*  Make sure the rows are tall enough to hold the new control */
      if ( info->item &&
           vdialogGetItemH( info->item ) > vlistitemGetRowHeight( listitem ) )
          vlistitemSetRowHeight( listitem, 
                                 vdialogGetItemH( info->item ) );
    }
}

/*************************************************************
  _drawResEntryCell

  Draw resource entry in list cell
**************************************************************/
static void _drawResEntryCell( vlistitem *listitem, int row, int col, 
			       int selected, vrect *rect )
{
  _dialogInfo	*info;
  _resEntry	*entry;
  vrect		 temp;
  vchar		 arrayName[10];
  vimage    	*image = NULL;
  vlist		*list = vlistitemGetList( listitem );
  vbool		 isArray;
  int		 offset;
  int		 defArrowWidth;

  info = (_dialogInfo *) vlistitemGetData( listitem );
  entry = (_resEntry *) vlistGetCellValue( list, row, col );
  if ( !entry )
    return;

  vdrawGSave();

  /*
   *  Clip to inset list cell rectangle
   */
  temp = *rect;
  temp.x += 3; temp.w -= 3;
  vdrawRectClip( temp.x, temp.y, temp.w, temp.h );

  /*
   *  Draw expand/collapse image if necessary
   */
  if ( ( entry->type == vresourceDICT  || entry->type == vresourceARRAY ) )
    {
      image = entry->isOpen ? info->downArrow : info->rtArrow;
      vdrawMoveTo( temp.x, temp.y + ( temp.h - vimageGetHeight( info->rtArrow ) ) / 2 );
      vdrawImageCompositeIdent( image );
    }

  /*
   *  Inset cell rectangle the appropriate amount for drawing string
   */
  defArrowWidth = vimageGetWidth( info->rtArrow );
  offset = entry->level * entryLEVEL_INSET + defArrowWidth + 5;
  temp.x += offset;
  temp.w -= offset;

  /*
   *  Draw resource name or array index
   */
  isArray = ( vresourceType( entry->parentRes ) == vresourceARRAY );
  if ( isArray )
    {
      vcharCopyScribed( vnumScribeInt( entry->index ), arrayName );
      vdrawRectShowCenterY( arrayName, &temp );
    }
  else
    vdrawRectShowCenterY( entry->tag, &temp );

  /*
   *  If cell contains dialog item, position and draw it
   */
  if ( entry->item )
    {
      /*
       *  Positiion dialog item
       */
      temp = *rect;
      temp.x = temp.x + temp.w - 80;
      temp.w = 80;
      if ( !vrectMIsEqual( vdialogGetItemRect( entry->item ), &temp ) )
	vdialogSetItemRect( entry->item, &temp );

      /*
       *  Draw item
       */
      vdrawSetFont( vdialogDetermineItemFont( entry->item ) );
      vdrawSetColor( vdialogDetermineItemForeground( entry->item ) );
      vdrawSetComplement( vdialogDetermineItemBackground( entry->item ) );
      vdialogDrawItem( entry->item );
    }

  vdrawGRestore();
}

/*****************************************************************
  _doExpandListNotify

  list notification function for expand list
*****************************************************************/
static void _doExpandListNotify( vlistitem *listitem, int notifyType )
{
  _dialogInfo		*info;
  _resEntry		*entry;
  int		 	 row;
  vlist			*list = vlistitemGetList( listitem );

  info = (_dialogInfo *) vlistitemGetData( listitem );

  if ( notifyType == vlistviewSELECTION_WILL_CHANGE )
    vdialogSetItemListFocus( info->expandItemList, NULL );

  /*
   *  If nothing is selected, set selected entry to NULL and return
   */
  if ( ( row = vlistitemGetSelectedRow( listitem ) ) == 
       vlistitemNO_CELLS_SELECTED )
    {
      info->entry = NULL;
      return;
    }

  /*
   *  Store away selected entry
   */
  if ( notifyType == vlistviewSELECTION_HAS_CHANGED )
    {
      entry = (_resEntry *) vlistGetCellValue( list, row, 0 );
      info->entry = entry;
    }
}

/*****************************************************************
  _initExpandList

  Initializes expand list
*****************************************************************/
static void _initExpandList( vlistitem *listitem )
{
  vlistview   		*listview;
  vdialogItem		*item;
  _dialogInfo		*info;
  _resEntry		*entry;
  vlist			*list;
  vlistSelection	*select;
  
  info = (_dialogInfo *) vlistitemGetData( listitem );
  info->entry = NULL;

  list = vlistitemGetList( listitem );
  select = vlistitemGetSelection( listitem );

  /*
   *  Initialize listitem 
   */
  listview = vlistitemGetView( listitem );
  item = vlistviewGetItem( listview );
  vlistitemSetCellContentProc( listitem, _drawResEntryCell );
  vlistitemSetSelectNotify( listitem, _doExpandListNotify );
  vlistSetSelectMethod( list, select, vlistONE_ONLY_SELECTION );
  vlistSetAtLeastOneSelection( list, select, TRUE );
  vlistSetRowCount( list, 0 );

  /*
   *  Initialize first entry
   */
  entry 		= _newResEntry();
  entry->resource	= examineResFile;
  entry->type		= vresourceDICT;
  entry->level		= -1;
  
  /*
   *  Open top level resource (which is a dictionary)
   */
  info->start = entry;
  openDict( info->expandList, -1, entry );
}

/*****************************************************************
  _cleanUp

  Cleans up memory associated with dialog
*****************************************************************/
static void _cleanUp( _dialogInfo *info )
{
  vimageDestroy( info->downArrow );
  vimageDestroy( info->rtArrow );
  closeDict( info->expandList, 0, info->start );
  vpoolFree( entryPool, info->start );
}

/*****************************************************************
  _doFileQuit

  Quits application when quit menu item chosen
*****************************************************************/
static void _doFileQuit( vmenuItem *item, vevent *event )
{
  _dialogInfo	*info;
  
  info = (_dialogInfo *) vmenuGetItemData( item );

  /*
   *  Clean up
   */
  _cleanUp( info );
  vwindowDestroyLater( vdialogGetWindow( info->dialog ) );

  /*
   *  Stop event loop
   */
  veventStopProcessing();
}

/*****************************************************************
  _initMenus

  Initialize menus
*****************************************************************/
static void _initMenus( vmenubar *menubar )
{
  _dialogInfo	*info;
  vmenu		*menu;
  vmenuItem	*item;

  info = (_dialogInfo *) vmenubarGetData( menubar );
  menu = vmenubarFindMenu( menubar, vnameInternGlobalLiteral( "FileMenu" ) );
  item = vmenuFindItem( menu, vnameInternGlobalLiteral( "Quit" ) );
  vmenuSetItemData( item, info );
  vmenuSetItemNotify( item, _doFileQuit );
}

/*****************************************************************
  _syncScrollAction

  Notification for hex list when it scrolls.  Force scroll of 
  title lists.
*****************************************************************/
static void _syncScrollAction( vlistitem *listitem, int hscroll, int vscroll )
{
  _dialogInfo	*info;

  info = (_dialogInfo *) vlistitemGetData( listitem );
  
  vlistviewScrollRelative( vlistitemGetView( info->rowList ), 0, vscroll );
  vlistviewScrollRelative( vlistitemGetView( info->colList ), hscroll, 0 );
}

/*****************************************************************
  _initSyncScrollClass

  Initialize syncronized scrolling list for hex list
*****************************************************************/
static void _initSyncScrollClass( void )
{
  if ( syncScrollClass == NULL )
    {
      syncScrollClass = vclassReproduce( vlistitemGetDefaultClass() );
      vclassSetNameScribed( syncScrollClass,
			    vcharScribeLiteral( "syncScrollClass" ) );
      vclassSet( syncScrollClass, vlistviewNOTIFY_SCROLL, _syncScrollAction );
    }
}

/*****************************************************************
  _handleDoNothingButtonDown

  Do nothing for button down
*****************************************************************/
static int _handleDoNothingButtonDown( vlistitem *item, vevent *event )
{
  return( FALSE );
}

/*****************************************************************
  _initDoNothingListClass

  Initialize list class for title fields of hex list
*****************************************************************/
static void _initDoNothingListClass( void )
{
  if ( doNothingListClass == NULL )
    {
      doNothingListClass = vclassReproduce( vlistitemGetDefaultClass() );
      vclassSetNameScribed( doNothingListClass,
			    vcharScribeLiteral( "doNothingListClass" ) );
      vclassSet( doNothingListClass, vdialogHANDLE_ITEM_BUTTON_DOWN, 
		 _handleDoNothingButtonDown );
    }
}

/*****************************************************************
  _initHexList

  Initialize hex list.
*****************************************************************/
static void _initHexList( _dialogInfo *info, vbyte *buffer, long size )
{
  int		 numRows;
  int		 numCols;
  int		 value;
  int	     	 i;
  int		 row, col;
  vliststr	*list;

  /*
   *  Perform calculations for number of rows and columns
   */
  numCols = size > 16 ? 16 : size;
  numRows = ( size + 15 ) / 16;

  /*
   *  Initialize row titles list
   */
  vlistSetSelectMethod( vlistitemGetList( info->rowList ), 
		        vlistitemGetSelection( info->rowList ),
		        vlistNO_SELECTION );
  for ( i = value = 0; i < numRows; i++, value += 16 )
    vlistitemAppendScribed( info->rowList, vnumScribeInt( value ) );

  /* Append a few emptys to make sure we can scroll when we're told */
  vlistitemAppendScribed( info->rowList, vcharScribeLiteral( " " ) );
  vlistitemAppendScribed( info->rowList, vcharScribeLiteral( " " ) );

  /*
   *  Initialize column titles list
   */
  list = vlistitemGetListstr( info->colList );
  vlistitemSetSelectMethod( info->colList, vlistNO_SELECTION );
  vlistviewSetColumnWidth( vlistitemGetView( info->colList ), 
			   vlistviewALL_COLUMNS, 40 );
  vliststrSetColumnCount( list, numCols+2 );
  for ( i = 0; i < numCols; i++ )
    vliststrSetCellValueScribed( list, 0, i, vnumScribeInt( i ) );

  /* Append a few emptys to make sure we can scroll when we're told */
  vliststrSetCellValueScribed( list, 0, numCols+1, vcharScribeLiteral( " " ) );
  vliststrSetCellValueScribed( list, 0, numCols+2, vcharScribeLiteral( " " ) );


  /*
   *  Initialize hex list
   */
  i = 0;
  list = vlistitemGetListstr( info->hexList );
  vlistviewSetColumnWidth( vlistitemGetView( info->hexList ), 
			   vlistviewALL_COLUMNS, 40 );
  vliststrSetRowCount( list, numRows );	
  vliststrSetColumnCount( list, numCols );
  for ( row = 0; row < numRows; row++ )
    for ( col = 0; col < numCols; col++ )
      if ( i < size )
	vliststrSetCellValueScribed( list, row, col, 
				     vnumScribeInt( buffer[i++] ) );
}

/*****************************************************************
  _handleExpandButtonDown
*****************************************************************/
static int _handleExpandButtonDown( vlistitem *listitem, vevent *event )
{
  _dialogInfo	*info;
  vdialogItem	*item;
  vdialogItem	*litem;
  vpoint	 pt;
  vlistview	*view = vlistitemGetView( listitem );
  int		 row, col;
  vrect		 rect;
  _resEntry	*entry;

  info = (_dialogInfo *) vlistitemGetData( listitem );

  vpointSet( veventGetPointerX( event ), veventGetPointerY( event ), &pt );

  /*
   *  Check to see if point is in dialog item contained in listitem
   */
  if ( info->entry && info->entry->item &&
       vrectContainsPoint( vdialogGetItemRect( info->entry->item ), 
			   pt.x, pt.y ) )
    {
      litem = vlistitemGetItem( listitem );
      item = info->entry->item;

      vdialogFocusItemList( vdialogGetItemItemList( litem ) );
      vdialogSetItemListFocus( vdialogGetItemItemList( litem ), litem );
      vdialogSetItemListFocus( info->expandItemList, item );
      vdialogSetItemListDrag( vdialogGetItemItemList( litem ), item );

      return( vdialogHandleItemButtonDown( item, event ) );
    }

  /*
   *  Check to see if point is in expand/contract arrow rectangle
   */
  if ( vrectContainsPoint( vlistviewGetListRect( view ), pt.x, pt.y ) )
    {
      vlistviewMapPointToCell( view, &pt, &row, &col );
      entry = ( row == -1 ) ? NULL :
	(_resEntry *) vlistitemGetValueAt( listitem, row );

      if ( entry && ( entry->type == vresourceDICT || 
		      entry->type == vresourceARRAY ) )
	{
	  vlistviewGetCellRect( (vlistview *) listitem, row, 0, &rect );
	  rect.x += 3;
	  rect.w = vimageGetWidth( info->rtArrow );
	  
	  if ( !entry->processing && 
	       pt.x >= rect.x && pt.x <= rect.x + rect.w )
	    {
	      entry->processing = TRUE;
	      if ( entry->isOpen )
		{
		  closeDict( info->expandList, row + 1, entry );
		  entry->isOpen = FALSE;
		}
	      else
		{
		  openDict( info->expandList, row, entry );
		  entry->isOpen = TRUE;
		}
	      entry->processing = FALSE;    
	      vdialogInvalItemRect( (vdialogItem *) listitem, &rect, 
				    vwindowINVAL_OPAQUE );
	    }
	}
    }

  return( vclassSendSuper( expandListClass, vdialogHANDLE_ITEM_BUTTON_DOWN, 
			   (listitem, event) ) );
}

/*****************************************************************
  _handleExpandKeyUp
*****************************************************************/
static int _handleExpandKeyUp( vlistitem *listitem, vevent *event )
{
  _dialogInfo	*info;

  info = (_dialogInfo *) vlistitemGetData( listitem );
  if ( info->entry && info->entry->item &&
       vdialogGetItemListFocus( info->expandItemList ) == info->entry->item )
    return( vdialogHandleItemKeyUp( info->entry->item, event ) );

  return( vclassSendSuper( expandListClass, vdialogHANDLE_ITEM_KEY_UP, 
			   (listitem, event) ) );
}

/*****************************************************************
  _handleExpandKeyDown
*****************************************************************/
static int _handleExpandKeyDown( vlistitem *listitem, vevent *event )
{
  _dialogInfo	*info;

  info = (_dialogInfo *) vlistitemGetData( listitem );
  if ( info->entry && info->entry->item &&
       vdialogGetItemListFocus( info->expandItemList ) == info->entry->item )
    return( vdialogHandleItemKeyDown( info->entry->item, event ) );

  return( vclassSendSuper( expandListClass, vdialogHANDLE_ITEM_KEY_DOWN, 
			   (listitem, event) ) );
}

/*****************************************************************
  _doExpandOpen
*****************************************************************/
static void _doExpandOpen( vlistitem *listitem )
{
  _dialogInfo	*info;

  info = (_dialogInfo *) vlistitemGetData( listitem );
  vdialogOpenItemList( info->expandItemList );
  vclassSendSuper( expandListClass, vdialogOPEN_ITEM, (listitem) );
}

/*****************************************************************
  _doExpandClose
*****************************************************************/
static void _doExpandClose( vlistitem *listitem )
{
  _dialogInfo	*info;

  info = (_dialogInfo *) vlistitemGetData( listitem );
  vdialogCloseItemList( info->expandItemList );
  vclassSendSuper( expandListClass, vdialogCLOSE_ITEM, (listitem) );
}

/*****************************************************************
  _doExpandFocus
*****************************************************************/
static void _doExpandFocus( vlistitem *listitem )
{
  _dialogInfo	*info;

  info = (_dialogInfo *) vlistitemGetData( listitem );
  vclassSendSuper( expandListClass, vdialogFOCUS_ITEM, (listitem) );
  vdialogFocusItemList( info->expandItemList );
}

/*****************************************************************
  _doExpandUnfocus
*****************************************************************/
static void _doExpandUnfocus( vlistitem *listitem )
{
  _dialogInfo	*info;

  info = (_dialogInfo *) vlistitemGetData( listitem );
  vclassSendSuper( expandListClass, vdialogUNFOCUS_ITEM, (listitem) );
  vdialogUnfocusItemList( info->expandItemList );
}

/*****************************************************************
  _doExpandNotifyScroll
*****************************************************************/
static void _doExpandNotifyScroll( vlistitem *listitem, int hor, int ver )
{
  _dialogInfo	*info;
  vrect		 r;

  vclassSendSuper( expandListClass, vlistviewNOTIFY_SCROLL, 
		   (listitem, hor, ver) );

  /*
   *  Scroll dialog items as well when listitem scrolls
   */
  info = (_dialogInfo *) vlistitemGetData( listitem );
  if ( info->entry && info->entry->item )
    {
      r = *vdialogGetItemRect( info->entry->item );
      vrectOffset( &r, hor, ver, &r );
      vdialogSetItemRect( info->entry->item, &r );
    }
}

/*****************************************************************
  _initExpandListClass

  Initialize Expandronized scrolling list for hex list
*****************************************************************/
static void _initExpandListClass( void )
{
  if ( expandListClass == NULL )
    {
      expandListClass = vclassReproduce( vlistitemGetDefaultClass() );
      vclassSetNameScribed( expandListClass,
			    vcharScribeLiteral( "expandListClass" ) );
      vclassSet( expandListClass, vdialogHANDLE_ITEM_KEY_DOWN, 
		 _handleExpandKeyDown );
      vclassSet( expandListClass, vdialogHANDLE_ITEM_KEY_UP, 
		 _handleExpandKeyUp );
      vclassSet( expandListClass, vdialogHANDLE_ITEM_BUTTON_DOWN, 
		 _handleExpandButtonDown );
      vclassSet( expandListClass, vdialogFOCUS_ITEM, _doExpandFocus );
      vclassSet( expandListClass, vdialogUNFOCUS_ITEM, _doExpandUnfocus );
      vclassSet( expandListClass, vdialogOPEN_ITEM, _doExpandOpen );
      vclassSet( expandListClass, vdialogCLOSE_ITEM, _doExpandClose );
      vclassSet( expandListClass, vlistviewNOTIFY_SCROLL,
		 _doExpandNotifyScroll );
    }
}

/****************************************************************
  _dialogNotify
*****************************************************************/
static void _dialogNotify( vdialog *dialog, vevent *event )
{
  if ( veventGetType( event ) == veventWINDOW_STATE && 
       veventIsClose( event ) )
    {
      _cleanUp( &info );
      vwindowDestroyLater( vdialogGetWindow( info.dialog ) );
      veventStopProcessing();
    }
}

/*****************************************************************
  _openDialog

  Load in dialog from resource file, initialize it and open it.
*****************************************************************/
static void _openDialog( void )
{
  vresource	 	 res;
  vdialog		*dialog;
  const vname		*tag;

  _initSyncScrollClass();
  _initExpandListClass();
  _initDoNothingListClass();

  /*
   *  Load Images
   */
  res = vresourceGet( resFile, vnameInternGlobalLiteral( "Right Arrow" ) );
  info.rtArrow = vimageLoad( res );

  res = vresourceGet( resFile, vnameInternGlobalLiteral( "Down Arrow" ) );
  info.downArrow = vimageLoad( res );

  /*
   *  Load dialog
   */
  res = vresourceGet( resFile, vnameInternGlobalLiteral( "Dialog" ) );
  dialog = vdialogLoad( res );
  info.dialog = dialog;

  /*
   *  Load and Initialize dialog items
   */
  tag = vnameInternGlobalLiteral( "RowList" );
  info.rowList = (vlistitem *) vdialogFindItem( dialog, tag );
  vlistitemSetData( info.rowList, &info );

  tag = vnameInternGlobalLiteral( "ColList" );
  info.colList = (vlistitem *) vdialogFindItem( dialog, tag );
  vlistitemSetData( info.colList, &info );

  tag = vnameInternGlobalLiteral( "HexList" );
  info.hexList = (vlistitem *) vdialogFindItem( dialog, tag );
  vlistitemSetData( info.hexList, &info );
  _initHexList( &info, block, blockSize );

  tag = vnameInternGlobalLiteral( "ExpandList" );
  info.expandList = (vlistitem *) vdialogFindItem( dialog, tag );
  vlistitemSetData( info.expandList, &info );
  _initExpandList( info.expandList );

  tag = vnameInternGlobalLiteral( "MenuBar" );
  info.menubar = (vmenubar *) vdialogFindItem( dialog, tag );
  vmenubarSetData( info.menubar, &info );
  _initMenus( info.menubar );

  info.expandItemList = vdialogCreateItemList();
  vdialogSetItemListOwner( info.expandItemList, 
			   vdialogGetItemObject( (vdialogItem *) 
						 info.expandList ), 
			   &ownerFuncs );

  /*
   *  Open dialog
   */
  vdialogSetNotify( dialog, _dialogNotify );
  vdialogSetData( dialog, &info );
  vdialogOpen( dialog );
}

/*****************************************************************
  _initBlockData

  Init byte stream data to edit
*****************************************************************/
static void _initBlockData()
{
  int	 i;
  int	 value;

  blockSize = 512;
  block = (vbyte *) vmemAlloc( blockSize );
  for ( i = value = 0; i < 512; i++ )
    {
      block[i] = value++;
      if ( value == 256 )
	value = 0;
    }
}

/*****************************************************************
    ************************* MAIN **************************
*****************************************************************/
int main( int argc, char *argv[] )
{
  vfsPath		**paths;
  int			  numFiles;

  vstartup( argc, argv );
  resFile = vapplicationGetResources( vapplicationGetCurrent() );

  vfsGetArgs(&numFiles, (const vfsPath ***) &paths);
  if ( numFiles == 2 )
    vexWITH_HANDLING
      {
	examineResFile = vresourceOpenFile( paths[1], vfsOPEN_READ_ONLY );
      }
    vexON_EXCEPTION
      {
        examineResFile = vresourceNULL;
      }
    vexEND_HANDLING;

  if ( examineResFile == vresourceNULL )
    examineResFile = resFile;

  _initBlockData();
  _openDialog();
  veventProcess();

  if ( examineResFile != resFile )
    vresourceCloseFile( examineResFile );

  vdialogDestroyItemList( info.expandItemList );

  if ( entryPool )
    vpoolDestroy( entryPool );
  vmemFree( block );

  exit( EXIT_SUCCESS );
  return( EXIT_FAILURE );
}


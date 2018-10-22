/* $Id: drag.c,v 1.8 1996/09/25 18:59:11 scotth Exp $ */

/*
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
 * copyright notice in the in the form of "Copyright 1992 Visix Software Inc.,
 * 11440 Commerce Park Drive, Reston, VA  22091. All Rights Reserved" appears
 * in all copies, (ii) both the copyright notice and this permission notice
 * appear in supporting documentation and (iii) you are a valid licensee of
 * Galaxy Application Environment.
 */

#ifndef  vportINCLUDED
#include <vport.h>		/* for v*HEADER */
#endif

#ifndef  vstdlibINCLUDED
#include vstdlibHEADER		/* for exit, EXIT_SUCCESS */
#endif

#ifndef  vdebugINCLUDED
#include vdebugHEADER
#endif

#ifndef  vapplicationINCLUDED
#include vapplicationHEADER
#endif

#ifndef  vclassINCLUDED
#include vclassHEADER
#endif

#ifndef  vimageINCLUDED
#include vimageHEADER
#endif

#ifndef  veventINCLUDED
#include veventHEADER
#endif

#ifndef  vwindowINCLUDED
#include vwindowHEADER
#endif

#ifndef  vdialogINCLUDED
#include vdialogHEADER
#endif

#ifndef  vlistINCLUDED
#include vlistHEADER
#endif

#ifndef  vlistviewINCLUDED
#include vlistviewHEADER
#endif

#ifndef  vlistitemINCLUDED
#include vlistitemHEADER
#endif

#ifndef  vmenuINCLUDED
#include vmenuHEADER
#endif

#ifndef  vmenubarINCLUDED
#include vmenubarHEADER
#endif

#ifndef  vstartupINCLUDED
#include vstartupHEADER
#endif

#ifndef  vnumINCLUDED
#include vnumHEADER
#endif

#ifndef  vdragINCLUDED
#include vdragHEADER
#endif

#if (vdebugDEBUG)
static const char * const	 _dragsampleTag = "main";
#define vdebugTAG		 _dragsampleTag
#endif

#define ABS(x)           ( (x) > 0 ? (x) : ( -(x) ) )

/*
 *  Type and structure declarations for drag list item
 */
typedef void (*dragListDropNotify)( vlistitem *listitem, int row, 
				    vwindow *from, vwindow *to,
				    vpoint *mousePt, vevent *event );

typedef struct dragListItem{
  vlistitem	 		 listitem;
  vpoint       	 		 startPt;
  int		 		 row;
  dragListDropNotify	 	 dragNotify;
} dragListItem;

/*
 *  Variable declarations
 */
static vlistitemClass		*dragListItemClass	= NULL;
static vdialogItemClass		*imageItemClass		= NULL;
static vdialog			*dropDialog;
static vdialog			*dragDialog;
static vcursor			*goodDropCursor;
static vcursor			*badDropCursor;
static vcursor			*originalCursor;

/*
 * External references:
 */

/****************************************************************
  _handleWindowDrop

  NOTE:  There are many ways to handle drop for a window and this
  is one.  You can always tell the type of window by its class or 
  the window's type tag.  You could also add a method for a 
  window for drop or create a user event.
*****************************************************************/
static void _handleWindowDrop( vwindow *from, vwindow *to, vpoint *mousePt,
			       vevent *event, const vname *dragType, 
			       const void *data )
{
  vimage	*image;
  const vchar	*str;
  vdialog	*dialog;
  vdialogItem	*item = NULL;
  vrect		 r;
  int		 w, h;

  if ( vwindowGetTag( to ) == vnameInternGlobalLiteral( "DROP_DIALOG" ) )
    {
      dialog = (vdialog *) to;
      if ( dragType == vname_Image )
	{
	  image = (vimage *) data;
	  item = vdialogCreateBoxItem();
	  vdialogSetItemImage( item, image );
	}
      else if ( dragType == vname_Title )
	{
	  str = (const vchar *) data;
	  item = vdialogCreateLabelItem();
	  vdialogSetItemTitle( item, str );
	}

      r = *vdialogGetItemRect( item );
      vdialogGetItemNaturalSize( item, &w, &h );
      r.x = mousePt->x - w / 2;
      r.y = mousePt->y - h / 2;
      r.w = w; r.h = h;
      vdialogSetItemRect( item, &r );
      vdialogAppendItem( dialog, item );
    }
}

/*****************************************************************
  _setDragListItemDropNotify
*****************************************************************/
static void _setDragListItemDropNotify( vlistitem *listitem, 
				       dragListDropNotify notify )
{
  dragListItem		*dragItem;

  dragItem = (dragListItem *) listitem;
  dragItem->dragNotify = notify;
}

/*****************************************************************
  _handleDragListItemButtonDown
*****************************************************************/
static int _handleDragListItemButtonDown( vlistitem *listitem, vevent *event )
{
  int			 row, col;
  int			 oldrow;
  dragListItem		*dragItem;

  dragItem = (dragListItem *) listitem;

  /*
   *  If the event binding is not drag then let super class handle it
   */
  if ( veventGetBinding( event ) != vname_Drag )
    return( vclassSendSuper( dragListItemClass, vdialogHANDLE_ITEM_BUTTON_DOWN,
			     (listitem, event) ) );

  /*
   *  If mouse point is in list content rect select proper cell and continue
   *  until we break a certain hysterisis otherwise let super class handle it
   */
  vpointSet( veventGetPointerX( event ), veventGetPointerY( event ), 
	     &dragItem->startPt );
  if ( vrectContainsPoint( vlistviewGetListRect( vlistitemGetView( listitem )),
			   dragItem->startPt.x, dragItem->startPt.y ) )
    {
      vlistviewMapPointToCell( vlistitemGetView( listitem ), 
			       &dragItem->startPt, &row, &col);
      if ( ( oldrow = vlistitemGetSelectedRow( listitem ) ) != row )
	{
	  vlistitemSelectRow( listitem, row );
	  if ( row != -1 )
	    vlistviewDrawCell( vlistitemGetView( listitem ), row, 0 );
	  if ( oldrow != -1 )
	    vlistviewDrawCell( vlistitemGetView( listitem ), oldrow, 0 );
	}

      vwindowSyncEvents();
      dragItem->row = vlistitemGetSelectedRow( listitem );
    }
  else
    return( vclassSendSuper( dragListItemClass, 
			     vdialogHANDLE_ITEM_BUTTON_DOWN, 
			     (listitem, event) ) );

  return( TRUE );
}

/*****************************************************************
  _handleDragListItemButtonUp
*****************************************************************/
static int _handleDragListItemButtonUp( vlistitem *listitem, vevent *event )
{
  /*
   *  If binding is not drag then let super class handle it
   */
  if ( veventGetBinding( event ) != vname_Drag )
    return( vclassSendSuper( dragListItemClass, 
			     vdialogHANDLE_ITEM_BUTTON_UP, 
			     (listitem, event) ) );

  return( TRUE );
}

/*****************************************************************
  _dragListDetailNotify

  Notify procedure for drag to give feedback about potential drop site.
*****************************************************************/
static int _dragListDetailNotify( vdrag *drag, vwindow *from, vwindow *to,
				   vevent *event )
{
  vcursor	*cursor;

  if ( to && vwindowGetTag( to ) == vnameInternGlobalLiteral( "DROP_DIALOG" ) )
    cursor = goodDropCursor;
  else
    cursor = badDropCursor;
  vapplicationSetCursor( vapplicationGetCurrent(), cursor );

  return( 0 );
}

/*****************************************************************
  _dragListNotify

  Notify procedure for finished drag in drag list item
*****************************************************************/
static void _dragListNotify( vdrag *drag, vwindow *from, vwindow *to,
			     vevent *event )
{
  dragListItem		*dragItem;
  vpoint		 mousePt;

  dragItem = (dragListItem *) vdragGetData( drag );
  vpointSet( veventGetPointerX( event ), 
	     veventGetPointerY( event ), &mousePt );

  /*
   *  Call list drop notify
   */
  if ( dragItem->dragNotify )
    dragItem->dragNotify( (vlistitem *) dragItem, dragItem->row,
			  from, to, &mousePt, event );

  /*
   *  Destroy drag
   */
  vdragDestroy( drag );

  /*
   *  Restore original window cursor
   */
  vapplicationSetCursor( vapplicationGetCurrent(), originalCursor );
}

/*****************************************************************
  _dragListDraw

  Draw procedure for drag in a drag list item
*****************************************************************/
static void _dragListDraw( vdrag *drag, vrect *draw )
{
  dragListItem		*listitem;

  listitem = (dragListItem *) vdragGetData( drag );

  vdrawGSave();
  vdrawSetLineWidth( 1 );

  /*
   *  Outline list cell rect
   */
  vdrawRectsStrokeInside( draw, 1 );
  
  /*
   *  Draw list cell 
   */
  vlistviewDrawCellContents( (vlistview *) listitem, listitem->row, 0,
			     FALSE, draw );
  vdrawGRestore();
}

/*****************************************************************
  _handleDragListItemDrag
*****************************************************************/
static int _handleDragListItemDrag( vlistitem *listitem, vevent *event )
{
  vdrag	      		*drag;
  vrect			 r;
  dragListItem		*dragItem;
  vwindow		*window;

  dragItem = (dragListItem *) listitem;

  /*
   *  If binding is not drag then let super class handle it
   */
  if ( veventGetBinding( event ) != vname_Drag )
    return( vclassSendSuper( dragListItemClass, vdialogHANDLE_ITEM_DRAG, 
			     (listitem, event) ) );

  /*
   *  If we are dragging and break hysterisis then start drag
   */
  if ( ( dragItem->row != -1 ) &&
       ( ABS( veventGetPointerX( event ) - dragItem->startPt.x ) > 4 ||
         ABS( veventGetPointerY( event ) - dragItem->startPt.y ) > 4 ) )
    {
      /*
       *  Get list cell rectangle
       */
      vlistviewGetCellRect( vlistitemGetView( listitem ), 
			    vlistitemGetSelectedRow( listitem ), 0, &r );

      /*
       *  Store away original window cursor
       */
      window = vdialogDetermineItemWindow( vlistitemGetItem( listitem ) );
      originalCursor = vapplicationGetCursor( vapplicationGetCurrent() );

      /*
       *  Create drag and initialize
       */
      drag = vdragCreate();
      vdragSetData( drag, dragItem );
      vdragSetMaxSize( drag, r.w, r.h );
      vdragSetDrawProc( drag, _dragListDraw );
      vdragSetNotify( drag, _dragListNotify );
      vdragSetDetail( drag, _dragListDetailNotify );

      /*
       *  Start drag
       */
      vdragSetOffset( drag, 
		      veventGetPointerX( event ) - r.x, 
		      veventGetPointerY( event ) - r.y );
      vdragStart( drag, event );
    }

  return( TRUE );
}

/*****************************************************************
  _initDragListItem
*****************************************************************/
static void _initDragListItem( vlistitem *listitem )
{
  dragListItem		*dragItem;

  dragItem = (dragListItem *) listitem;

  /*
   * initialize from superclass
   */
  vclassSendSuper( dragListItemClass, vobjectINIT, (listitem) );
  
  /*
   * initialize editor fields
   */
  dragItem->dragNotify 	= NULL;
  dragItem->row		= -1;
}

/*****************************************************************
  _loadInitDragListItem
*****************************************************************/
static void _loadInitDragListItem( vlistitem *listitem,
				   vresource resource )
{
  dragListItem		*dragItem;

  dragItem = (dragListItem *) listitem;

  /*
   * initialize from superclass
   */
  vclassSendSuper( dragListItemClass, vobjectLOAD_INIT, (listitem, resource) );
  
  /*
   * initialize editor fields
   */
  dragItem->dragNotify 	= NULL;
  dragItem->row		= -1;
}

/*****************************************************************
  _initDragListItemClass
*****************************************************************/
static void _initDragListItemClass(void)
{
  dragListItemClass = vclassReproduce( vlistitemGetDefaultClass() );
  vclassSetNameScribed( dragListItemClass, 
		        vcharScribeLiteral( "dragListItemClass" ) );
  vclassSetObjectSize( dragListItemClass, sizeof( dragListItem ) );

  vclassSet( dragListItemClass, vobjectINIT, _initDragListItem );
  vclassSet( dragListItemClass, vobjectLOAD_INIT, _loadInitDragListItem );
  vclassSet( dragListItemClass, vdialogHANDLE_ITEM_BUTTON_DOWN, 
	     _handleDragListItemButtonDown );
  vclassSet( dragListItemClass, vdialogHANDLE_ITEM_BUTTON_UP, 
	     _handleDragListItemButtonUp );
  vclassSet( dragListItemClass, vdialogHANDLE_ITEM_DRAG, 
	     _handleDragListItemDrag );
}

/*****************************************************************
  _dragImageDetailNotify

  Notify procedure for drag to give feedback about potential drop site.
*****************************************************************/
static int _dragImageDetailNotify( vdrag *drag, vwindow *from, vwindow *to,
				    vevent *event )
{
  vcursor	*cursor; 

  if ( to && vwindowGetTag( to ) == vnameInternGlobalLiteral( "DROP_DIALOG" ) )
    cursor = goodDropCursor;
  else
    cursor = badDropCursor;
  vapplicationSetCursor( vapplicationGetCurrent(), cursor );

  return( 0 );
}

/*****************************************************************
  _dragImageNotify

  Notify procedure for finished drag in image item
*****************************************************************/
static void _dragImageNotify( vdrag *drag, vwindow *from, vwindow *to,
			      vevent *event )
{
  vimage		*image;
  vpoint	         mousePt;

  image = (vimage *) vdragGetData( drag );

  /*
   *  Handle drop
   */
  vpointSet( veventGetPointerX( event ), veventGetPointerY( event ), 
	     &mousePt );
  _handleWindowDrop( from, to, &mousePt, event, vname_Image, image );

  /*
   *  Destroy drag
   */
  vdragDestroy( drag );

  /*	
   *  Restore original window cursor
   */
  vapplicationSetCursor( vapplicationGetCurrent(), originalCursor );
}

/*****************************************************************
  _dragImageDraw
  
  Draw procedure for drag in a drag list item
*****************************************************************/
static void _dragImageDraw( vdrag *drag, vrect *draw )
{
  vimage		*image;

  image = (vimage *) vdragGetData( drag );

  vdrawGSave();
  vdrawMoveTo( draw->x, draw->y );
  vdrawImageIdent( image );
  vdrawGRestore();
}

/*****************************************************************
  _handleImageItemButtonDown
*****************************************************************/
static int _handleImageItemButtonDown( vdialogItem *item, vevent *event )
{
  vdrag	      		*drag;
  vimage		*image;
  const vrect	       	*r;

  /*
   *  If the event binding is not drag then let super class handle it
   */
  if ( veventGetBinding( event ) != vname_Drag )
    return( vclassSendSuper( imageItemClass, 
			     vdialogHANDLE_ITEM_BUTTON_DOWN, 
			     (item, event) ) );

  /*
   *  Get image to drag
   */
  image = vdialogGetItemImage( item );
  r = vdialogGetItemRect( item );

  /*
   *  Create drag and initialize
   */
  drag = vdragCreate();
  vdragSetData( drag, image );
  vdragSetMaxSize( drag, vimageGetWidth( image ), vimageGetHeight( image ) );
  vdragSetDrawProc( drag, _dragImageDraw );
  vdragSetNotify( drag, _dragImageNotify);
  vdragSetDetail( drag, _dragImageDetailNotify );

  /*
   *  Store away original window cursor
   */
  originalCursor = vapplicationGetCursor( vapplicationGetCurrent() );

  /*
   *  Start drag
   */
  vdragSetOffset( drag, 
		  veventGetPointerX( event ) - r->x,
		  veventGetPointerY( event ) - r->y );
  vdragStart( drag, event );

  return( TRUE );
}

/****************************************************************
  _initImageItemClass

  Initialize class for image drag item
*****************************************************************/
static void _initImageItemClass(void)
{
  imageItemClass = vclassReproduce( vdialogGetBoxItemClass() );
  vclassSetNameScribed( imageItemClass, 
		        vcharScribeLiteral( "imageItemClass" ) );

  vclassSet( imageItemClass, vdialogHANDLE_ITEM_BUTTON_DOWN, 
	     _handleImageItemButtonDown );
}

/****************************************************************
  _quitNotify

  Notify for quit menu item
*****************************************************************/
static void _quitNotify( vmenuItem *item, vevent *event )
{
  veventStopProcessing();
}

/****************************************************************
  _handleListDrop

  Handles drag list item's drop
*****************************************************************/
static void _handleListDrop( vlistitem *listitem, int row, 
			     vwindow *from, vwindow *to, 
			     vpoint *mousePt, vevent *event )
{
  int	 	 nrow, ncol;
  const vchar	*str;

  /*	
   *  If drop is in same dialog and in listitem then just move row
   */
  if ( to == from && vdialogItemContainsPoint( vlistitemGetItem( listitem ),
					       mousePt->x, mousePt->y ) )
    {
      /*
       *  If drop is in same cell then return
       */
      vlistviewMapPointToCell( vlistitemGetView( listitem ), 
			       mousePt, &nrow, &ncol );
      if ( nrow == row )
	return;
      
      /*
       *  Move row
       */
      vlistMoveRow( vlistitemGetList( listitem ), row, nrow );
      return;
    }

  /*
   *  Handle drop into another dialog
   */
  str = vlistitemGetValueAt( listitem, row );
  _handleWindowDrop( from, to, mousePt, event, vname_Title, str );
}

/****************************************************************
  _dialogNotify
*****************************************************************/
static void _dialogNotify( vdialog *dialog, vevent *event )
{
  if ( veventGetType( event ) == veventWINDOW_STATE && 
       veventIsClose( event ) )
    veventStopProcessing();
}

/****************************************************************
  _openDragDialog
*****************************************************************/
static void _openDragDialog( vresource resfile )
{
  vresource	res;
  vlistitem	*listItem;
  vmenubar	*menubar;
  vmenu		*menu;
  vmenuItem	*mitem;
  vdialog	*dialog;
  int		 i;

  /*
   *  Load drag dialog from resource file
   */
  res = vresourceGet( resfile, vnameInternGlobalLiteral( "DragDialog" ) );
  dragDialog = dialog = vdialogLoad( res );

  /*
   *  Load list item
   */
  listItem = (vlistitem *)
    vdialogFindItem( dialog, vnameInternGlobalLiteral( "List Item" ) );
  _setDragListItemDropNotify( listItem, _handleListDrop );

  /*
   *  Add some strings to list item
   */
  for ( i = 0; i < 30; i++ )
    vlistitemAppendScribed( listItem,
      vscribeScribeMulti( vcharScribeLiteral( "New Item " ), 
			  vnumScribeInt( i ), NULL ) );

  /*
   *  Set quit notify for quit menu item
   */
  menubar = (vmenubar *) 
    vdialogFindItem( dialog, vnameInternGlobalLiteral( "Menu Bar" ) );  
  menu = vmenubarFindMenu( menubar, vnameInternGlobalLiteral( "FileMenu" ) );
  mitem = vmenuFindItem( menu, vnameInternGlobalLiteral( "Quit" ) );
  vmenuSetItemNotify( mitem, _quitNotify );

  /*
   *  Open dialog 
   */
  vdialogSetNotify( dialog, _dialogNotify );
  vdialogOpen( dialog );
}

/****************************************************************
  _openDropDialog
*****************************************************************/
static void _openDropDialog( vresource resfile )
{
  vresource	 res;
  vdialog     	*dialog;

  res = vresourceGet( resfile, vnameInternGlobalLiteral( "DropDialog" ) );
  dropDialog = dialog = vdialogLoad( res );
  vdialogPlace( dialog, dragDialog, 
	        vrectPLACE_RIGHT | vrectPLACE_NEAR, 
	        vrectPLACE_ALIGN | vrectPLACE_TOP );
  vdialogSetNotify( dialog, _dialogNotify );
  vdialogOpen( dialog );
}

/****************************************************************
  _cleanup
*****************************************************************/
static void _cleanup(void)
{
  vdialogDestroy( dropDialog );
  vdialogDestroy( dragDialog );
  vcursorDestroy( badDropCursor );
  vcursorDestroy( goodDropCursor );
}

/****************************************************************
 **********************     MAIN    ****************************
*****************************************************************/
int main( int argc, char *argv[] )
{
  vresource  	 resFile;
  vresource 	 res;

  /*
   * The Exception Manager must be started before any vex or vdebug calls
   */
  vexStartup();
  vdebugTraceEnter( main );
  
  /*
   *  Startup classes
   */
  vstartup( argc, argv );

  /*
   *  Initialize internal classes
   */
  _initDragListItemClass();
  _initImageItemClass();

  /*
   *  Get application resource file 
   */
  resFile  = vapplicationGetResources( vapplicationGetCurrent() );

  /*
   *  Load cursors
   */
  res = vresourceGet( resFile, vnameInternGlobalLiteral( "Cursors" ) );
  goodDropCursor = 
    vcursorLoad( vresourceGet( res, vnameInternGlobalLiteral( "GoodDrop" ) ) );
  badDropCursor = 
    vcursorLoad( vresourceGet( res, vnameInternGlobalLiteral( "BadDrop" ) ) );

  /*
   *  Open dialogs
   */
  _openDragDialog( resFile );
  _openDropDialog( resFile );
  
  /*
   *  Start event loop
   */
  veventProcess();

  /*
   *  Clean up
   */
  _cleanup();

  vdebugTraceLeave();
  exit( EXIT_SUCCESS );
  return( EXIT_FAILURE );
}

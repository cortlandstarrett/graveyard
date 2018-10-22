/* $Id: listtest.c,v 1.6 1997/10/17 19:34:57 hoyle Exp $ */

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

/****************************************************************************
 * Executable Name:    listtest
 * Source Files:       listtest.c
 * Header Files:
 * Resource Files:     
 *
 * Managers Illustrated:
 *              Notebook
 *      
 *
 * Description Of Sample:
 *
 * Illustrates a notebook with a listitem as a tab set.  Each cell in the 
 * listitem represents a tab in the notebook.
 *
 * History:             Written for 2.1 release   11/10/94
 * $Log: listtest.c,v $
 * Revision 1.6  1997/10/17  19:34:57  hoyle
 * Fixed bug where accessing NULL tabset.
 *
 * Revision 1.5  1995/02/02 19:22:43  hoyle
 * Changed resource file to have pages under notebook instead of placing
 * them in notebook in code.
 *
 * Revision 1.4  1994/12/15  17:32:59  hoyle
 * Changed setting of class style since it changed to a pointer instead of
 * a structure reference.
 *
 * Revision 1.3  1994/12/14  15:53:30  hoyle
 * Added the standard sample disclaimer, purpose and comments.
 *
 *
 *****************************************************************************/

#include <vport.h>

#ifndef vstdlibINCLUDED
#include vstdlibHEADER
#endif

#ifndef vapplicationINCLUDED
#include vapplicationHEADER
#endif

#ifndef vstartupINCLUDED
#include vstartupHEADER
#endif

#ifndef vclassINCLUDED
#include vclassHEADER
#endif

#ifndef veventINCLUDED
#include veventHEADER
#endif

#ifndef vdialogINCLUDED
#include vdialogHEADER
#endif

#ifndef vcontainerINCLUDED
#include vcontainerHEADER
#endif

#ifndef vlistitemINCLUDED
#include vlistitemHEADER
#endif

#ifndef vnotebookINCLUDED
#include vnotebookHEADER
#endif

#define _listtestINSET 	5

vnotebookClass		*listtestClass = NULL;
vresource		 resfile;
vdialog			*dialog;
vnotebook		*notebook;
vnotebookStyle		*_defaultStyle = NULL;

/*****************************************************************
  _findCell

  Returns the listitem cell whose data pointer contains data.
*****************************************************************/
static int _findCell( vlistitem *listitem, void *data )
{
  int	 	 i, count = vlistitemGetRowCount( listitem );

  for ( i = 0; i < count; i++ )
    if ( (void *) vlistitemGetValueAt( listitem, i ) == data )
      return( i );
  return( -1 );
}

/*****************************************************************
  _listtestSetTabSetTabSelected

  Method override for vnotebookSET_TABSET_TAB_SELECTED.
    - Sets the tab to be the selected in the listitem.
*****************************************************************/
static void _listtestSetTabSetTabSelected( vnotebook *notebook,
					   vdialogItem *tabset,
					   vnotebookTab *tab )
{
  vlistitem	*listitem = (vlistitem *) tabset;
  int	    	 row;

  if ( listitem && ( row = _findCell( listitem, tab ) ) != -1 )
    {
      vlistitemSelectRow( listitem, row );
      vlistviewScrollSelectionIntoView( (vlistview *) listitem );
    }
}

/*****************************************************************
  _listtestScrollTabSetTabIntoView

  Method override for vnotebookSCROLL_TABSET_TAB_INTO_VIEW
    - Scroll the tab into view in the listitem.
*****************************************************************/
static void _listtestScrollTabSetTabIntoView( vnotebook *notebook,
					     vdialogItem *tabset, 
					     vnotebookTab *tab )
{
  vlistitem	*listitem = (vlistitem *) tabset;

  if ( listitem )
    vlistviewScrollSelectionIntoView( (vlistview *) listitem );
}

/*****************************************************************
  _listtestGetTabSetClipRects

  Method override for vnotebookGET_TABSET_CLIP_RECTS
    - We don't need to clip anything out, so return NULL
*****************************************************************/
static vrect *_listtestGetTabSetClipRects( vnotebook *notebook, 
					   vdialogItem *tabset,
					   int *rectCount )
{
  return( NULL );
}

/*****************************************************************
  _listtestGetTabSetTabCount

  Method override for vnotebookGET_TABSET_TAB_COUNT
    - Returns the number of tabs in the listitem
*****************************************************************/
static int _listtestGetTabSetTabCount( vnotebook *notebook, 
				       vdialogItem *tabset )
{
  vlistitem	*listitem = (vlistitem *) tabset;

  return( vlistitemGetRowCount( listitem ) );
}

/*****************************************************************
  _listtestGetTabSetTabAt

  Method override for vnotebookGET_TABSET_TAB_AT
    - Returns the tab at the index specified in the listitem
*****************************************************************/
static vnotebookTab *_listtestGetTabSetTabAt( vnotebook *notebook, 
					      vdialogItem *tabset, int index )
{
  vlistitem	*listitem = (vlistitem *) tabset;

  return( (vnotebookTab *) vlistitemGetValueAt( listitem, index ) );
}

/*****************************************************************
  _listtestDeleteTabSetTab

  Method override for vnotebookDELETE_TABSET_TAB
    - Removes the tab from the listitem
*****************************************************************/
static void _listtestDeleteTabSetTab( vnotebook *notebook, vdialogItem *tabset,
				      vnotebookTab *tab )
{
  vnotebookTab		*temp;
  int			 count, i;
  int			 found = FALSE;
  vlistitem		*listitem = (vlistitem *) tabset;

  /*
   *  Find the tab in the listitem
   */
  count = vlistitemGetRowCount( listitem );
  for ( i = count - 1; i >= 0; i-- )
    {
      temp = (vnotebookTab *) vlistitemGetValueAt( listitem, i );
      if ( ( found = ( temp == tab ) ) )
	break;
    }

  /*
   *  Remove the tab from the listitem
   */
  if ( found )
    {
      vlistitemRemoveRow( listitem, i );
      vnotebookSetTabTabSet( tab, NULL );
    }
}

/*****************************************************************
  _listtestAddTabSetTab

  Method override for vnotebookADD_TABSET_TAB
    - Adds the tab to the listitem
*****************************************************************/
static void _listtestAddTabSetTab( vnotebook *notebook, vdialogItem *tabset,
				   vnotebookTab *tab )
{
  vlistitem		*listitem = (vlistitem *) tabset;

  vlistitemAppend( listitem, (const vchar *) tab );
  vnotebookSetTabTabSet( tab, tabset );
}

/*************************************************************
  _getCellName

  Returns the name of the tab that the listitem cell represents
**************************************************************/
static const vchar *_getCellName( vlist *list, int row, int col )
{
  vnotebookTab		*tab;

  tab = (vnotebookTab *) vlistGetCellValue( list, row, col );
  return( ( tab == NULL ) ? vcharGetEmptyString() :
	  vnotebookGetTabTitle( tab ) );
}

/*************************************************************
  _drawCell

  Draws a tab into a listitem's cell
**************************************************************/
static void _drawCell( vlistitem *listitem, int row, int col, 
		       int selected, vrect *rect )
{
  vnotebookTab	*tab;
  vrect		 temp;
  int		 ch;

  tab = (vnotebookTab *) vlistitemGetValueAt( listitem, row );
  if ( tab == NULL )
    return;
  
  ch = tab->contentH;
  vrectSet( rect->x + 5, rect->y + rect->h / 2 - ch / 2, 
	    rect->w - 5, ch, &temp );

  vnotebookDrawTabContent( tab, &temp );
}

/*****************************************************************
  _doListNotify

  Listitem notification function
*****************************************************************/
static void _doListNotify( vlistitem *listitem, int notifyType )
{
  int		 	 row;
  vnotebook	       	*notebook;
  vnotebookTab		*tab;
  vnotebookPage		*page;

  if ( notifyType == vlistviewSELECTION_HAS_CHANGED &&
       ( row = vlistitemGetSelectedRow( listitem ) ) != 
       vlistitemNO_CELLS_SELECTED )
    {
      tab = (vnotebookTab *) vlistitemGetValueAt( listitem, row );
      if ( tab )
	{
	  page = vnotebookGetTabPage( tab );
	  notebook = vnotebookDeterminePageNotebook( page );
	  vnotebookSetTabSetTabSelected( notebook, 
					 vnotebookGetTabTabSet( tab ), tab );
	  vnotebookSetPageCurrent( page );
	}
    }
}

/*****************************************************************
  _listtestCreateTabSet

  Method override for vnotebookCREATE_TABSET
    - We create a listitem for the tab set and set it up appropriately
*****************************************************************/
static vdialogItem *_listtestCreateTabSet( vnotebook *notebook, int whichTabs )
{
  vlistitem	*listitem;

  listitem = vlistitemCreate();

  vlistSetCellNamer( vlistitemGetList( listitem ), _getCellName );
  vlistitemSetCellContentProc( listitem, _drawCell );
  vlistitemSetSelectMethod( listitem, vlistONE_ONLY_SELECTION );
  vlistitemSetSelectNotify( listitem, _doListNotify );

  return( vlistitemGetItem( listitem ) );
}

/*****************************************************************
  _listtestGetTabSetSize

  Method override for vnotebookGET_TABSET_SIZE
*****************************************************************/
static void _listtestGetTabSetSize( vnotebook *notebook, vdialogItem *tabset,
				     int *w, int *h )
{
  vnotebookGetMaxTabSetTabSize( notebook, tabset, w, h );
  *w += 30;
}

/*****************************************************************
  _listtestCalcTabSetRect

  Method override for vnotebookCALC_TABSET_RECT.
*****************************************************************/
static void _listtestCalcTabSetRect( vnotebook *notebook, vdialogItem *tabset,
				     vrect *rect )
{
  vrect		 pageRect;
  const vrect	*r;

  r = vdialogGetItemRect( vnotebookGetItem( notebook ) );
  vnotebookCalcPageRect( notebook, &pageRect );
  vrectSet( r->x, r->y,
	    pageRect.x - r->x - _listtestINSET, pageRect.h, rect );
}

/*****************************************************************
  _listtestGetBorderSizes

  Method override for vnotebookGET_PAGE_BORDER_SIZES
    - We don't need to inset the border any so we return 0
*****************************************************************/
static void _listtestGetBorderSizes( vnotebook *notebook, 
				      int *top, int *left,
				      int *bot, int *right)
{
  *top = *left = *bot = *right = 0;
}

/*****************************************************************
  _listtestGetDecorationSizes

  Method override for vnotebookGET_PAGE_DECORATION_SIZES
    - Account for the list item on the left side
*****************************************************************/
static void _listtestGetDecorationSizes( vnotebook *notebook, 
					  int *top, int *left,
					  int *bot, int *right)
{
  int		 tw = 0, th = 0;

  *top = *left = *bot = *right = 0;
  if ( !vdialogItemHasBorder( vnotebookGetItem( notebook ) ) )
    return;

  if ( vnotebookGetMajorTabSet( notebook ) )
    vnotebookGetTabSetSize( notebook, vnotebookGetMajorTabSet( notebook ), 
			    &tw, &th );
  *left = _listtestINSET + tw;
}

/*****************************************************************
  _listtestRecalcTabSetTabs

  Method override for vnotebookRECALC_TABSET_TABS
    - We want to make sure that the row height is set properly for listitem
*****************************************************************/
static void _listtestRecalcTabSetTabs( vnotebook *notebook, vdialogItem *item )
{
  int		 w, h;

  vclassSendSuper( listtestClass, vnotebookRECALC_TABSET_TABS, 
		   (notebook, item) );

  vnotebookGetMaxTabSetTabSize( notebook, item, &w, &h );
  vlistitemSetRowHeight( (vlistitem *) item, h );
}

/*****************************************************************
  _listtestDrawBinder

  Method override for vnotebookDRAW_BINDER
    - We don't want a binder so we do nothing
*****************************************************************/
static void _listtestDrawBinder( vnotebook *notebook )
{
}

/*****************************************************************
  _listtestShutdown
*****************************************************************/
#if vmemBALANCE
static void _listtestShutdown( void )
{
  if ( _defaultStyle )
    vnotebookDestroyStyle( _defaultStyle );
}
#endif

/*****************************************************************
  _getlisttestClass
*****************************************************************/
vnotebookClass *_getlisttestClass( void )
{
  vnotebookStyle		*style;

  if ( listtestClass == NULL )
    {
      listtestClass = vclassReproduce( vnotebookGetDefaultClass() );
      vclassSetNameScribed( listtestClass, 
			    vcharScribeLiteral( "listtestNotebook" ) );
      
      vclassSet( listtestClass, vnotebookGET_TABSET_CLIP_RECTS,
		 _listtestGetTabSetClipRects );
      vclassSet( listtestClass, vnotebookADD_TABSET_TAB,
		 _listtestAddTabSetTab );
      vclassSet( listtestClass, vnotebookDELETE_TABSET_TAB,
		 _listtestDeleteTabSetTab );
      vclassSet( listtestClass, vnotebookGET_TABSET_TAB_AT,
		 _listtestGetTabSetTabAt );
      vclassSet( listtestClass, vnotebookGET_TABSET_TAB_COUNT,
		 _listtestGetTabSetTabCount );
      vclassSet( listtestClass, vnotebookCREATE_TABSET,
		 _listtestCreateTabSet );
      vclassSet( listtestClass, vnotebookSET_TABSET_TAB_SELECTED,
		 _listtestSetTabSetTabSelected );
      vclassSet( listtestClass, vnotebookSCROLL_TABSET_TAB_INTO_VIEW,
		 _listtestScrollTabSetTabIntoView );
      vclassSet( listtestClass, vnotebookRECALC_TABSET_TABS,
		 _listtestRecalcTabSetTabs );

      vclassSet( listtestClass, vnotebookGET_PAGE_BORDER_SIZES, 
		 _listtestGetBorderSizes );
      vclassSet( listtestClass, vnotebookGET_PAGE_DECORATION_SIZES, 
		_listtestGetDecorationSizes );

      vclassSet( listtestClass, vnotebookCALC_TABSET_RECT, 
		 _listtestCalcTabSetRect );
      vclassSet( listtestClass, vnotebookGET_TABSET_SIZE, 
		 _listtestGetTabSetSize );
      vclassSet( listtestClass, vnotebookDRAW_BINDER, 
		 _listtestDrawBinder );

      /*
       *  Override the default class style to set up what we want
       */
      style = _defaultStyle =
	vnotebookCloneStyle( vnotebookGetClassStyle( listtestClass ) );
      vnotebookSetStyleFolio( style, FALSE );
      vnotebookSetStylePageButtons( style, FALSE );
      vnotebookSetStyleTabs( style, vnotebookTABS_PAGE );
      vnotebookSetStylePageBorders( style, TRUE );
      vclassSet( listtestClass, vnotebookCLASS_STYLE, style );

#if vmemBALANCE
      vclientRegisterShutdown( _listtestShutdown );
#endif
    }

  return( listtestClass );
}

/*****************************************************************
  _dialogNotify
*****************************************************************/
static void _dialogNotify( vdialog *dialog, vevent *event )
{
  if ( veventGetType( event ) == veventWINDOW_STATE && veventIsClose( event ) )
    veventStopProcessing();
}

/*****************************************************************
  _openNotebookDialog
*****************************************************************/
static void _openNotebookDialog( void )
{
  /*
   *  Load dialog and set notify
   */
  dialog = vdialogLoad( vresourceGet( resfile, vname_Dialog ) );
  vdialogSetNotify( dialog, _dialogNotify );

  /*
   *  Find notebook in dialog
   */
  notebook = (vnotebook *)
    vdialogFindItem( dialog, vnameInternGlobalLiteral( "Notebook" ) );

  vdialogOpen( dialog );
}

/*****************************************************************
  main
*****************************************************************/
int main( int argc, char **argv )
{
  /*
   *  Startup managers
   */
  vstartup( argc, argv );

  resfile  = vapplicationGetResources( vapplicationGetCurrent() );
  (void) vnotebookGetDefaultClass();
  (void) _getlisttestClass();

  _openNotebookDialog();

  /*
   *  Start handling events
   */
  veventProcess();

  /*
   *  Clean up 
   */
  vdialogDestroy( dialog );

  /*
   *  Exit
   */
  exit( EXIT_SUCCESS );
  return( EXIT_FAILURE );
}

/*
 *+------------------------------------------------------------------------+
 * emacs editor formatting information:
 *+------------------------------------------------------------------------+
 */

/*
 * Local Variables:
 * c-indent-level:2
 * c-continued-statement-offset:2
 * c-brace-offset:0
 * c-brace-imaginary-offset:0
 * c-argdecl-indent:5
 * c-label-offset:-2
 * c-tab-always-indent:nil
 * End:
 */

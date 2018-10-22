/* $Id: opttest.c,v 1.6 1997/10/17 19:38:45 hoyle Exp $ */

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
 * Executable Name:    opttest
 * Source Files:       opttest.c
 * Header Files:
 * Resource Files:     
 *
 * Managers Illustrated:
 *              Notebook
 *      
 *
 * Description Of Sample:
 *
 * Illustrates a notebook with a control option menu as a tab set.  
 * Each menu item in the option menu represents a tab in the notebook.
 *
 * History:             Written for 2.1 release   11/10/94
 * $Log: opttest.c,v $
 * Revision 1.6  1997/10/17  19:38:45  hoyle
 * Fixed bug where accessing NULL tabset.
 *
 * Revision 1.5  1995/02/02 19:19:40  hoyle
 * 1) Fixed where notebook header was included directly instead of
 *    vnotebookHEADER
 * 2) Changed resource file to have pages under notebook instead of placing
 *    them in notebook in code.
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

#ifndef vcontrolINCLUDED
#include vcontrolHEADER
#endif

#ifndef vmenuINCLUDED
#include vmenuHEADER
#endif

#ifndef vnotebookINCLUDED
#include vnotebookHEADER
#endif

#define _optiontestINSET 	15

vnotebookClass		*optiontestClass = NULL;
vresource		 resfile;
vdialog			*dialog;
vnotebook		*notebook;
vnotebookStyle		*_defaultStyle = NULL;

/*****************************************************************
  _findCell

  Returns the option menu item whose data pointer contains data.
*****************************************************************/
static int _findCell( vcontrol *control, void *data )
{
  vmenu		*menu = vcontrolGetMenu( control );
  int	 	 i, count = vmenuGetItemCount( menu );

  for ( i = 0; i < count; i++ )
    if ( vmenuGetItemData( vmenuGetItemAt( menu, i ) ) == data )
      return( i );

  return( -1 );
}

/*****************************************************************
  _optiontestSetTabSetTabSelected

  Method override for vnotebookSET_TABSET_TAB_SELECTED.
    - Sets the tab to be the selected in the option menu.
*****************************************************************/
static void _optiontestSetTabSetTabSelected( vnotebook *notebook,
					   vdialogItem *tabset,
					   vnotebookTab *tab )
{
  vcontrol	*control = (vcontrol *) tabset;
  int	    	 row;

  if ( control && ( row = _findCell( control, tab ) ) != -1 )
    vcontrolSetValue( control, row );
}

/*****************************************************************
  _optiontestScrollTabSetTabIntoView

  Method override for vnotebookSCROLL_TABSET_TAB_INTO_VIEW
    - Does nothing because selecting control value automatically
      scrolls it into view
*****************************************************************/
static void _optiontestScrollTabSetTabIntoView( vnotebook *notebook,
					     vdialogItem *tabset, 
					     vnotebookTab *tab )
{
}

/*****************************************************************
  _optiontestGetTabSetClipRects

  Method override for vnotebookGET_TABSET_CLIP_RECTS
    - We don't need to clip anything out, so return NULL
*****************************************************************/
static vrect *_optiontestGetTabSetClipRects( vnotebook *notebook, 
					   vdialogItem *tabset,
					   int *rectCount )
{
  return( NULL );
}

/*****************************************************************
  _optiontestGetTabSetTabCount

  Method override for vnotebookGET_TABSET_TAB_COUNT
    - Returns the number of tabs in the option menu
*****************************************************************/
static int _optiontestGetTabSetTabCount( vnotebook *notebook, 
				       vdialogItem *tabset )
{
  vcontrol	*control = (vcontrol *) tabset;
  vmenu		*menu = vcontrolGetMenu( control );

  return( vmenuGetItemCount( menu ) );
}

/*****************************************************************
  _optiontestGetTabSetTabAt

  Method override for vnotebookGET_TABSET_TAB_AT
    - Returns the tab at the index specified in the option menu
*****************************************************************/
static vnotebookTab *_optiontestGetTabSetTabAt( vnotebook *notebook, 
					      vdialogItem *tabset, int index )
{
  vcontrol	*control = (vcontrol *) tabset;
  vmenu		*menu = vcontrolGetMenu( control );

  return( (vnotebookTab *) vmenuGetItemData( vmenuGetItemAt( menu, index ) ) );
}

/*****************************************************************
  _optiontestDeleteTabSetTab

  Method override for vnotebookDELETE_TABSET_TAB
    - Removes the tab from the option menu
*****************************************************************/
static void _optiontestDeleteTabSetTab( vnotebook *notebook, 
				      vdialogItem *tabset,
				      vnotebookTab *tab )
{
  int			 i;
  vcontrol		*control = (vcontrol *) tabset;
  vmenu			*menu = vcontrolGetMenu( control );
  vmenuItem		*item;

  if ( ( i = _findCell( control, tab ) ) != -1 )
    {
      item = vmenuGetItemAt( menu, i );
      vmenuDeleteItem( menu, item );
      vmenuDestroyItem( item );
      
      vcontrolSetMax( control, vmenuGetItemCount( menu ) - 1 );
      vnotebookSetTabTabSet( tab, NULL );
    }
}

/*****************************************************************
  _optiontestAddTabSetTab

  Method override for vnotebookADD_TABSET_TAB
    - Adds the tab to the option menu
*****************************************************************/
static void _optiontestAddTabSetTab( vnotebook *notebook, vdialogItem *tabset,
				   vnotebookTab *tab )
{
  vcontrol		*control = (vcontrol *) tabset;
  vmenu			*menu = vcontrolGetMenu( control );
  vmenuItem		*item;

  item = vmenuCreateItem();

  vmenuSetItemTitle( item, vnotebookGetTabTitle( tab ) );
  vmenuSetItemData( item, tab );

  vmenuAppendItem( menu, item );
  vnotebookSetTabTabSet( tab, tabset );
  vcontrolSetMax( control, vmenuGetItemCount( menu ) - 1 );

  vmenuRecalc( menu );
}

/*****************************************************************
  _doControlNotify

  Notification function for the option menu
*****************************************************************/
static void _doControlNotify( vcontrol *control, vevent *event )
{
  int		 	 row;
  vnotebookTab		*tab;
  vmenu			*menu = vcontrolGetMenu( control );

  row = vcontrolGetValue( control );
  if ( row >= 0 && row < vmenuGetItemCount( menu ) )
    {
      tab = (vnotebookTab *) vmenuGetItemData( vmenuGetItemAt( menu, row ) );
      if ( tab )
	vnotebookSetPageCurrent( vnotebookGetTabPage( tab ) );
    }
}

/*****************************************************************
  _optiontestCreateTabSet

  Method override for vnotebookCREATE_TABSET
    - We create an option menu for the tab set and set it up appropriately
*****************************************************************/
static vdialogItem *_optiontestCreateTabSet( vnotebook *notebook, int whichTabs )
{
  vcontrol	*control;

  control = vcontrolCreateOptionMenu();
  vcontrolSetMenu( control, vmenuCreate() );
  vcontrolSetNotify( control, _doControlNotify );
  vcontrolSetMin( control, 0 );
  vcontrolSetMax( control, 0 );
  
  return( vcontrolGetItem( control ) );
}

/*****************************************************************
  _optiontestGetTabSetSize

  Method override for vnotebookGET_TABSET_SIZE
*****************************************************************/
static void _optiontestGetTabSetSize( vnotebook *notebook, vdialogItem *tabset,
				      int *w, int *h )
{
  if ( tabset )
    vdialogGetItemNaturalSize( tabset, w, h );
  else
    *w = *h = 0;
}

/*****************************************************************
  _optiontestCalcTabSetRect

  Method override for vnotebookCALC_TABSET_RECT.
*****************************************************************/
static void _optiontestCalcTabSetRect( vnotebook *notebook, vdialogItem *tabset,
				     vrect *rect )
{
  const vrect	*r;
  int		 w, h;

  r = vdialogGetItemRect( vnotebookGetItem( notebook ) );
  vnotebookGetTabSetSize( notebook, tabset, &w, &h );
  vrectSet( r->x + _optiontestINSET, r->y + r->h - h, w, h, rect );
}

/*****************************************************************
  _optiontestGetBorderSizes

  Method override for vnotebookGET_PAGE_BORDER_SIZES
*****************************************************************/
static void _optiontestGetBorderSizes( vnotebook *notebook, 
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
  *top = th / 2 + 2;
  *left = *bot = *right = 2;
}

/*****************************************************************
  _optiontestGetDecorationSizes

  Method override for vnotebookGET_PAGE_DECORATION_SIZES
    - Account for the option menu on the top side
*****************************************************************/
static void _optiontestGetDecorationSizes( vnotebook *notebook, 
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
  *top = th / 2;
}

/*****************************************************************
  _optiontestDrawBinder

  Method override for vnotebookDRAW_BINDER
*****************************************************************/
static void _optiontestDrawBinder( vnotebook *notebook )
{
  vcolorScheme           scheme;
  vrect			 border;

  vnotebookCalcPageRect( notebook, &border );

  vdialogDetermineItemColorSchemeState( vnotebookGetItem( notebook ), 
				        vcolorFLAG_SHADOW_TOP |
				        vcolorFLAG_SHADOW_BOTTOM, 
				        &scheme );

  vdrawRectsHiliteStrokeInside( &border, 1, 
			        vcolorGetSchemeShadowBottom( &scheme ),
			        vcolorGetSchemeShadowTop( &scheme ) );

  vcolorDestroyScheme( &scheme );
}

/*****************************************************************
  _opttestShutdown
*****************************************************************/
#if vmemBALANCE
static void _opttestShutdown( void )
{
  if ( _defaultStyle )
    vnotebookDestroyStyle( _defaultStyle );
}
#endif

/*****************************************************************
  _getOptiontestClass
*****************************************************************/
vnotebookClass *_getOptiontestClass( void )
{
  vnotebookStyle	*style;

  if ( optiontestClass == NULL )
    {
      optiontestClass = vclassReproduce( vnotebookGetDefaultClass() );
      vclassSetNameScribed( optiontestClass, 
			    vcharScribeLiteral( "optiontestNotebook" ) );

      vclassSet( optiontestClass, vnotebookGET_TABSET_CLIP_RECTS,
		 _optiontestGetTabSetClipRects );
      vclassSet( optiontestClass, vnotebookADD_TABSET_TAB,
		 _optiontestAddTabSetTab );
      vclassSet( optiontestClass, vnotebookDELETE_TABSET_TAB,
		 _optiontestDeleteTabSetTab );
      vclassSet( optiontestClass, vnotebookGET_TABSET_TAB_AT,
		 _optiontestGetTabSetTabAt );
      vclassSet( optiontestClass, vnotebookGET_TABSET_TAB_COUNT,
		 _optiontestGetTabSetTabCount );
      vclassSet( optiontestClass, vnotebookCREATE_TABSET,
		 _optiontestCreateTabSet );
      vclassSet( optiontestClass, vnotebookSET_TABSET_TAB_SELECTED,
		 _optiontestSetTabSetTabSelected );
      vclassSet( optiontestClass, vnotebookSCROLL_TABSET_TAB_INTO_VIEW,
		 _optiontestScrollTabSetTabIntoView );

      vclassSet( optiontestClass, vnotebookGET_PAGE_BORDER_SIZES, 
		 _optiontestGetBorderSizes );
      vclassSet( optiontestClass, vnotebookGET_PAGE_DECORATION_SIZES, 
		_optiontestGetDecorationSizes );

      vclassSet( optiontestClass, vnotebookCALC_TABSET_RECT, 
		 _optiontestCalcTabSetRect );
      vclassSet( optiontestClass, vnotebookGET_TABSET_SIZE, 
		 _optiontestGetTabSetSize );
      vclassSet( optiontestClass, vnotebookDRAW_BINDER, 
		 _optiontestDrawBinder );
 
      /*
       *  Override the default class style to set up what we want
       */
      style = _defaultStyle =
	vnotebookCloneStyle( vnotebookGetClassStyle( optiontestClass ) );
      vnotebookSetStyleFolio( style, FALSE );
      vnotebookSetStylePageButtons( style, FALSE );
      vnotebookSetStyleTabs( style, vnotebookTABS_PAGE );
      vnotebookSetStylePageBorders( style, FALSE );
      vclassSet( optiontestClass, vnotebookCLASS_STYLE, style );

#if vmemBALANCE
      vclientRegisterShutdown( _opttestShutdown );
#endif
    }

  return( optiontestClass );
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

  vwindowPlace( vdialogGetWindow( dialog ), vwindowGetRoot(),
	        vrectPLACE_CENTER, vrectPLACE_CENTER );
	        
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
  (void) _getOptiontestClass();

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

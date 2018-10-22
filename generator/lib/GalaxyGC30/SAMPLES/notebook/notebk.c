/* $Id: notebk.c,v 1.7 1995/02/02 19:21:37 hoyle Exp $ */

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
 * Executable Name:    notebk
 * Source Files:       notebk.c
 * Header Files:
 * Resource Files:     
 *
 * Managers Illustrated:
 *              Notebook
 *      
 *
 * Description Of Sample:
 *
 * Illustrates how styles can be used to change the appearance and behavior
 * of notebooks.  This sample also shows how other attributes affect the
 * notebook.
 *
 * History:             Written for 2.1 release   11/10/94
 * $Log: notebk.c,v $
 * Revision 1.7  1995/02/02  19:21:37  hoyle
 * 1) Fixed where notebook header was included directly instead of
 *    vnotebookHEADER.
 * 2) Changed resource file to have pages under notebook instead of placing
 *    them in notebook in code.
 *
 * Revision 1.6  1994/12/20  18:34:58  hoyle
 * Fixed case where tab set sides were not specified on adjacent sides.
 *
 * Revision 1.5  1994/12/14  15:53:30  hoyle
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

#ifndef vdialogINCLUDED
#include vdialogHEADER
#endif

#ifndef vcontainerINCLUDED
#include vcontainerHEADER
#endif

#ifndef vnotebookINCLUDED
#include vnotebookHEADER
#endif

vresource		 resfile;
vdialog			*dialog;
vnotebook		*notebook;
vbutton			*leftBtn;
vbutton			*rtBtn;
vcontrol		*majorTabCtrl;
vcontrol		*minorTabCtrl;

static void _leftBtnNotify( vbutton *button, vevent *event );
static void _rtBtnNotify( vbutton *button, vevent *event );

/*****************************************************************
  _dialogNotify

  Dialog notification function - used to catch close message
*****************************************************************/
static void _dialogNotify( vdialog *dialog, vevent *event )
{
  if ( veventGetType( event ) == veventWINDOW_STATE && veventIsClose( event ) )
    veventStopProcessing();
}

/*****************************************************************
  _leftBtnNotify

  Left (previous) page button notify
*****************************************************************/
static void _leftBtnNotify( vbutton *button, vevent *event )
{
  vnotebook	*notebook;

  notebook = (vnotebook *) vbuttonGetData( button );
  vnotebookSetSectionPreviousPage( vnotebookGetSection( notebook ) );
}

/*****************************************************************
  _rtBtnNotify

  Right (next) page button notify
*****************************************************************/
static void _rtBtnNotify( vbutton *button, vevent *event )
{
  vnotebook	*notebook;

  notebook = (vnotebook *) vbuttonGetData( button );
  vnotebookSetSectionNextPage( vnotebookGetSection( notebook ) );
}

/*****************************************************************
  _borderChkNotify

  Notification for notebook border check box.
*****************************************************************/
static void _borderChkNotify( vcontrol *control, vevent *event )
{
  vdialogSetItemBorder( vnotebookGetItem( notebook ), 
		        vcontrolGetValue( control ) );
}

/*****************************************************************
  _majorTabCtrlNotify

  Notification for major tab option menu.
*****************************************************************/
static void _majorTabCtrlNotify( vcontrol *control, vevent *event )
{
  vnotebookStyle	 style;
  vnotebookStyle	*current;
  int			 majorSide;
  int			 minorSide;

  /*
   *  Determine minor tab side 
   */
  vnotebookInitStyle( &style );
  vnotebookDetermineStyle( notebook, &style, 
			   vnotebookSTYLE_MINOR_TABSET_SIDE );
  minorSide = vnotebookGetStyleMinorTabSetSide( &style );
  vnotebookDestroyStyle( &style );
			  
  /*
   *  Create new style
   */
  vnotebookInitStyle( &style );
  if ( ( current = vnotebookGetStyle( notebook ) ) )
    vnotebookCopyStyle( current, &style );

  majorSide = vcontrolGetValue( control );
  
  /*
   *  Make sure that major and minor tabs are on adjacent sides
   */
  switch ( majorSide )
    {
    case vnotebookTABSET_RIGHT :
    case vnotebookTABSET_LEFT  :
      if ( minorSide == vnotebookTABSET_RIGHT ||
	   minorSide == vnotebookTABSET_LEFT )
	{
	  minorSide = vnotebookTABSET_TOP;
	  vcontrolSetValue( minorTabCtrl, minorSide );
	}
      break;
    case vnotebookTABSET_BOTTOM :
    case vnotebookTABSET_TOP  :
      if ( minorSide == vnotebookTABSET_BOTTOM ||
	   minorSide == vnotebookTABSET_TOP )
	{
	  minorSide = vnotebookTABSET_RIGHT;
	  vcontrolSetValue( minorTabCtrl, minorSide );
	}
      break;
    }
  
  vnotebookSetStyleMajorTabSetSide( &style, majorSide );
  vnotebookSetStyleMinorTabSetSide( &style, minorSide );

  vnotebookSetStyle( notebook, &style );
  vnotebookDestroyStyle( &style );
}

/*****************************************************************
  _minorTabCtrlNotify

  Notification for minor tab option menu.
*****************************************************************/
static void _minorTabCtrlNotify( vcontrol *control, vevent *event )
{
  vnotebookStyle	 style;
  vnotebookStyle	*current;
  int			 majorSide;
  int			 minorSide;

  /*
   *  Determine major tab side 
   */
  vnotebookInitStyle( &style );
  vnotebookDetermineStyle( notebook, &style, 
			   vnotebookSTYLE_MAJOR_TABSET_SIDE );
  majorSide = vnotebookGetStyleMajorTabSetSide( &style );
  vnotebookDestroyStyle( &style );
					  
  /*
   *  Create new style
   */	  
  vnotebookInitStyle( &style );
  if ( ( current = vnotebookGetStyle( notebook ) ) )
    vnotebookCopyStyle( current, &style );

  minorSide = vcontrolGetValue( control );

  /*
   *  Make sure that major and minor tabs are on adjacent sides
   */
  switch ( minorSide )
    {
    case vnotebookTABSET_RIGHT :
    case vnotebookTABSET_LEFT  :
      if ( majorSide == vnotebookTABSET_RIGHT ||
	   majorSide == vnotebookTABSET_LEFT )
	{
	  majorSide = vnotebookTABSET_TOP;
	  vcontrolSetValue( majorTabCtrl, majorSide );
	}
      break;
    case vnotebookTABSET_BOTTOM :
    case vnotebookTABSET_TOP  :
      if ( majorSide == vnotebookTABSET_BOTTOM ||
	   majorSide == vnotebookTABSET_TOP )
	{
	  majorSide = vnotebookTABSET_RIGHT;
	  vcontrolSetValue( majorTabCtrl, majorSide );
	}
      break;
    }
  
  vnotebookSetStyleMajorTabSetSide( &style, majorSide );
  vnotebookSetStyleMinorTabSetSide( &style, minorSide );

  vnotebookSetStyle( notebook, &style );
  vnotebookDestroyStyle( &style );
}

/*****************************************************************
  _vertTabChkNotify

  Notification for vertical tab check box
*****************************************************************/
static void _vertTabChkNotify( vcontrol *control, vevent *event )
{
  vnotebookStyle	 style;
  vnotebookStyle	*current;

  vnotebookInitStyle( &style );
  if ( ( current = vnotebookGetStyle( notebook ) ) )
    vnotebookCopyStyle( current, &style );

  vnotebookSetStyleVerticalTabs( &style, vcontrolGetValue( control ) );
  
  vnotebookSetStyle( notebook, &style );
  vnotebookDestroyStyle( &style );
}

/*****************************************************************
  _folioChkNotify

  Notification for folio check box
*****************************************************************/
static void _folioChkNotify( vcontrol *control, vevent *event )
{
  vnotebookStyle	 style;
  vnotebookStyle	*current;

  vnotebookInitStyle( &style );
  if ( ( current = vnotebookGetStyle( notebook ) ) )
    vnotebookCopyStyle( current, &style );

  vnotebookSetStyleFolio( &style, vcontrolGetValue( control ) );

  vnotebookSetStyle( notebook, &style );
  vnotebookDestroyStyle( &style );
}

/*****************************************************************
  _pageBtnChkNotify

  Notification for page buttons check box
*****************************************************************/
static void _pageBtnChkNotify( vcontrol *control, vevent *event )
{  
  vnotebookStyle	 style;
  vnotebookStyle	*current;

  vnotebookInitStyle( &style );
  if ( ( current = vnotebookGetStyle( notebook ) ) )
    vnotebookCopyStyle( current, &style );

  vnotebookSetStylePageButtons( &style, vcontrolGetValue( control ) );

  vnotebookSetStyle( notebook, &style );
  vnotebookDestroyStyle( &style );
}

/*****************************************************************
  _justOptionNotify

  Notification for folio justification option menu
*****************************************************************/
static void _justOptionNotify( vcontrol *control, vevent *event )
{
  vnotebookStyle	 style;
  vnotebookStyle	*current;

  vnotebookInitStyle( &style );
  if ( ( current = vnotebookGetStyle( notebook ) ) )
    vnotebookCopyStyle( current, &style );

  vnotebookSetStyleFolioJustification( &style, vcontrolGetValue( control ) );
  
  vnotebookSetStyle( notebook, &style );
  vnotebookDestroyStyle( &style );
}

/*****************************************************************
  _tabOptionNotify

  Notification for tab type option menu
*****************************************************************/
static void _tabOptionNotify( vcontrol *control, vevent *event )
{
  vnotebookStyle	 style;
  vnotebookStyle	*current;

  vnotebookInitStyle( &style );
  if ( ( current = vnotebookGetStyle( notebook ) ) )
    vnotebookCopyStyle( current, &style );

  vnotebookSetStyleTabs( &style, vcontrolGetValue( control ) );

  vnotebookSetStyle( notebook, &style );
  vnotebookDestroyStyle( &style );
}

/*****************************************************************
  _pageBordersChkNotify

  Notification for page borders check box
*****************************************************************/
static void _pageBordersChkNotify( vcontrol *control, vevent *event )
{
  vnotebookStyle	 style;
  vnotebookStyle	*current;

  vnotebookInitStyle( &style );
  if ( ( current = vnotebookGetStyle( notebook ) ) )
    vnotebookCopyStyle( current, &style );

  vnotebookSetStylePageBorders( &style, vcontrolGetValue( control ) );

  vnotebookSetStyle( notebook, &style );
  vnotebookDestroyStyle( &style );
}

/*****************************************************************
  _tabStyleNotify

  Notification for tab style option menu
*****************************************************************/
static void _tabStyleNotify( vcontrol *control, vevent *event )
{
  vnotebookStyle	 style;
  vnotebookStyle	*current;

  vnotebookInitStyle( &style );
  if ( ( current = vnotebookGetStyle( notebook ) ) )
    vnotebookCopyStyle( current, &style );

  vnotebookSetStyleTabStyle( &style, vcontrolGetValue( control ) );

  vnotebookSetStyle( notebook, &style );
  vnotebookDestroyStyle( &style );
}

/*****************************************************************
  _pageWrapChkNotify

  Notification for page wrap check box
*****************************************************************/
static void _pageWrapChkNotify( vcontrol *control, vevent *event )
{
  vnotebookStyle	 style;
  vnotebookStyle	*current;

  vnotebookInitStyle( &style );
  if ( ( current = vnotebookGetStyle( notebook ) ) )
    vnotebookCopyStyle( current, &style );

  vnotebookSetStylePagesWrap( &style, vcontrolGetValue( control ) );

  vnotebookSetStyle( notebook, &style );
  vnotebookDestroyStyle( &style );
}

/*****************************************************************
  _openNotebookDialog
*****************************************************************/
static void _openNotebookDialog( void )
{
  vcontrol		*borderChk;
  vcontrol		*pageBtnChk;
  vcontrol		*folioChk;
  vcontrol		*tabOption;
  vcontrol		*vertTabChk;
  vcontrol		*justOption;
  vcontrol		*pageBordersChk;
  vcontrol		*pageWrapChk;
  vcontrol		*tabStyleOption;
  vnotebookStyle	 style;

  dialog = vdialogLoad( vresourceGet( resfile, vname_Dialog ) );
  vdialogSetNotify( dialog, _dialogNotify );

  notebook = (vnotebook *)
    vdialogFindItem( dialog, vnameInternGlobalLiteral( "Notebook" ) );

  leftBtn = (vbutton *)
    vdialogFindItem( dialog, vnameInternGlobalLiteral( "Left" ) );
  vbuttonSetData( leftBtn, notebook );
  vbuttonSetNotify( leftBtn, _leftBtnNotify );

  rtBtn = (vbutton *)
    vdialogFindItem( dialog, vnameInternGlobalLiteral( "Right" ) );
  vbuttonSetData( rtBtn, notebook );
  vbuttonSetNotify( rtBtn, _rtBtnNotify );


  borderChk = (vcontrol *)
    vdialogFindItem( dialog, vnameInternGlobalLiteral( "BorderChk" ) );
  vcontrolSetNotify( borderChk, _borderChkNotify );
  vcontrolSetValue( borderChk, 
		    vdialogItemHasBorder( vnotebookGetItem( notebook ) ) );

  vnotebookInitStyle( &style );
  vnotebookDetermineStyle( notebook, &style, 
			   vnotebookSTYLE_FOLIO |
			   vnotebookSTYLE_PAGE_BORDERS |
			   vnotebookSTYLE_PAGES_WRAP |
			   vnotebookSTYLE_TAB_STYLE |
			   vnotebookSTYLE_PAGE_BUTTONS |
			   vnotebookSTYLE_MAJOR_TABSET_SIDE |
			   vnotebookSTYLE_MINOR_TABSET_SIDE |
			   vnotebookSTYLE_TABS | 
			   vnotebookSTYLE_FOLIO_JUSTIFY |
			   vnotebookSTYLE_VERTICAL_TABS );
			   
			   
  folioChk = (vcontrol *)
    vdialogFindItem( dialog, vnameInternGlobalLiteral( "StatusChk" ) );
  vcontrolSetNotify( folioChk, _folioChkNotify );
  vcontrolSetValue( folioChk, vnotebookGetStyleFolio( &style ) );

  pageBordersChk = (vcontrol *)
    vdialogFindItem( dialog, vnameInternGlobalLiteral( "PageBordersChk" ) );
  vcontrolSetNotify( pageBordersChk, _pageBordersChkNotify );
  vcontrolSetValue( pageBordersChk, vnotebookGetStylePageBorders( &style ) );

  tabStyleOption = (vcontrol *)
    vdialogFindItem( dialog, vnameInternGlobalLiteral( "TabStyle" ) );
  vcontrolSetNotify( tabStyleOption, _tabStyleNotify );
  vcontrolSetValue( tabStyleOption, vnotebookGetStyleTabStyle( &style ) );

  pageWrapChk = (vcontrol *)
    vdialogFindItem( dialog, vnameInternGlobalLiteral( "PageWrapChk" ) );
  vcontrolSetNotify( pageWrapChk, _pageWrapChkNotify );
  vcontrolSetValue( pageWrapChk, vnotebookGetStylePagesWrap( &style ) );

  pageBtnChk = (vcontrol *)
    vdialogFindItem( dialog, vnameInternGlobalLiteral( "PageBtnChk" ) );
  vcontrolSetNotify( pageBtnChk, _pageBtnChkNotify );
  vcontrolSetValue( pageBtnChk, vnotebookGetStylePageButtons( &style ) );

  majorTabCtrl = (vcontrol *)
    vdialogFindItem( dialog, vnameInternGlobalLiteral( "MajorTabs" ) );
  vcontrolSetNotify( majorTabCtrl, _majorTabCtrlNotify );
  vcontrolSetValue( majorTabCtrl, vnotebookGetStyleMajorTabSetSide( &style ) );

  minorTabCtrl = (vcontrol *)
    vdialogFindItem( dialog, vnameInternGlobalLiteral( "MinorTabs" ) );
  vcontrolSetNotify( minorTabCtrl, _minorTabCtrlNotify );
  vcontrolSetValue( minorTabCtrl, vnotebookGetStyleMinorTabSetSide( &style ) );

  tabOption = (vcontrol *)
    vdialogFindItem( dialog, vnameInternGlobalLiteral( "TabOption" ) );
  vcontrolSetNotify( tabOption, _tabOptionNotify );
  vcontrolSetValue( tabOption, vnotebookGetStyleTabs( &style ) );

  justOption = (vcontrol *)
    vdialogFindItem( dialog, vnameInternGlobalLiteral( "JustOption" ) );
  vcontrolSetNotify( justOption, _justOptionNotify );
  vcontrolSetValue( justOption, 
		    vnotebookGetStyleFolioJustification( &style ) );

  vertTabChk = (vcontrol *)
    vdialogFindItem( dialog, vnameInternGlobalLiteral( "VertTabChk" ) );
  vcontrolSetNotify( vertTabChk, _vertTabChkNotify );
  vcontrolSetValue( vertTabChk, vnotebookGetStyleVerticalTabs( &style ) );

  vnotebookDestroyStyle( &style );

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

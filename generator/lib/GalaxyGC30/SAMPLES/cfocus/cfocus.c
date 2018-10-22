/* $Id: cfocus.c,v 1.9 1997/11/12 19:48:32 bill Exp $ */
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
 * copyright notice in the in the form of "Copyright 1993-96 Visix Software,
 * Inc., 11440 Commerce Park Drive, Reston, VA  22091. All Rights Reserved" 
 * appears in all copies, (ii) both the copyright notice and this permission 
 * notice appear in supporting documentation and (iii) you are a valid 
 * licensee of Galaxy Application Environment.
 */

/****************************************************************************
 * Source File, cfocus.c
 *
 * Managers Illustrated:
 *     vcontainer
 *
 * Description Of Sample:
 *     This code illustrates how to make containers scroll 
 *     automatically as focus is changed from the keyboard. 
 *     Focus changes within the container are sniffed by 
 *     overriding vdialogITEM_SELECT_MOVE_FOCUS in 
 *     the vobjectISSUE_SELECTOR (however, the relevant commands
 *     may also have been dispatched programmatically) .
 *     The case where the container gains focus due to keyboard
 *     events is taken care of in the override of vdialogTEST_FOCUS_ITEM 
 *     (new in Galaxy 3.0)
 *
 * History:
 *     Written for 1.2 release, 7/21/93
 *     Updated for 3.0 release, 2/29/96
 ****************************************************************************/

#ifndef  vportINCLUDED
#include <vport.h>		/* for v*HEADER */
#endif

#ifndef  vstdlibINCLUDED
#include vstdlibHEADER
#endif

#ifndef  vresourceINCLUDED
#include vresourceHEADER
#endif

#ifndef  vstartupINCLUDED
#include vstartupHEADER
#endif

#ifndef  vapplicationINCLUDED
#include vapplicationHEADER
#endif

#ifndef  vprefINCLUDED
#include vprefHEADER
#endif

#ifndef  vwindowINCLUDED
#include vwindowHEADER
#endif

#ifndef  vdialogINCLUDED
#include vdialogHEADER
#endif

#ifndef  vcontainerINCLUDED
#include vcontainerHEADER
#endif

#ifndef  vtestINCLUDED
#include vtestHEADER
#endif

vcontainerClass		*myContainerClass;

/*****************************************************************
  _myScrollFocusedItemIntoView
 
  helper function that changes the bounds of the container
*****************************************************************/
static void _myScrollFocusedItemIntoView( vcontainer *container, 
					  vdialogItem *item )
{
  vrect	 	 dr;
  vrect	 	 cr;
  vrect	       	 r;
  vrect		 bounds;
  int		 outset;

  /*
   *  Get the container's content rectangle (dialog item rectangle
   *   minus the scroll bars and border width)
   */
  cr = *vcontainerGetContent( container );
  
  /*
   *  To get the screen rectangle for the dialog item we need to
   *    add in the container bounds
   */
  dr = *vdialogGetItemRect( item );

  if ( ( outset = -vclassGet( vdialogGetItemClass( item ),
                             vdialogITEM_FOCUS_EXTRA ) ) != 0
       ||
       ( vdialogItemIsConfirmed( item ) &&
         ( outset = -vclassGet( vdialogGetItemClass( item ), 
                                vdialogITEM_CONFIRM_EXTRA ) ) != 0 ) )
      vrectInset(&dr, outset, outset, &dr);
  bounds = *vcontainerGetBounds( container );
  dr.x += bounds.x;
  dr.y += bounds.y;
  
  /*
   *  If the dialog item is enclosed in the view rectangle, do 
   *   nothing; otherwise we need to scroll
   */
  if ( !vrectEncloses( &cr, &dr ) )
    {
       vrectUnion( &cr, &dr, &r );
       
       /*
	*  Calculate amount to scroll in the horizontal direction
	*/
       if ( r.x < cr.x )
	  bounds.x += ( cr.x - r.x );
       else
	  bounds.x -= ( ( r.x + r.w ) - ( cr.x + cr.w ) );
       
       /*
	*  Calculate amount to scroll in the vertical direction
	*/
       if ( r.y < cr.y )
	  bounds.y += ( cr.y - r.y );
       else
	  bounds.y -= ( ( r.y + r.h ) - ( cr.y + cr.h ) );
       
       /*
	*  Set the new bounds to effectively scroll the container
	*/
       vcontainerSetBounds( container, &bounds );
    }
}

/*****************************************************************
  _myIssueSelector

  vobjectISSUE_SELECTOR method for my container class
*****************************************************************/
static int _myIssueSelector( vcontainer *container, int selector, 
			     vdict *attr2value )
{
  int	 	 retval;
  vdialogItem	*item;

  switch (selector)
    {
    case vdialogITEM_SELECT_MOVE_FOCUS:
      /*
       *  Let the superclass handle changing focus first
       */
      retval = vclassSendSuper( myContainerClass, vobjectISSUE_SELECTOR,
			        (container, selector, attr2value) );
      
      /*
       *  Check focused item here and make sure it is in view (bounds)
       *   of container
       */
      if ( ( item = vcontainerGetFocus( container ) ) != NULL )
	 _myScrollFocusedItemIntoView ( container, item );
      return( retval );

    default:
	break;
    }

  /*
   *  Let the superclass handle the selector
   */
  return( vclassSendSuper( myContainerClass, vobjectISSUE_SELECTOR,
			   (container, selector, attr2value) ) );
}

/*****************************************************************
  _myTestFocus

  vdialogTEST_ITEM_FOCUS method for my container class
*****************************************************************/
static vbool _myTestFocus( vcontainer *container, vevent *event )
{
  vbool	 	 retval;
  vdialogItem	*item;

  /*
   *  Let the superclass handle the focus change first
   */
  retval = vclassSendSuper( myContainerClass, vdialogTEST_FOCUS_ITEM,
			    (container, event) );
  /*
   * If the event that causes the focus change was a keyboard event
   * scroll the focused item into view
   *
   * Note that in the case of button events for click-focusable containers
   * this method may be called before their itemList 
   * handles the button event, so changing the bounds for such events
   * here would cause the button event to go to the wrong item within 
   * the container or be dropped
   */

  if ( retval 
       && ( event != NULL ) 
       && ( veventGetType( event ) == veventKEY_DOWN )
       && ( ( item = vcontainerGetFocus( container ) ) != NULL ) )
    _myScrollFocusedItemIntoView( container, item );
  return ( retval );
}

/*****************************************************************
  _initContainerClass
*****************************************************************/
static void _initContainerClass()
{
  myContainerClass = vclassReproduce( vcontainerGetDefaultClass() );
  vclassSetNameScribed( myContainerClass, 
			vcharScribeLiteral( "myContainer" ) );
  vclassSet( myContainerClass, vobjectISSUE_SELECTOR, _myIssueSelector );
  vclassSet( myContainerClass, vdialogTEST_FOCUS_ITEM, _myTestFocus );
}

/*************************************************************
  _dialogNotify
**************************************************************/
static void _dialogNotify( vdialog *dialog, vevent *event )
{
  if ( veventIsClose( event ) )
    veventStopProcessing();
}

/*************************************************************
 **********************     main     ************************
**************************************************************/
int main( short argc, char **argv )
{
  vresource	 resfile;
  vdialog     	*dialog;

  /*
   *  Initialize proper classes
   */
  vstartup( argc, argv );

  /*
   *  Connect to any running testing tools
   */
  vtestStartup();

  /*
   *  Initialize custom classes 
   */
  _initContainerClass();

  /*
   *  Get dialog from resource file and open it
   */
  resfile = vapplicationGetResources( vapplicationGetCurrent() );
  dialog = 
    vdialogLoad( vresourceGet( resfile, 
			       vnameInternGlobalLiteral( "Dialog" ) ) );
  vdialogSetNotify( dialog, _dialogNotify );
  vwindowPlace( vdialogGetWindow( dialog ), vwindowGetRoot(), 
	        vrectPLACE_CENTER, vrectPLACE_CENTER );
  vdialogOpen( dialog );

  /*
   *  Start event loop
   */
  veventProcess();

  /*
   *  Clean up
   */
  vdialogDestroy( dialog );

  exit( EXIT_SUCCESS );
  return( EXIT_FAILURE );
}

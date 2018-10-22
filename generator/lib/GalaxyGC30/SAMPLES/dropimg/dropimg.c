/* $Id: dropimg.c,v 1.6 1996/03/07 01:38:42 david Exp $ */

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
 * copyright notice in the in the form of "Copyright 1993-95 Visix Software,
 * Inc., 11440 Commerce Park Drive, Reston, VA  22091. All Rights Reserved" 
 * appears in all copies, (ii) both the copyright notice and this permission 
 * notice appear in supporting documentation and (iii) you are a valid 
 * licensee of Galaxy Application Environment.
 */

#include <vport.h>		/* for v*HEADER */

#ifndef  vstdlibINCLUDED	/* for exit, EXIT_SUCCESS */
#include vstdlibHEADER
#endif

#ifndef  vapplicationINCLUDED
#include vapplicationHEADER
#endif

#ifndef  vdebugINCLUDED
#include vdebugHEADER
#endif

#ifndef  vclassINCLUDED
#include vclassHEADER
#endif

#ifndef  vprefINCLUDED
#include vprefHEADER
#endif

#ifndef  vstdioINCLUDED
#include vstdioHEADER
#endif

#ifndef  vstrINCLUDED
#include vstrHEADER
#endif

#ifndef  vcolorINCLUDED
#include vcolorHEADER
#endif

#ifndef  vimageINCLUDED
#include vimageHEADER
#endif

#ifndef  vlafINCLUDED
#include vlafHEADER
#endif

#ifndef  vdialogINCLUDED
#include vdialogHEADER
#endif

#ifndef  vmenuINCLUDED
#include vmenuHEADER
#endif

#ifndef  vmenubarINCLUDED
#include vmenubarHEADER
#endif

#ifndef  vbuttonINCLUDED
#include vbuttonHEADER
#endif

#ifndef  vnumINCLUDED
#include vnumHEADER
#endif

#ifndef  vstartupINCLUDED
#include vstartupHEADER
#endif

#ifndef  vtimerINCLUDED
#include vtimerHEADER
#endif

#ifndef  vspinnerINCLUDED
#include vspinnerHEADER
#endif

#ifndef  vconfirmINCLUDED
#include vconfirmHEADER
#endif

#ifndef  vdragINCLUDED
#include vdragHEADER
#endif

#ifndef  vlistitemINCLUDED
#include vlistitemHEADER
#endif

#ifndef  vserviceINCLUDED	/* for provider	*/
#include vserviceHEADER
#endif

#ifndef  vsessionINCLUDED	/* for consumer and provider */
#include vsessionHEADER
#endif

#ifndef  vcommINCLUDED		/* to initialize for Transport preference */
#include vcommHEADER
#endif

#ifndef  vdasservINCLUDED
#include vdasservHEADER
#endif

#ifndef  vservicechsrINCLUDED
#include vservicechsrHEADER
#endif

#if (vdebugDEBUG)
static const char _dropimgTag[] = "dropimg";
#define vdebugTAG _dropimgTag
#endif

#ifndef ABS
#define ABS(x)           ( (x) > 0 ? (x) : ( -(x) ) )
#endif

/*
 *  Type and structure declarations 
 */

typedef struct _dragInfo{
  vdialogItem		*imageItem;
  vdialogItem		*tapeEnd;
  vdialogItem		*tapeBegin;
  vtextitem		*textitem;
  vbutton		*sendBtn;
  vlistitem		*listitem;
  vdialogItem		*dropItem;
} _dragInfo;

typedef struct _dropInfo{
  vdialogItem		*imageItem;
  vdialogItem		*tapeItem;
  vtextitem		*textitem;
} _dropInfo;

/*
 *  Local variables
 */

static _dragInfo		 dragInfo;
static _dropInfo		 dropInfo;

static vservice			*service;
static vsession		        *sessions[20];
static int			 sessionCount = 0;
static vsession			*session;
static vresource	 	 resfile;
static vdialog			*dragDialog;
static vdialog			*imageDialog = NULL;
static vdialogItemClass		*dragBoxItemClass;
static vpoint		 	 startPt;
static vtimer			*timer;
static vimage	       	       **images;
static int		 	 currFrame = 0, numFrames = 20;
static int		 	 fps = 30;
static vrect		 	 animRect;
static vimage			*offscreen;
static vimage			*savescreen;
static vimage			*strImage;
static int			 offset;
static int			 endoffset;
static vstr			*sentstr;
static vsignature		*_signatureDumpString;
static vsignature		*_signatureImage;
static vbool			 outsideNotify = FALSE;
static vcursor			*originalCursor;
static vcursor			*goodDropCursor;
static vcursor		      	*badDropCursor;
static vservicechsr		*chooser = NULL;
static vwindow			*animWindow;

/*
 *  Forward declarations
 */

static void _sessionNotify( vsession *, vsessionEvent * );

/*************************************************************
  _dialogNotify

  Notification function for dialog events.
**************************************************************/
static void _dialogNotify( vdialog *dialog, vevent *event )
{
  if ( veventGetType( event ) == veventWINDOW_STATE && veventIsClose( event ) )
    veventStopProcessing();
}

/*****************************************************************
  _doListNotify

  List notification function for list item selection changes.
*****************************************************************/
static void _doListNotify( vlistitem *listitem, int notifyType )
{
  vlist			*list = vlistitemGetList( listitem );
  vlistSelection	*select = vlistitemGetSelection( listitem );
  vlistview		*view = vlistitemGetView( listitem );
  int			 row;
  const vchar		*name;
  vresource		 res;
  vimage		*image;

  if ( vlistCountSelectedCells( list, select ) == 0 )
    return;

  row = vlistitemGetSelectedRow( listitem );
  if ( notifyType == vlistviewSELECTION_HAS_CHANGED )
    {
      if ( vlistviewGetLastPointerClickCount( view ) > 1 )
	{
	  name = vlistitemGetValueAt( listitem, row );
	  res = vresourceGet( resfile, vnameInternGlobalLiteral( "Images" ) );
	  res = vresourceGet( res, name );
	  image = vimageLoad( res );
	  vdialogSetItemImageOwned( dragInfo.imageItem, image );
	}
    }
}

/*****************************************************************
  _initList

  Initializes list item.
*****************************************************************/
static void _initList( vlistitem *listitem )
{
  vlistview		*listview;
  vlist			*list;
  vlistSelection     	*select;
  int			 count, i;
  vresource		 res;
  const vname		*name;

  listview = vlistitemGetView( listitem );
  list = vlistitemGetList( listitem );
  select = vlistitemGetSelection( listitem );

  vlistitemSetSelectNotify( listitem, _doListNotify );
  vlistitemSetSelectMethod( listitem, vlistONE_ONLY_SELECTION );
  vlistSetAtLeastOneSelection( list, select, TRUE );
  vlistitemSetRowCount( listitem, 0 );

  res = vresourceGet( resfile, vnameInternGlobalLiteral( "Images" ) );
  count = vresourceCountComponents( res );
  for ( i = 0; i < count; i++ )
    {
      name = vresourceGetNthTag( res, i );
      vlistitemSetValueAt( listitem, name, i );
    }
}

/*****************************************************************
  _captureWindowRect

  Returns a offscreen image of a specified rectangle in a window.
*****************************************************************/
vimage *_captureWindowRect( vwindow *window, vrect *r )
{
  vimage  	*rootImage;
  vimage	*image;
  vrect		 tr;

  rootImage = vwindowToImage( window );
  image = vwindowCreateBufferImage( r->w, r->h );
  tr = *r;
  tr.x = tr.y = 0;
  
  vdrawGSave();
  vdrawImageDevice( image );
  vdrawRectImage( rootImage, r, &tr );
  vdrawGRestore();

  vimageDestroy( rootImage );

  return( image );
}

/*****************************************************************
  _dropTextTimerNotify

  Timer notification function for text drop.
*****************************************************************/
static void _dropTextTimerNotify( vtimer *timer )
{
  vrect		 strRect;
  vrect		 r;
  vrect		 src, dest;

  r = animRect;
  r.x = r.y = 0;
  vrectSet( 0, 0, vimageGetWidth( strImage ), 
	    vimageGetHeight( strImage ), &strRect );

  vdrawGSave();

  if ( offset > endoffset )
    {
      vtimerStop( timer );
      vwindowDrawDevice( animWindow );
      vdrawRectImage( savescreen, &r, &animRect );

      if ( sessionCount && outsideNotify )
	vtextitemSetText( dragInfo.textitem, sentstr );
      else if ( imageDialog && vdialogIsOpen( imageDialog ) )
	vtextitemSetText( dropInfo.textitem, sentstr );
      vstrDestroy( sentstr );
      vwindowSyncEvents();

      vimageDestroy( offscreen );
      vimageDestroy( savescreen );
      vimageDestroy( strImage );
    }
  else
    {
      vdrawImageDevice( offscreen );
      vdrawRectImage( savescreen, &r, &r );

      src = strRect;
      if ( offset < 0 )
	{
	  src.x = -offset;
	  src.w = src.w + offset;
	  if ( src.w < 0 )
	    src.w = 0;
	}

      dest = src;
      dest.y = r.y + r.h/2 - src.h/2;
      if ( offset < 0 )
	dest.x = 0;
      else
	dest.x = offset;
      
      vdrawSetColor( vwindowDetermineForeground( animWindow ) );
      vdrawRectImageMask( strImage, &src, &dest );
      vwindowDrawDevice( animWindow );
      vdrawRectImage( offscreen, &r, &animRect );      
      offset += 3;
    }

  vdrawGRestore();
}

/*****************************************************************
  _dragTextTimerNotify

  Timer notification function for text drag.
*****************************************************************/
static void _dragTextTimerNotify( vtimer *timer )
{
  vrect		 	 strRect;
  vrect		 	 r;
  vrect		 	 src, dest;
  vrect		 	 tapeRect, textRect;
  vsessionStatement	*statement;
  int			 animate = FALSE;
  int			 i;

  r = animRect;
  r.x = r.y = 0;
  vrectSet( 0, 0, vimageGetWidth( strImage ), 
	    vimageGetHeight( strImage ), &strRect );

  vdrawGSave();

  if ( strRect.w + offset > animRect.w + strRect.w )
    {
      vtimerStop( timer );
      vwindowDrawDevice( animWindow );
      vdrawRectImage( savescreen, &r, &animRect );
      vimageDestroy( offscreen );
      vimageDestroy( savescreen );

      if ( imageDialog && vdialogIsOpen( imageDialog ) )
	{
	  tapeRect = *vdialogGetItemRect( dropInfo.tapeItem );
	  textRect = *vdialogGetItemRect( (vdialogItem *) dropInfo.textitem );

	  animRect.x = tapeRect.x + tapeRect.w/2;
	  animRect.y = vMIN( textRect.y, tapeRect.y );
	  animRect.w = textRect.x + textRect.w - (tapeRect.x + tapeRect.w/2);
	  animRect.h = vMAX( textRect.h, tapeRect.h );

	  animWindow = (vwindow *) imageDialog;
	  offscreen = vwindowCreateBufferImage( animRect.w, animRect.h );
	  savescreen = _captureWindowRect( animWindow, &animRect );
	  offset = -strRect.w + 3;
	  endoffset = textRect.x + 5 - (tapeRect.x + tapeRect.w/2);

	  vtimerSetNotify( timer, _dropTextTimerNotify );
	  vtimerStart( timer );
	  
	  outsideNotify = FALSE;
	  animate = TRUE;
	}

      if ( sessionCount )
	{
	  for ( i = 0; i < sessionCount; i++ )
	    {
	      statement = vsessionCreateStatement();
	      vsessionSetStatementSignature(statement, _signatureDumpString);
	      vsessionSetStatementSession(statement, sessions[i]);
	      vsessionSetStatementArgs(statement, sentstr);
	      vsessionSendStatement(statement);
	      vsessionDestroyStatement(statement);
	    }
	}

      if ( !animate )
	{
	  vstrDestroy( sentstr );
	  vimageDestroy( strImage );
	}
    }
  else
    {
      vdrawImageDevice( offscreen );
      vdrawRectImage( savescreen, &r, &r );

      src = strRect;
      if ( offset + src.w > r.w )
	src.w = src.w - (offset + src.w - r.w);
      if ( src.w < 0 )
	src.w = 0;
      dest = src;
      dest.y = r.y + r.h/2 - src.h/2;
      dest.x = offset;
      
      vdrawSetColor( vwindowDetermineForeground( (vwindow *) dragDialog ) );
      vdrawRectImageMask( strImage, &src, &dest );
      vwindowDrawDevice( animWindow );
      vdrawRectImage( offscreen, &r, &animRect );      
      offset += 3;
    }

  vdrawGRestore();
}

/*****************************************************************
  _createOffscreenText

  Creates offscreen image of a string given string and font.
*****************************************************************/
static vimage *_createOffscreenText( const vchar *str, vfont *font, int maxw )
{
  int 		 w, h;
  vrect		 r;
  vimage	*image;

  /*
   *  Determine the width and height of the string for the offscreen image
   */
  h = vfontHeight( font ) + 10;
  w = vfontStringWidthX( font, str );
  w = vMIN( w, maxw );
  image = vimageCreateSpecific( w, h, 2 );

  /*
   *  Draw the text into the offscreen image
   */
  vrectSet( 0, 0, w, h, &r );
  vdrawGSave();
  vdrawMaskDevice( image );
  vdrawSetFunction( vdrawFUNC_CLEAR );
  vdrawRectsFill( &r, 1 );
  vdrawSetFunction( vdrawFUNC_SET );
  vdrawSetFont( font );
  vdrawRectShowCenterY( str, &r );
  vdrawGRestore();

  return( image );
}

/*****************************************************************
  _sendBtnNotify

  Send button notification function
*****************************************************************/
static void _sendBtnNotify( vbutton *button, vevent *event )
{
  vstr		*str;
  vrect		 tapeRect, textRect;
  vfont		*font;

  /*
   *  Get string from text item
   */
  str = vtextitemGetTextAsString( dragInfo.textitem );

  /*
   *  If there isn't any text, return
   */
  if ( vcharLength( str ) == 0 )
    {
      vwindowBeep();
      vstrDestroy( str );
      return;
    }

  sentstr = str;

  /*
   *  First, clear the text out of the textitem
   */
  vtextitemSetText( dragInfo.textitem, vcharGetEmptyString() );
  vdialogInvalItem( (vdialogItem *) dragInfo.textitem, vwindowINVAL_UPDATE );
  vwindowSyncEvents();

  tapeRect = *vdialogGetItemRect( dragInfo.tapeEnd );
  textRect = *vdialogGetItemRect( (vdialogItem *) dragInfo.textitem );

  /*
   *  Calculate the window rectangle that will be damaged during the 
   *    animation
   */
  animRect.x = textRect.x;
  animRect.y = vMIN( textRect.y, tapeRect.y );
  animRect.w = tapeRect.x + tapeRect.w/2 - textRect.x;
  animRect.h = vMAX( textRect.h, tapeRect.h );

  animWindow = (vwindow *) dragDialog;
  offscreen = vwindowCreateBufferImage( animRect.w, animRect.h );
  savescreen = _captureWindowRect( animWindow, &animRect );
  
  font = vdialogDetermineItemFont( (vdialogItem *) dragInfo.textitem );
  strImage = _createOffscreenText( str, font, textRect.w );

  /*
   *  Initialize the location of the offscreen text
   */
  offset = 5;

  /*
   *  Start the timer to animate the text leaving the window
   */
  vtimerSetNotify( timer, _dragTextTimerNotify );
  vtimerStart( timer );
}

/*****************************************************************
  _openImageDialog

  Initializes and opens image dialog
*****************************************************************/
static void _openImageDialog( void )
{  
  /*
   *  If dialog already exists, raise it to the top
   */
  if ( imageDialog )
    {
      vwindowUniconify( (vwindow *) imageDialog );
      vwindowRaise( (vwindow *) imageDialog );
      vdialogOpen( imageDialog );
      return;
    }

  /*
   *  Load image dialog from resource file
   */
  imageDialog = 
    vdialogLoad( vresourceGet( resfile, 
			       vnameInternGlobalLiteral( "ImageDialog" ) ) );

  /*
   *  Initialize dialog items
   */
  dropInfo.imageItem = 
    vdialogFindItem( imageDialog, vnameInternGlobalLiteral( "Image" ) );

  dropInfo.tapeItem = 
    vdialogFindItem( imageDialog, vnameInternGlobalLiteral( "TapeImage" ) );
  dropInfo.textitem = (vtextitem *)
    vdialogFindItem( imageDialog, vnameInternGlobalLiteral( "Textitem" ) );

  /*
   *  Place and open dialog
   */
  vdialogPlace( imageDialog, dragDialog, 
	        vrectPLACE_RIGHT | vrectPLACE_NEAR, 
	        vrectPLACE_ALIGN | vrectPLACE_TOP );
  vdialogOpen( imageDialog );
}

/*****************************************************************
  _servicechsrHandleApply

  Service chooser apply notification function.
*****************************************************************/
static int _servicechsrHandleApply( vservicechsr *chooser,
				    vscrap *scrapAttributes )
{
  vservice	*service;
  
  service = (vservice *) vconfirmGetData( vservicechsrGetConfirm( chooser ) );
  session = vsessionCreate();
  vsessionSetDestroyWhenInactive( session, TRUE );
  vsessionSetAttributesFromScrap( session, scrapAttributes );
  vsessionSetNotify( session, _sessionNotify );
  vsessionSetService( session, service );
  vsessionBegin( session );

  return( TRUE );
}

/*****************************************************************
  _doFileOpen

  Menu item notification function.
*****************************************************************/
static void _doFileOpen( vmenuItem *item, vevent *event )
{
  _openImageDialog();
}

/*****************************************************************
  _doFileChooser

  Menu item notification function for service chooser menu item.
*****************************************************************/
static void _doFileChooser( vmenuItem *item, vevent *event )
{
  vscrap *scrapSpec;

  scrapSpec = vscrapCreateDictionary();
  vscrapStoreElement(scrapSpec, vname_Title,
	     vscrapFromStringScribed(vcharScribeLiteral("Send Image Demo")));

  chooser = vservicechsrCreate();
  vconfirmSetData( vservicechsrGetConfirm( chooser ), service );
  vservicechsrSetApply( chooser, _servicechsrHandleApply );
  vservicechsrSetMatchScrap( chooser, scrapSpec );
  vservicechsrOpen( chooser );
}

/*****************************************************************
  _openDragDialog

  Initializes and opens drag dialog.
*****************************************************************/
static void _openDragDialog( void )
{
  vscribe		*scribeLocation;
  vscribe		*scribeTransport;
  vscribe		*scribePort;
  vdialogItem		*item;
  vmenubar		*menubar;
  vmenu			*menu;
  vmenuItem		*mitem;

  dragDialog = 
    vdialogLoad( vresourceGet( resfile, 
			       vnameInternGlobalLiteral( "DragDialog" ) ) );
  vdialogSetNotify( dragDialog, _dialogNotify );

  dragInfo.listitem = (vlistitem *) 
    vdialogFindItem( dragDialog, vnameInternGlobalLiteral( "Listitem" ) );
  dragInfo.dropItem = 
    vdialogFindItem( dragDialog, vnameInternGlobalLiteral( "DropImage" ) );
  dragInfo.imageItem = 
    vdialogFindItem( dragDialog, vnameInternGlobalLiteral( "Image" ) );
  _initList( dragInfo.listitem );

  dragInfo.sendBtn = (vbutton *)
    vdialogFindItem( dragDialog, vnameInternGlobalLiteral( "Send" ) );
  vbuttonSetNotify( dragInfo.sendBtn, _sendBtnNotify );

  dragInfo.tapeBegin = 
    vdialogFindItem( dragDialog, 
		     vnameInternGlobalLiteral( "TapeImageBegin" ) );  
  dragInfo.tapeEnd = 
    vdialogFindItem( dragDialog, vnameInternGlobalLiteral( "TapeImageEnd" ) );
  dragInfo.textitem = (vtextitem *)
    vdialogFindItem( dragDialog, vnameInternGlobalLiteral( "Textitem" ) );

  menubar = (vmenubar *)
    vdialogFindItem( dragDialog, vnameInternGlobalLiteral( "Menubar" ) );
  menu = vmenubarFindMenu( menubar, vnameInternGlobalLiteral( "FileMenu" ) );
  mitem = vmenuFindItem( menu, vnameInternGlobalLiteral( "Open" ) );
  vmenuSetItemNotify( mitem, _doFileOpen );
  mitem = vmenuFindItem( menu, vnameInternGlobalLiteral( "Chooser" ) );
  vmenuSetItemNotify( mitem, _doFileChooser );

  scribeLocation  = vserviceFindAttributeScribe(service, vsession_Location);
  scribeTransport = vserviceFindAttributeScribe(service, vsession_Transport);
  scribePort      = vserviceFindAttributeScribe(service, vsession_Port);

  if (scribeLocation == NULL)
    scribeLocation = vcharScribeLiteral("<NULL>");
  if (scribeTransport == NULL)
    scribeTransport = vcharScribeLiteral("<NULL>");
  if (scribePort == NULL)
    scribePort = vcharScribeLiteral("<NULL>");

  item = vdialogFindItem( dragDialog, vnameInternGlobalLiteral( "Connect" ) );
  vdialogSetItemTitleScribed
    ( item, vcharScribeFormatLiteral( "Location: %S Transport: %S Port: %S", 
				      scribeLocation, scribeTransport, 
				      scribePort ) );

  vdialogOpen( dragDialog );
}

/*****************************************************************
  _doCleanUp

  Cleans up any allocated memory on exit.
*****************************************************************/
static void _doCleanUp( void )
{
  if ( chooser )
    vservicechsrDestroy( chooser );

  vdasservUnregisterService( service );

  vserviceDisable( service );
  vserviceDestroy( service );

  vtimerDestroy( timer );
  vdialogDestroy( dragDialog );
  if ( imageDialog )
    vdialogDestroy( imageDialog );

  vsignatureDestroy( _signatureImage );
  vsignatureDestroy( _signatureDumpString );

  vcursorDestroy( goodDropCursor );	
  vcursorDestroy( badDropCursor );
}

/*****************************************************************
  _createWarpFrames
*****************************************************************/
vimage **_createWarpFrames( vimage *image, int numFrames )
{
  vimage		**images;
  vrect			 r, tr;
  int			 w, h;
  int			 i;
  float			 radius;
  int			 cx, cy;
  float			 scale;
  float			 currScale;
  int			 currw, currh;
  int			 half;
  vimage		*mask;
  vrect			 src, dest;

  half = numFrames / 2;
  scale = 1.0 / ( half + 1 );

  images = vmemAlloc( sizeof(vimage *) * (numFrames + 1) );
  w = vimageGetWidth( image );  h = vimageGetHeight( image );
  vrectSet( 0, 0, w, h, &r );
  cx = w / 2; cy = h / 2;
  radius = sqrt( cx * cx + cy * cy );
  
  vdrawGSave();
  images[numFrames] = NULL;
  for ( i = 0; i < half; i++ )
    {
      currScale = 1.0 - (float) i * scale;
      images[i] = vwindowCreateBufferImage( w, h );
      vdrawImageDevice( images[i] );
      if ( i > 0 )
	{
	  vdrawMoveTo( 0, 0 );
	  vdrawImageIdent( images[i-1] );
	}

      currw = (double) w * currScale + 0.5;
      currh = (double) h * currScale + 0.5;
      vrectSet( 0, 0, w, h, &src );
      vrectSet( w/2 - currw/2, h/2 - currh/2, currw, currh, &dest );
      vdrawRectImage( image, &src, &dest );
    }

  for ( i = half; i < numFrames; i++ )
    {
      mask = vimageCreateSpecific( w, h, 2 );
      images[i] = vimageClone( images[half-1] );
      currScale = 1.0 - (float) (i - half + 1) * scale;
      currw = (double) w * currScale + 0.5;
      currh = (double) h * currScale + 0.5;

      vdrawSetFunction( vdrawFUNC_CLEAR );
      vrectSet( 0, 0, w, h, &tr );
      vdrawMaskDevice( mask );
      vdrawRectsFill( &tr, 1 );

      if ( i + 1 != numFrames )
	{
	  vdrawSetFunction( vdrawFUNC_SET );
	  vrectSet( w/2 - currw/2, h/2 - currh/2, currw, currh, &tr );
	  vdrawRectsFill( &tr, 1 );
	}

      vimageSetTransparencyOwned( images[i], mask );
    }
  vdrawGRestore();

  return( images );
}

/*****************************************************************
  _dropTimerNotify
*****************************************************************/
static void _dropTimerNotify( vtimer *timer )
{
  vrect	   	 r;
  int		 i;
  vimage	*image;
  int		 half;

  vdrawGSave();
  r = animRect;
  r.x = r.y = 0;
  image = (vimage *) vtimerGetData( timer );
  half = numFrames / 2;
  if ( currFrame >= (half - 1) )
    {
      vdrawImageDevice( offscreen );
      vdrawRectImage( savescreen, &r, &r );
      if ( currFrame == half - 1 )
	vdrawRectImage( image, &r, &r );
      else
	vdrawRectImageComposite( images[currFrame], &r, &r );
      vwindowDrawDevice( animWindow );
      vdrawRectImage( offscreen, &r, &animRect );
      currFrame--;
    }
  else 
    {
      vwindowDrawDevice( animWindow );
      vdrawRectImage( savescreen, &r, &animRect );

      vtimerStop( timer );
      vimageDestroy( offscreen );
      vimageDestroy( savescreen );
      for ( i = 0; i < numFrames; i++ )
	vimageDestroy( images[i] );
      vmemFree( images );

      if ( sessionCount && outsideNotify )
	vdialogSetItemImageOwned( dragInfo.imageItem, image );
      else if ( imageDialog && vdialogIsOpen( imageDialog ) )
	vdialogSetItemImageOwned( dropInfo.imageItem, image );
      else
	vimageDestroy( image );
    }

  vdrawGRestore();
  vwindowSyncEvents();
}

/*****************************************************************
  _dragTimerNotify
*****************************************************************/
static void _dragTimerNotify( vtimer *timer )
{
  vrect	   	 r;
  int		 i;
  vimage   	*image;

  vdrawGSave();
  r = animRect;
  r.x = r.y = 0;
  if ( currFrame < numFrames )
    {
      vdrawImageDevice( offscreen );
      vdrawRectImage( savescreen, &r, &r );
      vdrawRectImageComposite( images[currFrame], &r, &r );
      vwindowDrawDevice( animWindow );
      vdrawRectImage( offscreen, &r, &animRect );
      currFrame++;
    }
  else 
    {
      vwindowDrawDevice( animWindow );
      vdrawRectImage( savescreen, &r, &animRect );
      vimageDestroy( savescreen );
      vwindowSyncEvents();

      vtimerStop( timer );
      if ( imageDialog && vdialogIsOpen( imageDialog ) )
	{
	  outsideNotify = FALSE;

	  vtimerSetNotify( timer, _dropTimerNotify );
	  r = *vdialogGetItemRect( dropInfo.imageItem );
	  vrectSet( r.x + r.w/2 - animRect.w/2, 
		    r.y + r.h/2 - animRect.h/2, 
		    animRect.w, animRect.h, &animRect );

	  animWindow = (vwindow *) imageDialog;
	  savescreen = _captureWindowRect( animWindow, &animRect );
	  currFrame = numFrames - 1;

	  vtimerStart( timer );
	}
      else
	{
	  vimageDestroy( offscreen );
	  for ( i = 0; i < numFrames; i++ )
	    vimageDestroy( images[i] );
	  vmemFree( images );
	  
	  image = (vimage *) vtimerGetData( timer );
	  vimageDestroy( image );
	}
    }

  vdrawGRestore();
  vwindowSyncEvents();
}

/*****************************************************************
  _dragBoxNotify

  Drag notification function for image drag.
*****************************************************************/
static void _dragBoxNotify( vdrag *drag, vwindow *from, vwindow *to,
			     vevent *event )
{
  int			 x, y;
  vimage		*image;
  vrect		     	 r;
  vsessionStatement	*statement;
  vscrap		*scrapImage;
  vresource              res;
  int			 i;
  
  image = (vimage *) vdragGetData( drag );

  x = veventGetPointerX( event );
  y = veventGetPointerY( event );
  if ( to && to == from && 
       vdialogItemContainsPoint( dragInfo.dropItem, x, y ) )
    {
      vwindowSyncEvents();

      currFrame = 0;
      vrectSet( veventGetPointerX( event ) - vdragGetOffsetX( drag ),
	        veventGetPointerY( event ) - vdragGetOffsetY( drag ),
	        vdragGetMaxWidth( drag ), vdragGetMaxHeight( drag ), 
	        &animRect );

      animWindow = (vwindow *) dragDialog;
      offscreen = vwindowCreateBufferImage( animRect.w, animRect.h );
      savescreen = _captureWindowRect( animWindow, &animRect );
      
      r = animRect;
      r.x = r.y = 0;

      vdrawGSave();
      vdrawImageDevice( offscreen );
      vdrawRectImage( image, &r, &r );

      vwindowDrawDevice( animWindow );
      vdrawRectImage( image, &r, &animRect );
      vdrawGRestore();
      
      images = _createWarpFrames( image, numFrames );
      vtimerSetNotify( timer, _dragTimerNotify );
      vtimerSetData( timer, vimageClone( image ) );
      vtimerStart( timer );

      /*
       *  Send image drop to all open sessions
       */
      if ( sessionCount )
	{
	  res = vresourceCreateMem();
	  vimageStore( image, vresourceMake( res, vname_Image ) );
	  scrapImage = vresourceGetScrap( res, vname_Image );

	  for ( i = 0; i < sessionCount; i++ )
	    {
	      statement = vsessionCreateStatement();
	      vsessionSetStatementSignature(statement, _signatureImage );
	      vsessionSetStatementSession( statement, sessions[i] );
	      vsessionSetStatementArgs( statement, scrapImage );
	      vsessionSendStatement( statement );
	      vsessionDestroyStatement( statement );
	    }

	  vscrapDestroy( scrapImage );
	  vresourceDestroyMem( res );
	}
    }

  vdragDestroy( drag );
  vapplicationSetCursor( vapplicationGetCurrent(), originalCursor );
}

/*****************************************************************
  _dragBoxDetailNotify

  Drag detail notification function for image drag.
*****************************************************************/
static int _dragBoxDetailNotify( vdrag *drag, vwindow *from, vwindow *to,
				  vevent *event )
{
  vcursor	*cursor;

  if ( to && to == from &&
       vdialogItemContainsPoint( dragInfo.dropItem,
				 veventGetPointerX( event ),
				 veventGetPointerY( event ) ) )
    cursor = goodDropCursor;
  else
    cursor = badDropCursor;
  
  vapplicationSetCursor( vapplicationGetCurrent(), cursor );

  return( 0 );
}

/*****************************************************************
  _dragBoxDraw

  Drag draw function for image drag.
*****************************************************************/
static void _dragBoxDraw( vdrag *drag, vrect *draw )
{  
  vimage		*image;

  image = (vimage *) vdragGetData( drag );
  vdrawGSave();
  vdrawMoveTo( 0, 0 );
  vdrawImageIdent( image );
  vdrawGRestore(); 
}

/*****************************************************************
  _handleDragBoxDrag

  Drag handler for box item class.
*****************************************************************/
static int _handleDragBoxDrag( vdialogItem *item, vevent *event )
{
  vdrag		*drag;
  vrect		 r;
  vimage	*dragImage;

  /*
   *  If the user breaks the threshold, begin the drag
   */
  if ( ( ABS( veventGetPointerX( event ) - startPt.x ) > 4 ||
         ABS( veventGetPointerY( event ) - startPt.y ) > 4 ) )
    {
      originalCursor = vapplicationGetCursor( vapplicationGetCurrent() );

      drag = vdragCreate();
      r = *vdialogGetItemRect( item );
      vdragSetOffset( drag, 
		      veventGetPointerX( event ) - r.x, 
		      veventGetPointerY( event ) - r.y );

      dragImage = vdialogGetItemImage( item );
      vrectSet( 0, 0, vimageGetWidth( dragImage ), 
	        vimageGetHeight( dragImage ), &r );
      vdragSetMaxSize( drag, r.w, r.h );

      vdragSetDrawProc( drag, _dragBoxDraw );
      vdragSetNotify( drag, _dragBoxNotify );
      vdragSetDetail( drag, _dragBoxDetailNotify );
      vdragSetData( drag, dragImage );
      vdragStart( drag, event );
    }

  return( TRUE );
}

/*****************************************************************
  _handleDragBoxButtonDown

  Button down handler for box item class.
*****************************************************************/
static int _handleDragBoxButtonDown( vdialogItem *item, vevent *event )
{
  /*
   *  Set the start point for the drag; if in the drag event the user
   *   has crossed a four pixel threshold the drag will begin
   */
  vpointSet( veventGetPointerX( event ), veventGetPointerY( event ), 
	     &startPt );

  return( TRUE );
}

/*****************************************************************
  _initDragBoxItem

  Initializes special box item class that handles drag of an
  image.
*****************************************************************/
static void _initDragBoxItem( void )
{
  dragBoxItemClass = (vdialogItemClass *) 
    vclassReproduce( vdialogGetBoxItemClass() );
  vclassSetNameScribed( dragBoxItemClass, 
		        vcharScribeLiteral( "DragBoxItem" ) );

  vclassSet( dragBoxItemClass, vdialogHANDLE_ITEM_BUTTON_DOWN,
	     _handleDragBoxButtonDown );
  vclassSet( dragBoxItemClass, vdialogHANDLE_ITEM_DRAG,
	     _handleDragBoxDrag );
}

/*****************************************************************
  _sessionNotify
*****************************************************************/
static void _sessionNotify( vsession *session, vsessionEvent *event )
{
  int		i;

  switch ( vsessionGetEventCode( event ) )
    {
    case  vsessionEVENT_BEGIN :
      for ( i = 0; i < sessionCount; i++ )
	if ( sessions[i] == session )
	  return;
      
      sessions[sessionCount++] = session;
      break;
      
    case  vsessionEVENT_END:
      for ( i = 0; i < sessionCount; i++ )
	if ( sessions[i] == session )
	  {
	    (void)vmemMove( sessions + i + 1, sessions + i, 
			   (sessionCount - i + 1) * sizeof( vsession ** ) );
	    sessionCount--;
	  }
      break;

    case  vsessionEVENT_CANNOT_BEGIN:
      break;

    default:
      break;
    }
}

/*****************************************************************
  _handleImagePrimitive

  Notification function for the image service primitive.
*****************************************************************/
static vscrap *_handleImagePrimitive( vservicePrimitive *prim, 
				      vsession *session,
				      vscrap *scrapArgs )
{
  vscrap	*scrap;
  vresource	 res;
  vresource	 resMem;
  vimage	*image;
  vrect		 r;

  outsideNotify = TRUE;

  /*
   *  Load image from scrap resource
   */
  vserviceGetPrimitiveArgs( prim, scrapArgs, &scrap );
  resMem = vresourceCreateMem();
  vresourceSetScrap( resMem, vname_Name, scrap );
  res = vresourceGet( resMem, vname_Name );
  image = vimageLoad( res );

  /*
   *  Create the frames for the animation 
   */
  images = _createWarpFrames( image, numFrames );

  /*
   *  Calculate the window rectangle that will be damaged during the 
   *    animation
   */
  animRect.w = vimageGetWidth( image );
  animRect.h = vimageGetHeight( image );
  r = *vdialogGetItemRect( dragInfo.imageItem );
  vrectSet( r.x + r.w/2 - animRect.w/2, r.y + r.h/2 - animRect.h/2, 
	    animRect.w, animRect.h, &animRect );

  animWindow = (vwindow *) dragDialog;
  savescreen = _captureWindowRect( animWindow, &animRect );
  offscreen = vwindowCreateBufferImage( animRect.w, animRect.h );

  /*
   *  Initialize the starting frame and start the timer to 
   *    animate the image entering the window
   */
  currFrame = numFrames - 1;
  vtimerSetData( timer, image );
  vtimerSetNotify( timer, _dropTimerNotify );
  vtimerStart( timer );
  
  vresourceDestroyMem( resMem );
  vscrapDestroy( scrap );
  
  return( NULL );
}

/*****************************************************************
  _handleStringPrimitive

  Notification function for the string service primitive.
*****************************************************************/
static vscrap *_handleStringPrimitive( vservicePrimitive *prim,
				       vsession	*session,
				       vscrap *scrapArgs )
{
  vstr			*s;
  vfont			*font;
  vrect			 tapeRect, textRect;

  outsideNotify = TRUE;

  vserviceGetPrimitiveArgs( prim, scrapArgs, &s );
  sentstr = s;

  tapeRect = *vdialogGetItemRect( dragInfo.tapeBegin );
  textRect = *vdialogGetItemRect( (vdialogItem *) dragInfo.textitem );

  font = vdialogDetermineItemFont( (vdialogItem *) dragInfo.textitem );
  strImage = _createOffscreenText( s, font, textRect.w );

  /*
   *  Calculate the window rectangle that will be damaged during the 
   *    animation
   */
  animRect.x = tapeRect.x + tapeRect.w/2;
  animRect.y = vMIN( textRect.y, tapeRect.y );
  animRect.w = textRect.x + textRect.w - (tapeRect.x + tapeRect.w/2);
  animRect.h = vMAX( textRect.h, tapeRect.h );

  animWindow = (vwindow *) dragDialog;
  offscreen = vwindowCreateBufferImage( animRect.w, animRect.h );
  savescreen = _captureWindowRect( animWindow, &animRect );

  /*
   *  Initialize the begin and end location of the offscreen text
   */
  offset = -vimageGetWidth( strImage ) + 3;
  endoffset = textRect.x + 5 - (tapeRect.x + tapeRect.w/2);

  /*
   *  Start the timer to animate the text entering the window
   */
  vtimerSetNotify( timer, _dropTextTimerNotify );
  vtimerStart( timer );

  return( NULL );
} 

/*****************************************************************
  _createService
*****************************************************************/
static vservice *_createService(void)
{
  vservice 		*service;
  vservicePrimitive	*prim;

  service = vserviceCreate();
  vsessionSetNotify( vserviceGetTemplateSession( service),
		     _sessionNotify );

#if (vdebugDEBUG)
  if (vprefLoad(vnameInternGlobalLiteral("vdasDebugAll"))) 
    {
      vsession		*session;

      session = vserviceGetTemplateSession(service);
      vsessionSetGeneralDebugFlags(session, vsessionFLAG_DEBUG_ALL);
      vsessionSetStatementDebugFlags(session, vsessionStatementFLAG_DEBUG_ALL);
      vserviceSetPrimitiveDebugFlags(service, vservicePrimitiveFLAG_DEBUG_ALL);
      vserviceSetGeneralDebugFlags(service, vserviceFLAG_DEBUG_ALL);
    }
#endif

  /*
   *  Create service primitive for string
   */
  prim = vserviceCreatePrimitive();
  vserviceSetPrimitiveSignature( prim, _signatureDumpString );
  vserviceSetPrimitiveHandler( prim, _handleStringPrimitive );
  vserviceAddPrimitiveOwned( service, prim );

  /*
   *  Create service primitive for image
   */
  prim = vserviceCreatePrimitive();
  vserviceSetPrimitiveSignature( prim, _signatureImage );
  vserviceSetPrimitiveHandler( prim, _handleImagePrimitive );
  vserviceAddPrimitiveOwned( service, prim );

  return( service );
}

/*****************************************************************
  _loadCursors

  Loads drag and drop cursors from resource file.
*****************************************************************/
static void _loadCursors( void )
{
  vresource	 res;

  res = vresourceGet( resfile, vnameInternGlobalLiteral( "Cursors" ) );
  goodDropCursor = 
    vcursorLoad( vresourceGet( res, vnameInternGlobalLiteral( "GoodDrop" ) ) );
  badDropCursor = 
    vcursorLoad( vresourceGet( res, vnameInternGlobalLiteral( "BadDrop" ) ) );
}

/*****************************************************************
  main
*****************************************************************/
int main( int argc, char *argv[] )
{
  int		 bConnect;
  vstr		*sEmpty;
  const vchar	*sPref;

  /*
   *  Initialize preference values
   */
  vprefStoreScribed( vcharScribeLiteral( "vdasDebugAll" ), 
		     vcharScribeLiteral( "" ) );
  vprefStoreScribed( vcharScribeLiteral("Port"),
		     vcharScribeLiteral(" ") );
  vprefStoreScribed( vcharScribeLiteral("Transport"),
		     vcharScribeLiteral(" ") );
  vprefStoreScribed( vcharScribeLiteral("Location"),
		     vcharScribeLiteral(" ") );

  /*
   *  Startup managers
   */
  vstartup( argc, argv );
  vcommRegisterAllDrivers();

  /*
   *  Initialize signatures
   */
  _signatureDumpString = vsignatureCreate();
  vsignatureSetTag( _signatureDumpString, 
		    vnameInternGlobalLiteral( "sendstr" ) );
  vsignatureConstructArgs( _signatureDumpString, vdatatagGetString(), NULL );

  _signatureImage = vsignatureCreate();
  vsignatureSetTag( _signatureImage, 
		    vnameInternGlobalLiteral( "image" ) );
  vsignatureConstructArgs( _signatureImage, vdatatagGetScrap(), NULL );
  
  /*
   *  Start service
   */
  service = _createService();
  vserviceEnable( service );

  /*
   *  Add name attribute to service and register with broker
   */
  vserviceSetAttributeScribe( service, vname_Title,
			      vcharScribeLiteral("Send Image Demo") );
  vserviceSetAttributeScribe( service, vname_Name,
			     vcharScribeLiteral("dropimg"));
  vdasservRegisterService( service );

  /*
   *  Get user resource file and initialize
   */
  resfile  = vapplicationGetResources( vapplicationGetCurrent() );
  _loadCursors();
  _initDragBoxItem();
  _openDragDialog();
  
  /*
   *  Establish session with specified provider, if any  (DAS specific)
   */
  bConnect = FALSE;
  sEmpty = vstrCloneScribed( vcharScribeLiteral( " " ) );
  session = vsessionCreate();

  sPref = vprefLoadScribed( vcharScribeLiteral( "Transport" ) );
  if ( vcharCompare( sPref, sEmpty ) != 0 ) 
    {
      vsessionSetAttribute(session, vsession_Transport,
			   vdatatagGetTag(), vnameInternGlobal(sPref));
      bConnect = TRUE;
    }

  sPref = vprefLoadScribed( vcharScribeLiteral( "Location" ) );
  if ( vcharCompare( sPref, sEmpty ) != 0 ) 
    {
      vsessionSetAttribute( session, vsession_Location,
			    vdatatagGetString(), sPref );
      bConnect = TRUE;
    }

  sPref = vprefLoadScribed( vcharScribeLiteral( "Port" ) );
  if ( vcharCompare( sPref, sEmpty ) != 0 ) 
    {
      vsessionSetAttribute( session, vsession_Port,
			    vdatatagGetString(), sPref );
      bConnect = TRUE;
    }
  vstrDestroy( sEmpty );

  if ( bConnect ) 
    {
      vsessionSetService( session, service );
      vsessionSetNotify( session, _sessionNotify );
      vsessionSetDestroyWhenInactive( session, TRUE );
      vsessionBegin( session );
    }
  else
    vsessionDestroy( session );

  /*
   *  Initialize timer for animation
   */
  timer = vtimerCreate();
  vtimerSetRecurrent( timer );
  vtimerSetPeriod( timer, 0, 1000000000 / fps );

  /*
   *  Start handling events
   */
  veventProcess();
  
  /*
   *  Recover memory
   */ 
  _doCleanUp();
  
  /*
   *  Exit
   */
  exit( EXIT_SUCCESS );
  return( EXIT_FAILURE );
}

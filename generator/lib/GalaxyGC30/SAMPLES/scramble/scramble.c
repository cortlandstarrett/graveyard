/* $Id: scramble.c,v 1.9 1994/08/09 18:10:05 chad Exp $ */

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
 * Executable Name:    scramble
 * Source Files:       scramble.c
 * Header Files:
 * Resource Files:     
 *
 * Managers Illustrated:
 *              Window, Image, Draw
 *      
 *
 * Description Of Sample:
 *
 * Illustrates a screen-saver like application that does animation.  The 
 * screen is divided into cells. The cells move around to scramble the
 * screen.
 *
 * History:             Written for 2.0 release   11/10/93
 * $Log: scramble.c,v $
 * Revision 1.9  1994/08/09  18:10:05  chad
 * fixed use of vtimer - can't call SetOneShot and expect it to call you again
 *
 *****************************************************************************/

#ifndef  vportINCLUDED
#include <vport.h>		/* for v*HEADER */
#endif

#ifndef  vstdlibINCLUDED	/* for rand, exit, EXIT_SUCCESS */
#include vstdlibHEADER
#endif

#ifndef  vdebugINCLUDED
#include vdebugHEADER
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

#ifndef  vapplicationINCLUDED
#include vapplicationHEADER
#endif

#ifndef  vtimerINCLUDED
#include vtimerHEADER
#endif

#ifndef  vprefINCLUDED
#include vprefHEADER
#endif

#ifndef  vtimestampINCLUDED
#include vtimestampHEADER
#endif

#if (vdebugDEBUG)
static const char		 _scrambleTag[] = "scramble";
#define vdebugTAG		 _scrambleTag
#endif

/*
 *  Constant declarations
 */

#define	ANIM_STEPS	20

enum{
  MOVE_UP		= 0,
  MOVE_LEFT		= 1,
  MOVE_DOWN		= 2,
  MOVE_RIGHT		= 3
};

/*
 *  Variable declarations
 */

vimage			*images[25];
int		 	 width, height;
int			 nextCell;
int			 currCell = 24;
int			 lastCell = -1;
vrect			 cellRect;
vtimer			*timer;
vwindow			*window;
vwindowClass		*scrambleClass = NULL;

int			 animating = FALSE;
int			 currStep;
float			 stepx, stepy;
vimage			*offscreen;
vrect			 unionRect;

/*****************************************************************
  _nextCell

  Returns the next direction to travel.
*****************************************************************/
static int _nextCell(void)
{
  int		 row;
  int		 col;
  int		 nrow;
  int		 ncol;
  int		 dir;
  int		 nextCell = 0;
  vbool		 done;

  vdebugTraceEnter(_nextCell);

  row = currCell / 5;
  col = currCell % 5;
  
  done = FALSE;
  while ( !done )
    {
      dir = ( rand() / 333 ) & 0x3;
      nrow = row; ncol = col;
      switch ( dir )
	{
	case MOVE_UP :
	  nrow = row - 1;
	  if ( nrow < 0 )
	    continue;
	  break;
	case MOVE_LEFT :
	  ncol = col - 1;
	  if ( ncol < 0 )
	    continue;
	  break;
	case MOVE_DOWN :
	  nrow = row + 1;
	  if ( nrow >= 5 )
	    continue;
	  break;
	case MOVE_RIGHT :
	  ncol = col + 1;
	  if ( ncol >= 5 )
	    continue;
	  break;
	}

      nextCell = nrow * 5 + ncol;
      done = ( nextCell >= 0 && nextCell < 25 && nextCell != lastCell );
    }

  vdebugTraceLeave();

  return nextCell;
}

/*****************************************************************
  _calcCellRect

  Returns the on-screen cell rectangle given a cell number
*****************************************************************/
static void _calcCellRect( int cell, vrect *r )
{
  *r = cellRect;
  r->x += ( cell % 5 * width );
  r->y += ( cell / 5 * height );
}

/*****************************************************************
  _timerNotify
*****************************************************************/
static void _timerNotify( vtimer *timer )
{
  vrect	 	 tr;
  vrect		 c1Rect, c2Rect;
  vimage	*temp;

  if ( animating )
    {
      /*
       *  Draw into offscreen image to reduce flicker
       */
      vdrawImageDevice( offscreen );
      
      tr = unionRect;
      tr.x = tr.y = 0;
      vdrawRectsFill( &tr, 1 );
      
      _calcCellRect( nextCell, &tr );
      tr.x = tr.x - ( stepx * (float) currStep ) - unionRect.x;
      tr.y = tr.y - ( stepy * (float) currStep ) - unionRect.y;
      vdrawRectImage( images[nextCell], &cellRect, &tr );
      
      /*
       *  Send offscreen image to screen
       */
      vwindowDrawDevice( window );
      tr = unionRect;
      tr.x = tr.y = 0;
      vdrawRectImage( offscreen, &tr, &unionRect );
      vwindowSyncEvents();
      
      if ( currStep++ == ANIM_STEPS )
	{
	  /*
	   *  We are finished animating moving cell
	   */
	  animating = FALSE;

	  /*
	   *  Swap images
	   */
	  temp = images[currCell];
	  images[currCell] = images[nextCell];
	  images[nextCell] = temp;  

	  /*
	   *  Keep up with the current and last cells 
	   */
	  lastCell = currCell;
	  currCell = nextCell;

	  /*
	   *  Delay a little longer before calculating next position
	   */
	  vtimerSetPeriod( timer, 1, 0 );
	}
    }
  else
    {
      /*
       *  Start animation
       */
      animating = TRUE;
      currStep = 1;

      /*
       *  Calculate union rectangle of two cells
       */
      nextCell = _nextCell();
      _calcCellRect( nextCell, &c1Rect );
      _calcCellRect( currCell, &c2Rect );
      vrectUnion( &c1Rect, &c2Rect, &unionRect );

      /*
       *  Calculate the distance to move on each animation
       */
      stepx = (float) ( c1Rect.x - c2Rect.x ) / (float) (ANIM_STEPS);
      stepy = (float) ( c1Rect.y - c2Rect.y ) / (float) (ANIM_STEPS);

      /*
       *  Speed up timer to show animation
       */
      vtimerSetPeriod( timer, 0, 50 * vtimestampMILLISECOND );
    }
}

/*****************************************************************
  _drawScrambleWindow
*****************************************************************/
static void _drawScramble( vwindow *window )
{
  int		i;
  vrect		tr;

  for ( i = 0; i < 25; i++ )
    {
      _calcCellRect( i, &tr );
      vdrawRectImage( images[i], &cellRect, &tr );
    }
}

/*****************************************************************
  _handleScrambleButtonDown

  Handles button down events - when user presses button, clean up and go home
*****************************************************************/
static int _handleScrambleButtonDown( vwindow *window, vevent *event )
{
  veventStopProcessing();
  return( TRUE );
}

/*****************************************************************
*******************         M A I N            *******************
*****************************************************************/
int main( int argc, char *argv[] )
{
  vrect		 r;
  vrect		 tr;
  vwindow	*root;
  int		 screenw, screenh;
  int		 i;
  vimage	*rootImage;

  vprefSetArgs( argc, argv );
  srand( vtimestampGetSeconds( vtimestampGetNow() ) );

  /*
   *  Get root window and root image
   */
  root = vwindowGetRoot();
  vwindowOpen( root );
  rootImage = vwindowToImage( vwindowGetRoot() );

  /*
   *  Get root window size
   */
  screenw = vwindowGetW( root );
  screenh = vwindowGetH( root );

  /*
   *  Calculate width and height of a cell
   */
  width = screenw / 5;
  height = screenh / 5;
  vrectSet( 0, 0, width, height, &r );
  cellRect = r;

  /*
   *  Create offscreen image to do animation in
   */
  offscreen = vwindowCreateBufferImage( 2 * width, 2 * height );

  for ( i = 0; i < 25; i++ )
    {
      images[i] = vwindowCreateBufferImage( width, height );
      _calcCellRect( i, &tr );
      vdrawImageDevice( images[i] );
      if ( i == 24 )
	vdrawRectsFill( &r, 1 );
      else
	vdrawRectImage( rootImage, &tr, &r );
      vdrawRectsStrokeInside( &r, 1 );
    }

  /*
   *  Create borderless window as big as root window
   */
  scrambleClass = vclassReproduce( vwindowGetDefaultClass() );
  vclassSet( scrambleClass, vwindowDRAW, _drawScramble );
  vclassSet( scrambleClass, vwindowHANDLE_BUTTON_DOWN, 
	     _handleScrambleButtonDown );
  window = vwindowCreateOfClass( scrambleClass );
  vrectSet( 0, 0, screenw, screenh, &r );
  vwindowSetRect( window, &r );
  vwindowSetStyle( window, vwindowSTYLE_BACKGROUND );
  vwindowSetPopup( window, TRUE );
  vwindowOpen( window );

  /*
   *  Create and start timer
   */
  timer = vtimerCreate();
  vtimerSetPeriod( timer, 1, 0 );
  vtimerSetCallback( timer, _timerNotify );
  vtimerSetRecurrent( timer );
  vtimerStart( timer );

  /*
   *  Start event loop
   */
  veventProcess();

  /*
   *  Clean up
   */
  vtimerStop( timer );
  vtimerDestroy( timer );
  vwindowDestroy( window );
  vimageDestroy( offscreen );
  vimageDestroy( rootImage );
  for ( i = 0; i < 25; i++ )
    vimageDestroy( images[i] );

  exit(EXIT_SUCCESS);
  return EXIT_FAILURE;
}

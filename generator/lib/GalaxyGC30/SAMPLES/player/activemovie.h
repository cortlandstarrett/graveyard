/* $Id: activemovie.h,v 1.1 1997/09/29 22:23:07 alex Exp $ */
/*
 * Helper functions for ActiveX (OLE) control ActiveMovie:
 * {05589FA1-C356-11CE-BF01-00AA0055595A}
 * 
 * This file automatically generated.
 * Then simplified for this sample.
 */

#include <vport.h>

#ifndef vstdlibINCLUDED
#include vstdlibHEADER
#endif

#ifndef voleINCLUDED
#include voleHEADER
#endif

#ifndef volesiteINCLUDED
#include volesiteHEADER
#endif

#ifndef volevariantINCLUDED
#include volevariantHEADER
#endif


void ActiveMovieAboutBox(voleControlSite *site);

/*
 * Puts the multimedia stream into Running state
 */
void ActiveMovieRun(voleControlSite *site);

/*
 * Puts the multimedia stream into Paused state
 */
void ActiveMoviePause(voleControlSite *site);

/*
 * Puts the multimedia stream into Stopped state
 */
void ActiveMovieStop(voleControlSite *site);

/*
 * Returns the width of the movie image
 */
int ActiveMovieGetImageSourceWidth(voleControlSite *site);

/*
 * Returns the height of the movie image
 */
int ActiveMovieGetImageSourceHeight(voleControlSite *site);

/*
 * Returns the name of the author of the movie clip
 */
vstr *ActiveMovieGetAuthor(voleControlSite *site);

/*
 * Returns the title of the movie clip
 */
vstr *ActiveMovieGetTitle(voleControlSite *site);

/*
 * Returns the copyright statement of the movie clip
 */
vstr *ActiveMovieGetCopyright(voleControlSite *site);

/*
 * Returns the description of the movie clip
 */
vstr *ActiveMovieGetDescription(voleControlSite *site);

/*
 * Returns the rating of the movie clip
 */
vstr *ActiveMovieGetRating(voleControlSite *site);

/*
 * Returns/sets the current multimedia file
 */
vstr *ActiveMovieGetFileName(voleControlSite *site);

/*
 * Returns/sets the current multimedia file
 */
void ActiveMovieSetFileName(voleControlSite *site, vstr *arg0);

/*
 * Returns the duration of the multimedia stream, if known
 */
double ActiveMovieGetDuration(voleControlSite *site);

/*
 * Returns/sets the current position of the multimedia stream
 */
double ActiveMovieGetCurrentPosition(voleControlSite *site);

/*
 * Returns/sets the current position of the multimedia stream
 */
void ActiveMovieSetCurrentPosition(voleControlSite *site, double arg0);

/*
 * Returns/sets the number of times the movie will be played
 */
int ActiveMovieGetPlayCount(voleControlSite *site);

/*
 * Returns/sets the number of times the movie will be played
 */
void ActiveMovieSetPlayCount(voleControlSite *site, int arg0);

/*
 * Returns/sets the position where playback will begin
 */
double ActiveMovieGetSelectionStart(voleControlSite *site);

/*
 * Returns/sets the position where playback will begin
 */
void ActiveMovieSetSelectionStart(voleControlSite *site, double arg0);

/*
 * Returns/sets the position where playback will stop
 */
double ActiveMovieGetSelectionEnd(voleControlSite *site);

/*
 * Returns/sets the position where playback will stop
 */
void ActiveMovieSetSelectionEnd(voleControlSite *site, double arg0);

/*
 * Returns the current state of the movie clip
 */
int ActiveMovieGetCurrentState(voleControlSite *site);

/*
 * Returns/sets the rate of the multimedia stream
 */
double ActiveMovieGetRate(voleControlSite *site);

/*
 * Returns/sets the rate of the multimedia stream
 */
void ActiveMovieSetRate(voleControlSite *site, double arg0);

/*
 * Returns/sets the audio volume of the multimedia stream
 */
int ActiveMovieGetVolume(voleControlSite *site);

/*
 * Returns/sets the audio volume of the multimedia stream
 */
void ActiveMovieSetVolume(voleControlSite *site, int arg0);

/*
 * Returns/sets the stereo balance of the multimedia stream
 */
int ActiveMovieGetBalance(voleControlSite *site);

/*
 * Returns/sets the stereo balance of the multimedia stream
 */
void ActiveMovieSetBalance(voleControlSite *site, int arg0);

/*
 * Enables/disables the right-click context menu
 */
vbool ActiveMovieGetEnableContextMenu(voleControlSite *site);

/*
 * Enables/disables the right-click context menu
 */
void ActiveMovieSetEnableContextMenu(voleControlSite *site, vbool arg0);

/*
 * Shows/hides the display panel
 */
vbool ActiveMovieGetShowDisplay(voleControlSite *site);

/*
 * Shows/hides the display panel
 */
void ActiveMovieSetShowDisplay(voleControlSite *site, vbool arg0);

/*
 * Shows/hides the control panel
 */
vbool ActiveMovieGetShowControls(voleControlSite *site);

/*
 * Shows/hides the control panel
 */
void ActiveMovieSetShowControls(voleControlSite *site, vbool arg0);

/*
 * Shows/hides the position buttons in the control panel
 */
vbool ActiveMovieGetShowPositionControls(voleControlSite *site);

/*
 * Shows/hides the position buttons in the control panel
 */
void ActiveMovieSetShowPositionControls(voleControlSite *site, vbool arg0);

/*
 * Shows/hides the selection buttons in the control panel
 */
vbool ActiveMovieGetShowSelectionControls(voleControlSite *site);

/*
 * Shows/hides the selection buttons in the control panel
 */
void ActiveMovieSetShowSelectionControls(voleControlSite *site, vbool arg0);

/*
 * Shows/hides the tracker bar in the control panel
 */
vbool ActiveMovieGetShowTracker(voleControlSite *site);

/*
 * Shows/hides the tracker bar in the control panel
 */
void ActiveMovieSetShowTracker(voleControlSite *site, vbool arg0);

/*
 * Enables/disables the position buttons in the control panel
 */
vbool ActiveMovieGetEnablePositionControls(voleControlSite *site);

/*
 * Enables/disables the position buttons in the control panel
 */
void ActiveMovieSetEnablePositionControls(voleControlSite *site, vbool arg0);

/*
 * Enables/disables the selection buttons in the control panel
 */
vbool ActiveMovieGetEnableSelectionControls(voleControlSite *site);

/*
 * Enables/disables the selection buttons in the control panel
 */
void ActiveMovieSetEnableSelectionControls(voleControlSite *site, vbool arg0);

/*
 * Enables/disables the tracker bar in the control panel
 */
vbool ActiveMovieGetEnableTracker(voleControlSite *site);

/*
 * Enables/disables the tracker bar in the control panel
 */
void ActiveMovieSetEnableTracker(voleControlSite *site, vbool arg0);

/*
 * Allows/disallows hiding the display panel at run time
 */
vbool ActiveMovieGetAllowHideDisplay(voleControlSite *site);

/*
 * Allows/disallows hiding the display panel at run time
 */
void ActiveMovieSetAllowHideDisplay(voleControlSite *site, vbool arg0);

/*
 * Allows/disallows hiding the control panel at run time
 */
vbool ActiveMovieGetAllowHideControls(voleControlSite *site);

/*
 * Allows/disallows hiding the control panel at run time
 */
void ActiveMovieSetAllowHideControls(voleControlSite *site, vbool arg0);

/*
 * Returns/sets the display mode (time or frames)
 */
int ActiveMovieGetDisplayMode(voleControlSite *site);

/*
 * Returns/sets the display mode (time or frames)
 */
void ActiveMovieSetDisplayMode(voleControlSite *site, int arg0);

/*
 * Allows/disallows changing the display mode at run time
 */
vbool ActiveMovieGetAllowChangeDisplayMode(voleControlSite *site);

/*
 * Allows/disallows changing the display mode at run time
 */
void ActiveMovieSetAllowChangeDisplayMode(voleControlSite *site, vbool arg0);

/*
 * Returns/sets the current filter graph
 */
LPUNKNOWN ActiveMovieGetFilterGraph(voleControlSite *site);

/*
 * Returns/sets the current filter graph
 */
void ActiveMovieSetFilterGraph(voleControlSite *site, LPUNKNOWN arg0);

/*
 * Returns the current filter graph's Dispatch interface
 *
IActiveMovie *ActiveMovieGetFilterGraphDispatch(voleControlSite *site);
*/

/*
 * Returns/sets the foreground color of the display panel
 */
int ActiveMovieGetDisplayForeColor(voleControlSite *site);

/*
 * Returns/sets the foreground color of the display panel
 */
void ActiveMovieSetDisplayForeColor(voleControlSite *site, int arg0);

/*
 * Returns/sets the background color of the display panel
 */
int ActiveMovieGetDisplayBackColor(voleControlSite *site);

/*
 * Returns/sets the background color of the display panel
 */
void ActiveMovieSetDisplayBackColor(voleControlSite *site, int arg0);

/*
 * Returns/sets the movie window size
 */
int ActiveMovieGetMovieWindowSize(voleControlSite *site);

/*
 * Returns/sets the movie window size
 */
void ActiveMovieSetMovieWindowSize(voleControlSite *site, int arg0);

/*
 * Indicates whether the media clip will run full screen
 */
vbool ActiveMovieGetFullScreenMode(voleControlSite *site);

/*
 * Indicates whether the media clip will run full screen
 */
void ActiveMovieSetFullScreenMode(voleControlSite *site, vbool arg0);

/*
 * Indicates whether the Control will start playing when activated
 */
vbool ActiveMovieGetAutoStart(voleControlSite *site);

/*
 * Indicates whether the Control will start playing when activated
 */
void ActiveMovieSetAutoStart(voleControlSite *site, vbool arg0);

/*
 * Indicates whether the media clip will rewind automatically after
 * playing
 */
vbool ActiveMovieGetAutoRewind(voleControlSite *site);

/*
 * Indicates whether the media clip will rewind automatically after
 * playing
 */
void ActiveMovieSetAutoRewind(voleControlSite *site, vbool arg0);

/*
 * Returns the handle of the control window
 */
int ActiveMovieGethWnd(voleControlSite *site);

/*
 * Returns/sets the appearance
 */
int ActiveMovieGetAppearance(voleControlSite *site);

/*
 * Returns/sets the appearance
 */
void ActiveMovieSetAppearance(voleControlSite *site, int arg0);

/*
 * Returns/sets the border style
 */
int ActiveMovieGetBorderStyle(voleControlSite *site);

/*
 * Returns/sets the border style
 */
void ActiveMovieSetBorderStyle(voleControlSite *site, int arg0);

/*
 * Enables/disables the control
 */
vbool ActiveMovieGetEnabled(voleControlSite *site);

/*
 * Enables/disables the control
 */
void ActiveMovieSetEnabled(voleControlSite *site, vbool arg0);

int ActiveMovieGetInfo(voleControlSite *site);

/*
 * Indicates that the current state of the movie has changed
 */
void OnActiveMovieStateChange(voleControlSite *site, int oldState, int newState);

/*
 * Indicates that the current position of the movie has changed
 */
void OnActiveMoviePositionChange(voleControlSite *site, double oldPosition, double newPosition);

/*
 * ActiveMovie Control's progress timer
 */
void OnActiveMovieTimer(voleControlSite *site);

/*
 * Reports that an asynchronous operation to open a file has completed
 * successfully
 */
void OnActiveMovieOpenComplete(voleControlSite *site);

void OnActiveMovieClick(voleControlSite *site);

void OnActiveMovieDblClick(voleControlSite *site);

void OnActiveMovieKeyDown(voleControlSite *site, short *KeyCode, short Shift);

void OnActiveMovieKeyUp(voleControlSite *site, short *KeyCode, short Shift);

void OnActiveMovieKeyPress(voleControlSite *site, short *KeyAscii);

void OnActiveMovieMouseDown(voleControlSite *site, short Button, short Shift, int x, int y);

void OnActiveMovieMouseMove(voleControlSite *site, short Button, short Shift, int x, int y);

void OnActiveMovieMouseUp(voleControlSite *site, short Button, short Shift, int x, int y);

void OnActiveMovieError(voleControlSite *site, short SCode, vstr *Description, vstr *Source, short *CancelDisplay);

/*
 * OLE Events notifcation handler
 *
 * To set this function as the event handler for your
 * control site, invoke the following in your code:
 *
 * voleSetControlSiteNotify(site, ActiveMovieNotifyEvent);
 *
 * You must also enable events of interest to you either
 * in the resource editor, or via the API, using
 * voleSetControlSiteNotifyEvent() or
 * voleSetControlSiteNotifyAllEvents().
 */
void ActiveMovieNotifyEvent(voleControlSite *site, int dispid, volevariantList *list);


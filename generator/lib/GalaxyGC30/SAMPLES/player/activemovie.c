/* $Id: activemovie.c,v 1.1 1997/09/29 22:22:12 alex Exp $ */
/*
 * Helper functions for ActiveX (OLE) control ActiveMovie:
 * {05589FA1-C356-11CE-BF01-00AA0055595A}
 * 
 * This file automatically generated.
 * Then simplified for this sample.
 */

#include "activemovie.h"

/*
 * Property get/put and method invocation
 */

void ActiveMovieAboutBox(voleControlSite *site)
{
  int hr;

  hr = voleInvokeControlSite(site, -552, INVOKE_FUNC, NULL, NULL);
}

/*
 * Puts the multimedia stream into Running state
 */
void ActiveMovieRun(voleControlSite *site)
{
  int hr;

  hr = voleInvokeControlSite(site, 1610743809, INVOKE_FUNC, NULL, NULL);
}

/*
 * Puts the multimedia stream into Paused state
 */
void ActiveMoviePause(voleControlSite *site)
{
  int hr;

  hr = voleInvokeControlSite(site, 1610743810, INVOKE_FUNC, NULL, NULL);
}

/*
 * Puts the multimedia stream into Stopped state
 */
void ActiveMovieStop(voleControlSite *site)
{
  int hr;

  hr = voleInvokeControlSite(site, 1610743811, INVOKE_FUNC, NULL, NULL);
}

/*
 * Returns the width of the movie image
 */
int ActiveMovieGetImageSourceWidth(voleControlSite *site)
{
  int hr;
  volevariant *retVar = volevariantCreate();
  int retVal;

  hr = voleInvokeControlSite(site, 4, INVOKE_PROPERTYGET, NULL, retVar);

  retVal = volevariantGetInt(retVar);
  volevariantDestroy(retVar);
  return retVal;
}

/*
 * Returns the height of the movie image
 */
int ActiveMovieGetImageSourceHeight(voleControlSite *site)
{
  int hr;
  volevariant *retVar = volevariantCreate();
  int retVal;

  hr = voleInvokeControlSite(site, 5, INVOKE_PROPERTYGET, NULL, retVar);

  retVal = volevariantGetInt(retVar);
  volevariantDestroy(retVar);
  return retVal;
}

/*
 * Returns the name of the author of the movie clip
 */
vstr *ActiveMovieGetAuthor(voleControlSite *site)
{
  int hr;
  volevariant *retVar = volevariantCreate();
  vstr *retVal;

  hr = voleInvokeControlSite(site, 6, INVOKE_PROPERTYGET, NULL, retVar);

  retVal = volevariantGetString(retVar);
  volevariantDestroy(retVar);
  return retVal;
}

/*
 * Returns the title of the movie clip
 */
vstr *ActiveMovieGetTitle(voleControlSite *site)
{
  int hr;
  volevariant *retVar = volevariantCreate();
  vstr *retVal;

  hr = voleInvokeControlSite(site, 7, INVOKE_PROPERTYGET, NULL, retVar);

  retVal = volevariantGetString(retVar);
  volevariantDestroy(retVar);
  return retVal;
}

/*
 * Returns the copyright statement of the movie clip
 */
vstr *ActiveMovieGetCopyright(voleControlSite *site)
{
  int hr;
  volevariant *retVar = volevariantCreate();
  vstr *retVal;

  hr = voleInvokeControlSite(site, 8, INVOKE_PROPERTYGET, NULL, retVar);

  retVal = volevariantGetString(retVar);
  volevariantDestroy(retVar);
  return retVal;
}

/*
 * Returns the description of the movie clip
 */
vstr *ActiveMovieGetDescription(voleControlSite *site)
{
  int hr;
  volevariant *retVar = volevariantCreate();
  vstr *retVal;

  hr = voleInvokeControlSite(site, 9, INVOKE_PROPERTYGET, NULL, retVar);

  retVal = volevariantGetString(retVar);
  volevariantDestroy(retVar);
  return retVal;
}

/*
 * Returns the rating of the movie clip
 */
vstr *ActiveMovieGetRating(voleControlSite *site)
{
  int hr;
  volevariant *retVar = volevariantCreate();
  vstr *retVal;

  hr = voleInvokeControlSite(site, 10, INVOKE_PROPERTYGET, NULL, retVar);

  retVal = volevariantGetString(retVar);
  volevariantDestroy(retVar);
  return retVal;
}

/*
 * Returns/sets the current multimedia file
 */
vstr *ActiveMovieGetFileName(voleControlSite *site)
{
  int hr;
  volevariant *retVar = volevariantCreate();
  vstr *retVal;

  hr = voleInvokeControlSite(site, 11, INVOKE_PROPERTYGET, NULL, retVar);

  retVal = volevariantGetString(retVar);
  volevariantDestroy(retVar);
  return retVal;
}

/*
 * Returns/sets the current multimedia file
 */
void ActiveMovieSetFileName(voleControlSite *site, vstr *arg0)
{
  int hr;
  volevariant *argVar;
  volevariantList *argList = volevariantCreateList();

  argVar = volevariantCreate();
  volevariantSetString(argVar, arg0);
  volevariantAppendList(argList, argVar);

  hr = voleInvokeControlSite(site, 11, INVOKE_PROPERTYPUT, argList, NULL);
  volevariantDestroyList(argList);
}

/*
 * Returns the duration of the multimedia stream, if known
 */
double ActiveMovieGetDuration(voleControlSite *site)
{
  int hr;
  volevariant *retVar = volevariantCreate();
  double retVal;

  hr = voleInvokeControlSite(site, 12, INVOKE_PROPERTYGET, NULL, retVar);

  retVal = volevariantGetDouble(retVar);
  volevariantDestroy(retVar);
  return retVal;
}

/*
 * Returns/sets the current position of the multimedia stream
 */
double ActiveMovieGetCurrentPosition(voleControlSite *site)
{
  int hr;
  volevariant *retVar = volevariantCreate();
  double retVal;

  hr = voleInvokeControlSite(site, 13, INVOKE_PROPERTYGET, NULL, retVar);

  retVal = volevariantGetDouble(retVar);
  volevariantDestroy(retVar);
  return retVal;
}

/*
 * Returns/sets the current position of the multimedia stream
 */
void ActiveMovieSetCurrentPosition(voleControlSite *site, double arg0)
{
  int hr;
  volevariant *argVar;
  volevariantList *argList = volevariantCreateList();

  argVar = volevariantCreate();
  volevariantSetDouble(argVar, arg0);
  volevariantAppendList(argList, argVar);

  hr = voleInvokeControlSite(site, 13, INVOKE_PROPERTYPUT, argList, NULL);
  volevariantDestroyList(argList);
}

/*
 * Returns/sets the number of times the movie will be played
 */
int ActiveMovieGetPlayCount(voleControlSite *site)
{
  int hr;
  volevariant *retVar = volevariantCreate();
  int retVal;

  hr = voleInvokeControlSite(site, 14, INVOKE_PROPERTYGET, NULL, retVar);

  retVal = volevariantGetInt(retVar);
  volevariantDestroy(retVar);
  return retVal;
}

/*
 * Returns/sets the number of times the movie will be played
 */
void ActiveMovieSetPlayCount(voleControlSite *site, int arg0)
{
  int hr;
  volevariant *argVar;
  volevariantList *argList = volevariantCreateList();

  argVar = volevariantCreate();
  volevariantSetInt(argVar, arg0);
  volevariantAppendList(argList, argVar);

  hr = voleInvokeControlSite(site, 14, INVOKE_PROPERTYPUT, argList, NULL);
  volevariantDestroyList(argList);
}

/*
 * Returns/sets the position where playback will begin
 */
double ActiveMovieGetSelectionStart(voleControlSite *site)
{
  int hr;
  volevariant *retVar = volevariantCreate();
  double retVal;

  hr = voleInvokeControlSite(site, 15, INVOKE_PROPERTYGET, NULL, retVar);

  retVal = volevariantGetDouble(retVar);
  volevariantDestroy(retVar);
  return retVal;
}

/*
 * Returns/sets the position where playback will begin
 */
void ActiveMovieSetSelectionStart(voleControlSite *site, double arg0)
{
  int hr;
  volevariant *argVar;
  volevariantList *argList = volevariantCreateList();

  argVar = volevariantCreate();
  volevariantSetDouble(argVar, arg0);
  volevariantAppendList(argList, argVar);

  hr = voleInvokeControlSite(site, 15, INVOKE_PROPERTYPUT, argList, NULL);
  volevariantDestroyList(argList);
}

/*
 * Returns/sets the position where playback will stop
 */
double ActiveMovieGetSelectionEnd(voleControlSite *site)
{
  int hr;
  volevariant *retVar = volevariantCreate();
  double retVal;

  hr = voleInvokeControlSite(site, 16, INVOKE_PROPERTYGET, NULL, retVar);

  retVal = volevariantGetDouble(retVar);
  volevariantDestroy(retVar);
  return retVal;
}

/*
 * Returns/sets the position where playback will stop
 */
void ActiveMovieSetSelectionEnd(voleControlSite *site, double arg0)
{
  int hr;
  volevariant *argVar;
  volevariantList *argList = volevariantCreateList();

  argVar = volevariantCreate();
  volevariantSetDouble(argVar, arg0);
  volevariantAppendList(argList, argVar);

  hr = voleInvokeControlSite(site, 16, INVOKE_PROPERTYPUT, argList, NULL);
  volevariantDestroyList(argList);
}

/*
 * Returns the current state of the movie clip
 */
int ActiveMovieGetCurrentState(voleControlSite *site)
{
  int hr;
  volevariant *retVar = volevariantCreate();
  int retVal;

  hr = voleInvokeControlSite(site, 17, INVOKE_PROPERTYGET, NULL, retVar);

  retVal = volevariantGetInt(retVar);
  volevariantDestroy(retVar);
  return retVal;
}

/*
 * Returns/sets the rate of the multimedia stream
 */
double ActiveMovieGetRate(voleControlSite *site)
{
  int hr;
  volevariant *retVar = volevariantCreate();
  double retVal;

  hr = voleInvokeControlSite(site, 18, INVOKE_PROPERTYGET, NULL, retVar);

  retVal = volevariantGetDouble(retVar);
  volevariantDestroy(retVar);
  return retVal;
}

/*
 * Returns/sets the rate of the multimedia stream
 */
void ActiveMovieSetRate(voleControlSite *site, double arg0)
{
  int hr;
  volevariant *argVar;
  volevariantList *argList = volevariantCreateList();

  argVar = volevariantCreate();
  volevariantSetDouble(argVar, arg0);
  volevariantAppendList(argList, argVar);

  hr = voleInvokeControlSite(site, 18, INVOKE_PROPERTYPUT, argList, NULL);
  volevariantDestroyList(argList);
}

/*
 * Returns/sets the audio volume of the multimedia stream
 */
int ActiveMovieGetVolume(voleControlSite *site)
{
  int hr;
  volevariant *retVar = volevariantCreate();
  int retVal;

  hr = voleInvokeControlSite(site, 19, INVOKE_PROPERTYGET, NULL, retVar);

  retVal = volevariantGetInt(retVar);
  volevariantDestroy(retVar);
  return retVal;
}

/*
 * Returns/sets the audio volume of the multimedia stream
 */
void ActiveMovieSetVolume(voleControlSite *site, int arg0)
{
  int hr;
  volevariant *argVar;
  volevariantList *argList = volevariantCreateList();

  argVar = volevariantCreate();
  volevariantSetInt(argVar, arg0);
  volevariantAppendList(argList, argVar);

  hr = voleInvokeControlSite(site, 19, INVOKE_PROPERTYPUT, argList, NULL);
  volevariantDestroyList(argList);
}

/*
 * Returns/sets the stereo balance of the multimedia stream
 */
int ActiveMovieGetBalance(voleControlSite *site)
{
  int hr;
  volevariant *retVar = volevariantCreate();
  int retVal;

  hr = voleInvokeControlSite(site, 20, INVOKE_PROPERTYGET, NULL, retVar);

  retVal = volevariantGetInt(retVar);
  volevariantDestroy(retVar);
  return retVal;
}

/*
 * Returns/sets the stereo balance of the multimedia stream
 */
void ActiveMovieSetBalance(voleControlSite *site, int arg0)
{
  int hr;
  volevariant *argVar;
  volevariantList *argList = volevariantCreateList();

  argVar = volevariantCreate();
  volevariantSetInt(argVar, arg0);
  volevariantAppendList(argList, argVar);

  hr = voleInvokeControlSite(site, 20, INVOKE_PROPERTYPUT, argList, NULL);
  volevariantDestroyList(argList);
}

/*
 * Enables/disables the right-click context menu
 */
vbool ActiveMovieGetEnableContextMenu(voleControlSite *site)
{
  int hr;
  volevariant *retVar = volevariantCreate();
  vbool retVal;

  hr = voleInvokeControlSite(site, 21, INVOKE_PROPERTYGET, NULL, retVar);

  retVal = volevariantGetBool(retVar);
  volevariantDestroy(retVar);
  return retVal;
}

/*
 * Enables/disables the right-click context menu
 */
void ActiveMovieSetEnableContextMenu(voleControlSite *site, vbool arg0)
{
  int hr;
  volevariant *argVar;
  volevariantList *argList = volevariantCreateList();

  argVar = volevariantCreate();
  volevariantSetBool(argVar, arg0);
  volevariantAppendList(argList, argVar);

  hr = voleInvokeControlSite(site, 21, INVOKE_PROPERTYPUT, argList, NULL);
  volevariantDestroyList(argList);
}

/*
 * Shows/hides the display panel
 */
vbool ActiveMovieGetShowDisplay(voleControlSite *site)
{
  int hr;
  volevariant *retVar = volevariantCreate();
  vbool retVal;

  hr = voleInvokeControlSite(site, 22, INVOKE_PROPERTYGET, NULL, retVar);

  retVal = volevariantGetBool(retVar);
  volevariantDestroy(retVar);
  return retVal;
}

/*
 * Shows/hides the display panel
 */
void ActiveMovieSetShowDisplay(voleControlSite *site, vbool arg0)
{
  int hr;
  volevariant *argVar;
  volevariantList *argList = volevariantCreateList();

  argVar = volevariantCreate();
  volevariantSetBool(argVar, arg0);
  volevariantAppendList(argList, argVar);

  hr = voleInvokeControlSite(site, 22, INVOKE_PROPERTYPUT, argList, NULL);
  volevariantDestroyList(argList);
}

/*
 * Shows/hides the control panel
 */
vbool ActiveMovieGetShowControls(voleControlSite *site)
{
  int hr;
  volevariant *retVar = volevariantCreate();
  vbool retVal;

  hr = voleInvokeControlSite(site, 23, INVOKE_PROPERTYGET, NULL, retVar);

  retVal = volevariantGetBool(retVar);
  volevariantDestroy(retVar);
  return retVal;
}

/*
 * Shows/hides the control panel
 */
void ActiveMovieSetShowControls(voleControlSite *site, vbool arg0)
{
  int hr;
  volevariant *argVar;
  volevariantList *argList = volevariantCreateList();

  argVar = volevariantCreate();
  volevariantSetBool(argVar, arg0);
  volevariantAppendList(argList, argVar);

  hr = voleInvokeControlSite(site, 23, INVOKE_PROPERTYPUT, argList, NULL);
  volevariantDestroyList(argList);
}

/*
 * Shows/hides the position buttons in the control panel
 */
vbool ActiveMovieGetShowPositionControls(voleControlSite *site)
{
  int hr;
  volevariant *retVar = volevariantCreate();
  vbool retVal;

  hr = voleInvokeControlSite(site, 24, INVOKE_PROPERTYGET, NULL, retVar);

  retVal = volevariantGetBool(retVar);
  volevariantDestroy(retVar);
  return retVal;
}

/*
 * Shows/hides the position buttons in the control panel
 */
void ActiveMovieSetShowPositionControls(voleControlSite *site, vbool arg0)
{
  int hr;
  volevariant *argVar;
  volevariantList *argList = volevariantCreateList();

  argVar = volevariantCreate();
  volevariantSetBool(argVar, arg0);
  volevariantAppendList(argList, argVar);

  hr = voleInvokeControlSite(site, 24, INVOKE_PROPERTYPUT, argList, NULL);
  volevariantDestroyList(argList);
}

/*
 * Shows/hides the selection buttons in the control panel
 */
vbool ActiveMovieGetShowSelectionControls(voleControlSite *site)
{
  int hr;
  volevariant *retVar = volevariantCreate();
  vbool retVal;

  hr = voleInvokeControlSite(site, 25, INVOKE_PROPERTYGET, NULL, retVar);

  retVal = volevariantGetBool(retVar);
  volevariantDestroy(retVar);
  return retVal;
}

/*
 * Shows/hides the selection buttons in the control panel
 */
void ActiveMovieSetShowSelectionControls(voleControlSite *site, vbool arg0)
{
  int hr;
  volevariant *argVar;
  volevariantList *argList = volevariantCreateList();

  argVar = volevariantCreate();
  volevariantSetBool(argVar, arg0);
  volevariantAppendList(argList, argVar);

  hr = voleInvokeControlSite(site, 25, INVOKE_PROPERTYPUT, argList, NULL);
  volevariantDestroyList(argList);
}

/*
 * Shows/hides the tracker bar in the control panel
 */
vbool ActiveMovieGetShowTracker(voleControlSite *site)
{
  int hr;
  volevariant *retVar = volevariantCreate();
  vbool retVal;

  hr = voleInvokeControlSite(site, 26, INVOKE_PROPERTYGET, NULL, retVar);

  retVal = volevariantGetBool(retVar);
  volevariantDestroy(retVar);
  return retVal;
}

/*
 * Shows/hides the tracker bar in the control panel
 */
void ActiveMovieSetShowTracker(voleControlSite *site, vbool arg0)
{
  int hr;
  volevariant *argVar;
  volevariantList *argList = volevariantCreateList();

  argVar = volevariantCreate();
  volevariantSetBool(argVar, arg0);
  volevariantAppendList(argList, argVar);

  hr = voleInvokeControlSite(site, 26, INVOKE_PROPERTYPUT, argList, NULL);
  volevariantDestroyList(argList);
}

/*
 * Enables/disables the position buttons in the control panel
 */
vbool ActiveMovieGetEnablePositionControls(voleControlSite *site)
{
  int hr;
  volevariant *retVar = volevariantCreate();
  vbool retVal;

  hr = voleInvokeControlSite(site, 27, INVOKE_PROPERTYGET, NULL, retVar);

  retVal = volevariantGetBool(retVar);
  volevariantDestroy(retVar);
  return retVal;
}

/*
 * Enables/disables the position buttons in the control panel
 */
void ActiveMovieSetEnablePositionControls(voleControlSite *site, vbool arg0)
{
  int hr;
  volevariant *argVar;
  volevariantList *argList = volevariantCreateList();

  argVar = volevariantCreate();
  volevariantSetBool(argVar, arg0);
  volevariantAppendList(argList, argVar);

  hr = voleInvokeControlSite(site, 27, INVOKE_PROPERTYPUT, argList, NULL);
  volevariantDestroyList(argList);
}

/*
 * Enables/disables the selection buttons in the control panel
 */
vbool ActiveMovieGetEnableSelectionControls(voleControlSite *site)
{
  int hr;
  volevariant *retVar = volevariantCreate();
  vbool retVal;

  hr = voleInvokeControlSite(site, 28, INVOKE_PROPERTYGET, NULL, retVar);

  retVal = volevariantGetBool(retVar);
  volevariantDestroy(retVar);
  return retVal;
}

/*
 * Enables/disables the selection buttons in the control panel
 */
void ActiveMovieSetEnableSelectionControls(voleControlSite *site, vbool arg0)
{
  int hr;
  volevariant *argVar;
  volevariantList *argList = volevariantCreateList();

  argVar = volevariantCreate();
  volevariantSetBool(argVar, arg0);
  volevariantAppendList(argList, argVar);

  hr = voleInvokeControlSite(site, 28, INVOKE_PROPERTYPUT, argList, NULL);
  volevariantDestroyList(argList);
}

/*
 * Enables/disables the tracker bar in the control panel
 */
vbool ActiveMovieGetEnableTracker(voleControlSite *site)
{
  int hr;
  volevariant *retVar = volevariantCreate();
  vbool retVal;

  hr = voleInvokeControlSite(site, 29, INVOKE_PROPERTYGET, NULL, retVar);

  retVal = volevariantGetBool(retVar);
  volevariantDestroy(retVar);
  return retVal;
}

/*
 * Enables/disables the tracker bar in the control panel
 */
void ActiveMovieSetEnableTracker(voleControlSite *site, vbool arg0)
{
  int hr;
  volevariant *argVar;
  volevariantList *argList = volevariantCreateList();

  argVar = volevariantCreate();
  volevariantSetBool(argVar, arg0);
  volevariantAppendList(argList, argVar);

  hr = voleInvokeControlSite(site, 29, INVOKE_PROPERTYPUT, argList, NULL);
  volevariantDestroyList(argList);
}

/*
 * Allows/disallows hiding the display panel at run time
 */
vbool ActiveMovieGetAllowHideDisplay(voleControlSite *site)
{
  int hr;
  volevariant *retVar = volevariantCreate();
  vbool retVal;

  hr = voleInvokeControlSite(site, 30, INVOKE_PROPERTYGET, NULL, retVar);

  retVal = volevariantGetBool(retVar);
  volevariantDestroy(retVar);
  return retVal;
}

/*
 * Allows/disallows hiding the display panel at run time
 */
void ActiveMovieSetAllowHideDisplay(voleControlSite *site, vbool arg0)
{
  int hr;
  volevariant *argVar;
  volevariantList *argList = volevariantCreateList();

  argVar = volevariantCreate();
  volevariantSetBool(argVar, arg0);
  volevariantAppendList(argList, argVar);

  hr = voleInvokeControlSite(site, 30, INVOKE_PROPERTYPUT, argList, NULL);
  volevariantDestroyList(argList);
}

/*
 * Allows/disallows hiding the control panel at run time
 */
vbool ActiveMovieGetAllowHideControls(voleControlSite *site)
{
  int hr;
  volevariant *retVar = volevariantCreate();
  vbool retVal;

  hr = voleInvokeControlSite(site, 31, INVOKE_PROPERTYGET, NULL, retVar);

  retVal = volevariantGetBool(retVar);
  volevariantDestroy(retVar);
  return retVal;
}

/*
 * Allows/disallows hiding the control panel at run time
 */
void ActiveMovieSetAllowHideControls(voleControlSite *site, vbool arg0)
{
  int hr;
  volevariant *argVar;
  volevariantList *argList = volevariantCreateList();

  argVar = volevariantCreate();
  volevariantSetBool(argVar, arg0);
  volevariantAppendList(argList, argVar);

  hr = voleInvokeControlSite(site, 31, INVOKE_PROPERTYPUT, argList, NULL);
  volevariantDestroyList(argList);
}

/*
 * Returns/sets the display mode (time or frames)
 */
int ActiveMovieGetDisplayMode(voleControlSite *site)
{
  int hr;
  volevariant *retVar = volevariantCreate();
  int retVal;

  hr = voleInvokeControlSite(site, 32, INVOKE_PROPERTYGET, NULL, retVar);

  retVal = volevariantGetInt(retVar);
  volevariantDestroy(retVar);
  return retVal;
}

/*
 * Returns/sets the display mode (time or frames)
 */
void ActiveMovieSetDisplayMode(voleControlSite *site, int arg0)
{
  int hr;
  volevariant *argVar;
  volevariantList *argList = volevariantCreateList();

  argVar = volevariantCreate();
  volevariantSetInt(argVar, arg0);
  volevariantAppendList(argList, argVar);

  hr = voleInvokeControlSite(site, 32, INVOKE_PROPERTYPUT, argList, NULL);
  volevariantDestroyList(argList);
}

/*
 * Allows/disallows changing the display mode at run time
 */
vbool ActiveMovieGetAllowChangeDisplayMode(voleControlSite *site)
{
  int hr;
  volevariant *retVar = volevariantCreate();
  vbool retVal;

  hr = voleInvokeControlSite(site, 33, INVOKE_PROPERTYGET, NULL, retVar);

  retVal = volevariantGetBool(retVar);
  volevariantDestroy(retVar);
  return retVal;
}

/*
 * Allows/disallows changing the display mode at run time
 */
void ActiveMovieSetAllowChangeDisplayMode(voleControlSite *site, vbool arg0)
{
  int hr;
  volevariant *argVar;
  volevariantList *argList = volevariantCreateList();

  argVar = volevariantCreate();
  volevariantSetBool(argVar, arg0);
  volevariantAppendList(argList, argVar);

  hr = voleInvokeControlSite(site, 33, INVOKE_PROPERTYPUT, argList, NULL);
  volevariantDestroyList(argList);
}

/*
 * Returns/sets the current filter graph
 */
LPUNKNOWN ActiveMovieGetFilterGraph(voleControlSite *site)
{
  int hr;
  volevariant *retVar = volevariantCreate();
  LPUNKNOWN retVal;

  hr = voleInvokeControlSite(site, 34, INVOKE_PROPERTYGET, NULL, retVar);

  retVal = (LPUNKNOWN)volevariantGetUnknown(retVar);
  volevariantDestroy(retVar);
  return retVal;
}

/*
 * Returns/sets the current filter graph
 */
void ActiveMovieSetFilterGraph(voleControlSite *site, LPUNKNOWN arg0)
{
  int hr;
  volevariant *argVar;
  volevariantList *argList = volevariantCreateList();

  argVar = volevariantCreate();
  volevariantSetUnknown(argVar, arg0);
  volevariantAppendList(argList, argVar);

  hr = voleInvokeControlSite(site, 34, INVOKE_PROPERTYPUT, argList, NULL);
  volevariantDestroyList(argList);
}


/*
 * Returns/sets the foreground color of the display panel
 */
int ActiveMovieGetDisplayForeColor(voleControlSite *site)
{
  int hr;
  volevariant *retVar = volevariantCreate();
  int retVal;

  hr = voleInvokeControlSite(site, 36, INVOKE_PROPERTYGET, NULL, retVar);

  retVal = volevariantGetInt(retVar);
  volevariantDestroy(retVar);
  return retVal;
}

/*
 * Returns/sets the foreground color of the display panel
 */
void ActiveMovieSetDisplayForeColor(voleControlSite *site, int arg0)
{
  int hr;
  volevariant *argVar;
  volevariantList *argList = volevariantCreateList();

  argVar = volevariantCreate();
  volevariantSetInt(argVar, arg0);
  volevariantAppendList(argList, argVar);

  hr = voleInvokeControlSite(site, 36, INVOKE_PROPERTYPUT, argList, NULL);
  volevariantDestroyList(argList);
}

/*
 * Returns/sets the background color of the display panel
 */
int ActiveMovieGetDisplayBackColor(voleControlSite *site)
{
  int hr;
  volevariant *retVar = volevariantCreate();
  int retVal;

  hr = voleInvokeControlSite(site, 37, INVOKE_PROPERTYGET, NULL, retVar);

  retVal = volevariantGetInt(retVar);
  volevariantDestroy(retVar);
  return retVal;
}

/*
 * Returns/sets the background color of the display panel
 */
void ActiveMovieSetDisplayBackColor(voleControlSite *site, int arg0)
{
  int hr;
  volevariant *argVar;
  volevariantList *argList = volevariantCreateList();

  argVar = volevariantCreate();
  volevariantSetInt(argVar, arg0);
  volevariantAppendList(argList, argVar);

  hr = voleInvokeControlSite(site, 37, INVOKE_PROPERTYPUT, argList, NULL);
  volevariantDestroyList(argList);
}

/*
 * Returns/sets the movie window size
 */
int ActiveMovieGetMovieWindowSize(voleControlSite *site)
{
  int hr;
  volevariant *retVar = volevariantCreate();
  int retVal;

  hr = voleInvokeControlSite(site, 38, INVOKE_PROPERTYGET, NULL, retVar);

  retVal = volevariantGetInt(retVar);
  volevariantDestroy(retVar);
  return retVal;
}

/*
 * Returns/sets the movie window size
 */
void ActiveMovieSetMovieWindowSize(voleControlSite *site, int arg0)
{
  int hr;
  volevariant *argVar;
  volevariantList *argList = volevariantCreateList();

  argVar = volevariantCreate();
  volevariantSetInt(argVar, arg0);
  volevariantAppendList(argList, argVar);

  hr = voleInvokeControlSite(site, 38, INVOKE_PROPERTYPUT, argList, NULL);
  volevariantDestroyList(argList);
}

/*
 * Indicates whether the media clip will run full screen
 */
vbool ActiveMovieGetFullScreenMode(voleControlSite *site)
{
  int hr;
  volevariant *retVar = volevariantCreate();
  vbool retVal;

  hr = voleInvokeControlSite(site, 39, INVOKE_PROPERTYGET, NULL, retVar);

  retVal = volevariantGetBool(retVar);
  volevariantDestroy(retVar);
  return retVal;
}

/*
 * Indicates whether the media clip will run full screen
 */
void ActiveMovieSetFullScreenMode(voleControlSite *site, vbool arg0)
{
  int hr;
  volevariant *argVar;
  volevariantList *argList = volevariantCreateList();

  argVar = volevariantCreate();
  volevariantSetBool(argVar, arg0);
  volevariantAppendList(argList, argVar);

  hr = voleInvokeControlSite(site, 39, INVOKE_PROPERTYPUT, argList, NULL);
  volevariantDestroyList(argList);
}

/*
 * Indicates whether the Control will start playing when activated
 */
vbool ActiveMovieGetAutoStart(voleControlSite *site)
{
  int hr;
  volevariant *retVar = volevariantCreate();
  vbool retVal;

  hr = voleInvokeControlSite(site, 40, INVOKE_PROPERTYGET, NULL, retVar);

  retVal = volevariantGetBool(retVar);
  volevariantDestroy(retVar);
  return retVal;
}

/*
 * Indicates whether the Control will start playing when activated
 */
void ActiveMovieSetAutoStart(voleControlSite *site, vbool arg0)
{
  int hr;
  volevariant *argVar;
  volevariantList *argList = volevariantCreateList();

  argVar = volevariantCreate();
  volevariantSetBool(argVar, arg0);
  volevariantAppendList(argList, argVar);

  hr = voleInvokeControlSite(site, 40, INVOKE_PROPERTYPUT, argList, NULL);
  volevariantDestroyList(argList);
}

/*
 * Indicates whether the media clip will rewind automatically after
 * playing
 */
vbool ActiveMovieGetAutoRewind(voleControlSite *site)
{
  int hr;
  volevariant *retVar = volevariantCreate();
  vbool retVal;

  hr = voleInvokeControlSite(site, 41, INVOKE_PROPERTYGET, NULL, retVar);

  retVal = volevariantGetBool(retVar);
  volevariantDestroy(retVar);
  return retVal;
}

/*
 * Indicates whether the media clip will rewind automatically after
 * playing
 */
void ActiveMovieSetAutoRewind(voleControlSite *site, vbool arg0)
{
  int hr;
  volevariant *argVar;
  volevariantList *argList = volevariantCreateList();

  argVar = volevariantCreate();
  volevariantSetBool(argVar, arg0);
  volevariantAppendList(argList, argVar);

  hr = voleInvokeControlSite(site, 41, INVOKE_PROPERTYPUT, argList, NULL);
  volevariantDestroyList(argList);
}

/*
 * Returns the handle of the control window
 */
int ActiveMovieGethWnd(voleControlSite *site)
{
  int hr;
  volevariant *retVar = volevariantCreate();
  int retVal;

  hr = voleInvokeControlSite(site, -515, INVOKE_PROPERTYGET, NULL, retVar);

  retVal = volevariantGetInt(retVar);
  volevariantDestroy(retVar);
  return retVal;
}

/*
 * Returns/sets the appearance
 */
int ActiveMovieGetAppearance(voleControlSite *site)
{
  int hr;
  volevariant *retVar = volevariantCreate();
  int retVal;

  hr = voleInvokeControlSite(site, -520, INVOKE_PROPERTYGET, NULL, retVar);

  retVal = volevariantGetInt(retVar);
  volevariantDestroy(retVar);
  return retVal;
}

/*
 * Returns/sets the appearance
 */
void ActiveMovieSetAppearance(voleControlSite *site, int arg0)
{
  int hr;
  volevariant *argVar;
  volevariantList *argList = volevariantCreateList();

  argVar = volevariantCreate();
  volevariantSetInt(argVar, arg0);
  volevariantAppendList(argList, argVar);

  hr = voleInvokeControlSite(site, -520, INVOKE_PROPERTYPUT, argList, NULL);
  volevariantDestroyList(argList);
}

/*
 * Returns/sets the border style
 */
int ActiveMovieGetBorderStyle(voleControlSite *site)
{
  int hr;
  volevariant *retVar = volevariantCreate();
  int retVal;

  hr = voleInvokeControlSite(site, 42, INVOKE_PROPERTYGET, NULL, retVar);

  retVal = volevariantGetInt(retVar);
  volevariantDestroy(retVar);
  return retVal;
}

/*
 * Returns/sets the border style
 */
void ActiveMovieSetBorderStyle(voleControlSite *site, int arg0)
{
  int hr;
  volevariant *argVar;
  volevariantList *argList = volevariantCreateList();

  argVar = volevariantCreate();
  volevariantSetInt(argVar, arg0);
  volevariantAppendList(argList, argVar);

  hr = voleInvokeControlSite(site, 42, INVOKE_PROPERTYPUT, argList, NULL);
  volevariantDestroyList(argList);
}

/*
 * Enables/disables the control
 */
vbool ActiveMovieGetEnabled(voleControlSite *site)
{
  int hr;
  volevariant *retVar = volevariantCreate();
  vbool retVal;

  hr = voleInvokeControlSite(site, -514, INVOKE_PROPERTYGET, NULL, retVar);

  retVal = volevariantGetBool(retVar);
  volevariantDestroy(retVar);
  return retVal;
}

/*
 * Enables/disables the control
 */
void ActiveMovieSetEnabled(voleControlSite *site, vbool arg0)
{
  int hr;
  volevariant *argVar;
  volevariantList *argList = volevariantCreateList();

  argVar = volevariantCreate();
  volevariantSetBool(argVar, arg0);
  volevariantAppendList(argList, argVar);

  hr = voleInvokeControlSite(site, -514, INVOKE_PROPERTYPUT, argList, NULL);
  volevariantDestroyList(argList);
}

int ActiveMovieGetInfo(voleControlSite *site)
{
  int hr;
  volevariant *retVar = volevariantCreate();
  int retVal;

  hr = voleInvokeControlSite(site, 1610743885, INVOKE_PROPERTYGET, NULL, retVar);

  retVal = volevariantGetInt(retVar);
  volevariantDestroy(retVar);
  return retVal;
}

/* Event notifcation templates */

/*
 * Indicates that the current state of the movie has changed
 */
void OnActiveMovieStateChange(voleControlSite *site, int oldState, int newState)
{
  /* Put your code for handling StateChange event here. */
}

/*
 * Indicates that the current position of the movie has changed
 */
void OnActiveMoviePositionChange(voleControlSite *site, double oldPosition, double newPosition)
{
  /* Put your code for handling PositionChange event here. */
}

/*
 * ActiveMovie Control's progress timer
 */
void OnActiveMovieTimer(voleControlSite *site)
{
  /* Put your code for handling Timer event here. */
}

/*
 * Reports that an asynchronous operation to open a file has completed
 * successfully
 */
void OnActiveMovieOpenComplete(voleControlSite *site)
{
  /* Put your code for handling OpenComplete event here. */
}

void OnActiveMovieClick(voleControlSite *site)
{
  /* Put your code for handling Click event here. */
}

void OnActiveMovieDblClick(voleControlSite *site)
{
  /* Put your code for handling DblClick event here. */
}

void OnActiveMovieKeyDown(voleControlSite *site, short *KeyCode, short Shift)
{
  /* Put your code for handling KeyDown event here. */
}

void OnActiveMovieKeyUp(voleControlSite *site, short *KeyCode, short Shift)
{
  /* Put your code for handling KeyUp event here. */
}

void OnActiveMovieKeyPress(voleControlSite *site, short *KeyAscii)
{
  /* Put your code for handling KeyPress event here. */
}

void OnActiveMovieMouseDown(voleControlSite *site, short Button, short Shift, int x, int y)
{
  /* Put your code for handling MouseDown event here. */
}

void OnActiveMovieMouseMove(voleControlSite *site, short Button, short Shift, int x, int y)
{
  /* Put your code for handling MouseMove event here. */
}

void OnActiveMovieMouseUp(voleControlSite *site, short Button, short Shift, int x, int y)
{
  /* Put your code for handling MouseUp event here. */
}

void OnActiveMovieError(voleControlSite *site, short SCode, vstr *Description, vstr *Source, short *CancelDisplay)
{
  /* Put your code for handling Error event here. */
}

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
void ActiveMovieNotifyEvent(voleControlSite *site, int dispid, volevariantList *list)
{
  switch(dispid) {
    case 1:
      OnActiveMovieStateChange(site,
        volevariantGetInt(volevariantGetListAt(list, 0)),
        volevariantGetInt(volevariantGetListAt(list, 1))
      );
      break;
    case 2:
      OnActiveMoviePositionChange(site,
        volevariantGetDouble(volevariantGetListAt(list, 0)),
        volevariantGetDouble(volevariantGetListAt(list, 1))
      );
      break;
    case 3:
      OnActiveMovieTimer(site);
      break;
    case 50:
      OnActiveMovieOpenComplete(site);
      break;
    case -600:
      OnActiveMovieClick(site);
      break;
    case -601:
      OnActiveMovieDblClick(site);
      break;
    case -602:
      OnActiveMovieKeyDown(site,
        volevariantGetShortRef(volevariantGetListAt(list, 0)),
        volevariantGetShort(volevariantGetListAt(list, 1))
      );
      break;
    case -604:
      OnActiveMovieKeyUp(site,
        volevariantGetShortRef(volevariantGetListAt(list, 0)),
        volevariantGetShort(volevariantGetListAt(list, 1))
      );
      break;
    case -603:
      OnActiveMovieKeyPress(site,
        volevariantGetShortRef(volevariantGetListAt(list, 0))
      );
      break;
    case -605:
      OnActiveMovieMouseDown(site,
        volevariantGetShort(volevariantGetListAt(list, 0)),
        volevariantGetShort(volevariantGetListAt(list, 1)),
        volevariantGetInt(volevariantGetListAt(list, 2)),
        volevariantGetInt(volevariantGetListAt(list, 3))
      );
      break;
    case -606:
      OnActiveMovieMouseMove(site,
        volevariantGetShort(volevariantGetListAt(list, 0)),
        volevariantGetShort(volevariantGetListAt(list, 1)),
        volevariantGetInt(volevariantGetListAt(list, 2)),
        volevariantGetInt(volevariantGetListAt(list, 3))
      );
      break;
    case -607:
      OnActiveMovieMouseUp(site,
        volevariantGetShort(volevariantGetListAt(list, 0)),
        volevariantGetShort(volevariantGetListAt(list, 1)),
        volevariantGetInt(volevariantGetListAt(list, 2)),
        volevariantGetInt(volevariantGetListAt(list, 3))
      );
      break;
    case 999:
      OnActiveMovieError(site,
        volevariantGetShort(volevariantGetListAt(list, 0)),
        volevariantGetString(volevariantGetListAt(list, 1)),
        volevariantGetString(volevariantGetListAt(list, 2)),
        volevariantGetBoolRef(volevariantGetListAt(list, 3))
      );
      break;
  }
}

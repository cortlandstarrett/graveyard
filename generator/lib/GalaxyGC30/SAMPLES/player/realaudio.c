/* $Id: realaudio.c,v 1.1 1997/09/29 22:22:31 alex Exp $ */
/*
 * Helper functions for ActiveX (OLE) control RealAudio:
 * {CFCDAA03-8BE4-11CF-B84B-0020AFBBCCFA}
 * 
 * This file automatically generated.
 */

#include "RealAudio.h"

/*
 * Property get/put and method invocation
 */

/*
 * Returns/Sets the source of the RealAudio clip. Can be pnm:, file: or
 * http: protocol.
 */
vstr *RealAudioGetSource(voleControlSite *site)
{
  int hr;
  volevariant *retVar = volevariantCreate();
  vstr *retVal;

  hr = voleInvokeControlSite(site, 102, INVOKE_PROPERTYGET, NULL, retVar);

  retVal = volevariantGetString(retVar);
  volevariantDestroy(retVar);
  return retVal;
}

/*
 * Returns/Sets the source of the RealAudio clip. Can be pnm:, file: or
 * http: protocol.
 */
void RealAudioSetSource(voleControlSite *site, vstr *arg0)
{
  int hr;
  volevariant *argVar;
  volevariantList *argList = volevariantCreateList();

  argVar = volevariantCreate();
  volevariantSetString(argVar, arg0);
  volevariantAppendList(argList, argVar);

  hr = voleInvokeControlSite(site, 102, INVOKE_PROPERTYPUT, argList, NULL);
  volevariantDestroyList(argList);
}

/*
 * Returns/Sets the console name for this control. Consoles with the same
 * name work in unison.
 */
vstr *RealAudioGetConsole(voleControlSite *site)
{
  int hr;
  volevariant *retVar = volevariantCreate();
  vstr *retVal;

  hr = voleInvokeControlSite(site, 103, INVOKE_PROPERTYGET, NULL, retVar);

  retVal = volevariantGetString(retVar);
  volevariantDestroy(retVar);
  return retVal;
}

/*
 * Returns/Sets the console name for this control. Consoles with the same
 * name work in unison.
 */
void RealAudioSetConsole(voleControlSite *site, vstr *arg0)
{
  int hr;
  volevariant *argVar;
  volevariantList *argList = volevariantCreateList();

  argVar = volevariantCreate();
  volevariantSetString(argVar, arg0);
  volevariantAppendList(argList, argVar);

  hr = voleInvokeControlSite(site, 103, INVOKE_PROPERTYPUT, argList, NULL);
  volevariantDestroyList(argList);
}

/*
 * Returns/Sets the visible components of the control (like PlayButton,
 * StopButton, etc.).
 */
vstr *RealAudioGetControls(voleControlSite *site)
{
  int hr;
  volevariant *retVar = volevariantCreate();
  vstr *retVal;

  hr = voleInvokeControlSite(site, 104, INVOKE_PROPERTYGET, NULL, retVar);

  retVal = volevariantGetString(retVar);
  volevariantDestroy(retVar);
  return retVal;
}

/*
 * Returns/Sets the visible components of the control (like PlayButton,
 * StopButton, etc.).
 */
void RealAudioSetControls(voleControlSite *site, vstr *arg0)
{
  int hr;
  volevariant *argVar;
  volevariantList *argList = volevariantCreateList();

  argVar = volevariantCreate();
  volevariantSetString(argVar, arg0);
  volevariantAppendList(argList, argVar);

  hr = voleInvokeControlSite(site, 104, INVOKE_PROPERTYPUT, argList, NULL);
  volevariantDestroyList(argList);
}

/*
 * Returns/Sets the visibility of labels in the Information Panel of the
 * control.
 */
vbool RealAudioGetNoLabels(voleControlSite *site)
{
  int hr;
  volevariant *retVar = volevariantCreate();
  vbool retVal;

  hr = voleInvokeControlSite(site, 105, INVOKE_PROPERTYGET, NULL, retVar);

  retVal = volevariantGetBool(retVar);
  volevariantDestroy(retVar);
  return retVal;
}

/*
 * Returns/Sets the visibility of labels in the Information Panel of the
 * control.
 */
void RealAudioSetNoLabels(voleControlSite *site, vbool arg0)
{
  int hr;
  volevariant *argVar;
  volevariantList *argList = volevariantCreateList();

  argVar = volevariantCreate();
  volevariantSetBool(argVar, arg0);
  volevariantAppendList(argList, argVar);

  hr = voleInvokeControlSite(site, 105, INVOKE_PROPERTYPUT, argList, NULL);
  volevariantDestroyList(argList);
}

/*
 * Returns/Sets whether or not the control will automatically start
 * playing once the source data is available.
 */
vbool RealAudioGetAutoStart(voleControlSite *site)
{
  int hr;
  volevariant *retVar = volevariantCreate();
  vbool retVal;

  hr = voleInvokeControlSite(site, 106, INVOKE_PROPERTYGET, NULL, retVar);

  retVal = volevariantGetBool(retVar);
  volevariantDestroy(retVar);
  return retVal;
}

/*
 * Returns/Sets whether or not the control will automatically start
 * playing once the source data is available.
 */
void RealAudioSetAutoStart(voleControlSite *site, vbool arg0)
{
  int hr;
  volevariant *argVar;
  volevariantList *argList = volevariantCreateList();

  argVar = volevariantCreate();
  volevariantSetBool(argVar, arg0);
  volevariantAppendList(argList, argVar);

  hr = voleInvokeControlSite(site, 106, INVOKE_PROPERTYPUT, argList, NULL);
  volevariantDestroyList(argList);
}

/*
 * Returns/Sets whether or not the control will automatically activate
 * URL events associated with the RealAudio stream. If FALSE, the OnGotoURL event will be fired instead.
 */
vbool RealAudioGetAutoGotoURL(voleControlSite *site)
{
  int hr;
  volevariant *retVar = volevariantCreate();
  vbool retVal;

  hr = voleInvokeControlSite(site, 107, INVOKE_PROPERTYGET, NULL, retVar);

  retVal = volevariantGetBool(retVar);
  volevariantDestroy(retVar);
  return retVal;
}

/*
 * Returns/Sets whether or not the control will automatically activate
 * URL events associated with the RealAudio stream. If FALSE, the OnGotoURL event will be fired instead.
 */
void RealAudioSetAutoGotoURL(voleControlSite *site, vbool arg0)
{
  int hr;
  volevariant *argVar;
  volevariantList *argList = volevariantCreateList();

  argVar = volevariantCreate();
  volevariantSetBool(argVar, arg0);
  volevariantAppendList(argList, argVar);

  hr = voleInvokeControlSite(site, 107, INVOKE_PROPERTYPUT, argList, NULL);
  volevariantDestroyList(argList);
}

/*
 * Returns/Sets the window name for this control.
 */
vstr *RealAudioGetWindowName(voleControlSite *site)
{
  int hr;
  volevariant *retVar = volevariantCreate();
  vstr *retVal;

  hr = voleInvokeControlSite(site, 108, INVOKE_PROPERTYGET, NULL, retVar);

  retVal = volevariantGetString(retVar);
  volevariantDestroy(retVar);
  return retVal;
}

/*
 * Returns/Sets the window name for this control.
 */
void RealAudioSetWindowName(voleControlSite *site, vstr *arg0)
{
  int hr;
  volevariant *argVar;
  volevariantList *argList = volevariantCreateList();

  argVar = volevariantCreate();
  volevariantSetString(argVar, arg0);
  volevariantAppendList(argList, argVar);

  hr = voleInvokeControlSite(site, 108, INVOKE_PROPERTYPUT, argList, NULL);
  volevariantDestroyList(argList);
}

/*
 * Play or Pause the RealAudio clip, as if the play/pause button was
 * pressed.
 */
void RealAudioDoPlayPause(voleControlSite *site)
{
  int hr;

  hr = voleInvokeControlSite(site, 201, INVOKE_FUNC, NULL, NULL);
}

/*
 * Stop the RealAudio clip, as if the stop button was pressed.
 */
void RealAudioDoStop(voleControlSite *site)
{
  int hr;

  hr = voleInvokeControlSite(site, 202, INVOKE_FUNC, NULL, NULL);
}

/*
 * Skip to the next RealAudio clip in a multi-part RealAudio play list.
 */
void RealAudioDoNextItem(voleControlSite *site)
{
  int hr;

  hr = voleInvokeControlSite(site, 203, INVOKE_FUNC, NULL, NULL);
}

/*
 * Skip to the previous RealAudio clip in a multi-part RealAudio play
 * list.
 */
void RealAudioDoPrevItem(voleControlSite *site)
{
  int hr;

  hr = voleInvokeControlSite(site, 204, INVOKE_FUNC, NULL, NULL);
}

/*
 * Determines whether the DoPlayPause method is valid for the control.
 */
vbool RealAudioCanPlayPause(voleControlSite *site)
{
  int hr;
  volevariant *retVar = volevariantCreate();
  vbool retVal;

  hr = voleInvokeControlSite(site, 205, INVOKE_FUNC, NULL, retVar);

  retVal = volevariantGetBool(retVar);
  volevariantDestroy(retVar);
  return retVal;
}

/*
 * Determines whether the DoStop method is valid for the control.
 */
vbool RealAudioCanStop(voleControlSite *site)
{
  int hr;
  volevariant *retVar = volevariantCreate();
  vbool retVal;

  hr = voleInvokeControlSite(site, 206, INVOKE_FUNC, NULL, retVar);

  retVal = volevariantGetBool(retVar);
  volevariantDestroy(retVar);
  return retVal;
}

/*
 * Determines whether the DoNextItem method is valid for the control.
 */
vbool RealAudioHasNextItem(voleControlSite *site)
{
  int hr;
  volevariant *retVar = volevariantCreate();
  vbool retVal;

  hr = voleInvokeControlSite(site, 207, INVOKE_FUNC, NULL, retVar);

  retVal = volevariantGetBool(retVar);
  volevariantDestroy(retVar);
  return retVal;
}

/*
 * Determines whether the DoPrevItem method is valid for the control.
 */
vbool RealAudioHasPrevItem(voleControlSite *site)
{
  int hr;
  volevariant *retVar = volevariantCreate();
  vbool retVal;

  hr = voleInvokeControlSite(site, 208, INVOKE_FUNC, NULL, retVar);

  retVal = volevariantGetBool(retVar);
  volevariantDestroy(retVar);
  return retVal;
}

/*
 * Show copyright information for the control.
 */
void RealAudioAboutBox(voleControlSite *site)
{
  int hr;

  hr = voleInvokeControlSite(site, -552, INVOKE_FUNC, NULL, NULL);
}

/*
 * Show dialog to allow user modification of RealAudio preferences.
 */
void RealAudioEditPreferences(voleControlSite *site)
{
  int hr;

  hr = voleInvokeControlSite(site, 210, INVOKE_FUNC, NULL, NULL);
}

/*
 * Hide or Show the Statistics dialog box.
 */
void RealAudioHideShowStatistics(voleControlSite *site)
{
  int hr;

  hr = voleInvokeControlSite(site, 211, INVOKE_FUNC, NULL, NULL);
}

/*
 * Determines whether the Statistics dialog box is currently visible.
 */
vbool RealAudioIsStatisticsVisible(voleControlSite *site)
{
  int hr;
  volevariant *retVar = volevariantCreate();
  vbool retVal;

  hr = voleInvokeControlSite(site, 212, INVOKE_FUNC, NULL, retVar);

  retVal = volevariantGetBool(retVar);
  volevariantDestroy(retVar);
  return retVal;
}

/*
 * Cause the control to attempt a navigation to the specified URL in the
 * specified frame target. The container must support URL browsing.
 */
void RealAudioDoGotoURL(voleControlSite *site, vstr *url, vstr *target)
{
  int hr;
  volevariant *argVar;
  volevariantList *argList = volevariantCreateList();

  argVar = volevariantCreate();
  volevariantSetString(argVar, url);
  volevariantAppendList(argList, argVar);
  argVar = volevariantCreate();
  volevariantSetString(argVar, target);
  volevariantAppendList(argList, argVar);

  hr = voleInvokeControlSite(site, 213, INVOKE_FUNC, argList, NULL);
  volevariantDestroyList(argList);
}

/* Event notifcation templates */

/*
 * Fired when a URL event has been encountered for the currently playing
 * RealAudio clip. This event will only occur if the AutoGotoURL property is FALSE.
 */
void OnRealAudioOnGotoURL(voleControlSite *site, vstr *url, vstr *target)
{
  /* Put your code for handling OnGotoURL event here. */
}

/*
 * Fired when a clip has been opened by the control.
 */
void OnRealAudioOnClipOpened(voleControlSite *site, vstr *shortClipName, vstr *url)
{
  /* Put your code for handling OnClipOpened event here. */
}

/*
 * Fired to indicate that no clip is currently open by the control.
 */
void OnRealAudioOnClipClosed(voleControlSite *site)
{
  /* Put your code for handling OnClipClosed event here. */
}

/*
 * Fired to indicate that the controls status text is changing.
 */
void OnRealAudioOnShowStatus(voleControlSite *site, vstr *statusText)
{
  /* Put your code for handling OnShowStatus event here. */
}

/*
 * OLE Events notifcation handler
 *
 * To set this function as the event handler for your
 * control site, invoke the following in your code:
 *
 * voleSetControlSiteNotify(site, RealAudioNotifyEvent);
 *
 * You must also enable events of interest to you either
 * in the resource editor, or via the API, using
 * voleSetControlSiteNotifyEvent() or
 * voleSetControlSiteNotifyAllEvents().
 */
void RealAudioNotifyEvent(voleControlSite *site, int dispid, volevariantList *list)
{
  switch(dispid) {
    case 301:
      OnRealAudioOnGotoURL(site,
        volevariantGetString(volevariantGetListAt(list, 0)),
        volevariantGetString(volevariantGetListAt(list, 1))
      );
      break;
    case 302:
      OnRealAudioOnClipOpened(site,
        volevariantGetString(volevariantGetListAt(list, 0)),
        volevariantGetString(volevariantGetListAt(list, 1))
      );
      break;
    case 303:
      OnRealAudioOnClipClosed(site);
      break;
    case 304:
      OnRealAudioOnShowStatus(site,
        volevariantGetString(volevariantGetListAt(list, 0))
      );
      break;
  }
}

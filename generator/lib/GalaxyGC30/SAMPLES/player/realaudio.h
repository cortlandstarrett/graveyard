/* $Id: realaudio.h,v 1.1 1997/09/29 22:22:46 alex Exp $ */
/*
 * Helper functions for ActiveX (OLE) control RealAudio:
 * {CFCDAA03-8BE4-11CF-B84B-0020AFBBCCFA}
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


/*
 * Returns/Sets the source of the RealAudio clip. Can be pnm:, file: or
 * http: protocol.
 */
vstr *RealAudioGetSource(voleControlSite *site);

/*
 * Returns/Sets the source of the RealAudio clip. Can be pnm:, file: or
 * http: protocol.
 */
void RealAudioSetSource(voleControlSite *site, vstr *arg0);

/*
 * Returns/Sets the console name for this control. Consoles with the same
 * name work in unison.
 */
vstr *RealAudioGetConsole(voleControlSite *site);

/*
 * Returns/Sets the console name for this control. Consoles with the same
 * name work in unison.
 */
void RealAudioSetConsole(voleControlSite *site, vstr *arg0);

/*
 * Returns/Sets the visible components of the control (like PlayButton,
 * StopButton, etc.).
 */
vstr *RealAudioGetControls(voleControlSite *site);

/*
 * Returns/Sets the visible components of the control (like PlayButton,
 * StopButton, etc.).
 */
void RealAudioSetControls(voleControlSite *site, vstr *arg0);

/*
 * Returns/Sets the visibility of labels in the Information Panel of the
 * control.
 */
vbool RealAudioGetNoLabels(voleControlSite *site);

/*
 * Returns/Sets the visibility of labels in the Information Panel of the
 * control.
 */
void RealAudioSetNoLabels(voleControlSite *site, vbool arg0);

/*
 * Returns/Sets whether or not the control will automatically start
 * playing once the source data is available.
 */
vbool RealAudioGetAutoStart(voleControlSite *site);

/*
 * Returns/Sets whether or not the control will automatically start
 * playing once the source data is available.
 */
void RealAudioSetAutoStart(voleControlSite *site, vbool arg0);

/*
 * Returns/Sets whether or not the control will automatically activate
 * URL events associated with the RealAudio stream. If FALSE, the OnGotoURL event will be fired instead.
 */
vbool RealAudioGetAutoGotoURL(voleControlSite *site);

/*
 * Returns/Sets whether or not the control will automatically activate
 * URL events associated with the RealAudio stream. If FALSE, the OnGotoURL event will be fired instead.
 */
void RealAudioSetAutoGotoURL(voleControlSite *site, vbool arg0);

/*
 * Returns/Sets the window name for this control.
 */
vstr *RealAudioGetWindowName(voleControlSite *site);

/*
 * Returns/Sets the window name for this control.
 */
void RealAudioSetWindowName(voleControlSite *site, vstr *arg0);

/*
 * Play or Pause the RealAudio clip, as if the play/pause button was
 * pressed.
 */
void RealAudioDoPlayPause(voleControlSite *site);

/*
 * Stop the RealAudio clip, as if the stop button was pressed.
 */
void RealAudioDoStop(voleControlSite *site);

/*
 * Skip to the next RealAudio clip in a multi-part RealAudio play list.
 */
void RealAudioDoNextItem(voleControlSite *site);

/*
 * Skip to the previous RealAudio clip in a multi-part RealAudio play
 * list.
 */
void RealAudioDoPrevItem(voleControlSite *site);

/*
 * Determines whether the DoPlayPause method is valid for the control.
 */
vbool RealAudioCanPlayPause(voleControlSite *site);

/*
 * Determines whether the DoStop method is valid for the control.
 */
vbool RealAudioCanStop(voleControlSite *site);

/*
 * Determines whether the DoNextItem method is valid for the control.
 */
vbool RealAudioHasNextItem(voleControlSite *site);

/*
 * Determines whether the DoPrevItem method is valid for the control.
 */
vbool RealAudioHasPrevItem(voleControlSite *site);

/*
 * Show copyright information for the control.
 */
void RealAudioAboutBox(voleControlSite *site);

/*
 * Show dialog to allow user modification of RealAudio preferences.
 */
void RealAudioEditPreferences(voleControlSite *site);

/*
 * Hide or Show the Statistics dialog box.
 */
void RealAudioHideShowStatistics(voleControlSite *site);

/*
 * Determines whether the Statistics dialog box is currently visible.
 */
vbool RealAudioIsStatisticsVisible(voleControlSite *site);

/*
 * Cause the control to attempt a navigation to the specified URL in the
 * specified frame target. The container must support URL browsing.
 */
void RealAudioDoGotoURL(voleControlSite *site, vstr *url, vstr *target);

/*
 * Fired when a URL event has been encountered for the currently playing
 * RealAudio clip. This event will only occur if the AutoGotoURL property is FALSE.
 */
void OnRealAudioOnGotoURL(voleControlSite *site, vstr *url, vstr *target);

/*
 * Fired when a clip has been opened by the control.
 */
void OnRealAudioOnClipOpened(voleControlSite *site, vstr *shortClipName, vstr *url);

/*
 * Fired to indicate that no clip is currently open by the control.
 */
void OnRealAudioOnClipClosed(voleControlSite *site);

/*
 * Fired to indicate that the controls status text is changing.
 */
void OnRealAudioOnShowStatus(voleControlSite *site, vstr *statusText);

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
void RealAudioNotifyEvent(voleControlSite *site, int dispid, volevariantList *list);


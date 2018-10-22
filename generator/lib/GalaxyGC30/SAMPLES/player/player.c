/* $Id: player.c,v 1.2 1997/10/16 19:17:21 gary Exp $ */
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
 * copyright notice in the in the form of "Copyright 1997 Visix Software Inc.,
 * 11440 Commerce Park Drive, Reston, VA  20191. All Rights Reserved"
 * appears in all copies, (ii) both the copyright notice and this permission
 * notice appear in supporting documentation and (iii) you are a valid
 * licensee of Galaxy Application Environment.
 */

/****************************************************************************
 * executable:    player
 * source files:  player.c
 *                activemovie.c
 *                realaudio.c
 * 
 * header files:  activemovie.h
 *                realaudio.h
 * 
 * resource file: player.vr
 *
 * classes illustrated:  volesite
 *                       volevariant
 *
 *
 * This program illustrates how use ActiveX (OLE) controls in Galaxy.
 * The sample uses ActiveMovie and RealAudio controls, so you need them installed
 * on your machine. These controls are freely avaiable.
 * See http:// www.microsoft.com for ActiveMovie
 * and  http://www.realaudio.com for RealAudio/RealVideo,
 * 
 * To use the sample select the current player from menu, type some source
 * (file or URL) in the text item, press the "Set" button to set the source
 * and press the "Play" button.
 *
 * To end the demo, choose "Quit" from the File menu.
 *
 ****************************************************************************/

#include <vport.h>             

#ifndef  vstdlibINCLUDED
#include vstdlibHEADER
#endif

#ifndef  vdictINCLUDED
#include vdictHEADER
#endif

#ifndef  veventINCLUDED
#include veventHEADER
#endif

#ifndef  vapplicationINCLUDED
#include vapplicationHEADER
#endif

#ifndef  vcommandINCLUDED
#include vcommandHEADER
#endif

#ifndef  vnameINCLUDED
#include vnameHEADER
#endif

#ifndef  vresourceINCLUDED
#include vresourceHEADER
#endif

#ifndef  vdialogINCLUDED
#include vdialogHEADER
#endif

#ifndef  vmenubarINCLUDED
#include vmenubarHEADER
#endif

#ifndef  vtextitemINCLUDED
#include vtextitemHEADER
#endif

#ifndef  vbuttonINCLUDED
#include vbuttonHEADER
#endif

#ifndef  vstartupINCLUDED
#include vstartupHEADER
#endif

#ifndef  volesiteINCLUDED
#include volesiteHEADER
#endif

#include "activemovie.h"
#include "realaudio.h"

/*****************************************************************************
 * declarations
 *****************************************************************************/

static void SetActivePlayer(int player); 

int     activePlayer;
vbool   sourceSet;

voleControlSite *activeMovie;
voleControlSite *realAudio;

/*
 * Integer selectors for each of our commands. These selectors are used
 * to differentiate the commands coming into our IssueCommand() function.
 */
enum {
    ACTIVE_MOVIE,    
    REAL_AUDIO, 
    DISPLAY,    
    CONTROLS,
    PLAY,
    PAUSE,
    STOP,
    SET_SOURCE,
    PROPERTIES,
    GOTO_S1,
    GOTO_S2,
    ABOUT_CONTROL,
    QUIT };

/*
 * The tags for each of our commands. These are the tags assigned to each
 * corresponding menu item in vre. These tags are associated with command
 * objects in the command dictionary in our application command space set
 * up in main().
 */
static vcommandSelectorTemplate playerCommands[] =
{
    {"ActiveMovie",  ACTIVE_MOVIE},
    {"RealAudio",    REAL_AUDIO},
    {"ViewDisplay",  DISPLAY},
    {"ViewControls", CONTROLS},
    {"Play",         PLAY},
    {"Pause",        PAUSE},
    {"Stop",         STOP},
    {"SetSource",    SET_SOURCE},
    {"Properties",   PROPERTIES},
    {"GoTo1",        GOTO_S1},
    {"GoTo2",        GOTO_S2},
    {"AboutControl", ABOUT_CONTROL},
    {"Quit",         QUIT}
};


static int IssueCommand(vcommandSelector *command, vdict *attr2value)
{
    vdialog   *dialog; 
    vtextitem *textItem;
    vstr      *source;

    voleControlSite *actMovie = activeMovie;
    voleControlSite *rAudio   = realAudio;

    dialog = (vdialog *)vdictLoad(attr2value, vname_Dialog);
    textItem = (vtextitem *)vdialogFindItem(dialog, 
                            vnameInternGlobalLiteral("SourceItem"));

    switch (vcommandGetSelector(command))
    {

    case SET_SOURCE:
        {   
            source = vtextitemGetTextAsString(textItem);         

            if (activePlayer == ACTIVE_MOVIE)
            {
               ActiveMovieSetFileName(actMovie, source);    
               sourceSet = TRUE; 
            }
            else
            {
                RealAudioSetSource(rAudio, source);            
            }
           
            vstrDestroy(source);
            break;
        }

    case PLAY:
           
         vexWITH_HANDLING
         {
             if (activePlayer == ACTIVE_MOVIE && sourceSet)
                 ActiveMovieRun(actMovie);
             else if (RealAudioCanPlayPause(rAudio))
                 RealAudioDoPlayPause(rAudio);
         }
         vexON_EXCEPTION
         {
         }
         vexEND_HANDLING
         break;
        

    case STOP:
        
         vexWITH_HANDLING
         {
             if (activePlayer == ACTIVE_MOVIE)
                 ActiveMovieStop(actMovie);
             else if (RealAudioCanStop(rAudio))
                 RealAudioDoStop(rAudio);
         }
         vexON_EXCEPTION
         {
         }
         vexEND_HANDLING

    
         break;
   
    case PAUSE:

         vexWITH_HANDLING
         {
             if (activePlayer == ACTIVE_MOVIE)
                 ActiveMoviePause(actMovie);
             else if (RealAudioCanPlayPause(rAudio))
                RealAudioDoPlayPause(rAudio);          
         }
         vexON_EXCEPTION
         {
         }
         vexEND_HANDLING

         break;

    case ABOUT_CONTROL:

         if (activePlayer == ACTIVE_MOVIE)
             ActiveMovieAboutBox(actMovie);
         else
             ActiveMovieAboutBox(rAudio);

         break;

    case PROPERTIES:
         /* OLEIVERB_PROPERTIES is -7 */
         if (activePlayer == ACTIVE_MOVIE)
             voleDoControlSiteVerb(actMovie, -7, NULL);
         else
             voleDoControlSiteVerb(rAudio, -7, NULL);
         
         break;

    case CONTROLS:
         if (ActiveMovieGetShowControls(actMovie))        
             ActiveMovieSetShowControls(actMovie, FALSE);
         else
             ActiveMovieSetShowControls(actMovie, TRUE);

         break;

    case DISPLAY:
         if (ActiveMovieGetShowDisplay(actMovie))        
             ActiveMovieSetShowDisplay(actMovie, FALSE);
         else
             ActiveMovieSetShowDisplay(actMovie, TRUE);

        if (RealAudioGetNoLabels(rAudio))
            RealAudioSetNoLabels(rAudio, FALSE);
        else
            RealAudioSetNoLabels(rAudio, TRUE);
         
         break;

    case ACTIVE_MOVIE:
         SetActivePlayer(ACTIVE_MOVIE);        
         break;

    case REAL_AUDIO:
         SetActivePlayer(REAL_AUDIO);        
         break;

         
    case GOTO_S1:
        {
            
            SetActivePlayer(REAL_AUDIO);
            source = vstrCloneScribed(vcharScribeLiteral(
                  "http://www.foxnews.com/newsnow/video/fnc20.rmm"));
            RealAudioSetSource(rAudio, source);
            sourceSet = TRUE;
            RealAudioDoPlayPause(rAudio);
            vstrDestroy(source);
            break;
        }

    case QUIT:
	veventStopProcessing();
	break;
	
    default:
	return vclassSendSuper(vcommandGetDefaultSelectorClass(), vcommandISSUE,
			          (command, attr2value));
    }
    
    return TRUE;
}


static void NotifyDialog(vdialog *dialog, vevent *event)
{
    if (veventIsClose(event))
	veventStopProcessing();
}

static void SetActivePlayer(int player)
{
    if (player == ACTIVE_MOVIE)
    {
        vdialogShowItem(voleGetControlSiteItem(activeMovie));
        vdialogHideItem(voleGetControlSiteItem(realAudio));        
    }
    else
    {
        vdialogShowItem(voleGetControlSiteItem(realAudio));
        vdialogHideItem(voleGetControlSiteItem(activeMovie));     
    }

    activePlayer = player;
}

/*****************************************************************************
 * main
 *****************************************************************************/
int main(int argc, char *argv[])
{
    vapplication           *application;
    vcommandSpace          *space;
    vcommandSelectorClass  *clas;  
    vdict                  *dict;
    vresource               resource;  
    vdialog                *dialog;
    
    vstartup(argc, argv);
    
    clas = vclassReproduce(vcommandGetDefaultSelectorClass());
    vclassSet(clas, vcommandISSUE, IssueCommand);


    /* Create our individual Selector commands, set their numerical
     * selector values, and map them to string tags by Storing 
     * each <tag, command> pair in the dict dictionary.
     */
    dict = vcommandCreateDictOfClassSelectorTemplates(clas, playerCommands,
       sizeof(playerCommands)/sizeof(vcommandSelectorInitializer));
    
    /* Create a command space and store it in our application. */
    space = vcommandCreateSpace();
    vcommandAddSpaceDictOwned(space, vname_Command, dict);

    application = vapplicationGetCurrent();
    vapplicationSetSpaceOwned(application, space);

    /* load our dialog from our resource file. */
    resource = vresourceGet(vapplicationGetResources(application), 
				      vnameInternGlobalLiteral("Dialog"));

    dialog = vdialogLoad(resource);
    vdialogSetNotify(dialog, NotifyDialog);

    activeMovie = (voleControlSite *)vdialogFindItem(dialog, vnameInternGlobalLiteral("site"));
    realAudio  = (voleControlSite *)vdialogFindItem(dialog, vnameInternGlobalLiteral("site1"));
    sourceSet = FALSE;
    SetActivePlayer(ACTIVE_MOVIE);

    vdialogPlace(dialog, vwindowGetRoot(), vrectPLACE_CENTER, vrectPLACE_CENTER);
    vdialogOpen(dialog);
   
    veventProcess();
    
    vdialogDestroy(dialog);
    
    exit(EXIT_SUCCESS);
    return EXIT_FAILURE;
}


/* $Id: offsamp.c,v 1.1 1997/10/24 19:33:05 bill Exp $
 *
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
 * copyright notice in the in the form of "Copyright 1992,93 Visix Software
 * Inc., 11440 Commerce Park Drive, Reston, VA  22091. All Rights Reserved"
 * appears in all copies, (ii) both the copyright notice and this permission
 * notice appear in supporting documentation and (iii) you are a valid
 * licensee of Galaxy Application Environment.
 */

  /*  /////////////////////////////////////////////////////////////
 //                About the sample                             //
/////////////////////////////////////////////////////////////  */

/* 
 * Author:  Bill Baxter
 * Date: September 1997
 * For: Galaxy 3.0 initial release
 * Demonstrates:
 *    Offscreen drawing of a dialog to prevent heinous flicker.
 * Comments:
 *   This file is the sample program which uses the OffscreeDialog class.
 *   On all windowing systems besides Microsoft Windows, the class is
 *   just a duplicate of the vdialog class with a different name.
 *
 * Warning:
 *   The technique demonstrated in this sample is not supported and may
 *   cease to function with releases of Galaxy after 3.0.
 */


#ifndef vportINCLUDED
#include <vport.h>
#endif 

#ifndef vstdlibINCLUDED
#include vstdlibHEADER
#endif 

#ifndef vstartupINCLUDED
#include vstartupHEADER
#endif 

#ifndef vdialogINCLUDED
#include vdialogHEADER
#endif

#ifndef vapplicationINCLUDED
#include vapplicationHEADER
#endif

#ifndef vnoticeINCLUDED
#include vnoticeHEADER
#endif

#include "offscreen.h"

static void dialogNotify(vdialog *dialog, vevent *event)
{
    if (veventIsClose(event))
    {
        veventStopProcessing();
    }
}

#ifndef OffscreenDialogUSE_OFFSCREEN

static void checkWinSystemAndWarn(void)
{
    vnotice *notice;
    notice = vnoticeCreate();
    vnoticeSetTitleScribed(notice, vcharScribeLiteral("Warning"));
    vnoticeSetTextScribed(
        notice,
        vcharScribeLiteral(
            "Offscreen drawing is not enabled on this windowing system so "
            "this sample will just appear as two identical dialogs! "
            "Currently the OfscreenDialog class is a no-op on all platforms "
            "except for Microsoft Windows."
            ));
    vnoticeSetCancel(notice, FALSE);
    vnoticeSetHelp(notice, FALSE);
    (void)vnoticeProcess(notice);
}

#endif /* OffscreenDialogUSE_OFFSCREEN */

  /*  /////////////////////////////////////////////////////////////
 //                The Big Wazoo                                //
/////////////////////////////////////////////////////////////  */

int main(int argc, char * argv[])
{
    OffscreenDialog *off;
    vdialog *dlg;
    vrect rect;

    vstartup(argc, argv);
    
    OffscreenDialogStartup();
    
#ifndef OffscreenDialogUSE_OFFSCREEN
    checkWinSystemAndWarn();
#endif

    off =
        OffscreenDialogLoad(
            vresourceGet(vapplicationGetResources(vapplicationGetCurrent()),
                         vname_Dialog));
    dlg =
        vdialogLoad(
            vresourceGet(vapplicationGetResources(vapplicationGetCurrent()),
                         vname_Document));

    rect = *vwindowGetRect(vwindowGetRoot());
    rect.x = rect.w/2;
    rect.y = rect.h/2;
    rect.w = rect.h = 0;
    vwindowPlaceRect(vdialogGetWindow(dlg), &rect, 
                     vrectPLACE_CENTER,
                     vrectPLACE_TOP);
    vwindowPlaceRect(OffscreenDialogGetWindow(off), &rect, 
                     vrectPLACE_CENTER,
                     vrectPLACE_BOTTOM);

    vdialogSetNotify(dlg, dialogNotify);
    OffscreenDialogSetNotify(off, dialogNotify);

    OffscreenDialogOpen(off);
    vdialogOpen(dlg);

    veventProcess();

    OffscreenDialogDestroy(off);
    vdialogDestroy(dlg);

    exit(EXIT_SUCCESS);
    return EXIT_FAILURE;
    
}


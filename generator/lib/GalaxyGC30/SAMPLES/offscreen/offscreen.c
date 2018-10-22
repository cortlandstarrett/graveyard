/* $Id: offscreen.c,v 1.2 1997/10/25 01:12:23 bill Exp $
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
 * Date: October 1997
 * For: Galaxy 3.0 initial release
 *
 * Demonstrates:
 *   How to use offscreen drawing to make window resizing less flickery
 *   on platforms with "Full Drag".
 *
 * Comments:
 *   This file is the implementation of the OffscreeDialog class.  
 *   On all windowing systems besides Microsoft Windows, the class is 
 *   a complete no-op with all calls reducing to plain vdialog calls.
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

#ifndef vmutexINCLUDED
#include vmutexHEADER
#endif

#if (vportWIN_MS_WINDOWS)
#include vmswhdrsHEADER
#endif

#include "offscreen.h"

  /*  /////////////////////////////////////////////////////////////
 //                Unsupported Prototype                        //
/////////////////////////////////////////////////////////////  */

/* The following function is an undocumented call which
 * clears out the window's internal list of rectangles that
 * need invalidation.  Without this, the dialog would do a 
 * complete repaint the first time it is clicked on after resizing 
 * the window.
 */

extern void _vwindowClearInval(vwindow *window);


  /*  /////////////////////////////////////////////////////////////
 //                Private Exernal Variables                    //
/////////////////////////////////////////////////////////////  */

vmutex _offscreenDialogMutex = vmutexNULL;


  /*  /////////////////////////////////////////////////////////////
 //                Global Types                                 //
/////////////////////////////////////////////////////////////  */

typedef struct offscreenDialogGlobals
{
    OffscreenDialogClass  *offscreenDialogClass;
} offscreenDialogGlobals;

  /*  /////////////////////////////////////////////////////////////
 //                Global Data                                  //
/////////////////////////////////////////////////////////////  */

static offscreenDialogGlobals glob;
static vbool offscreenDialogStarted = vFALSE;

  /*  /////////////////////////////////////////////////////////////
 //                Subclass method implementation               //
/////////////////////////////////////////////////////////////  */

#ifdef OffscreenDialogUSE_OFFSCREEN

static void offscreenDialogInit(OffscreenDialog *dialog)
{
    vclassSendSuper(glob.offscreenDialogClass, vinstanceINIT, (dialog));
    dialog->resized = FALSE;
}

static void offscreenDialogLoadInit(OffscreenDialog *dialog, vresource res)
{
    vclassSendSuper(glob.offscreenDialogClass, vloadableLOAD_INIT,
                    (dialog, res));
    dialog->resized = FALSE;
}

static void offscreenDialogCopyInit(OffscreenDialog *dialog, 
                                    OffscreenDialog *target)
{
    vclassSendSuper(glob.offscreenDialogClass, vloadableCOPY_INIT,
                    (dialog, target));
    target->resized = FALSE;
}

static void offscreenDialogCopy(OffscreenDialog *dialog, 
                                    OffscreenDialog *target)
{
    vclassSendSuper(glob.offscreenDialogClass, vloadableCOPY,
                    (dialog, target));
    target->resized = FALSE;
}


/* offscreenDialogHandleConfigure
 *    This method is called when a dialog moves, is resized and perhaps
 *    a few other situations.  We just want to know when it is resized,
 *    and mark the dialog as having been resized so that we know to 
 *    do an offscreen update in the HandleUpdate method.
 */
static int offscreenDialogHandleConfigure(OffscreenDialog *dialog, 
                                          vevent *event) 
{
    vrect oldRect;
    int   w, h;

    dialog->resized = FALSE;

    oldRect  = *vwindowGetRect(OffscreenDialogGetWindow(dialog));

    w = veventGetConfigureWidth(event);
    h = veventGetConfigureHeight(event);

    if (w != oldRect.w || h != oldRect.h)
    {
        dialog->resized = TRUE;
    }
    
    return vclassSendSuper(glob.offscreenDialogClass, vwindowHANDLE_CONFIGURE,
                           (dialog, event));
}



/*
 * offscreenDialogHandleUpdate
 *    Here we repaint the dialog.  We rely on vdialog's implementation of
 *    HandleUpdate unless the dialog's resize flag has been set, in which
 *    case we perform an offscreen update.
 */
static int offscreenDialogHandleUpdate(OffscreenDialog *dialog, vevent *event)
{
    /* the resized flag tells us if the size of the dialog has changed */
    if (dialog->resized)
    {
        vdrawcontext *oldcontext, *context;
        vrect rect, eraserect;
        vdrawpen *oldpen, *pen;
        vwindow *window = OffscreenDialogGetWindow(dialog);
        vcolor *color;
        vimage *image;

        /* Create an offscreen buffer the size of the desktop if it has
         * not been created yet.  Since this is a shared resource, we lock
         * it using the offscreen dialog's mutex.
         */
        OffscreenDialogLock();
        if (NULL == 
            (image = vclassGet(OffscreenDialogGetClass(dialog),
                               OffscreenDialogIMAGE)))
        {
            const vrect *root = vwindowGetRect(vwindowGetRoot());
            image = vwindowCreateBufferImage(root->w, root->h);
            vclassSet(OffscreenDialogGetClass(dialog), 
                      OffscreenDialogIMAGE, image);
        }

        /* Clear out the list of invalid rects to update,
         * since we'll be updating 'em all
         */
        _vwindowClearInval(window);
        vwindowUpdateDevice(window);

        rect = *vwindowGetRect(window);

        oldcontext = _vdrawcontextCreateFromCurrentGState();
        oldpen = vdrawcontextGetPen(oldcontext);

        /* Create drawing context for image drawing */
        context = vdrawCreateImageDrawcontext(image);

        /* Setup pen */
        pen = vdrawcontextGetPen(context);
        vdrawpenCopy(oldpen, pen);
        vdrawcontextDestroy(oldcontext);
        
        /* Erase Background */
        color = vdrawpenGetColor(pen);
        vdrawpenSetColor(pen, vdrawpenGetComplementColor(pen));
        eraserect = rect;
        eraserect.x = eraserect.y = 0;
        vdrawcontextFillRectangles(context, &eraserect, 1);
        vdrawpenSetColor(pen, color);

        /* Draw the window on the buffer image */
        vdrawcontextSetCurrentPoint(context, (double)rect.x, (double)rect.y);
        vwindowDrawWith(window, context);
        vdrawcontextDestroy(context);

        /* Draw the image of the window onto the window */
        context = vwindowCreateDrawcontext(window);
        vwindowUpdateDevice(window);
        vdrawcontextSetCurrentPoint(context, (double)0.0, (double)0.0);
        vdrawcontextDrawImageTiled(context, image, &eraserect, &eraserect);
        vdrawcontextDestroy(context);

        /* We're done with the shared image now */
        OffscreenDialogUnlock();

        vdrawNullDevice(); 

        dialog->resized = FALSE;
        return TRUE;
    }
    else 
        return vclassSendSuper(glob.offscreenDialogClass, vwindowHANDLE_UPDATE,
                               (dialog, event));
}

#endif /*  OffscreenDialogUSE_OFFSCREEN */


  /*  /////////////////////////////////////////////////////////////
 //                Setup and cleanup                            //
/////////////////////////////////////////////////////////////  */


/* 
 * OffscreenDialogCleanup
 *    cleans up left over messes
 */
static void _offscreenDialogShutdown(void)
{
#ifdef OffscreenDialogUSE_OFFSCREEN
    vimage *image = vclassGet(glob.offscreenDialogClass, OffscreenDialogIMAGE);
    if (image != NULL)
        vimageDestroy(image);
#endif

    vmutexDestroy(&_offscreenDialogMutex);
}


/* 
 * OffscreenDialogStartup
 *    makes sure everything is initialized
 */
void OffscreenDialogStartup(void)
{
    if (!offscreenDialogStarted)
        (void)OffscreenDialogGetDefaultClass();
}


/*
 * OffscreenDialogGetDefaultClass
 *   Returns the default Offscreen Dialog Class,
 *   initializing it if necessary first.
 */
OffscreenDialogClass *OffscreenDialogGetDefaultClass()
{
    OffscreenDialogClass   *clas;

    if (!offscreenDialogStarted) {
        vmutexLockGlobalWithHandling();
        if (!offscreenDialogStarted) {

            if (_offscreenDialogMutex == vmutexNULL) {
                vexStartup();
                vmutexInit(&_offscreenDialogMutex);
                vmutexSetName(&_offscreenDialogMutex, "_offscreenDialogMutex");
            }

            vclientRegisterShutdown(_offscreenDialogShutdown);

#ifdef OffscreenDialogUSE_OFFSCREEN

            clas = (OffscreenDialogClass*)vclassSpawn(
                vdialogGetDefaultClass(),
                sizeof(OffscreenDialogClass));
            vclassSetNameScribed(clas, vcharScribeLiteral("OffscreenDialog"));
            vclassSetObjectSize(clas, sizeof(OffscreenDialog));

            /* Setup method overrides */
            vclassSet(clas, vinstanceINIT, offscreenDialogInit);
            vclassSet(clas, vloadableLOAD_INIT, offscreenDialogLoadInit);
            vclassSet(clas, vwindowHANDLE_UPDATE, offscreenDialogHandleUpdate);
            vclassSet(clas, vwindowHANDLE_CONFIGURE, 
                      offscreenDialogHandleConfigure);
            vclassSet(clas, OffscreenDialogIMAGE, NULL);

#else /* OffscreenDialogUSE_OFFSCREEN */

            clas = (OffscreenDialogClass*)
                vclassReproduce(vdialogGetDefaultClass());
            vclassSetNameScribed(clas, vcharScribeLiteral("OffscreenDialog"));

#endif /* OffscreenDialogUSE_OFFSCREEN */

            glob.offscreenDialogClass = clas;
            offscreenDialogStarted = TRUE;
        }
        vmutexUnlockGlobalWithHandling();
    }
    return clas;
}





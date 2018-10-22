/* $Id: identify.c,v 1.2 1996/10/03 22:26:06 chad Exp $ */
/*----------------------------------------------------------------------------
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
 * copyright notice in the form of "Copyright 1992 Visix Software Inc.,
 * 11440 Commerce Park Drive, Reston, VA  22091. All Rights Reserved" appears
 * in all copies, (ii) both the copyright notice and this permission notice
 * appear in supporting documentation and (iii) you are a valid licensee of
 * Galaxy Application Environment.
 ---------------------------------------------------------------------------*/


/****************************************************************************
 * executable:    identify
 * .c files:      identify.c
 * resource file: identify.vr
 *
 *
 * Managers Illustrated: Dialog Manager
 *                       Timer Manager
 * 
 * Description Of Sample:
 * Mouse tracking and identifying dialog items.
 *
 * The purpose of this sample is to show how to track mouse pointer
 * movements using the timer manager.  It also shows how one might
 * identify items in a dialog as the mouse pointer passes over them.
 *
 * History: Written for 2.0 release, 6/1/94
 ****************************************************************************/


#include <vport.h>

#include vstdlibHEADER
#include vstdioHEADER
#include vapplicationHEADER
#include vstartupHEADER
#include vresourceHEADER
#include vdialogHEADER
#include vbuttonHEADER
#include vcontainerHEADER
#include vnotebookHEADER
#include vcomboboxHEADER
#include vcomboHEADER
#include vimageHEADER
#include vmenubarHEADER
#include vmenuHEADER


/* forward references
*/
static void     timerCallback(vtimer *pTimer);
static void     winClosed(vdialog *dialog, vevent *event);
static void     quitPushed(vmenuItem *item, vevent *event);
static int      ContainsPoint(vdialog *dialog, int x, int y);
static vbool    handleContainer(vcontainer *container, int x, int y);


/* static globals
 */
static vdialog          *theDialog;
static vdialogItem      *idlabel;

#define TAG(t) vnameInternGlobalLiteral(t)
#define SCRIBE(t) vcharScribeLiteral(t)


/*********
 * main()
 *
 * The main function
 *
 **********/
int main(int argc, char *argv[])
{
    unsigned long secs = 0;
    unsigned long nanosecs = 250000000;
    vresource   rootRes;
    vresource   dialogRes;
    vmenubar    *menubar;
    vmenu       *menu;
    vmenuItem   *mItem;
    vtimer      *pTimer;

    /* Initialize Galaxy, since "vgalaxy.h" is included, all managers will
     * be started
     */
    vstartup(argc, argv);


    /* Get the current application object and root resource
     */
    rootRes = vapplicationGetResources(vapplicationGetCurrent());


    /* Get the dialog, tagged "Dialog", resource
      */
    dialogRes = vresourceGet(rootRes, TAG("Dialog"));


    /* Load the dialog
     */
    theDialog = vdialogLoad(dialogRes);


    /* Set up callback when window that dialog is living in is closed
     */
    vdialogSetNotify(theDialog, winClosed);


    /* Attempt to find the label item tagged "Idlabel", this label will
     * serve as an echo for the name of the dialog item the mouse pointer
     * is currently over
     */
    idlabel = (vdialogItem *) vdialogFindItem(theDialog, TAG("Idlabel"));


    /* Attempt to find menu Item tagged "Quit" attached to a menu
     * tagged "FileMenu" attached to a menu bar named "Menu Bar".
     * Attach callback function to menu item.
     */
    menubar = (vmenubar *) vdialogFindItem (theDialog, TAG("Menu Bar"));
    if (menubar != NULL)
    {
        menu = vmenubarFindMenu (menubar, TAG("FileMenu"));
        if (menu != NULL)
        {
            mItem = vmenuFindItem (menu, TAG("Quit"));
            vmenuSetItemNotify (mItem, quitPushed);
        }
        
    }


    /* Set up and start the timer
     */

    pTimer = vtimerCreate(); /* initializes also */

    vdialogSetData(theDialog, pTimer);

    vtimerSetRecurrent(pTimer);
    vtimerSetPeriod(pTimer, secs, nanosecs);
    vtimerSetCallback(pTimer, timerCallback);
    vtimerStart(pTimer);


    /* Open the Dialog
     */
    vdialogOpen(theDialog);


    /* Enter event loop
     */
    veventProcess();


    /* Cleanup
     */
    vtimerDestroy(pTimer);
    vdialogDestroy(theDialog);
    theDialog = NULL;

    exit(EXIT_SUCCESS);
    return EXIT_FAILURE;
}


/*********
 * timerCallback(vtimer *pTimer)
 *
 * When the timer goes off, this routine is called
 *
 **********/
static void timerCallback(vtimer *pTimer)
{
    const vname *name=NULL;

    static int          oldx = 0;
    static int          oldy = 0;
    static int          previtem = -1;

    int                 curx, cury;
    int                 item, cnt;
    vdialogItem         *ditem;


    /* make sure idlabel was found in the dialog
     */
    if (idlabel == NULL)
        return;


    /* get current pointer position with respect to the dialog
     */
    vwindowGetPointer(vdialogGetWindow(theDialog), &curx, &cury);


    /* if pointer has not moved, leave
     */
    if ((curx != oldx) || (cury != oldy))
    {
        /* update the pointer trackers
         */
        oldx = curx;
        oldy = cury;
    }
    else
        return;


    /* if pointer is not contained in the dialog, leave
     */
    if (!ContainsPoint(theDialog, curx, cury))
        return;



    /* for each dialog item in the dialog ...
     */
    cnt = vdialogGetItemCount(theDialog);

    for (item=0; item<cnt; item++)
    {
        ditem = vdialogGetItemAt(theDialog, item);

        /* check if pointer is over "ditem"
         */
        if (vdialogItemContainsPoint(ditem, curx, cury))
        {
            /* check if dialog item is a container
             */
            if (vclassIsKindOf(vdialogGetItemClass(ditem),
                                vcontainerGetDefaultClass()))
            {
                /* look inside of container
                 */
                if (handleContainer((vcontainer *) ditem, curx, cury) == vTRUE)
                    return;
                else
                {
                    break;
                }
            }
            else
            {
                /* don't set the idlabel again if positioned on same item
                 */
                if (item != previtem)
                {
                    previtem = item;

                    name = vdialogGetItemTag(ditem);
                    if (name == NULL)
                    {
                        break;
                    }
                    else
                    {
                        vdialogSetItemTitleScribed(idlabel,
                                                   vnameScribeGlobal(name));
                        return;
                    }
                }
            }
        }
    }


    /* if program control gets to this point, the pointer is 
     * not positioned over any item, set message to window, if you can
     */
    name = vwindowGetTag(vdialogGetWindow(theDialog));
    if (name == NULL)
        vdialogSetItemTitleScribed(idlabel,
                                   vnameScribeGlobal(name));
    else
        vdialogSetItemTitleScribed(idlabel, SCRIBE(" "));

    previtem = -1;

    return;
}



/********
 * following function checks if point (x,y) is in dialog
 * returns:
 *      TRUE if in dialog
 *      FALSE if not in dialog
 *********/
static int ContainsPoint(vdialog *dialog, int x, int y)
{

    if ( (x >= 0) && (x <= vwindowGetW(vdialogGetWindow(dialog)))  &&
         (y >= 0) && (y <= vwindowGetH(vdialogGetWindow(dialog))) )
        return TRUE;
    else
        return FALSE;
}




/********
 * following function is called when mouse is found to be over a container
 *********/
static vbool handleContainer(vcontainer *container, int curx, int cury)
{
    const vname *name = NULL;
    static vdialogItem  *olditem = NULL;

    int                 item;
    int                 containerx, containery;
    vdialogItem         *ditem;
    vrect               rect;
    int                 count;


    /* transform pointer position to its position with respect to
     * the container (all items in container are positioned this way)
     */
    rect = *vcontainerGetBounds(container);
    containerx = curx - rect.x;
    containery = cury - rect.y;

    /* get the count of things in the container
     */
    count = vcontainerGetItemCount(container);



    /* notebooks are a special case container

       The notebook tabs are contained in a container that has odd 
       characteristics.

       NOTE: the following (1-3) may not be this way in the future!!

       The dialog item that contains them (you
       get this from vnotebookGetMajorTabSet) is:
           1.  a container, you are not supposed to know that, and this
               might change in the future
           2.  is not part of the notebook's dialog item list
           3.  it's coordinates are NOT with respect to the notebook, but
               whatever contains the notebook
    */

    if (vclassIsKindOf(vdialogGetItemClass(vcontainerGetItem(container)),
                       vnotebookGetDefaultClass()))
    {
        /* If the coordinates (curx, cury) are within the major tab set 
           container, just call handle container on that.  Else, just let 
           it fall through so that it can attempt to find pages or possibly
           report the notebook tag.
        */

        ditem = vnotebookGetMajorTabSet((vnotebook *) container);

        if (vdialogItemContainsPoint(ditem, curx, cury))
        {
            if (handleContainer((vcontainer *) ditem, curx, cury) == vTRUE)
                return vTRUE;
            else
                count = 0;
        }
    }


    /* for each item in container...
     */
    for (item=0; item<count; item++)
    {
        ditem = vcontainerGetItemAt(container, item);

        /* check if pointer is over "ditem"
         */
        if (vdialogItemContainsPoint(ditem, containerx, containery))
        {
            /* check if dialog item is a container
             */
            if (vclassIsKindOf(vdialogGetItemClass(ditem),
                               vcontainerGetDefaultClass()))
            {
                /* look inside of container, send coordinates with respect
                 * to the current container
                 */
                if (handleContainer((vcontainer *) ditem, 
                                    containerx, containery) == vTRUE)
                    return vTRUE;
                else
                {
                    break;
                }
            }
            else
            {
                name = vdialogGetItemTag(ditem);
                if (name != NULL)
                {
                    /* don't set the idlabel again if positioned on same item
                     */
                    if (ditem != olditem)
                    {
                        olditem = ditem;
                        
                        vdialogSetItemTitleScribed(idlabel,
                                                   vnameScribeGlobal(name));
                    }
                    return vTRUE;
                }
                else
                {
                    break;
                }
            }
        }
    }


    /* if program control gets to this point, the pointer is not positioned 
     * over any item, or the item it was over, it's tag was NULL, set idlabel 
     * to tag of the container itself if it is not NULL
     */

    olditem = NULL;

    name = vdialogGetItemTag(vcontainerGetItem(container));
    if (name == NULL)
    {
        return vFALSE;
    }
    else
    {
        vdialogSetItemTitleScribed(idlabel, vnameScribeGlobal(name));
        return vTRUE;
    }
}



/* following function handles close window event
 */
static void winClosed(vdialog *dialog, vevent *event)
{
    vtimer *pTimer = (vtimer *)vdialogGetData(dialog);

    /* Check if this is a close window event, if so, exit event loop
     */
    if (veventGetType(event) == veventWINDOW_STATE && veventIsClose(event))
    {
        vtimerStop(pTimer);

        veventStopProcessing();
    }
}


/* following function handles quit button pushed event
 */
static void quitPushed(vmenuItem *mitem, vevent *event)
{
    veventStopProcessing();
}


/*
 * Local Variables:
 * c-argdecl-indent:4
 * c-brace-imaginary-offset:0
 * c-brace-offset:-4
 * c-continued-brace-offset:0
 * c-continued-statement-offset:4
 * c-extra-brace-offset:0
 * c-file-offsets:((block-open . -))
 * c-file-style:"BSD"
 * c-indent-level:4
 * c-label-offset:-4
 * indent-tabs-mode:nil
 * tab-width:4
 * End:
 */


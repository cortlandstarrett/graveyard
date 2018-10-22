/* $Id: toolbar2.c,v 1.2 1997/10/14 19:59:31 bill Exp $
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
 *   - vtoolbar
 *   - vhelpTooltip
 *   - vhelpStatus
 *   - Commands & Attribute propagation
 *   - Fields
 * Comments:
 *
 *   This sample demonstrates the basic usage of a toolbar very much
 *   like the toolbar1 sample.
 *   The only difference between this sample and that one is that
 *   this sample uses a vfield to keep the menu choices in sync with
 *   the exclusive toolbar buttons.  The field on the menu items is set
 *   one time using attribute propagation.  Thereafter the field 
 *   automatically keeps the items in sync.  In the toolbar1 sample 
 *   attribute propagation is necessary every time a command is invoked
 *   to set the states of items.  This sample therefore is a bit more
 *   efficient that the first.
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

#ifndef vtoolbarINCLUDED
#include vtoolbarHEADER
#endif 

#ifndef vdialogINCLUDED
#include vdialogHEADER
#endif

#ifndef vapplicationINCLUDED
#include vapplicationHEADER
#endif

#ifndef vstatusbarINCLUDED
#include vstatusbarHEADER
#endif

#ifndef vhelpINCLUDED
#include vhelpHEADER
#endif

#ifndef vhelpstatusINCLUDED
#include vhelpstatusHEADER
#endif

#ifndef vhelptooltipINCLUDED
#include vhelptooltipHEADER
#endif

#ifndef vtoolbuttonINCLUDED
#include vtoolbuttonHEADER
#endif


  /*  /////////////////////////////////////////////////////////////
 //                Global Types                                 //
/////////////////////////////////////////////////////////////  */

typedef struct toolbarSampleGlobals
{
    vdialogClass  *toolbarDialogClass;
    vcommandSpace  toolbarDialogSpace;
} toolbarSampleGlobals;

  /*  /////////////////////////////////////////////////////////////
 //                Global Data                                  //
/////////////////////////////////////////////////////////////  */

static toolbarSampleGlobals glob;

enum {
    ToolbarDialogSELECT_QUIT = vdialogNEXT_SELECT,
    ToolbarDialogSELECT_SAVE,
    ToolbarDialogSELECT_OPEN,
    ToolbarDialogSELECT_COPY,
    ToolbarDialogSELECT_CUT,
    ToolbarDialogSELECT_BOTTOMS,
    ToolbarDialogSELECT_CENTERS,
    ToolbarDialogSELECT_LEFTS,
    ToolbarDialogSELECT_RIGHTS,
    ToolbarDialogSELECT_TOPS,
    ToolbarDialogSELECT_WRAP,
    ToolbarDialogSELECT_REARRANGEABLE,
    ToolbarDialogNEXT_SELECT
};
    
static const vcommandSelectorTemplate _ToolbarDialogSelectorTemplates[] = {
    { "Quit",		ToolbarDialogSELECT_QUIT	},
    { "Save",		ToolbarDialogSELECT_SAVE	},
    { "Open",		ToolbarDialogSELECT_OPEN	},
    { "Copy",		ToolbarDialogSELECT_COPY	},
    { "Cut",		ToolbarDialogSELECT_CUT		},
    { "AlignBottoms",	ToolbarDialogSELECT_BOTTOMS	},
    { "AlignCenters",	ToolbarDialogSELECT_CENTERS	},
    { "AlignLefts",	ToolbarDialogSELECT_LEFTS	},
    { "AlignRights",	ToolbarDialogSELECT_RIGHTS	},
    { "AlignTops",	ToolbarDialogSELECT_TOPS	},
    { "Wrap",		ToolbarDialogSELECT_WRAP	},
    { "Rearrangeable",	ToolbarDialogSELECT_REARRANGEABLE}
};

static const char *_ToolbarDialogExclusives[] = {
    "AlignBottoms", 
    "AlignTops", 
    "AlignLefts", 
    "AlignRights", 
    "AlignCenters"
};

  /*  /////////////////////////////////////////////////////////////
 //                Subclass method implementation               //
/////////////////////////////////////////////////////////////  */

static void toolbarDialogLoadInit(vdialog *dialog, vresource res)
{
    vobservable *field;
    vdialogItem *button;
    vdict       *changeDict;
    int          i;
    const vname *tag;

    vclassSendSuper(glob.toolbarDialogClass, vloadableLOAD_INIT,
                    (dialog, res));

    /* Turn on motion so status and toolbar help will work */
    vwindowSetMotion(vdialogGetWindow(dialog), TRUE);

    /* Find the field in use for exclusive grouping */
    button = (vdialogItem*)
        vobjectFindChild(vdialogGetObject(dialog), 
                         vnameInternGlobalLiteral("AlignBottoms"),
                         (vobjectClass*)vdialogGetDefaultItemClass());
    field = vdialogGetItemField(button);

    /* Set that field on all that should observe it */
    changeDict = vdictCreate(vnameHash);
    for (i = 0; i < (sizeof(_ToolbarDialogExclusives)/sizeof(char*)); i++)
    {
        tag = vnameInternGlobalLiteral(_ToolbarDialogExclusives[i]);
        vdictStore(changeDict, tag, field);
    }

    /*
     * Attributes offer a powerful way to change the state of objects
     * without concern about their actual class.  
     * This call will set the field on anything that has a field attribute 
     * and whose tag is one of the ones we added to the dict.
     */
    vobjectPropagateChangeDict(vdialogGetObject(dialog), 
                               vname_Field, changeDict);
    vdictDestroy(changeDict);
}


static int toolbarDialogIssueSelector(vdialog *dialog, int selector,
                                      vdict *attr2value)
{
    switch (selector) {
    
    case ToolbarDialogSELECT_BOTTOMS:
    case ToolbarDialogSELECT_CENTERS:
    case ToolbarDialogSELECT_LEFTS:
    case ToolbarDialogSELECT_RIGHTS:
    case ToolbarDialogSELECT_TOPS:
    case ToolbarDialogSELECT_SAVE:
    case ToolbarDialogSELECT_OPEN:
    case ToolbarDialogSELECT_COPY:
    case ToolbarDialogSELECT_CUT:
    {
        vstatusbar  *statusbar;

        /* Change the status indicator */

        statusbar = (vstatusbar *)
            vobjectFindChild(vdialogGetObject(dialog), 
                             vnameInternGlobalLiteral("StatusBar"),
                             (vobjectClass*)vstatusbarGetDefaultClass());

        /* If this were a real application, we would load the string
         * below from a resource file rather than hard-code it.
         */
        vstatusbarSetDefaultItemTextScribed(
            statusbar, 
            vscribeScribeMulti(
                vcharScribeLiteral("Woo woo! You invoked the "),
                vcharScribe((vchar*)vdictLoad(attr2value, vname_Tag)),
                vcharScribeLiteral(" command!"),
                NULL));
        
    }
    return TRUE;
    break;

    case ToolbarDialogSELECT_WRAP:
    case ToolbarDialogSELECT_REARRANGEABLE:
    {
        vdict *changeDict;
        vobject *oper8or;
        const vname *value, *attrname;

        
        oper8or = (vobject*) vdictLoad(attr2value, vname_Operator);
        value = vobjectGetAttribute(oper8or, vname_Toggle);
        changeDict = vdictCreate(vnameHash);

        vdictStore(changeDict, vnameInternGlobalLiteral("Toolbar"),
                   (value == vname_On) ? vname_True : vname_False);

        /* What follows only works because we just happened to give
         * the menu items tags which match the names of the attributes
         * that we want to toggle.
         */
        attrname = (const vname *) vdictLoad(attr2value, vname_Tag);
        vobjectPropagateChangeDict(vdialogGetObject(dialog), 
                                   attrname, changeDict);
        vdictDestroy(changeDict);
    }
    return TRUE;
    break;

    case ToolbarDialogSELECT_QUIT:
        veventStopProcessing();
        return TRUE;

    default:
        return vclassSendSuper(glob.toolbarDialogClass, vobjectISSUE_SELECTOR,
                               (dialog, selector, attr2value));
    }
}


static int toolbarDialogQuerySelector(vdialog *dialog, int selector,
                                      vdict *attr2value)
{
    vtoolbar    *toolbar;
    const vname *attrname, *value;
    

    switch (selector)
    {
    case ToolbarDialogSELECT_WRAP:
    case ToolbarDialogSELECT_REARRANGEABLE:
        
        toolbar = (vtoolbar *)
            vobjectFindChild(vdialogGetObject(dialog), 
                             vnameInternGlobalLiteral("Toolbar"),
                             (vobjectClass*)vtoolbarGetDefaultClass());
        attrname = (const vname*) vdictLoad(attr2value, vname_Tag);
        value = vobjectGetAttribute(vtoolbarGetObject(toolbar), attrname);
        vdictStore(attr2value, vname_Toggle,
                   (value == vname_True) ? vname_On : vname_Off);
        
        return TRUE;
        break;
        

    default:
        return vclassSendSuper(glob.toolbarDialogClass, vobjectQUERY_SELECTOR,
                               (dialog, selector, attr2value));
    }

}

static void toolbarDialogNotify(vdialog *dialog, vevent *event)
{
    if (veventIsClose(event))
    {
        veventStopProcessing();
    }
}


  /*  /////////////////////////////////////////////////////////////
 //                Subclass setup and cleanup                   //
/////////////////////////////////////////////////////////////  */

static void initializeToolbarDialogClass()
{
    vdialogClass   *clas;
    vcommandSpace  *superSpace;

    clas = vclassReproduce(vdialogGetDefaultClass());
    vclassSetNameScribed(clas, vcharScribeLiteral("ToolbarDialog"));
    vclassSetObjectSize(clas, sizeof(vdialog));

    /* Setup method overrides */
    vclassSet(clas, vloadableLOAD_INIT, toolbarDialogLoadInit);
    vclassSet(clas, vobjectISSUE_SELECTOR, toolbarDialogIssueSelector);
    vclassSet(clas, vobjectQUERY_SELECTOR, toolbarDialogQuerySelector);
    vclassSet(clas, vwindowNOTIFY, toolbarDialogNotify);

    /* Setup selector commands */
    superSpace = vclassGet(vdialogGetDefaultClass(), vobjectSPACE);
    vcommandCopyInitSpace(superSpace, &(glob.toolbarDialogSpace));
    vcommandAddSpaceDictOwned(
        &glob.toolbarDialogSpace, 
        vname_Command,
        vcommandCreateDictOfClassSelectorTemplates(
            vobjectGetCommandClass(),
            _ToolbarDialogSelectorTemplates,
            sizeof(_ToolbarDialogSelectorTemplates)/
            sizeof(vcommandSelectorTemplate)));

    vclassSet(clas, vobjectSPACE,  &glob.toolbarDialogSpace);

    glob.toolbarDialogClass = clas;
}


  /*  /////////////////////////////////////////////////////////////
 //                Sample setup and cleanup                     //
/////////////////////////////////////////////////////////////  */


/* 
 * toolbarSampleStartup
 *    makes the dialog subclass
 */
static void toolbarSampleStartup(void)
{
    initializeToolbarDialogClass();
}

/* 
 * toolbarSampleCleanup
 *    cleans up left over messes
 */
static void toolbarSampleCleanup(void)
{
    vcommandDestroySpace(&glob.toolbarDialogSpace);
}


  /*  /////////////////////////////////////////////////////////////
 //                The Big Wazoo                                //
/////////////////////////////////////////////////////////////  */

int main(int argc, char * argv[])
{
    vdialog *dialog;

    vstartup(argc, argv);
    
    vhelpStartupTooltip();
    vhelpStartupStatus();
    toolbarSampleStartup();
    
    dialog =
        vdialogLoad(
            vresourceGet(vapplicationGetResources(vapplicationGetCurrent()),
                         vname_Dialog));
    vdialogOpen(dialog);
    veventProcess();
    vdialogDestroy(dialog);

    toolbarSampleCleanup();

    exit(EXIT_SUCCESS);
    return EXIT_FAILURE;
    
}



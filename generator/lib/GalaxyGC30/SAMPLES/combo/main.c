/* $Id: main.c,v 1.11 1995/07/06 16:25:48 ian Exp $ */

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
 * copyright notice in the form of "Copyright 1994 Visix Software Inc.,
 * 11440 Commerce Park Drive, Reston, VA  22091. All Rights Reserved" appears
 * in all copies, (ii) both the copyright notice and this permission notice
 * appear in supporting documentation and (iii) you are a valid licensee of
 * Galaxy Application Environment.
 */
 
/* 
 * Executable Name: sample[*]
 * Source Files:    sample[*].c, main.c
 * Resource Files:  main.vr
 *
 * Managers Illustrated:
 *      Combobox Manager
 *
 * Description Of Sample:
 *      This code is a part of all samples.  It consists of various 
 *      dialog items that control the attributes of comboboxes imported from
 *      sample[*].c.  The dialog items include:
 *             accept behavior
 *             accept value
 *             background color
 *             border on/off
 *             enable/disable
 *             font setting
 *             foreground color
 *             mix values
 *             modifiable on/off
 *             scroll behavior
 *             scroll value
 *             select behavior
 *             select value
 *             show/hide
 *             sort values
 *             use of copy
 *             use of copyInit
 *             use of load and store
 *             QUIT
 *
 * History:
 *      Written for 2.1 release Decemeber 1994
 */

/*****************************************************************************
 * include files
 ****************************************************************************/

#ifndef vportINCLUDED
#include <vport.h>  /* for v*HEADER */
#endif

#ifndef vbuttonINCLUDED
#include vbuttonHEADER
#endif

#ifndef vclassINCLUDED
#include vclassHEADER
#endif

#ifndef vcolorINCLUDED
#include vcolorHEADER
#endif

#ifndef vcomboboxINCLUDED
#include vcomboboxHEADER
#endif

#ifndef vdialogINCLUDED
#include vdialogHEADER
#endif

#ifndef veventINCLUDED
#include veventHEADER
#endif

#ifndef vfontINCLUDED
#include vfontHEADER
#endif

#ifndef  vinstINCLUDED
#include  vinstHEADER
#endif

#ifndef vstartupINCLUDED
#include vstartupHEADER
#endif

#ifndef vstdlibINCLUDED
#include vstdlibHEADER
#endif

#ifndef vresourceINCLUDED
#include vresourceHEADER
#endif

#ifndef vstdioINCLUDED
#include vstdioHEADER
#endif

/*****************************************************************************
 * data structures
 ****************************************************************************/

typedef struct {
    vdialog               *dialog;
    vcomboboxClass        *comboClass;
    vcomboboxPopdownClass *popdownClass;
    vcombobox             *combo1;
    vcombobox             *combo2;
    vcombobox             *popdown1;
    vcombobox             *popdown2;
    vbutton               *quitButton;
} globals;

/******************************************************************************
 * variables
 *****************************************************************************/

static globals *_master = NULL;

extern vcomboboxClass        *sampleGetComboboxClass(void);
extern vcomboboxPopdownClass *sampleGetPopdownClass(void);
extern void                   sampleSetup(vcombobox *combo);

/*****************************************************************************
 *
 *****************************************************************************/

static void replace(globals *master,
		    vcombobox *newItem,
		    vcombobox *oldItem)
{
    vdialogSetItemListItemAt(vdialogGetItemList(master->dialog),
			     vdialogGetItemIndex(master->dialog, 
						 vcomboboxGetItem(oldItem)),
			     vcomboboxGetItem(newItem));
    vcomboboxDestroy(oldItem);

    vdialogChangedItemAttributeNone(vcomboboxGetItem(newItem), vname_MinSize);

    if (master->combo1 == oldItem)
	master->combo1 = newItem;
    else if (master->combo2 == oldItem)
	master->combo2 = newItem;
    else if (master->popdown1 == oldItem)
	master->popdown1 = newItem;
    else if (master->popdown2 == oldItem)
	master->popdown2 = newItem;
}

static void arrange(globals *master)
{
    vrect rect;

    rect.x = 0;
    rect.y = 0;
    rect.w = vwindowGetW(vdialogGetWindow(master->dialog));
    rect.h = vwindowGetH(vdialogGetWindow(master->dialog));

    vdialogArrange(master->dialog, &rect);
}

static void dialogNotify(vdialog *dialog, vevent *event)
{
    if (veventGetType(event) == veventWINDOW_STATE &&
	veventIsClose(event)) {
	veventStopProcessing();
    }
}

static void buttonAddNotify(vbutton *button, vevent *event)
{
    globals *master;
    vcomboboxValue *value;
    
    master = (globals *)vbuttonGetData(button);
    
    value = vcomboboxCloneValue(vcomboboxGetValue(master->combo1));
    vcomboboxAppendValue(master->combo1, value);
    
    value = vcomboboxCloneValue(vcomboboxGetValue(master->popdown1));
    vcomboboxAppendValue(master->popdown1, value);

    value = vcomboboxCloneValue(vcomboboxGetValue(master->combo2));
    vcomboboxAppendValue(master->combo2, value);
    
    value = vcomboboxCloneValue(vcomboboxGetValue(master->popdown2));
    vcomboboxAppendValue(master->popdown2, value);
}

static void buttonDeleteNotify(vbutton *button, vevent *event)
{
    globals *master;
    vcomboboxValue *value;
    int index;
    
    master = (globals *)vbuttonGetData(button);
    
    index = vcomboboxGetSelectedIndex(master->combo1);
    if (index >= 0)
    {
	value = vcomboboxGetValueAt(master->combo1, index);
	vcomboboxDeleteValueAt(master->combo1, index);
	vcomboboxDestroyValue(value);
    }

    index = vcomboboxGetSelectedIndex(master->popdown1);
    if (index >= 0)
    {
	value = vcomboboxGetValueAt(master->popdown1, index);
	vcomboboxDeleteValueAt(master->popdown1, index);
	vcomboboxDestroyValue(value);
    }

    index = vcomboboxGetSelectedIndex(master->combo2);
    if (index >= 0)
    {
	value = vcomboboxGetValueAt(master->combo2, index);
	vcomboboxDeleteValueAt(master->combo2, index);
	vcomboboxDestroyValue(value);
    }

    index = vcomboboxGetSelectedIndex(master->popdown2);
    if (index >= 0)
    {
	value = vcomboboxGetValueAt(master->popdown2, index);
	vcomboboxDeleteValueAt(master->popdown2, index);
	vcomboboxDestroyValue(value);
    }
}

static void controlDisableNotify(vcontrol *control, vevent *event)
{
    globals *master;
    
    master = (globals *)vcontrolGetData(control);
    
    if (vcontrolGetValue(control))
    {
	vdialogDisableItem(vcomboboxGetItem(master->combo1));
	vdialogDisableItem(vcomboboxGetItem(master->popdown1));
	vdialogDisableItem(vcomboboxGetItem(master->combo2));
	vdialogDisableItem(vcomboboxGetItem(master->popdown2));
    }
    else
    {
	vdialogEnableItem(vcomboboxGetItem(master->combo1));
	vdialogEnableItem(vcomboboxGetItem(master->popdown1));
	vdialogEnableItem(vcomboboxGetItem(master->combo2));
        vdialogEnableItem(vcomboboxGetItem(master->popdown2));
    }
}

static void buttonBackgroundNotify(vbutton *button, vevent *event)
{
    globals *master;
    vcolor     *color;
    vcolorSpec  spec;
    
    master = (globals *)vbuttonGetData(button);

    vcolorInitSpecSpecific(&spec, vcolorGetHLSModel());
    vcolorSetSpecHLS(&spec,
		     rand()<<8%vcolorCOMPONENT_MAX,
		     vcolorCOMPONENT_MAX/3*2,
		     rand()<<8%vcolorCOMPONENT_MAX);
    color = vcolorInternSpec(&spec);
    
    vdialogSetItemBackground(vcomboboxGetItem(master->combo1), color);
    vdialogSetItemBackground(vcomboboxGetItem(master->combo2), color);
    vdialogSetItemBackground(vcomboboxGetItem(master->popdown1), color);
    vdialogSetItemBackground(vcomboboxGetItem(master->popdown2), color);
}

static void buttonCopyInitNotify(vbutton *button, vevent *event)
{
    globals          *master;
    vcombobox        *combo;
    
    master = (globals *)vbuttonGetData(button);

    combo = vcomboboxClone(master->combo1);
    replace(master, combo, master->combo1);

    combo = vcomboboxClone(master->popdown1);
    replace(master, combo, master->popdown1);

    combo = vcomboboxClone(master->combo2);
    replace(master, combo, master->combo2);

    combo = vcomboboxClone(master->popdown2);
    replace(master, combo, master->popdown2);

    arrange(master);
}

static void buttonCopyNotify(vbutton *button, vevent *event)
{
    globals    *master;
    vcombobox  *combo;
    
    master = (globals *)vbuttonGetData(button);

    combo = vcomboboxCreateOfClass
	(vcomboboxGetClass(master->combo1));
    vcomboboxCopy(master->combo1, combo);
    replace(master, combo, master->combo1);

    combo = vcomboboxCreateOfClass
	(vcomboboxGetClass(master->popdown1));
    vcomboboxCopy(master->popdown1, combo);
    replace(master, combo, master->popdown1);

    combo = vcomboboxCreateOfClass
	(vcomboboxGetClass(master->combo2));
    vcomboboxCopy(master->combo2, combo);
    replace(master, combo, master->combo2);

    combo = vcomboboxCreateOfClass
	(vcomboboxGetClass(master->popdown2));
    vcomboboxCopy(master->popdown2, combo);
    replace(master, combo, master->popdown2);

    arrange(master);
}

static void buttonFontNotify(vbutton *button, vevent *event)
{
    globals        *master;
    vcomboboxValue *value;
    vscribe        *scribe;
    
    master = (globals *)vbuttonGetData(button);
    
    value = vcomboboxGetValue(master->combo1);
    scribe = vcharScribe(vcomboboxGetValueTitle(value));
    vdialogSetItemFont(vcomboboxGetItem(master->combo1), 
		       vfontFindScribed(scribe));
    
    value = vcomboboxGetValue(master->popdown1);
    scribe = vcharScribe(vcomboboxGetValueTitle(value));
    vdialogSetItemFont(vcomboboxGetItem(master->popdown1), 
		       vfontFindScribed(scribe));

    value = vcomboboxGetValue(master->combo2);
    scribe = vcharScribe(vcomboboxGetValueTitle(value));
    vdialogSetItemFont(vcomboboxGetItem(master->combo2), 
		       vfontFindScribed(scribe));
    
    value = vcomboboxGetValue(master->popdown2);
    scribe = vcharScribe(vcomboboxGetValueTitle(value));
    vdialogSetItemFont(vcomboboxGetItem(master->popdown2), 
		       vfontFindScribed(scribe));
}

static void buttonForegroundNotify(vbutton *button, vevent *event)
{
    globals *master;
    vcolor     *color;
    vcolorSpec  spec;
    
    master = (globals *)vbuttonGetData(button);

    vcolorInitSpecSpecific(&spec, vcolorGetHLSModel());
    vcolorSetSpecHLS(&spec,
		     rand()<<8%vcolorCOMPONENT_MAX,
		     vcolorCOMPONENT_MAX/3,
		     rand()<<8%vcolorCOMPONENT_MAX);
    color = vcolorInternSpec(&spec);
    
    vdialogSetItemForeground(vcomboboxGetItem(master->combo1), color);
    vdialogSetItemForeground(vcomboboxGetItem(master->combo2), color);
    vdialogSetItemForeground(vcomboboxGetItem(master->popdown1), color);
    vdialogSetItemForeground(vcomboboxGetItem(master->popdown2), color);
}

static void buttonLoadNotify(vbutton *button, vevent *event)
{
    globals *master;
    vcombobox *combo;
    vresource resource;
    
    master = (globals *)vbuttonGetData(button);
    
    resource = vresourceCreateMem();
    vcomboboxStore(master->combo1, resource);
    combo = vcomboboxLoad(resource);
    vresourceDestroyMem(resource);
    vcomboboxSetNotify(combo, vcomboboxGetNotify(master->combo1));
    vcomboboxSetData(combo, vcomboboxGetData(master->combo1));
    replace(master, combo, master->combo1);

    resource = vresourceCreateMem();
    vcomboboxStore(master->popdown1, resource);
    combo = vcomboboxLoad(resource);
    vresourceDestroyMem(resource);
    vcomboboxSetNotify(combo, vcomboboxGetNotify(master->popdown1));
    vcomboboxSetData(combo, vcomboboxGetData(master->popdown1));
    replace(master, combo, master->popdown1);

    resource = vresourceCreateMem();
    vcomboboxStore(master->combo2, resource);
    combo = vcomboboxLoad(resource);
    vresourceDestroyMem(resource);
    vcomboboxSetNotify(combo, vcomboboxGetNotify(master->combo2));
    vcomboboxSetData(combo, vcomboboxGetData(master->combo2));
    replace(master, combo, master->combo2);

    resource = vresourceCreateMem();
    vcomboboxStore(master->popdown2, resource);
    combo = vcomboboxLoad(resource);
    vresourceDestroyMem(resource);
    vcomboboxSetNotify(combo, vcomboboxGetNotify(master->popdown2));
    vcomboboxSetData(combo, vcomboboxGetData(master->popdown2));
    replace(master, combo, master->popdown2);

    arrange(master);
}

static void controlModifyableNotify(vcontrol *control, vevent *event)
{
    globals *master;
    
    master = (globals *)vcontrolGetData(control);
    
    if (vcontrolGetValue(control))
    {
	vcomboboxSetModifyable(master->combo1, TRUE);
	vcomboboxSetModifyable(master->popdown1, TRUE);
	vcomboboxSetModifyable(master->combo2, TRUE);
	vcomboboxSetModifyable(master->popdown2, TRUE);
    }
    else
    {
	vcomboboxSetModifyable(master->combo1, FALSE);
	vcomboboxSetModifyable(master->popdown1, FALSE);
	vcomboboxSetModifyable(master->combo2, FALSE);
	vcomboboxSetModifyable(master->popdown2, FALSE);
    }
}

static void buttonQuitNotify(vbutton *button, vevent *event)
{
    veventStopProcessing();
}

static void buttonSortNotify(vbutton *button, vevent *event)
{
    globals *master;
    
    master = (globals *)vbuttonGetData(button);
    
    vcomboboxSortValues(master->combo1);
    
    vcomboboxSortValues(master->popdown1);

    vcomboboxSortValues(master->combo2);
    
    vcomboboxSortValues(master->popdown2);
}

static void buttonMixNotify(vbutton *button, vevent *event)
{
    globals *master;
    int index;
    
    master = (globals *)vbuttonGetData(button);

    for (index = 1; index < vcomboboxGetValueCount(master->combo1); index++)
	vcomboboxMoveValue(master->combo1, rand()%index, index);

    for (index = 1; index < vcomboboxGetValueCount(master->popdown1); index++)
	vcomboboxMoveValue(master->popdown1, rand()%index, index);

    for (index = 1; index < vcomboboxGetValueCount(master->combo2); index++)
	vcomboboxMoveValue(master->combo2, rand()%index, index);

    for (index = 1; index < vcomboboxGetValueCount(master->popdown2); index++)
	vcomboboxMoveValue(master->popdown2, rand()%index, index);
}

static void controlBorderNotify(vcontrol *control, vevent *event)
{
    globals *master;
    
    master = (globals *)vcontrolGetData(control);
    
    if (vcontrolGetValue(control))
    {
	vdialogSetItemBorder(vcomboboxGetItem(master->combo1), TRUE);
	vdialogSetItemBorder(vcomboboxGetItem(master->popdown1),TRUE);
	vdialogSetItemBorder(vcomboboxGetItem(master->combo2), TRUE);
	vdialogSetItemBorder(vcomboboxGetItem(master->popdown2),TRUE);
    }
    else 
    {
	vdialogSetItemBorder(vcomboboxGetItem(master->combo1), FALSE);
	vdialogSetItemBorder(vcomboboxGetItem(master->popdown1), FALSE);
	vdialogSetItemBorder(vcomboboxGetItem(master->combo2), FALSE);
	vdialogSetItemBorder(vcomboboxGetItem(master->popdown2), FALSE);
    }
}

static void controlHideNotify(vcontrol *control, vevent *event)
{
    globals *master;
    
    master = (globals *)vcontrolGetData(control);
    
    if (vcontrolGetValue(control))
    {
	vdialogHideItem(vcomboboxGetItem(master->combo1));
	vdialogHideItem(vcomboboxGetItem(master->popdown1));
	vdialogHideItem(vcomboboxGetItem(master->combo2));
	vdialogHideItem(vcomboboxGetItem(master->popdown2));
    }
    else 
    {
	vdialogShowItem(vcomboboxGetItem(master->combo1));
	vdialogShowItem(vcomboboxGetItem(master->popdown1));
	vdialogShowItem(vcomboboxGetItem(master->combo2));
	vdialogShowItem(vcomboboxGetItem(master->popdown2));
    }
}

static void optionAcceptNotify(vcontrol *option, vevent *event)
{
    globals *master;
    
    master = (globals *)vcontrolGetData(option);

    vcomboboxSetAcceptBehavior(master->combo1, vcontrolGetValue(option));
    vcomboboxSetAcceptBehavior(master->combo2, vcontrolGetValue(option));
    vcomboboxSetAcceptBehavior(master->popdown1, vcontrolGetValue(option));
    vcomboboxSetAcceptBehavior(master->popdown2, vcontrolGetValue(option));
}

static void optionSelectNotify(vcontrol *option, vevent *event)
{
    globals *master;
    
    master = (globals *)vcontrolGetData(option);

    vcomboboxSetSelectBehavior(master->combo1, vcontrolGetValue(option));
    vcomboboxSetSelectBehavior(master->combo2, vcontrolGetValue(option));
    vcomboboxSetSelectBehavior(master->popdown1, vcontrolGetValue(option));
    vcomboboxSetSelectBehavior(master->popdown2, vcontrolGetValue(option));
}

static void optionScrollNotify(vcontrol *option, vevent *event)
{
    globals *master;
    
    master = (globals *)vcontrolGetData(option);

    vcomboboxSetScrollBehavior(master->combo1, vcontrolGetValue(option));
    vcomboboxSetScrollBehavior(master->combo2, vcontrolGetValue(option));
    vcomboboxSetScrollBehavior(master->popdown1, vcontrolGetValue(option));
    vcomboboxSetScrollBehavior(master->popdown2, vcontrolGetValue(option));
}

static void buttonAcceptNotify(vbutton *button, vevent *event)
{
    int count;
    globals *master;
    
    master = (globals *)vbuttonGetData(button);

    count = vcomboboxGetValueCount(master->combo1);
    if (count > 0)
	vcomboboxAcceptValue(master->combo1,
			     vcomboboxGetValueAt(master->combo1,
						 rand()%count));

    count = vcomboboxGetValueCount(master->popdown1);
    if (count > 0)
	vcomboboxAcceptValue(master->popdown1,
			     vcomboboxGetValueAt(master->popdown1,
						 rand()%count));

    count = vcomboboxGetValueCount(master->combo2);
    if (count > 0)
	vcomboboxAcceptValue(master->combo2,
			     vcomboboxGetValueAt(master->combo2,
						 rand()%count));

    count = vcomboboxGetValueCount(master->popdown2);
    if (count > 0)
	vcomboboxAcceptValue(master->popdown2,
			     vcomboboxGetValueAt(master->popdown2,
						 rand()%count));
}

static void buttonSelectNotify(vbutton *button, vevent *event)
{
    int count;
    globals *master;
    
    master = (globals *)vbuttonGetData(button);

    count = vcomboboxGetValueCount(master->combo1);
    if (count > 0)
	vcomboboxSelectValue(master->combo1,
			     vcomboboxGetValueAt(master->combo1,
						 rand()%count));

    count = vcomboboxGetValueCount(master->popdown1);
    if (count > 0)
	vcomboboxSelectValue(master->popdown1,
			     vcomboboxGetValueAt(master->popdown1,
						 rand()%count));

    count = vcomboboxGetValueCount(master->combo2);
    if (count > 0)
	vcomboboxSelectValue(master->combo2,
			     vcomboboxGetValueAt(master->combo2,
						 rand()%count));

    count = vcomboboxGetValueCount(master->popdown2);
    if (count > 0)
	vcomboboxSelectValue(master->popdown2,
			     vcomboboxGetValueAt(master->popdown2,
						 rand()%count));
}

static void buttonScrollNotify(vbutton *button, vevent *event)
{
    int count;
    globals *master;
    
    master = (globals *)vbuttonGetData(button);

    count = vcomboboxGetValueCount(master->combo1);
    if (count > 0)
	vcomboboxScrollToValue(master->combo1,
			       vcomboboxGetValueAt(master->combo1,
						   rand()%count));

    count = vcomboboxGetValueCount(master->popdown1);
    if (count > 0)
	vcomboboxScrollToValue(master->popdown1,
			       vcomboboxGetValueAt(master->popdown1,
						   rand()%count));

    count = vcomboboxGetValueCount(master->combo2);
    if (count > 0)
	vcomboboxScrollToValue(master->combo2,
			       vcomboboxGetValueAt(master->combo2,
						   rand()%count));
    
    count = vcomboboxGetValueCount(master->popdown2);
    if (count > 0)
	vcomboboxScrollToValue(master->popdown2,
			       vcomboboxGetValueAt(master->popdown2,
						   rand()%count));
}

/*****************************************************************************
 * main
 *****************************************************************************/

int main(int argc, char *argv[])
{
    const vname           *name;
    vresource              resource;
    vdialog               *dialog;
    vcombobox             *combo;
    vcombobox             *newCombo;
    vbutton               *button;
    vcontrol              *control;
    vfsPath               *path;
    
    vstartup(argc, argv);
    _master = (globals *)vmemAllocAndClear(sizeof(globals));

    /*
     * Set up classes
     */

    _master->comboClass = sampleGetComboboxClass();
    _master->popdownClass = sampleGetPopdownClass();

    /*
     * Get names
     */
    
    name = vnameInternGlobalLiteral("Dialog");
    path = vinstFindSameResourceScribed(vcharScribeLiteral("main.vr"));
    resource = vresourceOpenFile(path, vfsOPEN_READ_ONLY);
    resource = vresourceGet(resource, name);
    vfsDestroyPath(path);

    /*
     * Dialog...
     */
    
    dialog = vdialogLoad(resource);
    vdialogSetNotify(dialog, dialogNotify);
    _master->dialog = dialog;
    
    /*
     * Border control ...
     */

    name = vnameInternGlobalLiteral("Border");
    control = (vcontrol *)vdialogFindItem(dialog, name);
    vcontrolSetNotify(control, controlBorderNotify);
    vcontrolSetData(control, _master);
    
    /*
     * Quit button ...
     */

    name = vnameInternGlobalLiteral("Quit");
    button = (vbutton *)vdialogFindItem(dialog, name);
    vbuttonSetNotify(button, buttonQuitNotify);
    vbuttonSetData(button, _master);
    _master->quitButton = button;
    
    /*
     * Add button ...
     */

    name = vnameInternGlobalLiteral("Add");
    button = (vbutton *)vdialogFindItem(dialog, name);
    vbuttonSetNotify(button, buttonAddNotify);
    vbuttonSetData(button, _master);
    
    /*
     * Delete button ...
     */

    name = vnameInternGlobalLiteral("Delete");
    button = (vbutton *)vdialogFindItem(dialog, name);
    vbuttonSetNotify(button, buttonDeleteNotify);
    vbuttonSetData(button, _master);
    
    /*
     * Disable control ...
     */

    name = vnameInternGlobalLiteral("Disable");
    control = (vcontrol *)vdialogFindItem(dialog, name);
    vcontrolSetNotify(control, controlDisableNotify);
    vcontrolSetData(control, _master);
    
    /*
     * Copy button ...
     */

    name = vnameInternGlobalLiteral("Copy");
    button = (vbutton *)vdialogFindItem(dialog, name);
    vbuttonSetNotify(button, buttonCopyNotify);
    vbuttonSetData(button, _master);
    
    /*
     * Modifyable control ...
     */

    name = vnameInternGlobalLiteral("Modifyable");
    control = (vcontrol *)vdialogFindItem(dialog, name);
    vcontrolSetNotify(control, controlModifyableNotify);
    vcontrolSetData(control, _master);
    
    /*
     * Font button ...
     */

    name = vnameInternGlobalLiteral("Font");
    button = (vbutton *)vdialogFindItem(dialog, name);
    vbuttonSetNotify(button, buttonFontNotify);
    vbuttonSetData(button, _master);
    
    /*
     * Sort button ...
     */

    name = vnameInternGlobalLiteral("Sort");
    button = (vbutton *)vdialogFindItem(dialog, name);
    vbuttonSetNotify(button, buttonSortNotify);
    vbuttonSetData(button, _master);
    
    /*
     * Mix button ...
     */

    name = vnameInternGlobalLiteral("Mix");
    button = (vbutton *)vdialogFindItem(dialog, name);
    vbuttonSetNotify(button, buttonMixNotify);
    vbuttonSetData(button, _master);
    
    /*
     * CopyInit button ...
     */

    name = vnameInternGlobalLiteral("CopyInit");
    button = (vbutton *)vdialogFindItem(dialog, name);
    vbuttonSetNotify(button, buttonCopyInitNotify);
    vbuttonSetData(button, _master);
    
    /*
     * Hide control ...
     */

    name = vnameInternGlobalLiteral("Hide");
    control = (vcontrol *)vdialogFindItem(dialog, name);
    vcontrolSetNotify(control, controlHideNotify);
    vcontrolSetData(control, _master);
    
    /*
     * Load button ...
     */

    name = vnameInternGlobalLiteral("Load");
    button = (vbutton *)vdialogFindItem(dialog, name);
    vbuttonSetNotify(button, buttonLoadNotify);
    vbuttonSetData(button, _master);
    
    /*
     * Foreground button ...
     */

    name = vnameInternGlobalLiteral("Foreground");
    button = (vbutton *)vdialogFindItem(dialog, name);
    vbuttonSetNotify(button, buttonForegroundNotify);
    vbuttonSetData(button, _master);
    
    /*
     * Background button ...
     */

    name = vnameInternGlobalLiteral("Background");
    button = (vbutton *)vdialogFindItem(dialog, name);
    vbuttonSetNotify(button, buttonBackgroundNotify);
    vbuttonSetData(button, _master);

    /* 
     * Combobox (standard 1) ...
     */
    
    name = vnameInternGlobalLiteral("Combobox1");
    newCombo = vcomboboxCreateOfClass(_master->comboClass);
    combo = (vcombobox *)vdialogFindItem(dialog, name);
    vcomboboxSetData(newCombo, _master->quitButton);
    sampleSetup(newCombo);
    _master->combo1 = combo;
    replace(_master, newCombo, _master->combo1);

    /* 
     * Combobox (standard 2) ...
     */
    
    name = vnameInternGlobalLiteral("Combobox2");
    newCombo = vcomboboxCreateOfClass(_master->comboClass);
    combo = (vcombobox *)vdialogFindItem(dialog, name);
    vcomboboxSetData(newCombo, _master->quitButton);
    sampleSetup((vcombobox *)newCombo);
    _master->combo2 = combo;
    replace(_master, newCombo, _master->combo2);

    /* 
     * Combobox (popdown 1) ...
     */
    
    name = vnameInternGlobalLiteral("Popdown1");
    newCombo = vcomboboxCreateOfClass(_master->popdownClass);
    combo = (vcombobox *)vdialogFindItem(dialog, name);
    vcomboboxSetData(newCombo, _master->quitButton);
    sampleSetup((vcombobox *)newCombo);
    _master->popdown1 = combo;
    replace(_master, newCombo, _master->popdown1);

    /* 
     * Combobox (popdown 2) ...
     */
    
    name = vnameInternGlobalLiteral("Popdown2");
    newCombo = vcomboboxCreateOfClass(_master->popdownClass);
    combo = (vcombobox *)vdialogFindItem(dialog, name);
    vcomboboxSetData(newCombo, _master->quitButton);
    sampleSetup((vcombobox *)newCombo);
    _master->popdown2 = combo;
    replace(_master, newCombo, _master->popdown2);

    /* 
     * Accept OptionMenu ...
     */

    name = vnameInternGlobalLiteral("AcceptBehavior");
    control = (vcontrol *)vdialogFindItem(dialog, name);
    vcontrolSetNotify(control, optionAcceptNotify);
    vcontrolSetData(control, _master);
    
    /* 
     * Select OptionMenu ...
     */

    name = vnameInternGlobalLiteral("SelectBehavior");
    control = (vcontrol *)vdialogFindItem(dialog, name);
    vcontrolSetNotify(control, optionSelectNotify);
    vcontrolSetData(control, _master);
    
    /* 
     * Scroll OptionMenu ...
     */

    name = vnameInternGlobalLiteral("ScrollBehavior");
    control = (vcontrol *)vdialogFindItem(dialog, name);
    vcontrolSetNotify(control, optionScrollNotify);
    vcontrolSetData(control, _master);
    
    /* 
     * Accept Button ...
     */

    name = vnameInternGlobalLiteral("AcceptValue");
    button = (vbutton *)vdialogFindItem(dialog, name);
    vbuttonSetNotify(button, buttonAcceptNotify);
    vbuttonSetData(button, _master);
    
    /* 
     * Select Button ...
     */

    name = vnameInternGlobalLiteral("SelectValue");
    button = (vbutton *)vdialogFindItem(dialog, name);
    vbuttonSetNotify(button, buttonSelectNotify);
    vbuttonSetData(button, _master);
    
    /* 
     * Scroll Button ...
     */

    name = vnameInternGlobalLiteral("ScrollValue");
    button = (vbutton *)vdialogFindItem(dialog, name);
    vbuttonSetNotify(button, buttonScrollNotify);
    vbuttonSetData(button, _master);

    arrange(_master);

    vdialogOpen(dialog);
    
    veventProcess();
    
    vdialogDestroy(dialog);
    vmemFree(_master);
    
    exit(EXIT_SUCCESS);
    return EXIT_FAILURE;
}			   


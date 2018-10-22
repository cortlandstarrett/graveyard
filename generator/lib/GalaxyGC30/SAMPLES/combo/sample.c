/* $Id: sample.c,v 1.6 1995/04/28 14:18:53 ian Exp $ */

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
 * Executable Name: sample
 * Source Files:    sample.c, main.c
 * Resource Files:  main.vr
 *
 * Managers Illustrated:
 *      Combobox Manager
 *
 * Description Of Sample:
 *      This demo shows how to do simple comboboxes.
 *
 *      The functions below are used for setting up the combobox and
 *      using them from the main program.
 *
 *      Function                Description
 *      ---------------------------------------------------------------------
 *      sampleGetComboboxClass  Returns a simple class for standard combobox
 *      sampleGetPopdownClass   Returns a simple class for popdown combobox
 *      sampleSetup             Sets a combobox up with informations
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

#ifndef vcomboboxINCLUDED
#include vcomboboxHEADER
#endif

/*****************************************************************************
 * constants
 ****************************************************************************/

enum {
    BOOKMAN,
    CHICAGO,
    COURIER,
    FENICE,
    FUTURA,
    GALAXY,
    GARAMOND,
    GENEVA,
    HELVETICA,
    MONACO,
    PALATINO,
    SYMBOL,
    TIMES,
    NUM_FONTS
};

char *fontName[NUM_FONTS] = {
    "bookman",
    "chicago",
    "courier",
    "fenice",
    "futura",
    "galaxy",
    "garamond",
    "geneva",
    "helvetica",
    "monaco",
    "palatino",
    "symbol",
    "times"
};

/*****************************************************************************
 * private functions
 *****************************************************************************/

static void _sampleNotifyCombobox(vcombobox *combo, vevent *event, int message)
{
    vcomboboxValue *value;
    vbutton        *button;
    vscribe        *scribe;
    
    if (message != vcomboboxNOTIFY_SELECT && message != vcomboboxNOTIFY_ACCEPT)
	return;
    
    button = (vbutton *)vcomboboxGetData(combo);
    
    value = vcomboboxGetValue(combo);
    scribe = vcharScribe(vcomboboxGetValueTitle(value));
    vdialogSetItemFont(vbuttonGetItem(button), vfontFindScribed(scribe));
}

/*****************************************************************************
 * public functions
 *****************************************************************************/

vcomboboxClass *sampleGetComboboxClass(void)
{
    return vcomboboxGetDefaultClass();
}

vcomboboxPopdownClass *sampleGetPopdownClass(void)
{
    return vcomboboxGetDefaultPopdownClass();
}
    
void sampleSetup(vcombobox *combo)
{
    vcomboboxValue *value;
    int             loop;

    for (loop = 0; loop < NUM_FONTS; loop++)
    {
	value = vcomboboxCreateValue();
	vcomboboxSetValueTitleScribed(value,
				      vcharScribeLiteral(fontName[loop]));
	vcomboboxAppendValue(combo, value);
    }
    vcomboboxSelectValueAt(combo, 0);

    vcomboboxSetNotify(combo, _sampleNotifyCombobox);
}

/* $Id: sample1.c,v 1.8 1995/04/28 14:20:08 ian Exp $ */

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
 * Executable Name: sample1
 * Source Files:    sample1.c, main.c
 * Resource Files:  main.vr
 *
 * Managers Illustrated:
 *      Combobox Manager
 *
 * Description Of Sample:
 *      This demo shows how to do specialized comboboxes. 
 *      Specialized comboboxes are subclassed from comboboxes and their
 *      'entrybox' parts are entirely overriden to use vdialogLabelItem
 *      instead of standard entrybox.
 *
 *      The functions below are used for setting up the combobox and
 *      using them from the main program.
 *
 *      Function                Description
 *      ---------------------------------------------------------------------
 *      sampleGetComboboxClass  Returns specialized class for standard combobox
 *      sampleGetPopdownClass   Returns specialized class for popdown combobox
 *      sampleSetup             Sets specialized combobox up with informations
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

#ifndef vclassINCLUDED
#include vclassHEADER
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

/*****************************************************************************
 * data structures
 ****************************************************************************/

typedef struct sampleEntrybox        sampleEntrybox;
typedef struct sampleEntryboxClass   sampleEntryboxClass;

typedef void (*sampleEntryboxNoteProc)(sampleEntrybox *entrybox,
				       vevent *event);
    
struct sampleEntrybox {
    vdialogItem     item;
    vcomboboxValue *value;
};

struct sampleEntryboxClass {
    vdialogITEM_CLASS(sampleEntryboxClass,
		      sampleEntrybox, sampleEntryboxNoteProc);
};

typedef struct {
    sampleEntryboxClass   *entryboxClass;
    vcomboboxClass        *comboClass;
    vcomboboxPopdownClass *popdownClass;
} globals;

/*****************************************************************************
 * private macro
 *****************************************************************************/

#define master() ((globals *)*_master)

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

int fontLength[NUM_FONTS] = {
    7,  /* bookman */
    7,  /* chicago */
    7,  /* courier */
    6,  /* fenice */
    6,  /* futura */
    6,  /* galaxy */
    7,  /* garamond */
    6,  /* geneva */
    9,  /* helvetica */
    6,  /* monaco */
    8,  /* palatino */
    6,  /* symbol */
    5   /* times */
};

/******************************************************************************
 * variables
 *****************************************************************************/

static void **_master = NULL;

/*****************************************************************************
 * _sampleInitEntrybox initializes a combo box entrybox
 * entrybox -> the combo box entrybox to initialize
 *****************************************************************************/
static void _sampleInitEntrybox(sampleEntrybox *entrybox)
{
    /*
     * Init itself
     */
    
    vclassSendSuper(master()->entryboxClass,
		    vobjectINIT, (entrybox));
    
    /*
     * fill in the fields with default entryboxs
     */
    
    entrybox->value = vcomboboxCreateValue();
}

/*****************************************************************************
 * _sampleCopyEntrybox copys a combo box entrybox
 * entrybox -> the combo box entrybox to copy
 * target <- the combo box entrybox to be copied
 *****************************************************************************/
static void _sampleCopyEntrybox(sampleEntrybox *entrybox,
				sampleEntrybox *target)
{
    /*
     * Copy itself
     */
    
    vclassSendSuper(master()->entryboxClass,
		    vobjectCOPY, (entrybox, target));
    
    /*
     * Low-level copying
     */
    
    vcomboboxDestroyValue(target->value);
    target->value = vcomboboxCloneValue(entrybox->value);
}

/*****************************************************************************
 * _sampleCopyInitEntrybox initializes and copies a combo box entrybox
 * entrybox -> the combo box entrybox to copy
 * target <- the combo box entrybox to be copied
 *****************************************************************************/
static void _sampleCopyInitEntrybox(sampleEntrybox *entrybox,
				    sampleEntrybox *target)
{
    vclassSendSuper(master()->entryboxClass,
		    vobjectCOPY_INIT, (entrybox, target));
    
    /*
     * Stores value
     */
    
    target->value = vcomboboxCloneValue(entrybox->value);
}

/*****************************************************************************
 * _sampleDestroyEntrybox destroys a combo box entrybox
 * entrybox -> the combo box entrybox to destroy
 *****************************************************************************/
static void _sampleDestroyEntrybox(sampleEntrybox *entrybox)
{
    vcomboboxDestroyValue(entrybox->value);
    
    /*
     * Destroy itself
     */
    
    vclassSendSuper(master()->entryboxClass,
		    vobjectDESTROY, (entrybox));
}

/*****************************************************************************
 * _sampleLoadInitEntrybox initializes and copies a combo box entrybox
 * entrybox <-> the combo box entrybox to be initialized and loaded
 * resource -> resource to load combobox entrybox from
 *****************************************************************************/
static void _sampleLoadInitEntrybox(sampleEntrybox *entrybox,
				    vresource resource)
{
    vresource  res;
    
    /*
     * Load itself
     */
    
    vclassSendSuper(master()->entryboxClass,
		    vobjectLOAD_INIT, (entrybox, resource));
    
    if (vresourceTestGet(resource, vname_Value, &res))
	entrybox->value = vcomboboxLoadValue(res);
    else
	entrybox->value = vcomboboxCreateValue();
}

/*****************************************************************************
 * _sampleStoreEntrybox stores a combo box entrybox to resource
 * entrybox -> the combo box entrybox to store
 * resource <- resource to store combo box entrybox
 *****************************************************************************/
static void _sampleStoreEntrybox(sampleEntrybox *entrybox,
				 vresource resource)
{
    vclassSendSuper(master()->entryboxClass,
		    vobjectSTORE, (entrybox, resource));
    
    /*
     * Stores title
     */
    
    vcomboboxStoreValue(entrybox->value,
			vresourceMake(resource, vname_Value));
}

/*****************************************************************************
 * _sampleDrawEntrybox draws the entrybox
 * entrybox -> entrybox to draw
 *****************************************************************************/
static void _sampleDrawEntrybox(sampleEntrybox *entrybox)
{
    vcolor *color;
    vcolorScheme scheme;

    color = vdrawGetColor();
    vdialogDetermineItemColorSchemeState((vdialogItem *)entrybox,
					 vcolorFLAG_FOREGROUND|
					 vcolorFLAG_BACKGROUND, &scheme);

    if (vdialogItemFocusIsVisible((vdialogItem *)entrybox))
    {
	vdrawSetColor(vcolorGetSchemeForeground(&scheme));
	vdrawRectsFill(vdialogGetItemRect((vdialogItem *)entrybox), 1);
	vdrawSetColor(vcolorGetSchemeBackground(&scheme));
	vcomboboxDrawValue
	    (entrybox->value,
	     (vrect *)vdialogGetItemRect((vdialogItem *)entrybox));
    }
    else
    {
	vdrawSetColor(vcolorGetSchemeBackground(&scheme));
	vdrawRectsFill(vdialogGetItemRect((vdialogItem *)entrybox), 1);
	vdrawSetColor(vcolorGetSchemeForeground(&scheme));
	vcomboboxDrawValue
	    (entrybox->value,
	     (vrect *)vdialogGetItemRect((vdialogItem *)entrybox));
    }
    
    vdrawSetColor(color);
}

/*****************************************************************************
 * _sampleGetEntryboxMinSize returns the minimum size of entrybox
 * entrybox -> entrybox to get minimum size
 * width <- the minimum width
 * height <- the minimum height
 *****************************************************************************/
static void _sampleGetEntryboxMinSize(sampleEntrybox *entrybox,
				       int *width, int *height)
{
    vdialogGetItemNaturalSize((vdialogItem *)entrybox, width, height);
}

/*****************************************************************************
 * _sampleGetEntryboxNaturalSize get the natural size of entrybox
 * entrybox -> entrybox to get natural size
 * width <- the natural width
 * height <- the natural height
 *****************************************************************************/
static void _sampleGetEntryboxNaturalSize(sampleEntrybox *entrybox,
					  int *width, int *height)
{
    vcombobox *combo;

    combo = vcomboboxGetPartCombobox((vdialogItem *)entrybox);
    if (combo)
	vcomboboxGetValueMaxSize(combo, width, height);
    else
	vclassSendSuper(master()->entryboxClass,
			vdialogGET_ITEM_NATURAL_SIZE,
			(entrybox, width, height));
}

/******************************************************************************
 * private overrides for standard combo box boxes
 *****************************************************************************/

static vdialogItem *_sampleCreateEntrybox(vcombobox *combo)
{
    vdialogItem *item;
    
    item = vdialogCreateItemOfClass(master()->entryboxClass);

    vdialogSetItemFocusable(item, TRUE);
    
    return (vdialogItem *)item;
}

static void _sampleGetEntryboxSize(vcombobox *combo,
				   int *width,
				   int *height)
{
    vcomboboxGetValueMaxSize(combo, width, height);
}

static vcomboboxValue *_sampleGetEntryboxValue(vcombobox *combo, 
					       vdialogItem *entrybox)
{
    sampleEntrybox *sample;
    
    sample = (sampleEntrybox *)entrybox;
    
    return sample->value;
}

static void _sampleSetEntryboxModifyable(vcombobox *combo, 
					 vdialogItem *entrybox,
					 int onOff)
{
    /*
     * Do nothing
     */
}

static void _sampleSetEntryboxValue(vcombobox *combo,
				    vdialogItem *entrybox,
				    vcomboboxValue *value)
{
    sampleEntrybox *sample;
    
    sample = (sampleEntrybox *)entrybox;

    if (value != sample->value)
	vcomboboxCopyValue(value, sample->value);
    
    vdialogInvalItem(entrybox, 0);
}

/******************************************************************************
 * private overrides for popdown combo box boxes
 *****************************************************************************/

static vdialogItem *_sampleCreatePopdownEntrybox(vcomboboxPopdown *combo)
{
    return _sampleCreateEntrybox(vcomboboxGetPopdownCombobox(combo));
}

static void _sampleGetPopdownEntryboxSize(vcomboboxPopdown *combo,
					  int *width,
					  int *height)
{
    _sampleGetEntryboxSize(vcomboboxGetPopdownCombobox(combo), width, height);
}

static vcomboboxValue *_sampleGetPopdownEntryboxValue(vcomboboxPopdown *combo, 
						      vdialogItem *entrybox)
{
    return _sampleGetEntryboxValue(vcomboboxGetPopdownCombobox(combo),
				   entrybox);
}

static void _sampleSetPopdownEntryboxModifyable(vcomboboxPopdown *combo, 
						vdialogItem *entrybox,
						int onOff)
{
    _sampleSetEntryboxModifyable(vcomboboxGetPopdownCombobox(combo),
				 entrybox, onOff);
}

static void _sampleSetPopdownEntryboxValue(vcomboboxPopdown *combo,
					   vdialogItem *entrybox,
					   vcomboboxValue *value)
{
    _sampleSetEntryboxValue(vcomboboxGetPopdownCombobox(combo),
			    entrybox, value);
}

static void _sampleSetupEntryboxClass(void)
{
    sampleEntryboxClass   *entryboxClas;

    /*
     * Create a new entrybox class
     */
    
    entryboxClas = (sampleEntryboxClass *)
	vclassSpawn(vdialogGetDefaultItemClass(), sizeof(sampleEntryboxClass));
    vclassSetObjectSize(entryboxClas,
			sizeof(sampleEntrybox));
    vclassSetNameScribed(entryboxClas,
			 vcharScribeLiteral("sampleEntrybox"));
    vclassSet(entryboxClas,
	      vobjectDESTROY, _sampleDestroyEntrybox);
    vclassSet(entryboxClas,
	      vobjectINIT, _sampleInitEntrybox);
    vclassSet(entryboxClas,
	      vobjectCOPY, _sampleCopyEntrybox);
    vclassSet(entryboxClas,
	      vobjectCOPY_INIT, _sampleCopyInitEntrybox);
    vclassSet(entryboxClas,
	      vobjectLOAD_INIT, _sampleLoadInitEntrybox);
    vclassSet(entryboxClas,
	      vobjectSTORE, _sampleStoreEntrybox);

    vclassSet(entryboxClas,
	      vdialogDRAW_ITEM, _sampleDrawEntrybox);
    vclassSet(entryboxClas,
	      vdialogDRAW_ITEM_FOCUS, _sampleDrawEntrybox);
    vclassSet(entryboxClas,
	      vdialogGET_ITEM_MIN_SIZE, _sampleGetEntryboxMinSize);
    vclassSet(entryboxClas,
	      vdialogGET_ITEM_NATURAL_SIZE, _sampleGetEntryboxNaturalSize);

    master()->entryboxClass = entryboxClas;
}

static void _sampleSetupComboboxClass(void)
{
    vcomboboxClass *comboClas;

    /*
     * Create a new standard combobox box class
     */
    
    comboClas = (vcomboboxClass *)vclassReproduce(vcomboboxGetDefaultClass());
    vclassSetNameScribed(comboClas,
			 vcharScribeLiteral("sampleCombobox"));
    vclassSet(comboClas,
	      vcomboboxCREATE_ENTRYBOX, _sampleCreateEntrybox);
    vclassSet(comboClas,
	      vcomboboxGET_ENTRYBOX_SIZE, _sampleGetEntryboxSize);
    vclassSet(comboClas,
	      vcomboboxGET_ENTRYBOX_VALUE, _sampleGetEntryboxValue);
    vclassSet(comboClas,
	      vcomboboxSET_ENTRYBOX_MODIFYABLE, _sampleSetEntryboxModifyable);
    vclassSet(comboClas,
	      vcomboboxSET_ENTRYBOX_VALUE, _sampleSetEntryboxValue);
    
    master()->comboClass = comboClas;
}

static void _sampleSetupPopdownClass(void)
{
    vcomboboxPopdownClass *popdownClas;
    
    /*
     * Create a new popdown combobox box class
     */
    
    popdownClas = (vcomboboxPopdownClass *)
	vclassReproduce(vcomboboxGetDefaultPopdownClass());
    vclassSetNameScribed(popdownClas,
			 vcharScribeLiteral("samplePopdown"));
    vclassSet(popdownClas,
	      vcomboboxCREATE_ENTRYBOX, _sampleCreatePopdownEntrybox);
    vclassSet(popdownClas,
	      vcomboboxGET_ENTRYBOX_SIZE, _sampleGetPopdownEntryboxSize);
    vclassSet(popdownClas,
	      vcomboboxGET_ENTRYBOX_VALUE, _sampleGetPopdownEntryboxValue);
    vclassSet(popdownClas,
	      vcomboboxSET_ENTRYBOX_MODIFYABLE, _sampleSetPopdownEntryboxModifyable);
    vclassSet(popdownClas,
	      vcomboboxSET_ENTRYBOX_VALUE, _sampleSetPopdownEntryboxValue);
    
    master()->popdownClass = popdownClas;
}

static void _sampleSetupClasses(void)
{
    if (_master == NULL)
    {
	_master = vclientRegisterModule();
    }

    if (*_master == NULL)
    {
	vclientAllocateModule(_master, sizeof(globals));

	_sampleSetupEntryboxClass();
	_sampleSetupComboboxClass();
	_sampleSetupPopdownClass();
    }
}

void _sampleNotifyCombobox(vcombobox *combo, vevent *event, int message)
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

vcomboboxClass *sampleGetComboboxClass(void)
{
    _sampleSetupClasses();

    return master()->comboClass;
}

vcomboboxPopdownClass *sampleGetPopdownClass(void)
{
    _sampleSetupClasses();

    return master()->popdownClass;
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




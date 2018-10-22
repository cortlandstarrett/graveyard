/* $Id: sample2.c,v 1.8 1995/04/28 14:44:21 ian Exp $ */

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
 * Executable Name: sample2
 * Source Files:    sample2.c, main.c
 * Resource Files:  main.vr
 *
 * Managers Illustrated:
 *      Combobox Manager
 *
 * Description Of Sample:
 *      This demo shows how to do specialized comboboxes. 
 *      Specialized comboboxes are subclassed from comboboxes and their
 *      'choicebox' parts are entirely overriden to use vpalette, instead
 *      of standard choicebox.
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

#ifndef vpaletteINCLUDED
#include vpaletteHEADER
#endif

/*****************************************************************************
 * data structures
 ****************************************************************************/

typedef struct sampleChoicebox      sampleChoicebox;
typedef struct sampleChoiceboxClass sampleChoiceboxClass;

struct sampleChoicebox {
    vpalette palette;
};

struct sampleChoiceboxClass {
    vpaletteCLASS(sampleChoiceboxClass, sampleChoicebox, vpaletteItem);
};

typedef struct {
    sampleChoiceboxClass   *choiceboxClass;
    vcomboboxClass         *comboClass;
    vcomboboxPopdownClass  *popdownClass;
} globals;

/*****************************************************************************
 * macro
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

/*****************************************************************************
 * variables
 *****************************************************************************/

static void **_master = NULL;

/*****************************************************************************
 * private class method overrides for combobox choicebox
 *****************************************************************************/

/*****************************************************************************
 * _sampleGetChoiceboxMinSize returns the minimum size of choicebox
 * choicebox -> choicebox to get minimum size
 * width <- the minimum width
 * height <- the minimum height
 *****************************************************************************/
static void _sampleGetChoiceboxMinSize(sampleChoicebox *choicebox,
				       int *width, int *height)
{
    vdialogGetItemNaturalSize((vdialogItem *)choicebox, width, height);
}

/*****************************************************************************
 * private class method overrides for standard combobox box
 *****************************************************************************/

static void _sampleNotifyPaletteItem(vpalette *palette,
				     vpaletteItem *item)
{
    vcombobox *combo;
    vevent *event;
    int     index;
    
    combo = vcomboboxGetPartCombobox(vpaletteGetItem(palette));
    
    index = vpaletteGetItemIndex(palette, item);
    vcomboboxSelectValueAt(combo, index);
    
    /*
     * Generates a notify for combobox (with a fake event)
     */
    
    event = veventCreateClient();
    vcomboboxNotify(combo, event, vcomboboxNOTIFY_SELECT);
    veventDestroy(event);
}

static vdialogItem *_sampleCreateChoicebox(vcombobox *combo)
{
    vpalette    *palette;
    vdialogItem *item;
    
    palette = vpaletteCreateOfClass(master()->choiceboxClass);
    vpaletteSetColumns(palette, vcomboboxGetVisibleValues(combo));
    vpaletteSetImageSize(palette, 32, 20);

    item = vpaletteGetItem(palette);
    vdialogSetItemFocusable(item, FALSE);
    vdialogSetItemClickFocusable(item, FALSE);
    
    return (vdialogItem *)palette;
}

static void _sampleAppendChoiceboxValue(vcombobox *combo, 
					vdialogItem *choicebox,
					vcomboboxValue *value)
{
    vpalette     *palette;
    vpaletteItem *item;
    vimage       *image;
    int           w, h;
    vrect         rect;
    
    palette = (vpalette *)choicebox;
    
    /*
     * Create an image for palette item
     */
    
    vcomboboxGetComboboxValueSize(combo, value, &w, &h);
    image = vwindowCreateBufferImage(w, h);
    vdrawGSave();
    vdrawImageDevice(image);
    vrectSet(0, 0, w, h, &rect);
    vdrawSetColor(vcolorGetWhite());
    vdrawRectsFill(&rect, 1);
    vdrawSetColor(vcolorGetBlack());
    vcomboboxDrawComboboxValue(combo, value, &rect);
    vdrawGRestore();
    
    /*
     * Create a palette item and attach image to it
     */
    
    item = vpaletteCreateItem();
    vpaletteSetItemImage(item, image);
    vpaletteSetItemNotify(item, _sampleNotifyPaletteItem);
    vimageDestroy(image);
    
    /*
     * Finally attach the palette item to palette
     */
    
    vpaletteAppendItem(palette, item);
}

static void _sampleDeleteChoiceboxValueAt(vcombobox *combo,
					  vdialogItem *choicebox,
					  int index)
{
    vpaletteDeleteItemIndex((vpalette *)choicebox, index);
}

static int _sampleGetChoiceboxSelectedIndex(vcombobox *combo,
					    vdialogItem *choicebox)
{
    vpalette *palette;
    vpaletteItem *item;
    
    palette = (vpalette *)choicebox;
    item = vpaletteGetSelection(palette);
    if (item)
	return vpaletteGetItemIndex(palette, item);
    else
	return -1;
}

static void _sampleMoveChoiceboxValue(vcombobox *combo,
				      vdialogItem *choicebox,
				      int from,
				      int to)
{
    vpalette *palette;
    vpaletteItem *item;
    
    palette = (vpalette *)choicebox;
    item = vpaletteCloneItem(vpaletteGetItemAt(palette, from));
    vpaletteDeleteItemIndex(palette, from);
    vpaletteInsertItem(palette, to, item);
}

static void _sampleScrollChoiceboxToIndex(vcombobox *combo,
					  vdialogItem *choicebox,
					  int index)
{
    vpalette *palette;
    int       top, bottom;
    int       left, right;
    int       row, col;
    
    palette = (vpalette *)choicebox;
    
    if (vpaletteGetItemCount(palette) == 0 ||
	vpaletteGetItemCount(palette) <= index)
	return;
    
    if (index < 0)
	vlistviewScrollToCell(vpaletteGetListview(palette), 0, 0);
    else
    {
	col = index % vpaletteGetColumnCount(palette);
	row = index / vpaletteGetColumnCount(palette);
	
	top = vlistviewGetTopRow(vpaletteGetListview(palette));
	bottom = vlistviewGetBottomRow(vpaletteGetListview(palette)) - 1;
	left = vlistviewGetLeftColumn(vpaletteGetListview(palette));
	right = vlistviewGetRightColumn(vpaletteGetListview(palette)) - 1;
	if (bottom < top)
	    bottom = top;
	if (right < left)
	    right = left;
	
	if (row < top || row >= bottom)
	{
	    if (col < left || col >= right)
		vlistviewScrollToCell(vpaletteGetListview(palette), row, col);
	    else
		vlistviewScrollToCell(vpaletteGetListview(palette), row, left);
	}
	else  if (col < left || col >= right)
	    vlistviewScrollToCell(vpaletteGetListview(palette), top, col);
    }
}

static void _sampleSelectChoiceboxValueAt(vcombobox *combo,
					  vdialogItem *choicebox,
					  int index)
{
    vpalette *palette;
    
    palette = (vpalette *)choicebox;
    if (index == -1)
	vpaletteSetSelection(palette, NULL);
    else if (vpaletteGetItemIndex(palette,
				  vpaletteGetSelection(palette)) != index)
	vpaletteSetSelection(palette, vpaletteGetItemAt(palette, index));
}


static void _sampleSetChoiceboxValueAt(vcombobox *combo,
				       vdialogItem *choicebox,
				       vcomboboxValue *value,
				       int index)
{
    vpalette     *palette;
    vpaletteItem *item;
    vimage       *image;
    int           w, h;
    vrect         rect;
    
    palette = (vpalette *)choicebox;
    while (index >= vpaletteGetItemCount(palette))
    {
	item = vpaletteCreateItem();
	vpaletteAppendItem(palette, item);
	vpaletteSetItemNotify(item, _sampleNotifyPaletteItem);
    }
    item = vpaletteGetItemAt(palette, index);
    
    /*
     * Create an image for palette item
     */
    
    vcomboboxGetComboboxValueSize(combo, value, &w, &h);
    image = vwindowCreateBufferImage(w, h);
    vdrawGSave();
    vdrawImageDevice(image);
    vrectSet(0, 0, w, h, &rect);
    vdrawSetColor(vcolorGetWhite());
    vdrawRectsFill(&rect, 1);
    vdrawSetColor(vcolorGetBlack());
    vcomboboxDrawComboboxValue(combo, value, &rect);
    vdrawGRestore();
    
    /*
     * Redo the item's image
     */
    
    vpaletteSetItemImage(item, image);
    vimageDestroy(image);
}


static void _sampleSetChoiceboxVisibleValues(vcombobox *combo,
					     vdialogItem *choicebox,
					     int index)
{
    vpaletteSetColumns((vpalette *)choicebox, index);
}

static void _sampleSetChoiceboxWrap(vcombobox *combo,
				    vdialogItem *choicebox,
				    int onOff)
{
    /*
     * Do nothing
     */
}

/*****************************************************************************
 * private class method overrides for popdown combobox box
 *****************************************************************************/

static vdialogItem *_sampleCreatePopdownChoicebox(vcomboboxPopdown *combo)
{
    return _sampleCreateChoicebox(vcomboboxGetPopdownCombobox(combo));
}

static void _sampleAppendPopdownChoiceboxValue(vcomboboxPopdown *combo, 
					       vdialogItem *choicebox,
					       vcomboboxValue *value)
{
    _sampleAppendChoiceboxValue(vcomboboxGetPopdownCombobox(combo),
				choicebox, value);
}

static void _sampleDeletePopdownChoiceboxValueAt(vcomboboxPopdown *combo,
						 vdialogItem *choicebox,
						 int index)
{
    _sampleDeleteChoiceboxValueAt(vcomboboxGetPopdownCombobox(combo),
				  choicebox, index);
}

static int _sampleGetPopdownChoiceboxSelectedIndex(vcomboboxPopdown *combo,
						   vdialogItem *choicebox)
{
    return _sampleGetChoiceboxSelectedIndex(vcomboboxGetPopdownCombobox(combo),
					    choicebox);
}

static void _sampleMovePopdownChoiceboxValue(vcomboboxPopdown *combo,
					     vdialogItem *choicebox,
					     int from,
					     int to)
{
    _sampleMoveChoiceboxValue(vcomboboxGetPopdownCombobox(combo),
			      choicebox, from, to);
}

static void _sampleScrollPopdownChoiceboxToIndex(vcomboboxPopdown *combo,
						 vdialogItem *choicebox,
						 int index)
{
    _sampleScrollChoiceboxToIndex(vcomboboxGetPopdownCombobox(combo),
				  choicebox, index);
}

static void _sampleSelectPopdownChoiceboxValueAt(vcomboboxPopdown *combo,
						 vdialogItem *choicebox,
						 int index)
{
    _sampleSelectChoiceboxValueAt(vcomboboxGetPopdownCombobox(combo),
				  choicebox, index);
}


static void _sampleSetPopdownChoiceboxValueAt(vcomboboxPopdown *combo,
					      vdialogItem *choicebox,
					      vcomboboxValue *value,
					      int index)
{
    _sampleSetChoiceboxValueAt(vcomboboxGetPopdownCombobox(combo),
			       choicebox, value, index);
}


static void _sampleSetPopdownChoiceboxVisibleValues(vcomboboxPopdown *combo,
						    vdialogItem *choicebox,
						    int index)
{
    _sampleSetChoiceboxVisibleValues(vcomboboxGetPopdownCombobox(combo),
				     choicebox, index);
}

static void _sampleSetPopdownChoiceboxWrap(vcomboboxPopdown *combo,
					   vdialogItem *choicebox,
					   int onOff)
{
    _sampleSetChoiceboxWrap(vcomboboxGetPopdownCombobox(combo),
			    choicebox, onOff);
}

/*****************************************************************************
 * main
 *****************************************************************************/

static void _sampleSetupChoiceboxClass(void)
{
    sampleChoiceboxClass *choiceboxClas;

    /*
     * Create a new choicebox class for combobox boxes
     */
    
    choiceboxClas = (sampleChoiceboxClass *)
	vclassSpawn(vpaletteGetDefaultClass(), sizeof(sampleChoiceboxClass));
    vclassSetObjectSize(choiceboxClas,
			sizeof(sampleChoicebox));
    vclassSetNameScribed(choiceboxClas,
			 vcharScribeLiteral("sampleChoicebox"));

    vclassSet(choiceboxClas,
	      vdialogGET_ITEM_MIN_SIZE, _sampleGetChoiceboxMinSize);

    master()->choiceboxClass = choiceboxClas;
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
	      vcomboboxAPPEND_CHOICEBOX_VALUE, _sampleAppendChoiceboxValue);
    vclassSet(comboClas,
	      vcomboboxCREATE_CHOICEBOX, _sampleCreateChoicebox);
    vclassSet(comboClas,
	      vcomboboxDELETE_CHOICEBOX_VALUE_AT, _sampleDeleteChoiceboxValueAt);
    vclassSet(comboClas,
	      vcomboboxGET_CHOICEBOX_SELECTED_INDEX, _sampleGetChoiceboxSelectedIndex);
    vclassSet(comboClas,
	      vcomboboxMOVE_CHOICEBOX_VALUE, _sampleMoveChoiceboxValue);
    vclassSet(comboClas,
	      vcomboboxSCROLL_CHOICEBOX_TO_INDEX, _sampleScrollChoiceboxToIndex);
    vclassSet(comboClas,
	      vcomboboxSELECT_CHOICEBOX_VALUE_AT, _sampleSelectChoiceboxValueAt);
    vclassSet(comboClas,
	      vcomboboxSET_CHOICEBOX_VALUE_AT, _sampleSetChoiceboxValueAt);
    vclassSet(comboClas,
	      vcomboboxSET_CHOICEBOX_VALUE_AT, _sampleSetChoiceboxValueAt);
    vclassSet(comboClas,
	      vcomboboxSET_CHOICEBOX_VISIBLE_VALUES, _sampleSetChoiceboxVisibleValues);
    vclassSet(comboClas,
	      vcomboboxSET_CHOICEBOX_WRAP, _sampleSetChoiceboxWrap);
    
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
	      vcomboboxAPPEND_CHOICEBOX_VALUE, _sampleAppendPopdownChoiceboxValue);
    vclassSet(popdownClas,
	      vcomboboxCREATE_CHOICEBOX, _sampleCreatePopdownChoicebox);
    vclassSet(popdownClas,
	      vcomboboxDELETE_CHOICEBOX_VALUE_AT, _sampleDeletePopdownChoiceboxValueAt);
    vclassSet(popdownClas,
	      vcomboboxGET_CHOICEBOX_SELECTED_INDEX, _sampleGetPopdownChoiceboxSelectedIndex);
    vclassSet(popdownClas,
	      vcomboboxMOVE_CHOICEBOX_VALUE, _sampleMovePopdownChoiceboxValue);
    vclassSet(popdownClas,
	      vcomboboxSCROLL_CHOICEBOX_TO_INDEX, _sampleScrollPopdownChoiceboxToIndex);
    vclassSet(popdownClas,
	      vcomboboxSELECT_CHOICEBOX_VALUE_AT, _sampleSelectPopdownChoiceboxValueAt);
    vclassSet(popdownClas,
	      vcomboboxSET_CHOICEBOX_VALUE_AT, _sampleSetPopdownChoiceboxValueAt);
    vclassSet(popdownClas,
	      vcomboboxSET_CHOICEBOX_VALUE_AT, _sampleSetPopdownChoiceboxValueAt);
    vclassSet(popdownClas,
	      vcomboboxSET_CHOICEBOX_VISIBLE_VALUES, _sampleSetPopdownChoiceboxVisibleValues);
    vclassSet(popdownClas,
	      vcomboboxSET_CHOICEBOX_WRAP, _sampleSetPopdownChoiceboxWrap);
    
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

	_sampleSetupChoiceboxClass();
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


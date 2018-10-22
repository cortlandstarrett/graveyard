/* $Id: sample5.c,v 1.7 1995/04/28 14:45:34 ian Exp $ */

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
 * Executable Name: sample5
 * Source Files:    sample5.c, main.c
 * Resource Files:  main.vr
 *
 * Managers Illustrated:
 *      Combobox Manager
 *
 * Description Of Sample:
 *      This demo shows how to do specialized comboboxes. 
 *      Specialized comboboxes are subclassed from comboboxes and use 
 *      more than one column in 'choicebox' part.
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

typedef struct sampleChoicebox      sampleChoicebox;
typedef struct sampleChoiceboxClass sampleChoiceboxClass;

struct sampleChoicebox {
    vlistitem listitem;
};

struct sampleChoiceboxClass {
    vlistitemCLASS(sampleChoiceboxClass, sampleChoicebox, vlistitemNoteProc);
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
 * _sampleNotifyChoiceboxSelect handles the sample combo box's
 *       choicebox selection
 * listitem -> listitem to be handled
 * state    -> the state of selection
 *****************************************************************************/
static void _sampleNotifyChoiceboxSelect(sampleChoicebox *choicebox,
					 int state)
{
    if (state == vlistviewSELECTION_HAS_CHANGED)
    {
	int row;
	
	row = vlistitemGetSelectedRow((vlistitem *)choicebox);
	if (row != vlistNO_CELLS_SELECTED)
	{
	    vevent       *event;
	    vcombobox      *combo;
	    vcomboboxValue *value;
	    
	    combo = vcomboboxGetPartCombobox(vlistitemGetItem((vlistitem *)choicebox));
	    if (combo)
	    {
		value = vcomboboxGetValue(combo);
		if (row != vcomboboxFindValueExactIndex(combo, value,
						   vcomboboxSEARCH_FORWARD,
						   vcomboboxFROM_BEGINNING))
		{
		    vcomboboxSelectValueAt(combo, row);
		    event = veventCreateClient();
		    vcomboboxNotify(combo, event, vcomboboxNOTIFY_SELECT);
		    veventDestroy(event);
		}
	    }
	}
    }
    
    vclassSendSuper(master()->choiceboxClass,
		    vlistviewNOTIFY_SELECT, (choicebox, state));
}

/*****************************************************************************
 * _sampleGetChoiceboxContentNaturalSize returns the natural content size
 * choicebox -> choicebox to get content natural size
 * width    <- the natural width
 * height   <- the natural height
 *****************************************************************************/
static void _sampleGetChoiceboxContentNaturalSize(sampleChoicebox *choicebox,
						  int *width, int *height)
{
    int     w, h;
    vcombobox *combo;
    
    combo = vcomboboxGetPartCombobox(vlistitemGetItem((vlistitem *)choicebox));
    if (combo)
    {
	vcomboboxGetValueMaxSize(combo, &w, &h);
	
	vlistviewSetColumnWidth(vlistitemGetView((vlistitem *)choicebox), 
				0, w);
	vlistviewSetColumnWidth(vlistitemGetView((vlistitem *)choicebox),
				1, 200);
	vlistviewSetRowHeight(vlistitemGetView((vlistitem *)choicebox),
			      vlistviewALL_ROWS, h);
    }
    
    vclassSendSuper(master()->choiceboxClass,
		    vlistviewGET_CONTENT_NATURAL_SIZE,
		    (choicebox, width, height));
}

/*****************************************************************************
 * _sampleDrawChoiceboxCellContents draws the default cell contents
 * choicebox -> the choicebox to draw upon
 * row      -> the row to draw upon
 * column   -> the column to draw upon
 * selected -> selected flag
 * rect	    -> the area to draw in (skipped-over selection highlighting frobs)
 *****************************************************************************/
static void _sampleDrawChoiceboxCellContents(sampleChoicebox *choicebox,
					     int row, int column, 
					     int selected, 
					     register vrect *rect)
{
    if (column == 0)
    {
	vcomboboxValue *value;
	
	if (vlistitemGetList((vlistitem *)choicebox) != NULL)
	{
	    value = (vcomboboxValue *)
		vlistGetCellValue(vlistitemGetList((vlistitem *)choicebox),
				  row, column);
	    if (value != NULL)
	    {
		vcomboboxDrawValue(value, rect);
	    }
	}
    }
    else
	vclassSendSuper(master()->choiceboxClass,
			vlistviewDRAW_CELL_CONTENTS,
			(choicebox, row, column, selected, rect));
}

/*****************************************************************************
 * private class method overrides for standard combobox box
 *****************************************************************************/

static void _sampleAppendChoiceboxValue(vcombobox *combo, 
					vdialogItem *choicebox,
					vcomboboxValue *value)
{
    int       index;
    vliststr *liststr;

    liststr = vlistitemGetListstr((vlistitem *)choicebox);
    index = vliststrGetRowCount(liststr);
    vliststrSetCellValue(liststr, index, 0, value);
    vliststrSetCellValueScribed(liststr, index, 1, 
				vcharScribeLiteral("Descriptions Here"));
}

static vdialogItem *_sampleCreateChoicebox(vcombobox *combo)
{
    vlistitem   *listitem;
    vdialogItem *item;
    
    listitem = vlistitemCreateOfClass(master()->choiceboxClass);
    vlistitemSetVisibleRows(listitem, vcomboboxGetVisibleValues(combo));
    vlistviewSetTraversalWrap(vlistitemGetView(listitem),
			      vcomboboxIsWrap(combo));
    vlistviewSetRowHeight(vlistitemGetView(listitem), vlistviewALL_ROWS, 0);
    vlistviewSetColumnWidth(vlistitemGetView(listitem),
			    vlistviewALL_COLUMNS, 100);
    vlistitemSetAutowidth(listitem, FALSE);
    vlistSetExtendRowSelection(vlistitemGetList(listitem),
			       vlistitemGetSelection(listitem),
			       TRUE);
    
    item = vlistitemGetItem(listitem);
    vdialogSetItemFocusable(item, FALSE);
    vdialogSetItemClickFocusable(item, FALSE);
    
    return (vdialogItem *)listitem;
}

static void _sampleDeleteChoiceboxValueAt(vcombobox *combo,
					  vdialogItem *choicebox,
					  int index)
{
    vlistitemRemoveRow((vlistitem *)choicebox, index);
}

static int _sampleGetChoiceboxSelectedIndex(vcombobox *combo,
					    vdialogItem *choicebox)
{
    return vlistitemGetSelectedRow((vlistitem *)choicebox);
}

static void _sampleMoveChoiceboxValue(vcombobox *combo,
				      vdialogItem *choicebox,
				      int from,
				      int to)
{
    vlistMoveRow(vlistitemGetList((vlistitem *)choicebox), from, to);
}

static void _sampleScrollChoiceboxToIndex(vcombobox *combo,
					  vdialogItem *choicebox,
					  int index)
{
    int top, bottom;
    
    if (vlistitemGetRowCount((vlistitem *)choicebox) == 0 ||
	vlistitemGetRowCount((vlistitem *)choicebox) <= index)
	return;
    
    if (index < 0)
	vlistviewScrollToCell((vlistview *)choicebox, 0, 0);
    else
    {
	top = vlistviewGetTopRow((vlistview *)choicebox);
	bottom = vlistviewGetBottomRow((vlistview *)choicebox) - 1;
	if (bottom < top) bottom = top;
	
	if (index < top)
	    vlistviewScrollToCell((vlistview *)choicebox, index, 0);
	else if (index >= bottom)
	    vlistviewScrollToCell((vlistview *)choicebox,
				  index - bottom + top, 0);
    }
}

static void _sampleSelectChoiceboxValueAt(vcombobox *combo,
					  vdialogItem *choicebox,
					  int index)
{
    if (index >= 0)
	vlistitemSelectRow((vlistitem *)choicebox, index);
    else
	vlistUnselectAll(vlistitemGetList((vlistitem *)choicebox),
			 vlistitemGetSelection((vlistitem *)choicebox));
}


static void _sampleSetChoiceboxValueAt(vcombobox *combo,
				       vdialogItem *choicebox,
				       vcomboboxValue *value,
				       int index)
{
    vliststr *liststr;

    liststr = vlistitemGetListstr((vlistitem *)choicebox);
    vliststrSetCellValue(liststr, index, 0, value);
    vliststrSetCellValueScribed(liststr, index, 1, 
				vcharScribeLiteral("Description here"));
}


static void _sampleSetChoiceboxVisibleValues(vcombobox *combo,
					     vdialogItem *choicebox,
					     int count)
{
    vlistitemSetVisibleRows((vlistitem *)choicebox, count);
}

static void _sampleSetChoiceboxWrap(vcombobox *combo,
				    vdialogItem *choicebox,
				    int onOff)
{
    vlistviewSetTraversalWrap((vlistview *)choicebox, onOff);
}

/*****************************************************************************
 * private class method overrides for popdown combobox box
 *****************************************************************************/

static void _sampleAppendPopdownChoiceboxValue(vcomboboxPopdown *combo, 
					       vdialogItem *choicebox,
					       vcomboboxValue *value)
{
    _sampleAppendChoiceboxValue(vcomboboxGetPopdownCombobox(combo),
				choicebox, value);
}

static vdialogItem *_sampleCreatePopdownChoicebox(vcomboboxPopdown *combo)
{
    return _sampleCreateChoicebox(vcomboboxGetPopdownCombobox(combo));
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
	vclassSpawn(vlistitemGetDefaultClass(), sizeof(sampleChoiceboxClass));
    vclassSetObjectSize(choiceboxClas,
			sizeof(sampleChoicebox));
    vclassSetNameScribed(choiceboxClas,
			 vcharScribeLiteral("sampleChoicebox"));

    vclassSet(choiceboxClas,
	      vdialogGET_ITEM_MIN_SIZE, _sampleGetChoiceboxMinSize);

    vclassSet(choiceboxClas,
	      vlistviewGET_CONTENT_NATURAL_SIZE,
	                                _sampleGetChoiceboxContentNaturalSize);
    vclassSet(choiceboxClas,
	      vlistviewDRAW_CELL_CONTENTS, _sampleDrawChoiceboxCellContents);
    vclassSet(choiceboxClas,
	      vlistviewNOTIFY_SELECT, _sampleNotifyChoiceboxSelect);

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


/* $Id: sample4.c,v 1.14 1997/04/10 23:54:03 dimitri Exp $ */

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
 * Executable Name: sample4
 * Source Files:    sample4.c, main.c
 * Resource Files:  main.vr
 *
 * Managers Illustrated:
 *      Combobox Manager
 *
 * Description Of Sample:
 *      This demo shows how to do specialized comboboxes. 
 *      Specialized comboboxes are subclassed from comboboxes and their
 *      'entrybox', 'choicebox', and 'value' parts are entirely
 *      overriden to use vdialogLabelItem, vpalette and vcolor, respectively,
 *      instead of standard combobox's part.
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

#ifndef vpaletteINCLUDED
#include vpaletteHEADER
#endif

#ifndef vresourceINCLUDED
#include vresourceHEADER
#endif

#ifndef vstartupINCLUDED
#include vstartupHEADER
#endif

#ifndef vstdlibINCLUDED
#include vstdlibHEADER
#endif

#ifndef vstdioINCLUDED
#include vstdioHEADER
#endif

#ifndef vprefINCLUDED
#include vprefHEADER
#endif

/*****************************************************************************
 * private constants
 *****************************************************************************/

enum {
    horizontalLEFT,
    horizontalRIGHT,
    horizontalNO_MOVE,

    verticalTOP,
    verticalBOTTOM,
    verticalNO_MOVE
};

/*****************************************************************************
 * data structures
 ****************************************************************************/

typedef struct sampleValue           sampleValue;
typedef struct sampleValueClass      sampleValueClass;

typedef struct sampleEntrybox        sampleEntrybox;
typedef struct sampleEntryboxClass   sampleEntryboxClass;

typedef struct sampleChoicebox       sampleChoicebox;
typedef struct sampleChoiceboxClass  sampleChoiceboxClass;

typedef void (*sampleEntryboxNoteProc)(sampleEntrybox *entrybox,
				       vevent *event);
    
struct sampleValue {
    vcomboboxValue  value;
    vcolorSpec     *spec;
};

struct sampleValueClass {
    vcomboboxValueCLASS(sampleValueClass, sampleValue);
};

struct sampleEntrybox {
    vdialogItem     item;
    vcomboboxValue *value;
};

struct sampleEntryboxClass {
    vdialogITEM_CLASS(sampleEntryboxClass,
		      sampleEntrybox, sampleEntryboxNoteProc);
};

struct sampleChoicebox {
    vpalette      palette;
};

struct sampleChoiceboxClass {
    vpaletteCLASS(sampleChoiceboxClass, sampleChoicebox, vpaletteItem);
};

typedef struct {
    vdialog               *dialog;
    sampleEntryboxClass   *entryboxClass;
    sampleChoiceboxClass  *choiceboxClass;
    sampleValueClass      *valueClass;
    vcomboboxClass        *comboClass;
    vcomboboxPopdownClass *popdownClass;
    vcombobox             *combo;
    vcomboboxPopdown      *popdown;
    vbutton               *quitButton;
} globals;

/*****************************************************************************
 * macro
 *****************************************************************************/

#define master() ((globals *)*_master)

/*****************************************************************************
 * constants
 *****************************************************************************/

#define sampleDITHER_AREA          16
#define sampleDELTA_RGB            vcolorCOMPONENT_MAX/sampleDITHER_AREA/2

/*****************************************************************************
 * variables
 *****************************************************************************/

static void **_master = NULL;

/*****************************************************************************
 * private overrides for customized entrybox for combo boxes
 *****************************************************************************/

/*****************************************************************************
 * _sampleInitEntrybox initializes a combobox entrybox
 * entrybox -> the combobox entrybox to initialize
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
    
    entrybox->value = vcomboboxCreateValueOfClass(master()->valueClass);
}

/*****************************************************************************
 * _sampleCopyEntrybox copys a combobox entrybox
 * entrybox -> the combobox entrybox to copy
 * target <- the combobox entrybox to be copied
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
 * _sampleCopyInitEntrybox initializes and copies a combobox entrybox
 * entrybox -> the combobox entrybox to copy
 * target <- the combobox entrybox to be copied
 *****************************************************************************/
static void _sampleCopyInitEntrybox(sampleEntrybox *entrybox,
				    sampleEntrybox *target)
{
    vclassSendSuper(master()->entryboxClass,
		    vobjectCOPY_INIT, (entrybox, target));
    
    /*
     * Clone value
     */
    
    target->value = vcomboboxCloneValue(entrybox->value);
}

/*****************************************************************************
 * _sampleDestroyEntrybox destroys a combobox entrybox
 * entrybox -> the combobox entrybox to destroy
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
 * _sampleLoadInitEntrybox initializes and copies a combobox entrybox
 * entrybox -> the combobox entrybox to be initialized and loaded
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
	entrybox->value = vcomboboxCreateValueOfClass(master()->valueClass);
}

/*****************************************************************************
 * _sampleStoreEntrybox stores a combobox entrybox to resource
 * entrybox -> the combobox entrybox to store
 * resource <- resource to store combobox entrybox
 *****************************************************************************/
static void _sampleStoreEntrybox(sampleEntrybox *entrybox, vresource resource)
{
    vclassSendSuper(master()->entryboxClass,
		    vobjectSTORE, (entrybox, resource));
    
    /*
     * Stores title
     */
    
    vcomboboxStoreValue(entrybox->value, resource);
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

/*****************************************************************************
 * _sampleDrawEntrybox draws the entrybox
 * entrybox -> entrybox to draw
 *****************************************************************************/
static void _sampleDrawEntrybox(sampleEntrybox *entrybox)
{
    vcolor       *color;
    vcolorScheme  scheme;

    color = vdrawGetColor();

    vdialogDetermineItemColorSchemeState((vdialogItem *)entrybox,
					 vcolorFLAG_FOREGROUND, &scheme);
    vdrawSetColor(vcolorGetSchemeForeground(&scheme));

    vcomboboxDrawValue(entrybox->value,
		       (vrect *)vdialogGetItemRect((vdialogItem *)entrybox));

    if (vdialogItemFocusIsVisible((vdialogItem *)entrybox))
    {
	vrect rect;

	rect = *vdialogGetItemRect((vdialogItem *)entrybox);
	vrectInset(&rect, 3, 3, &rect);

	vdrawRectsStrokeInside(&rect, 1);
    }

    vdrawSetColor(color);
}

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
 * _sampleGetChoiceboxNaturalSize returns the natural size of choicebox
 * choicebox -> choicebox to get natural size
 * width <- the natural width
 * height <- the natural height
 *****************************************************************************/
static void _sampleGetChoiceboxNaturalSize(sampleChoicebox *choicebox,
					   int *width, int *height)
{
    vcombobox *combo;

    vclassSendSuper(master()->choiceboxClass,
		    vdialogGET_ITEM_NATURAL_SIZE, 
		    (choicebox, width, height));

    combo = vcomboboxGetPartCombobox((vdialogItem *)choicebox);
    if (combo)
    {
	int w, h;
    
	vcomboboxGetValueMaxSize(combo, &w, &h);
	*height = (h + 8)*vcomboboxGetVisibleValues(combo);
    }
}

/*****************************************************************************
 * private class method overrides for combobox values
 *****************************************************************************/

/*****************************************************************************
 * _sampleInitValue initializes a combobox value
 * value -> the combobox value to initialize
 *****************************************************************************/
static void _sampleInitValue(sampleValue *value)
{
    /*
     * Init itself
     */
    
    vclassSendSuper(master()->valueClass,
		    vobjectINIT, (value));
    
    /*
     * fill in the fields with default values
     */
    
    value->spec = vcolorCreateSpec();
}

/*****************************************************************************
 * _sampleCopyValue copys a combobox value
 * value -> the combobox value to copy
 * target <- the combobox value to be copied
 *****************************************************************************/
static void _sampleCopyValue(sampleValue *value, sampleValue *target)
{
    /*
     * Copy itself
     */
    
    vclassSendSuper(master()->valueClass,
		    vobjectCOPY, (value, target));
    
    /*
     * Low-level copying
     */
    
    vcolorCopySpec(value->spec, target->spec);
}

/*****************************************************************************
 * _sampleCopyInitValue initializes and copies a combobox value
 * value -> the combobox value to copy
 * target <- the combobox value to be copied
 *****************************************************************************/
static void _sampleCopyInitValue(sampleValue *value, sampleValue *target)
{
    vclassSendSuper(master()->valueClass,
		    vobjectCOPY_INIT, (value, target));
    
    /*
     * Low-level copyInit
     */
    
    target->spec = vcolorCloneSpec(value->spec);
}

/*****************************************************************************
 * _sampleDestroyValue destroys a combobox value
 * value -> the combobox value to destroy
 *****************************************************************************/
static void _sampleDestroyValue(sampleValue *value)
{
    vcolorDestroySpec(value->spec);
    
    /*
     * Destroy itself
     */
    
    vclassSendSuper(master()->valueClass,
		    vobjectDESTROY, (value));
}

/*****************************************************************************
 * _sampleLoadInitValue initializes and copies a combobox value
 * value <-> the combobox value to be initialized and loaded
 * resource -> resource to load combobox value from
 *****************************************************************************/
static void _sampleLoadInitValue(sampleValue *value, vresource resource)
{
    vresource  res;
    
    /*
     * Load itself
     */
    
    vclassSendSuper(master()->valueClass,
		    vobjectLOAD_INIT, (value, resource));
    
    if (vresourceTestGet(resource, vname_Color, &res))
	value->spec = vcolorLoadSpec(res);
    else
	value->spec = vcolorCreateSpec();
}

/*****************************************************************************
 * _sampleStoreValue stores a combobox value to resource
 * value -> the combobox value to store
 * resource <- resource to store combobox value
 *****************************************************************************/
static void _sampleStoreValue(sampleValue *value, vresource resource)
{
    vclassSendSuper(master()->valueClass,
		    vobjectSTORE, (value, resource));
    
    /*
     * Stores title
     */
    
    vcolorStoreSpec(value->spec, vresourceMake(resource, vname_Color));
}

/*****************************************************************************
 * _sampleDrawValue draws the value
 * value -> value to draw
 * rect  -> the rect to draw on
 *****************************************************************************/
static void _sampleDrawValue(sampleValue *value, vrect *rect)
{
    vcolor *color;
    vcolor *temp;
    vrect   tRect;
    
    color = vcolorInternSpec(value->spec);
    
    temp = vdrawGetColor();
    vdrawSetColor(color);
    vrectInset(rect, 2, 2, &tRect);
    vdrawRectsFill(&tRect, 1);
    vdrawSetColor(temp);
    vdrawRectsStrokeInside(&tRect, 1);
    
    vcolorRelease(color);
}

/*****************************************************************************
 * _sampleGetValueSize returns the size of the value
 * value  -> value to get size
 * width  <- the width
 * height <- the height
 *****************************************************************************/
static void _sampleGetValueSize(sampleValue *value, int *width, int *height)
{
    *width = 20;
    *height = 20;
}

/*****************************************************************************
 * private class method overrides for standard combo box
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

static vcomboboxValue *_sampleCreateComboboxValue(vcombobox *combo)
{
    vcomboboxValue *value;
    
    value = vcomboboxCreateValueOfClass(master()->valueClass);
    
    return value;
}

static int _sampleCompareComboboxValues(vcombobox *combo,
					vcomboboxValue *value1,
					vcomboboxValue *value2)
{
    vcolorSpec	 spec1;
    vcolorSpec	 spec2;
    int		 result;

    vcolorCopyInitSpec(((sampleValue *)value1)->spec, &spec1 );
    vcolorCopyInitSpec(((sampleValue *)value2)->spec, &spec2 );
    vcolorConvertSpec( &spec1, vcolorGetHLSClass() );
    vcolorConvertSpec( &spec2, vcolorGetHLSClass() );

    if ( ( result = vcolorGetSpecHLSHue( &spec2 ) -
	vcolorGetSpecHLSHue( &spec1 ) ) == 0 &&
	( result = vcolorGetSpecHLSLightness( &spec2 ) -
	 vcolorGetSpecHLSLightness( &spec1 ) ) == 0 &&
	( result = vcolorGetSpecHLSSaturation( &spec2 ) -
	 vcolorGetSpecHLSSaturation( &spec1 ) ) == 0)
	result = vcharCompareBase(vcomboboxGetValueTitle(value1),
				  vcomboboxGetValueTitle(value2));

    vcolorDestroySpec( &spec1 );
    vcolorDestroySpec( &spec2 );

    return result;
}

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
    vpaletteSetColumns(palette, 4);
    vpaletteSetImageSize(palette, 20, 20);
    
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

static void _sampleGetChoiceboxSize(vcombobox *combo,
				    int *width, int *height)
{
    vdialogGetItemNaturalSize(vcomboboxGetChoicebox(combo), width, height);
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

/*****************************************************************************
 * _sampleDetermineChoiceboxNonant determines choicebox of the direction
 *         the given row/column lives in
 *
 *        |     |         .Where (5) is the listview rectangle.  The cell
 *    (1) | (2) | (3)     .to scroll to can be any of the 9 nonants.  The
 *        |     |         .behavior for each of them is like this:
 *   -----+-----+-----    .(1) - move to top, left
 *        |     |         .(2) - keep horizontal scrolling the same and
 *    (4) | (5) | (6)     .      move to top
 *        |     |         .(3) - move to top, right
 *   -----+-----+-----    .(4) - move to left, vert scrolling same
 *        |     |         .(5) - don't move
 *    (7) | (8) | (9)     .(6) - move to right, vert scrolling same
 *        |     |         .(7) - move to bottom, left
 *                        .(8) - move to bottom, horz scrolling same
 *                        .(9) - move to bottom, right
 *
 * listview -> the listview to determine the direction
 * riw -> the cell to determine where it lives in row
 * column -> the cell to determine where it lives in column
 * horizontalMove <- one of horizontalLEFT/RIGHT/NO_MOVE as appropriate
 * verticalMove <- one of verticalTOP/BOTTOM/NO_MOVE as appropriate
 *****************************************************************************/
static void _sampleDetermineChoiceboxNonant(vlistview *listview,
					    int row, int column,
					    int *horizontalMove,
					    int *verticalMove)
{
    int    xoffset;
    int    yoffset;

    vlistviewGetDrawingOffsets(listview, &xoffset, &yoffset);

    if (row < vlistviewGetTopRow(listview))
	*verticalMove = verticalTOP;
    else if (row == vlistviewGetTopRow(listview))
    {
	if (yoffset != 0)
	    /*
	     * straddle
	     */
	    *verticalMove = verticalTOP;
	else
	    *verticalMove = verticalNO_MOVE;
    }
    else if (row >= vlistviewGetBottomRow(listview))
	*verticalMove = verticalBOTTOM;
    else
	*verticalMove = verticalNO_MOVE;

    if (column < vlistviewGetLeftColumn(listview))
	*horizontalMove = horizontalLEFT;
    else if (column == vlistviewGetLeftColumn(listview))
    {
	if (xoffset != 0)
	    /*
	     * straddle
	     */
	    *horizontalMove = horizontalLEFT;
	else 
	    *horizontalMove = horizontalNO_MOVE;
    }
    else if (column >= vlistviewGetRightColumn(listview))
	*horizontalMove = horizontalRIGHT;
    else
	*horizontalMove = horizontalNO_MOVE;
}

/*****************************************************************************
 * _sampleCalcChoiceboxHorizontalDelta determines how far to scroll
 *    the listview horizontally to scroll the given cell into view and be
 *    flush with the given side of the listview
 *
 * listview -> the listview to calc the scrolling delta for
 * row -> the row to scroll into
 * column -> the column to scroll into
 * horizontalMode -> the direction the cell should be scrolled to
 * <- how far to scroll horizontally (for passing to vlistviewScrollRelative)
 *****************************************************************************/
static int _sampleCalcChoiceboxHorizontalDelta(vlistview *listview,
					       int row, int column,
					       int horizontalMove)
{
    vrectLong     rect, cellRect;
    int           xoffset, yoffset;
    vlistsize    *sizes;
    vrect        *contentRect;
    int           delta;

    sizes = vlistviewGetSizes(listview);
    contentRect = vlistviewGetListRect(listview);

    vlistviewGetDrawingOffsets(listview, &xoffset, &yoffset);

    vlistsizeGetCellRect(sizes, row, column, &cellRect);
    vlistsizeGetCellRect(sizes, row, 
			 vlistviewGetLeftColumn(listview), &rect);
    
    switch (horizontalMove)
    {
    case horizontalLEFT:
	delta = rect.x - cellRect.x - xoffset;
	break;
	
    case horizontalRIGHT:
    {
	int distFromEdge;
	
	/*
	 * first, see how far from left edge of the list content area
	 * the cell needs to go
	 */
	
	distFromEdge = contentRect->w - cellRect.w;
	
	if (distFromEdge < 0)
	    /*
	     * cell is wider than list, so scroll it left-aligned
	     */
	    delta = rect.x - cellRect.x - xoffset;
	else
	    /*
	     * do the equivalent of scroll it left-aligned, then scroll
	     * over by distFromEdge
	     */
	    delta = rect.x - cellRect.x - xoffset + distFromEdge;
	break;
    }
    case horizontalNO_MOVE:
	delta = 0;
	break;
    }

    return delta;

}

/*****************************************************************************
 * _sampleCalcChoiceboxVerticalDelta determines how far to scroll
 *     the listview vertically to scroll the given cell into view and be
 *     flush with the given side of the listview
 *
 *  listview -> the listveiw to calc the scrolling delta for
 * row -> the row to scroll into
 * column -> the column to scroll into
 * verticalMode -> the direction the cell should be scrolled to
 * <- how far to scroll vertically (for passing to vlistviewScrollRelative)
 *****************************************************************************/
static int _sampleCalcChoiceboxVerticalDelta(vlistview *listview,
					     int row, int column,
					     int verticalMove)
{
    vrectLong     rect, cellRect;
    int           xoffset, yoffset; /* account for straddle */
    vlistsize    *sizes;
    vrect        *contentRect;
    int           delta;

    sizes = vlistviewGetSizes(listview);
    contentRect = vlistviewGetListRect(listview);

    vlistviewGetDrawingOffsets(listview, &xoffset, &yoffset);

    vlistsizeGetCellRect(sizes, row, column, &cellRect);
    vlistsizeGetCellRect(sizes, vlistviewGetTopRow(listview), column, &rect);

    switch (verticalMove)
    {
    case verticalTOP:
	delta = cellRect.y - rect.y - yoffset;
	break;
	
    case verticalBOTTOM:
    {
	int distFromEdge;
	
	/* first, see how far from left edge of the list content area
	 * the cell needs to go
	 */
	distFromEdge = contentRect->h - cellRect.h;
	
	if (distFromEdge < 0)
	    /*
	     * cell is taller than list, so scroll it top-aligned
	     */
	    delta = cellRect.y - rect.y - yoffset;
	else
	    /*
	     * do the equivalent of scroll it top-aligned, then scroll
	     * down by distFromEdge
	     */
	    delta = cellRect.y - rect.y - yoffset - distFromEdge;
	break;
    }
	
    case verticalNO_MOVE:
	delta = 0;
	break;
    }

    return delta;
    
}

/*****************************************************************************
 * _vcomoboboxScrollChoiceboxToCell scrolls choicebox such that a given cell
 *        is fully into view of the viewing area.
 * listview -> the listview to scroll
 * row -> the row to scroll into
 * column -> the column to scroll into
 *****************************************************************************/
static void _sampleScrollChoiceboxToCell(vlistview *listview,
					 int row, int column)
{
    int horizontalMove, verticalMove;
    int horizontalDelta, verticalDelta;

    /*
     * first, figure out which case we're dealing with
     */
    _sampleDetermineChoiceboxNonant(listview, row, column, &horizontalMove, &verticalMove);

    /*
     * special-case easy case
     */
    if ((horizontalMove == horizontalLEFT) && (verticalMove == verticalTOP))
	vlistviewScrollToCell(listview, row, column);
    else
    {
	horizontalDelta =
	    _sampleCalcChoiceboxHorizontalDelta(listview, row, column,
						   horizontalMove);
	verticalDelta = 
	    _sampleCalcChoiceboxVerticalDelta(listview, row, column, 
						 verticalMove);
	vlistviewScrollRelative(listview, horizontalDelta, verticalDelta);
    }
}

static void _sampleScrollChoiceboxToIndex(vcombobox *combo,
					  vdialogItem *choicebox,
					  int index)
{
    vpalette *palette;
    int       row, col;
    
    palette = (vpalette *)choicebox;
    
    if (vpaletteGetItemCount(palette) == 0 ||
	vpaletteGetItemCount(palette) <= index)
	return;
    
    if (index < 0)
	_sampleScrollChoiceboxToCell(vpaletteGetListview(palette), 0, 0);
    else
    {
	col = index % vpaletteGetColumnCount(palette);
	row = index / vpaletteGetColumnCount(palette);
	
	_sampleScrollChoiceboxToCell
	    (vpaletteGetListview(palette), row, col);
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
 * private class method overrides for popdown combo box
 *****************************************************************************/

static vdialogItem *_sampleCreatePopdownChoicebox(vcomboboxPopdown *combo)
{
    return _sampleCreateChoicebox(vcomboboxGetPopdownCombobox(combo));
}

static vdialogItem *_sampleCreatePopdownEntrybox(vcomboboxPopdown *combo)
{
    return _sampleCreateEntrybox(vcomboboxGetPopdownCombobox(combo));
}

static vcomboboxValue *_sampleCreatePopdownValue(vcomboboxPopdown *combo)
{
    return _sampleCreateComboboxValue(vcomboboxGetPopdownCombobox(combo));
}

static int _sampleComparePopdownValues(vcomboboxPopdown *combo,
				       vcomboboxValue *value1,
				       vcomboboxValue *value2)
{
    return _sampleCompareComboboxValues(vcomboboxGetPopdownCombobox(combo),
					value1, value2);
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

static void _sampleGetPopdownChoiceboxSize(vcomboboxPopdown *combo,
					   int *width, int *height)
{
    _sampleGetChoiceboxSize(vcomboboxGetPopdownCombobox(combo),
			    width, height);
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

static void _sampleSetupEntryboxClass(void)
{
    sampleEntryboxClass *entryboxClas;
    
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

static void _sampleSetupChoiceboxClass(void)
{
    sampleChoiceboxClass *choiceboxClas;
    
    /*
     * Create a new choicebox class for combo boxes
     */
    
    choiceboxClas = (sampleChoiceboxClass *)
	vclassSpawn(vpaletteGetDefaultClass(), sizeof(sampleChoiceboxClass));
    vclassSetObjectSize(choiceboxClas,
			sizeof(sampleChoicebox));
    vclassSetNameScribed(choiceboxClas,
			 vcharScribeLiteral("sampleChoicebox"));
    
    vclassSet(choiceboxClas,
	      vdialogGET_ITEM_MIN_SIZE, _sampleGetChoiceboxMinSize);
    vclassSet(choiceboxClas,
	      vdialogGET_ITEM_NATURAL_SIZE, _sampleGetChoiceboxNaturalSize);

    master()->choiceboxClass = choiceboxClas;
}

static void _sampleSetupValueClass(void)
{
    sampleValueClass *valueClas;

    /*
     * Create a new combobox value class
     */
    
    valueClas = (sampleValueClass *)
	vclassSpawn(vcomboboxGetDefaultValueClass(), sizeof(vcomboboxValueClass));
    vclassSetObjectSize(valueClas,
			sizeof(sampleValue));
    vclassSetNameScribed(valueClas,
			 vcharScribeLiteral("sampleValue"));
    
    vclassSet(valueClas,
	      vobjectDESTROY, _sampleDestroyValue);
    vclassSet(valueClas,
	      vobjectINIT, _sampleInitValue);
    vclassSet(valueClas,
	      vobjectCOPY, _sampleCopyValue);
    vclassSet(valueClas,
	      vobjectCOPY_INIT, _sampleCopyInitValue);
    vclassSet(valueClas,
	      vobjectLOAD_INIT, _sampleLoadInitValue);
    vclassSet(valueClas,
	      vobjectSTORE, _sampleStoreValue);
    
    vclassSet(valueClas,
	      vcomboboxValueDRAW, _sampleDrawValue);
    vclassSet(valueClas,
	      vcomboboxValueGET_SIZE, _sampleGetValueSize);
    
    master()->valueClass = valueClas;
}

static void _sampleSetupComboboxClass(void)
{
    vcomboboxClass *comboClas;

    /*
     * Create a new standard combo box class
     */
    
    comboClas = (vcomboboxClass *)
	vclassReproduce(vcomboboxGetDefaultClass());
    vclassSetNameScribed(comboClas,
			 vcharScribeLiteral("sampleCombobox"));
    vclassSet(comboClas,
	      vcomboboxAPPEND_CHOICEBOX_VALUE, _sampleAppendChoiceboxValue);
    vclassSet(comboClas,
	      vcomboboxCOMPARE_VALUES, _sampleCompareComboboxValues);
    vclassSet(comboClas,
	      vcomboboxCREATE_CHOICEBOX, _sampleCreateChoicebox);
    vclassSet(comboClas,
	      vcomboboxCREATE_ENTRYBOX, _sampleCreateEntrybox);
    vclassSet(comboClas,
	      vcomboboxCREATE_VALUE, _sampleCreateComboboxValue);
    vclassSet(comboClas,
	      vcomboboxDELETE_CHOICEBOX_VALUE_AT, _sampleDeleteChoiceboxValueAt);
    vclassSet(comboClas,
	      vcomboboxGET_CHOICEBOX_SELECTED_INDEX, _sampleGetChoiceboxSelectedIndex);
    vclassSet(comboClas,
	      vcomboboxGET_CHOICEBOX_SIZE, _sampleGetChoiceboxSize);
    vclassSet(comboClas,
	      vcomboboxGET_ENTRYBOX_SIZE, _sampleGetEntryboxSize);
    vclassSet(comboClas,
	      vcomboboxGET_ENTRYBOX_VALUE, _sampleGetEntryboxValue);
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
     * Create a new popdown combo box class
     */
    
    popdownClas = (vcomboboxPopdownClass *)
	vclassReproduce(vcomboboxGetDefaultPopdownClass());
    vclassSetNameScribed(popdownClas,
			 vcharScribeLiteral("samplePopdown"));
    vclassSet(popdownClas,
	      vcomboboxAPPEND_CHOICEBOX_VALUE, _sampleAppendPopdownChoiceboxValue);
    vclassSet(popdownClas,
	      vcomboboxCOMPARE_VALUES, _sampleComparePopdownValues);
    vclassSet(popdownClas,
	      vcomboboxCREATE_CHOICEBOX, _sampleCreatePopdownChoicebox);
    vclassSet(popdownClas,
	      vcomboboxCREATE_ENTRYBOX, _sampleCreatePopdownEntrybox);
    vclassSet(popdownClas,
	      vcomboboxCREATE_VALUE, _sampleCreatePopdownValue);
    vclassSet(popdownClas,
	      vcomboboxDELETE_CHOICEBOX_VALUE_AT, _sampleDeletePopdownChoiceboxValueAt);
    vclassSet(popdownClas,
	      vcomboboxGET_CHOICEBOX_SELECTED_INDEX, _sampleGetPopdownChoiceboxSelectedIndex);
    vclassSet(popdownClas,
	      vcomboboxGET_CHOICEBOX_SIZE, _sampleGetPopdownChoiceboxSize);
    vclassSet(popdownClas,
	      vcomboboxGET_ENTRYBOX_SIZE, _sampleGetPopdownEntryboxSize);
    vclassSet(popdownClas,
	      vcomboboxGET_ENTRYBOX_VALUE, _sampleGetPopdownEntryboxValue);
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
    vclassSet(popdownClas,
	      vcomboboxSET_ENTRYBOX_MODIFYABLE, _sampleSetPopdownEntryboxModifyable);
    vclassSet(popdownClas,
	      vcomboboxSET_ENTRYBOX_VALUE, _sampleSetPopdownEntryboxValue);
    
    master()->popdownClass = popdownClas;
}

static void _sampleNotifyCombobox(vcombobox *combo, vevent *event, int message)
{
    int          index;
    sampleValue *value;
    vbutton     *button;
    vcolor      *color;

    if (message != vcomboboxNOTIFY_SELECT && message != vcomboboxNOTIFY_ACCEPT)
	return;
    
    button = (vbutton *)vcomboboxGetData(combo);
    index = vcomboboxGetSelectedIndex(combo);
    if (index >= 0)
    {
	value = (sampleValue *)vcomboboxGetValueAt(combo, index);
	color = vcolorInternSpec(value->spec);
	vdialogSetItemForeground(vbuttonGetItem(button), color);
    }
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
	_sampleSetupChoiceboxClass();
	_sampleSetupValueClass();
	_sampleSetupComboboxClass();
	_sampleSetupPopdownClass();
    }
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
    vprefDict          *dict;
    vprefIterator      iterator;
    vresource          res;
    sampleValue       *value;
    
    dict = vprefGetRootDict();
    dict = vprefDictLoadDictScribed(dict, 
				    vcharScribeLiteral("namedcolordict"));
    vprefDictInitIterator(&iterator, dict);
    while (vprefNextIterator(&iterator))
    {
	value = (sampleValue*)vcomboboxCreateValueOfClass(master()->valueClass);
	res = vprefGetIteratorResource(&iterator);
	vcolorDestroySpec(value->spec);
	vcomboboxSetValueTitle((vcomboboxValue *)value,
			       vprefGetIteratorKey(&iterator));

	value->spec = vcolorLoadSpec(res);
	vcolorSetSpecDeltaRGB(value->spec, sampleDELTA_RGB,
			      sampleDELTA_RGB, sampleDELTA_RGB);
	vcolorSetSpecMaxDitherDotArea(value->spec, sampleDITHER_AREA);

	vcomboboxAppendValue(combo, (vcomboboxValue *)value);
    }
    
    vprefDestroyIterator(&iterator);
    vprefDictRelease(dict);

    vcomboboxSelectValueAt(combo, 0);

    vcomboboxSetNotify(combo, _sampleNotifyCombobox);
}











/* $Id: sample3.c,v 1.11 1997/04/10 23:54:03 dimitri Exp $ */

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
 * Executable Name: sample3
 * Source Files:    sample3.c, main.c
 * Resource Files:  main.vr
 *
 * Managers Illustrated:
 *      Combobox Manager
 *
 * Description Of Sample:
 *      This demo shows how to do specialized comboboxes. 
 *      Specialized comboboxes are subclassed from comboboxes and their
 *      values are entirely overriden to use vcolor, instead of standard
 *      value.
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

#ifndef vprefINCLUDED
#include vprefHEADER
#endif

/*****************************************************************************
 * data structures
 *****************************************************************************/

typedef struct sampleValue        sampleValue;
typedef struct sampleValueClass   sampleValueClass;

struct sampleValue {
    vcomboboxValue value;
    vcolorSpec    *spec;
};

struct sampleValueClass {
    vcomboboxValueCLASS(sampleValueClass, sampleValue);
};

typedef struct {
    sampleValueClass      *valueClass;
    vcomboboxClass        *comboClass;
    vcomboboxPopdownClass *popdownClass;
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
 * resource -> the resource to load combobox value from
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
    vdrawRectsStrokeInside(rect, 1);
    
    vcolorRelease(color);
    
    vdrawRectShowCenterY
	(vcomboboxGetValueTitle((vcomboboxValue *)value), &tRect);
}

/*****************************************************************************
 * _sampleGetValueSize returns the size of the value
 * value  -> value to get size
 * width  <- the width
 * height <- the height
 *****************************************************************************/
static void _sampleGetValueSize(sampleValue *value, int *width, int *height)
{
    vcombobox *combo;
    
    /*
     * add in the width of the title and max with its height
     */
    
    combo = vcomboboxGetValueCombobox((vcomboboxValue *)value);
    if (combo)
    {
	vfont *font;
	
	font = vdialogDetermineItemFont(vcomboboxGetItem(combo));
	
	*width = vfontStringWidthX
	    (font, vcomboboxGetValueTitle((vcomboboxValue *)value));
	*height = vfontHeight(font);
    }
    else
    {
	*width = 80;
	*height = 16;
    }
    
    *width += 4;
    *height += 4;
}

/*****************************************************************************
 * private class method overrides for standard combobox box
 *****************************************************************************/

static vcomboboxValue *_sampleCreateComboboxValue(vcombobox *combo)
{
    vcomboboxValue *value;
    
    value = vcomboboxCreateValueOfClass(master()->valueClass);
    
    return value;
}

/*****************************************************************************
 * private class method overrides for popdown combobox box
 *****************************************************************************/

static vcomboboxValue *_sampleCreatePopdownValue(vcomboboxPopdown *combo)
{
    return _sampleCreateComboboxValue(vcomboboxGetPopdownCombobox(combo));
}



static void _sampleSetupValueClass(void)
{
    sampleValueClass      *valueClas;
    
    /*
     * Create a new combobox value class
     */
    
    valueClas = (sampleValueClass *)
	vclassSpawn(vcomboboxGetDefaultValueClass(),
		    sizeof(sampleValueClass));
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
     * Create a new standard combobox box class
     */
    
    comboClas = (vcomboboxClass *)vclassReproduce(vcomboboxGetDefaultClass());
    vclassSetNameScribed(comboClas,
			 vcharScribeLiteral("sampleCombobox"));
    vclassSet(comboClas,
	      vcomboboxCREATE_VALUE, _sampleCreateComboboxValue);
    
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
	      vcomboboxCREATE_VALUE, _sampleCreatePopdownValue);
    
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

	_sampleSetupValueClass();
	_sampleSetupComboboxClass();
	_sampleSetupPopdownClass();
    }
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


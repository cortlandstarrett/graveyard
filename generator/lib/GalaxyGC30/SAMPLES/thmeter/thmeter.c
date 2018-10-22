/* $Id: thmeter.c,v 1.4 1995/07/12 19:42:43 lis Exp $ */
/* thermometer.c -- a simple read-only control that mimics a thermometer
 *		    (two different colored regions indicating division
 *		    of a whole.)
 *
 * This implements a subclass called "thermoMeter."  It uses the dialog
 * item settings (foreground and background color, item menu.) to let
 * clients customize the control without having to use code.  The
 * "vertical" setting determines whether the control displays the dividing
 * line between the two colors as horizontal or vertical.
 *
 * This also includes a small driver program (that hooks up a slider that
 * controls the thermometer's value) and a quit button.
 */

#include <vgalaxy.h>


#define TAG(s) vnameInternGlobalLiteral((s))


/* -=-=-=-=- */



/* These are a useful idiom for doing the Right Thing with respect to
 * colors.  Let the clients set the colors in vre, and use 
 * vdialogDetermineItemColors() calculate the proper shadow values.
 * This subclass doesn't use all of these.
 */

enum {
    colorFOREGROUND = 0,
    colorBACKGROUND,
    colorSHADOW_TOP,
    colorSHADOW_BOTTOM,
    colorFOCUS,
    colorBACKGROUND_DEBOSS,
    colorNUM_COLORS /* must be last one */
};

static int	colorIDs[colorNUM_COLORS] = {
    vdrawCOLOR_FOREGROUND, 
    vdrawCOLOR_BACKGROUND, 
    vdrawCOLOR_SHADOW_TOP, 
    vdrawCOLOR_SHADOW_BOTTOM,
    vdrawCOLOR_FOCUS,
    vdrawCOLOR_BACKGROUND_DEBOSS
};

static int 	disableColorIDs[colorNUM_COLORS] = {
    vdrawCOLOR_FOREGROUND        | vdrawCOLOR_DISABLE,
    vdrawCOLOR_BACKGROUND        | vdrawCOLOR_DISABLE,
    vdrawCOLOR_SHADOW_TOP        | vdrawCOLOR_DISABLE,
    vdrawCOLOR_SHADOW_BOTTOM     | vdrawCOLOR_DISABLE,
    vdrawCOLOR_FOCUS             | vdrawCOLOR_DISABLE,
    vdrawCOLOR_BACKGROUND_DEBOSS | vdrawCOLOR_DISABLE
};


/* _spamDrawThermoMeter -- override of vdialogDRAW_ITEM that draws
 * 			   thermometer contents.
 *
 *  -> thermoMeter -- the thermometer to draw.
 */
static void _spamDrawThermoMeter (vcontrol *thermoMeter)
{
    vcolor	*colors[colorNUM_COLORS];
    vdialogItem *item = vcontrolGetItem (thermoMeter);
    vrect	 backRect, foreRect;
    double	 mangulation;

    /* get the proper colors to draw with */
    vdialogDetermineItemColors (item,
				vdialogItemIsEnabled (item)
				? colorIDs : disableColorIDs,
				colorNUM_COLORS, colors);

    /* snarf copy of bounds rect */
    foreRect = *vdialogGetItemRect (item);

    if (vdialogItemHasBorder (item)) {
	vdrawRectsHiliteStrokeInside (&foreRect, 1,
				      colors[colorSHADOW_BOTTOM],
				      colors[colorSHADOW_TOP]);
	vrectInset (&foreRect,
		    vdialogDetermineItemLineWidth(item),
		    vdialogDetermineItemLineWidth(item),
		    &foreRect);
    }

    backRect = foreRect;
    
    /* draw thermoMeter value */
    
    mangulation = ((double)vcontrolGetValue (thermoMeter)
		   / (double)(vcontrolGetMax (thermoMeter) 
			      - vcontrolGetMin (thermoMeter)));

    /* adjust foreground color and background color rects so 
     * they don't overlap */
    if (vcontrolIsVertical (thermoMeter)) {
	foreRect.h *= mangulation;
	backRect.h -= foreRect.h;
	backRect.y += foreRect.h;
    } else {
	foreRect.w *= mangulation;
	backRect.w -= foreRect.w;
	backRect.x += foreRect.w;
    }


    /* and now actually draw it */
    {
	vcolor	*saveColor;

	saveColor = vdrawGetColor();
	
	vdrawSetColor (colors[colorFOREGROUND]);
	
	vdrawRectsFill (&foreRect, 1);
	
	vdrawSetColor (colors[colorBACKGROUND]);
	
	vdrawRectsFill (&backRect, 1);
	
	vdrawSetColor (saveColor);
    }

} /* _spamDrawThermoMeter */


/* this is the pointer to the class we create. */
static vcontrolClass	*thermoMeterClass = NULL;



/* _spamThermoMeterButtonDowner -- override of vdialogHANDLE_ITEM_BUTTON_DOWN.
 *			Since this thing is read-only, ignore mouse-downs.
 *			We do need to handle the case where the client
 *			attached a menu in vre and the user clicked with
 *			the menu button -- so pass that along to the
 *			superclass if this happens.
 *
 *  -> thermoMeter -- the thermometer clicked in
 *  -> event	   -- the event that happened.
 */
static int _spamThermoMeterButtonDowner (vcontrol *thermoMeter,
					  vevent   *event)
{
    /* suck up the mouse downs */

    if (veventGetBinding(event) == vname_Menu) {

	/* pick up any menu attached to the dialog item */
	return(vclassSendSuper (thermoMeterClass,
				vdialogHANDLE_ITEM_BUTTON_DOWN,
				(thermoMeter, event)));

    } else {
	return (TRUE);
    }
} /* _spamThermoMeterButtonDowner */





/* _spamSetupThermoMeterClass -- This subclasses the vcontrol, sets up
 *			our thermometer specific methods, and registers
 *			the class with the class manager.
 *
 * SideEffects: registeres class "thermoMeterClass" with the class manager
 */
static void _spamSetupThermoMeterClass (void)
{
    if (thermoMeterClass == NULL) {
	
	thermoMeterClass = vclassReproduce (vcontrolGetDefaultClass());
	vclassSetNameScribed (thermoMeterClass,
			      vcharScribeLiteral ("thermoMeterClass"));

	vclassSet (thermoMeterClass, vdialogDRAW_ITEM, _spamDrawThermoMeter);
	vclassSet (thermoMeterClass, vdialogHANDLE_ITEM_BUTTON_DOWN,
		   _spamThermoMeterButtonDowner);
    }
} /* _spamSetupThermoMeterClass */
    


/* _spamShutdownThermoMeterClass -- cleans up after the thermometer class.
 *
 * SideEffects: since the class is destroyed, further use of objects
 * created from this class, or loading a dialog containing dialog items
 * of this class will generate exceptions.
 */
static void _spamShutdownThermoMeterClass (void)
{
    if (thermoMeterClass != NULL) {
	vclassDestroy (thermoMeterClass);
    }
} /* _spamShutdownThermoMeterClass */



/* -=-=-=-=-=- */



/* sliderNotify -- fiddling this changes the thermometer value.
 *
 *  -> control 	-- the slider clicked on
 *  -> event	-- the event that happened.
 *
 * SideEffects -- changes the value of the thermometer.  (The thermometer
 * has a pointer to it stored in the slider's data field.
 */
static void sliderNotify (vcontrol *control, vevent *event)
{
    vcontrol	*thermoMeter = (vcontrol*)vcontrolGetData (control);

    vcontrolSetValue (thermoMeter,vcontrolGetValue(control));

} /* sliderNotify */



/* quitNotify -- quits the program.
 *
 *  -> button -- the pushbutton clicked on.
 *  -> event  -- the event that happened.
 *
 * SideEffects -- none, except that the event loop stops, which will
 * most likely cause the program to quit.
 */
static void quitNotify (vbutton *button, vevent *event)
{
    veventStopProcessing ();
} /* quitNotify */



/* -=-=-=-=-=- */



/*********
 *  dialogNotify()
 *
 *  -> dialog -- the dialog receiving notification
 *  -> event  -- the event that happened.
 *
 * SideEffects -- none, except that the event loop stops, which will
 * most likely cause the program to quit.
 *
 *  The dialog notification procedure gets called whenever any 
 *  major event applies to the dialog as a whole.  We need to
 *  look for the event which tells us that the dialog has
 *  closed.
 *
 **********/
static void dialogNotify (vdialog *dialog, vevent *event)
{
  int      et;

  et = veventGetType (event);
  
  if (et == veventWINDOW_STATE && veventIsClose (event))
    veventStopProcessing ();

} /* dialogNotify */




/* main -- the main functional dude.
 *
 *  -> argc -- command line argument count
 *  -> argv -- vector of command line arguments.
 * <-       -- EXIT_SUCCESS if everyting is happy, EXIT_FAILURE otherwise.
 */
int main (int argc, char *argv[])
{
    vresource	appres, dlogres;
    vdialog    *dialog;
    vbutton    *button;
    vcontrol   *slider, *meter;

    /* startup the world */
    vstartup (argc, argv);

    /* create and register the thermometer class before the dialog is
     * loaded. */
    _spamSetupThermoMeterClass ();

    /* get the dialog */
    appres = vapplicationGetResources (vapplicationGetCurrent());
    dlogres = vresourceGet (appres, TAG("Dialog"));
    dialog = vdialogLoad (dlogres);
    vdialogSetNotify (dialog, dialogNotify);

    /* get the slider, set its notify, and stash a pointer to the 
     * thermometer into the slider's data field so the slider notify can
     * modify the thermometer's value.
     */
    slider = (vcontrol*)vdialogFindItem (dialog, TAG("thermoSlider"));
    vcontrolSetNotify (slider, sliderNotify);

    meter = (vcontrol*)vdialogFindItem (dialog, TAG("thermoMeter"));
    vcontrolSetData (slider, meter);

    button = (vbutton*)vdialogFindItem (dialog, TAG("quittoMeter"));
    vbuttonSetNotify (button, quitNotify);

    /* show the dialog */
    vdialogOpen (dialog);

    /* fire up the user interface. */
    veventProcess ();

    /* clean up after the dialog */
    vdialogDestroy (dialog);

    /* clean up after the class. */
    _spamShutdownThermoMeterClass ();

    /* tell the world we're done. */
    exit (EXIT_SUCCESS);
    return (EXIT_FAILURE);

} /* main */



/*
 * Formatting information for emacs in c-mode
 *
 * Local Variables:
 * c-indent-level:4
 * c-continued-statement-offset:0
 * c-brace-offset:0
 * c-brace-imaginary-offset:0
 * c-argdecl-indent:0
 * c-label-offset:0
 * End:
 */


/* $Id: demo.c,v 1.3 1994/12/21 16:12:47 markd Exp $ */

/* demo.c -- run the mtext object through its paces.
 */

#include <vport.h>

#ifndef vstdlibINCLUDED
#include vstdlibHEADER
#endif

#ifndef vapplicationINCLUDED
#include vapplicationHEADER
#endif

#ifndef vfontchsrINCLUDED
#include vfontchsrHEADER
#endif

#ifndef vcolorchsrINCLUDED
#include vcolorchsrHEADER
#endif

#ifndef vmenubarINCLUDED
#include vmenubarHEADER
#endif

/* bring in the mtext interface
 */
#include "mtext.h"


/* handy macro for generating vnames from literal strings
 */
#define TAG(s)	vnameInternGlobalLiteral((s))


/* forward reference - installs a command space into the given dialog.
 * this particular sample installs the same set of commands into every
 * dialog for simplicity.
 */
static void _setupCommands (vdialog *dialog);




/* _arrange -- this forces a dialog to rearrange to pick up user changes in
 *	       the natural separation demo.
 *
 *  -> dialog -- the dialog to arrange
 */
static void _arrange (vdialog *dialog)
{
    vrect rect;
    vdialogItem *item;

    rect = *vwindowGetRect (vdialogGetWindow(dialog));
    rect.x = rect.y = 0;

    item = vdialogFindItem (dialog, TAG("AttributeTarget"));

    /* this is necessary because the dialog manager doesn't erase the
     * out-of-the-border focus cursor properly for us.
     */
    if (item != NULL) {
	vrect rect;
	rect = *vdialogGetItemRect(item);
	vrectInset (&rect,
		    - vclassGet (vdialogGetItemClass(item),
				 vdialogITEM_FOCUS_EXTRA),
		    - vclassGet (vdialogGetItemClass(item),
				 vdialogITEM_FOCUS_EXTRA),
		    &rect);
	vdialogInvalItemRect (item, &rect, 0);
    }

    vdialogArrange (dialog, &rect);

} /* _arrange */




/* a subclass of mtext called "natSepMText" follows here.  This changes the
 * natural separation values to show how they work.
 */


/* pointer to our subclass
 */
mtextClass *natsepClass;


/* globals that control the natural separation.  These will be returned in
 * an override of vdialogGetItemNaturalSeparation
 */
static int g_rightToRight = 5;
static int g_leftToLeft = 5;
static int g_bottomToTop = 5;
static int g_topToBottom = 5;



/* _natsepGetItemNaturalSeparation -- return the amount of space a natural
 *      			      strut originating from this item should
 *				      be.
 *
 *  -> text        -- the text to determine the separation for
 *  -> to          -- the dialog item connected to.  can be NULL for connecting
 *		      to the dialog/container border
 *  -> wickedWitch -- a connection constant
 * <-              -- the size this strut should be
 *
 * The conenction constant is one of these:
 *   vspringLEFT_TO_LEFT_SEPARATION     -- left of text to left side of 'to'
 *   vspringLEFT_TO_RIGHT_SEPARATION    -- left of text to right side of 'to'
 *   vspringRIGHT_TO_LEFT_SEPARATION    -- right of text to left side of 'to'
 *   vspringRIGHT_TO_RIGHT_SEPARATION   -- right of text to right side of 'to'
 *   vspringBOTTOM_TO_BOTTOM_SEPARATION -- bottom of text to bot side of 'to'
 *   vspringBOTTOM_TO_TOP_SEPARATION    -- bottom of text to top side of 'to'
 *   vspringTOP_TO_BOTTOM_SEPARATION    -- I think you get the idea
 *   vspringTOP_TO_TOP_SEPARATION       -- of what's going on here.
 *
 * more elaboration can be found in the ditem.c of this sample
 */
static int _natsepGetItemNaturalSeparation (mtext *text, vdialogItem *item,
					    unsigned int which)
{
    int ret;

    switch (which) {
	case vspringRIGHT_TO_RIGHT_SEPARATION: {
	    ret = g_rightToRight;
	    break;
	}
	case vspringLEFT_TO_LEFT_SEPARATION: {
	    ret = g_leftToLeft;
	    break;
	}
	case vspringBOTTOM_TO_TOP_SEPARATION: {
	    ret = g_bottomToTop;
	    break;
	}
	case vspringTOP_TO_BOTTOM_SEPARATION: {
	    ret = g_topToBottom;
	    break;
	}
	default: {
	    ret = 7;
	}
    }

    return (ret);

} /* _natsepGetItemNaturalSeparation */



/* _natsepSetItemRect -- set the item rect of the natural separation subclass
 *			 of mtext.
 *
 *  -> text -- the mtext to change the item rect for
 *  -> rect -- the rectangle to set it to.
 *
 * vdialogITEM_FOCUS_EXTRA doesn't work very well yet - changing the
 * item rectangle doesn't inval the focus_extra pad.  Here is taken a
 * very heavy-handed approach - inval the entire previous location.
 */
static void _natsepSetItemRect (mtext *text, const vrect *rect)
{
    vrect nuRect;
    nuRect = *vdialogGetItemRect (mtextGetItem(text));

    vrectInset (&nuRect,
		- vclassGet (mtextGetClass(text), vdialogITEM_FOCUS_EXTRA),
		- vclassGet (mtextGetClass(text), vdialogITEM_FOCUS_EXTRA),
		&nuRect);

    vdialogInvalItemRect (mtextGetItem(text), &nuRect, 0);

    vclassSendSuper (natsepClass, vdialogSET_ITEM_RECT, (text, rect));

} /* _natsepSetItemRect */



/* natsepGetDefaultClass -- return the class pointer for our natural-separation
 * 			    controlled mtext subclass
 *
 * <- -- a pointer to our new class.
 */
mtextClass *natsepGetDefaultClass (void)
{
    if (natsepClass == NULL) {
	natsepClass = vclassReproduce (mtextGetDefaultClass());
	vclassSetNameScribed (natsepClass, vcharScribeLiteral("natSepMText"));

	vclassSet (natsepClass,
		   vdialogGET_ITEM_NATURAL_SEPARATION,
		   _natsepGetItemNaturalSeparation);
	
	vclassSet (natsepClass, /* work around a vdialog limitation */
		   vdialogSET_ITEM_RECT,
		   _natsepSetItemRect);
    }

    return (natsepClass);

} /* natsepGetDefaultClass */




/* _rightToRightIssue -- handle the twiddiling of a slider that controls the
 *			 amount of space to leave between the right side of
 *			 our text object and a connection to the right side
 *			 of another object
 * 
 *  -> command -- the command that's being issued right now
 *  -> context -- the context in which this command is being issued
 * <-          -- TRUE if we handled it, FALSE if we didn't
 */
static int _rightToRightIssue (vcommandFunction *command, vdict *context)
{
    int value = *((int*)vdictLoad (context, vname_Value));

    g_rightToRight = value;

    _arrange ((vdialog*)vdictLoad (context, vname_Dialog));

    return (TRUE);

} /* _rightToRightIssue */



/* _leftToLeftIssue -- handle the twiddiling of a slider that controls the
 *			 amount of space to leave between the left side of
 *			 our text object and a connection to the left side
 *			 of another object
 * 
 *  -> command -- the command that's being issued right now
 *  -> context -- the context in which this command is being issued
 * <-          -- TRUE if we handled it, FALSE if we didn't
 */
static int _leftToLeftIssue (vcommandFunction *command, vdict *context)
{
    int value = *((int*)vdictLoad (context, vname_Value));

    g_leftToLeft = value;

    _arrange ((vdialog*)vdictLoad (context, vname_Dialog));

    return (TRUE);

} /* _leftToLeftIssue */



/* _bottomToTopIssue -- handle the twiddiling of a slider that controls the
 *			 amount of space to leave between the bottom side of
 *			 our text object and a connection to the top side
 *			 of another object
 * 
 *  -> command -- the command that's being issued right now
 *  -> context -- the context in which this command is being issued
 * <-          -- TRUE if we handled it, FALSE if we didn't
 */
static int _bottomToTopIssue (vcommandFunction *command, vdict *context)
{
    int value = *((int*)vdictLoad (context, vname_Value));

    g_bottomToTop = value;

    _arrange ((vdialog*)vdictLoad (context, vname_Dialog));

    return (TRUE);

} /* _bottomToTopIssue */



/* _topToBottomIssue -- handle the twiddiling of a slider that controls the
 *			 amount of space to leave between the top side of
 *			 our text object and a connection to the bottom side
 *			 of another object
 * 
 *  -> command -- the command that's being issued right now
 *  -> context -- the context in which this command is being issued
 * <-          -- TRUE if we handled it, FALSE if we didn't
 */
static int _topToBottomIssue (vcommandFunction *command, vdict *context)
{
    int value = *((int*)vdictLoad (context, vname_Value));

    g_topToBottom = value;

    _arrange ((vdialog*)vdictLoad (context, vname_Dialog));

    return (TRUE);

} /* _topToBottomIssue */




/*
 * ----- command implementation
 */


/* _naturalSizeIssue -- open the natural size demo dialog
 *
 *  -> command -- the command that's being issued right now
 *  -> context -- the context in which this command is being issued
 * <-          -- TRUE if we handled it, FALSE if we didn't
 */
static int _naturalSizeIssue (vcommandFunction *command, vdict *context)
{
    vresource appres, dialogres;
    vdialog *dialog;

    appres = vapplicationGetResources (vapplicationGetCurrent());
    dialogres = vresourceGet (appres, TAG("Natural Size"));

    dialog = vdialogLoad (dialogres);

    _setupCommands (dialog);

    vdialogOpen (dialog);

    return (TRUE);

} /* _naturalSizeIssue */




/* _naturalSizeIssue -- open the natural separation demo dialog
 *
 *  -> command -- the command that's being issued right now
 *  -> context -- the context in which this command is being issued
 * <-          -- TRUE if we handled it, FALSE if we didn't
 */
static int _naturalSeparationIssue (vcommandFunction *command, vdict *context)
{
    vresource appres, dialogres;
    vdialog *dialog;

    appres = vapplicationGetResources (vapplicationGetCurrent());
    dialogres = vresourceGet (appres, TAG("Natural Separation"));

    dialog = vdialogLoad (dialogres);

    _setupCommands (dialog);

    vdialogOpen (dialog);

    return (TRUE);

} /* _naturalSepeartionIssue */




/* _naturalSizeIssue -- open the attribute demo dialog
 *
 *  -> command -- the command that's being issued right now
 *  -> context -- the context in which this command is being issued
 * <-          -- TRUE if we handled it, FALSE if we didn't
 */
static int _attributeIssue (vcommandFunction *command, vdict *context)
{
    vresource appres, dialogres;
    vdialog *dialog;

    appres = vapplicationGetResources (vapplicationGetCurrent());
    dialogres = vresourceGet (appres, TAG("Attribute"));

    dialog = vdialogLoad (dialogres);

    _setupCommands (dialog);

    vdialogOpen (dialog);

    return (TRUE);

} /* _AttributeIssue */




/* _naturalSizeIssue -- open the mtext-in-a-container dialog
 *
 *  -> command -- the command that's being issued right now
 *  -> context -- the context in which this command is being issued
 * <-          -- TRUE if we handled it, FALSE if we didn't
 */
static int _containerIssue (vcommandFunction *command, vdict *context)
{
    vresource appres, dialogres;
    vdialog *dialog;

    appres = vapplicationGetResources (vapplicationGetCurrent());
    dialogres = vresourceGet (appres, TAG("Container"));

    dialog = vdialogLoad (dialogres);

    _setupCommands (dialog);

    vdialogOpen (dialog);

    return (TRUE);

} /* _containerIssue */




/* _setFontApply -- apply hook for the font chooser.  It sets the font onto
 * 		    what ever item was put into the the chizler's data pointer.
 *
 *  -> chizler -- the font chooser
 *  -> font    -- the font that was chizled.
 * <-          -- TRUE if it's OK to close the window, FALSE if it's not
 */
static int _setFontApply (vfontchsr *chizler, vfont *font)
{
    vdialogItem *item = (vdialogItem*)vfontchsrGetData(chizler);

    if (item != NULL) {
	vdialogSetItemFont (item, font);
    }

    return (TRUE);

} /* _setFontApply */




/* _setFontIssue -- open a font chizler and have it control the font of a
 *                  given minitext.
 *
 *  -> command -- the command that's being issued right now
 *  -> context -- the context in which this command is being issued
 * <-          -- TRUE if we handled it, FALSE if we didn't
 */
static int _setFontIssue (vcommandFunction *command, vdict *context)
{
    static vfontchsr *chizler = NULL;
    vdialogItem *item;

    if (chizler == NULL) {
	chizler = vfontchsrCreate ();
	vfontchsrSetApply (chizler, _setFontApply);
    }

    item = vdialogFindItem ((vdialog*)vdictLoad(context, vname_Dialog),
			    TAG("AttributeTarget"));
    vfontchsrSetData (chizler, item);

    if (item != NULL) {
	vfontchsrSetFont (chizler, vdialogDetermineItemFont(item));
    }

    vfontchsrOpen (chizler);

    return (TRUE);

} /* _setFontIssue */



/* _setForeColorApply -- apply hook for the color chizler.  It set the color
 *			 onto the foreground of the given dialog item that's
 *			 been up into the chizler's data pointer
 *
 *  -> chizler -- the color chooser 
 *  -> color   -- the color that was chizled
 */
static void _setForeColorApply (vcolorchsr *chizler, vcolor *color)
{
    vdialogItem *item = (vdialogItem*)vcolorchsrGetData(chizler);

    if (item != NULL) {
	vdialogSetItemForeground (item, color);
    }

} /* _setForeColorApply */



/* _setForeColorIsssue -- set the foreground color for a minitext.
 *
 *  -> command -- the command that's being issued right now
 *  -> context -- the context in which this command is being issued
 * <-          -- TRUE if we handled it, FALSE if we didn't
 */
static int _setForeColorIssue (vcommandFunction *command, vdict *context)
{
    static vcolorchsr *chizler = NULL;
    vdialogItem *item;

    if (chizler == NULL) {
	chizler = vcolorchsrCreate ();
	vcolorchsrSetApply (chizler, _setForeColorApply);
    }

    item = vdialogFindItem ((vdialog*)vdictLoad(context, vname_Dialog),
			    TAG("AttributeTarget"));
    vcolorchsrSetData (chizler, item);

    if (item != NULL) {
	vcolorchsrSetColor (chizler, vdialogDetermineItemForeground(item));
    }

    vcolorchsrOpen (chizler);

    return (TRUE);

} /* _setForeColorIssue */




/* _setForeColorApply -- apply hook for the color chizler.  It set the color
 *			 onto the foreground of the given dialog item that's
 *			 been up into the chizler's data pointer
 *
 *  -> chizler -- the color chooser 
 *  -> color   -- the color that was chizled
 */
static void _setBackColorApply (vcolorchsr *chizler, vcolor *color)
{
    vdialogItem *item = (vdialogItem*)vcolorchsrGetData(chizler);

    if (item != NULL) {
	vdialogSetItemBackground (item, color);
    }

} /* _setBackColorApply */




/* _setBackColorIsssue -- set the background color for a minitext.
 *
 *  -> command -- the command that's being issued right now
 *  -> context -- the context in which this command is being issued
 * <-          -- TRUE if we handled it, FALSE if we didn't
 */
static int _setBackColorIssue (vcommandFunction *command, vdict *context)
{
    static vcolorchsr *chizler = NULL;
    vdialogItem *item;

    if (chizler == NULL) {
	chizler = vcolorchsrCreate ();
	vcolorchsrSetApply (chizler, _setBackColorApply);
    }

    item = vdialogFindItem ((vdialog*)vdictLoad(context, vname_Dialog),
			    TAG("AttributeTarget"));
    vcolorchsrSetData (chizler, item);

    if (item != NULL) {
	vcolorchsrSetColor (chizler, vdialogDetermineItemBackground(item));
    }

    vcolorchsrOpen (chizler);

    return (TRUE);

} /* _setBackColorIssue */



/* _noSelectionIssue -- set the 'no selection' attribute of the minitext
 *
 *  -> command -- the command that's being issued right now
 *  -> context -- the context in which this command is being issued
 * <-          -- TRUE if we handled it, FALSE if we didn't
 */
static int _noSelectionIssue (vcommandFunction *command, vdict *context)
{
    mtext *text;

    text = (mtext*)vdialogFindItem ((vdialog*)vdictLoad(context, vname_Dialog),
				    TAG("AttributeTarget"));

    mtextSetSelectType (text, mtextNO_SELECTION);

    return (TRUE);

} /* _noSelectionIssue */




/* _noSelectionIssue -- set the 'single selection' attribute of the minitext
 *
 *  -> command -- the command that's being issued right now
 *  -> context -- the context in which this command is being issued
 * <-          -- TRUE if we handled it, FALSE if we didn't
 */
static int _singleSelectionIssue (vcommandFunction *command, vdict *context)
{
    mtext *text;

    text = (mtext*)vdialogFindItem ((vdialog*)vdictLoad(context, vname_Dialog),
				    TAG("AttributeTarget"));
    mtextSetSelectType (text, mtextSINGLE_POSITION_ONLY);
    return (TRUE);

} /* _singleSelectionIssue */




/* _noSelectionIssue -- set the 'range selection' attribute of the minitext
 *
 *  -> command -- the command that's being issued right now
 *  -> context -- the context in which this command is being issued
 * <-          -- TRUE if we handled it, FALSE if we didn't
 */
static int _rangeSelectionIssue (vcommandFunction *command, vdict *context)
{
    mtext *text;
    int type = mtextRANGE_SELECTION;

    text = (mtext*)vdialogFindItem ((vdialog*)vdictLoad(context, vname_Dialog),
				    TAG("AttributeTarget"));

    /* for grins, change this one via ID attributes */

    vobjectSetIDAttribute (mtextGetObject(text), 
			   mtextID_ATTRIBUTE_SELECT_TYPE, &type);
    

    return (TRUE);

} /* _rangeSelectionIssue */




/* _borderIssue -- turn on and off the border
 *
 *  -> command -- the command that's being issued right now
 *  -> context -- the context in which this command is being issued
 * <-          -- TRUE if we handled it, FALSE if we didn't
 */
static int _borderIssue (vcommandFunction *command, vdict *context)
{
    vdialogItem *item;

    item = vdialogFindItem ((vdialog*)vdictLoad(context, vname_Dialog),
			    TAG("AttributeTarget"));
    vdialogSetItemBorder (item, vdictLoad(context, vname_Toggle) == vname_On);

    return (TRUE);

} /* _borderIssue */




/* _enabledIssue -- enable and disable the item
 *
 *  -> command -- the command that's being issued right now
 *  -> context -- the context in which this command is being issued
 * <-          -- TRUE if we handled it, FALSE if we didn't
 */
static int _enabledIssue (vcommandFunction *command, vdict *context)
{
    vdialogItem *item;
    const vname *state;

    item = vdialogFindItem ((vdialog*)vdictLoad(context, vname_Dialog),
			    TAG("AttributeTarget"));

    /* for grins, set the state via attributes */
    state = (  (vdictLoad(context, vname_Toggle) == vname_On)
	     ? vname_Enabled
	     : vname_Disabled);

    vobjectSetIDAttribute (vdialogGetItemObject(item),
			   vdialogITEM_ID_ATTRIBUTE_STATE, state);
			   
    return (TRUE);

} /* _enabledIssue */





/* _cloneIssue -- clone the dialog the command came from - tests the clone
 *		  operations of the objects inside of it
 *
 *  -> command -- the command that's being issued right now
 *  -> context -- the context in which this command is being issued
 * <-          -- TRUE if we handled it, FALSE if we didn't
 */
static int _cloneIssue (vcommandFunction *command, vdict *context)
{
    vdialog *dialog = (vdialog*)vdictLoad (context, vname_Dialog);

    dialog = vdialogClone (dialog);

    _setupCommands (dialog);
    vdialogOpen (dialog);

    return (TRUE);

} /* _cloneIssue */



/* _loadStoreIssue -- store the dialog the command came from into a resource
 *		      and re-load it.  tests the resource operations of the
 *		      objects contained within
 *
 *  -> command -- the command that's being issued right now
 *  -> context -- the context in which this command is being issued
 * <-          -- TRUE if we handled it, FALSE if we didn't
 */
static int _loadStoreIssue (vcommandFunction *command, vdict *context)
{
    vdialog *dialog = (vdialog*)vdictLoad (context, vname_Dialog);
    vresource root, resource;

    root = vresourceCreateMem ();
    resource = vresourceCreate (root,
				vnameInternGlobalLiteral("Spam"), 
				vresourceDICT);

    vdialogStore (dialog, resource);
    dialog = vdialogLoad (resource);
    
    _setupCommands (dialog);
    vdialogOpen (dialog);

    vresourceDestroyMem (root);

    return (TRUE);

} /* _loadStoreIssue */




/*
 * ----- Application specific setup
 */



/* _generalSetup -- get the application up and running.
 */
static void _generalSetup (void)
{
    /* Galaxy classes coming in from resources */

    vcontainerStartup ();
    vmenubarStartup  ();
    vcontrolStartup ();
    vsliderStartup ();
    vdialogStartup();
    vmenuStartup ();

    (void) mtextGetDefaultClass ();
    
    /* our mtext subclass that diddles with natural separation */
    (void) natsepGetDefaultClass ();

} /* _generalSetup */




/*
 * ----- Generic Scaffolding follows
 */



static int _quitIssue (vcommandFunction *command, vdict *attr2value)
{
    veventStopProcessing ();
    return (TRUE);
} /* _quitNotify */



static int _closeIssue (vcommandFunction *command, vdict *attr2value)
{
    veventStopProcessing ();
    return (TRUE);
} /* _closeIssue */




static vcommandFunctionTemplate commandTable[] = {
    { "Close",		       _closeIssue,		NULL },
    { "Quit",		       _quitIssue,		NULL },
    { "Natural Size",	       _naturalSizeIssue,	NULL },
    { "Natural Separation",    _naturalSeparationIssue,	NULL },
    { "Attribute",	       _attributeIssue,		NULL },
    { "Container",	       _containerIssue,		NULL },
    { "Right to Right",        _rightToRightIssue,	NULL },
    { "Left to Left",	       _leftToLeftIssue,	NULL },
    { "Bottom to Top",	       _bottomToTopIssue,	NULL },
    { "Top to Bottom",	       _topToBottomIssue,	NULL },
    { "Set Font...",	       _setFontIssue,		NULL },
    { "Set Fore Color...",     _setForeColorIssue,	NULL },
    { "Set Back Color...",     _setBackColorIssue,	NULL },
    { "No Selection",	       _noSelectionIssue,	NULL },
    { "Single Selection",      _singleSelectionIssue,	NULL },
    { "Range Selection",       _rangeSelectionIssue,	NULL },
    { "Border",		       _borderIssue,		NULL },
    { "Enabled",	       _enabledIssue,		NULL },
    { "Clone",		       _cloneIssue,		NULL },
    { "Load/Store",	       _loadStoreIssue,		NULL }
};



/* _setupCommands -- stuff a command space into a dialog
 *
 *  -> dialog -- the dialog to install the commands into
 */
static void _setupCommands (vdialog *dialog)
{

    vdict *dict;
    vcommandSpace *space;
    
    dict = vcommandCreateDictFunctionTemplates (commandTable,
						sizeof(commandTable)
						/ sizeof(vcommandFunctionTemplate));
    
    space = vcommandCreateSpace ();
    
    vcommandAddSpaceDictOwned (space, vname_Command, dict);
    
    vwindowSetSpaceOwned (vdialogGetWindow(dialog), space);
    
} /* _setupCommands */




/* main -- the start of all power
 *
 *  -> argc -- command line argument counts
 *  -> argv -- count command line arguments
 * <-       -- success/failure of our codes
 */
int main (int argc, char *argv[])
{
    vresource appres, dialogres;
    vdialog  *dialog;

    vprefSetArgs (argc, argv);

    _generalSetup ();

    appres = vapplicationGetResources (vapplicationGetCurrent());
    dialogres = vresourceGet (appres, TAG("Dialog"));

    dialog = vdialogLoad (dialogres);

    _setupCommands (dialog);

    vdialogOpen (dialog);

    veventProcess ();

    /* close all open windows */
    {
	vapplicationWindowIterator iterator;
	vapplicationInitWindowIterator (&iterator, vapplicationGetCurrent());

	while (vapplicationNextWindowIterator(&iterator)) {
	    vwindowDestroy (vapplicationGetWindowIteratorWindow (&iterator));
	}

	vapplicationDestroyWindowIterator (&iterator);
    }

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


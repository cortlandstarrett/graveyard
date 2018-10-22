/* $Id: txtflt.c,v 1.10 1996/05/31 04:55:11 dimitri Exp $ */

/* textfilter.c -- Add filtration to textitems.
 *
 * This modules implements a simple subclass that runs all text insertion
 * through a client-settable filter function that can decide on a character-
 * by-character basis what gets put into the textitem.
 *
 * The client supplies a filter function of the form:
 * int filterFunc (vtext *text, vtextSelection *selection, 
 *             const vchar **newText, long *length)
 * Where text is the vtext object to add the text to, selection is the
 * currently selected range of text, newText is the new data being added,
 * and length is a pointer to the length of text in newText.  
 * Since newText is a vchar**, you can change the text being added, even
 * adding new text.  The length can be modified in the filter as well.
 * The filter returns TRUE if the text manager should insert the new text,
 * returning FALSE will abort the insertion.
 *
 * Then the client attaches the filter to the text.  The filter gets called
 * whenever new text is added to the text item.
 *
 * Modification history
 *	(long time ago)	created
 *	May 96		fixed vtextitemText dependency
 */

/* This file is broken into 3 parts:
 * (a)  The text and textitem filtering functions.  These can be lifted
 *      verbatim and put into your application.
 * (b)  Sample filters.  These give a flavor of writing a filter function.
 * (c)  Driver program that filters 5 textitems
 *
 * Parts (b) and (c) are surrounded by an #ifdef filterSAMPLE_PROGRAM.
 */


/* include the world. */
#include <vgalaxy.h>

/* handy macro */
#define TAG(s)	vnameInternGlobalLiteral((s))


/* this is the format of the filter functions that clients attach to
 * the textitems. */
typedef int (*filterFilterFunc)(vtext *text, vtextSelection *selection,
			        const vchar **newText, long *length);

/* This is a part of a technique of adding fields to object instances. */
typedef struct textfilter {
    vtextitemText	text;	/* the vtextitemText the filter thing 
				 * is based on */
    filterFilterFunc	filter; /* the filtering function */
} textfilter;


/* classes used.  One for vtext filtering, and a textitem that automatically
 * attaches a filtered vtext to itself.  This way you don't have to mess
 * with changing class names in vre.  This has the drawback of losing
 * any contents you may put into the text field inside of vre.  This module
 * could probably be extended to do a copy of the textitem`s previous 
 * information. */
vtextitemTextClass	*textfilterClass	= NULL;
vtextitemClass		*textfilteritemClass	= NULL;



/* _textfilterInit -- Initializes a text filter object.
 *
 *  -> text	-- the text filter to initialize.
 */
static void _textfilterInit (vtextitemText *text)
{
    textfilter	*filter;
    
    vclassSendSuper (textfilterClass, vobjectINIT, (text));
    filter = (textfilter *) text;
    filter->filter = NULL;
} /* _textfilterInit */



/* _textfilterInsert -- override of vtextINSERT.  This passes the text
 *			through the filter before giving it to the 
 *			Text Manager.
 *
 *  -> text	 -- the text manager object who is getting text added.
 *  -> selection -- current selected range.  This range will be replaced
 *		    by the new text.
 *  -> s	 -- the string being added.
 *  -> len	 -- how long s is .
 */
static void _textfilterInsert (vtextitemText *text, vtextSelection *selection,
			       const vchar *s, long len)
{
    textfilter		*filter;
    long		 nuLen = len;
    
    filter = (textfilter*) text;
    
    if (   (filter->filter == NULL)
	|| (filter->filter ((vtext*) text, selection, &s, &nuLen))) {
	vclassSendSuper (textfilterClass, vtextINSERT, 
			 (text, selection, s, nuLen));
    }
} /* _textfilterInsert */




/* textfilterGetClass -- returns the vtext subclass that does filtering.
 *
 * <- 		-- the filtering subclass.
 */
static vtextitemTextClass *textfilterGetClass (void)
{
    if (textfilterClass == NULL) {
	textfilterClass = vclassReproduce (vtextitemGetDefaultTextDataClass());
	vclassSetNameScribed (textfilterClass, 
			      vcharScribeLiteral ("textfilterClass"));
	vclassSetObjectSize (textfilterClass, sizeof(textfilter));
	vclassSet (textfilterClass, vobjectINIT, _textfilterInit);
	vclassSet (textfilterClass, vtextINSERT, _textfilterInsert);
    }
    
    return (textfilterClass);
} /* textfilterGetClass */




/* _textfilteritemCreateTextData -- creates a new filtered vtext for
 * 			use in the given textitem.
 *
 *  -> textitem	-- a filtered text item.  Parameter not used.
 * <-		-- a newly created filtered vtext.
 */
static vtext *_textfilteritemCreateTextData (vtextitem *textitem)
{
    return (vtextCreateOfClass (textfilterGetClass()));
} /* _textfilteritemCreate */




/* textfilteritemSetItemFilter -- attaches the given filter to the
 *			given filtered textitem.
 *
 *  -> textitem	-- the textitem whose text is being filtered
 *  -> filter	-- the filter function doing the filtering.
 */
void textfilteritemSetItemFilter (vtextitem *textitem, 
				  filterFilterFunc filter)
{
    textfilter		*textData;
    
    textData = (textfilter*)vtextitemGetTextData (textitem);
    textData->filter = filter;
} /* textfilteritemSetItemFilter */



/* _textfilteritemLoadInit -- reads a filtered text item from a resource.
 *
 *  -> textitem	-- the filtered textitem to read from a resource.
 *  -> resource -- the resource to read it from.
 *
 * We do things this way (destroying the existing text and replacing it
 * with a newly created filtered text object) to make the use of this thing
 * more convenient.  You can change the class the textitem uses for its 
 * vtext by editing the low-level resources manually, but that's a little
 * too painful.
 */
static void _textfilteritemLoadInit (vtextitem *textitem, vresource resource)
{
    vtext	*oldText, *newText;

    vclassSendSuper (textfilteritemClass, vobjectLOAD_INIT,
		     (textitem, resource));

    oldText = vtextitemGetTextData (textitem);
    newText = _textfilteritemCreateTextData (textitem);

    /* get the previous contents, rulers, etc... */

    vtextCopy (oldText, newText); 

    /* set the textitem text to NULL (safe state)
     */

    vtextviewSetTextData (vtextitemGetView(textitem), NULL);

    /* set the selection first, and the textData following that
     */
    vtextviewSetSelection (vtextitemGetView(textitem),
			   vtextCreateSelection(newText));
    vtextviewSetTextData (vtextitemGetView(textitem), newText);

    /* destroy the oldText, it will down the old selection with it
     */
    vtextDestroy (oldText);

} /* _textfilteritemLoadInit */



/* textfilteritemGetClass -- returns a vtextitemClass for a filteredTextitem.
 *			filteredTextitems have a filtered vtext attached to
 * 			them.  All of the magic is in the vtext -- no real
 *			changes have been made to the vtextitem.
 *
 * <-		-- the filteredTextitem class.
 */
vtextitemClass *textfilteritemGetClass (void)
{
    
    if (textfilteritemClass == NULL) {
	textfilteritemClass = vclassReproduce (vtextitemGetDefaultClass());
	vclassSetNameScribed (textfilteritemClass,
			      vcharScribeLiteral("filteredTextitem"));
	vclassSet (textfilteritemClass, vobjectLOAD_INIT,
		   _textfilteritemLoadInit);
	vclassSet (textfilteritemClass, vtextitemCREATE_TEXT_DATA,
		   _textfilteritemCreateTextData);
    }
    
    return (textfilteritemClass);
} /* filteritemGetClass */




/* textfilteritemCreate -- creates a new filteredtextitem on the fly.
 *
 * <-		-- A brand new filtered text item.
 */
vtextitem *textfilteritemCreate ()
{
    return (vtextitemCreateOfClass(textfilteritemGetClass()));
} /* filteritemCreate */





#define filterSAMPLE_PROGRAM 1

#if (filterSAMPLE_PROGRAM)



/* turns on and off the beeping on bad characters. */
vbool	doBeepDo = FALSE;
#define BEEP()  do { if (doBeepDo) vwindowBeep(); } while (0)



/* _sampleNCharFilter -- only allows N characters in a particular vtext.
 * 			 Usually this will be called with by the vtext's 
 *			 filter function
 *
 *  -> text	 -- the vtext of happiness.
 *  -> sel       -- the current selection.
 * <-> string	 -- the new text being added.
 * <-> len	 -- the length of the new text.
 *  -> n	 -- how many characters the text field is limited to.
 * <-		 -- TRUE if the text should be added, FALSE to cancel.
 */
static int _sampleNCharFilter (vtext *text, vtextSelection *sel,
			       const vchar **string, long *len, int n)
{
    int selectionLen, textlen;
    int ret;

    /* we need to do selection length calculations because the new text
     * is added _before_ the old selection's text is nuked. */
    selectionLen = vtextEndPos(sel) - vtextStartPos(sel);
    textlen = vtextLength (text);

    *len = vMIN (n - (textlen - selectionLen), *len);

    if (*len > 0) {
	ret = TRUE;
    } else {
	BEEP ();
	ret = FALSE;
    }
    return (ret);
} /* _sampleNCharFilter */



/* _sampleOneCharFilter -- sample filter for limiting a text field to 1 char.
 *
 *  -> text	-- the vtext being filtered.
 *  -> sel	-- the current selection.
 * <-> string	-- the new text being added.
 * <-> len	-- the length of the new text.
 * <-		-- TRUE if the text should be added, FALSE To cancel.
 */
static int _sampleOneCharFilter (vtext *text, vtextSelection *sel,
				 const vchar **string, long *len)
{
    return (_sampleNCharFilter(text, sel, string, len, 1));
} /* _sampleOneCharFilter */



/* _sample17CharFilter -- sample filter for limiting a text field to 17 chars.
 *
 *  -> text	-- the vtext being filtered.
 *  -> sel	-- the current selection.
 * <-> string	-- the new text being added.
 * <-> len	-- the length of the new text.
 * <-		-- TRUE if the text should be added, FALSE To cancel.
 */
static int _sample17CharFilter (vtext *text, vtextSelection *sel,
				const vchar **string, long *len)
{
    return (_sampleNCharFilter(text, sel, string, len, 17));
} /* _sample17CharFilter */



/* _sampleOneCharFilter -- sample filter for limiting a text field to
 *			alphabetic characters.
 *
 *  -> text	-- the vtext being filtered.
 *  -> sel	-- the current selection.
 * <-> string	-- the new text being added.
 * <-> len	-- the length of the new text.
 * <-		-- TRUE if the text should be added, FALSE To cancel.
 */
static int _sampleLetterFilter (vtext *text, vtextSelection *sel,
				 const vchar **s, long *len)
{
    int ret = FALSE;

    if (*len > 0) {
	*len = 1;
	if (vcharIsAlphabetic (**s)) {
	    ret = TRUE;
	} else {
	    BEEP ();
	    ret = FALSE;
	}
    } else {
	ret = FALSE;
    }
    return (ret);
} /* _sampleLetterFilter */


/* _sampleNumberFilter -- sample filter for limiting a text field to digits
 *
 *  -> text	-- the vtext being filtered.
 *  -> sel	-- the current selection.
 * <-> string	-- the new text being added.
 * <-> len	-- the length of the new text.
 * <-		-- TRUE if the text should be added, FALSE To cancel.
 */
static int _sampleNumberFilter (vtext *text, vtextSelection *sel,
				 const vchar **s, long *len)
{
    int ret = FALSE;

    if (*len > 0) {
	*len = 1;
	if (vcharIsDigit (**s)) {
	    ret = TRUE;
	} else {
	    BEEP ();
	    ret = FALSE;
	}
    } else {
	ret = FALSE;
    }
    return (ret);
} /* _sampleNumberFilter */



/* _samplePunctuationFilter -- sample filter for limiting a text field to 
 *			punctuation.
 *
 *  -> text	-- the vtext being filtered.
 *  -> sel	-- the current selection.
 * <-> string	-- the new text being added.
 * <-> len	-- the length of the new text.
 * <-		-- TRUE if the text should be added, FALSE To cancel.
 */
static int _samplePunctuationFilter (vtext *text, vtextSelection *sel,
				     const vchar **s, long *len)
{
    int ret = FALSE;

    if (*len > 0) {
	*len = 1;
	if (vcharIsPunctuation (**s)) {
	    ret = TRUE;
	} else {
	    BEEP ();
	    ret = FALSE;
	}
    } else {
	ret = FALSE;
    }
    return (ret);
} /* _samplePunctuationFilter */



/* _sampleRealFilter -- sample filter for limiting a text field to a real
 *			value (numbers and 1 decimal point.
 *
 *  -> text	-- the vtext being filtered.
 *  -> sel	-- the current selection.
 * <-> string	-- the new text being added.
 * <-> len	-- the length of the new text.
 * <-		-- TRUE if the text should be added, FALSE To cancel.
 */
static int _sampleRealFilter (vtext *text, vtextSelection *sel,
				 const vchar **s, long *len)
{
    int    ret = FALSE;
    vchar  decimalPoint;  /* !!! should use i18n version */

    decimalPoint = vcharFromLiteral('.');

    if (*len > 0) {
	*len = 1;
	if (vcharIsDigit (**s)) {
	    ret = TRUE;
	} else if (**s == decimalPoint) {
	    long len = vtextLength (text), i;
	    ret = TRUE;
	    /* make sure there's only one decimal point */
	    for (i = 0; i < len; i++) {
		if (*vtextGetTextAt (text, i) == decimalPoint) {
		    ret = FALSE;
		    BEEP ();
		    break;
		}
	    }
	} else {
	    BEEP ();
	    ret = FALSE;
	}
    } else {
	ret = FALSE;
    }
    return (ret);
} /* _sampleRealFilter */




/* --------------- Filter sample setup stuff ------------ */


/* the rest of this is support and setup for using the above classes,
 * and filters
 */


/* a typedef for making a table of mappings between textitem tag names
 * and the associated filter function. */
typedef struct sampleFilterItem {
    char		*textTag;
    filterFilterFunc	 filter;
} sampleFilterItem;


/* the mapping table. */
static sampleFilterItem sampleFilterTable[] = {
    { "OneChar", 	_sampleOneCharFilter 	},
    { "17Char",		_sample17CharFilter  	},
    { "Letters",	_sampleLetterFilter  	},
    { "Numbers",	_sampleNumberFilter  	},
    { "Punctuation",	_samplePunctuationFilter},
    { "Real Numbers",   _sampleRealFilter       },
    { NULL, 		NULL 		     	}
};




/* _sampleSetupImmediateFields -- attaches the filter functions to the
 * 			n filtered text items.  (these are the ones
 *			specified in the sampleFilterTable.)
 *
 *  -> dialog	-- the dialog that contains these textitems.
 */
static void _sampleSetupImmediateFields (vdialog *dialog)
{
    sampleFilterItem	*scan;
    vtextitem		*textitem;

    for (scan = sampleFilterTable; scan->textTag != NULL; scan++) {
	textitem = (vtextitem*)vdialogFindItem (dialog, TAG(scan->textTag));
	if (scan->filter != NULL) {
	    textfilteritemSetItemFilter (textitem, scan->filter);
	}
    }
} /* _sampleSetupImmediateFields */



/* _sampleQuitButtonNotify -- the callback function for the Quit
 *			pushbutton.  This stops processing, and we
 *			fall through the other side of the veventProcess ();
 *
 *  -> button	-- the button that was triggered.
 *  -> evetn	-- the event that triggered it.
 */
static void _sampleQuitButtonNotify (vbutton *button, vevent *event)
{
    veventStopProcessing ();
} /* _sampleQuitButtonNotify */



/* _sampleHandleDialog -- the callback function for the main dialog
 *			This stops processing, and we
 *			fall through the other side of the veventProcess ();
 *
 *  -> dialog	-- the dialog that was notified.
 *  -> event	-- the event that triggered it.
 */
static void _sampleHandleDialog (vdialog *dialog, vevent *event)
{
    if (veventIsClose (event)) {
	veventStopProcessing ();
    }
} /* _sampleHandleDialog */



/* _sampleBeepBoxNotify -- this turns on and off the "beep when an invalid
 *			character is typed" feature.
 *
 *  -> checkbox	-- the beep box boinked on.
 *  -> event	-- the event that boinked it.
 */
static void _sampleBeepBoxNotify (vcontrol *checkbox, vevent *event)
{
    doBeepDo = !doBeepDo;
} /* _sampleBeepBoxNotify */




/* _sampleSetupControls -- attaches the callbacks to the various pushbuttons
 *			and checkboxes in this sample.
 *
 *  -> dialog	-- the dialog that owns these controls.
 */
static void _sampleSetupControls (vdialog *dialog)
{
    vbutton    *quitButton;
    vcontrol   *humanBeepBox;

    quitButton = (vbutton*) vdialogFindItem (dialog, TAG("QuitButton"));
    vbuttonSetNotify (quitButton, _sampleQuitButtonNotify);

    humanBeepBox = (vcontrol*) vdialogFindItem (dialog, TAG("BeepBox"));
    vcontrolSetNotify (humanBeepBox, _sampleBeepBoxNotify);

} /* _sampleSetupControls */



/* main -- Guido, it's all so clear to me now.  main() is the keeper of
 *			the cheese, and you are the Lemon Merchant.
 *
 *  -> argc -- he is on to us, I know.
 *  -> argv -- we must escape now, before
 * <-	    -- they let loose the marmocets!
 */
int main (int argc, char *argv[])
{
    vresource	appRes, dialogRes;
    vdialog    *dialog;
    
    vstartup (argc, argv);
    
    (void) textfilterGetClass ();
    (void) textfilteritemGetClass ();
    
    appRes = vapplicationGetResources (vapplicationGetCurrent());

    dialogRes = vresourceGet (appRes, TAG("Dialog"));
    dialog = vdialogLoad (dialogRes);
    
    _sampleSetupControls (dialog);
    _sampleSetupImmediateFields (dialog);
    
    vdialogSetNotify (dialog, _sampleHandleDialog);

    vdialogOpen (dialog);
    
    veventProcess ();
    
    vdialogDestroy (dialog);
    vclassDestroy (textfilterClass);
    vclassDestroy (textfilteritemClass);

    exit (EXIT_SUCCESS);
    return (EXIT_FAILURE);
    
} /* main */

#endif /* SAMPLE_PROGRAM */






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



/* $Id: password.c,v 1.4 1996/05/31 16:55:48 dimitri Exp $
 *
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
 * copyright notice in the in the form of "Copyright 1992 Visix Software Inc.,
 * 11440 Commerce Park Drive, Reston, VA  22091. All Rights Reserved" appears
 * in all copies, (ii) both the copyright notice and this permission notice
 * appear in supporting documentation and (iii) you are a valid licensee of
 * Galaxy Application Environment.
 */

/*
 * password - displays a test item that can be used for entering a password,
 *            where "*"'s are displayed instead of text.
 *
 * The basic idea here it to display "*".s instead of text, while still
 * preserving the real text.  The most obvious solution is to override the
 * vtextviewDRAW_RUN method in text item.
 */

#include <vport.h>		/* for v*HEADER */
#include vstdlibHEADER		/* for random, exit, EXIT_SUCCESS */
#include vapplicationHEADER
#include vstartupHEADER
#include vmemHEADER
#include vdialogHEADER
#include vprefHEADER
#include vtextitemHEADER
#include vcharHEADER
#include vclassHEADER

vtextitemTextClass	      *defaultTextDataClass;

/* Forward declarations */

static void	      passwordInsert(vtextitemText *t, 
				     vtextSelection *selection, 
				     const vchar *text, long length);
static void	      passwordDelete(vtextitemText *t, 
				     vtextSelection *selection);
static void	      passwordDestroy(vtextitemText *t);
static void 	      passwordNotify(vtextitem *t, vevent *ev, int message);
static void	      dialogNotify (vdialog *dialog, vevent *event);

/* Structure for our own vtext object */

typedef struct passwordText {
    vtextitemText  text;
    vtext	   *realText;
    vtextSelection *realSelection;
} passwordText;


int main(int argc, char *argv[])
{
    vdialog		*dialog;
    vresource		res;
    vtextitem		*textItem;
    passwordText	*text;

    vstartup(argc, argv);

    /*
     * Set up the text data class to do the filtering
     */

    defaultTextDataClass = vclassReproduce(vtextitemGetDefaultTextDataClass());
    
    vclassSetNameScribed(defaultTextDataClass,
                         vcharScribeLiteral("myTextDataClass"));
    vclassSetObjectSize(defaultTextDataClass, sizeof(passwordText));

    vclassSet(defaultTextDataClass,
 	      vtextINSERT,		passwordInsert);
    vclassSet(defaultTextDataClass,
 	      vtextDELETE,		passwordDelete);
    vclassSet(defaultTextDataClass,
 	      vobjectDESTROY,		passwordDestroy);

    /*	
     * Get the resource file and load the dialog
     */

    res = vapplicationGetResources(vapplicationGetCurrent());

    dialog = vdialogLoad(vresourceGet(res, vname_Dialog));

    vdialogSetNotify (dialog, dialogNotify);
    
    /*
     * Find the text item in the dialog
     */

    textItem = (vtextitem *) vdialogFindItem(dialog, vname_Text);

    vtextitemSetNotify(textItem, passwordNotify);

    /*
     * Create the "realText" text data object, this is where the actual
     * text will go
     */
     
    text = (passwordText *) vtextitemGetTextData(textItem);
    text->realText      = vtextCreate();
    text->realSelection = vtextCreateSelection(text->realText);

    /*
     * Open the dialog and start processing
     */

    vdialogOpen(dialog);

    veventProcess();
    
    vdialogDestroy(dialog);

    exit(EXIT_SUCCESS);
    return EXIT_FAILURE;
}

/*
 * passwordInsert
 *
 * Implementation for the vtextINSERT method.  
 */
static void passwordInsert(
    vtextitemText	*editRec,
    vtextSelection	*selection,
    const vchar		*text,
    long		length
    )
{
    vstr		*str, *scan;
    int			i, start;
    passwordText	*passText = (passwordText *) editRec;

    scan = str = vstrCreateSized(length);
    i	       = length;

    while (i-- > 0)
	*(scan++) = '*';

    /* Send-super to insert the "*"'s into the displayed text item */

    start = vtextSelectionStart(selection);

    vclassSendSuper(defaultTextDataClass, vtextINSERT,
		    (editRec, selection, str, length));

    /* Insert the text into our "real" text object */

    vtextSelectRange(passText->realText, passText->realSelection,
		     start, start);
    vtextInsert(passText->realText, passText->realSelection, text, length);

    vstrDestroy(str);
}

/*
 * passwordDelete
 *
 * Implementation for the vtextDELETE method.  
 */
static void passwordDelete(
    vtextitemText	*editRec,
    vtextSelection	*selection
    )
{
    passwordText	*passText = (passwordText *) editRec;

    /* Delete the text in our "real" text object */

    vtextSelectRange(passText->realText, passText->realSelection,
		     vtextSelectionStart(selection), 
		     vtextSelectionEnd(selection));
    vtextDelete(passText->realText, passText->realSelection);

    vclassSendSuper(defaultTextDataClass, vtextDELETE, (editRec, selection));
}

/*
 * passwordDestroy
 *
 * Destroy the auxillary text object stored with our passwordText 
 * text data object
 */
static void passwordDestroy(
    vtextitemText	*editRec
    )
{
    vtextDestroy(((passwordText *) editRec)->realText);

    vclassSendSuper(defaultTextDataClass, vobjectDESTROY, (editRec));
}

/*
 * passwordNotify
 *
 * Catch when the user hits return or loses focus, and display
 * the password.  This shows how to retrieve the password from 
 * the auxillary storage
 */
static void passwordNotify(
    vtextitem		*textItem,
    vevent		*event,
    int			message
    )
{
    passwordText	*text;
    int			len;
    vstr		*str;
    char		*sys;

    if (message != vtextviewACCEPT_NOTIFY)
	return;

    text = (passwordText *) vtextitemGetTextData(textItem);

    /* Take the text from the real text data object and put it in a string */

    len  	= vtextLength(text->realText);
    str 	= vstrCreateSized(len + 1);
    str[len] 	= vcharNULL;
    
    vtextGetText(text->realText, NULL, str, len);

    /*
     * Now you have what they really typed - do so what you want here
     */
    
    sys = (char *) vcharExportAlloc(vcharScribeSystemExport(str));
    printf("Real text is \"%s\"\n", sys);
    vcharExportFree((void *) sys);

    vstrDestroy(str);
}


/*********
 *  dialogNotify()
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

}

/* $Id: object.c,v 1.4 1995/01/30 14:31:50 markd Exp $ */
/* object.c -- implementation of the "class/object" level functions for
 *	       the minitext example
 * The following Sample Code is provided for your reference purposes in
 * connection with your use of the Galaxy Application Environment (TM) software
 * product which you have licensed from Visix Software, Inc. ("Visix").
 * The Sample code is provided to you without any warranty of any kind
 * whatsoever and you agree to be responsible for the use and/or incorporation
 * of the Sample Code into any software product you develop. You agree to fully
 * and completely indemnify and hold Visix harmless from any and all loss,.
 * claim, liability or damages with respect to your use of the Sample Code.  
 *
 * Subject to the foregoing, you are permitted to copy, modify, and distribute
 * the Sample Code for any purpose and without fee, provided that (i) a
 * copyright notice in the in the form of "Copyright 1994 Visix Software Inc.,
 * 11440 Commerce Park Drive, Reston, VA  22091. All Rights Reserved" appears
 * in all copies, (ii) both the copyright notice and this permission notice
 * appear in supporting documentation and (iii) you are a valid licensee of
 * Galaxy Application Environment.
 *
 * Do not taunt Happy Fun Ball.
 *
 * Stuff that was done to construct this file:
 *
 * step zero:
 *    add functions for init, destroy, copy, copyInit, loadInit, store.
 *        (stubs only)
 * step one:
 *    add initialization of contents, length, and allocLeft fields
 *    add destruction of contents buffer
 *    add initialization of anchor field
 *    add shut-off of caret blink timer on destroy
 * step two:
 *    add issueSelector override
 *    add implementation of delFwd and delBackwd commands
 *    add dialog-item cursor moving (left/right/begin/end) implementations
 *    add objectDumpcommand implementation
 * step three:
 *    init selectionEnd field
 *    add more logic to cursor moving to account for selection ranges
 * step four:
 *    add changedParentAttribute override
 *    add set/getIDAttribute stuff
 *    add changed attribute override
 * step five:
 *    add more attribute stuff
 * step six:
 *    clean off cursor rect
 *    clean off flags field (gave weird results with cursor rect - oops!)
 *    add stuff to dump function
 * step seven:
 *    add arg checking
 *    implement object functions
 *    do cursor rect stuff for enabling/disabling
 */

#include <vport.h>

/* only include the header files we need for this particular file
 */

#ifndef  vobjectINCLUDED
#include vobjectHEADER
#endif

#ifndef  vresourceINCLUDED
#include vresourceHEADER
#endif

#include "mtext.h"
#include "priv.h"




/* _mtextInit -- initialzie a hunk of memory to become a living, breathing
 * 		 minitext object.
 *
 *  -> text -- the hunk of bits
 */
void _mtextInit (mtext *text)
{
    vclassSendSuper (_mtextGlobals->defaultClass, vinstanceINIT, (text));

    /* important - initialize fields *after* you sendSuper.  The object
     * is very much just garbage before sendingSuper
     */

    text->contents = (vchar*) vmemAlloc (sizeof(vchar) * _mtextALLOC_AMOUNT);
    text->length = 0;
    text->allocLeft = _mtextALLOC_AMOUNT;

    text->anchor = 0;
    text->selectionEnd = 0;

    text->selectType = mtextRANGE_SELECTION;

    text->flags = 0;

    vrectSet (0, 0, 0, 0, &text->cursorRect);

    mtextSanityCheck (text);

} /* _mtextInit */




/* _mtextDestroy -- render a living, breathing minitext object into an
 * 		    inert hunk of memory.
 *
 *  -> text -- the minitext to send to meet its maker
 */
void _mtextDestroy (mtext *text)
{
    /* important - free stuff *before* you sendSuper.  After you sendSuper,
     * the memory is effectively destroyed and is unusable.
     */

    /* don't want to try to blink with a destroyed item */
    _mtextStopCaretBlink (text);

    if (text->contents != NULL) {
	vmemFree (text->contents);
    }

    vclassSendSuper (_mtextGlobals->defaultClass, vinstanceDESTROY, (text));

} /* _mtextDestroy */




/* _mtextCopy -- replace one instance of a living, breathing minitext with
 *		 another one.  (just like that scene from Invasion of the
 *		 Body Snatchers)
 *
 *  -> text   -- the source pod^H^H^H text
 *  -> target -- the sleeper^H^H^H^H^H^H^H text to copy into
 */
void _mtextCopy (mtext *text, mtext *target)
{
#if (vdebugDEBUG)
    if (target == NULL) {
	vexGenerate (vexGetArgNullClass(), vexERRNO, 0, vexMESSAGE,
		     "_mtextCopy -- NULL target", vexNULL);
    }
#endif

    vclassSendSuper (_mtextGlobals->defaultClass, vobjectCOPY, (text, target));

    /* make sure text is sane first */
    mtextSanityCheck (text);

    if (target->contents != NULL) {
	vmemFree (target->contents);
    }

    /* make sure the previous identity's house is in order */
    _mtextRemoveCursor (target);
    _mtextStopCaretBlink (target);

    target->contents = vmemAlloc (sizeof(vchar)
				  * (text->length + text->allocLeft));
    target->length = text->length;
    target->allocLeft = text->allocLeft;

    (void) vmemCopy (text->contents, target->contents, 
		     sizeof(vchar) * text->length);

    target->anchor = text->anchor;
    target->selectionEnd = text->selectionEnd;

    target->selectType = text->selectType;

    /* mask out the cursorAdded flag */
    target->flags = text->flags & ~_mtextCURSOR_ADDED;

    /* don't need to copy cursorRect */

    mtextSanityCheck (target);

} /* _mtextCopy */




/* _mtextCopyInit -- copy a mini text into a hunk of random memory and
 *		     turn that into a living, breathing text object
 *
 *  -> text   -- the text to copy from
 *  -> target -- the memory to turn into a text object identical to the first
 */
void _mtextCopyInit (mtext *text, mtext *target)
{
#if (vdebugDEBUG)
    if (target == NULL) {
	vexGenerate (vexGetArgNullClass(), vexERRNO, 0, vexMESSAGE,
		     "_mtextCopyInit -- NULL target", vexNULL);
    }
#endif

    _mtextInit (target);
    _mtextCopy (text, target);

    mtextSanityCheck (target);

} /* _mtextCopyInit*/




/* _mtextLoadInit -- Make a text from a resource template
 *
 *  -> text     -- the minitext to initialize
 *  -> resource -- the resource template to use
 */
void _mtextLoadInit (mtext *text, vresource resource)
{
    vscribe *scribe;

    vclassSendSuper (_mtextGlobals->defaultClass, vobjectLOAD_INIT, 
		     (text, resource));

    if (vresourceTestScribeString(resource, mtext_Contents, &scribe)) {
	/* if we get "contents", assume that everything else we want
	 * is in here as well.
	 */
	text->length = vresourceGetInteger (resource, mtext_Length);
	text->allocLeft = vresourceGetInteger (resource, mtext_AllocLeft);
	text->anchor = vresourceGetInteger (resource, mtext_Anchor);
	text->selectionEnd = vresourceGetInteger (resource,mtext_SelectionEnd);

	text->contents = (vchar*) vmemAlloc (sizeof(vchar) *
					     (text->length + text->allocLeft));
	/* I'm unsure of if a trailing NUL character will be written by
	 * vcharSizedCopyScribed.  The bounded insures that only the
	 * text chars will be copied
	 */
	(void) vcharSizedCopyScribedBounded (scribe, 
					     text->contents, text->length);
	
    } else {
	int allocSize = _mtextALLOC_AMOUNT;

	/* gotten from a vre that doesn't know about mtexts.  Init to
	 * zero values, and use the title for the contents.
	 */
	text->length = vcharLength(vdialogGetItemTitle(mtextGetItem(text)));
	
	if (text->length > allocSize) {
	    allocSize = text->length + _mtextALLOC_AMOUNT;
	}

	text->contents = (vchar*) vmemAlloc (sizeof(vchar*) * allocSize);
	text->allocLeft = allocSize - text->length;

	vcharCopy (vdialogGetItemTitle(mtextGetItem(text)), text->contents);
	text->anchor = 0;
	text->selectionEnd = 0;

	text->selectType = mtextRANGE_SELECTION;
    }

    /* if you want to trigger the sanity check to see what it looks like,
     * comment this line:
     */
    text->flags = 0;

    vrectSet (0, 0, 0, 0, &text->cursorRect);

    mtextSanityCheck (text);
    
} /* _mtextLoadInit */




/* _mtextStore -- write out descriptive information so this textThing can
 * 		  be recreated in the future
 *
 *  -> text     -- the minitext to save for posterity
 *  -> resource -- the highschool yearbook to sign with this text
 */
void _mtextStore (mtext *text, vresource resource)
{
#if (vdebugDEBUG)
    if (resource == vresourceNULL) {
	vexGenerate (vexGetArgNullClass(), vexERRNO, 0, vexMESSAGE,
		     "_mtextStore -- NULL target resource", vexNULL);
    }
#endif

    vclassSendSuper (_mtextGlobals->defaultClass, vobjectSTORE, 
		     (text, resource));

    vresourceSetStringScribed (resource, mtext_Contents,
			       vcharSizedScribe (text->contents, 
						 text->length));
    vresourceSetInteger (resource, mtext_Length, text->length);
    vresourceSetInteger (resource, mtext_AllocLeft, text->allocLeft);
    vresourceSetInteger (resource, mtext_Anchor, text->anchor);
    vresourceSetInteger (resource, mtext_SelectionEnd, text->selectionEnd);
    
} /* _mtextStore */




/* _mtextDump -- spew out debugging information to a given stream
 *
 *  -> text   -- the minitext to dump
 *  -> stream -- the stream to spew to.  NULL implies using the
 *		 debug manager's info stream.
 */
void _mtextDump (mtext *text, FILE *stream)
{

#if (vdebugDEBUG)

    vchar *scan, *stop;

    if (stream == NULL) {
	stream = vdebugGetInfoStream ();
    }

    fprintf (stream, "mtext (%p\n", (void*)text);

    vclassSendSuper (_mtextGlobals->defaultClass, vobjectDUMP, (text, stream));

    fprintf (stream, "    anchor:       %d\n", text->anchor);
    fprintf (stream, "    selectionEnd: %d\n", text->selectionEnd); 
    fprintf (stream, "    length:       %d\n", text->length);
    fprintf (stream, "    allocLeft:    %d\n", text->allocLeft);

    fprintf (stream, "    contents:    (%p)", (void*)text->contents);

    scan = text->contents;
    stop = scan + text->length;
    while (scan < stop) {
	fputc ((int)(*scan), stream);
	scan++;
    }

    fprintf (stream, "\n");

    fprintf (stream, "    selectType:    %d\n", text->selectType);
    fprintf (stream, "    flags:         %x\n", text->flags);
    fprintf (stream, "    cursorRect:    %d %d %d %d",
	     text->cursorRect.x, text->cursorRect.y, 
	     text->cursorRect.w, text->cursorRect.h);
    

    fprintf (stream, ")\n");

#endif    

} /* _mtextDump */




/*
 * ----- command stuff
 */


/* _mtextIssueSelector -- handle a selector command dispatched against our 
 *			  ourselves.  [i.e. for whatever reason, the command
 * 		          manager thinks we should handle it.]
 *
 *  -> text     -- the object being commanded to do something
 *  -> selector -- the integer ID for the command being issued
 *  -> context  -- the context (all sorts of cool attributes) that this
 *		   command was issued in
 * <-           -- TRUE if we handled the command (and all further searches
 *		   for handlers should be ceased), or FALSE if we want the
 *		   next-in-line handler to process it.
 *
 * Any action that can conceivable be triggered by a keypress should be
 * invokable via a command.
 */
int _mtextIssueSelector (mtext *text, int selector, vdict *context)
{
    int ret = TRUE; /* assumed handled until proven otherwise */

#if (vdebugDEBUG)
    if (context == NULL) {
	vexGenerate (vexGetArgNullClass(), vexERRNO, 0, vexMESSAGE,
		     "_mtextIssueSelector -- NULL context dictionary", 
		     vexNULL);
    }
#endif

    switch (selector) {

	/* 
	 * bindings from mtext
	 */
	case mtextSELECT_BACKWARD_DELETE: {
	    mtextDeleteBackward (text);
	    break;
	}
	case mtextSELECT_FORWARD_DELETE: {
	    mtextDeleteForward (text);
	    break;
	}

	/*
	 * cursor-moving bindings from vdialogItem
	 */
	case vdialogITEM_SELECT_LEFT: {
	    if (mtextGetSelectionLength(text) > 0) {
		mtextSetAnchor (text, vMIN (mtextGetAnchor(text),
					    mtextGetSelectionEnd(text)));
	    } else {
		mtextSetAnchor (text, mtextGetAnchor(text) - 1);
	    }
	    break;
	}
	case vdialogITEM_SELECT_RIGHT: {
	    if (mtextGetSelectionLength(text) > 0) {
		mtextSetAnchor (text, vMAX (mtextGetAnchor(text),
					    mtextGetSelectionEnd(text)));
	    } else {
		mtextSetAnchor (text, mtextGetAnchor(text) + 1);
	    }
	    break;
	}
	case vdialogITEM_SELECT_BEGIN: {
	    mtextSetAnchor (text, 0);
	    break;
	}
	case vdialogITEM_SELECT_END: {
	    mtextSetAnchor (text, mtextGetLength(text));
	    break;
	}

	/* 
	 * object stuff 
	 */
	case vobjectSELECT_DUMP: {
	    mtextDump (text, NULL);
	    ret = FALSE; /* let our parent dump out too */
	    break;
	}

	/*
	 * leftovers
	 */
	default: {
	    ret = FALSE;
	}
    }

    mtextSanityCheck (text);

    return (ret);

} /* _mtextIssueSelector */




/* 
 * ----- Attribute stuff
 */


/* _mtextChangedParentAttribute -- some attribute of our parental object
 *				   has changed.
 *
 *  -> text      -- the object who's parent had an attribute change
 *  -> attribute -- the name of the attribute that's changed
 *  -> context   -- the context of the change
 *
 * Intercepting this method is useful to catch things that may affect us
 * indirectly.  In our case, we want to know if our parent's bounds have
 * changed so we can shift our cursor rect appropriately.  Normally, this
 * kind of bounds change has no impact at all on owned items, but we do 
 * some extra stuff that need to be kept up to date.
 *
 * Some other uses:
 * DialogItem uses this message to figure out if something interesting
 * changed in the parent that it also can control, such as fonts.
 *
 * When you do a vdialogDetermineItemFont, the dialog manager looks 
 * at some "extra" data associated with the dialog item to see if it
 * has a font explicitly set on it.  If not, it walks up to the parent
 * and sees what font it has.
 *
 * When the font changes, the individual items should be told that
 * the font changed via vdialogChangedItemAttribute.  Now suppose the
 * dialog item has a font attached to it.  This overrides the parent's
 * font.  If the parent changes its font, the ditem's font *won't* change,
 * and the vdialogChangedItemAttribute doesn't need to be sent.
 *
 * So, vdialog overrides vobjectCHANGED_PARENT_ATTRIBUTE.  If it gets
 * an attribute == vname_Font, and the ditem is currently inheriting
 * the font, call the vdialogChangedItemAttribute, otherwise do nothing.
 *
 *
 * Containers also override this method so that they can send
 * vdialogChangedItemListParentAttribute to all of the items in the
 * container's item list.  Basically propagating the change down to
 * the items.  The only attribute it really uses is the bounds attribute.
 */
void _mtextChangedParentAttribute (mtext *text, const vname *attribute,
				   vdict *context)
{
    int id_attribute;

#if (vdebugDEBUG)
    if (context == NULL) {
	vexGenerate (vexGetArgNullClass(), vexERRNO, 0, vexMESSAGE,
		     "_mtextChangedParentAttribute -- NULL context dictionary",
		     vexNULL);
    }
    if (attribute == NULL) {
	vexGenerate (vexGetArgNullClass(), vexERRNO, 0, vexMESSAGE,
		     "_mtextChangedParentAttribute -- NULL attribute",
		     vexNULL);
    }
#endif

    /* let the superclass play for awhile */
    vclassSendSuper (_mtextGlobals->defaultClass, 
		     vobjectCHANGED_PARENT_ATTRIBUTE,
		     (text, attribute, context));

    /* map from name to id_attribute number */
    id_attribute = (int)vdictLoadScalar(&_mtextDefaultIDAttributeDict,
					attribute);

    switch (id_attribute) {

	/* the rect attribute sniffing is to catch the case where the dialog
	 * item is strutted to the bottom of the dialog and the window is
	 * resized vertically.  The bounds really haven't changed, but the
	 * position of the item has physically changed, so we need to update
	 * the cursor rectangle.
	 */
	case vdialogITEM_ID_ATTRIBUTE_RECT:

	case vdialogITEM_ID_ATTRIBUTE_BOUNDS: {
	    _mtextChangeCursorRect (text);
	    break;
	}

	default: {
	    break;
	}

    }

} /* _mtextChangedParentAttribute */




/* _mtextSetIdAttribute -- an attribute is being set indirectly through
 *			   the ID_ATTRIBUTE mechanism rather than by a
 *			   direct API call.
 *
 *  -> text  -- the minitext getting an attribute changed
 *  -> id    -- the numeric attriubute ID being set
 *  -> value -- some value whose type is dependent on the attribute id
 *
 * Basically we just turn around and call the API depending on the attribute
 * that comes through. 
 */
void _mtextSetIDAttribute (mtext *text, int id, const void *value)
{
    switch (id) {

	case mtextID_ATTRIBUTE_SELECT_TYPE: {
	    mtextSetSelectType (text, *((const int*)value));
	    break;
	}

	default: {
	    vclassSendSuper (_mtextGlobals->defaultClass,
			     vobjectSET_ID_ATTRIBUTE, (text, id, value));
	}
    }

} /* _mtextSetIDAttribute */




/* _mtextGetIDAttribute -- given an ID_Attribute, return its current value
 *
 *  -> text -- the minitext having an ID attribute queried
 *  -> id   -- the numeric attribute ID being set
 * <-       -- some value whose type is dependent on the attribute id
 *
 * This is the mechanism that is used to populate command context
 * dictionaries.  (i.e. if this returns non-NULL, this attribute will be
 * put into that dictionary)
 */
const void *_mtextGetIDAttribute (mtext *text, int id)
{
    const void *ret;

    switch (id) {

	case mtextID_ATTRIBUTE_SELECT_TYPE: {
	    ret = & text->selectType;
	    break;
	}

	default: {
	    ret = vclassSendSuper (_mtextGlobals->defaultClass,
				   vobjectGET_ID_ATTRIBUTE, (text, id));
	}
    }

    return (ret);

} /* _mtextGetIDAttribute */




/* _mtextChangedAttribute -- an attribute for this particular object has
 *			     changed
 *
 *  -> text      -- the minitext who had an attribute change
 *  -> attribute -- the name of the attribute that changed
 *  -> context   -- the context the attribute changed in
 *
 * Use this mechanism to track interesting attribute changes without
 * having to know where it actually changes.  We're interested in the
 * dialogItem rect attribute.  Rather than sniffing vdialogSetItemRect,
 * we just look for the rect attribute to drift by and do our work then.
 */
void _mtextChangedAttribute (mtext *text, const vname *attribute,
			     vdict *context)
{
    int id_attribute;

#if (vdebugDEBUG)
    if (context == NULL) {
	vexGenerate (vexGetArgNullClass(), vexERRNO, 0, vexMESSAGE,
		     "_mtextChangedAttribute -- NULL context dictionary",
		     vexNULL);
    }
    if (attribute == NULL) {
	vexGenerate (vexGetArgNullClass(), vexERRNO, 0, vexMESSAGE,
		     "_mtextChangedAttribute -- NULL attribute",
		     vexNULL);
    }
#endif

    /* let the superclass play for awhile */
    vclassSendSuper (_mtextGlobals->defaultClass, vobjectCHANGED_ATTRIBUTE,
		     (text, attribute, context));

    /* map from name to id_attribute number */
    id_attribute = (int)vdictLoadScalar(&_mtextDefaultIDAttributeDict,
					attribute);

    switch (id_attribute) {

	case mtextID_ATTRIBUTE_SELECT_TYPE: {
	    vdebugInform ("cool! changing an mtext-specific attribute.\n");
	    break;
	}

	case vdialogITEM_ID_ATTRIBUTE_RECT: {
	    _mtextChangeCursorRect (text);
	    break;
	}

	case vdialogITEM_ID_ATTRIBUTE_STATE: {
	    const vname *value = vdictLoad (context, vname_Value);

	    /* turn on/off the cursor as we're enabled and disabled.  This
	     * has the side-effect of catching the case when our containing
	     * object is disabled
	     */
	    if (value == vname_Enabled) {
		_mtextAddCursor (text);
		_mtextStartCaretBlink (text);
	    } else if (value == vname_Disabled) {
		_mtextRemoveCursor (text);
		_mtextStopCaretBlink (text);
	    }
	    break;
	}

	default: {
	    break;
	}

    }

} /* _mtextChangedAttribute */




/* stuff that tells my editor (GNU emacs) how I like my code formatted */

/* Formatting information for emacs in c-mode
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


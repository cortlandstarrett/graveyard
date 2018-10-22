/* privstuff.h -- private header for the minitext example
 *
 * This file contains prototypes for private functions that get put into
 * the minitext class. (i.e. for functions that don't exist in the same
 * file that all of the vclassSet's live)
 *
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
 * Contained here also is the structure that describes the manager globals.
 *
 * Stuff that was done to construct this header
 *
 * step zero:
 *    Add prototypes for the object methods (copy, loadInit, destroy, etc...)
 *    Add initial struct for manager globals (right now has the class pointer)
 * step one:
 *    Add prototypes for dialog item draw, event, and focus/unfocus mthods
 *    Add prototypes for internal utility functions
 *    Add cursor blink timer to globals + functions to turn on/off
 * step two:
 *    add prototype for object IssueSelector method
 *    add "caretShown" global to client globals.
 *    add prototype for Dump method
 * step three:
 *    rename caret shown global
 * step four:
 *    add prototype for _mtextChangedParentAttribute
 *    add prototype for CalcPositionDifferenceRect
 *    add prototypes for ID attribute stuff
 * step five:
 *    add changed attribute proto
 * step six:
 *    add prototypes for cursor rect stuff
 */

/* no need for inclusion protection since this header shouldn't really
 * be used outside of the minitext implementation.
 */


/* 'cause not every file includes the timer header */
#ifndef vtimerINCLUDED
#include vtimerHEADER
#endif




/*
 * ----- object methods
 */

void _mtextInit (mtext *text);
void _mtextDestroy (mtext *text);
void _mtextCopy (mtext *text, mtext *target);
void _mtextCopyInit (mtext *text, mtext *target);
void _mtextLoadInit (mtext *text, vresource resource);
void _mtextStore (mtext *text, vresource resource);
void _mtextDump (mtext *text, FILE *stream);
 int _mtextIssueSelector (mtext *text, int selector, vdict *context);
void _mtextChangedParentAttribute (mtext *text, const vname *attribute,
				   vdict *context);
void _mtextSetIDAttribute (mtext *text, int id, const void *value);
const void *_mtextGetIDAttribute (mtext *text, int id);
void _mtextChangedAttribute (mtext *text, const vname *atrribute,
			     vdict *context);




/*
 * ----- dialog item methods
 */

void _mtextDrawItem (mtext *text);
void _mtextDrawItemFocus (mtext *text);
 int _mtextHandleItemButtonDown (mtext *text, vevent *event);
 int _mtextHandleItemButtonUp (mtext *text, vevent *event);
 int _mtextHandleItemDrag (mtext *text, vevent *event);
 int _mtextHandleItemDetail (mtext *text, vevent *event);
 int _mtextHandleItemKeyDown (mtext *text, vevent *event);
void _mtextFocusItem (mtext *text);
void _mtextUnfocusItem (mtext *text);
 int _mtextGetItemNaturalSeparation (mtext *item, vdialogItem *to,
				     unsigned int wickedWitch);
void _mtextConstrainItemSize (mtext *text, int *width, int *height);
void _mtextGetItemNaturalSize (mtext *text, int *width, int *height);
void _mtextGetItemMinSize (mtext *text, int *width, int *height);
void _mtextOpenItem (mtext *text);
void _mtextCloseItem (mtext *text);



/*
 * ----- non-exported utility functions
 */

void _mtextGetLineOrigin (mtext *text, int line, int *x, int *y);
 int _mtextMapPointToPosition (mtext *text, int x, int y);
void _mtextStartCaretBlink (mtext *text);
void _mtextStopCaretBlink (mtext *text);
void _mtextCalcPositionDifferenceRect (mtext *text, int pos1, int pos2,
				       vrect *rect);
void _mtextAddCursor (mtext *text);
void _mtextRemoveCursor (mtext *text);
void _mtextChangeCursorRect (mtext *text);
void _mtextDrawCaretImmediate (mtext *text, int characterPosition, int state);



/*
 * ----- global variable support
 */

/* the set of globals this manager needs.
 */
typedef struct _mtextGlobalsStruct {
    mtextClass  *defaultClass;

    vtimer      *caretTimer;
    vbool	 showCaret;

} _mtextGlobalsStruct;


/* actual variable located in text.c */
extern void **_mtextMaster;
extern vdict _mtextDefaultIDAttributeDict;


/* handy macro to get to the vclient-allocated hunk of memory where the
 * global vars live.
 */
#define _mtextGlobals ((_mtextGlobalsStruct*)*_mtextMaster)




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


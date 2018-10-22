/* $Id: listdemo.h,v 1.4 1993/11/22 22:58:16 markd Exp $
 *
 * Copyright 1992-1993 Visix Software Inc., 11440 Commerce Park Drive, 
 * Reston, VA  22091. All Rights Reserved.
 */

/* listdemo.h -- header file to the publicly export hunks of the listdemo
 *		 thingie.
 */

#ifndef listdemoINCLUDED
#define listdemoINCLUDED 1

#ifndef vportINCLUDED
#include <vport.h> /* for v*HEADER */
#endif

/* include headers for symbols used in this header */
#ifndef vresourceINCLUDED
#include vresourceHEADER
#endif

#ifndef vwindowINCLUDED
#include vwindowHEADER
#endif

#ifndef vdialogINCLUDED
#include vdialogHEADER
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C


/* open demo dialogs */
void listdemoNewLife (vresource resources);
void listdemoNewAPI (vresource resources);
void listdemoNewIncell (vresource resources);


/* handy utilities used by the demo dialogs */

void listdemoColorizeMenubar (vdialog *dialog, const vname *menubarTag);




/* windowset keepers.  Helps each demo module figure out which
 * windows to destory. See comments in vlist.c.
 */

typedef struct _windowsetNode _windowsetNode;

typedef struct _windowsetNode windowset;

typedef struct windowsetIterator windowsetIterator;

windowset *windowsetCreate (void);
void windowsetDestroy (windowset *set);
void windowsetDestroyUnbalanced (windowset *set);

void windowsetAddWindow (windowset *set, vwindow *window);
void windowsetRemoveWindow (windowset *set, vwindow *window);

void windowsetAddDialog (windowset *set, vdialog *dialog); /* conveniences */
void windowsetRemoveDialog (windowset *set, vdialog *dialog);

/* iterates over all windows in the windowset */
void windowsetInitIterator (windowsetIterator *iterator, windowset *set);
int windowsetNextIterator (windowsetIterator *iterator);
void windowsetDestroyIterator (windowsetIterator *iterator);

vwindow *windowsetGetIteratorWindow (windowsetIterator *iterator);
/* returns NULL if the pointed to window isn't really a vdialog */
vdialog *windowsetGetIteratorDialog (windowsetIterator *iterator);




/*
 * * * * * Private types and macros
 */
struct _windowsetNode {
    vwindow        *window;
    _windowsetNode *next;
};

struct windowsetIterator {
    _windowsetNode *scan;
};

#define windowsetAddDialog(s,d) windowsetAddWindow((s),vdialogGetWindow((d)))
#define windowsetRemoveDialog(s,d) windowsetRemoveWindow((s), \
							 vdialogGetWindow((d)))

/* this way of doing iterators will break if the windowset is modified 
 * during iteration */
#define windowsetGetIteratorWindow(i)	((i)->scan->window)
#define windowsetGetIteratorDialog(i)	(vclassIsKindOf 		     \
					 (vwindowGetClass((i)->scan->window),\
					  vdialogGetDefaultClass())	     \
					 ? ((vdialog*)((i)->scan->window))   \
					 : NULL)

vportEND_CPLUSPLUS_EXTERN_C

#endif /* listdemoINCLUDED */


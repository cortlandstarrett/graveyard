/* $Id: vtbsepar.h,v 1.4 1997/09/11 23:34:24 robert Exp $ */

/************************************************************

    vtbsepar.h

    C Interface file for Toolbars Separators

    Copyright (c) 1997 Visix Software Inc.
    All rights reserved

************************************************************/

#ifndef vtoolbarSeparatorINCLUDED
#define vtoolbarSeparatorINCLUDED

#ifndef vdialogINCLUDED
#include vdialogHEADER
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C

/* Public types
 */

typedef struct vtoolbarSeparator vtoolbarSeparator;
typedef struct vtoolbarSeparatorClass vtoolbarSeparatorClass;

typedef void (*vtoolbarSeparatorNoteProc)(
    vtoolbarSeparator              *Separator,
    vevent                       *event
    );

struct vtoolbarSeparator {
    vdialogItem   item;
    short         width, height;
};

/* Class definition and macros
 */

#define vtoolbarSeparatorCLASS(SUPER, SEPAR, NOTIFY) \
vdialogITEM_CLASS(SUPER, SEPAR, NOTIFY); \
vclassMETHOD(vtoolbarSET_SEPARATOR_WIDTH, (SEPAR *separator, short width));\
vclassMETHOD(vtoolbarSET_SEPARATOR_HEIGHT, (SEPAR *separator, short height))

struct vtoolbarSeparatorClass {
    vtoolbarSeparatorCLASS(vtoolbarSeparatorClass, vtoolbarSeparator, 
                           vtoolbarSeparatorNoteProc);
};
	
/* Public functions */

void vtoolbarSeparatorStartup(void);

vtoolbarSeparatorClass *vtoolbarGetDefaultSeparatorClass(void);

vtoolbarSeparatorClass *vtoolbarGetSeparatorClass(
    vtoolbarSeparator *Separator);

vtoolbarSeparator *vtoolbarCreateSeparator(void);

vtoolbarSeparator *vtoolbarCreateSeparatorOfClass(
    vtoolbarSeparatorClass *clas);

vdialogItem *vtoolbarGetSeparatorItem(
    vtoolbarSeparator *Separator);

void vtoolbarSetSeparatorWidth(
    vtoolbarSeparator *Separator,
    short width);

void vtoolbarSetSeparatorHeight(
    vtoolbarSeparator *Separator,
    short height);

short vtoolbarGetSeparatorWidth(
    vtoolbarSeparator *Separator);

short vtoolbarGetSeparatorHeight(
    vtoolbarSeparator *Separator);

/* Private macros */

#define vtoolbarGetSeparatorClass(d) \
    ((vtoolbarSeparatorClass*)vdialogGetItemClass(vtoolbarGetSeparatorItem(d)))

#define vtoolbarCreateSeparatorOfClass(c) \
    ((vtoolbarSeparator*)vdialogCreateItemOfClass((vdialogItemClass*)(c)))

#define vtoolbarCreateSeparator() \
    vtoolbarCreateSeparatorOfClass(vtoolbarGetDefaultSeparatorClass())

#define vtoolbarGetSeparatorItem(d) vportBASE_OBJECT(d, item)

#define vtoolbarSetSeparatorWidth(d, w) \
    vclassSend(vtoolbarGetSeparatorClass(d), \
               vtoolbarSET_SEPARATOR_WIDTH, (d, w))

#define vtoolbarSetSeparatorHeight(d, w) \
    vclassSend(vtoolbarGetSeparatorClass(d), \
               vtoolbarSET_SEPARATOR_HEIGHT, (d, w))

#define vtoolbarGetSeparatorWidth(d) ((d)->width)

#define vtoolbarGetSeparatorHeight(d) ((d)->height)

vportEND_CPLUSPLUS_EXTERN_C

#endif /* vtoolbarSeparatorINCLUDED */



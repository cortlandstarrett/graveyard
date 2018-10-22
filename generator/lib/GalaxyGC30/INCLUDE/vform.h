/* $Id: vform.h,v 1.20 1997/10/14 17:52:43 robert Exp $ */

/************************************************************

    vform.h

    C Interface file for the Form Manager

    (c) Copyright Visix Software Inc.
    All rights reserved

************************************************************/

#ifndef vformINCLUDED
#define vformINCLUDED

#ifndef  vportINCLUDED
#include <vport.h>
#endif

#ifndef  vclassINCLUDED
#include vclassHEADER
#endif

#ifndef  vcontainerINCLUDED
#include vcontainerHEADER
#endif

#ifndef  vdebugINCLUDED
#include vdebugHEADER
#endif

#ifndef  vdialogINCLUDED
#include vdialogHEADER
#endif

#ifndef  veventINCLUDED
#include veventHEADER
#endif

#ifndef  vfieldINCLUDED
#include vfieldHEADER
#endif

#ifndef  vnameINCLUDED
#include vnameHEADER
#endif

#ifndef  vobjectINCLUDED
#include vobjectHEADER
#endif

#ifndef  vobservableINCLUDED
#include vobservableHEADER
#endif

#ifndef  vresourceINCLUDED
#include vresourceHEADER
#endif

#ifndef  vsequenceINCLUDED
#include vsequenceHEADER
#endif

#ifndef  vspringINCLUDED
#include vspringHEADER
#endif


vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * * * * * * * * * * PUBLIC CONSTANT DEFINITIONS  * * * * * * * * * *
 */

#define vform_BooleanInterface      (_vformPredefs [_vform_BooleanInterface])

/* vform attribute ids */
enum {
  vformNEXT_ID_ATTRIBUTE      = vcontainerNEXT_ID_ATTRIBUTE
};

/* vform command selectors */
enum {
  vformNEXT_SELECT            = vcontainerNEXT_SELECT
};


/*
 * * * * * * * * * * PUBLIC TYPE DEFINITIONS * * * * * * * * * *
 */

typedef struct vform			   vform;
typedef struct vformClass		   vformClass;
typedef struct vformFieldIterator          vformFieldIterator;
typedef struct vformFieldIteratorClass     vformFieldIteratorClass;

typedef void (*vformNoteProc)(
  vform                      *form,
  vevent                     *event
);


/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */

/*
 * Form Class
 */

vformClass *vformGetDefaultClass (
  void
);

/*
 * Form
 */

void vformAddField (
  vform                        *form,
  vfield                       *field
);

void vformAppendItem (
  vform                        *form,
  vdialogItem                  *item
);

void vformArrange (
  vform                        *form,
  const vrect                  *rect
);

void vformCalcMinSize (
  vform                        *form,
  int                          *width,
  int                          *height
);

vform *vformClone (
  vform                        *form
);

void vformCopy (
  vform                        *form,
  vform                        *target
);

void vformCopyInit (
  vform                        *form,
  vform                        *target
);

vform *vformCreate (
  void
);

vform *vformCreateOfClass (
  vformClass                   *clas
);

void vformDeleteItem (
  vform                        *form,
  vdialogItem                  *item
);

void vformDestroy (
  vform                        *form
);

void vformDestroyLater (
  vform                        *form
);

void vformDisable (
  vform                        *form
);

void vformEnable (
  vform                        *form
);

vfield *vformFindFieldLinkedToItem (
  vform                        *form,
  const vname                  *itemTag
);

vsequence *vformFindAllItems (
  vform                        *form,
  const vname                  *tag
);

vdialogItem *vformFindItem (
  vform                        *form,
  const vname                  *tag
);

vdialogItem *vformFindItemRecursively (
  vform                        *form,
  const vname                  *tag
);

const vrect *vformGetBounds (
  vform                        *form
);

vformClass *vformGetClass (
  vform                        *form
);

vcontainer *vformGetContainer (
  vform                        *form
);

const vrect *vformGetContent (
  vform                        *form
);

const void *vformGetData (
  vform                        *form
);

vfield *vformGetField (
  vform                        *form,
  const vname                  *tag
);

vdialogItem *vformGetDefFocus (
  vform                        *form
);

vdialogItem *vformGetFocus (
  vform                        *form
);

vdialogItem *vformGetItem (
  vform                        *form
);

vdialogItem *vformGetItemAt (
  vform                        *form,
  int                           index
);

int vformGetItemCount (
  vform                        *form
);

int vformGetItemIndex (
  vform                        *form,
  vdialogItem                  *item
);

vdialogItemList *vformGetItemList (
  vform                        *form
);

int vformGetMinHeight (
  vform                        *form
);

int vformGetMinWidth (
  vform                        *form
);

vformNoteProc vformGetNotify (
  vform                        *form
);

vobject *vformGetObject (
  vform                        *form
);

vobservable *vformGetObservable (
  vform                        *form
);

vspringSolution *vformGetSolution (
  vform                        *form
);

const vchar *vformGetTitle (
  vform                        *form
);

vbool vformHasAutoScrollbarX (
  vform                        *form
);

vbool vformHasAutoScrollbarY (
  vform                        *form
);

vbool vformHasAutoScrollFocus (
  vform                        *form
);

int vformHasBorder (
  vform                        *form
);

vbool vformHasField (
  vform                        *form,
  vfield                       *field
);

int vformHasScrollX (
  vform                        *form
);

int vformHasScrollY (
  vform                        *form
);

void vformInit (
  vform                        *form
);

void vformInitOfClass (
  vform                        *form,
  vformClass                   *clas
);

int vformIsEnabled (
  vform                        *form
);

vbool vformIsDirty (
  vform                        *form
);

int vformIsFlat (
  vform                        *form
);

vbool vformIsItemLinked (
  vform                        *form,
  const vname                  *tag
);

void vformLinkField (
  vform                        *form,
  const vname                  *tag,
  vfield                       *field
);

vform *vformLoad (
  vresource                     resource
);

void vformLoadInit (
  vform                        *form,
  vresource                      resource
);

void vformRelinkFields (
  vform                        *form
);

void vformRemoveField (
  vform                        *form,
  vfield                       *field
);

void vformSetAutoScrollbarX (
  vform                        *form,
  vbool                         onOff
);

void vformSetAutoScrollbarY (
  vform                        *form,
  vbool                         onOff
);

void vformSetAutoScrollFocus (
  vform                        *form,
  vbool                         onOff
);

void vformSetBorder (
  vform                        *form,
  int                           onOff
);

void vformSetBounds (
  vform                        *form,
  const vrect                  *bounds
);

void vformSetData (
  vform                        *form,
  const void                   *data
);

void vformSetDirty (
  vform                        *form,
  int                           onOff
);

void vformSetFlat (
  vform                        *form,
  int                           onOff
);

void vformSetFocus (
  vform                        *form,
  vdialogItem                  *item
);

void vformSetItemIndex (
  vform                        *form,
  vdialogItem                  *item,
  int                           index
);

void vformSetMinHeight (
  vform                        *form,
  int                           height
);

void vformSetMinWidth (
  vform                        *form,
  int                           width
);

void vformSetNotify (
  vform                        *form,
  vformNoteProc                 noteProc
);

void vformSetScrollX (
  vform                        *form,
  int                           onOff
);

void vformSetScrollY (
  vform                        *form,
  int                           onOff
);

void vformSetSolution (
  vform                        *form,
  vspringSolution              *solution
);

void vformSetTitle (
  vform                        *form,
  const vchar                   *title
);

void vformSetTitleScribed (
  vform                        *form,
  vscribe                       *title
);

void vformStartup (
  void
);

void vformStore (
  vform                        *form,
  vresource                      resource
);

vbool vformTestSetFocus (
  vform                        *form,
  vdialogItem                  *item,
  vevent                       *event
);

void vformUnlinkField (
  vform                        *form,
  const vname                  *tag
);


/**********************************
   vformFieldIteratorClass
 **********************************/

vformFieldIteratorClass *vformGetDefaultFieldIteratorClass (
  void
);


/**********************************
    vformFieldIterator
 **********************************/

void vformDestroyFieldIterator (
  vformFieldIterator *iter
);

vformFieldIteratorClass *vformGetFieldIteratorClass (
  vformFieldIterator *iter
);

viterator *vformGetFieldIteratorIterator (
  vformFieldIterator *iter
);

vfield *vformGetFieldIteratorField (
  vformFieldIterator *iter
);

void vformInitFieldIterator (
  vformFieldIterator *iter,
  vform              *form
);

vbool vformNextFieldIterator (
  vformFieldIterator *iter
);


/*
 * * * * * * * * * * PRIVATE CONSTANTS * * * * * * * * * *
 */

enum {
  _vform_BooleanInterface,
  _vformNUM_NAMES
};

/*
 * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * *
 */

/*
 * form
 */

struct vform {
  vcontainer              container;
  unsigned                flags;
  int                     minWidth;
  int                     minHeight;
  vdict                  *fields;
  vdict                  *linkedItems;
  int                     fieldCount;
  vcommandSpace          *space;
};

#define vformCLASS(SUPER, FORM, NOTIFY)                                   \
  vcontainerCLASS (SUPER, FORM, NOTIFY);                                  \
  vclassMETHOD (vformADD_FIELD, (FORM *, vfield *));                      \
  vclassMETHOD_RET (vformFIND_ALL_ITEMS, vsequence *,                     \
                     (FORM *, const vname *));                            \
  vclassMETHOD_RET (vformFIND_FIELD_LINKED_TO_ITEM, vfield *,             \
                    (FORM *, const vname *));                             \
  vclassMETHOD_RET (vformFIND_ITEM_RECURSIVELY, vdialogItem *,            \
		    (FORM *, const vname *));                             \
  vclassMETHOD_RET (vformGET_FIELD, vfield *, (FORM *, const vname *));   \
  vclassMETHOD_RET (vformIS_ITEM_LINKED, vbool, (FORM *, const vname *)); \
  vclassMETHOD (vformLINK_FIELD, (FORM *, const vname *, vfield *));      \
  vclassMETHOD (vformRELINK_FIELDS, (FORM *));                            \
  vclassMETHOD (vformREMOVE_FIELD, (FORM *, vfield *));                   \
  vclassMETHOD (vformSET_AUTO_SCROLLBAR_X, (FORM *, vbool));              \
  vclassMETHOD (vformSET_AUTO_SCROLLBAR_Y, (FORM *, vbool));              \
  vclassMETHOD (vformSET_AUTO_SCROLL_FOCUS, (FORM *, vbool));             \
  vclassMETHOD (vformSET_DIRTY, (FORM *, int));                           \
  vclassMETHOD (vformSET_MIN_HEIGHT, (FORM *, int));                      \
  vclassMETHOD (vformSET_MIN_WIDTH, (FORM *, int));                       \
  vclassMETHOD (vformUNLINK_FIELD, (FORM *, const vname *))

struct vformClass {
  vformCLASS (vformClass, vform, vformNoteProc);
};

enum {
  _vformAUTO_SCROLLBAR_X  = 0x0001,
  _vformAUTO_SCROLLBAR_Y  = 0x0002,
  _vformAUTO_SCROLL_FOCUS = 0x0004,
  _vformIS_DIRTY          = 0x0008
};


#define vformFieldIteratorCLASS(SUPER, ITERATOR) \
    viteratorCLASS (SUPER, ITERATOR)

struct vformFieldIterator {
    viterator          iterator;
    vdictIterator      dictIter;
    vform             *form;
};

struct vformFieldIteratorClass {
    vformFieldIteratorCLASS (vformFieldIteratorClass,
		             vformFieldIterator);
};

/*
 * * * * * * * * * * PRIVATE VARIABLE DECLARATIONS * * * * * * * * * *
 */


/*
 * * * * * * * * * * PRIVATE FUNCTION PROTOTYPES * * * * * * * * * *
 */

void _vformValidate (
  vform                *form
);


/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * *
 */

/*
 * vform
 */

#define vformAppendItem(f,i) \
  vcontainerAppendItem (vformGetContainer (f), (i))

#define vformArrange(f,r) \
  vcontainerArrange (vformGetContainer (f), (r))

#define vformCalcMinSize(f,w,h) \
  vcontainerCalcMinSize (vformGetContainer (f), (w), (h))

#define vformClone(f) \
  ((vform *) vcontainerClone (vformGetContainer (f)))

#define vformCopy(f,t) \
  vcontainerCopy (vformGetContainer (f), vformGetContainer (t))

#define vformCopyInit(f,t) \
  vcontainerCopyInit (vformGetContainer (f), vformGetContainer (t))

#define vformCreate() \
  vformCreateOfClass (vformGetDefaultClass ())

#define vformCreateOfClass(c) \
  ((vform *) vobjectCreateOfClass((vobjectClass *)(c)))

#define vformDeleteItem(f,i) \
  vcontainerDeleteItem (vformGetContainer (f), (i))

#define vformDestroy(f) \
  vcontainerDestroy (vformGetContainer (f))

#define vformDestroyLater(f) \
  vobjectDestroyLater (vcontainerGetObject (vformGetContainer (f)))

#define vformDisable(f) \
  vcontainerDisable (vformGetContainer (f))

#define vformEnable(f) \
  vcontainerEnable (vformGetContainer (f))

#define vformFindItem(f,t) \
  vcontainerFindItem (vformGetContainer (f), (t))

#define vformGetBounds(f) \
  vcontainerGetBounds (vformGetContainer (f))

#define vformGetClass(f) \
  ((vformClass*)vcontainerGetClass (vformGetContainer (f)))

#define vformGetContainer(f) \
  vportBASE_OBJECT (f, container)

#define vformGetContent(f) \
  vcontainerGetContent (vformGetContainer (f))

#define vformGetData(f) \
  vcontainerGetData (vformGetContainer (f))

#define vformGetDefFocus(f) \
  vcontainerGetDefFocus (vformGetContainer (f))

#define vformGetFocus(f) \
  vcontainerGetFocus (vformGetContainer (f))

#define vformGetItem(f) \
  vcontainerGetItem (vformGetContainer (f))

#define vformGetItemAt(f,i) \
  vcontainerGetItemAt (vformGetContainer (f), (i))

#define vformGetItemCount(f) \
  vcontainerGetItemCount (vformGetContainer (f))

#define vformGetItemIndex(f,d) \
  vcontainerGetItemIndex (vformGetContainer (f), (d))

#define vformGetItemList(f) \
  vcontainerGetItemList (vformGetContainer (f))

#define vformGetMinHeight(f) \
  ((f)->minHeight)

#define vformGetMinWidth(f) \
  ((f)->minWidth)

#define vformGetNotify(f) \
  ((vformNoteProc) vcontainerGetNotify (vformGetContainer (f)))

#define vformGetObject(f) \
  vcontainerGetObject (vformGetContainer (f))

#define vformGetObservable(f) \
  vobjectGetObservable (vformGetObject (f))

#define vformGetSolution(f) \
  vcontainerGetSolution (vformGetContainer (f))

#define vformGetTitle(f) \
  vcontainerGetTitle (vformGetContainer (f))

#define vformHasAutoScrollbarX(f) \
  ((vbool)(((f)->flags & _vformAUTO_SCROLLBAR_X) != 0))

#define vformHasAutoScrollbarY(f) \
  ((vbool)(((f)->flags & _vformAUTO_SCROLLBAR_Y) != 0))

#define vformHasAutoScrollFocus(f) \
  ((vbool)(((f)->flags & _vformAUTO_SCROLL_FOCUS) != 0))

#define vformHasBorder(f) \
  vcontainerHasBorder (vformGetContainer (f))

#define vformHasField(f,fld) \
  ((vfieldGetTag (fld) != NULL) && \
   (vdictLoad ((f)->fields, vfieldGetTag (fld)) != NULL))

#define vformHasScrollX(f) \
  vcontainerHasScrollX (vformGetContainer (f))

#define vformHasScrollY(f) \
  vcontainerHasScrollY (vformGetContainer (f))

#define vformInit(f) \
  vformInitOfClass (f, vformGetDefaultClass ())

#define vformInitOfClass(f,c) \
  vcontainerInitOfClass (vformGetContainer (f), (vformClass *)(c))

#define vformIsDirty(f) \
  (vbool)((f)->flags & _vformIS_DIRTY)

#define vformIsEnabled(f) \
  vcontainerIsEnabled (vformGetContainer (f))

#define vformIsFlat(f) \
  vcontainerIsFlat (vformGetContainer (f))

#define vformLoad(r) \
  ((vform *) vobjectLoad (r))

#define vformLoadInit(f,r) \
  vcontainerLoadInit (vformGetContainer (f), (r))

#define vformSetBorder(f,b) \
  vcontainerSetBorder (vformGetContainer (f), (b))

#define vformSetBounds(f,r) \
  vcontainerSetBounds (vformGetContainer (f), (r))

#define vformSetData(f,d) \
  vcontainerSetData (vformGetContainer (f), (d))

#define vformSetFlat(f,b) \
  vcontainerSetFlat (vformGetContainer (f), (b))

#define vformSetFocus(f,i) \
  vcontainerSetFocus (vformGetContainer (f), (i))

#define vformSetItemIndex(f,i,x) \
  vcontainerSetItemIndex (vformGetContainer (f), (i), (x))

#define vformSetNoteProc(f,p) \
  vcontainerSetNotify (vformGetContainer (f), (p))

#define vformSetScrollX(f,b) \
  vcontainerSetScrollX (vformGetContainer (f), (b))

#define vformSetScrollY(f,b) \
  vcontainerSetScrollY (vformGetContainer (f), (b))

#define vformSetSolution(f,s) \
  vcontainerSetSolution (vformGetContainer (f), (s))

#define vformSetTitle(f,t) \
  vcontainerSetTitle (vformGetContainer (f), (t))

#define vformSetTitleScribed(f,t) \
  vcontainerSetTitleScribed (vformGetContainer (f), (t))

#define vformStore(f,r) \
  vcontainerStore (vformGetContainer (f), (r))

#define vformTestSetFocus(f,i,e) \
  vcontainerTestSetFocus (vformGetContainer (f), (i), (e))

#if !vdebugDEBUG
#define _vformValidate(f)
#endif


/**********************************
    vformFieldIterator
 **********************************/

#define vformGetFieldIteratorClass(i) \
  ((vformFieldIteratorClass *) \
   viteratorGetClass (vformGetFieldIteratorIterator (i)))

#define vformGetFieldIteratorIterator(i) \
  vportBASE_OBJECT (i, iterator)
 
#define vformDestroyFieldIterator(i) \
  viteratorDestroy(vformGetFieldIteratorIterator(i))

#define vformGetFieldIteratorField(i) \
  ((vfield *) \
   viteratorGetElement(vformGetFieldIteratorIterator(i)))

#define vformNextFieldIterator(i) \
  viteratorNext(vformGetFieldIteratorIterator(i))



/*
 * * * * * * * * * * PRIVATE FUNCTION MESSAGE DEFINITIONS * * * * * * * * * *
 */

/*
 * vform
 */

#define vformAddField(f,fld) \
  vclassSend (vformGetClass (f), vformADD_FIELD, (f, fld))

#define vformFindAllItems(f,t) \
  vclassSend (vformGetClass (f), vformFIND_ALL_ITEMS, (f, t))

#define vformFindFieldLinkedToItem(f,t) \
  vclassSend (vformGetClass (f), vformFIND_FIELD_LINKED_TO_ITEM, (f, t))

#define vformFindItemRecursively(f,t) \
  vclassSend (vformGetClass (f), vformFIND_ITEM_RECURSIVELY, (f, t))

#define vformGetField(f,t) \
  vclassSend (vformGetClass (f), vformGET_FIELD, (f, t))

#define vformIsItemLinked(f,i) \
  vclassSend (vformGetClass (f), vformIS_ITEM_LINKED, (f, i))

#define vformLinkField(f,i,fld) \
  vclassSend (vformGetClass (f), vformLINK_FIELD, (f, i, fld))

#define vformRelinkFields(f) \
  vclassSend (vformGetClass (f), vformRELINK_FIELDS, (f))

#define vformRemoveField(f,fld) \
  vclassSend (vformGetClass (f), vformREMOVE_FIELD, (f, fld))

#define vformSetDirty(f,b) \
  vclassSend (vformGetClass(f), vformSET_DIRTY, (f, b))

#define vformSetAutoScrollbarX(f,b) \
  vclassSend (vformGetClass (f), vformSET_AUTO_SCROLLBAR_X, (f,b))

#define vformSetAutoScrollbarY(f,b) \
  vclassSend (vformGetClass (f), vformSET_AUTO_SCROLLBAR_Y, (f,b))

#define vformSetAutoScrollFocus(f,b) \
  vclassSend (vformGetClass (f), vformSET_AUTO_SCROLL_FOCUS, (f,b))

#define vformSetMinHeight(f,h) \
  vclassSend (vformGetClass (f), vformSET_MIN_HEIGHT, (f,h))

#define vformSetMinWidth(f,w) \
  vclassSend (vformGetClass (f), vformSET_MIN_WIDTH, (f,w))

#define vformUnlinkField(f,i) \
  vclassSend (vformGetClass (f), vformUNLINK_FIELD, (f, i))


vportEND_CPLUSPLUS_EXTERN_C


#endif /* #ifndef vformINCLUDED */


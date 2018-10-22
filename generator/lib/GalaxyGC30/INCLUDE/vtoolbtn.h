/* $Id: vtoolbtn.h,v 1.7 1997/09/29 20:20:55 bill Exp $ */

/*------------------------------------------------------------------------
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
    vtoolbtn.h                                                           *
                                                                         *
    C Header file for Toolbar Buttons                                    *
                                                                         *
    Copyright (c) 1997 Visix Software Inc.                               *
    All rights reserved                                                  *
                                                                         *
  -----------------------------------------------------------------------*/

#ifndef vtoolbuttonINCLUDED
#define vtoolbuttonINCLUDED

#ifndef vbuttonINCLUDED
#include vbuttonHEADER
#endif

#ifndef vcontainerINCLUDED
#include vcontainerHEADER
#endif

#ifndef vfieldINCLUDED
#include vfieldHEADER
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C

/*-------------------------------------------------------------------------
 * * * PUBLIC CONSTANT DEFINITIONS  * * * * * * * * * * * * * * * * * * * *
  ------------------------------------------------------------------------*/

/* vtoolbuttonGroupField attribute id's */
enum {
  vtoolbuttonGroupFieldID_ATTRIBUTE_SELECTION      = vfieldNEXT_ID_ATTRIBUTE,
  vtoolbuttonGroupFieldNEXT_ID_ATTRIBUTE
};

/*-------------------------------------------------------------------------
 * * * PUBLIC TYPE DEFINITIONS  * * * * * * * * * * * * * * * * * * * * * *
  ------------------------------------------------------------------------*/

typedef struct vtoolbutton		vtoolbutton;
typedef struct vtoolbuttonClass 	vtoolbuttonClass;

typedef struct vtoolbuttonGroupField 		vtoolbuttonGroupField;
typedef struct vtoolbuttonGroupFieldClass	vtoolbuttonGroupFieldClass;

/*-------------------------------------------------------------------------
 * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * * * * * * * * * * * * *
  ------------------------------------------------------------------------*/

/*
 *  vtoolbutton function prototypes
 */

/* Class management */

void vtoolbuttonStartup(
    void
    );

vtoolbuttonClass *vtoolbuttonGetDefaultClass(
    void
    );

vtoolbuttonClass *vtoolbuttonGetClass(
    vtoolbutton		*button
    );

vtoolbutton *vtoolbuttonCreateOfClass(
    vtoolbuttonClass	*clas
    );

vtoolbutton *vtoolbuttonCreate(
    void
    );

vtoolbutton *vtoolbuttonClone(
    vtoolbutton		*button
    );

void vtoolbuttonInit(
    vtoolbutton		*button
    );

void vtoolbuttonDestroy(
    vtoolbutton		*button
    );

void vtoolbuttonCopy(
    vtoolbutton		*button,
    vtoolbutton		*target
    );

void vtoolbuttonCopyInit(
    vtoolbutton		*button,
    vtoolbutton		*target
    );

vtoolbutton *vtoolbuttonLoad(
    vresource		resource
    );

void vtoolbuttonLoadInit(
    vtoolbutton		*button,
    vresource		 resource
    );

void vtoolbuttonStore(
    vtoolbutton		*button,
    vresource		 resource
    );

/* Superclass API equivalents */

vbutton *vtoolbuttonGetButton(
    vtoolbutton		*button
    );

vcontrol *vtoolbuttonGetControl(
    vtoolbutton		*button
    );

vdialogItem *vtoolbuttonGetItem(
    vtoolbutton		*button
    );


void vtoolbuttonBlink(
    vtoolbutton         *button
    );

int vtoolbuttonIsToggle(
    vtoolbutton         *button
    );

void vtoolbuttonSetToggle(
    vtoolbutton         *button,
    int                  isToggle
    );

void vtoolbuttonSetMax(
    vtoolbutton         *button,
    int                  max
    );

void vtoolbuttonSetMin(
    vtoolbutton         *button,
    int                  min
    );

void vtoolbuttonSetValue(
    vtoolbutton         *button,
    int                  value
    );

int vtoolbuttonGetMax(
    vtoolbutton         *button
    );

int vtoolbuttonGetMin(
    vtoolbutton         *button
    );

int vtoolbuttonGetValue(
    vtoolbutton         *button
    );


/*
 *  vtoolbuttonGroupField function prototypes
 */

vtoolbuttonGroupFieldClass *vtoolbuttonGetDefaultGroupFieldClass(
    void
    );

vfield *vtoolbuttonGetGroupFieldField(
    vtoolbuttonGroupField	*field
    );

vtoolbuttonGroupFieldClass *vtoobuttonGetGroupFieldClass(
    vtoolbuttonGroupField	*field
    );

vtoolbuttonGroupField *vtoolbuttonCreateGroupFieldOfClass(
    vtoolbuttonGroupFieldClass	*clas
    );

vtoolbuttonGroupField *vtoolbuttonCreateGroupField(
    void
    );

vtoolbuttonGroupField *vtoolbuttonCloneGroupField(
    vtoolbuttonGroupField	*field
    );

void vtoolbuttonInitGroupFieldOfClass(
    vtoolbuttonGroupField	*field,
    vtoolbuttonGroupFieldClass	*clas
    );

void vtoolbuttonInitGroupField(
    vtoolbuttonGroupField	*field
    );

void vtoolbuttonDestroyGroupField(
    vtoolbuttonGroupField	*field
    );

void vtoolbuttonCopyGroupField(
    vtoolbuttonGroupField	*source,
    vtoolbuttonGroupField	*target
    );

void vtoolbuttonCopyInitGroupField(
    vtoolbuttonGroupField	*source,
    vtoolbuttonGroupField	*target
    );

vtoolbuttonGroupField *vtoolbuttonLoadGroupField(
    vresource			 res
    );

void vtoolbuttonStoreGroupField(
    vtoolbuttonGroupField	*field,
    vresource			 res
    );

void vtoolbuttonSetGroupFieldSelection(
    vtoolbuttonGroupField	*field,
    const vname			*selection_tag
    );

const vname *vtoolbuttonGetGroupFieldSelection(
    vtoolbuttonGroupField	*field
    );


/*-------------------------------------------------------------------------
 * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * * * * * * * * * * * * * *
  ------------------------------------------------------------------------*/

struct vtoolbutton {
    vbutton      button;
};

#define vtoolbuttonCLASS(CLASS, BUTTON, NOTIFY)			           \
  vbuttonCLASS(CLASS, BUTTON, NOTIFY)

struct vtoolbuttonClass {
    vtoolbuttonCLASS(vtoolbuttonClass, vtoolbutton, vbuttonNoteProc);
};


/* vtoolbuttonGroupField */

struct vtoolbuttonGroupField {
    vfield        field;
    const vname  *selection;
};

#define vtoolbuttonGroupFieldCLASS(SUPER, FIELD)		           \
  vfieldCLASS(SUPER, FIELD);                                               \
  vclassMETHOD(vtoolbuttonGroupFieldSET_SELECTION,                         \
               (FIELD *field, const vname *selection))

struct vtoolbuttonGroupFieldClass {
    vtoolbuttonGroupFieldCLASS(vtoolbuttonGroupFieldClass,
                               vtoolbuttonGroupField);
};


/*-------------------------------------------------------------------------
 * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * * * * * * * * *
  ------------------------------------------------------------------------*/

/*
 *  vtoolbutton macros
 */

#define vtoolbuttonGetButton(b)   vportBASE_OBJECT(b, button )
#define vtoolbuttonGetControl(b)  vbuttonGetControl(vtoolbuttonGetButton(b))
#define vtoolbuttonGetItem(b)     vbuttonGetItem(vtoolbuttonGetButton(b))
#define vtoolbuttonGetClass(b) \
    ((vtoolbuttonClass*)vdialogGetItemClass(vtoolbuttonGetItem(b)))

#define vtoolbuttonCreateOfClass(c) \
    ((vtoolbutton*)vdialogCreateItemOfClass((vdialogItemClass*)(c)))
#define vtoolbuttonCreate() \
    vtoolbuttonCreateOfClass(vtoolbuttonGetDefaultClass())

#define vtoolbuttonClone(b)  \
    ((vtoolbutton*)vbuttonClone(vtoolbuttonGetButton(b)))
#define vtoolbuttonInit(b)  vbuttonInit(vtoolbuttonGetButton(b))
#define vtoolbuttonDestroy(b) vbuttonDestroy(vtoolbuttonGetButton(b))
#define vtoolbuttonCopy(b, t) \
    vbuttonCopy(vtoolbuttonGetButton(b), vtoolbuttonGetButton(t))
#define vtoolbuttonCopyInit(b, t) \
    vbuttonCopyInit(vtoolbuttonGetButton(b), vtoolbuttonGetButton(t))
#define vtoolbuttonLoad(r)  ((vtoolbutton*)vbuttonLoad(r))
#define vtoolbuttonLoadInit(b, r)  vbuttonLoadInit(vtoolbuttonGetButton(b), r)
#define vtoolbuttonStore(b,r)  vbuttonStore(vtoolbuttonGetButton(b), r)

#define vtoolbuttonBlink(b)       vbuttonBlink(vtoolbuttonGetButton(b))
#define vtoolbuttonIsToggle(b)    vbuttonIsToggle(vtoolbuttonGetButton(b))
#define vtoolbuttonSetToggle(b, t) vbuttonSetToggle(vtoolbuttonGetButton(b), t)

#define vtoolbuttonSetMax(b, m)   vbuttonSetMax(vtoolbuttonGetButton(b),m)
#define vtoolbuttonSetMin(b, m)   vbuttonSetMin(vtoolbuttonGetButton(b),m)
#define vtoolbuttonSetValue(b,v)  vbuttonSetValue(vtoolbuttonGetButton(b),v)
#define vtoolbuttonGetMax(b)      vbuttonGetMax(vtoolbuttonGetButton(b))
#define vtoolbuttonGetMin(b)      vbuttonGetMin(vtoolbuttonGetButton(b))
#define vtoolbuttonGetValue(b)    vbuttonGetValue(vtoolbuttonGetButton(b))

/* Toolbar Group Field */
#define vtoolbuttonGetGroupFieldField(f) ((vfield*)f)
#define vtoolbuttonGetGroupFieldClass(f) \
  ((vtoolbuttonGroupFieldClass*)vfieldGetClass(vtoolbuttonGetGroupFieldField(f)))
#define vtoolbuttonCreateGroupFieldOfClass(c) \
  ((vtoolbuttonGroupField*)vfieldCreateOfClass((vfieldClass*)(c)))
#define vtoolbuttonCreateGroupField() \
  vtoolbuttonCreateGroupFieldOfClass(vtoolbuttonGetDefaultGroupFieldClass())
#define vtoolbuttonCloneGroupField(f) \
  ((vtoolbuttonGroupField*)vfieldClone(vtoolbuttonGetGroupFieldField(f)))
#define vtoolbuttonInitGroupFieldOfClass(f, c) \
  vfieldInitOfClass(vtoolbuttonGetGroupFieldField(f), (vfieldClass*)(c))
#define vtoolbuttonInitGroupField(f) \
  vtoolbuttonInitGroupFieldOfClass(f, vtoolbuttonGetDefaultGroupFieldClass())
#define vtoolbuttonDestroyGroupField(f) \
  vfieldDestroy(vtoolbuttonGetGroupFieldField(f))
#define vtoolbuttonCopyGroupField(s, t) \
  vfieldCopy(vtoolbuttonGetGroupFieldField(s), vtoolbuttonGetGroupFieldField(t))
#define vtoolbuttonCopyInitGroupField(s, t) \
  vfieldCopyInit(vtoolbuttonGetGroupFieldField(s),  \
                  vtoolbuttonGetGroupFieldField(t))
#define vtoolbuttonLoadGroupField(r) ((vtoolbuttonGroupField*)vfieldLoad(r))
#define vtoolbuttonLoadInitGroupField(f, s) \
  ((vtoolbuttonGroupField*)vfieldLoadInit(vtoolbuttonGetGroupFieldField(f), s))
#define vtoolbuttonStoreGroupField(f, s)  \
  vfieldStore(vtoolbuttonGetGroupFieldField(f), s)

#define vtoolbuttonSetGroupFieldSelection(f, s) \
  vclassSend(vtoolbuttonGetGroupFieldClass(f),  \
             vtoolbuttonGroupFieldSET_SELECTION, (f, s))

#define vtoolbuttonGetGroupFieldSelection(f) \
  ((f)->selection)


vportEND_CPLUSPLUS_EXTERN_C

#endif /* vtoolbuttonINCLUDED */

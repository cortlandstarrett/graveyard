/* $Id: vtoolchanger.h,v 1.2 1997/09/11 23:34:24 robert Exp $ */

/************************************************************

    vtoolchanger.h

    C Interface file for Toolbar Item Changer

    Copyright (c) 1997 Visix Software Inc.
    All rights reserved

************************************************************/

#ifndef vtoolchangerINCLUDED
#define vtoolchangerINCLUDED

#ifndef vcontainerINCLUDED
#include vcontainerHEADER
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * * * * * * * * * * PUBLIC CONSTANT DEFINITIONS * * * * * * * * * *
 */


/*
 * * * * * * * * * * PUBLIC TYPE DEFINITIONS * * * * * * * * * * * *
 */

typedef struct vtoolchanger 		vtoolchanger;
typedef struct vtoolchangerClass	vtoolchangerClass;

/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * * *
 */

/* Class and object management */
void vtoolchangerStartup( 
    void 
    );

vtoolchangerClass *vtoolchangerGetDefaultClass(
    void
    );

vtoolchangerClass *vtoolchangerGetClass(
    vtoolchanger 	*changer
    );

vtoolchanger *vtoolchangerCreateOfClass(
    vtoolchangerClass 	*clas
    );

vtoolchanger *vtoolchangerCreate(
     void
     );

vtoolchanger *vtoolchangerClone(
    vtoolchanger	*changer
    );

void vtoolchangerInitOfClass(
    vtoolchanger	*changer,
    vtoolchangerClass	*clas
    );

void vtoolchangerInit(
    vtoolchanger	*changer
    );

void vtoolchangerDestroy(
    vtoolchanger	*changer
    );

void vtoolchangerCopy(
    vtoolchanger	*changer,
    vtoolchanger	*target
    );

void vtoolchangerCopyInit(
    vtoolchanger	*changer,
    vtoolchanger	*target
    );

vtoolchanger *vtoolchangerLoad(
    vresource 		res
    );

vtoolchanger *vtoolchangerLoadInit(
    vtoolchanger	*changer,
    vresource 		 res
    );

vtoolchanger *vtoolchangerStore(
    vtoolchanger	*changer,
    vresource 		 res
    );

/* Inheritance accessors */

vcontainer *vtoolchangerGetContainer(
    vtoolchanger 	*changer
    );

vdialogItem *vtoolchangerGetItem(
    vtoolchanger 	*changer
    );

vobjectAttributed *vtoolchangerGetObject(
    vtoolchanger 	*changer
    );

vobservable *vtoolchangerGetObservable(
    vtoolchanger 	*changer
    );

/* Superclass API equivalents */


/*
 * * * * * * * * * * PRIVATE CONSTANT DEFINITIONS * * * * * * * * * *
 */

/*
 * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * *
 */

struct vtoolchanger {
    vcontainer		 container;
};

#define vtoolchangerCLASS(SUPER, TOOLCHANGER, NOTIFY) \
        vcontainerCLASS(SUPER, TOOLCHANGER, NOTIFY)

struct vtoolchangerClass {
    vtoolchangerCLASS(vtoolchangerClass, vtoolchanger, vcontainerNoteProc);
};

/*
 * * * * * * * * * * * * PRIVATE GLOBAL VARIABLES * * * * * * * * * * * * *
 */
/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * *
 */

/* Class and object management */

#define vtoolchangerGetClass(t)  \
  ((vtoolchangerClass*)vcontainerGetClass(vtoolchangerGetContainer(t)))
#define vtoolchangerCreateOfClass(c) \
  ((vtoolchanger*)vcontainerCreateOfClass((vcontainerClass*)(c)))
#define vtoolchangerCreate() \
  vtoolchangerCreateOfClass(vtoolchangerGetDefaultClass())
#define vtoolchangerClone(t) \
  ((vtoolchanger*)vcontainerClone(vtoolchangerGetContainer(t)))
#define vtoolchangerInitOfClass(t, c)  \
  vformInitOfClass(vtoolchangerGetContainer(t), (vformClass*)(c))
#define vtoolchangerInit(t) vtoolchangerInitOfClass(t, vtoolchangerGetDefaultClass())
#define vtoolchangerDestroy(t) vformDestroy(vtoolchangerGetContainer(t))
#define vtoolchangerCopy(s, t) \
  vformCopy(vtoolchangerGetContainer(s), vtoolchangerGetContainer(t))
#define vtoolchangerCopyInit(s, t) \
  vformCopyInit(vtoolchangerGetContainer(s), vtoolchangerGetContainer(t))
#define vtoolchangerLoad(r) ((vtoolchanger*)vformLoad(r))
#define vtoolchangerLoadInit(t, r) \
  ((vtoolchanger*)vformLoadInit(vtoolchangerGetContainer(t), r))
#define vtoolchangerStore(t, r) vformStore(vtoolchangerGetContainer(t), r);

/* Inheritance accessors */

#define vtoolchangerGetContainer(t) vportBASE_OBJECT(t, container)
#define vtoolchangerGetItem(t) \
  vcontainerGetItem(vtoolchangerGetContainer(t))
#define vtoolchangerGetObject(t) \
  vcontainerGetObject(vtoolchangerGetContainer(t))
#define vtoolchangerGetObservable(t) \
  vcontainerGetObservable(vtoolchangerGetContainer(t))


vportEND_CPLUSPLUS_EXTERN_C

#endif /* vtoolchangerINCLUDED */

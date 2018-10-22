/* $Id: vcursor.h,v 1.12 1996/06/05 00:17:00 sean Exp $ */

/************************************************************

    vcursor.h

    C Interface file for the Cursor Manager

    (c) Copyright Visix Software Inc.
    All rights reserved

************************************************************/

#ifndef vcursorINCLUDED
#define vcursorINCLUDED

#ifndef  vportINCLUDED
#include <vport.h>
#endif

#ifndef  vresourceINCLUDED
#include vresourceHEADER
#endif

#ifndef  vpixmapINCLUDED
#include vpixmapHEADER
#endif

#ifndef  vimageINCLUDED
#include vimageHEADER
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * * * * * * * * * * PUBLIC TYPE DEFINITIONS * * * * * * * * * *
 */

typedef struct vcursor              vcursor;
typedef struct vcursorClass         vcursorClass;

/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */

void vcursorStartup(void);


vcursorClass *vcursorGetDefaultClass(
    void
    );

vcursor *vcursorCreateOfClass(
    vcursorClass                    *clas
    );

vcursor *vcursorCreate(
    void
    );

vcursor *vcursorClone(
    vcursor                        *cursor
    );

void vcursorInitOfClass(
    vcursor                        *cursor,
    vcursorClass                   *clas
    );

void vcursorInit(
    vcursor                        *cursor
    );

void vcursorDestroy(
    vcursor                        *cursor
    );

void vcursorCopy(
    vcursor                        *cursor,
    vcursor                        *target
    );

void vcursorCopyInit(
    vcursor                        *cursor,
    vcursor                        *target
    );

vcursor *vcursorLoad(
    vresource                       resource
    );

void vcursorLoadInit(
    vcursor                        *cursor,
    vresource                       resource
    );

void vcursorStore(
    vcursor                        *cursor,
    vresource                       resource
    );

void vcursorDump(
    vcursor                        *cursor,
    FILE                           *stream
    );

void vcursorSetHot(
    vcursor                        *cursor,
    int                             x, 
    int                             y
    );

vimage *vcursorGetImage(
    vcursor                        *cursor
    );

vpixmap *vcursorGetPixmap(
    vcursor                        *cursor
    );

vobject *vcursorGetObject(
    vcursor                        *cursor
    );

vobservable *vcursorGetObservable(
    vcursor                        *cursor
    );

vloadable *vcursorGetLoadable(
    vcursor                        *cursor
    );

vinstance *vcursorGetInstance(
    vcursor                        *cursor
    );

vcursorClass *vcursorGetClass(
    vcursor                        *cursor
    );

int vcursorGetHotX(
    vcursor                        *cursor
    );

int vcursorGetHotY(
    vcursor                        *cursor
    );

const void *vcursorGetData(
    vcursor                         *cursor
    );

void vcursorSetData(
    vcursor                         *cursor,
    const void                      *data
    );

/*
 * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * *
 */

struct vcursor {
    vimage		            image;
    vimageDimension                 hotX, hotY;
};

#define vcursorCLASS(SUPER, CURSOR)                                           \
    vimageCLASS(SUPER, CURSOR);                                               \
    vclassMETHOD(vcursorSET_HOT, (CURSOR *cursor, int x, int y))

struct vcursorClass {
    vcursorCLASS(vcursorClass, vcursor);
};

/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * *
 */

#define vcursorGetImage(c)          vportBASE_OBJECT(c, image)
#define vcursorGetPixmap(c)	    vimageGetPixmap(vcursorGetImage(c))
#define vcursorGetObject(c)	    vpixmapGetObject(vcursorGetPixmap(c))
#define vcursorGetObservable(c)	    vobjectGetObservable(vcursorGetObject(c))
#define vcursorGetLoadable(c)	    vobservableGetLoadable(vcursorGetObservable(c))
#define vcursorGetInstance(c)	    vloadableGetInstance(vcursorGetLoadable(c))

#define vcursorCreateOfClass(c) \
    ((vcursor*)vimageCreateOfClass((vimageClass*)(c)))
#define vcursorCreate() \
    vcursorCreateOfClass(vcursorGetDefaultClass())
#define vcursorLoad(r) \
    ((vcursor*)vloadableLoadOfSubclass(r, (vloadableClass*) \
				       vcursorGetDefaultClass()))
#define vcursorLoadInit(c, r) \
    vloadableLoadInitOfSubclass(vcursorGetLoadable(c), (r), (vloadableClass*) \
				vcursorGetDefaultClass())
#define vcursorClone(c) \
    ((vcursor*)vloadableCloneOfSubclass(vcursorGetLoadable(c), \
					(vloadableClass*) \
					vcursorGetDefaultClass()))
#define vcursorCopyInit(c, s) \
    vloadableCopyInitOfSubclass(vcursorGetLoadable(c), \
				vcursorGetLoadable(s), \
				(vloadableClass*) vcursorGetDefaultClass()))
#define vcursorInit(c) \
    vcursorInitOfClass(c, vcursorGetDefaultClass())
#define vcursorDestroy(c) \
    vimageDestroy(vcursorGetImage(c))

#define vcursorGetData(c)    vimageGetData(vcursorGetImage(c))
#define vcursorSetData(c, d) vimageSetData(vcursorGetImage(c), (d))

#define vcursorGetClass(c) \
    ((vcursorClass*)vimageGetClass(vcursorGetImage(c)))
#define vcursorGetHotX(c)         ((c)->hotX)
#define vcursorGetHotY(c)         ((c)->hotY)

/*
 * * * * * * * * * * PRIVATE FUNCTION MESSAGE DEFINITIONS * * * * * * * * * *
 */

#define vcursorCopy(c, t) \
    vclassSend(vcursorGetClass(c), vobjectCOPY, (c, t))
#define vcursorStore(c, r) \
    vclassSend(vcursorGetClass(c), vobjectSTORE, (c, r))
#define vcursorDump(c, s) \
    vclassSend(vcursorGetClass(c), vobjectDUMP, (c, s))
#define vcursorSetHot(c, x, y) \
    vclassSend(vcursorGetClass(c), vcursorSET_HOT, (c, x, y))

vportEND_CPLUSPLUS_EXTERN_C

#endif /* #ifndef vcursorINCLUDED */


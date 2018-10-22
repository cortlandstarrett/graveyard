/* $Id: vpanecont.h,v 1.3 1997/06/30 17:40:22 robert Exp $ */

/******************************************************************************

    vpanecont.h

    C Interface to the Pane Container Manager

    (c) Copyright Visix Software Inc.
    All rights reserved

******************************************************************************/

#ifndef vpanecontainerINCLUDED
#define vpanecontainerINCLUDED

#ifndef  vportINCLUDED
#include <vport.h>
#endif

#ifndef  vcontainerINCLUDED
#include vcontainerHEADER
#endif


vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * * * * * * * * * * * PUBLIC TYPE DEFINITIONS * * * * * * * * * * *
 */

/*
 * pane containers
 */

typedef struct vpanecontainer                   vpanecontainer;
typedef struct vpanecontainerClass              vpanecontainerClass;

/*
 * * * * * * * * * * PUBLIC CONSTANT DEFINITIONS * * * * * * * * * *
 */

enum {
    vpanecontainerHORIZONTAL           = 0,
    vpanecontainerVERTICAL             = 1,

    vpanecontainerLEFT_JUSTIFY         = 0,
    vpanecontainerRIGHT_JUSTIFY        = 1,
    vpanecontainerBOTTOM_JUSTIFY       = vpanecontainerLEFT_JUSTIFY,
    vpanecontainerTOP_JUSTIFY          = vpanecontainerRIGHT_JUSTIFY
};

/*
 * pane containers
 */

enum {
    vpanecontainerNEXT_ID_ATTRIBUTE               = vcontainerNEXT_ID_ATTRIBUTE
};

enum {
    vpanecontainerNEXT_SELECT                     = vcontainerNEXT_SELECT
};

/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */

void vpanecontainerStartup(
    void
    );

/*
 * pane containers
 */

/**** inherited methods ****/

vpanecontainerClass *vpanecontainerGetDefaultClass(
    void
    );

vpanecontainer *vpanecontainerCreateOfClass(
    vpanecontainerClass            *clas
    );

vpanecontainer *vpanecontainerCreate(
    void
    );

vpanecontainer *vpanecontainerClone(
    vpanecontainer                 *pane
    );

void vpanecontainerInitOfClass(
    vpanecontainer                 *pane,
    vpanecontainerClass            *clas
    );

void vpanecontainerInit(
    vpanecontainer                 *pane
    );

void vpanecontainerDestroy(
    vpanecontainer                 *pane
    );

void vpanecontainerCopy(
    vpanecontainer                 *pane,
    vpanecontainer                 *target
    );

void vpanecontainerCopyInit(
    vpanecontainer                 *pane,
    vpanecontainer                 *target
    );

vpanecontainer *vpanecontainerLoad(
    vresource                       resource
    );

void vpanecontainerLoadInit(
    vpanecontainer                 *pane,
    vresource                       resource
    );

void vpanecontainerStore(
    vpanecontainer                 *pane,
    vresource                       resource
    );

void vpanecontainerEnable(
    vpanecontainer                 *pane
    );

void vpanecontainerDisable(
    vpanecontainer                 *pane
    );

void vpanecontainerSetData(
    vpanecontainer                 *pane,
    const void                     *data
    );

void vpanecontainerSetTitle(
    vpanecontainer                 *pane,
    const vchar                    *title
    );

void vpanecontainerSetTitleScribed(
    vpanecontainer                 *pane,
    vscribe                        *title
    );

void vpanecontainerSetBorder(
    vpanecontainer                 *pane,
    int                             flag
    );

void vpanecontainerSetBounds(
    vpanecontainer                 *pane,
    const vrect                    *bounds
    );

vcontainer *vpanecontainerGetContainer(
    vpanecontainer                 *pane
    );

vpanecontainerClass *vpanecontainerGetClass(
    vpanecontainer                 *pane
    );

const void *vpanecontainerGetData(
    vpanecontainer                 *pane
    );

const vchar *vpanecontainerGetTitle(
    vpanecontainer                 *pane
    );

int vpanecontainerIsEnabled(
    vpanecontainer                 *pane
    );

int vpanecontainerHasBorder(
    vpanecontainer                 *pane
    );

const vrect *vpanecontainerGetContent(
    vpanecontainer                 *pane
    );

const vrect *vpanecontainerGetBounds(
    vpanecontainer                 *pane
    );

/*** pane-specific methods ***/

void vpanecontainerSetItem(
    vpanecontainer                 *pane,
    vdialogItem                    *item
    );

vdialogItem *vpanecontainerGetItem(
    vpanecontainer                 *pane
    );

void vpanecontainerSetJustification(
    vpanecontainer                 *pane,
    int                             axis,
    int                             justify
    );

void vpanecontainerSetHorizJustification(
    vpanecontainer                 *pane,
    int                             justify
    );

void vpanecontainerSetVertJustification(
    vpanecontainer                 *pane,
    int                             justify
    );

int vpanecontainerGetHorizJustification(
    vpanecontainer                 *pane
    );

int vpanecontainerGetVertJustification(
    vpanecontainer                 *pane
    );

/*
 * * * * * * * * * * PRIVATE CONSTANT DEFINITIONS * * * * * * * * * *
 */

/*
 * * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * * *
 */

/*
 * pane containers
 */

vportALIAS(vpanecontainerItemList, vdialogItemList)

struct vpanecontainer
{
    vcontainer                       container;
    int                              horizJustify;
    int                              vertJustify;
};

#define vpanecontainerCLASS(CLASS, OBJECT, NOTIFY)                            \
    vcontainerCLASS(CLASS, OBJECT, NOTIFY);                                   \
    vclassMETHOD(vpanecontainerSET_JUSTIFICATION,                             \
                 (OBJECT *pane, int axis, int justify))

struct vpanecontainerClass
{
    vpanecontainerCLASS(vpanecontainerClass, vpanecontainer,
                        vcontainerNoteProc);
};


/*
 * * * * * * * * * * * PRIVATE FUNCTION PROTOTYPES * * * * * * * * * * *
 */

/*
 * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * *
 */

/*
 * pane containers
 */

#define vpanecontainerGetContainer(p)   vportBASE_OBJECT(p, container)

#define vpanecontainerGetClass(p) \
    ((vpanecontainerClass*)vcontainerGetClass(vpanecontainerGetContainer(p)))

#define vpanecontainerCreateOfClass(cl) \
    ((vpanecontainer*)vcontainerCreateOfClass((vcontainerClass*)(cl)))
#define vpanecontainerCreate() \
    vpanecontainerCreateOfClass(vpanecontainerGetDefaultClass())
#define vpanecontainerClone(p) \
    ((vpanecontainer*)vcontainerClone(vpanecontainerGetContainer(p)))
#define vpanecontainerInitOfClass(p, cl) \
    vcontainerInitOfClass(vpanecontainerGetContainer(p), (vcontainerClass*)(cl))
#define vpanecontainerInit(p) \
    vpanecontainerInitOfClass(p, vpanecontainerGetDefaultClass())
#define vpanecontainerCopyInit(p, t) \
    vcontainerCopyInit(vpanecontainerGetContainer(p), \
                       vpanecontainerGetContainer(t))
#define vpanecontainerLoad(r) \
    ((vpanecontainer*)vcontainerLoad(r))
#define vpanecontainerLoadInit(p, r) \
    vcontainerLoadInit(vpanecontainerGetContainer(p), (r))
#define vpanecontainerDestroy(p) \
    vcontainerDestroy(vpanecontainerGetContainer(p))
#define vpanecontainerSetTitle(p, s) \
    vcontainerSetTitle(vpanecontainerGetContainer(p), (s))
#define vpanecontainerGetData(p) \
    vcontainerGetData(vpanecontainerGetContainer(p))
#define vpanecontainerGetTitle(p) \
    vcontainerGetTitle(vpanecontainerGetContainer(p))
#define vpanecontainerIsEnabled(p) \
    vcontainerIsEnabled(vpanecontainerGetContainer(p))
#define vpanecontainerHasBorder(p) \
    vcontainerHasBorder(vpanecontainerGetContainer(p))
#define vpanecontainerGetContent(p) \
    vcontainerGetContent(vpanecontainerGetContainer(p))
#define vpanecontainerGetBounds(p) \
    vcontainerGetBounds(vpanecontainerGetContainer(p))
#define vpanecontainerCopy(p, t)        \
    vcontainerCopy(vpanecontainerGetContainer(p), vpanecontainerGetContainer(t))
#define vpanecontainerStore(p, r) \
    vcontainerStore(vpanecontainerGetContainer(p), (r)
#define vpanecontainerEnable(p) \
    vcontainerEnable(vpanecontainerGetContainer(p))
#define vpanecontainerDisable(p) \
    vcontainerDisable(vpanecontainerGetContainer(p))
#define vpanecontainerSetData(p, d) \
    vcontainerSetData(vpanecontainerGetContainer(p), (d))
#define vpanecontainerSetTitleScribed(p, s) \
    vcontainerSetTitleScribed(vpanecontainerGetContainer(p), (s))
#define vpanecontainerSetBorder(p, f) \
    vcontainerSetBorder(vpanecontainerGetContainer(p), (f))
#define vpanecontainerSetBounds(p, r) \
    vcontainerSetBounds(vpanecontainerGetContainer(p), (f))

/**** pane container api implemented as macros ****/

#define vpanecontainerGetItem(p) \
    vcontainerGetItemAt(vpanecontainerGetContainer(p), 0)
#define vpanecontainerGetHorizJustification(p)   ((p)->horizJustify)
#define vpanecontainerGetVertJustification(p)    ((p)->vertJustify)

/*
 * * * * * * * * * * PRIVATE FUNCTION MESSAGE DEFINITIONS * * * * * * * * * *
 */

/*
 * pane containers
 */

#define vpanecontainerSetJustification(p, v, j) \
    vclassSend(vpanecontainerGetClass(p), vpanecontainerSET_JUSTIFICATION, \
               (p, v, j))

#define vpanecontainerSetHorizJustification(p, j) \
    vpanecontainerSetJustification((p), vpanecontainerHORIZONTAL, (j))
#define vpanecontainerSetVertJustification(p, j) \
    vpanecontainerSetJustification((p), vpanecontainerVERTICAL, (j))


vportEND_CPLUSPLUS_EXTERN_C

#endif /* #ifndef vpanecontainerINCLUDED */

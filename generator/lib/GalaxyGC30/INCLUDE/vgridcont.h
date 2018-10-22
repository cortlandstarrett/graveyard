/* $Id: vgridcont.h,v 1.2 1997/09/02 16:44:26 robert Exp $ */

/******************************************************************************

    vgridcont.h

    C Interface to the Grid Container Manager

    (c) Copyright Visix Software Inc.
    All rights reserved

******************************************************************************/

#ifndef vgridcontainerINCLUDED
#define vgridcontainerINCLUDED

#ifndef  vportINCLUDED
#include <vport.h>
#endif

#ifndef  vscribeINCLUDED
#include vscribeHEADER
#endif

#ifndef  vcharINCLUDED
#include vcharHEADER
#endif

#ifndef  vnameINCLUDED
#include vnameHEADER
#endif

#ifndef  vdictINCLUDED
#include vdictHEADER
#endif

#ifndef  vrectINCLUDED
#include vrectHEADER
#endif

#ifndef  vresourceINCLUDED
#include vresourceHEADER
#endif

#ifndef  vcolorINCLUDED
#include vcolorHEADER
#endif

#ifndef  vfontINCLUDED
#include vfontHEADER
#endif

#ifndef  vdrawINCLUDED
#include vdrawHEADER
#endif

#ifndef  vcursorINCLUDED
#include vcursorHEADER
#endif

#ifndef  vclassINCLUDED
#include vclassHEADER
#endif

#ifndef  vobjectINCLUDED
#include vobjectHEADER
#endif

#ifndef  vcommandINCLUDED
#include vcommandHEADER
#endif

#ifndef  veventINCLUDED
#include veventHEADER
#endif

#ifndef  vwindowINCLUDED
#include vwindowHEADER
#endif

#ifndef  vdialogINCLUDED
#include vdialogHEADER
#endif

#ifndef  vcontainerINCLUDED
#include vcontainerHEADER
#endif


vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * * * * * * * * * * * PUBLIC TYPE DEFINITIONS * * * * * * * * * * *
 */

/*
 * grid containers
 */

typedef struct vgridcontainer                  vgridcontainer;
typedef struct vgridcontainerClass             vgridcontainerClass;

typedef void (*vgridcontainerNoteProc)(
    vgridcontainer                    *grid,
    vevent                            *event
    );

typedef void (*vgridcontainerPartitionNoteProc)(
    vgridcontainer                    *grid,
    int                                message,
    int                                axis,
    int                                index
    );

/*
 * * * * * * * * * * PUBLIC CONSTANT DEFINITIONS * * * * * * * * * *
 */

enum {
    vgridcontainerUSE_DEFAULT_SPACING  = -1,
    vgridcontainerNATURAL_SIZE         = -1,

    vgridcontainerHORIZONTAL           = 0,
    vgridcontainerVERTICAL             = 1,

    vgridcontainerROW_MAJOR            = 0,
    vgridcontainerCOLUMN_MAJOR         = 1,

    vgridcontainerUPDATE_OFF           = vFALSE,
    vgridcontainerUPDATE_ON            = vTRUE,

    vgridcontainerADD_NOTIFY           = 0,
    vgridcontainerREMOVE_NOTIFY        = 1,
    vgridcontainerSET_POSITION_NOTIFY  = 2
};

/*
 * grid containers
 */

enum {
    vgridcontainerID_ATTRIBUTE_MAJOR_AXIS         = vcontainerNEXT_ID_ATTRIBUTE,
    vgridcontainerID_ATTRIBUTE_HORIZ_SPACING,
    vgridcontainerID_ATTRIBUTE_VERT_SPACING,
    vgridcontainerID_ATTRIBUTE_UPDATE_MODE,
    vgridcontainerNEXT_ID_ATTRIBUTE
};

enum {
    vgridcontainerNEXT_SELECT                     = vcontainerNEXT_SELECT
};

/*
 * names
 */

extern const vname *vgridcontainer_MajorAxis;
extern const vname *vgridcontainer_RowMajor;
extern const vname *vgridcontainer_ColumnMajor;
extern const vname *vgridcontainer_HorizSpacing;
extern const vname *vgridcontainer_VertSpacing;
extern const vname *vgridcontainer_UpdateMode;
extern const vname *vgridcontainer_GridSpacing;
extern const vname *vgridcontainer_PartitionSpacing;
extern const vname *vgridcontainer_Row;
extern const vname *vgridcontainer_Column;
extern const vname *vgridcontainer_Message;
extern const vname *vgridcontainer_Axis;

/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */

void vgridcontainerStartup(void);

/*
 * grid containers
 */

vgridcontainerClass *vgridcontainerGetDefaultClass(
    void
    );

/**** inherited methods ****/

vgridcontainer *vgridcontainerCreateOfClass(
    vgridcontainerClass            *clas
    );

vgridcontainer *vgridcontainerCreate(
    void
    );

vgridcontainer *vgridcontainerClone(
    vgridcontainer                 *grid
    );

void vgridcontainerInitOfClass(
    vgridcontainer                 *grid,
    vgridcontainerClass            *clas
    );

void vgridcontainerInit(
    vgridcontainer                 *grid
    );

void vgridcontainerDestroy(
    vgridcontainer                 *grid
    );

void vgridcontainerCopy(
    vgridcontainer                 *grid,
    vgridcontainer                 *target
    );

void vgridcontainerCopyInit(
    vgridcontainer                 *grid,
    vgridcontainer                 *target
    );

vgridcontainer *vgridcontainerLoad(
    vresource                       resource
    );

void vgridcontainerLoadInit(
    vgridcontainer                 *grid,
    vresource                       resource
    );

void vgridcontainerStore(
    vgridcontainer                 *grid,
    vresource                       resource
    );

void vgridcontainerEnable(
    vgridcontainer                 *grid
    );

void vgridcontainerDisable(
    vgridcontainer                 *grid
    );

void vgridcontainerAppendItem(
    vgridcontainer                 *grid,
    vdialogItem                    *item
    );

void vgridcontainerDeleteItem(
    vgridcontainer                 *grid,
    vdialogItem                    *item
    );

void vgridcontainerSetItemIndex(
    vgridcontainer                 *grid,
    vdialogItem                    *item,
    int                             index
    );

void vgridcontainerArrange(
    vgridcontainer                 *grid,
    const vrect                    *rect
    );

void vgridcontainerCalcMinSize(
    vgridcontainer                 *grid,
    int                            *w,
    int                            *h
    );

void vgridcontainerSetNotify(
    vgridcontainer                 *grid,
    vgridcontainerNoteProc          noteProc
    );

void vgridcontainerSetData(
    vgridcontainer                 *grid,
    const void                     *data
    );

void vgridcontainerSetTitle(
    vgridcontainer                 *grid,
    const vchar                    *title
    );

void vgridcontainerSetTitleScribed(
    vgridcontainer                 *grid,
    vscribe                        *title
    );

void vgridcontainerSetBorder(
    vgridcontainer                 *grid,
    int                             flag
    );

void vgridcontainerSetBounds(
    vgridcontainer                 *grid,
    const vrect                    *bounds
    );

void vgridcontainerSetFlat(
    vgridcontainer                 *grid,
    int                             flag
    );

void vgridcontainerSetScrollX(
    vgridcontainer                 *grid,
    int                             flag
    );

void vgridcontainerSetScrollY(
    vgridcontainer                 *grid,
    int                             flag
    );

void vgridcontainerSetFocus(
    vgridcontainer                 *grid,
    vdialogItem                    *focus
    );

void vgridcontainerSetDefFocus(
    vgridcontainer                 *grid,
    vdialogItem                    *defFocus
    );

void vgridcontainerSetSolution(
    vgridcontainer                 *grid,
    vspringSolution                *solution
    );

void vgridcontainerSetSelection(
    vgridcontainer                 *grid,
    vdialogItem                    *selection
    );

vobjectAttributed *vgridcontainerGetObject(
    vgridcontainer                 *grid
    );

vdialogItem *vgridcontainerGetItem(
    vgridcontainer                 *grid
    );

vcontainer *vgridcontainerGetContainer(
    vgridcontainer                 *grid
    );

vgridcontainerClass *vgridcontainerGetClass(
    vgridcontainer                 *grid
    );

vgridcontainerNoteProc vgridcontainerGetNotify(
    vgridcontainer                 *grid
    );

const void *vgridcontainerGetData(
    vgridcontainer                 *grid
    );

const vchar *vgridcontainerGetTitle(
    vgridcontainer                 *grid
    );

int vgridcontainerIsEnabled(
    vgridcontainer                 *grid
    );

int vgridcontainerHasBorder(
    vgridcontainer                 *grid
    );

const vrect *vgridcontainerGetContent(
    vgridcontainer                 *grid
    );

const vrect *vgridcontainerGetBounds(
    vgridcontainer                 *grid
    );

int vgridcontainerIsFlat(
    vgridcontainer                 *grid
    );

int vgridcontainerHasScrollX(
    vgridcontainer                 *grid
    );

int vgridcontainerHasScrollY(
    vgridcontainer                 *grid
    );

vdialogItemList *vgridcontainerGetItemList(
    vgridcontainer                 *grid
    );

vdialogItem *vgridcontainerGetFocus(
    vgridcontainer                 *grid
    );

vdialogItem *vgridcontainerGetDefFocus(
    vgridcontainer                 *grid
    );

vspringSolution *vgridcontainerGetSolution(
    vgridcontainer                 *grid
    );

int vgridcontainerGetItemCount(
    vgridcontainer                 *grid
    );

vdialogItem *vgridcontainerGetItemAt(
    vgridcontainer                 *grid,
    int                             index
    );

int vgridcontainerGetItemIndex(
    vgridcontainer                 *grid,
    vdialogItem                    *item
    );

vdialogItem *vgridcontainerFindItem(
    vgridcontainer                 *grid,
    const vname                    *tag
    );

vdialogItem *vgridcontainerGetSelection(
    vgridcontainer                 *grid
    );

/**** grid-specific methods ****/

  /* per-grid attributes */

void vgridcontainerSetMajorAxis(
    vgridcontainer                 *grid,
    int                             rowOrCol
    );

int vgridcontainerGetMajorAxis(
    vgridcontainer                 *grid
    );

void vgridcontainerSetSpacing(
    vgridcontainer                 *grid,
    int                             axis,
    int                             spacing
    );

int vgridcontainerGetSpacing(
    vgridcontainer                 *grid,
    int                             axis
    );

void vgridcontainerSetUpdateMode(
    vgridcontainer                 *grid,
    int                             mode
    );

int vgridcontainerGetUpdateMode(
    vgridcontainer                 *grid
    );

unsigned vgridcontainerGetPartitionCount(
    vgridcontainer                 *grid,
    int                             axis
    );

unsigned vgridcontainerGetColumnCount(
    vgridcontainer                 *grid
    );

unsigned vgridcontainerGetRowCount(
    vgridcontainer                 *grid
    );

void vgridcontainerSetPartitionNotify(
    vgridcontainer                 *grid,
    vgridcontainerPartitionNoteProc noteProc
    );

vgridcontainerPartitionNoteProc vgridcontainerGetPartitionNotify(
    vgridcontainer                 *grid
    );

void vgridcontainerNotifyPartition(
    vgridcontainer                 *grid,
    int                             message,
    int                             axis,
    int                             index
    );

void vgridcontainerSetItemArrangeable(
    vgridcontainer                 *grid,
    vdialogItem                    *item,
    vbool                           arr
    );

vbool vgridcontainerIsItemArrangeable(
    vgridcontainer                 *grid,
    vdialogItem                    *item
    );

  /* per-item attributes */

void vgridcontainerSetItemMinSize(
    vgridcontainer                 *grid,
    vdialogItem                    *item,
    int                             minWidth,
    int                             minHeight
    );

void vgridcontainerGetItemMinSize(
    vgridcontainer                 *grid,
    vdialogItem                    *item,
    int                            *minWidth,
    int                            *minHeight
    );

int vgridcontainerGetItemMinWidth(
    vgridcontainer                 *grid,
    vdialogItem                    *item
    );

int vgridcontainerGetItemMinHeight(
    vgridcontainer                 *grid,
    vdialogItem                    *item
    );

vbool vgridcontainerIsItemVisible(
    vgridcontainer                 *grid,
    vdialogItem                    *item
    );

  /* per-partition attributes */

void vgridcontainerSetPartitionSpacing(
    vgridcontainer                 *grid,
    int                             axis,
    int                             index,
    int                             spacing
    );

int vgridcontainerGetPartitionSpacing(
    vgridcontainer                 *grid,
    int                             axis,
    int                             index
    );

int vgridcontainerDeterminePartitionSpacing(
    vgridcontainer                 *grid,
    int                             axis,
    int                             index
    );

void vgridcontainerSetPartitionCascadable(
    vgridcontainer                 *grid,
    int                             axis,
    int                             index,
    vbool                           cascadable
    );

vbool vgridcontainerIsPartitionCascadable(
    vgridcontainer                 *grid,
    int                             axis,
    int                             index
    );

void vgridcontainerCalcPartitionRange(
    vgridcontainer                 *grid,
    int                             axis,
    int                             index,
    int                            *minCoord,
    int                            *maxCoord
    );

int vgridcontainerSetPartitionPosition(
    vgridcontainer                 *grid,
    int                             axis,
    int                             index,
    int                             newCoord
    );

int vgridcontainerGetPartitionPosition(
    vgridcontainer                 *grid,
    int                             axis,
    int                             index
    );

  /* partitioning */

void vgridcontainerAddPartitionAtIndex(
    vgridcontainer                 *grid,
    vbool                           cascadable,
    int                             axis,
    int                             index,
    int                             coord
    );

int vgridcontainerAddPartition(
    vgridcontainer                 *grid,
    vbool                           cascadable,
    int                             axis,
    int                             coord
    );

void vgridcontainerRemovePartition(
    vgridcontainer                 *grid,
    int                             axis,
    int                             index
    );

void vgridcontainerTranspose(
    vgridcontainer                 *grid
    );

  /* row/column convenience api */

vdialogItem *vgridcontainerGetCellItem(
    vgridcontainer                 *grid,
    int                             row,
    int                             col
    );

/** XXX: more to do **/

  /* internal calculations */

int vgridcontainerCalcPartitionIndex(
    vgridcontainer                 *grid,
    int                             axis,
    int                             coord
    );

/*
 * * * * * * * * * * PRIVATE CONSTANT DEFINITIONS * * * * * * * * * *
 */

/*
 * * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * * *
 */

/*
 * grid containers
 */

vportALIAS(vgridcontainerItemList, vdialogItemList)

typedef struct _vgridcontainerExtra  _vgridcontainerExtra;

struct vgridcontainer
{
    vcontainer                       container;
    int                              majorAxis;
    int                              updateMode;
    vgridcontainerPartitionNoteProc  prtnNoteProc;
    _vgridcontainerExtra            *extra;
};

#define vgridcontainerCLASS(CLASS, OBJECT, NOTIFY, PNOTIFY)                   \
    vcontainerCLASS(CLASS, OBJECT, NOTIFY);                                   \
    vclassVARIABLE(vgridcontainerHORIZ_SPACING, int);                         \
    vclassVARIABLE(vgridcontainerVERT_SPACING, int);                          \
    vclassMETHOD_RET(vgridcontainerCALC_PARTITION_INDEX, int,                 \
                 (OBJECT *grid, int axis, int coord));                        \
    vclassMETHOD(vgridcontainerSET_MAJOR_AXIS,                                \
                 (OBJECT *grid, int rowOrCol));                               \
    vclassMETHOD(vgridcontainerTRANSPOSE, (OBJECT *grid));                    \
    vclassMETHOD(vgridcontainerSET_SPACING,                                   \
                 (OBJECT *grid, int axis, int spacing));                      \
    vclassMETHOD(vgridcontainerSET_UPDATE_MODE,                               \
                 (OBJECT *grid, int mode));                                   \
    vclassMETHOD(vgridcontainerSET_ITEM_MIN_SIZE,                             \
                 (OBJECT *grid, vdialogItem *item, int mw, int mh));          \
    vclassMETHOD(vgridcontainerSET_PARTITION_SPACING,                         \
                 (OBJECT *grid, int axis, int index, int spacing));           \
    vclassMETHOD_RET(vgridcontainerDETERMINE_PARTITION_SPACING, int,          \
                     (OBJECT *grid, int axis, int index));                    \
    vclassMETHOD(vgridcontainerSET_PARTITION_CASCADABLE,                      \
                 (OBJECT *grid, int axis, int index, vbool casc));            \
    vclassMETHOD(vgridcontainerCALC_PARTITION_RANGE,                          \
                 (OBJECT *grid, int axis, int index, int *min, int *max));    \
    vclassMETHOD(vgridcontainerADD_PARTITION_AT_INDEX,                        \
                 (OBJECT *grid, vbool casc, int axis, int index, int coord)); \
    vclassMETHOD(vgridcontainerREMOVE_PARTITION,                              \
                 (OBJECT *grid, int axis, int index));                        \
    vclassMETHOD_RET(vgridcontainerSET_PARTITION_POSITION, int,               \
                     (OBJECT *grid, int axis, int index, int coord));         \
    vclassMETHOD(vgridcontainerSET_PARTITION_NOTIFY,                          \
                 (OBJECT *grid, PNOTIFY noteProc));                           \
    vclassMETHOD(vgridcontainerNOTIFY_PARTITION,                              \
                 (OBJECT *grid, int msg, int axis, int index));               \
    vclassMETHOD_RET(vgridcontainerGET_CELL_ITEM, vdialogItem*,               \
                     (OBJECT *grid, int row, int col));                       \
    vclassMETHOD(vgridcontainerSET_ITEM_ARRANGEABLE,                           \
                 (OBJECT *grid, vdialogItem *item, vbool f))

struct vgridcontainerClass
{
    vgridcontainerCLASS(vgridcontainerClass, vgridcontainer,
                        vgridcontainerNoteProc,
                        vgridcontainerPartitionNoteProc);
};


/*
 * * * * * * * * * * * PRIVATE FUNCTION PROTOTYPES * * * * * * * * * * *
 */

int _vgridcontainerGetMinSizeFor(
    vgridcontainer                 *grid,
    int                             axis,
    int                             globalIndex
);


/*
 * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * *
 */

/*
 * grid containers
 */

#define vgridcontainerGetContainer(g)   vportBASE_OBJECT(g, container)
#define vgridcontainerGetItem(g) \
    vcontainerGetItem(vgridcontainerGetContainer(g))
#define vgridcontainerGetObject(g) \
    vcontainerGetObject(vgridcontainerGetContainer(g))

#define vgridcontainerGetClass(g) \
    ((vgridcontainerClass*)vcontainerGetClass(vgridcontainerGetContainer(g)))

#define vgridcontainerCreateOfClass(cl) \
    ((vgridcontainer*)vcontainerCreateOfClass((vcontainerClass*)(cl)))
#define vgridcontainerCreate() \
    vgridcontainerCreateOfClass(vgridcontainerGetDefaultClass())
#define vgridcontainerClone(g) \
    ((vgridcontainer*)vcontainerClone(vgridcontainerGetContainer(g)))
#define vgridcontainerInitOfClass(g, cl) \
    vcontainerInitOfClass(vgridcontainerGetContainer(g), (vcontainerClass*)(cl))
#define vgridcontainerInit(g) \
    vgridcontainerInitOfClass(g, vgridcontainerGetDefaultClass())
#define vgridcontainerCopyInit(g, t) \
    vcontainerCopyInit(vgridcontainerGetContainer(g), \
                       vgridcontainerGetContainer(t))
#define vgridcontainerLoad(r) \
    ((vgridcontainer*)vcontainerLoad(r))
#define vgridcontainerLoadInit(g, r) \
    vcontainerLoadInit(vgridcontainerGetContainer(g), (r))
#define vgridcontainerDestroy(g) \
    vcontainerDestroy(vgridcontainerGetContainer(g))
#define vgridcontainerGetNotify(g) \
    ((vgridcontainerNoteProc)vcontainerGetNotify(vgridcontainerGetContainer(g)))
#define vgridcontainerSetNotify(g, n) \
    vcontainerSetNotify((vcontainer *)(g), (vcontainerNoteProc)(n))
#define vgridcontainerSetTitle(g, s) \
    vcontainerSetTitle(vgridcontainerGetContainer(g), (s))
#define vgridcontainerGetData(g) \
    vcontainerGetData(vgridcontainerGetContainer(g))
#define vgridcontainerGetTitle(g) \
    vcontainerGetTitle(vgridcontainerGetContainer(g))
#define vgridcontainerIsEnabled(g) \
    vcontainerIsEnabled(vgridcontainerGetContainer(g))
#define vgridcontainerHasBorder(g) \
    vcontainerHasBorder(vgridcontainerGetContainer(g))
#define vgridcontainerGetContent(g) \
    vcontainerGetContent(vgridcontainerGetContainer(g))
#define vgridcontainerGetBounds(g) \
    vcontainerGetBounds(vgridcontainerGetContainer(g))
#define vgridcontainerIsFlat(g) \
    vcontainerIsFlat(vgridcontainerGetContainer(g))
#define vgridcontainerHasScrollX(g) \
    vcontainerHasScrollX(vgridcontainerGetContainer(g))
#define vgridcontainerHasScrollY(g) \
    vcontainerHasScrollY(vgridcontainerGetContainer(g))
#define vgridcontainerGetItemList(g) \
    vcontainerGetItemList(vgridcontainerGetContainer(g))
#define vgridcontainerGetFocus(g) \
    vcontainerGetFocus(vgridcontainerGetContainer(g))
#define vgridcontainerGetDefFocus(g) \
    vcontainerGetDefFocus(vgridcontainerGetContainer(g))
#define vgridcontainerGetSolution(g) \
    vcontainerGetSolution(vgridcontainerGetContainer(g))
#define vgridcontainerGetItemCount(g) \
    vcontainerGetItemCount(vgridcontainerGetContainer(g))
#define vgridcontainerGetItemAt(g, i) \
    vcontainerGetItemAt(vgridcontainerGetContainer(g), (i))
#define vgridcontainerGetItemIndex(g, i) \
    vcontainerGetItemIndex(vgridcontainerGetContainer(g), (i))
#define vgridcontainerFindItem(g, t) \
    vcontainerFindItem(vgridcontainerGetContainer(g), (t))
#define vgridcontainerGetSelection(g) \
    vcontainerGetSelection(vgridcontainerGetContainer(g))
#define vgridcontainerCopy(g, t)        \
    vcontainerCopy(vgridcontainerGetContainer(g), vgridcontainerGetContainer(t))
#define vgridcontainerStore(g, r) \
    vcontainerStore(vgridcontainerGetContainer(g), (r))
#define vgridcontainerEnable(g) \
    vcontainerEnable(vgridcontainerGetContainer(g))
#define vgridcontainerDisable(g) \
    vcontainerDisable(vgridcontainerGetContainer(g))
#define vgridcontainerAppendItem(g, i) \
    vcontainerAppendItem(vgridcontainerGetContainer(g), (i))
#define vgridcontainerDeleteItem(g, i) \
    vcontainerDeleteItem(vgridcontainerGetContainer(g), (i))
#define vgridcontainerSetItemIndex(g, i, n) \
    vcontainerSetItemIndex(vgridcontainerGetContainer(g), (i), (n))
#define vgridcontainerArrange(g, r) \
    vcontainerArrange(vgridcontainerGetContainer(g), (r))
#define vgridcontainerCalcMinSize(g, w, h) \
    vcontainerCalcMinSize(vgridcontainerGetContainer(g), (w), (h))
#define vgridcontainerSetData(g, d) \
    vcontainerSetData(vgridcontainerGetContainer(g), (d))
#define vgridcontainerSetTitleScribed(g, s) \
    vcontainerSetTitleScribed(vgridcontainerGetContainer(g), (s))
#define vgridcontainerSetBorder(g, f) \
    vcontainerSetBorder(vgridcontainerGetContainer(g), (f))
#define vgridcontainerSetBounds(g, r) \
    vcontainerSetBounds(vgridcontainerGetContainer(g), (f))
#define vgridcontainerSetFlat(g, f) \
    vcontainerSetFlat(vgridcontainerGetContainer(g), (f))
#define vgridcontainerSetScrollX(g, f) \
    vcontainerSetScrollX(vgridcontainerGetContainer(g), (f))
#define vgridcontainerSetScrollY(g, f) \
    vcontainerSetScrollY(vgridcontainerGetContainer(g), (f))
#define vgridcontainerSetFocus(g, i) \
    vcontainerSetFocus(vgridcontainerGetContainer(g), (i))
#define vgridcontainerSetDefFocus(g, i) \
    vcontainerSetDefFocus(vgridcontainerGetContainer(g), (i))
#define vgridcontainerSetSolution(g, s) \
    vcontainerSetSolution(vgridcontainerGetContainer(g), (s))
#define vgridcontainerSetSelection(g, i) \
    vcontainerSetSelection(vgridcontainerGetContainer(g), (i))

/**** grid api implemented as macros ****/

#define vgridcontainerGetMajorAxis(g)        ((g)->majorAxis)
#define vgridcontainerGetUpdateMode(g)       ((g)->updateMode)
#define vgridcontainerGetPartitionNotify(g)  ((g)->prtnNoteProc)
#define vgridcontainerGetRowCount(g) \
    (vgridcontainerGetPartitionCount((g), vgridcontainerVERTICAL) + 1)
#define vgridcontainerGetColumnCount(g) \
    (vgridcontainerGetPartitionCount((g), vgridcontainerHORIZONTAL) + 1)

/* XXX HACK: take out!! */
void updateRowColMin(vgridcontainer *grid, int row, int col);
void updateAllMins(vgridcontainer *grid);
void dumpAllMins(vgridcontainer *grid);

/*
 * * * * * * * * * * PRIVATE FUNCTION MESSAGE DEFINITIONS * * * * * * * * * *
 */

/*
 * grid containers
 */

#define vgridcontainerSetMajorAxis(g, a) \
    vclassSend(vgridcontainerGetClass(g), \
	       vgridcontainerSET_MAJOR_AXIS, (g, a))
#define vgridcontainerSetSpacing(g, h, s) \
    vclassSend(vgridcontainerGetClass(g), \
	       vgridcontainerSET_SPACING, (g, h, s))
#define vgridcontainerSetUpdateMode(g, m) \
    vclassSend(vgridcontainerGetClass(g), \
	       vgridcontainerSET_UPDATE_MODE, (g, m))
#define vgridcontainerSetItemMinSize(g, i, w, h) \
    vclassSend(vgridcontainerGetClass(g), \
	       vgridcontainerSET_ITEM_MIN_SIZE, (g, i, w, h))
#define vgridcontainerSetPartitionSpacing(g, v, i, s) \
    vclassSend(vgridcontainerGetClass(g), \
	       vgridcontainerSET_PARTITION_SPACING, (g, v, i, s))
#define vgridcontainerDeterminePartitionSpacing(g, v, i) \
    vclassSend(vgridcontainerGetClass(g), \
	       vgridcontainerDETERMINE_PARTITION_SPACING, (g, v, i))
#define vgridcontainerSetPartitionCascadable(g, v, i, c) \
    vclassSend(vgridcontainerGetClass(g), \
	       vgridcontainerSET_PARTITION_CASCADABLE, (g, v, i, c))
#define vgridcontainerCalcPartitionRange(g, v, i, m, M) \
    vclassSend(vgridcontainerGetClass(g), \
	       vgridcontainerCALC_PARTITION_RANGE,(g, v, i, m, M))
#define vgridcontainerAddPartitionAtIndex(g, c, v, i, x) \
    vclassSend(vgridcontainerGetClass(g), \
	       vgridcontainerADD_PARTITION_AT_INDEX, (g, c, v, i, x))
#define vgridcontainerRemovePartition(g, v, i) \
    vclassSend(vgridcontainerGetClass(g), \
	       vgridcontainerREMOVE_PARTITION, (g, v, i))
#define vgridcontainerSetPartitionPosition(g, v, i, c) \
    vclassSend(vgridcontainerGetClass(g), \
	       vgridcontainerSET_PARTITION_POSITION, (g, v, i, c))
#define vgridcontainerCalcPartitionIndex(g, v, c) \
    vclassSend(vgridcontainerGetClass(g), \
	       vgridcontainerCALC_PARTITION_INDEX, (g, v, c))
#define vgridcontainerTranspose(g) \
    vclassSend(vgridcontainerGetClass(g), \
	       vgridcontainerTRANSPOSE, (g))
#define vgridcontainerSetPartitionNotify(g, n) \
    vclassSend(vgridcontainerGetClass(g), \
	       vgridcontainerSET_PARTITION_NOTIFY, (g, n))
#define vgridcontainerNotifyPartition(g, m, v, i) \
    vclassSend(vgridcontainerGetClass(g), \
	       vgridcontainerNOTIFY_PARTITION, (g, m, v, i))
#define vgridcontainerGetCellItem(g, r, c) \
    vclassSend(vgridcontainerGetClass(g), \
	       vgridcontainerGET_CELL_ITEM, (g, r, c))
#define vgridcontainerSetItemArrangeable(g, i, f) \
    vclassSend(vgridcontainerGetClass(g), \
	       vgridcontainerSET_ITEM_ARRANGEABLE, (g, i, f))


vportEND_CPLUSPLUS_EXTERN_C

#endif /* #ifndef vgridcontainerINCLUDED */

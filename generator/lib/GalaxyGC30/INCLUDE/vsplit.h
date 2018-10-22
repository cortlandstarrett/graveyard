/* $Id: vsplit.h,v 1.15 1997/06/27 01:18:11 robert Exp $ */

/******************************************************************************

    vsplit.h

    C Interface to the Split Container Manager

    (c) Copyright Visix Software Inc.
    All rights reserved

******************************************************************************/

#ifndef vsplitINCLUDED
#define vsplitINCLUDED

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

#ifndef  vgridcontainerINCLUDED
#include vgridcontainerHEADER
#endif


vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * * * * * * * * * * * PUBLIC TYPE DEFINITIONS * * * * * * * * * * *
 */

/*
 * split containers
 */

typedef struct vsplit               vsplit;
typedef struct vsplitClass          vsplitClass;
 
typedef struct vsplitTrackEvent vsplitTrackEvent;

struct vsplitTrackEvent {
    int                             axis;
    int                             id;
    int                             coord;
    int                             prevCoord;
    int                             origCoord;
};

typedef void (*vsplitNoteProc)(
    vsplit                         *split,
    vevent                         *event
    );

typedef void (*vsplitPartitionNoteProc)(
    vsplit                         *split,
    int                             message,
    int                             axis,
    int                             index
    );

typedef void (*vsplitTrackNoteProc)(
    vsplit                         *split,
    int                             message,
    const vsplitTrackEvent         *event
    );

/*
 * sashes
 */

typedef struct vsplitSash           vsplitSash;
typedef struct vsplitSashClass      vsplitSashClass;

typedef struct vsplitSashTrackState vsplitSashTrackState;

struct vsplitSashTrackState
{
    int                             limitLow;
    int                             limitHigh;
    int                             offset;
    vrect                           dragRect;
    int                             prevCoord;
    int                             origCoord;
    vbool                           tracking;
    vbool                           indep;
};

typedef void (*vsplitSashNoteProc)(
    vsplitSash                     *sash,
    vevent                         *event
    );

typedef void (*vsplitSashTrackNoteProc)(
    vsplitSash                     *sash,
    int                             message,
    int                             coord
    );

/*
 * junctions
 */

typedef struct vsplitJunction       vsplitJunction;
typedef struct vsplitJunctionClass  vsplitJunctionClass;

typedef void (*vsplitJunctionNoteProc)(
    vsplitJunction                 *junction,
    vevent                         *event
    );


/*
 * * * * * * * * * * PUBLIC CONSTANT DEFINITIONS * * * * * * * * * *
 */

extern const vname *vsplit_Draggable;
extern const vname *vsplit_MoveToTopLeft;
extern const vname *vsplit_MoveToBottomRight;
extern const vname *vsplit_MoveUpRight;
extern const vname *vsplit_MoveDownLeft;
extern const vname *vsplit_MoveUpRightFine;
extern const vname *vsplit_MoveDownLeftFine;

extern const vname *vsplit_MoveUp;
extern const vname *vsplit_MoveDown;
extern const vname *vsplit_MoveLeft;
extern const vname *vsplit_MoveRight;
extern const vname *vsplit_MoveUpFine;
extern const vname *vsplit_MoveDownFine;
extern const vname *vsplit_MoveLeftFine;
extern const vname *vsplit_MoveRightFine;

extern const vname *vsplit_StartMove;
extern const vname *vsplit_EndMove;
extern const vname *vsplit_AbortMove;

/*
 * split containers
 */

enum {
    vsplitUSE_DEFAULT_SPACING  = vgridcontainerUSE_DEFAULT_SPACING,

    vsplitINHERIT_SCALAR       = -1,

    vsplitHORIZONTAL           = vgridcontainerHORIZONTAL,
    vsplitVERTICAL             = vgridcontainerVERTICAL,

    vsplitROW_MAJOR            = vgridcontainerROW_MAJOR,
    vsplitCOLUMN_MAJOR         = vgridcontainerCOLUMN_MAJOR,

    vsplitUPDATE_ON            = vgridcontainerUPDATE_ON,
    vsplitUPDATE_OFF           = vgridcontainerUPDATE_OFF,

    vsplitADD_NOTIFY           = vgridcontainerADD_NOTIFY,
    vsplitREMOVE_NOTIFY        = vgridcontainerREMOVE_NOTIFY,
    vsplitSET_POSITION_NOTIFY  = vgridcontainerSET_POSITION_NOTIFY,

    vsplitSPLIT_CENTER         = -1,
    vsplitSPLIT_EDGE           = -2
};

enum {
    vsplitID_ATTRIBUTE_FOO     = vgridcontainerNEXT_ID_ATTRIBUTE,
    vsplitNEXT_ID_ATTRIBUTE
};

enum {
    vsplitNEXT_SELECT          = vgridcontainerNEXT_SELECT
};

enum {
    vsplitTRACK_START,
    vsplitTRACK_DRAG,
    vsplitTRACK_END
};


/*
 * sashes
 */

enum {
    vsplitSashID_ATTRIBUTE_DRAGGABLE = vdialogITEM_NEXT_ID_ATTRIBUTE,
    vsplitSashNEXT_ID_ATTRIBUTE
};

enum {
    vsplitSashSELECT_MOVE_TO_TOP_LEFT        = vdialogITEM_NEXT_SELECT,
    vsplitSashSELECT_MOVE_TO_BOTTOM_RIGHT,
    vsplitSashSELECT_MOVE_UP_RIGHT,
    vsplitSashSELECT_MOVE_DOWN_LEFT,
    vsplitSashSELECT_MOVE_UP_RIGHT_FINE,
    vsplitSashSELECT_MOVE_DOWN_LEFT_FINE,
    vsplitSashSELECT_START_MOVE,
    vsplitSashSELECT_END_MOVE,
    vsplitSashSELECT_ABORT_MOVE,

    vsplitSashNEXT_SELECT
};

enum {
    vsplitSashMOVE_TO_TOP_LEFT,
    vsplitSashMOVE_TO_BOTTOM_RIGHT,
    vsplitSashMOVE_UP_RIGHT,
    vsplitSashMOVE_DOWN_LEFT,
    vsplitSashMOVE_UP_RIGHT_FINE,
    vsplitSashMOVE_DOWN_LEFT_FINE,
    vsplitSashSTART_MOVE,
    vsplitSashEND_MOVE,
    vsplitSashABORT_MOVE
};


/*
 * junctions
 */

enum {
    vsplitJunctionID_ATTRIBUTE_FOO   = vdialogITEM_NEXT_ID_ATTRIBUTE,
    vsplitJunctionNEXT_ID_ATTRIBUTE
};

enum {
    vsplitJunctionSELECT_MOVE_UP        = vdialogITEM_NEXT_SELECT,
    vsplitJunctionSELECT_MOVE_DOWN,
    vsplitJunctionSELECT_MOVE_LEFT,
    vsplitJunctionSELECT_MOVE_RIGHT,
    vsplitJunctionSELECT_MOVE_UP_FINE,
    vsplitJunctionSELECT_MOVE_DOWN_FINE,
    vsplitJunctionSELECT_MOVE_LEFT_FINE,
    vsplitJunctionSELECT_MOVE_RIGHT_FINE,
    vsplitJunctionSELECT_START_MOVE,
    vsplitJunctionSELECT_END_MOVE,
    vsplitJunctionSELECT_ABORT_MOVE,

    vsplitJunctionNEXT_SELECT
};

enum {
    vsplitJunctionMOVE_UP,
    vsplitJunctionMOVE_DOWN,
    vsplitJunctionMOVE_LEFT,
    vsplitJunctionMOVE_RIGHT,
    vsplitJunctionMOVE_UP_FINE,
    vsplitJunctionMOVE_DOWN_FINE,
    vsplitJunctionMOVE_LEFT_FINE,
    vsplitJunctionMOVE_RIGHT_FINE,
    vsplitJunctionSTART_MOVE,
    vsplitJunctionEND_MOVE,
    vsplitJunctionABORT_MOVE
};



/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */

/*
 * split containers
 */

void vsplitStartup(void);

vsplitClass *vsplitGetDefaultClass(
    void
    );

/**** inherited methods ****/

vsplit *vsplitCreateOfClass(
    vsplitClass                    *clas
    );

vsplit *vsplitCreate(
    void
    );

vsplit *vsplitClone(
    vsplit                         *split
    );

void vsplitInitOfClass(
    vsplit                         *split,
    vsplitClass                    *clas
    );

void vsplitInit(
    vsplit                         *split
    );

void vsplitDestroy(
    vsplit                         *split
    );

void vsplitCopy(
    vsplit                         *split,
    vsplit                         *target
    );

void vsplitCopyInit(
    vsplit                         *split,
    vsplit                         *target
    );

vsplit *vsplitLoad(
    vresource                       resource
    );

void vsplitLoadInit(
    vsplit                         *split,
    vresource                       resource
    );

void vsplitStore(
    vsplit                         *split,
    vresource                       resource
    );

void vsplitEnable(
    vsplit                         *split
    );

void vsplitDisable(
    vsplit                         *split
    );

void vsplitAppendItem(
    vsplit                         *split,
    vdialogItem                    *item
    );

void vsplitDeleteItem(
    vsplit                         *split,
    vdialogItem                    *item
    );

void vsplitSetItemIndex(
    vsplit                         *split,
    vdialogItem                    *item,
    int                             index
    );

void vsplitArrange(
    vsplit                         *split,
    const vrect                    *rect
    );

void vsplitCalcMinSize(
    vsplit                         *split,
    int                            *w,
    int                            *h
    );

void vsplitSetNotify(
    vsplit                         *split,
    vsplitNoteProc                  noteProc
    );

void vsplitSetData(
    vsplit                         *split,
    const void                     *data
    );

void vsplitSetTitle(
    vsplit                         *split,
    const vchar                    *title
    );

void vsplitSetTitleScribed(
    vsplit                         *split,
    vscribe                        *title
    );

void vsplitSetBorder(
    vsplit                         *split,
    int                             flag
    );

void vsplitSetBounds(
    vsplit                         *split,
    const vrect                    *bounds
    );

void vsplitSetFlat(
    vsplit                         *split,
    int                             flag
    );

void vsplitSetScrollX(
    vsplit                         *split,
    int                             flag
    );

void vsplitSetScrollY(
    vsplit                         *split,
    int                             flag
    );

void vsplitSetFocus(
    vsplit                         *split,
    vdialogItem                    *focus
    );

void vsplitSetDefFocus(
    vsplit                         *split,
    vdialogItem                    *defFocus
    );

void vsplitSetSolution(
    vsplit                         *split,
    vspringSolution                *solution
    );

void vsplitSetSelection(
    vsplit                         *split,
    vdialogItem                    *selection
    );

vobjectAttributed *vsplitGetObject(
    vsplit                         *split
    );

vdialogItem *vsplitGetItem(
    vsplit                         *split
    );

vcontainer *vsplitGetContainer(
    vsplit                         *split
    );

vgridcontainer *vsplitGetGrid(
    vsplit                         *split
    );

vsplitClass *vsplitGetClass(
    vsplit                         *split
    );

vsplitNoteProc vsplitGetNotify(
    vsplit                         *split
    );

const void *vsplitGetData(
    vsplit                         *split
    );

const vchar *vsplitGetTitle(
    vsplit                         *split
    );

int vsplitIsEnabled(
    vsplit                         *split
    );

int vsplitHasBorder(
    vsplit                         *split
    );

const vrect *vsplitGetContent(
    vsplit                         *split
    );

const vrect *vsplitGetBounds(
    vsplit                         *split
    );

int vsplitIsFlat(
    vsplit                         *split
    );

int vsplitHasScrollX(
    vsplit                         *split
    );

int vsplitHasScrollY(
    vsplit                         *split
    );

vdialogItemList *vsplitGetItemList(
    vsplit                         *split
    );

vdialogItem *vsplitGetFocus(
    vsplit                         *split
    );

vdialogItem *vsplitGetDefFocus(
    vsplit                         *split
    );

vspringSolution *vsplitGetSolution(
    vsplit                         *split
    );

int vsplitGetItemCount(
    vsplit                         *split
    );

vdialogItem *vsplitGetItemAt(
    vsplit                         *split,
    int                             index
    );

int vsplitGetItemIndex(
    vsplit                         *split,
    vdialogItem                    *item
    );

vdialogItem *vsplitFindItem(
    vsplit                         *split,
    const vname                    *tag
    );

vdialogItem *vsplitGetSelection(
    vsplit                         *split
    );

void vsplitSetMajorAxis(
    vsplit                         *split,
    int                             rowOrCol
    );

int vsplitGetMajorAxis(
    vsplit                         *split
    );

void vsplitSetSpacing(
    vsplit                         *split,
    int                             axis,
    int                             spacing
    );

int vsplitGetSpacing(
    vsplit                         *split,
    int                             axis
    );

void vsplitSetUpdateMode(
    vsplit                         *split,
    int                             mode
    );

int vsplitGetUpdateMode(
    vsplit                         *split
    );

unsigned vsplitGetPartitionCount(
    vsplit                         *split,
    int                             axis
    );

unsigned vsplitGetColumnCount(
    vsplit                         *split
    );

unsigned vsplitGetRowCount(
    vsplit                         *split
    );

void vsplitSetPartitionNotify(
    vsplit                         *split,
    vsplitPartitionNoteProc         noteProc
    );

vsplitPartitionNoteProc vsplitGetPartitionNotify(
    vsplit                         *split
    );

void vsplitNotifyPartition(
    vsplit                         *split,
    int                             message,
    int                             axis,
    int                             index
    );

void vsplitSetItemMinSize(
    vsplit                         *split,
    vdialogItem                    *item,
    int                             minWidth,
    int                             minHeight
    );

void vsplitGetItemMinSize(
    vsplit                         *split,
    vdialogItem                    *item,
    int                            *minWidth,
    int                            *minHeight
    );

int vsplitGetItemMinWidth(
    vsplit                         *split,
    vdialogItem                    *item
    );

int vsplitGetItemMinHeight(
    vsplit                         *split,
    vdialogItem                    *item
    );

vbool vsplitIsItemVisible(
    vsplit                         *split,
    vdialogItem                    *item
    );

void vsplitSetPartitionSpacing(
    vsplit                         *split,
    int                             axis,
    int                             index,
    int                             spacing
    );

int vsplitGetPartitionSpacing(
    vsplit                         *split,
    int                             axis,
    int                             index
    );

int vsplitDeterminePartitionSpacing(
    vsplit                         *split,
    int                             axis,
    int                             index
    );

void vsplitSetPartitionCascadable(
    vsplit                         *split,
    int                             axis,
    int                             index,
    vbool                           cascadable
    );

vbool vsplitIsPartitionCascadable(
    vsplit                         *split,
    int                             axis,
    int                             index
    );

void vsplitCalcPartitionRange(
    vsplit                         *split,
    int                             axis,
    int                             index,
    int                            *minCoord,
    int                            *maxCoord
    );

int vsplitSetPartitionPosition(
    vsplit                         *split,
    int                             axis,
    int                             index,
    int                             newCoord
    );

int vsplitGetPartitionPosition(
    vsplit                         *split,
    int                             axis,
    int                             index
    );

void vsplitAddPartitionAtIndex(
    vsplit                         *split,
    vbool                           cascadable,
    int                             axis,
    int                             index,
    int                             coord
    );

int vsplitAddPartition(
    vsplit                         *split,
    vbool                           cascadable,
    int                             axis,
    int                             coord
    );

void vsplitRemovePartition(
    vsplit                         *split,
    int                             axis,
    int                             index
    );

void vsplitTranspose(
    vsplit                         *split
    );

vdialogItem *vsplitGetCellItem(
    vsplit                         *split,
    int                             row,
    int                             col
    );

void vsplitSetItemArrangeable(
    vsplit                         *split,
    vdialogItem                    *item,
    vbool                           arr
    );

vbool vsplitIsItemArrangeable(
    vsplit                         *split,
    vdialogItem                    *item
    );

/**** new methods ****/

void vsplitSplit(
    vsplit                         *split,
    int                             axis,
    int                             coord
    );

void vsplitSplitBidir(
    vsplit                         *split,
    int                             x,
    int                             y
    );

vsplitSash *vsplitGetPartitionSash(
    vsplit                         *split,
    int                             axis,
    int                             index
    );

void vsplitSetTrackNotify(
    vsplit                         *split,
    vsplitTrackNoteProc             notify
    );

vsplitTrackNoteProc vsplitGetTrackNotify(
    vsplit                         *split
    );

void vsplitNotifyTrack(
    vsplit                         *split,
    int                             message,
    const vsplitTrackEvent         *event
    );

int vsplitGetSashCount(
    vsplit                         *split
    );

void vsplitSetLiveDrag(
    vsplit                         *split,
    vbool                           onOff
    );

vbool vsplitHasLiveDrag(
    vsplit                         *split
    );

void vsplitSetJunctionDrag(
    vsplit                         *split,
    vbool                           onOff
    );

vbool vsplitIsJunctionDrag(
    vsplit                         *split
    );

void vsplitSetAlternateStyle(
    vsplit                         *split,
    vbool                           onOff
    );

vbool vsplitIsAlternateStyle(
    vsplit                         *split
    );

/*
 * sashes
 */

vsplitSashClass *vsplitSashGetDefaultClass(
    void
    );

/**** inherited methods ****/

vsplitSash *vsplitSashCreateOfClass(
    vsplitSashClass                *clas
    );

vsplitSash *vsplitSashCreate(
    void
    );

vsplitSash *vsplitSashClone(
    vsplitSash                     *sash
    );

void vsplitSashInitOfClass(
    vsplitSash                     *sash,
    vsplitSashClass                *clas
    );

void vsplitSashInit(
    vsplitSash                     *sash
    );

void vsplitSashDestroy(
    vsplitSash                     *sash
    );

void vsplitSashCopy(
    vsplitSash                     *sash,
    vsplitSash                     *target
    );

void vsplitSashCopyInit(
    vsplitSash                     *sash,
    vsplitSash                     *target
    );

vsplitSash *vsplitSashLoad(
    vresource                       resource
    );

void vsplitSashLoadInit(
    vsplitSash                     *sash,
    vresource                       resource
    );

void vsplitSashStore(
    vsplitSash                     *sash,
    vresource                       resource
    );

void vsplitSashShow(
    vsplitSash                     *sash
    );

void vsplitSashHide(
    vsplitSash                     *sash
    );

void vsplitSashEnable(
    vsplitSash                     *sash
    );

void vsplitSashDisable(
    vsplitSash                     *sash
    );

void vsplitSashSetNotify(
    vsplitSash                     *sash,
    vsplitSashNoteProc              noteProc
    );

void vsplitSashSetData(
    vsplitSash                     *sash,
    const void                     *data
    );

vobjectAttributed *vsplitSashGetObject(
    vsplitSash                     *sash
    );

vdialogItem *vsplitSashGetItem(
    vsplitSash                     *sash
    );

vsplitSashClass *vsplitSashGetClass(
    vsplitSash                     *sash
    );

vsplitSashNoteProc vsplitSashGetNotify(
    vsplitSash                     *sash
    );

const void *vsplitSashGetData(
    vsplitSash                     *sash
    );

int vsplitSashIsShown(
    vsplitSash                     *sash
    );

int vsplitSashIsEnabled(
    vsplitSash                     *sash
    );

/**** new methods ****/

void vsplitSashSetDraggable(
    vsplitSash                     *sash,
    vbool                           onOff
    );

vbool vsplitSashIsDraggable(
    vsplitSash                     *sash
    );

void vsplitSashSetAlternateStyle(
    vsplitSash                     *sash,
    vbool                           onOff
    );

vbool vsplitSashIsAlternateStyle(
    vsplitSash                     *sash
    );

void vsplitSashInsertJunction(
    vsplitSash                     *sash,
    vsplitJunction                 *junction,
    int                             before
    );

void vsplitSashAppendJunction(
    vsplitSash                     *sash,
    vsplitJunction                 *junction
    );

vsplitJunction *vsplitSashDeleteJunction(
    vsplitSash                     *sash,
    int                             index
    );

int vsplitSashGetJunctionCount(
    vsplitSash                     *sash
    );

vsplitJunction *vsplitSashGetJunctionAt(
    vsplitSash                     *sash,
    int                             index
    );

void vsplitSashTrack(
    vsplitSash                     *sash,
    int                             message,
    int                             coord,
    vbool                           indep
    );

void vsplitSashCalcRange(
    vsplitSash                     *sash,
    int                            *low,
    int                            *high
    );

void vsplitSashCalcHitRects(
    vsplitSash                     *sash,
    vrect                         **rects,
    int                            *count
    );

void vsplitSashUpdateHitRects(
    vsplitSash                     *sash
    );

void vsplitSashGetHitRects(
    vsplitSash                     *sash,
    const vrect                   **rects,
    int                            *count
    );

void vsplitSashSetTrackNotify(
    vsplitSash                     *sash,
    vsplitSashTrackNoteProc         notify
    );

vsplitSashTrackNoteProc vsplitSashGetTrackNotify(
    vsplitSash                     *sash
    );

void vsplitSashNotifyTrack(
    vsplitSash                     *sash,
    int                             message,
    int                             coord
    );

void vsplitSashSetTrackState(
    vsplitSash                     *sash,
    const vsplitSashTrackState     *state
    );

const vsplitSashTrackState *vsplitSashGetTrackState(
    vsplitSash                     *sash
    );

void vsplitSashDrawMarquee(
    vsplitSash                     *sash,
    const vrect                    *rect
    );

void vsplitSashHilite(
    vsplitSash                     *sash
    );

void vsplitSashUnhilite(
    vsplitSash                     *sash
    );

vbool vsplitSashIsHilited(
    vsplitSash                     *sash
    );

void vsplitSashSetAxis(
    vsplitSash                     *sash,
    int                             axis
    );

int vsplitSashGetAxis(
    vsplitSash                     *sash
    );

void vsplitSashSetID(
    vsplitSash                     *sash,
    int                             id
    );

int vsplitSashGetID(
    vsplitSash                     *sash
    );

int vsplitSashGetJunctionIndex(
    vsplitSash                     *sash,
    vsplitJunction                 *junction
    );

vbool vsplitSashHasMarquee(
    vsplitSash                     *sash
    );

void vsplitSashMove(
    vsplitSash                     *sash,
    int                             type,
    vevent                         *event  /* = NULL */
    );

/*
 * junctions
 */

vsplitJunctionClass *vsplitJunctionGetDefaultClass(
    void
    );

/**** inherited methods ****/

vsplitJunction *vsplitJunctionCreateOfClass(
    vsplitJunctionClass            *clas
    );

vsplitJunction *vsplitJunctionCreate(
    void
    );

vsplitJunction *vsplitJunctionClone(
    vsplitJunction                 *junction
    );

void vsplitJunctionInitOfClass(
    vsplitJunction                 *junction,
    vsplitJunctionClass            *clas
    );

void vsplitJunctionInit(
    vsplitJunction                 *junction
    );

void vsplitJunctionDestroy(
    vsplitJunction                 *junction
    );

void vsplitJunctionCopy(
    vsplitJunction                 *junction,
    vsplitJunction                 *target
    );

void vsplitJunctionCopyInit(
    vsplitJunction                 *junction,
    vsplitJunction                 *target
    );

vsplitJunction *vsplitJunctionLoad(
    vresource                       resource
    );

void vsplitJunctionLoadInit(
    vsplitJunction                 *junction,
    vresource                       resource
    );

void vsplitJunctionStore(
    vsplitJunction                 *junction,
    vresource                       resource
    );

void vsplitJunctionShow(
    vsplitJunction                 *junction
    );

void vsplitJunctionHide(
    vsplitJunction                 *junction
    );

void vsplitJunctionEnable(
    vsplitJunction                 *junction
    );

void vsplitJunctionDisable(
    vsplitJunction                 *junction
    );

void vsplitJunctionSetNotify(
    vsplitJunction                 *junction,
    vsplitJunctionNoteProc          noteProc
    );

void vsplitJunctionSetData(
    vsplitJunction                 *junction,
    const void                     *data
    );

vobjectAttributed *vsplitJunctionGetObject(
    vsplitJunction                 *junction
    );

vdialogItem *vsplitJunctionGetItem(
    vsplitJunction                 *junction
    );

vsplitJunctionClass *vsplitJunctionGetClass(
    vsplitJunction                 *junction
    );

vsplitJunctionNoteProc vsplitJunctionGetNotify(
    vsplitJunction                 *junction
    );

const void *vsplitJunctionGetData(
    vsplitJunction                 *junction
    );

int vsplitJunctionIsShown(
    vsplitJunction                 *junction
    );

int vsplitJunctionIsEnabled(
    vsplitJunction                 *junction
    );

/**** new methods ****/

void vsplitJunctionSetSash(
    vsplitJunction                 *junction,
    int                             axis,
    vsplitSash                     *sash
    );

vsplitSash *vsplitJunctionGetSash(
    vsplitJunction                 *junction,
    int                             axis
    );

int vsplitJunctionGetPartition(
    vsplitJunction                 *junction,
    int                             axis
    );

void vsplitJunctionChangedSashAttribute(
    vsplitJunction                 *junction,
    const vname                    *attr,
    vdict                          *context
    );

void vsplitJunctionHilite(
    vsplitJunction                 *junction
    );

void vsplitJunctionUnhilite(
    vsplitJunction                 *junction
    );

vbool vsplitJunctionIsHilited(
    vsplitJunction                 *junction
    );

void vsplitJunctionMove(
    vsplitJunction                 *junction,
    int                             type,
    vevent                         *event  /* = NULL */
    );


/*
 * * * * * * * * * * PRIVATE FUNCTION PROTOTYPES * * * * * * * * * * *
 */


/*
 * * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * * *
 */

/*
 * split containers
 */

vportALIAS(vsplitItemList, vdialogItemList)

typedef struct _vsplitExtra         _vsplitExtra;

struct vsplit
{
    vgridcontainer                  grid;
    vsplitTrackNoteProc             trackNotify;
    unsigned short                  flags;
    int                             numSashes;
    _vsplitExtra                   *extra;
};

#define vsplitCLASS(CLASS, OBJECT, NOTIFY, PNOTIFY, TNOTIFY)                   \
    vgridcontainerCLASS(CLASS, OBJECT, NOTIFY, PNOTIFY);                       \
    vclassVARIABLE(vsplitSASH_CLASS, vsplitSashClass*);                        \
    vclassVARIABLE(vsplitJUNCTION_CLASS, vsplitJunctionClass*);                \
    vclassMETHOD(vsplitSPLIT,                                                  \
                 (OBJECT *sp, int axis, int coord));                           \
    vclassMETHOD(vsplitSPLIT_BIDIR,                                            \
                 (OBJECT *sp, int x, int y));                                  \
    vclassMETHOD(vsplitSET_LIVE_DRAG,                                          \
                 (OBJECT *sp, vbool onOff));                                   \
    vclassMETHOD(vsplitSET_JUNCTION_DRAG,                                      \
                 (OBJECT *sp, vbool onOff));                                   \
    vclassMETHOD(vsplitSET_ALTERNATE_STYLE, (OBJECT *sp, vbool f));            \
    vclassMETHOD(vsplitNOTIFY_TRACK,                                           \
                 (OBJECT *sp, int msg, const vsplitTrackEvent *e));            \
    vclassMETHOD(vsplitSET_TRACK_NOTIFY, (OBJECT *sp, TNOTIFY n))

struct vsplitClass
{
    vsplitCLASS(vsplitClass, vsplit, vsplitNoteProc, vsplitPartitionNoteProc,
                vsplitTrackNoteProc);
};


/*
 * sashes
 */

typedef struct _vsplitSashExtra     _vsplitSashExtra;

struct vsplitSash
{
    vdialogItem                     item;
    vsplitSashTrackNoteProc         trackNotify;
    int                             axis;
    int                             id;
    unsigned short                  flags;
    _vsplitSashExtra               *extra;
};

#define vsplitSashCLASS(CLASS, OBJECT, NOTIFY, TNOTIFY, SPLIT)                 \
    vdialogITEM_CLASS(CLASS, OBJECT, NOTIFY);                                  \
    vclassVARIABLE(vsplitSashHORIZ_CURSOR, vcursor*);                          \
    vclassVARIABLE(vsplitSashVERT_CURSOR, vcursor*);                           \
    vclassMETHOD(vsplitSashINSERT_JUNCTION,                                    \
                 (OBJECT *sash, vsplitJunction *jct, int before));             \
    vclassMETHOD_RET(vsplitSashDELETE_JUNCTION, vsplitJunction*,               \
                     (OBJECT *sash, int index));                               \
    vclassMETHOD_RET(vsplitSashHAS_MARQUEE, vbool, (OBJECT *sash));            \
    vclassMETHOD(vsplitSashTRACK,                                              \
                 (OBJECT *sash, int message, int x, vbool cursor));            \
    vclassMETHOD(vsplitSashSET_TRACK_NOTIFY, (OBJECT *sash, TNOTIFY n));       \
    vclassMETHOD(vsplitSashNOTIFY_TRACK,                                       \
                 (OBJECT *sash, int msg, int coord));                          \
    vclassMETHOD(vsplitSashCALC_RANGE, (OBJECT *sash, int *low, int *high));   \
    vclassMETHOD(vsplitSashCALC_HIT_RECTS,                                     \
                 (OBJECT *sash, vrect **rects, int *count));                   \
    vclassMETHOD(vsplitSashDRAW_MARQUEE, (OBJECT *sash, const vrect *rect));   \
    vclassMETHOD(vsplitSashHILITE, (OBJECT *sash));                            \
    vclassMETHOD(vsplitSashUNHILITE, (OBJECT *sash));                          \
    vclassMETHOD(vsplitSashSET_DRAGGABLE, (OBJECT *sash, vbool f));            \
    vclassMETHOD(vsplitSashSET_ALTERNATE_STYLE, (OBJECT *sash, vbool f));      \
    vclassMETHOD(vsplitSashSET_AXIS, (OBJECT *sash, int axis));                \
    vclassMETHOD(vsplitSashSET_ID, (OBJECT *sash, int id));                    \
    vclassMETHOD(vsplitSashMOVE, (OBJECT *sash, int type, vevent *event));     \
    vclassMETHOD(vsplitSashSET_TRACK_STATE,                                    \
                 (OBJECT *sash, const vsplitSashTrackState *state))

struct vsplitSashClass
{
    vsplitSashCLASS(vsplitSashClass, vsplitSash, vsplitSashNoteProc,
                    vsplitSashTrackNoteProc, vsplit);
};


/*
 * junctions
 */

typedef struct _vsplitJunctionExtra _vsplitJunctionExtra;

struct vsplitJunction
{
    vdialogItem                     item;
    vsplitSash                     *horizSash;
    vsplitSash                     *vertSash;
    unsigned short                  flags;
    _vsplitJunctionExtra           *extra;
};

#define vsplitJunctionCLASS(CLASS, OBJECT, NOTIFY, SPLIT)                      \
    vdialogITEM_CLASS(CLASS, OBJECT, NOTIFY);                                  \
    vclassVARIABLE(vsplitJunctionCURSOR, vcursor*);                            \
    vclassMETHOD(vsplitJunctionCHANGED_SASH_ATTRIBUTE,                         \
                 (OBJECT *jct, const vname *attr, vdict *context));            \
    vclassMETHOD(vsplitJunctionHILITE, (OBJECT *jct));                         \
    vclassMETHOD(vsplitJunctionUNHILITE, (OBJECT *jct));                       \
    vclassMETHOD(vsplitJunctionMOVE, (OBJECT *jct, int type, vevent *event));  \
    vclassMETHOD(vsplitJunctionSET_SASH,                                       \
                 (OBJECT *jct, int axis, vsplitSash *sash))

struct vsplitJunctionClass
{
    vsplitJunctionCLASS(vsplitJunctionClass, vsplitJunction,
                        vsplitJunctionNoteProc, vsplit);
};


/*
 * * * * * * * * * * * * * * PRIVATE CONSTANTS * * * * * * * * * * * * *
 */

enum {
    _vsplitLIVE_DRAG       = 0x0001,
    _vsplitJUNCTION_DRAG   = 0x0002,
    _vsplitALT_STYLE       = 0x0004
};


enum {
    _vsplitSashHILITED     = 0x0001,
    _vsplitSashDRAGGABLE   = 0x0002,
    _vsplitSashALT_STYLE   = 0x0004
};


enum {
    _vsplitJunctionHILITED     = 0x0001
};


/*
 * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * *
 */

/*
 * split containers
 */

#define vsplitGetGrid(s)        vportBASE_OBJECT(s, grid)
#define vsplitGetContainer(s)   vgridcontainerGetContainer(vsplitGetGrid(s))
#define vsplitGetItem(s)        vgridcontainerGetItem(vsplitGetGrid(s))
#define vsplitGetObject(s)      vgridcontainerGetObject(vsplitGetGrid(s))

#define vsplitCreateOfClass(cl) \
    ((vsplit*)vgridcontainerCreateOfClass((vgridcontainerClass*)(cl)))
#define vsplitCreate() \
    vsplitCreateOfClass(vsplitGetDefaultClass())
#define vsplitClone(s) \
    ((vsplit*)vgridcontainerClone(vsplitGetGrid(s)))
#define vsplitInitOfClass(s, cl) \
    vgridcontainerInitOfClass(vsplitGetGrid(s), (vgridcontainerClass*)(cl))
#define vsplitInit(s) \
    vsplitInitOfClass(s, vsplitGetDefaultClass())
#define vsplitCopyInit(s, t) \
    vgridcontainerCopyInit(vsplitGetGrid(s), vsplitGetGrid(t))
#define vsplitLoad(r)         ((vsplit*)vgridcontainerLoad(r))
#define vsplitLoadInit(s, r) \
    vgridcontainerLoadInit(vsplitGetGrid(s), (r))
#define vsplitDestroy(s) \
    vgridcontainerDestroy(vsplitGetGrid(s))

#define vsplitGetClass(s) \
    ((vsplitClass*)vgridcontainerGetClass(vsplitGetGrid(s)))

#define vsplitGetNotify(s) \
    ((vsplitNoteProc)vgridcontainerGetNotify(vsplitGetGrid(s)))
#define vsplitSetNotify(s, n) \
    vgridcontainerSetNotify((vgridcontainer *)(s), (vgridcontainerNoteProc)(n))
#define vsplitSetTitle(s, t)    vgridcontainerSetTitle(vsplitGetGrid(s), (t))
#define vsplitGetData(s)        vgridcontainerGetData(vsplitGetGrid(s))
#define vsplitGetTitle(s)       vgridcontainerGetTitle(vsplitGetGrid(s))
#define vsplitIsEnabled(s)      vgridcontainerIsEnabled(vsplitGetGrid(s))
#define vsplitHasBorder(s)      vgridcontainerHasBorder(vsplitGetGrid(s))
#define vsplitGetContent(s)     vgridcontainerGetContent(vsplitGetGrid(s))
#define vsplitGetBounds(s)      vgridcontainerGetBounds(vsplitGetGrid(s))
#define vsplitIsFlat(s)         vgridcontainerIsFlat(vsplitGetGrid(s))
#define vsplitHasScrollX(s)     vgridcontainerHasScrollX(vsplitGetGrid(s))
#define vsplitHasScrollY(s)     vgridcontainerHasScrollY(vsplitGetGrid(s))
#define vsplitGetItemList(s)    vgridcontainerGetItemList(vsplitGetGrid(s))
#define vsplitGetFocus(s)       vgridcontainerGetFocus(vsplitGetGrid(s))
#define vsplitGetDefFocus(s)    vgridcontainerGetDefFocus(vsplitGetGrid(s))
#define vsplitGetSolution(s)    vgridcontainerGetSolution(vsplitGetGrid(s))
#define vsplitGetItemCount(s)   vgridcontainerGetItemCount(vsplitGetGrid(s))
#define vsplitGetItemAt(s, i)   vgridcontainerGetItemAt(vsplitGetGrid(s), (i))
#define vsplitGetItemIndex(s, i) \
    vgridcontainerGetItemIndex(vsplitGetGrid(s), (i))
#define vsplitFindItem(s, t)    vgridcontainerFindItem(vsplitGetGrid(s), (t))
#define vsplitGetSelection(s)   vgridcontainerGetSelection(vsplitGetGrid(s))
#define vsplitCopy(s, t)        \
    vgridcontainerCopy(vsplitGetGrid(s), vsplitGetGrid(t))
#define vsplitStore(s, r)       vgridcontainerStore(vsplitGetGrid(s), (r)
#define vsplitEnable(s)         vgridcontainerEnable(vsplitGetGrid(s))
#define vsplitDisable(s)        vgridcontainerDisable(vsplitGetGrid(s))
#define vsplitAppendItem(s, i)  vgridcontainerAppendItem(vsplitGetGrid(s), (i))
#define vsplitDeleteItem(s, i)  vgridcontainerDeleteItem(vsplitGetGrid(s), (i))
#define vsplitSetItemIndex(s, i, n) \
    vgridcontainerSetItemIndex(vsplitGetGrid(s), (i), (n))
#define vsplitArrange(s, r)     vgridcontainerArrange(vsplitGetGrid(s), (r))
#define vsplitCalcMinSize(s, w, h) \
    vgridcontainerCalcMinSize(vsplitGetGrid(s), (w), (h))
#define vsplitSetData(s, d)     vgridcontainerSetData(vsplitGetGrid(s), (d))
#define vsplitSetTitleScribed(s, t) \
    vgridcontainerSetTitleScribed(vsplitGetGrid(s), (t))
#define vsplitSetBorder(s, f)   vgridcontainerSetBorder(vsplitGetGrid(s), (f))
#define vsplitSetBounds(s, r)   vgridcontainerSetBounds(vsplitGetGrid(s), (f))
#define vsplitSetFlat(s, f)     vgridcontainerSetFlat(vsplitGetGrid(s), (f))
#define vsplitSetScrollX(s, f)  vgridcontainerSetScrollX(vsplitGetGrid(s), (f))
#define vsplitSetScrollY(s, f)  vgridcontainerSetScrollY(vsplitGetGrid(s), (f))
#define vsplitSetFocus(s, i)    vgridcontainerSetFocus(vsplitGetGrid(s), (i))
#define vsplitSetDefFocus(s, i) vgridcontainerSetDefFocus(vsplitGetGrid(s), (i))
#define vsplitSetSolution(s, n) vgridcontainerSetSolution(vsplitGetGrid(s), (n))
#define vsplitSetSelection(s, i) \
    vgridcontainerSetSelection(vsplitGetGrid(s), (i))

#define vsplitGetMajorAxis(s)   vgridcontainerGetMajorAxis(vsplitGetGrid(s))
#define vsplitGetSpacing(s, h)  vgridcontainerGetSpacing(vsplitGetGrid(s), (h))
#define vsplitGetUpdateMode(s)  vgridcontainerGetUpdateMode(vsplitGetGrid(s))
#define vsplitGetPartitionCount(s, v) \
    vgridcontainerGetPartitionCount(vsplitGetGrid(s), (v))
#define vsplitGetRowCount(s)    vgridcontainerGetRowCount(vsplitGetGrid(s))
#define vsplitGetColumnCount(s) vgridcontainerGetColumnCount(vsplitGetGrid(s))
#define vsplitGetItemMinSize(s, i, w, h) \
    vgridcontainerGetItemMinSize(s, i, w, h)
#define vsplitGetItemMinWidth(s, i) \
    vgridcontainerGetItemMinWidth(s, i)
#define vsplitGetItemMinHeight(s, i) \
    vgridcontainerGetItemMinHeight(s, i)
#define vsplitIsItemVisible(s, i) \
    vgridcontainerIsItemVisible(s, i)
#define vsplitGetPartitionSpacing(s, h, i) \
    vgridcontainerGetPartitionSpacing(vsplitGetGrid(s), (h), (i))
#define vsplitDeterminePartitionSpacing(s, h, i) \
    vgridcontainerDeterminePartitionSpacing(vsplitGetGrid(s), (h), (i))
#define vsplitIsPartitionCascadable(s, h, i) \
    vgridcontainerIsPartitionCascadable(vsplitGetGrid(s), (h), (i))
#define vsplitGetPartitionPosition(s, h, i) \
    vgridcontainerGetPartitionPosition(vsplitGetGrid(s), (h), (i))

#define vsplitSetItemMinSize(s, i, w, h) \
    vgridcontainerSetItemMinSize(s, i, w, h)
#define vsplitSetMajorAxis(s, a) \
    vgridcontainerSetMajorAxis(vsplitGetGrid(s), (a))
#define vsplitSetSpacing(s, h, x) \
    vgridcontainerSetSpacing(vsplitGetGrid(s), (h), (x))
#define vsplitSetUpdateMode(s, m) \
    vgridcontainerSetUpdateMode(vsplitGetGrid(s), (m))
#define vsplitSetPartitionSpacing(s, v, i, x) \
    vgridcontainerSetPartitionSpacing(vsplitGetGrid(s), (v), (i), (x))
#define vsplitSetPartitionCascadable(s, v, i, c) \
    vgridcontainerSetPartitionCascadable(vsplitGetGrid(s), (v), (i), (c))
#define vsplitSetPartitionPosition(s, v, i, x) \
    vgridcontainerSetPartitionPosition(vsplitGetGrid(s), (v), (i), (x))
#define vsplitCalcPartitionRange(s, v, i, m, M) \
    vgridcontainerCalcPartitionRange(vsplitGetGrid(s), (v), (i), (m), (M))
#define vsplitAddPartitionAtIndex(s, c, v, i, x) \
    vgridcontainerAddPartitionAtIndex(vsplitGetGrid(s), (c), (v), (i), (x))
#define vsplitAddPartition(s, c, v, x) \
    vgridcontainerAddPartition(vsplitGetGrid(s), (c), (v), (x))
#define vsplitRemovePartition(s, v, i) \
    vgridcontainerRemovePartition(vsplitGetGrid(s), (v), (i))
#define vsplitTranspose(s) \
    vgridcontainerTranspose(vsplitGetGrid(s))

#define vsplitSetPartitionNotify(s, n) \
    vgridcontainerSetPartitionNotify(vsplitGetGrid(s), \
                                     (vgridcontainerPartitionNoteProc)(n))
#define vsplitGetPartitionNotify(s) \
   ((vsplitPartitionNoteProc)vgridcontainerGetPartitionNotify(vsplitGetGrid(s)))
#define vsplitNotifyPartition(s, m, v, i) \
    vgridcontainerNotifyPartition(vsplitGetGrid(s), (m), (v), (i))
#define vsplitGetCellItem(s, r, c) \
    vgridcontainerGetCellItem(vsplitGetGrid(s), (r), (c))
#define vsplitIsItemArrangeable(s, i) \
    vgridcontainerIsItemArrangeable(vsplitGetGrid(s), (i))
#define vsplitSetItemArrangeable(s, i, f) \
    vgridcontainerSetItemArrangeable(vsplitGetGrid(s), (i), (f))

/**** split container api implemented as macros ****/

#define vsplitGetTrackNotify(s)       ((s)->trackNotify)
#define vsplitHasLiveDrag(s)          (((s)->flags&_vsplitLIVE_DRAG)!=0)
#define vsplitIsJunctionDrag(s)       (((s)->flags&_vsplitJUNCTION_DRAG)!=0)
#define vsplitIsAlternateStyle(s)     (((s)->flags&_vsplitALT_STYLE)!=0)
#define vsplitGetSashCount(s)         ((s)->numSashes)


/*
 * sashes
 */

#define vsplitSashGetItem(s)          vportBASE_OBJECT(s, item)
#define vsplitSashGetObject(s)        vdialogGetItemObject(vsplitSashGetItem(s))

#define vsplitSashCreateOfClass(c) \
    ((vsplitSash*)vdialogCreateItemOfClass((vdialogItemClass*)(c)))
#define vsplitSashCreate() \
    vsplitSashCreateOfClass(vsplitSashGetDefaultClass())
#define vsplitSashClone(s) \
    ((vsplitSash*)vdialogCloneItem(vsplitSashGetItem(s)))
#define vsplitSashInitOfClass(s, c) \
    vdialogInitItemOfClass(vsplitSashGetItem(s), (vdialogItemClass*)(c))
#define vsplitSashInit(s) \
    vsplitSashInitOfClass(s, vsplitSashGetDefaultClass())
#define vsplitSashCopyInit(s, t) \
    vdialogCopyInitItem(vsplitSashGetItem(s), vsplitSashGetItem(t))
#define vsplitSashLoad(r) \
    ((vsplitSash*)vdialogLoadItem(r))
#define vsplitSashLoadInit(s, r) \
    vdialogLoadInitItem(vsplitSashGetItem(s), r)
#define vsplitSashDestroy(s) \
    vdialogDestroyItem(vsplitSashGetItem(s))

#define vsplitSashGetClass(s) \
    ((vsplitSashClass*)vdialogGetItemClass(vsplitSashGetItem(s)))

#define vsplitSashGetNotify(s) \
    ((vsplitSashNoteProc)vdialogGetItemNotify(vsplitSashGetItem(s)))
#define vsplitSashSetNotify(s, n) \
    vdialogSetItemNotify(vsplitSashGetItem(s), (vdialogItemNoteProc)(n))
#define vsplitSashGetData(s) \
    vdialogGetItemData(vsplitSashGetItem(s))
#define vsplitSashIsShown(s) \
    vdialogItemIsShown(vsplitSashGetItem(s))
#define vsplitSashIsEnabled(s) \
    vdialogItemIsEnabled(vsplitSashGetItem(s))
#define vsplitSashCopy(s, t) \
    vdialogCopyItem(vsplitSashGetItem(s), vsplitSashGetItem(t))
#define vsplitSashStore(s, r) \
    vdialogStoreItem(vsplitSashGetItem(s), (r))
#define vsplitSashShow(s) \
    vdialogShowItem(vsplitSashGetItem(s))
#define vsplitSashHide(s) \
    vdialogHideItem(vsplitSashGetItem(s))
#define vsplitSashEnable(s) \
    vdialogEnableItem(vsplitSashGetItem(s))
#define vsplitSashDisable(s) \
    vdialogDisableItem(vsplitSashGetItem(s))
#define vsplitSashSetData(s, d) \
    vdialogSetItemData(vsplitSashGetItem(s), (d))

/**** sash api implemented as macros ****/

#define vsplitSashIsDraggable(s)       (((s)->flags&_vsplitSashDRAGGABLE)!=0)
#define vsplitSashIsAlternateStyle(s)  (((s)->flags&_vsplitSashALT_STYLE)!=0)
#define vsplitSashIsHilited(s)         (((s)->flags&_vsplitSashHILITED)!=0)
#define vsplitSashGetAxis(s)           ((s)->axis)
#define vsplitSashGetID(s)             ((s)->id)
#define vsplitSashGetTrackNotify(s)    ((s)->trackNotify)


/*
 * junctions
 */

#define vsplitJunctionGetItem(j)                vportBASE_OBJECT(j, item)
#define vsplitJunctionGetObject(j) \
    vdialogGetItemObject(vsplitJunctionGetItem(j))

#define vsplitJunctionCreateOfClass(c) \
    ((vsplitJunction*)vdialogCreateItemOfClass((vdialogItemClass*)(c)))
#define vsplitJunctionCreate() \
    vsplitJunctionCreateOfClass(vsplitJunctionGetDefaultClass())
#define vsplitJunctionClone(j) \
    ((vsplitJunction*)vdialogCloneItem(vsplitJunctionGetItem(j)))
#define vsplitJunctionInitOfClass(j, c) \
    vdialogInitItemOfClass(vsplitJunctionGetItem(j), (vdialogItemClass*)(c))
#define vsplitJunctionInit(j) \
    vsplitJunctionInitOfClass(j, vsplitJunctionGetDefaultClass())
#define vsplitJunctionCopyInit(j, t) \
    vdialogCopyInitItem(vsplitJunctionGetItem(j), vsplitJunctionGetItem(t))
#define vsplitJunctionLoad(r) \
    ((vsplitJunction*)vdialogLoadItem(r))
#define vsplitJunctionLoadInit(j, r) \
    vdialogLoadInitItem(vsplitJunctionGetItem(j), r)
#define vsplitJunctionDestroy(j) \
    vdialogDestroyItem(vsplitJunctionGetItem(j))

#define vsplitJunctionGetClass(j) \
    ((vsplitJunctionClass*)vdialogGetItemClass(vsplitJunctionGetItem(j)))

#define vsplitJunctionGetNotify(j) \
    ((vsplitJunctionNoteProc)vdialogGetItemNotify(vsplitJunctionGetItem(j)))
#define vsplitJunctionSetNotify(j, n) \
    vdialogSetItemNotify(vsplitJunctionGetItem(j), (vdialogItemNoteProc)(n))
#define vsplitJunctionGetData(j) \
    vdialogGetItemData(vsplitJunctionGetItem(j))
#define vsplitJunctionIsShown(j) \
    vdialogItemIsShown(vsplitJunctionGetItem(j))
#define vsplitJunctionIsEnabled(j) \
    vdialogItemIsEnabled(vsplitJunctionGetItem(j))
#define vsplitJunctionCopy(j, t) \
    vdialogCopyItem(vsplitJunctionGetItem(j), vsplitJunctionGetItem(t))
#define vsplitJunctionStore(j, r) \
    vdialogStoreItem(vsplitJunctionGetItem(j), (r))
#define vsplitJunctionShow(j) \
    vdialogShowItem(vsplitJunctionGetItem(j))
#define vsplitJunctionHide(j) \
    vdialogHideItem(vsplitJunctionGetItem(j))
#define vsplitJunctionEnable(j) \
    vdialogEnableItem(vsplitJunctionGetItem(j))
#define vsplitJunctionDisable(j) \
    vdialogDisableItem(vsplitJunctionGetItem(j))
#define vsplitJunctionSetData(j, d) \
    vdialogSetItemData(vsplitJunctionGetItem(j), (d))

/**** junction api implemented as macros ****/

#define vsplitJunctionGetSash(j, v) \
    ((v) == vsplitHORIZONTAL ? (j)->horizSash : (j)->vertSash)
#define vsplitJunctionIsHilited(j)   (((j)->flags&_vsplitJunctionHILITED)!=0)


/*
 * * * * * * * * * * PRIVATE FUNCTION MESSAGE DEFINITIONS * * * * * * * * * *
 */

/*
 * split containers
 */

#define vsplitSplit(s, a, x) \
    vclassSend(vsplitGetClass(s), vsplitSPLIT, (s, a, x))
#define vsplitSplitBidir(s, x, y) \
    vclassSend(vsplitGetClass(s), vsplitSPLIT_BIDIR, (s, x, y))
#define vsplitSetLiveDrag(s, f) \
    vclassSend(vsplitGetClass(s), vsplitSET_LIVE_DRAG, (s, f))
#define vsplitSetJunctionDrag(s, f) \
    vclassSend(vsplitGetClass(s), vsplitSET_JUNCTION_DRAG, (s, f))
#define vsplitSetAlternateStyle(s, f) \
    vclassSend(vsplitGetClass(s), vsplitSET_ALTERNATE_STYLE, (s, f))
#define vsplitSetTrackNotify(s, n) \
    vclassSend(vsplitGetClass(s), vsplitSET_TRACK_NOTIFY, (s, n))
#define vsplitNotifyTrack(s, m, e) \
    vclassSend(vsplitGetClass(s), vsplitNOTIFY_TRACK, (s, m, e))

/*
 * sashes
 */

#define vsplitSashSetDraggable(s, f) \
    vclassSend(vsplitSashGetClass(s), vsplitSashSET_DRAGGABLE, (s, f))
#define vsplitSashSetAlternateStyle(s, f) \
    vclassSend(vsplitSashGetClass(s), vsplitSashSET_ALTERNATE_STYLE, (s, f))
#define vsplitSashInsertJunction(s, j, i) \
    vclassSend(vsplitSashGetClass(s), vsplitSashINSERT_JUNCTION, (s, j, i))
#define vsplitSashDeleteJunction(s, i) \
    vclassSend(vsplitSashGetClass(s), vsplitSashDELETE_JUNCTION, (s, i))
#define vsplitSashHasMarquee(s) \
    vclassSend(vsplitSashGetClass(s), vsplitSashHAS_MARQUEE, (s))
#define vsplitSashCalcRange(s, l, h) \
    vclassSend(vsplitSashGetClass(s), vsplitSashCALC_RANGE, (s, l, h))
#define vsplitSashCalcHitRects(s, r, c) \
    vclassSend(vsplitSashGetClass(s), vsplitSashCALC_HIT_RECTS, (s, r, c))
#define vsplitSashTrack(s, m, x, c) \
    vclassSend(vsplitSashGetClass(s), vsplitSashTRACK, (s, m, x, c))
#define vsplitSashSetTrackNotify(s, n) \
    vclassSend(vsplitSashGetClass(s), vsplitSashSET_TRACK_NOTIFY, (s, n))
#define vsplitSashNotifyTrack(s, m, x) \
    vclassSend(vsplitSashGetClass(s), vsplitSashNOTIFY_TRACK, (s, m, x))
#define vsplitSashDrawMarquee(s, r) \
    vclassSend(vsplitSashGetClass(s), vsplitSashDRAW_MARQUEE, (s, r))
#define vsplitSashHilite(s) \
    vclassSend(vsplitSashGetClass(s), vsplitSashHILITE, (s))
#define vsplitSashUnhilite(s) \
    vclassSend(vsplitSashGetClass(s), vsplitSashUNHILITE, (s))
#define vsplitSashSetAxis(s, v) \
    vclassSend(vsplitSashGetClass(s), vsplitSashSET_AXIS, (s, v))
#define vsplitSashSetID(s, i) \
    vclassSend(vsplitSashGetClass(s), vsplitSashSET_ID, (s, i))
#define vsplitSashMove(s, t, e) \
    vclassSend(vsplitSashGetClass(s), vsplitSashMOVE, (s, t, e))
#define vsplitSashSetTrackState(s, t) \
    vclassSend(vsplitSashGetClass(s), vsplitSashSET_TRACK_STATE, (s, t))

/*
 * junctions
 */

#define vsplitJunctionChangedSashAttribute(j, a, c) \
    vclassSend(vsplitJunctionGetClass(j), \
               vsplitJunctionCHANGED_SASH_ATTRIBUTE, (j, a, c))
#define vsplitJunctionHilite(j) \
    vclassSend(vsplitJunctionGetClass(j), vsplitJunctionHILITE, (j))
#define vsplitJunctionUnhilite(j) \
    vclassSend(vsplitJunctionGetClass(j), vsplitJunctionUNHILITE, (j))
#define vsplitJunctionMove(j, t, e) \
    vclassSend(vsplitJunctionGetClass(j), vsplitJunctionMOVE, (j, t, e))
#define vsplitJunctionSetSash(j, v, s) \
    vclassSend(vsplitJunctionGetClass(j), vsplitJunctionSET_SASH, (j, v, s))


vportEND_CPLUSPLUS_EXTERN_C

#endif /* #ifndef vsplitINCLUDED */

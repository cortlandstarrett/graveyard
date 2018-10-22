/* $Id: vtbrearranger.h,v 1.7 1997/11/17 20:01:41 bill Exp $ */

/*--------------------------------------------------------------------------
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
                                                                           * 
    vtbrearranger.h                                                        * 
                                                                           * 
    C Interface file for Toolbar Rearrangers                               * 
                                                                           * 
    Copyright (c) 1997 Visix Software Inc.                                 * 
    All rights reserved                                                    * 
                                                                           * 
  -------------------------------------------------------------------------*/

#ifndef vtoolbarRearrangerINCLUDED
#define vtoolbarRearrangerINCLUDED

#ifndef vportINCLUDED
#include <vport.h>
#endif

#ifndef  vrectINCLUDED
#include vrectHEADER
#endif

#ifndef  vnameINCLUDED
#include vnameHEADER
#endif

#ifndef  vdictINCLUDED
#include vdictHEADER
#endif

#ifndef  vkeyINCLUDED
#include vkeyHEADER
#endif

#ifndef  veventINCLUDED
#include veventHEADER
#endif

#ifndef  vresourceINCLUDED
#include vresourceHEADER
#endif

#ifndef  vclassINCLUDED
#include vclassHEADER
#endif

#ifndef  voccurrenceINCLUDED
#include voccurrenceHEADER
#endif

#ifndef  vobjectINCLUDED
#include vobjectHEADER
#endif

#ifndef  vdialogINCLUDED
#include vdialogHEADER
#endif

#ifndef  vdragINCLUDED
#include vdragHEADER
#endif

#ifndef  vdropsiteINCLUDED
#include vdropsiteHEADER
#endif

#ifndef  vtoolbarSeparatorINCLUDED
#include vtoolbarSeparatorHEADER
#endif


vportBEGIN_CPLUSPLUS_EXTERN_C

/*-------------------------------------------------------------------------
 * * * PUBLIC CONSTANT DEFINITIONS  * * * * * * * * * * * * * * * * * * * *
  ------------------------------------------------------------------------*/

/* Arrange permissions for Rearranger */
enum {
    vtoolbarPERMIT_DRAG			= 0x0001,
    vtoolbarPERMIT_REMOVE		= 0x0002,
    vtoolbarPERMIT_INSERT		= 0x0004,
    vtoolbarPERMIT_INTRA_MOVE		= 0x0008,
    vtoolbarPERMIT_SOURCE_INTER_MOVE	= 0x0010,
    vtoolbarPERMIT_SINK_INTER_MOVE	= 0x0020,
    vtoolbarPERMIT_INTRA_COPY		= 0x0040,
    vtoolbarPERMIT_SOURCE_INTER_COPY	= 0x0080,
    vtoolbarPERMIT_SINK_INTER_COPY	= 0x0100,
    vtoolbarPERMIT_DESTROY_ON_REMOVE	= 0x0200,

    vtoolbarPERMIT_INTER_MOVE = 
        (vtoolbarPERMIT_SOURCE_INTER_MOVE|vtoolbarPERMIT_SINK_INTER_MOVE),
    vtoolbarPERMIT_INTER_COPY = 
        (vtoolbarPERMIT_SOURCE_INTER_COPY|vtoolbarPERMIT_SINK_INTER_COPY),

    vtoolbarPERMIT_MOVE  =
        (vtoolbarPERMIT_INTER_MOVE|vtoolbarPERMIT_INTRA_MOVE),
    vtoolbarPERMIT_COPY  =
        (vtoolbarPERMIT_INTER_COPY|vtoolbarPERMIT_INTRA_COPY),

    vtoolbarPERMIT_INTRA_REARRANGE =
    (vtoolbarPERMIT_DRAG|vtoolbarPERMIT_INTRA_MOVE|vtoolbarPERMIT_INTRA_COPY),

    vtoolbarPERMIT_REARRANGE	= (~0x0 & ~vtoolbarPERMIT_DESTROY_ON_REMOVE),
    vtoolbarPERMIT_ALL		= (~0x0)
};


/* Arrange Types for Rearrange Drags */
enum {
    vtoolbarREARRANGE_NOOP = 0,
    vtoolbarREARRANGE_DRAG,
    vtoolbarREARRANGE_INSERT,
    vtoolbarREARRANGE_REMOVE,
    vtoolbarREARRANGE_MOVE,
    vtoolbarREARRANGE_COPY
};
    

/* Rearranger Occurrence Types */
enum {
    vtoolbarREARRANGE_PRE_INSERT_OCCURRENCE,
    vtoolbarREARRANGE_PRE_REMOVE_OCCURRENCE,
    vtoolbarREARRANGE_PRE_MOVE_OCCURRENCE,
    vtoolbarREARRANGE_PRE_COPY_OCCURRENCE,
    vtoolbarREARRANGE_PRE_DESTROY_OCCURRENCE,
    vtoolbarREARRANGE_START_OCCURRENCE,
    vtoolbarREARRANGE_INSERT_OCCURRENCE,
    vtoolbarREARRANGE_REMOVE_OCCURRENCE,
    vtoolbarREARRANGE_MOVE_OCCURRENCE,
    vtoolbarREARRANGE_COPY_OCCURRENCE,
    vtoolbarREARRANGE_DESTROY_OCCURRENCE,
    _vtoolbarREARRANGE_OCCURRENCE_COUNT
};

#define vtoolbarREARRANGE_BINDING_MAP_DEFAULT_KEY ((vkeyModifiers)(~0))

/*-------------------------------------------------------------------------
 * * * PUBLIC TYPE DEFINITIONS  * * * * * * * * * * * * * * * * * * * * * *
  ------------------------------------------------------------------------*/

typedef struct vtoolbarRearranger		vtoolbarRearranger;
typedef struct vtoolbarRearrangerClass		vtoolbarRearrangerClass;
typedef struct vtoolbarRearrangeDrag		vtoolbarRearrangeDrag;
typedef struct vtoolbarRearrangeDragClass	vtoolbarRearrangeDragClass;
typedef struct vtoolbarRearrangeDropsite	vtoolbarRearrangeDropsite;
typedef struct vtoolbarRearrangeDropsiteClass	vtoolbarRearrangeDropsiteClass;
typedef struct vtoolbarRearrangeOccurrence	vtoolbarRearrangeOccurrence;
typedef struct vtoolbarRearrangeOccurrenceClass	
                vtoolbarRearrangeOccurrenceClass;

/*-------------------------------------------------------------------------
 * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * * * * * * * * * * * * *
  ------------------------------------------------------------------------*/

/* * * * * * * Toolbar Rearranger * * * * * * * * * * * * * * * * * * * * */

vtoolbarRearrangerClass *vtoolbarGetDefaultRearrangerClass(
    void
    );

vtoolbarRearrangerClass *vtoolbarGetRearrangerClass(
    vtoolbarRearranger		*rearranger
    );

vtoolbarRearranger *vtoolbarCreateRearrangerOfClass(
    vtoolbarRearrangerClass	*clas
    );

vtoolbarRearranger *vtoolbarCreateRearranger(
    void
    );

vtoolbarRearranger *vtoolbarCloneRearranger(
    vtoolbarRearranger		*rearranger
    );

void vtoolbarInitRearrangerOfClass(
    vtoolbarRearranger		*rearranger,
    vtoolbarRearrangerClass	*clas
    );

void vtoolbarInitRearranger(
    vtoolbarRearranger		*rearranger
    );

void vtoolbarDestroyRearranger(
    vtoolbarRearranger		*rearranger
    );

void vtoolbarCopyRearranger(
    vtoolbarRearranger		*rearranger,
    vtoolbarRearranger		*target
    );

void vtoolbarCopyInitRearranger(
    vtoolbarRearranger		*rearranger,
    vtoolbarRearranger		*target
    );

vtoolbarRearranger *vtoolbarLoadRearranger(
    vresource 			 res
    );

void vtoolbarLoadInitRearranger(
    vtoolbarRearranger		*rearranger,
    vresource 		 	 res
    );

void vtoolbarStoreRearranger(
    vtoolbarRearranger		*rearranger,
    vresource 		 	 res
    );

vobject *vtoolbarGetRearrangerObject(
    vtoolbarRearranger		*rearranger
    );

void vtoolbarRearrangerInsertItem(
    vtoolbarRearranger		*rearranger,
    vdialogItem			*dropTarget,
    vdialogItem			*dropItem,
    const vrect 		*dropRect
    );

void vtoolbarRearrangerMoveItem(
    vtoolbarRearranger		*rearranger,
    vdialogItem			*dropTarget,
    vdialogItem			*dropItem,
    const vrect 		*dropRect
    );

const vname *vtoolbarDetermineRearrangerBinding(
    vtoolbarRearranger		*rearranger,
    vkeyModifiers		 eventMods
    );

vbool vtoolbarProcessRearrangerRearrange(
    vtoolbarRearranger		*rearranger,
    vevent			*event
    );

vbool vtoolbarRearrangerTestRearrange(
    vtoolbarRearranger         	*rearranger,
    vtoolbarRearrangeDrag 	*drag,
    vevent			*event
    );

void vtoolbarRearrangerRearrange(
    vtoolbarRearranger         	*rearranger,
    vtoolbarRearrangeDrag 	*drag,
    vevent			*event
    );

void vtoolbarSetRearrangerPermissions(
    vtoolbarRearranger		*rearranger,
    int				 permissions
    );

int vtoolbarGetRearrangerPermissions(
    vtoolbarRearranger		*rearranger
    );

int vtoolbarHasRearrangerPermissions(
    vtoolbarRearranger		*rearranger,
    int				 permissionFlags
    );

void vtoolbarSetRearrangerOwner(
    vtoolbarRearranger		*rearranger,
    vdialogItem			*owner
    );

vdialogItem *vtoolbarGetRearrangerOwner(
    vtoolbarRearranger		*rearranger
    );

void vtoolbarSetRearrangerDropsite(
    vtoolbarRearranger		*rearranger,
    vtoolbarRearrangeDropsite	*dropsite
    );

vtoolbarRearrangeDropsite *vtoolbarGetRearrangerDropsite(
    vtoolbarRearranger		*rearranger
    );

vdragEngine *vtoolbarGetRearrangerDragEngine(
    vtoolbarRearranger		*rearranger
    );

vtoolbarRearrangeDrag *vtoolbarCreateRearrangerDrag(
    vtoolbarRearranger		*rearranger
    );

vtoolbarRearrangeDropsite *vtoolbarCreateRearrangerDropsite(
    vtoolbarRearranger		*rearranger
    );

vtoolbarSeparator *vtoolbarCreateRearrangerToolbarSeparator(
    vtoolbarRearranger		*rearranger
    );

vdragEngine *vtoolbarCreateRearrangerDragEngine(
    vtoolbarRearranger		*rearranger
    );

vdict *vtoolbarGetRearrangerBindingMap(
    vtoolbarRearranger		*rearranger
    );

vdict *vtoolbarDetermineRearrangerBindingMap(
    vtoolbarRearranger		*rearranger
    );

void vtoolbarSetRearrangerBindingMap(
    vtoolbarRearranger		*rearranger,
    vdict			*bindings
    );
    
void vtoolbarSetRearrangerBindingMapOwned(
    vtoolbarRearranger		*rearranger,
    vdict			*bindings
    );

/* * * * * * * Toolbar Rearrange Drag * * * * * * * * * * * * * * * * * * */

vtoolbarRearrangeDrag *vtoolbarCreateRearrangeDrag(
    void
    );

vtoolbarRearrangeDragClass *vtoolbarGetDefaultRearrangeDragClass(
    void
    );    

vtoolbarRearrangeDragClass *vtoolbarGetRearrangeDragClass(
    vtoolbarRearrangeDrag	*drag
    );    

void vtoolbarComputeRearrangeDragDropRect(
    vtoolbarRearrangeDrag	*drag,
    vevent			*dropEvent,
    vrect                       *rRect
    );
    
vdrag *vtoolbarGetRearrangeDragDrag(
    vtoolbarRearrangeDrag	*drag
    );

vdialogItem *vtoolbarGetRearrangeDragDragItem(
    vtoolbarRearrangeDrag	*drag
    );

vdialogItem *vtoolbarGetRearrangeDragSourceItem(
    vtoolbarRearrangeDrag	*drag
    );

vdialogItem *vtoolbarGetRearrangeDragTargetItem(
    vtoolbarRearrangeDrag	*drag
    );

vtoolbarRearranger *vtoolbarGetRearrangeDragSourceRearranger(
    vtoolbarRearrangeDrag	*drag
    );

vtoolbarRearranger *vtoolbarGetRearrangeDragTargetRearranger(
    vtoolbarRearrangeDrag	*drag
    );

int vtoolbarGetRearrangeDragType(
    vtoolbarRearrangeDrag	*drag
    );

void vtoolbarSetRearrangeDragDragItem(
    vtoolbarRearrangeDrag	*drag,
    vdialogItem			*item
    );

void vtoolbarSetRearrangeDragSourceRearranger(
    vtoolbarRearrangeDrag	*drag,
    vtoolbarRearranger		*rearranger
    );

void vtoolbarSetRearrangeDragTargetRearranger(
    vtoolbarRearrangeDrag	*drag,
    vtoolbarRearranger		*rearranger
    );

void vtoolbarSetRearrangeDragType(
    vtoolbarRearrangeDrag	*drag,
    int				 type
    );

/* * * * * * * Toolbar Rearrange Dropsite * * * * * * * * * * * * * * * * */

vtoolbarRearrangeDropsiteClass *vtoolbarGetDefaultRearrangeDropsiteClass(
    void
    );

vtoolbarRearrangeDropsiteClass *vtoolbarGetRearrangeDropsiteClass(
    vtoolbarRearrangeDropsite	*dropsite
    );

vtoolbarRearrangeDropsite *vtoolbarCreateRearrangeDropsite(
    void
    );

void vtoolbarDestroyRearrangeDropsite(
    vtoolbarRearrangeDropsite	*dropsite
    );

vtoolbarRearrangeDropsite *vtoolbarCloneRearrangeDropsite(
    vtoolbarRearrangeDropsite	*dropsite
    );

void vtoolbarCopyRearrangeDropsite(
    vtoolbarRearrangeDropsite	*dropsite,
    vtoolbarRearrangeDropsite	*target
    );

void vtoolbarCopyInitRearrangeDropsite(
    vtoolbarRearrangeDropsite	*dropsite,
    vtoolbarRearrangeDropsite	*target
    );

vdropsite *vtoolbarGetRearrangeDropsiteSite(
    vtoolbarRearrangeDropsite	*dropsite
    );

vtoolbarRearranger *vtoolbarGetRearrangeDropsiteRearranger(
    vtoolbarRearrangeDropsite	*dropsite
    );

void vtoolbarSetRearrangeDropsiteRearranger(
    vtoolbarRearrangeDropsite	*dropsite,
    vtoolbarRearranger		*rearranger
    );

vdialogItem *vtoolbarGetRearrangeDropsiteItem(
    vtoolbarRearrangeDropsite	*dropsite
    );

/* * * * * * * Toolbar Rearrange Occurrence * * * * * * * * * * * * * * * */

vtoolbarRearrangeOccurrenceClass *vtoolbarGetDefaultRearrangeOccurrenceClass(
    void
    );

vtoolbarRearrangeOccurrenceClass *vtoolbarGetRearrangeOccurrenceClass(
    vtoolbarRearrangeOccurrence	 *occurrence
    );

voccurrence *vtoolbarGetRearrangeOccurrenceOccurrence(
    vtoolbarRearrangeOccurrence	 *occurrence
    );

vinstance *vtoolbarGetRearrangeOccurrenceInstance(
    vtoolbarRearrangeOccurrence	 *occurrence
    );

vtoolbarRearrangeOccurrence *vtoolbarCreateRearrangeOccurrenceOfClass(
    vtoolbarRearrangeOccurrenceClass *clas
    );

vtoolbarRearrangeOccurrence *vtoolbarCreateRearrangeOccurrence(
    void
    );

void vtoolbarInitRearrangeOccurrenceOfClass(
    vtoolbarRearrangeOccurrence	 *occurrence,
    vtoolbarRearrangeOccurrenceClass *clas
    );

void vtoolbarInitRearrangeOccurrence(
    vtoolbarRearrangeOccurrence *occurrence
    );

void vtoolbarDestroyRearrangeOccurrence(
    vtoolbarRearrangeOccurrence *occurrence
    );

int vtoolbarGetRearrangeOccurrenceType(
    vtoolbarRearrangeOccurrence *occurrence
    );

vdialogItem *vtoolbarGetRearrangeOccurrenceDragItem(
    vtoolbarRearrangeOccurrence *occurrence
    );

vdialogItem *vtoolbarGetRearrangeOccurrenceSourceItem(
    vtoolbarRearrangeOccurrence *occurrence
    );

vdialogItem *vtoolbarGetRearrangeOccurrenceTargetItem(
    vtoolbarRearrangeOccurrence *occurrence
    );

vtoolbarRearranger *vtoolbarGetRearrangeOccurrenceSourceRearranger(
    vtoolbarRearrangeOccurrence *occurrence
    );

vtoolbarRearranger *vtoolbarGetRearrangeOccurrenceTargetRearranger(
    vtoolbarRearrangeOccurrence *occurrence
    );
    
const vrect *vtoolbarGetRearrangeOccurrenceDropRect(
    vtoolbarRearrangeOccurrence *occurrence
    );
    
void vtoolbarSetRearrangeOccurrenceType(
    vtoolbarRearrangeOccurrence	*occurrence,
    int				 type
    );

void vtoolbarSetRearrangeOccurrenceDragItem(
    vtoolbarRearrangeOccurrence	*occurrence,
    vdialogItem			*item
    );

void vtoolbarSetRearrangeOccurrenceSourceRearranger(
    vtoolbarRearrangeOccurrence	*occurrence,
    vtoolbarRearranger		*rearranger
    );

void vtoolbarSetRearrangeOccurrenceTargetRearranger(
    vtoolbarRearrangeOccurrence	*occurrence,
    vtoolbarRearranger		*rearranger
    );

void vtoolbarSetRearrangeOccurrenceDropRect(
    vtoolbarRearrangeOccurrence	*occurrence,
    const vrect			*rect
    );
    
/*-------------------------------------------------------------------------
 * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * * * * * * * * * * * * * *
  ------------------------------------------------------------------------*/

/* vtoolbarRearranger */

struct vtoolbarRearranger {
    vobject			 super;
    int				 permissions;
    int				 flags;
    vdialogItem			*owner;
    vtoolbarRearrangeOccurrence	*savedOccurrence;
    vtoolbarRearrangeDropsite	*dropsite;
    vdict			*bindings;
};

#define vtoolbarRearrangerCLASS(SUPER, REARRANGER)                           \
  vobjectCLASS(SUPER, REARRANGER);                                           \
  vclassVARIABLE(vtoolbarRearrangerBINDING_MAP, vdict *);                    \
  vclassMETHOD(vtoolbarRearrangerSET_PERMISSIONS,                            \
               (REARRANGER *arrange, int permissions));                      \
  vclassMETHOD_RET(vtoolbarRearrangerPROCESS_REARRANGE, vbool,               \
                   (REARRANGER *arrange, vevent *event));                    \
  vclassMETHOD_RET(vtoolbarRearrangerTEST_REARRANGE, vbool,                  \
                   (REARRANGER *arrange,                                     \
                    vtoolbarRearrangeDrag *drag, vevent *event));            \
  vclassMETHOD(vtoolbarRearrangerREARRANGE,                                  \
               (REARRANGER *arrange,                                         \
                vtoolbarRearrangeDrag *drag, vevent *event));                \
  vclassMETHOD_RET(vtoolbarRearrangerCREATE_REARRANGE_DRAG,                  \
                   vtoolbarRearrangeDrag*, (REARRANGER *arrange));           \
  vclassMETHOD_RET(vtoolbarRearrangerCREATE_REARRANGE_DROPSITE,              \
                   vtoolbarRearrangeDropsite*, (REARRANGER *arrange));       \
  vclassMETHOD_RET(vtoolbarRearrangerCREATE_REARRANGE_DRAG_ENGINE,           \
                   vdragEngine*, (REARRANGER *arrange));                     \
  vclassMETHOD(vtoolbarRearrangerSET_OWNER, 		                     \
               (REARRANGER *arrange, vdialogItem *owner));                   \
  vclassMETHOD(vtoolbarRearrangerSET_DROPSITE, 		                     \
               (REARRANGER *arrange, vtoolbarRearrangeDropsite *dropsite));  \
  vclassMETHOD_RET(vtoolbarRearrangerCREATE_TOOLBAR_SEPARATOR,               \
                   vtoolbarSeparator*, (REARRANGER *arrange));               \
  vclassMETHOD(vtoolbarRearrangerINSERT_ITEM,                                \
               (REARRANGER *arrange, vdialogItem *dropTarget,                \
                vdialogItem *dropItem, const vrect *dropRect));              \
  vclassMETHOD(vtoolbarRearrangerMOVE_ITEM,                                  \
               (REARRANGER *arrange, vdialogItem *dropTarget,                \
                vdialogItem *dropItem, const vrect *dropRect));              \
  vclassMETHOD_RET(vtoolbarRearrangerDETERMINE_BINDING, const vname *,       \
               (REARRANGER *arrange, vkeyModifiers evMods))

struct vtoolbarRearrangerClass {
    vtoolbarRearrangerCLASS(vtoolbarRearrangerClass, vtoolbarRearranger);
};


/* vtoolbarRearrangeDrag */

struct vtoolbarRearrangeDrag {
    vdrag        drag;
    vdialogItem *dragItem;
    int		 type;
    vtoolbarRearranger *source;
    vtoolbarRearranger *target;
    vkeyModifiers lastMods;
};

#define vtoolbarRearrangeDragCLASS(SUPER, DRAG)                              \
    vdragCLASS(SUPER, DRAG);                                                 \
    vclassMETHOD(vtoolbarRearrangeDragSET_TYPE,                              \
                 (DRAG *drag, int type));                                    \
    vclassMETHOD(vtoolbarRearrangeDragSET_DRAG_ITEM,                         \
                 (DRAG *drag, vdialogItem *dragItem));                       \
    vclassMETHOD(vtoolbarRearrangeDragSET_SOURCE_REARRANGER,                 \
                 (DRAG *drag, vtoolbarRearranger *source));                  \
    vclassMETHOD(vtoolbarRearrangeDragSET_TARGET_REARRANGER,                 \
                 (DRAG *drag, vtoolbarRearranger *target))
    

struct vtoolbarRearrangeDragClass {
    vtoolbarRearrangeDragCLASS(vtoolbarRearrangeDragClass, 
                               vtoolbarRearrangeDrag);
};


/* vtoolbarRearrangeDropsite */

struct vtoolbarRearrangeDropsite {
    vdropsite		 dropsite;
    vtoolbarRearranger	*rearranger;
};

#define vtoolbarRearrangeDropsiteCLASS(SUPER, DROP, NOTIFY)                  \
    vdropsiteCLASS(SUPER, DROP, NOTIFY);                                     \
    vclassMETHOD(vtoolbarRearrangeDropsiteSET_REARRANGER,                    \
                 (DROP *dropsite, vtoolbarRearranger *rearranger))


struct vtoolbarRearrangeDropsiteClass {
    vtoolbarRearrangeDropsiteCLASS(vtoolbarRearrangeDropsiteClass,
                                   vtoolbarRearrangeDropsite,
                                   vdropsiteNoteProc);
};


/* vtoolbarRearrangeOccurrence */

struct vtoolbarRearrangeOccurrence {
    voccurrence		 super;

    int			 type;
    vdialogItem	        *dragItem;
    vtoolbarRearranger  *source;
    vtoolbarRearranger	*target;
    vrect        	 dropRect;
};

#define vtoolbarRearrangeOCCURRENCE_CLASS(CLASS, OCCURRENCE)		     \
    voccurrenceCLASS(CLASS, OCCURRENCE)

struct vtoolbarRearrangeOccurrenceClass
{
  vtoolbarRearrangeOCCURRENCE_CLASS(
      vtoolbarRearrangeOccurrenceClass, vtoolbarRearrangeOccurrence);
};

/*-------------------------------------------------------------------------
 * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * * * * * * * * *
  ------------------------------------------------------------------------*/

/* Toolbar Rearranger */
#define vtoolbarGetRearrangerObject(r) vportBASE_OBJECT(r, super)
#define vtoolbarGetRearrangerClass(r) \
  ((vtoolbarRearrangerClass*)vobjectGetClass(vtoolbarGetRearrangerObject(r)))
#define vtoolbarCreateRearrangerOfClass(c) \
  ((vtoolbarRearranger*)vobjectCreateOfClass((vobjectClass*)(c)))
#define vtoolbarCreateRearranger() \
  vtoolbarCreateRearrangerOfClass(vtoolbarGetDefaultRearrangerClass())
#define vtoolbarCloneRearranger(r) \
  ((vtoolbarRearranger*)vobjectClone(vtoolbarGetRearrangerObject(r)))
#define vtoolbarInitRearrangerOfClass(r, c) \
  vobjectInitOfClass(vtoolbarGetRearrangerObject(r), (vobjectClass*)(c))
#define vtoolbarInitRearranger(r) \
  vtoolbarInitRearrangerOfClass(r, vtoolbarGetDefaultRearrangerClass())

#define vtoolbarDestroyRearranger(r) \
  vobjectDestroy(vtoolbarGetRearrangerObject(r))
#define vtoolbarCopyRearranger(s, t) \
  vobjectCopy(vtoolbarGetRearrangerObject(s), vtoolbarGetRearrangerObject(t))
#define vtoolbarCopyInitRearranger(s, t) \
  vobjectCopyInit(vtoolbarGetRearrangerObject(s),  \
                  vtoolbarGetRearrangerObject(t))
#define vtoolbarLoadRearranger(r) ((vtoolbarRearranger*)vobjectLoad(r))
#define vtoolbarLoadInitRearranger(r, s) \
  ((vtoolbarRearranger*)vobjectLoadInit(vtoolbarGetRearrangerObject(r), s))
#define vtoolbarStoreRearranger(r, s)  \
  vobjectStore(vtoolbarGetRearrangerObject(r), s)

#define vtoolbarProcessRearrangerRearrange(r, e) \
  vclassSend(vtoolbarGetRearrangerClass(r), \
             vtoolbarRearrangerPROCESS_REARRANGE, (r, e))
#define vtoolbarRearrangerTestRearrange(r, d, e) \
  vclassSend(vtoolbarGetRearrangerClass(r), \
             vtoolbarRearrangerTEST_REARRANGE, (r, d, e))
#define vtoolbarRearrangerRearrange(r, d, e) \
  vclassSend(vtoolbarGetRearrangerClass(r), \
             vtoolbarRearrangerREARRANGE, (r, d, e))
#define vtoolbarSetRearrangerPermissions(r, p) \
  vclassSend(vtoolbarGetRearrangerClass(r), \
             vtoolbarRearrangerSET_PERMISSIONS, (r, p))
#define vtoolbarSetRearrangerOwner(r, o) \
  vclassSend(vtoolbarGetRearrangerClass(r), \
             vtoolbarRearrangerSET_OWNER, (r, o))
#define vtoolbarSetRearrangerDropsite(r, d) \
  vclassSend(vtoolbarGetRearrangerClass(r), \
             vtoolbarRearrangerSET_DROPSITE, (r, d))
#define vtoolbarCreateRearrangerDrag(r) \
  vclassSend(vtoolbarGetRearrangerClass(r), \
             vtoolbarRearrangerCREATE_REARRANGE_DRAG, (r))
#define vtoolbarCreateRearrangerDropsite(r) \
  vclassSend(vtoolbarGetRearrangerClass(r), \
             vtoolbarRearrangerCREATE_REARRANGE_DROPSITE, (r))
#define vtoolbarCreateRearrangerDragEngine(r) \
  vclassSend(vtoolbarGetRearrangerClass(r), \
             vtoolbarRearrangerCREATE_REARRANGE_DRAG_ENGINE, (r))
#define vtoolbarRearrangerInsertItem(r, t, i, d) \
  vclassSend(vtoolbarGetRearrangerClass(r), \
             vtoolbarRearrangerINSERT_ITEM, (r, t, i, d))
#define vtoolbarRearrangerMoveItem(r, t, i, d) \
  vclassSend(vtoolbarGetRearrangerClass(r), \
             vtoolbarRearrangerMOVE_ITEM, (r, t, i, d))
#define vtoolbarDetermineRearrangerBinding(r, m) \
  vclassSend(vtoolbarGetRearrangerClass(r), \
             vtoolbarRearrangerDETERMINE_BINDING, (r, m))
#define vtoolbarCreateRearrangerToolbarSeparator(r) \
  vclassSend(vtoolbarGetRearrangerClass(r), \
             vtoolbarRearrangerCREATE_TOOLBAR_SEPARATOR, (r))
#define vtoolbarGetRearrangerPermissions(r)    ((r)->permissions)
#define vtoolbarHasRearrangerPermissions(r, p) (((r)->permissions & p) == p)
#define vtoolbarGetRearrangerOwner(r)          ((r)->owner)
#define vtoolbarGetRearrangerDropsite(r)       ((r)->dropsite)

/* Rearrange Drag */

#define vtoolbarCreateRearrangeDrag() \
  ((vtoolbarRearrangeDrag*)vdragCreateOfClass( \
      (vdragClass*)vtoolbarGetDefaultRearrangeDragClass())) 
#define vtoolbarGetRearrangeDragClass(d) \
  ((vtoolbarRearrangeDragClass*)vdragGetClass(vtoolbarGetRearrangeDragDrag(d)))
#define vtoolbarGetRearrangeDragDrag(d)		   vportBASE_OBJECT(d, drag)
#define vtoolbarGetRearrangeDragDragItem(d)	   ((d)->dragItem)
#define vtoolbarGetRearrangeDragSourceRearranger(d) ((d)->source)
#define vtoolbarGetRearrangeDragTargetRearranger(d) ((d)->target)
#define vtoolbarGetRearrangeDragSourceItem(d)	    \
  ((d)->source==NULL?NULL:(d)->source->owner)
#define vtoolbarGetRearrangeDragTargetItem(d)	    \
  ((d)->target==NULL?NULL:(d)->target->owner)
#define vtoolbarGetRearrangeDragType(d)	   	   ((d)->type)

#define vtoolbarSetRearrangeDragDragItem(d,i)	   \
    vclassSend(vtoolbarGetRearrangeDragClass(d), \
               vtoolbarRearrangeDragSET_DRAG_ITEM, (d, i))
#define vtoolbarSetRearrangeDragSourceRearranger(d,i) \
    vclassSend(vtoolbarGetRearrangeDragClass(d), \
               vtoolbarRearrangeDragSET_SOURCE_REARRANGER, (d, i))
#define vtoolbarSetRearrangeDragTargetRearranger(d,i) \
    vclassSend(vtoolbarGetRearrangeDragClass(d), \
               vtoolbarRearrangeDragSET_TARGET_REARRANGER, (d, i))
#define vtoolbarSetRearrangeDragType(d,a)	  \
    vclassSend(vtoolbarGetRearrangeDragClass(d), \
               vtoolbarRearrangeDragSET_TYPE, (d, a))

/* Rearrange Dropsite */

#define vtoolbarGetRearrangeDropsiteSite(d)	 vportBASE_OBJECT(d, dropsite)
#define vtoolbarGetRearrangeDropsiteClass(d) \
  ((vtoolbarRearrangeDropsiteClass*)vdropsiteGetClass  \
   (vtoolbarGetRearrangeDropsiteSite(d)))
#define vtoolbarCreateRearrangeDropsite()   \
  ((vtoolbarRearrangeDropsite*)vdropsiteCreateOfClass( \
      (vdropsiteClass*)vtoolbarGetDefaultRearrangeDropsiteClass()))
#define vtoolbarDestroyRearrangeDropsite(d) \
  vdropsiteDestroy(vtoolbarGetRearrangeDropsiteSite(d))
#define vtoolbarCloneRearrangeDropsite(d) \
  ((vtoolbarRearrangeDropsite*) \
   vdropsiteClone(vtoolbarGetRearrangeDropsiteSite(d)))
#define vtoolbarCopyRearrangeDropsite(s, t) \
  vdropsiteCopy(vtoolbarGetRearrangeDropsiteSite(s), \
                vtoolbarGetRearrangeDropsiteSite(t))
#define vtoolbarCopyInitRearrangeDropsite(s, t) \
  vdropsiteCopyInit(vtoolbarGetRearrangeDropsiteSite(s), \
                    vtoolbarGetRearrangeDropsiteSite(t))
#define vtoolbarGetRearrangeDropsiteRearranger(d)      ((d)->rearranger)
#define vtoolbarGetRearrangeDropsiteItem(d)            ((d)->rearranger->owner)
#define vtoolbarSetRearrangeDropsiteRearranger(d, i)   \
  vclassSend(vtoolbarGetRearrangeDropsiteClass(d), \
             vtoolbarRearrangeDropsiteSET_REARRANGER, (d, i))


/* Toolbar occurrences */

#define vtoolbarGetRearrangeOccurrenceOccurrence(o) vportBASE_OBJECT(o, super)
#define vtoolbarGetRearrangeOccurrenceInstance(o) \
    voccurrenceGetInstance(vtoolbarGetRearrangeOccurrenceOccurrence(o))
#define vtoolbarGetRearrangeOccurrenceClass(o) \
    ((vtoolbarOccurrenceClass *) \
     voccurrenceGetClass(vtoolbarGetRearrangeOccurrenceOccurrence(o)))

#define vtoolbarCreateRearrangeOccurrenceOfClass(c)   	\
    ((vtoolbarRearrangeOccurrence *) \
     voccurrenceCreateOfClass((voccurrenceClass *)(c)))
#define vtoolbarCreateRearrangeOccurrence()		\
    (vtoolbarCreateRearrangeOccurrenceOfClass( \
     vtoolbarGetDefaultRearrangeOccurrenceClass()))
#define vtoolbarInitRearrangeOccurrenceOfClass(o, c)  	\
    voccurrenceInitOfClass(vtoolbarGetRearrangeOccurrenceOccurrence(o), \
			   (voccurrenceClass*)(c))
#define vtoolbarInitRearrangeOccurrence(o)	     	\
    vtoolbarInitRearrangeOccurrenceOfClass( \
        o, vtoolbarGetDefaultRearrangeOccurrenceClass())
#define vtoolbarDestroyRearrangeOccurrence(o)	\
    voccurrenceDestroy(vtoolbarGetRearrangeOccurrenceOccurrence(o))

#define vtoolbarGetRearrangeOccurrenceType(o) \
    ((o)->type)
#define vtoolbarGetRearrangeOccurrenceSourceItem(o) \
    ((o)->source==NULL?NULL:(o)->source->owner)
#define vtoolbarGetRearrangeOccurrenceTargetItem(o) \
    ((o)->target==NULL?NULL:(o)->target->owner)
#define vtoolbarGetRearrangeOccurrenceSourceRearranger(o) \
    ((o)->source)
#define vtoolbarGetRearrangeOccurrenceTargetRearranger(o) \
    ((o)->target)
#define vtoolbarGetRearrangeOccurrenceDragItem(o) \
    ((o)->dragItem)
#define vtoolbarGetRearrangeOccurrenceDropRect(o) \
    ((const vrect*)&((o)->dropRect))

#define vtoolbarSetRearrangeOccurrenceType(o, t) \
    ((o)->type = (t))
#define vtoolbarSetRearrangeOccurrenceDragItem(o, d) \
    ((o)->dragItem = (d))
#define vtoolbarSetRearrangeOccurrenceSourceRearranger(o, s) \
    ((o)->source = (s))
#define vtoolbarSetRearrangeOccurrenceTargetRearranger(o, t) \
    ((o)->target = (t))
#define vtoolbarSetRearrangeOccurrenceDropRect(o, d) \
    ((o)->dropRect = *(d))


vportEND_CPLUSPLUS_EXTERN_C

#endif /* vtoolbarRearrangerINCLUDED */


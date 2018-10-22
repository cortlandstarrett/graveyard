/* $Id: vdrawrectset.h,v 1.6 1997/09/11 22:51:29 robert Exp $ */

/*
 * vdrawrectset.h
 *
 * C Interface file for the Rectangle Set object
 *
 * (c) Copyright Visix Software, Inc.
 * All rights reserved
 */

#ifndef vdrawrectsetINCLUDED
#define vdrawrectsetINCLUDED

#ifndef vportINCLUDED
#include <vport.h>
#endif

#ifndef vdrawINCLUDED
#include vdrawHEADER
#endif

#ifndef vloadableINCLUDED
#include vloadableHEADER
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * PUBLIC TYPE DECLARATIONS
 */

typedef struct vdrawrectset vdrawrectset;
typedef struct vdrawrectsetClass vdrawrectsetClass;

/*
 * PUBLIC FUNCTION DECLARATION
 */

void vdrawrectsetStartup(
    void
    );

vdrawrectsetClass *vdrawrectsetGetDefaultClass(
    void
    );

vdrawrectsetClass *vdrawrectsetGetClass(
    vdrawrectset *rectset
    );

vdrawrectset *vdrawrectsetCreate(
    void
    );

vdrawrectset *vdrawrectsetCreateWithRects(
    const vrect			 *rects,
    int				  count
    );

vdrawrectset *vdrawrectsetCreateOfClass(
    vdrawrectsetClass *clas
    );

void vdrawrectsetInit(
    vdrawrectset                  *rectset
    );

void vdrawrectsetInitOfClass(
    vdrawrectset                  *rectset,
    vdrawrectsetClass             *clas
    );

vdrawrectset *vdrawrectsetClone(
    const vdrawrectset            *rectset
    );

void vdrawrectsetCopy(
    const vdrawrectset            *from,
    vdrawrectset                  *to
    );

void vdrawrectsetCopyInit(
    const vdrawrectset            *from,
    vdrawrectset                  *to
    );

void vdrawrectsetDestroy(
    vdrawrectset                  *rectset
    );

vdrawrectset *vdrawrectsetLoad(
    vresource                       resource
    );

void vdrawrectsetLoadInit(
    vdrawrectset                  *rectset,
    vresource                       resource
    );

void vdrawrectsetStore(
    const vdrawrectset            *rectset,
    vresource                       resource
    );

vloadable *vdrawrectsetGetLoadable(
    const vdrawrectset		   *rectset
    );
    
vinstance *vdrawrectsetGetInstance(
    const vdrawrectset		   *rectset
    );

size_t vdrawrectsetGetSize(
    const vdrawrectset            *rectset
    );

size_t vdrawrectsetGetRectCount(
    const vdrawrectset            *rectset
    );

void vdrawrectsetSetMinSize(
    vdrawrectset                  *rectset,
    size_t                         size
    );

vrect *vdrawrectsetGetRect(
    vdrawrectset                  *rectset,
    size_t                         index
    );

void vdrawrectsetSetRect(
    vdrawrectset                  *rectset,
    size_t                         index,
    vrect                         *rect
    );

void vdrawrectsetInsertRect(
    vdrawrectset                  *rectset,
    size_t                         index,
    vrect                         *rect
    );

void vdrawrectsetAppendRect(
    vdrawrectset                  *rectset,
    vrect                         *rect
    );

void vdrawrectsetDeleteRect(
    vdrawrectset                  *rectset,
    size_t                         index
    );

vbool vdrawrectsetContainsPoint(
    vdrawrectset                  *rectset,
    int                            x,
    int                            y
    );

vbool vdrawrectsetRectIntersects(
    vdrawrectset                  *rectset,
    vrect                         *rect
    );

void vdrawrectsetDetermineBounds(
    vdrawrectset                  *rectset,
    vrect                         *rrect
    );

vdrawrectset *vdrawrectsetIntersect(
    vdrawrectset                  *rectset1,
    vdrawrectset                  *rectset2
    );

vdrawrectset *vdrawrectsetUnion(
    vdrawrectset                  *rectset1,
    vdrawrectset                  *rectset2
    );

vdrawrectset *vdrawrectsetDifference(
    vdrawrectset                  *rectset1,
    vdrawrectset                  *rectset2
    );

/*
 * CLASS DECLARATION
 */

#define vdrawrectsetCLASS(CLASS, RECTSET)                                     \
  vloadableCLASS(CLASS, RECTSET)

/*
 * PRIVATE TYPE DECLARATION
 */

struct vdrawrectset {     
  vloadable super;
  vrect *rects;
  vrect *rectStop, *rectMax;
};

struct vdrawrectsetClass {
  vdrawrectsetCLASS(vdrawrectsetClass, vdrawrectset);
};

/*
 * FUNCTIONS IMPLEMENTED AS MACROS
 */

#define vdrawrectsetGetLoadable(r)  vportBASE_OBJECT((r),super)
#define vdrawrectsetGetInstance(r)                                            \
  vloadableGetInstance(vdrawrectsetGetLoadable((r)))

#define vdrawrectsetGetClass(r)                                               \
  (vdrawrectsetClass *)vloadableGetClass(vdrawrectsetGetLoadable((r)))

#define vdrawrectsetCreateOfClass(c)                                          \
  (vdrawrectset *)vloadableCreateOfClass((vloadableClass *)(c))

#define vdrawrectsetCreate()                                                  \
  vdrawrectsetCreateOfClass(vdrawrectsetGetDefaultClass())

#define vdrawrectsetInitOfClass(r,c)                                          \
  vloadableInitOfClass(vdrawrectsetGetLoadable(r),(vloadableClass *)(c))

#define vdrawrectsetInit(r)                                                   \
  vdrawrectsetInitOfClass((r),vdrawrectsetGetDefaultClass())

#define vdrawrectsetClone(r)                                                  \
  (vdrawrectset *)vloadableCloneOfSubclass(vdrawrectsetGetLoadable((r)),      \
         		   (vloadableClass *)vdrawrectsetGetDefaultClass())

#define vdrawrectsetCopy(r,t)                                                 \
  vloadableCopy(vdrawrectsetGetLoadable((r)), vdrawrectsetGetLoadable((t)))
 
#define vdrawrectsetCopyInit(r,t)                                             \
  vloadableCopyInit(vdrawrectsetGetLoadable((r)), vdrawrectsetGetLoadable((t)))

#define vdrawrectsetDestroy(r)                                                \
    vloadableDestroy(vdrawrectsetGetLoadable(r))

#define vdrawrectsetLoad(r)                                                   \
  (vdrawrectset *)vloadableLoadOfSubclass((r),                                \
                              (vloadableClass *)vdrawrectsetGetDefaultClass())

#define vdrawrectsetLoadInit(s,r)                                             \
  vloadableLoadInitOfSubclass(vdrawrectsetGetLoadable(s), (r), \
			(vloadableClass*) vdrawrectsetGetDefaultClass())  

#define vdrawrectsetStore(s,r)                                                \
  vloadableStore(vdrawrectsetGetLoadable(s),(r))

#define vdrawrectsetGetSize(r) ((r)->rectMax - (r)->rects)

#define vdrawrectsetGetRectCount(r) ((r)->rectStop - (r)->rects)

#define vdrawrectsetContainsPoint(r,x,y)                                      \
  vrectSetContainsPoint((r)->rects, vdrawrectsetGetRectCount((r)), (x), (y))

#define vdrawrectsetRectIntersects(s,r)                                       \
  vrectIntersectsSet((r),(s)->rects, vdrawrectsetGetRectCount((s)))

#define vdrawrectsetDetermineBounds(s,r)                                      \
  vrectUnionSet((s)->rects, vdrawrectsetGetRectCount((s)), (r))

vportEND_CPLUSPLUS_EXTERN_C

#endif

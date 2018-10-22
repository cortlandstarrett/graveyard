/* $Id: vdrawcontext.h,v 1.22 1997/10/15 20:34:42 gregt Exp $ */

/*
 * vdrawcontext.h
 *
 * C Interface file for the Drawing Context object
 *
 * (c) Copyright Visix Software, Inc.
 * All rights reserved
 */

#ifndef vdrawcontextINCLUDED
#define vdrawcontextINCLUDED

#ifndef vportINCLUDED
#include <vport.h>
#endif

#ifndef vdrawINCLUDED
#include vdrawHEADER
#endif

#ifndef vdrawrectsetINCLUDED
#include vdrawrectsetHEADER
#endif

#ifndef vdrawpenINCLUDED
#include vdrawpenHEADER
#endif

#ifndef vdrawpathINCLUDED
#include vdrawpathHEADER
#endif

#ifndef vloadableINCLUDED
#include vloadableHEADER
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * PUBLIC TYPE DECLARATIONS
 */

typedef struct vdrawcontext vdrawcontext;
typedef struct vdrawcontextClass vdrawcontextClass;

/*
 * PUBLIC CONSTANT DECLARATIONS
 */

/*
 * PUBLIC FUNCTION DECLARATIONS
 */

void vdrawcontextStartup(
    void
    );

/*
 * Drawing Context Functions
 */

vdrawcontextClass *vdrawcontextGetDefaultClass(
    void
    );

vdrawcontextClass *vdrawcontextGetClass(
    vdrawcontext *context
    );

vloadable *vdrawcontextGetLoadable(
    vdrawcontext *context
    );

vinstance *vdrawcontextGetInstance(
    vdrawcontext *context
    );

vdrawcontext *vdrawcontextCreate(
    void
    );

vdrawcontext *vdrawcontextCreateOfClass(
    vdrawcontextClass *clas
    );

vdrawcontext *vdrawCreateImageDrawcontext(
    vimage *image
    );

vdrawcontext *vdrawCreateMaskDrawcontext(
    vimage *mask
    );

vdrawcontext *vdrawcontextClone(
    vdrawcontext *context
    );

void vdrawcontextInit(
    vdrawcontext *context
    );

void vdrawcontextInitOfClass(
    vdrawcontext *context,
    vdrawcontextClass *clas
    );

void vdrawcontextDestroy(
    vdrawcontext *context
    );

void vdrawcontextDestroyLater(
    vdrawcontext *context
    );

void vdrawcontextCopy(
    vdrawcontext *context,
    vdrawcontext *target
    );

void vdrawcontextCopyInit(
    vdrawcontext *context,
    vdrawcontext *target
    );

void vdrawcontextUtilize(
    vdrawcontext *context
    );

void vdrawcontextDispose(
    vdrawcontext *context
    );

void vdrawcontextClipRectangles(
    vdrawcontext *context,
    const vrect *rects,
    size_t count
    );

void vdrawcontextClipPath(
    vdrawcontext *context,
    vdrawpath *path
    );

void vdrawcontextClipPathEvenOdd(
    vdrawcontext *context,
    vdrawpath *path
    );

void vdrawcontextTransform(
    vdrawcontext *context,
    const vmatrix *mtx
    );

vdrawpath *vdrawcontextCloneClipPath(
    vdrawcontext *context
    );

vdrawpath *vdrawcontextCloneViewClipPath(
    vdrawcontext *context
    );

const vrect *vdrawcontextGetClipBounds(
    vdrawcontext *context,
    size_t *count
    );

const vrectFloat *vdrawcontextGetClipBoundsFloat(
    vdrawcontext *context,
    size_t *count
    );

const vrect *vdrawcontextGetViewClipBounds(
    vdrawcontext *context,
    size_t *count
    );

const vrectFloat *vdrawcontextGetViewClipBoundsFloat(
    vdrawcontext *context,
    size_t *count
    );

void vdrawcontextDeltaTransformDimension(
    vdrawcontext *context,
    double x,
    double y,
    double *xo,
    double *yo
    );

void vdrawcontextDrawArcs(
    vdrawcontext *context,
    const vrect *rects,
    size_t size,
    double startAngle,
    double endAngle
    );

void vdrawcontextDrawArcsInside(
    vdrawcontext *context,
    const vrect *rects,
    size_t size,
    double startAngle,
    double endAngle
    );

void vdrawcontextDrawEllipses(
    vdrawcontext *context,
    const vrect *rects,
    size_t size
    );
    
void vdrawcontextDrawEllipsesInside(
    vdrawcontext *context,
    const vrect *rects,
    size_t size
    );
    
void vdrawcontextDrawHilitedRectangles(
    vdrawcontext *context,
    const vrect *rects,
    size_t count,
    vcolor *topShadow,
    vcolor *bottomShadow
    );

void vdrawcontextDrawHilitedRectanglesInside(
    vdrawcontext *context,
    const vrect *rects,
    size_t count,
    vcolor *topShadow,
    vcolor *bottomShadow
    );

void vdrawcontextDrawImage(
    vdrawcontext *context,
    vimage *image,
    vmatrix *mtx
    );

void vdrawcontextDrawImagePoint(
    vdrawcontext *context,
    vimage *image,
    double x,
    double y
    );

void vdrawcontextDrawImageRectangle(
    vdrawcontext *context,
    vimage *image,
    const vrect *rect
    );

void vdrawcontextDrawImageTiled(
    vdrawcontext *context,
    vimage *image,
    const vrect *tileRect,
    const vrect *destRect
    );

void vdrawcontextDrawKeyStroke(
    vdrawcontext *context,
    vkeyStroke key
    );

void vdrawcontextDrawLineTo(
    vdrawcontext *context,
    double x,
    double y
    );

void vdrawcontextDrawLineToRelative(
    vdrawcontext *context,
    double x,
    double y
    );

void vdrawcontextDrawMask(
    vdrawcontext *context,
    vimage *mask,
    vmatrix *mtx
    );

void vdrawcontextDrawMaskPoint(
    vdrawcontext *context,
    vimage *mask,
    double x,
    double y
    );

void vdrawcontextDrawMaskRectangle(
    vdrawcontext *context,
    vimage *mask,
    const vrect *rect
    );

void vdrawcontextDrawMaskTiled(
    vdrawcontext *context,
    vimage *mask,
    const vrect *tileRect,
    const vrect *destRect
    );

void vdrawcontextDrawPath(
    vdrawcontext *context,
    vdrawpath *path
    );

void vdrawcontextDrawRectangles(
    vdrawcontext *context,
    const vrect *rect,
    size_t count
    );

void vdrawcontextDrawRectanglesFloat(
    vdrawcontext *context,
    const vrectFloat *rect,
    size_t count
    );

void vdrawcontextDrawRectanglesInside(
    vdrawcontext *context,
    const vrect *rect,
    size_t count
    );

void vdrawcontextDrawRoundRectangles(
    vdrawcontext *context,
    const vrect *rect,
    size_t count,
    double radius
    );

void vdrawcontextDrawRoundRectanglesInside(
    vdrawcontext *context,
    const vrect *rect,
    size_t count,
    double radius
    );

void vdrawcontextDrawString(
    vdrawcontext *context,
    const vchar *string,
    const vrect *rect
);

void vdrawcontextDrawStringScribed(
    vdrawcontext *context,
    vscribe *scribe,
    const vrect *rect
);

void vdrawcontextDrawStringCenter(
    vdrawcontext *context,
    const vchar *string,
    const vrect *rect
    );

void vdrawcontextDrawStringCenterScribed(
    vdrawcontext *context,
    vscribe *scribe,
    const vrect *rect
    );

void vdrawcontextDrawStringCenterHorizontally(
    vdrawcontext *context,
    const vchar *string,
    const vrect *rect
    );

void vdrawcontextDrawStringCenterHorizontallyScribed(
    vdrawcontext *context,
    vscribe *scribe,
    const vrect *rect
    );

void vdrawcontextDrawStringCenterVertically(
    vdrawcontext *context,
    const vchar *string,
    const vrect *rect
    );

void vdrawcontextDrawStringCenterVerticallyScribed(
    vdrawcontext *context,
    vscribe *scribe,
    const vrect *rect
    );

void vdrawcontextDrawStringUnderlined(
    vdrawcontext *context,
    const vchar *string
);

void vdrawcontextDrawStringUnderlinedScribed(
    vdrawcontext *context,
    vscribe *scribe
);

void vdrawcontextDrawStringUnderlineMnemonic(
    vdrawcontext                   *context,
    const vchar                    *title,
    int                             mnemonic,
    const vrect                    *rect,
    unsigned int                    flags
    );

void vdrawcontextDrawStringUnderlineMnemonicScribed(
    vdrawcontext                   *context,
    vscribe                        *scribe,
    int                             mnemonic,
    const vrect                    *rect,
    unsigned int                    flags
    );

void vdrawcontextDrawHilitedBox(
    vdrawcontext                   *context,
    const vrect                    *rect,
    vcolor                         *interior,
    vcolor                         *top,
    vcolor                         *bottom
    );

void vdrawcontextDrawHilitedDiamond(
    vdrawcontext                   *context,
    const vrect                    *rect,
    vcolor                         *interior,
    vcolor                         *top,
    vcolor                         *bottom
    );

void vdrawcontextDrawHorizontalHilitedArrow(
    vdrawcontext                   *context,
    int                             x,
    int                             y,
    int                             length,
    int                             half,
    vcolor                         *interior,
    vcolor                         *straight,
    vcolor                         *bent
    );

void vdrawcontextDrawVerticalHilitedArrow(
    vdrawcontext                   *context,
    int                             x,
    int                             y,
    int                             length,
    int                             half,
    vcolor                         *interior,
    vcolor                         *straight,
    vcolor                         *bent
    );

void vdrawcontextFillArcChords(
    vdrawcontext *context,
    const vrect *rects,
    size_t count,
    double startAngle,
    double endAngle
    );

void vdrawcontextFillArcSectors(
    vdrawcontext *context,
    const vrect *rects,
    size_t count,
    double startAngle,
    double endAngle
    );

void vdrawcontextFillEllipses(
    vdrawcontext *context,
    const vrect *rects,
    size_t count
    );

void vdrawcontextFillPath(
    vdrawcontext *context,
    vdrawpath *path
    );

void vdrawcontextFillPathEvenOdd(
    vdrawcontext *context,
    vdrawpath *path
    );

void vdrawcontextFillRectangles(
    vdrawcontext *context,
    const vrect *rects,
    size_t count
    );

void vdrawcontextFillRectanglesFloat(
    vdrawcontext *context,
    const vrectFloat *rects,
    size_t count
    );

void vdrawcontextFillHilitedRectangles(
    vdrawcontext *context,
    const vrect *rects,
    size_t count,
    vcolor *interior,
    vcolor *topShadow,
    vcolor *bottomShadow
    );

void vdrawcontextFillHilitedRectanglesInside(
    vdrawcontext *context,
    const vrect *rects,
    size_t count,
    vcolor *interior,
    vcolor *topShadow,
    vcolor *bottomShadow
    );

void vdrawcontextFillRoundRectangles(
    vdrawcontext *context,
    const vrect *rects,
    size_t count,
    double radius
    );

void vdrawcontextGetCurrentPoint(
    vdrawcontext *context,
    double *x,
    double *y
    );

const vmatrix *vdrawcontextGetDefaultMatrix(
    vdrawcontext *context
    );

int vdrawcontextGetStrokeAdjustmentRule(
    vdrawcontext *context
    );

vmatrix *vdrawcontextGetMatrix(
    vdrawcontext *context
    );

vdrawpen *vdrawcontextGetPen(
    vdrawcontext *context
    );

vbool vdrawcontextIntersectsClip(
    vdrawcontext *context,
    const vrect *rect
    );

vbool vdrawcontextIntersectsViewClip(
    vdrawcontext *context,
    const vrect *rect
    );

void vdrawcontextInverseTransformPoint(
    vdrawcontext *context,
    double x,
    double y,
    double *xout,
    double *yout
    );

void vdrawcontextInverseDeltaTransformDimension(
    vdrawcontext *context,
    double x,
    double y,
    double *xout,
    double *yout
    );

void vdrawcontextRotate(
    vdrawcontext *context,
    double angle
    );

void vdrawcontextScale(
    vdrawcontext *context,
    double x,
    double y
    );    

void vdrawcontextSetCurrentPoint(
    vdrawcontext *context,
    double x,
    double y
    );

void vdrawcontextSetCurrentPointRelative(
    vdrawcontext *context,
    double dx,
    double dy
    );

void vdrawcontextTranslate(
    vdrawcontext *context,
    double x,
    double y
    );

void vdrawcontextTransformPoint(
    vdrawcontext *context,
    double x,
    double y,
    double *xout,
    double *yout
    );

void vdrawcontextForceDeviceResolutionScaling(
    vdrawcontext *context
    );

/*
 * CLASS DECLARATIONS
 */

#define vdrawcontextCLASS(CLASS, CONTEXT)                                     \
  vloadableCLASS(CLASS, CONTEXT);                                             \
  vclassMETHOD(vdrawcontextUTILIZE, (CONTEXT *context));                      \
  vclassMETHOD(vdrawcontextDISPOSE, (CONTEXT *context))

/*
 * PRIVATE TYPE DECLARATIONS
 */

struct vdrawcontext {     
  vloadable super;
  unsigned long flags;
  vdrawpath *clip;
  vdrawpen  *pen;
  vmatrix matrix;
  double x, y;

  unsigned long deviceFlags;
  void *device;
  const vdrawDynamicFuncs *dynamicFuncs;
  const vdrawStaticFuncs *staticFuncs;
  const vdrawDriver *driver;

  size_t  gsReferences;
};

struct vdrawcontextClass {
  vdrawcontextCLASS(vdrawcontextClass, vdrawcontext);
};

/*
 * PRIVATE CONSTANT DECLARATION
 */

enum {
  _vdrawcontextDIRTY_MATRIX          = 0x00000001,
  _vdrawcontextDIRTY_CLIP            = 0x00000002,
  _vdrawcontextDIRTY_PEN             = 0x00000004,
  _vdrawcontextDIRTY_POINT           = 0x00000008,
  _vdrawcontextDIRTY_MASK            = 0x0000000F,

  _vdrawcontextRECT_CLIP             = 0x00000010,
  _vdrawcontextEO_CLIP               = 0x00000020,
  _vdrawcontextCLIP_MASK             = 0x00000030,

  _vdrawcontextDISPOSED              = 0x40000000,

  _vdrawcontextSTROKE_ADJUST         = 0x20000000,

  _vdrawcontextUNROUND               = 0x10000000,

  _vdrawcontextNO_CURRENT_POINT      = 0x08000000
};

/*
 * PRIVATE FUNCTION DECLARATION
 */

vdrawcontext  *_vdrawcontextCreateFromCurrentGState(void);

/*
 * FUNCTIONS IMPLEMENTED AS MACROS
 */

#define vdrawcontextGetLoadable(c) vportBASE_OBJECT((c), super)
#define vdrawcontextGetInstance(c)                                            \
  vloadableGetInstance(vdrawcontextGetLoadable((c)))
#define vdrawcontextGetClass(c)                                               \
  (vdrawcontextClass *)vloadableGetClass(vdrawcontextGetLoadable((c)))
#define vdrawcontextCreateOfClass(c)                                          \
  (vdrawcontext *)vloadableCreateOfClass((vloadableClass *)(c))
#define vdrawcontextCreate()                                                  \
  vdrawcontextCreateOfClass(vdrawcontextGetDefaultClass())
#define vdrawcontextInitOfClass(i,c)                                          \
  vloadableInitOfClass(vdrawcontextGetLoadable((i)), (vloadableClass *)(c))
#define vdrawcontextInit(i)                                                   \
  vdrawcontextInitOfClass((i), vdrawcontextGetDefaultClass())
#define vdrawcontextDestroy(c) vloadableDestroy(vdrawcontextGetLoadable((c)))
#define vdrawcontextDestroyLater(c)                                           \
  vinstanceDestroyLater(vdrawcontextGetInstance((c)))
#define vdrawcontextClone(c)                                                  \
  (vdrawcontext *)vloadableCloneOfSubclass(vdrawcontextGetLoadable((c)),      \
					   (vloadableClass *)vdrawcontextGetDefaultClass())
#define vdrawcontextCopy(c,t)                                                 \
  vloadableCopy(vdrawcontextGetLoadable((c)), vdrawcontextGetLoadable((t)))
#define vdrawcontextCopyInit(c, t)                                            \
  vloadableCopyInitOfSubclass(vdrawcontextGetLoadable((c)),                   \
			      vdrawcontextGetLoadable((t)),                   \
			      vdrawcontextGetDefaultClass())

#define vdrawcontextUtilize(c)                                                \
  vclassSend(vdrawcontextGetClass((c)), vdrawcontextUTILIZE, ((c)))
#define vdrawcontextDispose(c)                                                \
  vclassSend(vdrawcontextGetClass((c)), vdrawcontextDISPOSE, ((c)))

#define _vdrawcontextEnsureUtilized(c)                                    \
  ( (((c)->flags & _vdrawcontextDIRTY_MASK) ||                            \
     (_vdrawGS->context != (void *)(c))) ?                                \
        (vdrawcontextUtilize((c))) : (void)0)

#define _vdrawcontextDraw(c,f)                                            \
  (_vdrawcontextEnsureUtilized((c)), (f))

#define vdrawcontextDeltaTransformDimension(c,x,y,xo,yo)                      \
  _vdrawcontextDraw((c), vdrawFDTransform((x),(y),(xo),(yo)))

#define vdrawcontextDrawArcs(c,r,n,s,e)                                       \
  _vdrawcontextDraw((c), vdrawRectArcsStroke((r),(n),(int)(s),(int)(e)))

#define vdrawcontextDrawArcsInside(c,r,n,s,e)                                 \
  _vdrawcontextDraw((c), vdrawRectArcsStrokeInside((r),(n),(int)(s),(int)(e)))

#define vdrawcontextDrawEllipses(c,r,n)                                       \
  _vdrawcontextDraw((c), vdrawRectEllipsesStroke((r),(n)))

#define vdrawcontextDrawEllipsesInside(c,r,n)                                 \
  _vdrawcontextDraw((c), vdrawRectEllipsesStrokeInside((r),(n)))

#define vdrawcontextDrawHilitedRectangles(c,r,n,t,b)                          \
  _vdrawcontextDraw((c), vdrawRectsHiliteStroke((r),(n),(t),(b)))

#define vdrawcontextDrawHilitedRectanglesInside(c,r,n,t,b)                    \
  _vdrawcontextDraw((c), vdrawRectsHiliteStrokeInside((r),(n),(t),(b)))

#define vdrawcontextDrawKeyStroke(c,k)                                        \
  _vdrawcontextDraw((c), vdrawKeyStrokeShow((k)))

#define vdrawcontextDrawRectangles(c,r,n)                                     \
  _vdrawcontextDraw((c), vdrawRectsStroke((r),(n)))

#define vdrawcontextDrawRectanglesFloat(c,r,n)                                \
  _vdrawcontextDraw((c), vdrawFRectsStroke((r),(n)))

#define vdrawcontextDrawRectanglesInside(c,r,n)                               \
  _vdrawcontextDraw((c), vdrawRectsStrokeInside((r),(n)))

#define vdrawcontextDrawRoundRectangles(c,r,n,radius)                         \
  _vdrawcontextDraw((c), vdrawRoundRectsStroke((r),(n),(int)(radius)))

#define vdrawcontextDrawRoundRectanglesInside(c,r,n,radius)                   \
  _vdrawcontextDraw((c), vdrawRoundRectsStrokeInside((r),(n),(int)(radius)))

#define vdrawcontextDrawString(c,s,r)                                         \
  vdrawcontextDrawStringScribed((c),vcharScribe((s)),(r))

#define vdrawcontextDrawStringCenter(c,s,r)                                   \
  _vdrawcontextDraw((c), vdrawRectShowCenter((s),(r)))

#define vdrawcontextDrawStringCenterScribed(c,s,r)                            \
  _vdrawcontextDraw((c), vdrawScribedRectShowCenter((s),(r)))     

#define vdrawcontextDrawStringCenterHorizontally(c,s,r)                       \
  _vdrawcontextDraw((c), vdrawRectShowCenterX((s),(r)))

#define vdrawcontextDrawStringCenterHorizontallyScribed(c,s,r)                \
  _vdrawcontextDraw((c), vdrawScribedRectShowCenterX((s),(r)))     

#define vdrawcontextDrawStringCenterVertically(c,s,r)                         \
  _vdrawcontextDraw((c), vdrawRectShowCenterY((s),(r)))

#define vdrawcontextDrawStringCenterVerticallyScribed(c,s,r)                  \
  _vdrawcontextDraw((c), vdrawScribedRectShowCenterY((s),(r)))     

#define vdrawcontextDrawStringUnderlined(c,s)                                 \
  _vdrawcontextDraw((c), vdrawUnderlineShow((s)))

#define vdrawcontextDrawStringUnderlinedScribed(c,s)                          \
  _vdrawcontextDraw((c), vdrawScribedUnderlineShow((s)))

#define vdrawcontextDrawStringUnderlineMnemonic(c,t,m,r,f)                    \
  vdrawcontextDrawStringUnderlineMnemonicScribed(c,vcharScribe(t),m,r,f)

#define vdrawcontextDrawHilitedBox(c,r,i,t,b)                                 \
  _vdrawcontextDraw((c), vdrawBoxHiliteFill(r,i,t,b))

#define vdrawcontextDrawHilitedDiamond(c,r,i,t,b)                             \
  _vdrawcontextDraw((c), vdrawDiamondHiliteFill(r,i,t,b))

#define vdrawcontextDrawHorizontalHilitedArrow(c,x,y,l,h,i,s,b)               \
  _vdrawcontextDraw((c), vdrawArrowHiliteFillX(x,y,l,h,i,s,b))

#define vdrawcontextDrawVerticalHilitedArrow(c,x,y,l,h,i,s,b)                 \
  _vdrawcontextDraw((c), vdrawArrowHiliteFillY(x,y,l,h,i,s,b))

#define vdrawcontextFillArcChords(c,r,n,s,e)			              \
  _vdrawcontextDraw((c), vdrawRectArcsFill((r),(n),(int)(s),(int)(e)))

#define vdrawcontextFillArcSectors(c,r,n,s,e)                                 \
  _vdrawcontextDraw((c), vdrawRectArcsFillSector((r),(n),(int)(s),(int)(e)))

#define vdrawcontextFillEllipses(c,r,n)                                       \
  _vdrawcontextDraw((c), vdrawRectEllipsesFill((r),(n)))

#define vdrawcontextFillRectangles(c,r,n)                                     \
  _vdrawcontextDraw((c), vdrawRectsFill((r),(n)))

#define vdrawcontextFillRectanglesFloat(c,r,n)                                \
  _vdrawcontextDraw((c), vdrawFRectsFill((r),(n)))

#define vdrawcontextFillHilitedRectangles(c,r,n,i,t,b)                        \
  _vdrawcontextDraw((c), vdrawRectsHiliteFill((r),(n),(i),(t),(b)))

#define vdrawcontextFillHilitedRectanglesInside(c,r,n,i,t,b)                  \
  _vdrawcontextDraw((c), vdrawRectsHiliteFillInside((r),(n),(i),(t),(b)))

#define vdrawcontextFillRoundRectangles(c,r,n,radius)                         \
  _vdrawcontextDraw((c), vdrawRoundRectsFill((r),(n),(int)(radius)))

#define vdrawcontextInverseTransformPoint(c,x,y,xout,yout)                    \
  _vdrawcontextDraw((c), vdrawFITransform((x),(y),(xout),(yout)))

#define vdrawcontextInverseDeltaTransformDimension(c,x,y,xout,yout)           \
  _vdrawcontextDraw((c), vdrawFIDTransform((x),(y),(xout),(yout)))

#define vdrawcontextTransformPoint(c,x,y,xout,yout)                           \
  _vdrawcontextDraw((c), vdrawFTransform((x),(y),(xout), (yout)))

#define vdrawcontextGetStrokeAdjustmentRule(c)                                \
  (((c)->flags & _vdrawcontextSTROKE_ADJUST) ?                                \
   vdrawSTROKE_ADJUST : vdrawNO_ADJUST)
#define vdrawcontextGetMatrix(c)                                              \
  (&(c)->matrix)
#define vdrawcontextGetClipBounds(c,s)                                        \
  vdrawpathGetBounds((c)->clip,(s))
#define vdrawcontextGetClipBoundsFloat(c,s)                                   \
  vdrawpathGetFloatBounds((c)->clip,(s))

vportEND_CPLUSPLUS_EXTERN_C

#endif

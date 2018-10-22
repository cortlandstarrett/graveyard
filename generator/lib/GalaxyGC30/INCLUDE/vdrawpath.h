/* $Id: vdrawpath.h,v 1.12 1997/10/23 21:38:16 gregt Exp $ */

/*
 * vdrawpath.h
 *
 * C Interface file for the Drawing Context object
 *
 * (c) Copyright Visix Software, Inc.
 * All rights reserved
 */

#ifndef vdrawpathINCLUDED
#define vdrawpathINCLUDED

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

typedef struct vdrawpath vdrawpath;
typedef struct vdrawpathClass vdrawpathClass;

/*
 * PUBLIC CONSTANT DECLARATIONS
 */

/*
 * PUBLIC FUNCTION DECLARATIONS
 */

void vdrawpathStartup(
    void
    );

/*
 * Drawing Path Functions
 */

vdrawpathClass *vdrawpathGetDefaultClass(
    void
    );

vdrawpathClass *vdrawpathGetClass(
    vdrawpath *path
    );

vloadable *vdrawpathGetLoadable(
    vdrawpath *path
    );

vinstance *vdrawpathGetInstance(
    vdrawpath *path
    );

vdrawpath *vdrawpathCreate(
    void
    );

vdrawpath *vdrawpathCreateOfClass(
    vdrawpathClass *clas
    );

vdrawpath *vdrawpathClone(
    vdrawpath *path
    );

void vdrawpathInit(
    vdrawpath *path
    );

void vdrawpathInitOfClass(
    vdrawpath *path,
    vdrawpathClass *clas
    );

void vdrawpathDestroy(
    vdrawpath *path
    );

void vdrawpathRelease(
    vdrawpath *path
    );

void vdrawpathCopy(
    vdrawpath *path,
    vdrawpath *target
    );

void vdrawpathCopyInit(
    vdrawpath *path,
    vdrawpath *target
    );

void vdrawpathAddReference(
    vdrawpath *path
    );

void vdrawpathAppendArcClockwise(
    vdrawpath *path,
    double cx,
    double cy,
    double radius,
    double startAngle,
    double endAngle
    );

void vdrawpathAppendArcCounterClockwise(
    vdrawpath *path,
    double cx,
    double cy,
    double radius,
    double startAngle,
    double endAngle
    );

void vdrawpathAppendCurve(
    vdrawpath *path,
    double cx1,
    double cy1,
    double cx2,
    double cy2,
    double cx3,
    double cy3
    );

void vdrawpathAppendCurveRelative(
    vdrawpath *path,
    double cx1,
    double cy1,
    double cx2,
    double cy2,
    double cx3,
    double cy3
    );

void vdrawpathAppendLineTo(
    vdrawpath *path,
    double x,
    double y
    );

void vdrawpathAppendLineToRelative(
    vdrawpath *path,
    double dx,
    double dy
    );

void vdrawpathAppendTangentArc(
    vdrawpath *path,
    double x1,
    double y1,
    double x2,
    double y2,
    double radius
    );

void vdrawpathAppendPath(
    vdrawpath *path,
    vdrawpath *newPath
    );

void vdrawpathClose(
    vdrawpath *path
    );

void vdrawpathFlatten(
    vdrawpath *path
    );

int vdrawpathGetComplexityHint(
    vdrawpath *path
    );

double vdrawpathGetFlatnessTolerance(
    vdrawpath *path
    );

void vdrawpathMoveTo(
    vdrawpath *path,
    double x,
    double y
    );

void vdrawpathMoveToRelative(
    vdrawpath *path,
    double dx,
    double dy
    );

void vdrawpathReset(
    vdrawpath *path
    );

void vdrawpathSetMask(
    vdrawpath *path,
    vimage *mask,
    vmatrix *mtx
    );

void vdrawpathSetString(
    vdrawpath *path,
    const vchar *string,
    vfont *font
    );

void vdrawpathSetStringScribed(
    vdrawpath *path,
    vscribe *scribe,
    vfont *font
    );

void vdrawpathSetArcChords(
    vdrawpath *path,
    const vrect *rects,
    size_t count,
    double startAngle,
    double endAngle
    );

void vdrawpathSetArcSectors(
    vdrawpath *path,
    const vrect *rects,
    size_t count,
    double startAngle,
    double endAngle
    );

void vdrawpathSetEllipses(
    vdrawpath *path,
    const vrect *rects,
    size_t count
    );

void vdrawpathSetRectangles(
    vdrawpath *path,
    const vrect *rects,
    size_t count
    );

void vdrawpathSetRectanglesFloat(
    vdrawpath *path,
    const vrectFloat *rects,
    size_t count
    );

void vdrawpathSetRoundRectangles(
    vdrawpath *path,
    const vrect *rects,
    size_t count,
    double radius
    );

void vdrawpathSetComplexityHint(
    vdrawpath *path,
    int complexity
    );

void vdrawpathSetFlatnessTolerance(
    vdrawpath *path,
    double flatness
    );

const vrect *vdrawpathGetBounds(
    vdrawpath *path,
    size_t *count
    );

const vrectFloat *vdrawpathGetFloatBounds(
    vdrawpath *path,
    size_t *count
    );


/*
 * CLASS DECLARATIONS
 */

#define vdrawpathCLASS(CLASS, PATH)                                           \
  vloadableCLASS(CLASS, PATH)


/*
 * PRIVATE TYPE DECLARATIONS
 */

struct vdrawpath {
  vloadable super;
  vdrawUPath upath;
  unsigned long references;
  double flatness;
  int complexityHint;
  vbool badInverse;
};

struct vdrawpathClass {
  vdrawpathCLASS(vdrawpathClass, vdrawpath);
};

/*
 * PRIVATE CONSTANT DECLARATION
 */

/*
 * PRIVATE FUNCTION DECLARATION
 */

void _vdrawpathUtilize(vdrawpath *path);

void _vdrawpathCacheChanges(vdrawpath *path);

void _vdrawDestroyPath(_vdrawPath *path);

/*
 * FUNCTIONS IMPLEMENTED AS MACROS
 */

#define vdrawpathGetLoadable(c) vportBASE_OBJECT((c), super)
#define vdrawpathGetInstance(c)                                               \
  vloadableGetInstance(vdrawpathGetLoadable((c)))
#define vdrawpathGetClass(c)                                                  \
  (vdrawpathClass *)vloadableGetClass(vdrawpathGetLoadable((c)))
#define vdrawpathCreateOfClass(c)                                             \
  (vdrawpath *)vloadableCreateOfClass((vloadableClass *)(c))
#define vdrawpathCreate()                                                     \
  vdrawpathCreateOfClass(vdrawpathGetDefaultClass())
#define vdrawpathInitOfClass(i,c)                                             \
  vloadableInitOfClass(vdrawpathGetLoadable((i)), (vloadableClass *)(c))
#define vdrawpathInit(i)                                                      \
  vdrawpathInitOfClass((i), vdrawpathGetDefaultClass())
#define vdrawpathDestroy(c) vloadableDestroy(vdrawpathGetLoadable((c)))
#define vdrawpathClone(c)                                                     \
  (vdrawpath *)vloadableCloneOfSubclass((c), vdrawpathGetDefaultClass())
#define vdrawpathCopy(c,t)                                                    \
  vloadableCopy(vdrawpathGetLoadable((c)), vdrawpathGetLoadable((t)))
#define vdrawpathCopyInit(c, t)                                               \
  vloadableCopyInitOfSubclass(vdrawpathGetLoadable((c)),                      \
			      vdrawpathGetLoadable((t)),                      \
			      vdrawpathGetDefaultClass())

#define _vdrawpathModify(p, f)                                                \
  do {                                                                        \
    if ((p)->upath.path != NULL) {                                            \
      if (_vdrawGS->path != (p)->upath.path) {                                \
        _vdrawpathUtilize((p));                                               \
      }                                                                       \
      if (--((p)->upath.path->references) == 0)                               \
        _vdrawDestroyPath((p)->upath.path);                                   \
      (p)->upath.path = NULL;                                                 \
    } else {                                                                  \
      _vdrawpathUtilize((p));                                                 \
    }                                                                         \
    (f);                                                                      \
   _vdrawpathCacheChanges((p));                                               \
  } while (0)

#define vdrawpathGetFlatnessTolerance(p) ((p)->flatness)
#define vdrawpathGetComplexityHint(p)    ((p)->complexityHint)

#define vdrawpathAppendArcClockwise(path,cx,cy,r,startAngle,endAngle)         \
  _vdrawpathModify((path), vdrawFArcN((cx),(cy),(r),(startAngle),(endAngle)))

#define vdrawpathAppendArcCounterClockwise(path,cx,cy,r,startAngle,endAngle)  \
  _vdrawpathModify((path), vdrawFArc((cx),(cy),(r),(startAngle),(endAngle)))

#define vdrawpathAppendCurve(path,cx1,cy1,cx2,cy2,cx3,cy3)                    \
  _vdrawpathModify((path), vdrawFCurveTo((cx1),(cy1),(cx2),(cy2),(cx3),(cy3)))

#define vdrawpathAppendCurveRelative(path,cx1,cy1,cx2,cy2,cx3,cy3)            \
  _vdrawpathModify((path), vdrawFRCurveTo((cx1),(cy1),(cx2),(cy2),(cx3),(cy3)))

#define vdrawpathAppendLineTo(path,x,y)                                       \
  _vdrawpathModify((path), vdrawFLineTo((x),(y)))

#define vdrawpathAppendLineToRelative(path,dx,dy)                             \
  _vdrawpathModify((path), vdrawFRLineTo((dx),(dy)))

#define vdrawpathAppendPath(p,n)                                              \
  _vdrawpathModify((p),vdrawUAppend(&(n)->upath))

#define vdrawpathAppendTangentArc(path,x1,y1,x2,y2,radius)                    \
  _vdrawpathModify((path), vdrawFArcT((x1),(y1),(x2),(y2),(radius)))

#define vdrawpathClose(path)                                                  \
  _vdrawpathModify((path), vdrawClosePath())

#define vdrawpathMoveTo(path,x,y)                                             \
  _vdrawpathModify((path), vdrawFMoveTo((x),(y)))

#define vdrawpathMoveToRelative(path,dx,dy)                                   \
  _vdrawpathModify((path), vdrawFRMoveTo((dx),(dy)))

#define vdrawpathReset(path)                                                  \
  _vdrawpathModify((path), vdrawNewPath())

#define vdrawpathFlatten(path)                                                \
  _vdrawpathModify((path), vdrawFlattenPath())

#define vdrawpathSetString(path, string, font)                                \
  vdrawpathSetStringScribed(path, vcharScribe(string), font)

#define vdrawpathSetArcChords(path,rects,count,startAngle,endAngle)           \
  _vdrawpathModify((path), vdrawRectArcs((rects),(int)(count),                \
					 (int)vmathRound(startAngle),         \
					 (int)vmathRound(endAngle)))

#define vdrawpathSetArcSectors(path,rects,count,startAngle,endAngle)          \
  _vdrawpathModify((path), vdrawRectArcsSector((rects),(int)(count),          \
					 (int)vmathRound(startAngle),         \
					 (int)vmathRound(endAngle)))

#define vdrawpathSetEllipses(path,rects,count)                                \
  _vdrawpathModify((path), vdrawRectEllipses((rects),(int)(count)))

#define vdrawpathSetRectangles(path,rects,count)                              \
  _vdrawpathModify((path), vdrawRects((rects),(int)(count)))

#define vdrawpathSetRectanglesFloat(path,rects,count)                         \
  _vdrawpathModify((path), vdrawFRects((rects),(int)(count)))

#define vdrawpathSetRoundRectangles(path,rects,count,radius)                  \
  _vdrawpathModify((path), vdrawRoundRects((rects),(int)(count),              \
				       (int)vmathRound(radius)))

#define vdrawpathAddReference(p)  (++(p)->references)

vportEND_CPLUSPLUS_EXTERN_C

#endif

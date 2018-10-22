/* $Id: vdraw.h,v 1.81 1997/06/19 01:14:29 robert Exp $ */

/************************************************************

    vdraw.h

    C Interface file for the Drawing Manager

    (c) Copyright Visix Software Inc.
    All rights reserved

************************************************************/

#ifndef vdrawINCLUDED
#define vdrawINCLUDED

#ifndef  vportINCLUDED
#include <vport.h>
#endif

#ifndef  vexINCLUDED
#include vexHEADER
#endif

#ifndef  vmemINCLUDED
#include vmemHEADER
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

#ifndef  vfixedINCLUDED
#include vfixedHEADER
#endif

#ifndef  vrectINCLUDED
#include vrectHEADER
#endif

#ifndef  vpointINCLUDED
#include vpointHEADER
#endif

#ifndef  vmatrixINCLUDED
#include vmatrixHEADER
#endif

#ifndef  vtransformINCLUDED
#include vtransformHEADER
#endif

#ifndef  vfixedINCLUDED
#include vfixedHEADER
#endif

#ifndef  vkeyINCLUDED
#include vkeyHEADER
#endif

#ifndef  vfsINCLUDED
#include vfsHEADER
#endif

#ifndef  vresourceINCLUDED
#include vresourceHEADER
#endif

#ifndef  vpixmapINCLUDED
#include vpixmapHEADER
#endif

#ifndef  vcolorINCLUDED
#include vcolorHEADER
#endif

#ifndef  vfontINCLUDED
#include vfontHEADER
#endif

#ifndef  vimageINCLUDED
#include vimageHEADER
#endif

#ifndef vthreadINCLUDED
#include vthreadHEADER
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * * * * * * * * * * PUBLIC CONSTANT DEFINITIONS * * * * * * * * * *
 */

/*
 * drawing
 */

enum {
    _vdrawDEFAULT_TRANSFORM         = 0x8000,

    _vdrawRULE_MASK                 = 0x1000,
    vdrawRULE_EVEN_ODD              = 0x1000,
    vdrawRULE_WINDING               = 0x0000,

    _vdrawCAP_MASK                  = 0x0C00,
    vdrawCAP_BUTT                   = 0x0C00,
    vdrawCAP_ROUND                  = 0x0800,
    vdrawCAP_PROJECTING             = 0x0400,

    _vdrawJOIN_MASK                 = 0x0300,
    vdrawJOIN_MITER                 = 0x0300,
    vdrawJOIN_ROUND                 = 0x0200,
    vdrawJOIN_BEVEL                 = 0x0100,

    _vdrawCOMPLEX_MASK              = 0x00C0,
    vdrawPATH_CONVEX                = 0x00C0,
    vdrawPATH_NONCONVEX             = 0x0080,
    vdrawPATH_COMPLEX               = 0x0040,

    _vdrawADJUST_MASK               = 0x0020,
    vdrawSTROKE_ADJUST              = 0x0020,
    vdrawNO_ADJUST                  = 0x0000,

    _vdrawFUNC_MASK                 = 0x001F,
    vdrawFUNC_CLEAR                 = 0x0000,
    vdrawFUNC_AND                   = 0x0001,
    vdrawFUNC_AND_REV               = 0x0002,
    vdrawFUNC_COPY                  = 0x0003,
    vdrawFUNC_AND_INV               = 0x0004,
    vdrawFUNC_NOP                   = 0x0005,
    vdrawFUNC_XOR                   = 0x0006,
    vdrawFUNC_OR                    = 0x0007,
    vdrawFUNC_NOR                   = 0x0008,
    vdrawFUNC_EQUIV                 = 0x0009,
    vdrawFUNC_INVERT                = 0x000A,
    vdrawFUNC_OR_REV                = 0x000B,
    vdrawFUNC_COPY_INV              = 0x000C,
    vdrawFUNC_OR_INV                = 0x000D,
    vdrawFUNC_NAND                  = 0x000E,
    vdrawFUNC_SET                   = 0x000F,
    vdrawFUNC_HILITE                = 0x0010,
    vdrawFUNC_COMPLEMENT            = 0x0011,
    _vdrawFUNC_MIN                  = vdrawFUNC_CLEAR,
    _vdrawFUNC_MAX                  = vdrawFUNC_COMPLEMENT
};

enum {
    vdrawPATH_MOVE                  = 0x0000,
    vdrawPATH_LINE                  = 0x0001,
    vdrawPATH_CURVE                 = 0x0002,
    vdrawPATH_CLOSE                 = 0x0003,
    _vdrawPATH_ARC1                 = 0x0004,
    _vdrawPATH_ARC2                 = 0x0005
};

enum {
    _vdrawDIRTY_CLIP                = 0x8000,

    vdrawDIRTY_COLOR                = 0x0001,
    vdrawDIRTY_COMPLEMENT           = 0x0002,
    vdrawDIRTY_COMPLEXITY           = 0x0004,
    vdrawDIRTY_DASH                 = 0x0008,
    vdrawDIRTY_FONT                 = 0x0010,
    vdrawDIRTY_FUNCTION             = 0x0020,
    vdrawDIRTY_CAP                  = 0x0040,
    vdrawDIRTY_JOIN                 = 0x0080,
    vdrawDIRTY_WIDTH                = 0x0100,
    vdrawDIRTY_MITER                = 0x0200,
    vdrawDIRTY_PHASE                = 0x0400,
    vdrawDIRTY_ADJUST               = 0x0800,
    vdrawDIRTY_RULE                 = 0x1000
};

enum {
    vdrawSHOW_X                     = 0x0001,
    vdrawSHOW_Y                     = 0x0002
};

enum {
    vdrawDEVICE_VIEW_CLIP           = 0x8000,
    vdrawDEVICE_DUMMY_VIEW_CLIP     = 0x4000,
    vdrawDEVICE_MASK                = 0x2000
};

enum {
    vdrawSTATIC_FUNCS_COMPLEMENT    = 0x0001,
    vdrawSTATIC_FUNCS_PHASE         = 0x0002
};

enum {
    vdrawDYNAMIC_FUNCS_ARC          = 0x0001
};

enum {
    vdrawDRIVER_STROKE_ADJUST       = vdrawSTROKE_ADJUST,
    vdrawDRIVER_ROUND               = 0x0001
};

/*
 * deprecated drawing
 */

enum {
    vdrawCOLOR_DISABLE              = vcolorID_DISABLE
};

enum {
    vdrawCOLOR_FOREGROUND           = vcolorID_FOREGROUND,
    vdrawCOLOR_BACKGROUND           = vcolorID_BACKGROUND,
    vdrawCOLOR_SHADOW_TOP           = vcolorID_SHADOW_TOP,
    vdrawCOLOR_SHADOW_BOTTOM        = vcolorID_SHADOW_BOTTOM,
    vdrawCOLOR_FOREGROUND_HILITE    = vcolorID_FOREGROUND_HILITE,
    vdrawCOLOR_BACKGROUND_HILITE    = vcolorID_BACKGROUND_HILITE,
    vdrawCOLOR_BACKGROUND_EMBOSS    = vcolorID_BACKGROUND_EMBOSS,
    vdrawCOLOR_BACKGROUND_DEBOSS    = vcolorID_BACKGROUND_DEBOSS,
    vdrawCOLOR_BORDER               = vcolorID_BORDER,
    vdrawCOLOR_FOCUS                = vcolorID_FOCUS,
    vdrawCOLOR_HILITE               = vcolorID_BACKGROUND_HILITE,
    vdrawCOLOR_SHADOW_TOP_DARK      = vcolorID_SHADOW_TOP_DARK,
    vdrawCOLOR_SHADOW_BOTTOM_DARK   = vcolorID_SHADOW_BOTTOM_DARK,
    vdrawCOLOR_MAX                  = vcolorID_MAX
};

/*
 * * * * * * * * * * PUBLIC TYPE DEFINITIONS * * * * * * * * * *
 */

/*
 * drawing
 */

typedef struct vdrawGState          vdrawGState;
typedef struct vdrawUPath           vdrawUPath;
typedef struct vdrawPathIterator    vdrawPathIterator;

typedef struct vdrawDynamicFuncs    vdrawDynamicFuncs;
typedef struct vdrawStaticFuncs     vdrawStaticFuncs;
typedef struct vdrawDriver          vdrawDriver;

typedef vexModuleStateException     vdrawNoCurrentPointException;

typedef void (*vdrawKeyStrokeShowProc)(
    vkeyStroke                      key
    );

struct vdrawDynamicFuncs {
    unsigned int flags;
    void (*FDTransform)(double dx, double dy, double *rdx, double *rdy);
    void (*FIDTransform)(double dx, double dy, double *rdx, double *rdy);
    void (*FITransform)(double x, double y, double *rx, double *ry);
    void (*FTransform)(double x, double y, double *rx, double *ry);
    void (*ClosePath)(void);
    void (*FCurveTo)(double x1, double y1, double x2, double y2, 
		     double x3, double y3);
    void (*LineTo)(int x, int y);
    void (*FLineTo)(double x, double y);
    void (*MoveTo)(int x, int y);
    void (*FMoveTo)(double x, double y);
    void (*NewPath)(void);
    void (*FRCurveTo)(double dx1, double dy1, double dx2, double dy2, 
		      double dx3, double dy3);
    void (*RLineTo)(int dx, int dy);
    void (*FRLineTo)(double dx, double dy);
    void (*RMoveTo)(int dx, int dy);
    void (*FRMoveTo)(double dx, double dy);
    void (*FRRCurveTo)(double dx1, double dy1, double dx2, double dy2, 
		       double dx3, double dy3);
    void (*FArc)(double x, double y, double r, double angle1, double angle2,
		 int direct);
    void (*FArcTo)(double x1, double y1, double x2, double y2, double r, 
		   double *rxt1, double *ryt1, double *rxt2, double *ryt2);
    void (*Clip)(int rule);
    void (*Fill)(int rule);
    void (*Stroke)(void);
    void (*ViewClip)(int rule);
    void (*RectsClip)(const vrect *rects, int count);
    void (*FRectsClip)(const vrectFloat *rects, int count);
    void (*RectsFill)(const vrect *rects, int count);
    void (*FRectsFill)(const vrectFloat *rects, int count);
    void (*RectsStroke)(const vrect *rects, int count);
    void (*FRectsStroke)(const vrectFloat *rects, int count);
    void (*RectsViewClip)(const vrect *rects, int count);
    void (*FRectsViewClip)(const vrectFloat *rects, int count);
    void (*FSizedAWidthShow)(double cx, double cy, int c, double ax, double ay,
			     const vchar *s, size_t count);
    void (*SizedShow)(const vchar *s, size_t count);
    void (*FSizedXYShow)
	     (const vchar *s, size_t count, const float *widths, int flags);
    void (*Image)(vimage *image, const vmatrix *mtx);
    void (*ImageMask)(vimage *mask, const vmatrix *mtx);
    void (*ImageIdent)(vimage *image);
    void (*ImageMaskIdent)(vimage *mask);
    void (*SizedCharPath)(const vchar *s, size_t count);
    void (*MaskPath)(vimage *mask, const vmatrix *mtx);
    void (*MaskPathIdent)(vimage *mask);
    void (*RectArcsFill)(const vrect *rects, int count, 
			 int angle1, int angle2);
    void (*RectArcsFillSector)(const vrect *rects, int count, 
			       int angle1, int angle2);
    void (*RectArcsStroke)(const vrect *rects, int count, 
			   int angle1, int angle2);
    void (*RoundRectsFill)(const vrect *rects, int count, int r);
    void (*RoundRectsStroke)(const vrect *rects, int count, int r);
};

struct vdrawStaticFuncs {
    unsigned int flags;
    void (*InitClip)(void);
    void (*InitGraphics)(void);
    void (*InitMatrix)(void);
    void (*InitViewClip)(void);
    void (*GRestore)(void);
    void (*GRestoreAll)(void);
    void (*GSave)(void);
    void (*Concat)(const vmatrix *mtx);
    void (*FRotate)(double angle);
    void (*FScale)(double x, double y);
    void (*FTranslate)(double x, double y);
    void (*Unround)(void);
    void (*SetColor)(vcolor *color);
    void (*SetComplexity)(int complexity);
    void (*FSetDash)(int size, const float *pat, double offset);
    void (*FSetFlat)(double flatness);
    void (*SetFont)(vfont *font);
    void (*SetFunction)(int func);
    void (*SetLineCap)(int cap);
    void (*SetLineJoin)(int join);
    void (*FSetLineWidth)(double width);
    void (*SetMatrix)(const vmatrix *mtx);
    void (*FSetMiterLimit)(double limit);
    void (*SetStrokeAdjust)(int adjust);
    void (*ClipBounds)(const vrect **rects, int *count);
    void (*FClipBounds)(const vrectFloat **rects, int *count);
    void (*ClipPath)(void);
    void (*FlattenPath)(void);
    void (*InitPathIterator)(vdrawPathIterator *iterator);
    int  (*NextPathIterator)(vdrawPathIterator *iterator);
    void (*DestroyPathIterator)(vdrawPathIterator *iterator);
    void (*PathBounds)(const vrect **rects, int *count);
    void (*FPathBounds)(const vrectFloat **rects, int *count);
    void (*ReversePath)(void);
    void (*StrokePath)(void);
    void (*ViewClipBounds)(const vrect **rects, int *count);
    void (*FViewClipBounds)(const vrectFloat **rects, int *count);
    void (*ViewClipPath)(void);
    vdrawUPath *(*CreateUPath)(int cache);
    void        (*DestroyUPath)(vdrawUPath *upath);
    void        (*UAppend)(vdrawUPath *upath);
    void        (*UFill)(vdrawUPath *upath, int rule);
    void        (*UStroke)(vdrawUPath *upath);
    void (*SetComplement)(vcolor *complement);
    void (*SetPhase)(int x, int y);
};

struct vdrawDriver {
    unsigned int flags;
    vfixed       flatness;
    size_t       infoSize;
    void (*Init)(void *info, void *device, unsigned int flags);
    void (*Destroy)(void *info);
    void (*Open)(void *info);
    void (*Close)(void *info);
    const vtransform *(*DefaultTransform)(void *info);
    const vrect      *(*DefaultClip)(void *info);
    void (*Reset)(void *info);
    void (*Synchronize)(void *info, unsigned int flags);
    void (*MaskClip)(void *info, vimage *mask, int x, int y);
    void (*PolyFill)(void *info, const vpoint *points, int count);
    void (*PolyStroke)(void *info, const vpoint *points, int count);
    void (*RectsClip)(void *info, const vrect *rects, int count);
    void (*RectsFill)(void *info, const vrect *rects, int count);
    void (*RectsStroke)(void *info, const vrect *rects, int count);
    void (*ArcsFill)(void *info, const vrect *rects, int count, 
		     vfixed angle, vfixed length);
    void (*ArcsFillSector)(void *info, const vrect *rects, int count, 
			   vfixed angle, vfixed length);
    void (*ArcsStroke)(void *info, const vrect *rects, int count, 
		       vfixed angle, vfixed length);
    void (*RoundRectsFill)(void *info, const vrect *rects, int count, 
			   int rx, int ry);
    void (*RoundRectsStroke)(void *info, const vrect *rects, int count, 
			     int rx, int ry);
    void (*SizedShow)(void *info, const vchar *s, size_t count, 
		      const vtransform *transform);
    void (*Image)(void *info, vimage *image, const vtransform *transform);
    void (*ImageMask)(void *info, vimage *mask, const vtransform *transform);
};


vportALIAS(vdraw, void)

/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */

void vdrawStartup(
    void
    );

/*
 * drawing
 */

void vdrawInitClip(
    void
    );

void vdrawInitGraphics(
    void
    );

void vdrawInitMatrix(
    void
    );

void vdrawInitViewClip(
    void
    );

void vdrawCopyGState(
    vdrawGState                    *gstate1,
    vdrawGState                    *gstate2
    );

vdrawGState *vdrawCreateGState(
    void
    );

void vdrawDestroyGState(
    vdrawGState                    *gstate
    );

void vdrawGetGState(
    vdrawGState                    *gstate
    );

void vdrawDeactivateDevice(
    void
    );

void vdrawGRestore(
    void
    );

void vdrawGRestoreAll(
    void
    );

void vdrawGSave(
    void
    );

void vdrawSetGState(
    vdrawGState                    *gstate
    );

void vdrawConcat(
    const vmatrix                  *mtx
    );

void vdrawRotate(
    int                             angle
    );

void vdrawFRotate(
    double                          angle
    );

void vdrawScale(
    int                             x,
    int                             y
    );

void vdrawFScale(
    double                          x,
    double                          y
    );

void vdrawTranslate(
    int                             x,
    int                             y
    );

void vdrawFTranslate(
    double                          x,
    double                          y
    );

void vdrawUnround(
    void
    );

void vdrawDTransform(
    int                             dx,
    int                             dy,
    int                            *rdx,
    int                            *rdy
    );

void vdrawFDTransform(
    double                          dx,
    double                          dy,
    double                         *rdx,
    double                         *rdy
    );

void vdrawIDTransform(
    int                             dx,
    int                             dy,
    int                            *rdx,
    int                            *rdy
    );

void vdrawFIDTransform(
    double                          dx,
    double                          dy,
    double                         *rdx,
    double                         *rdy
    );

void vdrawITransform(
    int                             x,
    int                             y,
    int                            *rx,
    int                            *ry
    );

void vdrawFITransform(
    double                          x,
    double                          y,
    double                         *rx,
    double                         *ry
    );

void vdrawTransform(
    int                             x,
    int                             y,
    int                            *rx,
    int                            *ry
    );

void vdrawFTransform(
    double                          x,
    double                          y,
    double                         *rx,
    double                         *ry
    );

void vdrawSetColor(
    vcolor                         *color
    );

void vdrawSetComplement(
    vcolor                         *complement
    );

void vdrawSetComplexity(
    int                             complexity
    );

void vdrawFSetDash(
    int                             size,
    const float                    *pat,
    double                          offset
    );

void vdrawSetFlat(
    int                             flatness
    );

void vdrawFSetFlat(
    double                          flatness
    );

void vdrawSetFont(
    vfont                          *font
    );

void vdrawSetFunction(
    int                             func
    );

void vdrawSetLineCap(
    int                             cap
    );

void vdrawSetLineJoin(
    int                             join
    );

void vdrawSetLineWidth(
    int                             width
    );

void vdrawFSetLineWidth(
    double                          width
    );

void vdrawSetMatrix(
    const vmatrix                  *mtx
    );

void vdrawSetMiterLimit(
    int                             limit
    );

void vdrawFSetMiterLimit(
    double                          limit
    );

void vdrawSetPhase(
    int                             x,
    int                             y
    );

void vdrawSetStrokeAdjust(
    int                             adjust
    );

const vmatrix *vdrawDefaultMatrix(
    void
    );

vcolor *vdrawGetColor(
    void
    );

vcolor *vdrawGetComplement(
    void
    );

int vdrawGetComplexity(
    void
    );

void vdrawFGetDash(
    int                            *size, 
    const float                   **pat,
    double                         *offset
    );

int vdrawGetFlat(
    void
    );

double vdrawFGetFlat(
    void
    );

vfont *vdrawGetFont(
    void
    );

int vdrawGetFunction(
    void
    );

int vdrawGetLineCap(
    void
    );

int vdrawGetLineJoin(
    void
    );

int vdrawGetLineWidth(
    void
    );

double vdrawFGetLineWidth(
    void
    );

const vmatrix *vdrawGetMatrix(
    void
    );

int vdrawGetMiterLimit(
    void
    );

double vdrawFGetMiterLimit(
    void
    );

void vdrawGetPhase(
    int                            *rx,
    int                            *ry
    );

void vdrawGetPoint(
    int                            *rx,
    int                            *ry
    );

void vdrawFGetPoint(
    double                         *rx,
    double                         *ry
    );

int vdrawGetRule(
    void
    );

int vdrawGetStrokeAdjust(
    void
    );

const vtransform *vdrawGetTransform(
    void
    );

void vdrawClosePath(
    void
    );

void vdrawCurveTo(
    int                             x1,
    int                             y1,
    int                             x2,
    int                             y2,
    int                             x3,
    int                             y3
    );

void vdrawFCurveTo(
    double                          x1,
    double                          y1,
    double                          x2,
    double                          y2,
    double                          x3,
    double                          y3
    );

void vdrawLineTo(
    int                             x,
    int                             y
    );

void vdrawFLineTo(
    double                          x,
    double                          y
    );

void vdrawMoveTo(
    int                             x,
    int                             y
    );

void vdrawFMoveTo(
    double                          x,
    double                          y
    );

void vdrawNewPath(
    void
    );

void vdrawRCurveTo(
    int                             dx1,
    int                             dy1,
    int                             dx2,
    int                             dy2,
    int                             dx3,
    int                             dy3
    );

void vdrawFRCurveTo(
    double                          dx1,
    double                          dy1,
    double                          dx2,
    double                          dy2,
    double                          dx3,
    double                          dy3
    );

void vdrawRLineTo(
    int                             dx,
    int                             dy
    );

void vdrawFRLineTo(
    double                          dx,
    double                          dy
    );

void vdrawRMoveTo(
    int                             dx,
    int                             dy
    );

void vdrawFRMoveTo(
    double                          dx,
    double                          dy
    );

void vdrawRRCurveTo(
    int                             dx1,
    int                             dy1,
    int                             dx2,
    int                             dy2,
    int                             dx3,
    int                             dy3
    );

void vdrawFRRCurveTo(
    double                          dx1,
    double                          dy1,
    double                          dx2,
    double                          dy2,
    double                          dx3,
    double                          dy3
    );

void vdrawArc(
    int                             x,
    int                             y,
    int                             r,
    int                             angle1,
    int                             angle2
    );

void vdrawFArc(
    double                          x,
    double                          y,
    double                          r,
    double                          angle1,
    double                          angle2
    );

void vdrawArcN(
    int                             x,
    int                             y,
    int                             r,
    int                             angle1,
    int                             angle2
    );

void vdrawFArcN(
    double                          x,
    double                          y,
    double                          r,
    double                          angle1,
    double                          angle2
    );

void vdrawArcT(
    int                             x1,
    int                             y1,
    int                             x2,
    int                             y2,
    int                             r
    );

void vdrawFArcT(
    double                          x1,
    double                          y1,
    double                          x2,
    double                          y2,
    double                          r
    );

void vdrawFArcTo(
    double                          x1,
    double                          y1,
    double                          x2,
    double                          y2,
    double                          r,
    double                         *rxt1,
    double                         *ryt1,
    double                         *rxt2,
    double                         *ryt2
    );

void vdrawClipBounds(
    const vrect                   **rects,
    int                            *count
    );

void vdrawFClipBounds(
    const vrectFloat              **rects,
    int                            *count
    );

void vdrawClipPath(
    void
    );

void vdrawFlattenPath(
    void
    );

void vdrawInitPathIterator(
    vdrawPathIterator              *iterator
    );

int vdrawNextPathIterator(
    vdrawPathIterator              *iterator
    );

void vdrawDestroyPathIterator(
    vdrawPathIterator              *iterator
    );

int vdrawGetPathIteratorType(
    vdrawPathIterator              *iterator
    );

double vdrawFGetPathIteratorX(
    vdrawPathIterator              *iterator
    );

double vdrawFGetPathIteratorY(
    vdrawPathIterator              *iterator
    );

double vdrawFGetPathIteratorX1(
    vdrawPathIterator              *iterator
    );

double vdrawFGetPathIteratorY1(
    vdrawPathIterator              *iterator
    );

double vdrawFGetPathIteratorX2(
    vdrawPathIterator              *iterator
    );

double vdrawFGetPathIteratorY2(
    vdrawPathIterator              *iterator
    );

double vdrawFGetPathIteratorX3(
    vdrawPathIterator              *iterator
    );

double vdrawFGetPathIteratorY3(
    vdrawPathIterator              *iterator
    );

void vdrawPathBounds(
    const vrect                   **rects,
    int                            *count
    );

void vdrawFPathBounds(
    const vrectFloat              **rects,
    int                            *count
    );

void vdrawViewClipBounds(
    const vrect                   **rects,
    int                            *count
    );

void vdrawFViewClipBounds(
    const vrectFloat              **rects,
    int                            *count
    );

void vdrawViewClipPath(
    void
    );

void vdrawClip(
    void
    );

void vdrawEOClip(
    void
    );

void vdrawFill(
    void
    );

void vdrawEOFill(
    void
    );

void vdrawStroke(
    void
    );

void vdrawViewClip(
    void
    );

void vdrawEOViewClip(
    void
    );

void vdrawRects(
    const vrect                    *rects,
    int                             count
    );

void vdrawFRects(
    const vrectFloat               *rects,
    int                             count
    );

void vdrawRectsClip(
    const vrect                    *rects,
    int                             count
    );

void vdrawFRectsClip(
    const vrectFloat               *rects,
    int                             count
    );

void vdrawRectsFill(
    const vrect                    *rects,
    int                             count
    );

void vdrawFRectsFill(
    const vrectFloat               *rects,
    int                             count
    );

void vdrawRectsStroke(
    const vrect                    *rects,
    int                             count
    );

void vdrawFRectsStroke(
    const vrectFloat               *rects,
    int                             count
    );

void vdrawRectsViewClip(
    const vrect                    *rects,
    int                             count
    );

void vdrawFRectsViewClip(
    const vrectFloat               *rects,
    int                             count
    );

void vdrawRectArcs(
    const vrect                    *rects,
    int                             count,
    int                             angle1,
    int                             angle2
    );

void vdrawRectArcsSector(
    const vrect                    *rects,
    int                             count,
    int                             angle1,
    int                             angle2
    );

void vdrawRectArcsFill(
    const vrect                    *rects,
    int                             count,
    int                             angle1,
    int                             angle2
    );

void vdrawRectArcsFillSector(
    const vrect                    *rects,
    int                             count,
    int                             angle1,
    int                             angle2
    );

void vdrawRectArcsStroke(
    const vrect                    *rects,
    int                             count,
    int                             angle1,
    int                             angle2
    );

void vdrawRoundRects(
    const vrect                    *rects,
    int                             count,
    int                             r
    );

void vdrawRoundRectsFill(
    const vrect                    *rects,
    int                             count,
    int                             r
    );

void vdrawRoundRectsStroke(
    const vrect                    *rects,
    int                             count,
    int                             r
    );

void vdrawAShow(
    int                             ax,
    int                             ay,
    const vchar                    *s
    );

void vdrawFAShow(
    double                          ax,
    double                          ay,
    const vchar                    *s
    );

void vdrawSizedAShow(
    int                             ax,
    int                             ay,
    const vchar                    *s,
    size_t                          count
    );

void vdrawFSizedAShow(
    double                          ax,
    double                          ay,
    const vchar                    *s,
    size_t                          count
    );

void vdrawScribedAShow(
    int                             ax,
    int                             ay,
    vscribe                        *scribe
    );

void vdrawFScribedAShow(
    double                          ax,
    double                          ay,
    vscribe                        *scribe
    );

void vdrawAWidthShow(
    int                             cx,
    int                             cy,
    int                             c,
    int                             ax,
    int                             ay,
    const vchar                    *s
    );

void vdrawFAWidthShow(
    double                          cx,
    double                          cy,
    int                             c,
    double                          ax,
    double                          ay,
    const vchar                    *s
    );

void vdrawSizedAWidthShow(
    int                             cx,
    int                             cy,
    int                             c,
    int                             ax,
    int                             ay,
    const vchar                    *s,
    size_t                          count
    );

void vdrawFSizedAWidthShow(
    double                          cx,
    double                          cy,
    int                             c,
    double                          ax,
    double                          ay,
    const vchar                    *s,
    size_t                          count
    );

void vdrawScribedAWidthShow(
    int                             cx,
    int                             cy,
    int                             c,
    int                             ax,
    int                             ay,
    vscribe                        *scribe
    );

void vdrawFScribedAWidthShow(
    double                          cx,
    double                          cy,
    int                             c,
    double                          ax,
    double                          ay,
    vscribe                        *scribe
    );

void vdrawShow(
    const vchar                    *s
    );

void vdrawSizedShow(
    const vchar                    *s,
    size_t                          count
    );

void vdrawScribedShow(
    vscribe                        *scribe
    );

void vdrawWidthShow(
    int                             cx,
    int                             cy,
    int                             c,
    const vchar                    *s
    );

void vdrawFWidthShow(
    double                          cx,
    double                          cy,
    int                             c,
    const vchar                    *s
    );

void vdrawSizedWidthShow(
    int                             cx,
    int                             cy,
    int                             c,
    const vchar                    *s,
    size_t                          count
    );

void vdrawFSizedWidthShow(
    double                          cx,
    double                          cy,
    int                             c,
    const vchar                    *s,
    size_t                          count
    );

void vdrawScribedWidthShow(
    int                             cx,
    int                             cy,
    int                             c,
    vscribe                        *scribe
    );

void vdrawFScribedWidthShow(
    double                          cx,
    double                          cy,
    int                             c,
    vscribe                        *scribe
    );

void vdrawFXShow(
    const vchar                    *s,
    const float                    *widths
    );

void vdrawFSizedXShow(
    const vchar                    *s,
    size_t                          count,
    const float                    *widths
    );

void vdrawFScribedXShow(
    vscribe                        *scribe,
    const float                    *widths
    );

void vdrawFXYShow(
    const vchar                    *s,
    const float                    *widths
    );

void vdrawFSizedXYShow(
    const vchar                    *s,
    size_t                          count,
    const float                    *widths
    );

void vdrawFScribedXYShow(
    vscribe                        *scribe,
    const float                    *widths
    );

void vdrawFYShow(
    const vchar                    *s,
    const float                    *widths
    );

void vdrawFSizedYShow(
    const vchar                    *s,
    size_t                          count,
    const float                    *widths
    );

void vdrawFScribedYShow(
    vscribe                        *scribe,
    const float                    *widths
    );

void vdrawImage(
    vimage                         *image,
    const vmatrix                  *mtx
    );

void vdrawImageMask(
    vimage                         *mask,
    const vmatrix                  *mtx
    );

void vdrawImageIdent(
    vimage                         *image
    );

void vdrawImageMaskIdent(
    vimage                         *mask
    );

void vdrawCharPath(
    const vchar                    *s
    );

void vdrawSizedCharPath(
    const vchar                    *s,
    size_t                          count
    );

void vdrawScribedCharPath(
    vscribe                        *scribe
    );

void vdrawMaskPath(
    vimage                         *mask,
    const vmatrix                  *mtx
    );

void vdrawMaskPathIdent(
    vimage                         *mask
    );

vdrawUPath *vdrawCreateUPath(
    void
    );

vdrawUPath *vdrawCreateCachedUPath(
    void
    );

void vdrawDestroyUPath(
    vdrawUPath                     *upath
    );

void vdrawUAppend(
    vdrawUPath                     *upath
    );

void vdrawUFill(
    vdrawUPath                     *upath
    );

void vdrawUEOFill(
    vdrawUPath                     *upath
    );

void vdrawUStroke(
    vdrawUPath                     *upath
    );

void vdrawSetDevice(
    unsigned int                    flags,
    void                           *device,
    const vdrawDynamicFuncs        *dynamicFuncs,
    const vdrawStaticFuncs         *staticFuncs,
    const vdrawDriver              *driver
    );

void *vdrawGetDevice(
    void
    );

const vdrawDynamicFuncs *vdrawStdDynamicFuncs(
    void
    );

const vdrawStaticFuncs *vdrawStdStaticFuncs(
    void
    );

const vdrawDriver *vdrawNullDriver(
    void
    );

void vdrawNullDevice(
    void
    );

void vdrawImageDevice(
    vimage                         *image
    );

void vdrawMaskDevice(
    vimage                         *image
    );

void vdrawRegisterImageDriver(
    const vdrawDriver              *driver,
    unsigned int                    flags
    );

const vexClass *vdrawGetNoCurrentPointExceptionClass(
    void
    );

vdrawNoCurrentPointException *vdrawGetNoCurrentPointException(
    void
    );

/*
 * drawing tools
 */

void vdrawSetGray(
    unsigned int                    gray
    );

void vdrawFSetGray(
    double                          gray
    );

void vdrawSetHLSColor(
    unsigned int                    hue,
    unsigned int                    lightness,
    unsigned int                    saturation
    );

void vdrawFSetHLSColor(
    double                          hue,
    double                          lightness,
    double                          saturation
    );

void vdrawSetRGBColor(
    unsigned int                    red,
    unsigned int                    green,
    unsigned int                    blue
    );

void vdrawFSetRGBColor(
    double                          red,
    double                          green,
    double                          blue
    );

unsigned int vdrawGetGray(
    void
    );

double vdrawFGetGray(
    void
    );

void vdrawGetHLSColor(
    unsigned int                   *hue,
    unsigned int                   *lightness,
    unsigned int                   *saturation
    );

void vdrawFGetHLSColor(
    double                         *hue,
    double                         *lightness,
    double                         *saturation
    );

void vdrawGetRGBColor(
    unsigned int                   *red,
    unsigned int                   *green,
    unsigned int                   *blue
    );

void vdrawFGetRGBColor(
    double                         *red,
    double                         *green,
    double                         *blue
    );

int vdrawIntersectsClip(
    const vrect                    *rect
    );

int vdrawIntersectsViewClip(
    const vrect                    *rect
    );

void vdrawRectEllipses(
    const vrect                    *rects,
    int                             count
    );

void vdrawRectEllipsesFill(
    const vrect                    *rects,
    int                             count
    );

void vdrawRectEllipsesStroke(
    const vrect                    *rects,
    int                             count
    );

void vdrawRectsHiliteFill(
    const vrect                    *rects,
    int                             count,
    vcolor                         *interior,
    vcolor                         *top,
    vcolor                         *bottom
    );

void vdrawRectsHiliteStroke(
    const vrect                    *rects,
    int                             count,
    vcolor                         *top,
    vcolor                         *bottom
    );

void vdrawRectsStrokeInside(
    const vrect                    *rects,
    int                             count
    );

void vdrawRectArcsStrokeInside(
    const vrect                    *rects,
    int                             count,
    int                             angle1,
    int                             angle2
    );

void vdrawRectEllipsesStrokeInside(
    const vrect                    *rects,
    int                             count
    );

void vdrawRoundRectsStrokeInside(
    const vrect                    *rects,
    int                             count,
    int                             r
    );

void vdrawRectsHiliteFillInside(
    const vrect                    *rects,
    int                             count,
    vcolor                         *interior,
    vcolor                         *top,
    vcolor                         *bottom
    );

void vdrawRectsHiliteStrokeInside(
    const vrect                    *rects,
    int                             count,
    vcolor                         *top,
    vcolor                         *bottom
    );

void vdrawRectClip(
    int                             x,
    int                             y,
    int                             w,
    int                             h
    );

void vdrawRectFill(
    int                             x,
    int                             y,
    int                             w,
    int                             h
    );

void vdrawRectStroke(
    int                             x,
    int                             y,
    int                             w,
    int                             h
    );

void vdrawRectStrokeInside(
    int                             x,
    int                             y,
    int                             w,
    int                             h
    );

void vdrawRectArcFill(
    int                             x,
    int                             y,
    int                             w,
    int                             h,
    int                             angle1,
    int                             angle2
    );

void vdrawRectArcFillSector(
    int                             x,
    int                             y,
    int                             w,
    int                             h,
    int                             angle1,
    int                             angle2
    );

void vdrawRectArcStroke(
    int                             x,
    int                             y,
    int                             w,
    int                             h,
    int                             angle1,
    int                             angle2
    );

void vdrawRectArcStrokeInside(
    int                             x,
    int                             y,
    int                             w,
    int                             h,
    int                             angle1,
    int                             angle2
    );

void vdrawRectEllipseFill(
    int                             x,
    int                             y,
    int                             w,
    int                             h
    );

void vdrawRectEllipseStroke(
    int                             x,
    int                             y,
    int                             w,
    int                             h
    );

void vdrawRectEllipseStrokeInside(
    int                             x,
    int                             y,
    int                             w,
    int                             h
    );

void vdrawRoundRectFill(
    int                             x,
    int                             y,
    int                             w,
    int                             h,
    int                             r
    );

void vdrawRoundRectStroke(
    int                             x,
    int                             y,
    int                             w,
    int                             h,
    int                             r
    );

void vdrawRoundRectStrokeInside(
    int                             x,
    int                             y,
    int                             w,
    int                             h,
    int                             r
    );

void vdrawRectHiliteFill(
    int                             x,
    int                             y,
    int                             w,
    int                             h,
    vcolor                         *interior,
    vcolor                         *top,
    vcolor                         *bottom
    );

void vdrawRectHiliteFillInside(
    int                             x,
    int                             y,
    int                             w,
    int                             h,
    vcolor                         *interior,
    vcolor                         *top,
    vcolor                         *bottom
    );

void vdrawRectHiliteStroke(
    int                             x,
    int                             y,
    int                             w,
    int                             h,
    vcolor                         *top,
    vcolor                         *bottom
    );

void vdrawRectHiliteStrokeInside(
    int                             x,
    int                             y,
    int                             w,
    int                             h,
    vcolor                         *top,
    vcolor                         *bottom
    );

void vdrawRectShow(
    const vchar                    *s,
    const vrect                    *rect
    );
    
void vdrawSizedRectShow(
    const vchar                    *s,
    size_t                          count,
    const vrect                    *rect
    );
    
void vdrawScribedRectShow(
    vscribe                        *scribe,
    const vrect                    *rect
    );
    
void vdrawRectShowCenterX(
    const vchar                    *s,
    const vrect                    *rect
    );
    
void vdrawSizedRectShowCenterX(
    const vchar                    *s,
    size_t                          count,
    const vrect                    *rect
    );
    
void vdrawScribedRectShowCenterX(
    vscribe                        *scribe,
    const vrect                    *rect
    );
    
void vdrawRectShowCenterY(
    const vchar                    *s,
    const vrect                    *rect
    );
    
void vdrawSizedRectShowCenterY(
    const vchar                    *s,
    size_t                          count,
    const vrect                    *rect
    );
    
void vdrawScribedRectShowCenterY(
    vscribe                        *scribe,
    const vrect                    *rect
    );
    
void vdrawRectShowCenter(
    const vchar                    *s,
    const vrect                    *rect
    );

void vdrawSizedRectShowCenter(
    const vchar                    *s,
    size_t                          count,
    const vrect                    *rect
    );

void vdrawScribedRectShowCenter(
    vscribe                        *scribe,
    const vrect                    *rect
    );

void vdrawSetSizedRectShow(
    const vchar                    *s,
    size_t                          count,
    const vrect                    *rect,
    unsigned int                    flags
    );
    
void vdrawUnderline(
    const vchar                    *s
    );

void vdrawSizedUnderline(
    const vchar                    *s,
    size_t                          count
    );

void vdrawScribedUnderline(
    vscribe                        *scribe
    );

void vdrawUnderlineShow(
    const vchar                    *s
    );

void vdrawSizedUnderlineShow(
    const vchar                    *s,
    size_t                          count
    );

void vdrawScribedUnderlineShow(
    vscribe                        *scribe
    );

void vdrawKeyStrokeShow(
    vkeyStroke                      key
    );

void vdrawRegisterKeyStrokeShow(
    vdrawKeyStrokeShowProc          proc
    );

void vdrawImageComposite(
    vimage                         *image,
    const vmatrix                  *mtx
    );

void vdrawImageCompositeIdent(
    vimage                         *image
    );

void vdrawRectImage(
    vimage                         *image,
    const vrect                    *source,
    const vrect                    *dest
    );

void vdrawRectImageMask(
    vimage                         *mask,
    const vrect                    *source,
    const vrect                    *dest
    );

void vdrawRectImageComposite(
    vimage                         *image,
    const vrect                    *source,
    const vrect                    *dest
    );

void vdrawRectImageIdent(
    vimage                         *image,
    const vrect                    *source
    );

void vdrawRectImageMaskIdent(
    vimage                         *mask,
    const vrect                    *source
    );

void vdrawRectImageCompositeIdent(
    vimage                         *image,
    const vrect                    *source
    );

/*
 * laf-related drawing tools
 */

void vdrawUnderlineMnemonic(
    const vchar                    *title,
    int                             mnemonic
    );

void vdrawRectShowMnemonic(
    const vchar                    *title,
    int                             mnemonic,
    const vrect                    *rect,
    unsigned int                    flags
    );

void vdrawBoxHiliteFill(
    const vrect                    *rect,
    vcolor                         *interior,
    vcolor                         *top,
    vcolor                         *bottom
    );

void vdrawDiamondHiliteFill(
    const vrect                    *rect,
    vcolor                         *interior,
    vcolor                         *top,
    vcolor                         *bottom
    );

void vdrawArrowHiliteFillX(
    int                             x,
    int                             y,
    int                             length,
    int                             half,
    vcolor                         *interior,
    vcolor                         *straight,
    vcolor                         *bent
    );

void vdrawArrowHiliteFillY(
    int                             x,
    int                             y,
    int                             length,
    int                             half,
    vcolor                         *interior,
    vcolor                         *straight,
    vcolor                         *bent
    );

/*
 * * * * * * * * * * PRIVATE CONSTANT DEFINITIONS * * * * * * * * * *
 */

/*
 * drawing
 */

#define _vdrawDEVICE_INFO_ALLOC     128
#define _vdrawDEVICE_GSTATE_ALLOC   4

#define _vdrawPATH_ELEM_ALLOC       8
#define _vdrawPATH_RECT_ALLOC       11

/*
 * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * *
 */

/*
 * drawing
 */

typedef struct _vdrawSpace          _vdrawSpace;
typedef struct _vdrawDash           _vdrawDash;
typedef struct _vdrawPathElem       _vdrawPathElem;
typedef struct _vdrawDevice         _vdrawDevice;
typedef struct _vdrawPath           _vdrawPath;

typedef void (*_vdrawTransformProc)(
    double                          x, 
    double                          y,
    double                         *rx,
    double                         *ry
    );

typedef void (*_vdrawImageProc)(
    vimage                         *image,
    const vmatrix                  *matrix
    );

typedef void (*_vdrawImageIdentProc)(
    vimage                         *image
    );

struct vdrawGState {
    unsigned short                  flags;
    unsigned short                  dirty;
    unsigned short                  references;
    short                           lineWidthInt;
    _vdrawSpace                    *space;
    vcolor                         *color;
    vcolor                         *complement;
    _vdrawDash                     *dash;
    float                           lineWidth;
    float                           miterLimit;
    vfixed                          flatness;
    short                           phaseX, phaseY;
    _vdrawPath                     *path;
    _vdrawPath                     *clip;
    _vdrawDevice                   *device;
    void                           *context;
};

struct vdrawPathIterator {
    _vdrawPath                     *path;
    _vdrawPathElem                 *scan, *stop;
    int                             type;
    double                          x1, y1, x2, y2, x, y;
    int                             arc1Open;
    double                          cxd, cyd, rxd, ryd;
    vfixed                          fangle, flength;
};

struct _vdrawSpace {
    unsigned short                  flags;
    unsigned short                  references;
    vmatrix                         mtx, inverse;
    vtransform                      transform;
    vfont                          *font;
    vtransform                      stransform;
    vfixed                          stx, sty;
};

struct _vdrawDevice {
    unsigned short                  flags;
    void                           *instance;
    const vdrawDynamicFuncs        *dynamicFuncs;
    const vdrawStaticFuncs         *staticFuncs;
    const vdrawDriver              *driver;
    vtransform                      transform;
    vdrawGState                   **gstates, **gstateNext, **gstateMax;
    vdrawGState                    *staticGStates[_vdrawDEVICE_GSTATE_ALLOC];
    char                            info[_vdrawDEVICE_INFO_ALLOC];
};

struct _vdrawPathElem {
    int                             type;
    vfixed                          x, y;
};

struct _vdrawPath {
    short                           flags;
    short                           references;
    vrect                           bounds;
    _vdrawPathElem                 *next, *max;
    vfixed                          x, y, cx, cy;
    union {
	struct {
	    short                   count;
	    vrect                   buf[_vdrawPATH_RECT_ALLOC];
	} rects;
	vimage                     *mask;
	_vdrawPathElem              elems[_vdrawPATH_ELEM_ALLOC];
    } u;
};

struct vdrawUPath {
    vtransform                      transform;
    vmatrix                         imtx;
    _vdrawPath                     *path;
};

/*
 * * * * * * * * * * PRIVATE VARIABLE DECLARATIONS * * * * * * * * * *
 */

/*
 * drawing
 */

extern vportLINK vthreadLOCAL(vdrawGState *)             __vdrawGS;
extern vportLINK vthreadLOCAL(const vdrawDynamicFuncs *) __vdrawGSDynamicFuncs;
extern vportLINK vthreadLOCAL(const vdrawStaticFuncs *)  __vdrawGSStaticFuncs;
extern vportLINK vthreadLOCAL(const vdrawDriver *)       __vdrawGSDriver;
extern vportLINK vthreadLOCAL(void *)                    __vdrawGSInfo;
extern vportLINK vthreadLOCAL(const vdrawDynamicFuncs *) __vdrawStdDynamicFuncs;
#if (vportVMS_OS)
extern vportLINK vthreadLOCAL(const vdrawDynamicFuncs *) _vdrawTransformDynamicFuncs[];
#else
extern vportLINK vthreadLOCAL(const vdrawDynamicFuncs *) const _vdrawTransformDynamicFuncs[];
#endif
extern vportLINK const vdrawDynamicFuncs    _vdrawNullDynamicFuncs;
extern vportLINK const vdrawStaticFuncs     _vdrawStdStaticFuncs;
extern vportLINK const vdrawDriver          _vdrawNullDriver;
extern vportLINK const vexClass             _vdrawNoCurrentPointExceptionClass;

/*
 * * * * * * * * * * PRIVATE FUNCTION PROTOTYPES * * * * * * * * * *
 */

/*
 * drawing
 */

void _vdrawRectArcs(
    const vrect                    *rects,
    int                             count,
    int                             angle1,
    int                             angle2,
    int                             sector
    );

void _vdrawFScribedXYShow(
    vscribe                        *scribe,
    const float                    *widths, 
    int                             flags
    );

void _vdrawImageDevice(
    vimage                         *image,
    unsigned int                    flags
    );

/*
 * drawing tools
 */

void _vdrawSizedRectShow(
    const vchar                    *s,
    size_t                          count,
    const vrect                    *rect,
    unsigned int                    flags
    );
    
void _vdrawScribedRectShow(
    vscribe                        *scribe,
    const vrect                    *rect,
    unsigned int                    flags
    );
    
void _vdrawSizedUnderlineShow(
    const vchar                    *s,
    size_t                          count,
    int                             show
    );

void _vdrawScribedUnderlineShow(
    vscribe                        *scribe,
    int                             show
    );

void _vdrawImage(
    vimage                         *image,
    const vmatrix                  *mtx
    );

void _vdrawImageIdent(
    vimage                         *image
    );

void _vdrawImageMask(
    vimage                         *mask,
    const vmatrix                  *mtx
    );

void _vdrawImageMaskIdent(
    vimage                         *mask
    );

void _vdrawRectImage(
    vimage                         *image,
    const vrect                    *source,
    const vrect                    *dest,
    _vdrawImageProc                 proc
    );

void _vdrawRectImageIdent(
    vimage                         *image,
    const vrect                    *source,
    _vdrawImageIdentProc            proc
    );

/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * *
 */

/*
 * drawing
 */

/* macros to read thread local variables */
#define _vdrawGS                                                              \
  ((vdrawGState *)vthreadGetLocal(__vdrawGS))
#define _vdrawGSDynamicFuncs                                                  \
  ((const vdrawDynamicFuncs *)vthreadGetLocal((void *) __vdrawGSDynamicFuncs))
#define _vdrawGSStaticFuncs                                                   \
  ((const vdrawStaticFuncs *)vthreadGetLocal((void *) __vdrawGSStaticFuncs))
#define _vdrawGSDriver                                                        \
  ((const vdrawDriver *)vthreadGetLocal((void *) __vdrawGSDriver))
#define _vdrawGSInfo                                                          \
  ((void *)vthreadGetLocal(__vdrawGSInfo))
#define _vdrawStdDynamicFuncs                                                 \
  ((const vdrawDynamicFuncs *)vthreadGetLocal((void *) __vdrawStdDynamicFuncs))

#define _vdrawD(m, a)            ((*_vdrawGSDynamicFuncs->m)a)
#define _vdrawS(m, a)            ((*_vdrawGSStaticFuncs->m)a)

#define vdrawInitClip()             _vdrawS(InitClip, ())
#define vdrawInitGraphics()         _vdrawS(InitGraphics, ())
#define vdrawInitMatrix()           _vdrawS(InitMatrix, ())
#define vdrawInitViewClip()         _vdrawS(InitViewClip, ())

#define vdrawGRestore()             _vdrawS(GRestore, ())
#define vdrawGRestoreAll()          _vdrawS(GRestoreAll, ())

#define vdrawConcat(m)              _vdrawS(Concat, (m))
#define vdrawRotate(a)              _vdrawS(FRotate, ((double)(a)))
#define vdrawFRotate(a)             _vdrawS(FRotate, (a))
#define vdrawScale(x, y)            _vdrawS(FScale, ((double)(x), (double)(y)))
#define vdrawFScale(x, y)           _vdrawS(FScale, (x, y))
#define vdrawTranslate(x, y) \
    _vdrawS(FTranslate, ((double)(x), (double)(y)))
#define vdrawFTranslate(x, y)       _vdrawS(FTranslate, (x, y))
#define vdrawUnround()              _vdrawS(Unround, ())

#define vdrawFDTransform(x, y, rx, ry) \
    _vdrawD(FDTransform, (x, y, rx, ry))
#define vdrawFIDTransform(x, y, rx, ry) \
    _vdrawD(FIDTransform, (x, y, rx, ry))
#define vdrawFITransform(x, y, rx, ry) \
    _vdrawD(FITransform, (x, y, rx, ry))
#define vdrawFTransform(x, y, rx, ry) \
    _vdrawD(FTransform, (x, y, rx, ry))

#define vdrawSetColor(c)            _vdrawS(SetColor, (c))
#define vdrawSetComplexity(c)       _vdrawS(SetComplexity, (c))
#define vdrawFSetDash(s, p, o)      _vdrawS(FSetDash, (s, p, o))
#define vdrawSetFlat(f)             _vdrawS(FSetFlat, ((double)(f)))
#define vdrawFSetFlat(f)            _vdrawS(FSetFlat, (f))
#define vdrawSetFont(f)             _vdrawS(SetFont, (f))
#define vdrawSetFunction(f)         _vdrawS(SetFunction, (f))
#define vdrawSetLineCap(c)          _vdrawS(SetLineCap, (c))
#define vdrawSetLineJoin(j)         _vdrawS(SetLineJoin, (j))
#define vdrawSetLineWidth(w)        _vdrawS(FSetLineWidth, ((double)(w)))
#define vdrawFSetLineWidth(w)       _vdrawS(FSetLineWidth, (w))
#define vdrawSetMatrix(m)           _vdrawS(SetMatrix, (m))
#define vdrawSetMiterLimit(l)       _vdrawS(FSetMiterLimit, ((double)(l)))
#define vdrawFSetMiterLimit(l)      _vdrawS(FSetMiterLimit, (l))
#define vdrawSetStrokeAdjust(b)     _vdrawS(SetStrokeAdjust, (b))

#define vdrawGetColor()            (_vdrawGS->color)
#define vdrawGetComplement()       (_vdrawGS->complement)
#define vdrawGetComplexity()       (_vdrawGS->flags&_vdrawCOMPLEX_MASK)
#define vdrawFGetFlat()             vfixedToFloat(_vdrawGS->flatness)
#define vdrawGetFlat()            ((int)vmathRound(vdrawFGetFlat()))
#define vdrawGetFont()             (_vdrawGS->space->font)
#define vdrawGetFunction()         (_vdrawGS->flags&_vdrawFUNC_MASK)
#define vdrawGetLineCap()          (_vdrawGS->flags&_vdrawCAP_MASK)
#define vdrawGetLineJoin()         (_vdrawGS->flags&_vdrawJOIN_MASK)
#define vdrawGetLineWidth()        (_vdrawGS->lineWidthInt)
#define vdrawFGetLineWidth()       (_vdrawGS->lineWidth)
#define vdrawGetMatrix()          (&_vdrawGS->space->mtx)
#define vdrawGetMiterLimit()      ((int)vmathRound(_vdrawGS->miterLimit))
#define vdrawFGetMiterLimit()      (_vdrawGS->miterLimit)
#define vdrawGetRule()             (_vdrawGS->flags&_vdrawRULE_MASK)
#define vdrawGetStrokeAdjust()     (_vdrawGS->flags&_vdrawADJUST_MASK)
#define vdrawGetTransform() \
    ((const vtransform*)&_vdrawGS->space->transform)

#define vdrawClosePath()            _vdrawD(ClosePath, ())
#define vdrawCurveTo(x1, y1, x2, y2, x3, y3) \
    _vdrawD(FCurveTo, \
	    ((double)(x1), (double)(y1), \
	     (double)(x2), (double)(y2), (double)(x3), (double)(y3)))
#define vdrawFCurveTo(x1, y1, x2, y2, x3, y3) \
    _vdrawD(FCurveTo, (x1, y1, x2, y2, x3, y3))
#define vdrawLineTo(x, y)           _vdrawD(LineTo, (x, y))
#define vdrawFLineTo(x, y)          _vdrawD(FLineTo, (x, y))
#define vdrawMoveTo(x, y)           _vdrawD(MoveTo, (x, y))
#define vdrawFMoveTo(x, y)          _vdrawD(FMoveTo, (x, y))
#define vdrawNewPath()              _vdrawD(NewPath, ())
#define vdrawRCurveTo(x1, y1, x2, y2, x3, y3) \
    _vdrawD(FRCurveTo, \
	    ((double)(x1), (double)(y1), \
	     (double)(x2), (double)(y2), (double)(x3), (double)(y3)))
#define vdrawFRCurveTo(x1, y1, x2, y2, x3, y3) \
    _vdrawD(FRCurveTo, (x1, y1, x2, y2, x3, y3))
#define vdrawRLineTo(x, y)          _vdrawD(RLineTo, (x, y))
#define vdrawFRLineTo(x, y)         _vdrawD(FRLineTo, (x, y))
#define vdrawRMoveTo(x, y)          _vdrawD(RMoveTo, (x, y))
#define vdrawFRMoveTo(x, y)         _vdrawD(FRMoveTo, (x, y))
#define vdrawRRCurveTo(x1, y1, x2, y2, x3, y3) \
    _vdrawD(FRRCurveTo, \
	    ((double)(x1), (double)(y1), \
	     (double)(x2), (double)(y2), (double)(x3), (double)(y3)))
#define vdrawFRRCurveTo(x1, y1, x2, y2, x3, y3) \
    _vdrawD(FRRCurveTo, (x1, y1, x2, y2, x3, y3))

#define vdrawArc(x, y, r, a1, a2) \
    _vdrawD(FArc, ((double)(x), (double)(y), (double)(r), \
		   (double)(a1), (double)(a2), 1))
#define vdrawFArc(x, y, r, a1, a2)  _vdrawD(FArc, (x, y, r, a1, a2, 1))
#define vdrawArcN(x, y, r, a1, a2) \
    _vdrawD(FArc, ((double)(x), (double)(y), (double)(r), \
		   (double)(a1), (double)(a2), -1))
#define vdrawFArcN(x, y, r, a1, a2) _vdrawD(FArc, (x, y, r, a1, a2, -1))
#define vdrawArcT(x1, y1, x2, y2, r) \
    _vdrawD(FArcTo, \
	    ((double)(x1), (double)(y1), (double)(x2), (double)(y2), \
	     (double)(r), \
	     (double*)NULL, (double*)NULL, (double*)NULL, (double*)NULL))
#define vdrawFArcT(x1, y1, x2, y2, r) \
    _vdrawD(FArcTo, \
	    (x1, y1, x2, y2, r, \
	     (double*)NULL, (double*)NULL, (double*)NULL, (double*)NULL))
#define vdrawFArcTo(x1, y1, x2, y2, r, xt1, yt1, xt2, yt2) \
    _vdrawD(FArcTo, (x1, y1, x2, y2, r, xt1, yt1, xt2, yt2))

#define vdrawClipBounds(r, n)       _vdrawS(ClipBounds, (r, n))
#define vdrawFClipBounds(r, n)      _vdrawS(FClipBounds, (r, n))
#define vdrawClipPath()             _vdrawS(ClipPath, ())
#define vdrawFlattenPath()          _vdrawS(FlattenPath, ())
#define vdrawInitPathIterator(i)    _vdrawS(InitPathIterator, (i))
#define vdrawNextPathIterator(i)    _vdrawS(NextPathIterator, (i))
#define vdrawDestroyPathIterator(i) _vdrawS(DestroyPathIterator, (i))
#define vdrawGetPathIteratorType(i) ((i)->type)
#define vdrawFGetPathIteratorX(i)   ((i)->x)
#define vdrawFGetPathIteratorY(i)   ((i)->y)
#define vdrawFGetPathIteratorX1(i)  ((i)->x1)
#define vdrawFGetPathIteratorY1(i)  ((i)->y1)
#define vdrawFGetPathIteratorX2(i)  ((i)->x2)
#define vdrawFGetPathIteratorY2(i)  ((i)->y2)
#define vdrawFGetPathIteratorX3(i)  ((i)->x)
#define vdrawFGetPathIteratorY3(i)  ((i)->y)
#define vdrawPathBounds(r, n)       _vdrawS(PathBounds, (r, n))
#define vdrawFPathBounds(r, n)      _vdrawS(FPathBounds, (r, n))
#define vdrawViewClipBounds(r, n)   _vdrawS(ViewClipBounds, (r, n))
#define vdrawFViewClipBounds(r, n)  _vdrawS(FViewClipBounds, (r, n))
#define vdrawViewClipPath()         _vdrawS(ViewClipPath, ())

#define vdrawClip()                 _vdrawD(Clip, (vdrawRULE_WINDING))
#define vdrawEOClip()               _vdrawD(Clip, (vdrawRULE_EVEN_ODD))
#define vdrawFill()                 _vdrawD(Fill, (vdrawRULE_WINDING))
#define vdrawEOFill()               _vdrawD(Fill, (vdrawRULE_EVEN_ODD))
#define vdrawStroke()               _vdrawD(Stroke, ())
#define vdrawViewClip()             _vdrawD(ViewClip, (vdrawRULE_WINDING))
#define vdrawEOViewClip()           _vdrawD(ViewClip, (vdrawRULE_EVEN_ODD))

#define vdrawRectsClip(r, n)        _vdrawD(RectsClip, (r, n))
#define vdrawFRectsClip(r, n)       _vdrawD(FRectsClip, (r, n))
#define vdrawRectsFill(r, n)        _vdrawD(RectsFill, (r, n))
#define vdrawFRectsFill(r, n)       _vdrawD(FRectsFill, (r, n))
#define vdrawRectsStroke(r, n)      _vdrawD(RectsStroke, (r, n))
#define vdrawFRectsStroke(r, n)     _vdrawD(FRectsStroke, (r, n))
#define vdrawRectsViewClip(r, n)    _vdrawD(RectsViewClip, (r, n))
#define vdrawFRectsViewClip(r, n)   _vdrawD(FRectsViewClip, (r, n))
#define vdrawRectArcs(r, n, a1, a2) _vdrawRectArcs(r, n, a1, a2, FALSE)
#define vdrawRectArcsSector(r, n, a1, a2) _vdrawRectArcs(r, n, a1, a2, TRUE)

#define vdrawAShow(x, y, s) \
    _vdrawD(FSizedAWidthShow, \
	    (0.0, 0.0, ' ', (double)(x), (double)(y), s, vcharLength(s)))
#define vdrawFAShow(x, y, s) \
    _vdrawD(FSizedAWidthShow, (0.0, 0.0, ' ', x, y, s, vcharLength(s)))
#define vdrawSizedAShow(x, y, s, n) \
    _vdrawD(FSizedAWidthShow, (0.0, 0.0, ' ', (double)(x), (double)(y), s, n))
#define vdrawFSizedAShow(x, y, s, n) \
    _vdrawD(FSizedAWidthShow, (0.0, 0.0, ' ', x, y, s, n))
#define vdrawScribedAShow(x, y, s) \
    vdrawFScribedAWidthShow(0.0, 0.0, ' ', (double)(x), (double)(y), s)
#define vdrawFScribedAShow(x, y, s) \
    vdrawFScribedAWidthShow(0.0, 0.0, ' ', x, y, s)

#define vdrawAWidthShow(wx, wy, c, x, y, s) \
    _vdrawD(FSizedAWidthShow, \
	    ((double)(wx), (double)(wy), c, (double)(x), (double)(y), \
	     s, vcharLength(s)))
#define vdrawFAWidthShow(wx, wy, c, x, y, s) \
    _vdrawD(FSizedAWidthShow, (wx, wy, c, x, y, s, vcharLength(s)))
#define vdrawSizedAWidthShow(wx, wy, c, x, y, s, n) \
    _vdrawD(FSizedAWidthShow, \
	    ((double)(wx), (double)(wy), c, (double)(x), (double)(y), s, n))
#define vdrawFSizedAWidthShow(wx, wy, c, x, y, s, n) \
    _vdrawD(FSizedAWidthShow, (wx, wy, c, x, y, s, n))
#define vdrawScribedAWidthShow(wx, wy, c, x, y, s) \
    vdrawFScribedAWidthShow((double)(wx), (double)(wy), c, \
			    (double)(x), (double)(y), s)

#define vdrawShow(s)                _vdrawD(SizedShow, (s, vcharLength(s)))
#define vdrawSizedShow(s, n)        _vdrawD(SizedShow, (s, n))

#define vdrawWidthShow(x, y, c, s) \
    _vdrawD(FSizedAWidthShow, \
	    ((double)(x), (double)(y), c, 0.0, 0.0, s, vcharLength(s)))
#define vdrawFWidthShow(x, y, c, s) \
    _vdrawD(FSizedAWidthShow, (x, y, c, 0.0, 0.0, s, vcharLength(s)))
#define vdrawSizedWidthShow(x, y, c, s, n) \
    _vdrawD(FSizedAWidthShow, ((double)(x), (double)(y), c, 0.0, 0.0, s, n))
#define vdrawFSizedWidthShow(x, y, c, s, n) \
    _vdrawD(FSizedAWidthShow, (x, y, c, 0.0, 0.0, s, n))
#define vdrawScribedWidthShow(x, y, c, s) \
    vdrawFScribedAWidthShow((double)(x), (double)(y), c, 0.0, 0.0, s)
#define vdrawFScribedWidthShow(x, y, c, s) \
    vdrawFScribedAWidthShow(x, y, c, 0.0, 0.0, s)

#define _vdrawFSizedXYShow(s, n, a, f) \
    _vdrawD(FSizedXYShow, (s, n, a, f))
#define vdrawFXShow(s, a) \
    _vdrawD(FSizedXYShow, (s, vcharLength(s), a, vdrawSHOW_X))
#define vdrawFSizedXShow(s, n, a) \
    _vdrawD(FSizedXYShow, (s, n, a, vdrawSHOW_X))
#define vdrawFScribedXShow(s, a) \
    _vdrawFScribedXYShow(s, a, vdrawSHOW_X)
#define vdrawFXYShow(s, a) \
    _vdrawD(FSizedXYShow, (s, vcharLength(s), a, vdrawSHOW_X|vdrawSHOW_Y))
#define vdrawFSizedXYShow(s, n, a) \
    _vdrawD(FSizedXYShow, (s, n, a, vdrawSHOW_X|vdrawSHOW_Y))
#define vdrawFScribedXYShow(s, a) \
    _vdrawFScribedXYShow(s, a, vdrawSHOW_X|vdrawSHOW_Y)
#define vdrawFYShow(s, a) \
    _vdrawD(FSizedXYShow, (s, vcharLength(s), a, vdrawSHOW_Y))
#define vdrawFSizedYShow(s, n, a) \
    _vdrawD(FSizedXYShow, (s, n, a, vdrawSHOW_Y))
#define vdrawFScribedYShow(s, a) \
    _vdrawFScribedXYShow(s, a, vdrawSHOW_Y)

#define vdrawImage(i, m)            _vdrawD(Image, (i, m))
#define vdrawImageMask(i, m)        _vdrawD(ImageMask, (i, m))
#define vdrawImageIdent(i)          _vdrawD(ImageIdent, (i))
#define vdrawImageMaskIdent(i)      _vdrawD(ImageMaskIdent, (i))

#define vdrawCharPath(s)            _vdrawD(SizedCharPath, (s, vcharLength(s)))
#define vdrawSizedCharPath(s, n)    _vdrawD(SizedCharPath, (s, n))
#define vdrawMaskPath(i, m)         _vdrawD(MaskPath, (i, m))
#define vdrawMaskPathIdent(i)       _vdrawD(MaskPathIdent, (i))

#define vdrawCreateUPath()          _vdrawS(CreateUPath, (FALSE))
#define vdrawCreateCachedUPath()    _vdrawS(CreateUPath, (TRUE))
#define vdrawDestroyUPath(u)        _vdrawS(DestroyUPath, (u))
#define vdrawUAppend(u)             _vdrawS(UAppend, (u))
#define vdrawUFill(u)               _vdrawS(UFill, (u, vdrawRULE_WINDING))
#define vdrawUEOFill(u)             _vdrawS(UFill, (u, vdrawRULE_EVEN_ODD))
#define vdrawUStroke(u)             _vdrawS(UStroke, (u))

#define vdrawGetDevice()           (_vdrawGS->device->instance)
#define vdrawStdStaticFuncs()     (&_vdrawStdStaticFuncs)
#define vdrawNullDriver()         (&_vdrawNullDriver)

#define vdrawImageDevice(i)         _vdrawImageDevice(i, 0)
#define vdrawMaskDevice(i)          _vdrawImageDevice(i, vdrawDEVICE_MASK)

#define vdrawGetNoCurrentPointExceptionClass() \
    (&_vdrawNoCurrentPointExceptionClass)
#define vdrawGetNoCurrentPointException() \
    ((vdrawNoCurrentPointException*) \
         vexGetExceptionOfClass(&_vdrawNoCurrentPointExceptionClass))

/*
 * drawing tools
 */

#define vdrawFSetGray(g) \
    vdrawSetGray((unsigned int)((g)*vcolorCOMPONENT_MAX))
#define vdrawFSetHLSColor(h, l, s) \
    vdrawSetHLSColor((unsigned int)((h)*vcolorCOMPONENT_MAX), \
		     (unsigned int)((l)*vcolorCOMPONENT_MAX), \
		     (unsigned int)((s)*vcolorCOMPONENT_MAX))
#define vdrawFSetRGBColor(r, g, b) \
    vdrawSetRGBColor((unsigned int)((r)*vcolorCOMPONENT_MAX), \
		     (unsigned int)((g)*vcolorCOMPONENT_MAX), \
		     (unsigned int)((b)*vcolorCOMPONENT_MAX))
#define vdrawFGetGray()           ((double)vdrawGetGray()/vcolorCOMPONENT_MAX)

#define vdrawRectEllipses(r, n)     vdrawRectArcs(r, n, 0, 360)
#define vdrawRectEllipsesFill(r, n) vdrawRectArcsFill(r, n, 0, 360)
#define vdrawRectEllipsesStroke(r, n) vdrawRectArcsStroke(r, n, 0, 360)
#define vdrawRectEllipsesStrokeInside(r, n) \
    vdrawRectArcsStrokeInside(r, n, 0, 360)
#define vdrawRectEllipseFill(x, y, w, h) vdrawRectArcFill(x, y, w, h, 0, 360)
#define vdrawRectEllipseStroke(x, y, w, h) \
    vdrawRectArcStroke(x, y, w, h, 0, 360)
#define vdrawRectEllipseStrokeInside(x, y, w, h) \
    vdrawRectArcStrokeInside(x, y, w, h, 0, 360)

#define vdrawRectShow(s, r) \
    _vdrawSizedRectShow(s, vcharLength(s), r, 0)
#define vdrawSizedRectShow(s, n, r) _vdrawSizedRectShow(s, n, r, 0)
#define vdrawScribedRectShow(s, r) \
    _vdrawScribedRectShow(s, r, 0)
#define vdrawRectShowCenterX(s, r) \
    _vdrawSizedRectShow(s, vcharLength(s), r, vdrawSHOW_X)
#define vdrawSizedRectShowCenterX(s, n, r) \
    _vdrawSizedRectShow(s, n, r, vdrawSHOW_X)
#define vdrawScribedRectShowCenterX(s, r) \
    _vdrawScribedRectShow(s, r, vdrawSHOW_X)
#define vdrawRectShowCenterY(s, r) \
    _vdrawSizedRectShow(s, vcharLength(s), r, vdrawSHOW_Y)
#define vdrawSizedRectShowCenterY(s, n, r) \
    _vdrawSizedRectShow(s, n, r, vdrawSHOW_Y)
#define vdrawScribedRectShowCenterY(s, r) \
    _vdrawScribedRectShow(s, r, vdrawSHOW_Y)
#define vdrawRectShowCenter(s, r) \
    _vdrawSizedRectShow(s, vcharLength(s), r, vdrawSHOW_X|vdrawSHOW_Y)
#define vdrawSizedRectShowCenter(s, n, r) \
    _vdrawSizedRectShow(s, n, r, vdrawSHOW_X|vdrawSHOW_Y)
#define vdrawScribedRectShowCenter(s, r) \
    _vdrawScribedRectShow(s, r, vdrawSHOW_X|vdrawSHOW_Y)

#define vdrawUnderline(s) \
    _vdrawSizedUnderlineShow(s, vcharLength(s), FALSE)
#define vdrawSizedUnderline(s, n)   _vdrawSizedUnderlineShow(s, n, FALSE)
#define vdrawScribedUnderline(s) \
    _vdrawScribedUnderlineShow(s, FALSE)
#define vdrawUnderlineShow(s) \
    _vdrawSizedUnderlineShow(s, vcharLength(s), TRUE)
#define vdrawSizedUnderlineShow(s, n) _vdrawSizedUnderlineShow(s, n, TRUE)
#define vdrawScribedUnderlineShow(s) \
    _vdrawScribedUnderlineShow(s, TRUE)

#define vdrawRectImage(i, s, d) \
    _vdrawRectImage(i, s, d, _vdrawImage)
#define vdrawRectImageMask(i, s, d) \
    _vdrawRectImage(i, s, d, _vdrawImageMask)
#define vdrawRectImageComposite(i, s, d) \
    _vdrawRectImage(i, s, d, vdrawImageComposite)
#define vdrawRectImageIdent(i, s) \
    _vdrawRectImageIdent(i, s, _vdrawImageIdent)
#define vdrawRectImageMaskIdent(i, s) \
    _vdrawRectImageIdent(i, s, _vdrawImageMaskIdent)
#define vdrawRectImageCompositeIdent(i, s) \
    _vdrawRectImageIdent(i, s, vdrawImageCompositeIdent)

vportEND_CPLUSPLUS_EXTERN_C

#endif /* #ifndef vdrawINCLUDED */


/* $Id: vdrawpen.h,v 1.7 1997/09/11 22:51:29 robert Exp $ */

/*
 * vdrawpen.h
 *
 * C Interface file for the Draw Pen object
 *
 * (c) Copyright Visix Software, Inc.
 * All rights reserved
 */

#ifndef vdrawpenINCLUDED
#define vdrawpenINCLUDED

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

typedef struct vdrawpen vdrawpen;
typedef struct vdrawpenClass vdrawpenClass;

/*
 * PUBLIC CONSTANT DECLARATIONS
 */

/*
 * PUBLIC FUNCTION DECLARATIONS
 */

void vdrawpenStartup(
    void
    );

/*
 * Drawing Pen Functions
 */

vdrawpenClass *vdrawpenGetDefaultClass(
    void
    );

vdrawpenClass *vdrawpenGetClass(
    vdrawpen *pen
    );

vloadable *vdrawpenGetLoadable(
    vdrawpen *pen
    );

vinstance *vdrawpenGetInstance(
    vdrawpen *pen
    );

vdrawpen *vdrawpenCreate(
    void
    );

vdrawpen *vdrawpenCreateOfClass(
    vdrawpenClass *clas
    );

vdrawpen *vdrawpenClone(
    vdrawpen *pen
    );

void vdrawpenInit(
    vdrawpen *pen
    );

void vdrawpenInitOfClass(
    vdrawpen *pen,
    vdrawpenClass *clas
    );

void vdrawpenDestroy(
    vdrawpen *pen
    );

void vdrawpenCopy(
    vdrawpen *pen,
    vdrawpen *target
    );

void vdrawpenCopyInit(
    vdrawpen *pen,
    vdrawpen *target
    );

vcolor *vdrawpenGetColor(
    vdrawpen *pen
    );

vcolor *vdrawpenGetComplementColor(
    vdrawpen *pen
    );

vfont *vdrawpenGetFont(
    vdrawpen *pen
    );

float *vdrawpenGetDashPattern(
    vdrawpen *pen,
    size_t *size
    );

double vdrawpenGetDashOffset(
    vdrawpen *pen
    );

int vdrawpenGetDrawingFunction(
    vdrawpen *pen
    );

double vdrawpenGetGray(
    vdrawpen *pen
    );

int vdrawpenGetLineCapStyle(
    vdrawpen *pen
    );

int vdrawpenGetLineJoinStyle(
    vdrawpen *pen
    );

double vdrawpenGetLineWidth(
    vdrawpen *pen
    );

double vdrawpenGetLineJoinMiterLimit(
    vdrawpen *pen
    );

void vdrawpenGetPhase(
    vdrawpen *pen,
    int *x,
    int *y
    );

void vdrawpenSetColor(
    vdrawpen *pen,
    vcolor *color
    );

void vdrawpenSetColorSpec(
    vdrawpen *pen,
    vcolorSpec *spec
    );

void vdrawpenSetComplementColor(
    vdrawpen *pen,
    vcolor *complement
    );

void vdrawpenSetComplementColorSpec(
    vdrawpen *pen,
    vcolorSpec *spec
    );

void vdrawpenSetDashPattern(
    vdrawpen *pen,
    float *pattern,
    size_t size,
    double offset
    );

void vdrawpenSetDashPatternOwned(
    vdrawpen *pen,
    float *pattern,
    size_t size,
    double offset
    );

void vdrawpenSetFont(
    vdrawpen *pen,
    vfont *font
    );

void vdrawpenSetDrawingFunction(
    vdrawpen *pen,
    int function
    );

void vdrawpenSetLineCapStyle(
    vdrawpen *pen,
    int capStyle
    );

void vdrawpenSetLineJoinStyle(
    vdrawpen *pen,
    int joinStyle
    );

void vdrawpenSetLineWidth(
    vdrawpen *pen,
    double width
    );

void vdrawpenSetLineJoinMiterLimit(
    vdrawpen *pen,
    double limit
    );

void vdrawpenSetPhase(
    vdrawpen *pen,
    int x,
    int y
    );

void vdrawpenSetOwner(
    vdrawpen *pen,
    void * /* vdrawcontext * */owner 
    );
			     
/*
 * CLASS DECLARATIONS
 */

#define vdrawpenCLASS(CLASS, PEN)                                             \
  vloadableCLASS(CLASS, PEN)
  
/*
 * PRIVATE TYPE DECLARATIONS
 */

struct vdrawpen {
  vloadable super;
  unsigned long flags;
  double lineWidth;
  vcolor *color;
  vcolor *complement;
  float *dashPattern;
  size_t dashSize;
  double dashOffset;
  double miterLimit;
  int phaseX, phaseY;
  vfont *font;
  void *owner;
};

struct vdrawpenClass {
  vdrawpenCLASS(vdrawpenClass, vdrawpen);
};

/*
 * PRIVATE CONSTANT DECLARATION
 */

enum {
  _vdrawpenDASH_PATTERN_OWNED        = 0x40000000
};

/*
 * PRIVATE FUNCTION DECLARATION
 */

void _vdrawpenSetDashPatternOwned(vdrawpen *pen, float *pattern, size_t size,
				  double offset, vbool owned);

/*
 * FUNCTIONS IMPLEMENTED AS MACROS
 */

#define vdrawpenGetLoadable(c) vportBASE_OBJECT((c), super)
#define vdrawpenGetInstance(c)                                                \
  vloadableGetInstance(vdrawpenGetLoadable((c)))
#define vdrawpenGetClass(c)                                                   \
  (vdrawpenClass *)vloadableGetClass(vdrawpenGetLoadable((c)))
#define vdrawpenCreateOfClass(c)                                              \
  (vdrawpen *)vloadableCreateOfClass((vloadableClass *)(c))
#define vdrawpenCreate()                                                      \
  vdrawpenCreateOfClass(vdrawpenGetDefaultClass())
#define vdrawpenInitOfClass(i,c)                                              \
  vloadableInitOfClass(vdrawpenGetLoadable((i)), (vloadableClass *)(c))
#define vdrawpenInit(i)                                                       \
  vdrawpenInitOfClass((i), vdrawpenGetDefaultClass())
#define vdrawpenDestroy(c) vloadableDestroy(vdrawpenGetLoadable((c)))
#define vdrawpenClone(c)                                                      \
  (vdrawpen *)vloadableCloneOfSubclass(vdrawpenGetLoadable(c),                \
                                   (vloadableClass *)vdrawpenGetDefaultClass())
#define vdrawpenCopy(c,t)                                                     \
  vloadableCopy(vdrawpenGetLoadable((c)), vdrawpenGetLoadable((t)))
#define vdrawpenCopyInit(c, t)                                                \
  vloadableCopyInitOfSubclass(vdrawpenGetLoadable((c)),                       \
			      vdrawpenGetLoadable((t)),                       \
			      vdrawpenGetDefaultClass())

#define vdrawpenGetColor(p) ((p)->color) 

#define vdrawpenGetComplementColor(p) ((p)->complement)

#define vdrawpenGetFont(p) ((p)->font)

#define vdrawpenGetDashOffset(p) ((p)->dashOffset)

#define vdrawpenGetDrawingFunction(p) ((p)->flags & _vdrawFUNC_MASK)

#define vdrawpenGetLineCapStyle(p) ((p)->flags & _vdrawCAP_MASK)

#define vdrawpenGetLineJoinStyle(p) ((p)->flags & _vdrawJOIN_MASK)

#define vdrawpenGetLineWidth(p) ((p)->lineWidth)

#define vdrawpenGetLineJoinMiterLimit(p) ((p)->miterLimit)

#define vdrawpenSetColorSpec(p,s) \
    vdrawpenSetColor(p,vcolorInternSpec(s))

#define vdrawpenSetComplementColorSpec(p,s) \
    vdrawpenSetComplementColor(p,vcolorInternSpec(s))

#define vdrawpenSetDashPattern(p,a,s,o)                                       \
    _vdrawpenSetDashPatternOwned((p),(a),(s),(o), vFALSE)

#define vdrawpenSetDashPatternOwned(p,a,s,o)                                  \
    _vdrawpenSetDashPatternOwned((p),(a),(s),(o), vTRUE)

vportEND_CPLUSPLUS_EXTERN_C

#endif

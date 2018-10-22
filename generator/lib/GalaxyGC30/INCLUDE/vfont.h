/* $Id: vfont.h,v 1.46 1996/10/25 22:47:44 jim Exp $ */

/************************************************************

    vfont.h

    C Interface file for the Font Manager

    (c) Copyright Visix Software Inc.
    All rights reserved

************************************************************/

#ifndef vfontINCLUDED
#define vfontINCLUDED

#ifndef  vportINCLUDED
#include <vport.h>
#endif

#ifndef  vmathINCLUDED
#include vmathHEADER
#endif

#ifndef  vdebugINCLUDED
#include vdebugHEADER
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

#ifndef  vmatrixINCLUDED
#include vmatrixHEADER
#endif

#ifndef  vfsINCLUDED
#include vfsHEADER
#endif

#ifndef  vresourceINCLUDED
#include vresourceHEADER
#endif

#ifndef  vinstanceINCLUDED
#include vinstanceHEADER
#endif


vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * * * * * * * * * * PUBLIC CONSTANT DEFINITIONS * * * * * * * * * *
 */

#define vfontDEFAULT_SIZE           12

/*
 * * * * * * * * * * PUBLIC TYPE DEFINITIONS * * * * * * * * * *
 */

typedef struct vfontFamily          vfontFamily;
typedef struct vfontFace            vfontFace;
typedef struct vfont                vfont;
typedef struct vfontMetricsFuncs    vfontMetricsFuncs;

typedef struct vfontFamilyClass     vfontFamilyClass;
typedef struct vfontFaceClass       vfontFaceClass;
typedef struct vfontClass           vfontClass;

typedef void (*vfontStartupProc)(
    void
    );

struct vfontMetricsFuncs {
    unsigned int flags;
    void   (*Width)(vfont *font, vfixed *dx, vfixed *dy);
    void   (*Bounds)(vfont *font, vrectFixed *bounds);
    vfixed (*Ascent)(vfont *font);
    vfixed (*Descent)(vfont *font);
    void   (*StringWidth)(vfont *font, const vchar *s, size_t count, 
			  vfixed *dx, vfixed *dy);
    void   (*StringBounds)(vfont *font, const vchar *s, size_t count, 
			   vrectFixed *bounds);
};

/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */

void vfontRegisterStartup(
    vfontStartupProc		  startup
    );

int vfontRegisterDevice(
    void
    );

void vfontRegisterDefault(
    const vchar                    *defaultKey
    );

void vfontRegisterMetrics(
    const vfontMetricsFuncs        *metrics
    );

/* vfontFamily routines */

vfontFamilyClass *vfontGetDefaultFamilyClass(
    void
    );

vfontFamilyClass *vfontGetFamilyClass(
    vfontFamily			   *family
    );

vinstance *vfontGetFamilyInstance(
    vfontFamily			   *family
    );

vfontFamily *vfontCreateFamily(
    const vname                    *name,
    const vname                    *foundry,
    const vname                    *encoding,
    int                             mono,
    int                             id
    );

int vfontGetFamilyCount(
    void
    );

vfontFamily *vfontGetFamilyAt(
    int                             index
    );

void vfontDumpFamily(
    vfontFamily                    *family,
    FILE                           *stream
    );

void vfontSetFamilyInfo(
    vfontFamily                    *family,
    int                             id,
    const void                     *info
    );

const vname *vfontGetFamilyName(
    vfontFamily                    *family
    );

const vname *vfontGetFamilyFoundry(
    vfontFamily                    *family
    );

const vname *vfontGetFamilyEncoding(
    vfontFamily                    *family
    );

int vfontFamilyIsMono(
    vfontFamily                    *family
    );

int vfontGetFamilyFaceCount(
    vfontFamily                    *family
    );

vfontFace *vfontGetFamilyFaceAt(
    vfontFamily                    *family,
    int                             index
    );

int vfontFamilyIsAvailOn(
    vfontFamily                    *family,
    int                             id
    );

const void *vfontGetFamilyInfo(
    vfontFamily                    *family,
    int                             id
    );

/* vfontFace routines */

vfontFaceClass *vfontGetDefaultFaceClass(
    void
    );

vfontFaceClass *vfontGetFaceClass(
    vfontFace			   *face
    );

vinstance *vfontGetFaceInstance(
    vfontFace			   *face
    );

vfontFace *vfontCreateFace(
    vfontFamily                    *family,
    const vname                    *name,
    int                             id
    );

int vfontGetFaceCount(
    void
    );

vfontFace *vfontGetFaceAt(
    int                             index
    );

void vfontDumpFace(
    vfontFace                      *face,
    FILE                           *stream
    );

void vfontSetFaceInfo(
    vfontFace                      *face,
    int                             id,
    const void                     *info
    );

const vname *vfontGetFaceName(
    vfontFace                      *face
    );

int vfontGetFaceFontCount(
    vfontFace                      *face
    );

vfont *vfontGetFaceFontAt(
    vfontFace                      *face,
    int                             index
    );

vfontFamily *vfontGetFaceFamily(
    vfontFace                      *face
    );

int vfontFaceIsAvailOn(
    vfontFace                      *face,
    int                             id
    );

const void *vfontGetFaceInfo(
    vfontFace                      *face,
    int                             id
    );

/* vfont routines */

vfontClass *vfontGetDefaultClass(
    void
    );

vfontClass *vfontGetClass(
    vfont			   *font
    );

vinstance *vfontGetInstance(
    vfont			   *font
    );

vfont *vfontCreate(
    vfontFace                      *face,
    const vmatrix                  *mtx,
    int                             id
    );

vfont *vfontMake(
    vfontFace                      *face,
    const vmatrix                  *mtx
    );

vfont *vfontScale(
    vfontFace                      *face,
    int                             size
    );

vfont *vfontFScale(
    vfontFace                      *face,
    double                          size
    );

vfont *vfontMatch(
    vfontFace                      *face,
    const vmatrix                  *mtx,
    int                             id
    );

vfont *vfontLoad(
    vresource                       resource
    );

void vfontStore(
    vfont                          *font,
    vresource                       resource
    );

void vfontDump(
    vfont                          *font,
    FILE                           *stream
    );

void vfontSetInfo(
    vfont                          *font,
    int                             id,
    const void                     *info
    );

const vmatrix *vfontGetMatrix(
    vfont                          *font
    );

int vfontGetSize(
    vfont                          *font
    );

double vfontFGetSize(
    vfont                          *font
    );

vfontFace *vfontGetFace(
    vfont                          *font
    );

const vname *vfontGetName(
    vfont                          *font
    );

const vname *vfontGetKey(
    vfont                          *font
    );

int vfontIsSquare(
    vfont                          *font
    );

int vfontIsUpright(
    vfont                          *font
    );

int vfontIsAvailOn(
    vfont                          *font,
    int                             id
    );

const void *vfontGetInfo(
    vfont                          *font,
    int                             id
    );

vscribe *vfontScribeEscapeString(
    const vchar                   *value
    );

vfont *vfontFind(
    const vchar                    *key
    );

vfont *vfontFindScribed(
    vscribe                        *key
    );

vfont *vfontFindRelative(
    vfont                          *font,
    const vchar                    *key
    );

vfont *vfontFindRelativeScribed(
    vfont                          *font,
    vscribe                        *key
    );

void vfontWidth(
    vfont                          *font,
    int                            *dx,
    int                            *dy
    );

void vfontFixWidth(
    vfont                          *font,
    vfixed                         *dx,
    vfixed                         *dy
    );

int vfontWidthX(
    vfont                          *font
    );

vfixed vfontFixWidthX(
    vfont                          *font
    );

void vfontBounds(
    vfont                          *font,
    vrect                          *bounds
    );

void vfontFixBounds(
    vfont                          *font,
    vrectFixed                     *bounds
    );

int vfontAscent(
    vfont                          *font
    );

vfixed vfontFixAscent(
    vfont                          *font
    );

int vfontDescent(
    vfont                          *font
    );

vfixed vfontFixDescent(
    vfont                          *font
    );

int vfontHeight(
    vfont                          *font
    );

vfixed vfontFixHeight(
    vfont                          *font
    );

void vfontStringWidth(
    vfont                          *font,
    const vchar                    *s,
    int                            *dx,
    int                            *dy
    );

void vfontFixStringWidth(
    vfont                          *font,
    const vchar                    *s,
    vfixed                         *dx,
    vfixed                         *dy
    );

void vfontSizedStringWidth(
    vfont                          *font,
    const vchar                    *s,
    size_t                          count,
    int                            *dx,
    int                            *dy
    );

void vfontFixSizedStringWidth(
    vfont                          *font,
    const vchar                    *s,
    size_t                          count,
    vfixed                         *dx,
    vfixed                         *dy
    );

void vfontScribedStringWidth(
    vfont                          *font,
    vscribe                        *scribe,
    int                            *dx,
    int                            *dy
    );

void vfontFixScribedStringWidth(
    vfont                          *font,
    vscribe                        *scribe,
    vfixed                         *dx,
    vfixed                         *dy
    );

int vfontStringWidthX(
    vfont                          *font,
    const vchar                    *s
    );

vfixed vfontFixStringWidthX(
    vfont                          *font,
    const vchar                    *s
    );

int vfontSizedStringWidthX(
    vfont                          *font,
    const vchar                    *s,
    size_t                          count
    );

vfixed vfontFixSizedStringWidthX(
    vfont                          *font,
    const vchar                    *s,
    size_t                          count
    );

int vfontScribedStringWidthX(
    vfont                          *font,
    vscribe                        *scribe
    );

vfixed vfontFixScribedStringWidthX(
    vfont                          *font,
    vscribe                        *scribe
    );

void vfontStringBounds(
    vfont                          *font,
    const vchar                    *s,
    vrect                          *bounds
    );

void vfontFixStringBounds(
    vfont                          *font,
    const vchar                    *s,
    vrectFixed                     *bounds
    );

void vfontSizedStringBounds(
    vfont                          *font,
    const vchar                    *s,
    size_t                          count,
    vrect                          *bounds
    );

void vfontFixSizedStringBounds(
    vfont                          *font,
    const vchar                    *s,
    size_t                          count,
    vrectFixed                     *bounds
    );

void vfontScribedStringBounds(
    vfont                          *font,
    vscribe                        *scribe,
    vrect                          *bounds
    );

void vfontFixScribedStringBounds(
    vfont                          *font,
    vscribe                        *scribe,
    vrectFixed                     *bounds
    );

/*
 * * * * * * * * * * PRIVATE CONSTANT DEFINITIONS * * * * * * * * * *
 */

enum {
    _vfontFAMILY_SORTED             = 0x0001,
    _vfontFAMILY_MONO               = 0x0002
};

enum {
    _vfontFACE_SORTED               = 0x0001
};

enum {
    _vfontSQUARE                    = 0x0001,
    _vfontUPRIGHT                   = 0x0002
};

/*
 * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * *
 */

typedef unsigned long               _vfontDeviceFlags;

typedef struct _vfontFaceComponents _vfontFaceComponents;

struct vfontFamily {
    vinstance			    super;

    const vname                    *name;
    const vname                    *foundry;
    const vname                    *encoding;
    unsigned short                  flags;
    vfontFace                     **faces, **faceNext, **faceMax;
    _vfontDeviceFlags               availFlags;
    const void                    **info;
    const vname                    *lname;
};

#define vfontFAMILY_CLASS(CLASS, FAMILY)				\
    vinstanceCLASS(CLASS, FAMILY)

struct vfontFamilyClass
{
  vfontFAMILY_CLASS(vfontFamilyClass, vfontFamily);
};


struct vfontFace {
    vinstance			    super;

    const vname                    *name;
    vfontFamily                    *family;
    const _vfontFaceComponents     *components;
    unsigned short                  flags;
    vfont                         **fonts, **fontNext, **fontMax;
    _vfontDeviceFlags               availFlags;
    const void                    **info;
};

#define vfontFACE_CLASS(CLASS, FACE)				\
    vinstanceCLASS(CLASS, FACE)

struct vfontFaceClass
{
  vfontFACE_CLASS(vfontFaceClass, vfontFace);
};


struct vfont {
    vinstance			    super;

    const vmatrix                  *mtx;
    vfontFace                      *face;
    const vname                    *name;
    const vname                    *key;
    unsigned short                  flags;
    _vfontDeviceFlags               availFlags;
    const void                    **info;
};

#define vfontCLASS(CLASS, FONT)						\
    vinstanceCLASS(CLASS, FONT)

struct vfontClass
{
  vfontCLASS(vfontClass, vfont);
};

/*
 * * * * * * * * * * PRIVATE VARIABLE DECLARATIONS * * * * * * * * * *
 */

extern vportLINK vfontMetricsFuncs            _vfontMetrics;

/*
 * * * * * * * * * * PRIVATE FUNCTION PROTOTYPES * * * * * * * * * *
 */

void _vfontDummyWidth(
    vfont                          *font,
    vfixed                         *dx,
    vfixed                         *dy
    );

void _vfontDummyBounds(
    vfont                          *font,
    vrectFixed                     *bounds
    );

vfixed _vfontDummyHeight(
    vfont                          *font
    );

void _vfontDummyStringWidth(
    vfont                          *font,
    const vchar                    *s,
    size_t                          count,
    vfixed                         *dx,
    vfixed                         *dy
    );

void _vfontDummyStringBounds(
    vfont                          *font,
    const vchar                    *s,
    size_t                          count,
    vrectFixed                     *bounds
    );
    
/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * *
 */

#define vfontGetFamilyInstance(f)	vportBASE_OBJECT(f, super)
#define vfontGetFamilyClass(f) \
    ((vfontFamilyClass *) vinstanceGetClass(vfontGetFamilyInstance(f)))

#define vfontGetFamilyName(f)     ((f)->name)
#define vfontGetFamilyFoundry(f)  ((f)->foundry)
#define vfontGetFamilyEncoding(f) ((f)->encoding)
#define vfontFamilyIsMono(f)     (((f)->flags&_vfontFAMILY_MONO)!=0)

#if (!vdebugDEBUG)
#define vfontGetFamilyFaceAt(f, i)  ((f)->faces[i])
#define vfontFamilyIsAvailOn(f, i) (((f)->availFlags>>(i))&1)
#define vfontGetFamilyInfo(f, i)    ((f)->info[i])
#endif

#define vfontGetFaceInstance(f)		vportBASE_OBJECT(f, super)
#define vfontGetFaceClass(f) \
    ((vfontFaceClass *) vinstanceGetClass(vfontGetFaceInstance(f)))

#define vfontGetFaceName(f)       ((f)->name)
#define vfontGetFaceFamily(f)     ((f)->family)

#if (!vdebugDEBUG)
#define vfontGetFaceFontAt(f, i)  ((f)->fonts[i])
#define vfontFaceIsAvailOn(f, i) (((f)->availFlags>>(i))&1)
#define vfontGetFaceInfo(f, i)    ((f)->info[i])
#endif

#define vfontGetInstance(f)		vportBASE_OBJECT(f, super)
#define vfontGetClass(f) \
    ((vfontClass *) vinstanceGetClass(vfontGetInstance(f)))

#define vfontMake(f, m)             vfontCreate(f, m, -1)
#define vfontScale(f, n)            vfontFScale(f, (double)(n))
#define vfontGetMatrix(f)         ((f)->mtx)
#define vfontGetSize(f)           ((int)vmathRound((double)(f)->mtx->d))
#define vfontFGetSize(f)          ((double)(f)->mtx->d)
#define vfontGetFace(f)           ((f)->face)
#define vfontIsSquare(f)         (((f)->flags&_vfontSQUARE)!=0)
#define vfontIsUpright(f)        (((f)->flags&_vfontUPRIGHT)!=0)
#define vfontFind(s)                vfontFindScribed(vcharScribe(s))
#define vfontFindRelative(f, s)     vfontFindRelativeScribed(f, vcharScribe(s))

#if (!vdebugDEBUG)
#define vfontIsAvailOn(f, i)     (((f)->availFlags>>(i))&1)
#define vfontGetInfo(f, i)        ((f)->info[i])
#endif

#define vfontFixWidth(f, dx, dy) ((*_vfontMetrics.Width)(f, dx, dy))
#define vfontWidthX(f)              vfixedToInt(vfixedRound(vfontFixWidthX(f)))
#define vfontFixBounds(f, r)     ((*_vfontMetrics.Bounds)(f, r))
#define vfontAscent(f) \
    vfixedToInt(vfixedRound((*_vfontMetrics.Ascent)(f)))
#define vfontFixAscent(f)        ((*_vfontMetrics.Ascent)(f))
#define vfontDescent(f) \
    vfixedToInt(vfixedRound((*_vfontMetrics.Descent)(f)))
#define vfontFixDescent(f)       ((*_vfontMetrics.Descent)(f))
#define vfontHeight(f)              vfixedToInt(vfixedRound(vfontFixHeight(f)))

#define vfontStringWidth(f, s, dx, dy) \
    vfontSizedStringWidth(f, s, vcharLength(s), dx, dy)
#define vfontFixStringWidth(f, s, dx, dy) \
    ((*_vfontMetrics.StringWidth)(f, s, vcharLength(s), dx, dy))
#define vfontFixSizedStringWidth(f, s, n, dx, dy) \
    ((*_vfontMetrics.StringWidth)(f, s, n, dx, dy))

#define vfontStringWidthX(f, s) \
    vfixedToInt(vfixedRound(vfontFixSizedStringWidthX(f, s, vcharLength(s))))
#define vfontFixStringWidthX(f, s) \
    vfontFixSizedStringWidthX(f, s, vcharLength(s))
#define vfontSizedStringWidthX(f, s, n) \
    vfixedToInt(vfixedRound(vfontFixSizedStringWidthX(f, s, n)))
#define vfontScribedStringWidthX(f, s) \
    vfixedToInt(vfixedRound(vfontFixScribedStringWidthX(f, s)))

#define vfontStringBounds(f, s, r) \
    vfontSizedStringBounds(f, s, vcharLength(s), r)
#define vfontFixStringBounds(f, s, r) \
    ((*_vfontMetrics.StringBounds)(f, s, vcharLength(s), r))
#define vfontFixSizedStringBounds(f, s, n, r) \
    ((*_vfontMetrics.StringBounds)(f, s, n, r))

vportEND_CPLUSPLUS_EXTERN_C

#endif /* #ifndef vfontINCLUDED */


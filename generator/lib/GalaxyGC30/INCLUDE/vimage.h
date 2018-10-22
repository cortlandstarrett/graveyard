/* $Id: vimage.h,v 1.32 1996/06/05 00:16:47 sean Exp $ */

/************************************************************

    vimage.h

    C Interface file for the Image Manager

    (c) Copyright Visix Software Inc.
    All rights reserved

************************************************************/

#ifndef vimageINCLUDED
#define vimageINCLUDED

#ifndef  vportINCLUDED
#include <vport.h>
#endif

#ifndef  vstdioINCLUDED
#include vstdioHEADER
#endif

#ifndef  vbufferINCLUDED
#include vbufferHEADER
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

vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * * * * * * * * * * PUBLIC TYPE DEFINITIONS * * * * * * * * * *
 */

typedef vpixmapValue                vimageValue;
typedef vpixmapDimension            vimageDimension;

typedef struct vimage               vimage;
typedef struct vimageClass          vimageClass;

/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */

void vimageStartup(void);


/*
 * images
 */

vimageClass *vimageGetDefaultClass(
    void
    );

vimage *vimageCreateOfClass(
    vimageClass                    *clas
    );

vimage *vimageCreate(
    void
    );

vimage *vimageCreateSpecific(
    int                             w,
    int                             h,
    int                             numColors
    );

vimage *vimageClone(
    vimage                         *image
    );

void vimageInitOfClass(
    vimage                         *image,
    vimageClass                    *clas
    );

void vimageInit(
    vimage                         *image
    );

void vimageInitSpecific(
    vimage                         *image,
    int                             w,
    int                             h,
    int                             numColors
    );

void vimageDestroy(
    vimage                         *image
    );

void vimageCopy(
    vimage                         *image,
    vimage                         *target
    );

void vimageCopyInit(
    vimage                         *image,
    vimage                         *target
    );

vimage *vimageLoad(
    vresource                       resource
    );

void vimageLoadInit(
    vimage                         *image,
    vresource                       resource
    );

void vimageStore(
    vimage                         *image,
    vresource                       resource
    );

void vimageDump(
    vimage                         *image,
    FILE                           *stream
    );

void vimageMarkModified(
    vimage                         *image
    );

vbuffer *vimageMakeBuffer(
    vimage                         *image,
    const vbufferDevice            *device
    );

void vimageSetSize(
    vimage                         *image,
    int                             w,
    int                             h
    );

void vimageSetSizePreserve(
    vimage                         *image,
    int                             w,
    int                             h,
    int                             preserve,
    vimageValue                     background
    );

void vimageSetDepth(
    vimage                         *image,
    int                             depth
    );

void vimageSetNumColors(
    vimage                         *image,
    int                             numColors
    );

void vimageSetPalette(
    vimage                         *image,
    vcolorPalette                  *palette
    );

void vimageSetPaletteOwned(
    vimage                         *image,
    vcolorPalette                  *palette
    );

void vimageSetTransparency(
    vimage                         *image,
    vimage                         *transparency
    );

void vimageSetTransparencyOwned(
    vimage                         *image,
    vimage                         *transparency
    );

void vimageSetNeverDitherFlag(
    vimage                         *image,
    int /* vbool */		    value
    );

void vimageSetNeverDitherFlagOn(
    vimage                         *image
    );

void vimageSetNeverDitherFlagOff(
    vimage                         *image
    );

void vimageSetTrueColor(
    vimage			   *image,
    int				    flag
    );

vpixmap *vimageGetPixmap(
    vimage                         *image
    );

vobject *vimageGetObject(
    vimage                        *image
    );

vobservable *vimageGetObservable(
    vimage                        *image
    );

vloadable *vimageGetLoadable(
    vimage                        *image
    );

vinstance *vimageGetInstance(
    vimage                        *image
    );

vpixmap *vimageGetMap(
    vimage                         *image
    );

vimageClass *vimageGetClass(
    vimage                         *image
    );

int vimageGetWidth(
    vimage                         *image
    );

int vimageGetHeight(
    vimage                         *image
    );

int vimageGetDepth(
    vimage                         *image
    );

int vimageGetNumColors(
    vimage                         *image
    );

vcolorPalette *vimageGetPalette(
    vimage                         *image
    );

int vimageHasPalette(
    vimage                         *image
    );

vimage *vimageGetTransparency(
    vimage                         *image
    );

int vimageIsNeverDitherFlagOn(
    vimage                         *image
    );

int vimageIsTrueColor(
    vimage                         *image
    );

const void *vimageGetData(
    vimage                         *image
    );

void vimageSetData(
    vimage                         *image,
    const void                     *data
    );

vimageValue vimagePackValue24(
    unsigned int                    red,
    unsigned int                    green,
    unsigned int                    blue
    );

void vimageUnpackValue24(
    vimageValue                     value,
    unsigned int                   *red,
    unsigned int                   *green,
    unsigned int                   *blue
    );

void vimageUnpackValue24Quick(
    vimageValue                     value,
    unsigned int                   *red,
    unsigned int                   *green,
    unsigned int                   *blue
    );

/*
 * deprecated images
 */

int vimageAppendPaletteEntry(
    vimage                         *image
    );

void vimageDeletePaletteEntry(
    vimage                         *image,
    int                             index
    );

void vimageCompactPalette(
    vimage                         *image
    );

/*
 * * * * * * * * * * PRIVATE CONSTANT DEFINITIONS * * * * * * * * * *
 */

enum {
    _vimageNEVER_DITHER             = 0x0001,
    _vimageTRUE_COLOR		    = 0x0002,
    _vimageOWN_PALETTE              = 0x0004,
    _vimageOWN_TRANSPARENCY         = 0x0008
};

/*
 * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * *
 */

struct vimage {
    vpixmap                         pixmap;
    unsigned long                   numColors;
    vcolorPalette                  *palette;
    vimage                         *transparency;
    unsigned short                  flags;
};

#define vimageCLASS(SUPER, IMAGE)                                             \
    vpixmapCLASS(SUPER, IMAGE);                                               \
    vclassMETHOD(vimageSET_NUM_COLORS, (IMAGE *image, int numColors));        \
    vclassMETHOD(vimageSET_PALETTE, (IMAGE *image, vcolorPalette *palette));  \
    vclassMETHOD(vimageSET_TRANSPARENCY,                                      \
		 (IMAGE *image, vimage *transparency));                       \
    vclassMETHOD(vimageSET_NEVER_DITHER_FLAG, (IMAGE *image, int flag));      \
    vclassMETHOD(vimageSET_TRUE_COLOR, (IMAGE *image, int flag))

struct vimageClass {
    vimageCLASS(vimageClass, vimage);
};

/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * *
 */

/*
 * images
 */

#define vimageGetPixmap(i)          vportBASE_OBJECT(i, pixmap)
#define vimageGetObject(c)	    vpixmapGetObject(vimageGetPixmap(c))
#define vimageGetObservable(c)	    vobjectGetObservable(vimageGetObject(c))
#define vimageGetLoadable(c)	    vobservableGetLoadable(vimageGetObservable(c))
#define vimageGetInstance(c)	    vloadableGetInstance(vimageGetLoadable(c))

#define vimageCreateOfClass(c) \
    ((vimage*)vpixmapCreateOfClass((vpixmapClass*)(c)))
#define vimageCreate() \
    vimageCreateOfClass(vimageGetDefaultClass())
#define vimageInitOfClass(i, c) \
    vpixmapInitOfClass(vimageGetPixmap(i), (vpixmapClass*)(c))
#define vimageInit(i) \
    vimageInitOfClass(i, vimageGetDefaultClass())
#define vimageDestroy(i) \
    vpixmapDestroy(vimageGetPixmap(i))

#define vimageClone(i) \
    ((vimage *) \
     vloadableCloneOfSubclass(vimageGetLoadable(i), \
			      (vloadableClass*) vimageGetDefaultClass()))
#define vimageCopyInit(i,t) \
    vloadableCopyInitOfSubclass(vimageGetLoadable(i), vimageGetLoadable(t), \
				(vloadableClass*) vimageGetDefaultClass())
#define vimageLoad(r) \
    ((vimage *) \
     vloadableLoadOfSubclass(r, (vloadableClass*) vimageGetDefaultClass()))
#define vimageLoadInit(i, r) \
     vloadableLoadInitOfSubclass(vimageGetLoadable(i), (r), \
				 (vloadableClass*) vimageGetDefaultClass())

#define vimageGetData(i)    vpixmapGetData(vimageGetPixmap(i))
#define vimageSetData(i, d) vpixmapSetData(vimageGetPixmap(i), (d))

#define vimageSetNeverDitherFlagOn(i)  vimageSetNeverDitherFlag(i, TRUE)
#define vimageSetNeverDitherFlagOff(i) vimageSetNeverDitherFlag(i, FALSE)

#define vimageGetMap(i)                 vimageGetPixmap(i)
#define vimageGetClass(i) \
    ((vimageClass*)vpixmapGetClass(vimageGetPixmap(i)))
#define vimageGetWidth(i)               vpixmapGetWidth(vimageGetPixmap(i))
#define vimageGetHeight(i)              vpixmapGetHeight(vimageGetPixmap(i))
#define vimageGetDepth(i)	        vpixmapGetDepth(vimageGetPixmap(i))
#define vimageGetNumColors(i)         ((int)(i)->numColors)
#define vimageHasPalette(i)           ((i)->palette!=NULL)
#define vimageGetTransparency(i)      ((i)->transparency)
#define vimageIsNeverDitherFlagOn(i) (((i)->flags&_vimageNEVER_DITHER)!=0)
#define vimageIsTrueColor(i)         (((i)->flags&_vimageTRUE_COLOR)!=0)

#if (vcolorSIGNIFICANT_BITS<24)
#define _vimagePACK24_RED(v)   (((v)<<(24-vcolorSIGNIFICANT_BITS))&0xFF0000)
#define _vimageUNPACK24_RED(v) (((v)&0xFF0000)>>(24-vcolorSIGNIFICANT_BITS))
#else
#define _vimagePACK24_RED(v)   (((v)>>(vcolorSIGNIFICANT_BITS-24))&0xFF0000)
#define _vimageUNPACK24_RED(v) (((v)&0xFF0000)<<(vcolorSIGNIFICANT_BITS-24))
#endif

#if (vcolorSIGNIFICANT_BITS<16)
#define _vimagePACK24_GREEN(v)   (((v)<<(16-vcolorSIGNIFICANT_BITS))&0xFF00)
#define _vimageUNPACK24_GREEN(v) (((v)&0xFF00)>>(16-vcolorSIGNIFICANT_BITS))
#else
#define _vimagePACK24_GREEN(v)   (((v)>>(vcolorSIGNIFICANT_BITS-16))&0xFF00)
#define _vimageUNPACK24_GREEN(v) (((v)&0xFF00)<<(vcolorSIGNIFICANT_BITS-16))
#endif

#if (vcolorSIGNIFICANT_BITS<8)
#define _vimagePACK24_BLUE(v)   (((v)<<(8-vcolorSIGNIFICANT_BITS))&0xFF)
#define _vimageUNPACK24_BLUE(v) (((v)&0xFF)>>(8-vcolorSIGNIFICANT_BITS))
#else
#define _vimagePACK24_BLUE(v)   (((v)>>(vcolorSIGNIFICANT_BITS-8))&0xFF)
#define _vimageUNPACK24_BLUE(v) (((v)&0xFF)<<(vcolorSIGNIFICANT_BITS-8))
#endif

#define vimagePackValue24(r, g, b) (_vimagePACK24_RED((vimageValue)(r))| \
				    _vimagePACK24_GREEN((vimageValue)(g))| \
				    _vimagePACK24_BLUE((vimageValue)(b)))
#define vimageUnpackValue24Quick(v, r, g, b) \
    (void)(*(r) = (unsigned int) _vimageUNPACK24_RED(v), \
	   *(g) = (unsigned int) _vimageUNPACK24_GREEN(v), \
	   *(b) = (unsigned int) _vimageUNPACK24_BLUE(v))

/*
 * deprecated images
 */

#define vimageCompactPalette(i)

/*
 * * * * * * * * * * PRIVATE FUNCTION MESSAGE DEFINITIONS * * * * * * * * * *
 */

#define vimageCopy(i, t) \
    vclassSend(vimageGetClass(i), vobjectCOPY, (i, t))
#define vimageStore(i, r) \
    vclassSend(vimageGetClass(i), vobjectSTORE, (i, r))
#define vimageDump(i, s) \
    vclassSend(vimageGetClass(i), vobjectDUMP, (i, s))
#define vimageMarkModified(i) \
    vclassSend(vimageGetClass(i), vpixmapMARK_MODIFIED, (i))
#define vimageMakeBuffer(i, d) \
    vclassSend(vimageGetClass(i), vpixmapMAKE_BUFFER, (i, d))
#define vimageSetSizePreserve(i, w, h, pr, b) \
    vclassSend(vimageGetClass(i), vpixmapSET_SIZE, (i, w, h, pr, b))
#define vimageSetSize(i, w, h) \
    vimageSetSizePreserve(i, w, h, vpixmapPRESERVE_NONE, (vimageValue)0)
#define vimageSetDepth(i, d) \
    vclassSend(vimageGetClass(i), vpixmapSET_DEPTH, (i, d))
#define vimageSetNumColors(i, n) \
    vclassSend(vimageGetClass(i), vimageSET_NUM_COLORS, (i, n))
#define vimageSetPalette(i, p) \
    vclassSend(vimageGetClass(i), vimageSET_PALETTE, (i, p))
#define vimageSetTransparency(i, t) \
    vclassSend(vimageGetClass(i), vimageSET_TRANSPARENCY, (i, t))
#define vimageSetNeverDitherFlag(i, f) \
    vclassSend(vimageGetClass(i), vimageSET_NEVER_DITHER_FLAG, (i, f))
#define vimageSetTrueColor(i, f) \
    vclassSend(vimageGetClass(i), vimageSET_TRUE_COLOR, (i, f))

vportEND_CPLUSPLUS_EXTERN_C

#endif /* #ifndef vimageINCLUDED */


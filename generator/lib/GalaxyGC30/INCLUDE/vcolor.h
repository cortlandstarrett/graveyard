/* $Id: vcolor.h,v 1.91 1997/11/13 17:07:06 gregt Exp $ */

/************************************************************
 *
 *    vcolor.h
 *
 *    C Interface file for the Color Manager
 *
 *    (c) Copyright Visix Software Inc.
 *    All rights reserved
 *
 ***********************************************************/

#ifndef vcolorINCLUDED
#define vcolorINCLUDED

#ifndef  vportINCLUDED
#include <vport.h>
#endif

#ifndef  vcharINCLUDED
#include vcharHEADER
#endif

#ifndef  vresourceINCLUDED
#include vresourceHEADER
#endif

#ifndef  vbufferINCLUDED
#include vbufferHEADER
#endif

#ifndef  vloadableINCLUDED
#include vloadableHEADER
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * * * * * * * * * * PUBLIC CONSTANT DEFINITIONS * * * * * * * * * *
 */

/*
 * colors
 */

#define vcolorSIGNIFICANT_BITS      16
#define vcolorCOMPONENT_MIN         0
#define vcolorCOMPONENT_MAX       ((1<<vcolorSIGNIFICANT_BITS)-1)

#define vcolorGRAY_RED              19595    /* 0.299*65535 */
#define vcolorGRAY_GREEN            38469    /* 0.587*65535 */
#define vcolorGRAY_BLUE             7471     /* 0.114*65535 */

#define vcolorDELTA_RGB             _vcolorMODEL_RGB
#define vcolorDELTA_HLS             _vcolorMODEL_HLS
#define vcolorDELTA_CMY             _vcolorMODEL_CMY

#define vcolorDELTA_RGB_DISTANCE   (_vcolorMODEL_RGB|_vcolorDISTANCE)
#define vcolorDELTA_HLS_DISTANCE   (_vcolorMODEL_HLS|_vcolorDISTANCE)
#define vcolorDELTA_CMY_DISTANCE   (_vcolorMODEL_CMY|_vcolorDISTANCE)

/*
 * color schemes
 */

enum {
    vcolorID_DISABLE                = 0x0001,
    _vcolorID_MODIFIERS             = 1
};

enum {
    vcolorID_FOREGROUND             = 0<<_vcolorID_MODIFIERS,
    vcolorID_BACKGROUND             = 1<<_vcolorID_MODIFIERS,
    vcolorID_SHADOW_TOP             = 2<<_vcolorID_MODIFIERS,
    vcolorID_SHADOW_BOTTOM          = 3<<_vcolorID_MODIFIERS,
    vcolorID_FOREGROUND_HILITE      = 4<<_vcolorID_MODIFIERS,
    vcolorID_BACKGROUND_HILITE      = 5<<_vcolorID_MODIFIERS,
    vcolorID_BACKGROUND_EMBOSS      = 6<<_vcolorID_MODIFIERS,
    vcolorID_BACKGROUND_DEBOSS      = 7<<_vcolorID_MODIFIERS,
    vcolorID_BORDER                 = 8<<_vcolorID_MODIFIERS,
    vcolorID_FOCUS                  = 9<<_vcolorID_MODIFIERS,
    vcolorID_SHADOW_TOP_DARK        = 10<<_vcolorID_MODIFIERS,
    vcolorID_SHADOW_BOTTOM_DARK     = 11<<_vcolorID_MODIFIERS,
    vcolorID_MAX                    = 12<<_vcolorID_MODIFIERS
};

enum {
    vcolorFLAG_FOREGROUND           = 1<<vcolorID_FOREGROUND,
    vcolorFLAG_BACKGROUND           = 1<<vcolorID_BACKGROUND,
    vcolorFLAG_SHADOW_TOP           = 1<<vcolorID_SHADOW_TOP,
    vcolorFLAG_SHADOW_BOTTOM        = 1<<vcolorID_SHADOW_BOTTOM,
    vcolorFLAG_FOREGROUND_HILITE    = 1<<vcolorID_FOREGROUND_HILITE,
    vcolorFLAG_BACKGROUND_HILITE    = 1<<vcolorID_BACKGROUND_HILITE,
    vcolorFLAG_BACKGROUND_EMBOSS    = 1<<vcolorID_BACKGROUND_EMBOSS,
    vcolorFLAG_BACKGROUND_DEBOSS    = 1<<vcolorID_BACKGROUND_DEBOSS,
    vcolorFLAG_BORDER               = 1<<vcolorID_BORDER,
    vcolorFLAG_FOCUS                = 1<<vcolorID_FOCUS,
    vcolorFLAG_SHADOW_TOP_DARK      = 1<<vcolorID_SHADOW_TOP_DARK,
    vcolorFLAG_SHADOW_BOTTOM_DARK   = 1<<vcolorID_SHADOW_BOTTOM_DARK,
    vcolorFLAG_ALL                  = (1<<vcolorID_MAX)-1
};

enum {
    vcolorFLAG_DISABLE_FOREGROUND        = 
	1<<(vcolorID_DISABLE|vcolorID_FOREGROUND),
    vcolorFLAG_DISABLE_BACKGROUND        = 
	1<<(vcolorID_DISABLE|vcolorID_BACKGROUND),
    vcolorFLAG_DISABLE_SHADOW_TOP        = 
	1<<(vcolorID_DISABLE|vcolorID_SHADOW_TOP),
    vcolorFLAG_DISABLE_SHADOW_BOTTOM     = 
	1<<(vcolorID_DISABLE|vcolorID_SHADOW_BOTTOM),
    vcolorFLAG_DISABLE_FOREGROUND_HILITE = 
	1<<(vcolorID_DISABLE|vcolorID_FOREGROUND_HILITE),
    vcolorFLAG_DISABLE_BACKGROUND_HILITE = 
	1<<(vcolorID_DISABLE|vcolorID_BACKGROUND_HILITE),
    vcolorFLAG_DISABLE_BACKGROUND_EMBOSS = 
	1<<(vcolorID_DISABLE|vcolorID_BACKGROUND_EMBOSS),
    vcolorFLAG_DISABLE_BACKGROUND_DEBOSS = 
	1<<(vcolorID_DISABLE|vcolorID_BACKGROUND_DEBOSS),
    vcolorFLAG_DISABLE_BORDER            = 
	1<<(vcolorID_DISABLE|vcolorID_BORDER),
    vcolorFLAG_DISABLE_FOCUS             = 
	1<<(vcolorID_DISABLE|vcolorID_FOCUS),
    vcolorFLAG_DISABLE_SHADOW_TOP_DARK   = 
        1<<(vcolorID_DISABLE|vcolorID_SHADOW_TOP_DARK),
    vcolorFLAG_DISABLE_SHADOW_BOTTOM_DARK        = 
        1<<(vcolorID_DISABLE|vcolorID_SHADOW_BOTTOM_DARK),
    vcolorFLAG_ENABLE_ALL                = vcolorFLAG_ALL&0x55555555,
    vcolorFLAG_DISABLE_ALL               = vcolorFLAG_ALL&0xAAAAAAAAu
};

/*
 * * * * * * * * * * PUBLIC TYPE DEFINITIONS * * * * * * * * * *
 */

/*
 * color specs
 */

typedef struct vcolorSpec           vcolorSpec;
typedef struct vcolorSpecClass      vcolorSpecClass;

typedef unsigned short              vcolorComponentValue;
typedef unsigned long               vcolorMappedValue;

typedef struct vcolorModel          vcolorModel;
typedef struct vcolorDevice         vcolorDevice;
typedef struct vcolorConverter      vcolorConverter;

typedef void (*vcolorConverterProc)(
    const vcolorSpec               *spec,
    vcolorSpec                     *target
    );

typedef void (*vcolorNudgeProc)(
    vcolorSpec                     *subject,
    double                          ratio,
    const vcolorSpec               *target
    );

/*
 * colors
 */

typedef struct vcolor               vcolor;
typedef struct vcolorInstanceClass  vcolorInstanceClass;

/*
 * color palettes
 */

typedef struct vcolorPalette        vcolorPalette;
typedef struct vcolorPaletteClass   vcolorPaletteClass;

/*
 * color schemes
 */

typedef struct vcolorScheme         vcolorScheme;
typedef struct vcolorSchemeClass    vcolorSchemeClass;

/*
 * deprecated
 */

typedef vcolorModel                 vcolorClass;

/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */

void vcolorStartup(void);


/*
 * colors
 */

vcolor *vcolorCreate(
    void
    );

vcolor *vcolorCreateSpecific(
    const vcolorModel              *model
    );

void vcolorDestroy(
    vcolor                         *color
    );

void vcolorMarkModified(
    vcolor                         *color
    );

void vcolorShare(
    vcolor                         *color
    );

int vcolorIsPrivate(
    vcolor                         *color
    );

vcolor *vcolorInternSpec(
    const vcolorSpec               *spec
    );

vcolor *vcolorLoadIntern(
    vresource                       resource
    );

vcolorSpec *vcolorGetSpec(
    const vcolor                   *color
    );

void vcolorSetSpec(
    vcolor                         *color,
    vcolorSpec			   *spec
    );

void vcolorRelease(
    vcolor                         *color
    );

vbuffer *vcolorMakeBuffer(
    vcolor                         *color,
    const vcolorDevice             *device
    );

const vbufferDevice *vcolorDeviceGetBufferDevice(
    const vcolorDevice             *device
    );

int vcolorIsEqual(
    vcolor                         *color1,
    vcolor                         *color2
    );

/*
 * predefined colors
 */

vcolor *vcolorGetBlack(
    void
    );

vcolor *vcolorGetWhite(
    void
    );

/*
 * color specs
 */

vcolorSpecClass *vcolorGetDefaultSpecClass(
    void
    );

vcolorSpec *vcolorCreateSpec(
    void
    );

vcolorSpec *vcolorCreateSpecSpecific(
    const vcolorModel              *model
    );

void vcolorInitSpec(
    vcolorSpec                     *spec
    );

void vcolorInitSpecSpecific(
    vcolorSpec                     *spec,
    const vcolorModel              *model
    );

vcolorSpec *vcolorCloneSpec(
    const vcolorSpec               *spec
    );

void vcolorCopySpec(
    const vcolorSpec               *from,
    vcolorSpec                     *to
    );

void  vcolorCopyInitSpec(
    const vcolorSpec               *from,
    vcolorSpec                     *to
    );

void vcolorDestroySpec(
    vcolorSpec                     *spec
    );

vcolorSpec *vcolorLoadSpec(
    vresource                       resource
    );

void vcolorLoadInitSpec(
    vcolorSpec                     *spec,
    vresource                       resource
    );

void vcolorStoreSpec(
    const vcolorSpec               *spec,
    vresource                       resource
    );

vloadable *vcolorGetSpecLoadable(
    const vcolorSpec		   *spec
    );
    
vinstance *vcolorGetSpecInstance(
    const vcolorSpec		   *spec
    );

void vcolorSetSpecGray(
    vcolorSpec                     *spec,
    unsigned int                    value
    );

void vcolorSetSpecRGB(
    vcolorSpec                     *spec,
    unsigned int                    red,
    unsigned int                    green,
    unsigned int                    blue
    );

void vcolorSetSpecHLS( 
    vcolorSpec                     *spec,
    unsigned int                    hue,
    unsigned int                    lightness,
    unsigned int                    saturation
    );

void vcolorSetSpecCMY( 
    vcolorSpec                     *spec,
    unsigned int                    cyan,
    unsigned int                    magenta,
    unsigned int                    yellow
    );

void vcolorFSetSpecGray(
    vcolorSpec                     *spec,
    double                          gray
    );

void vcolorFSetSpecRGB(
    vcolorSpec                     *spec,
    double                          red,
    double                          green,
    double                          blue
    );

void vcolorFSetSpecHLS(
    vcolorSpec                     *spec,
    double                          hue,
    double                          lightness,
    double                          saturation
    );

void vcolorFSetSpecCMY(
    vcolorSpec                     *spec,
    double                          cyan,
    double                          magenta,
    double                          yellow
    );
		      
void vcolorGetSpecRGB(
    const vcolorSpec               *spec,
    unsigned int                   *red,
    unsigned int                   *green,
    unsigned int                   *blue
    );

void vcolorGetSpecHLS( 
    const vcolorSpec               *spec,
    unsigned int                   *hue,
    unsigned int                   *lightness,
    unsigned int                   *saturation
    );

void vcolorGetSpecCMY( 
    const vcolorSpec               *spec,
    unsigned int                   *cyan,
    unsigned int                   *magenta,
    unsigned int                   *yellow
    );

void vcolorFGetSpecRGB(
    const vcolorSpec               *spec,
    double                         *red,
    double                         *green,
    double                         *blue
    );

void vcolorFGetSpecHLS(
    const vcolorSpec               *spec,
    double                         *hue,
    double                         *lightness,
    double                         *saturation
    );

void vcolorFGetSpecCMY(
    const vcolorSpec               *spec,
    double                         *cyan,
    double                         *magenta,
    double                         *yellow
    );
		      
void vcolorSetSpecDeltaRGB(
    vcolorSpec                     *spec,
    unsigned int                    redDelta,
    unsigned int                    greenDelta,
    unsigned int                    blueDelta
    );
	 
void vcolorSetSpecDeltaRGBDistance(
    vcolorSpec                     *spec,
    unsigned int                    distance
    );

void vcolorFSetSpecDeltaRGB(
    vcolorSpec                     *spec,
    double                          redDelta,
    double                          greenDelta,
    double                          blueDelta
    );
	 
void vcolorFSetSpecDeltaRGBDistance( 
    vcolorSpec                     *spec,
    double                          distance
    );

void vcolorSetSpecDeltaHLS(
    vcolorSpec                     *spec,
    unsigned int                    hueDelta,
    unsigned int                    lightnessDelta,
    unsigned int                    saturationDelta
    );

void vcolorSetSpecDeltaHLSDistance(
    vcolorSpec                     *spec,
    unsigned int                    distance
    );

void vcolorFSetSpecDeltaHLS(
    vcolorSpec                     *spec,
    double                          hueDelta,
    double                          lightnessDelta,
    double                          saturationDelta
    );

void vcolorFSetSpecDeltaHLSDistance(
    vcolorSpec                     *spec,
    double                          distance
    );

void vcolorSetSpecDeltaCMY(
    vcolorSpec                     *spec,
    unsigned int		    cyanDelta,
    unsigned int		    magentaDelta,
    unsigned int		    yellowDelta
    );

void vcolorSetSpecDeltaCMYDistance(
    vcolorSpec                     *spec,
    unsigned int		    distance
    );

void vcolorFSetSpecDeltaCMY(
    vcolorSpec                     *spec,
    double                          cyanDelta,
    double                          magentaDelta,
    double                          yellowDelta
    );

void vcolorFSetSpecDeltaCMYDistance(
    vcolorSpec                     *spec,
    double                          distance
    );

int vcolorGetSpecDeltaType(
    const vcolorSpec               *spec
    );

unsigned int vcolorGetSpecDeltaRGBDistance(
    const vcolorSpec               *spec
    );

unsigned int vcolorGetSpecDeltaRGBRed(
    const vcolorSpec               *spec
    );

unsigned int vcolorGetSpecDeltaRGBGreen(
    const vcolorSpec               *spec
    );

unsigned int vcolorGetSpecDeltaRGBBlue(
    const vcolorSpec               *spec
    );

unsigned int vcolorGetSpecDeltaHLSHue(
    const vcolorSpec               *spec
    );

unsigned int vcolorGetSpecDeltaHLSLightness(
    const vcolorSpec               *spec
    );

unsigned int vcolorGetSpecDeltaHLSSaturation(
    const vcolorSpec               *spec
    );

unsigned int vcolorGetSpecDeltaHLSDistance(
    const vcolorSpec               *spec
    );

unsigned int vcolorGetSpecDeltaCMYCyan(
    const vcolorSpec               *spec
    );

unsigned int vcolorGetSpecDeltaCMYMagenta(
    const vcolorSpec               *spec
    );

unsigned int vcolorGetSpecDeltaCMYYellow(
    const vcolorSpec               *spec
    );

unsigned int vcolorGetSpecDeltaCMYDistance(
    const vcolorSpec               *spec
    );

void vcolorSetSpecMaxDitherDotArea(
    vcolorSpec                     *spec,
    unsigned int                    area
    );

unsigned int vcolorGetSpecMaxDitherDotArea(
    vcolorSpec                     *spec
    );

void vcolorConvertSpec(
    vcolorSpec                     *spec,
    const vcolorModel              *model
    );

void  vcolorNudgeSpec(
    vcolorSpec                     *subject,
    unsigned int                    ratio,
    const vcolorSpec               *target
    );

void vcolorFNudgeSpec(
    vcolorSpec                     *subject,
    double                          ratio,
    const vcolorSpec               *target
    );

const vcolorModel *vcolorGetSpecModel(
    const vcolorSpec               *spec
    );

void vcolorSetSpecModel(
    vcolorSpec                     *spec,
    const vcolorModel              *model
    );

/*
 * color spec models
 */

const vcolorModel *vcolorGetRGBModel(
    void
    );

const vcolorModel *vcolorGetHLSModel(
    void
    );

const vcolorModel *vcolorGetCMYModel(
    void
    );

/*
 * color component conversions
 */

unsigned int vcolorRGBToGray(
    unsigned int                    red,
    unsigned int                    green,
    unsigned int                    blue
    );

unsigned int vcolorRGBToGrayQuick(
    unsigned int                    red,
    unsigned int                    green,
    unsigned int                    blue
    );

/*
 * color palettes
 */

vcolorPaletteClass *vcolorGetDefaultPaletteClass(
    void
    );

vcolorPalette *vcolorCreatePalette(
    void
    );

void vcolorInitPalette(
    vcolorPalette                  *palette
    );

vcolorPalette *vcolorClonePalette(
    const vcolorPalette            *palette
    );

void vcolorCopyPalette(
    const vcolorPalette            *from,
    vcolorPalette                  *to
    );

void vcolorCopyInitPalette(
    const vcolorPalette            *from,
    vcolorPalette                  *to
    );

void vcolorDestroyPalette(
    vcolorPalette                  *palette
    );

vcolorPalette *vcolorLoadPalette(
    vresource                       resource
    );

void vcolorLoadInitPalette(
    vcolorPalette                  *palette,
    vresource                       resource
    );

void vcolorStorePalette(
    const vcolorPalette            *palette,
    vresource                       resource
    );

vloadable *vcolorGetPaletteLoadable(
    const vcolorPalette		   *palette
    );
    
vinstance *vcolorGetPaletteInstance(
    const vcolorPalette		   *palette
    );

unsigned int vcolorGetPaletteSize(
    const vcolorPalette            *palette
    );

void vcolorSetPaletteSize(
    vcolorPalette                  *palette,
    unsigned int                    size
    );

void vcolorAppendPaletteSlots(
    vcolorPalette                  *palette,
    unsigned int                    size
    );

void vcolorInsertPaletteSlots(
    vcolorPalette                  *palette,
    unsigned int                    at,
    unsigned int                    count
    );

void vcolorDeletePaletteSlots(
    vcolorPalette                  *palette,
    unsigned int                    at,
    unsigned int                    count
    );

void vcolorMarkPaletteModified(
    vcolorPalette                  *palette
    );

vbuffer *vcolorMakePaletteBuffer(
    vcolorPalette                  *palette,
    const vbufferDevice            *device
    );

vcolorSpec *vcolorGetPaletteFirstSpec(
    const vcolorPalette            *palette
    );

vcolorSpec *vcolorGetPaletteLastPlusOneSpec(
    const vcolorPalette            *palette
    );

vcolorSpec *vcolorGetPaletteSpecAt(
    const vcolorPalette            *palette,
    unsigned int                    at
    );

void vcolorSetPaletteSpecAt(
    vcolorPalette                  *palette,
    unsigned int                    at,
    const vcolorSpec		   *spec
    );

unsigned int vcolorGetPaletteSpecCount(
    vcolorPalette                  *palette
    );

/*
 * color schemes
 */

const vname *vcolorGetIDName(
    int                             id
    );

int vcolorIsIDName(
    const vname                    *name
    );

int vcolorGetNameID(
    const vname                    *name
    );

unsigned long vcolorEnableFlags(
    unsigned long                   flags
    );

unsigned long vcolorDisableFlags(
    unsigned long                   flags
    );

unsigned long vcolorIDsToFlags(
    const int                      *ids,
    int                             count
    );

int vcolorFlagsToIDs(
    unsigned long                   flags,
    int                            *ids
    );

vcolorSchemeClass *vcolorGetDefaultSchemeClass(
    void
    );

void vcolorInitScheme(
    vcolorScheme                   *scheme
    );

void vcolorDestroyScheme(
    vcolorScheme                   *scheme
    );

void vcolorCopyScheme(
    vcolorScheme                   *scheme,
    vcolorScheme                   *target
    );

void vcolorCopyInitScheme(
    vcolorScheme                   *scheme,
    vcolorScheme                   *target
    );

void vcolorMergeScheme(
    vcolorScheme                   *scheme,
    unsigned long                   flags,
    vcolorScheme                   *target
    );

void vcolorMergeInitScheme(
    vcolorScheme                   *scheme,
    unsigned long                   flags,
    vcolorScheme                   *target
    );

void vcolorLoadInitScheme(
    vcolorScheme                   *scheme,
    vresource                       resource
    );

void vcolorStoreScheme(
    vcolorScheme                   *scheme,
    vresource                       resource
    );

vloadable *vcolorGetSchemeLoadable(
    const vcolorScheme		   *scheme
    );
    
vinstance *vcolorGetSchemeInstance(
    const vcolorScheme		   *scheme
    );

void vcolorEnableScheme(
    vcolorScheme                   *scheme
    );

void vcolorDisableScheme(
    vcolorScheme                   *scheme
    );

void vcolorSetScheme(
    vcolorScheme                   *scheme,
    int                             id,
    vcolor                         *color
    );

void vcolorSetSchemeArray(
    vcolorScheme                   *scheme,
    unsigned long                   flags,
    vcolor                         *const *colors
    );

void vcolorSetSchemeIDArray(
    vcolorScheme                   *scheme,
    const int                      *ids,
    int                             count,
    vcolor                         *const *colors
    );

unsigned long vcolorGetSchemeFlags(
    vcolorScheme                   *scheme
    );

vcolor *vcolorGetScheme(
    vcolorScheme                   *scheme,
    int                             id
    );

void vcolorGetSchemeArray(
    vcolorScheme                   *scheme,
    unsigned long                   flags,
    vcolor                        **target
    );

void vcolorGetSchemeIDArray(
    vcolorScheme                   *scheme,
    const int                      *ids,
    int                             count,
    vcolor                        **target
    );

vcolor *vcolorGetSchemeForeground(
    vcolorScheme                   *scheme
    );

vcolor *vcolorGetSchemeBackground(
    vcolorScheme                   *scheme
    );

vcolor *vcolorGetSchemeShadowTop(
    vcolorScheme                   *scheme
    );

vcolor *vcolorGetSchemeShadowBottom(
    vcolorScheme                   *scheme
    );

vcolor *vcolorGetSchemeForegroundHilite(
    vcolorScheme                   *scheme
    );

vcolor *vcolorGetSchemeBackgroundHilite(
    vcolorScheme                   *scheme
    );

vcolor *vcolorGetSchemeBackgroundEmboss(
    vcolorScheme                   *scheme
    );

vcolor *vcolorGetSchemeBackgroundDeboss(
    vcolorScheme                   *scheme
    );

vcolor *vcolorGetSchemeBorder(
    vcolorScheme                   *scheme
    );

vcolor *vcolorGetSchemeFocus(
    vcolorScheme                   *scheme
    );

vcolor *vcolorGetSchemeShadowTopDark(
    vcolorScheme                   *scheme
    );

vcolor *vcolorGetSchemeShadowBottomDark(
    vcolorScheme                   *scheme
    );

vcolor *vcolorGetSchemeDisableForeground(
    vcolorScheme                   *scheme
    );

vcolor *vcolorGetSchemeDisableBackground(
    vcolorScheme                   *scheme
    );

vcolor *vcolorGetSchemeDisableShadowTop(
    vcolorScheme                   *scheme
    );

vcolor *vcolorGetSchemeDisableShadowBottom(
    vcolorScheme                   *scheme
    );

vcolor *vcolorGetSchemeDisableForegroundHilite(
    vcolorScheme                   *scheme
    );

vcolor *vcolorGetSchemeDisableBackgroundHilite(
    vcolorScheme                   *scheme
    );

vcolor *vcolorGetSchemeDisableBackgroundEmboss(
    vcolorScheme                   *scheme
    );

vcolor *vcolorGetSchemeDisableBackgroundDeboss(
    vcolorScheme                   *scheme
    );

vcolor *vcolorGetSchemeDisableBorder(
    vcolorScheme                   *scheme
    );

vcolor *vcolorGetSchemeDisableFocus(
    vcolorScheme                   *scheme
    );

vcolor *vcolorGetSchemeDisableShadowTopDark(
    vcolorScheme                   *scheme
    );

vcolor *vcolorGetSchemeDisableShadowBottomDark(
    vcolorScheme                   *scheme
    );

/*
 * deprecated functions:
 */

const vcolorModel *vcolorGetSpecClass(const vcolorSpec *spec);
void vcolorSetSpecClass(vcolorSpec *spec, const vcolorModel *clas);

const vcolorModel *vcolorGetRGBClass(void);
const vcolorModel *vcolorGetHLSClass(void);
const vcolorModel *vcolorGetCMYClass(void);

unsigned int vcolorGetSpecRGBRed(const vcolorSpec *spec);
unsigned int vcolorGetSpecRGBGreen(const vcolorSpec *spec);
unsigned int vcolorGetSpecRGBBlue(const vcolorSpec *spec);

unsigned int vcolorGetSpecHLSHue(const vcolorSpec *spec);
unsigned int vcolorGetSpecHLSLightness(const vcolorSpec *spec);
unsigned int vcolorGetSpecHLSSaturation(const vcolorSpec *spec);

unsigned int vcolorGetSpecCMYCyan(const vcolorSpec *spec);
unsigned int vcolorGetSpecCMYMagenta(const vcolorSpec *spec);
unsigned int vcolorGetSpecCMYYellow(const vcolorSpec *spec);


/*
 * * * * * * * * * * PRIVATE CONSTANT DEFINITIONS * * * * * * * * * *
 */

/*
 * colors
 */

#define _vcolorDELTA_MASK	   (0x1F)
#define _vcolorDISTANCE            (0x10) /* uses distance mode? */
#define _vcolorMODEL               (0x0F) /* which color model? */
#define _vcolorMODEL_RGB           (0x00)
#define _vcolorMODEL_HLS           (0x01)
#define _vcolorMODEL_CMY           (0x02)

#define _vcolorRGB_RESTRICTION_RED		0
#define _vcolorRGB_RESTRICTION_GREEN		1
#define _vcolorRGB_RESTRICTION_BLUE		2

#define _vcolorRGB_RESTRICTION_DISTANCE		0

#define _vcolorHLS_RESTRICTION_HUE		0
#define _vcolorHLS_RESTRICTION_LIGHTNESS	1
#define _vcolorHLS_RESTRICTION_SATURATION	2

#define _vcolorHLS_RESTRICTION_DISTANCE		0

#define _vcolorCMY_RESTRICTION_CYAN		0
#define _vcolorCMY_RESTRICTION_MAGENTA		1
#define _vcolorCMY_RESTRICTION_YELLOW		2

#define _vcolorCMY_RESTRICTION_DISTANCE		0

#define _vcolorMAX_RESTRICTION_DELTAS		3


#define _vcolorRGB_RED			0
#define _vcolorRGB_GREEN		1
#define _vcolorRGB_BLUE			2

#define _vcolorHLS_HUE			0
#define _vcolorHLS_LIGHTNESS		1
#define _vcolorHLS_SATURATION		2

#define _vcolorCMY_CYAN			0
#define _vcolorCMY_MAGENTA		1
#define _vcolorCMY_YELLOW		2

#define _vcolorMAX_COMPONENTS		3

/*
 * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * *
 */

/*
 * color specs
 */

struct vcolorModel {
    const vcolorConverter	   *toConverters;
    const vcolorConverter	   *fromConverters;
    vcolorNudgeProc		    nudge;
};

struct vcolorDevice {
    vbufferDevice	            bufferDevice;
    vcolorPalette	           *palette;
};

struct vcolorConverter {
    const vcolorModel	           *model;
    vcolorConverterProc	            proc;
};

typedef struct _vcolorRestriction {
    const vcolorModel	           *model;
    const vcolor	           *differing;
    unsigned short                  flags;
    unsigned short                  maxDitherDotArea;
    vcolorComponentValue	    delta[_vcolorMAX_RESTRICTION_DELTAS];
} _vcolorRestriction;

struct vcolorSpec {
    vloadable			    object;

    const _vcolorRestriction       *restriction;
    vcolorComponentValue	    component[_vcolorMAX_COMPONENTS];
};

#define vcolorSpecCLASS(SUPER, OBJECT)					      \
    vloadableCLASS(SUPER, OBJECT)

struct vcolorSpecClass {
    vcolorSpecCLASS(vcolorSpecClass, vcolorSpec);
};


/*
 * colors
 */

struct vcolor {
    vcolorSpec		            spec;

    vbuffer                        *buffers;
    vbool			    isPrivate;
    unsigned short		    refCount;
};

#define vcolorCLASS(SUPER, OBJECT)					      \
    vcolorSpecCLASS(SUPER, OBJECT)

struct vcolorInstanceClass {
    vcolorCLASS(vcolorInstanceClass, vcolor);
};


/*
 * color palettes
 */

struct vcolorPalette {
    vloadable			    object;

    vbuffer                        *buffers;
    unsigned short		    count;
    vcolorSpec		           *specs;
};

#define vcolorPaletteCLASS(SUPER, OBJECT)				      \
    vloadableCLASS(SUPER, OBJECT)

struct vcolorPaletteClass {
    vcolorPaletteCLASS(vcolorPaletteClass, vcolorPalette);
};


/*
 * color schemes
 */

struct vcolorScheme {
    vloadable			    object;

    unsigned long                   flags;
    vcolor                         *colors[vcolorID_MAX];
};

#define vcolorSchemeCLASS(SUPER, OBJECT)				      \
    vloadableCLASS(SUPER, OBJECT)

struct vcolorSchemeClass {
    vcolorSchemeCLASS(vcolorSchemeClass, vcolorScheme);
};


/*
 * * * * * * * * * * PRIVATE VARIABLE DECLARATIONS * * * * * * * * * *
 */

/*
 * color models
 */

extern vportLINK const vcolorModel	    _vcolorRGBModel;
extern vportLINK const vcolorModel	    _vcolorHLSModel;
extern vportLINK const vcolorModel            _vcolorCMYModel;

/*
 * * * * * * * * * * PRIVATE FUNCTION PROTOTYPES * * * * * * * * * *
 */

/*
 * colors
 */

vcolorInstanceClass *_vcolorGetDefaultClass(void);
void _vcolorRelease(vcolor *color);

/*
 * color schemes
 */

vcolor *_vcolorGetScheme(vcolorScheme *scheme, int  id);

/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * *
 */

/*
 * color specs
 */

#define vcolorGetSpecLoadable(l) \
    (vportBASE_OBJECT((vcolorSpec *) l, object))
#define vcolorGetSpecInstance(l) \
    vloadableGetInstance(vcolorGetSpecLoadable(l))

#define vcolorInitSpec(s) \
    vloadableInitOfClass(vcolorGetSpecLoadable(s), \
			 (vloadableClass*)vcolorGetDefaultSpecClass())
#define vcolorCreateSpec() \
    ((vcolorSpec *) \
     vloadableCreateOfClass((vloadableClass*)vcolorGetDefaultSpecClass()))
#define vcolorDestroySpec(s) \
    vloadableDestroy(vcolorGetSpecLoadable(s))

#define vcolorSetSpecGray( spec, gray )	   vcolorSetSpecHLS( spec, 0, gray, 0 )

#define vcolorFSetSpecRGB( spec, r, g, b ) vcolorSetSpecRGB(                  \
     (spec), (unsigned int)((r)*vcolorCOMPONENT_MAX),                         \
             (unsigned int)((g)*vcolorCOMPONENT_MAX),                         \
             (unsigned int)((b)*vcolorCOMPONENT_MAX) )

#define vcolorFSetSpecHLS( spec, h, l, s ) vcolorSetSpecHLS(                  \
     (spec), (unsigned int)((h)*vcolorCOMPONENT_MAX),                         \
             (unsigned int)((l)*vcolorCOMPONENT_MAX),                         \
             (unsigned int)((s)*vcolorCOMPONENT_MAX) )

#define vcolorFSetSpecCMY( spec, c, m, y ) vcolorSetSpecCMY(                  \
     (spec), (unsigned int)((c)*vcolorCOMPONENT_MAX),                         \
	     (unsigned int)((m)*vcolorCOMPONENT_MAX),                         \
             (unsigned int)((y)*vcolorCOMPONENT_MAX) )

#define vcolorFSetSpecGray( spec, gray ) vcolorFSetSpecHLS(                   \
     spec, 0.0, gray, 0.0 )

#define vcolorGetSpecDeltaType( spec )	                                      \
     ((spec)->restriction->flags & _vcolorDELTA_MASK)

#define vcolorGetSpecDeltaRGBRed( spec )	                              \
     ((spec)->restriction->delta[_vcolorRGB_RESTRICTION_RED])
#define vcolorGetSpecDeltaRGBGreen( spec )	                              \
     ((spec)->restriction->delta[_vcolorRGB_RESTRICTION_GREEN])
#define vcolorGetSpecDeltaRGBBlue( spec )	                              \
     ((spec)->restriction->delta[_vcolorRGB_RESTRICTION_BLUE])

#define vcolorGetSpecDeltaRGBDistance( spec )	                              \
     ((spec)->restriction->delta[_vcolorRGB_RESTRICTION_DISTANCE])

#define vcolorGetSpecDeltaHLSHue( spec )	                              \
     ((spec)->restriction->delta[_vcolorHLS_RESTRICTION_HUE])
#define vcolorGetSpecDeltaHLSLightness( spec )	                              \
     ((spec)->restriction->delta[_vcolorHLS_RESTRICTION_LIGHTNESS])
#define vcolorGetSpecDeltaHLSSaturation( spec )	                              \
     ((spec)->restriction->delta[_vcolorHLS_RESTRICTION_SATURATION])

#define vcolorGetSpecDeltaHLSDistance( spec )	                              \
     ((spec)->restriction->delta[_vcolorHLS_RESTRICTION_DISTANCE])

#define vcolorGetSpecDeltaCMYCyan( spec )	                              \
     ((spec)->restriction->delta[_vcolorCMY_RESTRICTION_CYAN])
#define vcolorGetSpecDeltaCMYMagenta( spec )	                              \
     ((spec)->restriction->delta[_vcolorCMY_RESTRICTION_MAGENTA])
#define vcolorGetSpecDeltaCMYYellow( spec )	                              \
     ((spec)->restriction->delta[_vcolorCMY_RESTRICTION_YELLOW])

#define vcolorGetSpecDeltaCMYDistance( spec )	                              \
     ((spec)->restriction->delta[_vcolorCMY_RESTRICTION_DISTANCE])

#define vcolorFSetSpecDeltaRGB( spec, r, g, b ) vcolorSetSpecDeltaRGB(        \
     (spec), (unsigned int)((r)*vcolorCOMPONENT_MAX),                         \
             (unsigned int)((g)*vcolorCOMPONENT_MAX),                         \
             (unsigned int)((b)*vcolorCOMPONENT_MAX) )

#define vcolorFSetSpecDeltaRGBDistance( spec, d )                             \
  vcolorSetSpecDeltaRGBDistance( (spec),                                      \
                                 (unsigned int)((d)*vcolorCOMPONENT_MAX) )

#define vcolorFSetSpecDeltaHLS( spec, h, l, s ) vcolorSetSpecDeltaHLS(        \
     (spec), (unsigned int)((h)*vcolorCOMPONENT_MAX),                         \
             (unsigned int)((l)*vcolorCOMPONENT_MAX),                         \
             (unsigned int)((s)*vcolorCOMPONENT_MAX) )
#define vcolorFSetSpecDeltaHLSDistance( spec, d )                             \
     vcolorSetSpecDeltaHLSDistance( (spec),                                   \
                                    (unsigned int)((d)*vcolorCOMPONENT_MAX) )

#define vcolorFSetSpecDeltaCMY( spec, c, m, y ) vcolorSetSpecDeltaCMY(        \
     (spec), (unsigned int)((c)*vcolorCOMPONENT_MAX),                         \
             (unsigned int)((m)*vcolorCOMPONENT_MAX),                         \
             (unsigned int)((y)*vcolorCOMPONENT_MAX) )

#define vcolorFSetSpecDeltaCMYDistance( spec, d)                              \
     vcolorSetSpecDeltaCMYDistance( (spec),                                   \
                                    (unsigned int)((d)*vcolorCOMPONENT_MAX) )

#define vcolorGetSpecMaxDitherDotArea( spec )	                              \
     ((spec)->restriction->maxDitherDotArea)

#define vcolorFNudgeSpec( subject, ratio, target )                            \
    ((*((vcolorModel *) (subject)->restriction->model)->nudge)(		      \
					   (subject), (ratio), (target) ))

#define vcolorNudgeSpec( subject, ratio, target )	                      \
    vcolorFNudgeSpec( (subject), (ratio)/(double)vcolorCOMPONENT_MAX,         \
    (target) )

#define vcolorGetSpecModel( spec )		   ((spec)->restriction->model)

#define vcolorRGBToGray(r, g, b) \
    ((unsigned int)(((unsigned long)(r)*vcolorGRAY_RED+ \
		     (unsigned long)(g)*vcolorGRAY_GREEN+ \
		     (unsigned long)(b)*vcolorGRAY_BLUE)>>16))
#define vcolorRGBToGrayQuick(r, g, b) \
    ((unsigned int)(((((unsigned long)(r)<<2)+(r))>>4)+ \
		    ((((unsigned long)(g)<<3)+(g))>>4)+((b)>>3)))

/*
 * colors
 */

#define vcolorGetSpec(l) \
    (vportBASE_OBJECT((vcolor *) l, spec))

#define vcolorIsPrivate(c)		   ((c)->isPrivate)
#define vcolorRelease(c)                   vcolorDestroy(c)

#define vcolorDeviceGetBufferDevice( dev ) (&(dev)->bufferDevice)

/*
 * color models
 */

#define vcolorGetRGBModel()			   (&_vcolorRGBModel)
#define vcolorGetHLSModel()			   (&_vcolorHLSModel)
#define vcolorGetCMYModel()			   (&_vcolorCMYModel)

/*
 * color palettes
 */

#define vcolorGetPaletteLoadable(l) \
    (vportBASE_OBJECT((vcolorPalette *) l, object))
#define vcolorGetPaletteInstance(l) \
    vloadableGetInstance(vcolorGetPaletteLoadable(l))

#define vcolorGetPaletteSize( palette )		                              \
    ((palette)->count)

#define vcolorGetPaletteFirstSpec( palette )	   ((palette)->specs)
#define vcolorGetPaletteLastPlusOneSpec( palette ) \
					((palette)->specs + (palette)->count)

#define vcolorAppendPaletteSlots(palette, n)                                  \
  vcolorInsertPaletteSlots( (palette),                                        \
			     vcolorGetPaletteSize(palette),                   \
			     (n))

#define vcolorGetPaletteSpecAt( pal, at )	(&(pal)->specs[(at)])
#define vcolorGetPaletteSpecCount( pal )	((pal)->count)

#define vcolorInitPalette(p) \
    vloadableInitOfClass(vcolorGetPaletteLoadable(p), \
			 (vloadableClass*)vcolorGetDefaultPaletteClass())
#define vcolorCreatePalette() \
    ((vcolorPalette *) \
     vloadableCreateOfClass((vloadableClass*)vcolorGetDefaultPaletteClass()))
#define vcolorDestroyPalette(p) \
    vloadableDestroy(vcolorGetPaletteLoadable(p))
#define vcolorCopyPalette(p,t) \
    vloadableCopy(vcolorGetPaletteLoadable(p), vcolorGetPaletteLoadable(t))
#define vcolorStorePalette(p, r) \
    vloadableStore(vcolorGetPaletteLoadable(p), r)
#define vcolorClonePalette(p) \
    ((vcolorPalette *) \
     vloadableCloneOfSubclass(vcolorGetPaletteLoadable(p), \
			      (vloadableClass*) \
			      vcolorGetDefaultPaletteClass()))
#define vcolorCopyInitPalette(p,t) \
    vloadableCopyInitOfSubclass(vcolorGetPaletteLoadable(p), \
				vcolorGetPaletteLoadable(t), \
				(vloadableClass*) vcolorGetDefaultPaletteClass())

#define vcolorLoadPalette(r) \
    ((vcolorPalette *) vloadableLoadOfSubclass(r, \
					       (vloadableClass*) \
					       vcolorGetDefaultPaletteClass()))
#define vcolorLoadInitPalette(p,r) \
    vloadableLoadInitOfSubclass(vcolorGetPaletteLoadable(p), (r), \
			(vloadableClass*) vcolorGetDefaultPaletteClass())

/*
 * color schemes
 */

#define vcolorGetSchemeLoadable(l) \
    (vportBASE_OBJECT((vcolorScheme *) l, object))
#define vcolorGetSchemeInstance(l) \
    vloadableGetInstance(vcolorGetSchemeLoadable(l))

#define vcolorEnableFlags(f) \
    (((f)&vcolorFLAG_ENABLE_ALL)|((f)&vcolorFLAG_DISABLE_ALL)>>1)
#define vcolorDisableFlags(f) \
    (((f)&vcolorFLAG_DISABLE_ALL)|((f)&vcolorFLAG_ENABLE_ALL)<<1)

#if (!vdebugDEBUG)
#define vcolorSetScheme(s, i, c) \
    (void)((c)!=NULL ? ((s)->colors[i] = (c), (s)->flags |= 1UL<<(i)) : \
	               ((s)->flags &= ~(1UL<<(i))))
#define vcolorGetScheme(s, i) \
    ((s)->flags&1UL<<(i) ? (s)->colors[i] : NULL)
#endif

#define vcolorGetSchemeFlags(s)   ((s)->flags)

#if (vdebugDEBUG)
#define vcolorGetSchemeForeground(s) _vcolorGetScheme(s, vcolorID_FOREGROUND)
#define vcolorGetSchemeBackground(s) _vcolorGetScheme(s, vcolorID_BACKGROUND)
#define vcolorGetSchemeShadowTop(s)  _vcolorGetScheme(s, vcolorID_SHADOW_TOP)
#define vcolorGetSchemeShadowBottom(s) \
    _vcolorGetScheme(s, vcolorID_SHADOW_BOTTOM)
#define vcolorGetSchemeForegroundHilite(s) \
    _vcolorGetScheme(s, vcolorID_FOREGROUND_HILITE)
#define vcolorGetSchemeBackgroundHilite(s) \
    _vcolorGetScheme(s, vcolorID_BACKGROUND_HILITE)
#define vcolorGetSchemeBackgroundEmboss(s) \
    _vcolorGetScheme(s, vcolorID_BACKGROUND_EMBOSS)
#define vcolorGetSchemeBackgroundDeboss(s) \
    _vcolorGetScheme(s, vcolorID_BACKGROUND_DEBOSS)
#define vcolorGetSchemeBorder(s)     _vcolorGetScheme(s, vcolorID_BORDER)
#define vcolorGetSchemeFocus(s)      _vcolorGetScheme(s, vcolorID_FOCUS)
#define vcolorGetSchemeShadowTopDark(s)  \
    _vcolorGetScheme(s, vcolorID_SHADOW_TOP_DARK)
#define vcolorGetSchemeShadowBottomDark(s) \
    _vcolorGetScheme(s, vcolorID_SHADOW_BOTTOM_DARK)

#define vcolorGetSchemeDisableForeground(s) \
    _vcolorGetScheme(s, vcolorID_DISABLE|vcolorID_FOREGROUND)
#define vcolorGetSchemeDisableBackground(s) \
    _vcolorGetScheme(s, vcolorID_DISABLE|vcolorID_BACKGROUND)
#define vcolorGetSchemeDisableShadowTop(s) \
    _vcolorGetScheme(s, vcolorID_DISABLE|vcolorID_SHADOW_TOP)
#define vcolorGetSchemeDisableShadowBottom(s) \
    _vcolorGetScheme(s, vcolorID_DISABLE|vcolorID_SHADOW_BOTTOM)
#define vcolorGetSchemeDisableForegroundHilite(s) \
    _vcolorGetScheme(s, vcolorID_DISABLE|vcolorID_FOREGROUND_HILITE)
#define vcolorGetSchemeDisableBackgroundHilite(s) \
    _vcolorGetScheme(s, vcolorID_DISABLE|vcolorID_BACKGROUND_HILITE)
#define vcolorGetSchemeDisableBackgroundEmboss(s) \
    _vcolorGetScheme(s, vcolorID_DISABLE|vcolorID_BACKGROUND_EMBOSS)
#define vcolorGetSchemeDisableBackgroundDeboss(s) \
    _vcolorGetScheme(s, vcolorID_DISABLE|vcolorID_BACKGROUND_DEBOSS)
#define vcolorGetSchemeDisableBorder(s) \
    _vcolorGetScheme(s, vcolorID_DISABLE|vcolorID_BORDER)
#define vcolorGetSchemeDisableFocus(s) \
    _vcolorGetScheme(s, vcolorID_DISABLE|vcolorID_FOCUS)
#define vcolorGetSchemeDisableShadowTopDark(s) \
    _vcolorGetScheme(s, vcolorID_DISABLE|vcolorID_SHADOW_TOP_DARK)
#define vcolorGetSchemeDisableShadowBottomDark(s) \
    _vcolorGetScheme(s, vcolorID_DISABLE|vcolorID_SHADOW_BOTTOM_DARK)
#else
#define vcolorGetSchemeForeground(s) ((s)->colors[vcolorID_FOREGROUND])
#define vcolorGetSchemeBackground(s) ((s)->colors[vcolorID_BACKGROUND])
#define vcolorGetSchemeShadowTop(s)  ((s)->colors[vcolorID_SHADOW_TOP])
#define vcolorGetSchemeShadowBottom(s) \
    ((s)->colors[vcolorID_SHADOW_BOTTOM])
#define vcolorGetSchemeForegroundHilite(s) \
    ((s)->colors[vcolorID_FOREGROUND_HILITE])
#define vcolorGetSchemeBackgroundHilite(s) \
    ((s)->colors[vcolorID_BACKGROUND_HILITE])
#define vcolorGetSchemeBackgroundEmboss(s) \
    ((s)->colors[vcolorID_BACKGROUND_EMBOSS])
#define vcolorGetSchemeBackgroundDeboss(s) \
    ((s)->colors[vcolorID_BACKGROUND_DEBOSS])
#define vcolorGetSchemeBorder(s)     ((s)->colors[vcolorID_BORDER])
#define vcolorGetSchemeFocus(s)      ((s)->colors[vcolorID_FOCUS])
#define vcolorGetSchemeShadowTopDark(s) \
    ((s)->colors[vcolorID_SHADOW_TOP_DARK])
#define vcolorGetSchemeShadowBottomDark(s) \
    ((s)->colors[vcolorID_SHADOW_BOTTOM_DARK])

#define vcolorGetSchemeDisableForeground(s) \
    ((s)->colors[vcolorID_DISABLE|vcolorID_FOREGROUND])
#define vcolorGetSchemeDisableBackground(s) \
    ((s)->colors[vcolorID_DISABLE|vcolorID_BACKGROUND])
#define vcolorGetSchemeDisableShadowTop(s) \
    ((s)->colors[vcolorID_DISABLE|vcolorID_SHADOW_TOP])
#define vcolorGetSchemeDisableShadowBottom(s) \
    ((s)->colors[vcolorID_DISABLE|vcolorID_SHADOW_BOTTOM])
#define vcolorGetSchemeDisableForegroundHilite(s) \
    ((s)->colors[vcolorID_DISABLE|vcolorID_FOREGROUND_HILITE])
#define vcolorGetSchemeDisableBackgroundHilite(s) \
    ((s)->colors[vcolorID_DISABLE|vcolorID_BACKGROUND_HILITE])
#define vcolorGetSchemeDisableBackgroundEmboss(s) \
    ((s)->colors[vcolorID_DISABLE|vcolorID_BACKGROUND_EMBOSS])
#define vcolorGetSchemeDisableBackgroundDeboss(s) \
    ((s)->colors[vcolorID_DISABLE|vcolorID_BACKGROUND_DEBOSS])
#define vcolorGetSchemeDisableBorder(s) \
    ((s)->colors[vcolorID_DISABLE|vcolorID_BORDER])
#define vcolorGetSchemeDisableFocus(s) \
    ((s)->colors[vcolorID_DISABLE|vcolorID_FOCUS])
#define vcolorGetSchemeDisableShadowTopDark(s) \
    ((s)->colors[vcolorID_DISABLE|vcolorID_SHADOW_TOP_DARK])
#define vcolorGetSchemeDisableShadowBottomDark(s) \
    ((s)->colors[vcolorID_DISABLE|vcolorID_SHADOW_BOTTOM_DARK])
#endif

#define vcolorGetSpecClass(s)	vcolorGetSpecModel(s)
#define vcolorSetSpecClass(s,c)	vcolorSetSpecModel(s,c)

#define vcolorGetRGBClass()	vcolorGetRGBModel()
#define vcolorGetHLSClass()	vcolorGetHLSModel()
#define vcolorGetCMYClass()	vcolorGetCMYModel()

#define vcolorInitScheme(s) \
    vloadableInitOfClass(vcolorGetSchemeLoadable(s), \
			 (vloadableClass*)vcolorGetDefaultSchemeClass())
#define vcolorDestroyScheme(s) \
    vloadableDestroy(vcolorGetSchemeLoadable(s))
#define vcolorCopyScheme(s,t) \
    vloadableCopy(vcolorGetSchemeLoadable(s), vcolorGetSchemeLoadable(t))
#define vcolorStoreScheme(s, r) \
    vloadableStore(vcolorGetSchemeLoadable(s), r)
#define vcolorCopyInitScheme(s,t) \
    	vloadableCopyInitOfSubclass(vcolorGetSchemeLoadable(s), \
				    vcolorGetSchemeLoadable(t), \
				    (vloadableClass*) \
				    vcolorGetDefaultSchemeClass())

#define vcolorLoadInitScheme(s,r) \
    	vloadableLoadInitOfSubclass(vcolorGetSchemeLoadable(s), (r), \
				    (vloadableClass*) \
				    vcolorGetDefaultSchemeClass())

vportEND_CPLUSPLUS_EXTERN_C

#endif /* vcolorINCLUDED */


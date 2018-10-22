/* $Id: vattribute.h,v 1.2 1997/08/12 20:51:53 dimitri Exp $ */

/************************************************************

    vattribute.h

    C Interface file for attribute objects

    (c) Copyright Visix Software Inc.
    All rights reserved

************************************************************/

#ifndef vattributeINCLUDED
#define vattributeINCLUDED

#ifndef  vportINCLUDED
#include <vport.h>
#endif

#ifndef  vstdioINCLUDED
#include vstdioHEADER
#endif

#ifndef  vdebugINCLUDED
#include vdebugHEADER
#endif

#ifndef  vexINCLUDED
#include vexHEADER
#endif

#ifndef  vnameINCLUDED
#include vnameHEADER
#endif

#ifndef  vstrINCLUDED
#include vstrHEADER
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

#ifndef  vkeyINCLUDED
#include vkeyHEADER
#endif

#ifndef  vclassINCLUDED
#include vclassHEADER
#endif

#ifndef  vloadableINCLUDED
#include vloadableHEADER
#endif

#ifndef  vcolorINCLUDED
#include vcolorHEADER
#endif

#ifndef  vfontINCLUDED
#include vfontHEADER
#endif

#ifndef  vfontspecINCLUDED
#include vfontspecHEADER
#endif

#ifndef  vobservableINCLUDED
#include vobservableHEADER
#endif

#ifndef  vmappingINCLUDED
#include vmappingHEADER
#endif

#ifndef vobjectINCLUDED
#include vobjectHEADER
#endif


vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * * * * * * * * * * PUBLIC CONSTANT DEFINITIONS  * * * * * * * * * *
 */

/*
 * * * * * * * * * * PUBLIC TYPE DEFINITIONS * * * * * * * * * *
 */

typedef struct vattributeContext	vattributeContext;
typedef struct vattributeContextClass	vattributeContextClass;

typedef struct vattributeTyper		vattributeTyper;
typedef struct vattributeTyperClass	vattributeTyperClass;


typedef vloadable			vattribute;
typedef struct vattributeClass		vattributeClass;

typedef struct vattributeBoolean	vattributeBoolean;
typedef struct vattributeBooleanClass	vattributeBooleanClass;

typedef struct vattributeInteger	vattributeInteger;
typedef struct vattributeIntegerClass	vattributeIntegerClass;

typedef struct vattributeKeyStroke	vattributeKeyStroke;
typedef struct vattributeKeyStrokeClass	vattributeKeyStrokeClass;

typedef struct vattributeTag		vattributeTag;
typedef struct vattributeTagClass	vattributeTagClass;

typedef struct vattributeString		vattributeString;
typedef struct vattributeStringClass	vattributeStringClass;

typedef struct vattributeRect		vattributeRect;
typedef struct vattributeRectClass	vattributeRectClass;

typedef struct vattributePoint		vattributePoint;
typedef struct vattributePointClass	vattributePointClass;

typedef struct vattributeMatrix		vattributeMatrix;
typedef struct vattributeMatrixClass	vattributeMatrixClass;

typedef struct vattributeColor		vattributeColor;
typedef struct vattributeColorClass	vattributeColorClass;

typedef struct vattributeFont		vattributeFont;
typedef struct vattributeFontClass	vattributeFontClass;


/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */

void vattributeStartup(void);


/*
 * attribute contexts
 */

vattributeContextClass *vattributeGetDefaultContextClass(
    void
    );

vobservable *vattributeGetContextObservable(
    vattributeContext		*context
    );

vloadable *vattributeGetContextLoadable(
    vattributeContext           *context
    );

vinstance *vattributeGetContextInstance(
    vattributeContext           *context
    );

vattributeContextClass *vattributeGetContextClass(
    vattributeContext           *attribute
    );

vattributeContext *vattributeCreateContextOfClass(
    vattributeContextClass      *clas
    );

vattributeContext *vattributeCreateContext(
    void
    );

void vattributeInitContextOfClass(
    vattributeContext           *context,
    vattributeContextClass      *clas
    );

void vattributeInitContext(
    vattributeContext           *context
    );

void vattributeDestroyContext(
    vattributeContext           *context
    );

vattributeContext *vattributeCloneContext(
    vattributeContext           *context
    );

void vattributeCopyContext(
    vattributeContext           *source,
    vattributeContext           *target
    );

void vattributeCopyInitContext(
    vattributeContext           *source,
    vattributeContext           *target
    );

vattributeContext *vattributeLoadContext(
    vresource			 resource
    );

void vattributeLoadInitContext(
    vattributeContext           *context,
    vresource			 resource
    );

void vattributeStoreContext(
    vattributeContext           *context,
    vresource			 resource
    );

vloadable *vattributeAddContextAttributeOwned(
    vattributeContext		*context,
    const vname			*objectTag,
    const vname			*attributeName,
    vloadable			*attribute
    );

vloadable *vattributeAddContextAttributeShared(
    vattributeContext		*context,
    const vname			*objectTag,
    const vname			*attributeName,
    vloadable			*attribute
    );

vloadable *vattributeGetContextAttribute(
    vattributeContext		*context,
    const vname			*objectTag,
    const vname			*attributeName
    );

vloadable *vattributeTestGetContextAttribute(
    vattributeContext		*context,
    const vname			*objectTag,
    const vname			*attributeName
    );

vloadable *vattributeRemoveContextAttribute(
    vattributeContext		*context,
    const vname			*objectTag,
    const vname			*attributeName
    );

void vattributeApplyContext(
    vattributeContext		*context,
    vobject			*object,
    const vname			*attributeName
    );

void vattributeApplyContextRecursively(
    vattributeContext		*context,
    vobject			*rootObject,
    const vname			*attributeName
    );


/*
 * attribute typers
 */

vattributeTyperClass *vattributeGetDefaultTyperClass(
    void
    );

vloadable *vattributeGetTyperLoadable(
    vattributeTyper             *typer
    );

vinstance *vattributeGetTyperInstance(
    vattributeTyper             *typer
    );

vattributeTyperClass *vattributeGetTyperClass(
    vattributeTyper             *attribute
    );

vattributeTyper *vattributeCreateTyperOfClass(
    vattributeTyperClass        *clas
    );

vattributeTyper *vattributeCreateTyper(
    void
    );

void vattributeInitTyperOfClass(
    vattributeTyper             *typer,
    vattributeTyperClass        *clas
    );

void vattributeInitTyper(
    vattributeTyper             *typer
    );

void vattributeDestroyTyper(
    vattributeTyper             *typer
    );

vattributeTyper *vattributeCloneTyper(
    vattributeTyper             *typer
    );

void vattributeCopyTyper(
    vattributeTyper             *source,
    vattributeTyper             *target
    );

void vattributeCopyInitTyper(
    vattributeTyper             *source,
    vattributeTyper             *target
    );

vattributeTyper *vattributeLoadTyper(
    vresource			 resource
    );

void vattributeLoadInitTyper(
    vattributeTyper             *typer,
    vresource			 resource
    );

void vattributeStoreTyper(
    vattributeTyper             *typer,
    vresource			 resource
    );


/*
 * attributes:
 */

vattributeClass *vattributeGetDefaultClass(
    void
    );

vattributeClass *vattributeGetClass(
    vattribute			*attribute
    );

vloadable *vattributeGetLoadable(
    vattribute			*attribute
    );

vinstance *vattributeGetInstance(
    vattribute			*attribute
    );

vattribute *vattributeCreateOfClass(
    vattributeClass		*clas
    );

void vattributeInitOfClass(
    vattribute			*attribute,
    vattributeClass		*clas
    );

void vattributeDestroy(
    vattribute			*attribute
    );

vattribute *vattributeClone(
    vattribute			*attribute
    );

void vattributeCopy(
    vattribute			*source,
    vattribute			*target
    );

void vattributeCopyInit(
    vattribute			*source,
    vattribute			*target
    );

vattribute *vattributeLoad(
    vresource			 resource
    );

void vattributeLoadInit(
    vattribute			*attribute,
    vresource			 resource
    );

void vattributeStore(
    vattribute			*attribute,
    vresource			 resource
    );

void vattributeApplyValue(
    vattribute			*attribute,
    vobject			*object,
    const vname			*attributeName
    );

void vattributeApply(
    vobject			*object,
    const vname			*attributeName,
    vloadable			*attribute
    );


/*
 * boolean attributes:
 */

vattributeBooleanClass *vattributeGetDefaultBooleanClass(
    void
    );

vattributeBooleanClass *vattributeGetBooleanClass(
    vattributeBoolean		*attribute
    );

vattribute *vattributeGetBooleanAttribute(
    vattributeBoolean		*attribute
    );

vloadable *vattributeGetBooleanLoadable(
    vattributeBoolean		*attribute
    );

vinstance *vattributeGetBooleanInstance(
    vattributeBoolean		*attribute
    );

vattributeBoolean *vattributeCreateBoolean(
    void
    );

void vattributeDestroyBoolean(
    vattributeBoolean		*attribute
    );

vloadable *vattributeMakeBoolean(
    vbool			 value
    );

vbool vattributeGetBooleanValue(
    vattributeBoolean		*attribute
    );

void vattributeSetBooleanValue(
    vattributeBoolean		*attribute,
    vbool			 value
    );


/*
 * integer attributes:
 */

vattributeIntegerClass *vattributeGetDefaultIntegerClass(
    void
    );

vattributeIntegerClass *vattributeGetIntegerClass(
    vattributeInteger		*attribute
    );

vattribute *vattributeGetIntegerAttribute(
    vattributeInteger		*attribute
    );

vloadable *vattributeGetIntegerLoadable(
    vattributeInteger		*attribute
    );

vinstance *vattributeGetIntegerInstance(
    vattributeInteger		*attribute
    );

vattributeInteger *vattributeCreateInteger(
    void
    );

void vattributeDestroyInteger(
    vattributeInteger		*attribute
    );

vloadable *vattributeMakeInteger(
    int				 value
    );

int vattributeGetIntegerValue(
    vattributeInteger		*attribute
    );

void vattributeSetIntegerValue(
    vattributeInteger		*attribute,
    int				 value
    );


/*
 * key stroke attributes:
 */

vattributeKeyStrokeClass *vattributeGetDefaultKeyStrokeClass(
    void
    );

vattributeKeyStrokeClass *vattributeGetKeyStrokeClass(
    vattributeKeyStroke		*attribute
    );

vattribute *vattributeGetKeyStrokeAttribute(
    vattributeKeyStroke		*attribute
    );

vloadable *vattributeGetKeyStrokeLoadable(
    vattributeKeyStroke		*attribute
    );

vinstance *vattributeGetKeyStrokeInstance(
    vattributeKeyStroke		*attribute
    );

vattributeKeyStroke *vattributeCreateKeyStroke(
    void
    );

void vattributeDestroyKeyStroke(
    vattributeKeyStroke		*attribute
    );

vloadable *vattributeMakeKeyStroke(
    vkeyStroke			 value
    );

vkeyStroke vattributeGetKeyStrokeValue(
    vattributeKeyStroke		*attribute
    );

void vattributeSetKeyStrokeValue(
    vattributeKeyStroke		*attribute,
    vkeyStroke			 value
    );


/*
 * tag attributes:
 */

vattributeTagClass *vattributeGetDefaultTagClass(
    void
    );

vattributeTagClass *vattributeGetTagClass(
    vattributeTag		*attribute
    );

vattribute *vattributeGetTagAttribute(
    vattributeTag		*attribute
    );

vloadable *vattributeGetTagLoadable(
    vattributeTag		*attribute
    );

vinstance *vattributeGetTagInstance(
    vattributeTag		*attribute
    );

vattributeTag *vattributeCreateTag(
    void
    );

void vattributeDestroyTag(
    vattributeTag		*attribute
    );

vloadable *vattributeMakeTag(
    const vname			*value
    );

vloadable *vattributeMakeTagScribed(
    vscribe			*value
    );

const vname *vattributeGetTagValue(
    vattributeTag		*attribute
    );

void vattributeSetTagValue(
    vattributeTag		*attribute,
    const vname			*value
    );

void vattributeSetTagValueScribed(
    vattributeTag		*attribute,
    vscribe			*value
    );


/*
 * string attributes:
 */

vattributeStringClass *vattributeGetDefaultStringClass(
    void
    );

vattributeStringClass *vattributeGetStringClass(
    vattributeString		*attribute
    );

vattribute *vattributeGetStringAttribute(
    vattributeString		*attribute
    );

vloadable *vattributeGetStringLoadable(
    vattributeString		*attribute
    );

vinstance *vattributeGetStringInstance(
    vattributeString		*attribute
    );

vattributeString *vattributeCreateString(
    void
    );

void vattributeDestroyString(
    vattributeString		*attribute
    );

vloadable *vattributeMakeString(
    const vchar			*value
    );

vloadable *vattributeMakeStringScribed(
    vscribe			*value
    );

const vchar *vattributeGetStringValue(
    vattributeString		*attribute
    );

vscribe *vattributeScribeStringValue(
    vattributeString		*attribute
    );

void vattributeSetStringValue(
    vattributeString		*attribute,
    const vchar			*value
    );

void vattributeSetStringValueScribed(
    vattributeString		*attribute,
    vscribe			*value
    );


/*
 * rect attributes:
 */

vattributeRectClass *vattributeGetDefaultRectClass(
    void
    );

vattributeRectClass *vattributeGetRectClass(
    vattributeRect		*attribute
    );

vattribute *vattributeGetRectAttribute(
    vattributeRect		*attribute
    );

vloadable *vattributeGetRectLoadable(
    vattributeRect		*attribute
    );

vinstance *vattributeGetRectInstance(
    vattributeRect		*attribute
    );

vattributeRect *vattributeCreateRect(
    void
    );

void vattributeDestroyRect(
    vattributeRect		*attribute
    );

vloadable *vattributeMakeRect(
    const vrect			*value
    );

const vrect *vattributeGetRectValue(
    vattributeRect		*attribute
    );

void vattributeSetRectValue(
    vattributeRect		*attribute,
    const vrect			*value
    );


/*
 * point attributes:
 */

vattributePointClass *vattributeGetDefaultPointClass(
    void
    );

vattributePointClass *vattributeGetPointClass(
    vattributePoint		*attribute
    );

vattribute *vattributeGetPointAttribute(
    vattributePoint		*attribute
    );

vloadable *vattributeGetPointLoadable(
    vattributePoint		*attribute
    );

vinstance *vattributeGetPointInstance(
    vattributePoint		*attribute
    );

vattributePoint *vattributeCreatePoint(
    void
    );

void vattributeDestroyPoint(
    vattributePoint		*attribute
    );

vloadable *vattributeMakePoint(
    const vpoint		*value
    );

const vpoint *vattributeGetPointValue(
    vattributePoint		*attribute
    );

void vattributeSetPointValue(
    vattributePoint		*attribute,
    const vpoint		*value
    );


/*
 * matrix attributes:
 */

vattributeMatrixClass *vattributeGetDefaultMatrixClass(
    void
    );

vattributeMatrixClass *vattributeGetMatrixClass(
    vattributeMatrix		*attribute
    );

vattribute *vattributeGetMatrixAttribute(
    vattributeMatrix		*attribute
    );

vloadable *vattributeGetMatrixLoadable(
    vattributeMatrix		*attribute
    );

vinstance *vattributeGetMatrixInstance(
    vattributeMatrix		*attribute
    );

vattributeMatrix *vattributeCreateMatrix(
    void
    );

void vattributeDestroyMatrix(
    vattributeMatrix		*attribute
    );

vloadable *vattributeMakeMatrix(
    const vmatrix		*value
    );

const vmatrix *vattributeGetMatrixValue(
    vattributeMatrix		*attribute
    );

void vattributeSetMatrixValue(
    vattributeMatrix		*attribute,
    const vmatrix		*value
    );


/*
 * color attributes:
 */

vattributeColorClass *vattributeGetDefaultColorClass(
    void
    );

vattributeColorClass *vattributeGetColorClass(
    vattributeColor		*attribute
    );

vattribute *vattributeGetColorAttribute(
    vattributeColor		*attribute
    );

vloadable *vattributeGetColorLoadable(
    vattributeColor		*attribute
    );

vinstance *vattributeGetColorInstance(
    vattributeColor		*attribute
    );

vattributeColor *vattributeCreateColor(
    void
    );

void vattributeDestroyColor(
    vattributeColor		*attribute
    );

vloadable *vattributeMakeColor(
    const vcolor		*value
    );

vloadable *vattributeMakeColorWithSpec(
    const vcolorSpec		*spec
    );

const vcolor *vattributeGetColorValue(
    vattributeColor		*attribute
    );

const vcolorSpec *vattributeGetColorSpec(
    vattributeColor		*attribute
    );

void vattributeSetColorValue(
    vattributeColor		*attribute,
    const vcolor		*value
    );

void vattributeSetColorValueWithSpec(
    vattributeColor		*attribute,
    const vcolorSpec		*spec
    );


/*
 * font attributes:
 */

vattributeFontClass *vattributeGetDefaultFontClass(
    void
    );

vattributeFontClass *vattributeGetFontClass(
    vattributeFont		*attribute
    );

vattribute *vattributeGetFontAttribute(
    vattributeFont		*attribute
    );

vloadable *vattributeGetFontLoadable(
    vattributeFont		*attribute
    );

vinstance *vattributeGetFontInstance(
    vattributeFont		*attribute
    );

vattributeFont *vattributeCreateFont(
    void
    );

void vattributeDestroyFont(
    vattributeFont		*attribute
    );

vloadable *vattributeMakeFont(
    const vfont		*value
    );

vloadable *vattributeMakeFontWithSpec(
    const vfontspec		*spec
    );

const vfont *vattributeGetFontValue(
    vattributeFont		*attribute
    );

const vfontspec *vattributeGetFontSpec(
    vattributeFont		*attribute
    );

void vattributeSetFontValue(
    vattributeFont		*attribute,
    const vfont			*value
    );

void vattributeSetFontValueWithSpec(
    vattributeFont		*attribute,
    const vfontspec		*spec
    );


/*
 * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * *
 */


struct vattributeContext {
    vobservable			 super;

    vmapping			*tag2attr2value;
};

#define vattributeCONTEXT_CLASS(SUPER, ATTRIBUTE)                         \
    vobservableCLASS(SUPER, ATTRIBUTE)

struct vattributeContextClass {
    vattributeCONTEXT_CLASS(vattributeContextClass, vattributeContext);
};


struct vattributeTyper {
    vloadable			 super;

    vdict			*attr2class;
};

#define vattributeTYPER_CLASS(SUPER, ATTRIBUTE)                         \
    vloadableCLASS(SUPER, ATTRIBUTE)

struct vattributeTyperClass {
    vattributeTYPER_CLASS(vattributeTyperClass, vattributeTyper);
};


#define vattributeCLASS(SUPER, ATTRIBUTE)                                     \
    vloadableCLASS(SUPER, ATTRIBUTE);					      \
    vclassMETHOD(vattributeAPPLY_VALUE,					      \
		 (ATTRIBUTE *attribute, vobject *object,		      \
		  const vname *attributeName))

struct vattributeClass {
    vattributeCLASS(vattributeClass, vattribute);
};


struct vattributeBoolean {
    vattribute			 super;
    vbool			 value;    
};

#define vattributeBOOLEAN_CLASS(SUPER, ATTRIBUTE)                             \
    vattributeCLASS(SUPER, ATTRIBUTE)

struct vattributeBooleanClass {
    vattributeBOOLEAN_CLASS(vattributeBooleanClass, vattributeBoolean);
};


struct vattributeInteger {
    vattribute			 super;
    int				 value;    
};

#define vattributeINTEGER_CLASS(SUPER, ATTRIBUTE)                             \
    vattributeCLASS(SUPER, ATTRIBUTE)

struct vattributeIntegerClass {
    vattributeINTEGER_CLASS(vattributeIntegerClass, vattributeInteger);
};


struct vattributeKeyStroke {
    vattribute			 super;
    vkeyStroke			 value;    
};

#define vattributeKEY_STROKE_CLASS(SUPER, ATTRIBUTE)                          \
    vattributeCLASS(SUPER, ATTRIBUTE)

struct vattributeKeyStrokeClass {
    vattributeKEY_STROKE_CLASS(vattributeKeyStrokeClass, vattributeKeyStroke);
};


struct vattributeTag {
    vattribute			 super;
    const vname			*value;    
};

#define vattributeTAG_CLASS(SUPER, ATTRIBUTE)                                 \
    vattributeCLASS(SUPER, ATTRIBUTE)

struct vattributeTagClass {
    vattributeTAG_CLASS(vattributeTagClass, vattributeTag);
};


struct vattributeString {
    vattribute			 super;
    vstr			*value;    
};

#define vattributeSTRING_CLASS(SUPER, ATTRIBUTE)                              \
    vattributeCLASS(SUPER, ATTRIBUTE)

struct vattributeStringClass {
    vattributeSTRING_CLASS(vattributeStringClass, vattributeString);
};


struct vattributeRect {
    vattribute			 super;
    vrect			 buffer;
    const vrect			*value;    
};

#define vattributeRECT_CLASS(SUPER, ATTRIBUTE)                                \
    vattributeCLASS(SUPER, ATTRIBUTE)

struct vattributeRectClass {
    vattributeRECT_CLASS(vattributeRectClass, vattributeRect);
};


struct vattributePoint {
    vattribute			 super;
    vpoint			 buffer;
    const vpoint		*value;    
};

#define vattributePOINT_CLASS(SUPER, ATTRIBUTE)                               \
    vattributeCLASS(SUPER, ATTRIBUTE)

struct vattributePointClass {
    vattributePOINT_CLASS(vattributePointClass, vattributePoint);
};


struct vattributeMatrix {
    vattribute			 super;
    vmatrix			 buffer;
    const vmatrix		*value;    
};

#define vattributeMATRIX_CLASS(SUPER, ATTRIBUTE)                              \
    vattributeCLASS(SUPER, ATTRIBUTE)

struct vattributeMatrixClass {
    vattributeMATRIX_CLASS(vattributeMatrixClass, vattributeMatrix);
};


struct vattributeColor {
    vattribute			 super;
    vcolorSpec			*spec;
    vcolor			*value;    
};

#define vattributeCOLOR_CLASS(SUPER, ATTRIBUTE)                               \
    vattributeCLASS(SUPER, ATTRIBUTE)

struct vattributeColorClass {
    vattributeCOLOR_CLASS(vattributeColorClass, vattributeColor);
};


struct vattributeFont {
    vattribute			 super;
    vfontspec			*spec;
    vfont			*value;    
};

#define vattributeFONT_CLASS(SUPER, ATTRIBUTE)                               \
    vattributeCLASS(SUPER, ATTRIBUTE)

struct vattributeFontClass {
    vattributeFONT_CLASS(vattributeFontClass, vattributeFont);
};


/*
 * * * * * * * * * * PRIVATE VARIABLE DECLARATIONS * * * * * * * * * *
 */

/*
 * * * * * * * * * * PRIVATE FUNCTION PROTOTYPES * * * * * * * * * *
 */

/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * *
 */

/*
 * attribute contexts
 */

#define vattributeGetContextObservable(x)	vportBASE_OBJECT(x, super)
#define vattributeGetContextLoadable(x) \
    vobservableGetLoadable(vattributeGetContextObservable(x))
#define vattributeGetContextInstance(x) \
    vloadableGetInstance(vattributeGetContextLoadable(x))
#define vattributeGetContextClass(x) \
    ((vattributeContextClass*) \
     vinstanceGetClass(vattributeGetContextInstance(x)))

#define vattributeCreateContextOfClass(c) \
    ((vattributeContext *) vinstanceCreateOfClass((vinstanceClass *)(c)))
#define vattributeCreateContext() \
    vattributeCreateContextOfClass(vattributeGetDefaultContextClass())
#define vattributeInitContextOfClass(x,c) \
    vinstanceInitOfClass(vattributeGetContextInstance(x), (vinstanceClass *)(c))
#define vattributeInitContext(x) \
    vattributeInitContextOfClass((x), vattributeGetDefaultContextClass())
#define vattributeDestroyContext(x) \
    vinstanceDestroy(vattributeGetContextInstance(x))

#define vattributeCloneContext(x) \
    ((vattributeContext *) vloadableClone(vattributeGetContextLoadable(x)))
#define vattributeCopyContext(x,t) \
    vloadableCopy(vattributeGetContextLoadable(x), \
		  vattributeGetContextLoadable(t))
#define vattributeCopyInitContext(x,t) \
    vloadableCopyInit(vattributeGetContextLoadable(x), \
		      vattributeGetContextLoadable(t))

#define vattributeLoadContext(r) \
    ((vattributeContext *) vloadableLoad(r))
#define vattributeLoadInitContext(x,r) \
    vloadableLoadInit(vattributeGetContextLoadable(x), r)
#define vattributeStoreContext(x,r) \
    vloadableStore(vattributeGetContextLoadable(x), r)


/*
 * attribute typers
 */

#define vattributeGetTyperLoadable(t)	vportBASE_OBJECT(t, super)
#define vattributeGetTyperInstance(t) \
    vloadableGetInstance(vattributeGetTyperLoadable(t))
#define vattributeGetTyperClass(t) \
    ((vattributeTyperClass*) \
     vinstanceGetClass(vattributeGetTyperInstance(t)))

#define vattributeCreateTyperOfClass(c) \
    ((vattributeTyper *) vinstanceCreateOfClass((vinstanceClass *)(c)))
#define vattributeCreateTyper() \
    vattributeCreateTyperOfClass(vattributeGetDefaultTyperClass())
#define vattributeInitTyperOfClass(t,c) \
    vinstanceInitOfClass(vattributeGetTyperInstance(t), (vinstanceClass *)(c))
#define vattributeInitTyper(t) \
    vattributeInitTyperOfClass((t), vattributeGetDefaultTyperClass())
#define vattributeDestroyTyper(t) \
    vinstanceDestroy(vattributeGetTyperInstance(t))

#define vattributeCloneTyper(t) \
    ((vattributeTyper *) vloadableClone(vattributeGetTyperLoadable(t)))
#define vattributeCopyTyper(s,t) \
    vloadableCopy(vattributeGetTyperLoadable(s), \
		  vattributeGetTyperLoadable(t))
#define vattributeCopyInitTyper(s,t) \
    vloadableCopyInit(vattributeGetTyperLoadable(s), \
		      vattributeGetTyperLoadable(t))

#define vattributeLoadTyper(r) \
    ((vattributeTyper *) vloadableLoad(r))
#define vattributeLoadInitTyper(t,r) \
    vloadableLoadInit(vattributeGetTyperLoadable(t), r)
#define vattributeStoreTyper(t,r) \
    vloadableStore(vattributeGetTyperLoadable(t), r)


/*
 * attributes
 */

#define vattributeGetLoadable(a)		(a)
#define vattributeGetInstance(a) \
    vloadableGetInstance(vattributeGetLoadable(a))
#define vattributeGetClass(a) \
    ((vattributeClass *) \
     vinstanceGetClass(vattributeGetInstance(a)))

#define vattributeCreateOfClass(c) \
    ((vattribute *) vloadableCreateOfClass((vloadableClass *)(c)))
#define vattributeInitOfClass(a,c) \
    vinstanceInitOfClass(vattributeGetInstance(x), (vinstanceClass *)(c))
#define vattributeDestroy(a) \
    vinstanceDestroy(vattributeGetInstance(a))

#define vattributeClone(a) \
    ((vattribute *) vloadableClone(vattributeGetLoadable(a)))
#define vattributeCopy(a,t) \
    vloadableCopy(vattributeGetLoadable(a), vattributeGetLoadable(t))
#define vattributeCopyInit(a,t) \
    vloadableCopyInit(vattributeGetLoadable(a), vattributeGetLoadable(t))

#define vattributeLoad(r) \
    ((vattribute *) vloadableLoad(r))
#define vattributeLoadInit(a,r) \
    vloadableLoadInit(vattributeGetLoadable(a), r)
#define vattributeStore(a,r) \
    vloadableStore(vattributeGetLoadable(a), r)


/*
 * boolean attributes
 */

#define vattributeGetBooleanAttribute(a)	vportBASE_OBJECT(a, super)
#define vattributeGetBooleanLoadable(a) \
    vattributeGetLoadable(vattributeGetBooleanAttribute(a))
#define vattributeGetBooleanInstance(a) \
    vloadableGetInstance(vattributeGetBooleanLoadable(a))
#define vattributeGetBooleanClass(a) \
    ((vattributeBooleanClass *) \
     vinstanceGetClass(vattributeGetBooleanInstance(a)))

#define vattributeCreateBoolean() \
    ((vattributeBoolean *) vloadableCreateOfClass( \
	    (vloadableClass *) vattributeGetDefaultBooleanClass()))
#define vattributeDestroyBoolean(a) \
    vloadableDestroy(vattributeGetBooleanLoadable(a))

#define vattributeGetBooleanValue(a)	((a)->value)
#define vattributeSetBooleanValue(a,v)	((a)->value = (v))


/*
 * integer attributes
 */

#define vattributeGetIntegerAttribute(a)	vportBASE_OBJECT(a, super)
#define vattributeGetIntegerLoadable(a) \
    vattributeGetLoadable(vattributeGetIntegerAttribute(a))
#define vattributeGetIntegerInstance(a) \
    vloadableGetInstance(vattributeGetIntegerLoadable(a))
#define vattributeGetIntegerClass(a) \
    ((vattributeIntegerClass *) \
     vinstanceGetClass(vattributeGetIntegerInstance(a)))

#define vattributeCreateInteger() \
    ((vattributeInteger *) vloadableCreateOfClass( \
	    (vloadableClass *) vattributeGetDefaultIntegerClass()))
#define vattributeDestroyInteger(a) \
    vloadableDestroy(vattributeGetIntegerLoadable(a))

#define vattributeGetIntegerValue(a)	((a)->value)
#define vattributeSetIntegerValue(a,v)	((a)->value = (v))


/*
 * key stroke attributes
 */

#define vattributeGetKeyStrokeAttribute(a)	vportBASE_OBJECT(a, super)
#define vattributeGetKeyStrokeLoadable(a) \
    vattributeGetLoadable(vattributeGetKeyStrokeAttribute(a))
#define vattributeGetKeyStrokeInstance(a) \
    vloadableGetInstance(vattributeGetKeyStrokeLoadable(a))
#define vattributeGetKeyStrokeClass(a) \
    ((vattributeKeyStrokeClass *) \
     vinstanceGetClass(vattributeGetKeyStrokeInstance(a)))

#define vattributeCreateKeyStroke() \
    ((vattributeKeyStroke *) vloadableCreateOfClass( \
	    (vloadableClass *) vattributeGetDefaultKeyStrokeClass()))
#define vattributeDestroyKeyStroke(a) \
    vloadableDestroy(vattributeGetKeyStrokeLoadable(a))

#define vattributeGetKeyStrokeValue(a)	 ((a)->value)
#define vattributeSetKeyStrokeValue(a,v) ((a)->value = (v))


/*
 * tag attributes
 */

#define vattributeGetTagAttribute(a)		vportBASE_OBJECT(a, super)
#define vattributeGetTagLoadable(a) \
    vattributeGetLoadable(vattributeGetTagAttribute(a))
#define vattributeGetTagInstance(a) \
    vloadableGetInstance(vattributeGetTagLoadable(a))
#define vattributeGetTagClass(a) \
    ((vattributeTagClass *) \
     vinstanceGetClass(vattributeGetTagInstance(a)))

#define vattributeCreateTag() \
    ((vattributeTag *) vloadableCreateOfClass( \
	    (vloadableClass *) vattributeGetDefaultTagClass()))
#define vattributeDestroyTag(a) \
    vloadableDestroy(vattributeGetTagLoadable(a))

#define vattributeGetTagValue(a)	((a)->value)
#define vattributeSetTagValue(a,v)	((a)->value = (v))

#define vattributeMakeTagScribed(v)	\
    vattributeMakeTag(((v) == NULL) ? (const vname *)NULL : vnameInternGlobalScribed(v))
#define vattributeSetTagValueScribed(a,v)	\
    ((a)->value = ((v) == NULL) ? (const vname *)NULL : vnameInternGlobalScribed(v))


/*
 * string attributes
 */

#define vattributeGetStringAttribute(a)		vportBASE_OBJECT(a, super)
#define vattributeGetStringLoadable(a) \
    vattributeGetLoadable(vattributeGetStringAttribute(a))
#define vattributeGetStringInstance(a) \
    vloadableGetInstance(vattributeGetStringLoadable(a))
#define vattributeGetStringClass(a) \
    ((vattributeStringClass *) \
     vinstanceGetClass(vattributeGetStringInstance(a)))

#define vattributeCreateString() \
    ((vattributeString *) vloadableCreateOfClass( \
	    (vloadableClass *) vattributeGetDefaultStringClass()))
#define vattributeDestroyString(a) \
    vloadableDestroy(vattributeGetStringLoadable(a))

#define vattributeGetStringValue(a)	((a)->value)
#define vattributeScribeStringValue(a) \
    vcharScribe(((a)->value == NULL) ? vcharGetEmptyString() : (a)->value)

#define vattributeMakeString(v) \
    vattributeMakeStringScribed(((v) == NULL) ? (vscribe *)NULL : vcharScribe(v))
#define vattributeSetStringValue(a, v) \
    vattributeSetStringValueScribed(a, ((v) == NULL) ? (vscribe *)NULL : vcharScribe(v))


/*
 * rect attributes
 */

#define vattributeGetRectAttribute(a)		vportBASE_OBJECT(a, super)
#define vattributeGetRectLoadable(a) \
    vattributeGetLoadable(vattributeGetRectAttribute(a))
#define vattributeGetRectInstance(a) \
    vloadableGetInstance(vattributeGetRectLoadable(a))
#define vattributeGetRectClass(a) \
    ((vattributeRectClass *) \
     vinstanceGetClass(vattributeGetRectInstance(a)))

#define vattributeCreateRect() \
    ((vattributeRect *) vloadableCreateOfClass( \
	    (vloadableClass *) vattributeGetDefaultRectClass()))
#define vattributeDestroyRect(a) \
    vloadableDestroy(vattributeGetRectLoadable(a))

#define vattributeGetRectValue(a)	((a)->value)


/*
 * point attributes
 */

#define vattributeGetPointAttribute(a)		vportBASE_OBJECT(a, super)
#define vattributeGetPointLoadable(a) \
    vattributeGetLoadable(vattributeGetPointAttribute(a))
#define vattributeGetPointInstance(a) \
    vloadableGetInstance(vattributeGetPointLoadable(a))
#define vattributeGetPointClass(a) \
    ((vattributePointClass *) \
     vinstanceGetClass(vattributeGetPointInstance(a)))

#define vattributeCreatePoint() \
    ((vattributePoint *) vloadableCreateOfClass( \
	    (vloadableClass *) vattributeGetDefaultPointClass()))
#define vattributeDestroyPoint(a) \
    vloadableDestroy(vattributeGetPointLoadable(a))

#define vattributeGetPointValue(a)	((a)->value)


/*
 * matrix attributes
 */

#define vattributeGetMatrixAttribute(a)		vportBASE_OBJECT(a, super)
#define vattributeGetMatrixLoadable(a) \
    vattributeGetLoadable(vattributeGetMatrixAttribute(a))
#define vattributeGetMatrixInstance(a) \
    vloadableGetInstance(vattributeGetMatrixLoadable(a))
#define vattributeGetMatrixClass(a) \
    ((vattributeMatrixClass *) \
     vinstanceGetClass(vattributeGetMatrixInstance(a)))

#define vattributeCreateMatrix() \
    ((vattributeMatrix *) vloadableCreateOfClass( \
	    (vloadableClass *) vattributeGetDefaultMatrixClass()))
#define vattributeDestroyMatrix(a) \
    vloadableDestroy(vattributeGetMatrixLoadable(a))

#define vattributeGetMatrixValue(a)	((a)->value)


/*
 * color attributes
 */

#define vattributeGetColorAttribute(a)		vportBASE_OBJECT(a, super)
#define vattributeGetColorLoadable(a) \
    vattributeGetLoadable(vattributeGetColorAttribute(a))
#define vattributeGetColorInstance(a) \
    vloadableGetInstance(vattributeGetColorLoadable(a))
#define vattributeGetColorClass(a) \
    ((vattributeColorClass *) \
     vinstanceGetClass(vattributeGetColorInstance(a)))

#define vattributeCreateColor() \
    ((vattributeColor *) vloadableCreateOfClass( \
	    (vloadableClass *) vattributeGetDefaultColorClass()))
#define vattributeDestroyColor(a) \
    vloadableDestroy(vattributeGetColorLoadable(a))

#define vattributeGetColorValue(a)	((a)->value)
#define vattributeGetColorSpec(a)	((a)->spec)


/*
 * font attributes
 */

#define vattributeGetFontAttribute(a)		vportBASE_OBJECT(a, super)
#define vattributeGetFontLoadable(a) \
    vattributeGetLoadable(vattributeGetFontAttribute(a))
#define vattributeGetFontInstance(a) \
    vloadableGetInstance(vattributeGetFontLoadable(a))
#define vattributeGetFontClass(a) \
    ((vattributeFontClass *) \
     vinstanceGetClass(vattributeGetFontInstance(a)))

#define vattributeCreateFont() \
    ((vattributeFont *) vloadableCreateOfClass( \
	    (vloadableClass *) vattributeGetDefaultFontClass()))
#define vattributeDestroyFont(a) \
    vloadableDestroy(vattributeGetFontLoadable(a))

#define vattributeGetFontValue(a)	((a)->value)
#define vattributeGetFontSpec(a)	((a)->spec)


/*
 * * * * * * * * * * PRIVATE FUNCTION MESSAGE DEFINITIONS * * * * * * * * * *
 */

#define vattributeApplyValue(a, o, n) \
    vclassSend(vattributeGetClass(a), vattributeAPPLY_VALUE, (a, o, n))


vportEND_CPLUSPLUS_EXTERN_C


#ifdef  vportNULL_HEADER
#ifdef  vattributeHEADER
#undef  vattributeHEADER
#endif
#define vattributeHEADER vportNULL_HEADER
#endif


#endif /* #ifndef vattributeINCLUDED */


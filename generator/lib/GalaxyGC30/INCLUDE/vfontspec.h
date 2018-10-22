/* $Id: vfontspec.h,v 1.3 1997/06/19 00:34:30 robert Exp $ */

/************************************************************

    vfontspec.h

    C Interface file for the Class Manager loadable objects

    (c) Copyright Visix Software Inc.
    All rights reserved

************************************************************/

#ifndef vfontspecINCLUDED
#define vfontspecINCLUDED

#ifndef  vportINCLUDED
#include <vport.h>
#endif

#ifndef  vstdioINCLUDED
#include vstdioHEADER
#endif

#ifndef  vdebugINCLUDED
#include vdebugHEADER
#endif

#ifndef  vstrINCLUDED
#include vstrHEADER
#endif

#ifndef  vnameINCLUDED
#include vnameHEADER
#endif

#ifndef  vloadableINCLUDED
#include vloadableHEADER
#endif

#ifndef  vmatrixINCLUDED
#include vmatrixHEADER
#endif

#ifndef  viteratorINCLUDED
#include viteratorHEADER
#endif

#ifndef  vfontINCLUDED
#include vfontHEADER
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * * * * * * * * * * PUBLIC CONSTANT DEFINITIONS  * * * * * * * * * *
 */

enum {
  vfontspecDEFAULT_BIAS			= 0,

  vfontspecSTRONGEST_BIAS		= 1,
  vfontspecDEFAULT_MONOSPACE_BIAS	= 20,
  vfontspecDEFAULT_BITMAP_BIAS		= 40,
  vfontspecDEFAULT_FAMILY_BIAS		= 60,
  vfontspecDEFAULT_FOUNDRY_BIAS		= 80,
  vfontspecDEFAULT_ENCODING_BIAS	= 100,
  vfontspecDEFAULT_FACE_BIAS		= 120,
  vfontspecDEFAULT_SIZE_BIAS		= 140,
  vfontspecDEFAULT_MATRIX_BIAS		= 160,
  vfontspecWEAKEST_BIAS			= 255
};

/*
 * * * * * * * * * * PUBLIC TYPE DEFINITIONS * * * * * * * * * *
 */

typedef struct vfontspec                vfontspec;
typedef struct vfontspecClass           vfontspecClass;

typedef struct vfontspecMatchIterator          vfontspecMatchIterator;
typedef struct vfontspecMatchIteratorClass     vfontspecMatchIteratorClass;

/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */

void vfontspecStartup(void);


/*
 * font specs
 */

vfontspecClass *vfontspecGetDefaultClass(
    void
    );

vfontspecClass *vfontspecGetClass(
    vfontspec                  *fontspec
    );

vloadable *vfontspecGetLoadable(
    vfontspec                  *fontspec
    );

vinstance *vfontspecGetInstance(
    vfontspec                  *fontspec
    );

vfontspec *vfontspecCreate(
    void
    );

vfontspec *vfontspecCreateOfClass(
    vfontspecClass              *clas
    );

void vfontspecInit(
    vfontspec                   *fontspec
    );

void vfontspecInitOfClass(
    vfontspec                   *fontspec,
    vfontspecClass              *clas
    );

void vfontspecDestroy(
    vfontspec                   *fontspec
    );

vfontspec *vfontspecClone(
    vfontspec                   *fontspec
    );

void vfontspecCopyInit(
    vfontspec                   *fontspec,
    vfontspec                   *target
    );

void vfontspecCopy(
    vfontspec                   *fontspec,
    vfontspec                   *target
    );

vfontspec *vfontspecLoad(
    vresource                    resource
    );

void vfontspecLoadInit(
    vfontspec                   *fontspec,
    vresource                    resource
    );

void vfontspecStore(
    vfontspec                   *fontspec,
    vresource                    resource
    );

void vfontspecDump(
    vfontspec                   *fontspec,
    FILE                        *stream
    );

vfontspec *vfontspecGetDefaultSpec(
    void
    );

const vchar *vfontspecGetDefaultBiasString(
    void
    );

void vfontspecSetDefaultBiasString(
    const vchar			*biasString
    );

void vfontspecSetDefaultBiasStringScribed(
    vscribe			*biasString
    );

void vfontspecClearAllBiases(
    vfontspec			*spec
    );

void vfontspecAddFamilyBias(
    vfontspec			*spec,
    const vchar			*familyName,
    int				 biasToward,
    int				 biasStrength
    );

void vfontspecAddFamilyBiasScribed(
    vfontspec			*spec,
    vscribe			*familyName,
    int				 biasToward,
    int				 biasStrength
    );

void vfontspecAddFoundryBias(
    vfontspec			*spec,
    const vchar			*foundry,
    int				 biasToward,
    int				 biasStrength
    );

void vfontspecAddFoundryBiasScribed(
    vfontspec			*spec,
    vscribe			*foundry,
    int				 biasToward,
    int				 biasStrength
    );

void vfontspecAddEncodingBias(
    vfontspec			*spec,
    const vchar			*encoding,
    int				 biasToward,
    int				 biasStrength
    );

void vfontspecAddEncodingBiasScribed(
    vfontspec			*spec,
    vscribe			*encoding,
    int				 biasToward,
    int				 biasStrength
    );

void vfontspecAddFaceBias(
    vfontspec			*spec,
    const vchar			*faceName,
    int				 biasToward,
    int				 biasStrength
    );

void vfontspecAddFaceBiasScribed(
    vfontspec			*spec,
    vscribe			*faceName,
    int				 biasToward,
    int				 biasStrength
    );

void vfontspecAddSizeBias(
    vfontspec			*spec,
    double			 size,
    int				 biasToward,
    int				 biasStrength
    );

void vfontspecAddMatrixBias(
    vfontspec			*spec,
    vmatrix			*matrix,
    int				 biasToward,
    int				 biasStrength
    );

void vfontspecAddMonospaceBias(
    vfontspec			*spec,
    int				 biasToward,
    int				 biasStrength
    );

void vfontspecAddBitmapBias(
    vfontspec			*spec,
    int				 biasToward,
    int				 biasStrength
    );

const vchar *vfontspecGetBiasString(
    vfontspec			*spec
    );

vscribe *vfontspecScribeBiasString(
    vfontspec			*spec
    );

int vfontspecGetBiasCount(
    vfontspec			*spec
    );

vscribe *vfontspecScribeBiasAt(
    vfontspec			*spec,
    int				 index
    );

vscribe *vfontspecScribeBiasTypeAt(
    vfontspec			*spec,
    int				 index
    );

vscribe *vfontspecScribeBiasValueAt(
    vfontspec			*spec,
    int				 index
    );

int vfontspecGetBiasStrengthAt(
    vfontspec			*spec,
    int				 index
    );

vbool vfontspecIsBiasTowardAt(
    vfontspec			*spec,
    int				 index
    );

void vfontspecAddBias(
    vfontspec			*spec,
    const vchar			*biasType,
    const vchar			*biasValue,
    int				 biasToward,
    int				 biasStrength
    );

void vfontspecAddBiasScribed(
    vfontspec			*spec,
    vscribe			*biasType,
    vscribe			*biasValue,
    int				 biasToward,
    int				 biasStrength
    );

void vfontspecSetBiasString(
    vfontspec			*spec,
    const vchar			*biasString
    );

void vfontspecSetBiasStringScribed(
    vfontspec			*spec,
    vscribe			*biasString
    );

vfont *vfontspecDetermineFont(
    vfontspec			*spec
    );

vfont *vfontspecDetermineRelativeFont(
    vfontspec			*spec,
    vfont			*relativeTo
    );

/*
 * font spec match iterator
 */

vfontspecMatchIteratorClass *vfontspecGetDefaultMatchIteratorClass(
    void
    );

vfontspecMatchIteratorClass *vfontspecGetMatchIteratorClass(
    vfontspecMatchIterator	*iterator
    );

viterator *vfontspecGetMatchIteratorIterator(
    vfontspecMatchIterator	*iterator
    );

void vfontspecInitMatchIterator(
    vfontspecMatchIterator	*iterator,
    vfontspec			*spec,
    int				 ignoreUnmeetable,
    int				 considerDefaults
    );

void vfontspecSetMatchIteratorIgnoreUnmeetable(
    vfontspecMatchIterator	*iterator,
    int				 ignoreUnmeetable
    );

vbool vfontspecHasMatchIteratorIgnoreUnmeetable(
    vfontspecMatchIterator	*iterator
    );

void vfontspecSetMatchIteratorConsiderDefaults(
    vfontspecMatchIterator	*iterator,
    int				 considerDefaults
    );

vbool vfontspecHasMatchIteratorConsiderDefaults(
    vfontspecMatchIterator	*iterator
    );

void vfontspecNextMatchIterator(
    vfontspecMatchIterator	*iterator
    );

vfontFace *vfontspecGetMatchIteratorFace(
    vfontspecMatchIterator	*iterator
    );

vfont *vfontspecGetMatchIteratorFont(
    vfontspecMatchIterator	*iterator
    );

void vfontspecDestroyMatchIterator(
    vfontspecMatchIterator	*iterator
    );


/*
 * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * *
 */

typedef struct _vfontspecAttribute	_vfontspecAttribute;

struct _vfontspecAttribute {
    int                  type;
    union {
	struct {
	    const vname *n1;
	    const vname *n2;
	} name;
	const vmatrix   *mtx;
	int              id;
    } u;
};


struct vfontspec {
    vloadable               object;

    vstr		   *biases;
    vstr		   *strengths;

    _vfontspecAttribute    *compiled;
    int			    compiledCount;
    vmatrix		    matrix;
};

#define vfontspecCLASS(SUPER, FONTSPEC)                                       \
    vloadableCLASS(SUPER, FONTSPEC)

struct vfontspecClass {
    vfontspecCLASS(vfontspecClass, vfontspec);
};


struct vfontspecMatchIterator {
    viterator               iterator;

    vbool		    ignoreUnmeetable;
    vbool		    considerDefaults;
    vfontFace		  **matchedFaces;
};

#define vfontspecMATCH_ITERATOR_CLASS(SUPER,ITERATOR)                         \
    viteratorCLASS(SUPER, ITERATOR)

struct vfontspecMatchIteratorClass {
    vfontspecMATCH_ITERATOR_CLASS(vfontspecMatchIteratorClass,
				  vfontspecMatchIterator);
};


/*
 * * * * * * * * * * PRIVATE FUNCTION PROTOTYPES * * * * * * * * * *
 */

/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * *
 */

#define vfontspecGetLoadable(i) 	vportBASE_OBJECT(i, object)
#define vfontspecGetInstance(i) \
    vloadableGetInstance(vfontspecGetLoadable(i))
#define vfontspecGetClass(i) \
    ((vfontspecClass *) vinstanceGetClass(vfontspecGetInstance(i)))

#define vfontspecCreateOfClass(c) \
    ((vfontspec *) vinstanceCreateOfClass((vinstanceClass *)(c)))
#define vfontspecCreate() \
    vfontspecCreateOfClass(vfontspecGetDefaultClass())
#define vfontspecInitOfClass(i,c) \
    vinstanceInitOfClass(vfontspecGetInstance(i), (vinstanceClass *)(c))
#define vfontspecInit(i) \
    vfontspecInitOfClass(i, vfontspecGetDefaultClass())
#define vfontspecDestroy(i) \
    vinstanceDestroy(vfontspecGetInstance(i))

#define vfontspecClone(i) \
    ((vfontspec *) vloadableClone(vfontspecGetLoadable(i)))
#define vfontspecCopy(i,t) \
    vloadableCopy(vfontspecGetLoadable(i), vfontspecGetLoadable(t))
#define vfontspecCopyInit(i,t) \
    vloadableCopyInitOfSubclass(vfontspecGetLoadable(i), \
				vfontspecGetLoadable(t), \
		(vloadableClass *) vfontspecGetDefaultClass())

#define vfontspecLoad(r) \
    ((vfontspec *) vloadableLoadOfSubclass(r, \
		(vloadableClass *) vfontspecGetDefaultClass()))
#define vfontspecLoadInit(i,r) \
    vloadableLoadInitOfSubclass(vfontspecGetLoadable(i), (r), \
		(vloadableClass *) vfontspecGetDefaultClass())
#define vfontspecStore(i,r) \
    vloadableStore(vfontspecGetLoadable(i), (r))

#define vfontspecDump(i,s) \
    vloadableDump(vfontspecGetLoadable(i), (s))


#define vfontspecSetDefaultBiasString(b) \
    vfontspecSetDefaultBiasStringScribed(vcharScribe(b))

#define vfontspecAddFamilyBias(s, b, t, n) \
    vfontspecAddFamilyBiasScribed(s, vcharScribe(b), t, n)
#define vfontspecAddFoundryBias(s, b, t, n) \
    vfontspecAddFoundryBiasScribed(s, vcharScribe(b), t, n)
#define vfontspecAddEncodingBias(s, b, t, n) \
    vfontspecAddEncodingBiasScribed(s, vcharScribe(b), t, n)
#define vfontspecAddFaceBias(s, b, t, n) \
    vfontspecAddFaceBiasScribed(s, vcharScribe(b), t, n)
#define vfontspecSetBiasString(s, b) \
    vfontspecSetBiasStringScribed(s, vcharScribe(b))


#define vfontspecGetMatchIteratorIterator(i) \
    vportBASE_OBJECT(i, iterator)
#define vfontspecGetMatchIteratorClass(i) \
    ((vfontspecMatchIteratorClass *) \
     viteratorGetClass(vfontspecGetMatchIteratorIterator(i)))

#define vfontspecDestroyMatchIterator(i) \
    viteratorDestroyGroup(vfontspecGetMatchIteratorGroupIterator(i))
#define vfontspecNextMatchIterator(i) \
    viteratorNext(vfontspecGetMatchIteratorIterator(i))
#define vfontspecGetMatchIteratorFace(i) \
    ((vfontFace *) viteratorGetElement(vfontspecGetMatchIteratorIterator(i)))

#define vfontspecSetMatchIteratorIgnoreUnmeetable(i,u) \
    ((i)->ignoreUnmeetable = (u))
#define vfontspecHasMatchIteratorIgnoreUnmeetable(i) \
    ((i)->ignoreUnmeetable)

#define vfontspecSetMatchIteratorConsiderDefaults(i,u) \
    ((i)->considerDefaults = (u))
#define vfontspecHasMatchIteratorConsiderDefaults(i) \
    ((i)->considerDefaults)


/*
 * * * * * * * * * * PRIVATE FUNCTION MESSAGE DEFINITIONS * * * * * * * * * *
 */


vportEND_CPLUSPLUS_EXTERN_C


#endif /* #ifndef vfontspecINCLUDED */

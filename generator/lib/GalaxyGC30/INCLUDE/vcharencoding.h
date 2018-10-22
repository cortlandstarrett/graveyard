/************************************************************

    vcharencoding.h

    C Interface file for font encoding information

    (c) Copyright Visix Software Inc.
    All rights reserved

************************************************************/
#ifndef vcharencodingINCLUDED
#define vcharencodingINCLUDED

#ifndef vportINCLUDED
#include <vport.h>
#endif

#ifndef vcharINCLUDED
#include vcharHEADER
#endif

#ifndef vnameINCLUDED
#include vnameHEADER
#endif

#ifndef vresourceINCLUDED
#include vresourceHEADER
#endif

#ifndef vinstanceINCLUDED
#include vinstanceHEADER
#endif

#ifndef vloadableINCLUDED
#include vloadableHEADER
#endif

#ifndef vsequenceINCLUDED
#include vsequenceHEADER
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * * * * * * * * * * PUBLIC CONSTANT DEFINITIONS * * * * * * * * * *
 */
enum {
     vcharencodingONE_BYTE,
     vcharencodingTWO_BYTE_SHORT,
     vcharencodingTWO_BYTE_ORDERED_SHORT,
     vcharencodingMULTI_BYTE
};

/*
 * * * * * * * * * * PUBLIC TYPE DEFINITIONS * * * * * * * * * *
 */

typedef struct vcharencoding              vcharencoding;
typedef struct vcharencodingClass         vcharencodingClass;

typedef struct vcharencodingString        vcharencodingString;

typedef vsequence			  vcharencodingSequence;
typedef vsequenceClass                    vcharencodingSequenceClass;

typedef int (*vcharencodingExportCharacterProc)(int);
typedef vchar (*vcharencodingImportCharacterProc)(int);

/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */

/* general manager routines  */

void vcharencodingStartup(
    void
    );

void vcharencodingRegisterMasterEncodings(
    vcharencodingSequence             *eSequence
    );

vcharencodingSequence *vcharencodingGetMasterEncodings(
    void
    );

vcharencodingString **vcharencodingConvertString(
    vcharencoding                     *base,
    const vchar                       *str
    );

vcharencodingString **vcharencodingConvertSizedString(
    vcharencoding                     *base,
    const vchar                       *str,
    size_t                             count     
    );

vcharencodingString **vcharencodingSizedConvertSizedString(
    vcharencoding                     *base,
    size_t                             maxLength,
    const vchar                       *str,
    size_t                             count     
    );

vcharencodingString **vcharencodingGetStringsStart(
    void
    );

vcharencodingString **vcharencodingGetStringsEnd(
    void
    );

void vcharencodingFreeStrings(
    void
    );

/* vcharencodingSequence routines */

vcharencodingSequenceClass *vcharencodingSequenceGetDefaultClass(
    void
    );

vinstance *vcharencodingSequenceGetInstance(
    vcharencodingSequence                 *eSequence
    );

vloadable *vcharencodingSequenceGetLoadable(
    vcharencodingSequence                 *eSequence
    );

vobservable *vcharencodingSequenceGetObservable(
    vcharencodingSequence                 *eSequence
    );

vsequence *vcharencodingSequenceGetSequence(
    vcharencodingSequence                 *eSequence
    );

vcharencodingSequenceClass *vcharencodingSequenceGetClass(
    vcharencodingSequence                 *eSequence
    );

vcharencodingSequence *vcharencodingSequenceCreateOfClass(
    vcharencodingSequenceClass             *clas
    );

void vcharencodingSequenceInitOfClass(
    vcharencodingSequence		   *eSequence,
    vcharencodingSequenceClass             *clas
    );

vcharencodingSequence *vcharencodingSequenceCreate(
    void
    );

void vcharencodingSequenceInit(
    vcharencodingSequence			*eSequence
    );

void vcharencodingSequenceDestroy(
    vcharencodingSequence			*eSequence
    );

vcharencodingSequence *vcharencodingSequenceClone(
    vcharencodingSequence			*eSequence
    );

void vcharencodingSequenceCopy(
    vcharencodingSequence			*source,
    vcharencodingSequence			*target
    );

void vcharencodingSequenceCopyInit(
    vcharencodingSequence			*source,
    vcharencodingSequence			*target
    );

vcharencodingSequence *vcharencodingSequenceLoad(
    vresource					*resource
    );

void vcharencodingSequenceLoadInit(
    vcharencodingSequence			*eSequence,
    vresource					*resource
    );

void vcharencodingSequenceStore(
    vcharencodingSequence			*eSequence,
    vresource			 		 resource
    );

void vcharencodingSequenceAppendEncodingShared(
    vcharencodingSequence			*eSequence,
    vcharencoding				*encoding
    );

void vcharencodingSequenceAppendEncodingOwned(
    vcharencodingSequence			*eSequence,
    vcharencoding				*encoding
    );

void vcharencodingSequenceInsertEncodingShared(
    vcharencodingSequence			*eSequence,
    int						 index,
    vcharencoding				*encoding
    );

void vcharencodingSequenceInsertEncodingOwned(
    vcharencodingSequence			*eSequence,
    int						 index,
    vcharencoding				*encoding
    );

vcharencoding *vcharencodingSequenceRemoveEncodingAt(
    vcharencodingSequence			*eSequence,
    int						 index
    );

vcharencoding *vcharencodingSequenceRemoveEncoding(
    vcharencodingSequence			*eSequence,
    vcharencoding				*encoding
    );

vcharencoding *vcharencodingSequenceReplaceEncodingAtShared(
    vcharencodingSequence			*eSequence,
    int						 index,
    vcharencoding				*encoding
    );

vcharencoding *vcharencodingSequenceReplaceEncodingAtOwned(
    vcharencodingSequence			*eSequence,
    int						 index,
    vcharencoding				*encoding
    );

int vcharencodingSequenceGetEncodingCount(
    vcharencodingSequence			*eSequence
    );

vcharencoding *vcharencodingSequenceGetEncodingAt(
    vcharencodingSequence			*eSequence,
    int						 index
    );

int vcharencodingSequenceGetEncodingIndex(
    vcharencodingSequence			*eSequence,
    vcharencoding				*encoding
    );

void vcharencodingSequenceMoveIndex(
    vcharencodingSequence			*eSequence,
    int						 currentIndex,
    int						 newIndex
    );

void vcharencodingSequenceMoveEncoding(
    vcharencodingSequence			*eSequence,
    vcharencoding				*encoding,
    int						 index
    );

vbool vcharencodingSequenceIsIndexOwned(
    vcharencodingSequence			*eSequence,
    int						 index
    );

void vcharencodingSequenceSetIndexOwned(
    vcharencodingSequence			*eSequence,
    int						 index,
    int						 owned
    );

void vcharencodingSequenceDump(
    vcharencodingSequence                 *eSequence,
    FILE                          *stream
    );


/* vcharencoding routines */

vcharencodingClass *vcharencodingGetDefaultClass(
    void
    );

vcharencoding *vcharencodingCreateOfClass(
    vcharencodingClass                *clas
    );

void vcharencodingInitOfClass(
    vcharencoding                     *encoding,
    vcharencodingClass                *clas
    );

vcharencoding *vcharencodingCreate(
    void
    );

void vcharencodingInit(
    vcharencoding                     *encoding
    );

void vcharencodingDestroy(
    vcharencoding                     *encoding
    );

vcharencodingClass *vcharencodingGetClass(
    vcharencoding                     *encoding
    );

vinstance *vcharencodingGetInstance(
    vcharencoding                       *encoding
    );

vloadable *vcharencodingGetLoadable(
    vcharencoding                       *encoding
    );

vcharencoding *vcharencodingClone(
    vcharencoding			*encoding
    );

void vcharencodingCopyInit(
    vcharencoding			*encoding,
    vcharencoding			*target
    );

vcharencoding *vcharencodingLoad(
    vresource				 resource
    );

void vcharencodingLoadInit(
    vcharencoding			*encoding,
    vresource				 resource
    );

void vcharencodingCopy(
    vcharencoding			*encoding,
    vcharencoding			*target
    );

void vcharencodingStore(
    vcharencoding		        *encoding,
    vresource				 resource
    );

void vcharencodingDump(
    vcharencoding                      *encoding,
    FILE                               *stream
    );

const vname *vcharencodingGetName(
    vcharencoding                     *encoding
    );

const vname *vcharencodingGetTag(
    vcharencoding		      *encoding
    );

void vcharencodingSetTag(
    vcharencoding		      *encoding,
    const vname			      *tag
    );

const vname *vcharencodingGetDisplayName(
    vcharencoding                     *encoding
    );

int vcharencodingGetByteType(
    vcharencoding                     *encoding
    );

void vcharencodingSetName(
    vcharencoding		      *encoding,
    const vname			      *name
    );

void vcharencodingSetDisplayName(
    vcharencoding		      *encoding,
    const vname			      *dname
    );

void vcharencodingSetByteType(
    vcharencoding                     *encoding,
    int                                type		      
    );

vcharencodingExportCharacterProc vcharencodingGetExportCharacterFunc(
    vcharencoding                     *encoding
    );

vcharencodingImportCharacterProc vcharencodingGetImportCharacterFunc(
    vcharencoding                     *encoding
    );

void vcharencodingSetExportCharacterFunc(
    vcharencoding                     *encoding,
    vcharencodingExportCharacterProc   export
    );

void vcharencodingSetImportCharacterFunc(
    vcharencoding                     *encoding,
    vcharencodingImportCharacterProc   import
    );

int vcharencodingExportCharacter(
    vcharencoding                     *encoding,
    int                                c
    );

vchar vcharencodingImportCharacter(
    vcharencoding                     *encoding,
    int                                c
    );

vcharencodingSequence *vcharencodingGetAssocSequence(
    vcharencoding                     *encoding
    );

void vcharencodingSetAssocSequence(
    vcharencoding                     *encoding,
    vcharencodingSequence             *eSequence
    );

/* vcharencodingString routines */

unsigned char *vcharencodingGetStringChars(
    vcharencodingString *estr
    );

vcharencoding *vcharencodingGetStringEncoding(
    vcharencodingString *estr
    );

size_t vcharencodingGetStringLength(
    vcharencodingString *estr
    );

/*
 * * * * * * * * * * PRIVATE CONSTANT DEFINITIONS * * * * * * * * * *
 */


/*
 * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * *
 */

struct vcharencoding {
   vloadable			      super;

   const vname			     *name;
   const vname			     *displayName;
   int				      byteType;
   vcharencodingExportCharacterProc   vcharTo;
   vcharencodingImportCharacterProc   vcharFrom;
   vcharencodingSequence	     *assoc;
/*   vcharencodingsys		     *sys; */
};

#define vcharencodingCLASS(CLASS, ENCODING)                                 \
    vloadableCLASS(CLASS, ENCODING)

struct vcharencodingClass
{
  vcharencodingCLASS(vcharencodingClass, vcharencoding);
};

#define vcharencodingSequenceCLASS(CLASS, SEQUENCE)                           \
    vsequenceCLASS(CLASS, SEQUENCE)
    
struct vcharencodingString {
   vcharencoding                *encoding;
   unsigned char                *str;
   size_t                        len;
};


/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * *
 */

/*
 *   Static methods
 */

#define vcharencodingConvertString(e, s) \
    vcharencodingSizedConvertSizedString((e), 0, (s), vcharLength(s))
#define vcharencodingConvertSizedString(e, s, l) \
    vcharencodingSizedConvertSizedString((e), 0, (s), (l))

/*
 * vcharencoding
 */

#define vcharencodingGetLoadable(e)  vportBASE_OBJECT(e, super)
#define vcharencodingGetInstance(e)                                           \
    vloadableGetInstance(vcharencodingGetLoadable(e))
#define vcharencodingGetClass(e)                                              \
    ((vcharencoding*)vinstanceGetClass(vcharencodingGetInstance(e)))

#define vcharencodingCreateOfClass(c)                                         \
    ((vcharencoding*)vinstanceCreateOfClass((vinstanceClass*)(c)))
#define vcharencodingCreate()                                                 \
    vcharencodingCreateOfClass(vcharencodingGetDefaultClass())
#define vcharencodingInitOfClass(e, c)                                        \
    vinstanceInitOfClass(vcharencodingGetInstance(e), (vinstanceClass *)(c))
#define vcharencodingInit(e)                                                  \
    vcharencodingInitOfClass(e, vcharencodingGetDefaultClass())
#define vcharencodingDestroy(e)                                               \
    vinstanceDestroy(vcharencodingGetInstance(e))

#define vcharencodingClone(e)                                                 \
    ((vcharencoding *) vloadableCloneOfSubclass(vcharencodingGetLoadable(e),  \
      (vloadableClass *) vcharencodingGetDefaultClass()))
#define vcharencodingCopy(e,t)                                                \
    vloadableCopy(vcharencodingGetLoadable(s), vcharencodingGetLoadable(t))
#define vcharencodingCopyInit(e,t)                                            \
    vloadableCopyInitOfSubclass(vcharencodingGetLoadable(e),                  \
				vcharencodingGetLoadable(t),                  \
			(vloadableClass *) vcharencodingGetDefaultClass())
#define vcharencodingLoad(r)                                                  \
    ((vcharencoding *) vloadableLoadOfSubclass(r,                             \
			(vloadableClass *) vcharencodingGetDefaultClass()))
#define vcharencodingLoadInit(e,r)                                            \
    vloadableLoadInitOfSubclass(vcharencodingGetLoadable(e), (r),             \
			(vloadableClass *) vcharencodingGetDefaultClass())
#define vcharencodingStore(e,r)                                               \
    vloadableStore(vcharencodingGetLoadable(e), (r))
#define vcharencodingDump(e,s)                                                \
    vloadableDump(vcharencodingGetLoadable(e), (s))
#define vcharencodingGetTag(e) \
    vloadableGetTag(vcharencodingGetLoadable(e))
#define vcharencodingSetTag(e,n) \
    vloadableSetTag(vcharencodingGetLoadable(e), (n))

#define vcharencodingGetName(e)                ((e)->name)
#define vcharencodingGetDisplayName(e)         ((e)->displayName)
#define vcharencodingGetByteType(e)            ((e)->byteType)
#define vcharencodingGetExportCharacterFunc(e) ((e)->vcharTo)
#define vcharencodingGetImportCharacterFunc(e) ((e)->vcharFrom)
#define vcharencodingExportCharacter(e, c)     ((e)->vcharTo)(c)
#define vcharencodingImportCharacter(e, c)     ((e)->vcharFrom)(c)
#define vcharencodingGetAssocSequence(e)       ((e)->assoc)

/*
 * vcharencodingSequence
 */

#define vcharencodingSequenceGetSequence(s)				      \
    ((vsequence*)(s))
#define vcharencodingSequenceGetInstance(s)				      \
    vsequenceGetInstance(vcharencodingSequenceGetSequence(s))
#define vcharencodingSequenceGetLoadable(s)				      \
    vsequenceGetLoadable(vcharencodingSequenceGetSequence(s))
#define vcharencodingSequenceGetObservable(s)				      \
    vsequenceGetObservable(vcharencodingSequenceGetSequence(s))
#define vcharencodingSequenceGetClass(s)				      \
    ((vcharencodingSequenceClass*)					      \
     vsequenceGetClass((vcharencodingSequenceGetSequence(s))))
#define vcharencodingSequenceCreateOfClass(c)				      \
    ((vcharencodingSequence*)vsequenceCreateOfClass((vsequenceClass*)(c)))
#define vcharencodingSequenceCreate()					      \
    vcharencodingSequenceCreateOfClass(vcharencodingSequenceGetDefaultClass())
#define vcharencodingSequenceInitOfClass(s, c)				      \
    vsequenceInitOfClass(vcharencodingSequenceGetSequence(s),		      \
			 (vcharencodingSequenceClass*)(c))
#define vcharencodingSequenceInit(s)					      \
    vcharencodingSequenceInitOfClass(s, vcharencodingSequenceGetDefaultClass())
#define vcharencodingSequenceDestroy(s)					      \
    vsequenceDestroy(vcharencodingSequenceGetSequence(s))
#define vcharencodingSequenceClone(s)					      \
    ((vcharencodingSequence*)						      \
     vsequenceClone(vcharencodingSequenceGetSequence(s)))
#define vcharencodingSequenceCopy(s, t)					      \
    vsequenceCopy(vcharencodingSequenceGetSequence(s),			      \
		  vcharencodingSequenceGetSequence(t))
#define vcharencodingSequenceCopyInit(s, t)				      \
    vsequenceCopyInit(vcharencodingSequenceGetSequence(s),		      \
		      vcharencodingSequenceGetSequence(t))
#define vcharencodingSequenceLoad(r)					      \
    ((vcharencodingSequence*)vsequenceLoad(r))
#define vcharencodingSequenceLoadInit(s, r)				      \
    vsequenceLoadInit(vcharencodingSequenceGetSequence(s), r)
#define vcharencodingSequenceStore(s, r)				      \
    vsequenceStore(vcharencodingSequenceGetSequence(s), r)
#define vcharencodingSequenceAppendEncodingShared(s, e)			      \
    vsequenceAppendElementShared(vcharencodingSequenceGetSequence(s),         \
				 vcharencodingGetInstance(e))
#define vcharencodingSequenceAppendEncodingOwned(s, e)			      \
    vsequenceAppendElementOwned(vcharencodingSequenceGetSequence(s),          \
				vcharencodingGetInstance(e))
#define vcharencodingSequenceInsertEncodingShared(s, i, e)		      \
    vsequenceInsertElementShared(vcharencodingSequenceGetSequence(s), i,      \
				 vcharencodingGetInstance(e))
#define vcharencodingSequenceInsertEncodingOwned(s, i, e)		      \
    vsequenceInsertElementOwned(vcharencodingSequenceGetSequence(s), i,       \
				vcharencodingGetInstance(e))
#define vcharencodingSequenceRemoveEncodingAt(s, i)			      \
    ((vcharencoding*)							      \
     vsequenceRemoveElementAt(vcharencodingSequenceGetSequence(s), i))
#define vcharencodingSequenceRemoveEncoding(s, e)			      \
    ((vcharencoding*)							      \
     vsequenceRemoveElement(vcharencodingSequenceGetSequence(s),              \
			    vcharencodingGetInstance(e)))
#define vcharencodingSequenceReplaceEncodingAtShared(s, i, e)		      \
    ((vcharencoding*)							      \
     vsequenceReplaceElementAtShared(vcharencodingSequenceGetSequence(s), i,  \
				     vcharencodingGetInstance(e)))
#define vcharencodingSequenceReplaceEncodingAtOwned(s, i, e)		      \
    ((vcharencoding*)							      \
     vsequenceReplaceElementAtOwned(vcharencodingSequenceGetSequence(s), i,   \
				    vcharencodingGetInstance(e)))
#define vcharencodingSequenceGetEncodingCount(s)			      \
    vsequenceGetElementCount(vcharencodingSequenceGetSequence(s))
#define vcharencodingSequenceGetEncodingAt(s, i)			      \
    ((vcharencoding*)							      \
     vsequenceGetElementAt(vcharencodingSequenceGetSequence(s), i))
#define vcharencodingSequenceGetEncodingIndex(s, e)			      \
    vsequenceGetElementIndex(vcharencodingSequenceGetSequence(s),             \
			     vcharencodingGetInstance(e))
#define vcharencodingSequenceMoveIndex(s, c, n)				      \
    vsequenceMoveIndex(vcharencodingSequenceGetSequence(s), c, n)
#define vcharencodingSequenceMoveEncoding(s, e, i)			      \
    vsequenceMoveElement(vcharencodingSequenceGetSequence(s),                 \
			 vcharencodingGetInstance(e), i)
#define vcharencodingSequenceIsIndexOwned(s, i)				      \
    vsequenceIsIndexOwned(vcharencodingSequenceGetSequence(s), i)
#define vcharencodingSequenceSetIndexOwned(s, i, o)			      \
    vsequenceSetIndexOwned(vcharencodingSequenceGetSequence(s), i, o)

/*
 * vcharencodingString
 */

#define vcharencodingGetStringChars(s)         ((s)->str)
#define vcharencodingGetStringLength(s)        ((s)->len)
#define vcharencodingGetStringEncoding(s)      ((s)->encoding)

/*
 * * * * * * * * * * PRIVATE FUNCTION MESSAGE DEFINITIONS * * * * * * * * * *
 */

vportEND_CPLUSPLUS_EXTERN_C

#endif /* #ifndef vcharencodingINCLUDED */

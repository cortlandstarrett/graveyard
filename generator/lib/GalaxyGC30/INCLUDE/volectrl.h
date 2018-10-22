/* $Id: volectrl.h,v 1.6 1997/09/11 23:24:03 robert Exp $ */

#ifndef volectrlINCLUDED
#define volectrlINCLUDED

#ifndef  vportINCLUDED
#include <vport.h>
#endif

#if (vportOLE)
#ifndef  vmswhdrsINCLUDED
#include vmswhdrsHEADER
#endif
#endif

#ifndef  vimageINCLUDED
#include vimageHEADER
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * Prototypes and definitions for OLE control iterator
 */

typedef struct voleControlIterator voleControlIterator;

struct voleControlIterator {
    vchar	*name,
		*value,
		*className;
    vimage	*image;
#if (vportOLE)
    HKEY	clsidKey,
    		ctrlKey;
#endif
    int		nextKey;
};

void voleInitControlIterator(voleControlIterator *iterator);

int voleNextControlIterator(voleControlIterator *iterator);

vchar *voleGetControlIteratorName(voleControlIterator *iterator);

vchar *voleGetControlIteratorValue(voleControlIterator *iterator);

vchar *voleGetControlIteratorClassName(voleControlIterator *iterator);

vimage *voleGetControlIteratorImage(voleControlIterator *iterator);

void voleDestroyControlIterator(voleControlIterator *iterator);

vportEND_CPLUSPLUS_EXTERN_C

#endif /* volectrlINCLUDED */

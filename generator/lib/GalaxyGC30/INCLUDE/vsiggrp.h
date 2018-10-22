/* $Id: vsiggrp.h,v 1.2 1997/04/21 18:02:08 robert Exp $ */
/*===========================================================================*\
     FILE: vsiggrp.h                                      MODULE:  vsignature
 +---------------------------------------------------------------------------+

                (c) Copyright 1995, Visix Software, Inc.
                        All rights reserved.

 +--------  DESCRIPTION  ----------------------------------------------------+

        Signature Groups are sets of signatures

 +--------  NOTES  ----------------------------------------------------------+

        Should eventually be merged into <vsignature.h>, or perhaps
	generalized to a "package" abstraction that includes signatures
	and datatypes.

 +--------  BUGS  -----------------------------------------------------------+
        
\*===========================================================================*/
#ifndef  vsignatureGroupINCLUDED
#define  vsignatureGroupINCLUDED	(1)

#ifndef  vportINCLUDED
#include  <vport.h>
#endif

#ifndef  vdebugDEBUG
#include  vdebugHEADER
#endif
#ifndef  vsignatureINCLUDED
#include  vsignatureHEADER
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C

typedef struct vsignatureGroup	vsignatureGroup;
typedef vdictIterator		vsignatureGroupIterator;



/*********************
 **  vsignatureGroup
 *********************/
vsignatureGroup *vsignatureCreateGroup( void );
void  vsignatureInitGroup( vsignatureGroup *group );
void  vsignatureDestroyGroup( vsignatureGroup *group );

vsignatureGroup  *vsignatureLoadGroup( vresource res );
void  vsignatureStoreGroup( vsignatureGroup *group, vresource res );
void  vsignatureDumpGroup( vsignatureGroup *group, FILE *file );

vsignatureGroup *vsignatureFindGroup( const vname *name );
const vname *vsignatureGetGroupName( vsignatureGroup *group );
void  vsignatureSetGroupName( vsignatureGroup *group, const vname *name );

void  vsignatureAddToGroup( vsignatureGroup *group, vsignature *sig );
vsignature *vsignatureRemoveFromGroup( vsignatureGroup *group,
				       const vname *name );
vsignature  *vsignatureLookupInGroup( vsignatureGroup *group,
				      const vname *name );

#if  (vdebugDEBUG)
vsignatureGroup *_vsignatureCreateGroupDebug( const char *file,
					      int line );
vsignatureGroup *_vsignatureLoadGroupDebug( vresource res,
					    const char *file, int line );
#endif

/*****************************
 **  vsignatureGroupIterator
 *****************************/

void vsignatureInitGroupIterator( vsignatureGroupIterator *iter,
				  vsignatureGroup *group );
void vsignatureDestroyGroupIterator( vsignatureGroupIterator *iter );
int vsignatureNextGroupIterator( vsignatureGroupIterator *iter );
const vname *vsignatureGetGroupIteratorName( vsignatureGroupIterator *iter );
vsignature *vsignatureGetGroupIteratorSignature(vsignatureGroupIterator *iter);



/*===========================================================================*\
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
\*===========================================================================*/
struct vsignatureGroup {
    const vname	 *name;
    vdict	  dictSigs;
};


/*===========================================================================*\
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
\*===========================================================================*/
#define  vsignatureGetGroupName(_group)		(_group)->name
#define  vsignatureLookupInGroup(_group, _tag)	\
    (vsignature *)vdictLoad(&(_group)->dictSigs, _tag)

#if  (vdebugDEBUG)			/*----  #if     vdebugDEBUG  ----*/

#define  vsignatureCreateGroup()		\
    _vsignatureCreateGroupDebug(__FILE__, __LINE__)
#define  vsignatureLoadGroup(_res)		\
    _vsignatureLoadGroupDebug(_res, __FILE__, __LINE__)

#endif					/*----  #endif  vdebugDEBUG  ----*/


#define  vsignatureNextGroupIterator		vdictNextIterator
#define  vsignatureDestroyGroupIterator		vdictDestroyIterator
#define  vsignatureGetGroupIteratorName		vdictGetIteratorKey

#define  vsignatureInitGroupIterator(_iter, _group)	\
    vdictInitIterator(_iter, &(_group)->dictSigs)
#define  vsignatureGetGroupIteratorSignature		\
					(vsignature *)vdictGetIteratorValue


vportEND_CPLUSPLUS_EXTERN_C

#endif

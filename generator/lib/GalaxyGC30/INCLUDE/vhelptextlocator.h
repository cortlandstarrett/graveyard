/* $Id: vhelptextlocator.h,v 1.10 1997/09/11 23:13:33 robert Exp $ */

/* -----------------------------------------------------------------------
 *
 *  vhelptextlocator.h
 *
 *  Programming interface to the root vhelptextlocator
 *
 *  (c) Copyright Visix Software
 *  All rights reserved
 *
 * -----------------------------------------------------------------------
 */

#ifndef vhelptextlocatorINCLUDED
#define vhelptextlocatorINCLUDED	1

#ifndef  vportINCLUDED
#include <vport.h>
#endif

#ifndef  vhelplocatorINCLUDED
#include vhelplocatorHEADER
#endif

#ifndef  vhelptextINCLUDED
#include vhelptextHEADER
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * * * * * * * * * * PUBLIC TYPE DEFINITIONS * * * * * * * * * *
 */

typedef struct	vhelptextlocator		vhelptextlocator;
typedef	struct	vhelptextlocatorClass		vhelptextlocatorClass;       


/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */

/*
 * Creation/Destruction/Class Management
 */

vhelptextlocatorClass *vhelptextlocatorGetDefaultClass(
    void
    );

vhelptextlocatorClass *vhelptextlocatorGetClass(
    vhelptextlocator	*helptextlocator
    );

vhelptextlocator *vhelptextlocatorCreateOfClass(
    vhelptextlocatorClass	*helptextlocatorClass
    );

vhelptextlocator *vhelptextlocatorCreate(
    void
    );

vhelptextlocator *vhelptextlocatorInitOfClass(
   vhelptextlocator		*helptextlocator,
   vhelptextlocatorClass	*clas
   );

vhelptextlocator *vhelptextlocatorInit(
   vhelptextlocator		*helptextlocator
   );

vhelptextlocator *vhelptextlocatorDestroy(
   vhelptextlocator		*helptextlocator
   );

vhelplocator *vhelptextlocatorGetLocator(
    vhelptextlocator		*helptextlocator
    );

/*
 * Class specific API.
 */

vbool vhelptextlocatorSearchUIHierarchy(
    vhelptextlocator	*helplocator,
    vhelprequest	*request
    );

vbool vhelptextlocatorSearchResources(
    vhelptextlocator	*helplocator,
    vhelprequest	*request
    );

vbool vhelptextlocatorGetSearchUIHierarchy(
    vhelptextlocator	*helplocator
    );

vbool vhelptextlocatorGetSearchResources(
    vhelptextlocator	*helplocator
    );

vbool vhelptextlocatorGetUseItemTitle(
    vhelptextlocator	*helplocator
    );

void vhelptextlocatorSetSearchUIHierarchy(
    vhelptextlocator	*helplocator,
    vbool		 yesNo
    );

void vhelptextlocatorSetSearchResources(
    vhelptextlocator	*helplocator,
    vbool		 yesNo
    );

void vhelptextlocatorSetUseItemTitle(
    vhelptextlocator	*helplocator,
    vbool		 yesNo
    );

const vname *vhelptextlocatorGetDictionaryName(
    vhelptextlocator	*helplocator
    );

void vhelptextlocatorSetDictionaryName(
    vhelptextlocator	*helplocator,
    const vname		*dictName
    );

   				      
/*
 * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * *
 */

struct vhelptextlocator {
    vhelplocator	 locator;
    unsigned short	 flags;
    const vname		*dictName;
    vdict 		 resourceDict;
    vhelptext		 helptext;
};

#define vhelptextlocatorCLASS(SUPER, HELP_LOC)			        \
    vhelplocatorCLASS(SUPER, HELP_LOC);				        \
    vclassMETHOD_RET(vhelptextlocatorSEARCH_UI_HIERARCHY, vbool,	\
		     (HELP_LOC *helploc, vhelprequest *request));	\
    vclassMETHOD_RET(vhelptextlocatorSEARCH_RESOURCES, vbool,		\
		     (HELP_LOC *helploc, vhelprequest *request));	\
    vclassMETHOD(vhelptextlocatorSET_SEARCH_UI_HIERARCHY,		\
                     (HELP_LOC *helploc, vbool yesNo));			\
    vclassMETHOD(vhelptextlocatorSET_SEARCH_RESOURCES,			\
                     (HELP_LOC *helploc, vbool yesNo));			\
    vclassMETHOD(vhelptextlocatorSET_USE_ITEM_TITLE,			\
                     (HELP_LOC *helploc, vbool yesNo));			\
    vclassMETHOD(vhelptextlocatorSET_DICTIONARY_NAME,			\
		     (HELP_LOC *helploc, const vname *dictName))

struct vhelptextlocatorClass {
    vhelptextlocatorCLASS(vhelptextlocatorClass, vhelptextlocator);
};

/*
 * Flag values.
 */
enum 
{
    _vhelptextlocatorWILL_SEARCH_UI_HIERARCHY	= 0x0001,
    _vhelptextlocatorWILL_SEARCH_RESOURCES	= 0x0002,
    _vhelptextlocatorDICT_INITIALIZED		= 0x0004,
    _vhelptextlocatorUSE_ITEM_TITLE		= 0x0008
};

/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * *
 */
#define vhelptextlocatorGetLocator(l)     vportBASE_OBJECT((l), locator)
#define vhelptextlocatorGetClass(l)				        \
    ((vhelptextlocatorClass*)						\
      vhelplocatorGetClass(vhelptextlocatorGetLocator(l)))
#define vhelptextlocatorCreateOfClass(c) 				\
    ((vhelptextlocator *)						\
      vhelplocatorCreateOfClass((vhelplocatorClass*)(c)))
#define vhelptextlocatorInitOfClass(l, c) 				\
    ((vhelptextlocator *)						\
      vhelplocatorInitOfClass(vhelptextlocatorGetLocator(l), 		\
       (vhelplocatorClass*)(c)))
#define vhelptextlocatorCreate()					\
      vhelptextlocatorCreateOfClass(vhelptextlocatorGetDefaultClass())

#define vhelptextlocatorGetSearchUIHierarchy(l)				\
    ((l)->flags & _vhelptextlocatorWILL_SEARCH_UI_HIERARCHY)
#define vhelptextlocatorGetSearchResources(l)				\
    ((l)->flags & _vhelptextlocatorWILL_SEARCH_RESOURCES)
#define vhelptextlocatorGetUseItemTitle(l)				\
    ((l)->flags & _vhelptextlocatorUSE_ITEM_TITLE)

#define vhelptextlocatorGetDictionaryName(l)				\
    ((l)->dictName)
/*
 * * * * * * * * * * PRIVATE FUNCTION MESSAGE DEFINITIONS * * * * * * * * * *
 */
#define vhelptextlocatorSearchUIHierarchy(l, r)				\
    vclassSend(vhelptextlocatorGetClass(l), 				\
	       vhelptextlocatorSEARCH_UI_HIERARCHY, (l, r))
#define vhelptextlocatorSearchResources(l, r)				\
    vclassSend(vhelptextlocatorGetClass(l),				\
	       vhelptextlocatorSEARCH_RESOURCES, (l, r))

#define vhelptextlocatorSetSearchUIHierarchy(l, b)			\
      vclassSend(vhelptextlocatorGetClass(l),				\
		 vhelptextlocatorSET_SEARCH_UI_HIERARCHY, (l, b))
#define vhelptextlocatorSetSearchResources(l, b)			\
      vclassSend(vhelptextlocatorGetClass(l), 				\
		 vhelptextlocatorSET_SEARCH_RESOURCES, (l, b))

#define vhelptextlocatorSetDictionaryName(l, n)				\
      vclassSend(vhelptextlocatorGetClass(l), 				\
		 vhelptextlocatorSET_DICTIONARY_NAME, (l, n))

vportEND_CPLUSPLUS_EXTERN_C

#endif /* vhelptextlocatorINCLUDED */



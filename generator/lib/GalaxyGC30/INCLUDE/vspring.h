/* $Id: vspring.h,v 1.32 1997/09/17 21:49:55 robert Exp $ */

/************************************************************

    vspring.h
    C Interface file for spring solutions

    (c) Copyright Visix Software Inc.
    All rights reserved

************************************************************/

#ifndef vspringINCLUDED
#define vspringINCLUDED 1


#ifndef  vportINCLUDED		/* for v*HEADER */
#include <vport.h>
#endif

#ifndef  vstdioINCLUDED		/* for FILE */
#include vstdioHEADER
#endif

#ifndef  vstdINCLUDED		/* for vbyte, vbool */
#include vstdHEADER
#endif

#ifndef  vresourceINCLUDED
#include vresourceHEADER
#endif

#ifndef  vrectINCLUDED
#include vrectHEADER
#endif

#ifndef  vclassINCLUDED
#include vclassHEADER
#endif

#ifndef  vloadableINCLUDED
#include vloadableHEADER
#endif


vportBEGIN_CPLUSPLUS_EXTERN_C


/*
 * * * * * * * * * CONSTANTS AND MACRO DEFINITIONS * * * * * * * * * *
 */

/*
 * Solution step flags:
 */

enum {
    vspringVERTICAL_STEP		= 0x80,
    vspringFORWARD_EDGE_STEP		= 0x40,
    vspringSTRETCH_STEP			= 0x20,
    vspringNATURAL_BASE_STEP		= 0x10,
    vspringLAST_STEP			= 0x08,
    vspringINTERNAL_STEP		= 0x02,
    vspringLOCKED_STEP			= 0x01,

    vspringSTRETCH_FACTOR_SHIFT		= 8,
    vspringSTRETCH_FACTOR_MASK		= 0x7F00,
    vspringDEFAULT_SPRING		= 0x0000,
    vspringSINGLE_SPRING		= 0x0800,
    vspringDOUBLE_SPRING		= 0x1000,
    vspringFOUR_TIMES_SPRING		= 0x2000,
    vspringEIGHT_TIMES_SPRING		= 0x4000,
    vspringHALF_SPRING			= 0x0400,
    vspringQUARTER_SPRING		= 0x0200,
    vspringEIGHTH_SPRING		= 0x0100,
    vspringSTRETCH_FACTOR_MAX		= 0x7F00
};

/*
 * Separation specifier:
 */

enum {
    _vspringVERTICAL_SEPARATION		= 0x04,
    _vspringFORWARD_EDGE_1_SEPARATION	= 0x02,
    _vspringFORWARD_EDGE_2_SEPARATION	= 0x01,

    vspringLEFT_TO_LEFT_SEPARATION	= 0x00,
    vspringLEFT_TO_RIGHT_SEPARATION	= 0x01,
    vspringRIGHT_TO_LEFT_SEPARATION	= 0x02,
    vspringRIGHT_TO_RIGHT_SEPARATION	= 0x03,
    vspringBOTTOM_TO_BOTTOM_SEPARATION	= 0x04,
    vspringBOTTOM_TO_TOP_SEPARATION	= 0x05,
    vspringTOP_TO_BOTTOM_SEPARATION	= 0x06,
    vspringTOP_TO_TOP_SEPARATION	= 0x07
};

/*
 * Solution flags:
 */

enum {
    _vspringKEEP_INFO			= 0x01,
    _vspringITEM_AT_INVALID		= 0x02,
    _vspringITEM_RECT_INVALID		= 0x04,
    _vspringITEM_MIN_SIZE_INVALID	= 0x08,
    _vspringITEM_NATURAL_SIZE_INVALID	= 0x10,
    _vspringSOLUTION_CHANGED		= 0x20,
       
    _vspringITEM_ALL_INVALID		= 0x1E
};


/*
 * * * * * * * * * TYPE AND STRUCTURE DEFINITIONS * * * * * * * * * *
 */

#define _vspringALLOC_INCREMENT	8

struct _vspringItemInfo;
struct _vspringStepInfo;

typedef struct vspringSolution		vspringSolution;

struct vspringSolution {
    vloadable			object;
    short			flags;
    short			itemCount;
    int				stepCount;
    int				stepAlloc;
    short			*itemIndexArray;
    short			*fixedBaseArray;
    unsigned short		*flagsArray;
    struct _vspringItemInfo	*itemInfos;
    struct _vspringStepInfo	*stepInfos;
};


#define vspringSolutionCLASS(SUPER, OBJECT)				      \
    vloadableCLASS(SUPER, OBJECT)

typedef struct vspringSolutionClass	vspringSolutionClass;

struct vspringSolutionClass {
    vspringSolutionCLASS(vspringSolutionClass, vspringSolution);
};


#define vspringArrangerCLASS(SUPER, USER, ITEM)				      \
    vclassROOT(SUPER);							      \
    vclassMETHOD_RET(vspringGET_ITEM_AT, ITEM *, (USER *user, int index));    \
    vclassMETHOD(vspringSET_ITEM_RECT,					      \
		 (USER *user, ITEM *item, const vrect *rect));		      \
    vclassMETHOD_RET(vspringGET_ITEM_RECT, const vrect *,		      \
		     (USER *user, ITEM *item));				      \
    vclassMETHOD(vspringGET_ITEM_MIN_SIZE,				      \
		 (USER *user, ITEM *item, int *wPtr, int *hPtr));	      \
    vclassMETHOD(vspringGET_ITEM_NATURAL_SIZE,				      \
		 (USER *user, ITEM *item, int *wPtr, int *hPtr));	      \
    vclassMETHOD(vspringCONSTRAIN_ITEM_SIZE,				      \
		 (USER *user, ITEM *item, int *wPtr, int *hPtr));	      \
    vclassMETHOD_RET(vspringGET_NATURAL_ITEM_SEPARATION, int,		      \
		     (USER *user, ITEM *item1, ITEM *item2,		      \
		      unsigned int whichSeparation))

typedef struct vspringArrangerClass	vspringArrangerClass;

struct vspringArrangerClass {
    vspringArrangerCLASS(vspringArrangerClass, void, void);
};


/*
 * * * * * * * * * FUNCTION PROTOTYPES * * * * * * * * * *
 */

void vspringStartup(void);


/* Initialization and Allocation of Spring Solutions */

vspringSolution *vspringCreateSolution(
    void
    );

vspringSolution *vspringCloneSolution(
    vspringSolution                *solution
    );

void vspringDestroySolution(
    vspringSolution                *solution
    );

vspringSolution *vspringLoadSolution(
    vresource                       resource
    );

void vspringStoreSolution(
    vspringSolution                *solution,
    vresource                       resource
    );

/* Spring Solution Operations */

void vspringAppendSolutionStep(
    vspringSolution                *solution,
    int                             flags,
    int                             baseLength,
    int                             itemIndex
    );

void vspringEmptySolution(
    vspringSolution                *solution
    );

void vspringDumpSolution(
    vspringSolution                *solution,
    FILE                           *stream
    );

/* Spring Solution Attributes Modification */

void vspringSetSolutionKeepInfo(
    vspringSolution                *solution,
    int				   keepInfo
    );

void vspringMarkSolutionItemIndexesChanged(
    vspringSolution                *solution
    );

void vspringMarkSolutionItemRectsChanged(
    vspringSolution                *solution
    );

void vspringMarkSolutionItemMinSizesChanged(
    vspringSolution                *solution
    );

void vspringMarkSolutionItemNaturalSizesChanged(
    vspringSolution                *solution
    );

/* Spring Solution Attributes Access */

vbool vspringHasSolutionKeepInfo(
    vspringSolution                *solution
    );

/* Spring Solution Step Attributes Modification */

void vspringSetSolutionFlagsAt(
    vspringSolution		   *solution,
    int				    stepIndex,
    unsigned int		    flags
    );

void vspringSetSolutionFixedBaseAt(
    vspringSolution		   *solution,
    int				    stepIndex,
    int				    baseLength
    );

void vspringSetSolutionItemIndexAt(
    vspringSolution		   *solution,
    int				    stepIndex,
    int				    itemIndex
    );

/* Spring Solution Step Attributes Access */

int vspringGetSolutionStepCount(
    vspringSolution		   *solution
    );

int vspringGetSolutionItemCount(
    vspringSolution		   *solution
    );

unsigned int vspringGetSolutionFlagsAt(
    vspringSolution		   *solution,
    int				    stepIndex
    );

int vspringGetSolutionFixedBaseAt(
    vspringSolution		   *solution,
    int				    stepIndex
    );

int vspringGetSolutionItemIndexAt(
    vspringSolution		   *solution,
    int				    stepIndex
    );

/* Arranger Class Functions */

vspringArrangerClass *vspringGetDefaultArrangerClass(
    void
    );

void vspringArrangeFromSolution(
    vspringArrangerClass	   *arrangerClass,
    void			   *arrangerData,
    vspringSolution                *solution,
    const vrect			   *rect
    );

void vspringCalcMinSizeFromSolution(
    vspringArrangerClass	   *arrangerClass,
    void			   *arrangerData,
    vspringSolution                *solution,
    int                            *w,
    int                            *h
    );

/*
 * * * * * * * * * * PRIVATE FUNCTION PROTOTYPES * * * * * * * * * *
 */

vspringSolutionClass *_vspringGetDefaultSolutionClass(void);

vspringSolutionClass *_vspringGetSolutionClass(
    vspringSolution			   *solution
    );

vloadable *_vspringGetSolutionLoadable(
    vspringSolution			   *solution
    );

vspringSolution *_vspringCreateSolutionOfClass(
    vspringSolutionClass                   *clas
    );

void _vspringInitSolutionOfClass(
    vspringSolution                        *solution,
    vspringSolutionClass                   *clas
    );

/*
 * * * * * * * * * FUNCTIONS IMPLEMENTED AS MACROS * * * * * * * * * *
 */

#define _vspringGetSolutionLoadable(s) \
    (vportBASE_OBJECT(s, object))

#define _vspringGetSolutionClass(s) \
    ((vspringSolutionClass*)vloadableGetClass(_vspringGetSolutionLoadable(s)))

#define vspringDestroySolution(s) \
    vloadableDestroy(_vspringGetSolutionLoadable(s))

#define vspringStoreSolution(s, r) \
    vclassSend(_vspringGetSolutionClass(s), vloadableSTORE, (s, r))

#define _vspringCreateSolutionOfClass(c) \
    ((vspringSolution*)vloadableCreateOfClass((vloadableClass*)(c)))

#define _vspringInitSolutionOfClass(s, c) \
    vloadableInitOfClass(_vspringGetSolutionLoadable(s), (vloadableClass*)(c))

#define vspringCreateSolution() \
    (_vspringCreateSolutionOfClass(_vspringGetDefaultSolutionClass()))

#define vspringCloneSolution(s) \
    ((vspringSolution*)vloadableClone(_vspringGetSolutionLoadable(s)))

#define vspringHasSolutionKeepInfo(s)	(((s)->flags & _vspringKEEP_INFO) != 0)

#define vspringMarkSolutionItemIndexesChanged(s) \
    ((s)->flags |= _vspringITEM_ALL_INVALID)

#define vspringMarkSolutionItemRectsChanged(s) \
    ((s)->flags |= _vspringITEM_RECT_INVALID)

#define vspringMarkSolutionItemMinSizesChanged(s) \
    ((s)->flags |= _vspringITEM_MIN_SIZE_INVALID)

#define vspringMarkSolutionItemNaturalSizesChanged(s) \
    ((s)->flags |= _vspringITEM_NATURAL_SIZE_INVALID)


vportEND_CPLUSPLUS_EXTERN_C


#endif /* #ifndef vspringINCLUDED */


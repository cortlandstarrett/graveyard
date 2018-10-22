/* $Id: vtreelist.h,v 1.25 1997/11/20 15:32:17 gregt Exp $ */

/************************************************************

    vtreelist.h
    C Interface to static and editable treelist box

    (c) Copyright Visix Software  1992
    All rights reserved
    
************************************************************/

#ifndef vtreelistINCLUDED
#define vtreelistINCLUDED 1

#ifndef  vportINCLUDED
#include <vport.h>
#endif

#ifndef vlistviewINCLUDED
#include vlistviewHEADER
#endif 

#ifndef  vdialogINCLUDED
#include vdialogHEADER
#endif

#ifndef  vtreeINCLUDED
#include vtreeHEADER
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C

/*****************************************************************************
 * PUBLIC CONSTANTS
 *****************************************************************************/

enum {
    vtreelistNEXT_SELECT = vlistviewNEXT_SELECT
};

/*
 * for vtreelistNoteProc message component
 */

enum {
    vtreelistNOTIFY_EXPAND = 1,
    vtreelistNOTIFY_COLLAPSE,
    vtreelistNOTIFY_SELECT_CONTENTS,
    vtreelistNOTIFY_SELECT_ICON,
    vtreelistNOTIFY_SELECT_TOGGLE,
    vtreelistNEXT_NOTIFY
};

/*
 * for vtreeOccurrence behaviors from vtreelistTree, subclass of vtree.
 */

enum {
    vtreelistTreeOccurrenceBEHAVIOR_CHANGE_EXPANDABLE
                                                 = vtreeOccurrenceNEXT_BEHAVIOR,
    vtreelistTreeOccurrenceBEHAVIOR_CHANGE_ICON,
    vtreelistTreeOccurrenceBEHAVIOR_COLLAPSE,
    vtreelistTreeOccurrenceBEHAVIOR_EXPAND,
    vtreelistTreeOccurrenceNEXT_BEHAVIOR
};

/*****************************************************************************
 * PUBLIC TYPE DEFINITION
 *****************************************************************************/

typedef struct vtreelistClass             vtreelistClass;
typedef struct vtreelistTreeClass         vtreelistTreeClass;

typedef struct vtreelist                  vtreelist;
typedef struct vtreelistTree              vtreelistTree; 

typedef vtreeOccurrence                   vtreelistTreeOccurrence;

typedef vtreeDepthFirstIterator           vtreelistTreeDepthFirstIterator;
typedef vtreeBreadthFirstIterator         vtreelistTreeBreadthFirstIterator;

typedef void (*vtreelistNoteProc)(vtreelist *treelist,
				  vtreelistTree *tree,
				  int message);

/*****************************************************************************
 * PUBLIC STANDARD FUNCTION PROTOTYPES
 *****************************************************************************/

void                vtreelistStartup(void);  

/*
 * vtreelist 
 */

vtreelist         *vtreelistClone(vtreelist *treelist); 
void               vtreelistCopy(vtreelist *treelist,
                                 vtreelist *target); 
void               vtreelistCopyInit(vtreelist *treelist,
                                     vtreelist *target); 
vtreelist         *vtreelistCreate(void); 
vtreelist         *vtreelistCreateOfClass(vtreelistClass *clas); 
void               vtreelistDestroy(vtreelist *treelist); 
int                vtreelistDetermineRowIndex(vtreelist *treelist,
                                              vtreelistTree *tree);
vtreelistTree     *vtreelistGetAtRow(vtreelist *treelist,
                                     int index);
vtreelistClass    *vtreelistGetClass(vtreelist *treelist);
vlistview         *vtreelistGetListview(vtreelist *treelist);
const void        *vtreelistGetData(vtreelist *treelist);
vtreelistClass    *vtreelistGetDefaultClass(void);
vdialogItem       *vtreelistGetItem(vtreelist *treelist);
vtreelistNoteProc  vtreelistGetNotify(vtreelist *treelist);
int                vtreelistGetRowCount(vtreelist *treelist);
int                vtreelistGetRowIndex(vtreelist *treelist,
                                        vtreelistTree *tree);
int                vtreelistGetSelectedRow(vtreelist *treelist);
vtreelistTree     *vtreelistGetTree(vtreelist *treelist);
int                vtreelistHasEdgeDisplay(vtreelist *treelist);
int                vtreelistHasHorzBar(vtreelist *treelist);
int                vtreelistHasRootDisplay(vtreelist *treelist);
int                vtreelistHasVertBar(vtreelist *treelist);
void               vtreelistInit(vtreelist *treelist); 
void               vtreelistInitOfClass(vtreelist *treelist,
                                        vtreelistClass *clas); 
void               vtreelistInsertRow(vtreelist *treelist,
                                      vtreelistTree *tree,
                                      int row);
void               vtreelistInvalRow(vtreelist *treelist,
                                     int row);
vtreelist         *vtreelistLoad(vresource resource); 
void               vtreelistLoadInit(vtreelist *treelist,
                                     vresource resource); 
void               vtreelistNotify(vtreelist *treelist,
                                   vtreelistTree *tree,
                                   int message);
void               vtreelistRemoveRow(vtreelist *treelist,
                                      int index);
void               vtreelistSetData(vtreelist *treelist,
                                    const void *data); 
void               vtreelistSetEdgeDisplay(vtreelist *treelist,
                                           int onOff);
void               vtreelistSetHorzBar(vtreelist *treelist,
                                       int onOff);
void               vtreelistSetNotify(vtreelist *treelist,
                                      vtreelistNoteProc noteProc);
void               vtreelistSetRootDisplay(vtreelist *treelist,
                                           int onOff);
void               vtreelistSetTree(vtreelist *treelist,
                                    vtreelistTree *tree);
void               vtreelistSetTreeOwned(vtreelist *treelist,
                                         vtreelistTree *tree);
void               vtreelistSetVertBar(vtreelist *treelist,
                                       int onOff);
void               vtreelistStore(vtreelist *treelist,
                                  vresource resource); 

/*
 * vtreelistTree
 */

void                 *vtreelistAppendTreeChild(vtreelistTree *tree,
			 		       vtreelistTree *child);
vtreelistTree        *vtreelistCloneTree(vtreelistTree *tree); 
void                  vtreelistCollapseTree(vtreelistTree *tree);
void                  vtreelistCollapseTreeRecursively(vtreelistTree *tree);
void                  vtreelistCopyInitTree(vtreelistTree *tree,
                                            vtreelistTree *target); 
void                  vtreelistCopyTree(vtreelistTree *tree,
                                        vtreelistTree *target); 
vtreelistTree        *vtreelistCreateTree(void); 
vtreelistTree        *vtreelistCreateTreeOfClass(vtreelistTreeClass *clas); 
void                  vtreelistDestroyTree(vtreelistTree *tree); 
void                  vtreelistExpandTree(vtreelistTree *tree);
vtreelistTreeClass   *vtreelistGetDefaultTreeClass(void);
vtreelistTree        *vtreelistGetTreeChildAt(vtreelistTree *tree,
					      int index);
int                   vtreelistGetTreeChildCount(vtreelistTree *tree);
int                   vtreelistGetTreeChildIndex(vtreelistTree *tree,
						 vtreelistTree *child);
vtreelistTreeClass   *vtreelistGetTreeClass(vtreelistTree *tree);
const void           *vtreelistGetTreeData(vtreelistTree *tree); 
vimage               *vtreelistGetTreeIcon(vtreelistTree *tree);
int                   vtreelistGetTreeLevel(vtreelistTree *tree);
vobservable          *vtreelistGetTreeObservable(vtreelistTree *tree);
vtreelistTree        *vtreelistGetTreeParent(vtreelistTree *tree);
const vname          *vtreelistGetTreeTag(vtreelistTree *tree);
const vchar          *vtreelistGetTreeTitle(vtreelistTree *tree); 
vtree                *vtreelistGetTreeTree(vtreelistTree *tree);
void                  vtreelistInitTree(vtreelistTree *tree); 
void                  vtreelistInitTreeOfClass(vtreelistTree *tree,
					       vtreelistTreeClass *clas); 
void                 *vtreelistInsertTreeChild(vtreelistTree *tree,
			 		       vtreelistTree *child,
					       int index);
int                   vtreelistIsTreeExpandable(vtreelistTree *tree);
int                   vtreelistIsTreeExpanded(vtreelistTree *tree);
void                  vtreelistLoadInitTree(vtreelistTree *tree,
					     vresource resource); 
vtreelistTree        *vtreelistLoadTree(vresource resource); 
vtreelistTree        *vtreelistRemoveTreeChild(vtreelistTree *tree,
					       vtreelistTree *child);
vtreelistTree        *vtreelistRemoveTreeChildAt(vtreelistTree *tree,
						 int index);
void                  vtreelistSetTreeChildAt(vtreelistTree *tree,
					      vtreelistTree *child,
					      int index);
void                  vtreelistSetTreeExpandable(vtreelistTree *tree,
						 int onOff);
void                  vtreelistSetTreeData(vtreelistTree *tree,
					    const void *data); 
void                  vtreelistSetTreeIcon(vtreelistTree *tree,
					    vimage *image);
void                  vtreelistSetTreeIconOwned(vtreelistTree *tree,
						 vimage *image);
void                  vtreelistSetTreeLevel(vtreelistTree *tree,
					    int level);
void                  vtreelistSetTreeParent(vtreelistTree *tree,
					     vtreelistTree *parent);
void                  vtreelistSetTreeTag(vtreelistTree *tree,
					   const vname *tag);
void                  vtreelistSetTreeTitle(vtreelistTree *tree,
					    const vchar *title); 
void                  vtreelistSetTreeTitleScribed(vtreelistTree *tree,
						   vscribe *scribe); 
void                  vtreelistStoreTree(vtreelistTree *tree,
					 vresource resource); 

/*
 * vtreelistTreeIterator
 */

vtreeIteratorClass *vtreelistGetDefaultTreeBreadthFirstIteratorClass(
    void
    );

vtreeIteratorClass *vtreelistGetDefaultTreeDepthFirstIteratorClass(
    void
    );

void vtreelistInitTreeBreadthFirstIterator(
    vtreeIterator     *iterator,
    vtreelistTree     *tree
    );

void vtreelistInitTreeDepthFirstIterator(
    vtreeIterator     *iterator,
    vtreelistTree     *tree
    );

/*****************************************************************************
 * PRIVATE CONSTANT DEFINITIONS
 *****************************************************************************/

enum {
    _vtreelistFLAGS_EDGE_DISPLAY        = 0x0001,
    _vtreelistFLAGS_ROOT_DISPLAY        = 0x0002,
    _vtreelistFLAGS_SELECT_CONTENTS     = 0x0004,
    _vtreelistFLAGS_SELECT_ICON         = 0x0008,
    _vtreelistFLAGS_SELECT_TOGGLE       = 0x0010,
    _vtreelistFLAGS_TREE_OWNED          = 0x0020
};

enum {
    _vtreelistTreeFLAGS_EXPANDABLE      = 0x0001,
    _vtreelistTreeFLAGS_EXPANDED        = 0x0002,
    _vtreelistTreeFLAGS_ICON_OWNED      = 0x0004,
    _vtreelistTreeFLAGS_HILITE_TOGGLE   = 0x0008,
    _vtreelistTreeFLAGS_HILITE_ICON     = 0x0010,
    _vtreelistTreeFLAGS_HILITE_CONTENTS = 0x0020
};

/*****************************************************************************
 * PRIVATE TYPE DEFINITIONS
 ****************************************************************************/

/*
 * vtreelist
 */

struct vtreelist {
    vlistview               listview;
    int                     flags;
    vtreelistTree          *tree;
    vtreelistNoteProc       noteProc;
};

#define vtreelistCLASS(SUPER, TREELIST, TREE, DI_NOTIFY, NOTIFY) \
    vlistviewCLASS(SUPER, TREELIST, DI_NOTIFY); \
    vclassMETHOD_RET(vtreelistDETERMINE_ROW_INDEX, \
		     int, (TREELIST *treelist, TREE *node)); \
    vclassMETHOD(vtreelistDRAW_NODE_CONTENTS, \
		 (TREELIST *treelist, int row, int selected, vrect *rect)); \
    vclassMETHOD(vtreelistDRAW_NODE_EDGE, \
		 (TREELIST *treelist, int row, int selected, vrect *rect)); \
    vclassMETHOD(vtreelistDRAW_NODE_ICON, \
		 (TREELIST *treelist, int row, int selected, vrect *rect)); \
    vclassMETHOD(vtreelistDRAW_NODE_TOGGLE, \
		 (TREELIST *treelist, int row, int selected, vrect *rect)); \
    vclassMETHOD_RET(vtreelistGET_AT_ROW, \
                     TREE *, (TREELIST *treelist, int index)); \
    vclassMETHOD_RET(vtreelistGET_LEVEL, \
                     int, (TREELIST *treelist, TREE *node)); \
    vclassMETHOD(vtreelistGET_NODE_CONTENTS_RECT, \
		 (TREELIST *treelist, int row, \
                  vrect *cellRect, vrect *contentsRect)); \
    vclassMETHOD(vtreelistGET_NODE_CONTENTS_SIZE, \
		 (TREELIST *treelist, int row, int *width, int *height)); \
    vclassMETHOD(vtreelistGET_NODE_EDGE_RECT, \
		 (TREELIST *treelist, int row, \
                  vrect *cellRect, vrect *edgeRect)); \
    vclassMETHOD(vtreelistGET_NODE_EDGE_SIZE, \
		 (TREELIST *treelist, int row, int *width, int *height)); \
    vclassMETHOD(vtreelistGET_NODE_ICON_RECT, \
		 (TREELIST *treelist, int row, \
                  vrect *cellRect, vrect *iconRect)); \
    vclassMETHOD(vtreelistGET_NODE_ICON_SIZE, \
		 (TREELIST *treelist, int row, int *width, int *height)); \
    vclassMETHOD(vtreelistGET_NODE_TOGGLE_RECT, \
		 (TREELIST *treelist, int row, \
                  vrect *cellRect, vrect *toggleRect)); \
    vclassMETHOD(vtreelistGET_NODE_TOGGLE_SIZE, \
		 (TREELIST *treelist, int row, int *width, int *height)); \
    vclassMETHOD_RET(vtreelistGET_ROW_INDEX, \
		     int, (TREELIST *treelist, TREE *node)); \
    vclassMETHOD_RET(vtreelistGET_ROW_COUNT, \
		     int, (TREELIST *treelist)); \
    vclassMETHOD_RET(vtreelistGET_SELECTED_ROW, \
		     int, (TREELIST *treelist)); \
    vclassMETHOD(vtreelistINVAL_ROW, \
		 (TREELIST *treelist, int row)); \
    vclassMETHOD(vtreelistINSERT_ROW, \
                 (TREELIST *treelist, TREE *tree, int index)); \
    vclassMETHOD(vtreelistNOTIFY, \
		 (TREELIST *treelist, TREE *node, int message)); \
    vclassMETHOD(vtreelistREMOVE_ROW, \
                 (TREELIST *treelist, int index)); \
    vclassMETHOD(vtreelistSET_EDGE_DISPLAY, \
		 (TREELIST *treelist, int onOff)); \
    vclassMETHOD(vtreelistSET_NOTIFY, \
                 (TREELIST *treelist, NOTIFY proc)); \
    vclassMETHOD(vtreelistSET_ROOT_DISPLAY, \
		 (TREELIST *treelist, int onOff)); \
    vclassMETHOD(vtreelistSET_TREE, \
		 (TREELIST *treelist, TREE *tree)); \
    vclassMETHOD(vtreelistSET_TREE_OWNED, \
		 (TREELIST *treelist, TREE *tree))

struct vtreelistClass {  
    vtreelistCLASS(vtreelistClass, vtreelist, vtreelistTree, 
		   vdialogItemNoteProc, vtreelistNoteProc);
};

/*
 * vtreelistTree
 */

struct vtreelistTree {
    vtree           tree;

    vimage         *icon;

    short           flags;
    int             level;
};

#define vtreelistTreeCLASS(SUPER, TREE) \
    vtreeCLASS(SUPER, TREE); \
    vclassVARIABLE(vtreelistTreeIMAGE_COLLAPSED, vimage *); \
    vclassVARIABLE(vtreelistTreeIMAGE_EXPANDED, vimage *); \
    vclassVARIABLE(vtreelistTreeLEVEL_INSET, short); \
    vclassMETHOD(vtreelistTreeCOLLAPSE, \
		 (TREE *tree)); \
    vclassMETHOD(vtreelistTreeCOLLAPSE_RECURSIVELY, \
		 (TREE *tree)); \
    vclassMETHOD(vtreelistTreeDRAW_CONTENTS, \
		 (TREE *tree, int selected, vrect *rect)); \
    vclassMETHOD(vtreelistTreeDRAW_EDGE, \
		 (TREE *tree, TREE *prevTree, TREE *nextTree, \
		  TREE *rootTree, int level, int selected, vrect *rect)); \
    vclassMETHOD(vtreelistTreeDRAW_ICON, \
		 (TREE *tree, int selected, vrect *rect)); \
    vclassMETHOD(vtreelistTreeDRAW_TOGGLE, \
		 (TREE *tree, int selected, vrect *rect)); \
    vclassMETHOD(vtreelistTreeEXPAND, \
		 (TREE *tree)); \
    vclassMETHOD(vtreelistTreeGET_CONTENTS_SIZE, \
                 (TREE *tree, int *width, int *height)); \
    vclassMETHOD(vtreelistTreeGET_CONTENTS_RECT, \
                 (TREE *tree, int level, \
                  vrect *cellRect, vrect *contentRect)); \
    vclassMETHOD(vtreelistTreeGET_EDGE_RECT, \
                 (TREE *tree, int level, \
                  vrect *cellRect, vrect *edgeRect)); \
    vclassMETHOD(vtreelistTreeGET_EDGE_SIZE, \
                 (TREE *tree, int *width, int *height)); \
    vclassMETHOD(vtreelistTreeGET_ICON_RECT, \
                 (TREE *tree, int level, \
                  vrect *cellRect, vrect *iconRect)); \
    vclassMETHOD(vtreelistTreeGET_ICON_SIZE, \
                 (TREE *tree, int *width, int *height)); \
    vclassMETHOD(vtreelistTreeGET_TOGGLE_RECT, \
                 (TREE *tree, int level, \
                  vrect *cellRect, vrect *toggleRect)); \
    vclassMETHOD(vtreelistTreeGET_TOGGLE_SIZE, \
                 (TREE *tree, int *width, int *height)); \
    vclassMETHOD(vtreelistTreeHILITE_CONTENTS, \
                 (TREE *tree)); \
    vclassMETHOD(vtreelistTreeHILITE_ICON, \
                 (TREE *tree)); \
    vclassMETHOD(vtreelistTreeHILITE_TOGGLE, \
                 (TREE *tree)); \
    vclassMETHOD(vtreelistTreeSET_EXPANDABLE, \
		 (TREE *tree, int onOff)); \
    vclassMETHOD(vtreelistTreeSET_ICON, \
		 (TREE *tree, vimage *image)); \
    vclassMETHOD(vtreelistTreeSET_ICON_OWNED, \
		 (TREE *tree, vimage *image)); \
    vclassMETHOD(vtreelistTreeSET_LEVEL, \
		 (TREE *tree, int level)); \
    vclassMETHOD(vtreelistTreeUNHILITE_CONTENTS, \
                 (TREE *tree)); \
    vclassMETHOD(vtreelistTreeUNHILITE_ICON, \
                 (TREE *tree)); \
    vclassMETHOD(vtreelistTreeUNHILITE_TOGGLE, \
                 (TREE *tree))

struct vtreelistTreeClass {
    vtreelistTreeCLASS(vtreelistTreeClass, vtreelistTree);
};

/*
 * vtreelistTreeIterator
 */

vportALIAS(vtreelistTreeBreadthFirstIterator, vtreeBreadthFirstIterator)

vportALIAS(vtreelistTreeDepthFirstIterator, vtreeDepthFirstIterator)

/*****************************************************************************
 * PRIVATE vtreelist FUNCTION MACRO DEFINITIONS
 *****************************************************************************/

#define vtreelistGetListview(t) \
    vportBASE_OBJECT((t), listview)
#define vtreelistGetClass(t) \
    ((vtreelistClass *)vobjectGetClass((vobject *) (t)))

/*
 * vobject level
 */
 
#define vtreelistClone(t) \
    ((vtreelist *)vdialogCloneItem(vtreelistGetItem(t)))
#define vtreelistCopy(t1, t2) \
    vdialogCopyItem(vtreelistGetItem(t1), vtreelistGetItem(t2))
#define vtreelistCopyInit(t1, t2) \
    vdialogCopyInitItem(vtreelistGetItem(t1), vtreelistGetItem(t2))
#define vtreelistCreateOfClass(clas) \
    ((vtreelist *)vdialogCreateItemOfClass((vdialogItemClass *)(clas)))
#define vtreelistCreate() \
    vtreelistCreateOfClass(vtreelistGetDefaultClass())
#define vtreelistDestroy(t) \
    vdialogDestroyItem(vtreelistGetItem(t))
#define vtreelistInitOfClass(t, clas) \
    vdialogInitItemOfClass(vtreelistGetItem(t), (vdialogItemClass *)(clas))
#define vtreelistInit(t) \
    vtreelistInitOfClass((t), vtreelistGetDefaultClass())
#define vtreelistLoad(r) \
    ((vtreelist *)vdialogLoadItem(r))
#define vtreelistLoadInit(t, r) \
    vdialogLoadInitItem(vtreelistGetItem(t), r)
#define vtreelistStore(t, r) \
    vdialogStoreItem(vtreelistGetItem(t), r)

/*
 * vdialogItem level
 */

#define vtreelistGetData(t) \
    vdialogGetItemData(vtreelistGetItem(t))
#define vtreelistSetData(t, d) \
    vdialogSetItemData(vtreelistGetItem(t), (d))

/*
 * vlistview level
 */

#define vtreelistGetItem(t) \
    vlistviewGetItem(vtreelistGetListview(t))
#define vtreelistHasHorzBar(t) \
    vlistviewHasHorzBar(vtreelistGetListview(t))
#define vtreelistHasVertBar(t) \
    vlistviewHasVertBar(vtreelistGetListview(t))
#define vtreelistSetHorzBar(t, f) \
    vlistviewSetHorzBar(vtreelistGetListview(t), f)
#define vtreelistSetVertBar(t, f) \
    vlistviewSetVertBar(vtreelistGetListview(t), f)

/*
 * vtreelist level
 */

#define vtreelistDetermineRowIndex(t, n) \
    vclassSend(vtreelistGetClass(t), vtreelistDETERMINE_ROW_INDEX, (t, n))
#define vtreelistGetAtRow(t, i) \
    vclassSend(vtreelistGetClass(t), vtreelistGET_AT_ROW, (t, i))
#define vtreelistGetRowIndex(t, n) \
    vclassSend(vtreelistGetClass(t), vtreelistGET_ROW_INDEX, (t, n))
#define vtreelistGetNotify(t) \
    ((t)->noteProc)
#define vtreelistGetRowCount(t) \
    vclassSend(vtreelistGetClass(t), vtreelistGET_ROW_COUNT, (t))
#define vtreelistGetSelectedRow(t) \
    vclassSend(vtreelistGetClass(t), vtreelistGET_SELECTED_ROW, (t))
#define vtreelistGetTree(t) \
    ((t)->tree)
#define vtreelistHasEdgeDisplay(t) \
    ((t)->flags & _vtreelistFLAGS_EDGE_DISPLAY)
#define vtreelistHasRootDisplay(t) \
    ((t)->flags & _vtreelistFLAGS_ROOT_DISPLAY)
#define vtreelistInsertRow(t, n, i) \
    vclassSend(vtreelistGetClass(t), vtreelistINSERT_ROW, (t, n, i))
#define vtreelistInvalRow(t, r) \
    vclassSend(vtreelistGetClass(t), vtreelistINVAL_ROW, (t, r))
#define vtreelistNotify(t, n, m) \
    vclassSend(vtreelistGetClass(t), vtreelistNOTIFY, (t, n, m))
#define vtreelistRemoveRow(t, i) \
    vclassSend(vtreelistGetClass(t), vtreelistREMOVE_ROW, (t, i))
#define vtreelistSetEdgeDisplay(t, f) \
    vclassSend(vtreelistGetClass(t), vtreelistSET_EDGE_DISPLAY, (t, f))
#define vtreelistSetNotify(t, p) \
    vclassSend(vtreelistGetClass(t), vtreelistSET_NOTIFY, (t, p))
#define vtreelistSetRootDisplay(t, f) \
    vclassSend(vtreelistGetClass(t), vtreelistSET_ROOT_DISPLAY, (t, f))
#define vtreelistSetTree(t, v) \
    vclassSend(vtreelistGetClass(t), vtreelistSET_TREE, (t, v))
#define vtreelistSetTreeOwned(t, v) \
    vclassSend(vtreelistGetClass(t), vtreelistSET_TREE_OWNED, (t, v))

/*****************************************************************************
 * PRIVATE vtreelistTree FUNCTION MACRO DEFINITIONS
 *****************************************************************************/

#define vtreelistGetTreeTree(n) \
    vportBASE_OBJECT((n), tree)
#define vtreelistGetTreeObservable(n) \
    vtreeGetObservable(vtreelistGetTreeTree(n))
#define vtreelistGetTreeClass(n) \
    ((vtreelistTreeClass *)vtreeGetClass(vtreelistGetTreeTree(n)))

/*
 * vobservable level
 */

#define vtreelistCloneTree(c) \
    ((vtreelistTree *)vobservableClone(vtreelistGetTreeObservable(c)))
#define vtreelistCopyInitTree(c1, c2) \
    vobservableCopyInit(vtreelistGetTreeObservable(c1), \
			vtreelistGetTreeObservable(c2))
#define vtreelistCopyTree(c1, c2) \
    vobservableCopy(vtreelistGetTreeObservable(c1), \
		    vtreelistGetTreeObservable(c2))
#define vtreelistCreateTreeOfClass(clas) \
    ((vtreelistTree *)vobservableCreateOfClass((vobservableClass*)(clas)))
#define vtreelistCreateTree() \
    vtreelistCreateTreeOfClass(vtreelistGetDefaultTreeClass())
#define vtreelistDestroyTree(c) \
    vobservableDestroy(vtreelistGetTreeObservable(c))
#define vtreelistGetTreeTag(c) \
    vobservableGetTag(vtreelistGetTreeObservable(c))
#define vtreelistInitTreeOfClass(c, clas) \
    vobservableInitOfClass(vtreelistGetTreeObservable(c), \
			   (vobservableClass *)(clas))
#define vtreelistInitTree(c) \
    vtreelistInitTreeOfClass((c), vtreelistGetDefaultTreeClass())
#define vtreelistLoadInitTree(c, r) \
    vobservableLoadInit(vtreelistGetTreeObservable(c), r)
#define vtreelistLoadTree(r) \
    ((vtreelistTree *)vobservableLoad(r))
#define vtreelistSetTreeTag(c, n) \
    vobservableSetTag(vtreelistGetTreeObservable(c), n)
#define vtreelistStoreTree(c, r) \
    vobservableStore(vtreelistGetTreeObservable(c), r)

/*
 * vtree level
 */

#define vtreelistAppendTreeChild(n, c) \
    vtreeAppendChild(vtreelistGetTreeTree(n), vtreelistGetTreeTree(c))
#define vtreelistGetTreeChildAt(n, i) \
    (vtreelistTree *)vtreeGetChildAt(vtreelistGetTreeTree(n), i)
#define vtreelistGetTreeChildCount(n) \
    vtreeGetChildCount(vtreelistGetTreeTree(n))
#define vtreelistGetTreeChildIndex(n, c) \
    vtreeGetChildIndex(vtreelistGetTreeTree(n), vtreelistGetTreeTree(c))
#define vtreelistGetTreeData(n) \
    vtreeGetData(vtreelistGetTreeTree(n))
#define vtreelistGetTreeParent(n) \
    (vtreelistTree *)vtreeGetParent(vtreelistGetTreeTree(n))
#define vtreelistGetTreeTitle(n) \
    vtreeGetTitle(vtreelistGetTreeTree(n))
#define vtreelistInsertTreeChild(n, c, i) \
    vtreeInsertChild(vtreelistGetTreeTree(n), vtreelistGetTreeTree(c), i)
#define vtreelistRemoveTreeChild(n, c) \
    (vtreelistTree *)vtreeRemoveChild(vtreelistGetTreeTree(n), vtreelistGetTreeTree(c))
#define vtreelistRemoveTreeChildAt(n, i) \
    (vtreelistTree *)vtreeRemoveChildAt(vtreelistGetTreeTree(n), i)
#define vtreelistSetTreeData(n, s) \
    vtreeSetData(vtreelistGetTreeTree(n), s)
#define vtreelistSetTreeParent(n, p) \
    vtreeSetParent(vtreelistGetTreeTree(n), vtreelistGetTreeTree(p))
#define vtreelistSetTreeTitle(n, s) \
    vtreeSetTitle(vtreelistGetTreeTree(n), s)
#define vtreelistSetTreeTitleScribed(n, s) \
    vtreeSetTitleScribed(vtreelistGetTreeTree(n), s)

/*
 * vtreelistTree level
 */

#define vtreelistCollapseTree(n) \
    vclassSend(vtreelistGetTreeClass(n), vtreelistTreeCOLLAPSE, (n))
#define vtreelistCollapseTreeRecursively(n) \
    vclassSend(vtreelistGetTreeClass(n),vtreelistTreeCOLLAPSE_RECURSIVELY,(n))
#define vtreelistExpandTree(n) \
    vclassSend(vtreelistGetTreeClass(n), vtreelistTreeEXPAND, (n))
#define vtreelistGetTreeIcon(v) \
    ((v)->icon)
#define vtreelistGetTreeLevel(n) \
    ((n)->level)
#define vtreelistIsTreeExpandable(n) \
    ((n)->flags&_vtreelistTreeFLAGS_EXPANDABLE)
#define vtreelistIsTreeExpanded(n) \
    ((n)->flags&_vtreelistTreeFLAGS_EXPANDED)
#define vtreelistSetTreeExpandable(n, f) \
    vclassSend(vtreelistGetTreeClass(n), vtreelistTreeSET_EXPANDABLE, (n, f))
#define vtreelistSetTreeIcon(v, d) \
    vclassSend(vtreelistGetTreeClass(v), vtreelistTreeSET_ICON, (v, d))
#define vtreelistSetTreeIconOwned(v, d) \
    vclassSend(vtreelistGetTreeClass(v), vtreelistTreeSET_ICON_OWNED, (v, d))
#define vtreelistSetTreeLevel(n, l) \
    vclassSend(vtreelistGetTreeClass(n), vtreelistTreeSET_LEVEL, (n, l))

vportEND_CPLUSPLUS_EXTERN_C

#endif /* vtreelistINCLUDED */





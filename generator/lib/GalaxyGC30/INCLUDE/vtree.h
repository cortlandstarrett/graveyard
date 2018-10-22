/* $Id: vtree.h,v 1.13 1997/07/29 13:25:58 jsbrown Exp $ */

/************************************************************

    vtree.h
    C Interface to trees

    (c) Copyright Visix Software  1994
    All rights reserved
    
************************************************************/

#ifndef vtreeINCLUDED
#define vtreeINCLUDED

#ifndef vclassINCLUDED
#include vclassHEADER
#endif

#ifndef vobservableINCLUDED
#include vobservableHEADER
#endif

#ifndef vsequenceINCLUDED
#include vsequenceHEADER
#endif

#ifndef vresourceINCLUDED
#include vresourceHEADER
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C

/*****************************************************************************
 * PUBLIC CONSTANT DEFINITIONS
 *****************************************************************************/

/* for vtreeOccurrence, vtree[Get/Set]OccurrenceBehavior() */

enum {
    vtreeOccurrenceBEHAVIOR_ADD_CHILD,
    vtreeOccurrenceBEHAVIOR_CHANGE_DATA,
    vtreeOccurrenceBEHAVIOR_CHANGE_TITLE,
    vtreeOccurrenceBEHAVIOR_DESTROY,
    vtreeOccurrenceBEHAVIOR_REMOVE_CHILD,
    vtreeOccurrenceNEXT_BEHAVIOR
};
    
/*****************************************************************************
 * PUBLIC TYPE DEFINITIONS
 *****************************************************************************/

typedef struct vtreeClass	     	vtreeClass;

typedef struct vtree			vtree;

typedef struct vtreeOccurrenceClass     vtreeOccurrenceClass;

typedef struct vtreeOccurrence          vtreeOccurrence;

typedef struct vtreeIteratorClass       vtreeIteratorClass;

typedef struct vtreeIterator            vtreeIterator;
typedef vtreeIterator                   vtreeBreadthFirstIterator;
typedef vtreeIterator                   vtreeDepthFirstIterator;

/*****************************************************************************
 * PUBLIC FUNCTION PROTOTYPES
 *****************************************************************************/

void vtreeStartup(
    void
   );

/*
 * vtree
 */

void vtreeAppendChild(
    vtree                       *tree,
    vtree                       *child
    );

vtree *vtreeClone(
    vtree                       *tree
    );

vtree *vtreeCreate(
    void
    );

vtree *vtreeCreateOfClass(
    vtreeClass                  *clas
    );

void vtreeDestroy(
    vtree                       *tree 
    );

void vtreeCopy(
    vtree                       *tree,
    vtree                       *target
    );

void vtreeCopyInit(
    vtree                       *tree,
    vtree                       *target
    );

vtreeClass *vtreeGetClass(
    vtree                       *tree
    );

vtree *vtreeGetChildAt(
    vtree                       *tree,
    int                          index
    );

int vtreeGetChildCount(
    vtree                       *tree
    );

int vtreeGetChildIndex(
    vtree                       *tree,
    vtree                       *child
    );

const void *vtreeGetData(
    vtree                       *tree
    );

vtreeClass *vtreeGetDefaultClass(
    void
    );

vobservable *vtreeGetObservable(
    vtree                       *tree
    );

vloadable *vtreeGetLoadable(
    vtree                       *tree
    );

vinstance *vtreeGetInstance(
    vtree                       *tree
    );

vtree *vtreeGetParent(
    vtree                       *tree
    );

const vchar *vtreeGetTitle(
    vtree                       *tree
    );

void vtreeInit(
    vtree                       *tree
    );

void vtreeInitOfClass(
    vtree                       *tree,
    vtreeClass                  *clas
    );

void vtreeInsertChild(
    vtree                       *tree,
    vtree                       *child,
    int                          index
    );

void vtreeInstallObserver(
    vtree                       *tree,
    vobservable                 *observer
    );

void vtreeInstallObserverOwned(
    vtree                       *tree,
    vobservable                 *observer
    );

vtree *vtreeLoad(
    vresource                    resource
    );

void vtreeLoadInit(
    vtree                       *tree,
    vresource                    resource
    );

vtree *vtreeRemoveChild(
    vtree                       *tree,
    vtree                       *child
    );

vtree *vtreeRemoveChildAt(
    vtree                       *tree,
    int                          index
    );

void vtreeSetData(
    vtree                       *tree,
    const void                  *data
    );

void vtreeSetTitle(
    vtree                       *tree,
    const vchar                 *title
    );		   

void vtreeSetTitleScribed(
    vtree                       *tree,
    vscribe                     *scribe
    );		   

void vtreeSetParent(
    vtree                       *tree,
    vtree                       *parent
    );

void vtreeStore(
    vtree                       *tree,
    vresource                    resource
    );

void vtreeUninstallObserver(
    vtree                       *tree,
    vobservable                 *observer
    );

/*
 * vtreeOccurrence
 */

vtreeOccurrence *vtreeCreateOccurrence(
    void 
    );

vtreeOccurrence *vtreeCreateOccurrenceOfClass(
    vtreeOccurrenceClass       *clas
    );

void vtreeDestroyOccurrence(
    vtreeOccurrence            *occurrence
    );

vtreeOccurrenceClass *vtreeGetDefaultOccurrenceClass(
    void
    );

vtree *vtreeGetOccurrenceAnnouncer(
    vtreeOccurrence            *occurrence
    );

int vtreeGetOccurrenceBehavior(
    vtreeOccurrence            *occurrence
    );

vtree *vtreeGetOccurrenceChild(
    vtreeOccurrence            *occurrence
    );

vtree *vtreeGetOccurrenceNode(
    vtreeOccurrence            *occurrence
    );

voccurrence *vtreeGetOccurrenceOccurrence(
    vtreeOccurrence            *occurrence
    );

void vtreeInitOccurrence(
    vtreeOccurrence            *occurrence
    );

void vtreeInitOccurrenceOfClass(
    vtreeOccurrence            *occurrence,
    vtreeOccurrenceClass       *clas
    );

void vtreeSetOccurrenceAnnouncer(
    vtreeOccurrence            *occurrence,
    vtree                      *announcer
    );

void vtreeSetOccurrenceBehavior(
    vtreeOccurrence            *occurrence,
    int                         behavior
    );

void vtreeSetOccurrenceChild(
    vtreeOccurrence            *occurrence,
    vtree                      *child
    );

void vtreeSetOccurrenceNode(
    vtreeOccurrence            *occurrence,
    vtree                      *node
    );

/*
 * vtreeIterator
 */

vtreeIterator *vtreeCreateIterator(
    void
    );
 
vtreeIterator *vtreeCreateIteratorOfClass(
    vtreeIteratorClass                  *clas
    );

void vtreeDestroyIterator(
    vtreeIterator              *iterator
    );

vtreeIteratorClass *vtreeGetDefaultBreadthFirstIteratorClass(
    void
    );

vtreeIteratorClass *vtreeGetDefaultDepthFirstIteratorClass(
    void
    );

vtreeIteratorClass *vtreeGetDefaultIteratorClass(
    void
    );

vtreeIteratorClass *vtreeGetIteratorClass(
    vtreeIterator              *iterator
    );

viteratorGroup *vtreeGetIteratorGroupIterator(
    vtreeIterator              *iterator
    );

viterator *vtreeGetIteratorIterator(
    vtreeIterator              *iterator
    );

vtree *vtreeGetIteratorTree(
    vtreeIterator              *iterator
    );

void vtreeInitBreadthFirstIterator(
    vtreeIterator              *iterator,
    vtree                      *tree
    );

void vtreeInitDepthFirstIterator(
    vtreeIterator              *iterator,
    vtree                      *tree
    );

void vtreeInitIterator(
    vtreeIterator              *iterator,
    vtree                      *tree
    );

vbool vtreeNextIterator(
    vtreeIterator              *iterator
    );

/*****************************************************************************
 * PRIVATE CONSTANTS
 *****************************************************************************/

enum {
    _vtreeFLAGS_OWN_TITLE = 0x0001
};

/*****************************************************************************
 * PRIVATE TYPE DEFINITIONS
 *****************************************************************************/

/*
 * vtree
 */

struct vtree {
    vobservable		 observable;
    short                flags;
    vsequence           *children;
    vtree               *parent;
    const vchar         *title;
    const void		*data;
};

#define vtreeCLASS(SUPER, TREE) \
    vobservableCLASS(SUPER, TREE); \
    vclassMETHOD(vtreeAPPEND_CHILD, \
		 (TREE *tree, vtree *child)); \
    vclassMETHOD_RET(vtreeGET_CHILD_AT, \
		     TREE *, (TREE *tree, int index)); \
    vclassMETHOD_RET(vtreeGET_CHILD_COUNT, \
		     int, (TREE *tree)); \
    vclassMETHOD_RET(vtreeGET_CHILD_INDEX, \
		     int, (TREE *tree, vtree *child)); \
    vclassMETHOD(vtreeINSERT_CHILD, \
		 (TREE *tree, vtree *child, int index)); \
    vclassMETHOD_RET(vtreeREMOVE_CHILD_AT, \
		     vtree *, (TREE *tree, int index)); \
    vclassMETHOD(vtreeSET_DATA, \
		 (TREE *tree, const void *data)); \
    vclassMETHOD(vtreeSET_PARENT, \
		 (TREE *tree, vtree *parent)); \
    vclassMETHOD(vtreeSET_TITLE_SCRIBED, \
                 (TREE *tree, vscribe *scribe))
    
struct vtreeClass {
    vtreeCLASS(vtreeClass, vtree);
};

/*
 * vtreeOccurrence
 */

struct vtreeOccurrence {
    voccurrence          occurrence;
    int                  behavior;
    vtree               *child;
    vtree               *node;
};

#define vtreeOccurrenceCLASS(SUPER, OCCURRENCE, TREE) \
    voccurrenceCLASS(SUPER, OCCURRENCE); \
    vclassMETHOD(vtreeOccurrenceSET_BEHAVIOR, \
		 (OCCURRENCE *occurrence, int behavior)); \
    vclassMETHOD(vtreeOccurrenceSET_CHILD, \
                 (OCCURRENCE *occurrence, TREE *child)); \
    vclassMETHOD(vtreeOccurrenceSET_NODE, \
                 (OCCURRENCE *occurrence, TREE *node))

struct vtreeOccurrenceClass {
    vtreeOccurrenceCLASS(vtreeOccurrenceClass, vtreeOccurrence, vtree);
};

/*
 * vtreeIterator
 */

struct vtreeIterator {
    viteratorGroup  iterator;
    vtree          *tree;
    int             index;
};

#define vtreeIteratorCLASS(SUPER, ITERATOR) \
    viteratorGROUP_CLASS(SUPER, ITERATOR)

struct vtreeIteratorClass {
    vtreeIteratorCLASS(vtreeIteratorClass, vtreeIterator);
};

vportALIAS(vtreeBreadthFirstIterator, vtreeIterator)

vportALIAS(vtreeDepthFirstIterator, vtreeIterator)

/*****************************************************************************
 * PRIVATE vtree FUNCTION MACRO DEFINITIONS 
 *****************************************************************************/

#define vtreeGetObservable(t) \
    (vportBASE_OBJECT((t), observable))
#define vtreeGetLoadable(t) \
    vobservableGetLoadable(vtreeGetObservable(t))
#define vtreeGetInstance(t) \
    vobservableGetInstance(vtreeGetObservable(t))
#define vtreeGetClass(t) \
    ((vtreeClass *)vobservableGetClass(vtreeGetObservable(t)))

/*
 * vobservable level
 */

#define vtreeClone(t) \
    ((vtree *)vobservableClone(vtreeGetObservable(t)))
#define vtreeCopy(n, t) \
    vobservableCopy(vtreeGetObservable(n), vtreeGetObservable(t))
#define vtreeCopyInit(n, t) \
    vobservableCopyInit(vtreeGetObservable(n), vtreeGetObservable(t))
#define vtreeCreateOfClass(t) \
    ((vtree *)vobservableCreateOfClass((vobservableClass *)(t)))
#define vtreeCreate() \
    vtreeCreateOfClass(vtreeGetDefaultClass())
#define vtreeDestroy(t)\
    vobservableDestroy(vtreeGetObservable(t))
#define vtreeInitOfClass(t, c) \
    vobservableInitOfClass(vtreeGetObservable(t), (vtreeClass*)(c))
#define vtreeInit(t) \
    vobservableInitOfClass(vtreeGetObservable(t), vtreeGetDefaultClass())
#define vtreeInstallObserver(t, o) \
    vobservableInstallObserver(vtreeGetObservable(t), (vobservable *)(o))   
#define vtreeInstallObserverOwned(t, o) \
    vobservableInstallObserverOwned(vtreeGetObservable(t), (vobservable *)(o))
#define vtreeLoad(r) \
    ((vtree *)vobservableLoad(r))
#define vtreeLoadInit(n, r) \
    vobservableLoadInit(vtreeGetObservable(n), r)
#define vtreeStore(t, r) \
    vobservableStore(vtreeGetObservable(t), r)
#define vtreeUninstallObserver(t, o) \
    vobservableUninstallObserver(vtreeGetObservable(t), (vobservable *)(o))   

/*
 * vtree level
 */

#define vtreeAppendChild(t, c) \
    vclassSend(vtreeGetClass(t), vtreeAPPEND_CHILD, (t, c))
#define vtreeGetChildAt(t, i) \
    vclassSend(vtreeGetClass(t), vtreeGET_CHILD_AT, (t, i))
#define vtreeGetChildCount(t) \
    vclassSend(vtreeGetClass(t), vtreeGET_CHILD_COUNT, (t))
#define vtreeGetChildIndex(t, c) \
    vclassSend(vtreeGetClass(t), vtreeGET_CHILD_INDEX, (t, c))
#define vtreeGetData(t) \
    (t->data)
#define vtreeGetParent(t) \
    (t->parent)
#define vtreeGetTitle(t) \
    (t->title)
#define vtreeInsertChild(t, c, i) \
    vclassSend(vtreeGetClass(t), vtreeINSERT_CHILD, (t, c, i))
#define vtreeRemoveChildAt(t, i) \
    vclassSend(vtreeGetClass(t), vtreeREMOVE_CHILD_AT, (t, i))
#define vtreeSetData(t, d) \
    vclassSend(vtreeGetClass(t), vtreeSET_DATA, (t, d))
#define vtreeSetParent(t, p) \
    vclassSend(vtreeGetClass(t), vtreeSET_PARENT, (t, p))
#define vtreeSetTitleScribed(t, s) \
    vclassSend(vtreeGetClass(t), vtreeSET_TITLE_SCRIBED, (t, s))
#define vtreeSetTitle(t, s) \
    vtreeSetTitleScribed(t, vcharScribe(s))

/*****************************************************************************
 * PRIVATE vtreeOccurrence FUNCTION MACRO DEFINITIONS 
 *****************************************************************************/

#define vtreeGetOccurrenceOccurrence(o) \
    (vportBASE_OBJECT((o), occurrence))
#define vtreeGetOccurrenceClass(o) \
    ((vtreeOccurrenceClass*)voccurrenceGetClass(vtreeGetOccurrenceOccurrence(o)))

/*
 * voccurrence level
 */

#define vtreeCreateOccurrenceOfClass(c) \
    ((vtreeOccurrence *)voccurrenceCreateOfClass((voccurrenceClass *)(c)))
#define vtreeCreateOccurrence() \
    vtreeCreateOccurrenceOfClass(vtreeGetDefaultOccurrenceClass())
#define vtreeDestroyOccurrence(o) \
    voccurrenceDestroy(vtreeGetOccurrenceOccurrence(o))
#define vtreeInitOccurrenceOfClass(o, c) \
    voccurrenceInitOfClass(vtreeGetOccurrenceOccurrence(o), \
			   (voccurrenceClass *)c)
#define vtreeInitOccurrence(o) \
    vtreeInitOccurrenceOfClass(o, vtreeGetDefaultOccurrenceClass())
#define vtreeGetOccurrenceAnnouncer(o) \
    (vtree *)voccurrenceGetAnnouncer(vtreeGetOccurrenceOccurrence(o))
#define vtreeSetOccurrenceAnnouncer(o, t) \
    voccurrenceSetAnnouncer(vtreeGetOccurrenceOccurrence(o), (vinstance *)t)

/*
 * vtreeOccurrence level
 */

#define vtreeGetOccurrenceBehavior(o) \
    ((o)->behavior)
#define vtreeGetOccurrenceChild(o) \
    ((o)->child)
#define vtreeGetOccurrenceNode(o) \
    ((o)->node)
#define vtreeSetOccurrenceBehavior(o, b) \
    vclassSend(vtreeGetOccurrenceClass(o), vtreeOccurrenceSET_BEHAVIOR, (o, b))
#define vtreeSetOccurrenceChild(o, n) \
    vclassSend(vtreeGetOccurrenceClass(o), vtreeOccurrenceSET_CHILD, (o, n))
#define vtreeSetOccurrenceNode(o, n) \
    vclassSend(vtreeGetOccurrenceClass(o), vtreeOccurrenceSET_NODE, (o, n))

/*****************************************************************************
 * PRIVATE vtreeIterator FUNCTION MACRO DEFINITIONS 
 *****************************************************************************/

#define vtreeGetIteratorGroupIterator(i) \
    (vportBASE_OBJECT((i), iterator))
#define vtreeGetIteratorIterator(i) \
    viteratorGetGroupIterator(vtreeGetIteratorGroupIterator(i))
#define vtreeGetIteratorClass(i) \
    ((vtreeIteratorClass *)viteratorGetClass(vtreeGetIteratorIterator(i)))

/*
 * viterator level
 */
#define vtreeCreateIteratorOfClass(c) \
    ((vtreeIterator *)viteratorCreateOfClass((viteratorClass *)(c)))
#define vtreeCreateIterator() \
    vtreeCreateIteratorOfClass(vtreeGetDefaultIteratorClass())
#define vtreeDestroyIterator(i) \
    viteratorDestroy(vtreeGetIteratorIterator(i))
#define vtreeGetIteratorTree(i) \
    ((vtree *)viteratorGetElement(vtreeGetIteratorIterator(i)))
#define vtreeNextIterator(i) \
     viteratorNext(vtreeGetIteratorIterator(i))


vportEND_CPLUSPLUS_EXTERN_C

#endif /* vtreeINCLUDED */


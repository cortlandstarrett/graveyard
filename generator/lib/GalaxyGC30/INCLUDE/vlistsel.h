/* $Id: vlistsel.h,v 1.3 1997/09/18 23:19:04 robert Exp $ */

/************************************************************

    vlistsel.h

    C Interface for the List Manager's selection objects

    (c) Copyright Visix Software
    All rights reserved

************************************************************/

#ifndef vlistselectionINCLUDED
#define vlistselectionINCLUDED 1

#ifndef  vportINCLUDED
#include <vport.h>
#endif

#ifndef  vclassINCLUDED
#include vclassHEADER
#endif

#ifndef  vobjectINCLUDED
#include vobjectHEADER
#endif

#ifndef  vrectINCLUDED
#include vrectHEADER
#endif

#ifndef  viteratorINCLUDED
#include viteratorHEADER
#endif

#ifndef  vobserverINCLUDED
#include vobserverHEADER
#endif

#ifndef  vresourceINCLUDED
#include vresourceHEADER
#endif


vportBEGIN_CPLUSPLUS_EXTERN_C


/*
 * * * * * * * * * * PUBLIC CONSTANT DEFINITIONS * * * * * * * * * *
 */

/* selection types for vlistSetSelectMethod() */
enum {
    vlistselectionFREE_SELECTION	= 1,
    vlistselectionONE_ONLY_SELECTION	= 2,
    vlistselectionRECTANGULAR_SELECTION	= 3,
    vlistselectionNO_SELECTION		= 4
};

/* row/column specifications for range operations */
enum {
    vlistselectionROW			= 1,
    vlistselectionCOLUMN
};

/* return value for vlistselectionGetSelectedCell() on an empty selection */
enum {
    vlistselectionNO_CELLS_SELECTED	= -1
};

/* selection change observer states */
enum {
    vlistselectionSELECTION_WILL_CHANGE	= 0,
    vlistselectionSELECTION_HAS_CHANGED
};

/*
 * * * * * * * * * * PUBLIC TYPE DEFINITIONS * * * * * * * * * *
 */

typedef struct vlistselection	     vlistselection;
typedef struct vlistselectionClass   vlistselectionClass;

typedef struct vlistselectionRangeIterator vlistselectionRangeIterator;
typedef vlistselectionRangeIterator	   vlistselectionIterator;
typedef struct vlistselectionIteratorClass vlistselectionIteratorClass;

/* Forward declared for references */
typedef struct vlist		     vlist;

/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */


void vlistselectionStartup(void);


/*
 * Selection Entrypoints
 */

vlistselectionClass *vlistselectionGetDefaultClass (
    void
    );

vlistselectionClass *vlistselectionGetClass (
    vlistselection	*selection
    );

vobservable *vlistselectionGetObservable (
    vlistselection	*selection
    );

vloadable *vlistselectionGetLoadable (
    vlistselection	*selection
    );

vinstance *vlistselectionGetInstance (
    vlistselection	*selection
    );

vlistselection *vlistselectionCreate (
    void
    );

vlistselection *vlistselectionCreateOfClass (
    vlistselectionClass	*clas
    );

void vlistselectionInit (
    vlistselection	*selection
    );

void vlistselectionInitOfClass (
    vlistselection	*selection,
    vlistselectionClass	*clas
    );

void vlistselectionDestroy (
    vlistselection	*selection
    );

vlistselection *vlistselectionClone (
    vlistselection 	*selection
    );

void vlistselectionCopyInit (
    vlistselection 	*source,
    vlistselection 	*destination
    );

void vlistselectionCopy (
    vlistselection 	*source,
    vlistselection 	*destination
    );

vlistselection *vlistselectionLoad (
    vresource		 resource
    );

void vlistselectionLoadInit (
    vlistselection 	*selection,
    vresource		 resource
    );

void vlistselectionStore (
    vlistselection 	*selection,
    vresource		 resource
    );

void vlistselectionDump (
    vlistselection 	*selection,
    FILE 		*stream
    );

void vlistselectionSetList (
    vlistselection	*selection,
    vlist		*list
    );

vlist *vlistselectionGetList (
    vlistselection	*selection
    );

void vlistselectionSetImmutable (
    vlistselection	*selection,
    int		 	 onOff
    );

int vlistselectionIsImmutable (
    vlistselection	*selection
    );

void vlistselectionGetSelectedCell (
    vlistselection	*selection,
    int			*row,
    int			*column
    );

void vlistselectionSelectRange (
    vlistselection	*selection,
    int	 	 	 row,
    int	 		 column,
    int	 		 numDown,
    int	 		 numAcross
    );

void vlistselectionUnselectRange (
    vlistselection	*selection,
    int	 		 row,
    int	 		 column,
    int	 		 numDown,
    int	 		 numAcross
    );

void vlistselectionSelectCell (
    vlistselection	*selection,
    int	  		 row,
    int	 		 column
    );

void vlistselectionUnselectCell (
    vlistselection	*selection,
    int	 		 row,
    int	 		 column
    );

void vlistselectionSelectRow (
    vlistselection  	*selection,
    int			 row
    );

void vlistselectionUnselectRow (
    vlistselection  	*selection,
    int			 row
    );

void vlistselectionSelectColumn (
    vlistselection  	*selection,
    int			 column
    );

void vlistselectionUnselectColumn (
    vlistselection  	*selection,
    int			 column
    );

void vlistselectionSelectAll (
    vlistselection	*selection
    );

void vlistselectionUnselectAll (
    vlistselection	*selection
    );

int vlistselectionIsCellSelected (
    vlistselection	*selection,
    int		 	 row,
    int			 column
    );

long vlistselectionGetSelectedCellCount (
    vlistselection  	*selection
    );

int vlistselectionGetMaxRowCount (
    vlistselection  	*selection
    );

int vlistselectionGetMaxColumnCount (
    vlistselection  	*selection
    );

void vlistselectionDetermineBounds (
    vlistselection 	*selection,
    int            	*row,
    int            	*column,
    int            	*numDown,
    int            	*numAcross
    );

int vlistselectionIsEmpty (
    vlistselection 	*selection
    );

vlistselection *vlistselectionCreateUnion (
    vlistselection	*number1,
    vlistselection	*number2
    );

vlistselection *vlistselectionCreateIntersection (
    vlistselection	*number1,
    vlistselection	*number2
    );

vlistselection *vlistselectionCreateComplement (
    vlistselection	*selection
    );

vlistselection *vlistselectionCreateDifference (
    vlistselection	*selection1,
    vlistselection	*selection2
    );

void vlistselectionSetSelectMethod (
    vlistselection	*selection,
    int		 method
    );
    
void vlistselectionSetAtLeastOne (
    vlistselection  	*selection,
    int			 onOff
    );

int vlistselectionHasAtLeastOne (
    vlistselection  	*selection
    );

void vlistselectionSetExtendRow (
    vlistselection  	*selection,
    int		 	 onOff
    );

int vlistselectionHasExtendRow (
    vlistselection  	*selection
    );

void vlistselectionSetExtendColumn (
    vlistselection  	*selection,
    int		 	 onOff
    );

int vlistselectionHasExtendColumn (
    vlistselection  	*selection
    );

int vlistselectionGetSelectMethod (
    vlistselection	*selection
    );


/*
 * List Iterator Entrypoints
 */


vlistselectionIteratorClass *vlistselectionGetDefaultRangeIteratorClass(
    void
    );

void vlistselectionInitRangeIterator (
    vlistselectionRangeIterator	*iterator,
    vlistselection 		*selection
    );

int vlistselectionNextRangeIterator (
    vlistselectionRangeIterator	*iterator
    );

void vlistselectionDestroyRangeIterator (
    vlistselectionRangeIterator	*iterator
    );

const void *vlistselectionGetRangeIteratorValue (
    vlistselectionRangeIterator	*iterator
    );

int vlistselectionGetRangeIteratorRow (
    vlistselectionRangeIterator	*iterator
    );

int vlistselectionGetRangeIteratorColumn (
    vlistselectionRangeIterator	*iterator
    );

int vlistselectionGetRangeIteratorRowCount (
    vlistselectionRangeIterator	*iterator
    );

int vlistselectionGetRangeIteratorColumnCount (
    vlistselectionRangeIterator	*iterator
    );

void vlistselectionGetRangeIteratorRange (
    vlistselectionRangeIterator	*iterator,
    vrectLong			*rect  /* rect.x,y,w,h = col,row,ncols,nrows */
    );


vlistselectionIteratorClass *vlistselectionGetDefaultIteratorClass(
    void
    );

void vlistselectionInitIterator (
    vlistselectionIterator	*iterator,
    vlistselection 		*selection
    );

int vlistselectionNextIterator (
    vlistselectionIterator	*iterator
    );

void vlistselectionDestroyIterator (
    vlistselectionIterator	*iterator
    );

int vlistselectionGetIteratorRow (
    vlistselectionIterator	*iterator
    );

int vlistselectionGetIteratorColumn (
    vlistselectionIterator	*iterator
    );

const void *vlistselectionGetIteratorValue (
    vlistselectionIterator	*iterator
    );


/*
 * * * * * * * * * * PRIVATE CONSTANT DEFINITIONS * * * * * * * * * *
 */

enum {
    _vlistselectionEXTEND_ROW_SELECTION		= 0x0001,
    _vlistselectionEXTEND_COLUMN_SELECTION	= 0x0002,
    _vlistselectionSELECTION_IMMUTABLE		= 0x0004,
    _vlistselectionAT_LEAST_ONE_SELECTION	= 0x0008,
    _vlistselectionMODIFY_SELECTION		= 0x0010
};

/*
 * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * *
 */

struct vlistselection {
    vobservable super;

    vlist      *list;
    short	index;
    short 	method;
    short	flags;
    vrectLong  *rects;
    int		rectCount;

    const void *data;
};

#define vlistselection_CLASS(CLASS, SELECTION)				\
    vobservableCLASS(CLASS, SELECTION)

struct vlistselectionClass
{
  vlistselection_CLASS(vlistselectionClass, vlistselection);
};


enum {
    _vlistselectionRANGE_ITERATION,
    _vlistselectionSELECTION_ITERATION,
    _vlistselectionLIST_ITERATION
};

struct vlistselectionRangeIterator {
    viterator    iterator;

    int          type;
    vlist	*list;
    vrectLong	*rects;
    int 	 rectIndex, rectCount;
    int		 nextRow, nextColumn;
    int		 row, column;
};

vportALIAS(vlistselectionIterator, vlistselectionRangeIterator)

#define vlistselectionITERATOR_CLASS(CLASS, ITERATOR)			\
    viteratorCLASS(CLASS, ITERATOR)

struct vlistselectionIteratorClass
{
  vlistselectionITERATOR_CLASS(vlistselectionIteratorClass,
			       vlistselectionIterator);
};


/*
 * * * * * * * * * * PRIVATE FUNCTION PROTOTYPES * * * * * * * * * *
 */


/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * *
 */


/*
 * List selections
 */

#define vlistselectionGetObservable(s)	vportBASE_OBJECT(s, super)
#define vlistselectionGetLoadable(s) \
    vobservableGetLoadable(vlistselectionGetObservable(s))
#define vlistselectionGetInstance(s) \
    vloadableGetInstance(vlistselectionGetLoadable(s))
#define vlistselectionGetClass(s) \
    ((vlistselectionClass*)vloadableGetClass(vlistselectionGetLoadable(s)))

#define vlistselectionCreateOfClass(c) \
    ((vlistselection *) vloadableCreateOfClass((vloadableClass *)(c)))
#define vlistselectionCreate() \
    vlistselectionCreateOfClass(vlistselectionGetDefaultClass())
#define vlistselectionInitOfClass(s,c) \
    vloadableInitOfClass(vlistselectionGetLoadable(s), (vloadableClass *)(c))
#define vlistselectionInit(s) \
    vlistselectionInitOfClass((s), vlistselectionGetDefaultClass())
#define vlistselectionDestroy(s) \
    vloadableDestroy(vlistselectionGetLoadable(s))

#define vlistselectionClone(s) \
    ((vlistselection *) vloadableClone(vlistselectionGetLoadable(s)))
#define vlistselectionCopy(s,t) \
    vloadableCopy(vlistselectionGetLoadable(s), vlistselectionGetLoadable(t))
#define vlistselectionCopyInit(s,t) \
    vloadableCopyInitOfSubclass(vlistselectionGetLoadable(s), \
				vlistselectionGetLoadable(t), \
			(vloadableClass *) vlistselectionGetDefaultClass())

#define vlistselectionLoad(r) \
    ((vlistselection *) vloadableLoadOfSubclass(r, \
			(vloadableClass *) vlistselectionGetDefaultClass()))
#define vlistselectionLoadInit(s,r) \
    vloadableLoadInitOfSubclass(vlistselectionGetLoadable(s), (r), \
			(vloadableClass *) vlistselectionGetDefaultClass())
#define vlistselectionStore(s,r) \
    vloadableStore(vlistselectionGetLoadable(s), (r))

#define vlistselectionDump(s,f) \
    vloadableDump(vlistselectionGetLoadable(s), (f))

#define vlistselectionGetList(s) \
    ((s)->list)
#define vlistselectionGetSelectMethod(s) \
    ((s)->method)
#define vlistselectionIsEmpty(s) \
    ((s)->rectCount == 0)
#define vlistselectionHasAtLeastOne(s) \
    (((s)->flags & _vlistselectionAT_LEAST_ONE_SELECTION) != 0)
#define vlistselectionIsImmutable(s) \
    (((s)->flags & _vlistselectionSELECTION_IMMUTABLE) != 0)
#define vlistselectionHasExtendRow(s) \
    (((s)->flags & _vlistselectionEXTEND_ROW_SELECTION) != 0)
#define vlistselectionHasExtendColumn(s) \
    (((s)->flags & _vlistselectionEXTEND_COLUMN_SELECTION) != 0)

#define vlistselectionSelectCell(s,r,c) \
    vlistselectionSelectRange(s,r,c,1,1)
#define vlistselectionUnselectCell(s,r,c) \
    vlistselectionUnselectRange(s,r,c,1,1)
#define vlistselectionSelectRow(s,r) \
    vlistselectionSelectRange(s,r,0,1, vlistselectionGetMaxColumnCount(s))
#define vlistselectionUnselectRow(s,r) \
    vlistselectionUnselectRange(s,r,0,1, vlistselectionGetMaxColumnCount(s))
#define vlistselectionSelectColumn(s,c) \
    vlistselectionSelectRange(s,0,c, vlistselectionGetMaxRowCount(s),1)
#define vlistselectionUnselectColumn(s,c) \
    vlistselectionUnselectRange(s,0,c, vlistselectionGetMaxRowCount(s),1)
#define vlistselectionSelectAll(s) \
    vlistselectionSelectRange(s,0,0, vlistselectionGetMaxRowCount(s), \
			      vlistselectionGetMaxColumnCount(s))
#define vlistselectionUnselectAll(s) \
    vlistselectionUnselectRange(s,0,0, vlistselectionGetMaxRowCount(s), \
				vlistselectionGetMaxColumnCount(s))

/*
 * List iterators
 */

#define _vlistselectionGetRangeIteratorIterator(i) \
    vportBASE_OBJECT(i, iterator)
#define _vlistselectionGetIteratorIterator(i) \
    _vlistselectionGetRangeIteratorIterator((vlistselectionRangeIterator *)(i))

#define vlistselectionNextRangeIterator(i) \
    viteratorNext(_vlistselectionGetRangeIteratorIterator(i))
#define vlistselectionDestroyRangeIterator(i) \
    viteratorDestroy(_vlistselectionGetRangeIteratorIterator(i))
#define vlistselectionGetRangeIteratorValue(i) \
    viteratorGetElementUntyped(_vlistselectionGetRangeIteratorIterator(i))

#define vlistselectionGetRangeIteratorRow(i) \
   ((i)->row)
#define vlistselectionGetRangeIteratorColumn(i) \
   ((i)->column)
#define vlistselectionGetRangeIteratorRowCount(i) \
   (((i)->rects[(i)->rectIndex]).h)
#define vlistselectionGetRangeIteratorColumnCount(i) \
   (((i)->rects[(i)->rectIndex]).w)
#define vlistselectionGetRangeIteratorRange(i,r) \
   (*(r) = (((i)->rects)[(i)->rectIndex]))


#define vlistselectionNextIterator(i) \
    viteratorNext(_vlistselectionGetIteratorIterator(i))
#define vlistselectionDestroyIterator(i) \
    viteratorDestroy(_vlistselectionGetIteratorIterator(i))
#define vlistselectionGetIteratorRow(i) \
    vlistselectionGetRangeIteratorRow((vlistselectionRangeIterator *)(i))
#define vlistselectionGetIteratorColumn(i) \
    vlistselectionGetRangeIteratorColumn((vlistselectionRangeIterator *)(i))
#define vlistselectionGetIteratorValue(i) \
    vlistselectionGetRangeIteratorValue((vlistselectionRangeIterator *)(i))


/*
 * Deprecation
 */

/*
 * * * * * * * * * * PRIVATE FUNCTION MESSAGE DEFINITIONS * * * * * * * * * *
 */


vportEND_CPLUSPLUS_EXTERN_C

#endif


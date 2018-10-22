/* $Id: vlist.h,v 1.81 1997/10/22 17:35:31 robert Exp $ */

/************************************************************

    vlist.h

    C Interface for the List Manager, list data objects

    (c) Copyright Visix Software
    All rights reserved

************************************************************/

#ifndef vlistINCLUDED
#define vlistINCLUDED 1

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

#ifndef  vlistselectionINCLUDED
#include vlistselectionHEADER
#endif


vportBEGIN_CPLUSPLUS_EXTERN_C


/*
 * * * * * * * * * * PUBLIC CONSTANT DEFINITIONS * * * * * * * * * *
 */

/* selection types for vlistSetSelectMethod() */
enum {
    vlistFREE_SELECTION			= vlistselectionFREE_SELECTION,
    vlistONE_ONLY_SELECTION		= vlistselectionONE_ONLY_SELECTION,
    vlistRECTANGULAR_SELECTION		= vlistselectionRECTANGULAR_SELECTION,
    vlistNO_SELECTION			= vlistselectionNO_SELECTION
};

/* row/column specifications for range operations */
enum {
    vlistROW			= vlistselectionROW,
    vlistCOLUMN			= vlistselectionCOLUMN
};

/* data orientation types for vlistSetOrientation() */
enum {
    vlistROW_MAJOR,
    vlistCOLUMN_MAJOR
};

/* return value for vlistGetSelectedCell() on an empty selection */
enum {
    vlistNO_CELLS_SELECTED	= vlistselectionNO_CELLS_SELECTED
};

/* selection change observer states */
enum {
    vlistSELECTION_WILL_CHANGE	= vlistselectionSELECTION_WILL_CHANGE,
    vlistSELECTION_HAS_CHANGED	= vlistselectionSELECTION_HAS_CHANGED
};

/* sorting change observer states */
enum {
    vlistSORT_BEGIN,
    vlistSORT_END
};


/* hints for vlistFindCell() */
enum {
    vlistFIND_LIST_IS_SORTED		= 0x00000001,

    /* check all columns before going to next row */
    vlistFIND_COLUMN_MAJOR		= 0x00000002,

    /* check all rows before going to next column */
    vlistFIND_ROW_MAJOR			= 0x00000004
};


/* types for vlistGetOccurrenceType and vlistSetOccurrenceType */
enum {
    vlistCELL_VALUE_CHANGE_OCCURRENCE	= 1,
    vlistINSERT_ROW_RANGE_OCCURRENCE	= 2,
    vlistINSERT_COLUMN_RANGE_OCCURRENCE	= 3,
    vlistREMOVE_ROW_RANGE_OCCURRENCE	= 4,
    vlistREMOVE_COLUMN_RANGE_OCCURRENCE	= 5,
    vlistSWAP_ROW_RANGE_OCCURRENCE	= 6,
    vlistSWAP_COLUMN_RANGE_OCCURRENCE	= 7,
    vlistMOVE_ROW_RANGE_OCCURRENCE	= 8,
    vlistMOVE_COLUMN_RANGE_OCCURRENCE	= 9,
    vlistSELECT_OCCURRENCE		= 10,
    vlistSET_SELECT_METHOD_OCCURRENCE	= 11,
    vlistSET_SELECT_ATTRIBUTE_OCCURRENCE = 12,
    vlistDATA_SET_CHANGE_OCCURRENCE	= 13,
    vlistROW_COUNT_CHANGE_OCCURRENCE	= 14,
    vlistCOLUMN_COUNT_CHANGE_OCCURRENCE	= 15,
    vlistORIENTATION_CHANGE_OCCURRENCE	= 16,
    vlistSORT_OCCURRENCE		= 17,
    vlistDESTROY_OCCURRENCE		= 18,
    _vlistOCCURRENCE_COUNT
};

/*
 * * * * * * * * * * PUBLIC TYPE DEFINITIONS * * * * * * * * * *
 */

#ifndef vlistselectionINCLUDED
typedef struct vlist		     vlist;
#endif
typedef struct vlistClass  	     vlistClass;

typedef vlistselection	             vlistSelection;
typedef vlistselectionClass          vlistSelectionClass;

typedef vlistselectionRangeIterator  vlistSelectionRangeIterator;
typedef vlistselectionIterator       vlistSelectionIterator;
typedef vlistselectionIterator	     vlistIterator;
typedef vlistselectionIteratorClass  vlistIteratorClass;

typedef struct vlistOccurrence	     vlistOccurrence;
typedef struct vlistOccurrenceClass  vlistOccurrenceClass;

typedef struct vlistObserver	     vlistObserver;
typedef struct vlistObserverClass    vlistObserverClass;

typedef vobservableObserverIterator  vlistObserverIterator;


typedef void (*vlistCellValueSetterProc) (
    vlist 	*list, 
    int 	 row,
    int 	 column, 
    const void  *value
    );

typedef const void *(*vlistCellValueGetterProc) (
    vlist 	*list, 
    int 	 row,
    int 	 column
    );

typedef const vchar *(*vlistNameCellProc) (
    vlist *list,
    int row,
    int column
    );

typedef int (*vlistCellValueSorterFunc) (
    const void *first,
    const void *second
    );

/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */


void vlistStartup(void);


vlistClass *vlistGetDefaultClass (
    void
    );

vlist *vlistCreate (
    void
    );

vlist *vlistCreateOfClass (
    vlistClass	*clas
    );

vlist *vlistClone (
    vlist	*list
    );

void vlistInit (
    vlist	*list
    );

void vlistInitOfClass (
    vlist	*list,
    vlistClass	*clas
    );

void vlistDestroy (
    vlist	*list
    );

void vlistCopy (
    vlist	*list,
    vlist	*target
    );

void vlistCopyInit(
    vlist      *list,
    vlist      *target
    );

vlist *vlistLoad (
    vresource	 resource
    );

void vlistLoadInit (
    vlist	*list,
    vresource    resource
    );

void vlistStore (
    vlist	*list,
    vresource    resource
    );

vresource vlistMakeMajorResource (
    vlist	*list,
    vresource    resource
    );

vresource vlistMakeMinorResource (
    vlist	*list,
    vresource	 resource,
    int		 index
    );

vresource vlistFindMinorResource (
    vlist	*list,
    vresource	 resource,
    int		 index
    );

vlistClass *vlistGetClass (
    vlist	*list
    );

vobject *vlistGetObject (
    vlist	*list
    );

vobservable *vlistGetObservable (
    vlist	*list
    );

vloadable *vlistGetLoadable (
    vlist	*list
    );

vinstance *vlistGetInstance (
    vlist	*list
    );

void vlistSetData (
    vlist	*list,
    void	*data
    );

void *vlistGetData (
    vlist	*list
    );

void vlistSetDataset (
    vlist	*list,
    void	*dataset,
    int	         size   /* actually a dummy parameter */
    );

void *vlistGetDataset (
    vlist	*list
    );

void vlistStoreCell (
    vlist 	*list,
    int 	 row,
    int 	 column,
    vresource    resource
    );
    
void vlistLoadCell (
    vlist 	*list,
    int 	 row,
    int 	 column,
    vresource    resource
    );

void vlistSetOrientation (
    vlist	*list,
    int	         direction    /* vlistROW_MAJOR or vlistCOLUMN_MAJOR */
    );


int vlistGetOrientation (
    vlist	*list
    );

void vlistSetCellValueSetter (
    vlist	*list,
    vlistCellValueSetterProc func
    );

void vlistSetCellValueGetter (
    vlist	*list,
    vlistCellValueGetterProc func
    );

void vlistSort (
    vlist	*list,
    int		 axis,
    int		 key,
    vlistCellValueSorterFunc compar
    );

void vlistSortByName (
    vlist	*list,
    int		 axis,
    int		 key,
    vlistCellValueSorterFunc compar
    );

int vlistFindCell (
    vlist	*list,
    const vchar	*name,
    int		*row,
    int		*column,
    int		 startRow,
    int		 startColumn,
    int		 directionHint
    );

void vlistSetCellNamer (
    vlist	*list,
    vlistNameCellProc proc
    );

vlistNameCellProc vlistGetCellNamer (
    vlist	*list
    );

const vchar *vlistDetermineCellName (
    vlist	*list,
    int		 row,
    int		 column
    );

void vlistSetCellValue (
    vlist 	*list,
    int	         row,
    int	         column,
    const void	*value
    );

const void *vlistGetCellValue (
    vlist	*list,
    int	         row,
    int	         column
    );

const void *vlistMGetCellValue ( /*only valid with default data representation*/
    vlist   	*list,
    int	         row,
    int	         column
    );

void vlistInsertRow (
    vlist	*list,
    int	 	 beforeRow
    );

void vlistInsertColumn (
    vlist	*list,
    int	 	 beforeColumn
    );

void vlistRemoveRow (
    vlist	*list,
    int	 	 row
    );

void vlistRemoveColumn (
    vlist	*list,
    int	 	 column
    );

void vlistSwapRows (
    vlist	*list,
    int	 	 row1,
    int	 	 row2
    );

void vlistSwapColumns (
    vlist	*list,
    int	 	 column1,
    int	 	 column2
    );

void vlistMoveRow (
    vlist	*list,
    int	 	 from,
    int	 	 to
    );

void vlistMoveColumn (
    vlist	*list,
    int	 	 from,
    int	 	 to
    );

void vlistInsertRange (
    vlist 	*list,
    int    	 before,
    int    	 count,
    int    	 type
    );

void vlistRemoveRange (
    vlist 	*list,
    int    	 victim,
    int    	 count,
    int    	 type
    );

void vlistSwapRange (
    vlist 	*list,
    int    	 swap1,
    int    	 swap2,
    int    	 count,
    int    	 type
    );

void vlistMoveRange (
    vlist 	*list,
    int    	 moveFrom,
    int    	 moveTo,
    int    	 count,
    int    	 type
    );

void vlistSetRowCount (
    vlist	*list,
    int	 	 rowCount
    );

int vlistGetRowCount (
    vlist	*list
    );

void vlistSetColumnCount (
    vlist	*list,
    int	 	 columnCount
    );

int vlistGetColumnCount (
    vlist	*list
    );

vlistselection *vlistCreateSelection (
    vlist	*list
    );

void vlistDump (
    vlist 		*list, 
    FILE 		*stream
    );

vlistCellValueSetterProc vlistGetDefaultCellValueSetterProc (
    void
    );

vlistCellValueGetterProc vlistGetDefaultCellValueGetterProc (
    void
    );

vlistNameCellProc vlistGetDefaultCellNamerProc (
    void
    );
  

/*
 * List Occurrence Entrypoints
 */

vlistOccurrenceClass *vlistGetDefaultOccurrenceClass (
    void
    );

vlistOccurrenceClass *vlistGetOccurrenceClass (
    vlistOccurrence	 *occurrence
    );

voccurrence *vlistGetOccurrenceOccurrence (
    vlistOccurrence	 *occurrence
    );

vinstance *vlistGetOccurrenceInstance (
    vlistOccurrence	 *occurrence
    );

vlistOccurrence *vlistCreateOccurrenceOfClass (
    vlistOccurrenceClass *clas
    );

vlistOccurrence *vlistCreateOccurrence (
    );

void vlistInitOccurrenceOfClass (
    vlistOccurrence	 *occurrence,
    vlistOccurrenceClass *clas
    );

void vlistInitOccurrence (
    vlistOccurrence	 *occurrence
    );

void vlistDestroyOccurrence (
    vlistOccurrence	 *occurrence
    );

vlist *vlistGetOccurrenceList (
    vlistOccurrence	 *occurrence
    );

int vlistGetOccurrenceType (
    vlistOccurrence	 *occurrence
    );

vlistselection *vlistGetOccurrenceSelection (
    vlistOccurrence	 *occurrence
    );

int vlistGetOccurrenceRow (
    vlistOccurrence	 *occurrence
    );

int vlistGetOccurrenceColumn (
    vlistOccurrence	 *occurrence
    );

int vlistGetOccurrenceRowCount (
    vlistOccurrence	 *occurrence
    );

int vlistGetOccurrenceColumnCount (
    vlistOccurrence	 *occurrence
    );

int vlistGetOccurrenceOldRow (
    vlistOccurrence	 *occurrence
    );

int vlistGetOccurrenceOldColumn (
    vlistOccurrence	 *occurrence
    );

int vlistGetOccurrenceOldRowCount (
    vlistOccurrence	 *occurrence
    );

int vlistGetOccurrenceOldColumnCount (
    vlistOccurrence	 *occurrence
    );

int vlistGetOccurrenceState (
    vlistOccurrence	 *occurrence
    );

int vlistGetOccurrenceOrientation (
    vlistOccurrence	 *occurrence
    );

void vlistSetOccurrenceList (
    vlistOccurrence	 *occurrence,
    vlist		 *list
    );

void vlistSetOccurrenceType (
    vlistOccurrence	 *occurrence,
    int			  type
    );

void vlistSetOccurrenceSelection (
    vlistOccurrence	 *occurrence,
    vlistselection	 *selection
    );

void vlistSetOccurrenceRow (
    vlistOccurrence	 *occurrence,
    int			  value
    );

void vlistSetOccurrenceColumn (
    vlistOccurrence	 *occurrence,
    int			  value
    );

void vlistSetOccurrenceRowCount (
    vlistOccurrence	 *occurrence,
    int			  value
    );

void vlistSetOccurrenceColumnCount (
    vlistOccurrence	 *occurrence,
    int			  value
    );

void vlistSetOccurrenceOldRow (
    vlistOccurrence	 *occurrence,
    int			  value
    );

void vlistSetOccurrenceOldColumn (
    vlistOccurrence	 *occurrence,
    int			  value
    );

void vlistSetOccurrenceOldRowCount (
    vlistOccurrence	 *occurrence,
    int			  value
    );

void vlistSetOccurrenceOldColumnCount (
    vlistOccurrence	 *occurrence,
    int			  value
    );

void vlistSetOccurrenceState (
    vlistOccurrence	 *occurrence,
    int			  value
    );

void vlistSetOccurrenceOrientation (
    vlistOccurrence	 *occurrence,
    int			  value
    );


/*
 * List Iterator Entrypoints
 */


vlistIteratorClass *vlistGetDefaultIteratorClass(
    void
    );

void vlistInitIterator (
    vlistIterator 		*iterator,
    vlist 			*list
    );

int vlistNextIterator (
    vlistIterator		*iterator
    );

void vlistDestroyIterator (
    vlistIterator		*iterator
    );

int vlistGetIteratorRow (
    vlistIterator		*iterator
    );

int vlistGetIteratorColumn (
    vlistIterator		*iterator
    );

const void *vlistGetIteratorValue (
    vlistIterator		*iterator
    );



/*
 * Deprecated List Observer Entrypoints
 */

vlistObserverClass *vlistGetDefaultObserverClass (
    void
    );

vlistObserverClass *vlistGetObserverClass (
    vlistObserver	*observer
    );

vobserver *vlistGetObserverObserver (
    vlistObserver	*observer
    );

vobservable *vlistGetObserverObservable (
    vlistObserver	*observer
    );

vloadable *vlistGetObserverLoadable (
    vlistObserver	*observer
    );

vinstance *vlistGetObserverInstance (
    vlistObserver	*observer
    );

vlistObserver *vlistCreateObserver (
    void
    );

vlistObserver *vlistCreateObserverOfClass (
    vlistObserverClass	*clas
    );

vlistObserver *vlistCloneObserver (
    vlistObserver	*observer
    );

void vlistCopyObserver (
    vlistObserver	*observer,
    vlistObserver	*target
    );

void vlistCopyInitObserver (
    vlistObserver	*observer,
    vlistObserver	*target
    );

void vlistInitObserver (
    vlistObserver	*observer
    );

void vlistInitObserverOfClass (
    vlistObserver	*observer,
    vlistObserverClass	*clas
    );

void vlistDestroyObserver (
    vlistObserver	*observer
    );


void vlistInstallObserver (
    vlist 		*list,
    vlistObserver	*observer
    );

void vlistInstallObserverOwned (
    vlist		*list,
    vlistObserver	*observer
    );

void vlistUninstallObserver (
    vlist		*list,
    vlistObserver	*observer
    );

void vlistSetObserverData (
    vlistObserver	*observer,
    void		*data
    );

void vlistDisableObserver (
    vlistObserver	*observer
    );

void vlistEnableObserver (
    vlistObserver	*observer
    );

void *vlistGetObserverData (
    vlistObserver	*observer
    );

int vlistObserverIsEnabled (
    vlistObserver	*observer
    );

void vlistSetObserverOwner (
    vlistObserver	*observer,
    vlist		*owner
    );

vlist *vlistGetObserverOwner (
    vlistObserver	*observer
    );


/*
 * Deprecated Observer Iterator Entrypoints
 */

void vlistInitObserverIterator (
    vlistObserverIterator	*iterator,
    vlist		     	*list
    );

int vlistNextObserverIterator (
    vlistObserverIterator	*iterator
    );

void vlistDestroyObserverIterator (
    vlistObserverIterator	*iterator
    );

vlistObserver *vlistGetObserverIteratorObserver (
    vlistObserverIterator	*iterator
    );

/*
 * Deprecated Selection Entrypoints
 */

vlistselectionClass *vlistGetDefaultSelectionClass (
    void
    );

void vlistDestroySelection (
    vlist		*list,
    vlistSelection	*selection
    );

vlistSelection *vlistCloneSelection (
    vlist	    	*list,
    vlistSelection 	*selection
    );

void vlistCopySelection (
    vlist	        *list,
    vlistSelection 	*source,
    vlistSelection 	*destination
    );

void vlistSetSelectionImmutable (
    vlist		*list,
    vlistSelection	*selection,
    int		 	 onOff
    );

int vlistIsSelectionImmutable (
    vlist		*list,
    vlistSelection	*selection
    );

void vlistGetSelectedCell (
    vlist		*list,
    vlistSelection	*selection,
    int			*row,
    int			*column
    );

void vlistSelectRange (
    vlist		*list,
    vlistSelection	*selection,
    int	 	 	 row,
    int	 		 column,
    int	 		 numDown,
    int	 		 numAcross
    );

void vlistUnselectRange (
    vlist		*list,
    vlistSelection	*selection,
    int	 		 row,
    int	 		 column,
    int	 		 numDown,
    int	 		 numAcross
    );

void vlistSelectCell (
    vlist		*list,
    vlistSelection	*selection,
    int	  		 row,
    int	 		 column
    );

void vlistUnselectCell (
    vlist		*list,
    vlistSelection	*selection,
    int	 		 row,
    int	 		 column
    );

void vlistSelectRow (
    vlist		*list,
    vlistSelection  	*selection,
    int			 row
    );

void vlistUnselectRow (
    vlist		*list,
    vlistSelection  	*selection,
    int			 row
    );

void vlistSelectColumn (
    vlist		*list,
    vlistSelection  	*selection,
    int			 column
    );

void vlistUnselectColumn (
    vlist		*list,
    vlistSelection  	*selection,
    int			 column
    );

void vlistSelectAll (
    vlist		*list,
    vlistSelection	*selection
    );

void vlistUnselectAll (
    vlist		*list,
    vlistSelection	*selection
    );

int vlistIsCellSelected (
    vlist		*list,
    vlistSelection	*selection,
    int		 	 row,
    int			 column
    );

long vlistCountSelectedCells (
    vlist		*list,
    vlistSelection  	*selection
    );

void vlistDetermineSelectionBounds (
    vlist          	*list, 
    vlistSelection 	*selection,
    int            	*row,
    int            	*column,
    int            	*numDown,
    int            	*numAcross
    );

int vlistIsSelectionEmpty (
    vlist	     	*list,
    vlistSelection 	*selection
    );

vlistSelection *vlistUnionSelections (
    vlist		*list,
    vlistSelection	*number1,
    vlistSelection	*number2
    );

vlistSelection *vlistIntersectSelections (
    vlist		*list,
    vlistSelection	*number1,
    vlistSelection	*number2
    );

vlistSelection *vlistComplementSelection (
    vlist		*list,
    vlistSelection	*selection
    );

vlistSelection *vlistDifferenceSelections (
    vlist		*list,
    vlistSelection	*selection1,
    vlistSelection	*selection2
    );

void vlistSetSelectMethod (
    vlist		*list,
    vlistSelection	*selection,
    int		 method
    );
    
void vlistSetAtLeastOneSelection (
    vlist		*list,
    vlistSelection  	*selection,
    int			 onOff
    );

int vlistHasAtLeastOneSelection (
    vlist		*list,
    vlistSelection  	*selection
    );

void vlistSetExtendRowSelection (
    vlist		*list,
    vlistSelection  	*selection,
    int		 	 onOff
    );

int vlistHasExtendRowSelection (
    vlist		*list,
    vlistSelection  	*selection
    );

void vlistSetExtendColumnSelection (
    vlist		*list,
    vlistSelection  	*selection,
    int		 	 onOff
    );

int vlistHasExtendColumnSelection (
    vlist		*list,
    vlistSelection  	*selection
    );

int vlistGetSelectMethod (
    vlist		*list,
    vlistSelection	*selection
    );

void vlistDumpSelection (
    vlistSelection 	*selection,
    FILE 		*stream
    );

vlistIteratorClass *vlistGetDefaultSelectionRangeIteratorClass(
    void
    );

void vlistInitSelectionRangeIterator (
    vlistSelectionRangeIterator	*iterator,
    vlistSelection 		*selection
    );

int vlistNextSelectionRangeIterator (
    vlistSelectionRangeIterator	*iterator
    );

void vlistDestroySelectionRangeIterator (
    vlistSelectionRangeIterator	*iterator
    );

const void *vlistGetSelectionRangeIteratorValue (
    vlistSelectionRangeIterator	*iterator
    );

int vlistGetSelectionRangeIteratorRow (
    vlistSelectionRangeIterator	*iterator
    );

int vlistGetSelectionRangeIteratorColumn (
    vlistSelectionRangeIterator	*iterator
    );

int vlistGetSelectionRangeIteratorRowCount (
    vlistSelectionRangeIterator	*iterator
    );

int vlistGetSelectionRangeIteratorColumnCount (
    vlistSelectionRangeIterator	*iterator
    );

void vlistGetSelectionRangeIteratorRange (
    vlistSelectionRangeIterator	*iterator,
    vrectLong			*rect  /* rect.x,y,w,h = col,row,ncols,nrows */
    );


vlistIteratorClass *vlistGetDefaultSelectionIteratorClass(
    void
    );

void vlistInitSelectionIterator (
    vlistSelectionIterator	*iterator,
    vlistSelection 		*selection
    );

int vlistNextSelectionIterator (
    vlistSelectionIterator	*iterator
    );

void vlistDestroySelectionIterator (
    vlistSelectionIterator	*iterator
    );

int vlistGetSelectionIteratorRow (
    vlistSelectionIterator	*iterator
    );

int vlistGetSelectionIteratorColumn (
    vlistSelectionIterator	*iterator
    );

const void *vlistGetSelectionIteratorValue (
    vlistSelectionIterator	*iterator
    );

int vlistGetIteratorRangeRowCount (
    vlistIterator	*iterator
    );

int vlistGetIteratorRangeColumnCount (
    vlistIterator	*iterator
    );

void vlistGetIteratorRange (
    vlistIterator	*iterator,
    vrectLong		*rect
    );

/*
 * * * * * * * * * * PRIVATE CONSTANT DEFINITIONS * * * * * * * * * *
 */

enum {
    _vlistDATA_FROM_CLIENT  	= 0x0001,
    _vlistROW_MAJOR		= 0x0002,
    _vlistCOLUMN_MAJOR		= 0x0004
};

enum {
    _vlistOCCURRENCE_ROW,
    _vlistOCCURRENCE_COLUMN,
    _vlistOCCURRENCE_ROW_COUNT,
    _vlistOCCURRENCE_COLUMN_COUNT,
    _vlistOCCURRENCE_OLD_ROW,
    _vlistOCCURRENCE_OLD_ROW_COUNT = _vlistOCCURRENCE_OLD_ROW,
    _vlistOCCURRENCE_OLD_COLUMN,
    _vlistOCCURRENCE_OLD_COLUMN_COUNT = _vlistOCCURRENCE_OLD_COLUMN,
    _vlistOCCURRENCE_STATE,
    _vlistOCCURRENCE_ORIENTATION = _vlistOCCURRENCE_STATE,
    _vlistOCCURRENCE_VALUE_COUNT
};


/*
 * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * *
 */

struct vlist {
    vobject	     object;

    void	    *dataset;
    int		     rowCount;
    int		     columnCount;
    vlistCellValueSetterProc	cellValueSetter;
    vlistCellValueGetterProc	cellValueGetter;
    vlistNameCellProc		cellNamer;
    vlistselection **selectionList;
    vlistOccurrence *savedOccurrence;
    void	    *data;
    short            selections;
    short	     usedSelections;
    short	     flags;
    short	     lock;
};


#define vlistCLASS(SUPER, LIST, SELECTION) 				      \
vobjectCLASS(SUPER, LIST);						      \
									      \
vclassMETHOD_RET (vlistMAKE_MAJOR_RESOURCE, vresource,			      \
		  (LIST *list, vresource resource));			      \
vclassMETHOD_RET (vlistMAKE_MINOR_RESOURCE, vresource, 			      \
		  (LIST *list, vresource resource, int index)); 	      \
vclassMETHOD_RET (vlistFIND_MINOR_RESOURCE, vresource, 			      \
		  (LIST *list, vresource resource, int index)); 	      \
vclassMETHOD (vlistSTORE_CELL, (LIST *list, int row, int column,	      \
				vresource resource));			      \
vclassMETHOD (vlistLOAD_CELL, (LIST *list, int row, int column,	      	      \
			       vresource resource));	      		      \
vclassMETHOD (vlistSET_CELL_VALUE, (LIST *list, int row, int column, 	      \
				    const void *value)); 		      \
									      \
vclassMETHOD (vlistINSERT_RANGE, (LIST *list, int before, 		      \
				  int count, int type)); 		      \
vclassMETHOD (vlistREMOVE_RANGE, (LIST *list, int victim, 		      \
				  int count, int type)); 		      \
vclassMETHOD (vlistSWAP_RANGE, (LIST *list, int swap1, int swap2, 	      \
				int count, int type)); 			      \
vclassMETHOD (vlistMOVE_RANGE, (LIST *list, int move1, int move2, 	      \
				int count, int type)); 			      \
									      \
vclassMETHOD (vlistSET_ROW_COLUMN_COUNT, (LIST *list, int count, int type));  \
vclassMETHOD_RET (vlistGET_CELL_VALUE, const void*, (LIST *list, 	      \
						     int row, int column));   \
vclassMETHOD_RET (vlistFIND_CELL, int, (LIST *list, 			      \
					const vchar *name, int *row, 	      \
					int *column, 			      \
					int startRow, int startColumn,	      \
					int directionHint)); 		      \
vclassMETHOD_RET (vlistDETERMINE_CELL_NAME, const vchar*,		      \
		  (LIST *list, int row, int column));			      \
vclassMETHOD (vlistSORT, (LIST *list, int axis, int key, 		      \
			  vlistCellValueSorterFunc compar));		      \
vclassMETHOD (vlistSORT_BY_NAME, (LIST *list, int axis, int key, 	      \
				  vlistCellValueSorterFunc compar));	      \
vclassMETHOD (vlistOBSERVE_CELL_VALUE_CHANGE, (LIST *list, int row,	      \
					       int column)); 		      \
vclassMETHOD (vlistOBSERVE_INSERT_RANGE, (LIST *list, int before,	      \
					  int count, int type)); 	      \
vclassMETHOD (vlistOBSERVE_REMOVE_RANGE, (LIST *list, int victim,	      \
					  int count, int type)); 	      \
vclassMETHOD (vlistOBSERVE_SWAP_RANGE, (LIST *list, int index1, int index2,   \
					int count, int type)); 		      \
vclassMETHOD (vlistOBSERVE_MOVE_RANGE, (LIST *list, int from, int to,	      \
					int count, int type)); 		      \
vclassMETHOD (vlistOBSERVE_SELECT, (LIST *list, SELECTION *selection,	      \
				    int state)); 			      \
vclassMETHOD (vlistOBSERVE_SELECT_METHOD, (LIST *list, SELECTION *selection,  \
					   int newState));		      \
vclassMETHOD (vlistOBSERVE_SELECT_ATTRIBUTE, (LIST *list, 		      \
					      SELECTION *selection));	      \
vclassMETHOD (vlistOBSERVE_DATA_SET_CHANGE, (LIST *list)); 		      \
vclassMETHOD (vlistOBSERVE_ROW_COLUMN_COUNT_CHANGE, (LIST *list, 	      \
						     int prevCount,	      \
						     int newCount, 	      \
						     int type)); 	      \
vclassMETHOD (vlistOBSERVE_ORIENTATION_CHANGE, (LIST *list,		      \
						int newDirection));	      \
vclassMETHOD (vlistOBSERVE_DESTROY, (LIST *list));			      \
vclassMETHOD (vlistOBSERVE_SORT, (LIST *list, int state));		      \
vclassMETHOD (vlistSET_DATA, (LIST *list, void *data));			      \
vclassMETHOD (vlistSET_DATASET, (LIST *list, void *dataset, int size));	      \
vclassMETHOD (vlistSET_ORIENTATION, (LIST *list, int direction));	      \
									      \
/* these are deprecated and exist only for backward-compatibility.  */ 	      \
									      \
vclassMETHOD (vlistINSERT_ROW_COLUMN, (LIST *list, int beforeRowCol, 	      \
				       int type));		    	      \
vclassMETHOD (vlistREMOVE_ROW_COLUMN, (LIST *list, int victim, int type));    \
vclassMETHOD (vlistSWAP_ROW_COLUMN, (LIST *list, int swap1, int swap2,        \
				    int type));                               \
vclassMETHOD (vlistMOVE_ROW_COLUMN, (LIST *list, int from, int to, int type))



struct vlistClass {
    vlistCLASS(vlistClass, vlist, vlistselection);
};


struct vlistOccurrence {
    voccurrence		 super;

    int			 type;
    vlistselection      *selection;
    int		         values[_vlistOCCURRENCE_VALUE_COUNT];	 
};

#define vlistOCCURRENCE_CLASS(CLASS, OCCURRENCE)			     \
    voccurrenceCLASS(CLASS, OCCURRENCE)

struct vlistOccurrenceClass
{
  vlistOCCURRENCE_CLASS(vlistOccurrenceClass, vlistOccurrence);
};


struct vlistObserver {
    vobserver	 super;

    vlist	*owner;
};


#define vlistObserverCLASS(SUPER, OBSERVER, SELECTION) 			      \
vobserverCLASS(SUPER, OBSERVER);					      \
vclassMETHOD (vlistObserverCELL_VALUE_CHANGE, (OBSERVER *obsr, 		      \
					       int row, int column)); 	      \
vclassMETHOD (vlistObserverINSERT_RANGE, (OBSERVER *obsr, int before, 	      \
					  int count, int type)); 	      \
vclassMETHOD (vlistObserverREMOVE_RANGE, (OBSERVER *obsr, int victim, 	      \
					  int count, int type)); 	      \
vclassMETHOD (vlistObserverSWAP_RANGE, (OBSERVER *obsr, int index1, 	      \
					int index2, int count, int type));    \
vclassMETHOD (vlistObserverMOVE_RANGE, (OBSERVER *obsr, int from, int to,     \
					int count, int type)); 		      \
									      \
vclassMETHOD (vlistObserverSELECT, (OBSERVER *obsr, SELECTION *selection,     \
				    int thingie)); 			      \
vclassMETHOD (vlistObserverSELECT_METHOD, (OBSERVER *obsr, 		      \
					   SELECTION *selection,  	      \
					   int newState)); 		      \
vclassMETHOD (vlistObserverSELECT_ATTRIBUTE, (OBSERVER *obsr, 		      \
					      SELECTION *selection));	      \
vclassMETHOD (vlistObserverDATA_SET_CHANGE, (OBSERVER *obsr)); 		      \
vclassMETHOD (vlistObserverROW_COLUMN_COUNT_CHANGE, (OBSERVER *obsr, 	      \
						     int prevCount, 	      \
						     int newCount, int type));\
vclassMETHOD (vlistObserverORIENTATION_CHANGE, (OBSERVER *obsr,		      \
						int newDirection));	      \
vclassMETHOD (vlistObserverDESTROY, (OBSERVER *obsr)); 			      \
vclassMETHOD (vlistObserverSORT, (OBSERVER *obsr, int state)); 		      \
									      \
/* these are deprecated and exist only for backward-compatibility. */ 	      \
									      \
vclassMETHOD (vlistObserverINSERT_ROW_COLUMN, (OBSERVER *obsr, int before,    \
					       int type)); 		      \
vclassMETHOD (vlistObserverREMOVE_ROW_COLUMN, (OBSERVER *obsr, int victim,    \
					       int type)); 		      \
vclassMETHOD (vlistObserverSWAP_ROW_COLUMN, (OBSERVER *obsr, int index1,      \
					     int index2, int type)); 	      \
vclassMETHOD (vlistObserverMOVE_ROW_COLUMN, (OBSERVER *obsr, int from, int to,\
					     int type))


struct vlistObserverClass {
    vlistObserverCLASS(vlistObserverClass, vlistObserver, vlistselection);
};


vportALIAS(vlistObserverIterator, vobservableObserverIterator)

vportALIAS(vlistIterator, vlistselectionIterator)


/*
 * * * * * * * * * * PRIVATE FUNCTION PROTOTYPES * * * * * * * * * *
 */


void _vlistSendInsertRowColumn(vlist *list, int before, int type);
void _vlistSendRemoveRowColumn(vlist *list, int victim, int type);
void _vlistSendSwapRowColumn(vlist *list, int swap1, int swap2, int type);
void _vlistSendMoveRowColumn(vlist *list, int from, int to, int type);
void _vlistSendSetRowColumnCount(vlist *list, int count, int type);

void _vlistCallCellValueSetter(vlist *list, int row, int column,
			       const void *pointer);
const void *_vlistCallCellValueGetter(vlist *list, int row, int column);


/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * *
 */


#define vlistGetObject(l)	(vportBASE_OBJECT((l), object))
#define vlistGetObservable(l) \
    vobjectGetObservable(vlistGetObject(l))
#define vlistGetLoadable(l) \
    vobservableGetLoadable(vlistGetObservable(l))
#define vlistGetInstance(l) \
    vloadableGetInstance(vlistGetLoadable(l))
#define vlistGetClass(l)        \
	((vlistClass*)vobservableGetClass(vlistGetObservable(l)))

#define vlistCreateOfClass(c) \
	((vlist*) vobservableCreateOfClass((vobservableClass *)(c)))
#define vlistCreate() \
	(vlistCreateOfClass(vlistGetDefaultClass()))

#define vlistInitOfClass(i,c) \
	vobservableInitOfClass(vlistGetObservable(i), (vobservableClass*)(c))
#define vlistInit(l) \
	vlistInitOfClass(l, vlistGetDefaultClass())

#define vlistDestroy(l) \
        vobservableDestroy(vlistGetObservable(l))

#define vlistClone(l) \
	((vlist*)vobservableClone(vlistGetObservable(l)))
#define vlistCopyInit(l,t) \
	vobservableCopyInit(vlistGetObservable((l)), vlistGetObservable((t)))
#define vlistCopy(l,t) \
	vobservableCopy(vlistGetObservable((l)), vlistGetObservable((t)))

#define vlistLoad(r) \
	((vlist*)vobservableLoad(r))
#define vlistLoadInit(l,r) \
        vobservableLoadInit(vlistGetObservable(l), r)
#define vlistStore(l,r) \
	vobservableStore(vlistGetObservable(l), r)

#define vlistDump(l,s) \
	vobservableDump(vlistGetObservable(l), s)

#define vlistGetData(l)		((l)->data)
#define vlistGetDataset(l)	((l)->dataset)

#define vlistGetRowCount(l)	((l)->rowCount)
#define vlistGetColumnCount(l)	((l)->columnCount)
#define vlistSetCellNamer(l,p)	(l)->cellNamer = (p)
#define vlistGetCellNamer(l)	((l)->cellNamer)

#define vlistGetOrientation(l)	(((l)->flags & _vlistROW_MAJOR)  \
				 ? vlistROW_MAJOR : vlistCOLUMN_MAJOR)

#define vlistMGetCellValue(l,r,c) \
     (((l)->flags&_vlistCOLUMN_MAJOR) \
      ? ((*((void***)((*((void***)(l)->dataset))[(c)])))[(r)]) \
      : ((*((void***)((*((void***)(l)->dataset))[(r)])))[(c)]))

#define vlistInsertRow(l,b)	\
    _vlistSendInsertRowColumn(l, b, vlistROW)
#define vlistInsertColumn(l,b)	\
    _vlistSendInsertRowColumn(l, b, vlistCOLUMN)

#define vlistRemoveRow(l,r)	\
    _vlistSendRemoveRowColumn(l, r, vlistROW)
#define vlistRemoveColumn(l,c)	\
    _vlistSendRemoveRowColumn(l, c, vlistCOLUMN)

#define vlistSwapRows(l,r1,r2)	\
    _vlistSendSwapRowColumn(l, r1, r2, vlistROW)
#define vlistSwapColumns(l,c1,c2) \
    _vlistSendSwapRowColumn(l, c1, c2, vlistCOLUMN)

#define vlistMoveRow(l,f,t)	\
    _vlistSendMoveRowColumn(l, f, t, vlistROW)
#define vlistMoveColumn(l,f,t)	\
    _vlistSendMoveRowColumn(l, f, t, vlistCOLUMN)

#define vlistSetRowCount(l,rc)	\
    _vlistSendSetRowColumnCount(l, rc, vlistROW)
#define vlistSetColumnCount(l,cc) \
    _vlistSendSetRowColumnCount(l, cc, vlistCOLUMN)


/*
 * List observers
 */

#define vlistGetObserverObserver(o)	vportBASE_OBJECT(o, super)
#define vlistGetObserverObservable(o) \
    vobserverGetObservable(vlistGetObserverObserver(o))
#define vlistGetObserverLoadable(o) \
    vobservableGetLoadable(vlistGetObserverObservable(o))
#define vlistGetObserverInstance(o) \
    vloadableGetInstance(vlistGetObserverLoadable(o))
#define vlistGetObserverClass(o) \
    ((vlistObserverClass*)vloadableGetClass(vlistGetObserverLoadable(o)))

#define vlistCreateObserverOfClass(c)   	\
    ((vlistObserver *) vloadableCreateOfClass((vloadableClass *)(c)))
#define vlistCreateObserver()		\
    (vlistCreateObserverOfClass(vlistGetDefaultObserverClass()))
#define vlistInitObserverOfClass(g, c)  	\
    vloadableInitOfClass(vlistGetObserverLoadable(g), (vloadableClass*)(c))
#define vlistInitObserver(g)	     	\
    vlistInitObserverOfClass(g, vlistGetDefaultObserverClass())
#define vlistDestroyObserver(g)	\
    vloadableDestroy(vlistGetObserverLoadable(g))

#define vlistCloneObserver(g)	\
    ((vlistObserver *) vloadableClone(vlistGetObserverLoadable(g)))
#define vlistCopyObserver(g,t)	\
    vloadableCopy(vlistGetObserverLoadable(g), vlistGetObserverLoadable(t))
#define vlistCopyInitObserver(g,t)      	\
    vloadableCopyInit(vlistGetObserverLoadable(g), vlistGetObserverLoadable(t))

#define vlistSetObserverData(o,d) \
    vobserverSetData(vlistGetObserverObserver(o), d)
#define vlistGetObserverData(o) \
    vobserverGetData(vlistGetObserverObserver(o))

#define vlistSetObserverOwner(o,l) \
    ((o)->owner = (l))
#define vlistGetObserverOwner(o) \
    ((o)->owner)

#define vlistDisableObserver(o) \
    vobserverDisable(vlistGetObserverObserver(o))
#define vlistEnableObserver(o) \
    vobserverEnable(vlistGetObserverObserver(o))
#define vlistObserverIsEnabled(o)  \
    vobserverIsEnabled(vlistGetObserverObserver(o))


#define vlistInstallObserver(e,o) \
    vobservableInstallObserver(vlistGetObservable(e), \
			       vlistGetObserverObservable(o))
#define vlistInstallObserverOwned(e,o) \
    vobservableInstallObserverOwned(vlistGetObservable(e), \
				    vlistGetObserverObservable(o))
#define vlistUninstallObserver(e,o) \
    vobservableUninstallObserver(vlistGetObservable(e), \
				    vlistGetObserverObservable(o))

/*
 * List iterators
 */

#define _vlistGetIteratorIterator(i) \
    _vlistselectionGetIteratorIterator((vlistselectionIterator *)(i))
#define vlistNextIterator(i) \
    viteratorNext(_vlistGetIteratorIterator(i))
#define vlistDestroyIterator(i) \
    viteratorDestroy(_vlistGetIteratorIterator(i))
#define vlistGetIteratorRow(i) \
    vlistselectionGetIteratorRow((vlistselectionIterator *)(i))
#define vlistGetIteratorColumn(i) \
    vlistselectionGetIteratorColumn((vlistselectionIterator *)(i))
#define vlistGetIteratorValue(i) \
    vlistselectionGetIteratorValue((vlistselectionIterator *)(i))

#define vlistNextObserverIterator(i) \
    vobservableNextObserverIterator(i)
#define vlistDestroyObserverIterator(i) \
    vobservableDestroyObserverIterator(i)
#define vlistGetObserverIteratorObserver(i) \
    ((vlistObserver *) vobservableGetObserverIteratorObserver( \
					(vobservableObserverIterator *) i))

/*
 * List occurrences
 */

#define vlistGetOccurrenceOccurrence(o)	vportBASE_OBJECT(o, super)
#define vlistGetOccurrenceInstance(o) \
    voccurrenceGetInstance(vlistGetOccurrenceOccurrence(o))
#define vlistGetOccurrenceClass(o) \
    ((vlistOccurrenceClass *) \
     voccurrenceGetClass(vlistGetOccurrenceOccurrence(o)))

#define vlistCreateOccurrenceOfClass(c)   	\
    ((vlistOccurrence *) voccurrenceCreateOfClass((voccurrenceClass *)(c)))
#define vlistCreateOccurrence()		\
    (vlistCreateOccurrenceOfClass(vlistGetDefaultOccurrenceClass()))
#define vlistInitOccurrenceOfClass(o, c)  	\
    voccurrenceInitOfClass(vlistGetOccurrenceOccurrence(o), \
			   (voccurrenceClass*)(c))
#define vlistInitOccurrence(o)	     	\
    vlistInitOccurrenceOfClass(o, vlistGetDefaultOccurrenceClass())
#define vlistDestroyOccurrence(o)	\
    voccurrenceDestroy(vlistGetOccurrenceOccurrence(o))

#define vlistGetOccurrenceList(o) \
    ((vlist *) voccurrenceGetAnnouncer(vlistGetOccurrenceOccurrence(o)))
#define vlistGetOccurrenceType(o) \
    ((o)->type)
#define vlistGetOccurrenceSelection(o) \
    ((o)->selection)
#define vlistGetOccurrenceRow(o) \
    ((o)->values[_vlistOCCURRENCE_ROW])
#define vlistGetOccurrenceColumn(o) \
    ((o)->values[_vlistOCCURRENCE_COLUMN])
#define vlistGetOccurrenceRowCount(o) \
    ((o)->values[_vlistOCCURRENCE_ROW_COUNT])
#define vlistGetOccurrenceColumnCount(o) \
    ((o)->values[_vlistOCCURRENCE_COLUMN_COUNT])
#define vlistGetOccurrenceOldRow(o) \
    ((o)->values[_vlistOCCURRENCE_OLD_ROW])
#define vlistGetOccurrenceOldColumn(o) \
    ((o)->values[_vlistOCCURRENCE_OLD_COLUMN])
#define vlistGetOccurrenceOldRowCount(o) \
    ((o)->values[_vlistOCCURRENCE_OLD_ROW_COUNT])
#define vlistGetOccurrenceOldColumnCount(o) \
    ((o)->values[_vlistOCCURRENCE_OLD_COLUMN_COUNT])
#define vlistGetOccurrenceState(o) \
    ((o)->values[_vlistOCCURRENCE_STATE])
#define vlistGetOccurrenceOrientation(o) \
    ((o)->values[_vlistOCCURRENCE_ORIENTATION])

#define vlistSetOccurrenceList(o, l) \
    voccurrenceSetAnnouncer(vlistGetOccurrenceOccurrence(o), \
			    vlistGetInstance(l))
#define vlistSetOccurrenceType(o, t) \
    ((o)->type = (t))
#define vlistSetOccurrenceSelection(o, s) \
    ((o)->selection = (s))
#define vlistSetOccurrenceRow(o, v) \
    ((o)->values[_vlistOCCURRENCE_ROW] = (v))
#define vlistSetOccurrenceColumn(o, v) \
    ((o)->values[_vlistOCCURRENCE_COLUMN] = (v))
#define vlistSetOccurrenceRowCount(o, v) \
    ((o)->values[_vlistOCCURRENCE_ROW_COUNT] = (v))
#define vlistSetOccurrenceColumnCount(o, v) \
    ((o)->values[_vlistOCCURRENCE_COLUMN_COUNT] = (v))
#define vlistSetOccurrenceOldRow(o, v) \
    ((o)->values[_vlistOCCURRENCE_OLD_ROW] = (v))
#define vlistSetOccurrenceOldColumn(o, v) \
    ((o)->values[_vlistOCCURRENCE_OLD_COLUMN] = (v))
#define vlistSetOccurrenceOldRowCount(o, v) \
    ((o)->values[_vlistOCCURRENCE_OLD_ROW_COUNT] = (v))
#define vlistSetOccurrenceOldColumnCount(o, v) \
    ((o)->values[_vlistOCCURRENCE_OLD_COLUMN_COUNT] = (v))
#define vlistSetOccurrenceState(o, v) \
    ((o)->values[_vlistOCCURRENCE_STATE] = (v))
#define vlistSetOccurrenceOrientation(o, v) \
    ((o)->values[_vlistOCCURRENCE_ORIENTATION] = (v))

/*
 * Deprecation
 */

#define vlistGetDefaultSelectionClass() \
    vlistselectionGetDefaultClass()
#define vlistDestroySelection(l, s) \
    vlistselectionDestroy(s)
#define vlistCloneSelection(l, s) \
    vlistselectionClone(s)
#define vlistCopySelection(l, s, d) \
    vlistselectionCopy(s, d)
#define vlistSetSelectionImmutable(l, s, v) \
    vlistselectionSetImmutable(s, v)
#define vlistIsSelectionImmutable(l, s) \
    vlistselectionIsImmutable(s)
#define vlistGetSelectedCell(l, s, r, c) \
    vlistselectionGetSelectedCell(s, r, c)
#define vlistSelectRange(l, s, r, c, d, a) \
    vlistselectionSelectRange(s, r, c, d, a)
#define vlistUnselectRange(l, s, r, c, d, a) \
    vlistselectionUnselectRange(s, r, c, d, a)
#define vlistSelectCell(l, s, r, c) \
    vlistselectionSelectCell(s, r, c)
#define vlistUnselectCell(l, s, r, c) \
    vlistselectionUnselectCell(s, r, c)
#define vlistSelectRow(l, s, r) \
    vlistselectionSelectRow(s, r)
#define vlistUnselectRow(l, s, r) \
    vlistselectionUnselectRow(s, r)
#define vlistSelectColumn(l, s, c) \
    vlistselectionSelectColumn(s, c)
#define vlistUnselectColumn(l, s, c) \
    vlistselectionUnselectColumn(s, c)
#define vlistSelectAll(l, s) \
    vlistselectionSelectAll(s)
#define vlistUnselectAll(l, s) \
    vlistselectionUnselectAll(s)
#define vlistIsCellSelected(l, s, r, c) \
    vlistselectionIsCellSelected(s, r, c)
#define vlistCountSelectedCells(l, s) \
    vlistselectionGetSelectedCellCount(s)
#define vlistDetermineSelectionBounds(l, s, r, c, d, a) \
    vlistselectionDetermineBounds(s, r, c, d, a)
#define vlistIsSelectionEmpty(l, s) \
    vlistselectionIsEmpty(s)
#define vlistUnionSelections(l, s1, s2) \
    vlistselectionCreateUnion(s1, s2)
#define vlistIntersectSelections(l, s1, s2) \
    vlistselectionCreateIntersection(s1, s2)
#define vlistComplementSelection(l, s) \
    vlistselectionCreateComplement(s)
#define vlistDifferenceSelections(l, s1, s2) \
    vlistselectionCreateDifference(s1, s2)
#define vlistSetSelectMethod(l, s, m) \
    vlistselectionSetSelectMethod(s, m)
#define vlistSetAtLeastOneSelection(l, s, v) \
    vlistselectionSetAtLeastOne(s, v)
#define vlistHasAtLeastOneSelection(l, s) \
    vlistselectionHasAtLeastOne(s)
#define vlistSetExtendRowSelection(l, s, v) \
    vlistselectionSetExtendRow(s, v)
#define vlistHasExtendRowSelection(l, s) \
    vlistselectionHasExtendRow(s)
#define vlistSetExtendColumnSelection(l, s, v) \
    vlistselectionSetExtendColumn(s, v)
#define vlistHasExtendColumnSelection(l, s) \
    vlistselectionHasExtendColumn(s)
#define vlistGetSelectMethod(l, s) \
    vlistselectionGetSelectMethod(s)
#define vlistDumpSelection(s, f) \
    vlistselectionDump(s, f)

#define vlistGetDefaultSelectionRangeIteratorClass() \
    vlistselectionGetDefaultRangeIteratorClass()
#define vlistNextSelectionRangeIterator(i) \
    vlistselectionNextRangeIterator(i)
#define vlistDestroySelectionRangeIterator(i) \
    vlistselectionDestroyRangeIterator(i)
#define vlistGetSelectionRangeIteratorValue(i) \
    vlistselectionGetRangeIteratorValue(i)
#define vlistGetSelectionRangeIteratorRow(i) \
    vlistselectionGetRangeIteratorRow(i)
#define vlistGetSelectionRangeIteratorColumn(i) \
    vlistselectionGetRangeIteratorColumn(i)
#define vlistGetSelectionRangeIteratorRowCount(i) \
    vlistselectionGetRangeIteratorRowCount(i)
#define vlistGetSelectionRangeIteratorColumnCount(i) \
    vlistselectionGetRangeIteratorColumnCount(i)
#define vlistGetSelectionRangeIteratorRange(i, r) \
    vlistselectionGetRangeIteratorRange(i, r)

#define vlistGetDefaultSelectionIteratorClass() \
    vlistselectionGetDefaultIteratorClass()
#define vlistNextSelectionIterator(i) \
    vlistselectionNextIterator(i)
#define vlistDestroySelectionIterator(i) \
    vlistselectionDestroyIterator(i)
#define vlistGetSelectionIteratorValue(i) \
    vlistselectionGetIteratorValue(i)
#define vlistGetSelectionIteratorRow(i) \
    vlistselectionGetIteratorRow(i)
#define vlistGetSelectionIteratorColumn(i) \
    vlistselectionGetIteratorColumn(i)

#define vlistGetIteratorRangeRowCount(i) \
    vlistselectionGetRangeIteratorRowCount(i)
#define vlistGetIteratorRangeColumnCount(i) \
    vlistselectionGetRangeIteratorColumnCount(i)
#define vlistGetIteratorRange(i, r) \
    vlistselectionGetRangeIteratorRange(i, r)

#define vlistSelectionGetClass		vlistselectionGetClass
#define vlistSelectionGetObservable	vlistselectionGetObservable
#define vlistSelectionGetLoadable	vlistselectionGetLoadable
#define vlistSelectionGetInstance	vlistselectionGetInstance
#define vlistSelectionCreate		vlistselectionCreate
#define vlistSelectionCreateOfClass	vlistselectionCreateOfClass
#define vlistSelectionInit		vlistselectionInit
#define vlistSelectionInitOfClass	vlistselectionInitOfClass
#define vlistSelectionDestroy		vlistselectionDestroy
#define vlistSelectionClone		vlistselectionClone
#define vlistSelectionCopyInit		vlistselectionCopyInit
#define vlistSelectionCopy		vlistselectionCopy
#define vlistSelectionLoad		vlistselectionLoad
#define vlistSelectionLoadInit		vlistselectionLoadInit
#define vlistSelectionStore		vlistselectionStore
#define vlistSelectionDump		vlistselectionDump
#define vlistSelectionSetList		vlistselectionSetList
#define vlistSelectionGetList		vlistselectionGetList
#define vlistSelectionSetImmutable	vlistselectionSetImmutable
#define vlistSelectionIsImmutable	vlistselectionIsImmutable
#define vlistSelectionGetSelectedCell	vlistselectionGetSelectedCell
#define vlistSelectionSelectRange	vlistselectionSelectRange
#define vlistSelectionUnselectRange	vlistselectionUnselectRange
#define vlistSelectionSelectCell	vlistselectionSelectCell
#define vlistSelectionUnselectCell	vlistselectionUnselectCell
#define vlistSelectionSelectRow		vlistselectionSelectRow
#define vlistSelectionUnselectRow	vlistselectionUnselectRow
#define vlistSelectionSelectColumn	vlistselectionSelectColumn
#define vlistSelectionUnselectColumn	vlistselectionUnselectColumn
#define vlistSelectionSelectAll		vlistselectionSelectAll
#define vlistSelectionUnselectAll	vlistselectionUnselectAll
#define vlistSelectionIsCellSelected	vlistselectionIsCellSelected
#define vlistSelectionGetSelectedCellCount vlistselectionGetSelectedCellCount
#define vlistSelectionGetMaxRowCount	vlistselectionGetMaxRowCount
#define vlistSelectionGetMaxColumnCount	vlistselectionGetMaxColumnCount
#define vlistSelectionDetermineBounds	vlistselectionDetermineBounds
#define vlistSelectionIsEmpty		vlistselectionIsEmpty
#define vlistSelectionCreateUnion	vlistselectionCreateUnion
#define vlistSelectionCreateIntersection vlistselectionCreateIntersection
#define vlistSelectionCreateComplement	vlistselectionCreateComplement
#define vlistSelectionCreateDifference	vlistselectionCreateDifference
#define vlistSelectionSetSelectMethod	vlistselectionSetSelectMethod
#define vlistSelectionSetAtLeastOne	vlistselectionSetAtLeastOne
#define vlistSelectionHasAtLeastOne	vlistselectionHasAtLeastOne
#define vlistSelectionSetExtendRow	vlistselectionSetExtendRow
#define vlistSelectionHasExtendRow	vlistselectionHasExtendRow
#define vlistSelectionSetExtendColumn	vlistselectionSetExtendColumn
#define vlistSelectionHasExtendColumn	vlistselectionHasExtendColumn
#define vlistSelectionGetSelectMethod	vlistselectionGetSelectMethod


/*
 * * * * * * * * * * PRIVATE FUNCTION MESSAGE DEFINITIONS * * * * * * * * * *
 */

#define _vlistSendInsertRowColumn(l,b,t)	\
	vclassSend(vlistGetClass(l), vlistINSERT_ROW_COLUMN, (l, b, t))
#define _vlistSendRemoveRowColumn(l,r,t)	\
	vclassSend(vlistGetClass(l), vlistREMOVE_ROW_COLUMN, (l, r, t))
#define _vlistSendSwapRowColumn(l,s1,s2,t)	\
	vclassSend(vlistGetClass(l), vlistSWAP_ROW_COLUMN, (l, s1, s2, t))
#define _vlistSendMoveRowColumn(l,o,n,t)	\
	vclassSend(vlistGetClass(l),vlistMOVE_ROW_COLUMN, (l, o, n, t))
#define _vlistSendSetRowColumnCount(l,c,t)	\
	vclassSend(vlistGetClass(l), vlistSET_ROW_COLUMN_COUNT, (l, c, t))
#define vlistSetCellValue(l,r,c,v) \
	vclassSend(vlistGetClass(l), vlistSET_CELL_VALUE, (l,r,c,v))
#define vlistGetCellValue(l,r,c)   \
	vclassSend(vlistGetClass(l), vlistGET_CELL_VALUE, (l,r,c))
#define vlistFindCell(l,s,r,c,sr,sc,dh)  \
	vclassSend(vlistGetClass(l), vlistFIND_CELL, (l,s,r,c,sr,sc,dh))
#define vlistSort(l,a,k,c) 	\
	vclassSend(vlistGetClass(l), vlistSORT, (l,a,k,c))
#define vlistSortByName(l,a,k,c) \
	vclassSend(vlistGetClass(l), vlistSORT_BY_NAME, (l,a,k,c))

#define vlistInsertRange(l,b,c,t) \
	vclassSend(vlistGetClass(l), vlistINSERT_RANGE,(l,b,c,t))
#define vlistRemoveRange(l,v,c,t) \
	vclassSend(vlistGetClass(l), vlistREMOVE_RANGE,(l,v,c,t))
#define vlistSwapRange(l,s1,s2,c,t) \
	vclassSend(vlistGetClass(l), vlistSWAP_RANGE,(l,s1,s2,c,t))
#define vlistMoveRange(l,m1,m2,c,t) \
	vclassSend(vlistGetClass(l), vlistMOVE_RANGE,(l,m1,m2,c,t))

#define vlistSetData(l,d) \
	vclassSend(vlistGetClass(l), vlistSET_DATA, (l, d))
#define vlistSetDataset(l,d,s) \
	vclassSend(vlistGetClass(l), vlistSET_DATASET, (l, d, s))
#define vlistDetermineCellName(l,r,c) \
	vclassSend(vlistGetClass(l), vlistDETERMINE_CELL_NAME, (l,r,c))
#define vlistSetOrientation(l,d) \
	vclassSend(vlistGetClass(l), vlistSET_ORIENTATION, (l,d))

#define vlistStoreCell(l,r,c,s) \
	vclassSend(vlistGetClass(l), vlistSTORE_CELL, (l,r,c,s))
#define vlistLoadCell(l,r,c,s) \
	vclassSend(vlistGetClass(l), vlistLOAD_CELL, (l,r,c,s))

#define vlistMakeMajorResource(l,r) \
	vclassSend(vlistGetClass(l), vlistMAKE_MAJOR_RESOURCE, (l,r))
#define vlistMakeMinorResource(l,r,i) \
	vclassSend(vlistGetClass(l), vlistMAKE_MINOR_RESOURCE, (l,r,i))
#define vlistFindMinorResource(l,r,i) \
	vclassSend(vlistGetClass(l), vlistFIND_MINOR_RESOURCE, (l,r,i))

vportEND_CPLUSPLUS_EXTERN_C


#endif


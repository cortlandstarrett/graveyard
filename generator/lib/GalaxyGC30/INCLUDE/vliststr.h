/* $Id: vliststr.h,v 1.15 1994/09/29 20:52:38 markd Exp $ */

/************************************************************

    vliststr.h

    C Interface for the List Manager, string list data objects

    (c) Copyright Visix Software
    All rights reserved

************************************************************/

#ifndef vliststrINCLUDED
#define vliststrINCLUDED 1

#ifndef  vportINCLUDED
#include <vport.h>
#endif

#ifndef  vscribeINCLUDED
#include vscribeHEADER
#endif

#ifndef  vclassINCLUDED
#include vclassHEADER
#endif

#ifndef  vresourceINCLUDED
#include vresourceHEADER
#endif

#ifndef  vlistINCLUDED
#include vlistHEADER
#endif


vportBEGIN_CPLUSPLUS_EXTERN_C


/*
 * * * * * * * * * * * PUBLIC TYPE DEFINITIONS * * * * * * * * * * *
 */

typedef struct vliststr vliststr;
typedef struct vliststrClass vliststrClass;



/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */

void vliststrStartup (
    void
    );


vliststrClass *vliststrGetDefaultClass (
    void
    );

vliststr *vliststrCreate (
    void
    );

vliststr *vliststrCreateOfClass (
    vliststrClass		*clas
    );

vliststr *vliststrClone (
    vliststr			*list
    );

void vliststrInit (
    vliststr			*list
    );

void vliststrInitOfClass (
    vliststr			*list,
    vliststrClass		*clas
    );

void vliststrDestroy (
    vliststr			*list
    );

void vliststrCopy (
    vliststr			*list,
    vliststr			*target
    );

void vliststrCopyInit (
    vliststr			*list,
    vliststr			*target
    );

vliststr *vliststrLoad (
    vresource			 resource
    );

void vliststrLoadInit (
    vliststr			*list,
    vresource			 resource
    );

void vliststrStore (
    vliststr			*list,
    vresource			 resource
    );

vresource vliststrMakeMajorResource (
    vliststr			*list,
    vresource 			 resource
    );

vresource vliststrMakeMinorResource (
    vliststr       		*list,
    vresource			 resource,
    int				 index
    );

vresource vliststrFindMinorResource (
    vliststr			*list,
    vresource			 resource,
    int				 index
    );

vliststrClass *vliststrGetClass (
    vliststr			*list
    );

vlist *vliststrGetList (
    vliststr			*list
    );

vobject *vliststrGetObject (
    vliststr			*list
    );

void vliststrSetData (
    vliststr			*list,
    void			*data
    );

void *vliststrGetData (
    vliststr			*list
    );

void vliststrSetDataset (
    vliststr			*list,
    void			*dataset,
    int				 size
    );

void *vliststrGetDataset (
    vliststr		        *list
    );

void vliststrStoreCell (
    vliststr 		        *list,
    int 			 row,
    int 			 column,
    vresource			 resource
    );

void vliststrLoadCell (
    vliststr 			*list,
    int 	 		 row,
    int 			 column,
    vresource			 resource
    );

void vliststrSetOrientation (
    vliststr		   *list,
    int	 		    direction /* vlistROW_MAJOR or vlistCOLUMN_MAJOR */
    );


int vliststrGetOrientation (
    vliststr		    	*list
    );

void vliststrSetCellValueSetter (
    vliststr			*list,
    vlistCellValueSetterProc	 func
    );

void vliststrSetCellValueGetter (
    vliststr			*list,
    vlistCellValueGetterProc	 func
    );

void vliststrSort (
    vliststr			*list,
    int				 axis,
    int				 key,
    vlistCellValueSorterFunc	 compar
    );

void vliststrSortByName (
    vliststr			*list,
    int		 		 axis,
    int				 key,
    vlistCellValueSorterFunc	 compar
    );

int vliststrFindCell (
    vliststr			*list,
    vchar			*name,
    int				*row,
    int				*column,
    int				 startRow,
    int				 startColumn,
    int				 directionHint
    );

void vliststrSetCellNamer (
    vliststr			*list,
    vlistNameCellProc		 proc
    );

vlistNameCellProc vliststrGetCellNamer (
    vliststr			*list
    );

const vchar *vliststrDetermineCellName (
    vliststr			*list,
    int				 row,
    int				 column
    );

void vliststrSetCellValue (
    vliststr			*list,
    int				 row,
    int				 column,
    const void			*value
    );

void vliststrSetCellValueScribed (
    vliststr			*list,
    int				 row,
    int				 column,
    vscribe			*scribe
    );

const void *vliststrGetCellValue (
    vliststr			*list,
    int				 row,
    int				 column
    );

vscribe *vliststrGetCellValueScribed (
    vliststr			*list,
    int			         row,
    int				 column
    );

void vliststrInsertRow (
    vliststr			*list,
    int				 beforeRow
    );

void vliststrInsertColumn (
    vliststr			*list,
    int				 beforeColumn
    );

void vliststrRemoveRow (
    vliststr			*list,
    int				 row
    );

void vliststrRemoveColumn (
    vliststr			*list,
    int				 column
    );

void vliststrSwapRows (
    vliststr			*list,
    int				 row1,
    int				 row2
    );

void vliststrSwapColumns (
    vliststr			*list,
    int				 column1,
    int				 column2
    );

void vliststrMoveRow (
    vliststr			*list,
    int				 from,
    int				 to
    );

void vliststrMoveColumn (
    vliststr			*list,
    int				 from,
    int				 to
    );

void vliststrInsertRange (
    vliststr			*list,
    int				 before,
    int				 count,
    int				 type
    );

void vliststrRemoveRange (
    vliststr			*list,
    int				 victim,
    int				 count,
    int				 type
    );

void vliststrSwapRange (
    vliststr			*list,
    int				 swap1,
    int				 swap2,
    int				 count,
    int				 type
    );

void vliststrMoveRange (
    vliststr			*list,
    int				 moveFrom,
    int				 moveTo,
    int				 count,
    int				 type
    );

void vliststrSetRowCount (
    vliststr			*list,
    int				 rowCount
    );

int vliststrGetRowCount (
    vliststr			*list
    );

void vliststrSetColumnCount (
    vliststr			*list,
    int				 columnCount
    );

int vliststrGetColumnCount (
    vliststr			*list
    );

vlistSelection *vliststrCreateSelection (
    vliststr			*list
    );

void vliststrDestroySelection (
    vliststr			*list,
    vlistSelection		*selection
    );

vlistSelection *vliststrCloneSelection (
    vliststr			*list,
    vlistSelection		*selection
    );

void vliststrCopySelection (
    vliststr			*list,
    vlistSelection		*source,
    vlistSelection		*destination
    );

void vliststrSetSelectionImmutable (
    vliststr			*list,
    vlistSelection		*selection,
    int				 onOff
    );

int vliststrIsSelectionImmutable (
    vliststr			*list,
    vlistSelection		*selection
    );

void vliststrGetSelectedCell (
    vliststr			*list,
    vlistSelection		*selection,
    int				*row,
    int				*column
    );

void vliststrSelectRange (
    vliststr			*list,
    vlistSelection		*selection,
    int				 row,
    int				 column,
    int				 numDown,
    int				 numAcross
    );

void vliststrUnselectRange (
    vliststr			*list,
    vlistSelection		*selection,
    int				 row,
    int				 column,
    int				 numDown,
    int				 numAcross
    );

void vliststrSelectCell (
    vliststr			*list,
    vlistSelection		*selection,
    int				 row,
    int				 column
    );

void vliststrUnselectCell (
    vliststr			*list,
    vlistSelection		*selection,
    int				 row,
    int				 column
    );

void vliststrSelectRow (
    vliststr			*list,
    vlistSelection		*selection,
    int				 row
    );

void vliststrUnselectRow (
    vliststr			*list,
    vlistSelection		*selection,
    int				 row
    );

void vliststrSelectColumn (
    vliststr			*list,
    vlistSelection		*selection,
    int				 column
    );

void vliststrUnselectColumn (
    vliststr			*list,
    vlistSelection		*selection,
    int				 column
    );

void vliststrSelectAll (
    vliststr			*list,
    vlistSelection		*selection
    );

void vliststrUnselectAll (
    vliststr			*list,
    vlistSelection		*selection
    );

int vliststrIsCellSelected (
    vliststr			*list,
    vlistSelection		*selection,
    int				 row,
    int				 column
    );

long vliststrCountSelectedCells (
    vliststr			*list,
    vlistSelection		*selection
    );

void vliststrDetermineSelectionBounds (
    vliststr			*list,
    vlistSelection		*selection,
    int				*row,
    int				*column,
    int				*numDown,
    int				*numAcross
    );

void vliststrInitSelectionIterator (
    vlistIterator		*iterator,
    vlistSelection		*selection
    );

void vliststrInitIterator (
    vlistIterator		*iterator,
    vliststr			*list
    );

void vliststrInitSelectionRangeIterator (
    vlistIterator *iterator,
    vlistSelection *selection
    );

int vliststrNextIterator (
    vlistIterator		*iterator
    );

void vliststrDestroyIterator (
    vlistIterator		*iterator
    );

int vliststrGetIteratorRow (
    vlistIterator		*iterator
    );

int vliststrGetIteratorColumn (
    vlistIterator		*iterator
    );

int vliststrGetIteratorRangeRowCount (
    vlistIterator		*iterator
    );

int vliststrGetIteratorRangeColumnCount (
    vlistIterator		*iterator
    );

void vliststrGetIteratorRange (
    vlistIterator		*iterator,
    vrectLong			*rect     /* rect.x = column
					   * rect.y = row
					   * rect.w = column count
					   * rect.h = row count
					   */
    );

const void *vliststrGetIteratorValue (
    vlistIterator		*iterator
    );

int vliststrIsSelectionEmpty (
    vliststr			*list,
    vlistSelection		*selection
    );

void vliststrSetSelectMethod (
    vliststr			*list,
    vlistSelection		*selection,
    int				 method
    );

void vliststrSetAtLeastOneSelection (
    vliststr			*list,
    vlistSelection		*selection,
    int				 onOff
    );

int vliststrHasAtLeastOneSelection (
    vliststr			*list,
    vlistSelection		*selection
    );

void vliststrSetExtendRowSelection (
    vliststr			*list,
    vlistSelection		*selection,
    int				 onOff
    );

int vliststrHasExtendRowSelection (
    vliststr			*list,
    vlistSelection		*selection
    );

void vliststrSetExtendColumnSelection (
    vliststr			*list,
    vlistSelection		*selection,
    int				 onOff
    );

int vliststrHasExtendColumnSelection (
    vliststr			*list,
    vlistSelection		*selection
    );

int vliststrGetSelectMethod (
    vliststr			*list,
    vlistSelection		*selection
    );

void vliststrDump (
    vliststr			*list, 
    FILE			*stream
    );


/*
 * * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * *
 */

struct vliststr {
    vlist		 list;
    vlistSelection	*ownedStrings;
};


#define vliststrCLASS(SUPER, LIST, SELECTION)				\
  vlistCLASS(SUPER, LIST, SELECTION);					\
  vclassMETHOD(vliststrSET_CELL_VALUE_SCRIBED,				\
	      (LIST *list, int row, int column, vscribe *scribe));	\
vclassMETHOD_RET(vliststrGET_CELL_VALUE_SCRIBED, vscribe *,		\
	     (LIST *list, int row, int column))


struct vliststrClass {
    vliststrCLASS(vliststrClass, vliststr, vlistSelection);
};


/*
 * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * *
 */

#define vliststrCreateOfClass(c) \
  ((vliststr*)vlistCreateOfClass((vlistClass*)(c)))
#define vliststrCreate() \
  (vliststrCreateOfClass(vliststrGetDefaultClass()))
#define vliststrClone(l) \
  ((vliststr*)vlistClone(vliststrGetList(l)))
#define vliststrInitOfClass(l, c) \
  vlistInitOfClass(vliststrGetList(l), (vlistClass*)(c))
#define vliststrInit(l) \
  vliststrInitOfClass(l, vliststrGetDefaultClass())
#define vliststrCopyInit(l, t)		vlistCopyInit(vliststrGetList(l), \
					 vliststrGetList(t))
#define vliststrLoad(r)			((vliststr *)vlistLoad(r))
#define vliststrLoadInit(l, r)		(vlistLoadInit(vliststrGetList(l), r))
#define vliststrDestroy(l) \
  vlistDestroy(vliststrGetList(l))

#define vliststrGetObject(l)		(vlistGetObject(vliststrGetList(l)))
#define vliststrGetList(l)		(vportBASE_OBJECT((l), list))
#define vliststrGetClass(l)	        ((vliststrClass*)vlistGetClass \
					 (vliststrGetList(l)))

#define vliststrSetData(l, v)		vlistSetData(vliststrGetList(l), v)
#define vliststrGetData(l)		(vlistGetData(vliststrGetList(l)))
#define vliststrSetDataset(l, d, s)	vlistSetDataset(vliststrGetList(l), d, s)
#define vliststrGetDataset(l)		(vlistGetDataset(vliststrGetList(l)))

#define vliststrGetSelectedCell(l, s, r, c) \
           vlistGetSelectedCell(vliststrGetList(l), (s), (r), (c))

#define vliststrGetRowCount(l)		(vlistGetRowCount(vliststrGetList(l)))
#define vliststrGetColumnCount(l)	(vlistGetColumnCount(vliststrGetList(l)))

#define vliststrSetCellValueSetter(l, f) \
  vlistSetCellValueSetter(vliststrGetList(l), f)
#define vliststrSetCellValueGetter(l, f) \
  vlistSetCellValueGetter(vliststrGetList(l), f)

#define vliststrSelectCell(l, s, r, c) \
  vlistSelectCell(vliststrGetList(l), s, r, c)
#define vliststrUnselectCell(l, s, r, c) \
  vlistUnselectCell(vliststrGetList(l), s, r, c)
#define vliststrSelectRow(l, s, r)	\
  vlistSelectRow(vliststrGetList(l), s, r)
#define vliststrUnselectRow(l, s, r)	\
  vlistUnselectRow(vliststrGetList(l), s, r)
#define vliststrSelectColumn(l, s, c)	\
  vlistSelectColumn(vliststrGetList(l) , s, c)
#define vliststrUnselectColumn(l, s, c)	\
  vlistUnselectColumn(vliststrGetList(l) , s, c)
#define vliststrSelectAll(l, s)		\
  vlistSelectAll(vliststrGetList(l), s)
#define vliststrUnselectAll(l, s)	\
  vlistUnselectAll(vliststrGetList(l), s)
#define vliststrIsSelectionEmpty(l, s)	\
  (vlistIsSelectionEmpty(vliststrGetList(l), s))
#define vliststrGetSelectMethod(l, s)	\
  (vlistGetSelectMethod(vliststrGetList(l), s))
#define vliststrSetSelectMethod(l, s, m) \
  vlistSetSelectMethod(vliststrGetList(l), (s), (m))

#define vliststrHasAtLeastOneSelection(l, s) \
  (vlistHasAtLeastOneSelection(vliststrGetList(l), s))
#define vliststrIsSelectionImmutable(l, s) \
  (vlistIsSelectionImmutable(vliststrGetList(l), s))
#define vliststrHasExtendRowSelection(l, s) \
  (vlistHasExtendRowSelection(vliststrGetList(l), s))
#define vliststrHasExtendColumnSelection(l, s) \
  (vlistHasExtendColumnSelection(vliststrGetList(l), s))
#define vliststrGetOrientation(l) \
  (vlistGetOrientation(vliststrGetList(l)))
#define vliststrSetOrientation(l,d) \
  vlistSetOrientation(vliststrGetList(l), (d))

#define vliststrInitSelectionIterator(i, s) \
  vlistInitSelectionIterator(i, s)
#define vliststrInitIterator(i, l)	vlistInitIterator(i, \
							  vliststrGetList(l))
#define vliststrNextIterator(i)		vlistNextIterator(i)
#define vliststrGetIteratorRow(i)	(vlistGetIteratorRow(i))
#define vliststrGetIteratorColumn(i)	(vlistGetIteratorColumn(i))
#define vliststrGetIteratorValue(i)	(vlistGetIteratorValue(i))
#define vliststrDestroyIterator(i)	vlistDestroyIterator(i)
#define vliststrInitSelectionRangeIterator(i,s) \
   vlistInitSelectionRangeIterator((i),(s))
#define vliststrGetIteratorRangeRowCount(i) \
  (vlistGetIteratorRangeRowCount((i)))
#define vliststrGetIteratorRangeColumnCount(i) \
  (vlistGetIteratorRangeColumnCount((i)))
#define vliststrGetIteratorRange(i,r) \
  (vlistGetIteratorRange((i),(r)))

#define vliststrDestroySelection(l,s) 	\
	vlistDestroySelection(vliststrGetList(l),(s))
#define vliststrSelectRange(l,s,r,c,a,b)\
	vlistSelectRange(vliststrGetList(l), (s), (r), (c), (a), (b))
#define vliststrSetSelectionImmutable(l,s,o)\
	vlistSetSelectionImmutable(vliststrGetList(l), (s), (o))
#define vliststrIsCellSelected(l,s,r,c)\
	vlistIsCellSelected(vliststrGetList(l), (s), (r), (c))
#define vliststrSetExtendRowSelection(l,s,o)\
	vlistSetExtendRowSelection(vliststrGetList(l), (s), (o))
#define vliststrCloneSelection(l,s)\
	vlistCloneSelection(vliststrGetList(l), (s))
#define vliststrDetermineCellName(l,r,c) 	\
	vlistDetermineCellName(vliststrGetList(l), (r), (c))
#define vliststrCountSelectedCells(l,s) 	\
	vlistCountSelectedCells(vliststrGetList(l), (s))
#define vliststrSetCellNamer(l,n) 		\
	vlistSetCellNamer(vliststrGetList(l), (n))
#define vliststrDetermineSelectionBounds(l,s,r,c,a,b)  \
	vlistDetermineSelectionBounds(vliststrGetList(l), (s), (r), \
				      (c), (a), (b))
#define vliststrUnselectRange(l,s,r,c,a,b) 		\
	vlistUnselectRange(vliststrGetList(l), (s), (r), (c), (a), (b))
#define vliststrCreateSelection(l) 	\
	vlistCreateSelection(vliststrGetList(l))
#define vliststrGetCellNamer(l) 		\
	vlistGetCellNamer(vliststrGetList(l))
#define vliststrSetAtLeastOneSelection(l,s,o) 	\
	vlistSetAtLeastOneSelection(vliststrGetList(l), (s), (o))
#define vliststrSetExtendColumnSelection(l,s,o) \
	vlistSetExtendColumnSelection(vliststrGetList(l), (s), (o))
#define vliststrCopySelection(l,s,t) 		\
	vlistCopySelection(vliststrGetList(l), (s), (t))



/*
 * * * * * * * * PRIVATE FUNCTION MESSAGE DEFINITIONS * * * * * * *
 */

#define vliststrCopy(l, t) \
  vclassSend(vliststrGetClass(l), vobjectCOPY, (l,t))
#define vliststrStore(l, r) \
  vclassSend(vliststrGetClass(l), vobjectSTORE, (l,r))

#define vliststrInsertRow(l, b) \
  vclassSend(vliststrGetClass(l), vlistINSERT_ROW_COLUMN, (l, b, vlistROW))
#define vliststrInsertColumn(l, b) \
  vclassSend(vliststrGetClass(l), vlistINSERT_ROW_COLUMN, (l, b, vlistCOLUMN))
#define vliststrRemoveRow(l, r) \
  vclassSend(vliststrGetClass(l), vlistREMOVE_ROW_COLUMN, (l, r, vlistROW))
#define vliststrRemoveColumn(l, c) \
  vclassSend(vliststrGetClass(l), vlistREMOVE_ROW_COLUMN, (l, c, vlistCOLUMN))
#define vliststrSwapRows(l, r1, r2) \
  vclassSend(vliststrGetClass(l), vlistSWAP_ROW_COLUMN, (l, r1, r2, vlistROW))
#define vliststrSwapColumns(l, c1, c2) \
  vclassSend(vliststrGetClass(l), vlistSWAP_ROW_COLUMN, \
	     (l, c1, c2, vlistCOLUMN))
#define vliststrMoveRow(l, f, t) \
  vclassSend(vliststrGetClass(l), vlistMOVE_ROW_COLUMN, (l, f, t, vlistROW))
#define vliststrMoveColumn(l, f, t) \
  vclassSend(vliststrGetClass(l), vlistMOVE_ROW_COLUMN, (l, f, t, vlistCOLUMN))
#define vliststrSetRowCount(l, rc) \
  vclassSend(vliststrGetClass(l), vlistSET_ROW_COLUMN_COUNT, (l, rc, vlistROW))
#define vliststrSetColumnCount(l, cc) \
  vclassSend(vliststrGetClass(l), vlistSET_ROW_COLUMN_COUNT, \
	     (l, cc, vlistCOLUMN))
#define vliststrSetCellValue(l, r, c, v) \
  vclassSend(vliststrGetClass(l), vlistSET_CELL_VALUE, (l, r, c, v))
#define vliststrSetCellValueScribed(l, r, c, s) \
  vclassSend(vliststrGetClass(l), vliststrSET_CELL_VALUE_SCRIBED, (l, r, c, s))
#define vliststrGetCellValueScribed(l,r,c) \
  vclassSend(vliststrGetClass(l), vliststrGET_CELL_VALUE_SCRIBED, (l,r,c))
#define vliststrGetCellValue(l, r, c) \
  vclassSend(vliststrGetClass(l), vlistGET_CELL_VALUE, (l, r, c))
#define vliststrFindCell(l, s, r, c, sr, sc, dh) \
  vclassSend(vliststrGetClass(l), vlistFIND_CELL, (l, s, r, c, sr, sc, dh))
#define vliststrSort(l, a, k, c) \
  vclassSend(vliststrGetClass(l), vlistSORT, (l, a, k, c))
#define vliststrSortByName(l, a, k, c) \
  vclassSend(vliststrGetClass(l), vlistSORT_BY_NAME, (l, a, k, c))
#define vliststrInsertRange(l, b, c, t) \
  vclassSend(vliststrGetClass(l), vlistINSERT_RANGE, (l, b, c, t))
#define vliststrRemoveRange(l, v, c, t) \
  vclassSend(vliststrGetClass(l), vlistREMOVE_RANGE, (l, v, c, t))
#define vliststrSwapRange(l, s1, s2, c, t) \
  vclassSend(vliststrGetClass(l), vlistSWAP_RANGE, (l, s1, s2, c, t))
#define vliststrMoveRange(l, m1, m2, c, t) \
  vclassSend(vliststrGetClass(l), vlistMOVE_RANGE, (l, m1, m2, c, t))
#define vliststrMakeMajorResource(l, r) \
  vclassSend(vliststrGetClass(l), vlistMAKE_MAJOR_RESOURCE, (l,r))
#define vliststrMakeMinorResource(l,r,i) \
  vclassSend(vliststrGetClass(l), vlistMAKE_MINOR_RESOURCE, (l,r,i))
#define vliststrFindMinorResource(l,r,i) \
  vclassSend(vliststrGetClass(l), vlistFIND_MINOR_RESOURCE, (l,r,i))
#define vliststrStoreCell(l,r,c,s) \
  vclassSend(vliststrGetClass(l), vlistSTORE_CELL, (l,r,c,s))
#define vliststrLoadCell(l,r,c,s) \
  vclassSend(vliststrGetClass(l), vlistLOAD_CELL, (l,r,c,s))



vportEND_CPLUSPLUS_EXTERN_C

#endif

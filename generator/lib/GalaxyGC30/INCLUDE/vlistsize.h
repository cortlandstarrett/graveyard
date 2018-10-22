/* $Id: vlistsize.h,v 1.15 1997/09/19 22:38:17 robert Exp $ */

/************************************************************

    vlistsize.h
    C Interface to the List Manager, listsize objects

    (c) Copyright Visix Software  1992
    All rights reserved

************************************************************/

#ifndef vlistsizeINCLUDED
#define vlistsizeINCLUDED 1

#ifndef  vportINCLUDED
#include <vport.h>
#endif

#ifndef  vclassINCLUDED
#include vclassHEADER
#endif

#ifndef  vloadableINCLUDED
#include vloadableHEADER
#endif

#ifndef  vrectINCLUDED
#include vrectHEADER
#endif

#ifndef  vresourceINCLUDED
#include vresourceHEADER
#endif

#ifndef  vlistINCLUDED
#include vlistHEADER
#endif


vportBEGIN_CPLUSPLUS_EXTERN_C




/*
 * * * * * * * * * * PUBLIC CONSTANT DEFINITIONS * * * * * * * * * *
 */

enum {
    vlistsizeALL_ROWS	 	= -1,
    vlistsizeALL_COLUMNS 	= -2
};



/*
 * * * * * * * * * * PUBLIC TYPE DEFINITIONS * * * * * * * * * *
 */

typedef struct vlistsizeClass vlistsizeClass;
typedef struct vlistsize vlistsize;



/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */


void vlistsizeStartup(
    void
    );

vlistsizeClass *vlistsizeGetDefaultClass(
    void
    );

vlistsizeClass *vlistsizeGetClass(
    vlistsize 	*size
    );

vlistsize *vlistsizeCreateOfClass(
    vlistsizeClass *clas
    );

vlistsize *vlistsizeCreate(
    void
    );

vlistsize *vlistsizeClone(
    vlistsize 	*size
    );

void vlistsizeInit(
    vlistsize 	*size
    );

void vlistsizeDestroy(
    vlistsize 	*size
    );

void vlistsizeCopy(
    vlistsize 	*size, 
    vlistsize 	*target
    );

void vlistsizeCopyInit(
    vlistsize 	*size, 
    vlistsize 	*target
    );

void vlistsizeLoadInit(
    vlistsize 	*size, 
    vresource 	 resource
    );

void vlistsizeStore(
    vlistsize 	*size, 
    vresource 	 resource
    );

vlistsize *vlistsizeLoad(
    vresource    resource
    );

void vlistsizeSetRowHeight(
    vlistsize 	*size, 
    int		 row, 
    int		 height
    );

void vlistsizeSetColumnWidth(
    vlistsize 	*size, 
    int		 column, 
    int		 width
    );

void vlistsizeSetDefaultHeight(
    vlistsize 	*size, 
    int		 height
    );

void vlistsizeSetDefaultWidth(
    vlistsize 	*size, 
    int	 width
    );

int vlistsizeGetDefaultHeight(
    vlistsize 	*size
    );

int vlistsizeGetDefaultWidth(
    vlistsize 	*size
    );

int vlistsizeGetRowHeight(
    vlistsize 	*size, 
    int		 row
    );

int vlistsizeGetColumnWidth(
    vlistsize 	*size, 
    int		 column
    );

void vlistsizeGetCellRect(
    vlistsize 	*size, 
    int		 row, 
    int		 column, 
    vrectLong 	*rect
    );

int vlistsizeGetRowCount(
    vlistsize 	*size
    );

int vlistsizeGetColumnCount(
    vlistsize 	*size
    );

void vlistsizeInsertRow(
    vlistsize 	*size, 
    int		 beforeRow
    );

void vlistsizeInsertColumn(
    vlistsize 	*size, 
    int		 beforeColumn
    );

void vlistsizeInsertRange(
    vlistsize   *size,
    int		 before,
    int	         count,
    int          type
    );

void vlistsizeRemoveRow(
    vlistsize 	*size, 
    int		 victim
    );

void vlistsizeRemoveColumn(
    vlistsize 	*size, 
    int		 victim
    );

void vlistsizeRemoveRange(
    vlistsize   *size,
    int		 victim,
    int	         count,
    int          type
    );

void vlistsizeMoveRow(
    vlistsize 	*size, 
    int		 from, 
    int		 to
    );

void vlistsizeMoveColumn(
    vlistsize 	*size, 
    int		 from, 
    int		 to
    );

void vlistsizeMoveRange(
    vlistsize   *size,
    int		 from,
    int		 to,
    int	         count,
    int          type
    );

void vlistsizeSwapRows(
    vlistsize 	*size, 
    int		 from, 
    int		 to
    );
    
void vlistsizeSwapColumns(
    vlistsize *size, 
    int		 from,
    int		 to
    );

void vlistsizeSwapRange(
    vlistsize   *size,
    int		 swap1,
    int		 swap2,
    int	         count,
    int          type
    );

void vlistsizeCalcCellRange(
    vlistsize 	*size, 
    int		 startRow, 
    int		 startColumn,
    int		 width, 
    int		 height, 
    int	 	*endRow, 
    int 	*endColumn
    );

void vlistsizeGetMaxArea(
    vlistsize 	*size, 
    vrectLong 	*rect
    );

void vlistsizeSetData(
    vlistsize 	*size, 
    void 	*data
    );

const void *vlistsizeGetData(
    vlistsize 	*size
    );

void vlistsizeDump (
    vlistsize 	*size,
    FILE     	*stream
    );


/*
 * * * * * * * * * * PRIVATE CONSTANT DEFINITIONS * * * * * * * * * *
 */

enum {
    vlistsizeUNDEFINED = -1
};


/*
 * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * *
 */

#define vlistsizeCLASS(SUPER, SIZE) \
    vloadableCLASS(SUPER, SIZE); \
    vclassMETHOD(vlistsizeSET_ROW_HEIGHT, \
                 (SIZE *size, int row, int height)); \
    vclassMETHOD(vlistsizeSET_COLUMN_WIDTH, \
                 (SIZE *size, int column, int width)); \
    vclassMETHOD_RET(vlistsizeGET_ROW_HEIGHT, \
                     int, (SIZE *size, int row)); \
    vclassMETHOD_RET(vlistsizeGET_COLUMN_WIDTH, \
                     int, (SIZE *size, int column)); \
    vclassMETHOD(vlistsizeSET_DEFAULT_HEIGHT, \
                 (SIZE *size, int height)); \
    vclassMETHOD(vlistsizeSET_DEFAULT_WIDTH, \
                 (SIZE *size, int width)); \
    vclassMETHOD(vlistsizeGET_CELL_RECT, \
                 (SIZE *size, int row, int column, vrectLong *rect)); \
    vclassMETHOD(vlistsizeINSERT_ROW_COLUMN, \
                 (SIZE *size, int beforeRowCol, int type)); \
    vclassMETHOD(vlistsizeREMOVE_ROW_COLUMN, \
                 (SIZE *size, int victim, int type));\
    vclassMETHOD(vlistsizeMOVE_ROW_COLUMN, \
                 (SIZE *size, int from, int to, int type)); \
    vclassMETHOD(vlistsizeSWAP_ROW_COLUMN, \
                 (SIZE *size, int from, int to, int type)); \
    vclassMETHOD(vlistsizeINSERT_RANGE, \
                 (SIZE *size, int before, int count, int type)); \
    vclassMETHOD(vlistsizeREMOVE_RANGE, \
                 (SIZE *size, int victim, int count, int type)); \
    vclassMETHOD(vlistsizeMOVE_RANGE, \
                 (SIZE *size, int from, int to, int count, int type)); \
    vclassMETHOD(vlistsizeSWAP_RANGE, \
                 (SIZE *size, int swap1, int swap2, int count, int type)); \
    vclassMETHOD(vlistsizeCALC_CELL_RANGE, \
                 (SIZE *size, int startRow, int startColumn, \
                  int width, int height, int *endRow, int *endColumn)); \
    vclassMETHOD(vlistsizeGET_MAX_AREA, \
                 (SIZE *size, vrectLong *rect))

struct vlistsize {
    vloadable  object;
    int      rowCount, columnCount;
    int     *widthTable, *heightTable;
    int	     widthTableSize, heightTableSize;
    int	     defaultWidth, defaultHeight;
    void    *data;
    short    flags;
};

struct vlistsizeClass {
    vlistsizeCLASS (vlistsizeClass, vlistsize);
};
	      


/*
 * * * * * * * * * * PRIVATE FUNCTION PROTOTYPES * * * * * * * * * *
 */

/*
 * * * * * * * PRIVATE BACKWARD COMPATIBILITY MACRO DEFINITIONS * * * * * *
 */
#define vlistSize vlistsize
#define vlistSizeUNDEFINED vlistsizeUNDEFINED
#define vlistSizeClass vlistsizeClass
#define vlistSizeSET_ROW_HEIGHT		vlistsizeSET_ROW_HEIGHT
#define vlistSizeSET_COLUMN_WIDTH	vlistsizeSET_COLUMN_WIDTH
#define vlistSizeGET_ROW_HEIGHT		vlistsizeGET_ROW_HEIGHT
#define vlistSizeGET_COLUMN_WIDTH	vlistsizeGET_COLUMN_WIDTH
#define vlistSizeGET_CELL_RECT		vlistsizeGET_CELL_RECT
#define vlistSizeSET_DEFAULT_HEIGHT	vlistsizeSET_DEFAULT_HEIGHT
#define vlistSizeSET_DEFAULT_WIDTH	vlistsizeSET_DEFAULT_WIDTH
#define vlistSizeINSERT_ROW_COLUMN	vlistsizeINSERT_ROW_COLUMN
#define vlistSizeREMOVE_ROW_COLUMN	vlistsizeREMOVE_ROW_COLUMN
#define vlistSizeMOVE_ROW_COLUMN	vlistsizeMOVE_ROW_COLUMN
#define vlistSizeSWAP_ROW_COLUMN	vlistsizeSWAP_ROW_COLUMN
#define vlistSizeCALC_CELL_RANGE	vlistsizeCALC_CELL_RANGE
#define vlistSizeGET_MAX_AREA		vlistsizeGET_MAX_AREA

#define vlistSizeDump			vlistsizeDump
#define vlistSizeGetDefaultClass	vlistsizeGetDefaultClass
#define vlistSizeGetClass		vlistsizeGetClass
#define vlistSizeCreateOfClass		vlistsizeCreateOfClass
#define vlistSizeCreate			vlistsizeCreate
#define vlistSizeClone			vlistsizeClone
#define vlistSizeInit			vlistsizeInit
#define vlistSizeDestroy		vlistsizeDestroy
#define vlistSizeCopy			vlistsizeCopy
#define vlistSizeCopyInit		vlistsizeCopyInit
#define vlistSizeLoadInit		vlistsizeLoadInit
#define vlistSizeStore			vlistsizeStore
#define vlistSizeSetRowHeight		vlistsizeSetRowHeight
#define vlistSizeSetColumnWidth		vlistsizeSetColumnWidth
#define vlistSizeSetDefaultHeight	vlistsizeSetDefaultHeight
#define vlistSizeSetDefaultWidth	vlistsizeSetDefaultWidth
#define vlistSizeGetDefaultHeight	vlistsizeGetDefaultHeight
#define vlistSizeGetDefaultWidth	vlistsizeGetDefaultWidth
#define vlistSizeGetRowHeight		vlistsizeGetRowHeight
#define vlistSizeGetColumnWidth		vlistsizeGetColumnWidth
#define vlistSizeGetCellRect		vlistsizeGetCellRect
#define vlistSizeGetRowCount		vlistsizeGetRowCount
#define vlistSizeGetColumnCount		vlistsizeGetColumnCount
#define vlistSizeInsertRow		vlistsizeInsertRow
#define vlistSizeInsertColumn		vlistsizeInsertColumn
#define vlistSizeRemoveRow		vlistsizeRemoveRow
#define vlistSizeRemoveColumn		vlistsizeRemoveColumn
#define vlistSizeMoveRow		vlistsizeMoveRow
#define vlistSizeMoveColumn		vlistsizeMoveColumn
#define vlistSizeSwapRows		vlistsizeSwapRows
#define vlistSizeSwapColumns		vlistsizeSwapColumns
#define vlistSizeCalcCellRange		vlistsizeCalcCellRange
#define vlistSizeGetMaxArea		vlistsizeGetMaxArea
#define vlistSizeSetData		vlistsizeSetData
#define vlistSizeGetData		vlistsizeGetData


/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * *
 */

#define _vlistsizeGetLoadable(s)	(vportBASE_OBJECT((s), object))
#define vlistsizeSetData(s,d)	(s)->data = (d)
#define vlistsizeGetData(s)	(s)->data
#define vlistsizeGetRowCount(s)	(s)->rowCount
#define vlistsizeGetColumnCount(s) (s)->columnCount
#define vlistsizeGetClass(s)	((vlistsizeClass*)vloadableGetClass(_vlistsizeGetLoadable(s)))
#define vlistsizeCreateOfClass(c) (vlistsize*)vloadableCreateOfClass((vloadableClass*)(c))
#define vlistsizeCreate()	vlistsizeCreateOfClass(vlistsizeGetDefaultClass())
#define vlistsizeClone(s)	((vlistsize*)vloadableClone(_vlistsizeGetLoadable(s)))

#define vlistsizeInit(s)	vloadableInitOfClass(&((s)->loadable), \
						   vlistsizeGetDefaultClass())
#define vlistsizeDestroy(s)	vloadableDestroy(_vlistsizeGetLoadable(s))
#define vlistsizeCopyInit(s,t)	vloadableCopyInit(_vlistsizeGetLoadable(s), \
						_vlistsizeGetLoadable(t))
#define vlistsizeCopy(s,t)	vloadableCopy(_vlistsizeGetLoadable(s), \
					      _vlistsizeGetLoadable(t))
#define vlistsizeStore(s,r)	vloadableStore(_vlistsizeGetLoadable(s), r)

#define vlistsizeLoadInit(s,r)	vloadableLoadInit(_vlistsizeGetLoadable(s), r)
#define vlistsizeLoad(r)	((vlistsize*)vloadableLoad(r))


#define vlistsizeInsertRow(s,b) \
    vclassSend(vlistsizeGetClass(s), \
               vlistsizeINSERT_ROW_COLUMN, (s, b, vlistROW))
#define vlistsizeInsertColumn(s,b) \
    vclassSend(vlistsizeGetClass(s), \
               vlistsizeINSERT_ROW_COLUMN, (s, b, vlistCOLUMN))

#define vlistsizeRemoveRow(s,b) \
    vclassSend(vlistsizeGetClass(s), \
               vlistsizeREMOVE_ROW_COLUMN, (s, b, vlistROW))
#define vlistsizeRemoveColumn(s,b) \
    vclassSend(vlistsizeGetClass(s), \
               vlistsizeREMOVE_ROW_COLUMN, (s, b, vlistCOLUMN))

#define vlistsizeSwapRows(s,s1,s2) \
    vclassSend(vlistsizeGetClass(s), \
               vlistsizeSWAP_ROW_COLUMN, (s, s1, s2, vlistROW))
#define vlistsizeSwapColumns(s,s1,s2) \
    vclassSend(vlistsizeGetClass(s), \
               vlistsizeSWAP_ROW_COLUMN, (s, s1, s2, vlistCOLUMN))

#define vlistsizeMoveRow(s,f,t) \
    vclassSend(vlistsizeGetClass(s), \
               vlistsizeMOVE_ROW_COLUMN, (s, f, t, vlistROW))
#define vlistsizeMoveColumn(s,f,t) \
    vclassSend(vlistsizeGetClass(s), \
               vlistsizeMOVE_ROW_COLUMN, (s, f, t, vlistCOLUMN))


/*
 * * * * * * * * * * PRIVATE FUNCTION MESSAGE DEFINITIONS * * * * * * * * * *
 */

#define vlistsizeSetRowHeight(s,r,h) \
				vclassSend(vlistsizeGetClass(s), \
					   vlistsizeSET_ROW_HEIGHT, (s,r,h))
#define vlistsizeSetColumnWidth(s,c,w)	vclassSend(vlistsizeGetClass(s), \
					           vlistsizeSET_COLUMN_WIDTH, \
					           (s,c,w))
#define vlistsizeSetDefaultHeight(s,h) vclassSend(vlistsizeGetClass(s), \
					         vlistsizeSET_DEFAULT_HEIGHT, \
						  (s,h))
#define vlistsizeSetDefaultWidth(s,h) vclassSend(vlistsizeGetClass(s), \
					         vlistsizeSET_DEFAULT_WIDTH, \
						 (s,h))
#define vlistsizeGetDefaultWidth(s) (s)->defaultWidth
#define vlistsizeGetDefaultHeight(s) (s)->defaultHeight

#define vlistsizeGetRowHeight(s,r)	vclassSend(vlistsizeGetClass(s), \
						   vlistsizeGET_ROW_HEIGHT, \
						   (s,r))
#define vlistsizeGetColumnWidth(s,c)	vclassSend(vlistsizeGetClass(s), \
						   vlistsizeGET_COLUMN_WIDTH,\
						   (s,c))
#define vlistsizeGetCellRect(s,r,c,t)	vclassSend(vlistsizeGetClass(s), \
						   vlistsizeGET_CELL_RECT, \
						   (s,r,c,t))

#define vlistsizeCalcCellRange(s,sr,sc,w,h,er,ec) \
	vclassSend(vlistsizeGetClass(s), vlistsizeCALC_CELL_RANGE, \
		   (s,sr,sc,w,h,er,ec))
#define vlistsizeGetMaxArea(s,r)	\
	vclassSend(vlistsizeGetClass(s), vlistsizeGET_MAX_AREA, (s,r))

#define vlistsizeInsertRange(s,b,c,t) \
	vclassSend(vlistsizeGetClass(s), vlistsizeINSERT_RANGE, (s,b,c,t))

#define vlistsizeRemoveRange(s,b,c,t) \
	vclassSend(vlistsizeGetClass(s), vlistsizeREMOVE_RANGE, (s,b,c,t))

#define vlistsizeMoveRange(s,f,tw,c,t) \
	vclassSend(vlistsizeGetClass(s), vlistsizeMOVE_RANGE, (s,f,tw,c,t))

#define vlistsizeSwapRange(s,s1,s2,c,t) \
	vclassSend(vlistsizeGetClass(s), vlistsizeSWAP_RANGE, (s,s1,s2,c,t))



vportEND_CPLUSPLUS_EXTERN_C


#endif /* #ifndef vlistsizeINCLUDED */


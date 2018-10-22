/* $Id: vlistitem.h,v 1.52 1996/10/03 01:36:18 robert Exp $ */

/************************************************************

    vlistitem.h
    C Interface to the List Manager, listitem objects

    (c) Copyright Visix Software
    All rights reserved

************************************************************/

#ifndef vlistitemINCLUDED
#define vlistitemINCLUDED 1

#ifndef  vportINCLUDED
#include <vport.h>
#endif

#ifndef  vlistviewINCLUDED
#include vlistviewHEADER
#endif

#ifndef  vlistINCLUDED
#include vlistHEADER
#endif

#ifndef  vliststrINCLUDED
#include vliststrHEADER
#endif

#ifndef  vobjectINCLUDED
#include vobjectHEADER
#endif

#ifndef  vresourceINCLUDED
#include vresourceHEADER
#endif


vportBEGIN_CPLUSPLUS_EXTERN_C



/*
 * * * * * * * * * * PUBLIC CONSTANT DEFINITIONS * * * * * * * * * *
 */

#define vlistitemSELECTION_WILL_CHANGE vlistviewSELECTION_WILL_CHANGE
#define vlistitemSELECTION_IS_CHANGING vlistviewSELECTION_IS_CHANGING
#define vlistitemSELECTION_HAS_CHANGED vlistviewSELECTION_HAS_CHANGED

#define vlistitemNO_CELLS_SELECTED vlistNO_CELLS_SELECTED



/*
 * * * * * * * * * * PUBLIC TYPE DEFINITIONS * * * * * * * * * *
 */

typedef struct vlistitem		vlistitem;
typedef struct vlistitemClass		vlistitemClass;
typedef struct vlistitemList		vlistitemList;
typedef struct vlistitemListClass	vlistitemListClass;

typedef void (*vlistitemSelectNoteProc) (
    vlistitem *listitem,
    int state
    );

typedef void (*vlistitemDrawCellProc) (
    vlistitem *listitem,
    int row,
    int column,
    int selected,
    vrect *rect
    );

typedef void (*vlistitemNoteProc) (
    vlistitem *listitem,
    vevent *event
    );



/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */


void vlistitemStartup (
    void
    );

vlistitemClass	*vlistitemGetDefaultClass (
    void
    );

vlistitemListClass *vlistitemGetDefaultListDataClass (
    void
    );

vlistitem *vlistitemCreateOfClass (
    vlistitemClass	*clas
    );

vlistitem *vlistitemCreate (
    void
    );

vlistitem *vlistitemClone (
    vlistitem	*listitem
    );

void vlistitemInit (
    vlistitem	*listitem
    );

void vlistitemInitOfClass (
    vlistitem		*listitem,
    vlistitemClass	*clas
    );

void vlistitemDestroy (
    vlistitem	*listitem
    );

void vlistitemCopy (
    vlistitem	*listitem,
    vlistitem	*target
    );

void vlistitemCopyInit (
    vlistitem	*listitem,
    vlistitem	*target
    );

vlistitem *vlistitemLoad (
    vresource 	 resource
    );
    
void vlistitemLoadInit (
    vlistitem *listitem,
    vresource  resource
    );

void vlistitemStore (
    vlistitem *listitem,
    vresource  resource
    );

void vlistitemSetList (
    vlistitem	*listitem,
    vlist	*list
    );

void vlistitemSetNotify (
    vlistitem         *listitem,
    vlistitemNoteProc  noteProc
    );

vlistitemNoteProc vlistitemGetNotify (
    vlistitem	*listitem
    );

void vlistitemSetSelectNotify (
    vlistitem	*listitem,
    vlistitemSelectNoteProc proc
    );

void vlistitemAppend (
    vlistitem	*listitem,
    const vchar	*str
    );

void vlistitemAppendScribed (
    vlistitem	*listitem,
    vscribe	*scribe
    );

void vlistitemPrepend (
    vlistitem	*listitem,
    const vchar	*str
    );

void vlistitemPrependScribed (
    vlistitem	*listitem,
    vscribe	*scribe
    );

void vlistitemInsert (
    vlistitem   *listitem,
    int          row,
    const vchar *str
    );

void vlistitemInsertScribed (
    vlistitem   *listitem,
    int          row,
    vscribe     *scribe
    );

void vlistitemSetValueAt (
    vlistitem	*listitem,
    const vchar *str,
    int		 at
    );

void vlistitemSetValueAtScribed (
    vlistitem	*listitem,
    vscribe	*scribe,
    int		 at
    );

const vchar *vlistitemGetValueAt (
    vlistitem	*listitem,
    int		 row
    );

vscribe *vlistitemGetValueAtScribed (
    vlistitem	*listitem,
    int		 row
    );

vlistSelection *vlistitemGetSelection (
    vlistitem	*listitem
    );

vlistSelection *vlistitemGetVolatileSelection (
    vlistitem	*listitem
    );

int vlistitemGetSelectedRow (
    vlistitem	*listitem
    );

int vlistitemGetVolatileSelectedRow (
    vlistitem	*listitem
    );
    
void vlistitemSelectRow (
    vlistitem	*listitem,
    int		 row
    );

void vlistitemUnselectRow (
    vlistitem	*listitem,
    int		 row
    );

void vlistitemRemoveRow (
    vlistitem	*listitem,
    int		 row
    );

void vlistitemSortList (
    vlistitem	*listitem,
    vlistCellValueSorterFunc compar
    );

void vlistitemSetRowCount (
    vlistitem	*listitem,
    int		 count
    );

int vlistitemGetRowCount (
    vlistitem	*listitem
    );

void vlistitemSetRowHeight (
    vlistitem	*listitem,
    int		 height
    );

int vlistitemGetRowHeight (
    vlistitem	*listitem
    );

void vlistitemSetCellContentProc (
    vlistitem	*listitem,
    vlistitemDrawCellProc	proc
    );

vlistitemDrawCellProc vlistitemGetCellContentProc (
    vlistitem	*listitem
    );

vlist *vlistitemGetList (
    vlistitem	*listitem
    );

vliststr *vlistitemGetListstr (
    vlistitem	*listitem
    );

vlistview *vlistitemGetView (
    vlistitem	*listitem
    );

vdialogItem *vlistitemGetItem (
    vlistitem	*listitem
    );

vlistitemClass *vlistitemGetClass (
    vlistitem	*listitem
    );

void vlistitemSetData (
    vlistitem	*listitem,
    const void	*data
    );
    
const void *vlistitemGetData (
    vlistitem	*listitem
    );


void vlistitemSetSelectMethod (
    vlistitem	*listitem,
    int		 selectMethod
    );

int vlistitemGetSelectMethod (
    vlistitem	*listitem
    );

void vlistitemSetAtLeastOneSelection (
    vlistitem	*listitem,
    int		 onOff
    );
    
int vlistitemHasAtLeastOneSelection (
    vlistitem	*listitem
    );

void vlistitemSetVisibleRows ( /* only used in natural size calculation */
    vlistitem	*listitem,
    int		 rows
    );

int vlistitemGetVisibleRows ( /* value used for natural size calculation */
    vlistitem	*listitem
    );

void vlistitemSetAutowidth (
    vlistitem	*listitem, 
    int 	 onOff
    );

int vlistitemGetAutowidth (
    vlistitem	*listitem
    );




/*
 * * * * * * * * * * PRIVATE CONSTANT DEFINITIONS * * * * * * * * * *
 */


enum {
    _vlistitemAUTOWIDTH    = 0x0001,
    _vlistitemSETTING_DATA = 0x0002,
    _vlistitemSETTING_LIST = 0x0004
};


/*
 * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * *
 */


struct vlistitem {
    vlistview		 view;
    int			 maxWidth;
    int			 visibleRows;
    short		 flags;
};

#define vlistitemCLASS(SUPER,ITEM,NOTIFY)				\
vlistviewCLASS(SUPER,ITEM,NOTIFY);					\
vclassMETHOD_RET (vlistitemCREATE_LIST_DATA, vlistitemList *, 		\
		  (ITEM *listitem));					\
vclassMETHOD	 (vlistitemSET_AUTOWIDTH, (ITEM *listitem, int onOff));\
vclassMETHOD	 (vlistitemSET_VISIBLE_ROWS, (ITEM *listitem, int rows))

struct vlistitemClass {
    vlistitemCLASS (vlistitemClass, vlistitem, vlistitemNoteProc);
};



struct vlistitemList {
    vliststr     list;
    vlistitem	*owner;
};

#define vlistitemListCLASS(SUPER,LIST,SELECTION)			\
vliststrCLASS(SUPER,LIST,SELECTION)

struct vlistitemListClass {
    vlistitemListCLASS (vlistitemListClass, vlistitemList, vlistSelection);
};


/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * *
 */

#define vlistitemGetView(i)	(vportBASE_OBJECT((i), view))

#define vlistitemGetItem(i)	(vlistviewGetItem(vlistitemGetView((i))))

#define vlistitemGetClass(l)	((vlistitemClass*)vdialogGetItemClass \
				 ((vdialogItem *)(l)))

#define vlistitemCreateOfClass(c) \
	((vlistitem*)vdialogCreateItemOfClass((vdialogItemClass*)(c)))

#define vlistitemCreate()  (vlistitemCreateOfClass(vlistitemGetDefaultClass()))
#define vlistitemClone(i)  ((vlistitem*)vdialogCloneItem((vdialogItem*)(i)))
#define vlistitemInitOfClass(i,c) \
	vdialogInitItemOfClass((vdialogItem*)(i), (vdialogItemClass*)(c))
#define vlistitemInit(i) \
	vlistitemInitOfClass(i,vlistitemGetDefaultClass())
#define vlistitemDestroy(i)	vlistviewDestroy(vlistitemGetView(i))
#define vlistitemCopy(i,t)	vlistviewCopy(vlistitemGetView((i)),  \
					      (vlistview*)(t))
#define vlistitemCopyInit(i,t)	vlistviewCopyInit(vlistitemGetView((i)), \
						  (vlistview*)(t))
#define vlistitemLoad(r)	(((vlistitem*)vdialogLoadItem((r))))
#define vlistitemLoadInit(i,r)	vdialogLoadInitItem(vlistitemGetItem((i)),(r))
#define vlistitemStore(i,r)	vclassSend(vlistitemGetClass(i), vobjectSTORE, \
					   (i,r))

#define vlistitemSetSelectNotify(i,p) vlistviewSetSelectNotify \
			(vlistitemGetView((i)), \
			 (vlistviewSelectNoteProc)p)
#define vlistitemSetNotify(l,p)	vdialogSetItemNotify(vlistitemGetItem((l)),\
						     (vdialogItemNoteProc)(p))
#define vlistitemGetNotify(l) (vlistitemNoteProc)(vlistviewGetNotify \
						  (vlistitemGetView((l))))
#define vlistitemSetList(l,z) vlistviewSetListOwned(vlistitemGetView((l)),(z))

/* vlistitem data manipulations */

#define vlistitemGetList(i) 	(vlistviewGetList(vlistitemGetView((i))))
#define vlistitemGetListstr(i) 	\
			((vliststr*)vlistviewGetList(vlistitemGetView((i))))

#define vlistitemGetValueAt(i,r) \
	((const vchar*)vliststrGetCellValue(vlistitemGetListstr((i)), \
					   (r), 0))
#define vlistitemGetValueAtScribed(i,r) \
	(vliststrGetCellValueScribed(vlistitemGetListstr((i)), (r), 0))

#define vlistitemSelectRow(i,r) \
	vlistSelectRow(vlistviewGetList(vlistitemGetView((i))), \
		       vlistviewGetSelection(vlistitemGetView((i))), (r))
#define vlistitemUnselectRow(i,r) \
	vlistUnselectRow(vlistviewGetList(vlistitemGetView((i))), \
			 vlistviewGetSelection(vlistitemGetView((i))), (r))
#define vlistitemRemoveRow(i,r) \
	vlistRemoveRow(vlistviewGetList(vlistitemGetView((i))), (r))
#define vlistitemGetRowCount(i) \
	(vlistGetRowCount(vlistviewGetList(vlistitemGetView((i)))))
#define vlistitemAppend(i,s) \
	vliststrSetCellValue (vlistitemGetListstr((i)), \
			      vlistGetRowCount(vlistitemGetList \
					       ((i))), 0, (s))
#define vlistitemAppendScribed(i,s) \
	vliststrSetCellValueScribed(vlistitemGetListstr((i)),		    \
				    vlistGetRowCount(vlistitemGetList((i))), \
				    0, (s))
#define vlistitemSetValueAt(i,s,a)					\
	vliststrSetCellValue (vlistitemGetListstr((i)), (a), 0, (s))
#define vlistitemSetValueAtScribed(i,s,a)				\
	vliststrSetCellValueScribed(vlistitemGetListstr((i)), (a), 0, (s))
#define vlistitemSortList(i,b)	vlistSort(vlistitemGetList(i),	\
					  vlistROW, 0, (b))

#define vlistitemSetRowHeight(i,h) \
	vlistviewSetRowHeight(vlistitemGetView((i)), vlistviewALL_ROWS, (h))
#define vlistitemGetRowHeight(i) \
	(vlistviewGetRowHeight(vlistitemGetView((i)), 0))


#define vlistitemSetCellContentProc(i,p) \
	vlistviewSetCellContentProc(vlistitemGetView((i)), \
				    (vlistviewDrawCellProc)(p))
#define vlistitemGetCellContentProc(i) \
	((vlistitemDrawCellProc)(vlistviewGetCellContentProc\
            (vlistitemGetView((i)))))

#define vlistitemSetSelectMethod(i,m) \
	vlistSetSelectMethod(vlistitemGetList((i)), \
			     vlistviewGetSelection(vlistitemGetView((i))),(m))
#define vlistitemGetSelectMethod(i) \
	(vlistGetSelectMethod(vlistitemGetList((i)), \
			     vlistviewGetSelection(vlistitemGetView((i)))))
#define vlistitemSetAtLeastOneSelection(l,o) \
	vlistSetAtLeastOneSelection(vlistitemGetList((l)), \
				vlistviewGetSelection(vlistitemGetView((l))), \
				    o)
#define vlistitemHasAtLeastOneSelection(l) \
	(vlistHasAtLeastOneSelection(vlistitemGetList((l)), \
			     vlistviewGetSelection(vlistitemGetView((l)))))
#define vlistitemGetSelection(l) vlistviewGetSelection(vlistitemGetView((l)))
#define vlistitemGetVolatileSelection(l) \
        (vlistviewGetVolatileSelection(vlistitemGetView((l))))
#define vlistitemSetData(l,d)	vdialogSetItemData(vlistitemGetItem(l),d)
#define vlistitemGetData(l)	((void*)vdialogGetItemData \
				 (vlistitemGetItem(l)))

#define vlistitemGetAutowidth(l)	((l)->flags & _vlistitemAUTOWIDTH)
#define vlistitemGetVisibleRows(l)	((l)->visibleRows)

/* private vlistitemList macros and such */

#define vlistitemListCreateOfClass(c)	\
	((vlistitemList*)vliststrCreateOfClass((vliststrClass*)(c)))
#define vlistitemListCreate()		\
	(vlistitemListCreateOfClass(vlistitemGetDefaultListDataClass()))
#define vlistitemListGetListstr(l)	(vportBASE_OBJECT((l), list))
#define vlistitemListGetList(l)		\
	(vliststrGetList(vlistitemListGetListstr(l)))
#define vlistitemListLoad(r)		((vlistitemList*)vliststrLoad((r)))


/*
 * * * * * * * * * * PRIVATE FUNCTION MESSAGE DEFINITIONS * * * * * * * * * *
 */

#define vlistitemSetAutowidth(l,o) \
	vclassSend (vlistitemGetClass(l), vlistitemSET_AUTOWIDTH, (l,o))

#define vlistitemSetVisibleRows(l,r) \
	vclassSend (vlistitemGetClass(l), vlistitemSET_VISIBLE_ROWS, (l,r))

vportEND_CPLUSPLUS_EXTERN_C


#endif /* #ifndef vlistitemINCLDUED */


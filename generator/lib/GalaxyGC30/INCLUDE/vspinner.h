/* $Id: vspinner.h,v 1.34 1996/04/25 13:51:25 ian Exp $ */

/************************************************************

    vspinner.h
    C Interface to static and editable spinner box

    (c) Copyright Visix Software  1992
    All rights reserved

************************************************************/

#ifndef vspinnerINCLUDED
#define vspinnerINCLUDED 1

#ifndef  vportINCLUDED
#include <vport.h>		/* for v*HEADER */
#endif

#ifndef  vcharINCLUDED
#include vcharHEADER
#endif

#ifndef  vclassINCLUDED
#include vclassHEADER
#endif

#ifndef  vdialogINCLUDED
#include vdialogHEADER
#endif

#ifndef  vcontrolINCLUDED
#include vcontrolHEADER
#endif

#ifndef  vtextitemINCLUDED
#include vtextitemHEADER
#endif

#ifndef  vliststrINCLUDED
#include vliststrHEADER
#endif


vportBEGIN_CPLUSPLUS_EXTERN_C


/*
 * * * * * * * * * CONSTANTS AND MACRO DEFINITIONS * * * * * * * * * *
 */

#define _vspinnerTEXT_MODIFYABLE      0x0001
#define _vspinnerWRAP                 0x0002
#define _vspinnerDIRTY_CONTENT        0x0004
#define _vspinnerDIRTY_LIST           0x0008
#define _vspinnerAUTO_SORT            0x0010
 
/*
#define vspinnerNO_ARROWS            0x0000
#define vspinnerLEFT_ARROWS          0x0100
#define vspinnerSPLIT_ARROWS         0x0200
#define vspinnerRIGHT_ARROWS         0x0300
#define vspinnerLEFT_STACKED_ARROWS  0x0400
#define vspinnerRIGHT_STACKED_ARROWS 0x0500
*/

/*
 * * * * * * * * * TYPE AND STRUCTURE DEFINITIONS * * * * * * * * * *
 */

typedef struct vspinner          vspinner;

typedef void (*vspinnerNoteProc)(vspinner *spinner, vevent *event);

typedef int  (*vspinnerCompareProc)(const vchar *text1, const vchar *text2);

struct vspinner {
    vcontrol             control;

    int                  flags;

    vliststr            *liststr;     /* used if spinner is text */

    vtextitem	        *textitem;
};

/*
 * For C -> C++ merge
 */

typedef vspinner        vspinnerText;

/*
 * Spinner class Definition
 */
#define vspinnerCLASS(SUPER, SPINNER, NOTIFY) \
    vcontrolCLASS(SUPER, SPINNER, NOTIFY); \
    vclassMETHOD(vspinnerAPPEND_TEXT_SCRIBED, \
		 (SPINNER *spinner, vscribe *scribe)); \
    vclassVARIABLE(vspinnerCOMPARE, vspinnerCompareProc); \
    vclassMETHOD_RET(vspinnerCREATE_TEXTITEM, \
		     vtextitem *, (SPINNER *spinner)); \
    vclassMETHOD(vspinnerDELETE_TEXT_SCRIBED, \
		 (SPINNER *spinner, vscribe *scribe)); \
    vclassMETHOD(vspinnerDELETE_TEXT_AT, \
		 (SPINNER *spinner, int index)); \
    vclassMETHOD_RET(vspinnerFIND_TEXT_SCRIBED_INDEX, int, \
		     (SPINNER *spinner, vscribe *scribe)); \
    vclassMETHOD(vspinnerMARK_CONTENT_DIRTY, (SPINNER *spinner)); \
    vclassMETHOD(vspinnerMARK_LIST_DIRTY, (SPINNER *spinner)); \
    vclassMETHOD(vspinnerRECALC_CONTENT, (SPINNER *spinner)); \
    vclassMETHOD(vspinnerSELECT_TEXT_SCRIBED, \
		 (SPINNER *spinner, vscribe *scribe)); \
    vclassMETHOD(vspinnerSET_AUTO_SORT, (SPINNER *spinner, int onOff)); \
    vclassMETHOD(vspinnerSET_LIST, \
		 (SPINNER *spinner, vlist *list)); \
    vclassMETHOD(vspinnerSET_MODIFYABLE, (SPINNER *spinner, int onOff)); \
    vclassMETHOD(vspinnerSET_TEXT_SCRIBED_AT, \
		 (SPINNER *spinner, vscribe *scribe, int index)); \
    vclassMETHOD(vspinnerSET_WRAP, (SPINNER *spinner, int onOff)); \
    vclassMETHOD(vspinnerSORT_LIST, (SPINNER *spinner))

typedef struct vspinnerClass     vspinnerClass;

struct vspinnerClass {
    vspinnerCLASS(vspinnerClass, vspinner, vspinnerNoteProc);
};

/*
 * * * * * * * * * SPINNER FUNCTION PROTOTYPES * * * * * * * * * *
 */

void vspinnerStartup(void);


/* Spinner Class Functions */

vspinnerClass *vspinnerGetDefaultClass(void);

vspinnerClass *vspinnerGetTextClass(void);

vliststrClass *vspinnerGetDefaultListClass(void);

/* Initialization and allocation */

vspinner *vspinnerCreateOfClass(
    vspinnerClass *clas
    );

vspinner *vspinnerCreate(void);

vspinner *vspinnerCreateText(void);

vspinner *vspinnerClone(
    vspinner	*spinner
    );

void vspinnerInitOfClass(
    vspinner	  *spinner,
    vspinnerClass *clas
    );

void vspinnerInit(
    vspinner	*spinner
    );

void vspinnerInitText(
    vspinner	*spinner
    );

void vspinnerDestroy(
    vspinner	*spinner
    );

void vspinnerCopy(
    vspinner  	*spinner,
    vspinner	*target
    );

void vspinnerCopyInit(
    vspinner   	*spinner,
    vspinner	*target
    );

vspinner *vspinnerLoad(
    vresource	resource
    );

void vspinnerLoadInit(
    vspinner	*spinner,
    vresource	resource
    );

void vspinnerStore(
    vspinner	*spinner,
    vresource	resource
    );

/*
 * Attribute Modification Functions
 */
void vspinnerMarkContentDirty(
    vspinner            *spinner
    );
    
void vspinnerMarkListDirty(
    vspinner            *spinner
    );

void vspinnerRecalcContent(
    vspinner            *spinner
    );

void vspinnerSortList(
    vspinner            *spinner
    );		      
    
void vspinnerSetData(
    vspinner		*spinner,
    const void		*data
    );

void vspinnerSetTitle(
    vspinner           *spinner,
    vchar              *title
    );		    

void vspinnerSetTitleScribed(
    vspinner           *spinner,
    vscribe            *scribe
    );		    

void vspinnerSetNotify(
    vspinner		*spinner,
    vspinnerNoteProc	 noteProc
    );

void vspinnerSetValue(
    vspinner		*spinner,
    int                  value
    );

void vspinnerSetMin(
    vspinner		*spinner,
    int                  min
    );

void vspinnerSetMax(
    vspinner		*spinner,
    int                  max
    );

void vspinnerSetIncrement(
    vspinner		*spinner,
    int                  increment
    );

void vspinnerSetModifyable(
    vspinner    *spinner,
    int          onOff
    );

void vspinnerSetWrap(
    vspinner    *spinner,
    int          onOff
    );

void vspinnerSetAutoSort(
    vspinner    *spinner,
    int          onOff
    );

void vspinnerSetList(
    vspinner    *spinner,
    vlist       *list
    );
		   
void vspinnerSetTextAt(
    vspinner    *spinner,
    const vchar *text,
    int          index
    );
			      
void vspinnerSetTextScribedAt(
    vspinner    *spinner,
    vscribe     *scribe,
    int          index
    );
			      
void vspinnerAppendText(
    vspinner    *spinner,
    const vchar *text
    );			 

void vspinnerAppendTextScribed(
    vspinner    *spinner,
    vscribe     *scribe
    );			 

void vspinnerDeleteText(
    vspinner    *spinner,
    const vchar *text
    );			 

void vspinnerDeleteTextScribed(
    vspinner    *spinner,
    vscribe     *scribe
    );			 

void vspinnerDeleteTextAt(
    vspinner    *spinner,
    int          index
    );
			  
void vspinnerSelectText(
    vspinner    *spinner,
    const vchar *text
    );			 

void vspinnerSelectTextScribed(
    vspinner    *spinner,
    vscribe     *scribe
    );			 

void vspinnerSelectTextAt(
    vspinner    *spinner,
    int          index
    );			 

int vspinnerFindTextIndex(
    vspinner    *spinner,
    const vchar *text
    );			 

int vspinnerFindTextScribedIndex(
    vspinner    *spinner,
    vscribe     *scribe
    );			 

/*
 * Attribute Access Functions
 */

vcontrol    *vspinnerGetControl(
    vspinner    *spinner
    );

vdialogItem *vspinnerGetItem(
    vspinner	*spinner
    );

vtextitem *vspinnerGetTextitem(
    vspinner    *spinner
    );

vspinnerClass *vspinnerGetClass(
    vspinner	*spinner
    );

int vspinnerGetValue(
    vspinner    *spinner
    );

int vspinnerGetMin(
    vspinner    *spinner
    );

int vspinnerGetMax(
    vspinner    *spinner
    );

int vspinnerGetIncrement(
    vspinner    *spinner
    );

void vspinnerGetText(
    vspinner    *spinner,
    vchar       *text,
    long         length
    );

vscribe *vspinnerGetTextScribed(
    vspinner    *spinner
    );
	
vstr *vspinnerGetTextAsString(
    vspinner    *spinner
    );

const vchar *vspinnerGetTextAt(
    vspinner    *spinner,
    int          index
    );

vscribe *vspinnerGetTextScribedAt(
    vspinner    *spinner,
    int          index
    );

int vspinnerGetTextCount(
    vspinner    *spinner
    );

void *vspinnerGetData(
    vspinner    *spinner
    );

const vchar *vspinnerGetTitle(
    vspinner    *spinner
    );

vspinnerNoteProc vspinnerGetNotify(
    vspinner	*spinner
    );

vlist *vspinnerGetList(
    vspinner    *spinner
    );

vliststr *vspinnerGetListstr(
    vspinner    *spinner
    );

int vspinnerIsModifyable(
    vspinner    *spinner
    );

int vspinnerIsWrap(
    vspinner    *spinner
    );

int vspinnerIsAutoSort(
    vspinner    *spinner
    );

/*
 * * * * * * * * * P_R_I_V_A_T_E FUNCTION PROTOTYPES * * * * * * * * * *
 */

vspinnerCompareProc _vspinnerGetDefaultCompareFunc(vspinner *spinner);


#define _vspinnerSend(m, s, a) vclassSend(vspinnerGetClass(m), s, a)
#define _vspinnerGet(m, s) vclassGet(vspinnerGetClass(m), s)

/*
 * * * * * * * * * FUNCTIONS IMPLEMENTED AS MACROS * * * * * * * *
 */

#define vspinnerGetControl(s) \
    vportBASE_OBJECT((s), control)
#define vspinnerGetItem(s) \
    vcontrolGetItem(vspinnerGetControl(s))

#define vspinnerGetDefaultListClass() \
    vliststrGetDefaultClass()
#define vspinnerCreateOfClass(clas) \
    ((vspinner *)vdialogCreateItemOfClass((vdialogItemClass*)(clas)))
#define vspinnerCreate() \
    vspinnerCreateOfClass(vspinnerGetDefaultClass())
#define vspinnerCreateText() \
    vspinnerCreateOfClass(vspinnerGetTextClass())
#define vspinnerClone(s) \
    ((vspinner*)vdialogCloneItem((vdialogItem*)(s)))
#define vspinnerInitOfClass(s, clas) \
    vdialogInitItemOfClass((vdialogItem *)(s), (vdialogItemClass *)(clas))
#define vspinnerInit(s) \
    vspinnerInitOfClass((s), vspinnerGetDefaultClass())
#define vspinnerInitText(s) \
    vspinnerInitOfClass((s), vspinnerGetTextClass())
#define vspinnerDestroy(s) \
    vdialogDestroyItem((vdialogItem *)(s))
#define vspinnerCopy(s1, s2) \
    vclassSend(vspinnerGetClass(s1), vobjectCOPY, (s1, s2))
#define vspinnerCopyInit(s1, s2) \
    vdialogCopyInitItem((vdialogItem *)(s1), (vdialogItem *)(s2))
#define vspinnerLoad(s) \
    ((vspinner *)vdialogLoadItem(s))
#define vspinnerLoadInit(s, r) \
    vdialogLoadInitItem((vdialogItem *)(s), r)
#define vspinnerStore(s, r) \
    vclassSend(vspinnerGetClass(s), vobjectSTORE, (s, r))
#define vspinnerSetData(s, d) \
    vdialogSetItemData((vdialogItem *)(s), (d))
#define vspinnerSetTitleScribed(s, t) \
    vclassSend(vspinnerGetClass(s), vdialogSET_ITEM_TITLE_SCRIBED, (s, t))
#define vspinnerSetTitle(s, t) \
    vspinnerSetTitleScribed(s, vcharScribe(t))
#define vspinnerSetNotify(s, n) \
    vclassSend(vspinnerGetClass(s), vdialogSET_ITEM_NOTIFY, (s, n))
#define vspinnerSetValue(s, v) \
    vclassSend(vspinnerGetClass(s), vcontrolSET_VALUE, (s, v))
#define vspinnerSetMin(s, m) \
    vclassSend(vspinnerGetClass(s), vcontrolSET_MIN, (s, m))
#define vspinnerSetMax(s, m) \
    vclassSend(vspinnerGetClass(s), vcontrolSET_MAX, (s, m))
#define vspinnerSetIncrement(s, i) \
    vclassSend(vspinnerGetClass(s), vcontrolSET_INCREMENT, (s, i))
#define vspinnerSetModifyable(s, f) \
    vclassSend(vspinnerGetClass(s), vspinnerSET_MODIFYABLE, (s, f))
#define vspinnerSetWrap(s, f) \
    vclassSend(vspinnerGetClass(s), vspinnerSET_WRAP, (s, f))
#define vspinnerSetAutoSort(s, f) \
    vclassSend(vspinnerGetClass(s), vspinnerSET_AUTO_SORT, (s, f))
#define vspinnerSetList(s, l) \
    vclassSend(vspinnerGetClass(s), vspinnerSET_LIST, (s, l))
#define vspinnerSetTextScribedAt(s, v, i) \
    vclassSend(vspinnerGetClass(s), vspinnerSET_TEXT_SCRIBED_AT, (s, v, i))
#define vspinnerSetTextAt(s, v, i) \
    vspinnerSetTextScribedAt(s, vcharScribe(v), i)
#define vspinnerAppendTextScribed(s, v) \
    vclassSend(vspinnerGetClass(s), vspinnerAPPEND_TEXT_SCRIBED, (s, v))
#define vspinnerAppendText(s, v) \
    vspinnerAppendTextScribed(s, vcharScribe(v))
#define vspinnerDeleteTextScribed(s, v) \
    vclassSend(vspinnerGetClass(s), vspinnerDELETE_TEXT_SCRIBED, (s, v))
#define vspinnerDeleteText(s, v) \
    vspinnerDeleteTextScribed(s, vcharScribe(v))
#define vspinnerDeleteTextAt(s, i) \
    vclassSend(vspinnerGetClass(s), vspinnerDELETE_TEXT_AT, (s, i))
#define vspinnerSelectTextScribed(s, v) \
    vclassSend(vspinnerGetClass(s), vspinnerSELECT_TEXT_SCRIBED, (s, v))
#define vspinnerSelectText(s, v) \
    vspinnerSelectTextScribed(s, vcharScribe(v))
#define vspinnerSelectTextAt(s, i) \
    vcontrolSetValue(vspinnerGetControl(s), i)
#define vspinnerFindTextScribedIndex(s, v) \
    vclassSend(vspinnerGetClass(s), vspinnerFIND_TEXT_SCRIBED_INDEX, (s, v))
#define vspinnerFindTextIndex(s, v) \
    vspinnerFindTextScribedIndex(s, vcharScribe(v))
#define vspinnerGetTextitem(s) \
    ((s)->textitem)
#define vspinnerGetClass(s) \
    ((vspinnerClass*)vcontrolGetClass(vspinnerGetControl(s)))
#define vspinnerGetData(s) \
    vcontrolGetData(vspinnerGetControl(s))
#define vspinnerGetTitle(s) \
    vcontrolGetTitle(vspinnerGetControl(s))
#define vspinnerGetNotify(s) \
    vcontrolGetNotify(vspinnerGetControl(s))
#define vspinnerGetListstr(s) \
    ((s)->liststr)
#define vspinnerGetList(s) \
    vliststrGetList(vspinnerGetListstr(s))
#define vspinnerGetValue(s) \
    vcontrolGetValue(vspinnerGetControl(s))
#define vspinnerGetMin(s) \
    vcontrolGetMin(vspinnerGetControl(s))
#define vspinnerGetMax(s) \
    (vcontrolGetMax(vspinnerGetControl(s)) - \
     vcontrolGetView(vspinnerGetControl(s)))
#define vspinnerGetIncrement(s) \
    vcontrolGetIncrement(vspinnerGetControl(s))
#define vspinnerGetText(s, t, l) \
    vtextitemGetText(vspinnerGetTextitem(s), t, l)
#define vspinnerGetTextScribed(s) \
    vtextitemGetTextScribed(vspinnerGetTextitem(s))
#define vspinnerGetTextAsString(s) \
    vtextitemGetTextAsString(vspinnerGetTextitem(s))
#define vspinnerGetTextCount(s) \
    vliststrGetRowCount(vspinnerGetListstr(s))
#define vspinnerGetTextAt(s, i) \
    ((const vchar *)vliststrGetCellValue(vspinnerGetListstr(s), i, 0))
#define vspinnerGetTextScribedAt(s, i) \
    vliststrGetCellValueScribed(vspinnerGetListstr(s), i, 0)
#define vspinnerMarkContentDirty(s) \
    vclassSend(vspinnerGetClass(s), vspinnerMARK_CONTENT_DIRTY, (s))
#define vspinnerRecalcContent(s) \
    vclassSend(vspinnerGetClass(s), vspinnerRECALC_CONTENT, (s))
#define vspinnerMarkListDirty(s) \
    vclassSend(vspinnerGetClass(s), vspinnerMARK_LIST_DIRTY, (s))
#define vspinnerSortList(s) \
    vclassSend(vspinnerGetClass(s), vspinnerSORT_LIST, (s))
#define vspinnerIsModifyable(s) \
    ((s)->flags & _vspinnerTEXT_MODIFYABLE)
#define vspinnerIsWrap(s) \
    ((s)->flags & _vspinnerWRAP)
#define vspinnerIsAutoSort(s) \
    ((s)->flags & _vspinnerAUTO_SORT)
#define _vspinnerGetDefaultCompareFunc(s) \
    vclassGet(vspinnerGetClass(s), vspinnerCOMPARE)

vportEND_CPLUSPLUS_EXTERN_C

#endif /* #ifndef vspinnerINCLUDED */


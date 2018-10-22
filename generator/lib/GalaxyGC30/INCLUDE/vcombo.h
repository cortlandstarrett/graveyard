/* $Id: vcombo.h,v 1.54 1997/08/22 01:40:49 robert Exp $ */

/************************************************************

    vcombo.h
    C Interface to static and editable combo box

    (c) Copyright Visix Software  1992
    All rights reserved
    
************************************************************/

#ifndef vcomboINCLUDED
#define vcomboINCLUDED 1

#ifndef  vportINCLUDED
#include <vport.h>
#endif

#ifndef  vscribeINCLUDED
#include vscribeHEADER
#endif

#ifndef  vcharINCLUDED
#include vcharHEADER
#endif

#ifndef  vclassINCLUDED
#include vclassHEADER
#endif

#ifndef  vcomboboxINCLUDED
#include vcomboboxHEADER
#endif

#ifndef  vtextitemINCLUDED
#include vtextitemHEADER
#endif

#ifndef  vlistINCLUDED
#include vlistHEADER
#endif

#ifndef  vlistitemINCLUDED
#include vlistitemHEADER
#endif

#ifndef  vlafINCLUDED
#include vlafHEADER
#endif 

#ifndef  vdialogINCLUDED
#include vdialogHEADER
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C


/*****************************************************************************
 * PUBLIC TYPE DEFINITION
 *****************************************************************************/

typedef struct vcombo          vcombo;
typedef struct vcomboClass     vcomboClass;

typedef void (*vcomboNoteProc)(vcombo *combo, vevent *event);
typedef int  (*vcomboHookProc)(vcombo *combo, const vchar *text);
typedef int  (*vcomboCompareProc)(const vchar *string1, const vchar *string2);

/*
 * For C -> C++ merge
 */

typedef vcombo              vcomboPopdown;
typedef vlistitem           vcomboListitem;
typedef vlistitem           vcomboPopdownListitem;
typedef vtextitem           vcomboTextitem;
typedef vtextitem           vcomboPopdownTextitem;

/*****************************************************************************
 * PUBLIC MANAGERICAL FUNCTION PROTOTYPES
 *****************************************************************************/

void            vcomboStartup(void);

/*****************************************************************************
 * PUBLIC FUNCTION PROTOTYPES
 *****************************************************************************/

/* Combo Class Functions */

void            vcomboAppendText(vcombo *combo, const vchar *text);
void            vcomboAppendTextScribed(vcombo *combo, vscribe *scribe);
vcombo         *vcomboClone(vcombo *combo);
void            vcomboCopy(vcombo *combo, vcombo *target);
void            vcomboCopyInit(vcombo *combo, vcombo *target);
vcombo         *vcomboCreate(void);
vcombo         *vcomboCreateOfClass(vcomboClass *clas);
vcombo         *vcomboCreatePopdown(void);
void            vcomboDeleteText(vcombo *combo, const vchar *text);
void            vcomboDeleteTextAt(vcombo *combo, int index);
void            vcomboDeleteTextScribed(vcombo *combo, vscribe *scribe);
void            vcomboDestroy(vcombo *combo);
int             vcomboFindTextIndex(vcombo *combo, const vchar *text);
int             vcomboFindTextScribedIndex(vcombo *combo, vscribe *scribe);
void           *vcomboGetData(vcombo *combo);
vcomboClass    *vcomboGetDefaultClass(void);
vcomboClass    *vcomboGetClass(vcombo *combo);
vliststrClass  *vcomboGetDefaultListClass(void);
vcomboHookProc  vcomboGetHook(vcombo *combo);
vdialogItem    *vcomboGetItem(vcombo *combo);
vlist          *vcomboGetList(vcombo *combo);
vlistitem      *vcomboGetListitem(vcombo *combo);
vliststr       *vcomboGetListstr(vcombo *combo);
vcomboNoteProc  vcomboGetNotify(vcombo *combo);
vcomboClass    *vcomboGetPopdownClass(void);
void            vcomboGetText(vcombo *combo, vchar *text, int length);
vstr           *vcomboGetTextAsString(vcombo *combo);
const vchar    *vcomboGetTextAt(vcombo *combo, int index);
int             vcomboGetTextCount(vcombo *combo);
vscribe        *vcomboGetTextScribed(vcombo *combo);
vscribe        *vcomboGetTextScribedAt(vcombo *combo, int index);
vtextitem      *vcomboGetTextitem(vcombo *combo);
const vchar    *vcomboGetTitle(vcombo *combo);
int             vcomboGetVisibleRows(vcombo *combo);
void            vcomboInit(vcombo *combo);
void            vcomboInitOfClass(vcombo *combo, vcomboClass *clas);
void            vcomboInitPopdown(vcombo *combo);
int             vcomboIsAutoSort(vcombo *combo);
int             vcomboIsModifyable(vcombo *combo);
vcombo         *vcomboLoad(vresource resource);
void            vcomboLoadInit(vcombo *combo, vresource resource);
void            vcomboMarkContentDirty(vcombo *combo);
void            vcomboMarkListDirty(vcombo *combo);
void            vcomboRecalcContent(vcombo *combo);
void            vcomboSelectText(vcombo *combo, const vchar *text);
void            vcomboSelectTextAt(vcombo *combo, int index);
void            vcomboSelectTextScribed(vcombo *combo, vscribe *scribe);
void            vcomboSetAutoSort(vcombo *combo, int onOff);
void            vcomboSetData(vcombo *combo, const void *data);
void            vcomboSetHook(vcombo *combo, vcomboHookProc hookProc);
void            vcomboSetList(vcombo *combo, vlist *list);
void            vcomboSetModifyable(vcombo *combo, int onOff);
void            vcomboSetNotify(vcombo *combo, vcomboNoteProc noteProc);
void            vcomboSetTextAt(vcombo *combo, const vchar *text, int index);
void            vcomboSetTextScribedAt(vcombo *combo, 
				       vscribe *scribe, int index);
void            vcomboSetTitle(vcombo *combo, const vchar *title);
void            vcomboSetTitleScribed(vcombo *combo, vscribe *scribe);
void            vcomboSetVisibleRows(vcombo *combo, int rows);
void            vcomboSortList(vcombo *combo);
void            vcomboStore(vcombo *combo, vresource resource);

/*****************************************************************************
 * PRIVATE CONSTANTS
 *****************************************************************************/

#define _vcomboDIRTY_CONTENT        0x0002
#define _vcomboDIRTY_LIST           0x0004

#define _vcomboFROM_ITEM            0x0008
#define _vcomboTEXT_MODIFYABLE      0x0001
#define _vcomboAUTO_SORT            0x0010

/*****************************************************************************
 * PRIVATE TYPE DEFINITION
 *****************************************************************************/

struct vcombo { 
    vcomboboxPopdown      item;
    vcomboHookProc      hookProc;
    vlistObserver      *observer;
};

/*
 * Combo class Definition
 */
#define vcomboCLASS(SUPER, COMBO, NOTIFY) \
    vcomboboxPopdownCLASS(SUPER, COMBO, vcomboboxValue, NOTIFY, vcomboboxNoteProc); \
    vclassMETHOD(vcomboAPPEND_TEXT_SCRIBED, (COMBO *combo, vscribe *scribe)); \
    vclassVARIABLE(vcomboCOMPARE, vcomboCompareProc); \
    vclassMETHOD_RET(vcomboCREATE_LISTITEM, vlistitem*, (COMBO *combo)); \
    vclassMETHOD_RET(vcomboCREATE_TEXTITEM, vtextitem*, (COMBO *combo)); \
    vclassMETHOD(vcomboDELETE_TEXT_AT, (COMBO *combo, int index)); \
    vclassMETHOD(vcomboDELETE_TEXT_SCRIBED, (COMBO *combo, vscribe *scribe)); \
    vclassMETHOD_RET(vcomboFIND_TEXT_SCRIBED_INDEX, int, \
		     (COMBO *combo, vscribe *scribe)); \
    vclassVARIABLE(vcomboLIST_BOX_ROWS, short); \
    vclassVARIABLE(vcomboLIST_LEFT_MARGIN, short); \
    vclassVARIABLE(vcomboLIST_RIGHT_MARGIN, short); \
    vclassMETHOD(vcomboMARK_CONTENT_DIRTY, (COMBO *combo)); \
    vclassMETHOD(vcomboMARK_LIST_DIRTY, (COMBO *combo)); \
    vclassMETHOD(vcomboRECALC_CONTENT, (COMBO *combo)); \
    vclassMETHOD(vcomboSCROLL_TO_TEXT_SCRIBED, \
		 (COMBO *combo, vscribe *scribe)); \
    vclassMETHOD(vcomboSELECT_TEXT_AT, (COMBO *combo, int index)); \
    vclassMETHOD(vcomboSELECT_TEXT_SCRIBED, (COMBO *combo, vscribe *scribe)); \
    vclassMETHOD(vcomboSET_AUTO_SORT, (COMBO *combo, int onOff)); \
    vclassMETHOD(vcomboSET_HOOK, (COMBO *combo, vcomboHookProc hookProc)); \
    vclassMETHOD(vcomboSET_LIST, (COMBO *combo, vlist *list)); \
    vclassMETHOD(vcomboSET_MODIFYABLE, (COMBO *combo, int onOff)); \
    vclassMETHOD(vcomboSET_TEXT_SCRIBED_AT, \
		 (COMBO *combo, vscribe *scribe, int index)); \
    vclassMETHOD(vcomboSET_VISIBLE_ROWS, (COMBO *combo, int rows)); \
    vclassMETHOD(vcomboSORT_LIST, (COMBO *combo)); \
    vclassVARIABLE(vcomboTEXT_BUTTON_MARGIN, short); \
    vclassVARIABLE(vcomboTEXT_LIST_MARGIN, short)

struct vcomboClass {
    vcomboCLASS(vcomboClass, vcombo, vcomboNoteProc);
};


vportALIAS(vcomboPopdown, vcombo)


/*****************************************************************************
 * PRIVATE FUNCTION PROTOTYPES
 *****************************************************************************/

vcombobox        *_vcomboGetCombobox(vcombo *combo);
vcomboboxPopdown *_vcomboGetComboboxPopdown(vcombo *combo);

int _vcomboCallHookProc(vcombo *combo, const vchar *text);

vcomboCompareProc _vcomboGetDefaultCompareFunc(vcombo *combo);
short _vcomboGetDefaultTextButtonMargin(vcombo *combo);
short _vcomboGetDefaultTextListMargin(vcombo *combo);
short _vcomboGetDefaultListLeftMargin(vcombo *combo);
short _vcomboGetDefaultListRightMargin(vcombo *combo);
short _vcomboGetDefaultListBoxRows(vcombo *combo);
int _vcomboGetFontHeight(vcombo *combo);

/*****************************************************************************
 * PRIVATE FUNCTION MACRO DEFINITIONS
 *****************************************************************************/

#define vcomboAppendText(c, t) vcomboAppendTextScribed(c, vcharScribe(t))
#define vcomboAppendTextScribed(c, v) vclassSend(vcomboGetClass(c), vcomboAPPEND_TEXT_SCRIBED, (c, v))
#define vcomboClone(c) ((vcombo *)vdialogCloneItem(vcomboGetItem(c)))
#define vcomboCopy(c1, c2) vclassSend(vcomboGetClass(c1), vobjectCOPY, (c1, c2))
#define vcomboCopyInit(c1, c2) vdialogCopyInitItem(vcomboGetItem(c1), vcomboGetItem(c2))
#define vcomboCreate() vcomboCreateOfClass(vcomboGetDefaultClass())
#define vcomboCreateOfClass(clas) ((vcombo *)vdialogCreateItemOfClass((vdialogItemClass*)(clas)))
#define vcomboCreatePopdown() vcomboCreateOfClass(vcomboGetPopdownClass())
#define vcomboDeleteText(c, t) vcomboDeleteTextScribed(c, vcharScribe(t))
#define vcomboDeleteTextAt(c, i) vclassSend(vcomboGetClass(c), vcomboDELETE_TEXT_AT, (c, i))
#define vcomboDeleteTextScribed(c, v) vclassSend(vcomboGetClass(c), vcomboDELETE_TEXT_SCRIBED, (c, v))
#define vcomboDestroy(c) vdialogDestroyItem(vcomboGetItem(c))
#define vcomboFindTextIndex(c, v) vcomboFindTextScribedIndex(c, vcharScribe(v))
#define vcomboFindTextScribedIndex(c, v) vclassSend(vcomboGetClass(c), vcomboFIND_TEXT_SCRIBED_INDEX, (c, v))
#define vcomboGetClass(c) ((vcomboClass *)vdialogGetItemClass(vcomboGetItem(c)))
#define vcomboGetData(c) vdialogGetItemData(vcomboGetItem(c))
#define vcomboGetDefaultListClass() vlistitemGetDefaultListDataClass()
#define vcomboGetHook(c) ((c)->hookProc)
#define _vcomboGetComboboxPopdown(c) vportBASE_OBJECT((c), item)
#define _vcomboGetCombobox(c) vcomboboxGetPopdownCombobox(_vcomboGetComboboxPopdown(c))
#define vcomboGetItem(c) vcomboboxGetPopdownItem(_vcomboGetComboboxPopdown(c))
#define vcomboGetListitem(c) ((vlistitem *)vcomboboxGetChoicebox(_vcomboGetCombobox(c)))
#define vcomboGetList(c) vlistitemGetList(vcomboGetListitem(c))
#define vcomboGetListstr(c) vlistitemGetListstr(vcomboGetListitem(c))
#define vcomboGetNotify(c) (vcomboNoteProc)(vdialogGetItemNotify(vcomboGetItem(c)))
#define vcomboGetTextitem(c) ((vtextitem *)vcomboboxGetEntrybox(_vcomboGetCombobox(c)))
#define vcomboGetText(c, t, l) vtextitemGetText(vcomboGetTextitem(c), t, l)
#define vcomboGetTextAsString(c) vtextitemGetTextAsString(vcomboGetTextitem(c))
#define vcomboGetTextAt(c, i) vcomboboxGetValueTitle(vcomboboxGetValueAt(_vcomboGetCombobox(c), i))
#define vcomboGetTextCount(c) vcomboboxGetValueCount(_vcomboGetCombobox(c))
#define vcomboGetTextScribed(c) vtextitemGetTextScribed(vcomboGetTextitem(c))
#define vcomboGetTextScribedAt(c, i) vcharScribe(vcomboGetTextAt(c, i))
#define vcomboGetTitle(c) vdialogGetItemTitle(vcomboGetItem(c))
#define vcomboGetVisibleRows(c) vcomboboxGetVisibleValues(_vcomboGetCombobox(c))
#define vcomboInit(c) vcomboInitOfClass((c), vcomboGetDefaultClass())
#define vcomboInitOfClass(c, clas) vdialogInitItemOfClass(vcomboGetItem(c), (vdialogItemClass*)(clas))
#define vcomboInitPopdown(c) vcomboInitOfClass((c), vcomboGetPopdownClass())
#define vcomboIsAutoSort(c) vcomboboxIsAutoSort(_vcomboGetCombobox(c))
#define vcomboIsModifyable(c) vcomboboxIsModifyable(_vcomboGetCombobox(c))
#define vcomboLoad(r) ((vcombo *)vdialogLoadItem(r))
#define vcomboLoadInit(c, r) vdialogLoadInitItem(vcomboGetItem(c), r)
#define vcomboMarkContentDirty(c) vclassSend(vcomboGetClass(c), vcomboMARK_CONTENT_DIRTY, (c))
#define vcomboMarkListDirty(c) vclassSend(vcomboGetClass(c), vcomboMARK_LIST_DIRTY, (c))
#define vcomboRecalcContent(c) vclassSend(vcomboGetClass(c), vcomboRECALC_CONTENT, (c))
#define vcomboSelectText(c, v) vcomboSelectTextScribed(c, vcharScribe(v))
#define vcomboSelectTextAt(c, i) vclassSend(vcomboGetClass(c), vcomboSELECT_TEXT_AT, (c, i))
#define vcomboSelectTextScribed(c, v) vclassSend(vcomboGetClass(c), vcomboSELECT_TEXT_SCRIBED, (c, v))
#define vcomboSetAutoSort(c, onOff) vclassSend(vcomboGetClass(c), vcomboSET_AUTO_SORT, (c, onOff))
#define vcomboSetData(c, d) vdialogSetItemData((vdialogItem *)(c), (d))
#define vcomboSetHook(c, hook) vclassSend(vcomboGetClass(c), vcomboSET_HOOK, (c, hook))
#define vcomboSetList(c, l) vclassSend(vcomboGetClass(c), vcomboSET_LIST, (c, l))
#define vcomboSetModifyable(c, onOff) vclassSend(vcomboGetClass(c), vcomboSET_MODIFYABLE, (c, onOff))
#define vcomboSetNotify(c, note) vclassSend(vcomboGetClass(c), vdialogSET_ITEM_NOTIFY, (c, note))
#define vcomboSetTextAt(c, v, i) vcomboSetTextScribedAt(c, vcharScribe(v), i)
#define vcomboSetTextScribedAt(c, v, i) vclassSend(vcomboGetClass(c), vcomboSET_TEXT_SCRIBED_AT, (c, v, i))
#define vcomboSetTitle(c, t) vcomboSetTitleScribed(c, vcharScribe(t))
#define vcomboSetTitleScribed(c, t) vclassSend(vcomboGetClass(c), vdialogSET_ITEM_TITLE_SCRIBED, (c, t))
#define vcomboSetVisibleRows(c, rows) vclassSend(vcomboGetClass(c), vcomboSET_VISIBLE_ROWS, (c, rows))
#define vcomboSortList(c) vclassSend(vcomboGetClass(c), vcomboSORT_LIST, (c))
#define vcomboStore(c, r) vclassSend(vcomboGetClass(c), vobjectSTORE, (c, r))

#define _vcomboGetDefaultCompareFunc(s) vclassGet(vcomboGetClass(s), vcomboCOMPARE)
#define _vcomboGetDefaultListBoxRows(c) vclassGet(vcomboGetClass(c), vcomboLIST_BOX_ROWS)
#define _vcomboGetDefaultListLeftMargin(c) vclassGet(vcomboGetClass(c), vcomboLIST_LEFT_MARGIN)
#define _vcomboGetDefaultListRightMargin(c) vclassGet(vcomboGetClass(c), vcomboLIST_RIGHT_MARGIN)
#define _vcomboGetDefaultTextButtonMargin(c) vclassGet(vcomboGetClass(c), vcomboTEXT_BUTTON_MARGIN)
#define _vcomboGetDefaultTextListMargin(c) vclassGet(vcomboGetClass(c), vcomboTEXT_LIST_MARGIN)
#define _vcomboGetFontHeight(c) (vfontHeight(vdialogDetermineItemFont(vcomboGetItem(c))) + 8)

vportEND_CPLUSPLUS_EXTERN_C

#endif /* vcomboINCLUDED */



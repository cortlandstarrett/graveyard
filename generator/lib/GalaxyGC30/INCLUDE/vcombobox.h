/* $Id: vcombobox.h,v 1.21 1997/06/25 17:40:14 robert Exp $ */

/************************************************************

    vcombobox.h
    C Interface to static and editable combobox box

    (c) Copyright Visix Software  1992
    All rights reserved
    
************************************************************/

#ifndef vcomboboxINCLUDED
#define vcomboboxINCLUDED 1

#ifndef  vportINCLUDED
#include <vport.h>
#endif

#ifndef vcontainINCLUDED
#include vcontainerHEADER
#endif 

#ifndef  vscribeINCLUDED
#include vscribeHEADER
#endif

#ifndef  vbuttonINCLUDED
#include vbuttonHEADER
#endif

#ifndef  vtextitemINCLUDED
#include vtextitemHEADER
#endif

#ifndef  vlistitemINCLUDED
#include vlistitemHEADER
#endif

#ifndef  vdialogINCLUDED
#include vdialogHEADER
#endif

#ifndef  vobjectINCLUDED
#include vobjectHEADER
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C

/*****************************************************************************
 * PUBLIC CONSTANTS
 *****************************************************************************/

enum {
    vcomboboxID_ATTRIBUTE_CHANGE_VALUES = vcontainerNEXT_ID_ATTRIBUTE,
    vcomboboxID_ATTRIBUTE_MODIFYABLE,                                 
    vcomboboxID_ATTRIBUTE_AUTOSORT,                                   
    vcomboboxID_ATTRIBUTE_VISIBLE_VALUES,                             
    vcomboboxNEXT_ID_ATTRIBUTE                                        
};

enum {
    vcomboboxPopdownNEXT_ID_ATTRIBUTE = vcomboboxNEXT_ID_ATTRIBUTE  
};

enum {
    vcomboboxNEXT_SELECT = vcontainerNEXT_SELECT
};

enum {
    vcomboboxPopdownSELECT_OPEN = vcomboboxNEXT_SELECT,    
    vcomboboxPopdownSELECT_CLOSE,                        
    vcomboboxPopdownNEXT_SELECT = vcomboboxNEXT_SELECT     
};

/*
 * for vcomboboxNoteProc message component
 */
enum {
    vcomboboxNOTIFY_SCROLL = 1,          
    vcomboboxNOTIFY_ACCEPT,              
    vcomboboxNOTIFY_SELECT,              
    vcomboboxNEXT_NOTIFY                 
};

/*
 * for vcomboboxPopdownNoteProc message component
 */
enum {
    vcomboboxPopdownNOTIFY_OPEN = vcomboboxNEXT_NOTIFY,   
    vcomboboxPopdownNOTIFY_CLOSE,                      
    vcomboboxPopdownNEXT_NOTIFY                        
};

/*
 * for vcomboboxFindValueExactIndex, vcomboboxFindPopdownValueExactIndex,
 *     vcomboboxFindValueClosestIndex, vcomboboxFindPopdownValueClosestIndex,
 *     vcomboboxFindValuePartialIndex, vcomboboxFindPopdownValuePartialIndex
 */
enum{
  vcomboboxFROM_BEGINNING = 0,     
  vcomboboxFROM_CURRENT,           
  vcomboboxFROM_END                
};

/*
 * for vcomboboxFindValueExactIndex, vcomboboxFindPopdownValueExactIndex,
 *     vcomboboxFindValueClosestIndex, vcomboboxFindPopdownValueClosestIndex,
 *     vcomboboxFindValuePartialIndex, vcomboboxFindPopdownValuePartialIndex
 */
enum {
  vcomboboxSEARCH_FORWARD = 0,     
  vcomboboxSEARCH_BACKWARD         
};

/* 
 * for vcomboboxSetAcceptBehavior, vcomboboxGetAcceptBehavior,
 *     vcomboboxSetSelectBehavior, vcomboboxGetSelectBehavior,
 *     vcomboboxSetScrollBehavior, vcomboboxGetScrollBehavior
 */
enum {
    vcomboboxBEHAVIOR_DO_NOTHING,        
    vcomboboxBEHAVIOR_MATCH_OR_ADD,      
    vcomboboxBEHAVIOR_MATCH_OR_CLOSEST,  
    vcomboboxBEHAVIOR_MATCH_OR_PARTIAL,
    vcomboboxBEHAVIOR_MATCH_OR_FIRST,    
    vcomboboxBEHAVIOR_MATCH_OR_NOTHING,  
    vcomboboxBEHAVIOR_MATCH_OR_REVERT,   
    vcomboboxBEHAVIOR_DEFAULT,           
    vcomboboxNEXT_BEHAVIOR               
};

/*****************************************************************************
 * PUBLIC TYPE DEFINITION
 *****************************************************************************/

typedef struct vcomboboxClass        vcomboboxClass;         
typedef struct vcomboboxPopdownClass vcomboboxPopdownClass; 
typedef struct vcomboboxValueClass   vcomboboxValueClass;    
typedef struct vcombobox             vcombobox;              
typedef struct vcomboboxPopdown      vcomboboxPopdown;      
typedef struct vcomboboxValue        vcomboboxValue;         

typedef void (*vcomboboxNoteProc)(vcombobox *combo, vevent *event, int message);                    
typedef void (*vcomboboxPopdownNoteProc)(vcomboboxPopdown *combo, vevent *event, int message);      

/*****************************************************************************
 * PUBLIC MANAGERICAL FUNCTION PROTOTYPES
 *****************************************************************************/

void              vcomboboxStartup(void);  
void              vcomboboxStartupPopdown(void); 
void              vcomboboxStartupValue(void); 

vcombobox          *vcomboboxGetPartCombobox(vdialogItem *item); 

/*****************************************************************************
 * PUBLIC VALUE FUNCTION PROTOTYPES
 *****************************************************************************/

vcomboboxValue  *vcomboboxCloneValue(vcomboboxValue *value); 
void             vcomboboxCopyInitValue(vcomboboxValue *value,
					vcomboboxValue *target); 
void             vcomboboxCopyValue(vcomboboxValue *value,
				    vcomboboxValue *target); 
vcomboboxValue  *vcomboboxCreateValue(); 
vcomboboxValue  *vcomboboxCreateValueOfClass(vcomboboxValueClass *clas);
void             vcomboboxDestroyValue(vcomboboxValue *value); 
void             vcomboboxDrawValue(vcomboboxValue *value,
				    vrect *rect); 
void             vcomboboxDrawValueWith(vcomboboxValue *value,
					vrect *rect, vdrawcontext *context); 
vcomboboxValueClass *vcomboboxGetDefaultValueClass(void); 
vcomboboxValueClass *vcomboboxGetValueClass(vcomboboxValue *value); 
vcombobox       *vcomboboxGetValueCombobox(vcomboboxValue *value); 
const void      *vcomboboxGetValueData(vcomboboxValue *value); 
vobjectAttributed *vcomboboxGetValueObject(vcomboboxValue *value); 
void             vcomboboxGetValueSize(vcomboboxValue *value, 
				       int *width,
				       int *height); 
const vname     *vcomboboxGetValueTag(vcomboboxValue *value);
const vchar     *vcomboboxGetValueTitle(vcomboboxValue *value); 
void             vcomboboxInitValue(vcomboboxValue *value); 
void             vcomboboxInitValueOfClass(vcomboboxValue *value,
					   vcomboboxValueClass *clas); 
void             vcomboboxLoadInitValue(vcomboboxValue *value,
					vresource resource); 
vcomboboxValue  *vcomboboxLoadValue(vresource resource); 
void             vcomboboxSetValueCombobox(vcomboboxValue *value,
					   vcombobox *combo); 
void             vcomboboxSetValueData(vcomboboxValue *value,
				       const void *data); 
void             vcomboboxSetValueTag(vcomboboxValue *value,
				      const vname *tag);
void             vcomboboxSetValueTitle(vcomboboxValue *value,
					const vchar *title); 
void             vcomboboxSetValueTitleScribed(vcomboboxValue *value,
					       vscribe *scribe); 
void             vcomboboxStoreValue(vcomboboxValue *value,
				     vresource resource); 

/*****************************************************************************
 * PUBLIC STANDARD FUNCTION PROTOTYPES
 *****************************************************************************/

void              vcomboboxAcceptValue(vcombobox *combo,
				       vcomboboxValue *value); 
void              vcomboboxAppendValue(vcombobox *combo,
				       vcomboboxValue *value); 
void              vcomboboxBlockEntrybox(vcombobox *combo); 
vcombobox        *vcomboboxClone(vcombobox *combo); 
int               vcomboboxCompareValues(vcombobox *combo,
					 vcomboboxValue *value1,
					 vcomboboxValue *value2); 
void              vcomboboxCopy(vcombobox *combo,
				vcombobox *target); 
void              vcomboboxCopyInit(vcombobox *combo,
				    vcombobox *target); 
vcombobox        *vcomboboxCreate(void); 
vcombobox        *vcomboboxCreateOfClass(vcomboboxClass *clas); 
vcomboboxValue   *vcomboboxRemoveValue(vcombobox *combo,
				       vcomboboxValue *value); 
vcomboboxValue   *vcomboboxRemoveValueAt(vcombobox *combo, 
					 int index); 
void              vcomboboxDestroy(vcombobox *combo); 
void              vcomboboxDrawComboboxValue(vcombobox *combo,
					     vcomboboxValue *value,
					     vrect *rect); 
void              vcomboboxDrawComboboxValueWith(vcombobox *combo,
					     vcomboboxValue *value,
					     vrect *rect,
						 vdrawcontext *context); 
vcomboboxValue   *vcomboboxFindValue(vcombobox *combo,
				     const vname *tag);
void              vcomboboxFindValueClosestIndex(vcombobox *combo,
						 vcomboboxValue *value,
						 int direction,
						 int from,
						 int *after,
						 int *before); 
int               vcomboboxFindValueExactIndex(vcombobox *combo,
					       vcomboboxValue *value,
					       int direction, int from); 
int               vcomboboxFindValuePartialIndex(vcombobox *combo,
						vcomboboxValue *value,
						int direction, int from); 
int               vcomboboxGetAcceptBehavior(vcombobox *combo); 
vdialogItem      *vcomboboxGetChoicebox(vcombobox *combo); 
void              vcomboboxGetChoiceboxRect(vcombobox *combo,
					    vrect *rect); 
void              vcomboboxGetChoiceboxSize(vcombobox *combo,
					    int *width,
					    int *height); 
vcomboboxClass   *vcomboboxGetClass(vcombobox *combo); 
vcontainer       *vcomboboxGetContainer(vcombobox *combo); 
const void       *vcomboboxGetData(vcombobox *combo); 
vcomboboxClass   *vcomboboxGetDefaultClass(void); 
vdialogItem      *vcomboboxGetEntrybox(vcombobox *combo); 
void              vcomboboxGetEntryboxChoiceboxGap(vcombobox *combo,
						   int *gap); 
void              vcomboboxGetEntryboxRect(vcombobox *combo,
					   vrect *rect); 
void              vcomboboxGetEntryboxSize(vcombobox *combo,
					   int *width,
					   int *height);
vdialogItem      *vcomboboxGetItem(vcombobox *combo); 
vcomboboxNoteProc vcomboboxGetNotify(vcombobox *combo); 
int               vcomboboxGetScrollBehavior(vcombobox *combo); 
int               vcomboboxGetSelectBehavior(vcombobox *combo); 
int               vcomboboxGetSelectedIndex(vcombobox *combo); 
const vchar      *vcomboboxGetTitle(vcombobox *combo); 
vcomboboxValue   *vcomboboxGetValue(vcombobox *combo); 
vcomboboxValue   *vcomboboxGetValueAt(vcombobox *combo, int index); 
int               vcomboboxGetValueCount(vcombobox *combo);
int               vcomboboxGetValueIndex(vcombobox *combo,
					 vcomboboxValue *value);
void              vcomboboxGetValueMaxSize(vcombobox *combo,
					   int *width,
					   int *height); 
void              vcomboboxGetComboboxValueSize(vcombobox *combo,
						vcomboboxValue *value,
						int *width,
						int *height); 
int               vcomboboxGetVisibleValues(vcombobox *combo); 
void              vcomboboxInit(vcombobox *combo); 
void              vcomboboxInitOfClass(vcombobox *combo,
				       vcomboboxClass *clas); 
int               vcomboboxIsAutoSort(vcombobox *combo); 
int               vcomboboxIsEntryboxBlocked(vcombobox *combo); 
int               vcomboboxIsModifyable(vcombobox *combo); 
int               vcomboboxIsValuePartial(vcombobox *combo,
					 vcomboboxValue *subValue,
					 vcomboboxValue *superValue);
int               vcomboboxIsWrap(vcombobox *combo); 
vcombobox        *vcomboboxLoad(vresource resource); 
void              vcomboboxLoadInit(vcombobox *combo,
				    vresource resource); 
void              vcomboboxMoveValue(vcombobox *combo,
				     int from, int to); 
void              vcomboboxNotify(vcombobox *combo,
				  vevent *event, int message); 
void              vcomboboxRecalc(vcombobox *combo); 
void              vcomboboxScrollToIndex(vcombobox *combo,
					 int index); 
void              vcomboboxScrollToValue(vcombobox *combo,
					 vcomboboxValue *value); 
void              vcomboboxSelectValue(vcombobox *combo,
				       vcomboboxValue *value); 
void              vcomboboxSelectValueAt(vcombobox *combo,
					 int index); 
void              vcomboboxSetAcceptBehavior(vcombobox *combo,
					     int behavior); 
void              vcomboboxSetAutoSort(vcombobox *combo, int onOff); 
void              vcomboboxSetData(vcombobox *combo,
				   const void *data); 
void              vcomboboxSetModifyable(vcombobox *combo,
					 int onOff); 
void              vcomboboxSetNotify(vcombobox *combo,
				     vcomboboxNoteProc noteProc); 
void              vcomboboxSetScrollBehavior(vcombobox *combo,
					     int behavior); 
void              vcomboboxSetSelectBehavior(vcombobox *combo,
					     int behavior); 
void              vcomboboxSetTitle(vcombobox *combo,
				    const vchar *title); 
void              vcomboboxSetTitleScribed(vcombobox *combo,
					   vscribe *scribe); 
void              vcomboboxSetValue(vcombobox *combo,
				    vcomboboxValue *value); 
void              vcomboboxSetValueAt(vcombobox *combo,
				      vcomboboxValue *value,
				      int index); 
void              vcomboboxSetVisibleValues(vcombobox *combo,
					    int values); 
void              vcomboboxSetWrap(vcombobox *combo, int onOff); 
void              vcomboboxSortValues(vcombobox *combo); 
void              vcomboboxStore(vcombobox *combo,
				 vresource resource); 
void              vcomboboxUnblockEntrybox(vcombobox *combo); 

/*****************************************************************************
 * PUBLIC POPDOWN FUNCTION PROTOTYPES
 *****************************************************************************/

void              vcomboboxAcceptPopdownValue(vcomboboxPopdown *combo,
					      vcomboboxValue *value); 
void              vcomboboxAppendPopdownValue(vcomboboxPopdown *combo,
					      vcomboboxValue *value); 
void              vcomboboxBlockPopdownEntrybox(vcomboboxPopdown *combo);
vcomboboxPopdown *vcomboboxClonePopdown(vcomboboxPopdown *combo); 
void              vcomboboxClosePopdownDialog(vcomboboxPopdown *combo); 
int               vcomboboxComparePopdownValues(vcomboboxPopdown *combo,
						vcomboboxValue *value1,
						vcomboboxValue *value2);
void              vcomboboxCopyInitPopdown(vcomboboxPopdown *combo,
					   vcomboboxPopdown *target); 
void              vcomboboxCopyPopdown(vcomboboxPopdown *combo,
				       vcomboboxPopdown *target); 
vcomboboxPopdown *vcomboboxCreatePopdown(void);
vcomboboxPopdown *vcomboboxCreatePopdownOfClass(vcomboboxPopdownClass *clas); 
vcomboboxValue   *vcomboboxRemovePopdownValue(vcomboboxPopdown *combo,
					      vcomboboxValue *value); 
vcomboboxValue   *vcomboboxRemovePopdownValueAt(vcomboboxPopdown *combo,
						int index); 
void              vcomboboxDestroyPopdown(vcomboboxPopdown *combo); 
void              vcomboboxDrawPopdownValue(vcomboboxPopdown *combo,
					    vcomboboxValue *value,
					    vrect *rect); 
void              vcomboboxDrawPopdownValueWith(vcomboboxPopdown *combo,
						vcomboboxValue *value,
						vrect *rect,
						vdrawcontext *context); 
vcomboboxValue   *vcomboboxFindPopdownValue(vcomboboxPopdown *combo,
					    const vname *tag);
void             vcomboboxFindPopdownValueClosestIndex(vcomboboxPopdown *combo,
						       vcomboboxValue *value,
						       int dir,
						       int from, 
						       int *after,
						       int *before); 
int               vcomboboxFindPopdownValueExactIndex(vcomboboxPopdown *combo,
						      vcomboboxValue *value,
						      int direction,
						      int from); 
int               vcomboboxFindPopdownValuePartialIndex(vcomboboxPopdown *combo,
						       vcomboboxValue *value,
						       int direction,
						       int from); 
vcomboboxPopdownClass *vcomboboxGetDefaultPopdownClass(void);
int               vcomboboxGetPopdownAcceptBehavior(vcomboboxPopdown *combo); 
vdialogItem      *vcomboboxGetPopdownButton(vcomboboxPopdown *combo); 
void              vcomboboxGetPopdownButtonRect(vcomboboxPopdown *combo,
						vrect *rect); 
void              vcomboboxGetPopdownButtonSize(vcomboboxPopdown *combo,
						int *width,
						int *height); 
vdialogItem      *vcomboboxGetPopdownChoicebox(vcomboboxPopdown *combo); 
void              vcomboboxGetPopdownChoiceboxRect(vcomboboxPopdown *combo,
						   vrect *rect); 
void              vcomboboxGetPopdownChoiceboxSize(vcomboboxPopdown *combo,
						   int *width,
						   int *height); 
vcomboboxPopdownClass *vcomboboxGetPopdownClass(vcomboboxPopdown *combo); 
vcombobox        *vcomboboxGetPopdownCombobox(vcomboboxPopdown *combo); 
vcontainer       *vcomboboxGetPopdownContainer(vcomboboxPopdown *combo); 
const void       *vcomboboxGetPopdownData(vcomboboxPopdown *combo); 
vdialog          *vcomboboxGetPopdownDialog(vcomboboxPopdown *combo); 
vdialogItem      *vcomboboxGetPopdownEntrybox(vcomboboxPopdown *combo); 
void              vcomboboxGetPopdownEntryboxButtonGap(vcomboboxPopdown *combo,
						       int *gap); 
void           vcomboboxGetPopdownEntryboxChoiceboxGap(vcomboboxPopdown *combo,
						       int *gap);
void              vcomboboxGetPopdownEntryboxRect(vcomboboxPopdown *combo,
						  vrect *rect); 
void              vcomboboxGetPopdownEntryboxSize(vcomboboxPopdown *combo,
						  int *width,
						  int *height); 
vdialogItem      *vcomboboxGetPopdownItem(vcomboboxPopdown *combo); 
vcomboboxPopdownNoteProc vcomboboxGetPopdownNotify(vcomboboxPopdown *combo); 
int               vcomboboxGetPopdownScrollBehavior(vcomboboxPopdown *combo); 
int               vcomboboxGetPopdownSelectBehavior(vcomboboxPopdown *combo); 
int               vcomboboxGetPopdownSelectedIndex(vcomboboxPopdown *combo); 
const vchar      *vcomboboxGetPopdownTitle(vcomboboxPopdown *combo); 
vcomboboxValue   *vcomboboxGetPopdownValue(vcomboboxPopdown *combo); 
vcomboboxValue   *vcomboboxGetPopdownValueAt(vcomboboxPopdown *combo,
					     int index); 
int               vcomboboxGetPopdownValueCount(vcomboboxPopdown *combo); 
int               vcomboboxGetPopdownValueIndex(vcomboboxPopdown *combo,
						vcomboboxValue *value);
void              vcomboboxGetPopdownValueMaxSize(vcomboboxPopdown *combo,
						  int *width,
						  int *height); 
void              vcomboboxGetPopdownValueSize(vcomboboxPopdown *combo,
					       vcomboboxValue *value,
					       int *width,
					       int *height); 
int               vcomboboxGetPopdownVisibleValues(vcomboboxPopdown *combo); 
void              vcomboboxInitPopdown(vcomboboxPopdown *combo);
void              vcomboboxInitPopdownOfClass(vcomboboxPopdown *combo,
					      vcomboboxPopdownClass *clas); 
int               vcomboboxIsPopdownAutoSort(vcomboboxPopdown *combo); 
int               vcomboboxIsPopdownEntryboxBlocked(vcomboboxPopdown *combo); 
int               vcomboboxIsPopdownModifyable(vcomboboxPopdown *combo); 
int               vcomboboxIsPopdownValuePartial(vcomboboxPopdown *combo,
						vcomboboxValue *subValue,
						vcomboboxValue *superValue);
int               vcomboboxIsPopdownWrap(vcomboboxPopdown *combo); 
void              vcomboboxLoadInitPopdown(vcomboboxPopdown *combo,
					   vresource resource); 
vcomboboxPopdown *vcomboboxLoadPopdown(vresource resource); 
void              vcomboboxMovePopdownValue(vcomboboxPopdown *combo,
					    int from, int to); 
void              vcomboboxNotifyPopdown(vcomboboxPopdown *combo,
					 vevent *event, int message); 
void              vcomboboxOpenPopdownDialog(vcomboboxPopdown *combo); 
void              vcomboboxPlacePopdownDialog(vcomboboxPopdown *combo); 
int               vcomboboxPopdownPopdownDialog(vcomboboxPopdown *combo,
						vevent *event); 
int               vcomboboxPopupPopdownDialog(vcomboboxPopdown *combo,
					      vevent *event); 
void              vcomboboxRecalcPopdown(vcomboboxPopdown *combo); 
void              vcomboboxRecalcPopdownDialog(vcomboboxPopdown *combo); 
void              vcomboboxScrollPopdownToIndex(vcomboboxPopdown *combo,
						int index); 
void              vcomboboxScrollPopdownToValue(vcomboboxPopdown *combo,
						vcomboboxValue *value); 
void              vcomboboxSelectPopdownValue(vcomboboxPopdown *combo,
					      vcomboboxValue *value); 
void              vcomboboxSelectPopdownValueAt(vcomboboxPopdown *combo,
						int index); 
void              vcomboboxSetPopdownAcceptBehavior(vcomboboxPopdown *combo,
						    int behavior); 
void              vcomboboxSetPopdownAutoSort(vcomboboxPopdown *combo,
					      int onOff); 
void              vcomboboxSetPopdownData(vcomboboxPopdown *combo,
					  const void *data); 
void              vcomboboxSetPopdownModifyable(vcomboboxPopdown *combo,
						int onOff); 
void              vcomboboxSetPopdownNotify(vcomboboxPopdown *combo,
					    vcomboboxPopdownNoteProc noteProc); 
void              vcomboboxSetPopdownScrollBehavior(vcomboboxPopdown *combo,
						    int behavior); 
void              vcomboboxSetPopdownSelectBehavior(vcomboboxPopdown *combo,
						    int behavior); 
void              vcomboboxSetPopdownTitle(vcomboboxPopdown *combo,
					   const vchar *title); 
void              vcomboboxSetPopdownTitleScribed(vcomboboxPopdown *combo,
						  vscribe *scribe); 
void              vcomboboxSetPopdownValue(vcomboboxPopdown *combo,
					   vcomboboxValue *value); 
void              vcomboboxSetPopdownValueAt(vcomboboxPopdown *combo,
					     vcomboboxValue *value, int index); 
void              vcomboboxSetPopdownVisibleValues(vcomboboxPopdown *combo,
						   int values); 
void              vcomboboxSetPopdownWrap(vcomboboxPopdown *combo,
					  int onOff); 
void              vcomboboxSortPopdownValues(vcomboboxPopdown *combo); 
void              vcomboboxStorePopdown(vcomboboxPopdown *combo,
					vresource resource); 
void              vcomboboxUnblockPopdownEntrybox(vcomboboxPopdown *combo);

/*****************************************************************************
 * DEPRECATED FUNCTION DEFINITIONS
 *****************************************************************************/

void              vcomboboxDeleteValue(vcombobox *combo,
				       vcomboboxValue *value); 
void              vcomboboxDeleteValueAt(vcombobox *combo, 
					 int index); 
void              vcomboboxDeletePopdownValue(vcomboboxPopdown *combo,
					      vcomboboxValue *value); 
void              vcomboboxDeletePopdownValueAt(vcomboboxPopdown *combo,
						int index); 

/*****************************************************************************
 * PRIVATE CONSTANT DEFINITIONS
 *****************************************************************************/

/*
 * For vcomboboxValue
 */

enum {
    _vcomboboxValueOWN_TITLE      = 0x0001    
};

/*
 * For vcombobox 
 */

enum {
    _vcomboboxFLAGS_MODIFYABLE             = 0x00000001,   
    _vcomboboxFLAGS_BLOCKED                = 0x00000002,   
    _vcomboboxFLAGS_WRAP                   = 0x00000004,   
    _vcomboboxFLAGS_AUTO_SORT              = 0x00000008,   
    _vcomboboxFLAGS_ACCEPT_BEHAVIOR_MASK   = 0x00000F00,   
    _vcomboboxFLAGS_SCROLL_BEHAVIOR_MASK   = 0x0000F000,   
    _vcomboboxFLAGS_SELECT_BEHAVIOR_MASK   = 0x000F0000    
};

enum {
    _vcomboboxSHIFT_ACCEPT_BEHAVIOR   = 8,  
    _vcomboboxSHIFT_SCROLL_BEHAVIOR   = 12, 
    _vcomboboxSHIFT_SELECT_BEHAVIOR   = 16  
};

/*
 * For vcomboboxPopdown
 */

enum {
    _vcomboboxPopdownINHERIT_EVENT             = 0x0001, 
    _vcomboboxPopdownDIALOG_LOCKED             = 0x0002, 
    _vcomboboxPopdownDIALOG_WILL_CLOSE         = 0x0004, 
    _vcomboboxPopdownDIALOG_DESTROY_WHEN_CLOSE = 0x0008  
};

/*****************************************************************************
 * PRIVATE TYPE DEFINITIONS
 ****************************************************************************/

/*
 * vcomboboxValue
 */

struct vcomboboxValue {            
    vobjectAttributed    object;
    short                flags;
    vcombobox           *combo;
    const vchar         *title;
    const void          *data;
};

#define vcomboboxValueCLASS(SUPER, VALUE) \
    vobjectATTRIBUTED_CLASS(SUPER, VALUE); \
    vclassMETHOD(vcomboboxValueDRAW, (VALUE *value, vrect *rect)); \
    vclassMETHOD(vcomboboxValueDRAW_WITH, \
		 (VALUE *value, vrect *rect, vdrawcontext *context)); \
    vclassMETHOD(vcomboboxValueGET_SIZE, (VALUE *value, int *width, int *height)); \
    vclassMETHOD(vcomboboxValueSET_COMBOBOX, (VALUE *value, vcombobox *combo)); \
    vclassMETHOD(vcomboboxValueSET_DATA, (VALUE *value, const void *data)); \
    vclassMETHOD(vcomboboxValueSET_TITLE_SCRIBED, (VALUE *value, vscribe *scribe))

struct vcomboboxValueClass {    
    vcomboboxValueCLASS(vcomboboxValueClass, vcomboboxValue);
};

/*
 * vcombobox
 */

struct vcombobox {
    vcontainer              container;
    int                     flags;
    vobjectList            *valueList;
    vcomboboxNoteProc       noteProc;
    int                     visibleValues;
    vcomboboxValue         *revert;
    vcomboboxValue         *current;
    vdialogItem	           *entrybox;
    vdialogItem            *choicebox;
    int                     maxValueWidth;
    int                     maxValueHeight;
};

#define vcomboboxCLASS(SUPER, COMBOBOX, VALUE, DI_NOTIFY, NOTIFY) \
    vcontainerCLASS(SUPER, COMBOBOX, DI_NOTIFY); \
    vclassMETHOD(vcomboboxACCEPT_VALUE, (COMBOBOX *combo, VALUE *value)); \
    vclassMETHOD(vcomboboxAPPEND_CHOICEBOX_VALUE, \
		 (COMBOBOX *combo, vdialogItem *choicebox, VALUE *value)); \
    vclassMETHOD(vcomboboxAPPEND_VALUE, (COMBOBOX *combo, VALUE *value)); \
    vclassMETHOD_RET(vcomboboxCOMPARE_VALUES, int, \
		     (COMBOBOX *combo, VALUE *value1, VALUE *value2)); \
    vclassMETHOD_RET(vcomboboxCREATE_CHOICEBOX, vdialogItem *, \
		     (COMBOBOX *combo)); \
    vclassMETHOD_RET(vcomboboxCREATE_ENTRYBOX, vdialogItem *, \
		     (COMBOBOX *combo)); \
    vclassMETHOD_RET(vcomboboxCREATE_VALUE, VALUE *, (COMBOBOX *combo)); \
    vclassMETHOD(vcomboboxDELETE_CHOICEBOX_VALUE_AT, \
		 (COMBOBOX *combo, vdialogItem *choicebox, int index)); \
    vclassMETHOD_RET(vcomboboxREMOVE_VALUE_AT, VALUE *, \
		     (COMBOBOX *combo, int index)); \
    vclassMETHOD(/* deprecated */ vcomboboxDELETE_VALUE_AT, \
		 (COMBOBOX *combo, int index)); \
    vclassMETHOD(vcomboboxDRAW_COMBOBOX_VALUE, \
		 (COMBOBOX *combo, VALUE *data, vrect *rect )); \
    vclassMETHOD(vcomboboxDRAW_COMBOBOX_VALUE_WITH, \
		 (COMBOBOX *combo, VALUE *data, vrect *rect, \
		  vdrawcontext *context )); \
    vclassMETHOD(vcomboboxFIND_VALUE_CLOSEST_INDEX, \
		 (COMBOBOX *combo, VALUE *value, int dir, \
		  int from, int *after, int *before)); \
    vclassMETHOD_RET(vcomboboxFIND_VALUE_EXACT_INDEX, int, \
		     (COMBOBOX *combo, VALUE *value, int dir, int from)); \
    vclassMETHOD_RET(vcomboboxFIND_VALUE_PARTIAL_INDEX, int, \
		     (COMBOBOX *combo, VALUE *value, int dir, int from)); \
    vclassMETHOD(vcomboboxGET_CHOICEBOX_RECT, \
		 (COMBOBOX *combo, vrect *rect)); \
    vclassMETHOD_RET(vcomboboxGET_CHOICEBOX_SELECTED_INDEX, int, \
		     (COMBOBOX *combo, vdialogItem *choicebox)); \
    vclassMETHOD(vcomboboxGET_CHOICEBOX_SIZE, \
		 (COMBOBOX *combo, int *width, int *height)); \
    vclassMETHOD(vcomboboxGET_ENTRYBOX_CHOICEBOX_GAP, \
		 (COMBOBOX *combo, int *gap)); \
    vclassMETHOD(vcomboboxGET_ENTRYBOX_RECT, \
		 (COMBOBOX *combo, vrect *rect)); \
    vclassMETHOD(vcomboboxGET_ENTRYBOX_SIZE, \
		 (COMBOBOX *combo, int *width, int *height)); \
    vclassMETHOD_RET(vcomboboxGET_ENTRYBOX_VALUE, VALUE *, \
		     (COMBOBOX *combo, vdialogItem *entrybox)); \
    vclassMETHOD_RET(vcomboboxGET_SELECTED_INDEX, int, (COMBOBOX *combo)); \
    vclassMETHOD_RET(vcomboboxGET_VALUE, VALUE *, (COMBOBOX *combo)); \
    vclassMETHOD(vcomboboxGET_COMBOBOX_VALUE_SIZE, \
		 (COMBOBOX *combo, VALUE *value, int *width, int *height)); \
    vclassMETHOD(vcomboboxGET_VALUE_MAX_SIZE, \
		 (COMBOBOX *combo, int *width, int *height)); \
    vclassMETHOD_RET(vcomboboxIS_VALUE_PARTIAL, int, \
		 (COMBOBOX *combo, VALUE *subValue, VALUE *superValue)); \
    vclassMETHOD(vcomboboxMOVE_CHOICEBOX_VALUE, \
		 (COMBOBOX *combo, vdialogItem *choicebox, int from, int to));\
    vclassMETHOD(vcomboboxMOVE_VALUE, (COMBOBOX *combo, int from, int to)); \
    vclassMETHOD(vcomboboxNOTIFY, \
		 (COMBOBOX *combo, vevent *event, int message)); \
    vclassMETHOD(vcomboboxRECALC, (COMBOBOX *combo)); \
    vclassMETHOD(vcomboboxSCROLL_CHOICEBOX_TO_INDEX, \
		 (COMBOBOX *combo, vdialogItem *choicebox, int index)); \
    vclassMETHOD(vcomboboxSCROLL_TO_INDEX, (COMBOBOX *combo, int index)); \
    vclassMETHOD(vcomboboxSCROLL_TO_VALUE, (COMBOBOX *combo, VALUE *value)); \
    vclassMETHOD(vcomboboxSELECT_CHOICEBOX_VALUE_AT, \
		 (COMBOBOX *combo, vdialogItem *choicebox, int index)); \
    vclassMETHOD(vcomboboxSELECT_VALUE, (COMBOBOX *combo, VALUE *value)); \
    vclassMETHOD(vcomboboxSELECT_VALUE_AT, (COMBOBOX *combo, int index)); \
    vclassMETHOD(vcomboboxSET_ACCEPT_BEHAVIOR, (COMBOBOX *combo, int flag)); \
    vclassMETHOD(vcomboboxSET_AUTO_SORT, (COMBOBOX *combo, int onOff)); \
    vclassMETHOD(vcomboboxSET_CHOICEBOX_VALUE_AT, \
		 (COMBOBOX *combo, vdialogItem *choicebox, \
		  VALUE *value, int index)); \
    vclassMETHOD(vcomboboxSET_CHOICEBOX_VISIBLE_VALUES, \
		 (COMBOBOX *combo, vdialogItem *choicebox, int values)); \
    vclassMETHOD(vcomboboxSET_CHOICEBOX_WRAP, \
		 (COMBOBOX *combo, vdialogItem *choicebox, int onOff)); \
    vclassMETHOD(vcomboboxSET_ENTRYBOX_MODIFYABLE, \
		 (COMBOBOX *combo, vdialogItem *entrybox, int onOff)); \
    vclassMETHOD(vcomboboxSET_ENTRYBOX_VALUE, \
		 (COMBOBOX *combo, vdialogItem *entrybox, VALUE *value)); \
    vclassMETHOD(vcomboboxSET_MODIFYABLE, (COMBOBOX *combo, int onOff)); \
    vclassMETHOD(vcomboboxSET_SCROLL_BEHAVIOR, \
		 (COMBOBOX *combo, int behavior)); \
    vclassMETHOD(vcomboboxSET_SELECT_BEHAVIOR, \
		 (COMBOBOX *combo, int behavior)); \
    vclassMETHOD(vcomboboxSET_WRAP, (COMBOBOX *combo, int onOff)); \
    vclassMETHOD(vcomboboxSET_NOTIFY, \
		 (COMBOBOX *combo, NOTIFY proc)); \
    vclassMETHOD(vcomboboxSET_VALUE, (COMBOBOX *combo, VALUE *value)); \
    vclassMETHOD(vcomboboxSET_VALUE_AT, \
		 (COMBOBOX *combo, VALUE *value, int index)); \
    vclassMETHOD(vcomboboxSET_VISIBLE_VALUES, (COMBOBOX *combo, int values)); \
    vclassMETHOD(vcomboboxSORT_VALUES, (COMBOBOX *combo))

struct vcomboboxClass {  
    vcomboboxCLASS(vcomboboxClass, vcombobox, vcomboboxValue, vdialogItemNoteProc, vcomboboxNoteProc);
};

/*
 * vcomboboxPopdown
 */

struct vcomboboxPopdown {
    vcombobox            combo;
    short                flags;
    vdialogItem         *button;
    vdialog             *dialog;
};

#define vcomboboxPopdownCLASS(SUPER, COMBOBOX, VALUE, DI_NOTIFY, NOTIFY) \
    vcomboboxCLASS(SUPER, COMBOBOX, VALUE, DI_NOTIFY, NOTIFY); \
    vclassMETHOD_RET(vcomboboxPopdownCREATE_BUTTON, vdialogItem*, \
		     (COMBOBOX *combo)); \
    vclassMETHOD(vcomboboxPopdownGET_BUTTON_RECT, \
		 (COMBOBOX *combo, vrect *rect)); \
    vclassMETHOD(vcomboboxPopdownGET_BUTTON_SIZE, \
		 (COMBOBOX *combo, int *width, int *height)); \
    vclassMETHOD(vcomboboxPopdownGET_ENTRYBOX_BUTTON_GAP, \
		 (COMBOBOX *combo, int *gap)); \
    vclassMETHOD(vcomboboxPopdownCLOSE_DIALOG, (COMBOBOX *combo)); \
    vclassMETHOD_RET(vcomboboxPopdownHIT_CONTENT, int, \
		     (COMBOBOX *combo, vdialogItem *choicebox, \
		      vevent *event)); \
    vclassMETHOD(vcomboboxPopdownOPEN_DIALOG, (COMBOBOX *combo)); \
    vclassMETHOD(vcomboboxPopdownPLACE_DIALOG, (COMBOBOX *combo)); \
    vclassMETHOD_RET(vcomboboxPopdownPOPDOWN_DIALOG, int, \
		     (COMBOBOX *combo, vevent *event)); \
    vclassMETHOD_RET(vcomboboxPopdownPOPUP_DIALOG, int, \
		     (COMBOBOX *combo, vevent *event)); \
    vclassMETHOD(vcomboboxPopdownRECALC_DIALOG, (COMBOBOX *combo))


struct vcomboboxPopdownClass {     
    vcomboboxPopdownCLASS(vcomboboxPopdownClass, vcomboboxPopdown, vcomboboxValue, vdialogItemNoteProc, vcomboboxPopdownNoteProc);

};


/*****************************************************************************
 * PRIVATE VALUE FUNCTION MACRO DEFINITIONS
 *****************************************************************************/

#define vcomboboxGetValueObject(c) \
    vportBASE_OBJECT((c), object)
#define vcomboboxGetValueClass(v) \
    ((vcomboboxValueClass *)vobjectGetClass(vcomboboxGetValueObject(v)))

/*
 * vobject level
 */

#define vcomboboxCloneValue(c) \
    ((vcomboboxValue *)vobjectClone(vcomboboxGetValueObject(c)))
#define vcomboboxCopyInitValue(c1, c2) \
    vobjectCopyInit(vcomboboxGetValueObject(c1), vcomboboxGetValueObject(c2))
#define vcomboboxCopyValue(c1, c2) \
    vobjectCopy(vcomboboxGetValueObject(c1), vcomboboxGetValueObject(c2))
#define vcomboboxCreateValueOfClass(clas) \
    ((vcomboboxValue *)vobjectCreateOfClass((vobjectClass*)(clas)))
#define vcomboboxCreateValue() \
    vcomboboxCreateValueOfClass(vcomboboxGetDefaultValueClass())
#define vcomboboxDestroyValue(c) \
    vobjectDestroy(vcomboboxGetValueObject(c))
#define vcomboboxGetValueTag(c) \
    vobjectGetTag(vcomboboxGetValueObject(c))
#define vcomboboxInitValueOfClass(c, clas) \
    vobjectInitOfClass(vcomboboxGetValueObject(c), (vobjectClass *)(clas))
#define vcomboboxInitValue(c) \
    vcomboboxInitValueOfClass((c), vcomboboxGetDefaultValueClass())
#define vcomboboxLoadInitValue(c, r) \
    vobjectLoadInit(vcomboboxGetValueObject(c), r)
#define vcomboboxLoadValue(r) \
    ((vcomboboxValue *)vobjectLoad(r))
#define vcomboboxSetValueTag(c, n) \
    vobjectSetTag(vcomboboxGetValueObject(c), n)
#define vcomboboxStoreValue(c, r) \
    vobjectStore(vcomboboxGetValueObject(c), r)

/*
 * vcomboboxValue level
 */

#define vcomboboxDrawValue(v, r) \
    vclassSend(vcomboboxGetValueClass(v), vcomboboxValueDRAW, (v, r))
#define vcomboboxDrawValueWith(v, r,c ) \
    vclassSend(vcomboboxGetValueClass(v), vcomboboxValueDRAW_WITH, (v, r, c))
#define vcomboboxGetValueCombobox(v) \
    ((v)->combo)
#define vcomboboxGetValueData(v) \
    ((v)->data)
#define vcomboboxGetValueSize(v, w, h) \
    vclassSend(vcomboboxGetValueClass(v), vcomboboxValueGET_SIZE, (v, w, h))
#define vcomboboxGetValueTitle(v) \
    ((v)->title)
#define vcomboboxSetValueCombobox(v, c) \
    vclassSend(vcomboboxGetValueClass(v), vcomboboxValueSET_COMBOBOX, (v, c))
#define vcomboboxSetValueData(v, d) \
    vclassSend(vcomboboxGetValueClass(v), vcomboboxValueSET_DATA, (v, d))
#define vcomboboxSetValueTitleScribed(v, s) \
    vclassSend(vcomboboxGetValueClass(v), vcomboboxValueSET_TITLE_SCRIBED, \
	       (v, s))
#define vcomboboxSetValueTitle(v, s) \
    vcomboboxSetValueTitleScribed(v, vcharScribe(s))

/*****************************************************************************
 * PRIVATE STANDARD FUNCTION MACRO DEFINITIONS
 *****************************************************************************/

#define vcomboboxGetContainer(c) \
    vportBASE_OBJECT((c), container)
#define vcomboboxGetItem(c) \
    vcontainerGetItem(vcomboboxGetContainer(c))
#define vcomboboxGetClass(c) \
    ((vcomboboxClass *)vdialogGetItemClass(vcomboboxGetItem(c)))

/*
 * vobject level
 */
 
#define vcomboboxClone(c) \
    ((vcombobox *)vdialogCloneItem(vcomboboxGetItem(c)))
#define vcomboboxCopy(c1, c2) \
    vdialogCopyItem(vcomboboxGetItem(c1), vcomboboxGetItem(c2))
#define vcomboboxCopyInit(c1, c2) \
    vdialogCopyInitItem(vcomboboxGetItem(c1), vcomboboxGetItem(c2))
#define vcomboboxCreateOfClass(clas) \
    ((vcombobox *)vdialogCreateItemOfClass((vdialogItemClass *)(clas)))
#define vcomboboxCreate() \
    vcomboboxCreateOfClass(vcomboboxGetDefaultClass())
#define vcomboboxDestroy(c) \
    vdialogDestroyItem(vcomboboxGetItem(c))
#define vcomboboxInitOfClass(c, clas) \
    vdialogInitItemOfClass(vcomboboxGetItem(c), (vdialogItemClass *)(clas))
#define vcomboboxInit(c) \
    vcomboboxInitOfClass((c), vcomboboxGetDefaultClass())
#define vcomboboxLoad(r) \
    ((vcombobox *)vdialogLoadItem(r))
#define vcomboboxLoadInit(c, r) \
    vdialogLoadInitItem(vcomboboxGetItem(c), r)
#define vcomboboxStore(c, r) \
    vdialogStoreItem(vcomboboxGetItem(c), r)

/*
 * vdialogItem level
 */

#define vcomboboxGetData(c) \
    vdialogGetItemData(vcomboboxGetItem(c))
#define vcomboboxGetTitle(c) \
    vdialogGetItemTitle(vcomboboxGetItem(c))
#define vcomboboxSetData(c, d) \
    vdialogSetItemData(vcomboboxGetItem(c), (d))
#define vcomboboxSetTitleScribed(c, t) \
    vdialogSetItemTitleScribed(vcomboboxGetItem(c), t)
#define vcomboboxSetTitle(c, t) \
    vdialogSetItemTitle(vcomboboxGetItem(c), t)

/*
 * vcontainer level
 */

/*
 * vcombobox level
 */

#define vcomboboxAcceptValue(c, v) \
    vclassSend(vcomboboxGetClass(c), vcomboboxACCEPT_VALUE, (c, v));
#define vcomboboxAppendValue(c, v) \
    vclassSend(vcomboboxGetClass(c), vcomboboxAPPEND_VALUE, (c, v));
#define vcomboboxBlockEntrybox(c) \
    ((c)->flags |= _vcomboboxFLAGS_BLOCKED)
#define vcomboboxCompareValues(c, v1, v2) \
    vclassSend(vcomboboxGetClass(c), vcomboboxCOMPARE_VALUES, (c, v1, v2))
#define vcomboboxRemoveValueAt(c, i) \
    vclassSend(vcomboboxGetClass(c), vcomboboxREMOVE_VALUE_AT, (c, i))
#define vcomboboxDeleteValueAt(c, i) \
    ((void) vcomboboxRemoveValueAt(c, i))
#define vcomboboxDrawComboboxValue(c, v, r) \
    vclassSend(vcomboboxGetClass(c), vcomboboxDRAW_COMBOBOX_VALUE, (c, v, r))
#define vcomboboxDrawComboboxValueWith(c, v, r, x) \
    vclassSend(vcomboboxGetClass(c), vcomboboxDRAW_COMBOBOX_VALUE_WITH, \
	       (c, v, r,x))
#define vcomboboxFindValue(c, t) \
    ((vcomboboxValue *)vobjectFindList((c)->valueList, t))
#define vcomboboxFindValueClosestIndex(c, v, d, f, a, b) \
    vclassSend(vcomboboxGetClass(c), vcomboboxFIND_VALUE_CLOSEST_INDEX, \
	       (c, v, d, f, a, b))
#define vcomboboxFindValueExactIndex(c, v, d, f) \
    vclassSend(vcomboboxGetClass(c), vcomboboxFIND_VALUE_EXACT_INDEX, \
	       (c, v, d, f))
#define vcomboboxFindValuePartialIndex(c, v, d, f) \
    vclassSend(vcomboboxGetClass(c), vcomboboxFIND_VALUE_PARTIAL_INDEX, \
	       (c, v, d, f))
#define vcomboboxGetAcceptBehavior(c) \
    (((c)->flags & _vcomboboxFLAGS_ACCEPT_BEHAVIOR_MASK) \
       >> _vcomboboxSHIFT_ACCEPT_BEHAVIOR)
#define vcomboboxGetChoicebox(c) \
    ((c)->choicebox)
#define vcomboboxGetChoiceboxRect(c, r) \
    vclassSend(vcomboboxGetClass(c), vcomboboxGET_CHOICEBOX_RECT, (c, r))
#define vcomboboxGetChoiceboxSize(c, w, h) \
    vclassSend(vcomboboxGetClass(c), vcomboboxGET_CHOICEBOX_SIZE, (c, w, h))
#define vcomboboxGetComboboxValueSize(c, v, w, h) \
    vclassSend(vcomboboxGetClass(c), vcomboboxGET_COMBOBOX_VALUE_SIZE, (c, v, w, h))
#define vcomboboxGetEntrybox(c) \
    ((c)->entrybox)
#define vcomboboxGetEntryboxChoiceboxGap(c, g) \
    vclassSend(vcomboboxGetClass(c), vcomboboxGET_ENTRYBOX_CHOICEBOX_GAP, \
	       (c, g))
#define vcomboboxGetEntryboxRect(c, r) \
    vclassSend(vcomboboxGetClass(c), vcomboboxGET_ENTRYBOX_RECT, (c, r))
#define vcomboboxGetEntryboxSize(c, w, h) \
    vclassSend(vcomboboxGetClass(c), vcomboboxGET_ENTRYBOX_SIZE, (c, w, h))
#define vcomboboxGetScrollBehavior(c) \
    (((c)->flags & _vcomboboxFLAGS_SCROLL_BEHAVIOR_MASK) \
       >> _vcomboboxSHIFT_SCROLL_BEHAVIOR)
#define vcomboboxGetSelectBehavior(c) \
    (((c)->flags & _vcomboboxFLAGS_SELECT_BEHAVIOR_MASK) \
       >> _vcomboboxSHIFT_SELECT_BEHAVIOR)
#define vcomboboxGetNotify(c) \
    ((c)->noteProc)
#define vcomboboxGetSelectedIndex(c) \
    vclassSend(vcomboboxGetClass(c), vcomboboxGET_SELECTED_INDEX, (c))
#define vcomboboxGetValue(c) \
    vclassSend(vcomboboxGetClass(c), vcomboboxGET_VALUE, (c))
#define vcomboboxGetValueAt(c, i) \
    ((vcomboboxValue *)vobjectGetListAt((c)->valueList, i))
#define vcomboboxGetValueCount(c) \
    vobjectGetListCount((c)->valueList)
#define vcomboboxGetValueIndex(c, v) \
    vobjectGetListIndex((c)->valueList, vcomboboxGetValueObject(v))
#define vcomboboxGetValueMaxSize(c, w, h) \
    vclassSend(vcomboboxGetClass(c), vcomboboxGET_VALUE_MAX_SIZE, (c, w, h))
#define vcomboboxGetVisibleValues(c) \
    ((c)->visibleValues)
#define vcomboboxIsAutoSort(c) \
    ((c)->flags & _vcomboboxFLAGS_AUTO_SORT)
#define vcomboboxIsEntryboxBlocked(c) \
    ((c)->flags & _vcomboboxFLAGS_BLOCKED)
#define vcomboboxIsModifyable(c) \
    ((c)->flags & _vcomboboxFLAGS_MODIFYABLE)
#define vcomboboxIsValuePartial(c, v1, v2) \
    vclassSend(vcomboboxGetClass(c), vcomboboxIS_VALUE_PARTIAL, (c, v1, v2))
#define vcomboboxIsWrap(c) \
    ((c)->flags & _vcomboboxFLAGS_WRAP)
#define vcomboboxMoveValue(c, f, t) \
    vclassSend(vcomboboxGetClass(c), vcomboboxMOVE_VALUE, (c, f, t))
#define vcomboboxNotify(c, e, m) \
     vclassSend(vcomboboxGetClass(c), vcomboboxNOTIFY, (c, e, m))
#define vcomboboxRecalc(c) \
    vclassSend(vcomboboxGetClass(c), vcomboboxRECALC, (c))
#define vcomboboxScrollToIndex(c, i) \
    vclassSend(vcomboboxGetClass(c), vcomboboxSCROLL_TO_INDEX, (c, i))
#define vcomboboxScrollToValue(c, v) \
    vclassSend(vcomboboxGetClass(c), vcomboboxSCROLL_TO_VALUE, (c, v))
#define vcomboboxSelectValue(c, v) \
    vclassSend(vcomboboxGetClass(c), vcomboboxSELECT_VALUE, (c, v))
#define vcomboboxSelectValueAt(c, i) \
    vclassSend(vcomboboxGetClass(c), vcomboboxSELECT_VALUE_AT, (c, i))
#define vcomboboxSetAcceptBehavior(c, b) \
    vclassSend(vcomboboxGetClass(c), vcomboboxSET_ACCEPT_BEHAVIOR, (c, b))
#define vcomboboxSetAutoSort(c, f) \
    vclassSend(vcomboboxGetClass(c), vcomboboxSET_AUTO_SORT, (c, f))
#define vcomboboxSetModifyable(c, f) \
    vclassSend(vcomboboxGetClass(c), vcomboboxSET_MODIFYABLE, (c, f))
#define vcomboboxSetScrollBehavior(c, b) \
    vclassSend(vcomboboxGetClass(c), vcomboboxSET_SCROLL_BEHAVIOR, (c, b))
#define vcomboboxSetSelectBehavior(c, b) \
    vclassSend(vcomboboxGetClass(c), vcomboboxSET_SELECT_BEHAVIOR, (c, b))
#define vcomboboxSetNotify(c, n) \
    vclassSend(vcomboboxGetClass(c), vcomboboxSET_NOTIFY, (c, n))
#define vcomboboxSetValue(c, v) \
    vclassSend(vcomboboxGetClass(c), vcomboboxSET_VALUE, (c, v))
#define vcomboboxSetValueAt(c, v, i) \
    vclassSend(vcomboboxGetClass(c), vcomboboxSET_VALUE_AT, (c, v, i))
#define vcomboboxSetVisibleValues(c, r) \
    vclassSend(vcomboboxGetClass(c), vcomboboxSET_VISIBLE_VALUES, (c, r))
#define vcomboboxSetWrap(c, f) \
    vclassSend(vcomboboxGetClass(c), vcomboboxSET_WRAP, (c, f))
#define vcomboboxSortValues(c) \
    vclassSend(vcomboboxGetClass(c), vcomboboxSORT_VALUES, (c))
#define vcomboboxUnblockEntrybox(c) \
    ((c)->flags &= ~_vcomboboxFLAGS_BLOCKED)

/*****************************************************************************
 * PRIVATE POPDOWN FUNCTION MACRO DEFINITIONS
 *****************************************************************************/

#define vcomboboxGetPopdownCombobox(c) \
    vportBASE_OBJECT((c), combo)
#define vcomboboxGetPopdownContainer(c) \
    vcomboboxGetContainer(vcomboboxGetPopdownCombobox(c))
#define vcomboboxGetPopdownItem(c) \
    vcomboboxGetItem(vcomboboxGetPopdownCombobox(c))
#define vcomboboxGetPopdownClass(c) \
    ((vcomboboxPopdownClass *)vdialogGetItemClass(vcomboboxGetPopdownItem(c)))

/*
 * vobject level
 */

#define vcomboboxClonePopdown(c) \
    ((vcomboboxPopdown *)vdialogCloneItem(vcomboboxGetPopdownItem(c)))
#define vcomboboxCopyInitPopdown(c1, c2) \
    vdialogCopyInitItem(vcomboboxGetPopdownItem(c1), \
			vcomboboxGetPopdownItem(c2))
#define vcomboboxCopyPopdown(c1, c2) \
    vdialogCopyItem(vcomboboxGetPopdownItem(c1), \
		    vcomboboxGetPopdownItem(c2))
#define vcomboboxCreatePopdownOfClass(clas) \
    ((vcomboboxPopdown *)vdialogCreateItemOfClass((vdialogItemClass *)(clas)))
#define vcomboboxCreatePopdown() \
    vcomboboxCreatePopdownOfClass(vcomboboxGetDefaultPopdownClass())
#define vcomboboxDestroyPopdown(c) \
    vdialogDestroyItem(vcomboboxGetPopdownItem(c))
#define vcomboboxInitPopdownOfClass(c, clas) \
    vdialogInitItemOfClass(vcomboboxGetPopdownItem(c), \
			   (vdialogItemClass *)(clas))
#define vcomboboxInitPopdown(c) \
    vcomboboxInitPopdownOfClass((c), vcomboboxGetDefaultPopdownClass())
#define vcomboboxLoadInitPopdown(c, r) \
    vdialogLoadInitItem(vcomboboxGetPopdownItem(c), r)
#define vcomboboxLoadPopdown(r) \
    ((vcomboboxPopdown *)vdialogLoadItem(r))
#define vcomboboxStorePopdown(c, r) \
    vdialogStoreItem(vcomboboxGetPopdownItem(c), r)

/*
 * vdialogItem level 
 */

#define vcomboboxGetPopdownData(c) \
    vdialogGetItemData(vcomboboxGetPopdownItem(c))
#define vcomboboxGetPopdownTitle(c) \
    vdialogGetItemTitle(vcomboboxGetPopdownItem(c))
#define vcomboboxSetPopdownData(c, d) \
    vdialogSetItemData(vcomboboxGetPopdownItem(c), (d))
#define vcomboboxSetPopdownTitleScribed(c, t) \
    vdialogSetItemTitleScribed(vcomboboxGetPopdownItem(c), t)
#define vcomboboxSetPopdownTitle(c, t) \
    vdialogSetItemTitle(vcomboboxGetPopdownItem(c), t)

/*
 * vcontainer level
 */

/*
 * vcombobox level
 */

#define vcomboboxAcceptPopdownValue(c, v) \
    vcomboboxAcceptValue(vcomboboxGetPopdownCombobox(c), v)
#define vcomboboxAppendPopdownValue(c, v) \
    vcomboboxAppendValue(vcomboboxGetPopdownCombobox(c), v)
#define vcomboboxBlockPopdownEntrybox(c) \
    vcomboboxBlockEntrybox(vcomboboxGetPopdownCombobox(c))
#define vcomboboxComparePopdownValues(c, v1, v2) \
    vcomboboxCompareValues(vcomboboxGetPopdownCombobox(c), v1, v2)
#define vcomboboxRemovePopdownValue(c, v) \
    vcomboboxRemoveValue(vcomboboxGetPopdownCombobox(c), v)
#define vcomboboxDeletePopdownValue(c, v) \
    vcomboboxDeleteValue(vcomboboxGetPopdownCombobox(c), v)
#define vcomboboxRemovePopdownValueAt(c, i) \
    vcomboboxRemoveValueAt(vcomboboxGetPopdownCombobox(c), i)
#define vcomboboxDeletePopdownValueAt(c, i) \
    vcomboboxDeleteValueAt(vcomboboxGetPopdownCombobox(c), i)
#define vcomboboxDrawPopdownValue(c, v, r) \
    vcomboboxDrawComboboxValue(vcomboboxGetPopdownCombobox(c), v, r)
#define vcomboboxDrawPopdownValueWith(c, v, r, x) \
    vcomboboxDrawComboboxValueWith(vcomboboxGetPopdownCombobox(c), v, r, x)
#define vcomboboxFindPopdownValue(c, v) \
    vcomboboxFindValue(vcomboboxGetPopdownCombobox(c), v)
#define vcomboboxFindPopdownValueClosestIndex(c, v, d, f, a, b) \
    vcomboboxFindValueClosestIndex(vcomboboxGetPopdownCombobox(c), \
				   v, d, f, a, b)
#define vcomboboxFindPopdownValueExactIndex(c, v, d, f) \
    vcomboboxFindValueExactIndex(vcomboboxGetPopdownCombobox(c), v, d, f)
#define vcomboboxFindPopdownValuePartialIndex(c, v, d, f) \
    vcomboboxFindValuePartialIndex(vcomboboxGetPopdownCombobox(c), v, d, f)
#define vcomboboxGetPopdownAcceptBehavior(c) \
    vcomboboxGetAcceptBehavior(vcomboboxGetPopdownCombobox(c))
#define vcomboboxGetPopdownChoicebox(c) \
    vcomboboxGetChoicebox(vcomboboxGetPopdownCombobox(c))
#define vcomboboxGetPopdownChoiceboxRect(c, r) \
    vcomboboxGetChoiceboxRect(vcomboboxGetPopdownCombobox(c), r)
#define vcomboboxGetPopdownChoiceboxSize(c, w, h) \
    vcomboboxGetChoiceboxSize(vcomboboxGetPopdownCombobox(c), w, h)
#define vcomboboxGetPopdownEntrybox(c) \
    vcomboboxGetEntrybox(vcomboboxGetPopdownCombobox(c))
#define vcomboboxGetPopdownEntryboxChoiceboxGap(c, g) \
    vcomboboxGetEntryboxChoiceboxGap(vcomboboxGetPopdownCombobox(c), g)
#define vcomboboxGetPopdownEntryboxRect(c, r) \
    vcomboboxGetEntryboxRect(vcomboboxGetPopdownCombobox(c), r)
#define vcomboboxGetPopdownEntryboxSize(c, w, h) \
    vcomboboxGetEntryboxSize(vcomboboxGetPopdownCombobox(c), w, h)
#define vcomboboxGetPopdownSelectBehavior(c) \
    vcomboboxGetSelectBehavior(vcomboboxGetPopdownCombobox(c))
#define vcomboboxGetPopdownScrollBehavior(c) \
    vcomboboxGetScrollBehavior(vcomboboxGetPopdownCombobox(c))
#define vcomboboxGetPopdownNotify(c) \
    ((vcomboboxPopdownNoteProc) \
     vcomboboxGetNotify(vcomboboxGetPopdownCombobox(c)))
#define vcomboboxGetPopdownSelectedIndex(c) \
    vcomboboxGetSelectedIndex(vcomboboxGetPopdownCombobox(c))
#define vcomboboxGetPopdownValue(c) \
    vcomboboxGetValue(vcomboboxGetPopdownCombobox(c))
#define vcomboboxGetPopdownValueAt(c, i) \
    vcomboboxGetValueAt(vcomboboxGetPopdownCombobox(c), i)
#define vcomboboxGetPopdownValueCount(c) \
    vcomboboxGetValueCount(vcomboboxGetPopdownCombobox(c))
#define vcomboboxGetPopdownValueIndex(c, v) \
    vcomboboxGetValueIndex(vcomboboxGetPopdownCombobox(c), v)
#define vcomboboxGetPopdownValueMaxSize(c, w, h) \
    vcomboboxGetValueMaxSize(vcomboboxGetPopdownCombobox(c), w, h)
#define vcomboboxGetPopdownValueSize(c, v, w, h) \
    vcomboboxGetComboboxValueSize(vcomboboxGetPopdownCombobox(c), v, w, h)
#define vcomboboxGetPopdownVisibleValues(c) \
    vcomboboxGetVisibleValues(vcomboboxGetPopdownCombobox(c))
#define vcomboboxIsPopdownAutoSort(c) \
    vcomboboxIsAutoSort(vcomboboxGetPopdownCombobox(c))
#define vcomboboxIsPopdownEntryboxBlocked(c) \
    vcomboboxIsEntryboxBlocked(vcomboboxGetPopdownCombobox(c))
#define vcomboboxIsPopdownModifyable(c) \
    vcomboboxIsModifyable(vcomboboxGetPopdownCombobox(c))
#define vcomboboxIsPopdownValuePartial(c, v1, v2) \
    vcomboboxIsValuePartial(vcomboboxGetPopdownCombobox(c), v1, v2)
#define vcomboboxIsPopdownWrap(c) \
    vcomboboxIsWrap(vcomboboxGetPopdownCombobox(c))
#define vcomboboxMovePopdownValue(c, f, t) \
    vcomboboxMoveValue(vcomboboxGetPopdownCombobox(c), f, t)
#define vcomboboxNotifyPopdown(c, e, m) \
     vcomboboxNotify(vcomboboxGetPopdownCombobox(c), e, m)
#define vcomboboxRecalcPopdown(c) \
    vcomboboxRecalc(vcomboboxGetPopdownCombobox(c))
#define vcomboboxScrollPopdownToIndex(c, i) \
    vcomboboxScrollToIndex(vcomboboxGetPopdownCombobox(c), i)
#define vcomboboxScrollPopdownToValue(c, v) \
    vcomboboxScrollToValue(vcomboboxGetPopdownCombobox(c), v)
#define vcomboboxSelectPopdownValue(c, v) \
    vcomboboxSelectValue(vcomboboxGetPopdownCombobox(c), v)
#define vcomboboxSelectPopdownValueAt(c, i) \
    vcomboboxSelectValueAt(vcomboboxGetPopdownCombobox(c), i)
#define vcomboboxSetPopdownAcceptBehavior(c, b) \
    vcomboboxSetAcceptBehavior(vcomboboxGetPopdownCombobox(c), b)
#define vcomboboxSetPopdownAutoSort(c, f) \
    vcomboboxSetAutoSort(vcomboboxGetPopdownCombobox(c), f)
#define vcomboboxSetPopdownModifyable(c, f) \
    vcomboboxSetModifyable(vcomboboxGetPopdownCombobox(c), f)
#define vcomboboxSetPopdownScrollBehavior(c, b) \
    vcomboboxSetScrollBehavior(vcomboboxGetPopdownCombobox(c), b)
#define vcomboboxSetPopdownSelectBehavior(c, b) \
    vcomboboxSetSelectBehavior(vcomboboxGetPopdownCombobox(c), b)
#define vcomboboxSetPopdownNotify(c, n) \
    vcomboboxSetNotify(vcomboboxGetPopdownCombobox(c), \
		       (vcomboboxNoteProc)n)
#define vcomboboxSetPopdownValue(c, v) \
    vcomboboxSetValue(vcomboboxGetPopdownCombobox(c), v)
#define vcomboboxSetPopdownValueAt(c, v, i) \
    vcomboboxSetValueAt(vcomboboxGetPopdownCombobox(c), v, i)
#define vcomboboxSetPopdownVisibleValues(c, r) \
    vcomboboxSetVisibleValues(vcomboboxGetPopdownCombobox(c), r)
#define vcomboboxSetPopdownWrap(c, f) \
    vcomboboxSetWrap(vcomboboxGetPopdownCombobox(c), f)
#define vcomboboxSortPopdownValues(c) \
    vcomboboxSortValues(vcomboboxGetPopdownCombobox(c))
#define vcomboboxUnblockPopdownEntrybox(c) \
    vcomboboxUnblockEntrybox(vcomboboxGetPopdownCombobox(c))

/*
 * vcomboboxPopdown level
 */

#define vcomboboxClosePopdownDialog(c) \
    vclassSend(vcomboboxGetPopdownClass(c), vcomboboxPopdownCLOSE_DIALOG, (c))
#define vcomboboxGetPopdownButton(c) \
    ((c)->button)
#define vcomboboxGetPopdownButtonRect(c, r) \
    vclassSend(vcomboboxGetPopdownClass(c), vcomboboxPopdownGET_BUTTON_RECT, \
	       (c, r))
#define vcomboboxGetPopdownButtonSize(c, w, h) \
    vclassSend(vcomboboxGetPopdownClass(c), vcomboboxPopdownGET_BUTTON_SIZE, \
	       (c, w, h))
#define vcomboboxGetPopdownDialog(c) \
    ((c)->dialog)
#define vcomboboxGetPopdownEntryboxButtonGap(c, g) \
    vclassSend(vcomboboxGetPopdownClass(c), \
	       vcomboboxPopdownGET_ENTRYBOX_BUTTON_GAP, (c, g))
#define vcomboboxOpenPopdownDialog(c) \
    vclassSend(vcomboboxGetPopdownClass(c), vcomboboxPopdownOPEN_DIALOG, (c))
#define vcomboboxPlacePopdownDialog(c) \
    vclassSend(vcomboboxGetPopdownClass(c), vcomboboxPopdownPLACE_DIALOG, (c))
#define vcomboboxPopdownPopdownDialog(c, e) \
    vclassSend(vcomboboxGetPopdownClass(c), vcomboboxPopdownPOPDOWN_DIALOG, \
	       (c, e))
#define vcomboboxPopupPopdownDialog(c, e) \
    vclassSend(vcomboboxGetPopdownClass(c), vcomboboxPopdownPOPUP_DIALOG, \
	       (c, e))
#define vcomboboxRecalcPopdownDialog(c) \
    vclassSend(vcomboboxGetPopdownClass(c), vcomboboxPopdownRECALC_DIALOG, (c))

vportEND_CPLUSPLUS_EXTERN_C

#endif /* vcomboboxINCLUDED */




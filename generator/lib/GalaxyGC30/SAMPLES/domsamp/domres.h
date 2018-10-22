#ifndef domresINCLUDED
#define domresINCLUDED

#ifndef vnameINCLUDED
#include <vname.h>
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * * * * * * * * * CONSTANTS AND MACRO DEFINITIONS * * * * * * * * * *
 */

enum {
	_domres_YSpacing,
	_domres_yCoord,
	_domres_Rat,
	_domres_EditMenu,
	_domres_Galaxy_Logo,
	_domres_scaleX,
	_domres_scaleY,
	_domres_Align_Horizontal_Centers,
	_domres_EditGrid,
	_domres_Microdraw,
	_domres_Select_All,
	_domres_Images,
	_domres_Align_Right,
	_domres_myDomainView,
	_domres_Blue_Saturn,
	_domres_TrackSelect,
	_domres_Earth,
	_domres_Preditor,
	_domres_selColorToggle,
	_domres_SingleSelection,
	_domres_Gray_s_Spaceship,
	_domres_Moon_with_Red_Circle,
	_domres_Rocket_with_Green_Planet,
	_domres_Group,
	_domres_Align_Top,
	_domres_SnapAlignLimit,
	_domres_YSkew,
	_domres_Align_To_Grid,
	_domres_Emacs,
	_domres_List_Demo,
	_domres_ToggleTopLeft,
	_domres_EditMatrix,
	_domres_OutlineTwo,
	_domres_OutlineNone,
	_domres_Menu_Bar,
	_domres_AddObjects,
	_domres_Round_purple_Galaxy,
	_domres_Red_Galaxy,
	_domres_objectCount,
	_domres_xCoord,
	_domres_StopProcess,
	_domres_mainDialog,
	_domres_coordContainer,
	_domres_TrackAutoScroll,
	_domres_PrintDomain,
	_domres_OutlineAll,
	_domres_LiveSelection,
	_domres_SmallBlue_Galaxy,
	_domres_rotate,
	_domres_XSpacing,
	_domres_HorizontalBar,
	_domres_prefsConfirm,
	_domres_toggleRandom,
	_domres_ScrollToSelected,
	_domres_Orange_Saturn,
	_domres_Gray_s_Spaceman,
	_domres_MakeUnselectable,
	_domres_SnapOff,
	_domres_DomainViewMenu,
	_domres_ToggleLong,
	_domres_Edge,
	_domres_Green_Galaxy,
	_domres_OffscreenDrawing,
	_domres_objectSizes,
	_domres_X,
	_domres_Wizard,
	_domres_Y,
	_domres_Satellite_with_Green_Moon,
	_domres_objectType,
	_domres_XSkew,
	_domres_Align_Bottom,
	_domres_fontToggle,
	_domres_SelectEnclosed,
	_domres_SnapAlignOne,
	_domres_DomainMenu,
	_domres_SnapNoAlign,
	_domres_Galaxy_Demo,
	_domres_World,
	_domres_OutlineLimitRect,
	_domres_ExternalDrag,
	_domres_Blue_Moon,
	_domres_translateX,
	_domres_translateY,
	_domres_AutoScrollDrag,
	_domres_gridConfirm,
	_domres_RemoveObjects,
	_domres_ViewCoords,
	_domres_Purple_Moon,
	_domres_Bands,
	_domres_bgColorButton,
	_domres_coordSysWindow,
	_domres_TrackDrag,
	_domres_GrabbingHand,
	_domres_Orange_Spaceman,
	_domres_DragProhibited,
	_domres_Moon,
	_domres_Cancel,
	_domres_DisconnectObjects,
	_domres_Detached,
	_domres_LEX,
	_domres_ConnectObjects,
	_domres_SmartScrollbars,
	_domres_Schwapp,
	_domres_ToggleVirtual,
	_domres_selColorButton,
	_domres_fontButton,
	_domres_Align_Left,
	_domres_FileMenu,
	_domres_addItemsConfirm,
	_domres_ShowAllObjects,
	_domres_Open,
	_domres_Save,
	_domres_Bomb,
	_domres_DragOnUnselectables,
	_domres_matrixConfirm,
	_domres_bgColorToggle,
	_domres_DomainInstalled,
	_domres_jjw_vs__Barney,
	_domres_ObjectsMenu,
	_domres_NormalDrag,
	_domres_Preferences,
	_domres_All_Kids_Love_Log,
	_domres_Align_Vertical_Centers,
	_domres_VerticalBar,
	_domres_ShowGrid,
	_domres_HideObjects,
	_domres_Ok,
	_domres_Align_To_Objects,
	_domres_EOMS,
	_domres_FunStuffMenu,
	_domres_Conductor,
	_domresCOUNT
};


#define domres_YSpacing		 _domresPredefs[_domres_YSpacing]
#define domres_yCoord		 _domresPredefs[_domres_yCoord]
#define domres_Rat		 _domresPredefs[_domres_Rat]
#define domres_EditMenu		 _domresPredefs[_domres_EditMenu]
#define domres_Galaxy_Logo		 _domresPredefs[_domres_Galaxy_Logo]
#define domres_scaleX		 _domresPredefs[_domres_scaleX]
#define domres_scaleY		 _domresPredefs[_domres_scaleY]
#define domres_Align_Horizontal_Centers		 _domresPredefs[_domres_Align_Horizontal_Centers]
#define domres_EditGrid		 _domresPredefs[_domres_EditGrid]
#define domres_Microdraw		 _domresPredefs[_domres_Microdraw]
#define domres_Select_All		 _domresPredefs[_domres_Select_All]
#define domres_Images		 _domresPredefs[_domres_Images]
#define domres_Align_Right		 _domresPredefs[_domres_Align_Right]
#define domres_myDomainView		 _domresPredefs[_domres_myDomainView]
#define domres_Blue_Saturn		 _domresPredefs[_domres_Blue_Saturn]
#define domres_TrackSelect		 _domresPredefs[_domres_TrackSelect]
#define domres_Earth		 _domresPredefs[_domres_Earth]
#define domres_Preditor		 _domresPredefs[_domres_Preditor]
#define domres_selColorToggle		 _domresPredefs[_domres_selColorToggle]
#define domres_SingleSelection		 _domresPredefs[_domres_SingleSelection]
#define domres_Gray_s_Spaceship		 _domresPredefs[_domres_Gray_s_Spaceship]
#define domres_Moon_with_Red_Circle		 _domresPredefs[_domres_Moon_with_Red_Circle]
#define domres_Rocket_with_Green_Planet		 _domresPredefs[_domres_Rocket_with_Green_Planet]
#define domres_Group		 _domresPredefs[_domres_Group]
#define domres_Align_Top		 _domresPredefs[_domres_Align_Top]
#define domres_SnapAlignLimit		 _domresPredefs[_domres_SnapAlignLimit]
#define domres_YSkew		 _domresPredefs[_domres_YSkew]
#define domres_Align_To_Grid		 _domresPredefs[_domres_Align_To_Grid]
#define domres_Emacs		 _domresPredefs[_domres_Emacs]
#define domres_List_Demo		 _domresPredefs[_domres_List_Demo]
#define domres_ToggleTopLeft		 _domresPredefs[_domres_ToggleTopLeft]
#define domres_EditMatrix		 _domresPredefs[_domres_EditMatrix]
#define domres_OutlineTwo		 _domresPredefs[_domres_OutlineTwo]
#define domres_OutlineNone		 _domresPredefs[_domres_OutlineNone]
#define domres_Menu_Bar		 _domresPredefs[_domres_Menu_Bar]
#define domres_AddObjects		 _domresPredefs[_domres_AddObjects]
#define domres_Round_purple_Galaxy		 _domresPredefs[_domres_Round_purple_Galaxy]
#define domres_Red_Galaxy		 _domresPredefs[_domres_Red_Galaxy]
#define domres_objectCount		 _domresPredefs[_domres_objectCount]
#define domres_xCoord		 _domresPredefs[_domres_xCoord]
#define domres_StopProcess		 _domresPredefs[_domres_StopProcess]
#define domres_mainDialog		 _domresPredefs[_domres_mainDialog]
#define domres_coordContainer		 _domresPredefs[_domres_coordContainer]
#define domres_TrackAutoScroll		 _domresPredefs[_domres_TrackAutoScroll]
#define domres_PrintDomain		 _domresPredefs[_domres_PrintDomain]
#define domres_OutlineAll		 _domresPredefs[_domres_OutlineAll]
#define domres_LiveSelection		 _domresPredefs[_domres_LiveSelection]
#define domres_SmallBlue_Galaxy		 _domresPredefs[_domres_SmallBlue_Galaxy]
#define domres_rotate		 _domresPredefs[_domres_rotate]
#define domres_XSpacing		 _domresPredefs[_domres_XSpacing]
#define domres_HorizontalBar		 _domresPredefs[_domres_HorizontalBar]
#define domres_prefsConfirm		 _domresPredefs[_domres_prefsConfirm]
#define domres_toggleRandom		 _domresPredefs[_domres_toggleRandom]
#define domres_ScrollToSelected		 _domresPredefs[_domres_ScrollToSelected]
#define domres_Orange_Saturn		 _domresPredefs[_domres_Orange_Saturn]
#define domres_Gray_s_Spaceman		 _domresPredefs[_domres_Gray_s_Spaceman]
#define domres_MakeUnselectable		 _domresPredefs[_domres_MakeUnselectable]
#define domres_SnapOff		 _domresPredefs[_domres_SnapOff]
#define domres_DomainViewMenu		 _domresPredefs[_domres_DomainViewMenu]
#define domres_ToggleLong		 _domresPredefs[_domres_ToggleLong]
#define domres_Edge		 _domresPredefs[_domres_Edge]
#define domres_Green_Galaxy		 _domresPredefs[_domres_Green_Galaxy]
#define domres_OffscreenDrawing		 _domresPredefs[_domres_OffscreenDrawing]
#define domres_objectSizes		 _domresPredefs[_domres_objectSizes]
#define domres_X		 _domresPredefs[_domres_X]
#define domres_Wizard		 _domresPredefs[_domres_Wizard]
#define domres_Y		 _domresPredefs[_domres_Y]
#define domres_Satellite_with_Green_Moon		 _domresPredefs[_domres_Satellite_with_Green_Moon]
#define domres_objectType		 _domresPredefs[_domres_objectType]
#define domres_XSkew		 _domresPredefs[_domres_XSkew]
#define domres_Align_Bottom		 _domresPredefs[_domres_Align_Bottom]
#define domres_fontToggle		 _domresPredefs[_domres_fontToggle]
#define domres_SelectEnclosed		 _domresPredefs[_domres_SelectEnclosed]
#define domres_SnapAlignOne		 _domresPredefs[_domres_SnapAlignOne]
#define domres_DomainMenu		 _domresPredefs[_domres_DomainMenu]
#define domres_SnapNoAlign		 _domresPredefs[_domres_SnapNoAlign]
#define domres_Galaxy_Demo		 _domresPredefs[_domres_Galaxy_Demo]
#define domres_World		 _domresPredefs[_domres_World]
#define domres_OutlineLimitRect		 _domresPredefs[_domres_OutlineLimitRect]
#define domres_ExternalDrag		 _domresPredefs[_domres_ExternalDrag]
#define domres_Blue_Moon		 _domresPredefs[_domres_Blue_Moon]
#define domres_translateX		 _domresPredefs[_domres_translateX]
#define domres_translateY		 _domresPredefs[_domres_translateY]
#define domres_AutoScrollDrag		 _domresPredefs[_domres_AutoScrollDrag]
#define domres_gridConfirm		 _domresPredefs[_domres_gridConfirm]
#define domres_RemoveObjects		 _domresPredefs[_domres_RemoveObjects]
#define domres_ViewCoords		 _domresPredefs[_domres_ViewCoords]
#define domres_Purple_Moon		 _domresPredefs[_domres_Purple_Moon]
#define domres_Bands		 _domresPredefs[_domres_Bands]
#define domres_bgColorButton		 _domresPredefs[_domres_bgColorButton]
#define domres_coordSysWindow		 _domresPredefs[_domres_coordSysWindow]
#define domres_TrackDrag		 _domresPredefs[_domres_TrackDrag]
#define domres_GrabbingHand		 _domresPredefs[_domres_GrabbingHand]
#define domres_Orange_Spaceman		 _domresPredefs[_domres_Orange_Spaceman]
#define domres_DragProhibited		 _domresPredefs[_domres_DragProhibited]
#define domres_Moon		 _domresPredefs[_domres_Moon]
#define domres_Cancel		 _domresPredefs[_domres_Cancel]
#define domres_DisconnectObjects		 _domresPredefs[_domres_DisconnectObjects]
#define domres_Detached		 _domresPredefs[_domres_Detached]
#define domres_LEX		 _domresPredefs[_domres_LEX]
#define domres_ConnectObjects		 _domresPredefs[_domres_ConnectObjects]
#define domres_SmartScrollbars		 _domresPredefs[_domres_SmartScrollbars]
#define domres_Schwapp		 _domresPredefs[_domres_Schwapp]
#define domres_ToggleVirtual		 _domresPredefs[_domres_ToggleVirtual]
#define domres_selColorButton		 _domresPredefs[_domres_selColorButton]
#define domres_fontButton		 _domresPredefs[_domres_fontButton]
#define domres_Align_Left		 _domresPredefs[_domres_Align_Left]
#define domres_FileMenu		 _domresPredefs[_domres_FileMenu]
#define domres_addItemsConfirm		 _domresPredefs[_domres_addItemsConfirm]
#define domres_ShowAllObjects		 _domresPredefs[_domres_ShowAllObjects]
#define domres_Open		 _domresPredefs[_domres_Open]
#define domres_Save		 _domresPredefs[_domres_Save]
#define domres_Bomb		 _domresPredefs[_domres_Bomb]
#define domres_DragOnUnselectables		 _domresPredefs[_domres_DragOnUnselectables]
#define domres_matrixConfirm		 _domresPredefs[_domres_matrixConfirm]
#define domres_bgColorToggle		 _domresPredefs[_domres_bgColorToggle]
#define domres_DomainInstalled		 _domresPredefs[_domres_DomainInstalled]
#define domres_jjw_vs__Barney		 _domresPredefs[_domres_jjw_vs__Barney]
#define domres_ObjectsMenu		 _domresPredefs[_domres_ObjectsMenu]
#define domres_NormalDrag		 _domresPredefs[_domres_NormalDrag]
#define domres_Preferences		 _domresPredefs[_domres_Preferences]
#define domres_All_Kids_Love_Log		 _domresPredefs[_domres_All_Kids_Love_Log]
#define domres_Align_Vertical_Centers		 _domresPredefs[_domres_Align_Vertical_Centers]
#define domres_VerticalBar		 _domresPredefs[_domres_VerticalBar]
#define domres_ShowGrid		 _domresPredefs[_domres_ShowGrid]
#define domres_HideObjects		 _domresPredefs[_domres_HideObjects]
#define domres_Ok		 _domresPredefs[_domres_Ok]
#define domres_Align_To_Objects		 _domresPredefs[_domres_Align_To_Objects]
#define domres_EOMS		 _domresPredefs[_domres_EOMS]
#define domres_FunStuffMenu		 _domresPredefs[_domres_FunStuffMenu]
#define domres_Conductor		 _domresPredefs[_domres_Conductor]

/*
 * * * * * * * * * PRIVATE EXTERNAL VARIABLES * * * * * * * * * *
 */

extern const vname	 *_domresPredefs[];

/*
 * * * * * * * * * FUNCTION PROTOTYPES * * * * * * * * * *
 */

void domresInternNames( void ); 


vportEND_CPLUSPLUS_EXTERN_C

#endif

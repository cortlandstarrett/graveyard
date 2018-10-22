/* $Id: vlaf.h,v 1.106 1997/11/06 20:48:54 bill Exp $ */

/************************************************************

    vlaf.h

    C Interface file for the Look and Feel Manager

    (c) Copyright Visix Software Inc.
    All rights reserved

************************************************************/

#ifndef vlafINCLUDED
#define vlafINCLUDED

#ifndef  vportINCLUDED
#include <vport.h>
#endif

#ifndef  vcharINCLUDED
#include vcharHEADER
#endif

#ifndef  vnameINCLUDED
#include vnameHEADER
#endif

#ifndef  vrectINCLUDED
#include vrectHEADER
#endif

#ifndef  vkeyINCLUDED
#include vkeyHEADER
#endif

#ifndef  vresourceINCLUDED
#include vresourceHEADER
#endif

#ifndef  vcolorINCLUDED
#include vcolorHEADER
#endif

#ifndef  vcursorINCLUDED
#include vcursorHEADER
#endif

#ifndef  vimageINCLUDED
#include vimageHEADER
#endif

#ifndef  vfontINCLUDED
#include vfontHEADER
#endif

#ifndef  vdrawINCLUDED
#include vdrawHEADER
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * * * * * * * * * * PUBLIC CONSTANT DEFINITIONS * * * * * * * * * *
 */

#define vlafNONE		    0

#ifndef vlafDISABLE_MAC
#define vlafMAC			    1
#endif

#ifndef vlafDISABLE_WINDOWS
#define vlafWINDOWS		    2
#endif

#ifndef vlafDISABLE_MOTIF
#define vlafMOTIF		    3
#endif

/***
#ifndef vlafDISABLE_OPEN_LOOK
#define vlafOPEN_LOOK		    4
#endif
 ***/

#ifdef vlafOPEN_LOOK
#undef vlafOPEN_LOOK
#endif

#ifndef vlafDISABLE_CUA
#define vlafCUA			    5
#endif

#ifndef vlafDISABLE_WIN95
#define vlafWIN95		    6
#endif

#ifdef vlafENABLE_CUA96
#define vlafCUA96                   7
#endif

#ifdef vlafMAC
#define vlafMAC_WINDOWS
#define vlafMAC_WINDOWS_WIN95
#define vlafMAC_MOTIF
#define vlafMAC_CUA
#endif

#ifdef vlafWINDOWS
#ifndef vlafMAC_WINDOWS
#define vlafMAC_WINDOWS
#endif
#ifndef vlafMAC_WINDOWS_WIN95
#define vlafMAC_WINDOWS_WIN95
#endif
#ifndef vlafWINDOWS_MOTIF_CUA
#define vlafWINDOWS_MOTIF_CUA
#endif
#ifndef vlafWINDOWS_MOTIF_CUA_CUA96
#define vlafWINDOWS_MOTIF_CUA_CUA96
#endif
#ifndef vlafWINDOWS_MOTIF_CUA_WIN95
#define vlafWINDOWS_MOTIF_CUA_WIN95
#endif
#ifndef vlafWINDOWS_MOTIF_CUA_WIN95_CUA96
#define vlafWINDOWS_MOTIF_CUA_WIN95_CUA96
#endif
#ifndef vlafWINDOWS_MOTIF
#define vlafWINDOWS_MOTIF
#endif
#ifndef vlafWINDOWS_CUA
#define vlafWINDOWS_CUA
#endif
#ifndef vlafWINDOWS_CUA_CUA96
#define vlafWINDOWS_CUA_CUA96
#endif
#ifndef vlafWINDOWS_CUA_WIN95
#define vlafWINDOWS_CUA_WIN95
#endif
#ifndef vlafWINDOWS_CUA_WIN95_CUA96
#define vlafWINDOWS_CUA_WIN95_CUA96
#endif
#ifndef vlafWINDOWS_WIN95
#define vlafWINDOWS_WIN95
#endif
#endif

#ifdef vlafMOTIF
#ifndef vlafMAC_MOTIF
#define vlafMAC_MOTIF
#endif
#ifndef vlafWINDOWS_MOTIF_CUA
#define vlafWINDOWS_MOTIF_CUA
#endif
#ifndef vlafWINDOWS_MOTIF_CUA_CUA96
#define vlafWINDOWS_MOTIF_CUA_CUA96
#endif
#ifndef vlafWINDOWS_MOTIF_CUA_WIN95
#define vlafWINDOWS_MOTIF_CUA_WIN95
#endif
#ifndef vlafWINDOWS_MOTIF_CUA_WIN95_CUA96
#define vlafWINDOWS_MOTIF_CUA_WIN95_CUA96
#endif
#ifndef vlafWINDOWS_MOTIF
#define vlafWINDOWS_MOTIF
#endif
#define vlafMOTIF_OPEN_LOOK_CUA_CUA96
#define vlafMOTIF_OPEN_LOOK_CUA
#define vlafMOTIF_OPEN_LOOK
#define vlafMOTIF_CUA
#endif

#ifdef vlafOPEN_LOOK
#ifndef vlafMOTIF_OPEN_LOOK_CUA
#define vlafMOTIF_OPEN_LOOK_CUA
#endif
#ifndef vlafMOTIF_OPEN_LOOK_CUA_CUA96
#define vlafMOTIF_OPEN_LOOK_CUA_CUA96
#endif
#ifndef vlafMOTIF_OPEN_LOOK
#define vlafMOTIF_OPEN_LOOK
#endif
#endif

#ifdef vlafCUA
#ifndef vlafMAC_CUA
#define vlafMAC_CUA
#endif
#ifndef vlafWINDOWS_MOTIF_CUA
#define vlafWINDOWS_MOTIF_CUA
#endif
#ifndef vlafWINDOWS_MOTIF_CUA_CUA96
#define vlafWINDOWS_MOTIF_CUA_CUA96
#endif
#ifndef vlafWINDOWS_MOTIF_CUA_WIN95
#define vlafWINDOWS_MOTIF_CUA_WIN95
#endif
#ifndef vlafWINDOWS_MOTIF_CUA_WIN95_CUA96
#define vlafWINDOWS_MOTIF_CUA_WIN95_CUA96
#endif
#ifndef vlafWINDOWS_CUA
#define vlafWINDOWS_CUA
#endif
#ifndef vlafWINDOWS_CUA_CUA96
#define vlafWINDOWS_CUA_CUA96
#endif
#ifndef vlafWINDOWS_CUA_WIN95
#define vlafWINDOWS_CUA_WIN95
#endif
#ifndef vlafWINDOWS_CUA_WIN95_CUA96
#define vlafWINDOWS_CUA_WIN95_CUA96
#endif
#ifndef vlafMOTIF_OPEN_LOOK_CUA_CUA96
#define vlafMOTIF_OPEN_LOOK_CUA_CUA96
#endif
#ifndef vlafMOTIF_OPEN_LOOK_CUA
#define vlafMOTIF_OPEN_LOOK_CUA
#endif
#ifndef vlafMOTIF_CUA
#define vlafMOTIF_CUA
#endif
#ifndef vlafCUA_CUA96
#define vlafCUA_CUA96
#endif
#endif

#ifdef vlafWIN95
#ifndef vlafWINDOWS_WIN95
#define vlafWINDOWS_WIN95
#endif
#ifndef vlafWINDOWS_CUA_WIN95
#define vlafWINDOWS_CUA_WIN95
#endif
#ifndef vlafWINDOWS_CUA_WIN95_CUA96
#define vlafWINDOWS_CUA_WIN95_CUA96
#endif
#ifndef vlafWINDOWS_MOTIF_CUA_WIN95
#define vlafWINDOWS_MOTIF_CUA_WIN95
#endif
#ifndef vlafWINDOWS_MOTIF_CUA_WIN95_CUA96
#define vlafWINDOWS_MOTIF_CUA_WIN95_CUA96
#endif
#ifndef vlafMAC_WINDOWS_WIN95
#define vlafMAC_WINDOWS_WIN95
#endif
#endif

#ifdef vlafCUA96
#ifndef vlafCUA_CUA96
#define vlafCUA_CUA96
#endif
#ifndef vlafWINDOWS_CUA_CUA96
#define vlafWINDOWS_CUA_CUA96
#endif
#ifndef vlafWINDOWS_CUA_WIN95_CUA96
#define vlafWINDOWS_CUA_WIN95_CUA96
#endif
#ifndef vlafWINDOWS_MOTIF_CUA_CUA96
#define vlafWINDOWS_MOTIF_CUA_CUA96
#endif
#ifndef vlafWINDOWS_MOTIF_CUA_WIN95_CUA96
#define vlafWINDOWS_MOTIF_CUA_WIN95_CUA96
#endif
#ifndef vlafMOTIF_OPEN_LOOK_CUA_CUA96
#define vlafMOTIF_OPEN_LOOK_CUA_CUA96
#endif
#endif

enum {
    vlafCURSOR_BLOCK                = 0,
    vlafCURSOR_TEXT,
    vlafCURSOR_HELP,
    vlafCURSOR_RESIZE_HORIZONTAL,
    vlafCURSOR_RESIZE_VERTICAL,
    vlafCURSOR_RESIZE_NW_SE,
    vlafCURSOR_RESIZE_NE_SW,
    vlafCURSOR_RESIZE_COLUMN,
    vlafCURSOR_RESIZE_ROW,
    vlafCURSOR_RESIZE_OMNI,
    vlafCURSOR_SPLIT_HORIZONTAL,
    vlafCURSOR_SPLIT_VERTICAL,
    vlafCURSOR_SELECT,
    vlafCURSOR_GRAB,
    vlafCURSOR_MOVE,
    vlafCURSOR_GOOD_DROP,
    vlafCURSOR_GOOD_DROP_LINK,
    vlafCURSOR_GOOD_DROP_COPY,
    vlafCURSOR_BAD_DROP,
    _vlafCURSOR_COUNT
};

enum {
    vlafIMAGE_NOTICE_WARNING        = 0,
    vlafIMAGE_NOTICE_CAUTION,
    vlafIMAGE_NOTICE_INFORMATION,
    vlafIMAGE_NOTICE_ACTION,
    vlafIMAGE_TREEVIEW_EXPAND,
    vlafIMAGE_TREEVIEW_COLLAPSE,
    _vlafIMAGE_COUNT
};

enum {
    _vlafMASK_ISO                   = 0,
    vlafMASK_ISO_ALT                = _vlafMASK_ISO,
    vlafMASK_ISO_BACKSPACE,
    vlafMASK_ISO_CLEAR,
    vlafMASK_ISO_COMMAND,
    vlafMASK_ISO_CONTROL,
    vlafMASK_ISO_DELETE,
    vlafMASK_ISO_DOWN,
    vlafMASK_ISO_ENTER,
    vlafMASK_ISO_KEY_PAD,
    vlafMASK_ISO_LEFT,
    vlafMASK_ISO_RETURN,
    vlafMASK_ISO_RIGHT,
    vlafMASK_ISO_SHIFT,
    vlafMASK_ISO_SPACE,
    vlafMASK_ISO_TAB,
    vlafMASK_ISO_UNKNOWN,
    vlafMASK_ISO_UP,

    _vlafMASK_MOTIF,
    vlafMASK_MOTIF_RADIO_TOP = _vlafMASK_MOTIF,
    vlafMASK_MOTIF_RADIO_BOTTOM,
    vlafMASK_MOTIF_RADIO_SELECT,
    vlafMASK_MOTIF_MENU_RADIO_TOP,
    vlafMASK_MOTIF_MENU_RADIO_BOTTOM,
    vlafMASK_MOTIF_MENU_RADIO_SELECT,
    vlafMASK_MOTIF_CHECK_CHECK,

    _vlafMASK_WINDOWS,
    vlafMASK_WINDOWS_CHECK_3D_BACKGROUND = _vlafMASK_WINDOWS,
    vlafMASK_WINDOWS_CHECK_3D_CHECK,
    vlafMASK_WINDOWS_CHECK_3D_TOP,
    vlafMASK_WINDOWS_CHECK_3D_BOTTOM,
    vlafMASK_WINDOWS_CHECK_2D_BACKGROUND,
    vlafMASK_WINDOWS_CHECK_2D_CHECK,
    vlafMASK_WINDOWS_CHECK_2D_OUTLINE,
    vlafMASK_WINDOWS_RADIO_3D_BACKGROUND,
    vlafMASK_WINDOWS_RADIO_3D_CHECK,
    vlafMASK_WINDOWS_RADIO_3D_TOP,
    vlafMASK_WINDOWS_RADIO_3D_BOTTOM,
    vlafMASK_WINDOWS_RADIO_2D_BACKGROUND,
    vlafMASK_WINDOWS_RADIO_2D_CHECK,
    vlafMASK_WINDOWS_RADIO_2D_OUTLINE,
    vlafMASK_WINDOWS_MENU_SUBMENU,
    vlafMASK_WINDOWS_MENU_TOGGLE,
    vlafMASK_WINDOWS_SCROLL_LEFT,
    vlafMASK_WINDOWS_SCROLL_RIGHT,
    vlafMASK_WINDOWS_SCROLL_UP,
    vlafMASK_WINDOWS_SCROLL_DOWN,
    vlafMASK_WINDOWS_SLIDER_LEFT,
    vlafMASK_WINDOWS_SLIDER_RIGHT,
    vlafMASK_WINDOWS_SLIDER_UP,
    vlafMASK_WINDOWS_SLIDER_DOWN,
    vlafMASK_WINDOWS_SLIDER_HORZ_THUMB_OUTLINE,
    vlafMASK_WINDOWS_SLIDER_HORZ_THUMB_BACKGROUND,
    vlafMASK_WINDOWS_SLIDER_HORZ_THUMB_TOP,
    vlafMASK_WINDOWS_SLIDER_HORZ_THUMB_BOTTOM,
    vlafMASK_WINDOWS_SLIDER_HORZ_THUMB_INTERIOR,
    vlafMASK_WINDOWS_SLIDER_VERT_THUMB_OUTLINE,
    vlafMASK_WINDOWS_SLIDER_VERT_THUMB_BACKGROUND,
    vlafMASK_WINDOWS_SLIDER_VERT_THUMB_TOP,
    vlafMASK_WINDOWS_SLIDER_VERT_THUMB_BOTTOM,
    vlafMASK_WINDOWS_SLIDER_VERT_THUMB_INTERIOR,
    vlafMASK_WINDOWS_COMBO_DROP_DOWN,
    vlafMASK_WINDOWS_NOTEBOOK_UP,
    vlafMASK_WINDOWS_NOTEBOOK_DOWN,
    vlafMASK_WINDOWS_NOTEBOOK_LEFT,
    vlafMASK_WINDOWS_NOTEBOOK_RIGHT,
    vlafMASK_WINDOWS_SPINNER_UP,
    vlafMASK_WINDOWS_SPINNER_DOWN,
    vlafMASK_WINDOWS_DISABLED_ITEM,
    vlafMASK_WINDOWS_CHECK_3D_OFF,
    vlafMASK_WINDOWS_CHECK_3D_ON,
    vlafMASK_WINDOWS_CHECK_3D_OFF_PRESSED,
    vlafMASK_WINDOWS_CHECK_3D_ON_PRESSED,
    vlafMASK_WINDOWS_CHECK_3D_DISABLED,
    vlafMASK_WINDOWS_RADIO_3D_OFF,
    vlafMASK_WINDOWS_RADIO_3D_ON,
    vlafMASK_WINDOWS_RADIO_3D_OFF_PRESSED,
    vlafMASK_WINDOWS_RADIO_3D_ON_PRESSED,
    vlafMASK_WINDOWS_RADIO_3D_DISABLED,
    vlafMASK_WINDOWS_SCROLL_DNARROW,
    vlafMASK_WINDOWS_SCROLL_DNARROWD,
    vlafMASK_WINDOWS_SCROLL_DNARROWI,
    vlafMASK_WINDOWS_SCROLL_LFARROW,
    vlafMASK_WINDOWS_SCROLL_LFARROWD,
    vlafMASK_WINDOWS_SCROLL_LFARROWI,
    vlafMASK_WINDOWS_SCROLL_RGARROW,
    vlafMASK_WINDOWS_SCROLL_RGARROWD,
    vlafMASK_WINDOWS_SCROLL_RGARROWI,
    vlafMASK_WINDOWS_SCROLL_UPARROW,
    vlafMASK_WINDOWS_SCROLL_UPARROWD,
    vlafMASK_WINDOWS_SCROLL_UPARROWI,
#ifdef vlafOPEN_LOOK
    _vlafMASK_OPEN_LOOK,
    vlafMASK_OPEN_LOOK_PUSH_PIN_OUT_3D_SHADOW_TOP = _vlafMASK_OPEN_LOOK,
    vlafMASK_OPEN_LOOK_PUSH_PIN_OUT_3D_SHADOW_BOTTOM,
    vlafMASK_OPEN_LOOK_PUSH_PIN_OUT_3D_BACKGROUND,
    vlafMASK_OPEN_LOOK_PUSH_PIN_IN_3D_SHADOW_TOP,
    vlafMASK_OPEN_LOOK_PUSH_PIN_IN_3D_SHADOW_BOTTOM,
    vlafMASK_OPEN_LOOK_PUSH_PIN_IN_3D_BACKGROUND,
    vlafMASK_OPEN_LOOK_PUSH_PIN_OUT_2D,
    vlafMASK_OPEN_LOOK_PUSH_PIN_IN_2D,
#endif
    _vlafMASK_CUA,
    vlafMASK_CUA_CHECK_FOREGROUND = _vlafMASK_CUA,
    vlafMASK_CUA_CHECK_SHADOW,
    vlafMASK_CUA_RADIO_BORDER_OFF_IN,
    vlafMASK_CUA_RADIO_BORDER_OFF_OUT,
    vlafMASK_CUA_RADIO_BORDER_ON_IN,
    vlafMASK_CUA_RADIO_BORDER_ON_OUT,
    vlafMASK_CUA_RADIO_INDICATOR_ON_IN,
    vlafMASK_CUA_RADIO_INDICATOR_ON_OUT,
    vlafMASK_CUA_RADIO_SHADOW_ON_IN,
    vlafMASK_CUA_RADIO_SHADOW_ON_OUT,
    vlafMASK_CUA_MENU_SUBMENU,
    vlafMASK_CUA_MENU_TOGGLE,
    vlafMASK_CUA_SCROLL_STIPPLE,
    vlafMASK_CUA_SPINNER_UP,
    vlafMASK_CUA_SPINNER_DOWN,
    vlafMASK_CUA_COMBO_ARROW,
    vlafMASK_CUA_DOWN_ARROW,
    vlafMASK_CUA_UP_ARROW,
    vlafMASK_CUA_LEFT_ARROW,
    vlafMASK_CUA_RIGHT_ARROW,
    vlafMASK_CUA_NOTEBOOK_PAGE_DOWN_ARROW,
    vlafMASK_CUA_NOTEBOOK_PAGE_UP_ARROW,
    vlafMASK_CUA_NOTEBOOK_PAGE_LEFT_ARROW,
    vlafMASK_CUA_NOTEBOOK_PAGE_RIGHT_ARROW,
    vlafMASK_CUA_NOTEBOOK_TABSET_DOWN_ARROW,
    vlafMASK_CUA_NOTEBOOK_TABSET_UP_ARROW,
    vlafMASK_CUA_NOTEBOOK_TABSET_LEFT_ARROW,
    vlafMASK_CUA_NOTEBOOK_TABSET_RIGHT_ARROW,

    _vlafMASK_MAC,
    vlafMASK_MAC_SMALL_ARROW_TOP = _vlafMASK_MAC,
    vlafMASK_MAC_SMALL_ARROW_BOTTOM,
    vlafMASK_MAC_SMALL_ARROW_LEFT,
    vlafMASK_MAC_SMALL_ARROW_RIGHT,
    vlafMASK_MAC_BIG_ARROW_TOP,
    vlafMASK_MAC_BIG_ARROW_BOTTOM,
    vlafMASK_MAC_BIG_ARROW_LEFT,
    vlafMASK_MAC_BIG_ARROW_RIGHT,
    vlafMASK_MAC_SPINNER_BORDER,
    vlafMASK_MAC_SPINNER_BACKGROUND,
    vlafMASK_MAC_SPINNER_INSIDE,
    vlafMASK_MAC_SPINNER_BACKGROUND_TOP,
    vlafMASK_MAC_SPINNER_INSIDE_TOP,
    vlafMASK_MAC_SPINNER_BACKGROUND_BOTTOM,
    vlafMASK_MAC_SPINNER_INSIDE_BOTTOM,
    vlafMASK_MACGA_RADIO_OFF,
    vlafMASK_MACGA_RADIO_ON,
    vlafMASK_MACGA_RADIO_MIX,
    vlafMASK_MACGA_RADIO_OFF_P,
    vlafMASK_MACGA_RADIO_ON_P,
    vlafMASK_MACGA_RADIO_MIX_P,
    vlafMASK_MACGA_RADIO_OFF_D,
    vlafMASK_MACGA_RADIO_ON_D,
    vlafMASK_MACGA_RADIO_MIX_D,
    vlafMASK_MACGA_CHECK_OFF,
    vlafMASK_MACGA_CHECK_ON,
    vlafMASK_MACGA_CHECK_MIX,
    vlafMASK_MACGA_CHECK_OFF_P,
    vlafMASK_MACGA_CHECK_ON_P,
    vlafMASK_MACGA_CHECK_MIX_P,
    vlafMASK_MACGA_CHECK_OFF_D,
    vlafMASK_MACGA_CHECK_ON_D,
    vlafMASK_MACGA_CHECK_MIX_D,
    vlafMASK_MACGA_SCROLL_DARROW,
    vlafMASK_MACGA_SCROLL_LARROW,
    vlafMASK_MACGA_SCROLL_RARROW,
    vlafMASK_MACGA_SCROLL_UARROW,
    vlafMASK_MACGA_SCROLL_VTHUMB,
    vlafMASK_MACGA_SCROLL_HTHUMB,
    vlafMASK_MACGA_SCROLL_DARROW_P,
    vlafMASK_MACGA_SCROLL_LARROW_P,
    vlafMASK_MACGA_SCROLL_RARROW_P,
    vlafMASK_MACGA_SCROLL_UARROW_P,
    vlafMASK_MACGA_SCROLL_VTHUMB_P,
    vlafMASK_MACGA_SCROLL_HTHUMB_P,
    vlafMASK_MACGA_SCROLL_DARROW_D,
    vlafMASK_MACGA_SCROLL_LARROW_D,
    vlafMASK_MACGA_SCROLL_RARROW_D,
    vlafMASK_MACGA_SCROLL_UARROW_D,
    vlafMASK_MACGA_SLIDER_HTHUMB,
    vlafMASK_MACGA_SLIDER_VTHUMB,
    vlafMASK_MACGA_SLIDER_HTHUMB_P,
    vlafMASK_MACGA_SLIDER_VTHUMB_P,
    vlafMASK_MACGA_SLIDER_HTHUMB_D,
    vlafMASK_MACGA_SLIDER_VTHUMB_D,
    vlafMASK_MACGA_ALT_SLIDER_HTHUMB,
    vlafMASK_MACGA_ALT_SLIDER_VTHUMB,
    vlafMASK_MACGA_ALT_SLIDER_HTHUMB_P,
    vlafMASK_MACGA_ALT_SLIDER_VTHUMB_P,
    vlafMASK_MACGA_ALT_SLIDER_HTHUMB_D,
    vlafMASK_MACGA_ALT_SLIDER_VTHUMB_D,
    vlafMASK_MACGA_BUTTON_TL,
    vlafMASK_MACGA_BUTTON_TR,
    vlafMASK_MACGA_BUTTON_BL,
    vlafMASK_MACGA_BUTTON_BR,
    vlafMASK_MACGA_BUTTON_TL_P,
    vlafMASK_MACGA_BUTTON_TR_P,
    vlafMASK_MACGA_BUTTON_BL_P,
    vlafMASK_MACGA_BUTTON_BR_P,
    vlafMASK_MACGA_BUTTON_TL_D,
    vlafMASK_MACGA_BUTTON_TR_D,
    vlafMASK_MACGA_BUTTON_BL_D,
    vlafMASK_MACGA_BUTTON_BR_D,
    vlafMASK_MACGA_DEF_BUTTON_TL,
    vlafMASK_MACGA_DEF_BUTTON_TR,
    vlafMASK_MACGA_DEF_BUTTON_BL,
    vlafMASK_MACGA_DEF_BUTTON_BR,
    vlafMASK_MACGA_DEF_BUTTON_TL_P,
    vlafMASK_MACGA_DEF_BUTTON_TR_P,
    vlafMASK_MACGA_DEF_BUTTON_BL_P,
    vlafMASK_MACGA_DEF_BUTTON_BR_P,
    vlafMASK_MACGA_DEF_BUTTON_TL_D,
    vlafMASK_MACGA_DEF_BUTTON_TR_D,
    vlafMASK_MACGA_DEF_BUTTON_BL_D,
    vlafMASK_MACGA_DEF_BUTTON_BR_D,
    vlafMASK_MACGA_SPINNER_ENABLED,
    vlafMASK_MACGA_SPINNER_DISABLED,
    vlafMASK_MACGA_SPINNER_UP_P,
    vlafMASK_MACGA_SPINNER_DOWN_P,
    _vlafMASK_MAC_LAST = vlafMASK_MACGA_SPINNER_DOWN_P,

    _vlafMASK_WIN95,
    vlafMASK_WIN95_MENU_SUBMENU = _vlafMASK_WIN95,
    vlafMASK_WIN95_MENU_TOGGLE,
    vlafMASK_WIN95_MENU_BULLET,
    vlafMASK_WIN95_CHECK_OFF,
    vlafMASK_WIN95_CHECK_ON,
    vlafMASK_WIN95_CHECK_OFF_PRESSED,
    vlafMASK_WIN95_CHECK_ON_PRESSED,
    vlafMASK_WIN95_CHECK_TRISTATE,
    vlafMASK_WIN95_CHECK_TRISTATE_PRESSED,
    vlafMASK_WIN95_RADIO_OFF,
    vlafMASK_WIN95_RADIO_ON,
    vlafMASK_WIN95_RADIO_OFF_PRESSED,
    vlafMASK_WIN95_RADIO_ON_PRESSED,
    vlafMASK_WIN95_RADIO_DISABLED,
    vlafMASK_WIN95_SLIDER_THUMB_HORIZONTAL_SELECTABLE,
    vlafMASK_WIN95_SLIDER_THUMB_VERTICAL_SELECTABLE,
    vlafMASK_WIN95_SLIDER_THUMB_HORIZONTAL,
    vlafMASK_WIN95_SLIDER_THUMB_VERTICAL,
    vlafMASK_WIN95_SCROLL_DNARROW,
    vlafMASK_WIN95_SCROLL_DNARROWD,
    vlafMASK_WIN95_SCROLL_DNARROWI,
    vlafMASK_WIN95_SCROLL_LFARROW,
    vlafMASK_WIN95_SCROLL_LFARROWD,
    vlafMASK_WIN95_SCROLL_LFARROWI,
    vlafMASK_WIN95_SCROLL_RGARROW,
    vlafMASK_WIN95_SCROLL_RGARROWD,
    vlafMASK_WIN95_SCROLL_RGARROWI,
    vlafMASK_WIN95_SCROLL_UPARROW,
    vlafMASK_WIN95_SCROLL_UPARROWD,
    vlafMASK_WIN95_SCROLL_UPARROWI,
    vlafMASK_WIN95_COMBO_DROP_DOWN,

    _vlafMASK_CUA96,
    vlafMASK_CUA96_CHECK_FOREGROUND = _vlafMASK_CUA96,
    vlafMASK_CUA96_CHECK_SHADOW,
    vlafMASK_CUA96_RADIO_BORDER_OFF_IN,
    vlafMASK_CUA96_RADIO_BORDER_OFF_OUT,
    vlafMASK_CUA96_RADIO_BORDER_ON_IN,
    vlafMASK_CUA96_RADIO_BORDER_ON_OUT,
    vlafMASK_CUA96_RADIO_INDICATOR_ON_IN,
    vlafMASK_CUA96_RADIO_INDICATOR_ON_OUT,
    vlafMASK_CUA96_RADIO_SHADOW_ON_IN,
    vlafMASK_CUA96_RADIO_SHADOW_ON_OUT,
    vlafMASK_CUA96_MENU_SUBMENU,
    vlafMASK_CUA96_MENU_TOGGLE,
    vlafMASK_CUA96_SCROLL_STIPPLE,
    vlafMASK_CUA96_SPINNER_UP,
    vlafMASK_CUA96_SPINNER_DOWN,
    vlafMASK_CUA96_COMBO_ARROW,
    vlafMASK_CUA96_DOWN_ARROW,
    vlafMASK_CUA96_UP_ARROW,
    vlafMASK_CUA96_LEFT_ARROW,
    vlafMASK_CUA96_RIGHT_ARROW,
    vlafMASK_CUA96_NOTEBOOK_PAGE_DOWN_ARROW,
    vlafMASK_CUA96_NOTEBOOK_PAGE_UP_ARROW,
    vlafMASK_CUA96_NOTEBOOK_PAGE_LEFT_ARROW,
    vlafMASK_CUA96_NOTEBOOK_PAGE_RIGHT_ARROW,
    vlafMASK_CUA96_NOTEBOOK_TABSET_DOWN_ARROW,
    vlafMASK_CUA96_NOTEBOOK_TABSET_UP_ARROW,
    vlafMASK_CUA96_NOTEBOOK_TABSET_LEFT_ARROW,
    vlafMASK_CUA96_NOTEBOOK_TABSET_RIGHT_ARROW,

    _vlafMASK_COUNT
};

enum {
    vlafBUTTON_INSET                = 0,
    vlafBUTTON_WIDTH,
    vlafBUTTON_HEIGHT,
    vlafBUTTON_ARROW_SIZE,
    vlafBUTTON_ARROW_MARGIN,
    
    vlafTOGGLE_HEIGHT,
    vlafTOGGLE_WIDTH,
    vlafTOGGLE_MARGIN,

    vlafMENU_SIDE_MARGIN,
    vlafMENU_TOP_MARGIN,
    vlafMENU_BOTTOM_MARGIN,
    vlafMENU_ABBREV_WIDTH,
    vlafMENU_ABBREV_HEIGHT,

    vlafSLIDER_THUMB_WIDTH,
    vlafSLIDER_THUMB_HEIGHT,
    vlafSLIDER_ANCHOR_OFFSET,
    vlafSLIDER_ANCHOR_WIDTH,
    vlafSLIDER_ANCHOR_HEIGHT,
    vlafSLIDER_MARGIN,
    vlafSLIDER_GAUGE_INSET,
    vlafSLIDER_GAUGE_HEIGHT,
    vlafSLIDER_GAUGE_END_WIDTH,

    vlafSCROLLBAR_MINIMUM,
    vlafSCROLLBAR_ABBREV,
    vlafSCROLLBAR_FULL,
    vlafSCROLLBAR_THUMB_WIDTH,
    vlafSCROLLBAR_MIN_THUMB_WIDTH,
    vlafSCROLLBAR_THUMB_HEIGHT,
    vlafSCROLLBAR_CABLE_INSET,
    vlafSCROLLBAR_MARGIN,
    vlafSCROLLBAR_THUMB_ITEM_HEIGHT,

    vlafSPINNER_BUTTON_HEIGHT,
    vlafSPINNER_BUTTON_WIDTH,
    vlafSPINNER_BUTTON_ARROW_SIZE,

    vlafCOMBO_BUTTON_WIDTH,
    vlafCOMBO_BUTTON_HEIGHT,
    vlafCOMBO_BUTTON_ARROW_SIZE,

    _vlafNUM_IDS
};

#ifdef vlafOPEN_LOOK
enum {
    vlafOLG_SBAR_VERT_2D			= 0x01,
    vlafOLG_SBAR_UP_VERT_2D			= 0x02,
    vlafOLG_SBAR_MIDDLE_VERT_2D			= 0x03,
    vlafOLG_SBAR_DOWN_VERT_2D			= 0x04,
    vlafOLG_SBAR_MIN_VERT_2D			= 0x05,
    vlafOLG_SBAR_MIN_UP_VERT_2D			= 0x06,
    vlafOLG_SBAR_MIN_DOWN_VERT_2D		= 0x07,

    vlafOLG_SBAR_HORZ_2D			= 0x0A,
    vlafOLG_SBAR_LEFT_HORZ_2D			= 0x0B,
    vlafOLG_SBAR_MIDDLE_HORZ_2D			= 0x0C,
    vlafOLG_SBAR_RIGHT_HORZ_2D			= 0x0D,
    vlafOLG_SBAR_MIN_HORZ_2D			= 0x0E,
    vlafOLG_SBAR_MIN_LEFT_HORZ_2D		= 0x0F,
    vlafOLG_SBAR_MIN_RIGHT_HORZ_2D		= 0x10,

    vlafOLG_SLIDER_THUMB_HORZ_2D		= 0xAC,
    vlafOLG_SLIDER_GAUGE_HORZ_LEFT_2D		= 0xAD,
    vlafOLG_SLIDER_GAUGE_HORZ_RIGHT_2D		= 0xAE,

    vlafOLG_SLIDER_THUMB_VERT_2D		= 0xB6,
    vlafOLG_SLIDER_GAUGE_VERT_TOP_2D		= 0xB4,
    vlafOLG_SLIDER_GAUGE_VERT_BOTTOM_2D		= 0xB5,

    vlafOLG_SLIDER_THUMB_HORZ_TS		= 0x3C,
    vlafOLG_SLIDER_THUMB_HORZ_BS		= 0x3D,
    vlafOLG_SLIDER_THUMB_HORZ_IN		= 0x3E,
    vlafOLG_SLIDER_GAUGE_HORZ_LEFT_TS		= 0x3F,
    vlafOLG_SLIDER_GAUGE_HORZ_LEFT_BS		= 0x40,
    vlafOLG_SLIDER_GAUGE_HORZ_RIGHT_TS 		= 0x41,
    vlafOLG_SLIDER_GAUGE_HORZ_RIGHT_BS		= 0x42,
    vlafOLG_SLIDER_GAUGE_HORZ_IN		= 0x4D,

    vlafOLG_SLIDER_THUMB_VERT_TS		= 0x55,
    vlafOLG_SLIDER_THUMB_VERT_BS		= 0x56,
    vlafOLG_SLIDER_THUMB_VERT_IN		= 0x57,
    vlafOLG_SLIDER_GAUGE_VERT_TOP_TS		= 0x4F,
    vlafOLG_SLIDER_GAUGE_VERT_TOP_BS		= 0x50,
    vlafOLG_SLIDER_GAUGE_VERT_BOT_TS		= 0x52,
    vlafOLG_SLIDER_GAUGE_VERT_BOT_BS		= 0x53,
    vlafOLG_SLIDER_GAUGE_VERT_IN		= 0x54,

    vlafOLG_SBAR_VERT_THUMB_TS			= 0x36,
    vlafOLG_SBAR_VERT_THUMB_BS			= 0x37,
    vlafOLG_SBAR_HORZ_THUMB_TS			= 0x39,
    vlafOLG_SBAR_HORZ_THUMB_BS			= 0x3A,
    vlafOLG_SBAR_VERT_UP_ARROW			= 0x38,
    vlafOLG_SBAR_VERT_DOWN_ARROW		= 0x3B,

    vlafOLG_SBAR_HORZ_LEFT_ARROW		= 0x8A,
    vlafOLG_SBAR_HORZ_RIGHT_ARROW		= 0x87,

    vlafOLG_SBAR_VERT_MIN_THUMB_TS		= 0x85,
    vlafOLG_SBAR_VERT_MIN_THUMB_BS		= 0x86,
    vlafOLG_SBAR_HORZ_MIN_THUMB_TS		= 0x88,
    vlafOLG_SBAR_HORZ_MIN_THUMB_BS		= 0x89,

    vlafOLG_SBAR_THUMB_MARKER_TS	 	= 0xC4,
    vlafOLG_SBAR_THUMB_MARKER_BS		= 0xC5,
    vlafOLG_SBAR_THUMB_MARKER_BG		= 0xC6,

    vlafOLG_SPINNER_BUTTON                      = 0xE8,         
    vlafOLG_SPINNER_BUTTON_UP                   = 0xE9,         
    vlafOLG_SPINNER_BUTTON_DOWN                 = 0xEA,

    vlafOLG_CHECK_TOP	                        = 0x72,
    vlafOLG_CHECK_BOTTOM	                = 0x73,
    vlafOLG_CHECK_BACKGROUND                    = 0x74,
    vlafOLG_CHECK_CHECK	                        = 0x75,
    vlafOLG_CHECK_BACKCHECK                     = 0x76,
    vlafOLG_CHECK_BOX_2D	                = 0x77,

    vlafOLG_MENU_MARK_BS	                = 0x2D,
    vlafOLG_MENU_MARK_TS	                = 0x2E,
    vlafOLG_MENU_MARK_BG	                = 0x2F,
    vlafOLG_MENU_MARK_2D	                = 0x16,
    vlafOLG_MENU_MARK_HI_2D	                = 0x17,

    vlafOLG_LEFT_BUTTON_TS	                = 0x18,
    vlafOLG_LEFT_BUTTON_BS	                = 0x19,
    vlafOLG_RIGHT_BUTTON_TS	                = 0x1C,
    vlafOLG_RIGHT_BUTTON_BS	                = 0x1B,
    vlafOLG_LEFT_BUTTON_IN	                = 0x1A,
    vlafOLG_RIGHT_BUTTON_IN	                = 0x1D,
    vlafOLG_LEFT_BUTTON_CONF	                = 0x6A,
    vlafOLG_RIGHT_BUTTON_CONF	                = 0x6B,

    vlafOLG_MENU_BS		                = 0x2D,
    vlafOLG_MENU_TS		                = 0x2E,
    vlafOLG_MENU_IN		                = 0x2F,

    vlafOLG_LEFT_BUTTON_2D	                = 0x8B,
    vlafOLG_RIGHT_BUTTON_2D	                = 0x8C,
    vlafOLG_LEFT_BUTTON_IN_2D	                = 0x92,
    vlafOLG_RIGHT_BUTTON_IN_2D                  = 0x93,

    vlafOLG_MENU_FROB_BS	                = 0x30,
    vlafOLG_MENU_FROB_TS	                = 0x31,
    vlafOLG_MENU_FROB_BG	                = 0x32,

    _vlafOLG_COUNT                              = 0x100
};

enum {
    vlafOPEN_LOOK_BUTTON_MENU_FROB  = 0x0001,
    vlafOPEN_LOOK_BUTTON_HILITED    = 0x0002,
    vlafOPEN_LOOK_BUTTON_FILL_2D    = 0x0004,
    vlafOPEN_LOOK_BUTTON_ENABLED    = 0x0008
};

#endif

vportALIAS(vlaf, void)

/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */

const vname *vlafName(
    void
    );

int vlaf3D(
    void
    );

int vlafKeyNav(
    void
    );

int vlafShowMnemonic(
    void
    );

int vlafMultiButton(
    void
    );

int vlafPushPin(
    void
    );

int vlafSelectDefault(
    void
    );

int vlafWarpPointer(
    void
    );

int vlafWarpPointerConfirm(
    void
    );

int vlafItemMenu(
    void
    );

int vlafShadowAlert(
    void
    );

int vlafCenterMenu(
    void
    );

int vlafInvertHilite(
    void
    );

int vlafLeftScrollBar(
    void
    );

int vlafPedantic(
    void
    );

int vlafButtItems(
    void
    );

int vlafGlobalMenuBar(
    void
    );

int vlafNativeMenuBar(
    void
    );

int vlafMDI(
    void
    );

int vlafActivateConfirm(
    void
    );

int vlafUsesSystemColors(
    void
    );

int vlafUsesSystemFonts(
    void
    );

int vlafMnemonicMovesFocus(
    void
    );

int vlafAppear(
    void
    );

int vlafLineWidth(
    void
    );

int vlafShadowWidth(
    void
    );

int vlafCornerRadius(
    void
    );

vkeyModifiers vlafMnemonic(
    void
    );

long vlafControlRepeatDelay(
    void
    );

vcolor *vlafGetColor(
    int                             id
    );

vcursor *vlafGetCursor(
    int                             id
    );

vimage *vlafGetImage(
    int                             id
    );

vimage *vlafGetMask(
    int                             id
    );

void vlafImageMaskIdent(
    int                             id
    );

void vlafUnderlineMnemonic(
    const vchar                    *title,
    int                             mnemonic
    );

void vlafRectShowMnemonic(
    const vchar                    *title,
    int                             mnemonic,
    const vrect                    *rect,
    unsigned int                    flags
    );

void vlafBoxHiliteFill(
    const vrect                    *rect,
    vcolor                         *interior,
    vcolor                         *top,
    vcolor                         *bottom
    );

void vlafDiamondHiliteFill(
    const vrect                    *rect,
    vcolor                         *interior,
    vcolor                         *top,
    vcolor                         *bottom
    );

void vlafArrowHiliteFillX(
    int                             x,
    int                             y,
    int                             length,
    int                             half,
    vcolor                         *interior,
    vcolor                         *straight,
    vcolor                         *bent
    );

void vlafArrowHiliteFillY(
    int                             x,
    int                             y,
    int                             length,
    int                             half,
    vcolor                         *interior,
    vcolor                         *straight,
    vcolor                         *bent
    );

int vlafValue(
    int                             id
    );

void vlafDrawGlyph(
    int	                            id,
    int                             offset
    );

void vlafDrawOpenLookButtonImage(
    const vrect			   *rect,
    int                             flags,
    vcolor                         *topShadow,
    vcolor                         *botShadow,
    vcolor                         *background,
    vcolor			   *debossColor
    );


/*
 * * * * * * * * * * PRIVATE CONSTANT DEFINITIONS * * * * * * * * * *
 */

enum {
    _vlaf3D			    = 0x00000001,
    _vlafKEY_NAV		    = 0x00000002,
    _vlafSHOW_MNEMONIC		    = 0x00000004,
    _vlafMULTI_BUTTON		    = 0x00000008,
    _vlafPUSH_PIN		    = 0x00000010,
    _vlafSELECT_DEFAULT		    = 0x00000020,
    _vlafWARP_POINTER		    = 0x00000040,
    _vlafWARP_POINTER_CONFIRM	    = 0x00000080,
    _vlafITEM_MENU		    = 0x00000100,
    _vlafSHADOW_ALERT		    = 0x00000200,
    _vlafCENTER_MENU		    = 0x00000400,
    _vlafINVERT_HILITE		    = 0x00000800,
    _vlafLEFT_SCROLL_BAR	    = 0x00001000,
    _vlafPEDANTIC                   = 0x00002000,
    _vlafBUTT_ITEMS		    = 0x00004000,
    _vlafGLOBAL_MENU_BAR	    = 0x00008000,
    _vlafMDI             	    = 0x00010000,
    _vlafACTIVATE_CONFIRM           = 0x00020000,
    _vlafSYSTEM_COLORS              = 0x00040000,
    _vlafSYSTEM_FONTS               = 0x00080000,
    _vlafNATIVE_MENUBAR             = 0x00100000,
    _vlafFOCUS_MNEMONIC             = 0x00200000,
    _vlafNATIVE_SYSTEM_COLORS       = 0x00400000

};


enum {
    _vlafMAC_BUTTON_ARROW_GAP_H,
    _vlafMAC_BUTTON_ARROW_GAP_H_ALT,
    _vlafMAC_BUTTON_ARROW_GAP_V,
    _vlafMAC_BUTTON_ARROW_GAP_V_ALT,
    _vlafMAC_BUTTON_ARROW_GAP_H2IMAGE,
    _vlafMAC_SBAR_THICKNESS,
    _vlafMAC_FLOAT_SBAR_THICKNESS,
    _vlafMAC_SBAR_THUMB_LENGTH,
    _vlafMAC_FLOAT_SBAR_THUMB_LENGTH,
    _vlafMAC_DEFAULT_OUTSIDE_SEPARATION,
    _vlafNUM_MAC_IDS
};

#ifdef vlafMAC
#define _vlafMAC_MASK_COUNT (_vlafMASK_MAC_LAST-_vlafMASK_MAC)
#endif

enum {
    vlafCOLOR_3D_BACKGROUND = 0,
    vlafCOLOR_3D_FOREGROUND,
    vlafCOLOR_3D_DISABLED_FOREGROUND,
    vlafCOLOR_3D_BOTTOM_SHADOW,
    vlafCOLOR_3D_TOP_SHADOW,
    vlafCOLOR_3D_DARK_BOTTOM_SHADOW,
    vlafCOLOR_3D_DARK_TOP_SHADOW,
    vlafCOLOR_CONTENT_BACKGROUND,
    vlafCOLOR_CONTENT_FOREGROUND,
    vlafCOLOR_CONTENT_HILITE_BACKGROUND,
    vlafCOLOR_CONTENT_HILITE_FOREGROUND,
    vlafCOLOR_CONTENT_DISABLED_FOREGROUND,
    vlafCOLOR_CONTENT_BORDER,
    vlafCOLOR_STATIC_TEXT,
    vlafCOLOR_MENU_BACKGROUND,
    vlafCOLOR_MENU_FOREGROUND,
    vlafCOLOR_MENU_DISABLED_FOREGROUND,
    vlafCOLOR_MENU_HILITE_BACKGROUND,
    vlafCOLOR_MENU_HILITE_FOREGROUND,
    vlafCOLOR_MENU_BORDER,
    vlafCOLOR_DROP_SHADOW,
    vlafCOLOR_HELP_BACKGROUND,
    vlafCOLOR_HELP_FOREGROUND,
    vlafCOLOR_HELP_HILITE,
    vlafCOLOR_SCROLLBAR_BACKGROUND,
    vlafCOLOR_BUTTON_BACKGROUND,
    vlafCOLOR_NOTEPAGE_BACKGROUND,
    vlafCOLOR_ICON_TEXT,
    vlafCOLOR_FOCUS,
    vlafCOLOR_WINDOW_BACKGROUND,
    vlafCOLOR_WINDOW_FOREGROUND,
    vlafCOLOR_NOTICE_BACKGROUND,
    vlafCOLOR_NOTICE_FOREGROUND,
    vlafCOLOR_WORKSPACE_BACKGROUND,
    vlafCOLOR_DESKTOP_BACKGROUND,
    vlafCOLOR_ACTIVE_BORDER,
    vlafCOLOR_ACTIVE_TITLE_BACKGROUND,
    vlafCOLOR_ACTIVE_TITLE_TEXT_BACKGROUND,
    vlafCOLOR_ACTIVE_TITLE_TEXT_FOREGROUND,
    vlafCOLOR_INACTIVE_BORDER,
    vlafCOLOR_INACTIVE_TITLE_BACKGROUND,
    vlafCOLOR_INACTIVE_TITLE_TEXT_BACKGROUND,
    vlafCOLOR_INACTIVE_TITLE_TEXT_FOREGROUND,
    vlafCOLOR_MENU_BOTTOM_SHADOW,
    vlafCOLOR_MENU_TOP_SHADOW,
    vlafCOLOR_CONTENT_BOTTOM_SHADOW,
    vlafCOLOR_CONTENT_TOP_SHADOW,
    vlafCOLOR_NOTICE_DEBOSS,
    vlafCOLOR_DEBOSS,
    vlafCOLOR_COUNT
};

enum {
    _vlafFONT_DONT_INHERIT = -1,
    _vlafFONT_ICON         =  0,
    _vlafFONT_MENU,
    _vlafFONT_CONFIRM,
    _vlafFONT_HELP,
    _vlafFONT_COUNT
};

/*
 * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * *
 */

typedef struct _vlafAttrs           _vlafAttrs;
typedef struct _vlafButtonBinding   _vlafButtonBinding;

typedef void (*_vlafDrawGlyphProc)(
     int                            id,
     int                            offset
     );

struct _vlafAttrs {
    const char                     *literalName;
    const vname                    *name;
    unsigned long		    flags;
    short			    appear;
    short			    lineWidth;
    short			    shadowWidth;
    short			    cornerRadius;
    vkeyModifiers                   mnemonic;
    const _vlafButtonBinding       *bindings;
    vresource                       resources;
    vcursor                        *cursors[_vlafCURSOR_COUNT];
    vimage                         *images[_vlafIMAGE_COUNT];
    const int			   *systemColorMapping;
    vcolor			  **systemColors;
};

typedef void (*_vlafSystemFontUpdateFunc)(
     vobjectAttributedClass	*clas,
     vfont			*font
     );

/*
 * * * * * * * * * * PRIVATE VARIABLE DECLARATIONS * * * * * * * * * *
 */

extern vportLINK const int                    _vlafValues[];
extern vportLINK _vlafDrawGlyphProc           _vlafDrawGlyph;

extern vportLINK const int		    _vlafMacValues[];

/*
 * * * * * * * * * * PRIVATE FUNCTION PROTOTYPES * * * * * * * * * *
 */

_vlafAttrs *_vlaf(
    void
    );

void _vlafDrawGlyphStartup(
    int                             id, 
    int                             offset
    );

int _vlafMacValue(
    int                             id
    );

void _vlafSetMacDisabledMask(
    int				    id,
    vimage                         *mask
    );

vimage *_vlafGetMacDisabledMask(
    int 			     id
    );

void _vlafDrawMacImageRectCentered(
    vimage			   *image,
    const vrect		   	   *r
    );

void _vlafDrawMacMaskRectCentered(
    vimage			   *mask,
    const vrect			   *r
    );

void _vlafSetDisabledClip(
    const vrect                    *rect
    );

void _vlafDrawFocusRect(
    const vrect                    *rect
    );
		   
void _vlafRectShowMnemonicDisabled(
    const vchar *s, 
    int c, 
    const vrect *rect,
    unsigned int flags, 
    vcolorScheme *scheme
    );

#if (vportWIN_MS_WINDOWS)
vimage *_vlafGetWindowsOEMImage(
    int id
    );
void _vlafInvalWindowsOEMImages(
    void
    );
#endif

void vlafRegisterSystemFontRootClass(
    vobjectAttributedClass	   *clas,
    _vlafSystemFontUpdateFunc	    func
    );

void vlafSetClassSystemFont (
    int				    laf, 
    vobjectAttributedClass	   *clas, 
    int				    sysFont
    );

vstr *_vlafStrokeToString(
    vkeyStroke          stroke
    );

int _vlafTransformWindowsDialogUnitsX(
    vfont      *font,
    int         dialogUnits
    );

int _vlafTransformWindowsDialogUnitsY(
    vfont      *font,
    int         dialogUnits
    );

int _vlafMatchCursor(
    vcursor *cursor
    );

/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * *
 */

#define vlafName()                 (_vlaf()->name)
#define vlaf3D()		  ((_vlaf()->flags&_vlaf3D)	        !=0)
#define vlafKeyNav()		  ((_vlaf()->flags&_vlafKEY_NAV)	!=0)
#define vlafShowMnemonic()	  ((_vlaf()->flags&_vlafSHOW_MNEMONIC)  !=0)
#define vlafMultiButton()	  ((_vlaf()->flags&_vlafMULTI_BUTTON)   !=0)
#define vlafPushPin()		  ((_vlaf()->flags&_vlafPUSH_PIN)       !=0)
#define vlafSelectDefault()	  ((_vlaf()->flags&_vlafSELECT_DEFAULT) !=0)
#define vlafWarpPointer()	  ((_vlaf()->flags&_vlafWARP_POINTER)   !=0)
#define vlafWarpPointerConfirm() \
    ((_vlaf()->flags&_vlafWARP_POINTER_CONFIRM)!=0)
#define vlafItemMenu()		  ((_vlaf()->flags&_vlafITEM_MENU)       !=0)
#define vlafShadowAlert()	  ((_vlaf()->flags&_vlafSHADOW_ALERT)    !=0)
#define vlafCenterMenu()	  ((_vlaf()->flags&_vlafCENTER_MENU)     !=0)
#define vlafInvertHilite()	  ((_vlaf()->flags&_vlafINVERT_HILITE)   !=0)
#define vlafLeftScrollBar()	  ((_vlaf()->flags&_vlafLEFT_SCROLL_BAR) !=0)
#define vlafPedantic()		  ((_vlaf()->flags&_vlafPEDANTIC)        !=0)
#define vlafButtItems()		  ((_vlaf()->flags&_vlafBUTT_ITEMS)      !=0)
#define vlafGlobalMenuBar()	  ((_vlaf()->flags&_vlafGLOBAL_MENU_BAR) !=0)
#define vlafNativeMenuBar()	  ((_vlaf()->flags&_vlafNATIVE_MENUBAR)  !=0)
#define vlafMDI()	          ((_vlaf()->flags&_vlafMDI)             !=0)
#define vlafActivateConfirm()	  ((_vlaf()->flags&_vlafACTIVATE_CONFIRM)!=0)
#define vlafUsesSystemColors()	  ((_vlaf()->flags&_vlafSYSTEM_COLORS)   !=0)
#define vlafUsesSystemFonts()	  ((_vlaf()->flags&_vlafSYSTEM_FONTS)    !=0)
#define vlafMnemonicMovesFocus()  ((_vlaf()->flags&_vlafFOCUS_MNEMONIC)  !=0)
#define vlafAppear()		   (_vlaf()->appear)
#define vlafLineWidth()		   (_vlaf()->lineWidth)
#define vlafShadowWidth()	   (_vlaf()->shadowWidth)
#define vlafCornerRadius()	   (_vlaf()->cornerRadius)
#define vlafMnemonic()             (_vlaf()->mnemonic)

#define vlafValue(i)	           (_vlafValues[i])
#define vlafDrawGlyph(id, o)     ((*_vlafDrawGlyph)(id, o))

#define _vlafMacValue(_i)          (_vlafMacValues[_i])

#define vlafUnderlineMnemonic(t,m) \
    vdrawUnderlineMnemonic(t,m)
#define vlafRectShowMnemonic(t,m,r,f) \
    vdrawRectShowMnemonic(t,m,r,f)
#define vlafBoxHiliteFill(r,i,t,b) \
    vdrawBoxHiliteFill(r,i,t,b)
#define vlafDiamondHiliteFill(r,i,t,b) \
    vdrawDiamondHiliteFill(r,i,t,b)
#define vlafArrowHiliteFillX(x,y,l,h,i,s,b) \
    vdrawArrowHiliteFillX(x,y,l,h,i,s,b)
#define vlafArrowHiliteFillY(x,y,l,h,i,s,b) \
    vdrawArrowHiliteFillY(x,y,l,h,i,s,b)

vportEND_CPLUSPLUS_EXTERN_C

#endif /* #ifndef vlafINCLUDED */


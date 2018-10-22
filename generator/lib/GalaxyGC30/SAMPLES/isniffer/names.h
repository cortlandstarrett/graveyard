/* $Id: names.h,v 1.1 1994/08/19 00:03:16 simone Exp $ */
/****************************************************************************
 *                (c) Copyright 1991-1994 Visix Software, Inc.              *
 *                           All rights reserved.                           *
 * The following Sample Code is provided for your reference purposes in     *
 * connection with your use of the Galaxy Application Environment (TM)      *
 * software product which you have licensed from Visix Software, Inc.       *
 * ("Visix"). The Sample code is provided to you without any warranty of any*
 * kind and you agree to be responsible for the use and/or incorporation    *
 * of the Sample Code into any software product you develop. You agree to   *
 * fully and completely indemnify and hold Visix harmless from any and all  *
 * loss, claim, liability or damages with respect to your use of the Sample *
 * Code.                                                                    *
 *                                                                          *
 * Subject to the foregoing, you are permitted to copy, modify, and         *
 * distribute the Sample Code for any purpose, and without fee, provided    *
 * that (i) a copyright notice in the in the form of "Copyright 1992 Visix  *
 * Software Inc., 11440 Commerce Park Drive, Reston, VA  22091. All Rights  *
 * Reserved" appears in all copies, (ii) both the copyright notice and this *
 * permission notice appear in all supporting documentation and (iii) you   *
 * are a valid licensee of The Galaxy Application Environment.              *
 *                                                                          *
 ****************************************************************************
 *                                                                          *
 * Description:                                                             *
 *     This module defines the global names used by the isnoop application  *
 *                                                                          *
 * Modification History:                                                    *
 *     o 12-11-93: created for galaxy 2.0 (ssmc)                            *
 *                                                                          *
 * Text Editor Formatting:                                                  *
 *     Symantec: Tab(8), Font(Any Fixed Width)                              *
 *     Emacs: see end of file for info                                      *
 *                                                                          *
 ****************************************************************************
 */

#ifndef namesINCLUDED
#define namesINCLUDED 1

#ifndef vportINCLUDED
#include <vport.h>
#endif

#ifndef vnameINCLUDED
#include vnameHEADER
#endif


/*
 *+------------------------------------------------------------------------+
 * `cause i hate typing
 *+------------------------------------------------------------------------+
 */

#define TAG(_L) vnameInternGlobalLiteral(_L)
#define SCRIBE(_L) vcharScribeLiteral(_L)


/*
 *+------------------------------------------------------------------------+
 * global names (resources, dialog items, etc.)
 *+------------------------------------------------------------------------+
 */

enum {
  appNAME_TITLE,
  appNAME_ICON,
  appNAME_OTHER_QUIT_TITLE,
  appNAME_MESSAGES,
  appNAME_STRINGS,
  appNAME_INFO_NOTICE,
  appNAME_QUESTION_NOTICE,
  appNAME_NOTICE_ICON,
  appNAME_VERSION_STRING,
  appNAME_PRINT_STYLE_INFO,

  appNAME_PLACEHOLDER_1,
  appNAME_PLACEHOLDER_2,
  appNAME_PLACEHOLDER_3,
  appNAME_PLACEHOLDER_4,

  appNAME_SNOOP_DIALOG,
  appNAME_LABEL_FILES,
  appNAME_IVIEW_FILES,
  appNAME_ACT_SNOOP,
  appNAME_ACT_SUSPEND,
  appNAME_ACT_RESUME,
  appNAME_ACT_QUIT,
  appNAME_ACT_HELP,
  appNAME_ACT_ADJUST_PREFS,
  appNAME_ACT_OPEN,
  appNAME_ACT_DO_RECUR,
  appNAME_ACT_DO_ALL,
  appNAME_STATUS_ITEM,

  appNAME_IMAGE_TEMP_FILE,
  appNAME_IMAGE_OPEN_TEMP_FILE,
  appNAME_IMAGE_PERM_FILE,
  appNAME_IMAGE_OPEN_PERM_FILE,

  appNAME_VIEWER_DIALOG,
  appNAME_VIEWER_ICON,
  appNAME_VIEWER_GLASS_ICON,
  appNAME_VIEWER_IVIEW,
  appNAME_ACT_MENUCLOSE,
  appNAME_ACT_HIDE,
  appNAME_ACT_CLEANUP,
  appNAME_ACT_TOGGLE_TITLES,
  appNAME_ACT_TOGGLE_THUMBNAIL_VIEW,
  appNAME_ACT_SAVE,
  appNAME_ACT_SAVE_AS,
  appNAME_ACT_REVERT,
  appNAME_ACT_CONFIRM_PRINTSTYLE,
  appNAME_ACT_PRINT,
  appNAME_ACT_UNDO,
  appNAME_ACT_CUT,
  appNAME_ACT_COPY,
  appNAME_ACT_PASTE,
  appNAME_ACT_CLEAR,
  appNAME_ACT_DUPLICATE,
  appNAME_ACT_PASTE_ALIAS,
  appNAME_ACT_DUPLICATE_ALIAS,
  appNAME_ACT_REMOVE,
  appNAME_ACT_PASTE_DICT,
  appNAME_ACT_EDIT_IMAGE,
  appNAME_ACT_BOINK,
  appNAME_ACT_HELP_VIEWER,

  appNAME_STATUS_DIALOG,
  appNAME_SBOX_DICT_LOOK,
  appNAME_SBOX_DICT_FIND,
  appNAME_SBOX_ELLIPSES,
  appNAME_SBOX_WHOLEIMG,
  appNAME_SBOX_PIECEIMG,

  appNAME_PREFS_DIALOG,

  appNAME_PREF_HELP,
  appNAME_PREF_TEMPDIR,
  appNAME_PREF_TEMPFOLDER,
  appNAME_PREF_VERBOSE,
  appNAME_PREF_RECUR,
  appNAME_PREF_ALL,
  appNAME_PREF_THUMBNAILS,
  appNAME_PREF_TITLES,
  appNAME_PREF_THUMBSIZE,
  appNAME_PREF_THUMBSIZE_ACTUAL,
  appNAME_PREF_HEADER,
  appNAME_PREF_FOOTER,
  appNAME_PREF_BORDER,
  appNAME_PREF_PAGENOS,
  appNAME_PREF_ERRATA,

  appNAME_COUNT
};

extern const vname *appNames[];
void appInitNames(void);
const char *appNameLiteral(int);
const vname *appName(int);

#define appName(i)		appNames[(i)]
#define appname_Icon		appNames[appNAME_ICON]
#define appname_Title		appNames[appNAME_TITLE]
#define appname_OtherQuitTitle	appNames[appNAME_OTHER_QUIT_TITLE]
#define appname_Messages	appNames[appNAME_MESSAGES]
#define appname_Strings		appNames[appNAME_STRINGS]
#define appname_VersionString	appNames[appNAME_VERSION_STRING]
#define appname_InfoNotice	appNames[appNAME_INFO_NOTICE]
#define appname_QuestionNotice	appNames[appNAME_QUESTION_NOTICE]
#define appname_NoticeIcon	appNames[appNAME_NOTICE_ICON]
#define appname_PrintStyleInfo  appNames[appNAME_PRINT_STYLE_INFO]
#define appname_GlassImage	appNames[appNAME_VIEWER_GLASS_ICON]

#define appname_SnoopDialog	appNames[appNAME_SNOOP_DIALOG]
#define appname_ReqLabel	appNames[appNAME_LABEL_FILES]
#define appname_ReqView		appNames[appNAME_IVIEW_FILES]
#define appname_SnoopAct	appNames[appNAME_ACT_SNOOP]
#define appname_SuspendAct	appNames[appNAME_ACT_SUSPEND]
#define appname_ResumeAct	appNames[appNAME_ACT_RESUME]
#define appname_QuitAct		appNames[appNAME_ACT_QUIT]
#define appname_HelpAct		appNames[appNAME_ACT_HELP]
#define appname_AdjustPrefsAct	appNames[appNAME_ACT_ADJUST_PREFS]
#define appname_ViewFileAct	appNames[appNAME_ACT_OPEN]
#define appname_DoRecurAct	appNames[appNAME_ACT_DO_RECUR]
#define appname_DoAllAct	appNames[appNAME_ACT_DO_ALL]
#define appname_MainStatusBox	appNames[appNAME_STATUS_ITEM]

#define appname_ViewerDialog	appNames[appNAME_VIEWER_DIALOG]
#define appname_ViewerIcon	appNames[appNAME_VIEWER_ICON]
#define appname_ViewerView	appNames[appNAME_VIEWER_IVIEW]
#define appname_CloseMenuAct	appNames[appNAME_ACT_MENUCLOSE]
#define appname_HideAct		appNames[appNAME_ACT_HIDE]
#define appname_CleanupAct	appNames[appNAME_ACT_CLEANUP]
#define appname_ToggleTitlesAct appNames[appNAME_ACT_TOGGLE_TITLES]
#define appname_ToggleThumbnailAct appNames[appNAME_ACT_TOGGLE_THUMBNAIL_VIEW]
#define appname_SaveAct		appNames[appNAME_ACT_SAVE]
#define appname_SaveAsAct	appNames[appNAME_ACT_SAVE_AS]
#define appname_RevertAct	appNames[appNAME_ACT_REVERT]
#define appname_ConfirmStyleAct	appNames[appNAME_ACT_CONFIRM_PRINTSTYLE]
#define appname_PrintAct	appNames[appNAME_ACT_PRINT]
#define appname_UndoAct		appNames[appNAME_ACT_UNDO]
#define appname_CutAct		appNames[appNAME_ACT_CUT]
#define appname_CopyAct		appNames[appNAME_ACT_COPY]
#define appname_PasteAct	appNames[appNAME_ACT_PASTE]
#define appname_PasteAliasAct	appNames[appNAME_ACT_PASTE_ALIAS]
#define appname_PasteDictAct	appNames[appNAME_ACT_PASTE_DICT]
#define appname_ClearAct	appNames[appNAME_ACT_CLEAR]
#define appname_RemoveAct	appNames[appNAME_ACT_REMOVE]
#define appname_DupAct		appNames[appNAME_ACT_DUPLICATE]
#define appname_DupAliasAct	appNames[appNAME_ACT_DUPLICATE_ALIAS]
#define appname_EditImageAct	appNames[appNAME_ACT_EDIT_IMAGE]
#define appname_BoinkAct	appNames[appNAME_ACT_BOINK]
#define appname_HelpViewerAct	appNames[appNAME_ACT_HELP_VIEWER]

#define appname_PlaceHolder1	appNames[appNAME_PLACEHOLDER_1]
#define appname_PlaceHolder2	appNames[appNAME_PLACEHOLDER_2]
#define appname_PlaceHolder3	appNames[appNAME_PLACEHOLDER_3]
#define appname_PlaceHolder4	appNames[appNAME_PLACEHOLDER_4]

#define appname_StatusDialog	    appNames[appNAME_STATUS_DIALOG]
#define appname_StatusLookImages    appNames[appNAME_SBOX_DICT_LOOK]
#define appname_StatusFindImages    appNames[appNAME_SBOX_DICT_FIND]
#define appname_StatusBoxIdleString appNames[appNAME_SBOX_ELLIPSES]
#define appname_StatusBoxWholeImage appNames[appNAME_SBOX_WHOLEIMG]
#define appname_StatusBoxPieceImage appNames[appNAME_SBOX_PIECEIMG]

#define appname_TempFileIcon	  	appNames[appNAME_IMAGE_TEMP_FILE]
#define appname_OpenedTempFileIcon	appNames[appNAME_IMAGE_OPEN_TEMP_FILE]
#define appname_PermFileIcon		appNames[appNAME_IMAGE_PERM_FILE]
#define appname_OpenedPermFileIcon	appNames[appNAME_IMAGE_OPEN_PERM_FILE]

#define appname_PrefsDialog 	appNames[appNAME_PREFS_DIALOG]
#define appname_TempDir     	appNames[appNAME_PREF_TEMPDIR]
#define appname_TempFolder    	appNames[appNAME_PREF_TEMPFOLDER]
#define appname_HelpPref     	appNames[appNAME_PREF_HELP]
#define appname_Verbose    	appNames[appNAME_PREF_VERBOSE]
#define appname_Recursive	appNames[appNAME_PREF_RECUR]
#define appname_AllCompound	appNames[appNAME_PREF_ALL]
#define appname_Thumbnails	appNames[appNAME_PREF_THUMBNAILS]
#define appname_FullTitles	appNames[appNAME_PREF_TITLES]
#define appname_Thumbsize	appNames[appNAME_PREF_THUMBSIZE]
#define appname_ThumbsizeActual	appNames[appNAME_PREF_THUMBSIZE_ACTUAL]
#define appname_Header		appNames[appNAME_PREF_HEADER]
#define appname_Footer		appNames[appNAME_PREF_FOOTER]
#define appname_Border		appNames[appNAME_PREF_BORDER]
#define appname_PageNos		appNames[appNAME_PREF_PAGENOS]
#define appname_Errata		appNames[appNAME_PREF_ERRATA]

/* namesINCLUDED */
#endif

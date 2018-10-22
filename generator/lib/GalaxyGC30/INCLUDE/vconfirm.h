/* $Id: vconfirm.h,v 1.42 1997/08/22 18:39:26 dimitri Exp $ */

/************************************************************

    vconfirm.h
	Last Modified: September 30, 1993
    C Interface file for Confirmation Dialogs

    (c) Copyright Visix Software Inc.
    All rights reserved

************************************************************/

#ifndef vconfirmINCLUDED
#define vconfirmINCLUDED 1

#ifndef  vportINCLUDED
#include <vport.h>		/* for v*HEADER */
#endif

#ifndef vlafINCLUDED
#include vlafHEADER
#endif

#ifndef  vbuttonINCLUDED
#include vbuttonHEADER
#endif

#ifndef  vclassINCLUDED
#include vclassHEADER
#endif

#ifndef  vcontainerINCLUDED
#include vcontainerHEADER
#endif

#ifndef  vdialogINCLUDED
#include vdialogHEADER
#endif

#ifndef  veventINCLUDED
#include veventHEADER
#endif

#ifndef  vresourceINCLUDED
#include vresourceHEADER
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * * * * * * * * * CONSTANTS AND MACRO DEFINITIONS * * * * * * * * * *
 */

enum {
    _vconfirmOK_TITLE_SET           = 0x0001,
    _vconfirmAPPLY_TITLE_SET        = 0x0002,
    _vconfirmRESET_TITLE_SET        = 0x0004,
    _vconfirmCANCEL_TITLE_SET       = 0x0008,
    _vconfirmDEFAULTS_TITLE_SET     = 0x0010,
    _vconfirmHELP_TITLE_SET         = 0x0020,
    _vconfirmVERTICAL_ARRANGEMENT   = 0x0040,
    _vconfirmOVERRIDE_LABELS	    = 0x0400,
    _vconfirmDISABLE_BUTTONS        = 0x0800,
    _vconfirmGHOST_CHECKED	    = 0x1000,
    _vconfirmGHOST		    = 0x2000,
    _vconfirmPROCESS_NATIVE	    = 0x4000
};


/*
 * * * * * * * * * TYPE AND STRUCTURE DEFINITIONS * * * * * * * * * *
 */

typedef struct vconfirm             vconfirm;
typedef struct vconfirmClass        vconfirmClass;
typedef struct vconfirmButton       vconfirmButton;
typedef struct vconfirmButtonClass  vconfirmButtonClass;

typedef int (*vconfirmHookProc)(
    vconfirm                       *confirm,
    vevent                         *event
    );

struct vconfirm {
    vdialog                         dialog;
    short                           flags;
    vconfirmHookProc		    applyProc;
    vconfirmHookProc		    resetProc;
    vconfirmHookProc		    defaultsProc;
    vconfirmHookProc		    helpProc;
    vconfirmHookProc		    genericProc;
    vcontainer			   *container;
    vdialogItem                    *separator;
    const vname			   *tag;
    void                           *blockData;
    unsigned int		    hiddenFlags;

#if (vportWIN_MAC && defined(vlafMAC))
    const void			   *sysData;
#endif
};

#define vconfirmCLASS(SUPER, CONFIRM, HOOK)                                   \
    vdialogCLASS(SUPER, CONFIRM, HOOK, vdialogItem, vdialogItemList);         \
    vclassMETHOD_RET(vconfirmHANDLE_APPLY, int,                               \
		     (CONFIRM *confirm, vevent *event));                      \
    vclassMETHOD_RET(vconfirmHANDLE_RESET, int,                               \
		     (CONFIRM *confirm, vevent *event));                      \
    vclassMETHOD_RET(vconfirmHANDLE_DEFAULTS, int,                            \
		     (CONFIRM *confirm, vevent *event));                      \
    vclassMETHOD_RET(vconfirmHANDLE_HELP, int,                                \
		     (CONFIRM *confirm, vevent *event));                      \
    vclassMETHOD_RET(vconfirmHANDLE_GENERIC, int,                             \
		     (CONFIRM *confirm, vevent *event));                      \
    vclassMETHOD(vconfirmNOTIFY_APPLY,                                        \
		 (CONFIRM *confirm, vevent *event, int closeConfirm));        \
    vclassMETHOD(vconfirmNOTIFY_RESET,                                        \
		 (CONFIRM *confirm, vevent *event, int closeConfirm));        \
    vclassMETHOD(vconfirmNOTIFY_DEFAULTS,                                     \
		 (CONFIRM *confirm, vevent *event, int closeConfirm));        \
    vclassMETHOD(vconfirmNOTIFY_HELP,                                         \
		 (CONFIRM *confirm, vevent *event, int closeConfirm));        \
    vclassMETHOD(vconfirmNOTIFY_GENERIC,                                      \
		 (CONFIRM *confirm, vevent *event, int closeConfirm));        \
    vclassMETHOD(vconfirmORDER_BUTTONS,                                       \
		 (CONFIRM *confirm));                                         \
    vclassMETHOD(vconfirmDEFAULT_FOCUS_BUTTONS,                               \
		 (CONFIRM *confirm));                                         \
    vclassMETHOD(vconfirmDEFAULT_BUTTONS,                                     \
		 (CONFIRM *confirm));                                         \
    vclassMETHOD(vconfirmSET_OK_TITLE_SCRIBED,                                \
		 (CONFIRM *confirm, vscribe *scribe));                        \
    vclassMETHOD(vconfirmSET_APPLY_TITLE_SCRIBED,                             \
		 (CONFIRM *confirm, vscribe *scribe));                        \
    vclassMETHOD(vconfirmSET_RESET_TITLE_SCRIBED,                             \
		 (CONFIRM *confirm, vscribe *scribe));                        \
    vclassMETHOD(vconfirmSET_CANCEL_TITLE_SCRIBED,                            \
		 (CONFIRM *confirm, vscribe *scribe));                        \
    vclassMETHOD(vconfirmSET_DEFAULTS_TITLE_SCRIBED,                          \
		 (CONFIRM *confirm, vscribe *scribe));                        \
    vclassMETHOD(vconfirmSET_HELP_TITLE_SCRIBED,                              \
		 (CONFIRM *confirm, vscribe *scribe));                        \
    vclassMETHOD(vconfirmSET_APPLY_HOOK,                                      \
		 (CONFIRM *confirm, HOOK applyProc));                         \
    vclassMETHOD(vconfirmSET_RESET_HOOK,                                      \
		 (CONFIRM *confirm, HOOK resetProc));                         \
    vclassMETHOD(vconfirmSET_DEFAULTS_HOOK,                                   \
		 (CONFIRM *confirm, HOOK defaultsProc));                      \
    vclassMETHOD(vconfirmSET_HELP_HOOK,                                       \
		 (CONFIRM *confirm, HOOK helpProc));                          \
    vclassMETHOD(vconfirmSET_GENERIC_HOOK,                                    \
		 (CONFIRM *confirm, HOOK genericProc));                       \
    vclassMETHOD(vconfirmSET_OK, (CONFIRM *confirm, int flag));               \
    vclassMETHOD(vconfirmSET_CANCEL, (CONFIRM *confirm, int flag));           \
    vclassMETHOD(vconfirmSET_APPLY, (CONFIRM *confirm, int flag));            \
    vclassMETHOD(vconfirmSET_RESET, (CONFIRM *confirm, int flag));            \
    vclassMETHOD(vconfirmSET_DEFAULTS, (CONFIRM *confirm, int flag));         \
    vclassMETHOD(vconfirmSET_HELP, (CONFIRM *confirm, int flag));             \
    vclassMETHOD(vconfirmSET_GENERIC, (CONFIRM *confirm, const vname *tag,    \
				        int flag));                           \
    vclassMETHOD(vconfirmSET_OVERRIDE, (CONFIRM *confirm, int flag));         \
    vclassMETHOD_RET(vconfirmPROCESS, const vname *, (CONFIRM *confirm));     \
    vclassMETHOD(vconfirmPROCESS_START, (CONFIRM *confirm));                  \
    vclassMETHOD_RET(vconfirmPROCESS_GET, const vname *, (CONFIRM *confirm)); \
    vclassMETHOD(vconfirmPROCESS_STOP, (CONFIRM *confirm));                   \
    vclassVARIABLE(vconfirmDEFAULT_OK_TITLE, vchar*);                         \
    vclassVARIABLE(vconfirmDEFAULT_APPLY_TITLE, vchar*);                      \
    vclassVARIABLE(vconfirmDEFAULT_RESET_TITLE, vchar*);                      \
    vclassVARIABLE(vconfirmDEFAULT_CANCEL_TITLE, vchar*);                     \
    vclassVARIABLE(vconfirmDEFAULT_DEFAULTS_TITLE, vchar*);                   \
    vclassVARIABLE(vconfirmDEFAULT_HELP_TITLE, vchar*);                       \
    vclassVARIABLE(vconfirmDEFAULT_OK_MNEMONIC, vchar);                       \
    vclassVARIABLE(vconfirmDEFAULT_APPLY_MNEMONIC, vchar);                    \
    vclassVARIABLE(vconfirmDEFAULT_RESET_MNEMONIC, vchar);                    \
    vclassVARIABLE(vconfirmDEFAULT_CANCEL_MNEMONIC, vchar);                   \
    vclassVARIABLE(vconfirmDEFAULT_DEFAULTS_MNEMONIC, vchar);                 \
    vclassVARIABLE(vconfirmDEFAULT_HELP_MNEMONIC, vchar)

struct vconfirmClass {
    vconfirmCLASS(vconfirmClass, vconfirm, vconfirmHookProc);
};

/*
 * Confirmation button class
 */

struct vconfirmButton {
    vbutton            button;
    unsigned int       flags;
    vchar              mnemonic;
    vchar             *title;
};

#define vconfirmButtonCLASS(SUPER, BUTTON, NOTIFY)                            \
    vbuttonCLASS(SUPER, BUTTON, NOTIFY)

struct vconfirmButtonClass {
    vconfirmButtonCLASS(vconfirmButtonClass, vconfirmButton, vbuttonNoteProc);
};



/*
 * * * * * * * * * FUNCTION PROTOTYPES * * * * * * * * * *
 */

void vconfirmStartup(void);


vconfirmClass *vconfirmGetDefaultClass(
    void
    );

vconfirm *vconfirmCreateOfClass(
    vconfirmClass                  *clas
    );

vconfirm *vconfirmCreate(
    void
    );

vconfirm *vconfirmClone(
    vconfirm                       *confirm
    );

void vconfirmInitOfClass(
    vconfirm                       *confirm,
    vconfirmClass                  *clas
    );

void vconfirmInit(
    vconfirm                       *confirm
    );

void vconfirmDestroy(
    vconfirm                       *confirm
    );

void vconfirmCopy(
    vconfirm                       *confirm,
    vconfirm                       *target
    );

void vconfirmCopyInit(
    vconfirm                       *confirm,
    vconfirm                       *target
    );

vconfirm *vconfirmLoad(
    vresource                       resource
    );

void vconfirmLoadInit(
    vconfirm                       *confirm,
    vresource                       resource
    );

void vconfirmStore(
    vconfirm                       *confirm,
    vresource                       resource
    );

void vconfirmOpen(
    vconfirm                       *confirm
    );

void vconfirmProcessStart(
    vconfirm                       *confirm
    );

const vname *vconfirmProcessGet(
    vconfirm                       *confirm
    );

void vconfirmProcessStop(
    vconfirm                       *confirm
    );

const vname *vconfirmProcess(
    vconfirm                       *confirm
    );

void vconfirmClose(
    vconfirm                       *confirm
    );

void vconfirmPlace(
    vconfirm                       *confirm,
    vdialog                        *base,
    int                             modeX,
    int                             modeY
    );

void vconfirmPlaceWindow(
    vconfirm                       *confirm,
    vwindow                        *base,
    int                             modeX,
    int                             modeY
    );

int vconfirmHandleApply(
    vconfirm                       *confirm,
    vevent                         *event
    );

int vconfirmHandleDefaults(
    vconfirm                       *confirm,
    vevent                         *event
    );

int vconfirmHandleGeneric(
    vconfirm                       *confirm,
    vevent                         *event
    );

int vconfirmHandleHelp(
    vconfirm                       *confirm,
    vevent                         *event
    );

int vconfirmHandleReset(
    vconfirm                       *confirm,
    vevent                         *event
    );

void vconfirmNotifyApply(
    vconfirm                       *confirm,
    vevent                         *event,
    int                             closeConfirm
    );

void vconfirmNotifyReset(
    vconfirm                       *confirm,
    vevent                         *event,
    int                             closeConfirm
    );

void vconfirmNotifyDefaults(
    vconfirm                       *confirm,
    vevent                         *event,
    int                             closeConfirm
    );

void vconfirmNotifyHelp(
    vconfirm                       *confirm,
    vevent                         *event,
    int                             closeConfirm
    );

void vconfirmNotifyGeneric(
    vconfirm                       *confirm,
    vevent                         *event,
    int                             closeConfirm
    );

void vconfirmSetData(
    vconfirm                       *confirm,
    const void                     *data
    );

void vconfirmSetTitle(
    vconfirm                       *confirm,
    const vchar                    *title
    );

void vconfirmSetTitleScribed(
    vconfirm                       *confirm,
    vscribe			   *scribe
    );

void vconfirmSetOkTitle(
    vconfirm                       *confirm,
    const vchar                    *title
    );

void vconfirmSetOkTitleScribed(
    vconfirm                       *confirm,
    vscribe			   *title
    );

void vconfirmSetApplyTitle(
    vconfirm                       *confirm,
    const vchar                    *title
    );

void vconfirmSetApplyTitleScribed(
    vconfirm                       *confirm,
    vscribe			   *title
    );

void vconfirmSetResetTitle(
    vconfirm                       *confirm,
    const vchar                    *title
    );

void vconfirmSetResetTitleScribed(
    vconfirm                       *confirm,
    vscribe			   *title
    );

void vconfirmSetCancelTitle(
    vconfirm                       *confirm,
    const vchar                    *title
    );

void vconfirmSetCancelTitleScribed(
    vconfirm                       *confirm,
    vscribe			   *title
    );

void vconfirmSetDefaultsTitle(
    vconfirm                       *confirm,
    const vchar                    *title
    );

void vconfirmSetDefaultsTitleScribed(
    vconfirm                       *confirm,
    vscribe			   *title
    );

void vconfirmSetHelpTitle(
    vconfirm                       *confirm,
    const vchar                    *title
    );

void vconfirmSetHelpTitleScribed(
    vconfirm                       *confirm,
    vscribe			   *title
    );

void vconfirmSetOkMnemonic(
    vconfirm                       *confirm,
    int                             mnemonic
    );

void vconfirmSetApplyMnemonic(
    vconfirm                       *confirm,
    int                             mnemonic
    );

void vconfirmSetResetMnemonic(
    vconfirm                       *confirm,
    int                             mnemonic
    );

void vconfirmSetCancelMnemonic(
    vconfirm                       *confirm,
    int                             mnemonic
    );

void vconfirmSetDefaultsMnemonic(
    vconfirm                       *confirm,
    int                             mnemonic
    );

void vconfirmSetHelpMnemonic(
    vconfirm                       *confirm,
    int                             mnemonic
    );

void vconfirmResetTitles(
    vconfirm			   *confirm
    );

void vconfirmSetApplyHook(
    vconfirm                       *confirm,
    vconfirmHookProc	            applyProc
    );

void vconfirmSetResetHook(
    vconfirm                       *confirm,
    vconfirmHookProc	            resetProc
    );

void vconfirmSetDefaultsHook(
    vconfirm                       *confirm,
    vconfirmHookProc	            defaultsProc
    );

void vconfirmSetHelpHook(
    vconfirm                       *confirm,
    vconfirmHookProc	            helpProc
    );

void vconfirmSetGenericHook(
    vconfirm                       *confirm,
    vconfirmHookProc	            genericProc
    );

#if !(vportBAD_CC_SCOPING)
void vconfirmSetOK(
    vconfirm                       *confirm,
    int                             flag
    );
#endif

void vconfirmSetOk(
    vconfirm                       *confirm,
    int                             flag
    );

void vconfirmSetCancel(
    vconfirm                       *confirm,
    int                             flag
    );

void vconfirmSetApply(
    vconfirm                       *confirm,
    int                             flag
    );

void vconfirmSetReset(
    vconfirm                       *confirm,
    int                             flag
    );

void vconfirmSetDefaults(
    vconfirm                       *confirm,
    int                             flag
    );

void vconfirmSetHelp(
    vconfirm                       *confirm,
    int                             flag
    );

void vconfirmSetGeneric(
    vconfirm                       *confirm,
    const vname                    *tag,
    int                             flag
    );

void vconfirmSetOverride(
    vconfirm                       *confirm,
    int                             flag
    );

void vconfirmSetVertical(
    vconfirm                       *confirm,
    int                             flag
    );

void vconfirmSetDisabledButtons(
    vconfirm			   *confirm,
    int                             flag
    );

int vconfirmHasDisabledButtons(
    vconfirm			   *confirm
    );

vwindow *vconfirmGetWindow(
    vconfirm                       *confirm
    );

vdialog *vconfirmGetDialog(
    vconfirm                       *confirm
    );

vconfirmClass *vconfirmGetClass(
    vconfirm                       *confirm
    );

const void *vconfirmGetData(
    vconfirm                       *confirm
    );

const vchar *vconfirmGetTitle(
    vconfirm                       *confirm
    );

int vconfirmIsOpen(
    vconfirm                       *confirm
    );

const vchar *vconfirmGetOkTitle(
    vconfirm                       *confirm
    );

const vchar *vconfirmGetApplyTitle(
    vconfirm                       *confirm
    );

const vchar *vconfirmGetResetTitle(
    vconfirm                       *confirm
    );

const vchar *vconfirmGetCancelTitle(
    vconfirm                       *confirm
    );

const vchar *vconfirmGetDefaultsTitle(
    vconfirm                       *confirm
    );

const vchar *vconfirmGetHelpTitle(
    vconfirm                       *confirm
    );

int vconfirmGetOkMnemonic(
    vconfirm                       *confirm
    );

int vconfirmGetApplyMnemonic(
    vconfirm                       *confirm
    );

int vconfirmGetResetMnemonic(
    vconfirm                       *confirm
    );

int vconfirmGetCancelMnemonic(
    vconfirm                       *confirm
    );

int vconfirmGetDefaultsMnemonic(
    vconfirm                       *confirm
    );

int vconfirmGetHelpMnemonic(
    vconfirm                       *confirm
    );

vconfirmHookProc vconfirmGetApplyHook(
    vconfirm                       *confirm
    );

vconfirmHookProc vconfirmGetResetHook(
    vconfirm                       *confirm
    );

vconfirmHookProc vconfirmGetDefaultsHook(
    vconfirm                       *confirm
    );

vconfirmHookProc vconfirmGetHelpHook(
    vconfirm                       *confirm
    );

vconfirmHookProc vconfirmGetGenericHook(
    vconfirm                       *confirm
    );

const vname *vconfirmGetGenericTag(
    vconfirm                       *confirm
    );

int vconfirmHasOk(
    vconfirm                       *confirm
    );

int vconfirmHasCancel(
    vconfirm                       *confirm
    );

int vconfirmHasApply(
    vconfirm                       *confirm
    );

int vconfirmHasReset(
    vconfirm                       *confirm
    );

int vconfirmHasDefaults(
    vconfirm                       *confirm
    );

int vconfirmHasHelp(
    vconfirm                       *confirm
    );

int vconfirmHasOverride(
    vconfirm                       *confirm
    );

int vconfirmIsVertical(
    vconfirm                       *confirm
    );

vcontainer *vconfirmGetContainer(
    vconfirm                       *confirm
    );

vdialogItem *vconfirmGetSeparator(
    vconfirm                       *confirm
    );

vdialogItem *vconfirmGetButton(
    vconfirm                       *confirm,
    const vname                    *tag
    );

vchar *vconfirmGetButtonTitle(
    vconfirm                       *confirm,
    const vname                    *tag
    );

int vconfirmGetButtonMnemonic(
    vconfirm                       *confirm,
    const vname                    *tag
    );

vconfirmButtonClass *vconfirmButtonGetDefaultClass(
    void
    );

vconfirmButton *vconfirmButtonCreateOfClass(
    vconfirmButtonClass             *clas
    );

vconfirmButton *vconfirmButtonCreate(
    void
    );

vbutton *vconfirmButtonGetButton(
    vconfirmButton                  *button
    );

void vconfirmOrder(
    vconfirm                        *confirm
    );


/*
 * DEPRICATED  FUNCTIONS
 */

vconfirmHookProc vconfirmGetApplyNotify(
    vconfirm                       *confirm
    );

vconfirmHookProc vconfirmGetResetNotify(
    vconfirm                       *confirm
    );

vconfirmHookProc vconfirmGetDefaultsNotify(
    vconfirm                       *confirm
    );

vconfirmHookProc vconfirmGetHelpNotify(
    vconfirm                       *confirm
    );

void vconfirmGetMinSize(
    vconfirm                       *confirm,
    int				   *w,
    int				   *h
    );


/*
 * * * * * * * * * * PRIVATE FUNCTION PROTOTYPES * * * * * * * * * *
 */

/*
 * * * * * * * * * FUNCTION DEFINED AS #define MACROS * * * * * * * * * *
 */

#define vconfirmGetDialog(d)     vportBASE_OBJECT((d), dialog)

#define vconfirmCreateOfClass(c) \
    ((vconfirm*)vdialogCreateOfClass((vdialogClass*)(c)))
#define vconfirmCreate() \
    vconfirmCreateOfClass(vconfirmGetDefaultClass())
#define vconfirmClone(d)          ((vconfirm*)vdialogClone((vdialog*)(d)))
#define vconfirmInitOfClass(d, c) \
    vdialogInitOfClass(vconfirmGetDialog(d), (vdialogClass*)(c))
#define vconfirmInit(d) \
    vconfirmInitOfClass(d, vconfirmGetDefaultClass())
#define vconfirmCopyInit(d, t) \
    vdialogCopyInit(vconfirmGetDialog(d), vconfirmGetDialog(t))
#define vconfirmLoad(r)           ((vconfirm*)vdialogLoad(r))
#define vconfirmLoadInit(d, r)      vdialogLoadInit(vconfirmGetDialog(d), r)
#define vconfirmDestroy(d) \
  vdialogDestroy(vconfirmGetDialog(d))

#define vconfirmPlace(d, b, x, y)   vdialogPlace(vconfirmGetDialog(d), b, x, y)
#define vconfirmPlaceWindow(d, b, x, y)	\
    vdialogPlaceWindow(vconfirmGetDialog(d), b, x, y)
#define vconfirmGetWindow(d)        vdialogGetWindow(vconfirmGetDialog(d))
#define vconfirmGetClass(d) \
    ((vconfirmClass*) vobjectGetClass((vobject *) (d)))
#define vconfirmGetData(d)           vdialogGetData(vconfirmGetDialog(d))
#define vconfirmGetTitle(d)          vdialogGetTitle(vconfirmGetDialog(d))
#define vconfirmIsOpen(d)            vdialogIsOpen(vconfirmGetDialog(d))

#define vconfirmGetMinSize(d, w, h)                              \
  vdialogCalcMinSize(vconfirmGetDialog(d), w, h)

#define vconfirmGetOkTitle(d)        \
    ((const vchar*) vconfirmGetButtonTitle((d), vname_Ok))
#define vconfirmGetApplyTitle(d)     \
    ((const vchar*) vconfirmGetButtonTitle((d), vname_Apply))
#define vconfirmGetResetTitle(d)     \
    ((const vchar*) vconfirmGetButtonTitle((d), vname_Reset))
#define vconfirmGetCancelTitle(d)    \
    ((const vchar*) vconfirmGetButtonTitle((d), vname_Cancel))
#define vconfirmGetDefaultsTitle(d)  \
    ((const vchar*) vconfirmGetButtonTitle((d), vname_Defaults))
#define vconfirmGetHelpTitle(d)      \
    ((const vchar*) vconfirmGetButtonTitle((d), vname_Help))

#define vconfirmGetOkMnemonic(d)        \
    ((int) vconfirmGetButtonMnemonic((d), vname_Ok))
#define vconfirmGetApplyMnemonic(d)     \
    ((int) vconfirmGetButtonMnemonic((d), vname_Apply))
#define vconfirmGetResetMnemonic(d)     \
    ((int) vconfirmGetButtonMnemonic((d), vname_Reset))
#define vconfirmGetCancelMnemonic(d)    \
    ((int) vconfirmGetButtonMnemonic((d), vname_Cancel))
#define vconfirmGetDefaultsMnemonic(d)  \
    ((int) vconfirmGetButtonMnemonic((d), vname_Defaults))
#define vconfirmGetHelpMnemonic(d)      \
    ((int) vconfirmGetButtonMnemonic((d), vname_Help))

#define vconfirmGetApplyNotify(d)    ((d)->applyProc)
#define vconfirmGetResetNotify(d)    ((d)->resetProc)
#define vconfirmGetDefaultsNotify(d) ((d)->defaultsProc)
#define vconfirmGetHelpNotify(d)     ((d)->helpProc)
#define vconfirmGetApplyHook(d)      ((d)->applyProc)
#define vconfirmGetResetHook(d)      ((d)->resetProc)
#define vconfirmGetDefaultsHook(d)   ((d)->defaultsProc)
#define vconfirmGetHelpHook(d)       ((d)->helpProc)
#define vconfirmGetGenericHook(d)    ((d)->genericProc)
#define vconfirmGetGenericTag(d)     ((d)->tag)

#define vconfirmGetContainer(d)      ((d)->container)
#define vconfirmGetSeparator(d)      ((d)->separator)

#define vconfirmHasDisabledButtons(d) ((d)->flags&_vconfirmDISABLE_BUTTONS)
#define vconfirmIsVertical(d)        ((d)->flags&_vconfirmVERTICAL_ARRANGEMENT)
#define vconfirmHasOverride(d)	      ((d)->flags&_vconfirmOVERRIDE_LABELS)
#define vconfirmSetTitle(d, t)	     vdialogSetTitle(vconfirmGetDialog(d), t)

#define vconfirmSetOkTitle(d, t)                                  \
    vconfirmSetOkTitleScribed(d, ((t == NULL) ? (vscribe *)NULL : vcharScribe(t)))
#define vconfirmSetApplyTitle(d, t)                               \
    vconfirmSetApplyTitleScribed(d, ((t == NULL) ? (vscribe *)NULL : vcharScribe(t)))
#define vconfirmSetResetTitle(d, t)                               \
    vconfirmSetResetTitleScribed(d, ((t == NULL) ? (vscribe *)NULL : vcharScribe(t)))
#define vconfirmSetCancelTitle(d, t)                              \
    vconfirmSetCancelTitleScribed(d, ((t == NULL) ? (vscribe *)NULL : vcharScribe(t)))
#define vconfirmSetDefaultsTitle(d, t)                            \
    vconfirmSetDefaultsTitleScribed(d, ((t == NULL) ? (vscribe *)NULL : vcharScribe(t)))
#define vconfirmSetHelpTitle(d, t)                                \
    vconfirmSetHelpTitleScribed(d, ((t == NULL) ? (vscribe *)NULL : vcharScribe(t)))

#define vconfirmButtonCreateOfClass(c)                                       \
    ((vconfirmButton *) vbuttonCreateOfClass((vbuttonClass*)(c)))

#define vconfirmButtonCreate()                                               \
    vconfirmButtonCreateOfClass(vconfirmButtonGetDefaultClass())

#define vconfirmButtonGetButton(b)    vportBASE_OBJECT((b), button)

/*
 * * * * * * * * * FUNCTION DEFINED AS MESSAGES * * * * * * * * * *
 */

#define vconfirmCopy(d, t) \
  vclassSend(vconfirmGetClass(d), vobjectCOPY, (d, t))
#define vconfirmStore(d, r) \
  vclassSend(vconfirmGetClass(d), vobjectSTORE, (d, r))
#define vconfirmOpen(d) \
  vclassSend(vconfirmGetClass(d), vwindowOPEN, (d))
#define vconfirmClose(d) \
  vclassSend(vconfirmGetClass(d), vwindowCLOSE, (d))
#define vconfirmOrder(d) \
  vclassSend(vconfirmGetClass(d), vconfirmORDER_BUTTONS, (d))

#define vconfirmHandleApply(d, e)                              \
    vclassSend(vconfirmGetClass(d), vconfirmHANDLE_APPLY, (d, e))
#define vconfirmHandleReset(d, e)                              \
    vclassSend(vconfirmGetClass(d), vconfirmHANDLE_RESET, (d, e))
#define vconfirmHandleDefaults(d, e)                           \
    vclassSend(vconfirmGetClass(d), vconfirmHANDLE_DEFAULTS, (d, e))
#define vconfirmHandleHelp(d, e)                               \
    vclassSend(vconfirmGetClass(d), vconfirmHANDLE_HELP, (d, e))
#define vconfirmHandleGeneric(d, e)                            \
    vclassSend(vconfirmGetClass(d), vconfirmHANDLE_GENERIC, (d, e))

#define vconfirmNotifyApply(d, e, f)                              \
    vclassSend(vconfirmGetClass(d), vconfirmNOTIFY_APPLY, (d, e, f))
#define vconfirmNotifyReset(d, e, f)                              \
    vclassSend(vconfirmGetClass(d), vconfirmNOTIFY_RESET, (d, e, f))
#define vconfirmNotifyDefaults(d, e, f)                           \
    vclassSend(vconfirmGetClass(d), vconfirmNOTIFY_DEFAULTS, (d, e, f))
#define vconfirmNotifyHelp(d, e, f)                               \
    vclassSend(vconfirmGetClass(d), vconfirmNOTIFY_HELP, (d, e, f))
#define vconfirmNotifyGeneric(d, e, f)                            \
    vclassSend(vconfirmGetClass(d), vconfirmNOTIFY_GENERIC, (d, e, f))

#define vconfirmProcess(d) \
  vclassSend(vconfirmGetClass(d), vconfirmPROCESS, (d))
#define vconfirmProcessStart(d) \
  vclassSend(vconfirmGetClass(d), vconfirmPROCESS_START, (d))
#define vconfirmProcessGet(d) \
  vclassSend(vconfirmGetClass(d), vconfirmPROCESS_GET, (d))
#define vconfirmProcessStop(d) \
  vclassSend(vconfirmGetClass(d), vconfirmPROCESS_STOP, (d))

#define vconfirmSetData(d, p) \
  vclassSend(vconfirmGetClass(d), vwindowSET_DATA, (d, p))

#define vconfirmSetTitleScribed(d, s)                             \
  vclassSend(vconfirmGetClass(d), vwindowSET_TITLE_SCRIBED, (d, s))

#define vconfirmSetOkTitleScribed(d, t)                           \
  vclassSend(vconfirmGetClass(d), vconfirmSET_OK_TITLE_SCRIBED, (d, t))
#define vconfirmSetApplyTitleScribed(d, t)                        \
  vclassSend(vconfirmGetClass(d), vconfirmSET_APPLY_TITLE_SCRIBED, (d, t))
#define vconfirmSetResetTitleScribed(d, t)                        \
  vclassSend(vconfirmGetClass(d), vconfirmSET_RESET_TITLE_SCRIBED, (d, t))
#define vconfirmSetCancelTitleScribed(d, t)                       \
  vclassSend(vconfirmGetClass(d), vconfirmSET_CANCEL_TITLE_SCRIBED, (d, t))
#define vconfirmSetDefaultsTitleScribed(d, t)                     \
  vclassSend(vconfirmGetClass(d), vconfirmSET_DEFAULTS_TITLE_SCRIBED, (d, t))
#define vconfirmSetHelpTitleScribed(d, t)                         \
  vclassSend(vconfirmGetClass(d), vconfirmSET_HELP_TITLE_SCRIBED, (d, t))

#define vconfirmSetApplyHook(d, p)                                \
    vclassSend(vconfirmGetClass(d), vconfirmSET_APPLY_HOOK, (d, p))
#define vconfirmSetResetHook(d, p)                                \
    vclassSend(vconfirmGetClass(d), vconfirmSET_RESET_HOOK, (d, p))
#define vconfirmSetDefaultsHook(d, p)                             \
    vclassSend(vconfirmGetClass(d), vconfirmSET_DEFAULTS_HOOK, (d, p))
#define vconfirmSetHelpHook(d, p)                                 \
    vclassSend(vconfirmGetClass(d), vconfirmSET_HELP_HOOK, (d, p))
#define vconfirmSetGenericHook(d, p)                              \
    vclassSend(vconfirmGetClass(d), vconfirmSET_GENERIC_HOOK, (d, p))

#define vconfirmSetOk(d, f) \
  vclassSend(vconfirmGetClass(d), vconfirmSET_OK, (d, f))
#define vconfirmSetOK(d, f) \
  vclassSend(vconfirmGetClass(d), vconfirmSET_OK, (d, f))
#define vconfirmSetCancel(d, f) \
  vclassSend(vconfirmGetClass(d), vconfirmSET_CANCEL, (d, f))
#define vconfirmSetApply(d, f) \
 vclassSend(vconfirmGetClass(d), vconfirmSET_APPLY, (d, f))
#define vconfirmSetReset(d, f) \
  vclassSend(vconfirmGetClass(d), vconfirmSET_RESET, (d, f))
#define vconfirmSetDefaults(d, f)                                \
  vclassSend(vconfirmGetClass(d), vconfirmSET_DEFAULTS, (d, f))
#define vconfirmSetHelp(d, f) \
  vclassSend(vconfirmGetClass(d), vconfirmSET_HELP, (d, f))
#define vconfirmSetGeneric(d, f, t)                              \
  vclassSend(vconfirmGetClass(d), vconfirmSET_GENERIC, ((d), (f), (t)))

#define vconfirmSetOverride(d, f)                                \
  vclassSend(vconfirmGetClass(d), vconfirmSET_OVERRIDE, ((d), (f)))

vportEND_CPLUSPLUS_EXTERN_C

#endif


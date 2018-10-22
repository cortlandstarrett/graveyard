/* $Id: vnotice.h,v 1.40 1997/08/22 19:11:25 dimitri Exp $ */

/************************************************************

    vnotice.h
    C Interface file for Notification Dialogs

    (c) Copyright Visix Software Inc.
    All rights reserved

************************************************************/

#ifndef vnoticeINCLUDED
#define vnoticeINCLUDED 1

#ifndef  vportINCLUDED
#include <vport.h>		/* for v*HEADER */
#endif

#ifndef  vtextitemINCLUDED
#include vtextitemHEADER
#endif

#ifndef  vclassINCLUDED
#include vclassHEADER
#endif

#ifndef  vdialogINCLUDED
#include vdialogHEADER
#endif

#ifndef  veventINCLUDED
#include veventHEADER
#endif

#ifndef  vimageINCLUDED
#include vimageHEADER
#endif

#ifndef  vresourceINCLUDED
#include vresourceHEADER
#endif

#ifndef  vconfirmINCLUDED
#include vconfirmHEADER
#endif


vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * * * * * * * * * CONSTANTS AND MACRO DEFINITIONS * * * * * * * * * *
 */

/*
 * * * * * * * * * TYPE AND STRUCTURE DEFINITIONS * * * * * * * * * *
 */

typedef struct vnotice              vnotice;
typedef struct vnoticeClass         vnoticeClass;

typedef int (*vnoticeHookProc)(
    vnotice                        *notice,
    vevent                         *event
    );

struct vnotice {
    vconfirm			    confirm;
    short			    flags;
    vtextitem			   *textItem;
    vdialogItem			   *boxItem;
    vimage			   *icon;
    vchar			    key_down;
};

#define vnoticeCLASS(SUPER, NOTICE, HOOK)                                    \
    vconfirmCLASS(SUPER, NOTICE, HOOK);                                      \
    vclassMETHOD_RET(vnoticeHANDLE_YES, int,                                 \
		     (NOTICE *notice, vevent *event));                       \
    vclassMETHOD_RET(vnoticeHANDLE_NO, int,                                  \
		     (NOTICE *notice, vevent *event));                       \
    vclassMETHOD_RET(vnoticeHANDLE_CANCEL, int,                              \
		     (NOTICE *notice, vevent *event));                       \
    vclassMETHOD(vnoticeSET_YES_TITLE_SCRIBED,                               \
		 (NOTICE *notice, vscribe *scribe));                         \
    vclassMETHOD(vnoticeSET_NO_TITLE_SCRIBED,                                \
		 (NOTICE *notice, vscribe *scribe));                         \
    vclassMETHOD(vnoticeSET_TEXT_SCRIBED,                                    \
		 (NOTICE *notice, vscribe *text));                           \
    vclassMETHOD(vnoticeSET_CAUTION, (NOTICE *notice, int flag));	     \
    vclassMETHOD(vnoticeSET_CANCEL, (NOTICE *notice, int flag));	     \
    vclassMETHOD(vnoticeSET_ICON, (NOTICE *notice, vimage *icon));           \
    vclassMETHOD(vnoticeCALC_TEXT_SIZE, (NOTICE *notice, int avail_width,    \
					 int *w, int *h))

struct vnoticeClass {
    vnoticeCLASS(vnoticeClass, vnotice, vnoticeHookProc);
};

/*
 * * * * * * * * * FUNCTION PROTOTYPES * * * * * * * * * *
 */

void vnoticeStartup(void);


vnoticeClass *vnoticeGetDefaultClass(
    void
    );

vnotice *vnoticeCreateOfClass(
    vnoticeClass                  *clas
    );

vnotice *vnoticeCreate(
    void
    );

vnotice *vnoticeClone(
    vnotice                       *notice
    );

void vnoticeInitOfClass(
    vnotice                        *notice,
    vnoticeClass                   *clas
    );

void vnoticeInit(
    vnotice                        *notice
    );

void vnoticeDestroy(
    vnotice                        *notice
    );

void vnoticeCopy(
    vnotice                        *notice,
    vnotice                        *target
    );

void vnoticeCopyInit(
    vnotice                        *notice,
    vnotice                        *target
    );

vnotice *vnoticeLoad(
    vresource                       resource
    );

void vnoticeLoadInit(
    vnotice                        *notice,
    vresource                       resource
    );

void vnoticeStore(
    vnotice                        *notice,
    vresource                       resource
    );

void vnoticeOpen(
    vnotice                        *notice
    );

void vnoticeClose(
    vnotice                        *notice
    );

void vnoticePlace(
    vnotice                        *notice,
    vdialog                        *base,
    int                             modeX,
    int                             modeY
    );

void vnoticePlaceWindow(
    vnotice                        *notice,
    vwindow                        *base,
    int                             modeX,
    int                             modeY
    );

int vnoticeHandleYes(
    vnotice                       *notice,
    vevent                         *event
    );

int vnoticeHandleNo(
    vnotice                       *notice,
    vevent                         *event
    );

int vnoticeHandleCancel(
    vnotice                       *notice,
    vevent                         *event
    );

void vnoticeSetData(
    vnotice                        *notice,
    void                           *data
    );

void vnoticeSetTitle(
    vnotice                        *notice,
    const vchar                    *title
    );

void vnoticeSetTitleScribed(
    vnotice                        *notice,
    vscribe 			   *scribe
    );

void vnoticeSetOkTitle(
    vnotice                        *notice,
    const vchar                    *title
    );

void vnoticeSetOkTitleScribed(
    vnotice                        *notice,
    vscribe			   *scribe
    );

void vnoticeSetYesTitle(
    vnotice                        *notice,
    const vchar                    *title
    );

void vnoticeSetYesTitleScribed(
    vnotice                        *notice,
    vscribe			   *scribe
    );

void vnoticeSetNoTitle(
    vnotice                        *notice,
    const vchar                    *title
    );

void vnoticeSetNoTitleScribed(
    vnotice                        *notice,
    vscribe			   *scribe
    );

void vnoticeSetCancelTitle(
    vnotice                        *notice,
    const vchar                    *title
    );

void vnoticeSetCancelTitleScribed(
    vnotice                        *notice,
    vscribe			   *scribe
    );

void vnoticeSetOkMnemonic(
    vnotice                        *notice,
    int                             mnemonic
    );

void vnoticeSetYesMnemonic(
    vnotice                        *notice,
    int                             mnemonic			   
    );

void vnoticeSetNoMnemonic(
    vnotice                        *notice,
    int                             mnemonic
    );

void vnoticeSetCancelMnemonic(
    vnotice                        *notice,
    int                             mnemonic			      
    );

void vnoticeSetOkHook(
    vnotice                        *notice,
    vnoticeHookProc	            okProc
    );

void vnoticeSetYesHook(
    vnotice                        *notice,
    vnoticeHookProc	            yesProc
    );

void vnoticeSetNoHook(
    vnotice                        *notice,
    vnoticeHookProc	            noProc
    );

void vnoticeSetCancelHook(
    vnotice                        *notice,
    vnoticeHookProc	            cancelProc
    );

void vnoticeSetHelpHook(
    vnotice                        *notice,
    vnoticeHookProc	            helpProc
    );

void vnoticeSetText(
    vnotice                        *notice,
    const vchar		           *text
    );

void vnoticeSetTextScribed(
    vnotice                        *notice,
    vscribe			   *scribe
    );

void vnoticeSetCaution(
    vnotice			   *notice,
    int				    flag
    );

void vnoticeSetCancel(
    vnotice                        *notice,
    int                             flag
    );

void vnoticeSetHelp(
    vnotice                        *notice,
    int                             flag
    );

void vnoticeSetIcon(
    vnotice                        *notice,
    vimage			   *icon
    );

vnoticeClass *vnoticeGetClass(
    vnotice                        *notice
    );

vconfirm *vnoticeGetConfirm(
    vnotice                        *notice
    );

vwindow *vnoticeGetWindow(
    vnotice                        *notice
    );

vdialog *vnoticeGetDialog(
    vnotice                        *notice
    );

void *vnoticeGetData(
    vnotice                        *notice
    );

int vnoticeIsOpen(
    vnotice                        *notice
    );

int vnoticeIsCaution(
    vnotice                        *notice
    );

int vnoticeHasCancel(
    vnotice                        *notice
    );

int vnoticeHasHelp(
    vnotice                        *notice
    );

vtextitem *vnoticeGetTextitem(
    vnotice                        *notice
    );

int vnoticeHasIcon(
    vnotice                        *notice
    );

vimage *vnoticeGetIcon(
    vnotice                        *notice
    );

const vchar *vnoticeGetOkTitle(
    vnotice                        *notice
    );

const vchar *vnoticeGetYesTitle(
    vnotice                        *notice
    );

const vchar *vnoticeGetNoTitle(
    vnotice                        *notice
    );

const vchar *vnoticeGetCancelTitle(
    vnotice                        *notice
    );

int vnoticeGetOkMnemonic(
    vnotice                        *notice
    );

int vnoticeGetYesMnemonic(
    vnotice                        *notice
    );

int vnoticeGetNoMnemonic(
    vnotice                        *notice
    );

int vnoticeGetCancelMnemonic(
    vnotice                        *notice
    );

vnoticeHookProc vnoticeGetOkHook(
    vnotice                        *notice
    );

vnoticeHookProc vnoticeGetYesHook(
    vnotice                        *notice
    );

vnoticeHookProc vnoticeGetNoHook(
    vnotice                        *notice
    );

vnoticeHookProc vnoticeGetCancelHook(
    vnotice                        *notice
    );

vnoticeHookProc vnoticeGetHelpHook(
    vnotice                        *notice
    );

vstr *vnoticeGetText(
    vnotice			   *notice
    );
    
vscribe *vnoticeGetTextScribed(
    vnotice			   *notice
    );
    
void vnoticeProcessStart(
    vnotice                        *notice
    );

const vname *vnoticeProcessGet(
    vnotice                        *notice
    );

void vnoticeProcessStop(
    vnotice                        *notice
    );

const vname *vnoticeProcess(
    vnotice                        *notice
    );


/*
 * * * * * * * * * * PRIVATE FUNCTION PROTOTYPES * * * * * * * * * *
 */

/*
 * * * * * * * * * FUNCTION DEFINED AS #define MACROS * * * * * * * * * *
 */

#define vnoticeGetConfirm(d)       vportBASE_OBJECT((d), confirm)

#define vnoticeCreateOfClass(c)                                         \
    ((vnotice*)vconfirmCreateOfClass((vconfirmClass*)(c)))
#define vnoticeCreate()                                                 \
    vnoticeCreateOfClass(vnoticeGetDefaultClass())
#define vnoticeClone(d)            ((vnotice*)vconfirmClone((vconfirm*)(d)))
#define vnoticeInitOfClass(d, c)                                        \
    vconfirmInitOfClass(vnoticeGetConfirm(d), (vconfirmClass*)(c))
#define vnoticeInit(d)                                                  \
    vnoticeInitOfClass(d, vnoticeGetDefaultClass())
#define vnoticeCopyInit(d, t)                                           \
    vconfirmCopyInit(vnoticeGetConfirm(d), vnoticeGetConfirm(t))
#define vnoticeLoad(r)             ((vnotice*)vconfirmLoad(r))
#define vnoticeLoadInit(d, r)      vconfirmLoadInit(vnoticeGetConfirm(d), r)
#define vnoticeDestroy(d) \
    vconfirmDestroy(vnoticeGetConfirm(d))

#define vnoticeGetWindow(d)        vconfirmGetWindow(vnoticeGetConfirm(d))
#define vnoticeGetDialog(d)        vconfirmGetDialog(vnoticeGetConfirm(d))
#define vnoticeGetClass(d)                                             \
    ((vnoticeClass*) vobjectGetClass((vobject *) (d)))
#define vnoticeGetData(d)          vconfirmGetData(vnoticeGetConfirm(d))
#define vnoticeIsOpen(d)           vconfirmIsOpen(vnoticeGetConfirm(d))
#define vnoticeGetOkTitle(d)       (vconfirmGetOkTitle(vnoticeGetConfirm(d)))
#define vnoticeGetYesTitle(d)      (vconfirmGetOkTitle(vnoticeGetConfirm(d)))
#define vnoticeGetNoTitle(d)       (vconfirmGetButtonTitle(vnoticeGetConfirm(d), \
				    vname_No))
#define vnoticeGetCancelTitle(d)   (vconfirmGetCancelTitle(vnoticeGetConfirm(d)))
#define vnoticeGetOkMnemonic(d)    (vconfirmGetOkMnemonic(vnoticeGetConfirm(d)))
#define vnoticeGetYesMnemonic(d)   (vconfirmGetOkMnemonic(vnoticeGetConfirm(d)))
#define vnoticeGetNoMnemonic(d)    (vconfirmGetButtonMnemonic(vnoticeGetConfirm(d), \
				    vname_No))
#define vnoticeGetCancelMnemonic(d) (vconfirmGetCancelMnemonic(vnoticeGetConfirm(d)))
#define vnoticeGetOkHook(d)        \
          ((vnoticeHookProc) (vconfirmGetApplyHook(vnoticeGetConfirm(d))))
#define vnoticeGetYesHook(d)       \
          ((vnoticeHookProc) (vconfirmGetApplyHook(vnoticeGetConfirm(d))))
#define vnoticeGetNoHook(d)        \
          ((vnoticeHookProc) (vconfirmGetGenericHook(vnoticeGetConfirm(d))))
#define vnoticeGetCancelHook(d)    \
          ((vnoticeHookProc) (vconfirmGetResetHook(vnoticeGetConfirm(d))))
#define vnoticeGetHelpHook(d)      \
          ((vnoticeHookProc) (vconfirmGetHelpHook(vnoticeGetConfirm(d))))
#define vnoticeHasIcon(d)          ((d)->icon!=0)
#define vnoticeGetIcon(d)          ((d)->icon)
#define vnoticeSetText(d, s)	   vnoticeSetTextScribed(d, vcharScribe(s))
#define vnoticeGetTextitem(d)      ((d)->textItem)
#define vnoticeIsCaution(d)        ((vconfirmGetButton(vnoticeGetConfirm(d),       \
						       vname_No) != NULL))
#define vnoticeHasCancel(d)        (vconfirmHasCancel(vnoticeGetConfirm(d)))
#define vnoticeSetHelp(d, f)       (vconfirmSetHelp(vnoticeGetConfirm(d), (f)))
#define vnoticeHasHelp(d)          (vconfirmHasHelp(vnoticeGetConfirm(d)))

#define vnoticePlace(d, b, x, y)   vconfirmPlace(vnoticeGetConfirm(d), b, x, y)
#define vnoticePlaceWindow(d, b, x, y)	\
    vconfirmPlaceWindow(vnoticeGetConfirm(d), b, x, y)

#define vnoticeProcessStart(n)     vconfirmProcessStart(vnoticeGetConfirm(n))
#define vnoticeProcessGet(n)       vconfirmProcessGet(vnoticeGetConfirm(n))
#define vnoticeProcessStop(n)      vconfirmProcessStop(vnoticeGetConfirm(n))
#define vnoticeProcess(n)          vconfirmProcess(vnoticeGetConfirm(n))

#define vnoticeGetText(n) vstrCloneScribed(vtextitemGetTextScribed((n)->textItem))
#define vnoticeGetTextScribed(n)   vtextitemGetTextScribed((n)->textItem)

#define vnoticeSetTitle(d, t)                                           \
  vnoticeSetTitleScribed(d, vcharScribe(t))

#define vnoticeSetNoTitle(d, t)   vnoticeSetNoTitleScribed((d), vcharScribe(t))

#define vnoticeSetCancelTitle(d, t)                                     \
  vnoticeSetCancelTitleScribed(d, ((t == NULL) ? (vscribe *)NULL : vcharScribe(t)))

/*
 * * * * * * * * * FUNCTION DEFINED AS MESSAGES * * * * * * * * * *
 */

#define vnoticeCopy(d, t) \
  vclassSend(vnoticeGetClass(d), vobjectCOPY, (d, t))
#define vnoticeStore(d, r) \
  vclassSend(vnoticeGetClass(d), vobjectSTORE, (d, r))
#define vnoticeOpen(d) \
  vclassSend(vnoticeGetClass(d), vwindowOPEN, (d))
#define vnoticeClose(d) \
  vclassSend(vnoticeGetClass(d), vwindowCLOSE, (d))
#define vnoticeSetData(d, p) \
  vclassSend(vnoticeGetClass(d), vwindowSET_DATA, (d, p))

#define vnoticeSetTitleScribed(d, t)                                    \
  vclassSend(vnoticeGetClass(d), vwindowSET_TITLE_SCRIBED, (d, t))

#define vnoticeSetTextScribed(d, t)                                     \
  vclassSend(vnoticeGetClass(d), vnoticeSET_TEXT_SCRIBED, (d, t))

#define vnoticeSetOkTitleScribed(d, t)                                  \
  vclassSend(vnoticeGetClass(d), vconfirmSET_OK_TITLE_SCRIBED, (d, t))

#define vnoticeSetOkTitle(d, t)                                         \
  vnoticeSetOkTitleScribed(d, ((t == NULL) ? (vscribe *)NULL : vcharScribe(t)))

#define vnoticeSetYesTitle(d, t)                                        \
  vnoticeSetOkTitle(d, t)

#define vnoticeSetOkMnemonic(d, m)                                      \
  vconfirmSetOkMnemonic(vnoticeGetConfirm(d), (m))

#define vnoticeSetYesMnemonic(d, m)                                     \
  vconfirmSetOkMnemonic(vnoticeGetConfirm(d), (m))

#define vnoticeSetCancelMnemonic(d, m)                                  \
  vconfirmSetCancelMnemonic(vnoticeGetConfirm(d), (m))

#define vnoticeSetOkHook(d, p)                                          \
  vconfirmSetApplyHook(vnoticeGetConfirm(d), (vconfirmHookProc)(p))

#define vnoticeSetYesHook(d, p)                                         \
  vconfirmSetApplyHook(vnoticeGetConfirm(d), (vconfirmHookProc)(p))

#define vnoticeSetNoHook(d, p)                                          \
  vconfirmSetGenericHook(vnoticeGetConfirm(d), (vconfirmHookProc)(p))

#define vnoticeSetCancelHook(d, p)                                      \
  vconfirmSetResetHook(vnoticeGetConfirm(d), (vconfirmHookProc)(p))

#define vnoticeSetHelpHook(d, p)                                        \
  vconfirmSetHelpHook(vnoticeGetConfirm(d), (vconfirmHookProc)(p))

#define vnoticeHandleYes(d, e)                                          \
    vclassSend(vnoticeGetClass(d), vnoticeHANDLE_YES, (d, e))
#define vnoticeHandleNo(d, e)                                           \
    vclassSend(vnoticeGetClass(d), vnoticeHANDLE_NO, (d, e))
#define vnoticeHandleCancel(d, e)                                       \
    vclassSend(vnoticeGetClass(d), vnoticeHANDLE_CANCEL, (d, e))

#define vnoticeSetYesTitleScribed(d, t)                                 \
    vclassSend(vnoticeGetClass(d), vnoticeSET_YES_TITLE_SCRIBED, (d, t))
#define vnoticeSetNoTitleScribed(d, t)                                 \
    vclassSend(vnoticeGetClass(d), vnoticeSET_NO_TITLE_SCRIBED, (d, t))
#define vnoticeSetCancelTitleScribed(d, t)                                 \
    vclassSend(vnoticeGetClass(d), vconfirmSET_CANCEL_TITLE_SCRIBED, (d, t))

#define vnoticeSetCaution(d, f) \
  vclassSend(vnoticeGetClass(d), vnoticeSET_CAUTION, (d, f))
#define vnoticeSetCancel(d, f) \
  vclassSend(vnoticeGetClass(d), vnoticeSET_CANCEL, (d, f))
#define vnoticeSetIcon(d, f) \
  vclassSend(vnoticeGetClass(d), vnoticeSET_ICON, (d, f))

vportEND_CPLUSPLUS_EXTERN_C

#endif /* #ifndef vnoticeINCLUDED */


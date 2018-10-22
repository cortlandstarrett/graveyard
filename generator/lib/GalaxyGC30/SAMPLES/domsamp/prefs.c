/* $Id: prefs.c,v 1.1 1994/10/19 00:50:56 gregt Exp $ */
/* prefs
 *
 * code for preferences confirm
 */

#include <vport.h>

#ifndef vdebugINCLUDED
#include vdebugHEADER
#endif

#ifndef vnameINCLUDED
#include vnameHEADER
#endif

#ifndef vdictINCLUDED
#include vdictHEADER
#endif

#ifndef veventINCLUDED
#include veventHEADER
#endif

#ifndef vclassINCLUDED
#include vclassHEADER
#endif

#ifndef vobjectINCLUDED
#include vobjectHEADER
#endif

#ifndef vcommandINCLUDED
#include vcommandHEADER
#endif

#ifndef vcolorINCLUDED
#include vcolorHEADER
#endif

#ifndef vfontINCLUDED
#include vfontHEADER
#endif

#ifndef vwindowINCLUDED
#include vwindowHEADER
#endif

#ifndef vdialogINCLUDED
#include vdialogHEADER
#endif

#ifndef vcontrolINCLUDED
#include vcontrolHEADER
#endif

#ifndef vconfirmINCLUDED
#include vconfirmHEADER
#endif

#ifndef vcolorchsrINCLUDED
#include vcolorchsrHEADER
#endif

#ifndef vfontchsrINCLUDED
#include vfontchsrHEADER
#endif

#include "domsamp.h"
#include "domres.h"

#if (vdebugDEBUG)
static const char _prefsTAG[] = "prefs";
#define vdebugTAG _prefsTAG
#endif

enum {
  comBG_COLOR_TOGGLE,
  comBG_COLOR_BUTTON,
  comSEL_COLOR_TOGGLE,
  comSEL_COLOR_BUTTON,
  comFONT_TOGGLE,
  comFONT_BUTTON,
  comCOUNT
};

static const vcommandSelectorTemplate comTemplate[] = {
  {"bgColorToggle", comBG_COLOR_TOGGLE},
  {"bgColorButton", comBG_COLOR_BUTTON},
  {"selColorToggle", comSEL_COLOR_TOGGLE},
  {"selColorButton", comSEL_COLOR_BUTTON},
  {"fontToggle", comFONT_TOGGLE},
  {"fontButton", comFONT_BUTTON}
};

static vcommandSpace *space;
static vcolorchsr *colchs;
static vfontchsr *fontchs;

void prefsOpen(vconfirm *conf)
{
  if (!vconfirmIsOpen(conf)) {
    myDomainView *mview = appDataGetMview(prefsGetAppData(conf));
    vdialogItem *btn;

    btn = vdialogFindItem(vconfirmGetDialog(conf), domres_bgColorButton);
    vdialogSetItemBackground(btn, vdialogGetItemBackground
				    (myDomainViewGetItem(mview)));
    btn = vdialogFindItem(vconfirmGetDialog(conf), domres_selColorButton);
    vdialogSetItemForeground(btn, myDomainViewGetSelColor(mview));
    btn = vdialogFindItem(vconfirmGetDialog(conf), domres_fontButton);
    vdialogSetItemFont(btn, vdialogGetItemFont(myDomainViewGetItem(mview)));
    vconfirmOpen(conf);
  } else
    vwindowRaise(vconfirmGetWindow(conf));
}

static void bgApply(vcolorchsr *chsr, vcolor *color)
{
  vdialogItem *btn;

  btn = (vdialogItem *) vcolorchsrGetData(chsr);
  vdialogSetItemBackground(btn, color);
}

static void selApply(vcolorchsr *chsr, vcolor *color)
{
  vdialogItem *btn;

  btn = (vdialogItem *) vcolorchsrGetData(chsr);
  vdialogSetItemForeground(btn, color);
}

static int fontApply(vfontchsr *chsr, vfont *font)
{
  vdialogItem *btn;

  btn = (vdialogItem *) vfontchsrGetData(chsr);
  vdialogSetItemFont(btn, font);
  return vTRUE;
}

static int prefsIssueFunc(vcommandSelector *com, vdict *context)
{
  int selector = vcommandGetSelector(com);
  vconfirm *conf = (vconfirm *) vdictLoad(context, vname_Dialog);
  myDomainView *mview;
  vdialogItem *btn;
  vbool toggleState;
  int retVal = vTRUE;

  vdebugTraceEnter(prefsIssueFunc);

  if (conf == NULL) {
    vdebugTraceClear();
    return vFALSE;
  }
  mview = appDataGetMview(prefsGetAppData(conf));
  toggleState = ((vname *) vdictLoad(context, vname_Toggle)) == vname_On ?
    vTRUE : vFALSE;

  vdebugMInform(("issuing %s\n", comTemplate[selector].name));
  switch (selector) {
  case comBG_COLOR_TOGGLE:
    vwindowPropagateChange(vconfirmGetWindow(conf), vname_State,
			   domres_bgColorButton,
			   toggleState ? vname_Enabled : vname_Disabled);
    if (!toggleState) {
      vdialogItem *btn = vdialogFindItem(vconfirmGetDialog(conf),
					 domres_bgColorButton);

      vdialogSetItemBackground(btn, NULL);
    }
    break;
  case comBG_COLOR_BUTTON:
    vcolorchsrSetApply(colchs, bgApply);
    btn = (vdialogItem *) vdictLoad(context, vname_Operator);
    vcolorchsrSetData(colchs, (void *) btn);
    vcolorchsrSetColor(colchs, vdialogDetermineItemBackground(btn));
    vcolorchsrOpen(colchs);
    break;
  case comSEL_COLOR_TOGGLE:
    vwindowPropagateChange(vconfirmGetWindow(conf), vname_State,
			   domres_selColorButton,
			   toggleState ? vname_Enabled : vname_Disabled);
    if (!toggleState) {
      vdialogItem *btn = vdialogFindItem(vconfirmGetDialog(conf),
					 domres_selColorButton);

      vdialogSetItemForeground(btn, NULL);
    }
    break;
  case comSEL_COLOR_BUTTON:
    vcolorchsrSetApply(colchs, selApply);
    btn = (vdialogItem *) vdictLoad(context, vname_Operator);
    vcolorchsrSetData(colchs, (void *) btn);
    vcolorchsrSetColor(colchs, vdialogDetermineItemForeground(btn));
    vcolorchsrOpen(colchs);
    break;
  case comFONT_TOGGLE:
    vwindowPropagateChange(vconfirmGetWindow(conf), vname_State,
			   domres_fontButton,
			   toggleState ? vname_Enabled : vname_Disabled);
    if (!toggleState) {
      vdialogItem *btn = vdialogFindItem(vconfirmGetDialog(conf),
					 domres_fontButton);

      vdialogSetItemFont(btn, NULL);
    }
    break;
  case comFONT_BUTTON:
    vfontchsrSetApply(fontchs, fontApply);
    btn = (vdialogItem *) vdictLoad(context, vname_Operator);
    vfontchsrSetData(fontchs, (void *) btn);
    vfontchsrSetFont(fontchs, vdialogDetermineItemFont(btn));
    vfontchsrOpen(fontchs);
    break;
  default:
    retVal = vFALSE;
    break;
  }

  vdebugTraceLeave();
  return retVal;
}

static int prefsQueryFunc(vcommandSelector *com, vdict *context)
{
  int selector = vcommandGetSelector(com);
  vconfirm *conf = (vconfirm *) vdictLoad(context, vname_Dialog);
  vdialogItem *btn;
  vcontrol *tog;
  vbool retVal = vTRUE;

  vdebugTraceEnter(prefsQueryFunc);

  vdebugMInform(("querying %s\n", comTemplate[selector].name));
  switch (selector) {
  case comBG_COLOR_TOGGLE:
    btn = vdialogFindItem(vconfirmGetDialog(conf), domres_bgColorButton);
    vdictStore(context, vname_Toggle, vdialogGetItemBackground(btn) ?
	       vname_On : vname_Off);
    break;
  case comBG_COLOR_BUTTON:
    tog = (vcontrol *) vdialogFindItem(vconfirmGetDialog(conf), domres_bgColorToggle);
    vdictStore(context, vname_State, vcontrolGetValue(tog) ?
	       vname_Enabled : vname_Disabled);
    break;
  case comSEL_COLOR_TOGGLE:
    btn = vdialogFindItem(vconfirmGetDialog(conf), domres_selColorButton);
    vdictStore(context, vname_Toggle, vdialogGetItemForeground(btn) ?
	       vname_On : vname_Off);
    break;
  case comSEL_COLOR_BUTTON:
    tog = (vcontrol *) vdialogFindItem(vconfirmGetDialog(conf), domres_selColorToggle);
    vdictStore(context, vname_State, vcontrolGetValue(tog) ?
	       vname_Enabled : vname_Disabled);
    break;
  case comFONT_TOGGLE:
    btn = vdialogFindItem(vconfirmGetDialog(conf), domres_fontButton);
    vdictStore(context, vname_Toggle, vdialogGetItemFont(btn) ?
	       vname_On : vname_Off);
    break;
  case comFONT_BUTTON:
    tog = (vcontrol *) vdialogFindItem(vconfirmGetDialog(conf), domres_fontToggle);
    vdictStore(context, vname_State, vcontrolGetValue(tog) ?
	       vname_Enabled : vname_Disabled);
    break;
  default:
    retVal = vFALSE;
    break;
  }
  vdebugTraceLeave();
  return retVal;
}

static int applyPrefs(vconfirm *conf, vevent *event)
{
  myDomainView *mview = appDataGetMview(prefsGetAppData(conf));
  vdialogItem *btn;

  vdebugTraceEnter(applyPrefs);

  btn = vdialogFindItem(vconfirmGetDialog(conf), domres_bgColorButton);
  vdialogSetItemBackground(myDomainViewGetItem(mview),
			   vdialogGetItemBackground(btn));
  btn = vdialogFindItem(vconfirmGetDialog(conf), domres_selColorButton);
  myDomainViewSetSelColor(mview, vdialogGetItemForeground(btn));
  btn = vdialogFindItem(vconfirmGetDialog(conf), domres_fontButton);
  vdialogSetItemFont(myDomainViewGetItem(mview), vdialogGetItemFont(btn));

  vdebugTraceLeave();
  return vTRUE;
}

void prefsSetup(vconfirm *conf)
{
  vcommandSelectorClass *selClass;
  vdict *comDict;

  space = vcommandCreateSpace();
  vwindowSetSpaceOwned(vconfirmGetWindow(conf), space);
  selClass = vclassReproduce(vobjectGetCommandClass());
  vclassSet(selClass, vcommandISSUE, prefsIssueFunc);
  vclassSet(selClass, vcommandQUERY, prefsQueryFunc);
  comDict = vcommandCreateDictOfClassSelectorTemplates(selClass,
						       comTemplate,
						       comCOUNT);
  vcommandAddSpaceDictOwned(space, vname_Command, comDict);

  colchs = vcolorchsrCreate();
  fontchs = vfontchsrCreate();
  vconfirmSetApplyHook(conf, applyPrefs);
}

void prefsShutdown(vconfirm *conf)
{
  vcolorchsrDestroy(colchs);
  vfontchsrDestroy(fontchs);
}

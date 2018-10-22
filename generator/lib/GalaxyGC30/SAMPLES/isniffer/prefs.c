/* $Id: prefs.c,v 1.3 1996/08/21 15:52:23 david Exp $ */
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
 *                       isniffer preferences routines                      *
 *                                                                          *
 ****************************************************************************
 */

/* for v*HEADER */
#include <vport.h>

/* ANSI headers */
#include vstdioHEADER
#include vstdlibHEADER

/* Galaxy headers */
#include vdebugHEADER
#include vexHEADER
#include vmemHEADER
#include vcharHEADER
#include vnameHEADER
#include vdictHEADER
#include vfsHEADER
#include vscrapHEADER
#include vresourceHEADER
#include veventHEADER
#include vcommandHEADER
#include vprefHEADER
#include vnumHEADER
#include vobjectHEADER
#include vwindowHEADER
#include vdialogHEADER
#include vconfirmHEADER
#include vcontainerHEADER

/* Our headers */
#include "iman.h"
#include "names.h"
#include "com.h"
#include "isnf.h"
#include "utils.h"
#include "view.h"


/* Define our debug tag for vdebug manager */
#if vdebugDEBUG
static const char *const _moduleTag = "prefs";
#define vdebugTAG _moduleTag
#endif


/*
 *+------------------------------------------------------------------------+
 * private constants, variables, prototypes
 *+------------------------------------------------------------------------+
 */

/*
 * This is the actual "open" preferences chooza command information
 */

static int prefsOpenChooza(vcommandFunction*, vdict*);

static appFunctionCmd fcmds[]= {
  {{appNAME_ACT_ADJUST_PREFS, 1,1, vkeyNULL_STROKE}, prefsOpenChooza, NULL},
  {{-1},NULL}
};



/*
 * The following stuffage deals w/ the preferences chooza itself. These
 * commands are part of the chooza's command space -- not the toplevel
 * application command space...
 */

enum {
  prefSNIFF_RECURSIVE,
  prefSNIFF_ALL_COMPOSITE,
  prefSHOW_THUMBNAILS,
  prefFULL_TITLES,
  prefTHUMB_SIZE,
  prefPRINT_HEADER, 
  prefPRINT_FOOTER,
  prefPRINT_BORDER,
  prefPRINT_PAGE_NOS,
  prefPRINT_ERRATA
};

static appSelectorCmd scmds[]= {
  {{appNAME_PREF_RECUR, 0,0, vkeyNULL_STROKE}, prefSNIFF_RECURSIVE},
  {{appNAME_PREF_ALL,   0,0, vkeyNULL_STROKE}, prefSNIFF_ALL_COMPOSITE},
  {{appNAME_PREF_THUMBNAILS, 0,0, vkeyNULL_STROKE}, prefSHOW_THUMBNAILS},
  {{appNAME_PREF_TITLES, 0,0, vkeyNULL_STROKE}, prefFULL_TITLES},
  {{appNAME_PREF_THUMBSIZE, 0,0, vkeyNULL_STROKE}, prefTHUMB_SIZE},
  {{appNAME_PREF_HEADER, 0,0, vkeyNULL_STROKE}, prefPRINT_HEADER},
  {{appNAME_PREF_FOOTER, 0,0, vkeyNULL_STROKE}, prefPRINT_FOOTER},
  {{appNAME_PREF_BORDER, 0,0, vkeyNULL_STROKE}, prefPRINT_BORDER},
  {{appNAME_PREF_PAGENOS, 0,0, vkeyNULL_STROKE}, prefPRINT_PAGE_NOS},
  {{appNAME_PREF_ERRATA, 0,0, vkeyNULL_STROKE}, prefPRINT_ERRATA},
  {{-1}}
};

static int prefsAcceptOption(vcommandSelector*, vdict*);
static int prefsQueryOption(vcommandSelector*, vdict*);
static int prefsAcceptNew(vconfirm*, vevent*);
static int prefsResetDefaults(vconfirm*, vevent*);
static int prefsCancel(vconfirm*, vevent*);
static void prefsCheckTempFolder(isnifferApp*);
static void prefsUpdateBoolean(int, int);
static void prefsUpdateInteger(int, int);



/*
 * Default preferences settings -- could rely on the the settings
 * in the resource file?
 */
static int initialized= vFALSE;
static isnifferPrefs defaultPrefs= {
  {
    isnfH_ITEM_MARGIN, isnfV_ITEM_MARGIN, isnfH_PAGE_MARGIN, isnfV_PAGE_MARGIN,
    NULL  /* font => viewer module decides */, 
    1     /* border linewidth */, 
    vTRUE /* borders */, vTRUE /* header */, vTRUE /* page numbers */,
    vTRUE /* file names etc, */
  },
  vTRUE,  /* all */
  vTRUE,  /* recursive */
  vTRUE,  /* show thumbnails */
  vTRUE,  /* show full titles */
  vFALSE, /* user-specified thumbnail size*/
  0,      /* thumbnail size [ignored] */
  NULL    /* preferences dialuug */
};
static isnifferPrefs prefs,           /* being changed (not accepted) */
                     immutable_prefs; /* definitely accepted by user  */


/*
 *+------------------------------------------------------------------------+
 * exported routines
 *+------------------------------------------------------------------------+
 */

/********
 * isnfGetPreferences()
 *
 * -> void 
 * <- global isniffer preferences
 *********/
const isnifferPrefs*
isnfGetPreferences(void)
{
  if (!initialized)
    isnfStartupPreferences(isnfGet());
  return &immutable_prefs;
}



/********
 * isnfStartupPreferences() initializes the preferences module. 
 * basically reads/stores the session's preferences st. application
 * commands can use in layout, queries, etc. Must be called before
 * main requestor window opened 1st time!
 *
 * -> app, the application
 * <- void
 *********/
void isnfStartupPreferences(isnifferApp *app)
{
  const vchar *volatile v;

  /* woop. been here. seen it. bought the t-shirt */
  if (initialized)
    return;

  /* first load with defaults */
  vprefSetPreferences(vapplicationGetPreferences(app->app));
  prefs = defaultPrefs;

  /* check the temporary folder preferences */
  prefsCheckTempFolder(app);

  /* sniffage options [recursive,all-compound-types] */
  if ((v=vprefLoad(appname_Recursive))) {
    if (vcharCompare(v, vname_On)==0) {
      prefs.recursive= vTRUE;
      if ((v=vprefLoad(appname_AllCompound)))
	prefs.all = vcharCompare(v, vname_On)==0;
    }
    else {
      prefs.recursive= vFALSE;
      prefs.all= vFALSE;
    }
  }
  else {
    prefs.recursive= vFALSE;
    prefs.all= vFALSE;
  }


  /* thumbnails */
  if ((v=vprefLoad(appname_Thumbnails)))
    prefs.thumbnails = vcharCompare(v, vname_On)==0;
  else
    prefs.thumbnails = vFALSE;


  /* full titles */
  if ((v=vprefLoad(appname_FullTitles)))
    prefs.titles = vcharCompare(v, vname_On)==0;
  else
    prefs.titles = vFALSE;


  /* thumbnail size */
  if ((v=vprefLoad(appname_ThumbsizeActual))) {
    vexWITH_HANDLING
    {
      int n = vnumParseInt(v, NULL);
      if (n>=isnfMIN_THUMBSIZE && n<=isnfMAX_THUMBSIZE) {
	prefs.diff_thumbsize = vTRUE;
	prefs.thumbsize = (short)n;
      }
      else
	prefs.diff_thumbsize = vFALSE;
    }
    vexON_EXCEPTION
    {
      vdebugBE(vexDumpChain(vdebugGetWarningStream()));
      vexClear();
    }
    vexEND_HANDLING;
  }
  else
    prefs.diff_thumbsize = vFALSE;

  /* printing preferences [header,pages,border,etc.] */ 
  if ((v=vprefLoad(appname_Border)))
    prefs.pp.border = vcharCompare(v, vname_On)==0;
  else prefs.pp.border = vFALSE;
  if ((v=vprefLoad(appname_Header)))
    prefs.pp.header = vcharCompare(v, vname_On)==0;
  else prefs.pp.header = vFALSE;
  if ((v=vprefLoad(appname_PageNos)))
    prefs.pp.number = vcharCompare(v, vname_On)==0;
  else prefs.pp.number = vFALSE;
  if ((v=vprefLoad(appname_Errata)))
    prefs.pp.extra =  vcharCompare(v, vname_On)==0;
  else prefs.pp.extra = vFALSE;

  immutable_prefs = prefs;
  initialized = vTRUE;
}


/********
 * isnfStartupPreferencesChooza adds the preference chooza toplevel command 
 * to the application's command space. Call after initializing module!
 *
 * -> app, the application
 * <- void
 *********/
void
isnfStartupPreferencesChooza(isnifferApp *app)
{
  appAddFunctionsToCommandSpaceDescription
             (isnfGetCommandSpaceDescription(), fcmds);
}


/********
 * isnfShutdownPreferences permanently stores this session's
 * preferences to disk and cleans up any module-allocated stuffage.
 *
 * -> app, the application
 * <- void
 *********/
void
isnfShutdownPreferences(isnifferApp *app)
{
  /*
   * We use the new preference mangler stuff for demo purposes.
   * Usually for simple boolean preferences like these, the old API is
   * quite adequate; more complex preferences (like fonts/images/etc.)
   * should use the new vpref API.
   */
  prefsUpdateBoolean(appNAME_PREF_RECUR, immutable_prefs.recursive);
  prefsUpdateBoolean(appNAME_PREF_ALL, immutable_prefs.all);
  prefsUpdateBoolean(appNAME_PREF_THUMBNAILS, immutable_prefs.thumbnails);
  prefsUpdateBoolean(appNAME_PREF_TITLES, immutable_prefs.titles);
  prefsUpdateBoolean(appNAME_PREF_BORDER, immutable_prefs.pp.border);
  prefsUpdateBoolean(appNAME_PREF_HEADER, immutable_prefs.pp.header);
  prefsUpdateBoolean(appNAME_PREF_PAGENOS, immutable_prefs.pp.number);
  prefsUpdateBoolean(appNAME_PREF_ERRATA, immutable_prefs.pp.extra);
  prefsUpdateInteger(appNAME_PREF_THUMBSIZE_ACTUAL, 
    immutable_prefs.diff_thumbsize ? immutable_prefs.thumbsize : 0);

#if vmemBALANCE
  if (prefs.conf)
    vconfirmDestroy(prefs.conf);
#endif
}



/*
 *+------------------------------------------------------------------------+
 * private:
 *+------------------------------------------------------------------------+
 */

/********
 * updateAvailable, updateValue
 *
 * -> window,    the confirm window
 * -> tag,       command's tag
 * -> condition, [t/f] 
 * <- void
 *********/

#define updateAvailable(_w, _c, _b) \
  vwindowPropagateChange(_w, vname_State, _c, \
			 (_b) ? vname_Enabled : vname_Disabled)
#define updateValue(_w, _c, _b) \
  vwindowPropagateChange(_w, vname_Toggle, _c, \
			 (_b) ? vname_On : vname_Off)


/********
 * getThumbsizeField returns the thumbsize text input field from the
 * prefs chooza window...
 *
 * -> void 
 * <- item, the text input field
 *********/
static vdialogItem*
getThumbsizeField(void)
{
  register vdialogItem *item;
  item = vdialogFindItem(vconfirmGetDialog(prefs.conf), 
			 vnameInternGlobalLiteral("cViewOptions"));
  item = vcontainerFindItem((vcontainer*)item, appname_ThumbsizeActual);

  vdebugIF(!item, vexGenerate(vexGetReturnNullClass(), vexMESSAGE,
           "cannot locate thumbsize text input field!", vexERRNO, 0, 
			      vexNULL));
  return item;
}

/********
 * prefsSelectorClass defines the all-in-one selector command class
 * we use in the preferences chooza dialuug
 *
 * -> void 
 * <- clas, the command selector class reference
 *********/
static vcommandSelectorClass*
prefsSelectorClass(void)
{
  static vcommandSelectorClass *_clas = NULL;

  if (!_clas) {
    register vcommandSelectorClass *clas;
    clas = vclassReproduce(vobjectGetCommandClass());
    vclassSet(clas, vcommandISSUE, prefsAcceptOption);
    vclassSet(clas, vcommandQUERY, prefsQueryOption);
   _clas = clas;
  }

  return _clas;
}


/********
 * prefsOpenChooza opens the isniffer preferences editor/chooza/
 * window/spam. called when the user finds the magic cookie menu.
 *
 * -> com, the open chooza command
 * -> context, the command's context
 * <- TRUE
 *********/
static int 
prefsOpenChooza(vcommandFunction *com, vdict *context)
{

  /* already allocated; just make sure visible */
  if (prefs.conf) {
    if (!vdialogIsOpen(vconfirmGetDialog(prefs.conf)))
      vconfirmOpen(prefs.conf);
    else {
      if (!vwindowIsVisible(vconfirmGetWindow(prefs.conf)))
	vwindowUniconify(vconfirmGetWindow(prefs.conf));
      vwindowRaise(vconfirmGetWindow(prefs.conf));
    }
  }

  /* open for ze first time */
  else {
    vresource res;
    appCommandSpace aspace;

    res = vresourceGet(isnfGet()->resources, appname_PrefsDialog);
    prefs.conf = vconfirmLoad(res);
    vconfirmSetApplyHook(prefs.conf, prefsAcceptNew);
    vconfirmSetDefaultsHook(prefs.conf, prefsResetDefaults);
    vconfirmSetResetHook(prefs.conf, prefsCancel);

    appInitCommandSpaceDescription(vcommandCreateSpace(), &aspace);
    vwindowSetSpaceOwned(vconfirmGetWindow(prefs.conf), aspace.space);
    appAddSelectorsToCommandSpaceDescription
                          (&aspace, scmds, prefsSelectorClass());
    appCommitCommandSpaceDescription(&aspace);

    vconfirmPlace(prefs.conf, isnfGet()->requestor, 
	vrectPLACE_RIGHT|vrectPLACE_INSET, vrectPLACE_TOP|vrectPLACE_INSET);
    vconfirmOpen(prefs.conf);

    immutable_prefs.conf = prefs.conf;
  }

  return vTRUE;
}


/********
 * prefsAcceptNew called when the user selects OK or Apply from the
 * the preferences chooza. Commits any preferences changes. (ie. reset
 * will go back to these settings.)
 *
 * -> confirm, the chooza
 * -> event,   the event
 * <- TRUE
 *********/
static int 
prefsAcceptNew(vconfirm *conf, vevent *event)
{
  int volatile redrum= vFALSE;

  if (prefs.diff_thumbsize)
    vexWITH_HANDLING {
      int thumbsize = vtextitemGetTextAsInt((vtextitem*)getThumbsizeField);
      if (thumbsize>isnfMAX_THUMBSIZE)
	thumbsize = isnfMAX_THUMBSIZE;
      if (thumbsize<isnfMIN_THUMBSIZE)
	redrum = vTRUE;
      else
	prefs.thumbsize = (short)thumbsize;
    } vexON_EXCEPTION {
        vdebugBE(vexDumpChain(vdebugGetWarningStream()));
	redrum = vTRUE;
	vexClear();
    } vexEND_HANDLING;

  if (redrum) {
    isnfInformUser(msgInvalidThumbsize, vconfirmGetDialog(conf));
    return vFALSE;
  }
  else {
    immutable_prefs = prefs;
    return vTRUE;
  }
}



/********
 * prefsResetDefaults called when the user selects Reset from the 
 * preferences chooza. Resets the settings to their last commited
 * state (see immutable_prefs).
 *
 * -> confirm, the chooza
 * -> event,   the triggering event
 * <- TRUE
 *********/
static int 
prefsResetDefaults(vconfirm *conf, vevent *event)
{
  vdict			value_dict, state_dict;
  vdict			context;
  vcommandSelector	fake_com;
  const appSelectorCmd  *scan;
  const void		*v;

  prefs = immutable_prefs;

  vcommandInitSelectorOfClass(&fake_com, prefsSelectorClass());
  vdictInit(&value_dict, vnameHash);
  vdictInit(&state_dict, vnameHash);
  vdictInit(&context,    vnameHash);

  for (scan=scmds; scan->cmd.name>=0; scan++) {
    vdictStore(&context, vname_State, NULL);
    vcommandSetSelector(&fake_com, scan->selector);
    prefsQueryOption(&fake_com, &context);

    v = vdictLoad(&context, vname_Toggle);
    vdictStore(&value_dict, appName(scan->cmd.name), v);
    v = vdictLoad(&context, vname_State);
    if (v) vdictStore(&state_dict, appName(scan->cmd.name), v);
  }

  vwindowPropagateChangeDict(vconfirmGetWindow(prefs.conf), vname_Toggle, 
			     &value_dict);
  vwindowPropagateChangeDict(vconfirmGetWindow(prefs.conf), vname_State,
			     &state_dict);

  vdictDestroy(&context);
  vdictDestroy(&state_dict), vdictDestroy(&value_dict);
  vcommandDestroy(vcommandGetSelectorCommand(&fake_com));

  return vTRUE;
}


/********
 * prefsCancel called when the user selects Cancel from the
 * preferences chooza. Resets the settings to their last commited
 * state (see immutable_prefs). 
 *
 * -> confirm, the chooza
 * -> event,   the triggering event
 * <- TRUE
 *********/
static int
prefsCancel(vconfirm *conf, vevent *event)
{
  prefs = immutable_prefs;
  return vTRUE;
}



/********
 * prefsAcceptOption called when user selects/changes option in chooza.
 * updates the mutable preferences structure to match new setting(s). 
 *
 * -> com,     the command
 * -> context, the command's context
 * <- TRUE
 *********/
static int
prefsAcceptOption(vcommandSelector *com, vdict *context)
{
  register const vname	*toggled;
  int			 handled= vTRUE;
  vwindow		*window = vconfirmGetWindow(prefs.conf);

  switch (vcommandGetSelector(com)) 	{
    case prefSNIFF_RECURSIVE: 		{
      if ((toggled= (const vname*)vdictLoad(context, vname_Toggle))) {
	prefs.recursive = (toggled==vname_On);
	updateAvailable(window, appname_AllCompound, prefs.recursive);
      }
      break;
    }
    case prefSNIFF_ALL_COMPOSITE: 	{
      if ((toggled= (const vname*)vdictLoad(context, vname_Toggle))) {
	prefs.all = (toggled==vname_On);
      }
      break;
    }
    case prefSHOW_THUMBNAILS:		{
      if ((toggled= (const vname*)vdictLoad(context, vname_Toggle))) {
	prefs.thumbnails = (toggled==vname_On);
      }
      break;
    }
    case prefFULL_TITLES:		{
      if ((toggled= (const vname*)vdictLoad(context, vname_Toggle))) {
	prefs.titles = (toggled==vname_On);
      }
      break;
    }
    case prefTHUMB_SIZE:		{
      if ((toggled= (const vname*)vdictLoad(context, vname_Toggle))) {
	prefs.diff_thumbsize = (toggled==vname_On);
	updateAvailable(window, appname_ThumbsizeActual, prefs.diff_thumbsize);
      }
      break;
    }
    case prefPRINT_HEADER:		{
      if ((toggled= (const vname*)vdictLoad(context, vname_Toggle))) {
	prefs.pp.header = (toggled==vname_On);
      }
      break;
    }
    case prefPRINT_FOOTER:		{
      if ((toggled= (const vname*)vdictLoad(context, vname_Toggle))) {
	prefs.pp.header = (toggled==vname_Off);
      }
      break;
    }
    case prefPRINT_BORDER:		{
      if ((toggled= (const vname*)vdictLoad(context, vname_Toggle))) {
	prefs.pp.border = (toggled==vname_On);
      }
      break;
    }
    case prefPRINT_PAGE_NOS:		{
      if ((toggled= (const vname*)vdictLoad(context, vname_Toggle))) {
	prefs.pp.number = (toggled==vname_On);
      }
      break;
    }
    case prefPRINT_ERRATA:		{
      if ((toggled= (const vname*)vdictLoad(context, vname_Toggle))) {
	prefs.pp.extra = (toggled==vname_On);
      }
      break;
    }
    default: {
      handled = vFALSE;
    }
  }/*switch*/

  return handled;
}



/********
 * prefsQueryOption is called to determined attributt bindings for some
 * chooza ui items. (only those w/ matching selector values.)
 *
 * -> com,     the selector command
 * -> context, the context to fill in
 * <- TRUE
 *********/
static int
prefsQueryOption(vcommandSelector *com, vdict *context)
{
  int			 handled= vTRUE;

  switch (vcommandGetSelector(com)) 	{
    case prefSNIFF_RECURSIVE: 		{
      vdictStore(context, vname_Toggle, prefs.recursive ? vname_On 
		 : vname_Off);
      break;
    }
    case prefSNIFF_ALL_COMPOSITE: 	{
      vdictStore(context, vname_Toggle, prefs.all ? vname_On : vname_Off);
      vdictStore(context, vname_State, prefs.recursive ? vname_Enabled 
		 : vname_Disabled);
      break;
    }
    case prefSHOW_THUMBNAILS:		{
      vdictStore(context, vname_Toggle, prefs.thumbnails ? vname_On 
		 : vname_Off);
      break;
    }
    case prefFULL_TITLES:		{
      vdictStore(context, vname_Toggle, prefs.titles ? vname_On : vname_Off);
      break;
    }
    case prefTHUMB_SIZE:		{
      register vdialogItem *item;
      vdictStore(context, vname_Toggle, prefs.diff_thumbsize ? vname_On : vname_Off);
      item = getThumbsizeField();
      vtextitemSetTextScribed((vtextitem*)item, vnumScribeInt(prefs.thumbsize));
      if (prefs.diff_thumbsize) vdialogEnableItem(item);
      else vdialogDisableItem(item);
      break;
    }
    case prefPRINT_HEADER:		{
      vdictStore(context, vname_Toggle, prefs.pp.header ? vname_On 
		 : vname_Off);
      break;
    }
    case prefPRINT_FOOTER:		{
      vdictStore(context, vname_Toggle, prefs.pp.header ? vname_Off 
		 : vname_On);
      break;
    }
    case prefPRINT_BORDER:		{
      vdictStore(context, vname_Toggle, prefs.pp.border ? vname_On 
		 : vname_Off);
      break;
    }
    case prefPRINT_PAGE_NOS:		{
      vdictStore(context, vname_Toggle, prefs.pp.number ? vname_On
		 : vname_Off);
      break;
    }
    case prefPRINT_ERRATA:		{
      vdictStore(context, vname_Toggle, prefs.pp.extra ? vname_On
		 : vname_Off);
      break;
    }
    default: {
      handled = vFALSE;
    }
  }/*switch*/

  return handled;
}


/********
 * prefsUpdateSpecific writes the given scrap out to disk as the pref
 * matching application tag at index.
 *the 
 * -> index, the pref's name index in application name array
 * -> scrap, the pref's value in scrap form
 * <- void
 ********/
static void
prefsUpdateSpecific(int i, vscrap *scrap)
{
  register vprefDict *rd= vprefGetRootDict();
  register vprefValue *value;

  value = vprefValueCreate(scrap);
  vprefDictStorePref(rd, appName(i), vprefValueGetPref(value));
  if (isnfIsQuitting()) vprefDictWritePref(rd, appName(i));
  vprefValueRelease(value);
}

static void
prefsUpdateBoolean(int i, int b)
{
  prefsUpdateSpecific(i,vscrapFromBoolean(b));
}

static void
prefsUpdateInteger(int i, int v)
{
  prefsUpdateSpecific(i, vscrapFromInteger(v));
}


/********
 * prefsCheckTempFolder reads/process the -tempdir or -tempfolder
 * preference (for storing temp image files).
 *
 * -> void
 * <- void
 ********/
static void
prefsCheckTempFolder(register isnifferApp *app)
{
  const vchar	*v;

  /* process -tempdir|-tempfolder preference */
  if (((v=vprefLoad(appname_TempDir))|| (v=vprefLoad(appname_TempFolder)))
      && vcharCompareBase(v,TAG("None"))!=0) {
    app->tempdir = vfsPathFromStr(v);
    vfsMakePathCanonical(app->tempdir);
    if (vfsGetPathType(app->tempdir)!=vfsPATH_TYPE_FULL) {
      vfsPath *path;
      path = vfsResolvePath(vfsGetAppDirPath(), app->tempdir);
      vfsDestroyPath(app->tempdir);
      app->tempdir = path;
    }
    vexWITH_HANDLING {
      vfsInfo fi;
      app = isnfGet();
      vfsGetFileInfo(app->tempdir, &fi);
      if (!vfsIsDirectory(&fi))
	vexGenerateAbandon();
      else
      if (!vfsAccess(app->tempdir, vfsCAN_READ|vfsCAN_WRITE))
	vexGenerateAbandon();
    }
    vexON_EXCEPTION {
      app = isnfGet();
      if (app->tempdir)
	vfsDestroyPath(app->tempdir);
      app->tempdir = NULL;
    }
    vexEND_HANDLING;
  }
}


/*
  +-------------------------------------------------------------------------+
   formatting information for emacs in c-mode
  +-------------------------------------------------------------------------+
 */

/*
 * Local Variables:
 * c-indent-level:2
 * c-continued-statement-offset:2
 * c-brace-offset:0
 * c-brace-imaginary-offset:0
 * c-argdecl-indent:5
 * c-label-offset:0
 * c-tab-always-indent:nil
 * End:
 */

/********
 * xspam()
 *
 * ->
 * <-
 ********/

/* $Id: fontchs2.c,v 1.8 1996/08/21 15:45:23 david Exp $ */
/******************************************************************************
 *                   (c) Copyright 1994 Visix Software Inc.                   *
 *                            All rights reserved.                            *
 *                                                                            *
 *    The following Sample Code is provided for your reference purposes in    *
 *     connection with your use of the Galaxy Application Environment (TM)    *
 *     software product which you have licensed from Visix Software, Inc.     *
 * ("Visix"). The Sample code is provided to you without any warranty of any  *
 *     kind whatsoever and you agree to be responsible for the use and/or     *
 *   incorporation of the Sample Code into any software product you develop.  *
 *  You agree to fully and completely indemnify and hold Visix harmless from  *
 * any and all loss, claim, liability or damages with respect to your use of  *
 *    the Sample Code. Subject to the foregoing, you are permitted to copy,   *
 *   modify, and distribute the Sample Code for any purpose and without fee,  *
 * provided that (i) a copyright notice in the in the form of "Copyright 1992,*
 *  93 Visix Software Inc., 11440 Commerce Park Drive, Reston, VA  22091. All *
 * Rights Reserved" appears in all copies, (ii) both the copyright notice and *
 *  this permission notice appear in supporting documentation and (iii) you   *
 *            are a valid licensee of Galaxy Application Environment.         *
 *                                                                            *
 ******************************************************************************
 *                                                                            *
 * Description:                                                               *
 *    Using "fontchsr" as a basis, we've created a subclass of the standard   *
 *    galaxy font chooser that can filter out specific fonts, specific font   *
 *    families, or specific family face groups.                               *
 *                                                                            *
 *     Managers Used:                                                         *
 *         o Font Manager (vfont)                                             *
 *         o Font Chooser (vfontchsr)                                         *
 *         o Command Manager (vcommand)                                       *
 *                                                                            *
 *     Files Included:                                                        *
 *         o fontchs2.c, fontchs2.vr                                          *
 *                                                                            *
 * Modification History:                                                      *
 *     o 11-14-94: ssmc, created for Galaxy 2.1 release                       *
 *     o 03-08-95: ssmc, added filtering for rotated/scaled fonts             *
 *                                                                            *
 * Special Usage Notes:                                                       *
 *     o <none>                                                               *
 *                                                                            *
 * Text Editor Formatting:                                                    *
 *     Symantec: Tab(8), Font(Any Fixed Width)                                *
 *     Emacs: see end of file for info                                        *
 *                                                                            *
 ******************************************************************************
 */

#include <vport.h>		/* for v*HEADER */
#include vstdlibHEADER		/* for EXIT_* 	*/
#include vdebugHEADER
#include vscribeHEADER
#include vcharHEADER
#include vnameHEADER
#include vresourceHEADER
#include veventHEADER
#include vmatrixHEADER
#include vfontHEADER
#include vapplicationHEADER
#include vmenuHEADER
#include vdialogHEADER
#include vmenubarHEADER
#include vconfirmHEADER
#include vnumHEADER
#include vfontchsrHEADER
#include vstartupHEADER


/*
 * Zzzz...In a perfect world these should be part of the font chizler
 * subclass' definiton :)
 */
enum {
  optionNONE= 0x01,
  optionMONO= 0x02,
  optionLATIN1= 0x04,
  optionEVEN= 0x08,
  optionBOLDFACE= 0x10,
  optionUNROTATED= 0x20,
  optionSQUARE= 0x40
};


/*
 * selector command values
 */
enum {
  comCHK_MONOSPACE,
  comCHK_LATIN1,
  comCHK_EVEN_ODD,
  comCHK_CUSTOM_FONTS,
  comCHK_BOLD_FACES,
  comCHK_UNROTATED_FONTS,
  comCHK_SQUARE_FONTS,
  comCHK_GROUP_COUNT,
  comCHK_REMOVE_ALL = comCHK_GROUP_COUNT
};


/*
 * command tag literals
 */
#define COM_LATIN1	        "cOnlyLatin1"
#define COM_MONOSPACE	        "cOnlyMono"
#define COM_ODD_EVEN	        "cOnlyEven"
#define COM_CUSTOM_FONTS	"cAllowCustom"
#define COM_BOLD_FACES		"cOnlyBold"
#define COM_UNROTATED		"cOnlyUpright"
#define COM_SQUARE		"cOnlySquare"
#define COM_REMOVE_ALL		"cRemoveAll"
#define COM_MANGLE_FONT		"cMangleFont"
#define COM_QUIT		"Quit"		/* vname_Quit 	*/
#define COM_ABOUT		"About"		/* vname_About 	*/
#define COM_PICK_FONT		"cPickFont"
#define COM_CLOSE		"Close"		/* vname_Close	*/



/*
 * misc utils
 */
#define TAG(l)     vnameInternGlobalLiteral(l)
#define SCRIBE(l)  vcharScribeLiteral(l)
#define isOpen()   (gChsr && vdialogIsOpen(vfontchsrGetDialog(gChsr)))
#define getInfo(c) ((chooserInfo*)vfontchsrGetData(c))



/*
 * to track oft-used items
 */
typedef struct chooserInfo {
    vdialogItem	*fontDescription;
    vdialogItem	*irsLabel;
}chooserInfo;


/*
 * globals, pseudo constants
 */
static vfontchsrClass		*gChsrClass= NULL;
static vcommandSelectorClass	*gCmdClas = NULL;
static const vname              *gChkGroup[comCHK_GROUP_COUNT]={0};
static unsigned			 Once= 0;

static vdialog			*gDialog   = NULL;
static vfontchsr		*gChsr     = NULL;
static unsigned short		 gOptions  = 0;
static vdict			*gDict     = NULL;  /* state dict*/
static vconfirm			*gAboutBox = NULL;
static const vname		*name_latin1;
static const vname		*name_bold, *name_Bold;

static vfontchsr		*makeChooser(void);



/********
 * doQuit()
 * 	Abandon ship. Stop processing all events. Return to main().
 *
 * -> command context info
 * <- true
 ********/
static int
doQuit(vcommandFunction *com, vdict *context)
{
  veventStopProcessing();
  return vTRUE;
}



/********
 * doAbout()
 *	Show help window for our sample (explains the options)
 *
 * -> command context info <yawn>
 * <- true
 ********/
static int
doAbout(vcommandFunction *com, vdict *context)
{
  if (!gAboutBox)
    {
      vresource res;

      res = vresourceGet(vapplicationGetResources(vapplicationGetCurrent()), 
			 TAG("aOverview"));
      gAboutBox = vconfirmLoad(res);

      vconfirmSetCancel(gAboutBox, vFALSE);
      vconfirmSetOverride(gAboutBox, vTRUE);
      vconfirmSetOkTitleScribed(gAboutBox, vnameScribeGlobal(vname_Close));

      vconfirmPlace(gAboutBox, gDialog, vrectPLACE_CENTER,vrectPLACE_CENTER);
    }

  if (!vdialogIsOpen(vconfirmGetDialog(gAboutBox)))
    vconfirmOpen(gAboutBox);

  else {
    vwindowUniconify(vconfirmGetWindow(gAboutBox));
    vwindowRaise(vconfirmGetWindow(gAboutBox));
  }

  return vTRUE;
}



/********
 * doPickFont()
 *	Show our font chooser for user selection. Will create
 *	new chooser if 1st time.
 *
 * -> command context info
 * <- true
 ********/
static int
doPickFont(vcommandFunction *com, vdict *context)
{
  if (isOpen())
    {
      vwindowUniconify(vdialogGetWindow(vfontchsrGetDialog(gChsr)));
      vwindowRaise(vdialogGetWindow(vfontchsrGetDialog(gChsr)));
    }
  else
    {
      if (!gChsr) gChsr = makeChooser();
      vfontchsrOpen(gChsr);
    }

  return vTRUE;
}


/********
 * setFont()
 *	Called when user makes selection from the font chooser.
 *	Update the main dialog's label item w/ new font description.
 *
 * -> font chooser
 * -> user's font selection
 * <- true
 ********/
static int
setFont(vfontchsr *chsr, vfont *choice)
{
  chooserInfo	*info;
  vfontFace	*face;
  vscribe	*scribe, *sizeScribe;

  /*
   * This was stored when vfontchsr created
   */
  info = getInfo(chsr);


  /*
   * Create a title like: "Family: Courier, Face: Bold, Size: 12pt"
   */
  face = vfontGetFace(choice);

  sizeScribe = vnumScribeFloat(vfontFGetSize(choice));
  vnumSetScribeDigitsAfter(sizeScribe, 2); 

  scribe = vscribeScribeMulti
    (SCRIBE("Family: "),
     vnameScribeGlobal(vfontGetFamilyName(vfontGetFaceFamily(face))),
     SCRIBE(", Face: "),
     vnameScribeGlobal(vfontGetFaceName(face)),
     SCRIBE(", Size: "),
     sizeScribe,
     SCRIBE("pt"),
     NULL
     );

  /*
   * Update the label's font and title to reflect choice
   */
  vdialogSetItemFont(info->fontDescription, choice);
  vdialogSetItemTitleScribed(info->fontDescription, scribe);


  /*
   * Since rotated/scaled fonts might get clipped; tell user this
   * info in another way...
   */
  if (!vfontIsUpright(choice) || !vfontIsSquare(choice)) {
    vchar str[vmatrixSTRING_MAX+9];
    (void)vcharCopyScribed(SCRIBE("Mangled: "), str);
    vmatrixToString(vfontGetMatrix(choice), &str[9]);
    vdialogSetItemTitleScribed(info->irsLabel, vcharScribe(str));
  }
  else
    vdialogSetItemTitleScribed(info->irsLabel, SCRIBE("..."));
  


  /*
   * First time? We can now mangle fonts...
   */
  if (!Once)
    {
      Once = 1;
      vapplicationPropagateChange
        (vapplicationGetCurrent(), vname_State, TAG(COM_MANGLE_FONT), 
         vname_Enabled);
    }

  return vTRUE;
}



/********
 * noteMangleChange()
 *	Called when any mangle controller value is changed. Shows
 *      user the current value.
 *
 * -> control
 * -> event that triggered change (ignored)
 * <- void
 ********/
static void
noteMangleChange(vcontrol *control, vevent *ignored)
{
  vdialogItem *echo;
  
  echo = (vdialogItem*)vcontrolGetData(control);
  if (echo!=NULL)
    vdialogSetItemTitleScribed(echo, vnumScribeInt(vcontrolGetValue(control)));
}



/********
 * doMangle()
 *	Allow user to rotate/scale an existing font. Recreates
 *      the picker everytime (yick?)
 *
 * -> command context info
 * <- true
 ********/
static int
doMangle(vcommandFunction *com, vdict *context)
{
#define dlgOf(c) (vconfirmGetDialog(c))
  vresource 	 ares;
  vconfirm	*volatile mangler;
  chooserInfo	*info = getInfo(gChsr);
  vdialogItem	*item;
  const vname   *choice;
  vfont		*volatile font;
  vcontrol	*scalerX, *scalerY, *rotater;

  /*
   * Assign the last selected font for mangling. Note changes
   * are applied -on top of- any existing matrix transmorgifications...
   */
  ares    = vapplicationGetResources(vapplicationGetCurrent());
  ares    = vresourceGet(ares, TAG("aMangler"));
  mangler = vconfirmLoad(ares);

  item = vdialogFindItem(dlgOf(mangler), TAG("iFontDescript"));
  font = vdialogGetItemFont(info->fontDescription);
  vdialogSetItemTitle(item, vdialogGetItemTitle(info->fontDescription));


  /*
   * Remember these for control value feedback to user (used by
   * control noteprocs)
   */
  scalerX = (vcontrol*)vdialogFindItem(dlgOf(mangler), TAG("iScalerX"));
  item = vdialogFindItem(dlgOf(mangler), TAG("iScaleX"));
  vcontrolSetData(scalerX, item);
  vcontrolSetNotify(scalerX, noteMangleChange);
 
  scalerY = (vcontrol*)vdialogFindItem(dlgOf(mangler), TAG("iScalerY"));
  item = vdialogFindItem(dlgOf(mangler), TAG("iScaleY"));
  vcontrolSetData(scalerY, item);
  vcontrolSetNotify(scalerY, noteMangleChange);
 
  rotater = (vcontrol*)vdialogFindItem(dlgOf(mangler), TAG("iRotater"));
  item = vdialogFindItem(dlgOf(mangler), TAG("iRotate"));
  vcontrolSetData(rotater, item);
  vcontrolSetNotify(rotater, noteMangleChange);
 


  /*
   * Wait until they mangle or dismiss the window (synchronous but does not
   * block event loop)
   */
  vconfirmPlace(mangler, gDialog, vrectPLACE_HALF|vrectPLACE_RIGHT,
		vrectPLACE_INSET|vrectPLACE_TOP);

  choice = vconfirmProcess(mangler);

  if ((choice==vname_Ok) || (choice==vname_Apply))
    {
      vmatrix mtx;
      double d0,d1;

      vmatrixConcat(vfontGetMatrix(font), vmatrixIdent(), &mtx);

      d0 = (double)vcontrolGetValue(scalerX);
      d1 = (double)vcontrolGetValue(scalerY);
      vmatrixScale(&mtx, d0,d1, &mtx);
      d0 = (double)vcontrolGetValue(rotater);
      vmatrixRotate(&mtx, d0, &mtx);

      if (!vmatrixIsEqual(&mtx, vfontGetMatrix(font)))
        {
          vexWITH_HANDLING
	  {
            font = vfontMake(vfontGetFace(font), &mtx);
	  }
          vexON_EXCEPTION
	  {
            font = NULL;
            vdebugBE(vexDumpChain(vdebugGetWarningStream()));
	  }
          vexEND_HANDLING;
        }
      else
        font = NULL;
    }
  else
    {
      font = NULL;
    }


  /*
   * Tear down this dialog so we can see...
   */

  vconfirmDestroy(mangler);


  /*
   * Apply the mangled font to both the chooser and our main
   * window (as the last choice)
   */

  if (font!=NULL)
    {
      vfontchsrSetFont(gChsr, font);
      setFont(gChsr, font);
    }

  return vTRUE;
  
#undef dlgOf
}

static int
canMangle(vcommandFunction *com, vdict *context)
{
  vdictStore(context, vname_State, Once ? vname_Enabled : vname_Disabled);
  return vTRUE;
}




/********
 * turnOptionsAvail()
 *	Turn all of the filter options (sans "remove all") either
 *	on or off.
 *
 * -> [t/f] true for ON, otherwise OFF
 * <- void
 ********/
static void 
turnOptionsAvail(int on)
{
  register const vname 	**tag;
  register const vname	*state;
  register int           i;

  if (on) state = vname_Enabled;
  else state = vname_Disabled;

  for (i=0, tag= gChkGroup; i<comCHK_GROUP_COUNT; i++, tag++)
    {
      vdictStore(gDict, *tag, state);
      vapplicationPropagateChange(vapplicationGetCurrent(), vname_State, 
			          *tag, state);
    }
}



/********
 * noteOptionChange()
 *	Called to handle a change to one of the chooser 
 *	filtering options. Stores the options and forces the font
 *	chooser to refresh its listviews.
 *
 * -> command context
 * -> option that changed (see enum listing at top)
 * <- void
 ********/
static void
noteOptionChange(vdict *context, unsigned int flag)
{
  int	on;

  on = ((const vname*)vdictLoad(context, vname_Toggle)==vname_On);
  if (on) gOptions |= flag;
  else gOptions &= ~flag;

  if (gChsr!=NULL)
    vfontchsrRescan(gChsr);
}



/********
 * doChkOption()
 *	Issue override for our selector command. Basically processes
 *	user's filtering option selections.
 *
 * -> command context info <yawn>
 * <- true
 ********/
static int
doChkOption(vcommandSelector *com, vdict *context)
{
  unsigned	on, flag;
  int		selector;

  flag     = 0;
  selector = vcommandGetSelector(com);
  on       = ((const vname*)vdictLoad(context, vname_Toggle)==vname_On);

  switch (selector) {
    case comCHK_MONOSPACE: 	{
      flag = optionMONO;
      break;
    }
    case comCHK_LATIN1: 	{
      flag = optionLATIN1;
      break;
    }
    case comCHK_EVEN_ODD:	{
      flag = optionEVEN;
      break;
    }
    case comCHK_REMOVE_ALL:	{
      flag = optionNONE;
      break;
    }
    case comCHK_CUSTOM_FONTS:	{
      unsigned options;
      options = vfontchsrGetFilterOptions(gChsr);
      if (on) options |= vfontchsrFILTER_OPTION_ADD_CUSTOM_FONTS;
      else options &= ~((unsigned)vfontchsrFILTER_OPTION_ADD_CUSTOM_FONTS);
      vfontchsrSetFilterOptions(gChsr, options);
      break;
    }
    case comCHK_BOLD_FACES:	{
      flag = optionBOLDFACE;
      break;
    }
    case comCHK_UNROTATED_FONTS:{
      flag = optionUNROTATED;
      break;
    }
    case comCHK_SQUARE_FONTS:   {
      flag = optionSQUARE;
      break;
    }
  }

  if (flag) {
    noteOptionChange(context, flag);
    if (selector==comCHK_REMOVE_ALL)
      turnOptionsAvail(on ? vFALSE : vTRUE);
  }

  return vTRUE;
}



/********
 * chsrRemoveFonts()
 *	Our font filter override for the chooser. filters odd
 *	sized, scaled, and/or rotated fonts if appropriate
 *      filter is turned ON.
 *
 * -> chooser and font
 * <- [t/f]
 ********/

static vbool
chsrRemoveFonts(vfontchsr *chsr, vfont *font)
{
  vbool	allow = vTRUE;

  if (gOptions&optionEVEN)
    allow = (vfontGetSize(font)&0x1)==0;
  
  if (allow && (gOptions&optionUNROTATED))
    allow = vfontIsUpright(font);
  
  if (allow && (gOptions&optionSQUARE))
    allow = vfontIsSquare(font);

  return allow;
}




/********
 * chsrRemoveFamilies()
 *	Our font family filter override for the chooser. filters
 *	families not indicated by the user's current options.
 *
 * -> chooser and family
 * <- [t/f]
 ********/
static vbool
chsrRemoveFamilies(vfontchsr *chsr, vfontFamily *family)
{
  register vbool allow = vTRUE;
  const vname *encoding;

  /*
   * Remove all families from font chooser (why one would
   * do this is questionable but "give 'em enough rope...)
   */
  if (gOptions&optionNONE)
    {
      allow = vFALSE;
    }

  else
    {
      /*
       * Remove all non-iso8859 latin1 families
       */
      if ((gOptions&optionLATIN1) &&
          (encoding = vfontGetFamilyEncoding(family))!=vnameNULL &&
	  (encoding!=name_latin1))
	allow = vFALSE;
		
      /*
       * Remove all non-monospaced families
       */
      else
      if ((gOptions&optionMONO) &&
	  !vfontFamilyIsMono(family))
	allow = vFALSE;
    }

  return allow;
}



/********
 * chsrRemoveFaces()
 *	Removes non-bold faces from the font chooser's face 
 *	offerings.
 *
 * -> chizler and face
 * <- [t/f]
 ********/
static vbool
chsrRemoveFaces(vfontchsr *chsr, vfontFace *face)
{
  vbool allow = vTRUE;

  /*
   * Remove non-bolded faces
   */
  if (gOptions&optionBOLDFACE)
    if (vcharSearch(vfontGetFaceName(face), name_bold)==NULL &&
        vcharSearch(vfontGetFaceName(face), name_Bold)==NULL)
      allow = vFALSE;

  return allow;
}




/********
 * initClasses()
 *	Register/Initialize our font chooser and command subclasses.
 *	Must be called asap after vstartup().
 *
 * -> void
 * <- void
 ********/
static void
initClasses(void)
{
  vfontchsrClass *clas;

  /* our font chooser */
  clas = vclassReproduce(vfontchsrGetDefaultClass());
  vclassSetNameScribed(clas, SCRIBE("demo_font_chooser"));

  vclassSet(clas, vfontchsrFILTER_FAMILY, chsrRemoveFamilies);
  vclassSet(clas, vfontchsrFILTER_FACE,   chsrRemoveFaces);
  vclassSet(clas, vfontchsrFILTER,        chsrRemoveFonts);

  gChsrClass = clas;


  /* our selector commands */
  gCmdClas = vclassReproduce(vcommandGetDefaultSelectorClass());
  vclassSetNameScribed(gCmdClas, SCRIBE("demo_option_commands"));
  vclassSet(gCmdClas, vcommandISSUE, doChkOption);
}




/********
 * makeChooser()
 *	Makes an instance of our font chizler subclass. Should be
 *	called once for this sample (we got ourselves one of them
 *	"globals" thangs).
 *
 * -> void
 * <- chsr, new font chooza
 ********/
static vfontchsr*
makeChooser(void)
{
  vfontchsr 	*chsr;
  unsigned	options;
  chooserInfo	*info;

  /*
   * Create a new font chooser and cache oft-used info
   */
  chsr = vfontchsrCreateOfClass(gChsrClass);
  info = (chooserInfo*)vmemAlloc(sizeof(chooserInfo));

  vfontchsrSetData(chsr, info);
  vfontchsrSetApply(chsr, setFont);

  info->fontDescription = vdialogFindItem(gDialog, TAG("iFontDescript"));
  info->irsLabel = vdialogFindItem(gDialog, TAG("iRSLabel"));

  options  = vfontchsrGetFilterOptions(chsr);
  options |= vfontchsrFILTER_OPTION_FAMILY | vfontchsrFILTER_OPTION_FACE;
  vfontchsrSetFilterOptions(chsr, options);

  /* 
   * Stay up top (follow) o' our main window
   */
  vfontchsrSetLeader(chsr, vdialogGetWindow(gDialog));

  return chsr;
}



/********
 * loadWindows()
 *	Load the main dialog; create our global font chizler.
 *
 * -> void
 * <- void
 ********/
static void
loadWindows(void)
{
  vresource root, dres;

  /*
   * Load the main dialog and alloc a new chooser
   */
  root    = vapplicationGetResources(vapplicationGetCurrent());
  dres    = vresourceGet(root, TAG("aDialog"));
  gDialog = vdialogLoad(dres);
  gChsr   = makeChooser();
}




/********
 * nukeWindows()
 *	Cleanup our global window references.
 *
 * -> void
 * <- void
 ********/
static void
nukeWindows(void)
{
  if (gChsr) 
    {
      if (vfontchsrGetData(gChsr))
        vmemFree((void*)vfontchsrGetData(gChsr));
      vfontchsrDestroy(gChsr);
    }

  if (gDialog)
    vdialogDestroy(gDialog);

  if (gAboutBox)
    vconfirmDestroy(gAboutBox);
}



/********
 * initCommands()
 *	Initialize command processed by our sample. The "standard"
 *	bunch includes "Quit" and "About."
 *
 * -> void
 * <- void
 ********/

/* selector commands initializer */
static const vcommandSelectorTemplate _scmds[]= {
  {COM_LATIN1,		comCHK_LATIN1},
  {COM_MONOSPACE,	comCHK_MONOSPACE},
  {COM_ODD_EVEN,	comCHK_EVEN_ODD},
  {COM_CUSTOM_FONTS,	comCHK_CUSTOM_FONTS},
  {COM_BOLD_FACES,	comCHK_BOLD_FACES},
  {COM_UNROTATED,       comCHK_UNROTATED_FONTS},
  {COM_SQUARE,          comCHK_SQUARE_FONTS},
  {COM_REMOVE_ALL,	comCHK_REMOVE_ALL}
};


/* function commands initializer */
static const vcommandFunctionTemplate _fcmds[]= {
  {COM_QUIT,	    doQuit,     (vcommandFunc)NULL},
  {COM_CLOSE,	    doQuit,     (vcommandFunc)NULL},
  {COM_ABOUT,	    doAbout,    (vcommandFunc)NULL},
  {COM_PICK_FONT,   doPickFont, (vcommandFunc)NULL},
  {COM_MANGLE_FONT, doMangle,   canMangle}
};


static void
initCommands(void)
{
  vdict		*dict;
  vcommandSpace	*space;
  int            i;

  space = vcommandCreateSpace();
  vwindowSetSpaceOwned(vdialogGetWindow(gDialog), space);

  dict = vcommandCreateDictFunctionTemplates
    (_fcmds, sizeof(_fcmds)/sizeof(vcommandFunctionTemplate));
  vcommandStoreDictOfClassSelectorTemplates
    (dict, gCmdClas, _scmds, sizeof(_scmds)/sizeof(vcommandSelectorTemplate));

  for (i=0; i<comCHK_GROUP_COUNT; i++)
    gChkGroup[i] = TAG(_scmds[i].name);

  vcommandAddSpaceDictOwned(space, vname_Command, dict);

  dict = gDict = vdictCreate(vnameHash);
  vcommandAddSpaceDictOwned(space, vname_State, dict);
}




/********
 * main()
 *	The main enchilada...
 *
 * -> argc,argv
 * <- [EXIT_SUCCESS/EXIT_FAILURE]
 ********/
int main(int argc, char *argv[])
{
  int volatile exitcode = EXIT_SUCCESS;


  vstartup(argc,argv);
  name_latin1 = TAG("iso8859 1");
  name_bold   = TAG("bold");
  name_Bold   = TAG("Bold");


  vexUNWIND_PROTECT
    {

      /*
       * Init dialogs
       */
      initClasses();
      loadWindows();


      /*
       * Init our command space
       */
      initCommands();


      /*
       * Open the main dialog splat in the middle of the
       * main display
       */
      vdialogPlaceWindow(gDialog, vwindowGetRoot(),
			 vrectPLACE_CENTER, vrectPLACE_CENTER);
      vdialogOpen(gDialog);


      /*
       * Place the font chooser down to the right of the main
       * window
       */
      vfontchsrPlace(gChsr, gDialog,
		     vrectPLACE_HALF|vrectPLACE_RIGHT,
		     vrectPLACE_INSET|vrectPLACE_TOP);

      /*
       * Process events until quit
       */
      veventProcess();
    }

  vexON_UNWIND
    {
      /*
       * Cleanup memory, etc.
       */
      nukeWindows();

      if (vexGetRootException()) 
	{
	  vdebugBE(vexDumpChain(vdebugGetWarningStream()));
	  exitcode = EXIT_FAILURE;
	  vexClear();
	}
    }
  vexEND_UNWIND;

  exit(exitcode);
  return EXIT_FAILURE;
}

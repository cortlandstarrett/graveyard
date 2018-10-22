/* $Id: adjust.c,v 1.11 1996/09/25 16:27:52 scotth Exp $ */
/****************************************************************************
 *               (c) Copyright 1991,92,93 Visix Software, Inc.              *
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
 * Executable:     adjust                                                   *
 * Source Files:   adjust.c                                                 *
 * Resource Files: adjust.vr                                                *
 *                                                                          *
 * Managers Illustrated: Spring and Spring Domain Manager                   *
 *                       Resource Manager                                   *
 *                                                                          *
 *  This program illustrates how to create a dialog-specific adjuster item. *
 *  The code has knowledge of the dialog's layout so it is not an example   *
 *  of a generic splitter/adjuster dialog item.  It does however, give the  *
 *  programmer a sense of what is involved in doing runtime adjustments to  *
 *  a dialog's item layout.  Particularly, it demonstrates how the Spring   *
 *  and Spring Domain Managers must be used in adjustments.                 *
 *                                                                          *
 *  Adjust also demonstrates how to save a dialog's window bounds across    *
 *  sessions using the Galaxy Resource Manager.                             *
 *                                                                          *
 *  To exit the demo select File/Quit or close the main window              * 
 *                                                                          *
 ****************************************************************************/

#ifndef  vportINCLUDED
#include <vport.h>		/* for v*HEADER */
#endif

#include vstdlibHEADER
#include vdebugHEADER
#include vexHEADER
#include vrectHEADER
#include vcharHEADER
#include vnameHEADER
#include vstrHEADER
#include vclassHEADER
#include veventHEADER
#include vresourceHEADER
#include vdrawHEADER
#include veventHEADER
#include vcommandHEADER
#include vdomainHEADER
#include vspringHEADER
#include vspringdomHEADER
#include vapplicationHEADER
#include vdialogHEADER
#include vstartupHEADER
#include vtestHEADER

#if (vdebugDEBUG)
/* 
 * Maintain a distince debugging module tag for memory leaks
 */
static const char	 _adjustTag[] = "adjust";
#define vdebugTAG	 _adjustTag
#endif


/*
  +---------------------------------------------------------------------------+
   C O N S T A N T S
  +---------------------------------------------------------------------------+
 */

/* CHEATING: we connect the adjuster to the list by this fixed
 * amount, and we connect the information container to the adjuster
 * by this fixed amount,etc. This prevents us from having to find 
 * out these connection lengths through the spring manager!
 */
#define ADJUSTER_CONNECT_SPACING 3


/*
 * Global Name Array: we access our resource tag via a global array.
 * To get a name use name_??? where "???" is the identifier you're
 * looking for; eg. "name_List" to retrieve the tag for the "List."
 */
enum {
  nameDIALOG,
  nameLIST,
  nameADJUSTER,
  nameCONTAINER,
  nameAPP_TITLE,
  nameAPP_ICON,
  namePREF_BOUNDS,
  namePREF_ADJUST_H,
  nameCOUNT
};

static const vname *names[nameCOUNT];
static const char *literals[nameCOUNT]= {
  "dialog",		/* our sample dialog */
  "list",		/* arbitrary list item */
  "adjuster",		/* ze adjuster */
  "container",		/* arbitrary container */
  "name",		/* language-dependent displayable name of our app */
  "icon",		/* default icon for our window */
  "adj-bounds",		/* preference: the sample dialog's position and size*/
  "adj-dh"		/* preference: the adjuster's location */
};

#define name_Dialog	names[nameDIALOG]
#define name_List	names[nameLIST]
#define name_Adjuster	names[nameADJUSTER]
#define name_Container	names[nameCONTAINER]
#define name_Title	names[nameAPP_TITLE]
#define name_Icon	names[nameAPP_ICON]
#define name_Bounds	names[namePREF_BOUNDS]
#define name_AdjustH	names[namePREF_ADJUST_H]


/*
  +---------------------------------------------------------------------------+
   A D J U S T E R  --  C L A S S   D E C L A R A T I O N
  +---------------------------------------------------------------------------+
 */

typedef struct adjuster {
  vdialogItem	item;	/* superclass... */
  vrect		rLimit;	/* area where y and h are split drag limits */
  vrect		rDrag;	/* the adjuster's drag rect */
  int		oldY;	/* the y position last call to drag handler */
  int		delta;
}adjuster;

#define adjusterCLASS(CLASS, ADJUSTER, NOTIFY)	\
  vdialogITEM_CLASS(CLASS, ADJUSTER, NOTIFY);	\
  vclassMETHOD(adjusterADJUST, (ADJUSTER *adj, int dh))

typedef struct adjusterClass adjusterClass;
struct adjusterClass {
  adjusterCLASS(adjusterClass, adjuster, vdialogItemNoteProc);
};

#define _adjusterGetClass(adj)			\
  ((adjusterClass*)vdialogGetItemClass((vdialogItem*)(adj)))

#define _adjusterSend(adj,m,a)			\
  vclassSend(_adjusterGetClass(adj),m,a)
#define _adjusterAdjust(adj,dh)			\
  _adjusterSend(adj, adjusterADJUST, (adj,dh))

#define _adjusterSendSuper(m,a)			\
  vclassSendSuper(_adjusterGetDefaultClass(),m,a)

/*
  +---------------------------------------------------------------------------+
    A D J U S T E R  --  C L A S S   D E F I N I T I O N
  +---------------------------------------------------------------------------+
 */

/* prototypes */
static void		_adjusterInit(adjuster*);
static void		_adjusterLoadInit(adjuster*, vresource);
static void		_adjusterDraw(adjuster*);
static int		_adjusterButtonDownHandler(adjuster*, vevent*);
static int		_adjusterDragHandler(adjuster*, vevent*);
static int		_adjusterButtonUpHandler(adjuster*, vevent*);
static void		_adjusterDrawDragOutline(const vrect*);
static void		_adjusterAdjustPosition(adjuster*,int);
static adjusterClass   *_adjusterGetDefaultClass(void);



/*
 * adjusterInit(), adjusterLoadInit()
 *	Initialize an adjuster dialog item. We only need the 
 *	loadinit method for our sample since we've store our item
 *	with a dialog in a resource file
 */
 static void
_adjusterInit(adjuster *adj)
{
  _adjusterSendSuper(vobjectINIT, (adj));
   adj->delta = 0;
   return;
}


 static void
_adjusterLoadInit(adjuster *adj, vresource res)
{
 _adjusterSendSuper(vobjectLOAD_INIT, (adj, res));
  adj->delta = 0;
  return;
}



/*
 * adjusterAdjustPosition()
 *	Adjusts the dialog's spring solution to match a desired adjuster 
 *	location. Note the list item -- not the adjuster item -- is the
 *	item whose bounds are actually updated. We presume that the dialog's
 *	items are setup such that everything else falls into place if the
 *	list is adjusted.
 *
 * -> adjuster*,  the adjuster item
 * -> int, the amount to adjust the "split" view [-/+]
 * <- void
 */
 static void
_adjusterAdjustPosition(adjuster *adj, int delta)
{
  vspringdom		*springdom = NULL;
  vdialog		*dial;
  vdialogItem		*list;
  int			 index;
  vdomainObject		*obj;
  vspringdomObject	*springobj;
  vspringdomConnection	*connectH;
  int			 h;
  vspringSolution	*newSolution;


  /*
   * We do all this stuff here since we "know" we're not
   * moving from dialog to dialog and we don't exist in
   * containers...
   */
  dial = vdialogDetermineItemDialog(&adj->item);
  list = vdialogFindItem(dial, name_List);


  /*
   * Grab the dialog's current solution; we want to adjust
   * the list item's height (fixed base). We ASSUME our spring
   * solution is set st all other relevant item positions are
   * calculated based on the list's position!!!
   */
  springdom = vspringdomDecompile(vdialogGetSolution(dial));
  vexUNWIND_PROTECT
    {
      /*
       * According to Spring Manager, the topmost domain object
       * maps to the first item in the dialog's itemlist; so
       * in order to find our list in the spring domain, traverse
       * the domain objects top to bottom using the dialog itemlist
       * index as a stop guide...
       */
      index = vdialogGetItemIndex(dial, list);
      for (obj = vdomainTopObject(vspringdomGetDomain(springdom));
	   obj &&(index>0);
	   obj = vdomainNextObjectBehind(obj), index--)
	;

      /*
       * Iff we located the list object in spring domain
       */
      if (obj && !index) {

	/* 
	 * Convert the "regular" domain object to the spring 
	 * domain's object
	 */
	springobj = vspringdomGetFromDomainObject(springdom, obj);


	/* 
	 * Get the list's height connection
	 */
	connectH = vspringdomGetObjectConnection(springdom, springobj,
						 vspringdomTOP_INSIDE);

	/* 
	 * Figure out the new fixed base length 
	 */
	h  = vspringdomGetConnectionFixedBase(springdom, connectH);
	h += delta;


	/* 
	 * Set the height connection to its new fixed length 
	 */
	vspringdomSetConnectionFixedBase(springdom, connectH, h);


	/*
	 * Recompile spring domain into a spring solution and
	 * attach to the dialog. Note vdialogSetSolution() assumes
	 * ownership of the spring solution so we shouldn't try
	 * to destroy it!
	 */
	newSolution = vspringdomCompile(springdom);
	vdialogSetSolution(dial, newSolution);
      }
    }

  /*
   * If we encounter failure, make sure we destroy domain
   */
  vexON_UNWIND
    {
      if (springdom)
	vspringdomDestroy(springdom);
    }
  vexEND_UNWIND


  /*
   * Remember change in position for possible
   * later storage...
   */
  adj->delta += delta;
}



/*
 * adjusterDraw()
 * 	Draw our adjuster item. We assume the gstate has been previously
 *	saved.
 */
 static void 
_adjusterDraw(adjuster *adj)
{
  register vdialogItem	*item= &adj->item;
  const vrect		*r;

  r = vdialogGetItemRect(item);

  vdrawRectsHiliteFillInside
    (r, 1, (vcolor*)NULL, 
     vdialogDetermineItemColor(item, vdrawCOLOR_SHADOW_BOTTOM),
     vdialogDetermineItemColor(item, vdrawCOLOR_SHADOW_TOP));
}




/*
 * adjusterDrawDragOutline()
 *	While tracking our adjuster, draw an outline indicating the
 *	the active position of the adjuster. We assume the gstate
 *	has been properly saved.
 */
 static void
_adjusterDrawDragOutline(const vrect *r)
{
  int	saveW;

  saveW = vdrawGetLineWidth();
  vdrawSetLineWidth(0);
  vdrawSetFunction(vdrawFUNC_INVERT);
  vdrawRectsStroke(r, 1);
  vdrawSetLineWidth(saveW);
  vdrawSetFunction(vdrawFUNC_COPY);
}




/*
 * adjusterButtonDownHandler()
 *	Handle button down events in the adjuster. This sets up
 *	the adjuster's limit rect (based on the miniumum size of the
 *	list, container, and message boxes) and draws the initial
 *	drag-outline
 */
 static int 
_adjusterButtonDownHandler(adjuster *adj, vevent *evt)
{
  register vdialogItem	*item= &adj->item;
  register vrect	*area, *drag;
  int			 dim;
  vdialogItem		*list, *cont;
  vdialog		*dial;
  int			 w,h;

  /*
   * Calculate the rect enclosing both the list and the
   * information container...note this assumes a certain
   * layout of the browser window!
   */
  dial = vdialogDetermineItemDialog(item);
  list = vdialogFindItem(dial, name_List);
  cont = vdialogFindItem(dial, name_Container);
  area = &adj->rLimit;
  vrectUnion(vdialogGetItemRect(list), vdialogGetItemRect(cont), area);

  /*
   * Allow for the minimum sizes of list, container, and 
   * message items. REMEMBER: coords relative to the lower 
   * left-hand corner of the dialog!!
   */
  vdialogGetItemMinSize(cont, &w, &h);
  h += ADJUSTER_CONNECT_SPACING;
  area->y += h, area->h -= h;
  vdialogGetItemMinSize(list, &w, &h);
  h += ADJUSTER_CONNECT_SPACING;
  area->h -= h;



  /*
   * Calculate the adjuster drag rect using the mouse down
   * location as the vert.center of the adjuster and the x,w 
   * of the unioned area as the x,w.
   */
  dim   = vdialogGetItemH(item);
  drag  = &adj->rDrag;
  vrectSet(area->x, veventGetPointerY(evt)-dim/2, area->w, dim, drag);
  vrectPin((const vrect*)drag, area, drag);


  /*
   * Draw the adjuster/outline for begin drag...
   */
  vdrawGSave();
  vdialogItemDrawDevice(item);
 _adjusterDrawDragOutline(drag);
  vdrawGRestore();

  /*
   * Remember where we started...
   */
  adj->oldY = veventGetPointerY(evt);
  return TRUE;
}




/*
 * adjusterButtonUpHandler()
 *	Handle a button up event in our adjuster. If the user has actually
 *	moved the adjuster this causes the dialog's items to be repositioned
 *	wrt the new split ratio. Does nothing if the user hasn'e changed
 *	adjuster's position.
 */
 static int 
_adjusterButtonUpHandler(adjuster *adj, vevent *evt)
{
  register vdialogItem	*item= &adj->item;
  register vrect	*area, *drag;
  int			 oldY, newY;

  /*
   * Init...
   */
  area = &adj->rLimit;
  drag = &adj->rDrag;


  /*
   * Draw the outline for end drag...
   */
  vdrawGSave();
  vdialogItemDrawDevice(item);
 _adjusterDrawDragOutline(drag);
  vdrawGRestore();


  /*
   * Change the size of the list if necessary, the
   * container item should follow...note this assumes
   * a certain spring solution for items, namely the
   * container and adjuster FOLLOW the list item!
   */
  oldY = vdialogGetItemY(item) + vdialogGetItemH(item)/2;
  newY = drag->y + drag->h/2;
  if (newY-oldY)
   _adjusterAdjust(adj, oldY-newY);

  return TRUE;
}




/*
 * adjusterDragHandler()
 *	Handler drag (or track) events in our adjuster. This keeps track
 *	of the changes in the adjuster's original position as the user
 *	moves the adjuster. Additionally, it synchronizes the adjuster's
 *	drag-outline to match the user's movements.
 */
 static int 
_adjusterDragHandler(adjuster *adj, vevent *evt)
{
  register vdialogItem	*item= &adj->item;
  register vrect	*area, *drag;

  /*
   * Don't have a real sub-class; we used the item's
   * data field for ourselves...(ick)
   */
  area = &adj->rLimit;
  drag = &adj->rDrag;

  /*
   * Set up for drawing...erase the outline of prev
   * location
   */
  vdrawGSave();
  vdialogItemDrawDevice(item);
 _adjusterDrawDragOutline(drag);


  /*
   * Update location of adjuster outline...draw
   * outline in new location
   */
  vrectOffset((const vrect*)drag, 0, 
	      veventGetPointerY(evt)-adj->oldY, drag);
  vrectPin((const vrect*)drag, area, drag);
 _adjusterDrawDragOutline(drag);
  vdrawGRestore();

  /*
   * Remember where we dragged to...
   */
  adj->oldY = drag->y + drag->h/2;
  return TRUE;
}




/*
 * adjusterGetDefaultClass()
 *	Make sure the "adjuster" class is registered with the Galaxy
 *	Class Manager. This routine must be called before ANY dialog
 *	that contains adjuster items is loaded!
 */
 static adjusterClass*
_adjusterGetDefaultClass(void)
{
  static adjusterClass	*defaultClass = NULL;

  if (!defaultClass) {
    register adjusterClass *clas;

    clas = vclassSpawn(vdialogGetDefaultItemClass(), sizeof(adjusterClass));
    vclassSetNameScribed(clas, vcharScribeLiteral("adjuster"));
    vclassSetObjectSize(clas, sizeof(adjuster));

    vclassSet(clas, vobjectINIT,		    _adjusterInit);
    vclassSet(clas, vobjectLOAD_INIT,		    _adjusterLoadInit);
    vclassSet(clas, vdialogDRAW_ITEM,               _adjusterDraw);
    vclassSet(clas, vdialogHANDLE_ITEM_DRAG,        _adjusterDragHandler);
    vclassSet(clas, vdialogHANDLE_ITEM_BUTTON_DOWN, _adjusterButtonDownHandler);
    vclassSet(clas, vdialogHANDLE_ITEM_BUTTON_UP,   _adjusterButtonUpHandler);
    vclassSet(clas, adjusterADJUST,   		    _adjusterAdjustPosition);

    defaultClass = clas;
  }

  return defaultClass;
}



/*
  +---------------------------------------------------------------------------+
    A D J U S T E R   --   S A M P L E   D I A L O G
  +---------------------------------------------------------------------------+
 */

/*
 * Keep all our globals in one structure
 */
typedef struct adjusterApp {
  const char	*nameASCII;
  vapplication	*app;
  vresource	 resources;
  vdialog	*dialog;
}adjusterApp;

static adjusterApp gApp= {0};



/*
 * initGlobalNames()
 *	Initialize all global names used by our application. The
 *	resource manager expects tags interned in the global name table
 *	so we got no choice.
 */
static void
initGlobalNames(void)
{
  register const char 	**lit;
  register const vname	**name, **namestop;

  lit  = literals;
  name = names, namestop = name+nameCOUNT;
  for (; name<namestop; name++, lit++)
    *name = vnameInternGlobalLiteral(*lit);
  return;
}



/*
 * [get|set]AdjusterChangeFromTemplate()
 *	Utilities to enable storage of adjuster's setting in a preference
 *	so we can restore between sessions.
 * -> vdialog*, the sample dialogue
 * <-> int, the difference in adjuster's position FROM the default position
 *	   in the resource file!
 */
static void
setAdjusterChangeFromTemplate(vdialog *dialog, int delta)
{
  register adjuster	*adj;

  /*
   * If nothing to do...
   */
  if (!delta)
    return;
  adj = (adjuster*)vdialogFindItem(dialog, name_Adjuster);
  if (!adj)
    return;

  /*
   * Else try to restore the split ratio between list
   * and synopsis container
   */
  vexWITH_HANDLING
  {
    _adjusterAdjust(adj, delta);
  }
  vexON_EXCEPTION
  {
      vdebugMWarn(("%s: problem setting adjuster\n", gApp.nameASCII));
  }
  vexEND_HANDLING;

  return;
}

static int
getAdjusterChangeFromTemplate(vdialog *dialog)
{
  register adjuster	*adj;

  adj = (adjuster*)vdialogFindItem(dialog, name_Adjuster);
  return adj ? adj->delta : 0;
}




/*
 * initDialogLayout()
 *	Setup the sample dialog's layout based on saved preferences or,
 *	if not available, default values.
 * -> vresource, the application's preferences dictionary
 * -> vdialog*, the sample dialog BEFORE it's been opened!
 */
static void
initDialogLayout(vresource prefs, vdialog *dialog)
{
  vresource 	res;
  vrect		r;
  int		dh;
  vbool		defaults;

  defaults = (prefs==vresourceNULL);

  /* dialog's position */
  if (defaults || !vresourceTestGet(prefs, name_Bounds, &res))
    {
      vwindowPlace(vdialogGetWindow(dialog), vwindowGetRoot(), 
		   vrectPLACE_CENTER, vrectPLACE_CENTER);
    }
  else
    {
      vresourceLoadInitRect(&r, res);
      vwindowSetRect(vdialogGetWindow(dialog), &r);
    }

  /* adjuster's position */
  if (!defaults && vresourceTestGetInteger(prefs, name_AdjustH, &dh))
    setAdjusterChangeFromTemplate(dialog, dh);

  return;
}

/*
 * saveDialogLayout()
 *	Save the current bounds of the sample dialog (position, size)
 *	and the adjuster's current position within dialog. These are
 *	saved and restored across sessions.
 * -> vresource, the application's preferences dictionary
 * -> vdialog*, the sample dialog
 */
static void
saveDialogLayout(vresource prefs, vdialog *dialog)
{
  int	   	dh;
  const vrect  *pr;

  if (prefs!=vresourceNULL)
    vexWITH_HANDLING
      {
	pr = vwindowGetRect(vdialogGetWindow(dialog));
	vresourceStoreRect((vrect*)pr, vresourceMake(prefs, name_Bounds));

	dh = getAdjusterChangeFromTemplate(dialog);
	vresourceSetInteger(prefs, name_AdjustH, dh);
      }
    vexON_EXCEPTION
      {
	vdebugMWarn(("%s: problem writing preferences\n", gApp.nameASCII));
      }
    vexEND_HANDLING;

  return;
}



/*
 * triggerQuit
 *	Issue notification for the Quit command (from File/Quit or
 *      windows close adornment)
 * -> command, the quit command
 * -> context, ignored
 * <- true
 */
static int
triggerQuit(vcommandFunction *cmd, vdict *ignored_context)
{
  veventStopProcessing();
  return vTRUE;
}

/*
 * initDialogCommands()
 *	Initialize the commands for our main dialog
 * -> void
 * <- void
 */
static void
initDialogCommands(vdialog *dialog)
{
  vdict			*dict;
  vcommandFunction	*com;
  vcommandSpace		*space;

  dict = vdictCreate(vnameHash);

  com = vcommandCreateFunction();
  vcommandSetFunctionIssue(com, triggerQuit);
  vdictStore(dict, vname_Quit, com);

  com = vcommandCreateFunction();
  vcommandSetFunctionIssue(com, triggerQuit);
  vdictStore(dict, vname_Close, com);

  space = vwindowGetSpace(vdialogGetWindow(dialog));
  if (!space)
    {
      space = vcommandCreateSpace();
      vwindowSetSpaceOwned(vdialogGetWindow(dialog), space);
    }

  vcommandAddSpaceDictOwned(space, vname_Command, dict);
}


/*
  +-------------------------------------------------------------------------+
   main()
 
   Our application's main thingy. We initialize Galaxy the easy way, register
   our adjuster class, load ze dialogue, and we're off!
 
  +-------------------------------------------------------------------------+
 */
int
main(int argc, char *argv[])
{
  register adjusterApp 	*app = &gApp;
  register vresource	res;
  vstr			*str;


  /* we need to start vex up before we can use it */
  vexStartup ();

  
  /* If debugging enabled, remember our ascii name for 
   * error-reporting 
   */
  vdebugBE(app->nameASCII = argv[0];);


  /*
   * Wrap our entire application with an exception handler
   * which prints user message before dying
   */
  vexWITH_HANDLING
    {

      /* Initialize Galaxy the easy way */
      vstartup(argc, argv);      


      /* Connect to any running testing tools */
      vtestStartup();      


      /* Initialize our global names ASAP */
      initGlobalNames();



      /* Graphical bells-an'-whistles */
      app->app = vapplicationGetCurrent();
      app->resources = vapplicationGetResources(app->app);
      str = vresourceGetString(app->resources, name_Title);
      vapplicationSetTitleScribed(app->app, vstrScribe(str));
      res = vresourceGet(app->resources, name_Icon);
      vapplicationSetIconOwned(app->app, vimageLoad(res));



      /* !!!
       * NOTE: we must initialize our adjuster class -- BEFORE 
       * loading any dialog that contains items of that class
       * !!!
       */
      (void)_adjusterGetDefaultClass();



      /* 
       * Load and initialize ze sample dialogue, 
       * restore ze way we were ala preferences
       */
      res = vresourceGet(app->resources, name_Dialog);
      app->dialog = vdialogLoad(res);
      initDialogCommands(app->dialog);

      res = vapplicationGetPreferences(app->app);
      initDialogLayout(res, app->dialog);



      /* 
       * Open dialog.
       * Process events forever an' ever...
       */
      vdialogOpen(app->dialog);
      veventProcess();



      /* 
       * All done
       * Remember ze way we were for next time
       */
      saveDialogLayout(vapplicationGetPreferences(app->app), app->dialog);
      vdialogDestroy(app->dialog);
    }



  /*
   * WHOOPS...abandon ship! runaway, runaway! beam up, beam up!
   */
  vexON_EXCEPTION
    {
      if (gApp.dialog)
	vdialogDestroy(gApp.dialog);

      vexPropagate(NULL, vexNULL);
    }
  vexEND_HANDLING;



  /*
   * We're done...
   */
  exit(EXIT_SUCCESS);
  return EXIT_FAILURE;
}

/*
 * Formatting information for emacs
 *
 * Local Variables:
 * c-argdecl-indent:4
 * c-brace-imaginary-offset:0
 * c-brace-offset:-4
 * c-continued-brace-offset:0
 * c-continued-statement-offset:4
 * c-extra-brace-offset:0
 * c-file-offsets:((block-open . -))
 * c-file-style:"BSD"
 * c-indent-level:4
 * c-label-offset:-4
 * tab-width:8
 * End:
 */


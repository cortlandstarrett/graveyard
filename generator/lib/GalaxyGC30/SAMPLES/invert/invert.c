/* 	$Id: invert.c,v 1.6 1997/10/22 19:55:51 alexey Exp $	 */

#include <vport.h> /* Load the Galaxy preprocessor symbols  */

/* #include the necessary Galaxy headers                    */
/* but do it in the most preprocessor-friendly way possible */

#ifndef vstdlibINCLUDED
#include vstdlibHEADER
#endif
#ifndef vdebugINCLUDED
#include vdebugHEADER
#endif
#ifndef vmemINCLUDED
#include vmemHEADER
#endif
#ifndef vrectINCLUDED
#include vrectHEADER
#endif
#ifndef vcharINCLUDED
#include vcharHEADER
#endif
#ifndef vdictINCLUDED
#include vdictHEADER
#endif
#ifndef vnameINCLUDED
#include vnameHEADER
#endif
#ifndef veventINCLUDED
#include veventHEADER
#endif
#ifndef vresourceINCLUDED
#include vresourceHEADER
#endif
#ifndef vclassINCLUDED
#include vclassHEADER
#endif
#ifndef vcommandINCLUDED
#include vcommandHEADER
#endif
#ifndef vcolorINCLUDED
#include vcolorHEADER
#endif
#ifndef vdrawINCLUDED
#include vdrawHEADER
#endif
#ifndef vwindowINCLUDED
#include vwindowHEADER
#endif
#ifndef vapplicationINCLUDED
#include vapplicationHEADER
#endif
#ifndef vdialogINCLUDED
#include vdialogHEADER
#endif
#ifndef vnoticeINCLUDED
#include vnoticeHEADER
#endif
#ifndef vstartupINCLUDED
#include vstartupHEADER
#endif
#ifndef invertINCLUDED
#include "invert.h"
#endif

#ifndef lint
static char vcid[] = "$Id: invert.c,v 1.6 1997/10/22 19:55:51 alexey Exp $";
#endif

/* Label any leaked memory as ours */
#define vdebugTAG "invert"

static _invertGlobals *_globals;    /* global variables                    */

/* main -- driver function for the invert sample
 *
 * -> argc -- count of the command line arguments
 * -> argv -- vector containing text of the arguments
 * <-      -- EXIT_SUCCESS if the sample successfully completed execution
 *            EXIT_FAILURE otherwise
 */
int main(int argc, char **argv)
{
  vresource dialogResource;
  vdialog *mainDialog;
  vcommandSpace *dialogSpace = NULL;
  vdict *commandDict;
  vdialogItemClass *contentClass;    /* our dialogItem subclass */
  vdialogItem *content;
  vapplication *application;

  /* Command functions */
  static vcommandFunctionTemplate commands[invertNUM_COMMANDS] = {
    {"xor",  useFuncXor, NULL},
    {"invert",  useFuncInvert, NULL},
    {"hilite",  useFuncHilite, NULL},
    {"complement",  useFuncComplement, queryFuncComplement},
    {"quit", fileQuit, NULL},
    {"striped", backgroundStriped, NULL},
    {"solid", backgroundSolid, NULL},
    {"filled", foregroundFilled, NULL},
    {"outline", foregroundOutline, NULL}
  };

  /* Initialize the Galaxy managers */
  vstartup(argc, argv);
  application = vapplicationGetCurrent();

  /* initialize our private data structures */
  invertInitialize();

  /* Set the our dialog item subclass (the content area) up */
  contentClass = vclassReproduce(vdialogGetDefaultItemClass());
  vclassSetNameScribed(contentClass, vcharScribeLiteral("contentClass"));
  vclassSet(contentClass, vdialogDRAW_ITEM, contentDraw);
  vclassSet(contentClass, vdialogHANDLE_ITEM_BUTTON_DOWN,
	    contentHandleButtonDown);
  vclassSet(contentClass, vdialogHANDLE_ITEM_DRAG, contentHandleItemDrag);
  vclassSet(contentClass, vdialogHANDLE_ITEM_BUTTON_UP, contentHandleButtonUp);

  dialogResource = vresourceGet(vapplicationGetResources(application),
				vnameInternGlobalLiteral("invertDialog"));
  mainDialog = vdialogLoad(dialogResource);
  vdialogSetNotify(mainDialog, dialogNotify);
  
  content = vdialogFindItem(mainDialog, vnameInternGlobalLiteral("content"));
  invertSetItem(content);

  /* Create the command space, owned by the application */
  dialogSpace = vcommandCreateSpace();
  vapplicationSetSpaceOwned(application, dialogSpace);

  /* Create the command dictionaries */
  commandDict = vcommandCreateDictFunctionTemplates(commands,
						    invertNUM_COMMANDS);
  vcommandAddSpaceDictOwned(dialogSpace, vname_Command, commandDict);

  vdialogOpen(mainDialog);
  veventProcess();

  /* clean up after ourselves */
  vdialogDestroy(mainDialog);
  invertDestroy();

  exit(EXIT_SUCCESS);
  return EXIT_FAILURE; /* should not be reached */
}

/* contentDraw -- override of vdialogDRAW_ITEM, makes the screen reflect
 *                the current state of the program
 *
 * -> contentArea -- dialog item to draw to
 */
static void contentDraw(vdialogItem *contentArea)
{
  int i, j, x, y, w, h;
  vcolor *oldColor;

  /* avoid an expensive call to vdrawGSave() by noticing that  */
  /* the only part of the gstate affected is the current color */
  oldColor = vdrawGetColor();

  /* Cache the dialog item's dimentions for later use */
  x = vdialogGetItemX(contentArea);  y = vdialogGetItemY(contentArea);
  w = vdialogGetItemW(contentArea);  h = vdialogGetItemH(contentArea);

  /* clear the window */
  vdrawSetColor(invertGetWhite());
  vdrawRectFill(x, y, w, h);

  if (invertGetBackground() == invertSTRIPED) {
    /* draw RGB stripes */
    for (i = 0; i < (w / 10); i++) {
      j = (i % 3);

      vdrawSetColor(invertGetColor(j, 0));

      vdrawMoveTo((x + (i * 10) + 5), y);
      vdrawLineTo((x + (i * 10) + 5), h);
      vdrawStroke();
    }
  }

  /* restore the original gstate */
  vdrawSetColor(oldColor);
}

/* contentHandleButtonDown -- override of vdialogHANDLE_ITEM_BUTTON_DOWN
 *                            set up the drag rectangles
 *
 * -> contentArea -- dialog item the event occured in
 * -> event       -- button down event of interest
 */
static int contentHandleButtonDown(vdialogItem *contentArea, vevent *event)
{
  /* initialize this drag rect */
  invertRectSet(veventGetPointerX(event), veventGetPointerY(event), 0, 0);
  invertUpdateCache(invertGetRectX(), invertGetRectY(), 0, 0);
  
  /* Draw this degenerate rect to avoid bit turds */
  drawRubberRect(invertGetForeground(), invertGetRect());

  return vTRUE;
}

/* contentHandleDrag -- override of vdialogHANDLE_ITEM_DRAG
 *                      update the drag rectangles
 *
 * -> contentArea -- dialog item the event occured in
 * -> event       -- button down event of interest
 */
static int contentHandleItemDrag(vdialogItem *contentArea, vevent *event)
{
  static vrect screenRect;
  
  /* erase the old rect */
  drawRubberRect(invertGetForeground(), invertGetCache());
  
  /* adjust rubberRect for the new mouse position    */
  invertSetRectW(veventGetPointerX(event) - invertGetRectX());
  invertSetRectH(veventGetPointerY(event) - invertGetRectY());

  /* Copy rubberRect into screenRect for display */
  vrectSet(invertGetRectX(), invertGetRectY(),
	   invertGetRectW(), invertGetRectH(), &screenRect);

  /* if the rect contains negative values, adjust it */
  /* so that the contents are positive               */
  if (screenRect.w < 0) {
    screenRect.w *= -1;
    screenRect.x -= screenRect.w;
  }
  if (screenRect.h < 0) {
    screenRect.h *= -1;
    screenRect.y -= screenRect.h;
  }
  
  /* draw the new rect */
  drawRubberRect(invertGetForeground(), &screenRect);

  return vTRUE;
}

/* contentHandleButtonUp -- override of vdialogHANDLE_ITEM_BUTTON_UP
 *                          clean up a drag operation
 *
 * -> contentArea -- dialog item the event occured in
 * -> event       -- button down event of interest
 */
static int contentHandleButtonUp(vdialogItem *contentArea, vevent *event)
{
  /* Erase the last drag rect */
  drawRubberRect(invertGetForeground(), invertGetCache());

  /* and reset the drag rect  */
  invertRectClear();

 /* lastly, restore the old gstate */
  vdrawGRestore();

  return vTRUE;
}

/* dialogNotify -- notify function for the main dialog
 *                 (exit the app if the window manager's close box was hit)
 *
 * -> dialog -- the dialog the event occured in
 * -> event  -- the event of interest in the given dialog
 */
static void dialogNotify(vdialog *dialog, vevent *event)
{
  if (veventGetType(event) == veventWINDOW_STATE && veventIsClose(event))
    veventStopProcessing();
}

/* fileQuit -- function invoked when the "quit" command is issued
 *             (via the "File->Quit" menu item) - quits the application
 *
 * -> command -- the function command which caused this activation
 * -> content -- the associated context dictionary
 * <-         -- TRUE if this command was handled, FALSE otherwise
 */
static int fileQuit(vcommandFunction *command, vdict *context)
{
  veventStopProcessing();
  return vTRUE;
}

/* backgroundStriped -- function invoked when the "striped" command is issued
 *                      (via the "Background->Striped" menu item)
 *                      sets up use of the RGB striped background
 *
 * -> command -- the function command which caused this activation
 * -> content -- the associated context dictionary
 * <-         -- TRUE if this command was handled, FALSE otherwise
 */
static int backgroundStriped(vcommandFunction *command, vdict *context)
{
  invertSetBackground(invertSTRIPED);

  vdialogInvalItem(invertGetItem(), vwindowINVAL_UPDATE);

  return vTRUE;
}

/* backgroundSolid -- function invoked when the "solid" command is issued
 *                    (via the "Background->Solid" menu item)
 *                    sets up use of the solid white background
 *
 * -> command -- the function command which caused this activation
 * -> content -- the associated context dictionary
 * <-         -- TRUE if this command was handled, FALSE otherwise
 */
static int backgroundSolid(vcommandFunction *command, vdict *context)
{
  invertSetBackground(invertSOLID);

  vdialogInvalItem(invertGetItem(), vwindowINVAL_UPDATE);

  return vTRUE;
}

/* foregroundFilled -- function invoked when the "filled" command is issued
 *                     (via the "Foreground->Filled" menu item)
 *                     sets up drawing a filled-in rubber rectangle
 *
 * -> command -- the function command which caused this activation
 * -> content -- the associated context dictionary
 * <-         -- TRUE if this command was handled, FALSE otherwise
 */
static int foregroundFilled(vcommandFunction *command, vdict *context)
{
  invertSetForeground(invertFILLED);
  return vTRUE;
}

/* foregroundOutline -- function invoked when the "outline" command is issued
 *                      (via the "Foreground->Outline" menu item)
 *                      sets up drawing a outlined rubber rectangle
 *
 * -> command -- the function command which caused this activation
 * -> content -- the associated context dictionary
 * <-         -- TRUE if this command was handled, FALSE otherwise
 */
static int foregroundOutline(vcommandFunction *command, vdict *context)
{
  invertSetForeground(invertOUTLINE);
  return vTRUE;
}

/* useFuncXor -- function invoked when the "xor" command is issued
 *               (via the "Methods->vdrawFUNC_XOR" menu item)
 *               sets up use of the vdrawFUNC_XOR drawing function
 *
 * -> command -- the function command which caused this activation
 * -> content -- the associated context dictionary
 * <-         -- TRUE if this command was handled, FALSE otherwise
 */
static int useFuncXor(vcommandFunction *command, vdict *context)
{
  invertSetFunction(vdrawFUNC_XOR);
  return vTRUE;
}

/* useFuncInvert -- function invoked when the "invert" command is issued
 *                  (via the "Methods->vdrawFUNC_INVERT" menu item)
 *                  sets up use of the vdrawFUNC_INVERT drawing function
 *
 * -> command -- the function command which caused this activation
 * -> content -- the associated context dictionary
 * <-         -- TRUE if this command was handled, FALSE otherwise
 */
static int useFuncInvert(vcommandFunction *command, vdict *context)
{
  invertSetFunction(vdrawFUNC_INVERT);
  return vTRUE;
}

/* useFuncHilite -- function invoked when the "hilite" command is issued
 *                  (via the "Methods->vdrawFUNC_HILITE" menu item)
 *                  sets up use of the vdrawFUNC_HILITE drawing function
 *
 * -> command -- the function command which caused this activation
 * -> content -- the associated context dictionary
 * <-         -- TRUE if this command was handled, FALSE otherwise
 */
static int useFuncHilite(vcommandFunction *command, vdict *context)
{
  invertSetFunction(vdrawFUNC_HILITE);
  return vTRUE;
}

/* queryFuncComplement -- function invoked by a query command for the menubar
 *                        updates the state of the "Methods" menu based
 *                        on whether or not vwindowComplementColors succeeded
 *
 * Note: the query command will be issued whenever an AssociateAllAttributes
 *       is performed (ie when the menubar is first displayed)
 *
 * -> command -- the function command which caused this activation
 * -> content -- the associated context dictionary
 * <-         -- TRUE if this command was handled, FALSE otherwise
 */
static int queryFuncComplement(vcommandFunction *command, vdict *context)
{

  if (!invertHasComplementColors()) {
    /* disable the Method->vdrawCOMPLEMENT_COLORS menu item */
    vdictStore(context, vname_State, vname_Disabled);
  } else {
    /* make the Method->vdrawCOMPLEMENT_COLORS menu item the default */
    vdictStore(context, vname_Toggle, vname_On);
  }

  return vTRUE;
}

/* useFuncComplement --function invoked when the "complement" command is issued
 *                     (via the "Methods->vdrawFUNC_COMPLEMENT" menu item)
 *                     set the current drawing function to vdrawFUNC_COMPLEMENT
 *                     if available
 *
 * -> command -- the function command which caused this activation
 * -> content -- the associated context dictionary
 * <-         -- TRUE if this command was handled, FALSE otherwise
 */
static int useFuncComplement(vcommandFunction *command, vdict *context)
{
  if (invertHasComplementColors()) {
    invertSetFunction(vdrawFUNC_COMPLEMENT);
  }

  return vTRUE;
}

/* drawRubberRect -- function which draws a rectangle based on the options
 *                   passed it and the state of the invert globals structure
 *
 * -> options -- how to draw the rectangle (outlined or filled)
 * -> rect    -- the rect to draw
 */
static void drawRubberRect(short options, vrect *rect)
{
  vdrawGSave();
  vdialogItemDrawDevice(invertGetItem());

  vdrawSetFunction(invertGetFunction());

  /* Here, the foreground is the hilighting rect, and the background */
  /* is the window's (or dialog item's in our case) foreground       */

  switch(invertGetFunction()) {
  case vdrawFUNC_COMPLEMENT:
    /* The vwindowComplementColors() call sets a complement color for each */
    /* of the colors used in the dialog's foreground so we know exactly    */
    /* what colors are used where.                                         */

    vdrawSetColor(invertGetWhite());     /* white is the new background color */
    vdrawSetComplement(invertGetBlack()); /* black is the new foreground color */
    break;
  case vdrawFUNC_HILITE:
    /* The hilite color is either determined by the system (mac and windows) */
    /* or it's contained in a preferences dictionary (see vgalaxy1.vr:       */
    /* Preferences->Colors->backgroundhilite for an example)                 */
    /* All we need to do here is set the current color to the background ala */
    /* vdrawFUNC_COMPLEMENT, above.                                          */

    /* Note: you should not use vdrawFUNC_HILITE if want a specific color in */
    /* your hilit region! Use vdrawFUNC_COMPLEMENT instead. If you want a    */
    /* system-defined hilighting color to be used, vdrawFUNC_HILITE is best. */
    vdrawSetColor(vdialogDetermineItemBackground(invertGetItem()));
    break;
  case vdrawFUNC_XOR:
    /* use white 'cause white xor white = black on many systems     */
    /* note that the screen may not contain black with this mode!   */
    /* galaxy will xor white with the foreground and use that color */
    vdrawSetColor(invertGetWhite());
    break;
  case vdrawFUNC_INVERT:
    /* No color is needed for the hilighting - galaxy just takes the    */
    /* 1's complement of the current foreground as the hilighting color */
    break;
  }

  /* yeah, I know I don't need to draw the entire rectangle, */
  /* but that's not the point of this demo.                  */
  if (options == invertOUTLINE) {
    vdrawRectStroke(rect->x, rect->y, rect->w, rect->h);
  } else {
    vdrawRectFill(rect->x, rect->y, rect->w, rect->h);
  }

  /* update the cached rect */
  invertUpdateCache(rect->x, rect->y, rect->w, rect->h);
  
  vdrawGRestore();
}

/* disableComplementColors -- notify the user that vwindowComplementColors
 *                            failed and set the appropriate state bits
 *
 * -> message -- what to put in the notify
 */
static void disableComplementColors(const char *message)
{
  vnotice *rats;
  
  /* vwindowComplementColors() failed - notify the user of this */

  rats = vnoticeCreate();
  vnoticeSetCaution(rats, vFALSE);
  vnoticeSetTextScribed(rats, vcharScribeLiteral(message));

  vnoticeProcess(rats);

  invertDisableComplementColors();
}

/* invertInitialize -- initialize any space required for globals
 *                     and set up all internal data structures
 */
static void invertInitialize()
{
  /* table of RGB values for the required colors                    */
  /* order is red, cyan, green, magenta, blue, yellow, white, black */
  const static unsigned int
    colorValues[invertNUM_COMPLEMENTS][invertNUM_COLORS_PER_COMPLEMENT][RGB] =
  {
    {{vcolorCOMPONENT_MAX, vcolorCOMPONENT_MIN, vcolorCOMPONENT_MIN},
     {vcolorCOMPONENT_MIN, vcolorCOMPONENT_MAX, vcolorCOMPONENT_MAX}},
    {{vcolorCOMPONENT_MIN, vcolorCOMPONENT_MAX, vcolorCOMPONENT_MIN},
     {vcolorCOMPONENT_MAX, vcolorCOMPONENT_MIN, vcolorCOMPONENT_MAX}},
    {{vcolorCOMPONENT_MIN, vcolorCOMPONENT_MIN, vcolorCOMPONENT_MAX},
     {vcolorCOMPONENT_MAX, vcolorCOMPONENT_MAX, vcolorCOMPONENT_MIN}},
    {{vcolorCOMPONENT_MAX, vcolorCOMPONENT_MAX, vcolorCOMPONENT_MAX},
     {vcolorCOMPONENT_MIN, vcolorCOMPONENT_MIN, vcolorCOMPONENT_MIN}}
  };

  /* loop counters */
  short i, j;

  /* Allocate space for the application globals structure           */
  _globals = vmemAllocAndClear(sizeof(_invertGlobals));

  /* Set up the complement table. colors[x][0] contain the colors   */
  /* red, green, blue, and white, respectively, and colors[x][1]    */
  /* contains their complements cyan, magenta, yellow, and black.   */

  /* Note that we can't use vcolorInternSpec() because the color    */
  /* manager cannot own these colors (it will blow core if it does) */

  _globals->colors =
    (vcolor ***) vmemAllocAndClear(invertNUM_COMPLEMENTS * sizeof(vcolor **));

  for (i = 0; i < invertNUM_COMPLEMENTS; i++) {

    _globals->colors[i] =
      (vcolor **) vmemAllocAndClear(invertNUM_COLORS_PER_COMPLEMENT *
				    sizeof(vcolor *));

    for (j = 0; j < invertNUM_COLORS_PER_COMPLEMENT; j++) {
      _globals->colors[i][j] = vcolorCreateSpecific(vcolorGetRGBClass());

      vcolorSetSpecRGB(vcolorGetSpec(_globals->colors[i][j]),
		       colorValues[i][j][R],
		       colorValues[i][j][G],
		       colorValues[i][j][B]);
    }
  }

  /* Send the complement table to galaxy - four pairs of colors */
  /* This will fail on displays with a fixed colormap           */
  if (!vwindowComplementColors(_globals->colors,
			       invertNUM_COMPLEMENTS,
			       invertNUM_COLORS_PER_COMPLEMENT)) {
    disableComplementColors("Can't allocate color complements!");
    invertSetFunction(vdrawFUNC_HILITE);

    /* The .vr file has the vdrawFUNC_HILITE menu item selected and */
    /* vdrawFUNC_COMPLEMENT's query function will disable the       */
    /* vdrawFUNC_COMPLEMENT menu item                               */
  } else {
    invertEnableComplementColors();
    invertSetFunction(vdrawFUNC_COMPLEMENT);

    /* The query function for the vdrawFUNC_COMPLEMENT menu item */
    /* will select this menu item "by default"                   */
  }

  /* and initialize the remaining state variables */
  invertRectClear();
  invertSetForeground(invertFILLED);
  invertSetBackground(invertSTRIPED);
}

/* invertDestroy -- free up all space allocated for globals
 */
static void invertDestroy()
{
  int i, j;
  
  for (i = 0; i < invertNUM_COMPLEMENTS; i++) {
    for (j = 0; j < invertNUM_COLORS_PER_COMPLEMENT; j++) {
      vcolorDestroy(_globals->colors[i][j]);
    }
    vmemFree(_globals->colors[i]);
  }
  vmemFree(_globals->colors);

  vmemFree(_globals);
}

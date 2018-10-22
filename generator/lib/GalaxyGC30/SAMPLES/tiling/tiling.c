/* $Id: tiling.c,v 1.6 1997/09/22 15:53:11 barry Exp $
 **************************************************************************
 *  Penrose Tiling - Sample Galaxy Application...
 *
 *  The following Sample Code is provided for your reference purposes in
 *  connection with your use of the Galaxy Application Environment (TM)
 *  software product which you have licensed from Visix Software, Inc.
 *  ("Visix"). The Sample code is provided to you without any warranty of any
 *  kind whatsoever and you agree to be responsible for the use and/or
 *  incorporation of the Sample Code into any software product you develop.
 *  You agree to fully and completely indemnify and hold Visix harmless from
 *  any and all loss, claim, liability or damages with respect to your use of
 *  the Sample Code.
 *  Subject to the foregoing, you are permitted to copy, modify, and
 *  distribute the Sample Code for any purpose and without fee, provided that
 *  (i) a copyright notice in the in the form of "Copyright 1994 Visix
 *  Software Inc., 11440 Commerce Park Drive, Reston, VA  22091. All Rights
 *  Reserved" appears in all copies, (ii) both the copyright notice and this
 *  permission notice appear in supporting documentation and (iii) you are a
 *  valid licensee of Galaxy Application Environment.
 **************************************************************************/

/***************************************************************************
 * executable:    tiling
 * .c files:      tiling.c
 * .h files:      tiling.h
 * resource file: tiling.vr
 *
 * managers illustrated: Command Manager
 *                       Drawing Manager
 *                       Class   Manager
 *                       Resource Manager
 *
 *  The tiling program draws quasi periodical Penrose tiling 
 *  of the plane. You can select different dimension of the 
 *	tiling from 3 to 13 from the Options menu.   
 *
 * This program illustrates how to associate application code to user
 * interface items using selector commands (instead of notify
 * functions). It also illustrates how to do simple subclassing and how
 * to use some of the drawing manager functionality.
 *
 * This sample gives an example how to write Galaxy application 
 * starting from the similar application written using Microsoft 
 * Windows SDK. It may be useful as a starting point for developers 
 * already familiar with MSW SDK.  Tilingw - application with the same 
 * functionality and user interface but written by MSW SDK API is 
 * included (for  MS-Windows platforms, files  tilingw.c, gridw.c 
 * tilingw.h  tilingw.ico, tilingw.rc). 
 * 
 * To end  the demo, choose "Exit" from the File menu. 
 *
 ***************************************************************************/

#ifndef  vportINCLUDED
#include <vport.h>		/* for v*HEADER */
#endif

#ifndef  vstdlibINCLUDED
#include vstdlibHEADER		/* for EXIT_SUCCESS */
#endif

#ifndef  vdictINCLUDED
#include vdictHEADER
#endif

#ifndef  veventINCLUDED
#include veventHEADER
#endif

#ifndef  vapplicationINCLUDED
#include vapplicationHEADER
#endif

#ifndef  vcommandINCLUDED
#include vcommandHEADER
#endif

#ifndef  vnameINCLUDED
#include vnameHEADER
#endif

#ifndef  vresourceINCLUDED
#include vresourceHEADER
#endif

#ifndef  vdialogINCLUDED
#include vdialogHEADER
#endif

#ifndef  vconfirmINCLUDED
#include vconfirmHEADER
#endif

#ifndef  vstartupINCLUDED
#include vstartupHEADER
#endif

#include vbuttonHEADER
#include vcontrolHEADER

#include "tiling.h"


int   xClient, yClient;
int   ScrX0;
int   ScrY0;
int   TilingSize = SIZE_MEDIUM;  /* 0 Auto, 1 Small , 2 Medium, 3 Large */
vbool AutoSize = FALSE;

vcolor *colorSet[10];

vapplication           *application; /* current application         */
vresource               resources;   /* application resource file   */
vresource               resUser;     /* user preferences file       */
vdialog                *ApplDialog;  /* application's main dialog   */
vcommandSelectorClass  *ApplSelectorClass = NULL;
vimage                 *icon;  /* icon for our application  */

vdialog  *AboutDialog  = NULL;
vconfirm *OptionsConfirm = NULL;


/*
 * Integer selectors for each of our commands. These selectors are used
 * to differentiate the commands coming into our IssueCommand() function.
 */
enum
  {
  comEXIT,
  comOPTIONS,
  comABOUT,
  comOPTIONS_OK,
  comOPTIONS_CANCEL,
  comABOUT_OK
  };

/*
 * The tags for each of our commands. These are the tags assigned to each
 * corresponding menu item in vre. These tags are associated with command
 * objects in the command dictionary in our application command space set
 * up in main().
 */
static const char *commandNames[] =
  {
  "Exit",
  "Options",
  "About",
  "Ok",
  "Cancel",
  "AboutOK"
	};

/***************************************************************************
*  IssueCommand()
*
*  The dispatch point for all the commands associated with the
*  application menu, Options ans About dialogs
*  (This function is an override of the vcommandISSUE method defined
*  originally for the Selector class).
***************************************************************************/
static int IssueCommand(vcommandSelector *command, vdict *attr2value)
{
  vdialog         *dialog;
  vdialogItem     *IconItem;
  vdialogItem     *DrawItem;
  vdialog         *OptionsDialog;
  static vcontrol *SizeItem;
  static vcontrol *DimensionItem;
  static vcontrol *FillItem;
  static vcontrol *SaveAsDefItem;
  static int       svSize;
  static int       svDim;
  static vbool     svFill;
  static int       bSaveAsDef = 0;

  dialog = (vdialog *)vdictLoad(attr2value, vname_Dialog);

  switch (vcommandGetSelector(command))
    {
    case comEXIT:
         veventStopProcessing();
         break;

    case comOPTIONS:
         svSize = TilingSize;
         svDim  = MaxGrid;
         svFill = bFillTiling;

         if (OptionsConfirm == NULL)
           {
           OptionsConfirm = vconfirmLoad(vresourceGet(resources,
                                   vnameInternGlobalLiteral("OptionsDialog")));
	   }

         OptionsDialog = vconfirmGetDialog(OptionsConfirm);
         SizeItem = (vcontrol *)vdialogFindItem(OptionsDialog,
         vnameInternGlobalLiteral("SizeOptionsMenu"));
         vcontrolSetValue(SizeItem, TilingSize);
         DimensionItem = (vcontrol *)vdialogFindItem(OptionsDialog,
         vnameInternGlobalLiteral("DimOptionsMenu"));
         vcontrolSetValue(DimensionItem, (MaxGrid-1)/2 - 1);
         FillItem = (vcontrol *)vdialogFindItem(OptionsDialog,
         vnameInternGlobalLiteral("FillCheckBox"));
         vcontrolSetValue(FillItem, bFillTiling);
         SaveAsDefItem = (vcontrol *)vdialogFindItem(OptionsDialog,
         vnameInternGlobalLiteral("SaveAsDef"));
         vcontrolSetValue(SaveAsDefItem, bSaveAsDef);

         if (!vconfirmIsOpen(OptionsConfirm))
           { 
           vwindowPlace(vconfirmGetWindow(OptionsConfirm),
           vdialogGetWindow(dialog),  vrectPLACE_CENTER, vrectPLACE_CENTER);
           vconfirmOpen(OptionsConfirm); 
           }
         else
           vwindowRaise(vconfirmGetWindow(OptionsConfirm));
       
         break;

    case comOPTIONS_OK:
         bFillTiling = (vcontrolGetValue(FillItem) != 0);
         TilingSize  = vcontrolGetValue(SizeItem);
         MaxGrid     = 2 * (vcontrolGetValue(DimensionItem)+1) + 1;

         /*
          * update tiling if parameters were changed
          */
         if (svSize != TilingSize || svDim != MaxGrid ||
           svFill != bFillTiling)
           {
           SetupParam();
           DrawItem = vdialogFindItem(dialog,
                                      vnameInternGlobalLiteral("DrawItem"));
           if (bFillTiling)
             vwindowInval((vwindow *)ApplDialog, vwindowINVAL_OPAQUE);
           else
             vwindowInval((vwindow *)ApplDialog, 0);
           }
				 
         if ((bSaveAsDef = vcontrolGetValue(SaveAsDefItem)) == 1)
           /*
            * Save user preferences to the user resourse file
            */
           WriteIniFile(resUser);
    
         vconfirmClose(OptionsConfirm);
         break;


    case comOPTIONS_CANCEL:
         vconfirmClose(OptionsConfirm);
         break;


    case comABOUT:
         if (AboutDialog == NULL)
           {
           AboutDialog = vdialogLoad(vresourceGet(resources,
                                       vnameInternGlobalLiteral("AboutDialog")));
           vwindowAddStyle(vdialogGetWindow(AboutDialog), vwindowSTYLE_CONFIRM);   
           IconItem = vdialogFindItem(AboutDialog,
                                       vnameInternGlobalLiteral("IconItem"));
           vdialogSetItemImage(IconItem, icon);
	   }

         if (!vdialogIsOpen(AboutDialog))
            {
           vwindowPlace(vdialogGetWindow(AboutDialog),
                         vdialogGetWindow(dialog), vrectPLACE_CENTER, vrectPLACE_CENTER);
           vdialogOpen(AboutDialog);   
           }
         else
           vwindowRaise(vdialogGetWindow(AboutDialog));

         break;

    case comABOUT_OK:
        /*
         *   close About dialog 
         */
         vdialogClose(AboutDialog);
         break;

    default:
         return vclassSendSuper(ApplSelectorClass, vcommandISSUE,
                                  (command, attr2value));
    }

  return TRUE;
  }

/***************************************************************************
*  DrawItemProc()
*
*  The drawing procedure for the DrawItem.
*  (This function is an override of the  method defined
*  originally for the vdialogItem class.)
***************************************************************************/

void DrawItemProc(vdialogItem *item)
  {
  const vrect *rect;
  int          rectX, rectY, rectW, rectH;
  vwindow      *window;
  vdialog      *dialog;
  int           i, j, knum;
  vcolorSpec   *spec;
  vcolor       *color;
  double       rColr, gColr, bColr;

  dialog = vdialogDetermineItemDialog(item);
  window = vdialogGetWindow(dialog);
  vwindowBlock(window);
  rect = vdialogGetItemRect (item);
  rectX = rect->x;
  rectY = rect->y;
  rectW = rect->w;
  rectH = rect->h;

  vdrawGSave();

  vdrawRectClip(rectX, rectY, rectW, rectH);
  vdrawSetColor(vwindowDetermineForeground(window));
  vdrawSetLineWidth(1);

  xClient = rectW;
  yClient = rectH;
  ScrX0 = xClient / 2;
  ScrY0 = yClient / 2;
  vdrawTranslate(xClient / 2, yClient / 2);

  /* set paremeters and size of the grid */
  SetupParam();
  /* start drawing */
  spec = vcolorCreateSpec();
  knum = 0;

  for (i = 1;     i <= MaxGrid; i++)
    {
    for (j = i + 1; j <= MaxGrid; j++)
      {
      /* create the color to draw set of rhombusa  */
      if (bFillTiling)
        {
        if (MaxGrid <= 5)
          {
          color = colorSet[knum];
          vdrawSetColor(color);
          }
        else
          {
          rColr = 0.25 * (knum % 5);
          gColr = 0.25  * (((knum+1) / 4) % 4);
          bColr = 0.25 * ((knum +1) % 4);

          vcolorFSetSpecRGB(spec, rColr, gColr, bColr);
          color = vcolorInternSpec(spec);
          vdrawSetColor(color);
          }
        }
     /*
      * draw set of rhombus for the pair of vectors g[i], g[j]
      */
      if ( !ProcessVectors(g[i], g[j], d[i], d[j]) )
        break;
      knum++;
      }  /* end of j loop */
    };   /* end of i loop */

  vcolorDestroySpec(spec);

  vdrawGRestore();
  vwindowUnblock(window);
  }

/***************************************************************************
*  SetupParam()
*  sets parameters of the tiling
***************************************************************************/
void SetupParam(void)
  {
  double  sl;
  int     i;

  switch (TilingSize)
    {
    case SIZE_AUTO:
       break;
    case SIZE_SMALL:
       Rsize = 30;
       break;
    case SIZE_MEDIUM:
       Rsize = 60;
       break;
    case SIZE_LARGE:
       Rsize = 120;
       break;
    default:
       TilingSize = SIZE_MEDIUM;
       Rsize = 60;
       break;
    }

  if (MaxGrid > NumMaxGrid)
    MaxGrid = NumMaxGrid;

   kdim = 1;

  if (TilingSize != SIZE_AUTO)
    {
    sl = (MaxGrid-1)* kdim*Rsize;
    MaxStep = (int) ceil((xClient+yClient)/(2*sl))+1;
    }
  else
    {
    MaxStep = 2;
    Rsize = (xClient+yClient)/(3*(MaxStep-1)*kdim*(MaxGrid-1));
    };

   alfa0 = 2.0 * PI/MaxGrid;
   for (i = 1; i <= MaxGrid; i++)
     {
     alfa[i] = alfa0 * (i-1);
     g[i][1] = Rsize*cos(alfa[i]);
     g[i][2] = Rsize*sin(alfa[i]);
     d[i] =  Rsize * 0.3333;
     };
  }

/***************************************************************************
*  SetupColors()
*  fills array of colors to draw tiling for 3 and 5 dimensions
***************************************************************************/
void SetupColors(void)
  {
  vcolorSpec   *spec;
  int           full;
  int           half;

  full = vcolorCOMPONENT_MAX;
  half = 128*(vcolorCOMPONENT_MAX/255); 
  spec = vcolorCreateSpec();

  vcolorSetSpecRGB(spec, full,   0,   0);
  colorSet[0] = vcolorInternSpec(spec);
  vcolorSetSpecRGB(spec, 0,   full, full);
  colorSet[1] = vcolorInternSpec(spec);
  vcolorSetSpecRGB(spec, 0,     0, full);
  colorSet[2] = vcolorInternSpec(spec);
  vcolorSetSpecRGB(spec, 0,   full,   0);
  colorSet[3] = vcolorInternSpec(spec);
  vcolorSetSpecRGB(spec, 0,     0, half);
  colorSet[4] = vcolorInternSpec(spec);
  vcolorSetSpecRGB(spec, full, full,   0);
  colorSet[5] = vcolorInternSpec(spec);
  vcolorSetSpecRGB(spec, half, half, half);
  colorSet[6] = vcolorInternSpec(spec);
  vcolorSetSpecRGB(spec, half,   0,   0);
  colorSet[7] = vcolorInternSpec(spec);
  vcolorSetSpecRGB(spec, full,   0, full);
  colorSet[8] = vcolorInternSpec(spec);
  vcolorSetSpecRGB(spec, 0,   half, half);
  colorSet[9] = vcolorInternSpec(spec);

  vcolorDestroySpec(spec);
  }

/**************************************************************************
* HandleDialog
*   the callback function for the main dialog
*   This stops processing, and we
*   fall through the other side of the veventProcess ();
*
*  -> dialog -- the dialog that was notified.
*  -> event  -- the event that triggered it.
***************************************************************************/
static void HandleDialog (vdialog *dialog, vevent *event)
  {
  if ((veventGetType(event) == veventWINDOW_STATE) && veventIsClose (event))
    {
    veventStopProcessing ();
    }
  } /* HandleDialog */

/***************************************************************************
*  ReadIniFile()
*  reads initial values of parameters from the resource file
*  -> resource file to read from
*  <- TRUE if success, FALSE otherwise
***************************************************************************/
vbool ReadIniFile(vresource res)
  {
  int ival = 0;

  if (res == vresourceNULL)
    return FALSE;

  vexWITH_HANDLING
    {
    ival =  vresourceGetInteger(res, vnameInternGlobalLiteral("size"));

    if ( (ival >= SIZE_AUTO) && (ival <= SIZE_LARGE))
      TilingSize = ival;
    else
      TilingSize = SIZE_MEDIUM;

    ival =  vresourceGetInteger(res, vnameInternGlobalLiteral("dimension"));

    if ( (ival >= 3)  && (ival <= NumMaxGrid) && (ival % 2 != 0) )
      MaxGrid = ival;
    else
      MaxGrid = 5;

    ival =  vresourceGetInteger(res, vnameInternGlobalLiteral("fill"));

    if (ival == 0)
      bFillTiling = FALSE;
    else
      bFillTiling = TRUE;
    }
   vexON_EXCEPTION
    {
	 return FALSE;
    }
  vexEND_HANDLING;

  return TRUE;
  }

/**************************************************************************
*   WriteIniFile()
*
*   Saves user preferences (options)
*  -> resource file to write to
*  <- TRUE if success, FALSE otherwise
***************************************************************************/
vbool  WriteIniFile(vresource res)
  {
  int  ival;

  vexWITH_HANDLING
    {
    vresourceSetInteger(res, vnameInternGlobalLiteral("size"), TilingSize);
    vresourceSetInteger(res, vnameInternGlobalLiteral("dimension"), MaxGrid);
    if (bFillTiling)
      ival = 1;
    else
      ival = 0;
    vresourceSetInteger(res, vnameInternGlobalLiteral("fill"), ival);
    }
  vexON_EXCEPTION
    {
    return FALSE;
    }
  vexEND_HANDLING;

  return TRUE;
  }


/***************************************************************************
 * main()
 *
 * The main program.
 * Set up our vcommandSelector subclass and our vdialogItem subclass, then
 * start the demo by entering the event processing loop.
***************************************************************************/
int main(int argc, char **argv)
  {
  int               i;
  vcommandSpace     *space;
  vdict             *dict;
  vcommandSelector  *command;
  vdialogItemClass  *DrawItemClass;
  const vrect       *rScreen;
  vrect              rWin;

  vstartup(argc, argv);
  /*
   * Subclass the Selector command class to customize it for our own selectors.
   */
  ApplSelectorClass = vclassReproduce(vcommandGetDefaultSelectorClass());

  /*
   * Set the vcommandISSUE message to refer to our own IssueCommand() function
   * that dispatches work based on our own selectors. In other words,
   * override our parent's vcommandIssue() function.
   */
  vclassSet(ApplSelectorClass, vcommandISSUE, IssueCommand);

  /*
   * Create a command space and store it in our application.
   */
  application = vapplicationGetCurrent();
  space = vcommandCreateSpace();
  dict = vdictCreate(vnameHash);

  /*
   * Create our four individual Selector commands, set their numerical
   * selector values, and map them to string tags by Storing
   * each <tag, command> pair in the dict dictionary.
   */
  for (i = comEXIT; i <= comABOUT_OK; i++)
    {
    command = vcommandCreateSelectorOfClass(ApplSelectorClass);
    vcommandSetSelector(command, i);
    vdictStore(dict, vnameInternGlobalLiteral(commandNames[i]), command);
    }

  vcommandAddSpaceDictOwned(space, vname_Command, dict);
  vapplicationSetSpaceOwned(application, space);

  /*
   * Create a subclass of vdialogItem so that we can override it's
   * drawing method to draw.
   */
  DrawItemClass = vclassReproduce(vdialogGetDefaultItemClass());
  vclassSetNameScribed(DrawItemClass, vcharScribeLiteral("DrawItem"));

  /*
   * Set the vdialogDRAW_ITEM message to refer to our own DrawItemProc()
   * function that contains code to draw the tiling.
   */
  vclassSet(DrawItemClass, vdialogDRAW_ITEM, DrawItemProc);

  resources = vapplicationGetResources(application);
  resUser   = vapplicationGetPreferences(application);
  ApplDialog = vdialogLoad(vresourceGet(resources,
                        vnameInternGlobalLiteral("ApplDialog")));

  icon   = vimageLoad(vresourceGet(resources,
                       vnameInternGlobalLiteral("Icon")));

  vdialogSetIcon(ApplDialog, icon);

  vdialogSetNotify(ApplDialog, HandleDialog);
  /*
   *    set the size and position of the dialog vindow on the screen
   */
  rScreen  = vwindowGetRect(vwindowGetRoot());
  rWin.w = (int)(0.6*rScreen->w);
  rWin.h = (int)(0.6*rScreen->h);
  rWin.x = (int)(0.2*rScreen->w);
  rWin.y = (int)(0.2*rScreen->h);
  vwindowMove((vwindow *)ApplDialog, rWin.x, rWin.y);
  vwindowSetRect((vwindow *)ApplDialog, &rWin);

  ReadIniFile(resUser);
  SetupColors();
  SetupParam();
  vdialogOpen(ApplDialog);

  /*
   *  main event loop
   */
  veventProcess();

  if (OptionsConfirm != NULL)
    vconfirmDestroy(OptionsConfirm);
  if (AboutDialog != NULL)
    vdialogDestroy(AboutDialog);

  vdialogDestroy(ApplDialog);

  exit(EXIT_SUCCESS);
  return EXIT_FAILURE;
  }
/**************************************************************************/

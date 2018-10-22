/* $Id: drawdemo.h,v 1.9 1993/12/07 05:12:35 jim Exp $
 *
 * Copyright 1992-1993 Visix Software Inc., 11440 Commerce Park Drive, 
 * Reston, VA  22091. All Rights Reserved.
 */

/************************************************************

    drawdemo.h
    C Interface to galaxy draw demo

************************************************************/

#ifndef drawdemoINCLUDED
#define drawdemoINCLUDED 1

#include <vport.h>	/* for #include symbols */

/* ANSI headers */
#include vstdlibHEADER	/* for exit(), srand() */
#include vtimeHEADER	/* for time() and time_t */

/* Galaxy headers */
#include vapplicationHEADER
#include veventHEADER
#include vnumHEADER
#include vtextHEADER
#include vtextviewHEADER
#include vclassHEADER
#include vdialogHEADER
#include vcolorHEADER
#include vdrawHEADER
#include vbuttonHEADER
#include vmenuHEADER
#include vhelpHEADER
#include vtextitemHEADER
#include vfontchsrHEADER
#include vstartupHEADER

/*
 * * * * * * * * * CONSTANTS AND MACRO DEFINITIONS * * * * * * * * * *
 */

/**********
 * Counts for the arrays
 **********/

#define drawdemoOBJECT_TYPES	5
#define drawdemoFILL_TYPES	6
#define drawdemoLINE_CAPS	3
#define drawdemoLINE_JOINS	3
#define drawdemoPHRASES		29

/**********
 * Types of objects that can be drawn in this demo:
 **********/

enum
{
  drawdemoDRAW_LINES,		/* Straight poly-lines			*/
  drawdemoDRAW_RECTS,		/* Upright rectangles			*/
  drawdemoDRAW_CURVES,		/* Curved poly-lines			*/
  drawdemoDRAW_ARCS,		/* Poly-arcs				*/
  drawdemoDRAW_CCW_ARCS,	/* Single counter-clockwise arcs	*/
  drawdemoDRAW_CW_ARCS,		/* Single clockwise arcs		*/
  drawdemoDRAW_TEXT,		/* Short text strings			*/
  drawdemoDRAW_IMAGES		/* Small images				*/
};

/**********
 * Types of fills that can be used in this demo:
 **********/

enum
{
  drawdemoSTROKE,		/* Outlined				*/
  drawdemoFILL,			/* Filled, without outline		*/
  drawdemoEO_FILL,		/* Alternate (even-odd) fill technique	*/
				/*   which fills only every other	*/
				/*   enclosed space			*/
  drawdemoCLIP,			/* Straight lines clipped by object	*/
  drawdemoEO_CLIP,		/* Alternate (even-odd) clip technique	*/
  drawdemoBORDERED		/* Filled and outlined			*/
};


/**********
 * Global variable for the files
 **********/

extern vfont			*drawdemoFont;
extern vcolor			*drawdemoColor;

extern vdialogClass		*drawdemoHookedDialogClass;
extern vdialog			*drawdemoDialog;
extern vdialogItemClass		*drawdemoFabricClass;
extern vdialogItem		*drawdemoFabric;

extern vcontrol			*drawdemoDedicatedCheckBox;
extern vcontrol			*drawdemoOneAtTimeCheckBox;
extern vtextitem		*drawdemoObjectCountText;
extern vcontrol			*drawdemoObjectTypePopup;
extern vmenu			*drawdemoObjectTypePopupMenu;
extern vcontrol			*drawdemoMonochromeCheckBox;
extern vcontrol			*drawdemoExclusiveOrCheckBox;
extern vcontrol			*drawdemoFillTypePopup;
extern vmenu			*drawdemoFillTypePopupMenu;
extern vtextitem		*drawdemoRotateAngleText;
extern vtextitem		*drawdemoScaleXText;
extern vtextitem		*drawdemoScaleYText;
extern vtextitem		*drawdemoLineWidthText;
extern vtextitem		*drawdemoFlatnessText;
extern vcontrol			*drawdemoDashedCheckBox;
extern vcontrol			*drawdemoLineCapPopup;
extern vmenu			*drawdemoLineCapPopupMenu;
extern vcontrol			*drawdemoLineJoinPopup;
extern vmenu			*drawdemoLineJoinPopupMenu;
extern vtextitem		*drawdemoMiterLimitText;
extern vbutton			*drawdemoStartButton;
extern vbutton			*drawdemoChangeFontButton;
extern vbutton			*drawdemoCloseButton;

/*
 * * * * * * * * * TYPE AND STRUCTURE DEFINITIONS * * * * * * * * * *
 */

/*
 * * * * * * * * * FUNCTION PROTOTYPES * * * * * * * * * * * * * * * *
 */

void drawdemoMakeClasses(
  void
);

void drawdemoLoad(
  void
);

void drawdemoSetNotifyStuff(
  void
);

void drawdemoUnload(
  void
);

void drawdemoOpen(
  void
);

void drawdemoClose(
  void
);

void drawdemoDialogNotify(
  vdialog			*dialog,
  vevent			*event
);

int drawdemoApplyFont(
  vfontchsr			*chooser,
  vfont				*font
);

void drawdemoNotifyStartButton(
  vbutton                        *button,
  vevent                         *event
);

void drawdemoNotifyChangeFontButton(
  vbutton                        *button,
  vevent                         *event
);

void drawdemoNotifyCloseButton(
  vbutton                        *button,
  vevent                         *event
);

int drawdemoHandleMouseDown(
  vdialog			*dialog,
  vevent			*event
);

void drawdemoDraw(
  vdialogItem			*item
);

int drawdemoHandleCustomEvent(
  vevent			*event
);

void drawdemoDrawSetup(
  void
);

void drawdemoDrawOne(
  void
);


/*
 * * * * * * * * GLOBAL VARIABLES * * * * * * * * * *
 */

#endif  /**  drawdemoINCLUDED  **/


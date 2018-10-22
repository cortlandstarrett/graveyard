/* $Id: spread.h,v 1.2 1994/12/29 04:12:00 skip Exp $ */
/*
 * The following Sample Code is provided for your reference purposes in
 * connection with your use of the Galaxy Application Environment (TM) software
 * product which you have licensed from Visix Software, Inc. ("Visix").
 * The Sample code is provided to you without any warranty of any kind
 * whatsoever and you agree to be responsible for the use and/or incorporation
 * of the Sample Code into any software product you develop. You agree to fully
 * and completely indemnify and hold Visix harmless from any and all loss,
 * claim, liability or damages with respect to your use of the Sample Code.  
 *
 * Subject to the foregoing, you are permitted to copy, modify, and distribute
 * the Sample Code for any purpose and without fee, provided that (i) a
 * copyright notice in the in the form of "Copyright 1994 Visix Software Inc.,
 * 11440 Commerce Park Drive, Reston, VA  22091. All Rights Reserved" appears
 * in all copies, (ii) both the copyright notice and this permission notice
 * appear in supporting documentation and (iii) you are a valid licensee of
 * Galaxy Application Environment.
 */

/* 
 * spread.h -- Header file for the spreadsheet sample.  
 *
 * See the file spread.c for more information.
 */

#include <vport.h>

#include vstdlibHEADER
#include vstartupHEADER
#include vapplicationHEADER
#include vtextitemHEADER
#include vtextviewHEADER
#include vcontainerHEADER
#include vresourceHEADER
#include vdialogHEADER
#include vnoticeHEADER
#include vcontrolHEADER
#include vmenubarHEADER
#include vmenuHEADER
#include vfontHEADER
#include vdrawHEADER
#include vlistHEADER
#include vlistviewHEADER
#include vlistsizeHEADER
#include vstrHEADER
#include vnumHEADER
#include vmemHEADER 
#include vspinnerHEADER
#include vpointHEADER
#include vcursorHEADER
#include vexHEADER

/* "fudge" factors for displaying text in cells */
#define FONT_OFFSET_X           2
#define FONT_OFFSET_Y           6

/* types of spreadsheet data */
#define SPREAD_STRING           0x10
#define SPREAD_DOUBLE           0x20

/* markers for clean and dirty data */
#define SPREAD_CLEAN            0x00
#define SPREAD_DIRTY            0x01

/* format types for spreadsheet data */
#define SPREAD_RIGHT_JUSTIFY    0x10
#define SPREAD_DOLLARS          0x20
#define SPREAD_COMMAS           0x40

/* maximum number of digits after decimal */
#define MAX_PRECISION           8

/* copy types */
#define COPY_OFF                0
#define COPY_RANGE              1
#define COPY_PAGE               2
#define REPLICATE_ROW           3
#define REPLICATE_COLUMN        4
#define REPLICATE_CELL          5
#define FILL_PAGE_CELL          6
#define FILL_PAGE_ROW           7
#define FILL_PAGE_COLUMN        8

/* movement type */
#define SPREAD_HOME             0
#define SPREAD_END              1
#define SPREAD_PAGE_UP          2
#define SPREAD_PAGE_DOWN        3

/* extern number formats */
extern vnumFormat       *dollarFormat;
extern vnumFormat       *commaFormat;
extern vnumFormat       *commaDollarFormat;

/* extern classes */
extern vlistviewClass   *spreadviewClass;
extern vlistviewClass   *rowviewClass;
extern vlistviewClass   *columnviewClass;
extern vtextClass       *editTextClass;

/* extern copy globals */
extern int copyingOn;
extern int copyRow;
extern int copyColumn;
extern int copyAcross;
extern int copyDown;

/* extern value globals */
extern long lastMultiplyValue;
extern long lastAddValue;
extern long lastEscalationRate;

/* extern width globals */
extern char lastCellWidth;
extern char lastLabelWidth;

typedef struct
{
    vdialog         *spreadDialog;
    vdialog         *valueDialog;
    vdialog         *searchDialog;
    vdialog         *gotoDialog;
    vdialog         *widthDialog;
    vdialog         *repCellDialog; 
    vdialog         *formatDialog;
    vnotice         *okNotice;
    vlist           *spreadList;
    vlistview       *spreadView;
    vlist           *rowList;
    vlistview       *rowView;
    vlist           *columnList;
    vlistview       *columnView;
    vfont           *font;
    char            fontWidth;
    char            fontHeight;
    long            currentRow;
    long            currentColumn;
    long            lastRow;
    long            lastColumn;
    short           rowHeight;
    short           columnWidth;
    short           rowLabelWidth;
    long            numRows;
    long            numColumns;
    char            cellCharWidth;
    char            labelCharWidth;
    char            currentOperation;
    char            *rowFormat;
    vtextitem       *informationDisplay;
    vtextitem       *unitsDisplay;
    vtextitem       *messageDisplay;
    vtextview       *editView;
    vtext           *editData;
    vtextSelection  *editSelection;
    vcursor         *standardCursor;
    vcursor         *copyCursor;
} spreadStruct;

typedef union
{
    double  value;
    vstr    *string;
} dataUnion;

typedef struct
{
    char            type;
    dataUnion       data;
} spreadData;

/* dialog notify prototypes */
void spreadDialogNotify(vdialog *dialog, vevent *event);
void spreadHandleItemButtonDown(vdialogItem *item, vevent *event);

/* file menu command prototypes */
int quitSpreadsheet(vcommandFunction *command, vdict *context);

/* edit menu command prototypes */
int replicateCell(vcommandFunction *command, vdict *context);
int copyRange(vcommandFunction *command, vdict *context);

/* operations menu command prototypes */
int multiplyRange(vcommandFunction *command, vdict *context);
int addRange(vcommandFunction *command, vdict *context);

/* spreadsheet menu command prototypes */
int transposeSpreadsheet(vcommandFunction *command, vdict *context);
int setWidths(vcommandFunction *command, vdict *context);
int setFormat(vcommandFunction *command, vdict *context);

/* goto menu command prototypes */
int gotoCell(vcommandFunction *command, vdict *context);
int searchFor(vcommandFunction *command, vdict *context);

/* listview notify prototypes */
void spreadviewNotifyScroll(vlistview *listview, int horzDistance, int vertDistance);
void spreadviewNotifySelect(vlistview *listview, int type);
void spreadviewItemNotify(vdialogItem *item, vevent *event);

/* edit text notify prototypes */
void editViewDrawBackground(vtextview *textview, vrect *area);
void editViewDrawCaret(vtextview *textview, vrect *caret);
void editViewHiliteCaret(vtextview *textview, int state);
void editViewNotify(vtextview *textview, vevent *event, long message);
void editTextInsert(vtext *text, vtextSelection *selection,
                    const vchar *nextChar, long length);
void editTextDelete(vtext *text, vtextSelection *selection);
double getTextAsFloat(spreadStruct *spreadSheet);

/* dialog button notify prototypes */
void gotoOKNotify(vbutton *button, vevent *event);
void gotoApplyNotify(vbutton *button, vevent *event);
void gotoCancelNotify(vbutton *button, vevent *event);

void searchOKNotify(vbutton *button, vevent *event);
void searchApplyNotify(vbutton *button, vevent *event);
void searchCancelNotify(vbutton *button, vevent *event);

void valueOKNotify(vbutton *button, vevent *event);
void valueApplyNotify(vbutton *button, vevent *event);
void valueCancelNotify(vbutton *button, vevent *event);

void widthOKNotify(vbutton *button, vevent *event);
void widthCancelNotify(vbutton *button, vevent *event);
void rowWidthSliderNotify(vcontrol *control, vevent *event);
void columnWidthSliderNotify(vcontrol *control, vevent *event);

void repCellOKNotify(vbutton *button, vevent *event);
void repCellApplyNotify(vbutton *button, vevent *event);
void repCellCancelNotify(vbutton *button, vevent *event);
void repCellExGroupNotify(vcontainer *container, vevent *event);

void formatOKNotify(vbutton *button, vevent *event);
void formatApplyNotify(vbutton *button, vevent *event);
void formatCancelNotify(vbutton *button, vevent *event);

/* custom cell drawing prototypes */
void spreadviewDrawCellBackground(vlistview *listview, int row, int column,    
				  int selected, vrect *rect);
void spreadviewDrawCellContents(vlistview *listview, int row, int column,      
                                int selected, vrect *rect);
void rowviewDrawCellBackground(vlistview *listview, int row, int column,    
                               int selected, vrect *rect);
void rowviewDrawCellContents(vlistview *listview, int row, int column,      
                             int selected, vrect *rect);
void columnviewDrawCellBackground(vlistview *listview, int row, int column, 
                                  int selected, vrect *rect);
void columnviewDrawCellContents(vlistview *listview, int row, int column,      
                                int selected, vrect *rect);

/* convenience function prototypes */
void setFunctionCommands(vdialog *dialog, 
			 vcommandFunctionTemplate commandBindings[],
			 int commandCount);

/* notice function prototypes */
void raiseOKNotice(spreadStruct *spreadSheet, vdialog *baseDialog,
                   vscribe *title, vscribe *text);

/* edit cell function prototypes */
void setEditCell(spreadStruct *spreadSheet);
void unsetEditCell(spreadStruct *spreadSheet);
void focusEditCell(spreadStruct *spreadSheet);
void setEditRect(spreadStruct *spreadSheet);

/* selection prototypes */
void selectFocus(spreadStruct *spreadSheet);
void selectRowChange(spreadStruct *spreadSheet);
void selectColumnChange(spreadStruct *spreadSheet);
void selectChange(spreadStruct *spreadSheet);

/* spreadsheet setup and release prototypes */
void setupSpreadsheet(spreadStruct *spreadSheet);
void setupRowLabels(spreadStruct *spreadSheet);
void setupColumnHeadings(spreadStruct *spreadSheet);
void releaseSpreadsheet(spreadStruct *spreadSheet);
void releaseRowLabels(spreadStruct *spreadSheet);
void releaseColumnHeadings(spreadStruct *spreadSheet);
int loadSpreadsheetData(spreadStruct *spreadSheet);
int openSpreadsheet(spreadStruct *spreadSheet);
void changeSizes(spreadStruct *spreadSheet, int refresh);

/* spreadsheet resource create and destroy prototypes */
int createSpreadsheetClasses(void);
int destroySpreadsheetClasses(void);
int loadSpreadsheetDialog(spreadStruct *spreadSheet, vresource rootRes);
int unloadSpreadsheetDialog(spreadStruct *spreadSheet);
int loadPopupDialogs(spreadStruct *spreadSheet, vresource rootRes);
int unloadPopupDialogs(spreadStruct *spreadSheet);
int loadCursors(spreadStruct *spreadSheet, vresource rootRes);
int unloadCursors(spreadStruct *spreadSheet);

/* number format create and destroy prototypes */
void createNumFormats(void);
void destroyNumFormats(void);

/* spreadsheet sizing and display prototypes */
void setupSizes(spreadStruct *spreadSheet);
void setupVisible(spreadStruct *spreadSheet, int initial);

/* copy routine prototypes */
void executeCopy(spreadStruct *spreadSheet);

/* message prototypes */
void changeMessage(vtextitem *textItem, vscribe *message);


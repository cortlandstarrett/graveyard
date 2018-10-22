/* $Id: spread.c,v 1.5 1995/01/19 03:22:45 skip Exp $ */
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
 * Executable Name: spread
 * Source Files:    spcom.c, spkey.c, spnote.c, spread.c, spview.c
 * Header Files:    spcellop.h, spread.h
 * Resource Files:  spread.vr
 *
 * Managers Illustrated:
 *      Class, Command, Draw, Font, List, Text, Number, and others. 
 *
 * Description Of Sample:
 *      This sample demonstrates a simple spreadsheet build with Galaxy.  
 *      Extensive use of the list manager provides the basis for the
 *      spreadsheet, with other Galaxy managers providing other functions.
 *      The main dialog is accompanied by several smaller dialogs for 
 *      operations on ranges, setting values, etc. 
 *
 *      Some of the features include in-cell editing, dynamic cell sizing,
 *      per-row formats, custom draw methods for listviews, and a variety
 *      of cell and range operations.  
 *
 *      This is not a full-blown spreadsheet and it has no provisions for
 *      reading/writing data, charting, and many other operations commonly
 *      found in a spreadsheet.  It does provide the basics and could be
 *      enhanced to create a fully functional spreadsheet, but that is left
 *      as an exercise for the reader.  
 *
 * Files:
 *      spread.c   -- The main program.
 *      spkey.c    -- Various routines for keyboard/text handling.
 *      spview.c   -- Routines for handling the listviews.
 *      spcom.c    -- Command functions.
 *      spnote.c   -- Notify functions.
 *      spread.h   -- Master header file.
 *      spcellop.h -- Cell operations.
 *
 * History:
 *      Written for 2.0 release July 1994.  
 *      Cleaned up for 2.1 release November 1994.
 */

#include "spread.h"

/* subclasses */
vlistviewClass   *spreadviewClass;
vlistviewClass   *rowviewClass;
vlistviewClass   *columnviewClass;
vtextClass       *editTextClass;
vtextviewClass   *editViewClass;

/* number formats */
vnumFormat              *dollarFormat;
vnumFormat              *commaFormat;
vnumFormat              *commaDollarFormat;

int main(int argc, char **argv)
{
    vresource           rootRes;
    spreadStruct        *spreadSheet;

    /* startup Galaxy */
    vstartup(argc, argv);
    
    /* create the spreadsheet structure */
    spreadSheet = (spreadStruct *) vmemAlloc(sizeof(spreadStruct));

    /* create the various subclasses */
    createSpreadsheetClasses();

    /* get the root resource */
    rootRes   = vapplicationGetResources(vapplicationGetCurrent());

    /* load the spreadsheet dialog */
    loadSpreadsheetDialog(spreadSheet, rootRes);

    /* load the various popup dialogs */
    loadPopupDialogs(spreadSheet, rootRes);

    /* load the cursors */
    loadCursors(spreadSheet, rootRes);

    /* create the custom number formats */
    createNumFormats();

    /* load the spreadsheet data */
    loadSpreadsheetData(spreadSheet);

    /* open the spreadsheet */
    openSpreadsheet(spreadSheet);

    /* setup the visible portions of the spreadsheet */
    setupVisible(spreadSheet, 1);

    /* enter the event loop */
    veventProcess();

    /* free the spreadsheet dialog resources */
    unloadSpreadsheetDialog(spreadSheet);

    /* free the popup dialog resources */
    unloadPopupDialogs(spreadSheet);

    /* free the cursor resources */
    unloadCursors(spreadSheet);

    /* destroy the custom number formats */
    destroyNumFormats();

    /* destroy the various subclasses */
    destroySpreadsheetClasses();

    /* free the memory used by the spreadsheet structure */
    if (spreadSheet != NULL)
	vmemFree(spreadSheet);

    /* exit the program */
    exit(EXIT_SUCCESS);
    return(EXIT_FAILURE);
}

int createSpreadsheetClasses()
{
    spreadviewClass = vclassReproduce(vlistviewGetDefaultClass());
    vclassSetNameScribed(spreadviewClass, 
			 vcharScribeLiteral("spreadview"));
    vclassSet(spreadviewClass, 
	      vlistviewNOTIFY_SCROLL, 
	      spreadviewNotifyScroll);
    vclassSet(spreadviewClass, 
	      vlistviewNOTIFY_SELECT, 
	      spreadviewNotifySelect);
    vclassSet(spreadviewClass, 
	      vlistviewDRAW_CELL_BACKGROUND, 
	      spreadviewDrawCellBackground);
    vclassSet(spreadviewClass, 
	      vlistviewDRAW_CELL_CONTENTS, 
	      spreadviewDrawCellContents);

    rowviewClass = vclassReproduce(vlistviewGetDefaultClass());
    vclassSetNameScribed(rowviewClass, 
			 vcharScribeLiteral("rowview"));
    vclassSet(rowviewClass, 
	      vlistviewDRAW_CELL_BACKGROUND, 
	      rowviewDrawCellBackground);
    vclassSet(rowviewClass, 
	      vlistviewDRAW_CELL_CONTENTS, 
	      rowviewDrawCellContents);

    columnviewClass = vclassReproduce(vlistviewGetDefaultClass());
    vclassSetNameScribed(columnviewClass, 
			 vcharScribeLiteral("columnview"));
    vclassSet(columnviewClass, 
	      vlistviewDRAW_CELL_BACKGROUND, 
	      columnviewDrawCellBackground);
    vclassSet(columnviewClass, 
	      vlistviewDRAW_CELL_CONTENTS, 
	      columnviewDrawCellContents);

    editTextClass = vclassReproduce(vtextGetDefaultClass());
    vclassSetNameScribed(editTextClass, 
			 vcharScribeLiteral("editTextClass"));
    vclassSet(editTextClass,
	      vtextINSERT,
	      editTextInsert);
    vclassSet(editTextClass,
	      vtextDELETE,
	      editTextDelete);

    editViewClass = vclassReproduce(vtextviewGetDefaultClass());
    vclassSetNameScribed(editViewClass, 
			 vcharScribeLiteral("editview"));

    return TRUE;
}

int destroySpreadsheetClasses()
{
    if (spreadviewClass != NULL)
	vclassDestroy(spreadviewClass);

    if (rowviewClass != NULL)
	vclassDestroy(rowviewClass);
    
    if (columnviewClass != NULL)
	vclassDestroy(columnviewClass);
    
    if (editTextClass != NULL)
	vclassDestroy(editTextClass);
    
    if (editViewClass != NULL)
	vclassDestroy(editViewClass);

    return TRUE;
}

int loadSpreadsheetDialog(spreadStruct *spreadSheet, vresource rootRes)
{
    int                 count;
    vresource           dialogRes;
    vcontainer          *container;

    vcommandFunctionTemplate spreadCommands[] = 
    {
	/* file menu */
	{"quitSpreadsheet",         quitSpreadsheet,      NULL},

	/* edit menu */
	{"copyRange",               copyRange,            NULL},
	{"replicateCell",           replicateCell,        NULL},

	/* operations menu */
	{"multiplyRange",           multiplyRange,        NULL},
	{"addRange",                addRange,             NULL},

	/* spreadsheet menu */
	{"transposeSpreadsheet",    transposeSpreadsheet, NULL},
	{"setWidths",               setWidths,            NULL},
	{"setFormat",               setFormat,            NULL},

	/* goto menu */ 
	{"gotoCell",                gotoCell,             NULL},
	{"searchFor",               searchFor,            NULL},
    }; 
    
    count = sizeof(spreadCommands) / sizeof(spreadCommands[0]);

    dialogRes = vresourceGet(rootRes,
			     vnameInternGlobalLiteral("spreadDialog"));
    spreadSheet->spreadDialog = vdialogLoad(dialogRes);                        
    vdialogSetNotify(spreadSheet->spreadDialog, spreadDialogNotify); 
    setFunctionCommands(spreadSheet->spreadDialog, spreadCommands, count);
    vdialogSetData(spreadSheet->spreadDialog, spreadSheet);

    /* add our editable text item */
    spreadSheet->editView = (vtextview *) vdialogFindItem(spreadSheet->spreadDialog,
							  vnameInternGlobalLiteral("editView"));

    vtextviewSetNotify(spreadSheet->editView, (vtextviewNoteProc) editViewNotify);
    vtextviewSetData(spreadSheet->editView, spreadSheet);
    vtextviewSetHiliteStyle(spreadSheet->editView, vtextviewINVERT_HILITE);
    vtextviewSetOffscreenDrawing(spreadSheet->editView, TRUE);
    vdialogSetItemClickFocusable(vtextviewGetItem(spreadSheet->editView), TRUE);
    
    spreadSheet->editData = vtextCreateOfClass(editTextClass);
    vtextSetData(spreadSheet->editData, spreadSheet);
    vtextviewSetTextData(spreadSheet->editView, spreadSheet->editData);
    vtextviewSetAutoInsert(spreadSheet->editView, vTRUE);
    vtextviewSetAutoScroll(spreadSheet->editView, vTRUE);
    
    spreadSheet->editSelection = vtextCreateSelection(spreadSheet->editData);
    vtextviewSetSelection(spreadSheet->editView,
			  spreadSheet->editSelection);

    /* get our spreadsheet listview */
    spreadSheet->spreadView = (vlistview *) vdialogFindItem(spreadSheet->spreadDialog,
							    vnameInternGlobalLiteral("spreadView"));
    vlistviewSetData(spreadSheet->spreadView, spreadSheet);
    vdialogSetItemNotify(vlistviewGetItem(spreadSheet->spreadView),
			 spreadviewItemNotify);


    /* get our row labels listview */
    spreadSheet->rowView = (vlistview *) vdialogFindItem(spreadSheet->spreadDialog,
							 vnameInternGlobalLiteral("rowView"));
    vlistviewSetData(spreadSheet->rowView, spreadSheet);


    /* get our column headings listview */
    spreadSheet->columnView = (vlistview *) vdialogFindItem(spreadSheet->spreadDialog,
							    vnameInternGlobalLiteral("columnView"));
    vlistviewSetData(spreadSheet->columnView, spreadSheet);


    /* get the information containers and set them up */
    container = (vcontainer *) vdialogFindItem(spreadSheet->spreadDialog,      
					       vnameInternGlobalLiteral("message1"));

    spreadSheet->informationDisplay = (vtextitem *) vcontainerFindItem(container,
								       vnameInternGlobalLiteral("informationDisplay"));
    vtextitemSetData(spreadSheet->informationDisplay, spreadSheet);


    container = (vcontainer *) vdialogFindItem(spreadSheet->spreadDialog,      
					       vnameInternGlobalLiteral("message2"));
    
    spreadSheet->unitsDisplay = (vtextitem *) vcontainerFindItem(container,
								 vnameInternGlobalLiteral("unitsDisplay"));
    vtextitemSetData(spreadSheet->unitsDisplay, spreadSheet);

    spreadSheet->messageDisplay = (vtextitem *) vcontainerFindItem(container,
								   vnameInternGlobalLiteral("messageDisplay"));
    vtextitemSetData(spreadSheet->messageDisplay, spreadSheet);

    return TRUE;
}

int unloadSpreadsheetDialog(spreadStruct *spreadSheet)
{
    vdialogDestroy(spreadSheet->spreadDialog);
    
    releaseSpreadsheet(spreadSheet);
    releaseRowLabels(spreadSheet);
    releaseColumnHeadings(spreadSheet);

    if (spreadSheet->spreadList != NULL)
	vlistDestroy(spreadSheet->spreadList);

    if (spreadSheet->rowList != NULL)
	vlistDestroy(spreadSheet->rowList);
    
    if (spreadSheet->columnList != NULL)
	vlistDestroy(spreadSheet->columnList);

    if (spreadSheet->editData != NULL)
	vtextDestroy(spreadSheet->editData);

    return TRUE;
}


int loadPopupDialogs(spreadStruct *spreadSheet, vresource rootRes)
{
    vresource           dialogRes;
    vdialogItem         *dialogItem;
    vcontrol            *control;
    vbutton             *button;
    vcontainer          *container;

    /* get the value dialog and setup its notifies */
    dialogRes = vresourceGet(rootRes,
			     vnameInternGlobalLiteral("valueDialog"));
    spreadSheet->valueDialog = vdialogLoad(dialogRes);                        

    vwindowSetIcon(vdialogGetWindow(spreadSheet->valueDialog),
		   vwindowGetIcon(vdialogGetWindow(spreadSheet->spreadDialog)));

    button = (vbutton *) vdialogFindItem(spreadSheet->valueDialog,
					 vnameInternGlobalLiteral("okButton"));
    vbuttonSetNotify(button, valueOKNotify);
    vbuttonSetData(button, spreadSheet);

    button = (vbutton *) vdialogFindItem(spreadSheet->valueDialog,
					 vnameInternGlobalLiteral("applyButton"));
    vbuttonSetNotify(button, valueApplyNotify);
    vbuttonSetData(button, spreadSheet);

    button = (vbutton *) vdialogFindItem(spreadSheet->valueDialog,
					 vnameInternGlobalLiteral("cancelButton"));
    vbuttonSetNotify(button, valueCancelNotify);
    vbuttonSetData(button, spreadSheet);


    /* get the search dialog and setup its notifies */
    dialogRes = vresourceGet(rootRes,
			     vnameInternGlobalLiteral("searchDialog"));
    spreadSheet->searchDialog = vdialogLoad(dialogRes);                        

    vwindowSetIcon(vdialogGetWindow(spreadSheet->searchDialog),
		   vwindowGetIcon(vdialogGetWindow(spreadSheet->spreadDialog)));

    button = (vbutton *) vdialogFindItem(spreadSheet->searchDialog,
					 vnameInternGlobalLiteral("okButton"));
    vbuttonSetNotify(button, searchOKNotify);
    vbuttonSetData(button, spreadSheet);

    button = (vbutton *) vdialogFindItem(spreadSheet->searchDialog,
					 vnameInternGlobalLiteral("applyButton"));
    vbuttonSetNotify(button, searchApplyNotify);
    vbuttonSetData(button, spreadSheet);

    button = (vbutton *) vdialogFindItem(spreadSheet->searchDialog,
					 vnameInternGlobalLiteral("cancelButton"));
    vbuttonSetNotify(button, searchCancelNotify);
    vbuttonSetData(button, spreadSheet);


    /* get the goto dialog and setup its notifies */
    dialogRes = vresourceGet(rootRes,
			     vnameInternGlobalLiteral("gotoDialog"));
    spreadSheet->gotoDialog = vdialogLoad(dialogRes);                        

    vwindowSetIcon(vdialogGetWindow(spreadSheet->gotoDialog),
		   vwindowGetIcon(vdialogGetWindow(spreadSheet->spreadDialog)));

    button = (vbutton *) vdialogFindItem(spreadSheet->gotoDialog,
					 vnameInternGlobalLiteral("okButton"));
    vbuttonSetNotify(button, gotoOKNotify);
    vbuttonSetData(button, spreadSheet);

    button = (vbutton *) vdialogFindItem(spreadSheet->gotoDialog,
					 vnameInternGlobalLiteral("applyButton"));
    vbuttonSetNotify(button, gotoApplyNotify);
    vbuttonSetData(button, spreadSheet);

    button = (vbutton *) vdialogFindItem(spreadSheet->gotoDialog,
					 vnameInternGlobalLiteral("cancelButton"));
    vbuttonSetNotify(button, gotoCancelNotify);
    vbuttonSetData(button, spreadSheet);


    /* get the width dialog and setup its notifies */
    dialogRes = vresourceGet(rootRes,
			     vnameInternGlobalLiteral("widthDialog"));
    spreadSheet->widthDialog = vdialogLoad(dialogRes);                        

    vwindowSetIcon(vdialogGetWindow(spreadSheet->widthDialog),
		   vwindowGetIcon(vdialogGetWindow(spreadSheet->spreadDialog)));

    button = (vbutton *) vdialogFindItem(spreadSheet->widthDialog,
					 vnameInternGlobalLiteral("okButton"));
    vbuttonSetNotify(button, widthOKNotify);
    vbuttonSetData(button, spreadSheet);

    button = (vbutton *) vdialogFindItem(spreadSheet->widthDialog,
					 vnameInternGlobalLiteral("cancelButton"));
    vbuttonSetNotify(button, widthCancelNotify);
    vbuttonSetData(button, spreadSheet);

    control = (vcontrol *) vdialogFindItem(spreadSheet->widthDialog,
					   vnameInternGlobalLiteral("rowSlider"));
    vcontrolSetNotify(control, rowWidthSliderNotify);
    vcontrolSetData(control, spreadSheet);
    vcontrolSetValue(control, spreadSheet->labelCharWidth);    

    dialogItem = (vdialogItem *) vdialogFindItem(spreadSheet->widthDialog,
						 vnameInternGlobalLiteral("columnWidth"));
    vdialogSetItemTitleScribed(dialogItem,
			       vnumScribeInt(spreadSheet->labelCharWidth));



    control = (vcontrol *) vdialogFindItem(spreadSheet->widthDialog,
					   vnameInternGlobalLiteral("columnSlider"));
    vcontrolSetNotify(control, columnWidthSliderNotify);
    vcontrolSetData(control, spreadSheet);
    vcontrolSetValue(control, spreadSheet->cellCharWidth);
    
    dialogItem = (vdialogItem *) vdialogFindItem(spreadSheet->widthDialog,
						 vnameInternGlobalLiteral("columnWidth"));
    vdialogSetItemTitleScribed(dialogItem,
			       vnumScribeInt(spreadSheet->cellCharWidth));


    /* get the replicate cell dialog and setup its notifies */
    dialogRes = vresourceGet(rootRes,
			     vnameInternGlobalLiteral("repCellDialog"));
    spreadSheet->repCellDialog = vdialogLoad(dialogRes);                        

    vwindowSetIcon(vdialogGetWindow(spreadSheet->repCellDialog),
		   vwindowGetIcon(vdialogGetWindow(spreadSheet->spreadDialog)));

    button = (vbutton *) vdialogFindItem(spreadSheet->repCellDialog,
					 vnameInternGlobalLiteral("okButton"));
    vbuttonSetNotify(button, repCellOKNotify);
    vbuttonSetData(button, spreadSheet);

    button = (vbutton *) vdialogFindItem(spreadSheet->repCellDialog,
					 vnameInternGlobalLiteral("applyButton"));
    vbuttonSetNotify(button, repCellApplyNotify);
    vbuttonSetData(button, spreadSheet);

    button = (vbutton *) vdialogFindItem(spreadSheet->repCellDialog,
					 vnameInternGlobalLiteral("cancelButton"));
    vbuttonSetNotify(button, repCellCancelNotify);
    vbuttonSetData(button, spreadSheet);

    container = (vcontainer *) vdialogFindItem(spreadSheet->repCellDialog,
					       vnameInternGlobalLiteral("repCellExGroup"));
    vcontainerSetNotify(container, repCellExGroupNotify);
    vcontainerSetData(container, spreadSheet);

    
    /* get the format dialog and setup its notifies */
    dialogRes = vresourceGet(rootRes,
			     vnameInternGlobalLiteral("formatDialog"));
    spreadSheet->formatDialog = vdialogLoad(dialogRes);                        

    vwindowSetIcon(vdialogGetWindow(spreadSheet->formatDialog),
		   vwindowGetIcon(vdialogGetWindow(spreadSheet->spreadDialog)));

    button = (vbutton *) vdialogFindItem(spreadSheet->formatDialog,
					 vnameInternGlobalLiteral("okButton"));
    vbuttonSetNotify(button, formatOKNotify);
    vbuttonSetData(button, spreadSheet);

    button = (vbutton *) vdialogFindItem(spreadSheet->formatDialog,
					 vnameInternGlobalLiteral("applyButton"));
    vbuttonSetNotify(button, formatApplyNotify);
    vbuttonSetData(button, spreadSheet);

    button = (vbutton *) vdialogFindItem(spreadSheet->formatDialog,
					 vnameInternGlobalLiteral("cancelButton"));
    vbuttonSetNotify(button, formatCancelNotify);
    vbuttonSetData(button, spreadSheet);

    /* get the ok notice */
    dialogRes = vresourceGet(rootRes,
			     vnameInternGlobalLiteral("okNotice"));
    spreadSheet->okNotice = vnoticeLoad(dialogRes);                        

    return TRUE;
}

int unloadPopupDialogs(spreadStruct *spreadSheet)
{
    if (spreadSheet->searchDialog != NULL)
	vdialogDestroy(spreadSheet->searchDialog);

    if (spreadSheet->gotoDialog != NULL)
	vdialogDestroy(spreadSheet->gotoDialog);      

    if (spreadSheet->valueDialog != NULL)
	vdialogDestroy(spreadSheet->valueDialog);
    
    if (spreadSheet->widthDialog != NULL)
	vdialogDestroy(spreadSheet->widthDialog);
    
    if (spreadSheet->repCellDialog != NULL)
	vdialogDestroy(spreadSheet->repCellDialog);

    if (spreadSheet->formatDialog != NULL)
	vdialogDestroy(spreadSheet->formatDialog);
    
    if (spreadSheet->okNotice != NULL)
	vnoticeDestroy(spreadSheet->okNotice);

    return TRUE;
}

int loadCursors(spreadStruct *spreadSheet, vresource rootRes)
{
    vresource   cursorRes;

    /* get the standard cursor */
    spreadSheet->standardCursor = NULL;     /* default window cursor */

    /* get the copy cursor */
    cursorRes = vresourceGet(rootRes,
			     vnameInternGlobalLiteral("copyCursor"));
    
    spreadSheet->copyCursor = vcursorLoad(cursorRes);

    return TRUE;
}

int unloadCursors(spreadStruct *spreadSheet)
{
    if (spreadSheet->standardCursor != NULL)
	vcursorDestroy(spreadSheet->standardCursor);
    
    if (spreadSheet->copyCursor != NULL)
	vcursorDestroy(spreadSheet->copyCursor);

    return TRUE;
}

/* calls the routines to set up the sizes and load the data */
int loadSpreadsheetData(spreadStruct *spreadSheet)
{
    /* setup the various values that will be read from Fortran */
    spreadSheet->numRows = 100;
    spreadSheet->numColumns = 100;

    spreadSheet->currentRow = 0;
    spreadSheet->currentColumn = 0;

    spreadSheet->lastRow = 0;
    spreadSheet->lastColumn = 0;

    spreadSheet->cellCharWidth = 12;
    spreadSheet->labelCharWidth = 12;

    /* call the setup routines */
    setupSizes(spreadSheet);
    setupSpreadsheet(spreadSheet);
    setupRowLabels(spreadSheet);
    setupColumnHeadings(spreadSheet);

    return TRUE;
}

/* calculate the various sizes used by the spreadsheet */
void setupSizes(spreadStruct *spreadSheet)
{
    const vrect     *editRect;
    vrect           editBounds;
    vrect           fontBounds;
    vtextStyle      *style;

    /* get the spreadsheet's fonts and font bounds */
    spreadSheet->font = vdialogDetermineItemFont(vlistviewGetItem(spreadSheet->spreadView));
    vfontBounds(spreadSheet->font, &fontBounds);

    /* set the default style for the editable text */

    style = vtextCreateStyle();
    vtextInstallStyleOwned(spreadSheet->editData, style);
    vtextSetStyleBold(spreadSheet->editData, style, vtextON);
    vtextSetStyleFont(spreadSheet->editData, style, spreadSheet->font, TRUE);
    vtextSetDefaultStyle(spreadSheet->editData, style);

    /* get the rectangle for the editable text */
    editRect = vdialogGetItemRect(vtextviewGetItem(spreadSheet->editView));

    /* compute and store sizes in the spreadsheet struct */
    spreadSheet->fontWidth = fontBounds.w;
    spreadSheet->fontHeight = (fontBounds.h + 4); /* fudge factor */

    spreadSheet->columnWidth = (spreadSheet->cellCharWidth * spreadSheet->fontWidth);
    spreadSheet->rowHeight = spreadSheet->fontHeight;
    spreadSheet->rowLabelWidth = (spreadSheet->labelCharWidth * spreadSheet->fontWidth); 

    /* set the bounds for the edit view */
    editBounds.x = (editRect->x + 2);
    editBounds.y = (editRect->y + 2);
    editBounds.w = (spreadSheet->columnWidth - 4);
    editBounds.h = (spreadSheet->rowHeight - 4);

    vdialogSetItemRect(vtextviewGetItem(spreadSheet->editView), &editBounds);
}

/* used to change sizes after spreadsheet is open */
void changeSizes(spreadStruct *spreadSheet, int refresh)
{
    const vrect     *editRect;
    vrect           editBounds;
    const vrect     *winRect;
    vrect           dialogRect;

    unsetEditCell(spreadSheet);

    editRect = vdialogGetItemRect(vtextviewGetItem(spreadSheet->editView));

    spreadSheet->columnWidth = (spreadSheet->cellCharWidth * spreadSheet->fontWidth);
    spreadSheet->rowLabelWidth = (spreadSheet->labelCharWidth * spreadSheet->fontWidth); 


    vlistviewSetColumnWidth(spreadSheet->rowView, 
			    vlistviewALL_COLUMNS, 
			    spreadSheet->rowLabelWidth);

    vlistviewSetColumnWidth(spreadSheet->spreadView, 
			    vlistviewALL_COLUMNS, 
			    spreadSheet->columnWidth);

    vlistviewSetColumnWidth(spreadSheet->columnView, 
			    vlistviewALL_COLUMNS, 
			    spreadSheet->columnWidth);
    
    /* set the bounds for the edit view */
    editBounds.x = (editRect->x + 2);
    editBounds.y = (editRect->y + 2);
    editBounds.w = (spreadSheet->columnWidth - 4);
    editBounds.h = (spreadSheet->rowHeight - 4);

    vdialogSetItemRect(vtextviewGetItem(spreadSheet->editView), &editBounds);

    winRect = vwindowGetRect(vdialogGetWindow(spreadSheet->spreadDialog));

    dialogRect.x = 0;
    dialogRect.y = 0;
    dialogRect.w = winRect->w;
    dialogRect.h = winRect->h;

    vdialogArrange(spreadSheet->spreadDialog, &dialogRect);
}

/* sets up the visible portions after dialog is open */
void setupVisible(spreadStruct *spreadSheet, int initial)
{
    int             row, column;
    int             x, y;

    column = vlistviewGetLeftColumn(spreadSheet->spreadView);

    row = vlistviewGetTopRow(spreadSheet->spreadView);

    vlistviewGetDrawingOffsets(spreadSheet->spreadView, &x, &y);

    if (y >= 0)
	vlistviewScrollToCellWithOffset(spreadSheet->rowView, row, 0, 0, y);

    if (x <= 0)
	vlistviewScrollToCellWithOffset(spreadSheet->columnView, 0, column, x, 0);

    if (initial)
    {
	setEditCell(spreadSheet);
    }
    else
    {
	unsetEditCell(spreadSheet);
    }

}

/* setup the spreadsheet and fill it with data */
void setupSpreadsheet(spreadStruct *spreadSheet)
{
    register int    r, c;
    int             i;
    double          doubleValue;
    double          rd, cd;
    vstr            *string;
    spreadData      *cellData;
    char            format;

    /* create the list to be used for the spreadsheet */
    spreadSheet->spreadList = vlistCreate();

    /* associate the list with the listview */
    vlistviewSetList(spreadSheet->spreadView, spreadSheet->spreadList);
    
    /* set the heights and widths for the cells */
    vlistviewSetRowHeight(spreadSheet->spreadView, 
			  vlistviewALL_ROWS, 
			  spreadSheet->rowHeight);
    vlistviewSetColumnWidth(spreadSheet->spreadView, 
			    vlistviewALL_COLUMNS, 
			    spreadSheet->columnWidth);

    /* allocate memory for the row format */
    spreadSheet->rowFormat = (char *) vmemAlloc(sizeof(char) * spreadSheet->numRows);


    /* fill in values, currently faked */

    i = 0;

    for (r = 0; r < spreadSheet->numRows; r++)
    {
	/* faked formats for testing */

	if (r % 4)
	    format  = (SPREAD_RIGHT_JUSTIFY | SPREAD_COMMAS | SPREAD_DOLLARS | 0x02);
	else
	    format = (SPREAD_RIGHT_JUSTIFY | SPREAD_COMMAS | 0x03);

	spreadSheet->rowFormat[r] = format;

	for (c = 0; c < spreadSheet->numColumns; c++)
	{
	    /* fake some strings and floats */
	    if (c % 3)
	    {
		rd = (double) r;
		cd = (double) c;

		doubleValue = (double) (rd * cd) + ((rd + 1.0) / (cd + 1.0));
	    
		cellData = (spreadData *) vmemAlloc(sizeof(spreadData));
		
		cellData->type = (SPREAD_DOUBLE | SPREAD_CLEAN);
		cellData->data.value = doubleValue;
	    }
	    else
	    {
                /* faked text strings */
 
                switch (i)
                {
                    case 0 :
                    string = vstrCloneScribed(vcharScribeLiteral("Visix"));
                    break;
 
                    case 1 :
                    string = vstrCloneScribed(vcharScribeLiteral("Spam"));
                    break;
 
                    case 2 :
                    string = vstrCloneScribed(vcharScribeLiteral("Galaxy"));
                    break;
 
                    case 3 :
                    string = vstrCloneScribed(vcharScribeLiteral("Bork"));
                    break;
 
                    default :
                    string = vstrCloneScribed(vcharScribeLiteral("Fnord"));
                    break;                      
 
                }

		cellData = (spreadData *) vmemAlloc(sizeof(spreadData));
	
		cellData->type = (SPREAD_STRING | SPREAD_CLEAN);
		cellData->data.string = string;

		if (++i > 4)
		    i = 0;
	    }
		
	    vlistSetCellValue(spreadSheet->spreadList, r, c, cellData);
	}
    }
}

/* set up the row labels and fill them with text */
void setupRowLabels(spreadStruct *spreadSheet)
{
    vstr            *string;
    int             r;
    spreadData      *cellData;    
    
    /* create the list for the row labels */
    spreadSheet->rowList = vlistCreate();

    /* associate the list with the listview */
    vlistviewSetList(spreadSheet->rowView, spreadSheet->rowList);

    /* set the heights and widths for the cells */
    vlistviewSetRowHeight(spreadSheet->rowView, 
			  vlistviewALL_ROWS, 
			  spreadSheet->rowHeight);
    vlistviewSetColumnWidth(spreadSheet->rowView, 
			    vlistviewALL_COLUMNS, 
			    spreadSheet->rowLabelWidth);

    /* set row labels, currently faked */
    for (r = 0; r < spreadSheet->numRows; r++)
    {
	string = vstrCloneScribed(vnumScribeInt(r));
	    
	cellData = (spreadData *) vmemAlloc(sizeof(spreadData));
	
	cellData->type = SPREAD_STRING;
	cellData->data.string = string;
	
	vlistSetCellValue(spreadSheet->rowList, r, 0, cellData);
    }
}

/* setup the column headings and fill them with text */
void setupColumnHeadings(spreadStruct *spreadSheet)
{
    vstr            *string;
    int             c;
    spreadData      *cellData;

    /* create the list for the column headings */
    spreadSheet->columnList = vlistCreate();

    /* assoicate the list with the listview */
    vlistviewSetList(spreadSheet->columnView, spreadSheet->columnList);

    /* set the heights and widths for the cells */
    vlistviewSetRowHeight(spreadSheet->columnView, 
			  vlistviewALL_ROWS, 
			  spreadSheet->rowHeight);
    vlistviewSetColumnWidth(spreadSheet->columnView, 
			    vlistviewALL_COLUMNS, 
			    spreadSheet->columnWidth);

    /* set the column headings */
    for (c = 0; c < spreadSheet->numColumns; c++)
    {
	string = vstrCloneScribed(vnumScribeInt((1990 + c)));
	    
	cellData = (spreadData *) vmemAlloc(sizeof(spreadData));

	cellData->type = SPREAD_STRING;
	cellData->data.string = string;

	vlistSetCellValue(spreadSheet->columnList, 0, c, cellData);
    }
}

/* free the memory allocated for the spreadsheet */
void releaseSpreadsheet(spreadStruct *spreadSheet)
{
    int             r, c;
    spreadData      *cellData;
    char            type, dirty;

    /* free the memory for the row format */
    if (spreadSheet->rowFormat != NULL)
	vmemFree(spreadSheet->rowFormat);

    for (r = 0; r < spreadSheet->numRows; r++)
    {
	for (c = 0; c < spreadSheet->numColumns; c++)
	{
	    cellData = (spreadData *) vlistGetCellValue(spreadSheet->spreadList, r, c);      
    
	    type = (cellData->type & 0xF0);
	    dirty = (cellData->type & 0x0F);

	    switch (type)
	    {
		case SPREAD_DOUBLE :
		    if (dirty)
		    {
			/* write floating point data here */
		    }
		    if (cellData != NULL)
			vmemFree(cellData);
		    break;
	    
		case SPREAD_STRING :
		    if (dirty)
		    {
			/* write text data here */
		    }
		    if (cellData->data.string != NULL)
			vstrDestroy(cellData->data.string);
		    if (cellData != NULL)
			vmemFree(cellData);
		    break;

		default :
		    /* should never get here, but check anyway */
		    if (cellData != NULL)
			vmemFree(cellData);
		    break;
	    }
	}
    }
}

/* free up the memory allocated for the row labels */
void releaseRowLabels(spreadStruct *spreadSheet)
{
    int             r;
    spreadData      *cellData;
    char            type;

    for (r = 0; r < spreadSheet->numRows; r++)
    {
	cellData = (spreadData *) vlistGetCellValue(spreadSheet->rowList, r, 0);      
	
	type = (cellData->type & 0xF0);

	switch (type)
	{
	    case SPREAD_DOUBLE :
		if (cellData != NULL)
		    vmemFree(cellData);
		break;
	    
	    case SPREAD_STRING :
		if (cellData->data.string != NULL)
		    vstrDestroy(cellData->data.string);
		if (cellData != NULL)
		    vmemFree(cellData);
		break;

	    default :
		if (cellData != NULL)
		    vmemFree(cellData);
		break;
	}
    }
}

/* free up the memory allocated for the column headings */
void releaseColumnHeadings(spreadStruct *spreadSheet)
{
    int             c;
    spreadData      *cellData;
    char            type;

    for (c = 0; c < spreadSheet->numColumns; c++)
    {
	cellData = (spreadData *) vlistGetCellValue(spreadSheet->columnList, 0, c);      
	
	type = (cellData->type & 0xF0);
	    
	switch (type)
	{
	    case SPREAD_DOUBLE :
		if (cellData != NULL)
		    vmemFree(cellData);
		break;
	    
	    case SPREAD_STRING :
		if (cellData->data.string != NULL)
		    vstrDestroy(cellData->data.string);
		if (cellData != NULL)
		    vmemFree(cellData);
		break;

	    default :
		if (cellData != NULL)
		    vmemFree(cellData);
		break;
	}
    }
}

/* called to resize a dialog to full size of screen */
void setDialogFullScreen(vdialog *dialog)
{
    vwindow         *rootWindow;
    const vrect     *rootRect;
    vrect           dialogRect;

    /* get the root window */
    rootWindow = vwindowGetRoot();

    /* get it's rectangle */
    rootRect = vwindowGetRect(rootWindow);
    
    /* set the dialog rectangle to be 9/10 sreen size */
    dialogRect.x = rootRect->x;
    dialogRect.y = rootRect->y;
    dialogRect.h = ((rootRect->h * 9) / 10);
    dialogRect.w = ((rootRect->w * 9) / 10);

    /* set the dialog window rect */
    vwindowSetRect(vdialogGetWindow(dialog), &dialogRect);

    vwindowPlace(vdialogGetWindow(dialog), rootWindow, 
		 vrectPLACE_CENTER, vrectPLACE_CENTER);

    /* rearrange the dialog items according to new size */
    vdialogArrange(dialog, &dialogRect);
}
    
/* called to open the spreadsheet dialog */
int openSpreadsheet(spreadStruct *spreadSheet)
{
    if (spreadSheet->spreadDialog)
    {
	setDialogFullScreen(spreadSheet->spreadDialog);

	vdialogOpen(spreadSheet->spreadDialog);
    }
    else
	return FALSE;

    return TRUE;
} 

/* called whenever the popups need to be raised */
void raisePopups(spreadStruct *spreadSheet)
{
    if (vdialogIsOpen(spreadSheet->valueDialog))
	vwindowRaise(vdialogGetWindow(spreadSheet->valueDialog));

    if (vdialogIsOpen(spreadSheet->gotoDialog))
	vwindowRaise(vdialogGetWindow(spreadSheet->gotoDialog));

    if (vdialogIsOpen(spreadSheet->widthDialog))
	vwindowRaise(vdialogGetWindow(spreadSheet->widthDialog));
	    
    if (vdialogIsOpen(spreadSheet->repCellDialog))
	vwindowRaise(vdialogGetWindow(spreadSheet->repCellDialog));
	    
    if (vdialogIsOpen(spreadSheet->formatDialog))
	vwindowRaise(vdialogGetWindow(spreadSheet->formatDialog));

    /* add other popup dialogs to be raised here */

}

/* called when the dialog is notified */
void spreadDialogNotify(vdialog *dialog, vevent *event)
{
    veventType      eventType;
    spreadStruct    *spreadSheet;

    eventType = veventGetType(event);

    spreadSheet = (spreadStruct *) vdialogGetData(dialog);

    if (eventType == veventWINDOW_STATE && veventIsClose(event))
	veventStopProcessing();

    if (eventType == veventWINDOW_CONFIGURE)
    {
	setupVisible(spreadSheet, 0);
	unsetEditCell(spreadSheet);

	if (veventIsStack(event))
	{
	    /* window has been brought to front, raise popups */
	    raisePopups(spreadSheet);
	}
    }
}

/* convenience function for changing a text item's message */
void changeMessage(vtextitem *textItem, vscribe *message)
{
    if (textItem != NULL)
	vtextitemSetTextScribed(textItem, message);
}

/* create the number formats */
void createNumFormats()
{
    /* create the dollar format : $NNNN.NNN */
    dollarFormat = vnumCreateFormat();
    vnumAddFormatTextScribed(dollarFormat, NULL, vcharScribeLiteral("$"), NULL);
    vnumAddFormatDigits(dollarFormat, NULL, 0, 0, -1);
    vnumAddFormatDecimal(dollarFormat, NULL, vcharFromLiteral('.'));
    vnumAddFormatDigits(dollarFormat, NULL, 0, 0, (MAX_PRECISION + 1));

    /* create the comma format : NN,NNN,NNN.NN */
    commaFormat = vnumCreateFormat();
    vnumAddFormatDigits(commaFormat, NULL, 3, vcharFromLiteral(','), -1);
    vnumAddFormatDecimal(commaFormat, NULL, vcharFromLiteral('.'));
    vnumAddFormatDigits(commaFormat, NULL, 0, 0, (MAX_PRECISION + 1));

    /* create the comma/dollar format : $NN,NNN.NN */
    commaDollarFormat = vnumCreateFormat();
    vnumAddFormatTextScribed(commaDollarFormat, NULL, vcharScribeLiteral("$"), NULL);
    vnumAddFormatDigits(commaDollarFormat, NULL, 3, vcharFromLiteral(','), -1);
    vnumAddFormatDecimal(commaDollarFormat, NULL, vcharFromLiteral('.'));
    vnumAddFormatDigits(commaDollarFormat, NULL, 0, 0, (MAX_PRECISION + 1));
}

/* destroy the number formats */
void destroyNumFormats()
{
    if (dollarFormat != NULL)
	vnumDestroyFormat(dollarFormat);

    if (commaFormat != NULL)
	vnumDestroyFormat(commaFormat);

    if (commaDollarFormat != NULL)
	vnumDestroyFormat(commaDollarFormat);
}

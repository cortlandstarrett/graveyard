/* $Id: spcom.c,v 1.2 1994/12/29 04:12:28 skip Exp $ */
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
 * spcom.c -- Source file for commands used in spreadsheet sample.
 *
 * See the file spread.c for more information.
 */

#include "spread.h"
#include "spcellop.h"

/* command setup routines */
void setFunctionCommands(vdialog *dialog, vcommandFunctionTemplate commandBindings[],
			 int commandCount)
{
    vcommandSpace     *commandSpace;
    vdict             *commandDictionary;

    if ((commandSpace = vapplicationGetSpace(vapplicationGetCurrent())) == NULL)
    {
        commandSpace = vcommandCreateSpace();
	vapplicationSetSpaceOwned(vapplicationGetCurrent(), commandSpace);
    }

    commandDictionary = vcommandCreateDictFunctionTemplates(commandBindings, commandCount);

    vcommandAddSpaceDictOwned(commandSpace, vname_Command, commandDictionary);
}

/* file menu command functions */
int quitSpreadsheet(vcommandFunction *command, vdict *context)
{
    veventStopProcessing();
 
    return TRUE;
}

/* edit menu command functions */
int replicateCell(vcommandFunction *command, vdict *context)
{
    vdialog         *spreadDialog;
    spreadStruct    *spreadSheet;
    vspinner        *repCellSpinner;
    vcontainer      *container;
    vdialogItem     *which;

    spreadDialog = (vdialog *) vdictLoad(context, vname_Dialog);

    spreadSheet = (spreadStruct *) vdialogGetData(spreadDialog);

    if (!vdialogIsOpen(spreadSheet->repCellDialog))
    {

        container = (vcontainer *) vdialogFindItem(spreadSheet->repCellDialog,
                                                   vnameInternGlobalLiteral("repCellExGroup"));

        which = vcontainerGetSelection(container);
    
        repCellSpinner = (vspinner *) vdialogFindItem(spreadSheet->repCellDialog, 
                                                      vnameInternGlobalLiteral("repCellSpinner"));

        if (vdialogGetItemTag(which) == vnameInternGlobalLiteral("repRow"))
            vspinnerSetMax(repCellSpinner, (spreadSheet->numRows - 1));
        else
            vspinnerSetMax(repCellSpinner, (spreadSheet->numColumns - 1));

        vdialogOpen(spreadSheet->repCellDialog);

        vwindowSetPopup(vdialogGetWindow(spreadSheet->repCellDialog), TRUE);

        vwindowSetLeader(vdialogGetWindow(spreadSheet->repCellDialog), 
                         vdialogGetWindow(spreadSheet->spreadDialog));

        changeMessage(spreadSheet->messageDisplay, 
                      vcharScribeLiteral("Select row or column and number of cells to replicate"));
    }
    
    return TRUE;
}

int copyRange(vcommandFunction *command, vdict *context)
{
    vlistSelection  *selection;
    vdialog         *spreadDialog;
    spreadStruct    *spreadSheet;

    spreadDialog = (vdialog *) vdictLoad(context, vname_Dialog);

    spreadSheet = (spreadStruct *) vdialogGetData(spreadDialog);

    selection = vlistviewGetSelection(spreadSheet->spreadView);
    
    if (selection == NULL)
    {
        raiseOKNotice(spreadSheet, spreadSheet->spreadDialog,
                      vcharScribeLiteral("Copy Notice"), 
                      vcharScribeLiteral("No range selected."));

        copyingOn = COPY_OFF;
        
        vdialogSetItemCursor(vlistviewGetItem(spreadSheet->spreadView), spreadSheet->standardCursor);
    }
    else
    {
        vlistDetermineSelectionBounds(spreadSheet->spreadList, selection,
                                      &copyRow, &copyColumn,
                                      &copyDown, &copyAcross);

        vdialogSetItemCursor(vlistviewGetItem(spreadSheet->spreadView), spreadSheet->copyCursor);

        copyingOn = COPY_RANGE;
                
        changeMessage(spreadSheet->messageDisplay, 
                      vcharScribeLiteral("Click in upper left cell to copy range."));
    }

    return TRUE;
}

/* convenience function for value dialog */
void setupValueDialog(spreadStruct *spreadSheet, int operation)
{
    vdialogItem     *valueLabel;
    vtextitem       *valueText;

    spreadSheet->currentOperation = operation;
                
    valueLabel = (vdialogItem *) vdialogFindItem(spreadSheet->valueDialog,
                                                 vnameInternGlobalLiteral("valueLabel"));
        
    valueText = (vtextitem *) vdialogFindItem(spreadSheet->valueDialog,
                                              vnameInternGlobalLiteral("valueText"));

    switch (operation)
    {
        case ESCALATE_SELECTION :
            vdialogSetTitleScribed(spreadSheet->valueDialog, 
                                   vcharScribeLiteral("Escalate Range"));
            vdialogSetItemTitleScribed(valueLabel,
                                       vcharScribeLiteral("Escalation Rate"));
            vtextitemSetTextScribed(valueText,
                                    vnumScribeInt(lastEscalationRate));
            break;
        
        case ADD_SELECTION :
            vdialogSetTitleScribed(spreadSheet->valueDialog, 
                                   vcharScribeLiteral("Add To Range"));
            vdialogSetItemTitleScribed(valueLabel,
                                       vcharScribeLiteral("Adder"));
            vtextitemSetTextScribed(valueText,
                                    vnumScribeInt(lastAddValue));
            break;

        case MULTIPLY_SELECTION :
            vdialogSetTitleScribed(spreadSheet->valueDialog, 
                                   vcharScribeLiteral("Multiply Range"));
            vdialogSetItemTitleScribed(valueLabel,
                                       vcharScribeLiteral("Multiplier"));
            vtextitemSetTextScribed(valueText,
                                    vnumScribeInt(lastMultiplyValue));
            break;


        default :
            break;

    }
}

/* operations menu command functions */
int escalateRange(vcommandFunction *command, vdict *context)
{
    vdialog         *spreadDialog;
    spreadStruct    *spreadSheet;

    spreadDialog = (vdialog *) vdictLoad(context, vname_Dialog);

    spreadSheet = (spreadStruct *) vdialogGetData(spreadDialog);

    if (!vdialogIsOpen(spreadSheet->valueDialog))
    {
        setupValueDialog(spreadSheet, ESCALATE_SELECTION);
        
        vdialogOpen(spreadSheet->valueDialog);
        
        vwindowSetPopup(vdialogGetWindow(spreadSheet->valueDialog), TRUE);

        vwindowSetLeader(vdialogGetWindow(spreadSheet->valueDialog), 
                         vdialogGetWindow(spreadSheet->spreadDialog));

        changeMessage(spreadSheet->messageDisplay, 
                      vcharScribeLiteral("Enter the escalation rate for the range"));
    }

    return TRUE;
}

int multiplyRange(vcommandFunction *command, vdict *context)
{
    vdialog         *spreadDialog;
    spreadStruct    *spreadSheet;

    spreadDialog = (vdialog *) vdictLoad(context, vname_Dialog);

    spreadSheet = (spreadStruct *) vdialogGetData(spreadDialog);

    if (!vdialogIsOpen(spreadSheet->valueDialog))
    {
        setupValueDialog(spreadSheet, MULTIPLY_SELECTION);
        
        vdialogOpen(spreadSheet->valueDialog);
        
        vwindowSetPopup(vdialogGetWindow(spreadSheet->valueDialog), TRUE);

        vwindowSetLeader(vdialogGetWindow(spreadSheet->valueDialog), 
                         vdialogGetWindow(spreadSheet->spreadDialog));

        changeMessage(spreadSheet->messageDisplay, 
                      vcharScribeLiteral("Enter the number to multiply the range by"));
    }

    return TRUE;
}

int addRange(vcommandFunction *command, vdict *context)
{
    vdialog         *spreadDialog;
    spreadStruct    *spreadSheet;

    spreadDialog = (vdialog *) vdictLoad(context, vname_Dialog);
    
    spreadSheet = (spreadStruct *) vdialogGetData(spreadDialog);

    if (!vdialogIsOpen(spreadSheet->valueDialog))
    {
        setupValueDialog(spreadSheet, ADD_SELECTION);

        vdialogOpen(spreadSheet->valueDialog);
        
        vwindowSetPopup(vdialogGetWindow(spreadSheet->valueDialog), TRUE);

        vwindowSetLeader(vdialogGetWindow(spreadSheet->valueDialog), 
                         vdialogGetWindow(spreadSheet->spreadDialog));

        changeMessage(spreadSheet->messageDisplay, 
                      vcharScribeLiteral("Enter the number to add to the range"));
    }

    return TRUE;
}

/* goto menu command functions */
int gotoCell(vcommandFunction *command, vdict *context)
{
    vdialog         *spreadDialog;
    spreadStruct    *spreadSheet;
    vspinner        *rowSpinner, *columnSpinner;

    spreadDialog = (vdialog *) vdictLoad(context, vname_Dialog);

    spreadSheet = (spreadStruct *) vdialogGetData(spreadDialog);
    
    if (!vdialogIsOpen(spreadSheet->gotoDialog))
    {
        rowSpinner = (vspinner *) vdialogFindItem(spreadSheet->gotoDialog, 
                                                  vnameInternGlobalLiteral("rowSpinner"));
    
        columnSpinner = (vspinner *) vdialogFindItem(spreadSheet->gotoDialog, 
                                                     vnameInternGlobalLiteral("columnSpinner"));
    
        vspinnerSetMax(rowSpinner, (spreadSheet->numRows - 1));
        
        vspinnerSetValue(rowSpinner, spreadSheet->currentRow);

        vspinnerSetMax(columnSpinner, (spreadSheet->numColumns - 1));

        vspinnerSetValue(columnSpinner, spreadSheet->currentColumn);

        vdialogOpen(spreadSheet->gotoDialog);
        
        vwindowSetPopup(vdialogGetWindow(spreadSheet->gotoDialog), TRUE);

        vwindowSetLeader(vdialogGetWindow(spreadSheet->gotoDialog), 
                         vdialogGetWindow(spreadSheet->spreadDialog));
    }

    return TRUE;
}

int searchFor(vcommandFunction *command, vdict *context)
{
    vdialog         *spreadDialog;
    spreadStruct    *spreadSheet;
    spreadData      *cellData;
    vspinner        *rowSpinner, *columnSpinner;
    long            index, count;
    vstr            *cellString;
    char            type;

    spreadDialog = (vdialog *) vdictLoad(context, vname_Dialog);

    spreadSheet = (spreadStruct *) vdialogGetData(spreadDialog);
    
    if (!vdialogIsOpen(spreadSheet->searchDialog))
    {
        rowSpinner = (vspinner *) vdialogFindItem(spreadSheet->searchDialog, 
                                                  vnameInternGlobalLiteral("rowSpinner"));
    
        columnSpinner = (vspinner *) vdialogFindItem(spreadSheet->searchDialog, 
                                                     vnameInternGlobalLiteral("columnSpinner"));
    
        count = vspinnerGetTextCount(rowSpinner);

        for (index = (count - 1); index >= 0; index--)
        {
            vspinnerDeleteTextAt(rowSpinner, index);
        }
    
        for (index = 0; index < spreadSheet->numRows; index++)
        {
            cellData = (spreadData *) vlistGetCellValue(spreadSheet->rowList, index, 0);
  
            type = (cellData->type & 0xF0);

            if (type & SPREAD_DOUBLE)
                vspinnerAppendTextScribed(rowSpinner, 
                                          vnumScribeFloat(cellData->data.value));

            if (type & SPREAD_STRING)
            {
                cellString = vstrClone(cellData->data.string);

                vspinnerAppendTextScribed(rowSpinner, 
                                          vstrScribe(cellString));
            }
        }


        count = vspinnerGetTextCount(columnSpinner);

        for (index = (count - 1); index >= 0; index--)
        {
            vspinnerDeleteTextAt(columnSpinner, index);
        }

        for (index = 0; index < spreadSheet->numColumns; index++)
        {
            cellData = (spreadData *) vlistGetCellValue(spreadSheet->columnList, 0, index);
            
            type = (cellData->type & 0xF0);
            
            if (type & SPREAD_DOUBLE)
                vspinnerAppendTextScribed(columnSpinner, 
                                          vnumScribeFloat(cellData->data.value));

            if (type & SPREAD_STRING)
            {
                cellString = vstrClone(cellData->data.string);

                vspinnerAppendTextScribed(columnSpinner, 
                                          vstrScribe(cellString));
            }
        }

        vspinnerSetValue(rowSpinner, spreadSheet->currentRow);
        vspinnerSetValue(columnSpinner, spreadSheet->currentColumn);

        vdialogOpen(spreadSheet->searchDialog);
        
        vwindowSetPopup(vdialogGetWindow(spreadSheet->searchDialog), TRUE);

        vwindowSetLeader(vdialogGetWindow(spreadSheet->searchDialog), 
                         vdialogGetWindow(spreadSheet->spreadDialog));
    
    }

    return TRUE;
}

/* convenience function for format dialog */
void setupFormatDialog(spreadStruct *spreadSheet)
{
    vcontrol        *control;
    vspinner        *spinner;
    char            format, places;
        
    /* get the format for the current row */
    format = (spreadSheet->rowFormat[spreadSheet->currentRow] & 0xF0);
    places = (spreadSheet->rowFormat[spreadSheet->currentRow] & 0x0F);

    control = (vcontrol *) vdialogFindItem(spreadSheet->formatDialog,
                                           vnameInternGlobalLiteral("commasCheck"));
    if (format & SPREAD_COMMAS)
        vcontrolSetValue(control, TRUE);        
    else
        vcontrolSetValue(control, FALSE);
    

    control = (vcontrol *) vdialogFindItem(spreadSheet->formatDialog,
                                           vnameInternGlobalLiteral("dollarsCheck"));
    if (format & SPREAD_DOLLARS)
        vcontrolSetValue(control, TRUE);        
    else
        vcontrolSetValue(control, FALSE);


    control = (vcontrol *) vdialogFindItem(spreadSheet->formatDialog,
                                           vnameInternGlobalLiteral("rightJustifyCheck"));
    if (format & SPREAD_DOLLARS)
        vcontrolSetValue(control, TRUE);        
    else
        vcontrolSetValue(control, FALSE);
    

    spinner = (vspinner *) vdialogFindItem(spreadSheet->formatDialog,
                                           vnameInternGlobalLiteral("decimalSpinner"));
    vspinnerSetValue(spinner, places);
}

/* spreadsheet menu command functions */
int setWidths(vcommandFunction *command, vdict *context)
{
    vdialog         *spreadDialog;
    spreadStruct    *spreadSheet;
    vdialogItem     *rowWidth;
    vdialogItem     *columnWidth;
    vcontrol        *control;
                         
    spreadDialog = (vdialog *) vdictLoad(context, vname_Dialog);
    
    spreadSheet = (spreadStruct *) vdialogGetData(spreadDialog);

    if (!vdialogIsOpen(spreadSheet->widthDialog))
    {
        /* store widths for cancel */

        lastCellWidth = spreadSheet->cellCharWidth;

        lastLabelWidth = spreadSheet->labelCharWidth;

        /* get the text items and change the text */
        columnWidth = (vdialogItem *) vdialogFindItem(spreadSheet->widthDialog,
                                                      vnameInternGlobalLiteral("columnWidth"));
        
        rowWidth = (vdialogItem *) vdialogFindItem(spreadSheet->widthDialog,
                                                   vnameInternGlobalLiteral("rowWidth"));
        
        vdialogSetItemTitleScribed(columnWidth,
                                   vnumScribeInt(spreadSheet->cellCharWidth));

        vdialogSetItemTitleScribed(rowWidth,
                                   vnumScribeInt(spreadSheet->labelCharWidth));


        /* get the sliders and change their values */
        control = (vcontrol *) vdialogFindItem(spreadSheet->widthDialog,
                                               vnameInternGlobalLiteral("rowSlider"));

        vcontrolSetValue(control, spreadSheet->labelCharWidth);

        control = (vcontrol *) vdialogFindItem(spreadSheet->widthDialog,
                                               vnameInternGlobalLiteral("columnSlider"));

        vcontrolSetValue(control, spreadSheet->cellCharWidth);


        vdialogOpen(spreadSheet->widthDialog);
        
        vwindowSetPopup(vdialogGetWindow(spreadSheet->widthDialog), TRUE);

        vwindowSetLeader(vdialogGetWindow(spreadSheet->widthDialog), 
                         vdialogGetWindow(spreadSheet->spreadDialog));

        changeMessage(spreadSheet->messageDisplay, 
                      vcharScribeLiteral("Change the column and row widths with the sliders"));
    }

    return TRUE;
}

int setFormat(vcommandFunction *command, vdict *context)
{
    vdialog         *spreadDialog;
    spreadStruct    *spreadSheet;

    spreadDialog = (vdialog *) vdictLoad(context, vname_Dialog);

    spreadSheet = (spreadStruct *) vdialogGetData(spreadDialog);

    if (!vdialogIsOpen(spreadSheet->formatDialog))
    {
        setupFormatDialog(spreadSheet);

        vdialogOpen(spreadSheet->formatDialog);
        
        vwindowSetPopup(vdialogGetWindow(spreadSheet->formatDialog), TRUE);

        vwindowSetLeader(vdialogGetWindow(spreadSheet->formatDialog), 
                         vdialogGetWindow(spreadSheet->spreadDialog));
    }

    return TRUE;
}

int transposeSpreadsheet(vcommandFunction *command, vdict *context)
{
    vdialog         *spreadDialog;
    spreadStruct    *spreadSheet;
    vlist           *origList, *origList2;
    int             r, c, temp;
    vlistSelection  *selection;
    int             selRow, selColumn, selDown, selAcross;
    int             topRow, leftColumn;
    
    spreadDialog = (vdialog *) vdictLoad(context, vname_Dialog);

    spreadSheet = (spreadStruct *) vdialogGetData(spreadDialog);

    /* check here to see if legal to transpose, warn if not */



    /* set blocking cursor to indicate action */
    vwindowBlock(vdialogGetWindow(spreadSheet->spreadDialog));

    /* get the current selection */
    selection = vlistviewGetSelection(spreadSheet->spreadView);

    if (selection != NULL)
        vlistDetermineSelectionBounds(spreadSheet->spreadList, selection,
                                      &selRow, &selColumn, 
                                      &selDown, &selAcross);

    topRow = vlistviewGetTopRow(spreadSheet->spreadView);
    leftColumn = vlistviewGetLeftColumn(spreadSheet->spreadView);

    unsetEditCell(spreadSheet);

    /* invalidate the listviews to reduce flicker */
    vlistviewInval(spreadSheet->spreadView);
    vlistviewInval(spreadSheet->rowView);
    vlistviewInval(spreadSheet->columnView);

    /* transpose main spreadsheet */

    vlistviewSetList(spreadSheet->spreadView, NULL);

    origList = vlistClone(spreadSheet->spreadList);

    vlistDestroy(spreadSheet->spreadList);

    spreadSheet->spreadList = vlistCreate();

    for (r = 0; r < spreadSheet->numRows; r++)
        for (c = 0; c < spreadSheet->numColumns; c++)
            vlistSetCellValue(spreadSheet->spreadList, c, r, 
                              vlistGetCellValue(origList, r, c));

    vlistDestroy(origList);


    /* transpose row labels and column headings */

    vlistviewSetList(spreadSheet->rowView, NULL);
    vlistviewSetList(spreadSheet->columnView, NULL);


    origList = vlistClone(spreadSheet->rowList);
    
    vlistDestroy(spreadSheet->rowList);
    

    origList2 = vlistClone(spreadSheet->columnList);

    vlistDestroy(spreadSheet->columnList);


    spreadSheet->rowList = vlistCreate();

    for (r = 0; r < spreadSheet->numColumns; r++)
        vlistSetCellValue(spreadSheet->rowList, r, 0, 
                          vlistGetCellValue(origList2, 0, r));
    
    vlistDestroy(origList2);


    spreadSheet->columnList = vlistCreate();

    for (c = 0; c < spreadSheet->numRows; c++)
        vlistSetCellValue(spreadSheet->columnList, 0, c, 
                          vlistGetCellValue(origList, c, 0));

    vlistDestroy(origList);


    /* swap various values */

    temp = spreadSheet->numRows;
    spreadSheet->numRows = spreadSheet->numColumns;
    spreadSheet->numColumns = temp;

    temp = spreadSheet->currentRow;
    spreadSheet->currentRow = spreadSheet->currentColumn;
    spreadSheet->currentColumn = temp;
    
    temp = spreadSheet->lastRow;
    spreadSheet->lastRow = spreadSheet->lastColumn;
    spreadSheet->lastColumn = temp;

    temp = spreadSheet->cellCharWidth;
    spreadSheet->cellCharWidth = spreadSheet->labelCharWidth;
    spreadSheet->labelCharWidth = temp;

    /* reset the listviews to look at the lists */
    vlistviewSetList(spreadSheet->spreadView, spreadSheet->spreadList);
    vlistviewSetList(spreadSheet->rowView, spreadSheet->rowList);
    vlistviewSetList(spreadSheet->columnView, spreadSheet->columnList);
    
    /* redisplay everything */
    changeSizes(spreadSheet, 1);

    /* set the range and focus to reflect transposition */
    
    selection = vlistviewGetSelection(spreadSheet->spreadView);
    
    if (selection != NULL)
        vlistSelectRange(spreadSheet->spreadList, selection,
                         selColumn, selRow, selAcross, selDown);
    else
        vlistSelectCell(spreadSheet->spreadList, selection,
                        spreadSheet->currentRow,
                        spreadSheet->currentColumn);
    
    vlistviewSetFocus(spreadSheet->spreadView, 
                      spreadSheet->currentRow, 
                      spreadSheet->currentColumn);

    vlistviewScrollFocusIntoView(spreadSheet->spreadView);
    
    /* set the edit cell */
    focusEditCell(spreadSheet);

    /* restore the cursor to normal */
    vwindowUnblock(vdialogGetWindow(spreadSheet->spreadDialog));

    return TRUE;
}

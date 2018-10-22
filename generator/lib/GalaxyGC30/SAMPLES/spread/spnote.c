/* $Id: spnote.c,v 1.2 1994/12/29 04:13:32 skip Exp $ */
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
 * spnote.c -- Source file notify functions in spreadsheet sample.
 *
 * See the file spread.c for more information.
 */

#include "spread.h"
#include "spcellop.h"

/* storage for the previous values */
long lastMultiplyValue = 0;
long lastAddValue = 0;
long lastEscalationRate = 0;

/* values used by the copy routines */
int copyRow = -1;
int copyColumn = -1;
int copyDown = -1;
int copyAcross = -1;
int copyingOn = FALSE;

/* search functions */
void executeSearchFor(spreadStruct *spreadSheet)
{
    vspinner        *rowSpinner, *columnSpinner;
    long            row = -1;
    long            column = -1;

    rowSpinner = (vspinner *) vdialogFindItem(spreadSheet->searchDialog, 
                                              vnameInternGlobalLiteral("rowSpinner"));
    columnSpinner = (vspinner *) vdialogFindItem(spreadSheet->searchDialog, 
                                                 vnameInternGlobalLiteral("columnSpinner"));
    
    
    row = vspinnerFindTextScribedIndex(rowSpinner,
                                       vspinnerGetTextScribed(rowSpinner));
    
    column = vspinnerFindTextScribedIndex(columnSpinner,
                                          vspinnerGetTextScribed(columnSpinner));

    if (row == -1)
        row = 0;

    if (column == -1)
        column = 0;

    vlistviewScrollToCell(spreadSheet->spreadView, row, column);
    vlistviewScrollToCell(spreadSheet->rowView, row, 0);
    vlistviewScrollToCell(spreadSheet->columnView, 0, column);
}

void searchOKNotify(vbutton *button, vevent *event)
{
    spreadStruct *spreadSheet;

    spreadSheet = (spreadStruct *) vbuttonGetData(button);

    executeSearchFor(spreadSheet);

    vdialogClose(spreadSheet->searchDialog);
}

void searchApplyNotify(vbutton *button, vevent *event)
{
    spreadStruct *spreadSheet;

    spreadSheet = (spreadStruct *) vbuttonGetData(button);

    executeSearchFor(spreadSheet);
}

void searchCancelNotify(vbutton *button, vevent *event)
{
    spreadStruct *spreadSheet;

    spreadSheet = (spreadStruct *) vbuttonGetData(button);

    vdialogClose(spreadSheet->searchDialog);
}

/* goto cell functions */
void executeGotoCell(spreadStruct *spreadSheet)
{
    vspinner        *rowSpinner, *columnSpinner;
    long            row, column;

    rowSpinner = (vspinner *) vdialogFindItem(spreadSheet->gotoDialog, 
                                              vnameInternGlobalLiteral("rowSpinner"));
    columnSpinner = (vspinner *) vdialogFindItem(spreadSheet->gotoDialog, 
                                                 vnameInternGlobalLiteral("columnSpinner"));

    row = vspinnerGetValue(rowSpinner);

    column = vspinnerGetValue(columnSpinner);
    
    vlistviewScrollToCell(spreadSheet->spreadView, row, column);
    vlistviewScrollToCell(spreadSheet->rowView, row, 0);
    vlistviewScrollToCell(spreadSheet->columnView, 0, column);
}

void gotoOKNotify(vbutton *button, vevent *event)
{
    spreadStruct *spreadSheet;

    spreadSheet = (spreadStruct *) vbuttonGetData(button);

    executeGotoCell(spreadSheet);

    vdialogClose(spreadSheet->gotoDialog);
}

void gotoApplyNotify(vbutton *button, vevent *event)
{
    spreadStruct *spreadSheet;

    spreadSheet = (spreadStruct *) vbuttonGetData(button);

    executeGotoCell(spreadSheet);
}

void gotoCancelNotify(vbutton *button, vevent *event)
{
    spreadStruct *spreadSheet;

    spreadSheet = (spreadStruct *) vbuttonGetData(button);

    vdialogClose(spreadSheet->gotoDialog);
}


/* notice functions */

void raiseOKNotice(spreadStruct *spreadSheet, vdialog *baseDialog,
                   vscribe *title, vscribe *text)
{
    vnoticeSetTitleScribed(spreadSheet->okNotice, title);

    vnoticeSetTextScribed(spreadSheet->okNotice, text);
                                        
    vdialogResize(vnoticeGetDialog(spreadSheet->okNotice), 420, 120);

    vnoticePlace(spreadSheet->okNotice, baseDialog,
                 vrectPLACE_CENTER, vrectPLACE_CENTER);

    vnoticeOpen(spreadSheet->okNotice);

    vwindowSetPopup(vnoticeGetWindow(spreadSheet->okNotice), TRUE);

    vwindowSetLeader(vnoticeGetWindow(spreadSheet->okNotice),
                     vdialogGetWindow(baseDialog));
}


/* value functions */

void modifySelection(spreadStruct *spreadSheet, vlist *list, 
                     vlistSelection *selection, double modValue, 
                     char operation)
{
    spreadData      *cellData;
    vlistIterator   iterator;
    int             row, column; 
    double          escRate;
    double          escValue;
    int             escTimes;
    int             escCount;
    int             selRow, selColumn, selDown, selAcross;
    char            type;

    vlistInitSelectionIterator(&iterator, selection);

    if (operation == ESCALATE_SELECTION)
    {
        escRate = (1.0 + (modValue * 0.01));
        
        vlistDetermineSelectionBounds(list, selection, 
                                      &selRow, &selColumn, 
                                      &selDown, &selAcross);

        if ((selDown == 1) && (selAcross == 1))
        {
            /* escalate the selected cell */            
            
            cellData = (spreadData *) vlistGetCellValue(list, selRow, selColumn);
                    
            type = (cellData->type & 0xF0);

            if (type & SPREAD_DOUBLE)
            {
                cellData->data.value *= escRate;
                vlistSetCellValue(list, selRow, selColumn, cellData);
            }
        }
        
        if ((selDown > 1) && (selAcross == 1))
        {
            /* escalate the selected column */

            escTimes = 0;
            column = selColumn;

            while (vlistNextIterator(&iterator))
            {
                row = vlistGetIteratorRow(&iterator);

                cellData = (spreadData *) vlistGetCellValue(list, row, column);
                
                type = (cellData->type & 0xF0);

                if (type & SPREAD_DOUBLE)
                {
                    escValue = cellData->data.value;
                    
                    for (escCount = 0; escCount < escTimes; escCount++)
                        escValue *= escRate;
                    
                    cellData->data.value = escValue;
                
                    vlistSetCellValue(list, row, column, cellData);
                }
                escTimes++;
            }
        }

        if ((selAcross > 1) && (selDown == 1))
        {
            /* escalate the selected row */

            escTimes = 0;
            row = selRow;

            while (vlistNextIterator(&iterator))
            {
                column = vlistGetIteratorColumn(&iterator);
                cellData = (spreadData *) vlistGetCellValue(list, row, column);

                type = (cellData->type & 0xF0);

                if (type & SPREAD_DOUBLE)
                {
                    escValue = cellData->data.value;
                    
                    for (escCount = 0; escCount < escTimes; escCount++)
                        escValue *= escRate;
                
                    cellData->data.value = escValue;
                    vlistSetCellValue(list, row, column, cellData);
                }

                escTimes++;
            }
        }

        if ((selDown > 1) && (selAcross > 1))
        {
            /* range not valid for escalation, raise notice */

            raiseOKNotice(spreadSheet, spreadSheet->valueDialog,
                          vcharScribeLiteral("Escalation Notice"),
                          vcharScribeLiteral("Escalation is valid for cell, row, or column only."));
        }
    }
    else
    {
        while (vlistNextIterator(&iterator))
        {
            row = vlistGetIteratorRow(&iterator);
            column = vlistGetIteratorColumn(&iterator);
            cellData = (spreadData *) vlistGetCellValue(list, row, column);
                    
            type = (cellData->type & 0xF0);

            if (type & SPREAD_DOUBLE)
            {
                switch (operation)
                {
                    case ADD_SELECTION :
                        cellData->data.value += modValue; 
                        break;

                    case MULTIPLY_SELECTION :
                        cellData->data.value *= modValue; 
                        break;

                    default :
                        break;
                }
                vlistSetCellValue(list, row, column, cellData);
            }
        }
    }
    vlistDestroyIterator(&iterator);
}

void executeModifyValue(spreadStruct *spreadSheet)
{
    vtextitem       *textItem;
    vlist           *list;
    vlistSelection  *selection;
    double          modValue = 0;

    textItem = (vtextitem *) vdialogFindItem(spreadSheet->valueDialog,
                                             vnameInternGlobalLiteral("valueText"));

    /* we don't want a bad value, so do some checking */

    vexWITH_HANDLING
    {
        modValue = vtextitemGetTextAsFloat(textItem);
    }        
    
    vexON_EXCEPTION
    {
        /* set modValue so that it won't do any damage */

        if (spreadSheet->currentOperation == MULTIPLY_SELECTION)
            modValue = 1;
        else
            modValue = 0;  

    } vexEND_HANDLING;

    list = vlistviewGetList(spreadSheet->spreadView);

    selection = vlistviewGetSelection(spreadSheet->spreadView);

    if (!vlistIsSelectionEmpty(list, selection))
    {
        unsetEditCell(spreadSheet);

        modifySelection(spreadSheet, list, selection, 
                        modValue, spreadSheet->currentOperation);

        setEditCell(spreadSheet);
    }
            
    /* save the current values */
    switch (spreadSheet->currentOperation)
    {
        case ESCALATE_SELECTION :
            lastEscalationRate = modValue;
            break;
        
        case MULTIPLY_SELECTION :
            lastMultiplyValue = modValue;
            break;

        case ADD_SELECTION :
            lastAddValue = modValue;
            break;

        default :
            break;
    }

}

void valueOKNotify(vbutton *button, vevent *event)
{
    spreadStruct    *spreadSheet;

    spreadSheet = (spreadStruct *) vbuttonGetData(button);

    executeModifyValue(spreadSheet);

    vdialogClose(spreadSheet->valueDialog);
}

void valueApplyNotify(vbutton *button, vevent *event)
{
    spreadStruct    *spreadSheet;

    spreadSheet = (spreadStruct *) vbuttonGetData(button);

    executeModifyValue(spreadSheet);
}

void valueCancelNotify(vbutton *button, vevent *event)
{
    spreadStruct    *spreadSheet;

    spreadSheet = (spreadStruct *) vbuttonGetData(button);

    vdialogClose(spreadSheet->valueDialog);
}

char lastLabelWidth = 0;
char lastCellWidth = 0;

void widthOKNotify(vbutton *button, vevent *event)
{
    spreadStruct    *spreadSheet;

    spreadSheet = (spreadStruct *) vbuttonGetData(button);

    vdialogClose(spreadSheet->widthDialog);
}

void widthCancelNotify(vbutton *button, vevent *event)
{
    spreadStruct    *spreadSheet;

    spreadSheet = (spreadStruct *) vbuttonGetData(button);

    vdialogClose(spreadSheet->widthDialog);

    /* reset the sizes */

    spreadSheet->cellCharWidth = lastCellWidth;
    spreadSheet->labelCharWidth = lastLabelWidth;

    changeSizes(spreadSheet, 1);
}

void rowWidthSliderNotify(vcontrol *control, vevent *event)
{
    spreadStruct    *spreadSheet;
    vdialogItem     *rowWidth;

    spreadSheet = (spreadStruct *) vcontrolGetData(control);

    rowWidth = (vdialogItem *) vdialogFindItem(spreadSheet->widthDialog,
                                               vnameInternGlobalLiteral("rowWidth"));

    spreadSheet->labelCharWidth = vcontrolGetValue(control);
    
    /* change the text */
    vdialogSetItemTitleScribed(rowWidth,
                               vnumScribeInt(spreadSheet->labelCharWidth));

    /* update display */
    changeSizes(spreadSheet, 1);
}

void columnWidthSliderNotify(vcontrol *control, vevent *event)
{
    spreadStruct    *spreadSheet;
    vdialogItem     *columnWidth;

    spreadSheet = (spreadStruct *) vcontrolGetData(control);

    columnWidth = (vdialogItem *) vdialogFindItem(spreadSheet->widthDialog,
                                                  vnameInternGlobalLiteral("columnWidth"));

    spreadSheet->cellCharWidth = vcontrolGetValue(control);
    
    /* change the text */
    vdialogSetItemTitleScribed(columnWidth,
                               vnumScribeInt(spreadSheet->cellCharWidth));

    /* update display */
    changeSizes(spreadSheet, 1);
}



void executeRepCell(spreadStruct *spreadSheet)
{
    vcontrol        *end;
    vdialogItem     *which;
    vcontainer      *container;
    vspinner        *repCellSpinner;
    long            first, last, i;
    long            repAmount = 0;
    double          repValue = 0;
    vstr            *repString = NULL;
    char            repType = 0;
    spreadData      *cellData;
    char            type;

    end = (vcontrol *) vdialogFindItem(spreadSheet->repCellDialog,
                                       vnameInternGlobalLiteral("repCellEndToggle"));

    container = (vcontainer *) vdialogFindItem(spreadSheet->repCellDialog,      
                                               vnameInternGlobalLiteral("repCellExGroup"));

    which = vcontainerGetSelection(container);

    repCellSpinner = (vspinner *) vdialogFindItem(spreadSheet->repCellDialog, 
                                                  vnameInternGlobalLiteral("repCellSpinner"));

    repAmount = vspinnerGetValue(repCellSpinner);
    
    /* get the value to replicate */

    cellData = (spreadData *) vlistGetCellValue(spreadSheet->spreadList, spreadSheet->currentRow, spreadSheet->currentColumn);

    type = (cellData->type & 0xF0);

    if (type & SPREAD_DOUBLE)
    {
        repType = SPREAD_DOUBLE;
        repValue = cellData->data.value;        
    }

    if (type & SPREAD_STRING)
    {
        repType = SPREAD_STRING;
        repString = vstrClone(cellData->data.string);
    }


    if (vdialogGetItemTag(which) == vnameInternGlobalLiteral("repColumn"))
    {
        first = spreadSheet->currentRow;

        if (vcontrolGetValue(end) == TRUE)
            last = (spreadSheet->numRows - 1);
        else
        {
            last = (first + repAmount);

            if (last >= (spreadSheet->numRows))
                last = (spreadSheet->numRows - 1);
        }
        
        for (i = first; i <= last; i++)
        {   
            cellData = (spreadData *) vlistGetCellValue(spreadSheet->spreadList, 
                                                        i, spreadSheet->currentColumn);
            
            type = (cellData->type & 0xF0);
            
            if (type & repType)
            {
                if (repType & SPREAD_DOUBLE)
                    cellData->data.value = repValue;

                if (repType & SPREAD_STRING)
                    cellData->data.string = repString;

                vlistSetCellValue(spreadSheet->spreadList, 
                                  i, spreadSheet->currentColumn, cellData);
            }
        }
    }
    else
    {
        first = spreadSheet->currentColumn;
        
        if (vcontrolGetValue(end) == TRUE)
            last = (spreadSheet->numColumns - 1);
        else
        {
            last = (first + repAmount);

            if (last >= (spreadSheet->numColumns))
                last = (spreadSheet->numColumns - 1);
        }

        for (i = first; i <= last; i++)
        {   
            cellData = (spreadData *) vlistGetCellValue(spreadSheet->spreadList, 
                                                        spreadSheet->currentRow, i);
            
            type = (cellData->type & 0xF0);

            if (type & repType)
            {
                if (repType & SPREAD_DOUBLE)
                    cellData->data.value = repValue;

                if (repType & SPREAD_STRING)
                    cellData->data.string = repString;

                vlistSetCellValue(spreadSheet->spreadList, 
                                  spreadSheet->currentRow, i, cellData);
            }
        }
    }

    if ((repType & SPREAD_STRING) && (repString != NULL))
        vstrDestroy(repString);

}

void repCellOKNotify(vbutton *button, vevent *event)
{
    spreadStruct    *spreadSheet;

    spreadSheet = (spreadStruct *) vbuttonGetData(button);

    executeRepCell(spreadSheet);

    vdialogClose(spreadSheet->repCellDialog);
}

void repCellApplyNotify(vbutton *button, vevent *event)
{
    spreadStruct    *spreadSheet;

    spreadSheet = (spreadStruct *) vbuttonGetData(button);

    executeRepCell(spreadSheet);
}

void repCellCancelNotify(vbutton *button, vevent *event)
{
    spreadStruct    *spreadSheet;

    spreadSheet = (spreadStruct *) vbuttonGetData(button);

    vdialogClose(spreadSheet->repCellDialog);
}

/* if toggled, change max value */

void repCellExGroupNotify(vcontainer *container, vevent *event)
{
    spreadStruct        *spreadSheet;
    vdialogItem         *which;
    vspinner            *repCellSpinner;

    spreadSheet = (spreadStruct *) vcontainerGetData(container);

    container = (vcontainer *) vdialogFindItem(spreadSheet->repCellDialog,
                                                   vnameInternGlobalLiteral("repCellExGroup"));

    which = vcontainerGetSelection(container);
    
    repCellSpinner = (vspinner *) vdialogFindItem(spreadSheet->repCellDialog, 
                                                  vnameInternGlobalLiteral("repCellSpinner"));

    if (vdialogGetItemTag(which) == vnameInternGlobalLiteral("repRow"))
        vspinnerSetMax(repCellSpinner, (spreadSheet->numRows - 1));
    else
        vspinnerSetMax(repCellSpinner, (spreadSheet->numColumns - 1));
}


void executeFormatRow(spreadStruct *spreadSheet)
{
    vcontrol        *control;
    vspinner        *spinner;
    vcontainer      *container;
    vdialogItem     *which;
    char            format, places;
    long            r;   
    
    /* clear format */
    format = 0x00;

    /* see if the commas box is checked */
    control = (vcontrol *) vdialogFindItem(spreadSheet->formatDialog,
                                           vnameInternGlobalLiteral("commasCheck"));
    if (vcontrolGetValue(control))
        format |= SPREAD_COMMAS;

    /* see if the dollars box is checked */
    control = (vcontrol *) vdialogFindItem(spreadSheet->formatDialog,
                                           vnameInternGlobalLiteral("dollarsCheck"));
    if (vcontrolGetValue(control))
        format |= SPREAD_DOLLARS;

    /* see if the right justify box is checked */
    control = (vcontrol *) vdialogFindItem(spreadSheet->formatDialog,
                                           vnameInternGlobalLiteral("rightJustifyCheck"));
    if (vcontrolGetValue(control))
        format |= SPREAD_RIGHT_JUSTIFY;

    /* get the decimal places from the spinner */
    spinner = (vspinner *) vdialogFindItem(spreadSheet->formatDialog,
                                           vnameInternGlobalLiteral("decimalSpinner"));
    places = vspinnerGetValue(spinner);

    /* check places? */

    /* set the places in the format */
    format |= places;

    /* get the exclusive group */
    container = (vcontainer *) vdialogFindItem(spreadSheet->formatDialog,      
                                               vnameInternGlobalLiteral("rowPageExGroup"));
    
    /* find out which item is toggled */
    which = vcontainerGetSelection(container);

    /* if it's row, set format for current row */
    if (vdialogGetItemTag(which) == vnameInternGlobalLiteral("rowButton"))
        spreadSheet->rowFormat[spreadSheet->currentRow] = format;
    
    /* if it's page, set format for all rows */
    if (vdialogGetItemTag(which) == vnameInternGlobalLiteral("pageButton"))
        for (r = 0; r < spreadSheet->numRows; r++)
            spreadSheet->rowFormat[r] = format;

    /* update display */
    changeSizes(spreadSheet, 1);
}

void formatOKNotify(vbutton *button, vevent *event)
{
    spreadStruct *spreadSheet;

    spreadSheet = (spreadStruct *) vbuttonGetData(button);

    executeFormatRow(spreadSheet);

    vdialogClose(spreadSheet->formatDialog);
}

void formatApplyNotify(vbutton *button, vevent *event)
{
    spreadStruct *spreadSheet;

    spreadSheet = (spreadStruct *) vbuttonGetData(button);

    executeFormatRow(spreadSheet);
}

void formatCancelNotify(vbutton *button, vevent *event)
{
    spreadStruct *spreadSheet;

    spreadSheet = (spreadStruct *) vbuttonGetData(button);

    vdialogClose(spreadSheet->formatDialog);
}

/* convenience function for checking range overlap */
int rangeOverlap(int row1, int column1, int down1, int across1, 
                 int row2, int column2, int down2, int across2)
{   
    if (column1 >= (column2 + across2))     /* we're to the right */
        return FALSE;

    if ((column1 + across1) <= column2)     /* we're to the left */
        return FALSE;

    if (row1 >= (row2 + down2))             /* we're down below */
        return FALSE;

    if ((row1 + down1) <= row2)             /* we're up above */
        return FALSE;

    /* none of the above, so obviously we're overlapping */

    return TRUE;
}

/* copy selected range to new range starting at current cell */
void executeCopy(spreadStruct *spreadSheet)
{
    spreadData      *fromCellData = NULL;
    spreadData      *toCellData = NULL;
    vstr            *stringValue = NULL;
    double          doubleValue = 0;
    int             toRow = 0;
    int             toColumn = 0;
    int             toDown = 0;
    int             toAcross = 0;
    int             r, c;
    char            fromType = 0;
    char            toType = 0;
                
    /* determine the copy to range */
    switch (copyingOn)
    {
        case COPY_RANGE :
            toRow = spreadSheet->currentRow;
            toColumn = spreadSheet->currentColumn;
            toDown = copyDown;
            toAcross = copyAcross;
            break;
        
        case REPLICATE_ROW :
            toRow = spreadSheet->currentRow;
            toColumn = copyColumn;
            toDown = 1;
            toAcross = copyAcross;
            break;
        
        case REPLICATE_COLUMN :
            toRow = copyRow;
            toColumn = spreadSheet->currentColumn;
            toDown = copyDown;
            toAcross = 1;
            break;

        case REPLICATE_CELL :
            toRow = spreadSheet->currentRow;
            toColumn = spreadSheet->currentColumn;
            toDown = 1;
            toAcross = 1;
            break;

        case FILL_PAGE_CELL :        /* special case */
            toRow = 0;
            toColumn = 0;
            toDown = spreadSheet->numRows;
            toAcross = spreadSheet->numColumns;
            break;

        default :
            break;
    }

    /* determine how to handle the copy */
    if ((copyingOn == FILL_PAGE_ROW) || (copyingOn == FILL_PAGE_COLUMN))
    {
        if (copyingOn == FILL_PAGE_ROW)
        {
            for (r = 0; r < spreadSheet->numRows; r++)
            {
                if (r != copyRow)
                {
                    for (c = 0; c < spreadSheet->numColumns; c++)
                    {
                        /* get the from cell data and type */
                        fromCellData = (spreadData *) vlistGetCellValue(spreadSheet->spreadList, 
                                                                        copyRow, c);      
                        fromType = (fromCellData->type & 0xF0);

                        /* get the to cell data and type */
                        toCellData = (spreadData *) vlistGetCellValue(spreadSheet->spreadList, 
                                                                      r, c);      
                        toType = (toCellData->type & 0xF0);

                        if (fromType != toType)
                        {
                            /* copy is not valid, ignore */
                        }
                        else
                        {
                            /* store the data to copy from */
                            switch (fromType)
                            {
                                case SPREAD_DOUBLE :
                                    doubleValue = fromCellData->data.value;
                                    break;

                                case SPREAD_STRING :
                                    stringValue = vstrClone(fromCellData->data.string);
                                    break;

                                default :
                                    break;
                            }

                            switch (fromType)
                            {   
                                case SPREAD_DOUBLE :
                                    toCellData = (spreadData *) vmemAlloc(sizeof(spreadData));
                                    toCellData->type = (SPREAD_DOUBLE | SPREAD_DIRTY);
                                    toCellData->data.value = doubleValue;
                                    break;
            
                                case SPREAD_STRING :
                                    toCellData = (spreadData *) vmemAlloc(sizeof(spreadData));
                                    toCellData->type = (SPREAD_STRING | SPREAD_DIRTY);
                                    toCellData->data.string = stringValue;
                                    break;  

                                default :       
                                    break;
                            }

                            /* set the new cell value */
                            vlistSetCellValue(spreadSheet->spreadList, 
                                              r, c, toCellData);
                        }
                    }
                }
            }
        }
    
        if (copyingOn == FILL_PAGE_COLUMN)
        {
            for (c = 0; c < spreadSheet->numColumns; c++)
            {
                if (c != copyColumn)
                {
                    for (r = 0; r < spreadSheet->numRows; r++)
                    {
                        /* get the from cell data and type */
                        fromCellData = (spreadData *) vlistGetCellValue(spreadSheet->spreadList, 
                                                                         r, copyColumn);      
                        fromType = (fromCellData->type & 0xF0);

                        /* get the to cell data and type */
                        toCellData = (spreadData *) vlistGetCellValue(spreadSheet->spreadList, 
                                                                      r, c);      
                        toType = (toCellData->type & 0xF0);

                        if (fromType != toType)
                        {
                            /* copy is not valid, ignore */
                        }
                        else
                        {
                            /* store the data to copy from */
                            switch (fromType)
                            {
                                case SPREAD_DOUBLE :
                                    doubleValue = fromCellData->data.value;
                                    break;

                                case SPREAD_STRING :
                                    stringValue = vstrClone(fromCellData->data.string);
                                    break;

                                default :
                                    break;
                            }

                            switch (fromType)
                            {   
                                case SPREAD_DOUBLE :
                                    toCellData = (spreadData *) vmemAlloc(sizeof(spreadData));
                                    toCellData->type = (SPREAD_DOUBLE | SPREAD_DIRTY);
                                    toCellData->data.value = doubleValue;
                                    break;
            
                                case SPREAD_STRING :
                                    toCellData = (spreadData *) vmemAlloc(sizeof(spreadData));
                                    toCellData->type = (SPREAD_STRING | SPREAD_DIRTY);
                                    toCellData->data.string = stringValue;
                                    break;  

                                default :       
                                    break;
                            }

                            /* set the new cell value */
                            vlistSetCellValue(spreadSheet->spreadList, 
                                              r, c, toCellData);
                        }
                    }
                }
            }
        }

    }
    else
    {
        /* see if copy to range is within copy from range */
        if ((rangeOverlap(toRow, toColumn, toDown, toAcross,
                           copyRow, copyColumn, copyDown, copyAcross)) &&
            (copyingOn != FILL_PAGE_CELL))
        {
            raiseOKNotice(spreadSheet, spreadSheet->spreadDialog,
                          vcharScribeLiteral("Copy Notice"), 
                          vcharScribeLiteral("Cannot copy to cell within selected range."));
        }
        else
        {
            if ((toRow + toDown) >= spreadSheet->numRows)
                toDown = (spreadSheet->numRows - toRow);

            if ((toColumn + toAcross) >= spreadSheet->numColumns)
                toAcross = (spreadSheet->numColumns - toColumn);

            /* if filling page, get the value to use for fill */
            if (copyingOn == FILL_PAGE_CELL)
            {
                    fromCellData = (spreadData *) vlistGetCellValue(spreadSheet->spreadList, 
                                                                    copyRow, copyColumn);      
                    fromType = (fromCellData->type & 0xF0);
                        
                    switch (fromType)
                    {
                        case SPREAD_DOUBLE :
                            doubleValue = fromCellData->data.value;
                            break;

                        case SPREAD_STRING :
                            stringValue = vstrClone(fromCellData->data.string);
                            break;

                        default :
                         break;
                    }
            }

            for (r = 0; r < toDown; r++)
            {
                for (c = 0; c < toAcross; c++)
                {
                    /* if normal copying, get the source value */
                   if (copyingOn != FILL_PAGE_CELL)
                    {
                        /* get the from cell data and type */
                        fromCellData = (spreadData *) vlistGetCellValue(spreadSheet->spreadList, 
                                                                    (copyRow + r), (copyColumn + c));      
                        fromType = (fromCellData->type & 0xF0);
                    }

                    /* get the to cell data and type */
                    toCellData = (spreadData *) vlistGetCellValue(spreadSheet->spreadList, 
                                                                  (toRow + r), (toColumn + c));      
                    toType = (toCellData->type & 0xF0);

                    if (fromType != toType)
                    {
                        /* copy is not valid, ignore */
                    }
                    else
                    {
                        /* if normal copying, get the source data */
                        if (copyingOn != FILL_PAGE_CELL)
                        {
                            /* store the data to copy from */
                            switch (fromType)
                            {
                                case SPREAD_DOUBLE :
                                    doubleValue = fromCellData->data.value;
                                    break;

                                case SPREAD_STRING :
                                    stringValue = vstrClone(fromCellData->data.string);
                                    break;

                                default :
                                    break;
                            }
                        }

                        /* free the data in the copy to cell */
                        switch (toType)
                        {
                            case SPREAD_DOUBLE :
                                if (toCellData != NULL)
                                   vmemFree(toCellData);
                                break;
            
                            case SPREAD_STRING :
                                if (toCellData->data.string != NULL)
                                    vstrDestroy(toCellData->data.string);
                                if (toCellData != NULL)
                                    vmemFree(toCellData);
                                break;  

                            default :       
                                break;
                        }

                        switch (fromType)
                        {
                            case SPREAD_DOUBLE :
                                toCellData = (spreadData *) vmemAlloc(sizeof(spreadData));
                                toCellData->type = (SPREAD_DOUBLE | SPREAD_DIRTY);
                                toCellData->data.value = doubleValue;
                                break;
            
                            case SPREAD_STRING :
                                toCellData = (spreadData *) vmemAlloc(sizeof(spreadData));
                                toCellData->type = (SPREAD_STRING | SPREAD_DIRTY);
                                toCellData->data.string = stringValue;
                                break;  

                            default :       
                                break;
                        }

                        /* set the new cell value */
                        vlistSetCellValue(spreadSheet->spreadList, 
                                      (toRow + r), (toColumn + c), toCellData);
                    }
                }
            }
        }
    }

    /* turn of copying if page was just filled */
    if ((copyingOn == FILL_PAGE_CELL) ||
        (copyingOn == FILL_PAGE_ROW) ||
        (copyingOn == FILL_PAGE_COLUMN) ||
	(copyingOn == COPY_RANGE))
    {
        vdialogSetItemCursor(vlistviewGetItem(spreadSheet->spreadView), spreadSheet->standardCursor);
        
        copyingOn = COPY_OFF;
                        
        changeMessage(spreadSheet->messageDisplay, 
                      vcharScribeLiteral(""));
    }
}

/* $Id: spkey.c,v 1.3 1997/09/25 22:27:53 dimitri Exp $ */
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
 * spkey.c -- Source file for key and text operations in spreadsheet sample.
 *
 * See the file spread.c for more information.
 */

#include "spread.h"

/* global for editing */
char editOn = 1;

/* edit text functions */

/* return the edit text as a float */
double getTextAsFloat(spreadStruct *spreadSheet)
{
    volatile double     value;
    long                length;
    vchar               editText[64];

    value = 0;

    vexWITH_HANDLING
    {
        length = vtextLength(spreadSheet->editData);

        if (length > 0)
        {
            vtextSelectRange(spreadSheet->editData,
                             spreadSheet->editSelection,
                             0, length);

            vtextGetText(spreadSheet->editData,
			 spreadSheet->editSelection,
			 editText, length);

	    value = vnumParseFloat(editText, NULL);
        }
    }

    vexON_EXCEPTION
    {
        value = 0;  /* get original cell value? */

    } vexEND_HANDLING;

    return (value);
}

/* return the edit text as a string */
vstr *getTextAsString(spreadStruct *spreadSheet)
{
    vstr        *volatile string = NULL;
    long        length;
    long        end;
    vchar       editText[64];

    vexWITH_HANDLING
    {
        length = vtextLength(spreadSheet->editData);

        if (length > 0)
        {
            vtextSelectRange(spreadSheet->editData,
                             spreadSheet->editSelection,
                             0, length);

            end = vtextGetText(spreadSheet->editData,
                               spreadSheet->editSelection,
                               editText, length);

            if (end > 0)
                editText[end] = '\0';

            string = vstrClone(editText);
        }
    }

    vexON_EXCEPTION
    {
        string = vstrCloneScribed(vcharScribeLiteral("string exception!\n"));

    } vexEND_HANDLING;

    return (string);

}

/* called when the edit view gets a notification event */
void editViewNotify(vtextview *textview, vevent *event, long message)
{
    spreadStruct    *spreadSheet;

    spreadSheet = (spreadStruct *) vtextviewGetData(textview);

    if (message == vtextviewACCEPT_NOTIFY)
    {
        unsetEditCell(spreadSheet);
    }

    if (message == vtextviewUPDATE_NOTIFY)
    {
    }

}

/* insert text into the edit text */
void editTextInsert(vtext *text, vtextSelection *selection,
                    const vchar *nextChar, long length)
{
    spreadStruct    *spreadSheet;
    
    spreadSheet = (spreadStruct *) vtextGetData(text);

    if (*nextChar == vcharFromLiteral('\n'))
    {
        unsetEditCell(spreadSheet);
    }
    else
    {
	vclassSendSuper(vtextGetClass(text),
			vtextINSERT,
			(text, selection, nextChar, length));
    }
}

/* delete text from the edit text */
void editTextDelete(vtext *text, vtextSelection *selection)
{
    vclassSendSuper(vtextGetClass(text),
                    vtextDELETE,
                    (text, selection));
}

/* called to set the edit cell's position and contents */
void setEditCell(spreadStruct *spreadSheet)
{
    spreadData          *cellData;
    vrect               cellRect;
    vdialogItem         *editItem;
    static vscribe      *cellScribe;
    static vchar        cellString[64];
    static vchar        *startChar, *decimalChar;
    char                length;
    char                format, places;
    char                type;

    /* cache the item(s) */
    editItem = vtextviewGetItem(spreadSheet->editView);

    vlistviewGetCellRect(spreadSheet->spreadView,
                         spreadSheet->currentRow, 
                         spreadSheet->currentColumn, 
                         &cellRect);
        
    cellData = (spreadData *) vlistGetCellValue(spreadSheet->spreadList, 
                                                spreadSheet->currentRow, 
                                                spreadSheet->currentColumn);
    
    /* set the value for the edit text */
    type = (cellData->type & 0xF0);

    if (type & SPREAD_DOUBLE)
    {
        /* get the format */
        format = (spreadSheet->rowFormat[spreadSheet->currentRow] & 0xF0);
        places = (spreadSheet->rowFormat[spreadSheet->currentRow] & 0x0F);

	cellScribe = vnumScribeFloatFormatted(cellData->data.value,
					      vnumGetDecimalDigitSet(), 
					      vnumGetNormalFormat(),
					      NULL, TRUE, -1);
	vnumSetScribeDigitsAfter(cellScribe, places);
	vnumSetScribeTruncateZeroes(cellScribe, FALSE);

        /* copy the scribe into a character buffer */
        vcharCopyScribed(cellScribe, cellString);
    
        /* find the decimal */
        startChar = cellString;
        decimalChar = vcharSearchChar(cellString, '.');
        
	/* compute the length */
	length = vcharLength(cellString);

        /* select the edit range */
        vtextSelectRange(spreadSheet->editData,
                         spreadSheet->editSelection,
                         0, vtextLength(spreadSheet->editData));

        /* insert the text into the edit item */
        vtextInsert(spreadSheet->editData, 
                    spreadSheet->editSelection, 
                    cellString, length);
    
    }

    if (type & SPREAD_STRING)
    {
        cellScribe = vcharScribe(cellData->data.string);

        vcharCopyScribed(cellScribe, cellString);

        length = vtextLength(spreadSheet->editData);

        vtextSelectRange(spreadSheet->editData,
                         spreadSheet->editSelection,
                         0, length);

        vtextInsert(spreadSheet->editData, 
                    spreadSheet->editSelection, 
                    cellString, vcharLength(cellString));
    }

    /* set the edit rect */
    cellRect.x -= 2;
    cellRect.y += 1;
    cellRect.w += 1; 
    vdialogSetItemRect(editItem, 
                       &cellRect);

    /* scroll textview and move cursor to end */
    vtextviewMoveCursorToEnd(spreadSheet->editView, vtextviewLEFT);
    vtextviewScrollToStart(spreadSheet->editView, vtextviewSTS_ALWAYS);
    vtextviewSetCaret(spreadSheet->editView);
    
    /* change focus of listview */
    vlistviewSetFocus(spreadSheet->spreadView, 
		      spreadSheet->currentRow, 
		      spreadSheet->currentColumn);
    
    /* set the last row and column to reflect change */
    spreadSheet->lastRow = spreadSheet->currentRow;
    spreadSheet->lastColumn = spreadSheet->currentColumn;

    /* make the item visible and enabled */
    vdialogEnableItem(editItem);
    vdialogShowItem(editItem);
    editOn = 1;

}    

/* called to store the edit value's contents and hide it*/
void unsetEditCell(spreadStruct *spreadSheet)
{
    vdialogItem     *editItem;
    vdialogItem     *spreadItem;
    double          editValue;       
    double          difference;
    vstr            *editString;
    vstr            *tmpString1;
    vstr            *tmpString2;
    spreadData      *cellData;
    char            type;   
    
    if (editOn)
    {
	/* cache the edit and spread items */
	editItem = vtextviewGetItem(spreadSheet->editView);
	spreadItem = vlistviewGetItem(spreadSheet->spreadView);

	/* disable and hide the item */
	vdialogHideItem(editItem);
	vdialogDisableItem(editItem);

	editOn = 0;

	/* get the old cell's value */
	cellData = (spreadData *) vlistGetCellValue(spreadSheet->spreadList, 
						    spreadSheet->lastRow, 
						    spreadSheet->lastColumn);
   
	type = (cellData->type & 0xF0);

	/* get the edit text based on type */
	if (type & SPREAD_DOUBLE)
	{
	    editValue = getTextAsFloat(spreadSheet);
    
	    difference = (cellData->data.value - editValue);

	    if ((difference * 100000000) >= 1)
                cellData->type |= SPREAD_DIRTY;

	    cellData->data.value = editValue;
	}            
    
	if (type & SPREAD_STRING)
	{
	    editString = getTextAsString(spreadSheet);

	    if (editString)
	    {
		tmpString1 = vstrClone(cellData->data.string);                              
		tmpString2 = vstrClone(editString);

		if (vcharCompare(tmpString1, tmpString2) != 0)
                    cellData->type |= SPREAD_DIRTY;
                  
		if (tmpString1)
                    vstrDestroy(tmpString1);
            
		if (tmpString2)
                    vstrDestroy(tmpString2);

		if (cellData->data.string)
                    vstrDestroy(cellData->data.string);

		cellData->data.string = editString;
	    }
	}

	/* set the value back into the cell */
	vlistSetCellValue(spreadSheet->spreadList, 
			  spreadSheet->lastRow, 
			  spreadSheet->lastColumn, 
			  cellData);

    }
}

void focusEditCell(spreadStruct *spreadSheet)
{
    long row, column;

    vlistviewGetFocus(spreadSheet->spreadView, &row, &column);

    spreadSheet->currentRow = row;
    spreadSheet->currentColumn = column;

    setEditCell(spreadSheet);
}

/* sets the editing rect, including checks for position, scrolling, etc. */
void setEditRect(spreadStruct *spreadSheet)
{
    int             row, column;
    int             tmpRow, tmpColumn;
    int             selRow, selColumn, selDown, selAcross;
    vlistSelection  *selection;
    const vrect     *listRect;
    vrect           cellRect;
    long            top, right, bottom, left;
    long            hdelta, vdelta;

    /* get the focus cell */
    vlistviewGetFocus(spreadSheet->spreadView, &row, &column);
        
    spreadSheet->currentRow = row;
    spreadSheet->currentColumn = column;

    /* if copying is on, perform the copy */
    if (copyingOn)
        executeCopy(spreadSheet);

    selection = vlistviewGetSelection(spreadSheet->spreadView);

    if (selection != NULL)
    {
        /* get the selection bounds */

        vlistDetermineSelectionBounds(spreadSheet->spreadList, selection,
                                      &selRow, &selColumn, 
                                      &selDown, &selAcross);
        tmpRow = row;
        tmpColumn = column;

        /* flip the cell to mimic excel */

        if (tmpRow <= selRow)
            spreadSheet->currentRow = (selRow + selDown - 1);

        if (tmpRow >= (selRow + selDown - 1))
            spreadSheet->currentRow = selRow;

        if (tmpColumn <= selColumn)
            spreadSheet->currentColumn = (selColumn + selAcross - 1);

        if (tmpColumn >= (selColumn + selAcross - 1))
            spreadSheet->currentColumn = selColumn;
        
        row = spreadSheet->currentRow;
        column = spreadSheet->currentColumn;

        listRect = vlistviewGetListRect(spreadSheet->spreadView);

        vlistviewGetCellRect(spreadSheet->spreadView, row, column, &cellRect);

        /* see if edit cell is within the visible range */
        if (!vrectIntersects(listRect, &cellRect))
        {
            /* if not visible, do nothing */
        }
        else
        {
            /* see if cell is fully visible */

            if (!vrectEncloses(listRect, &cellRect))
            {
                /* if not, scroll it into view */

                top = vlistviewGetTopRow(spreadSheet->spreadView);
                right = vlistviewGetRightColumn(spreadSheet->spreadView);
                bottom = vlistviewGetBottomRow(spreadSheet->spreadView);
                left = vlistviewGetLeftColumn(spreadSheet->spreadView);
                   
                hdelta = 0;
                vdelta = 0;
            
                if (column == right)
                    hdelta = -((cellRect.x + cellRect.w) -
                               (listRect->x + listRect->w));

                if (column == left)
                    hdelta = (listRect->x - cellRect.x);

                if (row == top)
                    vdelta = -((cellRect.y + cellRect.h) -
                               (listRect->y + listRect->h));

                if (row == bottom)
                    vdelta = (listRect->y - cellRect.y);

                vlistviewScrollRelative(spreadSheet->spreadView, hdelta, vdelta);
            }

            setEditCell(spreadSheet);
        }
    }
}



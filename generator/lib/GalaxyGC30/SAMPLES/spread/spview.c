/* $Id: spview.c,v 1.1 1994/11/21 01:06:27 chad Exp $ */
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
 * spview.c -- Source file listview functions in spreadsheet sample.
 *
 * See the file spread.c for more information.
 */

#include "spread.h"

/* called when the spreadview is scrolled */
void spreadviewNotifyScroll(vlistview *listview, int horzDistance, int vertDistance)
{
    spreadStruct    *spreadSheet;

    spreadSheet = (spreadStruct *) vlistviewGetData(listview);
    
    /* unset the edit cell */
    unsetEditCell(spreadSheet);

    /* scroll the columnview to synchronize */
    if (horzDistance != 0)
        vlistviewScrollRelative(spreadSheet->columnView, horzDistance, 0);
    
    /* scroll the rowview to synchronize */
    if (vertDistance != 0)
        vlistviewScrollRelative(spreadSheet->rowView, 0, vertDistance);
}

/* called when the spreadview gets a selection event */
void spreadviewNotifySelect(vlistview *listview, int type)
{
    spreadStruct    *spreadSheet;

    spreadSheet = (spreadStruct *) vlistviewGetData(listview);
    
    if ((type == vlistviewSELECTION_WILL_CHANGE) ||
        (type == vlistviewSELECTION_IS_CHANGING))
    {
        unsetEditCell(spreadSheet);
    }

    if (type == vlistviewSELECTION_HAS_CHANGED)
    {
        setEditCell(spreadSheet);
    }
}

/* called when the spreadsheet gets an event */
void spreadviewItemNotify(vdialogItem *item, vevent *event)
{
    veventType      eventType;
    spreadStruct    *spreadSheet;

    spreadSheet = (spreadStruct *) vdialogGetItemData(item);

    eventType = veventGetType(event);

    if (eventType == veventBUTTON_UP)
    {
        unsetEditCell(spreadSheet);
        setEditRect(spreadSheet);
    }
    
    if (eventType == veventKEY_DOWN)
    {
        focusEditCell(spreadSheet);
    }
}

/* called by both rowview and columnview for backgrounds */
void drawCellBackground(vdialogItem *dialogItem, vrect *rect)
{
    vcolor      *background;
    vcolor      *shadowTop;
    vcolor      *shadowBottom;

    /* get the colors to be used for the drawing */  /* Make it white */
    background = vdialogDetermineItemColor(dialogItem, 
					   vdrawCOLOR_BACKGROUND_EMBOSS);

    shadowTop = vdialogDetermineItemColor(dialogItem,
                                          vdrawCOLOR_SHADOW_TOP);
    shadowBottom = vdialogDetermineItemColor(dialogItem,
                                             vdrawCOLOR_SHADOW_BOTTOM);

    /* draw the background as a highlighted rectangle */
    vdrawGSave();

    vdrawSetLineWidth(vdialogDetermineItemLineWidth(dialogItem));

    vdrawRectHiliteFillInside(rect->x, rect->y, rect->w, rect->h,
                              background, shadowTop, shadowBottom);

    vdrawGRestore();
}

/* override of standard listview draw cell background */
void columnviewDrawCellBackground(vlistview *listview, int row, int column, 
                                  int selected, vrect *rect)
{
    drawCellBackground(vlistviewGetItem(listview), rect);
}

/* overrride of standard listview draw cell background */
void rowviewDrawCellBackground(vlistview *listview, int row, int column, 
                               int selected, vrect *rect)
{
    drawCellBackground(vlistviewGetItem(listview), rect);
}

/* override of the standard listview draw cell contents */
void rowviewDrawCellContents(vlistview *listview, int row, int column, 
                             int selected, vrect *rect)
{
    spreadStruct    *spreadSheet = NULL;
    spreadData      *cellData = NULL;
    vscribe         *cellScribe = NULL;
    vstr            *tmpString = NULL;
    long            x, y;
    char            length, width;
    char            type;

    spreadSheet = (spreadStruct *) vlistviewGetData(listview);

    cellData = (spreadData *) vlistGetCellValue(vlistviewGetList(listview), row, column);
    
    type = (cellData->type & 0xF0);

    if (type & SPREAD_DOUBLE)
    {
        /* format the floating point data in the scribe */
        cellScribe = vnumScribeFloatFormatted(cellData->data.value,
                                              vnumGetDecimalDigitSet(), 
                                              vnumGetNormalFormat(),
                                              NULL, FALSE, -1);

        vnumSetScribeDigitsAfter(cellScribe, 2);
        vnumSetScribeTruncateZeroes(cellScribe, FALSE);
    }

    if (type & SPREAD_STRING)
    {
        /* get the string into the scribe */
        tmpString = vstrClone(cellData->data.string);
        cellScribe = vstrScribe(tmpString);
    }

    /* calculate the right justification */
    length = vcharLengthScribed(cellScribe);
    
    width = (length * spreadSheet->fontWidth);

    x = (rect->x + rect->w) - (width + FONT_OFFSET_X);
    y = (rect->y + FONT_OFFSET_Y);

    vdrawMoveTo(x, y);

    vdrawScribedShow(cellScribe);
}

/* override of the standard listview draw cell contents */
void columnviewDrawCellContents(vlistview *listview, int row, int column, 
                                int selected, vrect *rect)
{
    spreadStruct    *spreadSheet = NULL;
    spreadData      *cellData = NULL;
    vscribe         *cellScribe = NULL;
    vstr            *tmpString = NULL;
    int             x, y;
    int             length, width;
    char            type;

    spreadSheet = (spreadStruct *) vlistviewGetData(listview);

    cellData = (spreadData *) vlistGetCellValue(vlistviewGetList(listview), row, column);
    
    type = (cellData->type & 0xF0);
    
    if (type & SPREAD_DOUBLE)
    {
        /* format the floating point data in the scribe */
        cellScribe = vnumScribeFloatFormatted(cellData->data.value,
                                              vnumGetDecimalDigitSet(), 
                                              vnumGetNormalFormat(),
                                              NULL, FALSE, -1);

        vnumSetScribeDigitsAfter(cellScribe, 2);
        vnumSetScribeTruncateZeroes(cellScribe, FALSE);
    }

    if (type & SPREAD_STRING)
    {
        /* get the string into the scribe */
        tmpString = vstrClone(cellData->data.string);
        cellScribe = vstrScribe(tmpString);
    }

    /* calculate the right justification */
    length = vcharLengthScribed(cellScribe);
    
    width = (length * spreadSheet->fontWidth);

    x = (rect->x + rect->w) - (width + FONT_OFFSET_X);
    y = (rect->y + FONT_OFFSET_Y);

    vdrawMoveTo(x, y);

    vdrawScribedShow(cellScribe);
}

/* override of the standard listview draw cell background */
void spreadviewDrawCellBackground(vlistview *listview, int row, int column, 
                                  int selected, vrect *rect)
{
    vdialogItem *dialogItem;
    vcolor      *background;
    vcolor      *shadowTop;
    vcolor      *shadowBottom;

    /* get the dialog item */
    dialogItem = vlistviewGetItem(listview);

    /* get the colors to be used for the drawing */
    if (selected)
    {
        background = vdialogDetermineItemColor(dialogItem,
					       vdrawCOLOR_BACKGROUND_HILITE);
    }
    else
    {
        background = vcolorGetWhite();
    }

    shadowTop = vdialogDetermineItemColor(dialogItem,
					  vdrawCOLOR_SHADOW_TOP);

    shadowBottom = vdialogDetermineItemColor(dialogItem,
					     vdrawCOLOR_SHADOW_BOTTOM);

    /* draw the background as a highlighted rectangle */
    vdrawGSave();

    vdrawSetLineWidth(vdialogDetermineItemLineWidth(dialogItem));

    vdrawRectHiliteFillInside(rect->x, rect->y, rect->w, rect->h,
                              background, shadowTop, shadowBottom);

    vdrawGRestore();
}

/* override of the standard listview draw cell contents */
void spreadviewDrawCellContents(vlistview *listview, int row, int column, 
                                int selected, vrect *rect)
{
    spreadStruct        *spreadSheet;
    spreadData          *cellData;
    static vscribe      *cellScribe;
    static vstr         *tmpString;
    long                x, y;
    long                length = 0;
    long                width = 0;
    char                format, places;
    char                type, dirty;
    static vchar        drawString[64];
    static vchar        *startChar, *decimalChar;

    spreadSheet = (spreadStruct *) vlistviewGetData(listview);

    cellData = (spreadData *) vlistGetCellValue(vlistviewGetList(listview), row, column);
    
    /* get the data type */
    type = (cellData->type & 0xF0);
        
    /* see if it's dirty */
    dirty = (cellData->type & 0x0F);

    /* get the row format */
    format = (spreadSheet->rowFormat[row] & 0xF0);
    
    if (type & SPREAD_DOUBLE)
    {
        /* get the number of places */
        places = (spreadSheet->rowFormat[row] & 0x0F);

        if (format & SPREAD_COMMAS)
        {
            if (format & SPREAD_DOLLARS)
            {
                cellScribe = vnumScribeFloatFormatted(cellData->data.value,
                                                      vnumGetDecimalDigitSet(), 
                                                      commaDollarFormat,
                                                      NULL, TRUE, -1);
            }
            else
            {
                cellScribe = vnumScribeFloatFormatted(cellData->data.value,
                                                      vnumGetDecimalDigitSet(), 
                                                      commaFormat,
                                                      NULL, TRUE, -1);
            }
        }
        else
        {
            if (format & SPREAD_DOLLARS)
            {
                cellScribe = vnumScribeFloatFormatted(cellData->data.value,
                                                      vnumGetDecimalDigitSet(), 
                                                      dollarFormat,
                                                      NULL, TRUE, -1);
            }
            else
            {
                cellScribe = vnumScribeFloatFormatted(cellData->data.value,
                                                      vnumGetDecimalDigitSet(), 
                                                      vnumGetNormalFormat(),
                                                      NULL, TRUE, -1);
                vnumSetScribeDigitsAfter(cellScribe, places);
                vnumSetScribeTruncateZeroes(cellScribe, FALSE);
            }
        }
    
        /* copy the scribe into a character buffer */
        vcharCopyScribed(cellScribe, drawString);
    
        startChar = drawString;
        decimalChar = vcharSearchChar(drawString, '.');
    
        if (decimalChar != NULL)
            length = (((decimalChar - startChar) + 1) + places);
        else 
            length = vcharLength(drawString);
    
    }
    
    if (type & SPREAD_STRING)
    {
        /* get the string into the scribe */
        tmpString = vstrClone(cellData->data.string);
        
        cellScribe = vstrScribe(tmpString);
        
        length = vcharLengthScribed(cellScribe);
        
        vcharCopyScribed(cellScribe, drawString);
    }

    /* set the text color */
    if (selected)
    {
	vdrawSetColor(vcolorGetWhite());
    }
    else
    {
	vdrawSetColor(vcolorGetBlack());
    }

    width = (length * spreadSheet->fontWidth) + FONT_OFFSET_X;

    if (width > rect->w)
    {
        /* string is too big, set length to cell width -1 for room */
        length = (spreadSheet->cellCharWidth - 1);

        /* display stars to indicate problem */
        vcharCopyScribedBounded(vcharScribeLiteral("***************************"), 
                                drawString, length);
        
        /* draw the stars in the center of the rectangle */
        vdrawSizedRectShowCenterX(drawString, length, rect);
    
    }
    else
    {
        /* string is okay, so figure out justification */
        if (format & SPREAD_RIGHT_JUSTIFY)
            x = ((rect->x + rect->w) - width);
        else
            x = (rect->x + FONT_OFFSET_X);

        y = (rect->y + FONT_OFFSET_Y);
    
        /* move to the point and draw the string */
        vdrawMoveTo(x, y);
        vdrawSizedShow(drawString, length);
/*        
        if (dirty)  
        {
            vdrawMoveTo((x + 1), y);
            vdrawSizedShow(drawString, length);
        }
*/
    
    }
}

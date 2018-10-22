/* $Id: style.c,v 1.2 1995/01/11 00:31:35 dimitri Exp $ */

/************************************************************

    style.c
    C Source to xwrite

    (c) Copyright Visix Software
    All rights reserved

************************************************************/

#include "micwrite.h"

#if vdebugDEBUG
#define vdebugTAG "xwriteStyle"
#endif

writeStyleDoc			*writeStyleWindow = NULL;
writeStyle            		*writeStyleList   = NULL;
int                              writeStyleCount  = 0;
writeStyle            		*writeNormalStyle;

static writeStyleDocClass	*defaultStyleClass 	 = NULL;
static vtextitemClass		*defaultDescriptionClass = NULL;
static vpool			*writeStylePool 	 = NULL;
static writeDocument    	*_targetDocument 	 = NULL;

static void 	_styleListNotify(vlistview *, int);
static void 	_styleListDraw(vlistview *, int, int, int, vrect *);

void writeCreateStyleWindow(void)
{
    vdialog		*dialog;
    vlistview		*listview;
    vlist               *list;

    if (writeStyleWindow != NULL) {
        if (!vdialogIsOpen(&writeStyleWindow->dialog))
            vdialogOpen(&writeStyleWindow->dialog);
	vwindowRaise(vdialogGetWindow(&writeStyleWindow->dialog));
        return;
    }

    writeStyleWindow = (writeStyleDoc *)
	writeLoadDialog(vnameInternGlobalLiteral("Styles"));

    dialog = &writeStyleWindow->dialog;
    
    writeCenterWindow((vwindow *) dialog);

    writeStyleWindow->untitledCount = 0;

    writeStyleWindow->description = (vtextitem *)
        vdialogFindItem(dialog, vnameInternGlobalLiteral("Description"));
    writeStyleWindow->styleList   = (vlistview *)
        vdialogFindItem(dialog, vnameInternGlobalLiteral("List"));

    listview = writeStyleWindow->styleList;

    vlistviewSetList(listview, list = vlistCreate());
    vlistviewSetSelection(listview, vlistCreateSelection(list));

    vlistviewSetSelectNotify(listview,    _styleListNotify);
    vlistviewSetCellContentProc(listview, _styleListDraw);
    vlistSetSelectMethod(vlistviewGetList(listview),
			 vlistviewGetSelection(listview),
			 vlistONE_ONLY_SELECTION);

    writeLoadStyleWindow(NULL, FALSE);

    vlistSelectCell(vlistviewGetList(listview),
		    vlistviewGetSelection(listview), 0, 0);

    writeBuildWindowMenus();

    vdialogOpen(dialog);
}

/*
 * _writeDestroyStyle
 *
 * Close the style window
 */
static void _writeDestroyStyle(
    writeStyleDoc	*styleData
    )
{
    vlist               *list;

    list = vlistviewGetList(styleData->styleList);
    vlistviewSetList(styleData->styleList, NULL);
    vlistDestroy(list);

    vclassSendSuper(defaultStyleClass, vobjectDESTROY, (styleData));

    writeStyleWindow = NULL;

    writeBuildWindowMenus();
}

/*
 * writeLoadStyleWindow
 *
 * Reload the style window list to dislay the list of markers for
 * the document data
 */
void writeLoadStyleWindow(
    writeDocument	*data,
    vbool               setTarget
    )
{
    vlistview		*listview;
    writeStyle          *scan;
    int                 i = 0;

    if (_targetDocument == NULL || setTarget)
        _targetDocument = data;

    if (writeStyleWindow == NULL)
        return;

    listview = writeStyleWindow->styleList;

    vlistSetRowCount(vlistviewGetList(listview), 0);

    /* First, load the global list of styles */

    scan = writeStyleList;

    while (scan != NULL) {

        vlistSetCellValue(vlistviewGetList(listview), i, 0, scan);

        i++;
        scan = scan->next;
    }
    
    if (data == NULL || data != _targetDocument)
        return;

    /* Load 'data's style list */

    /* ... */
}

/* * * * *     Write Style Routines     * * * * */

/*
 * writeCreateStyle
 *
 * Create a new write style
 */
writeStyle *writeCreateStyle(void)
{
    writeStyle  *style;

    if (writeStylePool == NULL)
        writeStylePool = vpoolCreate(sizeof(writeStyle));

    style        = (writeStyle *) vpoolAlloc(writeStylePool);
    style->next  = NULL;
    style->style = NULL;
    style->flags = 0;
    style->name  = NULL;

    return(style);
}

/*
 * writeDestroyStyle
 */
void writeDestroyStyle(
    writeStyle          *style
    )
{
    if (style->flags & writeSTYLE_GLOBAL)
        vtextDestroyGlobalStyle(style->style);

    vpoolFree(writeStylePool, style);
}

/*
 * writeDestroyStyleList
 */
void writeDestroyStyleList(
    writeStyle		**styleList
    )
{
    writeStyle          *scan, *freeThis;

    scan = *styleList;

    while (scan != NULL) {
    
        freeThis = scan;
        scan     = scan->next;

        writeDestroyStyle(freeThis);

    }

    *styleList = NULL;
}

/*
 * writeLoadStyleList
 *
 * Load a list of styles from a resource (array of dicts)
 */
writeStyle *writeLoadStyleList(
    vresource		res
    )
{
    writeStyle          *list = NULL, *newStyle;
    int                 count;
    vresource           styleRes;
    const vname         *tag;

    count = vresourceCountComponents(res);

    while (count-- > 0) {

        styleRes = vresourceGetNthComponent(res, count,
                                            (const vname **) &tag);

        newStyle              = writeCreateStyle();
        newStyle->name        = tag;
        newStyle->style       = vtextCreateGlobalStyle();
        newStyle->flags       = writeSTYLE_GLOBAL;
        newStyle->next        = list;
        list                  = newStyle;

        vtextLoadInitStyle(newStyle->style, styleRes);
    }
    
    return(list);
}

/*
 * writeStoreStyleList
 *
 * Store a list of styles to a resource (array of dicts)
 */
void writeStoreStyleList(
    writeStyle          *styleList,
    vresource		res
    )
{
    vresource	styleRes;

    while (styleList != NULL) {
      
        styleRes = vresourceCreate(res, styleList->name, vresourceDICT);

	vtextStoreStyle(styleList->style, styleRes);

	styleList = styleList->next;
    }

}

/* * * * *     Style list support functions    * * * * */

/*
 * _styleListNotify
 */
static void _styleListNotify(
    vlistview		*item,
    int                 notifyType
    )
{
    if (notifyType != vlistviewSELECTION_HAS_CHANGED)
	return;

    /*
     * Update the style description text item
     */

/*
    if (vlistitemGetSelectedRow(item) == vlistNO_CELLS_SELECTED)
        vbuttonDisable(info->u.key.remove);
    else
        vbuttonEnable(info->u.key.remove); */
}

/*
 * _styleListDraw
 */
static void _styleListDraw(
    vlistview		*listview,
    int                 row,
    int                 column,
    int                 selected,
    vrect               *bounds
    )
{
    writeStyle          *style;

    vdrawMoveTo(bounds->x + 5, bounds->y + (bounds->h / 2)  - 8);
   /* vdrawImageCompositeIdent(fileType->icon); */

    style = (writeStyle *) vlistGetCellValue(vlistviewGetList(listview), 
                                             row, column);
    bounds->x += 20;
    vdrawRectShowCenterY(style->name, bounds);
}


/* * * * *     Description item support functions    * * * * */

/*
 * _writeDrawDescriptionBorder
 */
void _writeDrawDescriptionBorder(
    vtextitem		*textitem,
    vrect               *border
    )
{
    vcolor              *foreground;

    if (vlaf3D())
        vdrawRectsHiliteStrokeInside(border, 1,
		 vdialogDetermineItemColor(vtextitemGetItem(textitem),
                                           vdrawCOLOR_SHADOW_BOTTOM),
		 vdialogDetermineItemColor(vtextitemGetItem(textitem),
                                           vdrawCOLOR_SHADOW_TOP));
    else {
	foreground = vdialogDetermineItemForeground(vtextitemGetItem(textitem));
	vdrawRectsHiliteStrokeInside(border, 1,
                                     foreground, foreground);
    }
}

/* * * * * * * * STYLE WINDOW COMMAND SPACE * * * * * * * * */

static int _writeIssueStyleCommand(
    writeStyleDoc      *data,
    int		        selector,
    vdict               *context
    )
{
    writeStyle		*scan;
    vstr		*title;

    switch (selector) {
	
    case comCLOSE_STYLE:
        writeDestroyStyleWindow(data);
	return(TRUE);

    case comAPPLY_STYLE:
	return(TRUE);

    case comNEW_STYLE:
	scan = writeStyleList;
	while (scan->next != NULL)
            scan = scan->next;
        
	title = vresourceGetStringAt(writeMessages, writeMSG_UNTITLED);
	title = vstrAppendScribed(title, 
			  vnumScribeInt(writeStyleWindow->untitledCount));

        scan->next 	  = writeCreateStyle();
        scan->next->name  = vnameInternGlobal(title);
        scan->next->style = vtextCreateGlobalStyle();
        scan->next->flags = writeSTYLE_GLOBAL;
        vtextInitStyle(scan->next->style);

	writeStyleCount++;
	writeStyleWindow->untitledCount++;

        writeLoadStyleWindow(NULL, FALSE);
	vstrDestroy(title);

	return(TRUE);

    case comEDIT_STYLE:
	return(TRUE);
    }

    return vclassSendSuper(defaultStyleClass,
			   vobjectISSUE_SELECTOR,
			   (data, selector, context));
}

static int _writeQueryStyleCommand(
    writeStyleDoc      *data,
    int		        selector,
    vdict               *context
    )
{
    switch (selector) {
	
    default:
        break;
    }

    return vclassSendSuper(defaultStyleClass,
			   vobjectQUERY_SELECTOR,
			   (data, selector, context));
}


/* * * * * *   STARTUP AND SHUTDOWN * * * * * */

/*
 * writeStyleStartup
 *
 * One-time setup of all style classes, commands, and more
 */
void writeStyleStartup()
{
    /*
     * Create the default style window class
     */

    defaultStyleClass = vclassSpawn(vdialogGetDefaultClass(),
				     sizeof(writeStyleDocClass));
	
    vclassSetNameScribed(defaultStyleClass,
                         vcharScribeLiteral("writeStyle"));
    vclassSetObjectSize(defaultStyleClass, sizeof(writeStyleDoc));

    vclassSet(defaultStyleClass,
              vobjectDESTROY,           _writeDestroyStyle);
    vclassSet(defaultStyleClass, 
              vobjectISSUE_SELECTOR,    _writeIssueStyleCommand);
    vclassSet(defaultStyleClass, 
              vobjectQUERY_SELECTOR,    _writeQueryStyleCommand);

    /*
     * Create the default description text item class
     */

    defaultDescriptionClass = vclassReproduce(vtextitemGetDefaultClass());

    vclassSetNameScribed(defaultDescriptionClass,
                         vcharScribeLiteral("writeDescription"));

    vclassSet(defaultDescriptionClass,
              vtextviewDRAW_BORDER,		_writeDrawDescriptionBorder);
}


/*
 * writeStyleShutdown
 */
void writeStyleShutdown()
{
    if (writeStylePool != NULL)
        vpoolDestroy(writeStylePool);
}


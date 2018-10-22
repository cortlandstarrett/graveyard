/* $Id: mark.c,v 1.2 1994/12/23 18:30:09 dimitri Exp $ */

/************************************************************

    mark.c
    C Source to xwrite

    (c) Copyright Visix Software Inc.
    All rights reserved

************************************************************/

#include "micwrite.h"

#if vdebugDEBUG
#define vdebugTAG "xwriteMark"
#endif

static vpool		*writeMarkerPool = NULL;
extern vtextClass	*defaultTextClass;

vconfirm		*writeUnmarkWindow = NULL;
vconfirm		*writeMarkWindow = NULL;


/* 
 * * * * * * * * * * * * * * THE MARK WINDOW * * * * * * * * * * * * * * *
 */

static int 	_writeCreateButton(vconfirm *, vevent *);


/*
 * writeCreateMarkWindow
 *
 * Create the Confirm window Mark
 */
void writeCreateMarkWindow(void)
{
    vdialog		*dialog;
    vtextitem		*markEntry;

    if (writeMarkWindow != NULL) {
        if (!vdialogIsOpen(vconfirmGetDialog(writeMarkWindow)))
            vdialogOpen(vconfirmGetDialog(writeMarkWindow));
	vwindowRaise((vwindow *) writeMarkWindow);

	markEntry = (vtextitem *) 
	    vdialogFindItem(vconfirmGetDialog(writeMarkWindow), vname_Text);
	vtextitemSelectAll(markEntry);

        return;
    }

    writeMarkWindow = (vconfirm *) 
	writeLoadDialog(vnameInternGlobalLiteral("Mark"));

    dialog = vconfirmGetDialog(writeMarkWindow);

    markEntry = (vtextitem *) vdialogFindItem(dialog, vname_Text);
    vdialogSetData(dialog, markEntry);
    vdialogMove(dialog, 200, 200);

    vconfirmSetOkTitleScribed(writeMarkWindow, 
			      vcharScribeLiteral("Mark"));
    vconfirmSetApplyHook(writeMarkWindow,
			  _writeCreateButton);

    vdialogSetDefFocus(dialog, vtextitemGetItem(markEntry));

    writeBuildWindowMenus();

    vdialogOpen(dialog);
}

/*
 * _writeCreateButton
 *
 * Handle creating a marker for the selection of the active document
 */
static int _writeCreateButton(
    vconfirm		*confirm,
    vevent		*event
    )
{
    vchar               markName[256];
    vtextSelection      *sel;
    vtextitem		*markEntry;

    if (writeDocumentList != NULL) {
        markEntry = (vtextitem *) vdialogGetData((vdialog *) writeMarkWindow);
        vtextitemGetText(markEntry, markName, 256);
	sel = vtextviewGetSelection(writeDocumentList->textItem);
        writeAddMarker(writeDocumentList, markName, 
                       vtextGetPosition(sel)->start, vtextGetPosition(sel)->end);
    }
    return(TRUE);
}

/* 
 * * * * * * * * * * * * * * THE UNMARK WINDOW * * * * * * * * * * * * * * *
 */
 

static int 	_writeRemoveButton(vconfirm *, vevent *);
static void 	_writeDrawUnmarkCell(vlistview *, int, int, int, vrect *);

static vlistview	*_listview;
static writeDocument    *_targetDocument = NULL;

void writeCreateUnmarkWindow(void)
{
    vdialog		*dialog;

    if (writeUnmarkWindow != NULL) {
        if (!vdialogIsOpen(vconfirmGetDialog(writeUnmarkWindow)))
            vdialogOpen(vconfirmGetDialog(writeUnmarkWindow));
	vwindowRaise((vwindow *) writeUnmarkWindow);
        return;
    }

    writeUnmarkWindow = (vconfirm *) 
	writeLoadDialog(vnameInternGlobalLiteral("Unmark"));

    dialog = vconfirmGetDialog(writeUnmarkWindow);

    vdialogMove(dialog, 200, 200);

    _listview = (vlistview *) 
        vdialogFindItem(dialog, vnameInternGlobalLiteral("ListView"));
    vlistviewSetList(_listview, vlistCreate());
    vlistviewSetCellContentProc(_listview, _writeDrawUnmarkCell);
    vdialogSetData(dialog, _listview);

    vconfirmSetOkTitleScribed(writeUnmarkWindow, 
                              vcharScribeLiteral("Removed"));
    vconfirmSetApplyHook(writeUnmarkWindow,
                         _writeRemoveButton);

    writeBuildWindowMenus();

    vdialogOpen(dialog);
}

/*
 * writeLoadUnmarkWindow
 *
 * Reload the unmark window list to dislay the list of markers for
 * the document data
 */
void writeLoadUnmarkWindow(
    writeDocument	*data,
    vbool               setTarget
    )
{
    int         i = 0;
    writeMarker *marker;

    if (_targetDocument == NULL || setTarget)
        _targetDocument = data;

    if (data == NULL || writeUnmarkWindow == NULL ||  
        data != _targetDocument)
        return;

    vconfirmSetData((vconfirm *) writeUnmarkWindow, data);
    
    marker = data->markList;

    while (marker != NULL) {

        vlistSetCellValue(vlistviewGetList(_listview), i, 0, marker);
	i++;
        marker = marker->next;
    }

    vlistSetRowCount(vlistviewGetList(_listview), i);
}

/*
 * _writeRemoveButton
 *
 * Handle creating a unmarker for the selection of the active document
 */
static int _writeRemoveButton(
    vconfirm		*confirm,
    vevent		*event
    )
{
    vlistIterator	iterator;
    
    vlistInitSelectionIterator(&iterator, vlistviewGetSelection(_listview));
    
    while (vlistNextIterator(&iterator)) {
    
	writeRemoveMarker((writeDocument *) vconfirmGetData(confirm),
			  (writeMarker *) vlistGetCellValue
			  (vlistviewGetList(_listview),
			  vlistGetIteratorRow(&iterator), 0));
    }
    
    vlistDestroyIterator(&iterator);
    
    return(TRUE);
}

/*
 * _writeDrawUnmarkCell
 *
 * Draw a unmark cell
 */
static void _writeDrawUnmarkCell(
    vlistview           *list,
    int                 row,
    int                 column,
    int                 selected,
    vrect               *bounds
    )
{
    vchar		*name;

    bounds->x += 5;
    name = ((writeMarker *) vlistGetCellValue(vlistviewGetList(list), 
					      row, column))->name;

    vdrawSizedRectShowCenterY(name, vcharLength(name), bounds);
}

/* * * * * * * * MARKING ROUTINE * * * * * * * * * * */

/*
 * writeAddMarker
 *
 * Create a marker fogr the current selection and add it to the
 * documents list of markers
 */
writeMarker *writeAddMarker(
    writeDocument	*data,
    vchar               *markerName,
    long                start,
    long                end
    )
{
    writeMarker   	*newMarker, *temp, *prev = NULL;
    
    newMarker = vpoolAlloc(writeMarkerPool);
    
    newMarker->name[31] = vcharNULL;
    (void) vcharCopyBounded(markerName, newMarker->name, 31);
    vtextInitTag(&newMarker->tag);
    vtextSetTagRange(&newMarker->tag, start, end);
    vtextSetTagName(&newMarker->tag, write_Marker);
    
    /*
     * Insert into the marker list in the order of location within
     * the document
     */

    temp = data->markList;
    while (temp != NULL) {
        if (start < vtextGetTagStart(&temp->tag))
            break;
        prev = temp;
        temp = temp->next;
    }
    
    if (prev == NULL) {
        newMarker->next = data->markList;
        data->markList  = newMarker;
    }
    else { 
        prev->next      = newMarker;
        newMarker->next = temp;
    }
    
    writeLoadUnmarkWindow(data, FALSE);

    vtextAddTag(vtextviewGetTextData(data->textItem), &newMarker->tag);

    writeAddMarkerMenu(data, newMarker);

    writeChangeDocumentState(data,
	vnameInternGlobalScribed(vcharScribeLiteral("Unmark")), vname_Enabled);

    return(newMarker);
}

/*
 * writeRemoveMarker
 *
 * Remove a marker from the documents list of markers
 */
void writeRemoveMarker(
    writeDocument	*data,
    writeMarker		*marker
    )
{
    vtextRemoveTag(vtextviewGetTextData(data->textItem), &marker->tag);
}

/*
 * writeRemoveAllMarkers
 */
void writeRemoveAllMarkers(
    writeDocument		*data
    )
{
    writeMarker         *marker, *scan;

    scan = data->markList;

    while (scan != NULL) {

        marker = scan;
        scan   = scan->next;
        
	vtextRemoveTag(vtextviewGetTextData(data->textItem), &marker->tag);
    }
}

/*
 * writeSelectMarker
 */
void writeSelectMarker(
    writeDocument       *data,
    writeMarker		*marker
    )
{
    vtextSelectTag(vtextviewGetTextData(data->textItem),
                   vtextviewGetSelection(data->textItem),
                   &marker->tag);
    vtextviewScrollToStart(data->textItem, vtextviewSTS_HORIZONTAL |
                           vtextviewSTS_VERTICAL);
}

/*
 * writeStoreMarkers
 *
 * Save all non-function markers in a resource 
 */
void writeStoreMarkers(
    writeDocument	*data,
    vresource		res
    )
{
    writeMarker        *scan;
    int			count = 0, i;
    vresource		dictRes, entryRes;

    scan = data->markList;

    /* Count the markers */

    while (scan != NULL) {
	count++;
	scan = scan->next;
    }

    if (count == 0) {
	vresourceRemoveIfExists(res, vnameInternGlobalLiteral("Markers"));
	return;
    }

    dictRes = vresourceCreateArray(res, 
				   vnameInternGlobalLiteral("Markers"),
				   vresourceDICT, count);
    scan = data->markList;

    for (i=0; i<count; i++) {

	entryRes = vresourceCreateAt(dictRes, i, vresourceDICT);

	vresourceSetString(entryRes, vname_Name, scan->name);
	vresourceSetInteger(entryRes, vtext_Start,
			    vtextGetTagStart(&scan->tag));
	vresourceSetInteger(entryRes, vtext_End,
			    vtextGetTagEnd(&scan->tag));

	scan = scan->next;
    }
}

/*
 * writeLoadMarkers
 *
 * Load stored markers
 */
void writeLoadMarkers(
    writeDocument	*data,
    vresource		res
    )
{
    vresource		dictRes, entryRes;
    int			i, count;
    vstr		*str;
    int			start, end;

    if (!vresourceTestGet(res, vnameInternGlobalLiteral("Markers"), &dictRes))
	return;

    count = vresourceCountComponents(dictRes);

    for (i=0; i<count; i++) {

	entryRes = vresourceGetAt(dictRes, i);

	str   = vresourceGetString(entryRes, vname_Name);
	start = vresourceGetInteger(entryRes, vtext_Start);
	end   = vresourceGetInteger(entryRes, vtext_End);

	writeAddMarker(data, str, start, end);

	vstrDestroy(str);
    }
}

/* * *    REMOVE_TAG method for the default text class     * * */

/*
 * _writeRemoveTag
 *
 * vtextREMOVE_TAG method for the default text class.  We need to
 * check for markers being removed and remove them from the marker list
 */
void _writeRemoveTag(
    vtext		*editRec,
    vtextTag		*tag
    )
{
    writeDocument	*data;
    writeMarker         *prev = NULL, *scan, *marker;

    vclassSendSuper(defaultTextClass, vtextREMOVE_TAG, (editRec, tag));

    if (vtextGetTagName(tag) != write_Marker)
	return;

    data   = (writeDocument *) vtextGetData(editRec);
    marker = (writeMarker *) tag;

    scan = data->markList;

    while (scan != NULL) {

        if (scan == marker) {

            if (prev == NULL)
                data->markList = (writeMarker *) scan->next;
            else
                prev->next = scan->next;

	    writeRemoveMarkerMenu(data, scan);

	    writeLoadUnmarkWindow(data, FALSE);

	    if (data->markList == NULL)
                writeChangeDocumentState(data,
		      vnameInternGlobalScribed(vcharScribeLiteral("Unmark")),
                      vname_Disabled);

            vpoolFree(writeMarkerPool, (void *) scan);

            return;
        }

        prev = scan;
        scan = (writeMarker *) scan->next;
    }

    return;
}

/* * * * * *   STARTUP AND SHUTDOWN * * * * * */

/*
 * writeMarkStartup
 *
 * One-time setup of all mark classes, commands, and more
 */
void writeMarkStartup()
{
    writeMarkerPool = vpoolCreate(sizeof(writeMarker));
}


/*
 * writeMarkShutdown
 */
void writeMarkShutdown()
{
    vpoolDestroy(writeMarkerPool);
}


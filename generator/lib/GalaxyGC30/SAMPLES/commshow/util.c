/* $Id: util.c,v 1.4 1997/05/27 15:21:47 paul Exp $ */

#ifndef vportINCLUDED
#include <vport.h>
#endif

#ifndef vnameINCLUDED
#include vnameHEADER
#endif

#ifndef vclassINCLUDED
#include vclassHEADER
#endif

#ifndef vdialogINCLUDED
#include vdialogHEADER
#endif

#ifndef vcontainerINCLUDED
#include vcontainerHEADER
#endif

#ifndef vtextitemINCLUDED
#include vtextitemHEADER
#endif

#ifndef vnumINCLUDED
#include vnumHEADER
#endif

#ifndef _commtestCommshowINCLUDED
#include "commshow.h"
#endif

#ifndef _commtestUtilINCLUDED
#include "util.h"
#endif

static vtextClass *_getCommtestTextDataClass(void);
static vtextClass *_commtestTextDataClass=NULL;

static int  _commtestTextItemHandleKeyDown(vtextitem *textitem, vevent *event);
/* static void _commtestTextItemUnfocus(vtextitem *textitem); */
static vtext *_commtestLimitedTextItemCreateTextData(vtextitem *textitem);
static void _commtestLimitedTextItemLoadInit(vtextitem *textitem, 
					     vresource resource);
static void _commtestLimitedTextItemInsert(vtext *text, 
					   vtextSelection *selection,
					   const vchar *s, long len);

/*************************************************************************/
vdialogItem *
_utilFindItem(vdialog *dialog, const vname *tag)
{
    int i, count;
    vdialogItem *item;

    count = vdialogGetItemCount(dialog);

    for (i=0; i<count; i++)
    {
	item = vdialogGetItemAt(dialog, i);
	if (vobjectGetTag(vdialogGetItemObject(item)) == tag)
	    return item;
	else
	    if (vclassIsKindOf(vdialogGetItemClass(item),
			       vcontainerGetDefaultClass()))
		if ((item = _utilFindContainerItem((vcontainer *)item, tag)) 
		    != NULL)
		    return item;
    }
    return NULL;
}


/*************************************************************************/
vdialogItem *
_utilFindContainerItem(vcontainer *container, const vname *tag)
{
    int i, count;
    vdialogItem *item;

    count = vcontainerGetItemCount(container);

    for (i=0; i<count; i++)
    {
	item = vcontainerGetItemAt(container, i);
	if (vobjectGetTag(vdialogGetItemObject(item)) == tag)
	    return item;
	else
	    if (vclassIsKindOf(vdialogGetItemClass(item),
			       vcontainerGetDefaultClass()))
		if ((item = _utilFindContainerItem((vcontainer *)item, tag)) 
		    != NULL)
		    return item;
    }
    return NULL;
}


/*************************************************************************/
void
_utilSetUpTextItemClasses()
{
    vtextitemClass *clas;

    clas = (vtextitemClass *) vclassReproduce(vtextitemGetDefaultClass());
    vclassSetName(clas, TAG("commtestTextItem"));
    vclassSet(clas, vdialogHANDLE_ITEM_KEY_DOWN, 
	      _commtestTextItemHandleKeyDown);
/*    vclassSet(clas, vdialogUNFOCUS_ITEM, 
	      _commtestTextItemUnfocus);
*/

    clas = (vtextitemClass *) vclassReproduce(clas);
    vclassSetName(clas, TAG("commtestLimitedTextItem"));
    vclassSet(clas, vobjectLOAD_INIT,
	      _commtestLimitedTextItemLoadInit);
    vclassSet(clas, vtextitemCREATE_TEXT_DATA,
	      _commtestLimitedTextItemCreateTextData);
}

/*************************************************************************/
static vtextClass *
_getCommtestTextDataClass()
{
    if (_commtestTextDataClass == NULL)
    {
	_commtestTextDataClass = 
	    vclassReproduce (vtextitemGetDefaultTextDataClass());
	vclassSetNameScribed(_commtestTextDataClass, 
			     vcharScribeLiteral("_commtestTextDataClass"));
	vclassSet (_commtestTextDataClass, vtextINSERT, 
		   _commtestLimitedTextItemInsert);
    }
    return _commtestTextDataClass;
}

/*************************************************************************/
static vtext *
_commtestLimitedTextItemCreateTextData(vtextitem *textitem)
{
    return (vtextCreateOfClass(_getCommtestTextDataClass()));
}

/*************************************************************************/
static void
_commtestLimitedTextItemInsert(vtext *text, vtextSelection *selection,
			       const vchar *s, long len)
{

    int selectionLen, textlen;

    /* we need to do selection length calculations because the new text
     * is added _before_ the old selection's text is nuked. */
    selectionLen = vtextEndPos(selection) - vtextStartPos(selection);
    textlen = vtextLength(text);

    len = vMIN(SMALL_MESSAGE_SIZE - (textlen - selectionLen), len);

    if (len > 0) 
	vclassSendSuper(_getCommtestTextDataClass(), vtextINSERT, 
			(text, selection, s, len));
}

/*************************************************************************/
static void 
_commtestLimitedTextItemLoadInit(vtextitem *textitem, vresource resource)
{
    vtext	*oldText, *newText;

    vclassSendSuper(vtextitemGetClass(textitem), vobjectLOAD_INIT,
		    (textitem, resource));

    oldText = vtextitemGetTextData(textitem);
    newText = _commtestLimitedTextItemCreateTextData(textitem);

    /* get the previous contents, rulers, etc... */

    vtextCopy (oldText, newText); 

    vtextviewSetTextData((vtextview *)textitem, newText);

    /* work around a textitem bug in Galaxy 1.2.  
     * The selection in the textitem isn't getting recrated off of the 
     * new text item.  When oldText gets destroyed, it takes this textitem's
     * selection down with it.  Manually create our own selection.
     */
    vtextviewSetSelection((vtextview *)textitem,
			  vtextCreateSelection(newText));

    vtextDestroy (oldText);
}


/*************************************************************************/
static int  
_commtestTextItemHandleKeyDown(vtextitem *textitem, vevent *event)
{
    vobjectAttributed  *object;
    vkey key = vkeyGetStrokeKey(veventGetKeyStroke(event));

    if ((key == vkeyRETURN) || (key == vkeyENTER))
    {
	object = vdialogGetItemObject(vtextitemGetItem(textitem));
	vobjectDispatchCommand(object, vobjectGetTag(object), event);
    }

    /*
     * can't do super because of the way that I subclassed the limited
     * textitem (infinite loop if I did)
     */
    return vclassSend(vtextitemGetDefaultClass(),
		      vdialogHANDLE_ITEM_KEY_DOWN, 
		      (textitem, event));
}

/*************************************************************************/
/*
static void
_commtestTextItemUnfocus(vtextitem *textitem)
{
    vobjectAttributed  *object;

    object = vdialogGetItemObject(vtextitemGetItem(textitem));
    vobjectDispatchCommand(object, vobjectGetTag(object), NULL);

    vclassSendSuper(vtextitemGetClass(textitem), vdialogUNFOCUS_ITEM,
		    (textitem));
    return;
}
*/

/*************************************************************************/
void
_utilSetTextAsScribe(vtextitem *textitem, vscribe *scribe)
{
    vtext *text;
    vtextSelection *selection;
    vstr *str;
    int len;

    len = vscribeGetLength(scribe);
    str = vstrCloneScribed(scribe);
    text = vtextitemGetTextData(textitem);
    selection = vtextCreateSelection(text);
    vtextSelectRange(text, selection, 0, vtextLength(text));
    vtextInsert(text, selection, str, len);
    vstrDestroy(str);
    vtextDestroySelection(text, selection);
}

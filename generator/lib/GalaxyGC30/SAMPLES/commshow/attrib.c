/* $Id: attrib.c,v 1.9 1997/05/27 15:21:47 paul Exp $ */

#ifndef  vportINCLUDED
#include <vport.h>
#endif

#ifndef  vstdlibINCLUDED
#include vstdlibHEADER
#endif

#ifndef  vdialogINCLUDED
#include vdialogHEADER
#endif

#ifndef  vcontainerINCLUDED
#include vcontainerHEADER
#endif

#ifndef  vbuttonINCLUDED
#include vbuttonHEADER
#endif

#ifndef  vcommandINCLUDED
#include vcommandHEADER
#endif

#ifndef  vcontrolINCLUDED
#include vcontrolHEADER
#endif

#ifndef  vtextitemINCLUDED
#include vtextitemHEADER
#endif

#ifndef  vtimestampINCLUDED
#include vtimestampHEADER
#endif

#ifndef  vnumINCLUDED
#include vnumHEADER
#endif

#ifndef  vcommINCLUDED
#include vcommHEADER
#endif

#ifndef  _commtestAttribINCLUDED
#include "attrib.h"
#endif

#ifndef  _commtestCommshowINCLUDED
#include "commshow.h"
#endif

#ifndef  _commtestUtilINCLUDED
#include "util.h"
#endif

static int _attribBooleanFromToggle(vcommandFunction *command, vdict *context);
static int _attribScribeFromText(vcommandFunction *command, vdict *context);
static int _attribScalarFromText(vcommandFunction *command, vdict *context);
static int _attribTimestampFromText(vcommandFunction *command, vdict *context);
static int _attribQuery(vcommandFunction *command, vdict *context);

static int _locatorBooleanFromToggle(vcommandFunction *command,vdict *context);
static int _locatorScribeFromText(vcommandFunction *command, vdict *context);
static int _locatorScalarFromText(vcommandFunction *command, vdict *context);
static int _locatorULongFromText(vcommandFunction *command, vdict *context);
static int _locatorQuery(vcommandFunction *command, vdict *context);
static int _locatorClear(vcommandFunction *command, vdict *context);

static void _attribBooleanSetToggle(vdialog *dialog, const vname *name);
static void _attribScalarSetText(vdialog *dialog, const vname *name);
static void _attribScribeSetText(vdialog *dialog, const vname *name);
static void _attribTimestampSetText(vdialog *dialog, const vname *name);
static void _attribScalarSetLabel(vdialog *dialog, const vname *name);
static void _attribScalarSetStateLabel(vdialog *dialog, const vname *name);
static void _attribScribeSetLabel(vdialog *dialog, const vname *name);

static void _locatorBooleanSetToggle(vdialog *dialog, const vname *n, int sel);
static void _locatorScalarSetText(vdialog *dialog, const vname *n, int sel);
static void _locatorScribeSetText(vdialog *dialog, const vname *n, int sel);
static void _locatorScalarSetLabel(vdialog *dialog, const vname *n, int sel);
static void _locatorScribeSetLabel(vdialog *dialog, const vname *n, int sel);
static void _locatorULongSetText(vdialog *dialog, const vname *n, int sel);

/*
 * these two are pretty specialized for IP locators... oh well
 */
static void _locatorIPAddressesSetLabel(vdialog *d, const vname *n, int sel);
static void _locatorIPAddressCountSetLabel(vdialog *d, const vname *n, int sl);

/*
 * setting attributes on vcommBase
 */
static vcommandFunctionTemplate attribCommands[] = {
    {"Commands",             _attribBooleanFromToggle,  NULL},
    {"Synchronous",          _attribBooleanFromToggle,  NULL},
    {"Notification",         _attribBooleanFromToggle,  NULL},
    {"Reuseaddr",            _attribBooleanFromToggle,  NULL},
    {"Dontroute",            _attribBooleanFromToggle,  NULL},
    {"Loopback",             _attribBooleanFromToggle,  NULL},
    {"SendBufferSize",       _attribScalarFromText,     NULL},
    {"ReceiveBufferSize",    _attribScalarFromText,     NULL},
    {"SendLowWater",         _attribScalarFromText,     NULL},
    {"ReceiveLowWater",      _attribScalarFromText,     NULL},
    {"SendTimeout",          _attribTimestampFromText,  NULL},
    {"ReceiveTimeout",       _attribTimestampFromText,  NULL},
    {"Keepalive",            _attribBooleanFromToggle,  NULL},
    {"Linger",               _attribScalarFromText,     NULL},
    {"OobInline",            _attribBooleanFromToggle,  NULL},
    {"Broadcast",            _attribBooleanFromToggle,  NULL},
    {"EnableTimeout",        _attribTimestampFromText,  NULL},
    {"QueryAttributes",      _attribQuery,              NULL}
};

/*
 * setting attributes on vcommLocator
 */
static vcommandFunctionTemplate locatorCommands[] = {
    {"URL",                    _locatorScribeFromText,  NULL},
    {"Port",                   _locatorScalarFromText,  NULL},
    {"Server",                 _locatorScribeFromText,  NULL},
    {"Internet",               _locatorScribeFromText,  NULL},
    {"Number",                 _locatorULongFromText,  NULL},
    {"Hostname",               _locatorScribeFromText,  NULL},
    {"Key",                    _locatorScribeFromText,  NULL},
    {"QueryLocatorAttributes", _locatorQuery,           NULL},
    {"ClearLocatorAttributes", _locatorClear,           NULL}
};

/*
 * getting attributes from vcommBase and vcommLocator objects for each 
 * transport
 */
static _commtestAttributes _UDPAttribQueries[] = {
    {"Commands",             _attribBooleanSetToggle},
    {"State",                _attribScalarSetStateLabel},
    {"Synchronous",          _attribBooleanSetToggle},
    {"Notification",         _attribBooleanSetToggle},
    {"Descriptor",           _attribScalarSetLabel},
    {"Available",            _attribScalarSetLabel},
    {"Reuseaddr",            _attribBooleanSetToggle},
    {"Dontroute",            _attribBooleanSetToggle},
    {"Loopback",             _attribBooleanSetToggle},
    {"Broadcast",            _attribBooleanSetToggle}
};

static _commtestAttributes _TCPAttribQueries[] = {
    {"Commands",             _attribBooleanSetToggle},
    {"State",                _attribScalarSetStateLabel},
    {"Synchronous",          _attribBooleanSetToggle},
    {"Notification",         _attribBooleanSetToggle},
    {"Descriptor",           _attribScalarSetLabel},
    {"Available",            _attribScalarSetLabel},
    {"Reuseaddr",            _attribBooleanSetToggle},
    {"Dontroute",            _attribBooleanSetToggle},
    {"Loopback",             _attribBooleanSetToggle},
    {"SendBufferSize",       _attribScalarSetText},
    {"ReceiveBufferSize",    _attribScalarSetText},
    {"SendLowWater",         _attribScalarSetText},
    {"ReceiveLowWater",      _attribScalarSetText},
    {"SendTimeout",          _attribTimestampSetText},
    {"ReceiveTimeout",       _attribTimestampSetText},
    {"Keepalive",            _attribBooleanSetToggle},
    {"Linger",               _attribScalarSetText},
    {"OobInline",            _attribBooleanSetToggle}
};

static _commtestLocatorAttributes _IPLocatorQueries[] = {
    {"URL",                  _locatorScribeSetText},
    {"Port",                 _locatorScalarSetText},
    {"Server",               _locatorScribeSetText},
    {"Internet",             _locatorScribeSetText},
    {"Number",               _locatorULongSetText},
    {"Hostname",             _locatorScribeSetText},
    {"LocalAddresses",       _locatorIPAddressesSetLabel},
    {"LocalAddressCount",    _locatorIPAddressCountSetLabel}
};

static _commtestAttributes _MailboxAttribQueries[] = {
    {"Commands",             _attribBooleanSetToggle},
    {"State",                _attribScalarSetStateLabel},
    {"Synchronous",          _attribBooleanSetToggle},
    {"Notification",         _attribBooleanSetToggle},
    {"Descriptor",           _attribScalarSetLabel},
    {"Available",            _attribScalarSetLabel}
};

static _commtestAttributes _PipeAttribQueries[] = {
    {"Commands",             _attribBooleanSetToggle},
    {"State",                _attribScalarSetStateLabel},
    {"Synchronous",          _attribBooleanSetToggle},
    {"Notification",         _attribBooleanSetToggle},
    {"Descriptor",           _attribScalarSetLabel},
    {"Available",            _attribScalarSetLabel}
};

static _commtestLocatorAttributes _DomainLocatorQueries[] = {
    {"URL",                  _locatorScribeSetText},
    {"Hostname",             _locatorScribeSetText},
    {"Key",                  _locatorScribeSetText},
    {"Path",                 _locatorScribeSetLabel}
};

static _commtestAttributes _ShmAttribQueries[] = {
    {"Commands",             _attribBooleanSetToggle},
    {"State",                _attribScalarSetStateLabel},
    {"Synchronous",          _attribBooleanSetToggle},
    {"Notification",         _attribBooleanSetToggle},
    {"Available",            _attribScalarSetLabel},
    {"SharedMemoryID",       _attribScalarSetLabel},
    {"SemaphoreID",          _attribScalarSetLabel},
    {"SendBufferSize",       _attribScalarSetText},
    {"ReceiveBufferSize",    _attribScalarSetText},
    {"SendLowWater",         _attribScalarSetText},
    {"ReceiveLowWater",      _attribScalarSetText}
};

static _commtestLocatorAttributes _ShmLocatorQueries[] = {
    {"URL",                  _locatorScribeSetText},
    {"Key",                  _locatorScribeSetText}
};

/*************************************************************************/
#if (vdebugDEBUG)
static void
_notFoundItem(const vname *name)
{
        fprintf(vdebugGetWarningStream(), "dialog item with name \"");
	vcharDump(name, vdebugGetWarningStream());
        fprintf(vdebugGetWarningStream(), "\" not found.\n");
}
#else
#define _notFoundItem(n) ((void)0)
#endif

/*************************************************************************/
void 
_attribSetupCommandSpace(vdialog *dialog)
{
    vcommandSpace       *space;
    vdict               *cmdDict;

    space = vwindowGetSpace(vdialogGetWindow(dialog));

    cmdDict = vcommandCreateDictOfClassFunctionTemplates(
	       vcommandGetDefaultFunctionClass(),
               attribCommands,
               (size_t) sizeof(attribCommands) / sizeof(attribCommands[0]));
    vcommandAddSpaceDictOwned(space, vname_Command, cmdDict);

    cmdDict = vcommandCreateDictOfClassFunctionTemplates(
	       vcommandGetDefaultFunctionClass(),
               locatorCommands,
               (size_t) sizeof(locatorCommands) / sizeof(locatorCommands[0]));
    vcommandAddSpaceDictOwned(space, vname_Command, cmdDict);
}


/*************************************************************************/
static int 
_attribBooleanFromToggle(vcommandFunction *command, vdict *context)
{
    vcontrol *control;
    vdialog  *dialog;
    vbool     volatile status;

    control = (vcontrol *) (vdictLoad(context, vname_Operator));
    dialog  = (vdialog *)  (vdictLoad(context, vname_Dialog));

    status = vFALSE;
    vexWITH_HANDLING
    {
	if (vcontrolGetValue(control))
	    vcommSetBaseAttribute((vcommBase *) vdialogGetData(dialog),
		vobjectGetTag(vcontrolGetObject(control)), vname_True);
	else
	    vcommSetBaseAttribute((vcommBase *) vdialogGetData(dialog),
		vobjectGetTag(vcontrolGetObject(control)), vname_False);
	status = vTRUE;
    }
    vexON_EXCEPTION
    {
	vexDumpChain(vdebugGetWarningStream());
    }
    vexEND_HANDLING;

    if (status)
	vdialogSetItemForeground(vcontrolGetItem(control), _commtestGreen);
    return TRUE;
}

/*************************************************************************/
static int
_attribScribeFromText(vcommandFunction *command, vdict *context)
{
    vtextitem *textitem;
    vdialog   *dialog;
    vbool     volatile status;

    textitem = (vtextitem *) (vdictLoad(context, vname_Operator));
    dialog   = (vdialog *)   (vdictLoad(context, vname_Dialog));

    status = vFALSE;
    vexWITH_HANDLING
    {
	vcommSetBaseAttributeScribed((vcommBase *) vdialogGetData(dialog),
	    vobjectGetTag(vdialogGetItemObject(vtextitemGetItem(textitem))),
				     vtextitemGetTextScribed(textitem));
	status = vTRUE;
    }
    vexON_EXCEPTION
    {
	vexDumpChain(vdebugGetWarningStream());
    }
    vexEND_HANDLING;

    if (status)
	vdialogSetItemForeground(vtextitemGetItem(textitem), _commtestGreen);

    return TRUE;
}

/*************************************************************************/
static int
_attribScalarFromText(vcommandFunction *command, vdict *context)
{
    vtextitem * volatile textitem;
    vdialog   * volatile dialog;
    vbool       volatile status;
    int                  value;

    textitem = (vtextitem *) (vdictLoad(context, vname_Operator));
    dialog   = (vdialog *)   (vdictLoad(context, vname_Dialog));

    status = vFALSE;
    vexWITH_HANDLING
    {
	value = vtextitemGetTextAsInt(textitem);
	status = vTRUE;
    }
    vexON_EXCEPTION
    {
	vdebugMWarn(("value ignored, not integer\n"));
    }
    vexEND_HANDLING;

    if (!status)
	return TRUE;

    status = vFALSE;
    vexWITH_HANDLING
    {
	vcommSetBaseAttributeScalar((vcommBase *) vdialogGetData(dialog),
             vobjectGetTag(vdialogGetItemObject(vtextitemGetItem(textitem))),
				    value);
	status = vTRUE;
    }
    vexON_EXCEPTION
    {
	vexDumpChain(vdebugGetWarningStream());
    }
    vexEND_HANDLING;

    if (status)
	vdialogSetItemForeground(vtextitemGetItem(textitem), _commtestGreen);

    return TRUE;
}


/*************************************************************************/
static int
_attribTimestampFromText(vcommandFunction *command, vdict *context)
{
    vtextitem         *textitem;
    vdialog           *dialog;
    vcommBase         *base;
    vbool     volatile status;
    int                value;
    vtimestamp         timestamp;

    textitem = (vtextitem *) (vdictLoad(context, vname_Operator));
    dialog   = (vdialog *)   (vdictLoad(context, vname_Dialog));
    base     = (vcommBase *) vdialogGetData(dialog);

    status = vFALSE;
    vexWITH_HANDLING
    {
	value = vtextitemGetTextAsInt(textitem);
	status = vTRUE;
    }
    vexON_EXCEPTION
    {
	vdebugMWarn(("value ignored, not integer\n"));
    }
    vexEND_HANDLING;

    if (!status)
	return TRUE;

    timestamp = vtimestampMake(value, 0);
    status = vFALSE;
    vexWITH_HANDLING
    {
	vcommSetBaseAttribute(base,
               vobjectGetTag(vdialogGetItemObject(vtextitemGetItem(textitem))),
			      (void *) &timestamp);
	status = vTRUE;
    }
    vexON_EXCEPTION
    {
	vexDumpChain(vdebugGetWarningStream());
    }
    vexEND_HANDLING;

    if (status)
	vdialogSetItemForeground(vtextitemGetItem(textitem), _commtestGreen);

    return TRUE;
}


/*************************************************************************/
static int
_locatorBooleanFromToggle(vcommandFunction *command, vdict *context)
{
    vdebugMWarn(("_locatorBooleanFromToggle - not implemented\n"));
    return TRUE;
}

/*************************************************************************/
static int
_locatorScribeFromText(vcommandFunction *command, vdict *context)
{
    vtextitem          *textitem;
    vdialog            *dialog;
    vobjectAttributed  *object;
    vcommLocator       *locator; 
    _commtestData      *data;
    vbool     volatile  status;

    textitem = (vtextitem *) (vdictLoad(context, vname_Operator));
    dialog   = (vdialog *)   (vdictLoad(context, vname_Dialog));
    object   = vdialogGetItemObject(vtextitemGetItem(textitem));

    /*
     * find out if this a local or remote locator attribute
     */

    if (vobjectGetTag(vobjectGetParent(object)) == TAG("LocalLocator"))
	locator = vcommGetBaseLocator((vcommBase *) vdialogGetData(dialog));
    else
    {
	data = (_commtestData *) 
	    vcommGetBaseData((vcommBase *) vdialogGetData(dialog));
        locator = data->remote_locator;
    }

    status = vFALSE;
    vexWITH_HANDLING
    {
	vcommSetLocatorAttributeScribed(locator, vobjectGetTag(object),
					vtextitemGetTextScribed(textitem));
	status = vTRUE;
    }
    vexON_EXCEPTION
    {
	vexDumpChain(vdebugGetWarningStream());
    }
    vexEND_HANDLING;

    if (status)
	vdialogSetItemForeground(vtextitemGetItem(textitem), _commtestGreen);

    return TRUE;
}

/*************************************************************************/
static int
_locatorScalarFromText(vcommandFunction *command, vdict *context)
{
    vtextitem           *textitem;
    vdialog             *dialog;
    int                  value;
    vobject             *object;
    vcommLocator        *locator; 
    _commtestData       *data;
    vbool     volatile   status;

    textitem = (vtextitem *) (vdictLoad(context, vname_Operator));
    dialog   = (vdialog *)   (vdictLoad(context, vname_Dialog));
    object   = vdialogGetItemObject(vtextitemGetItem(textitem));

    status = vFALSE;
    vexWITH_HANDLING
    {
	value = vtextitemGetTextAsInt(textitem);
	status = vTRUE;
    }
    vexON_EXCEPTION
    {
	vdebugMWarn(("value ignored, not integer\n"));
    }
    vexEND_HANDLING;

    if (!status)
	return TRUE;

    /*
     * find out if this a local or remote locator attribute
     */

    if (vobjectGetTag(vobjectGetParent(object)) == TAG("LocalLocator"))
	locator = vcommGetBaseLocator((vcommBase *) vdialogGetData(dialog));
    else
    {
	data = (_commtestData *) 
	    vcommGetBaseData((vcommBase *) vdialogGetData(dialog));
        locator = data->remote_locator;
    }

    status = vFALSE;
    vexWITH_HANDLING
    {
	vcommSetLocatorAttributeScalar(locator, vobjectGetTag(object), value);
	status = vTRUE;
    }
    vexON_EXCEPTION
    {
	vexDumpChain(vdebugGetWarningStream());
    }
    vexEND_HANDLING;

    if (status)
	vdialogSetItemForeground(vtextitemGetItem(textitem), _commtestGreen);

    return TRUE;
}


/*************************************************************************/
static int
_locatorULongFromText(vcommandFunction *command, vdict *context)
{
    vtextitem           *textitem;
    vdialog             *dialog;
    unsigned long        value;
    vobject             *object;
    vcommLocator        *locator; 
    _commtestData       *data;
    vstr      volatile  *str;
    vbool     volatile   status;

    textitem = (vtextitem *) (vdictLoad(context, vname_Operator));
    dialog   = (vdialog *)   (vdictLoad(context, vname_Dialog));
    object   = vdialogGetItemObject(vtextitemGetItem(textitem));

    status = vFALSE;
    str = NULL;
    vexWITH_HANDLING
    {
	str = vtextitemGetTextAsString(textitem);
	value = vnumParseULong((vstr *)str, NULL);
	status = vTRUE;
    }
    vexON_EXCEPTION
    {
	vdebugMWarn(("value ignored, not integer\n"));
    }
    vexEND_HANDLING;

    if (str != NULL)
	vstrDestroy((vstr *)str);

    if (!status)
	return TRUE;

    /*
     * find out if this a local or remote locator attribute
     */

    if (vobjectGetTag(vobjectGetParent(object)) == TAG("LocalLocator"))
	locator = vcommGetBaseLocator((vcommBase *) vdialogGetData(dialog));
    else
    {
	data = (_commtestData *) 
	    vcommGetBaseData((vcommBase *) vdialogGetData(dialog));
        locator = data->remote_locator;
    }

    status = vFALSE;
    vexWITH_HANDLING
    {
	vcommSetLocatorAttributeScalar(locator, vobjectGetTag(object), value);
	status = vTRUE;
    }
    vexON_EXCEPTION
    {
	vexDumpChain(vdebugGetWarningStream());
    }
    vexEND_HANDLING;

    if (status)
	vdialogSetItemForeground(vtextitemGetItem(textitem), _commtestGreen);

    return TRUE;
}


/*************************************************************************/
static void 
_attribBooleanSetToggle(vdialog *dialog, const vname *name)
{
    vcontrol *control;
    const vname *newval, *oldval;
    control = (vcontrol *) _utilFindItem(dialog, name);

    oldval = (vcontrolGetValue(control))? vname_True : vname_False;
    newval = (const vname *) vcommGetBaseAttribute((vcommBase *) 
						   vdialogGetData(dialog), 
						   name);
    if (control != NULL)
    {
	if (oldval != newval)
	{
	    if (newval == vname_True)
		vcontrolSetValue(control, 1);
	    else
		vcontrolSetValue(control, 0);
	    vdialogSetItemForeground(vcontrolGetItem(control), 
			     _utilForeground(vcontrolGetItem(control)));
	}
    }
    else
	_notFoundItem(name);
}

/*************************************************************************/
static void 
_attribScalarSetText(vdialog *dialog, const vname *name)
{
    vtextitem  *   volatile textitem;
    int            volatile oldval, newval;

    textitem = (vtextitem *) _utilFindItem(dialog, name);

    if (textitem != NULL)
    {
	newval = vcommGetBaseAttributeScalar((vcommBase *) 
					     vdialogGetData(dialog), name);
	vexWITH_HANDLING
	{
	    oldval = vtextitemGetTextAsInt(textitem);
	}
	vexON_EXCEPTION
	{
	    oldval = !newval;
	}
	vexEND_HANDLING;

	if (oldval != newval)
	{
	    _utilSetTextAsScribe(textitem, vnumScribeInt(newval));
	    vdialogSetItemForeground(vtextitemGetItem(textitem), 
			     _utilForeground(vtextitemGetItem(textitem)));
	}
    }	
    else
	_notFoundItem(name);
}

/*************************************************************************/
static void 
_attribScribeSetText(vdialog *dialog, const vname *name)
{
    vtextitem  *textitem;
    vstr       *oldval, *newval;
    vcommBase  *base;
    base     = (vcommBase *) vdialogGetData(dialog);
    textitem = (vtextitem *) _utilFindItem(dialog, name);

    if (textitem != NULL)
    {
	oldval = vtextitemGetTextAsString(textitem);
	newval = vstrCloneScribed(vcommGetBaseAttributeScribed(base, name));

	if (oldval != NULL) /* can this be NULL? */
	{
	    if (vcharCompare(oldval, newval))
	    {
		_utilSetTextAsScribe(textitem, vstrScribe(newval));
		vdialogSetItemForeground(vtextitemGetItem(textitem), 
				  _utilForeground(vtextitemGetItem(textitem)));
	    }
	    else
		vstrDestroy(newval);
	    vstrDestroy(oldval);
        }
	else
	    _utilSetTextAsScribe(textitem, vstrScribe(newval));
    }
    else
	_notFoundItem(name);
}

/*************************************************************************/
static void 
_attribTimestampSetText(vdialog *dialog, const vname *name)
{
    vtextitem  *   volatile textitem;
    int            volatile oldval, newval;
    vtimestamp *   tptr;
    vcommBase  *   base;
    base     = (vcommBase *) vdialogGetData(dialog);
    textitem = (vtextitem *) _utilFindItem(dialog, name);

    if (textitem != NULL)
    {
	tptr = (vtimestamp *) vcommGetBaseAttribute(base, name);
	newval = vtimestampGetSeconds(*tptr);

	vexWITH_HANDLING
	{
	    oldval = vtextitemGetTextAsInt(textitem);
	}
	vexON_EXCEPTION
	{
	    oldval = !newval;
	}
	vexEND_HANDLING;

	if (oldval != newval)
	{
	    _utilSetTextAsScribe(textitem, vnumScribeInt(newval));
	    vdialogSetItemForeground(vtextitemGetItem(textitem), 
			     _utilForeground(vtextitemGetItem(textitem)));
	}
    }
    else
	_notFoundItem(name);
}

/*************************************************************************/
static void 
_attribScalarSetLabel(vdialog *dialog, const vname *name)
{
    vdialogItem *item;
    item = _utilFindItem(dialog, name);

    if (item != NULL)
	vdialogSetItemTitleScribed(item, vnumScribeInt(
           vcommGetBaseAttributeScalar((vcommBase *) vdialogGetData(dialog),
				      name)));
    else
	_notFoundItem(name);
}

/*************************************************************************/
static void 
_attribScalarSetStateLabel(vdialog *dialog, const vname *name)
{
    vdialogItem *item;
    item = _utilFindItem(dialog, name);

    if (item != NULL)
	switch(vcommGetBaseAttributeScalar(
               (vcommBase *) vdialogGetData(dialog), name))
	{
	    case vcommENABLED:
	    vdialogSetItemTitleScribed(item, SCRIBE("Enabled"));
	    break;
	    case vcommDISABLED:
	    vdialogSetItemTitleScribed(item, SCRIBE("Disabled"));
	    break;
	    case vcommENABLING:
	    vdialogSetItemTitleScribed(item, SCRIBE("Enabling"));
	    break;
	    default:
	    vdialogSetItemTitleScribed(item, SCRIBE("Unknown"));
	    break;
	}
    else
	_notFoundItem(name);
}

/*************************************************************************/
static void 
_attribScribeSetLabel(vdialog *dialog, const vname *name)
{
    vdialogItem *item;
    item = _utilFindItem(dialog, name);

    if (item != NULL)
	vdialogSetItemTitleScribed(item,
	  vcommGetBaseAttributeScribed((vcommBase *) vdialogGetData(dialog),
				       name));
    else
	_notFoundItem(name);
}


/*************************************************************************/
static void 
_locatorBooleanSetToggle(vdialog *dialog, const vname *name, int sel)
{
    _commtestData *data;
    vcontainer *container;
    vcontrol *control;
    const vname *oldval, *newval;

    data   = (_commtestData *) 
	vcommGetBaseData((vcommBase *) vdialogGetData(dialog));

    if (sel & _LOCAL_LOCATOR)
    {
	container = (vcontainer *) _utilFindItem(dialog, TAG("LocalLocator"));

	if (container == NULL)
	    control = NULL;
	else
	    control = (vcontrol *) _utilFindContainerItem(container, name);

	if (control != NULL)
	{
	    oldval = (vcontrolGetValue(control))? vname_True : vname_False;
	    newval = (const vname *) vcommGetLocatorAttribute(
	      vcommGetBaseLocator((vcommBase *) vdialogGetData(dialog)), name);
	    if (oldval != newval)
	    {
		if (newval == vname_True)
		    vcontrolSetValue(control, 1);
		else
		    vcontrolSetValue(control, 0);
		vdialogSetItemForeground(vcontrolGetItem(control), 
				_utilForeground(vcontrolGetItem(control)));
	    }
	    else if (sel & _CLEAR_LOCATOR)
		vdialogSetItemForeground(vcontrolGetItem(control), 
				 _utilForeground(vcontrolGetItem(control)));
	}
	else
	    _notFoundItem(name);
    }

    if (sel & _REMOTE_LOCATOR)
    {
	container = (vcontainer *) _utilFindItem(dialog, TAG("RemoteLocator"));
	
	if (container == NULL)
	    control = NULL;
	else
	    control = (vcontrol *) _utilFindContainerItem(container, name);
	
	if (control != NULL)
	{
	    oldval = (vcontrolGetValue(control))? vname_True : vname_False;
	    newval = (const vname *) 
		vcommGetLocatorAttribute(data->remote_locator, name);
	    if (oldval != newval)
	    {
		if (newval == vname_True)
		    vcontrolSetValue(control, 1);
		else
		    vcontrolSetValue(control, 0);
		vdialogSetItemForeground(vcontrolGetItem(control), 
				_utilForeground(vcontrolGetItem(control)));
	    }
	    else if (sel & _CLEAR_LOCATOR)
		vdialogSetItemForeground(vcontrolGetItem(control), 
				 _utilForeground(vcontrolGetItem(control)));
	}
	else
	    _notFoundItem(name);
    }
}

/*************************************************************************/
static void 
_locatorScalarSetText(vdialog *dialog, const vname *name, int sel)
{
    vtextitem     *   volatile textitem;
    int               volatile oldval, newval;
    _commtestData *   volatile data;
    vcontainer    *   volatile container;

    data   = (_commtestData *) 
	vcommGetBaseData((vcommBase *) vdialogGetData(dialog));

    if (sel & _LOCAL_LOCATOR)
    {
	container = (vcontainer *) _utilFindItem(dialog, TAG("LocalLocator"));
	
	if (container == NULL)
	    textitem = NULL;
	else
	    textitem = (vtextitem *) _utilFindContainerItem(container, name);
	
	if (textitem != NULL)
	{
	    newval = vcommGetLocatorAttributeScalar(
              vcommGetBaseLocator((vcommBase *) vdialogGetData(dialog)), name);
	    
	    vexWITH_HANDLING
	    {
		oldval = vtextitemGetTextAsInt(textitem);
	    }
	    vexON_EXCEPTION
	    {
		oldval = !newval;
	    }
	    vexEND_HANDLING;

	    if (oldval != newval)
	    {
		_utilSetTextAsScribe(textitem, vnumScribeInt(newval));
		vdialogSetItemForeground(vtextitemGetItem(textitem), 
				_utilForeground(vtextitemGetItem(textitem)));
	    }
	    else if (sel & _CLEAR_LOCATOR)
		vdialogSetItemForeground(vtextitemGetItem(textitem), 
				_utilForeground(vtextitemGetItem(textitem)));
	}	
	else
	    _notFoundItem(name);
    }

    if (sel & _REMOTE_LOCATOR)
    {
	container = (vcontainer *) _utilFindItem(dialog, TAG("RemoteLocator"));

	if (container == NULL)
	    textitem = NULL;
	else
	    textitem = (vtextitem *) _utilFindContainerItem(container, name);
	
	if (textitem != NULL)
	{
	    newval = vcommGetLocatorAttributeScalar(data->remote_locator, 
						    name);

	    vexWITH_HANDLING
	    {
		oldval = vtextitemGetTextAsInt(textitem);
	    }
	    vexON_EXCEPTION
	    {
		oldval = !newval;
	    }
	    vexEND_HANDLING;
	    
	    if (oldval != newval)
	    {
		_utilSetTextAsScribe(textitem, vnumScribeInt(newval));
		vdialogSetItemForeground(vtextitemGetItem(textitem), 
				 _utilForeground(vtextitemGetItem(textitem)));
	    }
	    else if (sel & _CLEAR_LOCATOR)
		vdialogSetItemForeground(vtextitemGetItem(textitem), 
				_utilForeground(vtextitemGetItem(textitem)));
	}	
	else
	    _notFoundItem(name);
    }
}

/*************************************************************************/
static void 
_locatorScribeSetText(vdialog *dialog, const vname *name, int sel)
{
    vtextitem     *   volatile textitem;
    vstr          *   volatile oldval, *newval;
    _commtestData *   volatile data;
    vcontainer    *   volatile container;

    data   = (_commtestData *) 
	vcommGetBaseData((vcommBase *) vdialogGetData(dialog));

    if (sel & _LOCAL_LOCATOR)
    {
	container = (vcontainer *) _utilFindItem(dialog, TAG("LocalLocator"));

	if (container == NULL)
	    textitem = NULL;
	else
	    textitem = (vtextitem *) _utilFindContainerItem(container, name);
	
	if (textitem != NULL)
	{
	    oldval = vtextitemGetTextAsString(textitem);
	    newval = vstrCloneScribed(vcommGetLocatorAttributeScribed(
             vcommGetBaseLocator((vcommBase *) vdialogGetData(dialog)), name));

	    if (sel & _CLEAR_LOCATOR)
		vdialogSetItemForeground(vtextitemGetItem(textitem), 
				 _utilForeground(vtextitemGetItem(textitem)));

	    if (oldval != NULL) /* can this be NULL? */
	    {
		if (vcharCompare(oldval, newval))
		{
		    _utilSetTextAsScribe(textitem, vstrScribe(newval));
		    vdialogSetItemForeground(vtextitemGetItem(textitem), 
			     _utilForeground(vtextitemGetItem(textitem)));
		}
		else
		    vstrDestroy(newval);

		vstrDestroy(oldval);
	    }
	    else
		_utilSetTextAsScribe(textitem, vstrScribe(newval));
	}
	else
	    _notFoundItem(name);
    }

    if (sel & _REMOTE_LOCATOR)
    {
	container = (vcontainer *) _utilFindItem(dialog, TAG("RemoteLocator"));
	
	if (container == NULL)
	    textitem = NULL;
	else
	    textitem = (vtextitem *) _utilFindContainerItem(container, name);
	
	if (textitem != NULL)
	{
	    oldval = vtextitemGetTextAsString(textitem);
	    newval = vstrCloneScribed(vcommGetLocatorAttributeScribed(
					      data->remote_locator, name));

	    if (sel & _CLEAR_LOCATOR)
		vdialogSetItemForeground(vtextitemGetItem(textitem), 
				 _utilForeground(vtextitemGetItem(textitem)));
	    
	    if (oldval != NULL) /* can this be NULL? */
	    {
		if (vcharCompare(oldval, newval))
		{
		    _utilSetTextAsScribe(textitem, vstrScribe(newval));
		    vdialogSetItemForeground(vtextitemGetItem(textitem), 
			     _utilForeground(vtextitemGetItem(textitem)));
		}
		else
		    vstrDestroy(newval);

		vstrDestroy(oldval);
	    }
	    else
		_utilSetTextAsScribe(textitem, vstrScribe(newval));
	}
	else
	    _notFoundItem(name);
    }
}

/*************************************************************************/
static void 
_locatorScalarSetLabel(vdialog *dialog, const vname *name, int sel)
{
    vcontainer *container;
    vdialogItem *item;
    _commtestData *data = (_commtestData *) 
	vcommGetBaseData((vcommBase *) vdialogGetData(dialog));

    if (sel & _LOCAL_LOCATOR)
    {
	container = (vcontainer *) _utilFindItem(dialog, TAG("LocalLocator"));
	
	if (container == NULL)
	    item = NULL;
	else
	    item = _utilFindContainerItem(container, name);
	
	if (item != NULL)
	    vdialogSetItemTitleScribed(item, 
			       vnumScribeInt(vcommGetLocatorAttributeScalar(
            vcommGetBaseLocator((vcommBase *) vdialogGetData(dialog)), name)));
	else
	    _notFoundItem(name);
    }
	
    if (sel & _REMOTE_LOCATOR)
    {
	container = (vcontainer *) _utilFindItem(dialog, TAG("RemoteLocator"));
	
	if (container == NULL)
	    item = NULL;
	else
	    item = _utilFindContainerItem(container, name);
	
	if (item != NULL)
	    vdialogSetItemTitleScribed(item, 
            vnumScribeInt(vcommGetLocatorAttributeScalar(data->remote_locator, 
							 name)));
	else
	    _notFoundItem(name);
    }
}

/*************************************************************************/
static void 
_locatorScribeSetLabel(vdialog *dialog, const vname *name, int sel)
{
    vcontainer *container;
    vdialogItem *item;
    _commtestData *data = (_commtestData *) 
	vcommGetBaseData((vcommBase *) vdialogGetData(dialog));

    if (sel & _LOCAL_LOCATOR)
    {
	container = (vcontainer *) _utilFindItem(dialog, TAG("LocalLocator"));
	
	if (container == NULL)
	    item = NULL;
	else
	    item = _utilFindContainerItem(container, name);
	
	if (item != NULL)
	    vdialogSetItemTitleScribed(item, vcommGetLocatorAttributeScribed(
	     vcommGetBaseLocator((vcommBase *) vdialogGetData(dialog)), name));
	else
	    _notFoundItem(name);
    }

    if (sel & _REMOTE_LOCATOR)
    {
	container = (vcontainer *) _utilFindItem(dialog, TAG("RemoteLocator"));

	if (container == NULL)
	    item = NULL;
	else
	    item = _utilFindContainerItem(container, name);
	
	if (item != NULL)
	    vdialogSetItemTitleScribed(item, vcommGetLocatorAttributeScribed(
				     data->remote_locator, name));
	else
	    _notFoundItem(name);
    }
}

/*************************************************************************/
static void 
_locatorULongSetText(vdialog *dialog, const vname *name, int sel)
{
    vtextitem     *   volatile textitem;
    unsigned long     volatile oldval, newval;
    _commtestData *   volatile data;
    vcontainer    *   volatile container;

    data   = (_commtestData *) 
	vcommGetBaseData((vcommBase *) vdialogGetData(dialog));

    if (sel & _LOCAL_LOCATOR)
    {
	container = (vcontainer *) _utilFindItem(dialog, TAG("LocalLocator"));
	
	if (container == NULL)
	    textitem = NULL;
	else
	    textitem = (vtextitem *) _utilFindContainerItem(container, name);
	
	if (textitem != NULL)
	{
	    newval = (unsigned long)vcommGetLocatorAttribute(
              vcommGetBaseLocator((vcommBase *) vdialogGetData(dialog)), name);
	    
	    vexWITH_HANDLING
	    {
		oldval = (unsigned long)vtextitemGetTextAsInt(textitem);
	    }
	    vexON_EXCEPTION
	    {
		oldval = !newval;
	    }
	    vexEND_HANDLING;

	    if (oldval != newval)
	    {
		_utilSetTextAsScribe(textitem, vnumScribeULong(newval));
		vdialogSetItemForeground(vtextitemGetItem(textitem), 
				_utilForeground(vtextitemGetItem(textitem)));
	    }
	    else if (sel & _CLEAR_LOCATOR)
		vdialogSetItemForeground(vtextitemGetItem(textitem), 
				_utilForeground(vtextitemGetItem(textitem)));
	}	
	else
	    _notFoundItem(name);
    }

    if (sel & _REMOTE_LOCATOR)
    {
	container = (vcontainer *) _utilFindItem(dialog, TAG("RemoteLocator"));

	if (container == NULL)
	    textitem = NULL;
	else
	    textitem = (vtextitem *) _utilFindContainerItem(container, name);
	
	if (textitem != NULL)
	{
	    newval = vcommGetLocatorAttributeScalar(data->remote_locator, 
						    name);

	    vexWITH_HANDLING
	    {
		oldval = vtextitemGetTextAsInt(textitem);
	    }
	    vexON_EXCEPTION
	    {
		oldval = !newval;
	    }
	    vexEND_HANDLING;
	    
	    if (oldval != newval)
	    {
		_utilSetTextAsScribe(textitem, vnumScribeULong(newval));
		vdialogSetItemForeground(vtextitemGetItem(textitem), 
				 _utilForeground(vtextitemGetItem(textitem)));
	    }
	    else if (sel & _CLEAR_LOCATOR)
		vdialogSetItemForeground(vtextitemGetItem(textitem), 
				_utilForeground(vtextitemGetItem(textitem)));
	}	
	else
	    _notFoundItem(name);
    }
}

/*************************************************************************/
static void
_setLocalAddresses(vdialogItem *item, vcommLocator *locator, 
		   const vname *name)
{
    unsigned long *addresses;
    int            i, naddrs;
    vscribe       *scribe;

    addresses = (unsigned long *)
	vcommGetLocatorAttribute(locator, vcomm_LocalAddresses);

    if (addresses != NULL)
    {
	naddrs = vcommGetLocatorAttributeScalar(locator, 
						vcomm_LocalAddressCount);
	scribe = vnumScribeULong(addresses[0]);
	for (i=1; i<naddrs; i++)
	{
	    scribe = vscribeConcatenate(
		scribe, vscribeScribeMulti(SCRIBE(", "), 
					   vnumScribeULong(addresses[i]), 
					   NULL));
	}
	vdialogSetItemTitleScribed(item, scribe);
    }
    else
    {
	vdialogSetItemTitleScribed(item, SCRIBE("<none>"));
    }
}

/*************************************************************************/
static void
_locatorIPAddressesSetLabel(vdialog *dialog, const vname *name, int sel)
{
    vdialogItem    *item;
    _commtestData  *data = (_commtestData *) 
	vcommGetBaseData((vcommBase *) vdialogGetData(dialog));

    item = _utilFindItem(dialog, name);

    if (item != NULL)
    {
	/*
	 * query both locators/update same UI twice for the heck of it
	 */
	if (sel & _LOCAL_LOCATOR)
	    _setLocalAddresses(item, vcommGetBaseLocator(
		(vcommBase *)vdialogGetData(dialog)), name);
	if (sel & _REMOTE_LOCATOR)
	    _setLocalAddresses(item, data->remote_locator, name);
    }
    else
	_notFoundItem(name);
}

/*************************************************************************/
static void
_locatorIPAddressCountSetLabel(vdialog *dialog, const vname *name, int sel)
{
    vdialogItem    *item;
    _commtestData  *data = (_commtestData *) 
	vcommGetBaseData((vcommBase *) vdialogGetData(dialog));

    item = _utilFindItem(dialog, name);

    if (item != NULL)
    {
	/*
	 * query both locators/update same UI twice for the heck of it
	 */
	if (sel & _LOCAL_LOCATOR)
	    vdialogSetItemTitleScribed(
		item, 
		vnumScribeInt(vcommGetLocatorAttributeScalar(
		    vcommGetBaseLocator(
			(vcommBase *)vdialogGetData(dialog)), name)));
	if (sel & _REMOTE_LOCATOR)
	    vdialogSetItemTitleScribed(
		item, 
		vnumScribeInt(vcommGetLocatorAttributeScalar(
		    data->remote_locator, name)));
    }
    else
	_notFoundItem(name);
}

/*************************************************************************/
static int 
_attribQuery(vcommandFunction *command, vdict *context)
{
    vdialog             *dialog;

    dialog = (vdialog *)   (vdictLoad(context, vname_Dialog));
    _attribUpdate(dialog);

    return TRUE;
}

/*************************************************************************/
void
_attribUpdate(vdialog *dialog)
{
    int                  i, num;
    _commtestAttributes *attribs;
    _commtestData       *data;

    data   = (_commtestData *) 
	vcommGetBaseData((vcommBase *) vdialogGetData(dialog));

    switch (data->transport)
    {
        case _UDPDatagram:
	num = sizeof(_UDPAttribQueries) / sizeof(_UDPAttribQueries[0]);
	attribs = _UDPAttribQueries;
	break;

	case _TCPStream:
	num = sizeof(_TCPAttribQueries) / sizeof(_TCPAttribQueries[0]);
	attribs = _TCPAttribQueries;
	break;

	case _PipeStream:
	num = sizeof(_PipeAttribQueries) / sizeof(_PipeAttribQueries[0]);
	attribs = _PipeAttribQueries;
	break;

	case _MailboxDatagram:
	num = sizeof(_MailboxAttribQueries) / sizeof(_MailboxAttribQueries[0]);
	attribs = _MailboxAttribQueries;
	break;

	case _ShmStream:
	num = sizeof(_ShmAttribQueries) / sizeof(_ShmAttribQueries[0]);
	attribs = _ShmAttribQueries;
	break;
    }

    for (i=0; i<num; i++)
	attribs[i].queryFunc(dialog, TAG(attribs[i].name));
}


/*************************************************************************/
static int 
_locatorQuery(vcommandFunction *command, vdict *context)
{
    vdialog             *dialog;

    dialog = (vdialog *)   (vdictLoad(context, vname_Dialog));
    _attribLocatorUpdate(dialog, _BOTH_LOCATOR);

    return TRUE;
}



/*************************************************************************/
static int 
_locatorClear(vcommandFunction *command, vdict *context)
{
    vdialog             *dialog;
    vbutton             *button;
    vobjectAttributed   *object;
    _commtestData       *data;

    dialog = (vdialog *) (vdictLoad(context, vname_Dialog));
    button = (vbutton *) (vdictLoad(context, vname_Operator));
    object   = vdialogGetItemObject(vbuttonGetItem(button));

    if (vobjectGetTag(vobjectGetParent(object)) == TAG("LocalLocator"))
    {
	vcommClearLocator(vcommGetBaseLocator((vcommBase *) 
					      vdialogGetData(dialog)));
	_attribLocatorUpdate(dialog, _LOCAL_LOCATOR | _CLEAR_LOCATOR);
    }
    else
    {
	data = (_commtestData *) 
	    vcommGetBaseData((vcommBase *) vdialogGetData(dialog));
	vcommClearLocator(data->remote_locator);
	_attribLocatorUpdate(dialog, _REMOTE_LOCATOR | _CLEAR_LOCATOR);
    }

    return TRUE;
}



/*************************************************************************/
void
_attribLocatorUpdate(vdialog *dialog, int sel)
{
    int                         i, num;
    _commtestLocatorAttributes *attribs;
    _commtestData              *data;

    data   = (_commtestData *) 
	vcommGetBaseData((vcommBase *) vdialogGetData(dialog));

    switch (data->transport)
    {
        case _TCPStream:
	case _UDPDatagram:
	num = sizeof(_IPLocatorQueries) / sizeof(_IPLocatorQueries[0]);
	attribs = _IPLocatorQueries;
	break;

	case _PipeStream:
	case _MailboxDatagram:
	num = sizeof(_DomainLocatorQueries) / sizeof(_DomainLocatorQueries[0]);
	attribs = _DomainLocatorQueries;
	break;

	case _ShmStream:
	num = sizeof(_ShmLocatorQueries) / sizeof(_ShmLocatorQueries[0]);
	attribs = _ShmLocatorQueries;
	break;
    }

    for (i=0; i<num; i++)
	attribs[i].queryFunc(dialog, TAG(attribs[i].name), sel);
}

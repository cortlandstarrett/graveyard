/* $Id: notify.c,v 1.6 1997/04/18 21:34:42 paul Exp $ */

#ifndef  vportINCLUDED
#include <vport.h>
#endif

#ifndef  vdialogINCLUDED
#include vdialogHEADER
#endif

#ifndef  vscribeINCLUDED
#include vscribeHEADER
#endif

#ifndef  vcommINCLUDED
#include vcommHEADER
#endif

#ifndef  _commtestCommshowINCLUDED
#include "commshow.h"
#endif

#ifndef  _commtestAttribINCLUDED
#include "attrib.h"
#endif

#ifndef  _commtestNotifyINCLUDED
#include "notify.h"
#endif

static void _notifyUpdateInterface(vcommBase *base, vcommEvent *event);

void
_notifyBase(vcommBase *base, vcommEvent *event)
{
    _notifyUpdateInterface(base, event);
    _attribLocatorUpdate(((_commtestData *) vcommGetBaseData(base))->dialog,
			 _BOTH_LOCATOR);
    _attribUpdate(((_commtestData *) vcommGetBaseData(base))->dialog);
}

static void
_notifyUpdateInterface(vcommBase *base, vcommEvent *event)
{
    _commtestData *data;
    vscribe *scribe;

    data = (_commtestData *) vcommGetBaseData(base);

    switch (vcommGetEventType(event)) 
    {
        case vcommENABLED:
	    _notifyUpdateState(base);
	    scribe = vcharScribeFormatScribed(SCRIBE("vcommENABLED - %d"),
					      data->count++);
        break;

        case vcommRECEIVE:
	    scribe = vcharScribeFormatScribed(SCRIBE("vcommRECEIVE - %d"),
					      data->count++);
	break;

        case vcommSEND:
	    scribe = vcharScribeFormatScribed(SCRIBE("vcommSEND - %d"),
					      data->count++);
	break;

        case vcommERROR:
	    _notifyUpdateState(base);
	    switch (vcommGetEventError(event))
	    {
		case vcommERROR_NONE:
		scribe = vcharScribeFormatScribed(
		    SCRIBE("vcommERROR_NONE - %d"), data->count++);
		break;
		case vcommERROR_TRANSPORT:
		scribe = vcharScribeFormatScribed(
		    SCRIBE("vcommERROR_TRANSPORT - %d"), data->count++);
		break;
		case vcommERROR_HALT:
		scribe = vcharScribeFormatScribed(
		    SCRIBE("vcommERROR_HALT - %d"), data->count++);
		break;
		case vcommERROR_ADDRINUSE:
		scribe = vcharScribeFormatScribed(
		    SCRIBE("vcommERROR_ADDRINUSE - %d"), data->count++);
		break;
		case vcommERROR_CONNECTION:
		scribe = vcharScribeFormatScribed(
		    SCRIBE("vcommERROR_CONNECTION - %d"), data->count++);
		break;
		case vcommERROR_STATE:
		scribe = vcharScribeFormatScribed(
		    SCRIBE("vcommERROR_STATE - %d"), data->count++);
		break;
		default:
		scribe = vcharScribeFormatScribed(
		    SCRIBE("vcommERROR type? - %d"), data->count++);
		break;
	    }
	break;

        case vcommDISABLED:
	    _notifyUpdateState(base);
	    scribe = vcharScribeFormatScribed(SCRIBE("vcommDISABLED - %d"),
					      data->count++);
	break;

        default:
	    _notifyUpdateState(base);
	    vdebugMWarn(("unrecognized message received\n"));
	    scribe = vcharScribeFormatScribed(SCRIBE("UNKNOWN - %d"),
					      data->count++);
        break;
    }

    vdialogSetItemTitleScribed(vdialogFindItem(data->dialog, 
					       TAG("MessageLabel")), scribe);
}

void 
_notifyUpdateState(vcommBase *base)
{
    _commtestData *data;
    vdialogItem *item;

    data = (_commtestData *) vcommGetBaseData(base);
    item = vdialogFindItem(data->dialog, TAG("StateLabel"));

    if (item == NULL)
    {
	vdebugMWarn(("could not find state label\n"));
	return;
    }

    switch(vcommGetBaseState(base))
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
}

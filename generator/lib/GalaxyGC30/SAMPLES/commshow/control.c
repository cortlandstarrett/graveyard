/* $Id: control.c,v 1.8 1997/05/27 15:21:47 paul Exp $ */

#ifndef  vportINCLUDED
#include <vport.h>
#endif

#ifndef  vstdINCLUDED
#include vstdHEADER
#endif

#ifndef  vstdlibINCLUDED
#include vstdlibHEADER
#endif

#ifndef  vdialogINCLUDED
#include vdialogHEADER
#endif

#ifndef  vtextitemINCLUDED
#include vtextitemHEADER
#endif

#ifndef  vcommandINCLUDED
#include vcommandHEADER
#endif

#ifndef  vcommINCLUDED
#include vcommHEADER
#endif

#ifndef  vnumINCLUDED
#include vnumHEADER
#endif

#ifndef  vdebugINCLUDED
#include vdebugHEADER
#endif

#ifndef  _commtestCommshowINCLUDED
#include "commshow.h"
#endif

#ifndef  _commtestAttribINCLUDED
#include "attrib.h"
#endif

#ifndef  _commtestControlINCLUDED
#include "control.h"
#endif

#ifndef  _commtestNotifyINCLUDED
#include "notify.h"
#endif

#ifndef  _commtestUtilINCLUDED
#include "util.h"
#endif

static int _controlSendSmallMessage(vcommandFunction *command, vdict *context);
static int _controlSendLargeMessage(vcommandFunction *command, vdict *context);
static int _controlReceiveMessage(vcommandFunction *command, vdict *context);
static int _controlEnable(vcommandFunction *command, vdict *context);
static int _controlDisable(vcommandFunction *command, vdict *context);
static int _controlDump(vcommandFunction *command, vdict *context);
static void _controlSetUpVector(vdialog *dialog, const vname *tagbytes, 
			const vname *tagvecs, vcommVector **vecs, int *nvecs);

/*
 * commands for vcommBase operation
 */
static vcommandFunctionTemplate controlCommands[] = {
    {"SendSmallMessage",     _controlSendSmallMessage,  NULL},
    {"SendLargeMessage",     _controlSendLargeMessage,  NULL},
    {"EnableBase",           _controlEnable,            NULL},
    {"DisableBase",          _controlDisable,           NULL},
    {"DumpBase",             _controlDump,              NULL},
    {"RecvMessage",          _controlReceiveMessage,    NULL}
};

/*************************************************************************/
void 
_controlSetupCommandSpace(vdialog *dialog)
{
    vcommandSpace       *space;
    vdict               *cmdDict;

    space = vwindowGetSpace(vdialogGetWindow(dialog));

    cmdDict = vcommandCreateDictOfClassFunctionTemplates(
	       vcommandGetDefaultFunctionClass(),
               controlCommands,
               (size_t) sizeof(controlCommands) / sizeof(controlCommands[0]));
    vcommandAddSpaceDictOwned(space, vname_Command, cmdDict);
}


/*************************************************************************/
static int 
_controlSendSmallMessage(vcommandFunction *command, vdict *context)
{
    int                  len;
    vtextitem           *textitem;
    vdialog             *dialog;
    vscribe             *export;
    vstr                *str;
    vcommBase           *base;
    _commtestData       *data;
    vbyte                buffer[SMALL_MESSAGE_SIZE*sizeof(vchar)+1];

    textitem = (vtextitem *) (vdictLoad(context, vname_Operator));
    dialog   = (vdialog *) (vdictLoad(context, vname_Dialog));
    base = (vcommBase *) vdialogGetData(dialog);
    data = (_commtestData *) vcommGetBaseData(base);

    str = vtextitemGetTextAsString(textitem);
    len = vstrGetSize(str);
    if (len == 0)
	return TRUE;

    export = vcharScribeASCIIExport(str);
    len = vcharGetExportLength(export)+1; /* ASCII null terminator is 1 byte */
    vcharExport(export, (void *)buffer);
    vstrDestroy(str);

    if (vclassIsKindOf(vcommGetBaseClass(base),
		       vcommGetDefaultDatagramClass()))
    {
	vexWITH_HANDLING
	{
	    vcommSendDatagramBuffer((vcommDatagram *) vdialogGetData(dialog),
				    data->remote_locator, buffer, len);
	}
        vexON_EXCEPTION
        {
	    vexDumpChain(vdebugGetWarningStream());
	}
	vexEND_HANDLING;
    }
    else
    {
	vexWITH_HANDLING
	{
	    vcommSendStreamBuffer((vcommStream *) vdialogGetData(dialog),
				  buffer, len);
	}
        vexON_EXCEPTION
        {
	    vexDumpChain(vdebugGetWarningStream());
	}
	vexEND_HANDLING;
    }
    return TRUE;
}

/*************************************************************************/
static int 
_controlSendLargeMessage(vcommandFunction *command, vdict *context)
{
    vdialog         * volatile dialog;
    vcommVector     *          vecs;
    int                        nvecs;
    vcommVector     * volatile vectors;
    int               volatile nvectors;
    vcommBase       * volatile base;
    _commtestData   * volatile data;
    int               volatile i, count;

    dialog  = (vdialog *) (vdictLoad(context, vname_Dialog));
    base    = (vcommBase *) vdialogGetData(dialog);
    data    = (_commtestData *) vcommGetBaseData(base);

    _controlSetUpVector(dialog, 
			TAG("SendNumberOfBytes"), TAG("SendNumberOfVectors"),
			&vecs, &nvecs);
    vectors = vecs;
    nvectors = nvecs;

    count = 0;
    if (vclassIsKindOf(vcommGetBaseClass(base),
		       vcommGetDefaultDatagramClass()))
    {
	vexWITH_HANDLING
	{
	    count = vcommSendDatagram((vcommDatagram *) vdialogGetData(dialog),
				      data->remote_locator, vectors, nvectors);
	}
        vexON_EXCEPTION
        {
	    vexDumpChain(vdebugGetWarningStream());
	}
	vexEND_HANDLING;
    }
    else
    {
	vexWITH_HANDLING
	{
	    count = vcommSendStream((vcommStream *) vdialogGetData(dialog),
				    vectors, nvectors);
	}
        vexON_EXCEPTION
        {
	    vexDumpChain(vdebugGetWarningStream());
	}
	vexEND_HANDLING;
    }

    for (i=0; i<nvectors; i++)
	vmemFree(vectors[i].buffer);
    vmemFree(vectors);

    vdialogSetItemTitleScribed(_utilFindItem(dialog, TAG("SentNumber")),
			       vnumScribeInt(count));
    return TRUE;
}

/*************************************************************************/
static int 
_controlReceiveMessage(vcommandFunction *command, vdict *context)
{
    vdialog         * volatile dialog;
    vcommVector     *          vecs;
    int                        nvecs;
    vcommVector     * volatile vectors;
    int               volatile nvectors;
    vcommBase       * volatile base;
    _commtestData   * volatile data;
    int               volatile count;
    int               i, msize;
    vbool             volatile success;

    dialog  = (vdialog *) (vdictLoad(context, vname_Dialog));
    base    = (vcommBase *) vdialogGetData(dialog);
    data    = (_commtestData *) vcommGetBaseData(base);

    _controlSetUpVector(dialog, 
			TAG("RecvNumberOfBytes"), TAG("RecvNumberOfVectors"),
			&vecs, &nvecs);
    vectors = vecs;
    nvectors = nvecs;

    success = vTRUE;
    count = 0;
    if (vclassIsKindOf(vcommGetBaseClass(base),
		       vcommGetDefaultDatagramClass()))
    {
	vexWITH_HANDLING
	{
	    count = 
		vcommReceiveDatagram((vcommDatagram *) vdialogGetData(dialog),
				     data->remote_locator, vectors, nvectors);
	}
        vexON_EXCEPTION
        {
	    success = vFALSE;
	    vexDumpChain(vdebugGetWarningStream());
	}
	vexEND_HANDLING;
	if (success)
	    _attribLocatorUpdate(dialog, _REMOTE_LOCATOR);
    }
    else
    {
	vexWITH_HANDLING
	{
	    count = vcommReceiveStream((vcommStream *) vdialogGetData(dialog),
				       vectors, nvectors);
	}
        vexON_EXCEPTION
        {
	    success = vFALSE;
	    vexDumpChain(vdebugGetWarningStream());
	}
	vexEND_HANDLING;
    }

    _notifyUpdateState((vcommBase *) vdialogGetData(dialog));
    if (success)
    {
	_attribUpdate(dialog);
	vdialogSetItemTitleScribed(_utilFindItem(dialog, TAG("RecvNumber")),
				   vnumScribeInt(count));
	msize = vMIN(SMALL_MESSAGE_SIZE, count);
	if ((msize > 0) && (nvectors > 0))
	{
	    msize = (int)vMIN((size_t)msize, vectors[0].count);
	    if (msize > 0)
		vdialogSetItemTitleScribed(
		    _utilFindItem(dialog, TAG("Message")),
		    vcharSizedScribeASCII((char *) vectors[0].buffer, msize));
	    else
		vdialogSetItemTitleScribed(
		    _utilFindItem(dialog, TAG("Message")),
		    vcharScribe(vcharGetEmptyString()));
	}
	else
	    vdialogSetItemTitleScribed(_utilFindItem(dialog, TAG("Message")),
				       vcharScribe(vcharGetEmptyString()));
    }
    for (i=0; i<nvectors; i++)
	vmemFree(vectors[i].buffer);
    vmemFree(vectors);

    return TRUE;
}

/*************************************************************************/
static void
_controlSetUpVector(vdialog *dialog, const vname *tagbytes, 
		    const vname *tagvecs, vcommVector **vecs, int *nvecs)
{
    vtextitem           * volatile textitem[2];
    vcommBase           * volatile base;
    _commtestData       * volatile data;
    int                   volatile nvectors;
    int                   volatile nbytes;
    int                   volatile status;
    int                   volatile i, count;
    vcommVector         * volatile vectors;

    base = (vcommBase *) vdialogGetData(dialog);
    data = (_commtestData *) vcommGetBaseData(base);

    textitem[0] = (vtextitem *) _utilFindItem(dialog, tagbytes);
    status = vFALSE;
    vexWITH_HANDLING
    {
	nbytes = vtextitemGetTextAsInt(textitem[0]);
	status = vTRUE;
    }
    vexON_EXCEPTION
    {
	vdebugMWarn(("value ignored, not integer\n"));
    }
    vexEND_HANDLING;

    if ((!status) || (nbytes <= 0))
    {
	nbytes = DEFAULT_NUMBER_OF_BYTES;
	_utilSetTextAsScribe(textitem[0], vnumScribeInt(nbytes));
    }
    else if (nbytes > MAX_NUMBER_OF_BYTES)
    {
	nbytes = MAX_NUMBER_OF_BYTES;
	_utilSetTextAsScribe(textitem[0], vnumScribeInt(nbytes));
    }

    textitem[1] = (vtextitem *) _utilFindItem(dialog, tagvecs);
    status = vFALSE;
    vexWITH_HANDLING
    {
	nvectors = vtextitemGetTextAsInt(textitem[1]);
	status = vTRUE;
    }
    vexON_EXCEPTION
    {
	vdebugMWarn(("value ignored, not integer\n"));
    }
    vexEND_HANDLING;

    if ((!status) || (nvectors <= 0))
    {
	nvectors = DEFAULT_NUMBER_OF_VECTORS;
	_utilSetTextAsScribe(textitem[1], vnumScribeInt(nvectors));
    }
    else if (nvectors > MAX_NUMBER_OF_VECTORS)
    {
	nvectors = MAX_NUMBER_OF_VECTORS;
	_utilSetTextAsScribe(textitem[1], vnumScribeInt(nvectors));
    }

    if (nvectors > nbytes)
    {
	nbytes = DEFAULT_NUMBER_OF_BYTES;
	_utilSetTextAsScribe(textitem[0], vnumScribeInt(nbytes));
    }

    vectors = (vcommVector *) vmemAlloc(sizeof(vcommVector)*nvectors);

    for (count=0, i=0; i<nvectors; i++)
    {
	if (i+1==nvectors)
	    vectors[i].count = nbytes - count;
	else
	{
	    vectors[i].count = nbytes/nvectors;
	    count += vectors[i].count;
	}
	vectors[i].buffer = 
	    (vbyte *) vmemAlloc(sizeof(vbyte)*vectors[i].count);
	(void ) vmemSet((void *) vectors[i].buffer, (int) 'a', 
			sizeof(vbyte)*vectors[i].count);
    }

    *nvecs = nvectors;
    *vecs  = vectors;
}
		    


/*************************************************************************/
static int 
_controlEnable(vcommandFunction *command, vdict *context)
{
    vdialog  * volatile dialog;
    vbool      volatile enabled;

    enabled = vFALSE;
    dialog  = (vdialog *)  (vdictLoad(context, vname_Dialog));
    vexWITH_HANDLING
    {
	vcommEnableBase((vcommBase *) vdialogGetData(dialog));
	enabled = vTRUE;
    }
    vexON_EXCEPTION
    {
	vexDumpChain(vdebugGetWarningStream());
    }
    vexEND_HANDLING;

    _notifyUpdateState((vcommBase *) vdialogGetData(dialog));
    if (enabled)
    {
	_attribLocatorUpdate(dialog, _BOTH_LOCATOR);
	_attribUpdate(dialog);
    }
    return TRUE;
}

/*************************************************************************/
static int 
_controlDisable(vcommandFunction *command, vdict *context)
{
    vdialog  * volatile dialog;
    vbool      volatile disabled;

    disabled = vFALSE;

    dialog  = (vdialog *)  (vdictLoad(context, vname_Dialog));
    vexWITH_HANDLING
    {
	vcommDisableBase((vcommBase *) vdialogGetData(dialog));
	disabled = vTRUE;
    }
    vexON_EXCEPTION
    {
	vexDumpChain(vdebugGetWarningStream());
    }
    vexEND_HANDLING;

    _notifyUpdateState((vcommBase *) vdialogGetData(dialog));
    if (disabled)
    {
	_attribLocatorUpdate(dialog, _BOTH_LOCATOR);
	_attribUpdate(dialog);
    }
    return TRUE;
}

/*************************************************************************/
static int 
_controlDump(vcommandFunction *command, vdict *context)
{
    vdialog  * volatile dialog;

    dialog  = (vdialog *)  (vdictLoad(context, vname_Dialog));
    vcommDumpBase((vcommBase *) vdialogGetData(dialog), vdebugGetInfoStream());

    return TRUE;
}

/* $Id: create.c,v 1.4 1997/02/25 16:39:04 paul Exp $ */

#ifndef vportINCLUDED
#include <vport.h>
#endif

#ifndef vdialogINCLUDED
#include vdialogHEADER
#endif

#ifndef vcommINCLUDED
#include vcommHEADER
#endif

#ifndef vexINCLUDED
#include vexHEADER
#endif

#ifndef vdebugINCLUDED
#include vdebugHEADER
#endif

#ifndef _commtestCommshowINCLUDED
#include "commshow.h"
#endif

#ifndef _commtestMainINCLUDED
#include "main.h"
#endif

#ifndef _commtestAttribINCLUDED
#include "attrib.h"
#endif

#ifndef _commtestNotifyINCLUDED
#include "notify.h"
#endif

static vdialog *_genericStreamCreate(vdialog *parent, 
				     _commtestTransportType transport);
static vdialog *_genericDatagramCreate(vdialog *parent, 
				       _commtestTransportType transport);

/*************************************************************************/
void 
_createUDP(vdialog *parent)
{
    vdialog *dialog = _genericDatagramCreate(parent, _UDPDatagram);
    vdialogOpen(dialog);
}

/*************************************************************************/
void 
_createMailbox(vdialog *parent)
{
    vdialog *dialog = _genericDatagramCreate(parent, _MailboxDatagram);
    vdialogOpen(dialog);
}

/*************************************************************************/
void 
_createTCP(vdialog *parent)
{
    vdialog *dialog = _genericStreamCreate(parent, _TCPStream);
    vdialogOpen(dialog);
}

/*************************************************************************/
void 
_createPipe(vdialog *parent)
{
    vdialog *dialog = _genericStreamCreate(parent, _PipeStream);
    vdialogOpen(dialog);
}

/*************************************************************************/
void 
_createShm(vdialog *parent)
{
    vdialog *dialog = _genericStreamCreate(parent, _ShmStream);
    vdialogOpen(dialog);
}

/*************************************************************************/
void
_destroyBase(vwindow *window)
{
    _commtestData *data;
    vcommBase *base = (vcommBase *) vwindowGetData(window);
    data = (_commtestData *) vcommGetBaseData(base);

    if (vclassIsKindOf(vcommGetBaseClass(base), 
		       vcommGetDefaultDatagramClass()))
	vcommDestroyLocator(data->remote_locator);

    vwindowDestroyLater(window);
    vmemFree(data);
    vexWITH_HANDLING
    {
	vcommDestroyBase(base);
    }
    vexON_EXCEPTION
    {
	vexDumpChain(vdebugGetWarningStream());
    }
    vexEND_HANDLING;
}


/*************************************************************************/
static vdialog *
_genericStreamCreate(vdialog *parent, _commtestTransportType transport)
{
    vdialog *dialog;
    vcommStream *stream;
    _commtestData *data;

    switch (transport)
    {
	case _TCPStream:
	dialog = vdialogClone(_getTCPDialogTemplate());
	stream = vcommCreateStreamOfClass(vcommGetTCPStreamClass());
	break;

	case _PipeStream:
	dialog = vdialogClone(_getPipeDialogTemplate());
	stream = vcommCreateStreamOfClass(vcommGetPipeStreamClass());
	break;

	case _ShmStream:
	dialog = vdialogClone(_getShmDialogTemplate());
	stream = vcommCreateStreamOfClass(vcommGetSharedMemoryStreamClass());
	break;

	default:
	break;
    }

    vwindowSetTitleScribed(vdialogGetWindow(dialog),
             vnameScribeGlobal(vclassGetName(vcommGetStreamClass(stream))));
    vwindowSetLeader(vdialogGetWindow(dialog), vdialogGetWindow(parent));
    vdialogSetData(dialog, (void *) stream);

    data = (_commtestData *) vmemAlloc(sizeof(_commtestData));
    data->remote_locator = vcommGetStreamRemoteLocator(stream);
    data->transport      = transport;
    data->dialog         = dialog;
    data->count          = 0;
    vcommSetStreamData(stream, (void *) data);
    vcommSetBaseNotify(vcommGetStreamBase(stream), _notifyBase);

    return dialog;
}

/*************************************************************************/
static vdialog *
_genericDatagramCreate(vdialog *parent, _commtestTransportType transport)
{
    vdialog *dialog;
    vcommDatagram *datagram;
    _commtestData *data;

    switch (transport)
    {
	case _UDPDatagram:
	dialog = vdialogClone(_getUDPDialogTemplate());
	datagram = vcommCreateDatagramOfClass(vcommGetUDPDatagramClass());
	break;

	case _MailboxDatagram:
	dialog = vdialogClone(_getMbxDialogTemplate());
	datagram = vcommCreateDatagramOfClass(vcommGetMailboxDatagramClass());
	break;

	default:
	break;
    }
    
    vwindowSetTitleScribed(vdialogGetWindow(dialog),
           vnameScribeGlobal(vclassGetName(vcommGetDatagramClass(datagram))));
    vwindowSetLeader(vdialogGetWindow(dialog), vdialogGetWindow(parent));
    vdialogSetData(dialog, (void *) datagram);

    data = (_commtestData *) vmemAlloc(sizeof(_commtestData));
    data->remote_locator = vcommCreateDatagramLocator(datagram);
    data->transport      = transport;
    data->dialog         = dialog;
    data->count          = 0;
    vcommSetDatagramData(datagram, (void *) data);
    vcommSetBaseNotify(vcommGetDatagramBase(datagram), _notifyBase);

    return dialog;
}

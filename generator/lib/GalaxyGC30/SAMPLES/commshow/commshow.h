/* $Id: commshow.h,v 1.4 1997/02/25 16:38:52 paul Exp $ */

#ifndef _commtestCommshowINCLUDED
#define _commtestCommshowINCLUDED 1

#ifndef vportINCLUDED
#include <vport.h>
#endif

#ifndef vcolorINCLUDED
#include vcolorHEADER
#endif

#ifndef vcommINCLUDED
#include vcommHEADER
#endif

#define SMALL_MESSAGE_SIZE 15
#define DEFAULT_NUMBER_OF_BYTES   1024
#define DEFAULT_NUMBER_OF_VECTORS 1
#define MAX_NUMBER_OF_BYTES       1024*1024*8
#define MAX_NUMBER_OF_VECTORS     15

extern vcolor *_commtestGreen;

typedef struct _commtestData _commtestData;

typedef enum
{
    _TCPStream,
    _UDPDatagram,
    _PipeStream,
    _MailboxDatagram,
    _ShmStream
} _commtestTransportType;

struct _commtestData
{
    vcommLocator *remote_locator;
    _commtestTransportType transport;
    vdialog *dialog;
    int count;
};

#define TAG(t) vnameInternGlobalLiteral(t)
#define SCRIBE(t) vcharScribeLiteral(t)

#endif

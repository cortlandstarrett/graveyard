/* $Id: vcomm.h,v 1.68 1997/09/22 22:41:13 paul Exp $ */

/*************************************************************************
 *
 * vcomm.h
 *
 * C Interface for New Communication Manager
 *
 * (c) Copyright Visix Software, Inc.
 * All Rights Reserved
 *
 *************************************************************************/

/*************************************************************************
 *
 * Inheritance looks like this:
 *
 *		     vobjectAttributed
 *			   /  \
 *	vcommLocator _____/    \_____ vcommBase
 *					 / \
 *		      vcommDatagram ____/   \____ vcommStream
 *
 *
 * vcommLocator -- Simple subclass of attributed object, adds default URL
 *		   attribute for all locators.
 *
 * vcommBase -- Superclass of all transport-related classes.  Adds
 *		enable/disable behavior, locator, and notification.
 *
 * vcommDatagram -- Base class for transports that specify their peer
 *		    locator when data is transmitted.
 *
 * vcommStream -- Base class for transports that specify their peer
 *		  locator when the transport is enabled.
 *
 * Support types:
 *
 * vcommEvent -- event struct passed to notify functions on transports.
 *
 * vcommVector -- encapsulates buffer and size for use by vectored send
 *		  and receive.
 *
 *************************************************************************/

#ifndef  vcommINCLUDED
#define  vcommINCLUDED 1

#ifndef  vportINCLUDED
#include <vport.h>
#endif

#ifndef  vclassINCLUDED
#include vclassHEADER
#endif

#ifndef  vnameINCLUDED
#include vnameHEADER
#endif

#ifndef  vobjectINCLUDED
#include vobjectHEADER
#endif

#ifndef  vresourceINCLUDED
#include vresourceHEADER
#endif

#ifndef  vstdioINCLUDED
#include vstdioHEADER
#endif

/*
 * Old vcommChannel/vcommAddress API included here, for compatibility
 */

#ifndef  vcommChannelINCLUDED
#include vcommChannelHEADER
#endif


vportBEGIN_CPLUSPLUS_EXTERN_C

/*************************************************************************
 * Public constant definitions.
 *************************************************************************/

/*
 * Transport states and messages (if any are added, must change enumerated
 * type in commpriv.h)
 */

enum {
    vcommENABLING     = 0x00001, /* STATE           - not fully enabled  */
    vcommENABLED      = 0x00002, /* STATE & MESSAGE - fully enabled      */
    vcommDISABLING    = 0x00004, /* STATE           - not fully disabled */
    vcommDISABLED     = 0x00008, /* STATE & MESSAGE - fully disabled     */
    vcommRECEIVE      = 0x00010, /* MESSAGE         - data has arrived   */
    vcommSEND         = 0x00020, /* MESSAGE         - data can be sent   */
    vcommERROR        = 0x00040, /* MESSAGE         - error has occured  */
    vcommNEXT_STATE   = 0x00080, /* subclass use 0x00080 <-> 0x08000     */
    vcommPRIVATE_FLAG = 0x10000  /* for use by vcomm manager internally  */
};

#define _vcommSTATE_MASK \
      (vcommENABLING | vcommENABLED | vcommDISABLING | vcommDISABLED)

/*
 * return values for vcommGetEventError() and vcommGetBaseExceptionError()
 */

enum {
    vcommERROR_NONE = 0x00, /* non descriptive error                    */
    vcommERROR_TRANSPORT,   /* some system level problem has occurred   */
    vcommERROR_HALT,        /* blocking operation interrupted by Halt() */
    vcommERROR_ADDRINUSE,   /* this address is already being used       */
    vcommERROR_CONNECTION,  /* the peer no longer exists                */
    vcommERROR_STATE        /* can not perform operation in this state  */
};

/*
 * ID Attributes; locators, base transports, datagram transports.
 */

enum {
    vcommLOCATOR_ID_ATTRIBUTE_URL = vobjectNEXT_ID_ATTRIBUTE,
    vcommLOCATOR_NEXT_ID_ATTRIBUTE
};

enum {
    vcommBASE_ID_ATTRIBUTE_COMMANDS = vobjectNEXT_ID_ATTRIBUTE,
    vcommBASE_ID_ATTRIBUTE_STATE,
    vcommBASE_ID_ATTRIBUTE_SYNCHRONOUS,
    vcommBASE_ID_ATTRIBUTE_NOTIFICATION,
    vcommBASE_NEXT_ID_ATTRIBUTE
};

enum {
    vcommDATAGRAM_NEXT_ID_ATTRIBUTE = vcommBASE_NEXT_ID_ATTRIBUTE
};

enum {
    vcommSTREAM_NEXT_ID_ATTRIBUTE = vcommBASE_NEXT_ID_ATTRIBUTE
};

/*
 * Predefined attribute names.
 */

#define vcomm_URL			(_vcommNames[_vcomm_URL])
#define vcomm_Commands			(_vcommNames[_vcomm_Commands])
#define vcomm_State			(_vcommNames[_vcomm_State])
#define vcomm_Synchronous		(_vcommNames[_vcomm_Synchronous])
#define vcomm_Notification		(_vcommNames[_vcomm_Notification])

#define vcomm_Port			(_vcommNames[_vcomm_Port])
#define vcomm_Server			(_vcommNames[_vcomm_Server])
#define vcomm_Internet			(_vcommNames[_vcomm_Internet])
#define vcomm_Number			(_vcommNames[_vcomm_Number])
#define vcomm_Hostname			(_vcommNames[_vcomm_Hostname])

#define vcomm_LocalAddresses		(_vcommNames[_vcomm_LocalAddresses])
#define vcomm_LocalAddressCount		(_vcommNames[_vcomm_LocalAddressCount])

#define vcomm_Path			(_vcommNames[_vcomm_Path])

#define vcomm_Key			(_vcommNames[_vcomm_Key])

#define vcomm_Descriptor		(_vcommNames[_vcomm_Descriptor])
#define vcomm_Available			(_vcommNames[_vcomm_Available])
#define vcomm_Reuseaddr			(_vcommNames[_vcomm_Reuseaddr])
#define vcomm_Dontroute			(_vcommNames[_vcomm_Dontroute])
#define vcomm_Loopback			(_vcommNames[_vcomm_Loopback])

#define vcomm_Broadcast			(_vcommNames[_vcomm_Broadcast])

#define vcomm_SendBufSize		(_vcommNames[_vcomm_SendBufSize])
#define vcomm_RecvBufSize		(_vcommNames[_vcomm_RecvBufSize])
#define vcomm_SendLowWater		(_vcommNames[_vcomm_SendLowWater])
#define vcomm_RecvLowWater		(_vcommNames[_vcomm_RecvLowWater])
#define vcomm_SendTimeout		(_vcommNames[_vcomm_SendTimeout])
#define vcomm_RecvTimeout		(_vcommNames[_vcomm_RecvTimeout])
#define vcomm_Keepalive			(_vcommNames[_vcomm_Keepalive])
#define vcomm_Linger			(_vcommNames[_vcomm_Linger])
#define vcomm_OobInline			(_vcommNames[_vcomm_Oobinline])

#define vcomm_SharedMemoryID		(_vcommNames[_vcomm_SharedMemoryID])
#define vcomm_SemaphoreID		(_vcommNames[_vcomm_SemaphoreID])

/*************************************************************************
 * Public type definitions.
 *************************************************************************/

/*
 * Support types; vectors, events, tickets.
 */

typedef struct vcommEvent		vcommEvent;
typedef struct vcommVector		vcommVector;

/*
 * Base locator types.
 */

typedef struct vcommLocator		vcommLocator;
typedef struct vcommLocatorClass	vcommLocatorClass;

/*
 * Base transport types.
 */

typedef struct vcommBase		vcommBase;
typedef struct vcommBaseClass		vcommBaseClass;
typedef struct vcommBaseException	vcommBaseException;

typedef void (*vcommBaseNoteProc)(
    vcommBase		*base,
    vcommEvent		*event
    );

/*
 * Base class for Datagram-oriented endpoints.
 */

typedef struct vcommDatagram		vcommDatagram;
typedef struct vcommDatagramClass	vcommDatagramClass;

typedef void (*vcommDatagramNoteProc)(
    vcommDatagram	*dgram,
    vcommEvent		*event
    );

/*
 * Base class for connection-oriented endpoints.
 */

typedef struct vcommStream		vcommStream;
typedef struct vcommStreamClass		vcommStreamClass;

typedef void (*vcommStreamNoteProc)(
    vcommStream		*stream,
    vcommEvent		*event
    );

/*
 * Transport specific classes.
 */
typedef struct vcommTCPStream			vcommTCPStream;
typedef struct vcommTCPStreamClass		vcommTCPStreamClass;
typedef struct vcommPipeStream			vcommPipeStream;
typedef struct vcommPipeStreamClass		vcommPipeStreamClass;
typedef struct vcommSharedMemoryStream		vcommSharedMemoryStream;
typedef struct vcommSharedMemoryStreamClass	vcommSharedMemoryStreamClass;
typedef struct vcommUDPDatagram			vcommUDPDatagram;
typedef struct vcommUDPDatagramClass		vcommUDPDatagramClass;
typedef struct vcommMailboxDatagram		vcommMailboxDatagram;
typedef struct vcommMailboxDatagramClass	vcommMailboxDatagramClass;

typedef vcommLocator				vcommIPLocator;
typedef vcommLocator				vcommLocalLocator;

typedef struct vcommTCPLocator			vcommTCPLocator;
typedef struct vcommTCPLocatorClass		vcommTCPLocatorClass;
typedef struct vcommPipeLocator			vcommPipeLocator;
typedef struct vcommPipeLocatorClass		vcommPipeLocatorClass;
typedef struct vcommSharedMemoryLocator		vcommSharedMemoryLocator;
typedef struct vcommSharedMemoryLocatorClass	vcommSharedMemoryLocatorClass;
typedef struct vcommUDPLocator			vcommUDPLocator;
typedef struct vcommUDPLocatorClass		vcommUDPLocatorClass;
typedef struct vcommMailboxLocator		vcommMailboxLocator;
typedef struct vcommMailboxLocatorClass		vcommMailboxLocatorClass;

/*************************************************************************
 * Public function prototypes, Event types.
 *************************************************************************/

void vcommInitEvent(
    vcommEvent			*event
    );

void vcommDestroyEvent(
    vcommEvent			*event
    );

int vcommGetEventType(
    vcommEvent			*event
    );

void vcommSetEventType(
    vcommEvent			*event,
    int				 type
    );

int vcommGetEventError(
    vcommEvent			*event
    );

void vcommSetEventError(
    vcommEvent			*event,
    int				 error
    );


/*************************************************************************
 * Public function prototypes, Vector types.
 *************************************************************************/

size_t vcommGetVectorSize(
    vcommVector			*vector
    );

void vcommSetVectorSize(
    vcommVector			*vector,
    size_t			 count
    );

vbyte *vcommGetVectorBuffer(
    vcommVector			*vector
    );

void vcommSetVectorBuffer(
    vcommVector			*vector,
    vbyte			*buffer
    );

void vcommSetVector(
    vcommVector			*vector,
    vbyte			*buffer,
    size_t			 count
    );

void vcommAdvanceVector(
    vcommVector                 *source,
    vcommVector                 *dest,
    int                          less_bytes,
    int                         *nvectors
    );

/*************************************************************************
 * Public function prototypes, Locator objects.
 *************************************************************************/

vcommLocatorClass *vcommGetDefaultLocatorClass(
    void
    );

vcommLocatorClass *vcommGetLocatorClass(
    vcommLocator		*locator
    );

vobjectAttributed *vcommGetLocatorObject(
    vcommLocator		*locator
    );

vcommLocator *vcommCreateLocatorOfClass(
    vcommLocatorClass		*clas
    );

vcommLocator *vcommCreateLocator(
    void
    );

void vcommInitLocatorOfClass(
    vcommLocator		*locator,
    vcommLocatorClass		*clas
    );

void vcommInitLocator(
    vcommLocator		*locator
    );

void vcommDestroyLocator(
    vcommLocator		*locator
    );

void vcommCopyLocator(
    vcommLocator		*locator,
    vcommLocator		*target
    );

void vcommCopyInitLocator(
    vcommLocator		*locator,
    vcommLocator		*target
    );

vcommLocator *vcommCloneLocator(
    vcommLocator		*locator
    );

vcommLocator *vcommLoadLocator(
    vresource			 resource
    );

void vcommStoreLocator(
    vcommLocator		*locator,
    vresource			 resource
    );

void vcommDumpLocator(
    vcommLocator		*locator,
    FILE			*fd
    );

const void *vcommGetLocatorAttribute(
    vcommLocator		*locator,
    const vname			*attribute
    );

void vcommSetLocatorAttribute(
    vcommLocator		*locator,
    const vname			*attribute,
    const void			*value
    );

long vcommGetLocatorAttributeScalar(
    vcommLocator		*locator,
    const vname			*attribute
    );

void vcommSetLocatorAttributeScalar(
    vcommLocator		*locator,
    const vname			*attribute,
    long			 value
    );

vscribe *vcommGetLocatorAttributeScribed(
    vcommLocator		*locator,
    const vname			*attribute
    );

void vcommSetLocatorAttributeScribed(
    vcommLocator		*locator,
    const vname			*attribute,
    vscribe			*value
    );

void *vcommGetLocatorDevice(
    vcommLocator		*locator
    );

void vcommSetLocatorDevice(
    vcommLocator		*locator,
    void			*device
    );

void vcommClearLocator(
    vcommLocator		*locator
    );

vbool vcommCompareLocator(
    vcommLocator		*locator,
    vcommLocator		*locator2
    );

void vcommRegisterStaticListener(
    vcommLocator		*locator
    );

vbool vcommUnregisterStaticListener(
    vcommLocator		*locator
    );

/*************************************************************************
 * Public function prototypes, Base objects.
 *************************************************************************/

vcommBaseClass *vcommGetDefaultBaseClass(
    void
    );

vcommBaseClass *vcommGetBaseClass(
    vcommBase			*base
    );

vobjectAttributed *vcommGetBaseObject(
    vcommBase			*base
    );

vcommBase *vcommCreateBaseOfClass(
    vcommBaseClass		*clas
    );

vcommBase *vcommCreateBase(
    void
    );

void vcommInitBaseOfClass(
    vcommBase			*base,
    vcommBaseClass		*clas
    );

void vcommInitBase(
    vcommBase			*base
    );

void vcommDestroyBase(
    vcommBase			*base
    );

vcommBase *vcommCloneBase(
    vcommBase			*base
    );

vcommBase *vcommLoadBase(
    vresource			 resource
    );

void vcommStoreBase(
    vcommBase			*base,
    vresource			 resource
    );

void vcommDumpBase(
    vcommBase			*base,
    FILE			*fd
    );

const void *vcommGetBaseAttribute(
    vcommBase			*base,
    const vname			*attribute
    );

void vcommSetBaseAttribute(
    vcommBase			*base,
    const vname			*attribute,
    const void			*value
    );

long vcommGetBaseAttributeScalar(
    vcommBase			*base,
    const vname			*attribute
    );

void vcommSetBaseAttributeScalar(
    vcommBase			*base,
    const vname			*attribute,
    long			 value
    );

vscribe *vcommGetBaseAttributeScribed(
    vcommBase			*base,
    const vname			*attribute
    );

void vcommSetBaseAttributeScribed(
    vcommBase			*base,
    const vname			*attribute,
    vscribe			*value
    );

const void *vcommGetBaseData(
    vcommBase			*base
    );

void vcommSetBaseData(
    vcommBase			*base,
    const void			*data
    );

void vcommEnableBase(
    vcommBase			*base
    );

void vcommDisableBase(
    vcommBase			*base
    );

int vcommWaitBase(
    vcommBase			*base,
    int                          events,
    vtimestamp                  *timestamp
    );

void vcommHaltBase(
    vcommBase			*base
    );

int vcommGetBaseState(
    vcommBase			*base
    );

void vcommSetBaseState(
    vcommBase			*base,
    int				 state
    );

void vcommSendBaseEvent(
    vcommBase			*base,
    vcommEvent			*event
    );

void vcommNotifyBase(
    vcommBase			*base,
    vcommEvent			*event
    );

vcommBaseNoteProc vcommGetBaseNotify(
    vcommBase			*base
    );

void vcommSetBaseNotify(
    vcommBase			*base,
    vcommBaseNoteProc		 noteProc
    );

vcommLocatorClass *vcommGetBaseLocatorClass(
    vcommBase			*base
    );

void vcommSetBaseLocatorClass(
    vcommBase			*base,
    vcommLocatorClass		*clas
    );

vcommLocator *vcommCreateBaseLocator(
    vcommBase			*base
    );

vcommLocator *vcommGetBaseLocator(
    vcommBase			*base
    );

void *vcommGetBaseDevice(
    vcommBase			*base
    );

void vcommSetBaseDevice(
    vcommBase			*base,
    void			*device
    );

/*
 * Exceptions generated by base class.
 */

const vexClass *vcommGetBaseExceptionClass(
    void
    );

vcommBaseException *vcommGetBaseException(
    void
    );

int vcommGetBaseExceptionError(
    vcommBaseException		*exception
    );

vcommBase *vcommGetBaseExceptionBase(
    vcommBaseException		*exception
    );

void vcommGenerateBaseException(
    vcommBase			*base,
    int				 error,
    const char			*message
    );

void vcommPropagateBaseException(
    vcommBase			*base,
    int				 error,
    const char			*message
    );

/*************************************************************************
 * Public function prototypes, Datagram objects.
 *************************************************************************/

vcommDatagramClass *vcommGetDefaultDatagramClass(
    void
    );

vcommDatagramClass *vcommGetDatagramClass(
    vcommDatagram		*dgram
    );

vcommBase *vcommGetDatagramBase(
    vcommDatagram		*dgram
    );

vcommDatagram *vcommCreateDatagramOfClass(
    vcommDatagramClass		*clas
    );

vcommDatagram *vcommCreateDatagram(
    void
    );

void vcommInitDatagramOfClass(
    vcommDatagram		*dgram,
    vcommDatagramClass		*clas
    );

void vcommInitDatagram(
    vcommDatagram		*dgram
    );

void vcommDestroyDatagram(
    vcommDatagram		*dgram
    );

vcommDatagram *vcommCloneDatagram(
    vcommDatagram		*dgram
    );

vcommDatagram *vcommLoadDatagram(
    vresource			resource
    );

void vcommStoreDatagram(
    vcommDatagram		*dgram,
    vresource			 resource
    );

void vcommDumpDatagram(
    vcommDatagram		*dgram,
    FILE			*fd
    );

const void *vcommGetDatagramAttribute(
    vcommDatagram		*dgram,
    const vname			*attribute
    );

void vcommSetDatagramAttribute(
    vcommDatagram		*dgram,
    const vname			*attribute,
    const void			*value
    );

long vcommGetDatagramAttributeScalar(
    vcommDatagram		*dgram,
    const vname			*attribute
    );

void vcommSetDatagramAttributeScalar(
    vcommDatagram		*dgram,
    const vname			*attribute,
    long			 value
    );

vscribe *vcommGetDatagramAttributeScribed(
    vcommDatagram		*dgram,
    const vname			*attribute
    );

void vcommSetDatagramAttributeScribed(
    vcommDatagram		*dgram,
    const vname			*attribute,
    vscribe			*value
    );

const void *vcommGetDatagramData(
    vcommDatagram		*dgram
    );

void vcommSetDatagramData(
    vcommDatagram		*dgram,
    const void			*data
    );

void vcommEnableDatagram(
    vcommDatagram		*dgram
    );

void vcommDisableDatagram(
    vcommDatagram		*dgram
    );

int vcommWaitDatagram(
    vcommDatagram		*dgram,
    int                          events,
    vtimestamp                  *timestamp
    );

void vcommHaltDatagram(
    vcommDatagram		*dgram
    );

int vcommGetDatagramState(
    vcommDatagram		*dgram
    );

void vcommSetDatagramState(
    vcommDatagram		*dgram,
    int				 state
    );

void vcommSendDatagramEvent(
    vcommDatagram		*dgram,
    vcommEvent			*event
    );

void vcommNotifyDatagram(
    vcommDatagram		*dgram,
    vcommEvent			*event
    );

vcommDatagramNoteProc vcommGetDatagramNotify(
    vcommDatagram		*dgram
    );

void vcommSetDatagramNotify(
    vcommDatagram		*dgram,
    vcommDatagramNoteProc	 noteProc
    );

vcommLocatorClass *vcommGetDatagramLocatorClass(
    vcommDatagram		*dgram
    );

void vcommSetDatagramLocatorClass(
    vcommDatagram		*dgram,
    vcommLocatorClass		*clas
    );

vcommLocator *vcommCreateDatagramLocator(
    vcommDatagram		*dgram
    );

vcommLocator *vcommGetDatagramLocator(
    vcommDatagram		*dgram
    );

void *vcommGetDatagramDevice(
    vcommDatagram		*dgram
    );

void vcommSetDatagramDevice(
    vcommDatagram		*dgram,
    void			*device
    );

size_t vcommSendDatagram(
    vcommDatagram		*dgram,
    vcommLocator		*locator,
    vcommVector			*vector,
    int				 num
    );

size_t vcommSendDatagramBuffer(
    vcommDatagram		*dgram,
    vcommLocator		*locator,
    vbyte			*buffer,
    size_t			 count
    );

size_t vcommReceiveDatagram(
    vcommDatagram		*dgram,
    vcommLocator		*locator,
    vcommVector			*vector,
    int				 num
    );

size_t vcommReceiveDatagramBuffer(
    vcommDatagram		*dgram,
    vcommLocator		*locator,
    vbyte			*buffer,
    size_t			 count
    );

void vcommGenerateDatagramException(
    vcommDatagram		*dgram,
    int				 error,
    const char			*message
    );

void vcommPropagateDatagramException(
    vcommDatagram		*dgram,
    int				 error,
    const char			*message
    );

/*************************************************************************
 * Public function prototypes, Stream objects.
 *************************************************************************/

vcommStreamClass *vcommGetDefaultStreamClass(
    void
    );

vcommStreamClass *vcommGetStreamClass(
    vcommStream			*stream
    );

vcommBase *vcommGetStreamBase(
    vcommStream			*stream
    );

vcommStream *vcommCreateStreamOfClass(
    vcommStreamClass		*clas
    );

vcommStream *vcommCreateStream(
    void
    );

void vcommInitStreamOfClass(
    vcommStream			*stream,
    vcommStreamClass		*clas
    );

void vcommInitStream(
    vcommStream			*stream
    );

void vcommDestroyStream(
    vcommStream			*stream
    );

vcommStream *vcommCloneStream(
    vcommStream			*stream
    );

vcommStream *vcommLoadStream(
    vresource			 resource
    );

void vcommStoreStream(
    vcommStream			*stream,
    vresource			 resource
    );

void vcommDumpStream(
    vcommStream			*stream,
    FILE			*fd
    );

const void *vcommGetStreamAttribute(
    vcommStream			*stream,
    const vname			*attribute
    );

void vcommSetStreamAttribute(
    vcommStream			*stream,
    const vname			*attribute,
    const void			*value
    );

long vcommGetStreamAttributeScalar(
    vcommStream			*stream,
    const vname			*attribute
    );

void vcommSetStreamAttributeScalar(
    vcommStream			*stream,
    const vname			*attribute,
    long			 value
    );

vscribe *vcommGetStreamAttributeScribed(
    vcommStream			*stream,
    const vname			*attribute
    );

void vcommSetStreamAttributeScribed(
    vcommStream			*stream,
    const vname			*attribute,
    vscribe			*value
    );

const void *vcommGetStreamData(
    vcommStream			*stream
    );

void vcommSetStreamData(
    vcommStream			*stream,
    const void			*data
    );

void vcommEnableStream(
    vcommStream			*stream
    );

void vcommDisableStream(
    vcommStream			*stream
    );

int vcommWaitStream(
    vcommStream			*stream,
    int                          events,
    vtimestamp                  *timestamp
    );

void vcommHaltStream(
    vcommStream			*stream
    );

int vcommGetStreamState(
    vcommStream			*stream
    );

void vcommSetStreamState(
    vcommStream			*stream,
    int				 state
    );

void vcommSendStreamEvent(
    vcommStream			*stream,
    vcommEvent			*event
    );

void vcommNotifyStream(
    vcommStream			*stream,
    vcommEvent			*event
    );

vcommStreamNoteProc vcommGetStreamNotify(
    vcommStream			*stream
    );

void vcommSetStreamNotify(
    vcommStream			*stream,
    vcommStreamNoteProc		 noteProc
    );

vcommLocatorClass *vcommGetStreamLocatorClass(
    vcommStream			*stream
    );

void vcommSetStreamLocatorClass(
    vcommStream			*stream,
    vcommLocatorClass		*clas
    );

vcommLocator *vcommCreateStreamLocator(
    vcommStream			*stream
    );

vcommLocator *vcommGetStreamLocator(
    vcommStream			*stream
    );

void *vcommGetStreamDevice(
    vcommStream			*stream
    );

void vcommSetStreamDevice(
    vcommStream			*stream,
    void			*device
    );

vcommLocator *vcommGetStreamRemoteLocator(
    vcommStream			*stream
    );

size_t vcommSendStream(
    vcommStream			*stream,
    vcommVector			*vector,
    int				 num
    );

size_t vcommSendStreamBuffer(
    vcommStream			*stream,
    vbyte			*buffer,
    size_t			 count
    );

size_t vcommReceiveStream(
    vcommStream			*stream,
    vcommVector			*vector,
    int				 num
    );

size_t vcommReceiveStreamBuffer(
    vcommStream			*stream,
    vbyte			*buffer,
    size_t			 count
    );

void vcommGenerateStreamException(
    vcommStream			*stream,
    int				 error,
    const char			*message
    );

void vcommPropagateStreamException(
    vcommStream			*stream,
    int				 error,
    const char			*message
    );

/*************************************************************************
 * Transport-specific function prototypes.
 *************************************************************************/

/*
 * Transport classes.
 */

vcommDatagramClass *vcommGetUDPDatagramClass(
    void
    );

vcommStreamClass *vcommGetTCPStreamClass(
    void
    );

vcommDatagramClass *vcommGetMailboxDatagramClass(
    void
    );

vcommStreamClass *vcommGetPipeStreamClass(
    void
    );

vcommStreamClass *vcommGetSharedMemoryStreamClass(
    void
    );

/*
 * Locator classes.
 */

vcommLocatorClass *vcommGetUDPLocatorClass(
   void
   );

vcommLocatorClass *vcommGetTCPLocatorClass(
   void
   );

vcommLocatorClass *vcommGetMailboxLocatorClass(
   void
   );

vcommLocatorClass *vcommGetPipeLocatorClass(
   void
   );

vcommLocatorClass *vcommGetSharedMemoryLocatorClass(
   void
   );

/*
 * API to determine availability of transport.
 */

int vcommHasUDP(
    void
    );

int vcommHasTCP(
    void
    );

int vcommHasMailbox(
    void
    );

int vcommHasPipe(
    void
    );

int vcommHasSharedMemory(
    void
    );

/*************************************************************************
 * Private constant definitions.
 *************************************************************************/

enum {
    _vcomm_URL = 0x00,
    _vcomm_Commands,
    _vcomm_State,
    _vcomm_Synchronous,
    _vcomm_Notification,

    _vcomm_Port,
    _vcomm_Server,
    _vcomm_Internet,
    _vcomm_Number,
    _vcomm_Hostname,

    _vcomm_LocalAddresses,
    _vcomm_LocalAddressCount,

    _vcomm_Path,

    _vcomm_Key,

    _vcomm_Descriptor,
    _vcomm_Available,
    _vcomm_Reuseaddr,
    _vcomm_Dontroute,
    _vcomm_Loopback,

    _vcomm_Broadcast,

    _vcomm_SendBufSize,
    _vcomm_RecvBufSize,
    _vcomm_SendLowWater,
    _vcomm_RecvLowWater,
    _vcomm_SendTimeout,
    _vcomm_RecvTimeout,
    _vcomm_Keepalive,
    _vcomm_Linger,
    _vcomm_Oobinline,

    _vcomm_SharedMemoryID,
    _vcomm_SemaphoreID,

    _vcommCOUNT
};

/*************************************************************************
 * Private type definitions.
 *************************************************************************/

/*
 * Event type definition.
 */

struct vcommEvent {
    int			type;
    int			error;
};

/*
 * Vector type definition.
 */

struct vcommVector {
    vbyte		*buffer;
    size_t		 count;
};

/*
 * Abstract locator class.
 */

struct vcommLocator {
    vobjectAttributed	 super;
    void		*device;
};

#define vcommLOCATOR_CLASS(SUPER, LOCATOR)				 \
    vobjectATTRIBUTED_CLASS(SUPER, LOCATOR);				 \
    vclassMETHOD(vcommLocatorSET_DEVICE,  (LOCATOR *loc, void *device)); \
    vclassMETHOD(vcommLocatorCLEAR,       (LOCATOR *loc));               \
    vclassMETHOD_RET(vcommLocatorCOMPARE, vbool,                         \
                    (LOCATOR *loc, vcommLocator *loc2))

struct vcommLocatorClass {
    vcommLOCATOR_CLASS(vcommLocatorClass, vcommLocator);
};

/*
 * Abstract transport class.
 */

struct vcommBase {
    vobjectAttributed	 super;
    vcommBaseNoteProc	 noteProc;
    vcommLocator	*local;
    const void		*data;
    int			 flags;
    void		*device;
};

#define vcommBASE_CLASS(SUPER, BASE, NOTIFY)				\
    vobjectATTRIBUTED_CLASS(SUPER, BASE);				\
    vclassVARIABLE(vcommBaseLOCATOR_CLASS, vcommLocatorClass *);	\
    vclassMETHOD(vcommBaseENABLE, (BASE *base));			\
    vclassMETHOD(vcommBaseDISABLE, (BASE *base));			\
    vclassMETHOD(vcommBaseSEND_EVENT, (BASE *base, vcommEvent *event));	\
    vclassMETHOD(vcommBaseNOTIFY, (BASE *base, vcommEvent *event));	\
    vclassMETHOD(vcommBaseSET_NOTIFY, (BASE *base, NOTIFY noteProc));	\
    vclassMETHOD(vcommBaseSET_DATA, (BASE *base, const void *data));	\
    vclassMETHOD(vcommBaseSET_DEVICE, (BASE *base, void *device));	\
    vclassMETHOD(vcommBaseHALT, (BASE *base));				\
    vclassMETHOD_RET(vcommBaseWAIT, int, (BASE *base, int event,	\
					  vtimestamp *timestamp))

struct vcommBaseClass {
    vcommBASE_CLASS(vcommBaseClass, vcommBase, vcommBaseNoteProc);
};

struct vcommBaseException {
    vexException	 super;
    vcommBase		*base;
    int			 error;
};

/*
 * Abstract Datagram class.
 */

struct vcommDatagram {
    vcommBase		 super;
};

#define vcommDATAGRAM_CLASS(SUPER, DATAGRAM, NOTIFY)			\
    vcommBASE_CLASS(SUPER, DATAGRAM, NOTIFY);				\
    vclassMETHOD_RET(vcommDatagramSEND, size_t, (DATAGRAM *dgram,	\
		     vcommLocator *loc, vcommVector *vector, int num));	\
    vclassMETHOD_RET(vcommDatagramRECEIVE, size_t, (DATAGRAM *dgram,	\
		     vcommLocator *loc, vcommVector *vector, int num))

struct vcommDatagramClass {
    vcommDATAGRAM_CLASS(vcommDatagramClass, vcommDatagram,
			vcommDatagramNoteProc);
};

/*
 * Abstract Stream class.
 */

struct vcommStream {
    vcommBase		 super;
    vcommLocator	*remote;
};

#define vcommSTREAM_CLASS(SUPER, STREAM, NOTIFY)			\
    vcommBASE_CLASS(SUPER, STREAM, NOTIFY);				\
    vclassMETHOD_RET(vcommStreamSEND, size_t, (STREAM *stream,		\
		        vcommVector *vector, int num));			\
    vclassMETHOD_RET(vcommStreamRECEIVE, size_t, (STREAM *stream,	\
			vcommVector *vector, int num))

struct vcommStreamClass {
    vcommSTREAM_CLASS(vcommStreamClass, vcommStream, vcommStreamNoteProc);
};

/*
 * Transport specific classes.
 */

struct vcommTCPStream {
    vcommStream		 super;
};

#define vcommTCP_STREAM_CLASS(SUPER, STREAM, NOTIFY)			\
    vcommSTREAM_CLASS(SUPER, STREAM, NOTIFY)

struct vcommTCPStreamClass {
    vcommTCP_STREAM_CLASS(vcommTCPStreamClass, vcommTCPStream,
			  vcommStreamNoteProc);
};

struct vcommPipeStream {
    vcommStream		 super;
};

#define vcommPIPE_STREAM_CLASS(SUPER, STREAM, NOTIFY)			\
    vcommSTREAM_CLASS(SUPER, STREAM, NOTIFY)

struct vcommPipeStreamClass {
    vcommPIPE_STREAM_CLASS(vcommPipeStreamClass, vcommPipeStream,
			  vcommStreamNoteProc);
};

struct vcommSharedMemoryStream {
    vcommStream		 super;
};

#define vcommSHARED_MEMORY_STREAM_CLASS(SUPER, STREAM, NOTIFY)		\
    vcommSTREAM_CLASS(SUPER, STREAM, NOTIFY)

struct vcommSharedMemoryStreamClass {
    vcommSHARED_MEMORY_STREAM_CLASS(vcommSharedMemoryStreamClass,
				    vcommSharedMemoryStream,
				    vcommStreamNoteProc);
};

struct vcommUDPDatagram {
    vcommDatagram		 super;
};

#define vcommUDP_DATAGRAM_CLASS(SUPER, DATAGRAM, NOTIFY)		\
    vcommDATAGRAM_CLASS(SUPER, DATAGRAM, NOTIFY)

struct vcommUDPDatagramClass {
    vcommUDP_DATAGRAM_CLASS(vcommUDPDatagramClass, vcommUDPDatagram,
			    vcommDatagramNoteProc);
};

struct vcommMailboxDatagram {
    vcommDatagram		 super;
};

#define vcommMAILBOX_DATAGRAM_CLASS(SUPER, DATAGRAM, NOTIFY)		\
    vcommDATAGRAM_CLASS(SUPER, DATAGRAM, NOTIFY)

struct vcommMailboxDatagramClass {
    vcommMAILBOX_DATAGRAM_CLASS(vcommMailboxDatagramClass,
				vcommMailboxDatagram, vcommDatagramNoteProc);
};


vportALIAS(vcommIPLocator, vcommLocator)


vportALIAS(vcommLocalLocator, vcommLocator)


struct vcommTCPLocator {
    vcommIPLocator         super;
};

#define vcommTCP_LOCATOR_CLASS(SUPER, LOCATOR)				 \
    vcommLOCATOR_CLASS(SUPER, LOCATOR)

struct vcommTCPLocatorClass {
    vcommTCP_LOCATOR_CLASS(vcommTCPLocatorClass, vcommTCPLocator);
};


struct vcommPipeLocator {
    vcommLocalLocator         super;
};

#define vcommPIPE_LOCATOR_CLASS(SUPER, LOCATOR)				 \
    vcommLOCATOR_CLASS(SUPER, LOCATOR)

struct vcommPipeLocatorClass {
    vcommPIPE_LOCATOR_CLASS(vcommPipeLocatorClass, vcommPipeLocator);
};


struct vcommSharedMemoryLocator {
    vcommLocator         super;
};

#define vcommSHARED_MEMORY_LOCATOR_CLASS(SUPER, LOCATOR)		 \
    vcommLOCATOR_CLASS(SUPER, LOCATOR)

struct vcommSharedMemoryLocatorClass {
    vcommSHARED_MEMORY_LOCATOR_CLASS(vcommSharedMemoryLocatorClass,
				     vcommSharedMemoryLocator);
};


struct vcommUDPLocator {
    vcommIPLocator         super;
};

#define vcommUDP_LOCATOR_CLASS(SUPER, LOCATOR)				 \
    vcommLOCATOR_CLASS(SUPER, LOCATOR)

struct vcommUDPLocatorClass {
    vcommUDP_LOCATOR_CLASS(vcommUDPLocatorClass, vcommUDPLocator);
};


struct vcommMailboxLocator {
    vcommLocalLocator         super;
};

#define vcommMAILBOX_LOCATOR_CLASS(SUPER, LOCATOR)			 \
    vcommLOCATOR_CLASS(SUPER, LOCATOR)

struct vcommMailboxLocatorClass {
    vcommMAILBOX_LOCATOR_CLASS(vcommMailboxLocatorClass, vcommMailboxLocator);
};


/*************************************************************************
 * Private variable declarations.
 *************************************************************************/

extern vportLINK const vexClass		 _vcommBaseExceptionClass;
extern vportLINK const vname		*_vcommNames[];

/*************************************************************************
 * Private function prototypes.
 *************************************************************************/

void _vcommBaseExceptionERROR(
    void 			*exception,
    va_list			*args
    );

void _vcommBaseExceptionBASE(
    void 			*exception,
    va_list			*args
    );

/*************************************************************************
 * Private function macro definitions.
 *************************************************************************/

/*
 * Event types.
 */

#define vcommInitEvent(e)  ((void)0)
#define vcommDestroyEvent(e)  ((void)0)

#define vcommGetEventType(e)						\
    ((e)->type)

#define vcommSetEventType(e, t)						\
    ((e)->type = (t))

#define vcommGetEventError(e)						\
    ((e)->error)

#define vcommSetEventError(e, r)					\
    ((e)->error = (r))

/*
 * Vector types.
 */

#define vcommGetVectorSize(v)						\
    ((v)->count)

#define vcommSetVectorSize(v, c)					\
    ((v)->count = (c))

#define vcommGetVectorBuffer(v)						\
    ((v)->buffer)

#define vcommSetVectorBuffer(v, b)					\
    ((v)->buffer = (b))

#define vcommSetVector(v, b, c)						\
    ((v)->buffer = (b), (v)->count = (c))

/*
 * Locator objects.
 */

#define vcommGetLocatorObject(l)					\
    vportBASE_OBJECT(l, super)

#define vcommGetLocatorClass(l)						\
    ((vcommLocatorClass *)vobjectGetClass(vcommGetLocatorObject(l)))

#define vcommCreateLocatorOfClass(c)					\
    ((vcommLocator *)vobjectCreateOfClass((vobjectClass *)(c)))

#define vcommCreateLocator()						\
    vcommCreateLocatorOfClass(vcommGetDefaultLocatorClass())

#define vcommInitLocatorOfClass(l, c)					\
    vobjectInitOfClass(vcommGetLocatorObject(l), (vobjectClass *)(c))

#define vcommInitLocator(l)						\
    vcommInitLocatorOfClass((l), vcommGetDefaultLocatorClass())

#define vcommDestroyLocator(l)						\
    vobjectDestroy(vcommGetLocatorObject(l))

#define vcommCopyLocator(l, t)						\
    vobjectCopy(vcommGetLocatorObject(l), vcommGetLocatorObject(t))

#define vcommCopyInitLocator(l, t)					\
    vobjectCopyInit(vcommGetLocatorObject(l), vcommGetLocatorObject(t))

#define vcommCloneLocator(l)						\
    ((vcommLocator *)vobjectClone(vcommGetLocatorObject(l)))

#define vcommLoadLocator(r)						\
    ((vcommLocator *)vobjectLoad(r))

#define vcommStoreLocator(l, r)						\
    vobjectStore(vcommGetLocatorObject(l), r)

#define vcommDumpLocator(l, f)						\
    vobjectDump(vcommGetLocatorObject(l), f)

#define vcommGetLocatorAttribute(l, n)					\
    vobjectGetAttribute(vcommGetLocatorObject(l), n)

#define vcommSetLocatorAttribute(l, n, v)				\
    vobjectSetAttribute(vcommGetLocatorObject(l), n, v)

#define vcommGetLocatorAttributeScalar(l, n)				\
    ((long)vcommGetLocatorAttribute(l, n))

#define vcommSetLocatorAttributeScalar(l, n, v)				\
    vcommSetLocatorAttribute(l, n, (const void *)(v))

#define vcommGetLocatorAttributeScribed(l, n)				\
    vcharScribe((const vchar *)vcommGetLocatorAttribute(l, n))

#define vcommGetLocatorDevice(l)					\
    ((l)->device)

/*
 * Base objects.
 */

#define vcommGetBaseObject(b)						\
    vportBASE_OBJECT(b, super)

#define vcommGetBaseClass(b)						\
    ((vcommBaseClass *)vobjectGetClass(vcommGetBaseObject(b)))

#define vcommCreateBaseOfClass(c)					\
    ((vcommBase *)vobjectCreateOfClass((vobjectClass *)(c)))

#define vcommCreateBase()						\
    vcommCreateBaseOfClass(vcommGetDefaultBaseClass())

#define vcommInitBaseOfClass(b, c)					\
    vobjectInitOfClass(vcommGetBaseObject(b), (vobjectClass *)(c))

#define vcommInitBase(b)						\
    vcommInitBaseOfClass((b), vcommGetDefaultBaseClass())

#define vcommDestroyBase(b)						\
    vobjectDestroy(vcommGetBaseObject(b))

#define vcommCloneBase(b)						\
    ((vcommBase *)vobjectClone(vcommGetBaseObject(b)))

#define vcommLoadBase(r)						\
    ((vcommBase *)vobjectLoad(r))

#define vcommStoreBase(b, r)						\
    vobjectStore(vcommGetBaseObject(b), r)

#define vcommDumpBase(b, f)						\
    vobjectDump(vcommGetBaseObject(b), f)

#define vcommGetBaseAttribute(b, n)					\
    vobjectGetAttribute(vcommGetBaseObject(b), n)

#define vcommSetBaseAttribute(b, n, v)					\
    vobjectSetAttribute(vcommGetBaseObject(b), n, v)

#define vcommGetBaseAttributeScalar(b, n)				\
    ((long)vcommGetBaseAttribute(b, n))

#define vcommSetBaseAttributeScalar(b, n, v)				\
    vcommSetBaseAttribute(b, n, (const void *)(v))

#define vcommGetBaseAttributeScribed(b, n)				\
    vcharScribe((const vchar *)vcommGetBaseAttribute(b, n))

#define vcommCreateBaseLocator(b)					\
    vcommCreateLocatorOfClass(vcommGetBaseLocatorClass(b))

#define vcommGetBaseData(b)						\
    ((b)->data)

#define vcommGetBaseState(b)						\
    ((b)->flags & _vcommSTATE_MASK)

#define vcommSetBaseState(b, s)						\
    ((b)->flags = ((b)->flags & ~_vcommSTATE_MASK) | (s))

#define vcommGetBaseNotify(b)						\
    ((b)->noteProc)

#define vcommGetBaseLocator(b)						\
    ((b)->local)

#define vcommGetBaseDevice(b)						\
    ((b)->device)

/*
 * Base transport exceptions.
 */

#define vcommGetBaseExceptionClass()					\
    (&_vcommBaseExceptionClass)

#define vcommGetBaseException()						\
    ((vcommBaseException *)vexGetExceptionOfClass(&_vcommBaseExceptionClass))

#define vcommGetBaseExceptionError(e)					\
    ((e)->error)

#define vcommGetBaseExceptionBase(e)					\
    ((e)->base)

#define vcommGenerateBaseException(b, e, m)				\
    vexGenerate(&_vcommBaseExceptionClass, _vcommBaseExceptionBASE, b,	\
		_vcommBaseExceptionERROR, e, vexMESSAGE, m, vexNULL)

#define vcommPropagateBaseException(b, e, m)				\
     vexPropagate(&_vcommBaseExceptionClass, _vcommBaseExceptionBASE, b,\
		  _vcommBaseExceptionERROR, e, vexMESSAGE, m, vexNULL)

/*
 * Datagram objects.
 */

#define vcommGetDatagramBase(d)						\
    vportBASE_OBJECT(d, super)

#define vcommGetDatagramClass(d)					\
    ((vcommDatagramClass *)vcommGetBaseClass(vcommGetDatagramBase(d)))

#define vcommCreateDatagramOfClass(c)					\
    ((vcommDatagram *)vcommCreateBaseOfClass((vcommBaseClass *)(c)))

#define vcommCreateDatagram()						\
    vcommCreateDatagramOfClass(vcommGetDefaultDatagramClass())

#define vcommInitDatagramOfClass(d, c)					\
    vcommInitBaseOfClass(vcommGetDatagramBase(d), (vcommBaseClass *)(c))

#define vcommInitDatagram(d)						\
    vcommInitDatagramOfClass((d), vcommGetDefaultDatagramClass())

#define vcommDestroyDatagram(d)						\
    vcommDestroyBase(vcommGetDatagramBase(d))

#define vcommCloneDatagram(d)						\
    ((vcommDatagram *)vcommCloneBase(vcommGetDatagramBase(d)))

#define vcommLoadDatagram(r)						\
    ((vcommDatagram *)vcommLoadBase(r))

#define vcommStoreDatagram(d, r)					\
    vcommStoreBase(vcommGetDatagramBase(d), r)

#define vcommDumpDatagram(d, f)						\
    vcommDumpBase(vcommGetDatagramBase(d), f)

#define vcommGetDatagramAttribute(d, n)					\
    vcommGetBaseAttribute(vcommGetDatagramBase(d), n)

#define vcommSetDatagramAttribute(d, n, v)				\
    vcommSetBaseAttribute(vcommGetDatagramBase(d), n, v)

#define vcommGetDatagramAttributeScalar(d, n)				\
    vcommGetBaseAttributeScalar(vcommGetDatagramBase(d), n)

#define vcommSetDatagramAttributeScalar(d, n, v)			\
    vcommSetBaseAttributeScalar(vcommGetDatagramBase(d), n, v)

#define vcommGetDatagramAttributeScribed(d, n)				\
    vcommGetBaseAttributeScribed(vcommGetDatagramBase(d), n)

#define vcommSetDatagramAttributeScribed(d, n, v)			\
    vcommSetBaseAttributeScribed(vcommGetDatagramBase(d), n, v)

#define vcommGetDatagramData(d)						\
    vcommGetBaseData(vcommGetDatagramBase(d))

#define vcommSetDatagramData(d, a)					\
    vcommSetBaseData(vcommGetDatagramBase(d), (a))

#define vcommEnableDatagram(d)						\
    vcommEnableBase(vcommGetDatagramBase(d))

#define vcommDisableDatagram(d)						\
    vcommDisableBase(vcommGetDatagramBase(d))

#define vcommWaitDatagram(d, e, t)					\
    vcommWaitBase(vcommGetDatagramBase(d), e, t)

#define vcommHaltDatagram(d)						\
    vcommHaltBase(vcommGetDatagramBase(d))

#define vcommGetDatagramState(d)					\
    vcommGetBaseState(vcommGetDatagramBase(d))

#define vcommSetDatagramState(d, s)					\
    vcommSetBaseState(vcommGetDatagramBase(d), s)

#define vcommGetDatagramNotify(d)					\
    (vcommDatagramNoteProc)vcommGetBaseNotify(vcommGetDatagramBase(d))

#define vcommSetDatagramNotify(d, n)					\
    vcommSetBaseNotify(vcommGetDatagramBase(d), (vcommBaseNoteProc)(n))

#define vcommSendDatagramEvent(d, e)					\
    vcommSendBaseEvent(vcommGetDatagramBase(d), e)

#define vcommNotifyDatagram(d, e)					\
    vcommNotifyBase(vcommGetDatagramBase(d), e)

#define vcommGetDatagramLocatorClass(d)					\
    vcommGetBaseLocatorClass(vcommGetDatagramBase(d))

#define vcommSetDatagramLocatorClass(d, c)				\
    vcommSetBaseLocatorClass(vcommGetDatagramBase(d), c)

#define vcommCreateDatagramLocator(d)					\
    vcommCreateBaseLocator(vcommGetDatagramBase(d))

#define vcommGetDatagramLocator(d)					\
    vcommGetBaseLocator(vcommGetDatagramBase(d))

#define vcommGetDatagramDevice(d)					\
    vcommGetBaseDevice(vcommGetDatagramBase(d))

#define vcommSetDatagramDevice(d, e)					\
    vcommSetBaseDevice(vcommGetDatagramBase(d), e)

#define vcommGenerateDatagramException(d, e, m)				\
    vcommGenerateBaseException(vcommGetDatagramBase(d), e, m)

#define vcommPropagateDatagramException(d, e, m)			\
    vcommPropagateBaseException(vcommGetDatagramBase(d), e, m)

/*
 * Stream objects.
 */

#define vcommGetStreamBase(s)						\
    vportBASE_OBJECT(s, super)

#define vcommGetStreamClass(s)						\
    ((vcommStreamClass *)vcommGetBaseClass(vcommGetStreamBase(s)))

#define vcommCreateStreamOfClass(c)					\
    ((vcommStream *)vcommCreateBaseOfClass((vcommBaseClass *)(c)))

#define vcommCreateStream()						\
    vcommCreateStreamOfClass(vcommGetDefaultStreamClass())

#define vcommInitStreamOfClass(s, c)					\
    vcommInitBaseOfClass(vcommGetStreamBase(s), (vcommBaseClass *)(c))

#define vcommInitStream(s)						\
    vcommInitStreamOfClass((s), vcommGetDefaultStreamClass())

#define vcommDestroyStream(s)						\
    vcommDestroyBase(vcommGetStreamBase(s))

#define vcommCloneStream(s)						\
    ((vcommStream *)vcommCloneBase(vcommGetStreamBase(s)))

#define vcommLoadStream(r)						\
    ((vcommStream *)vcommLoadBase(r))

#define vcommStoreStream(s, r)						\
    vcommStoreBase(vcommGetStreamBase(s), r)

#define vcommDumpStream(s, f)						\
    vcommDumpBase(vcommGetStreamBase(s), f)

#define vcommGetStreamAttribute(s, n)					\
    vcommGetBaseAttribute(vcommGetStreamBase(s), n)

#define vcommSetStreamAttribute(s, n, v)				\
    vcommSetBaseAttribute(vcommGetStreamBase(s), n, v)

#define vcommGetStreamAttributeScalar(s, n)				\
    vcommGetBaseAttributeScalar(vcommGetStreamBase(s), n)

#define vcommSetStreamAttributeScalar(s, n, v)				\
    vcommSetBaseAttributeScalar(vcommGetStreamBase(s), n, v)

#define vcommGetStreamAttributeScribed(s, n)				\
    vcommGetBaseAttributeScribed(vcommGetStreamBase(s), n)

#define vcommSetStreamAttributeScribed(s, n, v)				\
    vcommSetBaseAttributeScribed(vcommGetStreamBase(s), n, v)

#define vcommGetStreamData(s)						\
    vcommGetBaseData(vcommGetStreamBase(s))

#define vcommSetStreamData(s, d)					\
    vcommSetBaseData(vcommGetStreamBase(s), (d))

#define vcommEnableStream(s)						\
    vcommEnableBase(vcommGetStreamBase(s))

#define vcommDisableStream(s)						\
    vcommDisableBase(vcommGetStreamBase(s))

#define vcommWaitStream(d, e, t)					\
    vcommWaitBase(vcommGetStreamBase(d), e, t)

#define vcommHaltStream(d)						\
    vcommHaltBase(vcommGetStreamBase(d))

#define vcommGetStreamState(s)						\
    vcommGetBaseState(vcommGetStreamBase(s))

#define vcommSetStreamState(s, t)					\
    vcommSetBaseState(vcommGetStreamBase(s), t)

#define vcommGetStreamNotify(s)						\
    (vcommStreamNoteProc)vcommGetBaseNotify(vcommGetStreamBase(s))

#define vcommSetStreamNotify(s, n)					\
    vcommSetBaseNotify(vcommGetStreamBase(s), (vcommBaseNoteProc)(n))

#define vcommSendStreamEvent(s, e)					\
    vcommSendBaseEvent(vcommGetStreamBase(s), e)

#define vcommNotifyStream(s, e)						\
    vcommNotifyBase(vcommGetStreamBase(s), e)

#define vcommGetStreamLocatorClass(s)					\
    vcommGetBaseLocatorClass(vcommGetStreamBase(s))

#define vcommSetStreamLocatorClass(s, c)				\
    vcommSetBaseLocatorClass(vcommGetStreamBase(s), c)

#define vcommCreateStreamLocator(s)					\
    vcommCreateBaseLocator(vcommGetStreamBase(s))

#define vcommGetStreamLocator(s)					\
    vcommGetBaseLocator(vcommGetStreamBase(s))

#define vcommGetStreamRemoteLocator(s)					\
    ((s)->remote)

#define vcommGetStreamDevice(s)						\
    vcommGetBaseDevice(vcommGetStreamBase(s))

#define vcommSetStreamDevice(s, d)					\
    vcommSetBaseDevice(vcommGetStreamBase(s), d)

#define vcommGenerateStreamException(s, e, m)				\
    vcommGenerateBaseException(vcommGetStreamBase(s), e, m)

#define vcommPropagateStreamException(s, e, m)				\
    vcommPropagateBaseException(vcommGetStreamBase(s), e, m)

/*************************************************************************
 * Private function message definitions.
 *************************************************************************/

/*
 * Locator objects.
 */

#define vcommSetLocatorDevice(l, d)					\
    vclassSend(vcommGetLocatorClass(l), vcommLocatorSET_DEVICE, (l, d))

#define vcommClearLocator(l)                                            \
    vclassSend(vcommGetLocatorClass(l), vcommLocatorCLEAR, (l))

#define vcommCompareLocator(l, m)                                       \
    vclassSend(vcommGetLocatorClass(l), vcommLocatorCOMPARE, (l, m))

/*
 * Base objects.
 */

#define vcommEnableBase(b)						\
    vclassSend(vcommGetBaseClass(b), vcommBaseENABLE, (b))

#define vcommDisableBase(b)						\
    vclassSend(vcommGetBaseClass(b), vcommBaseDISABLE, (b))

#define vcommWaitBase(b, e, t)						\
    vclassSend(vcommGetBaseClass(b), vcommBaseWAIT, (b, e, t))

#define vcommHaltBase(b)						\
    vclassSend(vcommGetBaseClass(b), vcommBaseHALT, (b))

#define vcommSendBaseEvent(b, e)					\
    vclassSend(vcommGetBaseClass(b), vcommBaseSEND_EVENT, (b, e))

#define vcommNotifyBase(b, e)						\
    vclassSend(vcommGetBaseClass(b), vcommBaseNOTIFY, (b, e))

#define vcommSetBaseNotify(b, n)					\
    vclassSend(vcommGetBaseClass(b), vcommBaseSET_NOTIFY, (b, n))

#define vcommSetBaseData(b, d)						\
    vclassSend(vcommGetBaseClass(b), vcommBaseSET_DATA, (b, d))

#define vcommSetBaseDevice(b, d)					\
    vclassSend(vcommGetBaseClass(b), vcommBaseSET_DEVICE, (b, d))

/*
 * Datagram objects.
 */

#define vcommSendDatagram(d, l, v, c)					\
    vclassSend(vcommGetDatagramClass(d), vcommDatagramSEND, (d, l, v, c))

#define vcommReceiveDatagram(d, l, v, c)				\
    vclassSend(vcommGetDatagramClass(d), vcommDatagramRECEIVE, (d, l, v, c))

/*
 * Stream objects.
 */

#define vcommSendStream(s, v, c)					\
    vclassSend(vcommGetStreamClass(s), vcommStreamSEND, (s, v, c))

#define vcommReceiveStream(s, v, c)					\
    vclassSend(vcommGetStreamClass(s), vcommStreamRECEIVE, (s, v, c))


vportEND_CPLUSPLUS_EXTERN_C

#endif

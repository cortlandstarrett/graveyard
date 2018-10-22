/* $Id: vcommchn.h,v 1.4 1997/08/22 20:33:32 dimitri Exp $ */

/************************************************************

    vcommchn.h
    C Interface file for the Old Communication Manager

    (c) Copyright 1991,1992 Visix Software Inc.
    All rights reserved

************************************************************/

#ifndef vcommChannelINCLUDED
#define vcommChannelINCLUDED	1

#ifndef  vportINCLUDED		/* for v*HEADER */
#include <vport.h>
#endif

#ifndef  vstdINCLUDED		/* for vbyte */
#include vstdHEADER
#endif

#ifndef  vcharINCLUDED
#include vcharHEADER
#endif

#ifndef  vresourceINCLUDED
#include vresourceHEADER
#endif

#ifndef  vnameINCLUDED
#include vnameHEADER
#endif

#ifndef  vtimestampINCLUDED
#include vtimestampHEADER
#endif

#ifndef  vexINCLUDED
#include vexHEADER
#endif


vportBEGIN_CPLUSPLUS_EXTERN_C


/*
 * * * * * * * * * PUBLIC CONSTANTS AND MACRO DEFINITIONS * * * * * * * * * *
 */

enum {
	vcommOPEN	= 0,	/**  channel has successfully opened	**/
	vcommCLOSE,		/**  channel has just closed		**/
	vcommINPUT,		/**  input is available on channel	**/
	vcommOUTPUT,		/**  output is possible on channel	**/
	vcommREAD_COMPLETE,	/**  vcommRead() has completed async	**/
	vcommWRITE_COMPLETE,	/**  vcommWrite() has completed async	**/
	vcommEXCEPTION		/**  exceptional condition on channel	**/
};


enum {
	vcommOPTION_SYNCHRONOUS,
	vcommOPTION_INPUT_BUFFER_SIZE,
	vcommOPTION_OUTPUT_BUFFER_SIZE,
	vcommOPTION_REUSEADDR
};


#define	 _vcommADDRESS_CACHE_SIZE	16
#define  _vcommADDRESS_DYNAMIC		0x00000001
#define  _vcommADDRESS_CACHE_VALID	0x00000002
#define  _vcommCHANNEL_OPEN		0x00000001
#define  _vcommCHANNEL_DESTROYING	0x00000002


/*
 * * * * * * * * * PUBLIC TYPE AND STRUCTURE DEFINITIONS * * * * * * * * * *
 */



typedef struct vcommChannel	vcommChannel;	/**  forward declaration **/
typedef struct vcommDriver	vcommDriver;	/**  forward declaration **/


typedef void (*vcommNoteProc)(vcommChannel *channel, int actionCode);


/**  Although these fields appear to be public, they really are not.
 **  go through the vcomm*Address interface.
 **/
typedef struct vcommAddress {
    const vname *transport;	/* what type of transport the address is on */
    const vchar *location;	/* the machine (node) it is located on */
    const vchar *port;		/* the access point within the location */
    unsigned long flags;
    unsigned long driverCache[_vcommADDRESS_CACHE_SIZE/sizeof(long)];
				/* per-driver cached information */
} vcommAddress;


/**  Although these fields appear to be public, they really are not.
 **  go through the vcomm*Channel interface.
 **/
struct vcommChannel {
    vcommDriver		*driver;
    vcommAddress	 local;		/**  copy to set  **/
    vcommAddress	 remote;	/**  copy to set  **/
    vcommNoteProc	 fnNotify;
    void		*clientData;
    void		*driverData;
    unsigned long	 flags;

    int			  nInputQueues;
    int			  nTotalQueuedInput;
    size_t		 *arrayInputBufferLength;
    vbyte		**arrayInputBufferQueue;

    int			  nOutputQueues;
    size_t		 *arrayOutputBufferLength;
    vbyte		 *bufferOutputQueue;
    vbyte		 *bufferOutputBase;
    int			  nMaxOutputQueue;
};


/**  Driver fields are only relevent to driver-writers within the actual
 **  implementation of the driver.
 **/
struct vcommDriver {
    unsigned long	 flags;
    const vname		*name;		/**  of transport  **/

    vcommChannel * (*Listen)(vcommAddress *address, vcommNoteProc fnNotify);
    void	   (*Open)(vcommChannel *channel);
    void	   (*Close)(vcommChannel *channel);
    size_t	   (*Avail)(vcommChannel *channel);
    size_t	   (*Pending)(vcommChannel *channel);
    size_t	   (*Read)(vcommChannel *channel, vbyte *buffer, size_t n);
    size_t	   (*Write)(vcommChannel *channel,vbyte *buffer, size_t n);
    void	   (*Flush)(vcommChannel *channel);
    int		   (*Block)(vcommChannel *channel, vtimestamp timeout);
    int		   (*QueryScalarOption)(vcommChannel *channel,
					int option, int *value);
    int		   (*SuggestScalarOption)(vcommChannel *channel,
					  int option, int value);
};


/*
 * * * * * * * * * * * * * *   Exception Handling  * * * * * * * * * * * * *
 */

/**  vcommException
 **	parent:	vexRootException
 **
 **	Root exception within communication manager
 **	(not used directly)
 **/
typedef  vexException	vcommException;


/**  vcommAddressException
 **  	parent:  vcommException
 **
 **	problem is directly associated with address
 **/
typedef struct vcommAddressException vcommAddressException;


/**  vcommUnknownTransportException
 **	parent: vcommAddressException
 **
 **	unknown Transport in address  (driver not registered)
 **/
typedef  vcommAddressException	vcommUnknownTransportException;


/**  vcommChannelException
 **	parent:  vcommException
 **
 **	problem is directly associated with particular channel
 **	(private class used as placeholder for time being)
 **/
typedef struct  vcommChannelException vcommChannelException;


/**  vcommNotOpenException
 **	parent:  vcommChannelException
 **
 **	operation required channel to be open, but it isnt
 **/
typedef  vcommChannelException  vcommNotOpenException;


/**  vcommReadException
 **	parent:  vcommChannelException
 **
 **	read-oriented error on channel
 **/
typedef  vcommChannelException	vcommReadException;


/**  vcommWriteException
 **	parent:  vcommChannelException
 **
 **	write-oriented error on channel
 **/
typedef  vcommChannelException	vcommWriteException;


/**  vcommUnknownOptionException
 **	parent:  vexArgException
 **
 **	generated when cannot force an option to a value
 **/
typedef  vexArgException  vcommUnknownOptionException;



/**  functions for setting exception fields on vexGenerate
 **/
void			 vcommADDRESS(void *exception, va_list *argList);
void			 vcommCHANNEL(void *exception, va_list *argList);


/**	Exception Query functions
 **/
vcommException			*vcommGetException(void);
vcommAddressException		*vcommGetAddressException(void);
vcommUnknownTransportException	*vcommGetUnknownTransportException(void);
vcommChannelException		*vcommGetChannelException(void);
vcommNotOpenException		*vcommGetNotOpenException(void);
vcommReadException		*vcommGetReadException(void);
vcommWriteException		*vcommGetWriteException(void);

const vexClass			*vcommGetExceptionClass(void);
const vexClass			*vcommGetAddressExceptionClass(void);
const vexClass			*vcommGetUnknownTransportExceptionClass(void);
const vexClass			*vcommGetChannelExceptionClass(void);
const vexClass			*vcommGetNotOpenExceptionClass(void);
const vexClass			*vcommGetReadExceptionClass(void);
const vexClass			*vcommGetWriteExceptionClass(void);


/**	Exception Class Declarations
 **/
extern vportLINK const vexClass	_vcommExceptionClass;
extern vportLINK const vexClass	_vcommAddressExceptionClass;
extern vportLINK const vexClass	_vcommUnknownTransportExceptionClass;
extern vportLINK const vexClass	_vcommChannelExceptionClass;
extern vportLINK const vexClass	_vcommNotOpenExceptionClass;
extern vportLINK const vexClass	_vcommReadExceptionClass;
extern vportLINK const vexClass	_vcommWriteExceptionClass;


/**	Macros for querying exceptions
 **/
#define  vcommGetExceptionClass() 			\
   &_vcommExceptionClass
#define  vcommGetAddressExceptionClass() 		\
   &_vcommAddressExceptionClass
#define  vcommGetUnknownTransportExceptionClass()	\
   &_vcommUnknownTransportExceptionClass
#define  vcommGetChannelExceptionClass() 		\
   &_vcommChannelExceptionClass
#define  vcommGetNotOpenExceptionClass() 		\
   &_vcommNotOpenExceptionClass
#define  vcommGetReadExceptionClass() 			\
   &_vcommReadExceptionClass
#define  vcommGetWriteExceptionClass() 			\
   &_vcommWriteExceptionClass

   
#define	 vcommGetException()				\
  (vcommException *)vexGetExceptionOfClass(&_vcommExceptionClass)
#define	 vcommGetAddressException()			\
  (vcommAddressException *)vexGetExceptionOfClass(&_vcommAddressExceptionClass)
#define	 vcommGetUnknownTransportException()		\
  (vcommUnknownTransportException *)vexGetExceptionOfClass(&_vcommUnknownTransportExceptionClass)
#define	 vcommGetChannelException()			\
  (vcommChannelException *)vexGetExceptionOfClass(&_vcommChannelExceptionClass)
#define	 vcommGetNotOpenException()			\
  (vcommNotOpenException *)vexGetExceptionOfClass(&_vcommNotOpenExceptionClass)
#define	 vcommGetReadException()			\
  (vcommReadException *)vexGetExceptionOfClass(&_vcommReadExceptionClass)
#define	 vcommGetWriteException()			\
  (vcommWriteException *)vexGetExceptionOfClass(&_vcommWriteExceptionClass)


/*
 * * * * * * * * * * * * * * Function Prototypes * * * * * * * * * * * * * * *
 */


void vcommStartup(void);


/**  Driver Management
 **/
vcommDriver    *vcommLookupDriver(const vname *transport);
void		vcommUnregisterDriver(const vname *transport);
void		vcommRegisterDriver(const vname *transport,
				    vcommDriver *driver);

void		vcommInitSocketDriver(void);	/**  dont use anymore  **/
void		vcommRegisterAllDrivers(void);


/**  Address manipulation
 **/
vcommAddress	*vcommCreateAddress(void);
void		 vcommDestroyAddress(vcommAddress *address);
void		 vcommInitAddress(vcommAddress *address);

void		 vcommCopyAddress(vcommAddress *source,
				  vcommAddress *destination);

void		 vcommFormatAddress(vcommAddress *address,
				    vchar	 *string,
				    size_t	  maxlength);
void		 vcommParseAddress(vchar *string, vcommAddress *address);


void vcommSetAddressTransport(vcommAddress *address, const vname *transport);
void vcommSetAddressLocation(vcommAddress *address, const vchar *location);
void vcommSetAddressPort(vcommAddress *address, const vchar *port);
void vcommSetAddressLocationScribed(vcommAddress *address, vscribe *scribe);
void vcommSetAddressPortScribed(vcommAddress *address, vscribe *scribe);

const vname *vcommGetAddressTransport(vcommAddress *address);
const vchar *vcommGetAddressLocation(vcommAddress *address);
const vchar *vcommGetAddressPort(vcommAddress *address);

const vname *vcommGetDefaultTransportName(void);
const vname *vcommGetDefaultLocalTransportName(void);
const vname *vcommGetDefaultRemoteTransportName(void);
const vname *vcommGetInternalTransportName(void);
const vname *vcommGetTcpTransportName(void);
const vname *vcommGetUdpTransportName(void);
const vname *vcommGetUnixTransportName(void);
const vname *vcommGetDdeTransportName(void);
const vname *vcommGetDdpTransportName(void);
const vname *vcommGetNamedPipeTransportName(void);
const vname *vcommGetDECnetTransportName(void);


/**  Address resource functions
 **/
void		 vcommStoreAddress(vcommAddress *a, vresource resource);
vcommAddress	*vcommLoadAddress(vresource resource);



/**  Channel Functions
 **/
vcommChannel	*vcommCreate(void);
void		 vcommDestroy(vcommChannel *channel);
void		 vcommDestroyLater(vcommChannel *channel);

void		 vcommOpen(vcommChannel *address);
void		 vcommClose(vcommChannel *channel);
vcommChannel	*vcommListen(vcommAddress *address, vcommNoteProc fnNotify);

size_t		 vcommAvail(vcommChannel *channel);
size_t		 vcommPending(vcommChannel *channel);
size_t		 vcommRead(vcommChannel *channel, vbyte *buffer, size_t count);
size_t		 vcommWrite(vcommChannel *channel,vbyte *buffer, size_t count);
int		 vcommBlock(vcommChannel *channel, vtimestamp timeout);
void		 vcommFlush(vcommChannel *channel);
int		 vcommQueryScalarOption(vcommChannel *channel,
					int option, int *value);
void		vcommForceScalarOption(vcommChannel  *channel,
				       int option, int value);
int		vcommSuggestScalarOption(vcommChannel  *channel,
					 int option, int value);

vbool		 vcommIsOpen(vcommChannel *channel);

void		 vcommSetNotify(vcommChannel *channel, vcommNoteProc fnNotify);
vcommNoteProc	 vcommGetNotify(vcommChannel *channel);

vcommAddress	*vcommGetLocalAddress(vcommChannel *channel);
vcommAddress	*vcommGetRemoteAddress(vcommChannel *channel);

void		 vcommSetClientData(vcommChannel *channel, void *data);
void		*vcommGetClientData(vcommChannel *channel);

void		 vcommSetDriverData(vcommChannel *channel, void *data);
void		*vcommGetDriverData(vcommChannel *channel);

void		 vcommSetDriver(vcommChannel *channel, vcommDriver *driver);
vcommDriver	*vcommGetDriver(vcommChannel *channel);

size_t		 vcommCountBytesLeftInInputQueue(vcommChannel *channel);
void		 vcommAddInputQueue(vcommChannel *channel,
				    vbyte *buffer,
				    size_t nBytes);
size_t		 vcommFeedInputQueue(vcommChannel *channel,
				     vbyte *buffer,
				     size_t nBytes);

int		 vcommIsValidChannel( vcommChannel *channel );


/*
 * * * * * * * * * * Private Constants * * * * * * * * * *
 */

#define _vcommUSE_DDP		(vportMAC_OS && vport68K_PROCESSOR && vportSYMANTEC_ENVIRONMENT)
#define _vcommUSE_MAC_TCP	vportMAC_OS


/*
 * * * * * * * * * * Private Types * * * * * * * * * *
 */

struct vcommAddressException
{
    vcommException		 exception;
    vcommAddress		*address;
};

struct vcommChannelException
{
    vcommException		 exception;
    vcommChannel		*channel;
};


/*
 * * * * * * * * * * Private Function Prototypes * * * * * * * * * *
 */

vcommAddress *_vcommAllocAddress(void);

#if (_vcommUSE_DDP)
void _vcommDDPShutdown(void);
#endif

#if (_vcommUSE_MAC_TCP)
void _vcommMacTCPShutdown(void);
#endif

/*
 * * * * * * * * * * * * * * * Function MACROs * * * * * * * * * * * * * * *
 */


#define vcommGetDefaultTransportName()				\
	vnameNULL


#define  vcommSetAddressLocation(a, l)				\
  vcommSetAddressLocationScribed(a, ((l) == NULL) ? (vscribe *)NULL : vcharScribe(l))

#define  vcommSetAddressPort(a, p)				\
  vcommSetAddressPortScribed(a, ((p) == NULL) ? (vscribe *)NULL : vcharScribe(p))


#define  vcommGetAddressTransport(a)	((a)->transport)
#define  vcommGetAddressLocation(a)	((a)->location)
#define  vcommGetAddressPort(a)		((a)->port)

#define  vcommGetNotify( c )		((c)->fnNotify)
#define  vcommSetNotify( c, n )		((c)->fnNotify = (n))
#define  vcommGetLocalAddress( c )	(&((c)->local))
#define  vcommGetRemoteAddress( c )	(&((c)->remote))
#define  vcommGetClientData( c )	((c)->clientData)
#define  vcommSetClientData( c, d )	((c)->clientData = (d))

#define  vcommGetDriver( c )		((c)->driver)
#define  vcommSetDriver( c, d )		((c)->driver = (d))
#define  vcommGetDriverData( c )	((c)->driverData)
#define  vcommSetDriverData( c, d )	((c)->driverData = (d))

#define  vcommIsOpen(c)			(((c)->flags & _vcommCHANNEL_OPEN) !=0)
#define	 vcommCountBytesLeftInInputQueue(c)	((c)->nTotalQueuedInput)


vportEND_CPLUSPLUS_EXTERN_C


#endif	 /* #ifndef vcommChannelINCLUDED */


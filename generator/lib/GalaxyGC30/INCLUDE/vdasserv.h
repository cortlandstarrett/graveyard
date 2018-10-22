/* $Id: vdasserv.h,v 1.5 1994/06/16 02:34:08 robert Exp $ */
/************************************************************

    vdasserv.h

    C Interface file for the Service Broker

    (c) Copyright 1994, Visix Software Inc.
    All rights reserved

************************************************************/

#ifndef vdasservINCLUDED	/**----------  vdasservINCLUDED  ----------**/
#define vdasservINCLUDED	(1)

#ifndef  vportINCLUDED
#include  <vport.h>
#endif

#ifndef  vdictINCLUDED
#include  vdictHEADER
#endif
#ifndef  vdatatagINCLUDED
#include  vdatatagHEADER
#endif
#ifndef  vsignatureINCLUDED
#include  vsignatureHEADER
#endif
#ifndef  vsessionINCLUDED
#include  vsessionHEADER
#endif
#ifndef  vserviceINCLUDED
#include  vserviceHEADER
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C

vportALIAS(vdasserv, void)

/*===========================================================================*\
 * * * * * * * * * * *   PUBLIC  FUNCTION  PROTOTYPES  * * * * * * * * * * * *
\*===========================================================================*/

void  vdasservStartup(void);


vscrap  *vdasservCreateAttributeScrap(void);


/*  functions
 */
void  vdasservRegisterService(
	vservice	*service
	);

void  vdasservUnregisterService(
	vservice	*service
	);


/*  signatures
 */
vsignature  *vdasservGetRegisterSignature(void);
vsignature  *vdasservGetUnregisterSignature(void);
vsignature  *vdasservGetMatchSignature(void);


/*  statements
 */
vsessionStatement  *vdasservMakeRegisterStatement(
	vsession	*sessionBroker,
	vscrap		*scrapAttributes
	);

vsessionStatement  *vdasservMakeUnregisterStatement(
	vsession	*sessionBroker,
	vscrap		*scrapAttributes
	);

vsessionStatement  *vdasservMakeMatchStatement(
	vsession	*sessionBroker,
	vscrap		*scrapSpec
	);


vportEND_CPLUSPLUS_EXTERN_C

#endif				/**----------  vdasservINCLUDED  ----------**/

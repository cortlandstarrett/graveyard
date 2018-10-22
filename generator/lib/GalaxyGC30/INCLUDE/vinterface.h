/* $Id: vinterface.h,v 1.12 1997/10/08 17:14:21 robert Exp $ */

/************************************************************

    vinterface.h

    Interface extension to the Class Manager

    (c) Copyright Visix Software Inc.
    All rights reserved

************************************************************/

#ifndef vinterfaceINCLUDED
#define vinterfaceINCLUDED

#ifndef  vportINCLUDED
#include <vport.h>
#endif

#ifndef  vdebugINCLUDED
#include vdebugHEADER
#endif

#ifndef  vexINCLUDED
#include vexHEADER
#endif

#ifndef  vscribeINCLUDED
#include vscribeHEADER
#endif

#ifndef  vcharINCLUDED
#include vcharHEADER
#endif

#ifndef  vnameINCLUDED
#include vnameHEADER
#endif

#if (vportCPLUSPLUS_SOURCE)
#ifndef  vkindINCLUDED
#include vkindHEADER
#endif
#endif /* (vportCPLUSPLUS_SOURCE) */


vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * * * * * * * * * * PUBLIC MACRO DEFINITIONS  * * * * * * * * * *
 */

#define vinterfaceMETHOD(n, a)            vclassMETHOD(n, a)
#define vinterfaceMETHOD_RET(n, t, a)     vclassMETHOD_RET(n, t, a)

/*
 * * * * * * * * * * PUBLIC TYPE DEFINITIONS * * * * * * * * * *
 */

#if (!vportCPLUSPLUS_SOURCE)

#define vinterface		void
#define vinterfaceRoot		vclassRoot

#else /* (vportCPLUSPLUS_SOURCE) */

#define vinterface		vkindInterface
#define vinterfaceRoot		vkindInterface

#endif /* (vportCPLUSPLUS_SOURCE) */


/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */

/*
 * Interface allocation:
 */

vinterface *vinterfaceGetRoot(
    void
    );

vinterface *vinterfaceSpawn(
    vinterface                     *interfac, 
    size_t                          size
    );

void vinterfaceDestroy(
    vinterface                     *interfac
    );


/*
 * Interface attributes:
 */

void vinterfaceDump(
    vinterface                     *interfac,
    FILE                           *stream
    );

void vinterfaceSetName(
    vinterface                     *interfac, 
    const vchar                    *name
    );

void vinterfaceSetNameScribed(
    vinterface                     *interfac, 
    vscribe                        *scribe
    );

vinterface *vinterfaceGetSuper(
    vinterface                     *interfac
    );

const vname *vinterfaceGetName(
    const vinterface               *interfac
    );

/*
 * Interface relationships:
 */

int vinterfaceIsKindOf(
    const vinterface               *interfac,
    const vinterface               *super
    );

/*
 * Interface message sending:
 */

#if 0

void vinterfaceSet(
    vinterface                     *interfac, 
    ...
    );

void vinterfaceSend(
    const vinterface               *interfac,
    ...
    );

void vinterfaceSendSuper(
    const vinterface               *interfac,
    ...
    );

#endif /* 0 */


/*
 * * * * * * * * * * PRIVATE TYPE DEFINITIONS * * * * * * * * * *
 */

#define vinterfaceROOT(INTERFACE)	vclassROOT(INTERFACE)

/*
 * * * * * * * * * * PRIVATE FUNCTION MACRO DEFINITIONS * * * * * * * * * *
 */

#if (!vportCPLUSPLUS_SOURCE)

#define vinterfaceGetRoot()		vclassGetRoot()
#define vinterfaceSpawn(i,s)		vclassSpawn(i,s)
#define vinterfaceDestroy(i)		vclassDestroy(i)

#define vinterfaceDump(i,s)		vclassDump(i,s)
#define vinterfaceSetName(i,n)		vclassSetName(i,n)
#define vinterfaceSetNameScribed(i,n)	vclassSetNameScribed(i,n)
#define vinterfaceGetSuper(i)		vclassGetSuper(i)
#define vinterfaceGetName(i)		vclassGetName(i)
#define vinterfaceIsKindOf(i,s)		vclassIsKindOf(i,s)

#define vinterfaceSet			vclassSet
#define vinterfaceSend			vclassSend
#define vinterfaceSendSuper		vclassSendSuper

#else /* (vportCPLUSPLUS_SOURCE) */

#define vinterfaceSet(i, m, v)			
#define vinterfaceSend(i, m, a)			
#define vinterfaceSendSuper(i, m, a)		

#endif /* (vportCPLUSPLUS_SOURCE) */


vportEND_CPLUSPLUS_EXTERN_C


#endif /* #ifndef vinterfaceINCLUDED */


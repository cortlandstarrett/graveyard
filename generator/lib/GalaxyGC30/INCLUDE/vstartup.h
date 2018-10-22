/* $Id: vstartup.h,v 1.9 1997/05/16 16:21:49 sean Exp $ */

/************************************************************

    vstartup.h

    C Interface file for Galaxy comprehensive start-up

    (c) Copyright Visix Software Inc.
    All rights reserved

************************************************************/

#ifndef vstartupINCLUDED
#define vstartupINCLUDED

#ifndef vportINCLUDED
#include <vport.h>
#endif

#ifndef vnameINCLUDED
#include vnameHEADER
#endif

#ifndef vmoduleINCLUDED
#include vmoduleHEADER
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C

/*
 * * * * * * * * * * * * * PUBLIC TYPES * * * * * * * * * * * * * 
 */

typedef void 	(*vstartupFunction)(void);

/*
 * * * * * * * * * * PUBLIC FUNCTION PROTOTYPES * * * * * * * * * *
 */

void vstartup(
    int                             argc,
    char                          **argv
    );

void vstartupAll(
    int                             argc,
    char                          **argv
    );

void vstartupMinimal(
    int                             argc,
    char                          **argv
    );

void vstartupDelayed(
    int                             argc,
    char                          **argv
    );

void vstartupPrefs(
    int                             argc,
    char                          **argv
    );

void vstartupRegisterClassStartup(
    const vname			   *classPrefix,
    vstartupFunction		    startupFunction
    );

vstartupFunction vstartupGetClassStartup(
    const vname			   *classPrefix
    );

void vstartupRegisterModule(
    vmodule			   *module
    );

/*
 * * * * * * * * * * PRIVATE FUNCTION PROTOTYPES * * * * * * * * * *
 */

void _vstartupAll(
    int                             argc,
    char                          **argv
    );

void _vstartupMinimal(
    int                             argc,
    char                          **argv
    );

void _vstartupDelayed(
    int                             argc,
    char                          **argv
    );

void _vstartupPrefs(
    int                             argc,
    char                          **argv
    );

void _vstartupStartup(
    void
    );

/*
 * * * * * * * * * * PRIVATE MACRO DEFINITIONS * * * * * * * * * *
 */


#if (!vportCPLUSPLUS_SOURCE)

#define vstartup(c,v)		vstartupPrefs(c,v)

#define vstartupAll(c,v)	\
    _vstartupAll(c,v)
#define vstartupMinimal(c,v)	\
    _vstartupMinimal(c,v)
#define vstartupDelayed(c,v)	\
    _vstartupDelayed(c,v)
#define vstartupPrefs(c,v)	\
    _vstartupPrefs(c,v)

#else /* (vportCPLUSPLUS_SOURCE) */

#if (vportSUPPRESS_STARTUP)

#define vstartup(c,v)		vstartupAll(c,v)

#else /* (!vportSUPPRESS_STARTUP) */

#define vstartup(c,v)		vstartupMinimal(c,v)

#endif /* (!vportSUPPRESS_STARTUP) */

#define vstartupAll(c,v)	\
    { _vstartupAll(c,v); vloadable::Startup(); }
#define vstartupMinimal(c,v)	\
    { _vstartupMinimal(c,v); vloadable::Startup(); }
#define vstartupDelayed(c,v)	\
    { _vstartupDelayed(c,v); vloadable::Startup(); }

#endif /* (vportCPLUSPLUS_SOURCE) */


vportEND_CPLUSPLUS_EXTERN_C

#endif


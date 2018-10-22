/* $Id: prefs.h,v 1.1 1994/10/19 00:50:49 gregt Exp $ */
/* prefs
 *
 * header file for preferences confirm
 */

#ifndef vportINCLUDED
#include <vport.h>
#endif

#ifndef vconfirmINCLUDED
#include vconfirmHEADER
#endif

void prefsOpen(
    vconfirm *conf
    );

void prefsSetup(
    vconfirm *conf
    );

void prefsShutdown(
    vconfirm *conf
    );

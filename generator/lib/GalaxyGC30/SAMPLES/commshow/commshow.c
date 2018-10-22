/* $Id: commshow.c,v 1.3 1997/02/20 18:31:09 david Exp $ */
 
/*
 * The following Sample Code is provided for your reference purposes in
 * connection with your use of the Galaxy Application Environment (TM) software
 * product which you have licensed from Visix Software, Inc. ("Visix").
 * The Sample code is provided to you without any warranty of any kind
 * whatsoever and you agree to be responsible for the use and/or incorporation
 * of the Sample Code into any software product you develop. You agree to fully
 * and completely indemnify and hold Visix harmless from any and all loss,
 * claim, liability or damages with respect to your use of the Sample Code.  
 *
 * Subject to the foregoing, you are permitted to copy, modify, and distribute
 * the Sample Code for any purpose and without fee, provided that (i) a
 * copyright notice in the in the form of "Copyright 1992,93 Visix Software
 * Inc., 11440 Commerce Park Drive, Reston, VA  22091. All Rights Reserved"
 * appears in all copies, (ii) both the copyright notice and this permission
 * notice appear in supporting documentation and (iii) you are a valid
 * licensee of Galaxy Application Environment.
 */

#ifndef vportINCLUDED
#include <vport.h>
#endif
 
#ifndef vstdlibINCLUDED
#include vstdlibHEADER
#endif

#ifndef vstartupINCLUDED
#include vstartupHEADER
#endif

#ifndef veventINCLUDED
#include veventHEADER
#endif

#ifndef _commtestMainINCLUDED
#include "main.h"
#endif

/*
 * Global vars
 */

vcolor *_commtestGreen;

int main(int argc, char **argv)
{
    vstartup(argc, argv);
    
    _mainStartUp();

    veventProcess();
    
    _mainShutDown();

    exit(EXIT_SUCCESS);
    return(EXIT_FAILURE);
}

/******************************************************************************
*	$Header: /visix/vsx/arch/src/vtutor2/RCS/command.c,v 1.3 1993/12/07 05:12:35 jim Exp $
*
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
* copyright notice in the in the form of "Copyright 1992 Visix Software Inc.,
* 11440 Commerce Park Drive, Reston, VA  22091. All Rights Reserved" appears
* in all copies, (ii) both the copyright notice and this permission notice
* appear in supporting documentation and (iii) you are a valid licensee of
* Galaxy Application Environment.
*
*       command.c
*
*       Command manager helper functions.
*
*       (C) Copyright 1992 Visix Software Inc.
*           All Rights Reserved
*
******************************************************************************/

#include <vport.h> /* for v*HEADER */

/* Galaxy includes */
#include vclassHEADER
#include vclientHEADER
#include vcommandHEADER
#include vdictHEADER
#include vnameHEADER
#include vstrHEADER

/* Application includes */
#include "command.h"

/**********************************************************************/
/*                    Private variables                               */
/**********************************************************************/

/*********************************************************************/
/*                Private functions                                  */
/*********************************************************************/

/***********************************************************************/
/*                Public functions                                     */
/***********************************************************************/

/*
 *  commandCreateCommandDict
 *
 *  Create and initialize a command dictionary.
 *  The caller is responsible for freeing the dictionary.
 *
 */

vdict *commandCreateCommandDict (commandInitializer *commands, 
				 vcommandSelectorClass *selectorClass)

{

  commandInitializer  *selectScan;
  vcommandSelector    *selector;
  vdict               *commandDict = vdictCreate (vnameHash);

  for (selectScan = commands; selectScan->tag != NULL; selectScan++) {
    selector = vcommandCreateSelectorOfClass (selectorClass);
    vcommandSetSelector (selector, selectScan->value);
    vdictStore (commandDict, 
		vnameInternGlobalLiteral (selectScan->tag), 
		selector);
  }

  return commandDict;

}

/*
 *  commandCreateStateDict
 *
 *  Create and initialize a state dictionary.  Ownership of the
 *  dictionary is turned over to the caller.
 *
 */

vdict *commandCreateStateDict (commandInitializer *states)

{

  vdict  *stateDict = vdictCreate (vnameHash);

  while (states->tag != NULL) {
    vdictStore (stateDict,
		vnameInternGlobalLiteral (states->tag),
		states->value ? vname_Enabled : vname_Disabled);
    states++;
  }

  return stateDict;

}

/*
 *  commandCreateKeyDict
 *
 *  Create and initialize a key dictionary.  Ownership of the
 *  dictionary is turned over to the caller.
 *
 */

vdict *commandCreateKeyDict (commandInitializer *keys)

{

  vdict       *keyDict = vdictCreate (vnameHash);
  vcommandKey *key;

  while (keys->tag != NULL) {
    if (keys->key != 0) {
      key = vcommandCreateKey ();
      vcommandAddKeyStroke (key, keys->key);
      vdictStore (keyDict, vnameInternGlobalLiteral (keys->tag), key);
    }
    keys++;
  }

  return keyDict;

}

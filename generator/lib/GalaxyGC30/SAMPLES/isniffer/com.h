/* $Id: com.h,v 1.1 1994/08/19 00:03:38 simone Exp $ */
/****************************************************************************
 *                (c) Copyright 1991-1994 Visix Software, Inc.              *
 *                           All rights reserved.                           *
 * The following Sample Code is provided for your reference purposes in     *
 * connection with your use of the Galaxy Application Environment (TM)      *
 * software product which you have licensed from Visix Software, Inc.       *
 * ("Visix"). The Sample code is provided to you without any warranty of any*
 * kind and you agree to be responsible for the use and/or incorporation    *
 * of the Sample Code into any software product you develop. You agree to   *
 * fully and completely indemnify and hold Visix harmless from any and all  *
 * loss, claim, liability or damages with respect to your use of the Sample *
 * Code.                                                                    *
 *                                                                          *
 * Subject to the foregoing, you are permitted to copy, modify, and         *
 * distribute the Sample Code for any purpose, and without fee, provided    *
 * that (i) a copyright notice in the in the form of "Copyright 1992 Visix  *
 * Software Inc., 11440 Commerce Park Drive, Reston, VA  22091. All Rights  *
 * Reserved" appears in all copies, (ii) both the copyright notice and this *
 * permission notice appear in all supporting documentation and (iii) you   *
 * are a valid licensee of The Galaxy Application Environment.              *
 *                                                                          *
 ****************************************************************************
 *                                                                          *
 * Description:                                                             *
 *     This module provides a simple mechanism for "passing around a command*
 *     space" to be filled in with commands. This allows modules to         *
 *     encapsulate their command structures and definitions eventhough the  *
 *     user interface triggers for these commands belong to another module. *
 *     Used by the isnoop application.                                      *
 *                                                                          *
 * Modification History:                                                    *
 *     o 12-11-93: created for galaxy 2.0 (ssmc)                            *
 *                                                                          *
 * Special Usage Notes:                                                     *
 *     o                                                                    *
 *                                                                          *
 * Text Editor Formatting:                                                  *
 *     Symantec: Tab(8), Font(Any Fixed Width)                              *
 *     Emacs: see end of file for info                                      *
 *                                                                          *
 ****************************************************************************
 */

#ifndef commandINCLUDED
#define commandINCLUDED 1

#ifndef vportINCLUDED
#include <vport.h>
#endif

#ifndef vkeyINCLUDED
#include vkeyHEADER
#endif

#ifndef vdictINCLUDED
#include vdictHEADER
#endif

#ifndef vcommandINCLUDED
#include vcommandHEADER
#endif


typedef struct appCmd {
  int		name;		/* index into global application name table */
  vbool		state;		/* TRUE if have state bindings */
  vbool		statevalue;	/* state value (only checked if state TRUE) */
  vkeyStroke	keystroke;	/* associated keystroke or vkeyNULL_STROKE */
}appCmd;
  /* Generic structure used for both function and selector commands. The
       name, state, and keystroke fields *must* be initialized! */


typedef struct appFunctionCmd  {
  appCmd	cmd;
  int	      (*issue)(vcommandFunction*, vdict*);
  int	      (*query)(vcommandFunction*, vdict*);
}appFunctionCmd;
  /* Use to attach function commands to a command space. The command can
       have either or both issue and query functions defined. */


typedef struct appSelectorCmd  {
  appCmd	cmd;
  int		selector;
}appSelectorCmd;
  /* Use to attach selector commands to a command space. The selector
     field is (surprise) the command's selector identifier. */



typedef struct appCommandSpace {
  vcommandSpace	*space;
  vdict		*cmds;
  vdict		*keys;
  vdict		*state;
  vbool		 owned;
}appCommandSpace;
  /* This structure is generally used as a temporary holder for the 3 
     dictionaries associated with a command space (command definition,
     key binding, and state binding). it can however, be stored and used
     later to synchronize the key and/or state bindings for command queries.
     (esp true for menu command queries). With exception of the state 
     dictionary, commit clears all dictionaries that weren't attached to 
     the command space (ie. the empty ones). */



void appInitCommandSpaceDescription(vcommandSpace*, appCommandSpace*);
  /* Initialize our command space description structure for use. this
       creates 3 dictionaries and associates the command space with the
       description. */


void appDestroyCommandSpaceDescription(appCommandSpace*);
  /* Cleanup after init. Since ownership of all the dictionaries is
       transferred to the command space (in commit) there's usually
       no reason to use this call. however, if a description is not
       commited after it's been initialized, this routine will cleanup
       the 3 dictionaries -- it does NOT destroy the command space */


void appAddSelectorsToCommandSpaceDescription(appCommandSpace*, 
	             const appSelectorCmd*, const vcommandSelectorClass*);
  /* Add one or more selector commands to a command space description. the 
       array of selectorCmds must be terminated with a "null entry," namely 
       an entry who's name index is -1 */


void appAddFunctionsToCommandSpaceDescription(appCommandSpace*,
                      const appFunctionCmd*);
  /* Add one or more function commands to a command space description. the
       array of functionCmds must be terminated with a "null entry," namely
       an entry who's name index is -1 */


void appAddUnivFunctionToCommandSpaceDescription(appCommandSpace*,
                const vname*, vcommandFunction*, vkeyStroke);
  /* Convenience function for adding to a command space description function 
       commands that are always active  (for example, the commands
       "quit" or "help" might always be available). */


void appCommitCommandSpaceDescription(appCommandSpace*);
  /* Commit the command space description dictionaries to the command space.
       This adds the dictionaries to the command space. On exit the user
       can examine the command description structure to find out which 
       dictionaries where actually added (empty dictionaries are not added
       but are destroyed and their fields set to NULL).
       For commands with changing state bindings, it might be a good idea
       to keep track of the state bindings dictionary. ui objects such as
       menus depend on the state-bindings dictionary being up-to-date since
       they are only tagged "dirty" by the misc "propagateChange" routines,
       and depend on the query mechanism to determine their states when
       necessary (ie. when they're next popped down) */


/* commandINCLUDED */
#endif

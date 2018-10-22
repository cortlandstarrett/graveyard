/* $Id: com.c,v 1.1 1994/08/19 00:07:35 simone Exp $ */
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
 *     This module provides a simple mechanism for "passing around a com-   *
 *     mand space" to be filled in with commands. This allows modules to    *
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

/* for v*HEADER */
#include <vport.h>

/* ANSI headers */
#include vstdioHEADER
#include vstdlibHEADER

/* Galaxy headers */
#include vmemHEADER
#include vdebugHEADER
#include vexHEADER
#include vcharHEADER
#include vnameHEADER
#include vdictHEADER
#include vkeyHEADER
#include vcommandHEADER

/* Our headers */
#include "names.h"
#include "com.h"


/* Our debug tag for the vdebug manager */
#if vdebugDEBUG
static const char *const _moduleTag = "commands";
#define vdebugTAG _moduleTag
#endif

/*
 *+------------------------------------------------------------------------+
 * private routines: generic key and state bindings
 *+------------------------------------------------------------------------+
 */

/*
 * static void addBindings()
 *   add the given command's equiv keystroke and/or state to the approp
 *   command space dictionary
 */
static void
addBindings(vcommandSpace *space, register const appCmd *cmd, vdict *kdict, 
	    vdict *sdict)
{
  const vname	    *tag;
  vcommandKey	    *key;

  tag = appName(cmd->name);

  if (cmd->keystroke!=vkeyNULL_STROKE){
    key = vcommandCreateKey();
    vcommandAddKeyStroke(key, cmd->keystroke);
    vdictStore(kdict, tag, key);
  }
  if (cmd->state)
    vdictStore(sdict, tag, 
	       cmd->statevalue ? vname_Enabled : vname_Disabled);
  return;
}



/*
 * static void validate()
 *  make sure the parameter app-command-space is valid (was initialized
 *  with appInitCommandsSpace). only defined if debugging.
 */
#if vdebugDEBUG
#define validate(as,m) \
  vdebugIF((!as || !as->space || !as->cmds || !as->keys || !as->state), \
	   vexGenerate(vexGetArgNullClass(), vexMESSAGE, m, vexERRNO, 0,\
           vexNULL))
#else
#define validate(as,m)
#endif




/*
 *+------------------------------------------------------------------------+
 * exported routines:
 *+------------------------------------------------------------------------+
 */

/* 
 * void appInitCommandSpaceDescription()
 *   purpose: initialize the given appCommandSpace structure. this 
 *	      associates a specific command space with a set of 3
 *	      dictionaries (command definitions, key bindings, and
 *	      state bindings). until "taggable dictionaries" are 
 *	      added to the command manager, these dictionaries should
 *	      be filled in with all the space's information. then
 *	      call appCommitCommandDictsToSpace to actually attach
 *	      the dictionaries to the command space. the caller can later
 *	      retrieve any of the three dictionaries from a description
 *	      structure or from the space itself (esp. state dictionary) 
 *	      to synchronize with the ui.
 *   accepts: -> vcommandSpace*, the owning command space
 *	      -> appCommandSpace*, the command space description
 *   returns: <- void
 *   errors : (only debug) /arg/null - bad arguments
 */
void
appInitCommandSpaceDescription(vcommandSpace *space, appCommandSpace *aspace)
{
  /* debug only - validate input */
  vdebugIF((!space || !aspace), vexGenerate(vexGetArgNullClass(), vexMESSAGE,
           "init description: NULL argument(s)!", vexERRNO, 0, vexNULL));

  aspace->space = space;

 /* we own the dictionaries */
  aspace->owned = TRUE;

  /* assume we've got 'em all */
  aspace->cmds  = vdictCreate(vnameHash); /* command-definitions */
  aspace->keys  = vdictCreate(vnameHash); /* key-bindings */
  aspace->state = vdictCreate(vnameHash); /* state-bindings */

  return;
}





/* 
 * void appDestroyCommandSpaceDescription()
 *   purpose: cleanup after appInitCommandDicts. usually only called
 *	      if something has failed between initialization and 
 *	      commiting the command dicts to the space (ie. if an
 *	      exception has occured and the caller wants to cleanup).
 *	      really shouldn't be called otherwise although no harm
 *	      in doing so.
 *   accepts:  -> appCommandSpace*, the command space description
 *   returns: <- void
 *   errors : (only debug) /arg/null - bad arguments
 */void
appDestroyCommandSpaceDescription(appCommandSpace *aspace)
{
  /* debug only - validate input */
  vdebugIF((!aspace), vexGenerate(vexGetArgNullClass(), vexMESSAGE,
           "destroy description: NULL argument(s)!", vexERRNO, 0, vexNULL));

  /* nuke if it hasn't been commited to the command space */
  if (aspace->owned && aspace->cmds)
    vdictDestroy(aspace->cmds);
  if (aspace->owned && aspace->keys)
    vdictDestroy(aspace->keys);
  if (aspace->owned && aspace->state)
    vdictDestroy(aspace->state);

  return;
}





/* 
 * void appAddSelectorsToCommandSpaceDescription()
 *   purpose: adds a bunch o' selector commands to a given command space
 *	      description . selector commands require a selector class 
 *	      to be properly added. 
 *   accepts: -> appCommandSpace*, command space description
 *	      -> const appSelectorCmd*, selector command descriptions
 *	      -> const void *, the selector command class
 *   returns: <- void
 *   errors : (only debug) /arg/null - bad arguments
 */
void
appAddSelectorsToCommandSpaceDescription(appCommandSpace *aspace, 
	      const appSelectorCmd *cmds, const vcommandSelectorClass *clas)
{
  vdict			   	*cdict, *kdict, *sdict;
  vcommandSelector	   	*com;
  register const appSelectorCmd *scan;

  /* debug only - validate input */
  validate(aspace, "add selectors: NULL argument(s)!");
  vdebugIF((!cmds || !clas), vexGenerate(vexGetArgNullClass(), vexMESSAGE,
           "add selectors: NULL cmds or class argument", vexERRNO, 0, 
            vexNULL));

  /* register temps */
  cdict = aspace->cmds;
  kdict = aspace->keys;
  sdict = aspace->state;

  /* update space dictionaries */
  for (scan=cmds; scan->cmd.name>=0; scan++) {
    com = vcommandCreateSelectorOfClass(clas);
    vcommandSetSelector(com, scan->selector);
    vdictStore(cdict, appName(scan->cmd.name), com);
    addBindings(aspace->space, &scan->cmd, kdict, sdict);
  }

  return;
}





/* 
 * void appAddFunctionsToCommandSpaceDescription()
 *   purpose: adds a bunch o' function commands to a given command space
 *	      description. functions can define both issue and query
 *	      methods.
 *   accepts: -> appCommandSpace*, command space description
 *	      -> const appFunctionCmd*, function command description
 *   returns: <- void
 *   errors : (only debug) /arg/null - bad arguments
 */
void
appAddFunctionsToCommandSpaceDescription(appCommandSpace *aspace, 
			      const appFunctionCmd *cmds)
{
  vdict			   	*cdict, *kdict, *sdict;
  vcommandFunction	   	*com;
  register const appFunctionCmd *scan;

  /* debug only - validate input */
  validate(aspace, "add functions: NULL argument(s)!");
  vdebugIF((!cmds), vexGenerate(vexGetArgNullClass(), vexMESSAGE,
          "add functions: NULL cmds argument!", vexERRNO, 0, vexNULL));

  /* register temps */
  cdict = aspace->cmds;
  kdict = aspace->keys;
  sdict = aspace->state;

  /* update space dictionaries */
  for (scan=cmds; scan->cmd.name>=0; scan++) {
    if (scan->issue || scan->query) {
      com = vcommandCreateFunction();
      if (scan->issue)
	vcommandSetFunctionIssue(com, scan->issue);
      if (scan->query)
	vcommandSetFunctionQuery(com, scan->query);
      vdictStore(cdict, appName(scan->cmd.name), com);
    }
    addBindings(aspace->space, &scan->cmd, kdict, sdict);
  }

  return;
}





/* 
 * void appAddUnivFunctionToCommandSpaceDescription()
 *   purpose: adds a single function command to a given command space
 *	      description. a universal command is assume to always be
 *            active (eg. "quit" or "help").
 *   accepts: -> appCommandSpace*, command space description
 *            -> const vname *, the command's global name identifier
 *	      -> vcommandFunction*, the function command
 *            -> vkeyStroke, optional keystroke binding
 *   returns: <- void
 *   errors : (only debug) /arg/null - bad arguments
 */
void
appAddUnivFunctionToCommandSpaceDescription(appCommandSpace *aspace,
         const vname *tag, vcommandFunction *com, vkeyStroke keystroke)
{
  /* debug only - validate input */
  validate(aspace, "add univ functions: NULL argument(s)!");
  vdebugIF((!com || !tag), vexGenerate(vexGetArgNullClass(), vexMESSAGE,
           "add univ functions: NULL command or tag", vexERRNO, 0, 
            vexNULL));


  /* add to space command definition dictionary */
  vdictStore(aspace->cmds, tag, com);

  /* add key binding if applicable */
  if (keystroke!=vkeyNULL_STROKE) {
    vcommandKey *key = vcommandCreateKey();
    vcommandAddKeyStroke(key, keystroke);
    vdictStore(aspace->keys, tag, key);
  }

  return;
}






/* 
 * void appCommitCommandSpaceDescription()
 *   purpose: adds the misc dictionaries (command definition, key
 *	      bindings, and state bindings) to the command space 
 *	      associated with the description. Note: with the 
 *	      exception of the state dictionary, a dictionary
 *	      is only added if it contains information; otherwise
 *	      the dictionary is destroyed and it's description 
 *	      reference set to NULL.
 *   accepts: -> appCommandSpace*, command space description
 *   returns: <- void
 *   errors : (only debug) /arg/null - bad arguments
 */
void
appCommitCommandSpaceDescription(appCommandSpace *aspace)
{
  /* make sure init was used */
  validate(aspace, "commit space: NULL argument(s)!");

  /* attach to space if something defined */
  if (vdictGetSize(aspace->cmds)>0)
    vcommandAddSpaceDictOwned(aspace->space, vname_Command, aspace->cmds);
  else {vdictDestroy(aspace->cmds), aspace->cmds = NULL;}

  /* ditto */
  if (vdictGetSize(aspace->keys)>0)
    vcommandAddSpaceDictOwned(aspace->space, vname_Key, aspace->keys);
  else {vdictDestroy(aspace->keys), aspace->keys = NULL;}

  /* we always attach the state dictionary st user can update it at
   * later points in program (a requirement for menus!)*/
  vcommandAddSpaceDictOwned(aspace->space, vname_State, aspace->state);


  /* we don't own dictionaries anymore */
  aspace->owned = FALSE;
  return;
}



/*
  +-------------------------------------------------------------------------+
   misc formatting information for (emacs) in c-mode
  +-------------------------------------------------------------------------+
 */

/*
 * Local Variables:
 * c-indent-level:2
 * c-continued-statement-offset:2
 * c-brace-offset:0
 * c-brace-imaginary-offset:0
 * c-argdecl-indent:5
 * c-label-offset:0
 * c-tab-always-indent:nil
 * End:
 */

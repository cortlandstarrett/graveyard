/* $Id: help.c,v 1.1 1994/08/19 00:07:58 simone Exp $ */
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
 *                                                                          *
 ****************************************************************************
 */

/* for v*HEADER */
#include <vport.h>

/* ANSI headers */
#include vstdioHEADER
#include vstdlibHEADER

/* Galaxy headers */
#include vdebugHEADER
#include vexHEADER
#include vmemHEADER
#include vcharHEADER
#include vstrHEADER
#include vnameHEADER
#include vdictHEADER
#include vresourceHEADER
#include vclassHEADER
#include vstdHEADER

#include vcommandHEADER
#include vwindowHEADER
#include vdialogHEADER


/* Our Headers */
#include "names.h"
#include "com.h"
#include "isnf.h"
#include "help.h"

/* Define our debug tag for vdebug manager */
#if vdebugDEBUG
static const char *const _moduleTag = "help";
#define vdebugTAG _moduleTag
#endif


/*
 *+------------------------------------------------------------------------+
 * private constants, variables, prototypes
 *+------------------------------------------------------------------------+
 */

enum {
  comHELP_OVERVIEW,
  comHELP_VIEWER
};

static appSelectorCmd helpcmds[]= {
/*  {{appNAME_ACT_HELP,       0,0, vkeyNULL_STROKE}, comHELP_OVERVIEW},*/
  {{appNAME_ACT_HELP_VIEWER,0,0, vkeyNULL_STROKE}, comHELP_VIEWER},
  {{-1}}
};

static int 			 help(vcommandSelector*,vdict*);
static vcommandSelectorClass 	*getHelpClass(void);


/*
 *+------------------------------------------------------------------------+
 * exported routines
 *+------------------------------------------------------------------------+
 */

void
isnfStartupHelp(isnifferApp *app)
{
  vresource res;

  vdebugIF(!app, vexGenerate(vexGetArgNullClass(), vexMESSAGE,
           "init help: NULL app ref!", vexERRNO, 0, vexNULL));

  /* if missing dialogues, disable the help commands */
  if (!vresourceTestGet(app->resources, appname_HelpAct, &res)) {
    helpcmds[0].cmd.state = TRUE;
    helpcmds[1].cmd.state = TRUE;
  }

  /* add help commands */
  appAddSelectorsToCommandSpaceDescription(isnfGetCommandSpaceDescription(), 
                            helpcmds, getHelpClass());
  return;
}

/*
 *+------------------------------------------------------------------------+
 * private routines
 *+------------------------------------------------------------------------+
 */

static vcommandSelectorClass*
getHelpClass(void)
{
  static vcommandSelectorClass *helpclass = NULL;

  if (!helpclass) {
    register vcommandSelectorClass *clas;
    clas = vclassReproduce(vobjectGetCommandClass());
    vclassSet(clas, vcommandISSUE, help);
    helpclass = clas;
  }
  return helpclass;
}


static int
help(vcommandSelector *com, vdict *context)
{
  return vTRUE;
}


/*
  +-------------------------------------------------------------------------+
   MISC formatting information for emacs in c-mode
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

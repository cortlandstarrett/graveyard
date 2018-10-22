/* $Id: utils.c,v 1.1 1994/08/19 00:08:05 simone Exp $ */
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
#include vresourceHEADER

#include vwindowHEADER
#include vdialogHEADER
#include vnoticeHEADER

/* Our headers */
#include "names.h"
#include "isnf.h"
#include "utils.h"


/* Define our debug tag for vdebug manager */
#if vdebugDEBUG
static const char *const _moduleTag = "utils";
#define vdebugTAG _moduleTag
#endif


/*
 *+------------------------------------------------------------------------+
 * private constants, variables, prototypes
 *+------------------------------------------------------------------------+
 */

typedef struct askinfo {
  askInvoker	invoker;
  void		*data;
}askinfo;

static void	placeNotice(vnotice*,vdialog*);
static int 	unblockApp(vnotice*,vevent*);
static int	doYes(vnotice*,vevent*);
static int	doNo(vnotice*,vevent*);
static int	doCancel(vnotice*,vevent*);


/*
 *+------------------------------------------------------------------------+
 * exported routines
 *+------------------------------------------------------------------------+
 */

/* 
 * void isnfInformUser()
 *   purpose: display an information notice to user. because all galaxy
 * 	      notices are modal this forces the user to dismiss the dialog
 *	      before continuing work -- not the desired behavior since
 *	      information messages aren't critical but hopefully this 
 *	      restriction will be soon removed from the notice manager.
 *   accepts: -> int, the message (index into app's message strings)
 *	      -> vdialog*, the notice should be placed with respect
 *		 to this dialog. if NULL uses the requestor dialog.
 *   returns: <- void
 */
void
isnfInformUser(int what, vdialog *wrt)
{
  register isnifferApp 	*app= isnfGet();
  vstr			*str;
  register vnotice 	*notice;

  /* if not loaded yet, do so now */
  notice = app->infoNotice;
  if (!notice) {
    vresource res;
    res = vresourceGet(app->resources, appname_InfoNotice);
    app->infoNotice = notice = vnoticeLoad(res);
    if (!app->noticeIcon) {
      res = vresourceGet(app->resources, appname_NoticeIcon);
      app->noticeIcon = vimageLoad(res);
    }
    vnoticeSetIcon(notice, app->noticeIcon);
    vnoticeSetYesHook(notice, unblockApp);
    vnoticeSetCancelHook(notice, unblockApp);
    vnoticeSetNoHook(notice, unblockApp);
  }

  /* position notice */
  placeNotice(notice, wrt);


  /* reflect message */
  str = vresourceGetStringAt(app->messages, what);
  vnoticeSetText(notice, str);
  vstrDestroy(str);

  /* open (we block the application to visually emphasize the mode) */
  vwindowUnblock(vnoticeGetWindow(notice));
  vnoticeOpen(notice);
  isnfBlock(vnoticeGetDialog(notice));
  return;
}





/*
 * void isnfAskUser()
 *   purpose: display an question notice to user and wait for response.
 *	      the user's response is transmitted to the caller through
 *	      the provided "askInvoker" callback.
 *   accepts: -> int, the message (index into app's message strings)
 *	      -> int, TRUE if want a cancel button in notice
 *	      -> askInvoker, the callback for responses
 *	      -> void*, user definable information (passed to callback)
 *	      -> vdialog*, the notice should be placed with respect
 *		 to this dialog. if NULL uses the requestor dialog.
 *   returns: <- void
 */
void
isnfAskUser(int what, int cancel, askInvoker caller, void *data, vdialog *wrt)
{
  register isnifferApp 	*app = isnfGet();
  vstr			*str;
  askinfo		*info;
  register vnotice	*notice;

  vdebugIF((!caller), vexGenerate(vexGetArgNullClass(), vexMESSAGE,
           "ask-user called with NULL callback!?", vexNULL));

  /* if not created yet, do so now */
  notice = app->quesNotice;
  if (!notice) {
    vresource res;
    res = vresourceGet(app->resources, appname_QuestionNotice);
    app->quesNotice = notice = vnoticeLoad(res);
    vnoticeSetYesHook(notice, doYes);
    vnoticeSetNoHook(notice, doNo);
    vnoticeSetCancelHook(notice, doCancel);

    info = (askinfo*)vmemAlloc(sizeof(askinfo));
    vnoticeSetData(notice, info);
  }
  else
    info = (askinfo*)vnoticeGetData(notice);


  /* position notice */
  placeNotice(notice, wrt);


  /* reflect caller's request */
  vnoticeSetCancel(notice, cancel);
  str = vresourceGetStringAt(app->messages, what);
  vnoticeSetText(notice, str);
  vstrDestroy(str);

  info->invoker = caller;
  info->data    = data;

  /* open (we block the application to visually emphasize the mode) */
  vwindowUnblock(vnoticeGetWindow(notice));
  vnoticeOpen(notice);
  isnfBlock(vnoticeGetDialog(notice));
  return;
}




/*
 * void isnfBlock()
 *   purpose: Block the application, ie. show busy cursors in all windows
 *	      except the caller's unless that's NULL. Usually called at
 *            the beginning of a long operation that has blocked all input
 *            Nestable.
 *   accepts: -> vdialog*, the caller or NULL
 *   returns: <- void
 */
void
isnfBlock(vdialog *dialog)
{
  isnifferApp 		   *app = isnfGet();
  vwindowIterator 	    iterator;
  register vwindowIterator *iter= &iterator;
  register vwindow	   *callerwin, *scan, *root;

  app->busy++;
  callerwin = vdialogGetWindow(dialog);
  root = vwindowGetRoot();
  vwindowInitIterator(iter);
  while (vwindowNextIterator(iter)) {
    scan = vwindowGetIteratorWindow(iter);
    if (scan!=root && scan!=callerwin && !vwindowIsBlocked(scan))
      vwindowBlock(scan);
  }
  vwindowDestroyIterator(iter);
  return;
}





/*
 * void isnfUnBlock()
 *   purpose: Unblock the application. Some previous operation has "blocked"
 *	      the application (disabled all input) so we showed busy cursors
 *	      in (all) windows. unblocking resets window cursors. in debug 
 *	      we track caller's source to check correct balance of 
 *	      block/unblock pairs.
 *   accepts: -> const char*, file where unblock called from (debug)
 *	      -> int, line in file (debug)
 *   returns: <- void
 */
#if vdebugDEBUG
 void
_isnfUnBlock(const char *file, int line)
#else
 void
_isnfUnBlock(void)
#endif
{
  isnifferApp 		   *app = isnfGet();
  vwindowIterator 	    iterator;
  register vwindowIterator *iter= &iterator;

  if (app->busy) {
    app->busy--;
    if (!app->busy) {
      vwindowInitIterator(iter);
      while (vwindowNextIterator(iter))
	vwindowUnblock(vwindowGetIteratorWindow(iter));
      vwindowDestroyIterator(iter);
    }
  }
#if vdebugDEBUG
  else
    vdebugWarn("isnfUnBlock() not matched (%s, %d)!\n", file, line);
#endif

  return;
}




/*
 * void isnfInitTheseNames()
 *   purpose: Initialize a table of global names.
 *   accepts: -> const char**, literals to intern
 *            -> const vname**, the name table to fill in
 *	      -> unsigned int, the number of names in table
 *   returns: <- void
 */
void
isnfInitTheseNames(register const char **scan, register const vname **name,
		   unsigned int nameCount)
{
  register const char  **stop;

#if vdebugDEBUG
  if (!scan)
    vexGenerate(vexGetArgNullClass(), vexMESSAGE, "init names: NULL scan",
		vexERRNO, 0, vexNULL);
  if (!name)
    vexGenerate(vexGetArgNullClass(), vexMESSAGE, "init names: NULL name",
		vexERRNO, 0, vexNULL);
#endif

  stop = scan+nameCount;
  for (; scan<stop; scan++,name++)
    *name = vnameInternGlobalLiteral(*scan);

  return;
}



/********
 * isnfReplaceMulti works like vcharReplaceScribe except it can replace
 * up to 4 tokens in a single template string. Also it returns a vstr
 * not a vscribe. The placeholder strings are "%1s", "%2s", "%3s", and
 * "%4s"
 *
 * -> tmpl,     the template
 * -> ...,      NULL-terminated replacement strings
 * <- string,   new string
 *********/
vstr *
isnfReplaceMulti(const vchar *tmpl, ...)
{
    va_list		ap;
    register vstr	*str, *tmp;
    const vchar		*placeholder;
    const vchar		*replacer;
    
    vdebugIF(!tmpl, vexGenerate(vexGetArgNullClass(), vexMESSAGE,
             "replace multi: NULL template!", vexERRNO, 0, vexNULL));

    str = vstrClone(tmpl);
    va_start(ap, tmpl);
    
    /* %1s */
    replacer = va_arg(ap, const vchar*);
    if (!replacer)
        goto done;
    placeholder = appname_PlaceHolder1;
    tmp = vstrCloneScribed(vcharScribeReplace(str, placeholder, replacer));
    vstrDestroy(str);
    str = tmp;
   
    /* %2s */
    replacer = va_arg(ap, const vchar*);
    if (!replacer)
        goto done;
    placeholder = appname_PlaceHolder2;
    tmp = vstrCloneScribed(vcharScribeReplace(str, placeholder, replacer));
    vstrDestroy(str);
    str = tmp;

    /* %3s */
    replacer = va_arg(ap, const vchar*);
    if (!replacer)
        goto done;
    placeholder = appname_PlaceHolder3;
    tmp = vstrCloneScribed(vcharScribeReplace(str, placeholder, replacer));
    vstrDestroy(str);
    str = tmp;

    /* %4s */
    replacer = va_arg(ap, const vchar*);
    if (!replacer)
        goto done;
    placeholder = appname_PlaceHolder4;
    tmp = vstrCloneScribed(vcharScribeReplace(str, placeholder, replacer));
    vstrDestroy(str);
    str = tmp;

    done:
    va_end(ap);
    return str;
}


/********
 * isnfStyleConfirmationIsAvailable,
 * isnfPrintConfirmationIsAvailable
 *
 * >> Warning: this is to get around a bug in Galaxy 2.0 where "unimplemented"
 *    exceptions are generated for vprintConfirmJob and vprintConfirmStyle
 *    on platforms that do not support these dialogs. Actually if no 
 *    dialogs are available, these two routines are -supposed- to just call
 *    the printer's notification routines. This code should be removed once
 *    this bug has been fixed. 04-22-94 <<
 *
 * -> void
 * <- [t/f], true if the requested print dialog available
 ********/
int
isnfStyleConfirmationIsAvailable(void)
{
#if (vportWIN_MAC || vportWIN_MS_WINDOWS)
  return vTRUE;
#else
  return vFALSE;
#endif
}

int
isnfPrintConfirmationIsAvailable(void)
{
#if (vportWIN_MAC)
  return vTRUE;
#else
  return vFALSE;
#endif
}



/*
 *+------------------------------------------------------------------------+
 * private routines
 *+------------------------------------------------------------------------+
 */

static void
placeNotice(vnotice *notice, register vdialog *dialog)
{
  isnifferApp      *app = isnfGet();
  register vwindow *wrt;

  /* make sure the base window is visible, otherwise the notice
   * may not be shown */
  if (!dialog || !vwindowIsVisible(vdialogGetWindow(dialog))) {
    if (vwindowIsVisible(vdialogGetWindow(app->requestor)))
      wrt = vdialogGetWindow(app->requestor);
    else 
      wrt = vwindowGetRoot();
  }
  else
    wrt = vdialogGetWindow(dialog);

  vwindowPlace(vdialogGetWindow(vnoticeGetDialog(notice)), wrt,
	       vrectPLACE_CENTER, vrectPLACE_CENTER);
  return;
}

static int
unblockApp(vnotice *notice, vevent *event)
{
  isnfUnBlock();
  return TRUE;
}

static int
doYes(vnotice *notice, vevent *event)
{
  register askinfo *info;
  info =(askinfo*)vnoticeGetData(notice);
  (info->invoker)(responseYES, info->data);
  return unblockApp(notice, event);
}

static int
doNo(vnotice *notice, vevent *event)
{
  register askinfo *info;
  info =(askinfo*)vnoticeGetData(notice);
  (info->invoker)(responseNO, info->data);
  return unblockApp(notice,event);
}

static int
doCancel(vnotice *notice, vevent *event)
{
  register askinfo *info;
  info =(askinfo*)vnoticeGetData(notice);
  (info->invoker)(responseCANCEL, info->data);
  return unblockApp(notice,event);
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

/* $Id: worker.c,v 1.2 1997/09/16 18:52:19 mikem Exp $
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
 * copyright notice in the in the form of "Copyright 1992,93 Visix Software
 * Inc., 11440 Commerce Park Drive, Reston, VA  22091. All Rights Reserved"
 * appears in all copies, (ii) both the copyright notice and this permission
 * notice appear in supporting documentation and (iii) you are a valid
 * licensee of Galaxy Application Environment.
 */

/*
 * This is a simple example of using a thread to perform a long-running
 * task, giving the user the ability to cancle the task and see its progress.
 * This sample uses a subclass of vthread, just like the second producer/
 * consumer sample does.
 */


/*
 * Include Galaxy portable headers.
 */
#include <vport.h>


/*
 * Include Galaxy Misc Headers
 */
#include vstdlibHEADER
#include vstdioHEADER
#include vpoolHEADER


/*
 * Include Galaxy UI Headers
 */
#include vapplicationHEADER
#include vstartupHEADER
#include vresourceHEADER
#include vdialogHEADER
#include vbuttonHEADER
#include vcommandHEADER
#include vcontainerHEADER
#include vdictHEADER
#include vspinnerHEADER
#include vmenuHEADER
#include vmenubarHEADER


/*
 * Include Galaxy thread-related headers.
 */
#include vthreadHEADER
#include vmutexHEADER
#include vconditionHEADER


/*
 * Define the debug tag for this file.
 */
#if (vdebugDEBUG)
static const char _debugTag[] = __FILE__;
#define vdebugTAG	_debugTag
#endif


/*
 * Convienence macro.
 */
#define TAG(t) vnameInternGlobalLiteral(t)


/************************************************************************
 * Worker thread class definition
 ************************************************************************/

typedef struct _workerThread {
  vthread           super;
  vdialog          *ui_main_dialog;
  vbool             run;
} _workerThread;

#define _workerThreadCLASS(SUPER, THREAD) vthreadCLASS(SUPER, THREAD)

typedef struct _workerThreadClass _workerThreadClass;

struct _workerThreadClass {
  _workerThreadCLASS(_workerThreadClass, _workerThread);
};

static _workerThreadClass *_workerThreadDefaultClass = NULL;
static _workerThreadClass *_workerThreadGetDefaultClass(void);

#define _workerThreadGetThread(_t) (vportBASE_OBJECT(_t, super))
#define _workerThreadCreateOfClass(_c) \
          ((_workerThread *) vthreadCreateOfClass((vthreadClass*)(_c)))
#define _workerThreadCreate() \
          _workerThreadCreateOfClass(_workerThreadGetDefaultClass())
#define _workerThreadDestroy(_t) vthreadDestroy(_workerThreadGetThread((_t)))


/************************************************************************
 * This struct contains information that is attached to events posted from
 * the producers and consumers back to the that that is running the UI
 * event loop. 
 ************************************************************************/

typedef struct _workerUpdateUIData {
  _workerThread *thread;
  int            operation;
  vstr          *message;
} _workerUpdateUIData;


/*
 * Values for the operation field of _workerUpdateUIData
 */
enum {
  _workerOP_UPDATE_MESSAGE = 1,
  _workerOP_THREAD_DONE
};


/*
 * Misc globals.
 */
static vmenuItem *_workerQuitButton = NULL;
static int        _workerNumberRunningThreads = 0;


/*
 * Function prototypes.
 */
static int _workerQuit(vcommandFunction *command, vdict *context);
static int _workerStartWorkerButton(vcommandFunction *command,
                                    vdict *context);
static int _workerCancelWorkerButton(vcommandFunction *command,
                                     vdict *context);
static int _workerUpdateEventCallback(vevent *e);


/*
 * Command functions for our main dialog.
 */
static vcommandFunctionTemplate _workerDialogCommands[] =
{
  {"Quit", _workerQuit, NULL},
  {"Start Worker", _workerStartWorkerButton, NULL}
};


/*
 * Command functions for the worker status dialogs.
 */
static vcommandFunctionTemplate _workerWorkerStatusCommands[] =
{
  {"Cancel", _workerCancelWorkerButton, NULL}
};


/************************************************************************
 * Worker thread class implementation
 ************************************************************************/

/*
 * _workerThreadInitMethod
 * Init method for class _workerThread.
 */
static void
_workerThreadInitMethod(_workerThread *p)
{
  vclassSendSuper(_workerThreadDefaultClass, vinstanceINIT, (p));

  /*
   * Perform subclass-specific initialization here.
   */
  p->ui_main_dialog = NULL;
  p->run = vTRUE;
}


/*
 * _workerThreadDestroyMethod
 * Destroy method for class _workerThread
 */
static void
_workerThreadDestroyMethod(_workerThread *p)
{
  /*
   * Perform subclass-specific destruction here. (There really isn't any
   * for this thread subclass.)
   */

  vclassSendSuper(_workerThreadDefaultClass, vinstanceDESTROY, (p));
}


/*
 * _workerThreadPostEvent
 * Post an event from the context of the current thread to the event loop
 * behind the main dialog.
 */
static void
_workerThreadPostEvent(_workerThread *p, int operation, vstr *message)
{
  _workerUpdateUIData *d;
  vevent *e;
  
  /*
   * Create a block of data to tell the UI what to do. This will be free'd
   * by the thread running the event loop for the main dialog. The message
   * string will also be free'd by the other thread.
   */
  d = (_workerUpdateUIData *) vmemAlloc(sizeof(_workerUpdateUIData));
  d->thread = p;
  d->operation = operation;
  d->message = message;
  
  /*
   * Create the client event and post it to the main dialog.
   */
  e = veventCreateClient();
  veventSetTarget(e, _workerUpdateEventCallback);
  veventSetClientData(e, (void *) d);
  vwindowPostEvent(vdialogGetWindow(p->ui_main_dialog), e);
}


/*
 * _workerThreadRunMethod
 * The Run method for _workerThreads.
 */
static int
_workerThreadRunMethod(_workerThread *p, void *arg)
{
  int i;

  /*
   * This is a really simply "worker thread." Basically, we just want to
   * display some pretty messages in the status window while the thread
   * runs.
   */
  vexWITH_HANDLING {
    _workerThreadPostEvent(p, _workerOP_UPDATE_MESSAGE,
                           vstrCloneScribed(vcharScribeFormatLiteral(
                                              "Worker 0x%p starting...",
                                              p)));
    vthreadSleep(1, 0);

    for (i = 0; (i < 100) && (p->run == vTRUE); i+= 5) {
      _workerThreadPostEvent(p, _workerOP_UPDATE_MESSAGE,
                             vstrCloneScribed(vcharScribeFormatLiteral(
                                                "Worker 0x%p is %d%% done...",
                                                p, i)));
      vthreadSleep(0, 500000000);
    }

    _workerThreadPostEvent(p, _workerOP_UPDATE_MESSAGE,
                           vstrCloneScribed(vcharScribeFormatLiteral(
                                              "Worker 0x%p finished.",
                                              p)));
    vthreadSleep(1, 0);
  }
  vexON_EXCEPTION {
    vexClear();
  }
  vexEND_HANDLING;

  /*
   * Send a done event to the main ui event loop saying we're done.
   */
  _workerThreadPostEvent(p, _workerOP_THREAD_DONE, NULL);
  
  /*
   * We don't use the return value for this thread.
   */
  return(0);
}


/*
 * _workerThreadGetDefaultClass
 * Return the _workerThread class, creating it if necessary.
 */
static _workerThreadClass *
_workerThreadGetDefaultClass(void)
{
  _workerThreadClass *clas;

  if (_workerThreadDefaultClass == NULL) {
    vmutexLockGlobalWithHandling();

    if (_workerThreadDefaultClass == NULL) {
      clas = (_workerThreadClass *) vclassSpawn(vthreadGetDefaultClass(), 
                                              sizeof(_workerThreadClass));
      vclassSetObjectSize(clas, sizeof(_workerThread));
      vclassSetGlobalNameScribed(clas,
                                  vcharScribeLiteral("_workerThread"));
      
      vclassSet(clas, vinstanceDESTROY, _workerThreadDestroyMethod);
      vclassSet(clas, vinstanceINIT, _workerThreadInitMethod);
      vclassSet(clas, vthreadRUN, _workerThreadRunMethod);

      _workerThreadDefaultClass = clas;
    }

    vmutexUnlockGlobalWithHandling();
  }

  return(_workerThreadDefaultClass);
}


/************************************************************************
 * GUI Functions
 ************************************************************************/

/*
 *_workerDialogNotify
 * Dialog notify function to exit the application when the window is
 * closed.
 */
static void
_workerDialogNotify(vdialog * dialog, vevent * event)
{
  vdebugMTrace(("Entering _workerDialogNotify\n"));

  if (veventGetType(event) == veventWINDOW_STATE &&
      veventIsClose(event)) {
    veventStopProcessing();
  }

  vdebugMTrace(("Leaving _workerDialogNotify\n"));
  return;
}


/*
 * _workerStartWorkerButton
 * Callback on the Start Worker button.
 */
static int
_workerStartWorkerButton(vcommandFunction * command, vdict * context)
{
  vresource       rootRes,
                  dialogRes;
  vdialog        *dialog;
  vcommandSpace  *space;
  vdict          *commandDict;
  _workerThread  *thread;

  /*
   * Load a new copy of the worker status dialog.
   */
  rootRes = vapplicationGetResources(vapplicationGetCurrent());
  dialogRes = vresourceGet(rootRes, TAG("Worker Status"));
  dialog = vdialogLoad(dialogRes);

  /*
   * Create the command space for this dialog.
   */
  commandDict = vcommandCreateDictFunctionTemplates(
                                      _workerWorkerStatusCommands,
                                      sizeof(_workerWorkerStatusCommands) /
                                      sizeof(_workerWorkerStatusCommands[0]));
  space = vcommandCreateSpace();
  vcommandAddSpaceDictOwned(space, vname_Command, commandDict);
  vwindowSetSpaceOwned(vdialogGetWindow(dialog), space);

  vdialogPlaceWindow(dialog, 
                     vwindowGetRoot(),
                     vrectPLACE_CENTER,
                     vrectPLACE_CENTER);

  /*
   * Open the dialog before the thread is started.
   */
  vdialogOpen(dialog);

  /*
   * Create a worker thread.
   */
  thread = _workerThreadCreate();

  /*
   * Give the worker thread the dialog pointer, and the dialog a pointer to
   * the worker thread.
   */
  thread->ui_main_dialog = dialog;
  vdialogSetData(dialog, thread);

  /*
   * If this is the first thread started, disable the Quit button on the
   * main dialog.
   */
  if (_workerNumberRunningThreads++ == 0) {
    vmenuDisableItem(_workerQuitButton);
  }
  
  /*
   * Start the thread. We don't use the argument to the thread's run method
   * so we pass NULL for the argument here.
   */
  vthreadStart(_workerThreadGetThread(thread), NULL);
  
  return(vTRUE);
}


/*
 * _workerCancelWorkerButton
 * Callback on the Cancel button in the worker status dialog.
 */
static int
_workerCancelWorkerButton(vcommandFunction * command, vdict * context)
{
  _workerThread *thread;
  vdialogItem   *di;
  vdialog       *dialog;

  /*
   * The user has pressed cancel. Disable the cancle button.
   */
  di = (vdialogItem *) vdictLoad(context, vname_Operator);
  vdialogDisableItem(di);

  dialog = vdialogDetermineItemDialog(di);
  thread = (_workerThread *) vdialogGetData(dialog);

  /*
   * Now, tell the thread to stop running.
   */
  thread->run = vFALSE;

  /*
   * We also call vthreadInterrupt() here because our worker thread spends
   * a lot of time in vthreadSleep(). vthreadInterrupt() will cause
   * vthreadSleep() to immediatley throw vthreadInterruptedException.
   *
   * NOTE: if your worker thread doesn't ever call vthreadSleep, you would
   * never need to call vthreadInterrupt.
   */
  vthreadInterrupt(_workerThreadGetThread(thread));
  
  return(vTRUE);
}


/*
 * _workerUpdateEventCallback
 * Callback for the event that the worker threads post when they complete.
 */
static int
_workerUpdateEventCallback(vevent *e)
{
  _workerUpdateUIData *d;
  _workerThread       *thread;
  vdialog             *dialog;
  vdialogItem         *message_item;

  /*
   * We received a message from a worker thread. (Could be _any_ worker
   * thread.)
   */
  d = (_workerUpdateUIData *) veventGetClientData(e);
  thread = d->thread;
  dialog = thread->ui_main_dialog;
    
  switch (d->operation) {
  case _workerOP_THREAD_DONE: 
    /*
     * If this worker thread is done, close and destroy its status dialog.
     */
    vdialogClose(dialog);
    vdialogDestroy(dialog);
    
    /*
     * Now, we wait for the thread to terminate. We know this will return
     * really quickly, because the thread exits after posting this event.
     * Realistically, its probally already terminated.
     */
    vthreadWaitForTermination(_workerThreadGetThread(thread), 0, 0);
    _workerThreadDestroy(thread);

    /*
     * If that was the last thread running, re-enable the Quit button on
     * the main dialog.
     */
    if (--_workerNumberRunningThreads == 0) {
      vmenuEnableItem(_workerQuitButton);
    }
  
    break;

  case _workerOP_UPDATE_MESSAGE:
    /*
     * A worker thread wants us to upate the message in its status dialog.
     */
    if (d->message != NULL) {
      message_item = vdialogFindItem(dialog, TAG("Message"));
      
      /*
       * Note: vstrScribe takes ownership of the message.
       */
      vdialogSetItemTitleScribed(message_item, vstrScribe(d->message));
    }
    break;
  }

  /*
   * Free the data block on the event.
   */
  vmemFree(d);
  
  return(vTRUE);
}


/*
 * _workerQuit
 * Notify function on the File->Quit menu button.
 */
static int
_workerQuit(vcommandFunction * command, vdict * context)
{
  /*
   * For this little application, stopping the event loop is enough to
   * quit the program. 
   */
  veventStopProcessing();

  return(vTRUE);
}


/*
 * Main function.
 */
int
main(int argc, char **argv)
{
  vresource       rootRes,
                  dialogRes;
  vdialog        *dialog;
  vcommandSpace  *space;
  vdict          *commandDict;
  vmenubar       *menubar;
  vmenu          *menu;

  /*
   * Initialize Galaxy.
   */
  vstartup(argc, argv);

  /*
   * Load the main dialog.
   */
  rootRes = vapplicationGetResources(vapplicationGetCurrent());
  dialogRes = vresourceGet(rootRes, TAG("Main Dialog"));
  dialog = vdialogLoad(dialogRes);
  vdialogSetNotify(dialog, _workerDialogNotify);

  /*
   * Find the Quit button in the File menu.
   */
  menubar = (vmenubar *) vdialogFindItem(dialog, TAG("Menu Bar"));
  menu = vmenubarFindMenu(menubar, TAG("FileMenu"));
  _workerQuitButton = vmenuFindItem(menu, TAG("Quit"));
  
  /*
   * Create the command space for this dialog.
   */
  commandDict = vcommandCreateDictFunctionTemplates(_workerDialogCommands,
					      sizeof(_workerDialogCommands) /
					   sizeof(_workerDialogCommands[0]));
  space = vcommandCreateSpace();
  vcommandAddSpaceDictOwned(space, vname_Command, commandDict);
  vwindowSetSpaceOwned(vdialogGetWindow(dialog), space);

  /*
   * Position the dialog in the center of the screen.
   */
  vwindowPlace(vdialogGetWindow(dialog),
		vwindowGetRoot(),
		vrectPLACE_CENTER,
		vrectPLACE_CENTER);

  /*
   * Open the dialog.
   */
  vdialogOpen(dialog);

  /*
   * Event loop.
   */
  veventProcess();
  
  /*
   * Cleanup.
   */
  vdialogDestroy(dialog);
  
  exit(EXIT_SUCCESS);
  return(EXIT_FAILURE);
}

/*
 * End of worker.c
 */

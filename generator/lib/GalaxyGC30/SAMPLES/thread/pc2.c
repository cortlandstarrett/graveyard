/* $Id: pc2.c,v 1.4 1997/10/30 22:37:56 mikem Exp $
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
 * This sample is just like the first producer/consumer sample (pc.c)
 * except that it uses a subclass of vthread with an overriden Run method.
 * Also, the thread data block is gone, with the information being held
 * in the vthread subclass.
 */

/*
 * This is a very basic example of using threads, mutexes, and condition
 * variables in Galaxy 3.0. It is the classic producer/consumer problem.
 * There are some number of "producers" that create elements. The producers
 * want to place their elements in a queue, or bounded buffer, so that they
 * may be picked up by "consumers" and used somehow. Producers cannot add
 * items to a full buffer, however, and consumers cannot pull elements
 * from an empty buffer. This program shows a graphical representation of
 * the producer consumer problem with 5 producers, 5 consumers, and a buffer
 * large enough for 6 elements.
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


/*
 * This struct is the basic "element" of data passed between the producer
 * and consumer threads. It consists of a number and the color of the
 * producer thread that produced it.
 */
typedef struct _pcElement {
  int       number;
  vcolor   *color;
} _pcElement;


/*
 * This struct is the bounded buffer between the producer and consumer
 * threads. It has an array to hold the elements contained within the buffer
 * and information about the array (size, head, tail, and count.) It also
 * contains two condition variables and one mutex. The mutex is used to
 * prevent multiple threads from corrupting the buffer. The condition
 * variables are used by threads that want to remove or add to the buffer
 * when the buffer is full or empty, respectivley. 
 */
typedef struct _pcBoundedBuffer {
  _pcElement **buffer;
  vcondition   buffer_full_cv;
  vcondition   buffer_empty_cv;
  vmutex       buffer_lock;
  int          size;
  int          head;
  int          tail;
  int          count;
} _pcBoundedBuffer;


/*
 * This is the producer thread. It is a subclass of a vthread.
 */
typedef struct _pcProducer {
  vthread           super;
  int               id;
  int               period;
  vbool             run;
  vbool             stop;
  vbool             update_event_handled;
  int               current_element;
  vmutex            thread_data_lock;
  vcondition        thread_data_cv;
  vwindow          *ui_main_window;
} _pcProducer;

#define _pcProducerCLASS(SUPER, THREAD) vthreadCLASS(SUPER, THREAD)

typedef struct _pcProducerClass _pcProducerClass;

struct _pcProducerClass {
  _pcProducerCLASS(_pcProducerClass, _pcProducer);
};

static _pcProducerClass *_pcProducerDefaultClass = NULL;
static _pcProducerClass *_pcProducerGetDefaultClass(void);

#define _pcProducerGetThread(_t) (vportBASE_OBJECT(_t, super))
#define _pcProducerCreateOfClass(_c) \
          ((_pcProducer *) vthreadCreateOfClass((vthreadClass*)(_c)))
#define _pcProducerCreate() \
          _pcProducerCreateOfClass(_pcProducerGetDefaultClass())
#define _pcProducerDestroy(_t) vthreadDestroy(_pcProducerGetThread((_t)))


/*
 * This is the consumer thread. It is a subclass of a vthread.
 */
typedef struct _pcConsumer {
  vthread           super;
  int               id;
  int               period;
  vbool             run;
  vbool             stop;
  vbool             update_event_handled;
  int               current_element;
  vmutex            thread_data_lock;
  vcondition        thread_data_cv;
  vwindow          *ui_main_window;
} _pcConsumer;

#define _pcConsumerCLASS(SUPER, THREAD) vthreadCLASS(SUPER, THREAD)

typedef struct _pcConsumerClass _pcConsumerClass;

struct _pcConsumerClass {
  _pcConsumerCLASS(_pcConsumerClass, _pcConsumer);
};

static _pcConsumerClass *_pcConsumerDefaultClass = NULL;
static _pcConsumerClass *_pcConsumerGetDefaultClass(void);

#define _pcConsumerGetThread(_t) (vportBASE_OBJECT(_t, super))
#define _pcConsumerCreateOfClass(_c) \
          ((_pcConsumer *) vthreadCreateOfClass((vthreadClass*)(_c)))
#define _pcConsumerCreate() \
          _pcConsumerCreateOfClass(_pcConsumerGetDefaultClass())
#define _pcConsumerDestroy(_t) vthreadDestroy(_pcConsumerGetThread((_t)))


/*
 * This struct contains information that is attached to events posted from
 * the producers and consumers back to the that that is running the UI
 * event loop. 
 */
typedef struct _pcUpdateUIData {
  union {
    vdialogItem  *item;
    int           slot_number;
  } u;
  vcolor         *color;
  int             number;
  vthread        *pc_thread;
  vbool           p_or_c;
} _pcUpdateUIData;


#define _pcPRODUCER_THREAD_COUNT  5
#define _pcCONSUMER_THREAD_COUNT  5
#define _pcBUFFER_SIZE            6


static vpool             _pcElementPool;
static vmutex            _pcElementPoolMutex;

static _pcProducer      *_pcProducerThreads[_pcPRODUCER_THREAD_COUNT];
static _pcConsumer      *_pcConsumerThreads[_pcCONSUMER_THREAD_COUNT];

static _pcBoundedBuffer *_pcElementBuffer;

static vdialogItem      *_pcBufferItems[_pcBUFFER_SIZE];
static vdialogItem      *_pcProducerStartStopItems[_pcPRODUCER_THREAD_COUNT];
static vdialogItem      *_pcConsumerStartStopItems[_pcCONSUMER_THREAD_COUNT];


/*
 * Function prototypes.
 */
static int _pcQuit(vcommandFunction *command, vdict *context);
static int _pcProducerPeriodButton(vcommandFunction *command, vdict *context);
static int _pcProducerThreadPriorityButton(vcommandFunction *command,
                                           vdict *context);
static int _pcProducerStartStopButton(vcommandFunction *command,
                                      vdict *context);
static int _pcConsumerPeriodButton(vcommandFunction *command, vdict *context);
static int _pcConsumerThreadPriorityButton(vcommandFunction *command,
                                           vdict *context);
static int _pcConsumerStartStopButton(vcommandFunction *command,
                                      vdict *context);

static int _pcEmptyBufferButton(vcommandFunction *command, vdict *context);

static int _pcStartAllConsumers(vcommandFunction *command, vdict *context);
static int _pcStartAllProducers(vcommandFunction *command, vdict *context);
static int _pcStartAllThreads(vcommandFunction *command, vdict *context);
static int _pcStopAllConsumers(vcommandFunction *command, vdict *context);
static int _pcStopAllProducers(vcommandFunction *command, vdict *context);
static int _pcStopAllThreads(vcommandFunction *command, vdict *context);

/*
 * Command functions for our main dialog.
 */
static vcommandFunctionTemplate _pcDialogCommands[] =
{
  {"Quit", _pcQuit, NULL},
  {"Empty Buffer", _pcEmptyBufferButton, NULL},
  {"Start All Consumers", _pcStartAllConsumers, NULL},
  {"Start All Producers", _pcStartAllProducers, NULL},
  {"Start All Threads", _pcStartAllThreads, NULL},
  {"Stop All Consumers", _pcStopAllConsumers, NULL},
  {"Stop All Producers", _pcStopAllProducers, NULL},
  {"Stop All Threads", _pcStopAllThreads, NULL},

  {"PPer1",    _pcProducerPeriodButton, NULL},
  {"PThrPri1", _pcProducerThreadPriorityButton, NULL},
  {"PSS1",     _pcProducerStartStopButton, NULL},
  {"PPer2",    _pcProducerPeriodButton, NULL},
  {"PThrPri2", _pcProducerThreadPriorityButton, NULL},
  {"PSS2",     _pcProducerStartStopButton, NULL},
  {"PPer3",    _pcProducerPeriodButton, NULL},
  {"PThrPri3", _pcProducerThreadPriorityButton, NULL},
  {"PSS3",     _pcProducerStartStopButton, NULL},
  {"PPer4",    _pcProducerPeriodButton, NULL},
  {"PThrPri4", _pcProducerThreadPriorityButton, NULL},
  {"PSS4",     _pcProducerStartStopButton, NULL},
  {"PPer5",    _pcProducerPeriodButton, NULL},
  {"PThrPri5", _pcProducerThreadPriorityButton, NULL},
  {"PSS5",     _pcProducerStartStopButton, NULL},

  {"CPer1",    _pcConsumerPeriodButton, NULL},
  {"CThrPri1", _pcConsumerThreadPriorityButton, NULL},
  {"CSS1",     _pcConsumerStartStopButton, NULL},
  {"CPer2",    _pcConsumerPeriodButton, NULL},
  {"CThrPri2", _pcConsumerThreadPriorityButton, NULL},
  {"CSS2",     _pcConsumerStartStopButton, NULL},
  {"CPer3",    _pcConsumerPeriodButton, NULL},
  {"CThrPri3", _pcConsumerThreadPriorityButton, NULL},
  {"CSS3",     _pcConsumerStartStopButton, NULL},
  {"CPer4",    _pcConsumerPeriodButton, NULL},
  {"CThrPri4", _pcConsumerThreadPriorityButton, NULL},
  {"CSS4",     _pcConsumerStartStopButton, NULL},
  {"CPer5",    _pcConsumerPeriodButton, NULL},
  {"CThrPri5", _pcConsumerThreadPriorityButton, NULL},
  {"CSS5",     _pcConsumerStartStopButton, NULL}
};


/*
 *_pcDialogNotify
 * Dialog notify function to exit the application when the window is
 * closed.
 */
static void
_pcDialogNotify(vdialog * dialog, vevent * event)
{
  vdebugMTrace(("Entering _pcDialogNotify\n"));

  if (veventGetType(event) == veventWINDOW_STATE &&
      veventIsClose(event)) {
    veventStopProcessing();
  }

  vdebugMTrace(("Leaving _pcDialogNotify\n"));
  return;
}


/*
 * _pcProducerPeriodButton
 * Callback on the producer period spinners.
 */
static int
_pcProducerPeriodButton(vcommandFunction * command, vdict * context)
{
  _pcProducer *p;
  vspinner *sp;
  int thread_id;

  /*
   * Each period spinner has the id number of the producer thread that
   * it is supposed to control. We get that number out of the spinner's
   * data and use that to lookup the producer thread.
   */
  sp = (vspinner *) vdictLoad(context, vname_Operator);
  thread_id = (int) vdialogGetItemData(vspinnerGetItem(sp));
  p = _pcProducerThreads[thread_id];

  /*
   * Simply record the new period in the producer. It will be
   * picked up by the thread the next time it goes to sleep.
   */
  p->period = vspinnerGetValue(sp);

  return(vTRUE);
}


/*
 * _pcProducerThreadPriorityButton
 * Callback on the producer ThreadPriority spinners.
 */
static int
_pcProducerThreadPriorityButton(vcommandFunction * command, vdict * context)
{
  vspinner *sp;
  int thread_id;

  /*
   * Just like in _pcProducerPeriodButton, we get the thread's id from the
   * spinner. 
   */
  sp = (vspinner *) vdictLoad(context, vname_Operator);
  thread_id = (int) vdialogGetItemData(vspinnerGetItem(sp));

  /*
   * One thread can set another thread's priority at any time without
   * synchronization.
   */
  vthreadSetPriority(_pcProducerGetThread(_pcProducerThreads[thread_id]),
                     vspinnerGetValue(sp));

  return(vTRUE);
}


/*
 * _pcProducerStartStopButton
 * Callback on the producer StartStop spinners.
 */
static int
_pcProducerStartStopButton(vcommandFunction * command, vdict * context)
{
  _pcProducer *p;
  vdialogItem *di;
  int thread_id;

  /*
   * Again, we get the thread to work with by getting its id from the UI
   * item then using that to get the producer.
   */
  di = (vdialogItem *) vdictLoad(context, vname_Operator);
  thread_id = (int) vdialogGetItemData(di);
  p = _pcProducerThreads[thread_id];

  /*
   * We modify the producer under its lock.
   */
  vmutexLock(&p->thread_data_lock);

  if (p->run == vFALSE) {
    /*
     * Set the run flag to true and wake up the thread. Its blocked on its
     * condition variable right now.
     */
    p->run = vTRUE;
    vconditionSignal(&p->thread_data_cv);
    vdialogSetItemTitleScribed(di, vcharScribeLiteral("Stop"));
  }
  else{
    /*
     * Set the run flag to false. We signal the buffer's full condition
     * variable just in case our thread is blocked on that. It will get
     * the signal, wake up and see that its run flag is false now and
     * go back to waiting on its own condition variable.
     */
    p->run = vFALSE;
    vconditionSignalAll(&_pcElementBuffer->buffer_full_cv);
    vdialogSetItemTitleScribed(di, vcharScribeLiteral("Start"));
  }

  vmutexUnlock(&p->thread_data_lock);

  return(vTRUE);
}


/*
 * _pcConsumerPeriodButton
 * Callback on the Consumer period spinners.
 */
static int
_pcConsumerPeriodButton(vcommandFunction * command, vdict * context)
{
  _pcConsumer *c;
  vspinner *sp;
  int thread_id;

  /*
   * Each period spinner has the id number of the consumer thread that
   * it is supposed to control. We get that number out of the spinner's
   * data and use that to lookup the consumer.
   */
  sp = (vspinner *) vdictLoad(context, vname_Operator);
  thread_id = (int) vdialogGetItemData(vspinnerGetItem(sp));
  c = _pcConsumerThreads[thread_id];

  /*
   * Simply record the new period in the consumer. It will be
   * picked up by the thread the next time it goes to sleep.
   */
  c->period = vspinnerGetValue(sp);

  return(vTRUE);
}


/*
 * _pcConsumerThreadPriorityButton
 * Callback on the Consumer ThreadPriority spinners.
 */
static int
_pcConsumerThreadPriorityButton(vcommandFunction * command, vdict * context)
{
  vspinner *sp;
  int thread_id;

  /*
   * Just like in _pcConsumerPeriodButton, we get the thread's id from the
   * spinner. 
   */
  sp = (vspinner *) vdictLoad(context, vname_Operator);
  thread_id = (int) vdialogGetItemData(vspinnerGetItem(sp));

  /*
   * One thread can set another thread's priority at any time without
   * synchronization.
   */
  vthreadSetPriority(_pcConsumerGetThread(_pcConsumerThreads[thread_id]),
                     vspinnerGetValue(sp));

  return(vTRUE);
}


/*
 * _pcConsumerStartStopButton
 * Callback on the Consumer StartStop spinners.
 */
static int
_pcConsumerStartStopButton(vcommandFunction * command, vdict * context)
{
  _pcConsumer *c;
  vdialogItem *di;
  int thread_id;

  /*
   * Again, we get the thread to work with by getting its id from the UI
   * item then using that to get its consumer.
   */
  di = (vdialogItem *) vdictLoad(context, vname_Operator);
  thread_id = (int) vdialogGetItemData(di);
  c = _pcConsumerThreads[thread_id];

  /*
   * We modify the consumer under its lock.
   */
  vmutexLock(&c->thread_data_lock);

  if (c->run == vFALSE) {
    /*
     * Set the run flag to true and wake up the thread. Its blocked on its
     * condition variable right now.
     */
    c->run = vTRUE;
    vconditionSignal(&c->thread_data_cv);
    vdialogSetItemTitleScribed(di, vcharScribeLiteral("Stop"));
  }
  else{
    /*
     * Set the run flag to false. We signal the buffer's empty condition
     * variable just in case our thread is blocked on that. It will get
     * the signal, wake up and see that its run flag is false now and
     * go back to waiting on its own condition variable.
     */
    c->run = vFALSE;
    vconditionSignalAll(&_pcElementBuffer->buffer_empty_cv);
    vdialogSetItemTitleScribed(di, vcharScribeLiteral("Start"));
  }

  vmutexUnlock(&c->thread_data_lock);

  return(vTRUE);
}


/*
 * _pcEmptyBufferButton
 * Notify function on the File->Empty Buffer menu button.
 */
static int
_pcEmptyBufferButton(vcommandFunction * command, vdict * context)
{
  /*
   * Grab the buffer lock so that we can work without being bothered by
   * any possibly running producers or consumers.
   */
  vmutexLock(&_pcElementBuffer->buffer_lock);

  while (_pcElementBuffer->count > 0) {
    _pcElement *element;

    element = _pcElementBuffer->buffer[_pcElementBuffer->head];
    _pcElementBuffer->buffer[_pcElementBuffer->head] = NULL;
    vdialogSetItemTitleScribed(_pcBufferItems[_pcElementBuffer->head],
                               vcharScribeLiteral("<empty>"));
    _pcElementBuffer->head++;
    _pcElementBuffer->count--;
    
    if (_pcElementBuffer->head == _pcElementBuffer->size)
      _pcElementBuffer->head = 0;

    vpoolFree(&_pcElementPool, element);
  }
  
  vmutexUnlock(&_pcElementBuffer->buffer_lock);

  /*
   * We signal the full condition now, since the buffer has more room in it.
   * (A lot of room, actually.) We use SignalAll rather than Signal to make
   * sure to wake _every_ producer thread that is waiting for room. If
   * you change this to a Signal instead of a SignalAll, you'll notice that
   * if all producers are waiting to add elements to the buffer and you clear
   * the buffer, only one of the producers will proceed to refill it if there
   * are no consumers running.
   */
  vconditionSignalAll(&_pcElementBuffer->buffer_full_cv);
  
  return(vTRUE);
}


/*
 * _pcStartAllConsumers
 * Notify function on the File->Start All Consumers menu button.
 */
static int
_pcStartAllConsumers(vcommandFunction * command, vdict * context)
{
  int i;

  for (i = 0; i < _pcCONSUMER_THREAD_COUNT; i++) {
    _pcConsumer *c;

    c = _pcConsumerThreads[i];

    vmutexLock(&c->thread_data_lock);
    c->run = vTRUE;
    vconditionSignal(&c->thread_data_cv);
    vdialogSetItemTitleScribed(_pcConsumerStartStopItems[i],
                               vcharScribeLiteral("Stop"));
    vmutexUnlock(&c->thread_data_lock);
  }

  return(vTRUE);
}


/*
 * _pcStartAllProducers
 * Notify function on the File->Start All Producers menu button.
 */
static int
_pcStartAllProducers(vcommandFunction * command, vdict * context)
{
  int i;

  for (i = 0; i < _pcPRODUCER_THREAD_COUNT; i++) {
    _pcProducer *p;

    p = _pcProducerThreads[i];

    vmutexLock(&p->thread_data_lock);
    p->run = vTRUE;
    vconditionSignal(&p->thread_data_cv);
    vdialogSetItemTitleScribed(_pcProducerStartStopItems[i],
                               vcharScribeLiteral("Stop"));
    vmutexUnlock(&p->thread_data_lock);
  }

  return(vTRUE);
}


/*
 * _pcStartAllThreads
 * Notify function on the File->Start All Threads menu button.
 */
static int
_pcStartAllThreads(vcommandFunction * command, vdict * context)
{
  int i;

  for (i = 0; i < _pcPRODUCER_THREAD_COUNT; i++) {
    _pcProducer *p;

    p = _pcProducerThreads[i];

    vmutexLock(&p->thread_data_lock);
    p->run = vTRUE;
    vconditionSignal(&p->thread_data_cv);
    vdialogSetItemTitleScribed(_pcProducerStartStopItems[i],
                               vcharScribeLiteral("Stop"));
    vmutexUnlock(&p->thread_data_lock);
  }

  for (i = 0; i < _pcCONSUMER_THREAD_COUNT; i++) {
    _pcConsumer *c;

    c = _pcConsumerThreads[i];

    vmutexLock(&c->thread_data_lock);
    c->run = vTRUE;
    vconditionSignal(&c->thread_data_cv);
    vdialogSetItemTitleScribed(_pcConsumerStartStopItems[i],
                               vcharScribeLiteral("Stop"));
    vmutexUnlock(&c->thread_data_lock);
  }

  return(vTRUE);
}


/*
 * _pcStopAllConsumers
 * Notify function on the File->Stop All Consumers menu button.
 */
static int
_pcStopAllConsumers(vcommandFunction * command, vdict * context)
{
  int i;

  for (i = 0; i < _pcCONSUMER_THREAD_COUNT; i++) {
    _pcConsumer *c;

    c = _pcConsumerThreads[i];

    vmutexLock(&c->thread_data_lock);
    c->run = vFALSE;
    vconditionSignal(&c->thread_data_cv);
    vconditionSignalAll(&_pcElementBuffer->buffer_empty_cv);
    vdialogSetItemTitleScribed(_pcConsumerStartStopItems[i],
                               vcharScribeLiteral("Start"));
    vmutexUnlock(&c->thread_data_lock);
  }

  return(vTRUE);
}


/*
 * _pcStopAllProducers
 * Notify function on the File->Stop All Producers menu button.
 */
static int
_pcStopAllProducers(vcommandFunction * command, vdict * context)
{
  int i;

  for (i = 0; i < _pcPRODUCER_THREAD_COUNT; i++) {
    _pcProducer *p;

    p = _pcProducerThreads[i];

    vmutexLock(&p->thread_data_lock);
    p->run = vFALSE;
    vconditionSignal(&p->thread_data_cv);
    vconditionSignalAll(&_pcElementBuffer->buffer_full_cv);
    vdialogSetItemTitleScribed(_pcProducerStartStopItems[i],
                               vcharScribeLiteral("Start"));
    vmutexUnlock(&p->thread_data_lock);
  }

  return(vTRUE);
}


/*
 * _pcStopAllThreads
 * Notify function on the File->Stop All Threads menu button.
 */
static int
_pcStopAllThreads(vcommandFunction * command, vdict * context)
{
  int i;

  for (i = 0; i < _pcPRODUCER_THREAD_COUNT; i++) {
    _pcProducer *p;

    p = _pcProducerThreads[i];

    vmutexLock(&p->thread_data_lock);
    p->run = vFALSE;
    vconditionSignal(&p->thread_data_cv);
    vconditionSignalAll(&_pcElementBuffer->buffer_full_cv);
    vdialogSetItemTitleScribed(_pcProducerStartStopItems[i],
                               vcharScribeLiteral("Start"));
    vmutexUnlock(&p->thread_data_lock);
  }

  for (i = 0; i < _pcCONSUMER_THREAD_COUNT; i++) {
    _pcConsumer *c;

    c = _pcConsumerThreads[i];

    vmutexLock(&c->thread_data_lock);
    c->run = vFALSE;
    vconditionSignal(&c->thread_data_cv);
    vconditionSignalAll(&_pcElementBuffer->buffer_empty_cv);
    vdialogSetItemTitleScribed(_pcConsumerStartStopItems[i],
                               vcharScribeLiteral("Start"));
    vmutexUnlock(&c->thread_data_lock);
  }

  return(vTRUE);
}


/*
 * _pcQuit
 * Notify function on the File->Quit menu button.
 */
static int
_pcQuit(vcommandFunction * command, vdict * context)
{
  /*
   * For this little application, stopping the event loop is enough to
   * quit the program. 
   */
  veventStopProcessing();

  return(vTRUE);
}


/*
 * _pcUpdateUIBufferSlot
 * Update a buffer slot based on the information in the update event.
 */
static int
_pcUpdateUIBufferSlot(vevent *e)
{
  _pcUpdateUIData *d;

  /*
   * Get the data struct out of the event. 
   */
  d = (_pcUpdateUIData *) veventGetClientData(e);

  if (d->color == NULL) {
    vdialogSetItemTitleScribed(_pcBufferItems[d->u.slot_number],
                               vcharScribeLiteral("<empty>"));
  }
  else {
    vdialogSetItemForeground(_pcBufferItems[d->u.slot_number], d->color);
    vdialogSetItemTitleScribed(_pcBufferItems[d->u.slot_number],
                               vcharScribeFormatLiteral("%d", d->number));
  }

  /*
   * Even though the data struct was created in some other thread, we can
   * free it here because we know that the other thread won't ever try to
   * reference it again.
   */
  vmemFree(d);
  
  return(vTRUE);
}


/*
 * _pcUpdateBufferSlot
 * Ask the thread running the UI to update a slot in the buffer.
 */
static void
_pcUpdateBufferSlot(int element, vwindow *w, int slot_number, vcolor *color)
{
  _pcUpdateUIData *d;
  vevent *e;
  
  /*
   * Allocate a data struct and fill it up with enough info to update a
   * buffer UI item for the given slot.
   */
  d = (_pcUpdateUIData *) vmemAlloc(sizeof(_pcUpdateUIData));
  d->u.slot_number = slot_number;
  d->color = color;
  d->number = element;
  d->pc_thread = NULL;

  /*
   * Now, post a client event back to the loop owned by the thread that
   * opened our main dialog.
   *
   * You might think that we could simply update the color and title of
   * the UI item here, in the context of a producer or consumer thread.
   * You cannot. Changing an attribute of a dialog item in here could only
   * work if you could ensure that another thread would _not_ alter or try
   * to access that attribute until you were done. But if the main dialog
   * is asked to redraw itself, then it will access those dialog item
   * attributes. Since you can't synchronize with events that would cause
   * the dialog item to be accessed or modified, you need to post your own
   * event back into the loop that handles events for the dialog.
   */
  e = veventCreateClient();
  veventSetTarget(e, _pcUpdateUIBufferSlot);
  veventSetClientData(e, (void *) d);
  vwindowPostEvent(w, e);
}


/*
 * _pcUpdateUIElementNumber
 * Update a thread's element number UI item based on information in the
 * update event.
 */
static int
_pcUpdateUIElementNumber(vevent *e)
{
  _pcUpdateUIData *d;

  d = (_pcUpdateUIData *) veventGetClientData(e);

  vdialogSetItemForeground(d->u.item, d->color);
  vdialogSetItemTitleScribed(d->u.item, vcharScribeFormatLiteral("%d",
                                                                 d->number));

  /*
   * If a thread is waiting to know that its update UI event has been
   * processed, go ahead and let it know that. Clearly, it would have
   * been better to make a subclass of vthread that included the thread
   * data lock, thread cv, and update event handled information instead
   * of conditionalizing the following code based on the type of thread
   * that posted the event. Such extra subclassing is left as an exercise
   * to the reader.
   */
  if (d->pc_thread != NULL) {
    if (d->p_or_c == vFALSE) {
      _pcProducer *p = (_pcProducer *) d->pc_thread;

      vmutexLock(&p->thread_data_lock);

      p->update_event_handled = vTRUE;
      vconditionSignal(&p->thread_data_cv);
      
      vmutexUnlock(&p->thread_data_lock);
    }
    else {
      _pcConsumer *c = (_pcConsumer *) d->pc_thread;

      vmutexLock(&c->thread_data_lock);

      c->update_event_handled = vTRUE;
      vconditionSignal(&c->thread_data_cv);
      
      vmutexUnlock(&c->thread_data_lock);
    }
  }
  
  /*
   * Even though the data struct was created in some other thread, we can
   * free it here because we know that the other thread won't ever try to
   * reference it again.
   */
  vmemFree(d);
  
  return(vTRUE);
}


/*
 * _pcUpdateProducerElementNumber
 * Ask the thread running the UI to update the current element number for
 * a producer.
 */
static void
_pcUpdateProducerElementNumber(_pcProducer *p, vdialogItem *item,
                               vcolor *color)
{
  _pcUpdateUIData *d;
  vevent *e;
  
  d = (_pcUpdateUIData *) vmemAlloc(sizeof(_pcUpdateUIData));
  d->u.item = item;
  d->color = color;
  d->number = p->current_element;
  d->pc_thread = _pcProducerGetThread(p);
  d->p_or_c = vFALSE;

  /*
   * Now, post a client event back to the loop owned by the thread that
   * opened our main dialog.
   *
   * You might think that we could simply update the color and title of
   * the UI item here, in the context of a producer or consumer thread.
   * You cannot. Changing an attribute of a dialog item in here could only
   * work if you could ensure that another thread would _not_ alter or try
   * to access that attribute until you were done. But if the main dialog
   * is asked to redraw itself, then it will access those dialog item
   * attributes. Since you can't synchronize with events that would cause
   * the dialog item to be accessed or modified, you need to post your own
   * event back into the loop that handles events for the dialog.
   */
  e = veventCreateClient();
  veventSetTarget(e, _pcUpdateUIElementNumber);
  veventSetClientData(e, (void *) d);

  /*
   * We do a little something special here. You see, there are a lot of
   * threads posting events to a single thread's event loop. That thread
   * needs to process all of these events. But if the computer is slow
   * or if the time it takes to process these events is greater than the
   * time it takes for a thread to post more events, the event loop of that
   * one thread will grow without bound. This will overwhelm the thread
   * running the UI and the application will appear to halt. So, after
   * we post this type of event, we'll wait to be signaled that the event
   * has really be handled. That way, we won't get ahead of the UI thread.
   */
  vmutexLock(&p->thread_data_lock);
  p->update_event_handled = vFALSE;
  
  
  vwindowPostEvent(p->ui_main_window, e);

  while ((p->stop == vFALSE) && (p->run == vTRUE)
	 && (p->update_event_handled == vFALSE)) {
    vconditionWait(&p->thread_data_cv, &p->thread_data_lock, 0, 0);
  }

  vmutexUnlock(&p->thread_data_lock);
}


/*
 * _pcUpdateConsumerElementNumber
 * Ask the thread running the UI to update the current element number for
 * a consumer.
 */
static void
_pcUpdateConsumerElementNumber(_pcConsumer *c, vdialogItem *item,
                               _pcElement *element)
{
  _pcUpdateUIData *d;
  vevent *e;
  
  d = (_pcUpdateUIData *) vmemAlloc(sizeof(_pcUpdateUIData));
  d->u.item = item;
  d->color = element->color;
  d->number = element->number;
  d->pc_thread = _pcConsumerGetThread(c);
  d->p_or_c = vTRUE;

  /*
   * Now, post a client event back to the loop owned by the thread that
   * opened our main dialog.
   *
   * You might think that we could simply update the color and title of
   * the UI item here, in the context of a producer or consumer thread.
   * You cannot. Changing an attribute of a dialog item in here could only
   * work if you could ensure that another thread would _not_ alter or try
   * to access that attribute until you were done. But if the main dialog
   * is asked to redraw itself, then it will access those dialog item
   * attributes. Since you can't synchronize with events that would cause
   * the dialog item to be accessed or modified, you need to post your own
   * event back into the loop that handles events for the dialog.
   */
  e = veventCreateClient();
  veventSetTarget(e, _pcUpdateUIElementNumber);
  veventSetClientData(e, (void *) d);

  /*
   * We do a little something special here. You see, there are a lot of
   * threads posting events to a single thread's event loop. That thread
   * needs to process all of these events. But if the computer is slow
   * or if the time it takes to process these events is greater than the
   * time it takes for a thread to post more events, the event loop of that
   * one thread will grow without bound. This will overwhelm the thread
   * running the UI and the application will appear to halt. So, after
   * we post this type of event, we'll wait to be signaled that the event
   * has really be handled. That way, we won't get ahead of the UI thread.
   */
  vmutexLock(&c->thread_data_lock);
  c->update_event_handled = vFALSE;
  
  
  vwindowPostEvent(c->ui_main_window, e);

  while ((c->stop == vFALSE) && (c->run == vTRUE)
	 && (c->update_event_handled == vFALSE)) {
    vconditionWait(&c->thread_data_cv, &c->thread_data_lock, 0, 0);
  }

  vmutexUnlock(&c->thread_data_lock);
}


/*
 * _pcProducerInitMethod
 * Init method for class _pcProducer.
 */
static void
_pcProducerInitMethod(_pcProducer *p)
{
  vclassSendSuper(_pcProducerDefaultClass, vinstanceINIT, (p));
  
  p->period = 1;
  p->run = vFALSE;
  p->stop = vFALSE;
  p->current_element = 1;
  p->ui_main_window = NULL;
  
  /*
   * Create a mutex and condition variable for each thread. Its often
   * helpfull to give mutexes and cv's names because in a debug build,
   * if there is a problem with a mutex or cv the library will often
   * print the object's name along with its address.
   */
  vmutexInit(&p->thread_data_lock);
  vmutexSetNameFormatted(&p->thread_data_lock, "Lock for thread data 0x%p", p);
  
  vconditionInit(&p->thread_data_cv);
  vconditionSetNameFormatted(&p->thread_data_cv, "CV for thread data 0x%p", p);
}


/*
 * _pcProducerDestroyMethod
 * Destroy method for class _pcProducer
 */
static void
_pcProducerDestroyMethod(_pcProducer *p)
{
  vconditionDestroy(&p->thread_data_cv);
  vmutexDestroy(&p->thread_data_lock);
  
  vclassSendSuper(_pcProducerDefaultClass, vinstanceDESTROY, (p));
}


/*
 * _pcProducerRunMethod
 * The Run method for _pcProducers.
 */
static int
_pcProducerRunMethod(_pcProducer *p, void *arg)
{
  _pcElement     *element;
  vcolor         *my_color;
  vdialogItem    *my_item;
  vdialog        *dialog;
  vcontainer     *pc;

  /*
   * Just for fun, we pass the pointer to the main dialog in via the thread's
   * argument.
   */
  dialog = (vdialog *) arg;

  /*
   * Notice that we can access the dialog in a read-only manner without
   * synchronization with other threads.
   */
  pc = (vcontainer *) vdialogFindItem(dialog, TAG("Producer Threads"));
  
  /*
   * Find the label item that this thread wants to display its current
   * value in.
   */
  my_item = vdialogFindItem(pc, vnameInternGlobalScribed(
                                  vcharScribeFormatLiteral("PEle%d",
                                                           p->id + 1)));
  my_color = vdialogGetItemForeground(my_item);

  /*
   * Lock this thread's data lock. We have to hold this lock in order
   * to check the value of the stop and run flags in the data block.
   */
  vmutexLock(&p->thread_data_lock);
  
  /*
   * Stay alive until we're told to stop.
   */
  while (p->stop == vFALSE) {
    /*
     * So long as we're allowed to be alive, but we're not allowed to actually
     * try to run and modify the buffer, wait on the thread's condition
     * variable. Basically, we wait here until told to either exit (via
     * the stop flag) or mess with the buffer (via the run flag.)
     *
     * Note that while this thread blocks in vconditionWait, the thread's
     * lock on p->thread_data_lock is released.
     */
    while ((p->stop == vFALSE) && (p->run == vFALSE)) {
      vconditionWait(&p->thread_data_cv, &p->thread_data_lock, 0, 0);
    }

    /*
     * Someone woke us up by signaling our cv. Try to modify the buffer.
     */
    if (p->run == vTRUE) {
      /*
       * We release the thread's lock because there is no reason to hold
       * it while we're working with the buffer.
       */
      vmutexUnlock(&p->thread_data_lock);
      
      /*
       * Create an element to add to the buffer
       */
      element = (_pcElement *) vpoolAlloc(&_pcElementPool);
      element->number = p->current_element;
      element->color = my_color;
      
      /*
       * Lock down the buffer.
       */
      vmutexLock(&_pcElementBuffer->buffer_lock);
      
      /*
       * If the buffer is full, we need to wait for a consumer to remove
       * an element from the buffer to make room. So we wait on
       * buffer_full_cv. buffer_lock is released while we wait, allowing
       * a consumer to lock the buffer and remove an element.
       *
       * Notice that we check the value of p->run, too. We do this so that
       * we can make the thread abandon its attempt to add an element to
       * the buffer. Its okay to read this value out from under the
       * thread_data_lock. 
       */
      while ((_pcElementBuffer->count == _pcElementBuffer->size) &&
             (p->run == vTRUE)) {
        vconditionWait(&_pcElementBuffer->buffer_full_cv,
                       &_pcElementBuffer->buffer_lock, 0, 0);
      }
      
      /*
       * If we're still allowed to run, go ahead and add the element in.
       */
      if (p->run == vTRUE) {
        _pcElementBuffer->buffer[_pcElementBuffer->tail] = element;

        /*
         * Tell the UI to update the buffer slot we just modified.
         */
        _pcUpdateBufferSlot(p->current_element, p->ui_main_window,
                            _pcElementBuffer->tail, my_color);
        _pcElementBuffer->tail++;
        _pcElementBuffer->count++;
        
        if (_pcElementBuffer->tail == _pcElementBuffer->size)
          _pcElementBuffer->tail = 0;
      
        /*
         * Unlock the buffer, we're done with it now.
         */
        vmutexUnlock(&_pcElementBuffer->buffer_lock);
        
        /*
         * Signal a possibly waiting consumer that there is an element
         * in the buffer to be read.
         */
        vconditionSignal(&_pcElementBuffer->buffer_empty_cv);

        /*
         * Tell the UI to update our thread's next element number.
         */
        p->current_element++;
        _pcUpdateProducerElementNumber(p, my_item, my_color);
        
        /*
         * Sleep a while to simulate work. Notive the exceptino handler.
	 * vthreadSleep can throw vthreadInterruptedException if another
	 * thread calls vthreadInterrupt on this thread. In fact the UI
	 * thread will interrupt this thread's sleep when you press the
	 * stop button to ensure that the thread responds quickly.
         */
	if (p->run == vTRUE) {
	  vexWITH_HANDLING {
	    if (p->period != 0) {
              vthreadSleep(p->period, 0);
	    }
	    else {
              vthreadSleep(0, 250000000);
	    }
          }
          vexON_EXCEPTION {
            vexClear();
          }
          vexEND_HANDLING;
        }
      }
      else {
        /*
         * Make sure to release the lock if we weren't allow to add the
         * element to the buffer. Also destroy the element ourselves because
         * a consumer can't do it for us now.
         */
        vmutexUnlock(&_pcElementBuffer->buffer_lock);
        vpoolFree(&_pcElementPool, element);
      }

      /*
       * Re-lock the thread_data_lock so we have the lock at the top of the
       * loop again when checking the run and stop flags.
       */
      vmutexLock(&p->thread_data_lock);
    }
  }

  vmutexUnlock(&p->thread_data_lock);

  /*
   * We don't use the return value for this thread.
   */
  return(0);
}


/*
 * _pcProducerGetDefaultClass
 * Return the _pcProducer class, creating it if necessary.
 */
static _pcProducerClass *
_pcProducerGetDefaultClass(void)
{
  _pcProducerClass *clas;

  if (_pcProducerDefaultClass == NULL) {
    vmutexLockGlobalWithHandling();

    if (_pcProducerDefaultClass == NULL) {
      clas = (_pcProducerClass *) vclassSpawn(vthreadGetDefaultClass(), 
                                              sizeof(_pcProducerClass));
      vclassSetObjectSize(clas, sizeof(_pcProducer));
      vclassSetGlobalNameScribed(clas,
                                  vcharScribeLiteral("_pcProducer"));
      
      vclassSet(clas, vinstanceDESTROY, _pcProducerDestroyMethod);
      vclassSet(clas, vinstanceINIT, _pcProducerInitMethod);
      vclassSet(clas, vthreadRUN, _pcProducerRunMethod);

      _pcProducerDefaultClass = clas;
    }

    vmutexUnlockGlobalWithHandling();
  }

  return(_pcProducerDefaultClass);
}


/*
 * _pcConsumerInitMethod
 * Init method for class _pcConsumer.
 */
static void
_pcConsumerInitMethod(_pcConsumer *c)
{
  vclassSendSuper(_pcConsumerDefaultClass, vinstanceINIT, (c));
  
  c->period = 1;
  c->run = vFALSE;
  c->stop = vFALSE;
  c->current_element = 1;
  c->ui_main_window = NULL;
  
  /*
   * Create a mutex and condition variable for each thread. Its often
   * helpfull to give mutexes and cv's names because in a debug build,
   * if there is a problem with a mutex or cv the library will often
   * print the object's name along with its address.
   */
  vmutexInit(&c->thread_data_lock);
  vmutexSetNameFormatted(&c->thread_data_lock, "Lock for thread data 0x%p", c);
  
  vconditionInit(&c->thread_data_cv);
  vconditionSetNameFormatted(&c->thread_data_cv, "CV for thread data 0x%p", c);
}


/*
 * _pcConsumerDestroyMethod
 * Destroy method for class _pcConsumer
 */
static void
_pcConsumerDestroyMethod(_pcConsumer *c)
{
  vconditionDestroy(&c->thread_data_cv);
  vmutexDestroy(&c->thread_data_lock);
  
  vclassSendSuper(_pcConsumerDefaultClass, vinstanceDESTROY, (c));
}


/*
 * _pcConsumerRunMethod
 * The Run method for _pcConsumers.
 */
static int
_pcConsumerRunMethod(_pcConsumer *c, void *arg)
{
  _pcElement    *element;
  vdialogItem    *my_item;
  vdialog        *dialog;
  vcontainer     *cc;

  /*
   * Just for fun, we pass the pointer to the main dialog in via the thread's
   * argument.
   */
  dialog = (vdialog *) arg;

  /*
   * Notice that we can access the dialog in a read-only manner without
   * synchronization with other threads.
   */
  cc = (vcontainer *) vdialogFindItem(dialog, TAG("Consumer Threads"));
  
  /*
   * Find the label item that this thread wants to display its current
   * value in.
   */
  my_item = vdialogFindItem(cc, vnameInternGlobalScribed(
                                  vcharScribeFormatLiteral("CEle%d",
                                                           c->id + 1)));

  /*
   * Lock this thread's data lock. We have to hold this lock in order
   * to check the value of the stop and run flags in the data block.
   */
  vmutexLock(&c->thread_data_lock);

  /*
   * Stay alive until we're told to stop.
   */
  while (c->stop == vFALSE) {
    /*
     * So long as we're allowed to be alive, but we're not allowed to actually
     * try to run and modify the buffer, wait on the thread's condition
     * variable. Basically, we wait here until told to either exit (via
     * the stop flag) or mess with the buffer (via the run flag.)
     *
     * Note that while this thread blocks in vconditionWait, the thread's
     * lock on c->thread_data_lock is released.
     */
    while ((c->stop == vFALSE) && (c->run == vFALSE)) {
      vconditionWait(&c->thread_data_cv, &c->thread_data_lock, 0, 0);
    }

    /*
     * Someone woke us up by signaling our cv. Try to modify the buffer.
     */
    if (c->run == vTRUE) {
      /*
       * We release the thread's lock because there is no reason to hold
       * it while we're working with the buffer.
       */
      vmutexUnlock(&c->thread_data_lock);

      /*
       * Lock down the buffer.
       */
      vmutexLock(&_pcElementBuffer->buffer_lock);
      
      /*
       * If the buffer is empty, we need to wait for a producer to add
       * an element from the buffer to make room. So we wait on
       * buffer_empty_cv. buffer_lock is released while we wait, allowing
       * a producer to lock the buffer and add an element.
       *
       * Notice that we check the value of c->run, too. We do this so that
       * we can make the thread abandon its attempt to remove an element from
       * the buffer. Its okay to read this value out from under the
       * thread_data_lock. 
       */
      while ((_pcElementBuffer->count == 0) && (c->run == vTRUE)) {
        vconditionWait(&_pcElementBuffer->buffer_empty_cv,
                       &_pcElementBuffer->buffer_lock, 0, 0);
      }
      
      /*
       * If we're still allowed to run, go ahead and remove an element.
       */
      if (c->run == vTRUE) {
        element = _pcElementBuffer->buffer[_pcElementBuffer->head];
        _pcElementBuffer->buffer[_pcElementBuffer->head] = NULL;

        /*
         * Tell the UI to update the buffer slot we just modified.
         */
        _pcUpdateBufferSlot(c->current_element, c->ui_main_window,
                            _pcElementBuffer->head, NULL);
        _pcElementBuffer->head++;
        _pcElementBuffer->count--;
        
        if (_pcElementBuffer->head == _pcElementBuffer->size)
          _pcElementBuffer->head = 0;

        /*
         * Unlock the buffer, we're done with it now.
         */
        vmutexUnlock(&_pcElementBuffer->buffer_lock);
      
        /*
         * Signal a possibly waiting producer that there is room
         * in the buffer for another element now.
         */
        vconditionSignal(&_pcElementBuffer->buffer_full_cv);
        
        /*
         * Tell the UI to update our thread's new element number.
         */
        c->current_element = element->number;
        _pcUpdateConsumerElementNumber(c, my_item, element);
        
        /*
         * Free the element.
         */
        vpoolFree(&_pcElementPool, element);
      
        /*
         * Sleep a while to simulate work. Notive the exceptino handler.
	 * vthreadSleep can throw vthreadInterruptedException if another
	 * thread calls vthreadInterrupt on this thread. In fact the UI
	 * thread will interrupt this thread's sleep when you press the
	 * stop button to ensure that the thread responds quickly.
         */
	if (c->run == vTRUE) {
	  vexWITH_HANDLING {
	    if (c->period != 0) {
              vthreadSleep(c->period, 0);
	    }
	    else {
              vthreadSleep(0, 250000000);
	    }
          }
          vexON_EXCEPTION {
            vexClear();
          }
          vexEND_HANDLING;
        }
      }
      else {
        /*
         * Make sure to release the lock if we weren't allow to remove an
         * element from the buffer.
         */
        vmutexUnlock(&_pcElementBuffer->buffer_lock);
      }
      
      /*
       * Re-lock the thread_data_lock so we have the lock at the top of the
       * loop again when checking the run and stop flags.
       */
      vmutexLock(&c->thread_data_lock);
    }
  }

  vmutexUnlock(&c->thread_data_lock);

  /*
   * We don't use the return value for this thread.
   */
  return(0);
}


/*
 * _pcConsumerGetDefaultClass
 * Return the _pcConsumer class, creating it if necessary.
 */
static _pcConsumerClass *
_pcConsumerGetDefaultClass(void)
{
  _pcConsumerClass *clas;

  if (_pcConsumerDefaultClass == NULL) {
    vmutexLockGlobalWithHandling();

    if (_pcConsumerDefaultClass == NULL) {
      clas = (_pcConsumerClass *) vclassSpawn(vthreadGetDefaultClass(), 
                                           sizeof(_pcConsumerClass));
      vclassSetObjectSize(clas, sizeof(_pcConsumer));
      vclassSetGlobalNameScribed(clas,
                                  vcharScribeLiteral("_pcConsumer"));
      
      vclassSet(clas, vinstanceDESTROY, _pcConsumerDestroyMethod);
      vclassSet(clas, vinstanceINIT, _pcConsumerInitMethod);
      vclassSet(clas, vthreadRUN, _pcConsumerRunMethod);

      _pcConsumerDefaultClass = clas;
    }

    vmutexUnlockGlobalWithHandling();
  }

  return(_pcConsumerDefaultClass);
}


/*
 * _pcSetupThreads
 * Create the producer and consumer threads.
 */
static void
_pcSetupThreads(vdialog *dialog)
{
  int i;

  /*
   * Create the producer threads.
   */
  for (i = 0; i < _pcPRODUCER_THREAD_COUNT; i++) {
    /*
     * Create a "producer" thread.
     */
    _pcProducerThreads[i] = _pcProducerCreate();
    _pcProducerThreads[i]->id = i;
    _pcProducerThreads[i]->ui_main_window = vdialogGetWindow(dialog);

    /*
     * Start the thread. The thread will start running immediatley, perhaps
     * even before the call to vthreadStart returns. 
     */
    vthreadStart(_pcProducerGetThread(_pcProducerThreads[i]), (void *) dialog);
  }
  
  /*
   * Create consumers just like producers.
   */
  for (i = 0; i < _pcCONSUMER_THREAD_COUNT; i++) {
    /*
     * Create a "consumer" thread.
     */
    _pcConsumerThreads[i] = _pcConsumerCreate();
    _pcConsumerThreads[i]->id = i;
    _pcConsumerThreads[i]->ui_main_window = vdialogGetWindow(dialog);

    /*
     * Start the thread. The thread will start running immediatley, perhaps
     * even before the call to vthreadStart returns. 
     */
    vthreadStart(_pcConsumerGetThread(_pcConsumerThreads[i]), (void *) dialog);
  }
}


/*
 * _pcCleanupThreads
 * Cleanup the producer and consumer threads.
 */
static void
_pcCleanupThreads(void)
{
  int i;

  vdebugMAdvise(("Stopping and destroying all threads now.\n"));
  
  /*
   * Stop each producer.
   */
  for (i = 0; i < _pcPRODUCER_THREAD_COUNT; i++) {
    _pcProducer *p;

    p = _pcProducerThreads[i];

    /*
     * Lock the element buffer _and_ the thread's data block.
     */
    vmutexLock(&_pcElementBuffer->buffer_lock);
    vmutexLock(&p->thread_data_lock);

    /*
     * Set the flags to make the thread stop modifing the buffer and exit.
     */
    p->run = vFALSE;
    p->stop = vTRUE;

    /*
     * Signal the thread's cv and the element buffer's full cv. We do this
     * because we don't know what the thread is doing right now. If its
     * not modifying the buffer, but instead waiting on its cv to be told to
     * modify the buffer, then signaling the thread's cv will wake it up to
     * see the new value of td->stop and exit. If, however, it is trying
     * to add an element to the buffer, but the buffer is full, then it is
     * blocked on the buffer's full cv. Signaling that will allow the thread
     * to wake up and see the new value of td->run. It will then stop trying
     * to add an element to the buffer and exit.
     *
     * Notice that we use vconditionSignal for the thread's data cv but we
     * use vconditionSignalAll for the element buffer cv. This is because
     * we know that there is only one thread waiting on the thread's data
     * cv but there could be many threads waiting on the element buffer's
     * cv. Since you can't direct a cv signal to a specific thread, we
     * signal all the threads waiting on the buffer cv. They will all wake
     * up and re-check their conditions, but only this thread will find a
     * reason to modify its behavior.
     */
    vconditionSignal(&p->thread_data_cv);
    vconditionSignalAll(&_pcElementBuffer->buffer_full_cv);

    /*
     * We call vthreadInterrupt just in case the thread is in vthreadSleep.
     * This will cause vthreadSleep to throw vthreadInterruptedException
     * immediatley. So, even if the sleep period for a thread is 60 seconds,
     * we won't have to wait that long just to ask the thread to exit.
     */
    vthreadInterrupt(_pcProducerGetThread(_pcProducerThreads[i]));

    vmutexUnlock(&p->thread_data_lock);
    vmutexUnlock(&_pcElementBuffer->buffer_lock);

    /*
     * Wait for the thread to terminate.
     */
    vthreadWaitForTermination(_pcProducerGetThread(_pcProducerThreads[i]),
                              0, 0);
  }
  
  /*
   * Stop each consumer.
   */
  for (i = 0; i < _pcCONSUMER_THREAD_COUNT; i++) {
    _pcConsumer *c;
    
    c = _pcConsumerThreads[i];

    /*
     * Lock the element buffer _and_ the thread's data block.
     */
    vmutexLock(&_pcElementBuffer->buffer_lock);
    vmutexLock(&c->thread_data_lock);

    /*
     * Set the flags to make the thread stop modifing the buffer and exit.
     */
    c->run = vFALSE;
    c->stop = vTRUE;

    /*
     * Signal the thread's cv and the element buffer's empty cv. We do this
     * because we don't know what the thread is doing right now. If its
     * not modifying the buffer, but instead waiting on its cv to be told to
     * modify the buffer, then signaling the thread's cv will wake it up to
     * see the new value of td->stop and exit. If, however, it is trying
     * to remove an element from the buffer, but the buffer is empty, then
     * it is blocked on the buffer's empty cv. Signaling that will allow
     * the thread to wake up and see the new value of td->run. It will
     * then stop trying to remove an element from the buffer and exit.
     *
     * Notice that we use vconditionSignal for the thread's data cv but we
     * use vconditionSignalAll for the element buffer cv. This is because
     * we know that there is only one thread waiting on the thread's data
     * cv but there could be many threads waiting on the element buffer's
     * cv. Since you can't direct a cv signal to a specific thread, we
     * signal all the threads waiting on the buffer cv. They will all wake
     * up and re-check their conditions, but only this thread will find a
     * reason to modify its behavior.
     */
    vconditionSignal(&c->thread_data_cv);
    vconditionSignalAll(&_pcElementBuffer->buffer_empty_cv);

    /*
     * We call vthreadInterrupt just in case the thread is in vthreadSleep.
     * This will cause vthreadSleep to throw vthreadInterruptedException
     * immediatley. So, even if the sleep period for a thread is 60 seconds,
     * we won't have to wait that long just to ask the thread to exit.
     */
    vthreadInterrupt(_pcConsumerGetThread(_pcConsumerThreads[i]));

    vmutexUnlock(&c->thread_data_lock);
    vmutexUnlock(&_pcElementBuffer->buffer_lock);

    /*
     * Wait for the thread to terminate.
     */
    vthreadWaitForTermination(_pcConsumerGetThread(_pcConsumerThreads[i]),
                              0, 0);
  }

  /*
   * Flush any update events out of the queue. After this, all threads
   * should be stopped and their update events flushed.
   */
  veventFlushProcessing();
  
  /*
   * Now, since there will be no more references to the threads, destroy
   * them.
   */
  for (i = 0; i < _pcPRODUCER_THREAD_COUNT; i++) {
    _pcProducerDestroy(_pcProducerThreads[i]);
    _pcProducerThreads[i] = NULL;
  }
  
  for (i = 0; i < _pcCONSUMER_THREAD_COUNT; i++) {
    _pcConsumerDestroy(_pcConsumerThreads[i]);
    _pcConsumerThreads[i] = NULL;
  }
  
  vdebugMAdvise(("Done.  All threads are gone now.\n"));
}


/*
 * _pcSetupBuffer
 * Initialize the global bounded buffer.
 */
static void
_pcSetupBuffer(void)
{
  _pcElementBuffer = (_pcBoundedBuffer *) vmemAlloc(sizeof(_pcBoundedBuffer));
  _pcElementBuffer->buffer = (_pcElement **) vmemAllocAndClear(
                                               sizeof(_pcElement *) *
                                               _pcBUFFER_SIZE);
  _pcElementBuffer->size = _pcBUFFER_SIZE;
  _pcElementBuffer->head = 0;
  _pcElementBuffer->tail = 0;
  _pcElementBuffer->count = 0;

  /*
   * The element buffer has a mutex and two condition variables.
   */
  vmutexInit(&_pcElementBuffer->buffer_lock);
  vmutexSetName(&_pcElementBuffer->buffer_lock, "Protects the global buffer");

  vconditionInit(&_pcElementBuffer->buffer_full_cv);
  vconditionSetName(&_pcElementBuffer->buffer_full_cv, "Buffer Full");

  vconditionInit(&_pcElementBuffer->buffer_empty_cv);
  vconditionSetName(&_pcElementBuffer->buffer_empty_cv, "Buffer Empty");

  /*
   * Elements are allocated from a global pool. vpools are not usable from
   * multiple threads by default. We want to allow multiple producer and
   * consumer threads to allocate and free elements without synchronization,
   * so we create a mutex to go with the pool and use vpoolSetMutex to
   * have the vpool manager automatically lock the pool with that mutex
   * whenever it is accessed.
   */
  vpoolInit(&_pcElementPool, sizeof(_pcElement));
  vmutexInit(&_pcElementPoolMutex);
  vmutexSetName(&_pcElementPoolMutex, "Protects the global element pool");
  vpoolSetMutex(&_pcElementPool, &_pcElementPoolMutex);
}


/*
 * _pcCleanupBuffer
 * Initialize the global bounded buffer.
 */
static void
_pcCleanupBuffer(void)
{
  int i;
  
  /*
   * Free any elements that remain the the buffer.
   */
  for (i = 0; i < _pcBUFFER_SIZE; i++) {
    _pcElement *e;

    e = _pcElementBuffer->buffer[i];

    if (e) vpoolFree(&_pcElementPool, e);
  }
  
  vmemFree(_pcElementBuffer->buffer);
  vmutexDestroy(&_pcElementBuffer->buffer_lock);
  vconditionDestroy(&_pcElementBuffer->buffer_full_cv);
  vconditionDestroy(&_pcElementBuffer->buffer_empty_cv);
  vpoolDestroy(&_pcElementPool);
  vmutexDestroy(&_pcElementPoolMutex);
  vmemFree(_pcElementBuffer);
}


/*
 * _pcSetupUI
 * Associate a thread id number (0-4) with each UI item in the producer
 * and consumer parts of the main dialog.
 */
static void
_pcSetupUI(vdialog *dialog)
{
  vcontainer *pc;
  vcontainer *cc;
  int i;

  /*
   * Find the UI items associated with the buffer slots and hold them
   * in a global array.
   */
  for (i = 0; i < _pcBUFFER_SIZE; i++) {
    const vname *tmp_tag;

    tmp_tag = vnameInternGlobalScribed(vcharScribeFormatLiteral(
                                                            "Buffer Slot %d",
                                                            i + 1));
    _pcBufferItems[i] = vdialogFindItem(dialog, tmp_tag);
  }
  
  pc = (vcontainer *) vdialogFindItem(dialog, TAG("Producer Threads"));
  cc = (vcontainer *) vdialogFindItem(dialog, TAG("Consumer Threads"));

  /*
   * Find the Period, Thread Priority, and Start/Stop UI items associated
   * with each producer thread. We place the thread "id", which is an index
   * into a global array of prodcer threads, in the data element of each
   * dialog item. This is so that when we are in one of the item's
   * notification function we can figure out which thread to manipulate.
   */
  for (i = 0; i < _pcPRODUCER_THREAD_COUNT; i++) {
    vdialogItem *tmp_item;
    const vname *tmp_tag;

    tmp_tag = vnameInternGlobalScribed(vcharScribeFormatLiteral("PPer%d",
                                                                i + 1));
    tmp_item = vcontainerFindItem(pc, tmp_tag);
    vdialogSetItemData(tmp_item, (void *) i);

    tmp_tag = vnameInternGlobalScribed(vcharScribeFormatLiteral("PThrPri%d",
                                                                i + 1));
    tmp_item = vcontainerFindItem(pc, tmp_tag);
    vdialogSetItemData(tmp_item, (void *) i);

    tmp_tag = vnameInternGlobalScribed(vcharScribeFormatLiteral("PSS%d",
                                                                i + 1));
    tmp_item = vcontainerFindItem(pc, tmp_tag);
    vdialogSetItemData(tmp_item, (void *) i);
    _pcProducerStartStopItems[i] = tmp_item;
  }
  
  /*
   * Find the Period, Thread Priority, and Start/Stop UI items associated
   * with each consumer thread. We place the thread "id", which is an index
   * into a global array of consumer threads, in the data element of each
   * dialog item. This is so that when we are in one of the item's
   * notification function we can figure out which thread to manipulate.
   */
  for (i = 0; i < _pcCONSUMER_THREAD_COUNT; i++) {
    vdialogItem *tmp_item;
    const vname *tmp_tag;

    tmp_tag = vnameInternGlobalScribed(vcharScribeFormatLiteral("CPer%d",
                                                                i + 1));
    tmp_item = vcontainerFindItem(cc, tmp_tag);
    vdialogSetItemData(tmp_item, (void *) i);

    tmp_tag = vnameInternGlobalScribed(vcharScribeFormatLiteral("CThrPri%d",
                                                                i + 1));
    tmp_item = vcontainerFindItem(cc, tmp_tag);
    vdialogSetItemData(tmp_item, (void *) i);

    tmp_tag = vnameInternGlobalScribed(vcharScribeFormatLiteral("CSS%d",
                                                                i + 1));
    tmp_item = vcontainerFindItem(cc, tmp_tag);
    vdialogSetItemData(tmp_item, (void *) i);
    _pcConsumerStartStopItems[i] = tmp_item;
  }
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

  /*
   * Initialize Galaxy.
   */
  vstartup(argc, argv);

  /*
   * Load the main dialog.
   */
  rootRes = vapplicationGetResources(vapplicationGetCurrent());
  dialogRes = vresourceGet(rootRes, TAG("Pc Dialog"));
  dialog = vdialogLoad(dialogRes);
  vdialogSetNotify(dialog, _pcDialogNotify);

  /*
   * Create the command space for this dialog.
   */
  commandDict = vcommandCreateDictFunctionTemplates(_pcDialogCommands,
					      sizeof(_pcDialogCommands) /
					   sizeof(_pcDialogCommands[0]));
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
   * Associate thread numbers with all those little UI items...
   */
  _pcSetupUI(dialog);
  
  /*
   * Setup the buffer that the threads will use.
   */
  _pcSetupBuffer();
  
  /*
   * Create the threads that the UI will control.
   */
  _pcSetupThreads(dialog);
  
  /*
   * Open the dialog.
   */
  vdialogOpen(dialog);

  /*
   * Event loop.
   */
  veventProcess();
  
  /*
   * Clean up. Order is important here. We stop the threads before we
   * destroy the buffer to ensure that this thread is the only thread that
   * can possible access the buffer.
   */
  _pcCleanupThreads();
  _pcCleanupBuffer();

  vdialogDestroy(dialog);
  
  exit(EXIT_SUCCESS);
  return(EXIT_FAILURE);
}

/*
 * End of pc2.c
 */

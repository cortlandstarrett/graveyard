/* 
 * notify.cpp:
 *
 * This example illustrates how to send and receive ObjectStore notifications.
 *
 * This example is intended to be run as a single process, and demonstrates 
 * notifications between sessions in both single and connected modes. The 
 * process creates 2 sessions and starts 2 threads - the initiator and 
 * responder threads. 
 *
 */

#include "dbname.h"
#include <ostore/ostore.hh>
#include <iostream.h>
#include <assert.h>

#include <windows.h>
#include <process.h>
HANDLE hEvent;

#include <sys/timeb.h>

class timer {
 public:
  static double now() {
    struct _timeb timeStruct;
    _ftime(&timeStruct);
    double result = (double)1000000 * timeStruct.time + (timeStruct.millitm * 1000);
    return result;
  }
};

/*
 * The initiator thread - this is the thread that is responsible for 
 * initiating the notifications 
 */

void initiator_thread(void *s)

{
/*
 * Before starting, wait for the responder thread to complete its initialization 
 * and subscribe to the notifications. 
 */

  WaitForSingleObject(hEvent, INFINITE);

  OS_ESTABLISH_FAULT_HANDLER
  os_session *sess = (os_session*)s;
  os_session::set_current(sess);

  const char* root_name = "Test Object";

  cout << "Initiator opening database " << example_db_name << endl;
  os_database* db = os_database::open(example_db_name,0,0644);

  os_soft_pointer<void> location1 = 0;
  os_soft_pointer<void> location2 = 0;

  OS_BEGIN_TXN(t1,0,os_transaction::update)
  {
    os_database_root* root = db->find_root(root_name);
    location1 = root->get_value();           /*  &int[0] */
    location2 = &((int*)location1.resolve())[1];  /*  &int[1] */
    }
  OS_END_TXN(t1);

  os_notification* note;
  int iterations = 0;

  {
    cout << "Initiator Starting notifications..." << endl;

   /* subscribe to location2 */
   os_notification::subscribe(location2);

    double begin = timer::now();

     while (iterations < 50) {
      iterations++;

      /* send immediate notification on location1 with iterations as kind */
      os_notification::notify_immediate(location1,iterations);

      /* now get response into note */
      os_notification::receive(note);

      /* make sure note response is on location2 */
      os_soft_pointer<void> location = note->get_location();
      assert(location == location2);

      /* make sure correct iterations comes back */
      int kind = note->get_kind();
      assert(kind == iterations);

    delete note; /* avoid memory leak */

    }

    double end = timer::now();

    /*  Tell Responder to exit by sending notification on location1 with kind=0 */
    os_notification::notify_immediate(location1,0);

    cout << "We performed " << iterations
	 << " notifications in "
	 << (end-begin)/1000000
	 << " seconds" << endl;

    /* Initiator done */
  }
  OS_END_FAULT_HANDLER

}

void responder_thread(void *s)

{
  OS_ESTABLISH_FAULT_HANDLER
  const char* root_name = "Test Object";
  os_session *sess = (os_session*)s;
  os_session::set_current(sess);

  cout << "Responder opening database " << example_db_name << endl;
  os_database* db = os_database::open(example_db_name,0,0644);

  os_soft_pointer<void> location1 = 0, location2 = 0;

    OS_BEGIN_TXN(t1,0,os_transaction::update)
    {
    os_database_root* root = db->find_root(root_name);
    location1 = root->get_value();           /*  &int[0] */
    location2 = &((int*)location1.resolve())[1];  /*  &int[1] */
    }
    OS_END_TXN(t1);

  os_notification* note;
  int iterations = 0;
  OS_BEGIN_TXN(t2,0,os_transaction::update)
  {
    cout << "Responder Waiting for Notifications" << endl;
     /* subscribe to location1 */
    os_notification::subscribe(location1);
     /*
      * Now that we've subscribed to the notifications, tell the initiator 
      * thread that it can continue 
      */

    SetEvent(hEvent);

    iterations = 0;
    while(1) {
      /* receive notification for location1 into note */
      os_notification::receive(note);
      iterations++;
      /* see what kind it is */
      int kind = note->get_kind();

      /* if kind is 0, exit */
      if (kind == 0)
	  break; /* Responder done */

      /* make sure notification is about location1 */
      os_soft_pointer<void> location = note->get_location();
      assert(location == location1);

      delete note; /* avoid memory leak */

      /* send notification on location2 with kind */
      os_notification::notify_immediate(location2,kind);

      }
    cout << "received: " << iterations << " notifications" << endl;
  } OS_END_TXN(t2)
  OS_END_FAULT_HANDLER

}

int main(int argc, char **argv)
{
  const char* root_name = "Test Object";

  /* can see client name with "ossvrstat -clients <host>" */
  OS_ESTABLISH_FAULT_HANDLER

  objectstore::set_client_name(argv[0]);

  objectstore::initialize_for_sessions(2);
  os_session *s1 = os_session::create("Responder Session");
  os_session *s2 = os_session::create("Initiator Session");
  os_session::set_current(s1);

  cout << "Main Opening database " << example_db_name << endl;
  os_database* db = os_database::open(example_db_name,0,0644);

  os_soft_pointer<void> location1 = 0;
  os_soft_pointer<void> location2 = 0;

  OS_BEGIN_TXN(t1,0,os_transaction::update) {
    os_database_root* root = db->find_root(root_name);
    if (!root) {
      cout << "Creating a couple of ints" << endl;
      root = db->create_root(root_name);
      root->set_value(new (db, os_typespec::get_int(), 2) int[2]);
      }

    location1 = root->get_value();           /*  &int[0] */
    location2 = &((int*)location1.resolve())[1];  /*  &int[1] */
    }
  OS_END_TXN(t1);
  db->close();

  os_session::set_current(0);
  cout << "Main starting threads" << endl << flush;

  hEvent = CreateEvent(NULL,FALSE,FALSE,NULL);
  HANDLE hT[2];

  hT[0] = (HANDLE)_beginthread(responder_thread,0,s1);
  hT[1] = (HANDLE)_beginthread(initiator_thread,0,s2);

  WaitForMultipleObjects(2, hT, TRUE, INFINITE);

  objectstore::shutdown();
  cout << "Main exiting" << endl << flush;

OS_END_FAULT_HANDLER

objectstore::shutdown();
return 0;
}


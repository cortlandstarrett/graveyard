/*** app_server.cpp ***/

#include "app_server.hh"

int req_count = 0; // used to simulate request data
int thread_count = 0;
os_reference mvcc_countp; 
os_reference update_countp;
long tlast_refresh;
int mvcc_persistent_access = 0;
os_database *mvcc_db;
os_database *update_db;
os_session *mvcc_session;
os_session *update_session;
char *DBNAME;

Mutex* hmCout;
Mutex* hmMvccAccess;
Mutex* hmUpdateAccess;
Mutex* hmRefresh;

void app_server::init()
{
  hmCout->lock();
  cout << "initializing app server..." << endl << flush;
  hmCout->unlock();

  update_queue = new queue();
  mvcc_queue = new queue();

  os_session::set_current(update_session);
  os_database *db1 = os_database::create(DBNAME, 0666, 1); 
  OS_BEGIN_TXN(tx1, 0, os_transaction::update)
     int *countp = new(db1, os_typespec::get_int()) int(0);
     db1->create_root("count")->set_value(countp);
  OS_END_TXN(tx1)
  db1->close();
  os_session::set_current(0);
}

request *app_server::get_request()
{
  value_list *v = 0;
  request *r = 0;

  if (req_count == NUM_REQUESTS) {
    v = new value_list();
    v->insert(req_count);
    v->insert("end");
    r = new request(request::end, v, request::mvcc);
  }
  else if (req_count % 19) {
    v = new value_list();
    v->insert(req_count);
    v->insert("view");
    r = new request(request::view, v, request::mvcc);
  }
  else {
    v = new value_list();
    v->insert(req_count);
    v->insert("buy");
    r = new request(request::buy, v, request::update);
  }

  req_count++;

  hmCout->lock();

  if (v) {
    cout << "sending: " << v->first()->get_float_value() << "  ";
    cout << v->next()->get_string_value();
    cout << " thread: " << Thread::get_id() << endl << flush;
  }

  hmCout->unlock();

  return r;
}


void app_server::route_requests()
{
   request *the_request;

   while(1) {
     the_request = app_server::get_request();
     if (!the_request) continue;

     if (the_request->get_type() == request::end) {
       delete the_request;
       int i;
       for (i = 0; i < NUM_MVCC_THREADS; i++) {
	 the_request = new request(request::end, 0, request::mvcc);
         app_server::schedule_mvcc_request(*the_request);
       }
       for (i = 0; i < NUM_UPDATE_THREADS; i++) {
	 the_request = new request(request::end, 0, request::update);
	 app_server::schedule_update_request(*the_request);
       }
       break;
     }

     if (the_request->get_txn_type() == request::mvcc)
       app_server::schedule_mvcc_request(*the_request);
     else
       app_server::schedule_update_request(*the_request);
   }

   // synchronize thread completion
   Thread::wait_on_threads(NUM_MVCC_THREADS, NUM_UPDATE_THREADS);
}

unsigned int STDCALL app_server::service_update_requests(void*)
{
   OS_ESTABLISH_FAULT_HANDLER // required b/c this is top level of a thread

   // bind this thread to the updater session
   os_session::set_current(update_session);
 
   request *the_request;
   value_list *the_reply;

   while(1) {

     the_request = app_server::get_update_request();

     if (!the_request) assert(0);

     if (the_request->get_type() == request::end) {
       delete the_request;
       break;
     }

     if (the_request->get_type() == request::buy) {
       hmUpdateAccess->lock();
       OS_BEGIN_TXN(buy_txn, 0, os_transaction::update) 
	   the_reply = app_server::buy_seats(the_request->get_args());
       OS_END_TXN(buy_txn)
       hmUpdateAccess->unlock();

       app_server::send_reply(the_reply);
     }
     else
         error("Unknown update request type.");
     
     delete the_request;

   } // end while
 
   // remove this thread from the session before exiting the thread
   os_session::set_current(0);

   OS_END_FAULT_HANDLER

   return 0;
}

unsigned int STDCALL app_server::service_mvcc_requests(void*)
{
   OS_ESTABLISH_FAULT_HANDLER // top level of thread

   // bind this thread to the mvcc reader session
   os_session::set_current(mvcc_session);
 
   request *the_request = 0;

   while(1) {
     the_request = app_server::get_mvcc_request();

     if (!the_request) assert(0);

     if (the_request->get_type() == request::end) {
       delete the_request;
       break;
     }

     if (the_request->get_type() == request::view) {
       
       // refresh mvcc view, if needed

       // This locks tlast_refresh and prevents concurrent refreshes
       hmRefresh->lock();
       app_server::refresh_if_needed(); 
       hmRefresh->unlock();

       // increment so refresh_if_needed() knows if there is pers access now
       hmMvccAccess->lock();
       mvcc_persistent_access++;
       hmMvccAccess->unlock();

       // execute mvcc operation and send reply
       send_reply(app_server::view_seats(the_request->get_args()));

       // decrement value since pers access finished
       hmMvccAccess->lock();
       mvcc_persistent_access--;
       hmMvccAccess->unlock();
     }
     else
       error("Unknown mvcc request type.");

     delete the_request;

   } // end while

   // remove this thread from the session before exiting the thread
   os_session::set_current(0);
   
   OS_END_FAULT_HANDLER

   return 0;
}


void app_server::refresh_if_needed()
{
  long currTime = Time::get_time_in_secs();
  if (currTime - tlast_refresh > MAX_LATENCY) {
    tlast_refresh = currTime;

    // wait till no current pers mvcc access
    while (1){
      hmMvccAccess->lock();
      if (mvcc_persistent_access) 
	hmMvccAccess->unlock();
      else 
	break;
    }
    // hold on to PersAccess lock, refresh mvcc view
    os_transaction::checkpoint();

    hmCout->lock();
    cout << "Performed refresh." << endl << flush;
    hmCout->unlock();
    
    // release lock
    hmMvccAccess->unlock();
  }
}


request *app_server::get_update_request()
{
  return update_queue->remove();
}

request *app_server::get_mvcc_request()
{
  return mvcc_queue->remove();
}

void app_server::schedule_update_request(request& r)
{
  update_queue->insert(r);
}


void app_server::schedule_mvcc_request(request& r)
{
  mvcc_queue->insert(r);
}


void app_server::startup_update_processing()
{
   os_session::set_current(update_session);

   app_server::setup_buy_seats();

   // create a pool of threads, all w/ the same thread func   
   for (int i = 0; i < NUM_UPDATE_THREADS; i++) {
   Thread::create(app_server::service_update_requests);
   os_session::set_current(0);
   }

   hmCout->lock();
   cout << "started update thread(s)" << endl;
   hmCout->unlock();
  
}

void app_server::cleanup_update_processing()
{
   os_session::set_current(update_session);

   //all threads known to be finished

   // nothing to do here, really

   os_session::set_current(0);
}

void app_server::startup_mvcc_processing()
{

   os_session::set_current(mvcc_session);

   app_server::setup_view_seats();

   tlast_refresh = Time::get_time_in_secs();

   // start long-lived global mvcc transaction
   os_transaction::begin(os_transaction::read_only, os_transaction::global);

   // create a pool of threads, all w/ the same thread func   
   for (int i = 0; i < NUM_MVCC_THREADS; i++) {
     Thread::create(app_server::service_mvcc_requests);
   }

   os_session::set_current(0);
   
   hmCout->lock();
   cout << "started mvcc threads" << endl;
   hmCout->unlock();

}

void app_server::cleanup_mvcc_processing()
{
   os_session::set_current(mvcc_session);

   //all threads known to be finished

   // commit and cleanup the transaction object
   os_transaction *txn = os_transaction::get_current();
   txn->commit();
   delete txn;

   os_session::set_current(0);
}


void app_server::send_reply(value_list *v)
{
  hmCout->lock();
  cout << "reply: " << v->first()->get_float_value() << "  "; 
  cout << v->next()->get_float_value() << " "; 
  cout << v->next()->get_string_value();
  cout << " thread: " << Thread::get_id() << endl << flush;
  hmCout->unlock();

  delete v;
}



void app_server::setup_view_seats()
{
  mvcc_db = os_database::open_mvcc(DBNAME);
  OS_BEGIN_TXN(tx1, 0, os_transaction::read_only)
    os_database_root *a_root = mvcc_db->find_root("count");
    mvcc_countp = (int*) (a_root->get_value());
  OS_END_TXN(tx1)
}

void app_server::setup_buy_seats()
{
  update_db = os_database::open(DBNAME);
  OS_BEGIN_TXN(tx1, 0, os_transaction::update)
    os_database_root *a_root = update_db->find_root("count");
    update_countp = (int*) (a_root->get_value());
  OS_END_TXN(tx1)
}


value_list *app_server::view_seats(value_list* v)
{
  value_list *vl = new value_list();
  /* caller is responsible for serializing access to mvcc_countp */
  vl->insert(*(int*)mvcc_countp.resolve());
  vl->insert(v->first()->get_float_value());
  vl->insert(v->next()->get_string_value());
  return vl;
}

value_list *app_server::buy_seats(value_list* v)
{
  /* caller is responsible for serializing access to update_countp */
  ++*(int*)update_countp.resolve();
  value_list *vl = new value_list();
  vl->insert(*(int*)update_countp.resolve());
  vl->insert(v->first()->get_float_value());
  vl->insert(v->next()->get_string_value());
  return vl;
}


queue *app_server::mvcc_queue = 0;
queue *app_server::update_queue = 0;


int main(int argc, char *argv[])
{
  if (argc < 6) {
    cout << "Usage: app_server <dbname> <latency in secs> ";
    cout << "<num of mvcc threads > 0> <num of update threads > 0> ";
    cout << "<num of requests > 0>" << endl;
    return 1;
  }
  
  DBNAME = argv[1];
  MAX_LATENCY = atof(argv[2]);
  NUM_MVCC_THREADS = atoi(argv[3]);
  NUM_UPDATE_THREADS = atoi(argv[4]);  
  NUM_REQUESTS = atoi(argv[5]);  
  if (NUM_MVCC_THREADS <= 0 || NUM_UPDATE_THREADS <= 0 || NUM_REQUESTS <= 0) {
    cout << "Usage: app_server <latency in secs> ";
    cout << "<num of mvcc threads > 0> <num of update threads > 0> ";
    cout << "<num of requests > 0>" << endl;
    return 1;
  }

  if (NUM_MVCC_THREADS + NUM_UPDATE_THREADS > MAX_THREADS) {
    cout << "Total number of threads cannot exceed " << MAX_THREADS << ".";
    cout << "You specified " << NUM_MVCC_THREADS << " mvcc threads and " ;
    cout << NUM_UPDATE_THREADS << " update threads." << endl;
    return 1;
  }

  Thread::initialize();  // initialize the thread portability layer
  
  hmCout = new Mutex((char*)"cout");
  hmMvccAccess = new Mutex((char*)"mvccAccess");
  hmUpdateAccess = new Mutex((char*)"updateAccess");
  hmRefresh = new Mutex((char*)"refresh");


  cout << MAX_LATENCY << " " << NUM_MVCC_THREADS << " " <<
    NUM_UPDATE_THREADS << " " << NUM_REQUESTS << endl;

   OS_ESTABLISH_FAULT_HANDLER // required b/c this is top level of a thread

   // turn on ObjectStore multiple-session support
   objectstore::initialize_for_sessions(2);
 
   // create 2 sessions, a writer and reader
   update_session = os_session::create("update_session");
   mvcc_session = os_session::create("mvcc_session");

   // create queues
   app_server::init();

   // start update thread
   app_server::startup_update_processing();
   
   // start mvcc threads
   app_server::startup_mvcc_processing();
  
   // accept requests and route them to the appropriate session
   app_server::route_requests();
   
   // cleanup sessions
   app_server::cleanup_update_processing();
   app_server::cleanup_mvcc_processing();
  
   // cleanup ObjectStore os_session objects
   delete update_session;
   delete mvcc_session;
   
   cout << "Done." << endl;

   OS_END_FAULT_HANDLER

   objectstore::shutdown();

   return 0;
}

void error(const char *msg)
{
  cout << "ERROR: " << msg << "\n" <<flush;
  exit(0);
}

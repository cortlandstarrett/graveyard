#include <ostore/ostore.hh>
#include <assert.h>
#if defined(PTHREADS)
#include <pthread.h>
#elif defined(WIN32)
#include <windows.h>
#endif
#include "queue.hh"
#include "osint.hh"


float MAX_LATENCY;
int NUM_MVCC_THREADS;
int NUM_UPDATE_THREADS;
int NUM_REQUESTS;

class app_server
{
private:
	static queue *mvcc_queue;
	static queue *update_queue;

public:
        static void init();

	static void route_requests();
	static request *get_request();
        static void schedule_mvcc_request(request&);
        static void schedule_update_request(request&);

  	static unsigned int STDCALL service_update_requests(void*);
  	static unsigned int STDCALL  service_mvcc_requests(void*);
        static request *get_mvcc_request();
        static request *get_update_request();

      	static void send_reply(value_list*);

        static void startup_mvcc_processing();
        static void cleanup_mvcc_processing();
	static void startup_update_processing();
        static void cleanup_update_processing();

        static void refresh_if_needed();

        static void setup_view_seats();
        static void setup_buy_seats();

	static value_list *view_seats(value_list*);
	static value_list *buy_seats(value_list*);

};









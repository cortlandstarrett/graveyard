#include "osu_txn_observer.hh"
#include "osu_sessmgt.hh"
#include "osu_vector.hh"
#include <ostore/osreleas.hh>

#define FOR_EACH(VECTOR,ELEMENT)                                    \
    {  unsigned short n = VECTOR->cardinality();                    \
       for (unsigned short i = 0; i < n; i++) {                     \
           void* aHook = (*VECTOR)[i];                              \
           osu_txn_observer* ELEMENT = (osu_txn_observer*) aHook;   \
           if (ELEMENT) {

#define END_FOR       }}}


static void txn_handler(const os_transaction_hook::event_type et,
			const os_transaction*                 txn)
{
  osu_sessdata_ptr<osu_vector> hooks("__osu_txn_observer__");
  osu_vector* hookList = hooks;
  if (hookList) {
    FOR_EACH(hookList,anObserver) {
	anObserver->handle(et,txn);
    } END_FOR;
  }
}

static osu_vector* txn_observer_initialize(void*)
{
  os_transaction_hook::register_hook(os_transaction_hook::after_begin,
				     txn_handler);
  os_transaction_hook::register_hook(os_transaction_hook::before_commit,
				     txn_handler);
  os_transaction_hook::register_hook(os_transaction_hook::after_commit,
				     txn_handler);
  os_transaction_hook::register_hook(os_transaction_hook::before_abort,
				     txn_handler);
#if OS_MAJOR_RELEASE > 5
  os_transaction_hook::register_hook(os_transaction_hook::after_abort,
				     txn_handler);
#endif
  os_transaction_hook::register_hook(os_transaction_hook::before_retry,
				     txn_handler);
  os_transaction_hook::register_hook(os_transaction_hook::before_rpc,
				     txn_handler);
  os_transaction_hook::register_hook(os_transaction_hook::before_finish_xa_commit,
				     txn_handler);
  os_transaction_hook::register_hook(os_transaction_hook::before_retry,
				     txn_handler);

  return new osu_vector(10);
}

void osu_txn_observer::subscribe(osu_txn_observer* observer)
{
  osu_sessdata_ptr<osu_vector> hooks("__osu_txn_observer__",
					&txn_observer_initialize);
  hooks->insert(observer);
}

void osu_txn_observer::unsubscribe(osu_txn_observer* observer)
{
  osu_sessdata_ptr<osu_vector> hooks("__osu_txn_observer__");
  osu_vector* hookList = hooks;
  if (hookList) {
    hookList->remove(observer);
  }
}



osu_txn_observer::~osu_txn_observer()
{
  osu_txn_observer::unsubscribe(this);
}


void osu_txn_observer::handle(const os_transaction_hook::event_type et,
			      const os_transaction* txn)
{
  switch (et) {
  case os_transaction_hook::after_begin:
    after_begin(txn);
    break;
  case os_transaction_hook::before_commit:
    before_commit(txn);
    break;
  case os_transaction_hook::after_commit:
    after_commit();
    break;
  case os_transaction_hook::before_abort:
    before_abort(txn);
    break;
#if OS_MAJOR_RELEASE > 5
  case os_transaction_hook::after_abort:
    after_abort();
    break;
#endif
  case os_transaction_hook::before_retry:
    before_retry();
    break;
  case os_transaction_hook::before_rpc:
    before_rpc(txn);
    break;
  case os_transaction_hook::before_finish_xa_commit:
    before_finish_xa_commit();
  default:
    break;
  };
}


/* default do nothing implementations. */


void osu_txn_observer::after_begin(const os_transaction* txn)
{
	;
}



void osu_txn_observer::before_commit(const os_transaction* txn)
{
	;
}



void osu_txn_observer::before_abort(const os_transaction* txn)
{
	;
}



void osu_txn_observer::before_rpc(const os_transaction* txn)
{
	;
}



void osu_txn_observer::before_finish_xa_commit()
{
	;
}



void osu_txn_observer::before_retry()
{
	;
}



void osu_txn_observer::after_commit()
{
	;
}



void osu_txn_observer::after_abort()
{
	;
}

#ifndef OSU_TXN_OBSERVER_HH
#define OSU_TXN_OBSERVER_HH

#include "base.hh"
#include <ostore/ostore.hh>
#include <ostore/tranhook.hh>

class OSUEXPORT osu_txn_observer {
public:
  osu_txn_observer() { ; }

  static void subscribe(osu_txn_observer* observer);
  static void unsubscribe(osu_txn_observer* observer);

public:
  virtual ~osu_txn_observer();

public:
  // the default handler calls the following virtual functions.

  virtual void handle(const os_transaction_hook::event_type,
		      const os_transaction* txn);

public:
  // you can either override default handler or any of methods below.
  // default implementation below is an empty function.

  virtual void after_begin(const os_transaction* txn);
  virtual void before_commit(const os_transaction* txn);
  virtual void before_abort(const os_transaction* txn);
  virtual void before_rpc(const os_transaction* txn);
  virtual void before_finish_xa_commit();
  virtual void before_retry();
  virtual void after_commit();
  virtual void after_abort();

private:  // not allowed...
  osu_txn_observer(const osu_txn_observer&);
  osu_txn_observer& operator=(const osu_txn_observer&);

};

#endif

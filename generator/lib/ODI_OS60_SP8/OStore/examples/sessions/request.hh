/*** request.hh ***/
#include "value_list.hh"

class request
{
public:
  enum request_type {end, buy, view};
  enum txn_type {mvcc, update};

private:
  request_type optype;
  value_list *opargs;
  txn_type txtype;

public:
  request(request_type name, value_list *args, txn_type t) {
    optype = name; opargs = args; txtype = t;
  }

  request_type get_type() const {return optype;}
  value_list *get_args() const {return opargs;}
  txn_type get_txn_type() const {return txtype;}

  ~request() {delete opargs;}

};


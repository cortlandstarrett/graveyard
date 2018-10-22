#ifndef _QUEUE_HH
#define _QUEUE_HH

#include "osint.hh"
#include "request.hh"

class mt_cond_internal;
class queue_entry
{
private:
  queue_entry *rest;
  request *first;

public:
  queue_entry(request &r) {first = &r; rest = 0;}
  queue_entry *get_rest() const {return rest;}
  void set_rest(queue_entry *e){rest = e;}
  request *get_first() const {return first;}
  void set_first(request *r) {first = r;}
};

class queue
{
private:
  queue_entry *first;
  queue_entry *last;
  Mutex *hmQueue;
  unsigned int cnt;
  mt_cond_internal *cond;
public:
  void insert (request &r);
  request *remove();
  queue();
};

#endif

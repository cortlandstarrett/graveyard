#ifndef osu_mutex_hh
#define osu_mutex_hh

#include <ostore/ostore.hh>
#include "osu_low.hh"

class osu_mutex
{
public:
  typedef char boolean;
public:
  void lock();
  boolean try_lock();
  void unlock();
  osu_mutex(): n_locked_(0){}
  ~osu_mutex(){}

private:
  friend class osu_event;

  inline operator osu_low::mutex&(){ return mutex_; }
  inline operator osu_low::place&(){ return place_; }
  inline void lock_internal();
  inline void unlock_internal();

private:
  osu_low::mutex mutex_;
  osu_low::place place_;
  int n_locked_;
};

class osu_event
{
public:
  void signal(osu_mutex& m);
  void broadcast(osu_mutex& m);
  void wait(osu_mutex& m);
  int n_thread(){ return n_thread_; }
  osu_event():
    n_thread_(0),
    op_(ev_waiting)
  {}
  ~osu_event(){}

private:
  int n_thread_;
  enum { ev_waiting, ev_signal, ev_broadcast } op_;
  osu_low::place place_;
};

class osu_sync : private basic_undo
{
public:
  osu_sync(osu_low::mutex& m): mutex_(&m){ mutex_->lock(); }
  ~osu_sync(){ mutex_->unlock(); }
private:
  osu_low::mutex* mutex_;
};

////////////////////////////////////////////////////////////////////////

void osu_mutex::lock_internal()
{
  n_locked_++;
}

void osu_mutex::unlock_internal()
{
  n_locked_--;
  if (n_locked_ == 0){
    place_.signal();
  }
}


#endif // _osu_mutex_h

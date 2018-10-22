#include "osu_mutex.hh"
#include "osu_low.hh"

void osu_mutex::lock()
{
  mutex_.lock();

  /* This is expensive why is it done. */
  while (n_locked_ > 0){
    place_.wait(mutex_);
  }
  lock_internal();

}

osu_mutex::boolean osu_mutex::try_lock()
{
  if (n_locked_ == 0){
    mutex_.lock();
    if (n_locked_ == 0){
      lock_internal();
      return 1;
    }
    mutex_.unlock();
  }
  return 0;
}

void osu_mutex::unlock()
{
  /* unlock internal is expensive why is it done. */
  unlock_internal();
  mutex_.unlock();
}

////////////////////////////////////////////////////////////////////////


void osu_event::signal(osu_mutex& m)
{
  if (n_thread_ == 0) return;
  switch(op_){
  case ev_waiting:
    op_ = ev_signal;
    m.lock_internal();
    break;
  case ev_signal:
    break;
  case ev_broadcast:
    break;
  }
  place_.signal();
}

void osu_event::broadcast(osu_mutex& m)
{
  if (n_thread_ == 0) return;
  switch(op_){
  case ev_waiting:
    op_ = ev_broadcast;
    m.lock_internal();
    break;
  case ev_signal:
    op_ = ev_broadcast;
    break;
  case ev_broadcast:
    break;
  }
  place_.signal();
}

void osu_event::wait(osu_mutex&m)
{
  osu_low::mutex& lm = m;
  n_thread_++;

  m.unlock_internal();
  for(;;){
    switch(op_){
    case ev_waiting:
      place_.wait(lm);
      continue;
    case ev_signal:
      n_thread_--;
      op_ = ev_waiting;
      break;
    case ev_broadcast:
      n_thread_--;
      if (n_thread_ == 0){
	op_ = ev_waiting;
      } else {
	m.lock_internal();
	place_.signal();
      }
      break;
    }
    break;
  }
}

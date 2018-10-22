#ifndef osu_low_hh
#define osu_low_hh

class osu_mutex;
class osu_event;
class osu_low
{
public:
  friend class osu_mutex;
  friend class osu_event;
  class mutex;
  class place;
  friend class osu_low::mutex;
  friend class osu_low::place;
};


#ifndef WIN32
#include <pthread.h>

////////////////////////////////////////////////////////////////////////

class osu_low::mutex
{
public:
  inline void lock(){ pthread_mutex_lock(&mutex_); }
  inline void unlock(){ pthread_mutex_unlock(&mutex_); }

public:
  inline mutex(){ pthread_mutex_init(&mutex_,0); }
  inline ~mutex(){ pthread_mutex_destroy(&mutex_); }

private:
  friend class osu_low::place;
  pthread_mutex_t* pthread_mutex(){ return &mutex_; }

  pthread_mutex_t mutex_;
};

////////////////////////////////////////////////////////////////////////

class osu_low::place
{
public:
  inline void wait(osu_low::mutex& m){
    pthread_cond_wait(&queue_, m.pthread_mutex()); }
  inline void signal(){ pthread_cond_signal(&queue_); }
  inline place(){ pthread_cond_init(&queue_, 0); }
  inline ~place(){
    pthread_cond_broadcast(&queue_);
    pthread_cond_destroy(&queue_);
  }
private:
  pthread_cond_t queue_;
};

#else /* WIN32 */
#include <windows.h>

////////////////////////////////////////////////////////////////////////

class osu_low::mutex
{
public:
  inline void lock(){ EnterCriticalSection(&critical_section_); }
  inline void unlock(){ LeaveCriticalSection(&critical_section_); }

public:
  inline mutex(){ InitializeCriticalSection(&critical_section_); }

  inline ~mutex(){ DeleteCriticalSection(&critical_section_); }

private:
  CRITICAL_SECTION critical_section_;
};

////////////////////////////////////////////////////////////////////////

class osu_low::place
{
public:
  inline void wait(osu_low::mutex& m)
  {
    m.unlock();
    WaitForSingleObject(event_, INFINITE);
    m.lock();
    ResetEvent(event_);
  }
  inline void signal(){ 
    SetEvent(event_);
  }

  inline place()
  {
    event_ = CreateEvent(0,
			 TRUE /* Manual Reset*/,
			 FALSE /* Initial State */,
			 0 /* name */
			 );
  }
  inline ~place(){ CloseHandle(event_); }
private:
  HANDLE event_;
};
#endif /* WIN32 */

#endif // _osu_low_hh


#include <string.h>
#include <iostream.h>
#include <assert.h>


#if defined (PTHREADS)

#include <pthread.h>
#include <sched.h>
#include <errno.h>
typedef	struct _thrd_cond_t {
  pthread_cond_t Cond;
  long nwaiters; /* number of waiting threads */
  int Errno; 
} thrd_cond_t;

#elif defined (WIN32)

#include <windows.h>
#include <process.h>
#include <time.h>
typedef	struct	_thrd_cond_t {
  long nwaiters; /* Number of waiting threads. */
  CRITICAL_SECTION waiters_lock; /* Serialize access to the waiters count. */
  HANDLE sema; /* Semaphore used to queue up threads waiting
                ** for the condition to become signaled. */
  HANDLE waiters_done; /* An auto reset event used by the broadcast/signal 
                        ** thread to wait for all the waiting thread(s) to 
                        ** wake up and be released from the semaphore. */
  size_t was_broadcast; /* Keeps track of whether we were broadcasting 
                         ** or signaling.  This allows us to optimize the
                         ** code if we're just signaling. */
  int Errno; 
} thrd_cond_t;

#else

#include "This example only supports for PTHREADS or the Windows thread API"

#endif

#include "queue.hh"

class mt_cond_internal {
private:
  thrd_cond_t cond_state;
public:
  void create();
  void wait(Mutex *mutex);
  void broadcast();
  void destroy();
  int get_errno() { return cond_state.Errno; }
};


// Condition variables.

void
mt_cond_internal::create() {
#if defined (PTHREADS)
  cond_state.nwaiters = 0;
  int rval = pthread_cond_init(&cond_state.Cond, NULL);
  if (rval == -1) {
      cond_state.Errno = rval;
      cout << "pthread_cond_init returned: " << rval << ", errno:" << cond_state.Errno;
      exit(1);
  }
#elif defined (WIN32)
  cond_state.nwaiters = 0;
  cond_state.was_broadcast = 0;
  cond_state.sema = 
    CreateSemaphore (0, // no security
		     0, // non-signaled
		     0x7fffffff, // max count
		     0); // unnamed 
  if (!cond_state.sema) {
      cout << "CreateSemaphore returned NULL";
      exit(1);
    }
  InitializeCriticalSection (&cond_state.waiters_lock);
  cond_state.waiters_done = 
    CreateEvent (0, // no security
		 FALSE, // auto-reset
		 FALSE, // non-signaled 
		 NULL); // unnamed
  if (cond_state.waiters_done == NULL) {
      cout << "CreateEvent returned NULL";
      exit(1);
    }
#endif
}


void
mt_cond_internal::wait(Mutex *mutex) {
#if defined (PTHREADS)
  ++cond_state.nwaiters;
  int rval = pthread_cond_wait(&cond_state.Cond,
			       (pthread_mutex_t*)mutex->get_id());

  if (rval != 0) {
      cond_state.Errno = rval;
      cout << "pthread_cond_wait returned: " << rval << ", errno: " << cond_state.Errno;
      exit(1);      
    }
  --cond_state.nwaiters;
#elif defined (WIN32)
  // It's ok to increment the number 
  // of waiters since <external_mutex> 
  // must be locked by the caller.
  cond_state.nwaiters++;

  // We don't build special for windows NT 4.0.
  // But if we did then there is a more efficient way...
  //
#if defined (SIGNAL_OBJECT_AND_WAIT) /* NT 4.0 only */
  // This call will automatically release 
  // the mutex and wait on the semaphore
  // until cond_signal() or cond_broadcast()
  // are called by another thread.
  DWORD rc = SignalObjectAndWait(mutex->get_id(),
			   cond_state.sema,
			   INFINITE, FALSE);
  if (rc == 0xFFFFFFFF) {
      cout << "SignalObjectAndWait returned: " <<  rc;
      exit(1);
    }

#else /* NT 3.51 or Win95 */
  // Keep the lock held just long enough to 
  // increment the count of waiters by one.  
  // We can't keep it held across the call
  // to WaitForSingleObject() since that will 
  // deadlock other calls to pthread_cond_signal()
  // and pthread_cond_broadcast().
  if (!ReleaseMutex(mutex->get_id())) {
      cout << "ReleaseMutex returned zero";
      exit(1);
    }
  
  
  // Wait to be awakened by a pthread_cond_signal() or
  // pthread_cond_broadcast().
  if (WaitForSingleObject(cond_state.sema, INFINITE) == WAIT_FAILED) {
      cout << "WaitForSingleObject returned WAIT_FAILED";
      exit(1);
    }
#endif /* SIGNAL_OBJECT_AND_WAIT */

  // Reacquire lock to avoid race conditions.
  EnterCriticalSection(&cond_state.waiters_lock);

  // We're no longer waiting...
  cond_state.nwaiters--;

  // If we're the last waiter thread
  // during this particular broadcast then
  // let all the other threads proceed.
  if (cond_state.was_broadcast && cond_state.nwaiters == 0) {
      if (!SetEvent(cond_state.waiters_done)) {
	  cond_state.Errno = GetLastError();
	  cout << "SetEvent returned zero, errno: " << cond_state.Errno;
	  exit(1);
	}
    }
  LeaveCriticalSection(&cond_state.waiters_lock);

  // Always regain the external mutex since that's 
  // the guarantee that we give to our callers.
  if (WaitForSingleObject(mutex->get_id(), INFINITE) == WAIT_FAILED) {
      cout << "WaitForSingleObject returned WAIT_FAILED";
      exit(1);
    }
#endif

}


// This method unblocks all threads blocked on the
// this condition variable instance.
//
void
mt_cond_internal::broadcast() {
#if defined (PTHREADS)
  int rval = pthread_cond_broadcast(&cond_state.Cond);
  if (rval == -1) {
      cond_state.Errno = rval;
      cout << "pthread_cond_broadcast returned: " << rval << ", errno: " << cond_state.Errno;
      exit(1);
    }
#elif defined (WIN32)
  // If there aren't any waiters, then this 
  // is a no-op.  
  if (cond_state.nwaiters == 0)
    return;
  else 
    // We are broadcasting, even if there 
    // is just one waiter...
    {
      // Record that we are broadcasting.  
      // This helps optimize cond_wait().
      cond_state.was_broadcast = 1;

      // Wake up all the waiters.
      if (!ReleaseSemaphore(cond_state.sema, cond_state.nwaiters, 0)) {
	  cout << "ReleaseSemaphore returned zero";
	  exit(1);
	}

      // Wait for all the awakened threads to 
      // acquire the counting semaphore. 
      if (WaitForSingleObject(cond_state.waiters_done, INFINITE) == 
	  WAIT_FAILED) {
	  cout << "WaitForSingleObject returned WAIT_FAILED";
	  exit(1);
	}
      cond_state.was_broadcast = 0;
    }
#endif
}


// Destroys the state assocated with this condition variable instance.
void
mt_cond_internal::destroy() {
#if defined (PTHREADS)
  if (cond_state.nwaiters) {
    cout << "destroy has " << cond_state.nwaiters << " waiters!" << endl;
    return;
  }

  int rval = pthread_cond_destroy(&cond_state.Cond);
  if (rval == -1) {
      cond_state.Errno = errno;
      cout << "pthread_cond_destroy returned: " << rval << ", errno: " << cond_state.Errno;
      exit(1);
    }
#elif defined (WIN32)
  CloseHandle(cond_state.sema);
  CloseHandle(cond_state.waiters_done);
#endif
}


void queue::insert (request &r) 
{
  queue_entry *e = new queue_entry(r);
  hmQueue->lock();
  if (last)
    last->set_rest(e);
  last = e;
  if (!first)
    first = e;
  cnt++;
  cond->broadcast();
  hmQueue->unlock();
}


request *
queue::remove() {
  hmQueue->lock();
  while(cnt == 0)
    cond->wait(hmQueue);

  queue_entry *e = first;
  if (!e) {
    hmQueue->unlock();
    return 0;
  }
  first = e->get_rest();
  if (!first)
    last = 0;
  request *r = e->get_first();
  delete e;
  cnt--;
  hmQueue->unlock();
  return r;
}

queue::queue() {
  first = 0; 
  last = 0; 
  cnt = 0;
  cond = new mt_cond_internal;
  if (!cond) {
    cout << "Condition variable create failed";
    exit(1);
  }
  cond->create();
  hmQueue = new Mutex((char*)"queue");
}

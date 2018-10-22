#include <string.h>
#include <iostream.h>

#if defined (PTHREADS)

#include <pthread.h>
#include <sched.h>
#include <stdlib.h>
#include <sys/time.h>

#elif defined (WIN32)

#include <windows.h>
#include <process.h>
#include <time.h>

#else

#include "This example only supports for PTHREADS or the Windows thread API"

#endif

#include "osint.hh"




Mutex::Mutex(char* _name) {
  name = (char*)new char[(strlen(_name)+1)];
  strcpy(name,_name);
  
#if defined (PTHREADS)
  pthread_mutex_init(&theMutex, NULL);
#elif defined (WIN32)
  theMutex = CreateMutex(NULL,FALSE,_name);
#endif
}


void Mutex::lock() {
#if defined (PTHREADS)
  pthread_mutex_lock((pthread_mutex_t *)&theMutex);
#elif defined (WIN32)
  WaitForSingleObject(theMutex, INFINITE);
#endif
}

void Mutex::unlock() {
#if defined (PTHREADS)
  pthread_mutex_unlock((pthread_mutex_t *)&theMutex);
#elif defined (WIN32)
  ReleaseMutex(theMutex);
#endif
}

int Thread::thread_count=0;
#if defined(PTHREADS)
pthread_t Thread::threadids[MAX_THREADS];
#elif defined(WIN32)
HANDLE Thread::threadids[MAX_THREADS];
#endif

Mutex* Thread::hmThreadCount = 0;

void Thread::initialize() {
  /* caller is responsible for making sure this is called in a thread
     safe manner */
  hmThreadCount = new Mutex((char*)"threadCount");
}

void Thread::create(unsigned int (STDCALL *method)(void*)) {
  int bogus;

#if defined (PTHREADS)
  pthread_t threadid;
  pthread_create(&threadid, NULL, (void* (*)(void*))method, NULL);
#elif defined (WIN32)
  HANDLE threadid;

  (HANDLE) threadid =
    (HANDLE)_beginthreadex(NULL,NULL,
			   (unsigned int (__stdcall *)(void*))method,
			   NULL, CREATE_SUSPENDED,
			   (unsigned int *)&bogus);
  ResumeThread(threadid);
#endif

  hmThreadCount->lock();
  threadids[thread_count] = threadid;
  thread_count++;
  hmThreadCount->unlock();
} 


void Thread::wait_on_threads(int num_mvcc, int num_update) {
  extern Mutex *hmCout;
  while(1) {
    hmThreadCount->lock();
    if (thread_count == num_mvcc + num_update) {
      hmThreadCount->unlock();
      break;
    }
    hmThreadCount->unlock();
  }

  int thr_count = num_mvcc + num_update;
  for (int i = 0; i < thr_count; i++) {
#if defined (PTHREADS)
    pthread_join((pthread_t)threadids[i], NULL);
#else
    WaitForSingleObject(threadids[i],INFINITE);
#endif
  }
}

#if defined (PTHREADS)
pthread_t Thread::get_id(void) {

  return pthread_self();
#elif defined (WIN32)
int Thread::get_id(void) {

  return GetCurrentThreadId();
#endif

}

long Time::get_time_in_secs() {
#if defined (PTHREADS)
  struct timeval t0;
  struct timezone tz;

  gettimeofday(&t0, &tz);
  return t0.tv_sec;
#elif defined (WIN32)
  time_t ltime;
  time(&ltime);
  return ltime;
#endif
}



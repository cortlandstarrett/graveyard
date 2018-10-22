#ifndef _OSINT_HH
#define _OSINT_HH


#if defined (PTHREADS)
#define STDCALL 
#elif defined (WIN32)
#define STDCALL __stdcall
#endif

class Mutex {
private:
#if defined(PTHREADS)
  pthread_mutex_t theMutex;
#elif defined(WIN32)
  HANDLE theMutex;
#endif
  char*  name;
public:
  Mutex(char* _name);
  void lock();
  void unlock();

#if defined(PTHREADS)
  pthread_mutex_t *get_id() { return &theMutex; }
#elif defined(WIN32)
  HANDLE get_id() { return theMutex; }
#endif
};

class Time {
public:
  static long get_time_in_secs();
};

const int MAX_THREADS= 20;


class Thread {
  static Mutex* hmThreadCount;
#if defined(PTHREADS)
  static pthread_t threadids[MAX_THREADS];  
#elif defined(WIN32)
  static HANDLE threadids[MAX_THREADS];
#endif

  static int thread_count;
private:
  Thread();
  
public:
  static void initialize();
  static void create(unsigned int (STDCALL *method)(void*));
  static void wait_on_threads(int num_mvcc, int num_update);
#if defined(PTHREADS)
  static pthread_t get_id(void);
#elif defined(WIN32)
  static int get_id(void);
#endif
};

#endif  // #ifndef _OSINT_HH

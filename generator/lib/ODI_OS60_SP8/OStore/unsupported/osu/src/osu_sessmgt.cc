#include <ostore/ostore.hh>
#include <ostore/osreleas.hh>
#include <iostream.h>
#include <string.h>
#include "osu_sessmgt.hh"
#include "osu_mutex.hh"

/* this is temporary, I don't want to use ObjectStore collections.
   So I'm hardcoding a max size and simple iteration.  A real hashtable
   or map should be implemented.
*/

#define STREQ(A,B) (::strcmp(A,B) == 0)

static osu_low::mutex* g_mutex = new osu_low::mutex();

class osu_sess_table {
public:
  struct entry {
    entry() { _key = 0; _value = 0; }
    char* _key;
    void* _value;
  };

  osu_sess_table() { ; }
  ~osu_sess_table() { ; }
  void  insert(const char* key, void* value);
  void* pick(const char* key);

private:
  osu_low::mutex  _mutex;
  entry           _entries[1024];
};

void osu_sess_table::insert(const char* key, void* value)
{
  osu_sync sync(_mutex);

  int n = 0;
  while (_entries[n]._key) {
    if (STREQ(_entries[n]._key,key)) {
      _entries[n]._value = value;
      return;
    }
    static int nentries = sizeof(_entries)/sizeof(_entries[0]);
    if (++n == nentries) {
      cerr << "osu_sess_table is full" << endl;
      exit(0);
      return;
    }
  }

  // insert into table at n.
  _entries[n]._key = ::strdup(key);
  _entries[n]._value = value;
}

void* osu_sess_table::pick(const char* key)
{
  osu_sync sync(_mutex);

  int n = 0;
  while (_entries[n]._key) {
    if (STREQ(_entries[n]._key,key)) {
      return _entries[n]._value;
    }
    static int nentries = sizeof(_entries)/sizeof(_entries[0]);
    if (++n == nentries) break;
  }
  return 0;
}

#if OS_MAJOR_RELEASE < 6
static void* theDICTIONARY = 0;
#endif

// TBD: are sessions dynamic.  Do I need to worry about cleanup when a
// session is deleted.  If so then I need another API.

void* osu_session_data::get(const char* name)
{
#if OS_MAJOR_RELEASE > 5
  os_session* currentSESSION = os_session::get_current();
  if (currentSESSION == 0) {
    return 0;
  }

  void* theDICTIONARY = currentSESSION->get_value();
#endif

  void* theVALUE = 0;
  if (theDICTIONARY != 0) {
    osu_sess_table* theTABLE =
      (osu_sess_table*) theDICTIONARY;
    theVALUE = theTABLE->pick(name);
  }
  return theVALUE;
}


void osu_session_data::set(const char* name, void* value)
{
#if OS_MAJOR_RELEASE > 5
  os_session* currentSESSION = os_session::get_current();
  if (currentSESSION == 0) return;

  void* theDICTIONARY = currentSESSION->get_value();

  if (theDICTIONARY == 0) {
    theDICTIONARY = new osu_sess_table();
    currentSESSION->set_value(theDICTIONARY);
  }
#else
  if (theDICTIONARY == 0) {
      theDICTIONARY = new osu_sess_table();
  }
#endif

  osu_sess_table* theTABLE = 
    (osu_sess_table*) theDICTIONARY;
  theTABLE->insert(name,value);
}

void osu_session_data::acquire_lock(const char* name)
{
  g_mutex->lock();
}

void osu_session_data::release_lock(const char* name)
{
  g_mutex->unlock();
}

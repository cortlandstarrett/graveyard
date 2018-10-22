#ifndef OSU_SESSMGT_HH
#define OSU_SESSMGT_HH

#include "base.hh"
#include <ostore/ostore.hh>
#include <string.h>
#include <stdlib.h>

class OSUEXPORT osu_session_data {
public:
  static void* get(const char* name);
  static void  set(const char* name, void* value);
  static void  acquire_lock(const char* name);
  static void  release_lock(const char* name);
};

class osu_sessdata_mutex :public basic_undo {
public:
  osu_sessdata_mutex(const char* n) {
    _name = n;
    osu_session_data::acquire_lock(_name);

  }
  ~osu_sessdata_mutex() {
    osu_session_data::release_lock(_name);
  }
private:
  const char* _name;
};

template <class T>
class osu_sessdata_ptr :public basic_undo {
public:
  typedef T* (* init_func)(void* args);
public:
  osu_sessdata_ptr(const char* n)
    : _name(n),
      _value((T*)osu_session_data::get(n))
    {
      ;
    }

  osu_sessdata_ptr(const char* n, init_func func, void* args = 0)
    : _name(n),
      _value(0)
    {
      _value = (T*) osu_session_data::get(_name);
      if ((_value == 0) && (func != 0)) {
	osu_sessdata_mutex mutex(_name);
	if ((T*) osu_session_data::get(_name) == 0) {
	  _value = (*func)(args);
	  osu_session_data::set(_name,(void*) _value);
	}
      }
    }

  ~osu_sessdata_ptr() { ; }

  T* operator =(T* value) {
    // the delete is problematic for private, protected,
    // destructors. What should we do?

    osu_sessdata_mutex mutex(_name);

    if (_value) delete (T*) _value;

    osu_session_data::set(_name,(void*)value);
    _value = (T*) osu_session_data::get(_name);

    return _value;
  }

  operator T*()       {     return _value;  }
  operator T*() const {     return _value;  }
  T* operator->()     {     return _value; }
    
  operator int() {
    return (_value != 0);
  }

protected:
  const char*  _name;
  T*           _value;
};


#endif

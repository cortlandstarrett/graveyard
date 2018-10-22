/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef _OS_COLL_os_dictionary_slot
#define _OS_COLL_os_dictionary_slot
#ifndef _OS_PSE_COLL
#include <ostore/hdrstart.hh>
#else
#include <os_pse/psecoll/hdrstart.hh>
_OS_BEGIN_NAMESPACE(os_pse)
#endif

/*****************************************************************************/
/*****************************************************************************/

template<class KT > class os_dictionary_key;
template<class K > struct os_dk_wrapper;

template<class K >
struct os_dk_wrapper
{
  K val;
  os_unsigned_int32 _hashval;

  os_dk_wrapper() {}
  ~os_dk_wrapper() { _hashval = 0; }
  inline void die();

  os_boolean eq(_Rank_fcn rfn, K const* key) const
    { return !(*rfn)(key, &val); }
  void* key() {return (void*)&val;}  
  os_unsigned_int32 hashval() { return _hashval; }
  void set_hashval(os_unsigned_int32 h) { _hashval = h; }

  void assign(const os_dk_wrapper<K>* dk)
    { *this = *dk; }

  void operator=(const K& k) { val = k; }
  operator K&() { return val; }
  operator const K&() const { return val; }

  os_boolean returns_point_to_key() {return 1;}
  static inline const char* _type();
  static os_boolean _functions(_Rank_fcn&, _Hash_fcn&) { return 0; }
};

typedef char* os_outsmart_cafe_d_key_char;

#ifdef __os_sol2c5
template<>
#endif
struct os_dk_wrapper<char*>
{
  os_soft_pointer<char> val;
  os_unsigned_int32 _hashval;
 
  os_dk_wrapper() { val = 0; }
  ~os_dk_wrapper() { if (val) delete [] (char*)val; val = 0; _hashval = 0; }
  void die() { if (val) delete [] (char*)val; val = 0; _hashval = 0; }
  
  os_unsigned_int32 hashval() { return _hashval; }
  void set_hashval(os_unsigned_int32 h) { _hashval = h; }
  void* key() {return (void*)(char*) val;}
  os_boolean eq(_Rank_fcn rfn, char const * key) const 
  { 
     char * deref_key = val;
     return !(*rfn)(key, &deref_key); 
  }  
  
  void assign(const os_dk_wrapper<char*>* dk)
    { val = dk->val; _hashval = dk->_hashval; }

  void set_key(char * k)
    {
      if (val)
        delete [](char*) val;
      val = k;
    }	

  void operator=(const char* k) 
    { 
      if (val)
	delete [] (char*)val;
      os_int32 size = strlen(k) + 1;
      val = new (os_segment::of(this), os_typespec::get_char(), size)
	char[size];
      strcpy(val,k);
    }
  operator os_outsmart_cafe_d_key_char&() { return *(char**)&val; }
  operator const os_outsmart_cafe_d_key_char&() const
    { return *(char*const*)&val; }

  os_boolean returns_point_to_key() {return 0;} 
  static const char* _type() { return "char*"; }
  static os_boolean _functions(_Rank_fcn& rfn, _Hash_fcn& hfn) 
    { rfn = _Str_rank; hfn = _Str_hash_khs; return 1; }
};


template<class K > struct os_dk_wrapper;
#ifdef __os_sol2c5
template<>
#endif
struct os_dk_wrapper<const char *>
{
  os_soft_pointer<char> val;
  os_unsigned_int32 _hashval;

  os_dk_wrapper() { val = 0; }
  ~os_dk_wrapper() { if (val) delete [] (char*)(const char *)val; val = 0; _hashval = 0; }
  void die() { if (val) delete [] (char*)(const char *)val; val = 0; _hashval = 0; }

  os_unsigned_int32 hashval() { return _hashval; }
  void set_hashval(os_unsigned_int32 h) { _hashval = h; }
  void* key() {return (void*)(char*)val;}
  os_boolean eq(_Rank_fcn rfn, char const* key) const
  { 
     char * deref_key = val;
     return !(*rfn)(key, &deref_key); 
  }

  void assign(const os_dk_wrapper<const char *>* dk)
    { val = dk->val; _hashval = dk->_hashval; }

  void set_key(char * k)
    {
      if (val)
        delete [](char*) val;
      val = k;
    }	
        
  void operator=(const os_const_char_p k) 
    { 
      if (val)
	delete (char*)(const char *)val;
      os_int32 size = strlen(k) + 1;
      val = new (os_segment::of(this), os_typespec::get_char(), size)
	char[size];
      strcpy(val,k);
    }
  operator os_outsmart_cafe_d_key_char&() { return *(char**)&val; }
  operator const os_outsmart_cafe_d_key_char&() const
    { return *(char*const*)&val; }

  os_boolean returns_point_to_key() {return 1;}
  static const char* _type() { return "char*"; }
  static os_boolean _functions(_Rank_fcn& rfn, _Hash_fcn& hfn) 
    { rfn = _Str_rank; hfn = _Str_hash_khs; return 1; }
};

#ifdef __os_sol2c5
template<>
#endif
struct os_dk_wrapper<char>
{
  char val;
  char pad[3];
  os_dk_wrapper() {}
  ~os_dk_wrapper() { val = 0; }
  void die() { val = 0; }
 
  os_boolean eq(_Rank_fcn , char const* key) const 
    { return *key == val; }
  void* key() {return (void*)&val;}
  os_unsigned_int32 hashval() { return 0; }
  void set_hashval(os_unsigned_int32) {}

  void assign(const os_dk_wrapper<char>* dk)
    { val = dk->val; }

  void operator=(char k) { val = k; }
  operator char&() { return val; }
  operator const char&() const { return val; }

  os_boolean returns_point_to_key() {return 1;}
  static const char* _type() { return "char"; }
  static os_boolean _functions(_Rank_fcn& rfn, _Hash_fcn& hfn) 
    { rfn = _Char_rank; hfn = _Char_hash; return 1; }
};

#ifdef __os_sol2c5
template<>
#endif
struct os_dk_wrapper<short>
{
  os_int16 val;
  os_int16 pad;
  os_dk_wrapper() {}
  ~os_dk_wrapper() { val = 0; }
  void die() { val = 0; }

  os_boolean eq(_Rank_fcn , os_int16 const* key) const 
    { return *key == val; }
  void* key() {return (void*)&val;}
  os_unsigned_int32 hashval() { return 0; }
  void set_hashval(os_unsigned_int32) {}

  void assign(const os_dk_wrapper<short>* dk)
    { val = dk->val; }

  void operator=(short k) { val = k; }
  operator short&() { return val; }
  operator const short&() const { return val; }

  os_boolean returns_point_to_key() {return 1;}
  static const char* _type() { return "short"; }
  static os_boolean _functions(_Rank_fcn& rfn, _Hash_fcn& hfn) 
    { rfn = _Short_rank; hfn = _Short_hash; return 1; }
};

#ifdef __os_sol2c5
template<>
#endif
struct os_dk_wrapper<unsigned short>
{
  os_unsigned_int16 val;
  os_unsigned_int16 pad;
  os_dk_wrapper() {}
  ~os_dk_wrapper() { val = 0; }
  void die() { val = 0; }

  os_boolean eq(_Rank_fcn,os_unsigned_int16 const* key) const 
    { return *key ==val; }   
  void* key() {return (void*)&val;}
  os_unsigned_int32 hashval() { return 0; }
  void set_hashval(os_unsigned_int32) {}

  void assign(const os_dk_wrapper<unsigned short>* dk)
    { val = dk->val; }

  void operator=(unsigned short k) { val = k; }
  operator unsigned short&() { return val; }
  operator const unsigned short&() const { return val; }

  os_boolean returns_point_to_key() {return 1;}
  static const char* _type() { return "unsigned short"; }
  static os_boolean _functions(_Rank_fcn& rfn, _Hash_fcn& hfn) 
    { rfn = _Ushort_rank; hfn = _Short_hash; return 1; }
};


#ifdef __os_sol2c5
template<>
#endif
struct os_dk_wrapper<unsigned int>
{
  os_unsigned_int32 val;
  os_dk_wrapper() {}
  ~os_dk_wrapper() { val = 0; }
  void die() { val = 0; }
 
  os_boolean eq(_Rank_fcn,os_unsigned_int32 const* key) const 
    { return *key ==val; }
  void* key() {return (void*)&val;}
  os_unsigned_int32 hashval() { return 0; }
  void set_hashval(os_unsigned_int32) {}

  void assign(const os_dk_wrapper<unsigned int>* dk)
    { val = dk->val; }

  void operator=(os_unsigned_int32 k) { val = k; }
  operator os_unsigned_int32&() { return val; }
  operator const os_unsigned_int32&() const { return val; }

  os_boolean returns_point_to_key() {return 1;}
  static const char* _type() { return "unsigned int"; }
  static os_boolean _functions(_Rank_fcn& rfn, _Hash_fcn& hfn) 
    { rfn = _Uint_rank; hfn = _Int_hash; return 1; }
};


#ifdef __os_sol2c5
template<>
#endif
struct os_dk_wrapper<int>
{
  os_int32 val;
  os_dk_wrapper() {}
  ~os_dk_wrapper() { val = 0; }
  void die() { val = 0; }
 
  os_boolean eq(_Rank_fcn,os_int32 const* key) const 
    { return *key == val; }
  void* key() {return (void*)&val;}
  os_unsigned_int32 hashval() { return 0; }
  void set_hashval(os_unsigned_int32) {}

  void assign(const os_dk_wrapper<int>* dk)
    { val = dk->val; }

  void operator=(os_int32 k) { val = k; }
  operator os_int32&() { return val; }
  operator const os_int32&() const { return val; }

  os_boolean returns_point_to_key() {return 1;}
  static const char* _type() { return "int"; }
  static os_boolean _functions(_Rank_fcn& rfn, _Hash_fcn& hfn) 
    { rfn = _Int_rank; hfn = _Int_hash; return 1; }
};

#ifdef __os_sol2c5
template<>
#endif
struct os_dk_wrapper<float>
{
  float val;
  os_dk_wrapper() {}
  ~os_dk_wrapper() { val = (float)0.0; }
  void die() { val = (float)0.0; }

  os_boolean eq(_Rank_fcn , float const* key) const 
    { return *key == val; } 
  void* key() {return (void*)&val;}
  os_unsigned_int32 hashval() { return 0; }
  void set_hashval(os_unsigned_int32) {}

  void assign(const os_dk_wrapper<float>* dk)
    { val = dk->val; }

  void operator=(float k) { val = k; }
  operator float&() { return val; }
  operator const float&() const { return val; }

  os_boolean returns_point_to_key() {return 1;}
  static const char* _type() { return "float"; }
  static os_boolean _functions(_Rank_fcn& rfn, _Hash_fcn& hfn) 
    { rfn = _Float_rank; hfn = _Float_hash; return 1; }
};

#ifdef __os_sol2c5
template<>
#endif
struct os_dk_wrapper<double>
{
  double val;
  os_dk_wrapper() {}
  ~os_dk_wrapper() { val = (double)0.0; }
  void die() { val = (double)0.0; }
 
  os_boolean eq(_Rank_fcn rfn, double const* key) const 
    { return !(*rfn)(key, &val); }
  void* key() {return (void*)&val;}
  os_unsigned_int32 hashval() { return 0; }
  void set_hashval(os_unsigned_int32) {}

  void assign(const os_dk_wrapper<double>* dk)
    { val = dk->val; }

  void operator=(double k) { val = k; }
  operator double&() { return val; }
  operator const double&() const { return val; }

  os_boolean returns_point_to_key() {return 1;}
  static const char* _type() { return "double"; }
  static os_boolean _functions(_Rank_fcn& rfn, _Hash_fcn& hfn) 
    { rfn = _Double_rank; hfn = _Double_hash; return 1; }
};


#ifdef __os_sol2c5
template<>
#endif
struct os_dk_wrapper<unsigned long>
{
  unsigned long val;
  os_dk_wrapper() {}
  ~os_dk_wrapper() { val = 0; }
  void die() { val = 0; }

  os_boolean eq(_Rank_fcn , unsigned long const* key) const 
    { return *key == val; } 
  void* key() {return (void*)&val;}
  os_unsigned_int32 hashval() { return 0; }
  void set_hashval(os_unsigned_int32) {}

  void assign(const os_dk_wrapper<unsigned long>* dk)
    { val = dk->val; }

  void operator=(unsigned long k) { val = k; }
  operator unsigned long&() { return val; }
  operator const unsigned long&() const { return val; }

  os_boolean returns_point_to_key() {return 1;}
  static const char* _type() { return "unsigned long"; }
  static os_boolean _functions(_Rank_fcn& rfn, _Hash_fcn& hfn) 
    { rfn = _Ulong_rank; hfn = _Long_hash; return 1; }
};


#ifdef __os_sol2c5
template<>
#endif
struct os_dk_wrapper<long>
{
  long val;
  os_dk_wrapper() {}
  ~os_dk_wrapper() { val = 0; }
  void die() { val = 0; }

  os_boolean eq(_Rank_fcn , long const* key) const 
    { return *key == val; }
  void* key() {return (void*)&val;}
  os_unsigned_int32 hashval() { return 0; }
  void set_hashval(os_unsigned_int32) {}

  void assign(const os_dk_wrapper<long>* dk)
    { val = dk->val; }

  void operator=(long k) { val = k; }
  operator long&() { return val; }
  operator const long&() const { return val; }
 
  os_boolean returns_point_to_key() {return 1;}
  static const char* _type() { return "long"; }
  static os_boolean _functions(_Rank_fcn& rfn, _Hash_fcn& hfn) 
    { rfn = _Long_rank; hfn = _Long_hash; return 1; }
};

typedef void* os_outsmart_cafe_d_key_pvoid;

#ifdef __os_sol2c5
template<>
#endif
struct os_dk_wrapper<void*>
{
  os_soft_pointer<void> val;
  os_unsigned_int32 _hashval;

  os_dk_wrapper() {}
  ~os_dk_wrapper() { val = 0; _hashval = 0; }
  void die() { val = 0; _hashval = 0; }

  os_unsigned_int32 hashval() { return _hashval; }
  void set_hashval(os_unsigned_int32 h) { _hashval = h; }

  os_boolean eq(_Rank_fcn rfn,  os_void_p const* key) const 
  { 
     void * deref_key = val;
     return !(*rfn)(key, &deref_key); 
  }
  void* key() {return val;}
  operator os_outsmart_cafe_d_key_pvoid&() { return *(void**)&val; }
  operator const os_outsmart_cafe_d_key_pvoid&() const
    { return *(void*const*)&val; }

  void assign(const os_dk_wrapper<void*>* dk)
    { val = dk->val; _hashval = dk->_hashval; }
  
  void operator=(const void* k) { val = (void*)k; }
  
  os_boolean returns_point_to_key() {return 0;}
  static const char* _type() { return "os_pvoid"; }
  static os_boolean _functions(_Rank_fcn& rfn, _Hash_fcn& hfn) 
    { rfn = _Pvoid_rank; hfn = _Pvoid_hash; return 1; }
};

template<class K>
inline const char* os_dk_wrapper<K>::_type()
#ifndef _OS_PSE_COLL
{ return K::get_os_typespec()->get_name(); }
#else
{ return os_ts<K >::get()->get_name(); }
#endif

template<class K>
inline void os_dk_wrapper<K>::die()
#if defined(__CLCC__)
{ val.destroy(); _hashval = 0; }
#else
{ val.K::~K(); _hashval = 0; }
#endif

template<os_int32 n>
class os_char_array {
private:
  char str[n];
public:
  void operator=(const char* s) { strcpy(str, s); }
  os_char_array() { str[0] = 0; }
  os_char_array(const char* s) { strcpy(str,s); }
  ~os_char_array() {}
#if defined(__CLCC__) || defined(__EDG)
  void destroy() { this->~os_char_array(); }
#endif
#if !defined(_LINGUIST_) && !defined(_ODI_LINGUIST_)
  operator char*() { return str; }
  operator const char*() { return str; }
  operator char*() const{ return (char*)str; }
  operator const char*() const { return str; }
#else
  operator char*();
  operator const char*();
  operator char*() const;
  operator const char*() const;
#endif
  static os_typespec* get_os_typespec();
};

class os_char_star_nocopy {
public:
  char* _str;
public:
  os_char_star_nocopy() {}
  os_char_star_nocopy(char const* str) { _str = (char*)str; }
  os_char_star_nocopy(char* str) { _str = str; }
  ~os_char_star_nocopy() {}

#if !defined(_LINGUIST_) && !defined(_ODI_LINGUIST_)
  operator char*() const{ return (char*)_str; }
  operator const char*() const { return _str; }
#else
  operator char*() const;
  operator const char*() const;
#endif

  static os_typespec* get_os_typespec();
};

#ifdef __os_sol2c5
template<>
#endif
struct os_dk_wrapper<os_char_star_nocopy>
{
  os_char_star_nocopy val;
  os_unsigned_int32 _hashval;
  os_dk_wrapper() {}
  ~os_dk_wrapper() { val._str = 0; }
  void die() { val._str = 0; }

  void assign(const os_dk_wrapper<os_char_star_nocopy>* dk)
    { val._str = dk->val._str; _hashval = dk->_hashval; }

  os_boolean eq(_Rank_fcn rfn, os_char_star_nocopy const* key) const 
  {
    return !(*rfn)((void*)&val, (const void*)key); 
  }
  void* key() {return (void*)(char*)val._str;}
  os_unsigned_int32 hashval() { return _hashval; }
  void set_hashval(os_unsigned_int32 h) { _hashval = h; }

  void operator=(char const* k) { val._str = (char*)k; }
  operator os_outsmart_cafe_d_key_char&()
    { return *(char**)&val._str; }
  operator const os_outsmart_cafe_d_key_char&() const
    { return *(char*const*)&val._str; }

  os_boolean returns_point_to_key() {return 0;}
  static const char* _type() { return "os_char_star_nocopy"; }
  static os_boolean _functions(_Rank_fcn& rfn, _Hash_fcn& hfn) 
    { rfn = _Str_rank; hfn = _Str_hash_khs; return 1; }
};


#ifdef _OS_ANSI_TOKENS
#define _STRINGIFY(x) #x
#else
#define _STRINGIFY(x) "x"
#endif

/* Since these files will be included for PSE the second time when using both 
   OStore and PSE we want to redefine these macros.
*/
#ifdef OS_TRANSIENT_DICTIONARY_KEY
#undef OS_TRANSIENT_DICTIONARY_KEY
#endif
#ifdef OS_TRANSIENT_CHAR_ARRAY
#undef OS_TRANSIENT_CHAR_ARRAY
#endif
#ifdef OS_TRANSIENT_CHAR_STAR_NOCOPY
#undef OS_TRANSIENT_CHAR_STAR_NOCOPY
#endif

#define OS_TRANSIENT_DICTIONARY_KEY(kt) \
struct _PSE_NS_ os_dk_wrapper<kt> \
{ \
  kt val; \
  const char* _type() { return _STRINGIFY(kt); } \
};

#define OS_TRANSIENT_CHAR_ARRAY(n) \
os_typespec* _PSE_NS_ os_char_array<n>::get_os_typespec() { return 0; }

#define OS_TRANSIENT_CHAR_STAR_NOCOPY \
os_typespec* _PSE_NS_ os_char_star_nocopy::get_os_typespec() { return 0; }


/* The following templates are used by os_Dictionary<KT,VT>::retrieve_key
   for casting to the correct return value.  char* and void* keys return
   the actual key, where all others return a pointer to the key. */
template<class K >
struct os_dk_ptr_type
{
  typedef K* TYPE;
};
#ifdef __os_sol2c5
template<>
#endif
struct os_dk_ptr_type<char*>
{
  typedef char* TYPE;
};
#ifdef __os_sol2c5
template<>
#endif
struct os_dk_ptr_type<const char*>
{
  typedef char* TYPE;
};
#ifdef __os_sol2c5
template<>
#endif
struct os_dk_ptr_type<void*>
{
  typedef void* TYPE;
};
#ifdef __os_sol2c5
template<>
#endif
struct os_dk_ptr_type<os_char_star_nocopy>
{
  typedef char* TYPE;
};

#ifndef _OS_PSE_COLL
#include <ostore/hdrend.hh>
#else
_OS_END_NAMESPACE
#include <os_pse/psecoll/hdrend.hh>
#endif
#endif

/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef _REF_H_
#define _REF_H_
#include <ostore/hdrstart.hh>

#include <ostore/nclient/typespec.hh>
#include <ostore/nclient/softptr.hh>

#define _Ref_transient_seg_id (os_unsigned_int32(0x7fffffff));

class os_notification;
class os_database;
class os_segment;
class os_cluster;
class _CLIENT_cluster_proxy;
class _CLIENT_address_value;

/* Maximum length of portable "handle" for references: 
   (MAX_PATHNAME + some slack for other fields) */
#define MAX_DUMP (os_unsigned_int32(2048))

class _OS_DLLIMPORT(_OS_CLIENT) os_reference_internal {
public:
  char* dump() const;
  char* dump(const char* database_name) const;

  /* Return the substring of dump_str that identifies the */
  /* database. dump_str must have been generated using the */ 
  /* dump operation. Otherwise, the exception err_reference_syntax */
  /* is raised   */

  static char* get_database_key(const char* dump_str);
  
  os_unsigned_int32 hash() const;
  os_unsigned_int32 hash(const os_segment* hash_context) const;
  
  void load(const char* handle);
  
  void *resolve() const;
  
  os_database* get_database() const;

  os_boolean operator== (os_reference_internal const& r) const;
  os_boolean operator < (os_reference_internal const& r) const;
  os_boolean operator > (os_reference_internal const& r) const;

  os_boolean operator != (os_reference_internal const& r) const
  { return(!((*this) == r)); }

  os_boolean operator >= (os_reference_internal const& r) const
  { return(!((*this) < r)); }

  os_boolean operator <= (os_reference_internal const& r) const
  { return(!((*this) > r)); }

  os_boolean operator ! () const;

protected:
  os_reference_internal();
  os_reference_internal(const void* p);
  os_reference_internal(os_cluster* new_cluster, os_unsigned_int32 new_offset);
  os_reference_internal(const os_reference_internal& r);

  os_reference_internal& operator=(const void* p);
  os_reference_internal& operator=(const os_reference_internal& r);
 
  void *resolve(const os_database* db) const;

protected:
  os_soft_pointer32<void> ref_value;
  
public:
  /* The following are for internal use only: */
  os_soft_pointer32<void> const& _get_ref_value() const
    { return ref_value; }

  void _get_dsco_address(os_unsigned_int32& seg_id,
			 os_unsigned_int32& clus_id,
			 os_unsigned_int32& offset) const;
};


class _OS_DLLIMPORT(_OS_CLIENT) os_reference_protected_internal {
public:
  ~os_reference_protected_internal();

  char* dump() const;
  char* dump(const char* database_name) const;

  /* Return the substring of dump_str that identifies the */
  /* database. dump_str must have been generated using the */ 
  /* dump operation. Otherwise, the exception err_reference_syntax */
  /* is raised   */

  static char* get_database_key(const char* dump_str);
  
  os_unsigned_int32 hash() const;
  
  void load(const char* handle);
  
  os_boolean deleted() const;

  void *resolve() const;
  
  os_database* get_database() const;

  os_boolean operator== (os_reference_protected_internal const& r) const;
  os_boolean operator < (os_reference_protected_internal const& r) const;
  os_boolean operator > (os_reference_protected_internal const& r) const;

  os_boolean operator != (os_reference_protected_internal const& r) const
  { return(!((*this) == r)); }

  os_boolean operator >= (os_reference_protected_internal const& r) const
  { return(!((*this) < r)); }

  os_boolean operator <= (os_reference_protected_internal const& r) const
  { return(!((*this) > r)); }

  os_boolean operator ! () const;

protected:
  os_reference_protected_internal();
  os_reference_protected_internal(const void* p);
  os_reference_protected_internal(os_segment* new_segment, 
				  const os_export_id& export_id,
				  os_unsigned_int32 new_offset);
  os_reference_protected_internal(const os_reference_protected_internal& r);

  os_reference_protected_internal& operator=(const void* p);
  os_reference_protected_internal& operator=(const os_reference_protected_internal& r);

protected:
  os_unsigned_int32 dbindex;
  os_unsigned_int32 segnum;
  os_export_id export_id;
  os_unsigned_int32 offset;

public:
  /* The following are for internal use only: */
  void _get_dseo_address(os_unsigned_int32& seg_id,
			 os_export_id& export_id,
			 os_unsigned_int32& offset) const;
  void _set_dseo_offset(os_unsigned_int32 new_offset);
};


class _OS_DLLIMPORT(_OS_CLIENT)  os_reference_transient : public os_reference_internal {
public:
  os_reference_transient();
  
  os_reference_transient(const void* p);

  os_reference_transient& operator=(const void *p);

  os_reference_transient& operator=(const os_reference_transient &r);

  static os_typespec * get_os_typespec();

  operator void*() const {return resolve();}

};

/* No declared import because get_os_typespec will be generated by ossg */

class os_reference_local : public os_reference_internal {
public:
  os_reference_local();
  
  os_reference_local(const void* p);

  os_reference_local& operator=(const void *p);

  os_reference_local& operator=(const os_reference_local& r);

  void *resolve(const os_database * db) const 
    { return os_reference_internal::resolve(db); }

  static os_typespec * get_os_typespec();
};


/* No declared import because get_os_typespec will be generated by ossg */

class os_reference_this_DB : public os_reference_internal {
public:
  os_reference_this_DB();
  
  os_reference_this_DB(const void* p);
  
  os_reference_this_DB& operator=(const void *p);

  os_reference_this_DB& operator=(const os_reference_this_DB& r);

  static os_typespec * get_os_typespec();

  operator void*() const {return resolve();}
};


/* No declared import because get_os_typespec will be generated by ossg */

class os_reference : public os_reference_internal {
private:
  friend class os_notification;
  os_soft_pointer32<void> & _get_ref_value_for_update()
    { return ref_value; }

public:		
  os_reference();
  
  os_reference(const void* p);
  
  os_reference& operator=(const void *p);

  os_reference& operator=(const os_reference& r);

  static os_typespec * get_os_typespec();

  operator void*() const {return resolve();}

  operator os_soft_pointer<void>() const { return (os_soft_pointer<void>)ref_value; } 
};


/* No declared import because get_os_typespec will be generated by ossg */

class os_reference_protected : public os_reference_protected_internal {
public:		
  os_reference_protected();
  
  os_reference_protected(const void* p);
  
  os_reference_protected& operator=(const void *p);

  os_reference_protected& operator=(const os_reference_protected& r);

  static os_typespec * get_os_typespec();

  operator void*() const {return resolve();}
};


/* No declared import because get_os_typespec will be generated by ossg */

class os_reference_protected_local : public os_reference_protected_internal {
public:		
  os_reference_protected_local();
  
  os_reference_protected_local(const void* p);
  
  os_reference_protected_local& operator=(const void *p);

  os_reference_protected_local& operator=(const os_reference_protected_local& r);

  void *resolve(const os_database* db) const;

  static os_typespec * get_os_typespec();
};



/* Define all the parameterized reference classes */
/* There are no instantiations provided by the ostore client so no export
   declarations are required. */


template <class Ref_to> 
class os_Reference : public os_reference_internal {
public:
  os_Reference(Ref_to * p) : os_reference_internal((void *)p) {}
  os_Reference(const os_Reference<Ref_to>& ref) 
    : os_reference_internal(ref) {}
  os_Reference() : os_reference_internal () {}
  static os_typespec * get_os_typespec();

  os_Reference<Ref_to> & operator=(const Ref_to *p)
    { os_reference_internal::operator=(p); return *this; }
  os_Reference<Ref_to> & operator=(const os_Reference<Ref_to> & r)
    { os_reference_internal::operator=(*((const os_reference_internal *)&r));
      return *this; }

#if !defined(__os_cafe)
  operator const os_reference & () const
    { return *((const os_reference *)this); }
  operator os_reference & ()
    { return *((os_reference *)this); }
#endif

  Ref_to * resolve () const
    { return (Ref_to *) os_reference_internal::resolve(); }
  operator Ref_to * () const 
    { return (Ref_to *) os_reference_internal::resolve(); }
  Ref_to * operator->() const
    { return (Ref_to *) os_reference_internal::resolve(); }
};


template <class Ref_to> 
class os_Reference_protected : public os_reference_protected_internal {
public:
  os_Reference_protected(Ref_to * p) : 
    os_reference_protected_internal((void *)p) {}
  os_Reference_protected(const os_Reference_protected<Ref_to>& ref) 
    : os_reference_protected_internal(ref) {}
  os_Reference_protected() : os_reference_protected_internal () {}
  static os_typespec * get_os_typespec();

  os_Reference_protected<Ref_to> & operator=(const Ref_to *p)
    { os_reference_protected_internal::operator=(p); return *this; }
  os_Reference_protected<Ref_to> & operator=(const os_Reference_protected<Ref_to> & r)
    { os_reference_protected_internal::operator=(
			*((const os_reference_protected_internal *)&r));
      return *this; }

#if !defined(__os_cafe)
  operator const os_reference_protected & () const
    { return *((const os_reference_protected *)this); }
  operator os_reference_protected & ()
    { return *((os_reference_protected *)this); }
#endif

  Ref_to * resolve () const
    { return (Ref_to *) os_reference_protected_internal::resolve(); }
  operator Ref_to * () const 
    { return (Ref_to *) os_reference_protected_internal::resolve(); }
  Ref_to * operator->() const
    { return (Ref_to *) os_reference_protected_internal::resolve(); }
};


template <class Ref_to> 
class os_Reference_protected_local : public os_reference_protected_internal {
public:
  os_Reference_protected_local(Ref_to * p) : 
    os_reference_protected_internal((void *)p) {}
  os_Reference_protected_local(const os_Reference_protected<Ref_to>& ref) 
    : os_reference_protected_internal(ref) {}
  os_Reference_protected_local() : os_reference_protected_internal () {}
  static os_typespec * get_os_typespec();

  os_Reference_protected_local<Ref_to> & operator=(const Ref_to *p)
    { os_reference_protected_internal::operator=(p); return *this; }
  os_Reference_protected_local<Ref_to> & operator=(const os_Reference_protected_local<Ref_to> & r)
    { os_reference_protected_internal::operator=(
			*((const os_reference_protected_internal *)&r));
      return *this; }

#if !defined(__os_cafe)
  operator const os_reference_protected_local & () const
    { return *((const os_reference_protected_local *)this); }
  operator os_reference_protected_local & ()
    { return *((os_reference_protected_local *)this); }
#endif

  Ref_to * resolve (const os_database* db) const
    { return (Ref_to *) os_reference_protected_internal::resolve(); }
};


#if !defined(__os_cafe)
#define OS_REFERENCE_NO_CLASS_REF_CASTS                                \
  operator const os_reference & () const                               \
    { return *((const os_reference *)this); }                          \
  operator os_reference & ()                                           \
    { return *((os_reference *)this); }
#else
#define OS_REFERENCE_NO_CLASS_REF_CASTS
#endif

#define OS_REFERENCE_NOCLASS(REF_TO)                                   \
class os_Reference<REF_TO>                                             \
  : public os_reference_internal {                                     \
public:                                                                \
  os_Reference(REF_TO * p) : os_reference_internal((void *)p) {}       \
  os_Reference(const os_Reference<REF_TO>& ref)                        \
    : os_reference_internal(ref) {}                                    \
  os_Reference() : os_reference_internal () {}                         \
  static os_typespec * get_os_typespec();                              \
  os_Reference<REF_TO> & operator=(const REF_TO *p)                    \
    { os_reference_internal::operator=(p); return *this; }             \
  os_Reference<REF_TO> & operator=(const os_Reference<REF_TO> & r)     \
    { os_reference_internal::operator=(*((const os_reference_internal *)&r)); \
      return *this; }                                                  \
  OS_REFERENCE_NO_CLASS_REF_CASTS                                      \
  REF_TO * resolve () const                                            \
    { return (REF_TO *) os_reference_internal::resolve(); }            \
  operator REF_TO * () const                                           \
    { return (REF_TO *) os_reference_internal::resolve(); }            \
};


template <class Ref_to> 
class os_Reference_local : public os_reference_internal {
public:
  os_Reference_local(Ref_to * p) : os_reference_internal((void *)p) {};
  os_Reference_local(const os_Reference_local<Ref_to>& ref) 
    : os_reference_internal(ref) {};
  os_Reference_local() : os_reference_internal () {};
  static os_typespec * get_os_typespec();

  os_Reference_local<Ref_to> & operator=(const Ref_to *p)
    { os_reference_internal::operator=(p); return *this; }
  os_Reference_local<Ref_to> & operator=(const os_Reference_local<Ref_to> & r)
    { os_reference_internal::operator=(*((const os_reference_internal *)&r));
      return *this; }

#if !defined(__os_cafe)
  operator const os_reference_local & () const
    { return *((const os_reference_local *)this); }
  operator os_reference_local & ()
    { return *((os_reference_local *)this); }
#endif

  Ref_to * resolve (os_database * db) const
    { return (Ref_to *) os_reference_internal::resolve(db); };
};


template <class Ref_to> 
class os_Reference_this_DB : public os_reference_internal {
public:
  os_Reference_this_DB(Ref_to * p) : os_reference_internal((void *)p) {}
  os_Reference_this_DB(const os_Reference_this_DB<Ref_to>& ref) 
    : os_reference_internal(ref) {}
  os_Reference_this_DB() : os_reference_internal () {}
  static os_typespec * get_os_typespec();

  os_Reference_this_DB<Ref_to> & operator=(const Ref_to *p)
    { os_reference_internal::operator=(p); return *this; }
  os_Reference_this_DB<Ref_to> & operator=(const os_Reference_this_DB<Ref_to> & r)
    { os_reference_internal::operator=(*((const os_reference_internal *)&r));
      return *this; }

#if !defined(__os_cafe)
  operator const os_reference_this_DB & () const
    { return *((const os_reference_this_DB *)this); }
  operator os_reference_this_DB & ()
    { return *((os_reference_this_DB *)this); }
#endif

  Ref_to * resolve () const
    { return (Ref_to *) os_reference_internal::resolve(); }
  operator Ref_to * () const 
    { return (Ref_to *) os_reference_internal::resolve(); }
  Ref_to * operator->() const
    { return (Ref_to *) os_reference_internal::resolve(); }
};


template <class Ref_to> 
class os_Reference_transient : public os_reference_internal {
public:
  os_Reference_transient(Ref_to * p) : os_reference_internal((void *)p) {}
  os_Reference_transient(const os_Reference_transient<Ref_to>& ref) 
    : os_reference_internal(ref) {}
  os_Reference_transient() : os_reference_internal () {}

  os_Reference_transient<Ref_to> & operator=(const Ref_to *p)
    { os_reference_internal::operator=(p); return *this; }
  os_Reference_transient<Ref_to> & operator=(const os_Reference_transient<Ref_to> & r)
    { os_reference_internal::operator=(*((const os_reference_internal *)&r));
      return *this; }

#if !defined(__os_cafe)
  operator const os_reference_transient & () const
    { return *((const os_reference_transient *)this); }
  operator os_reference_transient & ()
    { return *((os_reference_transient *)this); }
#endif

  Ref_to * resolve () const
    { return (Ref_to *) os_reference_internal::resolve(); }
  operator Ref_to * () const 
    { return (Ref_to *) os_reference_internal::resolve(); }
  Ref_to * operator->() const
    { return (Ref_to *) os_reference_internal::resolve(); }
};



class  _OS_DLLIMPORT(_OS_CLIENT) os_reference_cross_session
{
  char*                      dbname;    //the database name
  os_unsigned_int32          segmentid; //segment id
  os_unsigned_int32          clusterid; // cluster id
  os_unsigned_int32          offset;    // offset
  os_export_id               exportid;  // eid
  os_unsigned_int32          size;      // size of mapping if dsco

public:

  os_reference_cross_session();
  os_reference_cross_session(const void* p);
  os_reference_cross_session(const os_reference_cross_session& ref);
  os_reference_cross_session(const os_reference& ref);
  os_reference_cross_session(const os_soft_pointer<void>& ref);

  ~os_reference_cross_session();

  os_reference_cross_session& operator=(const void* p);
  os_reference_cross_session& operator=(const os_reference_cross_session& ref);
  os_reference_cross_session& operator=(const os_reference& ref);
  os_reference_cross_session& operator=(const os_soft_pointer<void>& ref);

  void* resolve() const;              //returns pointer in current sesion
  operator void*() const;       //same as resolve, only different syntax

  void reset();                //resets the fields

  //comparison operators

  os_boolean operator!() const;

  os_boolean operator==(const void*) const;
  os_boolean operator==(const os_reference_cross_session& ) const;

  os_boolean operator<(void const*)const;
  os_boolean operator<(os_reference_cross_session const& ref) const;
  os_boolean operator<(os_soft_pointer<void> const& ref) const;
  os_boolean operator<(os_reference const& ref) const;

  os_boolean operator<=(void const* other) const
    {  return !(*this > other); }
  os_boolean operator<=(os_reference_cross_session const& ref) const
    { return !(*this > ref); }
  os_boolean operator<=(os_soft_pointer<void> const& ref) const
    { return !(*this > ref); }
  os_boolean operator<=(os_reference const& ref) const
    { return !(*this > ref); }

  os_boolean operator>(void const*)const;
  os_boolean operator>(os_reference_cross_session const& ref) const;
  os_boolean operator>(os_soft_pointer<void> const& ref) const;
  os_boolean operator>(os_reference const& ref) const;

  os_boolean operator>=(void const* other) const
    { return !(*this < other); }
  os_boolean operator>=(os_reference_cross_session const& ref) const
    { return !(*this < ref); }
  os_boolean operator>=(os_soft_pointer<void> const& ref) const
    { return !(*this < ref); }
  os_boolean operator>=(os_reference const& ref) const
    { return !(*this < ref); }


  //utility functions
  os_database* get_database() const;
  char* dump() const;
  void load(const char* handle);

};
  
template <class T>
class os_Reference_cross_session:public os_reference_cross_session
{

public:

  os_Reference_cross_session() :os_reference_cross_session() {}

  os_Reference_cross_session( T *p) 
      :os_reference_cross_session( (void*)p ) {}

  os_Reference_cross_session(const os_Reference_cross_session<T>& ref)
          :os_reference_cross_session( ref)
  {}

  os_Reference_cross_session(const os_reference& ref)
          :os_reference_cross_session(ref)
  {}

  os_Reference_cross_session(const os_soft_pointer<void>& ref)
               :os_reference_cross_session(ref)
  {}

  os_Reference_cross_session<T>& operator=(T *p)
  {
          ( (*((os_reference_cross_session *)this) = (void*)p) );
          return *this;
  }

  os_Reference_cross_session<T>& operator=(const
					 os_Reference_cross_session<T>& ref)
  {
	 os_reference_cross_session::operator=(ref);
         return *this;
  }

  os_Reference_cross_session<T>& operator=(const os_reference& ref)
  {
         os_reference_cross_session::operator=(ref);
         return *this;
  }

  os_Reference_cross_session<T>& operator=(const os_soft_pointer<void>& ref)
  {
         os_reference_cross_session::operator=(ref);
         return *this;
  }

  T* resolve() const
  {
              return (T*) os_reference_cross_session::resolve();
  }

  operator T*() const
  { return resolve(); }

   T* operator->() const 
   {  return (T*) os_reference_cross_session::resolve(); }

    //comparison operators from the base class will be used

};


#define OS_REFERENCE_CROSS_SESSION_NOCLASS(REF_TO)                     \
class os_Reference_cross_session<REF_TO>                               \
   : public os_reference_cross_session                                 \
{                                                                      \
                                                                       \
public:                                                                \
                                                                       \
  os_Reference_cross_session() :os_reference_cross_session() {}              \
                                                                       \
  os_Reference_cross_session( REF_TO *p)                                     \
      :os_reference_cross_session( (void*)p ) {}                       \
                                                                       \
  os_Reference_cross_session(const os_Reference_cross_session<REF_TO>& ref)  \
          :os_reference_cross_session( ref)                            \
  {}                                                                   \
                                                                       \
  os_Reference_cross_session(const os_reference& ref)                        \
          :os_reference_cross_session(ref)                             \
  {}                                                                   \
                                                                       \
  os_Reference_cross_session(const os_soft_pointer<void>& ref)               \
               :os_reference_cross_session(ref)                        \
  {}                                                                   \
                                                                     \
  os_Reference_cross_session<REF_TO>& operator=(REF_TO *p)                   \
  {                                                                    \
          ( (*((os_reference_cross_session *)this) = (void*)p) );      \
          return *this;                                                \
  }                                                                    \
                                                                     \
  os_Reference_cross_session<REF_TO>& operator=(const                        \
				os_Reference_cross_session<REF_TO>& ref)     \
  {                                                                    \
	 os_reference_cross_session::operator=(ref);                   \
         return *this;                                                 \
  }                                                                    \
                                                                       \
  os_Reference_cross_session<REF_TO>& operator=(const os_reference& ref)     \
  {                                                                    \
         os_reference_cross_session::operator=(ref);                   \
         return *this;                                                 \
  }                                                                    \
                                                                       \
  os_Reference_cross_session<REF_TO>& operator=(const os_soft_pointer<void>& ref) \
  {                                                                    \
         os_reference_cross_session::operator=(ref);                   \
         return *this;                                                 \
  }                                                                    \
                                                                       \
  REF_TO* resolve() const                                              \
  {                                                                    \
              return (REF_TO*) os_reference_cross_session::resolve();  \
  }                                                                    \
                                                                       \
  operator REF_TO*() const                                             \
  { return resolve(); }                                                \
                                                                       \
                                                                       \
};

#include <ostore/hdrend.hh>
#endif /* _REF_H_ */



/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef CLIENT_INTERFACE_SOFTPTR
#define CLIENT_INTERFACE_SOFTPTR 1

#ifndef _OS_PSE_COLL
#include <ostore/hdrstart.hh>
#include <ostore/portypes.hh>
#include <ostore/nclient/typedefs.hh>
#include <ostore/nclient/objstore.hh>
#include <ostore/nclient/export_id.hh>
#include <ostore/os_types/paddef.hh>
#include <ostore/facade.hh>

class os_database;
class os_segment;
class os_cluster;
#define _OS_SOFTPTR_IMPORT _OS_DLLIMPORT(_OS_CLIENT)

#else // PSE C++

#include <os_pse/psecoll/hdrstart.hh>
#include <os_pse/portypes.hh>
#define _OS_SOFTPTR_IMPORT _OS_COLL_IMPORT

_OS_BEGIN_NAMESPACE(os_pse)
#endif // PSE C++

template <class T> class os_soft_pointer32;
template <class T> class os_soft_pointer64;

#ifdef _OS_64BIT_NATIVE
#define os_soft_pointer os_soft_pointer64
#else
#define os_soft_pointer os_soft_pointer32
#endif

/* For the convenience of collections */
#define os_soft_pointer32_void os_soft_pointer32<void>
#define os_soft_pointer64_void os_soft_pointer64<void>


template <int SZ> class os_soft_pointer_defs;

#ifdef __os_sol2c5
template <> 
#endif
class os_soft_pointer_defs<32> {
public:
#ifdef _OS_PSE_COLL
  typedef void* pointer_value_type;
#else 
  typedef os_unsigned_int32 pointer_value_type;
#endif
};

/* This union only requires 32 bit alignment on 32 bit platforms but
   ossg understands that this is effectively a pointer type and will
   require 64 bit soft pointers to be 64 bit aligned, even if no
   neutralization is requested. */

#ifndef _OS_PSE_COLL

union _OS_SOFTPTR_IMPORT os_soft_pointer64_value_type {
  OS_ALIGN_CLASS(8);
  os_unsigned_int32 pointer_words[2];
  void* dummy_pointer;

  os_soft_pointer64_value_type() {}
#ifdef _OS_64BIT_NATIVE
  os_platform_uint64 pointer_value;
  os_soft_pointer64_value_type(os_ptr_val value) : pointer_value(value) {}
  operator os_ptr_val() const { return pointer_value; }
  os_soft_pointer64_value_type& operator=(os_ptr_val value) 
  { pointer_value = value; return *this; }
#else
  os_soft_pointer64_value_type(os_ptr_val value) { pointer_words[0] = value; }
  operator os_ptr_val() const { return pointer_words[0]; }
  os_soft_pointer64_value_type& operator=(os_ptr_val value) 
  { pointer_words[0] = value; return *this; }
#endif    

  /* The following is a temporary measure so that old versions of ossg
     don't get upset about the lack of a discriminant function.  This 
     function will never get called. */
  os_int32 discriminant() const;
};

#else
  typedef void* os_soft_pointer64_value_type;
#endif // PSE C++

#ifdef __os_sol2c5
template <>
#endif
class os_soft_pointer_defs<64> {
public:
  typedef os_soft_pointer64_value_type pointer_value_type;
};

/* Provide convenience base class typedefs.  This also helps VC++ from
 * getting confused when parsing the template definition.
 */

template <int SZ> class os_soft_pointer_base;
#ifndef _OS_PSE_COLL
#if !defined(_OS_DECCXX) && !defined(__os_sgi_mips) && !defined(__os_hp11) && !defined(__os_linux) && !(defined(_ODI_OSSG_) && defined(_ODI_EDGFE_) && defined(__os_sol2c5)) && !defined(__os_sol64)
class _OS_SOFTPTR_IMPORT os_soft_pointer_base<32>;
class _OS_SOFTPTR_IMPORT os_soft_pointer_base<64>;
#endif
#else  // PSE C++
#if !defined(__os_hpansi) && !defined(__os_linux) && !defined(__os_sol2c5)
class _OS_SOFTPTR_IMPORT os_soft_pointer_base<32>;
class _OS_SOFTPTR_IMPORT os_soft_pointer_base<64>;
#endif // HP aCC
class os_soft_pointer_access;
#endif // PSE C++

typedef os_soft_pointer_base<32> os_soft_pointer32_base;
typedef os_soft_pointer_base<64> os_soft_pointer64_base;

template <int SZ>
class os_soft_pointer_base {
public:
  /* Pick up our pointer value type from the corresponding
   * os_soft_pointer_defs instantiation.  We shouldn't really need
   * this but I until ossg and all compilers support member templates
   * we'll need to use this indirection mechanism.
   */
#ifndef _OS_PSE_COLL
  typedef _OS_TYPENAME os_soft_pointer_defs<SZ>::pointer_value_type pointer_value_type;
#else
  typedef void* pointer_value_type;
#endif

public:
  friend class os_soft_pointer_access;

  os_soft_pointer_base();
  os_soft_pointer_base(void*);
  os_soft_pointer_base(os_soft_pointer32_base const&);
  os_soft_pointer_base(os_soft_pointer64_base const&);

  ~os_soft_pointer_base();

  os_soft_pointer_base<SZ> &operator=(os_soft_pointer32_base const&);
  os_soft_pointer_base<SZ> &operator=(os_soft_pointer64_base const&);
  os_soft_pointer_base<SZ> &operator=(void*);

  void* resolve() const;
  void* resolve(os_boolean cache) const;

  void decache();

  os_database* get_database() const;
  os_database* get_open_database() const;

  char* dump() const;
  char* dump(const char* database_name) const;
  static char* get_database_key(const char* dump_str);
  void load(const char* handle);
  void load(const char* handle, const os_database* db);

  os_unsigned_int32 hash() const;
  os_unsigned_int32 hash(const os_segment* hash_context) const;
  os_unsigned_int32 hash_dseo() const;

  os_boolean operator!() const;

  /* comparison operators */
  os_boolean operator==(void const*) const;
  os_boolean operator==(os_soft_pointer32_base const&) const;
  os_boolean operator==(os_soft_pointer64_base const&) const;

  os_boolean operator!=(void const* other) const {
    return ! (*this == other); }
  os_boolean operator!=(os_soft_pointer32_base const& other) const {
    return ! (*this == other); }
  os_boolean operator!=(os_soft_pointer64_base const& other) const {
    return ! (*this == other); }

  os_boolean operator<(void const*) const;
  os_boolean operator<(os_soft_pointer32_base const&) const;
  os_boolean operator<(os_soft_pointer64_base const&) const;

  os_boolean operator>(void const*) const;
  os_boolean operator>(os_soft_pointer32_base const&) const;
  os_boolean operator>(os_soft_pointer64_base const&) const;

  os_boolean operator<=(void const* other) const {
    return ! (*this > other); }
  os_boolean operator<=(os_soft_pointer32_base const& other) const {
    return ! (*this > other); }
  os_boolean operator<=(os_soft_pointer64_base const& other) const {
    return ! (*this > other); }

  os_boolean operator>=(void const* other) const {
    return ! (*this < other); }
  os_boolean operator>=(os_soft_pointer32_base const& other) const {
    return ! (*this < other); }
  os_boolean operator>=(os_soft_pointer64_base const& other) const {
    return ! (*this < other); }

  /* support for global comparison operators */
  os_boolean is_eq(void const*) const;
  os_boolean is_lt(void const*) const;
  os_boolean is_gt(void const*) const;

  /* low-level accessors */
#ifndef _OS_PSE_COLL
  void set_persistent_address(os_cluster* cluster, os_unsigned_int32 offset,
			      os_unsigned_int32 mapping_size);
  void set_persistent_address(os_segment* segment,
			      os_export_id const& eid,
			      os_unsigned_int32 offset);
  objectstore::address_mode 
    get_persistent_address(void*& transient_address,
			   os_segment*& export_id_segment,
			   os_cluster*& dsco_cluster,
			   os_export_id& export_id,
			   os_unsigned_int32& offset,
			   os_unsigned_int32& mapping_size) const;
#endif  

private:
  pointer_value_type opaque;

protected:
  os_boolean is_cached() const { return !((os_ptr_val)opaque & 1); }
  pointer_value_type get_opaque() const { return opaque; }
};

#if (defined(_MSC_VER) && (_MSC_VER >= 1200)) || defined(__os_hp11)
template class os_soft_pointer_base<32>;
template class os_soft_pointer_base<64>;
#endif

template <class T> class os_soft_pointer32 :
   public os_soft_pointer32_base
{
public:
  os_soft_pointer32() {}
  os_soft_pointer32(T* p) : os_soft_pointer32_base(p) {}
  os_soft_pointer32(os_soft_pointer32<T> const& sp)
    : os_soft_pointer32_base(sp) {}
  os_soft_pointer32(os_soft_pointer64<T> const& sp)
    : os_soft_pointer32_base(sp) {}

  os_soft_pointer32<T>& operator=(T* p)
    { os_soft_pointer32_base::operator=(p); return *this; }
  os_soft_pointer32<T>& operator=(os_soft_pointer32<T> const& sp)
    { os_soft_pointer32_base::operator=(sp); return *this; }
  os_soft_pointer32<T>& operator=(os_soft_pointer64<T> const& sp)
    { os_soft_pointer32_base::operator=(sp); return *this; }

  os_boolean operator==(T const* p) const {
    return os_soft_pointer32_base::operator==(p); }
  os_boolean operator==(os_soft_pointer32<T> const& sp) const {
    return os_soft_pointer32_base::operator==(sp); }
  os_boolean operator==(os_soft_pointer64<T> const& sp) const {
    return os_soft_pointer32_base::operator==(sp); }

  os_boolean operator!=(T const* other) const {
    return ! (*this == other); }
  os_boolean operator!=(os_soft_pointer32<T> const& other) const {
    return ! (*this == other); }
  os_boolean operator!=(os_soft_pointer64<T> const& other) const {
    return ! (*this == other); }

  os_boolean operator<(T const* p) const {
    return os_soft_pointer32_base::operator<(p); }
  os_boolean operator<(os_soft_pointer32<T> const& sp) const {
    return os_soft_pointer32_base::operator<(sp); }
  os_boolean operator<(os_soft_pointer64<T> const& sp) const {
    return os_soft_pointer32_base::operator<(sp); }

  os_boolean operator>(T const* p) const {
    return os_soft_pointer32_base::operator>(p); }
  os_boolean operator>(os_soft_pointer32<T> const& sp) const {
    return os_soft_pointer32_base::operator>(sp); }
  os_boolean operator>(os_soft_pointer64<T> const& sp) const {
    return os_soft_pointer32_base::operator>(sp); }

  os_boolean operator<=(T const* other) const {
    return ! (*this > other); }
  os_boolean operator<=(os_soft_pointer32<T> const& other) const {
    return ! (*this > other); }
  os_boolean operator<=(os_soft_pointer64<T> const& other) const {
    return ! (*this > other); }

  os_boolean operator>=(T const* other) const {
    return ! (*this < other); }
  os_boolean operator>=(os_soft_pointer32<T> const& other) const {
    return ! (*this < other); }
  os_boolean operator>=(os_soft_pointer64<T> const& other) const {
    return ! (*this < other); }

  T* resolve(os_boolean cache) const {
    if (is_cached())
      return (T*)(os_ptr_val)get_opaque(); // cached
    else
      return (T*) os_soft_pointer32_base::resolve(cache); // not cached
  }

  T* resolve() const { return resolve(1); }

  operator T*() const { return resolve(); }

  T* operator->() const { return resolve(); }
};

template <class T> class os_soft_pointer64 :
   public os_soft_pointer64_base
{
public:
  os_soft_pointer64() {}
  os_soft_pointer64(T* p) : os_soft_pointer64_base(p) {}
  os_soft_pointer64(os_soft_pointer32<T> const& sp)
    : os_soft_pointer64_base(sp) {}
  os_soft_pointer64(os_soft_pointer64<T> const& sp)
    : os_soft_pointer64_base(sp) {}

  os_soft_pointer64<T>& operator=(T* p)
    { os_soft_pointer64_base::operator=(p); return *this; }
  os_soft_pointer64<T>& operator=(os_soft_pointer32<T> const& sp)
    { os_soft_pointer64_base::operator=(sp); return *this; }
  os_soft_pointer64<T>& operator=(os_soft_pointer64<T> const& sp)
    { os_soft_pointer64_base::operator=(sp); return *this; }

  os_boolean operator==(T const* p) const {
    return os_soft_pointer64_base::operator==(p); }
  os_boolean operator==(os_soft_pointer32<T> const& sp) const {
    return os_soft_pointer64_base::operator==(sp); }
  os_boolean operator==(os_soft_pointer64<T> const& sp) const {
    return os_soft_pointer64_base::operator==(sp); }

  os_boolean operator!=(T const* other) const {
    return ! (*this == other); }
  os_boolean operator!=(os_soft_pointer32<T> const& other) const {
    return ! (*this == other); }
  os_boolean operator!=(os_soft_pointer64<T> const& other) const {
    return ! (*this == other); }

  os_boolean operator<(T const* p) const {
    return os_soft_pointer64_base::operator<(p); }
  os_boolean operator<(os_soft_pointer32<T> const& sp) const {
    return os_soft_pointer64_base::operator<(sp); }
  os_boolean operator<(os_soft_pointer64<T> const& sp) const {
    return os_soft_pointer64_base::operator<(sp); }

  os_boolean operator>(T const* p) const {
    return os_soft_pointer64_base::operator>(p); }
  os_boolean operator>(os_soft_pointer32<T> const& sp) const {
    return os_soft_pointer64_base::operator>(sp); }
  os_boolean operator>(os_soft_pointer64<T> const& sp) const {
    return os_soft_pointer64_base::operator>(sp); }

  os_boolean operator<=(T const* other) const {
    return ! (*this > other); }
  os_boolean operator<=(os_soft_pointer32<T> const& other) const {
    return ! (*this > other); }
  os_boolean operator<=(os_soft_pointer64<T> const& other) const {
    return ! (*this > other); }

  os_boolean operator>=(T const* other) const {
    return ! (*this < other); }
  os_boolean operator>=(os_soft_pointer32<T> const& other) const {
    return ! (*this < other); }
  os_boolean operator>=(os_soft_pointer64<T> const& other) const {
    return ! (*this < other); }

  T* resolve(os_boolean cache) const {
    if (is_cached())
      return  (T*)(os_ptr_val)get_opaque(); // cached
    else
      return (T*) os_soft_pointer64_base::resolve(cache);
  }
  
  T* resolve() const { return resolve(1); }

  operator T*() const { return resolve(); }

  T* operator->()const { return resolve(); }
};


/* The os_soft_pointerXX<void> specializations are not equivalent to
   the expansion of OS_SOFT_POINTER_NOCLASS(void) macro.  This is
   intentional and allows a soft pointer of any type to be assigned
   to an os_soft_pointerXX<void>.  The macro expansion would allow only
   os_soft_pointerXX<void> to be assigned. */

/* VC++ claims DLLIMPORT needs to be here, even though this is all inline */
#ifdef __os_sol2c5
template <> 
#endif
class _OS_SOFTPTR_IMPORT os_soft_pointer32<void> : 
  public os_soft_pointer32_base
{
public:
  os_soft_pointer32() {}
  os_soft_pointer32(void* p) : os_soft_pointer32_base(p) {}
  /* provide both the exact copy constructor and the base class version.
     If the exact copy constructor isn't provided the Solaris compiler
     will complain. */
  os_soft_pointer32(os_soft_pointer32<void> const& sp)
    : os_soft_pointer32_base(sp) {}
  os_soft_pointer32(os_soft_pointer32_base const& sp)
    : os_soft_pointer32_base(sp) {}
  os_soft_pointer32(os_soft_pointer64_base const& sp)
    : os_soft_pointer32_base(sp) {}

  os_soft_pointer32<void>& operator=(void* p)
    { os_soft_pointer32_base::operator=(p); return *this; }
  /* provide both the exact copying assignment operator and the base class
     version.  If the exact copy assignment isn't provided the Solaris 
     compiler will complain. */
  os_soft_pointer32<void>& operator=(os_soft_pointer32<void> const& sp)
    { os_soft_pointer32_base::operator=(sp); return *this; }
  os_soft_pointer32<void>& operator=(os_soft_pointer32_base const& sp)
    { os_soft_pointer32_base::operator=(sp); return *this; }
  os_soft_pointer32<void>& operator=(os_soft_pointer64_base const& sp)
    { os_soft_pointer32_base::operator=(sp); return *this; }

  os_boolean operator==(void const* p) const
    { return os_soft_pointer32_base::operator==(p); }
  os_boolean operator==(os_soft_pointer32_base const& sp) const
    { return os_soft_pointer32_base::operator==(sp); }
  os_boolean operator==(os_soft_pointer64_base const& sp) const           
    { return os_soft_pointer32_base::operator==(sp); }

  os_boolean operator!=(void const* other) const       
    { return ! (*this == other); }                                    
  os_boolean operator!=(os_soft_pointer32_base const& other) const       
    { return ! (*this == other); }                                    
  os_boolean operator!=(os_soft_pointer64_base const& other) const       
    { return ! (*this == other); }                                    

  os_boolean operator<(void const* p) const           
    { return os_soft_pointer32_base::operator<(p); }
  os_boolean operator<(os_soft_pointer32_base const& sp) const           
    { return os_soft_pointer32_base::operator<(sp); }
  os_boolean operator<(os_soft_pointer64_base const& sp) const           
    { return os_soft_pointer32_base::operator<(sp); }

  os_boolean operator>(void const* p) const           
    { return os_soft_pointer32_base::operator>(p); }
  os_boolean operator>(os_soft_pointer32_base const& sp) const           
    { return os_soft_pointer32_base::operator>(sp); }
  os_boolean operator>(os_soft_pointer64_base const& sp) const           
    { return os_soft_pointer32_base::operator>(sp); }

  os_boolean operator<=(void const* other) const       
    { return ! (*this > other); }                                     
  os_boolean operator<=(os_soft_pointer32_base const& other) const       
    { return ! (*this > other); }                                     
  os_boolean operator<=(os_soft_pointer64_base const& other) const       
    { return ! (*this > other); }                                     

  os_boolean  operator>=(void const* other) const     
    { return ! (*this < other); }                                     
  os_boolean operator>=(os_soft_pointer32_base const& other) const       
    { return ! (*this < other); }                                     
  os_boolean operator>=(os_soft_pointer64_base const& other) const       
    { return ! (*this < other); }                                     

  void* resolve(os_boolean cache) const {
    if (is_cached())
      return  (void*)(os_ptr_val)get_opaque(); // cached
    else
      return (void*) os_soft_pointer32_base::resolve(cache);
  }
  
  void* resolve() const { return resolve(1); }

  operator void*() const { return resolve(); }
};


/* VC++ claims DLLIMPORT needs to be here, even though this is all inline */
#ifdef __os_sol2c5
template <> 
#endif
class _OS_SOFTPTR_IMPORT os_soft_pointer64<void> :
  public os_soft_pointer64_base
{
public:
  os_soft_pointer64() {}
  os_soft_pointer64(void* p) : os_soft_pointer64_base(p) {}
  /* provide both the exact copy constructor and the base class version.
     If the exact copy constructor isn't provided the Solaris compiler
     will complain. */
  os_soft_pointer64(os_soft_pointer64<void> const& sp)
    : os_soft_pointer64_base(sp) {}
  os_soft_pointer64(os_soft_pointer32_base const& sp)
    : os_soft_pointer64_base(sp) {}
  os_soft_pointer64(os_soft_pointer64_base const& sp)
    : os_soft_pointer64_base(sp) {}

  os_soft_pointer64<void>& operator=(void* p)
    { os_soft_pointer64_base::operator=(p); return *this; }
  /* provide both the exact copying assignment operator and the base class
     version.  If the exact copy assignment isn't provided the Solaris 
     compiler will complain. */
  os_soft_pointer64<void>& operator=(os_soft_pointer64<void> const& sp)
    { os_soft_pointer64_base::operator=(sp); return *this; }
  os_soft_pointer64<void>& operator=(os_soft_pointer32_base const& sp)
    { os_soft_pointer64_base::operator=(sp); return *this; }
  os_soft_pointer64<void>& operator=(os_soft_pointer64_base const& sp)
    { os_soft_pointer64_base::operator=(sp); return *this; }

  os_boolean operator==(void const* p) const
    { return os_soft_pointer64_base::operator==(p); }
  os_boolean operator==(os_soft_pointer32_base const& sp) const
    { return os_soft_pointer64_base::operator==(sp); }
  os_boolean operator==(os_soft_pointer64_base const& sp) const           
    { return os_soft_pointer64_base::operator==(sp); }

  os_boolean operator!=(void const* other) const       
    { return ! (*this == other); }                                    
  os_boolean operator!=(os_soft_pointer32_base const& other) const       
    { return ! (*this == other); }                                    
  os_boolean operator!=(os_soft_pointer64_base const& other) const       
    { return ! (*this == other); }                                    

  os_boolean operator<(void const* p) const           
    { return os_soft_pointer64_base::operator<(p); }
  os_boolean operator<(os_soft_pointer32_base const& sp) const           
    { return os_soft_pointer64_base::operator<(sp); }
  os_boolean operator<(os_soft_pointer64_base const& sp) const           
    { return os_soft_pointer64_base::operator<(sp); }

  os_boolean operator>(void const* p) const           
    { return os_soft_pointer64_base::operator>(p); }
  os_boolean operator>(os_soft_pointer32_base const& sp) const           
    { return os_soft_pointer64_base::operator>(sp); }
  os_boolean operator>(os_soft_pointer64_base const& sp) const           
    { return os_soft_pointer64_base::operator>(sp); }

  os_boolean operator<=(void const* other) const       
    { return ! (*this > other); }                                     
  os_boolean operator<=(os_soft_pointer32_base const& other) const       
    { return ! (*this > other); }                                     
  os_boolean operator<=(os_soft_pointer64_base const& other) const       
    { return ! (*this > other); }                                     

  os_boolean  operator>=(void const* other) const     
    { return ! (*this < other); }                                     
  os_boolean operator>=(os_soft_pointer32_base const& other) const       
    { return ! (*this < other); }                                     
  os_boolean operator>=(os_soft_pointer64_base const& other) const       
    { return ! (*this < other); }
  
  void* resolve(os_boolean cache) const {
    if (is_cached())
      return  (void*)(os_ptr_val)get_opaque(); // cached
    else
      return (void*) os_soft_pointer64_base::resolve(cache);
  }
  
  void* resolve() const { return resolve(1); }
  
  operator void*() const { return resolve(); }
};


/* Define macros to allow 32, 64 bit soft pointers to non-class types
   to be defined.  Because some of the methods require the definition
   of the other size soft pointer class be available, we have to
   first define the classes and then separately define those methods
   which require the other class definition.  Otherwise, the definition
   of one size of soft pointer would trigger instantiation of the other
   size from the template, which would then conflict with the specialization
   yet to be defined.

   We need to do things slightly differently for ossg and for normal 
   compilation because ossg improperly handles template specializations.
   Until ossg gets fixed, we'll need to supply a bogus definition
   of some methods.  These definitions effectively relax some type-checking
   when running ossg.
   */

#if defined(_ODI_OSSG_) && defined(_ODI_EDGFE_) && defined(__os_cafe)
/* the sparc compiler has a nonansi preprocessor, which causes all sorts
   of problems for us in the soft pointer specializations. 
   Added _OS_SPMTC for the contructor definitions.  Usually _OS_SPMT and 
   _OS_SPMTC are the same, but the AIX xlC compiler rejects constructor 
   names that include the type specialization.
*/
#define _OS_SPMTC(SP,TYPE) SP
#define _OS_SPMT(SP,TYPE) SP
#else
#if defined(__os_aix43)
#define _OS_SPMTC(SP,TYPE) SP
#define _OS_SPMT(SP,TYPE) SP<TYPE>
#else
#define _OS_SPMTC(SP,TYPE) SP<TYPE>
#define _OS_SPMT(SP,TYPE) SP<TYPE>
#endif
#endif

#define _OS_SOFT_POINTER_ANY_NOCLASS(TYPE,SP,SPBASE,SP32,SP64)          \
class SP<TYPE> : public SPBASE {                                        \
public:                                                                 \
  _OS_SPMTC(SP,TYPE)() {}                                                \
  _OS_SPMTC(SP,TYPE)(TYPE* p) : SPBASE(p) {}                             \
  _OS_SPMTC(SP,TYPE)(SP32 const& sp);                                    \
  _OS_SPMTC(SP,TYPE)(SP64 const& sp);                                    \
                                                                        \
  _OS_SPMT(SP,TYPE)& operator=(TYPE* p)                                 \
       { SPBASE::operator=(p); return *this; }                          \
  _OS_SPMT(SP,TYPE)& operator=(SP32 const& sp);                         \
  _OS_SPMT(SP,TYPE)& operator=(SP64 const& sp);                         \
                                                                        \
  os_boolean operator==(TYPE const* p) const                            \
    { return SPBASE::operator==(p); }                                   \
  os_boolean operator==(SP32 const& sp) const;                          \
  os_boolean operator==(SP64 const& sp) const;                          \
                                                                        \
  os_boolean operator!=(TYPE const* other) const;                       \
  os_boolean operator!=(SP32 const& other) const;                       \
  os_boolean operator!=(SP64 const& other) const;                       \
                                                                        \
  os_boolean operator<(TYPE const* p) const                             \
    { return SPBASE::operator<(p); }                                    \
  os_boolean operator<(SP32 const& sp) const;                           \
  os_boolean operator<(SP64 const& sp) const;                           \
                                                                        \
  os_boolean operator>(TYPE const* p) const                             \
    { return SPBASE::operator>(p); }                                    \
  os_boolean operator>(SP32 const& sp) const;                           \
  os_boolean operator>(SP64 const& sp) const;                           \
                                                                        \
  os_boolean operator<=(TYPE const* other) const;                       \
  os_boolean operator<=(SP32 const& other) const;                       \
  os_boolean operator<=(SP64 const& other) const;                       \
                                                                        \
  os_boolean operator>=(TYPE const* other) const;                       \
  os_boolean operator>=(SP32 const& other) const;                       \
  os_boolean operator>=(SP64 const& other) const;                       \
                                                                        \
  TYPE* resolve() const { return (TYPE*) SPBASE::resolve(); }           \
  TYPE* resolve(os_boolean cache) const                                 \
    { return (TYPE*) SPBASE::resolve(cache); }                          \
  operator TYPE*() const { return resolve(); }                          \
};

#define _OS_SOFT_POINTER_ANY_NOCLASS_METHODS(TYPE, SP, SPBASE, SP32, SP64) \
inline SP<TYPE>::SP(SP32 const& sp) : SPBASE(sp) {}                        \
inline SP<TYPE>::SP(SP64 const& sp) : SPBASE(sp) {}                        \
inline SP<TYPE>& SP<TYPE>::operator=(SP32 const& sp)                       \
    { SPBASE::operator=(sp); return *this; }                               \
inline SP<TYPE>& SP<TYPE>::operator=(SP64 const& sp)                       \
    { SPBASE::operator=(sp); return *this; }                               \
inline os_boolean SP<TYPE>::operator==(SP32 const& sp) const               \
    { return SPBASE::operator==(sp); }                                     \
inline os_boolean SP<TYPE>::operator==(SP64 const& sp) const               \
    { return SPBASE::operator==(sp); }                                     \
inline os_boolean SP<TYPE>::operator!=(TYPE const* other) const            \
    { return ! (*this == other); }                                         \
inline os_boolean SP<TYPE>::operator!=(SP32 const& other) const            \
    { return ! (*this == other); }                                         \
inline os_boolean SP<TYPE>::operator!=(SP64 const& other) const            \
    { return ! (*this == other); }                                         \
inline os_boolean SP<TYPE>::operator<(SP32 const& sp) const                \
    { return SPBASE::operator<(sp); }                                      \
inline os_boolean SP<TYPE>::operator<(SP64 const& sp) const                \
    { return SPBASE::operator<(sp); }                                      \
inline os_boolean SP<TYPE>::operator>(SP32 const& sp) const                \
    { return SPBASE::operator>(sp); }                                      \
inline os_boolean SP<TYPE>::operator>(SP64 const& sp) const                \
    { return SPBASE::operator>(sp); }                                      \
inline os_boolean SP<TYPE>::operator<=(TYPE const* other) const            \
    { return ! (*this > other); }                                          \
inline os_boolean SP<TYPE>::operator<=(SP32 const& other) const            \
    { return ! (*this > other); }                                          \
inline os_boolean SP<TYPE>::operator<=(SP64 const& other) const            \
    { return ! (*this > other); }                                          \
inline  os_boolean SP<TYPE>:: operator>=(TYPE const* other) const          \
    { return ! (*this < other); }                                          \
inline os_boolean SP<TYPE>::operator>=(SP32 const& other) const            \
    { return ! (*this < other); }                                          \
inline os_boolean SP<TYPE>::operator>=(SP64 const& other) const            \
    { return ! (*this < other); }                                          \

#ifdef _ODI_OSSG_

#define _OS_SOFT_POINTER32_NOCLASS(TYPE) \
_OS_SOFT_POINTER_ANY_NOCLASS(TYPE,os_soft_pointer32,os_soft_pointer32_base, \
		       os_soft_pointer32<TYPE>,os_soft_pointer64_base)

#define _OS_SOFT_POINTER64_NOCLASS(TYPE) \
_OS_SOFT_POINTER_ANY_NOCLASS(TYPE,os_soft_pointer64,os_soft_pointer64_base, \
		       os_soft_pointer32_base,os_soft_pointer64<TYPE>)

#define _OS_SOFT_POINTER32_NOCLASS_METHODS(TYPE)
#define _OS_SOFT_POINTER64_NOCLASS_METHODS(TYPE)

#else /* if not _ODI_OSSG */

#define _OS_SOFT_POINTER32_NOCLASS(TYPE) \
_OS_SOFT_POINTER_ANY_NOCLASS(TYPE,os_soft_pointer32,os_soft_pointer32_base, \
		       os_soft_pointer32<TYPE>,os_soft_pointer64<TYPE>)

#define _OS_SOFT_POINTER64_NOCLASS(TYPE) \
_OS_SOFT_POINTER_ANY_NOCLASS(TYPE,os_soft_pointer64,os_soft_pointer64_base, \
		       os_soft_pointer32<TYPE>,os_soft_pointer64<TYPE>)

#define _OS_SOFT_POINTER32_NOCLASS_METHODS(TYPE)                         \
_OS_SOFT_POINTER_ANY_NOCLASS_METHODS(TYPE,os_soft_pointer32,             \
  os_soft_pointer32_base,os_soft_pointer32<TYPE>,os_soft_pointer64<TYPE>)

#define _OS_SOFT_POINTER64_NOCLASS_METHODS(TYPE)                         \
_OS_SOFT_POINTER_ANY_NOCLASS_METHODS(TYPE,os_soft_pointer64,             \
  os_soft_pointer64_base,os_soft_pointer32<TYPE>,os_soft_pointer64<TYPE>)

#endif  /* if _ODI_OSSG */

#define OS_SOFT_POINTER_NOCLASS(TYPE)                                   \
  _OS_SOFT_POINTER32_NOCLASS(TYPE)                                      \
  _OS_SOFT_POINTER64_NOCLASS(TYPE)                                      \
  _OS_SOFT_POINTER32_NOCLASS_METHODS(TYPE)                              \
  _OS_SOFT_POINTER64_NOCLASS_METHODS(TYPE)

#ifndef __os_sol2c5
OS_SOFT_POINTER_NOCLASS(char)
OS_SOFT_POINTER_NOCLASS(unsigned)
#endif

#ifndef NO_GLOBAL_SOFT_POINTER_COMPARE
// For now, only support these for Win32 due to compiler issues
#ifdef _OS_Win32

template <class T> inline os_boolean
 operator==(const T* p, os_soft_pointer32<T> const& sp) { return sp.is_eq(p); }
template <class T> inline os_boolean
 operator==(const T* p, os_soft_pointer64<T> const& sp) { return sp.is_eq(p); }
template <class T> inline os_boolean
 operator!=(const T* p, os_soft_pointer32<T> const& sp) { return !sp.is_eq(p);}
template <class T> inline os_boolean
 operator!=(const T* p, os_soft_pointer64<T> const& sp) { return !sp.is_eq(p);}
template <class T> inline os_boolean
 operator<(const T* p, os_soft_pointer32<T> const& sp) { return sp.is_gt(p); }
template <class T> inline os_boolean
 operator<(const T* p, os_soft_pointer64<T> const& sp) { return sp.is_gt(p); }
template <class T> inline os_boolean
 operator>(const T* p, os_soft_pointer32<T> const& sp) { return sp.is_lt(p); }
template <class T> inline os_boolean
 operator>(const T* p, os_soft_pointer64<T> const& sp) { return sp.is_lt(p); }
template <class T> inline os_boolean
 operator<=(const T* p, os_soft_pointer32<T> const& sp) { return !sp.is_lt(p);}
template <class T> inline os_boolean
 operator<=(const T* p, os_soft_pointer64<T> const& sp) { return !sp.is_lt(p);}
template <class T> inline os_boolean
 operator>=(const T* p, os_soft_pointer32<T> const& sp) { return !sp.is_gt(p);}
template <class T> inline os_boolean
 operator>=(const T* p, os_soft_pointer64<T> const& sp) { return !sp.is_gt(p);}
#endif

#endif

#ifndef _OS_PSE_COLL
#include <ostore/hdrend.hh>
#else
_OS_END_NAMESPACE
#include <os_pse/psecoll/hdrend.hh>
#endif

#endif /* CLIENT_INTERFACE_SOFTPTR */

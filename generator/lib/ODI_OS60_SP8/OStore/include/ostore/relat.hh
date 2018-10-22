/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef _RELATIONSHIP_H_
#define _RELATIONSHIP_H_

#ifndef    _OS_PSE_COLL
#include <ostore/hdrstart.hh>

#include <ostore/coll.hh>
#include <ostore/coll/cursor.hh>
#include <ostore/coll/bplist.hh>

#else      // _OS_PSE_COLL

typedef os_database* os_database_p;
#include <os_pse/coll.hh>
#include <os_pse/coll/cursor.hh>
#include <os_pse/coll/bplist.hh>
_OS_BEGIN_NAMESPACE(os_pse)
#endif     // _OS_PSE_COLL

/* Includer can define OS_RELATIONSHIP_LINKAGE macro as text
 * to go between the keyword class and the class name for classes generated
 * by os_relationship_xxx macros.  This is for Windows, e.g. __declspec.
 * If not defined, the default is blank.
 */
#ifndef OS_RELATIONSHIP_LINKAGE
#define OS_RELATIONSHIP_LINKAGE
#endif

/* These typedefs make sure that all parameters of virtual member functions
   defined by these macros use 32-bit pointers under Digital UNIX. */
typedef os_collection* os_collection_p;
typedef os_int32& os_int32_r;
typedef os_cursor const& os_cursor_const_r;
typedef void const*& os_void_const_p_r;
typedef os_bound_query const& os_bound_query_const_r;

class _OS_COLL_IMPORT os_rel_protect_being_deleted : public basic_undo {
public:
  os_rel_protect_being_deleted (void* s);
 ~os_rel_protect_being_deleted ();
  static os_int32 objs_being_deleted_contains(void *);
  
protected:
  void* self;
};


enum os_relationship_deletion{ os_dont_propagate_delete = 0, os_propagate_delete = 1,
		       os_rel_dont_propagate_delete = 0, os_rel_propagate_delete = 1,
		       os_relationship_deletion_pad = 1<<30 };

void _Rel_many_unset_all_inverses (os_collection*, void*, os_unsigned_int32,
 os_unsigned_int32, void *, os_int32, os_int32 );
void _Rel_many_assignment_kill (os_collection*, void*, os_unsigned_int32,
 os_unsigned_int32, void *, os_int32, os_int32 );
void _Rel_many_insert (os_collection*, void *, os_unsigned_int32,
 os_unsigned_int32, os_unsigned_int32, void *, void *, os_int32, os_int32);
void _Rel_many_remove(os_collection*, void *, os_unsigned_int32,
 os_unsigned_int32, void *, void *, os_int32, os_int32);


class _OS_COLL_IMPORT os_rel_single {
  friend class os_rel_many;
  friend class os_rel_m_1;
  friend class os_rel_single_loader;
protected:

  char* container(os_int32 mem);
  os_coll_ptr _value;

public:
  void * value() const { return _value; }
  void  set_value(void* v) { _value = v; } 
 

};

class _OS_COLL_IMPORT os_rel_1_1 : public os_rel_single {
protected:
  void set_simple(void* val);
  void set_simple(void* val, os_int32 mem, os_int32 mb);
  void unset_inverse(os_int32 inv);
  void unset_inverse(os_int32 inv, os_int32 ib);
  void set_inverse(void* val, os_int32 inv);
  void set_inverse(void* val, os_int32 mem, os_int32 inv, os_int32 mb, os_int32 ib);
  void setvalue(void* val, os_int32 mem, os_int32 inv);
  void setvalue(void* val, os_int32 mem, os_int32 inv, os_int32 mb, os_int32 ib);
  os_rel_1_1() {set_value((void*) 0);}

  void* getvalue() const { return (void*)_value; };  

  static os_typespec* get_os_typespec();
};


class _OS_COLL_IMPORT os_rel_many : public os_collection {
  friend class os_rel_many_loader;
  friend class os_rel_dumper;
private: 
  friend void _Rel_many_insert(os_collection*, void *, os_unsigned_int32,
    os_unsigned_int32, os_unsigned_int32, void *, void *, os_int32, os_int32);
  friend void _Rel_many_remove(os_collection*, void *, os_unsigned_int32,
    os_unsigned_int32, void *, void *, os_int32, os_int32);

  virtual os_int32 has_indexes() const;
  virtual _Indexes*& indexes();

  void reclaim(); 

protected:

  os_coll_ptr _value;
  char _os_pad_0[4];

  virtual os_collection* _get_innermost_collection();

  virtual os_int32 _rep_enum() const;
 
  char* container(os_int32 mem);

  os_rel_many()
#ifndef _OS_BorlandCC
      {set_value((os_collection*)0);}
#endif
  ;
  ~os_rel_many()
  {
    if (value()) { 
       delete value(); 
       set_value((os_collection*)0);
    }
  }

  os_collection * value() const { return (os_collection*)(void*)_value; }
  void  set_value(os_collection* v) { _value = (void*)v; } 
 
  /* 
   * To avoid disturbing the many users of make_value, all arguments
   * to make_value are optional. use_specified_behavior indicates if
   * the behavior argument should be used in determining behavior.
   * (Relying on a special bit pattern in behavior to indicate "ignore
   * me" is risky.)
   */
  void make_value(os_int32 esize = 0,
		  /* behavior arguments */
		  os_boolean use_specified_behavior = 0,
		  os_unsigned_int32 behavior = 0);

  virtual void get_members(os_int32& mem, os_int32& inv) const=0;
  virtual void get_members(os_int32& mem, os_int32& inv, 
			   os_int32& backptr) const=0;
  virtual os_collection* create_relationship_collection(os_int32 esize,
		  /* behavior arguments */
		  os_boolean use_specified_behavior = 0,
		  os_unsigned_int32 behavior = 0) = 0;

  virtual void* _pick() const;
  virtual void* _only() const;

  virtual void* _replace_at(const void* p, const os_cursor& c);
  virtual void* _replace_at(const void* p, os_unsigned_int32 position);

  virtual os_int32 _remove_first (os_void_const_p &v);
  virtual os_int32 _remove_last (os_void_const_p &v);

  virtual void _remove_at(os_unsigned_int32 position);

  virtual void _insert(void const * v);
  virtual os_int32 _remove(void const * v);
  virtual void _insert_first(void const * v);
  virtual void _insert_last(void const * v);
  virtual void _insert_before(void const * v, const os_cursor& c);

  virtual os_int32 _remove_all(void const* v);

  virtual void _insert_before(const void* p, os_unsigned_int32 position);

  virtual void _insert_after(void const * v, const os_cursor& c);

  virtual void _insert_after(const void* p, os_unsigned_int32 position);

  virtual void _remove_at(const os_cursor& c);

  virtual os_int32 _contains(const void* v) const;
  virtual os_int32 _count(const void* v) const;
  virtual os_int32 _eq(const os_collection& s) const;
  virtual os_int32 _eq(const void* e) const;
  virtual os_int32 _ne(const os_collection& s) const;
  virtual os_int32 _ne(const void* e) const;
  virtual os_int32 _lt(const os_collection& s) const;
  virtual os_int32 _lt(const void* e) const;
  virtual os_int32 _le(const os_collection& s) const;
  virtual os_int32 _le(const void* e) const;
  virtual os_int32 _gt(const os_collection& s) const;
  virtual os_int32 _gt(const void* e) const;
  virtual os_int32 _ge(const os_collection& s) const;
  virtual os_int32 _ge(const void* e) const;
  os_int32 _first(os_cursor& c, os_void_p &v ) const;
  os_int32 _last(os_cursor& c, os_void_p &v) const;
  os_int32 _next(os_cursor& c, os_void_p &v) const;
  os_int32 _previous(os_cursor& c, os_void_p &v) const;

  void* _retrieve(const os_cursor& c) const;
  void* _retrieve(os_unsigned_int32 position) const;

  void _check_rep_invariants() const {}
public: /* for internal use only */
 
  virtual void* _this_pick_query(os_int32 /*restriction*/ r, const void* v,
				 os_unsigned_int32& found) const;
  virtual _Pset* _this_query(os_int32 /*restriction*/ r, const void* v) const;
  virtual os_boolean _fast_count() const;

public:
  os_collection& operator =(const os_collection& s){return os_collection::operator =(s);}
  os_collection& operator =(const void* e) {return os_collection::operator =(e) ; }

  os_collection& getvalue() {
#ifdef _OS_BorlandCC
    os_collection * turbo_kludge = this;
    return * turbo_kludge;
#else
    return *(os_collection*)this;
#endif
  };
#ifndef __os_linux
  operator os_collection& () {
#ifdef _OS_BorlandCC
    os_collection * turbo_kludge = this;
    return * turbo_kludge;
#else
    return *(os_collection*)this;
#endif
  };
#endif /* __os_linux */
  os_collection const& getvalue() const {
#ifdef _OS_BorlandCC
    const os_collection * turbo_kludge = this;
    return * turbo_kludge;
#else
    return *(os_collection*)this;
#endif
  };
#ifndef __os_linux
  operator os_collection const& () const {
#ifdef _OS_BorlandCC
    const os_collection * turbo_kludge = this;
    return * turbo_kludge;
#else
    return *(os_collection*)this;
#endif
  };
#endif /* __os_linux */
  virtual os_unsigned_int32 _cardinality() const;
  virtual void _clear() ;
  virtual os_int32 _empty() const;
  virtual char *_rep_name() const;

  /* Required by evolution protocol */
  void evolve_rep();
};


extern os_int32 _Reloc_missing_virtual_function(void*);

class _OS_COLL_IMPORT _os_rel_many_readonly : public os_rel_many {
#if defined(_OS_MicrosoftCC) || defined(__os_sgi_mips) || defined(__os_hpansi)
  /* See colvdsp.cc */
  friend class _os_rel_many_readonly_generic;
#endif
private:
  _os_rel_many_readonly();
protected:
  void make_value(os_int32 = 0) { _Reloc_missing_virtual_function((void*)this); };

  virtual void get_members(os_int32&, os_int32&) const;
  virtual void get_members(os_int32&, os_int32&, os_int32&) const;
  virtual os_collection* create_relationship_collection(os_int32 esize,
		  /* behavior arguments */
		  os_boolean use_specified_behavior = 0,
		  os_unsigned_int32 behavior = 0);

  virtual void _insert(void const *);
  virtual os_int32 _remove(void const *);

  virtual void _insert_first(void const *);
  virtual void _insert_last(void const *);
  virtual void _insert_before(void const *, const os_cursor&);
  virtual void _insert_after(void const *, const os_cursor&);

  virtual void _insert_before(const void* p, os_unsigned_int32 position);
  virtual void _insert_after(const void* p, os_unsigned_int32 position);
  virtual void _remove_at(os_unsigned_int32 position);

  virtual void _remove_at(const os_cursor&);
  virtual os_int32 _remove_first(os_void_const_p &);
  virtual os_int32 _remove_last(os_void_const_p &);

  virtual os_collection& _assign (const os_collection&);
  virtual os_collection& _assign(const void*);
  virtual os_collection& _assign_or(const os_collection&);
  virtual os_collection& _assign_or(const void*);
  virtual os_collection& _assign_and(const os_collection&);
  virtual os_collection& _assign_and(const void*);
  virtual os_collection& _assign_sub(const os_collection&);
  virtual os_collection& _assign_sub(const void*);

  virtual os_unsigned_int32 _get_behavior() const 
    { return value() ? value()->get_behavior() : os_collection::default_behavior(); }

public:
  os_collection& operator =(const os_collection&);
  os_collection& operator =(const _os_rel_many_readonly&);
  os_collection& operator =(const void*);

  os_collection& getvalue() { return *this; };
#ifndef __os_linux
  operator os_collection& () { return *this; };
#endif /* __os_linux */
  os_collection const& getvalue() const { return *this; };
#ifndef __os_linux
  operator os_collection const& () const { return *this; };
#endif /* __os_linux */
  static os_typespec * get_os_typespec();
};


class _OS_COLL_IMPORT os_rel_m_m : public os_rel_many {
public:
  void remove_simple( const void* v);
  void remove_simple_all(const void* v);

protected:
  os_rel_m_m()
#ifndef _OS_BorlandCC
      { }
#endif
  ;
  os_rel_m_m( os_unsigned_int32 params, os_int32 exp_size )
    {set_value((os_collection*)&os_collection::create(this, params, exp_size));};

  virtual void get_members(os_int32& mem, os_int32& inv) const=0;
  virtual void get_members(os_int32& mem, os_int32& inv, 
			   os_int32& backptr) const=0;
  virtual os_collection* create_relationship_collection(os_int32 esize,
		  /* behavior arguments */
		  os_boolean use_specified_behavior = 0,
		  os_unsigned_int32 behavior = 0) = 0;

  void _insert_inverse( void* v );
  void _remove_inverse( void* v );
  virtual void _insert(const void* v);
  virtual void _insert_before(const void* p, os_unsigned_int32 position);
  virtual void _insert_after(const void* p, os_unsigned_int32 position);
  virtual void _remove_at(os_unsigned_int32 position);
  

  virtual os_int32 _remove(const void* v);
  virtual void _insert_first(const void* v);
  virtual void _insert_last(const void* v);
  virtual void _insert_after(const void* v, const os_cursor& c);
  virtual void _insert_before(const void* v, const os_cursor& c);
  virtual void _remove_at(const os_cursor& c);

  void __insert_inverse( void* v, os_int32 mem, os_int32 inv);
  void __remove_inverse( void* v, os_int32 mem, os_int32 inv);

  os_int32 __retrieve_first(os_void_const_p &v, os_int32 , os_int32  ) const;
  os_int32 __retrieve_last(os_void_const_p &v,  os_int32 , os_int32  ) const;

  void* __retrieve(os_unsigned_int32 position) const;

  os_int32 __remove_first(os_void_const_p &v, os_int32 mem, os_int32 inv);
  os_int32 __remove_last(os_void_const_p &v, os_int32 mem, os_int32 inv);

  void* __replace_at(const void* v, const os_cursor& c,os_int32 mem, os_int32 inv);
  void* __replace_at(const void* v, os_unsigned_int32 position,
		     os_int32 mem, os_int32 inv);

  void __insert(const void* v, os_int32 mem, os_int32 inv);
  os_int32 __remove(const void* v, os_int32 mem, os_int32 inv);

  void __insert_first(const void* v, os_int32 mem, os_int32 inv);
  void __insert_last(const void* v, os_int32 mem, os_int32 inv);
  void __insert_after(const void* v, const os_cursor& c, os_int32 mem,os_int32 inv);
  void __insert_after(const void* v, os_int32 p, os_int32 mem, os_int32 inv);
  void __insert_before(const void* v, const os_cursor& c, os_int32 mem, os_int32 inv);
  void __insert_before(const void* v, os_unsigned_int32 position, os_int32 mem, os_int32 inv);
  void __remove_at(os_unsigned_int32 position, os_int32 mem, os_int32 inv);
  void __remove_at(const os_cursor& c, os_int32 mem, os_int32 inv);

public:

  ~os_rel_m_m() { };

  void insert_simple( const void* v);
  static os_typespec* get_os_typespec();
} ;

class _OS_COLL_IMPORT os_rel_m_1 : public os_rel_many {
private:
  friend class os_rel_1_m;
protected:
  os_rel_m_1()
#ifndef _OS_BorlandCC
      { }
#endif
  ;
  os_rel_m_1( os_unsigned_int32 params, os_int32 exp_size)
    {set_value((os_collection*)&os_collection::create(this, params));};

  virtual void get_members(os_int32& mem, os_int32& inv) const=0;
  virtual void get_members(os_int32& mem, os_int32& inv, 
			   os_int32& backptr) const=0;
  virtual os_collection* create_relationship_collection(os_int32 esize,
		  /* behavior arguments */
		  os_boolean use_specified_behavior = 0,
		  os_unsigned_int32 behavior = 0) = 0;

  void _insert_inverse( void* v );
  void _remove_inverse( void* v );

  virtual void _insert(const void* v);
  virtual os_int32 _remove(const void* v);

  /* There are no _insert_after/before functions in this class.
   * Their only user would _Rel_many (nreldml.hh) and I simply
   * put the logic in _Rel_many::_insert_after/before.  A similar thing could
   * be done to most of the single-underscore functions in this class
   */

  virtual void _insert_first(const void* v);
  virtual void _insert_last(const void* v);
  void __insert_after(const void* v, os_int32 p, os_int32 mem, os_int32 inv); 

  virtual void _insert_before(const void* p, os_unsigned_int32 position);
  virtual void _insert_after(const void* p, os_unsigned_int32 position);
  virtual void _remove_at(os_unsigned_int32 position);

  virtual void _insert_after(const void* v, const os_cursor& c); 
  virtual void _insert_before(const void* v, const os_cursor& c); 
  virtual void _remove_at(const os_cursor& c); 

  void __insert_inverse( void* v, os_int32 mem, os_int32 inv);
  void __remove_inverse( void* v, os_int32 /* mem */, os_int32 inv ) ;

  os_int32 __retrieve_first(os_void_const_p &v, os_int32 , os_int32  ) const; 
  os_int32 __retrieve_last(os_void_const_p &v,  os_int32 , os_int32  ) const;
  void* __retrieve(os_unsigned_int32 position) const; 

  os_int32 __remove_first(os_void_const_p &v, os_int32 mem, os_int32 inv); 
  os_int32 __remove_last(os_void_const_p &v, os_int32 mem, os_int32 inv); 

  void* __replace_at(const void* v, os_unsigned_int32 position,
		     os_int32 mem, os_int32 inv); 
  void* __replace_at(const void* v, const os_cursor& c,
		     os_int32 mem, os_int32 inv); 

  void __insert(const void* v, os_int32 mem, os_int32 inv); 
  os_int32 __remove(const void* v, os_int32 mem, os_int32 inv); 

  void __insert_first(const void* v, os_int32 mem, os_int32 inv); 
  void __insert_last(const void* v, os_int32 mem, os_int32 inv); 
  void __insert_after(const void* v, const os_cursor& c, os_int32 mem, os_int32 inv);
  void __insert_before(const void* v, const os_cursor& c, os_int32 mem, os_int32 inv);
  void __insert_before(const void* v, os_unsigned_int32 position,
		       os_int32 mem, os_int32 inv);

  void __remove_at(os_unsigned_int32 position, os_int32 mem, os_int32 inv);
  void __remove_at(const os_cursor& c, os_int32 mem, os_int32 inv );

  void __insert_inverse( void* v, os_int32 mem, os_int32 inv, os_int32 ib );
  void __remove_inverse( void* v, os_int32 /* mem */, os_int32 inv, os_int32 ib );

  void __insert(const void* v, os_int32 mem, os_int32 inv, os_int32 ib );
  os_int32 __remove(const void* v, os_int32 mem, os_int32 inv, os_int32 ib );
  void __insert_first(const void* v, os_int32 mem, os_int32 inv, os_int32 ib );
  void __insert_last(const void* v, os_int32 mem, os_int32 inv, os_int32 ib );
  void __insert_after(const void* v, const os_cursor& c, os_int32 mem, os_int32 inv, os_int32 ib );
  void __insert_before(const void* v, const os_cursor& c, os_int32 mem, os_int32 inv, os_int32 ib );
  void __remove_at(const os_cursor& c, os_int32 mem, os_int32 inv, os_int32 ib );

public:

  ~os_rel_m_1() { };

  void insert_simple( const void* v);
  void remove_simple( const void* v);
  void remove_simple_all(const void* v);
  static os_typespec* get_os_typespec();

} ;



class _OS_COLL_IMPORT os_rel_1_m : public os_rel_single {
private:
  friend class os_rel_m_1;
protected:
  void set_simple(void* val);
  void unset_inverse(os_int32 mem, os_int32 inv);
  void set_inverse(void* val, os_int32 mem, os_int32 inv);
  void setvalue(void* val, os_int32 mem, os_int32 inv, os_int32 mb);
  void setvalue(void* val, os_int32 mem, os_int32 inv);
  os_rel_1_m() {set_value((void*)0);};
public:
 
  void* getvalue() const { return _value; };
  static os_typespec* get_os_typespec();
};


#if defined(_OS_ANSI_TOKENS)
#define _Concat(x,y)x##y
#define _Concat3(x,y,z) x##y##z
#define _Concat4(x,y,z,w)x##y##z##w
#define _Concat5(x,y,z,w,v)x##y##z##w##v
#else
#define _Self(x)x

#define _Concat(x,y)_Self(x)y

#define _Concat3(x,y,z)_Concat(x,y)z

#define _Concat4(x,y,z,w)_Concat3(x,y,z)w

#define _Concat5(x,y,z,w,v)_Concat4(x,y,z,w)v
#endif

#define os_rel_1_1_body(base,member,type,inverse) \
os_relationship_1_1_body(base,member,type,inverse)

#define os_rel_1_1_body_options(base,member,type,inverse,deletion,memb,invb) \
os_relationship_1_1_body_options(base,member,type,inverse,deletion,memb,invb)

#define os_rel_1_m_body(base,member,type,inverse) \
os_relationship_1_m_body(base,member,type,inverse)

#define os_rel_1_m_body_options(base,member,type,inverse,deletion,memb,invb) \
os_relationship_1_m_body_options(base,member,type,inverse,deletion,memb,invb)

#define os_rel_m_1_body(base,member,type,inverse) \
os_relationship_m_1_body(base,member,type,inverse)

#define os_rel_m_1_body_options(base,member,type,inverse,deletion,memb,invb) \
os_relationship_m_1_body_options(base,member,type,inverse,deletion,memb,invb)

#define os_rel_m_m_body(base,member,type,inverse) \
os_relationship_m_m_body(base,member,type,inverse)

#define os_rel_m_m_body_options(base,member,type,inverse,deletion,memb,invb) \
os_relationship_m_m_body_options(base,member,type,inverse,deletion,memb,invb)

/* gcc does not allow a class to be a explicitly a friend to itself */

#if defined(__os_linux)
#define __FRIEND_KLUDGE(type)
#else
#define __FRIEND_KLUDGE(type) friend class type;
#endif

/* Borland truncates class names to make them fit in something like
 * 63 characters, so we have to resort to this extreme kludgery to
 * pluck out relationshipness of a class, as well as who it is related
 * to and of what type they are.
 */

#if (defined(_ODI_OSSG_))
#define _OSSG_REF_CLASS_MARKER(type, inverse) \
  private:\
    class os_rel_marker_class {\
      type* inverse;\
    };\
  public:
#elif (defined(_OS_BorlandCC) || defined(_OS_MicrosoftCC) || defined(_OS_OS2))
#define _OSSG_REF_CLASS_MARKER(type, inverse) \
  private:\
    class __wrmk_{\
      os_int32 __my_parent_is_a_relationship;\
      type* inverse;\
    };\
  public:
#else
#ifdef __os_xlc
/* explicitly define the other end class to avoid warnings*/
#define _OSSG_REF_CLASS_MARKER(type, inverse) \
  class _Concat(_os_rel_member_,inverse) {}; \
  friend class _Concat(_os_rel_member_,inverse);
#else
#define _OSSG_REF_CLASS_MARKER(type, inverse) friend class _Concat(_os_rel_member_,inverse);
#endif
#endif

#if defined(_OS_MicrosoftCC)
#define _OSSG_CLASS_VFT_MAKER(base,member) private: _Concat4(os_rel_,base,_,member)(int); public:
#define _OSSG_BODY_VFT_MAKER(base,member) base::_Concat4(os_rel_,base,_,member)::_Concat4(os_rel_,base,_,member)(int){};
#else
#define _OSSG_CLASS_VFT_MAKER(base,member)
#define _OSSG_BODY_VFT_MAKER(base,member)
#endif

#define os_relationship_1_1( base, member, type, inverse, signature ) \
  friend os_int32 _Concat4(os_rel_offsetof_,base,_,member) (); \
  __FRIEND_KLUDGE(type) \
  void _Concat4(os_rel_typecheck_,base,_,member) () \
    {type * arg3 = 0; signature arg5 = 0; arg3 = arg5; arg5 = arg3;} \
  class OS_RELATIONSHIP_LINKAGE _Concat4(os_rel_,base,_,member) : public os_rel_1_1 { public: \
  _OSSG_REF_CLASS_MARKER(type,inverse) \
  _OSSG_CLASS_VFT_MAKER(base,member)\
  void setvalue(type* __val); \
  type* operator=(type* __val) { setvalue(__val); return __val; } \
  operator type* () const { return (type*)(os_rel_1_1::getvalue());} \
  type* getvalue() const { return (type*)(os_rel_1_1::getvalue());} \
  type* operator->() const { return (type*)(os_rel_1_1::getvalue());} \
  type& operator*() const { return (type&)(char&)*(char*)(os_rel_1_1::getvalue());} \
  ~ _Concat4(os_rel_,base,_,member) (); \
  _Concat4(os_rel_,base,_,member) (_Concat4(os_rel_,base,_,member) & v): os_rel_1_1() \
    {setvalue(v.getvalue());} \
  _Concat4(os_rel_,base,_,member) () {} \
  static os_typespec* get_os_typespec(); \
 } 

#define __BASE_CC(base) base::

#if !defined(_OS_cfrontC) || defined(__os_sgi_mips)
/***
 ***  Workaround for inability to use typedef_name::~nested_class_name() to
 ***  define the destructor for a nested class out of line.
 ***/
#define _OS_REL_DESTRUCTOR_CLASS_NAME(base, member) \
	__BASE_CC(base) _Concat4(os_rel_,base,_,member)
#define _OS_REL_DEF_BASE(base, member)
#else
#define _OS_REL_DESTRUCTOR_CLASS_NAME(base, member) \
	_Concat5(os_rel_,base,_,member,_body)
#define _OS_REL_DEF_BASE(base, member) \
	typedef __BASE_CC(base) _Concat4(os_rel_,base,_,member) \
		_Concat5(os_rel_,base,_,member,_body);
#endif

#define os_relationship_1_1_body( base, member, type, inverse ) \
  _OSSG_BODY_VFT_MAKER(base,member) \
os_int32 _Concat4(os_rel_offsetof_,base,_,member) (){return __os_offsetof(base,member);} \
os_int32 _Concat4(os_rel_offsetof_,type,_,inverse) (); \
_OS_REL_DEF_BASE(base,member) \
void _OS_REL_DESTRUCTOR_CLASS_NAME(base,member)::setvalue(type* __val) { \
  os_rel_1_1::setvalue(__val,_Concat4(os_rel_offsetof_,base,_,member) (), \
		       _Concat4(os_rel_offsetof_,type,_,inverse) ());} \
_OS_REL_DESTRUCTOR_CLASS_NAME(base,member):: ~ _Concat4(os_rel_,base,_,member) () \
 {setvalue(0);} 


#define os_relationship_1_1_body_options( base, member, type, inverse, deletion, memb, invb ) \
  _OSSG_BODY_VFT_MAKER(base,member) \
os_int32 _Concat4(os_rel_offsetof_,base,_,member) (){return __os_offsetof(base,member);} \
os_int32 _Concat4(os_rel_offsetof_,type,_,inverse) (); \
_OS_REL_DEF_BASE(base,member) \
void _OS_REL_DESTRUCTOR_CLASS_NAME(base,member)::setvalue(type* __val) { \
  os_rel_1_1::setvalue(__val,_Concat4(os_rel_offsetof_,base,_,member) (), \
  _Concat4(os_rel_offsetof_,type,_,inverse) (), memb, invb);} \
_OS_REL_DESTRUCTOR_CLASS_NAME(base,member):: ~ _Concat4(os_rel_,base,_,member)(){if (deletion == os_propagate_delete) {\
  void* v = value();\
  if (!v)\
     return;\
  unset_inverse(_Concat4(os_rel_offsetof_,type,_,inverse)(), invb);\
  set_simple(0);\
  if (!os_rel_protect_being_deleted::objs_being_deleted_contains(v)) {\
  os_rel_protect_being_deleted protect(((char*)this)-_Concat4(os_rel_offsetof_,base,_,member)());\
  delete (type*)v; \
  }}\
else setvalue(0);}

#ifdef _OS_BorlandCC
#define __TURBO_TYPE_REFERENCE_KLUDGE(type) (type&)(char&)*(char*)
#else
#define __TURBO_TYPE_REFERENCE_KLUDGE(type) *(type*)
#endif

#define os_relationship_1_m( base, member, type, inverse, signature ) \
  friend os_int32 _Concat4(os_rel_offsetof_,base,_,member) (); \
  __FRIEND_KLUDGE(type) \
  void _Concat4(os_rel_typecheck_,base,_,member) () \
    {type * arg3 = 0; signature arg5 = 0; arg3 = arg5; arg5 = arg3;} \
  class OS_RELATIONSHIP_LINKAGE _Concat4(os_rel_,base,_,member) : public os_rel_1_m { public: \
  _OSSG_REF_CLASS_MARKER(type,inverse) \
  _OSSG_CLASS_VFT_MAKER(base,member) \
  void setvalue( signature ); \
  type* operator=( type * val) { setvalue(val); return val; } \
  type* operator=(_Concat4(os_rel_,base,_,member) & val) { type * real = (type*)val; setvalue(real); return real; } \
  operator type* () const { return (type*)(os_rel_1_m::getvalue());} \
  type* getvalue() const { return (type*)(os_rel_1_m::getvalue());} \
  type* operator->() const { return (type*)(os_rel_1_m::getvalue());} \
  type& operator*() const { return __TURBO_TYPE_REFERENCE_KLUDGE(type)(os_rel_1_m::getvalue());} \
  ~ _Concat4(os_rel_,base,_,member) (); \
  _Concat4(os_rel_,base,_,member) () {} \
  _Concat4(os_rel_,base,_,member) (_Concat4(os_rel_,base,_,member) & v): os_rel_1_m() \
    {setvalue(v.getvalue());} \
   static os_typespec* get_os_typespec(); \
 } 

#define os_relationship_1_m_body( base, member, type, inverse ) \
_OSSG_BODY_VFT_MAKER(base,member) \
os_int32 _Concat4(os_rel_offsetof_,base,_,member) (){return __os_offsetof(base,member);} \
os_int32 _Concat4(os_rel_offsetof_,type,_,inverse) (); \
_OS_REL_DEF_BASE(base,member) \
void _OS_REL_DESTRUCTOR_CLASS_NAME(base,member)::setvalue(type* __val) { \
  os_rel_1_m::setvalue(__val,_Concat4(os_rel_offsetof_,base,_,member) (), \
  _Concat4(os_rel_offsetof_,type,_,inverse) ());}\
_OS_REL_DESTRUCTOR_CLASS_NAME(base,member):: ~ _Concat4(os_rel_,base,_,member) () \
 {setvalue(0);} 

#define os_relationship_1_m_body_options( base, member, type, inverse, deletion, memb, invb) \
_OSSG_BODY_VFT_MAKER(base,member) \
os_int32 _Concat4(os_rel_offsetof_,base,_,member) (){return __os_offsetof(base,member);} \
os_int32 _Concat4(os_rel_offsetof_,type,_,inverse) (); \
_OS_REL_DEF_BASE(base,member) \
void _OS_REL_DESTRUCTOR_CLASS_NAME(base,member)::setvalue(type* __val) { \
  os_rel_1_m::setvalue(__val,_Concat4(os_rel_offsetof_,base,_,member) (), \
  _Concat4(os_rel_offsetof_,type,_,inverse) (), memb);}\
_OS_REL_DESTRUCTOR_CLASS_NAME(base,member):: ~ _Concat4(os_rel_,base,_,member)(){if (deletion == os_propagate_delete) {\
  void* v = value();\
  if (!v)\
    return;\
  unset_inverse(_Concat4(os_rel_offsetof_,base,_,member)(),\
		_Concat4(os_rel_offsetof_,type,_,inverse)());\
  set_simple(0);\
  if (!os_rel_protect_being_deleted::objs_being_deleted_contains(v)) {\
  os_rel_protect_being_deleted protect(((char*)this)-_Concat4(os_rel_offsetof_,base,_,member)());\
    delete (type*)v;\
  }}else setvalue(0);}\

#ifndef _OS_PSE_COLL
#define NEED_CAST_TO_OS_DB
#else
#define NEED_CAST_TO_OS_DB (os_database*)
#endif

#if !defined(OS_NO_COLLECTION_TEMPLATES) && !defined(_OS_VCPP_217r)

#define os_relationship_m_1( base, member, typ, inverse, signature ) \
  friend os_int32 _Concat4(os_rel_offsetof_,base,_,member) (); \
  __FRIEND_KLUDGE(typ) \
  void _Concat4(os_rel_typecheck_,base,_,member) () \
    {typ * arg3 = 0; signature* arg5 = 0; arg5->insert(arg3);} \
    class OS_RELATIONSHIP_LINKAGE _Concat4(os_rel_,base,_,member) : public os_rel_m_1 { \
  public: \
  _OSSG_REF_CLASS_MARKER(typ,inverse) \
  _OSSG_CLASS_VFT_MAKER(base,member) \
  void get_members(os_int32_r,os_int32_r) const ; \
  void get_members(os_int32_r,os_int32_r,os_int32_r) const ; \
  os_collection_p create_relationship_collection(os_int32 esize, \
		  /* behavior arguments */ \
                  os_boolean use_specified_behavior = 0, \
		  os_unsigned_int32 behavior = 0) \
    {return & signature :: create(this, \
				  use_specified_behavior ? behavior : 0, \
				  esize);} \
  void create_coll(os_database* db, os_unsigned_int32 beh = 0, \
		   os_int32 esize = 0) \
    { set_value((os_collection*)&signature::create(db,beh,esize)); } \
  void create_coll(os_segment* seg, os_unsigned_int32 beh = 0, \
		   os_int32 esize = 0) \
    { set_value((os_collection*)&signature::create(seg,beh,esize)); } \
  void create_coll(os_cluster* cl, os_unsigned_int32 beh = 0, \
		   os_int32 esize = 0) \
    { set_value((os_collection*)&signature::create(NEED_CAST_TO_OS_DB cl,beh,esize)); } \
  ~ _Concat4(os_rel_,base,_,member) (); \
  _Concat4(os_rel_,base,_,member) (const _Concat4(os_rel_,base,_,member) & v): os_rel_m_1() \
    {this->os_collection::operator =(*(os_collection*)(void*)(v.value()));} \
  _Concat4(os_rel_,base,_,member) () {} \
  void _insert(os_void_const_p v); \
  os_int32 _remove(os_void_const_p); \
  void _insert_first(os_void_const_p); \
  void _insert_last(os_void_const_p); \
  void _insert_after(os_void_const_p, os_cursor_const_r); \
  void _insert_before(os_void_const_p, os_cursor_const_r); \
  void _remove_at(os_cursor_const_r); \
  os_void_p _replace_at(os_void_const_p p, os_cursor_const_r c) ;\
  os_int32 _remove_first(os_void_const_p_r);\
  os_int32 _remove_last(os_void_const_p_r);\
  os_int32 _retrieve_first(os_void_const_p_r) const;\
  os_int32 _retrieve_last(os_void_const_p_r) const;\
  void _remove_at(os_unsigned_int32 position) ;\
  os_void_p _replace_at(os_void_const_p p, os_unsigned_int32 position) ;\
  void _insert_after(os_void_const_p p, os_unsigned_int32 position) ;\
  void _insert_before(os_void_const_p p, os_unsigned_int32 position) ;\
  os_unsigned_int32 _get_behavior() const \
    { return value() ? value()->get_behavior() : signature::default_behavior(); } \
  os_os_collection_type _type() const \
    { return value() ? value()->type() : signature::default_type(); } \
  signature& getvalue() { return *(signature*)(void*)&os_rel_m_1::getvalue(); } \
  operator signature& () { return *(signature*)(os_collection*)this; } \
  signature const& getvalue() const { return *(signature const*)(void*)&os_rel_m_1::getvalue(); }\
  operator signature const& () const {return *(signature const*)(os_collection*)this;}\
  signature& operator= (const _Concat4(os_rel_,base,_,member) & v) { os_collection::operator =(*(os_collection*)(void*)&(v.getvalue())); return this->getvalue();} \
  signature& operator= (const signature& s){os_collection::operator =(*(os_collection*)(void*)&s);return this->getvalue();} \
  os_Collection<typ*>& query(char*et,char*qs,os_database*db=0,char*fn=0,os_unsigned_int32 fl=0)\
    const {return (os_Collection<typ*>&)os_collection::query(et,qs,db,fn,fl);}\
  os_Collection<typ*>& query(const os_bound_query&q) \
     const {return (os_Collection<typ*>&)os_collection::query(q);} \
  typ* query_pick(os_char_p et,os_char_p qs,os_database_p db=0,os_char_p fn=0,os_unsigned_int32 fl=0)\
     const {return (typ*)os_collection::query_pick(et,qs,db,fn,fl);}\
  typ* query_pick(os_bound_query_const_r q)  \
     const { return (typ*) os_collection::query_pick(q); } \
  typ* retrieve_first() const { return (typ*) os_collection::retrieve_first();}\
  typ* retrieve_last() const {return (typ*) os_collection::retrieve_last();}\
  typ* retrieve(os_unsigned_int32 position) {return (typ*)os_collection::retrieve(position);}\
  typ* retrieve(const os_cursor&c) {return (typ*)os_collection::retrieve(c);}\
  typ* replace_at(os_void_const_p p, os_cursor_const_r c) {return (typ*)os_collection::replace_at(p,c);}\
  typ* replace_at(os_void_const_p p, os_unsigned_int32 position) {return (typ*)os_collection::replace_at(p,position);}\
  typ* remove_first() {return (typ*)os_collection::remove_first(); } \
  typ* remove_last() {return (typ*)os_collection::remove_last();}\
  static os_typespec* get_os_typespec(); \
  } 

#define os_relationship_m_m( base, member, typ, inverse, signature ) \
  friend os_int32 _Concat4(os_rel_offsetof_,base,_,member) (); \
  __FRIEND_KLUDGE(typ) \
  void _Concat4(os_rel_typecheck_,base,_,member) () \
    {typ * arg3 = 0; signature* arg5 = 0; arg5->insert(arg3);} \
  class OS_RELATIONSHIP_LINKAGE _Concat4(os_rel_,base,_,member) : public os_rel_m_m { public: \
  _OSSG_REF_CLASS_MARKER(typ,inverse) \
  _OSSG_CLASS_VFT_MAKER(base,member) \
  void get_members(os_int32_r,os_int32_r) const; \
  void get_members(os_int32_r,os_int32_r,os_int32_r) const; \
  os_collection_p create_relationship_collection(os_int32 esize, \
		  /* behavior arguments */ \
		  os_boolean use_specified_behavior = 0, \
		  os_unsigned_int32 behavior = 0) \
    {return & signature :: create(this, \
				  use_specified_behavior ? behavior : 0, \
				  esize);} \
  void create_coll(os_database* db, os_unsigned_int32 beh = 0, \
		   os_int32 esize = 0) \
    { set_value((os_collection*)&signature::create(db,beh,esize)); } \
  void create_coll(os_segment* seg, os_unsigned_int32 beh = 0, \
		   os_int32 esize = 0) \
    { set_value((os_collection*)&signature::create(seg,beh,esize)); } \
  void create_coll(os_cluster* cl, os_unsigned_int32 beh = 0, \
		   os_int32 esize = 0) \
    { set_value((os_collection*)&signature::create(NEED_CAST_TO_OS_DB cl,beh,esize)); } \
  ~ _Concat4(os_rel_,base,_,member) (); \
  _Concat4(os_rel_,base,_,member) () {} \
  _Concat4(os_rel_,base,_,member) (const _Concat4(os_rel_,base,_,member) & v): os_rel_m_m() \
    {this->os_collection::operator =(*(os_collection*)(void*)&(v.getvalue()));} \
  void _insert(os_void_const_p v); \
  os_void_p _replace_at(os_void_const_p p, os_cursor_const_r c) ;\
  os_int32 _remove_first(os_void_const_p_r);\
  os_int32 _remove_last(os_void_const_p_r);\
  os_int32 _retrieve_first(os_void_const_p_r) const;\
  os_int32 _retrieve_last(os_void_const_p_r) const;\
  os_void_p _replace_at(os_void_const_p p, os_unsigned_int32 position) ;\
  void _insert_before(os_void_const_p p, os_unsigned_int32 position) ;\
  void _insert_after(os_void_const_p p, os_unsigned_int32 position) ;\
  void _remove_at(os_unsigned_int32 position) ;\
  os_int32 _remove(os_void_const_p v); \
  void _insert_first(os_void_const_p v); \
  void _insert_last(os_void_const_p v); \
  void _insert_after(os_void_const_p v, os_cursor_const_r c); \
  void _insert_before(os_void_const_p v, os_cursor_const_r c); \
  void _remove_at(os_cursor_const_r c); \
  os_unsigned_int32 _get_behavior() const \
    { return value() ? value()->get_behavior() : signature::default_behavior(); } \
  os_os_collection_type _type() const \
    { return value() ? value()->type() : signature::default_type(); } \
  signature& getvalue() { return *(signature*)(void*)&os_rel_m_m::getvalue(); } \
  operator signature& () { return *(signature*)(os_collection*)this; } \
  signature const& getvalue() const {return *(signature const*)(void*)&os_rel_m_m::getvalue();}\
  operator signature const& () const {return *(signature const*)(os_collection*)this;}\
  signature& operator= (const _Concat4(os_rel_,base,_,member) & v) { os_collection::operator =(*(os_collection*)(void*)&(v.getvalue())); return this->getvalue(); } \
  signature& operator= (const signature& s){os_collection::operator =(*(os_collection*)(void*)&s);return this->getvalue();} \
  typ* pick() {return (typ*)os_collection::pick();} \
  typ* only() {return (typ*)os_collection::only();} \
  os_Collection<typ*>& query(char*et,char*qs,os_database*db=0,char*fn=0,os_unsigned_int32 fl=0)\
    const {return (os_Collection<typ*>&)os_collection::query(et,qs,db,fn,fl);}\
  os_Collection<typ*>& query(const os_bound_query&q) \
     const {return (os_Collection<typ*>&)os_collection::query(q);} \
  typ* query_pick(os_char_p et,os_char_p qs,os_database_p db=0,os_char_p fn=0,os_unsigned_int32 fl=0)\
     const {return (typ*)os_collection::query_pick(et,qs,db,fn,fl);}\
  typ* query_pick(os_bound_query_const_r q)  \
     const { return (typ*) os_collection::query_pick(q); } \
  typ* retrieve_first() const { return (typ*) os_collection::retrieve_first();}\
  typ* retrieve_last() const {return (typ*) os_collection::retrieve_last();}\
  typ* retrieve(os_unsigned_int32 position) {return (typ*)os_collection::retrieve(position);}\
  typ* retrieve(const os_cursor&c) {return (typ*)os_collection::retrieve(c);}\
  typ* replace_at(os_void_const_p p, os_cursor_const_r c) {return (typ*)os_collection::replace_at(p,c);}\
  typ* replace_at(os_void_const_p p, os_unsigned_int32 position) {return (typ*)os_collection::replace_at(p,position);}\
  typ* remove_first() {return (typ*)os_collection::remove_first(); } \
  typ* remove_last() {return (typ*)os_collection::remove_last();}\
  static os_typespec* get_os_typespec(); \
 } 

#else


#define os_relationship_m_1( base, member, typ, inverse, signature ) \
  friend os_int32 _Concat4(os_rel_offsetof_,base,_,member) (); \
   __FRIEND_KLUDGE(typ) \
  void _Concat4(os_rel_typecheck_,base,_,member) () \
    {typ * arg3 = 0; signature* arg5 = 0; arg5->insert(arg3);} \
  class OS_RELATIONSHIP_LINKAGE _Concat4(os_rel_,base,_,member) : public os_rel_m_1 { public: \
  _OSSG_REF_CLASS_MARKER(typ,inverse) \
  _OSSG_CLASS_VFT_MAKER(base,member) \
  os_collection_p create_relationship_collection(os_int32 esize, \
		  /* behavior arguments */ \
		  os_boolean use_specified_behavior = 0, \
		  os_unsigned_int32 behavior = 0) \
    {return & signature :: create(this, \
				  use_specified_behavior ? behavior : 0, \
				  esize);} \
  void create_coll(os_database* db, os_unsigned_int32 beh = 0, \
		   os_int32 esize = 0) \
    { set_value((os_collection*)&signature::create(db,beh,esize)); } \
  void create_coll(os_segment* seg, os_unsigned_int32 beh = 0, \
		   os_int32 esize = 0) \
    { set_value((os_collection*)&signature::create(seg,beh,esize)); } \
  void create_coll(os_cluster* cl, os_unsigned_int32 beh = 0, \
		   os_int32 esize = 0) \
    { set_value((os_collection*)&signature::create(NEED_CAST_TO_OS_DB cl,beh,esize)); } \
  void get_members(os_int32_r,os_int32_r) const ; \
  void get_members(os_int32_r,os_int32_r,os_int32_r) const ; \
  ~ _Concat4(os_rel_,base,_,member) (); \
  _Concat4(os_rel_,base,_,member) (const _Concat4(os_rel_,base,_,member) & v): os_rel_m_1() \
    {this->os_collection::operator =(*(os_collection*)(void*)&(v.getvalue()));} \
  _Concat4(os_rel_,base,_,member) () {} \
  void _insert(os_void_const_p v); \
  os_int32 _remove(os_void_const_p v); \
  void _insert_first(os_void_const_p v); \
  void _insert_last(os_void_const_p v); \
  void _insert_after(os_void_const_p v, os_cursor_const_r c); \
  void _insert_before(os_void_const_p v, os_cursor_const_r c); \
  void _remove_at(os_cursor_const_r c); \
  os_void_p _replace_at(os_void_const_p p, os_cursor_const_r c) ;\
  os_int32 _remove_first(os_void_const_p_r);\
  os_int32 _remove_last(os_void_const_p_r);\
  os_int32 _retrieve_first(os_void_const_p_r) const;\
  os_int32 _retrieve_last(os_void_const_p_r) const;\
  void _remove_at(os_unsigned_int32 position) ;\
  os_void_p _replace_at(os_void_const_p p, os_unsigned_int32 position) ;\
  void _insert_after(os_void_const_p p, os_unsigned_int32 position) ;\
  void _insert_before(os_void_const_p p, os_unsigned_int32 position) ;\
  os_unsigned_int32 _get_behavior() const \
    { return value() ? value()->get_behavior() : signature::default_behavior(); } \
  os_os_collection_type _type() const \
    { return value() ? value()->type() : signature::default_type(); } \
  signature& getvalue() { return *(signature*)(void*)&os_rel_m_1::getvalue(); } \
  operator signature& () { return *(signature*)(os_collection*)this; } \
  signature const& getvalue() const { return *(signature const*)(void*)&os_rel_m_1::getvalue(); }\
  operator signature const& () const {return *(signature const*)(os_collection*)this;}\
  signature& operator= (const os_collection& v) { os_collection::operator =(*(os_collection*)(void*)&v); return this->getvalue(); } \
  signature& operator= (const _Concat4(os_rel_,base,_,member) & v) { os_collection::operator =(*(os_collection*)(void*)&(v.getvalue())); return this->getvalue(); } \
  typ* pick() {return (typ*)os_collection::pick();} \
  typ* only() {return (typ*)os_collection::only();} \
  typ* query_pick(os_char_p et,os_char_p qs,os_database_p db=0,os_char_p fn=0,os_unsigned_int32 fl=0)\
     const {return (typ*)os_collection::query_pick(et,qs,db,fn,fl);}\
  typ* query_pick(os_bound_query_const_r q)  \
     const { return (typ*) os_collection::query_pick(q); } \
  typ* retrieve_first() const { return (typ*) os_collection::retrieve_first();}\
  typ* retrieve_last() const {return (typ*) os_collection::retrieve_last();}\
  typ* retrieve(os_unsigned_int32 position) {return (typ*)os_collection::retrieve(position);}\
  typ* retrieve(const os_cursor&c) {return (typ*)os_collection::retrieve(c);}\
  typ* replace_at(os_void_const_p p, os_cursor_const_r c) {return (typ*)os_collection::replace_at(p,c);}\
  typ* replace_at(os_void_const_p p, os_unsigned_int32 position) {return (typ*)os_collection::replace_at(p,position);}\
  typ* remove_first() {return (typ*)os_collection::remove_first(); } \
  typ* remove_last() {return (typ*)os_collection::remove_last();}\
  static os_typespec* get_os_typespec(); \
  } 

#define os_relationship_m_m( base, member, typ, inverse, signature ) \
  friend os_int32 _Concat4(os_rel_offsetof_,base,_,member) (); \
  __FRIEND_KLUDGE(typ) \
  void _Concat4(os_rel_typecheck_,base,_,member) () \
    {typ * arg3 = 0; signature* arg5 = 0; arg5->insert(arg3);} \
  class OS_RELATIONSHIP_LINKAGE _Concat4(os_rel_,base,_,member) : public os_rel_m_m { public: \
  _OSSG_REF_CLASS_MARKER(typ,inverse) \
  _OSSG_CLASS_VFT_MAKER(base,member) \
  os_collection_p create_relationship_collection(os_int32 esize, \
		  /* behavior arguments */ \
		  os_boolean use_specified_behavior = 0, \
		  os_unsigned_int32 behavior = 0) \
    {return & signature :: create(this, \
				  use_specified_behavior ? behavior : 0, \
				  esize);} \
  void create_coll(os_database* db, os_unsigned_int32 beh = 0, \
		   os_int32 esize = 0) \
	{ set_value((os_collection*)&signature::create(db,beh,esize)); } \
  void create_coll(os_segment* seg, os_unsigned_int32 beh = 0, \
		   os_int32 esize = 0) \
    { set_value((os_collection*)&signature::create(seg,beh,esize)); } \
  void create_coll(os_cluster* cl, os_unsigned_int32 beh = 0, \
		   os_int32 esize = 0) \
    { set_value((os_collection*)&signature::create(NEED_CAST_TO_OS_DB cl,beh,esize)); } \
  void get_members(os_int32_r,os_int32_r) const; \
  void get_members(os_int32_r,os_int32_r,os_int32_r) const; \
  ~ _Concat4(os_rel_,base,_,member) (); \
  _Concat4(os_rel_,base,_,member) () {} \
  _Concat4(os_rel_,base,_,member) (const _Concat4(os_rel_,base,_,member) & v): os_rel_m_m() \
    {this->os_collection::operator =(*(os_collection*)(void*)&(v.getvalue()));} \
  void _insert(os_void_const_p v); \
  os_int32 _remove(os_void_const_p v); \
  void _insert_first(os_void_const_p v); \
  void _insert_last(os_void_const_p v); \
  void _insert_after(os_void_const_p v, os_cursor_const_r c); \
  void _insert_before(os_void_const_p v, os_cursor_const_r c); \
  void _remove_at(os_cursor_const_r c); \
  os_void_p _replace_at(os_void_const_p p, os_cursor_const_r c) ;\
  os_int32 _remove_first(os_void_const_p_r);\
  os_int32 _remove_last(os_void_const_p_r);\
  os_int32 _retrieve_first(os_void_const_p_r) const;\
  os_int32 _retrieve_last(os_void_const_p_r) const;\
  void _remove_at(os_unsigned_int32 position) ;\
  os_void_p _replace_at(os_void_const_p p, os_unsigned_int32 position) ;\
  void _insert_after(os_void_const_p p, os_unsigned_int32 position) ;\
  void _insert_before(os_void_const_p p, os_unsigned_int32 position) ;\
  os_unsigned_int32 _get_behavior() const \
    { return value() ? value()->get_behavior() : signature::default_behavior(); } \
  os_os_collection_type _type() const \
    { return value() ? value()->type() : signature::default_type(); } \
  signature& getvalue() { return *(signature*)(void*)&os_rel_m_m::getvalue(); } \
  operator signature& () { return *(signature*)(os_collection*)this; } \
  signature const& getvalue() const {return *(signature const*)(void*)&os_rel_m_m::getvalue();}\
  operator signature const& () const {return *(signature const*)(os_collection*)this;}\
  signature& operator= (const os_collection& v) { os_collection::operator =(*(os_collection*)(void*)&v); return this->getvalue(); } \
  signature& operator= (const _Concat4(os_rel_,base,_,member) & v) { os_collection::operator =(*(os_collection*)(void*)&(v.getvalue())); return this->getvalue(); } \
  typ* pick() {return (typ*)os_collection::pick();} \
  typ* only() {return (typ*)os_collection::only();} \
  typ* query_pick(os_char_p et,os_char_p qs,os_database_p db=0,os_char_p fn=0,os_unsigned_int32 fl=0)\
     const {return (typ*)os_collection::query_pick(et,qs,db,fn,fl);}\
  typ* query_pick(os_bound_query_const_r q)  \
     const { return (typ*) os_collection::query_pick(q); } \
  typ* retrieve_first() const { return (typ*) os_collection::retrieve_first();}\
  typ* retrieve_last() const {return (typ*) os_collection::retrieve_last();}\
  typ* retrieve(os_unsigned_int32 position) {return (typ*)os_collection::retrieve(position);}\
  typ* retrieve(const os_cursor&c) {return (typ*)os_collection::retrieve(c);}\
  typ* replace_at(os_void_const_p p, os_cursor_const_r c) {return (typ*)os_collection::replace_at(p,c);}\
  typ* replace_at(os_void_const_p p, os_unsigned_int32 position) {return (typ*)os_collection::replace_at(p,position);}\
  typ* remove_first() {return (typ*)os_collection::remove_first(); } \
  typ* remove_last() {return (typ*)os_collection::remove_last();}\
  static os_typespec* get_os_typespec(); \
 } 

#endif

#define os_relationship_m_1_body( base, member, type, inverse ) \
  _OSSG_BODY_VFT_MAKER(base,member) \
os_int32 _Concat4(os_rel_offsetof_,base,_,member) (){return __os_offsetof(base,member);} \
os_int32 _Concat4(os_rel_offsetof_,type,_,inverse) (); \
_OS_REL_DEF_BASE(base,member) \
void _OS_REL_DESTRUCTOR_CLASS_NAME(base,member)::get_members(os_int32_r mem, os_int32_r inv) const { \
  mem = _Concat4(os_rel_offsetof_,base,_,member) (); \
  inv = _Concat4(os_rel_offsetof_,type,_,inverse) ();} \
void _OS_REL_DESTRUCTOR_CLASS_NAME(base,member)::get_members(os_int32_r mem, os_int32_r inv, os_int32_r ib) const { \
  mem = _Concat4(os_rel_offsetof_,base,_,member) (); \
  inv = _Concat4(os_rel_offsetof_,type,_,inverse) (); \
  ib = os_no_index; } \
_OS_REL_DESTRUCTOR_CLASS_NAME(base,member):: ~ _Concat4(os_rel_,base,_,member) () { clear(); }\
os_void_p _OS_REL_DESTRUCTOR_CLASS_NAME(base,member)::_replace_at(os_void_const_p p, os_cursor_const_r c) \
{return os_rel_m_1::__replace_at(p, c, _Concat4(os_rel_offsetof_,base,_,member) (), _Concat4(os_rel_offsetof_,type,_,inverse) ());} \
void _OS_REL_DESTRUCTOR_CLASS_NAME(base,member)::_remove_at(os_unsigned_int32 position) \
{os_rel_m_1::__remove_at(position,_Concat4(os_rel_offsetof_,base,_,member) (), _Concat4(os_rel_offsetof_,type,_,inverse) ());} \
os_void_p _OS_REL_DESTRUCTOR_CLASS_NAME(base,member)::_replace_at(os_void_const_p p, os_unsigned_int32 position) \
{return os_rel_m_1::__replace_at(p, position, _Concat4(os_rel_offsetof_,base,_,member) (), _Concat4(os_rel_offsetof_,type,_,inverse) ());} \
void _OS_REL_DESTRUCTOR_CLASS_NAME(base,member)::_insert_after(os_void_const_p p, os_unsigned_int32 position)\
{os_rel_m_1::__insert_after(p, position, _Concat4(os_rel_offsetof_,base,_,member) (), _Concat4(os_rel_offsetof_,type,_,inverse) ());} \
void _OS_REL_DESTRUCTOR_CLASS_NAME(base,member)::_insert_before(os_void_const_p p, os_unsigned_int32 position)\
{os_rel_m_1::__insert_before(p, position, _Concat4(os_rel_offsetof_,base,_,member) (), _Concat4(os_rel_offsetof_,type,_,inverse) ());} \
os_int32 _OS_REL_DESTRUCTOR_CLASS_NAME(base,member)::_retrieve_first(os_void_const_p_r v) const\
{return os_rel_m_1::__retrieve_first(v,_Concat4(os_rel_offsetof_,base,_,member) (), _Concat4(os_rel_offsetof_,type,_,inverse) ());} \
os_int32 _OS_REL_DESTRUCTOR_CLASS_NAME(base,member)::_retrieve_last(os_void_const_p_r v) const\
{return os_rel_m_1::__retrieve_last(v, _Concat4(os_rel_offsetof_,base,_,member) (), _Concat4(os_rel_offsetof_,type,_,inverse) ());} \
os_int32 _OS_REL_DESTRUCTOR_CLASS_NAME(base,member)::_remove_first(os_void_const_p_r v)\
{return os_rel_m_1::__remove_first(v,_Concat4(os_rel_offsetof_,base,_,member) (), _Concat4(os_rel_offsetof_,type,_,inverse) ());} \
os_int32 _OS_REL_DESTRUCTOR_CLASS_NAME(base,member)::_remove_last(os_void_const_p_r v)\
{return os_rel_m_1::__remove_last(v,_Concat4(os_rel_offsetof_,base,_,member) (), _Concat4(os_rel_offsetof_,type,_,inverse) ());} \
void _OS_REL_DESTRUCTOR_CLASS_NAME(base,member)::_insert(os_void_const_p v) \
{os_rel_m_1::__insert(v, _Concat4(os_rel_offsetof_,base,_,member) (), _Concat4(os_rel_offsetof_,type,_,inverse) ());} \
os_int32 _OS_REL_DESTRUCTOR_CLASS_NAME(base,member)::_remove(os_void_const_p v) \
{return os_rel_m_1::__remove(v, _Concat4(os_rel_offsetof_,base,_,member) (), _Concat4(os_rel_offsetof_,type,_,inverse) ());} \
void _OS_REL_DESTRUCTOR_CLASS_NAME(base,member)::_insert_first(os_void_const_p v) \
{os_rel_m_1::__insert_first(v, _Concat4(os_rel_offsetof_,base,_,member) (), _Concat4(os_rel_offsetof_,type,_,inverse) ());} \
void _OS_REL_DESTRUCTOR_CLASS_NAME(base,member)::_insert_last(os_void_const_p v) \
{os_rel_m_1::__insert_last(v, _Concat4(os_rel_offsetof_,base,_,member) (), _Concat4(os_rel_offsetof_,type,_,inverse) ());} \
void _OS_REL_DESTRUCTOR_CLASS_NAME(base,member)::_insert_after(os_void_const_p v, os_cursor_const_r c) \
{os_rel_m_1::__insert_after(v, c, _Concat4(os_rel_offsetof_,base,_,member) (), _Concat4(os_rel_offsetof_,type,_,inverse) ());} \
void _OS_REL_DESTRUCTOR_CLASS_NAME(base,member)::_insert_before(os_void_const_p v, os_cursor_const_r c) \
{os_rel_m_1::__insert_before(v, c, _Concat4(os_rel_offsetof_,base,_,member) (), _Concat4(os_rel_offsetof_,type,_,inverse) ());} \
void _OS_REL_DESTRUCTOR_CLASS_NAME(base,member)::_remove_at(os_cursor_const_r c) \
{os_rel_m_1::__remove_at(c, _Concat4(os_rel_offsetof_,base,_,member) (), _Concat4(os_rel_offsetof_,type,_,inverse) ());}

#define os_relationship_m_1_body_options( base, member, type, inverse, deletion, memb, invb) \
_OSSG_BODY_VFT_MAKER(base,member) \
os_int32 _Concat4(os_rel_offsetof_,base,_,member) (){return __os_offsetof(base,member);} \
os_int32 _Concat4(os_rel_offsetof_,type,_,inverse) (); \
_OS_REL_DEF_BASE(base,member) \
void _OS_REL_DESTRUCTOR_CLASS_NAME(base,member)::get_members(os_int32_r mem, os_int32_r inv) const { \
  mem = _Concat4(os_rel_offsetof_,base,_,member) (); \
  inv = _Concat4(os_rel_offsetof_,type,_,inverse) ();} \
void _OS_REL_DESTRUCTOR_CLASS_NAME(base,member)::get_members(os_int32_r mem, os_int32_r inv, os_int32_r ib) const { \
  mem = _Concat4(os_rel_offsetof_,base,_,member) (); \
  inv = _Concat4(os_rel_offsetof_,type,_,inverse) (); \
  ib = invb;} \
os_void_p _OS_REL_DESTRUCTOR_CLASS_NAME(base,member)::_replace_at(os_void_const_p p, os_cursor_const_r c) \
{return os_rel_m_1::__replace_at(p, c, _Concat4(os_rel_offsetof_,base,_,member) (), _Concat4(os_rel_offsetof_,type,_,inverse) ());} \
void _OS_REL_DESTRUCTOR_CLASS_NAME(base,member)::_remove_at(os_unsigned_int32 position) \
{os_rel_m_1::__remove_at(position,_Concat4(os_rel_offsetof_,base,_,member) (), _Concat4(os_rel_offsetof_,type,_,inverse) ());} \
os_void_p _OS_REL_DESTRUCTOR_CLASS_NAME(base,member)::_replace_at(os_void_const_p p, os_unsigned_int32 position) \
{return os_rel_m_1::__replace_at(p, position, _Concat4(os_rel_offsetof_,base,_,member) (), _Concat4(os_rel_offsetof_,type,_,inverse) ());} \
void _OS_REL_DESTRUCTOR_CLASS_NAME(base,member)::_insert_after(os_void_const_p p, os_unsigned_int32 position) \
{os_rel_m_1::__insert_after(p, position, _Concat4(os_rel_offsetof_,base,_,member) (), _Concat4(os_rel_offsetof_,type,_,inverse) ());} \
void _OS_REL_DESTRUCTOR_CLASS_NAME(base,member)::_insert_before(os_void_const_p p, os_unsigned_int32 position) \
{os_rel_m_1::__insert_before(p, position, _Concat4(os_rel_offsetof_,base,_,member) (), _Concat4(os_rel_offsetof_,type,_,inverse) ());} \
os_int32 _OS_REL_DESTRUCTOR_CLASS_NAME(base,member)::_retrieve_first(os_void_const_p_r v) const\
{return os_rel_m_1::__retrieve_first(v,_Concat4(os_rel_offsetof_,base,_,member) (), _Concat4(os_rel_offsetof_,type,_,inverse) ());} \
os_int32 _OS_REL_DESTRUCTOR_CLASS_NAME(base,member)::_retrieve_last(os_void_const_p_r v) const\
{return os_rel_m_1::__retrieve_last(v, _Concat4(os_rel_offsetof_,base,_,member) (), _Concat4(os_rel_offsetof_,type,_,inverse) ());} \
os_int32 _OS_REL_DESTRUCTOR_CLASS_NAME(base,member)::_remove_first(os_void_const_p_r v)\
{return os_rel_m_1::__remove_first(v,_Concat4(os_rel_offsetof_,base,_,member) (), _Concat4(os_rel_offsetof_,type,_,inverse) ());} \
os_int32 _OS_REL_DESTRUCTOR_CLASS_NAME(base,member)::_remove_last(os_void_const_p_r v)\
{return os_rel_m_1::__remove_last(v,_Concat4(os_rel_offsetof_,base,_,member) (), _Concat4(os_rel_offsetof_,type,_,inverse) ());} \
void _OS_REL_DESTRUCTOR_CLASS_NAME(base,member):: _insert(os_void_const_p v) \
{os_rel_m_1::__insert(v, _Concat4(os_rel_offsetof_,base,_,member) (), _Concat4(os_rel_offsetof_,type,_,inverse) (), invb);} \
os_int32 _OS_REL_DESTRUCTOR_CLASS_NAME(base,member):: _remove(os_void_const_p v) \
{return os_rel_m_1::__remove(v, _Concat4(os_rel_offsetof_,base,_,member) (), _Concat4(os_rel_offsetof_,type,_,inverse) (), invb);}\
void _OS_REL_DESTRUCTOR_CLASS_NAME(base,member):: _insert_first(os_void_const_p v) \
{os_rel_m_1::__insert_first(v, _Concat4(os_rel_offsetof_,base,_,member) (), _Concat4(os_rel_offsetof_,type,_,inverse) (), invb);} \
void _OS_REL_DESTRUCTOR_CLASS_NAME(base,member):: _insert_last(os_void_const_p v) \
{os_rel_m_1::__insert_last(v, _Concat4(os_rel_offsetof_,base,_,member) (), _Concat4(os_rel_offsetof_,type,_,inverse) (), invb);} \
void _OS_REL_DESTRUCTOR_CLASS_NAME(base,member):: _insert_after(os_void_const_p v, os_cursor_const_r c) \
{os_rel_m_1::__insert_after(v, c, _Concat4(os_rel_offsetof_,base,_,member) (), _Concat4(os_rel_offsetof_,type,_,inverse) (), invb);}\
void _OS_REL_DESTRUCTOR_CLASS_NAME(base,member):: _insert_before(os_void_const_p v, os_cursor_const_r c) \
{os_rel_m_1::__insert_before(v, c, _Concat4(os_rel_offsetof_,base,_,member) (), _Concat4(os_rel_offsetof_,type,_,inverse) (), invb);} \
void _OS_REL_DESTRUCTOR_CLASS_NAME(base,member):: _remove_at(os_cursor_const_r c) \
{os_rel_m_1::__remove_at(c, _Concat4(os_rel_offsetof_,base,_,member) (), _Concat4(os_rel_offsetof_,type,_,inverse) (), invb);}\
_OS_REL_DESTRUCTOR_CLASS_NAME(base,member):: ~ _Concat4(os_rel_,base,_,member)(){\
  if (!value())\
    return;\
  if (deletion == os_propagate_delete) { \
 os_rel_protect_being_deleted protect(((char*)this)-_Concat4(os_rel_offsetof_,base,_,member)());\
  while (value()->cardinality()) {\
    void* v = value()->pick();\
    _remove_inverse(v);\
    value()->remove(v);\
    if (!os_rel_protect_being_deleted::objs_being_deleted_contains(v))\
      delete (type*)v;\
  }\
} else clear(); }\

#define os_relationship_m_m_body( base, member, type, inverse ) \
  _OSSG_BODY_VFT_MAKER(base,member) \
os_int32 _Concat4(os_rel_offsetof_,base,_,member) (){return __os_offsetof(base,member);} \
os_int32 _Concat4(os_rel_offsetof_,type,_,inverse) (); \
_OS_REL_DEF_BASE(base,member) \
void _OS_REL_DESTRUCTOR_CLASS_NAME(base,member)::get_members(os_int32_r mem, os_int32_r inv) const { \
  mem = _Concat4(os_rel_offsetof_,base,_,member) (); \
  inv = _Concat4(os_rel_offsetof_,type,_,inverse) ();} \
void _OS_REL_DESTRUCTOR_CLASS_NAME(base,member)::get_members(os_int32_r mem, os_int32_r inv, os_int32_r ib) const { \
  mem = _Concat4(os_rel_offsetof_,base,_,member) (); \
  inv = _Concat4(os_rel_offsetof_,type,_,inverse) (); \
  ib = os_no_index; } \
_OS_REL_DESTRUCTOR_CLASS_NAME(base,member):: ~ _Concat4(os_rel_,base,_,member) () { clear(); }\
os_void_p _OS_REL_DESTRUCTOR_CLASS_NAME(base,member)::_replace_at(os_void_const_p p, os_cursor_const_r c) \
{return os_rel_m_m::__replace_at(p, c, _Concat4(os_rel_offsetof_,base,_,member) (), _Concat4(os_rel_offsetof_,type,_,inverse) ());} \
void _OS_REL_DESTRUCTOR_CLASS_NAME(base,member)::_remove_at(os_unsigned_int32 position) \
{os_rel_m_m::__remove_at(position,_Concat4(os_rel_offsetof_,base,_,member) (), _Concat4(os_rel_offsetof_,type,_,inverse) ());} \
os_void_p _OS_REL_DESTRUCTOR_CLASS_NAME(base,member)::_replace_at(os_void_const_p p, os_unsigned_int32 position) \
{return os_rel_m_m::__replace_at(p, position, _Concat4(os_rel_offsetof_,base,_,member) (), _Concat4(os_rel_offsetof_,type,_,inverse) ());} \
void _OS_REL_DESTRUCTOR_CLASS_NAME(base,member)::_insert_after(os_void_const_p p, os_unsigned_int32 position) \
{os_rel_m_m::__insert_after(p, position, _Concat4(os_rel_offsetof_,base,_,member) (), _Concat4(os_rel_offsetof_,type,_,inverse) ());} \
void _OS_REL_DESTRUCTOR_CLASS_NAME(base,member)::_insert_before(os_void_const_p p, os_unsigned_int32 position) \
{os_rel_m_m::__insert_before(p, position, _Concat4(os_rel_offsetof_,base,_,member) (), _Concat4(os_rel_offsetof_,type,_,inverse) ());} \
os_int32 _OS_REL_DESTRUCTOR_CLASS_NAME(base,member)::_retrieve_first(os_void_const_p_r v) const\
{return os_rel_m_m::__retrieve_first(v,_Concat4(os_rel_offsetof_,base,_,member) (), _Concat4(os_rel_offsetof_,type,_,inverse) ());} \
os_int32 _OS_REL_DESTRUCTOR_CLASS_NAME(base,member)::_retrieve_last(os_void_const_p_r v) const\
{return os_rel_m_m::__retrieve_last(v, _Concat4(os_rel_offsetof_,base,_,member) (), _Concat4(os_rel_offsetof_,type,_,inverse) ());} \
os_int32 _OS_REL_DESTRUCTOR_CLASS_NAME(base,member)::_remove_first(os_void_const_p_r v)\
{return os_rel_m_m::__remove_first(v,_Concat4(os_rel_offsetof_,base,_,member) (), _Concat4(os_rel_offsetof_,type,_,inverse) ());} \
os_int32 _OS_REL_DESTRUCTOR_CLASS_NAME(base,member)::_remove_last(os_void_const_p_r v)\
{return os_rel_m_m::__remove_last(v,_Concat4(os_rel_offsetof_,base,_,member) (), _Concat4(os_rel_offsetof_,type,_,inverse) ());} \
void _OS_REL_DESTRUCTOR_CLASS_NAME(base,member)::_insert(os_void_const_p v) \
{os_rel_m_m::__insert(v, _Concat4(os_rel_offsetof_,base,_,member) (), _Concat4(os_rel_offsetof_,type,_,inverse) ());} \
os_int32 _OS_REL_DESTRUCTOR_CLASS_NAME(base,member)::_remove(os_void_const_p v) \
{return os_rel_m_m::__remove(v, _Concat4(os_rel_offsetof_,base,_,member) (), _Concat4(os_rel_offsetof_,type,_,inverse) ());} \
void _OS_REL_DESTRUCTOR_CLASS_NAME(base,member)::_insert_first(os_void_const_p v) \
{os_rel_m_m::__insert_first(v, _Concat4(os_rel_offsetof_,base,_,member) (), _Concat4(os_rel_offsetof_,type,_,inverse) ());} \
void _OS_REL_DESTRUCTOR_CLASS_NAME(base,member)::_insert_last(os_void_const_p v) \
{os_rel_m_m::__insert_last(v, _Concat4(os_rel_offsetof_,base,_,member) (), _Concat4(os_rel_offsetof_,type,_,inverse) ());} \
void _OS_REL_DESTRUCTOR_CLASS_NAME(base,member)::_insert_after(os_void_const_p v, os_cursor_const_r c) \
{os_rel_m_m::__insert_after(v, c, _Concat4(os_rel_offsetof_,base,_,member) (), _Concat4(os_rel_offsetof_,type,_,inverse) ());} \
void _OS_REL_DESTRUCTOR_CLASS_NAME(base,member)::_insert_before(os_void_const_p v, os_cursor_const_r c) \
{os_rel_m_m::__insert_before(v, c, _Concat4(os_rel_offsetof_,base,_,member) (), _Concat4(os_rel_offsetof_,type,_,inverse) ());} \
void _OS_REL_DESTRUCTOR_CLASS_NAME(base,member)::_remove_at(os_cursor_const_r c) \
{os_rel_m_m::__remove_at(c, _Concat4(os_rel_offsetof_,base,_,member) (), _Concat4(os_rel_offsetof_,type,_,inverse) ());}

#define os_relationship_m_m_body_options( base, member, type, inverse, deletion, memb, invb) \
  _OSSG_BODY_VFT_MAKER(base,member) \
os_int32 _Concat4(os_rel_offsetof_,base,_,member) (){return __os_offsetof(base,member);} \
os_int32 _Concat4(os_rel_offsetof_,type,_,inverse) (); \
_OS_REL_DEF_BASE(base,member) \
void _OS_REL_DESTRUCTOR_CLASS_NAME(base,member)::get_members(os_int32_r mem, os_int32_r inv) const { \
  mem = _Concat4(os_rel_offsetof_,base,_,member) (); \
  inv = _Concat4(os_rel_offsetof_,type,_,inverse) ();} \
void _OS_REL_DESTRUCTOR_CLASS_NAME(base,member)::get_members(os_int32_r mem, os_int32_r inv, os_int32_r ib) const { \
  mem = _Concat4(os_rel_offsetof_,base,_,member) (); \
  inv = _Concat4(os_rel_offsetof_,type,_,inverse) (); \
  ib=os_auto_index; } \
os_void_p _OS_REL_DESTRUCTOR_CLASS_NAME(base,member)::_replace_at(os_void_const_p p, os_cursor_const_r c) \
{return os_rel_m_m::__replace_at(p, c, _Concat4(os_rel_offsetof_,base,_,member) (), _Concat4(os_rel_offsetof_,type,_,inverse) ());} \
void _OS_REL_DESTRUCTOR_CLASS_NAME(base,member)::_remove_at(os_unsigned_int32 position) \
{os_rel_m_m::__remove_at(position,_Concat4(os_rel_offsetof_,base,_,member) (), _Concat4(os_rel_offsetof_,type,_,inverse) ());} \
os_void_p _OS_REL_DESTRUCTOR_CLASS_NAME(base,member)::_replace_at(os_void_const_p p, os_unsigned_int32 position) \
{return os_rel_m_m::__replace_at(p, position, _Concat4(os_rel_offsetof_,base,_,member) (), _Concat4(os_rel_offsetof_,type,_,inverse) ());} \
void _OS_REL_DESTRUCTOR_CLASS_NAME(base,member)::_insert_after(os_void_const_p p, os_unsigned_int32 position) \
{os_rel_m_m::__insert_after(p,position,  _Concat4(os_rel_offsetof_,base,_,member) (), _Concat4(os_rel_offsetof_,type,_,inverse) ());} \
void _OS_REL_DESTRUCTOR_CLASS_NAME(base,member)::_insert_before(os_void_const_p p, os_unsigned_int32 position) \
{os_rel_m_m::__insert_before(p, position, _Concat4(os_rel_offsetof_,base,_,member) (), _Concat4(os_rel_offsetof_,type,_,inverse) ());} \
os_int32 _OS_REL_DESTRUCTOR_CLASS_NAME(base,member)::_retrieve_first(os_void_const_p_r v) const\
{return os_rel_m_m::__retrieve_first(v,_Concat4(os_rel_offsetof_,base,_,member) (), _Concat4(os_rel_offsetof_,type,_,inverse) ());} \
os_int32 _OS_REL_DESTRUCTOR_CLASS_NAME(base,member)::_retrieve_last(os_void_const_p_r v) const\
{return os_rel_m_m::__retrieve_last(v, _Concat4(os_rel_offsetof_,base,_,member) (), _Concat4(os_rel_offsetof_,type,_,inverse) ());} \
os_int32 _OS_REL_DESTRUCTOR_CLASS_NAME(base,member)::_remove_first(os_void_const_p_r v)\
{return os_rel_m_m::__remove_first(v,_Concat4(os_rel_offsetof_,base,_,member) (), _Concat4(os_rel_offsetof_,type,_,inverse) ());} \
os_int32 _OS_REL_DESTRUCTOR_CLASS_NAME(base,member)::_remove_last(os_void_const_p_r v)\
{return os_rel_m_m::__remove_last(v,_Concat4(os_rel_offsetof_,base,_,member) (), _Concat4(os_rel_offsetof_,type,_,inverse) ());} \
void _OS_REL_DESTRUCTOR_CLASS_NAME(base,member)::_insert(os_void_const_p v) \
{os_rel_m_m::__insert(v, _Concat4(os_rel_offsetof_,base,_,member) (), _Concat4(os_rel_offsetof_,type,_,inverse) ());} \
os_int32 _OS_REL_DESTRUCTOR_CLASS_NAME(base,member)::_remove(os_void_const_p v) \
{return os_rel_m_m::__remove(v, _Concat4(os_rel_offsetof_,base,_,member) (), _Concat4(os_rel_offsetof_,type,_,inverse) ());} \
void _OS_REL_DESTRUCTOR_CLASS_NAME(base,member)::_insert_first(os_void_const_p v) \
{os_rel_m_m::__insert_first(v, _Concat4(os_rel_offsetof_,base,_,member) (), _Concat4(os_rel_offsetof_,type,_,inverse) ());} \
void _OS_REL_DESTRUCTOR_CLASS_NAME(base,member)::_insert_last(os_void_const_p v) \
{os_rel_m_m::__insert_last(v, _Concat4(os_rel_offsetof_,base,_,member) (), _Concat4(os_rel_offsetof_,type,_,inverse) ());} \
void _OS_REL_DESTRUCTOR_CLASS_NAME(base,member)::_insert_after(os_void_const_p v, os_cursor_const_r c) \
{os_rel_m_m::__insert_after(v, c, _Concat4(os_rel_offsetof_,base,_,member) (), _Concat4(os_rel_offsetof_,type,_,inverse) ());} \
void _OS_REL_DESTRUCTOR_CLASS_NAME(base,member)::_insert_before(os_void_const_p v, os_cursor_const_r c) \
{os_rel_m_m::__insert_before(v, c, _Concat4(os_rel_offsetof_,base,_,member) (), _Concat4(os_rel_offsetof_,type,_,inverse) ());} \
void _OS_REL_DESTRUCTOR_CLASS_NAME(base,member)::_remove_at(os_cursor_const_r c) \
{os_rel_m_m::__remove_at(c, _Concat4(os_rel_offsetof_,base,_,member) (), _Concat4(os_rel_offsetof_,type,_,inverse) ());}\
_OS_REL_DESTRUCTOR_CLASS_NAME(base,member):: ~ _Concat4(os_rel_,base,_,member)(){if (!value())\
    return;\
  if (deletion == os_propagate_delete) { \
  os_rel_protect_being_deleted protect(((char*)this)-_Concat4(os_rel_offsetof_,base,_,member)());\
  while (value()->cardinality()) {\
    void* v = value()->pick();\
    _remove_inverse(v);\
    value()->remove(v);\
    if (!os_rel_protect_being_deleted::objs_being_deleted_contains(v))\
      delete (type*)v;\
  }\
  } else clear(); }\

#ifndef    _OS_PSE_COLL
#include <ostore/hdrend.hh>
#else
_OS_END_NAMESPACE
#endif     // _OS_PSE_COLL

#endif

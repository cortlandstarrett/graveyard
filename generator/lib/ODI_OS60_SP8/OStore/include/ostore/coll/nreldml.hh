/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


/*
*/
#ifndef _RELATIONDML_H_
#define _RELATIONDML_H_
#ifndef _OS_PSE_COLL
#include <ostore/hdrstart.hh>
#else
#include <os_pse/psecoll/hdrstart.hh>
#endif

/* These structures are known to the compiler */

typedef void* (*_Rel_ctor_type)(void*);
typedef void (*_Rel_dtor_type)(void*);
typedef os_collection* (*_Rel_coll_base_fcn_type) (void *);
typedef os_collection* _Rel_coll_base_type;

struct _Rel_mptr_dummy {	/* a vtbl is an array of these structs */
  os_int16 fudge_this;		/* add this to this before calling the vfunction */
  os_int16 not_used_here;		/* ignore this field (none of my business) */
  _Rel_dtor_type vfunction;	/* function pointer */
};

struct _Rel_vtbl_info {		/* this struct tells you how to get to a vtbl entry */
  os_int32 vptr_offset;		/* offset of the vtbl pointer from a _Rel this pointer */
  os_int32 vtbl_index;		/* the index into the vtbl (an array of _Rel_mptr_dummy) */
};

struct _Rel_dtor_info {		/* a pointer to one of these is the _Rel_dtor_info param */
  os_int16 dtor_is_virtual;	/* identifies which of the union fields is valid */
  union {
    _Rel_dtor_type nonvfunction; /* a non-virtual function ptr (dtor_is_virtual = 0) */
    _Rel_vtbl_info vtbl_info;	/* embedded struct telling how to get to the vtbl entry */
  };				/* leave the union anonymous, it makes the
				   compiler easier to code. */
};


/* End of compiler-known stuff */

void _Rel_single_assignment_operator (void * new_inv,
				      void * old_inv,
				      os_unsigned_int32 inverse_is_single,
				      os_unsigned_int32 inverse_attribute_offset,
				      os_unsigned_int32 attribute_offset,
				      void * here,
				      os_collection* old_inv_coll,
				      os_collection* inv_coll,
				      os_int32 is_indexable,
				      os_int32 inverse_is_indexable,
				      os_int32 backptr_offset,
				      os_int32 inverse_backptr_offset);


void _Rel_single_clear_inverse (void * old_inv,
				os_unsigned_int32 inverse_is_single,
				os_unsigned_int32 inverse_attribute_offset,
				void * here,
				os_collection* inv_coll,
				os_int32 inverse_is_indexable,
				os_int32 inverse_backptr_offset);

template<class basetype, 
	 class valuetype, 
	 __expression attribute_offset, 
	 __expression inverse_attribute_offset,
	 __expression inverse_is_single,
	 __expression get_p_collection_ptr,
	 __expression inverse_size,
	 __expression inverse_is_indexable,
	 __expression inverse_backptr_offset,
	 __expression is_indexable,
	 __expression backptr_offset
	 >
class _Rel_single : public os_rel_single
{
private:
  /* This finds a set-valued inverse */
  os_collection* getpcollptr (void * v) {
    return $inverse_is_single ? 
      (os_collection*)v :
    (*(_Rel_coll_base_fcn_type)$get_p_collection_ptr)(v);
  }
  basetype* backup() const {
    return (basetype*)((char*)this-(os_int32)$attribute_offset);
  }
public:
  ~_Rel_single()
    {
      _Rel_single_clear_inverse(
				(void *)value,
				(os_unsigned_int32) $inverse_is_single,
				(os_unsigned_int32) $inverse_attribute_offset,
				backup(),
				value == 0 ? 0 :
				getpcollptr((char*)value + $inverse_attribute_offset),
				(os_int32) $inverse_is_indexable,
				(os_int32) $inverse_backptr_offset);
    }
  void set_inverse(valuetype* v) {
    _Rel_single_clear_inverse ((void *)v,
			       (os_unsigned_int32)$inverse_is_single,
			       (os_unsigned_int32)$inverse_attribute_offset,
			       backup(),
			       value == 0 ? 0 :
			       getpcollptr((char*)value
					   + $inverse_attribute_offset),
			       (os_int32) $inverse_is_indexable,
			       (os_int32) $inverse_backptr_offset );
    value = v;
  }
  void unset_inverse(valuetype* v) { value = (((os_int32)value)==(os_int32)v) ? 0 : value; }
  valuetype * getvalue() const { return (valuetype*)value; };
  operator valuetype *() const { return (valuetype*)value; };
  valuetype * operator->() const { return (valuetype*)value; };
  valuetype* assignment_operator(valuetype* v) {
    _Rel_single_assignment_operator 
	  (v, (void *)value,
	   (os_unsigned_int32) $inverse_is_single,
	   (os_unsigned_int32) $inverse_attribute_offset,
	   (os_unsigned_int32) $attribute_offset,
	   backup(),
	   value == 0 ? 0 :
	   getpcollptr((char*)value + 
		       $inverse_attribute_offset),
	   v == 0 ? 0 :
	   /* the new inverse gets passed here */
	   getpcollptr((char*)v + 
		       $inverse_attribute_offset),
	   (os_int32) $is_indexable,
	   (os_int32) $inverse_is_indexable,
	   (os_int32) $backptr_offset,
	   (os_int32) $inverse_backptr_offset );
      /* value = v now in _Rel_single_assignment_operator */
      return v;
  }

  /* not const, since we bop the inverse in *v */
  valuetype* operator =(valuetype * v) {
    return (assignment_operator(v));
  }
  valuetype* setvalue(valuetype * v) {
    return (assignment_operator(v));
  }
  _Rel_single(_Rel_single& v) {value = 0; setvalue(v.getvalue());};
  _Rel_single() { 
    value = 0;
  };
};

/* Here is template _Rel_many.  This family of classes is used as the
implementation for "simple" inverse relationships (that is, inverses
with only two participants and no ancillary members, where there is no
explicit relationship instance).

The "inverse_member" syntax on a class data member definition results
in the generation of an embedded attribute class, which is actually
an appropriately parameterized member of this template family.  This
template is only used when the declared type of the attribute is a
collection (that is, this is a many-valued attribute); if the declared
type is a singleton, then _Rel_single is used instead.  The declared
type of the attribute must be an collection of pointers to class objects.

*/
template<class basetype,
	class valuetype,
	__expression attribute_offset,
	__expression inverse_attribute_offset,
	__expression inverse_is_single,
	__expression get_p_collection_ptr,
	__expression inverse_size,
	__expression inverse_is_indexable,
	__expression inverse_backptr_offset,
	class coll_type
	>
class _Rel_many : public os_rel_many
{
public:
  /* Here for inlining reasons, don't move */
  basetype* backup() const {
    return (basetype*)((char*)this-(os_int32)$attribute_offset);
  }

  os_unsigned_int32 _get_behavior() const
    { return value ? value->get_behavior() : coll_type::default_behavior(); }

  const os_coll_rep_descriptor& _get_rep() const
    { return value ? value->get_rep() : no_value_descriptor(); }

  const os_coll_rep_descriptor* _get_retained_rep() const
    { return value ? value->get_retained_rep() : 0; }

private:
  /* get pcollptr for inverse if its a set */
  os_collection* inv_pcollptr (void * v) {
      return ($inverse_is_single) ?
      (os_collection*)v :
      (*(_Rel_coll_base_fcn_type)$get_p_collection_ptr)(v);
  }

  os_collection * pcollptr (void * v) {
      return (*(void**)v) ? (os_collection*)
	/* This is what it really is */
	(coll_type *)v :
      0;
  }

  void insert_inverse(void const * v) {
    if (v)
      _Rel_many_insert(
		     (os_collection*) this,
		     (void *)v,
		     (os_unsigned_int32) $attribute_offset,
		     (os_unsigned_int32) $inverse_is_single,
		     (os_unsigned_int32) $inverse_attribute_offset,
		     (void *)this,
		     (void *) backup(),
		     (os_int32) $inverse_is_indexable,
		     (os_int32) $inverse_backptr_offset);
  }
  void remove_inverse(void const * v) {
    if (v)
      _Rel_many_remove((os_collection*) this,
		     (void *) v,
		     (os_unsigned_int32) $inverse_is_single,
		     (os_unsigned_int32) $inverse_attribute_offset,
		     (void *)this,
		     (void *)backup(),
		     (os_int32) $inverse_is_indexable,
		     (os_int32) $inverse_backptr_offset);
  }
  void assign_kill () {
      _Rel_many_assignment_kill
	  (pcollptr (this),
	   backup(),
	   (os_unsigned_int32) $inverse_attribute_offset,
	   (os_unsigned_int32) $inverse_is_single,
	   (void *)this,
	   (os_int32) $inverse_is_indexable,
	   (os_int32) $inverse_backptr_offset );
  }

private:
  /* the following functions are here only for compatibility with the LI interface */
  virtual void get_members(os_int32& mem, os_int32& inv) const 
    { mem = $attribute_offset; inv = $inverse_attribute_offset; }
  virtual void get_members(os_int32& mem, os_int32& inv, os_int32& backptr) const 
    { mem = $attribute_offset; inv = $inverse_attribute_offset; 
      backptr = ($inverse_is_indexable)?
                ($inverse_backptr_offset+$inverse_attribute_offset):os_no_index;}
  virtual os_collection* create_relationship_collection(os_int32 esize,
		  /* rep arguments */
		  const os_coll_rep_descriptor* desc = 0,
		  os_int32 retain_rep = 0,
		  /* behavior arguments */
		  os_boolean use_specified_behavior = 0,
		  os_unsigned_int32 behavior = 0)
      { return & coll_type::create((const void*)this,
				  use_specified_behavior ? behavior : 0,
				  esize,
				  desc,
				  retain_rep); }
private:
  /* the following functions implement the part of the interface that cannot go
     on base classes */

  virtual void* _replace_at(const void* p, const os_cursor& c) {
    if (!value) 
      make_value();
    void* oldvalue = c.retrieve();
    remove_inverse(oldvalue);
    insert_inverse(p);
    return os_rel_many::_replace_at(p, c);
    
  }
    
  virtual os_int32 _remove_first(const void* &v) {
    os_int32 r = 0;
    if (value && value->cardinality() > 0) {
      v = value->retrieve_first();
      if (v) {
	remove_inverse(v);
	os_rel_many::_remove_first(v);
	r = 1;
      }
    }
    return r;
  }

  os_int32 _remove_last(const void* &v) {
    os_int32 r = 0;
    if (value && value->cardinality() > 0) {
      v = value->retrieve_last();
      if (v) {
	remove_inverse(v);
	os_rel_many::_remove_last(v);
	r = 1;
      }
    }
    return r;
  }

  os_int32 _retrieve_first(const void*&v) const {
    if (!value)
      return 0;
    else
      return value->retrieve_first(v);
  }

    
  os_int32 _retrieve_last(const void*&v) const {
    if (!value)
      return 0;
    else
      return value->retrieve_last(v);
  }

  void _remove_at(os_unsigned_int32 position) {
    if (!value)
      make_value();
    valuetype* oldvalue = (valuetype*) _retrieve(position);
    remove_inverse(oldvalue);
    value->remove_at(position);
  }

  void* _replace_at(const void* p, os_unsigned_int32 position) {
    if (!value)
      make_value();
    valuetype* oldvalue = (valuetype*) _retrieve(position);
    remove_inverse(oldvalue);
    insert_inverse(p);
    return value->replace_at(p, position);
  }

  void _insert_after(const void* p, os_unsigned_int32 position) {
    if (!value)
      make_value();
    insert_inverse(p);
    value->insert_after(p, position);
  }

  void _insert_before(const void* p, os_unsigned_int32 position) {
    if (!value)
      make_value();
    insert_inverse(p);
    value->insert_before(p, position);
  }

  virtual void _insert(void const * v) {
	insert_inverse(v);
	os_rel_many::_insert((valuetype*)v);
  }
  virtual os_int32 _remove(void const * v) {
        os_int32 success = 0;
	remove_inverse(v);
	success = os_rel_many::_remove((valuetype*)v);
	return success;
  }
  virtual void _insert_first(void const * v) {
	insert_inverse(v);
	os_rel_many::_insert_first((valuetype*)v);
  }
  virtual void _insert_last(void const * v) {
	insert_inverse(v);
	os_rel_many::_insert_last((valuetype*)v);
  }
  virtual void _insert_before(void const * v, const os_cursor& c) {
	insert_inverse(v);
	os_rel_many::_insert_before((valuetype*)v, c);
  }
  virtual void _insert_after(void const * v, const os_cursor& c) {
	insert_inverse(v);
	os_rel_many::_insert_after((valuetype*)v, c);
  }
  virtual void _remove_at(const os_cursor& c) {
    void *v = c.retrieve();
    remove_inverse(v);
    os_rel_many::_remove_at(c);
  }

public:

  coll_type& getvalue() {return *(coll_type*)(void*)this;};

  _Rel_many(){}

  _Rel_many(_Rel_many& v) {_assign(v.getvalue());}

  ~_Rel_many() {
      _Rel_many_unset_all_inverses
	  (pcollptr(this),
	   backup(), 
	   (os_unsigned_int32) $inverse_attribute_offset,
	   (os_unsigned_int32) $inverse_is_single,
	   (void *)this,
	   (os_int32) $inverse_is_indexable,
	   (os_int32) $inverse_backptr_offset );
  }
  void set_inverse(void const * v)   { value->insert((valuetype*)v); }
  void unset_inverse(void const * v) { value->remove((valuetype*)v); }
  operator coll_type& () {return *(coll_type*)(void*)this;};
  coll_type const& getvalue() const {return *(coll_type const*)(void*)this;};
  operator coll_type const& () const {return *(coll_type const*)(void*)this;};
  coll_type& operator= (const os_Collection<valuetype*>& v) { _assign(*(os_collection*)(void*)&v); return this->getvalue(); };
  coll_type& operator= (const _Rel_many& v) { _assign(*(os_collection*)(void*)&(v.getvalue())); return this->getvalue(); };

public:
  /* Update protocol */
  void insert(valuetype* p) { _insert((void*)p) ; }
  os_int32 remove(valuetype* p) { return _remove((void*)p) ; }

  /* List-specific update protocol */
  void insert_first(valuetype* p) { _insert_first((void*)p) ; }
  void insert_last(valuetype* p) { _insert_last((void*)p) ; }

  os_int32 remove_first(valuetype* &p) {return _remove_first((const void* &) p);}
  os_int32 remove_last(valuetype* &p) {return _remove_last((const void* &)p);}
  
  /* for collections that don't contain null pointers */
  valuetype* remove_first() {void* p; return _remove_first(p) ? (valuetype*)p:(valuetype*)0;}
  valuetype* remove_last() {void* p; return _remove_last(p) ? (valuetype*)p:(valuetype*)0;}

  valuetype* pick() {return (valuetype*)os_collection::pick();}
  valuetype* only() {return (valuetype*)os_collection::only();}  

  os_Collection<valuetype*>& query(char* et, char* qs, os_database* db= 0,
			      char* fn=0, os_unsigned_int32 fl=0 ) const
    { return (os_Collection<valuetype*>&)os_collection::query(et,qs,db,fn,fl); }
  os_Collection<valuetype*>& query(const os_bound_query&q) const
    {return (os_Collection<valuetype*>&)os_collection::query(q);}
  valuetype* query_pick(char* et, char* qs, os_database* db= 0, char* fn= 0, 
		   os_unsigned_int32  fl= 0) const
    {return (valuetype*)os_collection::query_pick(et,qs,db,fn,fl);}
  valuetype* query_pick(const os_bound_query& q) const
    { return (valuetype*) os_collection::query_pick(q); }


  valuetype* retrieve_first() const { 
    return (valuetype*) os_collection::retrieve_first();}

  valuetype* retrieve_last() const {
    return (valuetype*) os_collection::retrieve_last();}

  valuetype* retrieve(os_unsigned_int32 position) {
    return (valuetype*)os_collection::retrieve(position);}

  valuetype* retrieve(const os_cursor&c) {
    return (valuetype*)os_collection::retrieve(c);}

  valuetype* replace_at(const void* p, const os_cursor& c) {
    return (valuetype*)os_collection::replace_at(p,c);}

  valuetype* replace_at(const void* p, os_unsigned_int32 position) {
    return (valuetype*)os_collection::replace_at(p,position);}

};


os_collection* _Rel_get_coll_base_noop (void *);

#ifndef _OS_PSE_COLL
#include <ostore/hdrend.hh>
#else
#include <os_pse/psecoll/hdrend.hh>
#endif
#endif

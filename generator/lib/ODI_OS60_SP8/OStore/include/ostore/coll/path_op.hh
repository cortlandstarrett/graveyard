/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef _Path_op_included
#define _Path_op_included
#if !defined(_OS_PSE_COLL)
#include <ostore/hdrstart.hh>
#else
#include <os_pse/psecoll/hdrstart.hh>
#endif

/* classes defined in this header are not used by PSE C++ */
#ifndef _OS_PSE_COLL 

class _Pset;
class os_dictionary;
class _Index_component;
class _Ipset;

class _Pvts;
typedef _Pset* _Pset_p;

#ifndef _ABSTRACT_COLLECTION
enum _Coll_clustering
{ _Coll_cluster_db, _Coll_cluster_seg, _Coll_cluster_config, _Coll_clustering_pad = 1<<30 };
#endif

/*----------------------------------------------------------------------*/

/* _Path_op */

enum _Path_op_id { DEREF, DESET, ID_VALUE, NOOP, OFFSET, OB_VALUE, _Path_op_id_pad = 1<<30 };
enum _New_path_op_id {
		   FN_DEREF = OB_VALUE+1, 
		   FN_OB_VALUE, FN_DESET, FN_DEREF_DM, FN_OBVAL_DM, 
		   FN_DESET_DM, FN_EMBEDDED_DM, FN_EMBEDDED_DESET_DM,
		   FN_OB_VALUE_DM, FN_DEREF_TERMINAL,
		   _New_pad_op_id_pad = 1<<30
		 };

/* For use in _Deref:: and _Deset::inverse_mapping. */
#define _TERMINAL_INDEX 0x80000000

class _OS_COLL_IMPORT _Path_op : public os_virtual_behavior64
{
  friend class os_index_path;
  friend class _Index_component;
  friend class _Index_tree;

/*......................................................................*/

/* representation */

private:
  os_int32 ordered;

protected:
  _Path_op_id name;
  os_int32 backptr_offset;
  char _os_pad_0[4];   /* 64-bit neutralization */

/*......................................................................*/


protected:
  /* Used in abbreviation of paths */
  _Path_op(_Path_op_id);

protected:

  enum { ignore_this_adjustment = 0x7fffffff };

  os_boolean ignore(os_int32 x) const
    { return (x == ignore_this_adjustment); }

public:

  virtual void NON_INLINE() const;

  _Path_op();
  _Path_op(const _Path_op&);
  virtual ~_Path_op();
  const _Path_op & operator =(const _Path_op&);

  os_int32 data_member_to_backptr() const
    { return backptr_offset; }

  _Path_op_id get_id() const { return name; }

  friend os_int32 compare(const _Path_op&, const _Path_op&);

  /* these are used in unsafe, ordered iteration */
  virtual void key_type_str(char *) const;
  virtual os_unsigned_int32 key_sizeof() const;

  virtual os_unsigned_int32 element_count() const;

/*......................................................................*/

/* _Path_op protocol */

  /* Forward */


  virtual void _interpret_singleton(void *v, void *&val) const = 0;
  virtual void interpret_ipset(_Ipset*) = 0;

  virtual void interpret(_Pset&) const = 0;
  virtual void interpret_and_disassociate(_Pset&,
					  const _Index_component*) const = 0;


  /* Backward */

  virtual void terpretni(_Pset&, os_dictionary const * const) const = 0;
  virtual void terpretni(_Pset&, os_dictionary const * const,
			 os_int32 /* os_collection::restriction */, void*,
			 os_collection*) const = 0;
  virtual void terpretni(_Pset&, os_dictionary const * const,
			 os_int32 /* os_collection::restriction */, void*,
			 os_int32 /* os_collection::restriction */, void*,
			 os_collection*) const = 0;
  virtual void* terpretni(void*, os_dictionary const * const, os_unsigned_int32&) const = 0;
  virtual void* terpretni_pick(os_dictionary*,
			       os_int32 /* os_collection::restriction */, void*,
			       os_collection*, os_unsigned_int32&) const = 0;
  virtual void* terpretni_pick(os_dictionary*,
			       os_int32 /* os_collection::restriction */, void*,
			       os_int32 /* os_collection::restriction */, void*,
			       os_collection*, os_unsigned_int32&) const = 0;


  /* Index maintenance */

  virtual os_dictionary* inverse_mapping(_Pset&, _Index_component*,
				    os_int32 index_options,
				    const void* where, _Coll_clustering, os_collection *) = 0;
  virtual void forget(_Pset&, _Index_component* const,
		      _Pset_p&, os_int32&, os_collection *) const = 0;
  virtual void remember(_Pset&, _Index_component* const,
			_Pset_p&, os_int32&, os_collection *) const = 0;


  /* Creation */

  virtual void LI_description(char *) const = 0;
  virtual void DML_description(char *) const = 0;


  /* Instantiation */

  virtual _Path_op* copy(os_cluster_with&) const = 0;
  /* needed for gcc. */
  virtual _Path_op* copy(os_cluster_with*) const;


  /* Evolution */

  virtual void reset_offset(const _Path_op&) = 0;


  /*
   *  Debugging
   */
  void _Path_op_basic_dump(void *) const;
  virtual void _Dump_path_op(void *) const = 0;

  /*
   * Function member support
   */
  virtual const char* get_class() const;
  virtual const char* get_member() const;
};


/*......................................................................*/

/* For cleanup within inverse_mapping in case of err_am_dup_key. */

class _Path_op_undo : public basic_undo
{
private:
  os_dictionary* inverse;

public:
  _Path_op_undo(os_dictionary*);
  ~_Path_op_undo();
};


/*----------------------------------------------------------------------*/

/* _Deref */

class _OS_COLL_IMPORT _Deref : public _Path_op
{
public:
  _Deref()
    : _Path_op(DEREF) {}

  virtual void key_type_str(char *) const;
  virtual os_unsigned_int32 key_sizeof() const;

  /* Forward */

  void _interpret_singleton(void *v, void *&val) const;

  void interpret_ipset(_Ipset* ip);

  void interpret(_Pset&) const;
  void interpret_and_disassociate(_Pset&, const _Index_component*) const;


  /* Backward */

  void terpretni(_Pset&, os_dictionary const * const) const;
  void terpretni(_Pset&, os_dictionary const * const,
		 os_int32 /* os_collection::restriction */, void*, os_collection*)
		 const;
  void terpretni(_Pset&, os_dictionary const * const,
		 os_int32 /* os_collection::restriction */, void*,
		 os_int32 /* os_collection::restriction */, void*,
		 os_collection*) const;
  void* terpretni(void*, os_dictionary const * const, os_unsigned_int32&) const;
  void* terpretni_pick(os_dictionary*, os_int32 /* os_collection::restriction */, void*,
		       os_collection*, os_unsigned_int32&) const;
  void* terpretni_pick(os_dictionary*,
		       os_int32 /* os_collection::restriction */, void*,
		       os_int32 /* os_collection::restriction */, void*,
		       os_collection*, os_unsigned_int32&) const;


  /* Index maintenance */

  os_dictionary* inverse_mapping(_Pset&,
			    _Index_component*,
			    os_int32 index_options,
			    const void* where, _Coll_clustering, os_collection *);
  void forget(_Pset&, _Index_component* const,
	      _Pset_p&, os_int32&, os_collection *) const;
  void remember(_Pset&, _Index_component* const,
		_Pset_p&, os_int32&, os_collection *) const;


  /* Creation */

  void LI_description(char *) const;
  void DML_description(char *) const;


  /* Instantiation */

  _Path_op* copy(os_cluster_with&) const;


  /* Evolution */

  void reset_offset(const _Path_op&);

  /*
   *  Debugging
   */
  virtual void _Dump_path_op(void *) const;

  static os_typespec* get_os_typespec();

};



/*----------------------------------------------------------------------*/

/* _Deset */

class _OS_COLL_IMPORT _Deset : public _Path_op
{
public:
  _Deset()
    : _Path_op(DESET) {}


  virtual void key_type_str(char *) const;
  virtual os_unsigned_int32 key_sizeof() const;

  /* Forward */

  void _interpret_singleton(void *v, void *&val) const;

  void interpret_ipset(_Ipset* ip);

  void interpret(_Pset&) const;
  void interpret_and_disassociate(_Pset&, const _Index_component*) const;


  /* Backward */

  void terpretni(_Pset&, os_dictionary const * const) const;
  void terpretni(_Pset&, os_dictionary const * const,
		 os_int32 /* os_collection::restriction */, void*, os_collection*)
		 const;
  void terpretni(_Pset&, os_dictionary const * const,
		 os_int32 /* os_collection::restriction */, void*,
		 os_int32 /* os_collection::restriction */, void*,
		 os_collection*) const;
  void* terpretni(void*, os_dictionary const * const, os_unsigned_int32&) const;
  void* terpretni_pick(os_dictionary*, os_int32 /* os_collection::restriction */, void*,
		       os_collection*, os_unsigned_int32&) const;
  void* terpretni_pick(os_dictionary*,
		       os_int32 /* os_collection::restriction */, void*,
		       os_int32 /* os_collection::restriction */, void*,
		       os_collection*, os_unsigned_int32&) const;


  /* Index maintenance */

  os_dictionary* inverse_mapping(_Pset&, _Index_component*,
			    os_int32 index_options, 
			    const void* where, _Coll_clustering, os_collection *);
  void forget(_Pset&, _Index_component* const,
	      _Pset_p&, os_int32&, os_collection *) const;
  void remember(_Pset&, _Index_component* const,
		_Pset_p&, os_int32&, os_collection *) const;


  /* Creation */

  void LI_description(char *) const;
  void DML_description(char *) const;


  /* Instantiation */

  _Path_op* copy(os_cluster_with&) const;


  /* Evolution */

  void reset_offset(const _Path_op&);

  /*
   *  Debugging
   */
  virtual void _Dump_path_op(void *) const;

  static os_typespec* get_os_typespec();
};


/*----------------------------------------------------------------------*/

/* _Id_value */

class _OS_COLL_IMPORT _Id_value : public _Path_op
{
public:
  _Id_value()
    : _Path_op(ID_VALUE)
      {}


  /* Forward */

  void _interpret_singleton(void *v, void *&val) const;

  void interpret_ipset(_Ipset* ip);

  void interpret(_Pset&) const;
  void interpret_and_disassociate(_Pset&, const _Index_component*) const;


  /* Backward */

  void terpretni(_Pset&, os_dictionary const * const) const;
  void terpretni(_Pset&, os_dictionary const * const,
		 os_int32 /* os_collection::restriction */, void*, os_collection*)
		 const;
  void terpretni(_Pset&, os_dictionary const * const,
		 os_int32 /* os_collection::restriction */, void*,
		 os_int32 /* os_collection::restriction */, void*,
		 os_collection*) const;
  void* terpretni(void*, os_dictionary const * const, os_unsigned_int32&) const;
  void* terpretni_pick(os_dictionary*, os_int32 /* os_collection::restriction */, void*,
		       os_collection*, os_unsigned_int32&) const;
  void* terpretni_pick(os_dictionary*,
		       os_int32 /* os_collection::restriction */, void*,
		       os_int32 /* os_collection::restriction */, void*,
		       os_collection*, os_unsigned_int32&) const;


  /* Index maintenance */

  os_dictionary* inverse_mapping(_Pset&, _Index_component*,
			    os_int32 index_options, 
			    const void* where, _Coll_clustering, os_collection *);
  void forget(_Pset&, _Index_component* const,
	      _Pset_p&, os_int32&, os_collection *) const;
  void remember(_Pset&, _Index_component* const,
		_Pset_p&, os_int32&, os_collection *) const;


  /* Creation */

  void LI_description(char *) const;
  void DML_description(char *) const;


  /* Instantiation */

  _Path_op* copy(os_cluster_with&) const;


  /* Evolution */

  void reset_offset(const _Path_op&);

  /*
   *  Debugging
   */
  virtual void _Dump_path_op(void *) const;

  static os_typespec* get_os_typespec();
};


/*----------------------------------------------------------------------*/

/* _Noop */

class _OS_COLL_IMPORT _Noop : public _Path_op
{
public:
  _Noop()
    : _Path_op(NOOP) {}


  /* Forward */

  void _interpret_singleton(void *v, void *&val) const;

  void interpret_ipset(_Ipset*) {};

  void interpret(_Pset&) const {}
  void interpret_and_disassociate(_Pset&, const _Index_component*) const {}


  /* Backward */

  void terpretni(_Pset&, os_dictionary const * const) const;
  void terpretni(_Pset&, os_dictionary const * const,
		 os_int32 /* os_collection::restriction */, void*, os_collection*)
		 const;
  void terpretni(_Pset&, os_dictionary const * const,
		 os_int32 /* os_collection::restriction */, void*,
		 os_int32 /* os_collection::restriction */, void*,
		 os_collection*) const;
  void* terpretni(void*, os_dictionary const * const, os_unsigned_int32&) const;
  void* terpretni_pick(os_dictionary*, os_int32 /* os_collection::restriction */, void*,
		       os_collection*, os_unsigned_int32&) const;
  void* terpretni_pick(os_dictionary*,
		       os_int32 /* os_collection::restriction */, void*,
		       os_int32 /* os_collection::restriction */, void*,
		       os_collection*, os_unsigned_int32&) const;


  /* Index maintenance */

  os_dictionary* inverse_mapping(_Pset&, _Index_component*,
			    os_int32, 
			    const void* where, _Coll_clustering, os_collection *);
  void forget(_Pset&, _Index_component* const,
	      _Pset_p&, os_int32&, os_collection *) const;
  void remember(_Pset&, _Index_component* const,
		_Pset_p&, os_int32&, os_collection *) const;


  /* Creation */

  void LI_description(char *) const;
  void DML_description(char *) const;


  /* Instantiation */

  _Path_op* copy(os_cluster_with&) const;


  /* Evolution */

  void reset_offset(const _Path_op&);

  /*
   *  Debugging
   */
  virtual void _Dump_path_op(void *) const;

  static os_typespec* get_os_typespec();
};

/*----------------------------------------------------------------------*/

/* _Offset */

class _OS_COLL_IMPORT _Offset : public _Path_op
{
public:
  os_int32 amount;
  char _os_pad_0[4];     /* 64-bit neutralization */ 

  _Offset(os_int32 o, os_int32 b)
    : _Path_op(OFFSET), amount(o)
    { backptr_offset = b; }


  /* Forward */

  void _interpret_singleton(void *v, void *&val) const;

  void interpret_ipset(_Ipset* ip);

  void interpret(_Pset& p) const;
  void interpret_and_disassociate(_Pset& p, const _Index_component*) const;


  /* Backward */

  void terpretni(_Pset&, os_dictionary const * const) const;
  void terpretni(_Pset&, os_dictionary const * const,
		 os_int32 /* os_collection::restriction */, void*, os_collection*)
		 const;
  void terpretni(_Pset&, os_dictionary const * const,
		 os_int32 /* os_collection::restriction */, void*,
		 os_int32 /* os_collection::restriction */, void*,
		 os_collection*) const;
  void* terpretni(void*, os_dictionary const * const, os_unsigned_int32&) const;
  void* terpretni_pick(os_dictionary*, os_int32 /* os_collection::restriction */, void*,
		       os_collection*, os_unsigned_int32&) const;
  void* terpretni_pick(os_dictionary*,
		       os_int32 /* os_collection::restriction */, void*,
		       os_int32 /* os_collection::restriction */, void*,
		       os_collection*, os_unsigned_int32&) const;


  /* Index maintenance */

  os_dictionary* inverse_mapping(_Pset&, _Index_component*,
			    os_int32 index_options,
			    const void* where, _Coll_clustering, os_collection *);
  void forget(_Pset&, _Index_component* const,
	      _Pset_p&, os_int32&, os_collection *) const;
  void remember(_Pset&, _Index_component* const,
		_Pset_p&, os_int32&, os_collection *) const;


  /* Creation */

  void LI_description(char *) const;
  void DML_description(char *) const;


  /* Instantiation */

  _Path_op* copy(os_cluster_with&) const;


  /* Evolution */

  void reset_offset(const _Path_op&);

  /*
   *  Debugging
   */
  virtual void _Dump_path_op(void *) const;

  static os_typespec* get_os_typespec();
};



/*----------------------------------------------------------------------*/

/* _Ob_value */


class _OS_COLL_IMPORT _Ob_value : public _Path_op
{
  os_soft_pointer<char> key_type;
  os_int32 array_size;
  os_int32 key_size;
  char _os_pad_0[4];   /* 64-bit neutralization */

public:
  _Ob_value(const char*, os_int32 array_size, os_int32 sizeof_key);
  ~_Ob_value();

  virtual void key_type_str(char *) const;
  virtual os_unsigned_int32 key_sizeof() const;

  virtual os_unsigned_int32 element_count() const;

  /* Forward */

  void _interpret_singleton(void *v, void *&val) const;

  void interpret_ipset(_Ipset* ip);

  void interpret(_Pset&) const;
  void interpret_and_disassociate(_Pset&, const _Index_component*) const;


  /* Backward */

  void terpretni(_Pset&, os_dictionary const * const) const;
  void terpretni(_Pset&, os_dictionary const * const,
		 os_int32 /* os_collection::restriction */, void*, os_collection*)
		 const;
  void terpretni(_Pset&, os_dictionary const * const,
		 os_int32 /* os_collection::restriction */, void*,
		 os_int32 /* os_collection::restriction */, void*,
		 os_collection*) const;
  void* terpretni(void*, os_dictionary const * const, os_unsigned_int32&) const;
  void* terpretni_pick(os_dictionary*, os_int32 /* os_collection::restriction */, void*,
		       os_collection*, os_unsigned_int32&) const;
  void* terpretni_pick(os_dictionary*,
		       os_int32 /* os_collection::restriction */, void*,
		       os_int32 /* os_collection::restriction */, void*,
		       os_collection*, os_unsigned_int32&) const;


  /* Index maintenance */

  os_dictionary* inverse_mapping(_Pset&,
			   _Index_component*,
			    os_int32 index_options,
			    const void* where, _Coll_clustering, os_collection *);
  void forget(_Pset&, _Index_component* const,
	      _Pset_p&, os_int32&, os_collection *) const;
  void remember(_Pset&, _Index_component* const,
		_Pset_p&, os_int32&, os_collection *) const;


  /* Creation */

  void LI_description(char *) const;
  void DML_description(char *) const;

  /* Instantiation */

  _Path_op* copy(os_cluster_with&) const;


  /* Evolution */

  void reset_offset(const _Path_op&);

  /*
   *  Debugging
   */
  virtual void _Dump_path_op(void *) const;

  static os_typespec* get_os_typespec();
};


/*----------------------------------------------------------------------*/
/*----------------------------------------------------------------------*/

class os_function_info;

class _OS_COLL_IMPORT _Fn_Pathop : public _Path_op {
protected:
  os_soft_pointer<os_function_info> _fn;
  os_int32 _this_ptr_adjustment;

public:

  virtual const char* get_class() const;
  virtual const char* get_member() const;
  os_function_info* get_function_info() const { return _fn; }
  os_int32 get_this_adjustment(void* obj) const;
  os_int32 get_offset_to_member_block(void* obj) const;

  virtual void get_value(void* obj, void *& val) const = 0;
  

  _Fn_Pathop(_Path_op_id p) : _Path_op(p) {}
  ~_Fn_Pathop() {}

public:

  /* Backward */

  void terpretni(_Pset&, os_dictionary const * const) const;
  void terpretni(_Pset&, os_dictionary const * const,
		 os_int32 /* os_collection::restriction */, void*, 
		 os_collection*) const;
  void terpretni(_Pset&, os_dictionary const * const,
		 os_int32 /* os_collection::restriction */, void*,
		 os_int32 /* os_collection::restriction */, void*,
		 os_collection*) const;
  void* terpretni(void*, os_dictionary const * const, os_unsigned_int32&) const;
  void* terpretni_pick(os_dictionary*, os_int32 /* os_collection::restriction */, 
		       void*,
		       os_collection*, os_unsigned_int32&) const;
  void* terpretni_pick(os_dictionary*,
		       os_int32 /* os_collection::restriction */, void*,
		       os_int32 /* os_collection::restriction */, void*,
		       os_collection*, os_unsigned_int32&) const;


};

class _OS_COLL_IMPORT _Fn_Deref : public _Fn_Pathop {

private:

  void init(const os_function_info* fn,
	    os_unsigned_int32 key_size, os_int32 this_adj,
	    os_boolean virtual_base);

protected:

  os_unsigned_int32 _key_size;  /* the size of the thing being pointed-to.
				   This is needed for paths terminating in
				   fn_deref's (_Fn_Deref_Terminal)
				   */
  char _os_pad_0[4];   /* 64-bit neutralization */ 

  /* constructor used by subclasses */
  _Fn_Deref(const os_function_info* fn, os_unsigned_int32 key_size,
	    _Path_op_id pid);

public:

  virtual void get_value(void* obj, void *& val) const;

public:

  /* this_adj is ignored 
     if the class type in fn is SOM OR virtual_base is TRUE
     */

  _Fn_Deref(const os_function_info* fn, os_unsigned_int32 key_size,
	    os_int32 this_adj = 0, os_boolean virtual_base = 0);
  ~_Fn_Deref();

  virtual void key_type_str(char *) const;
  virtual os_unsigned_int32 key_sizeof() const;

  /* Forward */

  void _interpret_singleton(void *v, void *&val) const;

  void interpret_ipset(_Ipset* ip);

  void interpret(_Pset&) const;
  void interpret_and_disassociate(_Pset&, const _Index_component*) const;


  /* Index maintenance */

  os_dictionary* inverse_mapping(_Pset&,
			    _Index_component*,
			    os_int32 index_options,
			    const void* where, _Coll_clustering, os_collection *);
  void forget(_Pset&, _Index_component* const,
	      _Pset_p&, os_int32&, os_collection *) const;
  void remember(_Pset&, _Index_component* const,
		_Pset_p&, os_int32&, os_collection *) const;


  /* Creation */

  void LI_description(char *) const;
  void DML_description(char *) const;


  /* Instantiation */

  _Path_op* copy(os_cluster_with&) const;


  /* Evolution */

  void reset_offset(const _Path_op&);

  /*
   *  Debugging
   */
  virtual void _Dump_path_op(void *) const;

  static os_typespec* get_os_typespec();

};


/* this is for paths that end in a dereferenced function that returns a 
   pointer
*/

class _OS_COLL_IMPORT _Fn_Deref_Terminal : public _Fn_Deref {
public:
  _Fn_Deref_Terminal(os_function_info* fn, os_unsigned_int32 key_size,
		     os_int32 this_adj, os_boolean virtual_base);
  ~_Fn_Deref_Terminal() {}

  virtual void key_type_str(char *) const;
  virtual os_unsigned_int32 key_sizeof() const;
  virtual void LI_description(char *) const;
  virtual void DML_description(char *) const;
  _Path_op* copy(os_cluster_with&) const;
  static os_typespec* get_os_typespec();
};


class _OS_COLL_IMPORT _Fn_Deref_DM : public _Fn_Deref {
private:

   void init(const char* cls, const char* mem,
	     os_int32 DM_offset_int_class);

protected:
  os_soft_pointer<char> _class;
  os_soft_pointer<char> _member;
  os_int32 _DM_offset_in_class;
  char _os_pad_0[4];   /* 64-bit neutralization */
  
  /* constructor used by subclasses */
  _Fn_Deref_DM(const char* cls, const char* mem,
	       const os_function_info* bpfn, os_unsigned_int32 key_size,
	       os_int32 DM_offset_in_class,
	       _Path_op_id pid);

public:

  _Fn_Deref_DM(const char* cls, const char* mem,
	       const os_function_info* bpfn,
	       os_unsigned_int32 key_size, os_int32 DM_offset_in_class);
  ~_Fn_Deref_DM();

  virtual const char* get_class() const;
  virtual const char* get_member() const;
  virtual void get_value(void* obj, void *& val) const;
  _Path_op* copy(os_cluster_with&) const;
  static os_typespec* get_os_typespec();
};

class _OS_COLL_IMPORT _Fn_Embedded_DM : public _Fn_Deref_DM {

public:

  _Fn_Embedded_DM(const char* cls, const char* mem,
		  const os_function_info* bpfn, os_unsigned_int32 key_size,
		  os_int32 DM_offset_in_class) 
  : _Fn_Deref_DM(cls,mem,bpfn,key_size,DM_offset_in_class, 
		 (_Path_op_id)FN_EMBEDDED_DM) {}
  
  ~_Fn_Embedded_DM(){}

  virtual void get_value(void* obj, void *& val) const;
  static os_typespec* get_os_typespec();
  virtual os_unsigned_int32 key_sizeof() const;
  _Path_op* copy(os_cluster_with&) const;
};


/*----------------------------------------------------------------------*/

class _OS_COLL_IMPORT _Fn_Ob_value : public _Fn_Pathop
{
private:

  void init(const os_function_info* fn, os_int32 array_size,
	    const char* key_type, os_int32 this_adj, 
	    os_boolean virtual_base);

protected:
  os_soft_pointer<char> _key_type;
  os_int32 _array_size;
  
  _Fn_Ob_value(const os_function_info* fn, 
	       os_int32 array_size, const char* key_type,
	       _Path_op_id pid);

public:

  virtual void get_value(void* obj, void *& val) const;

public:
  /* this_adj is ignored 
     if the class type in fn is SOM OR virtual_base is TRUE
     */

  _Fn_Ob_value(const os_function_info* fn, os_int32 array_size,
	       os_int32 this_adj=0, os_boolean virtual_base = 0);
  ~_Fn_Ob_value();

  virtual void key_type_str(char *) const;
  virtual os_unsigned_int32 key_sizeof() const;


  /* Forward */

  void _interpret_singleton(void *v, void *&val) const;

  void interpret_ipset(_Ipset* ip);

  void interpret(_Pset&) const;
  void interpret_and_disassociate(_Pset&, const _Index_component*) const;


  /* Backward */

  void terpretni(_Pset&, os_dictionary const * const) const;
  void terpretni(_Pset&, os_dictionary const * const,
		 os_int32 /* os_collection::restriction */, void*, 
		 os_collection*) const;
  void terpretni(_Pset&, os_dictionary const * const,
		 os_int32 /* os_collection::restriction */, void*,
		 os_int32 /* os_collection::restriction */, void*,
		 os_collection*) const;
  void* terpretni(void*, os_dictionary const * const, os_unsigned_int32&) const;
  void* terpretni_pick(os_dictionary*, os_int32 /* os_collection::restriction */, 
		       void*,
		       os_collection*, os_unsigned_int32&) const;
  void* terpretni_pick(os_dictionary*,
		       os_int32 /* os_collection::restriction */, void*,
		       os_int32 /* os_collection::restriction */, void*,
		       os_collection*, os_unsigned_int32&) const;

  /* Index maintenance */

  os_dictionary* inverse_mapping(_Pset&,
			   _Index_component*,
			    os_int32 index_options,
			    const void* where, _Coll_clustering, os_collection *);
  void forget(_Pset&, _Index_component* const,
	      _Pset_p&, os_int32&, os_collection *) const;
  void remember(_Pset&, _Index_component* const,
		_Pset_p&, os_int32&, os_collection *) const;


  /* Creation */

  void LI_description(char *) const;
  void DML_description(char *) const;


  /* Instantiation */

  _Path_op* copy(os_cluster_with&) const;


  /* Evolution */

  void reset_offset(const _Path_op&);

  /*
   *  Debugging
   */
  virtual void _Dump_path_op(void *) const;

  static os_typespec* get_os_typespec();

};


class _OS_COLL_IMPORT _Fn_Ob_value_DM : public _Fn_Ob_value {
private:

  os_soft_pointer<char> _class;
  os_soft_pointer<char> _member;
  os_int32 _DM_offset_in_class;
  os_unsigned_int32 _key_size;

public:

  _Fn_Ob_value_DM(const char* cls, const char* mem,
		  const char* type,
		  const os_function_info* bpfn,
		  os_unsigned_int32 _key_size,
		  os_int32 array_size, os_int32 DM_offset_in_class);
  ~_Fn_Ob_value_DM();

  virtual const char* get_class() const;
  virtual const char* get_member() const;
  virtual void get_value(void* obj, void *& val) const;
  _Path_op* copy(os_cluster_with&) const;
  virtual os_unsigned_int32 key_sizeof() const;
  static os_typespec* get_os_typespec();
};

/*----------------------------------------------------------------------*/

/* _Fn_Deset */

class _OS_DLLIMPORT(_OS_COLL) _Fn_Deset : public _Fn_Pathop
{
private:

  void init(const os_function_info* fn, 
	    os_int32 this_adj, os_boolean virtual_base);

protected:

  os_unsigned_int32 _flags; /* we have to remember if we are indexing the 
			       ptr or the thing being pointed-to
			       */
  char _os_pad_0[4];   /* 64-bit neutralization */
  /* constructor used by subclasses */

  _Fn_Deset(const os_function_info* fn, _Path_op_id pid);

public:

  virtual void get_value(void* obj, void *& val) const;
  os_unsigned_int32 get_flags() const { return _flags; }

public:

  _Fn_Deset(const os_function_info* fn, os_int32 this_adj = 0, 
	    os_boolean virtual_base = 0);
  ~_Fn_Deset();
       

  virtual void  key_type_str(char *) const;
  virtual os_unsigned_int32 key_sizeof() const;

  /* Forward */

  void _interpret_singleton(void *v, void *&val) const;

  void interpret_ipset(_Ipset* ip);

  void interpret(_Pset&) const;
  void interpret_and_disassociate(_Pset&, const _Index_component*) const;

  void terpretni(_Pset&, os_dictionary const * const) const;
  void terpretni(_Pset&, os_dictionary const * const,
		 os_int32 /* os_collection::restriction */, void*, 
		 os_collection*) const;
  void terpretni(_Pset&, os_dictionary const * const,
		 os_int32 /* os_collection::restriction */, void*,
		 os_int32 /* os_collection::restriction */, void*,
		 os_collection*) const;
  void* terpretni(void*, os_dictionary const * const, os_unsigned_int32&) const;
  
  /* Index maintenance */

  os_dictionary* inverse_mapping(_Pset&, _Index_component*,
			    os_int32 index_options, 
			    const void* where, _Coll_clustering, os_collection *);
  void forget(_Pset&, _Index_component* const,
	      _Pset_p&, os_int32&, os_collection *) const;
  void remember(_Pset&, _Index_component* const,
		_Pset_p&, os_int32&, os_collection *) const;


  /* Creation */

  void LI_description(char *) const;
  void DML_description(char *) const;


  /* Instantiation */

  _Path_op* copy(os_cluster_with&) const;


  /* Evolution */

  void reset_offset(const _Path_op&);

  /*
   *  Debugging
   */
  virtual void _Dump_path_op(void *) const;

  static os_typespec* get_os_typespec();

};

/* ---------------------------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

class _OS_COLL_IMPORT _Fn_Deset_DM : public _Fn_Deset {
private:

  void init(const char* cls, const char* mem,
	    os_int32 DM_offset_in_class);

protected:

  os_soft_pointer<char> _class;
  os_soft_pointer<char> _member;
  os_int32 _DM_offset_in_class;
  char _os_pad_0[4];   /* 64-bit neutralization */

  _Fn_Deset_DM(const char* cls, const char* mem,
	       const os_function_info* bpfn,
	       os_int32 DM_offset_in_class, _Path_op_id pid);

public:
  _Fn_Deset_DM(const char* cls, const char* mem,
	       const os_function_info* bpfn, os_int32 DM_offset_in_class);
  ~_Fn_Deset_DM();

  virtual const char* get_class() const;
  virtual const char* get_member() const;
  virtual void get_value(void* obj, void *& val) const;
  _Path_op* copy(os_cluster_with&) const;
  static os_typespec* get_os_typespec();
};

/* ---------------------------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

class _OS_COLL_IMPORT _Fn_Embedded_Deset_DM : public _Fn_Deset_DM {

public:

  _Fn_Embedded_Deset_DM(const char* cls, const char* mem,
			const os_function_info* bpfn,
			os_int32 DM_offset_in_class) 
  : _Fn_Deset_DM(cls,mem,bpfn,DM_offset_in_class, 
		 (_Path_op_id)FN_EMBEDDED_DESET_DM) {}
  
  ~_Fn_Embedded_Deset_DM(){}

  virtual void get_value(void* obj, void *& val) const;
  static os_typespec* get_os_typespec();
  void LI_description(char *) const;
};

#endif // not PSE C++

#if !defined(_OS_PSE_COLL)
#include <ostore/hdrend.hh>
#else
#include <os_pse/psecoll/hdrend.hh>
#endif
#endif

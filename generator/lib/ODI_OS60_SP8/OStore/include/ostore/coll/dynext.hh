/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef _OS_PSE_COLL
#include <ostore/coll/usercoll.hh>
#else
#include <os_pse/coll/usercoll.hh>
_OS_BEGIN_NAMESPACE(os_pse)
#endif

class _Basic_type;

class _OS_COLL_IMPORT os_dynamic_extent : public os_coll_user_ext_ix {
  private:
    
    char * type_name;
    os_database * db;
    os_segment * seg_req_p;
    os_boolean include_subclasses;

    	
  public:

    /* -------------------------------------------------------------------- */
    /* Creation                                                             */
    /* -------------------------------------------------------------------- */

   enum dynext_seg_enum {
     all_segments = 0,
     of_segment = 1
   };
   os_dynamic_extent(os_database * db1,
                     os_typespec * typespec,
                     os_boolean do_include_subclasses=0);

   os_dynamic_extent(os_typespec *typespec,
                     os_boolean of_seg,
                     os_boolean do_include_subclasses=0);

   os_dynamic_extent(os_database * db1,
                     os_typespec * typespec,
                     os_segment * seg,
                     os_boolean do_include_subclasses=0);
   
   virtual ~os_dynamic_extent();	 

  protected:
     
    /* -------------------------------------------------------------------- */
    /* cursor protocol                                                      */
    /* -------------------------------------------------------------------- */
  
    virtual os_int32 _first(os_cursor&, void* &) const;
    virtual os_int32 _next(os_cursor&, void* &) const;
    virtual os_unsigned_int32 _cardinality() const;     

    protected:

     
    /* -------------------------------------------------------------------- */
    /* for supporting indexes                                               */
    /* -------------------------------------------------------------------- */
  
    virtual void _insert(const void*);
    virtual os_int32 _remove(const void*);  
      
  protected:
  
    /* -------------------------------------------------------------------- */
    /* other odds and ends                                                  */
    /* -------------------------------------------------------------------- */
  
    os_address_space_marker * _set_segment( os_coll_user_ext_cursor& crs) const;
    os_int32 _find_object( os_coll_user_ext_cursor& crs ,void *& v) const; 

    os_boolean is_instance_of_subclass(const _Basic_type * bt) const;

public:
    static os_typespec* get_os_typespec();  

  };


#ifdef _OS_PSE_COLL
_OS_END_NAMESPACE
#endif





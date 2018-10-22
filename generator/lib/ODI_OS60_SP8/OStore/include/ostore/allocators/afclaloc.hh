/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/



#ifndef __OS_CL_ALLOCATOR__
#define __OS_CL_ALLOCATOR__

#include <ostore/portypes.hh>
#include <ostore/os_int64.hh>
#include <ostore/ostore.hh>
#include <ostore/coll.hh>
#include <ostore/allocators/afxalloc.hh>
#include <ostore/allocators/afitratr.hh>
#include <ostore/allocators/afttrait.hh>
#include <ostore/allocators/afmisc.hh>

/******************************************************************************
Class Name      : os_cluster_allocator
Description     : this implements extended allocator interface
Remarks         : 
******************************************************************************/



/****************************************************************************/
class _OS_DLLIMPORT(_OS_ALLOC) os_cluster_allocator :public os_extended_allocator
{
public: 

  typedef size_t    size_type;
  typedef ptrdiff_t difference_type;
  
  os_cluster_allocator() ;

  os_cluster_allocator( const os_cluster_allocator& ) ;

  os_cluster_allocator( os_cluster* p_cluster ) ;

  os_cluster_allocator( const os_string& database_str,
			os_unsigned_int32 clusters = MAX_CLUSTERS,
			os_unsigned_int32 cluster_size = MAX_CLUSTER_SIZE,
			os_unsigned_int32 segments = MAX_SEGMENTS) ;

  os_cluster_allocator( os_database * db,
			os_unsigned_int32 clusters = MAX_CLUSTERS,
			os_unsigned_int32 cluster_size = MAX_CLUSTER_SIZE,
			os_unsigned_int32 segments = MAX_SEGMENTS) ;

  ~os_cluster_allocator() ;
  
  os_boolean is_persistent() ; /* override */

  void insert_traits(os_Trait_List *);

  os_Trait_List * setup_trait_list(os_unsigned_int32 clusters,
				   os_unsigned_int32 cluster_size,
				   os_unsigned_int32 segments) ;
  /* get iterator for traits */
  os_trait_iterator* get_traits() const; /* override */

  /* set a trait */
  os_boolean set_trait( os_trait* ) ; /* override */

  /* get a trait by name */
  os_trait* get_trait( os_string trait_name ) const ; /* override */

  /* initialize the state if any */
  os_boolean initialize() ; /* override */

  /* clean the state if any */
  os_boolean clean() ; /* override */
  
  static os_typespec* get_os_typespec();

  friend os_boolean operator==( const os_cluster_allocator& left_x_alloc, 
				const os_cluster_allocator& right_x_alloc ) ;

  friend os_boolean operator!=( const os_cluster_allocator& left_x_alloc, 
				const os_cluster_allocator& right_x_alloc ) ;
  
public: /* interface implementation */
    
  void* allocate_type( size_type object_size, 
		       os_typespec* type_spec,
		       const void* hint = 0 ) ;

  void* allocate_type( size_type object_size, 
		       os_typespec* type_spec,
		       size_type number_elements, 
		       const void* hint = 0 ) ;

  os_unsigned_int32 max_size() const ;

  os_unsigned_int32 get_segment_number() const;

  os_Array<os_unsigned_int32 *> * get_cluster_array() const;

  os_extended_allocator* clone() ;

  void add_to_cluster_list(os_cluster *);

private: /* embedded data */

  void InitAllocator (os_database *);

  void SetupAllocator (os_database *,
		       os_unsigned_int32,
		       os_unsigned_int32,
		       os_unsigned_int32);

  os_string           m_database_path ;

  /* segment/clusters managed by an allocator */
  SegmentClusterList  af_SegClusterList; 

  /* traits */
  _ODI_AF_Map< os_trait >* m_p_traits ;
} ;

os_boolean operator==( const os_cluster_allocator& left_x_alloc, 
                       const os_cluster_allocator& right_x_alloc ) ;
os_boolean operator!=( const os_cluster_allocator& left_x_alloc, 
                       const os_cluster_allocator& right_x_alloc ) ;

#endif

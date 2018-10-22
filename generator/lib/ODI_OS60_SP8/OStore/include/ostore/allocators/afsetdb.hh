/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef _OS_SET_DB_HH
#define _OS_SET_DB_HH 1

#include <ostore/portypes.hh>
#include <ostore/allocators/afalcreg.hh>
#include <ostore/allocators/afruleng.hh>


class os_set_db
{
public:
  static os_boolean  set_rule_db( os_string db_path, os_string root_name  ) 
    {
      os_boolean res_err  = 0;
      os_database* rul_db  = 0;
      TIX_HANDLE( err_database_not_found )
	{
	  rul_db = os_database::lookup( db_path ) ;
	}
      TIX_EXCEPTION
	{
	  return res_err ;
	}
      TIX_END_HANDLE 
        rul_db = os_database::open( db_path,0,0664 ) ;
      os_database_root* check_rul_root = rul_db->find_root( root_name ) ;
      if( ! check_rul_root)
	{
	  rul_db->close() ;
	  return res_err ;
	}
      else
        {
	  os_rule_engine::rule_db( db_path, root_name ) ; 
	  res_err = 1 ;
	}

      rul_db->close() ;

      return res_err ;

    }


  static os_boolean set_alloc_db( os_string db_path, os_string root_name ) 
    {
      os_boolean res_err = 0 ;
      os_database* reg_db  = 0;

      TIX_HANDLE( err_database_not_found )
	{
	  reg_db = os_database::lookup( db_path ) ;
	}
      TIX_EXCEPTION
	{
	  return res_err ;
	}
      TIX_END_HANDLE 
        reg_db = os_database::open( db_path,0,0664 ) ;
      os_database_root* check_alloc_root = reg_db->find_root( root_name ) ;
      if( ! check_alloc_root)
	{
	  reg_db->close() ;
	  return res_err ;
	}
      else
	{
	  os_allocator_registry::alloc_db( db_path, root_name ) ;
	  res_err = 1 ;
	} 
      reg_db->close() ;

      return res_err ;
    }

} ;


#endif

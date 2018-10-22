/*========================================================================
 *
 * File:      $RCSfile: list.h,v $
 * Version:   $Revision: 1.10 $
 * Modified:  $Date: 2013/01/10 23:41:53 $
 *
 * (c) Copyright 2005-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#ifndef _included_class_list_
#define _included_class_list_ 1

#include <mc_dbms/mc_dbms_types.h>
#include <mc_dbms/collection.h>
#include <mc_dbms/database.h>


class mc_dbms_database;
class mc_dbms_typespec;

template <class E>
class mc_dbms_List : public mc_dbms_Collection<E>
{
public:
    mc_dbms_List(dbms_unsigned_int32 sz = 0, dbms_unsigned_int32 behavior = 0) 
	       : mc_dbms_Collection<E>('L') { }
	
	 mc_dbms_List(const mc_dbms_List<E>&c) : mc_dbms_Collection<E>('L') { }
	
	 mc_dbms_List(const mc_dbms_Collection<E>&c) : mc_dbms_Collection<E>('L') { }
	
	virtual ~mc_dbms_List() { }
	
  	// create functions are provided for backward compatibility
  	static mc_dbms_List<E> &create(mc_dbms_database* db, dbms_unsigned_int32 behavior = 0,
			    			dbms_int32 expected_size = 0)
    {
		// Implement in terms of our overloaded new operators.
		mc_dbms_List<E>* result = new (db, mc_dbms_List::get_mc_dbms_typespec()) mc_dbms_List<E>;
        return *result;
    }
   
  	static mc_dbms_typespec* get_mc_dbms_typespec() {
  		return mc_dbms_collection::get_list_typespec();
  	}
};

#endif /* _included_class_list_ */

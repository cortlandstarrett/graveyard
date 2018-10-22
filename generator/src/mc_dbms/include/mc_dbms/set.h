/*========================================================================
 *
 * File:      $RCSfile: set.h,v $
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
#ifndef _included_class_set_
#define _included_class_set_ 1

#include <mc_dbms/mc_dbms_types.h>
#include <mc_dbms/collection.h>

class mc_dbms_database;
class mc_dbms_typespec;

template <class E>
class mc_dbms_Set : public mc_dbms_Collection<E>
{
public:
    mc_dbms_Set(dbms_unsigned_int32 sz = 0) : mc_dbms_Collection<E>('S') { }
	
	mc_dbms_Set(const mc_dbms_Set<E>&c) : mc_dbms_Collection<E>('S') { }
	
	mc_dbms_Set(const mc_dbms_Collection<E>&c) : mc_dbms_Collection<E>('S') { }
	
	static mc_dbms_Set<E>& create(mc_dbms_database* db, dbms_unsigned_int32 behavior = 0,
                           dbms_int32 expected_size = 0)
	{
		// Implement in terms of our overloaded new operators.
		mc_dbms_Set<E>* result = new (db, mc_dbms_Set::get_mc_dbms_typespec())mc_dbms_Set<E>;
        return *result;
	}

  	static mc_dbms_typespec* get_mc_dbms_typespec() {
  		return mc_dbms_collection::get_set_typespec();
  	}
};

#endif /* _included_class_set_ */

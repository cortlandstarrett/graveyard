/*========================================================================
 *
 * File:      $RCSfile: bag.h,v $
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
#ifndef _included_class_bag_
#define _included_class_bag_ 1

#if defined(_MSC_VER)
#pragma warning(disable:4786)
#endif

#include <mc_dbms/mc_dbms_types.h>
#include <mc_dbms/collection.h>
#include <mc_dbms/InstanceTracker.h>

class mc_dbms_typespec;
class mc_dbms_database;

template <class E>
class mc_dbms_Bag : public mc_dbms_Collection<E>
{
public:
	mc_dbms_Bag(dbms_unsigned_int32 sz = 0) : mc_dbms_Collection<E>('B') { }
	
	mc_dbms_Bag(const mc_dbms_Bag<E>&c) : mc_dbms_Collection<E>('B') { }
	
	mc_dbms_Bag(const mc_dbms_Collection<E>&c) : mc_dbms_Collection<E>('B') { }
	 
	virtual ~mc_dbms_Bag() { }


  	static mc_dbms_Bag<E>& create(mc_dbms_database* db, dbms_unsigned_int32 behavior = 0,
			   dbms_int32 expected_size = 0)
    {
		// Implement in terms of our overloaded placement-new operators.
		mc_dbms_Bag<E>* result = new ((mc_dbms_database*)db, mc_dbms_Bag::get_mc_dbms_typespec()) mc_dbms_Bag<E>;
        return *result;
    }

public:
  	static mc_dbms_typespec* get_mc_dbms_typespec() {
  		return mc_dbms_collection::get_bag_typespec();
  	}

};

#endif /* _included_class_bag_ */

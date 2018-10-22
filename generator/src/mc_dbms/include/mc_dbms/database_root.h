/*========================================================================
 *
 * File:      $RCSfile: database_root.h,v $
 * Version:   $Revision: 1.11 $
 * Modified:  $Date: 2013/01/10 23:41:53 $
 *
 * (c) Copyright 2005-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#ifndef _included_class_database_root_
#define _included_class_database_root_ 1

#include <mc_dbms/mc_dbms_types.h>
#include <mc_dbms/SerializableObject.h>
#include <list>

class mc_dbms_database;

class mc_dbms_database_root : public SerializableObject {
public:
	friend class mc_dbms_database;
	
   	mc_dbms_database_root();
   
	virtual ~mc_dbms_database_root() { };	
	
	/** 
	 * This is an overloaded delete operator.  Currently, it's just a 
	 * no-op.
	 */
	void operator delete(void* foo) { };
	
	/**
	 * This returns the name of the root.
	 * @return A character string of the name.
	 */
	dbms_const_char_ptr get_name() const { return m_name.c_str(); }
	
	/** 
	 * This returns the entry-point object associated with this root.
	 * @return A pointer to the entry-point object.
	 */
	void* get_value() const { return m_value; }
	
	/** 
	 * This sets the entry-pont object and typespec for this root.
	 * @param new_value The entry-point object.
	 */
	void set_value(void *new_value);
	
	/**
	 * This copies one root onto another.
	 * @param The root to copy from.
	 * @return This root.
	 */
	mc_dbms_database_root& operator=( const mc_dbms_database_root& val);

	virtual long persist();
	
	static mc_dbms_database_root* create();

private:
	std::string m_name;
	void* m_value;
};

#endif /* _included_class_database_root_ */

/*========================================================================
 *
 * File:      $RCSfile: database.h,v $
 * Version:   $Revision: 1.12 $
 * Modified:  $Date: 2013/01/10 23:41:53 $
 *
 * (c) Copyright 2005-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#ifndef _included_class_database_
#define _included_class_database_ 1

#if defined(_MSC_VER)
#pragma warning(disable:4786)
#endif
#include <mc_dbms/mc_dbms_types.h>
#include <mc_dbms/segment.h>
#include <mc_dbms/database_root.h>
#include <mc_dbms/SerializableObject.h>
#include <list>
#include <string>

class mc_dbms_database_root;

class mc_dbms_database : public SerializableObject {
public:
	mc_dbms_database();
	virtual ~mc_dbms_database();
	
	/**
	 * @return Return true if this is a transient database and false if it is not.
	 */
    dbms_boolean is_transient_database() const{ return (this == &m_transient_db); }

    /**
     * This creates a root for the database.  A root is defined as an entry-point
     * for iterations.
     * @param name_arg The name of the root.
     * @return A pointer to the new root.
     */
    mc_dbms_database_root* create_root(dbms_const_char_ptr name_arg);
    
    /**
     * This finds a root in the database.
     * @param name_arg The name of the root to find.
     * @return A pointer to the root.  It is 0 if the root is not found
     */
    mc_dbms_database_root* find_root(dbms_const_char_ptr name_arg) const;

    /**
     * This returns the number of roots in this database. 
     * @return The number of roots associated with this database.
     */
    int get_n_roots() { return m_roots.size(); }
    
    /**
     * This creates a new segment.
     * @returns The pointer to the new segment.
     */
    mc_dbms_segment *create_segment();

	/**
	 * This returns the database the passed-in variable is in.  However, in our
	 * case, this can only be the persistent database, so this function always
	 * simply returns a pointer to our persistent database.
	 *
	 * @param location The pointer for whom the database should be returned.
	 * @return The database the pointer is in.
	 */
    static mc_dbms_database* of(void const* location) { return &m_persistent_db; }
    
    /** 
     * This returns the transient database.  
     * @return The transient database.
     */
    static mc_dbms_database* const get_transient_database() { return &m_transient_db; }
   
    /** 
     * This returns the persistent database.  
     * @return The persistent database.
     */
    static mc_dbms_database* const get_persistent_database() { return &m_persistent_db; }
     
	static setSerializationFlag(bool persistenceEnabled) {
		SerializationEnabled = persistenceEnabled;
	}

	static bool serializationIsEnabled() {
		return SerializationEnabled;
	}
	
	virtual long persist();

	virtual void restore();
	
private:
	static mc_dbms_database m_transient_db;
	static mc_dbms_database m_persistent_db;
	static bool SerializationEnabled;
	
	enum { DB_NOT_YET_ACCESSED = -1 };

	std::list< mc_dbms_database_root > m_roots;
	time_t	m_lastAccessed;
};

#endif /* _included_class_database_ */

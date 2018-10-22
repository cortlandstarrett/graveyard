/*========================================================================
 *
 * File:      $RCSfile: cursor.h,v $
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
#ifndef _included_class_cursor_
#define _included_class_cursor_ 1

#include <mc_dbms/mc_dbms_types.h>
#include <mc_dbms/collection.h>
#include <mc_dbms/list.h>

class mc_dbms_typespec;

class mc_dbms_cursor {
public:
	mc_dbms_cursor() { }
	~mc_dbms_cursor() { }
	
	/**  This returns the typespec of this cursor.
	  *
	  *@return  None
	  *
	  */
	static mc_dbms_typespec* get_mc_dbms_typespec();
	
  	/* mc_dbms_cursor flags */
  	enum {
     	_update_insensitive_cursor     = 1 << 6
  	};
  
	// Enums for user cursor options
  	enum {
         	safe = _update_insensitive_cursor  
  	};
private:
	static mc_dbms_typespec m_type;
};

template <class E>
class mc_dbms_Cursor : public std::iterator<std::bidirectional_iterator_tag,void>,public mc_dbms_cursor {
public:

	virtual ~mc_dbms_Cursor() { }
	
	/** 
	 * This constructor assigns a collection to the cursor.
     * @param c The collection to assign to this cursor.
     * @param _flags (optional) Flags for this container.
     */
	mc_dbms_Cursor(const mc_dbms_Collection<E>& c, dbms_int32 _flags = 0) : 
		m_assigned(true), m_pos(0), m_flags(_flags),
		m_collection( c )
	{
	}

	/**  
	 * This constructor assigns a set to the iterator.
     * @param c The set to assign to this cursor.
     * @param _flags (optional) Flags for this container.
     */	
	mc_dbms_Cursor(const mc_dbms_List<E>& c, dbms_int32 _flags = 0) : m_collection( c ) 
	{
		m_pos = 0;
		m_flags = _flags;
		m_assigned = true;
	}
	
	/**  
	 * This returns the first element in the collection the cursor referencces.
	 * @return Returns the first element in the collection
	 */
	E first()
	{
		E result = 0;
		if( !m_assigned || m_collection.empty() ) {
			m_assigned = false;
		} else {
			m_pos = 0;
			result = (E)m_collection.retrieve_first();
		}
		return result;
	}

	/**  
	 * This returns the last element in the collection the cursor referencces.
	 * @return Returns the last element in the collection
	 */	
	E last()
	{
		E result = 0;
		if( !m_assigned || m_collection.empty() ) {
			m_assigned = false;
		} else {
			dbms_unsigned_int32 size = m_collection.size();
 			m_pos = size-1;
			result = (E)m_collection.retrieve( m_pos );
		}
		return result;
	}

	/**  
	 * This returns the next element in the collection the cursor references.
	 * @return  Returns the next element in the collection
	 */		
	E next()
	{
		E result = 0;
		if( !m_assigned || m_collection.empty() ) {
			m_assigned = false;
		} else {
			m_pos++;
			if( m_pos < m_collection.size() ) {
				result = (E)m_collection.retrieve( m_pos );
			} else {
				m_assigned = false;
			}
		}
		return result;
	}
	
	/**
	 * This returns the previous element in the collection the cursor referencces.
	 * @return Returns the previous element in the collection
	 */	
	E previous()
	{
		E result = 0;
		if( !m_assigned || m_collection.empty() )	{	
			m_assigned = false;
		} else {
			m_pos--;
			if( m_pos > -1 )
				result = (E)m_collection.retrieve( m_pos );
			else
			{
				m_assigned = false;
			}
		}
		return result;	
	}
	
	/**
	 * This retrieves the current object the cursor is pointing at.
	 * @return Returns the current object.
	 */	
	E retrieve()
	{
		return m_collection.retrieve( m_pos );
	}

	/**
	 * This returns the next element in the collection the cursor referencces.
	 * @return Returns the next element in the collection
	 */	
	E operator++() { return next(); }
	
	/**
	 * This returns the previous element in the collection the cursor referencces.
	 * @return Returns the previous element in the collection
	 *
	 */	
	E operator--() { return previous(); }
	
	/**  
	 * This returns whether the cursor is currently pointing at anything.
	 * @return 0 if the cursor is pointing at something, 1 if it is not.
	 */
    dbms_int32 null() 
    {
   		return !m_assigned;
    }

	/**
	 * This retrieves the current object the cursor is pointing at.
	 * @return Returns the current object.
	 */	  
	operator E () { return retrieve(); }
	
	/**
	 * This retrieves the current object the cursor is pointing at.
	 * @return Returns the current object.
	 */	
	E operator-> () { return retrieve(); }

	/**  
	 * Returns the typespec of this cursor
	 * @return None
	 */
	static mc_dbms_typespec* get_mc_dbms_typespec() { return mc_dbms_cursor::get_mc_dbms_typespec(); }

protected:
	const mc_dbms_Collection<E>& m_collection;
	dbms_boolean m_assigned;
	dbms_int32 m_flags;
	dbms_int32 m_pos;
	
};

#endif /* _included_class_cursor_ */

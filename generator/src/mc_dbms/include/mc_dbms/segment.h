/*========================================================================
 *
 * File:      $RCSfile: segment.h,v $
 * Version:   $Revision: 1.10 $
 * Modified:  $Date: 2013/01/10 23:41:52 $
 *
 * (c) Copyright 2005-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#ifndef _included_class_segment_
#define _included_class_segment_ 1

#include <mc_dbms/mc_dbms_types.h>

class mc_dbms_segment {
public:
	mc_dbms_segment(dbms_boolean transient = false) : m_deleted(false), m_empty(true), m_isTransient(transient) { } 
	~mc_dbms_segment() { }
		
    /**
     * This returns the segment number of the segment it is called on.
     * @return An integer representing the segment's segment number.
     */
    dbms_unsigned_int32 get_number() const { return mc_dbms_segment::m_seg_number; }
    
    /** 
     * This returns the transient segment.  In our implementation there is only
     * 1 transient segment (it is static).
     *
     *@return The transient segment.
     */
    static mc_dbms_segment* const get_transient_segment() { return &mc_dbms_segment::m_transSegment; }

	/**
	 * In our implementation there is only one persistent segment (it is static).
	 *
     * @return The persistent segment.
	 */
    static mc_dbms_segment* const get_segment() { return &mc_dbms_segment::m_segment; }

    /**
     * This tells whether the segment has been deleted or not.
     * @return A boolean of 0 if the segment has not been deleted, 1 if it has
     *
     */
    dbms_boolean is_deleted() { return m_deleted; }
    
    /**
     * This tells whether the segment is empty or not.
     * @return A boolean of 0 if the segment is not empty, 1 if it is.
     *
     */  
    dbms_boolean is_empty() { return m_empty; }

	/**
	 * @return Return true if this is a transient segment and false if it is not.
	 */
	dbms_boolean is_transient_segment() { return (this == &m_transSegment); }
	
    static mc_dbms_segment* of(void const * ptr) { return &m_transSegment; }

private:
	dbms_boolean m_deleted;
	dbms_boolean m_empty;
	dbms_boolean m_isTransient;
	
	/**
	 * In this implementation there is only one segment (so this value is constant). 
	 */
	static const dbms_unsigned_int32 m_seg_number;
	
	/**
	 * We only use one persistent segment.
	 */
	static mc_dbms_segment m_segment;
	
	/**
	 * We only use one transient segment.
	 */
	static mc_dbms_segment m_transSegment;
};

#endif /* _included_class_segment_ */

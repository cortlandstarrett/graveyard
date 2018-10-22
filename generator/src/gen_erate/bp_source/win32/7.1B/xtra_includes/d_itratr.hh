/*========================================================================
 *
 * File:      $RCSfile: d_itratr.hh,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:13 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#include <mc_dbms/mc_dbms.hh>

#ifndef D_ITERATORS_HH
#define D_ITERATORS_HH


// Include those header files that are DIRECTLY needed by this one.

#include <vstddef.h>
#include <vstdio.h>


#include <u_typdef.hh>
#include <u_trace.hh>


template< class T >
class D_ordered_element
{
public:

	D_ordered_element( T * p_type_ptr, unsigned int p_number )
		:
		m_type_ptr( p_type_ptr ),
		m_number( p_number )
		{}
		
	~D_ordered_element()
		{}

	T * get_type_ptr()
		{ return m_type_ptr; }
	const unsigned int & get_number() const
		{ return m_number; }

private:

    const unsigned int m_number;
    T *	m_type_ptr;
};


template< class T >
class D_ordered_iterator
{
public:

	D_ordered_iterator() {}
	~D_ordered_iterator() {}

	T * get_first_element();
	T * get_next_element();
	void done_with_elements();

	// IMPORTANT: This function must be specialized for each specific type!

	void populate_elements( void * p_starting_point,
		t_boolean p_use_id = TRUE );

private:
	mc_dbms_List< D_ordered_element< T > * > * m_ordered_coll_ptr;
	mc_dbms_Cursor< D_ordered_element< T > * > * m_ordered_cursor_ptr;

	void insert_element( T * p_type_ptr, unsigned int p_number );
};

template< class T >
T *
D_ordered_iterator< T >::get_first_element()
{
    LOG_TRACE (L_D_DATA, L_FUNCTION_BEGIN, (L_log_string,
	"Begin/End D_ordered_iterator::get_first_element()."));

    D_ordered_element< T > * element_ptr = m_ordered_cursor_ptr->first();
	return( element_ptr ? element_ptr->get_type_ptr() : 0 );
}

template< class T >
T *
D_ordered_iterator< T >::get_next_element()
{
    LOG_TRACE (L_D_DATA, L_FUNCTION_BEGIN, (L_log_string,
	"Begin/End D_ordered_iterator::get_next_element()."));

    D_ordered_element< T > * element_ptr = m_ordered_cursor_ptr->next();
	return( element_ptr ? element_ptr->get_type_ptr() : 0 );
}

template< class T >
void
D_ordered_iterator< T >::done_with_elements()
{
    LOG_TRACE( L_D_DATA, L_FUNCTION_BEGIN, (L_log_string,
	"Begin D_ordered_iterator::done_with_elements()."));

	while ( ! m_ordered_coll_ptr->empty() )
	{
		D_ordered_element< T > * element_ptr = m_ordered_coll_ptr->pick();
		m_ordered_coll_ptr->remove( element_ptr );
		delete element_ptr;
	}

	delete ( mc_dbms_List< D_ordered_element< T > * > * ) m_ordered_coll_ptr;
	delete ( mc_dbms_Cursor< D_ordered_element< T > * > * ) m_ordered_cursor_ptr;

    LOG_TRACE( L_D_DATA, L_FUNCTION_END, (L_log_string,
	"End D_ordered_iterator::done_with_elements()."));
}


#endif /* D_ITERATORS_HH */

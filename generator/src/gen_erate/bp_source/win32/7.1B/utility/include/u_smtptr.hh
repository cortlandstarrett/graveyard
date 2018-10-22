/*========================================================================
 *
 * File:      $RCSfile: u_smtptr.hh,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:34 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#ifndef U_SMTPTR_HH
#define U_SMTPTR_HH




template< class T >
class Smart_ptr
{
public:

	// MANAGER functions

	Smart_ptr( T * p_ptr ) : m_ptr( p_ptr ) {}

	~Smart_ptr() { delete m_ptr; }

	// IMPLEMENTOR functions

	T * operator->() const { return m_ptr; }
	operator T *() const { return m_ptr; }

	// ACCESS functions.

private:

	T * m_ptr;

	// HELPING functions
};




#endif

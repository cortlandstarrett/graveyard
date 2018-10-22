/*========================================================================
 *
 * File:      $RCSfile: CountedPtr.h,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:43:08 $
 *
 * (c) Copyright 2005-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
/**
 * Class for counted reference semantics.
 * Deletes the object to which it refers when the last CountedPtr
 * that refers to it is destroyed.  This comes from "The C++ Standard Library
 * A Tutorial and Reference" by Nicolai M. Josuttis.
 *
 * Note: This is NOT thread safe.
 */

#ifndef COUNTED_PTR_HPP
#define COUNTED_PTR_HPP

template <class T>
class CountedPtr {
  private:
    T* m_ptr;
    long* m_count;

  public:
    /**
     * Initialize pointer with existing pointer
     * This requires that the pointer p is a return value of new.
     */
    explicit CountedPtr (T* p=0)
     : m_ptr(p)
	{
		m_count = new long;
		*m_count = 1; 
    }

    /**
     * copy pointer (one more owner)
     */
    CountedPtr (const CountedPtr<T>& p) throw()
     : m_ptr(p.m_ptr), m_count(p.m_count) {
        ++*m_count;
    }

    /**
     * destructor (delete value if this was the last owner)
     */
    ~CountedPtr () throw() {
        dispose();
    }

    /**
     * Assignment (unshare old and share new value)
     */
    CountedPtr<T>& operator= (const CountedPtr<T>& p) throw() {
        if (this != &p) {
            dispose();
            m_ptr = p.m_ptr;
            m_count = p.m_count;
            ++*m_count;
        }
        return *this;
    }

	bool operator<(const T& that) {
		return *this < *that;
	}
	 
    /**
     * Access the value to which the pointer refers
     */
    T& operator*() const throw() {
        return *m_ptr;
    }
    
    T* operator->() const throw() {
        return m_ptr;
    }

	T* get() const throw() {
		return m_ptr;
	}
	
  private:
    void dispose() {
        if (--*m_count == 0) {
			delete m_count;
            delete m_ptr;
        }
    }
};

#endif /*COUNTED_PTR_HPP*/

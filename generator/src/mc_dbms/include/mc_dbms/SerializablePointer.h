/*========================================================================
 *
 * File:      $RCSfile: SerializablePointer.h,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:52 $
 *
 * (c) Copyright 2005-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#ifndef _included_SerializablePointer_
#define _included_SerializablePointer_ 1

#include <mc_dbms/SerializableObject.h>

/**
 * The purpose of this class is to add a level of abstraction for embedded
 * collection type that hold pointer data.  When we restore this data, because
 * the embedded collections need to inherit from SerializableObject, there is
 * an embedded virtual function pointer that needs to be restored.  By adding this
 * level of abstraction, when it is time to restore a embedded collection of one
 * of the types that has one of these embedded Instance pointers, we can create a
 * new SerializablePointer instance and copy it in the place of the virtual function
 * pointer.
 */
class SerializablePointer : public SerializableObject
{
public:
	SerializablePointer() : m_val(0), m_insertWasPerformed(false) { }
	virtual ~SerializablePointer() { }

	void* getPointer() const { return m_val; }
	void setPointer(void* newVal) { m_val = newVal; }
	
	bool insertWasPerformed() const { return m_insertWasPerformed; }
	void insertCompleted() { m_insertWasPerformed = true; }

	virtual long persist();
	virtual void restore();

	static SerializablePointer* create();

private:
	/** 
	 * This is a void* and not a type* because overloaded operator= on 
	 * an element of "type*" is NOT what we want to do.
	 */
	void* m_val;
	bool m_insertWasPerformed;
};

#endif //_included_SerializablePointer_


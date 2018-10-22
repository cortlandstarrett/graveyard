/*========================================================================
 *
 * File:      $RCSfile: SerializablePointer.cpp,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:48 $
 *
 * (c) Copyright 2005-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#include <mc_dbms/SerializablePointer.h>
#include <mc_dbms/InstanceTracker.h>

long SerializablePointer::persist()
{
	long bytesWritten = 0;
	if (m_val) {
		bytesWritten += writeLong(0); // This is just a flag to tell us there is data here
		bytesWritten += writeLong(m_insertWasPerformed);
		bytesWritten += InstanceTracker::Instance::persist(reinterpret_cast<char*>(m_val));
	} else {
		bytesWritten += writeLong(1);   // This is just a flag to tell us there is NOT data here
	}
	
	return bytesWritten;
}

SerializablePointer* SerializablePointer::create()
{
	SerializablePointer* serPtr = new SerializablePointer();
	serPtr->restore();
	return serPtr;
}

void SerializablePointer::restore()
{
	long isNull = readLong();
	if ( !isNull ) {
		m_insertWasPerformed = readLong();
		InstanceTracker::InstancePtr inst = InstanceTracker::Instance::create();
		m_val = (void*)inst->m_block;
	} else {
		m_val = 0;
	}
}

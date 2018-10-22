/*========================================================================
 *
 * File:      $RCSfile: SerializableObject.h,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:53 $
 *
 * (c) Copyright 2005-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#ifndef _included_class_SerializableObject_
#define _included_class_SerializableObject_ 1

#include <ostream>
#include <istream>
#include <string>

/**
 * This class defines the interface for objects that will be persisted.
 */
class SerializableObject
{
public:
	SerializableObject() { }
	virtual ~SerializableObject() { }

	/**
	 *  Write this instance to the specified stream
	 */
	virtual long persist() = 0;

	virtual void restore() { }
	
	static void setOutputStream(std::ostream& out) { SerializableObject::OutputStream = &out; }
	static void setInputStream(std::istream& in) { SerializableObject::InputStream = &in; }

protected:
	
	static int writeLong(long value);
	
	static int writeString(const std::string& value);
	
	static int writeBlob(char* blob, int size);

	static long readLong();
	
	static std::string readString();
	
	static long readBlob(char* blob);

private:
	
	/**
	 * This function makes sure that the output stream was initialized before
	 * an attempt is made to write to it.
	 */
	static void checkOutputStream() {
		if ( !SerializableObject::OutputStream ) {
			throw std::runtime_error("A write was attempted before the output stream was initialized.");
		}
	}

	/**
	 * This function makes sure that the input stream was initialized before
	 * an attempt is made to read from it.
	 */
	static void checkInputStream() {
		if ( !SerializableObject::InputStream ) {
			throw std::runtime_error("A read was attempted before the input stream was initialized.");
		}
	}

protected:
	static std::ostream* OutputStream;
	static std::istream* InputStream;	
};

/**
 * A convience functin for persisting objects.  This simply makes the call to
 * SerializableObject.persist().
 *
 * @arg out The stream to write the objet to.
 * @arg obj The object to be written.
 * @return A reference to the modified stream.
 */
std::ostream& operator<<(std::ostream& out, SerializableObject& obj);

#endif  // _included_class_SerializableObject_

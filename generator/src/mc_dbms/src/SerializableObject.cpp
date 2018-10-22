/*========================================================================
 *
 * File:      $RCSfile: SerializableObject.cpp,v $
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
#include <mc_dbms/SerializableObject.h>

std::ostream* SerializableObject::OutputStream = 0;
std::istream* SerializableObject::InputStream = 0;

std::ostream& operator<<(std::ostream& out, SerializableObject& obj)
{
	obj.persist();
	return out;
}

int SerializableObject::writeLong(long value) {
	checkOutputStream();
	OutputStream->write((char*)&value, sizeof(long));
	return sizeof(long);
}

int SerializableObject::writeString(const std::string& value)  {
	checkOutputStream();
	writeLong(value.size());
	OutputStream->write(value.data(), value.size());

	return (sizeof(long) + value.size());
}

int SerializableObject::writeBlob(char* blob, int size) {
	checkOutputStream();
	writeLong(size);
	OutputStream->write(blob, size);
	return (sizeof(long) + size);
}

long SerializableObject::readLong() {
	checkInputStream();
	long result = 0;
	InputStream->read((char*)&result, sizeof(long));
	return result; 
}

std::string SerializableObject::readString() {
	checkInputStream();
	long strLength = readLong();
	std::string result;
	if (strLength) {
		result.assign(strLength, '\0');
		InputStream->read(const_cast<char*>(result.data()), strLength);
	}

	return result; 
}

long SerializableObject::readBlob(char* blob) {
	checkInputStream();
	long size = readLong();
	InputStream->read(blob, size);
	return size;
}


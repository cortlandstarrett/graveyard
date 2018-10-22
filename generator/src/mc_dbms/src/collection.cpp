/*========================================================================
 *
 * File:      $RCSfile: collection.cpp,v $
 * Version:   $Revision: 1.16 $
 * Modified:  $Date: 2013/01/10 23:41:48 $
 *
 * (c) Copyright 2005-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#include <mc_dbms/collection.h>
#include <mc_dbms/InstanceTracker.h>
#include <mc_dbms/SerializablePointer.h>
#include <algorithm>
#include <iterator>
#include <iostream>


// sizeof(mc_dbms_collection) for all collection types because they are all the same size.
mc_dbms_typespec mc_dbms_collection::m_typespec( "mc_dbms_collection", sizeof(mc_dbms_collection) );
mc_dbms_typespec mc_dbms_collection::m_array_typespec( "mc_dbms_Array", sizeof(mc_dbms_collection) );
mc_dbms_typespec mc_dbms_collection::m_bag_typespec( "mc_dbms_Bag", sizeof(mc_dbms_collection) );
mc_dbms_typespec mc_dbms_collection::m_list_typespec( "mc_dbms_List", sizeof(mc_dbms_collection) );
mc_dbms_typespec mc_dbms_collection::m_set_typespec( "mc_dbms_Set", sizeof(mc_dbms_collection) );
mc_dbms_typespec mc_dbms_collection::m_dict_typespec( "mc_dbms_Dictionary", sizeof(mc_dbms_collection) );

mc_dbms_collection::~mc_dbms_collection()
{ 
	// Remove it from the InstanceTracker map
	operator delete(this, "");  // Remove from InstanceTracker
}

mc_dbms_typespec* mc_dbms_collection::get_mc_dbms_typespec()
{
	return &m_typespec;
}

mc_dbms_typespec* mc_dbms_collection::get_array_typespec()
{
	return &m_array_typespec;
}

mc_dbms_typespec* mc_dbms_collection::get_bag_typespec()
{
	return &m_bag_typespec;
}

mc_dbms_typespec* mc_dbms_collection::get_list_typespec()
{
	return &m_list_typespec;
}

mc_dbms_typespec* mc_dbms_collection::get_set_typespec()
{
	return &m_set_typespec;
}

mc_dbms_typespec* mc_dbms_collection::get_dict_typespec()
{
	return &m_dict_typespec;
}


void mc_dbms_collection::clear()
{
	m_collection.clear();
}

void* mc_dbms_collection::retrieve_first() const
{
	void* result = 0;
	
	if (!m_collection.empty()) {
		// The way collection are used, they are always collections of pointers
		result = (void*)m_collection.front();
	}
	
	return result;
}

void* mc_dbms_collection::retrieve_first()
{
	return const_cast<const mc_dbms_collection*>(this)->retrieve_first();
}

void* mc_dbms_collection::pick() const
{
	return this->retrieve_first();
}

void mc_dbms_collection::insert_last( void * p )
{
	insert(p);
}

void* mc_dbms_collection::retrieve(dbms_unsigned_int32 offset) const
{
	void* result = 0;
	if (offset < m_collection.size()) {
		result = m_collection[offset];
	}
	return result;
}

void mc_dbms_collection::insert_before(void* p, dbms_unsigned_int32 position)
{
	CollectionType::iterator iter = m_collection.begin();
	if (position <= m_collection.size()) {
		 iter += position;
	}
	m_collection.insert(iter, (void*)p);
}

dbms_int32 mc_dbms_collection::remove(void* p)
{
	dbms_int32 elementWasRemoved = 0;
	
	CollectionType::iterator iter = std::find(m_collection.begin(), m_collection.end(), p);
	if (iter != m_collection.end()) {
		m_collection.erase(iter);
		elementWasRemoved = 1;
	}
	
	return elementWasRemoved;
}

void* mc_dbms_collection::replace_at(void* p, dbms_unsigned_int32 offset)
{
	void* result = 0;
	if (offset < m_collection.size()) {
		void* oldValue = m_collection[offset];
		m_collection[offset] = p;

	} else {
		throw std::runtime_error("mc_dbms_collection::replace_at - Invalid offset specified");
	}

	return result;
}

dbms_int32 mc_dbms_collection::count(const void* e) const
{
	return std::count(m_collection.begin(), m_collection.end(), e);
}

dbms_int32 mc_dbms_collection::operator ==(const mc_dbms_collection& s) const
{
	bool collectionsAreEqual = true;
	if (cardinality() == s.cardinality()) {
		// Get a list of unique elements
		CollectionType sortedCollection = m_collection;
		std::sort(sortedCollection.begin(), sortedCollection.end());
		CollectionType::iterator sortedEnd = std::unique(sortedCollection.begin(), sortedCollection.end());
		CollectionType::const_iterator iter = sortedCollection.begin();
		for (; collectionsAreEqual && iter != sortedEnd; ++iter) {
			if (count(*iter) != s.count(*iter)) {
				collectionsAreEqual = false;
			}
		}
	} else {
		collectionsAreEqual = false;
	}
	
	return collectionsAreEqual;
}

dbms_int32 mc_dbms_collection::operator ==(const void* e) const
{
	// To be equal every element in this collection must be equal to the value passed-in
	return (m_collection.size() == std::count(m_collection.begin(), m_collection.end(), e));
}

mc_dbms_collection& mc_dbms_collection::operator |=(const mc_dbms_collection& s)
{
	CollectionType::const_iterator iter = s.m_collection.begin();
	for (; iter != s.m_collection.end(); ++iter) {
		*this |= (*iter);
	}

	return *this;
}

mc_dbms_collection& mc_dbms_collection::operator |=(const void* e)
{
	CollectionType::iterator iter = std::find(m_collection.begin(), m_collection.end(), e);
	if (iter == m_collection.end()) {
		this->insert( const_cast<void*>(e) );
	}
	return *this;
}

mc_dbms_collection& mc_dbms_collection::operator &=(const mc_dbms_collection& s)
{
	// Get a list of unique elements in this collection
	CollectionType sortedCollection = m_collection;
	std::sort(sortedCollection.begin(), sortedCollection.end());
	CollectionType::iterator sortedEnd = std::unique(sortedCollection.begin(), sortedCollection.end());

	CollectionType::iterator iter = sortedCollection.begin();
	CollectionType::iterator temp_iter;
	for ( ;iter != sortedEnd; ++iter ) {
		int thisCount = count(*iter);
		int thatCount = s.count(*iter);

	    void* elementToRemove = *iter;
		while (thisCount > thatCount++) {
			remove(elementToRemove);
		}
	}

	return *this;
}

mc_dbms_collection& mc_dbms_collection::operator &=(const void* e)
{
	// If the element isn't in the collection we are performing the
	// intersection with, then remove it from this collection.
	m_collection.erase( std::remove_if(	m_collection.begin(), 
										m_collection.end(),
										std::bind2nd(std::not_equal_to<void* >(), e)
										),
						m_collection.end()
						);

	return *this;
}

mc_dbms_collection& mc_dbms_collection::operator -=(const mc_dbms_collection& s)
{
	// Get a list of unique elements in given collection
	CollectionType sortedCollection = s.m_collection;
	std::sort(sortedCollection.begin(), sortedCollection.end());
	CollectionType::iterator sortedEnd = std::unique(sortedCollection.begin(), sortedCollection.end());
	
	CollectionType::iterator iter = sortedCollection.begin();
	for (; iter != sortedEnd; ++iter) {
		int thatCount = s.count(*iter);
		int thisCount = count(*iter);
		int numToRemove = (thatCount <= thisCount) ? thatCount : (thisCount-thatCount); 
		for (int i = 0; i < numToRemove; ++i) {
			remove(*iter);
		}
	}

	return *this;
}

mc_dbms_collection& mc_dbms_collection::operator -=(const void* e)
{
	remove( const_cast<void*>(e) );
	return *this;
}

long mc_dbms_collection::persist() 
{
	long bytesWritten = 0;
		
	// We only store the unsorted collection, at restore-time we'll use it to rebuild the
	// sorted collection.  Note that we chose to persist the unsorted collection because
	// order of the unsorted collection is important, and we want to maintain it.
	bytesWritten += writeLong(m_collection.size());
	CollectionType::iterator iter = m_collection.begin();
	for (; iter != m_collection.end(); ++iter) {
		bytesWritten += InstanceTracker::Instance::persist(reinterpret_cast<char*>(*iter));
	}
	return bytesWritten;
}

mc_dbms_collection* mc_dbms_collection::create() 
{
	mc_dbms_collection* coll = new mc_dbms_collection();
	coll->restore();
	return coll;
}


void mc_dbms_collection::restore()
{
	const long numElements = readLong();
	for (int i = 0; i < numElements; ++i) {
		void* ptr = InstanceTracker::Instance::create()->m_block;;
		insert(ptr);  // This will insert the element into both the sorted and unsorted collections
	}
}

long mc_dbms_collection::persistEmbeddedCollections(char* objectPtr, TrackedType typeID)
{
	long numBytes = 0;
	// See if instances of this type contain any embedded collections
	mc_dbms_typespec::EmbeddedCollectionMap::iterator typeIter = mc_dbms_typespec::EmbeddedCollections.find(typeID);
	if (typeIter != mc_dbms_typespec::EmbeddedCollections.end()) {
		mc_dbms_typespec::EmbeddedCollectionData::iterator offsetIter = typeIter->second.begin();
		for (; offsetIter != typeIter->second.end(); ++offsetIter) {
			int collOffset = offsetIter->first;
			char* embeddedCollectionPtr =  objectPtr + collOffset;
			mc_dbms_typespec::EmbeddedCollectionType embeddedCollType = offsetIter->second;
			
			numBytes += reinterpret_cast<SerializableObject*>(embeddedCollectionPtr)->persist();
		}
	}
	return numBytes;
}


void mc_dbms_collection::createEmbeddedCollections(char* objectPtr, TrackedType typeID, bool objectHasValidCollections)
{
	// See if instances of this type contain any embedded collections
	mc_dbms_typespec::EmbeddedCollectionMap::iterator typeIter = mc_dbms_typespec::EmbeddedCollections.find(typeID);
	if (typeIter != mc_dbms_typespec::EmbeddedCollections.end()) {
		mc_dbms_typespec::EmbeddedCollectionData::iterator offsetIter = typeIter->second.begin();
		for (; offsetIter != typeIter->second.end(); ++offsetIter) {
			int collOffset = offsetIter->first;
			char* embeddedCollectionPtr = objectPtr + collOffset;
			if (objectHasValidCollections) {
				reinterpret_cast<SerializableObject*>(embeddedCollectionPtr)->restore();
			} else {
				createOneEmbeddedCollection(offsetIter->second, embeddedCollectionPtr);
			}
		}
	}
}

void mc_dbms_collection::createOneEmbeddedCollection(mc_dbms_typespec::EmbeddedCollectionType embeddedCollType, char* embeddedCollectionPtr)
{
	switch (embeddedCollType) {
	case mc_dbms_typespec::OneToOne:	// Fall through
	case mc_dbms_typespec::OneToMany:
		{
		SerializablePointer* collPtr = SerializablePointer::create();
		memcpy(embeddedCollectionPtr, (char*)collPtr, sizeof(SerializablePointer));
		}
		break;
	case mc_dbms_typespec::ManyToOne:	// Fall through
	case mc_dbms_typespec::ManyToMany:
		{
		mc_dbms_collection* collPtr = mc_dbms_collection::create();
		memcpy(embeddedCollectionPtr, (char*)collPtr, sizeof(mc_dbms_collection));
		}
		break;
	default:
		{
		std::stringstream msg;
		msg << "Unsupported embedded collection encountered in restoreEmbeddedCollections(). "
		    << "EmbeddedCollType: " << embeddedCollType;
		throw std::runtime_error(msg.str());
		}
	};
}

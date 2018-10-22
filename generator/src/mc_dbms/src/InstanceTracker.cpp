/*========================================================================
 *
 * File:      $RCSfile: InstanceTracker.cpp,v $
 * Version:   $Revision: 1.11 $
 * Modified:  $Date: 2013/01/10 23:41:48 $
 *
 * (c) Copyright 2005-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#include <mc_dbms/InstanceTracker.h>
#include <mc_dbms/segment.h>
#include <mc_dbms/database.h>
#include <mc_dbms/SerializableObject.h>
#include <mc_dbms/collection.h>
#include <mc_dbms/external_object.h>
#include <fstream>
#include <ctime>

InstanceTracker::InstanceContainer InstanceTracker::m_instances;
InstanceTracker::InstanceIDs InstanceTracker::m_instanceIDs;
InstanceTracker::RestoredInstanceMap InstanceTracker::RestoredInstances;

InstanceTracker::Instance::Instance(TrackedType type, int typeSize, int numInstances, long instanceNum, bool isPersisent, char* objPtr) :
	m_type(type),
	m_typeSize(typeSize),
	m_numInstances(numInstances),
	m_instanceID(instanceNum),
	m_persistent(isPersisent),
	m_persistFlag(Persistence::InitialState)
{
	int blockSize = typeSize*numInstances;
	// If a pointer was passed-in then use it.  If not, then allocate one.
	if (!objPtr) {
		m_block = new char[blockSize];
		if (m_block == 0) {
			throw std::runtime_error( "Failed to allocate memory in Instance constructor." );
		}
		
		// This memset is required because there are some classes in the
		// generator that don't properly initialize all their member variables. This
		// causes misc errors that can be difficult to track-down.
		memset(m_block, 0, blockSize);
	} else {
		m_block = objPtr;
	}
}

InstanceTracker::Instance::Instance() :
	m_type(tt_UnitializedTypeID),
	m_typeSize(0),
	m_numInstances(0),
	m_instanceID(-1),
	m_persistent(false),
	m_persistFlag(Persistence::InitialState)
{
}

InstanceTracker::Instance::~Instance()
{
    // The underlaying pointer (m_block) is deleted by the caller to
    // whom the pointer was returned when it was allocated.
}

InstanceTracker::~InstanceTracker() 
{ 
}

long InstanceTracker::Instance::persist(char* blockPtr)
{
	long bytesWritten = 0;

	// Find the InstanceTracker::Instance obect that is being held by database_root.
	InstanceTracker::InstancePtr instPtr = InstanceTracker::findInstance(blockPtr);
	if (instPtr.get()) {
		bytesWritten += instPtr->persist();
	} else {
		throw std::runtime_error("Unable to find the specified Instance object in the instance map.");
	}
	return bytesWritten;
}

long InstanceTracker::Instance::persist()
{
	long numBytes = 0;

	/**
	 * Always write-out the type and instanceID, but only perform
	 * the rest of the serialization for this instance if the instance has not
	 * already been serialized (we only want to recurse once).  When 
	 * restoring, if this instance is encountered multiple times, we DO need to
	 * restore from disk on the first reference to the instance, and then simply 
	 * return the pointer for the remaining references. This type and instanceID
	 * allows us to maintain a map during the restore that can give us the pointer 
	 * to the instance. This is why we always write type and instanceID, but 
	 * don't recurse further for instances that have already been persisted. 
	 */
	numBytes += writeLong(m_type);
	numBytes += writeLong(m_instanceID);
	if ( needToSerialize() ) {
		/**
		 * Mark this as serialized BEFORE the recursion starts, or we'll end-up dumping it multiple times.
		 */
		m_persistFlag = Persistence::Serialized;

		numBytes += writeLong(m_typeSize);
		numBytes += writeLong(m_numInstances);

		if ( mc_dbms_typespec::isSerializableType(m_type) ) {
			if (m_numInstances > 1) {
				std::ostringstream msg;
				msg << "Encountered a serializaable type with multiple instances while persisting. "
					<< "Type: " << m_type << " NumInstances: " << m_numInstances;
				throw std::runtime_error(msg.str());
			}
			numBytes += reinterpret_cast<SerializableObject*>(m_block)->persist();
		} else {
			// WARNING: This will only work for types that don't hold
			// pointers of references.  We do handle embedded collections below.
			numBytes += writeBlob(m_block, m_numInstances*m_typeSize);
		}
		// If there are embedded collection in this type serialize them, if not
		// do nothing
		numBytes += mc_dbms_collection::persistEmbeddedCollections(m_block, m_type);
	}
	
	return numBytes;
}

InstanceTracker::InstancePtr InstanceTracker::Instance::create()
{

	TrackedType type = (TrackedType)readLong();
	long instanceID = readLong();
	InstancePtr instPtr = findRestoredInstance(type, instanceID);
	if ( !instPtr.get() ) {

		// Add an element to the map that tracks restored instance now, before
		// we do something that may cause recursion.  This way, if there is 
		// recursion, we will not re-enter this code for this instance (thus we
		// will only serialize the instance once).  Note that at this point we don't
		// Yet have a pointer to pass to the restored instance map.  We are going
		// ahead and pushing an element now jsut in case during this function 
		// there is recurision that attempts to re-enter this code for the same
		// instance.  If that happens, the findRestoredInstance() code will throw
		// an exception.
		addRestoredInstance(type, instanceID);

		// Keep the instanceID map updated as we restore Instances this will
		// be needed when the restore is complete and we start allocating new
		// instances  (we need to know the next available ID for each type.
		InstanceTracker::updateIDMap(type, instanceID);

		long typeSize = readLong();
		long numInstances = readLong();
		if ( mc_dbms_typespec::isSerializableType(type) ) {
			if (numInstances > 1) {
				std::ostringstream msg;
				msg << "Encountered a serializaable type with multiple instances while restoring. "
					<< "Type: " << type << " NumInstances: " << numInstances;
				throw std::runtime_error( msg.str() );
			}
			
			// We have different types of serializeable objects.  The action we take
			// needs to be based on the type.
			char* objPtr = 0;
			if ( mc_dbms_typespec::isCollectionType(type) ) {
				// We are taking advantage of the fact that all "collection"  types are
				// the same size (they all inherit from mc_dbms_collection, and it holds all 
				// the data.
				objPtr = (char*)mc_dbms_collection::create();
			} else {
		
				// It is required that this method be implemented in external applications
				// that use the mc_dbms library.
				objPtr = mcdbms_RestoreExternalObject(type);
			}
			instPtr = InstanceTracker::createInstance(type, typeSize, numInstances, true, instanceID, objPtr);

		} else {
			instPtr = InstanceTracker::createInstance(type, typeSize, numInstances, true, instanceID);
			
			readBlob(instPtr->m_block);
		}
		
		// Update the restored instance map with the new instance data
		addRestoredInstance(type, instanceID, instPtr);
			
		mc_dbms_collection::createEmbeddedCollections(instPtr->m_block, type);
	}

	return instPtr;
}

void* InstanceTracker::allocate(mc_dbms_typespec* ts,mc_dbms_database* db, mc_dbms_segment* seg, dbms_int32 numToAllocate)
{
	bool isPersistent = true;
	if ((db && db->is_transient_database()) || (seg && seg->is_transient_segment())) { 
		isPersistent = false;
	}
	TrackedType typeID = ts->get_type_id();
	long instanceNumber = 0;
	InstanceIDs::iterator iter = m_instanceIDs.find(typeID);
	if (iter != m_instanceIDs.end()) {
		instanceNumber = iter->second;	
	}
	
	// Increment the instance count for this ID (add it to the map if it's the
	// first one).
	m_instanceIDs[typeID] = instanceNumber+1;

	return InstanceTracker::createInstance(typeID, ts->size(), numToAllocate, isPersistent, instanceNumber)->m_block;
}

InstanceTracker::InstancePtr InstanceTracker::createInstance(TrackedType typeID, int typeSize, int numToAllocate, bool isPersistent, long instanceNumber, char* objPtr)
{
	numToAllocate = numToAllocate ? numToAllocate : 1;
	InstancePtr instPtr(new Instance(typeID, typeSize, numToAllocate, instanceNumber, isPersistent, objPtr));
	
	// If the pointer is already there, update it, if not then add it.
	// We do this instead of insert because Galaxy will sometimes delete
	// transient data out from under us (we allocate, they destroy).
	InstanceContainer::iterator instIter = m_instances.find(instPtr->m_block);
	if (instIter != m_instances.end()) {
		instIter->second = instPtr;
	} else {
		m_instances.insert( std::make_pair(instPtr->m_block, instPtr ) );
	}
	
	return instPtr;
}

void InstanceTracker::destroy(void* ptr)
{
	// Wrapping this find in a size check to prevent a core dump that
	// happens during the CRT exit.  Cleanup is being done at that time, and 
	// static members (like m_instances are being deleted in the wrong order).
	// 
	if (m_instances.size() > 0) {
		InstanceContainer::iterator instIter = m_instances.find( reinterpret_cast<char*>(ptr) );
		if (instIter != m_instances.end()) {
			// Erase the instance from the container.  Note that we leave the
			// InstanceContainer
			m_instances.erase(instIter);		
		}
	}
}
	
void InstanceTracker::purge() 
{
	InstanceContainer::iterator instIter = m_instances.begin();
	while ( instIter != m_instances.end()) {
		char* blockPtr = instIter->first;
		InstanceContainer::iterator tempIter = instIter;
		tempIter++;
		// Erase the instance from the container.  Note that we leave the
		// InstanceContainer
		m_instances.erase(instIter);
		instIter = tempIter;
	}
}

void* InstanceTracker::findInstance(void* ptr, int offset)
{ 
	void* result = 0;
	// Find the instance container for the given type.
	char* blockPtr = reinterpret_cast<char*>(ptr) - offset;
	InstanceContainer::iterator instIter = m_instances.find(blockPtr);
	if (instIter != m_instances.end()) {
		result = instIter->second->m_block;
	}
	return result;
}

InstanceTracker::InstancePtr InstanceTracker::findInstance(char* ptr)
{ 
	InstanceTracker::InstancePtr result;
	
	InstanceContainer::iterator instIter = m_instances.find(ptr);
	if (instIter != m_instances.end()) {
		result = instIter->second;
	}

	return result;
}

int InstanceTracker::instanceCount(mc_dbms_typespec* ts)
{
	int result = 0;
	
	if (!ts) {
		result = m_instances.size();
	} else {
		long type = ts->get_type_id();
		InstanceContainer::iterator instIter = m_instances.begin();
		for (; instIter != m_instances.end(); ++instIter) {
			if (instIter->second->m_type == type) {
				result++;
			}
		}
	}
	
	return result;
	
}

long InstanceTracker::persist()
{
	long numBytesWritten = 0;
	
#ifdef DUMP_ORPHANDED_INSTANCES
	// Write out the instances (we'll write the total number of instance here,
	// but we'll update this at the end based on how many we really had to 
	// write out.
	std::ios::pos_type numInstancePos = OutputStream->tellp();
	long numInstancesWritten = m_instances.size();
	numBytesWritten += writeLong(numInstancesWritten);
	InstanceContainer::iterator instIter = m_instances.begin();
	for (; instIter != m_instances.end(); ++instIter) {
		// We only serialize the ones that haven't been serialized yet. 
		if ( instIter->second->m_persistFlag != Persistence::Serialized ) {
			numBytesWritten += instIter->second->persist();
		} else {
			numInstancesWritten--;
		}
	}

	// Re-write the updated count and then reset the file pointer to the end of file.
	// Note that we do NOT increment the bytesWritten count here.
	OutputStream->seekp(numInstancePos);
	writeLong(numInstancesWritten);
	OutputStream->seekp(std::ios::end);
#endif

	return numBytesWritten;
}

void InstanceTracker::create()
{
#ifdef DUMP_ORPHANDED_INSTANCES
	// Restore Instances
	long numInstances = readLong();
	for (int i = 0; i < numInstances; ++i) {
		Instance::create();
	}
#endif
}

void InstanceTracker::report(bool cleanShutdown)
{
	std::ofstream persistentStream("gen_stats_persistent.txt", std::ios_base::out|std::ios_base::trunc);
	std::ofstream transientStream("gen_stats_transient.txt", std::ios_base::out|std::ios_base::trunc);
	long transSize = 0;
	long persistSize = 0;
	int transCount = 0;
	int persistCount = 0;
	int persistTypes = 0;
	int transTypes = 0;
	int* typeCount= 0;
	
	time_t aclock;
	time( &aclock );
	struct tm *curTime = localtime( &aclock );

	persistentStream << asctime( curTime )
					 << "Persistent Instance Data Report: (CleanShutdown = " << cleanShutdown << ")" << std::endl
		       		 << "----------------------------------------------------" << std::endl;

	transientStream << asctime( curTime )
					<< "Transient Instance Data Report: (CleanShutdown = " << cleanShutdown << ")" << std::endl
		       		<< "---------------------------------------------------" << std::endl;

	
	// We will use this to send the transient data to the transient report and the
	// persisntent to the persistent report.  This allows us to report on both types
	// of data in one pass.
	std::ofstream* streamPtr = 0;
	
	bool dataWasFound = false;
	// Print out the details for every type and every instance.
	InstanceContainer::iterator typeIter = m_instances.begin();
	for (;typeIter != m_instances.end(); ++typeIter) {
		bool displayedTransHeading = false;
		bool displayedPersistHeading = false;
		bool* displayedHeading = 0;
		
		InstancePtr inst = typeIter->second;
		TrackedType type_id = inst->m_type;
		if ( inst->m_persistent) { 
			streamPtr = &persistentStream;
			persistSize += inst->m_typeSize * inst->m_numInstances;
			persistCount++;
			displayedHeading = &displayedPersistHeading;
			typeCount = &persistTypes;
		} else {
			streamPtr = &transientStream;
			transSize += inst->m_typeSize * inst->m_numInstances;
			transCount++;
			displayedHeading = &displayedTransHeading;
			typeCount = &transTypes;
		}

		if (!(*displayedHeading)) {
			*streamPtr << std::endl 
				<< "\tType ID " << type_id <<": ("<< mc_dbms_typespec::get_name(type_id) <<")" << std::endl
		      	<< "\t------------------------------------------ " << std::endl;
			    
		    *displayedHeading = true;
		    *typeCount++;
		}
		
		*streamPtr << "\tInstanceID: " << inst->m_instanceID
					<< "  Type: " << inst->m_type
					<< "  TypeSize: " << inst->m_typeSize
					<< "  Occurances: " << inst->m_numInstances
					<< std::endl;
	}

	transientStream << std::endl
					<< "\tTransient Data Summary:" << std::endl
		      	  	<< "\t-----------------------" << std::endl
		      		<< "\tBuffer Size:\t\t" << transSize << std::endl
		      		<< "\tNumber of Instances:\t" << transCount << std::endl
			  		<< "\tNumber of Types:\t" << transTypes << std::endl
					<< std::endl
				    << "Summary (transient and persistent):" << std::endl
				    << "-----------------------------------" << std::endl
				    << "Buffer Size:\t\t" << (transSize+persistSize) << std::endl
				    << "Number of Instances:\t" << (transCount+persistCount) << std::endl
					<< "Number of Types:\t" << m_instances.size() << std::endl 
					<< std::endl;
	
	persistentStream  << std::endl
			<< "\tPersistent Data Summary:" << std::endl
      	  	<< "\t------------------------" << std::endl
      		<< "\tBuffer Size:\t\t" << persistSize << std::endl
      		<< "\tNumber of Instances:\t" << persistCount << std::endl
	  		<< "\tNumber of Types:\t" << persistTypes << std::endl
		  	<< std::endl
	        << "Summary (transient and persistent):" << std::endl
	        << "-----------------------------------" << std::endl
	        << "Buffer Size:\t\t" << (transSize+persistSize) << std::endl
	        << "Number of Instances:\t" << (transCount+persistCount) << std::endl
		    << "Number of Types:\t" << m_instances.size() << std::endl 
		    << std::endl;      
}
